/**
 * \文件pkcs11.h
 *
 * \PKCS#11库libpkcs11助手的brief Wrapper
 *
 * \作者Adrian de Jong<dejong@fox-it.com>
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
#ifndef MBEDTLS_PKCS11_H
#define MBEDTLS_PKCS11_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PKCS11_C)

#include "mbedtls/x509_crt.h"

#include <pkcs11-helper-1.0/pkcs11h-certificate.h>

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_DEPRECATED_REMOVED)

/**
 * PKCS#11私钥的上下文。
 */
typedef struct mbedtls_pkcs11_context
{
        pkcs11h_certificate_t pkcs11h_cert;
        int len;
} mbedtls_pkcs11_context;

#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif

/**
 * 初始化mbedtls_pkcs11_text。（只是使内存引用有效。）
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 */
MBEDTLS_DEPRECATED void mbedtls_pkcs11_init( mbedtls_pkcs11_context *ctx );

/**
 * 根据给定的PKCS11帮助者证书填写mbed TLS证书。
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param cert X.509证书以填充\param pkcs11h_cert PKCS#11帮助者证书
 *
 * \成功时返回0。
 */
MBEDTLS_DEPRECATED int mbedtls_pkcs11_x509_cert_bind( mbedtls_x509_crt *cert,
                                        pkcs11h_certificate_t pkcs11h_cert );

/**
 * 设置存储给定证书的mbedtls_pkcs11_text。请注意，mbedtls_pkcs11_text将接管证书的控制权，并在完成后释放证书。
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param priv_key要填充的私钥结构。\param pkcs11_cert PKCS#11帮助者证书
 *
 * \成功时返回0
 */
MBEDTLS_DEPRECATED int mbedtls_pkcs11_priv_key_bind(
                                        mbedtls_pkcs11_context *priv_key,
                                        pkcs11h_certificate_t pkcs11_cert );

/**
 * 释放给定私钥上下文的内容。请注意，结构本身没有被释放。
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param priv_key要清理的私钥结构
 */
MBEDTLS_DEPRECATED void mbedtls_pkcs11_priv_key_free(
                                            mbedtls_pkcs11_context *priv_key );

/**
 * \brief执行RSA私钥解密，然后删除消息填充
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param ctx PKCS#11上下文\param模式必须为MBEDTLS_RSA_PRIVATE，以与RSA兼容。c的签名\param保存加密数据的输入缓冲区\param将保存明文的输出缓冲区将包含明文长度\param output_max_len输出缓冲区的最大长度
 *
 * \如果成功，则返回0，或返回MBEDTLS_error_RSA_XXX错误代码
 *
 * \注意：输出缓冲区必须与ctx->N的大小一样大（例如，如果使用RSA-1024，则为128字节），否则会引发错误。
 */
MBEDTLS_DEPRECATED int mbedtls_pkcs11_decrypt( mbedtls_pkcs11_context *ctx,
                                               int mode, size_t *olen,
                                               const unsigned char *input,
                                               unsigned char *output,
                                               size_t output_max_len );

/**
 * \brief使用专用RSA签署消息摘要
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param ctx PKCS#11上下文\param模式必须为MBEDTLS_RSA_PRIVATE，以与RSA兼容。c的签名\param md_alg a MBEDTLS_md_XXX（使用MBEDTLS_md_NONE对原始数据进行签名）\param hashlen消息摘要长度（仅适用于MBEDTLS_md_NONE）\pram保存消息摘要的哈希缓冲区\param将保存密文的sig缓冲区
 *
 * \如果签名操作成功，则返回0，或者返回MBEDTLS_error_RSA_XXX错误代码
 *
 * \注意“sig”缓冲区必须与ctx->N的大小一样大（例如，如果使用RSA-1024，则为128字节）。
 */
MBEDTLS_DEPRECATED int mbedtls_pkcs11_sign( mbedtls_pkcs11_context *ctx,
                                            int mode,
                                            mbedtls_md_type_t md_alg,
                                            unsigned int hashlen,
                                            const unsigned char *hash,
                                            unsigned char *sig );

/**
 * PKCS#11函数的SSL/TLS包装器
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 */
MBEDTLS_DEPRECATED static inline int mbedtls_ssl_pkcs11_decrypt( void *ctx,
                            int mode, size_t *olen,
                            const unsigned char *input, unsigned char *output,
                            size_t output_max_len )
{
    return mbedtls_pkcs11_decrypt( (mbedtls_pkcs11_context *) ctx, mode, olen, input, output,
                           output_max_len );
}

/**
 * \brief此函数使用RSA对消息摘要进行签名。
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param ctx PKCS#11上下文。\param f_rng rng函数。此参数未使用。\param p_rng rng上下文。此参数未使用。\param mode要运行的操作。为了与RSA兼容，必须将其设置为MBEDTLS_RSA_PRIVATE。c的签名。\param md_alg消息摘要算法。必须将其中一个MBEDTLS_MD_XXX传递给此函数，并且MBEDTLS_MD_NONE可用于对原始数据进行签名。\param hashlen消息摘要长度（仅适用于MBEDTLS_MD_NONE）。\param hash保存消息摘要的缓冲区。\param sig将保存密文的缓冲区。
 *
 * \如果签名操作成功，则返回\c 0。\失败时返回非零错误代码。
 *
 * \注意\p sig缓冲区必须与<code>ctx->N</code>的大小一样大。例如，如果使用RSA-1024，则为128字节。
 */
MBEDTLS_DEPRECATED static inline int mbedtls_ssl_pkcs11_sign( void *ctx,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                    int mode, mbedtls_md_type_t md_alg, unsigned int hashlen,
                    const unsigned char *hash, unsigned char *sig )
{
    ((void) f_rng);
    ((void) p_rng);
    return mbedtls_pkcs11_sign( (mbedtls_pkcs11_context *) ctx, mode, md_alg,
                        hashlen, hash, sig );
}

/**
 * 此函数获取私钥的长度。
 *
 * \已弃用此函数已弃用，将在库的未来版本中删除。
 *
 * \param ctx PKCS#11上下文。
 *
 * \return私钥的长度。
 */
MBEDTLS_DEPRECATED static inline size_t mbedtls_ssl_pkcs11_key_len( void *ctx )
{
    return ( (mbedtls_pkcs11_context *) ctx )->len;
}

#undef MBEDTLS_DEPRECATED

#endif /* MBEDTLS_DEPRECATED_REMOVED */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_PKCS11_C */

#endif /* MBEDTLS_PKCS11_H */

