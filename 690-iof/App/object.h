#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

enum
{
    ObjType_IO = 0,
    ObjType_Device,
};

typedef struct object
{
    const char *name;
    uint8_t type;
} object_t;

void obj_init(void);
void obj_add(object_t *me);
object_t *obj_find(const char *name);
void obj_poll(void);

#endif
