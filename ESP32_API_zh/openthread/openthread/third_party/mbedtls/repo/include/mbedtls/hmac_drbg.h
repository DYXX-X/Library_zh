/**
 * \文件hmac_drbg.h
 *
 * \简要介绍HMAC_DRBG伪随机生成器。
 *
 * 该模块实现了NIST SP 800-90A：使用确定性随机位生成器生成随机数的建议</em>中描述的HMAC_DRBG伪随机生成器。
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
#ifndef MBEDTLS_HMAC_DRBG_H
#define MBEDTLS_HMAC_DRBG_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/md.h"

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif

/*
 * 错误代码
 */
#define MBEDTLS_ERR_HMAC_DRBG_REQUEST_TOO_BIG              -0x0003  /**<单个呼叫中请求的随机数太多。*/
#define MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG                -0x0005  /**<输入太大（熵+附加）。*/
#define MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR                -0x0007  /**<文件中的读/写错误。*/
#define MBEDTLS_ERR_HMAC_DRBG_ENTROPY_SOURCE_FAILED        -0x0009  /**<熵源失败。*/

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */

#if !defined(MBEDTLS_HMAC_DRBG_RESEED_INTERVAL)
#define MBEDTLS_HMAC_DRBG_RESEED_INTERVAL   10000   /**<默认情况下执行重新设定种子前的间隔*/
#endif

#if !defined(MBEDTLS_HMAC_DRBG_MAX_INPUT)
#define MBEDTLS_HMAC_DRBG_MAX_INPUT         256     /**<附加输入字节的最大数量*/
#endif

#if !defined(MBEDTLS_HMAC_DRBG_MAX_REQUEST)
#define MBEDTLS_HMAC_DRBG_MAX_REQUEST       1024    /**<每次调用请求的最大字节数*/
#endif

#if !defined(MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT)
#define MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT    384     /**<（重新）种子缓冲区的最大大小*/
#endif

/* \}name SECTION:模块设置*/

#define MBEDTLS_HMAC_DRBG_PR_OFF   0   /**<无预测阻力*/
#define MBEDTLS_HMAC_DRBG_PR_ON    1   /**<预测电阻已启用*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * HMAC_DRBG上下文。
 */
typedef struct mbedtls_hmac_drbg_context
{
    /* 工作状态：密钥K不是显式存储的，而是HMAC上下文隐含的*/
    mbedtls_md_context_t md_ctx;                    /*!< HMAC上下文（包括K）*/
    unsigned char V[MBEDTLS_MD_MAX_SIZE];  /*!< 规范中的V*/
    int reseed_counter;                     /*!< 种子计数器*/

    /* 行政状态*/
    size_t entropy_len;         /*!< 每个（再）种子上抓取的熵字节*/
    int prediction_resistance;  /*!< 启用预测阻力（在每次随机生成之前自动重新设定种子）*/
    int reseed_interval;        /*!< 补种间隔*/

    /* 回调*/
    int (*f_entropy)(void *, unsigned char *, size_t); /*!< 熵函数*/
    void *p_entropy;            /*!< 熵函数的上下文*/

#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t mutex;
#endif
} mbedtls_hmac_drbg_context;

/**
 * \简短的HMAC_DRBG上下文初始化。
 *
 * 此函数使上下文为mbedtls_hmac_drbg_seed（）、mbedtls_hmac_drbg_seed_buf（）或mbedtls-hmac_drbb_free（）做好准备。
 *
 * \注意：默认情况下，重置间隔为#MBEDTLS_MAC_DRBG_reseed_interval。通过调用mbedtls_hmac_drbg_set_reseed_interval（）覆盖此值。
 *
 * \param ctx要初始化的HMAC_DRBG上下文。
 */
void mbedtls_hmac_drbg_init( mbedtls_hmac_drbg_context *ctx );

