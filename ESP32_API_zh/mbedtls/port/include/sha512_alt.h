/*
 *  添加了硬件ESP32支持的SHA-512实现。在使用并发SHA操作时，使用mbedTLS软件实现故障切换。
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
#ifndef _SHA512_ALT_H_
#define _SHA512_ALT_H_

#if defined(MBEDTLS_SHA512_ALT)

#include "hal/sha_types.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif


#if SOC_SHA_SUPPORT_PARALLEL_ENG

typedef enum {
    ESP_MBEDTLS_SHA512_UNUSED, /* 第一个块尚未处理*/
    ESP_MBEDTLS_SHA512_HARDWARE, /* 使用硬件SHA引擎*/
    ESP_MBEDTLS_SHA512_SOFTWARE, /* 使用软件SHA*/
} esp_mbedtls_sha512_mode;

/**
 * \SHA-512上下文结构简介
 */
typedef struct {
    uint64_t total[2];          /*!< 处理的字节数*/
    uint64_t state[8];          /*!< 中间消化状态*/
    unsigned char buffer[128];  /*!< 正在处理的数据块*/
    int is384;                  /*!< 0=>SHA-512，否则为SHA-384*/
    esp_mbedtls_sha512_mode mode;
} mbedtls_sha512_context;

#elif SOC_SHA_SUPPORT_DMA

typedef enum {
    ESP_SHA512_STATE_INIT,
    ESP_SHA512_STATE_IN_PROCESS
} esp_sha512_state;

/**
 * \SHA-512上下文结构简介
 */
typedef struct {
    uint64_t total[2];          /*!< 处理的字节数*/
    uint64_t state[8];          /*!< 中间消化状态*/
    unsigned char buffer[128];  /*!< 正在处理的数据块*/
    int first_block;
    esp_sha_type mode;
    uint32_t t_val;             /*!< 512/t模式的t_val*/
    esp_sha512_state sha_state;
} mbedtls_sha512_context;

/**
 * @brief 设置SHA512的特定算法
 *
 * @param ctx mbedtls sha512上下文
 *
 * @param type 用于设置SHA2_512224和SHA2_512256的模式：
 *
 */
void esp_sha512_set_mode(mbedtls_sha512_context *ctx, esp_sha_type type);

/* 对于SHA512/t模式，初始哈希值将取决于t*/
void esp_sha512_set_t( mbedtls_sha512_context *ctx, uint16_t t_val);


#endif

#endif

#ifdef __cplusplus
}
#endif

#endif

