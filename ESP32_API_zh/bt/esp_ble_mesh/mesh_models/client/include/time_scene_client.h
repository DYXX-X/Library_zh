/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格时间和场景客户端模型API。
 */

#ifndef _TIME_SCENE_CLIENT_H_
#define _TIME_SCENE_CLIENT_H_

#include "client_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 时间场景客户端模型通用结构*/
typedef bt_mesh_client_user_data_t      bt_mesh_time_scene_client_t;
typedef bt_mesh_client_internal_data_t  time_scene_internal_data_t;

/* 时间场景客户端模型回调*/
extern const struct bt_mesh_model_cb bt_mesh_time_scene_client_cb;

/* 时间客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_time_cli_op[];

/** @def BLE_MESH_MODEL_TIME_CLI
 *
 *  定义新的时间客户端模型。注意，对于应用程序希望具有时间模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_time_cli的指针。
 *
 *  @return 新的时间客户端模型实例。
 */
#define BLE_MESH_MODEL_TIME_CLI(cli_pub, cli_data)      \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_TIME_CLI,      \
            bt_mesh_time_cli_op, cli_pub, cli_data, &bt_mesh_time_scene_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_time_client_t;

struct bt_mesh_time_status {
    uint8_t  tai_seconds[5];     /* 当前TAI时间（秒）*/
    uint8_t  sub_second;         /* 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;        /* 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1; /* 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta : 15; /* TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset;   /* 以15分钟为增量的本地时区偏移*/
};

struct bt_mesh_time_zone_status {
    uint8_t time_zone_offset_curr; /* 当前本地时区偏移*/
    uint8_t time_zone_offset_new;  /* 即将到来的本地时区偏移*/
    uint8_t tai_zone_change[5];    /* TAI即将到来的时区偏移更改的秒时间*/
};

struct bt_mesh_tai_utc_delta_status {
    uint16_t tai_utc_delta_curr : 15; /* TAI和UTC之间的当前差值（秒）*/
    uint16_t padding_1 : 1;           /* 始终为0b0。禁止使用其他值。*/
    uint16_t tai_utc_delta_new : 15;  /* TAI和UTC之间即将出现的差异（秒）*/
    uint16_t padding_2 : 1;           /* 始终为0b0。禁止使用其他值。*/
    uint8_t  tai_delta_change[5];     /* TAI即将到来的TAI-UTC Delta变化的秒时间*/
};

struct bt_mesh_time_role_status {
    uint8_t time_role; /* 元素的时间角色*/
};

struct bt_mesh_time_set {
    uint8_t  tai_seconds[5];     /* 当前TAI时间（秒）*/
    uint8_t  sub_second;         /* 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;        /* 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1; /* 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta : 15; /* TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset;   /* 以15分钟为增量的本地时区偏移*/
};

struct bt_mesh_time_zone_set {
    uint8_t time_zone_offset_new; /* 即将到来的本地时区偏移*/
    uint8_t tai_zone_change[5];   /* TAI即将到来的时区偏移更改的秒时间*/
};

struct bt_mesh_tai_utc_delta_set {
    uint16_t tai_utc_delta_new : 15; /* TAI和UTC之间即将出现的差异（秒）*/
    uint16_t padding : 1;            /* 始终为0b0。禁止使用其他值。*/
    uint8_t  tai_delta_change[5];    /* TAI即将到来的TAI-UTC Delta变化的秒时间*/
};

struct bt_mesh_time_role_set {
    uint8_t time_role; /* 元素的时间角色*/
};

/* 场景客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_scene_cli_op[];

/** @def BLE_MESH_MODEL_SCENE_CLI
 *
 *  定义新的场景客户端模型。请注意，需要为应用程序希望具有场景模型的每个元素重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_scene_cli的指针。
 *
 *  @return 新场景客户端模型实例。
 */
#define BLE_MESH_MODEL_SCENE_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_SCENE_CLI,     \
            bt_mesh_scene_cli_op, cli_pub, cli_data, &bt_mesh_time_scene_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_scene_client_t;

