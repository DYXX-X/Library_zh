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

// 触摸传感器的HAL层（esp32特定部分）

#pragma once

#include "hal/touch_sensor_ll.h"
#include "hal/touch_sensor_types.h"

#include_next "hal/touch_sensor_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 设置触摸传感器测量时间。
 *
 * @param meas_time 触摸传感器测量的持续时间。t_meas=meas_time/（8MHz），最大测量时间为0xffff/8M=8.19ms。
 */
#define touch_hal_set_meas_time(meas_time) touch_ll_set_meas_time(meas_time)

/**
 * 获取触摸传感器测量时间。
 *
 * @param meas_time 接受测量周期计数的指针。
 */
#define touch_hal_get_meas_time(meas_time) touch_ll_get_meas_time(meas_time)

/**
 * 设置触摸传感器中断触发模式。当触摸值小于阈值或触摸值大于阈值时，可以触发中断。
 *
 * @param mode 触摸传感器中断触发模式。
 */
#define touch_hal_set_trigger_mode(mode) touch_ll_set_trigger_mode(mode)

/**
 * 获取触摸传感器中断触发模式。当触摸值小于阈值或触摸值大于阈值时，可以触发中断。
 *
 * @param mode 触摸传感器中断触发模式。
 */
#define touch_hal_get_trigger_mode(mode) touch_ll_get_trigger_mode(mode)

/**
 * 设置触摸传感器中断触发源。有两组触摸信号。Set1和set2可以被映射到多个触摸信号。如果至少有一个触摸信号被“触摸”，将触发任一组。可以将中断配置为在触发set1时生成，或者仅在触发两个集合时生成。
 *
 * @param src 触摸传感器中断触发源。
 */
#define touch_hal_set_trigger_source(src) touch_ll_set_trigger_source(src)

/**
 * 获取触摸传感器中断触发源。
 *
 * @param src 用于接受触摸传感器中断触发源的指针。
 */
#define touch_hal_get_trigger_source(src) touch_ll_get_trigger_source(src)

/**
 * 设置触摸传感器组掩码。触摸板模块有两组信号，只有当该组中至少一个触摸板被“触摸”时，才会触发“触摸”信号。此函数将根据给定的位掩码设置寄存器位。
 *
 * @param set1_mask 触摸传感器信号组1的位掩码，为10位值
 * @param set2_mask 触摸传感器信号组2的位掩码，为10位值
 */
#define touch_hal_set_group_mask(group1_mask, group2_mask) touch_ll_set_group_mask(group1_mask, group2_mask)

/**
 * 获取触摸传感器组掩码。
 *
 * @param set1_mask 用于接受触摸传感器信号组1的位掩码的指针，它是一个10位值
 * @param set2_mask 用于接受触摸传感器信号组2的位掩码的指针，它是一个10位值
 */
#define touch_hal_get_group_mask(group1_mask, group2_mask) touch_ll_get_group_mask(group1_mask, group2_mask)

/**
 * 清除触摸传感器组掩码。
 *
 * @param set1_mask 用于接受触摸传感器信号组1的位掩码的指针，它是一个10位值
 * @param set2_mask 用于接受触摸传感器信号组2的位掩码的指针，它是一个10位值
 */
#define touch_hal_clear_group_mask(group1_mask, group2_mask) touch_ll_clear_group_mask(group1_mask, group2_mask)

/**
 * 启用触摸板中断。
 */
#define touch_hal_intr_enable() touch_ll_intr_enable()

/**
 * 禁用触摸板中断。
 */
#define touch_hal_intr_disable() touch_ll_intr_disable()

/**
 * 清除触摸板中断。
 */
#define touch_hal_intr_clear() touch_ll_intr_clear()

/**
 * 获取导致从深度睡眠中醒来的触摸板。
 *
 * @param pad_num 导致唤醒的触摸板指针。
 */
void touch_hal_get_wakeup_status(touch_pad_t *pad_num);

#ifdef __cplusplus
}
#endif

