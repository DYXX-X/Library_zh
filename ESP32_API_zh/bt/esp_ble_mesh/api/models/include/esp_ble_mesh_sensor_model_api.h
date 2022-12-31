/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格传感器客户端模型API。
 */

#ifndef _ESP_BLE_MESH_SENSOR_MODEL_API_H_
#define _ESP_BLE_MESH_SENSOR_MODEL_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def    ESP_BLE_MESH_MODEL_SENSOR_CLI
 *
 *  @brief  定义新的传感器客户端模型。
 *
 *  @note   需要为应用程序需要具有传感器客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的传感器客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_SENSOR_CLI(cli_pub, cli_data)            \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SENSOR_CLI,    \
                    NULL, cli_pub, cli_data)

/**
 *  @brief 蓝牙网格传感器客户端模型获取和设置参数结构。
 */

/**获取传感器描述符的参数*/
typedef struct {
    bool  op_en;        /*!< 指示是否包含可选参数*/
    uint16_t property_id;  /*!< 传感器的属性ID（可选）*/
} esp_ble_mesh_sensor_descriptor_get_t;

/**传感器Cadence Get参数*/
typedef struct {
    uint16_t property_id;  /*!< 传感器的属性ID*/
} esp_ble_mesh_sensor_cadence_get_t;

/**传感器Cadence Set参数*/
typedef struct {
    uint16_t property_id;                               /*!< 传感器的属性ID*/
    uint8_t  fast_cadence_period_divisor : 7,           /*!< 发布期间的除数*/
             status_trigger_type : 1;                   /*!< 状态触发器增量字段的单位和格式*/
    struct net_buf_simple *status_trigger_delta_down;   /*!< 触发状态消息的向下增量值*/
    struct net_buf_simple *status_trigger_delta_up;     /*!< 触发状态消息的增量值*/
    uint8_t  status_min_interval;                       /*!< 两条连续状态消息之间的最小间隔*/
    struct net_buf_simple *fast_cadence_low;            /*!< 快速节奏范围值低*/
    struct net_buf_simple *fast_cadence_high;           /*!< 快速节奏范围的快速值*/
} esp_ble_mesh_sensor_cadence_set_t;

/**传感器设置参数获取*/
typedef struct {
    uint16_t sensor_property_id;   /*!< 传感器的属性ID*/
} esp_ble_mesh_sensor_settings_get_t;

/**传感器设置参数获取*/
typedef struct {
    uint16_t sensor_property_id;           /*!< 传感器的属性ID*/
    uint16_t sensor_setting_property_id;   /*!< 标识传感器内设置的设置ID*/
} esp_ble_mesh_sensor_setting_get_t;

/**传感器设置设置参数*/
typedef struct {
    uint16_t sensor_property_id;           /*!< 标识传感器的属性ID*/
    uint16_t sensor_setting_property_id;   /*!< 标识传感器内设置的设置ID*/
    struct net_buf_simple *sensor_setting_raw;  /*!< 设置的原始值*/
} esp_ble_mesh_sensor_setting_set_t;

/**传感器获取参数*/
typedef struct {
    bool     op_en;        /*!< 指示是否包含可选参数*/
    uint16_t property_id;  /*!< 传感器的属性ID（可选）*/
} esp_ble_mesh_sensor_get_t;

/**传感器列获取参数*/
typedef struct {
    uint16_t property_id;  /*!< 标识传感器的属性*/
    struct net_buf_simple *raw_value_x; /*!< 标识列的原始值*/
} esp_ble_mesh_sensor_column_get_t;

/**传感器系列参数获取*/
typedef struct {
    bool     op_en;        /*!< 指示是否包含可选参数*/
    uint16_t property_id;  /*!< 标识传感器的属性*/
    struct net_buf_simple *raw_value_x1;    /*!< 标识起始列的原始值（可选）*/
    struct net_buf_simple *raw_value_x2;    /*!< 标识结束列的原始值（C.1）*/
} esp_ble_mesh_sensor_series_get_t;

/**
 * @brief 传感器客户端模型获取消息联合
 */
