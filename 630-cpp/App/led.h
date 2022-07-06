#ifndef LED_H
#define LED_H

#include <stdint.h>

class led_t
{
public:
    void init(uint32_t port, uint32_t pin);
    void set_status(bool status);

private:
    uint32_t port_;
    uint32_t pin_;
};


#endif
