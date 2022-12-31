/**
 * \文件ecdh.h
 *
 * \brief此文件包含ECDH定义和函数。
 *
 * 椭圆曲线Diffie-Hellman（ECDH）协议是一种匿名密钥协议，允许双方在不安全的信道上建立共享密钥。每一方必须有一个椭圆曲线公钥-私钥对。
 *
 * 有关更多信息，请参见NIST SP 800-56A第2版：使用离散对数密码的成对密钥建立方案建议</em>。
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

#ifndef MBEDTLS_ECDH_H
#define MBEDTLS_ECDH_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ecp.h"

#if defined(MBEDTLS_ECDH_VARIANT_EVEREST_ENABLED)
#undef MBEDTLS_ECDH_LEGACY_CONTEXT
#include "everest/everest.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 定义导入的EC密钥的源。
 */
typedef enum
{
    MBEDTLS_ECDH_OURS,   /**<我们的钥匙。*/
    MBEDTLS_ECDH_THEIRS, /**<对等方的密钥。*/
} mbedtls_ecdh_side;

#if !defined(MBEDTLS_ECDH_LEGACY_CONTEXT)
/**
 * 定义使用的ECDH实现。
 *
 * 该库的后续版本可能会添加新的变体，因此用户不应对此进行任何假设。
 */
typedef enum
{
    MBEDTLS_ECDH_VARIANT_NONE = 0,   /*!< 未定义实现。*/
    MBEDTLS_ECDH_VARIANT_MBEDTLS_2_0,/*!< 默认的Mbed TLS实现*/
#if defined(MBEDTLS_ECDH_VARIANT_EVEREST_ENABLED)
    MBEDTLS_ECDH_VARIANT_EVEREST     /*!< 珠峰实施*/
#endif
} mbedtls_ecdh_variant;

/**
 * 默认ECDH实现使用的上下文。
 *
 * 以后的版本可能会更改此上下文的结构，因此用户不应对mbedtls_ecdh_context_mbed的结构进行任何假设。
 */
typedef struct mbedtls_ecdh_context_mbed
{
    mbedtls_ecp_group grp;   /*!< 使用的椭圆曲线。*/
    mbedtls_mpi d;           /*!< 私钥。*/
    mbedtls_ecp_point Q;     /*!< 公钥。*/
    mbedtls_ecp_point Qp;    /*!< 对等方公钥的值。*/
    mbedtls_mpi z;           /*!< 共享的秘密。*/
#if defined(MBEDTLS_ECP_RESTARTABLE)
    mbedtls_ecp_restart_ctx rs; /*!< EC计算的重新启动上下文。*/
#endif
} mbedtls_ecdh_context_mbed;
#endif

/**
 * \警告：不支持在同一ECDSA上下文上同时执行多个操作；这种类型的对象不应在多个线程之间共享。\简要ECDH上下文结构。
 */
typedef struct mbedtls_ecdh_context
{
#if defined(MBEDTLS_ECDH_LEGACY_CONTEXT)
    mbedtls_ecp_group grp;   /*!< 使用的椭圆曲线。*/
    mbedtls_mpi d;           /*!< 私钥。*/
    mbedtls_ecp_point Q;     /*!< 公钥。*/
    mbedtls_ecp_point Qp;    /*!< 对等方公钥的值。*/
    mbedtls_mpi z;           /*!< 共享的秘密。*/
    int point_format;        /*!< TLS消息中的点导出格式。*/
    mbedtls_ecp_point Vi;    /*!< 致盲值。*/
    mbedtls_ecp_point Vf;    /*!< 未装订值。*/
    mbedtls_mpi _d;          /*!< 上一个\p d。*/
#if defined(MBEDTLS_ECP_RESTARTABLE)
    int restart_enabled;        /*!< 可重新启动模式的标志。*/
    mbedtls_ecp_restart_ctx rs; /*!< EC计算的重新启动上下文。*/
#endif /* MBEDTLS_ECP_RESTARTABLE */
#else
    uint8_t point_format;       /*!< RFC 4492中定义的TLS消息中的点导出格式。*/
    mbedtls_ecp_group_id grp_id;/*!< 使用的椭圆曲线。*/
    mbedtls_ecdh_variant var;   /*!< 使用的ECDH实施/结构。*/
    union
    {
        mbedtls_ecdh_context_mbed   mbed_ecdh;
#if defined(MBEDTLS_ECDH_VARIANT_EVEREST_ENABLED)
        mbedtls_ecdh_context_everest everest_ecdh;
#endif
    } ctx;                      /*!< 具体实施环境。使用的上下文由\c var字段指定。*/
#if defined(MBEDTLS_ECP_RESTARTABLE)
    uint8_t restart_enabled;    /*!< 可重新启动模式的标志。如果设置了此标志，则不支持可重启模式的替代实现的函数必须返回MBEDTLS_error_PLATFORM_FEATURE_UNSUPPORTED错误。*/
#endif /* MBEDTLS_ECP_RESTARTABLE */
#endif /* MBEDTLS_ECDH_LEGACY_CONTEXT */
}
mbedtls_ecdh_context;

