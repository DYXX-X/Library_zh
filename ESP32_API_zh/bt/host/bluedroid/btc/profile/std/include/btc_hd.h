/******************************************************************************
 * Copyright（C）2016 Android开源项目版权所有（C）2009-2012 Broadcom Corporation版权所有（B）2019 Blake Felt
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef BTC_HD_H
#define BTC_HD_H

#if BTC_HD_INCLUDED == TRUE

#include <stdint.h>
#include "bta/bta_hd_api.h"
#include "btc/btc_task.h"
#include "esp_hidd_api.h"

typedef enum {
    BTC_HD_INIT_EVT = 0,
    BTC_HD_DEINIT_EVT,
    BTC_HD_REGISTER_APP_EVT,
    BTC_HD_UNREGISTER_APP_EVT,
    BTC_HD_CONNECT_EVT,
    BTC_HD_DISCONNECT_EVT,
    BTC_HD_SEND_REPORT_EVT,
    BTC_HD_REPORT_ERROR_EVT,
    BTC_HD_UNPLUG_EVT,
} BTC_HD_EVT;

typedef enum { BTC_HD_DISABLED = 0, BTC_HD_ENABLED, BTC_HD_DISABLING } BTC_HD_STATUS;

/* BTIF-HD控制块*/
typedef struct {
    BTC_HD_STATUS status;
    bool app_registered;
    bool service_dereg_active;
    bool forced_disc;
    tBTA_HD_APP_INFO app_info;
    tBTA_HD_QOS_INFO in_qos;
    tBTA_HD_QOS_INFO out_qos;
} btc_hd_cb_t;

/* btc_hidd_args_t*/
typedef union {
    // BTC_HD_CONNECT_EVT
    struct connect_arg {
        BD_ADDR bd_addr;
    } connect;

    // BTC_HD_REGISTER_APP_EVT
    struct register_app_arg {
        esp_hidd_app_param_t *app_param;
        esp_hidd_qos_param_t *in_qos;
        esp_hidd_qos_param_t *out_qos;
    } register_app;

    // BTC_HD_SEND_REPORT_EVT
    struct send_report_arg {
        esp_hidd_report_type_t type;
        uint8_t id;
        uint16_t len;
        uint8_t *data;
    } send_report;

    // BTC_HD_REPORT_ERROR_EVT
    uint8_t error;
} btc_hidd_args_t;

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * 功能
 ******************************************************************************/
void btc_hd_call_handler(btc_msg_t *msg);

void btc_hd_cb_handler(btc_msg_t *msg);

// 外部btc_hd_cb_t btc_hd_cb；
// 外部无效btc_hd_remove_device（bt_bdaddr_t bd_addr）；
// 外部无效btc_hd_service_registration（）；

void btc_hd_arg_deep_copy(btc_msg_t *msg, void *p_dest, void *p_src);

#ifdef __cplusplus
}
#endif

#endif /* BTC_HD_INCLUDED == TRUE */
#endif /* BTC_HD_H */

