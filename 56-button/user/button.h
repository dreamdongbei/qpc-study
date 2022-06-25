#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>
#include "qpc.h"

#define BUTTON_TIME_DE_JITTER                       (15)

enum
{
    ButtonId_WakeUp = 0,
    ButtonId_UserKey,
    ButtonId_Tamper,

    ButtonId_Max
};

void button_init(void);
bool button_is_pressed(uint8_t button_id);

#endif
