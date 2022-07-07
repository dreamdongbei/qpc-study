#ifndef MOTOR_H
#define MOTOR_H

#include "pin_aout.h"
#include "pin_out.h"
#include "pin_in.h"

class motor_t
{
public:
    void init(pin_aout_t *speed,
              pin_out_t *enable,
              pin_out_t *direction,
              pin_in_t *err);
    void enable(bool status);
    void set_speed(int32_t speed);
    uint8_t err_id(void);
    void poll(void);

private:
    bool enabled;
    uint8_t error_id;

    pin_aout_t *aout_speed;
    pin_out_t *out_enable;
    pin_out_t *out_direction;
    pin_in_t *in_err;
};

#endif
