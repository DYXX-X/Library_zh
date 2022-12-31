/******************************************************************************
 * 版权所有（c）2014 Android开源项目版权所有（c）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#include "bta/bta_sys.h"
#include "bta/bta_api.h"
#include "bta/bta_hf_client_api.h"
#include "bta_hf_client_at.h"

#if (BTA_HF_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/
#define HFP_VERSION_1_1         0x0101
#define HFP_VERSION_1_5         0x0105
#define HFP_VERSION_1_6         0x0106
#define HFP_VERSION_1_7         0x0107

/* RFCOMM MTU SIZE */
#define BTA_HF_CLIENT_MTU       256

/* 连接的配置文件角色*/
#define BTA_HF_CLIENT_ACP       0       /* 接受的连接*/
#define BTA_HF_CLIENT_INT       1       /* 启动连接*/

/* 发生冲突时等待重试的计时器*/
#ifndef BTA_HF_CLIENT_COLLISION_TIMER
#define BTA_HF_CLIENT_COLLISION_TIMER  2411
#endif

enum {
    /* 这些事件由状态机处理*/
    BTA_HF_CLIENT_API_REGISTER_EVT = BTA_SYS_EVT_START(BTA_ID_HS),
    BTA_HF_CLIENT_API_DEREGISTER_EVT,
    BTA_HF_CLIENT_API_OPEN_EVT,
    BTA_HF_CLIENT_API_CLOSE_EVT,
    BTA_HF_CLIENT_API_AUDIO_OPEN_EVT,
    BTA_HF_CLIENT_API_AUDIO_CLOSE_EVT,
    BTA_HF_CLIENT_RFC_OPEN_EVT,
    BTA_HF_CLIENT_RFC_CLOSE_EVT,
    BTA_HF_CLIENT_RFC_SRV_CLOSE_EVT,
    BTA_HF_CLIENT_RFC_DATA_EVT,
    BTA_HF_CLIENT_DISC_ACP_RES_EVT,
    BTA_HF_CLIENT_DISC_INT_RES_EVT,
    BTA_HF_CLIENT_DISC_OK_EVT,
    BTA_HF_CLIENT_DISC_FAIL_EVT,
    BTA_HF_CLIENT_SCO_OPEN_EVT,
    BTA_HF_CLIENT_SCO_CLOSE_EVT,
    BTA_HF_CLIENT_SEND_AT_CMD_EVT,
#if (BTM_SCO_HCI_INCLUDED == TRUE )
    BTA_HF_CLIENT_CI_SCO_DATA_EVT,
#endif /* (BTM_SCO_HCI_INCLUDED == TRUE ) */
    BTA_HF_CLIENT_MAX_EVT,

    /* 这些事件在状态机之外处理*/
    BTA_HF_CLIENT_API_ENABLE_EVT,
    BTA_HF_CLIENT_API_DISABLE_EVT
};

/*****************************************************************************
**  数据类型
*****************************************************************************/

/* BTA_HF_CLIENT_API_ENABLE_EVT的数据类型*/
typedef struct {
    BT_HDR                     hdr;
    tBTA_HF_CLIENT_CBACK      *p_cback;
} tBTA_HF_CLIENT_API_ENABLE;

/* BTA_HF_CLIENT_API_REGISTER_EVT的数据类型*/
typedef struct {
    BT_HDR                     hdr;
    tBTA_HF_CLIENT_CBACK      *p_cback;
    tBTA_SEC                   sec_mask;
    tBTA_HF_CLIENT_FEAT        features;
    char                       name[BTA_SERVICE_NAME_LEN + 1];
} tBTA_HF_CLIENT_API_REGISTER;

/* BTA_HF_CLIENT_API_OPEN_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    tBTA_SEC            sec_mask;
} tBTA_HF_CLIENT_API_OPEN;

/* BTA_HF_CLIENT_DISC_RESULT_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    UINT16          status;
} tBTA_HF_CLIENT_DISC_RESULT;

/* RFCOMM事件的数据类型*/
typedef struct {
    BT_HDR          hdr;
    UINT16          port_handle;
} tBTA_HF_CLIENT_RFC;

/* 其他事件的通用数据类型*/
typedef struct {
    BT_HDR          hdr;
    BOOLEAN         bool_val;
    UINT8           uint8_val;
    UINT32          uint32_val1;
    UINT32          uint32_val2;
    char            str[BTA_HF_CLIENT_NUMBER_LEN + 1];
} tBTA_HF_CLIENT_DATA_VAL;

