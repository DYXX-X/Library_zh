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
 * 此文件包含Bluetooth Manager（BTM）API函数外部定义。
 *
 ******************************************************************************/
#ifndef BTM_BLE_API_H
#define BTM_BLE_API_H

#include "common/bt_defs.h"
#include "stack/btm_api.h"
#include "common/bt_common_types.h"

#define CHANNEL_MAP_LEN    5
typedef UINT8 tBTM_BLE_CHNL_MAP[CHANNEL_MAP_LEN];

/* 0x00-0x04仅用于设置广告参数命令*/
#define BTM_BLE_CONNECT_EVT     0x00   /* 0x00-0x04仅用于设置广告参数命令*/
#define BTM_BLE_CONNECT_DIR_EVT 0x01   /* 可连接的定向广告*/
#define BTM_BLE_DISCOVER_EVT    0x02  /* 无良广告*/
#define BTM_BLE_NON_CONNECT_EVT 0x03  /* 不可连接的无定向广告*/
#define BTM_BLE_CONNECT_LO_DUTY_DIR_EVT 0x04        /* 可连接的低占空比定向广告*/
/* 可以在adv事件类型上接收0x00-0x05*/
#define BTM_BLE_SCAN_RSP_EVT    0x04
#define BTM_BLE_SCAN_REQ_EVT    0x05
#define BTM_BLE_UNKNOWN_EVT     0xff

#define BTM_BLE_UNKNOWN_EVT     0xff

typedef UINT8 tBTM_BLE_EVT;
typedef UINT8 tBTM_BLE_CONN_MODE;

typedef UINT32 tBTM_BLE_REF_VALUE;

#define BTM_BLE_SCAN_MODE_PASS      0
#define BTM_BLE_SCAN_MODE_ACTI      1
#define BTM_BLE_SCAN_MODE_NONE      0xff
typedef UINT8 tBLE_SCAN_MODE;

#define BTM_BLE_BATCH_SCAN_MODE_DISABLE 0
#define BTM_BLE_BATCH_SCAN_MODE_PASS  1
#define BTM_BLE_BATCH_SCAN_MODE_ACTI  2
#define BTM_BLE_BATCH_SCAN_MODE_PASS_ACTI 3

typedef UINT8 tBTM_BLE_BATCH_SCAN_MODE;

/* 广告频道图*/
#define BTM_BLE_ADV_CHNL_37    (0x01 << 0)
#define BTM_BLE_ADV_CHNL_38    (0x01 << 1)
#define BTM_BLE_ADV_CHNL_39    (0x01 << 2)
typedef UINT8 tBTM_BLE_ADV_CHNL_MAP;

/*默认广告频道图*/
#ifndef BTM_BLE_DEFAULT_ADV_CHNL_MAP
#define BTM_BLE_DEFAULT_ADV_CHNL_MAP   (BTM_BLE_ADV_CHNL_37| BTM_BLE_ADV_CHNL_38| BTM_BLE_ADV_CHNL_39)
#endif

/* 广告筛选策略*/
#define AP_SCAN_CONN_ALL           0x00        /* 违约*/
#define AP_SCAN_WL_CONN_ALL        0x01
#define AP_SCAN_ALL_CONN_WL        0x02
#define AP_SCAN_CONN_WL            0x03
#define AP_SCAN_CONN_POLICY_MAX    0x04
typedef UINT8   tBTM_BLE_AFP;

/* 默认广告筛选器策略*/
#ifndef BTM_BLE_DEFAULT_AFP
#define BTM_BLE_DEFAULT_AFP   AP_SCAN_CONN_ALL
#endif

/* 扫描筛选器策略*/
#define SP_ADV_ALL     0x00     /* 0:接受来自所有人的adv数据包，定向adv pkt未定向*/
/* 忽略到本地设备*/
#define SP_ADV_WL      0x01     /* 1： 接受来自白名单设备的adv数据包，定向adv*/
/* 忽略未定向到本地设备的数据包*/
#define SP_ADV_ALL_RPA_DIR_ADV 0x02  /* 2： 接受所有人的adv包，直接adv pkt*/
/* 除了与RPA的直接广告外，不直接指向我的广告被忽略*/
#define SP_ADV_WL_RPA_DIR_ADV  0x03  /* 3： 接受来自白名单设备的adv数据包，定向*/
/* 除了直接adv之外，不直接指向我的pkt被忽略*/
/* 带RPA*/
typedef UINT8   tBTM_BLE_SFP;

#ifndef BTM_BLE_DEFAULT_SFP
#define BTM_BLE_DEFAULT_SFP   SP_ADV_ALL
#endif

/* adv参数边界值*/
#define BTM_BLE_ADV_INT_MIN            0x0020
#define BTM_BLE_ADV_INT_MAX            0x4000

/* 全扫描边界值*/
#define BTM_BLE_ADV_SCAN_FULL_MIN      0x00
#define BTM_BLE_ADV_SCAN_FULL_MAX      0x64

/* 部分扫描边界值*/
#define BTM_BLE_ADV_SCAN_TRUNC_MIN      BTM_BLE_ADV_SCAN_FULL_MIN
#define BTM_BLE_ADV_SCAN_TRUNC_MAX      BTM_BLE_ADV_SCAN_FULL_MAX

/* 阈值*/
#define BTM_BLE_ADV_SCAN_THR_MIN        BTM_BLE_ADV_SCAN_FULL_MIN
#define BTM_BLE_ADV_SCAN_THR_MAX        BTM_BLE_ADV_SCAN_FULL_MAX

/* 连接参数边界值*/
#define BTM_BLE_SCAN_INT_MIN            0x0004
#define BTM_BLE_SCAN_INT_MAX            0x4000
#define BTM_BLE_SCAN_WIN_MIN            0x0004
#define BTM_BLE_SCAN_WIN_MAX            0x4000
#define BTM_BLE_EXT_SCAN_INT_MAX        0x00FFFFFF
#define BTM_BLE_EXT_SCAN_WIN_MAX        0xFFFF
#define BTM_BLE_CONN_INT_MIN            0x0006
#define BTM_BLE_CONN_INT_MAX            0x0C80
#define BTM_BLE_CONN_LATENCY_MAX        499
#define BTM_BLE_CONN_SUP_TOUT_MIN       0x000A
#define BTM_BLE_CONN_SUP_TOUT_MAX       0x0C80
#define BTM_BLE_CONN_PARAM_UNDEF        0xffff      /* 在不覆盖特定值时使用此值*/
#define BTM_BLE_SCAN_PARAM_UNDEF        0xffffffff

/* 如果未配置默认连接参数，请使用GAP推荐值进行自动/选择性连接*/
/* 默认扫描间隔*/
#ifndef BTM_BLE_SCAN_FAST_INT
#define BTM_BLE_SCAN_FAST_INT    96    /* 30~60 ms（使用60）=96*0.625*/
#endif
/* 后台连接的默认扫描窗口，适用于自动连接或选择性连接*/
#ifndef BTM_BLE_SCAN_FAST_WIN
#define BTM_BLE_SCAN_FAST_WIN   48      /* 30毫秒=48*0.625*/
#endif

/* 在降低功率循环（背景扫描）中使用的默认扫描参数*/
#ifndef BTM_BLE_SCAN_SLOW_INT_1
#define BTM_BLE_SCAN_SLOW_INT_1    2048    /* 1.28秒=2048*0.625*/
#endif
#ifndef BTM_BLE_SCAN_SLOW_WIN_1
#define BTM_BLE_SCAN_SLOW_WIN_1   48      /* 30毫秒=48*0.625*/
#endif

/* 在降低功率循环（背景扫描）中使用的默认扫描参数*/
#ifndef BTM_BLE_SCAN_SLOW_INT_2
#define BTM_BLE_SCAN_SLOW_INT_2    4096    /* 2.56秒=4096*0.625*/
#endif
#ifndef BTM_BLE_SCAN_SLOW_WIN_2
#define BTM_BLE_SCAN_SLOW_WIN_2   36      /* 22.5毫秒=36*0.625*/
#endif

/* 默认连接间隔min*/
#ifndef BTM_BLE_CONN_INT_MIN_DEF
#define BTM_BLE_CONN_INT_MIN_DEF     10      /* 建议最小值：12.5 ms=10*1.25*/
#endif

/* 默认连接间隔最大值*/
#ifndef BTM_BLE_CONN_INT_MAX_DEF
#if CONFIG_IDF_TARGET_ESP32
#define BTM_BLE_CONN_INT_MAX_DEF     12      /* 建议最大值：15 ms=12*1.25*/
#else
#define BTM_BLE_CONN_INT_MAX_DEF     (((MAX_ACL_CONNECTIONS + 1) * 4) > 12 ? ((MAX_ACL_CONNECTIONS + 1) * 4) : 12)     /* 建议最大值：BTM_BLE_CONN_INT_max_DEF*1.25毫秒*/
#endif
#endif

/* 默认从属延迟*/
#ifndef BTM_BLE_CONN_SLAVE_LATENCY_DEF
#define BTM_BLE_CONN_SLAVE_LATENCY_DEF  0      /* 0 */
#endif

/* 默认监督超时*/
#ifndef BTM_BLE_CONN_TIMEOUT_DEF
#define BTM_BLE_CONN_TIMEOUT_DEF    600
#endif

/* 最小可接受连接间隔*/
#ifndef BTM_BLE_CONN_INT_MIN_LIMIT
#define BTM_BLE_CONN_INT_MIN_LIMIT     0x0009
#endif

#define BTM_BLE_DIR_CONN_FALLBACK_UNDIR         1
#define BTM_BLE_DIR_CONN_FALLBACK_NO_ADV        2

#ifndef BTM_BLE_DIR_CONN_FALLBACK
#define BTM_BLE_DIR_CONN_FALLBACK   BTM_BLE_DIR_CONN_FALLBACK_UNDIR
#endif

#define BTM_CMAC_TLEN_SIZE          8                   /* 64位*/
#define BTM_BLE_AUTH_SIGN_LEN       12                   /* BLE数据签名长度8字节+4字节计数器*/
typedef UINT8 BLE_SIGNATURE[BTM_BLE_AUTH_SIGN_LEN];         /* 设备地址*/

#ifndef BTM_BLE_HOST_SUPPORT
#define BTM_BLE_HOST_SUPPORT        0x01
#endif

#ifndef BTM_BLE_SIMULTANEOUS_HOST
#define BTM_BLE_SIMULTANEOUS_HOST   0x01
#endif

