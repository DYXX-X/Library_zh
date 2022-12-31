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
 * 这是BTA设备管理器的专用接口文件。
 *
 ******************************************************************************/
#ifndef BTA_DM_INT_H
#define BTA_DM_INT_H

#include "common/bt_target.h"
#include "freertos/semphr.h"
#include "bta/bta_sys.h"
#if (BLE_INCLUDED == TRUE && (defined BTA_GATT_INCLUDED) && (BTA_GATT_INCLUDED == TRUE))
#include "bta/bta_gatt_api.h"
#endif



/*****************************************************************************
**  常量和数据类型
*****************************************************************************/


#define BTA_COPY_DEVICE_CLASS(coddst, codsrc)   {((UINT8 *)(coddst))[0] = ((UINT8 *)(codsrc))[0]; \
                                                 ((UINT8 *)(coddst))[1] = ((UINT8 *)(codsrc))[1];  \
                                                 ((UINT8 *)(coddst))[2] = ((UINT8 *)(codsrc))[2];}


#define BTA_DM_MSG_LEN 50

#define BTA_SERVICE_ID_TO_SERVICE_MASK(id)       (1 << (id))

/* DM事件*/
enum {
    /* 设备管理器本地设备API事件*/
    BTA_DM_API_ENABLE_EVT = BTA_SYS_EVT_START(BTA_ID_DM),
    BTA_DM_API_DISABLE_EVT,
    BTA_DM_API_SET_NAME_EVT,
#if (CLASSIC_BT_INCLUDED == TRUE)
    BTA_DM_API_CONFIG_EIR_EVT,
#endif
    BTA_DM_API_SET_AFH_CHANNELS_EVT,
#if (SDP_INCLUDED == TRUE)
    BTA_DM_API_GET_REMOTE_NAME_EVT,
#endif
    BTA_DM_API_SET_VISIBILITY_EVT,

    BTA_DM_ACL_CHANGE_EVT,
    BTA_DM_API_ADD_DEVICE_EVT,
    BTA_DM_API_REMOVE_ACL_EVT,
#if (SMP_INCLUDED == TRUE)
    /* 安全API事件*/
    BTA_DM_API_BOND_EVT,
    BTA_DM_API_BOND_CANCEL_EVT,
    BTA_DM_API_SET_PIN_TYPE_EVT,
    BTA_DM_API_PIN_REPLY_EVT,
#endif  ///SMP_INCLUDED == TRUE
#if (BTA_DM_PM_INCLUDED == TRUE)
    /* 电源管理器事件*/
    BTA_DM_PM_BTM_STATUS_EVT,
    BTA_DM_PM_TIMER_EVT,
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/
#if (BTA_DM_QOS_INCLUDED == TRUE)
    /* 服务质量集合事件*/
    BTA_DM_API_QOS_SET_EVT,
#endif /* #如果（BTA_DM_QOS_INCLUDED==真）*/
#if (SMP_INCLUDED == TRUE)
    /* 简单配对事件*/
    BTA_DM_API_CONFIRM_EVT,
#if (BT_SSP_INCLUDED == TRUE)
    BTA_DM_API_KEY_REQ_EVT,
#endif ///BT_SSP_INCLUDED == TRUE
    BTA_DM_API_SET_ENCRYPTION_EVT,
#endif  ///SMP_INCLUDED == TRUE
#if (BTM_OOB_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    BTA_DM_API_LOC_OOB_EVT,
    BTA_DM_API_OOB_REPLY_EVT,
    BTA_DM_CI_IO_REQ_EVT,
    BTA_DM_CI_RMT_OOB_EVT,
#endif /* BTM_OOB_INCLUDED */


#if BLE_INCLUDED == TRUE
#if SMP_INCLUDED == TRUE
    BTA_DM_API_ADD_BLEKEY_EVT,
    BTA_DM_API_ADD_BLEDEVICE_EVT,
    BTA_DM_API_BLE_PASSKEY_REPLY_EVT,
    BTA_DM_API_BLE_SET_STATIC_PASSKEY_EVT,
    BTA_DM_API_BLE_CONFIRM_REPLY_EVT,
    BTA_DM_API_BLE_SEC_GRANT_EVT,
#endif  ///SMP_INCLUDED == TRUE
    BTA_DM_API_BLE_SET_BG_CONN_TYPE,
    BTA_DM_API_BLE_CONN_PARAM_EVT,
    BTA_DM_API_BLE_CONN_SCAN_PARAM_EVT,
    BTA_DM_API_BLE_SCAN_PARAM_EVT,
    /*******此事件由Yulong于2016/10/25添加，以支持APP的扫描过滤器设置******/
    BTA_DM_API_BLE_SCAN_FIL_PARAM_EVT,
    BTA_DM_API_BLE_OBSERVE_EVT,
    BTA_DM_API_BLE_SCAN_EVT,
    BTA_DM_API_UPDATE_CONN_PARAM_EVT,
    /*******此事件由Yulong于2016/9/9添加，以支持APP的随机地址设置******/
    BTA_DM_API_SET_RAND_ADDR_EVT,
    BTA_DM_API_CLEAR_RAND_ADDR_EVT,
    /*******2016年10月19日，裕隆公司添加了此事件，以支持停止APP的广告设置******/
    BTA_DM_API_BLE_STOP_ADV_EVT,
#if BLE_PRIVACY_SPT == TRUE
    BTA_DM_API_LOCAL_PRIVACY_EVT,
#endif
    BTA_DM_API_LOCAL_ICON_EVT,
    BTA_DM_API_BLE_ADV_PARAM_EVT,

    /*******此事件由裕隆于2016/10/20添加，以支持通过APP设置ble广告参数******/
    BTA_DM_API_BLE_ADV_PARAM_All_EVT,
    BTA_DM_API_BLE_SET_ADV_CONFIG_EVT,
    /* 添加以设置原始广告数据*/
    BTA_DM_API_BLE_SET_ADV_CONFIG_RAW_EVT,
    BTA_DM_API_BLE_SET_SCAN_RSP_EVT,
    /* 添加以设置原始扫描响应数据*/
    BTA_DM_API_BLE_SET_SCAN_RSP_RAW_EVT,
    BTA_DM_API_BLE_BROADCAST_EVT,
    BTA_DM_API_SET_DATA_LENGTH_EVT,
    BTA_DM_API_BLE_SET_LONG_ADV_EVT,
#if BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    BTA_DM_API_CFG_FILTER_COND_EVT,
    BTA_DM_API_SCAN_FILTER_SETUP_EVT,
    BTA_DM_API_SCAN_FILTER_ENABLE_EVT,
#endif
    BTA_DM_API_BLE_MULTI_ADV_ENB_EVT,
    BTA_DM_API_BLE_MULTI_ADV_PARAM_UPD_EVT,
    BTA_DM_API_BLE_MULTI_ADV_DATA_EVT,
    BTA_DM_API_BLE_MULTI_ADV_DISABLE_EVT,
    BTA_DM_API_BLE_SETUP_STORAGE_EVT,
    BTA_DM_API_BLE_ENABLE_BATCH_SCAN_EVT,
    BTA_DM_API_BLE_DISABLE_BATCH_SCAN_EVT,
    BTA_DM_API_BLE_READ_SCAN_REPORTS_EVT,
    BTA_DM_API_BLE_TRACK_ADVERTISER_EVT,
    BTA_DM_API_BLE_ENERGY_INFO_EVT,
    BTA_DM_API_BLE_DISCONNECT_EVT,

#endif

