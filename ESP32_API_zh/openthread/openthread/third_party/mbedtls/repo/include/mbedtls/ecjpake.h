/**
 * \文件ecjpake.h
 *
 * \短椭圆曲线J-PAKE
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
#ifndef MBEDTLS_ECJPAKE_H
#define MBEDTLS_ECJPAKE_H

/*
 * J-PAKE是一种经过密码认证的密钥交换，它允许从（潜在的低熵）预先共享的口令中导出一个强共享密钥，并具有前向保密性和相互认证。https://en.wikipedia.org/wiki/Password_Authenticated_Key_Exchange_by_Juggling
 *
 * 本文件实现了J-PAKE的椭圆曲线变体，如Thread v1.0规范第7.4章所定义，可供线程组成员使用http://threadgroup.org/
 *
 * 由于J-PAKE算法本质上是对称的，所以我们的API也是对称的。每一方都需要以任何顺序向另一方发送其第一轮消息，然后以任何顺序发送其第二轮消息。有效负载以适合在TLS中使用的方式序列化，但也可以在TLS之外使用。
 */
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ecp.h"
#include "mbedtls/md.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 在EC J-PAKE交换中的作用
 */
typedef enum {
    MBEDTLS_ECJPAKE_CLIENT = 0,         /**<客户端*/
    MBEDTLS_ECJPAKE_SERVER,             /**<服务器*/
} mbedtls_ecjpake_role;

#if !defined(MBEDTLS_ECJPAKE_ALT)
/**
 * EC J-PAKE上下文结构。
 *
 * J-PAKE是一种对称协议，除了零知识证明中使用的标识符和线程规范定义的第二条消息（KeyExchange）的序列化之外。
 *
 * 为了从这种对称性中获益，我们选择了与Thread v1.0规范不同的命名转换。描述中以一对C：客户端名称，S：服务器名称来表示对应关系
 */
typedef struct mbedtls_ecjpake_context
{
    const mbedtls_md_info_t *md_info;   /**<要使用的哈希*/
    mbedtls_ecp_group grp;              /**<椭圆曲线*/
    mbedtls_ecjpake_role role;          /**<我们是客户端还是服务器？*/
    int point_format;                   /**<点导出格式*/

    mbedtls_ecp_point Xm1;              /**<我的公钥1 C:X1，S:X3*/
    mbedtls_ecp_point Xm2;              /**<我的公钥2 C:X2，S:X4*/
    mbedtls_ecp_point Xp1;              /**<对等公钥1 C:X3，S:X1*/
    mbedtls_ecp_point Xp2;              /**<对等公钥2 C:X4，S:X2*/
    mbedtls_ecp_point Xp;               /**<对等公钥C:Xs，S:Xc*/

    mbedtls_mpi xm1;                    /**<我的私钥1 C:x1，S:x3*/
    mbedtls_mpi xm2;                    /**<我的私钥2 C:x2，S:x4*/

    mbedtls_mpi s;                      /**<预共享密钥（密码短语）*/
} mbedtls_ecjpake_context;

#else  /* MBEDTLS_ECJPAKE_ALT */
#include "ecjpake_alt.h"
#endif /* MBEDTLS_ECJPAKE_ALT */

/**
 * \brief初始化ECJPAKE上下文。
 *
 * \param ctx要初始化的ECJPAKE上下文。此值不能为空。
 */
void mbedtls_ecjpake_init( mbedtls_ecjpake_context *ctx );

/**
 * \brief设置要使用的ECJPAKE上下文。
 *
 * \注意：目前，标准允许的哈希/曲线值只有#MBEDTLS_MD_SHA256/#MBEDLLS_EP_DP_SECP256R1。
 *
 * \param ctx要设置的ECJPAKE上下文。必须对其进行初始化。\param role调用者的角色。这必须是#MBEDTLS_ECJPAKE_CLIENT或#MBEDLLS_ECJPOKE_SERVER。\param hash要使用的哈希函数的标识符，例如#MBEDTLS_MD_SHA256。\param curve要使用的椭圆曲线的标识符，如#MBEDTLS_ECP_DP_SECP256R1。\paramsecret预共享的密钥（密码短语）。这必须是长度为\plen Bytes的可读缓冲区。它只需在本次通话期间有效。\param len预先共享的secret \p secret的长度。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecjpake_setup( mbedtls_ecjpake_context *ctx,
                           mbedtls_ecjpake_role role,
                           mbedtls_md_type_t hash,
                           mbedtls_ecp_group_id curve,
                           const unsigned char *secret,
                           size_t len );

/**
 * \brief检查ECJPAKE上下文是否可以使用。
 *
 * \param ctx要检查的ECJPAKE上下文。必须对其进行初始化。
 *
 * \如果上下文已准备好使用，则返回\c 0。\否则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。
 */
