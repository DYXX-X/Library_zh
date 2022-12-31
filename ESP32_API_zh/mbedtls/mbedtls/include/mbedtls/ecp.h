/**
 * \文件ecp.h
 *
 * \该文件提供了GF（P）上椭圆曲线（ECP）的API。
 *
 * ECP在密码学和TLS中的使用在《高效密码组（SECG）标准：SEC1椭圆曲线密码》</em>和《RFC-4492：传输层安全（TLS）椭圆曲线密码套件》</em>中定义。
 *
 * <em>RFC-2409:Internet密钥交换（IKE）</em>定义ECP组类型。
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

#ifndef MBEDTLS_ECP_H
#define MBEDTLS_ECP_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/bignum.h"

/*
 * ECP错误代码
 */
/**函数的输入参数错误。*/
#define MBEDTLS_ERR_ECP_BAD_INPUT_DATA                    -0x4F80
/**缓冲区太小，无法写入。*/
#define MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL                  -0x4F00
/**请求的功能不可用，例如，不支持请求的曲线。*/
#define MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE               -0x4E80
/**签名无效。*/
#define MBEDTLS_ERR_ECP_VERIFY_FAILED                     -0x4E00
/**内存分配失败。*/
#define MBEDTLS_ERR_ECP_ALLOC_FAILED                      -0x4D80
/**生成随机值（如临时密钥）失败。*/
#define MBEDTLS_ERR_ECP_RANDOM_FAILED                     -0x4D00
/**私钥或公钥无效。*/
#define MBEDTLS_ERR_ECP_INVALID_KEY                       -0x4C80
/**缓冲区包含一个有效签名，后面跟着更多数据。*/
#define MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH                  -0x4C00

/* MBEDTLS_ERROR_ECP_HW_ACCEL_FAILED已弃用，不应使用。*/
/**ECP硬件加速器出现故障。*/
#define MBEDTLS_ERR_ECP_HW_ACCEL_FAILED                   -0x4B80

/**操作正在进行，请使用相同的参数再次调用以继续。*/
#define MBEDTLS_ERR_ECP_IN_PROGRESS                       -0x4B00

/* 指示是否包含特定于特定类型曲线的代码的标志。这些标志仅供内部库使用。*/
#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP384R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP512R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
#define MBEDTLS_ECP_SHORT_WEIERSTRASS_ENABLED
#endif
#if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED) || \
    defined(MBEDTLS_ECP_DP_CURVE448_ENABLED)
#define MBEDTLS_ECP_MONTGOMERY_ENABLED
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 域参数标识符：曲线、子组和生成器。
 *
 * \注意：仅支持素域上的曲线。
 *
 * \警告此库不支持验证任意域参数。因此，只能使用来自可信来源的标准化域参数。请参见mbedtls_ecp_group_load（）。
 */
/* 注意：添加新曲线时：
 * -将其添加到此枚举的末尾，否则将通过更改现有曲线的数值来破坏ABI。
 * -如果需要，将MBEDTLS_ECP_DP_MAX增加到以下。
 * -更新以下MBEDTLS_ECP_MAX_BITS_MIN的计算。
 * -将相应的MBEDTLS_ECP_DP_xxx_ENABLED宏定义添加到config.h。
 * -如果check_config.h中支持，则将曲线列为MBEDTLS_ECP_C和MBEDTLS_CDSA_C的依赖项。
 * -将曲线添加到上面相应的曲线类型宏MBEDTLS_ECP_yyy_ENABLED中。
 * -向ecp_curves.c添加必要的定义。
 * -将曲线添加到ecp.c中的ecp_supported_curves数组中。
 * -将曲线添加到x509_crt中的适用轮廓。c如果适用。
 */
typedef enum
{
    MBEDTLS_ECP_DP_NONE = 0,       /*!< 未定义曲线。*/
    MBEDTLS_ECP_DP_SECP192R1,      /*!< FIPS 186-4和SEC1定义的192位曲线的域参数。*/
    MBEDTLS_ECP_DP_SECP224R1,      /*!< FIPS 186-4和SEC1定义的224位曲线的域参数。*/
    MBEDTLS_ECP_DP_SECP256R1,      /*!< FIPS 186-4和SEC1定义的256位曲线的域参数。*/
    MBEDTLS_ECP_DP_SECP384R1,      /*!< FIPS 186-4和SEC1定义的384位曲线的域参数。*/
    MBEDTLS_ECP_DP_SECP521R1,      /*!< FIPS 186-4和SEC1定义的521位曲线的域参数。*/
    MBEDTLS_ECP_DP_BP256R1,        /*!< 256位Brainpool曲线的域参数。*/
    MBEDTLS_ECP_DP_BP384R1,        /*!< 384位Brainpool曲线的域参数。*/
    MBEDTLS_ECP_DP_BP512R1,        /*!< 512位Brainpool曲线的域参数。*/
    MBEDTLS_ECP_DP_CURVE25519,     /*!< Curve25519的域参数。*/
    MBEDTLS_ECP_DP_SECP192K1,      /*!< 192位“Koblitz”曲线的域参数。*/
    MBEDTLS_ECP_DP_SECP224K1,      /*!< 224位“Koblitz”曲线的域参数。*/
    MBEDTLS_ECP_DP_SECP256K1,      /*!< 256位“Koblitz”曲线的域参数。*/
    MBEDTLS_ECP_DP_CURVE448,       /*!< Curve448的域参数。*/
} mbedtls_ecp_group_id;

