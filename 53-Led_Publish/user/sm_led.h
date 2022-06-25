#ifndef SM_LED_H
#define SM_LED_H

#include "qpc.h"

// LED类的定义
typedef struct sm_led_tag
{
    QActive super;                                      // 对QActive类的继承
} sm_led_t;

void sm_led_init(void);

#endif
