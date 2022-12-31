/******************************************************************************
 * Copyright（C）2016 Android开源项目版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef BTA_HD_API_H
#define BTA_HD_API_H

#include "bta_api.h"
#include "stack/hidd_api.h"

#if BTA_HD_INCLUDED == TRUE

/*****************************************************************************
 *  常量和类型定义
 ****************************************************************************/

#ifndef BTA_HD_DEBUG
#define BTA_HD_DEBUG TRUE
#endif

/* BTA HID设备回调事件*/
#define BTA_HD_ENABLE_EVT 0         /* BT-HD已启用*/
#define BTA_HD_DISABLE_EVT 1        /* BT-HD已禁用*/
#define BTA_HD_REGISTER_APP_EVT 2   /* 申请已注册*/
#define BTA_HD_UNREGISTER_APP_EVT 3 /* 应用程序未注册*/
#define BTA_HD_OPEN_EVT 4           /* 与主机的连接已打开*/
#define BTA_HD_CLOSE_EVT 5          /* 与主机的连接已关闭*/
#define BTA_HD_GET_REPORT_EVT 6     /* 来自主机的GET_REPORT请求*/
#define BTA_HD_SET_REPORT_EVT 7     /* 来自主机的SET_REPORT请求*/
#define BTA_HD_SET_PROTOCOL_EVT 8   /* 来自主机的SET_PROTOCOL请求*/
#define BTA_HD_INTR_DATA_EVT 9      /* 在intr上从主机接收到数据*/
#define BTA_HD_VC_UNPLUG_EVT 10     /* 虚拟电缆拔出*/
// #define BTA_HD_CONN_STATE_EVT 11    /* 报告连接状态更改*/
#define BTA_HD_SEND_REPORT_EVT 12     /* 发送报告完成*/
#define BTA_HD_REPORT_ERR_EVT 13     /* 报告握手结束*/
#define BTA_HD_API_ERR_EVT 99       /* BT-HD API错误*/

typedef uint16_t tBTA_HD_EVT;

enum { BTA_HD_OK, BTA_HD_ERROR };

typedef enum {
    BTA_HD_CONN_STATE_CONNECTED,
    BTA_HD_CONN_STATE_CONNECTING,
    BTA_HD_CONN_STATE_DISCONNECTED,
    BTA_HD_CONN_STATE_DISCONNECTING,
    BTA_HD_CONN_STATE_UNKNOWN
} tBTA_HD_CONN_STAT;

typedef uint8_t tBTA_HD_STATUS;
typedef tHID_DEV_DSCP_INFO tBTA_HD_DEV_DESCR;

typedef struct {
    char *p_name;
    char *p_description;
    char *p_provider;
    uint8_t subclass;
    tBTA_HD_DEV_DESCR descriptor;
} tBTA_HD_APP_INFO;

typedef struct {
    uint8_t service_type;
    uint32_t token_rate;
    uint32_t token_bucket_size;
    uint32_t peak_bandwidth;
    uint32_t access_latency;
    uint32_t delay_variation;
} tBTA_HD_QOS_INFO;

typedef struct {
    bool use_intr;
    uint8_t type;
    uint8_t id;
    uint16_t len;
    uint8_t *p_data;
} tBTA_HD_REPORT;

typedef struct {
    tBTA_HD_STATUS status;
    bool in_use;
    BD_ADDR bda;
} tBTA_HD_REG_STATUS;

typedef struct {
    BD_ADDR bda;
    tBTA_HD_STATUS status;
    tBTA_HD_CONN_STAT conn_status;
} tBTA_HD_CONN;

typedef struct {
    uint8_t report_type;
    uint8_t report_id;
    uint16_t buffer_size;
} tBTA_HD_GET_REPORT;

typedef struct {
    uint8_t report_type;
    uint8_t report_id;
    uint16_t len;
    uint8_t *p_data;
} tBTA_HD_SET_REPORT;

typedef uint8_t tBTA_HD_SET_PROTOCOL;

