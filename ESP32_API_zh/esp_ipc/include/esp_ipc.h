// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(CONFIG_FREERTOS_UNICORE) || defined(CONFIG_APPTRACE_GCOV_ENABLE)

/*
 * 处理器间调用API
 *
 * FreeRTOS提供了几个API，可用于不同任务之间的通信，包括在不同CPU上运行的任务。该模块提供了在其他CPU上运行某些代码的附加API。这些API只能在FreeRTOS调度程序运行时使用。
 */

/**
 * @brief IPC回调
 *
 * 在调用esp_ipc_call（）或esp_ipc_call_blocking（）时，应提供此类型的回调作为参数。
 */
typedef void (*esp_ipc_func_t)(void* arg);

/**
 * @brief 在给定CPU上执行回调
 *
 * 在特定CPU上执行给定的回调。回调必须为“esp_ipc_func_t”类型，并将在目标CPU的ipc任务上下文中调用。
 *
 * -此函数将阻止目标CPU的IPC任务已开始执行回调
 * -如果另一个IPC调用正在进行，则此函数将阻塞，直到正在进行的IPC调用完成
 * -可以通过CONFIG_ESP_IPC_task_STATK_size选项配置IPC任务的堆栈大小
 *
 * @note 在单核模式下，为cpu_id 1返回ESP_ERR_INVALID_ARG。
 *
 * @param[in]   cpu_id  应执行给定功能的CPU（0或1）
 * @param[in]   func    指向要执行的void func（void*arg）类型函数的指针
 * @param[in]   arg     要传递到函数中的void*类型的任意参数
 *
 * @return
 *      -如果cpu_id无效，则为ESP_ERR_INVALID_ARG
 *      -如果FreeRTOS调度程序未运行，则为ESP_ERR_INVALID_STATE
 *      -否则ESP_OK
 */
esp_err_t esp_ipc_call(uint32_t cpu_id, esp_ipc_func_t func, void* arg);


/**
 * @brief 在给定的CPU上执行回调，直到并阻止回调完成
 *
 * 此函数与esp_ipc_call（）相同，只是此函数将阻塞，直到回调执行完成。
 *
 * @note    在单核模式下，为cpu_id 1返回ESP_ERR_INVALID_ARG。
 *
 * @param[in]   cpu_id  应执行给定功能的CPU（0或1）
 * @param[in]   func    指向要执行的void func（void*arg）类型函数的指针
 * @param[in]   arg     要传递到函数中的void*类型的任意参数
 *
 * @return
 *      -如果cpu_id无效，则为ESP_ERR_INVALID_ARG
 *      -如果FreeRTOS调度程序未运行，则为ESP_ERR_INVALID_STATE
 *      -否则ESP_OK
 */
esp_err_t esp_ipc_call_blocking(uint32_t cpu_id, esp_ipc_func_t func, void* arg);

#endif // !已定义（CONFIG_FREERTOS_UNCORE）||已定义（ONFIG_APPTRACE_GCOV_ENABLE）

#ifdef __cplusplus
}
#endif

