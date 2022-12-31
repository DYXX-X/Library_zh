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
 * @param input SHA输入描述符（outlink）
 * @return
 *      -ESP_OK：已成功启动DMA
 *      -ESP_ERR_INVALID_STATE:没有可用的DMA通道
 */
esp_err_t esp_sha_dma_start(const lldesc_t *input);


#ifdef __cplusplus
}
#endif

