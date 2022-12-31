/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief Bluetooth Mesh Light客户端模型API。
 */

#ifndef _ESP_BLE_MESH_LIGHTING_MODEL_API_H_
#define _ESP_BLE_MESH_LIGHTING_MODEL_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def    ESP_BLE_MESH_MODEL_LIGHT_LIGHTNESS_CLI
 *
 *  @brief  定义新的LightLightness客户端模型。
 *
 *  @note   需要为应用程序需要在其上具有LightLightness客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建Light Lightness客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_LIGHTNESS_CLI(cli_pub, cli_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI,   \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_CTL_CLI
 *
 *  @brief  定义新的轻型CTL客户端模型。
 *
 *  @note   需要为应用程序需要在其上具有轻型CTL客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建轻型CTL客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_CTL_CLI(cli_pub, cli_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_CLI,     \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_HSL_CLI
 *
 *  @brief  定义新的轻型HSL客户端模型。
 *
 *  @note   需要为应用程序需要具有轻型HSL客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的轻型HSL客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_HSL_CLI(cli_pub, cli_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_CLI,     \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_XYL_CLI
 *
 *  @brief  定义新的Light xyL客户端模型。
 *
 *  @note   需要为应用程序需要具有Light xyL客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的Light xyL客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_XYL_CLI(cli_pub, cli_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_CLI,     \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_LC_CLI
 *
 *  @brief  定义新的轻型LC客户端模型。
 *
 *  @note   需要为应用程序需要具有轻型LC客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的轻型LC客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_LC_CLI(cli_pub, cli_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_LC_CLI,     \
                    NULL, cli_pub, cli_data)

/**
 *  @brief Bluetooth Mesh Light Lightness客户端模型获取和设置参数结构。
 */

/**灯光亮度设置参数*/
typedef struct {
    bool     op_en;        /*!< 指示是否包含可选参数*/
    uint16_t lightness;    /*!< 灯光亮度实际状态目标值*/
    uint8_t  tid;          /*!< 事务ID*/
    uint8_t  trans_time;   /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;        /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_lightness_set_t;

/**光亮度线性集的参数*/
typedef struct {
    bool     op_en;        /*!< 指示是否包含可选参数*/
    uint16_t lightness;    /*!< 光亮度线性状态目标值*/
    uint8_t  tid;          /*!< 事务ID*/
    uint8_t  trans_time;   /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;        /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_lightness_linear_set_t;

/**灯光亮度默认设置参数*/
typedef struct {
    uint16_t lightness;    /*!< “灯光亮度默认”状态的值*/
} esp_ble_mesh_light_lightness_default_set_t;

/**灯光亮度范围设置参数*/
typedef struct {
    uint16_t range_min;    /*!< 亮度范围状态的最小范围字段值*/
    uint16_t range_max;    /*!< 灯光亮度范围状态的范围最大字段值*/
} esp_ble_mesh_light_lightness_range_set_t;

/**灯光CTL设置参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t ctl_lightness;    /*!< 灯光ctl亮度状态目标值*/
    uint16_t ctl_temperatrue;  /*!< 灯光ctl温度状态目标值*/
    int16_t  ctl_delta_uv;     /*!< 光ctl delta UV状态的目标值*/
    uint8_t  tid;              /*!< 事务ID*/
    uint8_t  trans_time;       /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;            /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_ctl_set_t;

/**灯光CTL温度设置参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t ctl_temperatrue;  /*!< 灯光ctl温度状态目标值*/
    int16_t  ctl_delta_uv;     /*!< 光ctl delta UV状态的目标值*/
    uint8_t  tid;              /*!< 事务ID*/
    uint8_t  trans_time;       /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;            /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_ctl_temperature_set_t;

/**灯光CTL温度范围设置参数*/
typedef struct {
    uint16_t range_min;        /*!< 温度范围值最小光场ctl温度范围状态*/
    uint16_t range_max;        /*!< 温度范围值最大光场ctl温度范围状态*/
} esp_ble_mesh_light_ctl_temperature_range_set_t;

/**灯光CTL默认设置的参数*/
typedef struct {
    uint16_t lightness;        /*!< 灯光亮度默认状态的值*/
    uint16_t temperature;      /*!< 灯光温度默认状态值*/
    int16_t  delta_uv;         /*!< 光增量UV默认状态的值*/
} esp_ble_mesh_light_ctl_default_set_t;

/**轻型HSL机组参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t hsl_lightness;    /*!< 轻hsl亮度状态目标值*/
    uint16_t hsl_hue;          /*!< 灯光hsl色调状态的目标值*/
    uint16_t hsl_saturation;   /*!< 光hsl饱和状态的目标值*/
    uint8_t  tid;              /*!< 事务ID*/
    uint8_t  trans_time;       /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;            /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_hsl_set_t;

/**光HSL色调集参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t hue;              /*!< 灯光hsl色调状态的目标值*/
    uint8_t  tid;              /*!< 事务ID*/
    uint8_t  trans_time;       /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;            /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_hsl_hue_set_t;

/**轻型HSL饱和设置参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t saturation;       /*!< 灯光hsl色调状态的目标值*/
    uint8_t  tid;              /*!< 事务ID*/
    uint8_t  trans_time;       /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;            /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_hsl_saturation_set_t;

/**灯光HSL默认设置参数*/
typedef struct {
    uint16_t lightness;        /*!< 灯光亮度默认状态的值*/
    uint16_t hue;              /*!< 灯光色调默认状态的值*/
    uint16_t saturation;       /*!< 光饱和度默认状态的值*/
} esp_ble_mesh_light_hsl_default_set_t;

/**轻型HSL范围设置参数*/
typedef struct {
    uint16_t hue_range_min;        /*!< 光hsl色域状态的色域最小值*/
    uint16_t hue_range_max;        /*!< 光hsl色域状态的色域最大值*/
    uint16_t saturation_range_min; /*!< 光hsl饱和范围状态的饱和范围最小场值*/
    uint16_t saturation_range_max; /*!< 光hsl饱和范围状态的饱和范围最大场值*/
} esp_ble_mesh_light_hsl_range_set_t;

/**Light xyL集合的参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t xyl_lightness;    /*!< 灯光xyL亮度状态的目标值*/
    uint16_t xyl_x;            /*!< 灯光xyL x状态的目标值*/
    uint16_t xyl_y;            /*!< 灯光xyL y状态的目标值*/
    uint8_t  tid;              /*!< 事务标识符*/
    uint8_t  trans_time;       /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;            /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_xyl_set_t;

/**灯光xyL默认设置的参数*/
typedef struct {
    uint16_t lightness;        /*!< “灯光亮度默认”状态的值*/
    uint16_t xyl_x;            /*!< 灯光xyL x默认状态的值*/
    uint16_t xyl_y;            /*!< 灯光xyL y默认状态的值*/
} esp_ble_mesh_light_xyl_default_set_t;

/**灯光xyL范围设置参数*/
typedef struct {
    uint16_t xyl_x_range_min;  /*!< 灯光xyL x范围状态的xyL x Range Min字段的值*/
    uint16_t xyl_x_range_max;  /*!< 灯光xyL x范围状态的xyL x Range Max字段的值*/
    uint16_t xyl_y_range_min;  /*!< 灯光xyL y范围状态的xyL y Range Min字段的值*/
    uint16_t xyl_y_range_max;  /*!< 灯光xyL y范围状态的xyL y Range Max字段的值*/
} esp_ble_mesh_light_xyl_range_set_t;

/**轻型LC模式集参数*/
typedef struct {
    uint8_t mode;              /*!< 轻LC模式状态的目标值*/
} esp_ble_mesh_light_lc_mode_set_t;

/**轻型LC OM集参数*/
typedef struct {
    uint8_t mode;              /*!< 轻型LC占用模式状态的目标值*/
} esp_ble_mesh_light_lc_om_set_t;

/**灯光LC灯光开关参数*/
typedef struct {
    bool    op_en;             /*!< 指示是否包含可选参数*/
    uint8_t light_onoff;       /*!< Light LC Light OnOff状态的目标值*/
    uint8_t tid;               /*!< 事务标识符*/
    uint8_t trans_time;        /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;             /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_light_lc_light_onoff_set_t;

/**轻LC特性参数获取*/
typedef struct {
    uint16_t property_id;      /*!< 标识轻型LC属性的属性ID*/
} esp_ble_mesh_light_lc_property_get_t;

/**轻型LC属性集的参数*/
typedef struct {
    uint16_t property_id;      /*!< 标识轻型LC属性的属性ID*/
    struct net_buf_simple *property_value;  /*!< 轻型LC属性的原始值*/
} esp_ble_mesh_light_lc_property_set_t;

/**
 * @brief 照明客户端模型获取消息联合
 */
typedef union {
    esp_ble_mesh_light_lc_property_get_t           lc_property_get;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_GET*/
} esp_ble_mesh_light_client_get_state_t;

/**
 * @brief 照明客户端模型集消息联合
 */
typedef union {
    esp_ble_mesh_light_lightness_set_t             lightness_set;               /*!< 对于ESP_BLE_MESH_MODE_OP_LIGHT_LIGHTNESS_SET和ESP_BLE-MESH_MODEL_OP_LIGHT_LIGHTNESS_SET_UNACK*/
    esp_ble_mesh_light_lightness_linear_set_t      lightness_linear_set;        /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNES_LINEAR_SET和ESP_BLE_MESH_MODE_OP_LIGHT_LIGHTNESS_LINEAR_SET_UNACK*/
    esp_ble_mesh_light_lightness_default_set_t     lightness_default_set;       /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_SET和ESP_BLE_MESH_MODE_OP_LIGHT_LIGHTNESS_DEFAULT _SET_UNACK*/
    esp_ble_mesh_light_lightness_range_set_t       lightness_range_set;         /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_SET和ESP_BLE_MESH_MODE_OP_LIGHT_LIGHTNESS_RANGE_SET_UNACK*/
    esp_ble_mesh_light_ctl_set_t                   ctl_set;                     /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_SET和ESP_BLE_MESH_MODE_OP_LIGHT_CTL_SET_UNACK*/
    esp_ble_mesh_light_ctl_temperature_set_t       ctl_temperature_set;         /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_SET和ESP_BLE_MESH_MODE_OP_LIGHT_CTL_TEMPERATURE_SET_UNACK*/
    esp_ble_mesh_light_ctl_temperature_range_set_t ctl_temperature_range_set;   /*!< 对于ESP_BLE_MESH_MODE_OP_LIGHT_CTL_TEMPERATURE_RANGE_SET和ESP_BLE_MESH_MODL_OP_LIGHT _CTL_TEMPERATURE_RANGE_SET_UNACK*/
    esp_ble_mesh_light_ctl_default_set_t           ctl_default_set;             /*!< 对于ESP_BLE_MESH_MODE_OP_LIGHT_CTL_DEFAULT_SET和ESP_BLE-MESH_MODEL_OP_LIGHT_CTL_DEFAULT_SET_UNACK*/
    esp_ble_mesh_light_hsl_set_t                   hsl_set;                     /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SET和ESP_BLE_MESH_MODE_OP_LIGHT_HSL_SET_UNACK*/
    esp_ble_mesh_light_hsl_hue_set_t               hsl_hue_set;                 /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_UE_SET和ESP_BLE_MESH_MODE_OP_LIGHT_HSL_HUE_SET_UNACK*/
    esp_ble_mesh_light_hsl_saturation_set_t        hsl_saturation_set;          /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_SL_SATURATION_SET和ESP_BLE-MESH_MODE_OP_LIGHT_HSL_SATULATION_SET_NACK*/
    esp_ble_mesh_light_hsl_default_set_t           hsl_default_set;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_SL_DEFAULT_SET和ESP_BLE_MESH_MODE_OP_LIGHT_HSL_DEFAUT_SET_UNACK*/
    esp_ble_mesh_light_hsl_range_set_t             hsl_range_set;               /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_SET和ESP_BLE_MESH_MODE_OP_LIGHT_HSL_RANGE_SET_UNACK*/
    esp_ble_mesh_light_xyl_set_t                   xyl_set;                     /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_SET和ESP_BLE_MESH_MODE_OP_LIGHT_XYL_SET_UNACK*/
    esp_ble_mesh_light_xyl_default_set_t           xyl_default_set;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_SET和ESP_BLE-MESH_MODE_OP_LIGHT_XYL_DEFUELT_SET_UNACK*/
    esp_ble_mesh_light_xyl_range_set_t             xyl_range_set;               /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_SET和ESP_BLE-MESH_MODE_OP_LIGHT_XYL_RANGE _SET_UNACK*/
    esp_ble_mesh_light_lc_mode_set_t               lc_mode_set;                 /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_SET和ESP_BLE_MESH_MODE_OP_LIGHT_LC_MODE_SET_UNACK*/
    esp_ble_mesh_light_lc_om_set_t                 lc_om_set;                   /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_SET和ESP_BLE_MESH_MODEL _OP_LIGHT _LC_OM_SET_UNACK*/
    esp_ble_mesh_light_lc_light_onoff_set_t        lc_light_onoff_set;          /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_SET和ESP_BLE_MESH_MODE_OP_LIGHT_LC_LIGHT_NOFF_SET_UNACK*/
    esp_ble_mesh_light_lc_property_set_t           lc_property_set;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_SET和ESP_BLE_MESH_MODE_OP_LIGHT_LC_PROPERTY_SET_NACK*/
} esp_ble_mesh_light_client_set_state_t;

/**
 *  @brief Bluetooth Mesh Light Lightness客户端模型获取和设置回调参数结构。
 */

/**灯光亮度状态参数*/
typedef struct {
    bool     op_en;                /*!< 指示是否包含可选参数*/
    uint16_t present_lightness;    /*!< 灯光亮度实际状态的当前值*/
    uint16_t target_lightness;     /*!< 灯光亮度实际状态目标值（可选）*/
    uint8_t  remain_time;          /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_lightness_status_cb_t;

/**光亮度线性状态参数*/
typedef struct {
    bool     op_en;                /*!< 指示是否包含可选参数*/
    uint16_t present_lightness;    /*!< 光亮度线性状态的当前值*/
    uint16_t target_lightness;     /*!< 光亮度线性状态目标值（可选）*/
    uint8_t  remain_time;          /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_lightness_linear_status_cb_t;

/**灯光亮度上次状态参数*/
typedef struct {
    uint16_t lightness;            /*!< “Light Lightness Last”状态的值*/
} esp_ble_mesh_light_lightness_last_status_cb_t;

/**灯光亮度默认状态参数*/
typedef struct {
    uint16_t lightness;            /*!< 灯光亮度默认状态的值*/
} esp_ble_mesh_light_lightness_default_status_cb_t;

/**灯光亮度范围状态参数*/
typedef struct {
    uint8_t  status_code;          /*!< 请求消息的状态代码*/
    uint16_t range_min;            /*!< 亮度范围状态的最小范围字段值*/
    uint16_t range_max;            /*!< 灯光亮度范围状态的范围最大字段值*/
} esp_ble_mesh_light_lightness_range_status_cb_t;

/**灯光CTL状态参数*/
typedef struct {
    bool     op_en;                    /*!< 指示是否包含可选参数*/
    uint16_t present_ctl_lightness;    /*!< 灯光ctl亮度状态的当前值*/
    uint16_t present_ctl_temperature;  /*!< 灯光ctl温度状态的当前值*/
    uint16_t target_ctl_lightness;     /*!< 灯光ctl亮度状态目标值（可选）*/
    uint16_t target_ctl_temperature;   /*!< 光ctl温度状态目标值（C.1）*/
    uint8_t  remain_time;              /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_ctl_status_cb_t;

/**灯光CTL温度状态参数*/
typedef struct {
    bool     op_en;                    /*!< 指示是否包含可选参数*/
    uint16_t present_ctl_temperature;  /*!< 灯光ctl温度状态的当前值*/
    uint16_t present_ctl_delta_uv;     /*!< 光ctl delta UV状态的电流值*/
    uint16_t target_ctl_temperature;   /*!< 灯光ctl温度状态目标值（可选）*/
    uint16_t target_ctl_delta_uv;      /*!< 光ctlδUV状态的目标值（C.1）*/
    uint8_t  remain_time;              /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_ctl_temperature_status_cb_t;

/**灯光CTL温度范围状态参数*/
typedef struct {
    uint8_t  status_code;      /*!< 请求消息的状态代码*/
    uint16_t range_min;        /*!< 温度范围值最小光场ctl温度范围状态*/
    uint16_t range_max;        /*!< 温度范围值最大光场ctl温度范围状态*/
} esp_ble_mesh_light_ctl_temperature_range_status_cb_t;

/**灯光CTL默认状态参数*/
typedef struct {
    uint16_t lightness;        /*!< 灯光亮度默认状态的值*/
    uint16_t temperature;      /*!< 灯光温度默认状态值*/
    int16_t  delta_uv;         /*!< 光增量UV默认状态的值*/
} esp_ble_mesh_light_ctl_default_status_cb_t;

/**轻型HSL状态参数*/
typedef struct {
    bool     op_en;            /*!< 指示是否包含可选参数*/
    uint16_t hsl_lightness;    /*!< 灯光hsl亮度状态的当前值*/
    uint16_t hsl_hue;          /*!< 灯光hsl色调状态的当前值*/
    uint16_t hsl_saturation;   /*!< 灯hsl饱和状态的当前值*/
    uint8_t  remain_time;      /*!< 完成状态转换的时间（可选）*/
} esp_ble_mesh_light_hsl_status_cb_t;

/**轻型HSL目标状态参数*/
typedef struct {
    bool  op_en;                    /*!< 指示是否包含可选参数*/
    uint16_t hsl_lightness_target;     /*!< 轻hsl亮度状态目标值*/
    uint16_t hsl_hue_target;           /*!< 灯光hsl色调状态的目标值*/
    uint16_t hsl_saturation_target;    /*!< 光hsl饱和状态的目标值*/
    uint8_t  remain_time;              /*!< 完成状态转换的时间（可选）*/
} esp_ble_mesh_light_hsl_target_status_cb_t;

/**光HSL色调状态参数*/
typedef struct {
    bool     op_en;        /*!< 指示是否包含可选参数*/
    uint16_t present_hue;  /*!< 灯光hsl色调状态的当前值*/
    uint16_t target_hue;   /*!< 灯光hsl色调状态的目标值（可选）*/
    uint8_t  remain_time;  /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_hsl_hue_status_cb_t;

/**轻型HSL饱和状态参数*/
typedef struct {
    bool     op_en;                /*!< 指示是否包含可选参数*/
    uint16_t present_saturation;   /*!< 灯hsl饱和状态的当前值*/
    uint16_t target_saturation;    /*!< 光hsl饱和状态的目标值（可选）*/
    uint8_t  remain_time;          /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_hsl_saturation_status_cb_t;

/**灯光HSL默认状态参数*/
typedef struct {
    uint16_t lightness;    /*!< 灯光亮度默认状态的值*/
    uint16_t hue;          /*!< 灯光色调默认状态的值*/
    uint16_t saturation;   /*!< 光饱和度默认状态的值*/
} esp_ble_mesh_light_hsl_default_status_cb_t;

/**轻型HSL范围状态参数*/
typedef struct {
    uint8_t  status_code;          /*!< 请求消息的状态代码*/
    uint16_t hue_range_min;        /*!< 光hsl色域状态的色域最小值*/
    uint16_t hue_range_max;        /*!< 光hsl色域状态的色域最大值*/
    uint16_t saturation_range_min; /*!< 光hsl饱和范围状态的饱和范围最小场值*/
    uint16_t saturation_range_max; /*!< 光hsl饱和范围状态的饱和范围最大场值*/
} esp_ble_mesh_light_hsl_range_status_cb_t;

/**灯光xyL状态参数*/
typedef struct {
    bool     op_en;                /*!< 指示是否包含可选参数*/
    uint16_t xyl_lightness;        /*!< 灯光xyL亮度状态的当前值*/
    uint16_t xyl_x;                /*!< Light xyL x状态的当前值*/
    uint16_t xyl_y;                /*!< Light xyL y状态的当前值*/
    uint8_t  remain_time;          /*!< 完成状态转换的时间（可选）*/
} esp_ble_mesh_light_xyl_status_cb_t;

/**灯光xyL目标状态参数*/
typedef struct {
    bool     op_en;                /*!< 指示是否包含可选参数*/
    uint16_t target_xyl_lightness; /*!< 灯光xyL亮度状态的目标值*/
    uint16_t target_xyl_x;         /*!< 灯光xyL x状态的目标值*/
    uint16_t target_xyl_y;         /*!< 灯光xyL y状态的目标值*/
    uint8_t  remain_time;          /*!< 完成状态转换的时间（可选）*/
} esp_ble_mesh_light_xyl_target_status_cb_t;

/**灯光xyL默认状态参数*/
typedef struct {
    uint16_t lightness;        /*!< “灯光亮度默认”状态的值*/
    uint16_t xyl_x;            /*!< 灯光xyL x默认状态的值*/
    uint16_t xyl_y;            /*!< 灯光xyL y默认状态的值*/
} esp_ble_mesh_light_xyl_default_status_cb_t;

/**灯光xyL范围状态参数*/
typedef struct {
    uint8_t  status_code;      /*!< 请求消息的状态代码*/
    uint16_t xyl_x_range_min;  /*!< 灯光xyL x范围状态的xyL x Range Min字段的值*/
    uint16_t xyl_x_range_max;  /*!< 灯光xyL x范围状态的xyL x Range Max字段的值*/
    uint16_t xyl_y_range_min;  /*!< 灯光xyL y范围状态的xyL y Range Min字段的值*/
    uint16_t xyl_y_range_max;  /*!< 灯光xyL y范围状态的xyL y Range Max字段的值*/
} esp_ble_mesh_light_xyl_range_status_cb_t;

/**轻型LC模式状态参数*/
typedef struct {
    uint8_t mode;              /*!< 轻LC模式状态的当前值*/
} esp_ble_mesh_light_lc_mode_status_cb_t;

/**轻型LC OM状态参数*/
typedef struct {
    uint8_t mode;              /*!< 轻型LC占用模式状态的当前值*/
} esp_ble_mesh_light_lc_om_status_cb_t;

/**灯LC灯开关状态参数*/
typedef struct {
    bool    op_en;                 /*!< 指示是否包含可选参数*/
    uint8_t present_light_onoff;   /*!< Light LC Light OnOff状态的当前值*/
    uint8_t target_light_onoff;    /*!< Light LC Light OnOff状态的目标值（可选）*/
    uint8_t remain_time;           /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_light_lc_light_onoff_status_cb_t;

/**轻型LC性能状态参数*/
typedef struct {
    uint16_t property_id;      /*!< 标识轻型LC属性的属性ID*/
    struct net_buf_simple *property_value;  /*!< 轻型LC属性的原始值*/
} esp_ble_mesh_light_lc_property_status_cb_t;

/**
 * @brief 照明客户端模型接收到消息联合
 */
typedef union {
    esp_ble_mesh_light_lightness_status_cb_t             lightness_status;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNES_STATUS*/
    esp_ble_mesh_light_lightness_linear_status_cb_t      lightness_linear_status;      /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNES_LINEAR_STATUS*/
    esp_ble_mesh_light_lightness_last_status_cb_t        lightness_last_status;        /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNES_LAST_STATUS*/
    esp_ble_mesh_light_lightness_default_status_cb_t     lightness_default_status;     /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_STATUS*/
    esp_ble_mesh_light_lightness_range_status_cb_t       lightness_range_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_STATUS*/
    esp_ble_mesh_light_ctl_status_cb_t                   ctl_status;                   /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_STATUS*/
    esp_ble_mesh_light_ctl_temperature_status_cb_t       ctl_temperature_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_STATUS*/
    esp_ble_mesh_light_ctl_temperature_range_status_cb_t ctl_temperature_range_status; /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_STATUS*/
    esp_ble_mesh_light_ctl_default_status_cb_t           ctl_default_status;           /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFULT_STATUS*/
    esp_ble_mesh_light_hsl_status_cb_t                   hsl_status;                   /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_STATUS*/
    esp_ble_mesh_light_hsl_target_status_cb_t            hsl_target_status;            /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_TARGET_STATUS*/
    esp_ble_mesh_light_hsl_hue_status_cb_t               hsl_hue_status;               /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_STATUS*/
    esp_ble_mesh_light_hsl_saturation_status_cb_t        hsl_saturation_status;        /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_STATUS*/
    esp_ble_mesh_light_hsl_default_status_cb_t           hsl_default_status;           /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_SL_DEFAULT_STATUS*/
    esp_ble_mesh_light_hsl_range_status_cb_t             hsl_range_status;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_STATUS*/
    esp_ble_mesh_light_xyl_status_cb_t                   xyl_status;                   /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_STATUS*/
    esp_ble_mesh_light_xyl_target_status_cb_t            xyl_target_status;            /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_TARGET_STATUS*/
    esp_ble_mesh_light_xyl_default_status_cb_t           xyl_default_status;           /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_STATUS*/
    esp_ble_mesh_light_xyl_range_status_cb_t             xyl_range_status;             /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_STATUS*/
    esp_ble_mesh_light_lc_mode_status_cb_t               lc_mode_status;               /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_STATUS*/
    esp_ble_mesh_light_lc_om_status_cb_t                 lc_om_status;                 /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_STATUS*/
    esp_ble_mesh_light_lc_light_onoff_status_cb_t        lc_light_onoff_status;        /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_STATUS*/
    esp_ble_mesh_light_lc_property_status_cb_t           lc_property_status;           /*!< 对于ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_STATUS*/
} esp_ble_mesh_light_client_status_cb_t;

/**照明客户端模型回调参数*/
typedef struct {
    int error_code;                                     /*!< 适当的错误代码*/
    esp_ble_mesh_client_common_param_t   *params;       /*!< 客户端公用参数。*/
    esp_ble_mesh_light_client_status_cb_t status_cb;    /*!< 灯光状态消息回调值*/
} esp_ble_mesh_light_client_cb_param_t;

/**此枚举值是照明客户端模型的事件*/
typedef enum {
    ESP_BLE_MESH_LIGHT_CLIENT_GET_STATE_EVT,
    ESP_BLE_MESH_LIGHT_CLIENT_SET_STATE_EVT,
    ESP_BLE_MESH_LIGHT_CLIENT_PUBLISH_EVT,
    ESP_BLE_MESH_LIGHT_CLIENT_TIMEOUT_EVT,
    ESP_BLE_MESH_LIGHT_CLIENT_EVT_MAX,
} esp_ble_mesh_light_client_cb_event_t;

/**
 *  @brief Bluetooth Mesh Light客户端模型功能。
 */

/**
 * @brief   照明客户端模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_light_client_cb_t)(esp_ble_mesh_light_client_cb_event_t event,
                                                esp_ble_mesh_light_client_cb_param_t *param);

/**
 * @brief       注册BLE Mesh Light客户端模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_light_client_callback(esp_ble_mesh_light_client_cb_t callback);

/**
 * @brief       使用轻型客户端模型获取消息获取轻型服务器模型状态的值。
 *
 * @note        如果您想知道此API接受的操作码和相应的含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_light_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   get_state: 指示灯指针获取消息值。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_light_client_get_state(esp_ble_mesh_client_common_param_t *params,
                                              esp_ble_mesh_light_client_get_state_t *get_state);

/**
 * @brief       使用轻型客户端模型设置消息设置轻型服务器模型状态的值。
 *
 * @note        如果您想知道此API接受的操作码和相应的含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_light_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   set_state: 指示灯设置消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_light_client_set_state(esp_ble_mesh_client_common_param_t *params,
                                              esp_ble_mesh_light_client_set_state_t *set_state);

/**
 * @brief 照明服务器模型相关上下文。
 */

/** @def    ESP_BLE_MESH_MODEL_LIGHT_LIGHTNESS_SRV
 *
 *  @brief  定义新的LightLightness服务器模型。
 *
 *  @note   1.Light Lightness Server模型扩展了Generic Power OnOff Server模型和Generic Level Server模型。当该模型出现在网元上时，相应的LightLightness Setup Server模型也应出现。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_lightness_srv_t的指针。
 *
 *  @return 新的LightLightness服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_LIGHTNESS_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_LIGHTNESS_SETUP_SRV
 *
 *  @brief  定义新的灯光亮度设置服务器模型。
 *
 *  @note   1.Light Lightness Setup Server模型扩展了Light Lightness Server模型和Generic Power OnOff Setup Server模型。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_lightness_setup_srv_t的指针。
 *
 *  @return 新建Light Lightness安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_LIGHTNESS_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_CTL_SRV
 *
 *  @brief  定义新的轻型CTL服务器模型。
 *
 *  @note   1.Light CTL Server模型扩展了Light Lightness Server模型。当该模型出现在元件上时，相应的灯光CTL温度服务器模型和相应的灯光控制设置服务器模型也应出现。2.该模型应支持模型发布和模型订阅。3.模型需要两个元素：主元素和温度元素。Temperature元素包含相应的Light CTL Temperature Server模型和绑定到Temperature元件上的Light CTL温度状态的Generic Level状态的实例。Temperature元素上的Light CTL Temperature状态与主元素上的Light CTL状态绑定。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_ctl_srv_t的指针。
 *
 *  @return 新建轻型CTL服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_CTL_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_CTL_SETUP_SRV
 *
 *  @brief  定义新的灯光CTL设置服务器模型。
 *
 *  @note   1.Light CTL设置服务器模型扩展了Light CTL服务器和Light Lightness设置服务器。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_ctl_setup_srv_t的指针。
 *
 *  @return 新建Light CTL安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_CTL_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_CTL_TEMP_SRV
 *
 *  @brief  定义新的灯光CTL温度服务器模型。
 *
 *  @note   1.Light CTL Temperature Server模型扩展了Generic Level Server模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_ctl_temp_srv_t的指针。
 *
 *  @return 新建轻型CTL温度服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_CTL_TEMP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_HSL_SRV
 *
 *  @brief  定义新的轻型HSL服务器模型。
 *
 *  @note   1.Light HSL Server模型扩展了Light Lightness Server模型。当该模型出现在元素上时，相应的Light HSL色调服务器模型、相应的Light HSL饱和度服务器模型和相应的Light HSML设置服务器模型也应出现。2.该模型应支持模型发布和模型订阅。3.模型需要三个元素：主元素、色调元素和饱和度元素。Hue元素包含相应的Light HSL Hue Server模型和绑定到Hue元素上的Light HSL-Hue状态的Generic Level状态的实例。Saturation元素包含相应的Light HSL Saturation Server模型和绑定到Saturation元件上Light HSL饱和状态的Generic Level状态的实例。色调元素上的光HSL色调状态与主元素上的灯HSL状态绑定，而饱和元素上的灯光HSL饱和状态与主元件上的灯光HSL状态绑定。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_hsl_srv_t的指针。
 *
 *  @return 新的轻型HSL服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_HSL_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_HSL_SETUP_SRV
 *
 *  @brief  定义新的Light HSL安装服务器模型。
 *
 *  @note   1.Light HSL设置服务器模型扩展了Light HSL服务器和Light Lightness设置服务器。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_hsl_setup_srv_t的指针。
 *
 *  @return 新的轻型HSL安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_HSL_SETUP_SRV(srv_pub, srv_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV,   \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_HSL_HUE_SRV
 *
 *  @brief  定义新的Light HSL色调服务器模型。
 *
 *  @note   1.轻型HSL色调服务器模型扩展了通用级别服务器模型。此模型与轻型HSL服务器模型相关联。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_hsl_hue_srv_t的指针。
 *
 *  @return 新的Light HSL Hue服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_HSL_HUE_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_HSL_SAT_SRV
 *
 *  @brief  定义新的轻型HSL饱和服务器模型。
 *
 *  @note   1.轻型HSL饱和服务器模型扩展了通用级别服务器模型。此模型与轻型HSL服务器模型相关联。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_hsl_sat_srv_t的指针。
 *
 *  @return 新的轻型HSL饱和服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_HSL_SAT_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_XYL_SRV
 *
 *  @brief  定义新的Light xyL服务器模型。
 *
 *  @note   1.Light xyL Server模型扩展了Light Lightness Server模型。当该模型出现在网元上时，相应的Light xyL Setup Server模型也应出现。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_xyl_srv_t的指针。
 *
 *  @return 新的Light xyL服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_XYL_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_XYL_SETUP_SRV
 *
 *  @brief  定义新的Light xyL安装服务器模型。
 *
 *  @note   1.Light xyL Setup Server模型扩展了Light xyL Server和Light Lightness Setup Server。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_xyl_setup_srv_t的指针。
 *
 *  @return 新建Light xyL安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_XYL_SETUP_SRV(srv_pub, srv_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV,   \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_LC_SRV
 *
 *  @brief  定义新的轻型LC服务器模型。
 *
 *  @note   1.Light LC（亮度控制）服务器模型扩展了Light Lightness Server模型和Generic OnOff Server模型。当该模型出现在网元上时，相应的Light LC Setup Server模型也应出现。2.该模型应支持模型发布和模型订阅。3.该模型可用于表示作为传感器服务器模型的客户端并通过定义的状态绑定来控制光亮度实际状态的元素。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_lc_srv_t的指针。
 *
 *  @return 新的轻型LC服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_LC_SRV(srv_pub, srv_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_LC_SRV,   \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_LIGHT_LC_SETUP_SRV
 *
 *  @brief  定义新的轻型LC安装服务器模型。
 *
 *  @note   1.Light LC（亮度控制）设置模型扩展了Light LC服务器模型。2.该模型应支持模型发布和模型订阅。3.此模型可用于配置轻型LC服务器模型的设置参数。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_light_lc_setup_srv_t的指针。
 *
 *  @return 新的轻型LC安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_LIGHT_LC_SETUP_SRV(srv_pub, srv_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_LIGHT_LC_SETUP_SRV,   \
                    NULL, srv_pub, srv_data)

/**灯光亮度状态参数*/
typedef struct {
    uint16_t lightness_linear;          /*!< “Light Lightness Linear”状态的当前值*/
    uint16_t target_lightness_linear;   /*!< “Light Lightness Linear”状态的目标值*/

    uint16_t lightness_actual;          /*!< 灯光亮度实际状态的当前值*/
    uint16_t target_lightness_actual;   /*!< “Light Lightness Actual”状态的目标值*/

    uint16_t lightness_last;            /*!< “Light Lightness Last”状态的值*/
    uint16_t lightness_default;         /*!< 灯光亮度默认状态的值*/

    uint8_t  status_code;               /*!< 设置灯光亮度范围状态的状态代码*/
    uint16_t lightness_range_min;       /*!< “灯光亮度范围”状态的最小值*/
    uint16_t lightness_range_max;       /*!< “灯光亮度范围”状态的最大值*/
} esp_ble_mesh_light_lightness_state_t;

/**Light Lightness服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向Lighting Lightness Server模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_lightness_state_t *state;    /*!< 灯光亮度状态参数*/
    esp_ble_mesh_last_msg_info_t last;              /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t actual_transition;  /*!< 状态转换参数*/
    esp_ble_mesh_state_transition_t linear_transition;  /*!< 状态转换参数*/
    int32_t tt_delta_lightness_actual;      /*!< 亮度实际状态转换的增量变化值*/
    int32_t tt_delta_lightness_linear;      /*!< 亮度线性状态转变的增量变化值*/
} esp_ble_mesh_light_lightness_srv_t;

/**Light Lightness设置服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向照明亮度设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_lightness_state_t *state;    /*!< 灯光亮度状态参数*/
} esp_ble_mesh_light_lightness_setup_srv_t;

/**灯光CTL状态参数*/
typedef struct {
    uint16_t lightness;             /*!< 灯光CTL亮度状态的当前值*/
    uint16_t target_lightness;      /*!< 灯光CTL亮度状态的目标值*/

    uint16_t temperature;           /*!< 灯光CTL温度状态的当前值*/
    uint16_t target_temperature;    /*!< 灯光CTL温度状态的目标值*/

    int16_t  delta_uv;              /*!< 灯光CTL Delta UV状态的当前值*/
    int16_t  target_delta_uv;       /*!< 灯光CTL Delta UV状态的目标值*/

    uint8_t  status_code;           /*!< 设置灯光CTL温度范围状态的状态代码*/
    uint16_t temperature_range_min; /*!< 灯光CTL温度范围状态的最小值*/
    uint16_t temperature_range_max; /*!< 灯光CTL温度范围状态的最大值*/

    uint16_t lightness_default;     /*!< 灯光亮度默认状态的值*/
    uint16_t temperature_default;   /*!< 灯光CTL温度默认状态的值*/
    int16_t  delta_uv_default;      /*!< 灯光CTL增量UV默认状态的值*/
} esp_ble_mesh_light_ctl_state_t;

/**轻型CTL服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明CTL服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_ctl_state_t *state;      /*!< 灯光CTL状态参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_lightness;     /*!< 亮度状态转变的Delta变化值*/
    int32_t tt_delta_temperature;   /*!< 温度状态转变的Delta变化值*/
    int32_t tt_delta_delta_uv;      /*!< Delta-uv状态转变的Delta-变化值*/
} esp_ble_mesh_light_ctl_srv_t;

/**Light CTL设置服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明CTL设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_ctl_state_t *state;      /*!< 灯光CTL状态参数*/
} esp_ble_mesh_light_ctl_setup_srv_t;

/**轻型CTL温度服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明CTL温度服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_ctl_state_t *state;      /*!< 灯光CTL状态参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_temperature;   /*!< 温度状态转变的Delta变化值*/
    int32_t tt_delta_delta_uv;      /*!< Delta-uv状态转变的Delta-变化值*/
} esp_ble_mesh_light_ctl_temp_srv_t;

/**轻型HSL状态参数*/
typedef struct {
    uint16_t lightness;             /*!< Light HSL Lightness状态的当前值*/
    uint16_t target_lightness;      /*!< Light HSL Lightness状态的目标值*/

    uint16_t hue;                   /*!< 光HSL色调状态的当前值*/
    uint16_t target_hue;            /*!< 灯光HSL色调状态的目标值*/

    uint16_t saturation;            /*!< 光HSL饱和状态的当前值*/
    uint16_t target_saturation;     /*!< 轻HSL饱和状态的目标值*/

    uint16_t lightness_default;     /*!< 灯光亮度默认状态的值*/
    uint16_t hue_default;           /*!< 灯光HSL色调默认状态的值*/
    uint16_t saturation_default;    /*!< Light HSL Saturation Default状态的值*/

    uint8_t  status_code;           /*!< 设置光HSL色调和饱和度范围状态的状态代码*/
    uint16_t hue_range_min;         /*!< 灯光HSL色调范围状态的最小值*/
    uint16_t hue_range_max;         /*!< 灯光HSL色调范围状态的最大值*/
    uint16_t saturation_range_min;  /*!< 轻HSL饱和状态的最小值*/
    uint16_t saturation_range_max;  /*!< 光HSL饱和状态的最大值*/
} esp_ble_mesh_light_hsl_state_t;

/**轻型HSL服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明HSL服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_hsl_state_t *state;      /*!< 轻型HSL状态参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_lightness;     /*!< 亮度状态转变的Delta变化值*/
    int32_t tt_delta_hue;           /*!< 色调状态转换的增量变化值*/
    int32_t tt_delta_saturation;    /*!< 饱和状态转变的Delta变化值*/
} esp_ble_mesh_light_hsl_srv_t;

/**轻型HSL安装服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明HSL设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_hsl_state_t *state;      /*!< 轻型HSL状态参数*/
} esp_ble_mesh_light_hsl_setup_srv_t;

/**Light HSL Hue服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明HSL色调服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_hsl_state_t *state;      /*!< 轻型HSL状态参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_hue;   /*!< 色调状态转换的增量变化值*/
} esp_ble_mesh_light_hsl_hue_srv_t;

/**轻型HSL饱和服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;    /*!< 指向照明HSL饱和服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_hsl_state_t *state;      /*!< 轻型HSL状态参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_saturation;    /*!< 饱和状态转变的Delta变化值*/
} esp_ble_mesh_light_hsl_sat_srv_t;

/**Light xyL状态参数*/
typedef struct {
    uint16_t lightness;         /*!< Light xyL Lightness状态的当前值*/
    uint16_t target_lightness;  /*!< Light xyL Lightness状态的目标值*/

    uint16_t x;                 /*!< Light xyL x状态的当前值*/
    uint16_t target_x;          /*!< Light xyL x状态的目标值*/

    uint16_t y;                 /*!< Light xyL y状态的当前值*/
    uint16_t target_y;          /*!< Light xyL y状态的目标值*/

    uint16_t lightness_default; /*!< 灯光亮度默认状态的值*/
    uint16_t x_default;         /*!< 灯光xyL x默认状态的值*/
    uint16_t y_default;         /*!< 灯光xyL y默认状态的值*/

    uint8_t  status_code;       /*!< 设置灯光xyL x和y范围状态的状态代码*/
    uint16_t x_range_min;       /*!< Light xyL x Range状态的最小值*/
    uint16_t x_range_max;       /*!< Light xyL x Range状态的最大值*/
    uint16_t y_range_min;       /*!< Light xyL y Range状态的最小值*/
    uint16_t y_range_max;       /*!< 灯光xyL y范围状态的最大值*/
} esp_ble_mesh_light_xyl_state_t;

/**Light xyL服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向Lighting xyL服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_xyl_state_t *state;      /*!< Light xyL状态参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_lightness; /*!< 亮度状态转变的Delta变化值*/
    int32_t tt_delta_x;         /*!< x状态转变的增量变化值*/
    int32_t tt_delta_y;         /*!< y状态转变的Delta变化值*/
} esp_ble_mesh_light_xyl_srv_t;

/**Light xyL安装服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向Lighting xyL安装服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_xyl_state_t *state;      /*!< Light xyL状态参数*/
} esp_ble_mesh_light_xyl_setup_srv_t;

/**轻LC状态参数*/
typedef struct {
    /**
     * 0b0控制器已关闭。
     * -已禁用具有“灯光亮度”状态的绑定。0b1控制器已打开。
     * -已启用具有“灯光亮度”状态的绑定。
     */
    uint32_t mode : 1,                  /*!< 轻LC模式状态的值*/
             occupancy_mode : 1,        /*!< 轻型LC占用模式状态的值*/
             light_onoff : 1,           /*!< Light LC Light OnOff状态的当前值*/
             target_light_onoff : 1,    /*!< Light LC Light OnOff状态的目标值*/
             occupancy : 1,             /*!< 轻型LC占用状态的值*/
             ambient_luxlevel : 24;     /*!< Light LC Ambient LuxLevel状态的值*/

    /**
     * 1.轻型LC线性输出=max（（Lightness Out）^2/65535，调节器输出）2.如果轻型LC模式状态设置为0b1，则启用绑定，并且在轻型LC线性输入状态更改后，应执行以下操作：轻型LC线性=轻型LC线性输出3.如果轻型LC状态设置为0 b0，绑定被禁用（即，在光LC线性输出状态改变时，不执行对光亮度线性状态的操作）。
     */
    uint16_t linear_output;     /*!< 光LC线性输出状态的值*/
} esp_ble_mesh_light_lc_state_t;

/**
 * 灯光属性状态的参数。光LC属性状态是确定光亮度控制器配置的读/写状态。每个状态由设备属性表示，并由轻LC属性消息控制。
 */
typedef struct {
    /**
     * 一种定时状态，在从占用传感器接收到传感器状态消息时，该状态确定改变灯LC占用状态的延迟。
     */
    uint32_t time_occupancy_delay;  /*!< 轻型LC时间占用延迟状态的值*/
    /**
     * 一种定时状态，用于确定受控灯光衰减到由灯光LC亮度开启状态确定的水平的时间。
     */
    uint32_t time_fade_on;      /*!< Light LC Time Fade On状态的值*/
    /**
     * 一种定时状态，用于确定受控灯光停留在由灯光LC亮度开启状态确定的水平的时间。
     */
    uint32_t time_run_on;       /*!< Light LC Time Run On状态的值*/
    /**
     * 一种定时状态，用于确定受控灯光从“灯光LC亮度开启”状态所确定的级别衰减到“灯光亮度延长”状态所决定的级别的时间。
     */
    uint32_t time_fade;         /*!< 灯光LC时间衰减状态的值*/
    /**
     * 一种定时状态，用于确定受控灯光停留在由灯光LC亮度延长状态确定的水平的时间。
     */
    uint32_t time_prolong;      /*!< 轻LC时间延长状态的值*/
    /**
     * 一种定时状态，当转换为自动时，该定时状态确定受控灯光从“灯光LC亮度延长”状态确定的级别衰减到“灯光LC灯光待机状态”确定的级别的时间。
     */
    uint32_t time_fade_standby_auto;    /*!< Light LC Time Fade Standby Auto状态的值*/
    /**
     * 一种定时状态，用于确定受控灯光从“灯光LC亮度延长”状态确定的级别衰减到“灯光LC灯光待机状态”确定的级别的时间。
     */
    uint32_t time_fade_standby_manual;  /*!< Light LC Time Fade Standby Manual状态的值*/

    /**
     * 一种亮度状态，用于确定“占用”和“运行”内部控制器状态下的感知灯光亮度。
     */
    uint16_t lightness_on;          /*!< Light LC Lightness On状态的值*/
    /**
     * 确定“延长”内部控制器状态下灯光亮度的亮度状态。
     */
    uint16_t lightness_prolong;     /*!< Light LC Lightness Extended状态的值*/
    /**
     * 确定待机内部控制器状态下的灯光亮度的亮度状态。
     */
    uint16_t lightness_standby;     /*!< Light LC Lightness Standby状态的值*/

    /**
     * uint16状态表示环境照度水平，确定控制器是否从光控制待机状态转换。
     */
    uint16_t ambient_luxlevel_on;       /*!< Light LC Ambient LuxLevel On状态的值*/
    /**
     * uint16状态表示延长状态下所需的环境照度水平。
     */
    uint16_t ambient_luxlevel_prolong;  /*!< 轻LC环境照度水平延长状态的值*/
    /**
     * uint16状态表示待机状态下所需的环境照度水平。
     */
    uint16_t ambient_luxlevel_standby;  /*!< 轻型LC环境照度等级待机状态的值*/

    /**
     * float32状态表示积分系数，该积分系数决定了当光LC环境LuxLevel低于LuxLevel Out时定义光LC PI反馈调节器输出的方程式的积分部分。有效范围：0.0～1000.0。默认值为250.0。
     */
    float regulator_kiu;    /*!< 轻型LC调节器Kiu状态的值*/
    /**
     * float32状态表示积分系数，当Light LC Ambient LuxLevel大于或等于LuxLevel Out状态的值时，该积分系数确定定义Light LC PI反馈调节器输出的方程式的积分部分。有效范围：0.0～1000.0。默认值为25.0。
     */
    float regulator_kid;    /*!< 轻型LC调节器Kid状态的值*/
    /**
     * 表示比例系数的float32状态，该比例系数确定了定义光LC PI反馈调节器输出的方程式的比例部分，当光LC环境LuxLevel小于LuxLevel Out状态的值时。有效范围：0.0～1000.0。默认值为80.0。
     */
    float regulator_kpu;    /*!< 轻型LC调节器Kpu状态的值*/
    /**
     * 表示比例系数的float32状态，该比例系数确定了定义光LC PI反馈调节器输出的方程式的比例部分，当光LC环境LuxLevel大于或等于LuxLevel Out状态的值时。有效范围：0.0～1000.0。默认值为80.0。
     */
    float regulator_kpd;    /*!< 轻型LC调节器Kpd状态的值*/
    /**
     * int8状态表示Light LC PI反馈调节器的百分比精度。有效范围：0.0～100.0。默认值为2.0。
     */
    int8_t regulator_accuracy;  /*!< 轻型LC调节器精度状态的值*/

    /**
     * 如果消息“原始”字段包含“自运动以来感知的时间”设备属性的“原始值”，该值表示小于或等于“轻型LC占用延迟”状态的值，则应通过“轻型LC占有延迟”状态值与接收到的“自运动起时间”值之间的差值将“轻型LC占据延迟”状态设置为0b1。
     */
    uint32_t set_occupancy_to_1_delay;  /*!< 轻型LC占用延迟状态值与接收到的运动时间值之间的差值*/
} esp_ble_mesh_light_lc_property_state_t;

/**此枚举值是轻型LC状态机状态*/
typedef enum {
    ESP_BLE_MESH_LC_OFF,
    ESP_BLE_MESH_LC_STANDBY,
    ESP_BLE_MESH_LC_FADE_ON,
    ESP_BLE_MESH_LC_RUN,
    ESP_BLE_MESH_LC_FADE,
    ESP_BLE_MESH_LC_PROLONG,
    ESP_BLE_MESH_LC_FADE_STANDBY_AUTO,
    ESP_BLE_MESH_LC_FADE_STANDBY_MANUAL,
} esp_ble_mesh_lc_state_t;

/**轻型LC状态机参数*/
typedef struct {
    /**
     * 淡入、淡入、自动淡入待机和手动淡入待机状态是过渡状态，它们定义了亮度降低和亮度降低状态的过渡。此转换可以作为光LC状态机更改的结果或作为接收到光LC光开关设置或光LC光设置未确认消息的结果而开始。
     */
    struct {
        uint8_t fade_on;                /*!< 灯光LC时间衰减开启的过渡时间值*/
        uint8_t fade;                   /*!< 灯光LC时间衰减的过渡时间值*/
        uint8_t fade_standby_auto;      /*!< Light LC time Fade Standby Auto的过渡时间值*/
        uint8_t fade_standby_manual;    /*!< Light LC time Fade Standby Manual的过渡时间值*/
    } trans_time;                       /*!< 过渡时间值*/
    esp_ble_mesh_lc_state_t state;      /*!< Light LC状态机状态的值*/
    struct k_delayed_work timer;        /*!< 轻型LC状态机定时器*/
} esp_ble_mesh_light_lc_state_machine_t;

/**灯光亮度控制器参数*/
typedef struct {
    esp_ble_mesh_light_lc_state_t          state;           /*!< 轻LC状态参数*/
    esp_ble_mesh_light_lc_property_state_t prop_state;      /*!< 轻LC特性状态参数*/
    esp_ble_mesh_light_lc_state_machine_t  state_machine;   /*!< 轻型LC状态机参数*/
} esp_ble_mesh_light_control_t;

/**轻型LC服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明LC服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_control_t *lc;           /*!< 灯光控制器的参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
} esp_ble_mesh_light_lc_srv_t;

/**Light LC安装服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向照明LC设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_light_control_t *lc;           /*!< 灯光控制器的参数*/
} esp_ble_mesh_light_lc_setup_srv_t;

/**灯光亮度参数实际状态更改事件*/
typedef struct {
    uint16_t lightness;     /*!< 灯光亮度实际状态的值*/
} esp_ble_mesh_state_change_light_lightness_set_t;

/**光亮度线性状态变化事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< “Light Lightness Linear”状态的值*/
} esp_ble_mesh_state_change_light_lightness_linear_set_t;

/**灯光亮度默认状态更改事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< 灯光亮度默认状态的值*/
} esp_ble_mesh_state_change_light_lightness_default_set_t;

