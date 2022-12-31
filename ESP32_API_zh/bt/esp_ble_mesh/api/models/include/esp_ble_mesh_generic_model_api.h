/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格通用客户端模型API。
 */

#ifndef _ESP_BLE_MESH_GENERIC_MODEL_API_H_
#define _ESP_BLE_MESH_GENERIC_MODEL_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def    ESP_BLE_MESH_MODEL_GEN_ONOFF_CLI
 *
 *  @brief  定义新的通用OnOff客户端模型。
 *
 *  @note   需要为应用程序需要具有通用OnOff客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建通用OnOff客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_ONOFF_CLI(cli_pub, cli_data)         \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI, \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_LEVEL_CLI
 *
 *  @brief  定义新的通用级客户端模型。
 *
 *  @note   需要为应用程序需要具有通用级客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建通用级别客户端模型实例。
 */

#define ESP_BLE_MESH_MODEL_GEN_LEVEL_CLI(cli_pub, cli_data)         \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_LEVEL_CLI, \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_DEF_TRANS_TIME_CLI
 *
 *  @brief  定义新的通用默认过渡时间客户端模型。
 *
 *  @note   需要为应用程序需要具有通用默认过渡时间客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建通用默认过渡时间客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_DEF_TRANS_TIME_CLI(cli_pub, cli_data)            \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI,    \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_POWER_ONOFF_CLI
 *
 *  @brief  定义新的通用电源开/关客户端模型。
 *
 *  @note   需要为应用程序需要具有通用电源开/关客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的通用电源开/关客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_POWER_ONOFF_CLI(cli_pub, cli_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI,   \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_POWER_LEVEL_CLI
 *
 *  @brief  定义新的通用电源级别客户端模型。
 *
 *  @note   需要为应用程序需要具有通用电源级别客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的通用电源级别客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_POWER_LEVEL_CLI(cli_pub, cli_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI,   \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_BATTERY_CLI
 *
 *  @brief  定义新的通用电池客户端模型。
 *
 *  @note   需要为应用程序需要具有通用电池客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新的通用电池客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_BATTERY_CLI(cli_pub, cli_data)           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_BATTERY_CLI,   \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_LOCATION_CLI
 *
 *  @brief  定义新的通用位置客户端模型。
 *
 *  @note   需要为应用程序需要在其上具有通用位置客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建通用位置客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_LOCATION_CLI(cli_pub, cli_data)          \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_CLI,  \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_PROPERTY_CLI
 *
 *  @brief  定义新的通用属性客户端模型。
 *
 *  @note   需要为应用程序需要在其上具有通用属性客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建通用位置客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_PROPERTY_CLI(cli_pub, cli_data)          \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_PROP_CLI,      \
                    NULL, cli_pub, cli_data)

/**
 *  @brief 蓝牙网格通用客户端模型获取和设置参数结构。
 */

/**通用开/关设置的参数。*/
typedef struct {
    bool    op_en;      /*!< 指示是否包含可选参数*/
    uint8_t onoff;      /*!< Generic OnOff状态的目标值*/
    uint8_t tid;        /*!< 事务ID*/
    uint8_t trans_time; /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;      /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_gen_onoff_set_t;

/**通用级别集的参数。*/
typedef struct {
    bool    op_en;      /*!< 指示是否包含可选参数*/
    int16_t level;      /*!< 通用级别状态的目标值*/
    uint8_t tid;        /*!< 事务ID*/
    uint8_t trans_time; /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;      /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_gen_level_set_t;

/**通用增量集的参数。*/
typedef struct {
    bool    op_en;      /*!< 指示是否包含可选参数*/
    int32_t level;      /*!< 通用级别状态的增量更改*/
    uint8_t tid;        /*!< 事务ID*/
    uint8_t trans_time; /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;      /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_gen_delta_set_t;

/**通用移动集的参数。*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    int16_t delta_level;    /*!< 计算通用级别状态移动速度的增量级别步骤*/
    uint8_t tid;            /*!< 事务ID*/
    uint8_t trans_time;     /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;          /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_gen_move_set_t;

/**通用默认转换时间集的参数。*/
typedef struct {
    uint8_t trans_time; /*!< 通用默认过渡时间状态的值*/
} esp_ble_mesh_gen_def_trans_time_set_t;

/**通用OnPowerUp集合的参数。*/
typedef struct {
    uint8_t onpowerup;  /*!< Generic OnPowerUp状态的值*/
} esp_ble_mesh_gen_onpowerup_set_t;

/**通用功率电平集的参数。*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t power;         /*!< 通用功率实际状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_gen_power_level_set_t;

/**通用电源默认设置的参数。*/
typedef struct {
    uint16_t power;         /*!< 常规电源默认状态的值*/
} esp_ble_mesh_gen_power_default_set_t;

/**通用功率范围集的参数。*/
typedef struct {
    uint16_t range_min;     /*!< 通用功率范围状态的范围最小值字段*/
    uint16_t range_max;     /*!< 通用功率范围状态的范围最大值字段的值*/
} esp_ble_mesh_gen_power_range_set_t;

/**通用位置全局集的参数。*/
typedef struct {
    int32_t global_latitude;    /*!< 全球坐标（纬度）*/
    int32_t global_longitude;   /*!< 全球坐标（经度）*/
    int16_t global_altitude;    /*!< 全球海拔高度*/
} esp_ble_mesh_gen_loc_global_set_t;

/**通用位置本地集的参数。*/
typedef struct {
    int16_t  local_north;       /*!< 本地坐标（北）*/
    int16_t  local_east;        /*!< 本地坐标（东）*/
    int16_t  local_altitude;    /*!< 当地海拔高度*/
    uint8_t  floor_number;      /*!< 楼层编号*/
    uint16_t uncertainty;       /*!< 不确定性*/
} esp_ble_mesh_gen_loc_local_set_t;

/**泛型用户属性Get的参数。*/
typedef struct {
    uint16_t property_id;       /*!< 标识通用用户属性的属性ID*/
} esp_ble_mesh_gen_user_property_get_t;

/**通用用户属性集的参数。*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用用户属性的属性ID*/
    struct net_buf_simple *property_value;  /*!< 用户属性的原始值*/
} esp_ble_mesh_gen_user_property_set_t;

/**泛型管理属性Get的参数。*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用管理属性的属性ID*/
} esp_ble_mesh_gen_admin_property_get_t;

/**通用管理属性集的参数。*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用管理属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举*/
    struct net_buf_simple *property_value;  /*!< 管理属性的原始值*/
} esp_ble_mesh_gen_admin_property_set_t;

/**泛型制造商属性Get的参数。*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用制造商属性的属性ID*/
} esp_ble_mesh_gen_manufacturer_property_get_t;

