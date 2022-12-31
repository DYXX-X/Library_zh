/**
 * \文件gcm.h
 *
 * \这个文件包含GCM定义和函数。
 *
 * 128位分组密码的伽罗瓦/计数器模式（GCM）在<em>D中定义。McGrew，J.Viega，《伽罗瓦/计数器操作模式》（GCM），Natl。仪器支架。技术</em>
 *
 * 有关GCM的更多信息，请参见NIST SP 800-38D：分组密码操作模式建议：伽罗瓦/计数器模式（GCM）和GMAC</em>。
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

#ifndef MBEDTLS_GCM_H
#define MBEDTLS_GCM_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/cipher.h"

#include <stdint.h>

#define MBEDTLS_GCM_ENCRYPT     1
#define MBEDTLS_GCM_DECRYPT     0

/**身份验证解密失败。*/
#define MBEDTLS_ERR_GCM_AUTH_FAILED                       -0x0012

/* MBEDTLS_ERROR_GCM_HW_ACCEL_FAILED已弃用，不应使用。*/
/**GCM硬件加速器失败。*/
#define MBEDTLS_ERR_GCM_HW_ACCEL_FAILED                   -0x0013

/**函数的输入参数错误。*/
#define MBEDTLS_ERR_GCM_BAD_INPUT                         -0x0014

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_GCM_ALT)

/**
 * \GCM上下文结构简介。
 */
typedef struct mbedtls_gcm_context
{
    mbedtls_cipher_context_t cipher_ctx;  /*!< 使用的密码上下文。*/
    uint64_t HL[16];                      /*!< 预先计算的HTable低。*/
    uint64_t HH[16];                      /*!< 预先计算的HTable高。*/
    uint64_t len;                         /*!< 加密数据的总长度。*/
    uint64_t add_len;                     /*!< 附加数据的总长度。*/
    unsigned char base_ectr[16];          /*!< 标记的第一个ECTR。*/
    unsigned char y[16];                  /*!< Y工作值。*/
    unsigned char buf[16];                /*!< buf工作值。*/
    int mode;                             /*!< 要执行的操作：#MBEDTLS_GCM_ENCRYPT或#MBEDTLS _GCM_DECRYPT。*/
}
mbedtls_gcm_context;

#else  /* !MBEDTLS_GCM_ALT */
#include "gcm_alt.h"
#endif /* !MBEDTLS_GCM_ALT */

/**
 * \brief此函数初始化指定的GCM上下文，使引用有效，并为mbedtls_GCM_setkey（）或mbedtls_GCM_free（）准备上下文。
 *
 *                  该函数不将GCM上下文绑定到特定密码，也不设置密钥。为此，请使用mbedtls_gcm_setkey（）。
 *
 * \param ctx要初始化的GCM上下文。此值不能为空。
 */
void mbedtls_gcm_init( mbedtls_gcm_context *ctx );

/**
 * \brief此函数将GCM上下文与密码算法和密钥相关联。
 *
 * \param ctx GCM上下文。必须对其进行初始化。\param cipher要使用的128位分组密码。\param key加密密钥。这必须是至少有\p个keybit位的可读缓冲区。\param keybits以位为单位的密钥大小。有效选项为：＜ul＞＜li＞128位＜/li＞＜li＜192位＜/li>＜li＞256位＜/li＞＜/ul＞
 *
 * \成功时返回\c 0。\return失败时的密码特定错误代码。
 */
int mbedtls_gcm_setkey( mbedtls_gcm_context *ctx,
                        mbedtls_cipher_id_t cipher,
                        const unsigned char *key,
                        unsigned int keybits );

/**
 * \brief此函数执行缓冲区的GCM加密或解密。
 *
 * \注意：对于加密，输出缓冲区可以与输入缓冲区相同。对于解密，输出缓冲区不能与输入缓冲区相同。如果缓冲区重叠，则输出缓冲区必须落后于输入缓冲区至少8个字节。
 *
 * \警告当此函数执行解密时，它将输出身份验证标签，并且不会验证数据是否真实。您应该使用此函数仅执行加密。对于解密，请改用mbedtls_gcm_auth_decrypt（）。
 *
 * \param ctx用于加密或解密的GCM上下文。必须对其进行初始化。\param mode要执行的操作：
 *                  -#MBEDTLS_GCM_ENCRYPT以执行经过身份验证的加密。密文写入\p输出，身份验证标记写入\p标记。
 *                  -#MBEDTLS_GCM_DECRYPT以执行解密。明文写入\p输出，身份验证标记写入\p标记。请注意，不建议使用此模式，因为它不会验证数据的真实性。因此，应该使用mbedtls_gcm_auth_decrypt（），而不是在解密模式下调用此函数。\param length输入数据的长度，等于输出数据的长度。\param iv初始化向量。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len iv的长度。\param add保存附加数据的缓冲区。这必须至少是以字节为单位的大小。\param add_len附加数据的长度。\param input保存输入数据的缓冲区。如果\p长度大于零，则这必须是一个可读缓冲区，其大小至少为字节。\param output用于保存输出数据的缓冲区。如果\p长度大于零，则这必须是一个以字节为单位至少具有该大小的可写缓冲区。\param tag_len要生成的标记的长度。\param tag用于保存标记的缓冲区。这必须是至少\p tag_len Bytes的可写缓冲区。
 *
 * \如果加密或解密成功执行，则返回\c 0。注意，在#MBEDTLS_GCM_DECRYPT模式下，这并不表示数据是真实的。\如果长度或指针无效，则返回#MBEDTLS_error_GCM_BAD_INPUT；如果加密或解密失败，则返回特定于密码的错误代码。
 */
