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
 * 此文件包含L2CAP内部定义
 *
 ******************************************************************************/
#ifndef L2C_INT_H
#define L2C_INT_H

#include <stdbool.h>
#include "stack/btm_api.h"
#include "stack/l2c_api.h"
#include "stack/l2cdefs.h"
#include "osi/list.h"
#include "osi/fixed_queue.h"

#define L2CAP_MIN_MTU   48      /* 最小可接受MTU为48字节*/

/* 基于LE信用的L2CAP连接参数*/
#define L2CAP_LE_MIN_MTU            23
#define L2CAP_LE_MIN_MPS            23
#define L2CAP_LE_MAX_MPS            65533
#define L2CAP_LE_MIN_CREDIT         0
#define L2CAP_LE_MAX_CREDIT         65535
#define L2CAP_LE_DEFAULT_MTU        512
#define L2CAP_LE_DEFAULT_MPS        23
#define L2CAP_LE_DEFAULT_CREDIT     1


/* 超时。由于L2CAP在1秒的列表中工作，所以所有这些都以秒为单位。
*/
#define L2CAP_LINK_ROLE_SWITCH_TOUT  10           /* 10秒*/
#define L2CAP_LINK_CONNECT_TOUT      60           /* 30秒*/
#define L2CAP_LINK_CONNECT_TOUT_EXT  120          /* 120秒*/
#define L2CAP_ECHO_RSP_TOUT          30           /* 30秒*/
#define L2CAP_LINK_FLOW_CONTROL_TOUT 2            /* 2秒*/
#define L2CAP_LINK_DISCONNECT_TOUT   45           /* 45秒*/

#ifndef L2CAP_CHNL_CONNECT_TOUT      /* BTIF需要覆盖内部项目需求*/
#define L2CAP_CHNL_CONNECT_TOUT      60           /* 60秒*/
#endif

#define L2CAP_CHNL_CONNECT_TOUT_EXT  120          /* 120秒*/
#define L2CAP_CHNL_CFG_TIMEOUT       30           /* 30秒*/
#define L2CAP_CHNL_DISCONNECT_TOUT   10           /* 10秒*/
#define L2CAP_DELAY_CHECK_SM4        2            /* 2秒*/
#define L2CAP_WAIT_INFO_RSP_TOUT     3            /* 3秒*/
#define L2CAP_WAIT_UNPARK_TOUT       2            /* 2秒*/
#define L2CAP_LINK_INFO_RESP_TOUT    2            /* 2秒*/
#define L2CAP_UPDATE_CONN_PARAM_TOUT 6            /* 6秒*/
#define L2CAP_BLE_LINK_CONNECT_TOUT  BLE_ESTABLISH_LINK_CONNECTION_TIMEOUT  // 在menuconfig中配置
#define L2CAP_BLE_CONN_PARAM_UPD_TOUT   30        /* 30秒*/

/* 快速计时器使用毫秒单位*/
#define L2CAP_DEFAULT_RETRANS_TOUT   2000         /* 2000毫秒*/
#define L2CAP_DEFAULT_MONITOR_TOUT   12000        /* 12000毫秒*/
#define L2CAP_FCR_ACK_TOUT           200          /* 200毫秒*/

#define L2CAP_CACHE_ATT_ACL_NUM      10

/* 定义可能的L2CAP信道状态。各州的名称可能看起来有点奇怪，但它们取自蓝牙规范。
*/
typedef enum {
    CST_CLOSED,                           /* 通道处于闭塞状态*/
    CST_ORIG_W4_SEC_COMP,                 /* 发起人等待安全清算*/
    CST_TERM_W4_SEC_COMP,                 /* 接收方等待安全清算*/
    CST_W4_L2CAP_CONNECT_RSP,             /* 正在等待对等连接响应*/
    CST_W4_L2CA_CONNECT_RSP,              /* 正在等待上层连接rsp*/
    CST_CONFIG,                           /* 正在协商配置*/
    CST_OPEN,                             /* 数据传输状态*/
    CST_W4_L2CAP_DISCONNECT_RSP,          /* 正在等待对等断开连接rsp*/
    CST_W4_L2CA_DISCONNECT_RSP            /* 等待上层磁盘rsp*/
} tL2C_CHNL_STATE;

/* 定义可能的L2CAP链路状态
*/
typedef enum {
    LST_DISCONNECTED,
    LST_CONNECT_HOLDING,
    LST_CONNECTING_WAIT_SWITCH,
    LST_CONNECTING,
    LST_CONNECTED,
    LST_DISCONNECTING
} tL2C_LINK_STATE;



/* 定义L2CAP链路和信道状态机的输入事件。事件的名称可能看起来有点奇怪，但它们取自蓝牙规范。
*/
#define L2CEVT_LP_CONNECT_CFM          0          /* 下层连接确认*/
#define L2CEVT_LP_CONNECT_CFM_NEG      1          /* 下层连接确认（失败）*/
#define L2CEVT_LP_CONNECT_IND          2          /* 下层连接指示*/
#define L2CEVT_LP_DISCONNECT_IND       3          /* 下层断开指示*/
#define L2CEVT_LP_QOS_CFM              4          /* 下层QOS确认*/
#define L2CEVT_LP_QOS_CFM_NEG          5          /* 下层QOS确认（失败）*/
#define L2CEVT_LP_QOS_VIOLATION_IND    6          /* 下层QOS违规指示*/

#define L2CEVT_SEC_COMP                7          /* 安全性已成功清除*/
#define L2CEVT_SEC_COMP_NEG            8          /* 安全程序失败*/