/* 使用BTM_BLE_AD_TYPE_APPARANCE报告的外观值*/
#define BTM_BLE_APPEARANCE_UNKNOWN                 0x0000
#define BTM_BLE_APPEARANCE_GENERIC_PHONE           0x0040
#define BTM_BLE_APPEARANCE_GENERIC_COMPUTER        0x0080
#define BTM_BLE_APPEARANCE_GENERIC_WATCH           0x00C0
#define BTM_BLE_APPEARANCE_SPORTS_WATCH            0x00C1
#define BTM_BLE_APPEARANCE_GENERIC_CLOCK           0x0100
#define BTM_BLE_APPEARANCE_GENERIC_DISPLAY         0x0140
#define BTM_BLE_APPEARANCE_GENERIC_REMOTE          0x0180
#define BTM_BLE_APPEARANCE_GENERIC_EYEGLASSES      0x01C0
#define BTM_BLE_APPEARANCE_GENERIC_TAG             0x0200
#define BTM_BLE_APPEARANCE_GENERIC_KEYRING         0x0240
#define BTM_BLE_APPEARANCE_GENERIC_MEDIA_PLAYER    0x0280
#define BTM_BLE_APPEARANCE_GENERIC_BARCODE_SCANNER 0x02C0
#define BTM_BLE_APPEARANCE_GENERIC_THERMOMETER     0x0300
#define BTM_BLE_APPEARANCE_THERMOMETER_EAR         0x0301
#define BTM_BLE_APPEARANCE_GENERIC_HEART_RATE      0x0340
#define BTM_BLE_APPEARANCE_HEART_RATE_BELT         0x0341
#define BTM_BLE_APPEARANCE_GENERIC_BLOOD_PRESSURE  0x0380
#define BTM_BLE_APPEARANCE_BLOOD_PRESSURE_ARM      0x0381
#define BTM_BLE_APPEARANCE_BLOOD_PRESSURE_WRIST    0x0382
#define BTM_BLE_APPEARANCE_GENERIC_HID             0x03C0
#define BTM_BLE_APPEARANCE_HID_KEYBOARD            0x03C1
#define BTM_BLE_APPEARANCE_HID_MOUSE               0x03C2
#define BTM_BLE_APPEARANCE_HID_JOYSTICK            0x03C3
#define BTM_BLE_APPEARANCE_HID_GAMEPAD             0x03C4
#define BTM_BLE_APPEARANCE_HID_DIGITIZER_TABLET    0x03C5
#define BTM_BLE_APPEARANCE_HID_CARD_READER         0x03C6
#define BTM_BLE_APPEARANCE_HID_DIGITAL_PEN         0x03C7
#define BTM_BLE_APPEARANCE_HID_BARCODE_SCANNER     0x03C8
#define BTM_BLE_APPEARANCE_GENERIC_GLUCOSE         0x0400
#define BTM_BLE_APPEARANCE_GENERIC_WALKING         0x0440
#define BTM_BLE_APPEARANCE_WALKING_IN_SHOE         0x0441
#define BTM_BLE_APPEARANCE_WALKING_ON_SHOE         0x0442
#define BTM_BLE_APPEARANCE_WALKING_ON_HIP          0x0443
#define BTM_BLE_APPEARANCE_GENERIC_CYCLING         0x0480
#define BTM_BLE_APPEARANCE_CYCLING_COMPUTER        0x0481
#define BTM_BLE_APPEARANCE_CYCLING_SPEED           0x0482
#define BTM_BLE_APPEARANCE_CYCLING_CADENCE         0x0483
#define BTM_BLE_APPEARANCE_CYCLING_POWER           0x0484
#define BTM_BLE_APPEARANCE_CYCLING_SPEED_CADENCE   0x0485
#define BTM_BLE_APPEARANCE_GENERIC_PULSE_OXIMETER  0x0C40
#define BTM_BLE_APPEARANCE_PULSE_OXIMETER_FINGERTIP 0x0C41
#define BTM_BLE_APPEARANCE_PULSE_OXIMETER_WRIST    0x0C42
#define BTM_BLE_APPEARANCE_GENERIC_WEIGHT          0x0C80
#define BTM_BLE_APPEARANCE_GENERIC_PERSONAL_MOBILITY_DEVICE    0x0CC0
#define BTM_BLE_APPEARANCE_POWERED_WHEELCHAIR                  0x0CC1
#define BTM_BLE_APPEARANCE_MOBILITY_SCOOTER                    0x0CC2
#define BTM_BLE_APPEARANCE_GENERIC_CONTINUOUS_GLUCOSE_MONITOR  0x0D00
#define BTM_BLE_APPEARANCE_GENERIC_INSULIN_PUMP                0x0D40
#define BTM_BLE_APPEARANCE_INSULIN_PUMP_DURABLE_PUMP           0x0D41
#define BTM_BLE_APPEARANCE_INSULIN_PUMP_PATCH_PUMP             0x0D44
#define BTM_BLE_APPEARANCE_INSULIN_PEN                         0x0D48
#define BTM_BLE_APPEARANCE_GENERIC_MEDICATION_DELIVERY         0x0D80
#define BTM_BLE_APPEARANCE_GENERIC_OUTDOOR_SPORTS  0x1440
#define BTM_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION 0x1441
#define BTM_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_AND_NAV     0x1442
#define BTM_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD         0x1443
#define BTM_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD_AND_NAV 0x1444


/* 随机/加密完整回调返回的结构*/
typedef struct {
    UINT8   status;
    UINT8   param_len;
    UINT16  opcode;
    UINT8   param_buf[BT_OCTET16_LEN];
} tBTM_RAND_ENC;

/* 用于通知应用程序同步BTM功能已完成的常规回调函数。指针包含任何返回数据的地址。
*/
typedef void (tBTM_RAND_ENC_CB) (tBTM_RAND_ENC *p1);

#define BTM_BLE_FILTER_TARGET_SCANNER       0x01
#define BTM_BLE_FILTER_TARGET_ADVR          0x00

#define BTM_BLE_POLICY_BLACK_ALL            0x00    /* 与两者相关*/
#define BTM_BLE_POLICY_ALLOW_SCAN           0x01    /* 与广告商相关*/
#define BTM_BLE_POLICY_ALLOW_CONN           0x02    /* 与广告商相关*/
#define BTM_BLE_POLICY_WHITE_ALL            0x03    /* 与两者相关*/

/* 用于BTM_BLE_AD_TYPE_flag的ADV数据标志位定义*/
#define BTM_BLE_LIMIT_DISC_FLAG         (0x01 << 0)
#define BTM_BLE_GEN_DISC_FLAG           (0x01 << 1)
#define BTM_BLE_BREDR_NOT_SPT           (0x01 << 2)
/* 4.1同步BR/EDR+LE连接支持的规范adv标志*/
#define BTM_BLE_DMT_CONTROLLER_SPT      (0x01 << 3)
#define BTM_BLE_DMT_HOST_SPT            (0x01 << 4)
#define BTM_BLE_NON_LIMIT_DISC_FLAG     (0x00 )         /* 最低位未设置*/
#define BTM_BLE_ADV_FLAG_MASK           (BTM_BLE_LIMIT_DISC_FLAG | BTM_BLE_BREDR_NOT_SPT | BTM_BLE_GEN_DISC_FLAG)
#define BTM_BLE_LIMIT_DISC_MASK         (BTM_BLE_LIMIT_DISC_FLAG )

#define BTM_BLE_AD_BIT_DEV_NAME        (0x00000001 << 0)
#define BTM_BLE_AD_BIT_FLAGS           (0x00000001 << 1)
#define BTM_BLE_AD_BIT_MANU            (0x00000001 << 2)
#define BTM_BLE_AD_BIT_TX_PWR          (0x00000001 << 3)
#define BTM_BLE_AD_BIT_INT_RANGE       (0x00000001 << 5)
#define BTM_BLE_AD_BIT_SERVICE         (0x00000001 << 6)
#define BTM_BLE_AD_BIT_SERVICE_SOL     (0x00000001 << 7)
#define BTM_BLE_AD_BIT_SERVICE_DATA    (0x00000001 << 8)
#define BTM_BLE_AD_BIT_SIGN_DATA       (0x00000001 << 9)
#define BTM_BLE_AD_BIT_SERVICE_128SOL  (0x00000001 << 10)
#define BTM_BLE_AD_BIT_APPEARANCE      (0x00000001 << 11)
#define BTM_BLE_AD_BIT_PUBLIC_ADDR      (0x00000001 << 12)
#define BTM_BLE_AD_BIT_RANDOM_ADDR       (0x00000001 << 13)
#define BTM_BLE_AD_BIT_SERVICE_32        (0x00000001 << 4)
#define BTM_BLE_AD_BIT_SERVICE_32SOL     (0x00000001 << 14)
#define BTM_BLE_AD_BIT_PROPRIETARY     (0x00000001 << 15)
#define BTM_BLE_AD_BIT_SERVICE_128      (0x00000001 << 16)      /*128位服务UUID*/

typedef  UINT32  tBTM_BLE_AD_MASK;

/* 与ESP_gap_BLE_api中的ESP_BLE_AD_TYPE_xxx相关。小时*/
#define BTM_BLE_AD_TYPE_FLAG                HCI_EIR_FLAGS_TYPE                  /* 0x01*/
#define BTM_BLE_AD_TYPE_16SRV_PART          HCI_EIR_MORE_16BITS_UUID_TYPE       /* 0x02*/
#define BTM_BLE_AD_TYPE_16SRV_CMPL          HCI_EIR_COMPLETE_16BITS_UUID_TYPE   /* 0x03*/
#define BTM_BLE_AD_TYPE_32SRV_PART          HCI_EIR_MORE_32BITS_UUID_TYPE       /* 0x04*/
#define BTM_BLE_AD_TYPE_32SRV_CMPL          HCI_EIR_COMPLETE_32BITS_UUID_TYPE   /* 0x05*/
#define BTM_BLE_AD_TYPE_128SRV_PART         HCI_EIR_MORE_128BITS_UUID_TYPE       /* 0x06*/
#define BTM_BLE_AD_TYPE_128SRV_CMPL         HCI_EIR_COMPLETE_128BITS_UUID_TYPE   /* 0x07*/
#define BTM_BLE_AD_TYPE_NAME_SHORT          HCI_EIR_SHORTENED_LOCAL_NAME_TYPE       /* 0x08*/
#define BTM_BLE_AD_TYPE_NAME_CMPL           HCI_EIR_COMPLETE_LOCAL_NAME_TYPE        /* 0x09*/
#define BTM_BLE_AD_TYPE_TX_PWR              HCI_EIR_TX_POWER_LEVEL_TYPE             /* 0x0A*/
#define BTM_BLE_AD_TYPE_DEV_CLASS           0x0D
#define BTM_BLE_AD_TYPE_SM_TK               0x10
#define BTM_BLE_AD_TYPE_SM_OOB_FLAG         0x11
#define BTM_BLE_AD_TYPE_INT_RANGE           0x12
#define BTM_BLE_AD_TYPE_SOL_SRV_UUID        0x14
#define BTM_BLE_AD_TYPE_128SOL_SRV_UUID     0x15
#define BTM_BLE_AD_TYPE_SERVICE_DATA        0x16
#define BTM_BLE_AD_TYPE_PUBLIC_TARGET       0x17
#define BTM_BLE_AD_TYPE_RANDOM_TARGET       0x18
#define BTM_BLE_AD_TYPE_APPEARANCE          0x19
#define BTM_BLE_AD_TYPE_ADV_INT             0x1a
#define BTM_BLE_AD_TYPE_LE_DEV_ADDR         0x1b
#define BTM_BLE_AD_TYPE_LE_ROLE             0x1c
#define BTM_BLE_AD_TYPE_SPAIR_C256          0x1d
#define BTM_BLE_AD_TYPE_SPAIR_R256          0x1e
#define BTM_BLE_AD_TYPE_32SOL_SRV_UUID      0x1f
#define BTM_BLE_AD_TYPE_32SERVICE_DATA      0x20
#define BTM_BLE_AD_TYPE_128SERVICE_DATA     0x21
#define BTM_BLE_AD_TYPE_LE_SECURE_CONFIRM   0x22
#define BTM_BLE_AD_TYPE_LE_SECURE_RANDOM    0x23
#define BTM_BLE_AD_TYPE_URI                 0x24
#define BTM_BLE_AD_TYPE_INDOOR_POSITION     0x25
#define BTM_BLE_AD_TYPE_TRANS_DISC_DATA     0x26
#define BTM_BLE_AD_TYPE_LE_SUPPORT_FEATURE  0x27
#define BTM_BLE_AD_TYPE_CHAN_MAP_UPDATE     0x28

#define BTM_BLE_AD_TYPE_MANU            HCI_EIR_MANUFACTURER_SPECIFIC_TYPE      /* 0xff（0xff）*/
typedef UINT8   tBTM_BLE_AD_TYPE;

#define BTM_BLE_LONG_ADV_MAX_LEN  249

/*  L2CAP LE COC使用的安全设置*/
#define BTM_SEC_LE_LINK_ENCRYPTED           0x01
#define BTM_SEC_LE_LINK_PAIRED_WITHOUT_MITM 0x02
#define BTM_SEC_LE_LINK_PAIRED_WITH_MITM    0x04

/*  最小/最大本地控制器应包括在单个链路层数据信道PDU中的有效载荷八位字节的首选数量。*/
#define BTM_BLE_DATA_SIZE_MAX     0x00fb
#define BTM_BLE_DATA_SIZE_MIN     0x001b

/*  本地控制器应用于传输单个链路层数据信道PDU的首选最大微秒数。*/
#define BTM_BLE_DATA_TX_TIME_MIN     0x0148
#if (BLE_50_FEATURE_SUPPORT == TRUE)
#define BTM_BLE_DATA_TX_TIME_MAX     0x04290 // 按规范v5.0定义
#else
#define BTM_BLE_DATA_TX_TIME_MAX     0x0848
#endif

/* adv tx功率电平*/
#define BTM_BLE_ADV_TX_POWER_MIN        0           /* 最小发射功率*/
#define BTM_BLE_ADV_TX_POWER_MAX        7           /* 最大发射功率*/
typedef UINT8 tBTM_BLE_ADV_TX_POWER;

/* adv tx功率（dBm）*/
typedef struct {
    UINT8 adv_inst_max;         /* 控制器中支持的最大adv实例*/
    UINT8 rpa_offloading;
    UINT16 tot_scan_results_strg;
    UINT8 max_irk_list_sz;
    UINT8 filter_support;
    UINT8 max_filter;
    UINT8 energy_support;
    BOOLEAN values_read;
    UINT16 version_supported;
    UINT16 total_trackable_advertisers;
    UINT8 extended_scan_support;
    UINT8 debug_logging_supported;
} tBTM_BLE_VSC_CB;

/* 从属首选连接间隔范围*/
typedef struct {
    UINT16  low;
    UINT16  hi;

} tBTM_BLE_INT_RANGE;

/* 设备中支持的服务标签*/
typedef struct {
    UINT8       num_service;
    BOOLEAN     list_cmpl;
    UINT16      *p_uuid;
} tBTM_BLE_SERVICE;

