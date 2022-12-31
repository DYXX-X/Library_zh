/**
 * \文件entropy_poll.h
 *
 * \简短的平台特定和自定义熵轮询功能
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
#ifndef MBEDTLS_ENTROPY_POLL_H
#define MBEDTLS_ENTROPY_POLL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 内置源的默认阈值（字节）
 */
#define MBEDTLS_ENTROPY_MIN_PLATFORM     32     /**<平台源的最小值*/
#define MBEDTLS_ENTROPY_MIN_HAVEGE       32     /**<HAVEGE的最小值*/
#define MBEDTLS_ENTROPY_MIN_HARDCLOCK     4     /**<mbedtls_timing_hardclock（）的最小值*/
#if !defined(MBEDTLS_ENTROPY_MIN_HARDWARE)
#define MBEDTLS_ENTROPY_MIN_HARDWARE     32     /**<硬件源的最小值*/
#endif

/**
 * \提供0熵的简短熵轮询回调。
 */
#if defined(MBEDTLS_TEST_NULL_ENTROPY)
    int mbedtls_null_entropy_poll( void *data,
                                unsigned char *output, size_t len, size_t *olen );
#endif

#if !defined(MBEDTLS_NO_PLATFORM_ENTROPY)
/**
 * \简短的特定于平台的熵轮询回调
 */
int mbedtls_platform_entropy_poll( void *data,
                           unsigned char *output, size_t len, size_t *olen );
#endif

#if defined(MBEDTLS_HAVEGE_C)
/**
 * \基于HAVEGE的熵轮询回调
 *
 * 需要HAVEGE状态作为其数据指针。
 */
int mbedtls_havege_poll( void *data,
                 unsigned char *output, size_t len, size_t *olen );
#endif

#if defined(MBEDTLS_TIMING_C)
/**
 * \基于mbedtls_timenghardclock的简短熵轮询回调
 */
int mbedtls_hardclock_poll( void *data,
                    unsigned char *output, size_t len, size_t *olen );
#endif

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)
/**
 * \硬件源的简短熵轮询回调
 *
 * \警告这不是mbed TLS提供的！请参见config.h中的\c MBEDTLS_ENTROPY_HARDWARE_ALT。
 *
 * \注意这必须接受NULL作为其第一个参数。
 */
int mbedtls_hardware_poll( void *data,
                           unsigned char *output, size_t len, size_t *olen );
#endif

#if defined(MBEDTLS_ENTROPY_NV_SEED)
/**
 * \非易失性种子文件的简短熵轮询回调
 *
 * \注意这必须接受NULL作为其第一个参数。
 */
int mbedtls_nv_seed_poll( void *data,
                          unsigned char *output, size_t len, size_t *olen );
#endif

#ifdef __cplusplus
}
#endif

#endif /* entropy_poll.h*/

