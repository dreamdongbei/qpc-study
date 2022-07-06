#include "bsp.h"
#include "pin_out.h"
#include "gd32f3x0.h"

pin_out_t led1;
pin_out_t led2;
pin_out_t led3;
pin_out_t led4;

int main(void)
{
    bsp_init();

    pin_out_init(&led1, GPIOC, GPIO_PIN_10);
    pin_out_init(&led2, GPIOC, GPIO_PIN_11);
    pin_out_init(&led3, GPIOC, GPIO_PIN_12);
    pin_out_init(&led4, GPIOC, GPIO_PIN_2);
    
    bool status;
    while (1)
    {
        // 1Hz
        status = (system_time() % 1000) <= 500 ? true : false;
        pin_out_set_status(&led1, status);

        // 5Hz
        status = (system_time() % 200) <= 100 ? true : false;
        pin_out_set_status(&led2, status);

        // 10Hz
        status = (system_time() % 100) <= 50 ? true : false;
        pin_out_set_status(&led3, status);

        // 20Hz
        status = (system_time() % 50) <= 25 ? true : false;
        pin_out_set_status(&led4, status);
    }
}
