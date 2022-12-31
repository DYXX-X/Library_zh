/******************************************************************************
 * 版权所有（C）2009-2013 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef GAP_API_H
#define GAP_API_H

#include "stack/sdpdefs.h"
#include "stack/profiles_api.h"
#include "stack/btm_api.h"
#include "stack/l2c_api.h"

/*****************************************************************************
**  常量
*****************************************************************************/
/***GAP错误和状态代码***/
#define GAP_UNSUPPORTED     (GAP_ERR_GRP + 0x01)    /* 不支持的呼叫*/
#define GAP_EOINQDB         (GAP_ERR_GRP + 0x02)    /* 查询结束数据库标记*/
#define GAP_ERR_BUSY        (GAP_ERR_GRP + 0x03)    /* 请求的功能正忙*/
#define GAP_ERR_NO_CTRL_BLK (GAP_ERR_GRP + 0x04)    /* 没有可用的控制块*/
#define GAP_ERR_STARTING_CMD (GAP_ERR_GRP + 0x05)   /* 启动命令时出错*/
#define GAP_NO_BDADDR_REC   (GAP_ERR_GRP + 0x06)    /* BD_ADDR无查询DB记录*/
#define GAP_ERR_ILL_MODE    (GAP_ERR_GRP + 0x07)    /* 检测到非法模式参数*/
#define GAP_ERR_ILL_INQ_TIME (GAP_ERR_GRP + 0x08)   /* 检测到非法的时间参数*/
#define GAP_ERR_ILL_PARM     (GAP_ERR_GRP + 0x09)   /* 检测到非法参数*/
#define GAP_ERR_REM_NAME    (GAP_ERR_GRP + 0x0a)    /* 启动远程设备名称请求时出错*/
#define GAP_CMD_INITIATED   (GAP_ERR_GRP + 0x0b)    /* GAP命令已启动（结果待定）*/
#define GAP_DEVICE_NOT_UP   (GAP_ERR_GRP + 0x0c)    /* 设备未启动；请求未执行*/
#define GAP_BAD_BD_ADDR     (GAP_ERR_GRP + 0x0d)    /* 传入的bd地址找不到或无效*/

#define GAP_ERR_BAD_HANDLE  (GAP_ERR_GRP + 0x0e)    /* 不良GAP手柄*/
#define GAP_ERR_BUF_OFFSET  (GAP_ERR_GRP + 0x0f)    /* 缓冲区偏移量无效*/
#define GAP_ERR_BAD_STATE   (GAP_ERR_GRP + 0x10)    /* 连接处于无效状态*/
#define GAP_NO_DATA_AVAIL   (GAP_ERR_GRP + 0x11)    /* 无可用数据*/
#define GAP_ERR_CONGESTED   (GAP_ERR_GRP + 0x12)    /* BT堆栈拥塞*/
#define GAP_ERR_SECURITY    (GAP_ERR_GRP + 0x13)    /* 安全性失败*/

#define GAP_ERR_PROCESSING  (GAP_ERR_GRP + 0x14)    /* 处理BTM请求时的一般错误*/
#define GAP_ERR_TIMEOUT     (GAP_ERR_GRP + 0x15)    /* 处理cmd时超时*/
#define GAP_EVT_CONN_OPENED         0x0100
#define GAP_EVT_CONN_CLOSED         0x0101
#define GAP_EVT_CONN_DATA_AVAIL     0x0102
#define GAP_EVT_CONN_CONGESTED      0x0103
#define GAP_EVT_CONN_UNCONGESTED    0x0104
/* “chan_mode_mask”字段的值*/
/* GAP_ConOpen（）-要协商的可选通道*/
#define GAP_FCR_CHAN_OPT_BASIC      L2CAP_FCR_CHAN_OPT_BASIC
#define GAP_FCR_CHAN_OPT_ERTM       L2CAP_FCR_CHAN_OPT_ERTM
#define GAP_FCR_CHAN_OPT_STREAM     L2CAP_FCR_CHAN_OPT_STREAM
/***用于连接变量和函数***/
#define GAP_INVALID_HANDLE      0xFFFF

/* 这用于更改AMP的标准*/
#define GAP_PROTOCOL_ID         (UUID_PROTOCOL_UDP)


#ifndef  GAP_PREFER_CONN_INT_MAX
#define  GAP_PREFER_CONN_INT_MAX         BTM_BLE_CONN_INT_MIN
#endif

#ifndef  GAP_PREFER_CONN_INT_MIN
#define  GAP_PREFER_CONN_INT_MIN         BTM_BLE_CONN_INT_MIN
#endif

#ifndef  GAP_PREFER_CONN_LATENCY
#define  GAP_PREFER_CONN_LATENCY         0
#endif

