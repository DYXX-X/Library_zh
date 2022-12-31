// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "soc/soc.h"

/* 一些RF前端控制寄存器。此处定义的PU/PD字段用于睡眠相关函数。
 */

#define FE_GEN_CTRL (DR_REG_FE_BASE + 0x0090)
#define FE_IQ_EST_FORCE_PU (BIT(5))
#define FE_IQ_EST_FORCE_PU_M (BIT(5))
#define FE_IQ_EST_FORCE_PU_V 1
#define FE_IQ_EST_FORCE_PU_S 5
#define FE_IQ_EST_FORCE_PD (BIT(4))
#define FE_IQ_EST_FORCE_PD_M (BIT(4))
#define FE_IQ_EST_FORCE_PD_V 1
#define FE_IQ_EST_FORCE_PD_S 4

#define FE2_TX_INTERP_CTRL (DR_REG_FE2_BASE + 0x00f0)
#define FE2_TX_INF_FORCE_PU (BIT(10))
#define FE2_TX_INF_FORCE_PU_M (BIT(10))
#define FE2_TX_INF_FORCE_PU_V 1
#define FE2_TX_INF_FORCE_PU_S 10
#define FE2_TX_INF_FORCE_PD (BIT(9))
#define FE2_TX_INF_FORCE_PD_M (BIT(9))
#define FE2_TX_INF_FORCE_PD_V 1
#define FE2_TX_INF_FORCE_PD_S 9