typedef union {
    esp_ble_mesh_sensor_descriptor_get_t descriptor_get;    /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_DESCRIPTOR_GET*/
    esp_ble_mesh_sensor_cadence_get_t    cadence_get;       /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_GET*/
    esp_ble_mesh_sensor_settings_get_t   settings_get;      /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SETTINGS_GET*/
    esp_ble_mesh_sensor_setting_get_t    setting_get;       /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_GET*/
    esp_ble_mesh_sensor_get_t            sensor_get;        /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_GET*/
    esp_ble_mesh_sensor_column_get_t     column_get;        /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_COLUMN_GET*/
    esp_ble_mesh_sensor_series_get_t     series_get;        /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SERIES_GET*/
} esp_ble_mesh_sensor_client_get_state_t;

/**
 * @brief 传感器客户端模型集消息联合
 */
typedef union {
    esp_ble_mesh_sensor_cadence_set_t cadence_set;          /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_SET和ESP_BLE_MESH_MODE_OP_SENSOR_CADENCE_SET_UNACK*/
    esp_ble_mesh_sensor_setting_set_t setting_set;          /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_SET和ESP_BLE-MESH_MODE_OP_SENSOR_SETTING_SET_UNACK*/
} esp_ble_mesh_sensor_client_set_state_t;

/**
 *  @brief 蓝牙网格传感器客户端模型获取和设置回调参数结构。
 */

/**传感器描述符状态参数*/
typedef struct {
    struct net_buf_simple *descriptor;  /*!< 8位字节传感器描述符序列（可选）*/
} esp_ble_mesh_sensor_descriptor_status_cb_t;

/**传感器Cadence状态参数*/
typedef struct {
    uint16_t property_id;  /*!< 传感器的属性*/
    struct net_buf_simple *sensor_cadence_value;    /*!< 传感器节奏状态值*/
} esp_ble_mesh_sensor_cadence_status_cb_t;

/**传感器设置状态参数*/
typedef struct {
    uint16_t sensor_property_id;   /*!< 标识传感器的属性ID*/
    struct net_buf_simple *sensor_setting_property_ids; /*!< 一系列N个传感器设置属性ID（可选）*/
} esp_ble_mesh_sensor_settings_status_cb_t;

/**传感器设置状态参数*/
typedef struct  {
    bool     op_en;                        /*!< 指示包含id可选参数*/
    uint16_t sensor_property_id;           /*!< 标识传感器的属性ID*/
    uint16_t sensor_setting_property_id;   /*!< 标识传感器内设置的设置ID*/
    uint8_t  sensor_setting_access;        /*!< 设置的读/写访问权限（可选）*/
    struct net_buf_simple *sensor_setting_raw;  /*!< 设置的原始值*/
} esp_ble_mesh_sensor_setting_status_cb_t;

/**传感器状态参数*/
typedef struct {
    struct net_buf_simple *marshalled_sensor_data;  /*!< 传感器数据状态值（可选）*/
} esp_ble_mesh_sensor_status_cb_t;

/**传感器列状态参数*/
typedef struct {
    uint16_t property_id;  /*!< 标识传感器和Y轴的属性*/
    struct net_buf_simple *sensor_column_value; /*!< 左侧传感器列状态值*/
} esp_ble_mesh_sensor_column_status_cb_t;

/**传感器系列状态参数*/
typedef struct {
    uint16_t property_id;  /*!< 标识传感器和Y轴的属性*/
    struct net_buf_simple *sensor_series_value; /*!< 传感器系列状态的左侧值*/
} esp_ble_mesh_sensor_series_status_cb_t;

/**
 * @brief 传感器客户端模型接收到消息联合
 */
typedef union {
    esp_ble_mesh_sensor_descriptor_status_cb_t descriptor_status;   /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_DESCRIPTOR_STATUS*/
    esp_ble_mesh_sensor_cadence_status_cb_t    cadence_status;      /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_STATUS*/
    esp_ble_mesh_sensor_settings_status_cb_t   settings_status;     /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SETTINGS_STATUS*/
    esp_ble_mesh_sensor_setting_status_cb_t    setting_status;      /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_STATUS*/
    esp_ble_mesh_sensor_status_cb_t            sensor_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_STATUS*/
    esp_ble_mesh_sensor_column_status_cb_t     column_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_COLUMN_STATUS*/
    esp_ble_mesh_sensor_series_status_cb_t     series_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_SENSOR_SERIES_STATUS*/
} esp_ble_mesh_sensor_client_status_cb_t;

