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

#ifndef __ESP_GATTC_API_H__
#define __ESP_GATTC_API_H__

#include "esp_bt_defs.h"
#include "esp_gatt_defs.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

///GATT客户端回调函数事件
typedef enum {
    ESP_GATTC_REG_EVT                 = 0,        /*!< GATT客户注册后，事件发生*/
    ESP_GATTC_UNREG_EVT               = 1,        /*!< 当GATT客户端未注册时，事件发生*/
    ESP_GATTC_OPEN_EVT                = 2,        /*!< 当设置GATT虚拟连接时，事件发生*/
    ESP_GATTC_READ_CHAR_EVT           = 3,        /*!< 当读取GATT特征时，事件发生*/
    ESP_GATTC_WRITE_CHAR_EVT          = 4,        /*!< 当GATT特征写入操作完成时，事件发生*/
    ESP_GATTC_CLOSE_EVT               = 5,        /*!< 当GATT虚拟连接关闭时，事件发生*/
    ESP_GATTC_SEARCH_CMPL_EVT         = 6,        /*!< GATT服务发现完成后，事件发生*/
    ESP_GATTC_SEARCH_RES_EVT          = 7,        /*!< 当获得GATT服务发现结果时，事件发生*/
    ESP_GATTC_READ_DESCR_EVT          = 8,        /*!< 当GATT特征描述符读取完成时，事件发生*/
    ESP_GATTC_WRITE_DESCR_EVT         = 9,        /*!< 当GATT特征描述符写入完成时，事件发生*/
    ESP_GATTC_NOTIFY_EVT              = 10,       /*!< 当GATT通知或指示到达时，事件发生*/
    ESP_GATTC_PREP_WRITE_EVT          = 11,       /*!< 当GATT准备写入操作完成时，事件发生*/
    ESP_GATTC_EXEC_EVT                = 12,       /*!< 当写入执行完成时，事件发生*/
    ESP_GATTC_ACL_EVT                 = 13,       /*!< 当ACL连接打开时，事件发生*/
    ESP_GATTC_CANCEL_OPEN_EVT         = 14,       /*!< 当GATT客户端正在进行的连接被取消时，事件发生*/
    ESP_GATTC_SRVC_CHG_EVT            = 15,       /*!< 当“服务更改”发生时，事件发生*/
    ESP_GATTC_ENC_CMPL_CB_EVT         = 17,       /*!< 当加密过程完成时，事件发生*/
    ESP_GATTC_CFG_MTU_EVT             = 18,       /*!< MTU配置完成后，事件发生*/
    ESP_GATTC_ADV_DATA_EVT            = 19,       /*!< 当数据广告时，事件发生*/
    ESP_GATTC_MULT_ADV_ENB_EVT        = 20,       /*!< 启用多广告时，事件发生*/
    ESP_GATTC_MULT_ADV_UPD_EVT        = 21,       /*!< 当多个广告参数更新时，事件发生*/
    ESP_GATTC_MULT_ADV_DATA_EVT       = 22,       /*!< 当多个广告数据到达时，事件发生*/
    ESP_GATTC_MULT_ADV_DIS_EVT        = 23,       /*!< 禁用多广告时，事件发生*/
    ESP_GATTC_CONGEST_EVT             = 24,       /*!< 当GATT连接拥塞时，事件就发生了*/
    ESP_GATTC_BTH_SCAN_ENB_EVT        = 25,       /*!< 当启用批扫描时，事件发生*/
    ESP_GATTC_BTH_SCAN_CFG_EVT        = 26,       /*!< 配置批扫描存储时，事件发生*/
    ESP_GATTC_BTH_SCAN_RD_EVT         = 27,       /*!< 当报告批扫描读取事件时，事件将出现*/
    ESP_GATTC_BTH_SCAN_THR_EVT        = 28,       /*!< 当设置了批量扫描阈值时，事件发生*/
    ESP_GATTC_BTH_SCAN_PARAM_EVT      = 29,       /*!< 设置批扫描参数后，事件发生*/
    ESP_GATTC_BTH_SCAN_DIS_EVT        = 30,       /*!< 禁用批扫描时，事件发生*/
    ESP_GATTC_SCAN_FLT_CFG_EVT        = 31,       /*!< 扫描筛选器配置完成后，事件发生*/
    ESP_GATTC_SCAN_FLT_PARAM_EVT      = 32,       /*!< 设置扫描筛选器参数后，事件发生*/
    ESP_GATTC_SCAN_FLT_STATUS_EVT     = 33,       /*!< 当报告扫描筛选器状态时，事件发生*/
    ESP_GATTC_ADV_VSC_EVT             = 34,       /*!< 当报告广告供应商规范内容事件时，事件发生*/
    ESP_GATTC_REG_FOR_NOTIFY_EVT      = 38,       /*!< 当注册服务通知完成时，事件发生*/
    ESP_GATTC_UNREG_FOR_NOTIFY_EVT    = 39,       /*!< 当取消注册服务通知完成时，事件发生*/
    ESP_GATTC_CONNECT_EVT             = 40,       /*!< 当建立ble物理连接时，事件发生*/
    ESP_GATTC_DISCONNECT_EVT          = 41,       /*!< 当ble物理连接断开时，事件发生*/
    ESP_GATTC_READ_MULTIPLE_EVT       = 42,       /*!< 当布尔特征或描述符多重完成时，事件发生*/
    ESP_GATTC_QUEUE_FULL_EVT          = 43,       /*!< 当gattc命令队列已满时，事件将出现*/
    ESP_GATTC_SET_ASSOC_EVT           = 44,       /*!< 当ble gattc设置相关地址完成时，事件发生*/
    ESP_GATTC_GET_ADDR_LIST_EVT       = 45,       /*!< 当缓存中的ble get gattc地址列表完成时，事件发生*/
    ESP_GATTC_DIS_SRVC_CMPL_EVT       = 46,       /*!< 当ble discover服务完成时，事件发生*/
} esp_gattc_cb_event_t;