/**
 * \简短的HMAC_DRBG初始播种。
 *
 * 设置初始种子并为未来种子设置熵源。
 *
 * 熵和p_熵参数的典型选择是使用熵模块：
 * -\p f_entropy是mbedtls_entropy_func（）；
 * -\p p_entropy是用mbedtls_entropy_init（）初始化的：：mbedtls_intropy_context的实例（它注册平台的默认熵源）。
 *
 * 除了熵源之外，您还可以提供个性化字符串，以使该实例化尽可能唯一。
 *
 * \注：默认情况下，NIST定义的安全强度为：
 *                      -如果\p md_info为SHA-1，则为128位；
 *                      -如果md_info为SHA-224，则为192位；
 *                      -如果\p md_info为SHA-256、SHA-384或SHA-512，则为256位。请注意，SHA-256与SHA-224一样有效。如果使用mbedtls_hmac_drbg_set_entropy_len（）设置较小的熵长度，则可以降低安全强度。
 *
 * \注意：默认熵长度是安全强度（从位转换为字节）。可以通过调用mbedtls_hmac_drbg_set_entropy_len（）来覆盖它。
 *
 * \注意：在初始播种期间，此函数调用熵源以获得长度为熵长度一半的随机数。
 *
 * \param ctx要设定种子的HMAC_DRBG上下文。\param md_info md算法用于HMAC_DRBG。\param f_entropy熵回调，以\pp_entropy上下文、要填充的缓冲区和缓冲区长度作为参数。\pf_entropy总是以小于或等于熵长度的长度来调用。\param p_entropy要传递给\p f_entropy的熵上下文。\param custom个性化字符串。这可以是空的，在这种情况下，无论\p len的值如何，个性化字符串都是空的。\param len个性化字符串的长度。这最多必须是#MBEDTLS_MAC_DRBG_MAX_INPUT，也最多必须是#MBEDTLS_MAC_DRBG_MAX_SEED_INPUT-\p entropy_len 3/2，其中，\p entropy_ln是上述熵长度。
 *
 * \如果成功，返回\c 0。\如果\p MD_info无效，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。\如果没有足够的内存来分配上下文数据，则返回#MBEDTLS_ERROR_MD_ALLOC_FAILED。\如果对\p f_ENTROPY的调用失败，则返回#MBEDTLS_ERROR_HMAC_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_hmac_drbg_seed( mbedtls_hmac_drbg_context *ctx,
                    const mbedtls_md_info_t * md_info,
                    int (*f_entropy)(void *, unsigned char *, size_t),
                    void *p_entropy,
                    const unsigned char *custom,
                    size_t len );

/**
 * \简化HMAC_DRBG的简短初始化（从不重新设定种子）。
 *
 * 该函数用于需要伪随机输入的算法，如确定性ECDSA。
 *
 * \param ctx要初始化的HMAC_DRBG上下文。\param md_info md算法用于HMAC_DRBG。\param data初始熵串和附加数据的级联。\param data_len \p数据的长度（字节）。
 *
 * \如果成功，返回\c 0。如果MD_info无效，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。\如果没有足够的内存来分配上下文数据，则返回#MBEDTLS_ERROR_MD_ALLOC_FAILED。
 */
int mbedtls_hmac_drbg_seed_buf( mbedtls_hmac_drbg_context *ctx,
                        const mbedtls_md_info_t * md_info,
                        const unsigned char *data, size_t data_len );

/**
 * \brief此函数打开或关闭预测阻力。默认值为关闭。
 *
 * \注意：如果启用，熵将在每次调用mbedtls_hmac_drbg_random_with_add（）或mbedtls_hmac_drbg_random（）的开始处收集。仅当熵源具有足够的吞吐量时才使用此选项。
 *
 * \param ctx HMAC_DRBG上下文。\参数电阻#MBEDTLS_MAC_DRBG_PR_ON或#MBEDLLS_MAC_DRGG_PR_OFF。
 */
void mbedtls_hmac_drbg_set_prediction_resistance( mbedtls_hmac_drbg_context *ctx,
                                          int resistance );

/**
 * \brief此函数设置每个种子或种子重新播种的熵量。
 *
 * 有关默认值，请参阅mbedtls_hmac_drbg_seed（）的文档。
 *
 * \param ctx HMAC_DRBG上下文。\param len要获取的熵量，以字节为单位。
 */
void mbedtls_hmac_drbg_set_entropy_len( mbedtls_hmac_drbg_context *ctx,
                                size_t len );

/**
 * \brief设置重新播种间隔。
 *
 * resed interval是对mbedtls_hmac_drbg_random（）或mbedtls_hmac_drbg_random_with_add（）的调用次数，之后再次调用熵函数。
 *
 * 默认值为#MBEDTLS_MAC_DRBG_RESEED_INTERVAL。
 *
 * \param ctx HMAC_DRBG上下文。\param interval重新设定种子的间隔。
 */
void mbedtls_hmac_drbg_set_reseed_interval( mbedtls_hmac_drbg_context *ctx,
                                    int interval );

/**
 * \brief此函数更新HMAC_DRBG上下文的状态。
 *
 * \param ctx HMAC_DRBG上下文。\param additional用于更新状态的数据。如果为空，则没有其他数据。\param add_len \p附加长度（字节）。如果附加值为空，则不使用。
 *
 * \成功时返回\c 0，或基础哈希计算中的错误。
 */
int mbedtls_hmac_drbg_update_ret( mbedtls_hmac_drbg_context *ctx,
                       const unsigned char *additional, size_t add_len );

