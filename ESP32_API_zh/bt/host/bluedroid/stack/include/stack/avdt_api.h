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
 * 此接口文件包含音频视频分发传输协议（AVDTP）的接口。
 *
 ******************************************************************************/
#ifndef AVDT_API_H
#define AVDT_API_H

#include "stack/bt_types.h"
#include "common/bt_target.h"

/*****************************************************************************
**  常量
*****************************************************************************/
#ifndef AVDT_VERSION
#define AVDT_VERSION                0x0102
#endif
#define AVDT_VERSION_SYNC           0x0103

/* API函数返回值结果代码。*/
#define AVDT_SUCCESS                0       /* 功能成功*/
#define AVDT_BAD_PARAMS             1       /* 无效的参数*/
#define AVDT_NO_RESOURCES           2       /* 资源不足*/
#define AVDT_BAD_HANDLE             3       /* 错误的句柄*/
#define AVDT_BUSY                   4       /* 程序已在进行中*/
#define AVDT_WRITE_FAIL             5       /* 写入失败*/

/* 用于访问codec_info[]中的编解码器类型的索引。*/
#define AVDT_CODEC_TYPE_INDEX       2

/* 适应层标头的字节大小。*/
#define AVDT_AL_HDR_SIZE         3

/* 媒体数据包标头的字节大小。*/
#define AVDT_MEDIA_HDR_SIZE         12

/* AVDTP 7.5.3适配层分段未分段传输包的原始长度应由适配层报头的两字节长度字段指定*/
#define AVDT_MAX_MEDIA_SIZE         (0xFFFF - AVDT_MEDIA_HDR_SIZE)

/* 报告MULTI_AV特定事件时使用该句柄*/
#define AVDT_MULTI_AV_HANDLE        0xFF

/* 协议栈为媒体数据包的协议头所需的字节数。这是媒体包报头、L2CAP包报头和HCI报头的大小。
*/
#define AVDT_MEDIA_OFFSET           23

/* 应用程序使用标记位来标记重要事件，例如数据流中的帧边界。此常量用于检查或设置AVDT_Writeeq（）或AVDT_DATA_IND_EVT的m_pt参数中的标记位。
*/
#define AVDT_MARKER_SET             0x80

/* SEP类型。这表示流端点类型。*/
#define AVDT_TSEP_SRC               0       /* 来源SEP*/
#define AVDT_TSEP_SNK               1       /* 水槽SEP*/

/* 适应的引发剂/受体作用*/
#define AVDT_INT                0       /* 引发剂，引发剂*/
#define AVDT_ACP                1       /* 承兑人*/

/* 媒体类型。这表示流端点的媒体类型。*/
#define AVDT_MEDIA_AUDIO            0       /* 音频SEP*/
#define AVDT_MEDIA_VIDEO            1       /* 视频SEP*/
#define AVDT_MEDIA_MULTI            2       /* 多媒体SEP*/

/* 用于报告数据包*/
#define AVDT_RTCP_PT_SR         200     /* 数据包类型-SR（发件人报告）*/
#define AVDT_RTCP_PT_RR         201     /* 数据包类型-RR（接收方报告）*/
#define AVDT_RTCP_PT_SDES       202     /* 数据包类型-SDES（源描述）*/
typedef UINT8 AVDT_REPORT_TYPE;

#define AVDT_RTCP_SDES_CNAME    1       /* SDES项目CNAME*/
#ifndef AVDT_MAX_CNAME_SIZE
#define AVDT_MAX_CNAME_SIZE     28
#endif

/* 协议服务功能。这表示流端点的协议服务能力。该值是遮罩。多个值可以与按位OR组合。
*/
#define AVDT_PSC_TRANS              (1<<1)  /* 媒体传输*/
#define AVDT_PSC_REPORT             (1<<2)  /* 报告*/
#define AVDT_PSC_RECOV              (1<<3)  /* 恢复*/
#define AVDT_PSC_HDRCMP             (1<<5)  /* 收割台压缩*/
#define AVDT_PSC_MUX                (1<<6)  /* 多路复用*/
#define AVDT_PSC_DELAY_RPT          (1<<8)  /* 延迟报告*/

/* 恢复类型。这表示恢复类型。*/
#define AVDT_RECOV_RFC2733          1       /* RFC2733回收*/

/* 收割台压缩功能。这表示标头压缩能力。该值是遮罩。多个值可以与按位OR组合。
*/
#define AVDT_HDRCMP_MEDIA           (1<<5)  /* 可用于媒体数据包*/
#define AVDT_HDRCMP_RECOV           (1<<6)  /* 可用于恢复数据包*/
#define AVDT_HDRCMP_BACKCH          (1<<7)  /* 支持后通道*/

