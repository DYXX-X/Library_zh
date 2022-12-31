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
 * 此文件包含AVDTP内部的接口。
 *
 ******************************************************************************/
#ifndef AVDT_INT_H
#define AVDT_INT_H

#include "stack/avdt_api.h"
#include "stack/avdtc_api.h"
#include "avdt_defs.h"
#include "stack/l2c_api.h"
#include "stack/btm_api.h"
#include "osi/fixed_queue.h"

#if (AVRC_INCLUDED == TRUE)

#ifndef AVDT_DEBUG
#define AVDT_DEBUG  FALSE
#endif

/*****************************************************************************
** 常量
*****************************************************************************/

/* 渠道类型*/
enum {
    AVDT_CHAN_SIG,                  /* 信令信道*/
    AVDT_CHAN_MEDIA,                /* 媒体频道*/
#if AVDT_REPORTING == TRUE
    AVDT_CHAN_REPORT,               /* 报告渠道*/
#endif
    AVDT_CHAN_NUM_TYPES
};

/* AVDTP实现的协议服务能力*/
/* 目前，多路复用仅用于分段*/
#if ((AVDT_MULTIPLEXING == TRUE) && (AVDT_REPORTING == TRUE))
#define AVDT_PSC                (AVDT_PSC_TRANS | AVDT_PSC_MUX | AVDT_PSC_REPORT | AVDT_PSC_DELAY_RPT)
#define AVDT_LEG_PSC            (AVDT_PSC_TRANS | AVDT_PSC_MUX | AVDT_PSC_REPORT)
#else /* AVDT_MULTIPLEXING && AVDT_REPORTING  */

#if (AVDT_MULTIPLEXING == TRUE)
#define AVDT_PSC                (AVDT_PSC_TRANS | AVDT_PSC_MUX | AVDT_PSC_DELAY_RPT)
#define AVDT_LEG_PSC            (AVDT_PSC_TRANS | AVDT_PSC_MUX)
#else /* AVDT_MULTIPLEXING */

#if (AVDT_REPORTING == TRUE)
#define AVDT_PSC                (AVDT_PSC_TRANS | AVDT_PSC_REPORT | AVDT_PSC_DELAY_RPT)
#define AVDT_LEG_PSC            (AVDT_PSC_TRANS | AVDT_PSC_REPORT)
#else /* AVDT_REPORTING  */
#define AVDT_PSC                (AVDT_PSC_TRANS | AVDT_PSC_DELAY_RPT)
#define AVDT_LEG_PSC            (AVDT_PSC_TRANS)
#endif /* AVDT_REPORTING  */

#endif /* AVDT_MULTIPLEXING */

#endif /* AVDT_MULTIPLEXING && AVDT_REPORTING  */

/* 引发剂/受体信号作用*/
#define AVDT_CLOSE_ACP          0
#define AVDT_CLOSE_INT          1
#define AVDT_OPEN_ACP           2
#define AVDT_OPEN_INT           3

/* avdt_scb_verify的状态*/
#define AVDT_VERIFY_OPEN        0
#define AVDT_VERIFY_STREAMING   1
#define AVDT_VERIFY_SUSPEND     2
#define AVDT_VERIFY_START       3

/* 区分CCB事件和SCB事件*/
#define AVDT_CCB_MKR            0x80

/* AVDTP信令消息头在消息中开始的偏移*/
#define AVDT_HDR_OFFSET         (L2CAP_MIN_OFFSET + AVDT_NUM_SEPS)

/* AVDTP信令消息内容开始的偏移；使用起始标头的大小，因为它是缓冲区中信令消息的最大可能布局：
**
** |BT_HDR | SCB句柄| L2CAP+HCI标头| AVDTP标头|数据|
**
** 注意，我们在消息缓冲区的顶部“隐藏”scb句柄。
*/
#define AVDT_MSG_OFFSET         (L2CAP_MIN_OFFSET + AVDT_NUM_SEPS + AVDT_LEN_TYPE_START)

/* scb传输通道连接超时值*/
#define AVDT_SCB_TC_CONN_TOUT   10

/* scb传输通道断开连接超时值*/
#define AVDT_SCB_TC_DISC_TOUT   10

/* 命令重传的最大次数*/
#ifndef AVDT_RET_MAX
#define AVDT_RET_MAX            1
#endif


/* ccb状态机状态*/
enum {
    AVDT_CCB_IDLE_ST,
    AVDT_CCB_OPENING_ST,
    AVDT_CCB_OPEN_ST,
    AVDT_CCB_CLOSING_ST
};

