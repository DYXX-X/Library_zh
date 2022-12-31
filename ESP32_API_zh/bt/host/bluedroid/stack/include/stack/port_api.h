/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 该文件包含PORT API定义
 *
 ******************************************************************************/
#ifndef PORT_API_H
#define PORT_API_H

#include "common/bt_target.h"
#include "common/bt_defs.h"

/*****************************************************************************
**  常量和类型
*****************************************************************************/

/*
** 在设置请求中定义从应用程序发送的端口设置结构，或在设置指示中向应用程序发送端口设置结构。
*/
typedef struct {

#define PORT_BAUD_RATE_2400       0x00
#define PORT_BAUD_RATE_4800       0x01
#define PORT_BAUD_RATE_7200       0x02
#define PORT_BAUD_RATE_9600       0x03
#define PORT_BAUD_RATE_19200      0x04
#define PORT_BAUD_RATE_38400      0x05
#define PORT_BAUD_RATE_57600      0x06
#define PORT_BAUD_RATE_115200     0x07
#define PORT_BAUD_RATE_230400     0x08

    UINT8  baud_rate;

#define PORT_5_BITS               0x00
#define PORT_6_BITS               0x01
#define PORT_7_BITS               0x02
#define PORT_8_BITS               0x03

    UINT8  byte_size;

#define PORT_ONESTOPBIT           0x00
#define PORT_ONE5STOPBITS         0x01
    UINT8   stop_bits;

#define PORT_PARITY_NO            0x00
#define PORT_PARITY_YES           0x01
    UINT8   parity;

#define PORT_ODD_PARITY           0x00
#define PORT_EVEN_PARITY          0x01
#define PORT_MARK_PARITY          0x02
#define PORT_SPACE_PARITY         0x03

    UINT8   parity_type;

#define PORT_FC_OFF               0x00
#define PORT_FC_XONXOFF_ON_INPUT  0x01
#define PORT_FC_XONXOFF_ON_OUTPUT 0x02
#define PORT_FC_CTS_ON_INPUT      0x04
#define PORT_FC_CTS_ON_OUTPUT     0x08
#define PORT_FC_DSR_ON_INPUT      0x10
#define PORT_FC_DSR_ON_OUTPUT     0x20

    UINT8 fc_type;

    UINT8 rx_char1;

#define PORT_XON_DC1              0x11
    UINT8 xon_char;

#define PORT_XOFF_DC3             0x13
    UINT8 xoff_char;

} tPORT_STATE;


/*
** 定义回调函数原型。参数针对每个事件，如下所述
*/
typedef int  (tPORT_DATA_CALLBACK) (UINT16 port_handle, void *p_data, UINT16 len);

#define DATA_CO_CALLBACK_TYPE_INCOMING          1
#define DATA_CO_CALLBACK_TYPE_OUTGOING_SIZE     2
#define DATA_CO_CALLBACK_TYPE_OUTGOING          3
typedef int  (tPORT_DATA_CO_CALLBACK) (UINT16 port_handle, UINT8 *p_buf, UINT16 len, int type);

typedef void (tPORT_CALLBACK) (UINT32 code, UINT16 port_handle);

typedef void (tPORT_MGMT_CALLBACK) (UINT32 code, UINT16 port_handle, void* data);

/**
 * 定义服务器端口管理回调函数参数
 */
typedef struct {
    BOOLEAN accept; /* 如果上层接受传入连接*/
    BOOLEAN ignore_rfc_state; /* 如果需要忽略PORT_CheckConnection的rfc状态*/
} tPORT_MGMT_SR_CALLBACK_ARG;

/*
** 定义已注册应用程序可以在回调中接收的事件
*/

