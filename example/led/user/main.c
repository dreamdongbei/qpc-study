
#include "qpc.h"
#include "evt_def.h"
#include "bsp.h"
#include "ao_led.h"

Q_DEFINE_THIS_MODULE("Main")        // 定义当前的模块名称，此名称在QS和断言中会使用。

ao_led_t led;                                           // 状态机LED

int main(void)
{
    static QSubscrList sub_sto[MAX_PUB_SIG];            // 定义订阅缓冲区
    static QF_MPOOL_EL(m_evt_t) sml_pool_sto[128];      // 定义事件池
    
    QF_init();                                          // 状态机框架初始化
    QF_psInit(sub_sto, Q_DIM(sub_sto));                 // 发布-订阅缓冲区的初始化
    QF_poolInit(sml_pool_sto,                           // 事件池的初始化
                sizeof(sml_pool_sto),
                sizeof(sml_pool_sto[0]));
                
    ao_led_ctor(&led);                                  // 状态机的构建
    
    return QF_run();                                    // 框架启动
}
