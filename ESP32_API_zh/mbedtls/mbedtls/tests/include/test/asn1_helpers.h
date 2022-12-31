/** 用于操作ASN的测试的助手函数。1数据。
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

#ifndef ASN1_HELPERS_H
#define ASN1_HELPERS_H

#include "test/helpers.h"

/** 跳过ASN中的整数。1个缓冲区。
 *
 * 在以下任何情况下，将当前测试用例标记为失败：
 * -缓冲区不以ASN开头。1整数。
 * -整数的大小或奇偶性与通过\p min_bits、\p max_bits和\p must_be_oodd表示的约束不匹配。
 *
 * \param p输入时，“*p”指向要解析的缓冲区的第一个字节。成功返回时，“p”指向解析的INTEGER之后的第一个字节。失败时，未指定“p”。\param end ASN的结束。1个缓冲区。\param min_bits如果整数至少没有这么多有效位，则测试用例失败。\param max_bits如果整数的有效位超过此数量，则测试用例失败。\param must_be_oodd如果整数为偶数，则测试用例失败。
 *
 * \如果测试失败，则返回\c 0，否则返回1。
 */
int mbedtls_test_asn1_skip_integer( unsigned char **p, const unsigned char *end,
                                    size_t min_bits, size_t max_bits,
                                    int must_be_odd );

#endif /* ASN1_HELPERS_H */

