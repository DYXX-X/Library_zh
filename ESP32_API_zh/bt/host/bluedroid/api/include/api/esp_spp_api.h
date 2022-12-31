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

#ifndef __ESP_SPP_API_H__
#define __ESP_SPP_API_H__

#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_SPP_SUCCESS   = 0,          /*!< 操作成功。*/
    ESP_SPP_FAILURE,                /*!< 一般故障。*/
    ESP_SPP_BUSY,                   /*!< 暂时无法处理此请求。*/
    ESP_SPP_NO_DATA,                /*!< 无数据*/
    ESP_SPP_NO_RESOURCE,            /*!< 没有更多资源*/
    ESP_SPP_NEED_INIT,              /*!< SPP模块应首先初始化*/
    ESP_SPP_NEED_DEINIT,            /*!< SPP模块应首先卸载*/
    ESP_SPP_NO_CONNECTION,          /*!< 连接可能已关闭*/
    ESP_SPP_NO_SERVER,              /*!< 无SPP服务器*/
} esp_spp_status_t;

/* 安全设置掩码使用以下三种掩码模式：1.ESP_SPP_SEC_NONE 2.ESP_SPP_SEC_AUTHENTICATE 3
*/
#define ESP_SPP_SEC_NONE            0x0000    /*!< 没有安全性。与BTA/BTA_api.h中的BTA_SEC_NONE相关*/
#define ESP_SPP_SEC_AUTHORIZE       0x0001    /*!< 所需授权（仅用于外出连接）与BTA/BTA_api.h中的BTA_SEC_AUTHORIZE相关*/
#define ESP_SPP_SEC_AUTHENTICATE    0x0012    /*!< 需要身份验证。与BTA/BTA_api.h中的BTA_SEC_AUTHENTICATE相关*/
#define ESP_SPP_SEC_ENCRYPT         0x0024    /*!< 需要加密。与BTA/BTA_api.h中的BTA_SEC_ENCRYPT相关*/
#define ESP_SPP_SEC_MODE4_LEVEL4    0x0040    /*!< 模式4级别4服务，即传入/传出MITM和P-256加密与BTA/BTA_api.h中的BTA_SEC_MODE4_LEVEL4相关*/
#define ESP_SPP_SEC_MITM            0x3000    /*!< Man-In-The_Middle保护与BTA/BTA_api.h中的BTA_SEC_MITM相关*/
#define ESP_SPP_SEC_IN_16_DIGITS    0x4000    /*!< 引脚代码的最小16位数字与BTA/BTA_api.h中的BTA_SEC_IN_16_DIGITS相关*/
typedef uint16_t esp_spp_sec_t;

typedef enum {
    ESP_SPP_ROLE_MASTER     = 0,          /*!< 角色：master*/
    ESP_SPP_ROLE_SLAVE      = 1,          /*!< 角色：从属*/
} esp_spp_role_t;

typedef enum {
    ESP_SPP_MODE_CB         = 0,          /*!< 当数据到来时，回调将随数据一起到来*/
    ESP_SPP_MODE_VFS        = 1,          /*!< 使用VFS写入/读取数据*/
} esp_spp_mode_t;

#define ESP_SPP_MAX_MTU                 (3*330)     /*!< SPP最大MTU*/
#define ESP_SPP_MAX_SCN                 31          /*!< SPP最大SCN*/
/**
 * @brief SPP回调函数事件
 */
typedef enum {
    ESP_SPP_INIT_EVT                    = 0,                /*!< 启动SPP后，事件发生*/
    ESP_SPP_UNINIT_EVT                  = 1,                /*!< 当SPP未经批准时，事件发生*/
    ESP_SPP_DISCOVERY_COMP_EVT          = 8,                /*!< SDP发现完成后，事件发生*/
    ESP_SPP_OPEN_EVT                    = 26,               /*!< 当SPP客户端连接打开时，事件发生*/
    ESP_SPP_CLOSE_EVT                   = 27,               /*!< 当SPP连接关闭时，事件发生*/
    ESP_SPP_START_EVT                   = 28,               /*!< SPP服务器启动时，事件发生*/
    ESP_SPP_CL_INIT_EVT                 = 29,               /*!< 当SPP客户端启动连接时，事件发生*/
    ESP_SPP_DATA_IND_EVT                = 30,               /*!< 当SPP连接接收到数据时，事件发生，仅适用于ESP_SPP_MODE_CB*/
    ESP_SPP_CONG_EVT                    = 31,               /*!< 当SPP连接拥塞状态更改时，事件发生，仅适用于ESP_SPP_MODE_CB*/
    ESP_SPP_WRITE_EVT                   = 33,               /*!< SPP写入操作完成后，事件发生，仅适用于ESP_SPP_MODE_CB*/
    ESP_SPP_SRV_OPEN_EVT                = 34,               /*!< 当SPP服务器连接打开时，事件发生*/
    ESP_SPP_SRV_STOP_EVT                = 35,               /*!< SPP服务器停止时，事件发生*/
} esp_spp_cb_event_t;


