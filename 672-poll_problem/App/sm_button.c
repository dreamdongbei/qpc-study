
#include "sm_button.h"
#include "button.h"
#include "bsp.h"

static void sm_button_poll(object_t *me);

void sm_button_init(sm_button_t *sm, uint8_t button_id)
{
    obj_register(&sm->super, sm_button_poll, 5);

    sm->state = ButtonState_Idle;
    sm->button_id = button_id;

    sm->count_click = 0;
    sm->count_double_click = 0;
    sm->count_long_press = 0;
}

static void sm_button_poll(object_t *me)
{
    sm_button_t *sm = (sm_button_t *)me;
    
    switch (sm->state)
    {
    case ButtonState_Idle:
        if (button_is_pressed(sm->button_id) == true)
        {
            sm->state = ButtonState_Click;
            sm->time_press = system_time();
        }
        break;

    case ButtonState_Click:
        if (button_is_pressed(sm->button_id) == false)
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
        else
        {
            if ((system_time() - sm->time_press) > SM_BUTTON_LONG_PRESS_TIME_PRESS)
            {
                sm->state = ButtonState_LongPress;
            }
        }
        break;

    case ButtonState_Release:
        if (button_is_pressed(sm->button_id) == true)
        {
            sm->state = ButtonState_DoubleClick;
        }
        else
        {
            if ((system_time() - sm->time_release) > SM_BUTTON_CLICK_TIME_RELEASE)
            {
                sm->state = ButtonState_Idle;
                sm->count_click ++;
            }
        }
        break;

    case ButtonState_DoubleClick:
        if (button_is_pressed(sm->button_id) == false)
        {
            sm->state = ButtonState_Idle;
            sm->count_double_click ++;
        }
        break;

    case ButtonState_LongPress:
        if (button_is_pressed(sm->button_id) == false)
        {
            sm->state = ButtonState_Idle;
            sm->count_long_press ++;
        }
        break;

    default:
        break;
    }
}
