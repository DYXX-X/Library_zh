/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_HEALTH_MODEL_API_H_
#define _ESP_BLE_MESH_HEALTH_MODEL_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def    ESP_BLE_MESH_MODEL_HEALTH_SRV
 *
 *  @brief  定义新的Health Server模型。
 *
 *  @note   Health Server模型只能由主元素包含。
 *
 *  @param  srv 指向唯一结构esp_ble_mesh_health_srv_t的指针。
 *  @param  pub 指向唯一结构esp_ble_mesh_model_pub_t的指针。
 *
 *  @return 新建Health Server模型实例。
 */
#define ESP_BLE_MESH_MODEL_HEALTH_SRV(srv, pub)                           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_HEALTH_SRV,          \
                           NULL, pub, srv)

/** @def    ESP_BLE_MESH_MODEL_HEALTH_CLI
 *
 *  @brief  定义新的Health Client模型。
 *
 *  @note   需要为应用程序需要具有健康客户端模型的每个元素调用此API。
 *
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建健康客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_HEALTH_CLI(cli_data)                           \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_HEALTH_CLI,          \
                           NULL, NULL, cli_data)

/** @def ESP_BLE_MESH_HEALTH_PUB_DEFINE
 *
 *  用于定义健康发布上下文的帮助程序
 *
 *  @param _name 给发布上下文变量的名称。
 *  @param _max  元素可能具有的最大故障数。
 *  @param _role 包含模型的设备的角色。
 */
#define ESP_BLE_MESH_HEALTH_PUB_DEFINE(_name, _max, _role) \
        ESP_BLE_MESH_MODEL_PUB_DEFINE(_name, (1 + 3 + (_max)), _role)

/**
 * 健康故障测试的SIG标识符。0x01~0xFF：供应商特定测试。
 */
#define ESP_BLE_MESH_HEALTH_STANDARD_TEST               0x00

/**
 * 健康故障测试的故障值。0x33~0x7F：保留供将来使用。0x80~0xFF：供应商特定警告/错误。
 */
