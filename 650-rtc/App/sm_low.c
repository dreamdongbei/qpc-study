#include "sm.h"
#include "event_def.h"
#include "qpc.h"

Q_DEFINE_THIS_MODULE("SmLow")

static QState state_init(sm_test_t * const me, void const * const par);
static QState state_work(sm_test_t * const me, QEvt const * const e);

sm_test_t sm_low;

void sm_low_init(void)
{
    sm_test_t *me = &sm_low;

    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    static QEvt const *event_queue[128];
    QACTIVE_START(&me->super,
                  SmPrio_Low,
                  event_queue, (sizeof(event_queue) / sizeof(QEvt const *)),
                  (void *)0, 0U,
                  (void *)0);
}

static QState state_init(sm_test_t * const me, void const * const par)
{
    QActive_subscribe(&me->super, Event_Low);

    return Q_TRAN(&state_work);
}

static QState state_work(sm_test_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Event_Low:
            sm_delay_ms(SM_LOW_DELAY_MS);
            me->count ++;
            return Q_HANDLED();

        default:
            return Q_SUPER(&QHsm_top);
    }
}
