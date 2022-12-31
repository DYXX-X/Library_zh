/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#include "esp_image_format.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 更新g_rom_flashchip（全局esp_rom_spiflash_chip_t结构）中的闪存id。
 *
 * @return 没有一个
 */
void bootloader_flash_update_id(void);

/**
 * @brief 更新g_rom_flashchip（全局esp_rom_spiflash_chip_t结构）中的闪存大小。
 *
 * @param size 要存储的大小（以字节为单位）。
 * @return 没有一个
 */
void bootloader_flash_update_size(uint32_t size);

/**
 * @brief 设置闪光CS设置和保持时间。
 *
 * @note CS设置时间建议为1.5T，CS保持时间建议为2.5T。cs_setup=1，cs_setup_time=0；cs_hold=1，cs_hold_time=1。
 *
 * @return 没有一个
 */
void bootloader_flash_cs_timing_config(void);

/**
 * @brief 配置SPI闪存时钟。
 *
 * @note 此函数仅为SPI0设置时钟频率。
 *
 * @param pfhdr 指向应用程序图像标题的指针，从中获取闪存设置。
 *
 * @return 没有一个
 */
void bootloader_flash_clock_config(const esp_image_header_t* pfhdr);

/**
 * @brief 配置SPI闪存gpio，包括IO矩阵和驱动器强度配置。
 *
 * @param pfhdr 指向应用程序图像标题的指针，从中获取闪存设置。
 *
 * @return 没有一个
 */
void bootloader_flash_gpio_config(const esp_image_header_t* pfhdr);

/**
 * @brief 根据不同的模式和频率配置SPI闪存读伪。
 *
 * @param pfhdr 指向应用程序图像标题的指针，从中获取闪存设置。
 *
 * @return 没有一个
 */
void bootloader_flash_dummy_config(const esp_image_header_t* pfhdr);

#ifdef CONFIG_IDF_TARGET_ESP32
/**
 * @brief 返回用于自定义SPI闪存和/或SPIRAM WP引脚的引脚号
 *
 * 在大多数情况下可由eFuse值确定，或在配置中被覆盖
 *
 * 只有当其他SPI闪存引脚通过eFuse被覆盖时，该值才有意义。
 *
 * 仅当闪存设置为QIO或QOUT模式，或启用SPIRAM时，此值才有意义。
 *
 * @return 要使用的端号，如果应保留默认值，则为-1
 */
int bootloader_flash_get_wp_pin(void);
#endif

#ifdef __cplusplus
}
#endif

