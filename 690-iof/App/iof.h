#ifndef IOF_H
#define IOF_H

#include "object.h"

enum
{
    IoType_In = 0,
    IoType_Out,
    IoType_AIn,
    IoType_AOut,
    IoType_Uart,
    IoType_SPI,
    IoType_OneWire,
    IoType_IIC,
    IoType_CAN,
};

typedef struct io
{
    object_t super;
    uint8_t type;
} io_t;

void iof_init(void);
void io_enable(io_t * io);
uint32_t io_read(io_t * io, uint32_t pos, void *data, uint32_t size);
uint32_t io_write(io_t * io, uint32_t pos, void *data, uint32_t size);
uint32_t io_control(io_t * io, uint32_t cmd, void *data);

#endif