/**传感器客户端模型回调参数*/
typedef struct {
    int error_code;     /*!< 0：成功，否则失败。有关错误代码值，请参阅errno。h文件。在errno.h中的标准错误代码中添加负号。*/
    esp_ble_mesh_client_common_param_t    *params;      /*!< 客户端公用参数。*/
    esp_ble_mesh_sensor_client_status_cb_t status_cb;   /*!< 传感器状态消息回调值*/
} esp_ble_mesh_sensor_client_cb_param_t;

/**此枚举值是传感器客户端模型的事件*/
typedef enum {
    ESP_BLE_MESH_SENSOR_CLIENT_GET_STATE_EVT,
    ESP_BLE_MESH_SENSOR_CLIENT_SET_STATE_EVT,
    ESP_BLE_MESH_SENSOR_CLIENT_PUBLISH_EVT,
    ESP_BLE_MESH_SENSOR_CLIENT_TIMEOUT_EVT,
    ESP_BLE_MESH_SENSOR_CLIENT_EVT_MAX,
} esp_ble_mesh_sensor_client_cb_event_t;

/**
 *  @brief 蓝牙网状传感器客户端模型功能。
 */

/**
 * @brief   传感器客户端模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_sensor_client_cb_t)(esp_ble_mesh_sensor_client_cb_event_t event,
                                                 esp_ble_mesh_sensor_client_cb_param_t *param);

/**
 * @brief       注册BLE网状传感器客户端模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_sensor_client_callback(esp_ble_mesh_sensor_client_cb_t callback);

/**
 * @brief       使用传感器客户端模型获取消息获取传感器服务器模型状态的值。
 *
 * @note        如果您想知道此API接受的操作码和相应的含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_sensor_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   get_state: 指向传感器获取消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_sensor_client_get_state(esp_ble_mesh_client_common_param_t *params,
                                               esp_ble_mesh_sensor_client_get_state_t *get_state);

/**
 * @brief       使用传感器客户端模型设置消息设置传感器服务器模型状态的值。
 *
 * @note        如果您想知道此API接受的操作码和相应的含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_sensor_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   set_state: 指向传感器设置消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_sensor_client_set_state(esp_ble_mesh_client_common_param_t *params,
                                               esp_ble_mesh_sensor_client_set_state_t *set_state);

/**
 * @brief 传感器服务器模型相关上下文。
 */

/** @def    ESP_BLE_MESH_MODEL_SENSOR_SRV
 *
 *  @brief  定义新的传感器服务器模型。
 *
 *  @note   1.传感器服务器模型是根模型。当该模型出现在元件上时，相应的传感器设置服务器模型也应出现。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_sensor_srv_t的指针。
 *
 *  @return 新的传感器服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_SENSOR_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SENSOR_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_SENSOR_SETUP_SRV
 *
 *  @brief  定义新的传感器设置服务器模型。
 *
 *  @note   1.传感器设置服务器模型扩展了传感器服务器模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_sensor_setup_srv_t的指针。
 *
 *  @return 新建传感器设置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_SENSOR_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SENSOR_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

#define ESP_BLE_MESH_INVALID_SENSOR_PROPERTY_ID 0x0000  /*!< 传感器属性ID无效*/

#define ESP_BLE_MESH_SENSOR_PROPERTY_ID_LEN     0x02    /*!< 传感器属性ID的长度*/

#define ESP_BLE_MESH_SENSOR_DESCRIPTOR_LEN      0x08    /*!< 传感器描述符状态的长度*/

#define ESP_BLE_MESH_SENSOR_UNSPECIFIED_POS_TOLERANCE   0x000   /*!< 未指定的传感器正容差*/
#define ESP_BLE_MESH_SENSOR_UNSPECIFIED_NEG_TOLERANCE   0x000   /*!< 未指定的传感器负公差*/

