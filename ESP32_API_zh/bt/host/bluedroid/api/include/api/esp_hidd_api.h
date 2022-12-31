// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
// 版权所有2019 Blake Felt
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_HIDD_API_H__
#define __ESP_HIDD_API_H__

#include "esp_bt_defs.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* hid设备的子类*/
#define ESP_HID_CLASS_UNKNOWN      (0x00<<2)
#define ESP_HID_CLASS_JOS          (0x01<<2)           /* 操纵杆*/
#define ESP_HID_CLASS_GPD          (0x02<<2)           /* 游戏板*/
#define ESP_HID_CLASS_RMC          (0x03<<2)           /* 遥控器*/
#define ESP_HID_CLASS_SED          (0x04<<2)           /* 传感装置*/
#define ESP_HID_CLASS_DGT          (0x05<<2)           /* 数字化仪平板电脑*/
#define ESP_HID_CLASS_CDR          (0x06<<2)           /* 读卡器*/
#define ESP_HID_CLASS_KBD          (0x10<<2)           /* 键盘*/
#define ESP_HID_CLASS_MIC          (0x20<<2)           /* 指向装置*/
#define ESP_HID_CLASS_COM          (0x30<<2)           /* 组合键盘/定点*/

/**
 * @brief HIDD握手错误
 */
typedef enum {
    ESP_HID_PAR_HANDSHAKE_RSP_SUCCESS = 0,
    ESP_HID_PAR_HANDSHAKE_RSP_NOT_READY = 1,
    ESP_HID_PAR_HANDSHAKE_RSP_ERR_INVALID_REP_ID = 2,
    ESP_HID_PAR_HANDSHAKE_RSP_ERR_UNSUPPORTED_REQ = 3,
    ESP_HID_PAR_HANDSHAKE_RSP_ERR_INVALID_PARAM = 4,
    ESP_HID_PAR_HANDSHAKE_RSP_ERR_UNKNOWN = 14,
    ESP_HID_PAR_HANDSHAKE_RSP_ERR_FATAL = 15
} esp_hidd_handshake_error_t;

/**
 * @brief HIDD报告类型
 */
typedef enum {
    ESP_HIDD_REPORT_TYPE_OTHER = 0,
    ESP_HIDD_REPORT_TYPE_INPUT,
    ESP_HIDD_REPORT_TYPE_OUTPUT,
    ESP_HIDD_REPORT_TYPE_FEATURE,
    // 要在INTR上发送的报告的特殊值（假定为INPUT）
    ESP_HIDD_REPORT_TYPE_INTRDATA
} esp_hidd_report_type_t;

/**
 * @brief HIDD连接状态
 */
typedef enum {
    ESP_HIDD_CONN_STATE_CONNECTED,
    ESP_HIDD_CONN_STATE_CONNECTING,
    ESP_HIDD_CONN_STATE_DISCONNECTED,
    ESP_HIDD_CONN_STATE_DISCONNECTING,
    ESP_HIDD_CONN_STATE_UNKNOWN
} esp_hidd_connection_state_t;

/**
 * @brief HID设备协议模式
 */
typedef enum {
    ESP_HIDD_REPORT_MODE = 0x00,
    ESP_HIDD_BOOT_MODE = 0x01,
    ESP_HIDD_UNSUPPORTED_MODE = 0xff
} esp_hidd_protocol_mode_t;


/**
 * @brief SDP报告的HIDD特征
 */
typedef struct {
    const char *name;
    const char *description;
    const char *provider;
    uint8_t subclass;
    uint8_t *desc_list;
    int desc_list_len;
} esp_hidd_app_param_t;

/**
 * @brief HIDD服务质量参数
 */
typedef struct {
    uint8_t service_type;
    uint32_t token_rate;
    uint32_t token_bucket_size;
    uint32_t peak_bandwidth;
    uint32_t access_latency;
    uint32_t delay_variation;
} esp_hidd_qos_param_t;

/**
 * @brief HID设备回调函数事件
 */
typedef enum {
    ESP_HIDD_INIT_EVT = 0,       /*!< 当HID设备初始化时，事件发生*/
    ESP_HIDD_DEINIT_EVT,         /*!< 当HID设备卸载时，事件发生*/
    ESP_HIDD_REGISTER_APP_EVT,   /*!< 当HID设备应用程序注册时，事件发生*/
    ESP_HIDD_UNREGISTER_APP_EVT, /*!< 当HID设备应用程序未注册时，事件发生*/
    ESP_HIDD_OPEN_EVT,           /*!< 当HID设备与主机的连接打开时，事件发生*/
    ESP_HIDD_CLOSE_EVT,          /*!< 当HID设备与主机的连接关闭时，事件发生*/
    ESP_HIDD_SEND_REPORT_EVT,    /*!< 当HID设备向较低层发送报告时，事件发生*/
    ESP_HIDD_REPORT_ERR_EVT,     /*!< 当HID设备向下层报告握手错误时，事件发生*/
    ESP_HIDD_GET_REPORT_EVT,     /*!< 当HID设备从主机接收到GET_REPORT请求时，事件发生*/
    ESP_HIDD_SET_REPORT_EVT,     /*!< 当HID设备从主机接收SET_REPORT请求时，事件发生*/
    ESP_HIDD_SET_PROTOCOL_EVT,   /*!< 当HID设备从主机接收SET_PROTOCOL请求时，事件发生*/
    ESP_HIDD_INTR_DATA_EVT,      /*!< 当HID设备在intr上从主机接收DATA时，事件发生*/
    ESP_HIDD_VC_UNPLUG_EVT,      /*!< 当HID设备启动虚拟电缆拔出时，事件发生*/
    ESP_HIDD_API_ERR_EVT         /*!< 当HID设备出现API错误时，事件发生*/
} esp_hidd_cb_event_t;

