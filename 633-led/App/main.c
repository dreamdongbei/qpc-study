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

    pin_out_init(&led1.super, GPIOC, GPIO_PIN_10);
    pin_out_init(&led2.super, GPIOC, GPIO_PIN_11);
    pin_out_init(&led3.super, GPIOC, GPIO_PIN_12);
    pin_out_init(&led4.super, GPIOC, GPIO_PIN_2);

    led_twinkle(&led1, 1);                      // 1Hz
    led_twinkle(&led2, 5);                      // 5Hz
    led_twinkle(&led3, 10);                     // 10Hz
    led_twinkle(&led4, 20);                     // 20Hz
    
    while (1)
    {
        led_poll(&led1);
        led_poll(&led2);
        led_poll(&led3);
        led_poll(&led4);
    }
}
