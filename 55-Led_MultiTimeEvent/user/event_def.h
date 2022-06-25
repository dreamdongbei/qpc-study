#ifndef EVENT_DEF_H
#define EVENT_DEF_H

#include "qpc.h"

enum
{
    Event_Test = Q_USER_SIG,
    MAX_PUB_SIG,
    
    Evt_Led1_OnOff,
    Evt_Led2_OnOff,
    Evt_Led3_OnOff,
    Evt_Led4_OnOff,
    
    MAX_SIG
};

typedef struct m_evt_tag {
    QEvt super;
    uint32_t data;
} m_evt_t;

#endif