#define ESP_BLE_MESH_SENSOR_NOT_APPL_MEASURE_PERIOD     0x00    /*!< 不适用的传感器测量周期*/

#define ESP_BLE_MESH_SENSOR_NOT_APPL_UPDATE_INTERVAL    0x00    /*!< 不适用的传感器更新间隔*/

#define ESP_BLE_MESH_INVALID_SENSOR_SETTING_PROPERTY_ID 0x0000  /*!< 传感器设置属性ID无效*/

#define ESP_BLE_MESH_SENSOR_SETTING_PROPERTY_ID_LEN     0x02    /*!< 传感器设置属性ID的长度*/
#define ESP_BLE_MESH_SENSOR_SETTING_ACCESS_LEN          0x01    /*!< 传感器设置访问的长度*/

#define ESP_BLE_MESH_SENSOR_SETTING_ACCESS_READ         0x01    /*!< 传感器设置访问-读取*/
#define ESP_BLE_MESH_SENSOR_SETTING_ACCESS_READ_WRITE   0x03    /*!< 传感器设置访问-读写*/

#define ESP_BLE_MESH_SENSOR_DIVISOR_TRIGGER_TYPE_LEN    0x01    /*!< 传感器分频器触发类型的长度*/
#define ESP_BLE_MESH_SENSOR_STATUS_MIN_INTERVAL_LEN     0x01    /*!< 传感器状态最小间隔长度*/

#define ESP_BLE_MESH_SENSOR_PERIOD_DIVISOR_MAX_VALUE    15  /*!< 传感器周期因子的最大值*/

#define ESP_BLE_MESH_SENSOR_STATUS_MIN_INTERVAL_MAX     26  /*!< 传感器状态最小间隔的最大值*/

/**
 * 传感器状态触发器类型—传感器属性ID状态引用的特性的格式类型
 */
#define ESP_BLE_MESH_SENSOR_STATUS_TRIGGER_TYPE_CHAR    0
/**传感器状态触发器类型-格式类型“uint16”*/
#define ESP_BLE_MESH_SENSOR_STATUS_TRIGGER_TYPE_UINT16  1

#define ESP_BLE_MESH_SENSOR_DATA_FORMAT_A   0x00    /*!< 传感器数据格式A*/
#define ESP_BLE_MESH_SENSOR_DATA_FORMAT_B   0x01    /*!< 传感器数据格式B*/

#define ESP_BLE_MESH_SENSOR_DATA_FORMAT_A_MPID_LEN  0x02    /*!< 传感器数据格式A的MPID长度*/
#define ESP_BLE_MESH_SENSOR_DATA_FORMAT_B_MPID_LEN  0x03    /*!< 传感器数据格式B的MPID长度*/

/**
 * 传感器数据长度为零。
 *
 * 注意：长度字段是从1开始的uint7值（有效范围0x0–0x7F，表示范围为1–127）。值0x7F表示长度为零。
 */
#define ESP_BLE_MESH_SENSOR_DATA_ZERO_LEN   0x7F

/** @def    ESP_BLE_MESH_GET_SENSOR_DATA_FORMAT
 *
 *  @brief  获取传感器数据的格式。
 *
 *  @note   可以连接多个传感器数据。确保在获取相应传感器数据的格式之前更新了_data指针。
 *
 *  @param  _data 指向传感器数据起点的指针。
 *
 *  @return 传感器数据的格式。
 */
#define ESP_BLE_MESH_GET_SENSOR_DATA_FORMAT(_data)      (((_data)[0]) & BIT_MASK(1))

/** @def    ESP_BLE_MESH_GET_SENSOR_DATA_LENGTH
 *
 *  @brief  获取传感器数据的长度。
 *
 *  @note   可以连接多个传感器数据。确保在获取相应传感器数据的长度之前更新了_data指针。
 *
 *  @param  _data 指向传感器数据起点的指针。
 *  @param  _fmt  传感器数据的格式。
 *
 *  @return 传感器数据的长度（从零开始）。
 */
