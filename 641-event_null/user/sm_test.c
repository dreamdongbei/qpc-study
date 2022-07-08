#include "sm_test.h"
#include "sm_def.h"
#include "event_def.h"
#include "qpc.h"

Q_DEFINE_THIS_MODULE("SmTest")

typedef struct sm_test
{
    QActive super;
    
    uint32_t count_click;
    uint32_t count_double_click;
    uint32_t count_long_press;
} sm_test_t;

static QState state_init(sm_test_t * const me, void const * const par);
static QState state_work(sm_test_t * const me, QEvt const * const e);

sm_test_t test;

void sm_test_init(void)
{
    sm_test_t *me = &test;

    // 活动对象的构建
    QActive_ctor(&me->super, Q_STATE_CAST(&state_init));
    // 活动对象的启动
    static QEvt const *event_queue[128];
    QACTIVE_START(&me->super,
                  SmPrio_Test,
                  event_queue, (sizeof(event_queue) / sizeof(QEvt const *)),
                  (void *)0, 0U,
                  (void *)0);
}

static QState state_init(sm_test_t * const me, void const * const par)
{
    QActive_subscribe(&me->super, Evt_Click);
    QActive_subscribe(&me->super, Evt_DoubleClick);
    QActive_subscribe(&me->super, Evt_LongPress);
    
    return Q_TRAN(&state_work);
}

static QState state_work(sm_test_t * const me, QEvt const * const e)
{
    switch (e->sig)
    {
        case Evt_Click:
            me->count_click ++;
            return Q_HANDLED();

        case Evt_DoubleClick:
            me->count_double_click ++;
            return Q_HANDLED();

        case Evt_LongPress:
            me->count_long_press ++;
            return Q_HANDLED();

        default:
            return Q_SUPER(&QHsm_top);
    }
}
