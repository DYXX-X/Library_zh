/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "hal/xt_wdt_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    rtc_cntl_dev_t *dev;    /* 指向RTC寄存器结构的指针*/
} xt_wdt_hal_context_t;     /* HAL上下文结构*/

typedef struct {
    uint32_t timeout;       /* RTC_CLK周期中的看门狗计时器超时*/
} xt_wdt_hal_config_t;      /* HAL配置参数结构*/

/* ----------------------------初始化和配置---------------------------*/

/**
 * @brief 初始化WDT关联的HAL上下文
 *
 * 准备启用WDT的寄存器并设置超时值
 *
 * @param hal 指向HAL层上下文的指针
 * @param config 指向配置结构的指针
 */
void xt_wdt_hal_init(xt_wdt_hal_context_t *hal, const xt_wdt_hal_config_t *config);


/**
 * @brief 启用或禁用WDT
 *
 * @param hal 指向HAL层上下文的指针
 * @param enable true表示启用WDT，false表示禁用
 */
void xt_wdt_hal_enable(xt_wdt_hal_context_t *hal, bool enable);

/**
 * @brief 启用给定频率的自动RTC备份时钟
 *
 * 计算并设置必要的硬件参数，以满足所需的备份时钟频率
 *
 * @param hal 指向HAL层上下文的指针
 * @param rtc_clk_frequency_khz 备用时钟所需频率
 * @return uint32_t计算的时钟因子值
 */
uint32_t xt_wdt_hal_enable_backup_clk(xt_wdt_hal_context_t *hal, uint32_t rtc_clk_frequency_khz);

#ifdef __cplusplus
}
#endif