#ifndef  GAP_PREFER_CONN_SP_TOUT
#define  GAP_PREFER_CONN_SP_TOUT         2000
#endif

/*****************************************************************************
**  类型定义
*****************************************************************************/
/*
** 连接服务的回调函数
*/
typedef void (tGAP_CONN_CALLBACK) (UINT16 gap_handle, UINT16 event);

/*
** 定义回调函数原型。参数特定于每个事件，如下所述
*/
typedef void (tGAP_CALLBACK) (UINT16 event, void *p_data);


/* GAP_FindAddrByName结果结构的定义*/
typedef struct {
    UINT16       status;
    BD_ADDR      bd_addr;
    tBTM_BD_NAME devname;
} tGAP_FINDADDR_RESULTS;

typedef struct {
    UINT16      int_min;
    UINT16      int_max;
    UINT16      latency;
    UINT16      sp_tout;
} tGAP_BLE_PREF_PARAM;

typedef union {
    tGAP_BLE_PREF_PARAM     conn_param;
    BD_ADDR                 reconn_bda;
    UINT16                  icon;
    UINT8                   *p_dev_name;
    UINT8                   addr_resolution;

} tGAP_BLE_ATTR_VALUE;

typedef void (tGAP_BLE_CMPL_CBACK)(BOOLEAN status, BD_ADDR addr, UINT16 length, char *p_name);


/*****************************************************************************
**  外部函数声明
*****************************************************************************/

/***L2CAP连接接口的功能***/

/*******************************************************************************
** 功能GAP_ConOpen
**
** 说明调用此函数以打开通用L2CAP连接。
**
** 如果成功，则返回连接的句柄，否则返回GAP_INVALID_handle
**
*******************************************************************************/
extern UINT16 GAP_ConnOpen (const char *p_serv_name, UINT8 service_id, BOOLEAN is_server,
                            BD_ADDR p_rem_bda, UINT16 psm, tL2CAP_CFG_INFO *p_cfg,
                            tL2CAP_ERTM_INFO *ertm_info,
                            UINT16 security, UINT8 chan_mode_mask, tGAP_CONN_CALLBACK *p_cb);

/*******************************************************************************
** 功能GAP_Connect关闭
**
** 说明调用此函数以关闭连接。
**
** 返回BT_PASS-关闭的OK GAP_ERR_BAD_HANDLE-无效句柄
**
*******************************************************************************/
extern UINT16 GAP_ConnClose (UINT16 gap_handle);

/*******************************************************************************
** 函数GAP_ConnReadData
**
** 说明GKI缓冲区未知应用程序在收到GAP_EVT_RXDATA事件后将调用此函数。将数据复制到接收缓冲区参数中。
**
** 返回BT_PASS-数据读取GAP_ERR_BAD_HANDLE-无效句柄GAP_NO_data_AVAIL-无可用数据
**
*******************************************************************************/
extern UINT16 GAP_ConnReadData (UINT16 gap_handle, UINT8 *p_data,
                                UINT16 max_len, UINT16 *p_len);

/*******************************************************************************
** 函数GAP_GetRxQueueCnt
**
** 说明此函数返回rx队列上的字节数。
**
** 参数：handle-GAP_ConOpen p_rx_queue_count中返回的句柄-中返回队列计数的指针。
**
**
*******************************************************************************/
extern int GAP_GetRxQueueCnt (UINT16 handle, UINT32 *p_rx_queue_count);

/*******************************************************************************
** 函数GAP_ConBTRead
**
** 说明GKI缓冲区感知应用程序将在收到GAP_EVT_RXDATA事件后调用此函数以处理传入的数据缓冲区。
**
** 返回BT_PASS-数据读取GAP_ERR_BAD_HANDLE-无效句柄GAP_NO_data_AVAIL-无可用数据
**
*******************************************************************************/
extern UINT16 GAP_ConnBTRead (UINT16 gap_handle, BT_HDR **pp_buf);

/*******************************************************************************
** 函数GAP_ConBTWrite
**
** 说明GKI缓冲区感知应用程序可以通过将指针传递到GKI数据缓冲区来调用此函数来写入数据。
**
** 返回BT_PASS-数据读取GAP_ERR_BAD_HANDLE-无效句柄GAP_ERR-BAD_STATE-未建立连接GAP_invalid_BBUF_OFFSET-缓冲区偏移量无效
*******************************************************************************/
extern UINT16 GAP_ConnBTWrite (UINT16 gap_handle, BT_HDR *p_buf);

/*******************************************************************************
** 函数GAP_ConnWriteData
**
** 说明GKI缓冲区未知应用程序将调用此函数向连接发送数据。数据拷贝被制作成GKI缓冲区。
**
** 返回BT_PASS-数据读取GAP_ERR_BAD_HANDLE-无效句柄GAP_ERR-BAD_STATE-连接未建立GAP_CONGESTION-系统拥塞
**
*******************************************************************************/
extern UINT16 GAP_ConnWriteData (UINT16 gap_handle, UINT8 *p_data,
                                 UINT16 max_len, UINT16 *p_len);