int mbedtls_gcm_crypt_and_tag( mbedtls_gcm_context *ctx,
                       int mode,
                       size_t length,
                       const unsigned char *iv,
                       size_t iv_len,
                       const unsigned char *add,
                       size_t add_len,
                       const unsigned char *input,
                       unsigned char *output,
                       size_t tag_len,
                       unsigned char *tag );

/**
 * \brief此函数执行缓冲区的GCM认证解密。
 *
 * \注意：对于解密，输出缓冲区不能与输入缓冲区相同。如果缓冲区重叠，则输出缓冲区必须落后于输入缓冲区至少8个字节。
 *
 * \param ctx GCM上下文。必须对其进行初始化。\param length要解密的密文的长度，也是解密的明文的长度。\param iv初始化向量。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len iv的长度。\param add保存附加数据的缓冲区。这必须至少是以字节为单位的大小。\param add_len附加数据的长度。\param tag保存要验证的标记的缓冲区。这必须是至少有\p tag_len字节的可读缓冲区。\param tag_len要验证的标记的长度。\param input保存密文的缓冲区。如果\p长度大于零，则这必须是一个至少具有该大小的可读缓冲区。\param output用于保存解密明文的缓冲区。如果\p长度大于零，则这必须是一个至少具有该大小的可写缓冲区。
 *
 * \如果成功并经过身份验证，则返回\c 0。\如果标记不匹配，则返回#MBEDTLS_ERROR_GCM_AUTH_FAILED。\如果长度或指针无效，则返回#MBEDTLS_error_GCM_BAD_INPUT；如果解密失败，则返回特定于密码的错误代码。
 */
int mbedtls_gcm_auth_decrypt( mbedtls_gcm_context *ctx,
                      size_t length,
                      const unsigned char *iv,
                      size_t iv_len,
                      const unsigned char *add,
                      size_t add_len,
                      const unsigned char *tag,
                      size_t tag_len,
                      const unsigned char *input,
                      unsigned char *output );

/**
 * \brief此函数启动GCM加密或解密操作。
 *
 * \param ctx GCM上下文。必须对其进行初始化。\param mode要执行的操作：#MBEDTLS_GCM_ENCRYPT或#MBEDTLS _GCM_DECRYPT。\param iv初始化向量。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len iv的长度。\param add保存附加数据的缓冲区，或者如果\p add_len为\c 0，则为空。\pram add_len附加数据的长度。如果\c 0，\p add可能为\c NULL。
 *
 * \成功时返回\c 0。
 */
int mbedtls_gcm_starts( mbedtls_gcm_context *ctx,
                int mode,
                const unsigned char *iv,
                size_t iv_len,
                const unsigned char *add,
                size_t add_len );

/**
 * \brief此函数将输入缓冲区送入正在进行的GCM加密或解密操作。
 *
 *    `该函数要求输入为16字节的倍数。只有在调用mbedtls_gcm_finish（）之前的最后一次调用才能小于16字节。
 *
 * \注意：对于解密，输出缓冲区不能与输入缓冲区相同。如果缓冲区重叠，则输出缓冲区必须落后于输入缓冲区至少8个字节。
 *
 * \param ctx GCM上下文。必须对其进行初始化。\param length输入数据的长度。这必须是16的倍数，除了在mbedtls_gcm_finish（）之前的最后一次调用中。\param input保存输入数据的缓冲区。如果\p长度大于零，则这必须是一个可读缓冲区，其大小至少为字节。\param output用于保存输出数据的缓冲区。如果\p长度大于零，则这必须是一个以字节为单位至少具有该大小的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_GCM_BAD_INPUT。
 */
int mbedtls_gcm_update( mbedtls_gcm_context *ctx,
                size_t length,
                const unsigned char *input,
                unsigned char *output );

/**
 * \brief此函数完成GCM操作并生成身份验证标签。
 *
 *                  它包装GCM流，并生成标记。标记的最大长度为16字节。
 *
 * \param ctx GCM上下文。必须对其进行初始化。\param tag用于保存标记的缓冲区。这必须是至少\p tag_len Bytes的可写缓冲区。\param tag_len要生成的标记的长度。这必须至少是四个。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_GCM_BAD_INPUT。
 */
int mbedtls_gcm_finish( mbedtls_gcm_context *ctx,
                unsigned char *tag,
                size_t tag_len );

/**
 * \brief此函数清除GCM上下文和底层密码子上下文。
 *
 * \param ctx要清除的GCM上下文。如果该值为空，则调用无效。否则，必须对其进行初始化。
 */
void mbedtls_gcm_free( mbedtls_gcm_context *ctx );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要介绍GCM检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_gcm_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif


#endif /* 总立方米小时*/

