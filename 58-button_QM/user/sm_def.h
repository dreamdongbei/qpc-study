/*.$file${.::sm_def.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: button.qm
* File:  ${.::sm_def.h}
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
/*.$endhead${.::sm_def.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#ifndef SM_DEF_H
#define SM_DEF_H

enum
{
    SmPrio_Led = 1,
    SmPrio_Button,
    SmPrio_Count,
};

#define SM_LED_QUEUE_LENGTH                     (32)
#define SM_BUTTON_QUEUE_LENGTH                  (128)
#define SM_COUNT_QUEUE_LENGTH                   (32)

#endif