/**灯光亮度范围状态更改事件的参数*/
typedef struct {
    uint16_t range_min;     /*!< “灯光亮度范围”状态的最小值*/
    uint16_t range_max;     /*!< “灯光亮度范围”状态的最大值*/
} esp_ble_mesh_state_change_light_lightness_range_set_t;

/**灯光CTL状态更改事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< 灯光CTL亮度状态的值*/
    uint16_t temperature;   /*!< 灯光CTL温度状态的值*/
    int16_t  delta_uv;      /*!< 灯光CTL增量UV状态的值*/
} esp_ble_mesh_state_change_light_ctl_set_t;

/**灯光CTL温度状态更改事件的参数*/
typedef struct {
    uint16_t temperature;   /*!< 灯光CTL温度状态的值*/
    int16_t  delta_uv;      /*!< 灯光CTL增量UV状态的值*/
} esp_ble_mesh_state_change_light_ctl_temperature_set_t;

/**灯光CTL温度范围状态更改事件的参数*/
typedef struct {
    uint16_t range_min;     /*!< 灯光CTL温度范围状态的最小值*/
    uint16_t range_max;     /*!< 灯光CTL温度范围状态的最大值*/
} esp_ble_mesh_state_change_light_ctl_temperature_range_set_t;

/**灯光CTL默认状态更改事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< 灯光亮度默认状态的值*/
    uint16_t temperature;   /*!< 灯光CTL温度默认状态的值*/
    int16_t  delta_uv;      /*!< 灯光CTL增量UV默认状态的值*/
} esp_ble_mesh_state_change_light_ctl_default_set_t;

