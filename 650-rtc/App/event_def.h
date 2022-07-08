#ifndef EVENT_DEF_H
#define EVENT_DEF_H

#include "qpc.h"

enum
{
    Event_Test = Q_USER_SIG,
    Event_Low,
    Event_Middle,
    Event_High,
    MAX_PUB_SIG,
    
    MAX_SIG
};

#endif