/*******************************************************************************
** 功能GAP_ConneReconfig
**
** 说明应用程序可以调用此函数来重新配置连接。
**
** 返回BT_PASS-配置进程已启动GAP_ERR_BAD_HANDLE-无效句柄
**
*******************************************************************************/
extern UINT16 GAP_ConnReconfig (UINT16 gap_handle, tL2CAP_CFG_INFO *p_cfg);

/*******************************************************************************
** 函数GAP_ConnetSetIdleTimeout
**
** 说明高层调用此函数以设置连接或所有未来连接的空闲超时。“空闲超时”是指连接在没有L2CAP通道的情况下可以保持连接的时间。超时为零意味着当删除最后一个通道时，连接将立即断开。超时0xFFFF表示没有超时。值以秒为单位。
**
** 返回BT_PASS-配置进程已启动GAP_ERR_BAD_HANDLE-无效句柄
**
*******************************************************************************/
extern UINT16 GAP_ConnSetIdleTimeout (UINT16 gap_handle, UINT16 timeout);

/*******************************************************************************
** 函数GAP_ConnGetRemoteAddr
**
** 描述调用此函数以获取连接的远程BD地址。
**
** 返回BT_PASS-关闭的OK GAP_ERR_BAD_HANDLE-无效句柄
**
*******************************************************************************/
extern UINT8 *GAP_ConnGetRemoteAddr (UINT16 gap_handle);

/*******************************************************************************
** 函数GAP_ConnGetRemMtuSize
**
** 说明返回远程设备的MTU大小。
**
** 返回UINT16-可以传输到对等端的最大缓冲区大小
**
*******************************************************************************/
extern UINT16 GAP_ConnGetRemMtuSize (UINT16 gap_handle);

/*******************************************************************************
** 函数GAP_ConnGetL2CAPCid
**
** 说明返回L2CAP通道id
**
** 参数：handle-连接的句柄
**
** 返回UINT16-如果错误，则返回L2CAP通道id 0
**
*******************************************************************************/
extern UINT16 GAP_ConnGetL2CAPCid (UINT16 gap_handle);

/*******************************************************************************
** 函数GAP_SetTraceLevel
**
** 说明此功能设置GAP的跟踪级别。如果使用值0xFF调用，它只返回当前跟踪级别。
**
** 返回新的或当前的跟踪级别
**
*******************************************************************************/
extern UINT8 GAP_SetTraceLevel (UINT8 new_level);

/*******************************************************************************
** 函数GAP_Init
**
** 说明初始化GAP使用的控制块。除非每次堆栈调用一次，否则不应调用此例程。
**
** 退货状态
**
*******************************************************************************/
extern bt_status_t GAP_Init(void);

/*******************************************************************************
** 函数GAP_Deinit
**
** 说明调用此函数以取消初始化此层的控制块。
**
** 返回void
**
*******************************************************************************/
extern void GAP_Deinit(void);

#if (BLE_INCLUDED == TRUE)
/*******************************************************************************
** 函数GAP_BleAttrDBUpdate
**
** 描述更新GAP本地BLE属性数据库。
**
** 不返回任何内容
**
*******************************************************************************/
extern void GAP_BleAttrDBUpdate(UINT16 attr_uuid, tGAP_BLE_ATTR_VALUE *p_value);


/*******************************************************************************
** 函数GAP_BleReadPeerRefConnParams
**
** 说明启动读取已连接外设的首选连接参数的过程
**
** 如果已开始读取，则返回TRUE；如果GAP忙，则返回FALSE
**
*******************************************************************************/
extern BOOLEAN GAP_BleReadPeerPrefConnParams (BD_ADDR peer_bda);

/*******************************************************************************
** 函数GAP_BleReadPeerDevName
**
** 说明启动读取已连接外设设备名称的过程。
**
** 如果请求被接受，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN GAP_BleReadPeerDevName (BD_ADDR peer_bda, tGAP_BLE_CMPL_CBACK *p_cback);


/*******************************************************************************
** 函数GAP_BleReadPeerAddressResolutionCap
**
** 说明启动读取对等地址解析功能的过程
**
** 如果请求被接受，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN GAP_BleReadPeerAddressResolutionCap (BD_ADDR peer_bda,
        tGAP_BLE_CMPL_CBACK *p_cback);

/*******************************************************************************
** 函数GAP_BleCancelReadPeerDevName
**
** 说明取消读取外围设备的设备名称。
**
** 如果请求被接受，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN GAP_BleCancelReadPeerDevName (BD_ADDR peer_bda);


#endif

#endif  /* GAP_API_H */