    BTA_DM_API_ENABLE_TEST_MODE_EVT,
    BTA_DM_API_DISABLE_TEST_MODE_EVT,
    BTA_DM_API_EXECUTE_CBACK_EVT,
    BTA_DM_API_REMOVE_ALL_ACL_EVT,
    BTA_DM_API_REMOVE_DEVICE_EVT,
    BTA_DM_API_BLE_SET_CHANNELS_EVT,
    BTA_DM_API_UPDATE_WHITE_LIST_EVT,
    BTA_DM_API_CLEAR_WHITE_LIST_EVT,
    BTA_DM_API_BLE_READ_ADV_TX_POWER_EVT,
    BTA_DM_API_READ_RSSI_EVT,
#if BLE_INCLUDED == TRUE
    BTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_EVT,
#endif
#if (BLE_50_FEATURE_SUPPORT == TRUE)
    BTA_DM_API_READ_PHY_EVT,
    BTA_DM_API_SET_PER_DEF_PHY_EVT,
    BTA_DM_API_SET_PER_PHY_EVT,
    BTA_DM_API_SET_EXT_ADV_RAND_ADDR_EVT,
    BTA_DM_API_SET_EXT_ADV_PARAMS_EVT,
    BTA_DM_API_CFG_ADV_DATA_RAW_EVT,
    BTA_DM_API_EXT_ADV_ENABLE_EVT,
    BTA_DM_API_EXT_ADV_SET_REMOVE_EVT,
    BTA_DM_API_EXT_ADV_SET_CLEAR_EVT,
    BTA_DM_API_PERIODIC_ADV_SET_PARAMS_EVT,
    BTA_DM_API_PERIODIC_ADV_CFG_DATA_EVT,
    BTA_DM_API_PERIODIC_ADV_ENABLE_EVT,
    BTA_DM_API_PERIODIC_ADV_SYNC_EVT,
    BTA_DM_API_PERIODIC_ADV_SYNC_CANCEL_EVT,
    BTA_DM_API_PERIODIC_ADV_SYNC_TERMINATE_EVT,
    BTA_DM_API_PERIODIC_ADV_ADD_DEV_TO_LSIT_EVT,
    BTA_DM_API_PERIODIC_ADV_REMOVE_DEV_FROM_LSIT_EVT,
    BTA_DM_API_PERIODIC_ADV_CLEAR_DEV_EVT,
    BTA_DM_API_SET_EXT_SCAN_PARAMS_EVT,
    BTA_DM_API_START_EXT_SCAN_EVT,
    BTA_DM_API_SET_PERF_EXT_CONN_PARAMS_EVT,
    BTA_DM_API_EXT_CONN_EVT,
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
    BTA_DM_MAX_EVT
};


/* DM搜索事件*/
enum {
    /* DM搜索API事件*/
    BTA_DM_API_SEARCH_EVT = BTA_SYS_EVT_START(BTA_ID_DM_SEARCH),
    BTA_DM_API_SEARCH_CANCEL_EVT,
    BTA_DM_API_DISCOVER_EVT,
    BTA_DM_INQUIRY_CMPL_EVT,
    BTA_DM_REMT_NAME_EVT,
    BTA_DM_SDP_RESULT_EVT,
    BTA_DM_SEARCH_CMPL_EVT,
    BTA_DM_DISCOVERY_RESULT_EVT,
    BTA_DM_API_DI_DISCOVER_EVT,
    BTA_DM_DISC_CLOSE_TOUT_EVT,
};

/* BTA_DM_API_ENABLE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_DM_SEC_CBACK *p_sec_cback;
} tBTA_DM_API_ENABLE;

/* BTA_DM_API_SET_NAME_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_NAME             name; /* 最大248字节的名称，加号必须以Null结尾*/
} tBTA_DM_API_SET_NAME;

/* BTA_DM_API_CONFIG_EIR_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BOOLEAN             eir_fec_required;
    BOOLEAN             eir_included_tx_power;
    BOOLEAN             eir_included_uuid;
    UINT8               eir_flags;
    UINT8               eir_manufac_spec_len;
    UINT8               *eir_manufac_spec;
    UINT8               eir_url_len;
    UINT8               *eir_url;
    UINT8               data[];
}tBTA_DM_API_CONFIG_EIR;

/* BTA_DM_API_SET_AFH_CHANNELS_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    AFH_CHANNELS        channels;
    tBTA_CMPL_CB        *set_afh_cb;
}tBTA_DM_API_SET_AFH_CHANNELS;

/* BTA_DM_API_GET_REMOTE_NAME_EVT的数据类型*/
typedef struct {
    BT_HDR         hdr;
    BD_ADDR        rmt_addr;
    BD_NAME        rmt_name;
    tBTA_TRANSPORT transport;
    tBTA_CMPL_CB   *rmt_name_cb;
} tBTA_DM_API_GET_REMOTE_NAME;

#if (BLE_INCLUDED == TRUE)
/* BTA_DM_API_BLE_SET_CHANNELS_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    AFH_CHANNELS        channels;
    tBTA_CMPL_CB        *set_channels_cb;
}tBTA_DM_API_BLE_SET_CHANNELS;

typedef struct {
    BT_HDR    hdr;
    BOOLEAN   add_remove;
    BD_ADDR   remote_addr;
    tBLE_ADDR_TYPE addr_type;
    tBTA_ADD_WHITELIST_CBACK *add_wl_cb;
}tBTA_DM_API_UPDATE_WHITE_LIST;

typedef struct {
    BT_HDR    hdr;
    UINT8     subcode;
    UINT32    type;
    BD_ADDR   device_info;
    tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK *exceptional_list_cb;
}tBTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST;

typedef struct {
    BT_HDR       hdr;
    tBTA_CMPL_CB *read_tx_power_cb;
}tBTA_DM_API_READ_ADV_TX_POWER;
#endif  ///BLE_INCLUDED == TRUE

typedef struct {
    BT_HDR        hdr;
    BD_ADDR       remote_addr;
    tBTA_TRANSPORT  transport;
    tBTA_CMPL_CB  *read_rssi_cb;
}tBTA_DM_API_READ_RSSI;

/* BTA_DM_API_SET_VISIBILITY_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    tBTA_DM_DISC    disc_mode;
    tBTA_DM_CONN    conn_mode;
    UINT8           pair_mode;
    UINT8           conn_paired_only;
} tBTA_DM_API_SET_VISIBILITY;

enum {
    BTA_DM_RS_NONE,     /* 直接API调用*/
    BTA_DM_RS_OK,       /* 角色切换结果-成功*/
    BTA_DM_RS_FAIL      /* 角色切换结果-失败*/
};
typedef UINT8 tBTA_DM_RS_RES;

/* BTA_DM_API_SEARCH_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    tBTA_DM_INQ inq_params;
    tBTA_SERVICE_MASK services;
    tBTA_DM_SEARCH_CBACK *p_cback;
    tBTA_DM_RS_RES  rs_res;
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    UINT8           num_uuid;
    tBT_UUID        *p_uuid;
#endif
} tBTA_DM_API_SEARCH;

#if (SDP_INCLUDED == TRUE)
/* BTA_DM_API_DISCOVER_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    tBTA_SERVICE_MASK services;
    tBTA_DM_SEARCH_CBACK *p_cback;
    BOOLEAN         sdp_search;
    tBTA_TRANSPORT  transport;
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    UINT8           num_uuid;
    tBT_UUID        *p_uuid;
#endif
    tSDP_UUID    uuid;
} tBTA_DM_API_DISCOVER;
#endif  ///SDP_INCLUDED == TRUE

/* BTA_DM_API_DI_DISC_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
#if (SDP_INCLUDED == TRUE)
    tBTA_DISCOVERY_DB   *p_sdp_db;
#endif  ///SDP_INCLUDED == TRUE
    UINT32              len;
    tBTA_DM_SEARCH_CBACK *p_cback;
} tBTA_DM_API_DI_DISC;

/* BTA_DM_API_BOND_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    tBTA_TRANSPORT transport;
} tBTA_DM_API_BOND;

/* BTA_DM_API_BOND_CANCEL_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tBTA_TRANSPORT  transport;
} tBTA_DM_API_BOND_CANCEL;

/* BTA_DM_API_SET_PIN_type_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    UINT8       pin_type;
    UINT8       pin_len;
    UINT8       p_pin[PIN_CODE_LEN];
} tBTA_DM_API_SET_PIN_TYPE;

/* BTA_DM_API_PIN_REPLY_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    BOOLEAN accept;
    UINT8 pin_len;
    UINT8 p_pin[PIN_CODE_LEN];
} tBTA_DM_API_PIN_REPLY;

/* BTA_DM_API_LOC_OOB_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
} tBTA_DM_API_LOC_OOB;

/* BTA_DM_API_OOB_REPLY_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    UINT8       len;
    UINT8       value[BT_OCTET16_LEN];
} tBTA_DM_API_OOB_REPLY;

/* BTA_DM_API_CONFIRM_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    BOOLEAN     accept;
} tBTA_DM_API_CONFIRM;

/* BTA_DM_API_KEY_REQ_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    BOOLEAN     accept;
    UINT32      passkey;
} tBTA_DM_API_KEY_REQ;

/* BTA_DM_CI_IO_REQ_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tBTA_IO_CAP     io_cap;
    tBTA_OOB_DATA   oob_data;
    tBTA_AUTH_REQ   auth_req;
} tBTA_DM_CI_IO_REQ;

/* BTA_DM_CI_RMT_OOB_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    BT_OCTET16  c;
    BT_OCTET16  r;
    BOOLEAN     accept;
} tBTA_DM_CI_RMT_OOB;

/* BTA_DM_REMT_NAME_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    tBTA_DM_SEARCH  result;
} tBTA_DM_REM_NAME;

/* tBTA_DM_DISC_RESULT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    tBTA_DM_SEARCH  result;
} tBTA_DM_DISC_RESULT;


/* BTA_DM_INQUIRY_MPL_VT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    UINT8       num;
} tBTA_DM_INQUIRY_CMPL;

/* BTA_DM_SDP_RESULT_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    UINT16 sdp_result;
} tBTA_DM_SDP_RESULT;

/* BTA_DM_ACL_CHANGE_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    tBTM_BL_EVENT   event;
    UINT8           busy_level;
    UINT8           busy_level_flags;
    BOOLEAN         is_new;
    UINT8           new_role;
    BD_ADDR         bd_addr;
    UINT8           hci_status;
    BOOLEAN         sc_downgrade;
#if BLE_INCLUDED == TRUE
    UINT16          handle;
#endif
    tBT_TRANSPORT   transport;
} tBTA_DM_ACL_CHANGE;

#if (BTA_DM_PM_INCLUDED == TRUE)
/* BTA_DM_PM_BTM_STATUS_EVT的数据类型*/
typedef struct {

    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tBTM_PM_STATUS  status;
    UINT16          value;
    UINT8           hci_status;

} tBTA_DM_PM_BTM_STATUS;

