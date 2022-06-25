#include "qpc.h"

enum DPPSignals {
    Evt_AoLow = Q_USER_SIG,
    Evt_AoHigh,
    MAX_PUB_SIG,

    Evt_Send,
    
    MAX_SIG
};

typedef struct m_evt_tag {
    QEvt super;
    uint32_t data;
} m_evt_t;

