
#include "stm32f0xx.h"
#include "qpc.h"
#include "event_def.h"
#include "ao.h"

Q_DEFINE_THIS_MODULE("Main")        // 定义当前的模块名称，此名称在QS和断言中会使用。

ao_low_t ao_low;                                        // 优先级低的AO
ao_high_t ao_high;                                      // 优先级高的AO

uint32_t system_time_ms = 0;
uint32_t system_time_bkp = 0;
uint32_t time_consume_ms = 0;

static void cpu_wait(uint32_t time_ms)
{
    uint32_t loop_size;
    
    while (time_ms --) {
        loop_size = 8000;
        while (loop_size --) {
            __nop();
        }
    }
}

int main(void)
{
    static QSubscrList sub_sto[MAX_PUB_SIG];            // 定义订阅缓冲区
    static QF_MPOOL_EL(m_evt_t) sml_pool_sto[128];      // 定义事件池

    SysTick_Config(SystemCoreClock / 1000);             // 时间基准为1ms
    
    QF_init();                                          // 状态机框架初始化
    QF_psInit(sub_sto, Q_DIM(sub_sto));                 // 发布-订阅缓冲区的初始化
    QF_poolInit(sml_pool_sto,                           // 事件池的初始化
                sizeof(sml_pool_sto),
                sizeof(sml_pool_sto[0]));
    
//    system_time_bkp = system_time_ms;
//    cpu_wait(10);
//    time_consume_ms = system_time_ms - system_time_bkp;
                
    ao_low_ctor(&ao_low);                               // 状态机的构建
    ao_high_ctor(&ao_high);                             // 状态机的构建
    
    return QF_run();                                    // 框架启动
}

void SysTick_Handler(void)
{
    QK_ISR_ENTRY();
    QF_TICK_X(0U, &l_SysTick_Handler);              // 时间基准
    
    system_time_ms ++;
    QK_ISR_EXIT();
}

void QF_onStartup(void)
{

}

void QF_onCleanup(void)
{
    // null
}

uint32_t count_qk_idle = 0;
void QK_onIdle(void)
{
    count_qk_idle ++;
}

char * qp_module = 0;
int qp_loc = 0;
void Q_onAssert(char_t const * const module, int_t const loc)
{
    qp_module = (char *)module;
    qp_loc = loc;
    
    while (1);
}
