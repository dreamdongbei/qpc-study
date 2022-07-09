#include "sm_led.h"
#include "bsp.h"
#include "led.h"

static void sm_led_poll(object_t *me);

void sm_led_init(sm_led_t *sm, uint8_t led_id, uint32_t frequecy)
{
    obj_register(&sm->super, sm_led_poll, (1000 / frequecy / 2));

    sm->led_id = led_id;
    sm->status = false;
}

static void sm_led_poll(object_t *me)
{
    sm_led_t *sm = (sm_led_t *)me;

    sm->status = !sm->status;
    led_set_status(sm->led_id, sm->status);
}
