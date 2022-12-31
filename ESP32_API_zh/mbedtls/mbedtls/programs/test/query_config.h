/*
 *  从config.h查询Mbed TLS编译时配置
 *
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef MBEDTLS_PROGRAMS_TEST_QUERY_CONFIG_H
#define MBEDTLS_PROGRAMS_TEST_QUERY_CONFIG_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

/** 检查给定的配置符号是否已启用。
 *
 * \param config要查询的符号（例如“MBEDTLS_RSA_C”）。\如果符号是在编译时定义的（在MBEDTLS_CONFIG_FILE或CONFIG.h中），则返回\c 0，否则返回\c 1。
 *
 * \注意此函数在`programs/test/query_config中定义。c”，由“scripts/generate_query_config.pl”自动生成。
 */
int query_config( const char *config );

#endif /* MBEDTLS_PROGRAMS_TEST_QUERY_CONFIG_H */

