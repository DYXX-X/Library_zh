/**
 * \文件aes.h
 *
 * \brief此文件包含AES定义和函数。
 *
 *          高级加密标准（AES）指定了FIPS批准的加密算法，可用于保护电子数据。
 *
 *          AES算法是一种可以加密和解密信息的对称分组密码。有关详细信息，请参阅FIPS出版物197：高级加密标准</em>和ISO/IEC 18033-2:2006：信息技术——安全技术——加密算法——第2部分：非对称密码</em>。
 *
 *          AES-XTS块模式由NIST SP 800-38E标准化<https://nvlpubs.nist.gov/nistpubs/legacy/sp/nistspecialpublication800-38e.pdf>并由IEEE P1619详细描述<https://ieeexplore.ieee.org/servlet/opac?punumber=4375278>.
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

#ifndef MBEDTLS_AES_H
#define MBEDTLS_AES_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* 挂锁。c和aesni。c依赖这些值！*/
#define MBEDTLS_AES_ENCRYPT     1 /**<AES加密。*/
#define MBEDTLS_AES_DECRYPT     0 /**<AES解密。*/

/* 范围0x0020-0x0022内的错误代码*/
#define MBEDTLS_ERR_AES_INVALID_KEY_LENGTH                -0x0020  /**<密钥长度无效。*/
#define MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH              -0x0022  /**<数据输入长度无效。*/

/* 范围0x0021-0x0025内的错误代码*/
#define MBEDTLS_ERR_AES_BAD_INPUT_DATA                    -0x0021  /**<输入数据无效。*/

/* MBEDTLS_ERROR_AES_FEATURE_NAVAILABLE已弃用，不应使用。*/
#define MBEDTLS_ERR_AES_FEATURE_UNAVAILABLE               -0x0023  /**<功能不可用。例如，不支持的AES密钥大小。*/

/* MBEDTLS_ERROR_AES_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_AES_HW_ACCEL_FAILED                   -0x0025  /**<AES硬件加速器失败。*/

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_AES_ALT)
// 定期实施
//

/**
 * \brief AES上下文类型定义。
 */
typedef struct mbedtls_aes_context
{
    int nr;                     /*!< 轮数。*/
    uint32_t *rk;               /*!< AES圆键。*/
    uint32_t buf[68];           /*!< 未对齐的数据缓冲区。此缓冲区可容纳32个额外的字节，可用于以下目的之一：如果使用VIA挂锁，则＜ul＞＜li＞对齐</li><li>通过生成额外的循环密钥，简化了256位情况下的密钥扩展</li></ul>*/
}
mbedtls_aes_context;

#if defined(MBEDTLS_CIPHER_MODE_XTS)
/**
 * \简要AES XTS上下文类型定义。
 */
typedef struct mbedtls_aes_xts_context
{
    mbedtls_aes_context crypt; /*!< 用于AES块加密或解密的AES上下文。*/
    mbedtls_aes_context tweak; /*!< 用于调整计算的AES上下文。*/
} mbedtls_aes_xts_context;
#endif /* MBEDTLS_CIPHER_MODE_XTS */

#else  /* MBEDTLS_AES_ALT */
#include "aes_alt.h"
#endif /* MBEDTLS_AES_ALT */

/**
 * \brief此函数初始化指定的AES上下文。
 *
 *                 它必须是在使用上下文之前调用的第一个API。
 *
 * \param ctx要初始化的AES上下文。此值不能为空。
 */
void mbedtls_aes_init( mbedtls_aes_context *ctx );

/**
 * \brief此函数释放并清除指定的AES上下文。
 *
 * \param ctx要清除的AES上下文。如果该值为空，则此函数不执行任何操作。否则，上下文必须至少已初始化。
 */
void mbedtls_aes_free( mbedtls_aes_context *ctx );

#if defined(MBEDTLS_CIPHER_MODE_XTS)
/**
 * \brief此函数初始化指定的AES XTS上下文。
 *
 *                 它必须是在使用上下文之前调用的第一个API。
 *
 * \param ctx要初始化的AES XTS上下文。此值不能为空。
 */
void mbedtls_aes_xts_init( mbedtls_aes_xts_context *ctx );

/**
 * \brief此函数释放并清除指定的AESXTS上下文。
 *
 * \param ctx要清除的AES XTS上下文。如果该值为空，则此函数不执行任何操作。否则，上下文必须至少已初始化。
 */
void mbedtls_aes_xts_free( mbedtls_aes_xts_context *ctx );
#endif /* MBEDTLS_CIPHER_MODE_XTS */

