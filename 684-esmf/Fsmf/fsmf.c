#include "fsmf.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdarg.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// framework -------------------------------------------------------------------
typedef struct m_evt_timer_tag {
    int sig;
    int time_ms_delay;
    uint32_t timeout_ms;
} m_evt_timer_t;

typedef struct frame_tag {
    // 状态机池
    uint32_t flag_fsm_enable;
    m_fsm_t * fsm[M_SM_NUM_MAX];

    // 定时器池
    m_evt_timer_t e_timer_pool[M_ETIMERPOOL_SIZE];
    uint32_t flag_etimerpool[M_ETIMERPOOL_SIZE / 32 + 1];   // 事件池标志位
    bool is_etimerpool_empty;
    uint32_t timeout_ms_min;

    bool is_enabled;
    bool is_running;
    bool is_idle;
    
    uint32_t time_crt_ms;
} frame_t;

static frame_t frame;

// data ------------------------------------------------------------------------
static const uint32_t table_left_shift[32] = {
    0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
    0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
};

static const uint32_t table_left_shift_rev[32] = {
    0xfffffffe, 0xfffffffd, 0xfffffffb, 0xfffffff7, 0xffffffef, 0xffffffdf, 0xffffffbf, 0xffffff7f,
    0xfffffeff, 0xfffffdff, 0xfffffbff, 0xfffff7ff, 0xffffefff, 0xffffdfff, 0xffffbfff, 0xffff7fff,
    0xfffeffff, 0xfffdffff, 0xfffbffff, 0xfff7ffff, 0xffefffff, 0xffdfffff, 0xffbfffff, 0xff7fffff,
    0xfeffffff, 0xfdffffff, 0xfbffffff, 0xf7ffffff, 0xefffffff, 0xdfffffff, 0xbfffffff, 0x7fffffff
};

// macro -----------------------------------------------------------------------
#define HSM_TRIG_(state_, sig_)                                                \
    ((*(state_))(me, &fsmf_system_evt_table[sig_]))

#define HSM_EXIT_(state_) do {                                                 \
    if (HSM_TRIG_(state_, Evt_Exit) == M_Ret_Handled) {                        \
    }                                                                          \
} while (false)

#define HSM_ENTER_(state_) do {                                                \
    if (HSM_TRIG_(state_, Evt_Enter) == M_Ret_Handled) {                       \
    }                                                                          \
} while (false)

// fsmf ------------------------------------------------------------------------
static void fsmf_clear(void)
{
    // 清空事件定时器池
    for (int i = 0; i < M_ETIMERPOOL_SIZE / 32 + 1; i ++)
        frame.flag_etimerpool[i] = 0xffffffff;
    for (int i = 0; i < M_ETIMERPOOL_SIZE; i ++)
        frame.flag_etimerpool[i / 32] &= table_left_shift_rev[i % 32];
    frame.is_etimerpool_empty = true;
}

void fsmf_init(void)
{
    fsmf_clear();
    frame.is_enabled = true;
    frame.is_running = false;
    frame.is_idle = true;
}

int fsmf_evttimer(void)
{
    // 获取当前时间，检查延时事件队列`
    frame.time_crt_ms = port_get_time_ms();
    
    if (frame.is_etimerpool_empty == true)
        return 210;

    // 时间未到达
    if (frame.time_crt_ms < frame.timeout_ms_min)
        return 211;
    
    // 若时间到达，将此事件推入事件队列，同时在e_timer_pool里删除。
    bool is_etimerpool_empty = true;
    for (int i = 0; i < M_ETIMERPOOL_SIZE; i ++) {
        if ((frame.flag_etimerpool[i / 32] & table_left_shift[i % 32]) == 0)
            continue;
        if (frame.e_timer_pool[i].timeout_ms > frame.time_crt_ms) {
            is_etimerpool_empty = false;
            continue;
        }

        evt_send(frame.e_timer_pool[i].sig);
        // 清零标志位
        frame.flag_etimerpool[i / 32] &= table_left_shift_rev[i % 32];
    }
    frame.is_etimerpool_empty = is_etimerpool_empty;
    if (frame.is_etimerpool_empty == true)
        return 212;

    // 寻找到最小的时间定时器
    uint32_t min_time_out_ms = UINT32_MAX;
    for (int i = 0; i < M_ETIMERPOOL_SIZE; i ++) {
        if ((frame.flag_etimerpool[i / 32] & table_left_shift[i % 32]) == 0)
            continue;
        if (min_time_out_ms <= frame.e_timer_pool[i].timeout_ms)
            continue;
        min_time_out_ms = frame.e_timer_pool[i].timeout_ms;
    }
    frame.timeout_ms_min = min_time_out_ms;

    return 0;
}

