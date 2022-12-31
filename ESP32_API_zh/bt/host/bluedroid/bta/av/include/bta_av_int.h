/******************************************************************************
 * 版权所有（C）2004-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA高级音频/视频的专用接口文件。
 *
 ******************************************************************************/
#ifndef BTA_AV_INT_H
#define BTA_AV_INT_H

#include "bta/bta_sys.h"
#include "bta/bta_api.h"
#include "bta/bta_av_api.h"
#include "stack/avdt_api.h"
#include "bta/bta_av_co.h"
#include "osi/list.h"

#if (BTA_AV_INCLUDED == TRUE)

/*****************************************************************************
**  常量
*****************************************************************************/

enum {
    /* 这些事件由AV主状态机处理*/
    BTA_AV_API_DISABLE_EVT = BTA_SYS_EVT_START(BTA_ID_AV),
    BTA_AV_API_REMOTE_CMD_EVT,
    BTA_AV_API_VENDOR_CMD_EVT,
    BTA_AV_API_VENDOR_RSP_EVT,
    BTA_AV_API_META_RSP_EVT,
    BTA_AV_API_RC_CLOSE_EVT,
    BTA_AV_AVRC_OPEN_EVT,
    BTA_AV_AVRC_MSG_EVT,
    BTA_AV_AVRC_NONE_EVT,

    /* 这些事件由AV流状态机处理*/
    BTA_AV_API_OPEN_EVT,
    BTA_AV_API_CLOSE_EVT,
    BTA_AV_AP_START_EVT,        /* 以下两个事件的顺序必须与*API_*EVT的顺序相同*/
    BTA_AV_AP_STOP_EVT,
    BTA_AV_API_RECONFIG_EVT,
    BTA_AV_API_PROTECT_REQ_EVT,
    BTA_AV_API_PROTECT_RSP_EVT,
    BTA_AV_API_RC_OPEN_EVT,
    BTA_AV_SRC_DATA_READY_EVT,
    BTA_AV_CI_SETCONFIG_OK_EVT,
    BTA_AV_CI_SETCONFIG_FAIL_EVT,
    BTA_AV_SDP_DISC_OK_EVT,
    BTA_AV_SDP_DISC_FAIL_EVT,
    BTA_AV_STR_DISC_OK_EVT,
    BTA_AV_STR_DISC_FAIL_EVT,
    BTA_AV_STR_GETCAP_OK_EVT,
    BTA_AV_STR_GETCAP_FAIL_EVT,
    BTA_AV_STR_OPEN_OK_EVT,
    BTA_AV_STR_OPEN_FAIL_EVT,
    BTA_AV_STR_START_OK_EVT,
    BTA_AV_STR_START_FAIL_EVT,
    BTA_AV_STR_CLOSE_EVT,
    BTA_AV_STR_CONFIG_IND_EVT,
    BTA_AV_STR_SECURITY_IND_EVT,
    BTA_AV_STR_SECURITY_CFM_EVT,
    BTA_AV_STR_WRITE_CFM_EVT,
    BTA_AV_STR_SUSPEND_CFM_EVT,
    BTA_AV_STR_RECONFIG_CFM_EVT,
    BTA_AV_AVRC_TIMER_EVT,
    BTA_AV_AVDT_CONNECT_EVT,
    BTA_AV_AVDT_DISCONNECT_EVT,
    BTA_AV_ROLE_CHANGE_EVT,
    BTA_AV_AVDT_DELAY_RPT_EVT,
    BTA_AV_ACP_CONNECT_EVT,

