/**
 * \文件平台.h
 *
 * \这个文件包含了Mbed TLS平台抽象层的定义和功能。
 *
 *        平台抽象层消除了库直接链接到标准C库函数或操作系统服务的需要，使库更易于移植和嵌入。应用程序开发人员和库的用户可以提供他们自己的这些功能的实现，或特定于他们平台的实现，这些功能可以静态链接到库或在运行时动态配置。
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
#ifndef MBEDTLS_PLATFORM_H
#define MBEDTLS_PLATFORM_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_HAVE_TIME)
#include "mbedtls/platform_time.h"
#endif

/**硬件加速器失败*/
#define MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED     -0x0070
/**平台不支持请求的功能*/
#define MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED -0x0072

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */

/* 较旧的Microsoft Windows公共运行时提供了一些标准库函数（包括snprintf和vsnprintf）的非一致实现。这会影响MSVC和MinGW构建。
 */
#if defined(__MINGW32__) || (defined(_MSC_VER) && _MSC_VER <= 1900)
#define MBEDTLS_PLATFORM_HAS_NON_CONFORMING_SNPRINTF
#define MBEDTLS_PLATFORM_HAS_NON_CONFORMING_VSNPRINTF
#endif

#if !defined(MBEDTLS_PLATFORM_NO_STD_FUNCTIONS)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if !defined(MBEDTLS_PLATFORM_STD_SNPRINTF)
#if defined(MBEDTLS_PLATFORM_HAS_NON_CONFORMING_SNPRINTF)
#define MBEDTLS_PLATFORM_STD_SNPRINTF   mbedtls_platform_win32_snprintf /**<要使用的默认\c snprintf函数。*/
#else
#define MBEDTLS_PLATFORM_STD_SNPRINTF   snprintf /**<要使用的默认\c snprintf函数。*/
#endif
#endif
#if !defined(MBEDTLS_PLATFORM_STD_VSNPRINTF)
#if defined(MBEDTLS_PLATFORM_HAS_NON_CONFORMING_VSNPRINTF)
#define MBEDTLS_PLATFORM_STD_VSNPRINTF   mbedtls_platform_win32_vsnprintf /**<要使用的默认\c vsnprintf函数。*/
#else
#define MBEDTLS_PLATFORM_STD_VSNPRINTF   vsnprintf /**<要使用的默认\c vsnprintf函数。*/
#endif
#endif
#if !defined(MBEDTLS_PLATFORM_STD_PRINTF)
#define MBEDTLS_PLATFORM_STD_PRINTF   printf /**<要使用的默认\c printf函数。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_FPRINTF)
#define MBEDTLS_PLATFORM_STD_FPRINTF fprintf /**<要使用的默认\c fprintf函数。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_CALLOC)
#define MBEDTLS_PLATFORM_STD_CALLOC   calloc /**<要使用的默认\c calloc函数。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_FREE)
#define MBEDTLS_PLATFORM_STD_FREE       free /**<要使用的默认\c自由函数。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_EXIT)
#define MBEDTLS_PLATFORM_STD_EXIT      exit /**<要使用的默认\c退出函数。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_TIME)
#define MBEDTLS_PLATFORM_STD_TIME       time    /**<要使用的默认时间函数。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_EXIT_SUCCESS)
#define MBEDTLS_PLATFORM_STD_EXIT_SUCCESS  EXIT_SUCCESS /**<要使用的默认退出值。*/
#endif
#if !defined(MBEDTLS_PLATFORM_STD_EXIT_FAILURE)
#define MBEDTLS_PLATFORM_STD_EXIT_FAILURE  EXIT_FAILURE /**<要使用的默认退出值。*/
#endif
#if defined(MBEDTLS_FS_IO)
#if !defined(MBEDTLS_PLATFORM_STD_NV_SEED_READ)
#define MBEDTLS_PLATFORM_STD_NV_SEED_READ   mbedtls_platform_std_nv_seed_read
#endif
#if !defined(MBEDTLS_PLATFORM_STD_NV_SEED_WRITE)
#define MBEDTLS_PLATFORM_STD_NV_SEED_WRITE  mbedtls_platform_std_nv_seed_write
#endif
#if !defined(MBEDTLS_PLATFORM_STD_NV_SEED_FILE)
#define MBEDTLS_PLATFORM_STD_NV_SEED_FILE   "seedfile"
#endif
#endif /* MBEDTLS_FS_IO */
#else /* MBEDTLS_PLATFORM_NO_STD_FUNCTIONS */
#if defined(MBEDTLS_PLATFORM_STD_MEM_HDR)
#include MBEDTLS_PLATFORM_STD_MEM_HDR
#endif
#endif /* MBEDTLS_PLATFORM_NO_STD_FUNCTIONS */


