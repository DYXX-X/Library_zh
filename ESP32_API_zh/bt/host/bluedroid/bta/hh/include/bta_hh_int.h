/******************************************************************************
 * 版权所有（C）2005-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此文件包含BTA HID主机内部定义
 *
 ******************************************************************************/

#ifndef BTA_HH_INT_H
#define BTA_HH_INT_H

#include "bta/bta_sys.h"
#include "bta/utl.h"
#include "bta/bta_hh_api.h"

//#如果BTA_HH_LE_INCLUDED==真
#include "bta/bta_gatt_api.h"
//#结束符
#if defined(BTA_HH_INCLUDED) && (BTA_HH_INCLUDED == TRUE)

/* 可以移动到bta/bta_api。小时*/
#define BTA_HH_MAX_RPT_CHARS    8

#if (BTA_GATT_INCLUDED == FALSE || BLE_INCLUDED == FALSE)
#undef BTA_HH_LE_INCLUDED
#define BTA_HH_LE_INCLUDED      FALSE
#endif

/* 状态机事件，这些事件由状态机处理*/
enum {
    BTA_HH_API_OPEN_EVT     = BTA_SYS_EVT_START(BTA_ID_HH),
    BTA_HH_API_CLOSE_EVT,
    BTA_HH_INT_OPEN_EVT,
    BTA_HH_INT_CLOSE_EVT,
    BTA_HH_INT_DATA_EVT,
    BTA_HH_INT_CTRL_DATA,
    BTA_HH_INT_HANDSK_EVT,
    BTA_HH_SDP_CMPL_EVT,
    BTA_HH_API_WRITE_DEV_EVT,
    BTA_HH_API_GET_DSCP_EVT,
    BTA_HH_API_MAINT_DEV_EVT,
    BTA_HH_OPEN_CMPL_EVT,
#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
    BTA_HH_GATT_CLOSE_EVT,
    BTA_HH_GATT_OPEN_EVT,
    BTA_HH_START_ENC_EVT,
    BTA_HH_ENC_CMPL_EVT,
    BTA_HH_GATT_READ_CHAR_CMPL_EVT,
    BTA_HH_GATT_WRITE_CHAR_CMPL_EVT,
    BTA_HH_GATT_READ_DESCR_CMPL_EVT,
    BTA_HH_GATT_WRITE_DESCR_CMPL_EVT,
    BTA_HH_API_SCPP_UPDATE_EVT,
    BTA_HH_GATT_ENC_CMPL_EVT,
#endif

    /* 未由执行状态机处理*/
    BTA_HH_API_ENABLE_EVT,
    BTA_HH_API_DISABLE_EVT,
    BTA_HH_DISC_CMPL_EVT
};
typedef UINT16 tBTA_HH_INT_EVT;         /* HID主机内部事件*/

#define BTA_HH_INVALID_EVT      (BTA_HH_DISC_CMPL_EVT + 1)

/* 用于在BTE事件和BTA事件之间映射的事件*/
#define BTA_HH_FST_TRANS_CB_EVT         BTA_HH_GET_RPT_EVT
#define BTA_HH_FST_BTE_TRANS_EVT        HID_TRANS_GET_REPORT

/* 用于设备维护API调用的子事件代码*/
#define BTA_HH_ADD_DEV          0
#define BTA_HH_REMOVE_DEV       1

/* 状态机状态*/
enum {
    BTA_HH_NULL_ST,
    BTA_HH_IDLE_ST,
    BTA_HH_W4_CONN_ST,
    BTA_HH_CONN_ST
#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
    , BTA_HH_W4_SEC
#endif
    , BTA_HH_INVALID_ST   /* 用于在执行SM功能之前检查无效状态*/

};
typedef UINT8 tBTA_HH_STATE;

/* 用于向HID设备发送命令/数据的数据结构*/
typedef struct {
    BT_HDR           hdr;
    UINT8            t_type;
    UINT8            param;
    UINT8            rpt_id;
#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
    UINT8            srvc_id;
#endif
    UINT16           data;
    BT_HDR           *p_data;
} tBTA_HH_CMD_DATA;

