#include "qpc.h"
#include "bsp.h"

void QF_onStartup(void)
{
    bsp_init();                                         // 硬件初始化
}

void QF_onCleanup(void)
{
    // null
}

void QV_onIdle(void)
{
    // null
}

void Q_onAssert(char_t const * const module, int_t const loc)
{
    (void)module;
    (void)loc;
    while (1);
}
