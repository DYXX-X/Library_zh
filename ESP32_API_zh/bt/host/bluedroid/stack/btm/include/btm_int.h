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
 * 该文件包含主要蓝牙管理器（BTM）内部定义。
 *
 ******************************************************************************/
#ifndef BTM_INT_H
#define BTM_INT_H

typedef struct tBTM_SEC_DEV_REC tBTM_SEC_DEV_REC;

#include "common/bt_defs.h"
#include "common/bt_target.h"
#include "stack/hcidefs.h"

#include "stack/rfcdefs.h"

#include "stack/btm_api.h"
#include "osi/fixed_queue.h"

#if (BLE_INCLUDED == TRUE)
#include "btm_ble_int.h"
#endif
#if (SMP_INCLUDED == TRUE)
#include "stack/smp_api.h"
#endif

#define ESP_VS_REM_LEGACY_AUTH_CMP 0x03

#if BTM_MAX_LOC_BD_NAME_LEN > 0
typedef char tBTM_LOC_BD_NAME[BTM_MAX_LOC_BD_NAME_LEN + 1];
#endif

#define  BTM_ACL_IS_CONNECTED(bda)   (btm_bda_to_acl (bda, BT_TRANSPORT_BR_EDR) != NULL)

/* 服务器通道号（SCN）管理的定义
*/
#define BTM_MAX_SCN      PORT_MAX_RFC_PORTS

/* 定义受支持和异常2.0 ACL数据包类型的掩码
*/
#define BTM_ACL_SUPPORTED_PKTS_MASK      (HCI_PKT_TYPES_MASK_DM1        | \
                                          HCI_PKT_TYPES_MASK_DH1        | \
                                          HCI_PKT_TYPES_MASK_DM3        | \
                                          HCI_PKT_TYPES_MASK_DH3        | \
                                          HCI_PKT_TYPES_MASK_DM5        | \
                                          HCI_PKT_TYPES_MASK_DH5)

#define BTM_ACL_EXCEPTION_PKTS_MASK      (HCI_PKT_TYPES_MASK_NO_2_DH1   | \
                                          HCI_PKT_TYPES_MASK_NO_3_DH1   | \
                                          HCI_PKT_TYPES_MASK_NO_2_DH3   | \
                                          HCI_PKT_TYPES_MASK_NO_3_DH3   | \
                                          HCI_PKT_TYPES_MASK_NO_2_DH5   | \
                                          HCI_PKT_TYPES_MASK_NO_3_DH5)

#define BTM_EPR_AVAILABLE(p) ((HCI_ATOMIC_ENCRYPT_SUPPORTED((p)->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0]) && \
                               HCI_ATOMIC_ENCRYPT_SUPPORTED(controller_get_interface()->get_features_classic(0)->as_array)) \
                               ? TRUE : FALSE)

#define BTM_IS_BRCM_CONTROLLER() (controller_get_interface()->get_bt_version()->manufacturer == LMP_COMPID_BROADCOM)

typedef struct t_acl_db_param{
#define ACL_DB_HANDLE 0x00
#define ACL_DB_BDA    0x01
    UINT8 type;
    void *p_data1;
    void *p_data2;
}tACL_DB_PARAM;

enum {
    BTM_PM_ST_ACTIVE  = BTM_PM_STS_ACTIVE,
    BTM_PM_ST_HOLD    = BTM_PM_STS_HOLD,
    BTM_PM_ST_SNIFF   = BTM_PM_STS_SNIFF,
    BTM_PM_ST_PARK    = BTM_PM_STS_PARK,
    BTM_PM_ST_PENDING = BTM_PM_STS_PENDING
};
typedef UINT8 tBTM_PM_STATE;

typedef struct {
    tBTM_PM_PWR_MD req_mode[BTM_MAX_PM_RECORDS + 1]; /* 所需的连接模式和参数*/
    tBTM_PM_PWR_MD set_mode;  /* 模式和参数发送到主机控制器。*/
    UINT16         interval;  /* 距上次模式更改事件的间隔。*/
#if (BTM_SSR_INCLUDED == TRUE)
    UINT16         max_lat;   /* 存储的SSR最大延迟*/
    UINT16         min_rmt_to;/* 存储的SSR最小远程超时*/
    UINT16         min_loc_to;/* 存储的SSR最小本地超时*/
#endif
    tBTM_PM_STATE  state;     /* 包含连接的当前模式*/
    BOOLEAN        chg_ind;   /* 请求更改指示*/
} tBTM_PM_MCB;

/* 定义ACL管理控制结构
*/
typedef struct {
UINT16          hci_handle;
UINT16          pkt_types_mask;
UINT16          clock_offset;
BD_ADDR         remote_addr;
DEV_CLASS       remote_dc;
BD_NAME         remote_name;

UINT16          manufacturer;
UINT16          lmp_subversion;
UINT16          link_super_tout;
BD_FEATURES     peer_lmp_features[HCI_EXT_FEATURES_PAGE_MAX + 1];    /* 设备的对等LMP扩展功能掩码表*/
UINT8           num_read_pages;
UINT8           lmp_version;

BOOLEAN         in_use;
UINT8           link_role;
BOOLEAN         link_up_issued;     /* 如果已发出busy_level链接，则为True*/
BOOLEAN         sc_downgrade;       /* 存储安全性是否降级。*/

#define BTM_ACL_LEGACY_AUTH_NONE                (0)
#define BTM_ACL_LEGACY_AUTH_SELF                (1<<0)
#define BTM_ACL_LEGACY_AUTH_REMOTE              (1<<1)
#define BTM_ACL_LEGACY_AUTH_MUTUAL              (1<<2)
UINT8           legacy_auth_state;

#define BTM_ACL_SWKEY_STATE_IDLE                0
#define BTM_ACL_SWKEY_STATE_MODE_CHANGE         1
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF      2
#define BTM_ACL_SWKEY_STATE_SWITCHING           3
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_ON       4
#define BTM_ACL_SWKEY_STATE_IN_PROGRESS         5
UINT8           switch_role_state;

#define BTM_ACL_ENCRYPT_STATE_IDLE              0
#define BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF       1   /* 加密关闭*/
#define BTM_ACL_ENCRYPT_STATE_TEMP_FUNC         2   /* 更改链接键或角色切换时暂时关闭*/
#define BTM_ACL_ENCRYPT_STATE_ENCRYPT_ON        3   /* 加密开启*/
UINT8           encrypt_state;                  /* 总体BTM加密状态*/

#if BLE_INCLUDED == TRUE
tBT_TRANSPORT   transport;
BD_ADDR         conn_addr;              /* 用于此连接的本地设备地址*/
UINT8           conn_addr_type;         /* 此连接的本地设备地址类型*/
BD_ADDR         active_remote_addr;     /* 此连接上使用的远程地址*/
UINT8           active_remote_addr_type;         /* 此连接的本地设备地址类型*/
BD_FEATURES     peer_le_features;       /* 对等LE使用的设备功能掩码*/
tBTM_SET_PKT_DATA_LENGTH_CBACK *p_set_pkt_data_cback;
tBTM_LE_SET_PKT_DATA_LENGTH_PARAMS data_length_params;
BOOLEAN   data_len_updating;
// 数据len更新cmd缓存
BOOLEAN   data_len_waiting;
tBTM_SET_PKT_DATA_LENGTH_CBACK *p_set_data_len_cback_waiting;
UINT16 tx_len_waiting;
#endif
tBTM_PM_MCB     *p_pm_mode_db;          /* 指向每个ACL链接的PM模式控制块的指针*/

} tACL_CONN;

/*****************************************************
** TIMER定义
******************************************************/
#define TT_DEV_RESET     1
#define TT_DEV_RLN       2
#define TT_DEV_RLNKP     4              /* 读取链接策略设置*/