/* 所有事件数据类型的联合*/
typedef union {
    BT_HDR                         hdr;
    tBTA_HF_CLIENT_API_ENABLE      api_enable;
    tBTA_HF_CLIENT_API_REGISTER    api_register;
    tBTA_HF_CLIENT_API_OPEN        api_open;
    tBTA_HF_CLIENT_DISC_RESULT     disc_result;
    tBTA_HF_CLIENT_RFC             rfc;
    tBTA_HF_CLIENT_DATA_VAL        val;

} tBTA_HF_CLIENT_DATA;

/* 每个服务控制块的类型*/
typedef struct {
    UINT16              serv_handle;    /* RFCOMM服务器句柄*/
    BD_ADDR             peer_addr;      /* 对等bd地址*/
    tSDP_DISCOVERY_DB   *p_disc_db;     /* 指向发现数据库的指针*/
    UINT16              conn_handle;    /* 连接服务的RFCOMM句柄*/
    tBTA_SEC            serv_sec_mask;  /* 服务器安全掩码*/
    tBTA_SEC            cli_sec_mask;   /* 客户端安全掩码*/
    tBTA_HF_CLIENT_FEAT        features;       /* 应用程序注册的功能*/
    tBTA_HF_CLIENT_PEER_FEAT   peer_features;  /* 对等设备功能*/
    tBTA_HF_CLIENT_CHLD_FEAT   chld_features;  /* 呼叫处理功能*/
    UINT16              peer_version;   /* 对等设备的配置文件版本*/
    UINT8               peer_scn;       /* 对等scn*/
    UINT8               role;           /* 引发剂/受体角色*/
    UINT16              sco_idx;        /* SCO手柄*/
    UINT8               sco_state;      /* SCO状态变量*/
    BOOLEAN             sco_close_rfc;   /* 如果在SCO之后也关闭RFCOMM，则为TRUE*/
    BOOLEAN             retry_with_sco_only;
    BOOLEAN             deregister;     /* 如果服务关闭，则为TRUE*/
    BOOLEAN             svc_conn;       /* 服务级别连接启动时设置为TRUE*/
    BOOLEAN             send_at_reply;  /* 设置为TRUE以向框架通知AT结果*/
    tBTA_HF_CLIENT_AT_CB at_cb;         /* AT解析器控制块*/
    UINT8               state;          /* 状态机状态*/
    tBTM_SCO_CODEC_TYPE negotiated_codec; /* 协商编解码器*/
    TIMER_LIST_ENT      colli_timer;    /* 碰撞计时器*/
    BOOLEAN             colli_tmr_on;   /* 如果碰撞计时器处于活动状态，则为TRUE*/

    UINT16              in_pkt_len;
    UINT16              out_pkt_len;
    UINT8               link_type;      /* BTM_LINK_TYPE_SCO或BTM_LINK_TYPE_ESCO*/
    UINT8               tx_interval;
    UINT8               retrans_window;
    UINT8               air_mode;
} tBTA_HF_CLIENT_SCB;

/* 上合组织成员国*/
enum {
    BTA_HF_CLIENT_SCO_SHUTDOWN_ST,  /* 没有倾听，没有连接*/
    BTA_HF_CLIENT_SCO_LISTEN_ST,    /* 听*/
    BTA_HF_CLIENT_SCO_OPENING_ST,   /* 连接开口*/
    BTA_HF_CLIENT_SCO_OPEN_CL_ST,   /* 打开连接关闭*/
    BTA_HF_CLIENT_SCO_OPEN_ST,      /* 打开*/
    BTA_HF_CLIENT_SCO_CLOSING_ST,   /* 关闭*/
    BTA_HF_CLIENT_SCO_CLOSE_OP_ST,  /* 关闭打开的sco*/
    BTA_HF_CLIENT_SCO_SHUTTING_ST   /* sco关闭*/
};

/* AG控制块类型*/
typedef struct {
    tBTA_HF_CLIENT_SCB         scb;             /* 服务控制块*/
    UINT32                     sdp_handle;
    UINT8                      scn;
    tBTA_HF_CLIENT_CBACK       *p_cback;        /* 应用程序回调*/
    BOOLEAN                    msbc_enabled;
} tBTA_HF_CLIENT_CB;

/*****************************************************************************
**  全局数据
*****************************************************************************/

/* 控制块声明*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_HF_CLIENT_CB bta_hf_client_cb;
#else
extern tBTA_HF_CLIENT_CB *bta_hf_client_cb_ptr;
#define bta_hf_client_cb (*bta_hf_client_cb_ptr)
#endif

/*****************************************************************************
**  功能原型
*****************************************************************************/

