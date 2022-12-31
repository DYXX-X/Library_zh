/******************************************************************************
 * 版权所有（C）2006-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA Java I/F的专用接口文件
 *
 ******************************************************************************/
#ifndef BTA_JV_INT_H
#define BTA_JV_INT_H

#include "bta/bta_sys.h"
#include "bta/bta_api.h"
#include "bta/bta_jv_api.h"
#include "stack/rfcdefs.h"
#include "stack/port_api.h"
#include "stack/sdp_api.h"

#include "common/bt_target.h"
#if (defined BTA_JV_INCLUDED && BTA_JV_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

#define SPP_VERSION             0x0102

enum {
    /* 这些事件由状态机处理*/
    BTA_JV_API_ENABLE_EVT = BTA_SYS_EVT_START(BTA_ID_JV),
    BTA_JV_API_DISABLE_EVT,
    BTA_JV_API_GET_CHANNEL_EVT,
    BTA_JV_API_FREE_SCN_EVT,
    BTA_JV_API_START_DISCOVERY_EVT,
    BTA_JV_API_CREATE_RECORD_EVT,
    BTA_JV_API_DELETE_RECORD_EVT,
#if BTA_JV_L2CAP_INCLUDED
    BTA_JV_API_L2CAP_CONNECT_EVT,
    BTA_JV_API_L2CAP_CLOSE_EVT,
    BTA_JV_API_L2CAP_START_SERVER_EVT,
    BTA_JV_API_L2CAP_STOP_SERVER_EVT,
    BTA_JV_API_L2CAP_READ_EVT,
    BTA_JV_API_L2CAP_WRITE_EVT,
#endif /* BTA_JV_L2CAP_INCLUDED */
    BTA_JV_API_RFCOMM_CONNECT_EVT,
    BTA_JV_API_RFCOMM_CLOSE_EVT,
    BTA_JV_API_RFCOMM_START_SERVER_EVT,
    BTA_JV_API_RFCOMM_STOP_SERVER_EVT,
    BTA_JV_API_RFCOMM_READ_EVT,
    BTA_JV_API_RFCOMM_WRITE_EVT,
    BTA_JV_API_RFCOMM_FLOW_CONTROL_EVT,
    BTA_JV_API_SET_PM_PROFILE_EVT,
    BTA_JV_API_PM_STATE_CHANGE_EVT,
#if BTA_JV_L2CAP_INCLUDED
    BTA_JV_API_L2CAP_CONNECT_LE_EVT,
    BTA_JV_API_L2CAP_START_SERVER_LE_EVT,
    BTA_JV_API_L2CAP_STOP_SERVER_LE_EVT,
    BTA_JV_API_L2CAP_WRITE_FIXED_EVT,
    BTA_JV_API_L2CAP_CLOSE_FIXED_EVT,
#endif /* BTA_JV_L2CAP_INCLUDED */
    BTA_JV_MAX_INT_EVT
};

#ifndef BTA_JV_RFC_EV_MASK
#define BTA_JV_RFC_EV_MASK (PORT_EV_RXCHAR | PORT_EV_TXEMPTY | PORT_EV_FC | PORT_EV_FCS)
#endif

/* BTA_JV_API_ENABLE_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    tBTA_JV_DM_CBACK   *p_cback;
} tBTA_JV_API_ENABLE;

/* BTA_JV_API_DISABLE_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    tBTA_JV_RFCOMM_CBACK   *p_cback;
} tBTA_JV_API_DISABLE;

/* BTA_JV_API_START_DISCOVERY_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    UINT16 num_uuid;
    tSDP_UUID uuid_list[BTA_JV_MAX_UUIDS];
    UINT16 num_attr;
    UINT16 attr_list[BTA_JV_MAX_ATTRS];
    void            *user_data;      /* 携带呼叫者的私人数据*/
} tBTA_JV_API_START_DISCOVERY;

enum {
    BTA_JV_PM_FREE_ST = 0, /* 空PM插槽*/
    BTA_JV_PM_IDLE_ST,
    BTA_JV_PM_BUSY_ST
};

