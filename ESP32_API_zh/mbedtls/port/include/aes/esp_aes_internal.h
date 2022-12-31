/**
 * \基于mbedTLS FIPS-197兼容版本的ESP-IDF硬件加速版本。
 *
 *  版权所有（C）2006-2015，ARM Limited，保留所有权利添加版权所有（C）2016，Espressif Systems（Shanghai）PTE Ltd SPDX License Identifier:Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  内部API
 */

#pragma once


#include "aes/esp_aes.h"
#include "aes/esp_aes_gcm.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool valid_key_length(const esp_aes_context *ctx);


/**
 * @brief           使用DMA运行AES-GCM转换
 *
 * @param ctx       Aes上下文
 * @param input     指向输入数据的指针
 * @param output    指向输出数据的指针
 * @param len       输入数据的长度
 * @param aad_desc  GCM附加数据DMA描述符
 * @param aad_len   GCM附加数据长度
 * @return int-1出错
 */
int esp_aes_process_dma_gcm(esp_aes_context *ctx, const unsigned char *input, unsigned char *output, size_t len, lldesc_t *aad_desc, size_t aad_len);


#ifdef __cplusplus
}
#endif

