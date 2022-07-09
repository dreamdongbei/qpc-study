
#include "sm_button.h"
#include "button.h"
#include "bsp.h"

static void sm_button_poll(object_t *me);
static void sm_button_event(sm_button_t *sm, uint8_t e_sig);

void sm_button_init(sm_button_t *sm, uint8_t button_id)
{
    obj_register(&sm->super, sm_button_poll, 10);

    sm->state = ButtonState_Idle;
    sm->button_id = button_id;

    sm->count_click = 0;
    sm->count_double_click = 0;
    sm->count_long_press = 0;

    sm->status_bkp = button_is_pressed(sm->button_id);
}

enum
{
    ButtonEvt_Null = 0,
    ButtonEvt_Press,
    ButtonEvt_Release,
    ButtonEvt_10ms,
};

static void sm_button_poll(object_t *me)
{
    sm_button_t *sm = (sm_button_t *)me;

    // Button Poll
    bool status = button_is_pressed(sm->button_id);

    // Button event
    uint8_t e_queue[4];
    uint8_t count = 0;
    if (status != sm->status_bkp)
    {
        if (status == true)
        {
            e_queue[count ++] = ButtonEvt_Press;
        }
        else
        {
            e_queue[count ++] = ButtonEvt_Release;
        }
        sm->status_bkp = status;
    }
    
    e_queue[count ++] = ButtonEvt_10ms;

    // Event handling
    for (uint8_t i = 0; i < count; i ++)
    {
        sm_button_event(sm, e_queue[i]);
    }
}

static void sm_button_event(sm_button_t *sm, uint8_t e_topic)
{
    switch (sm->state)
    {
    case ButtonState_Idle:
        if (e_topic == ButtonEvt_Press)
        {
            sm->state = ButtonState_Click;
            sm->time_press = system_time();
        }
        break;

    case ButtonState_Click:
        if (e_topic == ButtonEvt_Release)
        {
            sm->time_release = system_time();
            if ((system_time() - sm->time_press) < SM_BUTTON_CLICK_TIME_PRESS)
            {
                sm->state = ButtonState_Release;
            }
            else
            {
                sm->state = ButtonState_Idle;
                sm->count_click ++;
            }
        }
        
        if (e_topic == ButtonEvt_10ms)
        {
            if ((system_time() - sm->time_press) > SM_BUTTON_LONG_PRESS_TIME_PRESS)
            {
                sm->state = ButtonState_LongPress;
            }
        }
        break;

    case ButtonState_Release:
        if (e_topic == ButtonEvt_Press)
        {
            sm->state = ButtonState_DoubleClick;
        }

        if (e_topic == ButtonEvt_10ms)
        {
            if ((system_time() - sm->time_release) > SM_BUTTON_CLICK_TIME_RELEASE)
            {
                sm->state = ButtonState_Idle;
                sm->count_click ++;
            }
        }
        break;

    case ButtonState_DoubleClick:
        if (e_topic == ButtonEvt_Release)
        {
            sm->state = ButtonState_Idle;
            sm->count_double_click ++;
        }
        break;

    case ButtonState_LongPress:
        if (e_topic == ButtonEvt_Release)
        {
            sm->state = ButtonState_Idle;
            sm->count_long_press ++;
        }
        break;

    default:
        break;
    }
}
