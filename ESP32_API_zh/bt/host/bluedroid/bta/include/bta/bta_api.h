/******************************************************************************
 * 版权所有（C）2003-2014 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA的公共接口文件，Broadcom的移动电话蓝牙应用层。
 *
 ******************************************************************************/
#ifndef BTA_API_H
#define BTA_API_H

#include "common/bt_target.h"
#include "stack/bt_types.h"
#include "stack/btm_api.h"
// #包括“uipc_msg.h”
#include "stack/sdp_api.h"

// #如果BLE_INCLUDED==真
#include "stack/btm_ble_api.h"
// #结束符

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/* 状态返回值*/
#define BTA_SUCCESS             0           /* 操作成功。*/
#define BTA_FAILURE             1           /* 一般故障。*/
#define BTA_PENDING             2           /* API现在无法完成*/
#define BTA_BUSY                3
#define BTA_NO_RESOURCES        4
#define BTA_WRONG_MODE          5
#define BTA_EIR_TOO_LARGE       6

typedef UINT8 tBTA_STATUS;

/*
 * 服务ID
 *
 * 注意：当您为BTA添加新的服务ID并要求更改BTA_MAX_Service_ID的值时，请确保应将安全服务定义（stack/btm_api.h）中新服务的正确安全ID添加到BTA_se_ID_to_btm_srv_ID_lkup_tbl表中。
 */

#define BTA_RES_SERVICE_ID      0           /* 保留*/
#define BTA_SPP_SERVICE_ID      1           /* 串行端口配置文件。*/
#define BTA_DUN_SERVICE_ID      2           /* 拨号网络配置文件。*/
#define BTA_A2DP_SOURCE_SERVICE_ID      3   /* A2DP源配置文件。*/
#define BTA_LAP_SERVICE_ID      4           /* LAN访问配置文件。*/
#define BTA_HSP_SERVICE_ID      5           /* 耳机模式。*/
#define BTA_HFP_SERVICE_ID      6           /* 免提模式。*/
#define BTA_OPP_SERVICE_ID      7           /* 对象推送*/
#define BTA_FTP_SERVICE_ID      8           /* 文件传输*/
#define BTA_CTP_SERVICE_ID      9           /* 无绳终端*/
#define BTA_ICP_SERVICE_ID      10          /* 内部通信终端*/
#define BTA_SYNC_SERVICE_ID     11          /* 同步*/
#define BTA_BPP_SERVICE_ID      12          /* 基本打印配置文件*/
#define BTA_BIP_SERVICE_ID      13          /* 基本成像配置文件*/
#define BTA_PANU_SERVICE_ID     14          /* PAN用户*/
#define BTA_NAP_SERVICE_ID      15          /* PAN网络接入点*/
#define BTA_GN_SERVICE_ID       16          /* PAN组自组织网络*/
#define BTA_SAP_SERVICE_ID      17          /* SIM卡接入模式*/
#define BTA_A2DP_SINK_SERVICE_ID        18  /* A2DP水槽*/
#define BTA_AVRCP_SERVICE_ID    19          /* A/V遥控器*/
#define BTA_HID_SERVICE_ID      20          /* HID主机*/
#define BTA_VDP_SERVICE_ID      21          /* 视频分发*/
#define BTA_PBAP_SERVICE_ID     22          /* 电话簿访问服务器*/
#define BTA_HSP_HS_SERVICE_ID   23          /* HFP HS角色*/
#define BTA_HFP_HS_SERVICE_ID   24          /* HSP HS角色*/
#define BTA_MAP_SERVICE_ID      25          /* 邮件访问配置文件*/
#define BTA_MN_SERVICE_ID       26          /* 消息通知服务*/
#define BTA_HDP_SERVICE_ID      27          /* 健康设备配置文件*/
#define BTA_PCE_SERVICE_ID      28          /* 电话簿访问客户端*/
#define BTA_SDP_SERVICE_ID      29          /* SDP搜索*/
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
/* BLE配置文件服务ID*/
#define BTA_BLE_SERVICE_ID      30          /* GATT概况*/

// btla特定++
#define BTA_USER_SERVICE_ID     31          /* 用户请求的UUID*/

#define BTA_MAX_SERVICE_ID      32
// btla特定--
#else
#define BTA_USER_SERVICE_ID     30          /* 用户请求的UUID*/
#define BTA_MAX_SERVICE_ID      31
#endif
/* BTA JV使用服务ID（BTM_SEC_service_FIRST_EMPTY+1）到（BTM_SEC_MAX_SERVICES-1）*/
#define BTA_FIRST_JV_SERVICE_ID     (BTM_SEC_SERVICE_FIRST_EMPTY + 1)
#define BTA_LAST_JV_SERVICE_ID      (BTM_SEC_MAX_SERVICES - 1)

typedef UINT8 tBTA_SERVICE_ID;

/* 服务ID掩码*/
#define BTA_RES_SERVICE_MASK        0x00000001  /* 保留*/
#define BTA_SPP_SERVICE_MASK        0x00000002  /* 串行端口配置文件。*/
#define BTA_DUN_SERVICE_MASK        0x00000004  /* 拨号网络配置文件。*/
#define BTA_FAX_SERVICE_MASK        0x00000008  /* 传真配置文件。*/
#define BTA_LAP_SERVICE_MASK        0x00000010  /* LAN访问配置文件。*/
#define BTA_HSP_SERVICE_MASK        0x00000020  /* HSP AG的作用。*/
#define BTA_HFP_SERVICE_MASK        0x00000040  /* HFP AG角色*/
#define BTA_OPP_SERVICE_MASK        0x00000080  /* 对象推送*/
#define BTA_FTP_SERVICE_MASK        0x00000100  /* 文件传输*/
#define BTA_CTP_SERVICE_MASK        0x00000200  /* 无绳终端*/
#define BTA_ICP_SERVICE_MASK        0x00000400  /* 内部通信终端*/
#define BTA_SYNC_SERVICE_MASK       0x00000800  /* 同步*/
#define BTA_BPP_SERVICE_MASK        0x00001000  /* 打印服务器*/
#define BTA_BIP_SERVICE_MASK        0x00002000  /* 基本成像*/
#define BTA_PANU_SERVICE_MASK       0x00004000  /* PAN用户*/
#define BTA_NAP_SERVICE_MASK        0x00008000  /* PAN网络接入点*/
#define BTA_GN_SERVICE_MASK         0x00010000  /* PAN组自组织网络*/
#define BTA_SAP_SERVICE_MASK        0x00020000  /* PAN组自组织网络*/
#define BTA_A2DP_SERVICE_MASK       0x00040000  /* 高级音频分发*/
#define BTA_AVRCP_SERVICE_MASK      0x00080000  /* A/V遥控器*/
#define BTA_HID_SERVICE_MASK        0x00100000  /* HID */
#define BTA_VDP_SERVICE_MASK        0x00200000  /* 视频分发*/
#define BTA_PBAP_SERVICE_MASK       0x00400000  /* 电话簿服务器*/
#define BTA_HSP_HS_SERVICE_MASK     0x00800000  /* HFP HS角色*/
#define BTA_HFP_HS_SERVICE_MASK     0x01000000  /* HSP HS角色*/
#define BTA_MAS_SERVICE_MASK        0x02000000  /* 邮件访问配置文件*/
#define BTA_MN_SERVICE_MASK         0x04000000  /* 消息通知配置文件*/
#define BTA_HL_SERVICE_MASK         0x08000000  /* 健康设备配置文件*/
#define BTA_PCE_SERVICE_MASK        0x10000000  /* 电话簿客户端*/

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
#define BTA_BLE_SERVICE_MASK        0x20000000  /* 基于GATT的服务*/
// btla特定++
#define BTA_USER_SERVICE_MASK       0x40000000  /* 消息通知配置文件*/
// btla特定--
#else
// btla特定++
#define BTA_USER_SERVICE_MASK       0x20000000  /* 消息通知配置文件*/
// btla特定--
#endif

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
#define BTA_ALL_SERVICE_MASK        0x3FFFFFFF  /* BTA支持的所有服务。*/
#else
#define BTA_ALL_SERVICE_MASK        0x1FFFFFFF  /* BTA支持的所有服务。*/
#endif

typedef UINT32 tBTA_SERVICE_MASK;

/* 扩展服务掩码，包括带有一个或多个GATT UUID的掩码*/
typedef struct {
    tBTA_SERVICE_MASK   srvc_mask;
    UINT8               num_uuid;
    tBT_UUID            *p_uuid;
} tBTA_SERVICE_MASK_EXT;

/* 安全设置掩码*/
#define BTA_SEC_NONE            BTM_SEC_NONE                                         /* 没有安全性。*/
#define BTA_SEC_AUTHORIZE       (BTM_SEC_IN_AUTHORIZE )                              /* 需要授权（仅用于外出连接）*/
#define BTA_SEC_AUTHENTICATE    (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_OUT_AUTHENTICATE) /* 需要身份验证。*/
#define BTA_SEC_ENCRYPT         (BTM_SEC_IN_ENCRYPT | BTM_SEC_OUT_ENCRYPT)           /* 需要加密。*/
#define BTA_SEC_MODE4_LEVEL4    (BTM_SEC_MODE4_LEVEL4)                               /* 模式4级别4服务，即传入/传出MITM和P-256加密*/
#define BTA_SEC_MITM            (BTM_SEC_IN_MITM | BTM_SEC_OUT_MITM)                 /* Man-In-The_Middle保护*/
#define BTA_SEC_IN_16_DIGITS    (BTM_SEC_IN_MIN_16_DIGIT_PIN)                        /* 引脚代码最小16位*/

typedef UINT16 tBTA_SEC;

/* 忽略可发现、可连接、可配对和可连接仅配对设备模式*/
#define BTA_DM_IGNORE           0x00FF

/* 对于可发现模式忽略，对于LE模式仅可连接*/
#define BTA_DM_LE_IGNORE           0xFF00

#define BTA_APP_ID_1               1    /* PM示例配置文件1*/
#define BTA_APP_ID_PAN_MULTI    0xFE    /* 泛多连接的应用程序id*/
#define BTA_ALL_APP_ID          0xFF

/* 可发现模式*/
#define BTA_DM_NON_DISC         BTM_NON_DISCOVERABLE        /* 设备无法发现。*/
#define BTA_DM_GENERAL_DISC     BTM_GENERAL_DISCOVERABLE    /* 一般可发现。*/
#define BTA_DM_LIMITED_DISC     BTM_LIMITED_DISCOVERABLE    /* 有限的可发现性。*/
#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
#define BTA_DM_BLE_NON_DISCOVERABLE        BTM_BLE_NON_DISCOVERABLE        /* 设备无法被LE发现*/
#define BTA_DM_BLE_GENERAL_DISCOVERABLE    BTM_BLE_GENERAL_DISCOVERABLE    /* 设备是LE常规可发现的*/
#define BTA_DM_BLE_LIMITED_DISCOVERABLE    BTM_BLE_LIMITED_DISCOVERABLE    /* 设备是LE有限的可发现设备*/
#endif
typedef UINT16 tBTA_DM_DISC;        /* 这种可发现模式是BR模式和LE模式之间的位掩码*/

/* 可连接模式*/
#define BTA_DM_NON_CONN         BTM_NON_CONNECTABLE         /* 设备无法连接。*/
#define BTA_DM_CONN             BTM_CONNECTABLE             /* 设备可连接。*/
#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
#define BTA_DM_BLE_NON_CONNECTABLE      BTM_BLE_NON_CONNECTABLE     /* 设备是LE不可连接的。*/
#define BTA_DM_BLE_CONNECTABLE          BTM_BLE_CONNECTABLE         /* 设备可通过LE连接。*/
#endif

// btla特定++
typedef UINT16 tBTA_DM_CONN;

#define BTA_TRANSPORT_UNKNOWN   0
#define BTA_TRANSPORT_BR_EDR    BT_TRANSPORT_BR_EDR
#define BTA_TRANSPORT_LE        BT_TRANSPORT_LE
typedef tBT_TRANSPORT tBTA_TRANSPORT;

/* 可配对模式*/
#define BTA_DM_PAIRABLE         1
#define BTA_DM_NON_PAIRABLE     0

/* 仅可连接成对模式*/
#define BTA_DM_CONN_ALL         0
#define BTA_DM_CONN_PAIRED      1

/* 查询模式*/
#define BTA_DM_INQUIRY_NONE     BTM_INQUIRY_NONE            /*无BR查询。*/
#define BTA_DM_GENERAL_INQUIRY  BTM_GENERAL_INQUIRY         /* 执行一般查询。*/
#define BTA_DM_LIMITED_INQUIRY  BTM_LIMITED_INQUIRY         /* 执行有限的查询。*/

#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
#define BTA_BLE_INQUIRY_NONE    BTM_BLE_INQUIRY_NONE
#define BTA_BLE_GENERAL_INQUIRY BTM_BLE_GENERAL_INQUIRY      /* 执行LE常规查询。*/
#define BTA_BLE_LIMITED_INQUIRY BTM_BLE_LIMITED_INQUIRY      /* 执行LE受限查询。*/
#endif
typedef UINT8 tBTA_DM_INQ_MODE;

/* 查询筛选器类型*/
#define BTA_DM_INQ_CLR          BTM_CLR_INQUIRY_FILTER          /* 清除查询筛选器。*/
#define BTA_DM_INQ_DEV_CLASS    BTM_FILTER_COND_DEVICE_CLASS    /* 设备类上的筛选器。*/
#define BTA_DM_INQ_BD_ADDR      BTM_FILTER_COND_BD_ADDR         /* 过滤特定BD地址。*/

typedef UINT8 tBTA_DM_INQ_FILT;

/* 授权响应*/
#define BTA_DM_AUTH_PERM        0      /* 授权将来连接到服务*/
#define BTA_DM_AUTH_TEMP        1      /* 仅授权用于当前连接*/
#define BTA_DM_NOT_AUTH         2      /* 未授权服务*/

typedef UINT8 tBTA_AUTH_RESP;

/* M/S首选角色*/
#define BTA_ANY_ROLE          0x00
#define BTA_MASTER_ROLE_PREF  0x01
#define BTA_MASTER_ROLE_ONLY  0x02
#define BTA_SLAVE_ROLE_ONLY   0x03     /* 仅用于PANU，跳过角色切换到主*/

typedef UINT8 tBTA_PREF_ROLES;

enum {

    BTA_DM_NO_SCATTERNET,        /* 设备不支持散点网，它可能支持传入连接的“连接过程中的角色切换”，当它已经在主角色中有另一个连接时*/
    BTA_DM_PARTIAL_SCATTERNET,   /* 设备支持部分散射网。它可以在短时间内在主和从角色中具有模拟连接*/
    BTA_DM_FULL_SCATTERNET       /* 设备可以在主和从角色中同时连接*/

};


/* 查询过滤器设备类别条件*/
typedef struct {
    DEV_CLASS       dev_class;        /* 感兴趣的设备类别*/
    DEV_CLASS       dev_class_mask;   /* 掩码以确定感兴趣的设备类别的位*/
} tBTA_DM_COD_COND;


/* 查询筛选条件*/
typedef union {
    BD_ADDR              bd_addr;            /* 要筛选的设备的BD地址。*/
    tBTA_DM_COD_COND     dev_class_cond;     /* 设备类别筛选器条件*/
} tBTA_DM_INQ_COND;

/* 查询参数*/
typedef struct {
    tBTA_DM_INQ_MODE    mode;           /* 查询模式，有限或一般。*/
    UINT8               duration;       /* 以1.28秒为单位的查询持续时间。*/
    UINT8               max_resps;      /* 最大查询响应。设置为零表示无限响应。*/
    BOOLEAN             report_dup;     /* 报告具有较高RSSI值的重复查询响应*/
    tBTA_DM_INQ_FILT    filter_type;    /* 过滤条件类型。*/
    tBTA_DM_INQ_COND    filter_cond;    /* 筛选条件数据。*/
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    UINT8               intl_duration[4];/*存储交织扫描时间部分的持续时间数组*/
#endif
} tBTA_DM_INQ;

/* 配置EIR回调*/
typedef void (tBTA_DM_CONFIG_EIR_CBACK) (tBTA_STATUS status, UINT8 eir_type_num, UINT8 *eir_type);

