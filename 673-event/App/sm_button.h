#ifndef SM_BUTTON_H
#define SM_BUTTON_H

#include <stdint.h>
#include <stdbool.h>
#include "button.h"
#include "poll.h"

#define SM_BUTTON_CLICK_TIME_PRESS                  200
#define SM_BUTTON_CLICK_TIME_RELEASE                300
#define SM_BUTTON_LONG_PRESS_TIME_PRESS             1000

enum button_state
{
    ButtonState_Idle = 0,
    ButtonState_Click,
    ButtonState_Release,
    ButtonState_DoubleClick,
    ButtonState_LongPress,
};

typedef struct sm_button
{
    object_t super;

    uint8_t state;
    uint8_t button_id;
    bool status_bkp;

    uint32_t time_press;
    uint32_t time_release;

    // For testing
    uint32_t count_click;
    uint32_t count_double_click;
    uint32_t count_long_press;
} sm_button_t;

void sm_button_init(sm_button_t *sm, uint8_t button_id);

#endif
