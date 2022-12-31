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
 * @file esp32/rtc.h标准
 *
 * 此文件包含rtc相关函数的声明。
 */

/**
 * @brief 获取RTC计数器的当前值（以微秒为单位）
 *
 * 注意：执行此功能可能需要1个RTC_SLOW_CLK周期
 *
 * @return RTC计数器的当前值（微秒）
 */
uint64_t esp_rtc_get_time_us(void);

#ifdef __cplusplus
}
#endif