/**轻型HSL状态变化事件参数*/
typedef struct {
    uint16_t lightness;     /*!< Light HSL Lightness状态的值*/
    uint16_t hue;           /*!< 灯光HSL色调状态的值*/
    uint16_t saturation;    /*!< 光HSL饱和状态的值*/
} esp_ble_mesh_state_change_light_hsl_set_t;

/**光HSL色调状态更改事件的参数*/
typedef struct {
    uint16_t hue;           /*!< 灯光HSL色调状态的值*/
} esp_ble_mesh_state_change_light_hsl_hue_set_t;

/**光HSL饱和状态变化事件参数*/
typedef struct {
    uint16_t saturation;    /*!< 光HSL饱和状态的值*/
} esp_ble_mesh_state_change_light_hsl_saturation_set_t;

/**Light HSL默认状态更改事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< 灯光HSL亮度默认状态的值*/
    uint16_t hue;           /*!< 灯光HSL色调默认状态的值*/
    uint16_t saturation;    /*!< Light HSL Saturation Default状态的值*/
} esp_ble_mesh_state_change_light_hsl_default_set_t;

/**轻型HSL范围状态更改事件的参数*/
typedef struct {
    uint16_t hue_range_min;         /*!< 光HSL范围状态的最小色调值*/
    uint16_t hue_range_max;         /*!< 灯光HSL范围状态的最大色调值*/
    uint16_t saturation_range_min;  /*!< 轻型HSL范围状态的最小饱和值*/
    uint16_t saturation_range_max;  /*!< 轻型HSL范围状态的最大饱和值*/
} esp_ble_mesh_state_change_light_hsl_range_set_t;