#define L2CEVT_L2CAP_CONNECT_REQ      10          /* 对等连接请求*/
#define L2CEVT_L2CAP_CONNECT_RSP      11          /* 对等连接响应*/
#define L2CEVT_L2CAP_CONNECT_RSP_PND  12          /* 对等连接响应挂起*/
#define L2CEVT_L2CAP_CONNECT_RSP_NEG  13          /* 对等连接响应（失败）*/
#define L2CEVT_L2CAP_CONFIG_REQ       14          /* 对等配置请求*/
#define L2CEVT_L2CAP_CONFIG_RSP       15          /* 对等配置响应*/
#define L2CEVT_L2CAP_CONFIG_RSP_NEG   16          /* 对等配置响应（失败）*/
#define L2CEVT_L2CAP_DISCONNECT_REQ   17          /* 对等断开连接请求*/
#define L2CEVT_L2CAP_DISCONNECT_RSP   18          /* 对等断开连接响应*/
#define L2CEVT_L2CAP_INFO_RSP         19          /* 对等信息响应*/
#define L2CEVT_L2CAP_DATA             20          /* 对等数据*/

#define L2CEVT_L2CA_CONNECT_REQ       21          /* 上层连接请求*/
#define L2CEVT_L2CA_CONNECT_RSP       22          /* 上层连接响应*/
#define L2CEVT_L2CA_CONNECT_RSP_NEG   23          /* 上层连接响应（失败）*/
#define L2CEVT_L2CA_CONFIG_REQ        24          /* 上层配置请求*/
#define L2CEVT_L2CA_CONFIG_RSP        25          /* 上层配置响应*/
#define L2CEVT_L2CA_CONFIG_RSP_NEG    26          /* 上层配置响应（失败）*/
#define L2CEVT_L2CA_DISCONNECT_REQ    27          /* 上层断开请求*/
#define L2CEVT_L2CA_DISCONNECT_RSP    28          /* 上层断开响应*/
#define L2CEVT_L2CA_DATA_READ         29          /* 上层数据读取*/
#define L2CEVT_L2CA_DATA_WRITE        30          /* 上层数据写入*/
#define L2CEVT_L2CA_FLUSH_REQ         31          /* 上层齐平*/

#define L2CEVT_TIMEOUT                32          /* 超时*/
#define L2CEVT_SEC_RE_SEND_CMD        33          /* btm_sec有足够的信息继续*/

#define L2CEVT_ACK_TIMEOUT            34          /* RR延迟超时*/


/* 跳过Broadcom保留功能（ID）的位掩码，以避免发送两个连续的ID值，仅“0”ID或同时发送两个ID值*/
#define L2CAP_ADJ_BRCM_ID           0x1
#define L2CAP_ADJ_ZERO_ID           0x2
#define L2CAP_ADJ_ID                0x3

/* l2cu_process_peer_cfg_req（）的返回值*/
#define L2CAP_PEER_CFG_UNACCEPTABLE     0
#define L2CAP_PEER_CFG_OK               1
#define L2CAP_PEER_CFG_DISCONNECT       2

/* eL2CAP选项常量*/
#define L2CAP_MIN_RETRANS_TOUT          2000    /* 如果没有刷新超时或PBF，则最小重传超时*/
#define L2CAP_MIN_MONITOR_TOUT          12000   /* 如果没有刷新超时或PBF，最小监视器超时*/

#define L2CAP_MAX_FCR_CFG_TRIES         2       /* 断开连接前的配置尝试*/

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
typedef uint8_t tL2C_BLE_FIXED_CHNLS_MASK;

typedef struct {
    UINT8       next_tx_seq;                /* 要发送的下一个序列号*/
    UINT8       last_rx_ack;                /* 对等方确认的最后序列号*/
    UINT8       next_seq_expected;          /* 需要下一个对等序列号*/
    UINT8       last_ack_sent;              /* 最后一个对等序列号已确认*/
    UINT8       num_tries;                  /* 发送数据包的重试次数*/
    UINT8       max_held_acks;              /* 发送前我们可以保存的最大ACK*/

    BOOLEAN     remote_busy;                /* 如果同行让我们离开，则为TRUE*/
    BOOLEAN     local_busy;                 /* 如果我们离开了同行，则为TRUE*/

    BOOLEAN     rej_sent;                   /* 拒绝已发送*/
    BOOLEAN     srej_sent;                  /* 已发送选择性拒绝*/
    BOOLEAN     wait_ack;                   /* 发射机正在等待确认（轮询已发送）*/
    BOOLEAN     rej_after_srej;             /* SREJ清除时发送REJ*/

    BOOLEAN     send_f_rsp;                 /* 我们需要发送F位响应*/

    UINT16      rx_sdu_len;                 /* 接收SDU的长度*/
    BT_HDR      *p_rx_sdu;                  /* 保存正在接收的SDU的缓冲区*/
    fixed_queue_t    *waiting_for_ack_q;          /* 已发送并等待对等确认的缓冲区*/
    fixed_queue_t    *srej_rcv_hold_q;            /* 缓冲区rcvd，但等待SREJ rsp*/
    fixed_queue_t    *retrans_q;                  /* 正在重新传输的缓冲区*/

    TIMER_LIST_ENT ack_timer;               /* 定时器延迟RR*/
    TIMER_LIST_ENT mon_retrans_timer;       /* 计时器监视器或重新传输*/

#if (L2CAP_ERTM_STATS == TRUE)
    UINT32      connect_tick_count;         /* 时间通道已建立*/
    UINT32      ertm_pkt_counts[2];         /* 发送和接收的数据包*/
    UINT32      ertm_byte_counts[2];        /* 发送和接收的字节数*/
    UINT32      s_frames_sent[4];           /* 发送的S帧（RR、REJ、RNR、SREJ）*/
    UINT32      s_frames_rcvd[4];           /* S帧rcvd（RR、REJ、RNR、SREJ）*/
    UINT32      xmit_window_closed;         /* #xmit窗口关闭的次数*/
    UINT32      controller_idle;            /* #控制器中少于2个数据包的次数*/
    /* 当xmit窗口关闭时*/
    UINT32      pkts_retransmitted;         /* #已重新传输的数据包（共个）*/
    UINT32      retrans_touts;              /* #的重传超时*/
    UINT32      xmit_ack_touts;             /* #在xmit ack timouts中*/

#define L2CAP_ERTM_STATS_NUM_AVG 10
#define L2CAP_ERTM_STATS_AVG_NUM_SAMPLES 100
    UINT32      ack_delay_avg_count;
    UINT32      ack_delay_avg_index;
    UINT32      throughput_start;
    UINT32      throughput[L2CAP_ERTM_STATS_NUM_AVG];
    UINT32      ack_delay_avg[L2CAP_ERTM_STATS_NUM_AVG];
    UINT32      ack_delay_min[L2CAP_ERTM_STATS_NUM_AVG];
    UINT32      ack_delay_max[L2CAP_ERTM_STATS_NUM_AVG];
    UINT32      ack_q_count_avg[L2CAP_ERTM_STATS_NUM_AVG];
    UINT32      ack_q_count_min[L2CAP_ERTM_STATS_NUM_AVG];
    UINT32      ack_q_count_max[L2CAP_ERTM_STATS_NUM_AVG];
#endif
} tL2C_FCRB;