/* 多路复用功能掩码。*/
#define AVDT_MUX_FRAG               (1<<7)  /* 允许自适应层分段*/

/* 应用程序服务类别。这表示应用程序服务类别。
*/
#define AVDT_ASC_PROTECT            4       /* 内容保护*/
#define AVDT_ASC_CODEC              7       /* 编解码器*/

/* 错误代码。以下是AVDTP和GAVDP规范中定义的错误代码。这些错误代码在AVDTP和应用程序之间传递协议错误。AVDTP和GAVDP规范中对错误代码及其适当使用进行了更详细的描述。这些错误代码与AVDTP API函数返回的结果值无关。
*/
#define AVDT_ERR_HEADER             0x01    /* 数据包标头格式错误*/
#define AVDT_ERR_LENGTH             0x11    /* 数据包长度错误*/
#define AVDT_ERR_SEID               0x12    /* 无效的SEID*/
#define AVDT_ERR_IN_USE             0x13    /* SEP正在使用*/
#define AVDT_ERR_NOT_IN_USE         0x14    /* SEP未使用*/
#define AVDT_ERR_CATEGORY           0x17    /* 服务类别错误*/
#define AVDT_ERR_PAYLOAD            0x18    /* 有效负载格式错误*/
#define AVDT_ERR_NSC                0x19    /* 请求的命令不受支持*/
#define AVDT_ERR_INVALID_CAP        0x1A    /* 重新配置尝试的无效功能*/
#define AVDT_ERR_RECOV_TYPE         0x22    /* 未定义请求的恢复类型*/
#define AVDT_ERR_MEDIA_TRANS        0x23    /* 媒体传输能力不正确*/
#define AVDT_ERR_RECOV_FMT          0x25    /* 恢复服务功能不正确*/
#define AVDT_ERR_ROHC_FMT           0x26    /* 收割台压缩服务能力不正确*/
#define AVDT_ERR_CP_FMT             0x27    /* 内容保护服务功能不正确*/
#define AVDT_ERR_MUX_FMT            0x28    /* 多路复用服务能力不正确*/
#define AVDT_ERR_UNSUP_CFG          0x29    /* 不支持配置*/
#define AVDT_ERR_BAD_STATE          0x31    /* 无法在此状态下处理消息*/
#define AVDT_ERR_REPORT_FMT         0x65    /* 报告服务功能不正确*/
#define AVDT_ERR_SERVICE            0x80    /* 服务类别无效*/
#define AVDT_ERR_RESOURCE           0x81    /* 资源不足*/
#define AVDT_ERR_INVALID_MCT        0xC1    /* 无效的媒体编解码器类型*/
#define AVDT_ERR_UNSUP_MCT          0xC2    /* 不支持的媒体编解码器类型*/
#define AVDT_ERR_INVALID_LEVEL      0xC3    /* 无效的级别*/
#define AVDT_ERR_UNSUP_LEVEL        0xC4    /* 不支持的级别*/
#define AVDT_ERR_INVALID_CP         0xE0    /* 无效的内容保护类型*/
#define AVDT_ERR_INVALID_FORMAT     0xE1    /* 无效的内容保护格式*/

/* 其他错误代码。这表示除了规范中定义的错误代码之外，AVDTP使用的错误代码。
*/
#define AVDT_ERR_CONNECT            0x07    /* 连接失败。*/
#define AVDT_ERR_TIMEOUT            0x08    /* 响应超时。*/

/* 控制回调事件。*/
#define AVDT_DISCOVER_CFM_EVT       0       /* 发现确认*/
#define AVDT_GETCAP_CFM_EVT         1       /* 获取功能确认*/
#define AVDT_OPEN_CFM_EVT           2       /* 打开确认*/
#define AVDT_OPEN_IND_EVT           3       /* 打开指示灯*/
#define AVDT_CONFIG_IND_EVT         4       /* 配置指示*/
#define AVDT_START_CFM_EVT          5       /* 启动确认*/
#define AVDT_START_IND_EVT          6       /* 启动指示*/
#define AVDT_SUSPEND_CFM_EVT        7       /* 暂停确认*/
#define AVDT_SUSPEND_IND_EVT        8       /* 暂停指示*/
#define AVDT_CLOSE_CFM_EVT          9       /* 关闭确认*/
#define AVDT_CLOSE_IND_EVT          10      /* 关闭指示*/
#define AVDT_RECONFIG_CFM_EVT       11      /* 重新配置确认*/
#define AVDT_RECONFIG_IND_EVT       12      /* 重新配置指示*/
#define AVDT_SECURITY_CFM_EVT       13      /* 安全性确认*/
#define AVDT_SECURITY_IND_EVT       14      /* 安全指示*/
#define AVDT_WRITE_CFM_EVT          15      /* 写入确认*/
#define AVDT_CONNECT_IND_EVT        16      /* 信号通道已连接*/
#define AVDT_DISCONNECT_IND_EVT     17      /* 信号通道断开*/
#define AVDT_REPORT_CONN_EVT        18      /* 报告通道已连接*/
#define AVDT_REPORT_DISCONN_EVT     19      /* 报告通道已断开*/
#define AVDT_DELAY_REPORT_EVT       20      /* 收到延迟报告*/
#define AVDT_DELAY_REPORT_CFM_EVT   21      /* 收到延迟报告响应*/

