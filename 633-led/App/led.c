#include "led.h"
#include "bsp.h"

void led_twinkle(led_t *me, uint32_t frequency)
{
    me->frequency = frequency;
}

void led_poll(led_t *me)
{
    uint32_t period = 1000 / me->frequency;
    bool status = (system_time() % period) <= (period / 2) ? true : false;
    pin_out_set_status((pin_out_t *)me, status);
}
