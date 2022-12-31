/**
 * \文件cam茶花.h
 *
 * \简单茶花分组密码
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#ifndef MBEDTLS_CAMELLIA_H
#define MBEDTLS_CAMELLIA_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#include "mbedtls/platform_util.h"

#define MBEDTLS_CAMELLIA_ENCRYPT     1
#define MBEDTLS_CAMELLIA_DECRYPT     0

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#define MBEDTLS_ERR_CAMELLIA_INVALID_KEY_LENGTH   MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( -0x0024 )
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
/**错误的输入数据。*/
#define MBEDTLS_ERR_CAMELLIA_BAD_INPUT_DATA -0x0024

/**数据输入长度无效。*/
#define MBEDTLS_ERR_CAMELLIA_INVALID_INPUT_LENGTH -0x0026

/* MBEDTLS_ERROR_CAMELLIA_WW_ACCEL_FAILED已弃用，不应使用。
 */
/**Camellia硬件加速器失败。*/
#define MBEDTLS_ERR_CAMELLIA_HW_ACCEL_FAILED              -0x0027

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_CAMELLIA_ALT)
// 定期实施
//

/**
 * \简短的CAMELLIA上下文结构
 */
typedef struct mbedtls_camellia_context
{
    int nr;                     /*!<  轮数*/
    uint32_t rk[68];            /*!<  CAMELLIA圆形钥匙*/
}
mbedtls_camellia_context;

#else  /* MBEDTLS_CAMELLIA_ALT */
#include "camellia_alt.h"
#endif /* MBEDTLS_CAMELLIA_ALT */

/**
 * \brief初始化CAMELLIA上下文。
 *
 * \param ctx要初始化的CAMELLIA上下文。此值不能为空。
 */
void mbedtls_camellia_init( mbedtls_camellia_context *ctx );

/**
 * \brief清除CAMELLIA上下文。
 *
 * \param ctx要清除的CAMELLIA上下文。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空值，则必须对其进行初始化。
 */
void mbedtls_camellia_free( mbedtls_camellia_context *ctx );