#define ESP_BLE_MESH_GET_SENSOR_DATA_LENGTH(_data, _fmt)    \
            (((_fmt) == ESP_BLE_MESH_SENSOR_DATA_FORMAT_A) ? ((((_data)[0]) >> 1) & BIT_MASK(4)) : ((((_data)[0]) >> 1) & BIT_MASK(7)))

/** @def    ESP_BLE_MESH_GET_SENSOR_DATA_PROPERTY_ID
 *
 *  @brief  获取传感器数据的传感器属性ID。
 *
 *  @note   可以连接多个传感器数据。确保在获取相应传感器数据的传感器属性ID之前更新了_data指针。
 *
 *  @param  _data 指向传感器数据起点的指针。
 *  @param  _fmt  传感器数据的格式。
 *
 *  @return 传感器数据的传感器属性ID。
 */
#define ESP_BLE_MESH_GET_SENSOR_DATA_PROPERTY_ID(_data, _fmt)   \
            (((_fmt) == ESP_BLE_MESH_SENSOR_DATA_FORMAT_A) ? ((((_data)[1]) << 3) | (((_data)[0]) >> 5)) : ((((_data)[2]) << 8) | ((_data)[1])))

/** @def    ESP_BLE_MESH_SENSOR_DATA_FORMAT_A_MPID
 *
 *  @brief  为格式为a的传感器数据生成MPID值。
 *
 *  @note   1.格式字段为0b0，表示使用了格式A。2.长度字段是从1开始的uint4值（有效范围0x0–0xF，表示范围为1–16）。3.属性ID是表示属性ID的11个LSb的11位字段。4.此格式可用于长度不超过16个八位字节的属性值和小于0x0800的属性ID。
 *
 *  @param  _len 传感器原始值的长度。
 *  @param  _id  传感器属性ID。
 *
 *  @return 格式为A的传感器数据的2位字节MPID值。
 *
 */
#define ESP_BLE_MESH_SENSOR_DATA_FORMAT_A_MPID(_len, _id) \
        ((((_id) & BIT_MASK(11)) << 5) | (((_len) & BIT_MASK(4)) << 1) | ESP_BLE_MESH_SENSOR_DATA_FORMAT_A)

/** @def    ESP_BLE_MESH_SENSOR_DATA_FORMAT_B_MPID
 *
 *  @brief  为格式为B的传感器数据生成MPID值。
 *
 *  @note   1.格式字段为0b1，表示使用了格式B。2.长度字段是从1开始的uint7值（有效范围0x0–0x7F，表示范围为1–127）。值0x7F表示长度为零。3.属性ID是表示属性ID的16位字段。4.此格式可用于长度不超过128个八位字节的属性值和任何属性ID。传感器状态消息不支持长度超过128个八位字节的属性值。5.排除生成的1-八位字节值、2-八位字节传感器属性ID
 *
 *  @param  _len 传感器原始值的长度。
 *  @param  _id  传感器属性ID。
 *
 *  @return 格式为B的传感器数据的3位字节MPID值。
 *
 */
#define ESP_BLE_MESH_SENSOR_DATA_FORMAT_B_MPID(_len, _id) \
        (((_id) << 8) | (((_len) & BIT_MASK(7)) << 1) | ESP_BLE_MESH_SENSOR_DATA_FORMAT_B)

/**此枚举值是传感器采样函数的值*/
enum esp_ble_mesh_sensor_sample_func {
    ESP_BLE_MESH_SAMPLE_FUNC_UNSPECIFIED,
    ESP_BLE_MESH_SAMPLE_FUNC_INSTANTANEOUS,
    ESP_BLE_MESH_SAMPLE_FUNC_ARITHMETIC_MEAN,
    ESP_BLE_MESH_SAMPLE_FUNC_RMS,
    ESP_BLE_MESH_SAMPLE_FUNC_MAXIMUM,
    ESP_BLE_MESH_SAMPLE_FUNC_MINIMUM,
    ESP_BLE_MESH_SAMPLE_FUNC_ACCUMULATED,
    ESP_BLE_MESH_SAMPLE_FUNC_COUNT,
};

