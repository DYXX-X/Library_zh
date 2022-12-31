/**
 * \文件ssl_ticket.h
 *
 * \简短的TLS服务器票证回调实现
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
#ifndef MBEDTLS_SSL_TICKET_H
#define MBEDTLS_SSL_TICKET_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

/*
 * 会话票证回调的这种实现包括密钥管理，在定义MBEDTLS_HAVE_TIME时，周期性地旋转密钥以保持前向保密。
 */

#include "mbedtls/ssl.h"
#include "mbedtls/cipher.h"

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \会话票证保护的简要信息
 */
typedef struct mbedtls_ssl_ticket_key
{
    unsigned char name[4];          /*!< 随机密钥标识符*/
    uint32_t generation_time;       /*!< 密钥生成时间戳（秒）*/
    mbedtls_cipher_context_t ctx;   /*!< auth-enc/解密上下文*/
}
mbedtls_ssl_ticket_key;

/**
 * \会话票证处理功能的简要上下文
 */
typedef struct mbedtls_ssl_ticket_context
{
    mbedtls_ssl_ticket_key keys[2]; /*!< 票证保护键*/
    unsigned char active;           /*!< 当前活动密钥的索引*/

    uint32_t ticket_lifetime;       /*!< 票的有效期（秒）*/

    /**获取（伪）随机数的回调*/
    int  (*f_rng)(void *, unsigned char *, size_t);
    void *p_rng;                    /*!< RNG功能的上下文*/

#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t mutex;
#endif
}
mbedtls_ssl_ticket_context;

/**
 * \brief初始化票证上下文。（只需为mbedtls_ssl_ticket_setup（）或mbedtls_ssl_tickot_free（）做好准备。）
 *
 * \param ctx要初始化的上下文
 */
void mbedtls_ssl_ticket_init( mbedtls_ssl_ticket_context *ctx );

/**
 * \brief准备实际使用的上下文
 *
 * \param ctx要设置的上下文\param f_rng rng回调函数\param p_rng rng回调上下文\param密码用于票证保护的AEAD密码。建议值：MBEDTLS_CIPHER_AES_256_GCM。\param lifetime门票寿命（秒）建议值：86400（一天）。
 *
 * \注意：强烈建议选择至少与支持的最强密码套件一样强的密码。通常这意味着256位密钥。
 *
 * \注：钥匙的寿命是车票寿命的两倍。建议选择一个合理的寿命，以免否定转发保密的好处。
 *
 * \如果成功，则返回0，或返回特定的MBEDTLS_error_XXX错误代码
 */
int mbedtls_ssl_ticket_setup( mbedtls_ssl_ticket_context *ctx,
    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
    mbedtls_cipher_type_t cipher,
    uint32_t lifetime );

/**
 * \票证写入回调的简要实现
 *
 * \注意：有关说明，请参见\c mbedtls_ssl_ticket_write_t
 */
mbedtls_ssl_ticket_write_t mbedtls_ssl_ticket_write;

/**
 * \票证解析回调的简要实现
 *
 * \注意：有关说明，请参见\c mbedtls_ssl_ticket_parse_t
 */
mbedtls_ssl_ticket_parse_t mbedtls_ssl_ticket_parse;

/**
 * \brief释放上下文的内容并将其归零。
 *
 * \param ctx要清理的上下文
 */
void mbedtls_ssl_ticket_free( mbedtls_ssl_ticket_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* ssl_ticket.h*/