/**
 * @brief SPP回调参数联合
 */
typedef union {
    /**
     * @brief SPP_INIT_EVT
     */
    struct spp_init_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
    } init;                                 /*!< SPP_INIT_EVT的SPP回调参数*/

    /**
     * @brief SPP_UNINIT_EVT
     */
    struct spp_uninit_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
    } uninit;                               /*!< SPP_UNINIT_EVT的SPP回调参数*/

    /**
     * @brief SPP_DISCOVERY_COMP_EVT
     */
    struct spp_discovery_comp_evt_param {
        esp_spp_status_t status;                   /*!< 地位*/
        uint8_t scn_num;                           /*!< scn_num的num*/
        uint8_t scn[ESP_SPP_MAX_SCN];              /*!< 通道#*/
        const char *service_name[ESP_SPP_MAX_SCN]; /*!< 服务名称*/
    } disc_comp;                            /*!< SPP_DISCOVERY_COMP_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_OPEN_EVT
     */
    struct spp_open_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        int                 fd;             /*!< 仅用于ESP_SPP_MODE_VFS的文件描述符*/
        esp_bd_addr_t       rem_bda;        /*!< 对等地址*/
    } open;                                 /*!< ESP_SPP_OPEN_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_SRV_OPEN_EVT
     */
    struct spp_srv_open_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        uint32_t            new_listen_handle;  /*!< 新的侦听句柄*/
        int                 fd;             /*!< 仅用于ESP_SPP_MODE_VFS的文件描述符*/
        esp_bd_addr_t       rem_bda;        /*!< 对等地址*/
    } srv_open;                             /*!< ESP_SPP_SRV_OPEN_EVT的SPP回调参数*/
    /**
     * @brief ESP_SPP_CLOSE_EVT
     */
    struct spp_close_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            port_status;    /*!< PORT状态*/
        uint32_t            handle;         /*!< 连接手柄*/
        bool                async;          /*!< 如果本地启动断开连接，则返回FALSE*/
    } close;                                /*!< ESP_SPP_CLOSE_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_START_EVT
     */
    struct spp_start_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        uint8_t             sec_id;         /*!< 此服务器使用的安全ID*/
        uint8_t             scn;            /*!< 服务器通道号*/
        bool                use_co;         /*!< TRUE使用corfc_data*/
    } start;                                /*!< ESP_SPP_START_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_SRV_STOP_EVT
     */
    struct spp_srv_stop_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint8_t             scn;            /*!< 服务器通道号*/
    } srv_stop;                             /*!< ESP_SPP_SRV_STOP_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_CL_INIT_EVT
     */
    struct spp_cl_init_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        uint8_t             sec_id;         /*!< 此服务器使用的安全ID*/
        bool                use_co;         /*!< TRUE使用corfc_data*/
    } cl_init;                              /*!< ESP_SPP_CL_INIT_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_WRITE_EVT
     */
    struct spp_write_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        int                 len;            /*!< 写入数据的长度。*/
        bool                cong;           /*!< 拥挤状态*/
    } write;                                /*!< ESP_SPP_WRITE_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_DATA_IND_EVT
     */
    struct spp_data_ind_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        uint16_t            len;            /*!< 数据的长度*/
        uint8_t             *data;          /*!< 收到的数据*/
    } data_ind;                             /*!< ESP_SPP_DATA_IND_EVT的SPP回调参数*/

    /**
     * @brief ESP_SPP_CONG_EVT
     */
    struct spp_cong_evt_param {
        esp_spp_status_t    status;         /*!< 地位*/
        uint32_t            handle;         /*!< 连接手柄*/
        bool                cong;           /*!< 真的，拥挤。FALSE，未消化*/
    } cong;                                 /*!< ESP_SPP_CONG_EVT的SPP回调参数*/
} esp_spp_cb_param_t;                       /*!< SPP回调参数联合类型*/

/**
 * @brief       SPP回调函数类型。在处理ESP_SPP_DATA_IND_EVT时，强烈建议缓存传入数据，并在其他较低优先级的应用程序任务中处理它们，而不是直接在回调中处理。
 *
 * @param       event:      事件类型
 * @param       param:      指向回调参数，当前为联合类型
 */
typedef void (esp_spp_cb_t)(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);

