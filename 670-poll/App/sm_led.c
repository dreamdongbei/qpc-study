#include "sm_led.h"
#include "bsp.h"
#include "led.h"

void sm_led_init(sm_led_t *sm, uint8_t led_id, uint32_t frequecy)
{
    sm->led_id = led_id;
    sm->frequecy = frequecy;
    sm->status = false;
    
    sm->systime_bkp = system_time();
}

void sm_led_poll(sm_led_t *sm, uint32_t time_unit_ms)
{
    if ((system_time() - sm->systime_bkp) >= time_unit_ms)
    {
        sm->systime_bkp = system_time();
        
        uint32_t peroid = 1000 / sm->frequecy;

        if ((system_time() % (peroid / 2)) == 0)
        {
            sm->status = !sm->status;
            led_set_status(sm->led_id, sm->status);
        }
    }
}