/* 定义注册控制块。向L2CAP注册的每个应用程序（例如RFCOMM、SDP、TCS等）都分配了其中一个。
*/
#if (L2CAP_UCD_INCLUDED == TRUE)
#define L2C_UCD_RCB_ID              0x00
#define L2C_UCD_STATE_UNUSED        0x00
#define L2C_UCD_STATE_W4_DATA       0x01
#define L2C_UCD_STATE_W4_RECEPTION  0x02
#define L2C_UCD_STATE_W4_MTU        0x04

typedef struct {
    UINT8               state;
    tL2CAP_UCD_CB_INFO  cb_info;
} tL2C_UCD_REG;
#endif

typedef struct {
    BOOLEAN                 in_use;
    UINT16                  psm;
    UINT16                  real_psm;               /* 这可能是用于o/b连接的虚拟RCB，但*/
    /* 这是我们需要连接的真正PSM*/
#if (L2CAP_UCD_INCLUDED == TRUE)
    tL2C_UCD_REG            ucd;
#endif

    tL2CAP_APPL_INFO        api;
} tL2C_RCB;

typedef void (tL2CAP_SEC_CBACK) (BD_ADDR bd_addr, tBT_TRANSPORT transport,
                                void *p_ref_data, tBTM_STATUS result);

typedef struct
{
    UINT16                  psm;
    tBT_TRANSPORT           transport;
    BOOLEAN                 is_originator;
    tL2CAP_SEC_CBACK        *p_callback;
    void                    *p_ref_data;
}tL2CAP_SEC_DATA;

#ifndef L2CAP_CBB_DEFAULT_DATA_RATE_BUFF_QUOTA
#define L2CAP_CBB_DEFAULT_DATA_RATE_BUFF_QUOTA 10
#endif
/* 定义信道控制块（CCB）。在相同的两个蓝牙设备之间（即在相同的链路上）可能存在许多信道控制块。每个CCB都有唯一的本地和远程CID。同一物理链路上的所有信道控制块都链接在一起。
*/
typedef struct t_l2c_ccb {
    BOOLEAN             in_use;                 /* 使用时为TRUE，不使用时为FALSE*/
    tL2C_CHNL_STATE     chnl_state;             /* 通道状态*/
    tL2CAP_LE_CFG_INFO  local_conn_cfg;         /* 我们的面向ble conn的通道配置*/
    tL2CAP_LE_CFG_INFO  peer_conn_cfg;          /* 对等设备可配置的面向连接的通道*/

    struct t_l2c_ccb    *p_next_ccb;            /* 链中的下一个CCB*/
    struct t_l2c_ccb    *p_prev_ccb;            /* 链中以前的CCB*/
    struct t_l2c_linkcb *p_lcb;                 /* 此CCB分配给的链接*/

    UINT16              local_cid;              /* 本地CID*/
    UINT16              remote_cid;             /* 远程CID*/

    TIMER_LIST_ENT      timer_entry;            /* CCB计时器列表条目*/

    tL2C_RCB            *p_rcb;                 /* 此频道的注册CB*/
    bool                should_free_rcb;        /* 如果在堆上分配了RCB，则为True*/

#define IB_CFG_DONE     0x01
#define OB_CFG_DONE     0x02
#define RECONFIG_FLAG   0x04                    /* 初始配置后为True*/
#define CFG_DONE_MASK   (IB_CFG_DONE | OB_CFG_DONE)

    UINT8               config_done;            /* 配置标志字*/
    UINT8               local_id;               /* 本地交易的交易ID*/
    UINT8               remote_id;              /* 本地事务ID*/

#define CCB_FLAG_NO_RETRY       0x01            /* 不再重试*/
#define CCB_FLAG_SENT_PENDING   0x02            /* 已发送挂起响应*/
    UINT8               flags;

    tL2CAP_CFG_INFO     our_cfg;                /* 我们保存的配置选项*/
    tL2CAP_CH_CFG_BITS  peer_cfg_bits;          /* 存储对等方要配置的内容*/
    tL2CAP_CFG_INFO     peer_cfg;               /* 对等方保存的配置选项*/

    fixed_queue_t       *xmit_hold_q;            /* 传输数据保持队列*/
    BOOLEAN             cong_sent;              /* 发送拥塞状态时设置*/
    UINT16              buff_quota;             /* 发送拥塞前的缓冲区配额*/

    tL2CAP_CHNL_PRIORITY ccb_priority;          /* 通道优先级*/
    tL2CAP_CHNL_DATA_RATE tx_data_rate;         /* 信道Tx数据速率*/
    tL2CAP_CHNL_DATA_RATE rx_data_rate;         /* 信道Rx数据速率*/

    /* 用于eL2CAP的字段*/
    tL2CAP_ERTM_INFO    ertm_info;
    tL2C_FCRB           fcrb;
    UINT16              tx_mps;                 /* 基于电流控制器调整的TX MPS*/
    UINT16              max_rx_mtu;
    UINT8               fcr_cfg_tries;          /* 最大协商尝试次数*/
    BOOLEAN             peer_cfg_already_rejected; /* 如果模式被拒绝一次，则设置为TRUE*/
    BOOLEAN             out_cfg_fcr_present;    /* 如果cfg响应应包含fcr选项，则为TRUE*/

#define L2CAP_CFG_FCS_OUR   0x01                /* 我们期望的配置FCS选项*/
#define L2CAP_CFG_FCS_PEER  0x02                /* 对等方所需的配置FCS选项*/
#define L2CAP_BYPASS_FCS    (L2CAP_CFG_FCS_OUR | L2CAP_CFG_FCS_PEER)
    UINT8               bypass_fcs;

#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
    BOOLEAN             is_flushable;                   /* 如果通道可冲洗，则为TRUE*/
#endif

#if (L2CAP_NUM_FIXED_CHNLS > 0) || (L2CAP_UCD_INCLUDED == TRUE)
    UINT16              fixed_chnl_idle_tout;   /* 用于固定通道的空闲超时*/
#endif
    UINT16              tx_data_len;
} tL2C_CCB;

