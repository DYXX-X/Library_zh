/**
 * \文件随机.h
 *
 * \brief这个文件包含帮助函数的原型，用于生成用于测试的随机数。
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

#ifndef TEST_RANDOM_H
#define TEST_RANDOM_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

typedef struct
{
    unsigned char *buf; /* 指向长度为字节的缓冲区的指针。*/
    size_t length;
    /* 如果fallback_f_rng为NULL，则在传递长度字节后失败。*/
    int ( *fallback_f_rng )( void*, unsigned char *, size_t );
    void *fallback_p_rng;
} mbedtls_test_rnd_buf_info;

/**
 * 伪随机函数的信息结构
 *
 * 密钥应在开始时设置为测试唯一值。不要忘记结尾！状态（v0，v1）应设置为零。
 */
typedef struct
{
    uint32_t key[16];
    uint32_t v0, v1;
} mbedtls_test_rnd_pseudo_info;

/**
 * 此函数仅从rand（）返回数据。尽管在多次运行中可以预测并且通常相似，但这不会导致每次运行中出现相同的随机性。因此，如果测试结果取决于生成的随机数据，请不要使用此选项。
 *
 * rng_state应为NULL。
 */
int mbedtls_test_rnd_std_rand( void *rng_state,
                               unsigned char *output,
                               size_t len );

/**
 * 此函数只返回零。
 *
 * \p rng_state应为\c NULL。
 */
int mbedtls_test_rnd_zero_rand( void *rng_state,
                                unsigned char *output,
                                size_t len );

/**
 * 此函数根据接收的缓冲区返回随机数据。
 *
 * \p rng_state应该是指向#mbedtls_test_rnd_buf_info结构的指针。
 *
 * 每次调用随机函数时从缓冲区释放的字节数由\p len指定。
 *
 * 缓冲区为空后，如果存在#mbedtls_test_rnd_buf_info结构中的回退RNG，则该函数将调用该结构，否则返回#mbedtls_ERROR_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_test_rnd_buffer_rand( void *rng_state,
                                  unsigned char *output,
                                  size_t len );

/**
 * 此函数基于伪随机函数返回随机值。这意味着所有系统的结果都应该相同。伪随机是基于XTEA加密算法生成伪随机的。
 *
 * \p rng_state应该是指向#mbedtls_test_rnd_pseudo_info结构的指针。
 */
int mbedtls_test_rnd_pseudo_rand( void *rng_state,
                                  unsigned char *output,
                                  size_t len );

#endif /* TEST_RANDOM_H */

