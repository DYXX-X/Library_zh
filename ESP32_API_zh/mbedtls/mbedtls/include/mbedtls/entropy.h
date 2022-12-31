/**
 * \文件熵.h
 *
 * \熵累加器的简单实现
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
#ifndef MBEDTLS_ENTROPY_H
#define MBEDTLS_ENTROPY_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

#if defined(MBEDTLS_SHA512_C) && !defined(MBEDTLS_ENTROPY_FORCE_SHA256)
#include "mbedtls/sha512.h"
#define MBEDTLS_ENTROPY_SHA512_ACCUMULATOR
#else
#if defined(MBEDTLS_SHA256_C)
#define MBEDTLS_ENTROPY_SHA256_ACCUMULATOR
#include "mbedtls/sha256.h"
#endif
#endif

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif

#if defined(MBEDTLS_HAVEGE_C)
#include "mbedtls/havege.h"
#endif

/**临界熵源失效。*/
#define MBEDTLS_ERR_ENTROPY_SOURCE_FAILED                 -0x003C
/**无法添加更多源。*/
#define MBEDTLS_ERR_ENTROPY_MAX_SOURCES                   -0x003E
/**尚未向投票中添加任何来源。*/
#define MBEDTLS_ERR_ENTROPY_NO_SOURCES_DEFINED            -0x0040
/**调查中没有添加有力的消息来源。*/
#define MBEDTLS_ERR_ENTROPY_NO_STRONG_SOURCE              -0x003D
/**文件中存在读/写错误。*/
#define MBEDTLS_ERR_ENTROPY_FILE_IO_ERROR                 -0x003F

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */

#if !defined(MBEDTLS_ENTROPY_MAX_SOURCES)
#define MBEDTLS_ENTROPY_MAX_SOURCES     20      /**<支持的最大源数*/
#endif

#if !defined(MBEDTLS_ENTROPY_MAX_GATHER)
#define MBEDTLS_ENTROPY_MAX_GATHER      128     /**<从熵源请求的最大数量*/
#endif

/* \}name SECTION:模块设置*/

#if defined(MBEDTLS_ENTROPY_SHA512_ACCUMULATOR)
#define MBEDTLS_ENTROPY_BLOCK_SIZE      64      /**<熵累加器的块大小（SHA-512）*/
#else
#define MBEDTLS_ENTROPY_BLOCK_SIZE      32      /**<熵累加器的块大小（SHA-256）*/
#endif

#define MBEDTLS_ENTROPY_MAX_SEED_SIZE   1024    /**<我们从种子文件读取的种子的最大大小*/
#define MBEDTLS_ENTROPY_SOURCE_MANUAL   MBEDTLS_ENTROPY_MAX_SOURCES

#define MBEDTLS_ENTROPY_SOURCE_STRONG   1       /**<熵源强*/
#define MBEDTLS_ENTROPY_SOURCE_WEAK     0       /**<熵源较弱*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简短熵轮询回调指针
 *
 * \param data回调特定数据指针\param output要填充的数据\param len要提供的最大大小\param olen放入缓冲区的实际字节数（可以是0）
 *
 * \如果未发生严重故障，则返回0，否则返回MBEDTLS_ERROR_ENTROPY_SOURCE_FAILED
 */
typedef int (*mbedtls_entropy_f_source_ptr)(void *data, unsigned char *output, size_t len,
                            size_t *olen);

/**
 * \简熵源态
 */
typedef struct mbedtls_entropy_source_state
{
    mbedtls_entropy_f_source_ptr    f_source;   /**<熵源回调*/
    void *          p_source;   /**<回调数据指针*/
    size_t          size;       /**<收到的字节数*/
    size_t          threshold;  /**<发布前所需的最小字节数*/
    int             strong;     /**<来源强大吗？*/
}
mbedtls_entropy_source_state;

/**
 * \简熵上下文结构
 */
typedef struct mbedtls_entropy_context
{
    int accumulator_started; /* 初始化后为0。第一次更新后1。*-免费后1。*/
#if defined(MBEDTLS_ENTROPY_SHA512_ACCUMULATOR)
    mbedtls_sha512_context  accumulator;
#elif defined(MBEDTLS_ENTROPY_SHA256_ACCUMULATOR)
    mbedtls_sha256_context  accumulator;
#endif
    int             source_count; /* 源中使用的条目数。*/
    mbedtls_entropy_source_state    source[MBEDTLS_ENTROPY_MAX_SOURCES];
#if defined(MBEDTLS_HAVEGE_C)
    mbedtls_havege_state    havege_data;
#endif
#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t mutex;    /*!< 互斥锁*/
#endif
#if defined(MBEDTLS_ENTROPY_NV_SEED)
    int initial_entropy_run;
#endif
}
mbedtls_entropy_context;