/* \}name SECTION:模块设置*/

/*
 * calloc和free的函数指针。
 */
#if defined(MBEDTLS_PLATFORM_MEMORY)
#if defined(MBEDTLS_PLATFORM_FREE_MACRO) && \
    defined(MBEDTLS_PLATFORM_CALLOC_MACRO)
#define mbedtls_free       MBEDTLS_PLATFORM_FREE_MACRO
#define mbedtls_calloc     MBEDTLS_PLATFORM_CALLOC_MACRO
#else
/* 对于size_t*/
#include <stddef.h>
extern void *mbedtls_calloc( size_t n, size_t size );
extern void mbedtls_free( void *ptr );

/**
 * \brief此函数在运行时动态设置库使用的内存管理函数。
 *
 * \param calloc_func \c calloc函数实现。\param free_func \c free函数实现。
 *
 * \返回\c 0。
 */
int mbedtls_platform_set_calloc_free( void * (*calloc_func)( size_t, size_t ),
                              void (*free_func)( void * ) );
#endif /* MBEDTLS_PLATFORM_FREE_MACRO && MBEDTLS_PLATFORM_CALLOC_MACRO */
#else /* !MBEDTLS_PLATFORM_MEMORY */
#define mbedtls_free       free
#define mbedtls_calloc     calloc
#endif /* MBEDTLS_PLATFORM_MEMORY && !MBEDTLS_PLATFORM_{FREE,CALLOC}_MACRO */

/*
 * fprintf的函数指针
 */
#if defined(MBEDTLS_PLATFORM_FPRINTF_ALT)
/* 我们需要文件**/
#include <stdio.h>
extern int (*mbedtls_fprintf)( FILE *stream, const char *format, ... );

/**
 * \brief此函数动态配置fprintf函数，当库调用mbedtls_fprintf（）函数时调用该函数。
 *
 * \param fprintf_func \c fprintf函数实现。
 *
 * \返回\c 0。
 */
int mbedtls_platform_set_fprintf( int (*fprintf_func)( FILE *stream, const char *,
                                               ... ) );
#else
#if defined(MBEDTLS_PLATFORM_FPRINTF_MACRO)
#define mbedtls_fprintf    MBEDTLS_PLATFORM_FPRINTF_MACRO
#else
#define mbedtls_fprintf    fprintf
#endif /* MBEDTLS_PLATFORM_FPRINTF_MACRO */
#endif /* MBEDTLS_PLATFORM_FPRINTF_ALT */

/*
 * printf的函数指针
 */
#if defined(MBEDTLS_PLATFORM_PRINTF_ALT)
extern int (*mbedtls_printf)( const char *format, ... );

/**
 * \brief此函数动态配置库调用mbedtls_snprintf（）函数时调用的snprintf函数。
 *
 * \param printf_func \c printf函数实现。
 *
 * \成功时返回\c 0。
 */
int mbedtls_platform_set_printf( int (*printf_func)( const char *, ... ) );
#else /* !MBEDTLS_PLATFORM_PRINTF_ALT */
#if defined(MBEDTLS_PLATFORM_PRINTF_MACRO)
#define mbedtls_printf     MBEDTLS_PLATFORM_PRINTF_MACRO
#else
#define mbedtls_printf     printf
#endif /* MBEDTLS_PLATFORM_PRINTF_MACRO */
#endif /* MBEDTLS_PLATFORM_PRINTF_ALT */

