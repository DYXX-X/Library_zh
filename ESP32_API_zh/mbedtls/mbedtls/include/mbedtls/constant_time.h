/**
 *  恒定时间函数
 *
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef MBEDTLS_CONSTANT_TIME_H
#define MBEDTLS_CONSTANT_TIME_H

#include <stddef.h>


/** 无分支的恒定时间缓冲区比较。
 *
 * 这相当于标准的memcmp函数，但很可能使用按位操作而不是分支编译为代码。
 *
 * 此函数可用于通过使用掩码将分支替换为位操作来编写恒定时间代码。
 *
 * \param a指向第一个缓冲区的指针。\param b指向第二个缓冲区的指针。\param n缓冲区中要比较的字节数。
 *
 * \如果两个缓冲区的内容相同，则返回零，否则为非零。
 */
int mbedtls_ct_memcmp( const void *a,
                       const void *b,
                       size_t n );

#endif /* MBEDTLS_CONSTANT_TIME_H */

