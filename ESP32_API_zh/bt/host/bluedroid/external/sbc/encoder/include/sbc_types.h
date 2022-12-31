/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 数据类型声明。
 *
 ******************************************************************************/

#ifndef SBC_TYPES_H
#define SBC_TYPES_H

#include <stdint.h>

#ifdef BUILDCFG
#include "common/bt_target.h"
#endif

#include "stack/bt_types.h"

typedef short SINT16;
typedef long SINT32;

#if (SBC_IPAQ_OPT == TRUE)

#if (SBC_FOR_EMBEDDED_LINUX == TRUE)
typedef long long SINT64;
#else
typedef int64_t SINT64;
#endif

#elif (SBC_IS_64_MULT_IN_WINDOW_ACCU == TRUE) || (SBC_IS_64_MULT_IN_IDCT == TRUE)

#if (SBC_FOR_EMBEDDED_LINUX == TRUE)
typedef long long SINT64;
#else
typedef int64_t SINT64;
#endif

#endif

#define abs32(x) ( (x >= 0) ? x : (-x) )

#endif

