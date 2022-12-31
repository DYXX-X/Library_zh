/**
 * \文件版本.h
 *
 * \简要运行时版本信息
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
 * 这组编译时定义和运行时变量可用于确定所使用的mbed TLS库的版本号。
 */
#ifndef MBEDTLS_VERSION_H
#define MBEDTLS_VERSION_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

/**
 * 版本号x.y.z分为三部分。主要、次要、修补程序级别
 */
#define MBEDTLS_VERSION_MAJOR  2
#define MBEDTLS_VERSION_MINOR  25
#define MBEDTLS_VERSION_PATCH  0

/**
 * 单个版本号具有以下结构：MMNNPP00主要版本|次要版本|修补程序版本
 */
#define MBEDTLS_VERSION_NUMBER         0x02190000
#define MBEDTLS_VERSION_STRING         "2.25.0"
#define MBEDTLS_VERSION_STRING_FULL    "mbed TLS 2.25.0"

#if defined(MBEDTLS_VERSION_C)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 获取版本号。
 *
 * \return构建的版本号，格式为MMNNPP00（主要、次要、补丁）。
 */
unsigned int mbedtls_version_get_number( void );

/**
 * 获取版本字符串（“x.y.z”）。
 *
 * \param string将接收值的字符串。（大小应至少为9字节）
 */
void mbedtls_version_get_string( char *string );

/**
 * 获取完整版本字符串（“mbed TLS x.y.z”）。
 *
 * \param string将接收值的字符串。mbed TLS版本字符串将在MOST处使用18个字节，包括终止空字节。（因此，缓冲区至少应为18个字节才能接收此版本字符串）。
 */
void mbedtls_version_get_string_full( char *string );

/**
 * \brief检查此mbed TLS二进制文件中是否编译了对功能的支持。这允许您在运行时查看库是在多线程支持或不支持多线程的情况下编译的。
 *
 * \注意，仅检查config.h中“系统支持”、“mbed TLS模块”和“mbed TLS功能支持”部分中的定义
 *
 * \param feature要检查的定义的字符串（例如“MBEDTLS_AES_C”）
 *
 * \如果特征存在，则返回0，
 *                  -1，如果该功能不存在，并且
 *                  -如果未在中编译对功能检查的整体支持，则为2。
 */
int mbedtls_version_check_feature( const char *feature );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_VERSION_C */

#endif /* 版本.h*/

