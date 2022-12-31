/******************************************************************************
 * 版权所有（C）2006-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是设备管理器调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_DM_CO_H
#define BTA_DM_CO_H

#include "bta/bta_sys.h"
#include "esp_err.h"

/*****************************************************************************
**  函数声明
*****************************************************************************/

/*******************************************************************************
** 函数bta_dm_co_bt_set_io_cap
**
** 说明此功能用于设置IO功能
**
** 参数bt_io_cap-io功能
**
** @return          -ESP_BT_STATUS_SUCCESS：成功
**                  -其他：失败
**
*******************************************************************************/
extern esp_err_t bta_dm_co_bt_set_io_cap(UINT8 bt_io_cap);

/*******************************************************************************
** 函数bta_dm_co_io_req
**
** 说明此调出功能由DM执行，以获取简单配对过程中本地设备的IO功能
**
** 参数bd_addr-对等设备p_io_cap-本地输入/输出功能p_oob_data-TRUE，如果oob数据可用于对等设备。p_auth_req-如果需要MITM保护，则为TRUE。
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_io_req(BD_ADDR bd_addr, tBTA_IO_CAP *p_io_cap,
                             tBTA_OOB_DATA *p_oob_data, tBTA_AUTH_REQ *p_auth_req,
                             BOOLEAN is_orig);

/*******************************************************************************
** 函数bta_dm_co_io_rsp
**
** 说明此调出功能由DM执行，以报告简单配对过程中对等设备的IO能力
**
** 参数bd_addr-对等设备io_cap-远程输入/输出功能oob_data-TRUE，如果oob数据可用于对等设备。auth_req-TRUE，如果需要MITM保护。
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_io_rsp(BD_ADDR bd_addr, tBTA_IO_CAP io_cap,
                             tBTA_OOB_DATA oob_data, tBTA_AUTH_REQ auth_req);

/*******************************************************************************
** 函数bta_dm_co_lk_upgrade
**
** 说明此调出功能由DM执行，以检查平台是否允许链接密钥升级
**
** 参数bd_addr-对等设备p_upgrade-TRUE，如果需要链接密钥升级。
**
** 返回void。
**
*******************************************************************************/
extern void  bta_dm_co_lk_upgrade(BD_ADDR bd_addr, BOOLEAN *p_upgrade );

/*******************************************************************************
** 函数bta_dm_c_loc_oob
**
** 说明此调出功能由DM执行，以报告简单配对过程中本地设备的OOB数据
**
** 参数有效-TRUE，如果从LM c-简单配对哈希c r-简单配对随机数器r检索到本地OOB数据
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_loc_oob(BOOLEAN valid, BT_OCTET16 c, BT_OCTET16 r);

/*******************************************************************************
** 函数bta_dm_co_rmt_oob
**
** 说明此调出功能由DM执行，以请求简单配对过程中远程设备的OOB数据
**
** 参数bd_addr-对等设备
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_rmt_oob(BD_ADDR bd_addr);


/*******************************************************************************
** 函数bta_dm_co_ble_io_req
**
** 说明此调出功能由DM执行，以在SMP配对开始之前获得BLE IO功能。
**
** 参数bd_addr-对等设备p_io_cap-本地输入/输出功能p_oob_data-TRUE，如果oob数据可用于对等设备。p_auth_req-身份验证请求设置（是否需要绑定和MITM）p_max_key_size-支持的最大密钥大小本地设备。p_init_key-启动器密钥。p_resp_key-响应者密钥。
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_ble_io_req(BD_ADDR bd_addr,  tBTA_IO_CAP *p_io_cap,
                                 tBTA_OOB_DATA *p_oob_data,
                                 tBTA_LE_AUTH_REQ *p_auth_req,
                                 UINT8 *p_max_key_size,
                                 tBTA_LE_KEY_TYPE *p_init_key,
                                 tBTA_LE_KEY_TYPE  *p_resp_key );


/*******************************************************************************
** 函数bta_dm_co_ble_local_key_reload
**
** 说明此调出功能用于加载设备上可用的本地BLE键。
**
** 参数无
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_ble_load_local_keys (tBTA_DM_BLE_LOCAL_KEY_MASK *p_key_mask, BT_OCTET16 er,
        tBTA_BLE_LOCAL_ID_KEYS *p_id_keys);

// btla特定++
/*******************************************************************************
** 函数bta_dm_co_ble_io_req
**
** 说明此调出功能由DM执行，以在SMP配对开始之前获得BLE IO功能。
**
** 参数bd_addr-对等设备p_io_cap-本地输入/输出功能p_oob_data-TRUE，如果oob数据可用于对等设备。p_auth_req-身份验证请求设置（是否需要绑定和MITM）p_max_key_size-支持的最大密钥大小本地设备。p_init_key-启动器密钥。p_resp_key-响应者密钥。
**
** 返回void。
**
*******************************************************************************/
extern void bta_dm_co_ble_io_req(BD_ADDR bd_addr,  tBTA_IO_CAP *p_io_cap,
                                 tBTA_OOB_DATA *p_oob_data,
                                 tBTA_LE_AUTH_REQ *p_auth_req,
                                 UINT8 *p_max_key_size,
                                 tBTA_LE_KEY_TYPE *p_init_key,
                                 tBTA_LE_KEY_TYPE  *p_resp_key );
// btla特定--

extern void bta_dm_co_ble_set_io_cap(UINT8 ble_io_cap);

extern void bta_dm_co_ble_set_auth_req(UINT8 ble_auth_req);

extern void bta_dm_co_ble_set_init_key_req(UINT8 init_key);

extern void bta_dm_co_ble_set_rsp_key_req(UINT8 rsp_key);

extern void bta_dm_co_ble_set_max_key_size(UINT8 ble_key_size);

extern void bta_dm_co_ble_set_min_key_size(UINT8 ble_key_size);

extern void bta_dm_co_ble_set_accept_auth_enable(UINT8 enable);

extern UINT8 bta_dm_co_ble_get_accept_auth_enable(void);

extern UINT8 bta_dm_co_ble_get_auth_req(void);

extern void bta_dm_co_ble_oob_support(UINT8 enable);

extern void bta_dm_co_ble_set_appl_enc_key_size(UINT8 ble_key_size);
#endif