/* BTA JV PM控制块*/
typedef struct {
    UINT32          handle;     /* 连接手柄*/
    UINT8           state;      /* 状态：请参见上面的枚举*/
    tBTA_JV_PM_ID   app_id;     /* JV应用程序特定id，指示要使用的功率表*/
    BD_ADDR         peer_bd_addr;    /* 对等BD地址*/
} tBTA_JV_PM_CB;

enum {
    BTA_JV_ST_NONE = 0,
    BTA_JV_ST_CL_OPENING,
    BTA_JV_ST_CL_OPEN,
    BTA_JV_ST_CL_CLOSING,
    BTA_JV_ST_SR_LISTEN,
    BTA_JV_ST_SR_OPEN,
    BTA_JV_ST_SR_CLOSING
} ;
typedef UINT8  tBTA_JV_STATE;
#define BTA_JV_ST_CL_MAX    BTA_JV_ST_CL_CLOSING

#if BTA_JV_L2CAP_INCLUDED
/* JV L2CAP控制块*/
typedef struct {
    tBTA_JV_L2CAP_CBACK *p_cback;   /* 回调函数*/
    UINT16              psm;        /* 用于此服务器连接的psm*/
    tBTA_JV_STATE       state;      /* 此控制块的状态*/
    tBTA_SERVICE_ID     sec_id;     /* 服务id*/
    UINT32              handle;     /* 报告给javaapp的句柄（与gap句柄相同）*/
    BOOLEAN             cong;       /* TRUE，如果拥堵*/
    tBTA_JV_PM_CB      *p_pm_cb;    /* ptr到pm控制块，NULL：未使用*/
    void                *user_data; /* 用于从更高层回调的用户数据*/
} tBTA_JV_L2C_CB;
#endif /* BTA_JV_L2CAP_INCLUDED */

#define BTA_JV_RFC_HDL_MASK         0xFF
#define BTA_JV_RFCOMM_MASK          0x80
#define BTA_JV_ALL_APP_ID           0xFF
#define BTA_JV_RFC_HDL_TO_SIDX(r)   (((r)&0xFF00) >> 8)
#define BTA_JV_RFC_H_S_TO_HDL(h, s) ((h)|(s<<8))

/* 端口控制块*/
typedef struct {
    UINT32              handle;     /* jv的rfcomm会话句柄*/
    UINT16              port_handle;/* 左舷手柄*/
    tBTA_JV_STATE       state;      /* 此控制块的状态*/
    UINT8               max_sess;   /* 最大会话数*/
    void                *user_data; /* 携带呼叫者的私人数据*/
    BOOLEAN             cong;       /* TRUE，如果拥堵*/
    tBTA_JV_PM_CB       *p_pm_cb;   /* ptr到pm控制块，NULL：未使用*/
} tBTA_JV_PCB;

/* JV RFCOMM控制块*/
typedef struct {
    tBTA_JV_RFCOMM_CBACK *p_cback;  /* 回调函数*/
    UINT16              rfc_hdl[BTA_JV_MAX_RFC_SR_SESSION];
    tBTA_SERVICE_ID     sec_id;     /* 服务id*/
    UINT8               handle;     /* index：报告给javaapp的句柄*/
    UINT8               scn;        /* 服务器的scn*/
    UINT8               max_sess;   /* 最大会话数*/
    int                 curr_sess;   /* 当前会话计数*/
} tBTA_JV_RFC_CB;