/**
 * 支持的曲线数，加上#MBEDTLS_EP_DP_NONE的一条。
 *
 * \注意蒙哥马利曲线目前被排除在外。
 */
#define MBEDTLS_ECP_DP_MAX     12

/*
 * 曲线类型
 */
typedef enum
{
    MBEDTLS_ECP_TYPE_NONE = 0,
    MBEDTLS_ECP_TYPE_SHORT_WEIERSTRASS,    /* y ^2=x ^3+a x+b*/
    MBEDTLS_ECP_TYPE_MONTGOMERY,           /* y ^2=x ^3+a x ^2+x*/
} mbedtls_ecp_curve_type;

/**
 * 曲线信息，供其他模块使用。
 */
typedef struct mbedtls_ecp_curve_info
{
    mbedtls_ecp_group_id grp_id;    /*!< 内部标识符。*/
    uint16_t tls_id;                /*!< TLS NamedCurve标识符。*/
    uint16_t bit_size;              /*!< 以位为单位的曲线大小。*/
    const char *name;               /*!< 人类友好的名字。*/
} mbedtls_ecp_curve_info;

/**
 * \简要ECP点结构，以雅可比坐标表示。
 *
 * \注意：所有函数都期望并返回满足以下条件的点：<code>Z==0</code>或<code>Z==1</code>。\p Z的其他值仅由内部函数使用。如果<code>Z==0</code>，则该点为零或“在无穷远处”。否则，\p X和\p Y是其标准（仿射）坐标。
 */
typedef struct mbedtls_ecp_point
{
    mbedtls_mpi X;          /*!< ECP点的X坐标。*/
    mbedtls_mpi Y;          /*!< ECP点的Y坐标。*/
    mbedtls_mpi Z;          /*!< ECP点的Z坐标。*/
}
mbedtls_ecp_point;

/* 确定MBEDTLS_ECP_MAX_BITS的最小安全值。*/
#if !defined(MBEDTLS_ECP_C)
#define MBEDTLS_ECP_MAX_BITS_MIN 0
/* 注意：曲线必须以递减大小列出！*/
#elif defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 521
#elif defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 512
#elif defined(MBEDTLS_ECP_DP_CURVE448_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 448
#elif defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 384
#elif defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 384
#elif defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 256
#elif defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 256
#elif defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 256
#elif defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 255
#elif defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 225 // n略高于2^224
#elif defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 224
#elif defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 192
#elif defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
#define MBEDTLS_ECP_MAX_BITS_MIN 192
#else
#error "MBEDTLS_ECP_C enabled, but no curve?"
#endif

#if !defined(MBEDTLS_ECP_ALT)
/*
 * 默认mbed TLS椭圆曲线算法实现
 *
 * （如果定义了MBEDTLS_ECP_ALT，则开发人员必须为整个模块提供替代实现，并将替换此实现。）
 */

/**
 * \ECP集团结构简介。
 *
 * 我们考虑两种类型的曲线方程：<ul><li>Short Weierstrass：<code>y^2=x^3+A x+B mod P</code>（SEC1+RFC-4492）</li><li>蒙哥马利：<code>y^2=x ^3+A x ^2+x mod P</code>（Curve25519，Curve448）</li></ul>在这两种情况下，素数阶子群的生成器（\P G）都是固定的。
 *
 * 对于Short Weierstrass，该子群是整条曲线，其基数由\p N表示。我们的代码要求\p N是奇数素数，因为mbedtls_ecp_mul（）需要奇数，而mbedtls-ecdsa_sign（）要求它是素数，用于致盲。
 *
 * 对于蒙哥马利曲线，我们不存储\p A，而是<code>（A+2）/4</code>，这是公式中使用的量。此外，位不是N的大小，而是私钥所需的大小。
 *
 * 如果modp为NULL，则使用通用算法进行模p的归约。否则，modp必须指向一个函数，该函数的mbedtls_mpi值在<code>0..2^（2pbits）-1</code>的范围内，并将其转换为一个整数，该整数与给定的mpi一致，并且大小足够接近，因此可以通过几次加法或减法将其有效地带入0..p-1范围。因此，它只是一个近似的模化约简。成功时必须返回0，失败时必须返回非零。
 *
 * \注意：替代实现必须保持组ID不同。如果两个组结构具有相同的ID，则它们必须相同。
 *
 */