/* 设备支持32位服务*/
typedef struct {
    UINT8       num_service;
    BOOLEAN     list_cmpl;
    UINT32      *p_uuid;
} tBTM_BLE_32SERVICE;

/* 设备支持128位服务*/
typedef struct {
    BOOLEAN     list_cmpl;
    UINT8       uuid128[MAX_UUID_SIZE];
} tBTM_BLE_128SERVICE;

typedef struct {
    UINT8       len;
    UINT8      *p_val;
} tBTM_BLE_MANU;


typedef struct {
    tBT_UUID    service_uuid;
    UINT8       len;
    UINT8      *p_val;
} tBTM_BLE_SERVICE_DATA;

typedef struct {
    UINT8       adv_type;
    UINT8       len;
    UINT8       *p_val;     /* len字节数*/
} tBTM_BLE_PROP_ELEM;

typedef struct {
    UINT8                   num_elem;
    tBTM_BLE_PROP_ELEM      *p_elem;
} tBTM_BLE_PROPRIETARY;

typedef struct {
    tBTM_BLE_INT_RANGE      int_range;      /* 从属优先连接间隔范围*/
    tBTM_BLE_MANU           *p_manu;           /* 制造商数据*/
    tBTM_BLE_SERVICE        *p_services;       /* 服务*/
    tBTM_BLE_128SERVICE     *p_services_128b;  /* 128位服务*/
    tBTM_BLE_32SERVICE      *p_service_32b;     /* 32位服务UUID*/
    tBTM_BLE_SERVICE        *p_sol_services;    /* 16位服务请求UUID*/
    tBTM_BLE_32SERVICE      *p_sol_service_32b;    /* 32位服务请求UUID列表*/
    tBTM_BLE_128SERVICE     *p_sol_service_128b;    /* 128位服务请求UUID列表*/
    tBTM_BLE_PROPRIETARY    *p_proprietary;
    tBTM_BLE_SERVICE_DATA   *p_service_data;    /* 服务数据*/
    UINT16                  appearance;
    UINT8                   flag;
    UINT8                   tx_power;
} tBTM_BLE_ADV_DATA;

#ifndef BTM_BLE_MULTI_ADV_MAX
#define BTM_BLE_MULTI_ADV_MAX   16 /* 控制器返回的adv_inst_max应小于此数字*/
#endif

#define BTM_BLE_MULTI_ADV_INVALID   0

#define BTM_BLE_MULTI_ADV_ENB_EVT           1
#define BTM_BLE_MULTI_ADV_DISABLE_EVT       2
#define BTM_BLE_MULTI_ADV_PARAM_EVT         3
#define BTM_BLE_MULTI_ADV_DATA_EVT          4
typedef UINT8 tBTM_BLE_MULTI_ADV_EVT;

#define BTM_BLE_MULTI_ADV_DEFAULT_STD 0

typedef struct {
    UINT16          adv_int_min;
    UINT16          adv_int_max;
    UINT8           adv_type;
    tBTM_BLE_ADV_CHNL_MAP channel_map;
    tBTM_BLE_AFP    adv_filter_policy;
    tBTM_BLE_ADV_TX_POWER tx_power;
} tBTM_BLE_ADV_PARAMS;

typedef struct {
    UINT8   *p_sub_code; /* 存储子代码的动态数组*/
    UINT8   *p_inst_id;  /* 用于存储实例id的动态数组*/
    UINT8   pending_idx;
    UINT8   next_idx;
} tBTM_BLE_MULTI_ADV_OPQ;

typedef void (tBTM_BLE_MULTI_ADV_CBACK)(tBTM_BLE_MULTI_ADV_EVT evt, UINT8 inst_id,
                                        void *p_ref, tBTM_STATUS status);

typedef struct {
    UINT8                       inst_id;
    BOOLEAN                     in_use;
    UINT8                       adv_evt;
    BD_ADDR                     rpa;
    TIMER_LIST_ENT              raddr_timer_ent;
    tBTM_BLE_MULTI_ADV_CBACK    *p_cback;
    void                        *p_ref;
    UINT8                       index;
} tBTM_BLE_MULTI_ADV_INST;

typedef struct {
    UINT8 inst_index_queue[BTM_BLE_MULTI_ADV_MAX];
    int front;
    int rear;
} tBTM_BLE_MULTI_ADV_INST_IDX_Q;

typedef struct {
    tBTM_BLE_MULTI_ADV_INST *p_adv_inst; /* 存储adv实例的动态数组*/
    tBTM_BLE_MULTI_ADV_OPQ  op_q;
} tBTM_BLE_MULTI_ADV_CB;

typedef UINT8 tGATT_IF;

typedef void (tBTM_BLE_SCAN_THRESHOLD_CBACK)(tBTM_BLE_REF_VALUE ref_value);
typedef void (tBTM_BLE_SCAN_REP_CBACK)(tBTM_BLE_REF_VALUE ref_value, UINT8 report_format,
                                       UINT8 num_records, UINT16 total_len,
                                       UINT8 *p_rep_data, UINT8 status);
typedef void (tBTM_BLE_SCAN_SETUP_CBACK)(UINT8 evt, tBTM_BLE_REF_VALUE ref_value, UINT8 status);

#ifndef BTM_BLE_BATCH_SCAN_MAX
#define BTM_BLE_BATCH_SCAN_MAX   5
#endif

#ifndef BTM_BLE_BATCH_REP_MAIN_Q_SIZE
#define BTM_BLE_BATCH_REP_MAIN_Q_SIZE  2
#endif

typedef enum {
    BTM_BLE_SCAN_INVALID_STATE = 0,
    BTM_BLE_SCAN_ENABLE_CALLED = 1,
    BTM_BLE_SCAN_ENABLED_STATE = 2,
    BTM_BLE_SCAN_DISABLE_CALLED = 3,
    BTM_BLE_SCAN_DISABLED_STATE = 4
} tBTM_BLE_BATCH_SCAN_STATE;

enum {
    BTM_BLE_DISCARD_OLD_ITEMS,
    BTM_BLE_DISCARD_LOWER_RSSI_ITEMS
};
typedef UINT8 tBTM_BLE_DISCARD_RULE;

typedef struct {
    UINT8   sub_code[BTM_BLE_BATCH_SCAN_MAX];
    tBTM_BLE_BATCH_SCAN_STATE cur_state[BTM_BLE_BATCH_SCAN_MAX];
    tBTM_BLE_REF_VALUE        ref_value[BTM_BLE_BATCH_SCAN_MAX];
    UINT8   pending_idx;
    UINT8   next_idx;
} tBTM_BLE_BATCH_SCAN_OPQ;

typedef struct {
    UINT8   rep_mode[BTM_BLE_BATCH_REP_MAIN_Q_SIZE];
    tBTM_BLE_REF_VALUE  ref_value[BTM_BLE_BATCH_REP_MAIN_Q_SIZE];
    UINT8   num_records[BTM_BLE_BATCH_REP_MAIN_Q_SIZE];
    UINT16  data_len[BTM_BLE_BATCH_REP_MAIN_Q_SIZE];
    UINT8   *p_data[BTM_BLE_BATCH_REP_MAIN_Q_SIZE];
    UINT8   pending_idx;
    UINT8   next_idx;
} tBTM_BLE_BATCH_SCAN_REP_Q;

typedef struct {
    tBTM_BLE_BATCH_SCAN_STATE      cur_state;
    tBTM_BLE_BATCH_SCAN_MODE scan_mode;
    UINT32                  scan_interval;
    UINT32                  scan_window;
    tBLE_ADDR_TYPE          addr_type;
    tBTM_BLE_DISCARD_RULE   discard_rule;
    tBTM_BLE_BATCH_SCAN_OPQ  op_q;
    tBTM_BLE_BATCH_SCAN_REP_Q main_rep_q;
    tBTM_BLE_SCAN_SETUP_CBACK     *p_setup_cback;
    tBTM_BLE_SCAN_THRESHOLD_CBACK *p_thres_cback;
    tBTM_BLE_SCAN_REP_CBACK       *p_scan_rep_cback;
    tBTM_BLE_REF_VALUE             ref_value;
} tBTM_BLE_BATCH_SCAN_CB;

///Ble扫描重复类型
enum {
    BTM_BLE_SCAN_DUPLICATE_DISABLE           = 0x0,  /*!< 链路层应为接收到的每个数据包向主机生成广告报告*/
    BTM_BLE_SCAN_DUPLICATE_ENABLE            = 0x1,  /*!< 链接层应过滤出向主机发送的重复广告报告*/
    BTM_BLE_SCAN_DUPLICATE_MAX               = 0x2,  /*!< 0x02–0xFF，保留以备将来使用*/
};
/* 滤波器选择位索引*/
#define BTM_BLE_PF_ADDR_FILTER          0
#define BTM_BLE_PF_SRVC_DATA            1
#define BTM_BLE_PF_SRVC_UUID            2
#define BTM_BLE_PF_SRVC_SOL_UUID        3
#define BTM_BLE_PF_LOCAL_NAME           4
#define BTM_BLE_PF_MANU_DATA            5
#define BTM_BLE_PF_SRVC_DATA_PATTERN    6
#define BTM_BLE_PF_TYPE_ALL             7  /* 当传入有效负载筛选器类型all时，只有清除操作适用*/
#define BTM_BLE_PF_TYPE_MAX             8

/* 不同过滤器类型的最大过滤点数量*/
#ifndef BTM_BLE_MAX_UUID_FILTER
#define BTM_BLE_MAX_UUID_FILTER     8
#endif
#ifndef BTM_BLE_MAX_ADDR_FILTER
#define BTM_BLE_MAX_ADDR_FILTER     8
#endif
#ifndef BTM_BLE_PF_STR_COND_MAX
#define BTM_BLE_PF_STR_COND_MAX     4   /* 应用于manu数据或本地名称*/
#endif
#ifndef BTM_BLE_PF_STR_LEN_MAX
#define BTM_BLE_PF_STR_LEN_MAX      29  /* 匹配前29个字节*/
#endif

typedef UINT8   tBTM_BLE_PF_COND_TYPE;

#define BTM_BLE_PF_LOGIC_OR              0
#define BTM_BLE_PF_LOGIC_AND             1
typedef UINT8 tBTM_BLE_PF_LOGIC_TYPE;

#define BTM_BLE_PF_ENABLE       1
#define BTM_BLE_PF_CONFIG       2
typedef UINT8 tBTM_BLE_PF_ACTION;

typedef UINT8 tBTM_BLE_PF_FILT_INDEX;

typedef UINT8 tBTM_BLE_PF_AVBL_SPACE;

#define BTM_BLE_PF_BRDCAST_ADDR_FILT  1
#define BTM_BLE_PF_SERV_DATA_CHG_FILT 2
#define BTM_BLE_PF_SERV_UUID          4
#define BTM_BLE_PF_SERV_SOLC_UUID     8
#define BTM_BLE_PF_LOC_NAME_CHECK    16
#define BTM_BLE_PF_MANUF_NAME_CHECK  32
#define BTM_BLE_PF_SERV_DATA_CHECK   64
typedef UINT16 tBTM_BLE_PF_FEAT_SEL;

#define BTM_BLE_PF_LIST_LOGIC_OR   1
#define BTM_BLE_PF_LIST_LOGIC_AND  2
typedef UINT16 tBTM_BLE_PF_LIST_LOGIC_TYPE;

#define BTM_BLE_PF_FILT_LOGIC_OR   0
#define BTM_BLE_PF_FILT_LOGIC_AND  1
typedef UINT16 tBTM_BLE_PF_FILT_LOGIC_TYPE;

typedef UINT8  tBTM_BLE_PF_RSSI_THRESHOLD;
typedef UINT8  tBTM_BLE_PF_DELIVERY_MODE;
typedef UINT16 tBTM_BLE_PF_TIMEOUT;
typedef UINT8  tBTM_BLE_PF_TIMEOUT_CNT;
typedef UINT16 tBTM_BLE_PF_ADV_TRACK_ENTRIES;

typedef struct {
    tBTM_BLE_PF_FEAT_SEL feat_seln;
    tBTM_BLE_PF_LIST_LOGIC_TYPE logic_type;
    tBTM_BLE_PF_FILT_LOGIC_TYPE filt_logic_type;
    tBTM_BLE_PF_RSSI_THRESHOLD  rssi_high_thres;
    tBTM_BLE_PF_RSSI_THRESHOLD  rssi_low_thres;
    tBTM_BLE_PF_DELIVERY_MODE dely_mode;
    tBTM_BLE_PF_TIMEOUT found_timeout;
    tBTM_BLE_PF_TIMEOUT lost_timeout;
    tBTM_BLE_PF_TIMEOUT_CNT found_timeout_cnt;
    tBTM_BLE_PF_ADV_TRACK_ENTRIES num_of_tracking_entries;
} tBTM_BLE_PF_FILT_PARAMS;

