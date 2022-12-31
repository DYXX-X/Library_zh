// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_GATTS_API_H__
#define __ESP_GATTS_API_H__

#include "esp_bt_defs.h"
#include "esp_gatt_defs.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

///GATT服务器回调函数事件
typedef enum {
    ESP_GATTS_REG_EVT                 = 0,       /*!< 注册应用程序id时，事件发生*/
    ESP_GATTS_READ_EVT                = 1,       /*!< 当gatt客户端请求读取操作时，事件发生*/
    ESP_GATTS_WRITE_EVT               = 2,       /*!< 当gatt客户端请求写入操作时，事件发生*/
    ESP_GATTS_EXEC_WRITE_EVT          = 3,       /*!< 当gatt客户端请求执行write时，事件发生*/
    ESP_GATTS_MTU_EVT                 = 4,       /*!< 当设置mtu完成时，事件发生*/
    ESP_GATTS_CONF_EVT                = 5,       /*!< 当接收确认时，事件发生*/
    ESP_GATTS_UNREG_EVT               = 6,       /*!< 注销应用程序id时，事件将出现*/
    ESP_GATTS_CREATE_EVT              = 7,       /*!< 创建服务完成后，事件发生*/
    ESP_GATTS_ADD_INCL_SRVC_EVT       = 8,       /*!< 当添加包含的服务完成时，事件发生*/
    ESP_GATTS_ADD_CHAR_EVT            = 9,       /*!< 当添加特征完成时，事件发生*/
    ESP_GATTS_ADD_CHAR_DESCR_EVT      = 10,      /*!< 添加描述符完成后，事件将出现*/
    ESP_GATTS_DELETE_EVT              = 11,      /*!< 删除服务完成后，事件发生*/
    ESP_GATTS_START_EVT               = 12,      /*!< 启动服务完成后，事件发生*/
    ESP_GATTS_STOP_EVT                = 13,      /*!< 停止服务完成后，事件发生*/
    ESP_GATTS_CONNECT_EVT             = 14,      /*!< 当gatt客户端连接时，事件发生*/
    ESP_GATTS_DISCONNECT_EVT          = 15,      /*!< 当gatt客户端断开连接时，事件发生*/
    ESP_GATTS_OPEN_EVT                = 16,      /*!< 当连接到对等时，事件发生*/
    ESP_GATTS_CANCEL_OPEN_EVT         = 17,      /*!< 当与对等方断开连接时，事件发生*/
    ESP_GATTS_CLOSE_EVT               = 18,      /*!< 当gatt服务器关闭时，事件发生*/
    ESP_GATTS_LISTEN_EVT              = 19,      /*!< 当gatt收听连接时，事件发生了*/
    ESP_GATTS_CONGEST_EVT             = 20,      /*!< 当拥堵发生时，事件就发生了*/
    /* 以下是额外事件*/
    ESP_GATTS_RESPONSE_EVT            = 21,      /*!< 当gatt发送响应完成时，事件发生*/
    ESP_GATTS_CREAT_ATTR_TAB_EVT      = 22,      /*!< 当gatt创建表完成时，事件发生*/
    ESP_GATTS_SET_ATTR_VAL_EVT        = 23,      /*!< 当gatt设置属性值完成时，事件发生*/
    ESP_GATTS_SEND_SERVICE_CHANGE_EVT = 24,      /*!< 当gatt发送服务更改指示完成时，事件发生*/
} esp_gatts_cb_event_t;

/**
 * @brief Gatt服务器回调参数联合
 */
typedef union {
    /**
     * @brief ESP_GATTS_REG_EVT
     */
    struct gatts_reg_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t app_id;                /*!< 在注册API中输入的应用程序id*/
    } reg;                              /*!< ESP_GATTS_REG_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_READ_EVT
     */
    struct gatts_read_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint32_t trans_id;              /*!< 传输id*/
        esp_bd_addr_t bda;              /*!< 已读取的蓝牙设备地址*/
        uint16_t handle;                /*!< 属性句柄*/
        uint16_t offset;                /*!< 值的偏移（如果值太长）*/
        bool is_long;                   /*!< 值是否过长*/
        bool need_rsp;                  /*!< 读取操作需要进行响应*/
    } read;                             /*!< ESP_GATTS_READ_EVT的Gatt服务器回调参数*/


    /**
     * @brief ESP_GATTS_WRITE_EVT
     */
    struct gatts_write_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint32_t trans_id;              /*!< 传输id*/
        esp_bd_addr_t bda;              /*!< 已写入的蓝牙设备地址*/
        uint16_t handle;                /*!< 属性句柄*/
        uint16_t offset;                /*!< 值的偏移（如果值太长）*/
        bool need_rsp;                  /*!< 写操作需要做响应*/
        bool is_prep;                   /*!< 此写入操作是准备写入*/
        uint16_t len;                   /*!< 写入属性值长度*/
        uint8_t *value;                 /*!< 写入属性值*/
    } write;                            /*!< ESP_GATTS_WRITE_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_EXEC_WRITE_EVT
     */
    struct gatts_exec_write_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint32_t trans_id;              /*!< 传输id*/
        esp_bd_addr_t bda;              /*!< 已写入的蓝牙设备地址*/
