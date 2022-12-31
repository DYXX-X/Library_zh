/**
 * \文件助手.h
 *
 * \brief此文件包含用于测试的助手函数的原型。
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

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_THREADING_C) && defined(MBEDTLS_THREADING_PTHREAD) && \
    defined(MBEDTLS_TEST_HOOKS)
#define MBEDTLS_TEST_MUTEX_USAGE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_fprintf    fprintf
#define mbedtls_snprintf   snprintf
#define mbedtls_calloc     calloc
#define mbedtls_free       free
#define mbedtls_exit       exit
#define mbedtls_time       time
#define mbedtls_time_t     time_t
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#include <stddef.h>
#include <stdint.h>

#if defined(MBEDTLS_BIGNUM_C)
#include "mbedtls/bignum.h"
#endif

typedef enum
{
    MBEDTLS_TEST_RESULT_SUCCESS = 0,
    MBEDTLS_TEST_RESULT_FAILED,
    MBEDTLS_TEST_RESULT_SKIPPED
} mbedtls_test_result_t;

typedef struct
{
    mbedtls_test_result_t result;
    const char *test;
    const char *filename;
    int line_no;
    unsigned long step;
    char line1[76];
    char line2[76];
#if defined(MBEDTLS_TEST_MUTEX_USAGE)
    const char *mutex_usage_error;
#endif
}
mbedtls_test_info_t;
extern mbedtls_test_info_t mbedtls_test_info;

int mbedtls_test_platform_setup( void );
void mbedtls_test_platform_teardown( void );

/**
 * \简要记录当前测试用例为失败。
 *
 *                  此函数可以直接调用，但通常通过宏调用，如TEST_ASSERT、TEST_EQUAL、PSA_SSERT等。。。
 *
 * \注意：如果测试用例已经被标记为失败，那么再次调用“mbedtls_test_fail（）”将不会覆盖有关失败的任何先前信息。
 *
 * \param test失败或失败断言的描述。这必须是字符串文本。\param line_no发生故障的行号。\param filename失败发生的文件名。
 */
void mbedtls_test_fail( const char *test, int line_no, const char* filename );

/**
 * \brief将当前测试用例记录为跳过。
 *
 *                  此函数可以直接调用，但通常通过TEST_ASSUME宏调用。
 *
 * \param test导致跳过测试用例的假设的描述。这必须是字符串文本。\param line_no跳过测试用例的行号。\param filename跳过测试用例的文件名。
 */
void mbedtls_test_skip( const char *test, int line_no, const char* filename );

/**
 * \brief设置故障报告的测试步骤编号。
 *
 *              如果测试失败，调用此函数除了显示行号和文件名外，还显示“步骤NNN”。通常，“步数”是for循环的索引，但它可以是您想要的任何值。
 *
 * \param step要报告的步骤号。
 */
void mbedtls_test_set_step( unsigned long step );

/**
 * \brief将mbedtls_test_info重置为就绪/启动状态。
 */
void mbedtls_test_info_reset( void );

/**
 * \如果两个整数具有不同的值，则将当前测试用例记录为失败。
 *
 *                  此函数通常通过宏#TEST_EQUAL调用。
 *
 * \param test失败或失败断言的描述。这必须是字符串文本。这通常具有“EXPR1==EXPR2”的形式，其中EXPR1的值为1，EXPR2的值为2。\param line_no故障发生的行号。\param filename失败发生的文件名。\param value1要比较的第一个值。\param value2要比较的第二个值。
 *
 * \如果值相等，则返回\c 1，否则返回\c 0。
 */
int mbedtls_test_equal( const char *test, int line_no, const char* filename,
                        unsigned long long value1, unsigned long long value2 );

/**
 * \brief此函数对数据的十六进制表示进行解码。
 *
 * \注意输出缓冲区可以与输入缓冲区相同。对于输入和输出缓冲区的任何其他重叠，行为是未定义的。
 *
 * \param obuf输出缓冲区。\param obufmax大小（字节数）。\param ibuf输入缓冲区。\param len在\p obuf中写入的无符号字符数。此值不能为空。
 *
 * \成功时返回\c 0。\如果输出缓冲区太小或输入字符串不是有效的十六进制表示，则返回\c-1。
 */
int mbedtls_test_unhexify( unsigned char *obuf, size_t obufmax,
                           const char *ibuf, size_t *len );

void mbedtls_test_hexify( unsigned char *obuf,
                          const unsigned char *ibuf,
                          int len );

/**
 * 分配缓冲区并将其归零。
 *
 * 如果大小为零，则返回指向已归零的1字节缓冲区的指针。
 *
 * 为方便起见，如果分配失败，将死亡。
 */
unsigned char *mbedtls_test_zero_alloc( size_t len );

/**
 * 从十六进制数据分配并填充缓冲区。
 *
 * 缓冲区的大小完全符合需要。这允许在valgrind下运行测试套件时检测缓冲区溢出（包括溢出）。
 *
 * 如果大小为零，则返回指向已归零的1字节缓冲区的指针。
 *
 * 为方便起见，如果分配失败，将死亡。
 */
unsigned char *mbedtls_test_unhexify_alloc( const char *ibuf, size_t *olen );

int mbedtls_test_hexcmp( uint8_t * a, uint8_t * b,
                         uint32_t a_len, uint32_t b_len );

