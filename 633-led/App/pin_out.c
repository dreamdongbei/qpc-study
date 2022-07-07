
#include "pin_out.h"
#include "gd32f3x0.h"

typedef struct pin_hw_info
{
    rcu_periph_enum clock;
    uint32_t port;
} pin_hw_info_t;

static const pin_hw_info_t hw_info[] =
{
    { RCU_GPIOA, GPIOA },
    { RCU_GPIOB, GPIOB },
    { RCU_GPIOC, GPIOC },
    { RCU_GPIOD, GPIOD },
    { RCU_GPIOF, GPIOF },
};

void pin_out_init(pin_out_t *me, uint32_t port, uint32_t pin)
{
    rcu_periph_enum clock = RCU_DMA;
    for (uint8_t i = 0; i < sizeof(hw_info) / sizeof(pin_hw_info_t); i ++)
    {
        if (port == hw_info[i].port)
        {
            clock = hw_info[i].clock;
        }
    }

    me->port = port;
    me->pin = pin;

    /* enable the LED GPIO clock. */
    rcu_periph_clock_enable(clock);
    /* configure led GPIO port. */
    gpio_mode_set(me->port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, me->pin);
    gpio_output_options_set(me->port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, me->pin);
    /* Off the led. */
    gpio_bit_reset(me->port, me->pin);
}

void pin_out_set_status(pin_out_t *me, bool status)
{
    gpio_bit_write(me->port, me->pin, (status != false ? SET : RESET));
}
