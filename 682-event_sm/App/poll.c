#include "poll.h"
#include <stdlib.h>
#include "bsp.h"

// 对象容器
static object_t *list_obj = NULL;

void obj_register(object_t *me, func_poll_t poll, uint32_t time_unit_ms)
{
    me->poll = poll;
    me->time_unit_ms = time_unit_ms;
    me->systime_bkp = system_time();

    // Add it to the object list.
    me->next = list_obj;
    list_obj = me;
}

void obj_poll(void)
{
    object_t *list = list_obj;
    while (list != NULL)
    {
        if (system_time() >= (list->systime_bkp + list->time_unit_ms))
        {
            list->systime_bkp += list->time_unit_ms;

            list->poll(list);
        }

        list = list->next;
    }
}