typedef struct {
    BOOLEAN bta_dm_eir_fec_required;        /* 需要FEC*/
    UINT8   bta_dm_eir_min_name_len;        /* 缩短本地名称时的最小长度*/

    BOOLEAN bta_dm_eir_included_uuid;       /* 是否包含UUID*/
#if (BTA_EIR_CANNED_UUID_LIST == TRUE)
    UINT8   bta_dm_eir_uuid16_len;          /* 16位UUID的长度*/
    UINT8  *bta_dm_eir_uuid16;              /* 16位UUID*/
#else
    UINT32  uuid_mask[BTM_EIR_SERVICE_ARRAY_SIZE];      /* EIR中UUID列表的掩码*/
#endif

    BOOLEAN bta_dm_eir_included_tx_power;   /* 是否包含询问TX功率*/
    INT8    bta_dm_eir_inq_tx_power;        /* 查询TX功率*/

    UINT8   bta_dm_eir_flags;               /* EIR标志*/
    UINT8   bta_dm_eir_manufac_spec_len;    /* 制造商特定的长度（字节）*/
    UINT8  *bta_dm_eir_manufac_spec;        /* 制造商特定*/
    UINT8   bta_dm_eir_url_len;             /* URL长度（字节）*/
    UINT8  *bta_dm_eir_url;                 /* URL数据*/

    tBTA_DM_CONFIG_EIR_CBACK    *config_eir_callback;   /* 回调*/
} tBTA_DM_EIR_CONF;

// #如果BLE_INCLUDED==真
/* 用于BTM_BLE_AD_TYPE_flag的ADV数据标志位定义*/
#define BTA_BLE_LIMIT_DISC_FLAG     BTM_BLE_LIMIT_DISC_FLAG
#define BTA_BLE_GEN_DISC_FLAG       BTM_BLE_GEN_DISC_FLAG
#define BTA_BLE_BREDR_NOT_SPT       BTM_BLE_BREDR_NOT_SPT
#define BTA_BLE_DMT_CONTROLLER_SPT  BTM_BLE_DMT_CONTROLLER_SPT
#define BTA_BLE_DMT_HOST_SPT        BTM_BLE_DMT_HOST_SPT
#define BTA_BLE_NON_LIMIT_DISC_FLAG BTM_BLE_NON_LIMIT_DISC_FLAG
#define BTA_BLE_ADV_FLAG_MASK       BTM_BLE_ADV_FLAG_MASK
#define BTA_BLE_LIMIT_DISC_MASK     BTM_BLE_LIMIT_DISC_MASK

/* ADV数据位掩码*/
#define BTA_BLE_AD_BIT_DEV_NAME        BTM_BLE_AD_BIT_DEV_NAME
#define BTA_BLE_AD_BIT_FLAGS           BTM_BLE_AD_BIT_FLAGS
#define BTA_BLE_AD_BIT_MANU            BTM_BLE_AD_BIT_MANU
#define BTA_BLE_AD_BIT_TX_PWR          BTM_BLE_AD_BIT_TX_PWR
#define BTA_BLE_AD_BIT_INT_RANGE       BTM_BLE_AD_BIT_INT_RANGE
#define BTA_BLE_AD_BIT_SERVICE         BTM_BLE_AD_BIT_SERVICE
#define BTA_BLE_AD_BIT_APPEARANCE      BTM_BLE_AD_BIT_APPEARANCE
#define BTA_BLE_AD_BIT_PROPRIETARY     BTM_BLE_AD_BIT_PROPRIETARY
#define BTA_DM_BLE_AD_BIT_SERVICE_SOL     BTM_BLE_AD_BIT_SERVICE_SOL
#define BTA_DM_BLE_AD_BIT_SERVICE_DATA    BTM_BLE_AD_BIT_SERVICE_DATA
#define BTA_DM_BLE_AD_BIT_SIGN_DATA       BTM_BLE_AD_BIT_SIGN_DATA
#define BTA_DM_BLE_AD_BIT_SERVICE_128SOL  BTM_BLE_AD_BIT_SERVICE_128SOL
#define BTA_DM_BLE_AD_BIT_PUBLIC_ADDR     BTM_BLE_AD_BIT_PUBLIC_ADDR
#define BTA_DM_BLE_AD_BIT_RANDOM_ADDR     BTM_BLE_AD_BIT_RANDOM_ADDR
#define BTA_DM_BLE_AD_BIT_SERVICE_128     BTM_BLE_AD_BIT_SERVICE_128      /*128位服务UUID*/

typedef  tBTM_BLE_AD_MASK  tBTA_BLE_AD_MASK;

/* 从属首选连接间隔范围*/
typedef struct {
    UINT16  low;
    UINT16  hi;

} tBTA_BLE_INT_RANGE;

/* 设备中支持的服务标签*/
typedef struct {
    UINT8       num_service;
    BOOLEAN     list_cmpl;
    UINT16      *p_uuid;
} tBTA_BLE_SERVICE;


typedef struct {
    UINT8       len;
    UINT8      *p_val;
} tBTA_BLE_MANU;

typedef struct {
    UINT8       adv_type;
    UINT8       len;
    UINT8       *p_val;     /* len字节数*/
} tBTA_BLE_PROP_ELEM;

/* 供应商专有adv类型*/
typedef struct {
    UINT8                   num_elem;
    tBTA_BLE_PROP_ELEM      *p_elem;
} tBTA_BLE_PROPRIETARY;

typedef struct {
    tBT_UUID    service_uuid;
    UINT8       len;
    UINT8      *p_val;
} tBTA_BLE_SERVICE_DATA;

typedef tBTM_BLE_128SERVICE tBTA_BLE_128SERVICE;
typedef tBTM_BLE_32SERVICE  tBTA_BLE_32SERVICE;

typedef struct {
    tBTA_BLE_INT_RANGE      int_range;          /* 从属优先连接间隔范围*/
    tBTA_BLE_MANU           *p_manu;            /* 制造商数据*/
    tBTA_BLE_SERVICE        *p_services;        /* 16位服务*/
    tBTA_BLE_128SERVICE     *p_services_128b;   /* 128位服务*/
    tBTA_BLE_32SERVICE      *p_service_32b;     /* 32位服务UUID*/
    tBTA_BLE_SERVICE        *p_sol_services;    /* 16位服务请求UUID*/
    tBTA_BLE_32SERVICE      *p_sol_service_32b; /* 32位服务请求UUID列表*/
    tBTA_BLE_128SERVICE     *p_sol_service_128b;/* 128位服务请求UUID列表*/
    tBTA_BLE_PROPRIETARY    *p_proprietary;     /* 专有数据*/
    tBTA_BLE_SERVICE_DATA   *p_service_data;    /* 服务数据*/
    UINT16                  appearance;         /* 外观数据*/
    UINT8                   flag;
    UINT8                   tx_power;
} tBTA_BLE_ADV_DATA;

typedef void (tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK) (tBTA_STATUS status, uint8_t subcode, uint32_t length, uint8_t *device_info);

typedef void (tBTA_SET_ADV_DATA_CMPL_CBACK) (tBTA_STATUS status);

typedef tBTM_START_ADV_CMPL_CBACK tBTA_START_ADV_CMPL_CBACK;

typedef tBTM_START_STOP_ADV_CMPL_CBACK tBTA_START_STOP_ADV_CMPL_CBACK;

typedef tBTM_ADD_WHITELIST_CBACK tBTA_ADD_WHITELIST_CBACK;

typedef tBTM_SET_PKT_DATA_LENGTH_CBACK tBTA_SET_PKT_DATA_LENGTH_CBACK;

typedef tBTM_SET_RAND_ADDR_CBACK tBTA_SET_RAND_ADDR_CBACK;

typedef tBTM_SET_LOCAL_PRIVACY_CBACK tBTA_SET_LOCAL_PRIVACY_CBACK;

typedef tBTM_CMPL_CB tBTA_CMPL_CB;

typedef tBTM_TX_POWER_RESULTS tBTA_TX_POWER_RESULTS;

typedef tBTM_RSSI_RESULTS tBTA_RSSI_RESULTS;

typedef tBTM_SET_AFH_CHANNELS_RESULTS tBTA_SET_AFH_CHANNELS_RESULTS;
typedef tBTM_BLE_SET_CHANNELS_RESULTS tBTA_BLE_SET_CHANNELS_RESULTS;

typedef tBTM_REMOTE_DEV_NAME tBTA_REMOTE_DEV_NAME;

/* 广告频道图*/
#define BTA_BLE_ADV_CHNL_37 BTM_BLE_ADV_CHNL_37
#define BTA_BLE_ADV_CHNL_38 BTM_BLE_ADV_CHNL_38
#define BTA_BLE_ADV_CHNL_39 BTM_BLE_ADV_CHNL_39
typedef tBTM_BLE_ADV_CHNL_MAP tBTA_BLE_ADV_CHNL_MAP; /* 用作位掩码*/

/* 广告筛选策略*/
typedef tBTM_BLE_AFP   tBTA_BLE_AFP;

/* adv事件类型*/
#define BTA_BLE_CONNECT_EVT         BTM_BLE_CONNECT_EVT     /* 可连接的无方向广告*/
#define BTA_BLE_CONNECT_DIR_EVT     BTM_BLE_CONNECT_DIR_EVT /* 可连接的定向广告*/
#define BTA_BLE_DISCOVER_EVT        BTM_BLE_DISCOVER_EVT    /* 无良广告*/
#define BTA_BLE_NON_CONNECT_EVT     BTM_BLE_NON_CONNECT_EVT /* 不可连接的无定向广告*/
typedef UINT8 tBTA_BLE_ADV_EVT;

/* adv tx功率电平*/
#define BTA_BLE_ADV_TX_POWER_MIN        0           /* 最小发射功率*/
#define BTA_BLE_ADV_TX_POWER_LOW        1           /* 低发射功率*/
#define BTA_BLE_ADV_TX_POWER_MID        2           /* 中间tx功率*/
#define BTA_BLE_ADV_TX_POWER_UPPER      3           /* 上tx功率*/
#define BTA_BLE_ADV_TX_POWER_MAX        4           /* 最大发射功率*/
typedef UINT8 tBTA_BLE_ADV_TX_POWER;

/* 广告实例参数*/
typedef struct {
    UINT16                  adv_int_min;            /* 最小adv间隔*/
    UINT16                  adv_int_max;            /* 最大adv间隔*/
    tBTA_BLE_ADV_EVT        adv_type;               /* adv事件类型*/
    tBTA_BLE_ADV_CHNL_MAP   channel_map;            /* adv频道图*/
    tBTA_BLE_AFP            adv_filter_policy;      /* 广告筛选策略*/
    tBTA_BLE_ADV_TX_POWER   tx_power;               /* adv tx电源*/
} tBTA_BLE_ADV_PARAMS;

/* 这些是每个设备adv数据包中返回的字段。如果已注册，则在结果回调中返回。
*/
typedef struct {
    UINT8               conn_mode;
    tBTA_BLE_AD_MASK    ad_mask;        /* 有效adv数据字段的掩码*/
    UINT8               flag;
    UINT8               tx_power_level;
    UINT8               remote_name_len;
    UINT8               *p_remote_name;
    tBTA_BLE_SERVICE    service;
} tBTA_BLE_INQ_DATA;

enum {
    BTA_BLE_BATCH_SCAN_MODE_PASS = 1,
    BTA_BLE_BATCH_SCAN_MODE_ACTI = 2,
    BTA_BLE_BATCH_SCAN_MODE_PASS_ACTI = 3
};
typedef UINT8 tBTA_BLE_BATCH_SCAN_MODE;

enum {
    BTA_BLE_DISCARD_OLD_ITEMS = 0,
    BTA_BLE_DISCARD_LOWER_RSSI_ITEMS = 1
};
typedef UINT8 tBTA_BLE_DISCARD_RULE;

enum {
    BTA_BLE_ADV_SEEN_FIRST_TIME = 0,
    BTA_BLE_ADV_TRACKING_TIMEOUT = 1
};
typedef UINT8 tBTA_BLE_ADV_CHANGE_REASON;

enum {
    BTA_BLE_BATCH_SCAN_ENB_EVT      = 1,
    BTA_BLE_BATCH_SCAN_CFG_STRG_EVT = 2,
    BTA_BLE_BATCH_SCAN_DATA_EVT     = 3,
    BTA_BLE_BATCH_SCAN_THRES_EVT    = 4,
    BTA_BLE_BATCH_SCAN_PARAM_EVT    = 5,
    BTA_BLE_BATCH_SCAN_DIS_EVT      = 6
};
typedef tBTM_BLE_BATCH_SCAN_EVT tBTA_BLE_BATCH_SCAN_EVT;

typedef tBTM_BLE_TRACK_ADV_ACTION tBTA_BLE_TRACK_ADV_ACTION;
// #结束符

/* BLE客户特定功能功能类型定义*/
/* 用于RSSI监控的客户特定功能的数据类型*/
#define BTA_BLE_RSSI_ALERT_HI        0
#define BTA_BLE_RSSI_ALERT_RANGE     1
#define BTA_BLE_RSSI_ALERT_LO        2
typedef UINT8 tBTA_DM_BLE_RSSI_ALERT_TYPE;

#define BTA_BLE_RSSI_ALERT_NONE         BTM_BLE_RSSI_ALERT_NONE         /*    (0) */
#define BTA_BLE_RSSI_ALERT_HI_BIT       BTM_BLE_RSSI_ALERT_HI_BIT       /*    (1) */
#define BTA_BLE_RSSI_ALERT_RANGE_BIT    BTM_BLE_RSSI_ALERT_RANGE_BIT    /*    (1 << 1) */
#define BTA_BLE_RSSI_ALERT_LO_BIT       BTM_BLE_RSSI_ALERT_LO_BIT       /*    (1 << 2) */
typedef UINT8     tBTA_DM_BLE_RSSI_ALERT_MASK;


typedef void (tBTA_DM_BLE_RSSI_CBACK) (BD_ADDR bd_addr, tBTA_DM_BLE_RSSI_ALERT_TYPE alert_type, INT8 rssi);

/* 不同过滤器类型的最大过滤点数量*/
#define BTA_DM_BLE_MAX_UUID_FILTER     BTM_BLE_MAX_UUID_FILTER    /* 8 */
#define BTA_DM_BLE_MAX_ADDR_FILTER     BTM_BLE_MAX_ADDR_FILTER    /* 8 */
#define BTA_DM_BLE_PF_STR_COND_MAX     BTM_BLE_PF_STR_COND_MAX    /* 4适用于manu数据或本地名称*/
#define BTA_DM_BLE_PF_STR_LEN_MAX      BTM_BLE_PF_STR_LEN_MAX     /* 匹配前20个字节*/

#define BTA_DM_BLE_PF_LOGIC_OR              0
#define BTA_DM_BLE_PF_LOGIC_AND             1
typedef UINT8 tBTA_DM_BLE_PF_LOGIC_TYPE;

enum {
    BTA_DM_BLE_SCAN_COND_ADD,
    BTA_DM_BLE_SCAN_COND_DELETE,
    BTA_DM_BLE_SCAN_COND_CLEAR = 2
};
typedef UINT8 tBTA_DM_BLE_SCAN_COND_OP;

/* ADV负载过滤供应商特定呼叫事件*/
enum {
    BTA_BLE_SCAN_PF_ENABLE_EVT = 7,
    BTA_BLE_SCAN_PF_COND_EVT
};

/* 滤波器选择位索引*/
#define BTA_DM_BLE_PF_ADDR_FILTER          BTM_BLE_PF_ADDR_FILTER
#define BTA_DM_BLE_PF_SRVC_DATA            BTM_BLE_PF_SRVC_DATA
#define BTA_DM_BLE_PF_SRVC_UUID            BTM_BLE_PF_SRVC_UUID
#define BTA_DM_BLE_PF_SRVC_SOL_UUID        BTM_BLE_PF_SRVC_SOL_UUID
#define BTA_DM_BLE_PF_LOCAL_NAME           BTM_BLE_PF_LOCAL_NAME
#define BTA_DM_BLE_PF_MANU_DATA            BTM_BLE_PF_MANU_DATA
#define BTA_DM_BLE_PF_SRVC_DATA_PATTERN    BTM_BLE_PF_SRVC_DATA_PATTERN
#define BTA_DM_BLE_PF_TYPE_ALL             BTM_BLE_PF_TYPE_ALL
#define BTA_DM_BLE_PF_TYPE_MAX             BTM_BLE_PF_TYPE_MAX
typedef UINT8   tBTA_DM_BLE_PF_COND_TYPE;

typedef union {
    UINT16              uuid16_mask;
    UINT32              uuid32_mask;
    UINT8               uuid128_mask[LEN_UUID_128];
} tBTA_DM_BLE_PF_COND_MASK;

