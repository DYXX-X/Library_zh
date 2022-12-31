/**
 * \文件memory_buffer_alloc.h
 *
 * \基于缓冲区的内存分配器
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
#ifndef MBEDTLS_MEMORY_BUFFER_ALLOC_H
#define MBEDTLS_MEMORY_BUFFER_ALLOC_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */

#if !defined(MBEDTLS_MEMORY_ALIGN_MULTIPLE)
#define MBEDTLS_MEMORY_ALIGN_MULTIPLE       4 /**<按此值的倍数对齐*/
#endif

/* \}name SECTION:模块设置*/

#define MBEDTLS_MEMORY_VERIFY_NONE         0
#define MBEDTLS_MEMORY_VERIFY_ALLOC        (1 << 0)
#define MBEDTLS_MEMORY_VERIFY_FREE         (1 << 1)
#define MBEDTLS_MEMORY_VERIFY_ALWAYS       (MBEDTLS_MEMORY_VERIFY_ALLOC | MBEDTLS_MEMORY_VERIFY_FREE)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief初始化基于堆栈的内存分配器的使用。基于堆栈的分配器在呈现的缓冲区内进行内存管理，不调用calloc（）和free（）。它将全局mbedtls_calloc（）和mbedtls_free（）指针设置为自己的函数。（如果定义了mbedtls_THREADING_C，则提供mbedtls_calloc（）和mbedtls_free（）是线程安全的）
 *
 * \注意：此代码未经优化，提供了基于堆栈的内存分配器的直接实现。
 *
 * \param buf缓冲区用作缓冲区的堆长度
 */
void mbedtls_memory_buffer_alloc_init( unsigned char *buf, size_t len );

/**
 * \brief释放互斥锁以确保线程安全并清除剩余内存
 */
void mbedtls_memory_buffer_alloc_free( void );

/**
 * \brief确定分配器何时应自动验证整个标头/元数据链的状态。（默认值：MBEDTLS_MEMORY_VERIFY_NONE）
 *
 * \param verify MBEDTLS_MEMORY_verify_NONE、MBEDTLS_MEMORY_verify_ALLOC、MBEDLLS_MEMORY_verify_FREE或MBEDTLY_MEMORY_VALIFY_ALWAYS中的一个
 */
void mbedtls_memory_buffer_set_verify( int verify );

#if defined(MBEDTLS_MEMORY_DEBUG)
/**
 * \brief打印出已分配内存的状态（主要用于程序应取消分配所有内存后使用）如果定义了MBEDTLS_memory_BACKTRACE，则打印出“仍分配”块及其堆栈跟踪的列表。
 */
void mbedtls_memory_buffer_alloc_status( void );

/**
 * \brief获取到目前为止的峰值堆使用率
 *
 * \param max_used正在使用或提交的最大字节数。这包括分配的块中的字节太小，无法分割成更小的块，但大于请求的大小。\param max_blocks正在使用的块的峰值数量，包括空闲块和已使用块
 */
void mbedtls_memory_buffer_alloc_max_get( size_t *max_used, size_t *max_blocks );

/**
 * \简要重置峰值统计信息
 */
void mbedtls_memory_buffer_alloc_max_reset( void );

/**
 * \brief获取当前堆使用情况
 *
 * \param cur_used当前使用或提交的字节数。这包括分配的块中的字节太小，无法分割成更小的块，但大于请求的大小。\param cur_blocks当前使用的块数，包括空闲块和已使用块
 */
void mbedtls_memory_buffer_alloc_cur_get( size_t *cur_used, size_t *cur_blocks );
#endif /* MBEDTLS_MEMORY_DEBUG */

/**
 * \brief验证内存缓冲区中的所有标头是否正确并包含正确的值。帮助调试缓冲区溢出错误。
 *
 *          如果定义了MBEDTLS_MEMORY_DEBUG，则打印第一个失败。如果定义了MBEDTLS_MEMORY_DEBUG，则打印完整的标头信息。（如果还定义了MBEDTLS_MEMORY_BACKTRACE，则包括每个块的堆栈跟踪信息）。
 *
 * \如果已验证，则返回0，否则返回1
 */
int mbedtls_memory_buffer_alloc_verify( void );

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_memory_buffer_alloc_self_test( int verbose );
#endif

#ifdef __cplusplus
}
#endif

#endif /* 内存缓冲区分配h*/