enum {
    BTM_BLE_SCAN_COND_ADD,
    BTM_BLE_SCAN_COND_DELETE,
    BTM_BLE_SCAN_COND_CLEAR = 2
};
typedef UINT8 tBTM_BLE_SCAN_COND_OP;

enum {
    BTM_BLE_FILT_ENABLE_DISABLE = 1,
    BTM_BLE_FILT_CFG            = 2,
    BTM_BLE_FILT_ADV_PARAM      = 3
};

typedef UINT8 tBTM_BLE_FILT_CB_EVT;

/* BLE adv负载过滤配置完成回调*/
typedef void (tBTM_BLE_PF_CFG_CBACK)(tBTM_BLE_PF_ACTION action, tBTM_BLE_SCAN_COND_OP cfg_op,
                                     tBTM_BLE_PF_AVBL_SPACE avbl_space, tBTM_STATUS status,
                                     tBTM_BLE_REF_VALUE ref_value);

typedef void (tBTM_BLE_PF_CMPL_CBACK) (tBTM_BLE_PF_CFG_CBACK);

/* BLE adv负载过滤状态设置完成回调*/
typedef void (tBTM_BLE_PF_STATUS_CBACK) (UINT8 action, tBTM_STATUS status,
        tBTM_BLE_REF_VALUE ref_value);

/* BLE adv有效负载过滤参数设置完成回调*/
typedef void (tBTM_BLE_PF_PARAM_CBACK) (tBTM_BLE_PF_ACTION action_type,
                                        tBTM_BLE_PF_AVBL_SPACE avbl_space,
                                        tBTM_BLE_REF_VALUE ref_value, tBTM_STATUS status);
#if (BLE_50_FEATURE_SUPPORT == TRUE)
#define MAX_BLE_ADV_INSTANCE 10
typedef struct {
    UINT8                       inst_id;
    BOOLEAN                     configured;
    BOOLEAN                     legacy_pdu;


    BOOLEAN                     directed;
    BOOLEAN                     scannable;
    BOOLEAN                     connetable;
} tBTM_BLE_EXTENDED_INST;

typedef struct {
    tBTM_BLE_EXTENDED_INST inst[MAX_BLE_ADV_INSTANCE]; /* 存储adv实例的动态数组*/
    UINT8  scan_duplicate;
} tBTM_BLE_EXTENDED_CB;

#define BTM_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE       (1 << 0)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE         (1 << 1)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED          (1 << 2)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED       (1 << 3)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY            (1 << 4)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_ANON_ADV          (1 << 5)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_INCLUDE_TX_PWR    (1 << 6)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_MASK              (0x7F)

#define BTM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_IND        (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_LD_DIR     (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_HD_DIR     (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_SCAN       (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                     ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE)
#define BTM_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_NONCONN    (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY)
typedef UINT16 tBTM_BLE_EXT_ADV_TYPE_MASK;

#define BTM_BLE_GAP_PHY_1M                             1
#define BTM_BLE_GAP_PHY_2M                             2
#define BTM_BLE_GAP_PHY_CODED                          3
typedef UINT8 tBTM_BLE_GAP_PHY;

#define BTM_BLE_GAP_PHY_NO_TX_PREF_MASK                (0x01)
#define BTM_BLE_GAP_PHY_NO_RX_PREF_MASK                (0x02)
#define BTM_BLE_GAP_PHY_1M_PREF_MASK                   (0x03)
#define BTM_BLE_GAP_PHY_2M_PREF_MASK                   (0x04)
#define BTM_BLE_GAP_PHY_CODED_PREF_MASK                (0x05)
typedef UINT8 tBTM_BLE_GAP_PHY_MASK;

#define BTM_BLE_GAP_EXT_SCAN_UNCODE_MASK               0x01
#define BTM_BLE_GAP_EXT_SCAN_CODE_MASK                 0x02
typedef UINT8 tBTM_BLE_EXT_SCAN_CFG_MASK;

typedef struct {
    tBTM_BLE_EXT_ADV_TYPE_MASK type;
    UINT32 interval_min;
    UINT32 interval_max;
    tBTM_BLE_ADV_CHNL_MAP channel_map;
    tBLE_ADDR_TYPE own_addr_type;
    tBLE_ADDR_TYPE peer_addr_type;
    BD_ADDR peer_addr;
    tBTM_BLE_AFP filter_policy;
    UINT8 tx_power;
    tBTM_BLE_GAP_PHY primary_phy;
    UINT8 max_skip;
    tBTM_BLE_GAP_PHY secondary_phy;
    UINT8 sid;
    BOOLEAN scan_req_notif;
} tBTM_BLE_GAP_EXT_ADV_PARAMS;

typedef struct {
    UINT8 instance;
    int duration;
    int max_events;
} tBTM_BLE_EXT_ADV;


typedef struct {
    tBLE_SCAN_MODE scan_type;
    UINT16 scan_interval;
    UINT16 scan_window;
} tBTM_BLE_EXT_SCAN_CFG;

typedef struct {
    tBLE_ADDR_TYPE own_addr_type;
    UINT8 filter_policy;
    UINT8  scan_duplicate;
    tBTM_BLE_EXT_SCAN_CFG_MASK cfg_mask;
    tBTM_BLE_EXT_SCAN_CFG uncoded_cfg;
    tBTM_BLE_EXT_SCAN_CFG coded_cfg;
} tBTM_BLE_EXT_SCAN_PARAMS;

typedef struct {
    UINT16 interval_min;
    UINT16 interval_max;
    UINT8  properties;
} tBTM_BLE_Periodic_Adv_Params;

typedef struct {
    UINT8 filter_policy;
    UINT8 sid;
    tBLE_ADDR_TYPE addr_type;
    BD_ADDR addr;
    UINT16 skip;
    UINT16 sync_timeout;
} tBTM_BLE_Periodic_Sync_Params;

typedef struct {
    uint8_t status;
    uint16_t conn_idx;
    uint8_t tx_phy;
    uint8_t rx_phy;
} tBTM_BLE_UPDATE_PHY;
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
typedef union {
    UINT16              uuid16_mask;
    UINT32              uuid32_mask;
    UINT8               uuid128_mask[LEN_UUID_128];
} tBTM_BLE_PF_COND_MASK;

typedef struct {
    tBLE_BD_ADDR            *p_target_addr;     /* 目标地址，如果为NULL，则为通用UUID筛选器*/
    tBT_UUID                uuid;           /* UUID条件*/
    tBTM_BLE_PF_LOGIC_TYPE  cond_logic;    /* AND/OR */
    tBTM_BLE_PF_COND_MASK   *p_uuid_mask;           /* UUID掩码*/
} tBTM_BLE_PF_UUID_COND;

typedef struct {
    UINT8                   data_len;       /* <=20字节*/
    UINT8                   *p_data;
} tBTM_BLE_PF_LOCAL_NAME_COND;

typedef struct {
    UINT16                  company_id;     /* 公司ID*/
    UINT8                   data_len;       /* <=20字节*/
    UINT8                   *p_pattern;
    UINT16                  company_id_mask; /* UUID值掩码*/
    UINT8                   *p_pattern_mask; /* 制造商数据匹配掩码，长度与数据模式相同，设置为所有0xff，匹配精确数据*/
} tBTM_BLE_PF_MANU_COND;

typedef struct {
    UINT16                  uuid;     /* 服务ID*/
    UINT8                   data_len;       /* <=20字节*/
    UINT8                   *p_pattern;
    UINT8                   *p_pattern_mask; /* 服务数据匹配掩码，长度与数据模式相同，设置为所有0xff，匹配精确数据*/
} tBTM_BLE_PF_SRVC_PATTERN_COND;


typedef union {
    tBLE_BD_ADDR                            target_addr;
    tBTM_BLE_PF_LOCAL_NAME_COND             local_name; /* 本地名称筛选*/
    tBTM_BLE_PF_MANU_COND                   manu_data;  /* 制造商数据过滤*/
    tBTM_BLE_PF_UUID_COND                   srvc_uuid;  /* 服务UUID筛选*/
    tBTM_BLE_PF_UUID_COND                   solicitate_uuid;   /* 请求服务UUID筛选*/
    tBTM_BLE_PF_SRVC_PATTERN_COND           srvc_data;      /* 服务数据模式*/
} tBTM_BLE_PF_COND_PARAM;

typedef struct {
    UINT8   action_ocf[BTM_BLE_PF_TYPE_MAX];
    tBTM_BLE_REF_VALUE  ref_value[BTM_BLE_PF_TYPE_MAX];
    tBTM_BLE_PF_PARAM_CBACK  *p_filt_param_cback[BTM_BLE_PF_TYPE_MAX];
    tBTM_BLE_PF_CFG_CBACK *p_scan_cfg_cback[BTM_BLE_PF_TYPE_MAX];
    UINT8   cb_evt[BTM_BLE_PF_TYPE_MAX];
    UINT8   pending_idx;
    UINT8   next_idx;
} tBTM_BLE_ADV_FILTER_ADV_OPQ;

#define BTM_BLE_MAX_FILTER_COUNTER  (BTM_BLE_MAX_ADDR_FILTER + 1) /* 每个设备筛选器+一个由0索引的通用筛选器*/

#ifndef BTM_CS_IRK_LIST_MAX
#define BTM_CS_IRK_LIST_MAX 0x20
#endif

typedef struct {
    BOOLEAN    in_use;
    BD_ADDR    bd_addr;
    UINT8      pf_counter[BTM_BLE_PF_TYPE_MAX]; /* 按tBTM_BLE_PF_COND_TYPE索引的过滤器数量*/
} tBTM_BLE_PF_COUNT;

typedef struct {
    BOOLEAN             enable;
    UINT8               op_type;
    tBTM_BLE_PF_COUNT   *p_addr_filter_count; /* 每个BDA滤波器阵列*/
    tBLE_BD_ADDR        cur_filter_target;
    tBTM_BLE_PF_STATUS_CBACK *p_filt_stat_cback;
    tBTM_BLE_ADV_FILTER_ADV_OPQ  op_q;
} tBTM_BLE_ADV_FILTER_CB;

/* 子代码*/
#define BTM_BLE_META_PF_ENABLE          0x00
#define BTM_BLE_META_PF_FEAT_SEL        0x01
#define BTM_BLE_META_PF_ADDR            0x02
#define BTM_BLE_META_PF_UUID            0x03
#define BTM_BLE_META_PF_SOL_UUID        0x04
#define BTM_BLE_META_PF_LOCAL_NAME      0x05
#define BTM_BLE_META_PF_MANU_DATA       0x06
#define BTM_BLE_META_PF_SRVC_DATA       0x07
#define BTM_BLE_META_PF_ALL             0x08

typedef UINT8 BTM_BLE_ADV_STATE;
typedef UINT8 BTM_BLE_ADV_INFO_PRESENT;
typedef UINT8 BTM_BLE_RSSI_VALUE;
typedef UINT16 BTM_BLE_ADV_INFO_TIMESTAMP;

/* 这些是每个设备adv数据包中返回的字段。如果已注册，则在结果回调中返回。
*/
typedef struct {
    UINT8               conn_mode;
    tBTM_BLE_AD_MASK    ad_mask;        /* 有效adv数据字段的掩码*/
    UINT8               flag;
    UINT8               tx_power_level;
    UINT8               remote_name_len;
    UINT8               *p_remote_name;
    tBTM_BLE_SERVICE    service;
} tBTM_BLE_INQ_DATA;

enum {
    BTM_BLE_CONN_NONE,
    BTM_BLE_CONN_AUTO,
    BTM_BLE_CONN_SELECTIVE
};
typedef UINT8   tBTM_BLE_CONN_TYPE;

#define ADV_INFO_PRESENT        0x00
#define NO_ADV_INFO_PRESENT     0x01

typedef btgatt_track_adv_info_t tBTM_BLE_TRACK_ADV_DATA;

typedef void (tBTM_BLE_TRACK_ADV_CBACK)(tBTM_BLE_TRACK_ADV_DATA *p_track_adv_data);

typedef UINT8 tBTM_BLE_TRACK_ADV_EVT;

typedef struct {
    tBTM_BLE_REF_VALUE             ref_value;
    tBTM_BLE_TRACK_ADV_CBACK *p_track_cback;
} tBTM_BLE_ADV_TRACK_CB;

enum {
    BTM_BLE_TRACK_ADV_ADD,
    BTM_BLE_TRACK_ADV_REMOVE
};

typedef UINT8 tBTM_BLE_TRACK_ADV_ACTION;

#define BTM_BLE_MULTI_ADV_INVALID   0

#define BTM_BLE_BATCH_SCAN_ENABLE_EVT     1
#define BTM_BLE_BATCH_SCAN_CFG_STRG_EVT   2
#define BTM_BLE_BATCH_SCAN_READ_REPTS_EVT 3
#define BTM_BLE_BATCH_SCAN_THR_EVT        4
#define BTM_BLE_BATCH_SCAN_PARAM_EVT      5
#define BTM_BLE_BATCH_SCAN_DISABLE_EVT    6