typedef struct {
    tBLE_BD_ADDR                *p_target_addr;     /* 目标地址，如果为NULL，则为通用UUID筛选器*/
    tBT_UUID                    uuid;           /* UUID条件*/
    tBTA_DM_BLE_PF_LOGIC_TYPE   cond_logic;    /* AND/OR */
    tBTA_DM_BLE_PF_COND_MASK    *p_uuid_mask;           /* UUID条件掩码，如果为NULL，则与UUID条件完全匹配*/
} tBTA_DM_BLE_PF_UUID_COND;

typedef struct {
    UINT8                   data_len;       /* <=20字节*/
    UINT8                   *p_data;
} tBTA_DM_BLE_PF_LOCAL_NAME_COND;

typedef struct {
    UINT16                  company_id;     /* 公司ID*/
    UINT8                   data_len;       /* <=20字节*/
    UINT8                   *p_pattern;
    UINT16                  company_id_mask; /* UUID值掩码*/
    UINT8                   *p_pattern_mask; /* 制造商数据匹配掩码，长度与数据模式相同，设置为所有0xff，匹配精确数据*/
} tBTA_DM_BLE_PF_MANU_COND;

typedef struct {
    UINT16                  uuid;     /* 服务ID*/
    UINT8                   data_len;       /* <=20字节*/
    UINT8                   *p_pattern;
    UINT8                   *p_pattern_mask; /* 服务数据匹配掩码，长度与数据模式相同，设置为所有0xff，匹配精确数据*/
} tBTA_DM_BLE_PF_SRVC_PATTERN_COND;

typedef union {
    tBLE_BD_ADDR                            target_addr;
    tBTA_DM_BLE_PF_LOCAL_NAME_COND             local_name; /* 本地名称筛选*/
    tBTA_DM_BLE_PF_MANU_COND                   manu_data;  /* 制造商数据过滤*/
    tBTA_DM_BLE_PF_UUID_COND                   srvc_uuid;  /* 服务UUID筛选*/
    tBTA_DM_BLE_PF_UUID_COND                   solicitate_uuid;   /* 请求服务UUID筛选*/
    tBTA_DM_BLE_PF_SRVC_PATTERN_COND           srvc_data;      /* 服务数据模式*/
} tBTA_DM_BLE_PF_COND_PARAM;

typedef UINT8 tBTA_DM_BLE_PF_FILT_INDEX;
typedef UINT8 tBTA_DM_BLE_PF_AVBL_SPACE;

typedef INT8 tBTA_DM_RSSI_VALUE;
typedef UINT8 tBTA_DM_LINK_QUALITY_VALUE;


typedef UINT8 tBTA_SIG_STRENGTH_MASK;


/* 安全回调事件*/
#define BTA_DM_ENABLE_EVT               0       /* 启用事件*/
#define BTA_DM_DISABLE_EVT              1       /* 禁用事件*/
#define BTA_DM_PIN_REQ_EVT              2       /* PIN请求。*/
#define BTA_DM_AUTH_CMPL_EVT            3       /* 认证完成指示。*/
#define BTA_DM_AUTHORIZE_EVT            4       /* 授权请求。*/
#define BTA_DM_LINK_UP_EVT              5       /* 连接UP事件*/
#define BTA_DM_LINK_DOWN_EVT            6       /* 连接DOWN事件*/
#define BTA_DM_SIG_STRENGTH_EVT         7       /* 蓝牙连接的信号强度*/
#define BTA_DM_BUSY_LEVEL_EVT           8       /* 系统繁忙级别*/
#define BTA_DM_BOND_CANCEL_CMPL_EVT     9       /* 债券取消完成指示*/
#define BTA_DM_SP_CFM_REQ_EVT           10      /* 简单配对用户确认请求。*/
#define BTA_DM_SP_KEY_NOTIF_EVT         11      /* 简单配对密钥通知*/
#define BTA_DM_SP_RMT_OOB_EVT           12      /* 简单配对远程OOB数据请求。*/
#define BTA_DM_SP_KEYPRESS_EVT          13      /* 按键通知事件。*/
#define BTA_DM_ROLE_CHG_EVT             14      /* 角色更改事件。*/
#define BTA_DM_BLE_KEY_EVT              15      /* 对等设备密钥的BLE SMP密钥事件*/
#define BTA_DM_BLE_SEC_REQ_EVT          16      /* BLE SMP安全请求*/
#define BTA_DM_BLE_PASSKEY_NOTIF_EVT    17      /* SMP密钥通知事件*/
#define BTA_DM_BLE_PASSKEY_REQ_EVT      18      /* SMP密钥请求事件*/
#define BTA_DM_BLE_OOB_REQ_EVT          19      /* SMP OOB请求事件*/
#define BTA_DM_BLE_LOCAL_IR_EVT         20      /* BLE本地IR事件*/
#define BTA_DM_BLE_LOCAL_ER_EVT         21      /* BLE本地ER事件*/
#define BTA_DM_BLE_NC_REQ_EVT           22      /* SMP数字比较请求事件*/
// btla特定++
#define BTA_DM_SP_RMT_OOB_EXT_EVT       23      /* 简单配对远程OOB扩展数据请求。*/
#define BTA_DM_BLE_AUTH_CMPL_EVT        24      /* BLE身份验证完成*/
// btla特定--
#define BTA_DM_DEV_UNPAIRED_EVT         25      /* BT取消配对事件*/
#define BTA_DM_HW_ERROR_EVT             26      /* BT芯片H/W错误*/
#define BTA_DM_LE_FEATURES_READ         27      /* 读取胶辊特定的LE特征*/
#define BTA_DM_ENER_INFO_READ           28      /* 能量信息读取*/
#define BTA_DM_BLE_DEV_UNPAIRED_EVT     29      /* BLE取消配对事件*/
#define BTA_DM_SP_KEY_REQ_EVT           30      /* 简单配对密钥请求*/
#define BTA_DM_PM_MODE_CHG_EVT          31      /* 模式更改事件*/

typedef UINT8 tBTA_DM_SEC_EVT;

/* 与BTA_DM_ENABLE_EVT相关的结构*/
typedef struct {
    tBTA_STATUS    status;
} tBTA_DM_ENABLE;

/* 与BTA_DM_PIN_REQ_EVT相关的结构*/
typedef struct {
    /* 注意：前3个数据成员必须依次为bd_addr、dev_class和bd_name*/
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
    DEV_CLASS       dev_class;          /* 设备类别*/
    BD_NAME         bd_name;            /* 对等设备的名称。*/
    BOOLEAN         min_16_digit;       /* 如果返回的引脚必须至少为16位，则为TRUE*/
} tBTA_DM_PIN_REQ;

/* BLE相关定义*/
#if (SMP_INCLUDED == TRUE)
#define BTA_DM_AUTH_FAIL_BASE                   (HCI_ERR_MAX_ERR + 10)
#define BTA_DM_AUTH_CONVERT_SMP_CODE(x)        (BTA_DM_AUTH_FAIL_BASE + (x))
#define BTA_DM_AUTH_SMP_PASSKEY_FAIL             BTA_DM_AUTH_CONVERT_SMP_CODE (SMP_PASSKEY_ENTRY_FAIL)
#define BTA_DM_AUTH_SMP_OOB_FAIL                (BTA_DM_AUTH_FAIL_BASE + SMP_OOB_FAIL)
#define BTA_DM_AUTH_SMP_PAIR_AUTH_FAIL          (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_AUTH_FAIL)
#define BTA_DM_AUTH_SMP_CONFIRM_VALUE_FAIL      (BTA_DM_AUTH_FAIL_BASE + SMP_CONFIRM_VALUE_ERR)
#define BTA_DM_AUTH_SMP_PAIR_NOT_SUPPORT        (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_NOT_SUPPORT)
#define BTA_DM_AUTH_SMP_ENC_KEY_SIZE            (BTA_DM_AUTH_FAIL_BASE + SMP_ENC_KEY_SIZE)
#define BTA_DM_AUTH_SMP_INVALID_CMD             (BTA_DM_AUTH_FAIL_BASE + SMP_INVALID_CMD)
#define BTA_DM_AUTH_SMP_UNKNOWN_ERR             (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_FAIL_UNKNOWN)
#define BTA_DM_AUTH_SMP_REPEATED_ATTEMPT        (BTA_DM_AUTH_FAIL_BASE + SMP_REPEATED_ATTEMPTS)
#define BTA_DM_AUTH_SMP_INVALID_PARAMETERS      (BTA_DM_AUTH_FAIL_BASE + SMP_INVALID_PARAMETERS)
#define BTA_DM_AUTH_SMP_INTERNAL_ERR            (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_INTERNAL_ERR)
#define BTA_DM_AUTH_SMP_UNKNOWN_IO              (BTA_DM_AUTH_FAIL_BASE + SMP_UNKNOWN_IO_CAP)
#define BTA_DM_AUTH_SMP_INIT_FAIL               (BTA_DM_AUTH_FAIL_BASE + SMP_INIT_FAIL)
#define BTA_DM_AUTH_SMP_CONFIRM_FAIL            (BTA_DM_AUTH_FAIL_BASE + SMP_CONFIRM_FAIL)
#define BTA_DM_AUTH_SMP_BUSY                    (BTA_DM_AUTH_FAIL_BASE + SMP_BUSY)
#define BTA_DM_AUTH_SMP_ENC_FAIL                (BTA_DM_AUTH_FAIL_BASE + SMP_ENC_FAIL)
#define BTA_DM_AUTH_SMP_RSP_TIMEOUT             (BTA_DM_AUTH_FAIL_BASE + SMP_RSP_TIMEOUT)
#endif  ///SMP_INCLUDED == TRUE
/* 连接参数边界值和虚设值*/
#define BTA_DM_BLE_SCAN_INT_MIN          BTM_BLE_SCAN_INT_MIN
#define BTA_DM_BLE_SCAN_INT_MAX          BTM_BLE_SCAN_INT_MAX
#define BTA_DM_BLE_SCAN_WIN_MIN          BTM_BLE_SCAN_WIN_MIN
#define BTA_DM_BLE_SCAN_WIN_MAX          BTM_BLE_SCAN_WIN_MAX
#define BTA_DM_BLE_CONN_INT_MIN          BTM_BLE_CONN_INT_MIN
#define BTA_DM_BLE_CONN_INT_MAX          BTM_BLE_CONN_INT_MAX
#define BTA_DM_BLE_CONN_LATENCY_MAX      BTM_BLE_CONN_LATENCY_MAX
#define BTA_DM_BLE_CONN_SUP_TOUT_MIN     BTM_BLE_CONN_SUP_TOUT_MIN
#define BTA_DM_BLE_CONN_SUP_TOUT_MAX     BTM_BLE_CONN_SUP_TOUT_MAX
#define BTA_DM_BLE_CONN_PARAM_UNDEF      BTM_BLE_CONN_PARAM_UNDEF  /* 在不覆盖特定值时使用此值*/

#if (SMP_INCLUDED == TRUE)
#define BTA_LE_KEY_PENC      BTM_LE_KEY_PENC  /* 对等设备的加密信息*/
#define BTA_LE_KEY_PID       BTM_LE_KEY_PID   /* 对等设备的身份密钥*/
#define BTA_LE_KEY_PCSRK     BTM_LE_KEY_PCSRK   /* 对等SRK*/
#define BTA_LE_KEY_LENC      BTM_LE_KEY_LENC        /* 主角色安全信息：div*/
#define BTA_LE_KEY_LID       BTM_LE_KEY_LID         /* 主设备ID密钥*/
#define BTA_LE_KEY_LCSRK     BTM_LE_KEY_LCSRK        /* 本地CSRK已交付给同行*/
#endif  ///SMP_INCLUDED == TRUE
typedef UINT8 tBTA_LE_KEY_TYPE; /* 可以用作位掩码*/


typedef tBTM_LE_PENC_KEYS  tBTA_LE_PENC_KEYS ;
typedef tBTM_LE_PCSRK_KEYS tBTA_LE_PCSRK_KEYS;
typedef tBTM_LE_LENC_KEYS  tBTA_LE_LENC_KEYS  ;
typedef tBTM_LE_LCSRK_KEYS tBTA_LE_LCSRK_KEYS ;
typedef tBTM_LE_PID_KEYS   tBTA_LE_PID_KEYS ;

typedef union {
    tBTA_LE_PENC_KEYS   penc_key;       /* 收到的对等加密密钥*/
    tBTA_LE_PCSRK_KEYS  psrk_key;       /* 接收的对等设备SRK*/
    tBTA_LE_PID_KEYS    pid_key;        /* 对等设备ID密钥*/
    tBTA_LE_LENC_KEYS   lenc_key;       /* 本地加密再现密钥LTK==d1（ER，DIV，0）*/
    tBTA_LE_LCSRK_KEYS  lcsrk_key;      /* 本地设备CSRK=d1（ER，DIV，1）*/
    tBTA_LE_PID_KEYS    lid_key;        /* 特定远程设备的本地设备ID密钥*/
} tBTA_LE_KEY_VALUE;

#define BTA_BLE_LOCAL_KEY_TYPE_ID         1
#define BTA_BLE_LOCAL_KEY_TYPE_ER         2
typedef UINT8 tBTA_DM_BLE_LOCAL_KEY_MASK;

typedef struct {
    BT_OCTET16       ir;
    BT_OCTET16       irk;
    BT_OCTET16       dhk;
} tBTA_BLE_LOCAL_ID_KEYS;
#if (SMP_INCLUDED == TRUE)
#define BTA_DM_SEC_GRANTED              BTA_SUCCESS
#define BTA_DM_SEC_PAIR_NOT_SPT         BTA_DM_AUTH_SMP_PAIR_NOT_SUPPORT
#define BTA_DM_SEC_REP_ATTEMPTS         BTA_DM_AUTH_SMP_REPEATED_ATTEMPT
#endif  ///SMP_INCLUDED == TRUE
typedef UINT8 tBTA_DM_BLE_SEC_GRANT;


#define BTA_DM_BLE_ONN_NONE             BTM_BLE_CONN_NONE
#define BTA_DM_BLE_CONN_AUTO            BTM_BLE_CONN_AUTO
#define BTA_DM_BLE_CONN_SELECTIVE       BTM_BLE_CONN_SELECTIVE
typedef UINT8 tBTA_DM_BLE_CONN_TYPE;

typedef BOOLEAN (tBTA_DM_BLE_SEL_CBACK)(BD_ADDR random_bda, UINT8 *p_remote_name);

typedef tBTM_LE_UPDATE_CONN_PRAMS tBTA_LE_UPDATE_CONN_PRAMS;
typedef tBTM_UPDATE_CONN_PARAM_CBACK tBTA_UPDATE_CONN_PARAM_CBACK;


/* 与BTA_DM_BLE_SEC_REQ_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    BD_NAME         bd_name;        /* 对等设备名称*/
} tBTA_DM_BLE_SEC_REQ;

typedef struct {
    BD_ADDR                 bd_addr;        /* 对等地址*/
    tBTM_LE_KEY_TYPE        key_type;
    tBTM_LE_KEY_VALUE       *p_key_value;
} tBTA_DM_BLE_KEY;

/* 与BTA_DM_AUTH_CMPL_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
    BD_NAME         bd_name;            /* 对等设备的名称。*/
    BOOLEAN         key_present;        /* 键元素中的有效链接键值*/
    LINK_KEY        key;                /* 与对等设备关联的链接密钥。*/
    UINT8           key_type;           /* 链接密钥的类型*/
    BOOLEAN         success;            /* 验证成功为TRUE，失败为FALSE。*/
    UINT8           fail_reason;        /* 成功=FALSE时的HCI原因/错误代码*/
    tBLE_ADDR_TYPE  addr_type;          /* 对等设备地址类型*/
    tBT_DEVICE_TYPE dev_type;
    UINT8           auth_mode;
    BOOLEAN           sc_support;         /* 表示绑定时对等设备是否支持安全连接。*/
} tBTA_DM_AUTH_CMPL;


/* 与BTA_DM_AUTHORIZE_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
    BD_NAME         bd_name;            /* 对等设备的名称。*/
    tBTA_SERVICE_ID service;            /* 要授权的服务ID。*/
// btla特定++
    DEV_CLASS      dev_class;
// btla特定--
} tBTA_DM_AUTHORIZE;

