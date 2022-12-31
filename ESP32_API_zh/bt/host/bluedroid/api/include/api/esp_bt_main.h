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

#ifndef __ESP_BT_MAIN_H__
#define __ESP_BT_MAIN_H__

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 蓝牙堆栈状态类型，指示蓝牙堆栈是否就绪。
 */
typedef enum {
    ESP_BLUEDROID_STATUS_UNINITIALIZED   = 0,        /*!< 蓝牙未初始化*/
    ESP_BLUEDROID_STATUS_INITIALIZED,                /*!< 蓝牙已初始化但未启用*/
    ESP_BLUEDROID_STATUS_ENABLED                     /*!< 蓝牙已初始化并已启用*/
} esp_bluedroid_status_t;

/**
 * @brief     获取蓝牙堆栈状态
 *
 * @return    蓝牙堆栈状态
 *
 */
esp_bluedroid_status_t esp_bluedroid_get_status(void);

/**
 * @brief     启用蓝牙，必须在esp_bluedroid_init（）之后。
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bluedroid_enable(void);

/**
 * @brief     禁用蓝牙，必须在esp_bluedroid_deinit（）之前。
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bluedroid_disable(void);

/**
 * @brief     初始化和分配蓝牙资源，必须先于所有蓝牙内容。
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bluedroid_init(void);

/**
 * @brief     为蓝牙设计和释放资源，必须在每一个蓝牙东西之后。
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bluedroid_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_BT_MAIN_H__ */