#define AVDT_MAX_EVT                (AVDT_DELAY_REPORT_CFM_EVT)

/* AVDT的PSM*/
#define AVDT_PSM                    0x0019

/* 不支持的协议命令消息。该值用于tAVDT_CS*/
#define AVDT_NSC_SUSPEND            0x01    /* 不支持挂起命令*/
#define AVDT_NSC_RECONFIG           0x02    /* 不支持重新配置命令*/
#define AVDT_NSC_SECURITY           0x04    /* 不支持安全命令*/

/* AVDT断开原因*/
#define AVDT_DISC_RSN_NORMAL        0
#define AVDT_DISC_RSN_ABNORMAL      (0xce)  /* 意外断开*/
/*****************************************************************************
**  类型定义
*****************************************************************************/

typedef struct {
    UINT32  ntp_sec;        /* NTP时间：相对于1900年1月1日0h UTC的秒数*/
    UINT32  ntp_frac;       /* NTP时间：小数部分*/
    UINT32  rtp_time;       /* RTP标头中的时间戳*/
    UINT32  pkt_count;      /* 发件人的数据包计数：从开始传输到生成此SR数据包为止。*/
    UINT32  octet_count;    /* 发件人的八位字节计数：相同的注释*/
} tAVDT_SENDER_INFO;

typedef struct {
    UINT8   frag_lost;      /* 自上次RR以来损失的分数*/
    UINT32  packet_lost;    /* 自开始以来丢失的数据包的累积数量*/
    UINT32  seq_num_rcvd;   /* 接收的扩展最高序列号*/
    UINT32  jitter;         /* 到达间隔抖动*/
    UINT32  lsr;            /* 上次SR时间戳*/
    UINT32  dlsr;           /* 自上次SR以来的延迟*/
} tAVDT_REPORT_BLK;

typedef union {
    tAVDT_SENDER_INFO   sr;
    tAVDT_REPORT_BLK    rr;
    UINT8               cname[AVDT_MAX_CNAME_SIZE + 1];
} tAVDT_REPORT_DATA;

/* 此结构包含在注册时设置的参数。*/
typedef struct {
    UINT16      ctrl_mtu;   /* AVDTP信令信道的L2CAP MTU*/
    UINT8       ret_tout;   /* AVDTP信令重传超时*/
    UINT8       sig_tout;   /* AVDTP信令消息超时*/
    UINT8       idle_tout;  /* AVDTP空闲信令信道超时*/
    UINT8       sec_mask;   /* BTM_SetSecurityLevel（）的安全掩码*/
} tAVDT_REG;

/* 此结构包含SEP信息。此信息在发现过程中传输。
*/
typedef struct {
    BOOLEAN     in_use;         /* 如果流当前正在使用，则为TRUE*/
    UINT8       seid;           /* 流端点标识符*/
    UINT8       media_type;     /* 媒体类型*/
    UINT8       tsep;           /* SEP类型*/
} tAVDT_SEP_INFO;

/* 此结构包含SEP配置。*/
typedef struct {
    UINT8   codec_info[AVDT_CODEC_SIZE];        /* 编解码器功能阵列*/
    UINT8   protect_info[AVDT_PROTECT_SIZE];    /* 内容保护功能*/
    UINT8   num_codec;                          /* 媒体编解码器信息元素的数量*/
    UINT8   num_protect;                        /* 内容保护信息元素的数量*/
    UINT16  psc_mask;                           /* 协议服务功能掩码*/
    UINT8   recov_type;                         /* 恢复类型*/
    UINT8   recov_mrws;                         /* 最大恢复窗口大小*/
    UINT8   recov_mnmp;                         /* 恢复最大媒体数据包数*/
    UINT8   hdrcmp_mask;                        /* 收割台压缩功能*/
#if AVDT_MULTIPLEXING == TRUE
    UINT8   mux_mask;                           /* 多路复用功能。AVDT_MUX_XXX位可以与逐位OR组合*/
    UINT8   mux_tsid_media;                     /* 媒体传输会话的TSID*/
    UINT8   mux_tcid_media;                     /* 媒体传输会话的TCID*/
    UINT8   mux_tsid_report;                    /* 用于报告传输会话的TSID*/
    UINT8   mux_tcid_report;                    /* 用于报告传输会话的TCID*/
    UINT8   mux_tsid_recov;                     /* 恢复传输会话的TSID*/
    UINT8   mux_tcid_recov;                     /* 恢复传输会话的TCID*/
#endif
} tAVDT_CFG;

