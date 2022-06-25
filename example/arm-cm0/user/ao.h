
#ifndef AO_LED_H
#define AO_LED_H

#include "qpc.h"

#define AO_QUEUE_LENGTH                 32

// ao_low类的定义
typedef struct ao_low_tag{
    QActive super;                                      // 对QActive类的继承
    
    QEvt const *evt_queue[AO_QUEUE_LENGTH];             // 事件队列
    QTimeEvt timeEvt;                                   // 延时事件
    
    bool status;                                        // 状态
} ao_low_t;

// ao_high类的定义
typedef struct ao_high_tag{
    QActive super;                                      // 对QActive类的继承
    
    QEvt const *evt_queue[AO_QUEUE_LENGTH];             // 事件队列
    QTimeEvt timeEvt;                                   // 延时事件
    
    bool count;                                         // 状态
} ao_high_t;

// -----------------------------------------------------------------------------
void ao_low_ctor(ao_low_t * const me);
void ao_high_ctor(ao_high_t * const me);

#endif