#define ESP_GATT_PREP_WRITE_CANCEL 0x00 /*!< 准备写入标志，指示取消准备写入*/
#define ESP_GATT_PREP_WRITE_EXEC   0x01 /*!< 准备写入标志，指示执行准备写入*/
        uint8_t exec_write_flag;        /*!< 执行写入标志*/
    } exec_write;                       /*!< ESP_GATTS_EXEC_WRITE_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_MTU_EVT
     */
    struct gatts_mtu_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint16_t mtu;                   /*!< MTU大小*/
    } mtu;                              /*!< ESP_GATTS_MTU_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_CONF_EVT
     */
    struct gatts_conf_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
        uint16_t handle;                /*!< 属性句柄*/
        uint16_t len;                   /*!< 发送通知或指示失败时，指示或通知值长度len有效*/
        uint8_t *value;                 /*!< 当发送通知或指示失败时，指示或通知值有效*/
    } conf;                             /*!< ESP_GATTS_CONF_EVT的门控服务器回调参数（确认）*/

    /**
     * @brief ESP_GATTS_UNREG_EVT
     */

    /**
     * @brief ESP_GATTS_CREATE_EVT
     */
    struct gatts_create_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
        esp_gatt_srvc_id_t service_id;  /*!< 服务id，包括服务uuid和其他信息*/
    } create;                           /*!< ESP_GATTS_CREATE_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_ADD_INCL_SRVC_EVT
     */
    struct gatts_add_incl_srvc_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t attr_handle;           /*!< 包含的服务属性句柄*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
    } add_incl_srvc;                    /*!< ESP_GATTS_ADD_INCL_SRVC_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_ADD_CHAR_EVT
     */
    struct gatts_add_char_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t attr_handle;           /*!< 特征属性句柄*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
        esp_bt_uuid_t char_uuid;        /*!< 特征uuid*/
    } add_char;                         /*!< ESP_GATTS_ADD_CHAR_EVT的门控服务器回调参数*/

    /**
     * @brief ESP_GATTS_ADD_CHAR_DESCR_EVT
     */
    struct gatts_add_char_descr_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t attr_handle;           /*!< 描述符属性句柄*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
        esp_bt_uuid_t descr_uuid;       /*!< 特征描述符uuid*/
    } add_char_descr;                   /*!< ESP_GATTS_ADD_CHAR_DESCR_EVT的门控服务器回调参数*/

    /**
     * @brief ESP_GATTS_DELETE_EVT
     */
    struct gatts_delete_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
    } del;                              /*!< ESP_GATTS_DELETE_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_START_EVT
     */
    struct gatts_start_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
    } start;                            /*!< ESP_GATTS_START_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_STOP_EVT
     */
    struct gatts_stop_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t service_handle;        /*!< 服务属性句柄*/
    } stop;                             /*!< ESP_GATTS_STOP_EVT的门控服务器回调参数*/

    /**
     * @brief ESP_GATTS_CONNECT_EVT
     */
    struct gatts_connect_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint8_t link_role;              /*!< 链接角色：主角色=0；从属角色=1*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
        esp_gatt_conn_params_t conn_params; /*!< 当前连接参数*/
    } connect;                          /*!< ESP_GATTS_CONNECT_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_DISCONNECT_EVT
     */
    struct gatts_disconnect_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
        esp_gatt_conn_reason_t reason;  /*!< 说明断开的原因*/
    } disconnect;                       /*!< ESP_GATTS_DISCONNECT_VT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_OPEN_EVT
     */
    struct gatts_open_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
    } open;                             /*!< ESP_GATTS_OPEN_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_CANCEL_OPEN_EVT
     */
    struct gatts_cancel_open_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
    } cancel_open;                      /*!< ESP_GATTS_CANCEL_OPEN_EVT的门控服务器回调参数*/

    /**
     * @brief ESP_GATTS_CLOSE_EVT
     */
    struct gatts_close_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
    } close;                            /*!< ESP_GATTS_CLOSE_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_LISTEN_EVT
     */
    /**
     * @brief ESP_GATTS_CONGEST_EVT
     */
    struct gatts_congest_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        bool congested;                 /*!< 是否拥挤*/
    } congest;                          /*!< ESP_GATTS_CONGEST_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_RESPONSE_EVT
     */
    struct gatts_rsp_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t handle;                /*!< 发送响应的属性句柄*/
    } rsp;                              /*!< ESP_GATTS_RESPONSE_EVT的Gatt服务器回调参数*/

    /**
     * @brief ESP_GATTS_CREAT_ATTR_TAB_EVT
     */
    struct gatts_add_attr_tab_evt_param{
        esp_gatt_status_t status;       /*!< 运行状态*/
        esp_bt_uuid_t svc_uuid;         /*!< 服务uuid类型*/
        uint8_t svc_inst_id;            /*!< 服务id*/
        uint16_t num_handle;            /*!< 要添加到gatts数据库的属性句柄的编号*/
        uint16_t *handles;              /*!< 把手的编号*/
    } add_attr_tab;                     /*!< ESP_GATTS_CREAT_ATTR_TAB_EVT的门控服务器回调参数*/


   /**
    * @brief ESP_GATTS_SET_ATTR_VAL_EVT
    */
    struct gatts_set_attr_val_evt_param{
        uint16_t srvc_handle;           /*!< 服务手柄*/
        uint16_t attr_handle;           /*!< 属性句柄*/
        esp_gatt_status_t status;       /*!< 运行状态*/
    } set_attr_val;                     /*!< ESP_GATTS_SET_ATTR_VAL_EVT的门控服务器回调参数*/

    /**
    * @brief ESP_GATTS_SEND_SERVICE_CHANGE_EVT
    */
    struct gatts_send_service_change_evt_param{
        esp_gatt_status_t status;       /*!< 运行状态*/
    } service_change;                    /*!< ESP_GATTS_SEND_SERVICE_CHANGE_EVT的Gatt服务器回调参数*/

} esp_ble_gatts_cb_param_t;

