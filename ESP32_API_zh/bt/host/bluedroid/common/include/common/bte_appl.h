/******************************************************************************
 * 版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是bte应用程序任务的接口文件
 *
 ******************************************************************************/

#pragma once

typedef struct {
#if ((BLE_INCLUDED == TRUE) && (SMP_INCLUDED == TRUE))
    UINT8   ble_auth_req;
    UINT8   ble_io_cap;
    UINT8   ble_init_key;
    UINT8   ble_resp_key;
    UINT8   ble_max_key_size;
    UINT8   ble_min_key_size;
    UINT8   ble_accept_auth_enable;
    UINT8   oob_support;
    UINT8   ble_appl_enc_key_size;
#endif

} tBTE_APPL_CFG;

extern tBTE_APPL_CFG bte_appl_cfg;


typedef struct {
#if ((CLASSIC_BT_INCLUDED == TRUE) && (BT_SSP_INCLUDED == TRUE))
    UINT8   bt_auth_req;
    UINT8   bt_io_cap;
    UINT8   *bt_oob_auth_data;
#endif
} tBTE_BT_APPL_CFG;

extern tBTE_BT_APPL_CFG bte_bt_appl_cfg;

