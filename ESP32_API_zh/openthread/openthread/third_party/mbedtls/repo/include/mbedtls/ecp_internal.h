/**
 * \文件ecp_internal.h
 *
 * \椭圆曲线点算法替代实现的简短函数声明。
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

/*
 * 参考文献：
 *
 * [1] Daniel J.Curve25519：新的Diffie Hellman速度记录<http://cr.yp.to/ecdh/curve25519-20060209.pdf>
 *
 * [2] CORON，Jean-S'ebastien。椭圆曲线密码系统的抗差分功率分析。中：加密硬件和嵌入式系统。施普林格柏林海德堡出版社，1999年，第292-302页<http://link.springer.com/chapter/10.1007/3-540-48059-5_25>
 *
 * [3] 赫达布、穆斯塔法、皮内尔、皮埃尔和布恩埃托、卢锡安。一种使ECC抵抗侧信道攻击的梳状方法。IACR Cryptology ePrint Archive，2004年，第2004卷，第342页<http://eprint.iacr.org/2004/342.pdf>
 *
 * [4] Certicom研究。SEC 2：推荐的椭圆曲线域参数<http://www.secg.org/sec2-v2.pdf>
 *
 * [5] 汉森、达雷尔、梅内斯、阿尔弗雷德·J、凡斯通、斯科特。椭圆曲线加密指南。
 *
 * [6] 数字签名标准（DSS），FIPS 186-4<http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf>
 *
 * [7] 用于传输层安全（TLS）的椭圆曲线加密（ECC）密码套件，RFC 4492<https://tools.ietf.org/search/rfc4492>
 *
 * [8] <http://www.hyperelliptic.org/EFD/g1p/auto-shortw-jacobian.html>
 *
 * [9] 亨利·科恩。计算代数数论课程。施普林格科学与商业媒体，2000年8月1日
 */

#ifndef MBEDTLS_ECP_INTERNAL_H
#define MBEDTLS_ECP_INTERNAL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_ECP_INTERNAL_ALT)

/**
 * \brief指示椭圆曲线点模块扩展是否可以处理该组。
 *
 * \param grp指向将作为加密计算基础的椭圆曲线组的指针。
 *
 * \如果成功，则返回非零。
 */
unsigned char mbedtls_internal_ecp_grp_capable( const mbedtls_ecp_group *grp );

/**
 * \brief初始化椭圆曲线点模块扩展。
 *
 *                  如果mbedtls_internal_ecp_grp_able为组返回true，则该函数必须能够为其初始化模块。
 *
 *                  该模块可以是加密硬件加速器的驱动程序，这可以是一个初始化功能。
 *
 * \param grp指向模块需要初始化的组的指针。
 *
 * \如果成功，则返回0。
 */
int mbedtls_internal_ecp_init( const mbedtls_ecp_group *grp );

/**
 * \brief释放并释放椭圆曲线点模块扩展。
 *
 * \param grp指向为其初始化模块的组的指针。
 */
void mbedtls_internal_ecp_free( const mbedtls_ecp_group *grp );

#if defined(MBEDTLS_ECP_SHORT_WEIERSTRASS_ENABLED)

#if defined(MBEDTLS_ECP_RANDOMIZE_JAC_ALT)
/**
 * \简单随机化jacobian坐标：（X，Y，Z）->（l^2 X，l^3 Y，lZ）用于随机l。
 *
 * \param grp指向表示曲线的组的指针。
 *
 * \param pt要随机化的曲线上的点，用雅可比坐标给出。
 *
 * \param f_rng指向随机数生成器的函数指针。
 *
 * \param p_rng指向随机数生成器状态的指针。
 *
 * \如果成功，则返回0。
 */
int mbedtls_internal_ecp_randomize_jac( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *pt, int (*f_rng)(void *, unsigned char *, size_t),
        void *p_rng );
#endif

#if defined(MBEDTLS_ECP_ADD_MIXED_ALT)
/**
 * \简单加法：R=P+Q，混合仿射雅可比坐标。
 *
 *                  Q的坐标必须归一化（=仿射），但P的坐标不需要归一化。R没有归一化。
 *
 *                  此函数仅用作ecp_mul_comb（）的子例程。
 *
 *                  特殊情况：（1）P或Q为零，（2）R为零，，（3）P==Q。这些情况都不能作为ecp_mul_comb（）中的中间步骤发生：
 *                      -在每个步骤中，P、Q和R是基点的倍数，因数小于其阶数，因此它们都不是零；
 *                      -Q是基点的奇数倍，P是偶数倍，这是由于在修改的梳状方法中选择了预计算的点。因此，这些案件的分支机构不会泄露秘密信息。
 *
 *                  我们接受Q->Z未设置（将内存保存在表中）为1。
 *
 *                  现场作业成本（如果由[5]3.22:1A:=8M+3S完成）
 *
 * \param grp指向表示曲线的组的指针。
 *
 * \param R指向保存结果的点结构的指针。
 *
 * \param P指向第一个被加数的指针，用雅可比坐标给出
 *
 * \param Q指向第二个被加数的指针，用仿射坐标给出。
 *
 * \如果成功，则返回0。
 */