/* 状态机操作枚举列表*/
enum {
    AVDT_CCB_CHAN_OPEN,
    AVDT_CCB_CHAN_CLOSE,
    AVDT_CCB_CHK_CLOSE,
    AVDT_CCB_HDL_DISCOVER_CMD,
    AVDT_CCB_HDL_DISCOVER_RSP,
    AVDT_CCB_HDL_GETCAP_CMD,
    AVDT_CCB_HDL_GETCAP_RSP,
    AVDT_CCB_HDL_START_CMD,
    AVDT_CCB_HDL_START_RSP,
    AVDT_CCB_HDL_SUSPEND_CMD,
    AVDT_CCB_HDL_SUSPEND_RSP,
    AVDT_CCB_SND_DISCOVER_CMD,
    AVDT_CCB_SND_DISCOVER_RSP,
    AVDT_CCB_SND_GETCAP_CMD,
    AVDT_CCB_SND_GETCAP_RSP,
    AVDT_CCB_SND_START_CMD,
    AVDT_CCB_SND_START_RSP,
    AVDT_CCB_SND_SUSPEND_CMD,
    AVDT_CCB_SND_SUSPEND_RSP,
    AVDT_CCB_CLEAR_CMDS,
    AVDT_CCB_CMD_FAIL,
    AVDT_CCB_FREE_CMD,
    AVDT_CCB_CONG_STATE,
    AVDT_CCB_RET_CMD,
    AVDT_CCB_SND_CMD,
    AVDT_CCB_SND_MSG,
    AVDT_CCB_SET_RECONN,
    AVDT_CCB_CLR_RECONN,
    AVDT_CCB_CHK_RECONN,
    AVDT_CCB_CHK_TIMER,
    AVDT_CCB_SET_CONN,
    AVDT_CCB_SET_DISCONN,
    AVDT_CCB_DO_DISCONN,
    AVDT_CCB_LL_CLOSED,
    AVDT_CCB_LL_OPENED,
    AVDT_CCB_DEALLOC,
    AVDT_CCB_NUM_ACTIONS
};

#define AVDT_CCB_IGNORE     AVDT_CCB_NUM_ACTIONS

/* ccb状态机事件*/
enum {
    AVDT_CCB_API_DISCOVER_REQ_EVT,
    AVDT_CCB_API_GETCAP_REQ_EVT,
    AVDT_CCB_API_START_REQ_EVT,
    AVDT_CCB_API_SUSPEND_REQ_EVT,
    AVDT_CCB_API_DISCOVER_RSP_EVT,
    AVDT_CCB_API_GETCAP_RSP_EVT,
    AVDT_CCB_API_START_RSP_EVT,
    AVDT_CCB_API_SUSPEND_RSP_EVT,
    AVDT_CCB_API_CONNECT_REQ_EVT,
    AVDT_CCB_API_DISCONNECT_REQ_EVT,
    AVDT_CCB_MSG_DISCOVER_CMD_EVT,
    AVDT_CCB_MSG_GETCAP_CMD_EVT,
    AVDT_CCB_MSG_START_CMD_EVT,
    AVDT_CCB_MSG_SUSPEND_CMD_EVT,
    AVDT_CCB_MSG_DISCOVER_RSP_EVT,
    AVDT_CCB_MSG_GETCAP_RSP_EVT,
    AVDT_CCB_MSG_START_RSP_EVT,
    AVDT_CCB_MSG_SUSPEND_RSP_EVT,
    AVDT_CCB_RCVRSP_EVT,
    AVDT_CCB_SENDMSG_EVT,
    AVDT_CCB_RET_TOUT_EVT,
    AVDT_CCB_RSP_TOUT_EVT,
    AVDT_CCB_IDLE_TOUT_EVT,
    AVDT_CCB_UL_OPEN_EVT,
    AVDT_CCB_UL_CLOSE_EVT,
    AVDT_CCB_LL_OPEN_EVT,
    AVDT_CCB_LL_CLOSE_EVT,
    AVDT_CCB_LL_CONG_EVT
};


/* scb状态机状态；这些状态值对此模块是私有的，因此操作函数无法读取或设置scb状态
*/
enum {
    AVDT_SCB_IDLE_ST,
    AVDT_SCB_CONF_ST,
    AVDT_SCB_OPENING_ST,
    AVDT_SCB_OPEN_ST,
    AVDT_SCB_STREAM_ST,
    AVDT_SCB_CLOSING_ST
};

