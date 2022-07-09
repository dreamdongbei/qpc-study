#ifndef SM_H
#define SM_H

#include "qpc.h"

enum
{
    SmPrio_A = 1,
    SmPrio_B,
};

typedef struct sm
{
    QActive super;
} sm_t;

void sm_a_init(void);
void sm_b_init(void);

#endif