int fsmf_once(void)
{
    // 保证框架先初始化
    M_ASSERT(frame.is_enabled == true);

    // 检查是否有状态机的注册
    if (frame.flag_fsm_enable == 0 || frame.flag_fsm_enable == 0) {
        return 201;
    }

    fsmf_evttimer();

    if (frame.is_idle == true) {
        return 202;
    }
    // 寻找到优先级最高且事件队列不为空的状态机
    m_fsm_t * p_fsm = (m_fsm_t *)0;
    for (int i = 0; i < M_SM_NUM_MAX; i ++) {
        if ((frame.flag_fsm_enable & table_left_shift[i]) == 0)
            continue;
        if (frame.fsm[i]->is_equeue_empty == true)
            continue;
        p_fsm = frame.fsm[i];
        break;
    }
    if (p_fsm == (m_fsm_t *)0) {
        frame.is_idle = true;
        
        return 203;
    }

    // 从事件队列里，寻找到最老的事件
    m_evt_t * e = p_fsm->e_queue + p_fsm->tail;
    port_irq_disable();
    p_fsm->tail ++;
    p_fsm->tail %= p_fsm->depth;
    if (p_fsm->tail == p_fsm->head) {
        p_fsm->is_equeue_empty = true;
        p_fsm->tail = 0;
        p_fsm->head = 0;
    }
    port_irq_enable();

    // 对事件进行执行
    m_ret_t sm_ret = ((m_state_handler)(p_fsm->state))(p_fsm, e);
    // 对状态进行转换
    if (sm_ret == M_Ret_Tran) {
        sm_ret = ((m_state_handler)(p_fsm->state_bkp))(p_fsm, &(m_evt_t){Evt_Exit});
        M_ASSERT(sm_ret == M_Ret_Handled);
        sm_ret = ((m_state_handler)(p_fsm->state))(p_fsm, &(m_evt_t){Evt_Enter});
        M_ASSERT(sm_ret == M_Ret_Handled);
        p_fsm->state_bkp = p_fsm->state;
    }

    return 0;
}

int fsmf_run(void)
{
    M_ASSERT(frame.is_enabled == true);
    hook_start();
    frame.is_running = true;

    while (true) {
        int ret = fsmf_once();
        if ((int)(ret / 100) == 2) {
            hook_idle();
        }
    }
}

// state machine ---------------------------------------------------------------
void fsm_init(m_fsm_t * const me, uint32_t pri, uint32_t fifo_depth)
{
    // 框架需要先启动起来
    M_ASSERT(frame.is_enabled == true);
    M_ASSERT(frame.is_running == false);
    // 参数检查
    M_ASSERT(me != (m_fsm_t *)0);
    M_ASSERT(pri >= 0 && pri < M_SM_NUM_MAX);

    // 检查优先级的重复注册
    M_ASSERT((frame.flag_fsm_enable & table_left_shift[pri]) == 0);

    // 注册到框架里
    frame.flag_fsm_enable |= table_left_shift[pri];
    frame.fsm[pri] = me;
    // 状态机   
    me->priv = pri;
    me->is_enabled = false;

    // 事件队列
    port_irq_disable();
    me->e_queue = (m_evt_t *)port_malloc(fifo_depth * sizeof(m_evt_t));
    M_ASSERT(me->e_queue != 0);
    me->head = 0;
    me->tail = 0;
    me->depth = fifo_depth;
    me->is_equeue_empty = true;
    port_irq_enable();
}

