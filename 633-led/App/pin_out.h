#ifndef PIN_OUT_H
#define PIN_OUT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct pin_out
{
    uint32_t port;
    uint32_t pin;
} pin_out_t;

void pin_out_init(pin_out_t *me, uint32_t port, uint32_t pin);
void pin_out_set_status(pin_out_t *me, bool status);

#endif