/**
 * \brief初始化上下文
 *
 * \param ctx要初始化的熵上下文
 */
void mbedtls_entropy_init( mbedtls_entropy_context *ctx );

/**
 * \brief释放上下文中的数据
 *
 * \param ctx要释放的熵上下文
 */
void mbedtls_entropy_free( mbedtls_entropy_context *ctx );

/**
 * \brief向轮询添加熵源（如果启用了MBEDTLS_THREADING_C，则线程安全）
 *
 * \param ctx熵上下文\param f_source熵函数\param p_source函数数据\param threshold在释放熵之前从源所需的最小值（使用mbedtls_Entropy_func（））（以字节为单位）\param strong mbedtls_Entropy_source_strong或mbedtls_Entropy_source_WEAK。至少需要添加一个强大的源。较弱的源（如循环计数器）可以用作补码。
 *
 * \如果成功，则返回0或MBEDTLS_ERROR_ENTROPY_MAX_SOURCES
 */
int mbedtls_entropy_add_source( mbedtls_entropy_context *ctx,
                        mbedtls_entropy_f_source_ptr f_source, void *p_source,
                        size_t threshold, int strong );

/**
 * \brief触发累加器的额外收集轮询（如果启用了MBEDTLS_THREADING_C，则线程安全）
 *
 * \param ctx熵上下文
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_ENTROPY_SOURCE_FAILED
 */
int mbedtls_entropy_gather( mbedtls_entropy_context *ctx );

/**
 * \brief从累加器中检索熵（最大长度：MBEDTLS_entropy_BLOCK_SIZE）（如果启用了MBEDTLS_THREADING_C，则线程安全）
 *
 * \param data熵上下文\param要填充的输出缓冲区\param len所需的字节数，必须最多为MBEDTLS_Entropy_BLOCK_SIZE
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_ENTROPY_SOURCE_FAILED
 */
int mbedtls_entropy_func( void *data, unsigned char *output, size_t len );

/**
 * \brief手动向累加器添加数据（如果启用了MBEDTLS_THREADING_C，则线程安全）
 *
 * \param ctx熵上下文\param data要添加的数据\param len数据长度
 *
 * \如果成功，则返回0
 */
int mbedtls_entropy_update_manual( mbedtls_entropy_context *ctx,
                           const unsigned char *data, size_t len );

#if defined(MBEDTLS_ENTROPY_NV_SEED)
/**
 * \brief使用当前熵池触发NV中种子文件的更新。
 *
 * \param ctx熵上下文
 *
 * \如果成功，则返回0
 */
int mbedtls_entropy_update_nv_seed( mbedtls_entropy_context *ctx );
#endif /* MBEDTLS_ENTROPY_NV_SEED */

#if defined(MBEDTLS_FS_IO)
/**
 * \brief编写种子文件
 *
 * \param ctx熵上下文\param path文件的名称
 *
 * \如果成功，则返回0，文件错误时返回MBEDTLS_ERROR_ENTROPY_FILE_IO_ERROR，或MBEDTLS_ERROR_ENTRPOY_SOURCE_FAILED
 */
int mbedtls_entropy_write_seed_file( mbedtls_entropy_context *ctx, const char *path );

/**
 * \brief读取并更新种子文件。种子将添加到此实例。从种子文件中读取的字节数不超过MBEDTLS_ENTROPY_MAX_SEED_SIZE。其余部分被忽略。
 *
 * \param ctx熵上下文\param path文件的名称
 *
 * \如果成功，则返回0，文件错误时返回MBEDTLS_ERROR_ENTROPY_FILE_IO_ERROR，MBEDTLS_ERROR_ENTRPOY_SOURCE_FAILED
 */
int mbedtls_entropy_update_seed_file( mbedtls_entropy_context *ctx, const char *path );
#endif /* MBEDTLS_FS_IO */

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要检查程序
 *
 *                 该模块自检还调用熵自检mbedtls_entropy_source_self_test（）；
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_entropy_self_test( int verbose );

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)
/**
 * \简要检查程序
 *
 *                 验证函数“mbedtls_hardware_poll（）”提供的硬件熵源的完整性。
 *
 *                 请注意，这是在链接时已知的唯一硬件熵源，其他在运行时由函数mbedtls_entropy_add_source（）动态配置的熵源将不会被测试。
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_entropy_source_self_test( int verbose );
#endif /* MBEDTLS_ENTROPY_HARDWARE_ALT */
#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 熵.h*/