/**传感器描述符状态参数*/
typedef struct {
    uint32_t positive_tolerance : 12,   /*!< 传感器正容差字段的值*/
             negative_tolerance : 12,   /*!< 传感器负公差字段的值*/
             sampling_function : 8;     /*!< 传感器采样功能字段的值*/
    uint8_t  measure_period;            /*!< 传感器测量周期字段的值*/
    uint8_t  update_interval;           /*!< 传感器更新间隔字段的值*/
} esp_ble_mesh_sensor_descriptor_t;

/**传感器设置状态参数*/
typedef struct {
    uint16_t property_id;       /*!< 传感器设置属性ID字段的值*/
    uint8_t  access;            /*!< 传感器设置访问字段的值*/
    struct net_buf_simple *raw; /*!< 传感器设置原始字段的值*/
} esp_ble_mesh_sensor_setting_t;

/**传感器Cadence状态参数*/
typedef struct {
    uint8_t period_divisor : 7, /*!< Fast Cadence Period Divisior字段的值*/
            trigger_type : 1;   /*!< 状态触发器类型字段的值*/
    /**
     * 注意：trigger_delta_down、trigger_delt _up、fast_cadence_low和fast_cadence_high中的参数“size”表示这四个参数的确切长度，它们与传感器属性ID相关。用户需要精确地初始化“size”。
     */
    struct net_buf_simple *trigger_delta_down;  /*!< Status Trigger Delta Down字段的值*/
    struct net_buf_simple *trigger_delta_up;    /*!< Status Trigger Delta Up字段的值*/
    uint8_t min_interval;                       /*!< 状态最小间隔字段的值*/
    struct net_buf_simple *fast_cadence_low;    /*!< Fast Cadence Low场的价值*/
    struct net_buf_simple *fast_cadence_high;   /*!< Fast Cadence High场的价值*/
} esp_ble_mesh_sensor_cadence_t;

/**传感器数据状态参数*/
typedef struct {
    /**
     * 格式A：长度字段是从1开始的uint4值（有效范围0x0–0xF，表示范围为1–16）。格式B：长度字段是从1开始的uint7值（有效范围0x0–0x7F，表示范围为1–127）。值0x7F表示长度为零。
     */
    uint8_t format : 1, /*!< 传感器数据格式的值*/
            length : 7; /*!< 传感器数据长度的值*/
    struct net_buf_simple *raw_value;   /*!< 传感器数据原始值的值*/
} esp_ble_mesh_sensor_data_t;

/**传感器系列列状态参数*/
typedef struct {
    struct net_buf_simple *raw_value_x;     /*!< 传感器原始值X字段的值*/
    struct net_buf_simple *column_width;    /*!< 传感器列宽字段的值*/
    struct net_buf_simple *raw_value_y;     /*!< 传感器原始值Y字段的值*/
} esp_ble_mesh_sensor_series_column_t;

/**传感器状态参数*/
typedef struct {
    uint16_t sensor_property_id;    /*!< 传感器属性ID字段的值*/

    /* 在元素的整个生命周期中保持不变*/
    esp_ble_mesh_sensor_descriptor_t descriptor;    /*!< 传感器描述符状态参数*/

    /**
     * 每个传感器可能存在多个传感器设置状态。传感器设置属性ID值对于识别元件内传感器的每个传感器属性ID应是唯一的。
     */
    const uint8_t setting_count;                /*!<  */
    esp_ble_mesh_sensor_setting_t *settings;    /*!< 传感器设置状态参数*/

    /**
     * 基于引用“非标量特性”（如“直方图”或“复合特性”）的设备属性，传感器可能不支持传感器Cadence状态。
     */
    esp_ble_mesh_sensor_cadence_t *cadence;     /*!< 传感器Cadence状态参数*/

    esp_ble_mesh_sensor_data_t sensor_data;     /*!< 传感器数据状态参数*/

    esp_ble_mesh_sensor_series_column_t series_column;  /*!< 传感器系列列状态参数*/
} esp_ble_mesh_sensor_state_t;