/* 定义设备管理控制结构
*/
typedef struct {
tBTM_DEV_STATUS_CB  *p_dev_status_cb;   /* 设备状态更改回调*/
tBTM_VS_EVT_CB      *p_vend_spec_cb[BTM_MAX_VSE_CALLBACKS];     /* 注册供应商特定事件*/

tBTM_CMPL_CB        *p_stored_link_key_cmpl_cb;   /* 读取/写入/删除存储的链接密钥*/

TIMER_LIST_ENT       reset_timer;
tBTM_CMPL_CB         *p_reset_cmpl_cb;

TIMER_LIST_ENT       rln_timer;
tBTM_CMPL_CB        *p_rln_cmpl_cb;     /* 当*/
/* 读取本地名称函数完成*/
TIMER_LIST_ENT       rssi_timer;
tBTM_CMPL_CB        *p_rssi_cmpl_cb;    /* 当*/
/* 读取rssi函数完成*/
TIMER_LIST_ENT       lnk_quality_timer;
tBTM_CMPL_CB        *p_lnk_qual_cmpl_cb;/* 当*/
/* 读链接质量功能完成*/
TIMER_LIST_ENT       txpwer_timer;
tBTM_CMPL_CB        *p_txpwer_cmpl_cb;    /* 当*/
/* 读入tx电源功能完成*/

TIMER_LIST_ENT       qossu_timer;
tBTM_CMPL_CB        *p_qossu_cmpl_cb;   /* 当*/
/* qos设置功能完成*/

tBTM_ROLE_SWITCH_CMPL switch_role_ref_data;
tBTM_CMPL_CB        *p_switch_role_cb;  /* 当*/
/* 请求的交换机角色已完成*/

TIMER_LIST_ENT       tx_power_timer;
tBTM_CMPL_CB        *p_tx_power_cmpl_cb;/* 要调用的回调函数*/

#if CLASSIC_BT_INCLUDED == TRUE
TIMER_LIST_ENT       afh_channels_timer;
tBTM_CMPL_CB        *p_afh_channels_cmpl_cb; /* 当调用回调函数时*/
/* 设置AFH通道已完成*/
#endif

DEV_CLASS            dev_class;         /* 本地设备类别*/

#if BLE_INCLUDED == TRUE

TIMER_LIST_ENT       ble_channels_timer;
tBTM_CMPL_CB        *p_ble_channels_cmpl_cb; /* 当ble set主机通道完成时要调用的回调函数*/

tBTM_CMPL_CB        *p_le_test_cmd_cmpl_cb;   /* 成功发送LE测试模式命令时要调用的回调函数*/

BD_ADDR                 read_tx_pwr_addr;   /* 读取TX功率目标地址*/

#define BTM_LE_SUPPORT_STATE_SIZE   8
UINT8                   le_supported_states[BTM_LE_SUPPORT_STATE_SIZE];

tBTM_BLE_LOCAL_ID_KEYS id_keys; /* 本地BLE ID密钥*/
BT_OCTET16 ble_encryption_key_value; /* BLE加密密钥*/

#if BTM_BLE_CONFORMANCE_TESTING == TRUE
BOOLEAN                 no_disc_if_pair_fail;
BOOLEAN                 enable_test_mac_val;
BT_OCTET8               test_mac;
BOOLEAN                 enable_test_local_sign_cntr;
UINT32                  test_local_sign_cntr;
#endif

#endif  /* BLE_INCLUDED */

tBTM_IO_CAP          loc_io_caps;       /* 本地设备的IO能力*/
tBTM_AUTH_REQ        loc_auth_req;      /* auth_req标志*/
BOOLEAN              secure_connections_only;    /* 如果出现以下情况，则拒绝服务级别0连接*/
/* 自身或对等设备不支持*/
/* 安全连接*/
} tBTM_DEVCB;


/* 定义用于查询的结构和常量
*/

/* 查询限额的定义*/
#define BTM_PER_INQ_MIN_MAX_PERIOD      HCI_PER_INQ_MIN_MAX_PERIOD
#define BTM_PER_INQ_MAX_MAX_PERIOD      HCI_PER_INQ_MAX_MAX_PERIOD
#define BTM_PER_INQ_MIN_MIN_PERIOD      HCI_PER_INQ_MIN_MIN_PERIOD
#define BTM_PER_INQ_MAX_MIN_PERIOD      HCI_PER_INQ_MAX_MIN_PERIOD
#define BTM_MAX_INQUIRY_LENGTH          HCI_MAX_INQUIRY_LENGTH
#define BTM_MIN_INQUIRY_LEN             0x01

#define BTM_MIN_INQ_TX_POWER    -70
#define BTM_MAX_INQ_TX_POWER    20

typedef struct {
UINT32          inq_count;          /* 用于确定响应是否已*/
/* 为当前查询操作接收。（我们没有*/
/* 想让呼叫者收到来自*/
/* 同一设备。*/
BD_ADDR         bd_addr;
} tINQ_BDADDR;

typedef struct {
UINT32          time_of_resp;
UINT32          inq_count;          /* “时间戳”具有特定查询计数的条目*/
/* 用于确定响应是否已*/
/* 为当前查询操作接收。（我们没有*/
/* 想让呼叫者收到来自*/
/* 同一设备。*/
tBTM_INQ_INFO   inq_info;
BOOLEAN         in_use;

#if (BLE_INCLUDED == TRUE)
BOOLEAN         scan_rsp;
#endif
} tINQ_DB_ENT;


enum {
INQ_NONE,
INQ_LE_OBSERVE,
INQ_GENERAL
};
typedef UINT8 tBTM_INQ_TYPE;

typedef struct {
    tBTM_CMPL_CB *p_remname_cmpl_cb;

#define BTM_EXT_RMT_NAME_TIMEOUT    40


    TIMER_LIST_ENT  rmt_name_timer_ent;

    UINT16           discoverable_mode;
    UINT16           connectable_mode;
    UINT16           page_scan_window;
    UINT16           page_scan_period;
    UINT16           inq_scan_window;
    UINT16           inq_scan_period;
    UINT16           inq_scan_type;
    UINT16           page_scan_type;        /* 当前页面扫描类型*/
    tBTM_INQ_TYPE    scan_type;

    BD_ADDR          remname_bda;           /* 活动远程名称请求的bd-addr的名称*/
#define BTM_RMT_NAME_INACTIVE       0
#define BTM_RMT_NAME_EXT            0x1     /* 通过API启动*/
#define BTM_RMT_NAME_SEC            0x2     /* 由安全经理内部发起*/
#define BTM_RMT_NAME_INQ            0x4     /* 通过查询在内部启动远程名称*/
    BOOLEAN          remname_active;        /* 外部API的远程名称请求的状态*/

    tBTM_CMPL_CB    *p_inq_cmpl_cb;
    tBTM_INQ_RESULTS_CB *p_inq_results_cb;
    tBTM_CMPL_CB    *p_inq_ble_cmpl_cb;     /*LE Observe专用的完成回调*/
    tBTM_INQ_RESULTS_CB *p_inq_ble_results_cb;/*只针对LE观察的结果回调*/
    tBTM_CMPL_CB    *p_inqfilter_cmpl_cb;   /* 查询筛选器完成后调用（如果不是NULL）*/
    UINT32           inq_counter;           /* 每次查询完成时计数器递增*/
    /* 用于确定是否重复设备*/
    /* 已对同一询问作出回应*/
    TIMER_LIST_ENT   inq_timer_ent;
    tINQ_BDADDR     *p_bd_db;               /* 指向保存bdaddrs的内存的指针*/
    UINT16           num_bd_entries;        /* 数据库中的条目数*/
    UINT16           max_bd_entries;        /* 可存储的最大条目数*/
    tINQ_DB_ENT      inq_db[BTM_INQ_DB_SIZE];
    tBTM_INQ_PARMS   inqparms;              /* 包含当前查询的参数*/
    tBTM_INQUIRY_CMPL inq_cmpl_info;        /* 上次查询的回复状态和数量*/

    UINT16           per_min_delay;         /* 电流周期最小延迟*/
    UINT16           per_max_delay;         /* 当前周期最大延迟*/
    BOOLEAN          inqfilt_active;
    UINT8            pending_filt_complete_event; /* 处理对应于的btm_event_filter_complete*/
    /* 已取消的查询*/
    UINT8            inqfilt_type;          /* 包含查询过滤器类型（BD ADDR、COD或Clear）*/

#define BTM_INQ_INACTIVE_STATE      0
#define BTM_INQ_CLR_FILT_STATE      1   /* 当前正在清除查询请求之前的查询筛选器*/
    /* （如果不使用过滤，则忽略）*/
#define BTM_INQ_SET_FILT_STATE      2   /* 在此状态下设置新过滤器（或关闭过滤器）*/
#define BTM_INQ_ACTIVE_STATE        3   /* 正在进行实际查询或定期查询*/
#define BTM_INQ_REMNAME_STATE       4   /* 远程名称请求处于活动状态*/

    UINT8            state;             /* 查询过程所处的当前状态*/
    UINT8            inq_active;        /* 指示查询类型的位掩码处于活动状态*/
    BOOLEAN          no_inc_ssp;        /* TRUE，停止对传入SSP的查询*/
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    btm_inq_state    next_state;        /*交织状态以确定要查询的下一模式*/
#endif
} tBTM_INQUIRY_VAR_ST;

