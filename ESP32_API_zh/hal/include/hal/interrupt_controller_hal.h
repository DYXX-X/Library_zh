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

#include <stdbool.h>
#include "hal/interrupt_controller_types.h"
#include "hal/interrupt_controller_ll.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOC_CPU_HAS_FLEXIBLE_INTC
/**
 * @brief 获取目标平台中断描述符表
 *
 * @return 中断描述符表的地址
 */
__attribute__((pure))  const int_desc_t *interrupt_controller_hal_desc_table(void);
#endif

/**
 * @brief 获取给定中断号的中断类型。
 *
 * @param interrupt_number 中断号0至31
 * @return 中断类型
 */
__attribute__((pure))  int_type_t interrupt_controller_hal_desc_type(int interrupt_number);

/**
 * @brief 获取给定中断号的中断级别。
 *
 * @param interrupt_number 中断号0至31
 * @return 中断级位掩码
 */
__attribute__((pure))  int interrupt_controller_hal_desc_level(int interrupt_number);

/**
 * @brief 获取给定中断号和目标cpu的cpu标志。
 *
 * @param interrupt_number 中断号0至31
 * @param cpu_number CPU编号介于0和SOC_CPU_CORES_NUM之间-1
 * @return 该中断号的标志
 */
__attribute__((pure))  int_desc_flag_t interrupt_controller_hal_desc_flags(int interrupt_number, int cpu_number);

/**
 * @brief 获取给定中断号的中断类型。
 *
 * @param interrupt_number 中断号0至31
 * @return 中断类型
 */
static inline int_type_t interrupt_controller_hal_get_type(int interrupt_number)
{
    return interrupt_controller_hal_desc_type(interrupt_number);
}

/**
 * @brief 获取给定中断号的中断级别。
 *
 * @param interrupt_number 中断号0至31
 * @return 中断级位掩码
 */
static inline int interrupt_controller_hal_get_level(int interrupt_number)
{
    return interrupt_controller_hal_desc_level(interrupt_number);
}

#ifdef SOC_CPU_HAS_FLEXIBLE_INTC
/**
 * @brief 在控制器中设置中断类型。
 *
 * @param interrupt_number 中断号0至31
 * @param type 边缘或电平触发的中断类型
 */
static inline void interrupt_controller_hal_set_int_type(int intr, int_type_t type)
{
    intr_cntrl_ll_set_int_type(intr, type);
}

/**
 * @brief 设置中断控制器的中断级别。
 *
 * @param interrupt_number 中断号0至31
 * @param level 优先级介于1（最低）到7（最高）之间
 */
static inline void interrupt_controller_hal_set_int_level(int intr, int level)
{
    intr_cntrl_ll_set_int_level(intr, level);
}
#endif

/**
 * @brief 获取给定中断号和目标cpu的cpu标志。
 *
 * @param interrupt_number 中断号0至31
 * @param cpu_number CPU编号介于0和SOC_CPU_CORES_NUM之间-1
 * @return 该中断号的标志
 */
static inline uint32_t interrupt_controller_hal_get_cpu_desc_flags(int interrupt_number, int cpu_number)
{
    return interrupt_controller_hal_desc_flags(interrupt_number, cpu_number);
}

/**
 * @brief 启用掩码指定的中断
 *
 * @param mask 需要启用的中断的位掩码
 */
static inline void interrupt_controller_hal_enable_interrupts(uint32_t mask)
{
    intr_cntrl_ll_enable_interrupts(mask);
}

/**
 * @brief 禁用掩码指定的中断
 *
 * @param mask 需要禁用的中断的位掩码
 */
static inline void interrupt_controller_hal_disable_interrupts(uint32_t mask)
{
    intr_cntrl_ll_disable_interrupts(mask);
}

/**
 * @brief 读取当前中断掩码。
 *
 * @return 当前中断的位掩码
 */
static inline uint32_t interrupt_controller_hal_read_interrupt_mask(void)
{
    return intr_cntrl_ll_read_interrupt_mask();
}

/**
 * @brief 检查给定的中断号是否具有有效的处理程序
 *
 * @param intr 中断号范围从0到31
 * @param cpu cpu编号范围介于0到SOC_cpu_CORES_NUM之间-1
 * @return 有效处理程序为true，否则为false
 */
static inline bool interrupt_controller_hal_has_handler(int intr, int cpu)
{
    return intr_cntrl_ll_has_handler(intr, cpu);
}

/**
 * @brief 设置给定中断号的中断处理程序和可选参数
 *
 * @param intr 中断号范围从0到31
 * @param handler 发生中断时调用的处理程序
 * @param arg 传递给处理程序的可选参数
 */
static inline void interrupt_controller_hal_set_int_handler(uint8_t intr, interrupt_handler_t handler, void *arg)
{
    intr_cntrl_ll_set_int_handler(intr, handler, arg);
}

/**
 * @brief 获取传递给给定中断号的处理程序的参数
 *
 * @param intr 中断号范围从0到31
 *
 * @return 传递的中断号处理程序使用的参数
 */
static inline void * interrupt_controller_hal_get_int_handler_arg(uint8_t intr)
{
    return intr_cntrl_ll_get_int_handler_arg(intr);
}

/**
 * @brief 通过清除边缘触发中断的挂起标志来确认边缘触发中断
 *
 * @param intr 中断号范围从0到31
 */
static inline void interrupt_controller_hal_edge_int_acknowledge(int intr)
{
    intr_cntrl_ll_edge_int_acknowledge(intr);
}

#ifdef __cplusplus
}
#endif