/**Light xyL状态更改事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< Light xyL Lightness状态的值*/
    uint16_t x;             /*!< Light xyL x状态的值*/
    uint16_t y;             /*!< Light xyL y状态的值*/
} esp_ble_mesh_state_change_light_xyl_set_t;

/**Light xyL默认状态更改事件的参数*/
typedef struct {
    uint16_t lightness;     /*!< 灯光亮度默认状态的值*/
    uint16_t x;             /*!< 灯光xyL x默认状态的值*/
    uint16_t y;             /*!< 灯光xyL y默认状态的值*/
} esp_ble_mesh_state_change_light_xyl_default_set_t;

/**Light xyL Range状态更改事件的参数*/
typedef struct {
    uint16_t x_range_min;   /*!< Light xyL x Range状态的最小值*/
    uint16_t x_range_max;   /*!< Light xyL x Range状态的最大值*/
    uint16_t y_range_min;   /*!< Light xyL y Range状态的最小值*/
    uint16_t y_range_max;   /*!< 灯光xyL y范围状态的最大值*/
} esp_ble_mesh_state_change_light_xyl_range_set_t;

/**轻型LC模式状态更改事件的参数*/
typedef struct {
    uint8_t mode;       /*!< 轻LC模式状态的值*/
} esp_ble_mesh_state_change_light_lc_mode_set_t;

