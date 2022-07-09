
#include "sm_button.h"
#include "button.h"
#include "bsp.h"

static void button_state_idle(sm_button_t *me, uint8_t e_topic);
static void button_state_click(sm_button_t *me, uint8_t e_topic);
static void button_state_release(sm_button_t *me, uint8_t e_topic);
static void button_state_double_click(sm_button_t *me, uint8_t e_topic);
static void button_state_long_press(sm_button_t *me, uint8_t e_topic);

static void sm_button_poll(object_t *me);

enum
{
    ButtonEvt_Null = 0,
    ButtonEvt_Press,
    ButtonEvt_Release,
    ButtonEvt_Poll,
};

void sm_button_init(sm_button_t *sm, uint8_t button_id)
{
    obj_register(&sm->super, sm_button_poll, 10);

    sm->state = button_state_idle;
    sm->button_id = button_id;

    sm->count_click = 0;
    sm->count_double_click = 0;
    sm->count_long_press = 0;

    sm->status_bkp = button_is_pressed(sm->button_id);
}

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

    e_queue[count ++] = ButtonEvt_Poll;

    for (uint8_t i = 0; i < count; i ++)
        sm->state(sm, e_queue[i]);
}

static void button_state_idle(sm_button_t *me, uint8_t e_topic)
{
    switch (e_topic)
    {
        case ButtonEvt_Press:
            me->state = button_state_click;
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
                me->state = button_state_release;
            }
            else
            {
                me->state = button_state_idle;
                me->count_click ++;
            }
            break;

        case ButtonEvt_Poll:
            if ((system_time() - me->time_press) > SM_BUTTON_LONG_PRESS_TIME_PRESS)
            {
                me->state = button_state_long_press;
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
            me->state = button_state_double_click;
            break;

        case ButtonEvt_Poll:
            if ((system_time() - me->time_release) > SM_BUTTON_CLICK_TIME_RELEASE)
            {
                me->state = button_state_idle;
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
            me->state = button_state_idle;
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
            me->state = button_state_idle;
            me->count_long_press ++;
            break;

        default:
            break;
    }
}
