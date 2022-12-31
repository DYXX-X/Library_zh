// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#include <esp_bit_defs.h>
#include "esp_attr.h"
#include "soc/soc_caps.h"

/**
 * @brief 从2个可用组中选择一个计时器组
 */
typedef enum {
    TIMER_GROUP_0 = 0, /*!<Hw计时器组0*/
#if SOC_TIMER_GROUPS > 1
    TIMER_GROUP_1 = 1, /*!<Hw计时器组1*/
#endif
    TIMER_GROUP_MAX,
} timer_group_t;

/**
 * @brief 从计时器组中选择硬件计时器
 */
typedef enum {
    TIMER_0 = 0, /*!<选择GROUPx的timer0*/
#if SOC_TIMER_GROUP_TIMERS_PER_GROUP > 1
    TIMER_1 = 1, /*!<选择GROUPx的timer1*/
#endif
    TIMER_MAX,
} timer_idx_t;

/**
 * @brief 决定计数器的方向
 */
typedef enum {
    TIMER_COUNT_DOWN = 0, /*!< 从cnt.high|cnt.low递减计数*/
    TIMER_COUNT_UP = 1,   /*!< 从零开始递增计数*/
    TIMER_COUNT_MAX
} timer_count_dir_t;

/**
 * @brief 决定计时器是打开还是暂停
 */
typedef enum {
    TIMER_PAUSE = 0, /*!<暂停计时器计数器*/
    TIMER_START = 1, /*!<启动计时器计数器*/
} timer_start_t;

/**
 * @brief 计时器的中断类型。
 */
//这与esp32的值兼容。
typedef enum {
    TIMER_INTR_T0 = BIT(0),  /*!< 计时器0中断*/
#if SOC_TIMER_GROUP_TIMERS_PER_GROUP > 1
    TIMER_INTR_T1 = BIT(1),  /*!< 计时器1中断*/
    TIMER_INTR_WDT = BIT(2), /*!< 看门狗中断*/
#else
    TIMER_INTR_WDT = BIT(1), /*!< 看门狗中断*/
#endif
    TIMER_INTR_NONE = 0
} timer_intr_t;
FLAG_ATTR(timer_intr_t)

/**
 * @brief 决定是否启用报警模式
 */
typedef enum {
    TIMER_ALARM_DIS = 0,  /*!< 禁用计时器报警*/
    TIMER_ALARM_EN = 1,   /*!< 启用计时器报警*/
    TIMER_ALARM_MAX
} timer_alarm_t;

/**
 * @brief 如果在报警模式下运行，请选择中断类型。
 */
typedef enum {
    TIMER_INTR_LEVEL = 0,  /*!< 中断模式：电平模式*/
    TIMER_INTR_MAX
} timer_intr_mode_t;

/**
 * @brief 选择报警需要由软件加载还是由硬件自动加载。
 */
typedef enum {
    TIMER_AUTORELOAD_DIS = 0,  /*!< 禁用自动重新加载：报警事件后，硬件不会加载计数器值*/
    TIMER_AUTORELOAD_EN = 1,   /*!< 启用自动重新加载：硬件将在报警事件后加载计数器值*/
    TIMER_AUTORELOAD_MAX,
} timer_autoreload_t;

#if SOC_TIMER_GROUP_SUPPORT_XTAL
/**
 * @brief 选择定时器源时钟。
 */
typedef enum {
    TIMER_SRC_CLK_APB = 0,  /*!< 选择APB作为源时钟*/
    TIMER_SRC_CLK_XTAL = 1, /*!< 选择XTAL作为源时钟*/
} timer_src_clk_t;
#endif

/**
 * @brief 具有计时器配置设置的数据结构
 */
typedef struct {
    timer_alarm_t alarm_en;      /*!< 定时器报警启用*/
    timer_start_t counter_en;    /*!< 计数器启用*/
    timer_intr_mode_t intr_type; /*!< 中断模式*/
    timer_count_dir_t counter_dir; /*!< 反方向*/
    timer_autoreload_t auto_reload;   /*!< 计时器自动重新加载*/
    uint32_t divider;   /*!< 计数器时钟分频器。除法器的范围从2到65536。*/
#if SOC_TIMER_GROUP_SUPPORT_XTAL
    timer_src_clk_t clk_src;  /*!< 使用XTAL作为源时钟。*/
#endif
} timer_config_t;

#ifdef __cplusplus
}
#endif