/* 时钟偏移字段的MSB表示如果为TRUE，则偏移有效*/
#define BTM_CLOCK_OFFSET_VALID      0x8000

/* 定义安全管理所需的结构
*/

#define BTM_SEC_INVALID_HANDLE  0xFFFF

typedef UINT8 *BTM_BD_NAME_PTR;                        /* 指向设备名称的指针*/

/* 当安全过程完成时，此单元调用安全回调。参数为远程操作结果的BD地址
*/
typedef tBTM_SEC_CBACK tBTM_SEC_CALLBACK;

#define BTM_DATA_HANDLE_MASK 0x0FFF

#define BTMD_GET_HANDLE(u16) (UINT16)((u16) & BTM_DATA_HANDLE_MASK)

typedef void (tBTM_SCO_IND_CBACK) (UINT16 sco_inx) ;

/* 从SCO数据包类型掩码转换为ESCO并返回的MACRO*/
#define BTM_SCO_PKT_TYPE_MASK   (   HCI_PKT_TYPES_MASK_HV1      \
                                 |  HCI_PKT_TYPES_MASK_HV2      \
                                 |  HCI_PKT_TYPES_MASK_HV3)

/* 仅定义esco数据包类型的SCO类型的掩码*/
#define BTM_ESCO_PKT_TYPE_MASK  (   HCI_ESCO_PKT_TYPES_MASK_HV1 \
                                 |  HCI_ESCO_PKT_TYPES_MASK_HV2 \
                                 |  HCI_ESCO_PKT_TYPES_MASK_HV3)

#define BTM_SCO_2_ESCO(scotype)  ((UINT16)(((scotype) & BTM_SCO_PKT_TYPE_MASK) >> 5))
#define BTM_ESCO_2_SCO(escotype) ((UINT16)(((escotype) & BTM_ESCO_PKT_TYPE_MASK) << 5))

/* 定义支持的和异常2.0 SCO数据包类型的掩码
*/
#define BTM_SCO_SUPPORTED_PKTS_MASK      (HCI_ESCO_PKT_TYPES_MASK_HV1       | \
                                          HCI_ESCO_PKT_TYPES_MASK_HV2       | \
                                          HCI_ESCO_PKT_TYPES_MASK_HV3       | \
                                          HCI_ESCO_PKT_TYPES_MASK_EV3       | \
                                          HCI_ESCO_PKT_TYPES_MASK_EV4       | \
                                          HCI_ESCO_PKT_TYPES_MASK_EV5)

#define BTM_SCO_EXCEPTION_PKTS_MASK      (HCI_ESCO_PKT_TYPES_MASK_NO_2_EV3  | \
                                          HCI_ESCO_PKT_TYPES_MASK_NO_3_EV3  | \
                                          HCI_ESCO_PKT_TYPES_MASK_NO_2_EV5  | \
                                          HCI_ESCO_PKT_TYPES_MASK_NO_3_EV5)


#define BTM_SCO_ROUTE_UNKNOWN       0xff

/* 定义包含（e）SCO数据的结构*/
typedef struct {
    tBTM_ESCO_CBACK    *p_esco_cback;   /* eSCO事件的回调*/
    tBTM_ESCO_PARAMS    setup;
    tBTM_ESCO_DATA      data;           /* 连接完成信息*/
    UINT8               hci_status;
} tBTM_ESCO_INFO;

/* 定义用于SCO管理的结构
*/
typedef struct {
    tBTM_ESCO_INFO   esco;              /* 当前设置*/
#if BTM_SCO_HCI_INCLUDED == TRUE
#define BTM_SCO_XMIT_QUEUE_THRS     30
#define BTM_SCO_XMIT_QUEUE_HIGH_WM  20
    fixed_queue_t   *xmit_data_q;       /* SCO数据传输队列*/
    INT16           sent_not_acked;
#endif
    tBTM_SCO_CB     *p_conn_cb;         /* 连接时的回调*/
    tBTM_SCO_CB     *p_disc_cb;         /* 断开连接时的回调*/
    UINT16           state;             /* 上海合作组织联系状况*/
    UINT16           hci_handle;        /* HCI手柄*/
    BOOLEAN          is_orig;           /* 如果发起人为TRUE*/
    BOOLEAN          rem_bd_known;      /* 如果远程BD地址已知，则为TRUE*/
} tSCO_CONN;

/* SCO管理控制块*/
typedef struct {
    tBTM_SCO_IND_CBACK  *app_sco_ind_cb;
#if BTM_SCO_HCI_INCLUDED == TRUE
    tBTM_SCO_DATA_CB     *p_data_cb;        /* HCI上SCO数据的回调*/
    UINT32               xmit_window_size; /* 总SCO窗口（字节）*/
    UINT16               num_lm_sco_bufs;
#endif
    tSCO_CONN            sco_db[BTM_MAX_SCO_LINKS];
    tBTM_ESCO_PARAMS     def_esco_parms;
    BD_ADDR              xfer_addr;
    UINT16               sco_disc_reason;
    BOOLEAN              esco_supported;    /* 如果1.2 cntlr AND支持eSCO链接，则为TRUE*/
    tBTM_SCO_TYPE        desired_sco_mode;
    tBTM_SCO_TYPE        xfer_sco_type;
    tBTM_SCO_PCM_PARAM   sco_pcm_param;
    tBTM_SCO_CODEC_TYPE  codec_in_use;      /* 无、CVSD、MSBC等。*/
#if BTM_SCO_HCI_INCLUDED == TRUE
    tBTM_SCO_ROUTE_TYPE  sco_path;
#endif

} tSCO_CB;


#if BTM_SCO_INCLUDED == TRUE
void     btm_set_sco_ind_cback( tBTM_SCO_IND_CBACK *sco_ind_cb );
void     btm_accept_sco_link(UINT16 sco_inx, tBTM_ESCO_PARAMS *p_setup,
                             tBTM_SCO_CB *p_conn_cb, tBTM_SCO_CB *p_disc_cb);
void     btm_reject_sco_link(UINT16 sco_inx );
void btm_sco_chk_pend_rolechange (UINT16 hci_handle);
#else
#define btm_accept_sco_link(sco_inx, p_setup, p_conn_cb, p_disc_cb)
#define btm_reject_sco_link(sco_inx)
#define btm_set_sco_ind_cback(sco_ind_cb)
#define btm_sco_chk_pend_rolechange(hci_handle)
#endif  /* BTM_SCO_INCLUDED */

/*
** 定义安全服务记录的结构。在Security Manager中注册的每个服务都有一个记录
*/
#define BTM_SEC_OUT_FLAGS   (BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT | BTM_SEC_OUT_AUTHORIZE)
#define BTM_SEC_IN_FLAGS    (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT | BTM_SEC_IN_AUTHORIZE)

#define BTM_SEC_OUT_LEVEL4_FLAGS   (BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT | \
                                        BTM_SEC_OUT_MITM | BTM_SEC_MODE4_LEVEL4)

#define BTM_SEC_IN_LEVEL4_FLAGS    (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT | \
                                        BTM_SEC_IN_MITM | BTM_SEC_MODE4_LEVEL4)