/* 主要功能*/
extern void bta_hf_client_scb_init(void);
extern void bta_hf_client_scb_disable(void);
extern BOOLEAN bta_hf_client_hdl_event(BT_HDR *p_msg);
extern void bta_hf_client_sm_execute(UINT16 event,
                                     tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_slc_seq(BOOLEAN error);
extern void bta_hf_client_collision_cback (tBTA_SYS_CONN_STATUS status, UINT8 id,
        UINT8 app_id, BD_ADDR peer_addr);
extern void bta_hf_client_resume_open (void);

/* SDP功能*/
extern BOOLEAN bta_hf_client_add_record(char *p_service_name,
                                        UINT8 scn, tBTA_HF_CLIENT_FEAT features,
                                        UINT32 sdp_handle);
extern void bta_hf_client_create_record(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_del_record(tBTA_HF_CLIENT_DATA *p_data);
extern BOOLEAN bta_hf_client_sdp_find_attr(void);
extern void bta_hf_client_do_disc(void);
extern void bta_hf_client_free_db(tBTA_HF_CLIENT_DATA *p_data);

/* RFCOMM函数*/
extern void bta_hf_client_setup_port(UINT16 handle);
extern void bta_hf_client_start_server(void);
extern void bta_hf_client_close_server(void);
extern void bta_hf_client_rfc_do_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_rfc_do_close(tBTA_HF_CLIENT_DATA *p_data);

/* SCO功能*/
extern void bta_hf_client_sco_listen(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_sco_shutdown(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_sco_conn_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_sco_conn_close(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_sco_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_sco_close(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_cback_sco(UINT8 event);

/* AT命令功能*/
extern void bta_hf_client_at_parse(char *buf, unsigned int len);
extern void bta_hf_client_send_at_brsf(void);
extern void bta_hf_client_send_at_bac(void);
extern void bta_hf_client_send_at_cind(BOOLEAN status);
extern void bta_hf_client_send_at_cmer(BOOLEAN activate);
extern void bta_hf_client_send_at_chld(char cmd, UINT32 idx);
extern void bta_hf_client_send_at_clip(BOOLEAN activate);
extern void bta_hf_client_send_at_ccwa(BOOLEAN activate);
extern void bta_hf_client_send_at_cmee(BOOLEAN activate);
extern void bta_hf_client_send_at_cops(BOOLEAN query);
extern void bta_hf_client_send_at_clcc(void);
extern void bta_hf_client_send_at_bvra(BOOLEAN enable);
extern void bta_hf_client_send_at_vgs(UINT32 volume);
extern void bta_hf_client_send_at_vgm(UINT32 volume);
extern void bta_hf_client_send_at_atd(char *number, UINT32 memory);
extern void bta_hf_client_send_at_bldn(void);
extern void bta_hf_client_send_at_ata(void);
extern void bta_hf_client_send_at_chup(void);
extern void bta_hf_client_send_at_btrh(BOOLEAN query, UINT32 val);
extern void bta_hf_client_send_at_vts(char code);
extern void bta_hf_client_send_at_bcc(void);
extern void bta_hf_client_send_at_bcs(UINT32 codec);
extern void bta_hf_client_send_at_cnum(void);
extern void bta_hf_client_send_at_nrec(void);
extern void bta_hf_client_send_at_binp(UINT32 action);
extern void bta_hf_client_send_at_bia(void);

/* 动作功能*/
extern void bta_hf_client_register(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_deregister(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_start_dereg(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_start_close(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_start_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_rfc_acp_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_rfc_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_rfc_fail(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_disc_fail(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_open_fail(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_rfc_close(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_disc_acp_res(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_rfc_data(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_disc_int_res(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_svc_conn_open(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_ind(tBTA_HF_CLIENT_IND_TYPE type, UINT16 value);
extern void bta_hf_client_evt_val(tBTA_HF_CLIENT_EVT type, UINT16 value);
extern void bta_hf_client_operator_name(char *name);
extern void bta_hf_client_clip(char *number);
extern void bta_hf_client_ccwa(char *number);
extern void bta_hf_client_at_result(tBTA_HF_CLIENT_AT_RESULT_TYPE type, UINT16 cme);
extern void bta_hf_client_clcc(UINT32 idx, BOOLEAN incoming, UINT8 status, BOOLEAN mpty, char *number);
extern void bta_hf_client_cnum(char *number, UINT16 service);
extern void bta_hf_client_binp(char *number);

/* 命令处理功能*/
extern void bta_hf_client_dial(tBTA_HF_CLIENT_DATA *p_data);
extern void bta_hf_client_send_at_cmd(tBTA_HF_CLIENT_DATA *p_data);
#if (BTM_SCO_HCI_INCLUDED == TRUE )
extern void bta_hf_client_ci_sco_data(tBTA_HF_CLIENT_DATA *p_data);
#endif /* (BTM_SCO_HCI_INCLUDED == TRUE ) */
#endif /* #如果（BTA_HF_INCLUDE==真）*/

