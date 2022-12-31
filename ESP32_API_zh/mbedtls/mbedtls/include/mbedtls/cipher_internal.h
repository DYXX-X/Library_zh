/**
 * \文件cipher_internal.h
 *
 * \简短的密码包装。
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
#ifndef MBEDTLS_CIPHER_WRAP_H
#define MBEDTLS_CIPHER_WRAP_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/cipher.h"

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#endif /* MBEDTLS_USE_PSA_CRYPTO */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 基本密码信息。非模式特定函数和值。
 */
struct mbedtls_cipher_base_t
{
    /**基本密码类型（例如MBEDTLS_Cipher_ID_AES）*/
    mbedtls_cipher_id_t cipher;

    /**使用ECB加密*/
    int (*ecb_func)( void *ctx, mbedtls_operation_t mode,
                     const unsigned char *input, unsigned char *output );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
    /**使用CBC加密*/
    int (*cbc_func)( void *ctx, mbedtls_operation_t mode, size_t length,
                     unsigned char *iv, const unsigned char *input,
                     unsigned char *output );
#endif

#if defined(MBEDTLS_CIPHER_MODE_CFB)
    /**使用CFB加密（全长）*/
    int (*cfb_func)( void *ctx, mbedtls_operation_t mode, size_t length, size_t *iv_off,
                     unsigned char *iv, const unsigned char *input,
                     unsigned char *output );
#endif

#if defined(MBEDTLS_CIPHER_MODE_OFB)
    /**使用OFB加密（全长）*/
    int (*ofb_func)( void *ctx, size_t length, size_t *iv_off,
                     unsigned char *iv,
                     const unsigned char *input,
                     unsigned char *output );
#endif

#if defined(MBEDTLS_CIPHER_MODE_CTR)
    /**使用CTR加密*/
    int (*ctr_func)( void *ctx, size_t length, size_t *nc_off,
                     unsigned char *nonce_counter, unsigned char *stream_block,
                     const unsigned char *input, unsigned char *output );
#endif

#if defined(MBEDTLS_CIPHER_MODE_XTS)
    /**使用XTS加密或解密。*/
    int (*xts_func)( void *ctx, mbedtls_operation_t mode, size_t length,
                     const unsigned char data_unit[16],
                     const unsigned char *input, unsigned char *output );
#endif

#if defined(MBEDTLS_CIPHER_MODE_STREAM)
    /**使用STREAM加密*/
    int (*stream_func)( void *ctx, size_t length,
                        const unsigned char *input, unsigned char *output );
#endif

    /**为加密目的设置密钥*/
    int (*setkey_enc_func)( void *ctx, const unsigned char *key,
                            unsigned int key_bitlen );

    /**为解密目的设置密钥*/
    int (*setkey_dec_func)( void *ctx, const unsigned char *key,
                            unsigned int key_bitlen);

    /**分配新上下文*/
    void * (*ctx_alloc_func)( void );

    /**释放给定上下文*/
    void (*ctx_free_func)( void *ctx );

};

typedef struct
{
    mbedtls_cipher_type_t type;
    const mbedtls_cipher_info_t *info;
} mbedtls_cipher_definition_t;

#if defined(MBEDTLS_USE_PSA_CRYPTO)
typedef enum
{
    MBEDTLS_CIPHER_PSA_KEY_UNSET = 0,
    MBEDTLS_CIPHER_PSA_KEY_OWNED, /* 用于基于PSA的密码上下文*/
                                  /* 使用内部进口的原关键材料*/
                                  /* 作为易失性密钥，因此需要*/
                                  /* 当上下文为*/
                                  /* 释放。*/
    MBEDTLS_CIPHER_PSA_KEY_NOT_OWNED, /* 用于基于PSA的密码上下文*/
                                      /* 使用由*/
                                      /* 用户，因此不会*/
                                      /* 释放上下文时销毁。*/
} mbedtls_cipher_psa_key_ownership;

typedef struct
{
    psa_algorithm_t alg;
    psa_key_id_t slot;
    mbedtls_cipher_psa_key_ownership slot_state;
} mbedtls_cipher_context_psa;
#endif /* MBEDTLS_USE_PSA_CRYPTO */

extern const mbedtls_cipher_definition_t mbedtls_cipher_definitions[];

extern int mbedtls_cipher_supported[];

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CIPHER_WRAP_H */

