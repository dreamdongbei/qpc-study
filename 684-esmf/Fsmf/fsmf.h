
#ifndef FSMF_H
#define FSMF_H

#ifdef __cplusplus
extern "C" {
#endif

/* include ------------------------------------------------------------------ */
#include "stdint.h"
#include "stdbool.h"
#include "fsmf_cfg.h"

/* data struct -------------------------------------------------------------- */
// 系统事件、时间事件的定义
enum m_evt_id_tag {
    // 系统事件
    Evt_Null = 0, Evt_Enter, Evt_Exit, Evt_User,
};

// 用户事件的定义
#include "evt_def.h"

typedef enum m_ret_tag {
    M_Ret_Handled = 0,
    M_Ret_Tran = !M_Ret_Handled
} m_ret_t;

// 事件类
typedef struct m_evt_tag {
    int sig;
} m_evt_t;

// 行为对象类
typedef struct fsm_tag {
    uint32_t priv;
    bool is_enabled;
    volatile void * state;
    volatile void * state_bkp;

    // evt queue
    m_evt_t * e_queue;
    uint32_t head;
    uint32_t tail;
    uint32_t depth;
    bool is_equeue_empty;
} m_fsm_t;

// 状态函数句柄的定义
typedef m_ret_t (* m_state_handler)(m_fsm_t * const me, m_evt_t const * const e);

// api -------------------------------------------------------------------------
// 关于fsmf框架 ---------------------------------------------
// 对框架进行初始化，在各状态机初始化之前调用。
void fsmf_init(void);
// 启动框架，放在main函数的末尾。
int fsmf_run(void);

// 关于状态机 -----------------------------------------------
// 状态机初始化函数
void fsm_init(m_fsm_t * const me, uint32_t pri, uint32_t fifo_depth);
void fsm_start(m_fsm_t * const me, m_state_handler state_init);

// 关于事件 -------------------------------------------------
// 注：能在中断服务函数中使用。
void evt_send(uint32_t evt_id);
// 注：不能在中断服务函数中使用，否则可能会导致崩溃。
void evt_send_delay(uint32_t evt_id, uint32_t delay_ms);

// 关于状态 -------------------------------------------------
m_ret_t m_tran(m_fsm_t * const me, m_state_handler state);

#define M_TRAN(target)              m_tran((m_fsm_t * )me, (m_state_handler)target)
#define STATE_CAST(state)           (m_state_handler)(state)

/* port --------------------------------------------------------------------- */
uint32_t port_get_time_ms(void);
void port_irq_disable(void);
void port_irq_enable(void);
void * port_malloc(uint32_t size);

/* hook --------------------------------------------------------------------- */
void hook_idle(void);
void hook_stop(void);
void hook_start(void);

/* interrupt disable/enable ------------------------------------------------- */
#define m_irq_disable()             port_irq_disable()
#define m_irq_enable()              port_irq_enable()

// #define NDEBUG
#include "assert.h"
#define M_ASSERT(t)                 (void)0

/* for unittest ------------------------------------------------------------- */
void * fsmf_get_frame(void);
int fsmf_once(void);
void set_time_ms(uint64_t time_ms);
int fsmf_evttimer(void);

int fsmf_unittest_sm(void);

#ifdef __cplusplus
}
#endif

#endif