/* 状态机操作枚举列表*/
enum {
    AVDT_SCB_HDL_ABORT_CMD,
    AVDT_SCB_HDL_ABORT_RSP,
    AVDT_SCB_HDL_CLOSE_CMD,
    AVDT_SCB_HDL_CLOSE_RSP,
    AVDT_SCB_HDL_GETCONFIG_CMD,
    AVDT_SCB_HDL_GETCONFIG_RSP,
    AVDT_SCB_HDL_OPEN_CMD,
    AVDT_SCB_HDL_OPEN_REJ,
    AVDT_SCB_HDL_OPEN_RSP,
    AVDT_SCB_HDL_PKT,
    AVDT_SCB_DROP_PKT,
    AVDT_SCB_HDL_RECONFIG_CMD,
    AVDT_SCB_HDL_RECONFIG_RSP,
    AVDT_SCB_HDL_SECURITY_CMD,
    AVDT_SCB_HDL_SECURITY_RSP,
    AVDT_SCB_HDL_SETCONFIG_CMD,
    AVDT_SCB_HDL_SETCONFIG_REJ,
    AVDT_SCB_HDL_SETCONFIG_RSP,
    AVDT_SCB_HDL_START_CMD,
    AVDT_SCB_HDL_START_RSP,
    AVDT_SCB_HDL_SUSPEND_CMD,
    AVDT_SCB_HDL_SUSPEND_RSP,
    AVDT_SCB_HDL_TC_CLOSE,
#if AVDT_REPORTING == TRUE
    AVDT_SCB_HDL_TC_CLOSE_STO,
#endif
    AVDT_SCB_HDL_TC_OPEN,
#if AVDT_REPORTING == TRUE
    AVDT_SCB_HDL_TC_OPEN_STO,
#endif
    AVDT_SCB_SND_DELAY_RPT_REQ,
    AVDT_SCB_HDL_DELAY_RPT_CMD,
    AVDT_SCB_HDL_DELAY_RPT_RSP,
    AVDT_SCB_HDL_WRITE_REQ,
    AVDT_SCB_SND_ABORT_REQ,
    AVDT_SCB_SND_ABORT_RSP,
    AVDT_SCB_SND_CLOSE_REQ,
    AVDT_SCB_SND_STREAM_CLOSE,
    AVDT_SCB_SND_CLOSE_RSP,
    AVDT_SCB_SND_GETCONFIG_REQ,
    AVDT_SCB_SND_GETCONFIG_RSP,
    AVDT_SCB_SND_OPEN_REQ,
    AVDT_SCB_SND_OPEN_RSP,
    AVDT_SCB_SND_RECONFIG_REQ,
    AVDT_SCB_SND_RECONFIG_RSP,
    AVDT_SCB_SND_SECURITY_REQ,
    AVDT_SCB_SND_SECURITY_RSP,
    AVDT_SCB_SND_SETCONFIG_REQ,
    AVDT_SCB_SND_SETCONFIG_REJ,
    AVDT_SCB_SND_SETCONFIG_RSP,
    AVDT_SCB_SND_TC_CLOSE,
    AVDT_SCB_CB_ERR,
    AVDT_SCB_CONG_STATE,
    AVDT_SCB_REJ_STATE,
    AVDT_SCB_REJ_IN_USE,
    AVDT_SCB_REJ_NOT_IN_USE,
    AVDT_SCB_SET_REMOVE,
    AVDT_SCB_FREE_PKT,
    AVDT_SCB_CLR_PKT,
    AVDT_SCB_CHK_SND_PKT,
    AVDT_SCB_TC_TIMER,
    AVDT_SCB_CLR_VARS,
    AVDT_SCB_DEALLOC,
    AVDT_SCB_NUM_ACTIONS
};

#define AVDT_SCB_IGNORE     AVDT_SCB_NUM_ACTIONS

