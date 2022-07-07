#ifndef PIN_IN_H
#define PIN_IN_H

#include <stdint.h>

class pin_in_t
{
public:
    void init(uint32_t port, uint32_t pin);
    bool get_status(void);

private:
    uint32_t port_;
    uint32_t pin_;
};

#endif