/* 与BTA_DM_LINK_UP_EVT相关的结构*/
typedef struct {
    BOOLEAN         sc_downgrade;       /* 安全降级状态。*/
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
#if BLE_INCLUDED == TRUE
    tBTA_TRANSPORT  link_type;
#endif
} tBTA_DM_LINK_UP;

/* 与BTA_DM_LINK_DOWN_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
    UINT8           status;             /* 连接打开/关闭*/
    UINT8           reason;             /* 链接关闭原因*/
    BOOLEAN         is_removed;         /* 如果链接关闭时删除设备，则为TRUE*/
#if BLE_INCLUDED == TRUE
    tBTA_TRANSPORT  link_type;
#endif
} tBTA_DM_LINK_DOWN;

/* 与BTA_DM_ROLE_CHG_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
    UINT8           new_role;           /* 新的连接角色*/
} tBTA_DM_ROLE_CHG;

/* 与BTA_DM_BUSY_LEVEL_EVT相关的结构*/
typedef struct {
    UINT8           level;     /* 分页或查询时，级别为10。否则，ACL链接数*/
    UINT8           level_flags; /* 表示单个标志*/
} tBTA_DM_BUSY_LEVEL;

#define BTA_IO_CAP_OUT      BTM_IO_CAP_OUT      /* 0仅显示*/
#define BTA_IO_CAP_IO       BTM_IO_CAP_IO       /* 1显示是否*/
#define BTA_IO_CAP_IN       BTM_IO_CAP_IN       /* 仅限2个键盘*/
#define BTA_IO_CAP_NONE     BTM_IO_CAP_NONE     /* 3无输入无输出*/
#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
#define BTA_IO_CAP_KBDISP   BTM_IO_CAP_KBDISP   /* 4键盘显示*/
#endif
typedef tBTM_IO_CAP     tBTA_IO_CAP;

#define BTA_AUTH_SP_NO    BTM_AUTH_SP_NO      /* 0不需要MITM保护-单剖面/无粘结数字比较，允许自动接受*/
#define BTA_AUTH_SP_YES   BTM_AUTH_SP_YES     /* 需要1个MITM保护-单配置文件/非绑定使用IO功能确定身份验证程序*/
#define BTA_AUTH_AP_NO    BTM_AUTH_AP_NO      /* 2不需要MITM保护-所有配置文件/专用键合数字比较，允许自动接受*/
#define BTA_AUTH_AP_YES   BTM_AUTH_AP_YES     /* 3需要MITM保护-所有配置文件/专用绑定使用IO功能来确定身份验证程序*/
#define BTA_AUTH_SPGB_NO  BTM_AUTH_SPGB_NO    /* 4不需要MITM保护-单个配置文件/通用键合数字比较，允许自动接受*/
#define BTA_AUTH_SPGB_YES BTM_AUTH_SPGB_YES   /* 5需要MITM保护-单一配置文件/通用绑定使用IO功能确定身份验证程序*/
typedef tBTM_AUTH_REQ   tBTA_AUTH_REQ;

#define BTA_AUTH_DD_BOND    BTM_AUTH_DD_BOND  /* 2此位设置为专用键合*/
#define BTA_AUTH_GEN_BOND   BTM_AUTH_SPGB_NO  /* 4此钻头用于普通粘接*/
#define BTA_AUTH_BONDS      BTM_AUTH_BONDS    /* 6通用/专用粘结钻头*/

#if (SMP_INCLUDED == TRUE)
#define BTA_LE_AUTH_NO_BOND    BTM_LE_AUTH_REQ_NO_BOND  /* 0*/
#define BTA_LE_AUTH_BOND       BTM_LE_AUTH_REQ_BOND     /* 1 << 0 */
#define BTA_LE_AUTH_REQ_MITM   BTM_LE_AUTH_REQ_MITM    /* 1 << 2 */

#define BTA_LE_AUTH_REQ_SC_ONLY         BTM_LE_AUTH_REQ_SC_ONLY         /* 1 << 3 */
#define BTA_LE_AUTH_REQ_SC_BOND         BTM_LE_AUTH_REQ_SC_BOND      /* 1001 */
#define BTA_LE_AUTH_REQ_SC_MITM         BTM_LE_AUTH_REQ_SC_MITM      /* 1100 */
#define BTA_LE_AUTH_REQ_SC_MITM_BOND    BTM_LE_AUTH_REQ_SC_MITM_BOND /* 1101 */
#endif  ///SMP_INCLUDED == TRUE
typedef tBTM_LE_AUTH_REQ       tBTA_LE_AUTH_REQ;       /* 上述位模式的组合*/

#define BTA_OOB_NONE        BTM_OOB_NONE
#define BTA_OOB_PRESENT     BTM_OOB_PRESENT
#if BTM_OOB_INCLUDED == TRUE
#define BTA_OOB_UNKNOWN     BTM_OOB_UNKNOWN
#endif
typedef tBTM_OOB_DATA   tBTA_OOB_DATA;

#define BTA_PM_MD_ACTIVE    BTM_PM_MD_ACTIVE    /* 0活动模式*/
#define BTA_PM_MD_HOLD      BTM_PM_MD_HOLD      /* 1保持模式*/
#define BTA_PM_MD_SNIFF     BTM_PM_MD_SNIFF     /* 2嗅探模式*/
#define BTA_PM_MD_PARK      BTM_PM_MD_PARK      /* 3驻车状态*/
typedef tBTM_PM_MODE tBTA_PM_MODE;

/* 与BTA_DM_SP_CFM_REQ_EVT相关的结构*/
typedef struct {
    /* 注意：前3个数据成员必须依次为bd_addr、dev_class和bd_name*/
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    BD_NAME         bd_name;        /* 对等设备名称*/
    UINT32          num_val;        /* 用于比较的数值。如果just_works，则不向UI显示此数字*/
    BOOLEAN         just_works;     /* TRUE，如果“Just Works”关联模型*/
    tBTA_AUTH_REQ   loc_auth_req;   /* 本地设备需要身份验证*/
    tBTA_AUTH_REQ   rmt_auth_req;   /* 对等设备需要身份验证*/
    tBTA_IO_CAP     loc_io_caps;    /* 本地设备的IO功能*/
    tBTA_AUTH_REQ   rmt_io_caps;    /* 远程设备的IO功能*/
} tBTA_DM_SP_CFM_REQ;

/* 与tBTA_DM_SP_KEY_REQ相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    BD_NAME         bd_name;        /* 对等设备名称*/
} tBTA_DM_SP_KEY_REQ;

enum {
    BTA_SP_KEY_STARTED,         /* 密钥输入已启动*/
    BTA_SP_KEY_ENTERED,         /* 输入密钥数字*/
    BTA_SP_KEY_ERASED,          /* 密钥数字已擦除*/
    BTA_SP_KEY_CLEARED,         /* 密钥已清除*/
    BTA_SP_KEY_COMPLT           /* 密钥输入已完成*/
};
typedef UINT8   tBTA_SP_KEY_TYPE;

/* 与BTA_DM_SP_KEYPRESS_EVT相关的结构*/
typedef struct {
    BD_ADDR             bd_addr;        /* 对等地址*/
    tBTA_SP_KEY_TYPE   notif_type;
} tBTA_DM_SP_KEY_PRESS;

/* 与BTA_DM_SP_KEY_NOTIF_EVT相关的结构*/
typedef struct {
    /* 注意：前3个数据成员必须依次为bd_addr、dev_class和bd_name*/
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    BD_NAME         bd_name;        /* 对等设备名称*/
    UINT32          passkey;        /* 用于比较的数值。如果just_works，则不向UI显示此数字*/
} tBTA_DM_SP_KEY_NOTIF;

/* 与BTA_DM_SP_RMT_OOB_EVT相关的结构*/
typedef struct {
    /* 注意：前3个数据成员必须依次为bd_addr、dev_class和bd_name*/
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    BD_NAME         bd_name;        /* 对等设备名称*/
} tBTA_DM_SP_RMT_OOB;

/* 与BTA_DM_BOND_CANCEL_CMPL_EVT关联的结构*/
typedef struct {
    tBTA_STATUS     result;    /* 债券取消成功为TRUE，失败为FALSE。*/
} tBTA_DM_BOND_CANCEL_CMPL;

/* 与BTA_DM_PM_MODE_HG_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;            /* BD地址对等设备。*/
    tBTA_PM_MODE    mode;               /* 新的连接角色*/
} tBTA_DM_MODE_CHG;


/* 所有安全回调结构的联合*/
typedef union {
    tBTA_DM_ENABLE              enable;             /* BTA已启用*/
    tBTA_DM_PIN_REQ             pin_req;            /* PIN请求。*/
    tBTA_DM_AUTH_CMPL           auth_cmpl;          /* 认证完成指示。*/
    tBTA_DM_AUTHORIZE           authorize;          /* 授权请求。*/
    tBTA_DM_LINK_UP             link_up;            /* ACL连接启动事件*/
    tBTA_DM_LINK_DOWN           link_down;          /* ACL连接关闭事件*/
    tBTA_DM_BUSY_LEVEL          busy_level;         /* 系统繁忙级别*/
    tBTA_DM_SP_CFM_REQ          cfm_req;            /* 用户确认请求*/
    tBTA_DM_SP_KEY_REQ          key_req;            /* 用户密钥请求*/
    tBTA_DM_SP_KEY_NOTIF        key_notif;          /* 密钥通知*/
    tBTA_DM_SP_RMT_OOB          rmt_oob;            /* 远程oob*/
    tBTA_DM_BOND_CANCEL_CMPL    bond_cancel_cmpl;   /* 债券取消完成指示*/
    tBTA_DM_SP_KEY_PRESS        key_press;          /* 按键通知事件*/
    tBTA_DM_ROLE_CHG            role_chg;           /* 角色更改事件*/
    tBTA_DM_BLE_SEC_REQ         ble_req;            /* BLE SMP相关请求*/
    tBTA_DM_BLE_KEY             ble_key;            /* 配对时使用的BLE SMP密钥*/
    tBTA_BLE_LOCAL_ID_KEYS      ble_id_keys;        /* IR事件*/
    BT_OCTET16                  ble_er;             /* ER事件数据*/
#if BTA_DM_PM_INCLUDED
    tBTA_DM_MODE_CHG            mode_chg;           /* 模式改变事件*/
#endif ///BTA_DM_PM_INCLUDED
} tBTA_DM_SEC;

/* 安全回调*/
typedef void (tBTA_DM_SEC_CBACK)(tBTA_DM_SEC_EVT event, tBTA_DM_SEC *p_data);

#define BTA_BLE_MULTI_ADV_ILLEGAL 0

/* 多adv回调事件*/
#define BTA_BLE_MULTI_ADV_ENB_EVT           1
#define BTA_BLE_MULTI_ADV_DISABLE_EVT       2
#define BTA_BLE_MULTI_ADV_PARAM_EVT         3
#define BTA_BLE_MULTI_ADV_DATA_EVT          4

typedef UINT8 tBTA_BLE_MULTI_ADV_EVT;

/* 多adv回调*/
typedef void (tBTA_BLE_MULTI_ADV_CBACK)(tBTA_BLE_MULTI_ADV_EVT event,
                                        UINT8 inst_id, void *p_ref, tBTA_STATUS status);
typedef UINT32 tBTA_DM_BLE_REF_VALUE;

#define BTA_DM_BLE_PF_ENABLE_EVT       BTM_BLE_PF_ENABLE
#define BTA_DM_BLE_PF_CONFIG_EVT       BTM_BLE_PF_CONFIG
typedef UINT8 tBTA_DM_BLE_PF_EVT;

#define BTA_DM_BLE_PF_ENABLE       1
#define BTA_DM_BLE_PF_CONFIG       2
typedef UINT8 tBTA_DM_BLE_PF_ACTION;

/* 配置回调*/
typedef void (tBTA_DM_BLE_PF_CFG_CBACK) (tBTA_DM_BLE_PF_ACTION action,
        tBTA_DM_BLE_PF_COND_TYPE cfg_cond,
        tBTA_DM_BLE_PF_AVBL_SPACE avbl_space, tBTA_STATUS status,
        tBTA_DM_BLE_REF_VALUE ref_value);
/* Param回调*/
typedef void (tBTA_DM_BLE_PF_PARAM_CBACK) (UINT8 action_type, tBTA_DM_BLE_PF_AVBL_SPACE avbl_space,
        tBTA_DM_BLE_REF_VALUE ref_value, tBTA_STATUS status);

/* 状态回调*/
typedef void (tBTA_DM_BLE_PF_STATUS_CBACK) (UINT8 action, tBTA_STATUS status,
        tBTA_DM_BLE_REF_VALUE ref_value);


#define BTA_DM_BLE_PF_BRDCAST_ADDR_FILT  1
#define BTA_DM_BLE_PF_SERV_DATA_CHG_FILT 2
#define BTA_DM_BLE_PF_SERV_UUID          4
#define BTA_DM_BLE_PF_SERV_SOLC_UUID     8
#define BTA_DM_BLE_PF_LOC_NAME_CHECK    16
#define BTA_DM_BLE_PF_MANUF_NAME_CHECK  32
#define BTA_DM_BLE_PF_SERV_DATA_CHECK   64
typedef UINT16 tBTA_DM_BLE_PF_FEAT_SEL;

#define BTA_DM_BLE_PF_LIST_LOGIC_OR   1
#define BTA_DM_BLE_PF_LIST_LOGIC_AND  2
typedef UINT16 tBTA_DM_BLE_PF_LIST_LOGIC_TYPE;

#define BTA_DM_BLE_PF_FILT_LOGIC_OR   0
#define BTA_DM_BLE_PF_FILT_LOGIC_AND  1
typedef UINT16 tBTA_DM_BLE_PF_FILT_LOGIC_TYPE;

typedef UINT8  tBTA_DM_BLE_PF_RSSI_THRESHOLD;
typedef UINT8  tBTA_DM_BLE_PF_DELIVERY_MODE;
typedef UINT16 tBTA_DM_BLE_PF_TIMEOUT;
typedef UINT8  tBTA_DM_BLE_PF_TIMEOUT_CNT;
typedef UINT16 tBTA_DM_BLE_PF_ADV_TRACK_ENTRIES;

typedef struct {
    tBTA_DM_BLE_PF_FEAT_SEL feat_seln;
    tBTA_DM_BLE_PF_LIST_LOGIC_TYPE list_logic_type;
    tBTA_DM_BLE_PF_FILT_LOGIC_TYPE filt_logic_type;
    tBTA_DM_BLE_PF_RSSI_THRESHOLD  rssi_high_thres;
    tBTA_DM_BLE_PF_RSSI_THRESHOLD  rssi_low_thres;
    tBTA_DM_BLE_PF_DELIVERY_MODE dely_mode;
    tBTA_DM_BLE_PF_TIMEOUT found_timeout;
    tBTA_DM_BLE_PF_TIMEOUT lost_timeout;
    tBTA_DM_BLE_PF_TIMEOUT_CNT found_timeout_cnt;
    tBTA_DM_BLE_PF_ADV_TRACK_ENTRIES num_of_tracking_entries;
} tBTA_DM_BLE_PF_FILT_PARAMS;

/* 搜索回调事件*/
#define BTA_DM_INQ_RES_EVT              0       /* 对等设备的查询结果。*/
#define BTA_DM_INQ_CMPL_EVT             1       /* 查询完成。*/
#define BTA_DM_DISC_RES_EVT             2       /* 对等设备的发现结果。*/
#define BTA_DM_DISC_BLE_RES_EVT         3       /* 对等设备上基于BLE GATT的伺服的发现结果。*/
#define BTA_DM_DISC_CMPL_EVT            4       /* 发现完成。*/
#define BTA_DM_DI_DISC_CMPL_EVT         5       /* 发现完成。*/
#define BTA_DM_SEARCH_CANCEL_CMPL_EVT   6       /* 搜索已取消*/
#define BTA_DM_INQ_DISCARD_NUM_EVT      7       /* 查询丢弃的数据包数*/

typedef UINT8 tBTA_DM_SEARCH_EVT;

#define BTA_DM_INQ_RES_IGNORE_RSSI      BTM_INQ_RES_IGNORE_RSSI /* 未提供0x7f RSSI值（忽略它）*/