    /* 这些事件在状态机之外处理*/
    BTA_AV_API_ENABLE_EVT,
    BTA_AV_API_REGISTER_EVT,
    BTA_AV_API_DEREGISTER_EVT,
    BTA_AV_API_DISCONNECT_EVT,
    BTA_AV_CI_SRC_DATA_READY_EVT,
    BTA_AV_SIG_CHG_EVT,
    BTA_AV_SIG_TIMER_EVT,
    BTA_AV_SDP_AVRC_DISC_EVT,
    BTA_AV_AVRC_CLOSE_EVT,
    BTA_AV_CONN_CHG_EVT,
    BTA_AV_DEREG_COMP_EVT,
#if (BTA_AV_SINK_INCLUDED == TRUE)
    BTA_AV_API_SINK_ENABLE_EVT,
#endif
#if (AVDT_REPORTING == TRUE)
    BTA_AV_AVDT_RPT_CONN_EVT,
#endif
    BTA_AV_API_START_EVT,       /* 以下两个事件的顺序必须与*AP_*EVT的顺序相同*/
    BTA_AV_API_STOP_EVT
};

/* AV控制块状态机事件*/
#define BTA_AV_FIRST_SM_EVT     BTA_AV_API_DISABLE_EVT
#define BTA_AV_LAST_SM_EVT      BTA_AV_AVRC_NONE_EVT

/* AV流控制块状态机事件*/
#define BTA_AV_FIRST_SSM_EVT    BTA_AV_API_OPEN_EVT

/* 不经过状态机的事件*/
#define BTA_AV_FIRST_NSM_EVT    BTA_AV_API_ENABLE_EVT
#define BTA_AV_LAST_NSM_EVT     BTA_AV_API_STOP_EVT

/* 传递给两个ssm的API事件（通过bta_av_API_to_sm）*/
#define BTA_AV_FIRST_A2S_API_EVT    BTA_AV_API_START_EVT
#define BTA_AV_FIRST_A2S_SSM_EVT    BTA_AV_AP_START_EVT

#define BTA_AV_LAST_EVT             BTA_AV_API_STOP_EVT

/* 流中SEPS发现结果的最大数量*/
#define BTA_AV_NUM_SEPS         32

/* AVRC句柄的初始化值*/
#define BTA_AV_RC_HANDLE_NONE   0xFF

/* 用于服务发现的数据库大小*/
#define BTA_AV_DISC_BUF_SIZE        1000

/* 编解码器信息字节数组中媒体类型的偏移量*/
#define BTA_AV_MEDIA_TYPE_IDX       1

/* AVDTP安全数据的最大长度*/
#define BTA_AV_SECURITY_MAX_LEN     400

/* 当此数量的缓冲区排队到L2CAP时，检查在L2CAP排队的缓冲区数量*/
#define BTA_AV_QUEUE_DATA_CHK_NUM   L2CAP_HIGH_PRI_MIN_XMIT_QUOTA

/* 具有AVDT的ACL链接数*/
#define BTA_AV_NUM_LINKS            AVDT_NUM_LINKS

#define BTA_AV_CO_ID_TO_BE_STREAM(p, u32) {*(p)++ = (UINT8)((u32) >> 16); *(p)++ = (UINT8)((u32) >> 8); *(p)++ = (UINT8)(u32); }
#define BTA_AV_BE_STREAM_TO_CO_ID(u32, p) {u32 = (((UINT32)(*((p) + 2))) + (((UINT32)(*((p) + 1))) << 8) + (((UINT32)(*(p))) << 16)); (p) += 3;}

/* 这些位是为bta_avcb定义的。多v（_A）*/
#define BTA_AV_MULTI_AV_SUPPORTED   0x01
#define BTA_AV_MULTI_AV_IN_USE      0x02

#define TSEP_TO_SYS_ID(x) ((x) == AVDT_TSEP_SRC ? BTA_ID_AV : BTA_ID_AVK)

/*****************************************************************************
**  数据类型
*****************************************************************************/
/* BTA_AV_API_ENABLE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_AV_CBACK       *p_cback;
    tBTA_AV_FEAT        features;
    tBTA_SEC            sec_mask;
} tBTA_AV_API_ENABLE;

/* BTA_AV_API_REG_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    char                p_service_name[BTA_SERVICE_NAME_LEN + 1];
    UINT8               app_id;
    UINT8               tsep; // 本地SEP类型
    tBTA_AV_DATA_CBACK  *p_app_data_cback;
    tBTA_AV_CO_FUNCTS   *bta_av_cos;
    tBTA_AVRC_CO_FUNCTS *bta_avrc_cos;
} tBTA_AV_API_REG;


enum {
    BTA_AV_RS_NONE,     /* 直接API调用*/
    BTA_AV_RS_OK,       /* 角色切换结果-成功*/
    BTA_AV_RS_FAIL,     /* 角色切换结果-失败*/
    BTA_AV_RS_DONE      /* 角色切换完成-继续*/
};
typedef UINT8 tBTA_AV_RS_RES;
/* BTA_AV_API_OPEN_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    BOOLEAN             use_rc;
    tBTA_SEC            sec_mask;
    tBTA_AV_RS_RES      switch_res;
    UINT16              uuid;  /* 启动器的uuid*/
} tBTA_AV_API_OPEN;

