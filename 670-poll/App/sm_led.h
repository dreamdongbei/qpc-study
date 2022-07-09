#ifndef SM_LED_H
#define SM_LED_H

#include <stdint.h>
#include <stdbool.h>
#include "led.h"

typedef struct sm_led
{
    uint32_t frequecy;
    uint8_t led_id;
    bool status;
    
    uint32_t systime_bkp;
} sm_led_t;

void sm_led_init(sm_led_t *sm, uint8_t led_id, uint32_t frequecy);
void sm_led_poll(sm_led_t *sm, uint32_t time_unit_ms);

#endif