typedef enum {
    ESP_HIDD_SUCCESS,
    ESP_HIDD_ERROR,         /*!< 一般ESP HD错误*/
    ESP_HIDD_NO_RES,        /*!< 系统外资源*/
    ESP_HIDD_BUSY,          /*!< 暂时无法处理此请求。*/
    ESP_HIDD_NO_DATA,       /*!< 无数据。*/
    ESP_HIDD_NEED_INIT,     /*!< HIDD模块应首先初始化*/
    ESP_HIDD_NEED_DEINIT,   /*!< HIDD模块应首先卸载*/
    ESP_HIDD_NEED_REG,      /*!< HIDD模块应首先注册*/
    ESP_HIDD_NEED_DEREG,    /*!< HIDD模块应首先注销注册*/
    ESP_HIDD_NO_CONNECTION, /*!< 连接可能已关闭*/
} esp_hidd_status_t;

/**
 * @brief HID设备回调参数联合
 */
typedef union {
    /**
     * @brief ESP_HIDD_INIT_EVT
     */
    struct hidd_init_evt_param {
        esp_hidd_status_t status; /*!< 运行状态*/
    } init;                       /*!< ESP_HIDD_INIT_VT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_DEINIT_EVT
     */
    struct hidd_deinit_evt_param {
        esp_hidd_status_t status; /*!< 运行状态*/
    } deinit;                     /*!< ESP_HIDD_INIT_VT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_REGISTER_APP_EVT
     */
    struct hidd_register_app_evt_param {
        esp_hidd_status_t status; /*!< 运行状态*/
        bool in_use;              /*!< 指示是否使用虚拟电缆插头主机地址*/
        esp_bd_addr_t bd_addr;    /*!< 主机地址*/
    } register_app;               /*!< ESP_HIDD_REGISTER_APP_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_UNREGISTER_APP_EVT
     */
    struct hidd_unregister_app_evt_param {
        esp_hidd_status_t status; /*!< 运行状态*/
    } unregister_app;             /*!< ESP_HIDD_UNREGISTER_APP_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_OPEN_EVT
     */
    struct hidd_open_evt_param {
        esp_hidd_status_t status;                /*!< 运行状态*/
        esp_hidd_connection_state_t conn_status; /*!< 连接状态*/
        esp_bd_addr_t bd_addr;                   /*!< 主机地址*/
    } open;                                      /*!< ESP_HIDD_OPEN_VT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_CLOSE_EVT
     */
    struct hidd_close_evt_param {
        esp_hidd_status_t status;                /*!< 运行状态*/
        esp_hidd_connection_state_t conn_status; /*!< 连接状态*/
    } close;                                     /*!< ESP_HIDD_CLOSE_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_SEND_REPORT_EVT
     */
    struct hidd_send_report_evt_param {
        esp_hidd_status_t status;           /*!< 运行状态*/
        uint8_t reason;                     /*!< 下层失败原因（ref hiddefs.h）*/
        esp_hidd_report_type_t report_type; /*!< 报告类型*/
        uint8_t report_id;                  /*!< 报告id*/
    } send_report;                          /*!< ESP_HIDD_SEND_REPORT_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_REPORT_ERR_EVT
     */
    struct hidd_report_err_evt_param {
        esp_hidd_status_t status; /*!< 运行状态*/
        uint8_t reason;           /*!< 下层失败原因（ref hiddefs.h）*/
    } report_err;                 /*!< ESP_HIDD_REPORT_ERR_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_GET_REPORT_EVT
     */
    struct hidd_get_report_evt_param {
        esp_hidd_report_type_t report_type; /*!< 报告类型*/
        uint8_t report_id;                  /*!< 报告id*/
        uint16_t buffer_size;               /*!< 缓冲区大小*/
    } get_report;                           /*!< ESP_HIDD_GET_REPORT_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_SET_REPORT_EVT
     */
    struct hidd_set_report_evt_param {
        esp_hidd_report_type_t report_type; /*!< 报告类型*/
        uint8_t report_id;                  /*!< 报告id*/
        uint16_t len;                       /*!< set_report数据长度*/
        uint8_t *data;                      /*!< set_report数据指针*/
    } set_report;                           /*!< ESP_HIDD_SET_REREPORT_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_SET_PROTOCOL_EVT
     */
    struct hidd_set_protocol_evt_param {
        esp_hidd_protocol_mode_t protocol_mode; /*!< 协议模式*/
    } set_protocol;                             /*!< ESP_HIDD_SET_PROTOCOL_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_INTR_DATA_EVT
     */
    struct hidd_intr_data_evt_param {
        uint8_t report_id; /*!< 中断通道报告id*/
        uint16_t len;      /*!< 中断通道报告数据长度*/
        uint8_t *data;     /*!< 中断通道报告数据指针*/
    } intr_data;           /*!< ESP_HIDD_INTR_DATA_EVT的HIDD回调参数*/

    /**
     * @brief ESP_HIDD_VC_UNPLUG_EVT
     */
    struct hidd_vc_unplug_param {
        esp_hidd_status_t status;                /*!< 运行状态*/
        esp_hidd_connection_state_t conn_status; /*!< 连接状态*/
    } vc_unplug;                                 /*!< ESP_HIDD_VC_UNLUG_EVT的HIDD回调参数*/
} esp_hidd_cb_param_t;