/**通用制造商属性集的参数。*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用制造商属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举*/
} esp_ble_mesh_gen_manufacturer_property_set_t;

/**通用客户端属性Get的参数。*/
typedef struct {
    uint16_t property_id;   /*!< 元素中存在起始客户端属性ID*/
} esp_ble_mesh_gen_client_properties_get_t;

/**
 * @brief 通用客户端模型获取消息联合
 */
typedef union {
    esp_ble_mesh_gen_user_property_get_t         user_property_get;         /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_GET*/
    esp_ble_mesh_gen_admin_property_get_t        admin_property_get;        /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_GET*/
    esp_ble_mesh_gen_manufacturer_property_get_t manufacturer_property_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_SET*/
    esp_ble_mesh_gen_client_properties_get_t     client_properties_get;     /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_CLIENT_PROPERTIES_GET*/
} esp_ble_mesh_generic_client_get_state_t;

/**
 * @brief 通用客户端模型集消息联合
 */
typedef union {
    esp_ble_mesh_gen_onoff_set_t          onoff_set;            /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET和ESP_BLE_MESH_MODEL _OP_GEN-ONOFF_SET_UNACK*/
    esp_ble_mesh_gen_level_set_t          level_set;            /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_SET和ESP_BLE_MESH_MODE_OP_GEN_LEVEL_SET_UNACK*/
    esp_ble_mesh_gen_delta_set_t          delta_set;            /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_DELTA_SET和ESP_BLE_MESH_MODE_OP_GEN_DELTA_SET_UNACK*/
    esp_ble_mesh_gen_move_set_t           move_set;             /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_MOVE_SET和ESP_BLE_MESH_MODE_OP_GEN_MOVE_SET_UNACK*/
    esp_ble_mesh_gen_def_trans_time_set_t def_trans_time_set;   /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_SET和ESP_BLE_MESH_MODE_OP_GEN_DEF_TRANS-TIME_SET_UNACK*/
    esp_ble_mesh_gen_onpowerup_set_t      power_set;            /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_SET和ESP_BLE_MESH_MODE_OP_GEN_ONPOWER UP_SET_UNACK*/
    esp_ble_mesh_gen_power_level_set_t    power_level_set;      /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_SET和ESP_BLE-MESH_MODE_OP_GEN_POWER_SET_UNACK*/
    esp_ble_mesh_gen_power_default_set_t  power_default_set;    /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_SET和ESP_BLE_MESH_MODE_OP_GEN_POWERDEFAULT_SET_UNACK*/
    esp_ble_mesh_gen_power_range_set_t    power_range_set;      /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_SET和ESP_BLE_MESH_MODE_OP_GEN_POWER-RANGE_SET_UNACK*/
    esp_ble_mesh_gen_loc_global_set_t     loc_global_set;       /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_SET和ESP_BLE_MESH_MODE_OP_GEN_LOC_GLOBAL_SET_UNACK*/
    esp_ble_mesh_gen_loc_local_set_t      loc_local_set;        /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_SET和ESP_BLE-MESH_MODE_OP_GEN_LOC_LOCAL_SET_UNACK*/
    esp_ble_mesh_gen_user_property_set_t  user_property_set;    /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_SET和ESP_BLE-MESH_MODE_OP_GEN_USERPROPERTY_SET_NACK*/
    esp_ble_mesh_gen_admin_property_set_t admin_property_set;   /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_SET和ESP_BLE_MESH_MODE_OP_GEN_ADMIN-PROPERTY_SET_UNACK*/
    esp_ble_mesh_gen_manufacturer_property_set_t manufacturer_property_set; /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_SET和ESP_BLE_MESH_MODE_OP_GEN_MANUFACTURER_PROPERTY_SET_UNACK*/
} esp_ble_mesh_generic_client_set_state_t;

/**
 *  @brief 蓝牙网格通用客户端模型获取和设置回调参数结构。
 */

/**通用开关状态参数。*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    uint8_t present_onoff;  /*!< Generic OnOff状态的当前值*/
    uint8_t target_onoff;   /*!< Generic OnOff状态的目标值（可选）*/
    uint8_t remain_time;    /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_gen_onoff_status_cb_t;

/**通用级别状态的参数。*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    int16_t present_level;  /*!< 通用级别状态的当前值*/
    int16_t target_level;   /*!< 通用级别状态的目标值（可选）*/
    uint8_t remain_time;    /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_gen_level_status_cb_t;

/**通用默认转换时间状态的参数。*/
typedef struct {
    uint8_t trans_time;     /*!< 通用默认过渡时间状态的值*/
} esp_ble_mesh_gen_def_trans_time_status_cb_t;

/**Generic OnPowerUp Status的参数。*/
typedef struct {
    uint8_t onpowerup;      /*!< Generic OnPowerUp状态的值*/
} esp_ble_mesh_gen_onpowerup_status_cb_t;

/**通用功率电平状态参数。*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t present_power; /*!< 通用功率实际状态的当前值*/
    uint16_t target_power;  /*!< 通用功率实际状态的目标值（可选）*/
    uint8_t  remain_time;   /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_gen_power_level_status_cb_t;

/**通用电源上次状态参数。*/
typedef struct {
    uint16_t power;         /*!< Generic Power Last状态的值*/
} esp_ble_mesh_gen_power_last_status_cb_t;

/**通用电源默认状态参数。*/
typedef struct {
    uint16_t power;         /*!< Generic Default Last状态的值*/
} esp_ble_mesh_gen_power_default_status_cb_t;