/**轻型LC占用模式状态更改事件的参数*/
typedef struct {
    uint8_t mode;       /*!< 轻型LC占用模式状态的值*/
} esp_ble_mesh_state_change_light_lc_om_set_t;

/**Light LC Light OnOff状态更改事件的参数*/
typedef struct {
    uint8_t onoff;      /*!< Light LC Light OnOff状态的值*/
} esp_ble_mesh_state_change_light_lc_light_onoff_set_t;

/**轻型LC特性状态变化事件的参数*/
typedef struct {
    uint16_t property_id;   /*!< Light LC属性状态的属性id*/
    struct net_buf_simple *property_value;  /*!< Light LC property状态的属性值*/
} esp_ble_mesh_state_change_light_lc_property_set_t;

/**传感器状态更改事件的参数*/
typedef struct {
    uint16_t property_id;       /*!< 传感器属性ID的值*/
    /**传感器状态相关状态参数*/
    union {
        uint8_t  occupancy;                 /*!< 轻型LC占用状态的值*/
        uint32_t set_occupancy_to_1_delay;  /*!< Light LC的值将Occupancy设置为1 Delay状态*/
        uint32_t ambient_luxlevel;          /*!< 光LC环境照度状态的值*/
    } state;
} esp_ble_mesh_state_change_sensor_status_t;