#if BTA_JV_L2CAP_INCLUDED
/* BTA_JV_API_L2CAP_CONNECT_EVT和BTA_JV-API_L2CAP _CONNECT_LE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_SEC            sec_mask;
    tBTA_JV_ROLE        role;
    union {
        UINT16          remote_psm;
        UINT16          remote_chan;
    };
    UINT16              rx_mtu;
    BD_ADDR             peer_bd_addr;
    INT32               has_cfg;
    tL2CAP_CFG_INFO     cfg;
    INT32               has_ertm_info;
    tL2CAP_ERTM_INFO    ertm_info;
    tBTA_JV_L2CAP_CBACK *p_cback;
    void                *user_data;
} tBTA_JV_API_L2CAP_CONNECT;

/* BTA_JV_API_L2CAP_SERVER_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_SEC            sec_mask;
    tBTA_JV_ROLE        role;
    union {
        UINT16          local_psm;
        UINT16          local_chan;
    };
    UINT16              rx_mtu;
    INT32               has_cfg;
    tL2CAP_CFG_INFO     cfg;
    INT32               has_ertm_info;
    tL2CAP_ERTM_INFO    ertm_info;
    tBTA_JV_L2CAP_CBACK *p_cback;
    void                *user_data;
} tBTA_JV_API_L2CAP_SERVER;

/* BTA_JV_API_L2CAP_CLOSE_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    UINT32          handle;
    tBTA_JV_L2C_CB  *p_cb;
} tBTA_JV_API_L2CAP_CLOSE;

/* BTA_JV_API_L2CAP_READ_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT32              handle;
    UINT32              req_id;
    tBTA_JV_L2CAP_CBACK *p_cback;
    UINT8              *p_data;
    UINT16              len;
    void                *user_data;
} tBTA_JV_API_L2CAP_READ;

/* BTA_JV_API_L2CAP_WRITE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT32              handle;
    UINT32              req_id;
    tBTA_JV_L2C_CB      *p_cb;
    UINT8               *p_data;
    UINT16              len;
    void                *user_data;
} tBTA_JV_API_L2CAP_WRITE;

/* BTA_JV_API_L2CAP_WRITE_FIXED_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT16              channel;
    BD_ADDR             addr;
    UINT32              req_id;
    tBTA_JV_L2CAP_CBACK *p_cback;
    UINT8               *p_data;
    UINT16              len;
    void                *user_data;
} tBTA_JV_API_L2CAP_WRITE_FIXED;
#endif /* BTA_JV_L2CAP_INCLUDED */

/* BTA_JV_API_RFCOMM_CONNECT_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    tBTA_SEC        sec_mask;
    tBTA_JV_ROLE    role;
    UINT8           remote_scn;
    BD_ADDR         peer_bd_addr;
    tBTA_JV_RFCOMM_CBACK *p_cback;
    void            *user_data;
} tBTA_JV_API_RFCOMM_CONNECT;

/* BTA_JV_API_RFCOMM_SERVER_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    tBTA_SEC        sec_mask;
    tBTA_JV_ROLE    role;
    UINT8           local_scn;
    UINT8           max_session;
    UINT32          handle;
    tBTA_JV_RFCOMM_CBACK *p_cback;
    void            *user_data;
} tBTA_JV_API_RFCOMM_SERVER;

/* BTA_JV_API_RFCOMM_READ_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    UINT32          handle;
    UINT32          req_id;
    UINT8           *p_data;
    UINT16          len;
    tBTA_JV_RFC_CB  *p_cb;
    tBTA_JV_PCB     *p_pcb;
} tBTA_JV_API_RFCOMM_READ;

/* BTA_JV_API_SET_PM_PROFILE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT32              handle;
    tBTA_JV_PM_ID       app_id;
    tBTA_JV_CONN_STATE  init_st;
} tBTA_JV_API_SET_PM_PROFILE;

/* BTA_JV_API_PM_STATE_CHANGE_VT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_JV_PM_CB       *p_cb;
    tBTA_JV_CONN_STATE  state;
} tBTA_JV_API_PM_STATE_CHANGE;

/* BTA_JV_API_RFCOMM_WRITE_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    UINT32          handle;
    UINT32          req_id;
    UINT8           *p_data;
    int             len;
    tBTA_JV_RFC_CB  *p_cb;
    tBTA_JV_PCB     *p_pcb;
} tBTA_JV_API_RFCOMM_WRITE;

/* BTA_JV_API_RFCOMM_FLOW_CONTROL_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    tBTA_JV_RFC_CB  *p_cb;
    tBTA_JV_PCB     *p_pcb;
    UINT16      credits_given;
} tBTA_JV_API_RFCOMM_FLOW_CONTROL;

/* BTA_JV_API_RFCOMM_CLOSE_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    UINT32          handle;
    tBTA_JV_RFC_CB  *p_cb;
    tBTA_JV_PCB     *p_pcb;
    tBTA_JV_RFCOMM_CBACK *p_cback;
    void            *user_data;
} tBTA_JV_API_RFCOMM_CLOSE;

/* BTA_JV_API_CREATE_RECORD_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
#define ESP_SDP_SERVER_NAME_MAX (32)
    char name[ESP_SDP_SERVER_NAME_MAX + 1];
    INT32       channel;
    void        *user_data;
} tBTA_JV_API_CREATE_RECORD;

/* BTA_JV_API_ADD_ATTRIBUTE_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    UINT32      handle;
    UINT16      attr_id;
    UINT8       *p_value;
    INT32       value_size;
} tBTA_JV_API_ADD_ATTRIBUTE;

/* BTA_JV_API_FREE_SCN_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    INT32       type;       /* BTA_JV_CONN_TYPE_之一*/
    UINT16      scn;
    tBTA_JV_RFCOMM_CBACK *p_cback;
    void        *user_data;
} tBTA_JV_API_FREE_CHANNEL;

