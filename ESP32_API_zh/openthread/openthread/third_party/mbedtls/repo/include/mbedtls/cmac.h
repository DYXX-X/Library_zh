/**
 * \文件cmac.h
 *
 * \brief此文件包含CMAC定义和函数。
 *
 * 用于认证的基于密码的消息认证码（CMAC）模式在RFC-4493：AES-CMAC算法</em>中定义。
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

#ifndef MBEDTLS_CMAC_H
#define MBEDTLS_CMAC_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/cipher.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MBEDTLS_ERROR_CMAC_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_CMAC_HW_ACCEL_FAILED -0x007A  /**<CMAC硬件加速器失败。*/

#define MBEDTLS_AES_BLOCK_SIZE          16
#define MBEDTLS_DES3_BLOCK_SIZE         8

#if defined(MBEDTLS_AES_C)
#define MBEDTLS_CIPHER_BLKSIZE_MAX      16  /**<CMAC使用的最长块是AES。*/
#else
#define MBEDTLS_CIPHER_BLKSIZE_MAX      8   /**<CMAC使用的最长块是3DES。*/
#endif

#if !defined(MBEDTLS_CMAC_ALT)

/**
 * CMAC上下文结构。
 */
struct mbedtls_cmac_context_t
{
    /**CMAC算法的内部状态。*/
    unsigned char       state[MBEDTLS_CIPHER_BLKSIZE_MAX];

    /**未处理数据-未对齐块且仍在等待处理的数据，或最终块。*/
    unsigned char       unprocessed_block[MBEDTLS_CIPHER_BLKSIZE_MAX];

    /**等待处理的数据的长度。*/
    size_t              unprocessed_len;
};

#else  /* !MBEDTLS_CMAC_ALT */
#include "cmac_alt.h"
#endif /* !MBEDTLS_CMAC_ALT */

/**
 * \brief此函数设置CMAC密钥，并准备验证输入数据。必须使用初始化的密码上下文调用。
 *
 * \param ctx用于CMAC操作的密码上下文，初始化为以下类型之一：MBEDTLS_cipher_AES_128_ECB、MBEDTLS_cipher_AES _192_ECB、MBEDTLS_cipher_AES_256_ECB或MBEDTL_cipher_DES_EDE3_ECB。\param key CMAC键。\param keybits CMAC密钥的长度（以位为单位）。必须由密码支持。
 *
 * \成功时返回\c 0。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_cmac_starts( mbedtls_cipher_context_t *ctx,
                                const unsigned char *key, size_t keybits );

/**
 * \brief此函数将输入缓冲区输入到正在进行的CMAC计算中。
 *
 *                      它在mbedtls_cipher_cmac_starts（）或mbedtls_cipher_cmc_reset（）和mbedtls/cipher_cmac_finish（）之间调用。可以重复调用。
 *
 * \param ctx用于CMAC操作的密码上下文。\param input保存输入数据的缓冲区。\param ilen输入数据的长度。
 *
 * \成功时返回\c 0。\如果参数验证失败，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_cipher_cmac_update( mbedtls_cipher_context_t *ctx,
                                const unsigned char *input, size_t ilen );

/**
 * \brief此函数完成CMAC操作，并将结果写入输出缓冲区。
 *
 *                      它是在mbedtls_cipher_cmac_update（）之后调用的。后面可以是mbedtls_cipher_cmac_reset（）和mbedtls_cipher_cmc_update（）或mbedtlsc_ipher_free（）。
 *
 * \param ctx用于CMAC操作的密码上下文。\param output CMAC校验和结果的输出缓冲区。
 *
 * \成功时返回\c 0。\如果参数验证失败，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_cipher_cmac_finish( mbedtls_cipher_context_t *ctx,
                                unsigned char *output );

/**
 * \brief此函数使用与上一次CMAC操作相同的密钥准备另一条消息的身份验证。
 *
 *                      它在mbedtls_cipher_cmac_finish（）之后和mbedtls_cipher_cmc_update（）之前调用。
 *
 * \param ctx用于CMAC操作的密码上下文。
 *
 * \成功时返回\c 0。\如果参数验证失败，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_cipher_cmac_reset( mbedtls_cipher_context_t *ctx );

/**
 * \brief此函数使用提供的键计算输入缓冲区上的完整通用CMAC。
 *
 *                      该函数分配上下文、执行计算并释放上下文。
 *
 *                      CMAC结果计算为输出=通用CMAC（CMAC密钥，输入缓冲区）。
 *
 * \param cipher_info密码信息。\param key CMAC键。\param keylen CMAC密钥的长度（以位为单位）。\param input保存输入数据的缓冲区。\param ilen输入数据的长度。\param output通用CMAC结果的缓冲区。
 *
 * \成功时返回\c 0。\如果参数验证失败，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_cipher_cmac( const mbedtls_cipher_info_t *cipher_info,
                         const unsigned char *key, size_t keylen,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output );

#if defined(MBEDTLS_AES_C)
/**
 * \简要此函数实现AES-CMAC-PRF-128伪随机函数，如RFC-4615中定义的：互联网密钥交换协议（IKE）的高级加密标准基于密码的消息认证码伪随机函数-128（AES-CMAC-PRF-128）算法</em>
 *
 * \param key要使用的密钥。\param key_len密钥长度（字节）。\param input保存输入数据的缓冲区。\param in_len输入数据的长度（字节）。\param output保存生成的16字节伪随机输出的缓冲区。
 *
 * \成功时返回\c 0。
 */
int mbedtls_aes_cmac_prf_128( const unsigned char *key, size_t key_len,
                              const unsigned char *input, size_t in_len,
                              unsigned char output[16] );
#endif /* MBEDTLS_AES_C */

#if defined(MBEDTLS_SELF_TEST) && ( defined(MBEDTLS_AES_C) || defined(MBEDTLS_DES_C) )
/**
 * \简短的CMAC检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_cmac_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST && ( MBEDTLS_AES_C || MBEDTLS_DES_C ) */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CMAC_H */