/* scb状态机事件*/
enum {
    AVDT_SCB_API_REMOVE_EVT,
    AVDT_SCB_API_WRITE_REQ_EVT,
    AVDT_SCB_API_GETCONFIG_REQ_EVT,
    AVDT_SCB_API_DELAY_RPT_REQ_EVT,
    AVDT_SCB_API_SETCONFIG_REQ_EVT,
    AVDT_SCB_API_OPEN_REQ_EVT,
    AVDT_SCB_API_CLOSE_REQ_EVT,
    AVDT_SCB_API_RECONFIG_REQ_EVT,
    AVDT_SCB_API_SECURITY_REQ_EVT,
    AVDT_SCB_API_ABORT_REQ_EVT,
    AVDT_SCB_API_GETCONFIG_RSP_EVT,
    AVDT_SCB_API_SETCONFIG_RSP_EVT,
    AVDT_SCB_API_SETCONFIG_REJ_EVT,
    AVDT_SCB_API_OPEN_RSP_EVT,
    AVDT_SCB_API_CLOSE_RSP_EVT,
    AVDT_SCB_API_RECONFIG_RSP_EVT,
    AVDT_SCB_API_SECURITY_RSP_EVT,
    AVDT_SCB_API_ABORT_RSP_EVT,
    AVDT_SCB_MSG_SETCONFIG_CMD_EVT,
    AVDT_SCB_MSG_GETCONFIG_CMD_EVT,
    AVDT_SCB_MSG_OPEN_CMD_EVT,
    AVDT_SCB_MSG_START_CMD_EVT,
    AVDT_SCB_MSG_SUSPEND_CMD_EVT,
    AVDT_SCB_MSG_CLOSE_CMD_EVT,
    AVDT_SCB_MSG_ABORT_CMD_EVT,
    AVDT_SCB_MSG_RECONFIG_CMD_EVT,
    AVDT_SCB_MSG_SECURITY_CMD_EVT,
    AVDT_SCB_MSG_DELAY_RPT_CMD_EVT,
    AVDT_SCB_MSG_DELAY_RPT_RSP_EVT,
    AVDT_SCB_MSG_SETCONFIG_RSP_EVT,
    AVDT_SCB_MSG_GETCONFIG_RSP_EVT,
    AVDT_SCB_MSG_OPEN_RSP_EVT,
    AVDT_SCB_MSG_START_RSP_EVT,
    AVDT_SCB_MSG_SUSPEND_RSP_EVT,
    AVDT_SCB_MSG_CLOSE_RSP_EVT,
    AVDT_SCB_MSG_ABORT_RSP_EVT,
    AVDT_SCB_MSG_RECONFIG_RSP_EVT,
    AVDT_SCB_MSG_SECURITY_RSP_EVT,
    AVDT_SCB_MSG_SETCONFIG_REJ_EVT,
    AVDT_SCB_MSG_OPEN_REJ_EVT,
    AVDT_SCB_MSG_START_REJ_EVT,
    AVDT_SCB_MSG_SUSPEND_REJ_EVT,
    AVDT_SCB_TC_TOUT_EVT,
    AVDT_SCB_TC_OPEN_EVT,
    AVDT_SCB_TC_CLOSE_EVT,
    AVDT_SCB_TC_CONG_EVT,
    AVDT_SCB_TC_DATA_EVT,
    AVDT_SCB_CC_CLOSE_EVT
};

/* 流路由表条目的自适应层数*/
#if AVDT_REPORTING == TRUE
/* 每个SEP 2个信道（1个媒体，1个报告），一个用于信令*/
#define AVDT_NUM_RT_TBL     ((AVDT_NUM_SEPS<<1) + 1)
#else
#define AVDT_NUM_RT_TBL     (AVDT_NUM_SEPS + 1)
#endif

/* 传输信道表项的适应层数量-移动到目标。h#定义AVDT_NUM_TC_TBL（AVDT_NUM_SEPS+AVTT_NUM_LINKS）*/

/* 传输通道表中使用的“状态”*/
#define AVDT_AD_ST_UNUSED   0       /* 未使用-未分配*/
#define AVDT_AD_ST_IDLE     1       /* 无连接*/
#define AVDT_AD_ST_ACP      2       /* 正在等待接受连接*/
#define AVDT_AD_ST_INT      3       /* 启动连接*/
#define AVDT_AD_ST_CONN     4       /* 正在等待连接确认*/
#define AVDT_AD_ST_CFG      5       /* 正在等待配置完成*/
#define AVDT_AD_ST_OPEN     6       /* 通道已打开*/
#define AVDT_AD_ST_SEC_INT  7       /* 作为INT的安全流程*/
#define AVDT_AD_ST_SEC_ACP  8       /* 作为ACP的安全流程*/