/**
 * @brief       HID设备回调函数类型。
 * @param       event:      事件类型
 * @param       param:      指向回调参数，当前为联合类型
 */
typedef void (esp_hd_cb_t)(esp_hidd_cb_event_t event, esp_hidd_cb_param_t *param);

/**
 * @brief       调用此函数以初始化HID设备模块的回调。
 *
 * @param[in]   callback:   指向init回调函数的指针。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_device_register_callback(esp_hd_cb_t callback);

/**
 * @brief       此函数初始化HIDD。该函数应在esp_bluedroid_enable和esp_blueroid_init成功后调用，并且应在esp_bt_hid_device_register_callback后调用。操作完成后，将使用ESP_HIDD_INIT_VT调用回调函数。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_device_init(void);

/**
 * @brief       此函数用于取消初始化HIDD接口。该函数应在esp_bluedroid_enable（）和esp_blueroid_init（）成功后调用，并且应在esp_bt_hid_device_init（）后调用。操作完成后，将使用ESP_HIDD_INIT_VT调用回调函数。
 *
 * @return    -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_deinit(void);

/**
 * @brief     向SDP注册HIDD参数并设置l2cap服务质量。该函数应在esp_bluedroid_enable和esp_blueroid_init成功后调用，并且必须在esp_bt_hid_device_init之后执行。操作完成后，将使用ESP_HIDD_REGISTER_APP_EVT调用回调函数。
 *
 * @param[in] app_param:  HIDD参数
 * @param[in] in_qos:     传入QoS参数
 * @param[in] out_qos:    传出QoS参数
 *
 * @return    -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_register_app(esp_hidd_app_param_t *app_param, esp_hidd_qos_param_t *in_qos,
                                         esp_hidd_qos_param_t *out_qos);

/**
 * @brief   从SDP中删除HIDD参数并重置l2cap服务质量。该函数应在esp_bluedroid_enable和esp_blueroid_init成功后调用，并且应在esp_bt_hid_device_init之后调用。操作完成后，将使用ESP_HIDD_UNREGISTER_APP_EVT调用回调函数。
 *
 * @return  -ESP_OK：成功
 *          -其他：失败
 */
esp_err_t esp_bt_hid_device_unregister_app(void);

/**
 * @brief     此功能将HIDD接口连接到已连接的蓝牙设备（如果尚未完成）。操作完成后，将使用ESP_HIDD_OPEN_VT调用回调函数。
 *
 * @param[in] bd_addr:      远程主机蓝牙设备地址。
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_connect(esp_bd_addr_t bd_addr);

/**
 * @brief     此函数用于断开HIDD接口。操作完成后，将使用ESP_HIDD_CLOSE_EVT调用回调函数。
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_disconnect(void);

/**
 * @brief     发送HIDD报告。操作完成后，将使用ESP_HIDD_SEND_REPORT_EVT调用回调函数。
 *
 * @param[in] type:   报告类型
 * @param[in] id:     描述符定义的报告id
 * @param[in] len:    报告长度
 * @param[in] data:   报告数据
 *
 * @return
 *            -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_send_report(esp_hidd_report_type_t type, uint8_t id, uint16_t len, uint8_t *data);

/**
 * @brief     发送带有无效set_report错误信息的HIDD握手。操作完成后，将使用ESP_HIDD_REPORT_ERR_EVT调用回调函数。
 *
 * @param[in] error: 错误类型
 *
 * @return    -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_report_error(esp_hidd_handshake_error_t error);

/**
 * @brief     拔下HIDD的虚拟电缆。操作完成后，将使用ESP_HIDD_VC_UNLUG_EVT调用回调函数。
 *
 * @return    -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_device_virtual_cable_unplug(void);

#ifdef __cplusplus
}
#endif

#endif