/**
 * @brief Gatt客户端回调参数联合
 */
typedef union {
    /**
     * @brief ESP_GATTC_REG_EVT
     */
    struct gattc_reg_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t app_id;                /*!< 在注册API中输入的应用程序id*/
    } reg;                              /*!< ESP_GATTC_REG_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_OPEN_EVT
     */
    struct gattc_open_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
        uint16_t mtu;                   /*!< MTU大小*/
    } open;                             /*!< ESP_GATTC_OPEN_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_CLOSE_EVT
     */
    struct gattc_close_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
        esp_gatt_conn_reason_t reason;  /*!< gatt连接关闭的原因*/
    } close;                            /*!< ESP_GATTC_CLOSE_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_CFG_MTU_EVT
     */
    struct gattc_cfg_mtu_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
        uint16_t mtu;                   /*!< MTU大小*/
    } cfg_mtu;                          /*!< ESP_GATTC_CFG_MTU_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_SEARCH_CMPL_EVT
     */
    struct gattc_search_cmpl_evt_param {
        esp_gatt_status_t status;                     /*!< 运行状态*/
        uint16_t conn_id;                             /*!< 连接id*/
        esp_service_source_t searched_service_source; /*!< 服务信息的来源*/
    } search_cmpl;                                    /*!< ESP_GATTC_SEARCH_MPL_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_SEARCH_RES_EVT
     */
    struct gattc_search_res_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint16_t start_handle;          /*!< 服务启动手柄*/
        uint16_t end_handle;            /*!< 服务端手柄*/
        esp_gatt_id_t srvc_id;          /*!< 服务id，包括服务uuid和其他信息*/
        bool      is_primary;           /*!< 如果这是主要服务，则为True*/
    } search_res;                       /*!< ESP_GATTC_SEARCH_RES_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_READ_CHAR_EVT,  ESP_GATTC_READ_DESCR_EVT
     */
    struct gattc_read_char_evt_param {

        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
        uint16_t handle;                /*!< 特色手柄*/
        uint8_t *value;                 /*!< 特征值*/
        uint16_t value_len;             /*!< 特征值长度*/
    } read;                             /*!< ESP_GATTC_READ_CHAR_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_WRITE_CHAR_EVT, ESP_GATTC_PREP_WRITE_EVT, ESP_GATTC_WRITE_DESCR_EVT
     */
    struct gattc_write_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
        uint16_t handle;                /*!< 特征或描述符句柄*/
        uint16_t offset;                /*!< 准备写入偏移量，此值仅在准备写入时有效*/
    } write;                            /*!< ESP_GATTC_WRITE_DESCR_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_EXEC_EVT
     */
    struct gattc_exec_cmpl_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t conn_id;               /*!< 连接id*/
    } exec_cmpl;                        /*!< ESP_GATTC_EXEC_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_NOTIFY_EVT
     */
    struct gattc_notify_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
        uint16_t handle;                /*!< 特征或描述符句柄*/
        uint16_t value_len;             /*!< 通知属性值*/
        uint8_t *value;                 /*!< 通知属性值*/
        bool is_notify;                 /*!< True表示通知，false表示指示*/
    } notify;                           /*!< ESP_GATTC_NOTIFY_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_SRVC_CHG_EVT
	 */
    struct gattc_srvc_chg_evt_param {
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
    } srvc_chg;                         /*!< ESP_GATTC_SRVC_CHG_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_CONGEST_EVT
     */
    struct gattc_congest_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        bool congested;                 /*!< 是否拥挤*/
    } congest;                          /*!< ESP_GATTC_CONGEST_EVT的Gatt客户端回调参数*/
    /**
     * @brief ESP_GATTC_REG_FOR_NOTIFY_EVT
     */
    struct gattc_reg_for_notify_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t handle;                /*!< 特征或描述符句柄*/
    } reg_for_notify;                   /*!< ESP_GATTC_REG_FOR_NOTIFY_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_UNREG_FOR_NOTIFY_EVT
     */
    struct gattc_unreg_for_notify_evt_param {
        esp_gatt_status_t status;       /*!< 运行状态*/
        uint16_t handle;                /*!< 特征或描述符句柄*/
    } unreg_for_notify;                 /*!< ESP_GATTC_UNREG_FOR_NOTIFY_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_CONNECT_EVT
     */
    struct gattc_connect_evt_param {
        uint16_t conn_id;               /*!< 连接id*/
        uint8_t link_role;              /*!< 链接角色：主角色=0；从属角色=1*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
        esp_gatt_conn_params_t conn_params; /*!< 电流连接参数*/
    } connect;                          /*!< ESP_GATTC_CONNECT_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_DISCONNECT_EVT
     */
    struct gattc_disconnect_evt_param {
        esp_gatt_conn_reason_t reason;  /*!< 断开连接原因*/
        uint16_t conn_id;               /*!< 连接id*/
        esp_bd_addr_t remote_bda;       /*!< 远程蓝牙设备地址*/
    } disconnect;                       /*!< ESP_GATTC_DISCONNECT_VT的Gatt客户端回调参数*/
    /**
     * @brief ESP_GATTC_SET_ASSOC_EVT
     */
    struct gattc_set_assoc_addr_cmp_evt_param {
        esp_gatt_status_t status;      /*!< 运行状态*/
    } set_assoc_cmp;                     /*!< ESP_GATTC_SET_ASSOC_EVT的Gatt客户端回调参数*/
    /**
     * @brief ESP_GATTC_GET_ADDR_LIST_EVT
     */
    struct gattc_get_addr_list_evt_param {
        esp_gatt_status_t status;      /*!< 运行状态*/
        uint8_t num_addr;              /*!< gattc缓存地址列表中的地址数*/
        esp_bd_addr_t *addr_list;      /*!< 指向从gattc缓存中获取的地址列表的指针*/
    } get_addr_list;                   /*!< ESP_GATTC_GET_ADDR_LIST_EVT的门控客户端回调参数*/

    /**
     * @brief ESP_GATTC_QUEUE_FULL_EVT
     */
    struct gattc_queue_full_evt_param {
        esp_gatt_status_t status;      /*!< 运行状态*/
        uint16_t conn_id;              /*!< 连接id*/
        bool     is_full;              /*!< gattc命令队列是否已满*/
    } queue_full;                      /*!< ESP_GATTC_QUEUE_FULL_EVT的Gatt客户端回调参数*/

    /**
     * @brief ESP_GATTC_DIS_SRVC_CMPL_EVT
     */
    struct gattc_dis_srvc_cmpl_evt_param {
        esp_gatt_status_t status;      /*!< 运行状态*/
        uint16_t conn_id;              /*!< 连接id*/
    } dis_srvc_cmpl;                   /*!< ESP_GATTC_DIS_SRVC_CMPL_EVT的门控客户端回调参数*/

} esp_ble_gattc_cb_param_t;             /*!< GATT客户端回调参数联合类型*/

