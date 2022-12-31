/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _SENSOR_SERVER_H_
#define _SENSOR_SERVER_H_

#include "server_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 传感器属性ID相关*/
#define INVALID_SENSOR_PROPERTY_ID          0x0000

#define SENSOR_PROPERTY_ID_LEN              0x02

/* 传感器描述符状态相关*/
#define SENSOR_DESCRIPTOR_LEN               0x08

#define SENSOR_UNSPECIFIED_POS_TOLERANCE    0x000
#define SENSOR_UNSPECIFIED_NEG_TOLERANCE    0x000

#define SENSOR_NOT_APPL_MEASURE_PERIOD      0x00

#define SENSOR_NOT_APPL_UPDATE_INTERVAL     0x00

/* 传感器设置状态相关*/
#define INVALID_SENSOR_SETTING_PROPERTY_ID  0x0000

#define SENSOR_SETTING_PROPERTY_ID_LEN      0x02
#define SENSOR_SETTING_ACCESS_LEN           0x01

#define SENSOR_SETTING_ACCESS_READ          0x01
#define SENSOR_SETTING_ACCESS_READ_WRITE    0x03

/* 传感器Cadence状态相关*/
#define SENSOR_DIVISOR_TRIGGER_TYPE_LEN     0x01
#define SENSOR_STATUS_MIN_INTERVAL_LEN      0x01

#define SENSOR_PERIOD_DIVISOR_MAX_VALUE     15

#define SENSOR_STATUS_MIN_INTERVAL_MAX      26

#define SENSOR_STATUS_TRIGGER_TYPE_CHAR     0
#define SENSOR_STATUS_TRIGGER_TYPE_UINT16   1

#define SENSOR_STATUS_TRIGGER_UINT16_LEN    0x02

/* 传感器数据状态相关*/
#define SENSOR_DATA_FORMAT_A                0x00
#define SENSOR_DATA_FORMAT_B                0x01

#define SENSOR_DATA_FORMAT_A_MPID_LEN       0x02
#define SENSOR_DATA_FORMAT_B_MPID_LEN       0x03

#define SENSOR_DATA_ZERO_LEN                0x7F

enum bt_mesh_sensor_sample_func {
    UNSPECIFIED,
    INSTANTANEOUS,
    ARITHMETIC_MEAN,
    RMS,
    MAXIMUM,
    MINIMUM,
    ACCUMULATED,
    COUNT,
};

struct sensor_descriptor {
    uint32_t positive_tolerance : 12,
             negative_tolerance : 12,
             sample_function : 8;
    uint8_t  measure_period;
    uint8_t  update_interval;
};

struct sensor_setting {
    uint16_t property_id;
    uint8_t  access;
    /* 或使用联合来包括所有可能的类型*/
    struct net_buf_simple *raw;
};

struct sensor_cadence {
    uint8_t period_divisor : 7,
            trigger_type : 1;
    struct net_buf_simple *trigger_delta_down;
    struct net_buf_simple *trigger_delta_up;
    uint8_t min_interval;
    struct net_buf_simple *fast_cadence_low;
    struct net_buf_simple *fast_cadence_high;
};

struct sensor_data {
    /**
     * 格式A：长度字段是从1开始的uint4值（有效范围0x0–0xF，表示范围为1–16）。格式B：长度字段是从1开始的uint7值（有效范围0x0–0x7F，表示范围为1–127）。值0x7F表示长度为零。
     */
    uint8_t format : 1,
            length : 7;
    struct net_buf_simple *raw_value;
};

struct sensor_series_column {
    struct net_buf_simple *raw_value_x;
    struct net_buf_simple *column_width;
    struct net_buf_simple *raw_value_y;
};

struct bt_mesh_sensor_state {
    uint16_t sensor_property_id;

    /* 在元素的整个生命周期中保持不变*/
    struct sensor_descriptor descriptor;

    /* 每个传感器可能存在多个传感器设置状态。传感器设置属性ID值对于识别元件内传感器的每个传感器属性ID应是唯一的。
     */
    const uint8_t setting_count;
    struct sensor_setting *settings;

    /* 基于引用“非标量特性”（如“直方图”或“复合特性”）的设备属性，传感器可能不支持传感器Cadence状态。
     */
    struct sensor_cadence *cadence;

    struct sensor_data sensor_data;

    /* 由传感器测量的值可以组织为阵列（并且表示为一系列列，例如直方图）。1.传感器原始值X字段具有由传感器属性ID定义的大小和表示，并表示X轴上列的左角。2.“传感器列宽”字段具有由传感器属性ID定义的大小和表示形式，并表示X轴上的列宽度。3.传感器原始值Y字段具有由传感器属性ID定义的大小和表示，并表示Y轴上的列高度。注：不包括传感器属性定义的箱外值。例如，如果直方图被定义为表示“给定温度范围内的灯运行小时数”的3个区间，并且区间为[40，60）、[60，80）和[80100]，则不包括[40，100]范围之外的任何小时。
     */
    struct sensor_series_column series_column;
};

/* 1.传感器状态的多个实例可以存在于同一模型中，前提是每个实例具有传感器属性ID的唯一值，以允许区分实例。2.注意：多传感器内的传感器数量受传感器描述符状态消息有效载荷大小的限制。可以使用单个未分段访问消息发送单个传感器描述符。使用分段和重组（SAR），最多可发送38个传感器描述符状态。
 */

struct bt_mesh_sensor_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    const uint8_t state_count;
    struct bt_mesh_sensor_state *states;
};

struct bt_mesh_sensor_setup_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    const uint8_t state_count;
    struct bt_mesh_sensor_state *states;
};

typedef union {
    struct {
        uint16_t id;
        uint8_t  period_divisor : 7,
                 trigger_type : 1;
        struct net_buf_simple *trigger_delta_down;
        struct net_buf_simple *trigger_delta_up;
        uint8_t min_interval;
        struct net_buf_simple *fast_cadence_low;
        struct net_buf_simple *fast_cadence_high;
    } sensor_cadence_set;
    struct {
        uint16_t id;
        uint16_t setting_id;
        struct net_buf_simple *value;
    } sensor_setting_set;
} bt_mesh_sensor_server_state_change_t;

typedef union {
    struct {
        bool     op_en;
        uint16_t id;
    } sensor_descriptor_get;
    struct {
        uint16_t id;
    } sensor_cadence_get;
    struct {
        uint16_t id;
    } sensor_settings_get;
    struct {
        uint16_t id;
        uint16_t setting_id;
    } sensor_setting_get;
    struct {
        bool     op_en;
        uint16_t id;
    } sensor_get;
    struct {
        uint16_t id;
        struct net_buf_simple *raw_x;
    } sensor_column_get;
    struct {
        bool     op_en;
        uint16_t id;
        struct net_buf_simple *raw;
    } sensor_series_get;
} bt_mesh_sensor_server_recv_get_msg_t;

typedef union {
    struct {
        uint16_t id;
        struct net_buf_simple *cadence;
    } sensor_cadence_set;
    struct {
        uint16_t id;
        uint16_t setting_id;
        struct net_buf_simple *raw;
    } sensor_setting_set;
} bt_mesh_sensor_server_recv_set_msg_t;

#ifdef __cplusplus
}
#endif

#endif /* _SENSOR_SERVER_H_ */