/**
 * \brief为加密执行CAMELLIA密钥调度操作。
 *
 * \param ctx要使用的CAMELLIA上下文。必须对其进行初始化。\param key要使用的加密密钥。这必须是大小为\p keybits Bits的可读缓冲区。\param keybits \p键的长度（以位为单位）。这必须是\c 128、\c 192或\c 256。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_camellia_setkey_enc( mbedtls_camellia_context *ctx,
                                 const unsigned char *key,
                                 unsigned int keybits );

/**
 * \brief执行CAMELLIA密钥调度操作以进行解密。
 *
 * \param ctx要使用的CAMELLIA上下文。必须对其进行初始化。\param key解密密钥。这必须是大小为\p keybits Bits的可读缓冲区。\param keybits \p键的长度（以位为单位）。这必须是\c 128、\c 192或\c 256。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_camellia_setkey_dec( mbedtls_camellia_context *ctx,
                                 const unsigned char *key,
                                 unsigned int keybits );

/**
 * \brief执行CAMELLIA-ECB块加密/解密操作。
 *
 * \param ctx要使用的CAMELLIA上下文。这必须初始化并绑定到密钥。\param mode操作模式。这必须是#MBEDTLS_NAMELLIA_ENCRYPT或#MBEDLLS_NAMELLAA_DECRYPT。\param input输入块。这必须是大小为\c 16字节的可读缓冲区。\param output输出块。这必须是大小为\c 16字节的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_camellia_crypt_ecb( mbedtls_camellia_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \brief执行CAMELLIA-CBC缓冲区加密/解密操作。
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx要使用的CAMELLIA上下文。这必须初始化并绑定到密钥。\param mode操作模式。这必须是#MBEDTLS_NAMELLIA_ENCRYPT或#MBEDLLS_NAMELLAA_DECRYPT。\param length输入数据的长度，以字节为单位。这必须是\c 16字节的倍数。\param iv初始化向量。这必须是长度为\c 16字节的读/写缓冲区。它被更新以允许如上所述的流媒体使用。\param input保存输入数据的缓冲区。这必须指向长度为\p-length Bytes的可读缓冲区。\param output保存输出数据的缓冲区。这必须指向长度为\p-length Bytes的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_camellia_crypt_cbc( mbedtls_camellia_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
/**
 * \brief执行CAMELLIA-CFB128缓冲区加密/解密操作。
 *
 * \注意：由于CFB模式的性质，您应该使用相同的密钥进行加密和解密。特别是，调用此函数之前应通过mbedtls_camellia_setkey_enc（）进行键调度，而不管\p模式是#mbedtls_camellia_ENCRYPT还是#mbedtls_AMELLIA_DECRYPT。
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx要使用的CAMELLIA上下文。这必须初始化并绑定到密钥。\param mode操作模式。这必须是#MBEDTLS_NAMELLIA_ENCRYPT或#MBEDLLS_NAMELLAA_DECRYPT。\param length输入数据的长度。允许任何值。\param iv_off iv中的当前偏移量。这必须小于\c 16字节。在该调用之后，它将被更新，以允许使用上述流媒体。\param iv初始化向量。这必须是长度为\c 16字节的读/写缓冲区。在该调用之后，它将被更新，以允许使用上述流媒体。\param input保存输入数据的缓冲区。这必须是大小为\p长度为Bytes的可读缓冲区。\param output保存输出数据的缓冲区。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_camellia_crypt_cfb128( mbedtls_camellia_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
/**
 * \brief执行CAMELLIA-CTR缓冲区加密/解密操作。
 *
 * *注意：由于CTR模式的性质，您应该使用相同的密钥进行加密和解密。特别是，调用此函数之前应通过mbedtls_camellia_setkey_enc（）进行键调度，而不管\p模式是#mbedtls_camellia_ENCRYPT还是#mbedtls_AMELLIA_DECRYPT。
 *
 * \警告您决不能使用同一密钥重复使用nonce值。这样做将使使用相同的随机数和密钥加密的两条消息的加密无效。
 *
 *             有两种常用的策略来管理CTR的随机数：
 *
 *             1.您可以将所有内容作为一条消息处理，该消息通过对该函数的连续调用进行处理。在这种情况下，您希望将第一次调用的\p nonce_counter和\p nc_off设置为0，然后在对该函数的调用中保留\p nonce _counter、\p nc_off和\p stream_block的值，因为它们将被该函数更新。
 *
 *             使用此策略，您不能使用同一密钥加密超过2**128个数据块。
 *
 *             2.您可以通过将\p nonce_counter缓冲区划分为两个区域来加密单独的消息：第一个区域用于您自己处理的每条消息nonce，第二个区域由此函数内部更新。
 *
 *             例如，您可以将前一个\c 12字节保留为每条消息随机数，最后一个\c4字节保留为内部使用。在这种情况下，在对新消息调用此函数之前，您需要将nonce_counter的前个\c 12字节设置为所选的nonce值，最后四个字节设置为\c 0，将nc_off设置为\c0（这将导致\p stream_block被忽略）。这样，您最多可以用同一密钥加密多达232个块的296条消息。
 *
 *             每条消息的随机数（或足以重建它的信息）需要与密文通信，并且必须是唯一的。确保唯一性的建议方法是使用消息计数器。另一种方法是生成随机随机数，但这限制了可以安全加密的消息数量：例如，使用96位随机随机数时，使用相同密钥加密的消息不应超过232条。
 *
 *             请注意，对于这两种策略，大小以块为单位，CAMELLIA块为\c 16字节。
 *
 * \警告返回时，\p stream_block包含敏感数据。其内容不得写入不安全的存储，一旦不再需要，应立即安全丢弃。
 *
 * \param ctx要使用的CAMELLIA上下文。这必须初始化并绑定到密钥。\param length输入数据的长度，以字节为单位。允许任何值。\param nc_off当前流块中的偏移量（用于在当前密码流中恢复）。指向的偏移指针应位于流的开头。此呼叫结束时更新。\param nonce_counter 128位的nonce和计数器。这必须是长度为\c 16字节的读/写缓冲区。\param stream_block用于恢复的已保存流块。这必须是长度为\c 16字节的读/写缓冲区。\param input输入数据流。这必须是大小为\p长度为Bytes的可读缓冲区。\param output输出数据流。这必须是大小为\p长度为Bytes的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_camellia_crypt_ctr( mbedtls_camellia_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CTR */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_camellia_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 山茶*/

