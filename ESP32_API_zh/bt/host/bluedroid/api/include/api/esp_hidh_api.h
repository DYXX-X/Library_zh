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

#ifndef __ESP_HIDH_API_H__
#define __ESP_HIDH_API_H__

#include "esp_bt_defs.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BTHH_MAX_DSC_LEN 884

/**
 * @brief HID主机连接状态
 */
typedef enum {
    ESP_HIDH_CONN_STATE_CONNECTED = 0,           /*!< 连接状态*/
    ESP_HIDH_CONN_STATE_CONNECTING,              /*!< 连接状态*/
    ESP_HIDH_CONN_STATE_DISCONNECTED,            /*!< 断开连接状态*/
    ESP_HIDH_CONN_STATE_DISCONNECTING,           /*!< 断开连接状态*/
    ESP_HIDH_CONN_STATE_UNKNOWN                  /*!< 未知状态（初始状态）*/
} esp_hidh_connection_state_t;

typedef enum {
    ESP_HIDH_OK,
    ESP_HIDH_HS_HID_NOT_READY,  /*!< 握手错误：设备未就绪*/
    ESP_HIDH_HS_INVALID_RPT_ID, /*!< 握手错误：报告ID无效*/
    ESP_HIDH_HS_TRANS_NOT_SPT,  /*!< 握手错误：事务不是spt*/
    ESP_HIDH_HS_INVALID_PARAM,  /*!< 握手错误：参数无效*/
    ESP_HIDH_HS_ERROR,          /*!< 握手错误：未指定的HS错误*/
    ESP_HIDH_ERR,               /*!< 一般ESP HH错误*/
    ESP_HIDH_ERR_SDP,           /*!< SDP错误*/
    ESP_HIDH_ERR_PROTO,         /*!< SET_Protocol错误，仅用于ESP_HIDH_OPEN_EVT回调*/

    ESP_HIDH_ERR_DB_FULL,       /*!< 设备数据库完全错误，用于ESP_HIDH_OPEN_EVT/ESP_HIDH_2ADD_DEV_EVT*/
    ESP_HIDH_ERR_TOD_UNSPT,     /*!< 不支持的设备类型*/
    ESP_HIDH_ERR_NO_RES,        /*!< 系统外资源*/
    ESP_HIDH_ERR_AUTH_FAILED,   /*!< 身份验证失败*/
    ESP_HIDH_ERR_HDL,           /*!< 连接句柄错误*/
    ESP_HIDH_ERR_SEC,           /*!< 加密错误*/
    // 自我定义的
    ESP_HIDH_BUSY,              /*!< 暂时无法处理此请求。*/
    ESP_HIDH_NO_DATA,           /*!< 无数据。*/
    ESP_HIDH_NEED_INIT,         /*!< HIDH模块应首先初始化*/
    ESP_HIDH_NEED_DEINIT,       /*!< HIDH模块应首先卸载*/
    ESP_HIDH_NO_CONNECTION,     /*!< 连接可能已关闭*/
} esp_hidh_status_t;

/**
 * @brief HID主机协议模式
 */
typedef enum {
    ESP_HIDH_BOOT_MODE = 0x00,       /*!< 引导协议模式*/
    ESP_HIDH_REPORT_MODE = 0x01,     /*!< 报告协议模式*/
    ESP_HIDH_UNSUPPORTED_MODE = 0xff /*!< 不支持的协议模式*/
} esp_hidh_protocol_mode_t;

/**
 * @brief HID主机报告类型
 */
typedef enum {
    ESP_HIDH_REPORT_TYPE_OTHER = 0, /*!< 不支持的报告类型*/
    ESP_HIDH_REPORT_TYPE_INPUT,     /*!< 输入报告类型*/
    ESP_HIDH_REPORT_TYPE_OUTPUT,    /*!< 输出报告类型*/
    ESP_HIDH_REPORT_TYPE_FEATURE,   /*!< 功能报告类型*/
} esp_hidh_report_type_t;

/**
 * @brief HID主机回调函数事件
 */
