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

#include "esp_hidh.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_GATTC_ENABLE

esp_err_t esp_ble_hidh_init(const esp_hidh_config_t *config);
esp_err_t esp_ble_hidh_deinit(void);

esp_hidh_dev_t *esp_ble_hidh_dev_open(esp_bd_addr_t bda, esp_ble_addr_type_t address_type);

#endif /* CONFIG_GATTC_ENABLE */

#ifdef __cplusplus
}
#endif