/**
 * \brief此函数重新设置HMAC_DRBG上下文，即从熵源中提取数据。
 *
 * \param ctx HMAC_DRBG上下文。\param additional要添加到状态的其他数据。如果这是\c NULL，则没有其他数据，\p len应为\c 0。\param len其他数据的长度。这必须最多为#MBEDTLS_MAC_DRBG_MAX_INPUT，也必须最多为#MBEDTLS_MAC_DRBG_MAX_SEED_INPUT-\p entropy_len，其中\p entropy_ln是熵长度（请参见MBEDTLS_HMAC_DRBG_set_entropy_len（））。
 *
 * \如果成功，返回\c 0。\如果对熵函数的调用失败，则返回#MBEDTLS_ERROR_HMAC_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_hmac_drbg_reseed( mbedtls_hmac_drbg_context *ctx,
                      const unsigned char *additional, size_t len );

/**
 * \brief此函数使用附加数据更新HMAC_DRBG实例，并使用它生成随机数据。
 *
 * 如果超过重置计数器或启用预测电阻，此功能将自动重置。
 *
 * \param p_rng HMAC_DRBG上下文。这必须是指向#mbedtls_hmac_drbg_context结构的指针。\param output要填充的缓冲区。\param output_len缓冲区的长度（字节）。这最多必须为#MBEDTLS_MAC_DRBG_MAX_REQUEST。\param additional要更新的其他数据。如果该值为\c NULL，则没有其他数据，\p add_len应为\c 0。\param add_ln其他数据的长度。这最多必须是#MBEDTLS_MAC_DRBG_MAX_INPUT。
 *
 * \如果成功，返回\c 0。\如果对熵源的调用失败，则返回#MBEDTLS_ERROR_HMAC_DRBG_ENTROPY_SOURCE_FAILED。\返回#MBEDTLS_ERROR_HMAC_DRBG_REQUEST_TOO_BIG，如果\p output_len>#MBEDLLS_HARC_DRBG_MAX_REQUEST。\返回#MBEDTLS_ERROR_HMAC_DRBG_INPUT_TOO_BIG。
 */
int mbedtls_hmac_drbg_random_with_add( void *p_rng,
                               unsigned char *output, size_t output_len,
                               const unsigned char *additional,
                               size_t add_len );

/**
 * \brief此函数使用HMAC_DRBG生成随机数据。
 *
 * 如果超过重置计数器或启用预测电阻，此功能将自动重置。
 *
 * \param p_rng HMAC_DRBG上下文。这必须是指向#mbedtls_hmac_drbg_context结构的指针。\param output要填充的缓冲区。\param out_len缓冲区的长度（字节）。这最多必须为#MBEDTLS_MAC_DRBG_MAX_REQUEST。
 *
 * \如果成功，返回\c 0。\如果对熵源的调用失败，则返回#MBEDTLS_ERROR_HMAC_DRBG_ENTROPY_SOURCE_FAILED。\返回#MBEDTLS_ERROR_HMAC_DRBG_REQUEST_TOO_BIG。
 */
int mbedtls_hmac_drbg_random( void *p_rng, unsigned char *output, size_t out_len );

/**
 * \brief此函数在初次调用mbedtls_HMAC_DRBG_init（）后立即将HMAC_DRBG上下文重置为状态。
 *
 * \param ctx要释放的HMAC_DRBG上下文。
 */
void mbedtls_hmac_drbg_free( mbedtls_hmac_drbg_context *ctx );

#if ! defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数更新HMAC_DRBG上下文的状态。
 *
 * \已弃用在2.16.0中被mbedtls_hmac_drbg_update_ret（）取代。
 *
 * \param ctx HMAC_DRBG上下文。\param additional用于更新状态的数据。如果为空，则没有其他数据。\param add_len \p附加长度（字节）。如果附加值为空，则不使用。
 */
MBEDTLS_DEPRECATED void mbedtls_hmac_drbg_update(
    mbedtls_hmac_drbg_context *ctx,
    const unsigned char *additional, size_t add_len );
#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_FS_IO)
/**
 * \brief此函数编写种子文件。
 *
 * \param ctx HMAC_DRBG上下文。\param path文件的名称。
 *
 * \成功时返回\c 0。\文件错误时返回#MBEDTLS_ERROR_HMAC_DRBG_FILE_IO_ERROR。\复位失败时返回#MBEDTLS_ERROR_HMAC_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_hmac_drbg_write_seed_file( mbedtls_hmac_drbg_context *ctx, const char *path );

/**
 * \brief此函数读取并更新种子文件。种子将添加到此实例。
 *
 * \param ctx HMAC_DRBG上下文。\param path文件的名称。
 *
 * \成功时返回\c 0。\文件错误时返回#MBEDTLS_ERROR_HMAC_DRBG_FILE_IO_ERROR。\复位失败时返回#MBEDTLS_ERROR_HMAC_DRBG_ENTROPY_SOURCE_FAILED。\如果现有种子文件太大，则返回#MBEDTLS_ERROR_HMAC_DRBG_INPUT_TOO_BIG。
 */
int mbedtls_hmac_drbg_update_seed_file( mbedtls_hmac_drbg_context *ctx, const char *path );
#endif /* MBEDTLS_FS_IO */


#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要介绍HMAC_DRBG检查例程。
 *
 * \如果成功，返回\c 0。\如果测试失败，则返回\c 1。
 */
int mbedtls_hmac_drbg_self_test( int verbose );
#endif

#ifdef __cplusplus
}
#endif

#endif /* hmac_drbg.h文件*/