typedef enum {
    ESP_HIDH_INIT_EVT = 0,  /*!< 当HID主机初始化时，事件发生*/
    ESP_HIDH_DEINIT_EVT,    /*!< 当HID主机被卸载时，事件发生*/
    ESP_HIDH_OPEN_EVT,      /*!< 当HID主机连接打开时，事件发生*/
    ESP_HIDH_CLOSE_EVT,     /*!< 当HID主机连接关闭时，事件发生*/
    ESP_HIDH_GET_RPT_EVT,   /*!< 调用Get_Report命令时，事件发生*/
    ESP_HIDH_SET_RPT_EVT,   /*!< 调用Set_Report命令时，事件发生*/
    ESP_HIDH_GET_PROTO_EVT, /*!< 调用Get_Protocol命令时，事件发生*/
    ESP_HIDH_SET_PROTO_EVT, /*!< 调用Set_Protocol命令时，事件发生*/
    ESP_HIDH_GET_IDLE_EVT,  /*!< 调用Get_Idle命令时，事件发生*/
    ESP_HIDH_SET_IDLE_EVT,  /*!< 调用Set_Idle命令时，事件将出现*/
    ESP_HIDH_GET_DSCP_EVT,  /*!< 当HIDH初始化时，事件发生*/
    ESP_HIDH_ADD_DEV_EVT,   /*!< 添加设备时，事件发生*/
    ESP_HIDH_RMV_DEV_EVT,   /*!< 移除设备后，事件发生*/
    ESP_HIDH_VC_UNPLUG_EVT, /*!< 当实际拔下电源时，事件就会发生*/
    ESP_HIDH_DATA_EVT,      /*!< 当在中断通道上发送数据时，事件发生*/
    ESP_HIDH_DATA_IND_EVT,  /*!< 当在中断通道上接收数据时，事件发生*/
    ESP_HIDH_SET_INFO_EVT   /*!< 当设置HID设备描述符时，事件发生*/
} esp_hidh_cb_event_t;

typedef struct {
    int attr_mask;
    uint8_t sub_class;
    uint8_t app_id;
    int vendor_id;
    int product_id;
    int version;
    uint8_t ctry_code;
    int dl_len;
    uint8_t dsc_list[BTHH_MAX_DSC_LEN];
} esp_hidh_hid_info_t;

/**
 * @brief HID主机回调参数联合
 */