/**
 * \brief检查给定组是否可用于ECDH。
 *
 * \param gid要检查的ECP组ID。
 *
 * \如果可以使用组，则返回\c 1，否则返回\c 0
 */
int mbedtls_ecdh_can_do( mbedtls_ecp_group_id gid );

/**
 * \brief此函数在椭圆曲线上生成ECDH密钥对。
 *
 *                  该函数执行ECDH密钥交换期间实现的两个核心计算中的第一个。第二个核心计算由mbedtls_ecdh_compute_shared（）执行。
 *
 * \见ecp.h
 *
 * \param grp要使用的ECP组。必须初始化并加载域参数，例如通过mbedtls_ecp_load（）或mbedtls-ecp_tls_read_group（）。\param d目标MPI（私钥）。必须对其进行初始化。\param Q目标点（公钥）。必须对其进行初始化。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为空。
 *
 * \成功时返回\c 0。\失败时返回另一个\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecdh_gen_public( mbedtls_ecp_group *grp, mbedtls_mpi *d, mbedtls_ecp_point *Q,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng );

/**
 * \brief此函数计算共享密钥。
 *
 *                  该函数执行ECDH密钥交换期间实现的两个核心计算中的第二个。第一个核心计算由mbedtls_ecdh_gen_public（）执行。
 *
 * \见ecp.h
 *
 * \注意：如果\pf_rng不为NULL，则它用于实施针对侧信道攻击的对策。有关详细信息，请参阅mbedtls_ecp_mul（）。
 *
 * \param grp要使用的ECP组。必须初始化并加载域参数，例如通过mbedtls_ecp_load（）或mbedtls-ecp_tls_read_group（）。\param z目标MPI（共享密钥）。必须对其进行初始化。\param Q来自另一方的公钥。必须对其进行初始化。\param d我们的秘密指数（私钥）。必须对其进行初始化。\param f_rng rng函数。如果不需要在ECP计算期间对中间结果进行随机化（不鼓励），则该值可能为NULL。有关详细信息，请参阅mbedtls_ecp_mul（）的文档。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文参数，则该值可能为空。
 *
 * \成功时返回\c 0。\失败时返回另一个\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecdh_compute_shared( mbedtls_ecp_group *grp, mbedtls_mpi *z,
                         const mbedtls_ecp_point *Q, const mbedtls_mpi *d,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng );

/**
 * \brief此函数初始化ECDH上下文。
 *
 * \param ctx要初始化的ECDH上下文。此值不能为空。
 */
void mbedtls_ecdh_init( mbedtls_ecdh_context *ctx );

/**
 * \brief此函数使用给定的信息设置ECDH上下文。
 *
 *                  应在mbedtls_ecdh_init（）之后但在mbedtls _ecdh_make_params（）之前调用此函数。在mbedtls_ecdh_read_params（）之前不需要调用此函数。
 *
 *                  这是TLS服务器用于ECDHE密码套件的第一个功能。
 *
 * \param ctx要设置的ECDH上下文。必须对其进行初始化。\param grp_id要为其设置上下文的组的组id。
 *
 * \成功时返回\c 0。
 */
int mbedtls_ecdh_setup( mbedtls_ecdh_context *ctx,
                        mbedtls_ecp_group_id grp_id );

/**
 * \brief此函数释放上下文。
 *
 * \param ctx要释放的上下文。这可能是空的，在这种情况下，此函数不执行任何操作。如果不是空，则必须指向初始化的ECDH上下文。
 */
void mbedtls_ecdh_free( mbedtls_ecdh_context *ctx );