/**
 * @brief GATT服务器回调函数类型
 * @param event ：事件类型
 * @param gatts_if ：GATT服务器访问接口，通常不同的gatts_if对应于不同的配置文件
 * @param param ：指向回调参数，当前为联合类型
 */
typedef void (* esp_gatts_cb_t)(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

/**
 * @brief           调用此函数以向BTA GATTS模块注册应用程序回调。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_register_callback(esp_gatts_cb_t callback);

/**
 * @brief           调用此函数以注册应用程序标识符
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_app_register(uint16_t app_id);



/**
 * @brief           注销GATT服务器。
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_app_unregister(esp_gatt_if_t gatts_if);


/**
 * @brief           创建服务。服务创建完成后，将调用回调事件ESP_GATTS_CREATE_EVT，以向概要文件报告状态和服务ID。在将包含的服务和特征/描述符添加到服务中时，需要使用回调函数中获得的服务ID。
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       service_id: 服务ID。
 * @param[in]       num_handle: 为此服务请求的句柄数。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_create_service(esp_gatt_if_t gatts_if,
                                       esp_gatt_srvc_id_t *service_id, uint16_t num_handle);


/**
 * @brief               创建服务属性选项卡。
 * @param[in]       gatts_attr_db: 指向服务属性选项卡的指针
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       max_nb_attr: 要添加到服务数据库的属性的数量。
 * @param[in]       srvc_inst_id: 服务的实例id
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_create_attr_tab(const esp_gatts_attr_db_t *gatts_attr_db,
                                            esp_gatt_if_t gatts_if,
                                            uint8_t max_nb_attr,
                                            uint8_t srvc_inst_id);
/**
 * @brief           调用此函数以添加包含的服务。必须在“esp_ble_gatts_create_service”和“esp_ble _gatts_add_char”之间调用此函数。在包含服务之后，回调事件ESP_GATTS_ADD_INCL_SRVC_EVT被报告为包含的服务ID。
 *
 * @param[in]       service_handle: 要向其中添加此包含服务的服务句柄。
 * @param[in]       included_service_handle: 要包括的服务ID。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_add_included_service(uint16_t service_handle, uint16_t included_service_handle);



/**
 * @brief           调用此函数将特性添加到服务中。
 *
 * @param[in]       service_handle: 要向其中添加此包含服务的服务句柄。
 * @param[in]       char_uuid ：特征UUID。
 * @param[in]       perm      ：特征值声明属性权限。
 * @param[in]       property  ：特性属性
 * @param[in]       char_val    ：特征值
 * @param[in]       control ：属性响应控制字节
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_add_char(uint16_t service_handle,  esp_bt_uuid_t  *char_uuid,
                                 esp_gatt_perm_t perm, esp_gatt_char_prop_t property, esp_attr_value_t *char_val,
                                 esp_attr_control_t *control);


/**
 * @brief           调用此函数以添加特征描述符。完成后，将调用回调事件ESP_GATTS_ADD_DESCR_EVT来报告此描述符的状态和ID号。
 *
 * @param[in]       service_handle: 要向其添加此特征描述符的服务句柄。
 * @param[in]       perm: 描述符访问权限。
 * @param[in]       descr_uuid: 描述符UUID。
 * @param[in]       char_descr_val  ：特征描述符值
 * @param[in]       control ：属性响应控制字节
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_add_char_descr (uint16_t service_handle,
                                        esp_bt_uuid_t   *descr_uuid,
                                        esp_gatt_perm_t perm, esp_attr_value_t *char_descr_val,
                                        esp_attr_control_t *control);



/**
 * @brief           调用此函数以删除服务。完成此操作后，将报告一个回调事件ESP_GATTS_DELETE_EVT及其状态。
 *
 * @param[in]       service_handle: 要删除的service_handle。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_delete_service(uint16_t service_handle);



/**
 * @brief           调用此函数以启动服务。
 *
 * @param[in]       service_handle: 要启动的服务句柄。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_start_service(uint16_t service_handle);



/**
 * @brief           调用此函数以停止服务。
 *
 * @param[in]       service_handle -服务将达到最高水平。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_stop_service(uint16_t service_handle);



/**
 * @brief           向GATT客户发送指示或通知。将参数need_confirm设置为false将发送通知，否则表示。
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       conn_id -要指示的连接id。
 * @param[in]       attr_handle -要指示的属性句柄。
 * @param[in]       value_len -指示值长度。
 * @param[in]       value: 要指示的值。
 * @param[in]       need_confirm -是否需要确认。false发送GATT通知，true发送GATT指示。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_send_indicate(esp_gatt_if_t gatts_if, uint16_t conn_id, uint16_t attr_handle,
                                      uint16_t value_len, uint8_t *value, bool need_confirm);


/**
 * @brief           调用此函数以发送对请求的响应。
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       conn_id -连接标识符。
 * @param[in]       trans_id -传输id
 * @param[in]       status -响应状态
 * @param[in]       rsp -响应数据。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_send_response(esp_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id,
                                      esp_gatt_status_t status, esp_gatt_rsp_t *rsp);


/**
 * @brief           应用程序调用此函数来设置属性值
 *
 * @param[in]       attr_handle: 要设置的属性句柄
 * @param[in]       length: 值长度
 * @param[in]       value: 指向属性值的指针
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_set_attr_value(uint16_t attr_handle, uint16_t length, const uint8_t *value);

/**
 * @brief       检索属性值
 *
 * @param[in]   attr_handle: 属性句柄。
 * @param[out]  length: 指向属性值长度的指针
 * @param[out]  value:  指向属性值有效负载的指针，用户无法修改该值
 *
 * @return
 *                  -ESP_GATT_OK:成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gatts_get_attr_value(uint16_t attr_handle, uint16_t *length, const uint8_t **value);


/**
 * @brief           打开直接打开的连接或添加后台自动连接
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       remote_bda: 远程设备蓝牙设备地址。
 * @param[in]       is_direct: 直接连接或后台自动连接
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_open(esp_gatt_if_t gatts_if, esp_bd_addr_t remote_bda, bool is_direct);

/**
 * @brief           关闭远程设备的连接。
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       conn_id: 要关闭的连接ID。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_close(esp_gatt_if_t gatts_if, uint16_t conn_id);

/**
 * @brief           发送服务更改指示
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       remote_bda: 远程设备蓝牙设备地址。如果remote_bda为NULL，则它将向所有连接的设备发送服务更改指示，如果不是，则向特定设备发送
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gatts_send_service_change_indication(esp_gatt_if_t gatts_if, esp_bd_addr_t remote_bda);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_GATTS_API_H__ */

