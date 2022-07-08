#ifndef SM_H
#define SM_H

#include "qpc.h"
#include "bsp.h"

#define SM_LOW_PERIOD_MS                        (10000)
#define SM_MID_PERIOD_MS                        (1000)
#define SM_HIGH_PERIOD_MS                       (100)

#define SM_LOW_DELAY_MS                         (SM_LOW_PERIOD_MS / 10 * 9)
#define SM_MIDDLE_DELAY_MS                      (SM_MID_PERIOD_MS / 10 * 9)
#define SM_HIGH_DELAY_MS                        (SM_HIGH_PERIOD_MS / 10 * 9)

static inline void sm_delay_ms(uint32_t time_ms)
{
    uint32_t time = system_time() + time_ms;
    while (system_time() < time);
}

enum
{
    SmPrio_Low = 1,
    SmPrio_Middle,
    SmPrio_High,
};

typedef struct sm_test
{
    QActive super;
    
    uint32_t count;
} sm_test_t;

void sm_low_init(void);
void sm_middle_init(void);
void sm_high_init(void);

#endif