/* BTA_DM_PM_TIMER_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tBTA_DM_PM_ACTION  pm_request;
} tBTA_DM_PM_TIMER;
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/

#if (BTA_DM_QOS_INCLUDED == TRUE)
/* BTA_DM_API_QOS_SET_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    UINT32          t_poll;
    tBTM_CMPL_CB    *p_cb;
} tBTA_DM_API_QOS_SET;
#endif /* #如果（BTA_DM_QOS_INCLUDED==真）*/

/* BTA_DM_API_ADD_DEVICE_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    DEV_CLASS           dc;
    LINK_KEY            link_key;
    tBTA_SERVICE_MASK   tm;
    BOOLEAN             is_trusted;
    UINT8               key_type;
    tBTA_IO_CAP         io_cap;
    BOOLEAN             link_key_known;
    BOOLEAN             dc_known;
    BD_NAME             bd_name;
    UINT8               features[BTA_FEATURE_BYTES_PER_PAGE * (BTA_EXT_FEATURES_PAGE_MAX + 1)];
    UINT8               pin_length;
    UINT8               sc_support;
} tBTA_DM_API_ADD_DEVICE;

/* BTA_DM_API_REMOVE_CL_EVT的数据类型*/
typedef struct {
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    UINT8               transport;
} tBTA_DM_API_REMOVE_DEVICE;

/* BTA_DM_API_EXECUTE_CBACK_EVT的数据类型*/
typedef struct {
    BT_HDR               hdr;
    void                *p_param;
    tBTA_DM_EXEC_CBACK  *p_exec_cback;
} tBTA_DM_API_EXECUTE_CBACK;

/* tBTA_DM_API_SET_ENCRYPTION的数据类型*/
typedef struct {
    BT_HDR                    hdr;
    tBTA_TRANSPORT            transport;
    tBTA_DM_ENCRYPT_CBACK     *p_callback;
    tBTA_DM_BLE_SEC_ACT       sec_act;
    BD_ADDR                   bd_addr;
} tBTA_DM_API_SET_ENCRYPTION;

#if BLE_INCLUDED == TRUE
typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    tBTA_LE_KEY_VALUE       blekey;
    tBTA_LE_KEY_TYPE        key_type;

} tBTA_DM_API_ADD_BLEKEY;

typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    tBT_DEVICE_TYPE         dev_type ;
    UINT32                  auth_mode;
    tBLE_ADDR_TYPE          addr_type;

} tBTA_DM_API_ADD_BLE_DEVICE;

typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    BOOLEAN                 accept;
    UINT32                  passkey;
} tBTA_DM_API_PASSKEY_REPLY;

typedef struct {
    BT_HDR                  hdr;
    BOOLEAN                 add;
    UINT32                  static_passkey;
} tBTA_DM_API_SET_DEFAULT_PASSKEY;

typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    tBTA_DM_BLE_SEC_GRANT   res;
} tBTA_DM_API_BLE_SEC_GRANT;


typedef struct {
    BT_HDR                  hdr;
    tBTA_DM_BLE_CONN_TYPE   bg_conn_type;
    tBTA_DM_BLE_SEL_CBACK   *p_select_cback;
} tBTA_DM_API_BLE_SET_BG_CONN_TYPE;

/* 为设备设置首选BLE连接参数*/
typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 peer_bda;
    UINT16                  conn_int_min;
    UINT16                  conn_int_max;
    UINT16                  supervision_tout;
    UINT16                  slave_latency;

} tBTA_DM_API_BLE_CONN_PARAMS;

typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 peer_bda;
    BOOLEAN                 privacy_enable;

} tBTA_DM_API_ENABLE_PRIVACY;

typedef struct {
    BT_HDR                  hdr;
    BOOLEAN                 privacy_enable;
    tBTA_SET_LOCAL_PRIVACY_CBACK *set_local_privacy_cback;
} tBTA_DM_API_LOCAL_PRIVACY;

typedef struct {
    BT_HDR                  hdr;
    uint16_t                icon;
} tBTA_DM_API_LOCAL_ICON;

/* 设置BLE连接的扫描参数*/
typedef struct {
    BT_HDR hdr;
    tBTA_GATTC_IF client_if;
    UINT32 scan_int;
    UINT32 scan_window;
    tBLE_SCAN_MODE scan_mode;
    tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_cback;
} tBTA_DM_API_BLE_SCAN_PARAMS;

typedef struct {
    BT_HDR hdr;
    tBTA_GATTC_IF client_if;
    UINT32 scan_int;
    UINT32 scan_window;
    tBLE_SCAN_MODE scan_mode;
    UINT8 addr_type_own;
    UINT8 scan_duplicate_filter;
    UINT8 scan_filter_policy;
    tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_cback;
} tBTA_DM_API_BLE_SCAN_FILTER_PARAMS;


/* 设置BLE连接的扫描参数*/
typedef struct {
    BT_HDR                  hdr;
    UINT16                  scan_int;
    UINT16                  scan_window;
} tBTA_DM_API_BLE_CONN_SCAN_PARAMS;

/* 启动/停止观察的数据类型*/
typedef struct {
    BT_HDR                  hdr;
    BOOLEAN                 start;
    UINT32                  duration;
    tBTA_DM_SEARCH_CBACK    *p_cback;
    tBTA_START_STOP_SCAN_CMPL_CBACK *p_start_scan_cback;
    tBTA_START_STOP_SCAN_CMPL_CBACK *p_stop_scan_cback;
    tBTA_START_STOP_ADV_CMPL_CBACK  *p_stop_adv_cback;
} tBTA_DM_API_BLE_OBSERVE;

/* 开始/停止扫描的数据类型*/
typedef struct {
    BT_HDR                  hdr;
    BOOLEAN                 start;
    UINT32                  duration;
    tBTA_DM_SEARCH_CBACK    *p_cback;
    tBTA_START_STOP_SCAN_CMPL_CBACK *p_start_scan_cback;
    tBTA_START_STOP_SCAN_CMPL_CBACK *p_stop_scan_cback;
    tBTA_START_STOP_ADV_CMPL_CBACK  *p_stop_adv_cback;
} tBTA_DM_API_BLE_SCAN;

typedef struct {
    BT_HDR      hdr;
    BD_ADDR     remote_bda;
    UINT16      tx_data_length;
    tBTA_SET_PKT_DATA_LENGTH_CBACK *p_set_pkt_data_cback;
} tBTA_DM_API_BLE_SET_DATA_LENGTH;

/* 设置玉龙在2016/9/9添加的BLE设备的地址*/
typedef struct {
    BT_HDR      hdr;
    tBLE_ADDR_TYPE addr_type;
    BD_ADDR address;
    tBTA_SET_RAND_ADDR_CBACK *p_set_rand_addr_cback;
} tBTA_DM_APT_SET_DEV_ADDR;

typedef struct {
    BT_HDR      hdr;
} tBTA_DM_APT_CLEAR_ADDR;

/* 设置BLE广告的adv参数*/
typedef struct {
    BT_HDR                  hdr;
    UINT16                  adv_int_min;
    UINT16                  adv_int_max;
    tBLE_BD_ADDR            *p_dir_bda;
} tBTA_DM_API_BLE_ADV_PARAMS;

/* 设置BLE广告的adv参数*/
typedef struct {
    BT_HDR                  hdr;
    UINT16                  adv_int_min;
    UINT16                  adv_int_max;
    UINT8                   adv_type;
    tBLE_ADDR_TYPE          addr_type_own;
    tBTM_BLE_ADV_CHNL_MAP   channel_map;
    tBTM_BLE_AFP            adv_filter_policy;
    tBLE_BD_ADDR            *p_dir_bda;
    tBTA_START_ADV_CMPL_CBACK  *p_start_adv_cback;
} tBTA_DM_API_BLE_ADV_PARAMS_ALL;


