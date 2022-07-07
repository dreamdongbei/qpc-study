#include "motor.h"

void motor_init(motor_t *me,
                pin_aout_t *speed,
                pin_out_t *enable,
                pin_out_t *direction,
                pin_in_t *err)
{
    me->aout_speed = speed;
    me->out_enable = enable;
    me->out_direction = direction;
    me->in_err = err;

    pin_out_set_status(me->out_direction, false);
    pin_out_set_status(me->out_enable, false);
    pin_aout_set_value(me->aout_speed, 0);
}

void motor_enable(motor_t *me, bool status)
{
    me->enabled = status;
    pin_out_set_status(me->out_enable, me->enabled);

    if (me->enabled == false)
    {
        pin_aout_set_value(me->aout_speed, 0);
    }
}

void motor_set_speed(motor_t *me, int32_t speed)
{
    if (me->enabled == true)
    {
        if (speed >= 0)
        {
            pin_out_set_status(me->out_direction, true);
            pin_aout_set_value(me->aout_speed, speed);
        }
        else
        {
            pin_out_set_status(me->out_direction, false);
            pin_aout_set_value(me->aout_speed, -speed);
        }
    }
}

uint8_t motor_error_id(motor_t *me)
{
    return me->err_id;
}

void motor_poll(motor_t *me)
{
    (void)me;
}