/* BTA_AV_API_STOP_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BOOLEAN             suspend;
    BOOLEAN             flush;
} tBTA_AV_API_STOP;

/* BTA_AV_API_DISCONNECT_VT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
} tBTA_AV_API_DISCNT;

/* BTA_AV_API_PROTECT_REQ_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT8               *p_data;
    UINT16              len;
} tBTA_AV_API_PROTECT_REQ;

/* BTA_AV_API_PROTECT_RSP_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT8               *p_data;
    UINT16              len;
    UINT8               error_code;
} tBTA_AV_API_PROTECT_RSP;

/* BTA_AV_API_REMOTE_CMD_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tAVRC_MSG_PASS      msg;
    UINT8               label;
} tBTA_AV_API_REMOTE_CMD;

/* BTA_AV_API_VENDOR_CMD_EVT和RSP的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tAVRC_MSG_VENDOR    msg;
    UINT8               label;
} tBTA_AV_API_VENDOR;

/* BTA_AV_API_RC_OPEN_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
} tBTA_AV_API_OPEN_RC;

/* BTA_AV_API_RC_CLOSE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
} tBTA_AV_API_CLOSE_RC;

/* BTA_AV_API_META_RSP_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BOOLEAN             is_rsp;
    UINT8               label;
    tBTA_AV_CODE        rsp_code;
    BT_HDR              *p_pkt;
} tBTA_AV_API_META_RSP;


/* BTA_AV_API_RECONFIG_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT8               codec_info[AVDT_CODEC_SIZE];    /* 编解码器配置*/
    UINT8               *p_protect_info;
    UINT8               num_protect;
    BOOLEAN             suspend;
    UINT8               sep_info_idx;
} tBTA_AV_API_RCFG;

/* BTA_AV_CI_SETCONFIG_OK_EVT和BTA_AV-CI_SETCONFIG _FAIL_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_AV_HNDL        hndl;
    UINT8               err_code;
    UINT8               category;
    UINT8               num_seid;
    UINT8               *p_seid;
    BOOLEAN             recfg_needed;
    UINT8               avdt_handle;  /* 将为其设置此流的本地sep类型*/
} tBTA_AV_CI_SETCONFIG;

/* AVDTP中所有流事件的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tAVDT_CFG           cfg;        /* 配置/功能参数*/
    tAVDT_CTRL          msg;        /* AVDTP回调消息参数*/
    BD_ADDR             bd_addr;    /* bd地址*/
    UINT8               handle;
    UINT8               avdt_event;
    BOOLEAN             initiator;  /* TRUE，如果本地设备启动SUSPEND*/
} tBTA_AV_STR_MSG;

/* BTA_AV_AVRC_MSG_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tAVRC_MSG           msg;
    UINT8               handle;
    UINT8               label;
    UINT8               opcode;
} tBTA_AV_RC_MSG;

/* BTA_AV_AVRC_OPEN_EVT、BTA_AV_AVRC_CLOSE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             peer_addr;
    UINT8               handle;
} tBTA_AV_RC_CONN_CHG;

/* BTA_AV_CONN_CHG_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             peer_addr;
    BOOLEAN             is_up;
} tBTA_AV_CONN_CHG;

/* BTA_AV_ROLE_CHANGE_VT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT8               new_role;
    UINT8               hci_status;
} tBTA_AV_ROLE_RES;

/* BTA_AV_SDP_DISC_OK_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT16              avdt_version;   /* AVDTP协议版本*/
} tBTA_AV_SDP_RES;

