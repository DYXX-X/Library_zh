/**
 * \文件base64.h
 *
 * \简要RFC 1521 base64编码/解码
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
#ifndef MBEDTLS_BASE64_H
#define MBEDTLS_BASE64_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

/**输出缓冲区太小。*/
#define MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL               -0x002A
/**输入中的字符无效。*/
#define MBEDTLS_ERR_BASE64_INVALID_CHARACTER              -0x002C

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief将缓冲区编码为base64格式
 *
 * \param dst目标缓冲区\param dlen目标缓冲区的大小\param olen写入的字节数\param src源缓冲区\pram slen要编码的数据量
 *
 * \如果成功则返回0，或MBEDTLS_ERROR_BASE64_BUFFER_TOO_SMALL。olen总是更新以反映已经（或将要）写入的数据量。如果无法表示该长度，则不会将数据写入缓冲区，并将olen设置为可表示为size_t的最大长度。
 *
 * \注意：在dlen=0时调用此函数以获取olen中所需的缓冲区大小
 */
int mbedtls_base64_encode( unsigned char *dst, size_t dlen, size_t *olen,
                   const unsigned char *src, size_t slen );

/**
 * \brief解码base64格式的缓冲区
 *
 * \param dst目标缓冲区（检查大小时可以为NULL）\param dlen目标缓冲区的大小\param olen写入的字节数\param src源缓冲区\param slen要解码的数据量
 *
 * \如果成功，则返回0；如果输入数据不正确，则返回MBEDTLS_ERROR_BASE64_BUFFER_TOO_SMALL或MBEDTLS_ERROR_BASE44_INVALID_CHARACTER。olen总是更新以反映已经（或将要）写入的数据量。
 *
 * \注意：使用*dst=NULL或dlen=0调用此函数以获取所需的缓冲区大小（以olen为单位）
 */
int mbedtls_base64_decode( unsigned char *dst, size_t dlen, size_t *olen,
                   const unsigned char *src, size_t slen );

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_base64_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 基64.h*/

