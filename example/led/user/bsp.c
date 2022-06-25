
#include "bsp.h"
#include "stm32f10x.h"
#include "qpc.h"

void bsp_init(void)
{
    SysTick_Config(SystemCoreClock / 1000);         // 时间基准为1ms
    NVIC_SetPriority(SysTick_IRQn, 0);              // 设置中断优先级
}

void SysTick_Handler(void)
{
    QF_TICK_X(0U, &l_SysTick_Handler);              // 时间基准
}
