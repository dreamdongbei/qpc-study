#ifndef SM_LED_H
#define SM_LED_H

#include "qpc.h"
#include <stdint.h>

// LED类的定义
// QActive 状态机基类
typedef struct sm_led_tag
{
    QActive super;                                      // 对QActive类的继承
    uint8_t status;
} sm_led_t;

void sm_led_init(void);

#endif