typedef struct {
    BT_HDR                  hdr;
    BOOLEAN                 enable;

} tBTA_DM_API_BLE_FEATURE;

/* 多adv数据结构*/
typedef struct {
    BT_HDR                      hdr;
    tBTA_BLE_MULTI_ADV_CBACK    *p_cback;
    void                        *p_ref;
    tBTA_BLE_ADV_PARAMS         *p_params;
} tBTA_DM_API_BLE_MULTI_ADV_ENB;

typedef struct {
    BT_HDR                      hdr;
    UINT8                        inst_id;
    tBTA_BLE_ADV_PARAMS         *p_params;
} tBTA_DM_API_BLE_MULTI_ADV_PARAM;

typedef struct {
    BT_HDR                  hdr;
    UINT8                   inst_id;
    BOOLEAN                 is_scan_rsp;
    tBTA_BLE_AD_MASK        data_mask;
    tBTA_BLE_ADV_DATA      *p_data;
} tBTA_DM_API_BLE_MULTI_ADV_DATA;

typedef struct {
    BT_HDR                  hdr;
    UINT8                   inst_id;
} tBTA_DM_API_BLE_MULTI_ADV_DISABLE;

typedef struct {
    BT_HDR                  hdr;
    UINT32                  data_mask;
    tBTA_BLE_ADV_DATA       *p_adv_cfg;
    tBTA_SET_ADV_DATA_CMPL_CBACK    *p_adv_data_cback;
} tBTA_DM_API_SET_ADV_CONFIG;

/* 原始扫描响应和原始广告数据使用相同的结构*/
typedef struct {
    BT_HDR                  hdr;
    UINT8                   *p_raw_adv;
    UINT32                  raw_adv_len;
    tBTA_SET_ADV_DATA_CMPL_CBACK    *p_adv_data_cback;
} tBTA_DM_API_SET_ADV_CONFIG_RAW;

typedef struct {
    BT_HDR                  hdr;
    UINT8                   *adv_data;
    UINT8                   adv_data_len;
    tBTA_SET_ADV_DATA_CMPL_CBACK    *p_adv_data_cback;
} tBTA_DM_API_SET_LONG_ADV;

typedef struct {
    BT_HDR                  hdr;
    UINT8                   batch_scan_full_max;
    UINT8                   batch_scan_trunc_max;
    UINT8                   batch_scan_notify_threshold;
    tBTA_BLE_SCAN_SETUP_CBACK *p_setup_cback;
    tBTA_BLE_SCAN_THRESHOLD_CBACK *p_thres_cback;
    tBTA_BLE_SCAN_REP_CBACK *p_read_rep_cback;
    tBTA_DM_BLE_REF_VALUE    ref_value;
} tBTA_DM_API_SET_STORAGE_CONFIG;

typedef struct {
    BT_HDR                  hdr;
    tBTA_BLE_BATCH_SCAN_MODE  scan_mode;
    UINT32                  scan_int;
    UINT32                  scan_window;
    tBTA_BLE_DISCARD_RULE   discard_rule;
    tBLE_ADDR_TYPE          addr_type;
    tBTA_DM_BLE_REF_VALUE   ref_value;
} tBTA_DM_API_ENABLE_SCAN;

typedef struct {
    BT_HDR                  hdr;
    tBTA_DM_BLE_REF_VALUE    ref_value;
} tBTA_DM_API_DISABLE_SCAN;

typedef struct {
    BT_HDR                  hdr;
    tBTA_BLE_BATCH_SCAN_MODE scan_type;
    tBTA_DM_BLE_REF_VALUE    ref_value;
} tBTA_DM_API_READ_SCAN_REPORTS;

typedef struct {
    BT_HDR                  hdr;
    tBTA_DM_BLE_REF_VALUE ref_value;
    tBTA_BLE_TRACK_ADV_CBACK *p_track_adv_cback;
} tBTA_DM_API_TRACK_ADVERTISER;

typedef struct {
    BT_HDR                  hdr;
    tBTA_BLE_ENERGY_INFO_CBACK *p_energy_info_cback;
} tBTA_DM_API_ENERGY_INFO;

typedef struct {
    BT_HDR      hdr;
    BD_ADDR     remote_bda;
} tBTA_DM_API_BLE_DISCONNECT;

#endif /* BLE_INCLUDED */

/* BTA_DM_API_REMOVE_CL_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    BOOLEAN     remove_dev;
    tBTA_TRANSPORT transport;

} tBTA_DM_API_REMOVE_ACL;

/* BTA_DM_API_REMOVE_ALL_ACL_EVT的数据类型*/
typedef struct {
    BT_HDR      hdr;
    tBTA_DM_LINK_TYPE link_type;

} tBTA_DM_API_REMOVE_ALL_ACL;
typedef struct {
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    UINT16      min_int;
    UINT16      max_int;
    UINT16      latency;
    UINT16      timeout;
} tBTA_DM_API_UPDATE_CONN_PARAM;

#if BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
typedef struct {
    BT_HDR                          hdr;
    tBTA_DM_BLE_SCAN_COND_OP        action;
    tBTA_DM_BLE_PF_COND_TYPE        cond_type;
    tBTA_DM_BLE_PF_FILT_INDEX       filt_index;
    tBTA_DM_BLE_PF_COND_PARAM       *p_cond_param;
    tBTA_DM_BLE_PF_CFG_CBACK      *p_filt_cfg_cback;
    tBTA_DM_BLE_REF_VALUE            ref_value;
} tBTA_DM_API_CFG_FILTER_COND;

typedef struct {
    BT_HDR                          hdr;
    UINT8                           action;
    tBTA_DM_BLE_PF_STATUS_CBACK    *p_filt_status_cback;
    tBTA_DM_BLE_REF_VALUE            ref_value;
} tBTA_DM_API_ENABLE_SCAN_FILTER;

typedef struct {
    BT_HDR                          hdr;
    UINT8                           action;
    tBTA_DM_BLE_PF_FILT_INDEX       filt_index;
    tBTA_DM_BLE_PF_FILT_PARAMS      filt_params;
    tBLE_BD_ADDR                    *p_target;
    tBTA_DM_BLE_PF_PARAM_CBACK      *p_filt_param_cback;
    tBTA_DM_BLE_REF_VALUE            ref_value;
} tBTA_DM_API_SCAN_FILTER_PARAM_SETUP;
#endif
#if (BLE_50_FEATURE_SUPPORT == TRUE)

#define BTA_PHY_1M_MASK                   (1 << 0)
#define BTA_PHY_2M_MASK                   (1 << 1)
#define BTAS_PHY_CODED_MASK               (1 << 2)
typedef struct {
    BT_HDR                          hdr;
    BD_ADDR                         bd_addr;
} tBTA_DM_API_READ_PHY;

typedef struct {
    BT_HDR                          hdr;
    tBTA_DM_BLE_GAP_PHY_MASK        tx_phy_mask;
    tBTA_DM_BLE_GAP_PHY_MASK        rx_phy_mask;
} tBTA_DM_API_SET_PER_DEF_PHY;

typedef struct {
    BT_HDR                          hdr;
    BD_ADDR                         bd_addr;
    UINT8                           all_phys;
    tBTA_DM_BLE_GAP_PHY_MASK        tx_phy_mask;
    tBTA_DM_BLE_GAP_PHY_MASK        rx_phy_mask;
    UINT16                          phy_options;
} tBTA_DM_API_SET_PER_PHY;

typedef struct {
    BT_HDR                          hdr;
    UINT16                          instance;
    BD_ADDR                         rand_addr;
} tBTA_DM_API_EXT_ADV_SET_RAND_ADDR;

typedef struct {
    BT_HDR                          hdr;
    UINT16                          instance;
    tBTA_DM_BLE_GAP_EXT_ADV_PARAMS  params;
} tBTA_DM_API_EXT_ADV_SET_PARAMS;

typedef struct {
    BT_HDR                          hdr;
    BOOLEAN                         is_scan_rsp;
    UINT8                           instance;
    UINT16                          length;
    UINT8                           *data;
} tBTA_DM_API_CFG_EXT_ADV_DATA;

typedef struct {
    BT_HDR                         hdr;
    BOOLEAN                        enable;
    UINT8                          num;
    tBTA_DM_BLE_EXT_ADV            *ext_adv;
} tBTA_DM_API_BLE_EXT_ADV;

typedef struct {
    BT_HDR                         hdr;
    UINT16                         instance;
} tBTA_DM_API_BLE_EXT_ADV_SET_REMOVE;

typedef struct {
    BT_HDR                         hdr;
} tBTA_DM_API_BLE_EXT_ADV_SET_CLEAR;

