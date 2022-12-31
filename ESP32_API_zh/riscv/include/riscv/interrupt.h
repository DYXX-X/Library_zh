// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

#ifdef __cplusplus
extern "C" {
#endif

enum intr_type {
    INTR_TYPE_LEVEL = 0,
    INTR_TYPE_EDGE
};
/***************************软件中断调度器***************************/

/**中断处理程序的回调类型*/
typedef void (*intr_handler_t)(void*);

/** 为给定的CPU中断设置中断处理程序函数
 * @param rv_int_num  CPU中断号
 * @param fn  处理程序函数
 * @param arg  处理程序参数
 */
void intr_handler_set(int rv_int_num, intr_handler_t fn, void* arg);

/** 获取给定CPU中断的中断处理程序函数
 *
 *@return 为特定中断号注册的中断处理程序，否则为NULL
 */
intr_handler_t intr_handler_get(int rv_int_num);

/** 获取与给定CPU中断相关联的中断处理程序参数
 *
 *@return 特定中断号的中断处理程序参数，否则为NULL
 */
void *intr_handler_get_arg(int rv_int_num);

/***************************中断矩阵***************************/

/**
 * 稍后将删除此功能，请改用“intr_matrix_set”将外围中断信号路由到CPU
 * @param periph_intr_source  外围中断号，ETS_XXX_SOURCE之一
 * @param rv_int_num  CPU中断号
 */
void intr_matrix_route(int periph_intr_source, int rv_int_num);

/***************************ESP-RV中断控制器***************************/

/**
  * @brief 从中断控制器启用中断。
  *
  * @param uint32_t 取消掩码，取消掩码位用于中断，每个位用于中断
  *
  * 不返回
  */
void esprv_intc_int_enable(uint32_t unmask);

/**
  * @brief 禁用来自中断控制器的中断。
  *
  * @param uint32_t 掩码，中断的掩码位，每个位用于中断
  *
  * 不返回
  */
void esprv_intc_int_disable(uint32_t mask);

/**
  * @brief 设置中断类型、级别或边缘
  *
  * @param int intr_num，中断号
  *
  * @param enum intr_type类型，中断类型，一旦中断源被清除，级别中断可以被自动清除，边缘中断应该在处理后由软件清除
  *
  * 不返回
  */
void esprv_intc_int_set_type(int intr_num, enum intr_type type);

/**
 * 在中断控制器中设置中断优先级
 * @param rv_int_num  CPU中断号
 * @param priority  中断优先级，1至7
 */
void esprv_intc_int_set_priority(int rv_int_num, int priority);

/**
 * 设置中断优先级阈值。优先级低于阈值的中断被屏蔽。
 *
 * @param priority_threshold  中断优先级阈值，0到7
 */
void esprv_intc_set_threshold(int priority_threshold);

/**
 * @brief 获取中断取消屏蔽
 * @param none
 * @return uint32_t中断取消屏蔽
 */
uint32_t esprv_intc_get_interrupt_unmask(void);

#ifdef __cplusplus
}
#endif