#if defined(MBEDTLS_CHECK_PARAMS)

typedef struct
{
    const char *failure_condition;
    const char *file;
    int line;
}
mbedtls_test_param_failed_location_record_t;

/**
 * \brief获取上次调用mbedtls_test_param_failed（）的位置记录。
 *
 * \注意，在下一次调用mbedtls_test_param_failed_check_expected_call（）或取消它的mbedtls_param_ffailed（）之前，将设置并激活调用预期。
 */
void mbedtls_test_param_failed_get_location_record(
         mbedtls_test_param_failed_location_record_t *location_record );

/**
 * \brief声明应调用mbedtls_param_failed（）。
 *
 * \注意，在下一次调用mbedtls_test_param_failed_check_expected_call（）或取消它的mbedtls_param_ffailed之前，将设置并激活调用预期。
 */
void mbedtls_test_param_failed_expect_call( void );

/**
 * \brief检查是否按预期调用了mbedtls_param_failed（）。
 *
 * \注意：检查在上次调用mbedtls_test_param_failed_expect_call（）和调用此函数之间是否调用了mbedtls_param_ffailed（）。
 *
 * \return \c 0自从上次调用mbedtls_param_failed_expect_call（）以来，已调用mbedtls _param_ffailed（）。\c-1否则。
 */
int mbedtls_test_param_failed_check_expected_call( void );

/**
 * \brief获取持有mbedtls_param_failed（）用于执行长跳转的执行状态信息的jmp_buf类型对象的地址。
 *
 * \注意：如果在前面没有对mbedtls_test_param_failed_expect_call（）的调用的情况下，不需要对mbedtls _param_ffailed（）进行调用，则mbedtls_param_fFailed（）将尝试将执行恢复到存储在jmp_buf对象中的状态，jmp_buff对象的地址由当前函数返回。
 *
 * \注意：此函数旨在提供setjmp（）函数的参数，以设置mbedtls_param_failed（）在必要时应长跳转的位置。预计将用作：
 *
 *          setjmp（mbedtls_test_param_failed_get_state_buf（））。
 *
 * \注意：返回值的类型不是jmp_buf，因为jmp_buf是数组类型（C规范），函数不能返回数组类型。
 *
 * \注意返回值的类型不是jmp_buf*，因为setjmp（）无法使用返回值，因为其参数的类型是jmp_buf。
 *
 * \return持有mbedtls_param_failed（）用于执行长跳转的执行状态信息的jmp_buf类型对象的地址。
 */
void* mbedtls_test_param_failed_get_state_buf( void );

/**
 * \brief重置mbedtls_param_failed（）用于执行长跳转的执行状态。
 *
 * \注意：如果在前面没有对mbedtls_test_param_failed_expect_call（）的调用的情况下，不需要调用mbedtls_param_ffailed（），则mbedtls.param_failed（）将尝试恢复此函数重置的执行状态。
 *
 * \注意：当状态不再相关时，建议重置执行状态。这样，对mbedtls_param_failed（）的意外调用将不会触发具有未定义行为的长跳转，而是触发相当错误的长跳转。
 */
void mbedtls_test_param_failed_reset_state( void );
#endif /* MBEDTLS_CHECK_PARAMS */

#if defined(MBEDTLS_PSA_CRYPTO_C) && defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
#include "test/fake_external_rng_for_test.h"
#endif

#if defined(MBEDTLS_TEST_MUTEX_USAGE)
/**永久激活互斥使用验证框架。请参见threading_helpers。c获取信息。*/
void mbedtls_test_mutex_usage_init( void );

/**在执行测试用例后调用此函数以检查互斥锁使用错误。*/
void mbedtls_test_mutex_usage_check( void );
#endif /* MBEDTLS_TEST_MUTEX_USAGE */

#if defined(MBEDTLS_TEST_HOOKS)
/**
 * \简要检查只有纯高级错误代码与纯低级错误代码组合，否则生成的错误代码将被损坏。
 *
 * \注意：高级和低级错误代码不能大于零，但可以为零。如果一个错误代码为零，则即使两个代码都为零，也会返回另一个错误码。
 *
 * \注意：如果检查失败，则当前正在运行的测试失败。
 */
void mbedtls_test_err_add_check( int high, int low,
                                 const char *file, int line);
#endif

#if defined(MBEDTLS_BIGNUM_C)
/** 从字符串中读取MPI。
 *
 * 与mbedtls_mpi_read_string（）类似，但根据字符串中的位数调整结果bignum的大小。特别是，为空字符串构造一个具有0个分支的bignum，如果字符串具有足够多的前导0位，则构造一个带有前导0个分支。
 *
 * 这一点很重要，因为“0（null）”和“0（1分支）”以及“前导零”测试用例可以实现它们所声称的功能。
 *
 * \param[out]X要填充的MPI对象。必须对其进行初始化。\param radix基数（2到16）。\param[in]s要读取的以空结尾的字符串。
 *
 * \成功时返回\c 0，否则返回\c MBEDTLS_error_MPI_xxx错误代码。
 */
/* 由于库完全具有所需的行为，所以这是微不足道的。*/
int mbedtls_test_read_mpi( mbedtls_mpi *X, int radix, const char *s );
#endif /* MBEDTLS_BIGNUM_C */

#endif /* TEST_HELPERS_H */

