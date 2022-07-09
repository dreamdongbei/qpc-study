#include "bsp.h"
#include "qpc.h"
#include "event_def.h"
#include "sm.h"

uint8_t shared_data[128];
uint32_t write_count = 0;
uint32_t loops_count = 0;

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
                
    sm_a_init();
    sm_b_init();
                
    return QF_run();                                    // 框架启动
}

extern sm_t sm_a;
extern sm_t sm_b;

void cb_systick(void)
{
    if ((system_time() % 1000) == 500)
    {
        // 基类
        QEvt *e = (QEvt *)Q_NEW(QEvt, Event_Test);
        QACTIVE_POST(&sm_a.super, e, &cb_systick);
    }
    
    if ((system_time() % 1000) == 501)
    {
        // 基类
        QEvt *e = (QEvt *)Q_NEW(QEvt, Event_Test);
        QACTIVE_POST(&sm_b.super, e, &cb_systick);
    }
}
