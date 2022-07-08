#ifndef BSP_H
#define BSP_H

#include <stdint.h>

void bsp_init(void);
uint32_t system_time(void);

void cb_systick(void);

#endif
