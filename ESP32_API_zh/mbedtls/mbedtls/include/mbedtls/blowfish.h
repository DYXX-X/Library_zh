/**
 * \锉吹鱼.h
 *
 * \短Blowfish分组密码
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
#ifndef MBEDTLS_BLOWFISH_H
#define MBEDTLS_BLOWFISH_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#include "mbedtls/platform_util.h"

#define MBEDTLS_BLOWFISH_ENCRYPT     1
#define MBEDTLS_BLOWFISH_DECRYPT     0
#define MBEDTLS_BLOWFISH_MAX_KEY_BITS     448
#define MBEDTLS_BLOWFISH_MIN_KEY_BITS     32
#define MBEDTLS_BLOWFISH_ROUNDS      16         /**<要使用的轮次。增加该值时，确保扩展初始化向量*/
#define MBEDTLS_BLOWFISH_BLOCKSIZE   8          /* Blowfish使用64位块*/

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#define MBEDTLS_ERR_BLOWFISH_INVALID_KEY_LENGTH   MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( -0x0016 )
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
/**错误的输入数据。*/
#define MBEDTLS_ERR_BLOWFISH_BAD_INPUT_DATA -0x0016

/**数据输入长度无效。*/
#define MBEDTLS_ERR_BLOWFISH_INVALID_INPUT_LENGTH -0x0018

/* MBEDTLS_ERROR_BLOWFISH_HW_ACCEL_FAILED已弃用，不应使用。
 */
/**Blowfish硬件加速器失败。*/
#define MBEDTLS_ERR_BLOWFISH_HW_ACCEL_FAILED                   -0x0017

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_BLOWFISH_ALT)
// 定期实施
//

/**
 * \简要的Blowfish上下文结构
 */
typedef struct mbedtls_blowfish_context
{
    uint32_t P[MBEDTLS_BLOWFISH_ROUNDS + 2];    /*!<  吹鱼圆键*/
    uint32_t S[4][256];                 /*!<  依赖于密钥的S盒*/
}
mbedtls_blowfish_context;

#else  /* MBEDTLS_BLOWFISH_ALT */
#include "blowfish_alt.h"
#endif /* MBEDTLS_BLOWFISH_ALT */

/**
 * \brief初始化Blowfish上下文。
 *
 * \param ctx要初始化的Blowfish上下文。此值不能为空。
 */
void mbedtls_blowfish_init( mbedtls_blowfish_context *ctx );

/**
 * \brief清除Blowfish上下文。
 *
 * \param ctx要清除的Blowfish上下文。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空，则必须指向已初始化的Blowfish上下文。
 */
void mbedtls_blowfish_free( mbedtls_blowfish_context *ctx );

