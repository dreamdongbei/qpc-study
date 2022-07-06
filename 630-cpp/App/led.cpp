
#include "led.h"
#include "gd32f3x0.h"

typedef struct led_hw_info
{
    rcu_periph_enum clock;
    uint32_t port;
} led_hw_info_t;

static const led_hw_info_t hw_info[] =
{
    { RCU_GPIOA, GPIOA },
    { RCU_GPIOB, GPIOB },
    { RCU_GPIOC, GPIOC },
    { RCU_GPIOD, GPIOD },
    { RCU_GPIOF, GPIOF },
};

void led_t::init(uint32_t port, uint32_t pin)
{
    rcu_periph_enum clock = RCU_DMA;
    for (uint8_t i = 0; i < sizeof(hw_info) / sizeof(led_hw_info_t); i ++)
    {
        if (port == hw_info[i].port)
        {
            clock = hw_info[i].clock;
        }
    }

    this->port_ = port;
    this->pin_ = pin;

    /* enable the LED GPIO clock. */
    rcu_periph_clock_enable(clock);
    /* configure led GPIO port. */
    gpio_mode_set(port_, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin_);
    gpio_output_options_set(port_, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, pin_);
    /* Off the led. */
    gpio_bit_reset(port_, pin_);
}

void led_t::set_status(bool status)
{
    gpio_bit_write(this->port_, this->pin_, (status != false ? SET : RESET));
}