#define PORT_EV_RXCHAR  0x00000001   /* 收到的任何字符*/
#define PORT_EV_RXFLAG  0x00000002   /* 收到特定字符*/
#define PORT_EV_TXEMPTY 0x00000004   /* 传输队列为空*/
#define PORT_EV_CTS     0x00000008   /* CTS已更改状态*/
#define PORT_EV_DSR     0x00000010   /* DSR已更改状态*/
#define PORT_EV_RLSD    0x00000020   /* RLSD已更改状态*/
#define PORT_EV_BREAK   0x00000040   /* 收到BREAK*/
#define PORT_EV_ERR     0x00000080   /* 发生线路状态错误*/
#define PORT_EV_RING    0x00000100   /* 检测到振铃信号*/
#define PORT_EV_CTSS    0x00000400   /* CTS状态*/
#define PORT_EV_DSRS    0x00000800   /* DSR状态*/
#define PORT_EV_RLSDS   0x00001000   /* RLSD状态*/
#define PORT_EV_OVERRUN 0x00002000   /* 接收机缓冲区溢出*/
#define PORT_EV_TXCHAR  0x00004000   /* 传输的任何字符*/

#define PORT_EV_CONNECTED    0x00000200  /* RFCOMM连接已建立*/
#define PORT_EV_CONNECT_ERR  0x00008000  /* 无法建立连接*/
/* 或断开连接*/
#define PORT_EV_FC      0x00010000   /* 远程更改了数据流启用标志*/
#define PORT_EV_FCS     0x00020000   /* 数据流启用状态true=已启用*/

/*
** 要注册事件，应用程序应提供具有相应位集的位掩码
*/

#define PORT_MASK_ALL             (PORT_EV_RXCHAR | PORT_EV_TXEMPTY | PORT_EV_CTS | \
                                   PORT_EV_DSR | PORT_EV_RLSD | PORT_EV_BREAK | \
                                   PORT_EV_ERR | PORT_EV_RING | PORT_EV_CONNECT_ERR | \
                                   PORT_EV_DSRS | PORT_EV_CTSS | PORT_EV_RLSDS | \
                                   PORT_EV_RXFLAG | PORT_EV_TXCHAR | PORT_EV_OVERRUN | \
                                   PORT_EV_FC | PORT_EV_FCS | PORT_EV_CONNECTED)


/*
** 定义端口结果代码
*/
#define PORT_SUCCESS                0

#define PORT_ERR_BASE               0

#define PORT_UNKNOWN_ERROR          (PORT_ERR_BASE + 1)
#define PORT_ALREADY_OPENED         (PORT_ERR_BASE + 2)
#define PORT_CMD_PENDING            (PORT_ERR_BASE + 3)
#define PORT_APP_NOT_REGISTERED     (PORT_ERR_BASE + 4)
#define PORT_NO_MEM                 (PORT_ERR_BASE + 5)
#define PORT_NO_RESOURCES           (PORT_ERR_BASE + 6)
#define PORT_BAD_BD_ADDR            (PORT_ERR_BASE + 7)
#define PORT_BAD_HANDLE             (PORT_ERR_BASE + 9)
#define PORT_NOT_OPENED             (PORT_ERR_BASE + 10)
#define PORT_LINE_ERR               (PORT_ERR_BASE + 11)
#define PORT_START_FAILED           (PORT_ERR_BASE + 12)
#define PORT_PAR_NEG_FAILED         (PORT_ERR_BASE + 13)
#define PORT_PORT_NEG_FAILED        (PORT_ERR_BASE + 14)
#define PORT_SEC_FAILED             (PORT_ERR_BASE + 15)
#define PORT_PEER_CONNECTION_FAILED (PORT_ERR_BASE + 16)
#define PORT_PEER_FAILED            (PORT_ERR_BASE + 17)
#define PORT_PEER_TIMEOUT           (PORT_ERR_BASE + 18)
#define PORT_CLOSED                 (PORT_ERR_BASE + 19)
#define PORT_TX_FULL                (PORT_ERR_BASE + 20)
#define PORT_LOCAL_CLOSED           (PORT_ERR_BASE + 21)
#define PORT_LOCAL_TIMEOUT          (PORT_ERR_BASE + 22)
#define PORT_TX_QUEUE_DISABLED      (PORT_ERR_BASE + 23)
#define PORT_PAGE_TIMEOUT           (PORT_ERR_BASE + 24)
#define PORT_INVALID_SCN            (PORT_ERR_BASE + 25)

