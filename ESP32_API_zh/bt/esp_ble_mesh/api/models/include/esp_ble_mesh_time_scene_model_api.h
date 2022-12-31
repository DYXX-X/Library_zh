/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格时间和场景客户端模型API。
 */

#ifndef _ESP_BLE_MESH_TIME_SCENE_MODEL_API_H_
#define _ESP_BLE_MESH_TIME_SCENE_MODEL_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def    ESP_BLE_MESH_MODEL_TIME_CLI
 *
 *  @brief  定义新的时间客户端模型。
 *
 *  @note   需要为应用程序需要具有时间客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建时间客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_TIME_CLI(cli_pub, cli_data)         \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_TIME_CLI, \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_SCENE_CLI
 *
 *  @brief  定义新的场景客户端模型。
 *
 *  @note   需要为应用程序需要在其上具有场景客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建场景客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_SCENE_CLI(cli_pub, cli_data)         \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SCENE_CLI, \
                    NULL, cli_pub, cli_data)

/** @def    ESP_BLE_MESH_MODEL_SCHEDULER_CLI
 *
 *  @brief  定义新的调度器客户端模型。
 *
 *  @note   需要为应用程序需要在其上具有调度器客户端模型的每个元素调用此API。
 *
 *  @param  cli_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建计划程序客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_SCHEDULER_CLI(cli_pub, cli_data)         \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SCHEDULER_CLI, \
                    NULL, cli_pub, cli_data)

/**
 *  @brief 蓝牙网格时间场景客户端模型获取和设置参数结构。
 */

/**时间设置参数*/
typedef struct {
    uint8_t  tai_seconds[5];        /*!< 当前TAI时间（秒）*/
    uint8_t  sub_second;            /*!< 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;           /*!< 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1;    /*!< 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta : 15;    /*!< TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset;      /*!< 以15分钟为增量的本地时区偏移*/
} esp_ble_mesh_time_set_t;

/**时区设置参数*/
typedef struct {
    uint8_t time_zone_offset_new;   /*!< 即将到来的本地时区偏移*/
    uint8_t tai_zone_change[5];     /*!< TAI即将到来的时区偏移更改的秒时间*/
} esp_ble_mesh_time_zone_set_t;

/**TAI-UTC增量集的参数*/
typedef struct {
    uint16_t tai_utc_delta_new : 15;   /*!< TAI和UTC之间即将出现的差异（秒）*/
    uint16_t padding : 1;              /*!< 始终为0b0。禁止使用其他值。*/
    uint8_t tai_delta_change[5];       /*!< TAI即将到来的TAI-UTC Delta变化的秒时间*/
} esp_ble_mesh_tai_utc_delta_set_t;

/**时间角色集参数*/
typedef struct {
    uint8_t time_role;      /*!< 元素的时间角色*/
} esp_ble_mesh_time_role_set_t;

/**场景存储参数*/
typedef struct {
    uint16_t scene_number;  /*!< 要存储的场景数*/
} esp_ble_mesh_scene_store_t;

/**场景调用参数*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t scene_number;  /*!< 要召回的场景数*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_scene_recall_t;

/**场景删除参数*/
typedef struct {
    uint16_t scene_number;  /*!< 要删除的场景数*/
} esp_ble_mesh_scene_delete_t;

/**Scheduler Action Get的参数*/
typedef struct {
    uint8_t index;  /*!< 要获取的计划注册表项的索引*/
} esp_ble_mesh_scheduler_act_get_t;

/**调度器操作集的参数*/
typedef struct {
    uint64_t index : 4;         /*!< 要设置的计划寄存器项的索引*/
    uint64_t year : 7;          /*!< 行动计划年度*/
    uint64_t month : 12;        /*!< 行动计划月份*/
    uint64_t day : 5;           /*!< 操作的计划日期*/
    uint64_t hour : 5;          /*!< 行动计划时间*/
    uint64_t minute : 6;        /*!< 计划的操作分钟数*/
    uint64_t second : 6;        /*!< 计划的第二个动作*/
    uint64_t day_of_week : 7;   /*!< 计划一周中的操作天数*/
    uint64_t action : 4;        /*!< 在计划时间执行的操作*/
    uint64_t trans_time : 8;    /*!< 此操作的过渡时间*/
    uint16_t scene_number;      /*!< 此操作的过渡时间*/
} esp_ble_mesh_scheduler_act_set_t;

/**
 * @brief 时间场景客户端模型获取消息联合
 */
typedef union {
    esp_ble_mesh_scheduler_act_get_t scheduler_act_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_GET*/
} esp_ble_mesh_time_scene_client_get_state_t;

/**
 * @brief 时间场景客户端模型集消息联合
 */
