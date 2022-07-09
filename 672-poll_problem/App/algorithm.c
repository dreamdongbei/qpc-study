#include "algorithm.h"
#include "poll.h"
#include "bsp.h"

static object_t algorithm;

static void algorithm_poll(object_t *me);

void algorithm_init(void)
{
    obj_register(&algorithm, algorithm_poll, 1000);
}

static void algorithm_poll(object_t *me)
{
    uint32_t time_consume = 500;
    uint32_t time_end = system_time() + time_consume;

    while (system_time() <= time_end);
}
