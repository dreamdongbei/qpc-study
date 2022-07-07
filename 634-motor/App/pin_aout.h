#ifndef PIN_AOUT_H
#define PIN_AOUT_H

#include <stdint.h>

class pin_aout_t
{
public:
    void init(uint32_t port, uint32_t pin, uint32_t scale);
    void set_value(uint32_t mv);

private:
    uint32_t port_;
    uint32_t pin_;
    uint32_t scale_;
};

#endif