int mbedtls_ecjpake_check( const mbedtls_ecjpake_context *ctx );

/**
 * \brief生成并写入第一轮消息（TLS：Client/ServerHello扩展的内容，不包括扩展类型和长度字节）。
 *
 * \param ctx要使用的ECJPAKE上下文。必须对其进行初始化和设置。\param buf要将内容写入的缓冲区。这必须是长度为\p len Bytes的可写缓冲区。\param len \p buf的长度（以字节为单位）。\param olen存储写入缓冲区的字节总数的地址。此值不能为空。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng未使用上下文，则该值可能为空。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecjpake_write_round_one( mbedtls_ecjpake_context *ctx,
                            unsigned char *buf, size_t len, size_t *olen,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng );

/**
 * \brief读取并处理第一轮消息（TLS：Client/ServerHello扩展的内容，不包括扩展类型和长度字节）。
 *
 * \param ctx要使用的ECJPAKE上下文。必须对其进行初始化和设置。\param buf保存第一轮消息的缓冲区。这必须是长度为\plen Bytes的可读缓冲区。\param len \p buf的长度（以字节为单位）。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecjpake_read_round_one( mbedtls_ecjpake_context *ctx,
                                    const unsigned char *buf,
                                    size_t len );

/**
 * \brief生成并写入第二轮消息（TLS：Client/ServerKeyExchange的内容）。
 *
 * \param ctx要使用的ECJPAKE上下文。这必须进行初始化、设置，并且已经执行了第一轮。\param buf将舍入两个内容写入的缓冲区。这必须是长度为\p len Bytes的可写缓冲区。\param len \p buf的大小（以字节为单位）。\param olen存储写入缓冲区的字节总数的地址。此值不能为空。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng未使用上下文，则该值可能为空。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecjpake_write_round_two( mbedtls_ecjpake_context *ctx,
                            unsigned char *buf, size_t len, size_t *olen,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng );

/**
 * \brief读取并处理第二轮消息（TLS：Client/ServerKeyExchange的内容）。
 *
 * \param ctx要使用的ECJPAKE上下文。这必须进行初始化和设置，并且已经执行了第一轮。\param buf保存第二轮消息的缓冲区。这必须是长度为\plen Bytes的可读缓冲区。\param len \p buf的长度（以字节为单位）。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecjpake_read_round_two( mbedtls_ecjpake_context *ctx,
                                    const unsigned char *buf,
                                    size_t len );

/**
 * \brief派生共享密钥（TLS：Pre-Master secret）。
 *
 * \param ctx要使用的ECJPAKE上下文。必须初始化、设置并执行第一轮和第二轮。\param buf要将派生密钥写入的缓冲区。这必须是长度为\p len Bytes的可写缓冲区。\param len \p buf的长度（以字节为单位）。\param olen存储写入缓冲区的字节总数的地址。此值不能为空。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng未使用上下文，则该值可能为空。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecjpake_derive_secret( mbedtls_ecjpake_context *ctx,
                            unsigned char *buf, size_t len, size_t *olen,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng );

/**
 * \brief这将清除ECJPAKE上下文并释放任何嵌入的数据结构。
 *
 * \param ctx要释放的ECJPAKE上下文。这可能是空的，在这种情况下，此函数不执行任何操作。如果不是空，则必须指向初始化的ECJPAKE上下文。
 */
void mbedtls_ecjpake_free( mbedtls_ecjpake_context *ctx );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_ecjpake_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif


#endif /* ecjpake.h*/

