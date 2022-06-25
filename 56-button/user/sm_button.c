#include "sm_button.h"
#include "led.h"
#include "qpc.h"
#include "event_def.h"
#include "sm_def.h"
#include "button.h"
#include "bsp.h"

Q_DEFINE_THIS_MODULE("SmButton")

static QState state_init(sm_button_t * const me, void const * const par);
static QState state_work(sm_button_t * const me, QEvt const * const e);
    static QState work_idle(sm_button_t * const me, QEvt const * const e);
    static QState work_click(sm_button_t * const me, QEvt const * const e);
    static QState work_release(sm_button_t * const me, QEvt const * const e);
    static QState work_double_click(sm_button_t * const me, QEvt const * const e);
    static QState work_long_press(sm_button_t * const me, QEvt const * const e);

void sm_button_init(sm_button_t *me,
                    uint8_t button_id,
                    uint8_t priority,
                    QEvt const **event_queue, uint32_t equeue_size)
{
    me->button_id = button_id;
    me->status = false;
    me->status_bkp = false;

    // 时间事件的构建
    QTimeEvt_ctorX(&me->event_poll, &me->super, Evt_Button_Poll, 0U);
    QTimeEvt_ctorX(&me->event_time_count, &me->super, Evt_Button_TimeCount, 0U);
    
    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    QACTIVE_START(&me->super,
                  priority,
                  event_queue, equeue_size,
                  (void *)0, 0U,
                  (void *)0);
}

// 状态函数的实现 ---------------------------------------------------------------
// 初始状态
static QState state_init(sm_button_t * const me, void const * const par)
{
    QTimeEvt_armX(&me->event_poll, 1, 1);
    QTimeEvt_armX(&me->event_time_count, 1, 1);
    
    return Q_TRAN(&state_work);
}

static QState state_work(sm_button_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Button_Poll:
            // 读取状态
            me->status = button_is_pressed(me->button_id);
            if (me->status == true && me->status_bkp == false)
            {
                QEvt *e = Q_NEW(QEvt, Evt_Button_Pressed);
                QACTIVE_POST(&me->super, e, me);
            }
            else if (me->status == false && me->status_bkp == true)
            {
                QEvt *e = Q_NEW(QEvt, Evt_Button_Released);
                QACTIVE_POST(&me->super, e, me);
            }
            me->status_bkp = me->status;
            return Q_HANDLED();

        case Q_INIT_SIG:
            return Q_TRAN(&work_idle);

        default:
            return Q_SUPER(&QHsm_top);
    }
}

static QState work_idle(sm_button_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Button_Pressed:
            me->time_press = system_time();
            return Q_TRAN(&work_click);

        default:
            return Q_SUPER(&state_work);
    }
}

static QState work_click(sm_button_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Button_TimeCount:
            if ((system_time() - me->time_press) >= SM_BUTTON_LONG_PRESS_TIME_PRESS)
            {
                return Q_TRAN(&work_long_press);
            }
            return Q_HANDLED();

        case Evt_Button_Released:
        {
            if ((system_time() - me->time_press) <= SM_BUTTON_CLICK_TIME_PRESS)
            {
                me->time_release = system_time();
                return Q_TRAN(&work_release);
            }
            else
            {
                return Q_TRAN(&work_idle);
            }
        }

        default:
            return Q_SUPER(&state_work);
    }
}

static QState work_release(sm_button_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Button_Pressed:
            me->time_press = system_time();
            return Q_TRAN(&work_double_click);

        case Evt_Button_TimeCount:
            if ((system_time() - me->time_release) >= SM_BUTTON_CLICK_TIME_RELEASE)
            {
                return Q_TRAN(&work_idle);
            }
            return Q_HANDLED();

        default:
            return Q_SUPER(&state_work);
    }
}

static QState work_double_click(sm_button_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Button_Released:
        {
            if ((system_time() - me->time_press) <= SM_BUTTON_CLICK_TIME_RELEASE)
            {
                return Q_TRAN(&work_release);
            }
            else
            {
                return Q_TRAN(&work_idle);
            }
        }

        default:
            return Q_SUPER(&state_work);
    }
}

static QState work_long_press(sm_button_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Button_Released:
        {
            QEvt *e = (QEvt *)Q_NEW(button_event_t, Evt_Button);
            QF_PUBLISH(e, me);

            return Q_TRAN(&work_idle);
        }

        default:
            return Q_SUPER(&state_work);
    }
}
