/**
 * \文件chacha20.h
 *
 * \brief此文件包含ChaCha20定义和函数。
 *
 *          ChaCha20是一种可以加密和解密信息的流密码。ChaCha由丹尼尔·伯恩斯坦（Daniel Bernstein）创建，作为其Salsa密码的变体https://cr.yp.to/chacha/chacha-20080128.pdfChaCha20是20发的变体，在RFC 7539中也进行了标准化。
 *
 * \作者丹尼尔·金<damaki.gh@gmail.com>
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

#ifndef MBEDTLS_CHACHA20_H
#define MBEDTLS_CHACHA20_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stdint.h>
#include <stddef.h>

/**输入参数无效。*/
#define MBEDTLS_ERR_CHACHA20_BAD_INPUT_DATA         -0x0051

/* MBEDTLS_ERROR_CHACHA20_FEATURE_NAVAILABLE已弃用，不应使用。*/
/**功能不可用。例如，API的s部分未实现。*/
#define MBEDTLS_ERR_CHACHA20_FEATURE_UNAVAILABLE    -0x0053

/* MBEDTLS_ERROR_CHACHA20_HW_ACCEL_FAILED已弃用，不应使用。
 */
/**Chacha20硬件加速器失败。*/
#define MBEDTLS_ERR_CHACHA20_HW_ACCEL_FAILED        -0x0055

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_CHACHA20_ALT)

typedef struct mbedtls_chacha20_context
{
    uint32_t state[16];          /*! 状态（循环操作之前）。*/
    uint8_t  keystream8[64];     /*! 剩余的密钥流字节。*/
    size_t keystream_bytes_used; /*! 已使用的密钥流字节数。*/
}
mbedtls_chacha20_context;

#else  /* MBEDTLS_CHACHA20_ALT */
#include "chacha20_alt.h"
#endif /* MBEDTLS_CHACHA20_ALT */

/**
 * \brief此函数初始化指定的ChaCha20上下文。
 *
 *                  它必须是在使用上下文之前调用的第一个API。
 *
 *                  后面通常是对\c mbedtls_chacha20_setkey（）和\c mbedls_hacha20_starts（）的调用，然后是对\cmbedtls_chacha20_update（）的一个或多个调用，最后是对\cembedtls_cha20_free（）的。
 *
 * \param ctx要初始化的ChaCha20上下文。此值不能为空。
 */
void mbedtls_chacha20_init( mbedtls_chacha20_context *ctx );

/**
 * \brief此函数释放并清除指定的ChaCha20上下文。
 *
 * \param ctx要清除的ChaCha20上下文。这可能是空的，在这种情况下，此函数是no-op。如果不是空，则必须指向已初始化的上下文。
 *
 */
void mbedtls_chacha20_free( mbedtls_chacha20_context *ctx );

/**
 * \brief此函数设置加密/解密密钥。
 *
 * \注意：使用此函数后，在开始使用\cmbedtls_chacha_update（）加密/解密数据之前，还必须调用\cmbedtls _chacha20_starts（）设置随机数。
 *
 * \param ctx键应绑定到的ChaCha20上下文。必须对其进行初始化。\param key加密/解密密钥。长度必须为\c 32字节。
 *
 * \成功时返回\c 0。\如果ctx或key为NULL，则返回#MBEDTLS_ERROR_CHACHA20_BAD_INPUT_DATA。
 */
int mbedtls_chacha20_setkey( mbedtls_chacha20_context *ctx,
                             const unsigned char key[32] );

/**
 * \brief此函数设置随机数和初始计数器值。
 *
 * \注意ChaCha20上下文可以通过调用此函数来更改nonce来与同一个键一起重新使用。
 *
 * \警告您决不能将同一个nonce与同一个key一起使用两次。这将使使用相同的随机数和密钥加密的消息的任何保密性保证无效。
 *
 * \param ctx随机数应绑定到的ChaCha20上下文。它必须初始化并绑定到密钥。\param nonce随机数。大小必须为\c 12字节。\param counter初始计数器值。这通常是\c 0。
 *
 * \成功时返回\c 0。\如果ctx或nonce为NULL，则返回#MBEDTLS_ERROR_CHACHA20_BAD_INPUT_DATA。
 */
int mbedtls_chacha20_starts( mbedtls_chacha20_context* ctx,
                             const unsigned char nonce[12],
                             uint32_t counter );

/**
 * \brief此函数用于加密或解密数据。
 *
 *                  由于ChaCha20是一种流密码，因此加密和解密数据时使用相同的操作。
 *
 * \注意\p输入和\p输出指针必须相等或指向非重叠缓冲区。
 *
 * \注意，必须至少调用一次\cmbedtls_chacha20_setkey（）和\cmbedtls _chacha20 _starts（）来设置上下文，然后才能调用此函数。
 *
 * \注意：可以连续多次调用此函数，以便使用相同的密钥和随机数分段加密解密数据。
 *
 * \param ctx用于加密或解密的ChaCha20上下文。它必须初始化并绑定到密钥和随机数。\param size输入数据的长度（字节）。\param input保存输入数据的缓冲区。如果“size==0”，则此指针可以为空。\param output保存输出数据的缓冲区。这必须能够容纳\p大小的字节。如果“size==0”，则此指针可以为空。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_chacha20_update( mbedtls_chacha20_context *ctx,
                             size_t size,
                             const unsigned char *input,
                             unsigned char *output );

/**
 * \brief此函数使用ChaCha20和给定的密钥和随机数对数据进行加密或解密。
 *
 *                  由于ChaCha20是一种流密码，因此加密和解密数据时使用相同的操作。
 *
 * \警告您不能多次使用同一（key，nonce）对。这将使使用相同的随机数和密钥加密的消息的任何保密性保证无效。
 *
 * \注意\p输入和\p输出指针必须相等或指向非重叠缓冲区。
 *
 * \param key加密/解密密钥。长度必须为\c 32字节。\param nonce随机数。大小必须为\c 12字节。\param counter初始计数器值。通常为\c 0.\param size输入数据的长度（以字节为单位）。\param input保存输入数据的缓冲区。如果“size==0”，则此指针可以为空。\param output保存输出数据的缓冲区。这必须能够容纳\p大小的字节。如果“size==0”，则此指针可以为空。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_chacha20_crypt( const unsigned char key[32],
                            const unsigned char nonce[12],
                            uint32_t counter,
                            size_t size,
                            const unsigned char* input,
                            unsigned char* output );

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要介绍ChaCha20检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_chacha20_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CHACHA20_H */

