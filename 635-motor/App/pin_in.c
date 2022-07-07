#include "pin_in.h"

void pin_in_init(pin_in_t *me, uint32_t port, uint32_t pin)
{
    (void)me;
    (void)port;
    (void)pin;
}

bool pin_in_get_status(pin_in_t *me)
{
    return me->status;
}