/**传感器服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向传感器服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    const uint8_t state_count;                  /*!< 传感器状态计数*/
    esp_ble_mesh_sensor_state_t *states;        /*!< 传感器状态参数*/
} esp_ble_mesh_sensor_srv_t;

/**传感器设置服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向传感器设置服务器型号的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    const uint8_t state_count;                  /*!< 传感器状态计数*/
    esp_ble_mesh_sensor_state_t *states;        /*!< 传感器状态参数*/
} esp_ble_mesh_sensor_setup_srv_t;

/**传感器Cadence Set状态更改事件的参数*/
typedef struct {
    uint16_t property_id;           /*!< 传感器属性ID状态的值*/
    uint8_t  period_divisor : 7,    /*!< Fast Cadence Period Divisor状态的值*/
             trigger_type : 1;      /*!< 状态触发器类型状态的值*/
    struct net_buf_simple *trigger_delta_down;  /*!< Status Trigger Delta Down状态的值*/
    struct net_buf_simple *trigger_delta_up;    /*!< Status Trigger Delta Up状态的值*/
    uint8_t min_interval;                       /*!< Status Min Interval状态的值*/
    struct net_buf_simple *fast_cadence_low;    /*!< Fast Cadence Low状态的值*/
    struct net_buf_simple *fast_cadence_high;   /*!< Fast Cadence High状态的价值*/
} esp_ble_mesh_state_change_sensor_cadence_set_t;

/**传感器设置设置状态更改事件的参数*/
typedef struct {
    uint16_t property_id;           /*!< 传感器属性ID状态的值*/
    uint16_t setting_property_id;   /*!< 传感器设置属性ID状态的值*/
    struct net_buf_simple *setting_value;   /*!< 传感器属性值状态的值*/
} esp_ble_mesh_state_change_sensor_setting_set_t;

/**
 * @brief 传感器服务器模型状态更改值联合
 */
typedef union {
    /**
     * ctx中的recv_op可用于决定更改的状态。
     */
    esp_ble_mesh_state_change_sensor_cadence_set_t sensor_cadence_set;  /*!< 传感器Cadence Set*/
    esp_ble_mesh_state_change_sensor_setting_set_t sensor_setting_set;  /*!< 传感器设置设置*/
} esp_ble_mesh_sensor_server_state_change_t;

/**收到的传感器描述符获取消息的上下文*/
typedef struct {
    bool  op_en;    /*!< 指示是否包含可选参数*/
    uint16_t property_id;   /*!< 传感器的属性ID（可选）*/
} esp_ble_mesh_server_recv_sensor_descriptor_get_t;

/**接收到的传感器Cadence Get消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 传感器的属性ID*/
} esp_ble_mesh_server_recv_sensor_cadence_get_t;

/**收到的传感器设置获取消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 传感器的属性ID*/
} esp_ble_mesh_server_recv_sensor_settings_get_t;

/**接收到的传感器设置获取消息的上下文*/
typedef struct {
    uint16_t property_id;           /*!< 传感器的属性ID*/
    uint16_t setting_property_id;   /*!< 标识传感器内设置的设置ID*/
} esp_ble_mesh_server_recv_sensor_setting_get_t;

/**接收到的传感器获取消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t property_id;   /*!< 传感器的属性ID（可选）*/
} esp_ble_mesh_server_recv_sensor_get_t;

/**收到的传感器列获取消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识传感器的属性*/
    struct net_buf_simple *raw_value_x; /*!< 标识列的原始值*/
} esp_ble_mesh_server_recv_sensor_column_get_t;

/**收到的传感器系列获取消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t property_id;   /*!< 标识传感器的属性*/
    struct net_buf_simple *raw_value;   /*!< 包含X1和X2的原始值（可选）*/
} esp_ble_mesh_server_recv_sensor_series_get_t;

