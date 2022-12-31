/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef __ESP_INTERFACE_H__
#define __ESP_INTERFACE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_IF_WIFI_STA = 0,     /**<ESP32站接口*/
    ESP_IF_WIFI_AP,          /**<ESP32软AP接口*/
    ESP_IF_ETH,              /**<ESP32以太网接口*/
    ESP_IF_MAX
} esp_interface_t;

#ifdef __cplusplus
}
#endif


#endif /* __ESP_INTERFACE_TYPES_H__ */