/***********************************************************************
** 定义链接的CCB队列。
*/
typedef struct {
    tL2C_CCB        *p_first_ccb;               /* 此队列中的第一个通道*/
    tL2C_CCB        *p_last_ccb;                /* 此队列中的最后一个频道*/
} tL2C_CCB_Q;

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)

/* 相同优先级信道的循环服务*/
#define L2CAP_NUM_CHNL_PRIORITY     3           /* 优先级组总数（高、中、低）*/
#define L2CAP_CHNL_PRIORITY_WEIGHT  5           /* 突发传输配额的每优先级权重*/
#define L2CAP_GET_PRIORITY_QUOTA(pri) ((L2CAP_NUM_CHNL_PRIORITY - (pri)) * L2CAP_CHNL_PRIORITY_WEIGHT)

/* 同一LCB内的CCB以循环方式优先服务*/
/* 它将确保低优先级信道（例如，RFCOMM上的HF信令）*/
/* 即使优先级较高的频道（例如，AV媒体频道）也可以发送到耳机*/
/* 拥堵。*/

typedef struct {
    tL2C_CCB        *p_serve_ccb;               /* 优先级组内的当前服务ccb*/
    tL2C_CCB        *p_first_ccb;               /* 优先级组的第一个ccb*/
    UINT8           num_ccb;                    /* 优先级组中的通道数*/
    UINT8           quota;                      /* 突发传输配额*/
} tL2C_RR_SERV;

#endif /* (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE) */


/* 定义链接控制块。此设备与任何其他设备（即BD ADDR）之间有一个链路控制块。
*/
typedef struct t_l2c_linkcb {
    BOOLEAN             in_use;                     /* 使用时为TRUE，不使用时为FALSE*/
    tL2C_LINK_STATE     link_state;
    BOOLEAN             is_aux;                     /* 当进行辅助连接时，此变量用于BLE 5.0或更高版本*/
    TIMER_LIST_ENT      timer_entry;                /* 超时evt的计时器列表条目*/
    UINT16              handle;                     /* 与LM一起使用的手柄*/

    tL2C_CCB_Q          ccb_queue;                  /* 此LCB上的CCB队列*/

    tL2C_CCB            *p_pending_ccb;             /* 链路断开期间等待信道的ccb*/
    TIMER_LIST_ENT      info_timer_entry;           /* 信息响应超时evt的计时器条目*/
    TIMER_LIST_ENT      upda_con_timer;             /* 更新连接参数的计时器条目*/
    BD_ADDR             remote_bd_addr;             /* 远程设备的BD地址*/

    UINT8               link_role;                  /* 主设备或从设备*/
    UINT8               id;
    UINT8               cur_echo_id;                /* 回显请求的当前id值*/
    tL2CA_ECHO_RSP_CB   *p_echo_rsp_cb;             /* 回显响应回调*/
    UINT16              idle_timeout;               /* 空闲超时*/
    BOOLEAN             is_bonding;                 /* True-链接仅用于绑定*/

    UINT16              link_flush_tout;            /* 已使用刷新超时*/

    UINT16              link_xmit_quota;            /* 允许的未完成pkt数*/
    UINT16              sent_not_acked;             /* 已发送但未确认的数据包数*/

    BOOLEAN             partial_segment_being_sent; /* 部分段时设置为TRUE*/
    /* 正在发送。*/
    BOOLEAN             w4_info_rsp;                /* 当信息请求处于活动状态时为TRUE*/
    UINT8               info_rx_bits;               /* 如果收到信息类型，则设置1*/
    UINT32              peer_ext_fea;               /* 对等扩展功能掩码*/
    list_t              *link_xmit_data_q;          /* 链路传输数据缓冲队列*/

    UINT8               peer_chnl_mask[L2CAP_FIXED_CHNL_ARRAY_SIZE];
#if (L2CAP_UCD_INCLUDED == TRUE)
    UINT16              ucd_mtu;                    /* UCD上的对等MTU*/
    fixed_queue_t       *ucd_out_sec_pending_q;      /* 安全挂起传出UCD数据包*/
    fixed_queue_t       *ucd_in_sec_pending_q;       /* 安全挂起的传入UCD数据包*/
#endif

    BT_HDR              *p_hcit_rcv_acl;            /* 当前HCIT ACL不可用*/
    UINT16              idle_timeout_sv;            /* 保存当前空闲超时*/
    UINT8               acl_priority;               /* L2C_PRIORITY_NORMAL或L2C_PRIORITY_HIGH*/
    tL2CA_NOCP_CB       *p_nocp_cb;                 /* Num Cmpl pkts回调*/

#if (L2CAP_NUM_FIXED_CHNLS > 0)
    tL2C_CCB            *p_fixed_ccbs[L2CAP_NUM_FIXED_CHNLS];
    UINT16              disc_reason;
#endif

    tBT_TRANSPORT       transport;
#if (BLE_INCLUDED == TRUE)
    tBLE_ADDR_TYPE      open_addr_type; /* 由开放API设置*/
    tBLE_ADDR_TYPE      ble_addr_type;
    UINT16              tx_data_len;            /* 数据长度扩展中使用的tx数据长度*/
    fixed_queue_t       *le_sec_pending_q;      /* LE coc通道等待安全检查完成*/
    UINT8               sec_act;
#define L2C_BLE_CONN_UPDATE_DISABLE 0x1  /* 禁用更新连接参数*/
#define L2C_BLE_NEW_CONN_PARAM      0x2  /* 要设置的新连接参数*/
#define L2C_BLE_UPDATE_PENDING      0x4  /* 等待连接更新完成*/
#define L2C_BLE_NOT_DEFAULT_PARAM   0x8  /* 不使用默认连接参数*/
#define L2C_BLE_UPDATE_PARAM_FULL   0x10 /* 更新连接参数已满，无法更新*/
    UINT8               conn_update_mask;
    /* 等待更新的缓存连接参数*/
    UINT16              waiting_update_conn_min_interval;
    UINT16              waiting_update_conn_max_interval;
    UINT16              waiting_update_conn_latency;
    UINT16              waiting_update_conn_timeout;
    /* 正在更新的缓存参数*/
    UINT16              updating_conn_min_interval;
    UINT16              updating_conn_max_interval;
    bool                updating_param_flag;
    /* 当前连接使用的当前连接参数*/
    UINT16              current_used_conn_interval;
    UINT16              current_used_conn_latency;
    UINT16              current_used_conn_timeout;
    /* 连接参数更新顺序：waiting_update_conn_xx->updating_conn_xx->current_used_conn_xx
    */
   /* 创建连接重试计数*/
   UINT8                retry_create_con;
   UINT32               start_time_s;
#endif

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* 每个优先级组都是有限的突发传输*/
    /* 相同优先级信道的循环服务*/
    tL2C_RR_SERV        rr_serv[L2CAP_NUM_CHNL_PRIORITY];
    UINT8               rr_pri;                             /* 当前服务优先级组*/
#endif

} tL2C_LCB;