/* 与BTA_DM_INQ_RES_EVT相关的结构*/
typedef struct {
    BD_ADDR         bd_addr;                /* BD地址对等设备。*/
    DEV_CLASS       dev_class;              /* 对等设备的设备类。*/
    BOOLEAN         remt_name_not_required; /* 如果应用程序已经知道设备的名称，则设置此标志*/
    /* 如果应用程序知道设备名称，BTA将跳过远程名称请求*/
    BOOLEAN         is_limited;             /* TRUE，如果CoD中设置了受限查询位*/
    INT8            rssi;                   /* rssi值*/
    UINT8           *p_eir;                 /* 收到EIR*/
#if (BLE_INCLUDED == TRUE)
    UINT8               inq_result_type;
    UINT8               ble_addr_type;
    tBTM_BLE_EVT_TYPE   ble_evt_type;
    tBT_DEVICE_TYPE     device_type;
    UINT8               flag;
    UINT8               adv_data_len;
    UINT8               scan_rsp_len;
#endif

} tBTA_DM_INQ_RES;

/* 与BTA_DM_INQ_CMPL_EVT相关的结构*/
typedef struct {
    UINT8           num_resps;          /* 查询响应数。*/
} tBTA_DM_INQ_CMPL;

/* 与BTA_DM_INQ_DISCARD_NUM_EVT相关的结构*/
typedef struct {
    UINT32           num_dis;          /* 查询丢弃的数据包数。*/
} tBTA_DM_INQ_DISCARD;

/* 与BTA_DM_DI_DISC_CMPL_VT相关的结构*/
typedef struct {
    BD_ADDR             bd_addr;        /* BD地址对等设备。*/
    UINT8               num_record;     /* DI记录数量*/
    tBTA_STATUS         result;
} tBTA_DM_DI_DISC_CMPL;

/* 与BTA_DM_DISC_RES_EVT相关的结构*/
typedef struct {
    BD_ADDR             bd_addr;        /* BD地址对等设备。*/
    BD_NAME             bd_name;        /* 对等设备的名称。*/
    tBTA_SERVICE_MASK   services;       /* 在对等设备上找到服务。*/
// btla特定++
    UINT8              *p_raw_data;     /* 发现数据库的原始数据*/
    UINT32              raw_data_size;  /* 原始数据大小*/
    tBT_DEVICE_TYPE     device_type;    /* 设备类型（如果是BLE设备）*/
    UINT32              num_uuids;
    UINT8               *p_uuid_list;
// btla特定--
    tBTA_STATUS         result;
} tBTA_DM_DISC_RES;

/* 与tBTA_DM_DISC_BLE_RES相关的结构*/
typedef struct {
    BD_ADDR             bd_addr;        /* BD地址对等设备。*/
    BD_NAME             bd_name;        /* 对等设备的名称。*/
    tBT_UUID            service;        /* 在对等设备上找到基于GATT的服务UUID。*/
} tBTA_DM_DISC_BLE_RES;

/* 与tBTA_DM_RMTNAME_CMPL相关的结构*/
typedef struct {
    BD_ADDR     bd_addr;
    BD_NAME     bd_name;
    tBTA_CMPL_CB        *read_rmtname_cb;
} tBTA_DM_RMTNAME_CMPL;

/* 所有搜索回调结构的联合*/
typedef union {
    tBTA_DM_INQ_RES         inq_res;        /* 对等设备的查询结果。*/
    tBTA_DM_INQ_CMPL        inq_cmpl;       /* 查询完成。*/
    tBTA_DM_DISC_RES        disc_res;       /* 对等设备的发现结果。*/
    tBTA_DM_DISC_BLE_RES    disc_ble_res;   /* 基于GATT的服务的发现结果*/
    tBTA_DM_DI_DISC_CMPL    di_disc;        /* 对等设备的DI发现结果*/
    tBTA_DM_INQ_DISCARD     inq_dis;        /* 查询的丢弃包信息*/
    tBTA_DM_RMTNAME_CMPL    rmt_name;       /* 远程名称信息*/
} tBTA_DM_SEARCH;

/* 搜索回调事件的结构和结构*/
typedef struct {
    tBTA_DM_SEARCH_EVT      event;      /* 搜索回调事件*/
    UINT16                  len;        /* p_data的长度*/
    tBTA_DM_SEARCH          *p_data;    /* 所有搜索回调结构的联合*/
} tBTA_DM_SEARCH_PARAM;

/* 搜索回调*/
typedef void (tBTA_DM_SEARCH_CBACK)(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data);

/* 执行回拨*/
typedef void (tBTA_DM_EXEC_CBACK) (void *p_param);

/* 加密回调*/
typedef void (tBTA_DM_ENCRYPT_CBACK) (BD_ADDR bd_addr, tBTA_TRANSPORT transport, tBTA_STATUS result);

/* 与ESP_gatt_defs中的ESP_BLE_SEC_xxx相关。小时*/
#if BLE_INCLUDED == TRUE
#define BTA_DM_BLE_SEC_NONE         BTM_BLE_SEC_NONE
#define BTA_DM_BLE_SEC_ENCRYPT      BTM_BLE_SEC_ENCRYPT
#define BTA_DM_BLE_SEC_NO_MITM      BTM_BLE_SEC_ENCRYPT_NO_MITM
#define BTA_DM_BLE_SEC_MITM         BTM_BLE_SEC_ENCRYPT_MITM
typedef tBTM_BLE_SEC_ACT            tBTA_DM_BLE_SEC_ACT;

typedef tBTM_BLE_TX_TIME_MS         tBTA_DM_BLE_TX_TIME_MS;
typedef tBTM_BLE_RX_TIME_MS         tBTA_DM_BLE_RX_TIME_MS;
typedef tBTM_BLE_IDLE_TIME_MS       tBTA_DM_BLE_IDLE_TIME_MS;
typedef tBTM_BLE_ENERGY_USED        tBTA_DM_BLE_ENERGY_USED;

#define BTA_DM_CONTRL_UNKNOWN 0       /* 未知状态*/
#define BTA_DM_CONTRL_ACTIVE  1       /* ACL链接打开，SCO链接正在进行，嗅探模式*/
#define BTA_DM_CONTRL_SCAN    2       /* 扫描状态-寻呼/查询/尝试连接*/
#define BTA_DM_CONTRL_IDLE    3       /* 空闲状态-页面扫描、LE advt、查询扫描*/

typedef UINT8 tBTA_DM_CONTRL_STATE;

typedef UINT8 tBTA_DM_BLE_ADV_STATE;
typedef UINT8 tBTA_DM_BLE_ADV_INFO_PRESENT;
typedef UINT8 tBTA_DM_BLE_RSSI_VALUE;
typedef UINT16 tBTA_DM_BLE_ADV_INFO_TIMESTAMP;

typedef tBTM_BLE_TRACK_ADV_DATA tBTA_DM_BLE_TRACK_ADV_DATA;

typedef void (tBTA_BLE_SCAN_THRESHOLD_CBACK)(tBTA_DM_BLE_REF_VALUE ref_value);

typedef void (tBTA_BLE_SCAN_REP_CBACK) (tBTA_DM_BLE_REF_VALUE ref_value, UINT8 report_format,
                                        UINT8 num_records, UINT16 data_len,
                                        UINT8 *p_rep_data, tBTA_STATUS status);

typedef void (tBTA_BLE_SCAN_SETUP_CBACK) (tBTA_BLE_BATCH_SCAN_EVT evt,
        tBTA_DM_BLE_REF_VALUE ref_value,
        tBTA_STATUS status);

typedef void (tBTA_START_STOP_SCAN_CMPL_CBACK) (tBTA_STATUS status);

typedef void (tBTA_START_STOP_ADV_CMPL_CBACK) (tBTA_STATUS status);

typedef void (tBTA_BLE_TRACK_ADV_CMPL_CBACK)(int action, tBTA_STATUS status,
        tBTA_DM_BLE_PF_AVBL_SPACE avbl_space,
        tBTA_DM_BLE_REF_VALUE ref_value);

typedef void (tBTA_BLE_TRACK_ADV_CBACK)(tBTA_DM_BLE_TRACK_ADV_DATA *p_adv_data);

typedef void (tBTA_BLE_ENERGY_INFO_CBACK)(tBTA_DM_BLE_TX_TIME_MS tx_time,
        tBTA_DM_BLE_RX_TIME_MS rx_time,
        tBTA_DM_BLE_IDLE_TIME_MS idle_time,
        tBTA_DM_BLE_ENERGY_USED  energy_used,
        tBTA_DM_CONTRL_STATE ctrl_state,
        tBTA_STATUS status);

#else
typedef UINT8                       tBTA_DM_BLE_SEC_ACT;
#endif

/* 最大服务名称长度*/
#define BTA_SERVICE_NAME_LEN    35
#define BTA_SERVICE_DESP_LEN    BTA_SERVICE_NAME_LEN
#define BTA_PROVIDER_NAME_LEN   BTA_SERVICE_NAME_LEN


/* 链接策略掩码*/
#define BTA_DM_LP_SWITCH        HCI_ENABLE_MASTER_SLAVE_SWITCH
#define BTA_DM_LP_HOLD          HCI_ENABLE_HOLD_MODE
#define BTA_DM_LP_SNIFF         HCI_ENABLE_SNIFF_MODE
#define BTA_DM_LP_PARK          HCI_ENABLE_PARK_MODE
typedef UINT16 tBTA_DM_LP_MASK;

/* 功率模式动作*/
#define BTA_DM_PM_NO_ACTION    0x00       /* 当前pm设置不变*/
#define BTA_DM_PM_PARK         0x10       /* 首选驻车模式*/
#define BTA_DM_PM_SNIFF        0x20       /* 首选嗅探模式*/
#define BTA_DM_PM_SNIFF1       0x21       /* 首选sniff1模式*/
#define BTA_DM_PM_SNIFF2       0x22       /* 更喜欢sniff2模式*/
#define BTA_DM_PM_SNIFF3       0x23       /* 更喜欢sniff3模式*/
#define BTA_DM_PM_SNIFF4       0x24       /* 更喜欢sniff4模式*/
#define BTA_DM_PM_SNIFF5       0x25       /* 更喜欢sniff5模式*/
#define BTA_DM_PM_SNIFF6       0x26       /* 更喜欢sniff6模式*/
#define BTA_DM_PM_SNIFF7       0x27       /* 更喜欢sniff7模式*/
#define BTA_DM_PM_SNIFF_USER0  0x28       /* 首选用户定义的sniff0模式（仅限测试工具）*/
#define BTA_DM_PM_SNIFF_USER1  0x29       /* 首选用户定义的sniff1模式（仅限测试工具）*/
#define BTA_DM_PM_ACTIVE       0x40       /* 首选活动模式*/
#define BTA_DM_PM_RETRY        0x80       /* 基于当前设置重试电源模式*/
#define BTA_DM_PM_SUSPEND      0x04       /* 首选挂起模式*/
#define BTA_DM_PM_NO_PREF      0x01       /* 服务对电源模式设置没有偏好。与服务的连接已关闭*/

typedef UINT8 tBTA_DM_PM_ACTION;

/* bta_dm_sr_spec索引*/
#define BTA_DM_PM_SSR0          0
#define BTA_DM_PM_SSR1          1       /* BTA_DM_PM_SSR1将专用于HH SSR设置条目，没有其他配置文件可以使用它*/
#define BTA_DM_PM_SSR2          2
#define BTA_DM_PM_SSR3          3
#define BTA_DM_PM_SSR4          4
#define BTA_DM_PM_SSR5          5
#define BTA_DM_PM_SSR6          6

#define BTA_DM_PM_NUM_EVTS      9

#ifndef BTA_DM_PM_PARK_IDX
#define BTA_DM_PM_PARK_IDX      5 /* PARK模式下bta_dm_pm_md[]的实际索引*/
#endif

#ifndef BTA_DM_PM_SNIFF_A2DP_IDX
#define BTA_DM_PM_SNIFF_A2DP_IDX      BTA_DM_PM_SNIFF
#endif

#ifndef BTA_DM_PM_SNIFF_JV_IDX
#define BTA_DM_PM_SNIFF_JV_IDX      BTA_DM_PM_SNIFF
#endif

#ifndef BTA_DM_PM_SNIFF_HD_IDLE_IDX
#define BTA_DM_PM_SNIFF_HD_IDLE_IDX   BTA_DM_PM_SNIFF2
#endif

#ifndef BTA_DM_PM_SNIFF_SCO_OPEN_IDX
#define BTA_DM_PM_SNIFF_SCO_OPEN_IDX  BTA_DM_PM_SNIFF3
#endif

#ifndef BTA_DM_PM_SNIFF_HD_ACTIVE_IDX
#define BTA_DM_PM_SNIFF_HD_ACTIVE_IDX BTA_DM_PM_SNIFF4
#endif

#ifndef BTA_DM_PM_SNIFF_HH_OPEN_IDX
#define BTA_DM_PM_SNIFF_HH_OPEN_IDX BTA_DM_PM_SNIFF2
#endif

#ifndef BTA_DM_PM_SNIFF_HH_ACTIVE_IDX
#define BTA_DM_PM_SNIFF_HH_ACTIVE_IDX BTA_DM_PM_SNIFF2
#endif

#ifndef BTA_DM_PM_SNIFF_HH_IDLE_IDX
#define BTA_DM_PM_SNIFF_HH_IDLE_IDX BTA_DM_PM_SNIFF2
#endif


#ifndef BTA_DM_PM_HH_OPEN_DELAY
#define BTA_DM_PM_HH_OPEN_DELAY 30000
#endif

#ifndef BTA_DM_PM_HH_ACTIVE_DELAY
#define BTA_DM_PM_HH_ACTIVE_DELAY 30000
#endif

#ifndef BTA_DM_PM_HH_IDLE_DELAY
#define BTA_DM_PM_HH_IDLE_DELAY 30000
#endif

/* 下面定义的嗅探参数必须从最高延迟（最大间隔）到最低延迟排序。如果连接的服务之间存在冲突，将选择具有最低延迟的设置。如果设备应覆盖嗅探参数，则必须确保维持顺序。
 */
#ifndef BTA_DM_PM_SNIFF_MAX
#define BTA_DM_PM_SNIFF_MAX      800
#define BTA_DM_PM_SNIFF_MIN      400
#define BTA_DM_PM_SNIFF_ATTEMPT  4
#define BTA_DM_PM_SNIFF_TIMEOUT  1
#endif

#ifndef BTA_DM_PM_SNIFF1_MAX
#define BTA_DM_PM_SNIFF1_MAX     400
#define BTA_DM_PM_SNIFF1_MIN     200
#define BTA_DM_PM_SNIFF1_ATTEMPT 4
#define BTA_DM_PM_SNIFF1_TIMEOUT 1
#endif

#ifndef BTA_DM_PM_SNIFF2_MAX
#define BTA_DM_PM_SNIFF2_MAX     54 //180
#define BTA_DM_PM_SNIFF2_MIN     30 //150
#define BTA_DM_PM_SNIFF2_ATTEMPT 4
#define BTA_DM_PM_SNIFF2_TIMEOUT 1
#endif

#ifndef BTA_DM_PM_SNIFF3_MAX
#define BTA_DM_PM_SNIFF3_MAX     150
#define BTA_DM_PM_SNIFF3_MIN     50
#define BTA_DM_PM_SNIFF3_ATTEMPT 4
#define BTA_DM_PM_SNIFF3_TIMEOUT 1
#endif

#ifndef BTA_DM_PM_SNIFF4_MAX
#define BTA_DM_PM_SNIFF4_MAX     18 //54
#define BTA_DM_PM_SNIFF4_MIN     10 //30
#define BTA_DM_PM_SNIFF4_ATTEMPT 4
#define BTA_DM_PM_SNIFF4_TIMEOUT 1
#endif

#ifndef BTA_DM_PM_SNIFF5_MAX
#define BTA_DM_PM_SNIFF5_MAX     36
#define BTA_DM_PM_SNIFF5_MIN     30
#define BTA_DM_PM_SNIFF5_ATTEMPT 2
#define BTA_DM_PM_SNIFF5_TIMEOUT 0
#endif

#ifndef BTA_DM_PM_PARK_MAX
#define BTA_DM_PM_PARK_MAX       800
#define BTA_DM_PM_PARK_MIN       400
#define BTA_DM_PM_PARK_ATTEMPT   0
#define BTA_DM_PM_PARK_TIMEOUT   0
#endif


/* 切换回调事件*/
#define BTA_DM_SWITCH_CMPL_EVT      0       /* 完成交换机API*/

typedef UINT8 tBTA_DM_SWITCH_EVT;
typedef void (tBTA_DM_SWITCH_CBACK)(tBTA_DM_SWITCH_EVT event, tBTA_STATUS status);

