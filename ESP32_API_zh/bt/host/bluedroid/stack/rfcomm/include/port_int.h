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

/*****************************************************************************
 * 此文件包含PORT单元内部的定义
 *
 *****************************************************************************/

#ifndef PORT_INT_H
#define PORT_INT_H

#include "common/bt_target.h"
#include "stack/rfcdefs.h"
#include "stack/port_api.h"
#include "osi/fixed_queue.h"
#include "common/bt_defs.h"

/* 应用程序事件从api发送到PORT时传递的本地事件*/
/* ???*/
#define PORT_EVENT_OPEN         (1  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_CONTROL      (2  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_SET_STATE    (3  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_SET_CALLBACK (5  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_WRITE        (6  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_PURGE        (7  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_SEND_ERROR   (8  | BT_EVT_TO_BTU_SP_EVT)
#define PORT_EVENT_FLOW_CONTROL (9  | BT_EVT_TO_BTU_SP_EVT)

/*
** 多路复用器的流量控制配置值
*/
#define PORT_FC_UNDEFINED       0   /* 多路复用流控制机制尚未定义*/
#define PORT_FC_TS710           1   /* 使用TS 07.10流量控制*/
#define PORT_FC_CREDIT          2   /* 使用基于RFCOMM信用的流量控制*/

/*
** 定义端口数据传输控制块
*/
typedef struct {
    fixed_queue_t *queue;         /* 等待发送的缓冲区队列*/
    BOOLEAN  peer_fc;       /* 如果基于对等方的请求设置了流控制，则为TRUE*/
    BOOLEAN  user_fc;       /* 如果根据用户的请求设置了流量控制，则为TRUE*/
    UINT32   queue_size;    /* 队列中的数据字节数*/
    tPORT_CALLBACK *p_callback;  /* 回调函数的地址*/
} tPORT_DATA;

/*
** 用于传递调制解调器信息的端口控制结构
*/
typedef struct {
#define MODEM_SIGNAL_DTRDSR        0x01
#define MODEM_SIGNAL_RTSCTS        0x02
#define MODEM_SIGNAL_RI            0x04
#define MODEM_SIGNAL_DCD           0x08

    UINT8   modem_signal;       /* [DTR/DSR | RTS/CTS | RI | DCD ] */

    UINT8   break_signal;       /* 0-3秒，步长为200毫秒*/

    UINT8   discard_buffers;    /* 0-不丢弃，1-丢弃*/

#define RFCOMM_CTRL_BREAK_ASAP      0
#define RFCOMM_CTRL_BREAK_IN_SEQ    1

    UINT8   break_signal_seq;   /* 尽快|按顺序（默认）*/

    BOOLEAN fc;                 /* 当设备无法接受帧时为TRUE*/
} tPORT_CTRL;


/*
** RFCOMM多路复用器控制块
*/
typedef struct {
    TIMER_LIST_ENT tle;       /* 计时器列表条目*/
    fixed_queue_t  *cmd_q;          /* 此多路复用器上的命令消息队列*/
    UINT8     port_inx[RFCOMM_MAX_DLCI + 1];  /* 用于快速访问的阵列*/
    /* 基于dlci的tPORT*/
    BD_ADDR   bd_addr;        /* 如果启动器，则为对等方的BD ADDR*/
    UINT16    lcid;           /* 用于此通道的本地cid*/
    UINT16    peer_l2cap_mtu; /* 可发送到对等L2CAP的最大帧数*/
    UINT8     state;          /* 当前多路复用器通道状态*/
    UINT8     is_initiator;   /* 如果该侧发送SABME（dlci=0），则为TRUE*/
    BOOLEAN   local_cfg_sent;
    BOOLEAN   peer_cfg_rcvd;
    BOOLEAN   restart_required; /* 如果必须在光盘后重新启动频道，则为TRUE*/
    BOOLEAN   peer_ready;      /* 如果另一侧可以接受帧，则为True*/
    UINT8     flow;            /* 此多路复用器的流量控制机制*/
    BOOLEAN   l2cap_congested; /* 如果L2CAP拥塞，则为TRUE*/
    BOOLEAN   is_disc_initiator; /* 如果端口的磁盘已启动，则为TRUE*/
    UINT16    pending_lcid;    /* 连接时存储传入连接的LCID*/
    UINT8     pending_id;      /* 连接时为传入连接存储l2cap ID*/
} tRFC_MCB;


/*
** RFCOMM端口连接控制块
*/
struct t_rfc_port {
#define RFC_PORT_STATE_IDLE          0
#define RFC_PORT_STATE_WAIT_START    1
#define RFC_PORT_STATE_OPENING       2
#define RFC_PORT_STATE_OPENED        3
#define RFC_PORT_STATE_CLOSING       4

    UINT8     state;          /* 连接的当前状态*/

#define RFC_RSP_PN                  0x01
#define RFC_RSP_RPN_REPLY           0x02
#define RFC_RSP_RPN                 0x04
#define RFC_RSP_MSC                 0x08
#define RFC_RSP_RLS                 0x10

    UINT8    expected_rsp;

    tRFC_MCB *p_mcb;

    TIMER_LIST_ENT tle;       /* 计时器列表条目*/
};
typedef struct t_rfc_port tRFC_PORT;