typedef struct {
    UINT32          mx_proto_id;        /* 服务在此多路复用器协议上运行*/
    UINT32          orig_mx_chan_id;    /* 多路复用器协议上的信道*/
    UINT32          term_mx_chan_id;    /* 多路复用器协议上的信道*/
    UINT16          psm;                /* L2CAP PSM值*/
    UINT16          security_flags;     /* 所需安全功能位图*/
    UINT8           service_id;         /* 传入的授权回调*/
#if (L2CAP_UCD_INCLUDED == TRUE)
    UINT16          ucd_security_flags; /* UCD所需安全功能位图*/
#endif
#if BTM_SEC_SERVICE_NAME_LEN > 0
    UINT8           orig_service_name[BTM_SEC_SERVICE_NAME_LEN + 1];
    UINT8           term_service_name[BTM_SEC_SERVICE_NAME_LEN + 1];
#endif
} tBTM_SEC_SERV_REC;

#if BLE_INCLUDED == TRUE
/* LE从属角色中设备的安全信息*/
typedef struct {
    BT_OCTET16          irk;            /* 对等验证身份根*/
    BT_OCTET16          pltk;           /* 对等长期密钥*/
    BT_OCTET16          pcsrk;          /* 用于对本地数据进行安全签名的对等SRK对等设备*/

    BT_OCTET16          lltk;           /* 本地长期密钥*/
    BT_OCTET16          lcsrk;          /* 用于对本地数据进行安全签名的本地SRK对等设备*/

    BT_OCTET8           rand;           /* LTK生成的随机向量*/
    UINT16              ediv;           /* 此从属设备的LTK分流器*/
    UINT16              div;            /* 本地DIV生成本地LTK＝d1（ER，DIV，0）和CSRK＝d1（ERDIV，1）*/
    UINT8               sec_level;      /* 本地配对安全级别*/
    UINT8               key_size;       /* 传送到对等设备的LTK的密钥大小*/
    UINT8               srk_sec_level;  /* 此设备的对等SRK的安全属性*/
    UINT8               local_csrk_sec_level;  /* 此设备的本地CSRK的安全属性*/

    UINT32              counter;        /* 用于验证rcv签名cmd的对等签名计数器*/
    UINT32              local_counter;  /* 用于发送签名写入命令的本地签名计数器*/
} tBTM_SEC_BLE_KEYS;

typedef struct {
    BD_ADDR pseudo_addr; /* 设备的LE伪地址（如果与设备地址不同）*/
    tBLE_ADDR_TYPE      ble_addr_type;  /* LE设备类型：公共或随机地址*/
    tBLE_ADDR_TYPE      static_addr_type;   /* 静态地址类型*/
    BD_ADDR             static_addr;    /* 静态地址*/

#define BTM_WHITE_LIST_BIT          0x01
#define BTM_RESOLVING_LIST_BIT      0x02
    UINT8               in_controller_list;   /* 是否在控制器解析列表中*/
    UINT8               resolving_list_index;
#if BLE_PRIVACY_SPT == TRUE
    BD_ADDR             cur_rand_addr;  /* 当前随机地址*/

#define BTM_BLE_ADDR_PSEUDO         0   /* 地址索引设备记录*/
#define BTM_BLE_ADDR_RRA            1   /* cur_rand地址*/
#define BTM_BLE_ADDR_STATIC         2   /* 静态地址*/
    UINT8               active_addr_type;
#endif

#if SMP_INCLUDED == TRUE
    tBTM_LE_KEY_TYPE    key_type;       /* 记录中有效密钥类型的位掩码*/
    tBTM_SEC_BLE_KEYS   keys;           /* 从设备中的LE设备安全信息*/
#if (SMP_SLAVE_CON_PARAMS_UPD_ENABLE == TRUE)
    bool skip_update_conn_param;        /* 是否跳过更新连接参数*/
#endif
    UINT16 auth_mode;                   /* 身份验证模式*/
#endif
#if (BLE_PRIVACY_SPT == TRUE && (!CONTROLLER_RPA_LIST_ENABLE))
    tBLE_ADDR_TYPE      current_addr_type; /* 当前adv-addr类型*/
    BD_ADDR             current_addr;      /* 当前adv地址*/
    bool                current_addr_valid; /* 当前地址信息是否有效*/
#endif
} tBTM_SEC_BLE;


#endif  /* BLE_INCLUDED */

/* 剥离粘结类型*/
enum {
    BOND_TYPE_UNKNOWN,
    BOND_TYPE_PERSISTENT,
    BOND_TYPE_TEMPORARY
};
typedef UINT8 tBTM_BOND_TYPE;

/*
** 定义安全设备记录的结构。通过此设备验证的每个设备都有一个记录
*/
struct tBTM_SEC_DEV_REC{
    tBTM_SEC_SERV_REC   *p_cur_service;
    tBTM_SEC_CALLBACK   *p_callback;
    void                *p_ref_data;
    UINT32               timestamp;         /* 上次连接的时间戳*/
    UINT32               trusted_mask[BTM_SEC_SERVICE_ARRAY_SIZE];  /* 可信服务的位OR*/
    UINT16               hci_handle;        /* 连接的句柄（如果存在）*/
    UINT16               clock_offset;      /* 最新已知时钟偏移*/
    BD_ADDR              bd_addr;           /* 设备的BD_ADDR*/
    DEV_CLASS            dev_class;         /* 设备的DEV_CLASS*/
    LINK_KEY             link_key;          /* 设备链接密钥*/
    UINT8                pin_code_length;   /* 用于配对的pin_code的长度*/

#define BTM_SEC_AUTHORIZED      BTM_SEC_FLAG_AUTHORIZED     /* 0x01*/
#define BTM_SEC_AUTHENTICATED   BTM_SEC_FLAG_AUTHENTICATED  /* 0x02*/
#define BTM_SEC_ENCRYPTED       BTM_SEC_FLAG_ENCRYPTED      /* 0x04*/
#define BTM_SEC_NAME_KNOWN      0x08
#define BTM_SEC_LINK_KEY_KNOWN  BTM_SEC_FLAG_LKEY_KNOWN /* 0x10像素*/
#define BTM_SEC_LINK_KEY_AUTHED BTM_SEC_FLAG_LKEY_AUTHED    /* 20倍*/
#define BTM_SEC_ROLE_SWITCHED   0x40
#define BTM_SEC_IN_USE          0x80
    /* LE链路安全标志*/
#define BTM_SEC_LE_AUTHORIZATION   0x0100   /* LE链接已授权*/
#define BTM_SEC_LE_AUTHENTICATED   0x0200   /* LE链路在与MITM配对后加密*/
#define BTM_SEC_LE_ENCRYPTED       0x0400   /* LE链接已加密*/
#define BTM_SEC_LE_NAME_KNOWN      0x0800   /* 未使用*/
#define BTM_SEC_LE_LINK_KEY_KNOWN  0x1000   /* 与对等体绑定（保存对等体LTK和/或SRK）*/
#define BTM_SEC_LE_LINK_KEY_AUTHED 0x2000   /* 配对使用MITM完成*/
#define BTM_SEC_16_DIGIT_PIN_AUTHED 0x4000   /* 配对使用16位引脚完成*/

    UINT16           sec_flags;          /* 当前设备安全状态*/

    tBTM_BD_NAME    sec_bd_name;        /* 设备的用户友好名称。（可以截断以节省dev_rec表中的空间）*/
    BD_FEATURES     features[HCI_EXT_FEATURES_PAGE_MAX + 1];           /* 设备支持的功能*/
    UINT8           num_read_pages;

#define BTM_SEC_STATE_IDLE               0
#define BTM_SEC_STATE_AUTHENTICATING     1
#define BTM_SEC_STATE_ENCRYPTING         2
#define BTM_SEC_STATE_GETTING_NAME       3
#define BTM_SEC_STATE_AUTHORIZING        4
#define BTM_SEC_STATE_SWITCHING_ROLE     5
#define BTM_SEC_STATE_DISCONNECTING      6 /* 断开BR/EDR*/
#define BTM_SEC_STATE_DELAY_FOR_ENC      7 /* 检查加密是否有效的延迟*/
    /* 控制器问题*/
#define BTM_SEC_STATE_DISCONNECTING_BLE  8 /* 断开BLE*/
#define BTM_SEC_STATE_DISCONNECTING_BOTH 9 /* 断开BR/EDR和BLE*/

