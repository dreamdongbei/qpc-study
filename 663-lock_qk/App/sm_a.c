#include "sm.h"
#include "qpc.h"
#include "event_def.h"

Q_DEFINE_THIS_MODULE("SmA")

sm_t sm_a;

extern uint8_t shared_data[128];
extern uint32_t write_count;
extern uint32_t loops_count;

static QState state_init(sm_t * const me, void const * const par);
static QState state_work(sm_t * const me, QEvt const * const e);

void sm_a_init(void)
{
    sm_t *me = &sm_a;

    // 活动对象的构造
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    static QEvt const *e_queue[32];
    QACTIVE_START(&me->super,
                  SmPrio_A,
                  e_queue, 32,
                  (void *)0, 0U,
                  (void *)0);
}

static QState state_init(sm_t * const me, void const * const par)
{
    return Q_TRAN(&state_work);
}

static QState state_work(sm_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Event_Test:
        {
            // QSchedStatus lock_status = QK_schedLock(SmPrio_B);

            for (uint32_t i = write_count; i < 100; i ++)
            {
                write_count = 0;
                for (uint32_t j = loops_count; j < 128; j ++)
                {
                    shared_data[j] = i;
                    write_count ++;
                }
                loops_count ++;
            }
            write_count = 0;
            loops_count = 0;

            // QK_schedUnlock(lock_status);

            return Q_HANDLED();
        }

        default:
            return Q_SUPER(&QHsm_top);
    }
}
