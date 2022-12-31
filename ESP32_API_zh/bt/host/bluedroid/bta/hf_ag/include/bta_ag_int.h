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
 * 这是BTA音频网关的专用接口文件。
 *
 ******************************************************************************/
#ifndef BTA_AG_INT_H
#define BTA_AG_INT_H

#include "bta_ag_at.h"
#include "bta/bta_sys.h"
#include "bta/bta_api.h"
#include "bta/bta_ag_api.h"
#include "stack/sdp_api.h"

#if (BTA_AG_INCLUDED == TRUE)

/* 在一个AT命令中发送RING&CLIP*/
#ifndef BTA_AG_MULTI_RESULT_INCLUDED
#define BTA_AG_MULTI_RESULT_INCLUDED      FALSE
#endif

/* 更换：用于HSP的VGS和VGM*/
#ifndef BTA_HSP_RESULT_REPLACE_COLON
#define BTA_HSP_RESULT_REPLACE_COLON      TRUE
#endif

/*****************************************************************************
**  常量
*****************************************************************************/
#define HFP_VERSION_1_1         0x0101
#define HFP_VERSION_1_5         0x0105
#define HFP_VERSION_1_6         0x0106

#define HSP_VERSION_1_0         0x0100
#define HSP_VERSION_1_2         0x0102

/* SCB的数量（可以注册的AG服务实例）*/
#ifndef BTA_AG_NUM_SCB
#define BTA_AG_NUM_SCB          1
#endif

/* 发生冲突时等待重试的计时器*/
#ifndef BTA_AG_COLLISION_TIMER
#define BTA_AG_COLLISION_TIMER  2000
#endif

/* RFCOMM MTU SIZE */
#define BTA_AG_MTU              256

/* 内部配置文件索引*/
#define BTA_AG_HSP              0       /* HSP索引*/
#define BTA_AG_HFP              1       /* HFP指数*/
#define BTA_AG_NUM_IDX          2       /* 配置文件索引数*/

/* 连接的配置文件角色*/
#define BTA_AG_ACP              0       /* 接受的连接*/
#define BTA_AG_INT              1       /* 启动连接*/

/* 与等级库匹配的要素遮罩*/
#define BTA_AG_BSRF_FEAT_SPEC        (BTA_AG_FEAT_3WAY | BTA_AG_FEAT_ECNR    | \
                                      BTA_AG_FEAT_VREC | BTA_AG_FEAT_INBAND  | \
                                      BTA_AG_FEAT_VTAG | BTA_AG_FEAT_REJECT  | \
                                      BTA_AG_FEAT_ECS  | BTA_AG_FEAT_ECC     | \
                                      BTA_AG_FEAT_EXTERR | BTA_AG_FEAT_CODEC | \
                                      BTA_AG_FEAT_VOIP)

#define BTA_AG_SDP_FEAT_SPEC         (BTA_AG_FEAT_3WAY | BTA_AG_FEAT_ECNR    | \
                                      BTA_AG_FEAT_VREC | BTA_AG_FEAT_INBAND  | \
                                      BTA_AG_FEAT_VTAG)

enum
{
    /* 这些事件由状态机处理*/
    BTA_AG_API_REGISTER_EVT = BTA_SYS_EVT_START(BTA_ID_AG),
    BTA_AG_API_DEREGISTER_EVT,
    BTA_AG_API_OPEN_EVT,
    BTA_AG_API_CLOSE_EVT,
    BTA_AG_API_AUDIO_OPEN_EVT,
    BTA_AG_API_AUDIO_CLOSE_EVT,
    BTA_AG_API_RESULT_EVT,
    BTA_AG_API_SETCODEC_EVT,
    BTA_AG_RFC_OPEN_EVT,
    BTA_AG_RFC_CLOSE_EVT,
    BTA_AG_RFC_SRV_CLOSE_EVT,
    BTA_AG_RFC_DATA_EVT,
    BTA_AG_SCO_OPEN_EVT,
    BTA_AG_SCO_CLOSE_EVT,
    BTA_AG_DISC_ACP_RES_EVT,
    BTA_AG_DISC_INT_RES_EVT,
    BTA_AG_DISC_OK_EVT,
    BTA_AG_DISC_FAIL_EVT,
    BTA_AG_CI_RX_WRITE_EVT,
    BTA_AG_RING_TOUT_EVT,
    BTA_AG_SVC_TOUT_EVT,
    BTA_AG_CI_SCO_DATA_EVT,
    BTA_AG_CI_SLC_READY_EVT,
    BTA_AG_MAX_EVT,

