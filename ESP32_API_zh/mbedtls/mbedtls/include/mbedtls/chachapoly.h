/**
 * \文件chachapoly.h
 *
 * \简要本文件包含AEAD-ChaCha20-Poly1305定义和函数。
 *
 *          ChaCha20-Poly1305是一种用于关联数据认证加密（AEAD）的算法，可用于加密和认证数据。它基于丹尼尔·伯恩斯坦的ChaCha20和Poly1305，并在RFC 7539中进行了标准化。
 *
 * \作者丹尼尔·金<damaki.gh@gmail.com>
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

#ifndef MBEDTLS_CHACHAPOLY_H
#define MBEDTLS_CHACHAPOLY_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

/* 用于共享错误代码*/
#include "mbedtls/poly1305.h"

/**当前状态下不允许请求的操作。*/
#define MBEDTLS_ERR_CHACHAPOLY_BAD_STATE            -0x0054
/**身份验证解密失败：数据不可信。*/
#define MBEDTLS_ERR_CHACHAPOLY_AUTH_FAILED          -0x0056

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MBEDTLS_CHACHAPOLY_ENCRYPT,     /**<执行加密的模式值。*/
    MBEDTLS_CHACHAPOLY_DECRYPT      /**<执行解密的模式值。*/
}
mbedtls_chachapoly_mode_t;

#if !defined(MBEDTLS_CHACHAPOLY_ALT)

#include "mbedtls/chacha20.h"

typedef struct mbedtls_chachapoly_context
{
    mbedtls_chacha20_context chacha20_ctx;  /**<ChaCha20上下文。*/
    mbedtls_poly1305_context poly1305_ctx;  /**<Poly1305上下文。*/
    uint64_t aad_len;                       /**<附加认证数据的长度（字节）。*/
    uint64_t ciphertext_len;                /**<密文的长度（字节）。*/
    int state;                              /**<上下文的当前状态。*/
    mbedtls_chachapoly_mode_t mode;         /**<密码模式（加密或解密）。*/
}
mbedtls_chachapoly_context;

#else /* !MBEDTLS_CHACHAPOLY_ALT */
#include "chachapoly_alt.h"
#endif /* !MBEDTLS_CHACHAPOLY_ALT */

/**
 * \brief此函数初始化指定的ChaCha20-Poly1305上下文。
 *
 *                  它必须是在使用上下文之前调用的第一个API。在执行任何操作之前，必须先调用\c mbedtls_chachapoly_setkey（），在完成该上下文的所有操作后，调用\c mbdtls_chapoly_free（）。
 *
 *                  为了一次加密或解密全部消息，您应该对每条消息调用\c mbedtls_chachapoly_crypt_and_tag（）或\c mbedt ls_chachaboly_auth_decrypt（）。
 *
 *                  为了分段加密消息，对于每条消息，您应该调用\c mbedtls_chachapoly_starts（），然后调用0个或多个\c mbedt ls_chachaboly_update_aad（），再调用0个以上\c mbeds ls_chachatoly_update（），最后调用一个\c embedtls_chapoly_finish（）。
 *
 * \警告不鼓励使用分段API解密！如果可能，请始终使用\c mbedtls_chachapoly_auth_decrypt（）！
 *
 *                  但是，如果由于数据太大而无法放入内存，则需要：
 *
 *                  -如上所述调用\c mbedtls_chachapoly_starts（）和（如果需要）\c mbedt ls_chachaboly_update_aad（），
 *                  -多次调用\c mbedtls_chachapoly_update（），并确保其输出（明文）不会以任何其他方式使用，
 *                  -调用\c mbedtls_chachapoly_finish（）计算身份验证标记，并在恒定时间内将其与接收到的带有密文的标记进行比较。
 *
 *                  如果标记不相等，则必须立即放弃\c mbedtls_chachapoly_update（）的所有先前输出，否则现在可以安全地使用明文。
 *
 * \param ctx要初始化的ChachaPoly上下文。不能为\c NULL。
 */
void mbedtls_chachapoly_init( mbedtls_chachapoly_context *ctx );