/**
 * \brief此函数设置加密密钥。
 *
 * \param ctx密钥应绑定到的AES上下文。必须对其进行初始化。\param key加密密钥。这必须是大小为\p keybits位的可读缓冲区。\param keybits以位为单位传递的数据大小。有效选项为：＜ul＞＜li＞128位＜/li＞＜li＜192位＜/li>＜li＞256位＜/li＞＜/ul＞
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH。
 */
int mbedtls_aes_setkey_enc( mbedtls_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );

/**
 * \brief此函数设置解密密钥。
 *
 * \param ctx密钥应绑定到的AES上下文。必须对其进行初始化。\param key解密密钥。这必须是大小为\p keybits位的可读缓冲区。\param keybits传递的数据大小。有效选项为：＜ul＞＜li＞128位＜/li＞＜li＜192位＜/li>＜li＞256位＜/li＞＜/ul＞
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH。
 */
int mbedtls_aes_setkey_dec( mbedtls_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );

#if defined(MBEDTLS_CIPHER_MODE_XTS)
/**
 * \brief此函数为加密准备XTS上下文并设置加密密钥。
 *
 * \param ctx密钥应绑定到的AES XTS上下文。必须对其进行初始化。\param key加密密钥。它由XTS key1和XTS key2连接而成。这必须是一个大小为\p keybits位的可读缓冲区。\param keybits传递的\p密钥的大小（以位为单位）。有效选项为：＜ul＞＜li＞256位（key1和key2中的每一个都是128位密钥）＜/li＞＜li＜512位（key 1和key 2中的每个都是256位密钥）
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH。
 */
int mbedtls_aes_xts_setkey_enc( mbedtls_aes_xts_context *ctx,
                                const unsigned char *key,
                                unsigned int keybits );

/**
 * \brief此函数为解密准备XTS上下文并设置解密密钥。
 *
 * \param ctx密钥应绑定到的AES XTS上下文。必须对其进行初始化。\param key解密密钥。它由XTS key1和XTS key2连接而成。这必须是一个大小为\p keybits位的可读缓冲区。\param keybits传递的\p密钥的大小（以位为单位）。有效选项为：＜ul＞＜li＞256位（key1和key2中的每一个都是128位密钥）＜/li＞＜li＜512位（key 1和key 2中的每个都是256位密钥）
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH。
 */
int mbedtls_aes_xts_setkey_dec( mbedtls_aes_xts_context *ctx,
                                const unsigned char *key,
                                unsigned int keybits );
#endif /* MBEDTLS_CIPHER_MODE_XTS */

/**
 * \brief此函数执行AES单块加密或解密操作。
 *
 *                 它对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密或解密）中定义的操作。
 *
 *                 在第一次调用具有相同上下文的此API之前，必须调用mbedtls_aes_init（）和mbedtls_aes_setkey_enc（）或mbedtls_ees_setkkey_dec（）。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param mode AES操作：#MBEDTLS_AES_ENCRYPT或#MBEDTLS_AES_DES_DECRYPT。\param input保存输入数据的缓冲区。它必须可读，长度至少为\c 16字节。\param output将写入输出数据的缓冲区。它必须是可写的，长度至少为\c 16字节。

 * \成功时返回\c 0。
 */
