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
 * 此文件包含使用椭圆曲线密码对私钥的简单配对算法
 *
 ******************************************************************************/

#pragma once

#include "p_256_multprecision.h"
#include "common/bt_target.h"

typedef unsigned long  DWORD;

typedef struct {
    DWORD x[KEY_LENGTH_DWORDS_P256];
    DWORD y[KEY_LENGTH_DWORDS_P256];
    DWORD z[KEY_LENGTH_DWORDS_P256];
} Point;

typedef struct {
    // 曲线系数
    DWORD a[KEY_LENGTH_DWORDS_P256];
    DWORD b[KEY_LENGTH_DWORDS_P256];

    //a是否为-3
    int a_minus3;

    // 基本模量
    DWORD p[KEY_LENGTH_DWORDS_P256];

    // 欧米茄，p=2^m-欧米茄
    DWORD omega[KEY_LENGTH_DWORDS_P256];

    // 基点，r阶E上的点
    Point G;

} elliptic_curve_t;

#if SMP_DYNAMIC_MEMORY == FALSE
extern elliptic_curve_t curve;
extern elliptic_curve_t curve_p256;
#else
extern elliptic_curve_t *curve_ptr;
extern elliptic_curve_t *curve_p256_ptr;
#define curve           (*curve_ptr)
#define curve_p256      (*curve_p256_ptr)
#endif


void ECC_PointMult_Bin_NAF(Point *q, Point *p, DWORD *n, uint32_t keyLength);

bool ECC_CheckPointIsInElliCur_P256(Point *p);

#define ECC_PointMult(q, p, n, keyLength)  ECC_PointMult_Bin_NAF(q, p, n, keyLength)

void p_256_init_curve(UINT32 keyLength);

