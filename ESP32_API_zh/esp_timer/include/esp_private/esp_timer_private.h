// 版权所有2017 Espressif Systems（上海）私人有限公司
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

#pragma once

/**
 * @file esp_private/esp_timer_private.h
 *
 * @brief esp_timer的公共部分和平台特定部分之间的接口。
 *
 * 此头文件中的函数是为每个受支持的SoC实现的。esp_timer中定义的高级函数。c调用此处的函数与硬件交互。
 *
 * 注意：此文件中的函数标记为专用，仅在电源管理和休眠文件中的IDF内部使用。
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 通知esp_timer实现APB频率已更改
 *
 * 由频率切换代码调用。
 *
 * @param apb_ticks_per_us 每微秒新的APB时钟周期数
 */
void esp_timer_private_update_apb_freq(uint32_t apb_ticks_per_us);

/**
 * @brief 将当前esp_timer时间调整一定值
 *
 * 从轻睡眠代码调用以将esp_timer时间与RTC时间同步。
 *
 * @param time_us  要应用于esp_timer时间的调整，以微秒为单位
 */
void esp_timer_private_advance(int64_t time_us);

/**
 * @brief 获取内部关键部分使用的esp_timer实现这可以在必须对esp_timeer进行一系列调用时使用，并且需要在调用之间保持计时器的状态一致。应该以与自旋锁相同的方式处理。调用esp_timer_unlock解除锁定
 */
void esp_timer_private_lock(void);

/**
 * @brief esp_timer_lock的对应项
 */
void esp_timer_private_unlock(void);

#ifdef __cplusplus
}
#endif