/**
 * @brief       调用此函数以初始化SPP模块的回调。
 *
 * @param[in]   callback:   指向init回调函数的指针。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_register_callback(esp_spp_cb_t callback);

/**
 * @brief       调用此函数以初始化SPP模块。操作完成后，将使用ESP_SPP_INIT_EVT调用回调函数。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 * @param[in]   mode: 选择SPP、ESP_SPP_mode_CB或ESP_SPP_mode_VFS模式。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_init(esp_spp_mode_t mode);

/**
 * @brief       调用此函数以取消SPP模块的初始化。该操作将首先关闭所有活动的SPP连接，然后使用ESP_SPP_close_EVT调用回调函数，并且ESP_SPP-close_EFT的数量等于连接的数量。操作完成后，将使用ESP_SPP_UNINIT_VT调用回调函数。应在esp_spp_init（）成功完成后调用此函数。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_deinit(void);


/**
 * @brief       调用此函数以对给定对等设备提供的服务执行服务发现。操作完成后，将使用ESP_SPP_DISCOVERY_COMP_EVT调用回调函数。必须在esp_spp_init（）成功之后和esp_spp_deinit（）之前调用此函数。
 *
 * @param[in]   bd_addr:   远程设备蓝牙设备地址。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_start_discovery(esp_bd_addr_t bd_addr);

/**
 * @brief       此功能将SPP连接到远程BD地址。当连接启动或未能启动时，将使用ESP_SPP_CL_INIT_EVT调用回调。当连接建立或失败时，将使用ESP_SPP_OPEN_EVT调用回调。必须在esp_spp_init（）成功之后和esp_spp_deinit（）之前调用此函数。
 *
 * @param[in]   sec_mask:     安全设置掩码。建议仅使用ESP_SPP_SEC_NONE、ESP_SPP_SC_AUTHIZE或ESP_SPP_SEC_AUTHENTICATE。
 * @param[in]   role:         主或从。
 * @param[in]   remote_scn:   远程设备蓝牙设备SCN。
 * @param[in]   peer_bd_addr: 远程设备蓝牙设备地址。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_connect(esp_spp_sec_t sec_mask, esp_spp_role_t role, uint8_t remote_scn, esp_bd_addr_t peer_bd_addr);

/**
 * @brief       此功能关闭SPP连接。操作完成后，将使用ESP_SPP_CLOSE_EVT调用回调函数。必须在esp_spp_init（）成功之后和esp_spp_deinit（）之前调用此函数。
 *
 * @param[in]   handle:    连接手柄。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_disconnect(uint32_t handle);

/**
 * @brief       此功能创建SPP服务器，并开始侦听来自远程蓝牙设备的SPP连接请求。成功启动服务器后，将使用ESP_SPP_START_EVT调用回调。建立连接后，使用ESP_SPP_SRV_OPEN_EVT调用回调。必须在esp_spp_init（）成功之后和esp_spp_deinit（）之前调用此函数。
 *
 * @param[in]   sec_mask:     安全设置掩码。建议仅使用ESP_SPP_SEC_NONE、ESP_SPP_SC_AUTHIZE或ESP_SPP_SEC_AUTHENTICATE。
 * @param[in]   role:         主或从。
 * @param[in]   local_scn:    要获取的特定频道。如果通道为0，表示获取任何通道。
 * @param[in]   name:         服务器的名称。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_start_srv(esp_spp_sec_t sec_mask, esp_spp_role_t role, uint8_t local_scn, const char *name);

/**
 * @brief       此功能可停止所有SPP服务器。该操作将首先关闭所有活动的SPP连接，然后使用ESP_SPP_close_EVT调用回调函数，并且ESP_SPP-close_EFT的数量等于连接的数量。操作完成后，将使用ESP_SPP_SRV_STOP_EVT调用回调。必须在esp_spp_init（）成功之后和esp_spp_deinit（）之前调用此函数。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */

esp_err_t esp_spp_stop_srv(void);

/**
 * @brief       此函数用于停止特定SPP服务器。该操作将首先关闭特定SPP服务器上的所有活动SPP连接，然后使用ESP_SPP_close_EVT调用回调函数，并且ESP_SPP-close_EFT的数量等于连接的数量。操作完成后，将使用ESP_SPP_SRV_STOP_EVT调用回调。必须在esp_spp_init（）成功之后和esp_spp_deinit（）之前调用此函数。
 *
 * @param[in]   scn:         服务器频道号。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_stop_srv_scn(uint8_t scn);

/**
 * @brief       此函数用于写入数据，仅适用于ESP_SPP_MODE_CB。当需要重复调用此函数时，强烈建议在收到上一事件ESP_SPP_WRITE_EVT且参数“cong”等于false后再次调用此函数。如果参数为“cong”的上一事件ESP_SPP_WRITE_EVT等于真，则只有在收到参数为“cong”的事件ESP_SPP _cong_EVT等于假时，才能再次调用该函数。必须在发起方和受体之间建立连接后调用此函数。
 *
 * @param[in]   handle: 连接手柄。
 * @param[in]   len:    写入数据的长度。
 * @param[in]   p_data: 写入的数据。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_write(uint32_t handle, int len, uint8_t *p_data);


/**
 * @brief       此函数用于注册VFS。目前，SPP仅支持写入、读取和关闭。
 *
 * @return
 *              -ESP_OK：成功
 *              -其他：失败
 */
esp_err_t esp_spp_vfs_register(void);

#ifdef __cplusplus
}
#endif

#endif ///__ESP_SPP_API_H__

