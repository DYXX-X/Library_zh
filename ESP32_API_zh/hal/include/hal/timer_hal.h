// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// 计时器组的HAL层。
// hal层中没有参数检查，因此调用者必须确保参数的正确性。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "soc/soc_caps.h"
#include "hal/timer_ll.h"
#include "hal/timer_types.h"

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    timg_dev_t *dev;
    timer_idx_t idx;
} timer_hal_context_t;

/**
 * @brief 初始化计时器hal。在调用其他hal层函数之前，应先调用此函数
 *
 * @param hal HAL层的上下文
 * @param group_num 计时器组编号
 * @param timer_num 计时器编号
 *
 * @return 没有一个
 */
void timer_hal_init(timer_hal_context_t *hal, timer_group_t group_num, timer_idx_t timer_num);

/**
 * @brief 获取中断状态寄存器地址和相应的控制位掩码
 *
 * @param hal HAL层的上下文
 * @param status_reg[out] 中断状态寄存器地址
 * @param mask_bit[out] 控制位掩码
 */
void timer_hal_get_status_reg_mask_bit(timer_hal_context_t *hal, uint32_t *status_reg, uint32_t *mask_bit);

/**
 * @brief 重置定时器外围设备
 *
 * @param hal HAL层的上下文
 *
 * @return 没有一个
 */
void timer_hal_reset_periph(timer_hal_context_t *hal);

/**
 * @brief 设置定时器时钟预缩放值
 *
 * @param hal HAL层的上下文
 * @param divider 预缩放值
 *
 * @return 没有一个
 */
#define timer_hal_set_divider(hal, divider)  timer_ll_set_divider((hal)->dev, (hal)->idx, divider)

/**
 * @brief 获取计时器时钟预缩放值
 *
 * @param hal HAL层的上下文
 * @param divider 接受预缩放值的指针
 *
 * @return 没有一个
 */
#define timer_hal_get_divider(hal, divider)  timer_ll_get_divider((hal)->dev, (hal)->idx, divider)

/**
 * @brief 将计数器值加载到时基计数器
 *
 * @param hal HAL层的上下文
 * @param load_val 计数器值
 *
 * @return 没有一个
 */
#define timer_hal_set_counter_value(hal, load_val)  timer_ll_set_counter_value((hal)->dev, (hal)->idx, load_val)

/**
 * @brief 从时基计数器获取计数器值
 *
 * @param hal HAL层的上下文
 * @param timer_val 用于接受计数器值的指针
 *
 * @return 没有一个
 */
#define timer_hal_get_counter_value(hal, timer_val)  timer_ll_get_counter_value((hal)->dev, (hal)->idx, timer_val)

/**
 * @brief 设置计数器模式，包括递增模式和递减模式。
 *
 * @param hal HAL层的上下文
 * @param increase_en 真至递增模式，快至递减模式
 *
 * @return 没有一个
 */
#define timer_hal_set_counter_increase(hal, increase_en)  timer_ll_set_counter_increase((hal)->dev, (hal)->idx, increase_en)

/**
 * @brief 获取计数器模式，包括递增模式和递减模式。
 *
 * @param hal HAL层的上下文
 * @param counter_dir 接受计数器模式的指针
 *
 * @return
 *     -真增量模式
 *     -假减量模式
 */
#define timer_hal_get_counter_increase(hal)  timer_ll_get_counter_increase((hal)->dev, (hal)->idx)

/**
 * @brief 设置计数器状态，启用或禁用计数器。
 *
 * @param hal HAL层的上下文
 * @param counter_en True表示启用计数器，false表示禁用计数器
 *
 * @return 没有一个
 */
#define timer_hal_set_counter_enable(hal, counter_en)  timer_ll_set_counter_enable((hal)->dev, (hal)->idx, counter_en)

/**
 * @brief 获取计数器状态。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -true启用计数器
 *     -false禁用圆锥
 */
#define timer_hal_get_counter_enable(hal)  timer_ll_get_counter_enable((hal)->dev, (hal)->idx)

/**
 * @brief 设置自动重新加载模式。
 *
 * @param hal HAL层的上下文
 * @param auto_reload_en True表示启用自动重新加载模式，flase表示禁用自动重新加载方式
 *
 * @return 没有一个
 */
#define timer_hal_set_auto_reload(hal, auto_reload_en)  timer_ll_set_auto_reload((hal)->dev, (hal)->idx, auto_reload_en)

/**
 * @brief 获取自动重新加载模式。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -true启用自动重新加载模式
 *     -false禁用自动重新加载模式
 */
#define timer_hal_get_auto_reload(hal)  timer_ll_get_auto_reload((hal)->dev, (hal)->idx)

/**
 * @brief 设置计数器值以触发警报。
 *
 * @param hal HAL层的上下文
 * @param alarm_value 触发报警的计数器值
 *
 * @return 没有一个
 */