/*
 * snprintf的函数指针
 *
 * snprintf实现应符合C99：
 * -它必须始终正确地将缓冲区归零（n==0时除外，则必须保持缓冲区不变）
 * -然而，当目标缓冲区太短时，返回-1而不是所需的长度是可以接受的。
 */
#if defined(MBEDTLS_PLATFORM_HAS_NON_CONFORMING_SNPRINTF)
/* 对于Windows（包括MSYS2），我们提供了自己的固定实现*/
int mbedtls_platform_win32_snprintf( char *s, size_t n, const char *fmt, ... );
#endif

#if defined(MBEDTLS_PLATFORM_SNPRINTF_ALT)
extern int (*mbedtls_snprintf)( char * s, size_t n, const char * format, ... );

/**
 * \brief此函数允许配置自定义的\c snprintf函数指针。
 *
 * \param snprintf_func \c snprintf函数实现。
 *
 * \成功时返回\c 0。
 */
int mbedtls_platform_set_snprintf( int (*snprintf_func)( char * s, size_t n,
                                                 const char * format, ... ) );
#else /* MBEDTLS_PLATFORM_SNPRINTF_ALT */
#if defined(MBEDTLS_PLATFORM_SNPRINTF_MACRO)
#define mbedtls_snprintf   MBEDTLS_PLATFORM_SNPRINTF_MACRO
#else
#define mbedtls_snprintf   MBEDTLS_PLATFORM_STD_SNPRINTF
#endif /* MBEDTLS_PLATFORM_SNPRINTF_MACRO */
#endif /* MBEDTLS_PLATFORM_SNPRINTF_ALT */

/*
 * vsnprintf的函数指针
 *
 * vsnprintf实现应符合C99：
 * -它必须始终正确地将缓冲区归零（n==0时除外，则必须保持缓冲区不变）
 * -然而，当目标缓冲区太短时，返回-1而不是所需的长度是可以接受的。
 */
#if defined(MBEDTLS_PLATFORM_HAS_NON_CONFORMING_VSNPRINTF)
#include <stdarg.h>
/* 对于较旧的Windows（包括MSYS2），我们提供了自己的固定实现*/
int mbedtls_platform_win32_vsnprintf( char *s, size_t n, const char *fmt, va_list arg );
#endif

#if defined(MBEDTLS_PLATFORM_VSNPRINTF_ALT)
#include <stdarg.h>
extern int (*mbedtls_vsnprintf)( char * s, size_t n, const char * format, va_list arg );

/**
 * \brief设置自己的snprintf函数指针
 *
 * \param vsnprintf_func \c vsnprentf函数实现
 *
 * \返回\c 0
 */
int mbedtls_platform_set_vsnprintf( int (*vsnprintf_func)( char * s, size_t n,
                                                 const char * format, va_list arg ) );
#else /* MBEDTLS_PLATFORM_VSNPRINTF_ALT */
#if defined(MBEDTLS_PLATFORM_VSNPRINTF_MACRO)
#define mbedtls_vsnprintf   MBEDTLS_PLATFORM_VSNPRINTF_MACRO
#else
#define mbedtls_vsnprintf   vsnprintf
#endif /* MBEDTLS_PLATFORM_VSNPRINTF_MACRO */
#endif /* MBEDTLS_PLATFORM_VSNPRINTF_ALT */

/*
 * 退出的函数指针
 */
#if defined(MBEDTLS_PLATFORM_EXIT_ALT)
extern void (*mbedtls_exit)( int status );

/**
 * \brief此函数动态配置库调用mbedtls_exit（）函数时调用的退出函数。
 *
 * \param exit_func \c退出函数实现。
 *
 * \成功时返回\c 0。
 */
int mbedtls_platform_set_exit( void (*exit_func)( int status ) );
#else
#if defined(MBEDTLS_PLATFORM_EXIT_MACRO)
#define mbedtls_exit   MBEDTLS_PLATFORM_EXIT_MACRO
#else
#define mbedtls_exit   exit
#endif /* MBEDTLS_PLATFORM_EXIT_MACRO */
#endif /* MBEDTLS_PLATFORM_EXIT_ALT */

