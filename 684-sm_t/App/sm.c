#include "sm.h"

static void sm_poll(object_t *me);

void sm_init(sm_t *me, uint8_t *e_queue, uint32_t size, func_state_t state_init)
{
    obj_register(&me->super, sm_poll, 1);

    me->state = state_init;
    me->state_bkp = state_init;
    me->e_queue = e_queue;
    me->size = size;

    me->state(me, Evt_Entry);
}

void sm_event_send(sm_t *me, uint8_t e_topic)
{
    // 演示代码，不考虑事件队列溢出的情况
    me->e_queue[me->count ++] = e_topic;
}

void sm_tran(sm_t *me, func_state_t state)
{
    me->state = state;
}

static void sm_poll(object_t *me)
{
    sm_t *sm = (sm_t *)me;
    if (sm->count == 0)
    {
        return;
    }

    for (uint8_t i = 0; i < sm->count; i ++)
    {
        if (sm->state_bkp != sm->state)
        {
            sm->state_bkp(sm, Evt_Exit);
            sm->state(sm, Evt_Entry);
            
            sm->state_bkp = sm->state;
        }
        sm->state(sm, sm->e_queue[i]);
    }
    
    sm->count = 0;
}