#define timer_hal_set_alarm_value(hal, alarm_value)  timer_ll_set_alarm_value((hal)->dev, (hal)->idx, alarm_value)

/**
 * @brief 获取触发警报的计数器值。
 *
 * @param hal HAL层的上下文
 * @param alarm_value 接受计数器值以触发报警的指针
 *
 * @return 没有一个
 */
#define timer_hal_get_alarm_value(hal, alarm_value)  timer_ll_get_alarm_value((hal)->dev, (hal)->idx, alarm_value)

/**
 * @brief 设置报警状态，启用或禁用报警。
 *
 * @param hal HAL层的上下文
 * @param alarm_en True表示启用报警，false表示禁用报警
 *
 * @return 没有一个
 */
#define timer_hal_set_alarm_enable(hal, alarm_en)  timer_ll_set_alarm_enable((hal)->dev, (hal)->idx, alarm_en)

/**
 * @brief 获取报警状态。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -真启用报警
 *     -假禁用报警
 */
#define timer_hal_get_alarm_enable(hal)  timer_ll_get_alarm_enable((hal)->dev, (hal)->idx)

/**
 * @brief 设置电平中断状态，启用或禁用电平中断。
 *
 * @param hal HAL层的上下文
 * @param level_int_en True表示启用电平中断，false表示禁用电平中断
 *
 * @return 没有一个
 */
#define timer_hal_set_level_int_enable(hal, level_int_en)  timer_ll_set_level_int_enable((hal)->dev, (hal)->idx, level_int_en)

/**
 * @brief 获取电平中断状态。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -真使能电平中断
 *     -false禁用级别中断
 */
#define timer_hal_get_level_int_enable(hal)  timer_ll_get_level_int_enable((hal)->dev, (hal)->idx)

/**
 * @brief 设置边缘中断状态，启用或禁用边缘中断。
 *
 * @param hal HAL层的上下文
 * @param edge_int_en True表示启用边缘中断，false表示禁用边缘中断
 *
 * @return 没有一个
 */
#define timer_hal_set_edge_int_enable(hal, edge_int_en)  timer_ll_set_edge_int_enable((hal)->dev, (hal)->idx, edge_int_en)

/**
 * @brief 获取边缘中断状态。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -true启用边缘中断
 *     -false禁用边缘中断
 */
#define timer_hal_get_edge_int_enable(hal)  timer_ll_get_edge_int_enable((hal)->dev, (hal)->idx)

/**
 * @brief 启用计时器中断。
 *
 * @param hal HAL层的上下文
 *
 * @return 没有一个
 */
#define timer_hal_intr_enable(hal)  timer_ll_intr_enable((hal)->dev, (hal)->idx)

/**
 * @brief 禁用计时器中断。
 *
 * @param hal HAL层的上下文
 *
 * @return 没有一个
 */
#define timer_hal_intr_disable(hal)  timer_ll_intr_disable((hal)->dev, (hal)->idx)

/**
 * @brief 清除中断状态。
 *
 * @param hal HAL层的上下文
 *
 * @return 没有一个
 */
#define timer_hal_clear_intr_status(hal)  timer_ll_clear_intr_status((hal)->dev, (hal)->idx)

/**
 * @brief 获取中断状态。
 *
 * @param hal HAL层的上下文
 * @param intr_status 中断状态
 *
 * @return 没有一个
 */
#define timer_hal_get_intr_status(hal, intr_status)  timer_ll_get_intr_status((hal)->dev, intr_status)

/**
 * @brief 获取中断原始状态。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param intr_raw_status 中断原始状态
 *
 * @return 没有一个
 */
#define timer_hal_get_intr_raw_status(group_num, intr_raw_status)  timer_ll_get_intr_raw_status(group_num, intr_raw_status)

/**
 * @brief 获取中断状态寄存器地址。
 *
 * @param hal HAL层的上下文
 *
 * @return 中断状态寄存器地址
 */
#define timer_hal_get_intr_status_reg(hal)  timer_ll_get_intr_status_reg((hal)->dev)

#if SOC_TIMER_GROUP_SUPPORT_XTAL
/**
 * @brief 设置时钟源。
 *
 * @param hal HAL层的上下文
 * @param use_xtal_en True表示使用XTAL时钟，flase表示使用APB时钟
 *
 * @return 没有一个
 */
#define timer_hal_set_use_xtal(hal, use_xtal_en)  timer_ll_set_use_xtal((hal)->dev, (hal)->idx, use_xtal_en)

/**
 * @brief 获取时钟源。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -true使用XTAL时钟
 *     -错误使用APB时钟
 */
#define timer_hal_get_use_xtal(hal)  timer_ll_get_use_xtal((hal)->dev, (hal)->idx)
#endif

#ifdef __cplusplus
}
#endif

