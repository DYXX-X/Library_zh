/**
 * \文件nist_kw.h
 *
 * \该文件提供了NIST SP 800-38F中定义的密钥包装（KW）和带填充的密钥包装的API。https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-38F.pdf
 *
 *        根据<em>NIST SP 800-38F：分组密码操作模式建议：密钥包装方法</em>，密钥包装指定了一种确定性认证加密操作模式。其目的是保护加密密钥。
 *
 *        它的等价物是用于KW的RFC 3394和用于KWP的RFC 5649。https://tools.ietf.org/html/rfc3394 https://tools.ietf.org/html/rfc5649
 *
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

#ifndef MBEDTLS_NIST_KW_H
#define MBEDTLS_NIST_KW_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/cipher.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MBEDTLS_KW_MODE_KW = 0,
    MBEDTLS_KW_MODE_KWP = 1
} mbedtls_nist_kw_mode_t;

#if !defined(MBEDTLS_NIST_KW_ALT)
// 定期实施
//

/**
 * \brief键包装上下文类型定义。密钥包装上下文传递给调用的API。
 *
 * \注意：在未来的库版本中，此类型的定义可能会更改。不要在这方面做任何假设！
 */
typedef struct {
    mbedtls_cipher_context_t cipher_ctx;    /*!< 使用的密码上下文。*/
} mbedtls_nist_kw_context;

#else  /* MBEDTLS_NIST_密钥包装_ALT*/
#include "nist_kw_alt.h"
#endif /* MBEDTLS_NIST_KW_ALT */

/**
 * \brief此函数初始化指定的密钥包装上下文以使引用有效，并为mbedtls_nist_kw_setkey（）或mbedtls_nist_kw_free（）准备上下文。
 *
 * \param ctx要初始化的密钥包装上下文。
 *
 */
void mbedtls_nist_kw_init( mbedtls_nist_kw_context *ctx );

/**
 * \brief此函数初始化\p ctx参数中设置的密钥包装上下文，并设置加密密钥。
 *
 * \param ctx密钥包装上下文。\param cipher要使用的128位分组密码。仅支持AES。\param key密钥加密密钥（KEK）。\param keybits以位为单位的KEK大小。这必须是密码可以接受的。\param is_wrap指定上下文中的操作是包装还是展开
 *
 * \成功时返回\c 0。\对于任何无效输入，返回\c MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\return \c MBEDTLS_ERROR_CIPHER_FEATURE_NAVAILABLE用于不支持的128位块密码。\在基础密码失败时返回密码特定的错误代码。
 */
int mbedtls_nist_kw_setkey( mbedtls_nist_kw_context *ctx,
                            mbedtls_cipher_id_t cipher,
                            const unsigned char *key,
                            unsigned int keybits,
                            const int is_wrap );

/**
 * \brief此函数释放并清除指定的密钥包装上下文和底层密码子上下文。
 *
 * \param ctx要清除的密钥包装上下文。
 */
void mbedtls_nist_kw_free( mbedtls_nist_kw_context *ctx );

/**
 * \brief此函数使用密钥包装对缓冲区进行加密。
 *
 * \param ctx用于加密的密钥包装上下文。\param mode要使用的密钥包装模式（MBEDTLS_KW_mode_KW或MBEDTLS_KW_mode_SKWP）\param input保存输入数据的缓冲区。\param in_len输入数据的长度（字节）。输入使用称为半块的8字节单位<ul><li>对于KW模式：8字节的倍数，介于16和2^57-8之间</li><li>对于KWP模式：介于1和2^32-1之间的任何长度</li></ul>\param[out]output保存输出数据的缓冲区<ul><li>对于KW模式：必须至少比\pin_len大8个字节</li><li>对于KWP模式：KWP必须至少大8字节，四舍五入到8字节的倍数（最多15字节）</li></ul>\param[out]out_len写入输出缓冲区的字节数。\c 0失败。\param[in]out_size输出缓冲区的容量。
 *
 * \成功时返回\c 0。\对于无效的输入长度，返回\c MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\在基础密码失败时返回密码特定的错误代码。
 */
int mbedtls_nist_kw_wrap( mbedtls_nist_kw_context *ctx, mbedtls_nist_kw_mode_t mode,
                          const unsigned char *input, size_t in_len,
                          unsigned char *output, size_t* out_len, size_t out_size );

/**
 * \brief此函数使用密钥包装对缓冲区进行解密。
 *
 * \param ctx用于解密的密钥包装上下文。\param mode要使用的密钥包装模式（MBEDTLS_KW_mode_KW或MBEDTLS_KW_mode_SKWP）\param input保存输入数据的缓冲区。\param in_len输入数据的长度（字节）。输入使用称为半块的8字节单位。输入必须是半块的倍数<ul><li>对于KW模式：8字节的倍数，介于24和2^57之间</li><li>对于KWP模式：介于16和2^32之间的8字节的倍数。</li></ul>\param[out]output保存输出数据的缓冲区。输出缓冲区的最小长度比\pin_len短8字节。\param[out]out_len写入输出缓冲区的字节数。\c 0失败。对于KWP模式，长度可能比\pin_len短15个字节，具体取决于向数据添加了多少填充。\param[in]out_size输出缓冲区的容量。
 *
 * \成功时返回\c 0。\对于无效的输入长度，返回\c MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\return \c MBEDTLS_ERROR_CIPHER_AUTH_FAILED，表示密文验证失败。\在基础密码失败时返回密码特定的错误代码。
 */
int mbedtls_nist_kw_unwrap( mbedtls_nist_kw_context *ctx, mbedtls_nist_kw_mode_t mode,
                            const unsigned char *input, size_t in_len,
                            unsigned char *output, size_t* out_len, size_t out_size);


#if defined(MBEDTLS_SELF_TEST) && defined(MBEDTLS_AES_C)
/**
 * \简要介绍关键包装检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_nist_kw_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST && MBEDTLS_AES_C */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_NIST_KW_H */

