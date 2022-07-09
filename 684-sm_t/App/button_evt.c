#include "button_evt.h"
#include "button.h"

static void button_evt_poll(object_t *me);

void button_evt_init(button_evt_t *me, uint8_t button_id, sm_t *sm)
{
    obj_register(&me->super, button_evt_poll, 10);
    me->button_id = button_id;
    me->sm = sm;

    me->status_bkp = button_is_pressed(me->button_id);
}

static void button_evt_poll(object_t *obj)
{
    button_evt_t *me = (button_evt_t *)obj;

    // Button Poll
    bool status = button_is_pressed(me->button_id);

    // Button event
    if (status != me->status_bkp)
    {
        if (status == true)
        {
            sm_event_send(me->sm, ButtonEvt_Press);
        }
        else
        {
            sm_event_send(me->sm, ButtonEvt_Release);
        }
        me->status_bkp = status;
    }

    sm_event_send(me->sm, ButtonEvt_Poll);
}
