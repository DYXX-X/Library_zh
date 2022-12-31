/**
 * \文件平台_时间.h
 *
 * \简短的mbed TLS平台时间抽象
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
#ifndef MBEDTLS_PLATFORM_TIME_H
#define MBEDTLS_PLATFORM_TIME_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */

/*
 * time_t数据类型
 */
#if defined(MBEDTLS_PLATFORM_TIME_TYPE_MACRO)
typedef MBEDTLS_PLATFORM_TIME_TYPE_MACRO mbedtls_time_t;
#else
/* 时间_t*/
#include <time.h>
typedef time_t mbedtls_time_t;
#endif /* MBEDTLS_PLATFORM_TIME_TYPE_MACRO */

/*
 * 时间的函数指针
 */
#if defined(MBEDTLS_PLATFORM_TIME_ALT)
extern mbedtls_time_t (*mbedtls_time)( mbedtls_time_t* time );

/**
 * \brief设置自己的时间函数指针
 *
 * \param time_func时间函数实现
 *
 * \返回0
 */
int mbedtls_platform_set_time( mbedtls_time_t (*time_func)( mbedtls_time_t* time ) );
#else
#if defined(MBEDTLS_PLATFORM_TIME_MACRO)
#define mbedtls_time    MBEDTLS_PLATFORM_TIME_MACRO
#else
#define mbedtls_time   time
#endif /* MBEDTLS_PLATFORM_TIME_MACRO */
#endif /* MBEDTLS_PLATFORM_TIME_ALT */

#ifdef __cplusplus
}
#endif

#endif /* 平台_时间.h*/

