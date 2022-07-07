#ifndef PIN_OUT_H
#define PIN_OUT_H

#include <stdint.h>

class pin_out_t
{
public:
    void init(uint32_t port, uint32_t pin);
    void set_status(bool status);

private:
    uint32_t port_;
    uint32_t pin_;
};

#endif
