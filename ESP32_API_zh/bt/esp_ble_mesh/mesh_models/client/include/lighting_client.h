/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网状照明客户端模型API。
 */

#ifndef _LIGHTING_CLIENT_H_
#define _LIGHTING_CLIENT_H_

#include "client_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 轻型客户端模型通用结构*/
typedef bt_mesh_client_user_data_t      bt_mesh_light_client_t;
typedef bt_mesh_client_internal_data_t  light_internal_data_t;

/* 照明客户端模型回调*/
extern const struct bt_mesh_model_cb bt_mesh_lighting_client_cb;

/* 轻型客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_light_lightness_cli_op[];

/** @def BLE_MESH_MODEL_LIGHT_LIGHTNESS_CLI
 *
 *  定义新的轻型客户端模型。请注意，对于应用程序希望具有轻量级客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_light_lightness_cli的指针。
 *
 *  @return 新的轻型客户端模型实例。
 */
#define BLE_MESH_MODEL_LIGHT_LIGHTNESS_CLI(cli_pub, cli_data)   \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI,   \
            bt_mesh_light_lightness_cli_op, cli_pub, cli_data, &bt_mesh_lighting_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_light_lightness_client_t;

struct bt_mesh_light_lightness_status {
    bool     op_en;             /* 指示是否包含可选参数*/
    uint16_t present_lightness; /* 光亮度实际状态的现值*/
    uint16_t target_lightness;  /* 灯光亮度实际状态目标值（可选）*/
    uint8_t  remain_time;       /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_lightness_linear_status {
    bool     op_en;             /* 指示是否包含可选参数*/
    uint16_t present_lightness; /* 光亮度线性状态的现值*/
    uint16_t target_lightness;  /* 光亮度线性状态目标值（可选）*/
    uint8_t  remain_time;       /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_lightness_last_status {
    uint16_t lightness; /* “Light Lightness Last”状态的值*/
};

struct bt_mesh_light_lightness_default_status {
    uint16_t lightness; /* “灯光亮度”默认状态的值*/
};

struct bt_mesh_light_lightness_range_status {
    uint8_t  status_code; /* 请求消息的状态代码*/
    uint16_t range_min;   /* 亮度范围状态的最小范围字段值*/
    uint16_t range_max;   /* 灯光亮度范围状态的范围最大字段值*/
};

struct bt_mesh_light_lightness_set {
    bool     op_en;      /* 指示是否包含可选参数*/
    uint16_t lightness;  /* 灯光亮度实际状态目标值*/
    uint8_t  tid;        /* 事务标识符*/
    uint8_t  trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t  delay;      /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_lightness_linear_set {
    bool     op_en;      /* 指示是否包含可选参数*/
    uint16_t lightness;  /* 光亮度线性状态目标值*/
    uint8_t  tid;        /* 事务标识符*/
    uint8_t  trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t  delay;      /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_lightness_default_set {
    uint16_t lightness;  /* “灯光亮度默认”状态的值*/
};

struct bt_mesh_light_lightness_range_set {
    uint16_t range_min; /* 亮度范围状态的最小范围字段值*/
    uint16_t range_max; /* 灯光亮度范围状态的范围最大字段值*/
};

/* 轻型CTL客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_light_ctl_cli_op[];

/** @def BLE_MESH_MODEL_LIGHT_CTL_CLI
 *
 *  定义新的灯光CTL客户端模型。请注意，对于应用程序希望具有轻型CTL客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_light_ctl_cli的指针。
 *
 *  @return 新的灯光CTL客户端模型实例。
 */
#define BLE_MESH_MODEL_LIGHT_CTL_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_LIGHT_CTL_CLI,     \
            bt_mesh_light_ctl_cli_op, cli_pub, cli_data, &bt_mesh_lighting_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_light_ctl_client_t;

struct bt_mesh_light_ctl_status {
    bool     op_en;                   /* 指示是否包含可选参数*/
    uint16_t present_ctl_lightness;   /* 光ctl亮度状态的当前值*/
    uint16_t present_ctl_temperature; /* 光ctl温度状态的当前值*/
    uint16_t target_ctl_lightness;    /* 灯光ctl亮度状态目标值（可选）*/
    uint16_t target_ctl_temperature;  /* 光ctl温度状态目标值（C.1）*/
    uint8_t  remain_time;             /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_ctl_temperature_status {
    bool     op_en;                   /* 指示是否包含可选参数*/
    uint16_t present_ctl_temperature; /* 光ctl温度状态的当前值*/
    uint16_t present_ctl_delta_uv;    /* 光ctl delta UV状态的当前值*/
    uint16_t target_ctl_temperature;  /* 灯光ctl温度状态目标值（可选）*/
    uint16_t target_ctl_delta_uv;     /* 光ctlδUV状态的目标值（C.1）*/
    uint8_t  remain_time;             /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_ctl_temperature_range_status {
    uint8_t  status_code; /* 请求消息的状态代码*/
    uint16_t range_min;   /* 温度范围值最小光场ctl温度范围状态*/
    uint16_t range_max;   /* 温度范围值最大光场ctl温度范围状态*/
};

struct bt_mesh_light_ctl_default_status {
    uint16_t lightness;   /* 灯光亮度默认状态的值*/
    uint16_t temperature; /* 灯光温度默认状态值*/
    int16_t  delta_uv;    /* 光增量UV默认状态的值*/
};

struct bt_mesh_light_ctl_set {
    bool     op_en;           /* 指示是否包含可选参数*/
    uint16_t ctl_lightness;   /* 灯光ctl亮度状态目标值*/
    uint16_t ctl_temperature; /* 灯光ctl温度状态目标值*/
    int16_t  ctl_delta_uv;    /* 光ctl delta UV状态的目标值*/
    uint8_t  tid;             /* 事务标识符*/
    uint8_t  trans_time;      /* 完成状态转换的时间（可选）*/
    uint8_t  delay;           /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_ctl_temperature_set {
    bool     op_en;           /* 指示是否包含可选参数*/
    uint16_t ctl_temperature; /* 灯光ctl温度状态目标值*/
    int16_t  ctl_delta_uv;    /* 光ctl delta UV状态的目标值*/
    uint8_t  tid;             /* 事务标识符*/
    uint8_t  trans_time;      /* 完成状态转换的时间（可选）*/
    uint8_t  delay;           /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_ctl_temperature_range_set {
    uint16_t range_min; /* 温度范围值最小光场ctl温度范围状态*/
    uint16_t range_max; /* 温度范围值最大光场ctl温度范围状态*/
};

struct bt_mesh_light_ctl_default_set {
    uint16_t lightness;   /* 灯光亮度默认状态的值*/
    uint16_t temperature; /* 灯光温度默认状态值*/
    int16_t  delta_uv;    /* 光增量UV默认状态的值*/
};

/* 轻型HSL客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_light_hsl_cli_op[];

/** @def BLE_MESH_MODEL_LIGHT_HSL_CLI
 *
 *  定义新的轻型HSL客户端模型。请注意，对于应用程序希望具有轻型HSL客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_light_hsl_cli的指针。
 *
 *  @return 新的轻型HSL客户端模型实例。
 */
#define BLE_MESH_MODEL_LIGHT_HSL_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_LIGHT_HSL_CLI,     \
            bt_mesh_light_hsl_cli_op, cli_pub, cli_data, &bt_mesh_lighting_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_light_hsl_client_t;

struct bt_mesh_light_hsl_status {
    bool     op_en;          /* 指示是否包含可选参数*/
    uint16_t hsl_lightness;  /* 轻hsl亮度状态的当前值*/
    uint16_t hsl_hue;        /* 光hsl色调状态的当前值*/
    uint16_t hsl_saturation; /* 光hsl饱和状态的当前值*/
    uint8_t  remain_time;    /* 完成状态转换的时间（可选）*/
};

struct bt_mesh_light_hsl_target_status {
    bool     op_en;                 /* 指示是否包含可选参数*/
    uint16_t hsl_lightness_target;  /* 轻hsl亮度状态目标值*/
    uint16_t hsl_hue_target;        /* 灯光hsl色调状态的目标值*/
    uint16_t hsl_saturation_target; /* 光hsl饱和状态的目标值*/
    uint8_t  remain_time;           /* 完成状态转换的时间（可选）*/
};

struct bt_mesh_light_hsl_hue_status {
    bool     op_en;       /* 指示是否包含可选参数*/
    uint16_t present_hue; /* 光hsl色调状态的当前值*/
    uint16_t target_hue;  /* 灯光hsl色调状态的目标值（可选）*/
    uint8_t  remain_time; /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_hsl_saturation_status {
    bool     op_en;              /* 指示是否包含可选参数*/
    uint16_t present_saturation; /* 光hsl饱和状态的当前值*/
    uint16_t target_saturation;  /* 光hsl饱和状态的目标值（可选）*/
    uint8_t  remain_time;        /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_hsl_default_status {
    uint16_t lightness;  /* 灯光亮度默认状态的值*/
    uint16_t hue;        /* 灯光色调默认状态的值*/
    uint16_t saturation; /* 光饱和度默认状态的值*/
};

struct bt_mesh_light_hsl_range_status {
    uint8_t  status_code;          /* 请求消息的状态代码*/
    uint16_t hue_range_min;        /* 光hsl色域状态的色域最小值*/
    uint16_t hue_range_max;        /* 光hsl色域状态的色域最大值*/
    uint16_t saturation_range_min; /* 光hsl饱和范围状态的饱和范围最小场值*/
    uint16_t saturation_range_max; /* 光hsl饱和范围状态的饱和范围最大场值*/
};

struct bt_mesh_light_hsl_set {
    bool     op_en;          /* 指示是否包含可选参数*/
    uint16_t hsl_lightness;  /* 轻hsl亮度状态目标值*/
    uint16_t hsl_hue;        /* 灯光hsl色调状态的目标值*/
    uint16_t hsl_saturation; /* 光hsl饱和状态的目标值*/
    uint8_t  tid;            /* 事务标识符*/
    uint8_t  trans_time;     /* 完成状态转换的时间（可选）*/
    uint8_t  delay;          /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_hsl_hue_set {
    bool     op_en;      /* 指示是否包含可选参数*/
    uint16_t hue;        /* 灯光hsl色调状态的目标值*/
    uint8_t  tid;        /* 事务标识符*/
    uint8_t  trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t  delay;      /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_hsl_saturation_set {
    bool     op_en;      /* 指示是否包含可选参数*/
    uint16_t saturation; /* 灯光hsl色调状态的目标值*/
    uint8_t  tid;        /* 事务标识符*/
    uint8_t  trans_time; /* 完成状态转换的时间（可选）*/
    uint8_t  delay;      /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_hsl_default_set {
    uint16_t lightness;  /* 灯光亮度默认状态的值*/
    uint16_t hue;        /* 灯光色调默认状态的值*/
    uint16_t saturation; /* 光饱和度默认状态的值*/
};

struct bt_mesh_light_hsl_range_set {
    uint16_t hue_range_min;        /* 光hsl色域状态的色域最小值*/
    uint16_t hue_range_max;        /* 光hsl色域状态的色域最大值*/
    uint16_t saturation_range_min; /* 光hsl饱和范围状态的饱和范围最小场值*/
    uint16_t saturation_range_max; /* 光hsl饱和范围状态的饱和范围最大场值*/
};

/* 轻型xyL客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_light_xyl_cli_op[];

/** @def BLE_MESH_MODEL_LIGHT_XYL_CLI
 *
 *  定义新的轻型xyL客户端模型。请注意，对于应用程序希望具有轻型xyL客户端模型的每个元素，都需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_light_xyl_cli的指针。
 *
 *  @return 新的轻型xyL客户端模型实例。
 */
#define BLE_MESH_MODEL_LIGHT_XYL_CLI(cli_pub, cli_data)     \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_LIGHT_XYL_CLI,     \
            bt_mesh_light_xyl_cli_op, cli_pub, cli_data, &bt_mesh_lighting_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_light_xyl_client_t;

struct bt_mesh_light_xyl_status {
    bool     op_en;         /* 指示是否包含可选参数*/
    uint16_t xyl_lightness; /* 灯光xyL亮度状态的当前值*/
    uint16_t xyl_x;         /* Light xyL x状态的当前值*/
    uint16_t xyl_y;         /* Light xyL y状态的当前值*/
    uint8_t  remain_time;   /* 完成状态转换的时间（可选）*/
};

struct bt_mesh_light_xyl_target_status {
    bool     op_en;                /* 指示是否包含可选参数*/
    uint16_t target_xyl_lightness; /* 灯光xyL亮度状态的目标值*/
    uint16_t target_xyl_x;         /* 灯光xyL x状态的目标值*/
    uint16_t target_xyl_y;         /* 灯光xyL y状态的目标值*/
    uint8_t  remain_time;          /* 完成状态转换的时间（可选）*/
};

struct bt_mesh_light_xyl_default_status {
    uint16_t lightness; /* “灯光亮度默认”状态的值*/
    uint16_t xyl_x;     /* 灯光xyL x默认状态的值*/
    uint16_t xyl_y;     /* 灯光xyL y默认状态的值*/
};

struct bt_mesh_light_xyl_range_status {
    uint8_t  status_code;     /* 请求消息的状态代码*/
    uint16_t xyl_x_range_min; /* 灯光xyL x范围状态的xyL x Range Min字段的值*/
    uint16_t xyl_x_range_max; /* 灯光xyL x范围状态的xyL x Range Max字段的值*/
    uint16_t xyl_y_range_min; /* 灯光xyL y范围状态的xyL y Range Min字段的值*/
    uint16_t xyl_y_range_max; /* 灯光xyL y范围状态的xyL y Range Max字段的值*/
};

struct bt_mesh_light_xyl_set {
    bool     op_en;         /* 指示是否包含可选参数*/
    uint16_t xyl_lightness; /* 灯光xyL亮度状态的目标值*/
    uint16_t xyl_x;         /* 灯光xyL x状态的目标值*/
    uint16_t xyl_y;         /* 灯光xyL y状态的目标值*/
    uint8_t  tid;           /* 事务标识符*/
    uint8_t  trans_time;    /* 完成状态转换的时间（可选）*/
    uint8_t  delay;         /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_xyl_default_set {
    uint16_t lightness; /* “灯光亮度默认”状态的值*/
    uint16_t xyl_x;     /* 灯光xyL x默认状态的值*/
    uint16_t xyl_y;     /* 灯光xyL y默认状态的值*/
};

struct bt_mesh_light_xyl_range_set {
    uint16_t xyl_x_range_min; /* 灯光xyL x范围状态的xyL x Range Min字段的值*/
    uint16_t xyl_x_range_max; /* 灯光xyL x范围状态的xyL x Range Max字段的值*/
    uint16_t xyl_y_range_min; /* 灯光xyL y范围状态的xyL y Range Min字段的值*/
    uint16_t xyl_y_range_max; /* 灯光xyL y范围状态的xyL y Range Max字段的值*/
};

/* 轻型LC客户端模型上下文*/
extern const struct bt_mesh_model_op bt_mesh_light_lc_cli_op[];

/** @def BLE_MESH_MODEL_LIGHT_LC_CLI
 *
 *  定义新的轻型lc客户端模型。请注意，对于应用程序希望具有轻型lc客户端模型的每个元素，需要重复此API。
 *  @param cli_pub  指向唯一结构bt_mesh_model_pub的指针。
 *  @param cli_data 指向唯一结构bt_mesh_light_lc_cli的指针。
 *
 *  @return 新的轻型lc客户端模型实例。
 */
#define BLE_MESH_MODEL_LIGHT_LC_CLI(cli_pub, cli_data)      \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_LIGHT_LC_CLI,      \
            bt_mesh_light_lc_cli_op, cli_pub, cli_data, &bt_mesh_lighting_client_cb)

typedef bt_mesh_client_user_data_t  bt_mesh_light_lc_client_t;

struct bt_mesh_light_lc_mode_status {
    uint8_t mode; /* 轻LC模式状态的当前值*/
};

struct bt_mesh_light_lc_om_status {
    uint8_t mode; /* 轻型LC占用模式状态的当前值*/
};

struct bt_mesh_light_lc_light_onoff_status {
    bool    op_en;               /* 指示是否包含可选参数*/
    uint8_t present_light_onoff; /* Light LC Light OnOff状态的当前值*/
    uint8_t target_light_onoff;  /* Light LC Light OnOff状态的目标值（可选）*/
    uint8_t remain_time;         /* 完成状态转换的时间（C.1）*/
};

struct bt_mesh_light_lc_property_status {
    uint16_t light_lc_property_id;  /* 标识轻型LC属性的属性ID*/
    struct net_buf_simple *light_lc_property_value; /* 轻型LC属性的原始值*/
};

struct bt_mesh_light_lc_mode_set {
    uint8_t mode; /* 轻LC模式状态的目标值*/
};

struct bt_mesh_light_lc_om_set {
    uint8_t mode; /* 轻型LC占用模式状态的目标值*/
};

struct bt_mesh_light_lc_light_onoff_set {
    bool    op_en;       /* 指示是否包含可选参数*/
    uint8_t light_onoff; /* Light LC Light OnOff状态的目标值*/
    uint8_t tid;         /* 事务标识符*/
    uint8_t trans_time;  /* 完成状态转换的时间（可选）*/
    uint8_t delay;       /* 指示消息执行延迟（C.1）*/
};

struct bt_mesh_light_lc_property_get {
    uint16_t light_lc_property_id;  /* 标识轻型LC属性的属性ID*/
};

struct bt_mesh_light_lc_property_set {
    uint16_t light_lc_property_id;  /* 标识轻型LC属性的属性ID*/
    struct net_buf_simple *light_lc_property_value; /* 轻型LC属性的原始值*/
};

/**
 * @brief 调用此函数以获取灯光状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  get:    指示灯获取消息值的指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_light_client_get_state(bt_mesh_client_common_param_t *common, void *get);

/**
 * @brief 调用此函数以设置灯光状态。
 *
 * @param[in]  common: 消息公共信息结构
 * @param[in]  set:    灯光设置消息值指针
 *
 * @return 零成功，其他失败
 */
int bt_mesh_light_client_set_state(bt_mesh_client_common_param_t *common, void *set);

#ifdef __cplusplus
}
#endif

#endif /* _LIGHTING_CLIENT_H_ */

