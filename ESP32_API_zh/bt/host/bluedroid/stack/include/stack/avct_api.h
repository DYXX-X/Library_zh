/******************************************************************************
 * 版权所有（C）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此接口文件包含音频视频控制传输协议（AVCTP）的接口。
 *
 ******************************************************************************/
#ifndef AVCT_API_H
#define AVCT_API_H

#include "stack/bt_types.h"
#include "common/bt_target.h"

/*****************************************************************************
**  常量
*****************************************************************************/

/* API函数返回值结果代码。*/
#define AVCT_SUCCESS                0       /* 功能成功*/
#define AVCT_NO_RESOURCES           1       /* 资源不足*/
#define AVCT_BAD_HANDLE             2       /* 错误的句柄*/
#define AVCT_PID_IN_USE             3       /* PID已在使用中*/
#define AVCT_NOT_OPEN               4       /* 连接未打开*/

/* AVCT的PSM。*/
#define AVCT_PSM                    0x0017
#define AVCT_BR_PSM                 0x001B

/* 方案修订号*/
#define AVCT_REV_1_0                0x0100
#define AVCT_REV_1_2                0x0102
#define AVCT_REV_1_3                0x0103
#define AVCT_REV_1_4                0x0104

/* 特定于图层的设置*/
#define AVCT_DATA_CTRL              0x0001    /* 用于控制通道*/
#define AVCT_DATA_BROWSE            0x0002    /* 用于浏览频道*/
#define AVCT_DATA_PARTIAL           0x0100    /* 只能容纳部分消息*/

#define AVCT_MIN_CONTROL_MTU        48  /* 根据AVRC规范，控制信道的最小MTU*/
#define AVCT_MIN_BROWSE_MTU         335 /* 根据AVRC规范，浏览频道的最小MTU*/

/* 消息偏移量。协议栈为AVCTP消息包的协议头所需的字节数。
*/
#define AVCT_MSG_OFFSET             15
#define AVCT_BROWSE_OFFSET          17 /* 浏览频道的默认偏移*/

/* 连接角色。*/
#define AVCT_INT                    0       /* 启动器连接*/
#define AVCT_ACP                    1       /* 接收器连接*/

/* 控制角色。*/
#define AVCT_TARGET                 1       /* 目标*/
#define AVCT_CONTROL                2       /* 控制器*/
#define AVCT_PASSIVE                4       /* 如果发生冲突，允许对方成功*/

/* 命令/响应指示器。*/
#define AVCT_CMD                    0       /* 命令消息*/
#define AVCT_RSP                    2       /* 响应消息*/
#define AVCT_REJ                    3       /* 邮件被拒绝*/

/* 控制回调事件。*/
#define AVCT_CONNECT_CFM_EVT        0       /* 连接确认*/
#define AVCT_CONNECT_IND_EVT        1       /* 连接指示*/
#define AVCT_DISCONNECT_CFM_EVT     2       /* 断开确认*/
#define AVCT_DISCONNECT_IND_EVT     3       /* 断开指示*/
#define AVCT_CONG_IND_EVT           4       /* 拥塞指示*/
#define AVCT_UNCONG_IND_EVT         5       /* 无充血迹象*/
#define AVCT_BROWSE_CONN_CFM_EVT    6       /* 浏览连接确认*/
#define AVCT_BROWSE_CONN_IND_EVT    7       /* 浏览连接指示*/
#define AVCT_BROWSE_DISCONN_CFM_EVT 8       /* 浏览断开确认*/
#define AVCT_BROWSE_DISCONN_IND_EVT 9       /* 浏览断开指示*/
#define AVCT_BROWSE_CONG_IND_EVT    10      /* 拥塞指示*/
#define AVCT_BROWSE_UNCONG_IND_EVT  11      /* 无充血迹象*/


/* 回调事件的通用失败结果代码。*/
#define AVCT_RESULT_FAIL            5

/*****************************************************************************
**  类型定义
*****************************************************************************/

/* 控件回调函数。*/
typedef void (tAVCT_CTRL_CBACK)(UINT8 handle, UINT8 event, UINT16 result,
                                BD_ADDR peer_addr);

/* 消息回调函数*/
/* p_pkt->层特定是AVCT_DATA_CTRL或AVCT_DDATA_BROWSE*/
typedef void (tAVCT_MSG_CBACK)(UINT8 handle, UINT8 label, UINT8 cr,
                               BT_HDR *p_pkt);

