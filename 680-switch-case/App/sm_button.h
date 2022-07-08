#ifndef SM_BUTTON_H
#define SM_BUTTON_H

#include <stdint.h>
#include "button.h"

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
    uint8_t state;
    uint8_t button_id;

    uint32_t time_press;
    uint32_t time_release;

    // For testing
    uint32_t count_click;
    uint32_t count_double_click;
    uint32_t count_long_press;
} sm_button_t;

void sm_button_init(sm_button_t *sm, uint8_t button_id);
void sm_button_poll(sm_button_t *sm);

#endif