typedef struct {
    BT_HDR                         hdr;
    UINT8                          instance;
    tBTA_DM_BLE_Periodic_Adv_Params params;
} tBTA_DM_API_BLE_PERIODIC_ADV_SET_PARAMS;

typedef struct {
    BT_HDR                          hdr;
    UINT8                           instance;
    UINT16                          length;
    UINT8                           *data;
} tBTA_DM_API_CFG_PERIODIC_ADV_DATA;

typedef struct {
    BT_HDR                          hdr;
    UINT8                           instance;
    BOOLEAN                         enable;
} tBTA_DM_API_ENABLE_PERIODIC_ADV;

typedef struct {
    BT_HDR                          hdr;
    tBTA_DM_BLE_Periodic_Sync_Params params;
} tBTA_DM_API_PERIODIC_ADV_SYNC;

typedef struct {
    BT_HDR                          hdr;
} tBTA_DM_API_PERIODIC_ADV_SYNC_CANCEL;

typedef struct {
    BT_HDR                          hdr;
    UINT16                          sync_handle;
} tBTA_DM_API_PERIODIC_ADV_SYNC_TERM;

typedef struct {
    BT_HDR                          hdr;
    tBLE_ADDR_TYPE                  addr_type;
    BD_ADDR                         addr;
    UINT16                          sid;
} tBTA_DM_API_PERIODIC_ADV_ADD_DEV_TO_LIST;

typedef struct {
    BT_HDR                          hdr;
    tBLE_ADDR_TYPE                  addr_type;
    BD_ADDR                         addr;
    UINT16                          sid;
} tBTA_DM_API_PERIODIC_ADV_REMOVE_DEV_FROM_LIST;

typedef struct {
    BT_HDR                          hdr;
} tBTA_DM_API_PERIODIC_ADV_DEV_CLEAR;


typedef struct {
    BT_HDR                          hdr;
    tBTA_DM_BLE_EXT_SCAN_PARAMS     params;
} tBTA_DM_API_SET_EXT_SCAN_PARAMS;

typedef struct {
    BT_HDR                          hdr;
    BOOLEAN                         start;
    UINT32                          duration;
    UINT16                          period;
} tBTA_DM_API_EXT_SCAN;

typedef struct {
    BT_HDR                          hdr;
    BD_ADDR                         bd_addr;
    UINT8                           phy_mask;
    tBTA_DM_BLE_CONN_PARAMS         phy_1m_conn_params;
    tBTA_DM_BLE_CONN_PARAMS         phy_2m_conn_params;
    tBTA_DM_BLE_CONN_PARAMS         phy_coded_conn_params;
} tBTA_DM_API_SET_PER_EXT_CONN_PARAMS;

typedef struct {
    BT_HDR                          hdr;
    tBLE_ADDR_TYPE                  own_addr_type;
    BD_ADDR                         peer_addr;
} tBTA_DM_API_EXT_CONN;
#endif //#如果（BLE_50_FFEATURE_SUPPORT==真）
/* 所有数据类型的联合*/
typedef union {
    /* 事件缓冲区标头*/
    BT_HDR              hdr;
    tBTA_DM_API_ENABLE  enable;

    tBTA_DM_API_SET_NAME set_name;
    tBTA_DM_API_CONFIG_EIR config_eir;

    tBTA_DM_API_SET_AFH_CHANNELS set_afh_channels;
#if (SDP_INCLUDED == TRUE)
    tBTA_DM_API_GET_REMOTE_NAME  get_rmt_name;
#endif

#if (BLE_INCLUDED == TRUE)
    tBTA_DM_API_BLE_SET_CHANNELS  ble_set_channels;
    tBTA_DM_API_UPDATE_WHITE_LIST white_list;
    tBTA_DM_API_READ_ADV_TX_POWER read_tx_power;
#endif  ///BLE_INCLUDED == TRUE
    tBTA_DM_API_READ_RSSI rssi;

    tBTA_DM_API_SET_VISIBILITY set_visibility;

    tBTA_DM_API_ADD_DEVICE  add_dev;

    tBTA_DM_API_REMOVE_DEVICE remove_dev;

    tBTA_DM_API_SEARCH search;
#if (SDP_INCLUDED == TRUE)
    tBTA_DM_API_DISCOVER discover;
#endif  ///SDP_INCLUDED == TRUE
    tBTA_DM_API_BOND bond;

    tBTA_DM_API_BOND_CANCEL bond_cancel;

    tBTA_DM_API_SET_PIN_TYPE set_pin_type;
    tBTA_DM_API_PIN_REPLY pin_reply;

    tBTA_DM_API_LOC_OOB     loc_oob;
    tBTA_DM_API_OOB_REPLY   oob_reply;
    tBTA_DM_API_CONFIRM     confirm;
    tBTA_DM_API_KEY_REQ     key_req;
    tBTA_DM_CI_IO_REQ       ci_io_req;
    tBTA_DM_CI_RMT_OOB      ci_rmt_oob;

    tBTA_DM_REM_NAME rem_name;

    tBTA_DM_DISC_RESULT disc_result;

    tBTA_DM_INQUIRY_CMPL inq_cmpl;

    tBTA_DM_SDP_RESULT sdp_event;

    tBTA_DM_ACL_CHANGE  acl_change;

#if (BTA_DM_PM_INCLUDED == TRUE)
    tBTA_DM_PM_BTM_STATUS pm_status;

    tBTA_DM_PM_TIMER pm_timer;
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/

#if (BTA_DM_QOS_INCLUDED == TRUE)
    /* 服务质量集合事件*/
    tBTA_DM_API_QOS_SET qos_set;
#endif /* #如果（BTA_DM_QOS_INCLUDED==真）*/

    tBTA_DM_API_DI_DISC     di_disc;

    tBTA_DM_API_EXECUTE_CBACK exec_cback;

    tBTA_DM_API_SET_ENCRYPTION     set_encryption;

#if BLE_INCLUDED == TRUE
    tBTA_DM_API_ADD_BLEKEY              add_ble_key;
    tBTA_DM_API_ADD_BLE_DEVICE          add_ble_device;
    tBTA_DM_API_PASSKEY_REPLY           ble_passkey_reply;
    tBTA_DM_API_SET_DEFAULT_PASSKEY     ble_set_static_passkey;
    tBTA_DM_API_BLE_SEC_GRANT           ble_sec_grant;
    tBTA_DM_API_BLE_SET_BG_CONN_TYPE    ble_set_bd_conn_type;
    tBTA_DM_API_BLE_CONN_PARAMS         ble_set_conn_params;
    tBTA_DM_API_BLE_CONN_SCAN_PARAMS    ble_set_conn_scan_params;
    tBTA_DM_API_BLE_SCAN_PARAMS         ble_set_scan_params;
    tBTA_DM_API_BLE_SCAN_FILTER_PARAMS  ble_set_scan_fil_params;
    tBTA_DM_API_BLE_OBSERVE             ble_observe;
    tBTA_DM_API_BLE_SCAN                ble_scan;
    tBTA_DM_API_ENABLE_PRIVACY          ble_remote_privacy;
    tBTA_DM_API_LOCAL_PRIVACY           ble_local_privacy;
    tBTA_DM_API_LOCAL_ICON              ble_local_icon;
    tBTA_DM_API_BLE_ADV_PARAMS          ble_set_adv_params;
    tBTA_DM_API_BLE_ADV_PARAMS_ALL      ble_set_adv_params_all;
    tBTA_DM_API_SET_ADV_CONFIG          ble_set_adv_data;
    tBTA_DM_API_SET_ADV_CONFIG_RAW      ble_set_adv_data_raw;
    tBTA_DM_API_SET_LONG_ADV            ble_set_long_adv_data;
#if BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    tBTA_DM_API_SCAN_FILTER_PARAM_SETUP ble_scan_filt_param_setup;
    tBTA_DM_API_CFG_FILTER_COND         ble_cfg_filter_cond;
    tBTA_DM_API_ENABLE_SCAN_FILTER      ble_enable_scan_filt;
#endif
    tBTA_DM_API_UPDATE_CONN_PARAM       ble_update_conn_params;
    tBTA_DM_API_BLE_SET_DATA_LENGTH     ble_set_data_length;
    tBTA_DM_APT_SET_DEV_ADDR            set_addr;
    tBTA_DM_APT_CLEAR_ADDR              clear_addr;
    tBTA_DM_API_BLE_MULTI_ADV_ENB       ble_multi_adv_enb;
    tBTA_DM_API_BLE_MULTI_ADV_PARAM     ble_multi_adv_param;
    tBTA_DM_API_BLE_MULTI_ADV_DATA      ble_multi_adv_data;
    tBTA_DM_API_BLE_MULTI_ADV_DISABLE   ble_multi_adv_disable;

    tBTA_DM_API_SET_STORAGE_CONFIG      ble_set_storage;
    tBTA_DM_API_ENABLE_SCAN             ble_enable_scan;
    tBTA_DM_API_READ_SCAN_REPORTS       ble_read_reports;
    tBTA_DM_API_DISABLE_SCAN            ble_disable_scan;
    tBTA_DM_API_TRACK_ADVERTISER        ble_track_advert;
    tBTA_DM_API_ENERGY_INFO             ble_energy_info;
    tBTA_DM_API_BLE_DISCONNECT          ble_disconnect;
    tBTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST ble_duplicate_exceptional_list;
#if (BLE_50_FEATURE_SUPPORT == TRUE)
    tBTA_DM_API_READ_PHY                ble_read_phy;
    tBTA_DM_API_SET_PER_DEF_PHY         ble_set_per_def_phy;
    tBTA_DM_API_SET_PER_PHY             ble_set_per_phy;
    tBTA_DM_API_EXT_ADV_SET_RAND_ADDR   ble_set_ext_adv_rand_addr;
    tBTA_DM_API_EXT_ADV_SET_PARAMS      ble_set_ext_adv_params;
    tBTA_DM_API_CFG_EXT_ADV_DATA        ble_cfg_ext_adv_data;
    tBTA_DM_API_BLE_EXT_ADV             ble_start_ext_adv;
    tBTA_DM_API_BLE_EXT_ADV_SET_REMOVE  ble_ext_adv_set_remove;
    tBTA_DM_API_BLE_EXT_ADV_SET_CLEAR   ble_ext_adv_set_clear;
    tBTA_DM_API_BLE_PERIODIC_ADV_SET_PARAMS ble_set_periodic_adv_params;
    tBTA_DM_API_CFG_PERIODIC_ADV_DATA   ble_cfg_periodic_adv_data;
    tBTA_DM_API_ENABLE_PERIODIC_ADV     ble_enable_periodic_adv;
    tBTA_DM_API_PERIODIC_ADV_SYNC       ble_periodic_adv_sync;
    tBTA_DM_API_PERIODIC_ADV_SYNC_CANCEL ble_periodic_adv_sync_cancel;
    tBTA_DM_API_PERIODIC_ADV_SYNC_TERM   ble_periodic_adv_sync_term;
    tBTA_DM_API_PERIODIC_ADV_ADD_DEV_TO_LIST ble_periodic_adv_add_dev_to_list;
    tBTA_DM_API_PERIODIC_ADV_REMOVE_DEV_FROM_LIST ble_periodic_adv_remove_dev_from_list;
    tBTA_DM_API_PERIODIC_ADV_DEV_CLEAR  ble_periodic_adv_clear_dev;
    tBTA_DM_API_SET_EXT_SCAN_PARAMS     ble_set_ext_scan_params;
    tBTA_DM_API_EXT_SCAN                ble_ext_scan;
    tBTA_DM_API_SET_PER_EXT_CONN_PARAMS ble_set_per_ext_conn_params;
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
#endif

    tBTA_DM_API_REMOVE_ACL              remove_acl;
    tBTA_DM_API_REMOVE_ALL_ACL          remove_all_acl;

} tBTA_DM_MSG;