typedef union {
    esp_ble_mesh_time_set_t          time_set;          /*!< 对于ESP_BLE_MESH_MODEL_OP_TIME_SET*/
    esp_ble_mesh_time_zone_set_t     time_zone_set;     /*!< 对于ESP_BLE_MESH_MODEL_OP_TIME_ZONE_SET*/
    esp_ble_mesh_tai_utc_delta_set_t tai_utc_delta_set; /*!< 对于ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_SET*/
    esp_ble_mesh_time_role_set_t     time_role_set;     /*!< 对于ESP_BLE_MESH_MODEL_OP_TIME_ROLE_SET*/
    esp_ble_mesh_scene_store_t       scene_store;       /*!< 对于ESP_BLE_MESH_MODEL_OP_CENE_STORE和ESP_BLE_MESH_MODE_OP_SCENE_STORE_UNACK*/
    esp_ble_mesh_scene_recall_t      scene_recall;      /*!< 对于ESP_BLE_MESH_MODE_OP_SCENE_RECALL和ESP_BLE-MESH_MODEL_OP_CENE_RECALL_UNACK*/
    esp_ble_mesh_scene_delete_t      scene_delete;      /*!< 对于ESP_BLE_MESH_MODEL_OP_SCENE_DELETE和ESP_BLE-MESH_MODE_OP_SCENE_DELETE_NACK*/
    esp_ble_mesh_scheduler_act_set_t scheduler_act_set; /*!< 对于ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_SET和ESP_BLE-MESH_MODE_OP_SCHEDULER_ACT_SET_UNACK*/
} esp_ble_mesh_time_scene_client_set_state_t;

/**
 *  @brief 蓝牙网格时间场景客户端模型获取和设置回调参数结构。
 */

/**时间状态参数*/
typedef struct {
    uint8_t  tai_seconds[5];           /*!< 当前TAI时间（秒）*/
    uint8_t  sub_second;               /*!< 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;              /*!< 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1;       /*!< 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta : 15;       /*!< TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset;         /*!< 以15分钟为增量的本地时区偏移*/
} esp_ble_mesh_time_status_cb_t;

/**时区状态参数*/
typedef struct {
    uint8_t time_zone_offset_curr;     /*!< 当前本地时区偏移*/
    uint8_t time_zone_offset_new;      /*!< 即将到来的本地时区偏移*/
    uint8_t tai_zone_change[5];        /*!< TAI即将到来的时区偏移更改的秒时间*/
} esp_ble_mesh_time_zone_status_cb_t;

/**TAI-UTC Delta状态参数*/
typedef struct {
    uint16_t tai_utc_delta_curr : 15;  /*!< TAI和UTC之间的当前差值（秒）*/
    uint16_t padding_1 : 1;            /*!< 始终为0b0。禁止使用其他值。*/
    uint16_t tai_utc_delta_new : 15;   /*!< TAI和UTC之间即将出现的差异（秒）*/
    uint16_t padding_2 : 1;            /*!< 始终为0b0。禁止使用其他值。*/
    uint8_t tai_delta_change[5];       /*!< TAI即将到来的TAI-UTC Delta变化的秒时间*/
} esp_ble_mesh_tai_utc_delta_status_cb_t;

/**时间角色状态参数*/
typedef struct {
    uint8_t time_role;  /*!< 元素的时间角色*/
} esp_ble_mesh_time_role_status_cb_t;

/**场景状态参数*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint8_t  status_code;   /*!< 上次操作的状态代码*/
    uint16_t current_scene; /*!< 当前场景的场景编号*/
    uint16_t target_scene;  /*!< 目标场景的场景编号（可选）*/
    uint8_t  remain_time;   /*!< 完成状态转换的时间（C.1）*/
} esp_ble_mesh_scene_status_cb_t;

/**场景注册状态参数*/
typedef struct {
    uint8_t  status_code;   /*!< 上一操作的状态代码*/
    uint16_t current_scene; /*!< 当前场景的场景编号*/
    struct net_buf_simple *scenes;  /*!< 存储在元素中的场景列表*/
} esp_ble_mesh_scene_register_status_cb_t;

/**调度器状态参数*/
typedef struct {
    uint16_t schedules;     /*!< 指示调度寄存器中定义的动作的位字段*/
} esp_ble_mesh_scheduler_status_cb_t;

/**调度器操作状态参数*/
typedef struct {
    uint64_t index : 4;         /*!< 枚举（选择）计划寄存器条目*/
    uint64_t year : 7;          /*!< 行动计划年度*/
    uint64_t month : 12;        /*!< 行动计划月份*/
    uint64_t day : 5;           /*!< 操作的计划日期*/
    uint64_t hour : 5;          /*!< 行动计划时间*/
    uint64_t minute : 6;        /*!< 计划的操作分钟数*/
    uint64_t second : 6;        /*!< 计划的第二个动作*/
    uint64_t day_of_week : 7;   /*!< 计划一周中的操作天数*/
    uint64_t action : 4;        /*!< 在计划时间执行的操作*/
    uint64_t trans_time : 8;    /*!< 此操作的过渡时间*/
    uint16_t scene_number;      /*!< 此操作的过渡时间*/
} esp_ble_mesh_scheduler_act_status_cb_t;

/**
 * @brief 时间场景客户端模型接收到消息联合
 */
