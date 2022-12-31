/**
 * \文件ctr_drbg.h
 *
 * \这个文件包含CTR_DRBG伪随机生成器的定义和函数。
 *
 * CTR_DRBG是一种在计数器模式操作中从分组密码构建PRNG的标准化方法，如<em>NIST SP 800-90A：使用确定性随机位生成器生成随机数的建议</em>中所定义。
 *
 * CTR_DRBG的Mbed TLS实现使用AES-256（默认值）或AES-128（如果编译时启用了MBEDTLS_CTR_DRBG_USE_128_BIT_KEY）作为基础分组密码，并带有派生函数。
 *
 * 使用AES-128时，NIST SP 800-90A中定义的安全强度为128位（启用MBEDTLS_CTR_DRBG_USE_128_BIT_KEY），否则为256位，前提是#MBEDTL_CTR_DRBG_ENTROPY_LEN保持在其默认值（且未在config.h中覆盖），并且DRBG实例设置为默认参数。有关详细信息，请参阅mbedtls_ctr_drbg_seed（）的文档。
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

#ifndef MBEDTLS_CTR_DRBG_H
#define MBEDTLS_CTR_DRBG_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/aes.h"

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif

/**熵源失败。*/
#define MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED        -0x0034
/**请求的随机缓冲区长度太大。*/
#define MBEDTLS_ERR_CTR_DRBG_REQUEST_TOO_BIG              -0x0036
/**输入（熵+附加数据）太大。*/
#define MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG                -0x0038
/**文件中存在读取或写入错误。*/
#define MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR                -0x003A

#define MBEDTLS_CTR_DRBG_BLOCKSIZE          16 /**<密码使用的块大小。*/

#if defined(MBEDTLS_CTR_DRBG_USE_128_BIT_KEY)
#define MBEDTLS_CTR_DRBG_KEYSIZE            16
/**< 密码使用的密钥大小（字节）。
 *
 * 编译时间选择：16字节（128位），因为#MBEDTLS_CTR_DRBG_USE_128_BIT_KEY已启用。
 */
#else
#define MBEDTLS_CTR_DRBG_KEYSIZE            32
/**< 密码使用的密钥大小（字节）。
 *
 * 编译时间选择：32字节（256位），因为禁用了\c MBEDTLS_CTR_DRBG_USE_128_BIT_KEY。
 */
#endif

