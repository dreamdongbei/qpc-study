#ifndef SM_LED_H
#define SM_LED_H

#include <stdint.h>
#include <stdbool.h>
#include "led.h"
#include "poll.h"

typedef struct sm_led
{
    object_t super;

    uint8_t led_id;
    bool status;
} sm_led_t;

void sm_led_init(sm_led_t *sm, uint8_t led_id, uint32_t frequecy);

#endif