/* 回调事件参数的标头结构。*/
typedef struct {
    UINT8           err_code;           /* 如果操作成功，则为零；如果操作失败，则为非零*/
    UINT8           err_param;          /* 某些事件包含错误参数*/
    UINT8           label;              /* 交易记录标签*/
    UINT8           seid;               /* 仅供内部使用*/
    UINT8           sig_id;             /* 仅供内部使用*/
    UINT8           ccb_idx;            /* 仅供内部使用*/
} tAVDT_EVT_HDR;

/* 此数据结构与AVDT_GETCAP_CFM_EVT、AVDT_RECONFIG_IND_EVT和AVDT_REONFIG_CFM_EVT相关联。
*/
typedef struct {
    tAVDT_EVT_HDR   hdr;                /* 事件标题*/
    tAVDT_CFG       *p_cfg;             /* 指向此SEP配置的指针*/
} tAVDT_CONFIG;

/* 此数据结构与AVDT_CONFIG_IND_EVT相关联。*/
typedef struct {
    tAVDT_EVT_HDR   hdr;                /* 事件标题*/
    tAVDT_CFG       *p_cfg;             /* 指向此SEP配置的指针*/
    UINT8           int_seid;           /* 启动操作的流的流端点ID*/
} tAVDT_SETCONFIG;

/* 该数据结构与AVDT_OPEN_IND_EVT和AVDT_OPEN_CFM_EVT相关。*/
typedef struct {
    tAVDT_EVT_HDR   hdr;                /* 事件标题*/
    UINT16          peer_mtu;           /* 对等体的传输信道L2CAP MTU*/
    UINT16          lcid;               /* 媒体频道的L2CAP LCID*/
} tAVDT_OPEN;

/* 此数据结构与AVDT_SECURITY_IND_EVT和AVDT_SECURITY_CFM_EVT相关联。
*/
typedef struct {
    tAVDT_EVT_HDR   hdr;                /* 事件标题*/
    UINT8           *p_data;            /* 指向安全数据的指针*/
    UINT16          len;                /* 安全数据的字节长度*/
} tAVDT_SECURITY;

/* 此数据结构与AVDT_DISCOVER_CFM_EVT相关。*/
typedef struct {
    tAVDT_EVT_HDR   hdr;                /* 事件标题*/
    tAVDT_SEP_INFO  *p_sep_info;        /* 指向SEP信息的指针*/
    UINT8           num_seps;           /* 流端点数*/
} tAVDT_DISCOVER;

/* 此数据结构与AVDT_DELAY_REPORT_EVT相关。*/
typedef struct {
    tAVDT_EVT_HDR   hdr;                /* 事件标题*/
    UINT16          delay;              /* 延迟值*/
} tAVDT_DELAY_RPT;

/* 所有控件回调事件数据结构的联合*/
typedef union {
    tAVDT_EVT_HDR       hdr;
    tAVDT_DISCOVER      discover_cfm;
    tAVDT_CONFIG        getcap_cfm;
    tAVDT_OPEN          open_cfm;
    tAVDT_OPEN          open_ind;
    tAVDT_SETCONFIG     config_ind;
    tAVDT_EVT_HDR       start_cfm;
    tAVDT_EVT_HDR       suspend_cfm;
    tAVDT_EVT_HDR       close_cfm;
    tAVDT_CONFIG        reconfig_cfm;
    tAVDT_CONFIG        reconfig_ind;
    tAVDT_SECURITY      security_cfm;
    tAVDT_SECURITY      security_ind;
    tAVDT_EVT_HDR       connect_ind;
    tAVDT_EVT_HDR       disconnect_ind;
    tAVDT_EVT_HDR       report_conn;
    tAVDT_DELAY_RPT     delay_rpt_cmd;
} tAVDT_CTRL;

/* 这是控件回调函数。此函数将控制事件传递给应用程序。此函数对于所有已注册的流端点以及AVDT_DiscoverReq（）和AVDT_GetCapRequest（）函数都是必需的。
**
*/
typedef void (tAVDT_CTRL_CBACK)(UINT8 handle, BD_ADDR bd_addr, UINT8 event,
                                tAVDT_CTRL *p_data);

