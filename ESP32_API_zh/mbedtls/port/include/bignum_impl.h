#ifndef _ESP_BIGNUM_H_
#define _ESP_BIGNUM_H_

#include <mbedtls/bignum.h>
#include <stdbool.h>

/* 使用蒙哥马利指数（HAC 14.94）计算X^Y mod M，这对于某些目标可能更快。ESP32上对模幂运算的硬件加速支持对于公钥操作来说很慢，因此请改用蒙哥马利幂运算。
*/
#if CONFIG_IDF_TARGET_ESP32
#define ESP_MPI_USE_MONT_EXP
#endif

/**
 * @brief 启用MPI硬件并获取锁
 *
 */
void esp_mpi_enable_hardware_hw_op( void );

/**
 * @brief 禁用MPI硬件并释放锁
 *
 */
void esp_mpi_disable_hardware_hw_op( void );

/**
 * @brief 计算在硬件中表示输入单词所需的单词数
 *
 * @param words 要表示的单词数
 *
 * @return size_t所需字数
 */
size_t esp_mpi_hardware_words(size_t words);

/**
 * @brief 在硬件中启动（X*Y）Mod M计算。Rinv和M_prime需要在软件中预先计算。
 *
 */
void esp_mpi_mul_mpi_mod_hw_op(const mbedtls_mpi *X, const mbedtls_mpi *Y, const mbedtls_mpi *M, const mbedtls_mpi *Rinv, mbedtls_mpi_uint Mprime, size_t hw_words);

/**
 * @brief 在硬件中开始（X*Y）计算。
 *
 */
void esp_mpi_mul_mpi_hw_op(const mbedtls_mpi *X, const mbedtls_mpi *Y, size_t num_words);

/**
 * @brief （X*Y）的特殊情况，其中我们使用硬件蒙哥马利模乘法来计算A或B大于2048位的结果，因此不能使用标准乘法方法。
 *
 */
void esp_mpi_mult_mpi_failover_mod_mult_hw_op(const mbedtls_mpi *X, const mbedtls_mpi *Y, size_t num_words);

/**
 * @brief 读出上一次计算的结果。
 *
 */
void esp_mpi_read_result_hw_op(mbedtls_mpi *Z, size_t z_words);

#ifdef ESP_MPI_USE_MONT_EXP
/**
 * @brief 在硬件中启动蒙哥马利乘法计算
 *
 */
int esp_mont_hw_op(mbedtls_mpi* Z, const mbedtls_mpi* X, const mbedtls_mpi* Y, const mbedtls_mpi* M,
                mbedtls_mpi_uint Mprime,
                size_t hw_words,
                bool again);

#else

/**
 * @brief 在硬件中启动（X^Y）Mod M计算。Rinv和M_prime需要在软件中预先计算。
 *
 */
void esp_mpi_exp_mpi_mod_hw_op(const mbedtls_mpi *X, const mbedtls_mpi *Y, const mbedtls_mpi *M, const mbedtls_mpi *Rinv, mbedtls_mpi_uint Mprime, size_t hw_words);

#endif //ESP_MPI_USE_MONT_EXP

#endif