/* 定义L2CAP控制结构
*/
typedef struct {
    UINT8           l2cap_trace_level;
    UINT16          controller_xmit_window;         /* 所有链接的总ACL窗口*/

    UINT16          round_robin_quota;              /* 循环链接配额*/
    UINT16          round_robin_unacked;            /* 循环未激活*/
    BOOLEAN         check_round_robin;              /* 进行循环检查*/

    BOOLEAN         is_cong_cback_context;

    list_t          *p_lcb_pool;                    /* 链接控制块池*/
    list_t          *p_ccb_pool;                    /* 通道控制块池*/
    tL2C_RCB        rcb_pool[MAX_L2CAP_CLIENTS];    /* 注册信息池*/


    UINT8           desire_role;                    /* 接受连接时希望成为主/从*/
    BOOLEAN         disallow_switch;                /* FALSE，允许在创建连接时切换*/
    UINT16          num_lm_acl_bufs;                /* #控制器上ACL缓冲区的*/
    UINT16          idle_timeout;                   /* 空闲超时*/

    list_t          *rcv_pending_q;                 /* 接收挂起队列*/
    TIMER_LIST_ENT  rcv_hold_tle;                   /* rcv保持的计时器列表条目*/

    tL2C_LCB        *p_cur_hcit_lcb;                /* 当前HCI传输缓冲区*/
    UINT16          num_links_active;               /* 活动链接数*/

#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
    UINT16          non_flushable_pbf;              /* L2CAP_PKT_START_NON_FLUSHABLE（如果控制器支持）*/
    /* 否则，L2CAP_PKT_START*/
    BOOLEAN         is_flush_active;                /* 如果已发送HCI_Enhanced_Flush，则为TRUE*/
#endif

#if L2CAP_CONFORMANCE_TESTING == TRUE
    UINT32          test_info_resp;                 /* 一致性测试需要动态响应*/
#endif

#if (L2CAP_NUM_FIXED_CHNLS > 0)
    tL2CAP_FIXED_CHNL_REG   fixed_reg[L2CAP_NUM_FIXED_CHNLS];   /* 固定频道的注册信息*/
#endif

#if (BLE_INCLUDED == TRUE)
    UINT16                   num_ble_links_active;               /* 活动的LE链接数*/
    BOOLEAN                  is_ble_connecting;
    BD_ADDR                  ble_connecting_bda;
    UINT16                   controller_le_xmit_window;         /* 所有链接的总ACL窗口*/
    tL2C_BLE_FIXED_CHNLS_MASK l2c_ble_fixed_chnls_mask;         // LE固定通道掩码
    UINT16                   num_lm_ble_bufs;                   /* #控制器上ACL缓冲区的*/
    UINT16                   ble_round_robin_quota;              /* 循环链接配额*/
    UINT16                   ble_round_robin_unacked;            /* 循环未激活*/
    BOOLEAN                  ble_check_round_robin;              /* 进行循环检查*/
    tL2C_RCB                 ble_rcb_pool[BLE_MAX_L2CAP_CLIENTS]; /* 注册信息池*/
#endif

    tL2CA_ECHO_DATA_CB      *p_echo_data_cb;                /* 回显数据回调*/

#if (defined(L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE) && (L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE == TRUE))
    UINT16              high_pri_min_xmit_quota;    /* 高优先级链路的ACL信用的最小数量*/
#endif /* (L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE == TRUE) */

    UINT16          dyn_psm;
} tL2C_CB;



/* 定义包含连接信息的结构。此结构用于在函数之间传递，并不是所有字段都会被填充。
*/
typedef struct {
    BD_ADDR         bd_addr;                        /* 远程BD地址*/
    UINT8           status;                         /* 连接状态*/
    UINT16          psm;                            /* 连接的PSM*/
    UINT16          l2cap_result;                   /* L2CAP结果*/
    UINT16          l2cap_status;                   /* L2CAP状态*/
    UINT16          remote_cid;                     /* 远程CID*/
} tL2C_CONN_INFO;


