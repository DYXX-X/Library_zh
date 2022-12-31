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

#ifndef __ESP_BT_DEVICE_H__
#define __ESP_BT_DEVICE_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief      获取蓝牙设备地址。必须在“esp_bluedroid_enable”之后使用。
 *
 * @return     蓝牙设备地址（六个字节），如果未启用蓝牙堆栈，则为NULL
 */
const uint8_t *esp_bt_dev_get_address(void);


/**
 * @brief           设置蓝牙设备名称。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 *                  BR/EDR/LE设备类型应具有单个蓝牙设备名称，无论用于执行名称发现程序的物理信道如何，该名称都应相同。
 *
 * @param[in]       name ：要设置的设备名称
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_ARG：如果名称为NULL指针或空，或字符串长度超出限制
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_dev_set_device_name(const char *name);

#ifdef __cplusplus
}
#endif


#endif /* __ESP_BT_DEVICE_H__ */