    UINT8       sec_state;              /* 工作状态*/
    BOOLEAN     is_originator;          /* 如果设备正在发起连接，则为TRUE*/
#if (L2CAP_UCD_INCLUDED == TRUE)
    BOOLEAN     is_ucd;                 /* 如果设备正在发送或接收UCD，则为TRUE*/
    /* 如果传入的安全性失败，则接收到的UCD将被丢弃*/
#endif
    BOOLEAN     role_master;            /* 如果当前模式为主模式，则为TRUE*/
    UINT16      security_required;      /* 连接所需的安全性*/
    BOOLEAN     link_key_not_sent;      /* 尚未发送链接密钥通知，等待名称*/
    UINT8       link_key_type;          /* 配对中使用的密钥类型*/
    BOOLEAN     link_key_changed;       /* 当前连接期间更改了链接密钥*/

#define BTM_MAX_PRE_SM4_LKEY_TYPE   BTM_LKEY_TYPE_REMOTE_UNIT /* 传统配对使用的链接密钥类型*/

#define BTM_SM4_UNKNOWN     0x00
#define BTM_SM4_KNOWN       0x10
#define BTM_SM4_TRUE        0x11
#define BTM_SM4_REQ_PEND    0x08        /* 获取远程功能时设置此位*/
#define BTM_SM4_UPGRADE     0x04        /* 升级链接密钥时设置此位*/
#define BTM_SM4_RETRY       0x02        /* 将此位设置为在HCI_ERR_KEY_MISSING或HCI_ERR_LMP_ERR_TRANS_COLLISION上重试*/
#define BTM_SM4_DD_ACP      0x20        /* 设置此位以指示对等方发起的专用绑定*/
#define BTM_SM4_CONN_PEND   0x40        /* 设置该位以指示接受acl连接；要在btm_acl_created上清除*/
    UINT8       sm4;                    /* BTM_SM4_TRUE，如果对等方支持SM4*/
    tBTM_IO_CAP rmt_io_caps;            /* 对等设备的IO能力*/
    tBTM_AUTH_REQ rmt_auth_req;         /* auth_req标志，如IO caps rsp evt中所示*/
    BOOLEAN     remote_supports_secure_connections;
    BOOLEAN     remote_features_needed; /* 如果本地设备处于*/
    /* “仅安全连接”模式，它接收*/
    /* 之前来自对等方的HCI_IO_CAPABILITY_REQUEST_EVT*/
    /* 它知道对等方对安全连接的支持*/
    BOOLEAN     remote_secure_connection_previous_state;     /* 存储对等方是否支持安全连接。这将有助于了解对等设备何时降级其安全性。*/

    UINT16              ble_hci_handle;         /* 用于DUMO连接*/
    UINT8               enc_key_size;           /* 当前链接加密密钥大小*/
    tBT_DEVICE_TYPE     device_type;
    BOOLEAN             new_encryption_key_is_p256; /* 当从P-256生成新生成的LK时，设置为TRUE。使用此类LK加密的链路可用于BR/EDR上的SM。
                                                    */
    BOOLEAN no_smp_on_br;       /* 如果设置为TRUE，则BR/EDR上的SMP不会*/
    /* 工作，即链接键交叉配对*/
    /* SC BR/EDR->SC LE未发生*/
    tBTM_BOND_TYPE bond_type;   /* 对等键类型*/

#if BLE_INCLUDED == TRUE
    tBTM_SEC_BLE        ble;
    tBTM_LE_CONN_PRAMS  conn_params;
#if (BLE_50_FEATURE_SUPPORT == TRUE)
    tBTM_EXT_CONN_PARAMS ext_conn_params;
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
#endif

// btla特定++
#if BTM_DISC_DURING_RS == TRUE
#define BTM_SEC_RS_NOT_PENDING          0           /* 角色切换未进行*/
#define BTM_SEC_RS_PENDING              1           /* 正在进行角色切换*/
#define BTM_SEC_DISC_PENDING            2           /* 断开连接挂起*/
    UINT8           rs_disc_pending;
#endif
// btla特定--
#define BTM_SEC_NO_LAST_SERVICE_ID      0
    UINT8           last_author_service_id;         /* 上次授权维修的ID：每次l2cap连接后重置*/
    BOOLEAN         enc_init_by_we;
};

#define BTM_SEC_IS_SM4(sm) ((BOOLEAN)(BTM_SM4_TRUE == ((sm)&BTM_SM4_TRUE)))
#define BTM_SEC_IS_SM4_LEGACY(sm) ((BOOLEAN)(BTM_SM4_KNOWN == ((sm)&BTM_SM4_TRUE)))
#define BTM_SEC_IS_SM4_UNKNOWN(sm) ((BOOLEAN)(BTM_SM4_UNKNOWN == ((sm)&BTM_SM4_TRUE)))

#define BTM_SEC_LE_MASK    (BTM_SEC_LE_AUTHENTICATED|BTM_SEC_LE_ENCRYPTED|BTM_SEC_LE_LINK_KEY_KNOWN|BTM_SEC_LE_LINK_KEY_AUTHED)

/*
** 定义设备配置结构
*/
typedef struct {
#if BTM_MAX_LOC_BD_NAME_LEN > 0
    tBTM_LOC_BD_NAME bd_name;                    /* 本地蓝牙设备名称*/
#endif
    BOOLEAN          pin_type;                   /* 如果PIN类型固定，则为TRUE*/
    UINT8            pin_code_len;               /* 担保信息*/
    PIN_CODE         pin_code;                   /* PIN码（如果PIN类型固定）*/
    BOOLEAN          connectable;                /* 如果应启用TRUE页面扫描*/
    UINT8            def_inq_scan_mode;          /* ??? 有限/一般/无*/
} tBTM_CFG;

enum {
    BTM_PM_SET_MODE_EVT,    /* 调用设置电源模式API。*/
    BTM_PM_UPDATE_EVT,
    BTM_PM_RD_MODE_EVT     /* 读取电源模式API被调用。*/
};
typedef UINT8 tBTM_PM_EVENT;

typedef struct {
    UINT16          event;
    UINT16          len;
    UINT8           link_ind;
} tBTM_PM_MSG_DATA;

typedef struct {
    UINT8 hci_status;
    UINT8 mode;
    UINT16 interval;
} tBTM_PM_MD_CHG_DATA;

typedef struct {
    UINT8          pm_id;      /* 调用SetPowerMode API的实体*/
    tBTM_PM_PWR_MD *p_pmd;
} tBTM_PM_SET_MD_DATA;

typedef struct {
    void        *p_data;
    UINT8        link_ind;
} tBTM_PM_SM_DATA;

#define BTM_PM_REC_NOT_USED 0
typedef struct {
    tBTM_PM_STATUS_CBACK *cback;/* 通知注册方模式更改事件*/
    UINT8                 mask; /* 注册的请求掩码。0，如果未使用此条目*/
} tBTM_PM_RCB;

enum {
    BTM_BLI_ACL_UP_EVT,
    BTM_BLI_ACL_DOWN_EVT,
    BTM_BLI_PAGE_EVT,
    BTM_BLI_PAGE_DONE_EVT,
    BTM_BLI_INQ_EVT,
    BTM_BLI_INQ_CANCEL_EVT,
    BTM_BLI_INQ_DONE_EVT
};
typedef UINT8 tBTM_BLI_EVENT;

/* 配对状态*/
enum {
    BTM_PAIR_STATE_IDLE,                        /* 闲置的*/
    BTM_PAIR_STATE_GET_REM_NAME,                /* 获取远程名称（检查SM4）*/
    BTM_PAIR_STATE_WAIT_PIN_REQ,                /* 已开始身份验证，等待PIN请求（PIN已预取）*/
    BTM_PAIR_STATE_WAIT_LOCAL_PIN,              /* 正在等待本地PIN码*/
    BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM,        /* 等待用户“是”进行数字确认*/
    BTM_PAIR_STATE_KEY_ENTRY,                   /* 键输入状态（我们是键盘）*/
    BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP,          /* 等待对对等OOB数据的本地响应*/
    BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS,           /* 等待本地IO功能和OOB数据*/
    BTM_PAIR_STATE_INCOMING_SSP,                /* 传入SSP（空闲时获得对等IO上限）*/
    BTM_PAIR_STATE_WAIT_AUTH_COMPLETE,          /* 全部完成，等待身份验证完成*/
    BTM_PAIR_STATE_WAIT_DISCONNECT              /* 正在等待断开ACL*/
};
typedef UINT8 tBTM_PAIRING_STATE;

