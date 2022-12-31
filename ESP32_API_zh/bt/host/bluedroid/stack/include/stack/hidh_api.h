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
#ifndef HIDH_API_H
#define HIDH_API_H

#include "stack/hiddefs.h"
#include "stack/sdp_api.h"

#if (HID_HOST_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

enum {
    HID_SDP_NO_SERV_UUID = (SDP_ILLEGAL_PARAMETER + 1),
    HID_SDP_MANDATORY_MISSING
};

/* 要在HID_HostAddDev API中使用的属性掩码值*/
#define HID_VIRTUAL_CABLE        0x0001
#define HID_NORMALLY_CONNECTABLE 0x0002
#define HID_RECONN_INIT          0x0004
#define HID_SDP_DISABLE          0x0008
#define HID_BATTERY_POWER        0x0010
#define HID_REMOTE_WAKE          0x0020
#define HID_SUP_TOUT_AVLBL       0x0040
#define HID_SSR_MAX_LATENCY      0x0080
#define HID_SSR_MIN_TOUT         0x0100

#define HID_SEC_REQUIRED         0x8000
#define HID_ATTR_MASK_IGNORE     0


/*****************************************************************************
**  类型定义
*****************************************************************************/

typedef void (tHID_HOST_SDP_CALLBACK) (UINT16 result, UINT16 attr_mask,
                                       tHID_DEV_SDP_INFO *sdp_rec );

/* HID-HOST通过tHID_HOST_DEV_CALLBACHID_HDEV_VT_OPEN将下表中的事件返回给应用程序，该设备连接到中断和控制通道处于打开状态的设备。数据=NAHID_HDEV_EVT_CLOSE与设备的连接已关闭。数据=原因代码。HID_HDEVE_EVT_RETRYING正在重新连接丢失的连接。数据=重试数HID_HDEV_EVT_IN_REPORT设备发送了输入报告数据=报告类型updatea=指向BT_HDR（具有报告数据的GKI缓冲区）的指针。HID_HDEVE_EVT_HANDSHAKE设备发送了SET_REPORT数据=结果代码updatea=NA。HID_HDEVE_EVT_VC_UNPLUG设备发送了虚拟拔出数据=NA。updatea=不适用。
*/

enum {
    HID_HDEV_EVT_OPEN,
    HID_HDEV_EVT_CLOSE,
    HID_HDEV_EVT_RETRYING,
    HID_HDEV_EVT_INTR_DATA,
    HID_HDEV_EVT_INTR_DATC,
    HID_HDEV_EVT_CTRL_DATA,
    HID_HDEV_EVT_CTRL_DATC,
    HID_HDEV_EVT_HANDSHAKE,
    HID_HDEV_EVT_VC_UNPLUG
};
typedef void (tHID_HOST_DEV_CALLBACK) (UINT8 dev_handle,
                                       BD_ADDR addr,
                                       UINT8 event, /* 来自HID-DEVICE的事件。*/
                                       UINT32 data, /* 与事件对应的整数数据。*/
                                       BT_HDR *p_buf ); /* 与事件对应的指针数据。*/


/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 函数HID_HostGetSDPRecord
**
** 说明此功能读取设备SDP记录。
**
** 返回tHID_STATUS
**
*******************************************************************************/
extern tHID_STATUS HID_HostGetSDPRecord (BD_ADDR addr,
        tSDP_DISCOVERY_DB *p_db,
        UINT32 db_len,
        tHID_HOST_SDP_CALLBACK *sdp_cback );

/*******************************************************************************
** 函数HID_HostRegister
**
** 说明此函数向较低层注册HID主机。
**
** 返回tHID_STATUS
**
*******************************************************************************/
extern tHID_STATUS HID_HostRegister (tHID_HOST_DEV_CALLBACK *dev_cback);

/*******************************************************************************
** 函数HID_HostDeregister
**
** 说明当主机即将断电时调用此函数。
**
** 返回tHID_STATUS
**
*******************************************************************************/
extern tHID_STATUS HID_HostDeregister(void);

/*******************************************************************************
** 函数HID_HostAddDev
**
** 描述这被称为HID主机可以管理此设备。
**
** 返回tHID_STATUS
**
*******************************************************************************/
extern tHID_STATUS HID_HostAddDev (BD_ADDR addr, UINT16 attr_mask,
                                   UINT8 *handle );

/*******************************************************************************
** 函数HID_HostGetDev
**
** 描述这被称为HID主机可以找到此设备。
**
** 返回tHID_STATUS
**
*******************************************************************************/
extern tHID_STATUS HID_HostGetDev(BD_ADDR addr, UINT8 *handle);

/*******************************************************************************
** 函数HID_HostRemoveDev
**
** 说明这将从主机必须管理的设备列表中删除设备。
**
** 返回tHID_STATUS
**
*******************************************************************************/
extern tHID_STATUS HID_HostRemoveDev (UINT8 dev_handle );

/*******************************************************************************
** 函数HID_HostOpenDev
**
** 说明当用户想要启动与设备的连接尝试时，会调用此函数。
**
** 返回void
**
*******************************************************************************/
extern tHID_STATUS HID_HostOpenDev (UINT8 dev_handle );

/*******************************************************************************
** 函数HID_HostWriteDev
**
** 说明当主机有报告要发送时调用此函数。
**
** 返回void
**
*******************************************************************************/
extern tHID_STATUS HID_HostWriteDev(UINT8 dev_handle, UINT8 t_type,
                                    UINT8 param, UINT16 data,
                                    UINT8 report_id, BT_HDR *pbuf);

/*******************************************************************************
** 函数HID_HostCloseDev
**
** 说明此功能可断开设备。
**
** 返回void
**
*******************************************************************************/
extern tHID_STATUS HID_HostCloseDev(UINT8 dev_handle );

/*******************************************************************************
** 函数HID_HostInit
**
** 说明此函数初始化控制块和跟踪变量
**
** 返回tHID_STATUS
*******************************************************************************/
extern tHID_STATUS HID_HostInit(void);

/*******************************************************************************
** 函数HID_HostDeinit
**
** 说明此函数用于取消初始化控制块
**
** 返回void
*******************************************************************************/
extern void HID_HostDeinit(void);

/*******************************************************************************
** 函数HID_HostSetSecurityLevel
**
** 说明此功能设置应用程序标记为需要安全的设备的安全级别
**
** 返回tHID_STATUS
*******************************************************************************/
extern tHID_STATUS HID_HostSetSecurityLevel( char serv_name[], UINT8 sec_lvl );

/*******************************************************************************
** 函数hid_known_hid_device
**
** 说明此功能检查此设备是否为HID设备类型
**
** 如果设备存在，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
BOOLEAN hid_known_hid_device (BD_ADDR bd_addr);


/*******************************************************************************
** 函数HID_HostSetTraceLevel
**
** 说明此函数设置HID主机的跟踪级别。如果用0xFF值调用，它只读取当前跟踪级别。
**
** 返回新的（当前）跟踪级别
**
*******************************************************************************/
extern UINT8 HID_HostSetTraceLevel (UINT8 new_level);

#ifdef __cplusplus
}
#endif

#endif  ///HID_HOST_INCLUDED == TRUE

#endif  /* HIDH_API_H */

