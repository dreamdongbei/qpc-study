#include "sm_led.h"
#include "led.h"
#include "qpc.h"
#include "event_def.h"
#include "sm_def.h"

Q_DEFINE_THIS_MODULE("SmLed")

static QState state_init(sm_led_t * const me, void const * const par);
static QState state_on(sm_led_t * const me, QEvt const * const e);
static QState state_off(sm_led_t * const me, QEvt const * const e);

sm_led_t sm_led;

void sm_led_init(void)
{
    sm_led_t *me = &sm_led;
    
    me->status = 0;

    // 活动对象的构造
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    static QEvt const *e_queue[SM_LED_QUEUE_LENGTH];
    static uint8_t stack[512];
    QACTIVE_START(&me->super,
                  SmPrio_Led,
                  e_queue, SM_LED_QUEUE_LENGTH,
                  stack, sizeof(stack),
                  (void *)0);
}

// 状态函数的实现 ---------------------------------------------------------------
// 初始状态
static QState state_init(sm_led_t * const me, void const * const par)
{
    led_init();
    
    return Q_TRAN(&state_off);
}

// LED的on状态
static QState state_on(sm_led_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:                           // 状态的进入事件
            for (uint8_t i = 0; i < Device_Led_Max; i ++)
            {
                led_set_status(i, LedStatus_On);
            }
            me->status = 1;
            return Q_HANDLED();                     // 通知框架，事件已处理

        case Q_EXIT_SIG:
            return Q_HANDLED();

        case Evt_LedOnOff:
            return Q_TRAN(&state_off);              // 通知框架，状态转移至state_off

        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}

// LED的Off状态
static QState state_off(sm_led_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:
            for (uint8_t i = 0; i < Device_Led_Max; i ++)
            {
                led_set_status(i, LedStatus_Off);
            }
            me->status = 0;
            return Q_HANDLED();

        case Q_EXIT_SIG:
            return Q_HANDLED();

        case Evt_LedOnOff:
            return Q_TRAN(&state_on);

        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}
