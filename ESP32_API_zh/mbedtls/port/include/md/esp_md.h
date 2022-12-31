// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和

#pragma once

#include "esp_rom_md5.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MD5Context mbedtls_md5_context;

/**
 * \brief初始化MD5上下文
 *
 * \param ctx要初始化的MD5上下文
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int esp_md5_init_ret( mbedtls_md5_context *ctx );

/**
 * \简要清除MD5上下文
 *
 * \param ctx要清除的MD5上下文
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void esp_md5_free( mbedtls_md5_context *ctx );

/**
 * \简要克隆MD5上下文（的状态）
 *
 * \param dst目标上下文\param src要克隆的上下文
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void esp_md5_clone( mbedtls_md5_context *dst, const mbedtls_md5_context *src );

/**
 * \简短的MD5进程缓冲区
 *
 * \param ctx MD5上下文\param保存数据的输入缓冲区\param输入数据的长度
 *
 * \如果成功，则返回0
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int esp_md5_update_ret( mbedtls_md5_context *ctx, const unsigned char *input, size_t ilen );

/**
 * \简短的MD5最终摘要
 *
 * \param ctx MD5上下文\param输出MD5校验和结果
 *
 * \如果成功，则返回0
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int esp_md5_finish_ret( mbedtls_md5_context *ctx, unsigned char output[16] );

/**
 * \简短的MD5进程数据块（仅供内部使用）
 *
 * \param ctx MD5上下文\param保存一个数据块的数据缓冲区
 *
 * \如果成功，则返回0
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int esp_md5_process( mbedtls_md5_context *ctx, const unsigned char data[64] );

/**
 * \简单的MD5上下文设置
 *
 * \已弃用在2.7.0中被mbedtls_md5_starts_ret（）取代
 *
 * \要初始化的param ctx上下文
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void esp_md5_init( mbedtls_md5_context *ctx );

/**
 * \简短的MD5进程缓冲区
 *
 * \已弃用2.7.0中的mbedtls_md5_update_ret（）取代
 *
 * \param ctx MD5上下文\param保存数据的输入缓冲区\param输入数据的长度
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void esp_md5_update( mbedtls_md5_context *ctx, const unsigned char *input, size_t ilen );

/**
 * \简短的MD5最终摘要
 *
 * \已弃用2.7.0中的mbedtls_md5_finish_ret（）取代
 *
 * \param ctx MD5上下文\param输出MD5校验和结果
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void esp_md5_finish( mbedtls_md5_context *ctx, unsigned char output[16] );

#ifdef __cplusplus
}
#endif