/**
 * @brief 照明服务器模型状态更改值联合
 */
typedef union {
    /**
     * ctx中的recv_op可用于决定更改的状态。
     */
    esp_ble_mesh_state_change_light_lightness_set_t             lightness_set;          /*!< 灯光亮度设置*/
    esp_ble_mesh_state_change_light_lightness_linear_set_t      lightness_linear_set;   /*!< 灯光亮度线性集*/
    esp_ble_mesh_state_change_light_lightness_default_set_t     lightness_default_set;  /*!< 灯光亮度默认设置*/
    esp_ble_mesh_state_change_light_lightness_range_set_t       lightness_range_set;    /*!< 灯光亮度范围设置*/
    esp_ble_mesh_state_change_light_ctl_set_t                   ctl_set;                /*!< 灯光CTL设置*/
    esp_ble_mesh_state_change_light_ctl_temperature_set_t       ctl_temp_set;           /*!< 灯光CTL温度设置*/
    esp_ble_mesh_state_change_light_ctl_temperature_range_set_t ctl_temp_range_set;     /*!< 灯光CTL温度范围设置*/
    esp_ble_mesh_state_change_light_ctl_default_set_t           ctl_default_set;        /*!< 灯光CTL默认设置*/
    esp_ble_mesh_state_change_light_hsl_set_t                   hsl_set;                /*!< 轻型HSL套件*/
    esp_ble_mesh_state_change_light_hsl_hue_set_t               hsl_hue_set;            /*!< 浅色HSL色调设置*/
    esp_ble_mesh_state_change_light_hsl_saturation_set_t        hsl_saturation_set;     /*!< 轻HSL饱和度设置*/
    esp_ble_mesh_state_change_light_hsl_default_set_t           hsl_default_set;        /*!< 灯光HSL默认设置*/
    esp_ble_mesh_state_change_light_hsl_range_set_t             hsl_range_set;          /*!< 轻型HSL范围设置*/
    esp_ble_mesh_state_change_light_xyl_set_t                   xyl_set;                /*!< 浅色xyL设置*/
    esp_ble_mesh_state_change_light_xyl_default_set_t           xyl_default_set;        /*!< 灯光xyL默认设置*/
    esp_ble_mesh_state_change_light_xyl_range_set_t             xyl_range_set;          /*!< 浅色xyL范围设置*/
    esp_ble_mesh_state_change_light_lc_mode_set_t               lc_mode_set;            /*!< 轻型LC模式设置*/
    esp_ble_mesh_state_change_light_lc_om_set_t                 lc_om_set;              /*!< 轻型LC占用模式设置*/
    esp_ble_mesh_state_change_light_lc_light_onoff_set_t        lc_light_onoff_set;     /*!< 灯LC灯开关设置*/
    esp_ble_mesh_state_change_light_lc_property_set_t           lc_property_set;        /*!< 轻型LC属性集*/
    esp_ble_mesh_state_change_sensor_status_t                   sensor_status;          /*!< 传感器状态*/
} esp_ble_mesh_lighting_server_state_change_t;

