#include "bsp.h"
#include "qpc.h"
#include "event_def.h"
#include "sm_led.h"

int main(void)
{
    bsp_init();
    
    static QSubscrList sub_sto[MAX_PUB_SIG];            // 定义订阅缓冲区
    static QF_MPOOL_EL(m_evt_t) sml_pool_sto[128];      // 定义事件池
    
    QF_init();                                          // 状态机框架初始化
    QF_psInit(sub_sto, Q_DIM(sub_sto));                 // 发布-订阅缓冲区的初始化
    QF_poolInit(sml_pool_sto,                           // 事件池的初始化
                sizeof(sml_pool_sto),
                sizeof(sml_pool_sto[0]));
                
    sm_led_init();
    
    return QF_run();                                    // 框架启动
}

extern sm_led_t sm_led;

void cb_systick(void)
{
    if ((system_time() % 500) == 0)
    {
        QEvt *e = Q_NEW(QEvt, Evt_LedOnOff);
        QACTIVE_POST(&sm_led.super, e, &cb_systick);
    }
}