#define BTM_PAIR_FLAGS_WE_STARTED_DD    0x01    /* 我们想做专门的粘接*/
#define BTM_PAIR_FLAGS_PEER_STARTED_DD  0x02    /* 对等启动的专用绑定*/
#define BTM_PAIR_FLAGS_DISC_WHEN_DONE   0x04    /* 完成后断开连接*/
#define BTM_PAIR_FLAGS_PIN_REQD         0x08    /* 调用pin_callback时设置此位*/
#define BTM_PAIR_FLAGS_PRE_FETCH_PIN    0x10    /* 预取引脚时设置此位*/
#define BTM_PAIR_FLAGS_REJECTED_CONNECT 0x20    /* 拒绝传入连接时设置此位*/
#define BTM_PAIR_FLAGS_WE_CANCEL_DD     0x40    /* 取消绑定过程时设置此位*/
#define BTM_PAIR_FLAGS_LE_ACTIVE        0x80    /* 当SMP配对处于活动状态时使用此位*/


typedef struct {
    BOOLEAN             is_mux;
    BD_ADDR             bd_addr;
    UINT16              psm;
    BOOLEAN             is_orig;
    tBTM_SEC_CALLBACK   *p_callback;
    void                *p_ref_data;
    UINT32              mx_proto_id;
    UINT32              mx_chan_id;
    tBT_TRANSPORT       transport;
} tBTM_SEC_QUEUE_ENTRY;

#if (L2CAP_UCD_INCLUDED == TRUE)

#define CONN_ORIENT_TERM                0x00    /* 面向传入连接*/
#define CONN_ORIENT_ORIG                0x01    /* 面向输出连接*/
#define CONNLESS_TERM                   0x02    /* 传入无连接*/
#define CONNLESS_ORIG                   0x03    /* 无输出连接*/
#define CONNECTION_TYPE_ORIG_MASK       0x01    /* 方向掩模*/
#define CONNECTION_TYPE_CONNLESS_MASK   0x02    /* 无连接或无连接的掩码*/
typedef UINT8 CONNECTION_TYPE;

#else

#define CONN_ORIENT_TERM                FALSE
#define CONN_ORIENT_ORIG                TRUE
typedef BOOLEAN CONNECTION_TYPE;

#endif /* (L2CAP_UCD_INCLUDED == TRUE) */

/* 定义保存所有BTM数据的结构
*/

#define BTM_STATE_BUFFER_SIZE  5                  /* 状态缓冲区大小*/

#define BTM_INVALID_HANDLE    0xFFFF

typedef struct {
    tBTM_CFG    cfg;                        /* 设备配置*/

    /****************************************************
    **      ACL管理
    ****************************************************/
    list_t      *p_acl_db_list;
#if (CLASSIC_BT_INCLUDED == TRUE)
    UINT8       btm_scn[BTM_MAX_SCN];        /* 当前SCN：如果正在使用SCN，则为TRUE*/
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    UINT16      btm_def_link_policy;
    UINT16      btm_def_link_super_tout;

    tBTM_BL_EVENT_MASK     bl_evt_mask;
    tBTM_BL_CHANGE_CB     *p_bl_changed_cb;    /* 忙碌级别更改时的回调*/

    /****************************************************
    **      电源管理
    ****************************************************/
    list_t      *p_pm_mode_db_list;
    tBTM_PM_RCB pm_reg_db[BTM_MAX_PM_RECORDS + 1]; /* 每个应用程序/模块*/
    UINT16      pm_pend_link_hdl;  /* acl_db的索引，它具有挂起的PM cmd*/
    UINT8       pm_pend_id;        /* 模块的id，该模块具有挂起的PM命令*/

    /*****************************************************
    **      设备控制
    *****************************************************/
    tBTM_DEVCB  devcb;

    /*****************************************************
    **      BLE设备控制器
    *****************************************************/
#if (BLE_INCLUDED == TRUE)
    tBTM_BLE_CB             ble_ctr_cb;

    UINT16                  enc_handle;
    BT_OCTET8               enc_rand;   /* 收到LTK请求的rand值*/
    UINT16                  ediv;       /* 从LTK请求接收到ediv值*/
    UINT8                   key_size;
    tBTM_BLE_VSC_CB         cmn_ble_vsc_cb;
#endif

    /* 本地设备支持的数据包类型*/
    UINT16      btm_acl_pkt_types_supported;
    UINT16      btm_sco_pkt_types_supported;


    /*****************************************************
    **      调查
    *****************************************************/
    tBTM_INQUIRY_VAR_ST     btm_inq_vars;

    /*****************************************************
    **      SCO管理
    *****************************************************/
#if BTM_SCO_INCLUDED == TRUE
    tSCO_CB             sco_cb;
#endif

    /*****************************************************
    **      安全管理
    *****************************************************/
    tBTM_APPL_INFO          api;

#define BTM_SEC_MAX_RMT_NAME_CALLBACKS  2

    tBTM_RMT_NAME_CALLBACK  *p_rmt_name_callback[BTM_SEC_MAX_RMT_NAME_CALLBACKS];
#if (SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC        *p_collided_dev_rec;
#endif  ///SMP_INCLUDED == TRUE
    TIMER_LIST_ENT           sec_collision_tle;
    UINT32                   collision_start_time;
    UINT32                   max_collision_delay;
    UINT32                   dev_rec_count;      /* 用于设备记录时间戳的计数器*/
    UINT8                    security_mode;
    BOOLEAN                  pairing_disabled;
    BOOLEAN                  connect_only_paired;
    BOOLEAN                  security_mode_changed;  /* 接合过程中模式改变*/
    BOOLEAN                  sec_req_pending;       /*   如果请求待定，则为TRUE*/
#if (CLASSIC_BT_INCLUDED == TRUE)
    BOOLEAN                  pin_type_changed;       /* 接合过程中针脚类型发生变化*/
#endif  ///CLASSIC_BT_INCLUDED == TRUE
#if (SMP_INCLUDED == TRUE)
#if (CLASSIC_BT_INCLUDED == TRUE)
// btla特定++
#ifdef PORCHE_PAIRING_CONFLICT
    UINT8                    pin_code_len_saved;     /* 对于传统设备*/
#endif
// btla特定--

    UINT8                    pin_code_len;  /* 对于传统设备*/
    PIN_CODE                 pin_code;      /* 对于传统设备*/
    UINT8                    disc_reason;   /* 对于传统设备*/
    UINT16                   disc_handle;   /* 对于传统设备*/
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    tBTM_PAIRING_STATE       pairing_state; /* 当前配对状态*/
    UINT8                    pairing_flags; /* 当前配对标志*/
    BD_ADDR                  pairing_bda;   /* 当前配对的设备*/
    TIMER_LIST_ENT           pairing_tle;   /* 配对过程计时器*/

#endif  ///SMP_INCLUDED == TRUE
#if SMP_INCLUDED == TRUE || CLASSIC_BT_INCLUDED == TRUE
    tBTM_SEC_SERV_REC        sec_serv_rec[BTM_SEC_MAX_SERVICE_RECORDS];
#endif // SMP_INCLUDED == TRUE || BT_CLASSIC_ENABLED == TRUE
    list_t                  *p_sec_dev_rec_list;
    tBTM_SEC_SERV_REC       *p_out_serv;
    tBTM_MKEY_CALLBACK      *mkey_cback;

    BD_ADDR                  connecting_bda;
    DEV_CLASS                connecting_dc;

    UINT8                   acl_disc_reason;
    UINT8                   trace_level;
    UINT8                   busy_level; /* 当前繁忙级别*/
    BOOLEAN                 is_paging;  /* TRUE，如果正在进行分页*/
    BOOLEAN                 is_inquiry; /* TRUE，如果查询正在进行*/
    fixed_queue_t           *page_queue;
    BOOLEAN                 paging;
    BOOLEAN                 discing;
    fixed_queue_t           *sec_pending_q;  /* tBTM_SEC_QUEUE_ENTRY格式的挂起序列请求*/
#if  (!defined(BT_TRACE_VERBOSE) || (BT_TRACE_VERBOSE == FALSE))
    char state_temp_buffer[BTM_STATE_BUFFER_SIZE];
#endif
} tBTM_CB;

