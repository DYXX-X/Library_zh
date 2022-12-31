/**
 * \文件rsa_internal.h
 *
 * \简短的上下文无关RSA帮助函数
 *
 *  本模块声明一些与RSA相关的帮助函数在实现RSA接口时非常有用。这些函数是在一个单独的编译单元中提供的，以便于替代RSA实现的设计者在自己的代码中使用它们，因为人们认为它们提供的功能对于大多数完整的实现都是必要的。
 *
 *  没有提供自己的替代RSA实现的Mbed TLS的最终用户不应该直接使用这些函数，而应该只使用RSA.h中声明的函数。
 *
 *  此模块提供的接口将通过Mbed TLS的LTS（长期支持）分支进行维护，但可能会发生变化，必须视为库的内部接口。
 *
 *  有两类助手函数：
 *
 *  （1） 参数生成助手。这些是：
 *      -mbedtls_rsa_deduced_primes公司
 *      -mbedtls_rsa_deduce_private_exponent公司
 *      -mbedtls_rsa_deduce_crt这些函数中的每一个都采用一组核心rsa参数，并生成一些其他或crt相关的参数。
 *
 *  （2） 参数检查助手。这些是：
 *      -mbedtls_rsa_validate_param文件
 *      -mbedtls_rsa_validate_crt他们获取一组核心或crt相关的rsa参数并检查其有效性。
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
 *
 */

#ifndef MBEDTLS_RSA_INTERNAL_H
#define MBEDTLS_RSA_INTERNAL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/bignum.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \根据公钥N＝PQ和一对私钥和公钥计算RSA素模P、Q。
 *
 * \注意：这是一个不在RSA上下文中运行的“静态”帮助函数。替代实现不需要覆盖它。
 *
 * \param N RSA模N=PQ，其中P，Q将被找到\param E RSA公共指数\param D RSA私有指数\pparam P指向MPI的指针，成功时持有N的第一个素因子\param Q指向MPI，成功时拥有N的第二个素因子
 *
 * \返回
 *                 -如果成功，则为0。在这种情况下，P和Q构成N的因子分解。
 *                 -否则为非零错误代码。
 *
 * \注意：既没有检查P、Q是素数，也没有检查D、E是P-1和Q-1的模逆。为此，请使用助手函数\c mbedtls_rsa_validate_params。
 *
 */
int mbedtls_rsa_deduce_primes( mbedtls_mpi const *N, mbedtls_mpi const *E,
                               mbedtls_mpi const *D,
                               mbedtls_mpi *P, mbedtls_mpi *Q );

/**
 * \根据素数模和公钥计算RSA私有指数。
 *
 * \注意：这是一个不在RSA上下文中运行的“静态”帮助函数。替代实现不需要覆盖它。
 *
 * \param P RSA模的第一个素因子\param Q RSA模的第二个素因子\param E RSA公共指数\param D成功时保存私有指数的MPI指针。
 *
 * \返回
 *                 -如果成功，则为0。在这种情况下，D被设置为E同时模P-1和Q-1的模逆。
 *                 -否则为非零错误代码。
 *
 * \注意：此函数不检查P和Q是否为素数。
 *
 */
int mbedtls_rsa_deduce_private_exponent( mbedtls_mpi const *P,
                                         mbedtls_mpi const *Q,
                                         mbedtls_mpi const *E,
                                         mbedtls_mpi *D );


/**
 * \简要生成RSA-CTR参数
 *
 * \注意：这是一个不在RSA上下文中运行的“静态”帮助函数。替代实现不需要覆盖它。
 *
 * \param P N的第一个素因子\param Q N的第二个素因子\param D RSA私有指数\param DP D模P-1的输出变量\param DQ D模Q-1的输出变量\param QP Q模P的模逆的输出变量。
 *
 * \成功时返回0，否则返回非零错误代码。
 *
 * \注意：此函数不检查P、Q是否为素数以及D是否为有效的私有指数。
 *
 */
int mbedtls_rsa_deduce_crt( const mbedtls_mpi *P, const mbedtls_mpi *Q,
                            const mbedtls_mpi *D, mbedtls_mpi *DP,
                            mbedtls_mpi *DQ, mbedtls_mpi *QP );


/**
 * \简要检查核心RSA参数的有效性
 *
 * \注意：这是一个不在RSA上下文中运行的“静态”帮助函数。替代实现不需要覆盖它。
 *
 * \param N RSA模数N=PQ \param P N的第一个素因子\param Q N的第二个素因子\param D RSA私有指数\param E RSA公共指数\pparam f_rng PRNG用于素性检查，或NULL \param P_rng PRNG上下文用于f_rng，或NULL
 *
 * \返回
 *                 -如果提供了所有相关参数，则满足以下条件：
 *                    -如果f_rng！=空（%）
 *                    -如果f_rng！=空（%）
 *                    - 1 < N = P * Q
 *                    - 1 < D, E < N
 *                    -D和E是模P-1和Q-1（%）的模逆。只有在定义了MBEDTLS_GENPRIME的情况下才能实现。
 *                 -否则为非零错误代码。
 *
 * \注意：该函数只能与一组受限制的参数一起使用，以执行特定的检查。E、 例如，用（-，P，-，-）和PRNG调用它相当于对P进行素性检查。
 */
int mbedtls_rsa_validate_params( const mbedtls_mpi *N, const mbedtls_mpi *P,
                                 const mbedtls_mpi *Q, const mbedtls_mpi *D,
                                 const mbedtls_mpi *E,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng );

/**
 * \简要检查RSA CRT参数的有效性
 *
 * \注意：这是一个不在RSA上下文中运行的“静态”帮助函数。替代实现不需要覆盖它。
 *
 * \param P RSA模的第一个素因子\param Q RSA模的第二个素因子\param D RSA私有指数\param DP MPI检查D模P-1 \param DQ MPI检查D模块P-1 \pparam QP MPI检查Q模P的模逆。
 *
 * \返回
 *                 -如果满足以下条件，则为0：
 *                    -D=如果P、D、DP！=无效的
 *                    -Q=如果P、D、DQ！=无效的
 *                    -QP=Q^-1模P，如果P，Q，QP！=无效的
 *                 -如果检查失败，则为\c MBEDTLS_ERROR_RSA_KEY_CHECK_FAILED，如果某些MPI计算失败，则可能包括\c MBEDTLS_ERR_MPI_XXX。
 *                 -\c如果提供的数据不足以检查DP、DQ或QP，则MBEDTLS_ERROR_RSA_BAD_INPUT_DATA。
 *
 * \注意：该函数只能与一组受限制的参数一起使用，以执行特定的检查。E、 例如，使用参数（P，-，D，DP，-，-）调用它将检查DP=D mod P-1。
 */
int mbedtls_rsa_validate_crt( const mbedtls_mpi *P,  const mbedtls_mpi *Q,
                              const mbedtls_mpi *D,  const mbedtls_mpi *DP,
                              const mbedtls_mpi *DQ, const mbedtls_mpi *QP );

#ifdef __cplusplus
}
#endif

#endif /* rsa_内部.h*/

