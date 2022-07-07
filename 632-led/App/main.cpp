#include "bsp.h"
#include "led.h"
#include "gd32f3x0.h"

led_t led1;
led_t led2;
led_t led3;
led_t led4;

int main(void)
{
    bsp_init();

    led1.init(GPIOC, GPIO_PIN_10);
    led2.init(GPIOC, GPIO_PIN_11);
    led3.init(GPIOC, GPIO_PIN_12);
    led4.init(GPIOC, GPIO_PIN_2);
    
    led1.twinkle(1);                    // 1Hz
    led2.twinkle(5);                    // 5Hz
    led3.twinkle(10);                   // 10Hz
    led4.twinkle(20);                   // 20Hz

    while (1)
    {
        led1.poll();
        led2.poll();
        led3.poll();
        led4.poll();
    }
}
