/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <esp_err.h>
#include <esp_spi_flash.h> /* 在bootloader中包含错误值*/
#include "sdkconfig.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 通过发送RDID命令读取闪存ID（0x9F）
 * @return 闪存原始ID mfg_ID=（ID>>16）&0xFF；flash_id=id&0xffff；
 */
uint32_t bootloader_read_flash_id(void);

#if SOC_CACHE_SUPPORT_WRAP
/**
 * @brief 为指定的换行模式设置突发模式设置命令。
 *
 * @param mode 指定的扭曲模式。
 * @return 始终ESP_OK
 */
esp_err_t bootloader_flash_wrap_set(spi_flash_wrap_mode_t mode);
#endif

/**
  * @brief 解锁闪存写入保护。请不要在SDK中调用此函数。
  *
  * @note 这可以被重写，因为它的属性很弱。
  */
esp_err_t bootloader_flash_unlock(void);

/**
 * @brief XMC推荐的启动流程。在任何擦除/写入操作之前启动时调用。
 *
 * @return ESP_OK成功启动时，否则为ESP_FAIL（表示应在擦除/写入之前重新启动）。
 */
esp_err_t bootloader_flash_xmc_startup(void);

#ifdef __cplusplus
}
#endif

