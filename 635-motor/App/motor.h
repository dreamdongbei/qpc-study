#ifndef MOTOR_H
#define MOTOR_H

#include "pin_aout.h"
#include "pin_out.h"
#include "pin_in.h"

typedef struct motor
{
    pin_aout_t *aout_speed;
    pin_out_t *out_enable;
    pin_out_t *out_direction;
    pin_in_t *in_err;

    bool enabled;
    uint8_t err_id;
} motor_t;

void motor_init(motor_t *me,
                pin_aout_t *speed,
                pin_out_t *enable,
                pin_out_t *direction,
                pin_in_t *err);
void motor_enable(motor_t *me, bool status);
void motor_set_speed(motor_t *me, int32_t speed);
uint8_t motor_error_id(motor_t *me);
void motor_poll(motor_t *me);

#endif
