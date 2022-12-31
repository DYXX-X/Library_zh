/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


/*******************************************************************************
 * 文件名：btc_av.h
 *
 *  描述：从内部堆栈访问的所有BTC AV函数的主API头文件。
 *
 *******************************************************************************/

#ifndef __BTC_AV_H__
#define __BTC_AV_H__

#include "common/bt_target.h"
#include "esp_a2dp_api.h"
#include "btc/btc_task.h"
#include "btc/btc_common.h"
#include "btc/btc_sm.h"
#include "bta/bta_av_api.h"

#if (BTC_AV_INCLUDED == TRUE)

// inidcate avrc的全局变量用a2dp初始化
extern bool g_av_with_rc;
// 用于指示a2dp已初始化的全局变量
extern bool g_a2dp_on_init;
// 用于指示a2dp未初始化的全局变量
extern bool g_a2dp_on_deinit;
// 全局变量，用于指示a2dp源去初始化正在进行
extern bool g_a2dp_source_ongoing_deinit;
// 全局变量，用于指示a2dp接收器去初始化正在进行
extern bool g_a2dp_sink_ongoing_deinit;

/*******************************************************************************
**  回调函数的类型定义
********************************************************************************/

enum {
    BTC_AV_DATAPATH_OPEN_EVT, // bluedroid中数据通道的原始UIPC_OPEN_EVT
    BTC_AV_DATAPATH_MAX_EVT,
};

typedef enum {
    BTC_AV_CONNECT_REQ_EVT = BTA_AV_MAX_EVT,
    BTC_AV_DISCONNECT_REQ_EVT,
    BTC_AV_START_STREAM_REQ_EVT,
    BTC_AV_STOP_STREAM_REQ_EVT,
    BTC_AV_SUSPEND_STREAM_REQ_EVT,
    BTC_AV_SINK_CONFIG_REQ_EVT,
} btc_av_sm_event_t;

typedef enum {
#if BTC_AV_SINK_INCLUDED
    BTC_AV_SINK_API_INIT_EVT = 0,
    BTC_AV_SINK_API_DEINIT_EVT,
    BTC_AV_SINK_API_CONNECT_EVT,
    BTC_AV_SINK_API_DISCONNECT_EVT,
    BTC_AV_SINK_API_REG_DATA_CB_EVT,
#endif  /* BTC_AV_SINK_INCLUDED */
#if BTC_AV_SRC_INCLUDED
    BTC_AV_SRC_API_INIT_EVT,
    BTC_AV_SRC_API_DEINIT_EVT,
    BTC_AV_SRC_API_CONNECT_EVT,
    BTC_AV_SRC_API_DISCONNECT_EVT,
    BTC_AV_SRC_API_REG_DATA_CB_EVT,
#endif  /* BTC_AV_SRC_INCLUDED */
    BTC_AV_API_MEDIA_CTRL_EVT,
} btc_av_act_t;

/* btc_av_args_t*/
typedef union {
#if BTC_AV_SINK_INCLUDED
    // BTC_AV_SINK_CONFIG_REQ_EVT—内部事件
    esp_a2d_mcc_t mcc;
    // BTC_AV_SINK_API_CONNECT_EVT
    bt_bdaddr_t connect;
    // BTC_AV_SINK_API_DISCONNECT_EVT
    bt_bdaddr_t disconn;
    // BTC_AV_SINK_API_REG_DATA_CB_EVT
    esp_a2d_sink_data_cb_t data_cb;
#endif  /* BTC_AV_SINK_INCLUDED */
#if BTC_AV_SRC_INCLUDED
    // BTC_AV_SRC_API_REG_DATA_CB_EVT
    esp_a2d_source_data_cb_t src_data_cb;
    // BTC_AV_SRC_API_CONNECT
    bt_bdaddr_t src_connect;
    // BTC_AV_SRC_API_DISCONNECT_EVT
    bt_bdaddr_t src_disconn;
#endif /* BTC_AV_SRC_INCLUDED */
    // BTC_AV_API_MEDIA_CTRL_EVT
    esp_a2d_media_ctrl_t ctrl;
} btc_av_args_t;

/*******************************************************************************
**  BTC AV API
********************************************************************************/

void btc_a2dp_call_handler(btc_msg_t *msg);

void btc_a2dp_cb_handler(btc_msg_t *msg);

void btc_a2dp_sink_reg_data_cb(esp_a2d_sink_data_cb_t callback);

void btc_a2dp_src_reg_data_cb(esp_a2d_source_data_cb_t callback);
/*******************************************************************************
** 函数btc_av_get_sm_handle
**
** 说明获取当前av SM句柄
**
** 返回None
**
*******************************************************************************/

btc_sm_handle_t btc_av_get_sm_handle(void);

/*******************************************************************************
** 函数btc_av_stream_ready
**
** 说明检查AV是否准备好启动流
**
** 返回None
**
*******************************************************************************/

BOOLEAN btc_av_stream_ready(void);

/*******************************************************************************
** 函数btc_av_stream_started_ready
**
** 说明检查AV是否准备好以流媒体状态启动媒体
**
** 返回None
**
*******************************************************************************/

BOOLEAN btc_av_stream_started_ready(void);

/*******************************************************************************
** 函数btc_dispatch_sm_event
**
** 说明向AV状态机发送事件
**
** 返回None
**
*******************************************************************************/

/* 用于将事件从其他任务传递到AV状态机*/
void btc_dispatch_sm_event(btc_av_sm_event_t event, void *p_data, int len);

/*******************************************************************************
** 函数btc_av_is_connected
**
** 说明检查av是否有连接的接收器
**
** 返回BOOLEAN
**
*******************************************************************************/

BOOLEAN btc_av_is_connected(void);


/*******************************************************************************
 * 函数btc_av_get_peer_sep
 *
 * 描述获取流终结点类型。
 *
 * 返回流端点类型：AVDT_TSEP_SRC或AVDT_TEP_SNK。
 *
 ******************************************************************************/

uint8_t btc_av_get_peer_sep(void);

/*******************************************************************************
** 函数btc_av_is_peer_edr
**
** 说明检查连接的a2dp设备是否支持EDR。只有在连接时，此功能才能准确地提供远程对等方的真正功能。如果未连接，则始终为假。
**
** 如果远程设备能够进行EDR，则返回TRUE
**
*******************************************************************************/

BOOLEAN btc_av_is_peer_edr(void);

/******************************************************************************
** 函数btc_av_clear_remote_suspend_flag
**
** 说明清除远程挂起标志
**
** 退货作废
********************************************************************************/
void btc_av_clear_remote_suspend_flag(void);

/*******************************************************************************
 * 函数btc_av_get_service_id
 *
 * 说明获取当前AV服务ID。
 *
 * 返回流端点类型：BTA_A2DP_SOURCE_SERVICE_ID或BTA_A2DPI_SINK_SERVICE-ID。
 *
 ******************************************************************************/
uint8_t btc_av_get_service_id(void);

#endif  ///BTC_AV_INCLUDED == TRUE

#endif /* __BTC_AV_H__ */