typedef union {
    esp_ble_mesh_time_status_cb_t           time_status;            /*!< 对于ESP_BLE_MESH_MODEL_OP_TIME_STATUS*/
    esp_ble_mesh_time_zone_status_cb_t      time_zone_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_TIME_ZONE_STATUS*/
    esp_ble_mesh_tai_utc_delta_status_cb_t  tai_utc_delta_status;   /*!< 对于ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_STATUS*/
    esp_ble_mesh_time_role_status_cb_t      time_role_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_TIME_ROLE_STATUS*/
    esp_ble_mesh_scene_status_cb_t          scene_status;           /*!< 对于ESP_BLE_MESH_MODEL_OP_CENE_STATUS*/
    esp_ble_mesh_scene_register_status_cb_t scene_register_status;  /*!< 对于ESP_BLE_MESH_MODEL_OP_CENE_REGISTER_STATUS*/
    esp_ble_mesh_scheduler_status_cb_t      scheduler_status;       /*!< 对于ESP_BLE_MESH_MODEL_OP_SCHEDULER_STATUS*/
    esp_ble_mesh_scheduler_act_status_cb_t  scheduler_act_status;   /*!< 对于ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_STATUS*/
} esp_ble_mesh_time_scene_client_status_cb_t;

/**时间场景客户端模型回调参数*/
typedef struct {
    int error_code;                                         /*!< 适当的错误代码*/
    esp_ble_mesh_client_common_param_t        *params;      /*!< 客户端公用参数。*/
    esp_ble_mesh_time_scene_client_status_cb_t status_cb;   /*!< 场景状态消息回调值*/
} esp_ble_mesh_time_scene_client_cb_param_t;

/**此枚举值是时间场景客户端模型的事件*/
typedef enum {
    ESP_BLE_MESH_TIME_SCENE_CLIENT_GET_STATE_EVT,
    ESP_BLE_MESH_TIME_SCENE_CLIENT_SET_STATE_EVT,
    ESP_BLE_MESH_TIME_SCENE_CLIENT_PUBLISH_EVT,
    ESP_BLE_MESH_TIME_SCENE_CLIENT_TIMEOUT_EVT,
    ESP_BLE_MESH_TIME_SCENE_CLIENT_EVT_MAX,
} esp_ble_mesh_time_scene_client_cb_event_t;

/**
 *  @brief 蓝牙网格时间场景客户端模型功能。
 */

/**
 * @brief   时间场景客户端模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_time_scene_client_cb_t)(esp_ble_mesh_time_scene_client_cb_event_t event,
                                                     esp_ble_mesh_time_scene_client_cb_param_t *param);

/**
 * @brief       注册BLE网格时间场景客户端模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_time_scene_client_callback(esp_ble_mesh_time_scene_client_cb_t callback);

/**
 * @brief       使用“时间场景客户端模型”获取消息获取“时间场景服务器模型”状态的值。
 *
 * @note        如果您想知道此API接受的操作码和相应的含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_time_scene_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   get_state: 指向时间场景获取消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 */
esp_err_t esp_ble_mesh_time_scene_client_get_state(esp_ble_mesh_client_common_param_t *params,
                                                   esp_ble_mesh_time_scene_client_get_state_t *get_state);

/**
 * @brief       使用“时间场景客户端模型”设置消息设置“时间场景服务器模型”状态的值。
 *
 * @note        如果您想知道此API接受的操作码和相应的含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_time_scene_message_opcode_t
 *
 * @param[in]   params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]   set_state: 指向时间场景集消息值的指针。不应设置为NULL。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 */
esp_err_t esp_ble_mesh_time_scene_client_set_state(esp_ble_mesh_client_common_param_t *params,
                                                   esp_ble_mesh_time_scene_client_set_state_t *set_state);

/**
 * @brief 时间场景服务器模型相关上下文。
 */

/** @def    ESP_BLE_MESH_MODEL_TIME_SRV
 *
 *  @brief  定义新的时间服务器模型。
 *
 *  @note   1.时间服务器模型是根模型。当网元上存在此模型时，相应的时间设置服务器模型也应存在。2.该模型应支持模型发布和模型订阅。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_time_srv_t的指针。
 *
 *  @return 新建时间服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_TIME_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_TIME_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_TIME_SETUP_SRV
 *
 *  @brief  定义新的时间设置服务器模型。
 *
 *  @note   1.时间设置服务器模型扩展了时间服务器模型。时间是通过网状网络传播的敏感信息。2.只有经过授权的时间客户端才能更改时间和时间角色状态。应在时间设置服务器上使用专用应用程序密钥Bluetooth SIG专有，以限制仅授权的时间客户端访问服务器。3.此模型不支持订阅或发布。
 *
 *  @param  srv_data 指向唯一结构esp_ble_mesh_time_setup_srv_t的指针。
 *
 *  @return 新建时间设置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_TIME_SETUP_SRV(srv_data)                     \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_TIME_SETUP_SRV,    \
                    NULL, NULL, srv_data)

/** @def    ESP_BLE_MESH_MODEL_SCENE_SRV
 *
 *  @brief  定义新的场景服务器模型。
 *
 *  @note   1.场景服务器模型是根模型。当该模型出现在元素上时，相应的场景设置服务器模型也应出现。2.该模型应支持模型发布和模型订阅。3.模型可以仅出现在节点的Primary元素上。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_scene_srv_t的指针。
 *
 *  @return 新建场景服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_SCENE_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SCENE_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_SCENE_SETUP_SRV
 *
 *  @brief  定义新的场景设置服务器模型。
 *
 *  @note   1.场景设置服务器模型扩展了场景服务器模型和通用默认过渡时间服务器模型。2.该模型应支持模型订阅。3.模型可以仅出现在节点的Primary元素上。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_scene_setup_srv_t的指针。
 *
 *  @return 新建场景设置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_SCENE_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SCENE_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_SCHEDULER_SRV
 *
 *  @brief  定义新的调度器服务器模型。
 *
 *  @note   1.调度器服务器模型扩展了场景服务器模型。当元素上存在此模型时，相应的调度器安装服务器模型也应存在。2.该模型应支持模型发布和模型订阅。3.模型可以仅出现在节点的Primary元素上。4.模型要求元素上应存在时间服务器模型。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_scheduler_srv_t的指针。
 *
 *  @return 新建计划程序服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_SCHEDULER_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SCHEDULER_SRV,     \
                    NULL, srv_pub, srv_data)

/** @def    ESP_BLE_MESH_MODEL_SCHEDULER_SETUP_SRV
 *
 *  @brief  定义新的计划程序安装服务器模型。
 *
 *  @note   1.调度器设置服务器模型扩展了调度器服务器和场景设置服务器模型。2.该模型应支持模型订阅。3.模型可以仅出现在节点的Primary元素上。
 *
 *  @param  srv_pub  指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *  @param  srv_data 指向唯一结构esp_ble_mesh_scheduler_setup_srv_t的指针。
 *
 *  @return 新建计划程序安装服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_SCHEDULER_SETUP_SRV(srv_pub, srv_data)             \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_SCHEDULER_SETUP_SRV,     \
                    NULL, srv_pub, srv_data)

#define ESP_BLE_MESH_UNKNOWN_TAI_SECONDS        0x0000000000    /*!< 未知TAI秒*/
#define ESP_BLE_MESH_UNKNOWN_TAI_ZONE_CHANGE    0x0000000000    /*!< 区域变更的未知TAI*/
#define ESP_BLE_MESH_UNKNOWN_TAI_DELTA_CHANGE   0x0000000000    /*!< Delta变更的未知TAI*/

