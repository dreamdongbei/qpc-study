#ifndef PIN_AOUT_H
#define PIN_AOUT_H

#include "stdint.h"

typedef struct pin_aout
{
    uint32_t port;
    uint32_t pin;
    uint32_t scale;
} pin_aout_t;

void pin_aout_init(pin_aout_t *me, uint32_t port, uint32_t pin, uint32_t scale);
void pin_aout_set_value(pin_aout_t *me, uint32_t mv);

#endif