/* 音频路由输出配置*/
#define BTA_DM_ROUTE_NONE       0x00    /* 无音频输出*/
#define BTA_DM_ROUTE_DAC        0x01    /* 模拟输出路由*/
#define BTA_DM_ROUTE_I2S        0x02    /* 数字（I2S）输出路由*/
#define BTA_DM_ROUTE_BT_MONO    0x04    /* 通过SCO路由*/
#define BTA_DM_ROUTE_BT_STEREO  0x08    /* 通过BT立体声布线*/
#define BTA_DM_ROUTE_HOST       0x10    /* 通过主机路由*/
#define BTA_DM_ROUTE_FMTX       0x20    /* 通过FMTX路由*/
#define BTA_DM_ROUTE_FMRX       0x40    /* 通过FMRX路由*/
#define BTA_DM_ROUTE_BTSNK      0x80    /* 通过BT SNK路由*/

typedef UINT8 tBTA_DM_ROUTE_PATH;

#if (SDP_INCLUDED == TRUE)
/* 设备标识（DI）数据结构
*/
/* 用于设置DI记录*/
typedef tSDP_DI_RECORD          tBTA_DI_RECORD;
/* 用于获取DI记录*/
typedef tSDP_DI_GET_RECORD      tBTA_DI_GET_RECORD;
/* SDP发现数据库*/
typedef tSDP_DISCOVERY_DB       tBTA_DISCOVERY_DB;
#endif  ///SDP_INCLUDED == TRUE

#ifndef         BTA_DI_NUM_MAX
#define         BTA_DI_NUM_MAX       3
#endif

/* 设备功能掩码定义*/
#define BTA_FEATURE_BYTES_PER_PAGE  BTM_FEATURE_BYTES_PER_PAGE
#define BTA_EXT_FEATURES_PAGE_MAX   BTM_EXT_FEATURES_PAGE_MAX
/* ACL类型
*/
#define BTA_DM_LINK_TYPE_BR_EDR    0x01
#define BTA_DM_LINK_TYPE_LE        0x02
#define BTA_DM_LINK_TYPE_ALL       0xFF
typedef UINT8 tBTA_DM_LINK_TYPE;

#define IMMEDIATE_DELY_MODE  0x00
#define ONFOUND_DELY_MODE    0x01
#define BATCH_DELY_MODE      0x02
#define ALLOW_ALL_FILTER     0x00
#define LOWEST_RSSI_VALUE     129
#if (BLE_50_FEATURE_SUPPORT == TRUE)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE       (1 << 0)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE         (1 << 1)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED          (1 << 2)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED       (1 << 3)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY            (1 << 4)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_ANON_ADV          (1 << 5)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_INCLUDE_TX_PWR    (1 << 6)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_MASK              (0x7F)

#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_IND        (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_LD_DIR     (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_HD_DIR     (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_SCAN       (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE)
#define BTA_DM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_NONCONN    (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY)
typedef UINT16 tBTA_DM_BLE_EXT_ADV_TYPE_MASK;


#define BTA_DM_BLE_GAP_PHY_1M                             1
#define BTA_DM_BLE_GAP_PHY_2M                             2
#define BTA_DM_BLE_GAP_PHY_CODED                          3
typedef UINT8 tBTA_DM_BLE_GAP_PHY;

#define BTA_DM_BLE_GAP_PHY_NO_TX_PREF_MASK                (0x01)
#define BTA_DM_BLE_GAP_PHY_NO_RX_PREF_MASK                (0x02)
#define BTA_DM_BLE_GAP_PHY_1M_PREF_MASK                   (0x03)
#define BTA_DM_BLE_GAP_PHY_2M_PREF_MASK                   (0x04)
#define BTA_DM_BLE_GAP_PHY_CODED_PREF_MASK                (0x05)
typedef UINT8 tBTA_DM_BLE_GAP_PHY_MASK;

#define BTA_DM_BLE_GAP_EXT_SCAN_UNCODE_MASK                0x01
#define BTA_DM_BLE_GAP_EXT_SCAN_CODE_MASK                  0x02
typedef UINT8 tBTA_DM_BLE_EXT_SCAN_CFG_MASK;


typedef struct {
    tBTA_DM_BLE_EXT_ADV_TYPE_MASK type;
    UINT32 interval_min;
    UINT32 interval_max;
    tBTA_BLE_ADV_CHNL_MAP channel_map;
    tBLE_ADDR_TYPE own_addr_type;
    tBLE_ADDR_TYPE peer_addr_type;
    BD_ADDR peer_addr;
    tBTA_BLE_AFP filter_policy;
    UINT8 tx_power;
    tBTA_DM_BLE_GAP_PHY primary_phy;
    UINT8 max_skip;
    tBTA_DM_BLE_GAP_PHY secondary_phy;
    UINT8 sid;
    BOOLEAN scan_req_notif;
} tBTA_DM_BLE_GAP_EXT_ADV_PARAMS;

typedef struct {
    UINT8 instance;
    int duration;
    int max_events;
} tBTA_DM_BLE_EXT_ADV;

typedef struct {
    UINT16 interval_min;
    UINT16 interval_max;
    UINT8  properties;
} tBTA_DM_BLE_Periodic_Adv_Params;

typedef struct {
    UINT8 filter_policy;
    UINT8 sid;
    tBLE_ADDR_TYPE addr_type;
    BD_ADDR addr;
    UINT16 skip;
    UINT16 sync_timeout;
} tBTA_DM_BLE_Periodic_Sync_Params;

typedef struct {
    tBLE_SCAN_MODE scan_type;
    UINT16 scan_interval;
    UINT16 scan_window;
} tBTA_DM_BLE_EXT_SCAN_CFG;

typedef struct {
    tBLE_ADDR_TYPE own_addr_type;
    UINT8 filter_policy;
    UINT8  scan_duplicate;
    tBTA_DM_BLE_EXT_SCAN_CFG_MASK cfg_mask;
    tBTA_DM_BLE_EXT_SCAN_CFG uncoded_cfg;
    tBTA_DM_BLE_EXT_SCAN_CFG coded_cfg;
} tBTA_DM_BLE_EXT_SCAN_PARAMS;

typedef struct {
    UINT16 scan_interval;
    UINT16 scan_window;
    UINT16 interval_min;
    UINT16 interval_max;
    UINT16 latency;
    UINT16 supervision_timeout;
    UINT16 min_ce_len;
    UINT16 max_ce_len;
} tBTA_DM_BLE_CONN_PARAMS;

#define BTA_DM_BLE_5_GAP_READ_PHY_COMPLETE_EVT                     BTM_BLE_5_GAP_READ_PHY_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_SET_PREFERED_DEFAULT_PHY_COMPLETE_EVT     BTM_BLE_5_GAP_SET_PREFERED_DEFAULT_PHY_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_SET_PREFERED_PHY_COMPLETE_EVT             BTM_BLE_5_GAP_SET_PREFERED_PHY_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_SET_RAND_ADDR_COMPLETE_EVT        BTM_BLE_5_GAP_EXT_ADV_SET_RAND_ADDR_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_SET_PARAMS_COMPLETE_EVT           BTM_BLE_5_GAP_EXT_ADV_SET_PARAMS_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_DATA_SET_COMPLETE_EVT             BTM_BLE_5_GAP_EXT_ADV_DATA_SET_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT        BTM_BLE_5_GAP_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_START_COMPLETE_EVT                BTM_BLE_5_GAP_EXT_ADV_START_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_STOP_COMPLETE_EVT                 BTM_BLE_5_GAP_EXT_ADV_STOP_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_SET_REMOVE_COMPLETE_EVT           BTM_BLE_5_GAP_EXT_ADV_SET_REMOVE_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_SET_CLEAR_COMPLETE_EVT            BTM_BLE_5_GAP_EXT_ADV_SET_CLEAR_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT      BTM_BLE_5_GAP_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_DATA_SET_COMPLETE_EVT        BTM_BLE_5_GAP_PERIODIC_ADV_DATA_SET_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_START_COMPLETE_EVT           BTM_BLE_5_GAP_PERIODIC_ADV_START_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_STOP_COMPLETE_EVT            BTM_BLE_5_GAP_PERIODIC_ADV_STOP_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT     BTM_BLE_5_GAP_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_SYNC_CANCEL_COMPLETE_EVT     BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_CANCEL_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_SYNC_TERMINATE_COMPLETE_EVT  BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_TERMINATE_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_ADD_DEV_COMPLETE_EVT         BTM_BLE_5_GAP_PERIODIC_ADV_ADD_DEV_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_REMOVE_DEV_COMPLETE_EVT      BTM_BLE_5_GAP_PERIODIC_ADV_REMOVE_DEV_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_CLEAR_DEV_COMPLETE_EVT       BTM_BLE_5_GAP_PERIODIC_ADV_CLEAR_DEV_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_SET_EXT_SCAN_PARAMS_COMPLETE_EVT          BTM_BLE_5_GAP_SET_EXT_SCAN_PARAMS_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_SCAN_START_COMPLETE_EVT               BTM_BLE_5_GAP_EXT_SCAN_START_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_SCAN_STOP_COMPLETE_EVT                BTM_BLE_5_GAP_EXT_SCAN_STOP_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PREFER_EXT_CONN_PARAMS_SET_COMPLETE_EVT   BTM_BLE_5_GAP_PREFER_EXT_CONN_PARAMS_SET_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_PHY_UPDATE_COMPLETE_EVT                   BTM_BLE_5_GAP_PHY_UPDATE_COMPLETE_EVT
#define BTA_DM_BLE_5_GAP_EXT_ADV_REPORT_EVT                        BTM_BLE_5_GAP_EXT_ADV_REPORT_EVT
#define BTA_DM_BLE_5_GAP_SCAN_TIMEOUT_EVT                          BTM_BLE_5_GAP_SCAN_TIMEOUT_EVT
#define BTA_DM_BLE_5_GAP_ADV_TERMINATED_EVT                        BTM_BLE_5_GAP_ADV_TERMINATED_EVT
#define BTA_DM_BLE_5_GAP_SCAN_REQ_RECEIVED_EVT                     BTM_BLE_5_GAP_SCAN_REQ_RECEIVED_EVT
#define BTA_DM_BLE_5_GAP_CHANNEL_SELETE_ALGORITHM_EVT              BTM_BLE_5_GAP_CHANNEL_SELETE_ALGORITHM_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_REPORT_EVT                   BTM_BLE_5_GAP_PERIODIC_ADV_REPORT_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_SYNC_LOST_EVT                BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_LOST_EVT
#define BTA_DM_BLE_5_GAP_PERIODIC_ADV_SYNC_ESTAB_EVT               BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_ESTAB_EVT
#define BTA_DM_BLE_5_GAP_UNKNOWN_EVT                              BTM_BLE_5_GAP_UNKNOWN_EVT
typedef tBTM_BLE_5_GAP_EVENT tBTA_DM_BLE_5_GAP_EVENT;

typedef tBTM_BLE_5_GAP_CB_PARAMS tBTA_DM_BLE_5_GAP_CB_PARAMS;
typedef tBTM_BLE_5_HCI_CBACK tBTA_DM_BLE_5_HCI_CBCAK;

extern tBTM_BLE_5_HCI_CBACK ble_5_hci_cb;