    /* 这些事件在状态机之外处理*/
    BTA_AG_API_ENABLE_EVT,
    BTA_AG_API_DISABLE_EVT
};

/* 上合组织事件后应采取的行动*/
enum
{
    BTA_AG_POST_SCO_NONE,       /* 不采取行动*/
    BTA_AG_POST_SCO_CLOSE_RFC,  /* SCO关闭后关闭RFCOMM通道*/
    BTA_AG_POST_SCO_RING,       /* SCO打开后发送RING结果代码*/
    BTA_AG_POST_SCO_CALL_CONN,  /* SCO打开/关闭后发送呼叫指示器*/
    BTA_AG_POST_SCO_CALL_ORIG,  /* SCO关闭后发送呼叫指示器*/
    BTA_AG_POST_SCO_CALL_END,   /* SCO关闭后发送呼叫指示器*/
    BTA_AG_POST_SCO_CALL_END_INCALL   /* 在SCO关闭后发送结束呼叫和传入呼叫的呼叫指示器*/
};

/* 上合组织成员国*/
enum
{
    BTA_AG_SCO_SHUTDOWN_ST,     /* 没有sco监听，所有sco连接关闭*/
    BTA_AG_SCO_LISTEN_ST,       /* sco监听*/
#if (BTM_WBS_INCLUDED == TRUE)
    BTA_AG_SCO_CODEC_ST,        /* sco编解码器协商*/
#endif
    BTA_AG_SCO_OPENING_ST,      /* sco连接开口*/
    BTA_AG_SCO_OPEN_CL_ST,      /* 打开关闭的sco连接*/
    BTA_AG_SCO_OPEN_XFER_ST,    /* 打开正在传输的sco连接*/
    BTA_AG_SCO_OPEN_ST,         /* sco打开*/
    BTA_AG_SCO_CLOSING_ST,      /* sco关闭*/
    BTA_AG_SCO_CLOSE_OP_ST,     /* 关闭打开的sco*/
    BTA_AG_SCO_CLOSE_XFER_ST,   /* 关闭正在转移的sco*/
    BTA_AG_SCO_SHUTTING_ST      /* sco关闭*/
};

/*****************************************************************************
**  数据类型
*****************************************************************************/

/* BTA_AG_API_ENABLE_EVT的数据类型*/
typedef struct
{
    BT_HDR              hdr;
    tBTA_AG_PARSE_MODE  parse_mode;
    tBTA_AG_CBACK      *p_cback;
} tBTA_AG_API_ENABLE;

/* BTA_AG_API_REGISTER_EVT的数据类型*/
typedef struct
{
    BT_HDR              hdr;
    char                p_name[2][BTA_SERVICE_NAME_LEN+1];
    tBTA_SERVICE_MASK   services;
    tBTA_SEC            sec_mask;
    tBTA_AG_FEAT        features;
    UINT8               app_id;
} tBTA_AG_API_REGISTER;

/* BTA_AG_API_OPEN_EVT的数据类型*/
typedef struct
{
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    tBTA_SERVICE_MASK   services;
    tBTA_SEC            sec_mask;
} tBTA_AG_API_OPEN;

/* BTA_AG_API_RESULT_EVT的数据类型*/
typedef struct
{
    BT_HDR            hdr;
    tBTA_AG_RES       result;
    tBTA_AG_RES_DATA  data;
} tBTA_AG_API_RESULT;

/* BTA_AG_API_SETCODEC_EVT的数据类型*/
typedef struct
{
    BT_HDR              hdr;
    tBTA_AG_PEER_CODEC  codec;
} tBTA_AG_API_SETCODEC;

/* BTA_AG_DISC_RESULT_EVT的数据类型*/
typedef struct
{
    BT_HDR          hdr;
    UINT16          status;
} tBTA_AG_DISC_RESULT;

/* RFCOMM事件的数据类型*/
typedef struct
{
    BT_HDR          hdr;
    UINT16          port_handle;
} tBTA_AG_RFC;