/* 配置标志。tAVDT_TC_TBL.cfg_标记*/
#define AVDT_L2C_CFG_IND_DONE   (1<<0)
#define AVDT_L2C_CFG_CFM_DONE   (1<<1)
#define AVDT_L2C_CFG_CONN_INT   (1<<2)
#define AVDT_L2C_CFG_CONN_ACP   (1<<3)


/* avdt_ad_write_req（）的结果代码（L2CA_DataWrite（））*/
#define AVDT_AD_FAILED       L2CAP_DW_FAILED        /* FALSE */
#define AVDT_AD_SUCCESS      L2CAP_DW_SUCCESS       /* TRUE */
#define AVDT_AD_CONGESTED    L2CAP_DW_CONGESTED     /* 2 */

/*****************************************************************************
** 数据类型
*****************************************************************************/

/* 所有消息参数类型的消息联合*/
typedef union {
    tAVDT_EVT_HDR           hdr;
    tAVDT_EVT_HDR           single;
    tAVDT_SETCONFIG         config_cmd;
    tAVDT_CONFIG            reconfig_cmd;
    tAVDT_MULTI             multi;
    tAVDT_SECURITY          security_cmd;
    tAVDT_DISCOVER          discover_rsp;
    tAVDT_CONFIG            svccap;
    tAVDT_SECURITY          security_rsp;
    tAVDT_DELAY_RPT         delay_rpt_cmd;
} tAVDT_MSG;

/* AVDT_CCB_API_DISCOVER_REQ_EVT的数据类型*/
typedef struct {
    tAVDT_CTRL_CBACK    *p_cback;
    tAVDT_SEP_INFO      *p_sep_info;
    UINT8               num_seps;
} tAVDT_CCB_API_DISCOVER;

/* AVDT_CCB_API_GETCAP_REQ_EVT的数据类型*/
typedef struct {
    tAVDT_EVT_HDR       single;
    tAVDT_CTRL_CBACK    *p_cback;
    tAVDT_CFG           *p_cfg;
} tAVDT_CCB_API_GETCAP;

/* AVDT_CCB_API_CONNECT_REQ_EVT的数据类型*/
typedef struct {
    tAVDT_CTRL_CBACK    *p_cback;
    UINT8               sec_mask;
} tAVDT_CCB_API_CONNECT;

/* AVDT_CCB_API_DISCONNECT_REQ_EVT的数据类型*/
typedef struct {
    tAVDT_CTRL_CBACK    *p_cback;
} tAVDT_CCB_API_DISCONNECT;

/* 与ccb状态机事件关联的联合*/
typedef union {
    tAVDT_CCB_API_DISCOVER      discover;
    tAVDT_CCB_API_GETCAP        getcap;
    tAVDT_CCB_API_CONNECT       connect;
    tAVDT_CCB_API_DISCONNECT    disconnect;
    tAVDT_MSG                   msg;
    BOOLEAN                     llcong;
    UINT8                       err_code;
} tAVDT_CCB_EVT;

/* 信道控制块类型*/
typedef struct {
    BD_ADDR             peer_addr;      /* 对等方的BD地址*/
    TIMER_LIST_ENT      timer_entry;    /* CCB计时器列表条目*/
    fixed_queue_t       *cmd_q;          /* 传出命令消息的队列*/
    fixed_queue_t       *rsp_q;          /* 传出响应和拒绝消息的队列*/
    tAVDT_CTRL_CBACK    *proc_cback;    /* 过程回调函数*/
    tAVDT_CTRL_CBACK    *p_conn_cback;  /* 连接/断开回调函数*/
    void                *p_proc_data;   /* 指向过程数据存储的指针*/
    BT_HDR              *p_curr_cmd;    /* 正在发送当前命令等待响应*/
    BT_HDR              *p_curr_msg;    /* 正在发送的当前消息*/
    BT_HDR              *p_rx_msg;      /* 正在接收的当前消息*/
    BOOLEAN             allocated;      /* 是否分配ccb*/
    UINT8               state;          /* CCB状态机状态*/
    BOOLEAN             ll_opened;      /* 如果LL打开，则为TRUE*/
    BOOLEAN             proc_busy;      /* 当发现或获取功能过程正在进行时为TRUE*/
    UINT8               proc_param;     /* 程序参数；获取能力的SEID或发现能力的SEPS数量*/
    BOOLEAN             cong;           /* 信令信道是否拥塞*/
    UINT8               label;          /* 消息标题“标签”（序列号）*/
    BOOLEAN             reconn;         /* 如果为TRUE，则在从CLOSING转换为IDLE状态后重新启动连接*/
    UINT8               ret_count;      /* 命令重传计数*/
    UINT8               disc_rsn;       /* 断开连接原因*/
} tAVDT_CCB;

