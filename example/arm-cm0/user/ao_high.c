
#include "ao.h"
#include "event_def.h"

// 当前模块名称的定义
Q_DEFINE_THIS_MODULE("AoHigh")

// 状态函数的声明 ---------------------------------------------------------------
// 初始状态
static QState state_init(ao_high_t * const me, void const * const par);
// 工作状态
static QState state_work(ao_high_t * const me, QEvt const * const e);

// 接口函数的实现 ---------------------------------------------------------------
// 活动对象（AO，Active Object）LED的构建
void ao_high_ctor(ao_high_t * const me)
{
    // LED对象的变量初始化
    me->count = 0;

    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 时间对象的构建
    QTimeEvt_ctorX(&me->timeEvt, &me->super, Evt_AoHigh, 0U);
    // 活动对象的启动
    QACTIVE_START(  &me->super,
                    2,
                    me->evt_queue,
                    AO_QUEUE_LENGTH,
                    (void *)0,
                    0U,
                    (QEvt *)0);
}

// 状态函数的实现 ---------------------------------------------------------------
// 初始状态
static QState state_init(ao_high_t * const me, void const * const par)
{
    // 事件Evt_AoHigh的订阅
    QActive_subscribe(&me->super, Evt_AoHigh);
    

    return Q_TRAN(&state_work);
}

// 工作状态
uint32_t count_evt_high = 0;
static QState state_work(ao_high_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:
            QTimeEvt_armX(&me->timeEvt, 10U, 0U);
            return Q_HANDLED();
        
        case Evt_AoHigh:
            QTimeEvt_armX(&me->timeEvt, 1000U, 0U); // 每1000ms产生一次事件
            me->count ++;                           // 计数
            count_evt_high ++;
            return Q_HANDLED();
        
        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}