typedef void (tL2C_FCR_MGMT_EVT_HDLR) (UINT8, tL2C_CCB *);

/* L2CAP在生成命令时将使用的缓冲区中的偏移量。
*/
#define L2CAP_SEND_CMD_OFFSET       0


/* 用于高优先级通道的ACL缓冲区数
*/
#if (!defined(L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE) || (L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE == FALSE))
#define L2CAP_HIGH_PRI_MIN_XMIT_QUOTA_A     (L2CAP_HIGH_PRI_MIN_XMIT_QUOTA)
#else
#define L2CAP_HIGH_PRI_MIN_XMIT_QUOTA_A     (l2cb.high_pri_min_xmit_quota)
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* L2CAP全局数据
************************************
*/
#if (!defined L2C_DYNAMIC_MEMORY) || (L2C_DYNAMIC_MEMORY == FALSE)
extern tL2C_CB  l2cb;
#else
extern tL2C_CB *l2c_cb_ptr;
#define l2cb (*l2c_cb_ptr)
#endif


/* l2c_main.c提供的函数
************************************
*/
void l2c_init(void);
void l2c_free(void);

extern void     l2c_process_timeout (TIMER_LIST_ENT *p_tle);
extern UINT8    l2c_data_write (UINT16 cid, BT_HDR *p_data, UINT16 flag);
extern void     l2c_rcv_acl_data (BT_HDR *p_msg);
extern void     l2c_process_held_packets (BOOLEAN timed_out);

/* l2c_utils.c提供的函数
************************************
*/
extern tL2C_LCB *l2cu_allocate_lcb (BD_ADDR p_bd_addr, BOOLEAN is_bonding, tBT_TRANSPORT transport);
extern BOOLEAN  l2cu_start_post_bond_timer (UINT16 handle);
extern void     l2cu_release_lcb (tL2C_LCB *p_lcb);
extern tL2C_LCB *l2cu_find_lcb_by_bd_addr (BD_ADDR p_bd_addr, tBT_TRANSPORT transport);
extern tL2C_LCB *l2cu_find_lcb_by_handle (UINT16 handle);
extern uint8_t l2cu_plcb_active_count(void);
extern void     l2cu_update_lcb_4_bonding (BD_ADDR p_bd_addr, BOOLEAN is_bonding);

extern UINT8    l2cu_get_conn_role (tL2C_LCB *p_this_lcb);
extern BOOLEAN  l2cu_set_acl_priority (BD_ADDR bd_addr, UINT8 priority, BOOLEAN reset_after_rs);

extern void     l2cu_enqueue_ccb (tL2C_CCB *p_ccb);
extern void     l2cu_dequeue_ccb (tL2C_CCB *p_ccb);
extern void     l2cu_change_pri_ccb (tL2C_CCB *p_ccb, tL2CAP_CHNL_PRIORITY priority);

extern tL2C_CCB *l2cu_allocate_ccb (tL2C_LCB *p_lcb, UINT16 cid);
extern void     l2cu_release_ccb (tL2C_CCB *p_ccb);
extern tL2C_CCB *l2cu_find_ccb_by_cid (tL2C_LCB *p_lcb, UINT16 local_cid);
extern tL2C_CCB *l2cu_find_free_ccb(void);
extern tL2C_CCB *l2cu_find_ccb_by_remote_cid (tL2C_LCB *p_lcb, UINT16 remote_cid);
extern void     l2cu_adj_id (tL2C_LCB *p_lcb, UINT8 adj_mask);
extern BOOLEAN  l2c_is_cmd_rejected (UINT8 cmd_code, UINT8 id, tL2C_LCB *p_lcb);

extern void     l2cu_send_peer_cmd_reject (tL2C_LCB *p_lcb, UINT16 reason,
        UINT8 rem_id, UINT16 p1, UINT16 p2);
extern void     l2cu_send_peer_connect_req (tL2C_CCB *p_ccb);
extern void     l2cu_send_peer_connect_rsp (tL2C_CCB *p_ccb, UINT16 result, UINT16 status);
extern void     l2cu_send_peer_config_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2cu_send_peer_config_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2cu_send_peer_config_rej (tL2C_CCB *p_ccb, UINT8 *p_data, UINT16 data_len, UINT16 rej_len);
extern void     l2cu_send_peer_disc_req (tL2C_CCB *p_ccb);
extern void     l2cu_send_peer_disc_rsp (tL2C_LCB *p_lcb, UINT8 remote_id, UINT16 local_cid, UINT16 remote_cid);
extern void     l2cu_send_peer_echo_req (tL2C_LCB *p_lcb, UINT8 *p_data, UINT16 data_len);
extern void     l2cu_send_peer_echo_rsp (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len);
extern void     l2cu_send_peer_info_rsp (tL2C_LCB *p_lcb, UINT8 id, UINT16 info_type);
extern void     l2cu_reject_connection (tL2C_LCB *p_lcb, UINT16 remote_cid, UINT8 rem_id, UINT16 result);
extern void     l2cu_send_peer_info_req (tL2C_LCB *p_lcb, UINT16 info_type);
extern void     l2cu_set_acl_hci_header (BT_HDR *p_buf, tL2C_CCB *p_ccb);
extern void     l2cu_check_channel_congestion (tL2C_CCB *p_ccb);
extern void     l2cu_disconnect_chnl (tL2C_CCB *p_ccb);

#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
extern void     l2cu_set_non_flushable_pbf(BOOLEAN);
#endif

#if (BLE_INCLUDED == TRUE)
extern void l2cu_send_peer_ble_par_req (tL2C_LCB *p_lcb, UINT16 min_int, UINT16 max_int, UINT16 latency, UINT16 timeout);
extern void l2cu_send_peer_ble_par_rsp (tL2C_LCB *p_lcb, UINT16 reason, UINT8 rem_id);
#endif

