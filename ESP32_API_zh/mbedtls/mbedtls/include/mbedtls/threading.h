/**
 * \文件线程.h
 *
 * \简要线程抽象层
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
#ifndef MBEDTLS_THREADING_H
#define MBEDTLS_THREADING_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MBEDTLS_ERROR_THREADING_FEATURE_NAVAILABLE已弃用，不应使用。*/
/**所选功能不可用。*/
#define MBEDTLS_ERR_THREADING_FEATURE_UNAVAILABLE         -0x001A

/**函数的输入参数错误。*/
#define MBEDTLS_ERR_THREADING_BAD_INPUT_DATA              -0x001C
/**锁定/解锁/释放失败，错误代码为。*/
#define MBEDTLS_ERR_THREADING_MUTEX_ERROR                 -0x001E

#if defined(MBEDTLS_THREADING_PTHREAD)
#include <pthread.h>
typedef struct mbedtls_threading_mutex_t
{
    pthread_mutex_t mutex;
    /* 初始化失败或空闲后is_valid为0，初始化成功后is_vvalid为非零。此字段不被视为Mbed TLS公共API的一部分，可能会更改，恕不另行通知。*/
    char is_valid;
} mbedtls_threading_mutex_t;
#endif

#if defined(MBEDTLS_THREADING_ALT)
/* 应该在头中定义mbedtls_threading_mutex_t类型*/
#include "threading_alt.h"

/**
 * \brief设置备用线程实现函数指针并初始化全局互斥锁。如果使用此函数，则在调用任何其他mbed TLS函数之前，必须在主线程中调用此函数一次，并且在所有其他mbed TLS函数之后，必须在主线程中调用mbedtls_threading_free_alt（）一次。
 *
 * \注意mutex_init（）和mutex_free（）不会返回状态代码。如果mutex_init（）失败，它应该将其参数（mutex）保持在这样一种状态，即当使用此参数调用mutex_lock（）时，它将失败。
 *
 * \param mutex_init初始化函数实现\param mutex_free自由函数实现\pram mutex_lock锁定函数实现\prammutex_unlock解锁函数实现
 */
void mbedtls_threading_set_alt( void (*mutex_init)( mbedtls_threading_mutex_t * ),
                       void (*mutex_free)( mbedtls_threading_mutex_t * ),
                       int (*mutex_lock)( mbedtls_threading_mutex_t * ),
                       int (*mutex_unlock)( mbedtls_threading_mutex_t * ) );

/**
 * \brief释放全局互斥锁。
 */
void mbedtls_threading_free_alt( void );
#endif /* MBEDTLS_THREADING_ALT */

#if defined(MBEDTLS_THREADING_C)
/*
 * mutex_init、mutex_free、mutex_和mutex_unlock的函数指针
 *
 * 所有这些函数都应该工作，否则结果将是不确定的。
 */
extern void (*mbedtls_mutex_init)( mbedtls_threading_mutex_t *mutex );
extern void (*mbedtls_mutex_free)( mbedtls_threading_mutex_t *mutex );
extern int (*mbedtls_mutex_lock)( mbedtls_threading_mutex_t *mutex );
extern int (*mbedtls_mutex_unlock)( mbedtls_threading_mutex_t *mutex );

/*
 * 全局互斥体
 */
#if defined(MBEDTLS_FS_IO)
extern mbedtls_threading_mutex_t mbedtls_threading_readdir_mutex;
#endif

#if defined(MBEDTLS_HAVE_TIME_DATE) && !defined(MBEDTLS_PLATFORM_GMTIME_R_ALT)
/* 在mbedtls_platform_gmtime_r（）的默认定义中可能使用或不使用此互斥锁，但为了确定这一点，我们需要检查POSIX特性，因此修改_POSIX_C_SOURCE。在当前方法中，此声明是孤立的，缺少附带的定义，以防mbedtls_platform_gmtime_r（）不需要它，但这不是问题。*/
extern mbedtls_threading_mutex_t mbedtls_threading_gmtime_mutex;
#endif /* MBEDTLS_HAVE_TIME_DATE && !MBEDTLS_PLATFORM_GMTIME_R_ALT */

#endif /* MBEDTLS_THREADING_C */

#ifdef __cplusplus
}
#endif

#endif /* 线程.h*/

