/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格通用客户端模型API。
 */

#ifndef _GENERIC_CLIENT_H_
#define _GENERIC_CLIENT_H_

#include "client_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 通用客户端模型通用结构*/
typedef bt_mesh_client_user_data_t      bt_mesh_generic_client_t;
typedef bt_mesh_client_internal_data_t  generic_internal_data_t;

/* 通用客户端模型回调*/
extern const struct bt_mesh_model_cb bt_mesh_generic_client_cb;

/* 通用OnOff客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_onoff_cli_op[];

/** @def BLE_MESH_MODEL_GEN_ONOFF_CLI
 *
 *  定义一个新的通用onoff客户端模型。注意，对于应用程序希望在其上具有通用onoff客户端模型的每个元素，都需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_onoff_cli的指针。
 *
 *  @return 新的通用onoff客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_ONOFF_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_ONOFF_CLI,     \
            bt_mesh_gen_onoff_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_onoff_client_t;

struct bt_mesh_gen_onoff_status {
    bool    op_en;         /* 指示是否包含可选参数*/
    uint8_t present_onoff; /* 通用开关状态的现值*/
    uint8_t target_onoff;  /* Generic OnOff状态的目标值（可选）*/
    uint8_t remain_time;   /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_gen_onoff_set {
    bool    op_en;      /* 指示是否包含可选参数*/
    uint8_t onoff;      /* Generic OnOff状态的目标值*/
    uint8_t tid;        /* 事务标识符*/
    uint8_t trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t delay;      /* 指示消息执行延迟（C.1）*/
};

/* 通用级客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_level_cli_op[];

/** @def BLE_MESH_MODEL_GEN_LEVEL_CLI
 *
 *  定义新的通用级别客户端模型。注意，对于应用程序希望在其上具有通用级客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_level_cli的指针。
 *
 *  @return 新的通用级客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_LEVEL_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_LEVEL_CLI,     \
            bt_mesh_gen_level_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_level_client_t;

struct bt_mesh_gen_level_status {
    bool    op_en;         /* 指示是否包含可选参数*/
    int16_t present_level; /* 通用级别状态的当前值*/
    int16_t target_level;  /* 通用级别状态的目标值（可选）*/
    uint8_t remain_time;   /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_gen_level_set {
    bool    op_en;      /* 指示是否包含可选参数*/
    int16_t level;      /* 通用级别状态的目标值*/
    uint8_t tid;        /* 事务标识符*/
    uint8_t trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t delay;      /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_gen_delta_set {
    bool    op_en;        /* 指示是否包含可选参数*/
    int32_t delta_level;  /* 通用级别状态的增量更改*/
    uint8_t tid;          /* 事务标识符*/
    uint8_t trans_time;   /* 完成状态转换的时间（可选）*/
    uint8_t delay;        /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_gen_move_set {
    bool    op_en;       /* 指示是否包含可选参数*/
    int16_t delta_level; /* 计算通用级别状态移动速度的增量级别步骤*/
    uint8_t tid;         /* 事务标识符*/
    uint8_t trans_time;  /* 完成状态转换的时间（可选）*/
    uint8_t delay;       /* 指示消息执行延迟（C.1）*/
};

/* 通用默认转换时间客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_def_trans_time_cli_op[];

/** @def BLE_MESH_MODEL_GEN_DEF_TRANS_TIME_CLI
 *
 *  定义新的通用默认过渡时间客户端模型。注意，对于应用程序希望在其上具有通用默认转换客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_def_trans_time_cli的指针。
 *
 *  @return 新的通用默认转换时间客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_DEF_TRANS_TIME_CLI(cli_pub, cli_data)    \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI,    \
            bt_mesh_gen_def_trans_time_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_def_trans_time_client_t;

struct bt_mesh_gen_def_trans_time_set {
    uint8_t trans_time;  /* 通用默认过渡时间状态的值*/
};

struct bt_mesh_gen_def_trans_time_status {
    uint8_t trans_time;  /* 通用默认过渡时间状态的值*/
};

/* 通用电源开/关客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_power_onoff_cli_op[];

/** @def BLE_MESH_MODEL_GEN_POWER_ONOFF_CLI
 *
 *  定义一个新的通用通断客户端模型。请注意，对于应用程序希望打开通用电源关闭客户端模型的每个元素，都需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_power_onoff_cli的指针。
 *
 *  @return 新的通用电源关闭客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_POWER_ONOFF_CLI(cli_pub, cli_data)   \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI,   \
            bt_mesh_gen_power_onoff_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_power_onoff_client_t;

struct bt_mesh_gen_onpowerup_set {
    uint8_t onpowerup;  /* Generic OnPowerUp状态的值*/
};

