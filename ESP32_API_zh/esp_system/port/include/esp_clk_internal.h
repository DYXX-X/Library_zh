// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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
 * @file esp_clk_内部.h
 *
 * 专用时钟相关功能
 */

/**
 * @brief 初始化时钟相关设置
 *
 * 从cpu_start调用。c、 不打算从其他地方调用。此功能配置CPU时钟、RTC慢时钟和快时钟，并执行RTC慢时钟校准。
 */
void esp_clk_init(void);


/**
 * @brief 禁用某些外围设备的时钟
 *
 * 从cpu_start调用。c、 不打算从其他地方调用。此功能在cpu启动时禁用无用外设的时钟。
 */
void esp_perip_clk_init(void);

/* 为RTC选择外部时钟源（32 kHz）。仅在单元测试中内部使用。
 */
void rtc_clk_select_rtc_slow_clk(void);