/*
 * 默认退出值
 */
#if defined(MBEDTLS_PLATFORM_STD_EXIT_SUCCESS)
#define MBEDTLS_EXIT_SUCCESS MBEDTLS_PLATFORM_STD_EXIT_SUCCESS
#else
#define MBEDTLS_EXIT_SUCCESS 0
#endif
#if defined(MBEDTLS_PLATFORM_STD_EXIT_FAILURE)
#define MBEDTLS_EXIT_FAILURE MBEDTLS_PLATFORM_STD_EXIT_FAILURE
#else
#define MBEDTLS_EXIT_FAILURE 1
#endif

/*
 * 以独立于平台的方式从非易失性存储器（NV）读取种子文件并将其写入的函数指针
 *
 * 仅当NV种子熵源启用时启用
 */
#if defined(MBEDTLS_ENTROPY_NV_SEED)
#if !defined(MBEDTLS_PLATFORM_NO_STD_FUNCTIONS) && defined(MBEDTLS_FS_IO)
/* 内部标准平台定义*/
int mbedtls_platform_std_nv_seed_read( unsigned char *buf, size_t buf_len );
int mbedtls_platform_std_nv_seed_write( unsigned char *buf, size_t buf_len );
#endif

#if defined(MBEDTLS_PLATFORM_NV_SEED_ALT)
extern int (*mbedtls_nv_seed_read)( unsigned char *buf, size_t buf_len );
extern int (*mbedtls_nv_seed_write)( unsigned char *buf, size_t buf_len );

/**
 * \brief此功能允许配置自定义种子文件写入和读取功能。
 *
 * \param nv_seed_read_func种子读取函数实现。\param nv_seed_write_func种子写入函数实现。
 *
 * \成功时返回\c 0。
 */
int mbedtls_platform_set_nv_seed(
            int (*nv_seed_read_func)( unsigned char *buf, size_t buf_len ),
            int (*nv_seed_write_func)( unsigned char *buf, size_t buf_len )
            );
#else
#if defined(MBEDTLS_PLATFORM_NV_SEED_READ_MACRO) && \
    defined(MBEDTLS_PLATFORM_NV_SEED_WRITE_MACRO)
#define mbedtls_nv_seed_read    MBEDTLS_PLATFORM_NV_SEED_READ_MACRO
#define mbedtls_nv_seed_write   MBEDTLS_PLATFORM_NV_SEED_WRITE_MACRO
#else
#define mbedtls_nv_seed_read    mbedtls_platform_std_nv_seed_read
#define mbedtls_nv_seed_write   mbedtls_platform_std_nv_seed_write
#endif
#endif /* MBEDTLS_PLATFORM_NV_SEED_ALT */
#endif /* MBEDTLS_ENTROPY_NV_SEED */

#if !defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)

/**
 * \brief平台上下文结构。
 *
 * \注意：此结构可用于协助平台特定的设置或拆卸操作。
 */
typedef struct mbedtls_platform_context
{
    char dummy; /**<占位符成员，因为空结构不可移植。*/
}
mbedtls_platform_context;

#else
#include "platform_alt.h"
#endif /* !MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */

/**
 * \brief此函数执行任何特定于平台的初始化操作。
 *
 * \注意：应在调用任何其他库函数之前调用此函数。
 *
 *          它的实现是特定平台的，除非提供特定平台的代码，否则它什么都不做。
 *
 * \注意：此功能的使用和必要性取决于平台。
 *
 * \param ctx平台上下文。
 *
 * \成功时返回\c 0。
 */
int mbedtls_platform_setup( mbedtls_platform_context *ctx );
/**
 * \brief此函数执行任何平台拆卸操作。
 *
 * \注意：应在使用适当的释放函数正确释放每个其他Mbed TLS模块后调用此函数。
 *
 *          它的实现是特定平台的，除非提供特定平台的代码，否则它什么都不做。
 *
 * \注意：此功能的使用和必要性取决于平台。
 *
 * \param ctx平台上下文。
 *
 */
void mbedtls_platform_teardown( mbedtls_platform_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* 平台.h*/