/**通用功率范围状态参数。*/
typedef struct {
    uint8_t  status_code;   /*!< 请求消息的状态代码*/
    uint16_t range_min;     /*!< 通用功率范围状态的范围最小值字段*/
    uint16_t range_max;     /*!< 通用功率范围状态的范围最大值字段的值*/
} esp_ble_mesh_gen_power_range_status_cb_t;

/**通用电池状态参数。*/
typedef struct {
    uint32_t battery_level     : 8;  /*!< 通用电池电量状态值*/
    uint32_t time_to_discharge : 24; /*!< 一般电池放电时间值*/
    uint32_t time_to_charge    : 24; /*!< 通用电池充电时间值*/
    uint32_t flags             : 8;  /*!< 通用电池标志状态值*/
} esp_ble_mesh_gen_battery_status_cb_t;

/**通用位置全局状态参数。*/
typedef struct {
    int32_t global_latitude;  /*!< 全球坐标（纬度）*/
    int32_t global_longitude; /*!< 全球坐标（经度）*/
    int16_t global_altitude;  /*!< 全球海拔高度*/
} esp_ble_mesh_gen_loc_global_status_cb_t;

/**通用位置本地状态参数。*/
typedef struct {
    int16_t  local_north;     /*!< 本地坐标（北）*/
    int16_t  local_east;      /*!< 本地坐标（东）*/
    int16_t  local_altitude;  /*!< 当地海拔高度*/
    uint8_t  floor_number;    /*!< 楼层编号*/
    uint16_t uncertainty;     /*!< 不确定性*/
} esp_ble_mesh_gen_loc_local_status_cb_t;

/**通用用户属性状态的参数。*/
typedef struct {
    struct net_buf_simple *property_ids;    /*!< 缓冲区包含N个用户属性ID序列*/
} esp_ble_mesh_gen_user_properties_status_cb_t;

/**通用用户属性状态的参数。*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t property_id;   /*!< 标识通用用户属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举（可选）*/
    struct net_buf_simple *property_value;  /*!< 用户属性的原始值（C.1）*/
} esp_ble_mesh_gen_user_property_status_cb_t;

/**通用管理属性状态的参数。*/
typedef struct {
    struct net_buf_simple *property_ids; /*!< 缓冲区包含N个管理属性ID序列*/
} esp_ble_mesh_gen_admin_properties_status_cb_t;

/**通用管理属性状态的参数。*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t property_id;   /*!< 标识通用管理属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举（可选）*/
    struct net_buf_simple *property_value;  /*!< 管理属性的原始值（C.1）*/
} esp_ble_mesh_gen_admin_property_status_cb_t;

/**通用制造商属性状态的参数。*/
typedef struct {
    struct net_buf_simple *property_ids;    /*!< 缓冲区包含N个制造商属性ID序列*/
} esp_ble_mesh_gen_manufacturer_properties_status_cb_t;

/**通用制造商属性状态参数。*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t property_id;   /*!< 标识通用制造商属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举（可选）*/
    struct net_buf_simple *property_value;  /*!< 制造商财产的原始值（C.1）*/
} esp_ble_mesh_gen_manufacturer_property_status_cb_t;

/**通用客户端属性状态的参数。*/
typedef struct {
    struct net_buf_simple *property_ids;    /*!< 缓冲区包含N个客户端属性ID序列*/
} esp_ble_mesh_gen_client_properties_status_cb_t;

/**
 * @brief 通用客户端模型接收到消息联合
 */
typedef union {
    esp_ble_mesh_gen_onoff_status_cb_t             onoff_status;            /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS*/
    esp_ble_mesh_gen_level_status_cb_t             level_status;            /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_STATUS*/
    esp_ble_mesh_gen_def_trans_time_status_cb_t    def_trans_time_status;   /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_STATUS*/
    esp_ble_mesh_gen_onpowerup_status_cb_t         onpowerup_status;        /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_STATUS*/
    esp_ble_mesh_gen_power_level_status_cb_t       power_level_status;      /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_STATUS*/
    esp_ble_mesh_gen_power_last_status_cb_t        power_last_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_LAST_STATUS*/
    esp_ble_mesh_gen_power_default_status_cb_t     power_default_status;    /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_STATUS*/
    esp_ble_mesh_gen_power_range_status_cb_t       power_range_status;      /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_STATUS*/
    esp_ble_mesh_gen_battery_status_cb_t           battery_status;          /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_BATTERY_STATUS*/
    esp_ble_mesh_gen_loc_global_status_cb_t        location_global_status;  /*!< 对于ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_STATUS*/
    esp_ble_mesh_gen_loc_local_status_cb_t         location_local_status;   /*!< ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_STATUS */
    esp_ble_mesh_gen_user_properties_status_cb_t   user_properties_status;  /*!< ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTIES_STATUS */
    esp_ble_mesh_gen_user_property_status_cb_t     user_property_status;    /*!< ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_STATUS */
    esp_ble_mesh_gen_admin_properties_status_cb_t  admin_properties_status; /*!< ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTIES_STATUS */
    esp_ble_mesh_gen_admin_property_status_cb_t    admin_property_status;   /*!< ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_STATUS */
    esp_ble_mesh_gen_manufacturer_properties_status_cb_t manufacturer_properties_status; /*!< ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTIES_STATUS */
    esp_ble_mesh_gen_manufacturer_property_status_cb_t   manufacturer_property_status;   /*!< ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_STATUS */
    esp_ble_mesh_gen_client_properties_status_cb_t       client_properties_status;       /*!< ESP_BLE_MESH_MODEL_OP_GEN_CLIENT_PROPERTIES_STATUS */
} esp_ble_mesh_gen_client_status_cb_t;

/**通用客户端模型回调参数*/
typedef struct {
    int error_code;                                 /*!< 适当的错误代码*/
    esp_ble_mesh_client_common_param_t *params;     /*!< 客户端公用参数。*/
    esp_ble_mesh_gen_client_status_cb_t status_cb;  /*!< 通用状态消息回调值*/
} esp_ble_mesh_generic_client_cb_param_t;

