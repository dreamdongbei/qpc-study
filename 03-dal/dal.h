#ifndef DAL_H
#define DAL_H

#include <stdint.h>

enum
{
    State_Idle = 0,                             // 待机
    State_Working_Light,                        // 轻度污染
    State_Working_Middle,                       // 中度
    State_Working_Dirty,                        // 重度
    State_Working_Charging,                     // 充电中
    State_Working_Charged,                      // 满电
};

enum 
{
    Warning_None = 0,
    Warning_NoRecoveryTank,                     // 未安装污水箱
    Warning_AirDuctingBlock,                    // 风道堵塞

    Warning_Max
};

typedef struct dal_h11_max
{
    uint8_t state;
    uint16_t motor1_speed;
    uint16_t motor2_speed;
    uint8_t warning;
    uint8_t battery_level;                      // 电池电量
    uint8_t error;
} dal_h11_max;

extern dal_h11_max *h11_max;

#endif