struct bt_mesh_gen_onpowerup_status {
    uint8_t onpowerup;  /* Generic OnPowerUp状态的值*/
};

/* 通用电源级别客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_power_level_cli_op[];

/** @def BLE_MESH_MODEL_GEN_POWER_LEVEL_CLI
 *
 *  定义新的通用电源级别客户端模型。注意，对于应用程序希望在其上具有通用功率级客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_power_level_cli的指针。
 *
 *  @return 新的通用电源级别客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_POWER_LEVEL_CLI(cli_pub, cli_data)   \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI,   \
            bt_mesh_gen_power_level_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_power_level_client_t;

struct bt_mesh_gen_power_level_status {
    bool     op_en;         /* 指示是否包含可选参数*/
    uint16_t present_power; /* 通用功率实际状态的现值*/
    uint16_t target_power;  /* 通用功率实际状态的目标值（可选）*/
    uint8_t  remain_time;   /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_gen_power_last_status {
    uint16_t power; /* Generic Power Last状态的值*/
};

struct bt_mesh_gen_power_default_status {
    uint16_t power; /* Generic Default Last状态的值*/
};

struct bt_mesh_gen_power_range_status {
    uint8_t  status_code; /* 请求消息的状态代码*/
    uint16_t range_min;   /* 通用功率范围状态的范围最小值字段*/
    uint16_t range_max;   /* 通用功率范围状态的范围最大值字段的值*/
};

struct bt_mesh_gen_power_level_set {
    bool     op_en;      /* 指示是否包含可选参数*/
    uint16_t power;      /* 通用功率实际状态的目标值*/
    uint8_t  tid;        /* 事务标识符*/
    uint8_t  trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t  delay;      /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_gen_power_default_set {
    uint16_t power;  /* 常规电源默认状态的值*/
};

struct bt_mesh_gen_power_range_set {
    uint16_t range_min; /* 通用功率范围状态的范围最小值字段*/
    uint16_t range_max; /* 通用功率范围状态的范围最大值字段的值*/
};

/* 通用电池客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_battery_cli_op[];

/** @def BLE_MESH_MODEL_GEN_BATTERY_CLI
 *
 *  定义新的通用电池客户端模型。注意，对于应用程序希望在其上具有通用电池客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_battery_cli的指针。
 *
 *  @return 新的通用电池客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_BATTERY_CLI(cli_pub, cli_data)   \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_BATTERY_CLI,   \
            bt_mesh_gen_battery_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_battery_client_t;

struct bt_mesh_gen_battery_status {
    uint32_t battery_level     : 8;  /* 通用电池电量状态值*/
    uint32_t time_to_discharge : 24; /* 一般电池放电时间值*/
    uint32_t time_to_charge    : 24; /* 通用电池充电时间值*/
    uint32_t flags             : 8;  /* 通用电池标志状态值*/
};

/* 通用位置客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_location_cli_op[];

/** @def BLE_MESH_MODEL_GEN_LOCATION_CLI
 *
 *  定义新的通用位置客户端模型。注意，对于应用程序希望在其上具有通用位置客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_location_cli的指针。
 *
 *  @return 新的通用位置客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_LOCATION_CLI(cli_pub, cli_data)  \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_LOCATION_CLI,  \
            bt_mesh_gen_location_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_location_client_t;

struct bt_mesh_gen_loc_global_status {
    int32_t global_latitude;  /* 全球坐标（纬度）*/
    int32_t global_longitude; /* 全球坐标（经度）*/
    int16_t global_altitude;  /* 全球海拔高度*/
};

struct bt_mesh_gen_loc_local_status {
    int16_t  local_north;    /* 本地坐标（北）*/
    int16_t  local_east;     /* 本地坐标（东）*/
    int16_t  local_altitude; /* 当地海拔高度*/
    uint8_t  floor_number;   /* 楼层编号*/
    uint16_t uncertainty;    /* 不确定性*/
};

struct bt_mesh_gen_loc_global_set {
    int32_t global_latitude;  /* 全球坐标（纬度）*/
    int32_t global_longitude; /* 全球坐标（经度）*/
    int16_t global_altitude;  /* 全球海拔高度*/
};

