/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __MCU_DA1469X_CLOCK_H_
#define __MCU_DA1469X_CLOCK_H_

#include <stdint.h>
#include "mcu/da1469x_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 初始化XTAL32M
 */
void da1469x_clock_sys_xtal32m_init(void);

/**
 * 启用XTAL32M
 */
void da1469x_clock_sys_xtal32m_enable(void);

/**
 * 等待XTAL32M稳定
 */
void da1469x_clock_sys_xtal32m_wait_to_settle(void);

/**
 * 将sys_clk切换到XTAL32M
 *
 * 呼叫者应确保XTAL32M已结算。
 */
void da1469x_clock_sys_xtal32m_switch(void);

/**
 * 将sys_clk切换到XTAL32M
 *
 * 等待XTAL32M稳定后再切换。
 */
void da1469x_clock_sys_xtal32m_switch_safe(void);

/**
 * 禁用RC32M
 */
void da1469x_clock_sys_rc32m_disable(void);

/**
 * 启用AMBA时钟
 *
 * @param mask
 */
static inline void
da1469x_clock_amba_enable(uint32_t mask)
{
    uint32_t primask;

    __HAL_DISABLE_INTERRUPTS(primask);
    CRG_TOP->CLK_AMBA_REG |= mask;
    __HAL_ENABLE_INTERRUPTS(primask);
}

/**
 * 禁用AMBA时钟
 *
 * @param uint32_t 面具
 */
static inline void
da1469x_clock_amba_disable(uint32_t mask)
{
    uint32_t primask;

    __HAL_DISABLE_INTERRUPTS(primask);
    CRG_TOP->CLK_AMBA_REG &= ~mask;
    __HAL_ENABLE_INTERRUPTS(primask);
}

/**
 * 启用PLL96
 */
static inline void
da1469x_clock_sys_pll_enable(void)
{
    CRG_XTAL->PLL_SYS_CTRL1_REG |= CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_EN_Msk |
                                   CRG_XTAL_PLL_SYS_CTRL1_REG_LDO_PLL_ENABLE_Msk;
}

/**
 * 禁用PLL96
 *
 * 如果PLL用作SYS_CLOCK，则切换到XTAL32M。
 */
void da1469x_clock_sys_pll_disable(void);

/**
 * 检查PLL96是否锁定，是否可用作系统时钟或USB时钟
 *
 * @return 如果PLL关闭，则为0，否则为0
 */
static inline int
da1469x_clock_is_pll_locked(void)
{
    return 0 != (CRG_XTAL->PLL_SYS_STATUS_REG & CRG_XTAL_PLL_SYS_STATUS_REG_PLL_LOCK_FINE_Msk);
}

/**
 * 等待PLL96锁定。
 */
void da1469x_clock_pll_wait_to_lock(void);

/**
 * 将系统时钟切换到PLL96
 *
 * 呼叫者应确保PLL已锁定。
 */
void da1469x_clock_sys_pll_switch(void);

#ifdef __cplusplus
}
#endif

#endif /* __MCU_DA1469X_CLOCK_H_ */

