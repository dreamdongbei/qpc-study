#include "driver_uart.h"
#include "gd32f3x0.h"

typedef struct driver_uart_data
{
    uint8_t buffer[UART_BUFF_SEND_SIZE];
    uint16_t size;
} driver_uart_data_t;

typedef struct drvier_uart_hw_info
{
    uint32_t clock;
    uint32_t usart_periph;
    uint32_t baudrate;
    IRQn_Type irq;
    dma_channel_enum dma_channel_tx;
    dma_channel_enum dma_channel_rx;
} drvier_uart_hw_info_t;

static const drvier_uart_hw_info_t uart_hw_info[DevUart_Max] =
{
    {
        RCU_USART0, USART0, 115200, 
    },

    {
        RCU_USART1, USART1, 115200, 
    },
};

static driver_uart_data_t uart_data[DevUart_Max];

void uart_init(void)
{

}

void uart_set_event_recv(uint8_t uart_id, uint32_t e_sig)
{

}

uint32_t uart_write(uint8_t uart_id, void *buffer, uint32_t size)
{

}
