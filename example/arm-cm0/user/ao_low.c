
#include "ao.h"
#include "event_def.h"

// 当前模块名称的定义
Q_DEFINE_THIS_MODULE("AoLow")

// 状态函数的声明 ---------------------------------------------------------------
// 初始状态
static QState state_init(ao_low_t * const me, void const * const par);
// 工作状态
static QState state_work(ao_low_t * const me, QEvt const * const e);

// 接口函数的实现 ---------------------------------------------------------------
// 活动对象（AO，Active Object）LED的构建
void ao_low_ctor(ao_low_t * const me)
{
    // LED对象的变量初始化
    me->status = false;

    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    QACTIVE_START(  &me->super,
                    1,
                    me->evt_queue,
                    AO_QUEUE_LENGTH,
                    (void *)0,
                    0U,
                    (QEvt *)0);
}

static void cpu_wait(uint32_t time_ms)
{
    uint32_t loop_size;
    
    while (time_ms --) {
        loop_size = 8000;
        while (loop_size --) {
            __nop();
        }
    }
}

// 状态函数的实现 ---------------------------------------------------------------
// 初始状态
static QState state_init(ao_low_t * const me, void const * const par)
{
    // 时间对象的构建
    QTimeEvt_ctorX(&me->timeEvt, &me->super, Evt_AoLow, 0U);

    return Q_TRAN(&state_work);
}

// LED的on状态
static QState state_work(ao_low_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:                           // 状态的进入事件
            QTimeEvt_armX(&me->timeEvt, 10U, 0U);
            me->status = true;                      // 打开LED灯
            return Q_HANDLED();                     // 通知框架，事件已处理

        case Evt_AoLow:
            QTimeEvt_armX(&me->timeEvt, 11000U, 0U);
            cpu_wait(10000);                        // 阻塞CPU长达10S，以测试高优先级的抢占
            return Q_HANDLED();

        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}