/* AVCT_CreateConn使用的结构。*/
typedef struct {
    tAVCT_CTRL_CBACK    *p_ctrl_cback;      /* 控件回调*/
    tAVCT_MSG_CBACK     *p_msg_cback;       /* 消息回调*/
    UINT16              pid;                /* 配置文件ID*/
    UINT8               role;               /* 发起人/受体角色*/
    UINT8               control;        /* 控制角色（控制/目标）*/
} tAVCT_CC;

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 功能AVCT_Register
**
** 说明这是AVCTP协议的系统级注册功能。此函数初始化AVCTP并准备协议堆栈以供其使用。在使用API的其他函数之前，系统或平台必须使用AVCTP调用一次该函数。
**
** 返回void
**
*******************************************************************************/
extern void AVCT_Register(UINT16 mtu, UINT16 mtu_br, UINT8 sec_mask);

/*******************************************************************************
** 函数AVCT_Degister
**
** 说明调用此函数以注销使用AVCTP协议的注册。当系统中的任何应用程序不再使用AVCTP时，将调用它。在调用此函数之前，必须使用AVCT_RemoveConn（）删除所有连接。
**
** 返回void
**
*******************************************************************************/
extern void AVCT_Deregister(void);

/*******************************************************************************
** 函数AVCT_CreateConn
**
** 说明创建AVCTP连接。有两种类型的连接，启动器和受体，由p_cc->role参数决定。调用此函数以创建启动器连接时，如果尚未存在到对等设备的AVCTP连接，则会启动该连接。如果创建了接收器连接，则该连接被动地等待来自对等设备的传入AVCTP连接。
**
** 如果成功，则返回AVCT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVCT_CreateConn(UINT8 *p_handle, tAVCT_CC *p_cc,
                              BD_ADDR peer_addr);

/*******************************************************************************
** 功能AVCT_RemoveConn
**
** 说明删除AVCTP连接。当应用程序不再使用连接时调用此函数。如果这是到对等端的最后一个连接，则AVCTP的L2CAP通道将关闭。
**
** 如果成功，则返回AVCT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVCT_RemoveConn(UINT8 handle);

/*******************************************************************************
** 函数AVCT_CreateBrowse
**
** 说明创建AVCTP连接。有两种类型的连接，启动器和受体，由p_cc->role参数决定。调用此函数以创建启动器连接时，如果尚未存在到对等设备的AVCTP连接，则会启动该连接。如果创建了接收器连接，则该连接被动地等待来自对等设备的传入AVCTP连接。
**
** 如果成功，则返回AVCT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVCT_CreateBrowse(UINT8 handle, UINT8 role);

/*******************************************************************************
** 功能AVCT_RemoveBrowse
**
** 说明删除AVCTP连接。当应用程序不再使用连接时调用此函数。如果这是到对等端的最后一个连接，则AVCTP的L2CAP通道将关闭。
**
** 如果成功，则返回AVCT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVCT_RemoveBrowse(UINT8 handle);

/*******************************************************************************
** 函数AVCT_GetBrowseMtu
**
** 说明获取给定连接的AVCTP浏览频道的peer_mtu。
**
** 返回对等浏览频道MTU。
**
*******************************************************************************/
extern UINT16 AVCT_GetBrowseMtu (UINT8 handle);

/*******************************************************************************
** 函数AVCT_GetPeerTu
**
** 描述获取给定连接的AVCTP通道的peer_mtu。
**
** 返回对等MTU大小。
**
*******************************************************************************/
extern UINT16 AVCT_GetPeerMtu (UINT8 handle);

/*******************************************************************************
** 函数AVCT_MsgReq
**
** 说明向对等设备发送AVCTP消息。在调用AVCT_MsgReq（）时，应用程序应跟踪与事件AVCT_CONG_IND_EVT和AVCT_UNCONG_IND_EVT通信的AVCTP的拥塞状态。如果应用程序在AVCTP拥塞时调用AVCT_MsgReq（），则消息可能被丢弃。应用程序可以在其在控制频道上接收到AVCT_CONNECT_CFM_EVT或AVCT_CONNECT_IND_EVT或在浏览频道上接收AVCT_BROWSE_CONN_CFM_EVT或AVCT_BOWSE_CONN_IND_EVT之后，对AVCT_MsgReq（）进行第一次调用。
**
**                  p_msg->layer_specific必须设置为AVCT_DATA_CTRL，用于控制信道流量；AVCT_DATA_BROWSE用于浏览频道流量。
**
** 如果成功，则返回AVCT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVCT_MsgReq(UINT8 handle, UINT8 label, UINT8 cr, BT_HDR *p_msg);

#ifdef __cplusplus
}
#endif


#endif /* AVCT_API_H */