/* 这是数据回调函数。当AVDTP为应用程序准备好媒体包时，执行该命令。此函数对于SNK端点是必需的，而不适用于SRC端点。
*/
typedef void (tAVDT_DATA_CBACK)(UINT8 handle, BT_HDR *p_pkt, UINT32 time_stamp,
                                UINT8 m_pt);

#if AVDT_MULTIPLEXING == TRUE
/* 这是数据回调函数的第二个版本。此版本使用AVDT_SetMediaBuf分配的应用程序缓冲区。调用方可以在回调期间分配不同的缓冲区，也可以保留当前缓冲区以供进一步使用。当AVDTP为应用程序准备好媒体包时，调用此回调。此函数对于SNK端点是必需的，而不适用于SRC端点。
*/
typedef void (tAVDT_MEDIA_CBACK)(UINT8 handle, UINT8 *p_payload, UINT32 payload_len,
                                 UINT32 time_stamp, UINT16 seq_num, UINT8 m_pt, UINT8 marker);
#endif

#if AVDT_REPORTING == TRUE
/* 这是报表回调函数。当AVDTP为应用程序准备好报告数据包时，执行该命令。使用AVDT_PSC_REPORT创建的流需要此函数。
*/
typedef void (tAVDT_REPORT_CBACK)(UINT8 handle, AVDT_REPORT_TYPE type,
                                  tAVDT_REPORT_DATA *p_data);
#endif

typedef UINT16 (tAVDT_GETCAP_REQ) (BD_ADDR bd_addr, UINT8 seid, tAVDT_CFG *p_cfg, tAVDT_CTRL_CBACK *p_cback);

/* 此结构包含创建流时所需的信息。它被传递给AVDT_CreateStream（）函数。
*/
typedef struct {
    tAVDT_CFG           cfg;            /* SEP配置*/
    tAVDT_CTRL_CBACK    *p_ctrl_cback;  /* 控制回调函数*/
    tAVDT_DATA_CBACK    *p_data_cback;  /* 数据回调函数*/
#if AVDT_MULTIPLEXING == TRUE
    tAVDT_MEDIA_CBACK   *p_media_cback; /* 媒体回调函数。只有p_data_cback为NULL时才会调用它*/
#endif
#if AVDT_REPORTING == TRUE
    tAVDT_REPORT_CBACK  *p_report_cback;/* 报告回调函数。*/
#endif
    UINT16              mtu;            /* 传输通道的L2CAP MTU*/
    UINT16              flush_to;       /* 传输通道的L2CAP刷新超时*/
    UINT8               tsep;           /* SEP类型*/
    UINT8               media_type;     /* 媒体类型*/
    UINT16              nsc_mask;       /* 不支持的协议命令消息*/
} tAVDT_CS;

/* 写入请求中使用AVDT数据选项掩码*/
#define AVDT_DATA_OPT_NONE      0x00         /* 没有选项仍然添加RTP标头*/
#define AVDT_DATA_OPT_NO_RTP   (0x01 << 0)   /* 跳过添加RTP标头*/

typedef UINT8 tAVDT_DATA_OPT_MASK;



/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 功能AVDT_Register
**
** 说明这是AVDTP协议的系统级注册功能。此函数初始化AVDTP并准备协议堆栈以供其使用。在使用API的其他函数之前，系统或平台必须使用AVDTP调用该函数一次。
**
** 返回void
**
*******************************************************************************/
extern void AVDT_Register(tAVDT_REG *p_reg, tAVDT_CTRL_CBACK *p_cback);

/*******************************************************************************
** 函数AVDT_Degister
**
** 说明调用此函数以注销使用AVDTP协议的注册。当系统中的任何应用程序不再使用AVDTP时，将调用此函数。在调用此函数之前，必须使用AVDT_RemoveStream（）删除所有流。
**
** 返回void
**
*******************************************************************************/
extern void AVDT_Deregister(void);


/*******************************************************************************
** 函数AVDT_SINK_Activate
**
** 说明激活A2DP接收器的SEP。调整“使用中”参数。在激活的情况下，“正在使用”将变为“假”。A2DP SRC将以false接收in_use，并可以打开A2DP Sink连接
**
** 返回void
**
*******************************************************************************/
extern void AVDT_SINK_Activate(void);

/*******************************************************************************
** 函数AVDT_SINK_Dactivate
**
** 说明停用A2DP接收器的SEP。调整“使用中”参数。激活时，“使用中”将变为TRUE。A2DP SRC将以true接收in_use，并且不会打开A2DP Sink连接
**
** 返回void。
**
*******************************************************************************/
extern void AVDT_SINK_Deactivate(void);

/*******************************************************************************
** 功能AVDT_AbortRq
**
** 说明触发中止请求以通过AVDTP中止相关的强制PTS测试用例。
**
** 返回void。
**
*******************************************************************************/
extern void AVDT_AbortReq(UINT8 handle);

