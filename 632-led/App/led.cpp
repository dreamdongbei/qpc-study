#include "led.h"
#include "bsp.h"

void led_t::twinkle(uint32_t frequency)
{
    this->frequency = frequency;
}

void led_t::poll(void)
{
    uint32_t period = 1000 / frequency;
    bool status = (system_time() % period) <= (period / 2) ? true : false;
    set_status(status);
}