#define BTA_DM_NUM_PEER_DEVICE 7

#define BTA_DM_NOT_CONNECTED  0
#define BTA_DM_CONNECTED      1
#define BTA_DM_UNPAIRING      2
typedef UINT8 tBTA_DM_CONN_STATE;


#define BTA_DM_DI_NONE          0x00       /* 没什么特别的*/
#define BTA_DM_DI_USE_SSR       0x10       /* 如果此链接支持ssr，则设置此位*/
#define BTA_DM_DI_AV_ACTIVE     0x20       /* 如果此链接的AV活动，则设置此位*/
#define BTA_DM_DI_SET_SNIFF     0x01       /* 如果调用BTM_SetPowerMode（嗅探），则设置此位*/
#define BTA_DM_DI_INT_SNIFF     0x02       /* 如果调用BTM_SetPowerMode（嗅探）并进入嗅探模式，则设置此位*/
#define BTA_DM_DI_ACP_SNIFF     0x04       /* 如果对等初始化嗅探，则设置此位*/
typedef UINT8 tBTA_DM_DEV_INFO;

/* 设置电源模式请求类型*/
#define BTA_DM_PM_RESTART       1
#define BTA_DM_PM_NEW_REQ       2
#define BTA_DM_PM_EXECUTE       3
typedef UINT8   tBTA_DM_PM_REQ;

typedef struct {
    BD_ADDR                     peer_bdaddr;
    UINT16                      link_policy;
    tBTA_DM_CONN_STATE          conn_state;
    tBTA_PREF_ROLES             pref_role;
    BOOLEAN                     in_use;
    tBTA_DM_DEV_INFO            info;
    tBTA_DM_ENCRYPT_CBACK      *p_encrypt_cback;
#if (BTM_SSR_INCLUDED == TRUE)
    tBTM_PM_STATUS              prev_low;   /* 以前使用的低功率模式*/
#endif
    tBTA_DM_PM_ACTION           pm_mode_attempted;
    tBTA_DM_PM_ACTION           pm_mode_failed;
    BOOLEAN                     remove_dev_pending;
#if BLE_INCLUDED == TRUE
    UINT16                      conn_handle;
#endif
    tBT_TRANSPORT               transport;
} tBTA_DM_PEER_DEVICE;



/* 用于存储活动连接列表的结构*/
typedef struct {
    tBTA_DM_PEER_DEVICE    peer_device[BTA_DM_NUM_PEER_DEVICE];
    UINT8                  count;
#if BLE_INCLUDED == TRUE
    UINT8                  le_count;
#endif
} tBTA_DM_ACTIVE_LINK;


typedef struct {
    BD_ADDR                 peer_bdaddr;
    tBTA_SYS_ID             id;
    UINT8                   app_id;
    tBTA_SYS_CONN_STATUS    state;
    BOOLEAN                 new_request;

} tBTA_DM_SRVCS;

#ifndef BTA_DM_NUM_CONN_SRVS
#define BTA_DM_NUM_CONN_SRVS   10
#endif

typedef struct {

    UINT8 count;
    tBTA_DM_SRVCS  conn_srvc[BTA_DM_NUM_CONN_SRVS];

}  tBTA_DM_CONNECTED_SRVCS;


#if (BTA_DM_PM_INCLUDED == TRUE)

typedef struct {
#define BTA_DM_PM_SNIFF_TIMER_IDX   0
#define BTA_DM_PM_PARK_TIMER_IDX    1
#define BTA_DM_PM_SUSPEND_TIMER_IDX 2
#define BTA_DM_PM_MODE_TIMER_MAX    3
    /*
     * 如果支持TBFC，请为PARK、SNIFF和SUSPEND保留三个不同的计时器。
     */
    TIMER_LIST_ENT          timer[BTA_DM_PM_MODE_TIMER_MAX];

    UINT8                   srvc_id[BTA_DM_PM_MODE_TIMER_MAX];
    UINT8                   pm_action[BTA_DM_PM_MODE_TIMER_MAX];
    UINT8                   active;     /* 活动计时器的数量*/

    BD_ADDR                 peer_bdaddr;
    BOOLEAN                 in_use;
} tBTA_PM_TIMER;

#define BTA_DM_NUM_PM_TIMER 7
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/