/*******************************************************************************
** 函数AVDT_CreateStream
**
** 描述创建流终结点。创建流端点后，应用程序可以启动此端点与对等设备上的端点之间的连接。此外，对等设备可以发现、获取功能并连接到此端点。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_CreateStream(UINT8 *p_handle, tAVDT_CS *p_cs);

/*******************************************************************************
** 函数AVDT_RemoveStream
**
** 说明删除流终结点。当应用程序不再使用流端点时调用此函数。如果在连接端点时调用此函数，则关闭连接，然后删除流端点。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_RemoveStream(UINT8 handle);

/*******************************************************************************
** 函数AVDT_DiscoverReq
**
** 描述此功能启动到对等设备上AVDTP服务的连接（如果尚未存在），并发现对等设备上的流端点。（请注意，AVDTP发现与SDP发现无关）。无论是否存在到对等设备的AVDTP连接，都可以随时调用此函数。
**
**                  发现完成后，AVDT_DISCOVER_CFM_EVT将通过其回调函数发送到应用程序。在发现完成之前，应用程序不得再次对同一设备调用AVDT_GetCapReq（）或AVDT_DiscoverRequest（）。
**
**                  sep_info寻址的内存由应用程序分配。作为发现过程的一部分，AVDTP会将此内存写入。在应用程序收到AVDT_DISCOVER_CFM_EVT之前，此内存必须保持可访问状态。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_DiscoverReq(BD_ADDR bd_addr, tAVDT_SEP_INFO *p_sep_info,
                               UINT8 max_seps, tAVDT_CTRL_CBACK *p_cback);


/*******************************************************************************
** 函数AVDT_GetCapReq
**
** 描述此功能启动到对等设备上的AVDTP服务的连接（如果尚未存在），并获取对等设备上流端点的功能。无论是否存在到对等设备的AVDTP连接，都可以随时调用此函数。
**
**                  当过程完成时，AVDT_GETCAP_CFM_EVT通过其回调函数发送到应用程序。在过程完成之前，应用程序不得再次调用AVDT_GetCapReq（）或AVDT_DiscoverReq（。
**
**                  p_cfg指向的内存由应用程序分配。此内存由AVDTP写入，作为获取功能过程的一部分。在应用程序收到AVDT_GETCAP_CFM_EVT之前，此内存必须保持可访问状态。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_GetCapReq(BD_ADDR bd_addr, UINT8 seid, tAVDT_CFG *p_cfg,
                             tAVDT_CTRL_CBACK *p_cback);

/*******************************************************************************
** 函数AVDT_GetAllCapReq
**
** 描述此功能启动到对等设备上的AVDTP服务的连接（如果尚未存在），并获取对等设备上流端点的功能。无论是否存在到对等设备的AVDTP连接，都可以随时调用此函数。
**
**                  当过程完成时，AVDT_GETCAP_CFM_EVT通过其回调函数发送到应用程序。在过程完成之前，应用程序不得再次调用AVDT_GetCapReq（）或AVDT_DiscoverReq（。
**
**                  p_cfg指向的内存由应用程序分配。此内存由AVDTP写入，作为获取功能过程的一部分。在应用程序收到AVDT_GETCAP_CFM_EVT之前，此内存必须保持可访问状态。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_GetAllCapReq(BD_ADDR bd_addr, UINT8 seid, tAVDT_CFG *p_cfg,
                                tAVDT_CTRL_CBACK *p_cback);

/*******************************************************************************
** 函数AVDT_DlayReport
**
** 描述此功能向与特定SEID相关联的对等设备发送延迟报告。此函数由SNK设备调用。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_DelayReport(UINT8 handle, UINT8 seid, UINT16 delay);

/*******************************************************************************
** 函数AVDT_OpenReq
**
** 说明此功能启动到对等设备上AVDTP服务的连接（如果尚未存在），并连接到对等设备的流端点。连接完成后，AVDT_OPEN_CFM_EVT将通过该句柄的控制回调函数发送到应用程序。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_OpenReq(UINT8 handle, BD_ADDR bd_addr, UINT8 seid,
                           tAVDT_CFG *p_cfg);


/*******************************************************************************
** 函数AVDT_ConfigRsp
**
** 描述响应来自对等设备的配置请求。如果应用程序通过其控制回调接收到AVDT_CONFIG_IND_EVT，则必须调用此函数。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_ConfigRsp(UINT8 handle, UINT8 label, UINT8 error_code,
                             UINT8 category);

/*******************************************************************************
** 功能AVDT_StartReq
**
** 描述启动一个或多个流终结点。这将启动流的媒体分组传输。之前必须打开所有流终结点。当流启动时，AVDT_START_CFM_EVT通过每个流的控制回调函数发送给应用程序。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_StartReq(UINT8 *p_handles, UINT8 num_handles);

/*******************************************************************************
** 函数AVDT_SuspendReq
**
** 说明挂起一个或多个流终结点。这将暂停流的媒体包传输。所有流终结点之前必须打开并启动。当流被挂起时，通过每个流的控制回调函数向应用程序发送AVDT_SUSPEND_FM_EVT。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_SuspendReq(UINT8 *p_handles, UINT8 num_handles);

/*******************************************************************************
** 函数AVDT_CloseReq
**
** 说明关闭流终结点。这将停止媒体数据包的传输，并关闭与此流端点关联的传输通道。当流关闭时，AVDT_CLOSE_CFM_EVT将通过该句柄的控制回调函数发送给应用程序。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_CloseReq(UINT8 handle);

/*******************************************************************************
** 函数AVDT_ReconfigReq
**
** 描述重新配置流终结点。这允许应用程序在流端点打开后更改其编解码器或内容保护功能。仅当流已打开但未启动或流已挂起时，才能调用此函数。当过程完成时，AVDT_RECONFIG_CFM_EVT通过该句柄的控制回调函数发送给应用程序。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_ReconfigReq(UINT8 handle, tAVDT_CFG *p_cfg);

/*******************************************************************************
** 函数AVDT_ReconfigRsp
**
** 描述响应来自对等设备的重新配置请求。如果应用程序通过其控制回调接收到AVDT_RECONFIG_IND_EVT，则必须调用此函数。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_ReconfigRsp(UINT8 handle, UINT8 label, UINT8 error_code,
                               UINT8 category);

/*******************************************************************************
** 函数AVDT_SecurityReq
**
** 说明向对等设备发送安全请求。安全过程完成后，将通过该句柄的控制回调函数向应用程序发送AVDT_security_CFM_EVT。（请注意，AVDTP安全程序与蓝牙链路级别安全无关。）
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_SecurityReq(UINT8 handle, UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 函数AVDT_SecurityRsp
**
** 描述响应来自对等设备的安全请求。如果应用程序通过其控制回调接收到AVDT_SECURITY_IND_EVT，则必须调用此函数。（请注意，AVDTP安全程序与蓝牙链路级别安全无关。）
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_SecurityRsp(UINT8 handle, UINT8 label, UINT8 error_code,
                               UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 函数AVDT_WriteReq
**
** 描述向对等设备发送媒体包。在调用此函数之前，必须启动流。此外，只有当流是SRC时，才能调用此函数。
**
**                  当AVDTP已发送媒体包并准备好下一个包时，AVDT_WRITE_CFM_EVT将通过控制回调发送给应用程序。应用程序必须等待AVDT_WRITE_CFM_EVT，然后才能调用AVDT_Writeeq（）。如果应用程序在收到事件之前调用AVDT_Writeeq（），则不会发送数据包。应用程序可以在接收到AVDT_START_CFM_EVT或AVDT_START _IND_EVT之后，对AVDT_Writeeq（）进行第一次调用。
**
**                  应用程序使用BT_HDR结构传递数据包。第2.1节描述了这种结构。偏移字段必须等于或大于AVDT_MEDIA_offset。这允许缓冲区中有足够的空间用于L2CAP和AVDTP标头。
**
**                  p_pkt指向的内存必须是应用程序分配的GKI缓冲区。该缓冲区将由协议栈释放；应用程序不能释放此缓冲区。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_WriteReq(UINT8 handle, BT_HDR *p_pkt, UINT32 time_stamp,
                            UINT8 m_pt);
/*******************************************************************************
** 函数AVDT_WriteReqOpt
**
** 描述向对等设备发送媒体包。在调用此函数之前，必须启动流。此外，只有当流是SRC时才能调用此函数
**
**                  当AVDTP已发送媒体包并准备好下一个包时，AVDT_WRITE_CFM_EVT将通过控制回调发送给应用程序。应用程序必须等待AVDT_WRITE_CFM_EVT，然后才能调用AVDT_Writeeq（）。如果应用程序在收到事件之前调用AVDT_Writeeq（），则不会发送数据包。应用程序可以在接收到AVDT_START_CFM_EVT或AVDT_START _IND_EVT之后，对AVDT_Writeeq（）进行第一次调用。
**
**                  应用程序使用BT_HDR结构传递数据包。该结构在第2.1节中进行了描述。偏移字段必须等于或大于AVDT_MEDIA_offset（如果指定了NO_RTP，则可以使用L2CAP_MIN_offset）。这在缓冲区中为L2CAP和AVDTP报头留出了足够的空间。
**
**                  p_pkt指向的内存必须是应用程序分配的GKI缓冲区。该缓冲区将由协议栈释放；应用程序不能释放此缓冲区。
**
**                  opt参数允许传递特定选项，如：
**                  -NO_RTP：不将RTP标头添加到缓冲区
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_WriteReqOpt(UINT8 handle, BT_HDR *p_pkt, UINT32 time_stamp,
                               UINT8 m_pt, tAVDT_DATA_OPT_MASK opt);

/*******************************************************************************
** 函数AVDT_ConnectReq
**
** 描述此功能启动到对等设备的AVDTP信令连接。连接完成后，AVDT_CONNECT_IND_EVT将通过其控制回调函数发送到应用程序。如果连接尝试失败，则发送AVDT_DISCONNECT_IND_EVT。安全掩码参数覆盖AVDT_Register（）中设置的传出安全掩码。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_ConnectReq(BD_ADDR bd_addr, UINT8 sec_mask,
                              tAVDT_CTRL_CBACK *p_cback);

/*******************************************************************************
** 函数AVDT_DisconnectReq
**
** 说明此功能断开与对等设备的AVDTP信令连接。断开连接时，AVDT_DISCONNECT_IND_EVT通过其控制回调函数发送到应用程序。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_DisconnectReq(BD_ADDR bd_addr, tAVDT_CTRL_CBACK *p_cback);

/*******************************************************************************
** 函数AVDT_GetL2CapChannel
**
** 说明获取句柄使用的L2CAP CID。
**
** 如果成功，则返回CID，否则为0。
**
*******************************************************************************/
extern UINT16 AVDT_GetL2CapChannel(UINT8 handle);

