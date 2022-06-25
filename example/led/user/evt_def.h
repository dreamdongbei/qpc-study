#include "qpc.h"

enum DPPSignals {
    Evt_Time_10ms = Q_USER_SIG,
    Evt_Time_500ms,
    MAX_PUB_SIG,

    Evt_Send,
    
    MAX_SIG
};

typedef struct m_evt_tag {
    QEvt super;
    uint32_t data;
} m_evt_t;