void fsm_start(m_fsm_t * const me, m_state_handler state_init)
{
    // 框架需要先启动起来
    M_ASSERT(frame.is_enabled == true);
    M_ASSERT(frame.is_running == false);
    // 参数检查
    M_ASSERT(me != (m_fsm_t *)0);
    // 防止二次启动
    M_ASSERT(me->is_enabled == false);

    me->is_enabled = true;

    m_ret_t ret = state_init(me, &(m_evt_t){Evt_Null});
    // 初始状态的返回值必须是M_Ret_Tran。
    M_ASSERT(ret == M_Ret_Tran);
    ret = ((m_state_handler)(me->state))(me, &(m_evt_t){Evt_Enter});
    // Evt_Enter事件的返回值必须是M_Ret_Handled。
    M_ASSERT(ret == M_Ret_Handled);
    me->state_bkp = me->state;
}

// event -----------------------------------------------------------------------
void evt_send(uint32_t evt_id)
{
    // 保证框架已经运行
    M_ASSERT(frame.is_enabled == true);
    // 没有状态机使能，返回
    if (frame.flag_fsm_enable == 0)
        return;

    port_irq_disable();

    int priv = M_SM_NUM_MAX;
    for (int i = 0; i < M_SM_NUM_MAX; i ++) {
        if ((frame.flag_fsm_enable & table_left_shift[i]) == 0)
            continue;
        if (frame.fsm[i]->is_enabled == false)
            continue;
        // 事件队列未满，将事件池序号放入事件队列
        *(frame.fsm[i]->e_queue + frame.fsm[i]->head) = (m_evt_t){evt_id};

        frame.fsm[i]->head ++;
        frame.fsm[i]->head %= frame.fsm[i]->depth;
        if (frame.fsm[i]->is_equeue_empty == true)
            frame.fsm[i]->is_equeue_empty = false;
        frame.is_idle = false;

        priv = 0;
    }
    if (priv == M_SM_NUM_MAX)
        M_ASSERT(false);

    port_irq_enable();
}

void evt_send_delay(uint32_t evt_id, uint32_t time_ms)
{
    M_ASSERT(time_ms >= 0);

    if (time_ms == 0) {
        evt_send(evt_id);
        return;
    }

    // 寻找到空的时间定时器
    uint32_t index_empty = UINT32_MAX;
    for (int i = 0; i < (M_ETIMERPOOL_SIZE / 32 + 1); i ++) {
        if (frame.flag_etimerpool[i] == UINT32_MAX)
            continue;
        for (int j = 0; j < 32; j ++) {
            if ((frame.flag_etimerpool[i] & table_left_shift[j]) == 0) {
                frame.flag_etimerpool[i] |= table_left_shift[j];
                index_empty = i * 32 + j;
                break;
            }
        }
        break;
    }
    M_ASSERT(index_empty != UINT32_MAX);

    uint32_t time_crt_ms = port_get_time_ms();
    frame.e_timer_pool[index_empty] = (m_evt_timer_t) {
        evt_id, time_ms, time_crt_ms + time_ms
    };

    frame.is_etimerpool_empty = false;
    
    // 寻找到最小的时间定时器
    uint32_t min_time_out_ms = UINT32_MAX;
    for (int i = 0; i < M_ETIMERPOOL_SIZE; i ++) {
        if ((frame.flag_etimerpool[i / 32] & table_left_shift[i % 32]) == 0)
            continue;
        if (min_time_out_ms <= frame.e_timer_pool[i].timeout_ms)
            continue;
        min_time_out_ms = frame.e_timer_pool[i].timeout_ms;
    }
    frame.timeout_ms_min = min_time_out_ms;
}

// state tran ------------------------------------------------------------------
m_ret_t m_tran(m_fsm_t * const me, m_state_handler state)
{
    me->state = (void *)state;

    return M_Ret_Tran;
}

/* for unittest ------------------------------------------------------------- */
void * fsmf_get_frame(void)
{
    return (void *)&frame;
}

#ifdef __cplusplus
}
#endif