/* DM控制块*/
typedef struct {
    BOOLEAN                     is_bta_dm_active;
    tBTA_DM_ACTIVE_LINK         device_list;
    tBTA_DM_SEC_CBACK           *p_sec_cback;
#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    tBTA_BLE_SCAN_SETUP_CBACK   *p_setup_cback;
    tBTA_DM_BLE_PF_CFG_CBACK     *p_scan_filt_cfg_cback;
    tBTA_DM_BLE_PF_STATUS_CBACK  *p_scan_filt_status_cback;
    tBTA_DM_BLE_PF_PARAM_CBACK   *p_scan_filt_param_cback;
    tBTA_BLE_MULTI_ADV_CBACK     *p_multi_adv_cback;
    tBTA_BLE_ENERGY_INFO_CBACK   *p_energy_info_cback;
#endif
    UINT16                      state;
    BOOLEAN                     disabling;
    TIMER_LIST_ENT              disable_timer;
    UINT32                      wbt_sdp_handle;          /* WIDCOMM扩展SDP记录句柄*/
    UINT8                       wbt_scn;                 /* WIDCOMM扩展SCN*/
    UINT8                       num_master_only;
#if (BTA_DM_PM_INCLUDED == TRUE)
    UINT8                       pm_id;
    tBTA_PM_TIMER               pm_timer[BTA_DM_NUM_PM_TIMER];
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/
    UINT32                      role_policy_mask;   /* 位集指示要从默认链接策略中删除角色切换的模块*/
    UINT16                      cur_policy;         /* 当前默认链接策略*/
    UINT16                      rs_event;           /* 等待角色切换的事件*/
    UINT8                       cur_av_count;       /* 当前AV连接*/
    BOOLEAN                     disable_pair_mode;          /* 是否禁用配对模式*/
    BOOLEAN                     conn_paired_only;   /* 是否仅允许连接到配对设备*/
    tBTA_DM_API_SEARCH          search_msg;

#if (CLASSIC_BT_INCLUDED == TRUE)
    UINT16                      page_scan_interval;
    UINT16                      page_scan_window;
    UINT16                      inquiry_scan_interval;
    UINT16                      inquiry_scan_window;

    /* pin码请求参数的存储*/
    BD_ADDR                     pin_bd_addr;
    DEV_CLASS                   pin_dev_class;
    tBTA_DM_SEC_EVT             pin_evt;
    UINT32                      num_val;        /* 用于比较的数值。如果just_works，则不向UI显示此数字*/
    BOOLEAN                     just_works;     /* TRUE，如果“Just Works”关联模型*/
#endif

#if ( BTA_EIR_CANNED_UUID_LIST != TRUE )
    /* 存储EIR的UUID列表*/
    TIMER_LIST_ENT              app_ready_timer;
    UINT32                      eir_uuid[BTM_EIR_SERVICE_ARRAY_SIZE];
#if (BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
    tBT_UUID                    custom_uuid[BTA_EIR_SERVER_NUM_CUSTOM_UUID];
#endif

#endif


    tBTA_DM_ENCRYPT_CBACK      *p_encrypt_cback;
    TIMER_LIST_ENT              switch_delay_timer[BTA_DM_NUM_PEER_DEVICE];

} tBTA_DM_CB;

#ifndef BTA_DM_SDP_DB_SIZE
#define BTA_DM_SDP_DB_SIZE 250
#endif

/* DM搜索控制块*/
typedef struct {

    tBTA_DM_SEARCH_CBACK *p_search_cback;
    tBTM_INQ_INFO         *p_btm_inq_info;
    tBTA_SERVICE_MASK      services;
    tBTA_SERVICE_MASK      services_to_search;
    tBTA_SERVICE_MASK      services_found;
#if (SDP_INCLUDED == TRUE)
    tSDP_DISCOVERY_DB     *p_sdp_db;
#endif  ///SDP_INCLUDED == TRUE
    UINT16                 state;
    BD_ADDR                peer_bdaddr;
    BOOLEAN                name_discover_done;
    BD_NAME                peer_name;
    TIMER_LIST_ENT         search_timer;
    UINT8                  service_index;
    tBTA_DM_MSG           *p_search_queue;   /* 在此处存储的搜索取消期间搜索或发现命令*/
    BOOLEAN                wait_disc;
    BOOLEAN                sdp_results;
#if (SDP_INCLUDED == TRUE)
    tSDP_UUID              uuid;
#endif  ///SDP_INCLUDED == TRUE
    UINT8                  peer_scn;
    BOOLEAN                sdp_search;
    BOOLEAN                cancel_pending; /* 查询取消待定*/
    tBTA_TRANSPORT         transport;
#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    tBTA_DM_SEARCH_CBACK *p_scan_cback;
#if ((defined BTA_GATT_INCLUDED) && (BTA_GATT_INCLUDED == TRUE) && SDP_INCLUDED == TRUE)
    tBTA_GATTC_IF          client_if;
    UINT8                  num_uuid;
    tBT_UUID               *p_srvc_uuid;
    UINT8                  uuid_to_search;
    BOOLEAN                gatt_disc_active;
    UINT16                 conn_id;
    UINT8                  *p_ble_rawdata;
    UINT32                 ble_raw_size;
    UINT32                 ble_raw_used;
    TIMER_LIST_ENT         gatt_close_timer; /* GATT通道关闭延迟计时器*/
    BD_ADDR                pending_close_bda; /* 未决GATT信道远程设备地址*/
#endif
#endif


} tBTA_DM_SEARCH_CB;

/* DI控制块*/
typedef struct {
#if (SDP_INCLUDED == TRUE)
    tSDP_DISCOVERY_DB     *p_di_db;     /* 指向DI发现数据库的指针*/
#endif  ///SDP_INCLUDED == TRUE
    UINT8               di_num;         /* 本地DI记录总数*/
    UINT32              di_handle[BTA_DI_NUM_MAX];  /* 本地DI记录句柄，第一个是主记录*/
} tBTA_DM_DI_CB;

/* DM搜索状态*/
enum {

    BTA_DM_SEARCH_IDLE,
    BTA_DM_SEARCH_ACTIVE,
    BTA_DM_SEARCH_CANCELLING,
    BTA_DM_DISCOVER_ACTIVE

};



typedef struct {
    DEV_CLASS      dev_class;          /* 本地设备类*/
    UINT16         policy_settings;    /* 链接策略设置保持、嗅探、驻车、MS切换*/
    UINT16         page_timeout;       /* 插槽中的页面超时*/
    UINT16         link_timeout;       /* 插槽中的链路监控超时*/
    BOOLEAN        avoid_scatter;      /* 如果为TRUE，则在av流时避免散射网（成为主控）*/

} tBTA_DM_CFG;

extern const UINT32 bta_service_id_to_btm_srv_id_lkup_tbl[];


typedef struct {
    UINT8   id;
    UINT8   app_id;
    UINT8   cfg;

} tBTA_DM_RM ;

extern tBTA_DM_CFG *const p_bta_dm_cfg;
extern tBTA_DM_RM *const p_bta_dm_rm_cfg;

typedef struct {

    UINT8  id;
    UINT8  app_id;
    UINT8  spec_idx;  /* 要使用的规格表索引*/

} tBTA_DM_PM_CFG;


typedef struct {

    tBTA_DM_PM_ACTION   power_mode;
    UINT16              timeout;

} tBTA_DM_PM_ACTN;

typedef struct {

    UINT8  allow_mask;         /* 允许的嗅探/保持/驻车模式掩码*/
#if (BTM_SSR_INCLUDED == TRUE)
    UINT8  ssr;                /* 在连接打开/取消标记时设置SSR*/
#endif
    tBTA_DM_PM_ACTN actn_tbl [BTA_DM_PM_NUM_EVTS][2];

} tBTA_DM_PM_SPEC;

typedef struct {
    UINT16      max_lat;
    UINT16      min_rmt_to;
    UINT16      min_loc_to;
} tBTA_DM_SSR_SPEC;

typedef struct {
    UINT16 manufacturer;
    UINT16 lmp_sub_version;
    UINT8 lmp_version;
} tBTA_DM_LMP_VER_INFO;

#if (BTA_DM_PM_INCLUDED == TRUE)
extern tBTA_DM_PM_CFG *const p_bta_dm_pm_cfg;
extern tBTA_DM_PM_SPEC *const p_bta_dm_pm_spec;
extern tBTM_PM_PWR_MD *const p_bta_dm_pm_md;
#if (BTM_SSR_INCLUDED == TRUE)
extern tBTA_DM_SSR_SPEC *const p_bta_dm_ssr_spec;
#endif
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/

/* 更新动态BRCM感知EIR数据*/
extern tBTA_DM_EIR_CONF bta_dm_eir_cfg;
extern tBTA_DM_EIR_CONF *p_bta_dm_eir_cfg;

/* DM控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_CB  bta_dm_cb;
#else
extern tBTA_DM_CB *bta_dm_cb_ptr;
#define bta_dm_cb (*bta_dm_cb_ptr)
#endif

/* DM搜索控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_SEARCH_CB  bta_dm_search_cb;
#else
extern tBTA_DM_SEARCH_CB *bta_dm_search_cb_ptr;
#define bta_dm_search_cb (*bta_dm_search_cb_ptr)
#endif

/* DI控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_DI_CB  bta_dm_di_cb;
#else
extern tBTA_DM_DI_CB *bta_dm_di_cb_ptr;
#define bta_dm_di_cb (*bta_dm_di_cb_ptr)
SemaphoreHandle_t deinit_semaphore;
#endif

#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_CONNECTED_SRVCS  bta_dm_conn_srvcs;
#else
extern tBTA_DM_CONNECTED_SRVCS *bta_dm_conn_srvcs_ptr;
#define bta_dm_conn_srvcs (*bta_dm_conn_srvcs_ptr)
#endif

/* 发现原始数据缓冲区*/
#define MAX_DISC_RAW_DATA_BUF       (1024)
#if BTA_DYNAMIC_MEMORY == TRUE
extern UINT8 *g_disc_raw_data_buf;
#endif

extern BOOLEAN bta_dm_sm_execute(BT_HDR *p_msg);
extern void bta_dm_sm_disable( void );
extern void bta_dm_sm_deinit(void);
extern BOOLEAN bta_dm_search_sm_execute(BT_HDR *p_msg);
extern void bta_dm_search_sm_disable( void );


