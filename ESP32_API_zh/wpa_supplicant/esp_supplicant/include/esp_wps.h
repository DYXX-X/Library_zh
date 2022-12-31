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

#ifndef __ESP_WPS_H__
#define __ESP_WPS_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_wifi_crypto_types.h"
#include "esp_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup WiFi_APIs WiFi相关API
  * @brief WiFi API
  */

/** @addtogroup WiFi_API@{
  */

/** \定义WPS_API WPS API
  * @brief ESP32 WPS API
  *
  * WPS只能在启用ESP32工作站时使用。
  *
  */

/** @addtogroup WPS_API@{
  */

#define ESP_ERR_WIFI_REGISTRAR   (ESP_ERR_WIFI_BASE + 51)  /*!< 不支持WPS注册器*/
#define ESP_ERR_WIFI_WPS_TYPE    (ESP_ERR_WIFI_BASE + 52)  /*!< WPS类型错误*/
#define ESP_ERR_WIFI_WPS_SM      (ESP_ERR_WIFI_BASE + 53)  /*!< WPS状态机未初始化*/

typedef enum wps_type {
    WPS_TYPE_DISABLE = 0,
    WPS_TYPE_PBC,
    WPS_TYPE_PIN,
    WPS_TYPE_MAX,
} wps_type_t;

#define WPS_MAX_MANUFACTURER_LEN 65
#define WPS_MAX_MODEL_NUMBER_LEN 33
#define WPS_MAX_MODEL_NAME_LEN   33
#define WPS_MAX_DEVICE_NAME_LEN  33

typedef struct {
    char manufacturer[WPS_MAX_MANUFACTURER_LEN]; /*!< 制造商，以空结尾的字符串。如果字符串为空，则使用默认制造商*/
    char model_number[WPS_MAX_MODEL_NUMBER_LEN]; /*!< 型号，以空结尾的字符串。如果字符串为空，则使用默认型号*/
    char model_name[WPS_MAX_MODEL_NAME_LEN];     /*!< 模型名称，以空结尾的字符串。如果字符串为空，则使用默认模型名称*/
    char device_name[WPS_MAX_DEVICE_NAME_LEN];   /*!< 设备名称，以空结尾的字符串。如果字符串为空，则使用默认设备名称*/
} wps_factory_information_t;

typedef struct {
    wps_type_t wps_type;
    wps_factory_information_t factory_info;
} esp_wps_config_t;

#define WPS_CONFIG_INIT_DEFAULT(type) { \
    .wps_type = type, \
    .factory_info = {   \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_STR(manufacturer, "ESPRESSIF")  \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_STR(model_number, "ESP32")  \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_STR(model_name, "ESPRESSIF IOT")  \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_STR(device_name, "ESP STATION")  \
    }  \
}

/**
  * @brief     启用Wi-Fi WPS功能。
  *
  * @attention WPS只能在启用ESP32工作站时使用。
  *
  * @param     wps_type_t wps_type：wps类型，目前仅支持wps_type_PBC和wps_type_PIN
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_WIFI_WPS_TYPE:WPS类型无效
  *          -ESP_ERR_WIFI_WPS_MODE：WIFI未处于站模式或嗅探器模式打开
  *          -ESP_FAIL:wps初始化失败
  */
esp_err_t esp_wifi_wps_enable(const esp_wps_config_t *config);

/**
  * @brief  禁用Wi-Fi WPS功能并释放其占用的资源。
  *
  * @param  null
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_WIFI_WPS_MODE：WIFI未处于站模式或嗅探器模式打开
  */
esp_err_t esp_wifi_wps_disable(void);

/**
  * @brief     WPS开始工作。
  *
  * @attention WPS只能在启用ESP32工作站时使用。
  *
  * @param     timeout_ms ：API返回前的最大阻塞时间。
  *          -0：非阻塞
  *          -1~120000：阻塞时间（IDF v1.0不支持）
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_WIFI_WPS_TYPE:WPS类型无效
  *          -ESP_ERR_WIFI_WPS_MODE：WIFI未处于站模式或嗅探器模式打开
  *          -ESP_ERR_WIFI_WPS_SM:WPS状态机未初始化
  *          -ESP_FAIL:wps初始化失败
  */
esp_err_t esp_wifi_wps_start(int timeout_ms);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ESP_WPS_H__ */