#define ESP_BLE_MESH_NO_FAULT                           0x00
#define ESP_BLE_MESH_BATTERY_LOW_WARNING                0x01
#define ESP_BLE_MESH_BATTERY_LOW_ERROR                  0x02
#define ESP_BLE_MESH_SUPPLY_VOLTAGE_TOO_LOW_WARNING     0x03
#define ESP_BLE_MESH_SUPPLY_VOLTAGE_TOO_LOW_ERROR       0x04
#define ESP_BLE_MESH_SUPPLY_VOLTAGE_TOO_HIGH_WARNING    0x05
#define ESP_BLE_MESH_SUPPLY_VOLTAGE_TOO_HIGH_ERROR      0x06
#define ESP_BLE_MESH_POWER_SUPPLY_INTERRUPTED_WARNING   0x07
#define ESP_BLE_MESH_POWER_SUPPLY_INTERRUPTED_ERROR     0x08
#define ESP_BLE_MESH_NO_LOAD_WARNING                    0x09
#define ESP_BLE_MESH_NO_LOAD_ERROR                      0x0A
#define ESP_BLE_MESH_OVERLOAD_WARNING                   0x0B
#define ESP_BLE_MESH_OVERLOAD_ERROR                     0x0C
#define ESP_BLE_MESH_OVERHEAT_WARNING                   0x0D
#define ESP_BLE_MESH_OVERHEAT_ERROR                     0x0E
#define ESP_BLE_MESH_CONDENSATION_WARNING               0x0F
#define ESP_BLE_MESH_CONDENSATION_ERROR                 0x10
#define ESP_BLE_MESH_VIBRATION_WARNING                  0x11
#define ESP_BLE_MESH_VIBRATION_ERROR                    0x12
#define ESP_BLE_MESH_CONFIGURATION_WARNING              0x13
#define ESP_BLE_MESH_CONFIGURATION_ERROR                0x14
#define ESP_BLE_MESH_ELEMENT_NOT_CALIBRATED_WARNING     0x15
#define ESP_BLE_MESH_ELEMENT_NOT_CALIBRATED_ERROR       0x16
#define ESP_BLE_MESH_MEMORY_WARNING                     0x17
#define ESP_BLE_MESH_MEMORY_ERROR                       0x18
#define ESP_BLE_MESH_SELF_TEST_WARNING                  0x19
#define ESP_BLE_MESH_SELF_TEST_ERROR                    0x1A
#define ESP_BLE_MESH_INPUT_TOO_LOW_WARNING              0x1B
#define ESP_BLE_MESH_INPUT_TOO_LOW_ERROR                0x1C
#define ESP_BLE_MESH_INPUT_TOO_HIGH_WARNING             0x1D
#define ESP_BLE_MESH_INPUT_TOO_HIGH_ERROR               0x1E
#define ESP_BLE_MESH_INPUT_NO_CHANGE_WARNING            0x1F
#define ESP_BLE_MESH_INPUT_NO_CHANGE_ERROR              0x20
#define ESP_BLE_MESH_ACTUATOR_BLOCKED_WARNING           0x21
#define ESP_BLE_MESH_ACTUATOR_BLOCKED_ERROR             0x22
#define ESP_BLE_MESH_HOUSING_OPENED_WARNING             0x23
#define ESP_BLE_MESH_HOUSING_OPENED_ERROR               0x24
#define ESP_BLE_MESH_TAMPER_WARNING                     0x25
#define ESP_BLE_MESH_TAMPER_ERROR                       0x26
#define ESP_BLE_MESH_DEVICE_MOVED_WARNING               0x27
#define ESP_BLE_MESH_DEVICE_MOVED_ERROR                 0x28
#define ESP_BLE_MESH_DEVICE_DROPPED_WARNING             0x29
#define ESP_BLE_MESH_DEVICE_DROPPED_ERROR               0x2A
#define ESP_BLE_MESH_OVERFLOW_WARNING                   0x2B
#define ESP_BLE_MESH_OVERFLOW_ERROR                     0x2C
#define ESP_BLE_MESH_EMPTY_WARNING                      0x2D
#define ESP_BLE_MESH_EMPTY_ERROR                        0x2E
#define ESP_BLE_MESH_INTERNAL_BUS_WARNING               0x2F
#define ESP_BLE_MESH_INTERNAL_BUS_ERROR                 0x30
#define ESP_BLE_MESH_MECHANISM_JAMMED_WARNING           0x31
#define ESP_BLE_MESH_MECHANISM_JAMMED_ERROR             0x32

