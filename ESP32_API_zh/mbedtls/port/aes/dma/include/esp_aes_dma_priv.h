// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "soc/lldesc.h"
#include "soc/soc_caps.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 启动DMA引擎
 *
 * @param input AES输入描述符（outlink）
 * @param output AES输出描述符（内联）
 * @return
 *      -ESP_OK：已成功启动DMA
 *      -ESP_ERR_INVALID_STATE:没有可用的DMA通道
 */
esp_err_t esp_aes_dma_start(const lldesc_t *input, const lldesc_t *output);

/**
 * @brief 检查DMA引擎是否已完成读取结果
 *
 * @param output AES输出描述符（内联）
 * @return
 *      -true：DMA已完成
 *      -false：DMA尚未完成
 */
bool esp_aes_dma_done(const lldesc_t *output);

#ifdef __cplusplus
}
#endif

