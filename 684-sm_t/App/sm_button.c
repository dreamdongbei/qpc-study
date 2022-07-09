
#include "sm_button.h"
#include "button.h"
#include "bsp.h"

static void button_state_idle(sm_button_t *me, uint8_t e_topic);
static void button_state_click(sm_button_t *me, uint8_t e_topic);
static void button_state_release(sm_button_t *me, uint8_t e_topic);
static void button_state_double_click(sm_button_t *me, uint8_t e_topic);
static void button_state_long_press(sm_button_t *me, uint8_t e_topic);

void sm_button_init(sm_button_t *sm, uint8_t button_id)
{
    sm->button_id = button_id;

    sm->count_click = 0;
    sm->count_double_click = 0;
    sm->count_long_press = 0;

    sm->status_bkp = button_is_pressed(sm->button_id);
    
    sm_init(&sm->super, sm->e_queue, 32, (func_state_t)button_state_idle);
    button_evt_init(&sm->button_evt, sm->button_id, &sm->super);
}

static void button_state_idle(sm_button_t *me, uint8_t e_topic)
{
    switch (e_topic)
    {
        case Evt_Entry:
            break;

        case Evt_Exit:
            break;

        case ButtonEvt_Press:
            SM_TRAN(button_state_click);
            me->time_press = system_time();
            break;

        default:
            break;
    }
}

static void button_state_click(sm_button_t *me, uint8_t e_topic)
{
    switch (e_topic)
    {
        case ButtonEvt_Release:
            me->time_release = system_time();
            if ((system_time() - me->time_press) < SM_BUTTON_CLICK_TIME_PRESS)
            {
                SM_TRAN(button_state_release);
            }
            else
            {
                me->count_click ++;
                SM_TRAN(button_state_idle);
            }
            break;

        case ButtonEvt_Poll:
            if ((system_time() - me->time_press) > SM_BUTTON_LONG_PRESS_TIME_PRESS)
            {
                SM_TRAN(button_state_long_press);
            }
            break;

        default:
            break;
    }
}

static void button_state_release(sm_button_t *me, uint8_t e_topic)
{
    switch (e_topic)
    {
        case ButtonEvt_Press:
            SM_TRAN(button_state_double_click);
            break;

        case ButtonEvt_Poll:
            if ((system_time() - me->time_release) > SM_BUTTON_CLICK_TIME_RELEASE)
            {
                SM_TRAN(button_state_idle);
                me->count_click ++;
            }
            break;

        default:
            break;
    }
}

static void button_state_double_click(sm_button_t *me, uint8_t e_topic)
{
    switch (e_topic)
    {
        case ButtonEvt_Release:
            SM_TRAN(button_state_idle);
            me->count_double_click ++;
            break;

        default:
            break;
    }
}

static void button_state_long_press(sm_button_t *me, uint8_t e_topic)
{
    switch (e_topic)
    {
        case ButtonEvt_Release:
            SM_TRAN(button_state_idle);
            me->count_long_press ++;
            break;

        default:
            break;
    }
}
