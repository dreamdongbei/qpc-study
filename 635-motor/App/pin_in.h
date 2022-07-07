#ifndef PIN_IN_H
#define PIN_IN_H

#include <stdint.h>
#include <stdbool.h>

typedef struct pin_in
{
    uint32_t port;
    uint32_t pin;

    bool status;
} pin_in_t;

void pin_in_init(pin_in_t *me, uint32_t port, uint32_t pin);
bool pin_in_get_status(pin_in_t *me);

#endif