/* 动作函数的类型*/
typedef void (*tAVDT_CCB_ACTION)(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);

/* AVDT_SCB_API_WRITE_REQ_EVT的类型*/
typedef struct {
    BT_HDR      *p_buf;
    UINT32      time_stamp;
#if AVDT_MULTIPLEXING == TRUE
    fixed_queue_t    *frag_q;          /* 传出媒体片段的队列。p_buf应为0*/
    UINT8       *p_data;
    UINT32      data_len;
#endif
    UINT8       m_pt;
    tAVDT_DATA_OPT_MASK     opt;
} tAVDT_SCB_APIWRITE;

/* AVDT_SCB_TC_CLOSE_EVT的类型*/
typedef struct {
    UINT8           old_tc_state;       /* 关闭前的通道状态*/
    UINT8           tcid;               /* TCID  */
    UINT8           type;               /* 渠道类型*/
    UINT8           disc_rsn;           /* 断开连接原因*/
} tAVDT_SCB_TC_CLOSE;

/* scb事件数据的类型*/
typedef union {
    tAVDT_MSG           msg;
    tAVDT_SCB_APIWRITE  apiwrite;
    tAVDT_DELAY_RPT     apidelay;
    tAVDT_OPEN          open;
    tAVDT_SCB_TC_CLOSE  close;
    BOOLEAN             llcong;
    BT_HDR              *p_pkt;
} tAVDT_SCB_EVT;

/* 流控制块类型*/
typedef struct {
    tAVDT_CS        cs;             /* 流创建结构*/
    tAVDT_CFG       curr_cfg;       /* 当前配置*/
    tAVDT_CFG       req_cfg;        /* 请求的配置*/
    TIMER_LIST_ENT  timer_entry;    /* 计时器条目*/
    BT_HDR          *p_pkt;         /* 等待发送的数据包*/
    tAVDT_CCB       *p_ccb;         /* 与此scb关联的ccb*/
    UINT16          media_seq;      /* 媒体包序列号*/
    BOOLEAN         allocated;      /* scb是否已分配或未使用*/
    BOOLEAN         in_use;         /* 是否对等方正在使用流*/
    BOOLEAN         sink_activated; /* A2DP接收器从应用程序激活/停用*/
    UINT8           role;           /* 引发剂/受体在当前过程中的作用*/
    BOOLEAN         remove;         /* CB是否标记为移除*/
    UINT8           state;          /* 状态机状态*/
    UINT8           peer_seid;      /* 对等流的SEID*/
    UINT8           curr_evt;       /* 当前事件；仅由状态机设置*/
    BOOLEAN         cong;           /* 媒体传输通道是否堵塞*/
    UINT8           close_code;     /* 关闭响应中收到错误代码*/
#if AVDT_MULTIPLEXING == TRUE
    fixed_queue_t        *frag_q;         /* 传出媒体片段的队列*/
    UINT32          frag_off;       /* 已接收媒体片段的长度*/
    UINT32          frag_org_len;   /* 接收媒体分组分段前的原始长度*/
    UINT8           *p_next_frag;   /* 要发送的下一个片段*/
    UINT8           *p_media_buf;   /* AVDT_SetMediaBuf分配的媒体包缓冲区*/
    UINT32          media_buf_len;  /* AVDT_SetMediaBuf分配的媒体包缓冲区长度*/
#endif
} tAVDT_SCB;

/* 动作函数的类型*/
typedef void (*tAVDT_SCB_ACTION)(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);

/* 传输信道表的自适应层类型*/
typedef struct {
    UINT16  peer_mtu;       /* 对等设备的L2CAP mtu*/
    UINT16  my_mtu;         /* 此频道的MTU*/
    UINT16  my_flush_to;    /* 此通道的刷新超时*/
    UINT16  lcid;
    UINT8   tcid;           /* 传输通道id*/
    UINT8   ccb_idx;        /* 与此tc相关的信道控制块*/
    UINT8   state;          /* 传输通道状态*/
    UINT8   cfg_flags;      /* L2CAP配置标志*/
    UINT8   id;
} tAVDT_TC_TBL;

/* 流路由表的自适应层类型*/
typedef struct {
    UINT16  lcid;           /* 相关传输通道的L2CAP LCID*/
    UINT8   scb_hdl;        /* 与此tc关联的流控制块*/
} tAVDT_RT_TBL;