typedef UINT8 tBTM_BLE_BATCH_SCAN_EVT;

typedef UINT32 tBTM_BLE_TX_TIME_MS;
typedef UINT32 tBTM_BLE_RX_TIME_MS;
typedef UINT32 tBTM_BLE_IDLE_TIME_MS;
typedef UINT32 tBTM_BLE_ENERGY_USED;

typedef void (tBTM_BLE_ENERGY_INFO_CBACK)(tBTM_BLE_TX_TIME_MS tx_time, tBTM_BLE_RX_TIME_MS rx_time,
        tBTM_BLE_IDLE_TIME_MS idle_time,
        tBTM_BLE_ENERGY_USED  energy_used,
        tBTM_STATUS status);

typedef struct {
    tBTM_BLE_ENERGY_INFO_CBACK *p_ener_cback;
} tBTM_BLE_ENERGY_INFO_CB;

typedef BOOLEAN (tBTM_BLE_SEL_CBACK)(BD_ADDR random_bda,     UINT8 *p_remote_name);
typedef void (tBTM_BLE_CTRL_FEATURES_CBACK)(tBTM_STATUS status);

/* SMP签名算法的回调函数，以小端顺序签名的数据，长度为tlen位*/
typedef void (tBTM_BLE_SIGN_CBACK)(void *p_ref_data, UINT8 *p_signing_data);
typedef void (tBTM_BLE_VERIFY_CBACK)(void *p_ref_data, BOOLEAN match);
/* 随机地址集完成回调*/
typedef void (tBTM_BLE_RANDOM_SET_CBACK) (BD_ADDR random_bda);

typedef void (tBTM_BLE_SCAN_REQ_CBACK)(BD_ADDR remote_bda, tBLE_ADDR_TYPE addr_type, UINT8 adv_evt);
typedef void (*tBLE_SCAN_PARAM_SETUP_CBACK)(tGATT_IF client_if, tBTM_STATUS status);

tBTM_BLE_SCAN_SETUP_CBACK bta_ble_scan_setup_cb;

typedef void (tBTM_START_ADV_CMPL_CBACK) (UINT8 status);
typedef void (tBTM_START_STOP_ADV_CMPL_CBACK) (UINT8 status);

typedef void (tBTM_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK) (tBTM_STATUS status, uint8_t subcode, uint32_t length, uint8_t *device_info);
#if (BLE_50_FEATURE_SUPPORT == TRUE)
#define    BTM_BLE_5_GAP_READ_PHY_COMPLETE_EVT                     1
#define    BTM_BLE_5_GAP_SET_PREFERED_DEFAULT_PHY_COMPLETE_EVT     2
#define    BTM_BLE_5_GAP_SET_PREFERED_PHY_COMPLETE_EVT             3
#define    BTM_BLE_5_GAP_EXT_ADV_SET_RAND_ADDR_COMPLETE_EVT        4
#define    BTM_BLE_5_GAP_EXT_ADV_SET_PARAMS_COMPLETE_EVT           5
#define    BTM_BLE_5_GAP_EXT_ADV_DATA_SET_COMPLETE_EVT             6
#define    BTM_BLE_5_GAP_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT        7
#define    BTM_BLE_5_GAP_EXT_ADV_START_COMPLETE_EVT                8
#define    BTM_BLE_5_GAP_EXT_ADV_STOP_COMPLETE_EVT                 9
#define    BTM_BLE_5_GAP_EXT_ADV_SET_REMOVE_COMPLETE_EVT           10
#define    BTM_BLE_5_GAP_EXT_ADV_SET_CLEAR_COMPLETE_EVT            11
#define    BTM_BLE_5_GAP_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT      12
#define    BTM_BLE_5_GAP_PERIODIC_ADV_DATA_SET_COMPLETE_EVT        13
#define    BTM_BLE_5_GAP_PERIODIC_ADV_START_COMPLETE_EVT           14
#define    BTM_BLE_5_GAP_PERIODIC_ADV_STOP_COMPLETE_EVT            15
#define    BTM_BLE_5_GAP_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT     16
#define    BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_CANCEL_COMPLETE_EVT     17
#define    BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_TERMINATE_COMPLETE_EVT  18
#define    BTM_BLE_5_GAP_PERIODIC_ADV_ADD_DEV_COMPLETE_EVT         19
#define    BTM_BLE_5_GAP_PERIODIC_ADV_REMOVE_DEV_COMPLETE_EVT      20
#define    BTM_BLE_5_GAP_PERIODIC_ADV_CLEAR_DEV_COMPLETE_EVT       21
#define    BTM_BLE_5_GAP_SET_EXT_SCAN_PARAMS_COMPLETE_EVT          22
#define    BTM_BLE_5_GAP_EXT_SCAN_START_COMPLETE_EVT               23
#define    BTM_BLE_5_GAP_EXT_SCAN_STOP_COMPLETE_EVT                24
#define    BTM_BLE_5_GAP_PREFER_EXT_CONN_PARAMS_SET_COMPLETE_EVT   25
#define    BTM_BLE_5_GAP_PHY_UPDATE_COMPLETE_EVT                   26
#define    BTM_BLE_5_GAP_EXT_ADV_REPORT_EVT                        27
#define    BTM_BLE_5_GAP_SCAN_TIMEOUT_EVT                          28
#define    BTM_BLE_5_GAP_ADV_TERMINATED_EVT                        29
#define    BTM_BLE_5_GAP_SCAN_REQ_RECEIVED_EVT                     30
#define    BTM_BLE_5_GAP_CHANNEL_SELETE_ALGORITHM_EVT              31
#define    BTM_BLE_5_GAP_PERIODIC_ADV_REPORT_EVT                   32
#define    BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_LOST_EVT                33
#define    BTM_BLE_5_GAP_PERIODIC_ADV_SYNC_ESTAB_EVT               34
#define    BTM_BLE_5_GAP_UNKNOWN_EVT                               35
typedef UINT8 tBTM_BLE_5_GAP_EVENT;

#define BTM_BLE_EXT_ADV_DATA_COMPLETE          0x00
#define BTM_BLE_EXT_ADV_DATA_INCOMPLETE        0x01
#define BTM_BLE_EXT_ADV_DATA_TRUNCATED         0x02
typedef UINT8 tBTM_BLE_EXT_ADV_DATA_STATUS;

#define BTM_BLE_ADV_DATA_COMPLETE_MASK         (0x0000)
#define BTM_BLE_ADV_DATA_INCOMPLETE_MASK       (0x0020)
#define BTM_BLE_ADV_DATA_TRUNCATED_MASK        (0x0040)
#define BTM_BLE_ADV_DATA_STATUS_MASK           (0x0060)


//#定义BTM_BLE_ADV_CONN_MASK（0x0001）
//#定义BTM_BLE_ADV_SCAN_MASK（0x0002）
//#定义BTM_BLE_ADV_DIRECT_MASK（0x0004）
//#定义BTM_BLE_SCAN_RSP_MASK（0x0008）
#define BTM_BLE_ADV_LEGACY_MASK                (0x0010)
typedef UINT8 tBTM_BLE_ADV_MASK;

// /* 广告报道*/
// #定义BTM_BLE_ADV_REPORT_ADV_IND（0）
// #定义BTM_BLE_ADV_REPORT_DIR_IND（1）
// #定义BTM_BLE_ADV_REPORT_SCAN_IND（2）
// #定义BTM_BLE_ADV_REPORT_NONCONN_IND（3）
// #定义BTM_BLE_ADV_REPORT_SCAN_RSP（4）

// /* 蓝牙5.0，第2卷，E部分，7.7.65.13*/
// #定义BTM_BLE_LEGACY_ADV_TYPE_IND（0x13）
// #定义BTM_BLE_LEGACY_ADV_TYPE_DIRECT_IND（0x15）
// #定义BTM_BLE_LEGACY_ADV_TYPE_SCAN_IND（0x12）
// #定义BTM_BLE_LEGACY_ADV_TYPE_NONCON_IND（0x10）
// #定义BTM_BLE_LEGACY_ADV_TYPE_SCAN_RSP_ADV_IND（0x1b）
// #定义BTM_BLE_LEGACY_ADV_TYPE_SCAN_SP_ADV_SCAN_IND（0x1a）

typedef struct {
    UINT8 status;
    BD_ADDR addr;
    UINT8 tx_phy;
    UINT8 rx_phy;
} tBTM_BLE_READ_PHY_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_SET_PREF_DEF_PHY_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_SET_PERF_PHY_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_ADV_SET_RAND_ADDR_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_ADV_SET_PARAMS_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_ADV_DATA_SET_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_ADV_SCAN_RSP_DATA_SET_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_ADV_START_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_ADV_STOP_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_SET_PARAMS_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_DATA_SET_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_START_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_STOP_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_SYNC_CREATE_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_SYNC_CANCEL_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_SYNC_TEMINAT_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_ADD_DEV_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PERIOD_ADV_REMOVE_DEV_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PEROID_ADV_CLEAR_DEV_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_SET_EXT_SCAN_PARAMS_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_SCAN_START_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_EXT_SCAN_STOP_CMPL;

typedef struct {
    UINT8 status;
} tBTM_BLE_PREF_EXT_CONN_SET_PARAMS_CMPL;

typedef struct {
    uint8_t status;
    BD_ADDR addr;
    uint8_t tx_phy;
    uint8_t rx_phy;
} tBTM_BLE_PHY_UPDATE_CMPL;

typedef struct {
    // UINT8道具；
    // UINT8 legacy_event_type；
    UINT8 event_type;
    tBLE_ADDR_TYPE addr_type;
    BD_ADDR addr;
    UINT8 primary_phy;
    UINT8 secondry_phy;
    UINT8 sid;
    UINT8 tx_power;
    UINT8 rssi;
    UINT16 per_adv_interval;
    tBLE_ADDR_TYPE dir_addr_type;
    BD_ADDR dir_addr;
    tBTM_BLE_EXT_ADV_DATA_STATUS data_status;
    UINT8 adv_data_len;
    UINT8 *adv_data;
} tBTM_BLE_EXT_ADV_REPORT;

typedef struct {
    UINT8 status;
    UINT8 adv_handle;
    UINT16 conn_handle;
    UINT8 completed_event;
} tBTM_BLE_ADV_TERMINAT;

typedef struct {
    UINT8 adv_handle;
    tBLE_ADDR_TYPE scan_addr_type;
    BD_ADDR scan_addr;
} tBTM_BLE_SCAN_REQ_RECEIVED;

typedef struct {
    UINT16 conn_handle;
    UINT8 channel_sel_alg;
} tBTM_BLE_CHANNEL_SEL_ALG;

typedef struct {
    UINT16 sync_handle;
    UINT8 tx_power;
    INT8 rssi;
    tBTM_BLE_EXT_ADV_DATA_STATUS data_status;
    UINT8 data_length;
    UINT8 *data;
} tBTM_PERIOD_ADV_REPORT;

typedef struct {
    UINT16 sync_handle;
} tBTM_BLE_PERIOD_ADV_SYNC_LOST;

typedef struct {
    UINT8 status;
    UINT16 sync_handle;
    UINT8 sid;
    tBLE_ADDR_TYPE adv_addr_type;
    BD_ADDR adv_addr;
    UINT8 adv_phy;
    UINT16 period_adv_interval;
    UINT8 adv_clk_accuracy;
} tBTM_BLE_PERIOD_ADV_SYNC_ESTAB;

typedef struct {
    UINT16 scan_interval;
    UINT16 scan_window;
    UINT16 interval_min;
    UINT16 interval_max;
    UINT16 latency;
    UINT16 supervision_timeout;
    UINT16 min_ce_len;
    UINT16 max_ce_len;
} tBTM_BLE_CONN_PARAMS;


