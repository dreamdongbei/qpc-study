#include "led.h"
#include "gd32f3x0.h"

typedef struct led_hw_info
{
    rcu_periph_enum clock;
    uint32_t port;
    uint32_t pin;
} led_hw_info_t;

static const led_hw_info_t hw_info[Device_Led_Max] =
{
    { RCU_GPIOC, GPIOC, GPIO_PIN_10 },
    { RCU_GPIOC, GPIOC, GPIO_PIN_11 },
    { RCU_GPIOC, GPIOC, GPIO_PIN_12 },
    { RCU_GPIOC, GPIOC, GPIO_PIN_2 },
};

void led_init(void)
{
    for (uint32_t i = 0; i < Device_Led_Max; i ++)
    {
        /* enable the LED GPIO clock. */
        rcu_periph_clock_enable(hw_info[i].clock);
        /* configure led GPIO port. */
        gpio_mode_set(hw_info[i].port,
                      GPIO_MODE_OUTPUT,
                      GPIO_PUPD_NONE,
                      hw_info[i].pin);
        gpio_output_options_set(hw_info[i].port,
                                GPIO_OTYPE_PP,
                                GPIO_OSPEED_50MHZ,
                                hw_info[i].pin);
        /* Off the led. */
        gpio_bit_reset(hw_info[i].port, hw_info[i].pin);
    }
}

void led_set_status(uint8_t device_led_id, uint8_t status)
{
    uint8_t i = device_led_id;
    gpio_bit_write(hw_info[i].port, hw_info[i].pin, (status != 0 ? SET : RESET));
}
