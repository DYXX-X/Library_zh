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

int mbedtls_test_platform_setup( void );
void mbedtls_test_platform_teardown( void );

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

#endif /* TEST_HELPERS_H */

