/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include "esp_err.h"
#include "esp_image_format.h"

/**@{*/
/**
 * @brief bootloader链接器脚本中的标签：bootloader.ld
 *
 */
extern int _bss_start;
extern int _bss_end;
extern int _data_start;
extern int _data_end;
/**@}*/

/**
 * @brief 引导加载程序映像标头
 *
 */
extern esp_image_header_t bootloader_image_hdr;

/**@{*/
/**
 * @brief 应用于所有目标的通用初始化步骤。
 *
 */
esp_err_t bootloader_read_bootloader_header(void);
esp_err_t bootloader_check_bootloader_validity(void);
void bootloader_clear_bss_section(void);
void bootloader_config_wdt(void);
void bootloader_enable_random(void);
void bootloader_print_banner(void);
/**@}*/

/* @brief 为工作准备硬件。
 *
 * 设置：
 * -禁用两个CPU的缓存访问；
 * -初始化缓存mmu；
 * -设置SD、SPI、UART、时钟的引脚和模式。

 *  @return ESP_OK-如果设置成功。ESP_FAIL-如果设置不成功。
 */
esp_err_t bootloader_init(void);

