#ifndef BUTTON_EVT_H
#define BUTTON_EVT_H

#include "poll.h"
#include "sm.h"
#include <stdbool.h>

enum
{
    ButtonEvt_Press = Evt_User,
    ButtonEvt_Release,
    ButtonEvt_Poll,
};

typedef struct button_evt
{
    object_t super;
    uint8_t button_id;
    bool status_bkp;
    sm_t *sm;
} button_evt_t;

void button_evt_init(button_evt_t *me, uint8_t button_id, sm_t *sm);

#endif
