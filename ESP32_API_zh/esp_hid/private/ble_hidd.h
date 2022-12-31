// 版权所有2017-2019 Espressif Systems（上海）私人有限公司
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

#include "esp_hidd.h"
#include "esp_err.h"
#include "esp_hid_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_GATTS_ENABLE

esp_err_t esp_ble_hidd_dev_init(esp_hidd_dev_t *dev, const esp_hid_device_config_t *config, esp_event_handler_t callback);

#endif /* CONFIG_GATTS_ENABLE */

#ifdef __cplusplus
}
#endif

