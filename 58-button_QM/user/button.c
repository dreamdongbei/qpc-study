#include "button.h"
#include "gd32f3x0.h"
#include "bsp.h"

typedef struct button_hw_info
{
    rcu_periph_enum clock;
    uint32_t port;
    uint32_t pin;
    uint32_t pull_up_down;
    bool polarity;
} button_hw_info_t;

typedef struct button_status_tag
{
    bool status;
    bool status_out;
    uint32_t time;
} button_status_t;

static const button_hw_info_t hw_info[ButtonId_Max] =
{
    { RCU_GPIOA, GPIOA, GPIO_PIN_0, GPIO_PUPD_PULLDOWN, true },
    { RCU_GPIOF, GPIOF, GPIO_PIN_7, GPIO_PUPD_PULLUP, false },
    { RCU_GPIOC, GPIOC, GPIO_PIN_13, GPIO_PUPD_PULLUP, false },
};

static button_status_t button_status[ButtonId_Max];

static void timer_config(void);

void button_init(void)
{
    nvic_irq_enable(TIMER2_IRQn, 0, 0);
    timer_config();

    for (uint32_t i = 0; i < ButtonId_Max; i ++)
    {
        /* enable the LED GPIO clock. */
        rcu_periph_clock_enable(hw_info[i].clock);

        /* configure led GPIO port. */
        gpio_mode_set(hw_info[i].port,
                      GPIO_MODE_INPUT,
                      hw_info[i].pull_up_down,
                      hw_info[i].pin);
        
        button_status[i].status = false;
        button_status[i].time = system_time();
    }
}

bool button_is_pressed(uint8_t button_id)
{
    return button_status[button_id].status_out;
}

static void timer_config(void)
{
    timer_parameter_struct timer_initpara;

    /* enable the peripherals clock */
    rcu_periph_clock_enable(RCU_TIMER2);

    /* deinit a TIMER */
    timer_deinit(TIMER2);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 840 - 1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 100 - 1;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_init(TIMER2, &timer_initpara);

    /* clear channel 0 interrupt bit */
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
    /* enable the TIMER interrupt */
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);
    /* enable a TIMER */
    timer_enable(TIMER2);
}

/**
  * @brief  This function handles TIMER2 interrupt request.
  * @param  None
  * @retval None
  */
void TIMER2_IRQHandler(void)
{
    if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_UP)) {
        /* clear update interrupt bit */
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);

        for (uint32_t i = 0; i < ButtonId_Max; i ++)
        {
            FlagStatus hw_status = gpio_input_bit_get(hw_info[i].port, hw_info[i].pin);
            bool status;
            if (hw_info[i].polarity == true)
            {
                status = (hw_status == RESET) ? false : true;
            }
            else
            {
                status = (hw_status == RESET) ? true : false;
            }

            if (button_status[i].status == status)
            {
                if ((system_time() - button_status[i].time) >= BUTTON_TIME_DE_JITTER)
                {
                    button_status[i].status_out = status;
                }
            }
            else
            {
                button_status[i].time = system_time();
                button_status[i].status = status;
            }
        }
    }
}