/* SEP控制块类型*/
typedef struct {
    UINT8               av_handle;         /* AVDTP手柄*/
    tBTA_AV_CODEC       codec_type;        /* 编解码器类型*/
    UINT8               tsep;              /* 本地SEP的SEP类型*/
    tBTA_AV_DATA_CBACK  *p_app_data_cback; /* 媒体数据包的应用程序回调*/
} tBTA_AV_SEP;


/* 适应的引发剂/受体作用*/
#define BTA_AV_ROLE_AD_INT          0x00       /* 引发剂，引发剂*/
#define BTA_AV_ROLE_AD_ACP          0x01       /* 承兑人*/

/* 引发剂/受体信号作用*/
#define BTA_AV_ROLE_START_ACP       0x00
#define BTA_AV_ROLE_START_INT       0x10    /* 不更改此值*/

#define BTA_AV_ROLE_SUSPEND         0x20    /* 启动时挂起*/
#define BTA_AV_ROLE_SUSPEND_OPT     0x40    /* 已设置“开始时挂起”选项*/

/* 所有事件数据类型的联合*/
typedef union {
    BT_HDR                  hdr;
    tBTA_AV_API_ENABLE      api_enable;
    tBTA_AV_API_REG         api_reg;
    tBTA_AV_API_OPEN        api_open;
    tBTA_AV_API_STOP        api_stop;
    tBTA_AV_API_DISCNT      api_discnt;
    tBTA_AV_API_PROTECT_REQ api_protect_req;
    tBTA_AV_API_PROTECT_RSP api_protect_rsp;
    tBTA_AV_API_REMOTE_CMD  api_remote_cmd;
    tBTA_AV_API_VENDOR      api_vendor;
    tBTA_AV_API_RCFG        api_reconfig;
    tBTA_AV_CI_SETCONFIG    ci_setconfig;
    tBTA_AV_STR_MSG         str_msg;
    tBTA_AV_RC_MSG          rc_msg;
    tBTA_AV_RC_CONN_CHG     rc_conn_chg;
    tBTA_AV_CONN_CHG        conn_chg;
    tBTA_AV_ROLE_RES        role_res;
    tBTA_AV_SDP_RES         sdp_res;
    tBTA_AV_API_META_RSP    api_meta_rsp;
} tBTA_AV_DATA;

typedef void (tBTA_AV_VDP_DATA_ACT)(void *p_scb);

typedef struct {
    tBTA_AV_VDP_DATA_ACT    *p_act;
    UINT8                   *p_frame;
    UINT16                  buf_size;
    UINT32                  len;
    UINT32                  offset;
    UINT32                  timestamp;
} tBTA_AV_VF_INFO;

typedef union {
    tBTA_AV_VF_INFO     vdp;            /* 仅用于视频频道*/
    tBTA_AV_API_OPEN    open;           /* 仅在打开之前使用，并且需要在另一个AV频道上切换角色*/
} tBTA_AV_Q_INFO;

#define BTA_AV_Q_TAG_OPEN               0x01 /* API_OPEN之后，STR_OPEND之前*/
#define BTA_AV_Q_TAG_START              0x02 /* 开始发送媒体数据包之前*/
#define BTA_AV_Q_TAG_STREAM             0x03 /* 在流式传输期间*/

#define BTA_AV_WAIT_ACP_CAPS_ON         0x01 /* 检索对等能力*/
#define BTA_AV_WAIT_ACP_CAPS_STARTED    0x02 /* 在检索对等功能时启动*/
#define BTA_AV_WAIT_ROLE_SW_RES_OPEN    0x04 /* 在API_OPEN之后、STR_OPENED之前等待角色切换结果*/
#define BTA_AV_WAIT_ROLE_SW_RES_START   0x08 /* 在流式传输之前等待角色切换结果*/
#define BTA_AV_WAIT_ROLE_SW_STARTED     0x10 /* 在等待角色切换结果时启动*/
#define BTA_AV_WAIT_ROLE_SW_RETRY       0x20 /* 超时重试时设置*/
#define BTA_AV_WAIT_CHECK_RC            0x40 /* 当角色开关使用计时器时设置*/
#define BTA_AV_WAIT_ROLE_SW_FAILED      0x80 /* 角色切换失败*/