/* BTA_HH_API_ENABLE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    UINT8               sec_mask;
    UINT8               service_name[BTA_SERVICE_NAME_LEN + 1];
    tBTA_HH_CBACK   *p_cback;
} tBTA_HH_API_ENABLE;

typedef struct {
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    UINT8           sec_mask;
    tBTA_HH_PROTO_MODE  mode;
} tBTA_HH_API_CONN;

/* 来自BTE HID回调的内部事件数据*/
typedef struct {
    BT_HDR          hdr;
    BD_ADDR         addr;
    UINT32          data;
    BT_HDR          *p_data;
} tBTA_HH_CBACK_DATA;

typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bda;
    UINT16              attr_mask;
    UINT16              sub_event;
    UINT8               sub_class;
    UINT8               app_id;
    tBTA_HH_DEV_DSCP_INFO      dscp_info;
} tBTA_HH_MAINT_DEV;

#if BTA_HH_LE_INCLUDED == TRUE
typedef struct {
    BT_HDR              hdr;
    UINT16              conn_id;
    tBTA_GATT_REASON    reason;         /* 断开原因代码，在报告连接事件时不有用*/

} tBTA_HH_LE_CLOSE;

typedef struct {
    BT_HDR              hdr;
    UINT16              scan_int;
    UINT16              scan_win;
} tBTA_HH_SCPP_UPDATE;
#endif
/* 所有事件数据类型的联合*/
typedef union {
    BT_HDR                   hdr;
    tBTA_HH_API_ENABLE       api_enable;
    tBTA_HH_API_CONN         api_conn;
    tBTA_HH_CMD_DATA         api_sndcmd;
    tBTA_HH_CBACK_DATA       hid_cback;
    tBTA_HH_STATUS           status;
    tBTA_HH_MAINT_DEV        api_maintdev;
#if BTA_HH_LE_INCLUDED == TRUE
    tBTA_HH_LE_CLOSE         le_close;
    tBTA_GATTC_OPEN          le_open;
    tBTA_HH_SCPP_UPDATE      le_scpp_update;
    tBTA_GATTC_ENC_CMPL_CB   le_enc_cmpl;
#endif
} tBTA_HH_DATA;

#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
typedef struct {
    UINT8                   index;
    BOOLEAN                 in_use;
    UINT8                   inst_id;    /* 共享服务实例ID和报告实例ID，对于服务实例ID为高4，对于特征实例ID为低4*/
    tBTA_HH_RPT_TYPE        rpt_type;
    UINT16                  uuid;
    UINT8                   prop;
    UINT8                   rpt_id;
    BOOLEAN                 client_cfg_exist;
    UINT16                  client_cfg_value;
} tBTA_HH_LE_RPT;

#ifndef BTA_HH_LE_RPT_MAX
#define BTA_HH_LE_RPT_MAX       20
#endif

typedef struct {
    BOOLEAN                 in_use;
    tBTA_HH_LE_RPT          report[BTA_HH_LE_RPT_MAX];

#define BTA_HH_LE_PROTO_MODE_BIT        0x01
#define BTA_HH_LE_CP_BIT                0x02
    UINT8                   option_char; /* 控制点字符是否存在*/

    BOOLEAN                 expl_incl_srvc;
    UINT8                   incl_srvc_inst; /* 假设只有一项服务：电池服务*/
    UINT8                   cur_expl_char_idx; /* 当前正在发现服务索引*/
    UINT8                   *rpt_map;
    UINT16                  ext_rpt_ref;
    tBTA_HH_DEV_DESCR       descriptor;

} tBTA_HH_LE_HID_SRVC;

#ifndef BTA_HH_LE_HID_SRVC_MAX
#define BTA_HH_LE_HID_SRVC_MAX      1
#endif

/* 将HID句柄转换为LE CB索引*/
#define BTA_HH_GET_LE_CB_IDX(x)         (((x) >> 4) - 1)
/* 将GATT连接ID转换为HID设备句柄，它是UINT8的hi 4位*/
#define BTA_HH_GET_LE_DEV_HDL(x)        (UINT8)(((x)  + 1) << 4)
/* 检查设备句柄是否为LE设备句柄*/
#define BTA_HH_IS_LE_DEV_HDL(x)        ((x) & 0xf0)
#define BTA_HH_IS_LE_DEV_HDL_VALID(x)  (((x)>>4) <= BTA_HH_LE_MAX_KNOWN)
#endif

