#ifndef SM_BUTTON_H
#define SM_BUTTON_H

#include "qpc.h"
#include <stdbool.h>

#define SM_BUTTON_CLICK_TIME_PRESS                  200
#define SM_BUTTON_CLICK_TIME_RELEASE                300
#define SM_BUTTON_LONG_PRESS_TIME_PRESS             1000

typedef struct sm_button
{
    QActive super;
    QTimeEvt event_poll;
    QTimeEvt event_time_count;

    uint8_t button_id;
    bool status;
    bool status_bkp;

    uint32_t time_press;
    uint32_t time_release;
} sm_button_t;

enum button_action
{
    ButtonAction_Click = 0,
    ButtonAction_DoubleClick,
    ButtonAction_LongPress,
};

typedef struct button_event
{
    QEvt super;
    uint8_t id;
    uint8_t action;
} button_event_t;

void sm_button_init(sm_button_t *me,
                    uint8_t button_id,
                    uint8_t priority,
                    QEvt const **event_queue, uint32_t equeue_size);

#endif
