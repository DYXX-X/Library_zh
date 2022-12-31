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
 * @brief 初始化IPC ISR功能，必须为每个CPU调用
 *
 * @note 此函数是从ipc_task（）调用的。
 *
 * 此函数初始化IPC ISR功能，必须在任何其他esp_IPC_ISR…（）函数之前调用。IPC ISR功能允许在高优先级中断的上下文中在特定CPU上运行回调（以汇编形式编写）。
 *
 * -此函数将为调用它的CPU注册高优先级中断。中断的优先级取决于CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL选项。
 * -然后，在程序集中写入的回调可以在已注册的高优先级中断的上下文中运行
 * -可以通过调用esp_ipc_isr_asm_call（）或esp_ipc_idsr_asm_call_blocking（）来执行回调
 */
void esp_ipc_isr_init(void);

#endif // CONFIG_ESP_IPC_ISR_ENABLE

#ifdef __cplusplus
}
#endif