/**
 * \brief此函数生成EC密钥对，并以TLS ServerKeyExchange握手消息中使用的格式导出。
 *
 *                  这是TLS服务器用于ECDHE密码套件的第二个功能。（在mbedtls_ecdh_setup（）之后调用。）
 *
 * \见ecp.h
 *
 * \param ctx要使用的ECDH上下文。这必须初始化并绑定到组，例如通过mbedtls_ecdh_setup（）。\param olen存储写入字节数的地址。\param buf目标缓冲区。这必须是长度为\n blen Bytes的可写缓冲区。\param blen目标缓冲区的长度（字节）。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为空。
 *
 * \成功时返回\c 0。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\失败时返回另一个\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_ecdh_make_params( mbedtls_ecdh_context *ctx, size_t *olen,
                      unsigned char *buf, size_t blen,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

/**
 * \brief此函数解析TLS ServerKeyExchange握手消息中的ECDHE参数。
 *
 * \注意：在TLS握手中，这是客户端如何从服务器的公共ECDHE密钥材料设置其ECDHE上下文的方式。
 *
 * \见ecp.h
 *
 * \param ctx要使用的ECDHE上下文。必须对其进行初始化。\param buf在输入时，\c buf必须是输入缓冲区的开始。在输出时，\c buf将更新为指向已读取数据的结尾。成功时，这是ServerKeyExchange参数结尾后的第一个字节。发生错误时，这是检测到错误的点，除了调试失败外，通常没有任何用处。\param end输入缓冲区的结尾。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_ecdh_read_params( mbedtls_ecdh_context *ctx,
                              const unsigned char **buf,
                              const unsigned char *end );

/**
 * \brief此函数从EC密钥设置ECDH上下文。
 *
 *                  客户端和服务器使用它来代替静态ECDH的ServerKeyEchange，并从证书的EC密钥信息中导入ECDH参数。
 *
 * \见ecp.h
 *
 * \param ctx要设置的ECDH上下文。必须对其进行初始化。\param key要使用的EC密钥。必须对其进行初始化。\param-side定义密钥的源。可能的值包括：
 *                  -#MBEDTLS_ECDH_OURS：关键是我们的。
 *                  -#MBEDTLS_ECDH_THEIRS：密钥是对等方的密钥。
 *
 * \成功时返回\c 0。\失败时返回另一个\c MBEDTLS_error_ECP_XXX错误代码。
 *
 */
int mbedtls_ecdh_get_params( mbedtls_ecdh_context *ctx,
                             const mbedtls_ecp_keypair *key,
                             mbedtls_ecdh_side side );

/**
 * \brief此函数生成公钥并将其导出为TLS ClientKeyExchange负载。
 *
 *                  这是TLS客户端用于ECDH（E）密码套件的第二个功能。
 *
 * \见ecp.h
 *
 * \param ctx要使用的ECDH上下文。这必须初始化并绑定到一个组，后者通常通过mbedtls_ecdh_read_params（）进行。\param olen存储写入字节数的地址。此值不能为空。\param buf目标缓冲区。这必须是长度为\n blen Bytes的可写缓冲区。\param blen目标缓冲区的大小（字节）。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为空。
 *
 * \成功时返回\c 0。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\失败时返回另一个\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_ecdh_make_public( mbedtls_ecdh_context *ctx, size_t *olen,
                      unsigned char *buf, size_t blen,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

/**
 * \brief此函数解析并处理TLS ClientKeyExchange消息的ECDHE负载。
 *
 *              这是TLS服务器用于ECDH（E）密码套件的第三个功能。（它在mbedtls_ecdh_setup（）和mbedtls-ecdh_make_params（）之后调用。）
 *
 * \见ecp.h
 *
 * \param ctx要使用的ECDH上下文。这必须初始化并绑定到组，例如通过mbedtls_ecdh_setup（）。\param buf指向ClientKeyExchange负载的指针。这必须是一个可读缓冲区，长度为\n blen Bytes。\param blen输入缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_ecdh_read_public( mbedtls_ecdh_context *ctx,
                              const unsigned char *buf, size_t blen );

/**
 * \brief此函数派生并导出共享秘密。
 *
 *                  这是TLS客户端和服务器使用的最后一个函数。
 *
 * \注意：如果\pf_rng不为NULL，则它用于实施针对侧信道攻击的对策。有关详细信息，请参阅mbedtls_ecp_mul（）。
 *
 * \见ecp.h

 * \param ctx要使用的ECDH上下文。必须对其进行初始化，并生成其自己的私钥，并导入对等方的公钥。\param olen存储成功写入的字节总数的地址。此值不能为空。\param buf要将生成的共享密钥写入的缓冲区。这必须是大小为\p blen Bytes的可写缓冲区。\param blen目标缓冲区的长度（字节）。\param f_rng rng函数，用于致盲目的。如果不需要盲板，则可能为空。\param p_rng rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\失败时返回另一个\c MBEDTLS_error_ECP_XXX错误代码。
 */
int mbedtls_ecdh_calc_secret( mbedtls_ecdh_context *ctx, size_t *olen,
                      unsigned char *buf, size_t blen,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

#if defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \brief此函数启用此上下文的可重启EC计算。（默认值：禁用。）
 *
 * \请参见\c mbedtls_ecp_set_max_ops（）
 *
 * \注意：一旦启用，就不可能安全地禁用可重新启动的计算，除非通过释放上下文来取消可能的正在进行的操作。
 *
 * \param ctx要使用的ECDH上下文。必须对其进行初始化。
 */
void mbedtls_ecdh_enable_restart( mbedtls_ecdh_context *ctx );
#endif /* MBEDTLS_ECP_RESTARTABLE */

#ifdef __cplusplus
}
#endif

#endif /* 电子海图*/

