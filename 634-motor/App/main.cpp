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

    led1.init(GPIOC, GPIO_PIN_10);
    led2.init(GPIOC, GPIO_PIN_11);
    led3.init(GPIOC, GPIO_PIN_12);
    led4.init(GPIOC, GPIO_PIN_2);
    
    led1.twinkle(1);                    // 1Hz
    led2.twinkle(5);                    // 5Hz
    led3.twinkle(10);                   // 10Hz
    led4.twinkle(20);                   // 20Hz
    
    in_err.init(GPIOB, GPIO_PIN_1);
    out_enable.init(GPIOC, GPIO_PIN_3);
    out_direction.init(GPIOC, GPIO_PIN_4);
    aout_speed.init(GPIOC, GPIO_PIN_5, 10);
    
    motor.init(&aout_speed, &out_enable, &out_direction, &in_err);

    while (1)
    {
        led1.poll();
        led2.poll();
        led3.poll();
        led4.poll();
        
        motor.poll();
    }
}
