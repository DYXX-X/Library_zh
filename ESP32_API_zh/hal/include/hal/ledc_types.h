// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"

typedef enum {
#if SOC_LEDC_SUPPORT_HS_MODE
    LEDC_HIGH_SPEED_MODE = 0, /*!< LEDC高速速度_模式*/
#endif
    LEDC_LOW_SPEED_MODE,      /*!< LEDC低速模式*/
    LEDC_SPEED_MODE_MAX,      /*!< LEDC速度限制*/
} ledc_mode_t;

typedef enum {
    LEDC_INTR_DISABLE = 0,    /*!< 禁用LEDC中断*/
    LEDC_INTR_FADE_END,       /*!< 启用LEDC中断*/
    LEDC_INTR_MAX,
} ledc_intr_type_t;

typedef enum {
    LEDC_DUTY_DIR_DECREASE = 0,    /*!< LEDC占空比降低方向*/
    LEDC_DUTY_DIR_INCREASE = 1,    /*!< LEDC占空比增加方向*/
    LEDC_DUTY_DIR_MAX,
} ledc_duty_direction_t;

typedef enum {
    LEDC_SLOW_CLK_RTC8M = 0,  /*!< LEDC低速定时器时钟源为8MHz RTC时钟*/
    LEDC_SLOW_CLK_APB,     /*!< LEDC低速定时器时钟源为80MHz APB时钟*/
#if SOC_LEDC_SUPPORT_XTAL_CLOCK
    LEDC_SLOW_CLK_XTAL,    /*!< LEDC低速定时器时钟源XTAL时钟*/
#endif
} ledc_slow_clk_sel_t;

typedef enum {
    LEDC_AUTO_CLK = 0,    /*!< 当初始化计时器时，驱动器将根据给定的分辨率和占空比参数自动选择源时钟（REF_TICK或APB）*/
    LEDC_USE_REF_TICK,    /*!< LEDC计时器选择REF_TICK时钟作为源时钟*/
    LEDC_USE_APB_CLK,     /*!< LEDC定时器选择APB时钟作为源时钟*/
    LEDC_USE_RTC8M_CLK,   /*!< LEDC计时器选择RTC8M_CLK作为源时钟。仅适用于低速通道，该参数必须与所有低速通道相同*/
#if SOC_LEDC_SUPPORT_XTAL_CLOCK
    LEDC_USE_XTAL_CLK,    /*!< LEDC定时器选择XTAL时钟作为源时钟*/
#endif
} ledc_clk_cfg_t;

/* 注意：设置数值以匹配ledc_clk_cfg_t值是避免与驱动程序中的ledc_AUTO_clk冲突的一种方法，因为这些枚举具有非常相似的名称，用户可能会错误地传递其中一个。*/
typedef enum  {
    LEDC_REF_TICK = LEDC_USE_REF_TICK, /*!< LEDC计时器时钟除以参考刻度（1Mhz）*/
    LEDC_APB_CLK = LEDC_USE_APB_CLK,  /*!< LEDC定时器时钟除以APB时钟（80Mhz）*/
} ledc_clk_src_t;


typedef enum {
    LEDC_TIMER_0 = 0, /*!< LEDC计时器0*/
    LEDC_TIMER_1,     /*!< LEDC计时器1*/
    LEDC_TIMER_2,     /*!< LEDC计时器2*/
    LEDC_TIMER_3,     /*!< LEDC计时器3*/
    LEDC_TIMER_MAX,
} ledc_timer_t;

typedef enum {
    LEDC_CHANNEL_0 = 0, /*!< LEDC通道0*/
    LEDC_CHANNEL_1,     /*!< LEDC通道1*/
    LEDC_CHANNEL_2,     /*!< LEDC通道2*/
    LEDC_CHANNEL_3,     /*!< LEDC通道3*/
    LEDC_CHANNEL_4,     /*!< LEDC通道4*/
    LEDC_CHANNEL_5,     /*!< LEDC通道5*/
#if SOC_LEDC_CHANNEL_NUM > 6
    LEDC_CHANNEL_6,     /*!< LEDC通道6*/
    LEDC_CHANNEL_7,     /*!< LEDC通道7*/
#endif
    LEDC_CHANNEL_MAX,
} ledc_channel_t;

