#ifndef SM_H
#define SM_H

#include "poll.h"

enum
{
    Evt_Null = 0,
    Evt_Entry,
    Evt_Exit,
    Evt_User,
};

struct sm;
typedef void (* func_state_t)(struct sm *me, uint8_t e_topic);

typedef struct sm
{
    object_t super;

    func_state_t state;
    func_state_t state_bkp;

    uint8_t *e_queue;
    uint32_t size;
    uint32_t count;
} sm_t;

void sm_init(sm_t *me, uint8_t *e_queue, uint32_t size, func_state_t state_init);
void sm_event_send(sm_t *me, uint8_t e_topic);
void sm_tran(sm_t *me, func_state_t state);

#define SM_TRAN(state)          sm_tran((sm_t *)me, (func_state_t)state)

#endif
