/*
 *  添加了硬件ESP32支持的SHA-1实现。在使用并发SHA操作时，使用mbedTLS软件实现故障切换。
 *
 *  版权所有（C）2006-2015，ARM有限公司，保留所有权利。补充版权（C）2016，Espressif Systems（Shanghai）PTE LTD SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 */
#ifndef _SHA1_ALT_H_
#define _SHA1_ALT_H_

#if defined(MBEDTLS_SHA1_ALT)

#include "hal/sha_types.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_SHA_SUPPORT_PARALLEL_ENG

typedef enum {
    ESP_MBEDTLS_SHA1_UNUSED, /* 第一个块尚未处理*/
    ESP_MBEDTLS_SHA1_HARDWARE, /* 使用硬件SHA引擎*/
    ESP_MBEDTLS_SHA1_SOFTWARE, /* 使用软件SHA*/
} esp_mbedtls_sha1_mode;

/**
 * \简短的SHA-1上下文结构
 */
typedef struct {
    uint32_t total[2];          /*!< 处理的字节数*/
    uint32_t state[5];          /*!< 中间消化状态*/
    unsigned char buffer[64];   /*!< 正在处理的数据块*/
    esp_mbedtls_sha1_mode mode;
} mbedtls_sha1_context;

#elif SOC_SHA_SUPPORT_DMA

typedef enum {
    ESP_SHA1_STATE_INIT,
    ESP_SHA1_STATE_IN_PROCESS
} esp_sha1_state;

/**
 * \简短的SHA-1上下文结构
 */
typedef struct {
    uint32_t total[2];          /*!< 处理的字节数*/
    uint32_t state[5];          /*!< 中间消化状态*/
    unsigned char buffer[64];   /*!< 正在处理的数据块*/
    int first_block;            /*!< 如果先为真，否则为假*/
    esp_sha_type mode;
    esp_sha1_state sha_state;
} mbedtls_sha1_context;

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif

