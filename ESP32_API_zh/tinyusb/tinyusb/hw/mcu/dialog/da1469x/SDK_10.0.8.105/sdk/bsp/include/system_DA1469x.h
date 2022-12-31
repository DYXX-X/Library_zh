/**************************************************************************//**
 * @file     system_DA1469x.h
 * @brief    CMSIS Device System Header File for DA1469x Device
 * @version  V5.3.1
 * @date     17. May 2019
 ******************************************************************************/
/*
 * 版权所有（c）2009-2018 Arm Limited。保留所有权利。
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 根据Apache许可证2.0版（许可证）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按原样分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
/* 版权所有（c）2017 Dialog Semiconductor修改*/


#ifndef SYSTEM_DA1469x_H
#define SYSTEM_DA1469x_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

extern uint32_t SystemCoreClock;     /*!< 系统时钟频率（核心时钟）*/


/**
  \简要设置微控制器系统。

   初始化系统并更新SystemCoreCock变量。
 */
extern void SystemInit (void);


/**
  \brief Update SystemCoreClock变量。使用从cpu寄存器中检索的当前核心时钟更新SystemCoreClock。
 */
extern void SystemCoreClockUpdate (void);

/**
 * \brief将CPU地址转换为物理地址
 *
 * 为了计算物理地址，使用当前重新映射（SYS_CTRL_REG.REMAP_ADR0）。
 *
 * \CPU看到的param[in]addr地址
 *
 * \返回物理地址（用于DMA、AES/HASH等）--可以与addr相同或不同
 *
 */
extern uint32_t black_orca_phy_addr(uint32_t addr);


#ifdef __cplusplus
}
#endif

#endif /* 系统_DA1469x_H*/