typedef union {
    /**
     * @brief ESP_HIDH_INIT_EVT
     */
    struct hidh_init_evt_param {
        esp_hidh_status_t status; /*!< 地位*/
    } init;                       /*!< ESP_HIDH_INIT_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_DEINIT_EVT
     */
    struct hidh_uninit_evt_param {
        esp_hidh_status_t status; /*!< 地位*/
    } deinit;                     /*!< ESP_HIDH_DEINIT_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_OPEN_EVT
     */
    struct hidh_open_evt_param {
        esp_hidh_status_t status;                /*!< 运行状态*/
        esp_hidh_connection_state_t conn_status; /*!< 连接状态*/
        bool is_orig;                            /*!< 指示主机是否初始化连接*/
        uint8_t handle;                          /*!< 设备手柄*/
        esp_bd_addr_t bd_addr;                   /*!< 设备地址*/
    } open;                                      /*!< ESP_HIDH_OPEN_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_CLOSE_EVT
     */
    struct hidh_close_evt_param {
        esp_hidh_status_t status;                /*!< 运行状态*/
        uint8_t reason;                          /*!< 下层失败原因（ref hiddefs.h）*/
        esp_hidh_connection_state_t conn_status; /*!< 连接状态*/
        uint8_t handle;                          /*!< 设备手柄*/
    } close;                                     /*!< ESP_HIDH_CLOSE_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_VC_UNPLUG_EVT
     */
    struct hidh_unplug_evt_param {
        esp_hidh_status_t status;                /*!< 运行状态*/
        esp_hidh_connection_state_t conn_status; /*!< 连接状态*/
        uint8_t handle;                          /*!< 设备手柄*/
    } unplug;                                    /*!< ESP_HIDH_VC_UNPLUG_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_GET_PROTO_EVT
     */
    struct hidh_get_proto_evt_param {
        esp_hidh_status_t status;            /*!< 运行状态*/
        uint8_t handle;                      /*!< 设备手柄*/
        esp_hidh_protocol_mode_t proto_mode; /*!< 协议模式*/
    } get_proto;                             /*!< ESP_HIDH_GET_PROTO_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_SET_PROTO_EVT
     */
    struct hidh_set_proto_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
    } set_proto;                  /*!< ESP_HIDH_SET_PROTO_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_GET_RPT_EVT
     */
    struct hidh_get_rpt_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        uint16_t len;             /*!< 数据长度*/
        uint8_t *data;            /*!< 数据指针*/
    } get_rpt;                    /*!< ESP_HIDH_GET_RPT_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_SET_RPT_EVT
     */
    struct hidh_set_rpt_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
    } set_rpt;                    /*!< ESP_HIDH_SET_RPT_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_DATA_EVT
     */
    struct hidh_send_data_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        uint8_t reason;           /*!< 下层失败原因（ref hiddefs.h）*/
    } send_data;                  /*!< ESP_HIDH_DATA_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_GET_IDLE_EVT
     */
    struct hidh_get_idle_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        uint8_t idle_rate;        /*!< 闲置率*/
    } get_idle;                   /*!< ESP_HIDH_GET_IDLE_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_SET_IDLE_EVT
     */
    struct hidh_set_idle_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
    } set_idle;                   /*!< ESP_HIDH_SET_IDLE_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_DATA_IND_EVT
     */
    struct hidh_data_ind_evt_param {
        esp_hidh_status_t status;            /*!< 运行状态*/
        uint8_t handle;                      /*!< 设备手柄*/
        esp_hidh_protocol_mode_t proto_mode; /*!< 协议模式*/
        uint16_t len;                        /*!< 数据长度*/
        uint8_t *data;                       /*!< 数据指针*/
    } data_ind;                              /*!< ESP_HIDH_DATA_IND_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_ADD_DEV_EVT
     */
    struct hidh_add_dev_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        esp_bd_addr_t bd_addr;    /*!< 设备地址*/
    } add_dev;                    /*!< ESP_HIDH_ADD_DEV_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_RMV_DEV_EVT
     */
    struct hidh_rmv_dev_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        esp_bd_addr_t bd_addr;    /*!< 设备地址*/
    } rmv_dev;                    /*!< ESP_HIDH_RMV_DEV_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_GET_DSCP_EVT
     */
    struct hidh_get_dscp_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        bool added;               /*!< 说明是否添加*/
        uint16_t vendor_id;       /*!< 供应商ID*/
        uint16_t product_id;      /*!< 产品ID*/
        uint16_t version;         /*!< 版本*/
        uint16_t ssr_max_latency; /*!< SSR最大延迟*/
        uint16_t ssr_min_tout;    /*!< SSR最小超时*/
        uint8_t ctry_code;        /*!< 国家/地区代码*/
        uint16_t dl_len;          /*!< 设备描述符长度*/
        uint8_t *dsc_list;        /*!< 设备描述符指针*/
    } dscp;                       /*!< ESP_HIDH_GET_DSCP_EVT的HIDH回调参数*/

    /**
     * @brief ESP_HIDH_SET_INFO_EVT
     */
    struct hidh_set_info_evt_param {
        esp_hidh_status_t status; /*!< 运行状态*/
        uint8_t handle;           /*!< 设备手柄*/
        esp_bd_addr_t bd_addr;    /*!< 设备地址*/
    } set_info;                   /*!< ESP_HIDH_SET_INFO_EVT的HIDH回调参数*/
} esp_hidh_cb_param_t;

/**
 * @brief       HID主机回调函数类型
 * @param       event:      事件类型
 * @param       param:      指向回调参数，当前为联合类型
 */