/**接收到的轻LC属性获取消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识轻型LC属性的属性ID*/
} esp_ble_mesh_server_recv_light_lc_property_get_t;

/**
 * @brief 照明服务器模型收到获取消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_light_lc_property_get_t lc_property;   /*!< 轻LC属性获取*/
} esp_ble_mesh_lighting_server_recv_get_msg_t;

/**接收到的灯光亮度设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t lightness;     /*!< 灯光亮度实际状态目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_lightness_set_t;

/**接收到的光亮度线性设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t lightness;     /*!< 光亮度线性状态目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_lightness_linear_set_t;

/**接收到的灯光亮度默认设置消息的上下文*/
typedef struct {
    uint16_t lightness;     /*!< “灯光亮度默认”状态的值*/
} esp_ble_mesh_server_recv_light_lightness_default_set_t;

/**接收到的灯光亮度范围设置消息的上下文*/
typedef struct {
    uint16_t range_min;     /*!< 亮度范围状态的最小范围字段值*/
    uint16_t range_max;     /*!< 灯光亮度范围状态的范围最大字段值*/
} esp_ble_mesh_server_recv_light_lightness_range_set_t;

/**接收到的灯光CTL设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t lightness;     /*!< 灯光ctl亮度状态目标值*/
    uint16_t temperature;   /*!< 灯光ctl温度状态目标值*/
    int16_t  delta_uv;      /*!< 光ctl delta UV状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_ctl_set_t;

/**接收到的灯光CTL温度设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t temperature;   /*!< 灯光ctl温度状态目标值*/
    int16_t  delta_uv;      /*!< 光ctl delta UV状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_ctl_temperature_set_t;

/**接收到的灯光CTL温度范围设置消息的上下文*/
typedef struct {
    uint16_t range_min;     /*!< 温度范围值最小光场ctl温度范围状态*/
    uint16_t range_max;     /*!< 温度范围值最大光场ctl温度范围状态*/
} esp_ble_mesh_server_recv_light_ctl_temperature_range_set_t;

/**接收到的灯光CTL默认设置消息的上下文*/
typedef struct {
    uint16_t lightness;     /*!< 灯光亮度默认状态的值*/
    uint16_t temperature;   /*!< 灯光温度默认状态值*/
    int16_t  delta_uv;      /*!< 光增量UV默认状态的值*/
} esp_ble_mesh_server_recv_light_ctl_default_set_t;

/**接收到的光HSL设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t lightness;     /*!< 轻hsl亮度状态目标值*/
    uint16_t hue;           /*!< 灯光hsl色调状态的目标值*/
    uint16_t saturation;    /*!< 光hsl饱和状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_hsl_set_t;

/**接收到的光HSL色调设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t hue;           /*!< 灯光hsl色调状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_hsl_hue_set_t;

/**接收到的光HSL饱和设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t saturation;    /*!< 灯光hsl色调状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_hsl_saturation_set_t;

/**接收到的轻型HSL默认设置消息的上下文*/
typedef struct {
    uint16_t lightness;     /*!< 灯光亮度默认状态的值*/
    uint16_t hue;           /*!< 灯光色调默认状态的值*/
    uint16_t saturation;    /*!< 光饱和度默认状态的值*/
} esp_ble_mesh_server_recv_light_hsl_default_set_t;