/* 自适应层控制块*/
typedef struct {
    tAVDT_RT_TBL    rt_tbl[AVDT_NUM_LINKS][AVDT_NUM_RT_TBL];
    tAVDT_TC_TBL    tc_tbl[AVDT_NUM_TC_TBL];
    UINT8           lcid_tbl[MAX_L2CAP_CHANNELS];   /* 将LCID映射到tc_tbl索引*/
} tAVDT_AD;

/* AVDT控制块*/
typedef struct {
    tAVDT_REG           rcb;                    /* 登记控制块*/
    tAVDT_CCB           ccb[AVDT_NUM_LINKS];    /* 信道控制块*/
    tAVDT_SCB           scb[AVDT_NUM_SEPS];     /* 流控制块*/
    tAVDT_AD            ad;                     /* 自适应层控制块*/
    tAVDTC_CTRL_CBACK   *p_conf_cback;          /* 一致性回调函数*/
    tAVDT_CCB_ACTION    *p_ccb_act;             /* CCB动作函数指针*/
    tAVDT_SCB_ACTION    *p_scb_act;             /* 指向SCB动作函数的指针*/
    tAVDT_CTRL_CBACK    *p_conn_cback;          /* 连接回调函数*/
    UINT8               trace_level;            /* 跟踪级别*/
} tAVDT_CB;


/*****************************************************************************
** 函数声明
*****************************************************************************/