#define ESP_BLE_MESH_TAI_UTC_DELTA_MAX_VALUE    0x7FFF  /*!< 最大TAI-UTC Delta值*/

#define ESP_BLE_MESH_TAI_SECONDS_LEN            0x05    /*!< TAI秒的长度*/
#define ESP_BLE_MESH_TAI_OF_ZONE_CHANGE_LEN     0x05    /*!< 区域变化的TAI长度*/
#define ESP_BLE_MESH_TAI_OF_DELTA_CHANGE_LEN    0x05    /*!< Delta变化的TAI长度*/

#define ESP_BLE_MESH_INVALID_SCENE_NUMBER       0x0000  /*!< 无效的场景编号*/
#define ESP_BLE_MESH_SCENE_NUMBER_LEN           0x02    /*!< 场景编号的长度*/

#define ESP_BLE_MESH_SCHEDULE_YEAR_ANY_YEAR     0x64    /*!< 计划年度的任何一年*/

#define ESP_BLE_MESH_SCHEDULE_DAY_ANY_DAY       0x00    /*!< 计划日期的任何一天*/

#define ESP_BLE_MESH_SCHEDULE_HOUR_ANY_HOUR     0x18    /*!< 计划时间的任何时间*/
#define ESP_BLE_MESH_SCHEDULE_HOUR_ONCE_A_DAY   0x19    /*!< 计划日的任何时间*/

#define ESP_BLE_MESH_SCHEDULE_SEC_ANY_OF_HOUR   0x3C    /*!< 计划时间的任何一分钟*/
#define ESP_BLE_MESH_SCHEDULE_SEC_EVERY_15_MIN  0x3D    /*!< 计划时间的每15分钟*/
#define ESP_BLE_MESH_SCHEDULE_SEC_EVERY_20_MIN  0x3E    /*!< 计划时间的每20分钟*/
#define ESP_BLE_MESH_SCHEDULE_SEC_ONCE_AN_HOUR  0x3F    /*!< 计划时间的一次*/

#define ESP_BLE_MESH_SCHEDULE_SEC_ANY_OF_MIN    0x3C    /*!< 计划分钟的任何一秒*/
#define ESP_BLE_MESH_SCHEDULE_SEC_EVERY_15_SEC  0x3D    /*!< 计划分钟的每15秒*/
#define ESP_BLE_MESH_SCHEDULE_SEC_EVERY_20_SEC  0x3E    /*!< 每计划分钟20秒*/
#define ESP_BLE_MESH_SCHEDULE_SEC_ONCE_AN_MIN   0x3F    /*!< 计划分钟的一次*/

#define ESP_BLE_MESH_SCHEDULE_ACT_TURN_OFF      0x00    /*!< 计划操作-关闭*/
#define ESP_BLE_MESH_SCHEDULE_ACT_TURN_ON       0x01    /*!< 计划操作-打开*/
#define ESP_BLE_MESH_SCHEDULE_ACT_SCENE_RECALL  0x02    /*!< 计划动作-场景召回*/
#define ESP_BLE_MESH_SCHEDULE_ACT_NO_ACTION     0x0F    /*!< 计划操作-无操作*/

#define ESP_BLE_MESH_SCHEDULE_SCENE_NO_SCENE    0x0000  /*!< 计划场景-无场景*/

#define ESP_BLE_MESH_SCHEDULE_ENTRY_MAX_INDEX   0x0F    /*!< 计划项目的最大数量*/

