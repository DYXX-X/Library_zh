// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#ifndef _MQTT_SUPPORTED_FEATURES_H_
#define _MQTT_SUPPORTED_FEATURES_H_

#if __has_include("esp_idf_version.h")
#include "esp_idf_version.h"
#endif

/**
 * @brief 此标头定义了支持的IDF特性，mqtt模块可以根据ESP-IDF的特定版本使用这些特性。如果找不到“esp_idf_version.h”，则将禁用所有其他功能
 */

#ifdef ESP_IDF_VERSION

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(3, 3, 0)
// 3.3支持的功能
#define MQTT_SUPPORTED_FEATURE_EVENT_LOOP
#define MQTT_SUPPORTED_FEATURE_SKIP_CRT_CMN_NAME_CHECK
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 0, 0)
// 4.0支持的功能
#define MQTT_SUPPORTED_FEATURE_WS_SUBPROTOCOL
#define MQTT_SUPPORTED_FEATURE_TRANSPORT_ERR_REPORTING
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 1, 0)
// 4.1中支持的功能
#define MQTT_SUPPORTED_FEATURE_PSK_AUTHENTICATION
#define MQTT_SUPPORTED_FEATURE_DER_CERTIFICATES
#define MQTT_SUPPORTED_FEATURE_ALPN
#define MQTT_SUPPORTED_FEATURE_CLIENT_KEY_PASSWORD
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)
// 4.2中支持的功能
#define MQTT_SUPPORTED_FEATURE_SECURE_ELEMENT
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 3, 0)
// 4.3中支持的功能
#define MQTT_SUPPORTED_FEATURE_DIGITAL_SIGNATURE
#define MQTT_SUPPORTED_FEATURE_TRANSPORT_SOCK_ERRNO_REPORTING
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 4, 0)
// 4.4中支持的功能
#define MQTT_SUPPORTED_FEATURE_CERTIFICATE_BUNDLE
#endif

#endif /* ESP_IDF_VERSION */
#endif // _MQTT_SUPPORTED_FEATURES_H_