/**
 * @brief GATT客户端回调函数类型
 * @param event ：事件类型
 * @param gattc_if ：GATT客户端访问接口，通常不同的gattc_if对应于不同的配置文件
 * @param param ：指向回调参数，当前为联合类型
 */
typedef void (* esp_gattc_cb_t)(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

/**
 * @brief           调用此函数以向GATTC模块注册应用程序回调。
 *
 * @param[in]       callback ：指向应用程序回调函数的指针。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_register_callback(esp_gattc_cb_t callback);


/**
 * @brief           调用此函数以向GATTC模块注册应用程序回调。
 *
 * @param[in]       app_id ：应用程序标识（UUID），用于不同的应用程序
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_app_register(uint16_t app_id);


/**
 * @brief           调用此函数以从GATTC模块注销应用程序。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_app_unregister(esp_gatt_if_t gattc_if);

#if (BLE_42_FEATURE_SUPPORT == TRUE)
/**
 * @brief           打开直接连接或添加后台自动连接
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       remote_bda: 远程设备蓝牙设备地址。
 * @param[in]       remote_addr_type: 远程设备蓝牙设备的地址类型。
 * @param[in]       is_direct: 直接连接或后台自动连接（目前不支持后台自动连接）。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_open(esp_gatt_if_t gattc_if, esp_bd_addr_t remote_bda, esp_ble_addr_type_t remote_addr_type, bool is_direct);
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）

#if (BLE_50_FEATURE_SUPPORT == TRUE)
esp_err_t esp_ble_gattc_aux_open(esp_gatt_if_t gattc_if, esp_bd_addr_t remote_bda, esp_ble_addr_type_t remote_addr_type, bool is_direct);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
/**
 * @brief           关闭与GATT服务器的虚拟连接。当注册多个app_id时，gattc可能具有多个虚拟GATT服务器连接，此API仅关闭一个虚拟GATS服务器连接。如果存在其他虚拟GATT服务器连接，则不会断开物理连接。如果要直接断开物理连接，可以使用espblegapdisconnect（espbdaddrremotedevice）。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 要关闭的连接ID。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_close (esp_gatt_if_t gattc_if, uint16_t conn_id);


/**
 * @brief           配置GATT通道中的MTU大小。每个连接只能执行一次。在使用之前，请使用esp_ble_gatt_set_local_mtu（）配置本地mtu大小。
 *
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 连接ID。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_send_mtu_req (esp_gatt_if_t gattc_if, uint16_t conn_id);


/**
 * @brief           调用此函数以从本地缓存获取服务。此函数通过回调事件和服务搜索完成事件报告服务搜索结果。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 连接ID。
 * @param[in]       filter_uuid: 服务应用程序的UUID感兴趣。如果为空，则查找所有服务。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_search_service(esp_gatt_if_t gattc_if, uint16_t conn_id, esp_bt_uuid_t *filter_uuid);

/**
 * @brief           在gattc缓存中查找具有给定服务uuid的所有服务，如果svc_uuid为NULL，则查找所有服务。注意：它只是从本地缓存获取服务，而不会从远程设备获取服务。如果要从远程设备获取它，需要使用esp_ble_gattc_cache_refresh，然后再次调用esp_ble_gattc_get_service。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       svc_uuid: 指向服务uuid的指针。
 * @param[out]      result: 指向在gattc缓存中找到的服务的指针。
 * @param[inout]   count: 输入要查找的服务数量，它将输出在gattc缓存中找到的具有给定服务uuid的服务数量。
 * @param[in]       offset: 要获取的服务位置的偏移。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_service(esp_gatt_if_t gattc_if, uint16_t conn_id, esp_bt_uuid_t *svc_uuid,
                                            esp_gattc_service_elem_t *result, uint16_t *count, uint16_t offset);

/**
 * @brief           在gattc缓存中查找给定服务的所有特性注意：它只是从本地缓存获取特性，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       start_handle: 属性开始句柄。
 * @param[in]       end_handle: 属性结束句柄
 * @param[out]      result: 指向服务中特征的指针。
 * @param[inout]   count: 输入要查找的特征数量，它将输出在给定服务的gattc缓存中找到的特征数量。
 * @param[in]       offset: 要获取的特征位置的偏移。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_all_char(esp_gatt_if_t gattc_if,
                                             uint16_t conn_id,
                                             uint16_t start_handle,
                                             uint16_t end_handle,
                                             esp_gattc_char_elem_t *result,
                                             uint16_t *count, uint16_t offset);

/**
 * @brief           在gattc缓存中查找具有给定特性的所有描述符注意：它只从本地缓存获取描述符，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       char_handle: 给定的特征句柄
 * @param[out]      result: 指向特征中描述符的指针。
 * @param[inout]    count: 输入要查找的描述符数量，它将输出在gattc缓存中找到的具有给定特征的描述符数量。
 * @param[in]       offset: 要获取的描述符位置的偏移量。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_all_descr(esp_gatt_if_t gattc_if,
                                              uint16_t conn_id,
                                              uint16_t char_handle,
                                              esp_gattc_descr_elem_t *result,
                                              uint16_t *count, uint16_t offset);


/**
 * @brief           在gattc缓存中查找具有给定特征uuid的特征注意：它只从本地缓存获取特征，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       start_handle: 属性开始句柄
 * @param[in]       end_handle: 属性结束句柄
 * @param[in]       char_uuid: 特征uuid
 * @param[out]      result: 指向服务中特征的指针。
 * @param[inout]   count: 输入要查找的特征数量，它将输出在给定服务的gattc缓存中找到的特征数量。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_char_by_uuid(esp_gatt_if_t gattc_if,
                                                 uint16_t conn_id,
                                                 uint16_t start_handle,
                                                 uint16_t end_handle,
                                                 esp_bt_uuid_t char_uuid,
                                                 esp_gattc_char_elem_t *result,
                                                 uint16_t *count);

/**
 * @brief           在gattc缓存中查找具有给定特征uuid的描述符注意：它只是从本地缓存获取描述符，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       start_handle: 属性开始句柄
 * @param[in]       end_handle: 属性结束句柄
 * @param[in]       char_uuid: 特征uuid。
 * @param[in]       descr_uuid: 描述符uuid。
 * @param[out]      result: 指向给定特征中描述符的指针。
 * @param[inout]   count: 输入要查找的描述符数量，它将输出在gattc缓存中找到的具有给定特征的描述符数量。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_descr_by_uuid(esp_gatt_if_t gattc_if,
                                                  uint16_t conn_id,
                                                  uint16_t start_handle,
                                                  uint16_t end_handle,
                                                  esp_bt_uuid_t char_uuid,
                                                  esp_bt_uuid_t descr_uuid,
                                                  esp_gattc_descr_elem_t *result,
                                                  uint16_t *count);

/**
 * @brief           在gattc缓存中查找具有给定特征句柄的描述符注意：它只是从本地缓存获取描述符，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       char_handle: 特色手柄。
 * @param[in]       descr_uuid: 描述符uuid。
 * @param[out]      result: 指向给定特征中描述符的指针。
 * @param[inout]   count: 输入要查找的描述符数量，它将输出在gattc缓存中找到的具有给定特征的描述符数量。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_descr_by_char_handle(esp_gatt_if_t gattc_if,
                                                         uint16_t conn_id,
                                                         uint16_t char_handle,
                                                         esp_bt_uuid_t descr_uuid,
                                                         esp_gattc_descr_elem_t *result,
                                                         uint16_t *count);

/**
 * @brief           在gattc缓存中查找具有给定服务句柄的include服务注意：它只是从本地缓存获取include服务，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       start_handle: 属性开始句柄
 * @param[in]       end_handle: 属性结束句柄
 * @param[in]       incl_uuid: include服务uuid
 * @param[out]      result: 指向给定服务中包含服务的指针。
 * @param[inout]   count: 输入要查找的include服务的数量，它将输出给定服务在gattc缓存中找到的include service的数量。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_include_service(esp_gatt_if_t gattc_if,
                                                    uint16_t conn_id,
                                                    uint16_t start_handle,
                                                    uint16_t end_handle,
                                                    esp_bt_uuid_t *incl_uuid,
                                                    esp_gattc_incl_svc_elem_t *result,
                                                    uint16_t *count);


/**
 * @brief           在gattc缓存中查找给定服务或特性的属性计数
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       type: 属性类型。
 * @param[in]       start_handle: 属性开始句柄，如果类型为ESP_GATT_DB_DESCRIPTOR，则应忽略此参数
 * @param[in]       end_handle: 属性结束句柄，如果类型为ESP_GATT_DB_DESCRIPTOR，则应忽略此参数
 * @param[in]       char_handle: 特性句柄，当类型为ESP_GATT_DB_DESCRIPTOR时，此参数有效。如果类型不是ESP_GATT_DB_DESCRIPTOR，则应忽略此参数。
 * @param[out]      count: 输出在gattc缓存中找到的具有给定属性类型的属性数。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_attr_count(esp_gatt_if_t gattc_if,
                                               uint16_t conn_id,
                                               esp_gatt_db_attr_type_t type,
                                               uint16_t start_handle,
                                               uint16_t end_handle,
                                               uint16_t char_handle,
                                               uint16_t *count);

/**
 * @brief           调用此函数以获取GATT数据库。注意：它只从本地缓存获取属性数据库，而不会从远程设备获取。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       start_handle: 属性开始句柄
 * @param[in]       end_handle: 属性结束句柄
 * @param[in]       conn_id: 标识服务器的连接ID。
 * @param[in]       db: 将包含GATT数据库副本的输出参数。调用者负责释放它。
 * @param[in]       count: 数据库中的元素数。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_gatt_status_t esp_ble_gattc_get_db(esp_gatt_if_t gattc_if, uint16_t conn_id, uint16_t start_handle, uint16_t end_handle,
                                        esp_gattc_db_elem_t *db, uint16_t *count);

/**
 * @brief           调用此函数以读取给定特征句柄的服务特征
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       handle ：要读取的字符句柄。
 * @param[in]       auth_req ：身份验证请求类型
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_read_char (esp_gatt_if_t gattc_if,
                                   uint16_t conn_id,
                                   uint16_t handle,
                                   esp_gatt_auth_req_t auth_req);

/**
 * @brief           调用此函数以读取给定特征UUID的服务特征
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       start_handle ：属性开始句柄。
 * @param[in]       end_handle ：属性结束句柄
 * @param[in]       uuid ：将读取的属性的UUID。
 * @param[in]       auth_req ：身份验证请求类型
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_read_by_type (esp_gatt_if_t gattc_if,
                                      uint16_t conn_id,
                                      uint16_t start_handle,
                                      uint16_t end_handle,
                                      esp_bt_uuid_t *uuid,
                                      esp_gatt_auth_req_t auth_req);

/**
 * @brief           调用此函数以读取多个特征或特征描述符。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       read_multi ：指向读取的多重参数的指针。
 * @param[in]       auth_req ：身份验证请求类型
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_read_multiple(esp_gatt_if_t gattc_if,
                                      uint16_t conn_id, esp_gattc_multi_t *read_multi,
                                      esp_gatt_auth_req_t auth_req);


/**
 * @brief           调用此函数以读取特征描述符。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       handle ：要读取的描述符句柄。
 * @param[in]       auth_req ：身份验证请求类型
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_read_char_descr (esp_gatt_if_t gattc_if,
                                         uint16_t conn_id,
                                         uint16_t handle,
                                         esp_gatt_auth_req_t auth_req);


/**
 * @brief           调用此函数以写入特征值。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       handle ：要写入的特征句柄。
 * @param[in]       value_len: 要写入的值的长度。
 * @param[in]       value ：要写入的值。
 * @param[in]       write_type ：属性写入操作的类型。
 * @param[in]       auth_req ：身份验证请求。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_write_char( esp_gatt_if_t gattc_if,
                                    uint16_t conn_id,
                                    uint16_t handle,
                                    uint16_t value_len,
                                    uint8_t *value,
                                    esp_gatt_write_type_t write_type,
                                    esp_gatt_auth_req_t auth_req);


/**
 * @brief           调用此函数以写入特征描述符值。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID
 * @param[in]       handle ：描述符无法写入。
 * @param[in]       value_len: 要写入的值的长度。
 * @param[in]       value ：要写入的值。
 * @param[in]       write_type ：属性写入操作的类型。
 * @param[in]       auth_req ：身份验证请求。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_write_char_descr (esp_gatt_if_t gattc_if,
                                         uint16_t conn_id,
                                         uint16_t handle,
                                         uint16_t value_len,
                                         uint8_t *value,
                                         esp_gatt_write_type_t write_type,
                                         esp_gatt_auth_req_t auth_req);


/**
 * @brief           调用此函数以准备写入特征值。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       handle ：准备写入的特征句柄。
 * @param[in]       offset ：写入值的偏移量。
 * @param[in]       value_len: 要写入的值的长度。
 * @param[in]       value ：要写入的值。
 * @param[in]       auth_req ：身份验证请求。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_prepare_write(esp_gatt_if_t gattc_if,
                                      uint16_t conn_id,
                                      uint16_t handle,
                                      uint16_t offset,
                                      uint16_t value_len,
                                      uint8_t *value,
                                      esp_gatt_auth_req_t auth_req);


/**
 * @brief           调用此函数以准备写入特征描述符值。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       handle ：准备写入的特征描述符句柄。
 * @param[in]       offset ：写入值的偏移量。
 * @param[in]       value_len: 要写入的值的长度。
 * @param[in]       value ：要写入的值。
 * @param[in]       auth_req ：身份验证请求。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_prepare_write_char_descr(esp_gatt_if_t gattc_if,
                                                 uint16_t conn_id,
                                                 uint16_t handle,
                                                 uint16_t offset,
                                                 uint16_t value_len,
                                                 uint8_t *value,
                                                 esp_gatt_auth_req_t auth_req);


/**
 * @brief           调用此函数以执行写入准备写入序列。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       conn_id ：连接ID。
 * @param[in]       is_execute ：执行或取消。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_execute_write (esp_gatt_if_t gattc_if, uint16_t conn_id, bool is_execute);


/**
 * @brief           调用此函数以注册服务通知。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       server_bda ：目标GATT服务器。
 * @param[in]       handle ：GATT特征手柄。
 *
 * @return
 *                  -ESP_OK：注册成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_register_for_notify (esp_gatt_if_t gattc_if,
                                             esp_bd_addr_t server_bda,
                                             uint16_t handle);


/**
 * @brief           调用此函数以取消注册服务通知。
 *
 * @param[in]       gattc_if: Gatt客户端访问接口。
 * @param[in]       server_bda ：目标GATT服务器。
 * @param[in]       handle ：GATT特征手柄。
 *
 * @return
 *                  -ESP_OK:注销成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gattc_unregister_for_notify (esp_gatt_if_t gattc_if,
                                               esp_bd_addr_t server_bda,
                                               uint16_t handle);


/**
* @brief           刷新远程设备gattc堆栈中的服务器缓存存储。如果设备已连接，此API将重新启动远程设备服务信息的发现
*
* @param[in]       remote_bda: 远程设备BD地址。
*
* @return
*                  -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_gattc_cache_refresh(esp_bd_addr_t remote_bda);

/**
* @brief           添加或删除与源地址关联的地址。注意：此API的作用主要是当客户端存储了服务器端数据库时，当它需要连接另一个设备时，但设备的属性数据库与客户端上存储的服务器数据库相同，调用该API可以使用设备存储的数据库作为对等服务器数据库，以减少属性数据库搜索和发现过程并加快连接时间。设备要使用数据库的相关地址干线已存储在本地缓存中。设备希望将数据库共享给相关地址设备的源地址干线。
*
* @param[in]       gattc_if: Gatt客户端访问接口。
* @param[in]       src_addr: 提供属性表的源地址。
* @param[in]       assoc_addr: 与源地址共享属性表的相关设备地址。
* @param[in]       is_assoc: true添加相关设备地址，false删除相关设备地址。
* @return
*                  -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_gattc_cache_assoc(esp_gatt_if_t gattc_if, esp_bd_addr_t src_addr,
                                      esp_bd_addr_t assoc_addr, bool is_assoc);
/**
* @brief           获取在gattc缓存中存储属性表的地址列表。获取地址列表完成后，将回调ESP_GATTC_GET_ADDR_LIST_EVT事件。
*
* @param[in]       gattc_if: Gatt客户端访问接口。
* @return
*                  -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_gattc_cache_get_addr_list(esp_gatt_if_t gattc_if);

/**
* @brief           清理gattc堆栈中此设备的服务缓存，
*
* @param[in]       remote_bda: 远程设备BD地址。
*
* @return
*                  -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_gattc_cache_clean(esp_bd_addr_t remote_bda);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_GATTC_API_H__ */