typedef union {
    UINT8 status;
    tBTM_BLE_READ_PHY_CMPL read_phy;
    tBTM_BLE_SET_PREF_DEF_PHY_CMPL set_perf_def_phy;
    tBTM_BLE_SET_PERF_PHY_CMPL set_perf_phy;
    tBTM_BLE_EXT_ADV_SET_RAND_ADDR_CMPL set_ext_rand_addr;
    tBTM_BLE_EXT_ADV_SET_PARAMS_CMPL set_params;
    tBTM_BLE_EXT_ADV_DATA_SET_CMPL adv_data_set;
    tBTM_BLE_EXT_ADV_SCAN_RSP_DATA_SET_CMPL scan_rsp_data_set;
    tBTM_BLE_EXT_ADV_START_CMPL adv_start;
    tBTM_BLE_EXT_ADV_STOP_CMPL adv_stop;
    tBTM_BLE_PERIOD_ADV_SET_PARAMS_CMPL per_adv_set_params;
    tBTM_BLE_PERIOD_ADV_DATA_SET_CMPL per_adv_data_set;
    tBTM_BLE_PERIOD_ADV_START_CMPL per_adv_start;
    tBTM_BLE_PERIOD_ADV_STOP_CMPL per_adv_stop;
    tBTM_BLE_PERIOD_ADV_SYNC_CREATE_CMPL per_adv_sync_create;
    tBTM_BLE_PERIOD_ADV_SYNC_CANCEL_CMPL per_adv_sync_cancel;
    tBTM_BLE_PERIOD_ADV_SYNC_TEMINAT_CMPL per_adv_sync_term;
    tBTM_BLE_PERIOD_ADV_ADD_DEV_CMPL per_adv_add_dev;
    tBTM_BLE_PERIOD_ADV_REMOVE_DEV_CMPL per_adv_remove_dev;
    tBTM_BLE_PEROID_ADV_CLEAR_DEV_CMPL per_adv_clear_dev;
    tBTM_BLE_SET_EXT_SCAN_PARAMS_CMPL ext_scan;
    tBTM_BLE_EXT_SCAN_START_CMPL scan_start;
    tBTM_BLE_EXT_SCAN_STOP_CMPL scan_stop;
    tBTM_BLE_PREF_EXT_CONN_SET_PARAMS_CMPL ext_conn_set_params;
    tBTM_BLE_PHY_UPDATE_CMPL phy_update;
    tBTM_BLE_EXT_ADV_REPORT ext_adv_report;
    tBTM_BLE_ADV_TERMINAT adv_term;
    tBTM_BLE_SCAN_REQ_RECEIVED scan_req;
    tBTM_BLE_CHANNEL_SEL_ALG channel_sel;
    tBTM_PERIOD_ADV_REPORT period_adv_report;
    tBTM_BLE_PERIOD_ADV_SYNC_LOST sync_lost;
    tBTM_BLE_PERIOD_ADV_SYNC_ESTAB sync_estab;
} tBTM_BLE_5_GAP_CB_PARAMS;

typedef struct {
    UINT8                           phy_mask;
    tBTM_BLE_CONN_PARAMS            phy_1m_conn_params;
    tBTM_BLE_CONN_PARAMS            phy_2m_conn_params;
    tBTM_BLE_CONN_PARAMS            phy_coded_conn_params;
} tBTM_EXT_CONN_PARAMS;

typedef void (*tBTM_BLE_5_HCI_CBACK)(tBTM_BLE_5_GAP_EVENT event, tBTM_BLE_5_GAP_CB_PARAMS *params);

#endif //#如果（BLE_50_FFEATURE_SUPPORT==真）

/*****************************************************************************
**  EXTERNAL FUNCTION DECLARATIONS
*****************************************************************************/
/*
#ifdef__cplusplusextern“C”｛#endif
*/

/*******************************************************************************
** 函数BTM_BleRegseterConnParamCallback
**
** 描述寄存器连接参数更新回调函数
**
** 参数：update_conn_param_cb
**
** 返回void
**
*******************************************************************************/
void BTM_BleRegiseterConnParamCallback(tBTM_UPDATE_CONN_PARAM_CBACK *update_conn_param_cb);

/*******************************************************************************
** 函数BTM_SecAddBleDevice
**
** 说明添加/修改设备。该功能通常在主机启动期间调用，以恢复存储在NVRAM中的LE设备的所有所需信息。
**
** 参数：bd_addr-对等设备的bd地址bd_name-对等设备名称。如果未知，则为NULL。dev_type-远程设备的设备类型。addr_type—LE设备地址类型。auth_mode-身份验证模式
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecAddBleDevice (BD_ADDR bd_addr, BD_NAME bd_name,
                             tBT_DEVICE_TYPE dev_type, tBLE_ADDR_TYPE addr_type, UINT32 auth_mode);

/*******************************************************************************
** 函数BTM_SecAddBleKey
**
** 说明添加/修改LE设备信息。该功能通常在主机启动期间调用，以恢复存储在NVRAM中的所有所需信息。
**
** 参数：bd_addr-对等体p_le_key的bd地址-le键值。key_type—LE SMP密钥类型。
*
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecAddBleKey (BD_ADDR bd_addr, tBTM_LE_KEY_VALUE *p_le_key,
                          tBTM_LE_KEY_TYPE key_type);

/*******************************************************************************
** 函数BTM_BleSetAdvParams
**
** 说明此函数用于设置广告参数。
**
** 参数：无。
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleSetAdvParams(UINT16 adv_int_min, UINT16 adv_int_max,
                                tBLE_BD_ADDR *p_dir_bda, tBTM_BLE_ADV_CHNL_MAP chnl_map);



/*******************************************************************************
** 函数BTM_BleSetAdvParamsAll
**
** 说明此函数用于设置所有广告参数。
**
** 参数：无。
**
** 返回void
**
*******************************************************************************/
tBTM_STATUS BTM_BleSetAdvParamsAll(UINT16 adv_int_min, UINT16 adv_int_max, UINT8 adv_type,
                                        tBLE_ADDR_TYPE own_bda_type, tBLE_BD_ADDR *p_dir_bda,
                                        tBTM_BLE_ADV_CHNL_MAP chnl_map, tBTM_BLE_AFP afp, tBTM_START_ADV_CMPL_CBACK *adv_cb);

/*******************************************************************************
** 函数BTM_BleStartAdv
**
** 说明调用此函数以启动adv。
**
** 参数：无。
**
** 退货状态
**
*******************************************************************************/
tBTM_STATUS BTM_BleStartAdv(void);


/*******************************************************************************
** 函数BTM_BleWriteAdvData
**
** 说明此函数用于写入广告数据。
**
** 参数：无。
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleWriteAdvData(tBTM_BLE_AD_MASK  data_mask,
                                tBTM_BLE_ADV_DATA *p_data);

/*******************************************************************************
** 函数BTM_BleWriteLongAdvData
**
** 说明此函数用于写入长广告数据。
**
** 参数：adv_data:长广告数据adv_data_len：长广告数据的长度
**
** 返回void
**
*******************************************************************************/
tBTM_STATUS BTM_BleWriteLongAdvData(uint8_t *adv_data, uint8_t adv_data_len);

/*******************************************************************************
** 函数BTM_BleWriteAdvDataRaw
**
** 说明此函数用于写入原始广告数据。
**
** 参数：p_raw_adv:指向原始广告数据raw_adv_len：原始广告数据
**
** 返回BTM_SUCCESS表示成功。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleWriteAdvDataRaw(UINT8 *p_raw_adv, UINT32 raw_adv_len);


tBTM_STATUS BTM_BleSetRandAddress(BD_ADDR rand_addr);

void BTM_BleClearRandAddress(void);


/*******************************************************************************
** 函数BTM_BleSetAdvParams
**
** 说明此函数用于设置广告参数。
**
** 参数adv_int_min：最小广告间隔adv_int_max：最大广告间隔p_dir_bda：可连接的直接启动器的LE设备地址chnl_map：广告频道映射。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleReadAdvParams (UINT16 *adv_int_min, UINT16 *adv_int_max,
                           tBLE_BD_ADDR *p_dir_bda, tBTM_BLE_ADV_CHNL_MAP *p_chnl_map);

/*******************************************************************************
** 函数BTM_BleObtainVendorCapabilities
**
** 说明调用此函数以获取供应商能力
**
** 参数p_cmn_vsc_cb-返回供应商功能
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleObtainVendorCapabilities(tBTM_BLE_VSC_CB *p_cmn_vsc_cb);

/*******************************************************************************
** 函数BTM_BleScanParams
**
** 说明调用此函数以设置扫描参数。
**
** 参数client_if-客户端if值scan_interval-扫描间隔scan_window-扫描窗口scan_type-扫描类型scan_setup_status_cback-扫描设置状态回调
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleSetScanParams(tGATT_IF client_if, UINT32 scan_interval,
                          UINT32 scan_window, tBLE_SCAN_MODE scan_type,
                          tBLE_SCAN_PARAM_SETUP_CBACK scan_setup_status_cback);



/*******************************************************************************
** 函数BTM_BleScanFilterParams
**
** 说明调用此函数以设置扫描筛选器参数（&P）。
**
** 参数client_if-客户端if值scan_interval-扫描间隔scan_window-扫描窗口scan_type-扫描类型addr_type_own-所有者地址类型scan_duplicate_filter-扫描重复筛选器scan_filter_policy-扫描筛选器策略scan_setup_status_cback-扫描设置状态回调
**
** 返回void
**
*******************************************************************************/
tBTM_STATUS BTM_BleSetScanFilterParams(tGATT_IF client_if, UINT32 scan_interval, UINT32 scan_window,
                                    tBLE_SCAN_MODE scan_mode, UINT8 addr_type_own, UINT8 scan_duplicate_filter, tBTM_BLE_SFP scan_filter_policy,
                                    tBLE_SCAN_PARAM_SETUP_CBACK scan_setup_status_cback);


/*******************************************************************************
** 函数BTM_BleGetVendorCapabilities
**
** 说明此功能读取本地LE功能
**
** 参数p_cmn_vsc_cb:Locala LE能力结构
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleGetVendorCapabilities(tBTM_BLE_VSC_CB *p_cmn_vsc_cb);
/*******************************************************************************
** 函数BTM_BleStorageConfig
**
** 说明此函数用于设置存储配置和设置回调。
**
** 参数UINT8 batch_scan_full_max-批量扫描最大值UINT8 batch_scan_trunc_max-批量扫描截断值最大值UINT 8 batch_scan_notify_threshold-阈值tBTM_BLE_scan_SETUP_CBACK p_SETUP_CBACK-设置回调tBTM_ABL_scan_threshold_CACK p_thres_CBACK-阈值回调无效p_ref-参考值
**
** 返回tBTM_STATUS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleSetStorageConfig(UINT8 batch_scan_full_max,
                                    UINT8 batch_scan_trunc_max,
                                    UINT8 batch_scan_notify_threshold,
                                    tBTM_BLE_SCAN_SETUP_CBACK *p_setup_cback,
                                    tBTM_BLE_SCAN_THRESHOLD_CBACK *p_thres_cback,
                                    tBTM_BLE_SCAN_REP_CBACK *p_cback,
                                    tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleEnableBatchScan
**
** 说明调用此函数以启用批扫描
**
** 参数tBTM_BLE_BATCH_SCAN_MODE SCAN_MODE-批扫描模式UINT32 SCAN_interval-扫描间隔UINT32扫描窗口-扫描窗口值tBLE_ADDR_TYPE ADDR_TYPE-地址类型tBTM_BLE_DISCARD_RULE DISCARD_RULE-数据丢弃规则
**
** 返回tBTM_STATUS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleEnableBatchScan(tBTM_BLE_BATCH_SCAN_MODE scan_mode,
                                   UINT32 scan_interval, UINT32 scan_window,
                                   tBTM_BLE_DISCARD_RULE discard_rule,
                                   tBLE_ADDR_TYPE addr_type,
                                   tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleDisableBatchScan
**
** 说明调用此函数以禁用批扫描
**
** 参数void
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleDisableBatchScan(tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleReadScanReports
**
** 说明调用此函数以读取批扫描报告
**
** 参数tBLE_SCAN_MODE SCAN_MODE-要读取的扫描模式报告tBTM_BLE_SCAN_REP_CBACK p_CBACK-报告回调
**
** 返回tBTM_STATUS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleReadScanReports(tBLE_SCAN_MODE scan_mode,
                                   tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleTrackAdvertiser
**
** 说明调用此函数以读取批扫描报告
**
** 参数p_track_cback-跟踪回调ref_value-参考值
**
** 返回tBTM_STATUS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleTrackAdvertiser(tBTM_BLE_TRACK_ADV_CBACK *p_track_cback,
                                   tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleWriteScanRsp
**
** 说明调用此函数以写入LE扫描响应。
**
** 参数：p_scan_rsp：扫描响应。
**
** 退货状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleWriteScanRsp(tBTM_BLE_AD_MASK data_mask,
                                tBTM_BLE_ADV_DATA *p_data);

/*******************************************************************************
** 函数BTM_BleWriteScanRspRaw
**
** 描述调用此函数以写入原始扫描响应数据
**
** 参数：无。
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleWriteScanRspRaw(UINT8 *p_raw_scan_rsp, UINT32 raw_scan_rsp_len);

/*******************************************************************************
** 函数BTM_BleObserve
**
** 说明此过程使设备监听来自广播设备的广告事件。
**
** 参数启动：启动或停止观察。
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleObserve(BOOLEAN start, UINT32 duration,
                           tBTM_INQ_RESULTS_CB *p_results_cb, tBTM_CMPL_CB *p_cmpl_cb);

/*******************************************************************************
** 函数BTM_BleScan
**
** 说明此过程使设备监听来自广播设备的广告事件。
**
** 参数开始：开始或停止扫描。
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleScan(BOOLEAN start, UINT32 duration,
                           tBTM_INQ_RESULTS_CB *p_results_cb, tBTM_CMPL_CB *p_cmpl_cb, tBTM_INQ_DIS_CB *p_discard_cb);


/*******************************************************************************
** 函数BTM_GetDeviceIDRoot
**
** 描述调用此函数以读取本地设备标识根。
**
** 将本地设备ER复制到ER时返回void
**
*******************************************************************************/
//外部
void BTM_GetDeviceIDRoot (BT_OCTET16 ir);

