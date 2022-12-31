
// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef ESP_WPA3_H
#define ESP_WPA3_H

#include "esp_wifi_driver.h"

#ifdef CONFIG_WPA3_SAE

void esp_wifi_register_wpa3_cb(struct wpa_funcs *wpa_cb);
void esp_wpa3_free_sae_data(void);

#else /* CONFIG_WPA3_SAE */

static inline void esp_wifi_register_wpa3_cb(struct wpa_funcs *wpa_cb)
{
    wpa_cb->wpa3_build_sae_msg = NULL;
    wpa_cb->wpa3_parse_sae_msg = NULL;
}

static inline void esp_wpa3_free_sae_data(void)
{
}

#endif /* CONFIG_WPA3_SAE */
#endif /* ESP_WPA3_H */