/**
 * \brief此函数释放并清除指定的ChaCha20-Poly1305上下文。
 *
 * \param ctx要清除的ChachaPoly上下文。这可能是空的，在这种情况下，此函数是no-op。
 */
void mbedtls_chachapoly_free( mbedtls_chachapoly_context *ctx );

/**
 * \brief此函数设置ChaCha20-Poly1305对称加密密钥。
 *
 * \param ctx密钥应绑定到的ChaCha20-Poly1305上下文。必须对其进行初始化。\param key \c 256位（\c 32字节）密钥。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_chachapoly_setkey( mbedtls_chachapoly_context *ctx,
                               const unsigned char key[32] );

/**
 * \brief此函数启动ChaCha20-Poly1305加密或解密操作。
 *
 * \警告您决不能将同一个nonce与同一个key一起使用两次。这将使使用相同的随机数和密钥加密的消息的任何保密性和真实性保证失效。
 *
 * \注意：如果上下文仅用于AAD（没有要加密或解密的数据），则\p模式可以设置为任何值。
 *
 * \警告不鼓励使用分段API解密，请参阅\c mbedtls_chachapoly_init（）上的警告。
 *
 * \param ctx ChaCha20-Poly1305上下文。这必须初始化并绑定到密钥。\param nonce用于消息的nonce/IV。这必须是长度为\c 12字节的可编解码器缓冲区。\param mode要执行的操作：#MBEDTLS_CHACHAPOLY_ENCRYPT或#MBEDLLS_CHACHA波利Y_DECRYPT（不鼓励，请参阅警告）。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_chachapoly_starts( mbedtls_chachapoly_context *ctx,
                               const unsigned char nonce[12],
                               mbedtls_chachapoly_mode_t mode );

/**
 * \brief此功能将要验证的附加数据馈送到正在进行的ChaCha20-Poly1305操作中。
 *
 *                  附加认证数据（AAD），也称为关联数据（AD），仅经过认证，但未加密，也未包含在加密输出中。它通常与密文分开传输或由各方在本地计算。
 *
 * \注意：此函数在数据加密/解密之前调用。一、 e.调用此函数以在调用\c mbedtls_chachapoly_update（）之前处理AAD。
 *
 *                  您可以多次调用此函数来处理任意数量的AAD。如果未使用AAD，则允许调用此函数0次。
 *
 *                  如果数据已由\c mbedtls_chachapoly_update（）处理，或者上下文已完成，则不能再调用此函数。
 *
 * \警告不鼓励使用分段API解密，请参阅\c mbedtls_chachapoly_init（）上的警告。
 *
 * \param ctx ChaCha20-Poly1305上下文。这必须初始化并绑定到密钥。\param aad_len aad的字节长度。长度没有限制。\param aad包含aad的缓冲区。如果“aad_len==0”，则此指针可以为空。
 *
 * \成功时返回\c 0。\如果ctx或aad为空，则返回#MBEDTLS_ERROR_POLY1305_BAD_INPUT_DATA。\如果操作尚未启动或已完成，或者AAD已完成，则返回#MBEDTLS_ERROR_CHACHAPOLY_BAD_STATE。
 */
int mbedtls_chachapoly_update_aad( mbedtls_chachapoly_context *ctx,
                                   const unsigned char *aad,
                                   size_t aad_len );

