#ifndef POLL_H
#define POLL_H

#include <stdint.h>

struct object;
typedef void (* func_poll_t)(struct object *me);

typedef struct object
{
    struct object *next;
    func_poll_t poll;
    uint32_t time_unit_ms;
    uint32_t systime_bkp;
} object_t;

void obj_register(object_t *me, func_poll_t poll, uint32_t time_unit_ms);
void obj_poll(void);

#endif