#define ESP_BLE_MESH_TIME_NONE          0x00    /*!< 时间角色-无*/
#define ESP_BLE_MESH_TIME_AUTHORITY     0x01    /*!< 时间角色-网格时间权限*/
#define ESP_BLE_MESH_TIME_RELAY         0x02    /*!< 时间角色-网状时间继电器*/
#define ESP_BLE_MESH_TIME_CLINET        0x03    /*!< 时间角色-网格时间客户端*/

#define ESP_BLE_MESH_SCENE_SUCCESS      0x00    /*!< 场景操作-成功*/
#define ESP_BLE_MESH_SCENE_REG_FULL     0x01    /*!< 场景操作-场景寄存器已满*/
#define ESP_BLE_MESH_SCENE_NOT_FOUND    0x02    /*!< 场景操作-找不到场景*/

/**时间状态参数*/
typedef struct {
    struct {
        uint8_t  tai_seconds[5];            /*!< TAI Seconds状态的值*/
        uint8_t  subsecond;                 /*!< Subsecond字段的值*/
        uint8_t  uncertainty;               /*!< 不确定性字段的值*/
        uint8_t  time_zone_offset_curr;     /*!< 时区偏移电流字段的值*/
        uint8_t  time_zone_offset_new;      /*!< 时区偏移新状态的值*/
        uint8_t  tai_zone_change[5];        /*!< Chaneg区字段的TAI值*/
        uint16_t time_authority : 1,        /*!< 时间授权位的值*/
                 tai_utc_delta_curr : 15;   /*!< TAI-UTC Delta Current状态的值*/
        uint16_t tai_utc_delta_new : 15;    /*!< TAI-UTC Delta New州的价值*/
        uint8_t  tai_delta_change[5];       /*!< Delta Change字段的TAI值*/
    } time;                                 /*!< 时间状态参数*/
    uint8_t time_role;                      /*!< 时间角色状态的值*/
} esp_ble_mesh_time_state_t;

/**时间服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向时间服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_time_state_t *state;           /*!< 时间状态参数*/
} esp_ble_mesh_time_srv_t;

/**时间设置服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向时间设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_time_state_t *state;           /*!< 时间状态参数*/
} esp_ble_mesh_time_setup_srv_t;

/**
 * 1.场景存储是存储元素的当前状态的值的操作。2.存储状态的结构和含义由模型确定。要存储的状态由每个模型指定。3.场景存储操作应持久存储节点所有元素上所有模型的所有标记为“与场景一起存储”的状态的所有值。4.如果一个模型正在扩展另一个模型，则扩展模型应确定该模型的“随场景存储”行为。
 */

/**场景寄存器状态参数*/
typedef struct {
    uint16_t scene_number;  /*!< 场景编号的值*/
    uint8_t  scene_type;    /*!< 场景类型的值*/
    /**
     * 场景值可以使用并集来表示，稍后，并集包含可以存储在场景中的所有模型状态的结构。
     */
    struct net_buf_simple *scene_value; /*!< 场景值的值*/
} esp_ble_mesh_scene_register_t;

/**
 * 场景状态参数。
 *
 * 场景用作存储状态（例如，功率级或光级/颜色）的存储器库。元素的状态值可以存储为场景，并且可以稍后从场景存储器中调用。
 *
 * 场景由“场景编号”（scene Number）表示，该编号是一个16位非零网格宽值。（网格网络中最多可以有65535个场景。）场景的含义以及与其关联的状态存储容器由模型确定。
 *
 * 场景状态更改可能会启动许多并行模型转换。在这种情况下，每个单独的模型都在内部处理转换。
 *
 * 场景变换定义为一组由场景调用操作启动的单独模型变换。当单个模型过渡组中的至少一个过渡正在进行时，场景过渡正在进行。
 */
typedef struct {
    const uint16_t scene_count;             /*!< 场景状态的场景计数*/
    esp_ble_mesh_scene_register_t *scenes;  /*!< 场景状态的参数*/

    /**
     * “当前场景”状态是一个16位值，该值包含当前活动场景的“场景编号”，或者在没有活动场景时为0x0000。
     *
     * 当场景存储操作或场景调用操作成功完成时，当前场景状态值应为该操作期间使用的场景编号。
     *
     * 当“场景删除”操作导致“当前场景编号”从“场景寄存器”状态中删除时，“当前场景状态”应设置为0x0000。
     *
     * 如果标记为“与场景一起存储”的任何元素状态未因场景调用操作而发生更改，则当前场景状态的值应设置为0x0000。
     *
     * 当正在进行场景转换时，当前场景状态的值应设置为0x0000。
     */
    uint16_t current_scene;     /*!< 当前场景状态的值*/

    /**
     * “目标场景”状态是一个16位值，在进行场景转换时包含目标“场景编号”。
     *
     * 当场景转换正在进行，并且由于“场景删除”操作，目标场景编号从“场景注册”状态中删除时，目标场景状态应设置为0x0000。
     *
     * 当场景转换正在进行，并且由于场景存储操作，新的场景号存储在场景寄存器中时，目标场景状态应设置为新的场景编号。
     *
     * 当场景转换未进行时，目标场景状态的值应设置为0x0000。
     */
    uint16_t target_scene;      /*!< “目标场景”状态的值*/

    /* 指示上次操作的状态代码*/
    uint8_t status_code;        /*!< 上次场景操作的状态代码*/

    /* 指示是否正在进行场景转换*/
    bool in_progress;           /*!< 指示场景转换是否正在进行*/
} esp_ble_mesh_scenes_state_t;