typedef struct{
  //连接参数更新回调
  tBTM_UPDATE_CONN_PARAM_CBACK *update_conn_param_cb;
}tBTM_CallbackFunc;

extern tBTM_CallbackFunc conn_param_update_cb;
/* L2CAP COC信道的安全操作*/
#define BTM_SEC_OK                1
#define BTM_SEC_ENCRYPT           2    /* 使用当前密钥加密链接*/
#define BTM_SEC_ENCRYPT_NO_MITM   3    /* 未经身份验证的加密或更好的加密*/
#define BTM_SEC_ENCRYPT_MITM      4    /* 经过身份验证的加密*/
#define BTM_SEC_ENC_PENDING       5    /* 等待链接加密挂起*/

typedef UINT8 tBTM_SEC_ACTION;

#ifdef __cplusplus
extern "C"
{
#endif

#if BTM_DYNAMIC_MEMORY == FALSE
extern tBTM_CB  btm_cb;
#else
extern tBTM_CB *btm_cb_ptr;
#define btm_cb (*btm_cb_ptr)
#endif

typedef struct tSecDevContext {
#define SEC_DEV_BTDM_BDA 0x01
#define SEC_DEV_BDA      0x02
#define SEC_DEV_HDL      0x03
#define SEC_DEV_ID_ADDR  0x04
    UINT8   type;
    BOOLEAN free_check;
    union {
        BD_ADDR_PTR p_bd_addr;
	UINT16      handle;
    }context;
}tSecDevContext;

/* btm_main.c提供的内部函数
********************************************
*/
void         btm_init (void);
void         btm_free (void);

/* btm_inq.c提供的内部函数
*******************************************
*/
tBTM_STATUS  btm_initiate_rem_name (BD_ADDR remote_bda,
                                    tBTM_INQ_INFO *p_cur,
                                    UINT8 origin, UINT32 timeout,
                                    tBTM_CMPL_CB *p_cb);

void         btm_process_remote_name (BD_ADDR bda, BD_NAME name, UINT16 evt_len,
                                      UINT8 hci_status);
void         btm_inq_rmt_name_failed(void);

/* 查询相关功能*/
void         btm_clr_inq_db (BD_ADDR p_bda);
void         btm_inq_db_init (void);
void         btm_process_inq_results (UINT8 *p, UINT8 inq_res_mode);
void         btm_process_inq_complete (UINT8 status, UINT8 mode);
void         btm_process_cancel_complete(UINT8 status, UINT8 mode);
void         btm_event_filter_complete (UINT8 *p);
void         btm_inq_stop_on_ssp(void);
void         btm_inq_clear_ssp(void);
tINQ_DB_ENT *btm_inq_db_find (BD_ADDR p_bda);
BOOLEAN      btm_inq_find_bdaddr (BD_ADDR p_bda);

BOOLEAN btm_lookup_eir(BD_ADDR_PTR p_rem_addr);

/* btm_acl.c提供的内部函数
********************************************
*/
void         btm_acl_free(void);
void         btm_acl_init (void);
void         btm_acl_created (BD_ADDR bda, DEV_CLASS dc, BD_NAME bdn,
                              UINT16 hci_handle, UINT8 link_role, tBT_TRANSPORT transport);
void         btm_acl_removed (BD_ADDR bda, tBT_TRANSPORT transport);
void         btm_acl_device_down (void);
void         btm_acl_update_busy_level (tBTM_BLI_EVENT event);

void         btm_cont_rswitch (tACL_CONN *p,
                               tBTM_SEC_DEV_REC *p_dev_rec,
                               UINT8 hci_status);

tACL_CONN    *btm_handle_to_acl (UINT16 hci_handle);
void         btm_read_link_policy_complete (UINT8 *p);
void         btm_read_rssi_complete (UINT8 *p);
void         btm_read_tx_power_complete (UINT8 *p, BOOLEAN is_ble);
void         btm_read_link_quality_complete (UINT8 *p);
tBTM_STATUS  btm_set_packet_types (tACL_CONN *p, UINT16 pkt_types);
void         btm_process_clk_off_comp_evt (UINT16 hci_handle, UINT16 clock_offset);
void         btm_acl_role_changed (UINT8 hci_status, BD_ADDR bd_addr, UINT8 new_role);
void         btm_acl_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable);
UINT16       btm_get_acl_disc_reason_code (void);
tBTM_STATUS  btm_remove_acl (BD_ADDR bd_addr, tBT_TRANSPORT transport);
void         btm_read_remote_features_complete (UINT8 *p);
void         btm_read_remote_ext_features_complete (UINT8 *p);
void         btm_read_remote_ext_features_failed (UINT8 status, UINT16 handle);
void         btm_read_remote_version_complete (UINT8 *p);
void         btm_establish_continue (tACL_CONN *p_acl_cb);

// btla特定++
void         btm_acl_chk_peer_pkt_type_support (tACL_CONN *p, UINT16 *p_pkt_type);
// btla特定--
/* 读取可通过当前连接发送的最大数据包*/
UINT16 btm_get_max_packet_size (BD_ADDR addr);
tACL_CONN *btm_bda_to_acl (BD_ADDR bda, tBT_TRANSPORT transport);
BOOLEAN    btm_acl_notif_conn_collision (BD_ADDR bda);

void btm_pm_reset(void);
tBTM_PM_MCB *btm_pm_sm_alloc(void);
void btm_pm_proc_cmd_status(UINT8 status);
void btm_pm_proc_mode_change (UINT8 hci_status, UINT16 hci_handle, UINT8 mode,
                              UINT16 interval);
void btm_pm_proc_ssr_evt (UINT8 *p, UINT16 evt_len);
#if BTM_SCO_INCLUDED == TRUE
void btm_sco_chk_pend_unpark (UINT8 hci_status, UINT16 hci_handle);
#if (BTM_SCO_HCI_INCLUDED == TRUE )
void btm_sco_process_num_bufs (UINT16 num_lm_sco_bufs);
void btm_sco_process_num_completed_pkts (UINT8 *p);
#endif /* (BTM_SCO_HCI_INCLUDED == TRUE ) */
#else
#define btm_sco_chk_pend_unpark(hci_status, hci_handle)
#endif /* BTM_SCO_INCLUDED */
void btm_qos_setup_complete (UINT8 status, UINT16 handle, FLOW_SPEC *p_flow);
void btm_qos_setup_timeout (void *p_tle);


#if (BLE_50_FEATURE_SUPPORT == TRUE)
void btm_create_sync_callback(UINT8 status);
void btm_set_phy_callback(UINT8 status);
void btm_read_phy_callback(uint8_t hci_status, uint16_t conn_handle, uint8_t tx_phy, uint8_t rx_phy);
#endif
/* btm_sco.c提供的内部函数
********************************************
*/
void btm_sco_init (void);
void btm_sco_connected (UINT8 hci_status, BD_ADDR bda, UINT16 hci_handle,
                        tBTM_ESCO_DATA *p_esco_data);
void btm_esco_proc_conn_chg (UINT8 status, UINT16 handle, UINT8 tx_interval,
                             UINT8 retrans_window, UINT16 rx_pkt_len,
                             UINT16 tx_pkt_len);
void btm_sco_conn_req (BD_ADDR bda,  DEV_CLASS dev_class, UINT8 link_type);
void btm_sco_removed (UINT16 hci_handle, UINT8 reason);
void btm_sco_acl_removed (BD_ADDR bda);
void btm_route_sco_data (BT_HDR *p_msg);
BOOLEAN btm_is_sco_active (UINT16 handle);
void btm_remove_sco_links (BD_ADDR bda);
BOOLEAN btm_is_sco_active_by_bdaddr (BD_ADDR remote_bda);