/**此枚举值是通用客户端模型的事件*/
typedef enum {
    ESP_BLE_MESH_GENERIC_CLIENT_GET_STATE_EVT,
    ESP_BLE_MESH_GENERIC_CLIENT_SET_STATE_EVT,
    ESP_BLE_MESH_GENERIC_CLIENT_PUBLISH_EVT,
    ESP_BLE_MESH_GENERIC_CLIENT_TIMEOUT_EVT,
    ESP_BLE_MESH_GENERIC_CLIENT_EVT_MAX,
} esp_ble_mesh_generic_client_cb_event_t;

/**
 *  @brief 蓝牙网格通用客户端模型功能。
 */

/**
 * @brief   通用客户端模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_generic_client_cb_t)(esp_ble_mesh_generic_client_cb_event_t event,
                                                  esp_ble_mesh_generic_client_cb_param_t *param);

/**
 * @brief       注册BLE Mesh通用客户端模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_generic_client_callback(esp_ble_mesh_generic_client_cb_t callback);

/**
 * @brief       使用通用客户端模型获取消息获取通用服务器模型状态的值。
 *
 * @note        如果要查找此API接受的操作码和相应含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_generic_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   get_state: 指向通用获取消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_generic_client_get_state(esp_ble_mesh_client_common_param_t *params,
                                                esp_ble_mesh_generic_client_get_state_t *get_state);

/**
 * @brief       使用通用客户端模型设置消息设置通用服务器模型状态的值。
 *
 * @note        如果要查找此API所接受的操作码和相应含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_generic_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   set_state: 指向通用设置消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_generic_client_set_state(esp_ble_mesh_client_common_param_t *params,
                                                esp_ble_mesh_generic_client_set_state_t *set_state);

/**
 * @brief 与通用服务器模型相关的上下文。
 */

/** @def    ESP_BLE_MESH_MODEL_GEN_ONOFF_SRV
 *
 *  @brief  定义新的通用OnOff服务器模型。
 *
 *  @note   1.通用OnOff服务器模型是根模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_off_srv_t的指针。
 *
 *  @return 新建通用OnOff服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_ONOFF_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_LEVEL_SRV
 *
 *  @brief  定义新的通用级服务器模型。
 *
 *  @note   1.通用级服务器模型是根模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_level_srv_t的指针。
 *
 *  @return 新建通用级别服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_LEVEL_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_LEVEL_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_DEF_TRANS_TIME_SRV
 *
 *  @brief  定义新的通用默认过渡时间服务器模型。
 *
 *  @note   1.通用默认过渡时间服务器模型是根模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_def_trans_time_srv_t的指针。
 *
 *  @return 新建通用默认过渡时间服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_DEF_TRANS_TIME_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_POWER_ONOFF_SRV
 *
 *  @brief  定义新的通用电源开关服务器模型。
 *
 *  @note   1.通用电源开关服务器模型扩展了通用开关服务器模型。当该模型出现在元件上时，相应的通用电源开/关设置服务器模型也应出现。2.此模型可用于表示不符合已定义的任何模型描述但支持开/关通用属性的各种设备。3.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_power_onoff_srv_t的指针。
 *
 *  @return 新的通用电源开关服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_POWER_ONOFF_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_POWER_ONOFF_SETUP_SRV
 *
 *  @brief  定义新的通用电源开/关设置服务器模型。
 *
 *  @note   1.通用电源开关设置服务器模型扩展了通用电源开关服务器模型和通用默认转换时间服务器模型。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_power_onoff_setup_srv_t的指针。
 *
 *  @return 新的通用电源开关安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_POWER_ONOFF_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_POWER_LEVEL_SRV
 *
 *  @brief  定义新的通用电源级别服务器模型。
 *
 *  @note   1.通用电源级别服务器模型扩展了通用电源开/关服务器模型和通用级别服务器模型。当该模型出现在网元上时，相应的通用功率级设置服务器模型也应出现。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_power_level_srv_t的指针。
 *
 *  @return 新的通用电源级别服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_POWER_LEVEL_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_POWER_LEVEL_SETUP_SRV
 *
 *  @brief  定义新的通用电源级别设置服务器模型。
 *
 *  @note   1.通用电源级别设置服务器模型扩展了通用电源级别服务器模型和通用电源开/关设置服务器模型。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_power_level_setup_srv_t的指针。
 *
 *  @return 新建通用电源级别设置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_POWER_LEVEL_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_BATTERY_SRV
 *
 *  @brief  定义新的通用电池服务器模型。
 *
 *  @note   1.通用电池服务器模型是根模型。2.该模型应支持模型发布和模型订阅。3.该模型可用于表示由电池供电的元件。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_battery_srv_t的指针。
 *
 *  @return 新建通用电池服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_BATTERY_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_BATTERY_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_LOCATION_SRV
 *
 *  @brief  定义新的通用位置服务器模型。
 *
 *  @note   1.通用位置服务器模型是根模型。当该模型出现在网元上时，相应的通用位置设置服务器模型也应出现。2.该模型应支持模型发布和模型订阅。3.模型可用于表示知道其位置（全局或局部）的元素。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_location_srv_t的指针。
 *
 *  @return 新建通用位置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_LOCATION_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_LOCATION_SETUP_SRV
 *
 *  @brief  定义新的通用位置设置服务器模型。
 *
 *  @note   1.通用位置设置服务器模型扩展了通用位置服务器模型。2.该模型应支持模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_location_setup_srv_t的指针。
 *
 *  @return 新建通用位置设置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_LOCATION_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_USER_PROP_SRV
 *
 *  @brief  定义新的通用用户属性服务器模型。
 *
 *  @note   1.通用用户属性服务器模型是根模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_user_prop_srv_t的指针。
 *
 *  @return 新建通用用户属性服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_USER_PROP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_USER_PROP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_ADMIN_PROP_SRV
 *
 *  @brief  定义新的通用管理属性服务器模型。
 *
 *  @note   1.通用管理属性服务器模型扩展了通用用户属性服务器模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_admin_prop_srv_t的指针。
 *
 *  @return 新建通用管理属性服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_ADMIN_PROP_SRV(srv_pub, srv_data)            \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV,    \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_MANUFACTURER_PROP_SRV
 *
 *  @brief  定义新的通用制造商属性服务器模型。
 *
 *  @note   1.通用制造商属性服务器模型扩展了通用用户属性服务器模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_manu_prop_srv_t的指针。
 *
 *  @return 新建通用制造商属性服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_MANUFACTURER_PROP_SRV(srv_pub, srv_data)            \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV,    \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_GEN_CLIENT_PROP_SRV
 *
 *  @brief  定义新的通用用户属性服务器模型。
 *
 *  @note   1.通用客户端属性服务器模型是根模型。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_gen_client_prop_srv_t的指针。
 *
 *  @return 新建通用客户端属性服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_GEN_CLIENT_PROP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV,     \
                    NULL, srv_pub, srv_data)

/**通用开/关状态参数*/
typedef struct {
    uint8_t onoff;          /*!< Generic OnOff状态的当前值*/
    uint8_t target_onoff;   /*!< Generic OnOff状态的目标值*/
} esp_ble_mesh_gen_onoff_state_t;

