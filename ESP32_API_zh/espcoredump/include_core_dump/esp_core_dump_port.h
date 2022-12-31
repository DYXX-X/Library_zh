// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#ifndef ESP_CORE_DUMP_PORT_H_
#define ESP_CORE_DUMP_PORT_H_

/**
 * @file
 * @brief 核心转储端口接口。
 *
 * 该文件包含核心转储组件获取与板或SoC本身相关的信息所需的所有功能。目前，该接口的实现位于“src/port/[arch]”中，支持Xtensa和RISC-V架构。
 */

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "soc/cpu.h"
#include "esp_debug_helpers.h"
#include "esp_app_format.h"
#include "esp_core_dump_types.h"
#include "esp_core_dump_port_impl.h"
#include "esp_core_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取体系结构ID。
 *
 * @return 架构ID，如ELF格式所述。
 */
uint16_t esp_core_dump_get_arch_id(void);

/**
 * @brief 初始化端口模块。该函数还负责初始化额外信息（如果有的话）。
 *
 * @param info 指向紧急信息的指针。它包含执行框架。
 */
void esp_core_dump_port_init(panic_info_t *info);

/**
 * @brief 重置假堆栈分配器（如果有）。
 *
 * @note 如果我们想释放之前分配的所有“假”堆栈，则调用此函数，这些堆栈用于中断的任务。
 */
void esp_core_dump_reset_fake_stacks(void);

/**
 * @brief 获取ISR堆栈结束地址。
 *
 * @return ISR堆栈的结束地址。
 */
uint32_t esp_core_dump_get_isr_stack_end(void);


/**
 * @brief 获取ISR堆栈的顶部。
 *
 * @return 指向ISR堆栈顶部的指针。
 */
uint8_t* esp_core_dump_get_isr_stack_top(void);


/**
 * @brief 检查由给定地址定义的堆栈。
 *
 * @param task 要检查堆栈的任务。
 *
 * @return 如果堆栈正常，则为true，否则为false。
 */
bool esp_core_dump_check_stack(core_dump_task_header_t *task);


/**
 * @brief 检查内存段是否正常。
 *
 * @param addr 要检查的内存段的地址。
 * @param sz 要检查的内存段的大小。
 *
 * @return 如果内存段正常，则为true，否则为false。
 */
bool esp_core_dump_mem_seg_is_sane(uint32_t addr, uint32_t sz);


/**
 * @brief 获取任务堆栈。
 *
 * @param task_snapshot 指向任务快照的指针。
 * @param stk_vaddr 将设置为堆栈虚拟地址的指针。不能为NULL。
 * @param stk_paddr 将设置为堆栈物理地址的指针。不能为NULL。
 *
 * @return 堆栈的大小（字节）。
 */
uint32_t esp_core_dump_get_stack(core_dump_task_header_t* task_snapshot,
                                 uint32_t* stk_vaddr, uint32_t* stk_paddr);


/**
 * @brief 检查作为参数传递的任务。
 *
 * @note 此函数的目标是检查传递的任务是否是崩溃的任务。如果是这种情况，并且它没有在ISR中崩溃，那么它的堆栈指针将被设置为紧急帧，其中包含发生错误时的所有寄存器值。此函数还检查TCB地址是否正常。
 *
 * @param task 指向发生死机时生成的帧异常的指针。
 *
 * @return 如果TCB正常，则为True，否则为false。
 */
bool esp_core_dump_check_task(core_dump_task_header_t *task);


/**
 * @brief 获取任务寄存器的转储。
 *
 * @note 实际上，此函数用于用所有现有任务的PR_STATUS部分填充ELF文件。此结构包含发生异常时的CPU寄存器值。
 *
 * @param task     从中转储寄存器的任务。
 * @param reg_dump 将用寄存器转储填充的指针。不能为NULL。
 *
 * @return 返回的寄存器duump的大小（字节）。
 */
uint32_t esp_core_dump_get_task_regs_dump(core_dump_task_header_t *task,
                                          void **reg_dump);

/**
 * @brief 传输崩溃的任务句柄。
 *
 * @param handle 任务句柄崩溃。
 *
 * @note 此函数用于向端口模块提供有关崩溃任务的信息。如果不需要，可以忽略它。
 */
void esp_core_dump_port_set_crashed_tcb(uint32_t handle);

/**
 * @brief 检索额外信息。
 *
 * @param info 将填充额外信息的指针。可以为NULL，在这种情况下，此函数用于获取额外的信息大小。
 *
 * @return 额外信息的大小（以字节为单位）。
 */
uint32_t esp_core_dump_get_extra_info(void **info);

#if CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF

/**
 * @brief 将额外信息解析为摘要
 *
 * @param summary 指向核心转储摘要结构的指针
 * @param ei_data 指向从闪存读取的EXTRA_INFO钞票数据的指针
 */
void esp_core_dump_summary_parse_extra_info(esp_core_dump_summary_t *summary, void *ei_data);

/**
 * @brief 将异常寄存器解析为摘要
 *
 * @param summary 指向核心转储摘要结构的指针
 * @param stack_data 指向从闪存读取的崩溃任务堆栈数据的指针
 */
void esp_core_dump_summary_parse_exc_regs(esp_core_dump_summary_t *summary, void *stack_data);

/**
 * @brief 将回溯分析为bt_info
 *
 * @param bt_info 用于存储回溯信息的指针
 * @param vaddr 指向崩溃任务堆栈vaddr的指针
 * @param paddr 指向崩溃任务的堆栈填充器
 * @param stack_size 堆栈大小
 */
void esp_core_dump_summary_parse_backtrace_info(esp_core_dump_bt_info_t *bt_info, const void *vaddr,
                                                const void *paddr, uint32_t stack_size);
#endif /* CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF */

#ifdef __cplusplus
}
#endif

#endif

