#include "bsp.h"
#include "button.h"
#include "qpc.h"
#include "event_def.h"
#include "sm_def.h"
#include "sm_led.h"
#include "sm_button_qm.h"
#include "sm_count.h"

sm_button button_user;

int main(void)
{
    bsp_init();
    button_init();
    
    static QSubscrList sub_sto[MAX_PUB_SIG];            // 定义订阅缓冲区
    static QF_MPOOL_EL(m_evt_t) sml_pool_sto[128];      // 定义事件池
    
    QF_init();                                          // 状态机框架初始化
    QF_psInit(sub_sto, Q_DIM(sub_sto));                 // 发布-订阅缓冲区的初始化
    QF_poolInit(sml_pool_sto,                           // 事件池的初始化
                sizeof(sml_pool_sto),
                sizeof(sml_pool_sto[0]));
                
    sm_led_init();
    sm_count_init();
                
    static QEvt const *equeue[SM_BUTTON_QUEUE_LENGTH];
    sm_button_init(&button_user, ButtonId_UserKey, 2, equeue, SM_BUTTON_QUEUE_LENGTH);
    
    return QF_run();                                    // 框架启动
}

void cb_systick(void)
{
    QF_TICK_X(0U, &cb_systick);
}