/**场景服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向场景服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_scenes_state_t *state;         /*!< 场景状态的参数*/
    esp_ble_mesh_last_msg_info_t last;          /*!< 上次收到的集合消息的参数*/
    esp_ble_mesh_state_transition_t transition; /*!< 状态转换参数*/
} esp_ble_mesh_scene_srv_t;

/**场景设置服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向场景设置服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_scenes_state_t *state;         /*!< 场景状态的参数*/
} esp_ble_mesh_scene_setup_srv_t;

/**调度器寄存器状态参数*/
typedef struct {
    bool in_use;                /*!< 指明是否正在使用已注册的计划*/
    uint64_t year : 7,          /*!< 操作的计划年份值*/
             month : 12,        /*!< 操作的计划月份值*/
             day : 5,           /*!< 操作的当月计划日期的值*/
             hour : 5,          /*!< 操作的计划小时值*/
             minute : 6,        /*!< 操作的计划分钟值*/
             second : 6,        /*!< 操作的计划秒值*/
             day_of_week : 7,   /*!< 操作的计划周天数的值*/
             action : 4,        /*!< 在计划时间执行的操作值*/
             trans_time : 8;    /*!< 此操作的过渡时间值*/
    uint16_t scene_number;      /*!< 用于某些操作的“场景编号”的值*/
} esp_ble_mesh_schedule_register_t;

/**调度器状态参数*/
typedef struct {
    const uint8_t schedule_count;                   /*!< 计划程序计数*/
    esp_ble_mesh_schedule_register_t *schedules;    /*!< 最多16个预定条目*/
} esp_ble_mesh_scheduler_state_t;

/**调度器服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向计划程序服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_scheduler_state_t *state;      /*!< 调度器状态的参数*/
} esp_ble_mesh_scheduler_srv_t;

/**调度器安装服务器模型的用户数据*/
typedef struct {
    esp_ble_mesh_model_t *model;                /*!< 指向计划程序安装服务器模型的指针。内部初始化。*/
    esp_ble_mesh_server_rsp_ctrl_t rsp_ctrl;    /*!< 服务器模型接收消息的响应控制*/
    esp_ble_mesh_scheduler_state_t *state;      /*!< 调度器状态的参数*/
} esp_ble_mesh_scheduler_setup_srv_t;

/**时间设置状态更改事件的参数*/
typedef struct {
    uint8_t  tai_seconds[5];        /*!< 当前TAI时间（秒）*/
    uint8_t  subsecond;             /*!< 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;           /*!< 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1;    /*!< 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta_curr : 15;   /*!< TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset_curr;     /*!< 以15分钟为增量的本地时区偏移*/
} esp_ble_mesh_state_change_time_set_t;

/**时间状态状态更改事件的参数*/
typedef struct {
    uint8_t  tai_seconds[5];        /*!< 当前TAI时间（秒）*/
    uint8_t  subsecond;             /*!< 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;           /*!< 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1;    /*!< 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta_curr : 15;   /*!< TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset_curr;     /*!< 以15分钟为增量的本地时区偏移*/
} esp_ble_mesh_state_change_time_status_t;

/**时区设置状态更改事件的参数*/
typedef struct {
    uint8_t time_zone_offset_new;   /*!< 即将到来的本地时区偏移*/
    uint8_t tai_zone_change[5];     /*!< TAI即将到来的时区偏移更改的秒时间*/
} esp_ble_mesh_state_change_time_zone_set_t;

/**TAI UTC Delta Set状态更改事件的参数*/
typedef struct {
    uint16_t tai_utc_delta_new : 15;    /*!< TAI和UTC之间即将出现的差异（秒）*/
    uint8_t tai_delta_change[5];        /*!< TAI即将到来的TAI-UTC Delta变化的秒时间*/
} esp_ble_mesh_state_change_tai_utc_delta_set_t;

/**时间角色集状态更改事件的参数*/
typedef struct {
    uint8_t time_role;      /*!< 元素的时间角色*/
} esp_ble_mesh_state_change_time_role_set_t;

/**场景存储状态更改事件的参数*/
typedef struct {
    uint16_t scene_number;  /*!< 要存储的场景数*/
} esp_ble_mesh_state_change_scene_store_t;

/**场景调用状态更改事件的参数*/
typedef struct {
    uint16_t scene_number;  /*!< 要召回的场景数*/
} esp_ble_mesh_state_change_scene_recall_t;

/**场景删除状态更改事件的参数*/
typedef struct {
    uint16_t scene_number;  /*!< 要删除的场景数*/
} esp_ble_mesh_state_change_scene_delete_t;