/**通用OnOff服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用OnOff服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_onoff_state_t state;       /*!< Generic OnOff状态的参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
} esp_ble_mesh_gen_onoff_srv_t;

/**通用级别状态参数*/
typedef struct {
    int16_t level;          /*!< 通用级别状态的当前值*/
    int16_t target_level;   /*!< 通用级别状态的目标值*/

    /**
     * 当一个新事务开始时，level应该设置为last_last，并使用“level+incoming delta”来计算目标级别。换句话说，“last_level”用于记录上一个事务的“level”，“last_delta”用于记录先前接收的delta_level值。
     */
    int16_t last_level; /*!< 通用级别状态的最后一个值*/
    int32_t last_delta; /*!< 通用级别状态的最后一次增量更改*/

    bool move_start;    /*!< 指示是否已开始转换通用级别状态*/
    bool positive;      /*!< 指示转换是正的还是负的*/
} esp_ble_mesh_gen_level_state_t;

/**通用级服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用级服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_level_state_t state;       /*!< 通用级别状态的参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
    int32_t tt_delta_level;                     /*!< 电平状态转换的增量变化值*/
} esp_ble_mesh_gen_level_srv_t;

/**通用默认转换时间状态参数*/
typedef struct {
    uint8_t trans_time;     /*!< 通用默认过渡时间状态的值*/
} esp_ble_mesh_gen_def_trans_time_state_t;

/**通用默认过渡时间服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向通用默认转换时间服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_def_trans_time_state_t state;  /*!< 通用默认转换时间状态的参数*/
} esp_ble_mesh_gen_def_trans_time_srv_t;

/**通用OnPowerUp状态参数*/
typedef struct {
    uint8_t onpowerup;      /*!< Generic OnPowerUp状态的值*/
} esp_ble_mesh_gen_onpowerup_state_t;

/**通用电源开关服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用电源开关服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_onpowerup_state_t *state;  /*!< Generic OnPowerUp状态的参数*/
} esp_ble_mesh_gen_power_onoff_srv_t;

/**通用电源开关设置服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用电源开关设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_onpowerup_state_t *state;  /*!< Generic OnPowerUp状态的参数*/
} esp_ble_mesh_gen_power_onoff_setup_srv_t;

/**通用功率电平状态参数*/
typedef struct {
    uint16_t power_actual;          /*!< 通用功率实际状态的当前值*/
    uint16_t target_power_actual;   /*!< 通用功率实际状态的目标值*/

    uint16_t power_last;            /*!< Generic Power Last状态的值*/
    uint16_t power_default;         /*!< 常规电源默认状态的值*/

    uint8_t  status_code;           /*!< 设置通用功率范围状态的状态代码*/
    uint16_t power_range_min;       /*!< 通用功率范围状态的最小值*/
    uint16_t power_range_max;       /*!< 通用功率范围状态的最大值*/
} esp_ble_mesh_gen_power_level_state_t;

/**通用功率级服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向通用电源级别服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_power_level_state_t *state;    /*!< 通用功率电平状态的参数*/
    esp_ble_mesh_last_msg_info_t last;              /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition;     /*!< 状态转换参数*/
    int32_t tt_delta_level;                         /*!< 电平状态转换的增量变化值*/
} esp_ble_mesh_gen_power_level_srv_t;

/**通用功率级设置服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向通用电源级别设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_power_level_state_t *state;    /*!< 通用功率电平状态的参数*/
} esp_ble_mesh_gen_power_level_setup_srv_t;

/**通用电池状态参数*/
typedef struct {
    uint32_t battery_level : 8,         /*!< 常规电池电量状态的值*/
             time_to_discharge : 24;    /*!< 通用电池放电时间状态的值*/
    uint32_t time_to_charge : 24,       /*!< 通用电池充电时间状态的值*/
             battery_flags : 8;         /*!< 通用电池标志状态的值*/
} esp_ble_mesh_gen_battery_state_t;

/**通用电池服务器型号的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用电池服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_battery_state_t state;     /*!< 通用电池状态参数*/
} esp_ble_mesh_gen_battery_srv_t;

/**通用位置状态参数*/
typedef struct {
    int32_t  global_latitude;   /*!< “全球纬度”字段的值*/
    int32_t  global_longitude;  /*!< “全球经度”字段的值*/
    int16_t  global_altitude;   /*!< “全球高度”字段的值*/
    int16_t  local_north;       /*!< 本地北字段的值*/
    int16_t  local_east;        /*!< 本地东部字段的值*/
    int16_t  local_altitude;    /*!< 本地高度字段的值*/
    uint8_t  floor_number;      /*!< 楼层编号字段的值*/
    uint16_t uncertainty;       /*!< 不确定性字段的值*/
} esp_ble_mesh_gen_location_state_t;

/**通用位置服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用位置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_location_state_t *state;   /*!< 通用位置状态的参数*/
} esp_ble_mesh_gen_location_srv_t;

/**通用位置设置服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用位置设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_gen_location_state_t *state;   /*!< 通用位置状态的参数*/
} esp_ble_mesh_gen_location_setup_srv_t;

