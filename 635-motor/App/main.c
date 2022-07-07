#include "bsp.h"
#include "led.h"
#include "motor.h"
#include "gd32f3x0.h"

led_t led1;
led_t led2;
led_t led3;
led_t led4;

pin_aout_t aout_speed;
pin_out_t out_enable;
pin_out_t out_direction;
pin_in_t in_err;

motor_t motor;

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
    
    pin_in_init(&in_err, GPIOB, GPIO_PIN_1);
    pin_out_init(&out_enable, GPIOC, GPIO_PIN_3);
    pin_out_init(&out_direction, GPIOC, GPIO_PIN_4);
    pin_aout_init(&aout_speed, GPIOC, GPIO_PIN_5, 10);
    
    motor_init(&motor, &aout_speed, &out_enable, &out_direction, &in_err);
    
    while (1)
    {
        led_poll(&led1);
        led_poll(&led2);
        led_poll(&led3);
        led_poll(&led4);
        
        motor_poll(&motor);
    }
}