#define BTA_AV_WAIT_ROLE_SW_BITS        (BTA_AV_WAIT_ROLE_SW_RES_OPEN|BTA_AV_WAIT_ROLE_SW_RES_START|BTA_AV_WAIT_ROLE_SW_STARTED|BTA_AV_WAIT_ROLE_SW_RETRY)

/* 冲突位图，coll_mask*/
#define BTA_AV_COLL_INC_TMR             0x01 /* 正在为传入L2C连接运行计时器*/
#define BTA_AV_COLL_API_CALLED          0x02 /* 传入计时器运行时调用了API open*/

/* AV流控制块类型*/
typedef struct {
    const tBTA_AV_ACT   *p_act_tbl;     /* 流状态机的动作表*/
    const tBTA_AV_CO_FUNCTS *p_cos;     /* 关联的callout函数*/
    tSDP_DISCOVERY_DB   *p_disc_db;     /* 指向发现数据库的指针*/
    tBTA_AV_SEP         seps[BTA_AV_MAX_SEPS];
    tAVDT_CFG           *p_cap;         /* 用于获取功能的缓冲区*/
    list_t              *a2d_list;      /* 仅用于音频频道*/
    tBTA_AV_Q_INFO      q_info;
    tAVDT_SEP_INFO      sep_info[BTA_AV_NUM_SEPS];      /* 流发现结果*/
    tAVDT_CFG           cfg;            /* 本地SEP配置*/
    TIMER_LIST_ENT      timer;          /* AVRC CT延时定时器*/
    BD_ADDR             peer_addr;      /* 对等BD地址*/
    UINT16              l2c_cid;        /* L2CAP通道ID*/
    UINT16              stream_mtu;     /* 流的MTU*/
    UINT16              avdt_version;   /* 对等设备的avdt版本*/
    tBTA_SEC            sec_mask;       /* 安全面罩*/
    tBTA_AV_CODEC       codec_type;     /* 编解码器类型*/
    UINT8               media_type;     /* 媒体类型*/
    BOOLEAN             cong;           /* 如果AVDTP拥塞，则为TRUE*/
    tBTA_AV_STATUS      open_status;    /* 打开故障状态*/
    tBTA_AV_CHNL        chnl;           /* 频道：音频/视频*/
    tBTA_AV_HNDL        hndl;           /* 句柄：（（hdi+1）|chnl）*/
    UINT16              cur_psc_mask;   /* 当前连接的协议服务功能掩码*/
    UINT8               avdt_handle;    /* AVDTP手柄*/
    UINT8               hdi;            /* SCB[]的索引*/
    UINT8               num_seps;       /* 流发现返回的sep数*/
    UINT8               num_disc_snks;  /* 发现的snk数*/
    UINT8               num_disc_srcs;  /* 发现的src数量*/
    UINT8               sep_info_idx;   /* 当前索引到sep_info*/
    UINT8               sep_idx;        /* 当前索引到本地seps[]*/
    UINT8               rcfg_idx;       /* 将请求的索引重新配置到sep_info中*/
    UINT8               state;          /* 状态机状态*/
    UINT8               avdt_label;     /* AVDTP标签*/
    UINT8               app_id;         /* 应用程序id*/
    UINT8               num_recfg;      /* 发送的重新配置数*/
    UINT8               role;
    UINT8               l2c_bufs;       /* 排队到L2CAP的缓冲区数*/
    UINT8               rc_handle;      /* 连接的AVRCP手柄*/
    BOOLEAN             use_rc;         /* 如果允许AVRCP，则为TRUE*/
    BOOLEAN             started;        /* 如果流已启动，则为TRUE*/
    UINT8               co_started;     /* 非零，如果流从调出透视图开始*/
    BOOLEAN             recfg_sup;      /* 如果第一次尝试重新配置流成功，则为TRUE；否则，如果命令失败，则为False*/
    BOOLEAN             suspend_sup;    /* 如果支持Suspend流，则为TRUE；如果Suspend命令失败，则为FALSE*/
    BOOLEAN             deregistring;   /* 如果正在注销，则为TRUE*/
    BOOLEAN             sco_suspend;    /* 如果为SCO自动发出SUSPEND，则为TRUE*/
    UINT8               coll_mask;      /* 用于检查传入和传出冲突的掩码*/
    tBTA_AV_API_OPEN    open_api;       /* 保存的OPEN api消息*/
    UINT8               wait;           /* 将Caps设置为ACP时设置0x1，启动时设置0x2*/
    UINT8               q_tag;          /* 标识关联的q_info联合成员*/
    BOOLEAN             no_rtp_hdr;     /* 如果未添加RTP标头，则为TRUE*/
    UINT8               disc_rsn;       /* 不满的原因*/
    UINT16              uuid_int;       /*要连接到的启动器的预期UUID*/
} tBTA_AV_SCB;