typedef struct mbedtls_ecp_group
{
    mbedtls_ecp_group_id id;    /*!< 内部组标识符。*/
    mbedtls_mpi P;              /*!< 基础场的素模量。*/
    mbedtls_mpi A;              /*!< 对于Short Weierstrass：方程中的A。对于蒙哥马利曲线：<code>（A+2）/4</code>。*/
    mbedtls_mpi B;              /*!< 对于Short Weierstrass：方程中的B。对于蒙哥马利曲线：未使用。*/
    mbedtls_ecp_point G;        /*!< 使用的子组的生成器。*/
    mbedtls_mpi N;              /*!< G的顺序。*/
    size_t pbits;               /*!< p中的位数。*/
    size_t nbits;               /*!< 对于Short Weierstrass：p中的位数。对于Montgomery曲线：私钥的位数。*/
    unsigned int h;             /*!< \如果常数是静态的，则为内部1。*/
    int (*modp)(mbedtls_mpi *); /*!< 快速伪归约模p的函数（见上文）。*/
    int (*t_pre)(mbedtls_ecp_point *, void *);  /*!< 未使用。*/
    int (*t_post)(mbedtls_ecp_point *, void *); /*!< 未使用。*/
    void *t_data;               /*!< 未使用。*/
    mbedtls_ecp_point *T;       /*!< ecp_mul_comb（）的预计算点。*/
    size_t T_size;              /*!< 预先计算的点数。*/
}
mbedtls_ecp_group;

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h、 或使用编译器命令行定义它们\{
 */

#if defined(MBEDTLS_ECP_MAX_BITS)

#if MBEDTLS_ECP_MAX_BITS < MBEDTLS_ECP_MAX_BITS_MIN
#error "MBEDTLS_ECP_MAX_BITS is smaller than the largest supported curve"
#endif

#elif defined(MBEDTLS_ECP_C)
/**
 * 组的最大大小，即\c N和\c P。
 */
#define MBEDTLS_ECP_MAX_BITS     MBEDTLS_ECP_MAX_BITS_MIN

#else
/* 如果没有MBEDTLS_ECP_MAX_BITS，则MBEDTLS_ECP_C不相关，但将其设置为非零值，以便无条件分配基于其大小的数组的代码在没有ECC支持的情况下构建时仍能正常工作。*/
#define MBEDTLS_ECP_MAX_BITS 1
#endif

#define MBEDTLS_ECP_MAX_BYTES    ( ( MBEDTLS_ECP_MAX_BITS + 7 ) / 8 )
#define MBEDTLS_ECP_MAX_PT_LEN   ( 2 * MBEDTLS_ECP_MAX_BYTES + 1 )

#if !defined(MBEDTLS_ECP_WINDOW_SIZE)
/*
 * 用于点乘法的最大“窗口”大小。默认值：内存使用率越高，性能越差。最小值：2。最大值：7。
 *
 * 结果是用于点乘法的最多（1<<（MBEDTLS_ECP_WINDOW_SIZE-1））个点的数组。该值与EC峰值内存使用量直接相关，因此将其减少一应该可以将内存使用量大致减少两倍（如果使用大型曲线）。
 *
 * 尺寸减小可能会降低速度，但较大的曲线首先受到影响。示例性能（ECDHE握手/秒，FIXED_POINT_OPTIM=1）：w-size:6 5 4 3 2 521 145 141 135 120 97 384 214 209 198 177 146 256 320 303 262 224 475 453 398 342 192 640 633 587 476
 */
#define MBEDTLS_ECP_WINDOW_SIZE    4   /**<使用的最大窗口大小。*/
#endif /* MBEDTLS_ECP_WINDOW_SIZE */

#if !defined(MBEDTLS_ECP_FIXED_POINT_OPTIM)
/*
 * 用内存换取定点乘法的速度。
 *
 * 这将使生成器的重复乘法（即ECDSA签名中的乘法，以及ECDSA验证和ECDHE中的乘法的一半）加快大约3到4倍。
 *
 * 成本使EC峰值内存使用量增加了大约2倍。
 *
 * 将此值更改为0以减少峰值内存使用。
 */
#define MBEDTLS_ECP_FIXED_POINT_OPTIM  1   /**<启用定点加速。*/
#endif /* MBEDTLS_ECP_FIXED_POINT_OPTIM */

/* \}name SECTION:模块设置*/

#else  /* MBEDTLS_ECP_ALT */
#include "ecp_alt.h"
#endif /* MBEDTLS_ECP_ALT */

#if defined(MBEDTLS_ECP_RESTARTABLE)

/**
 * \乘法的简短内部重新启动上下文
 *
 * \注释不透明结构
 */
typedef struct mbedtls_ecp_restart_mul mbedtls_ecp_restart_mul_ctx;

/**
 * \ecp_muladd（）的简短内部重新启动上下文
 *
 * \注释不透明结构
 */
typedef struct mbedtls_ecp_restart_muladd mbedtls_ecp_restart_muladd_ctx;

/**
 * \恢复ECC操作的简要概述
 */
typedef struct
{
    unsigned ops_done;                  /*!<  当前操作数*/
    unsigned depth;                     /*!<  调用深度（0=顶级）*/
    mbedtls_ecp_restart_mul_ctx *rsm;   /*!<  ecp_mul_comb（）子上下文*/
    mbedtls_ecp_restart_muladd_ctx *ma; /*!<  ecp_muladd（）子上下文*/
} mbedtls_ecp_restart_ctx;

/*
 * 可重新启动函数的操作计数
 */
#define MBEDTLS_ECP_OPS_CHK   3 /*!< ecp_check_pubkey（）的基本操作计数*/
#define MBEDTLS_ECP_OPS_DBL   8 /*!< ecp_double_jac（）的基本操作数*/
#define MBEDTLS_ECP_OPS_ADD  11 /*!< 基本操作计数，请参见ecp_add_mixed（）*/
#define MBEDTLS_ECP_OPS_INV 120 /*!< mpi_modinv（）的经验等价*/

/**
 * \简要内部；用于其他模块中的可重启功能。检查并更新基本运营预算。
 *
 * \param grp组结构\param rs_ctx重新启动上下文\param ops要执行的基本操作数
 *
 * \如果仍允许执行基本操作，则返回\c 0，否则返回#MBEDTLS_ERROR_ECP_IN_PROGRESS。
 */
int mbedtls_ecp_check_budget( const mbedtls_ecp_group *grp,
                              mbedtls_ecp_restart_ctx *rs_ctx,
                              unsigned ops );

/* 用于检查和更新操作预算的实用宏*/
#define MBEDTLS_ECP_BUDGET( ops )   \
    MBEDTLS_MPI_CHK( mbedtls_ecp_check_budget( grp, rs_ctx, \
                                               (unsigned) (ops) ) );

#else /* MBEDTLS_ECP_RESTARTABLE */

#define MBEDTLS_ECP_BUDGET( ops )   /* 无操作；兼容性*/

/* 无论如何，我们都希望声明现有函数的可重启版本*/
typedef void mbedtls_ecp_restart_ctx;

#endif /* MBEDTLS_ECP_RESTARTABLE */

/**
 * \简要介绍ECP密钥对结构。
 *
 * 例如，可用于ECDSA和固定ECDH的通用密钥对。
 *
 * \注意成员的顺序故意与：：mbedtls_ecdsa_context结构中的顺序相同。
 */
typedef struct mbedtls_ecp_keypair
{
    mbedtls_ecp_group grp;      /*!<  椭圆曲线和基点*/
    mbedtls_mpi d;              /*!<  我们的秘密价值*/
    mbedtls_ecp_point Q;        /*!<  我们的公共价值*/
}
mbedtls_ecp_keypair;

/*
 * 点格式，来自RFC 4492的枚举ECPointFormat
 */
#define MBEDTLS_ECP_PF_UNCOMPRESSED    0   /**<未压缩点格式。*/
#define MBEDTLS_ECP_PF_COMPRESSED      1   /**<压缩点格式。*/

/*
 * RFC 4492中的一些其他常量
 */
#define MBEDTLS_ECP_TLS_NAMED_CURVE    3   /**<ECCurveType的named_curve。*/

#if defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \brief设置一行中完成的基本操作的最大数量。
 *
 *                  如果需要更多操作来完成计算，则执行计算的函数将返回#MBEDTLS_ERROR_ECP_IN_PROGRESS。然后调用方负责使用相同的参数再次调用，直到返回0或错误代码；或者如果操作将被中止，则释放重新启动上下文。
 *
 *                  对于同一操作的连续调用，严格要求所有输入参数和重新启动上下文相同，但输出参数不必相同；在函数最终返回0之前，不能使用它们。
 *
 *                  这仅适用于文档中提到可能返回#MBEDTLS_ERROR_ECP_IN_PROGRESS（或SSL模块中的函数返回#MBEDTLS_ERR_SSL_CRYPTO_IN_PROGRESS）的函数。对于接受“restart context”参数的函数，传递NULL将禁用重新启动，并使该函数与删除了\c_restartable的同名函数等效。对于ECDH模块中的函数，除非函数接受“ECDH上下文”参数，并且之前在该上下文中调用了mbedtls_ECDH_enable_restart（），否则将禁用重新启动。对于SSL模块中的功能，仅对特定侧和密钥交换启用重新启动（当前仅对客户端和ECDHE-ECDSA）。
 *
 * \param max_ops一行中完成的基本操作的最大数量。默认值：0（无限制）。较低的（非零）值意味着ECC函数将阻塞较短的最长时间。
 *
 * \注：“基本运算”定义为NIST p-256曲线的GF（p）乘法的大致等价物。作为指示，在默认设置下，标量乘法（\c mbedtls_ecp_mul（）的完整运行）为：
 *                  -P-256的大约3300个基本操作
 *                  -P-384大约9400次基本操作
 *
 * \注意：非常低的值并不总是被遵守的：有时函数需要为最小数量的操作进行阻塞，即使max_ops设置为较低的值，也会这样做。该最小值取决于曲线大小，可以通过减小MBEDTLS_ECP_WINDW_size的值来降低。作为指示，这里是该参数的各种曲线和值的最低有效值（简称w）：w=6 w=5 w=4 w=3 w=2 P-256 208 208 160 136 124 P-384 682 416 320 272 248 P-521 1364 832 640 544 496
 *
 * \注意Curve25519当前忽略此设置。
 */
void mbedtls_ecp_set_max_ops( unsigned max_ops );

/**
 * \brief检查是否启用了重新启动（max_ops！=0）
 *
 * \如果\c max_ops==0（禁用重新启动），则返回\c 0；否则返回\c 1（启用重新启动）
 */
int mbedtls_ecp_restart_is_enabled( void );
#endif /* MBEDTLS_ECP_RESTARTABLE */

/*
 * 获取曲线的类型
 */
mbedtls_ecp_curve_type mbedtls_ecp_get_type( const mbedtls_ecp_group *grp );

/**
 * \brief此函数检索mbedtls_ecp_curve_info（）中定义的所有支持曲线的信息。
 *
 * \注意：此函数返回有关库支持的所有曲线的信息。某些曲线可能不适用于所有算法。调用mbedtls_ecdh_can_do（）或mbedtls-ecdsa_can_d（）检查ecdh或ecdsa是否支持曲线。
 *
 * \return静态分配的数组。最后一个条目是0。
 */
const mbedtls_ecp_curve_info *mbedtls_ecp_curve_list( void );

/**
 * \brief此函数按首选项顺序检索所有受支持曲线的内部组标识符列表。
 *
 * \注意：此函数返回有关库支持的所有曲线的信息。某些曲线可能不适用于所有算法。调用mbedtls_ecdh_can_do（）或mbedtls-ecdsa_can_d（）检查ecdh或ecdsa是否支持曲线。
 *
 * \return静态分配的数组，以MBEDTLS_ECP_DP_NONE结尾。
 */
const mbedtls_ecp_group_id *mbedtls_ecp_grp_id_list( void );

/**
 * \brief此函数从内部组标识符中检索曲线信息。
 *
 * \param grp_id一个\c MBEDTLS_ECP_DP_XXX值。
 *
 * \return成功时的关联曲线信息。\失败时返回NULL。
 */
const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_grp_id( mbedtls_ecp_group_id grp_id );

/**
 * \brief此函数从TLS NamedCurve值中检索曲线信息。
 *
 * \param tls_id An\c MBEDTLS_ECP_DP_XXX值。
 *
 * \return成功时的关联曲线信息。\失败时返回NULL。
 */
const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_tls_id( uint16_t tls_id );

/**
 * \brief此函数从人类可读的名称中检索曲线信息。
 *
 * \param name人类可读的名称。
 *
 * \return成功时的关联曲线信息。\失败时返回NULL。
 */
const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_name( const char *name );

/**
 * \brief此函数将点初始化为零。
 *
 * \param pt要初始化的点。
 */
void mbedtls_ecp_point_init( mbedtls_ecp_point *pt );

/**
 * \brief此函数在不加载任何域参数的情况下初始化ECP组上下文。
 *
 * \注意：调用此函数后，可以通过mbedtls_ECP_group_load（）或mbedtls-ECP_tls_read_group（）函数加载各种ECP组的域参数。
 */
void mbedtls_ecp_group_init( mbedtls_ecp_group *grp );

/**
 * \brief此函数将密钥对初始化为无效密钥对。
 *
 * \param key要初始化的密钥对。
 */
void mbedtls_ecp_keypair_init( mbedtls_ecp_keypair *key );

/**
 * \brief此函数释放点的组件。
 *
 * \param pt要释放的点。
 */
void mbedtls_ecp_point_free( mbedtls_ecp_point *pt );

/**
 * \brief此函数释放ECP组的组件。
 *
 * \param grp要释放的组。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空，则必须指向已初始化的ECP组。
 */
void mbedtls_ecp_group_free( mbedtls_ecp_group *grp );

/**
 * \brief此函数释放密钥对的组件。
 *
 * \param key要释放的密钥对。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空，则必须指向已初始化的ECP密钥对。
 */
void mbedtls_ecp_keypair_free( mbedtls_ecp_keypair *key );

#if defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \brief初始化重新启动上下文。
 *
 * \param ctx要初始化的重新启动上下文。此值不能为空。
 */
void mbedtls_ecp_restart_init( mbedtls_ecp_restart_ctx *ctx );

/**
 * \brief释放重启上下文的组件。
 *
 * \param ctx要释放的重新启动上下文。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空，则必须指向初始化的重新启动上下文。
 */
void mbedtls_ecp_restart_free( mbedtls_ecp_restart_ctx *ctx );
#endif /* MBEDTLS_ECP_RESTARTABLE */

/**
 * \brief此函数将点Q的内容复制到点p。
 *
 * \param P目标点。必须对其进行初始化。\param Q源点。必须对其进行初始化。
 *
 * \成功时返回\c 0。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_copy( mbedtls_ecp_point *P, const mbedtls_ecp_point *Q );

/**
 * \brief此函数将group\p src的内容复制到group\p dst中。
 *
 * \param dst目标组。必须对其进行初始化。\param src源组。必须对其进行初始化。
 *
 * \成功时返回\c 0。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_group_copy( mbedtls_ecp_group *dst,
                            const mbedtls_ecp_group *src );

/**
 * \brief此函数将点设置为无穷远处的点。
 *
 * \param pt要设置的点。必须对其进行初始化。
 *
 * \成功时返回\c 0。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_set_zero( mbedtls_ecp_point *pt );

/**
 * \brief这个函数检查一个点是否是无穷远处的点。
 *
 * \param pt要测试的点。必须对其进行初始化。
 *
 * \如果点为零，则返回\c 1。\如果点为非零，则返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ecp_is_zero( mbedtls_ecp_point *pt );

/**
 * \brief此函数比较两点。
 *
 * \注意：这假设点是标准化的。否则，他们可能会被比较为“不平等”，即使他们是平等的。
 *
 * \param P要比较的第一个点。必须对其进行初始化。\param Q要比较的第二个点。必须对其进行初始化。
 *
 * \如果点数相等，则返回\c 0。\如果点不相等，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。
 */
int mbedtls_ecp_point_cmp( const mbedtls_ecp_point *P,
                           const mbedtls_ecp_point *Q );

/**
 * \brief此函数从两个ASCII字符串中导入一个非零点。
 *
 * \param P目标点。必须对其进行初始化。\param radix输入的数字基数。\param x第一个仿射坐标，作为空终止字符串。\param y第二个仿射坐标，作为空终止字符串。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_MPI_XXX错误代码。
 */
int mbedtls_ecp_point_read_string( mbedtls_ecp_point *P, int radix,
                           const char *x, const char *y );

/**
 * \brief此函数将点导出为无符号二进制数据。
 *
 * \param grp点应属于的组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param P要导出的点。必须对其进行初始化。\param format点格式。必须是#MBEDTLS_ECP_PF_COMPRESSED或#MBEDLLS_ECP_F_UNCCOMPRESSED。（对于没有这些格式的组，此参数将被忽略。但它仍然必须是上述值之一。）\param olen以字节为单位存储输出长度的地址。此值不能为空。\param buf输出缓冲区。这必须是长度为\p buflen Bytes的可写缓冲区。\param buflen输出缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\如果输出缓冲区太小，无法保存该点，则返回#MBEDTLS_ERROR_ECP_BUFFER_TOO_SMALL。\如果未实现给定组的点格式或导出，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_point_write_binary( const mbedtls_ecp_group *grp,
                                    const mbedtls_ecp_point *P,
                                    int format, size_t *olen,
                                    unsigned char *buf, size_t buflen );

/**
 * \brief此函数从无符号二进制数据中导入点。
 *
 * \注意：此函数不会检查点是否实际属于给定组，请参见mbedtls_ecp_check_pubkey（）。
 *
 * \param grp点应属于的组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param P要将点导入的目标上下文。必须对其进行初始化。\param buf输入缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\如果输入无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果未实现给定组的导入，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。
 */
int mbedtls_ecp_point_read_binary( const mbedtls_ecp_group *grp,
                                   mbedtls_ecp_point *P,
                                   const unsigned char *buf, size_t ilen );

/**
 * \brief此函数从TLS ECPoint记录中导入点。
 *
 * \注意：在函数返回时，\p*buf会立即更新为ECPoint记录之后的点。
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param pt目标点。\param buf指向输入缓冲区起点的指针的地址。\param len缓冲区的长度。
 *
 * \成功时返回\c 0。\初始化失败时返回\c MBEDTLS_error_MPI_XXX错误代码。\如果输入无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。
 */
int mbedtls_ecp_tls_read_point( const mbedtls_ecp_group *grp,
                                mbedtls_ecp_point *pt,
                                const unsigned char **buf, size_t len );

/**
 * \brief此函数将点导出为RFC 4492第5.4节中定义的TLS ECPoint记录。
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param pt要导出的点。必须对其进行初始化。\param format要使用的点格式。必须是#MBEDTLS_ECP_PF_COMPRESSED或#MBEDLLS_ECP_F_UNCCOMPRESSED。\param olen存储写入数据长度（字节）的地址。\param buf目标缓冲区。这必须是长度为\n blen Bytes的可写缓冲区。\param blen目标缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\如果输入无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\如果目标缓冲区太小，无法容纳导出的点，则返回#MBEDTLS_ERROR_ECP_BUFFER_TOO_SMALL。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_tls_write_point( const mbedtls_ecp_group *grp,
                                 const mbedtls_ecp_point *pt,
                                 int format, size_t *olen,
                                 unsigned char *buf, size_t blen );

/**
 * \brief此函数从一组标准化的域参数设置ECP组上下文。
 *
 * \注意：索引应该是NamedCurve枚举的值，如<em>RFC-4492:Elliptic Curve Cryptography（ECC）Cipher Suites for Transport Layer Security（TLS）</em>中所定义，通常以\c MBEDTLS_EP_DP_XXX宏的形式。
 *
 * \param grp要设置的组上下文。必须对其进行初始化。\param id要加载的域参数集的标识符。
 *
 * \成功时返回\c 0。\返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE，如果\p id与已知组不对应。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_group_load( mbedtls_ecp_group *grp, mbedtls_ecp_group_id id );

/**
 * \brief此函数根据RFC 4492第5.4节中定义的TLS ECParameters记录设置ECP组上下文。
 *
 * \注意：退出时，读取指针\p buf将更新为正好位于ECParameters记录之后。
 *
 * \param grp要设置的组上下文。必须对其进行初始化。\param buf指向输入缓冲区起点的指针的地址。\param len输入缓冲区的长度，以字节为单位。
 *
 * \成功时返回\c 0。\如果输入无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\如果无法识别组，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_tls_read_group( mbedtls_ecp_group *grp,
                                const unsigned char **buf, size_t len );

/**
 * \该函数从TLS ECParameters记录中提取椭圆曲线组ID，如RFC 4492第5.4节所定义。
 *
 * \注意：退出时，读取指针\p buf将更新为正好位于ECParameters记录之后。
 *
 * \param grp存储组id的地址。该地址不能为\c NULL。\param buf指向输入缓冲区起点的指针的地址。\param len输入缓冲区的长度，以字节为单位。
 *
 * \成功时返回\c 0。\如果输入无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\如果无法识别组，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_tls_read_group_id( mbedtls_ecp_group_id *grp,
                                   const unsigned char **buf,
                                   size_t len );
/**
 * \brief此函数将椭圆曲线导出为RFC 4492第5.4节中定义的TLS ECParameters记录。
 *
 * \param grp要导出的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param olen存储写入字节数的地址。此值不能为空。\param buf要写入的缓冲区。这必须是长度为\p blen Bytes的可写缓冲区。\param blen输出缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\如果输出缓冲区太小，无法容纳导出的组，则返回#MBEDTLS_ERROR_ECP_BUFFER_TOO_SMALL。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_tls_write_group( const mbedtls_ecp_group *grp,
                                 size_t *olen,
                                 unsigned char *buf, size_t blen );

/**
 * \brief此函数执行点与整数的标量乘法：\p R=\p m\p p。
 *
 *                  在多个线程中使用同一组不是线程安全的。
 *
 * \注意：为了防止定时攻击，此函数对任何有效的\pm执行完全相同的基字段操作序列。它根据\pm的值避免任何if分支或数组索引。
 *
 * \注意：如果\pf_rng不为NULL，则它用于随机化中间结果，以防止针对这些结果的潜在定时攻击。我们建议始终提供非NULL \p f_rng。开销可以忽略不计。注意：除非定义了#MBEDTLS_ECP_NO_INTERNAL_RNG，否则当\pf_RNG为NULL时，将使用内部RNG（从值\p m中种子）。
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param R存储计算结果的点。必须对其进行初始化。\param m要乘以的整数。必须对其进行初始化。\param P要相乘的点。必须对其进行初始化。\param f_rng rng函数。如果不希望（不鼓励）对中间结果进行随机化，则该值可能为空。\param p_rng要传递给/p p_rng的rng上下文。
 *
 * \成功时返回\c 0。\如果\p m不是有效的私钥或\p p不是有效的公钥，则返回#MBEDTLS_ERROR_ECP_INVALID_KEY。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_mul( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/**
 * \brief此函数以可重新启动的方式执行点与整数的乘法：\p R=\p m\p p。
 *
 * \请参见mbedtls_ecp_mul（）
 *
 * \注意：此函数与\c mbedtls_ecp_mul（）执行相同的操作，但它可以提前返回并根据\c mbedt ls_ecp_set_max_ops（）设置的限制重新启动，以减少阻塞。
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param R存储计算结果的点。必须对其进行初始化。\param m要乘以的整数。必须对其进行初始化。\param P要相乘的点。必须对其进行初始化。\param f_rng rng函数。如果不希望（不鼓励）对中间结果进行随机化，则该值可能为空。\param p_rng要传递给/p p_rng的rng上下文。\param rs_ctx重新启动上下文（NULL禁用重新启动）。
 *
 * \成功时返回\c 0。\如果\p m不是有效的私钥或\p p不是有效的公钥，则返回#MBEDTLS_ERROR_ECP_INVALID_KEY。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_mul_restartable( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
             mbedtls_ecp_restart_ctx *rs_ctx );

#if defined(MBEDTLS_ECP_SHORT_WEIERSTRASS_ENABLED)
/**
 * \brief此函数执行两个点与整数的乘法和加法：\p R=\p m\p p+\p n\p Q
 *
 *                  在多个线程中使用同一组不是线程安全的。
 *
 * \注意：与mbedtls_ecp_mul（）不同，此函数不能保证恒定的执行流和定时。
 *
 * \注意：此函数仅针对短Weierstrass曲线定义。它可能不包含在没有任何短Weierstrass曲线的构建中。
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param R存储计算结果的点。必须对其进行初始化。\param m要乘以p的整数。必须对其进行初始化。\param P要乘以\P m的点。必须对其进行初始化。\param n要乘以Q的整数。这必须初始化。\param Q要乘以\n的点。必须对其进行初始化。
 *
 * \成功时返回\c 0。\如果\p m或\p n不是有效的私钥，或者\p p或\p Q不是有效的公钥，则返回#MBEDTLS_ERROR_ECP_INVALID_KEY。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p grp未指定短Weierstrass曲线，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_muladd( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q );

/**
 * \brief此函数以可重新启动的方式执行两点与整数的乘法和加法：\p R=\p m\p p+\p n\p Q。
 *
 * \请参见\c mbedtls_ecp_muladd（）
 *
 * \注意：此函数的工作原理与\c mbedtls_ecp_muladd（）相同，但它可以提前返回并根据\c mbedtls_ecp_set_max_ops（）设置的限制重新启动，以减少阻塞。
 *
 * \注意：此函数仅针对短Weierstrass曲线定义。它可能不包含在没有任何短Weierstrass曲线的构建中。
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param R存储计算结果的点。必须对其进行初始化。\param m要乘以p的整数。必须对其进行初始化。\param P要乘以\P m的点。必须对其进行初始化。\param n要乘以Q的整数。这必须初始化。\param Q要乘以\n的点。必须对其进行初始化。\param rs_ctx重新启动上下文（NULL禁用重新启动）。
 *
 * \成功时返回\c 0。\如果\p m或\p n不是有效的私钥，或者\p p或\p Q不是有效的公钥，则返回#MBEDTLS_ERROR_ECP_INVALID_KEY。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p grp未指定短Weierstrass曲线，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_muladd_restartable(
             mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q,
             mbedtls_ecp_restart_ctx *rs_ctx );
#endif /* MBEDTLS_ECP_SHORT_WEIERSTRASS_ENABLED */

/**
 * \brief此函数检查此曲线上的点是否为有效公钥。
 *
 *                  它只检查该点是否为非零，是否具有有效坐标，是否位于曲线上。它不能验证它确实是G的倍数。这种额外的检查在计算上更昂贵，标准不需要，如果使用的组具有小的辅因子，则不需要。特别是，对于所有辅因子均为1的NIST小组来说，这是无用的。
 *
 * \注意：此函数使用裸组件而不是：：mbedtls_ecp_keypair结构，以便于与其他结构（例如：：mbedtls_ecdh_context或：：mbedt ls_ecdsa_context）一起使用。
 *
 * \param grp点应该属于的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ECP_group_load（）。\param pt要检查的点。必须对其进行初始化。
 *
 * \如果该点是有效的公钥，则返回\c 0。\如果该点不是给定曲线的有效公钥，则返回#MBEDTLS_ERROR_ECP_INVALID_KEY。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_check_pubkey( const mbedtls_ecp_group *grp,
                              const mbedtls_ecp_point *pt );

/**
 * \brief此函数检查\p mbedtls_mpi是否是此曲线的有效私钥。
 *
 * \注意：此函数使用裸组件而不是：：mbedtls_ecp_keypair结构，以便于与其他结构（例如：：mbedtls_ecdh_context或：：mbedt ls_ecdsa_context）一起使用。
 *
 * \param grp私钥应该属于的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ECP_group_load（）。\param d要检查的整数。必须对其进行初始化。
 *
 * \如果该点是有效的私钥，则返回\c 0。\如果该点不是给定曲线的有效私钥，则返回#MBEDTLS_ERROR_ECP_INVALID_KEY。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_ecp_check_privkey( const mbedtls_ecp_group *grp,
                               const mbedtls_mpi *d );

/**
 * \brief此函数生成私钥。
 *
 * \param grp要为其生成私钥的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param d目标MPI（机密部分）。必须对其进行初始化。\param f_rng rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecp_gen_privkey( const mbedtls_ecp_group *grp,
                     mbedtls_mpi *d,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng );

/**
 * \brief此函数生成具有可配置基点的按键对。
 *
 * \注意：此函数使用裸组件而不是：：mbedtls_ecp_keypair结构，以便于与其他结构（例如：：mbedtls_ecdh_context或：：mbedt ls_ecdsa_context）一起使用。
 *
 * \param grp要为其生成密钥对的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param G要使用的基点。这必须初始化并属于\p grp。它将替换mbedtls_ecp_gen_keypair（）使用的默认基点\cgrp->G。\param d目标MPI（机密部分）。必须对其进行初始化。\param Q目标点（公共部分）。必须对其进行初始化。\param f_rng rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecp_gen_keypair_base( mbedtls_ecp_group *grp,
                                  const mbedtls_ecp_point *G,
                                  mbedtls_mpi *d, mbedtls_ecp_point *Q,
                                  int (*f_rng)(void *, unsigned char *, size_t),
                                  void *p_rng );

/**
 * \brief此函数生成ECP键对。
 *
 * \注意：此函数使用裸组件而不是：：mbedtls_ecp_keypair结构，以便于与其他结构（例如：：mbedtls_ecdh_context或：：mbedt ls_ecdsa_context）一起使用。
 *
 * \param grp要为其生成密钥对的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param d目标MPI（机密部分）。必须对其进行初始化。\param Q目标点（公共部分）。必须对其进行初始化。\param f_rng rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecp_gen_keypair( mbedtls_ecp_group *grp, mbedtls_mpi *d,
                             mbedtls_ecp_point *Q,
                             int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng );

/**
 * \brief此函数生成ECP密钥。
 *
 * \param grp_id ECP组标识符。\param key目标密钥。必须对其进行初始化。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecp_gen_key( mbedtls_ecp_group_id grp_id, mbedtls_ecp_keypair *key,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng );

/**
 * \brief此函数读取椭圆曲线私钥。
 *
 * \param grp_id ECP组标识符。\param key目标密钥。\param buf包含密钥二进制表示的缓冲区。（Weierstrass曲线为大端整数，Montgomery曲线为字节字符串。）\param buflen缓冲区的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\如果密钥无效，则返回#MBEDTLS_error_ECP_INVALID_KEY错误。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果未实现组的操作，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_ecp_read_key( mbedtls_ecp_group_id grp_id, mbedtls_ecp_keypair *key,
                          const unsigned char *buf, size_t buflen );

/**
 * \brief此函数导出椭圆曲线私钥。
 *
 * \param key私钥。\param buf用于包含密钥的二进制表示的输出缓冲区。（Weierstrass曲线为大端整数，Montgomery曲线为字节字符串。）\param buflen缓冲区的总长度（字节）。
 *
 * \成功时返回\c 0。\如果密钥表示大于缓冲区中的可用空间，则返回#MBEDTLS_ERROR_ECP_BUFFER_TOO_SMALL。\如果未实现组的操作，则返回#MBEDTLS_ERROR_ECP_FEATURE_NAVAILABLE。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_ecp_write_key( mbedtls_ecp_keypair *key,
                           unsigned char *buf, size_t buflen );

/**
 * \brief此函数检查密钥对对象\ppub和\pprv是否具有相同的组和相同的公共点，以及\pprv中的私钥是否与公钥一致。
 *
 * \param pub保存公钥的密钥对结构。必须对其进行初始化。如果它包含私钥，则忽略该部分。\param prv保存完整按键对的按键对结构。必须对其进行初始化。
 *
 * \成功时返回\c 0，表示密钥有效且匹配。\如果密钥无效或不匹配，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\在计算失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_ERR_MPI_XXX错误代码。
 */
int mbedtls_ecp_check_pub_priv( const mbedtls_ecp_keypair *pub,
                                const mbedtls_ecp_keypair *prv );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要介绍ECP检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_ecp_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* ecp.小时*/