/*******************************************************************************
** 函数BTM_GetDeviceEncRoot
**
** 说明调用此函数以读取本地设备加密根。
**
** 将本地设备ER复制到ER时返回void
**
*******************************************************************************/
//外部
void BTM_GetDeviceEncRoot (BT_OCTET16 er);

/*******************************************************************************
** 函数BTM_GetDeviceDHK
**
** 说明调用此函数以读取本地设备DHK。
**
** 将本地设备DHK复制到DHK时返回void
**
*******************************************************************************/
//外部
void BTM_GetDeviceDHK (BT_OCTET16 dhk);

/*******************************************************************************
** 函数BTM_SecurityGrant
**
** 说明调用此函数以授予安全进程。
**
** 参数bd_addr-对等设备bd地址。res-如果成功，则操作BTM_SUCCESS的结果。否则，BTM_REPEATED_ATTEMPTS尝试次数过多。
**
** 返回None
**
*******************************************************************************/
//外部
void BTM_SecurityGrant(BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
** 函数BTM_BlePasskeyReply
**
** 说明此函数在Security Manager向应用程序提交密钥请求后调用。
**
** 参数：bd_addr-请求密钥的设备的地址res-如果成功，则为SMP_SUCCESS操作的结果passkey-BTM_MIN_passkey_VAL（0）-BTM_MAX_passkey-VAL（999999（0xF423F））范围内的数值。
**
*******************************************************************************/
//外部
void BTM_BlePasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey);

/*******************************************************************************
** 函数BTM_BleStaticPasskey
**
** 说明调用此函数以设置静态密钥
**
** 参数：add-add为TRUE时设置静态密钥add为FALSE时清除静态密钥passkey-静态密钥
**
**
*******************************************************************************/
void BTM_BleSetStaticPasskey(BOOLEAN add, UINT32 passkey);

