#include "bsp.h"
#include "led.h"
#include "gd32f3x0.h"

led_t led;

int main(void)
{
    bsp_init();
    led.init(GPIOC, GPIO_PIN_10);
    
    while (1)
    {
        if ((system_time() % 1000) <= 500)
        {
            led.set_status(true);
        }
        else
        {
            led.set_status(false);
        }
    }
}
