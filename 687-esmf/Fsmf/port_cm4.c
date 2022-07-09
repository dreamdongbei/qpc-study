
#include "bsp.h"
#include <stdlib.h>

uint32_t port_get_time_ms(void)
{
    return system_time();
}

void port_irq_disable(void)
{
    __disable_irq();
}

void port_irq_enable(void)
{
    __enable_irq();
}

void * port_malloc(uint32_t size)
{
    return malloc(size);
}

void hook_idle(void)
{
    
}

void hook_start(void)
{
    
}