/* CCB函数声明*/
extern void avdt_ccb_init(void);
extern void avdt_ccb_event(tAVDT_CCB *p_ccb, UINT8 event, tAVDT_CCB_EVT *p_data);
extern tAVDT_CCB *avdt_ccb_by_bd(BD_ADDR bd_addr);
extern tAVDT_CCB *avdt_ccb_alloc(BD_ADDR bd_addr);
extern void avdt_ccb_dealloc(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern UINT8 avdt_ccb_to_idx(tAVDT_CCB *p_ccb);
extern tAVDT_CCB *avdt_ccb_by_idx(UINT8 idx);

/* CCB动作功能*/
extern void avdt_ccb_chan_open(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_chan_close(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_chk_close(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_discover_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_discover_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_getcap_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_getcap_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_start_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_start_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_suspend_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_hdl_suspend_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_discover_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_discover_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_getcap_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_getcap_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_start_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_start_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_suspend_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_suspend_rsp(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_clear_cmds(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_cmd_fail(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_free_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_cong_state(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_ret_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_cmd(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_snd_msg(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_set_reconn(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_clr_reconn(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_chk_reconn(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_chk_timer(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_set_conn(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_set_disconn(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_do_disconn(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_ll_closed(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);
extern void avdt_ccb_ll_opened(tAVDT_CCB *p_ccb, tAVDT_CCB_EVT *p_data);

/* SCB功能原型*/
extern void avdt_scb_event(tAVDT_SCB *p_scb, UINT8 event, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_init(void);
extern tAVDT_SCB *avdt_scb_alloc(tAVDT_CS *p_cs);
extern void avdt_scb_dealloc(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern UINT8 avdt_scb_to_hdl(tAVDT_SCB *p_scb);
extern tAVDT_SCB *avdt_scb_by_hdl(UINT8 hdl);
extern UINT8 avdt_scb_verify(tAVDT_CCB *p_ccb, UINT8 state, UINT8 *p_seid, UINT16 num_seid, UINT8 *p_err_code);
extern void avdt_scb_peer_seid_list(tAVDT_MULTI *p_multi);
extern UINT32 avdt_scb_gen_ssrc(tAVDT_SCB *p_scb);

/* SCB动作功能*/
extern void avdt_scb_hdl_abort_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_abort_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_close_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_close_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_getconfig_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_getconfig_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_open_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_open_rej(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_open_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_pkt(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_drop_pkt(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_reconfig_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_reconfig_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_security_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_security_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_setconfig_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_setconfig_rej(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_setconfig_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_start_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_start_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_suspend_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_suspend_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_delay_rpt_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_delay_rpt_cmd(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_delay_rpt_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_tc_close(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_tc_open(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_tc_close_sto(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_tc_open_sto(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_hdl_write_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_abort_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_abort_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_close_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_stream_close(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_close_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_getconfig_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_getconfig_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_open_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_open_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_reconfig_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_reconfig_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_security_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_security_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_setconfig_req(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_setconfig_rej(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_setconfig_rsp(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_snd_tc_close(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_cb_err(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_cong_state(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_rej_state(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_rej_in_use(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_rej_not_in_use(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_set_remove(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_free_pkt(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_chk_snd_pkt(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_clr_pkt(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_tc_timer(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_clr_vars(tAVDT_SCB *p_scb, tAVDT_SCB_EVT *p_data);
extern void avdt_scb_queue_frags(tAVDT_SCB *p_scb, UINT8 **pp_data, UINT32 *p_data_len, fixed_queue_t *pq);

/* msg函数声明*/
extern BOOLEAN avdt_msg_send(tAVDT_CCB *p_ccb, BT_HDR *p_msg);
extern void avdt_msg_send_cmd(tAVDT_CCB *p_ccb, void *p_scb, UINT8 sig_id, tAVDT_MSG *p_params);
extern void avdt_msg_send_rsp(tAVDT_CCB *p_ccb, UINT8 sig_id, tAVDT_MSG *p_params);
extern void avdt_msg_send_rej(tAVDT_CCB *p_ccb, UINT8 sig_id, tAVDT_MSG *p_params);
extern void avdt_msg_send_grej(tAVDT_CCB *p_ccb, UINT8 sig_id, tAVDT_MSG *p_params);
extern void avdt_msg_ind(tAVDT_CCB *p_ccb, BT_HDR *p_buf);

/* 适应层函数声明*/
extern void avdt_ad_init(void);
extern UINT8 avdt_ad_type_to_tcid(UINT8 type, tAVDT_SCB *p_scb);
extern tAVDT_TC_TBL *avdt_ad_tc_tbl_by_st(UINT8 type, tAVDT_CCB *p_ccb, UINT8 state);
extern tAVDT_TC_TBL *avdt_ad_tc_tbl_by_lcid(UINT16 lcid);
extern tAVDT_TC_TBL *avdt_ad_tc_tbl_alloc(tAVDT_CCB *p_ccb);
extern UINT8 avdt_ad_tc_tbl_to_idx(tAVDT_TC_TBL *p_tbl);
extern void avdt_ad_tc_close_ind(tAVDT_TC_TBL *p_tbl, UINT16 reason);
extern void avdt_ad_tc_open_ind(tAVDT_TC_TBL *p_tbl);
extern void avdt_ad_tc_cong_ind(tAVDT_TC_TBL *p_tbl, BOOLEAN is_congested);
extern void avdt_ad_tc_data_ind(tAVDT_TC_TBL *p_tbl, BT_HDR *p_buf);
extern tAVDT_TC_TBL *avdt_ad_tc_tbl_by_type(UINT8 type, tAVDT_CCB *p_ccb, tAVDT_SCB *p_scb);
extern UINT8 avdt_ad_write_req(UINT8 type, tAVDT_CCB *p_ccb, tAVDT_SCB *p_scb, BT_HDR *p_buf);
extern void avdt_ad_open_req(UINT8 type, tAVDT_CCB *p_ccb, tAVDT_SCB *p_scb, UINT8 role);
extern void avdt_ad_close_req(UINT8 type, tAVDT_CCB *p_ccb, tAVDT_SCB *p_scb);

extern void avdt_process_timeout(TIMER_LIST_ENT *p_tle);

/*****************************************************************************
** 宏
*****************************************************************************/

/* 我们将scb和标签存储在当前cmd的layerspecific字段中
*/
#define AVDT_BLD_LAYERSPEC(ls, msg, label) \
            ls = (((label) << 4) | (msg))

#define AVDT_LAYERSPEC_LABEL(ls)    ((UINT8)((ls) >> 4))

#define AVDT_LAYERSPEC_MSG(ls)      ((UINT8)((ls) & 0x000F))

/*****************************************************************************
** 全局数据
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
** 主控制块
*******************************************************************************/
#if AVDT_DYNAMIC_MEMORY == FALSE
extern tAVDT_CB  avdt_cb;
#else
extern tAVDT_CB *avdt_cb_ptr;
#define avdt_cb (*avdt_cb_ptr)
#endif


/* L2CAP回调注册结构*/
extern const tL2CAP_APPL_INFO avdt_l2c_appl;

/* 拒绝消息事件查找表*/
extern const UINT8 avdt_msg_rej_2_evt[];
#ifdef __cplusplus
}
#endif

#endif  ///AVRC_INCLUDED == TRUE

#endif /* AVDT_INT_H */