#define PORT_ERR_MAX                (PORT_ERR_BASE + 26)

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 函数RFCOMM_CreateConnection
**
** 说明RFCOMM_CreateConnection函数用于从应用程序建立到对等设备的串行端口连接，或允许RFCOMM接受来自对等应用程序的连接。
**
** 参数：scn-向SDP（服务器）注册或使用SDP从对等设备（客户端）获得的服务信道号。is_server-TRUE（如果请求应用程序是服务器）mtu-应用程序可以接受的最大帧大小bd_addr-对等（客户端）掩码的bd_addr-指定要启用的事件。值为零将禁用所有事件。p_handle-指向句柄的OUT指针。p_mgmt_cb-指向回调函数的指针，用于接收连接上/下事件。笔记：
**
** 如果服务器准备好接受多个同时连接，则可以使用相同的scn参数多次调用此函数。
**
** 如果客户端在现有无启动器多路复用器信道上发起连接，则连接的DLCI为（scn*2+1）。否则为（scn 2）。对于服务器，如果客户端将使用（scn 2+1）DLCI调用它，则可以稍后更改DLCI。
**
*******************************************************************************/
extern int RFCOMM_CreateConnection (UINT16 uuid, UINT8 scn,
                                    BOOLEAN is_server, UINT16 mtu,
                                    BD_ADDR bd_addr, UINT16 *p_handle,
                                    tPORT_MGMT_CALLBACK *p_mgmt_cb);


/*******************************************************************************
** 函数RFCOMM_RemoveConnection
**
** 说明调用此函数以关闭指定的连接。
**
** 参数：handle-Open中返回的端口的句柄
**
*******************************************************************************/
extern int RFCOMM_RemoveConnection (UINT16 handle);


/*******************************************************************************
** 函数RFCOMM_RemoveServer
**
** 说明调用此函数以关闭服务器端口。
**
** 参数：handle-RFCOMM_CreateConnection中返回的句柄
**
*******************************************************************************/
extern int RFCOMM_RemoveServer (UINT16 handle);


/*******************************************************************************
** 函数PORT_SetEventCallback
**
** 说明设置指定连接的事件回调。
**
** 参数：handle-在Openp_callback中返回的端口的句柄-当发生掩码中指定的事件时，应该从RFCOMM调用回调函数的地址。
**
*******************************************************************************/
extern int PORT_SetEventCallback (UINT16 port_handle,
                                  tPORT_CALLBACK *p_port_cb);

/*******************************************************************************
** 函数PORT_ClearKeepHandleFlag
**
** 描述调用此函数以清除保持句柄标志，这将导致关闭时不保持端口句柄打开参数：handle-RFCOMM_CreateConnection中返回的句柄
**
*******************************************************************************/
int PORT_ClearKeepHandleFlag (UINT16 port_handle);

/*******************************************************************************
** 函数PORT_SetEventCallback
**
** 说明设置指定连接的事件数据回调。
**
** 参数：handle-在Openp_callback中返回的端口的句柄-当接收到数据包时应该从RFCOMM调用的回调函数的地址。
**
*******************************************************************************/
extern int PORT_SetDataCallback (UINT16 port_handle,
                                 tPORT_DATA_CALLBACK *p_cb);

extern int PORT_SetDataCOCallback (UINT16 port_handle, tPORT_DATA_CO_CALLBACK *p_port_cb);
/*******************************************************************************
** 函数PORT_SetEventMask
**
** 说明调用此函数以关闭指定的连接。
**
** 参数：handle-打开掩码中返回的端口的句柄-指定要启用的事件。值为零将禁用所有事件。
**
*******************************************************************************/
extern int PORT_SetEventMask (UINT16 port_handle, UINT32 mask);


