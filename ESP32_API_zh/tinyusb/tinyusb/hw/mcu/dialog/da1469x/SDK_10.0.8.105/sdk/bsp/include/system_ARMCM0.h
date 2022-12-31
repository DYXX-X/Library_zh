/**************************************************************************//**
 * @file     system_ARMCM0.h
 * @brief    CMSIS Device System Header File for ARMCM0 Device
 * @version  V5.3.1
 * @date     09. July 2018
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

#ifndef SYSTEM_ARMCM0_H
#define SYSTEM_ARMCM0_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;     /*!< 系统时钟频率（核心时钟）*/


/**
  \简要设置微控制器系统。

   初始化系统并更新SystemCoreCock变量。
 */
extern void SystemInit (void);


/**
  \brief Update SystemCoreClock变量。

   使用从cpu寄存器中检索的当前核心时钟更新SystemCoreClock。
 */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_ARMCM0_H */

