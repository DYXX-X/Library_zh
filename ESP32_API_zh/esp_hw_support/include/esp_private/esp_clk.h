/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file 电子邮箱h
 *
 * 此文件包含时钟相关函数的声明。
 */

/**
 * @brief 获取RTC慢时钟的校准值
 *
 * 该值的格式与rtc_clk_cal返回的格式相同（微秒，Q13.19定点格式）。
 *
 * @return 启动时使用rtc_clk_cal获得的校准值
 */
uint32_t esp_clk_slowclk_cal_get(void);

/**
 * @brief 更新RTC慢时钟的校准值
 *
 * 该值的格式必须与rtc_clk_cal返回的格式相同（微秒，Q13.19定点格式）。计时函数（如gettimeofday）使用该值根据RTC计数器值计算当前时间。
 * @param value 使用rtc_clk_cal获得的校准值
 */
void esp_clk_slowclk_cal_set(uint32_t value);

/**
 * @brief 返回当前CPU时钟频率执行频率切换时，此频率可能会改变。然而，可以保证频率不会随临界截面而改变。
 *
 * @return CPU时钟频率（Hz）
 */
int esp_clk_cpu_freq(void);

/**
 * @brief 返回电流APB时钟频率
 *
 * 当执行频率切换时，该频率可能会改变。然而，可以保证频率不会随临界截面而改变。
 *
 * @return APB时钟频率，Hz
 */
int esp_clk_apb_freq(void);

/**
 * @brief 主XTAL的返回频率
 *
 * 主XTAL的频率可以自动检测或在编译时设置（请参阅CONFIG_ESP32_XTAL_FREQ_SEL sdkconfig选项）。在这两种情况下，此函数都会在运行时返回实际值。
 *
 * @return XTAL频率，单位：Hz
 */
int esp_clk_xtal_freq(void);


/**
 * @brief 读取RTC计数器的值，将其转换为微秒
 * @attention 当通过esp_clk_slowclk_cal_set函数更新RTC计数器的校准值时，此函数返回的值可能会突然改变。除非应用程序调用esp_clk_slowclk_cal_set，否则不会发生这种情况。在ESP-IDF中，ESP_clk_slowclk_cal_set仅在启动代码中调用。
 *
 * @return 值或RTC计数器，以微秒表示
 */
uint64_t esp_clk_rtc_time(void);

#ifdef __cplusplus
}
#endif