/*
** 定义包含PORT连接信息的控制块
*/
struct t_port_info {
    UINT8   inx;            /* port_info数组中此控制块的索引*/
    BOOLEAN in_use;         /* 分配结构时为True*/

#define PORT_STATE_CLOSED   0
#define PORT_STATE_OPENING  1
#define PORT_STATE_OPENED   2
#define PORT_STATE_CLOSING  3

    UINT8   state;          /* 应用程序状态*/

    UINT8   scn;            /* 服务通道编号*/
    UINT16  uuid;           /* 服务UUID*/

    BD_ADDR bd_addr;        /* 多路复用器通道设备的BD ADDR*/
    BOOLEAN is_server;      /* 如果服务器应用程序为TRUE*/
    UINT8   dlci;           /* 连接的DLCI*/

    UINT8   error;          /* 检测到最后一个错误*/

    UINT8   line_status;    /* 同行报告的线路状态*/

    UINT8   default_signal_state; /* 初始信号状态取决于uuid*/

    UINT16  mtu;            /* 端口可以接收的最大MTU*/
    UINT16  peer_mtu;       /* 端口可以发送的最大MTU*/

    tPORT_DATA tx;          /* 从应用程序到对等程序的数据控制块*/
    tPORT_DATA rx;          /* 对等应用数据的控制块*/

    tPORT_STATE user_port_pars;  /* 用户连接的端口参数*/
    tPORT_STATE peer_port_pars;  /* 用户连接的端口参数*/

    tPORT_CTRL  local_ctrl;
    tPORT_CTRL  peer_ctrl;

#define PORT_CTRL_REQ_SENT          0x01
#define PORT_CTRL_REQ_CONFIRMED     0x02
#define PORT_CTRL_IND_RECEIVED      0x04
#define PORT_CTRL_IND_RESPONDED     0x08

    UINT8       port_ctrl;                  /* 调制解调器状态命令*/

    BOOLEAN     rx_flag_ev_pending;         /* 接收到RXFLAG字符*/

    tRFC_PORT   rfc;                        /* RFCOMM端口控制块*/

    UINT32      ev_mask;                    /* 回调的事件掩码*/
    tPORT_CALLBACK      *p_callback;        /* 指向用户回调函数的指针*/
    tPORT_MGMT_CALLBACK *p_mgmt_callback;   /* 回调函数，用于接收上/下连接*/
    tPORT_DATA_CALLBACK *p_data_callback;   /* 接收数据指示的回调函数*/
    tPORT_DATA_CO_CALLBACK *p_data_co_callback;   /* 带callout和flowctrl的回调函数*/
    UINT16      credit_tx;                  /* tx路径的流量控制积分*/
    UINT16      credit_rx;                  /* rx路径的流量控制积分，这是*/
    /* 允许对等发送的缓冲区数*/
    UINT16      credit_rx_max;              /* 我们将允许此人发送的最大点数*/
    UINT16      credit_rx_low;              /* 发送信用更新时的信用数*/
    UINT16      rx_buf_critical;            /* 端口接收队列关键水印级别*/
    BOOLEAN     keep_port_handle;           /* 如果关闭时端口未解除分配，则为TRUE*/
    /* 在分配端口时，服务器将其设置为TRUE*/
    UINT16      keep_mtu;                   /* 服务器可以接收的端口最大MTU*/
};
typedef struct t_port_info tPORT;


/* 定义PORT/RFCOMM控制结构
*/
typedef struct {
    tPORT        port[MAX_RFC_PORTS];            /* 端口信息池*/
    tRFC_MCB     rfc_mcb[MAX_BD_CONNECTIONS];    /* RFCOMM bd_connections池*/
} tPORT_CB;

#ifdef __cplusplus
extern "C" {
#endif

/*
** port_utils.c提供的函数
*/
extern tPORT    *port_allocate_port (UINT8 dlci, BD_ADDR bd_addr);
extern void     port_set_defaults (tPORT *p_port);
extern void     port_select_mtu (tPORT *p_port);
extern void     port_release_port (tPORT *p_port);
extern tPORT    *port_find_mcb_dlci_port (tRFC_MCB *p_mcb, UINT8 dlci);
extern tRFC_MCB *port_find_mcb (BD_ADDR bd_addr);
extern tPORT    *port_find_dlci_port (UINT8 dlci);
extern tPORT    *port_find_port (UINT8 dlci, BD_ADDR bd_addr);
extern UINT32   port_get_signal_changes (tPORT *p_port, UINT8 old_signals, UINT8 signal);
extern UINT32   port_flow_control_user (tPORT *p_port);
extern void     port_flow_control_peer(tPORT *p_port, BOOLEAN enable, UINT16 count);

/*
** port_rfc.c提供的函数
*/
extern int  port_open_continue (tPORT *p_port);
extern void port_start_port_open (tPORT *p_port);
extern void port_start_par_neg (tPORT *p_port);
extern void port_start_control (tPORT *p_port);
extern void port_start_close (tPORT *p_port);
extern void port_rfc_closed (tPORT *p_port, UINT8 res);

#ifdef __cplusplus
}
#endif

#endif

