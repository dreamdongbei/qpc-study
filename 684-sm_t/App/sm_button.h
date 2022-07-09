#ifndef SM_BUTTON_H
#define SM_BUTTON_H

#include <stdint.h>
#include "button.h"
#include "sm.h"
#include "button_evt.h"

#define SM_BUTTON_CLICK_TIME_PRESS                  200
#define SM_BUTTON_CLICK_TIME_RELEASE                300
#define SM_BUTTON_LONG_PRESS_TIME_PRESS             1000

typedef struct sm_button
{
    sm_t super;

    uint8_t button_id;
    bool status_bkp;

    uint32_t time_press;
    uint32_t time_release;

    // For testing
    uint32_t count_click;
    uint32_t count_double_click;
    uint32_t count_long_press;
    
    uint8_t e_queue[32];

    button_evt_t button_evt;
} sm_button_t;

void sm_button_init(sm_button_t *sm, uint8_t button_id);

#endif
