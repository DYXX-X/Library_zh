/**
 * \文件ccm.h
 *
 * \brief此文件为块密码的CCM认证加密模式提供API。
 *
 * CCM将计数器模式加密与CBC-MAC认证相结合，用于128位分组密码。
 *
 * CCM的输入包括以下元素：＜ul＞＜li＞Payload-经过认证和加密的数据</li><li>关联数据（Adata）-经过身份验证但未加密的数据，例如标头</li><li>Nonce-分配给有效负载和相关数据的唯一值。</li></ul>
 *
 * CCM的定义：http://csrc.nist.gov/publications/nistpubs/800-38C/SP800-38C_updated-July20_2007.pdfRFC 3610“带CBC-MAC（CCM）的计数器”
 *
 * 相关：RFC 5116“认证加密的接口和算法”
 *
 * CCM*的定义：IEEE 802.15.4-IEEE局域网和城域网标准整数表示是固定的最高有效位一阶，八位位组表示是最高有效位第一阶。这与RFC 3610一致。
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

#ifndef MBEDTLS_CCM_H
#define MBEDTLS_CCM_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/cipher.h"

/**函数的输入参数错误。*/
#define MBEDTLS_ERR_CCM_BAD_INPUT       -0x000D
/**身份验证解密失败。*/
#define MBEDTLS_ERR_CCM_AUTH_FAILED     -0x000F

/* MBEDTLS_ERROR_CCM_HW_ACCEL_FAILED已弃用，不应使用。*/
/**CCM硬件加速器失败。*/
#define MBEDTLS_ERR_CCM_HW_ACCEL_FAILED -0x0011

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_CCM_ALT)
// 定期实施
//

/**
 * \brief CCM context type definition（CCM上下文类型定义）。CCM上下文传递给调用的API。
 */
typedef struct mbedtls_ccm_context
{
    mbedtls_cipher_context_t cipher_ctx;    /*!< 使用的密码上下文。*/
}
mbedtls_ccm_context;

#else  /* MBEDTLS_CCM_ALT */
#include "ccm_alt.h"
#endif /* MBEDTLS_CCM_ALT */

/**
 * \brief此函数初始化指定的CCM上下文，使引用有效，并为mbedtls_CCM_setkey（）或mbedtls_CCM_free（）准备上下文。
 *
 * \param ctx要初始化的CCM上下文。此值不能为空。
 */
void mbedtls_ccm_init( mbedtls_ccm_context *ctx );

/**
 * \brief此函数初始化\p ctx参数中设置的CCM上下文并设置加密密钥。
 *
 * \param ctx要初始化的CCM上下文。这必须是已初始化的上下文。\param cipher要使用的128位分组密码。\param key加密密钥。此值不能为空。\param keybits以位为单位的密钥大小。这必须是密码可以接受的。
 *
 * \成功时返回\c 0。\失败时返回CCM或密码特定错误代码。
 */
int mbedtls_ccm_setkey( mbedtls_ccm_context *ctx,
                        mbedtls_cipher_id_t cipher,
                        const unsigned char *key,
                        unsigned int keybits );

/**
 * \brief此函数释放并清除指定的CCM上下文和基础密码子上下文。
 *
 * \param ctx要清除的CCM上下文。如果为空，则函数无效。否则，必须对其进行初始化。
 */
void mbedtls_ccm_free( mbedtls_ccm_context *ctx );

/**
 * \brief此函数使用CCM加密缓冲区。
 *
 * \注意：标记被写入一个单独的缓冲区。要将\p标记与\p输出连接起来，如<em>RFC-3610:Counter with CBC-MAC（CCM）</em>中所述，请使用\p标记=\p output+\p length，并确保输出缓冲区至少为\p length+\p tag_len宽。
 *
 * \param ctx用于加密的CCM上下文。这必须初始化并绑定到密钥。\param length输入数据的长度（以字节为单位）。\param iv初始化向量（nonce）。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len随机数的长度（以字节为单位）：7、8、9、10、11、12或13。消息长度字段的长度L为15-\piv_len。\param add附加数据字段。如果\p add_len大于零，则\p add必须是至少具有该长度的可读缓冲区。\param add_len附加数据的长度（字节）。这必须小于“2^16-2^8”。\param input保存输入数据的缓冲区。如果\p长度大于零，\p输入必须是至少该长度的可读缓冲区。\param output保存输出数据的缓冲区。如果\p长度大于零，则\p输出必须是至少具有该长度的可写缓冲区。\param tag保存身份验证字段的缓冲区。这必须是至少\p tag_len Bytes的可写缓冲区。\param tag_len要生成的身份验证字段的长度（字节）：4、6、8、10、12、14或16。
 *
 * \成功时返回\c 0。\失败时返回CCM或密码特定错误代码。
 */
int mbedtls_ccm_encrypt_and_tag( mbedtls_ccm_context *ctx, size_t length,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *add, size_t add_len,
                         const unsigned char *input, unsigned char *output,
                         unsigned char *tag, size_t tag_len );