#define BTA_AV_RC_ROLE_MASK     0x10
#define BTA_AV_RC_ROLE_INT      0x00
#define BTA_AV_RC_ROLE_ACP      0x10

#define BTA_AV_RC_CONN_MASK     0x20

/* AV RCP控制块类型*/
/* 此控制块的索引是rc句柄*/
typedef struct {
    UINT8   status;
    UINT8   handle;
    UINT8   shdl;   /* 流句柄（hdi+1）*/
    UINT8   lidx;   /* （索引+1）至LCB*/
    tBTA_AV_FEAT        peer_features;  /* 对等要素遮罩*/
    UINT16              peer_ct_features;
    UINT16              peer_tg_features;
} tBTA_AV_RCB;
#define BTA_AV_NUM_RCB      (BTA_AV_NUM_STRS  + 2)

enum {
    BTA_AV_LCB_FREE,
    BTA_AV_LCB_FIND
};

/* AV ACL链路控制块的类型*/
typedef struct {
    BD_ADDR             addr;           /* 对等BD地址*/
    UINT8               conn_msk;       /* 连接流句柄的句柄掩码*/
    UINT8               lidx;           /* 索引+1*/
} tBTA_AV_LCB;

/* 流状态机操作函数的类型*/
typedef void (*tBTA_AV_SACT)(tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);


/* AV控制块类型*/
typedef struct {
    tBTA_AV_SCB         *p_scb[BTA_AV_NUM_STRS];    /* 流控制块*/
    tSDP_DISCOVERY_DB   *p_disc_db;     /* 指向发现数据库的指针*/
    tBTA_AV_CBACK       *p_cback;       /* 应用程序回调函数*/
    tBTA_AV_RCB         rcb[BTA_AV_NUM_RCB];  /* RCB控制块*/
    tBTA_AV_LCB         lcb[BTA_AV_NUM_LINKS + 1]; /* 链路控制块*/
    TIMER_LIST_ENT      sig_tmr;        /* 链接计时器*/
    TIMER_LIST_ENT      acp_sig_tmr;    /* 接收时监控信令的计时器*/
    UINT32              sdp_a2d_handle; /* 音频src的SDP记录句柄*/
#if (BTA_AV_SINK_INCLUDED == TRUE)
    UINT32              sdp_a2d_snk_handle; /* 音频snk的SDP记录句柄*/
#endif
    UINT32              sdp_vdp_handle; /* 视频src的SDP记录句柄*/
    tBTA_AV_FEAT        features;       /* 要素遮罩*/
    tBTA_SEC            sec_mask;       /* 安全面罩*/
    tBTA_AV_HNDL        handle;         /* SDP活动的句柄*/
    tBTA_AVRC_CO_FUNCTS *p_rc_cos;      /* AVRCP调出功能*/
    BOOLEAN             disabling;      /* 如果调用了禁用的api，则返回TRUE*/
    UINT8               disc;           /* 如果p_disc_db正在使用，则为（hdi+1）或（rc_handle|BTA_AV_CHNL_MSK）*/
    UINT8               state;          /* 状态机状态*/
    UINT8               conn_rc;        /* 连接RCP通道的处理掩码*/
    UINT8               conn_audio;     /* 连接音频通道的句柄掩码*/
    UINT8               conn_video;     /* 连接视频频道的句柄掩码*/
    UINT8               conn_lcb;       /* 已用LCB的索引掩码*/
    UINT8               audio_open_cnt; /* 连接的音频通道数*/
    UINT8               reg_audio;      /* 已注册音频通道的句柄掩码*/
    UINT8               reg_video;      /* 已注册视频频道的句柄掩码*/
    UINT8               rc_acp_handle;
    UINT8               rc_acp_idx;     /* （索引+1）至RCB*/
    UINT8               rs_idx;         /* （索引+1）至SCB，等待RS打开*/
    BOOLEAN             sco_occupied;   /* 如果正在使用SCO或正在调用，则为TRUE*/
    UINT8               audio_streams;  /* 流式音频通道的句柄掩码*/
    UINT8               video_streams;  /* 流式视频频道的处理掩码*/
} tBTA_AV_CB;

