#ifndef DEV_BUTTON_H
#define DEV_BUTTON_H

#include <stdint.h>
#include "qpc.h"

typedef enum button_action
{
    DevButtonAction_Click = 0,
    DevButtonAction_DoubleClick,
    DevButtonAction_LongPress,
} button_action_t;

typedef struct dev_button_event
{
    QEvt super;
    uint8_t dev_id;
} dev_button_event_t;

void dev_button_init(void);
void dev_button_poll(uint32_t time_unit);

void dev_button_set_event(uint8_t dev_button_id, uint8_t action, uint32_t event);

#endif