/**此枚举值是泛型用户属性的访问值*/
typedef enum {
    ESP_BLE_MESH_GEN_USER_ACCESS_PROHIBIT,
    ESP_BLE_MESH_GEN_USER_ACCESS_READ,
    ESP_BLE_MESH_GEN_USER_ACCESS_WRITE,
    ESP_BLE_MESH_GEN_USER_ACCESS_READ_WRITE,
} esp_ble_mesh_gen_user_prop_access_t;

/**此枚举值是通用管理属性的访问值*/
typedef enum {
    ESP_BLE_MESH_GEN_ADMIN_NOT_USER_PROP,
    ESP_BLE_MESH_GEN_ADMIN_ACCESS_READ,
    ESP_BLE_MESH_GEN_ADMIN_ACCESS_WRITE,
    ESP_BLE_MESH_GEN_ADMIN_ACCESS_READ_WRITE,
} esp_ble_mesh_gen_admin_prop_access_t;

/**此枚举值是泛型制造商属性的访问值*/
typedef enum {
    ESP_BLE_MESH_GEN_MANU_NOT_USER_PROP,
    ESP_BLE_MESH_GEN_MANU_ACCESS_READ,
} esp_ble_mesh_gen_manu_prop_access_t;

/**泛型属性状态的参数*/
typedef struct {
    uint16_t id;            /*!< 用户/管理员/制造商属性ID的值*/
    uint8_t  user_access;   /*!< “用户访问”字段的值*/
    uint8_t  admin_access;  /*!< “管理员访问”字段的值*/
    uint8_t  manu_access;   /*!< 制造商访问字段的值*/
    struct net_buf_simple *val; /*!< 用户/管理员/制造商属性的值*/
} esp_ble_mesh_generic_property_t;

/**通用用户属性服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向通用用户属性服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    uint8_t property_count;                         /*!< 通用用户属性计数*/
    esp_ble_mesh_generic_property_t *properties;    /*!< 通用用户属性状态的参数*/
} esp_ble_mesh_gen_user_prop_srv_t;

/**通用管理属性服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向通用管理属性服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    uint8_t property_count;                         /*!< 通用管理属性计数*/
    esp_ble_mesh_generic_property_t *properties;    /*!< 通用管理属性状态的参数*/
} esp_ble_mesh_gen_admin_prop_srv_t;

/**通用制造商属性服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向通用制造商属性服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;        /*!< 服务器模型接收消息的响应控制*/
    uint8_t property_count;                         /*!< 通用制造商属性计数*/
    esp_ble_mesh_generic_property_t *properties;    /*!< 通用制造商属性状态的参数*/
} esp_ble_mesh_gen_manu_prop_srv_t;

/**通用客户端属性服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向通用客户端属性服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    uint8_t id_count;                           /*!< 通用客户端属性ID计数*/
    uint16_t *property_ids;                     /*!< 通用客户端属性状态的参数*/
} esp_ble_mesh_gen_client_prop_srv_t;

/**通用OnOff Set状态更改事件的参数*/
typedef struct {
    uint8_t onoff;          /*!< Generic OnOff状态的值*/
} esp_ble_mesh_state_change_gen_onoff_set_t;

/**通用级别集状态更改事件的参数*/
typedef struct {
    int16_t level;          /*!< 通用级别状态的值*/
} esp_ble_mesh_state_change_gen_level_set_t;

/**通用增量集状态更改事件的参数*/
typedef struct {
    int16_t level;          /*!< 通用级别状态的值*/
} esp_ble_mesh_state_change_gen_delta_set_t;

/**通用移动集状态更改事件的参数*/
typedef struct {
    int16_t level;          /*!< 通用级别状态的值*/
} esp_ble_mesh_state_change_gen_move_set_t;

/**通用默认转换时间集状态更改事件的参数*/
typedef struct {
    uint8_t trans_time;     /*!< 通用默认过渡时间状态的值*/
} esp_ble_mesh_state_change_gen_def_trans_time_set_t;

/**Generic OnPowerUp Set状态更改事件的参数*/
typedef struct {
    uint8_t onpowerup;      /*!< Generic OnPowerUp状态的值*/
} esp_ble_mesh_state_change_gen_onpowerup_set_t;

/**通用功率电平设置状态更改事件的参数*/
typedef struct {
    uint16_t power;         /*!< 通用功率实际状态的值*/
} esp_ble_mesh_state_change_gen_power_level_set_t;

/**通用电源默认设置状态更改事件的参数*/
typedef struct {
    uint16_t power;         /*!< 通用电源默认状态的值*/
} esp_ble_mesh_state_change_gen_power_default_set_t;

/**通用功率范围设置状态更改事件的参数*/
typedef struct {
    uint16_t range_min;     /*!< 通用功率范围状态的最小值*/
    uint16_t range_max;     /*!< 通用功率范围状态的最大值*/
} esp_ble_mesh_state_change_gen_power_range_set_t;

/**通用位置全局设置状态更改事件的参数*/
typedef struct {
    int32_t latitude;       /*!< 通用位置状态的全球纬度值*/
    int32_t longitude;      /*!< 通用位置状态的全球经度值*/
    int16_t altitude;       /*!< 通用位置状态的全球高度值*/
} esp_ble_mesh_state_change_gen_loc_global_set_t;

/**通用位置本地设置状态更改事件的参数*/
typedef struct {
    int16_t  north;         /*!< 通用位置状态的本地北值*/
    int16_t  east;          /*!< 通用位置状态的本地东值*/
    int16_t  altitude;      /*!< 通用位置状态的本地高度值*/
    uint8_t  floor_number;  /*!< “常规位置”状态的楼层编号值*/
    uint16_t uncertainty;   /*!< 通用位置状态的不确定性值*/
} esp_ble_mesh_state_change_gen_loc_local_set_t;

/**通用用户属性集状态更改事件的参数*/
typedef struct {
    uint16_t id;    /*!< 通用用户属性状态的属性id*/
    struct net_buf_simple *value;   /*!< 泛型用户属性状态的属性值*/
} esp_ble_mesh_state_change_gen_user_property_set_t;

