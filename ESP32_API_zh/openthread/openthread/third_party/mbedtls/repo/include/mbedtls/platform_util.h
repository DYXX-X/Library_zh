/**
 * \文件平台_util.h
 *
 * \Mbed TLS库中多个模块使用的简单通用和共享函数。
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
#ifndef MBEDTLS_PLATFORM_UTIL_H
#define MBEDTLS_PLATFORM_UTIL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#if defined(MBEDTLS_HAVE_TIME_DATE)
#include "mbedtls/platform_time.h"
#include <time.h>
#endif /* MBEDTLS_HAVE_TIME_DATE */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_CHECK_PARAMS)

#if defined(MBEDTLS_CHECK_PARAMS_ASSERT)
/* 允许用户将MBEDTLS_PARAM_FAILED定义为assert（这是config.h建议的）。*/
#include <assert.h>
#endif /* MBEDTLS_CHECK_PARAMS_ASSERT */

#if defined(MBEDTLS_PARAM_FAILED)
/** 在config.h中设置了MBEDTLS_PARAM_FAILED的另一个定义。
 *
 * 此标志可用于检查假设MBEDTLS_PARAM_FAILED（）将扩展为对MBEDTLS_PARAM_FAILED（）的调用是否安全。
 */
#define MBEDTLS_PARAM_FAILED_ALT

#elif defined(MBEDTLS_CHECK_PARAMS_ASSERT)
#define MBEDTLS_PARAM_FAILED( cond ) assert( cond )
#define MBEDTLS_PARAM_FAILED_ALT

#else /* MBEDTLS_PARAM_FAILED */
#define MBEDTLS_PARAM_FAILED( cond ) \
    mbedtls_param_failed( #cond, __FILE__, __LINE__ )

/**
 * \brief用户为参数验证失败提供的回调函数。有关上下文，请参见#MBEDTLS_CHECK_PARAMS。
 *
 *              除非通过#MBEDTLS_PARAM_FAILED宏定义了替代处理，否则将调用此函数。
 *
 *              该函数可以返回，操作将被中止，或者通过使用setjmp（）/longjmp（（）可以在应用程序代码中恢复执行。
 *
 * \param failure_condition不成立的断言。\param file断言失败的文件。\param line文件中断言失败的行。
 */
void mbedtls_param_failed( const char *failure_condition,
                           const char *file,
                           int line );
#endif /* MBEDTLS_PARAM_FAILED */

/* 内部宏意味着只能从库中调用。*/
#define MBEDTLS_INTERNAL_VALIDATE_RET( cond, ret )  \
    do {                                            \
        if( !(cond) )                               \
        {                                           \
            MBEDTLS_PARAM_FAILED( cond );           \
            return( ret );                          \
        }                                           \
    } while( 0 )

/* 内部宏意味着只能从库中调用。*/
#define MBEDTLS_INTERNAL_VALIDATE( cond )           \
    do {                                            \
        if( !(cond) )                               \
        {                                           \
            MBEDTLS_PARAM_FAILED( cond );           \
            return;                                 \
        }                                           \
    } while( 0 )

#else /* MBEDTLS_CHECK_PARAMS */

/* 内部宏意味着只能从库中调用。*/
#define MBEDTLS_INTERNAL_VALIDATE_RET( cond, ret )  do { } while( 0 )
#define MBEDTLS_INTERNAL_VALIDATE( cond )           do { } while( 0 )

#endif /* MBEDTLS_CHECK_PARAMS */

/* 用于弃用API常量的内部助手宏。*/
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
/* 故意不在此处导出MBEDTLS_DEPRECATED，以避免与定义和使用它的其他标头发生冲突。为了统一起见，我们可能需要将所有这些定义都移到这里。*/
#define MBEDTLS_DEPRECATED __attribute__((deprecated))
MBEDTLS_DEPRECATED typedef char const * mbedtls_deprecated_string_constant_t;
#define MBEDTLS_DEPRECATED_STRING_CONSTANT( VAL )       \
    ( (mbedtls_deprecated_string_constant_t) ( VAL ) )
MBEDTLS_DEPRECATED typedef int mbedtls_deprecated_numeric_constant_t;
#define MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( VAL )       \
    ( (mbedtls_deprecated_numeric_constant_t) ( VAL ) )
#undef MBEDTLS_DEPRECATED
#else /* MBEDTLS_DEPRECATED_WARNING */
#define MBEDTLS_DEPRECATED_STRING_CONSTANT( VAL ) VAL
#define MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( VAL ) VAL
#endif /* MBEDTLS_DEPRECATED_WARNING */
#endif /* MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief将缓冲区安全归零
 *
 *              该功能旨在擦除缓冲区中包含的数据，以便即使程序内存稍后受到破坏，也无法恢复数据。在从函数返回之前，对存储在堆栈上的敏感数据调用此函数，在释放堆对象之前，对堆上存储的敏感数据也调用此函数。
 *
 *              很难保证对mbedtls_platform_zerozize（）的调用不会被激进的编译器优化以可移植的方式删除。因此，Mbed TLS提供了配置选项MBEDTLS_PLATFORM_ZERIZE_ALT，允许用户配置MBEDTLS_PLATFORM_ZERIze（）以使用适合其平台和需求的实现
 *
 * \param buf要清零的缓冲区\param len缓冲区长度（字节）
 *
 */
void mbedtls_platform_zeroize( void *buf, size_t len );

#if defined(MBEDTLS_HAVE_TIME_DATE)
/**
 * \gmtimer（）的特定于平台的简短实现
 *
 *             该函数是一个线程安全抽象，其行为类似于Unix/POSIX中的gmtime_r（）函数。
 *
 *             Mbed TLS将尝试识别底层平台并使用适当的底层实现（例如，用于POSIX的gmtime_r（）和用于Windows的gmtime_s（））。如果这不可能，那么将使用gmtime（）。在这种情况下，如果启用了mbedtls_threading_C，则库对gmtime（）的调用将由互斥体mbedtls_threading_gmtime_mutex保护。建议库外部的调用也受此互斥锁的保护。
 *
 *             如果定义了MBEDTLS_PLATFORM_GMTIME_R_ALT，则Mbed TLS将无条件地使用用户在编译时提供的MBEDTLS_PLATFORM_GMTIME_R（）的替代实现。
 *
 * \param tt指向一个对象的指针，该对象包含从要转换的历元开始的时间（以秒为单位）\param tm_buf指向将存储结果的对象的指针
 *
 * \return成功时指向struct tm类型对象的指针，否则为NULL
 */
struct tm *mbedtls_platform_gmtime_r( const mbedtls_time_t *tt,
                                      struct tm *tm_buf );
#endif /* MBEDTLS_HAVE_TIME_DATE */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_PLATFORM_UTIL_H */