/* 设备控制块*/
typedef struct {
    tBTA_HH_DEV_DSCP_INFO  dscp_info;      /* 报告描述符和DI信息*/
    BD_ADDR             addr;           /* HID设备的BD地址*/
    UINT16              attr_mask;      /* 属性掩码*/
    UINT16              w4_evt;         /* W4_握手事件名称*/
    UINT8               index;          /* 句柄索引引用的索引号*/
    UINT8               sub_class;      /* Cod子类*/
    UINT8               sec_mask;       /* 安全面罩*/
    UINT8               app_id;         /* 此连接的应用程序ID*/
    UINT8               hid_handle;     /* 设备句柄：常规HID的低4位：HID_HOST_MAX_DEVICES不能超过15；LE HID的高4位：GATT_MAX_PHY_CHANNEL不能超过15*/
    BOOLEAN             vp;             /* 虚拟拔出标志*/
    BOOLEAN             in_use;         /* 当前使用的控制块*/
    BOOLEAN             incoming_conn;  /* 是传入连接吗？*/
    UINT8               incoming_hid_handle;  /* 传入连接的临时句柄？*/
    BOOLEAN             opened;         /* 如果设备成功打开HID连接，则为TRUE*/
    tBTA_HH_PROTO_MODE  mode;           /* 协议模式*/
    tBTA_HH_PROTO_MODE  new_mode;           /* 协议模式*/
    tBTA_HH_STATE       state;          /* CB状态*/

#if (BTA_HH_LE_INCLUDED == TRUE)
#define BTA_HH_LE_DISC_NONE     0x00
#define BTA_HH_LE_DISC_HIDS     0x01
#define BTA_HH_LE_DISC_DIS      0x02
#define BTA_HH_LE_DISC_SCPS     0x04

    UINT8               disc_active;
    tBTA_HH_STATUS      status;
    tBTA_GATT_REASON    reason;
    BOOLEAN             is_le_device;
    tBTA_HH_LE_HID_SRVC hid_srvc[BTA_HH_LE_HID_SRVC_MAX];
    UINT16              conn_id;
    BOOLEAN             in_bg_conn;
    UINT8               total_srvc;
    UINT8               clt_cfg_idx;
    UINT8               cur_srvc_index; /* 当前正在发现服务索引*/
    BOOLEAN             scps_supported;

#define BTA_HH_LE_SCPS_NOTIFY_NONE    0
#define BTA_HH_LE_SCPS_NOTIFY_SPT  0x01
#define BTA_HH_LE_SCPS_NOTIFY_ENB  0x02
    UINT8               scps_notify;   /* 支持扫描刷新/已启用通知*/
#endif

    BOOLEAN             security_pending;
} tBTA_HH_DEV_CB;

/* 键盘解析控制块*/
typedef struct {
    BOOLEAN             mod_key[4]; /* ctrl、shift（上）、Alt、GUI*/
    BOOLEAN             num_lock;
    BOOLEAN             caps_lock;
    UINT8               last_report[BTA_HH_MAX_RPT_CHARS];
} tBTA_HH_KB_CB;

/******************************************************************************
** 主控制块
*******************************************************************************/
typedef struct {
    tBTA_HH_KB_CB           kb_cb;                  /* 键盘控制块，假设BTA同时只连接一个键盘*/
    tBTA_HH_DEV_CB          kdev[BTA_HH_MAX_DEVICE]; /* 设备控制块*/
    tBTA_HH_DEV_CB         *p_cur;              /* 当前设备控制块idx，用于sdp*/
    UINT8                   cb_index[BTA_HH_MAX_KNOWN]; /* 维护CB索引映射到开发句柄*/
#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
    UINT8                   le_cb_index[BTA_HH_MAX_DEVICE]; /* 维护LE开发句柄的CB索引映射*/
    tBTA_GATTC_IF           gatt_if;
#endif
    tBTA_HH_CBACK       *p_cback;               /* 应用程序回调*/
    tSDP_DISCOVERY_DB      *p_disc_db;
    UINT8                   trace_level;            /* 跟踪级别*/
    UINT8                   cnt_num;                /* 连接的设备编号*/
    BOOLEAN                 w4_disable;             /* w4禁用标志*/
}
tBTA_HH_CB;

#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_HH_CB  bta_hh_cb;
#else
extern tBTA_HH_CB *bta_hh_cb_ptr;
#define bta_hh_cb (*bta_hh_cb_ptr)
#endif