/**调度器操作集状态更改事件的参数*/
typedef struct {
    uint64_t index : 4;         /*!< 要设置的计划寄存器项的索引*/
    uint64_t year : 7;          /*!< 行动计划年度*/
    uint64_t month : 12;        /*!< 行动计划月份*/
    uint64_t day : 5;           /*!< 操作的计划日期*/
    uint64_t hour : 5;          /*!< 行动计划时间*/
    uint64_t minute : 6;        /*!< 计划的操作分钟数*/
    uint64_t second : 6;        /*!< 计划的第二个动作*/
    uint64_t day_of_week : 7;   /*!< 计划一周中的操作天数*/
    uint64_t action : 4;        /*!< 在计划时间执行的操作*/
    uint64_t trans_time : 8;    /*!< 此操作的过渡时间*/
    uint16_t scene_number;      /*!< 用于某些动作的场景编号*/
} esp_ble_mesh_state_change_scheduler_act_set_t;

/**
 * @brief 时间场景服务器模型状态更改值联合
 */
typedef union {
    /**
     * ctx中的recv_op可用于决定更改的状态。
     */
    esp_ble_mesh_state_change_time_set_t          time_set;             /*!< 时间设置*/
    esp_ble_mesh_state_change_time_status_t       time_status;          /*!< 时间状态*/
    esp_ble_mesh_state_change_time_zone_set_t     time_zone_set;        /*!< 时区设置*/
    esp_ble_mesh_state_change_tai_utc_delta_set_t tai_utc_delta_set;    /*!< TAI UTC增量集*/
    esp_ble_mesh_state_change_time_role_set_t     time_role_set;        /*!< 时间角色集*/
    esp_ble_mesh_state_change_scene_store_t       scene_store;          /*!< 场景存储区*/
    esp_ble_mesh_state_change_scene_recall_t      scene_recall;         /*!< 场景召回*/
    esp_ble_mesh_state_change_scene_delete_t      scene_delete;         /*!< 场景删除*/
    esp_ble_mesh_state_change_scheduler_act_set_t scheduler_act_set;    /*!< 计划程序操作集*/
} esp_ble_mesh_time_scene_server_state_change_t;

/**收到的调度程序操作获取消息的上下文*/
typedef struct {
    uint8_t index;  /*!< 要获取的计划注册表项的索引*/
} esp_ble_mesh_server_recv_scheduler_act_get_t;

/**
 * @brief 时间场景服务器模型接收到获取消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_scheduler_act_get_t scheduler_act; /*!< 调度程序操作获取*/
} esp_ble_mesh_time_scene_server_recv_get_msg_t;

/**接收到的时间集消息的上下文*/
typedef struct {
    uint8_t  tai_seconds[5];        /*!< 当前TAI时间（秒）*/
    uint8_t  subsecond;             /*!< 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;           /*!< 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1;    /*!< 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta : 15;    /*!< TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset;      /*!< 以15分钟为增量的本地时区偏移*/
} esp_ble_mesh_server_recv_time_set_t;

/**接收到的时区设置消息的上下文*/
typedef struct {
    uint8_t time_zone_offset_new;   /*!< 即将到来的本地时区偏移*/
    uint8_t tai_zone_change[5];     /*!< TAI即将到来的时区偏移更改的秒时间*/
} esp_ble_mesh_server_recv_time_zone_set_t;

/**接收到的TAI UTC Delta Set消息的上下文*/
typedef struct {
    uint16_t tai_utc_delta_new : 15;    /*!< TAI和UTC之间即将出现的差异（秒）*/
    uint16_t padding : 1;               /*!< 始终为0b0。禁止使用其他值。*/
    uint8_t tai_delta_change[5];        /*!< TAI即将到来的TAI-UTC Delta变化的秒时间*/
} esp_ble_mesh_server_recv_tai_utc_delta_set_t;

/**接收到的时间角色集消息的上下文*/
typedef struct {
    uint8_t time_role;      /*!< 元素的时间角色*/
} esp_ble_mesh_server_recv_time_role_set_t;

/**接收的场景存储消息的上下文*/
typedef struct {
    uint16_t scene_number;  /*!< 要存储的场景数*/
} esp_ble_mesh_server_recv_scene_store_t;

/**接收到的场景调用消息的上下文*/
typedef struct {
    bool     op_en;         /*!< 指示是否包含可选参数*/
    uint16_t scene_number;  /*!< 要召回的场景数*/
    uint8_t  tid;           /*!< 事务ID*/
    uint8_t  trans_time;    /*!< 完成状态转换的时间（可选）*/
    uint8_t  delay;         /*!< 指示消息执行延迟（C.1）*/
} esp_ble_mesh_server_recv_scene_recall_t;

/**收到的场景删除消息的上下文*/
typedef struct {
    uint16_t scene_number;  /*!< 要删除的场景数*/
} esp_ble_mesh_server_recv_scene_delete_t;

/**收到的调度程序操作集消息的上下文*/
typedef struct {
    uint64_t index : 4;         /*!< 要设置的计划寄存器项的索引*/
    uint64_t year : 7;          /*!< 行动计划年度*/
    uint64_t month : 12;        /*!< 行动计划月份*/
    uint64_t day : 5;           /*!< 操作的计划日期*/
    uint64_t hour : 5;          /*!< 行动计划时间*/
    uint64_t minute : 6;        /*!< 计划的操作分钟数*/
    uint64_t second : 6;        /*!< 计划的第二个动作*/
    uint64_t day_of_week : 7;   /*!< 计划一周中的操作天数*/
    uint64_t action : 4;        /*!< 在计划时间执行的操作*/
    uint64_t trans_time : 8;    /*!< 此操作的过渡时间*/
    uint16_t scene_number;      /*!< 用于某些动作的场景编号*/
} esp_ble_mesh_server_recv_scheduler_act_set_t;

