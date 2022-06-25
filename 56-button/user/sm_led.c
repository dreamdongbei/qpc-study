#include "sm_led.h"
#include "led.h"
#include "qpc.h"
#include "event_def.h"
#include "sm_def.h"

Q_DEFINE_THIS_MODULE("SmLed")

// LED类的定义
typedef struct sm_led_tag
{
    QActive super;                                      // 对QActive类的继承
    QTimeEvt time_event[Device_Led_Max];
    
    bool status[Device_Led_Max];
} sm_led_t;

static QState state_init(sm_led_t * const me, void const * const par);
static QState state_work(sm_led_t * const me, QEvt const * const e);

static sm_led_t sm_led;

void sm_led_init(void)
{
    sm_led_t *me = &sm_led;
    
    // 时间事件的构建
    static const uint32_t event_table[Device_Led_Max] =
    {
        Evt_Led1_OnOff, Evt_Led2_OnOff, Evt_Led3_OnOff, Evt_Led4_OnOff
    };
    for (uint8_t i = 0; i < Device_Led_Max; i ++)
    {
        QTimeEvt_ctorX(&me->time_event[i], &me->super, event_table[i], 0U);
    }
    
    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    static QEvt const *e_queue[SM_LED_QUEUE_LENGTH];
    QACTIVE_START(&me->super,
                  SmPrio_Led,
                  e_queue, SM_LED_QUEUE_LENGTH,
                  (void *)0, 0U,
                  (void *)0);
}

// 状态函数的实现 ---------------------------------------------------------------
// 初始状态
static QState state_init(sm_led_t * const me, void const * const par)
{
    led_init();
    
    static const uint32_t time_period[Device_Led_Max] =
    {
        500, 200, 100, 50,
    };
    for (uint8_t i = 0; i < Device_Led_Max; i ++)
    {
        QTimeEvt_armX(&me->time_event[i], time_period[i], time_period[i]);
    }
    
    return Q_TRAN(&state_work);
}

// LED的on状态
static QState state_work(sm_led_t * const me, QEvt const * const e)
{
    switch (e->sig) {
        case Q_ENTRY_SIG:                           // 状态的进入事件

            return Q_HANDLED();                     // 通知框架，事件已处理

        case Q_EXIT_SIG:
            return Q_HANDLED();

        case Evt_Led1_OnOff:
            led_set_status(Device_Led1, me->status[Device_Led1]);
            me->status[Device_Led1] = !me->status[Device_Led1];
            return Q_HANDLED();
        
        case Evt_Led2_OnOff:
            led_set_status(Device_Led2, me->status[Device_Led2]);
            me->status[Device_Led2] = !me->status[Device_Led2];
            return Q_HANDLED();
        
        case Evt_Led3_OnOff:
            led_set_status(Device_Led3, me->status[Device_Led3]);
            me->status[Device_Led3] = !me->status[Device_Led3];
            return Q_HANDLED();
        
        case Evt_Led4_OnOff:
            led_set_status(Device_Led4, me->status[Device_Led4]);
            me->status[Device_Led4] = !me->status[Device_Led4];
            return Q_HANDLED();

        default:
            return Q_SUPER(&QHsm_top);              // 其他事件，在此时不处理
    }
}