extern BOOLEAN l2cu_initialize_fixed_ccb (tL2C_LCB *p_lcb, UINT16 fixed_cid, tL2CAP_FCR_OPTS *p_fcr);
extern void    l2cu_no_dynamic_ccbs (tL2C_LCB *p_lcb);
extern void    l2cu_process_fixed_chnl_resp (tL2C_LCB *p_lcb);

/* l2c_ucd.c提供的函数
************************************
*/
#if (L2CAP_UCD_INCLUDED == TRUE)
void l2c_ucd_delete_sec_pending_q(tL2C_LCB  *p_lcb);
void l2c_ucd_enqueue_pending_out_sec_q(tL2C_CCB  *p_ccb, void *p_data);
BOOLEAN l2c_ucd_check_pending_info_req(tL2C_CCB  *p_ccb);
BOOLEAN l2c_ucd_check_pending_out_sec_q(tL2C_CCB  *p_ccb);
void l2c_ucd_send_pending_out_sec_q(tL2C_CCB  *p_ccb);
void l2c_ucd_discard_pending_out_sec_q(tL2C_CCB  *p_ccb);
BOOLEAN l2c_ucd_check_pending_in_sec_q(tL2C_CCB  *p_ccb);
void l2c_ucd_send_pending_in_sec_q(tL2C_CCB  *p_ccb);
void l2c_ucd_discard_pending_in_sec_q(tL2C_CCB  *p_ccb);
BOOLEAN l2c_ucd_check_rx_pkts(tL2C_LCB  *p_lcb, BT_HDR *p_msg);
BOOLEAN l2c_ucd_process_event(tL2C_CCB *p_ccb, UINT16 event, void *p_data);
#endif

#if (BLE_INCLUDED == TRUE)
extern void l2cu_send_peer_ble_par_req (tL2C_LCB *p_lcb, UINT16 min_int, UINT16 max_int, UINT16 latency, UINT16 timeout);
extern void l2cu_send_peer_ble_par_rsp (tL2C_LCB *p_lcb, UINT16 reason, UINT8 rem_id);
extern void l2cu_reject_ble_connection (tL2C_LCB *p_lcb, UINT8 rem_id, UINT16 result);
extern void l2cu_send_peer_ble_credit_based_conn_res (tL2C_CCB *p_ccb, UINT16 result);
extern void l2cu_send_peer_ble_credit_based_conn_req (tL2C_CCB *p_ccb);
extern void l2cu_send_peer_ble_flow_control_credit(tL2C_CCB *p_ccb, UINT16 credit_value);
extern void l2cu_send_peer_ble_credit_based_disconn_req(tL2C_CCB *p_ccb);

#endif

extern BOOLEAN l2cu_initialize_fixed_ccb (tL2C_LCB *p_lcb, UINT16 fixed_cid, tL2CAP_FCR_OPTS *p_fcr);
extern void    l2cu_no_dynamic_ccbs (tL2C_LCB *p_lcb);
extern void    l2cu_process_fixed_chnl_resp (tL2C_LCB *p_lcb);


/* 为Broadcom Aware提供的功能
****************************************
*/
extern BOOLEAN  l2cu_check_feature_req (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len);
extern void     l2cu_check_feature_rsp (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len);
extern void     l2cu_send_feature_req (tL2C_CCB *p_ccb);

extern tL2C_RCB *l2cu_allocate_rcb (UINT16 psm);
extern tL2C_RCB *l2cu_find_rcb_by_psm (UINT16 psm);
extern void     l2cu_release_rcb (tL2C_RCB *p_rcb);
extern tL2C_RCB *l2cu_allocate_ble_rcb (UINT16 psm);
extern tL2C_RCB *l2cu_find_ble_rcb_by_psm (UINT16 psm);


extern UINT8    l2cu_process_peer_cfg_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2cu_process_peer_cfg_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2cu_process_our_cfg_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2cu_process_our_cfg_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);

extern void     l2cu_device_reset (void);
extern tL2C_LCB *l2cu_find_lcb_by_state (tL2C_LINK_STATE state);
extern BOOLEAN  l2cu_lcb_disconnecting (void);

extern BOOLEAN l2cu_create_conn (tL2C_LCB *p_lcb, tBT_TRANSPORT transport);
extern BOOLEAN l2cu_create_conn_after_switch (tL2C_LCB *p_lcb);
extern BT_HDR *l2cu_get_next_buffer_to_send (tL2C_LCB *p_lcb);
extern void    l2cu_resubmit_pending_sec_req (BD_ADDR p_bda);
extern void    l2cu_initialize_amp_ccb (tL2C_LCB *p_lcb);
extern void    l2cu_adjust_out_mps (tL2C_CCB *p_ccb);

/* l2c_link.c提供的函数
************************************
*/
extern BOOLEAN  l2c_link_hci_conn_req (BD_ADDR bd_addr);
extern BOOLEAN  l2c_link_hci_conn_comp (UINT8 status, UINT16 handle, BD_ADDR p_bda);
extern BOOLEAN  l2c_link_hci_disc_comp (UINT16 handle, UINT8 reason);
extern BOOLEAN  l2c_link_hci_qos_violation (UINT16 handle);
extern void     l2c_link_timeout (tL2C_LCB *p_lcb);
extern void     l2c_info_timeout (tL2C_LCB *p_lcb);
extern void     l2c_link_check_send_pkts (tL2C_LCB *p_lcb, tL2C_CCB *p_ccb, BT_HDR *p_buf);
extern void     l2c_link_adjust_allocation (void);
extern void     l2c_link_process_num_completed_pkts (UINT8 *p);
extern void     l2c_link_process_num_completed_blocks (UINT8 controller_id, UINT8 *p, UINT16 evt_len);
extern void     l2c_link_processs_num_bufs (UINT16 num_lm_acl_bufs);
extern UINT8    l2c_link_pkts_rcvd (UINT16 *num_pkts, UINT16 *handles);
extern void     l2c_link_role_changed (BD_ADDR bd_addr, UINT8 new_role, UINT8 hci_status);
extern void     l2c_link_sec_comp (BD_ADDR p_bda, tBT_TRANSPORT transport, void *p_ref_data, UINT8 status);
extern void     l2c_link_segments_xmitted (BT_HDR *p_msg);
extern void     l2c_pin_code_request (BD_ADDR bd_addr);
extern void     l2c_link_adjust_chnl_allocation (void);