int mbedtls_internal_ecp_add_mixed( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *R, const mbedtls_ecp_point *P,
        const mbedtls_ecp_point *Q );
#endif

/**
 * \短点加倍R=2P，雅可比坐标。
 *
 *                  成本：1D:=3M+4S（A==0）4M+4S（A==-3）3M+6S+1a否则，当实施基于[8]中的“dbl-1998-cmo-2”倍增公式时，并且当曲线参数A为{0，-3}之一时，应用标准优化。
 *
 * \param grp指向表示曲线的组的指针。
 *
 * \param R指向保存结果的点结构的指针。
 *
 * \param P指向必须加倍的点的指针，用雅可比坐标给出。
 *
 * \如果成功，则返回0。
 */
#if defined(MBEDTLS_ECP_DOUBLE_JAC_ALT)
int mbedtls_internal_ecp_double_jac( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *R, const mbedtls_ecp_point *P );
#endif

/**
 * \brief规范化（指向）点数组的jacobian坐标。
 *
 *                  使用蒙哥马利的技巧仅执行一个反演模式P，成本为：1N（t）：=1I+（6t-3）M+1S（例如参见[9]中的算法10.3.4）
 *
 *                  此函数仅用作ecp_mul_comb（）的子例程。
 *
 *                  警告：如果其中一个点为零，则失败（返回错误）！这不应该发生，请参见ecp_mul_comb（）中的w选项。
 *
 * \param grp指向表示曲线的组的指针。
 *
 * \param T指向要规范化的点的指针数组。
 *
 * \param t_len数组中的元素数。
 *
 * \如果成功，则返回0，如果其中一个点为零，则返回错误。
 */
#if defined(MBEDTLS_ECP_NORMALIZE_JAC_MANY_ALT)
int mbedtls_internal_ecp_normalize_jac_many( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *T[], size_t t_len );
#endif

/**
 * \简略归一化雅可比坐标，使Z==0||Z==1。
 *
 *                  按照[5]3.2.1进行的现场作业成本：1N:=1I+3M+1S
 *
 * \param grp指向表示曲线的组的指针。
 *
 * \param pt指向要规范化的点的指针。这是一个输入/输出参数。
 *
 * \如果成功，则返回0。
 */
#if defined(MBEDTLS_ECP_NORMALIZE_JAC_ALT)
int mbedtls_internal_ecp_normalize_jac( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *pt );
#endif

#endif /* MBEDTLS_ECP_SHORT_WEIERSTRASS_ENABLED */

#if defined(MBEDTLS_ECP_MONTGOMERY_ENABLED)

#if defined(MBEDTLS_ECP_DOUBLE_ADD_MXZ_ALT)
int mbedtls_internal_ecp_double_add_mxz( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *R, mbedtls_ecp_point *S, const mbedtls_ecp_point *P,
        const mbedtls_ecp_point *Q, const mbedtls_mpi *d );
#endif

/**
 * \简单随机化投影x/z坐标：（x，z）->（l x，l z）用于随机l
 *
 * \param grp指向表示曲线的组的指针
 *
 * \param P用投影坐标给出的要随机化的曲线上的点。这是一个输入/输出参数。
 *
 * \param f_rng指向随机数生成器的函数指针
 *
 * \param p_rng指向随机数生成器状态的指针
 *
 * \如果成功，则返回0
 */
#if defined(MBEDTLS_ECP_RANDOMIZE_MXZ_ALT)
int mbedtls_internal_ecp_randomize_mxz( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *P, int (*f_rng)(void *, unsigned char *, size_t),
        void *p_rng );
#endif

/**
 * \brief规格化蒙哥马利x/z坐标：x=x/z，z=1。
 *
 * \param grp指向表示曲线的组的指针
 *
 * \param P指向要标准化的点的指针。这是一个输入/输出参数。
 *
 * \如果成功，则返回0
 */
#if defined(MBEDTLS_ECP_NORMALIZE_MXZ_ALT)
int mbedtls_internal_ecp_normalize_mxz( const mbedtls_ecp_group *grp,
        mbedtls_ecp_point *P );
#endif

#endif /* MBEDTLS_ECP_MONTGOMERY_ENABLED */

#endif /* MBEDTLS_ECP_INTERNAL_ALT */

#endif /* ecp_internal.h*/


