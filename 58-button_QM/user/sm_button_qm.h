/*.$file${.::sm_button_qm.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: button.qm
* File:  ${.::sm_button_qm.h}
*
* This code has been generated by QM 5.1.4 <www.state-machine.com/qm/>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*.$endhead${.::sm_button_qm.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#ifndef SM_BUTTON_QM_H
#define SM_BUTTON_QM_H

#include "qpc.h"
#include <stdbool.h>

#define SM_BUTTON_CLICK_TIME_PRESS                  200
#define SM_BUTTON_CLICK_TIME_RELEASE                300
#define SM_BUTTON_LONG_PRESS_TIME_PRESS             1000

enum button_action
{
    ButtonAction_Click = 0,
    ButtonAction_DoubleClick,
    ButtonAction_LongPress,
};

/*.$declare${sm::sm_button} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${sm::sm_button} ........................................................*/
typedef struct {
/* protected: */
    QActive super;

/* public: */
    QTimeEvt e_poll;
    uint8_t button_id;
    QTimeEvt e_time_count;
    bool status_bkp;
    uint32_t time_pressed;
    uint32_t time_released;
    bool status;
} sm_button;

/* protected: */
QState sm_button_initial(sm_button * const me, void const * const par);
QState sm_button_work(sm_button * const me, QEvt const * const e);
QState sm_button_idle(sm_button * const me, QEvt const * const e);
QState sm_button_click(sm_button * const me, QEvt const * const e);
QState sm_button_release(sm_button * const me, QEvt const * const e);
QState sm_button_long_press(sm_button * const me, QEvt const * const e);
QState sm_button_double_click(sm_button * const me, QEvt const * const e);
/*.$enddecl${sm::sm_button} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void sm_button_init(sm_button *me,
                    uint8_t button_id,
                    uint8_t priority,
                    QEvt const **event_queue, uint32_t equeue_size);

/*.$declare${event::button_event} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${event::button_event} ..................................................*/
typedef struct {
/* protected: */
    QEvt super;

/* public: */
    uint8_t id;
    uint8_t action;
} button_event;
/*.$enddecl${event::button_event} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#endif