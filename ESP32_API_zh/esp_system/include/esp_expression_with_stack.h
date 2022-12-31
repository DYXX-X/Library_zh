// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_debug_helpers.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*shared_stack_function)(void);

#define ESP_EXECUTE_EXPRESSION_WITH_STACK(lock, stack, stack_size, expression) \
    esp_execute_shared_stack_function(lock, stack, stack_size, expression)

/**
 * @brief 调用用户定义的共享堆栈空间函数
 * @param lock 共享堆栈时要保护的互斥对象
 * @param stack 指向用户分配堆栈的指针
 * @param stack_size 当前堆栈的大小（字节）
 * @param function 指向要执行的共享堆栈函数的指针
 * @note  如果锁、堆栈或堆栈大小无效，将使用当前堆栈调用表达式。
 */
void esp_execute_shared_stack_function(SemaphoreHandle_t lock,
                                      void *stack,
                                      size_t stack_size,
                                      shared_stack_function function);


#ifdef __cplusplus
}
#endif