tBTM_SCO_TYPE btm_read_def_esco_mode (tBTM_ESCO_PARAMS *p_parms);
UINT16  btm_find_scb_by_handle (UINT16 handle);
void btm_sco_flush_sco_data(UINT16 sco_inx);

/* btm_devctl.c提供的内部函数
**********************************************
*/
void btm_dev_init (void);
void btm_dev_timeout (TIMER_LIST_ENT *p_tle);
void btm_read_local_name_complete (UINT8 *p, UINT16 evt_len);

#if (BLE_INCLUDED == TRUE)
void btm_ble_add_2_white_list_complete(UINT8 status);
void btm_ble_remove_from_white_list_complete(UINT8 *p, UINT16 evt_len);
void btm_ble_clear_white_list_complete(UINT8 *p, UINT16 evt_len);
BOOLEAN btm_ble_addr_resolvable(BD_ADDR rpa, tBTM_SEC_DEV_REC *p_dev_rec);
tBTM_STATUS btm_ble_read_resolving_list_entry(tBTM_SEC_DEV_REC *p_dev_rec);
BOOLEAN btm_ble_resolving_list_load_dev(tBTM_SEC_DEV_REC *p_dev_rec);
void btm_ble_resolving_list_remove_dev(tBTM_SEC_DEV_REC *p_dev_rec);
#endif  /* BLE_INCLUDED */

/* 供应商特定命令完成evt处理程序*/
void btm_vsc_complete (UINT8 *p, UINT16 cc_opcode, UINT16 evt_len,
                       tBTM_CMPL_CB *p_vsc_cplt_cback);
void btm_inq_db_reset (void);
void btm_vendor_specific_evt (UINT8 *p, UINT8 evt_len);
void btm_delete_stored_link_key_complete (UINT8 *p);
void btm_report_device_status (tBTM_DEV_STATUS status);
void btm_set_afh_channels_complete (UINT8 *p);
void btm_ble_set_channels_complete (UINT8 *p);

/* btm_dev.c提供的内部函数
**********************************************
*/
BOOLEAN btm_dev_support_switch (BD_ADDR bd_addr);

tBTM_SEC_DEV_REC  *btm_sec_alloc_dev (BD_ADDR bd_addr);
void              btm_sec_free_dev (tBTM_SEC_DEV_REC *p_dev_rec, tBT_TRANSPORT transport);
tBTM_SEC_DEV_REC  *btm_find_dev (BD_ADDR bd_addr);
tBTM_SEC_DEV_REC  *btm_find_or_alloc_dev (BD_ADDR bd_addr);
tBTM_SEC_DEV_REC  *btm_find_dev_by_handle (UINT16 handle);
tBTM_BOND_TYPE     btm_get_bond_type_dev(BD_ADDR bd_addr);
BOOLEAN            btm_set_bond_type_dev(BD_ADDR bd_addr,
        tBTM_BOND_TYPE bond_type);
void               btm_sec_dev_init(void);
void               btm_sec_dev_free(void);

/* btm_sec.c提供的内部函数
**********************************************
*/
BOOLEAN btm_dev_support_switch (BD_ADDR bd_addr);
tBTM_STATUS  btm_sec_l2cap_access_req (BD_ADDR bd_addr, UINT16 psm,
                                       UINT16 handle, CONNECTION_TYPE conn_type,
                                       tBTM_SEC_CALLBACK *p_callback, void *p_ref_data);
tBTM_STATUS  btm_sec_mx_access_request (BD_ADDR bd_addr, UINT16 psm, BOOLEAN is_originator,
                                        UINT32 mx_proto_id, UINT32 mx_chan_id,
                                        tBTM_SEC_CALLBACK *p_callback, void *p_ref_data);
void  btm_sec_conn_req (UINT8 *bda, UINT8 *dc);
void btm_create_conn_cancel_complete (UINT8 *p);
void btm_read_linq_tx_power_complete (UINT8 *p);

void  btm_sec_init (UINT8 sec_mode);
void  btm_sec_dev_reset (void);
void  btm_sec_abort_access_req (BD_ADDR bd_addr);
void  btm_sec_auth_complete (UINT16 handle, UINT8 status);
void  btm_sec_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable);
void  btm_sec_connected (UINT8 *bda, UINT16 handle, UINT8 status, UINT8 enc_mode);
tBTM_STATUS btm_sec_disconnect (UINT16 handle, UINT8 reason);
void  btm_sec_disconnected (UINT16 handle, UINT8 reason);
void  btm_sec_rmt_name_request_complete (UINT8 *bd_addr, UINT8 *bd_name, UINT8 status);
void  btm_sec_rmt_host_support_feat_evt (UINT8 *p);
void  btm_io_capabilities_req (UINT8 *p);
void  btm_io_capabilities_rsp (UINT8 *p);
void  btm_proc_sp_req_evt (tBTM_SP_EVT event, UINT8 *p);
void  btm_keypress_notif_evt (UINT8 *p);
void  btm_simple_pair_complete (UINT8 *p);
void  btm_sec_link_key_notification (UINT8 *p_bda, UINT8 *p_link_key, UINT8 key_type);
void  btm_sec_link_key_request (UINT8 *p_bda);
void  btm_sec_pin_code_request (UINT8 *p_bda);
void  btm_sec_update_clock_offset (UINT16 handle, UINT16 clock_offset);
void  btm_sec_dev_rec_cback_event (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 res, BOOLEAN is_le_transport);
void btm_sec_set_peer_sec_caps (tACL_CONN *p_acl_cb, tBTM_SEC_DEV_REC *p_dev_rec);

#if BLE_INCLUDED == TRUE
void  btm_sec_clear_ble_keys (tBTM_SEC_DEV_REC  *p_dev_rec);
BOOLEAN btm_sec_find_bonded_dev (UINT8 start_idx, UINT16 *p_found_handle, tBTM_SEC_DEV_REC **p_rec);
BOOLEAN btm_sec_is_a_bonded_dev (BD_ADDR bda);
void btm_consolidate_dev(tBTM_SEC_DEV_REC *p_target_rec);
BOOLEAN btm_sec_is_le_capable_dev (BD_ADDR bda);
BOOLEAN btm_ble_init_pseudo_addr (tBTM_SEC_DEV_REC *p_dev_rec, BD_ADDR new_pseudo_addr);
extern BOOLEAN btm_ble_start_sec_check(BD_ADDR bd_addr, UINT16 psm, BOOLEAN is_originator,
                            tBTM_SEC_CALLBACK *p_callback, void *p_ref_data);
#endif /* BLE_INCLUDED */

extern tBTM_SEC_SERV_REC *btm_sec_find_first_serv (CONNECTION_TYPE conn_type, UINT16 psm);

tINQ_DB_ENT *btm_inq_db_new (BD_ADDR p_bda);

#if BTM_OOB_INCLUDED == TRUE
void  btm_rem_oob_req (UINT8 *p);
void  btm_read_local_oob_complete (UINT8 *p);
#else
#define btm_rem_oob_req(p)
#define btm_read_local_oob_complete(p)
#endif

void  btm_acl_resubmit_page (void);
void  btm_acl_reset_paging (void);
void  btm_acl_paging (BT_HDR *p, BD_ADDR dest);
UINT8 btm_sec_clr_service_by_psm (UINT16 psm);
void  btm_sec_clr_temp_auth_service (BD_ADDR bda);

void btm_ble_lock_init(void);

void btm_ble_sem_init(void);

void btm_ble_sem_free(void);

void btm_ble_lock_free(void);

void btm_sec_handle_remote_legacy_auth_cmp(UINT16 handle);
void btm_sec_update_legacy_auth_state(tACL_CONN *p_acl_cb, UINT8 legacy_auth_state);
BOOLEAN btm_sec_legacy_authentication_mutual (tBTM_SEC_DEV_REC *p_dev_rec);
BOOLEAN btm_find_sec_dev_in_list (void *p_node_data, void *context);

BOOLEAN btm_sec_dev_authorization(BD_ADDR bd_addr, BOOLEAN authorized);

/*
#ifdef__cplusplus｝#endif
*/

#endif

