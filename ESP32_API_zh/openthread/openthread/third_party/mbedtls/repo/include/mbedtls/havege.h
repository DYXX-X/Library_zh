/**
 * \文件havege.h
 *
 * \HAVEGE:HArdware挥发性熵的收集和扩展
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
#ifndef MBEDTLS_HAVEGE_H
#define MBEDTLS_HAVEGE_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#define MBEDTLS_HAVEGE_COLLECT_SIZE 1024

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简要HAVEGE状态结构
 */
typedef struct mbedtls_havege_state
{
    uint32_t PT1, PT2, offset[2];
    uint32_t pool[MBEDTLS_HAVEGE_COLLECT_SIZE];
    uint32_t WALK[8192];
}
mbedtls_havege_state;

/**
 * \简短HAVEGE初始化
 *
 * \param hs要初始化的HAVEGE状态
 */
void mbedtls_havege_init( mbedtls_havege_state *hs );

/**
 * \短暂清除HAVEGE状态
 *
 * \param hs要清除的HAVEGE状态
 */
void mbedtls_havege_free( mbedtls_havege_state *hs );

/**
 * \简要HAVEGE rand函数
 *
 * \param p_rng A HAVEGE状态\param要填充的输出缓冲区\param len缓冲区长度
 *
 * \返回0
 */
int mbedtls_havege_random( void *p_rng, unsigned char *output, size_t len );

#ifdef __cplusplus
}
#endif

#endif /* 哈奇·h*/

