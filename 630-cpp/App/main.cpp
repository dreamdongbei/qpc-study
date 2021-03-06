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

    led1.init(GPIOC, GPIO_PIN_10);
    led2.init(GPIOC, GPIO_PIN_11);
    led3.init(GPIOC, GPIO_PIN_12);
    led4.init(GPIOC, GPIO_PIN_2);
    
    bool status;
    while (1)
    {
        // 1Hz
        status = (system_time() % 1000) <= 500 ? true : false;
        led1.set_status(status);

        // 5Hz
        status = (system_time() % 200) <= 100 ? true : false;
        led2.set_status(status);

        // 10Hz
        status = (system_time() % 100) <= 50 ? true : false;
        led3.set_status(status);

        // 20Hz
        status = (system_time() % 50) <= 25 ? true : false;
        led4.set_status(status);
    }
}
