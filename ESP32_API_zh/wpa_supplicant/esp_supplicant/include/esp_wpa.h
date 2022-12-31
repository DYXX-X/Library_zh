// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_WPA_H__
#define __ESP_WPA_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_wifi_crypto_types.h"
#include "esp_wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup WiFi_APIs WiFi相关API
  * @brief WiFi API
  */

/** @addtogroup WiFi_API@{
  */

/** \defgroup WPA_API WPS API
  * @brief ESP32供应商API
  *
  */

/** @addtogroup WPA_API@{
  */
/* 加密回调函数*/
const wpa_crypto_funcs_t g_wifi_default_wpa_crypto_funcs;
/* 网格加密回调函数*/
const mesh_crypto_funcs_t g_wifi_default_mesh_crypto_funcs;

/**
  * @brief     恳求者初始化
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_NO_MEM：内存不足
  */
esp_err_t esp_supplicant_init(void);

/**
  * @brief     恳求性去初始化
  *
  * @return
  *          -ESP_OK：成功
  *          -其他：失败
  */
esp_err_t esp_supplicant_deinit(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ESP_WPA_H__ */

