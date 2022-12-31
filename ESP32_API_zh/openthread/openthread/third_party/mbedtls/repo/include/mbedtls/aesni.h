/**
 * \文件aesni.h
 *
 * \一些Intel处理器上硬件AES加速的简要AES-NI
 *
 * \警告这些函数仅供其他库函数内部使用；你不能直接打电话给他们。
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
#ifndef MBEDTLS_AESNI_H
#define MBEDTLS_AESNI_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/aes.h"

#define MBEDTLS_AESNI_AES      0x02000000u
#define MBEDTLS_AESNI_CLMUL    0x00000002u

#if defined(MBEDTLS_HAVE_ASM) && defined(__GNUC__) &&  \
    ( defined(__amd64__) || defined(__x86_64__) )   &&  \
    ! defined(MBEDTLS_HAVE_X86_64)
#define MBEDTLS_HAVE_X86_64
#endif

#if defined(MBEDTLS_HAVE_X86_64)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \检测CPU中AES-NI功能的简短内部功能。
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param要检测的功能（MBEDTLS_AESNI_AES或MBEDTLS_AENI_CLMUL）
 *
 * \如果CPU支持该功能，则返回1，否则返回0
 */
int mbedtls_aesni_has_support( unsigned int what );

/**
 * \简要内部AES-NI AES-ECB块加密和解密
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param ctx AES上下文\param模式MBEDTLS_AES_ENCRYPT或MBEDTLS_AES_DES_DECRYPT \param输入16字节输入块\param输出16字节输出块
 *
 * \成功时返回0（不能失败）
 */
int mbedtls_aesni_crypt_ecb( mbedtls_aes_context *ctx,
                             int mode,
                             const unsigned char input[16],
                             unsigned char output[16] );

/**
 * \简短的内部GCM乘法：c=GF中的a*b（2^128）
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param c结果\param a第一个操作数\param b第二个操作数
 *
 * \注意：根据GCM规范，操作数和结果都是被解释为GF（2^128）元素的位字符串。
 */
void mbedtls_aesni_gcm_mult( unsigned char c[16],
                             const unsigned char a[16],
                             const unsigned char b[16] );

/**
 * \简短的内部圆键反转。此函数根据加密循环密钥计算解密循环密钥。
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param invkey等效反密码的循环密钥\param fwdkey原始循环密钥（用于加密）\param nr循环数（即循环密钥数减1）
 */
void mbedtls_aesni_inverse_key( unsigned char *invkey,
                                const unsigned char *fwdkey,
                                int nr );

/**
 * \用于加密的简短内部密钥扩展
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param rk写入循环密钥的目标缓冲区\param key加密密钥\param bits以位为单位的密钥大小（必须是128、192或256）
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH
 */
int mbedtls_aesni_setkey_enc( unsigned char *rk,
                              const unsigned char *key,
                              size_t bits );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_HAVE_X86_64 */

#endif /* MBEDTLS_AESNI_H */

