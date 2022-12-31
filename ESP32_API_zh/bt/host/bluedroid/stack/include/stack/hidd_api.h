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
#ifndef HIDD_API_H
#define HIDD_API_H
#include "hiddefs.h"
#include "sdp_api.h"

#if (HID_DEV_INCLUDED == TRUE)
/*****************************************************************************
 *  类型定义
 ****************************************************************************/
enum {
    HID_CHANNEL_INTR,
    HID_CHANNEL_CTRL
};
/*
    HID_DHOST_EVT_OPEN-连接到主机设备（CTRL和INTR），数据=n/a HID_DHOST-EVT_CLOSE-与主机设备断开连接，数据=原因HID_DHOST.EVT_GET_REPORT-从主机获取GET_REPORT
*/

enum {
    HID_DHOST_EVT_OPEN,
    HID_DHOST_EVT_CLOSE,
    HID_DHOST_EVT_GET_REPORT,
    HID_DHOST_EVT_SET_REPORT,
    HID_DHOST_EVT_SET_PROTOCOL,
    HID_DHOST_EVT_INTR_DATA,
    HID_DHOST_EVT_VC_UNPLUG,
    HID_DHOST_EVT_SUSPEND,
    HID_DHOST_EVT_EXIT_SUSPEND,
};

typedef void (tHID_DEV_HOST_CALLBACK)(BD_ADDR bd_addr, uint8_t event, uint32_t data, BT_HDR* p_buf);

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *  外部函数声明
 ****************************************************************************/

/*******************************************************************************
 * 函数HID_DevInit
 *
 * 说明初始化控制块
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevInit(void);

/*******************************************************************************
 * 函数HID_DevInit
 *
 * 说明取消初始化控制块
 *
 * 返回void
 *
 ******************************************************************************/
extern void HID_DevDeinit(void);

/*******************************************************************************
 * 函数HID_DevRegister
 *
 * 说明向下层注册HID设备
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevRegister(tHID_DEV_HOST_CALLBACK* host_cback);

/*******************************************************************************
 * 函数HID_DevDeregister
 *
 * 说明取消注册具有较低层的HID设备
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevDeregister(void);

/*******************************************************************************
 * 函数HID_DevSetSecurityLevel
 *
 * 说明设置HID设备连接的安全级别
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevSetSecurityLevel(uint8_t sec_lvl);

/*******************************************************************************
 * 函数HID_DevAddRecord
 *
 * 描述为HID设备创建SDP记录
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevAddRecord(uint32_t handle, char* p_name,
                                    char* p_description, char* p_provider,
                                    uint16_t subclass, uint16_t desc_len,
                                    uint8_t* p_desc_data);

/*******************************************************************************
 * 函数HID_DevSendReport
 *
 * 描述发送报告
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevSendReport(uint8_t channel, uint8_t type, uint8_t id,
                                     uint16_t len, uint8_t* p_data);

/*******************************************************************************
 * 函数HID_DevVirtualCableDull
 *
 * 描述发送虚拟电缆拔出
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevVirtualCableUnplug(void);

/*******************************************************************************
 * 函数HID_DevPlugDevice
 *
 * 描述建立到给定主机的虚拟电缆
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevPlugDevice(BD_ADDR addr);

/*******************************************************************************
 * 函数HID_DevUnplugDevice
 *
 * 说明从给定主机拔下虚拟电缆
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevUnplugDevice(BD_ADDR addr);

/*******************************************************************************
 * 函数HID_DeviConnect
 *
 * 说明连接到设备
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevConnect(void);

/*******************************************************************************
 * 函数HID_DevDisconnect
 *
 * 说明与设备断开连接
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevDisconnect(void);

/*******************************************************************************
 * 函数HID_DevSetIncomingPolicy
 *
 * 说明设置传入连接的策略（允许/不允许）
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevSetIncomingPolicy(bool allow);

/*******************************************************************************
 * 函数HID_DevReportError
 *
 * 说明通过HANDSHAKE设置报告的报告错误
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevReportError(uint8_t error);

/*******************************************************************************
 * 函数HID_DevGetDevice
 *
 * 说明返回虚拟有线设备的BD地址
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevGetDevice(BD_ADDR* addr);

/*******************************************************************************
 * 函数HID_DevSetIncomingQos
 *
 * 说明设置中断L2CAP信道的传入QoS值
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevSetIncomingQos(
    uint8_t service_type, uint32_t token_rate, uint32_t token_bucket_size,
    uint32_t peak_bandwidth, uint32_t latency, uint32_t delay_variation);

/*******************************************************************************
 * 函数HID_DevSetOutgoingQos
 *
 * 说明设置中断L2CAP信道的传出QoS值
 *
 * 返回tHID_STATUS
 *
 ******************************************************************************/
extern tHID_STATUS HID_DevSetOutgoingQos(
    uint8_t service_type, uint32_t token_rate, uint32_t token_bucket_size,
    uint32_t peak_bandwidth, uint32_t latency, uint32_t delay_variation);

/*******************************************************************************
 * 函数HID_DevSetTraceLevel
 *
 * 说明此函数设置HID Dev的跟踪级别。如果使用值0xFF调用，则只读取当前跟踪级别。
 *
 * 返回新的（当前）跟踪级别
 *
 ******************************************************************************/
extern uint8_t HID_DevSetTraceLevel(uint8_t new_level);

#ifdef __cplusplus
}
#endif

#endif
#endif /* HIDD_API_H */

