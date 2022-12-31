// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#include "esp_err.h"
#include "freertos/FreeRTOSConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN    CONFIG_PTHREAD_STACK_MIN
#endif

/**影响pthread创建的pthread配置结构*/
typedef struct {
    size_t stack_size;  ///＜pthread的堆栈大小
    size_t prio;        ///<线程的优先级
    bool inherit_cfg;   ///<进一步继承此配置
    const char* thread_name;  ///<线程名称。
    int pin_to_core;    ///<要将线程固定到的核心id。具有与xTaskCreatePinnedToCore的xCoreId参数相同的值范围。
} esp_pthread_cfg_t;

/**
 * @brief 基于通过menuconfig设置的值创建默认pthread配置。
 *
 * @return 默认配置结构。
 */
esp_pthread_cfg_t esp_pthread_get_default_config(void);

/**
 * @brief 配置用于创建pthread的参数
 *
 * 此API允许您配置后续pthread_create（）调用的行为。此调用可用于设置配置参数，如堆栈大小、优先级、配置继承等。
 *
 * 如果配置结构中的“inherit”标志已启用，那么同样的配置也将在线程子树中继承。
 *
 * @note 向pthread_create（）传递非NULL属性将覆盖使用此API设置的stack_size参数
 *
 * @param cfg pthread配置参数
 *
 * @return
 *      -如果已成功设置配置，则ESP_OK
 *      -ESP_ERR_NO_MEM（如果内存不足）
 *      -如果堆栈大小小于PTHREAD_stack_MIN，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_pthread_set_cfg(const esp_pthread_cfg_t *cfg);

/**
 * @brief 获取当前pthread创建配置
 *
 * 这将检索用于创建线程的当前配置。
 *
 * @param p 指向将使用当前配置的参数更新的pthread配置结构的指针
 *
 * @return
 *      -ESP_OK（如果配置可用）
 *      -如果之前未设置配置，则为ESP_ERR_NOT_FOUND
 */
esp_err_t esp_pthread_get_cfg(esp_pthread_cfg_t *p);

/**
 * @brief 初始化pthread库
 */
esp_err_t esp_pthread_init(void);

#ifdef __cplusplus
}
#endif

