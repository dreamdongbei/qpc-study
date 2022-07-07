
#include "pin_in.h"

void pin_in_t::init(uint32_t port, uint32_t pin)
{
    port_ = port;
    pin_ = pin;
}

bool pin_in_t::get_status(void)
{
    return false;
}
