#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "pin_out.h"

class led_t : public pin_out_t
{
public:
    void twinkle(uint32_t frequency);
    void poll(void);

private:
    uint32_t frequency;
    bool status;
};


#endif