/* 用于处理SBC数据帧和编解码器功能的类型*/
typedef int (tBTA_AV_SBC_ACT)(void *p_src, void *p_dst,
                              UINT32 src_samples, UINT32 dst_samples,
                              UINT32 *p_ret);

/* AV上采样控制块类型*/
typedef struct {
    INT32               cur_pos;    /* 当前位置*/
    UINT32              src_sps;    /* 每秒采样数（源音频数据）*/
    UINT32              dst_sps;    /* 每秒采样数（转换的音频数据）*/
    tBTA_AV_SBC_ACT     *p_act;     /* 执行转换的动作函数*/
    UINT16              bits;       /* 每个pcm样本的位数*/
    UINT16              n_channels; /* 频道数（即单声道（1）、立体声（2）…）*/
    INT16               worker1;
    INT16               worker2;
    UINT8               div;
} tBTA_AV_SBC_UPS_CB;

/*****************************************************************************
**  全局数据
*****************************************************************************/
/* 控制块声明向上采样*/
#if BTA_DYNAMIC_MEMORY == TRUE
extern tBTA_AV_SBC_UPS_CB *bta_av_sbc_ups_cb_ptr;
#define bta_av_sbc_ups_cb (*bta_av_sbc_ups_cb_ptr)
#endif

/* 控制块声明*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_AV_CB bta_av_cb;
#else
extern tBTA_AV_CB *bta_av_cb_ptr;
#define bta_av_cb (*bta_av_cb_ptr)
#endif

/* 配置结构*/
extern tBTA_AV_CFG *p_bta_av_cfg;

extern const tBTA_AV_SACT bta_av_a2d_action[];
extern const tBTA_AV_SACT bta_av_vdp_action[];
extern tAVDT_CTRL_CBACK *const bta_av_dt_cback[];
extern void bta_av_stream_data_cback(UINT8 handle, BT_HDR *p_pkt, UINT32 time_stamp, UINT8 m_pt);

/*****************************************************************************
**  功能原型
*****************************************************************************/
/* 效用函数*/
extern tBTA_AV_SCB *bta_av_hndl_to_scb(UINT16 handle);
extern BOOLEAN bta_av_chk_start(tBTA_AV_SCB *p_scb);
extern void bta_av_restore_switch (void);
extern UINT16 bta_av_chk_mtu(tBTA_AV_SCB *p_scb, UINT16 mtu);
extern void bta_av_conn_cback(UINT8 handle, BD_ADDR bd_addr, UINT8 event, tAVDT_CTRL *p_data);
extern UINT8 bta_av_rc_create(tBTA_AV_CB *p_cb, UINT8 role, UINT8 shdl, UINT8 lidx);
extern void bta_av_stream_chg(tBTA_AV_SCB *p_scb, BOOLEAN started);
extern BOOLEAN bta_av_is_scb_opening (tBTA_AV_SCB *p_scb);
extern BOOLEAN bta_av_is_scb_incoming (tBTA_AV_SCB *p_scb);
extern void bta_av_set_scb_sst_init (tBTA_AV_SCB *p_scb);
extern BOOLEAN bta_av_is_scb_init (tBTA_AV_SCB *p_scb);
extern void bta_av_set_scb_sst_incoming (tBTA_AV_SCB *p_scb);
extern tBTA_AV_LCB *bta_av_find_lcb(BD_ADDR addr, UINT8 op);


