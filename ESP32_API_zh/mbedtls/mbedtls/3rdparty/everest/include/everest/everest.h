/*
 *  珠峰项目代码接口
 *
 *  版权所有2016-2018 INRIA和Microsoft Corporation SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  此文件是Mbed TLS的一部分(https://tls.mbed.org).
 */

#ifndef MBEDTLS_EVEREST_H
#define MBEDTLS_EVEREST_H

#include "everest/x25519.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 定义导入的EC密钥的源。
 */
typedef enum
{
    MBEDTLS_EVEREST_ECDH_OURS,   /**<我们的钥匙。*/
    MBEDTLS_EVEREST_ECDH_THEIRS, /**<对等方的密钥。*/
} mbedtls_everest_ecdh_side;

typedef struct {
    mbedtls_x25519_context ctx;
} mbedtls_ecdh_context_everest;


/**
 * \brief此函数使用给定的信息设置ECDH上下文。
 *
 *                  应在mbedtls_ecdh_init（）之后但在mbedtls _ecdh_make_params（）之前调用此函数。在mbedtls_ecdh_read_params（）之前不需要调用此函数。
 *
 *                  这是TLS服务器用于ECDHE密码套件的第一个功能。
 *
 * \param ctx要设置的ECDH上下文。\param grp_id要为其设置上下文的组的组id。
 *
 * \成功时返回\c 0。
 */
int mbedtls_everest_setup( mbedtls_ecdh_context_everest *ctx, int grp_id );

/**
 * \brief此函数释放上下文。
 *
 * \param ctx要释放的上下文。
 */
void mbedtls_everest_free( mbedtls_ecdh_context_everest *ctx );

/**
 * \brief此函数生成公钥和TLS ServerKeyExchange负载。
 *
 *                  这是TLS服务器用于ECDHE密码套件的第二个功能。（在mbedtls_ecdh_setup（）之后调用。）
 *
 * \注意：此函数假定ctx上下文的ECP组（grp）已正确设置，例如，使用mbedtls_ECP_group_load（）。
 *
 * \见ecp.h
 *
 * \param ctx ECDH上下文。\param olen写入的字符数。\param buf目标缓冲区。\param blen目标缓冲区的长度。\param f_rng rng函数。\param p_rng rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_everest_make_params( mbedtls_ecdh_context_everest *ctx, size_t *olen,
                                 unsigned char *buf, size_t blen,
                                 int( *f_rng )( void *, unsigned char *, size_t ),
                                 void *p_rng );

/**
 * \brief此函数解析并处理TLS ServerKeyExhange负载。
 *
 *                  这是TLS客户端用于ECDHE密码套件的第一个函数。
 *
 * \见ecp.h
 *
 * \param ctx ECDH上下文。\param buf指向输入缓冲区起点的指针。\param end缓冲区结束后一个字节的地址。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_everest_read_params( mbedtls_ecdh_context_everest *ctx,
                                 const unsigned char **buf, const unsigned char *end );

/**
 * \brief此函数解析并处理TLS ServerKeyExhange负载。
 *
 *                  这是TLS客户端用于ECDHE密码套件的第一个函数。
 *
 * \见ecp.h
 *
 * \param ctx ECDH上下文。\param buf指向输入缓冲区起点的指针。\param end缓冲区结束后一个字节的地址。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_everest_read_params( mbedtls_ecdh_context_everest *ctx,
                                 const unsigned char **buf, const unsigned char *end );

/**
 * \brief此函数从EC密钥设置ECDH上下文。
 *
 *                  客户端和服务器使用它来代替静态ECDH的ServerKeyEchange，并从证书的EC密钥信息中导入ECDH参数。
 *
 * \见ecp.h
 *
 * \param ctx要设置的ECDH上下文。\param key要使用的EC密钥。\param-side定义密钥的源：1：我们的密钥，或0：对等方的密钥。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_everest_get_params( mbedtls_ecdh_context_everest *ctx, const mbedtls_ecp_keypair *key,
                                mbedtls_everest_ecdh_side side );

/**
 * \brief此函数生成公钥和TLS ClientKeyExchange负载。
 *
 *                  这是TLS客户端用于ECDH（E）密码套件的第二个功能。
 *
 * \见ecp.h
 *
 * \param ctx ECDH上下文。\param olen写入的字节数。\param buf目标缓冲区。\param blen目标缓冲区的大小。\param f_rng rng函数。\param p_rng rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_everest_make_public( mbedtls_ecdh_context_everest *ctx, size_t *olen,
                                 unsigned char *buf, size_t blen,
                                 int( *f_rng )( void *, unsigned char *, size_t ),
                                 void *p_rng );

/**
 * \brief此函数解析并处理TLS ClientKeyExchange负载。
 *
 *              这是TLS服务器用于ECDH（E）密码套件的第三个功能。（它在mbedtls_ecdh_setup（）和mbedtls-ecdh_make_params（）之后调用。）
 *
 * \见ecp.h
 *
 * \param ctx ECDH上下文。\param buf输入缓冲区的开始。\param blen输入缓冲区的长度。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_everest_read_public( mbedtls_ecdh_context_everest *ctx,
                                 const unsigned char *buf, size_t blen );

/**
 * \brief此函数派生并导出共享秘密。
 *
 *                  这是TLS客户端和服务器使用的最后一个函数。
 *
 * \注意：如果\pf_rng不为NULL，则它用于实施针对侧信道攻击的对策。有关详细信息，请参阅mbedtls_ecp_mul（）。
 *
 * \见ecp.h
 *
 * \param ctx ECDH上下文。\param olen写入的字节数。\param buf目标缓冲区。\param blen目标缓冲区的长度。\param f_rng rng函数。\param p_rng rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_everest_calc_secret( mbedtls_ecdh_context_everest *ctx, size_t *olen,
                                 unsigned char *buf, size_t blen,
                                 int( *f_rng )( void *, unsigned char *, size_t ),
                                 void *p_rng );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_EVEREST_H */