struct bt_mesh_gen_loc_local_set {
    int16_t  local_north;    /* 本地坐标（北）*/
    int16_t  local_east;     /* 本地坐标（东）*/
    int16_t  local_altitude; /* 当地海拔高度*/
    uint8_t  floor_number;   /* 楼层编号*/
    uint16_t uncertainty;    /* 不确定性*/
};

/* 通用属性客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_gen_property_cli_op[];

/** @def BLE_MESH_MODEL_GEN_LOCATION_CLI
 *
 *  定义新的通用位置客户端模型。注意，对于应用程序希望在其上具有通用位置客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_gen_location_cli的指针。
 *
 *  @return 新的通用位置客户端模型实例。
 */
#define BLE_MESH_MODEL_GEN_PROPERTY_CLI(cli_pub, cli_data)  \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_GEN_PROP_CLI,      \
            bt_mesh_gen_property_cli_op, cli_pub, cli_data, &bt_mesh_generic_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_gen_property_client_t;

struct bt_mesh_gen_user_properties_status {
    struct net_buf_simple *user_property_ids; /* 缓冲区包含N个用户属性ID序列*/
};

struct bt_mesh_gen_user_property_status {
    bool     op_en;                   /* 指示是否包含可选参数*/
    uint16_t user_property_id;        /* 标识通用用户属性的属性ID*/
    uint8_t  user_access;             /* 指示用户访问的枚举（可选）*/
    struct net_buf_simple *user_property_value; /* 用户属性的原始值（C.1）*/
};

struct bt_mesh_gen_admin_properties_status {
    struct net_buf_simple *admin_property_ids; /* 缓冲区包含N个管理属性ID序列*/
};

struct bt_mesh_gen_admin_property_status {
    bool     op_en;                    /* 指示是否包含可选参数*/
    uint16_t admin_property_id;        /* 标识通用管理属性的属性ID*/
    uint8_t  admin_user_access;        /* 指示用户访问的枚举（可选）*/
    struct net_buf_simple *admin_property_value; /* 管理属性的原始值（C.1）*/
};

struct bt_mesh_gen_manu_properties_status {
    struct net_buf_simple *manu_property_ids; /* 缓冲区包含N个制造商属性ID序列*/
};

struct bt_mesh_gen_manu_property_status {
    bool     op_en;                   /* 指示是否包含可选参数*/
    uint16_t manu_property_id;        /* 标识通用制造商属性的属性ID*/
    uint8_t  manu_user_access;        /* 指示用户访问的枚举（可选）*/
    struct net_buf_simple *manu_property_value; /* 制造商财产的原始值（C.1）*/
};

struct bt_mesh_gen_client_properties_status {
    struct net_buf_simple *client_property_ids; /* 缓冲区包含N个客户端属性ID序列*/
};

struct bt_mesh_gen_user_property_get {
    uint16_t user_property_id;        /* 标识通用用户属性的属性ID*/
};

struct bt_mesh_gen_user_property_set {
    uint16_t user_property_id;        /* 标识通用用户属性的属性ID*/
    struct net_buf_simple *user_property_value; /* 用户属性的原始值*/
};

struct bt_mesh_gen_admin_property_get {
    uint16_t admin_property_id;        /* 标识通用管理属性的属性ID*/
};

struct bt_mesh_gen_admin_property_set {
    uint16_t admin_property_id;        /* 标识通用管理属性的属性ID*/
    uint8_t  admin_user_access;        /* 指示用户访问的枚举*/
    struct net_buf_simple *admin_property_value; /* 管理属性的原始值*/
};

struct bt_mesh_gen_manu_property_get {
    uint16_t manu_property_id; /* 标识通用制造商属性的属性ID*/
};

struct bt_mesh_gen_manu_property_set {
    uint16_t manu_property_id; /* 标识通用制造商属性的属性ID*/
    uint8_t  manu_user_access; /* 指示用户访问的枚举*/
};

struct bt_mesh_gen_client_properties_get {
    uint16_t client_property_id; /* 元素中存在起始客户端属性ID*/
};

/**
 * @brief 调用此函数以获取泛型状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  get:    通用获取消息值的指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_generic_client_get_state(bt_mesh_client_common_param_t *common, void *get);

/**
 * @brief 调用此函数以设置通用状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  set:    通用设置消息值的指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_generic_client_set_state(bt_mesh_client_common_param_t *common, void *set);

#ifdef __cplusplus
}
#endif

#endif /* _GENERIC_CLIENT_H_ */

