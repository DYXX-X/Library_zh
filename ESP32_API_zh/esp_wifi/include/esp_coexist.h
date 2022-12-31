/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_COEXIST_H__
#define __ESP_COEXIST_H__

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief coex偏好值
 */
typedef enum {
    ESP_COEX_PREFER_WIFI = 0,       /*!< 相比WiFi，WiFi将有更多机会使用RF*/
    ESP_COEX_PREFER_BT,             /*!< 与蓝牙相比，蓝牙将有更多的机会使用RF*/
    ESP_COEX_PREFER_BALANCE,        /*!< 平衡WiFi和蓝牙*/
    ESP_COEX_PREFER_NUM,            /*!< 首选值编号*/
} esp_coex_prefer_t;

typedef enum {
    EXTERN_COEX_WIRE_1 = 0,
    EXTERN_COEX_WIRE_2,
    EXTERN_COEX_WIRE_3,
    EXTERN_COEX_WIRE_NUM,
} external_coex_wire_t;

/**
 * @brief coex状态类型
 */
typedef enum {
    ESP_COEX_ST_TYPE_WIFI = 0,
    ESP_COEX_ST_TYPE_BLE,
    ESP_COEX_ST_TYPE_BT,
} esp_coex_status_type_t;

/**
 * @brief 外腔gpio pti
 */
typedef struct {
    int32_t in_pin0;
    int32_t in_pin1;
    int32_t out_pin0;
} esp_external_coex_gpio_set_t;

/**
 * @brief 外腔pti水平
 */
typedef enum {
    EXTERN_COEX_PTI_MID = 0,
    EXTERN_COEX_PTI_HIGH,
    EXTERN_COEX_PTI_NUM,
} esp_coex_pti_level_t;

/**
 * @brief 外腔pti
 */
typedef struct {
    uint32_t in_pti1;
    uint32_t in_pti2;
    uint32_t in_pti3;
    uint32_t out_pti1;
    uint32_t out_pti2;
    uint32_t out_pti3;
} esp_external_coex_pti_set_t;

#define ESP_COEX_BLE_ST_MESH_CONFIG        0x08
#define ESP_COEX_BLE_ST_MESH_TRAFFIC       0x10
#define ESP_COEX_BLE_ST_MESH_STANDBY       0x20

#define ESP_COEX_BT_ST_A2DP_STREAMING      0x10
#define ESP_COEX_BT_ST_A2DP_PAUSED         0x20

/**
 * @brief 获取软件共存版本字符串
 *
 * @return ：版本字符串
 */
const char *esp_coex_version_get(void);

/**
 * @deprecated 请改用esp_coex_status_bit_set（）和esp_coex_status_bit_clear（）。设置性能的共存偏好例如，如果更喜欢蓝牙，那么它将使A2DP（通过经典bt播放音频）在wifi运行时更加流畅。如果更喜欢wifi，它会做类似于蓝牙的事情。默认情况下，它倾向于平衡。
 *
 *  @param prefer ：首选枚举值
 *  @return ：ESP_OK-成功，其他-失败
 */
esp_err_t esp_coex_preference_set(esp_coex_prefer_t prefer);

/**
 * @brief 设置coex schm状态
 * @param type : WIFI/BLE/BT
 * @param status : WIFI/BLE/BT STATUS
 * @return ：ESP_OK-成功，其他-失败
 */
esp_err_t esp_coex_status_bit_set(esp_coex_status_type_t type, uint32_t status);

/**
 * @brief 清除coex schm状态
 * @param type : WIFI/BLE/BT
 * @param status : WIFI/BLE/BT STATUS
 * @return ：ESP_OK-成功，其他-失败
 */
esp_err_t esp_coex_status_bit_clear(esp_coex_status_type_t type, uint32_t status);

#if CONFIG_EXTERNAL_COEX_ENABLE
/**
 * @brief 设置gpio引脚和相应的pti级别，启动外部coex。
 * @param wire_type ：选择整个外部coex gpio编号。
 * @param gpio_pin ：gpio要选择的引脚号。
 * @return ：ESP_OK-成功，其他-失败
 */
esp_err_t esp_enable_extern_coex_gpio_pin(external_coex_wire_t wire_type,
                    esp_external_coex_gpio_set_t gpio_pin);

esp_err_t esp_disable_extern_coex_gpio_pin();
#endif

#ifdef __cplusplus
}
#endif


#endif /* __ESP_COEXIST_H__ */

