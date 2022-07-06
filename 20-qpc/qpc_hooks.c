#include "qpc.h"

void QV_onIdle(void)
{
    QF_INT_ENABLE();
}

void QK_onIdle(void)
{

}

void QXK_onIdle(void)
{

}

void QF_onStartup(void)
{

}

void QF_onCleanup(void)
{

}

char *p_module;
uint32_t p_loc;
void Q_onAssert(char_t const * const module, int const loc)
{
    p_module = (char *)module;
    p_loc = loc;
    
    while (1);
}
