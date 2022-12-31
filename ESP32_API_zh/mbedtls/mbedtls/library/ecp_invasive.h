/**
 * \文件ecp_invasive.h
 *
 * \简要ECP模块：仅用于侵入性测试的接口。
 *
 * 本文件中的接口仅用于测试目的。它们不应在库集成中可用，除非构建库进行测试。
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
#ifndef MBEDTLS_ECP_INVASIVE_H
#define MBEDTLS_ECP_INVASIVE_H

#include "common.h"
#include "mbedtls/bignum.h"
#include "mbedtls/ecp.h"

#if defined(MBEDTLS_TEST_HOOKS) && defined(MBEDTLS_ECP_C)

#if defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED) ||   \
    defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) ||   \
    defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
/* 前提条件：
 *   -位是64的倍数或224
 *   -c为-1或-2
 *   -0<=N<2^位
 *   -N有位加一个肢体的空间
 *
 * 行为：将N设置为c 2^bits+old_value_of_N。
 */
void mbedtls_ecp_fix_negative( mbedtls_mpi *N, signed char c, size_t bits );
#endif

#if defined(MBEDTLS_ECP_MONTGOMERY_ENABLED)
/** 在蒙哥马利曲线（Curve25519或Curve448）上生成私钥。
 *
 * 此函数实现[Curve25519]第5页和[Curve448]中指定的密钥集的密钥生成。结果值具有屏蔽的低位，但不一定是规范的。
 *
 * \注释-[曲线25519]http://cr.yp.to/ecdh/curve25519-20060209.pdf
 *                  -【RFC7748】https://tools.ietf.org/html/rfc7748
 *
 * \p high_bit要生成的密钥的高位的位置。对于Curve25519，这是密钥的比特大小减去1:254，对于Curve448，这是447。\param d随机生成的密钥。这是一个大小正好为\p n_bits+1位的数字，按照[Curve25519]和[RFC7748]§5中的规定屏蔽最低有效位。\param f_rng rng函数。\param p_rng要传递给\p f_rng的rng上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_ERROR_ECP_xxx或MBEDTLS_ERROR_MPI_xxx。
 */
int mbedtls_ecp_gen_privkey_mx( size_t n_bits,
                                mbedtls_mpi *d,
                                int (*f_rng)(void *, unsigned char *, size_t),
                                void *p_rng );

#endif /* MBEDTLS_ECP_MONTGOMERY_ENABLED */

#endif /* MBEDTLS_TEST_HOOKS && MBEDTLS_ECP_C */

#endif /* MBEDTLS_ECP_INVASIVE_H */