/**
 * \因此，该函数将要加密或解密的数据馈送到正在进行的ChaCha20-Poly1305操作中。
 *
 *                  方向（加密或解密）取决于调用\c mbedtls_chachapoly_starts（）时给定的模式。
 *
 *                  您可以多次调用此函数来处理任意数量的数据。如果没有要加密或解密的数据，则允许调用此函数0次。
 *
 * \警告不鼓励使用分段API解密，请参阅\c mbedtls_chachapoly_init（）上的警告。
 *
 * \param ctx要使用的ChaCha20-Poly1305上下文。必须对其进行初始化。\param len要加密或解密的数据的长度（以字节为单位）。\param input包含要加密或解密的数据的缓冲区。如果“len==0”，则此指针可以为空。\param output写入加密或解密数据的缓冲区。这必须能够容纳\plen字节。如果“len==0”，则此指针可以为空。
 *
 * \成功时返回\c 0。\如果操作尚未启动或已完成，则返回#MBEDTLS_ERROR_CHACHAPOLY_BAD_STATE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_chachapoly_update( mbedtls_chachapoly_context *ctx,
                               size_t len,
                               const unsigned char *input,
                               unsigned char *output );

/**
 * \brief此函数完成ChaCha20-Poly1305操作并生成MAC（认证标签）。
 *
 * \param ctx要使用的ChaCha20-Poly1305上下文。必须对其进行初始化。\param mac写入128位（16字节）mac的缓冲区。
 *
 * \警告不鼓励使用分段API解密，请参阅\c mbedtls_chachapoly_init（）上的警告。
 *
 * \成功时返回\c 0。\如果操作尚未启动或已完成，则返回#MBEDTLS_ERROR_CHACHAPOLY_BAD_STATE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_chachapoly_finish( mbedtls_chachapoly_context *ctx,
                               unsigned char mac[16] );

/**
 * \brief此函数使用先前设置的密钥执行完整的ChaCha20-Poly1305认证加密。
 *
 * \注意：在使用此函数之前，必须使用\cmbedtls_chachapoly_setkey（）设置密钥。
 *
 * \警告您决不能将同一个nonce与同一个key一起使用两次。这将使使用相同的随机数和密钥加密的消息的任何保密性和真实性保证失效。
 *
 * \param ctx要使用的ChaCha20-Poly1305上下文（保存密钥）。必须对其进行初始化。\param length要加密或解密的数据的长度（以字节为单位）。\param nonce要使用的96位（12字节）nonce/IV。\param aad包含附加认证数据（aad）的缓冲区。如果“aad_len==0”，则此指针可以为空。\param aad_len要处理的aad数据的长度（字节）。\param input包含要加密或解密的数据的缓冲区。如果“ilen==0”，则此指针可以为空。\param output写入加密或解密数据的缓冲区。如果“ilen==0”，则此指针可以为空。\param tag将计算出的128位（16字节）MAC写入的缓冲区。此值不能为空。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_chachapoly_encrypt_and_tag( mbedtls_chachapoly_context *ctx,
                                        size_t length,
                                        const unsigned char nonce[12],
                                        const unsigned char *aad,
                                        size_t aad_len,
                                        const unsigned char *input,
                                        unsigned char *output,
                                        unsigned char tag[16] );

/**
 * \brief此函数使用先前设置的密钥执行完整的ChaCha20-Poly1305认证解密。
 *
 * \注意：在使用此函数之前，必须使用\cmbedtls_chachapoly_setkey（）设置密钥。
 *
 * \param ctx要使用的ChaCha20-Poly1305上下文（保存密钥）。\param length要解密的数据的长度（以字节为单位）。\param nonce要使用的\c 96位（\c 12字节）nonce/IV。\param aad包含附加认证数据（aad）的缓冲区。如果“aad_len==0”，则此指针可以为空。\param aad_len要处理的aad数据的长度（字节）。\param tag保存身份验证标记的缓冲区。这必须是长度为\c 16字节的可读缓冲区。\param input包含要解密的数据的缓冲区。如果“ilen==0”，则此指针可以为空。\param output将解密数据写入的缓冲区。如果“ilen==0”，则此指针可以为空。
 *
 * \成功时返回\c 0。\如果数据不真实，则返回#MBEDTLS_ERROR_CHACHAPOLY_AUTH_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_chachapoly_auth_decrypt( mbedtls_chachapoly_context *ctx,
                                     size_t length,
                                     const unsigned char nonce[12],
                                     const unsigned char *aad,
                                     size_t aad_len,
                                     const unsigned char tag[16],
                                     const unsigned char *input,
                                     unsigned char *output );

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要介绍ChaCha20-Poly1305检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_chachapoly_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CHACHAPOLY_H */