/**通用管理属性集状态更改事件的参数*/
typedef struct {
    uint16_t id;        /*!< 通用管理属性状态的属性id*/
    uint8_t  access;    /*!< Generic Admin property状态的属性访问*/
    struct net_buf_simple *value;   /*!< Generic Admin property状态的属性值*/
} esp_ble_mesh_state_change_gen_admin_property_set_t;

/**通用制造商属性集状态更改事件的参数*/
typedef struct {
    uint16_t id;        /*!< 通用制造商属性状态的属性id*/
    uint8_t  access;    /*!< Generic Manufacturer property状态的属性值*/
} esp_ble_mesh_state_change_gen_manu_property_set_t;

/**
 * @brief 通用服务器模型状态更改值联合
 */
typedef union {
    /**
     * ctx中的recv_op可用于决定更改的状态。
     */
    esp_ble_mesh_state_change_gen_onoff_set_t          onoff_set;           /*!< 通用开关设置*/
    esp_ble_mesh_state_change_gen_level_set_t          level_set;           /*!< 通用级别集*/
    esp_ble_mesh_state_change_gen_delta_set_t          delta_set;           /*!< 通用增量集*/
    esp_ble_mesh_state_change_gen_move_set_t           move_set;            /*!< 通用移动集*/
    esp_ble_mesh_state_change_gen_def_trans_time_set_t def_trans_time_set;  /*!< 通用默认转换时间集*/
    esp_ble_mesh_state_change_gen_onpowerup_set_t      onpowerup_set;       /*!< 通用OnPowerUp集*/
    esp_ble_mesh_state_change_gen_power_level_set_t    power_level_set;     /*!< 通用功率电平设置*/
    esp_ble_mesh_state_change_gen_power_default_set_t  power_default_set;   /*!< 通用电源默认设置*/
    esp_ble_mesh_state_change_gen_power_range_set_t    power_range_set;     /*!< 通用功率范围设置*/
    esp_ble_mesh_state_change_gen_loc_global_set_t     loc_global_set;      /*!< 通用位置全局集*/
    esp_ble_mesh_state_change_gen_loc_local_set_t      loc_local_set;       /*!< 通用位置本地集*/
    esp_ble_mesh_state_change_gen_user_property_set_t  user_property_set;   /*!< 通用用户属性集*/
    esp_ble_mesh_state_change_gen_admin_property_set_t admin_property_set;  /*!< 通用管理属性集*/
    esp_ble_mesh_state_change_gen_manu_property_set_t  manu_property_set;   /*!< 通用制造商属性集*/
} esp_ble_mesh_generic_server_state_change_t;

/**收到的通用用户属性获取消息的上下文*/
typedef struct {
    uint16_t property_id;       /*!< 标识通用用户属性的属性ID*/
} esp_ble_mesh_server_recv_gen_user_property_get_t;

/**收到的通用管理属性获取消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用管理属性的属性ID*/
} esp_ble_mesh_server_recv_gen_admin_property_get_t;

/**收到的通用制造商属性消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用制造商属性的属性ID*/
} esp_ble_mesh_server_recv_gen_manufacturer_property_get_t;

/**收到的通用客户端属性获取消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 元素中存在起始客户端属性ID*/
} esp_ble_mesh_server_recv_gen_client_properties_get_t;

/**
 * @brief 收到通用服务器模型获取消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_gen_user_property_get_t         user_property;     /*!< 通用用户属性获取*/
    esp_ble_mesh_server_recv_gen_admin_property_get_t        admin_property;    /*!< 通用管理属性获取*/
    esp_ble_mesh_server_recv_gen_manufacturer_property_get_t manu_property;     /*!< 通用制造商属性获取*/
    esp_ble_mesh_server_recv_gen_client_properties_get_t     client_properties; /*!< 通用客户端属性获取*/
} esp_ble_mesh_generic_server_recv_get_msg_t;

/**接收到的通用OnOff Set消息的上下文*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    uint8_t onoff;          /*!< Generic OnOff状态的目标值*/
    uint8_t tid;            /*!< 事务ID*/
    uint8_t trans_time;     /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;          /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_gen_onoff_set_t;

/**收到的通用级别集消息的上下文*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    int16_t level;          /*!< 通用级别状态的目标值*/
    uint8_t tid;            /*!< 事务ID*/
    uint8_t trans_time;     /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;          /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_gen_level_set_t;

/**收到的通用增量集消息的上下文*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    int32_t delta_level;    /*!< 通用级别状态的增量更改*/
    uint8_t tid;            /*!< 事务ID*/
    uint8_t trans_time;     /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;          /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_gen_delta_set_t;

/**收到的通用移动集消息的上下文*/
typedef struct {
    bool    op_en;          /*!< 指示是否包含可选参数*/
    int16_t delta_level;    /*!< 计算通用级别状态移动速度的增量级别步骤*/
    uint8_t tid;            /*!< 事务ID*/
    uint8_t trans_time;     /*!< 完成状态转换的时间（可选）*/
    uint8_t delay;          /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_gen_move_set_t;

/**收到的通用默认转换时间集消息的上下文*/
typedef struct {
    uint8_t trans_time;     /*!< 通用默认过渡时间状态的值*/
} esp_ble_mesh_server_recv_gen_def_trans_time_set_t;

/**接收到的通用OnPowerUp Set消息的上下文*/
typedef struct {
    uint8_t onpowerup;      /*!< Generic OnPowerUp状态的值*/
} esp_ble_mesh_server_recv_gen_onpowerup_set_t;

/**接收到的通用功率电平设置消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t power;         /*!< 通用功率实际状态的目标值*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_gen_power_level_set_t;

/**收到的通用电源默认设置消息的上下文*/
typedef struct {
    uint16_t power;         /*!< 常规电源默认状态的值*/
} esp_ble_mesh_server_recv_gen_power_default_set_t;

/**接收到的通用功率范围设置消息的上下文*/
typedef struct {
    uint16_t range_min;     /*!< 通用功率范围状态的范围最小值字段*/
    uint16_t range_max;     /*!< 通用功率范围状态的范围最大值字段的值*/
} esp_ble_mesh_server_recv_gen_power_range_set_t;

/**接收到的通用位置全局设置消息的上下文*/
typedef struct {
    int32_t global_latitude;    /*!< 全球坐标（纬度）*/
    int32_t global_longitude;   /*!< 全球坐标（经度）*/
    int16_t global_altitude;    /*!< 全球海拔高度*/
} esp_ble_mesh_server_recv_gen_loc_global_set_t;

/**接收到的通用位置本地设置消息的上下文*/
typedef struct {
    int16_t  local_north;       /*!< 本地坐标（北）*/
    int16_t  local_east;        /*!< 本地坐标（东）*/
    int16_t  local_altitude;    /*!< 当地海拔高度*/
    uint8_t  floor_number;      /*!< 楼层编号*/
    uint16_t uncertainty;       /*!< 不确定性*/
} esp_ble_mesh_server_recv_gen_loc_local_set_t;

/**收到的通用用户属性集消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用用户属性的属性ID*/
    struct net_buf_simple *property_value;  /*!< 用户属性的原始值*/
} esp_ble_mesh_server_recv_gen_user_property_set_t;