/* 调试函数*/
extern char *bta_av_evt_code(UINT16 evt_code);
extern char *bta_av_action_code(UINT16 action_code);

/* 主要功能*/
extern void bta_av_api_deregister(tBTA_AV_DATA *p_data);
extern void bta_av_dup_audio_buf(tBTA_AV_SCB *p_scb, BT_HDR *p_buf);
extern void bta_av_sm_execute(tBTA_AV_CB *p_cb, UINT16 event, tBTA_AV_DATA *p_data);
extern void bta_av_ssm_execute(tBTA_AV_SCB *p_scb, UINT16 event, tBTA_AV_DATA *p_data);
extern BOOLEAN bta_av_hdl_event(BT_HDR *p_msg);
extern BOOLEAN bta_av_switch_if_needed(tBTA_AV_SCB *p_scb);
extern BOOLEAN bta_av_link_role_ok(tBTA_AV_SCB *p_scb, UINT8 bits);
extern BOOLEAN bta_av_is_rcfg_sst(tBTA_AV_SCB *p_scb);

/* nsm动作函数*/
extern void bta_av_api_disconnect(tBTA_AV_DATA *p_data);
extern void bta_av_sig_chg(tBTA_AV_DATA *p_data);
extern void bta_av_sig_timer(tBTA_AV_DATA *p_data);
extern void bta_av_rc_disc_done(tBTA_AV_DATA *p_data);
extern void bta_av_rc_closed(tBTA_AV_DATA *p_data);
extern void bta_av_rc_disc(UINT8 disc);
extern void bta_av_conn_chg(tBTA_AV_DATA *p_data);
extern void bta_av_dereg_comp(tBTA_AV_DATA *p_data);

/* sm作用函数*/
extern void bta_av_disable (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_opened (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_remote_cmd (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_vendor_cmd (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_vendor_rsp (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_msg (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_close (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_meta_rsp (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_free_rsp (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);
extern void bta_av_rc_free_msg (tBTA_AV_CB *p_cb, tBTA_AV_DATA *p_data);

extern tBTA_AV_RCB *bta_av_get_rcb_by_shdl(UINT8 shdl);
extern void bta_av_del_rc(tBTA_AV_RCB *p_rcb);

/* ssm动作函数*/
extern void bta_av_do_disc_a2d (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_cleanup (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_free_sdb (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_config_ind (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_disconnect_req (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_security_req (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_security_rsp (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_setconfig_rsp (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_str_opened (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_security_ind (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_security_cfm (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_do_close (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_connect_req (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_sdp_failed (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_disc_results (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_disc_res_as_acp (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_open_failed (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_getcap_results (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_setconfig_rej (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_discover_req (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_conn_failed (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_do_start (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_str_stopped (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_reconfig (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_data_path (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_start_ok (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_start_failed (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_str_closed (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_clr_cong (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_suspend_cfm (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rcfg_str_ok (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rcfg_failed (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rcfg_connect (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rcfg_discntd (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_suspend_cont (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rcfg_cfm (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rcfg_open (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_security_rej (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_open_rc (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_chk_2nd_start (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_save_caps (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rej_conn (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_rej_conn (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_set_use_rc (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_cco_close (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_switch_role (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_role_res (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_delay_co (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_open_at_inc (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_open_fail_sdp (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);

/* ssm操作函数-特定于vdp*/
extern void bta_av_do_disc_vdp (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_vdp_str_opened (tBTA_AV_SCB *p_scb, tBTA_AV_DATA *p_data);
extern void bta_av_reg_vdp (tAVDT_CS *p_cs, char *p_service_name, void *p_data);

#endif  ///BTA_AV_INCLUDED == TRUE

#endif /* BTA_AV_INT_H */

