/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>

#include "esp_err.h"
#include "esp_intr_alloc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief esp_xt_wdt配置结构
 *
 */
typedef struct {
    uint8_t timeout;                /*!< 看门狗超时*/
    bool auto_backup_clk_enable;    /*!< 在超时时启用自动切换到备份时钟*/
} esp_xt_wdt_config_t;

/*  WDT中断的回调函数*/
typedef void (*esp_xt_callback_t)(void *arg);

/**
 * @brief 初始化xtal32k看门狗计时器
 *
 * @param cfg 指向配置结构的指针
 * @return 电子邮箱地址
 *      -ESP_OK:XTWDT已成功启用
 *      -ESP_ERR_NO_MEM:分配ISR失败
 */
esp_err_t esp_xt_wdt_init(const esp_xt_wdt_config_t *cfg);

/**
 * @brief 注册一个回调函数，当看门狗超时时将调用该函数。
 *
 * @note 此函数将从可能禁用缓存的中断上下文中调用。因此，该功能应置于IRAM中，不得执行任何阻塞操作。
 *
 *       只能注册一个回调函数，对esp_xt_wdt_register_callback的任何调用都将覆盖先前的回调函数。
 *
 * @param func 要注册的回调函数
 * @param arg  指向将传递给回调函数的参数的指针
 */
void esp_xt_wdt_register_callback(esp_xt_callback_t func, void *arg);

/**
 * @brief 恢复xtal32k时钟并重新启用WDT
 *
 */
void esp_xt_wdt_restore_clk(void);

#ifdef __cplusplus
}
#endif