/**收到的通用管理属性集消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用管理属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举*/
    struct net_buf_simple *property_value;  /*!< 管理属性的原始值*/
} esp_ble_mesh_server_recv_gen_admin_property_set_t;

/**收到的通用制造商属性集消息的上下文*/
typedef struct {
    uint16_t property_id;   /*!< 标识通用制造商属性的属性ID*/
    uint8_t  user_access;   /*!< 指示用户访问的枚举*/
} esp_ble_mesh_server_recv_gen_manufacturer_property_set_t;

/**
 * @brief 通用服务器模型收到集合消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_gen_onoff_set_t                 onoff;             /*!< 通用开关设置/通用开关设置取消确认*/
    esp_ble_mesh_server_recv_gen_level_set_t                 level;             /*!< 通用级别集/通用级别集取消确认*/
    esp_ble_mesh_server_recv_gen_delta_set_t                 delta;             /*!< 通用增量集/通用增量集未确认*/
    esp_ble_mesh_server_recv_gen_move_set_t                  move;              /*!< 通用移动集/通用移动集取消确认*/
    esp_ble_mesh_server_recv_gen_def_trans_time_set_t        def_trans_time;    /*!< 通用默认转换时间集/通用默认转换转换时间集未确认*/
    esp_ble_mesh_server_recv_gen_onpowerup_set_t             onpowerup;         /*!< 通用OnPowerUp设置/通用OnPowerUp设置未确认*/
    esp_ble_mesh_server_recv_gen_power_level_set_t           power_level;       /*!< 通用功率电平设置/通用功率电平集取消确认*/
    esp_ble_mesh_server_recv_gen_power_default_set_t         power_default;     /*!< 通用电源默认设置/通用电源默认值设置取消确认*/
    esp_ble_mesh_server_recv_gen_power_range_set_t           power_range;       /*!< 通用功率范围设置/通用功率范围未确认*/
    esp_ble_mesh_server_recv_gen_loc_global_set_t            location_global;   /*!< 通用位置全局设置/通用位置全局集取消确认*/
    esp_ble_mesh_server_recv_gen_loc_local_set_t             location_local;    /*!< 通用位置本地设置/通用位置本地集取消确认*/
    esp_ble_mesh_server_recv_gen_user_property_set_t         user_property;     /*!< 通用用户属性集/通用用户属性设置取消确认*/
    esp_ble_mesh_server_recv_gen_admin_property_set_t        admin_property;    /*!< 通用管理属性集/通用管理属性设置取消确认*/
    esp_ble_mesh_server_recv_gen_manufacturer_property_set_t manu_property;     /*!< 通用制造商属性集/通用制造商属性设置未确认*/
} esp_ble_mesh_generic_server_recv_set_msg_t;

/**
 * @brief 通用服务器模型回调值联合
 */
typedef union {
    esp_ble_mesh_generic_server_state_change_t state_change;    /*!< ESP_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT */
    esp_ble_mesh_generic_server_recv_get_msg_t get;     /*!< ESP_BLE_MESH_GENERIC_SERVER_RECV_GET_MSG_EVT */
    esp_ble_mesh_generic_server_recv_set_msg_t set;     /*!< ESP_BLE_MESH_GENERIC_SERVER_RECV_SET_MSG_EVT */
} esp_ble_mesh_generic_server_cb_value_t;

/**通用服务器模型回调参数*/
typedef struct {
    esp_ble_mesh_model_t  *model;   /*!< 指向通用服务器模型的指针*/
    esp_ble_mesh_msg_ctx_t ctx;     /*!< 收到消息的上下文*/
    esp_ble_mesh_generic_server_cb_value_t value;   /*!< 收到的通用消息的值*/
} esp_ble_mesh_generic_server_cb_param_t;

/**此枚举值是通用服务器模型的事件*/
typedef enum {
    /**
     * 1.当get_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当收到Generic get消息时，不会将任何事件回调到应用层。2.当set_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当收到通用设置/设置未确认消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT,
    /**
     * 当get_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到GenericGet消息时，此事件将回调到应用程序层。
     */
    ESP_BLE_MESH_GENERIC_SERVER_RECV_GET_MSG_EVT,
    /**
     * 当set_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到通用设置/设置未确认消息时，此事件将回调到应用程序层。
     */
    ESP_BLE_MESH_GENERIC_SERVER_RECV_SET_MSG_EVT,
    ESP_BLE_MESH_GENERIC_SERVER_EVT_MAX,
} esp_ble_mesh_generic_server_cb_event_t;

/**
 *  @brief Bluetooth Mesh通用服务器模型功能。
 */

/**
 * @brief   通用服务器模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_generic_server_cb_t)(esp_ble_mesh_generic_server_cb_event_t event,
                                                  esp_ble_mesh_generic_server_cb_param_t *param);

/**
 * @brief       注册BLE Mesh通用服务器模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_generic_server_callback(esp_ble_mesh_generic_server_cb_t callback);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_GENERIC_MODEL_API_H_ */

