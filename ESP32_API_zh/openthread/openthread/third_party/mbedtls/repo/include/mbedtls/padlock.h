/**
 * \文件挂锁.h
 *
 * \某些处理器支持硬件加密/解密的VIA PadLock ACE简介
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
#ifndef MBEDTLS_PADLOCK_H
#define MBEDTLS_PADLOCK_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/aes.h"

#define MBEDTLS_ERR_PADLOCK_DATA_MISALIGNED               -0x0030  /**<输入数据应对齐。*/

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define MBEDTLS_HAVE_ASAN
#endif
#endif

/* ASan的某些版本会导致寄存器不足的错误*/
#if defined(MBEDTLS_HAVE_ASM) && defined(__GNUC__) && defined(__i386__) && \
    !defined(MBEDTLS_HAVE_ASAN)

#ifndef MBEDTLS_HAVE_X86
#define MBEDTLS_HAVE_X86
#endif

#include <stdint.h>

#define MBEDTLS_PADLOCK_RNG 0x000C
#define MBEDTLS_PADLOCK_ACE 0x00C0
#define MBEDTLS_PADLOCK_PHE 0x0C00
#define MBEDTLS_PADLOCK_PMM 0x3000

#define MBEDTLS_PADLOCK_ALIGN16(x) (uint32_t *) (16 + ((int32_t) (x) & ~15))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简短的内部挂锁检测例程
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param feature要检测的功能
 *
 * \如果CPU支持该功能，则返回1，否则返回0
 */
int mbedtls_padlock_has_support( int feature );

/**
 * \简短的内部挂锁AES-ECB块加密
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param ctx AES上下文\param模式MBEDTLS_AES_ENCRYPT或MBEDTLS_AES_DES_DECRYPT \param输入16字节输入块\param输出16字节输出块
 *
 * \如果成功，则返回0；如果操作失败，则返回1
 */
int mbedtls_padlock_xcryptecb( mbedtls_aes_context *ctx,
                               int mode,
                               const unsigned char input[16],
                               unsigned char output[16] );

/**
 * \简短的内部挂锁AES-CBC缓冲区加密
 *
 * \注意：此函数仅供其他库函数内部使用；你不能直接调用它。
 *
 * \param ctx AES上下文\param模式MBEDTLS_AES_ENCRYPT或MBEDTLS_AES_DES_DECRYPT \param输入数据的长度\param iv初始化向量（使用后更新）\param保存输入数据的输入缓冲区\param保持输出数据的输出缓冲区
 *
 * \如果成功，则返回0；如果操作失败，则返回1
 */
int mbedtls_padlock_xcryptcbc( mbedtls_aes_context *ctx,
                               int mode,
                               size_t length,
                               unsigned char iv[16],
                               const unsigned char *input,
                               unsigned char *output );

#ifdef __cplusplus
}
#endif

#endif /* HAVE_X86  */

#endif /* 挂锁.h*/

