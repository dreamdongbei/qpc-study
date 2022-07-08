#ifndef EVENT_DEF_H
#define EVENT_DEF_H

#include "qpc.h"

enum
{
    Event_Null = Q_USER_SIG,
    Evt_Button,
    
    Evt_Click,
    Evt_DoubleClick,
    Evt_LongPress,
    
    MAX_PUB_SIG,
    
    Evt_Led1_OnOff,
    Evt_Led2_OnOff,
    Evt_Led3_OnOff,
    Evt_Led4_OnOff,

    Evt_Button_Poll,
    Evt_Button_TimeCount,
    Evt_Button_Pressed,
    Evt_Button_Released,

    MAX_SIG
};

typedef struct m_evt_tag {
    QEvt super;
    uint32_t data;
} m_evt_t;

#endif