/*******************************************************************************
** 函数PORT_CheckConnection
**
** 说明如果句柄引用的连接已启动并正在运行，则此函数返回PORT_SUCCESS
**
** 参数：handle-Open ignore_rfc_state中返回的端口的句柄-如果需要忽略rfc状态bd_addr-对等体p_lcid的OUT bd_addl-OUT L2CAP的lcid
**
*******************************************************************************/
extern int PORT_CheckConnection (UINT16 handle, BOOLEAN ignore_rfc_state, BD_ADDR bd_addr,
                                 UINT16 *p_lcid);

/*******************************************************************************
** 函数PORT_IsOpen
**
** 说明如果正在打开任何RFCOMM连接，则此函数返回TRUE。
**
** 参数：如果发现对等方的bd_addr-bd_addr存在任何连接打开，则为TRUE
**
*******************************************************************************/
extern BOOLEAN PORT_IsOpening (BD_ADDR bd_addr);

/*******************************************************************************
** 函数PORT_SetState
**
** 说明此函数根据tPORT_STATE结构中的规范配置连接。
**
** 参数：handle-RFCOMM_CreateConnection p_settings中返回的句柄-指向包含连接配置信息的tPORT_STATE结构的指针。
**
*******************************************************************************/
extern int PORT_SetState (UINT16 handle, tPORT_STATE *p_settings);

/*******************************************************************************
** 函数PORT_GetRxQueueCnt
**
** 说明此函数返回rx队列上的缓冲区数。
**
** 参数：handle-RFCOMM_CreateConnection p_rx_queue_count中返回的句柄-中返回队列计数的指针。
**
*******************************************************************************/
extern int PORT_GetRxQueueCnt (UINT16 handle, UINT16 *p_rx_queue_count);

/*******************************************************************************
** 函数PORT_GetState
**
** 说明调用此函数以使用端口的当前控制设置填充tPORT_STATE结构
**
** 参数：handle-RFCOMM_CreateConnection p_settings中返回的句柄-返回配置信息的tPORT_STATE结构的指针。
**
*******************************************************************************/
extern int PORT_GetState (UINT16 handle, tPORT_STATE *p_settings);


/*******************************************************************************
** 功能PORT_Control
**
** 描述此函数指导指定的连接将控制控制信息传递给对等设备。
**
** 参数：handle-RFCOMM_CreateConnection信号中返回的句柄-指定要传递的函数
**
*******************************************************************************/
#define PORT_SET_DTRDSR         0x01
#define PORT_CLR_DTRDSR         0x02
#define PORT_SET_CTSRTS         0x03
#define PORT_CLR_CTSRTS         0x04
#define PORT_SET_RI             0x05        /* 仅DCE*/
#define PORT_CLR_RI             0x06        /* 仅DCE*/
#define PORT_SET_DCD            0x07        /* 仅DCE*/
#define PORT_CLR_DCD            0x08        /* 仅DCE*/
#define PORT_BREAK              0x09        /* 中断事件*/

extern int PORT_Control (UINT16 handle, UINT8 signal);


/*******************************************************************************
** 函数PORT_FlowControl
**
** 描述此函数指导指定的连接将流控制消息传递给对等设备。传递的启用标志显示端口是否可以接受更多数据。
**
** 参数：handle-RFCOMM_CreateConnection enable中返回的句柄-启用数据流
**
*******************************************************************************/
extern int PORT_FlowControl (UINT16 handle, BOOLEAN enable);

