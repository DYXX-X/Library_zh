// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  初始化任务监视计时器（TWDT）
  *
  * 此函数用于配置和初始化TWDT。如果在调用此函数时TWDT已经初始化，则此函数将更新TWDT的超时周期和死机配置。初始化TWDT后，任何任务都可以通过使用esp_task_wdt_add（）订阅TWDT来选择由TWDT监视。
  *
  * @param[in]  timeout     TWDT超时时间（秒）
  * @param[in]  panic       控制TWDT超时时是否执行紧急处理程序的标志
  *
  * @return
  *     -ESP_OK:初始化成功
  *     -ESP_ERR_NO_MEM:由于内存不足，初始化失败
  *
  * @note   esp_task_wdt_init（）只能在调度程序启动后调用
  */
esp_err_t esp_task_wdt_init(uint32_t timeout, bool panic);

/**
 * @brief   取消初始化任务监视计时器（TWDT）
 *
 * 此函数将取消TWDT的初始化。当任务仍然订阅TWDT时，或者当TWDT已经取消初始化时，调用此函数将导致返回错误代码。
 *
 * @return
 *      -ESP_OK:TWDT已成功取消初始化
 *      -ESP_ERR_INVALID_STATE:错误，任务仍订阅到TWDT
 *      -ESP_ERR_NOT_FOUND：错误，TWDT已取消初始化
 */
esp_err_t esp_task_wdt_deinit(void);

/**
  * @brief  将任务订阅到任务监视计时器（TWDT）
  *
  * 此函数向TWDT订阅任务。每个订阅的任务必须定期调用esp_task_wdt_reset（），以防止TWDT超时。否则将导致TWDT超时。如果正在订阅的任务是空闲任务之一，则此函数将自动启用esp_task_wdt_reset（），以便从空闲任务的空闲挂钩调用。在TWDT未初始化或尝试订阅已订阅的任务时调用此函数将导致返回错误代码。
  *
  * @param[in]  handle  任务的句柄。输入NULL将当前正在运行的任务订阅到TWDT
  *
  * @return
  *     -ESP_OK：已成功将任务订阅到TWDT
  *     -ESP_ERR_INVALID_ARG：错误，任务已预订
  *     -ESP_ERR_NO_MEM:错误，由于内存不足，无法订阅任务
  *     -ESP_ERR_INVALID_STATE:错误，TWDT尚未初始化
  */
esp_err_t esp_task_wdt_add(TaskHandle_t handle);

/**
  * @brief  代表当前运行的任务重置任务监视计时器（TWDT）
  *
  * 此功能将代表当前运行的任务重置TWDT。每个订阅的任务必须定期调用此函数，以防止TWDT超时。如果一个或多个订阅任务未能自行重置TWDT，则将发生TWDT超时。如果IDLE任务已经订阅了TWDT，它们将自动从空闲挂钩调用此函数。从尚未订阅TWDT的任务调用此函数，或者在TWDT未初始化时调用此函数将导致返回错误代码。
  *
  * @return
  *     -ESP_OK：代表当前运行的任务成功重置TWDT
  *     -ESP_ERR_NOT_FOUND：错误，当前正在运行的任务尚未订阅TWDT
  *     -ESP_ERR_INVALID_STATE:错误，TWDT尚未初始化
  */
esp_err_t esp_task_wdt_reset(void);

/**
  * @brief  从任务监视计时器（TWDT）取消订阅任务
  *
  * 此功能将从TWDT取消订阅任务。取消订阅后，任务不应再调用esp_task_wdt_reset（）。如果任务是IDLE任务，此函数将自动禁用从IdleHook调用esp_task_wdt_reset（）。在TWDT未初始化或试图从TWDT取消订阅已取消订阅的任务时调用此函数将导致返回错误代码。
  *
  * @param[in]  handle  任务的句柄。输入NULL以取消订阅当前正在运行的任务。
  *
  * @return
  *     -ESP_OK：已成功从TWDT取消订阅任务
  *     -ESP_ERR_INVALID_ARG：错误，任务已取消订阅
  *     -ESP_ERR_INVALID_STATE:错误，TWDT尚未初始化
  */
esp_err_t esp_task_wdt_delete(TaskHandle_t handle);

/**
  * @brief   查询任务是否订阅了任务监视计时器（TWDT）
  *
  * 此函数将查询任务当前是否订阅了TWDT，或者TWDT是否已初始化。
  *
  * @param[in]  handle  任务的句柄。输入NULL以查询当前正在运行的任务。
  *
  * @return:
  *     -ESP_OK：任务当前已订阅TWDT
  *     -ESP_ERR_NOT_FOUND：任务当前未订阅TWDT
  *     -ESP_ERR_INVALID_STATE:TWDT未初始化，因此无法订阅任何任务
  */
esp_err_t esp_task_wdt_status(TaskHandle_t handle);


#ifdef __cplusplus
}
#endif