/**
 * @brief 时间场景服务器模型接收到集合消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_time_set_t          time;              /*!< 时间设置*/
    esp_ble_mesh_server_recv_time_zone_set_t     time_zone;         /*!< 时区设置*/
    esp_ble_mesh_server_recv_tai_utc_delta_set_t tai_utc_delta;     /*!< TAI-UTC增量集*/
    esp_ble_mesh_server_recv_time_role_set_t     time_role;         /*!< 时间角色集*/
    esp_ble_mesh_server_recv_scene_store_t       scene_store;       /*!< 场景存储/场景存储取消确认*/
    esp_ble_mesh_server_recv_scene_recall_t      scene_recall;      /*!< 场景调用/场景调用取消确认*/
    esp_ble_mesh_server_recv_scene_delete_t      scene_delete;      /*!< 场景删除/场景删除取消确认*/
    esp_ble_mesh_server_recv_scheduler_act_set_t scheduler_act;     /*!< 调度器操作集/调度器操作集取消确认*/
} esp_ble_mesh_time_scene_server_recv_set_msg_t;

/**接收到的时间状态消息的上下文*/
typedef struct {
    uint8_t  tai_seconds[5];        /*!< 当前TAI时间（秒）*/
    uint8_t  subsecond;             /*!< 以1/256秒为单位的亚秒时间*/
    uint8_t  uncertainty;           /*!< 10毫秒步长的估计不确定性*/
    uint16_t time_authority : 1;    /*!< 0=无时间权限，1=时间权限*/
    uint16_t tai_utc_delta : 15;    /*!< TAI和UTC之间的当前差值（秒）*/
    uint8_t  time_zone_offset;      /*!< 以15分钟为增量的本地时区偏移*/
} esp_ble_mesh_server_recv_time_status_t;

/**
 * @brief 时间场景服务器模型接收到状态消息联合
 */
typedef union {
    esp_ble_mesh_server_recv_time_status_t time_status;     /*!< 时间状态*/
} esp_ble_mesh_time_scene_server_recv_status_msg_t;

/**
 * @brief 时间场景服务器模型回调值联合
 */
typedef union {
    esp_ble_mesh_time_scene_server_state_change_t state_change; /*!< ESP_BLE_MESH_TIME_SCENE_SERVER_STATE_CHANGE_EVT */
    esp_ble_mesh_time_scene_server_recv_get_msg_t get;  /*!< ESP_BLE_MESH_TIME_SCENE_SERVER_RECV_GET_MSG_EVT */
    esp_ble_mesh_time_scene_server_recv_set_msg_t set;  /*!< ESP_BLE_MESH_TIME_SCENE_SERVER_RECV_SET_MSG_EVT */
    esp_ble_mesh_time_scene_server_recv_status_msg_t status;    /*!< ESP_BLE_MESH_TIME_SCENE_SERVER_RECV_STATUS_MSG_EVT */
} esp_ble_mesh_time_scene_server_cb_value_t;

/**时间场景服务器模型回调参数*/
typedef struct {
    esp_ble_mesh_model_t  *model;   /*!< 指向时间和场景服务器模型的指针*/
    esp_ble_mesh_msg_ctx_t ctx;     /*!< 收到消息的上下文*/
    esp_ble_mesh_time_scene_server_cb_value_t value;    /*!< 收到的时间和场景消息的值*/
} esp_ble_mesh_time_scene_server_cb_param_t;

/**此枚举值是时间场景服务器模型的事件*/
typedef enum {
    /**
     * 1.当get_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当接收到时间场景获取消息时，不会将任何事件回调到应用层。2.当set_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp时，当接收到时间场景设置/设置未确认消息时，此事件将回调到应用层。
     */
    ESP_BLE_MESH_TIME_SCENE_SERVER_STATE_CHANGE_EVT,
    /**
     * 当get_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到时间场景获取消息时，此事件将回调到应用程序层。
     */
    ESP_BLE_MESH_TIME_SCENE_SERVER_RECV_GET_MSG_EVT,
    /**
     * 当set_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当接收到时间场景设置/设置未确认消息时，此事件将回调到应用程序层。
     */
    ESP_BLE_MESH_TIME_SCENE_SERVER_RECV_SET_MSG_EVT,
    /**
     * 当status_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP时，当收到TIme status消息时，此事件将回调到应用程序层。
     */
    ESP_BLE_MESH_TIME_SCENE_SERVER_RECV_STATUS_MSG_EVT,
    ESP_BLE_MESH_TIME_SCENE_SERVER_EVT_MAX,
} esp_ble_mesh_time_scene_server_cb_event_t;

/**
 *  @brief 蓝牙网格时间和场景服务器模型功能。
 */

/**
 * @brief   时间场景服务器模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_time_scene_server_cb_t)(esp_ble_mesh_time_scene_server_cb_event_t event,
                                                     esp_ble_mesh_time_scene_server_cb_param_t *param);

/**
 * @brief       注册BLE网格时间和场景服务器模型回调。
 *
 * @param[in]   callback: 指向回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_time_scene_server_callback(esp_ble_mesh_time_scene_server_cb_t callback);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_TIME_SCENE_MODEL_API_H_ */