#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 功能BTA_EnableBluetooth
**
** 说明此功能初始化BTA并准备BTA和蓝牙协议堆栈以供使用。此功能通常在启动时或手机需要蓝牙服务时调用。必须在调用任何其他API函数之前调用此函数。
**
** 如果成功，则返回BTA_SUCCESS。如果内部故障，则为BTA_FAIL。
**
*******************************************************************************/
extern tBTA_STATUS BTA_EnableBluetooth(tBTA_DM_SEC_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_DisableBluetooth
**
** 说明此功能禁用BTA和蓝牙协议堆栈。当BTA不再被系统中的任何应用程序使用时，将调用它。
**
** 返回void
**
*******************************************************************************/
extern tBTA_STATUS BTA_DisableBluetooth(void);

/*******************************************************************************
** 功能BTA_EnableTestMode
**
** 说明在测试模式下启用蓝牙设备
**
** 返回tBTA_STATUS
**
*******************************************************************************/
extern tBTA_STATUS BTA_EnableTestMode(void);

/*******************************************************************************
** 功能BTA_DisableTestMode
**
** 说明在测试模式下禁用蓝牙设备
**
** 返回None
**
*******************************************************************************/
extern void BTA_DisableTestMode(void);

/*******************************************************************************
** 函数BTA_DmSetDeviceName
**
** 说明此功能设置本地设备的蓝牙名称。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetDeviceName(const char *p_name);

/*******************************************************************************
** 函数BTA_DmGetRemoteName
**
** 说明此函数获取对等设备的蓝牙名称。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmGetRemoteName(BD_ADDR remote_addr, tBTA_CMPL_CB *read_remote_name_cb);

/*******************************************************************************
** 函数BTA_DmConfigEir
**
** 说明此功能配置本地设备的EIR数据。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmConfigEir(tBTA_DM_EIR_CONF *eir_config);

/*******************************************************************************
** 功能BTA_DmSetAfhChannels
**
** 说明此功能设置AFH通道
**
** 返回void
**
*******************************************************************************/
void BTA_DmSetAfhChannels(const uint8_t *channels, tBTA_CMPL_CB  *set_afh_cb);

#if (BTA_DM_QOS_INCLUDED == TRUE)
/*******************************************************************************
** 函数BTA_DmSetQos
**
** 说明此功能设置QOS
**
** 返回void
**
*******************************************************************************/
void BTA_DmSetQos(BD_ADDR bd_addr, UINT32 t_poll, tBTM_CMPL_CB *p_cb);
#endif /// (BTA_DM_QOS_INCLUDED == TRUE)

#if (BLE_INCLUDED == TRUE)
/*******************************************************************************
** 函数BTA_DmBleSetChannels
**
** 说明此功能设置BLE通道
**
** 返回void
**
*******************************************************************************/
void BTA_DmBleSetChannels(const uint8_t *channels, tBTA_CMPL_CB  *set_channels_cb);

extern void BTA_DmUpdateWhiteList(BOOLEAN add_remove,  BD_ADDR remote_addr, tBLE_ADDR_TYPE addr_type, tBTA_ADD_WHITELIST_CBACK *add_wl_cb);

extern void BTA_DmClearWhiteList(void);

extern void BTA_DmBleReadAdvTxPower(tBTA_CMPL_CB *cmpl_cb);
#endif  ///BLE_INCLUDED == TRUE

extern void BTA_DmReadRSSI(BD_ADDR remote_addr, tBTA_TRANSPORT transport, tBTA_CMPL_CB *cmpl_cb);

/*******************************************************************************
** 函数BTA_DmSetVisibility
**
** 说明此功能设置本地设备的蓝牙可连接、可发现、可配对和仅连接模式。这控制其他蓝牙设备是否可以找到并连接到本地设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetVisibility(tBTA_DM_DISC disc_mode, tBTA_DM_CONN conn_mode, UINT8 pairable_mode, UINT8 conn_filter);

/*******************************************************************************
** 函数BTA_DmSearch
**
** 说明此功能搜索对等蓝牙设备。它首先执行查询；对于从查询中找到的每个设备，它将获取设备的远程名称。如果参数服务不为零，将在每个设备上为指定的服务执行服务发现。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSearch(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK services,
                         tBTA_DM_SEARCH_CBACK *p_cback);

/*******************************************************************************
** 函数BTA_DmSearchCancel
**
** 说明此函数取消通过调用BTA_DmSearch（）启动的搜索。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSearchCancel(void);

/*******************************************************************************
** 函数BTA_DmDiscover
**
** 描述此功能为特定对等设备的服务执行服务发现。
**
** 返回void
**
*******************************************************************************/
#if (SDP_INCLUDED == TRUE)
extern void BTA_DmDiscover(BD_ADDR bd_addr, tBTA_SERVICE_MASK services,
                           tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search);
// btla特定++
/*******************************************************************************
** 函数BTA_DmDiscoveryUUID
**
** 描述此功能为特定对等设备的服务执行服务发现。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmDiscoverUUID(BD_ADDR bd_addr, tSDP_UUID *uuid,
                               tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search);
#endif  ///SDP_INCLUDED == TRUE
/*******************************************************************************
** 函数BTA_DmGetCachedRemoteName
**
** 说明注销缓存的远程名称（如果可用）
**
** 如果检索到缓存名称，返回BTA_SUCCESS；如果缓存名称不可用，则返回BTA_FAILURE
**
*******************************************************************************/
tBTA_STATUS BTA_DmGetCachedRemoteName(BD_ADDR remote_device, UINT8 **pp_cached_name);
// btla特定--

/*******************************************************************************
** 函数BTA_DmBond
**
** 说明此功能启动与对等设备的绑定过程。绑定过程启用蓝牙链路上的身份验证和可选加密。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBond(BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTA_DmBondByTransport
**
** 说明此功能通过指定的传输启动与对等设备的绑定过程。绑定过程启用蓝牙链路上的身份验证和可选加密。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBondByTransport(BD_ADDR bd_addr, tBTA_TRANSPORT transport);


/*******************************************************************************
** 函数BTA_DmBondCancel
**
** 说明此功能取消与对等设备的绑定过程。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBondCancel(BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTA_DMSetPinType
**
** 说明此函数将引脚类型设置为BTM_pin_type_FIXED或BTM_pin_type_VARIABLE
**
** 返回void
**
*******************************************************************************/
extern void BTA_DMSetPinType (UINT8 pin_type, UINT8 *pin_code, UINT8 pin_code_len);

/*******************************************************************************
** 函数BTA_DmPinReply
**
** 说明当DM在绑定过程中请求PIN时，此功能提供PIN。在使用BTA_DM_PIN_REQ_EVT调用安全回调后，应用程序应调用此函数。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmPinReply(BD_ADDR bd_addr, BOOLEAN accept, UINT8 pin_len,
                           UINT8 *p_pin);

#if (BTM_OOB_INCLUDED == TRUE)
/*******************************************************************************
** 函数BTA_DmLocalOob
**
** 说明此功能从本地控制器检索OOB数据。结果由bta_dm_co_loc_oob（）报告。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmLocalOob(void);

/*******************************************************************************
** 函数BTA_DmOobReply
**
**                  调用此函数以响应BTM_LE_OOB_REQ_EVT为SMP提供OOB数据
**
** 参数：bd_addr-对等设备的地址len-简单配对随机化器C的长度p_value-简单配对随机器C。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmOobReply(BD_ADDR bd_addr, UINT8 len, UINT8 *p_value);
#endif /* BTM_OOB_INCLUDED */

/*******************************************************************************
** 功能BTA_Dm确认
**
** 说明此函数接受或拒绝BTA_DM_SP_CFM_REQ_EVT上简单配对过程的数值
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmConfirm(BD_ADDR bd_addr, BOOLEAN accept);

/*******************************************************************************
** 函数BTA_DmPasskeyReqReply
**
** 说明调用此函数以响应BTA_DM_SP_KEY_REQ_EVT为简单配对提供密钥
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmPasskeyReqReply(BOOLEAN accept, BD_ADDR bd_addr, UINT32 passkey);

/*******************************************************************************
** 功能BTA_DmAddDevice
**
** 说明此功能将设备添加到对等设备的安全数据库列表中。该函数通常在系统启动时调用，以使用已知的对等设备初始化安全数据库。这是一个直接执行函数，可以在某些平台上锁定任务调度。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmAddDevice(BD_ADDR bd_addr, DEV_CLASS dev_class,
                            LINK_KEY link_key, tBTA_SERVICE_MASK trusted_mask,
                            BOOLEAN is_trusted, UINT8 key_type,
                            tBTA_IO_CAP io_cap, UINT8 pin_length,
                            UINT8 sc_support);

/*******************************************************************************
** 功能BTA_DmRemoveDevice
**
** 说明此功能从安全数据库中删除设备。这是一个直接执行函数，可以在某些平台上锁定任务调度。
**
** 如果成功，则返回BTA_SUCCESS。如果操作失败，则为BTA_FAIL。
**
*******************************************************************************/
extern tBTA_STATUS BTA_DmRemoveDevice(BD_ADDR bd_addr, tBT_TRANSPORT transport);

/*******************************************************************************
** 函数BTA_GetEirService
**
** 描述调用此函数以从EIR获取BTA服务掩码。
**
** 参数p_eir-eir重要部分p_services的指针-返回BTA服务掩码
**
** 返回None
**
*******************************************************************************/
extern void BTA_GetEirService( UINT8 *p_eir, tBTA_SERVICE_MASK *p_services );

/*******************************************************************************
** 函数BTA_DmGetConnectionState
**
** 说明返回远程设备当前是否已连接。
**
** 如果设备未连接，则返回0。
**
*******************************************************************************/
extern UINT16 BTA_DmGetConnectionState( BD_ADDR bd_addr );

#if (SDP_INCLUDED == TRUE)
/*******************************************************************************
** 函数BTA_DmSetLocalDiRecord
**
** 说明此功能将DI记录添加到本地SDP数据库。
**
** 如果记录设置成功，则返回BTA_SUCCESS，否则返回错误代码。
**
*******************************************************************************/
extern tBTA_STATUS BTA_DmSetLocalDiRecord( tBTA_DI_RECORD *p_device_info,
        UINT32 *p_handle );
#endif  ///SDP_INCLUDED == TRUE
/*******************************************************************************
**
**
** 函数BTA_DmCloseACL
**
** 说明此函数强制关闭ACL连接并从已知设备的安全数据库列表中删除该设备。
**
** 参数：bd_addr-对等设备的地址remove_dev-链接关闭传输后是否删除设备-要关闭哪个传输

** 返回void。
**
*******************************************************************************/
extern void BTA_DmCloseACL(BD_ADDR bd_addr, BOOLEAN remove_dev, tBTA_TRANSPORT transport);

/*******************************************************************************
** 函数bta_dexecutecallback
**
** 说明此函数将请求BTA在BTU任务上下文中执行回调。此API以小写形式命名，因为它仅适用于内部客户（如BTIF）。
**
** 返回void
**
*******************************************************************************/
extern void bta_dmexecutecallback (tBTA_DM_EXEC_CBACK *p_callback, void *p_param);

#if (BTM_SCO_HCI_INCLUDED == TRUE)
/*******************************************************************************
** 函数BTA_DmPcmInitSamples
**
** 说明初始化下采样转换器。
**
**                  src_sps：每秒原始样本（源音频数据）（例如44100、48000）位：每个pcm样本的位数（16）n_channels：信道数（即单声道（1）、立体声（2）…）
**
** 不返回任何值
**
*******************************************************************************/
extern void BTA_DmPcmInitSamples (UINT32 src_sps, UINT32 bits, UINT32 n_channels);

/*******************************************************************************
** 函数BTA_DmPcmDeinitSamples
**
** 说明取消初始化下采样转换器。
**
** 不返回任何值
**
*******************************************************************************/
extern void BTA_DmPcmDeinitSamples(void);

/**************************************************************************************
** 函数BTA_DmPcmResample
**
** 说明下采样实用程序，用于将较高采样率转换为8K/16位PCM采样。
**
** 参数p_src：指向存储原始采样PCM的缓冲区的指针。in_bytes：输入PCM采样缓冲区的长度（字节）。p_dst：指向用于存储转换PCM样本的缓冲区的指针。
**
** 返回INT32：转换的样本数。
**
**************************************************************************************/
extern INT32 BTA_DmPcmResample (void *p_src, UINT32 in_bytes, void *p_dst);
#endif

#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
/* BLE相关API函数*/
/*******************************************************************************
** 函数BTA_DmBleSecurityGrant
**
** 说明授予安全请求访问权限。
**
** 参数：bd_addr-对等端的bd地址-安全授权状态。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleSecurityGrant(BD_ADDR bd_addr, tBTA_DM_BLE_SEC_GRANT res);



/*******************************************************************************
** 函数BTA_DmBleSetBgConnType
**
** 说明调用此函数可设置外围设备的BLE可连接模式。
**
** 参数bg_conn_type：可以是自动连接，也可以是选择性连接。p_select_cback：使用选择性连接过程时的回调函数。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleSetBgConnType(tBTA_DM_BLE_CONN_TYPE bg_conn_type, tBTA_DM_BLE_SEL_CBACK *p_select_cback);

/*******************************************************************************
** 函数BTA_DmBlePasskeyReply
**
** 说明发送BLE SMP密钥回复。
**
** 参数：bd_addr-对等方accept-passkey条目的bd地址成功或被拒绝。passkey-passkey值，必须是6位数字，可以以0开头。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBlePasskeyReply(BD_ADDR bd_addr, BOOLEAN accept, UINT32 passkey);

/*******************************************************************************
** 函数BTA_DmBleStaticPasskey
**
** 说明设置BLE SMP静态密钥。
**
** 参数：add-add static passkey when add is true clear static passkeywhen add isfalse passkey-static passkey value
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleSetStaticPasskey(bool add, uint32_t passkey);

/*******************************************************************************
** 函数BTA_DmBleConfirmReply
**
** 说明发送BLE SMP SC用户确认回复。
**
** 参数：bd_addr-要比较的对等方接受号码的bd地址相同或不同。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleConfirmReply(BD_ADDR bd_addr, BOOLEAN accept);

/*******************************************************************************
** 功能BTA_DmAddBleDevice
**
** 说明添加BLE设备。该功能通常在主机启动期间调用，以恢复存储在NVRAM中的LE设备的所有所需信息。
**
** 参数：bd_addr-对等设备的bd地址dev_type-远程设备的设备类型。auth_mode-auth mode addr_type-LE设备地址类型。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmAddBleDevice(BD_ADDR bd_addr, tBLE_ADDR_TYPE addr_type, int auth_mode,
                               tBT_DEVICE_TYPE dev_type);


/*******************************************************************************
** 功能BTA_DmAddBleKey
**
** 说明添加/修改LE设备信息。该功能通常在主机启动期间调用，以恢复存储在NVRAM中的所有所需信息。
**
** 参数：bd_addr-对等体p_le_key的bd地址-le键值。key_type—LE SMP密钥类型。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmAddBleKey (BD_ADDR bd_addr,
                             tBTA_LE_KEY_VALUE *p_le_key,
                             tBTA_LE_KEY_TYPE key_type);

/*******************************************************************************
** 函数BTA_DmSetBlePrefConnParams
**
** 说明当不需要默认连接参数时，调用此函数以设置首选连接参数。
**
** 参数：bd_addr-外围设备的bd地址min_conn_int-最小首选连接间隔max_conn_int–最大首选连接间隔slave_elatency-首选从属延迟supervisory_tout-首选监视超时
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetBlePrefConnParams(BD_ADDR bd_addr,
                                       UINT16 min_conn_int, UINT16 max_conn_int,
                                       UINT16 slave_latency, UINT16 supervision_tout );

/*******************************************************************************
** 函数BTA_DmSetBleConnScanParams
**
** 说明调用此函数以设置BLE连接请求中使用的扫描参数
**
** 参数：scan_interval-扫描间隔scan_window-扫描窗口
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetBleConnScanParams(UINT32 scan_interval,
                                       UINT32 scan_window);

/*******************************************************************************
** 函数BTA_DmSetBleScanParams
**
** 说明调用此函数以设置扫描参数
**
** 参数：client_if-客户端if scan_interval-扫描间隔scan_window-扫描窗口scan_mode-扫描模式scan_param_setup_status_cback-设置扫描参数状态回调
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetBleScanParams(tGATT_IF client_if, UINT32 scan_interval,
                                   UINT32 scan_window, tBLE_SCAN_MODE scan_mode,
                                   tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_status_cback);


/*******************************************************************************
** 函数BTA_DmSetBleScanFilterParams
**
** 说明调用此函数以设置扫描参数
**
** 参数：client_if-客户端if scan_interval-扫描间隔scan_window-扫描窗口scan_mode-扫描模式scan_duplicate_filter-扫描重复筛选器scan_param_setup_status_cback-设置扫描参数状态回调
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetBleScanFilterParams(tGATT_IF client_if, UINT32 scan_interval,
        UINT32 scan_window, tBLE_SCAN_MODE scan_mode, UINT8 scan_fil_poilcy,
        UINT8 addr_type_own, UINT8 scan_duplicate_filter, tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_cback);


/*******************************************************************************
** 函数BTA_DmSetBleAdvParams
**
** 说明此功能设置广告参数BLE功能。当设备充当外围设备或广播器角色时，将调用它。
**
** 参数：adv_int_min-adv interval minimum adv_int_max-adv interval max p_dir_bda-定向adv启动器地址
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSetBleAdvParams (UINT16 adv_int_min, UINT16 adv_int_max,
                                   tBLE_BD_ADDR *p_dir_bda);

extern void BTA_DmSetBleAdvParamsAll (UINT16 adv_int_min, UINT16 adv_int_max,
                                      UINT8 adv_type, tBLE_ADDR_TYPE addr_type_own,
                                      tBTM_BLE_ADV_CHNL_MAP chnl_map, tBTM_BLE_AFP adv_fil_pol,
                                      tBLE_BD_ADDR *p_dir_bda, tBTA_START_ADV_CMPL_CBACK p_start_adv_cb);


/*******************************************************************************
** 函数BTA_DmSearchExt
**
** 说明此功能搜索对等蓝牙设备。它执行查询并获取设备的远程名称。如果服务为非零，则完成服务发现
**
** 参数p_dm_inq：查询条件服务：如果服务不为空，将执行服务发现。对于所有基于GATT的服务条件，放入num_uuid，p_uuid是uuid值列表的指针。p_cback：搜索完成时回调functino。
**
**
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmSearchExt(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK_EXT *p_services,
                            tBTA_DM_SEARCH_CBACK *p_cback);

/*******************************************************************************
** 函数BTA_DmDiscoveryExt
**
** 描述此功能为对等设备的服务进行服务发现。当服务。num_uuid为0，表示要搜索所有基于GATT的服务；另一方面，应该通过services.p_UUID提供感兴趣服务的UUID列表。
**
**
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmDiscoverExt(BD_ADDR bd_addr, tBTA_SERVICE_MASK_EXT *p_services,
                              tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search);

/*******************************************************************************
** 函数BTA_DmDiscoveryByTransport
**
** 描述此功能在对等设备的服务的特定传输上执行服务发现。当服务。num_uuid为0，表示要搜索所有基于GATT的服务；另一方面，应该通过p_services->p_UUID提供感兴趣服务的UUID列表。
**
**
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmDiscoverByTransport(BD_ADDR bd_addr, tBTA_SERVICE_MASK_EXT *p_services,
                                      tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search,
                                      tBTA_TRANSPORT transport);

/*******************************************************************************
** 函数BTA_DmSetEncryption
**
** 说明调用此函数以确保连接已加密。只能在打开的连接上调用。通常只需要用于首先要打开未加密链接，然后再对其进行加密的连接。
**
** 参数：bd_addr-对等设备传输的地址-要加密的链路的传输p_callback-指向回调函数的指针，用于指示链路加密状态sec_act-这是一个安全操作，用于指示BLE链路所需的BLE安全级别（如果BLE受支持）注意：对于BR/EDR链路或BLE不受支持，将忽略此参数支持
**
** 返回void
**
**
*******************************************************************************/
extern void BTA_DmSetEncryption(BD_ADDR bd_addr, tBTA_TRANSPORT transport,
                                tBTA_DM_ENCRYPT_CBACK *p_callback,
                                tBTA_DM_BLE_SEC_ACT sec_act);


/*******************************************************************************
** 功能BTA_DmBleObserve
**
** 说明此过程使设备监听来自广播设备的广告事件。
**
** 参数启动：启动或停止观察。duration：扫描的持续时间。如果传递了0，则继续扫描p_results_cb：使用扫描结果调用回调
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleObserve(BOOLEAN start, UINT32 duration,
                             tBTA_DM_SEARCH_CBACK *p_results_cb,
                             tBTA_START_STOP_SCAN_CMPL_CBACK *p_start_stop_scan_cb);

/*******************************************************************************
** 功能BTA_DmBleScan
**
** 说明此过程使设备监听来自广播设备的广告事件。
**
** 参数启动：启动或停止观察。duration：扫描的持续时间。如果传递了0，则继续扫描p_results_cb：使用扫描结果调用回调
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleScan(BOOLEAN start, UINT32 duration,
                             tBTA_DM_SEARCH_CBACK *p_results_cb,
                             tBTA_START_STOP_SCAN_CMPL_CBACK *p_start_stop_scan_cb);

extern void BTA_DmBleStopAdvertising(void);

extern void BTA_DmSetRandAddress(BD_ADDR rand_addr, tBTA_SET_RAND_ADDR_CBACK *p_set_rand_addr_cback);
extern void BTA_DmClearRandAddress(void);

#endif

#if BLE_INCLUDED == TRUE
// btla特定--
/*******************************************************************************
** 函数BTA_DmBleConfigLocalPrivacy
**
** 说明在本地设备上启用/禁用隐私
**
** 参数：privacy_enable-启用/禁用远程设备上的隐私。set_local_privacy_cback-使用结果调用的回调返回void
**
*******************************************************************************/
extern void BTA_DmBleConfigLocalPrivacy(BOOLEAN privacy_enable, tBTA_SET_LOCAL_PRIVACY_CBACK *set_local_privacy_cback);

/*******************************************************************************
** 函数BTA_DmBleConfigLocalIcon
**
** 描述集间隙本地图标
**
** 参数：图标-外观值。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleConfigLocalIcon(uint16_t icon);

/*******************************************************************************
** 功能BTA_DmBleEnableRemotePrivacy
**
** 说明启用/禁用远程设备上的隐私
**
** 参数：bd_addr-对等privacy_enable的bd地址-启用/禁用远程设备上的隐私。
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleEnableRemotePrivacy(BD_ADDR bd_addr, BOOLEAN privacy_enable);


/*******************************************************************************
** 函数BTA_DmBleSetAdvConfig
**
** 说明调用此函数以覆盖BTA默认ADV参数。
**
** 参数指向用户定义ADV数据结构的指针
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleSetAdvConfig (tBTA_BLE_AD_MASK data_mask,
                                   tBTA_BLE_ADV_DATA *p_adv_cfg,
                                   tBTA_SET_ADV_DATA_CMPL_CBACK *p_adv_data_cback);

/*******************************************************************************
** 函数BTA_DmBleSetAdvConfigRaw
**
** 说明调用此函数以设置原始广告数据
**
** 参数p_raw_adv:原始广告数据。raw_adv_len：原始广告数据长度。p_adv_data_cback：设置adv数据完成回调。
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleSetAdvConfigRaw (UINT8 *p_raw_adv, UINT32 raw_adv_len,
                            tBTA_SET_ADV_DATA_CMPL_CBACK *p_adv_data_cback);

/*******************************************************************************
** 函数BTA_DmBleSetLongAdv
**
** 说明此函数用于设置长广告数据
**
** 参数adv_data：长广告数据。adv_data_len：长广告数据长度。p_adv_data_cback：设置长adv数据完成回调。
**
** 返回None
**
*******************************************************************************/
void BTA_DmBleSetLongAdv (UINT8 *adv_data, UINT32 adv_data_len,
                            tBTA_SET_ADV_DATA_CMPL_CBACK *p_adv_data_cback);

/*******************************************************************************
** 函数BTA_DmBleScanRsp
**
** 说明调用此函数以覆盖BTA扫描响应。
**
** 参数指向用户定义ADV数据结构的指针
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleSetScanRsp (tBTA_BLE_AD_MASK data_mask,
                                 tBTA_BLE_ADV_DATA *p_adv_cfg,
                                 tBTA_SET_ADV_DATA_CMPL_CBACK *p_adv_data_cback);

/*******************************************************************************
** 函数BTA_DmBleScanRspRaw
**
** 说明调用此函数以设置原始扫描响应数据
**
** 参数p_raw_scan_rsp：原始扫描数据。raw_scan_rsp_len:raw scan_rsperting数据长度。p_scan_rsp_data_cback：设置scan_rsp数据完成回调。
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleSetScanRspRaw (UINT8 *p_raw_scan_rsp, UINT32 raw_scan_rsp_len,
                                    tBTA_SET_ADV_DATA_CMPL_CBACK *p_scan_rsp_data_cback);

/*******************************************************************************
** 函数BTA_DmUpdateDuplicateExceptionalList
**
** 说明调用此函数以更新重复扫描例外列表
**
** 参数子代码：添加、删除或清除重复扫描异常列表。type：设备信息类型。device_info：设备信息p_update_duplicate_ignore_list_cback：更新完成回调。
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmUpdateDuplicateExceptionalList(UINT8 subcode, UINT32 type,
                                                BD_ADDR device_info,
                                                tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK p_update_duplicate_exceptional_list_cback);

/*******************************************************************************
** 功能BTA_DmBleBroadcast
**
** 说明此功能启动或停止LE广播。
**
** 参数开始：开始或停止广播。p_start_stop_adv_cb：停止广播完成事件
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleBroadcast (BOOLEAN start, tBTA_START_STOP_ADV_CMPL_CBACK *p_start_stop_adv_cb);


/*******************************************************************************
** 函数BTA_BleEnableAdvInstance
**
** 说明此功能启用Multi-ADV实例功能
**
** 参数p_params指向ADV参数用户定义结构p_cback的指针指向多ADV回调结构p_ref-引用指针
**
** 返回None
**
*******************************************************************************/
extern void BTA_BleEnableAdvInstance (tBTA_BLE_ADV_PARAMS *p_params,
                                      tBTA_BLE_MULTI_ADV_CBACK *p_cback, void *p_ref);

/*******************************************************************************
** 函数BTA_BleUpdateAdvInstParam
**
** 说明此函数更新Multi-ADV实例参数
**
** 参数inst_id实例id p_params指向ADV参数用户定义结构的指针
**
** 返回None
**
*******************************************************************************/
extern void BTA_BleUpdateAdvInstParam (UINT8 inst_id,
                                       tBTA_BLE_ADV_PARAMS *p_params);

/*******************************************************************************
** 函数BTA_BleCfgAdvInstData
**
** 说明调用此函数以配置ADV实例数据
**
** 参数inst_id-实例id is_scan_rsp-布尔值扫描响应指向用户定义的ADV数据结构的指针返回无
**
*******************************************************************************/
extern void BTA_BleCfgAdvInstData (UINT8 inst_id, BOOLEAN is_scan_rsp,
                                   tBTA_BLE_AD_MASK data_mask, tBTA_BLE_ADV_DATA *p_data);

/*******************************************************************************
** 函数BTA_BleDisableAdvInstance
**
** 说明调用此函数以禁用ADV实例
**
** 参数inst_id-要禁用的实例id
**
** 返回None
**
*******************************************************************************/
extern void BTA_BleDisableAdvInstance(UINT8 inst_id);

/*******************************************************************************
** 函数BTA_DmBleUpdateConnectionParams
**
** 说明更新连接参数，只能在连接启动时使用。
**
** 参数：bd_addr-对等方的bd地址min_int-最小连接间隔，[0x004~0x4000]max_int-最大连接间隔，[00x04~0x4000]延迟-从属延迟[0~500]超时-监督超时[0x00a~0xc80]
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleUpdateConnectionParams(BD_ADDR bd_addr, UINT16 min_int,
        UINT16 max_int, UINT16 latency, UINT16 timeout);

/*******************************************************************************
** 功能BTA_DmBleDisconnect
**
** 说明此功能用于断开电缆连接
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleDisconnect(BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTA_DmBleSetDataLength
**
** 说明此功能用于设置最大LE数据包大小
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleSetDataLength(BD_ADDR remote_device, UINT16 tx_data_length, tBTA_SET_PKT_DATA_LENGTH_CBACK *p_set_pkt_data_cback);

/*******************************************************************************
** 函数BTA_DmBleStorageParams
**
** 说明调用此函数以设置存储参数
**
** 参数batch_scan_full_max-分配给完全扫描batch_scan_trunc_max的最大存储空间（%）-分配给截断扫描batch_scan_notify_threshold的最大存储容量（%）—基于两个池消耗的总空间设置通知级别。将其设置为0将禁用阈值通知p_setup_cback-设置回调p_thres_cback-阈值回调p_rep_cback-报告回调ref_value-参考值
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleSetStorageParams(UINT8 batch_scan_full_max,
                                      UINT8 batch_scan_trunc_max,
                                      UINT8 batch_scan_notify_threshold,
                                      tBTA_BLE_SCAN_SETUP_CBACK *p_setup_cback,
                                      tBTA_BLE_SCAN_THRESHOLD_CBACK *p_thres_cback,
                                      tBTA_BLE_SCAN_REP_CBACK *p_rep_cback,
                                      tBTA_DM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTA_DmBleEnableBatchScan
**
** 说明调用此函数以启用批扫描
**
** 参数scan_mode-批扫描模式scan_interval-扫描间隔scan_window-扫描窗口discard_rule-放弃规则addr_type-地址类型ref_value-参考值
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleEnableBatchScan(tBTA_BLE_BATCH_SCAN_MODE scan_mode,
                                     UINT32 scan_interval, UINT32 scan_window,
                                     tBTA_BLE_DISCARD_RULE discard_rule,
                                     tBLE_ADDR_TYPE        addr_type,
                                     tBTA_DM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTA_DmBleReadScanReports
**
** 说明调用此函数以读取批扫描报告
**
** 参数scan_mode-批扫描模式ref_value-参考值
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleReadScanReports(tBTA_BLE_BATCH_SCAN_MODE scan_type,
                                     tBTA_DM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTA_DmBleDisableBatchScan
**
** 说明调用此函数以禁用批扫描
**
** 参数ref_value-参考值
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleDisableBatchScan(tBTA_DM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTA_DmEnableScanFilter
**
** 说明调用此函数以启用adv数据有效负载筛选器
**
** 参数操作-启用或禁用APCF功能p_cmpl_cback-命令完成回调ref_value-参考值
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmEnableScanFilter(UINT8 action,
                                   tBTA_DM_BLE_PF_STATUS_CBACK *p_cmpl_cback,
                                   tBTA_DM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTA_DmBleScanFilterSetup
**
** 说明调用此函数以设置过滤器参数
**
** 参数p_target：启用目标设备上的过滤条件；if NULL filt_index-筛选器索引p_filt_params-筛选器参数ref_value-参考值action-添加、删除或清除p_cmpl_back-命令完成回调
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleScanFilterSetup(UINT8 action,
                                     tBTA_DM_BLE_PF_FILT_INDEX filt_index,
                                     tBTA_DM_BLE_PF_FILT_PARAMS *p_filt_params,
                                     tBLE_BD_ADDR *p_target,
                                     tBTA_DM_BLE_PF_PARAM_CBACK *p_cmpl_cback,
                                     tBTA_DM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTA_DmBleCfgFilterCondition
**
** 说明调用此函数以配置adv数据有效负载筛选器条件。
**
** 参数操作：读取/写入/清除cond_type：筛选器条件类型filt_index-筛选器索引p_cond:筛选器条件参数p_cmpl_back-命令完成回调ref_value-参考值
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleCfgFilterCondition(tBTA_DM_BLE_SCAN_COND_OP action,
                                        tBTA_DM_BLE_PF_COND_TYPE cond_type,
                                        tBTA_DM_BLE_PF_FILT_INDEX filt_index,
                                        tBTA_DM_BLE_PF_COND_PARAM *p_cond,
                                        tBTA_DM_BLE_PF_CFG_CBACK *p_cmpl_cback,
                                        tBTA_DM_BLE_REF_VALUE ref_value);


/*******************************************************************************
** 功能BTA_DmBleTrackAdvertiser
**
** 描述此函数用于跟踪广告客户
**
** 参数ref_value-参考值p_track_adv_cback-adv回调
**
** 返回None
**
*******************************************************************************/
extern void BTA_DmBleTrackAdvertiser(tBTA_DM_BLE_REF_VALUE ref_value,
                                     tBTA_BLE_TRACK_ADV_CBACK *p_track_adv_cback);

/*******************************************************************************
** 函数BTA_DmBleGetEnergyInfo
**
** 描述调用此函数以获取能量信息
**
** 参数p_cmpl_cback-命令完成回调
**
** 返回void
**
*******************************************************************************/
extern void BTA_DmBleGetEnergyInfo(tBTA_BLE_ENERGY_INFO_CBACK *p_cmpl_cback);

/*******************************************************************************
** 函数BTA_BrcmInit
**
** 说明此函数初始化BTA中特定于Broadcom的VS处理程序
**
** 返回void
**
*******************************************************************************/
extern void BTA_VendorInit  (void);

/*******************************************************************************
** 函数BTA_BrcmCleanup
**
** 说明此功能释放Broadcom特定VS特定动态内存
**
** 返回void
**
*******************************************************************************/
extern void BTA_VendorCleanup (void);

#if (BLE_50_FEATURE_SUPPORT == TRUE)
extern void BTA_DmBleGapReadPHY(BD_ADDR addr);

extern void BTA_DmBleGapSetPreferedDefaultPHY(tBTA_DM_BLE_GAP_PHY_MASK tx_phy_mask,
                                                          tBTA_DM_BLE_GAP_PHY_MASK rx_phy_mask);

extern void BTA_DmBleGapSetPreferedPHY(BD_ADDR addr,
                                               UINT8 all_phys,
                                               tBTA_DM_BLE_GAP_PHY_MASK tx_phy_mask,
                                               tBTA_DM_BLE_GAP_PHY_MASK rx_phy_mask,
                                               UINT16 phy_options);

extern void BTA_DmBleGapExtAdvSetRandaddr(UINT16 instance, BD_ADDR addr);

extern void BTA_DmBleGapExtAdvSetParams(UINT16 instance,
                                                 const tBTA_DM_BLE_GAP_EXT_ADV_PARAMS *params);

extern void BTA_DmBleGapConfigExtAdvDataRaw(BOOLEAN is_scan_rsp, UINT8 instance, UINT16 length,
                                                        const UINT8 *data);

extern void BTA_DmBleGapStartExtAdv(UINT8 num, tBTA_DM_BLE_EXT_ADV *ext_adv);

extern void BTA_DmBleGapExtAdvEnable(BOOLEAN enable, UINT8 num, tBTA_DM_BLE_EXT_ADV *ext_adv);

extern void BTA_DmBleGapExtAdvSetRemove(UINT8 instance);

extern void BTA_DmBleGapExtAdvSetClear(void);

extern void BTA_DmBleGapPeriodicAdvSetParams(UINT8 instance,
                                                         tBTA_DM_BLE_Periodic_Adv_Params *params);

extern void BTA_DmBleGapPeriodicAdvCfgDataRaw(UINT8 instance, UINT16 length,
                                                           const UINT8 *data);

extern void BTA_DmBleGapPeriodicAdvEnable(BOOLEAN enable, UINT8 instance);

extern void BTA_DmBleGapPeriodicAdvCreateSync(tBTA_DM_BLE_Periodic_Sync_Params *params);

extern void BTA_DmBleGapPeriodicAdvSyncCancel(void);

extern void BTA_DmBleGapPeriodicAdvSyncTerm(UINT16 sync_handle);

extern void BTA_DmBleGapPeriodicAdvAddDevToList(tBLE_ADDR_TYPE addr_type,
                                                              BD_ADDR addr,
                                                              UINT16 sid);

extern void BTA_DmBleGapPeriodicAdvRemoveDevFromList(tBLE_ADDR_TYPE addr_type,
                                                              BD_ADDR addr,
                                                              UINT16 sid);

extern void BTA_DmBleGapPeriodicAdvClearDev(void);

extern void BTA_DmBleGapSetExtScanParams(tBTA_DM_BLE_EXT_SCAN_PARAMS *params);

extern void BTA_DmBleGapExtScan(BOOLEAN start, UINT32 duration, UINT16 period);

extern void BTA_DmBleGapPreferExtConnectParamsSet(BD_ADDR bd_addr,
                                                  UINT8 phy_mask,
                                                  const tBTA_DM_BLE_CONN_PARAMS *phy_1m_conn_params,
                                                  const tBTA_DM_BLE_CONN_PARAMS *phy_2m_conn_params,
                                                  const tBTA_DM_BLE_CONN_PARAMS *phy_coded_conn_params);

extern void BTA_DmBleGapExtConnect(tBLE_ADDR_TYPE own_addr_type, const BD_ADDR peer_addr);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）

#endif

enum {
    BTA_COEX_EVT_SCAN_STARTED = 1,
    BTA_COEX_EVT_SCAN_STOPPED,
    BTA_COEX_EVT_ACL_CONNECTED,
    BTA_COEX_EVT_ACL_DISCONNECTED,
    BTA_COEX_EVT_STREAMING_STARTED,
    BTA_COEX_EVT_STREAMING_STOPPED,
    BTA_COEX_EVT_SNIFF_ENTER,
    BTA_COEX_EVT_SNIFF_EXIT,
    BTA_COEX_EVT_A2DP_PAUSED_ENTER,
    BTA_COEX_EVT_A2DP_PAUSED_EXIT,
};

extern void BTA_DmCoexEventTrigger(uint32_t event);

#ifdef __cplusplus
}
#endif

#endif /* BTA_API_H */