/**
 * \brief此函数使用CCM*加密缓冲区。
 *
 * \注意：标记被写入一个单独的缓冲区。要将\p标记与\p输出连接起来，如<em>RFC-3610:Counter with CBC-MAC（CCM）</em>中所述，请使用\p标记=\p output+\p length，并确保输出缓冲区至少为\p length+\p tag_len宽。
 *
 * \注意：在可变标记长度上下文中使用此函数时，必须将标记长度编码为传递给此函数的\p iv。
 *
 * \param ctx用于加密的CCM上下文。这必须初始化并绑定到密钥。\param length输入数据的长度（以字节为单位）。\param iv初始化向量（nonce）。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len随机数的长度（以字节为单位）：7、8、9、10、11、12或13。消息长度字段的长度L为15-\piv_len。\param add附加数据字段。这必须是至少有\p add_len字节的可读缓冲区。\param add_len附加数据的长度（字节）。此值必须小于2^16-2^8。\param input保存输入数据的缓冲区。如果\p长度大于零，\p输入必须是至少该长度的可读缓冲区。\param output保存输出数据的缓冲区。如果\p长度大于零，则\p输出必须是至少具有该长度的可写缓冲区。\param tag保存身份验证字段的缓冲区。这必须是至少\p tag_len Bytes的可写缓冲区。\param tag_len要生成的身份验证字段的长度（字节）：0、4、6、8、10、12、14或16。
 *
 * \警告将\c 0作为\p tag_len传递意味着消息不再经过身份验证。
 *
 * \成功时返回\c 0。\失败时返回CCM或密码特定错误代码。
 */
int mbedtls_ccm_star_encrypt_and_tag( mbedtls_ccm_context *ctx, size_t length,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *add, size_t add_len,
                         const unsigned char *input, unsigned char *output,
                         unsigned char *tag, size_t tag_len );

/**
 * \brief此函数执行缓冲区的CCM认证解密。
 *
 * \param ctx用于解密的CCM上下文。这必须初始化并绑定到密钥。\param length输入数据的长度（以字节为单位）。\param iv初始化向量（nonce）。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len随机数的长度（以字节为单位）：7、8、9、10、11、12或13。消息长度字段的长度L为15-\piv_len。\param add附加数据字段。这必须是至少为\p add_len Bytes的可读缓冲区..\param add_ln以字节为单位的附加数据长度。此值必须小于2^16-2^8。\param input保存输入数据的缓冲区。如果\p长度大于零，\p输入必须是至少该长度的可读缓冲区。\param output保存输出数据的缓冲区。如果\p长度大于零，则\p输出必须是至少具有该长度的可写缓冲区。\param tag保存身份验证字段的缓冲区。这必须是至少有\p tag_len字节的可读缓冲区。\param tag_len要生成的身份验证字段的长度（字节）：4、6、8、10、12、14或16。
 *
 * \成功时返回\c 0。这表示消息是真实的。\如果标记不匹配，则返回#MBEDTLS_ERROR_CCM_AUTH_FAILED。\return计算失败时的密码特定错误代码。
 */
int mbedtls_ccm_auth_decrypt( mbedtls_ccm_context *ctx, size_t length,
                      const unsigned char *iv, size_t iv_len,
                      const unsigned char *add, size_t add_len,
                      const unsigned char *input, unsigned char *output,
                      const unsigned char *tag, size_t tag_len );

/**
 * \brief此函数执行缓冲区的CCM*认证解密。
 *
 * \注意：在可变标记长度上下文中使用此函数时，必须从\p iv解码标记长度，并将其作为\p tag_len传递给此函数。（\p标记需要相应调整。）
 *
 * \param ctx用于解密的CCM上下文。这必须初始化并绑定到密钥。\param length输入数据的长度（以字节为单位）。\param iv初始化向量（nonce）。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len随机数的长度（以字节为单位）：7、8、9、10、11、12或13。消息长度字段的长度L为15-\piv_len。\param add附加数据字段。这必须是一个至少有\p add_len字节的可读缓冲区。\param add_len附加数据的长度（字节）。此值必须小于2^16-2^8。\param input保存输入数据的缓冲区。如果\p长度大于零，\p输入必须是至少该长度的可读缓冲区。\param output保存输出数据的缓冲区。如果\p长度大于零，则\p输出必须是至少具有该长度的可写缓冲区。\param tag保存身份验证字段的缓冲区。这必须是至少有\p tag_len字节的可读缓冲区。\param tag_len身份验证字段的长度（以字节为单位）。0、4、6、8、10、12、14或16。
 *
 * \警告将\c 0作为\p tag_len传递意味着消息不再经过身份验证。
 *
 * \成功时返回\c 0。\如果标记不匹配，则返回#MBEDTLS_ERROR_CCM_AUTH_FAILED。\return计算失败时的密码特定错误代码。
 */
int mbedtls_ccm_star_auth_decrypt( mbedtls_ccm_context *ctx, size_t length,
                      const unsigned char *iv, size_t iv_len,
                      const unsigned char *add, size_t add_len,
                      const unsigned char *input, unsigned char *output,
                      const unsigned char *tag, size_t tag_len );

#if defined(MBEDTLS_SELF_TEST) && defined(MBEDTLS_AES_C)
/**
 * \简要CCM检查例程。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_ccm_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST && MBEDTLS_AES_C */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CCM_H */

