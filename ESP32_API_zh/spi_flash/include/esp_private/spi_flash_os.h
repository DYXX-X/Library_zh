/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * 系统级MSPI API（专用）
 */
/**
 * 目前，MSPI定时调整相关API设计为专用。因为：1.现在我们没有拆分SPI0和SPI1，我们没有SPI0的组件，包括PSRAM、Cache等。2.SPI0和SPI1是强耦合的。
 *
 * 将来，我们可能会考虑为SPI0创建一个组件，而spi_flash组件将只在SPI1上工作（它可以依赖于SPI0）。因此，我们可以将这些API放在那里。
 *
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "esp_err.h"
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/spi_flash.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/spi_flash.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/spi_flash.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/spi_flash.h"
#endif
#include "esp_flash.h"
#include "hal/spi_flash_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置闪存芯片
 */
esp_err_t spi_flash_init_chip_state(void);

/**
 * @brief 使MSPI在20Mhz下工作，消除定时调谐所需的延迟。
 * @param control_spi1  选择是否控制SPI1。对于调整，我们需要使用SPI1。调整后（在启动阶段），让闪存驱动程序控制SPI1
 */
void spi_timing_enter_mspi_low_speed_mode(bool control_spi1);

/**
 * @brief 使MSPI在用户设置的频率下工作，可能会给MSPI RX方向增加某些延迟，以满足定时要求。
 * @param control_spi1  选择是否控制SPI1。对于调整，我们需要使用SPI1。调整后（在启动阶段），让闪存驱动程序控制SPI1
 */
void spi_timing_enter_mspi_high_speed_mode(bool control_spi1);

/**
 * @brief 将MSPI切换到低速模式/高速模式。
 * @note 此API是缓存安全的，它将冻结D$和I$，并在切换MSPI后恢复它们
 * @note 对于某些MSPI高频设置（例如80M DDR模式闪存或PSRAM），需要进行定时调整。MSPI RX方向将增加某些延迟。当CPU时钟从PLL切换到XTAL时，应首先调用此API以进入MSPI低速模式以消除延迟，反之亦然。
 */
void spi_timing_change_speed_mode_cache_safe(bool switch_down);

/**
 * @brief 调整MSPI闪光定时，使其在高频下工作
 */
void spi_timing_flash_tuning(void);

/**
 * @brief 调整MSPI psram定时，使其在高频下工作
 */
void spi_timing_psram_tuning(void);

/**
 * @brief 初始化MSPI引脚
 */
void esp_mspi_pin_init(void);

/**
 * @brief 设置SPI1寄存器以使ROM功能正常工作
 * @note 此函数用于将SPI1寄存器设置为ROM SPI功能工作的状态
 */
void spi_flash_set_rom_required_regs(void);

/**
 * @brief 初始化主闪存
 * @param chip 指向要使用的主SPI闪存（SPI1 CS0）芯片的指针。。
 */
esp_err_t esp_flash_init_main(esp_flash_t *chip);

/**
 * @brief 应仅由SPI1闪存驱动程序使用，以了解必要的定时寄存器
 * @param out_timing_config 指向timing_tuning参数的指针。
 */
void spi_timing_get_flash_timing_param(spi_flash_hal_timing_config_t *out_timing_config);

/**
 * @brief 了解MSPI定时是否调整
 */
bool spi_timing_is_tuned(void);

/**
 * @brief 在此处设置闪存芯片特别需要的MSPI寄存器设置
 */
void spi_flash_set_vendor_required_regs(void);


#ifdef __cplusplus
}
#endif

