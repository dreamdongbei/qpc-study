#include "motor.h"

void motor_t::init(pin_aout_t *speed,
                    pin_out_t *enable,
                    pin_out_t *direction,
                    pin_in_t *err)
{
    aout_speed = speed;
    out_enable = enable;
    out_direction = direction;
    in_err = err;

    direction->set_status(false);
    out_enable->set_status(false);
    aout_speed->set_value(0);
}

void motor_t::enable(bool status)
{
    enabled = status;
    out_enable->set_status(enabled);

    if (enabled == false)
    {
        aout_speed->set_value(0);
    }
}

void motor_t::set_speed(int32_t speed)
{
    if (enabled == true)
    {
        if (speed >= 0)
        {
            out_direction->set_status(true);
            aout_speed->set_value(speed);
        }
        else
        {
            out_direction->set_status(false);
            aout_speed->set_value(-speed);
        }
    }
}

uint8_t motor_t::err_id(void)
{
    return error_id;
}

void motor_t::poll(void)
{

}