typedef void (esp_hh_cb_t)(esp_hidh_cb_event_t event, esp_hidh_cb_param_t *param);

/**
 * @brief       调用此函数以初始化HID主机模块的回调。
 *
 * @param[in]   callback:   指向init回调函数的指针。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_register_callback(esp_hh_cb_t callback);

/**
 * @brief       此函数初始化HID主机。该函数应在esp_bluedroid_enable（）和esp_blueroid_init（）成功后调用，并且应在esp_bt_hid_host_register_callback（）后调用。操作完成后，将使用ESP_HIDH_INIT_EVT调用回调函数。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_init(void);

/**
 * @brief       关闭界面。该函数应在esp_bluedroid_enable（）和esp_blueroid_init（）成功后调用，并且应在esp_bt_hid_host_init（（）后调用。操作完成后，将使用ESP_HIDH_DEINIT_EVT调用回调函数。
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_deinit(void);

/**
 * @brief       连接到隐藏设备。操作完成后，将使用ESP_HIDH_OPEN_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_connect(esp_bd_addr_t bd_addr);

/**
 * @brief       断开与隐藏设备的连接。操作完成后，将使用ESP_HIDH_CLOSE_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_disconnect(esp_bd_addr_t bd_addr);

/**
 * @brief       虚拟解压缩（VUP）指定的HID设备。操作完成后，将使用ESP_HIDH_VC_UNPLUG_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_virtual_cable_unplug(esp_bd_addr_t bd_addr);

/**
 * @brief       为指定的HID设备设置HID设备描述符。操作完成后，将使用ESP_HIDH_SET_INFO_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 * @param[in]   hid_info:  HID设备描述符结构。
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_set_info(esp_bd_addr_t bd_addr, esp_hidh_hid_info_t *hid_info);

/**
 * @brief       获取HID原型模式。操作完成后，将使用ESP_HIDH_GET_PROTO_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_get_protocol(esp_bd_addr_t bd_addr);

/**
 * @brief       设置HID原型模式。操作完成后，将使用ESP_HIDH_SET_PROTO_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 * @param[in]   protocol_mode:  协议模式类型。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_set_protocol(esp_bd_addr_t bd_addr, esp_hidh_protocol_mode_t protocol_mode);

/**
 * @brief       获取HID空闲时间。操作完成后，将使用ESP_HIDH_GET_IDLE_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_get_idle(esp_bd_addr_t bd_addr);

/**
 * @brief       设置HID空闲时间。操作完成后，将使用ESP_HIDH_SET_IDLE_VT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 * @param[in]   idle_time:  空闲时间率
 *
 * @return    -ESP_OK：成功
 *            -其他：失败
 */
esp_err_t esp_bt_hid_host_set_idle(esp_bd_addr_t bd_addr, uint16_t idle_time);

/**
 * @brief       向HID设备发送GET_REPORT。操作完成后，将使用ESP_HIDH_GET_RPT_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 * @param[in]   report_type:  报告类型
 * @param[in]   report_id:  报告id
 * @param[in]   buffer_size:  缓冲区大小
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_get_report(esp_bd_addr_t bd_addr, esp_hidh_report_type_t report_type, uint8_t report_id,
                                     int buffer_size);

/**
 * @brief       向HID设备发送SET_REPORT。操作完成后，将使用ESP_HIDH_SET_RPT_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 * @param[in]   report_type:  报告类型
 * @param[in]   report:  报告数据指针
 * @param[in]   len:  报告数据长度
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_set_report(esp_bd_addr_t bd_addr, esp_hidh_report_type_t report_type, uint8_t *report,
                                     size_t len);

/**
 * @brief       向HID设备发送数据。操作完成后，将使用ESP_HIDH_DATA_EVT调用回调函数。
 *
 * @param[in]   bd_addr:  远程设备蓝牙设备地址。
 * @param[in]   data:  数据指针
 * @param[in]   len:  数据长度
 *
 * @return      -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_bt_hid_host_send_data(esp_bd_addr_t bd_addr, uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif

