/**
 * \文件aria.h
 *
 * \ARIA分组密码
 *
 *        ARIA算法是一种可以加密和解密信息的对称分组密码。它由韩国技术标准局（KATS）在<em>KS X 1213:2004</em>中定义（韩语，但请参见http://210.104.33.10/ARIA/index-e.html英语），也由IETF在RFC 5794</em>中描述。
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

#ifndef MBEDTLS_ARIA_H
#define MBEDTLS_ARIA_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#include "mbedtls/platform_util.h"

#define MBEDTLS_ARIA_ENCRYPT     1 /**<ARIA加密。*/
#define MBEDTLS_ARIA_DECRYPT     0 /**<ARIA解密。*/

#define MBEDTLS_ARIA_BLOCKSIZE   16 /**<ARIA块大小（字节）。*/
#define MBEDTLS_ARIA_MAX_ROUNDS  16 /**<ARIA中的最大轮数。*/
#define MBEDTLS_ARIA_MAX_KEYSIZE 32 /**<ARIA密钥的最大大小（字节）。*/

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#define MBEDTLS_ERR_ARIA_INVALID_KEY_LENGTH   MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( -0x005C )
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
/**错误的输入数据。*/
#define MBEDTLS_ERR_ARIA_BAD_INPUT_DATA -0x005C

/**数据输入长度无效。*/
#define MBEDTLS_ERR_ARIA_INVALID_INPUT_LENGTH -0x005E

/* MBEDTLS_ERROR_ARIA_FEATURE_NAVAILABLE已弃用，不应使用。
 */
/**功能不可用。例如，不支持的ARIA密钥大小。*/
#define MBEDTLS_ERR_ARIA_FEATURE_UNAVAILABLE  -0x005A

/* MBEDTLS_ERROR_ARIA_HW_ACCEL_FAILED已弃用，不应使用。*/
/**ARIA硬件加速器失败。*/
#define MBEDTLS_ERR_ARIA_HW_ACCEL_FAILED      -0x0058

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_ARIA_ALT)
// 定期实施
//

/**
 * \brief ARIA上下文类型定义。
 */
typedef struct mbedtls_aria_context
{
    unsigned char nr;           /*!< 轮数（12、14或16）*/
    /*! ARIA圆形钥匙。*/
    uint32_t rk[MBEDTLS_ARIA_MAX_ROUNDS + 1][MBEDTLS_ARIA_BLOCKSIZE / 4];
}
mbedtls_aria_context;

#else  /* MBEDTLS_ARIA_ALT */
#include "aria_alt.h"
#endif /* MBEDTLS_ARIA_ALT */

/**
 * \brief此函数初始化指定的ARIA上下文。
 *
 *                 它必须是在使用上下文之前调用的第一个API。
 *
 * \param ctx要初始化的ARIA上下文。此值不能为空。
 */
void mbedtls_aria_init( mbedtls_aria_context *ctx );

/**
 * \brief此函数释放并清除指定的ARIA上下文。
 *
 * \param ctx要清除的ARIA上下文。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空，则必须指向已初始化的ARIA上下文。
 */
void mbedtls_aria_free( mbedtls_aria_context *ctx );

