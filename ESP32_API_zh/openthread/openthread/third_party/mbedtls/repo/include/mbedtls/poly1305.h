/**
 * \文件poly1305.h
 *
 * \brief此文件包含Poly1305定义和函数。
 *
 *          Poly1305是一个一次性消息验证器，可用于验证消息。Poly1305 AES由Daniel Bernstein创建https://cr.yp.to/mac/poly1305-20050329.pdf通用Poly1305算法（与AES无关）也在RFC 7539中进行了标准化。
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

#ifndef MBEDTLS_POLY1305_H
#define MBEDTLS_POLY1305_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stdint.h>
#include <stddef.h>

#define MBEDTLS_ERR_POLY1305_BAD_INPUT_DATA         -0x0057 /**<输入参数无效。*/

/* MBEDTLS_ERROR_POLY1305_FEATURE_NAVAILABLE已弃用，不应使用。*/
#define MBEDTLS_ERR_POLY1305_FEATURE_UNAVAILABLE    -0x0059 /**<功能不可用。例如，API的s部分未实现。*/

/* MBEDTLS_ERROR_POLY1305_HW_ACCEL_FAILED已弃用，不应使用。
 */
#define MBEDTLS_ERR_POLY1305_HW_ACCEL_FAILED        -0x005B  /**<Poly1305硬件加速器失败。*/

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_POLY1305_ALT)

typedef struct mbedtls_poly1305_context
{
    uint32_t r[4];      /**“r”的值（键的低128位）。*/
    uint32_t s[4];      /**“s”的值（键的高128位）。*/
    uint32_t acc[5];    /**累加器编号。*/
    uint8_t queue[16];  /**当前部分数据块。*/
    size_t queue_len;   /**“队列”中存储的字节数。*/
}
mbedtls_poly1305_context;

#else  /* MBEDTLS_POLY1305_ALT */
#include "poly1305_alt.h"
#endif /* MBEDTLS_POLY1305_ALT */

/**
 * \brief此函数初始化指定的Poly1305上下文。
 *
 *                  它必须是在使用上下文之前调用的第一个API。
 *
 *                  后面通常是对\c mbedtls_poly1305_starts（）的调用，然后是对\cmbedtls_proly1305_update（）的一个或多个调用，然后调用\c mbedt ls_poly1305_finish（），最后是\c mbeds ls_poly 1305_free（）。
 *
 * \param ctx要初始化的Poly1305上下文。此值不能为空。
 */
void mbedtls_poly1305_init( mbedtls_poly1305_context *ctx );

/**
 * \brief此函数释放并清除指定的Poly1305上下文。
 *
 * \param ctx要清除的Poly1305上下文。这可能是空的，在这种情况下，此函数是no-op。如果不是空，则必须指向初始化的Poly1305上下文。
 */
void mbedtls_poly1305_free( mbedtls_poly1305_context *ctx );

/**
 * \brief此函数设置一次性身份验证密钥。
 *
 * \warning每次调用Poly1305时，密钥必须是唯一且不可预测的。
 *
 * \param ctx键应绑定到的Poly1305上下文。必须对其进行初始化。\param key包含\c 32字节（\c 256位）密钥的缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_poly1305_starts( mbedtls_poly1305_context *ctx,
                             const unsigned char key[32] );

/**
 * \brief此函数将输入缓冲区输入到正在进行的Poly1305计算中。
 *
 *                  它在\cmbedtls_cipher_poly1305_starts（）和\cmbedtls _cipher_poly1305_finish（）之间调用。可以重复调用它来处理数据流。
 *
 * \param ctx用于Poly1305操作的Poly1305上下文。这必须初始化并绑定到密钥。\param ilen输入数据的长度（以字节为单位）。接受任何值。\param input保存输入数据的缓冲区。如果“ilen==0”，则此指针可以为空。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_poly1305_update( mbedtls_poly1305_context *ctx,
                             const unsigned char *input,
                             size_t ilen );

/**
 * \brief此函数生成Poly1305消息认证码（MAC）。
 *
 * \param ctx用于Poly1305操作的Poly1305上下文。这必须初始化并绑定到密钥。\param mac写入mac的缓冲区。这必须是长度为\c 16字节的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_poly1305_finish( mbedtls_poly1305_context *ctx,
                             unsigned char mac[16] );

/**
 * \brief此函数使用提供的密钥计算输入缓冲区的Poly1305 MAC。
 *
 * \warning每次调用Poly1305时，密钥必须是唯一且不可预测的。
 *
 * \param key包含\c 32字节（\c 256位）密钥的缓冲区。\param ilen输入数据的长度（以字节为单位）。接受任何值。\param input保存输入数据的缓冲区。如果“ilen==0”，则此指针可以为空。\param mac写入mac的缓冲区。这必须是长度为\c 16字节的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_poly1305_mac( const unsigned char key[32],
                          const unsigned char *input,
                          size_t ilen,
                          unsigned char mac[16] );

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要介绍Poly1305检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_poly1305_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_POLY1305_H */

