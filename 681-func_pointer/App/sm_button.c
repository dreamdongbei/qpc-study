
#include "sm_button.h"
#include "button.h"
#include "bsp.h"

static void button_state_idle(sm_button_t *me);
static void button_state_click(sm_button_t *me);
static void button_state_release(sm_button_t *me);
static void button_state_double_click(sm_button_t *me);
static void button_state_long_press(sm_button_t *me);

void sm_button_init(sm_button_t *sm, uint8_t button_id)
{
    sm->state = button_state_idle;
    sm->button_id = button_id;

    sm->count_click = 0;
    sm->count_double_click = 0;
    sm->count_long_press = 0;
}

void sm_button_poll(sm_button_t *sm)
{
    sm->state(sm);
}

static void button_state_idle(sm_button_t *me)
{
    if (button_is_pressed(me->button_id) == true)
    {
        me->state = button_state_click;
        me->time_press = system_time();
    }
}

static void button_state_click(sm_button_t *me)
{
    if (button_is_pressed(me->button_id) == false)
    {
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
    }
    else
    {
        if ((system_time() - me->time_press) > SM_BUTTON_LONG_PRESS_TIME_PRESS)
        {
            me->state = button_state_long_press;
        }
    }
}

static void button_state_release(sm_button_t *me)
{
    if (button_is_pressed(me->button_id) == true)
    {
        me->state = button_state_double_click;
    }
    else
    {
        if ((system_time() - me->time_release) > SM_BUTTON_CLICK_TIME_RELEASE)
        {
            me->state = button_state_idle;
            me->count_click ++;
        }
    }
}

static void button_state_double_click(sm_button_t *me)
{
    if (button_is_pressed(me->button_id) == false)
    {
        me->state = button_state_idle;
        me->count_double_click ++;
    }
}

static void button_state_long_press(sm_button_t *me)
{
    if (button_is_pressed(me->button_id) == false)
    {
        me->state = button_state_idle;
        me->count_long_press ++;
    }
}
