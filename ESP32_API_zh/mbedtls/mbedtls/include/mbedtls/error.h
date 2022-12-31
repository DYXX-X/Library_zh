/**
 * \文件错误.h
 *
 * \字符串转换的简短错误
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
#ifndef MBEDTLS_ERROR_H
#define MBEDTLS_ERROR_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

/**
 * 错误代码布局。
 *
 * 目前，我们尝试将所有错误代码保持在16位有符号整数的负空间内，以支持所有平台（-0x0001--0x7FFF）。此外，如果可能的话，我们想提供两层错误信息。
 *
 * 为此，错误代码按以下方式分段：
 *
 * 16位错误代码位分段
 *
 * 1位-未使用（符号位）3位-高级模块ID 5位-模块相关错误代码7位-低级模块错误
 *
 * 由于历史原因，低级错误代码分为偶数和奇数，偶数代码首先分配，-1保留用于其他错误。
 *
 * 低级模块错误（0x0002-0x007E、0x0001-0x007F）
 *
 * 模块编号代码分配错误2 0x006E 0x0001 MPI 7 0x0002-0x0010 GCM 3 0x0012-0x0014 0x0013-0x0013 BLOWFISH 3 0x0016-0x0018 0x0017-0x0017 THREADING 3 0x001A-0x001E AES 5 0x0020-0x0022 0x0021-0x0025 CAMELLIA 3 0x0024-0x0026 0x0027-0x0027 XTEA 2 0x0028-0x0028 0x0029-0x0029 BASE64 2 0x002A-0x002C OID 1 0x002E-0x002E 0x000B-0x000B PADLOCK 1 0x0030-0x0030 DES 2 0x0032-0x0032 0x0033-0x0033CTR_DBRG 4 0x0034-0x003A ENTROPY 3 0x003C-0x0040 0x003D-0x003F NET 13 0x0042-0x0052 0x0043-0x0049 ARIA 4 0x0058-0x005E ASN1 7 0x0060-0x006C CMAC 1 0x007A-0x007A PBKDF2 1 0x007C-0x007C HMAC_DRBG 4 0x0003-0x0009 CCM 3 0x000D-0x0011 ARC4 1 0x0019-0x0019 MD2 1 0x002B-0x002B MD4 1 0x002D-0x002D MD5 1 0x002F-0x002F RIPEMD160 1 0x0031-0x0031 SHA1 0x0035-0x0035 0x0073-0x0073 SHA256 1 0x0037-0x00370x0074-0x0074 SHA512 1 0x0039-0x0039 0x0075-0x0075 CHACHA20 3 0x0051-0x0055 POLY1305 3 0x0057-0x005B CHACHAPOLY 2 0x0054-0x0056平台2 0x0070-0x0072
 *
 * 高级模块编号（3位-0x0…-0x7…）名称ID错误编号PEM 1 9 PKCS#12 1 4（从顶部开始）X509 2 20 PKCS5 2 4（从底部开始）DHM 3 11 PK 3 15（从顶部启动）RSA 4 11 ECP 4 10（从顶部起）MD 5 5 HKDF 5 1（从顶部）SSL 5 2（从0x5F00开始）CIPHER 6 8（从0x6080开始）SSL 6 24（从顶部，加上0x6000）SSL 7 32
 *
 * 模块相关错误代码（5位0x.00.-0xF8.）
 */

#ifdef __cplusplus
extern "C" {
#endif

/**一般性错误*/
#define MBEDTLS_ERR_ERROR_GENERIC_ERROR       -0x0001
/**这是库中的错误*/
#define MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED -0x006E

/**
 * \brief将高级和低级错误代码组合在一起。
 *
 *        mbedtls_error_add（）的包装宏。有关详细信息，请参见该函数。
 */
#define MBEDTLS_ERROR_ADD( high, low ) \
        mbedtls_error_add( high, low, __FILE__, __LINE__ )

#if defined(MBEDTLS_TEST_HOOKS)
/**
 * \在添加/合并两个错误代码之前调用了简短的测试钩子。仅在通过MBEDTLS_TEST_HOOKS启用侵入性测试时使用。
 */
extern void (*mbedtls_test_hook_error_add)( int, int, const char *, int );
#endif

/**
 * \brief将高级和低级错误代码组合在一起。
 *
 *        此函数可以直接调用，但通常通过#MBEDTLS_ERROR_ADD宏调用。
 *
 *        虽然零值不是负错误代码，但它仍然是错误代码（表示成功），可以与负错误代码或另一个零值组合。
 *
 * \注意：当通过#MBEDTLS_TEST_HOOKS启用侵入性测试时，也尝试调用\link MBEDTLS_TEST_hook_error_add\endlink。
 *
 * \param高级别错误代码。有关详细信息，请参阅error.h。\param低级别错误代码。有关详细信息，请参阅error.h。\发生此错误代码添加的param文件文件。\发生此错误代码添加的param行。
 */
static inline int mbedtls_error_add( int high, int low,
                                     const char *file, int line )
{
#if defined(MBEDTLS_TEST_HOOKS)
    if( *mbedtls_test_hook_error_add != NULL )
        ( *mbedtls_test_hook_error_add )( high, low, file, line );
#endif
    (void)file;
    (void)line;

    return( high + low );
}

/**
 * \brief将mbed TLS错误代码转换为字符串表示形式，必要时会截断Result，并始终包含终止的空字节。
 *
 * \param errnum错误代码\param缓冲区缓冲区要在缓冲区的长度中放置表示
 */
void mbedtls_strerror( int errnum, char *buffer, size_t buflen );

/**
 * \brief将Mbed TLS错误代码的高级部分转换为字符串表示。
 *
 * 此函数返回指向不可修改字符串的常量指针。调用方不得尝试修改字符串。它主要用于记录目的。
 *
 * \param error_code错误代码
 *
 * \return错误代码的字符串表示形式，如果错误代码未知，则返回空值。
 */
const char * mbedtls_high_level_strerr( int error_code );

/**
 * \brief将Mbed TLS错误代码的低级部分转换为字符串表示。
 *
 * 此函数返回指向不可修改字符串的常量指针。调用方不得尝试修改字符串。它主要用于记录目的。
 *
 * \param error_code错误代码
 *
 * \return错误代码的字符串表示形式，如果错误代码未知，则返回空值。
 */
const char * mbedtls_low_level_strerr( int error_code );

#ifdef __cplusplus
}
#endif

#endif /* 错误.h*/

