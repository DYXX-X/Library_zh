/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include_next "mbedtls/bignum.h"
#include "sdkconfig.h"

/**
 * 这是主mbedtls/bignum.h的包装器。该包装器提供了一些额外的仅限ESP32的函数。
 *
 * 这是因为我们没有像设置AES、SHA等那样设置MBEDTLS_BIGNUM_ALT。因为我们仍然使用大部分BIGNUM。h实现，只需替换一些硬件加速功能（参见esp_config.h中的MBEDTLS_MPI_EXP_MOD_ALT和MBEDTLS_MPI_MUL_MPI_ALT）。
 *
 * @note 与esp32/hwcrypto中的其他硬件加速器支持函数不同，在没有mbedTLS的情况下，没有通用的“hwcrypto/bignum.h”标头来使用这些函数。原因是所有函数实现都强烈依赖于mbedTLS MPI实现。
 */

/**
 * @brief 锁定对RSA Accelerator的访问（MPI/bignum操作）
 *
 * RSA Accelerator硬件单元一次只能由一个用户使用。
 *
 * @note 此函数是非递归的（不要在同一任务中调用它两次。）
 *
 * @note 如果您使用的是mbedTLS bignum，则不需要调用它。h API或esp_mpi_xxx函数。只有当您想调用ROM RSA函数或直接访问寄存器时，才需要此函数。
 *
 */
void esp_mpi_acquire_hardware(void);

/**
 * @brief 解锁对RSA Accelerator的访问（MPI/bignum操作）
 *
 * 每次调用esp_mpi_acquire_hardware（）都必须调用一次。
 *
 * @note 如果您使用的是mbedTLS bignum，则不需要调用它。h API或esp_mpi_xxx函数。只有当您想调用ROM RSA函数或直接访问寄存器时，才需要此函数。
 */
void esp_mpi_release_hardware(void);

#if CONFIG_MBEDTLS_HARDWARE_MPI

/* @brief MPI模块复用功能
 *
 * 使用MPI硬件加速计算Z=（X*Y）mod M。
 *
 * 这不是标准mbedTLS bignum API的一部分。
 *
 * @note 所有X、Y和Z的长度应小于4096位，否则将返回错误。
 *
 * @param Z 应使用mbedtls_mpi_init（）预初始化结果bignum。
 * @param X 第一个乘法参数。
 * @param Y 第二个乘法参数。
 * @param M 结果的模量值。
 *
 * @return 成功时为0，失败时为mbedTLS MPI错误代码。
 */
int esp_mpi_mul_mpi_mod(mbedtls_mpi *Z, const mbedtls_mpi *X, const mbedtls_mpi *Y, const mbedtls_mpi *M);

#if CONFIG_MBEDTLS_LARGE_KEY_SOFTWARE_MPI

/**
 * @brief          执行滑动窗口求幂：X=a^E mod N
 *
 * @param X        目标MPI。这必须指向已初始化的MPI。
 * @param A        求幂的基数。这必须指向已初始化的MPI。
 * @param E        指数MPI。这必须指向已初始化的MPI。
 * @param N        模块化缩减的基础。这必须指向已初始化的MPI。
 * @param _RR      一个仅依赖于\p N的帮助器MPI，它可用于为相同的\p N值加速多个模幂运算。这可能是空的。如果不是空，则必须指向已初始化的MPI。
 *
 * @return         \c 0如果成功。
 * @return         #如果内存分配失败，则MBEDTLS_ERROR_MPI_ALLOC_FAILED。
 * @return         #如果\c N为负或偶数，或\c E为负，则MBEDTLS_ERROR_MPI_BAD_INPUT_DATA。
 * @return         另一个关于不同类型故障的负面错误代码。
 *
 */
int mbedtls_mpi_exp_mod_soft(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RR);

#endif // CONFIG_MBEDTLS_LARGE_KEY_SOFTWARE_MPI

#endif // CONFIG_MBEDTLS_HARDWARE_MPI

