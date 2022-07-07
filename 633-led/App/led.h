#ifndef LED_H
#define LED_H

#include "pin_out.h"

typedef struct led
{
    pin_out_t super;

    uint32_t frequency;
} led_t;

void led_twinkle(led_t *me, uint32_t frequency);
void led_poll(led_t *me);

#endif
