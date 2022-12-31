/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  从硬件RNG获取一个随机32位字
 *
 * 如果启用了Wi-Fi或蓝牙，此函数将返回真实的随机数。在其他情况下，如果需要真正的随机数，请参阅ESP-IDF编程指南“随机数生成”部分了解必要的先决条件。
 *
 * 该函数在返回新的随机数之前，会自动忙等待，以确保在硬件RNG状态中引入了足够的外部熵。此延迟非常短（总是小于100个CPU周期）。
 *
 * @return 0和UINT32_MAX之间的随机值
 */
uint32_t esp_random(void);

/**
 * @brief 用硬件RNG中的随机字节填充缓冲区
 *
 * @note 此函数是通过调用esp_random（）实现的，因此应用相同的约束。
 *
 * @param buf 指向要用随机数填充的缓冲区的指针。
 * @param len 缓冲区长度（字节）
 */
void esp_fill_random(void *buf, size_t len);

#ifdef __cplusplus
}
#endif