/**
 * @brief 收到传感器服务器模型获取消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_sensor_descriptor_get_t sensor_descriptor; /*!< 传感器描述符获取*/
    esp_ble_mesh_server_recv_sensor_cadence_get_t    sensor_cadence;    /*!< 传感器Cadence获取*/
    esp_ble_mesh_server_recv_sensor_settings_get_t   sensor_settings;   /*!< 传感器设置获取*/
    esp_ble_mesh_server_recv_sensor_setting_get_t    sensor_setting;    /*!< 传感器设置获取*/
    esp_ble_mesh_server_recv_sensor_get_t            sensor_data;       /*!< 传感器获取*/
    esp_ble_mesh_server_recv_sensor_column_get_t     sensor_column;     /*!< 传感器列获取*/
    esp_ble_mesh_server_recv_sensor_series_get_t     sensor_series;     /*!< 传感器系列获取*/
} esp_ble_mesh_sensor_server_recv_get_msg_t;

/**接收到的传感器Cadence Set消息的上下文*/
typedef struct {
    uint16_t property_id;           /*!< 传感器的属性ID*/
    struct net_buf_simple *cadence; /*!< 传感器Cadence状态值*/
} esp_ble_mesh_server_recv_sensor_cadence_set_t;

/**接收到的传感器设置设置消息的上下文*/
typedef struct {
    uint16_t property_id;           /*!< 标识传感器的属性ID*/
    uint16_t setting_property_id;   /*!< 标识传感器内设置的设置ID*/
    struct net_buf_simple *setting_raw; /*!< 设置的原始值*/
} esp_ble_mesh_server_recv_sensor_setting_set_t;

/**
 * @brief 传感器服务器模型接收到集合消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_sensor_cadence_set_t sensor_cadence;   /*!< 传感器Cadence Set*/
    esp_ble_mesh_server_recv_sensor_setting_set_t sensor_setting;   /*!< 传感器设置设置*/
} esp_ble_mesh_sensor_server_recv_set_msg_t;

/**
 * @brief 传感器服务器模型回调值联合
 */
typedef union {
    esp_ble_mesh_sensor_server_state_change_t state_change; /*!< ESP_BLE_MESH_SENSOR_SERVER_STATE_CHANGE_EVT */
    esp_ble_mesh_sensor_server_recv_get_msg_t get;  /*!< ESP_BLE_MESH_SENSOR_SERVER_RECV_GET_MSG_EVT */
    esp_ble_mesh_sensor_server_recv_set_msg_t set;  /*!< ESP_BLE_MESH_SENSOR_SERVER_RECV_SET_MSG_EVT */
} esp_ble_mesh_sensor_server_cb_value_t;

/**传感器服务器模型回调参数*/
typedef struct {
    esp_ble_mesh_model_t  *model;   /*!< 指向传感器服务器型号的指针*/
    esp_ble_mesh_msg_ctx_t ctx;     /*!< 收到消息的上下文*/
    esp_ble_mesh_sensor_server_cb_value_t value;    /*!< 收到的传感器信息的值*/
} esp_ble_mesh_sensor_server_cb_param_t;

/**此枚举值是传感器服务器模型的事件*/
typedef enum {
    /**
     * 1.当get_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当收到传感器获取消息时，不会将任何事件回调到应用层。2.当set_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当收到传感器设置/设置未确认消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_SENSOR_SERVER_STATE_CHANGE_EVT,
    /**
     * 当get_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到传感器获取消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_SENSOR_SERVER_RECV_GET_MSG_EVT,
    /**
     * 当set_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到传感器设置/设置未确认消息时，此事件将回调至应用层。
     */
    ESP_BLE_MESH_SENSOR_SERVER_RECV_SET_MSG_EVT,
    ESP_BLE_MESH_SENSOR_SERVER_EVT_MAX,
} esp_ble_mesh_sensor_server_cb_event_t;

/**
 *  @brief 蓝牙网状传感器服务器模型功能。
 */

/**
 * @brief   传感器服务器模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_sensor_server_cb_t)(esp_ble_mesh_sensor_server_cb_event_t event,
                                                 esp_ble_mesh_sensor_server_cb_param_t *param);

/**
 * @brief       注册BLE Mesh传感器服务器模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_sensor_server_callback(esp_ble_mesh_sensor_server_cb_t callback);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_SENSOR_MODEL_API_H_ */

