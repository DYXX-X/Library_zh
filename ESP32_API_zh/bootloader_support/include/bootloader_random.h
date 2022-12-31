/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 如果RF被禁用，则为RNG启用熵源
 *
 * 确切的内部熵源机制取决于所使用的芯片，但所有SoC都使用SAR ADC将随机比特（内部噪声读数）连续混合到HWRNG中。有关更多信息，请参阅SoC技术参考手册。
 *
 * 如果在RF初始化之前需要真正的随机数，也可以在操作早期从应用程序代码中使用。有关详细信息，请参阅ESP-IDF编程指南“随机数生成”部分。
 */
void bootloader_random_enable(void);

/**
 * @brief 禁用RNG的熵源
 *
 * 禁用内部熵源。必须在bootloader_random_enable（）之后以及RF功能、ADC或I2S（仅限ESP32）初始化之前调用。
 *
 * 有关详细信息，请参阅ESP-IDF编程指南“随机数生成”部分。
 */
void bootloader_random_disable(void);

/**
 * @brief 用“length”随机字节填充缓冲区
 *
 * @note 如果该函数仅从应用程序代码调用，而不是从引导加载程序调用，那么最好调用esp_fill_random（）。
 *
 * @param buffer 指向缓冲区的指针
 * @param length 这许多字节的随机数据将被复制到缓冲区
 */
void bootloader_fill_random(void *buffer, size_t length);

#ifdef __cplusplus
}
#endif

