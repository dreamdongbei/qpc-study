#ifndef DRIVER_UART_H
#define DRIVER_UART_H

#include <stdint.h>
#include "qpc.h"

#define UART_DATA_RECV_SIZE                         (128)
#define UART_BUFF_SEND_SIZE                         (1024)

enum
{
    DevUart_1 = 0,

    DevUart_Max
};

typedef struct event_uart_data
{
    QEvt super;
    uint16_t size;
    uint8_t buffer[UART_DATA_RECV_SIZE];
} event_uart_data_t;

void uart_init(void);
void uart_set_event_recv(uint8_t uart_id, uint32_t e_sig);
uint32_t uart_write(uint8_t uart_id, void *buffer, uint32_t size);

#endif