/**
 * \brief此函数设置加密密钥。
 *
 * \param ctx键应绑定到的ARIA上下文。必须对其进行初始化。\param key加密密钥。这必须是大小为\p keybits Bits的可读缓冲区。\param keybits \p键的大小（以位为单位）。有效选项为：＜ul＞＜li＞128位＜/li＞＜li＜192位＜/li>＜li＞256位＜/li＞＜/ul＞
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_aria_setkey_enc( mbedtls_aria_context *ctx,
                             const unsigned char *key,
                             unsigned int keybits );

/**
 * \brief此函数设置解密密钥。
 *
 * \param ctx键应绑定到的ARIA上下文。必须对其进行初始化。\param key解密密钥。这必须是大小为\p keybits Bits的可读缓冲区。\param keybits传递的数据大小。有效选项为：＜ul＞＜li＞128位＜/li＞＜li＜192位＜/li>＜li＞256位＜/li＞＜/ul＞
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_aria_setkey_dec( mbedtls_aria_context *ctx,
                             const unsigned char *key,
                             unsigned int keybits );

/**
 * \brief此函数执行ARIA单块加密或解密操作。
 *
 *                 它对\p输入参数中定义的输入数据缓冲区执行加密或解密（取决于密钥是否设置为解密时加密）。
 *
 *                 在第一次调用具有相同上下文的此API之前，必须调用mbedtls_aria_init（）和mbedtls_aria_setkey_enc（）或mbedtls-aria_setkkey_dec（）。
 *
 * \param ctx用于加密或解密的ARIA上下文。这必须初始化并绑定到密钥。\param input保存输入数据的16字节缓冲区。\param output保存输出数据的16字节缓冲区。

 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_aria_crypt_ecb( mbedtls_aria_context *ctx,
                            const unsigned char input[MBEDTLS_ARIA_BLOCKSIZE],
                            unsigned char output[MBEDTLS_ARIA_BLOCKSIZE] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \brief此函数对完整块执行ARIA-CBC加密或解密操作。
 *
 *         它对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密/解密）中定义的操作。
 *
 *         它可以根据需要调用多次，直到处理完所有输入数据。在第一次调用具有相同上下文的此API之前，必须调用mbedtls_aria_init（）和mbedtls_aria_setkey_enc（）或mbedtls-aria_setkkey_dec（）。
 *
 * \注意：此函数对对齐的块进行操作，即输入大小必须是ARIA块大小16字节的倍数。
 *
 * \注意：退出后，IV的内容将更新，以便您可以在下一个数据块上再次调用相同的函数，并获得与在一次调用中加密相同的结果。这允许“流式”使用。如果您需要保留IV的内容，您应该手动保存或使用密码模块。
 *
 * \param ctx用于加密或解密的ARIA上下文。这必须初始化并绑定到密钥。\param mode操作模式。加密时必须为#MBEDTLS_ARIA_ENCRYPT，解密时必须为#MBEDTLS_ARIA_DECRYPT。\param length输入数据的长度（以字节为单位）。这必须是块大小（16字节）的倍数。\param iv初始化向量（使用后更新）。这必须是大小为16字节的可读缓冲区。\param input保存输入数据的缓冲区。这必须是长度为\p-length Bytes的可读缓冲区。\param output保存输出数据的缓冲区。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_aria_crypt_cbc( mbedtls_aria_context *ctx,
                            int mode,
                            size_t length,
                            unsigned char iv[MBEDTLS_ARIA_BLOCKSIZE],
                            const unsigned char *input,
                            unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
/**
 * \brief此函数执行ARIA-CFB128加密或解密操作。
 *
 *        它对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密或解密）中定义的操作。
 *
 *        对于CFB，您必须使用mbedtls_aria_setkey_enc（）设置上下文，无论您是执行加密还是解密操作，也就是说，无论\p mode参数如何。这是因为CFB模式使用相同的密钥调度进行加密和解密。
 *
 * \注意：退出后，IV的内容将更新，以便您可以在下一个数据块上再次调用相同的函数，并获得与在一次调用中加密相同的结果。这允许“流式”使用。如果您需要保留IV的内容，则必须手动保存或使用密码模块。
 *
 * \param ctx用于加密或解密的ARIA上下文。这必须初始化并绑定到密钥。\param mode操作模式。加密时必须为#MBEDTLS_ARIA_ENCRYPT，解密时必须为#MBEDTL_ARIA_DECRYPT。\param length输入数据的长度，以字节为单位。\param iv_off iv中的偏移量（使用后更新）。该值不得大于15。\param iv初始化向量（使用后更新）。这必须是大小为16字节的可读缓冲区。\param input保存输入数据的缓冲区。这必须是长度为\p-length Bytes的可读缓冲区。\param output保存输出数据的缓冲区。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_aria_crypt_cfb128( mbedtls_aria_context *ctx,
                               int mode,
                               size_t length,
                               size_t *iv_off,
                               unsigned char iv[MBEDTLS_ARIA_BLOCKSIZE],
                               const unsigned char *input,
                               unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
/**
 * \brief此函数执行ARIA-CTR加密或解密操作。
 *
 *             此函数对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密/解密）中定义的操作。
 *
 *             由于CTR的性质，加密和解密操作必须使用相同的密钥计划。因此，必须对#mbedtls_aria_ENCRYPT和#MBEDLLS_aria_DECRYPT使用使用mbedtls_aria_setkey_enc（）初始化的上下文。
 *
 * \警告您决不能使用同一密钥重复使用nonce值。这样做将使使用相同的随机数和密钥加密的两条消息的加密无效。
 *
 *             有两种常用的策略来管理CTR的随机数：
 *
 *             1.您可以将所有内容作为一条消息处理，该消息通过对该函数的连续调用进行处理。在这种情况下，您希望将第一次调用的\p nonce_counter和\p nc_off设置为0，然后在对该函数的调用中保留\p nonce _counter、\p nc_off和\p stream_block的值，因为它们将被该函数更新。
 *
 *             使用此策略，您不能使用同一密钥加密超过2**128个数据块。
 *
 *             2.您可以通过将\p nonce_counter缓冲区划分为两个区域来加密单独的消息：第一个区域用于您自己处理的每条消息nonce，第二个区域由此函数内部更新。
 *
 *             例如，您可以为每条消息的随机数保留前12个字节，为内部使用保留最后4个字节。在这种情况下，在对新消息调用此函数之前，您需要将nonce_counter的前12个字节设置为所选的nonce值，将最后4个设置为0，将nc_off设置为0（这将导致忽略stream_block）。这样，您可以使用相同的密钥加密最多296条消息，每个消息最多232个块。
 *
 *             每条消息的随机数（或足以重建它的信息）需要与密文通信，并且必须是唯一的。确保唯一性的建议方法是使用消息计数器。另一种方法是生成随机随机数，但这限制了可以安全加密的消息数量：例如，使用96位随机随机数时，使用相同密钥加密的消息不应超过232条。
 *
 *             注意，对于这两种策略，大小以块为单位，ARIA块为16字节。
 *
 * \警告返回时，\p stream_block包含敏感数据。其内容不得写入不安全的存储，一旦不再需要，应立即安全丢弃。
 *
 * \param ctx用于加密或解密的ARIA上下文。这必须初始化并绑定到密钥。\param length输入数据的长度，以字节为单位。\param nc_off当前流块中的偏移量（字节），用于在当前密码流中恢复。偏移指针应位于流的开头。这不能大于\c 15字节。\param nonce_counter 128位的nonce和计数器。这必须指向长度为\c 16字节的读/写缓冲区。\param stream_block用于恢复的已保存流块。这必须指向长度为\c 16字节的读/写缓冲区。这将被函数覆盖。\param input保存输入数据的缓冲区。这必须是长度为\p-length Bytes的可读缓冲区。\param output保存输出数据的缓冲区。这必须是长度为\p-length Bytes的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_aria_crypt_ctr( mbedtls_aria_context *ctx,
                            size_t length,
                            size_t *nc_off,
                            unsigned char nonce_counter[MBEDTLS_ARIA_BLOCKSIZE],
                            unsigned char stream_block[MBEDTLS_ARIA_BLOCKSIZE],
                            const unsigned char *input,
                            unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CTR */

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简短的检查程序。
 *
 * \成功时返回\c 0，失败时返回\c1。
 */
int mbedtls_aria_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 咏叹调*/