/**接收到的轻型HSL范围设置消息的上下文*/
typedef struct {
    uint16_t hue_range_min;         /*!< 光hsl色域状态的色域最小值*/
    uint16_t hue_range_max;         /*!< 光hsl色域状态的色域最大值*/
    uint16_t saturation_range_min;  /*!< 光hsl饱和范围状态的饱和范围最小场值*/
    uint16_t saturation_range_max;  /*!< 光hsl饱和范围状态的饱和范围最大场值*/
} esp_ble_mesh_server_recv_light_hsl_range_set_t;

/**接收到的Light xyL Set消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t lightness;     /*!< 灯光xyL亮度状态的目标值*/
    uint16_t x;             /*!< 灯光xyL x状态的目标值*/
    uint16_t y;             /*!< 灯光xyL y状态的目标值*/
    uint8_t  tid;           /*!< 事务标识符*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_xyl_set_t;

/**接收到的Light xyL Default Set消息的上下文*/
typedef struct {
    uint16_t lightness;     /*!< “灯光亮度默认”状态的值*/
    uint16_t x;             /*!< 灯光xyL x默认状态的值*/
    uint16_t y;             /*!< 灯光xyL y默认状态的值*/
} esp_ble_mesh_server_recv_light_xyl_default_set_t;

/**接收到的光xyl范围设置消息的上下文*/
typedef struct {
    uint16_t x_range_min;   /*!< 灯光xyL x范围状态的xyL x Range Min字段的值*/
    uint16_t x_range_max;   /*!< 灯光xyL x范围状态的xyL x Range Max字段的值*/
    uint16_t y_range_min;   /*!< 灯光xyL y范围状态的xyL y Range Min字段的值*/
    uint16_t y_range_max;   /*!< 灯光xyL y范围状态的xyL y Range Max字段的值*/
} esp_ble_mesh_server_recv_light_xyl_range_set_t;

/**接收到的光LC模式设置消息的上下文*/
typedef struct {
    uint8_t mode;   /*!< 轻LC模式状态的目标值*/
} esp_ble_mesh_server_recv_light_lc_mode_set_t;

/**接收到的光OM设置消息的上下文*/
typedef struct {
    uint8_t mode;   /*!< 轻型LC占用模式状态的目标值*/
} esp_ble_mesh_server_recv_light_lc_om_set_t;

/**接收到的灯光LC灯光开/关设置消息的上下文*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    uint8_t light_onoff;    /*!< Light LC Light OnOff状态的目标值*/
    uint8_t tid;            /*!< 事务标识符*/
    uint8_t trans_time;     /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;          /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_light_lc_light_onoff_set_t;

/**接收到的轻型LC属性集消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识轻型LC属性的属性ID*/
    struct net_buf_simple *property_value;  /*!< 轻型LC属性的原始值*/
} esp_ble_mesh_server_recv_light_lc_property_set_t;

/**
 * @brief 照明服务器模型接收到集合消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_light_lightness_set_t             lightness;           /*!< 灯光亮度设置/灯光亮度设置取消确认*/
    esp_ble_mesh_server_recv_light_lightness_linear_set_t      lightness_linear;    /*!< 灯光亮度线性集/灯光亮度线性设置取消确认*/
    esp_ble_mesh_server_recv_light_lightness_default_set_t     lightness_default;   /*!< 灯光亮度默认设置/灯光亮度默认值设置取消确认*/
    esp_ble_mesh_server_recv_light_lightness_range_set_t       lightness_range;     /*!< 灯光亮度范围设置/灯光亮度范围未确认*/
    esp_ble_mesh_server_recv_light_ctl_set_t                   ctl;                 /*!< 灯光CTL设置/灯光CTL设置取消确认*/
    esp_ble_mesh_server_recv_light_ctl_temperature_set_t       ctl_temp;            /*!< 灯光控制温度设置/灯光控制温度设定未确认*/
    esp_ble_mesh_server_recv_light_ctl_temperature_range_set_t ctl_temp_range;      /*!< 灯光控制温度范围设置/灯光控制温度设置未确认*/
    esp_ble_mesh_server_recv_light_ctl_default_set_t           ctl_default;         /*!< 灯光CTL默认设置/灯光CTL默认设定取消确认*/
    esp_ble_mesh_server_recv_light_hsl_set_t                   hsl;                 /*!< 轻型HSL设置/轻型HSL未锁定*/
    esp_ble_mesh_server_recv_light_hsl_hue_set_t               hsl_hue;             /*!< 浅色HSL色调设置/浅色HSL色相设置取消确认*/
    esp_ble_mesh_server_recv_light_hsl_saturation_set_t        hsl_saturation;      /*!< 轻HSL饱和设置/轻HSL饱和度设置未确认*/
    esp_ble_mesh_server_recv_light_hsl_default_set_t           hsl_default;         /*!< 灯光HSL默认设置/灯光HSL缺省设置未确认*/
    esp_ble_mesh_server_recv_light_hsl_range_set_t             hsl_range;           /*!< 轻型HSL范围设置/轻型HSL距离设置未确认*/
    esp_ble_mesh_server_recv_light_xyl_set_t                   xyl;                 /*!< 灯光xyL设置/灯光xyL未确认*/
    esp_ble_mesh_server_recv_light_xyl_default_set_t           xyl_default;         /*!< 灯光xyL默认设置/灯光xyL缺省设置未确认*/
    esp_ble_mesh_server_recv_light_xyl_range_set_t             xyl_range;           /*!< 灯光xyL范围设置/灯光xyL距离设置未确认*/
    esp_ble_mesh_server_recv_light_lc_mode_set_t               lc_mode;             /*!< 轻LC模式设置/轻LC模式未确认*/
    esp_ble_mesh_server_recv_light_lc_om_set_t                 lc_om;               /*!< 轻LC OM设置/轻LC OM未确认*/
    esp_ble_mesh_server_recv_light_lc_light_onoff_set_t        lc_light_onoff;      /*!< 灯光LC灯光开关设置/灯光LC灯光开/关设置未确认*/
    esp_ble_mesh_server_recv_light_lc_property_set_t           lc_property;         /*!< 轻LC属性集/轻LC属性设置未确认*/
} esp_ble_mesh_lighting_server_recv_set_msg_t;

/**接收到的传感器状态消息的上下文*/
typedef struct {
    struct net_buf_simple *data;    /*!< 传感器数据状态值（可选）*/
} esp_ble_mesh_server_recv_sensor_status_t;

/**
 * @brief 照明服务器模型收到状态消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_sensor_status_t sensor_status;     /*!< 传感器状态*/
} esp_ble_mesh_lighting_server_recv_status_msg_t;

/**
 * @brief 照明服务器模型回调值联合
 */
typedef union {
    esp_ble_mesh_lighting_server_state_change_t state_change;   /*!< ESP_BLE_MESH_LIGHTING_SERVER_STATE_CHANGE_EVT */
    esp_ble_mesh_lighting_server_recv_get_msg_t get;            /*!< ESP_BLE_MESH_LIGHTING_SERVER_RECV_GET_MSG_EVT */
    esp_ble_mesh_lighting_server_recv_set_msg_t set;            /*!< ESP_BLE_MESH_LIGHTING_SERVER_RECV_SET_MSG_EVT */
    esp_ble_mesh_lighting_server_recv_status_msg_t status;      /*!< ESP_BLE_MESH_LIGHTING_SERVER_RECV_STATUS_MSG_EVT */
} esp_ble_mesh_lighting_server_cb_value_t;

/**照明服务器模型回调参数*/
typedef struct {
    esp_ble_mesh_model_t  *model;   /*!< 指向照明服务器型号的指针*/
    esp_ble_mesh_msg_ctx_t ctx;     /*!< 收到消息的上下文*/
    esp_ble_mesh_lighting_server_cb_value_t value;  /*!< 接收到的照明信息的值*/
} esp_ble_mesh_lighting_server_cb_param_t;

/**此枚举值是照明服务器模型的事件*/
typedef enum {
    /**
     * 1.当get_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当接收到Lighting get消息时，不会将任何事件回调到应用层。2.当set_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当接收到照明设置/设置未确认消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_LIGHTING_SERVER_STATE_CHANGE_EVT,
    /**
     * 当get_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当接收到Lighting get消息时，此事件将回调到应用程序层。
     */
    ESP_BLE_MESH_LIGHTING_SERVER_RECV_GET_MSG_EVT,
    /**
     * 当set_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当接收到照明设置/设置未确认消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_LIGHTING_SERVER_RECV_SET_MSG_EVT,
    /**
     * 当status_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到传感器状态消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_LIGHTING_SERVER_RECV_STATUS_MSG_EVT,
    ESP_BLE_MESH_LIGHTING_SERVER_EVT_MAX,
} esp_ble_mesh_lighting_server_cb_event_t;

/**
 *  @brief 蓝牙网状照明服务器模型功能。
 */

/**
 * @brief   照明服务器模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_lighting_server_cb_t)(esp_ble_mesh_lighting_server_cb_event_t event,
                                                   esp_ble_mesh_lighting_server_cb_param_t *param);

/**
 * @brief       注册BLE Mesh Lighting Server模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_lighting_server_callback(esp_ble_mesh_lighting_server_cb_t callback);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_LIGHTING_MODEL_API_H_ */

