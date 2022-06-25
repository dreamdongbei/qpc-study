#ifndef DEV_LED_H
#define DEV_LED_H

#include <stdint.h>

#define LED_TWINKLE_INTERVAL_DEFAULT                (500)

typedef enum led_action
{
    DevLedAction_LongOff = 0,
    DevLedAction_LongOn,
    DevLedAction_Twinkle,
} led_action_t;

void dev_led_init(void);
void dev_led_poll(uint32_t time_unit);

void dev_led_set_action(uint8_t dev_led_id, uint8_t action);
void dev_led_twinkle(uint8_t dev_led_id, uint32_t interval);

#endif
