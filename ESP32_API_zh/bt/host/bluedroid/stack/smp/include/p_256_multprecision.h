/******************************************************************************
 * 版权所有（C）2006-2015 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此文件包含简单的配对算法
 *
 ******************************************************************************/
#pragma once

#include "stack/bt_types.h"

/* 类型定义*/
typedef unsigned long  DWORD;

#define DWORD_BITS      32
#define DWORD_BYTES     4
#define DWORD_BITS_SHIFT 5

#define KEY_LENGTH_DWORDS_P192 6
#define KEY_LENGTH_DWORDS_P256 8
/* 算术运算*/

int multiprecision_compare(DWORD *a, DWORD *b, uint32_t keyLength);
int multiprecision_iszero(DWORD *a, uint32_t keyLength);
void multiprecision_init(DWORD *c, uint32_t keyLength);
void multiprecision_copy(DWORD *c, DWORD *a, uint32_t keyLength);
UINT32 multiprecision_dword_bits (DWORD a);
UINT32 multiprecision_most_signdwords(DWORD *a, uint32_t keyLength);
UINT32 multiprecision_most_signbits(DWORD *a, uint32_t keyLength);
void multiprecision_inv_mod(DWORD *aminus, DWORD *a, uint32_t keyLength);
DWORD multiprecision_add(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength); // c=a+b
void multiprecision_add_mod(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength);
DWORD multiprecision_sub(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength); // c=a-b
void multiprecision_sub_mod(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength);
void multiprecision_rshift(DWORD *c, DWORD *a, uint32_t keyLength);    // c=a>>1，返回载体
void multiprecision_lshift_mod(DWORD *c, DWORD *a, uint32_t keyLength);   // c=a<<b，返回载体
DWORD multiprecision_lshift(DWORD *c, DWORD *a, uint32_t keyLength);    // c=a<<b，返回载体
void multiprecision_mult(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength); // c=a*b
void multiprecision_mersenns_mult_mod(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength);
void multiprecision_mersenns_squa_mod(DWORD *c, DWORD *a, uint32_t keyLength);
DWORD multiprecision_lshift(DWORD *c, DWORD *a, uint32_t keyLength);
void multiprecision_mult(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength);
void multiprecision_fast_mod(DWORD *c, DWORD *a);
void multiprecision_fast_mod_P256(DWORD *c, DWORD *a);