/* BTA_JV_API_ALLOC_CHANNEL_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    INT32       type;       /* BTA_JV_CONN_TYPE_之一*/
    INT32       channel;    /* 可选地请求特定频道*/
    void        *user_data;
} tBTA_JV_API_ALLOC_CHANNEL;
/* 所有数据类型的联合*/
typedef union {
    /* GKI事件缓冲区标头*/
    BT_HDR                          hdr;
    tBTA_JV_API_ENABLE              enable;
    tBTA_JV_API_DISABLE             disable;
    tBTA_JV_API_START_DISCOVERY     start_discovery;
    tBTA_JV_API_ALLOC_CHANNEL       alloc_channel;
    tBTA_JV_API_FREE_CHANNEL        free_channel;
    tBTA_JV_API_CREATE_RECORD       create_record;
    tBTA_JV_API_ADD_ATTRIBUTE       add_attr;
#if BTA_JV_L2CAP_INCLUDED
    tBTA_JV_API_L2CAP_CONNECT       l2cap_connect;
    tBTA_JV_API_L2CAP_READ          l2cap_read;
    tBTA_JV_API_L2CAP_WRITE         l2cap_write;
    tBTA_JV_API_L2CAP_CLOSE         l2cap_close;
    tBTA_JV_API_L2CAP_SERVER        l2cap_server;
    tBTA_JV_API_L2CAP_WRITE_FIXED   l2cap_write_fixed;
#endif /* BTA_JV_L2CAP_INCLUDED */
    tBTA_JV_API_RFCOMM_CONNECT      rfcomm_connect;
    tBTA_JV_API_RFCOMM_READ         rfcomm_read;
    tBTA_JV_API_RFCOMM_WRITE        rfcomm_write;
    tBTA_JV_API_RFCOMM_FLOW_CONTROL rfcomm_fc;
    tBTA_JV_API_SET_PM_PROFILE      set_pm;
    tBTA_JV_API_PM_STATE_CHANGE     change_pm_state;
    tBTA_JV_API_RFCOMM_CLOSE        rfcomm_close;
    tBTA_JV_API_RFCOMM_SERVER       rfcomm_server;
} tBTA_JV_MSG;

