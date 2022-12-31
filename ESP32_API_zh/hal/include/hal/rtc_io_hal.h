// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

// RTC IO主机的HAL层（公共部分）

#pragma once

#include <esp_err.h>
#if !CONFIG_IDF_TARGET_ESP32C3 && !CONFIG_IDF_TARGET_ESP32H2
#include "soc/soc_caps.h"
#include "hal/rtc_io_ll.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
/**
 * 选择rtcio函数。
 *
 * @note 在启用极板模拟功能之前，必须选择RTC功能。
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param func 选择引脚功能。
 */
#define rtcio_hal_function_select(rtcio_num, func) rtcio_ll_function_select(rtcio_num, func)

/**
 * 启用rtcio输出。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_output_enable(rtcio_num) rtcio_ll_output_enable(rtcio_num)

/**
 * 禁用rtcio输出。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_output_disable(rtcio_num) rtcio_ll_output_disable(rtcio_num)

/**
 * 设置RTCIO输出电平。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param level 0：输出低~0：输出高。
 */
#define rtcio_hal_set_level(rtcio_num, level) rtcio_ll_set_level(rtcio_num, level)

/**
 * 启用rtcio输入。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_input_enable(rtcio_num) rtcio_ll_input_enable(rtcio_num)

/**
 * 禁用rtcio输入。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_input_disable(rtcio_num) rtcio_ll_input_disable(rtcio_num)

/**
 * 获取RTCIO输入电平。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @return 0：输入低~0：输入高。
 */
#define rtcio_hal_get_level(rtcio_num) rtcio_ll_get_level(rtcio_num)

/**
 * @brief 设置RTC GPIO焊盘驱动能力。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param strength 衬垫的驱动能力。范围：0~3。
 */
#define rtcio_hal_set_drive_capability(rtcio_num, strength) rtcio_ll_set_drive_capability(rtcio_num, strength)

/**
 * @brief 获取RTC GPIO焊盘驱动功能。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @return 衬垫的驱动能力。范围：0~3。
 */
#define rtcio_hal_get_drive_capability(rtcio_num) rtcio_ll_get_drive_capability(rtcio_num)

/**
 * 设置RTCIO输出电平。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param level 0：输出低~0：输出高。
 */
#define rtcio_hal_set_level(rtcio_num, level) rtcio_ll_set_level(rtcio_num, level)

/**
 * 获取RTCIO输入电平。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @return 0：输入低~0：输入高。
 */
#define rtcio_hal_get_level(rtcio_num) rtcio_ll_get_level(rtcio_num)

/**
 * 设置RTC IO方向。
 *
 * 配置RTC IO方向，例如仅输出、仅输入、输出和输入。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param mode IO方向。
 */
void rtcio_hal_set_direction(int rtcio_num, rtc_gpio_mode_t mode);

/**
 * 将RTC IO方向设置为深度睡眠或禁用睡眠状态。
 *
 * 注意：ESP32支持INPUT_ONLY模式。ESP32S2支持INPUT_ONLY、OUTPUT_ONLY、INPUT_OUTPUT模式。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param mode IO方向。
 */
void rtcio_hal_set_direction_in_sleep(int rtcio_num, rtc_gpio_mode_t mode);

/**
 * RTC GPIO上拉启用。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_pullup_enable(rtcio_num) rtcio_ll_pullup_enable(rtcio_num)

/**
 * RTC GPIO上拉禁用。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_pullup_disable(rtcio_num) rtcio_ll_pullup_disable(rtcio_num)

/**
 * RTC GPIO下拉启用。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_pulldown_enable(rtcio_num) rtcio_ll_pulldown_enable(rtcio_num)

/**
 * RTC GPIO下拉禁用。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_pulldown_disable(rtcio_num) rtcio_ll_pulldown_disable(rtcio_num)

#endif // SOC_RTCIO_INPUT_OUTPUT_SUPPORTED

#if SOC_RTCIO_HOLD_SUPPORTED

/**
 * 启用RTC IO垫的强制保持功能。
 *
 * 启用HOLD功能将导致极板锁定当前状态，例如输入/输出启用、输入/输出值、功能、驱动强度值。当进入浅睡眠或深睡眠模式时，此功能非常有用，以防止引脚配置发生变化。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_hold_enable(rtcio_num) rtcio_ll_force_hold_enable(rtcio_num)

/**
 * 禁用RTC IO板上的保持功能
 *
 * @note 如果禁用键盘保持，则键盘的状态可能会在睡眠模式下更改。
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_hold_disable(rtcio_num) rtcio_ll_force_hold_disable(rtcio_num)

/**
 * 启用RTC IO焊盘的强制保持功能。
 *
 * 启用HOLD功能将导致极板锁定当前状态，例如输入/输出启用、输入/输出值、功能、驱动强度值。当进入浅睡眠或深睡眠模式时，此功能非常有用，以防止引脚配置发生变化。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_hold_all() rtcio_ll_force_hold_all()

/**
 * 禁用RTC IO焊盘上的保持功能。
 *
 * @note 如果禁用键盘保持，则键盘的状态可能会在睡眠模式下更改。
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_unhold_all() rtcio_ll_force_unhold_all()
#endif // SOC_RTCIO_HOLD_SUPPORTED

#if SOC_RTCIO_WAKE_SUPPORTED

/**
 * 启用唤醒功能，并为rtcio从浅睡眠状态设置唤醒类型。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param type  在高电平或低电平唤醒。
 */
#define rtcio_hal_wakeup_enable(rtcio_num, type) rtcio_ll_wakeup_enable(rtcio_num, type)

/**
 * 禁用rtcio的轻睡眠状态唤醒功能。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
#define rtcio_hal_wakeup_disable(rtcio_num) rtcio_ll_wakeup_disable(rtcio_num)

/**
 * 将RTC IO引脚上的特定逻辑电平设置为唤醒触发。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 * @param level 逻辑电平（0）
 */
#define rtcio_hal_ext0_set_wakeup_pin(rtcio_num, level)     rtcio_ll_ext0_set_wakeup_pin(rtcio_num, level)

#endif

#if SOC_RTCIO_HOLD_SUPPORTED || SOC_RTCIO_INPUT_OUTPUT_SUPPORTED

/**
 * 从RTC IO断开内部电路的辅助功能此功能禁用输入、输出、上拉、下拉，并启用RTC IO的保持功能。如果RTC IO需要在深度睡眠状态下从内部电路断开，请使用此功能，以最大限度地减少泄漏电流。
 *
 * 特别是，对于ESP32-WROVER模块，在进入深度睡眠之前调用rtc_gpio_isolate（gpio_NUM_12），以减少深度睡眠电流。
 *
 * @param rtcio_num rtcio的索引。0~SOC_RTCIO_PIN_COUNT。
 */
void rtcio_hal_isolate(int rtc_num);

#endif

#ifdef __cplusplus
}
#endif

