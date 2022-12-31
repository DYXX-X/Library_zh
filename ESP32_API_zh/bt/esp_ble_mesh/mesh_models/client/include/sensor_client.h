/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格传感器客户端模型API。
 */

#ifndef _SENSOR_CLIENT_H_
#define _SENSOR_CLIENT_H_

#include "client_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 传感器客户端模型回调*/
extern const struct bt_mesh_model_cb bt_mesh_sensor_client_cb;

/* 传感器客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_sensor_cli_op[];

/** @def BLE_MESH_MODEL_SENSOR_CLI
 *
 *  定义新的传感器客户端模型。请注意，对于应用程序希望在其上具有传感器客户端模型的每个元素，都需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_sensor_cli的指针。
 *
 *  @return 新的传感器客户端模型实例。
 */
#define BLE_MESH_MODEL_SENSOR_CLI(cli_pub, cli_data)    \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_SENSOR_CLI,    \
            bt_mesh_sensor_cli_op, cli_pub, cli_data, &bt_mesh_sensor_client_cb)

typedef bt_mesh_client_user_data_t      bt_mesh_sensor_client_t;
typedef bt_mesh_client_internal_data_t  sensor_internal_data_t;

struct bt_mesh_sensor_descriptor_status {
    struct net_buf_simple *descriptor; /* 8位字节传感器描述符序列（可选）*/
};

struct bt_mesh_sensor_cadence_status {
    uint16_t property_id;              /* 传感器的属性*/
    struct net_buf_simple *sensor_cadence_value; /* 传感器节奏状态值*/
};

struct bt_mesh_sensor_settings_status {
    uint16_t sensor_property_id;              /* 标识传感器的属性ID*/
    struct net_buf_simple *sensor_setting_property_ids; /* 一系列N个传感器设置属性ID（可选）*/
};

struct bt_mesh_sensor_setting_status {
    bool     op_en;                      /* 指示是否包含可选参数*/
    uint16_t sensor_property_id;         /* 标识传感器的属性ID*/
    uint16_t sensor_setting_property_id; /* 标识传感器内设置的设置ID*/
    uint8_t  sensor_setting_access;      /* 设置的读/写访问权限（可选）*/
    struct net_buf_simple *sensor_setting_raw; /* 设置的原始值*/
};

struct bt_mesh_sensor_status {
    struct net_buf_simple *marshalled_sensor_data; /* 传感器数据状态值（可选）*/
};

struct bt_mesh_sensor_column_status {
    uint16_t property_id;             /* 标识传感器和Y轴的属性*/
    struct net_buf_simple *sensor_column_value; /* 左侧传感器列状态值*/
};

struct bt_mesh_sensor_series_status {
    uint16_t property_id;             /* 标识传感器和Y轴的属性*/
    struct net_buf_simple *sensor_series_value; /* 传感器系列状态的左侧值*/
};

struct bt_mesh_sensor_descriptor_get {
    bool     op_en;       /* 指示是否包含可选参数*/
    uint16_t property_id; /* 传感器的属性ID（可选）*/
};

struct bt_mesh_sensor_cadence_get {
    uint16_t property_id; /* 传感器的属性ID*/
};

struct bt_mesh_sensor_cadence_set {
    uint16_t property_id;                     /* 传感器的属性ID*/
    uint8_t  fast_cadence_period_divisor : 7, /* 发布期间的除数*/
             status_trigger_type : 1;         /* 状态触发器增量字段的单位和格式*/
    struct net_buf_simple *status_trigger_delta_down; /* 触发状态消息的向下增量值*/
    struct net_buf_simple *status_trigger_delta_up; /* 触发状态消息的增量值*/
    uint8_t  status_min_interval;             /* 两条连续状态消息之间的最小间隔*/
    struct net_buf_simple *fast_cadence_low;  /* 快速节奏范围值低*/
    struct net_buf_simple *fast_cadence_high; /* 快速节奏范围的快速值*/
};

struct bt_mesh_sensor_settings_get {
    uint16_t sensor_property_id; /* 传感器的属性ID*/
};

struct bt_mesh_sensor_setting_get {
    uint16_t sensor_property_id;         /* 标识传感器的属性ID*/
    uint16_t sensor_setting_property_id; /* 标识传感器内设置的设置ID*/
};

struct bt_mesh_sensor_setting_set {
    uint16_t sensor_property_id;         /* 标识传感器的属性ID*/
    uint16_t sensor_setting_property_id; /* 标识传感器内设置的设置ID*/
    struct net_buf_simple *sensor_setting_raw; /* 设置的原始值*/
};

struct bt_mesh_sensor_get {
    bool     op_en;       /* 指示是否包含可选参数*/
    uint16_t property_id; /* 传感器的属性ID（可选）*/
};

struct bt_mesh_sensor_column_get {
    uint16_t property_id;     /* 标识传感器的属性*/
    struct net_buf_simple *raw_value_x; /* 标识列的原始值*/
};

struct bt_mesh_sensor_series_get {
    bool     op_en;            /* 指示是否包含可选参数*/
    uint16_t property_id;      /* 标识传感器的属性*/
    struct net_buf_simple *raw_value_x1; /* 标识起始列的原始值（可选）*/
    struct net_buf_simple *raw_value_x2; /* 识别结束列的原始值（C.1）*/
};

/**
 * @brief 调用此函数以获取传感器状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  get:    传感器获取消息值的指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_sensor_client_get_state(bt_mesh_client_common_param_t *common, void *get);

/**
 * @brief 调用此函数以设置传感器状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  set:    传感器设置消息值的指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_sensor_client_set_state(bt_mesh_client_common_param_t *common, void *set);

#ifdef __cplusplus
}
#endif

#endif /* _SENSOR_CLIENT_H_ */