extern void bta_dm_enable (tBTA_DM_MSG *p_data);
extern void bta_dm_disable (tBTA_DM_MSG *p_data);
extern void bta_dm_set_dev_name (tBTA_DM_MSG *p_data);
#if (CLASSIC_BT_INCLUDED == TRUE)
extern void bta_dm_config_eir (tBTA_DM_MSG *p_data);
#endif
extern void bta_dm_set_afh_channels (tBTA_DM_MSG *p_data);
extern void bta_dm_read_rmt_name(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_channels (tBTA_DM_MSG *p_data);
extern void bta_dm_update_white_list(tBTA_DM_MSG *p_data);
extern void bta_dm_clear_white_list(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_read_adv_tx_power(tBTA_DM_MSG *p_data);
extern void bta_dm_read_rssi(tBTA_DM_MSG *p_data);
extern void bta_dm_set_visibility (tBTA_DM_MSG *p_data);

extern void bta_dm_set_scan_config(tBTA_DM_MSG *p_data);
extern void bta_dm_vendor_spec_command(tBTA_DM_MSG *p_data);
extern void bta_dm_bond (tBTA_DM_MSG *p_data);
extern void bta_dm_bond_cancel (tBTA_DM_MSG *p_data);
extern void bta_dm_set_pin_type (tBTA_DM_MSG *p_data);
extern void bta_dm_pin_reply (tBTA_DM_MSG *p_data);
extern void bta_dm_acl_change(tBTA_DM_MSG *p_data);
extern void bta_dm_add_device (tBTA_DM_MSG *p_data);
extern void bta_dm_remove_device (tBTA_DM_MSG *p_data);
extern void bta_dm_close_acl(tBTA_DM_MSG *p_data);

extern void bta_dm_add_ampkey (tBTA_DM_MSG *p_data);

#if BLE_INCLUDED == TRUE
extern void bta_dm_add_blekey (tBTA_DM_MSG *p_data);
extern void bta_dm_add_ble_device (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_passkey_reply (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_static_passkey(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_confirm_reply (tBTA_DM_MSG *p_data);
extern void bta_dm_security_grant (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_bg_conn_type (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_conn_params (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_scan_params(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_scan_fil_params(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_conn_scan_params (tBTA_DM_MSG *p_data);
#if ((defined BTA_GATT_INCLUDED) &&  (BTA_GATT_INCLUDED == TRUE) && SDP_INCLUDED == TRUE) && (GATTC_INCLUDED == TRUE)
extern void bta_dm_close_gatt_conn(tBTA_DM_MSG *p_data);
#endif /* （（定义BTA_GATT_INCLUDED）&&（BTA_GATT.INCLUDED==真）&&SDP_INCLUDE==真）&（GATTC_INCLUDD==真*/
extern void bta_dm_ble_observe (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_scan (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_update_conn_params (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_disconnect (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_rand_address(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_clear_rand_address(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_stop_advertising(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_config_local_privacy (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_config_local_icon (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_adv_params (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_adv_params_all(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_adv_config (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_long_adv (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_adv_config_raw (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_scan_rsp (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_scan_rsp_raw (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_broadcast (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_data_length(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_update_duplicate_exceptional_list(tBTA_DM_MSG *p_data);
#if BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
extern void bta_dm_cfg_filter_cond (tBTA_DM_MSG *p_data);
extern void bta_dm_scan_filter_param_setup (tBTA_DM_MSG *p_data);
extern void bta_dm_enable_scan_filter(tBTA_DM_MSG *p_data);
#endif
extern void btm_dm_ble_multi_adv_disable(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_multi_adv_data(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_multi_adv_upd_param(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_multi_adv_enb(tBTA_DM_MSG *p_data);
#if (BLE_50_FEATURE_SUPPORT == TRUE)
extern void bta_dm_ble_gap_read_phy(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_set_prefer_default_phy(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_set_prefer_phy(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_ext_adv_set_rand_addr(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_ext_adv_set_params(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_config_ext_adv_data_raw(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_set_ext_scan_params(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_ext_scan(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_gap_set_prefer_ext_conn_params(tBTA_DM_MSG *p_data);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
extern void bta_dm_ble_setup_storage(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_enable_batch_scan(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_disable_batch_scan(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_read_scan_reports(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_track_advertiser(tBTA_DM_MSG *p_data);
extern void bta_dm_ble_get_energy_info(tBTA_DM_MSG *p_data);

#endif
extern void bta_dm_set_encryption(tBTA_DM_MSG *p_data);
extern void bta_dm_confirm(tBTA_DM_MSG *p_data);
extern void bta_dm_key_req(tBTA_DM_MSG *p_data);

#if (BTA_HD_INCLUDED == TRUE)
extern BOOLEAN bta_dm_check_if_only_hd_connected(BD_ADDR peer_addr);
#endif /* BTA_HD_INCLUDED */

#if (BTM_OOB_INCLUDED == TRUE)
extern void bta_dm_loc_oob(tBTA_DM_MSG *p_data);
extern void bta_dm_oob_reply(tBTA_DM_MSG *p_data);
extern void bta_dm_ci_io_req_act(tBTA_DM_MSG *p_data);
extern void bta_dm_ci_rmt_oob_act(tBTA_DM_MSG *p_data);
#endif /* BTM_OOB_INCLUDED */

#if (BTA_DM_PM_INCLUDED == TRUE)
extern void bta_dm_init_pm(void);
extern void bta_dm_disable_pm(void);
extern void bta_dm_pm_active(BD_ADDR peer_addr);
extern void bta_dm_pm_btm_status(tBTA_DM_MSG *p_data);
extern void bta_dm_pm_timer(tBTA_DM_MSG *p_data);
#endif /* #如果（BTA_DM_PM_INCLUDED==真）*/

#if (BTA_DM_QOS_INCLUDED == TRUE)
extern void bta_dm_set_qos(tBTA_DM_MSG *p_data);
#endif /* #如果（BTA_DM_QOS_INCLUDED==真）*/

extern UINT8 bta_dm_get_av_count(void);
extern void bta_dm_search_start (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel (tBTA_DM_MSG *p_data);
extern void bta_dm_discover (tBTA_DM_MSG *p_data);
#if (SDP_INCLUDED == TRUE)
extern void bta_dm_di_disc (tBTA_DM_MSG *p_data);
#endif  ///SDP_INCLUDED == TRUE
extern void bta_dm_inq_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_rmt_name (tBTA_DM_MSG *p_data);
#if (SDP_INCLUDED == TRUE)
extern void bta_dm_sdp_result (tBTA_DM_MSG *p_data);
#endif  ///SDP_INCLUDED == TRUE
extern void bta_dm_search_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_free_sdp_db (tBTA_DM_MSG *p_data);
extern void bta_dm_disc_result (tBTA_DM_MSG *p_data);
extern void bta_dm_search_result (tBTA_DM_MSG *p_data);
extern void bta_dm_discovery_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_queue_search (tBTA_DM_MSG *p_data);
extern void bta_dm_queue_disc (tBTA_DM_MSG *p_data);
extern void bta_dm_search_clear_queue (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel_notify (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel_transac_cmpl(tBTA_DM_MSG *p_data);
extern void bta_dm_disc_rmt_name (tBTA_DM_MSG *p_data);
extern tBTA_DM_PEER_DEVICE *bta_dm_find_peer_device(BD_ADDR peer_addr);
void bta_dm_eir_update_uuid(UINT16 uuid16, BOOLEAN adding);

extern void bta_dm_enable_test_mode(tBTA_DM_MSG *p_data);
extern void bta_dm_disable_test_mode(tBTA_DM_MSG *p_data);
extern void bta_dm_execute_callback(tBTA_DM_MSG *p_data);


extern void bta_dm_remove_all_acl(tBTA_DM_MSG *p_data);
#if (BLE_50_FEATURE_SUPPORT == TRUE)
extern void bta_dm_ble_gap_read_phy(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_set_prefer_default_phy(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_set_prefer_phy(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_ext_adv_set_rand_addr(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_ext_adv_set_params(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_config_ext_adv_data_raw(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_start_ext_adv(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_ext_adv_set_remove(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_ext_adv_set_clear(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_set_params(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_cfg_data_raw(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_enable(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_create_sync(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_sync_cancel(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_sync_terminate(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_add_dev_to_list(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_remove_dev_from_list(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_periodic_adv_clear_dev(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_set_ext_scan_params(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_ext_scan(tBTA_DM_MSG *p_data);

extern void bta_dm_ble_gap_set_prefer_ext_conn_params(tBTA_DM_MSG *p_data);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）

#endif /* BTA_DM_INT_H */

