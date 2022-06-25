
#ifndef AO_LED_H
#define AO_LED_H

#include "qpc.h"

#define AO_LED_QUEUE_LENGTH                 32

// LED类的定义
typedef struct ao_led_tag{
    QActive super;                                      // 对QActive类的继承
    
    QEvt const *evt_queue[AO_LED_QUEUE_LENGTH];         // 事件队列
    QTimeEvt timeEvt;                                   // 延时事件
    
    bool status;                                        // LED状态
} ao_led_t;

// LED的类方法 构造函数
void ao_led_ctor(ao_led_t * const me);

#endif