/* BTA_AG_CI_RX_WRITE_EVT的数据类型*/
typedef struct
{
    BT_HDR          hdr;
    char            p_data[BTA_AG_MTU+1];
} tBTA_AG_CI_RX_WRITE;

/* 所有事件数据类型的联合*/
typedef union
{
    BT_HDR                  hdr;
    tBTA_AG_API_ENABLE      api_enable;
    tBTA_AG_API_REGISTER    api_register;
    tBTA_AG_API_OPEN        api_open;
    tBTA_AG_API_RESULT      api_result;
#if (BTM_WBS_INCLUDED == TRUE)
    tBTA_AG_API_SETCODEC    api_setcodec;
#endif
    tBTA_AG_DISC_RESULT     disc_result;
    tBTA_AG_RFC             rfc;
    tBTA_AG_CI_RX_WRITE     ci_rx_write;
} tBTA_AG_DATA;

/* 每个配置文件的类型*/
typedef struct
{
    UINT32          sdp_handle;
    UINT8           scn;
} tBTA_AG_PROFILE;

#if (BTM_WBS_INCLUDED == TRUE)
typedef enum
{
    BTA_AG_SCO_MSBC_SETTINGS_T2 = 0, /* 当编解码器为mSBC时，首选/默认*/
    BTA_AG_SCO_MSBC_SETTINGS_T1,
} tBTA_AG_SCO_MSBC_SETTINGS;
#endif

/* 每个服务控制块的类型*/
typedef struct
{
    char                clip[BTA_AG_AT_MAX_LEN+10]; /* 用于CLIP的数字字符串*/
    UINT16              serv_handle[BTA_AG_NUM_IDX]; /* RFCOMM服务器句柄*/
    tBTA_AG_AT_CB       at_cb;          /* AT命令解释器*/
    TIMER_LIST_ENT      act_timer;     /* 环形计时器*/
    BD_ADDR             peer_addr;      /* 对等bd地址*/
    tSDP_DISCOVERY_DB   *p_disc_db;     /* 指向发现数据库的指针*/
    tBTA_SERVICE_MASK   reg_services;   /* 注册API中指定的服务*/
    tBTA_SERVICE_MASK   open_services;  /* 开放API中指定的服务*/
    UINT16              conn_handle;    /* 连接服务的RFCOMM句柄*/
    tBTA_SEC            serv_sec_mask;  /* 服务器安全掩码*/
    tBTA_SEC            cli_sec_mask;   /* 客户端安全掩码*/
    tBTA_AG_FEAT        features;       /* 应用程序注册的功能*/
    tBTA_AG_PEER_FEAT   peer_features;  /* 对等设备功能*/
    UINT16              peer_version;   /* 对等设备的配置文件版本*/
    UINT16              hsp_version;    /* HSP配置文件版本*/
#if (BTM_WBS_INCLUDED == TRUE)
    tBTA_AG_PEER_CODEC  peer_codecs;    /* 对等方支持的eSCO编解码器*/
    tBTA_AG_PEER_CODEC  sco_codec;      /* 用于eSCO连接的编解码器*/
    tBTA_AG_PEER_CODEC  inuse_codec;    /* 用于当前SCO连接的编解码器*/
    BOOLEAN             codec_updated;  /* 每当应用程序更新编解码器类型时，设置为TRUE*/
    BOOLEAN             codec_fallback; /* 如果sco-nego在mSBC失败，则回退到CVSD*/
    tBTA_AG_SCO_MSBC_SETTINGS codec_msbc_settings; /* 用于即将到来的eSCO的设置*/
    TIMER_LIST_ENT      cn_timer;       /* 编解码器协商计时器*/
#endif
    UINT16              sco_idx;        /* SCO手柄*/
    BOOLEAN             in_use;         /* 使用中的scb*/
    BOOLEAN             dealloc;        /* 如果服务关闭，则为TRUE*/
    BOOLEAN             clip_enabled;   /* 如果HF启用CLIP报告，则设置为TRUE*/
    BOOLEAN             ccwa_enabled;   /* 如果HF启用CCWA报告，则设置为TRUE*/
    BOOLEAN             cmer_enabled;   /* 如果HF启用CMER报告，则设置为TRUE*/
    BOOLEAN             cmee_enabled;   /* 如果HF启用CME错误报告，则设置为TRUE*/
    BOOLEAN             inband_enabled; /* 如果启用带内振铃，则设置为TRUE*/
    BOOLEAN             svc_conn;       /* 服务级别连接启动时设置为TRUE*/
    TIMER_LIST_ENT      colli_timer;    /* 碰撞计时器*/
    BOOLEAN             colli_tmr_on;   /* 如果碰撞计时器处于活动状态，则为TRUE*/
    UINT8               state;          /* 状态机状态*/
    UINT8               conn_service;   /* 已连接服务*/
    UINT8               peer_scn;       /* 对等scn*/
    UINT8               app_id;         /* 应用程序id*/
    UINT8               role;           /* 引发剂/受体角色*/
    tBTM_SCO_CODEC_TYPE negotiated_codec; /* 协商编解码器*/
    UINT8               post_sco;       /* sco事件后要执行的操作*/
    UINT8               call_ind;       /* CIEV呼叫指示器值*/
    UINT8               callsetup_ind;  /* CIEV呼叫设置指示器值*/
    UINT8               service_ind;    /* CIEV服务指标值*/
    UINT8               signal_ind;     /* CIEV信号指示值*/
    UINT8               roam_ind;       /* CIEV漫游指示器值*/
    UINT8               battchg_ind;    /* CIEV电池充电指示值*/
    UINT8               callheld_ind;   /* CIEV呼叫保持指示值*/
    BOOLEAN             retry_with_sco_only; /* 仅当eSCO失败时尝试使用SCO的指示器*/
    UINT32              bia_masked_out; /* HF不希望我们发送的指示器*/
    /* 添加*/
    UINT16              in_pkt_len;
    UINT16              out_pkt_len;
    UINT8               link_type;      /* BTM_LINK_TYPE_SCO或BTM_LINK_TYPE_ESCO*/
    UINT8               tx_interval;
    UINT8               retrans_window;
    UINT8               air_mode;
} tBTA_AG_SCB;