/**
 * \brief执行Blowfish键调度操作。
 *
 * \param ctx要对其执行密钥调度的Blowfish上下文。\param key加密密钥。这必须是长度为\p keybits Bits的可读缓冲区。\param keybits \p键的长度（以位为单位）。这必须介于\c 32和\c 448之间，并且是\c 8的倍数。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_blowfish_setkey( mbedtls_blowfish_context *ctx, const unsigned char *key,
                     unsigned int keybits );

/**
 * \brief执行Blowfish ECB块加密/解密操作。
 *
 * \param ctx要使用的Blowfish上下文。这必须初始化并绑定到密钥。\param mode操作模式。可能的值是用于加密的#MBEDTLS_BLOWFISH_ENCRYPT，或用于解密的#MBEDTLS_BLOWFISH_DECRYPT。\param input输入块。这必须是大小为\c 8字节的可读缓冲区。\param output输出块。这必须是大小为\c 8字节的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_blowfish_crypt_ecb( mbedtls_blowfish_context *ctx,
                        int mode,
                        const unsigned char input[MBEDTLS_BLOWFISH_BLOCKSIZE],
                        unsigned char output[MBEDTLS_BLOWFISH_BLOCKSIZE] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \brief执行Blowfish CBC缓冲区加密/解密操作。
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx要使用的Blowfish上下文。这必须初始化并绑定到密钥。\param mode操作模式。可能的值是用于加密的#MBEDTLS_BLOWFISH_ENCRYPT，或用于解密的#MBEDTLS_BLOWFISH_DECRYPT。\param length输入数据的长度（以字节为单位）。这必须是\c 8的倍数。\param iv初始化向量。这必须是长度为\c 8字节的读/写缓冲区。它由此函数更新。\param input输入数据。这必须是长度为\p-length Bytes的可读缓冲区。\param output输出数据。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_blowfish_crypt_cbc( mbedtls_blowfish_context *ctx,
                        int mode,
                        size_t length,
                        unsigned char iv[MBEDTLS_BLOWFISH_BLOCKSIZE],
                        const unsigned char *input,
                        unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
/**
 * \brief执行Blowfish CFB缓冲区加密/解密操作。
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx要使用的Blowfish上下文。这必须初始化并绑定到密钥。\param mode操作模式。可能的值是用于加密的#MBEDTLS_BLOWFISH_ENCRYPT，或用于解密的#MBEDTLS_BLOWFISH_DECRYPT。\param length输入数据的长度（以字节为单位）。\param iv_off初始化向量中的偏移量。指向的值必须小于\c 8字节。该功能会对其进行更新，以支持上述流媒体使用。\param iv初始化向量。这必须是大小为\c 8字节的读/写缓冲区。使用后更新。\param input输入数据。这必须是长度为\p-length Bytes的可读缓冲区。\param output输出数据。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_blowfish_crypt_cfb64( mbedtls_blowfish_context *ctx,
                          int mode,
                          size_t length,
                          size_t *iv_off,
                          unsigned char iv[MBEDTLS_BLOWFISH_BLOCKSIZE],
                          const unsigned char *input,
                          unsigned char *output );
#endif /*MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
/**
 * \brief执行Blowfish CTR缓冲区加密/解密操作。
 *
 * \警告您决不能使用同一密钥重复使用nonce值。这样做将使使用相同的随机数和密钥加密的两条消息的加密无效。
 *
 *             有两种常用的策略来管理CTR的随机数：
 *
 *             1.您可以将所有内容作为一条消息处理，该消息通过对该函数的连续调用进行处理。在这种情况下，您希望将第一次调用的\p nonce_counter和\p nc_off设置为0，然后在对该函数的调用中保留\p nonce _counter、\p nc_off和\p stream_block的值，因为它们将被该函数更新。
 *
 *             使用此策略，您不能使用同一密钥加密超过2**64个数据块。
 *
 *             2.您可以通过将\p nonce_counter缓冲区划分为两个区域来加密单独的消息：第一个区域用于您自己处理的每条消息nonce，第二个区域由此函数内部更新。
 *
 *             例如，您可以为每条消息的随机数保留前4个字节，为内部使用保留最后4个字节。在这种情况下，在对新消息调用此函数之前，需要将nonce_counter的前4个字节设置为所选的nonce值，将最后4个字节设为0，将nc_off设为0（这将导致忽略stream_block）。这样，您最多可以用相同的密钥加密232条消息，每个消息最多232个块。
 *
 *             每条消息的随机数（或足以重建它的信息）需要与密文通信，并且必须是唯一的。确保唯一性的建议方法是使用消息计数器。
 *
 *             请注意，对于这两种策略，大小都以块为单位，Blowfish块为8字节。
 *
 * \警告返回时，\p stream_block包含敏感数据。其内容不得写入不安全的存储，一旦不再需要，应立即安全丢弃。
 *
 * \param ctx要使用的Blowfish上下文。这必须初始化并绑定到密钥。\param length输入数据的长度（以字节为单位）。\param nc_off当前stream_block中的偏移量（用于在当前密码流中恢复）。偏移指针在流的开头应为\c 0，并且必须小于\c 8。此函数将更新它。\param nonce_counter 64位nonce和计数器。这必须指向长度为\c 8字节的读/写缓冲区。\param stream_block用于恢复的已保存流块。这必须指向长度为\c 8字节的读/写缓冲区。\param input输入数据。这必须是长度为\p-length Bytes的可读缓冲区。\param output输出数据。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_blowfish_crypt_ctr( mbedtls_blowfish_context *ctx,
                        size_t length,
                        size_t *nc_off,
                        unsigned char nonce_counter[MBEDTLS_BLOWFISH_BLOCKSIZE],
                        unsigned char stream_block[MBEDTLS_BLOWFISH_BLOCKSIZE],
                        const unsigned char *input,
                        unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CTR */

#ifdef __cplusplus
}
#endif

#endif /* 河豚鱼.h*/