/*******************************************************************************
** 函数PORT_FlowControl_GiveCredit
**
** 说明此功能为对等方提供指定的积分
**
** 参数：handle-RFCOMM_CreateConnection enable中返回的句柄-enables data flow credits_given-credits to give
**
*******************************************************************************/
extern int PORT_FlowControl_GiveCredit (UINT16 handle, BOOLEAN enable, UINT16 credits_given);
/*******************************************************************************
** 函数PORT_GetModemStatus
**
** 说明此功能检索调制解调器控制信号。通常，在回调函数被调用后，应用程序将调用此函数，并通知其中一个信号已更改。
**
** 参数：handle-RFCOMM_CreateConnection回调中返回的句柄。p_signal-指定指向控制信号信息的指针
**
*******************************************************************************/
#define PORT_DTRDSR_ON          0x01
#define PORT_CTSRTS_ON          0x02
#define PORT_RING_ON            0x04
#define PORT_DCD_ON             0x08

/*
** 定义连接建立后的默认初始本地调制解调器信号状态集
*/
#define PORT_OBEX_DEFAULT_SIGNAL_STATE  (PORT_DTRDSR_ON | PORT_CTSRTS_ON | PORT_DCD_ON)
#define PORT_SPP_DEFAULT_SIGNAL_STATE   (PORT_DTRDSR_ON | PORT_CTSRTS_ON | PORT_DCD_ON)
#define PORT_PPP_DEFAULT_SIGNAL_STATE   (PORT_DTRDSR_ON | PORT_CTSRTS_ON | PORT_DCD_ON)
#define PORT_DUN_DEFAULT_SIGNAL_STATE   (PORT_DTRDSR_ON | PORT_CTSRTS_ON)

extern int PORT_GetModemStatus (UINT16 handle, UINT8 *p_control_signal);


/*******************************************************************************
** 函数PORT_ClearError
**
** 描述此函数检索有关通信错误的信息并报告连接的当前状态。当发生错误时，应调用该函数以清除连接错误标志并启用其他读写操作。
**
** 参数：handle-RFCOMM_CreateConnection中返回的句柄p_errors-接收错误代码的变量指针p_status-接收连接状态的tPORT_status结构指针
**
*******************************************************************************/

#define PORT_ERR_BREAK      0x01    /* 对等设备上出现中断情况*/
#define PORT_ERR_OVERRUN    0x02    /* 对等设备报告溢出*/
#define PORT_ERR_FRAME      0x04    /* 对等设备报告的帧错误*/
#define PORT_ERR_RXOVER     0x08    /* 发生输入队列溢出*/
#define PORT_ERR_TXFULL     0x10    /* 发生输出队列溢出*/

typedef struct {
#define PORT_FLAG_CTS_HOLD  0x01    /* Tx正在等待CTS信号*/
#define PORT_FLAG_DSR_HOLD  0x02    /* Tx正在等待DSR信号*/
#define PORT_FLAG_RLSD_HOLD 0x04    /* Tx正在等待RLSD信号*/

    UINT16  flags;
    UINT16  in_queue_size;          /* 输入队列中的字节数*/
    UINT16  out_queue_size;         /* 输出队列中的字节数*/
    UINT16  mtu_size;               /* 对等MTU大小*/
} tPORT_STATUS;


extern int PORT_ClearError (UINT16 handle, UINT16 *p_errors,
                            tPORT_STATUS *p_status);


/*******************************************************************************
** 函数PORT_SendError
**
** 说明此功能向对等设备发送通信错误
**
** 参数：handle-RFCOMM_CreateConnection错误中返回的句柄-接收错误代码
**
*******************************************************************************/
extern int PORT_SendError (UINT16 handle, UINT8 errors);


/*******************************************************************************
** 函数PORT_GetQueueStatus
**
** 说明此函数报告连接的当前状态。
**
** 参数：handle-RFCOMM_CreateConnection p_status中返回的句柄-指向tPORT_status结构以接收连接状态的指针
**
*******************************************************************************/
extern int PORT_GetQueueStatus (UINT16 handle, tPORT_STATUS *p_status);


/*******************************************************************************
** 函数PORT_Purge
**
** 说明此函数丢弃指定连接的输出或输入队列中的所有数据。
**
** 参数：handle-RFCOMM_CreateConnection purge_flags中返回的句柄-指定要执行的操作。
**
*******************************************************************************/
#define PORT_PURGE_TXCLEAR  0x01
#define PORT_PURGE_RXCLEAR  0x02