/* sco数据的类型*/
typedef struct
{
    tBTM_ESCO_CONN_REQ_EVT_DATA  conn_data;     /* 待定连接请求的CO数据*/
    tBTA_AG_SCB                 *p_curr_scb;    /* 与SCO连接相关的SCB*/
    tBTA_AG_SCB                 *p_xfer_scb;    /* 与SCO传输相关的SCB*/
    UINT16                      cur_idx;        /* SCO手柄*/
    UINT8                       state;          /* SCO状态变量*/
    BOOLEAN                     param_updated;  /* 如果参数更新为非默认值*/
    tBTM_ESCO_PARAMS            params;         /* ESCO参数*/
    tBTA_AG_DATA                *p_data;
} tBTA_AG_SCO_CB;

/* AG控制块类型*/
typedef struct
{
    tBTA_AG_SCB         scb[BTA_AG_NUM_SCB];        /* 服务控制块*/
    tBTA_AG_PROFILE     profile[BTA_AG_NUM_IDX];    /* 配置文件特定数据*/
    tBTA_AG_SCO_CB      sco;                        /* SCO数据*/
    tBTA_AG_CBACK       *p_cback;                   /* 应用程序回调*/
    tBTA_AG_PARSE_MODE  parse_mode;                 /* 解析/传递模式*/
    BOOLEAN             msbc_enabled;
} tBTA_AG_CB;

/*****************************************************************************
**  全局数据
*****************************************************************************/

/* 常量查找表*/
extern const UINT16 bta_ag_uuid[BTA_AG_NUM_IDX];
extern const UINT8 bta_ag_sec_id[BTA_AG_NUM_IDX];
extern const tBTA_AG_AT_CMD *bta_ag_at_tbl[BTA_AG_NUM_IDX];

/* 控制块声明*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_AG_CB bta_ag_cb;
#else
extern tBTA_AG_CB *bta_ag_cb_ptr;
#define bta_ag_cb (*bta_ag_cb_ptr)
#endif

/* 配置结构*/
extern tBTA_AG_CFG *p_bta_ag_cfg;

/*****************************************************************************
**  功能原型
*****************************************************************************/