typedef struct {
    uint8_t report_id;
    uint16_t len;
    uint8_t *p_data;
} tBTA_HD_INTR_DATA;

typedef struct {
    tBTA_HD_STATUS status;
    uint8_t reason;
    uint8_t report_type;
    uint8_t report_id;
} tBTA_HD_API_SEND_REPORT;

typedef struct {
    tBTA_HD_STATUS status;
    uint8_t reason;
} tBTA_HD_API_REPORT_ERR;

/* 与HD回调关联的数据的并集*/
typedef union {
    tBTA_HD_STATUS status;                  /* BTA_HD_ENABLE_EVT BTA_HD_DISABLE_EVT BTA_HD_UNREGISTER_APP_EVT */
    tBTA_HD_REG_STATUS reg_status;          /* BTA_HD_REGISTER_APP_EVT */
    tBTA_HD_CONN conn;                      /* BTA_HD_OPEN_EVT BTA_HD_CLOSE_EVT BTA_HD_VC_UNPLUG_EVT BTA_HD_OWN_VC_UNPLUG_EVT */
    tBTA_HD_GET_REPORT get_report;          /* BTA_HD_GET_REPORT */
    tBTA_HD_SET_REPORT set_report;          /* BTA_HD_SET_REPORT */
    tBTA_HD_SET_PROTOCOL set_protocol;      /* BTA_HD_SETPROTOCOL */
    tBTA_HD_INTR_DATA intr_data;            /* BTA_HD_INTR_DATA_EVT */
    tBTA_HD_API_SEND_REPORT send_report;    /* BTA_HD_API_SEND_REPORT_EVT */
    tBTA_HD_API_REPORT_ERR report_err;      /* BTA_HD_API_REPORT_ERR_EVT */
} tBTA_HD;

/* BTA HD回调函数*/
typedef void (tBTA_HD_CBACK)(tBTA_HD_EVT event, tBTA_HD *p_data);

/*****************************************************************************
 *  外部函数声明
 ****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * 函数BTA_HhRegister
 *
 * 说明此功能启用HID主机并向较低层注册HID主机。
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdEnable(tBTA_HD_CBACK *p_cback);

/*******************************************************************************
 * 函数BTA_HhDeregister
 *
 * 说明当主机即将断电时调用此函数。
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdDisable(void);

/*******************************************************************************
 * 功能BTA_HdRegisterApp
 *
 * 说明应注册应用程序时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdRegisterApp(tBTA_HD_APP_INFO *p_app_info, tBTA_HD_QOS_INFO *p_in_qos, tBTA_HD_QOS_INFO *p_out_qos);

/*******************************************************************************
 * 函数BTA_HdUnregisterApp
 *
 * 说明应用程序应注销时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdUnregisterApp(void);

/*******************************************************************************
 * 函数BTA_HdSendReport
 *
 * 说明发送报告时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdSendReport(tBTA_HD_REPORT *p_report);

/*******************************************************************************
 * 功能BTA_HdVirtualCable拔出
 *
 * 说明发送VCU时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdVirtualCableUnplug(void);

/*******************************************************************************
 * 功能BTA_HdConnect
 *
 * 说明当连接到主机时调用此功能。
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdConnect(BD_ADDR addr);

/*******************************************************************************
 * 功能BTA_HdDisconnect
 *
 * 说明当主机断开连接时调用此功能
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdDisconnect(void);

/*******************************************************************************
 * 功能BTA_HdAddDevice
 *
 * 说明当虚拟连接设备时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdAddDevice(BD_ADDR addr);

/*******************************************************************************
 * 功能BTA_HdRemoveDevice
 *
 * 说明当设备实际上未连接时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdRemoveDevice(BD_ADDR addr);

/*******************************************************************************
 * 函数BTA_HdReportError
 *
 * 说明当报告集合报告错误时调用此函数
 *
 * 返回void
 *
 ******************************************************************************/
extern void BTA_HdReportError(uint8_t error);

#ifdef __cplusplus
}
#endif

#endif /* BTA_HD_INCLUDED */
#endif /* BTA_HD_API_H */