#if (BLE_INCLUDED == TRUE)
extern void     l2c_link_processs_ble_num_bufs (UINT16 num_lm_acl_bufs);
#endif

#if L2CAP_WAKE_PARKED_LINK == TRUE
extern BOOLEAN  l2c_link_check_power_mode ( tL2C_LCB *p_lcb );
#define L2C_LINK_CHECK_POWER_MODE(x) l2c_link_check_power_mode ((x))
#else  // L2CAP_WAKE_PARKED_LINK
#define L2C_LINK_CHECK_POWER_MODE(x) (FALSE)
#endif  // L2CAP_WAKE_PARKED_LINK

#if L2CAP_CONFORMANCE_TESTING == TRUE
/* 仅用于一致性测试*/
extern void l2cu_set_info_rsp_mask (UINT32 mask);
#endif

/* l2c_csm.c提供的函数
************************************
*/
extern void l2c_csm_execute (tL2C_CCB *p_ccb, UINT16 event, void *p_data);

extern void l2c_enqueue_peer_data (tL2C_CCB *p_ccb, BT_HDR *p_buf);


/* l2c_fcr.c提供的函数
************************************
*/
extern void     l2c_fcr_cleanup (tL2C_CCB *p_ccb);
extern void     l2c_fcr_proc_pdu (tL2C_CCB *p_ccb, BT_HDR *p_buf);
extern void     l2c_fcr_proc_tout (tL2C_CCB *p_ccb);
extern void     l2c_fcr_proc_ack_tout (tL2C_CCB *p_ccb);
extern void     l2c_fcr_send_S_frame (tL2C_CCB *p_ccb, UINT16 function_code, UINT16 pf_bit);
extern BT_HDR   *l2c_fcr_clone_buf (BT_HDR *p_buf, UINT16 new_offset, UINT16 no_of_bytes);
extern BOOLEAN  l2c_fcr_is_flow_controlled (tL2C_CCB *p_ccb);
extern BT_HDR   *l2c_fcr_get_next_xmit_sdu_seg (tL2C_CCB *p_ccb, UINT16 max_packet_length);
extern void     l2c_fcr_start_timer (tL2C_CCB *p_ccb);

/* 配置协商*/
extern UINT8    l2c_fcr_chk_chan_modes (tL2C_CCB *p_ccb);
extern BOOLEAN  l2c_fcr_adj_our_req_options (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2c_fcr_adj_our_rsp_options (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_peer_cfg);
extern BOOLEAN  l2c_fcr_renegotiate_chan(tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern UINT8    l2c_fcr_process_peer_cfg_req(tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg);
extern void     l2c_fcr_adj_monitor_retran_timeout (tL2C_CCB *p_ccb);
extern void     l2c_fcr_stop_timer (tL2C_CCB *p_ccb);
extern void     l2c_fcr_free_timer (tL2C_CCB *p_ccb);
/* l2c_ble.c提供的函数
************************************
*/
#if (BLE_INCLUDED == TRUE)
extern BOOLEAN l2cble_create_conn (tL2C_LCB *p_lcb);
extern void l2cble_process_sig_cmd (tL2C_LCB *p_lcb, UINT8 *p, UINT16 pkt_len);
extern void l2cble_conn_comp (UINT16 handle, UINT8 role, BD_ADDR bda, tBLE_ADDR_TYPE type,
                              UINT16 conn_interval, UINT16 conn_latency, UINT16 conn_timeout);
extern BOOLEAN l2cble_init_direct_conn (tL2C_LCB *p_lcb);
extern void l2cble_notify_le_connection (BD_ADDR bda);
extern void l2c_ble_link_adjust_allocation (void);
extern void l2cble_process_conn_update_evt (UINT16 handle, UINT8 status, UINT16 conn_interval,
                                                              UINT16 conn_latency, UINT16 conn_timeout);
extern void l2cble_get_conn_param_format_err_from_contoller(UINT8 status, UINT16 handle);

extern void l2cble_credit_based_conn_req (tL2C_CCB *p_ccb);
extern void l2cble_credit_based_conn_res (tL2C_CCB *p_ccb, UINT16 result);
extern void l2cble_send_peer_disc_req(tL2C_CCB *p_ccb);
extern void l2cble_send_flow_control_credit(tL2C_CCB *p_ccb, UINT16 credit_value);
extern BOOLEAN l2ble_sec_access_req(BD_ADDR bd_addr, UINT16 psm, BOOLEAN is_originator, tL2CAP_SEC_CBACK *p_callback, void *p_ref_data);


#if (defined BLE_LLT_INCLUDED) && (BLE_LLT_INCLUDED == TRUE)
extern void l2cble_process_rc_param_request_evt(UINT16 handle, UINT16 int_min, UINT16 int_max,
        UINT16 latency, UINT16 timeout);
#endif

extern void l2cble_update_data_length(tL2C_LCB *p_lcb);
extern void l2cble_set_fixed_channel_tx_data_length(BD_ADDR remote_bda, UINT16 fix_cid,
        UINT16 tx_mtu);
extern void l2c_send_update_conn_params_cb(tL2C_LCB *p_lcb, UINT8 status);
extern void l2cble_process_data_length_change_event(UINT16 handle, UINT16 tx_data_len,
        UINT16 rx_data_len);
extern UINT32 CalConnectParamTimeout(tL2C_LCB *p_lcb);

#endif
extern void l2cu_process_fixed_disc_cback (tL2C_LCB *p_lcb);

#ifdef __cplusplus
}
#endif

#endif