/*******************************************************************************
** 函数BTM_BleConfirmReply
**
** 说明此函数在Security Manager向应用程序提交数字比较请求后调用。
**
** 参数：bd_addr-请求数字比较的设备的地址res-比较结果BTM_SUCCESS如果成功
**
*******************************************************************************/
//外部
void BTM_BleConfirmReply (BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
** 函数BTM_LeOobDataReply
**
** 说明调用此函数以响应BTM_LE_OOB_REQ_EVT为SMP提供OOB数据
**
** 参数：bd_addr-对等设备的地址res-操作结果SMP_SUCCESS if SUCCESS p_data-简单配对随机化器C。
**
*******************************************************************************/
//外部
void BTM_BleOobDataReply(BD_ADDR bd_addr, UINT8 res, UINT8 len, UINT8 *p_data);


/*******************************************************************************
** 函数BTM_BleDSignature
**
** 说明调用此函数以使用AES128 CMAC算法对数据进行签名。
**
** 参数bd_addr：要签名的数据的目标设备。p_text：歌唱数据len：签名数据签名的长度：将存储数据签名的输出参数。
**
** 如果签名成功，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleDataSignature (BD_ADDR bd_addr, UINT8 *p_text, UINT16 len,
                              BLE_SIGNATURE signature);

/*******************************************************************************
** 函数BTM_BleVerifySignature
**
** 说明调用此函数以验证数据签名
**
** 参数bd_addr：要签名的数据的目标设备。p_orig：签名前的原始数据。len：签名数据计数器的长度：执行数据签名时使用的计数器p_comp：要比较的签名。

** 如果签名验证正确，则返回TRUE；否则为FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleVerifySignature (BD_ADDR bd_addr, UINT8 *p_orig,
                                UINT16 len, UINT32 counter,
                                UINT8 *p_comp);

/*******************************************************************************
** 函数BTM_ReadConnectionAddr
**
** 说明此函数用于设置本地设备随机地址。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_ReadConnectionAddr (BD_ADDR remote_bda, BD_ADDR local_conn_addr,
                             tBLE_ADDR_TYPE *p_addr_type);



/*******************************************************************************
** 函数BTM_ReadRemoteConnectionAddr
**
** 说明此功能读取当前使用的远程设备地址。
**
** 返回void
**
*******************************************************************************/
//外部
BOOLEAN BTM_ReadRemoteConnectionAddr(BD_ADDR pseudo_addr,
                                     BD_ADDR conn_addr,
                                     tBLE_ADDR_TYPE *p_addr_type);

/*******************************************************************************
** 函数BTM_BleLoadLocalKeys
**
** 说明本地身份密钥、加密根或签名计数器。
**
** 参数：key_type：密钥类型，可以是BTM_BLE_key_type_ID、BTM_BLE_6EY_type_ER或BTM_BLE_TKEY_type_COUNTER。p_key：指向键的指针。
*
** 返回non2。
**
*******************************************************************************/
//外部
void BTM_BleLoadLocalKeys(UINT8 key_type, tBTM_BLE_LOCAL_KEYS *p_key);


/*******************************************************************************
** 函数BTM_BleSetBgConnType
**
** 说明调用此函数以设置BLE后台连接过程类型。它可以是自动连接，也可以是选择性连接。
**
** 参数conn_type：可以是自动连接，也可以是选择性连接。p_select_cback：使用选择性连接过程时的回调函数。
**
** 返回void
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleSetBgConnType(tBTM_BLE_CONN_TYPE   conn_type,
                             tBTM_BLE_SEL_CBACK   *p_select_cback);

/*******************************************************************************
** 函数BTM_BleUpdateBgConnDev
**
** 说明调用此函数可将设备添加到后台连接过程或从后台连接过程中删除设备。后台连接过程由后台连接类型决定，可以是自动连接，也可以是选择性连接。
**
** 参数add_remove：TRUE添加；FALSE删除。remote_bda：要添加/删除的设备地址。
**
** 返回void
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleUpdateBgConnDev(BOOLEAN add_remove, BD_ADDR   remote_bda);

/*******************************************************************************
** 函数BTM_BleClearBgConnDev
**
** 描述调用此函数以清除白名单，结束任何挂起的白名单连接，并重置本地bg设备列表。
**
** 参数void
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleClearBgConnDev(void);

/********************************************************
** 函数BTM_BleSetPrefConnParams
**
** 说明设置外围设备的首选连接参数。如果其中任何一个值不想更新，而其他值不想进行更新，请使用BTM_BLE_CONN_PARAM_UNDEF替换那些不想更新的值。
**
** 参数：bd_addr-外围设备的bd地址min_conn_int-最小首选连接间隔max_conn_int–最大首选连接间隔slave_elatency-首选从属延迟supervisory_tout-首选监视超时
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleSetPrefConnParams (BD_ADDR bd_addr,
                               UINT16 min_conn_int,  UINT16 max_conn_int,
                               UINT16 slave_latency, UINT16 supervision_tout);

/******************************************************************************
** 函数BTM_BleSetConnScanParams
**
** 说明设置BLE连接请求中使用的扫描参数
**
** 参数：scan_interval-扫描间隔scan_window-扫描窗口
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleSetConnScanParams (UINT32 scan_interval, UINT32 scan_window);

/******************************************************************************
** 函数BTM_BleReadControllerFeatures
**
** 说明读取BLE特定控制器功能
**
** 参数：tBTM_BLE_CTRL_FEATURES_CACK：读取特征时通知的回调
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleReadControllerFeatures(tBTM_BLE_CTRL_FEATURES_CBACK  *p_vsc_cback);

/*******************************************************************************
** 函数BTM_CheckAdvData
**
** 说明调用此函数以获取特定类型的ADV数据。
**
** 参数p_adv-adv数据类型的指针-查找adv数据的类型p_length-返回不包括类型的adv数据长度
**
** 返回ADV数据的指针
**
*******************************************************************************/
//外部
UINT8 *BTM_CheckAdvData( UINT8 *p_adv, UINT8 type, UINT8 *p_length);

/*******************************************************************************
** 函数BTM_BleGetCurrentAddress
**
** 描述调用此函数以获取本地使用的BLE地址。
**
** 参数：无。
**
** 返回成功或失败
**
*******************************************************************************/
BOOLEAN BTM_BleGetCurrentAddress(BD_ADDR addr, uint8_t *addr_type);

/*******************************************************************************
** 函数BTM__BLEreadDiscoveryability
**
** 说明调用此函数以读取设备的当前LE可发现性模式。
**
** 返回BTM_BLE_NON_DISCOVERABLE、BTM_BLE_LIMITED_DISCOVERABLE或BTM_BLE_GENRAL_DISCOVERABLE
**
*******************************************************************************/
UINT16 BTM_BleReadDiscoverability(void);

/*******************************************************************************
** 函数BTM__BLEReadConnectability
**
** 说明调用此函数以读取设备的当前LE可连接模式。
**
** 返回BTM_BLE_NON_CONNECTABLE或BTM_BLE_CONNECTBLE
**
*******************************************************************************/
//外部
UINT16 BTM_BleReadConnectability (void);

void BTM_Recovery_Pre_State(void);

/*******************************************************************************
** 函数BTM_ReadDevInfo
**
** 说明调用此函数读取BD地址的设备/地址类型。
**
** 参数remote_bda：远程设备地址p_dev_type：用于读取设备类型的输出参数。p_addr_type：用于读取地址类型的输出参数。
**
*******************************************************************************/
//外部
void BTM_ReadDevInfo (BD_ADDR remote_bda, tBT_DEVICE_TYPE *p_dev_type,
                      tBLE_ADDR_TYPE *p_addr_type);


/*******************************************************************************
** 函数BTM_ReadConnectedTransportAddress
**
** 说明调用此函数以读取与BD_address对应的其他配对设备的配对设备/地址类型
**
** 参数remote_bda：远程设备地址，执行传输地址传输：活动传输
**
** 如果识别到活动链接，则返回TRUE；否则为FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_ReadConnectedTransportAddress(BD_ADDR remote_bda,
        tBT_TRANSPORT transport);

/*******************************************************************************
** 功能BTM_BleBroadcast
**
** 说明此功能用于启动或停止广播。
**
** 参数开始：开始或停止广播。
**
** 返回状态。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleBroadcast(BOOLEAN start, tBTM_START_STOP_ADV_CMPL_CBACK *p_stop_adv_cback);

/*******************************************************************************
** 函数BTM_BleConfigPrivacy
**
** 描述调用此函数以启用或禁用本地设备中的隐私。
**
** 参数启用：TRUE启用；FALSE禁用它。
**
** 返回BOOLEAN隐私模式设置成功；否则失败。
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleConfigPrivacy(BOOLEAN enable, tBTM_SET_LOCAL_PRIVACY_CBACK *set_local_privacy_cabck);

/*******************************************************************************
** 函数BTM_BleConfigLocalIcon
**
** 说明调用此函数设置本地图标
**
** 参数图标：外观值。
**
**
*******************************************************************************/
void BTM_BleConfigLocalIcon(uint16_t icon);

/*******************************************************************************
** 函数BTM_BleConfigConnParams
**
** 说明调用此函数以设置连接参数
**
** 参数int_min：最小连接间隔int_max：最大连接间隔延迟：从属延迟超时：监视超时
**
*******************************************************************************/
void BTM_BleConfigConnParams(uint16_t int_min, uint16_t int_max, uint16_t latency, uint16_t timeout);

/*******************************************************************************
** 函数BTM_BleLocalPrivacyEnabled
**
** 说明检查本地设备是否支持专用地址
**
** 如果启用了本地隐私，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleLocalPrivacyEnabled(void);

/*******************************************************************************
** 函数BTM_BleEnableMixedPrivacyMode
**
** 说明如果隐私1.2适用于控制器，则调用此函数以启用混合模式。
**
** 参数mixed_on：是否使用混合模式。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleEnableMixedPrivacyMode(BOOLEAN mixed_on);

/*******************************************************************************
** 函数BTM_BleMaxMultiAdvInstanceCount
**
** 说明返回控制器支持的多adv实例的最大数量
**
** 返回最大多adv实例计数
**
*******************************************************************************/
//外部
UINT8  BTM_BleMaxMultiAdvInstanceCount(void);

/*******************************************************************************
** 函数BTM_BleSetConnectableMode
**
** 说明调用此函数可设置外围设备的BLE可连接模式。
**
** 参数connectable_mode：定向可连接模式或非定向。它可以是BTM_BLE_CONNECT_EVT、BTM_BLE_CONNECT_DIR_EVT或BTM_BLE_CONNECT_LO_DUTY_DIR_EVT
**
** 如果控制器不支持BLE，则返回BTM_ILLEGAL_VALUE。BTM_SUCCESS状态设置成功；否则失败。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleSetConnectableMode(tBTM_BLE_CONN_MODE connectable_mode);

/*******************************************************************************
** 功能BTM_BleTurnOnPrivacyOnRemote
**
** 说明调用此函数以启用或禁用远程设备上的隐私。
**
** 参数bd_addr：远程设备地址。privacy_on：TRUE启用；FALSE禁用它。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_BleTurnOnPrivacyOnRemote(BD_ADDR bd_addr,
                                  BOOLEAN privacy_on);

/*******************************************************************************
** 函数BTM_BleUpdateAdvWhitelist
**
** 说明从广告白名单中添加或删除设备
**
** 返回void
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleUpdateAdvWhitelist(BOOLEAN add_remove, BD_ADDR emote_bda, tBLE_ADDR_TYPE addr_type, tBTM_ADD_WHITELIST_CBACK *add_wl_cb);

/*******************************************************************************
** 函数BTM_BleClearWhitelist
**
** 说明清除所有白色列表
**
** 返回void
**
*******************************************************************************/
void BTM_BleClearWhitelist(void);

/*******************************************************************************
** 函数BTM_BleUpdateAdvFilterPolicy
**
** 说明此功能更新广告客户的筛选策略。
**
** 参数adv_policy:广告筛选器策略
**
** 返回void
*******************************************************************************/
//外部
void BTM_BleUpdateAdvFilterPolicy(tBTM_BLE_AFP adv_policy);

/*******************************************************************************
** 函数BTM_BleReceiverTest
**
** 说明调用此函数以启动LE接收器测试
**
** 参数rx_freq-频率范围p_cmd_cmpl_cback-命令完成回调
**
*******************************************************************************/
void BTM_BleReceiverTest(UINT8 rx_freq, tBTM_CMPL_CB *p_cmd_cmpl_cback);


/*******************************************************************************
** 函数BTM_BleTransmitterTest
**
** 说明调用此函数以启动LE发射器测试
**
** 参数tx_freq-频率范围test_data_len-每个数据包中有效负载数据的字节长度packet_payload-有效负载中使用的模式p_cmd_cmpl_cback-命令完成回调
**
*******************************************************************************/
void BTM_BleTransmitterTest(UINT8 tx_freq, UINT8 test_data_len,
                            UINT8 packet_payload, tBTM_CMPL_CB *p_cmd_cmpl_cback);

/*******************************************************************************
** 函数BTM_BleTestEnd
**
** 说明调用此函数以停止正在进行的TX或RX测试
**
** 参数p_cmd_cmpl_cback-命令完成回调
**
*******************************************************************************/
void BTM_BleTestEnd(tBTM_CMPL_CB *p_cmd_cmpl_cback);

/*******************************************************************************
** 函数BTM_UseLeLink
**
** 说明此功能用于选择要使用的底层物理链接。
**
** 返回TRUE使用LE，返回FALSE使用BR/EDR。
**
*******************************************************************************/
//外部
BOOLEAN BTM_UseLeLink (BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_BleStackEnable
**
** 说明启用/禁用无堆栈控制器功能上的BLE功能。
**
** 参数：enable：TRUE表示启用，FALSE表示禁用。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleStackEnable (BOOLEAN enable);

/*******************************************************************************
** 函数BTM_GetLeSecurityState
**
** 描述调用此函数以获取LE对等体的安全模式1标志和加密密钥大小。
**
** 如果找到LE设备，则返回BOOLEAN TRUE，否则返回FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_GetLeSecurityState (BD_ADDR bd_addr,
                                UINT8 *p_le_dev_sec_flags,
                                UINT8 *p_le_key_size);

/*******************************************************************************
** 函数BTM_BleSecurityProcedureIsRunning
**
** 说明此函数指示LE安全过程当前是否与对等方一起运行。
**
** 如果安全过程正在运行，则返回BOOLEAN TRUE，否则返回FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_BleSecurityProcedureIsRunning (BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_BleGetSupportedKeySize
**
** 说明此函数获取本地设备可以支持的最大加密密钥大小（以字节为单位）。记录
**
** 如果无法检索密钥大小，则返回密钥大小或0。
**
*******************************************************************************/
//外部
UINT8 BTM_BleGetSupportedKeySize (BD_ADDR bd_addr);

/*******************************************************************************/
/*                          多ADV API*/
/*******************************************************************************
** 函数BTM_BleEnableAdvInstance
**
** 说明此函数使用指定的ADV参数启用Multi-ADV实例
**
** 参数p_params：指向adv参数结构的指针，在实例启用时设置为默认adv参数。p_cback：adv实例的回调函数。p_ref：附加到要启用的adv实例的引用数据。
**
** 退货状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleEnableAdvInstance (tBTM_BLE_ADV_PARAMS *p_params,
                                      tBTM_BLE_MULTI_ADV_CBACK *p_cback,
                                      void *p_ref);

/*******************************************************************************
** 函数BTM_BleUpdateAdvInstParam
**
** 说明此函数使用指定的ADV参数更新Multi-ADV实例。
**
** 参数inst_id：adv实例id p_params：指向adv参数结构的指针。
**
** 退货状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleUpdateAdvInstParam (UINT8 inst_id, tBTM_BLE_ADV_PARAMS *p_params);

/*******************************************************************************
** 函数BTM_BleCfgAdvInstData
**
** 说明此功能使用指定的ADV数据或扫描响应数据配置Multi-ADV实例。
**
** 参数inst_id:adv实例id is_scan_rsp：如果没有设置为adv数据，则是此scacn响应。data_mask：adv数据掩码。p_data：指向adv数据结构的指针。
**
** 退货状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleCfgAdvInstData (UINT8 inst_id, BOOLEAN is_scan_rsp,
                                   tBTM_BLE_AD_MASK data_mask,
                                   tBTM_BLE_ADV_DATA *p_data);

/*******************************************************************************
** 函数BTM_BleDisableAdvInstance
**
** 说明此功能禁用Multi-ADV实例。
**
** 参数inst_id:adv实例id
**
** 退货状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleDisableAdvInstance (UINT8 inst_id);

/*******************************************************************************
** 函数BTM_BleAdvFilterParamSetup
**
** 说明调用此函数以设置adv数据有效负载筛选器条件。
**
** 参数p_target：启用目标设备上的过滤条件；如果为NULL，则启用通用扫描条件。启用：启用或禁用筛选条件
**
** 返回void
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleAdvFilterParamSetup(int action,
                                       tBTM_BLE_PF_FILT_INDEX filt_index,
                                       tBTM_BLE_PF_FILT_PARAMS *p_filt_params,
                                       tBLE_BD_ADDR *p_target, tBTM_BLE_PF_PARAM_CBACK *p_cmpl_cback,
                                       tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleCfgFilterCondition
**
** 说明调用此函数以配置adv数据有效负载筛选器条件。
**
** 参数操作：读取/写入/清除cond_type：筛选器条件类型。p_cond：过滤条件参数
**
** 返回tBTM_STATUS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleCfgFilterCondition(tBTM_BLE_SCAN_COND_OP action,
                                      tBTM_BLE_PF_COND_TYPE cond_type,
                                      tBTM_BLE_PF_FILT_INDEX filt_index,
                                      tBTM_BLE_PF_COND_PARAM *p_cond,
                                      tBTM_BLE_PF_CFG_CBACK *p_cmpl_cback,
                                      tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleEnableDisableFilterFeature
**
** 说明调用此函数以启用或禁用APCF功能
**
** 参数启用-TRUE-启用APCF，FALSE-禁用APCF ref_value-ref值
**
** 返回tBTM_STATUS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleEnableDisableFilterFeature(UINT8 enable,
        tBTM_BLE_PF_STATUS_CBACK *p_stat_cback,
        tBTM_BLE_REF_VALUE ref_value);

/*******************************************************************************
** 函数BTM_BleGetEnergyInfo
**
** 说明此功能获取能量信息
**
** 参数p_ener_cback-回调指针
**
** 退货状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_BleGetEnergyInfo(tBTM_BLE_ENERGY_INFO_CBACK *p_ener_cback);

/*******************************************************************************
** 函数BTM_SetBleDataLength
**
** 描述调用此函数以设置最大BLE传输包大小
**
** 如果成功，则返回BTM_SUCCESS；否则失败。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetBleDataLength(BD_ADDR bd_addr, UINT16 tx_pdu_length);

/*******************************************************************************
** 函数BTM_UpdatebleDuplicateExceptionList
**
** 说明调用此函数以更新重复扫描例外列表。
**
** 参数：子代码：添加、删除或清除重复扫描异常列表。类型：设备信息类型device_info：设备信息update_exceptional_list_cmp_cb：完整回调
**
** 退货状态
**
*******************************************************************************/

tBTM_STATUS BTM_UpdateBleDuplicateExceptionalList(uint8_t subcode, uint32_t type, BD_ADDR device_info, tBTM_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK update_exceptional_list_cmp_cb);

/*******************************************************************************
** 函数BTM_GetCurrentConnParams
**
** 说明调用此函数以读取设备的当前连接参数
**
** 返回TRUE或FALSE
**
*******************************************************************************/

BOOLEAN BTM_GetCurrentConnParams(BD_ADDR bda, uint16_t *interval, uint16_t *latency, uint16_t *timeout);

/*******************************************************************************
** 函数BTM_Ble_Authorization
**
** 说明此功能用于授权指定的设备
**
** 返回TRUE或FALSE
**
*******************************************************************************/
BOOLEAN BTM_Ble_Authorization(BD_ADDR bd_addr, BOOLEAN authorize);
/*
#ifdef__cplusplus｝#endif
*/
#if (BLE_50_FEATURE_SUPPORT == TRUE)
void BTM_BleGapRegisterCallback(tBTM_BLE_5_HCI_CBACK cb);

tBTM_STATUS BTM_BleReadPhy(BD_ADDR bd_addr, UINT8 *tx_phy, UINT8 *rx_phy);

tBTM_STATUS BTM_BleSetPreferDefaultPhy(UINT8 tx_phy_mask, UINT8 rx_phy_mask);

tBTM_STATUS BTM_BleSetPreferPhy(BD_ADDR bd_addr, UINT8 all_phys, UINT8 tx_phy_mask,
                                           UINT8 rx_phy_mask, UINT16 phy_options);

tBTM_STATUS BTM_BleSetExtendedAdvRandaddr(UINT8 instance, BD_ADDR rand_addr);

tBTM_STATUS BTM_BleSetExtendedAdvParams(UINT8 instance, tBTM_BLE_GAP_EXT_ADV_PARAMS *params);

tBTM_STATUS BTM_BleConfigExtendedAdvDataRaw(BOOLEAN is_scan_rsp, UINT8 instance, UINT16 len, UINT8 *data);

tBTM_STATUS BTM_BleStartExtAdv(BOOLEAN enable, UINT8 num, tBTM_BLE_EXT_ADV *ext_adv);

tBTM_STATUS BTM_BleExtAdvSetRemove(UINT8 instance);

tBTM_STATUS BTM_BleExtAdvSetClear(void);

tBTM_STATUS BTM_BlePeriodicAdvSetParams(UINT8 instance, tBTM_BLE_Periodic_Adv_Params *params);

tBTM_STATUS BTM_BlePeriodicAdvCfgDataRaw(UINT8 instance, UINT16 len, UINT8 *data);

tBTM_STATUS BTM_BlePeriodicAdvEnable(UINT8 instance, BOOLEAN enable);

tBTM_STATUS BTM_BlePeriodicAdvCreateSync(tBTM_BLE_Periodic_Sync_Params *params);

tBTM_STATUS BTM_BlePeriodicAdvSyncCancel(void);

tBTM_STATUS BTM_BlePeriodicAdvSyncTerm(UINT16 sync_handle);

tBTM_STATUS BTM_BlePeriodicAdvAddDevToList(tBLE_ADDR_TYPE addr_type, BD_ADDR addr, UINT16 sid);

tBTM_STATUS BTM_BlePeriodicAdvRemoveDevFromList(tBLE_ADDR_TYPE addr_type, BD_ADDR addr, UINT16 sid);

tBTM_STATUS BTM_BlePeriodicAdvClearDev(void);

tBTM_STATUS BTM_BleSetExtendedScanParams(tBTM_BLE_EXT_SCAN_PARAMS *params);

tBTM_STATUS BTM_BleExtendedScan(BOOLEAN enable, UINT16 duration, UINT16 period);

void BTM_BleSetPreferExtenedConnParams(BD_ADDR bd_addr, tBTM_EXT_CONN_PARAMS *params);

#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）

#endif

