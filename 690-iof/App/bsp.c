#include "bsp.h"
#include "gd32f3x0.h"

static void systick_config(void);

static uint32_t system_time_ms = 0;

void bsp_init(void)
{
    systick_config();
}

uint32_t system_time(void)
{
    return system_time_ms;
}

static void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        /* capture error */
        while(1)
        {
        }
    }
    
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x8U);
}

void SysTick_Handler(void)
{
    system_time_ms ++;
}
