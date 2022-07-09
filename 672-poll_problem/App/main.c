#include "bsp.h"
#include "button.h"
#include "led.h"
#include "sm_button.h"
#include "sm_led.h"
#include "algorithm.h"

sm_button_t sm_button;

static uint32_t led_frequecy[Device_Led_Max] =
{
    1, 2, 4, 10
};
sm_led_t sm_led[Device_Led_Max];

int main(void)
{
    bsp_init();
    button_init();
    led_init();

    for (uint32_t i = 0; i < Device_Led_Max; i ++)
    {
        sm_led_init(&sm_led[i], i, led_frequecy[i]);
    }
    sm_button_init(&sm_button, ButtonId_UserKey);
    algorithm_init();
    
    while (1)
    {
        obj_poll();
    }
}
