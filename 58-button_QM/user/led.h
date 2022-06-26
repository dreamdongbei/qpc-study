#ifndef LED_H
#define LED_H

#include "led.h"
#include <stdint.h>

enum
{
    LedStatus_Off = 0,
    LedStatus_On = !LedStatus_Off,
};

enum
{
    Device_Led1 = 0,
    Device_Led2,
    Device_Led3,
    Device_Led4,

    Device_Led_Max
};

void led_init(void);
void led_set_status(uint8_t device_led_id, uint8_t status);

#endif
