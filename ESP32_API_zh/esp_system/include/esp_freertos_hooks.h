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

#ifndef __ESP_FREERTOS_HOOKS_H__
#define __ESP_FREERTOS_HOOKS_H__

#include <stdbool.h>

#include "freertos/portmacro.h"

#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 tickhook和idlehook回调的定义
*/
typedef bool (*esp_freertos_idle_cb_t)(void);
typedef void (*esp_freertos_tick_cb_t)(void);

/**
  * @brief  注册要从指定内核的空闲挂钩调用的回调。如果空闲钩子每次中断（或FreeRTOS滴答声）调用一次回调，则回调应返回true；如果空闲钩子应尽可能快地重复调用回调，则返回false。
  *
  * @warning 在任何情况下，空闲回调都不能调用可能阻塞的函数。
  *
  * @param[in]  new_idle_cb     要调用的回调
  * @param[in]  cpuid           核心id
  *
  * @return
  *     -ESP_OK：注册到指定内核的空闲挂钩的回调
  *     -ESP_ERR_NO_MEM：指定内核的空闲挂钩上没有更多空间来注册回调
  *     -ESP_ERR_INVALID_ARG:cpuid无效
  */
esp_err_t esp_register_freertos_idle_hook_for_cpu(esp_freertos_idle_cb_t new_idle_cb, UBaseType_t cpuid);

/**
  * @brief  向调用此函数的内核的空闲钩子注册回调。如果空闲钩子每次中断（或FreeRTOS滴答声）调用一次回调，则回调应返回true；如果空闲钩子应尽可能快地重复调用回调，则返回false。
  *
  * @warning 在任何情况下，空闲回调都不能调用可能阻塞的函数。
  *
  * @param[in]  new_idle_cb     要调用的回调
  *
  * @return
  *     -ESP_OK：注册到调用核心的空闲钩子的回调
  *     -ESP_ERR_NO_MEM：调用核心的空闲挂钩上没有更多空间来注册回调
  */
esp_err_t esp_register_freertos_idle_hook(esp_freertos_idle_cb_t new_idle_cb);

/**
  * @brief  注册要从指定内核的勾号钩子调用的回调。
  *
  * @param[in]  new_tick_cb     要调用的回调
  * @param[in]  cpuid           核心id
  *
  * @return
  *     -ESP_OK：注册到指定核心勾号的回调
  *     -ESP_ERR_NO_MEM：指定内核的勾号钩子上没有更多空间来注册回调
  *     -ESP_ERR_INVALID_ARG:cpuid无效
  */
esp_err_t esp_register_freertos_tick_hook_for_cpu(esp_freertos_tick_cb_t new_tick_cb, UBaseType_t cpuid);

/**
  * @brief  注册要从调用核心的勾号钩子调用的回调。
  *
  * @param[in]  new_tick_cb     要调用的回调
  *
  * @return
  *     -ESP_OK：回调注册到调用核心的勾号
  *     -ESP_ERR_NO_MEM：调用核心的勾号钩子上没有更多空间来注册回调
  */
esp_err_t esp_register_freertos_tick_hook(esp_freertos_tick_cb_t new_tick_cb);

/**
  * @brief  从指定内核的空闲挂钩注销空闲回调
  *
  * @param[in]  old_idle_cb     要注销的回调
  * @param[in]  cpuid           核心id
  */
void esp_deregister_freertos_idle_hook_for_cpu(esp_freertos_idle_cb_t old_idle_cb, UBaseType_t cpuid);

/**
  * @brief  注销空闲回调。如果空闲回调已注册到两个内核的空闲挂钩，则将从两个内核注销空闲挂钩
  *
  * @param[in]  old_idle_cb     要注销的回调
  */
void esp_deregister_freertos_idle_hook(esp_freertos_idle_cb_t old_idle_cb);

/**
  * @brief  从指定核心的勾号钩子注销勾号回调
  *
  * @param[in]  old_tick_cb     要注销的回调
  * @param[in]  cpuid           核心id
  */
void esp_deregister_freertos_tick_hook_for_cpu(esp_freertos_tick_cb_t old_tick_cb, UBaseType_t cpuid);

/**
  * @brief  注销tick回调。如果tick回调已注册到两个内核的tick钩子，则tick钩子将从两个内核中注销
  *
  * @param[in]  old_tick_cb     要注销的回调
  */
void esp_deregister_freertos_tick_hook(esp_freertos_tick_cb_t old_tick_cb);

#ifdef __cplusplus
}
#endif


#endif