/**ESP BLE Mesh Health Server回调*/
typedef struct {
    /**清除运行状况记录的故障。已由堆栈初始化。*/
    esp_ble_mesh_cb_t fault_clear;

    /**运行特定的健康测试。已由堆栈初始化。*/
    esp_ble_mesh_cb_t fault_test;

    /**回调时的健康注意事项。已由堆栈初始化。*/
    esp_ble_mesh_cb_t attention_on;

    /**健康注意关闭回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t attention_off;
} esp_ble_mesh_health_srv_cb_t;

#define ESP_BLE_MESH_HEALTH_FAULT_ARRAY_SIZE    32

/**ESP BLE Mesh Health Server测试上下文*/
typedef struct {
    uint8_t  id_count;          /*!< 健康自检ID的数量*/
    const uint8_t *test_ids;    /*!< 运行状况自检ID阵列*/
    uint16_t company_id;        /*!< 用于识别健康故障状态的公司ID*/
    uint8_t  prev_test_id;      /*!< 健康故障测试的当前测试ID*/
    uint8_t  current_faults[ESP_BLE_MESH_HEALTH_FAULT_ARRAY_SIZE];      /*!< 电流故障阵列*/
    uint8_t  registered_faults[ESP_BLE_MESH_HEALTH_FAULT_ARRAY_SIZE];   /*!< 记录的故障阵列*/
} __attribute__((packed)) esp_ble_mesh_health_test_t;

/**ESP BLE Mesh Health Server模型上下文*/
typedef struct {
    /**指向运行状况服务器模型的指针*/
    esp_ble_mesh_model_t *model;

    /**运行状况回调结构*/
    esp_ble_mesh_health_srv_cb_t health_cb;

    /**注意计时器状态*/
    struct k_delayed_work attention_timer;

    /**注意计时器启动标志*/
    bool attention_timer_start;

    /**运行状况服务器故障测试*/
    esp_ble_mesh_health_test_t health_test;
} esp_ble_mesh_health_srv_t;

/**健康故障获取参数*/
typedef struct {
    uint16_t company_id;    /*!< 蓝牙分配的16位公司ID*/
} esp_ble_mesh_health_fault_get_t;

/**健康注意集参数*/
typedef struct {
    uint8_t attention;      /*!< 注意计时器状态的值*/
} esp_ble_mesh_health_attention_set_t;

/**健康期设置参数*/
typedef struct {
    uint8_t fast_period_divisor;    /*!< 发布期间的分隔符*/
} esp_ble_mesh_health_period_set_t;

/**健康故障测试参数*/
typedef struct {
    uint16_t company_id;    /*!< 蓝牙分配的16位公司ID*/
    uint8_t  test_id;       /*!< 要执行的特定测试的ID*/
} esp_ble_mesh_health_fault_test_t;

/**健康故障清除参数*/
typedef struct {
    uint16_t company_id;    /*!< 蓝牙分配的16位公司ID*/
} esp_ble_mesh_health_fault_clear_t;

/**
 * @brief 对于ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_GET ESP_BLE_MESH_MODAL_OP_ATTENTION_GET ESP-BLE_MES_MODEL_OP_HEALTH_PERIOD_GET，ESP_BLE_MESH_HEALTH_client_GET_state函数中的GET_state参数不应设置为NULL。
 */
typedef union {
    esp_ble_mesh_health_fault_get_t fault_get;          /*!< 对于ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_GET。*/
} esp_ble_mesh_health_client_get_state_t;

/**
 * @brief 对于ESP_BLE_MESH_MODE_OP_HEALTH_FAULT_CLEAR ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_CLEAR_UNACK ESP_BLE-MESH_MODEL OP_HEALT FAULT_CLEAR_UNACK ESP_BLE/MESH_MODELL_OP_HEALT FAULT_TEST ESP_BLE.MESH_MODEME_OP_HHEALTH_PERIOD_SET这是一个很好的例子esp_ble_mesh_health_client_set_state函数不应设置为NULL。
 */
typedef union {
    esp_ble_mesh_health_attention_set_t attention_set;    /*!< 对于ESP_BLE_MESH_MODEL_OP_ATTENTION_SET或ESP_BLE_MESH_MODE_OP_ATTEENTION_SET_UNACK。*/
    esp_ble_mesh_health_period_set_t    period_set;       /*!< 对于ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_SET或ESP_BLE_MESH_MODEL _OP_HEALT _PERIOD_SET_UNACK。*/
    esp_ble_mesh_health_fault_test_t    fault_test;       /*!< 对于ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_TEST或ESP_BLE_MESH_MODE_OP_HEALTH_FAUT_TEST_UNACK。*/
    esp_ble_mesh_health_fault_clear_t   fault_clear;      /*!< 对于ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_CLEAR或ESP_BLE_MESH_MODE_OP_HEALTH_FAULT_CLEAR。*/
} esp_ble_mesh_health_client_set_state_t;

/**健康现状参数*/
typedef struct {
    uint8_t  test_id;                       /*!< 最近执行的测试的ID*/
    uint16_t company_id;                    /*!< 蓝牙分配的16位公司ID*/
    struct net_buf_simple *fault_array;     /*!< FaultArray（故障阵列）字段包含1个八位字节的故障值序列*/
} esp_ble_mesh_health_current_status_cb_t;

/**健康故障状态参数*/
typedef struct {
    uint8_t  test_id;                       /*!< 最近执行的测试的ID*/
    uint16_t company_id;                    /*!< 蓝牙分配的16位公司ID*/
    struct net_buf_simple *fault_array;     /*!< FaultArray（故障阵列）字段包含1个八位字节的故障值序列*/
} esp_ble_mesh_health_fault_status_cb_t;

/**健康期状态参数*/
typedef struct {
    uint8_t fast_period_divisor;            /*!< 发布期间的分隔符*/
} esp_ble_mesh_health_period_status_cb_t;

/**健康注意状态参数*/
typedef struct {
    uint8_t attention;                      /*!< 注意计时器状态的值*/
} esp_ble_mesh_health_attention_status_cb_t;

/**
 * @brief 运行状况客户端模型接收到消息联合
 */
typedef union {
    esp_ble_mesh_health_current_status_cb_t   current_status;       /*!< 运行状况当前状态值*/
    esp_ble_mesh_health_fault_status_cb_t     fault_status;         /*!< 健康故障状态值*/
    esp_ble_mesh_health_period_status_cb_t    period_status;        /*!< 健康期状态值*/
    esp_ble_mesh_health_attention_status_cb_t attention_status;     /*!< 健康关注状态值*/
} esp_ble_mesh_health_client_common_cb_param_t;

/**运行状况客户端模型回调参数*/
typedef struct {
    int error_code;                                         /*!< 适当的错误代码*/
    esp_ble_mesh_client_common_param_t          *params;    /*!< 客户端公用参数。*/
    esp_ble_mesh_health_client_common_cb_param_t status_cb; /*!< 运行状况消息状态回调值*/
} esp_ble_mesh_health_client_cb_param_t;

/**此枚举值是Health Client Model的事件*/
typedef enum {
    ESP_BLE_MESH_HEALTH_CLIENT_GET_STATE_EVT,
    ESP_BLE_MESH_HEALTH_CLIENT_SET_STATE_EVT,
    ESP_BLE_MESH_HEALTH_CLIENT_PUBLISH_EVT,
    ESP_BLE_MESH_HEALTH_CLIENT_TIMEOUT_EVT,
    ESP_BLE_MESH_HEALTH_CLIENT_EVT_MAX,
} esp_ble_mesh_health_client_cb_event_t;

/**发布运行状况当前状态完成事件的参数*/
typedef struct {
    int error_code;                 /*!< 发布Health Current Status的结果*/
    esp_ble_mesh_elem_t *element;   /*!< 指向包含Health Server模型的元素的指针*/
} esp_ble_mesh_health_fault_update_comp_cb_t;

/**运行状况故障清除事件的参数*/
typedef struct {
    esp_ble_mesh_model_t *model;    /*!< 指向运行状况服务器模型的指针*/
    uint16_t company_id;            /*!< 蓝牙分配的16位公司ID*/
} esp_ble_mesh_health_fault_clear_cb_t;

/**健康故障测试事件的参数*/
typedef struct {
    esp_ble_mesh_model_t *model;    /*!< 指向运行状况服务器模型的指针*/
    uint8_t  test_id;               /*!< 要执行的特定测试的ID*/
    uint16_t company_id;            /*!< 蓝牙分配的16位公司ID*/
} esp_ble_mesh_health_fault_test_cb_t;

/**健康注意事件参数*/
typedef struct {
    esp_ble_mesh_model_t *model;    /*!< 指向运行状况服务器模型的指针*/
    uint8_t time;                   /*!< 注意计时器打开的持续时间（秒）*/
} esp_ble_mesh_health_attention_on_cb_t;

/**健康注意关闭事件的参数*/
typedef struct {
    esp_ble_mesh_model_t *model;    /*!< 指向运行状况服务器模型的指针*/
} esp_ble_mesh_health_attention_off_cb_t;

/**
 * @brief Health Server模型回调参数联合
 */
typedef union {
    esp_ble_mesh_health_fault_update_comp_cb_t  fault_update_comp;  /*!< ESP_BLE_MESH_HEALTH_SERVER_FAULT_UPDATE_COMP_EVT */
    esp_ble_mesh_health_fault_clear_cb_t        fault_clear;        /*!< ESP_BLE_MESH_HEALTH_SERVER_FAULT_CLEAR_EVT */
    esp_ble_mesh_health_fault_test_cb_t         fault_test;         /*!< ESP_BLE_MESH_HEALTH_SERVER_FAULT_TEST_EVT */
    esp_ble_mesh_health_attention_on_cb_t       attention_on;       /*!< ESP_BLE_MESH_HEALTH_SERVER_ATTENTION_ON_EVT */
    esp_ble_mesh_health_attention_off_cb_t      attention_off;      /*!< ESP_BLE_MESH_HEALTH_SERVER_ATTENTION_OFF_EVT */
} esp_ble_mesh_health_server_cb_param_t;

/**此枚举值是Health Server模型的事件*/
typedef enum {
    ESP_BLE_MESH_HEALTH_SERVER_FAULT_UPDATE_COMP_EVT,
    ESP_BLE_MESH_HEALTH_SERVER_FAULT_CLEAR_EVT,
    ESP_BLE_MESH_HEALTH_SERVER_FAULT_TEST_EVT,
    ESP_BLE_MESH_HEALTH_SERVER_ATTENTION_ON_EVT,
    ESP_BLE_MESH_HEALTH_SERVER_ATTENTION_OFF_EVT,
    ESP_BLE_MESH_HEALTH_SERVER_EVT_MAX,
} esp_ble_mesh_health_server_cb_event_t;

/**
 *  @brief 蓝牙网格健康客户端和服务器模型功能。
 */

/**
 * @brief   健康客户端模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_health_client_cb_t)(esp_ble_mesh_health_client_cb_event_t event,
                                                 esp_ble_mesh_health_client_cb_param_t *param);

/**
 * @brief   运行状况服务器模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_health_server_cb_t)(esp_ble_mesh_health_server_cb_event_t event,
                                                 esp_ble_mesh_health_server_cb_param_t *param);

/**
 * @brief         注册BLE Mesh Health Model回调，回调将报告Health Client&Server Model事件。
 *
 * @param[in]     callback: 指向回调函数的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_health_client_callback(esp_ble_mesh_health_client_cb_t callback);

/**
 * @brief         注册BLE Mesh Health Server模型回调。
 *
 * @param[in]     callback: 指向回调函数的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_health_server_callback(esp_ble_mesh_health_server_cb_t callback);

/**
 * @brief         调用此函数以使用Health Client Model get消息获取Health Server状态。
 *
 * @note          如果要查找此API接受的操作码和相应含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_opcode_health_client_get_t
 *
 * @param[in]     params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]     get_state: 指向并集的指针，每种操作码对应于内部的一个结构。不应设置为NULL。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_health_client_get_state(esp_ble_mesh_client_common_param_t *params,
                                               esp_ble_mesh_health_client_get_state_t *get_state);

/**
 * @brief         调用此函数以使用Health Client Model集合消息设置Health Server状态。
 *
 * @note          如果要查找此API接受的操作码和相应含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_opcode_health_client_set_t
 *
 * @param[in]     params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]     set_state: 指向并集的指针，每种操作码对应于内部的一个结构。不应设置为NULL。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_health_client_set_state(esp_ble_mesh_client_common_param_t *params,
                                               esp_ble_mesh_health_client_set_state_t *set_state);

/**
 * @brief         Health Server模型调用此函数以更新其Health Current状态的上下文。
 *
 * @param[in]     element: Health Server模型所属的元素。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_health_server_fault_update(esp_ble_mesh_elem_t *element);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_HEALTH_MODEL_API_H_ */