struct bt_mesh_scene_status {
    bool     op_en;         /* 指示是否包含可选参数*/
    uint8_t  status_code;   /* 上次操作的状态代码*/
    uint16_t current_scene; /* 场景当前场景的编号*/
    uint16_t target_scene;  /* 场景目标场景的编号（可选）*/
    uint8_t  remain_time;   /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_scene_register_status {
    uint8_t  status_code;   /* 上一操作的状态代码*/
    uint16_t current_scene; /* 场景当前场景的编号*/
    struct net_buf_simple *scenes; /* 存储在元素中的场景列表*/
};

struct bt_mesh_scene_store {
    uint16_t scene_number; /* 要存储的场景编号*/
};

struct bt_mesh_scene_recall {
    bool     op_en;        /* 指示是否包含可选参数*/
    uint16_t scene_number; /* 要召回的场景编号*/
    uint8_t  tid;          /* 事务标识符*/
    uint8_t  trans_time;   /* 完成状态转换的时间（可选）*/
    uint8_t  delay;        /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_scene_delete {
    uint16_t scene_number; /* 要删除的场景的编号*/
};

/* 调度器客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_scheduler_cli_op[];

/** @def BLE_MESH_MODEL_SCHEDULER_CLI
 *
 *  定义新的调度程序客户端模型。请注意，对于应用程序希望具有调度程序模型的每个元素，都需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_scheduler_cli的指针。
 *
 *  @return 新的调度程序客户端模型实例。
 */
#define BLE_MESH_MODEL_SCHEDULER_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_SCHEDULER_CLI,     \
            bt_mesh_scheduler_cli_op, cli_pub, cli_data, &bt_mesh_time_scene_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_scheduler_client_t;

struct bt_mesh_scheduler_status {
    uint16_t schedules; /* 指示调度寄存器中定义的动作的位字段*/
};

struct bt_mesh_scheduler_act_status {
    uint64_t index : 4;        /* 枚举（选择）计划寄存器条目*/
    uint64_t year : 7;         /* 行动计划年度*/
    uint64_t month : 12;       /* 行动计划月份*/
    uint64_t day : 5;          /* 操作的计划日期*/
    uint64_t hour : 5;         /* 行动计划时间*/
    uint64_t minute : 6;       /* 计划的操作分钟数*/
    uint64_t second : 6;       /* 计划的第二个动作*/
    uint64_t day_of_week : 7;  /* 计划一周中的操作天数*/
    uint64_t action : 4;       /* 在计划时间执行的操作*/
    uint64_t trans_time : 8;   /* 此操作的过渡时间*/
    uint16_t scene_number;     /* 此操作的过渡时间*/
};

struct bt_mesh_scheduler_act_get {
    uint8_t index; /* 要获取的计划注册表项的索引*/
};

struct bt_mesh_scheduler_act_set {
    uint64_t index : 4;        /* 要设置的计划寄存器项的索引*/
    uint64_t year : 7;         /* 行动计划年度*/
    uint64_t month : 12;       /* 行动计划月份*/
    uint64_t day : 5;          /* 操作的计划日期*/
    uint64_t hour : 5;         /* 行动计划时间*/
    uint64_t minute : 6;       /* 计划的操作分钟数*/
    uint64_t second : 6;       /* 计划的第二个动作*/
    uint64_t day_of_week : 7;  /* 计划一周中的操作天数*/
    uint64_t action : 4;       /* 在计划时间执行的操作*/
    uint64_t trans_time : 8;   /* 此操作的过渡时间*/
    uint16_t scene_number;     /* 此操作的过渡时间*/
};

/**
 * @brief 调用此函数以获取场景状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  get:    场景获取消息值的时间指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_time_scene_client_get_state(bt_mesh_client_common_param_t *common, void *get);

/**
 * @brief 调用此函数以设置场景状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  set:    时间场景设置消息值指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_time_scene_client_set_state(bt_mesh_client_common_param_t *common, void *set);

#ifdef __cplusplus
}
#endif

#endif /* _TIME_SCENE_CLIENT_H_ */

