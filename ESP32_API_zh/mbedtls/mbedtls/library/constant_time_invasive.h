/**
 * \文件常量_时间_侵入.h
 *
 * \简短的恒定时间模块：仅用于侵入性测试的接口。
 *
 * 本文件中的接口仅用于测试目的。它们不应在库集成中可用，除非构建库进行测试。
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

#ifndef MBEDTLS_CONSTANT_TIME_INVASIVE_H
#define MBEDTLS_CONSTANT_TIME_INVASIVE_H

#include "common.h"

#if defined(MBEDTLS_TEST_HOOKS)

/** 将值转换为遮罩：
 * -如果\p low<=\p c<=\pp high，则返回所有位1掩码，aka（无符号）-1
 * -否则，返回所有位0掩码，即0
 *
 * \param low要分析的值。\param high要分析的值。\param c要分析的值。
 *
 * \如果\p低<=\p c<=\pp高，则返回所有位1，否则为零。
 */
unsigned char mbedtls_ct_uchar_mask_of_range( unsigned char low,
                                              unsigned char high,
                                              unsigned char c );

#endif /* MBEDTLS_TEST_HOOKS */

#endif /* MBEDTLS_CONSTANT_TIME_INVASIVE_H */

