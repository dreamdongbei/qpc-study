
#include "ao_led.h"
#include "evt_def.h"

// 当前模块名称的定义
Q_DEFINE_THIS_MODULE("AoLow")

// 状态函数的声明 ---------------------------------------------------------------
static QState state_init(ao_led_t * const me, void const * const par);
static QState state_on(ao_led_t * const me, QEvt const * const e);
static QState state_off(ao_led_t * const me, QEvt const * const e);

// 接口函数的实现 ---------------------------------------------------------------
// 活动对象（AO，Active Object）LED的构建
void ao_led_ctor(ao_led_t * const me)
{
    // LED对象的变量初始化
    me->status = false;

    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 时间对象的构建
    QTimeEvt_ctorX(&me->timeEvt, &me->super, Evt_Time_500ms, 0U);
    // 活动对象的启动
    QACTIVE_START(  &me->super,
                    1,
                    me->evt_queue,
                    AO_LED_QUEUE_LENGTH,
                    (void *)0,
                    0U,
                    (QEvt *)0);
}

// 状态函数的实现 ---------------------------------------------------------------
// 初始状态
static QState state_init(ao_led_t * const me, void const * const par)
{
    // 事件Evt_Time_500ms的订阅
//    QActive_subscribe(&me->super, Evt_Time_500ms);

    return Q_TRAN(&state_on);
}

// LED的on状态
static QState state_on(ao_led_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:                           // 状态的进入事件
            me->status = true;                      // 打开LED灯
            QTimeEvt_armX(&me->timeEvt, 500, 0U);   // 500ms后发送时间事件
            return Q_HANDLED();                     // 通知框架，事件已处理

        case Q_EXIT_SIG:
            QTimeEvt_disarm(&me->timeEvt);
            return Q_HANDLED();

        case Evt_Time_500ms:
            return Q_TRAN(&state_off);              // 通知框架，状态转移至state_off

        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}

// LED的Off状态
static QState state_off(ao_led_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:
            me->status = false;                     // 关闭LED灯
            QTimeEvt_armX(&me->timeEvt, 500, 0U);
            return Q_HANDLED();

        case Q_EXIT_SIG:
            QTimeEvt_disarm(&me->timeEvt);
            return Q_HANDLED();

        case Evt_Time_500ms:
            return Q_TRAN(&state_on);

        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}