int mbedtls_aes_crypt_ecb( mbedtls_aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \brief此函数对完整块执行AES-CBC加密或解密操作。
 *
 *         它对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密/解密）中定义的操作。
 *
 *         它可以根据需要调用多次，直到处理完所有输入数据。在第一次调用具有相同上下文的此API之前，必须调用mbedtls_aes_init（）和mbedtls_aes_setkey_enc（）或mbedtls_ees_setkkey_dec（）。
 *
 * \注意：此函数在完整块上运行，即输入大小必须是AES块大小\c 16字节的倍数。
 *
 * \注意：退出后，IV的内容将更新，以便您可以在下一个数据块上再次调用相同的函数，并获得与在一次调用中加密相同的结果。这允许“流式”使用。如果您需要保留IV的内容，您应该手动保存或使用密码模块。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param mode AES操作：#MBEDTLS_AES_ENCRYPT或#MBEDTLS_AES_DES_DECRYPT。\param length输入数据的长度（以字节为单位）。这必须是块大小的倍数（\c 16字节）。\param iv初始化向量（使用后更新）。它必须是一个16字节的可读写缓冲区。\param input保存输入数据的缓冲区。它必须是可读的，长度为字节。\param output保存输出数据的缓冲区。它必须是可写的，长度为字节。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_INPUT_LENGTH。
 */
int mbedtls_aes_crypt_cbc( mbedtls_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_XTS)
/**
 * \brief此函数对整个XTS数据单元执行AES-XTS加密或解密操作。
 *
 *             AES-XTS根据数据单元编号定义的块位置对块进行加密或解密。数据单元编号必须由\p data_unit提供。
 *
 *             NIST SP 800-38E将数据单元的最大大小限制为2^20 AES块。如果数据单位大于此值，则此函数返回#MBEDTLS_ERROR_AES_INVALID_INPUT_LENGTH。
 *
 * \param ctx用于AES XTS操作的AES XTS上下文。它必须初始化并绑定到密钥。\param mode AES操作：#MBEDTLS_AES_ENCRYPT或#MBEDTLS_AES_DES_DECRYPT。\param length数据单元的长度（以字节为单位）。这可以是16字节和2^24字节之间的任何长度（包括1和2^20块密码块）。\param data_unit数据单元的地址，以小端字节格式编码为16字节数组。对于磁盘加密，这通常是包含数据的块设备扇区的索引。\param input保存输入数据的缓冲区（它是一个完整的数据单元）。此函数从\p输入读取\p长度字节。\param output保存输出数据的缓冲区（它是一个完整的数据单元）。此函数将\p长度字节写入\p输出。
 *
 * \成功时返回\c 0。\如果长度小于AES块的大小（16字节）或长度大于2^20块（16 MiB），则返回#MBEDTLS_ERROR_AES_INVALID_INPUT_LENGTH。
 */
int mbedtls_aes_crypt_xts( mbedtls_aes_xts_context *ctx,
                           int mode,
                           size_t length,
                           const unsigned char data_unit[16],
                           const unsigned char *input,
                           unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_XTS */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
/**
 * \brief此函数执行AES-CFB128加密或解密操作。
 *
 *        它对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密或解密）中定义的操作。
 *
 *        对于CFB，您必须使用mbedtls_aes_setkey_enc（）设置上下文，无论您是执行加密还是解密操作，也就是说，无论\p mode参数如何。这是因为CFB模式使用相同的密钥调度进行加密和解密。
 *
 * \注意：退出后，IV的内容将更新，以便您可以在下一个数据块上再次调用相同的函数，并获得与在一次调用中加密相同的结果。这允许“流式”使用。如果您需要保留IV的内容，则必须手动保存或使用密码模块。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param mode AES操作：#MBEDTLS_AES_ENCRYPT或#MBEDTLS_AES_DES_DECRYPT。\param length输入数据的长度（以字节为单位）。\param iv_off iv中的偏移量（使用后更新）。它必须指向有效的\c size_t。\param iv初始化向量（使用后更新）。它必须是一个16字节的可读写缓冲区。\param input保存输入数据的缓冲区。它必须是可读的，长度为字节。\param output保存输出数据的缓冲区。它必须是可写的，长度为字节。
 *
 * \成功时返回\c 0。
 */
int mbedtls_aes_crypt_cfb128( mbedtls_aes_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief此函数执行AES-CFB8加密或解密操作。
 *
 *        它对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密/解密）中定义的操作。
 *
 *        由于CFB的性质，加密和解密操作必须使用相同的密钥调度。因此，必须对#mbedtls_aes_ENCRYPT和#mbedtls_aes_DES_DECRYPT使用使用mbedtls_aes_setkey_enc（）初始化的上下文。
 *
 * \注意：退出后，IV的内容将更新，以便您可以在下一个数据块上再次调用相同的函数，并获得与在一次调用中加密相同的结果。这允许“流式”使用。如果您需要保留IV的内容，您应该手动保存或使用密码模块。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param mode AES操作：#MBEDTLS_AES_ENCRYPT或#MBEDTLS_AES_DES_DECRYPT \param length输入数据的长度。\param iv初始化向量（使用后更新）。它必须是一个16字节的可读写缓冲区。\param input保存输入数据的缓冲区。它必须是可读的，长度为字节。\param output保存输出数据的缓冲区。它必须是可写的，长度为字节。
 *
 * \成功时返回\c 0。
 */
int mbedtls_aes_crypt_cfb8( mbedtls_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );
#endif /*MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_OFB)
/**
 * \brief此函数执行AES-OFB（输出反馈模式）加密或解密操作。
 *
 *              对于OFB，无论是执行加密还是解密操作，都必须使用mbedtls_aes_setkey_enc（）设置上下文。这是因为OFB模式使用相同的密钥调度进行加密和解密。
 *
 *              OFB操作对于加密或解密是相同的，因此不需要指定操作模式。
 *
 * \注意：退出后，iv（初始化向量）的内容将更新，以便您可以在下一个数据块上再次调用相同的函数，并获得与在一次调用中加密相同的结果。通过在第一次调用之前将iv_off初始化为0，并在调用之间保留其值，这允许“流式”使用。
 *
 *              对于非流媒体使用，应在每次调用时将iv初始化为唯一值，并在每次调用中将iv_off设置为0。
 *
 *              如果需要保留初始化向量的内容，则必须手动保存或使用密码模块。
 *
 * \警告对于OFB模式，每个加密操作的初始化向量必须是唯一的。重复使用初始化向量将危及安全性。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param length输入数据的长度。\param iv_off iv中的偏移量（使用后更新）。它必须指向有效的\c size_t。\param iv初始化向量（使用后更新）。它必须是一个16字节的可读写缓冲区。\param input保存输入数据的缓冲区。它必须是可读的，长度为字节。\param output保存输出数据的缓冲区。它必须是可写的，长度为字节。
 *
 * \成功时返回\c 0。
 */
int mbedtls_aes_crypt_ofb( mbedtls_aes_context *ctx,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );

#endif /* MBEDTLS_CIPHER_MODE_OFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
/**
 * \brief此函数执行AES-CTR加密或解密操作。
 *
 *             此函数对\p输入参数中定义的输入数据缓冲区执行\p模式参数（加密/解密）中定义的操作。
 *
 *             由于CTR的性质，加密和解密操作必须使用相同的密钥计划。因此，必须对#mbedtls_aes_ENCRYPT和#mbedtls_aes_DES_DECRYPT使用使用mbedtls_aes_setkey_enc（）初始化的上下文。
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
 *             注意，对于这两种策略，大小以块为单位，AES块为16字节。
 *
 * \警告返回时，\p stream_block包含敏感数据。其内容不得写入不安全的存储，一旦不再需要，应立即安全丢弃。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param length输入数据的长度。\param nc_off当前流块中的偏移量，用于在当前密码流中恢复。流开始处的偏移指针应为0。它必须指向有效的\c size_t。\param nonce_counter 128位的nonce和计数器。它必须是一个16字节的可读写缓冲区。\param stream_block用于恢复的已保存流块。这将被函数覆盖。它必须是一个16字节的可读写缓冲区。\param input保存输入数据的缓冲区。它必须是可读的，长度为字节。\param output保存输出数据的缓冲区。它必须是可写的，长度为字节。
 *
 * \成功时返回\c 0。
 */
int mbedtls_aes_crypt_ctr( mbedtls_aes_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CTR */

/**
 * \简短的内部AES块加密功能。这仅公开为允许使用\c MBEDTLS_AES_ENCRYPT_ALT覆盖它。
 *
 * \param ctx用于加密的AES上下文。\param input明文块。\param output输出（密文）块。
 *
 * \成功时返回\c 0。
 */
int mbedtls_internal_aes_encrypt( mbedtls_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] );

/**
 * \简短的内部AES块解密功能。这仅公开为允许使用参见\c MBEDTLS_AES_DES_DECRYPT_ALT覆盖它。
 *
 * \param ctx用于解密的AES上下文。\param input密文块。\param output输出（明文）块。
 *
 * \成功时返回\c 0。
 */
int mbedtls_internal_aes_decrypt( mbedtls_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \简短不推荐的内部AES块加密函数，没有返回值。
 *
 * \已弃用被mbedtls_internal_aes_encrypt（）取代
 *
 * \param ctx用于加密的AES上下文。\param输入明文块。\param输出输出（密文）块。
 */
MBEDTLS_DEPRECATED void mbedtls_aes_encrypt( mbedtls_aes_context *ctx,
                                             const unsigned char input[16],
                                             unsigned char output[16] );

/**
 * \简短不推荐的内部AES块解密函数，无返回值。
 *
 * \已弃用被mbedtls_internal_aes_decrypt（）取代
 *
 * \param ctx用于解密的AES上下文。\param输入密文块。\param输出输出（明文）块。
 */
MBEDTLS_DEPRECATED void mbedtls_aes_decrypt( mbedtls_aes_context *ctx,
                                             const unsigned char input[16],
                                             unsigned char output[16] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */


#if defined(MBEDTLS_SELF_TEST)
/**
 * \简短的检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_aes_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* aes小时*/

