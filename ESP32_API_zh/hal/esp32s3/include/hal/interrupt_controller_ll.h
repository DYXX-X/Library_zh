// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdint.h>
#include "soc/soc_caps.h"
#include "soc/soc.h"
#include "xtensa/xtensa_api.h"
#include "xtensa/config/specreg.h"
#include "xt_instr_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 启用掩码指定的中断
 *
 * @param mask 需要启用的中断的位掩码
 */
static inline void intr_cntrl_ll_enable_interrupts(uint32_t mask)
{
    xt_ints_on(mask);
}

/**
 * @brief 禁用掩码指定的中断
 *
 * @param mask 需要禁用的中断的位掩码
 */
static inline void intr_cntrl_ll_disable_interrupts(uint32_t mask)
{
    xt_ints_off(mask);
}

/**
 * @brief 读取运行此代码的CPU的当前中断掩码。
 *
 * @return 当前中断位掩码。
 */
static inline uint32_t intr_cntrl_ll_read_interrupt_mask(void)
{
    uint32_t int_mask;
    RSR(INTENABLE, int_mask);
    return int_mask;
}

/**
 * @brief 检查给定的中断号是否具有有效的处理程序
 *
 * @param intr 中断号范围从0到31
 * @param cpu cpu编号范围介于0到SOC_cpu_CORES_NUM之间-1
 * @return 有效处理程序为true，否则为false
 */
static inline bool intr_cntrl_ll_has_handler(uint8_t intr, uint8_t cpu)
{
    return xt_int_has_handler(intr, cpu);
}

/**
 * @brief 设置给定中断号的中断处理程序和可选参数
 *
 * @param intr 中断号范围从0到31
 * @param handler 发生中断时调用的处理程序
 * @param arg 传递给处理程序的可选参数
 */
static inline void intr_cntrl_ll_set_int_handler(uint8_t intr, interrupt_handler_t handler, void *arg)
{
    xt_set_interrupt_handler(intr, (xt_handler)handler, arg);
}

/**
 * @brief 获取传递给给定中断号的处理程序的参数
 *
 * @param intr 中断号范围从0到31
 *
 * @return 传递的中断号处理程序使用的参数
 */
static inline void *intr_cntrl_ll_get_int_handler_arg(uint8_t intr)
{
    return xt_get_interrupt_handler_arg(intr);
}

/**
 * @brief 通过清除边缘触发中断的挂起标志来确认边缘触发中断
 *
 * @param intr 中断号范围从0到31
 */
static inline void intr_cntrl_ll_edge_int_acknowledge (int intr)
{
    xthal_set_intclear(1 << intr);
}
#ifdef __cplusplus
}
#endif