/* 主要功能*/
extern void bta_ag_scb_dealloc(tBTA_AG_SCB *p_scb);
extern UINT16 bta_ag_scb_to_idx(tBTA_AG_SCB *p_scb);
extern tBTA_AG_SCB *bta_ag_scb_by_idx(UINT16 idx);
extern UINT8 bta_ag_service_to_idx(tBTA_SERVICE_MASK services);
extern UINT16 bta_ag_idx_by_bdaddr(BD_ADDR peer_addr);
extern BOOLEAN bta_ag_other_scb_open(tBTA_AG_SCB *p_curr_scb);
extern BOOLEAN bta_ag_scb_open(tBTA_AG_SCB *p_curr_scb);
extern tBTA_AG_SCB *bta_ag_get_other_idle_scb (tBTA_AG_SCB *p_curr_scb);
extern void bta_ag_sm_execute(tBTA_AG_SCB *p_scb, UINT16 event, tBTA_AG_DATA *p_data);
extern BOOLEAN bta_ag_hdl_event(BT_HDR *p_msg);
extern void bta_ag_collision_cback(tBTA_SYS_CONN_STATUS status, UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_ag_resume_open(tBTA_AG_SCB *p_scb);

/* SDP功能*/
extern BOOLEAN bta_ag_add_record(UINT16 service_uuid, char *p_service_name, UINT8 scn, tBTA_AG_FEAT features, UINT32 sdp_handle);
extern void bta_ag_create_records(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_del_records(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern BOOLEAN bta_ag_sdp_find_attr(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK service);
extern void bta_ag_do_disc(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK service);
extern void bta_ag_free_db(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);

/* RFCOMM函数*/
extern void bta_ag_start_servers(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK services);
extern void bta_ag_close_servers(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK services);
extern BOOLEAN bta_ag_is_server_closed (tBTA_AG_SCB *p_scb);
extern void bta_ag_rfc_do_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rfc_do_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);

/* SCO功能*/
extern BOOLEAN bta_ag_sco_is_open(tBTA_AG_SCB *p_scb);
extern BOOLEAN bta_ag_sco_is_opening(tBTA_AG_SCB *p_scb);
extern void bta_ag_sco_conn_rsp(tBTA_AG_SCB *p_scb, tBTM_ESCO_CONN_REQ_EVT_DATA *p_data);

/* AT命令功能*/
extern void bta_ag_at_hsp_cback(tBTA_AG_SCB *p_scb, UINT16 cmd, UINT8 arg_type, char *p_arg, INT16 int_arg);
extern void bta_ag_at_hfp_cback(tBTA_AG_SCB *p_scb, UINT16 cmd, UINT8 arg_type, char *p_arg, INT16 int_arg);
extern void bta_ag_at_err_cback(tBTA_AG_SCB *p_scb, BOOLEAN unknown, char *p_arg);
extern BOOLEAN bta_ag_inband_enabled(tBTA_AG_SCB *p_scb);
extern void bta_ag_send_call_inds(tBTA_AG_SCB *p_scb, tBTA_AG_RES result);

/* 动作功能*/
extern void bta_ag_register(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_deregister(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_start_dereg(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_start_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_start_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_disc_int_res(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_disc_acp_res(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_disc_fail(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_open_fail(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rfc_fail(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rfc_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rfc_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rfc_acp_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rfc_data(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_sco_listen(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_sco_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_sco_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
#if (BTM_WBS_INCLUDED == TRUE)
extern void bta_ag_sco_codec_nego(tBTA_AG_SCB *p_scb, BOOLEAN result);
extern void bta_ag_codec_negotiate (tBTA_AG_SCB *p_scb);
extern void bta_ag_send_bcs(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
#endif
extern void bta_ag_sco_shutdown(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_sco_conn_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_sco_conn_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_post_sco_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_post_sco_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_svc_conn_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_result(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_setcodec(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_send_ring(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_ci_sco_data(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_set_esco_param(BOOLEAN set_reset, tBTM_ESCO_PARAMS *param);
extern void bta_ag_ci_rx_data(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);
extern void bta_ag_rcvd_slc_ready(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data);

#endif /* #如果（BTA_AG_INCLUDE==真）*/

#endif /* BTA_AG_INT_H */

