/**
 * \psa/crypto_config文件。h\简要PSA加密配置选项（一组定义）
 *
 */
#if defined(MBEDTLS_PSA_CRYPTO_CONFIG)
/**
 * 当在配置中启用#MBEDTLS_PSA_CRYPTO_CONFIG时。h、 此文件确定通过PSA Cryptography API（\c PSA_xxx（）函数）启用了哪些加密机制。
 *
 * 要启用加密机制，请取消注释相应的\c PSA_ANT_xxx预处理器符号的定义。要禁用加密机制，请注释掉相应的\c PSA_ANT_xxx预处理器符号的定义。加密机制的名称对应于psa/crypto_values中定义的值。h、 前缀为\c PSA_CANT_而不是\c PSA_。
 *
 * 注意，许多加密机制涉及两个符号：一个用于密钥类型（\c PSA_ANT_key_type_xxx），一个用于算法（\c PSA _WANT_ALG_xxx）。具有附加参数的机制可能涉及附加符号。
 */
#else
/**
 * 当配置中禁用了\c MBEDTLS_PSA_CRYPTO_CONFIG时。h、 不使用此文件，并且只有当通过mbedtls_xxx API支持加密机制时，PSA API才支持加密机制。
 */
#endif
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_CONFIG_H
#define PSA_CRYPTO_CONFIG_H

/*
 * Mbed TLS中的PSA API尚不支持CBC-MAC。
 */
//#定义PSA_ANT_ALG_CBC_M 1
#define PSA_WANT_ALG_CBC_NO_PADDING             1
#define PSA_WANT_ALG_CBC_PKCS7                  1
#define PSA_WANT_ALG_CCM                        1
#define PSA_WANT_ALG_CMAC                       1
#define PSA_WANT_ALG_CFB                        1
#define PSA_WANT_ALG_CHACHA20_POLY1305          1
#define PSA_WANT_ALG_CMAC                       1
#define PSA_WANT_ALG_CTR                        1
#define PSA_WANT_ALG_DETERMINISTIC_ECDSA        1
#define PSA_WANT_ALG_ECB_NO_PADDING             1
#define PSA_WANT_ALG_ECDH                       1
#define PSA_WANT_ALG_ECDSA                      1
#define PSA_WANT_ALG_GCM                        1
#define PSA_WANT_ALG_HKDF                       1
#define PSA_WANT_ALG_HMAC                       1
#define PSA_WANT_ALG_MD2                        1
#define PSA_WANT_ALG_MD4                        1
#define PSA_WANT_ALG_MD5                        1
#define PSA_WANT_ALG_OFB                        1
#define PSA_WANT_ALG_RIPEMD160                  1
#define PSA_WANT_ALG_RSA_OAEP                   1
#define PSA_WANT_ALG_RSA_PKCS1V15_CRYPT         1
#define PSA_WANT_ALG_RSA_PKCS1V15_SIGN          1
#define PSA_WANT_ALG_RSA_PSS                    1
#define PSA_WANT_ALG_SHA_1                      1
#define PSA_WANT_ALG_SHA_224                    1
#define PSA_WANT_ALG_SHA_256                    1
#define PSA_WANT_ALG_SHA_384                    1
#define PSA_WANT_ALG_SHA_512                    1
#define PSA_WANT_ALG_STREAM_CIPHER              1
#define PSA_WANT_ALG_TLS12_PRF                  1
#define PSA_WANT_ALG_TLS12_PSK_TO_MS            1
#define PSA_WANT_ALG_XTS                        1

#define PSA_WANT_ECC_BRAINPOOL_P_R1_256         1
#define PSA_WANT_ECC_BRAINPOOL_P_R1_384         1
#define PSA_WANT_ECC_BRAINPOOL_P_R1_512         1
#define PSA_WANT_ECC_MONTGOMERY_255             1
/*
 * Curve448尚未通过Mbed TLS中的PSA API得到支持(https://github.com/ARMmbed/mbedtls/issues/4249). 因此，默认情况下不要启用它。
 */
//#定义PSA_ANT_ECC_MONTGOMERY_448 1
#define PSA_WANT_ECC_SECP_K1_192                1
/*
 * SECP224K1通过Mbed TLS中的PSA API存在漏洞(https://github.com/ARMmbed/mbedtls/issues/3541). 因此，默认情况下不要启用它。
 */
//#定义PSA_ANT_ECC_SECP_K1_224 1
#define PSA_WANT_ECC_SECP_K1_256                1
#define PSA_WANT_ECC_SECP_R1_192                1
#define PSA_WANT_ECC_SECP_R1_224                1
#define PSA_WANT_ECC_SECP_R1_256                1
#define PSA_WANT_ECC_SECP_R1_384                1
#define PSA_WANT_ECC_SECP_R1_521                1

#define PSA_WANT_KEY_TYPE_DERIVE                1
#define PSA_WANT_KEY_TYPE_HMAC                  1
#define PSA_WANT_KEY_TYPE_AES                   1
#define PSA_WANT_KEY_TYPE_ARC4                  1
#define PSA_WANT_KEY_TYPE_ARIA                  1
#define PSA_WANT_KEY_TYPE_CAMELLIA              1
#define PSA_WANT_KEY_TYPE_CHACHA20              1
#define PSA_WANT_KEY_TYPE_DES                   1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR          1
#define PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY        1
#define PSA_WANT_KEY_TYPE_RAW_DATA              1
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR          1
#define PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY        1

#endif /* PSA_CRYPTO_CONFIG_H */