/* 来自bta_hhcfg。c*/
extern tBTA_HH_CFG *p_bta_hh_cfg;

/*****************************************************************************
**  功能原型
*****************************************************************************/
extern BOOLEAN bta_hh_hdl_event(BT_HDR *p_msg);
extern void bta_hh_sm_execute(tBTA_HH_DEV_CB *p_cb, UINT16 event,
                              tBTA_HH_DATA *p_data);

/* 动作函数*/
extern void bta_hh_api_disc_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_open_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_close_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_data_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_ctrl_dat_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_start_sdp(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_sdp_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_write_dev_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_get_dscp_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_handsk_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_maint_dev_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_open_cmpl_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_open_failure(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);

/* 效用函数*/
extern UINT8  bta_hh_find_cb(BD_ADDR bda);
extern void bta_hh_parse_keybd_rpt(tBTA_HH_BOOT_RPT *p_kb_data,
                                   UINT8 *p_report, UINT16 report_len);
extern void bta_hh_parse_mice_rpt(tBTA_HH_BOOT_RPT *p_kb_data,
                                  UINT8 *p_report, UINT16 report_len);
extern BOOLEAN bta_hh_tod_spt(tBTA_HH_DEV_CB *p_cb, UINT8 sub_class);
extern void bta_hh_clean_up_kdev(tBTA_HH_DEV_CB *p_cb);

extern void bta_hh_add_device_to_list(tBTA_HH_DEV_CB *p_cb, UINT8 handle,
                                      UINT16 attr_mask,
                                      tHID_DEV_DSCP_INFO *p_dscp_info,
                                      UINT8 sub_class, UINT16 max_latency, UINT16 min_tout, UINT8 app_id);
extern void bta_hh_update_di_info(tBTA_HH_DEV_CB *p_cb, UINT16 vendor_id, UINT16 product_id,
                                  UINT16 version, UINT8 flag);
extern void bta_hh_cleanup_disable(tBTA_HH_STATUS status);

extern UINT8 bta_hh_dev_handle_to_cb_idx(UINT8 dev_handle);

/* 状态机外部使用的动作函数*/
extern void bta_hh_api_enable(tBTA_HH_DATA *p_data);
extern void bta_hh_api_disable(void);
extern void bta_hh_disc_cmpl(void);

extern tBTA_HH_STATUS bta_hh_read_ssr_param(BD_ADDR bd_addr, UINT16 *p_max_ssr_lat, UINT16 *p_min_ssr_tout);

/* LE HID的函数*/
#if (BTA_HH_LE_INCLUDED == TRUE)
extern void bta_hh_le_enable(void);
extern BOOLEAN bta_hh_le_is_hh_gatt_if(tBTA_GATTC_IF client_if);
extern void bta_hh_le_deregister(void);
extern BOOLEAN bta_hh_is_le_device(tBTA_HH_DEV_CB *p_cb, BD_ADDR remote_bda);
extern void bta_hh_le_open_conn(tBTA_HH_DEV_CB *p_cb, BD_ADDR remote_bda);
extern void bta_hh_le_api_disc_act(tBTA_HH_DEV_CB *p_cb);
extern void bta_hh_le_get_dscp_act(tBTA_HH_DEV_CB *p_cb);
extern void bta_hh_le_write_dev_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern UINT8 bta_hh_le_add_device(tBTA_HH_DEV_CB *p_cb, tBTA_HH_MAINT_DEV *p_dev_info);
extern void bta_hh_le_remove_dev_bg_conn(tBTA_HH_DEV_CB *p_cb);
extern void bta_hh_le_open_fail(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_gatt_open(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_gatt_close(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_start_security(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_start_srvc_discovery(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_w4_le_read_char_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_le_read_char_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_w4_le_read_descr_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_le_read_descr_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_w4_le_write_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_le_write_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_le_write_char_descr_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_start_security(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_security_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_le_update_scpp(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
extern void bta_hh_le_notify_enc_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_ci_load_rpt (tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_buf);
#endif

#if BTA_HH_DEBUG
extern void bta_hh_trace_dev_db(void);
#endif

#endif  ///已定义（BTA_HH_INCLUDED）&&（BTA_HH_INCLUDED==TRUE）
#endif