/*******************************************************************************
** 功能AVDT_GetSignalChannel
**
** 说明获取给定句柄的信号通道使用的L2CAP CID。
**
** 如果成功，则返回CID，否则为0。
**
*******************************************************************************/
extern UINT16 AVDT_GetSignalChannel(UINT8 handle, BD_ADDR bd_addr);

/*******************************************************************************
** 函数AVDT_WriteDataReq
**
** 描述向对等设备发送媒体包。在调用此函数之前，必须启动流。此外，只有当流是SRC时，才能调用此函数。
**
**                  当AVDTP已发送媒体包并准备好下一个包时，AVDT_WRITE_CFM_EVT将通过控制回调发送给应用程序。应用程序必须等待AVDT_WRITE_CFM_EVT，然后再调用AVDT_WriteDataReq（）。如果应用程序在收到事件之前调用AVDT_WriteDataReq（），则不会发送数据包。应用程序可以在接收到AVDT_START_CFM_EVT或AVDT_START _IND_EVT之后，对AVDT_WriteDataReq（）进行第一次调用。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_WriteDataReq(UINT8 handle, UINT8 *p_data, UINT32 data_len,
                                UINT32 time_stamp, UINT8 m_pt, UINT8 marker);

/*******************************************************************************
** 函数AVDT_SetMediaBuf
**
** 说明如果参数p_buf为NULL，则为媒体数据包分配缓冲区或禁止使用分配的缓冲区。只有当流是SNK时，才能调用此函数。
**
**                  AVDTP使用此缓冲区重新组合碎片化的媒体包。当AVDTP接收到完整的媒体包时，它调用AVDT_CreateStream（）分配的p_media_cback。此函数可以在回调期间调用，为下一个媒体包分配不同的缓冲区，也可以将当前缓冲区留给下一个包。
**
** 如果成功，则返回AVDT_SUCCESS，否则返回错误。
**
*******************************************************************************/
extern UINT16 AVDT_SetMediaBuf(UINT8 handle, UINT8 *p_buf, UINT32 buf_len);

/*******************************************************************************
** 函数AVDT_SendReport
**
** 描述
**
**
**
** 退换商品
**
*******************************************************************************/
extern UINT16 AVDT_SendReport(UINT8 handle, AVDT_REPORT_TYPE type,
                              tAVDT_REPORT_DATA *p_data);

/******************************************************************************
** 函数AVDT_SetTraceLevel
**
** 说明设置AVDT的跟踪级别。如果传递了0xff，则返回当前跟踪级别。
**
**                  输入参数：new_level：将AVDT跟踪设置为：0xff的级别返回当前设置。0—关闭跟踪。>=1-错误。>=2-警告。>=3-API。>=4-事件。>=5-调试。
**
** 如果输入参数为0xff，则返回新跟踪级别或当前跟踪级别。
**
******************************************************************************/
extern UINT8 AVDT_SetTraceLevel (UINT8 new_level);

#ifdef __cplusplus
}
#endif


#endif /* AVDT_API_H */