/* JV控制块*/
typedef struct {
    /* 报告给JV用户的SDP句柄是SDP_handle[]的（索引+1）。如果sdp_handle[i]==0，则不使用它。否则sdp_handle[i]是堆栈sdp句柄。*/
    UINT32                  sdp_handle[BTA_JV_MAX_SDP_REC]; /* SDP记录已创建*/
    UINT8                   *p_sel_raw_data;/* 上次服务选择的原始数据*/
    tBTA_JV_DM_CBACK        *p_dm_cback;
#if BTA_JV_L2CAP_INCLUDED
    tBTA_JV_L2C_CB          l2c_cb[BTA_JV_MAX_L2C_CONN];    /* index是GAP句柄（索引）*/
#endif /* BTA_JV_L2CAP_INCLUDED */
    tBTA_JV_RFC_CB          rfc_cb[BTA_JV_MAX_RFC_CONN];
    tBTA_JV_PCB             port_cb[MAX_RFC_PORTS];         /* 该数组的索引是port_handle，*/
    UINT8                   sec_id[BTA_JV_NUM_SERVICE_ID];  /* 服务ID*/
    BOOLEAN                 scn[BTA_JV_MAX_SCN];            /* 由java分配的SCN*/
    UINT16                  free_psm_list[BTA_JV_MAX_L2C_CONN];  /* 由java释放的PSM（可以重用）*/
    UINT8                   sdp_active;                     /* 参见BTA_JV_SDP_ACT_**/
    tSDP_UUID               uuid;                           /* sdp发现的当前uuid*/
    tBTA_JV_PM_CB           pm_cb[BTA_JV_PM_MAX_NUM];       /* 每个合资企业处理基础上的PM*/
} tBTA_JV_CB;

enum {
    BTA_JV_SDP_ACT_NONE = 0,
    BTA_JV_SDP_ACT_YES,     /* 等待SDP结果*/
    BTA_JV_SDP_ACT_CANCEL   /* 等待取消完成*/
};

/* JV控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_JV_CB bta_jv_cb;
#else
extern tBTA_JV_CB *bta_jv_cb_ptr;
#define bta_jv_cb (*bta_jv_cb_ptr)
#endif

/* 配置结构*/
extern tBTA_JV_CFG *p_bta_jv_cfg;

extern BOOLEAN bta_jv_sm_execute(BT_HDR *p_msg);

extern void bta_jv_enable (tBTA_JV_MSG *p_data);
extern void bta_jv_disable (tBTA_JV_MSG *p_data);
extern void bta_jv_get_channel_id (tBTA_JV_MSG *p_data);
extern void bta_jv_free_scn (tBTA_JV_MSG *p_data);
extern void bta_jv_start_discovery (tBTA_JV_MSG *p_data);
extern void bta_jv_create_record (tBTA_JV_MSG *p_data);
extern void bta_jv_delete_record (tBTA_JV_MSG *p_data);
#if BTA_JV_L2CAP_INCLUDED
extern void bta_jv_l2cap_connect (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_close (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_start_server (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_stop_server (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_read (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_write (tBTA_JV_MSG *p_data);
#endif /* BTA_JV_L2CAP_INCLUDED */
extern void bta_jv_rfcomm_connect (tBTA_JV_MSG *p_data);
extern void bta_jv_rfcomm_close (tBTA_JV_MSG *p_data);
extern void bta_jv_rfcomm_start_server (tBTA_JV_MSG *p_data);
extern void bta_jv_rfcomm_stop_server (tBTA_JV_MSG *p_data);
extern void bta_jv_rfcomm_read (tBTA_JV_MSG *p_data);
extern void bta_jv_rfcomm_write (tBTA_JV_MSG *p_data);
extern void bta_jv_rfcomm_flow_control(tBTA_JV_MSG *p_data);
extern void bta_jv_set_pm_profile (tBTA_JV_MSG *p_data);
extern void bta_jv_change_pm_state(tBTA_JV_MSG *p_data);
#if BTA_JV_L2CAP_INCLUDED
extern void bta_jv_l2cap_connect_le (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_start_server_le (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_stop_server_le (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_write_fixed (tBTA_JV_MSG *p_data);
extern void bta_jv_l2cap_close_fixed (tBTA_JV_MSG *p_data);
#endif /* BTA_JV_L2CAP_INCLUDED */

#endif  ///定义的BTA_JV_INCLUDE&BTA_JV_inCLUDE==真
#endif /* BTA_JV_INT_H */