extern int PORT_Purge (UINT16 handle, UINT8 purge_flags);


/*******************************************************************************
** 函数PORT_Read
**
** 说明此函数返回从对等设备接收的缓冲区指针。通常，应用程序在收到PORT_EVT_RXCHAR事件后将调用此函数。调用此函数的应用程序负责释放返回的缓冲区。
**
** 参数：handle-RFCOMM_CreateConnection回调中返回的句柄。pp_buf-指向数据缓冲区地址的指针，
**
*******************************************************************************/
extern int PORT_Read (UINT16 handle, BT_HDR **pp_buf);


/*******************************************************************************
** 函数PORT_ReadData
**
** 说明正常情况下，应用程序将在收到PORT_EVT_RXCHAR事件后调用此函数。
**
** 参数：handle-RFCOMM_CreateConnection回调中返回的句柄。p_data-数据区域max_len-请求的字节计数p_len-接收的字节计数
**
*******************************************************************************/
extern int PORT_ReadData (UINT16 handle, char *p_data, UINT16 max_len,
                          UINT16 *p_len);


/*******************************************************************************
** 函数PORT_Write
**
** 说明此功能用于向对等设备发送BT缓冲区。应用程序不应释放缓冲区。
**
** 参数：handle-RFCOMM_CreateConnection p_buf中返回的句柄-指向缓冲区的指针，
**
*******************************************************************************/
extern int PORT_Write (UINT16 handle, BT_HDR *p_buf);


/*******************************************************************************
** 函数PORT_WriteData
**
** 说明从旧版应用程序调用此函数以发送数据。
**
** 参数：handle-RFCOMM_CreateConnection中返回的句柄p_data-数据区域max_len-要写入的字节数p_len-写入的字节
**
*******************************************************************************/
extern int PORT_WriteData (UINT16 handle, char *p_data, UINT16 max_len,
                           UINT16 *p_len);

/*******************************************************************************
** 函数PORT_WriteDataCO
**
** 说明通常不支持GKI的应用程序将调用此函数，通过调用函数将数据发送到端口。
**
** 参数：handle-RFCOMM_CreateConnection中返回的句柄
**
*******************************************************************************/
extern int PORT_WriteDataCO (UINT16 handle, int *p_len, int len, UINT8 *p_data);

/*******************************************************************************
** 函数PORT_Test
**
** 说明应用程序可以调用此函数来发送RFCOMM测试帧
**
** 参数：handle-RFCOMM_CreateConnection p_data中返回的句柄-数据区域max_len-请求的字节数
**
*******************************************************************************/
extern int PORT_Test (UINT16 handle, UINT8 *p_data, UINT16 len);


/*******************************************************************************
** 函数RFCOMM_Init
**
** 描述调用此函数以初始化RFCOMM层
**
*******************************************************************************/
extern bt_status_t RFCOMM_Init (void);

/*******************************************************************************
** 函数RFCOMM_init
**
** 说明调用此函数以取消初始化此层的控制块。
**
** 返回void
**
*******************************************************************************/
extern void RFCOMM_Deinit(void);

/*******************************************************************************
** 函数PORT_SetTraceLevel
**
** 说明此函数设置RFCOMM的跟踪级别。如果用0xFF值调用，它只读取当前跟踪级别。
**
** 返回新的（当前）跟踪级别
**
*******************************************************************************/
extern UINT8 PORT_SetTraceLevel (UINT8 new_level);


/*******************************************************************************
** 函数PORT_GetResultString
**
** 说明此函数返回给定结果代码的可读字符串。
**
** 返回指向给定结果的可读字符串的指针。请注意，返回的字符串不能被释放。
**
*******************************************************************************/
extern const char *PORT_GetResultString (const uint8_t result_code);

#ifdef __cplusplus
}
#endif

#endif  /* PORT_API_H */