#define MBEDTLS_CTR_DRBG_KEYBITS            ( MBEDTLS_CTR_DRBG_KEYSIZE * 8 ) /**<DRBG操作的密钥大小，以位为单位。*/
#define MBEDTLS_CTR_DRBG_SEEDLEN            ( MBEDTLS_CTR_DRBG_KEYSIZE + MBEDTLS_CTR_DRBG_BLOCKSIZE ) /**<种子长度，计算为（计数器+AES密钥）。*/

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或使用编译器命令行定义它们\{
 */

/** \定义MBEDTLS_CTR_DRBG_ENTROPY_LEN
 *
 * \brief默认情况下每个种子使用的熵量，以字节为单位。
 */
#if !defined(MBEDTLS_CTR_DRBG_ENTROPY_LEN)
#if defined(MBEDTLS_SHA512_C) && !defined(MBEDTLS_ENTROPY_FORCE_SHA256)
/** 这是48字节，因为熵模块使用SHA-512（\c MBEDTLS_entropy_FORCE_SHA256被禁用）。
 */
#define MBEDTLS_CTR_DRBG_ENTROPY_LEN        48

#else /* 已定义（MBEDTLS_HA512_C）&&！已定义（MBEDTLS_ENTROPY_FORCE_SHA256）*/

/** 这是32字节，因为熵模块使用SHA-256（禁用SHA512模块或启用MBEDTLS_entropy_FORCE_SHA256）。
 */
#if !defined(MBEDTLS_CTR_DRBG_USE_128_BIT_KEY)
/** \警告要达到256位安全强度，必须向mbedtls_ctr_drbg_seed（）传递一个nonce。
 */
#endif /* !已定义（MBEDTLS_CTR_DRBG_USE_128_BIT_KEY）*/
#define MBEDTLS_CTR_DRBG_ENTROPY_LEN        32
#endif /* 已定义（MBEDTLS_HA512_C）&&！已定义（MBEDTLS_ENTROPY_FORCE_SHA256）*/
#endif /* !已定义（MBEDTLS_CTR_DRBG_ENTROPY_LEN）*/

#if !defined(MBEDTLS_CTR_DRBG_RESEED_INTERVAL)
#define MBEDTLS_CTR_DRBG_RESEED_INTERVAL    10000
/**<默认情况下执行重新设定种子之前的间隔。*/
#endif

#if !defined(MBEDTLS_CTR_DRBG_MAX_INPUT)
#define MBEDTLS_CTR_DRBG_MAX_INPUT          256
/**<附加输入字节的最大数量。*/
#endif

#if !defined(MBEDTLS_CTR_DRBG_MAX_REQUEST)
#define MBEDTLS_CTR_DRBG_MAX_REQUEST        1024
/**<每次调用请求的最大字节数。*/
#endif

#if !defined(MBEDTLS_CTR_DRBG_MAX_SEED_INPUT)
#define MBEDTLS_CTR_DRBG_MAX_SEED_INPUT     384
/**<种子或种子设定缓冲区的最大大小（字节）。*/
#endif

/* \}name SECTION:模块设置*/

#define MBEDTLS_CTR_DRBG_PR_OFF             0
/**<预测阻力被禁用。*/
#define MBEDTLS_CTR_DRBG_PR_ON              1
/**<预测电阻已启用。*/

#ifdef __cplusplus
extern "C" {
#endif

#if MBEDTLS_CTR_DRBG_ENTROPY_LEN >= MBEDTLS_CTR_DRBG_KEYSIZE * 3 / 2
/** 从熵源读取的随机数的默认长度。
 *
 * 这是\c 0，因为从熵源读取一次就足以包含随机数。有关详细信息，请参阅mbedtls_ctr_drbg_seed（）的文档。
 */
#define MBEDTLS_CTR_DRBG_ENTROPY_NONCE_LEN 0
#else
/** 从熵源读取的随机数的默认长度。
 *
 * 这是默认熵长度的一半，因为从熵源的单个读取不提供足够的材料来形成随机数。有关详细信息，请参阅mbedtls_ctr_drbg_seed（）的文档。
 */
#define MBEDTLS_CTR_DRBG_ENTROPY_NONCE_LEN ( MBEDTLS_CTR_DRBG_ENTROPY_LEN + 1 ) / 2
#endif

/**
 * \简要介绍CTR_DRBG上下文结构。
 */
typedef struct mbedtls_ctr_drbg_context
{
    unsigned char counter[16];  /*!< 计数器（V）。*/
    int reseed_counter;         /*!< 重新设定种子的计数器。这是自上次（重新）播种以来发出的请求数，减去1。在初始种子设定之前，此字段包含要用作初始种子设定的随机数的熵量（以字节为单位），如果未显式设置随机数长度，则为-1（请参阅mbedtls_ctr_drbg_set_nonce_len（））。
                                 */
    int prediction_resistance;  /*!< 这决定是否启用预测阻力，即是否在每次随机生成之前系统地重新播种。*/
    size_t entropy_len;         /*!< 每个种子或种子重新设定操作所获取的熵量，以字节为单位。*/
    int reseed_interval;        /*!< 重新播种的间隔。这是重置之间可以发出的最大请求数。*/

    mbedtls_aes_context aes_ctx;        /*!< AES上下文。*/

    /*
     * 回调（熵）
     */
    int (*f_entropy)(void *, unsigned char *, size_t);
                                /*!< 熵回调函数。*/

    void *p_entropy;            /*!< 熵函数的上下文。*/

#if defined(MBEDTLS_THREADING_C)
    /* 不变量：当且仅当f_entropy！=无效的。这意味着互斥体在mbedtls_ctr_drbg_seed（）中的初始种子设定期间初始化，并在mbedtls _ctr_drbg_free（）中释放。
     *
     * 请注意，此不变量可能会更改，恕不另行通知。不要依赖它，也不要在应用程序代码中直接访问互斥锁。
     */
    mbedtls_threading_mutex_t mutex;
#endif
}
mbedtls_ctr_drbg_context;

/**
 * \brief此函数初始化CTR_DRBG上下文，并为mbedtls_CTR_DRBG_seed（）或mbedtls_CTR_DRBG_free（）做好准备。
 *
 * \注意：默认情况下，重置间隔为#MBEDTLS_CTR_DRBG_reseed_interval。您可以通过调用mbedtls_ctr_drbg_set_reseed_interval（）来覆盖它。
 *
 * \param ctx要初始化的CTR_DRBG上下文。
 */
void mbedtls_ctr_drbg_init( mbedtls_ctr_drbg_context *ctx );

/**
 * \brief此函数为将来的种子设定CTR_DRBG熵源。
 *
 * 熵和p_熵参数的典型选择是使用熵模块：
 * -\p f_entropy是mbedtls_entropy_func（）；
 * -\p p_entropy是用mbedtls_entropy_init（）初始化的：：mbedtls_intropy_context的实例（它注册平台的默认熵源）。
 *
 * 默认情况下，熵长度为#MBEDTLS_CTR_DRBG_entropy_LEN。可以通过调用mbedtls_ctr_drbg_set_entropy_len（）来覆盖它。
 *
 * 熵随机数长度为：
 * -\c 0如果熵长度至少为熵长度的3/2倍，这保证了安全强度是根据NIST SP 800-90A§10.2.1密钥大小和熵长度所允许的最大值；
 * -否则为熵长度的一半。可以通过调用mbedtls_ctr_drbg_set_nonce_len（）来覆盖它。对于默认熵长度，熵随机数长度为#MBEDTLS_CTR_DRBG_entropy_nonce_LEN。
 *
 * 除了熵源之外，还可以提供随机数和个性化字符串，以使此实例化尽可能唯一。有关随机数的详细信息，请参见SP 800-90A§8.6.7。
 *
 * NIST SP 800-90A§10.2.1.3.2中描述的CTR_DRBG实例化过程中传递给派生函数的_sed_material_值是以下字符串的串联：
 * -通过为熵长度调用\pf_entropy函数获得的字符串。
 */
#if MBEDTLS_CTR_DRBG_ENTROPY_NONCE_LEN == 0
/**
 * -如果已调用mbedtls_ctr_drbg_set_nonce_len（），则为通过调用指定长度的\pf_entropy函数获得的字符串。
 */
#else
/**
 * -通过为熵随机数长度调用\pf_entropy函数获得的字符串。如果熵随机数长度为\c 0，则此函数不会再次调用\p f_entropy。
 */
#endif
#if defined(MBEDTLS_THREADING_C)
/**
 * \注意：当使用线程支持构建Mbed TLS时，在该函数成功返回后，可以从多个线程调用mbedtls_ctr_drbg_random（）。其他操作，包括重新种子，不是线程安全的。
 */
#endif /* MBEDTLS_THREADING_C */
/**
 * -\p自定义字符串。
 *
 * \注：为了达到CTR_DRBG允许的标称安全强度，熵长度必须为：
 *                      -128位强度（使用AES-128时的最大可实现强度）至少16字节；
 *                      -对于256比特强度（使用AES-256时的最大可实现强度），至少32字节。
 *
 *                      此外，如果未在自定义中传递随机数，则熵长度和熵随机数长度之和必须为：
 *                      -128位强度（使用AES-128时的最大可实现强度）至少24字节；
 *                      -对于256比特强度（使用AES-256时的最大可实现强度），至少48字节。
 *
 * \param ctx要种子的CTR_DRBG上下文。它必须已使用mbedtls_ctr_drbg_init（）初始化。在成功调用mbedtls_ctr_drbg_seed（）之后，除非首先再次调用mbedtls _ctr_drbg_free（）和mbedtls_ctr_drbg_init（），否则不能在同一上下文中再次调用mbedtls_ctr_drbg_see（）。调用mbedtls_ctr_drbg_seed（）失败后，必须调用mbedtls _ctr_drgg_free（）。\param f_entropy熵回调，以\pp_entropy上下文、要填充的缓冲区和缓冲区长度作为参数。\总是在缓冲区大小小于或等于熵长度的情况下调用pf_entropy。\param p_entropy要传递给\p f_entropy的熵上下文。\param custom个性化字符串。这可以是空的，在这种情况下，无论\p len的值如何，个性化字符串都是空的。\param len个性化字符串的长度。这最多必须是#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT
 *                      - #MBEDTLS_CTR_DRBG_ENTROPY_LEN.
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_ctr_drbg_seed( mbedtls_ctr_drbg_context *ctx,
                   int (*f_entropy)(void *, unsigned char *, size_t),
                   void *p_entropy,
                   const unsigned char *custom,
                   size_t len );

/**
 * \brief此函数在初始调用mbedtls_CTR_DRBG_init（）后立即将CTR_DRBG上下文重置为状态。
 *
 * \param ctx要清除的CTR_DRBG上下文。
 */
void mbedtls_ctr_drbg_free( mbedtls_ctr_drbg_context *ctx );

/**
 * \brief此函数打开或关闭预测阻力。默认值为关闭。
 *
 * \注意：如果启用，熵将在每次调用mbedtls_ctr_drbg_random_with_add（）或mbedtls_ctr_drbg_random（）的开始处收集。仅当熵源具有足够的吞吐量时才使用此选项。
 *
 * \param ctx CTR_DRBG上下文。\参数电阻#MBEDTLS_CTR_DRBG_PR_ON或#MBEDTLS_CTR_DRBG_PR_OFF。
 */
void mbedtls_ctr_drbg_set_prediction_resistance( mbedtls_ctr_drbg_context *ctx,
                                         int resistance );

/**
 * \brief此函数设置每个种子或种子重新播种的熵量。
 *
 * 默认值为#MBEDTLS_CTR_DRBG_ENTROPY_LEN。
 *
 * \注意CTR_DRBG的安全强度受熵长度的限制。因此：
 *                      -使用AES-256时（默认禁用MBEDTLS_CTR_DRBG_USE_128_BIT_KEY），\p长度必须至少为32（以字节为单位）才能达到256位强度。
 *                      -使用AES-128时（启用了MBEDTLS_CTR_DRBG_USE_128_BIT_KEY），长度必须至少为16（以字节为单位）才能达到128位强度。
 *
 * \param ctx CTR_DRBG上下文。\param len要获取的熵量，以字节为单位。这最多必须是#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT，最多必须是上下文中设置的熵函数所接受的最大长度。
 */
void mbedtls_ctr_drbg_set_entropy_len( mbedtls_ctr_drbg_context *ctx,
                               size_t len );

/**
 * \brief此函数将获取的熵量设置为初始种子的随机数。
 *
 * 在调用mbedtls_ctr_drbg_seed（）以在初始播种期间从熵源读取随机数之前，请先调用此函数。
 *
 * \param ctx CTR_DRBG上下文。\param len为随机数获取的熵量，以字节为单位。这最多必须是#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT，最多必须是上下文中设置的熵函数所接受的最大长度。
 *
 * \成功时返回\c 0。\如果长度大于#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT，则返回#MBEDLS_ERR_CTR_DRBG_INPUT_TOO_BIG。\如果初始种子设定已经发生，则返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_ctr_drbg_set_nonce_len( mbedtls_ctr_drbg_context *ctx,
                                    size_t len );

/**
 * \brief此函数设置重新设定种子的间隔。
 *
 * 重置间隔是对mbedtls_ctr_drbg_random（）或mbedtls_ctr_drbg_random_with_add（）的调用次数，之后再次调用熵函数。
 *
 * 默认值为#MBEDTLS_CTR_DRBG_RESEED_INTERVAL。
 *
 * \param ctx CTR_DRBG上下文。\param interval重新设定种子的间隔。
 */
void mbedtls_ctr_drbg_set_reseed_interval( mbedtls_ctr_drbg_context *ctx,
                                   int interval );

/**
 * \brief此函数重新设置CTR_DRBG上下文，即从熵源中提取数据。
 *
 * \注意：此函数不是线程安全的。如果另一个线程可能同时从同一上下文中获取随机数，或者更新或重新设定同一上下文，则调用此函数是不安全的。
 *
 * \param ctx CTR_DRBG上下文。\param additional要添加到状态的其他数据。不能为空。\param len附加数据的长度。这必须小于#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT-\c entropy_len，其中\c entropy_ln是为上下文配置的熵长度。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_ctr_drbg_reseed( mbedtls_ctr_drbg_context *ctx,
                     const unsigned char *additional, size_t len );

/**
 * \brief此函数更新CTR_DRBG上下文的状态。
 *
 * \注意：此函数不是线程安全的。如果另一个线程可能同时从同一上下文中获取随机数，或者更新或重新设定同一上下文，则调用此函数是不安全的。
 *
 * \param ctx CTR_DRBG上下文。\param additional用于更新状态的数据。除非\p add_len为\c 0，否则该值不能为\c NULL。\param add_len\p附加长度（以字节为单位）。这最多必须是#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT。
 *
 * \成功时返回\c 0。\如果add_len大于#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT，则返回#MBEDLLS_ERROR_CTR_DRBG_INPUT_TOO_BIG。\return失败时来自基础AES密码的错误。
 */
int mbedtls_ctr_drbg_update_ret( mbedtls_ctr_drbg_context *ctx,
                                 const unsigned char *additional,
                                 size_t add_len );

/**
 * \brief此函数使用附加数据更新CTR_DRBG实例，并使用它生成随机数据。
 *
 * 如果超过重置计数器或启用预测电阻，此功能将自动重置。
 *
 * \注意：此函数不是线程安全的。如果另一个线程可能同时从同一上下文中获取随机数，或者更新或重新设定同一上下文，则调用此函数是不安全的。
 *
 * \param p_rng CTR_DRBG上下文。这必须是指向#mbedtls_ctr_drbg_context结构的指针。\param output要填充的缓冲区。\param output_len缓冲区的长度（字节）。\param additional要更新的其他数据。可以为空，在这种情况下，附加数据为空，而不考虑\p add_len的值。\param add_len如果\p addition不是\c NULL，则附加数据的长度。此值必须小于#MBEDTLS_CTR_DRBG_MAX_INPUT，并且小于#MBETTLS_CTR-DRBG_MAX_SEED_INPUT-\c entropy_len，其中\c entropy_ln是为上下文配置的熵长度。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED或#MBEDRLS_ERROR_CTR _DRBG_REQUEST_TOO_BIG。
 */
int mbedtls_ctr_drbg_random_with_add( void *p_rng,
                              unsigned char *output, size_t output_len,
                              const unsigned char *additional, size_t add_len );

/**
 * \brief此函数使用CTR_DRBG生成随机数据。
 *
 * 如果超过重置计数器或启用预测电阻，此功能将自动重置。
 */
#if defined(MBEDTLS_THREADING_C)
/**
 * \注意：当使用线程支持构建Mbed TLS时，从多个线程调用mbedtls_ctr_drbg_random（）是安全的。其他操作，包括重新种子，不是线程安全的。
 */
#endif /* MBEDTLS_THREADING_C */
/**
 * \param p_rng CTR_DRBG上下文。这必须是指向#mbedtls_ctr_drbg_context结构的指针。\param output要填充的缓冲区。\param output_len缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED或#MBEDRLS_ERROR_CTR _DRBG_REQUEST_TOO_BIG。
 */
int mbedtls_ctr_drbg_random( void *p_rng,
                     unsigned char *output, size_t output_len );


#if ! defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数更新CTR_DRBG上下文的状态。
 *
 * \已弃用在2.16.0中被mbedtls_ctr_drbg_update_ret（）取代。
 *
 * \注意：如果\p add_len大于#MBEDTLS_CTR_DRBG_MAX_SEED_INPUT，则仅使用第一个#MBEDLS_CTR_DRBG_MAX_SEED_ININPUT字节。剩余的字节将被默默丢弃。
 *
 * \param ctx CTR_DRBG上下文。\param additional用于更新状态的数据。\param add_len其他数据的长度。
 */
MBEDTLS_DEPRECATED void mbedtls_ctr_drbg_update(
    mbedtls_ctr_drbg_context *ctx,
    const unsigned char *additional,
    size_t add_len );
#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_FS_IO)
/**
 * \brief此函数编写种子文件。
 *
 * \param ctx CTR_DRBG上下文。\param path文件的名称。
 *
 * \成功时返回\c 0。\文件错误时返回#MBEDTLS_ERROR_CTR_DRBG_FILE_IO_ERROR。\复位失败时返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED。
 */
int mbedtls_ctr_drbg_write_seed_file( mbedtls_ctr_drbg_context *ctx, const char *path );

/**
 * \brief此函数读取并更新种子文件。种子将添加到此实例。
 *
 * \param ctx CTR_DRBG上下文。\param path文件的名称。
 *
 * \成功时返回\c 0。\文件错误时返回#MBEDTLS_ERROR_CTR_DRBG_FILE_IO_ERROR。\复位失败时返回#MBEDTLS_ERROR_CTR_DRBG_ENTROPY_SOURCE_FAILED。\如果现有种子文件太大，则返回#MBEDTLS_ERROR_CTR_DRBG_INPUT_TOO_BIG。
 */
int mbedtls_ctr_drbg_update_seed_file( mbedtls_ctr_drbg_context *ctx, const char *path );
#endif /* MBEDTLS_FS_IO */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要介绍CTR_DRBG检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_ctr_drbg_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* ctr_drbg.h*/

