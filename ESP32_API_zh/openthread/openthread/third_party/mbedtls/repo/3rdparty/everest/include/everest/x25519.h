/*
 *  具有曲线优化实现多路复用的ECDH
 *
 *  版权所有2016-2018 INRIA和Microsoft Corporation SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  此文件是mbed TLS的一部分(https://tls.mbed.org)
 */

#ifndef MBEDTLS_X25519_H
#define MBEDTLS_X25519_H

#ifdef __cplusplus
extern "C" {
#endif

#define MBEDTLS_ECP_TLS_CURVE25519 0x1d
#define MBEDTLS_X25519_KEY_SIZE_BYTES 32

/**
 * 定义导入的EC密钥的源。
 */
typedef enum
{
    MBEDTLS_X25519_ECDH_OURS,   /**<我们的钥匙。*/
    MBEDTLS_X25519_ECDH_THEIRS, /**<对等方的密钥。*/
} mbedtls_x25519_ecdh_side;

/**
 * \brief x25519上下文结构。
 */
typedef struct
{
  unsigned char our_secret[MBEDTLS_X25519_KEY_SIZE_BYTES];
  unsigned char peer_point[MBEDTLS_X25519_KEY_SIZE_BYTES];
} mbedtls_x25519_context;

/**
 * \brief此函数初始化x25519上下文。
 *
 * \param ctx要初始化的x25519上下文。
 */
void mbedtls_x25519_init( mbedtls_x25519_context *ctx );

/**
 * \brief此函数释放上下文。
 *
 * \param ctx要释放的上下文。
 */
void mbedtls_x25519_free( mbedtls_x25519_context *ctx );

/**
 * \brief此函数生成公钥和TLS ServerKeyExchange负载。
 *
 *                  这是TLS服务器为x25519使用的第一个功能。
 *
 * \param ctx x25519上下文。\param olen写入的字符数。\param buf目标缓冲区。\param blen目标缓冲区的长度。\param f_rng rng函数。\param p_rng rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_x25519_make_params( mbedtls_x25519_context *ctx, size_t *olen,
                        unsigned char *buf, size_t blen,
                        int( *f_rng )(void *, unsigned char *, size_t),
                        void *p_rng );

/**
 * \brief此函数解析并处理TLS ServerKeyExchange负载。
 *
 * \param ctx x25519上下文。\param buf指向输入缓冲区起点的指针。\param end缓冲区结束后一个字节的地址。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_x25519_read_params( mbedtls_x25519_context *ctx,
                        const unsigned char **buf, const unsigned char *end );

/**
 * \brief此函数从EC密钥设置x25519上下文。
 *
 *                  客户端和服务器使用它来代替静态ECDH的ServerKeyEchange，并从证书的EC密钥信息中导入ECDH参数。
 *
 * \见ecp.h
 *
 * \param ctx要设置的x25519上下文。\param key要使用的EC密钥。\param-side定义密钥的源：1：我们的密钥，或0：对等方的密钥。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_x25519_get_params( mbedtls_x25519_context *ctx, const mbedtls_ecp_keypair *key,
                               mbedtls_x25519_ecdh_side side );

/**
 * \brief此函数派生并导出共享秘密。
 *
 *                  这是TLS客户端和服务器使用的最后一个函数。
 *
 * \param ctx x25519上下文。\param olen写入的字节数。\param buf目标缓冲区。\param blen目标缓冲区的长度。\param f_rng rng函数。\param p_rng rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_x25519_calc_secret( mbedtls_x25519_context *ctx, size_t *olen,
                        unsigned char *buf, size_t blen,
                        int( *f_rng )(void *, unsigned char *, size_t),
                        void *p_rng );

/**
 * \brief此函数生成公钥和TLS ClientKeyExchange负载。
 *
 *                  这是TLS客户端用于x25519的第二个函数。
 *
 * \见ecp.h
 *
 * \param ctx x25519上下文。\param olen写入的字节数。\param buf目标缓冲区。\param blen目标缓冲区的大小。\param f_rng rng函数。\param p_rng rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_x25519_make_public( mbedtls_x25519_context *ctx, size_t *olen,
                        unsigned char *buf, size_t blen,
                        int( *f_rng )(void *, unsigned char *, size_t),
                        void *p_rng );

/**
 * \brief此函数解析并处理TLS ClientKeyExchange负载。
 *
 *              这是TLS服务器为x25519使用的第二个功能。
 *
 * \见ecp.h
 *
 * \param ctx x25519上下文。\param buf输入缓冲区的开始。\param blen输入缓冲区的长度。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_x25519_read_public( mbedtls_x25519_context *ctx,
                        const unsigned char *buf, size_t blen );

#ifdef __cplusplus
}
#endif

#endif /* x25519.小时*/

