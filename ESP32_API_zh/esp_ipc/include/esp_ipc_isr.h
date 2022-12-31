/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_ESP_IPC_ISR_ENABLE

/**
 * @brief IPC ISR回调
 *
 * 在调用esp_ipc_isr_asm_call（）或esp_ipc_idsr_asm_call_blocking（）时，应提供此类型的回调作为参数。
 */
typedef void (*esp_ipc_isr_func_t)(void* arg);

/**
 * @brief 在其他CPU上执行程序集回调
 *
 * 在高优先级中断的上下文中，在其他CPU上执行给定的回调。
 *
 * -此函数将在关键部分忙着等待，直到其他CPU开始执行回调
 * -回调必须以汇编形式编写，使用CALLS0指令调用，并将a2、a3、a4作为暂存寄存器。有关详细信息，请参阅文档
 *
 * @note 此功能在单核模式下不可用。
 *
 * @param[in]   func    指向要执行的void func（void*arg）类型函数的指针
 * @param[in]   arg     要传递到函数中的void*类型的任意参数
 */
void esp_ipc_isr_asm_call(esp_ipc_isr_func_t func, void* arg);

/**
 * @brief 在其他CPU上执行程序集回调，并忙着等待它完成
 *
 * 此函数与esp_ipc_isr_asm_call（）相同，只是此函数将忙着等待回调的执行完成。
 *
 * @note 此功能在单核模式下不可用。
 *
 * @param[in]   func    指向要执行的void func（void*arg）类型函数的指针
 * @param[in]   arg     要传递到函数中的void*类型的任意参数
 */
void esp_ipc_isr_asm_call_blocking(esp_ipc_isr_func_t func, void* arg);

/**
 * @brief 暂停其他CPU
 *
 * 此功能将暂停其他CPU。另一个CPU由于在高优先级中断的上下文中忙于等待而停止。在调用esp_ipc_isr_release_other_CPU（）之前，不会恢复其他CPU。
 *
 * -此功能在内部使用IPC ISR实现
 * -此功能用于DPORT解决方案。
 * -如果使用esp_ipc_isr_stall_pause（）暂停暂停功能，则此函数将无效
 *
 * @note 此功能在单核模式下不可用。
 */
void esp_ipc_isr_stall_other_cpu(void);

/**
 * @brief 释放其他CPU
 *
 * 此函数将释放先前停止调用esp_ipc_isr_stall_other_CPU（）的其他CPU
 *
 * -此功能用于DPORT解决方案。
 * -如果使用esp_ipc_isr_stall_pause（）暂停暂停功能，则此函数将无效
 *
 * @note 此功能在单核模式下不可用。
 */
void esp_ipc_isr_release_other_cpu(void);

/**
 * @brief 启用CPU暂停功能
 *
 * 此功能将暂停CPU暂停功能。一旦暂停，对esp_ipc_isr_stall_other_cpu（）和esp_ipc_idsr_release_other_cpu（）的调用将无效。如果IPC ISR调用已经在进行中，则此函数将一直忙着等待调用完成，然后暂停CPU暂停功能。
 */
void esp_ipc_isr_stall_pause(void);

/**
 * @brief 中止CPU暂停
 *
 * 由于上次调用esp_ipc_isr_stall_other_CPU（），此函数将中止其他CPU的任何暂停例程。此函数以不可恢复的方式中止暂停，因此只能在panic（）的情况下调用。
 *
 * -此函数用于紧急处理代码
 */
void esp_ipc_isr_stall_abort(void);

/**
 * @brief 恢复CPU暂停功能
 *
 * 此函数将通过调用esp_ipc_isr_stall_pause（）恢复先前暂停的CPU暂停功能。一旦恢复，对esp_ipc_isr_stall_other_cpu（）和esp_ipc_idsr_release_other_cpu（）的调用将再次生效。
 */
void esp_ipc_isr_stall_resume(void);

#else // CONFIG_ESP_IPC_ISR_ENABLE

#define esp_ipc_isr_stall_other_cpu()
#define esp_ipc_isr_release_other_cpu()
#define esp_ipc_isr_stall_pause()
#define esp_ipc_isr_stall_abort()
#define esp_ipc_isr_stall_resume()

#endif // CONFIG_ESP_IPC_ISR_ENABLE

#ifdef __cplusplus
}
#endif