typedef enum {
    LEDC_TIMER_1_BIT = 1,   /*!< LEDC PWM占空比分辨率为1位*/
    LEDC_TIMER_2_BIT,       /*!< LEDC PWM占空比分辨率为2位*/
    LEDC_TIMER_3_BIT,       /*!< LEDC PWM占空比分辨率为3位*/
    LEDC_TIMER_4_BIT,       /*!< LEDC PWM占空比分辨率为4位*/
    LEDC_TIMER_5_BIT,       /*!< LEDC PWM占空比分辨率为5位*/
    LEDC_TIMER_6_BIT,       /*!< LEDC PWM占空比分辨率为6位*/
    LEDC_TIMER_7_BIT,       /*!< LEDC PWM占空比分辨率为7位*/
    LEDC_TIMER_8_BIT,       /*!< 8位LEDC PWM占空比分辨率*/
    LEDC_TIMER_9_BIT,       /*!< LEDC PWM占空比分辨率为9位*/
    LEDC_TIMER_10_BIT,      /*!< LEDC PWM占空比分辨率为10位*/
    LEDC_TIMER_11_BIT,      /*!< LEDC PWM占空比分辨率为11位*/
    LEDC_TIMER_12_BIT,      /*!< LEDC PWM占空比分辨率为12位*/
    LEDC_TIMER_13_BIT,      /*!< LEDC PWM占空比分辨率为13位*/
    LEDC_TIMER_14_BIT,      /*!< LEDC PWM占空比分辨率为14位*/
#if SOC_LEDC_TIMER_BIT_WIDE_NUM > 14
    LEDC_TIMER_15_BIT,      /*!< LEDC PWM占空比分辨率为15位*/
    LEDC_TIMER_16_BIT,      /*!< LEDC PWM占空比分辨率为16位*/
    LEDC_TIMER_17_BIT,      /*!< LEDC PWM占空比分辨率为17位*/
    LEDC_TIMER_18_BIT,      /*!< 18位LEDC PWM占空比分辨率*/
    LEDC_TIMER_19_BIT,      /*!< LEDC PWM占空比分辨率为19位*/
    LEDC_TIMER_20_BIT,      /*!< LEDC PWM占空比分辨率为20位*/
#endif
    LEDC_TIMER_BIT_MAX,
} ledc_timer_bit_t;

typedef enum {
    LEDC_FADE_NO_WAIT = 0,  /*!< LEDC淡入功能将立即返回*/
    LEDC_FADE_WAIT_DONE,    /*!< LEDC衰减功能将被阻止，直到衰减到目标占空比*/
    LEDC_FADE_MAX,
} ledc_fade_mode_t;

/**
 * @brief LEDC_channel_config函数的LEDC通道配置参数
 */
typedef struct {
    int gpio_num;                   /*!< LEDC输出gpio_num，如果要使用gpio16，gpio_num=16*/
    ledc_mode_t speed_mode;         /*!< LEDC速度speed_mode，高速模式或低速模式*/
    ledc_channel_t channel;         /*!< LEDC通道（0-7）*/
    ledc_intr_type_t intr_type;     /*!< 配置中断、淡入中断启用或淡入中断禁用*/
    ledc_timer_t timer_sel;         /*!< 选择信道的定时器源（0-3）*/
    uint32_t duty;                  /*!< LEDC通道占空比，占空比设置范围为[0，（2**占空比分辨率）]*/
    int hpoint;                     /*!< LEDC通道hpoint值，最大值为0xfffff*/
    struct {
        unsigned int output_invert: 1;/*!< 启用（1）或禁用（0）gpio输出反转*/
    } flags;                        /*!< LEDC标志*/

} ledc_channel_config_t;

/**
 * @brief LEDC_Timer_config函数的LEDC定时器配置参数
 */
typedef struct {
    ledc_mode_t speed_mode;                /*!< LEDC速度speed_mode，高速模式或低速模式*/
    union {
        ledc_timer_bit_t duty_resolution;  /*!< LEDC通道占空比分辨率*/
        ledc_timer_bit_t bit_num __attribute__((deprecated)); /*!< ESP-IDF 3.0中已弃用。这是“duty_resolution”的别名，用于与ESP-IDF 2.1向后兼容*/
    };
    ledc_timer_t  timer_num;               /*!< 信道的定时器源（0-3）*/
    uint32_t freq_hz;                      /*!< LEDC定时器频率（Hz）*/
    ledc_clk_cfg_t clk_cfg;                /*!< 配置LEDC源时钟。对于低速通道和高速通道，可以使用LEDC_USE_REF_TICK、LEDC_USE_APB_CLK或LEDC_AUTO_CLK指定源时钟。对于低速通道，您也可以使用LEDC_USE_RTC8M_CLK指定源时钟，在这种情况下，所有低速通道的源时钟必须为RTC8M_CLK*/
} ledc_timer_config_t;

#ifdef __cplusplus
}
#endif

