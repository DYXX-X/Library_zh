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
#ifndef BTM_API_H
#define BTM_API_H

#include "common/bt_defs.h"
#include "common/bt_target.h"
#include "stack/hcidefs.h"

#if SDP_INCLUDED == TRUE
#include "stack/sdp_api.h"
#endif

#if SMP_INCLUDED == TRUE
#include "stack/smp_api.h"
#endif
/*****************************************************************************
**  设备控制和公共
*****************************************************************************/
/*****************************
**  设备控制常数
******************************/
/* 供应商特定命令参数允许的最大字节数*/
#define BTM_MAX_VENDOR_SPECIFIC_LEN  HCI_COMMAND_SIZE

/* BTM应用程序返回状态代码*/
enum {
    BTM_SUCCESS = 0,                    /* 0命令成功*/
    BTM_CMD_STARTED,                    /* 1命令启动正常。*/
    BTM_BUSY,                           /* 2设备正忙于其他命令*/
    BTM_NO_RESOURCES,                   /* 3没有资源发布命令*/
    BTM_MODE_UNSUPPORTED,               /* 4请求1个或多个不支持的模式*/
    BTM_ILLEGAL_VALUE,                  /* 5非法参数值*/
    BTM_WRONG_MODE,                     /* 6请求时设备处于错误模式*/
    BTM_UNKNOWN_ADDR,                   /* 7未知的远程BD地址*/
    BTM_DEVICE_TIMEOUT,                 /* 8设备超时*/
    BTM_BAD_VALUE_RET,                  /* 9收到HCI的错误值*/
    BTM_ERR_PROCESSING,                 /* 10一般错误*/
    BTM_NOT_AUTHORIZED,                 /* 11授权失败*/
    BTM_DEV_RESET,                      /* 12设备已重置*/
    BTM_CMD_STORED,                     /* 13请求存储在控制块中*/
    BTM_ILLEGAL_ACTION,                 /* 14状态机获取非法命令*/
    BTM_DELAY_CHECK,                    /* 15延迟加密检查*/
    BTM_SCO_BAD_LENGTH,                 /* 16 HCI数据长度上的错误SCO*/
    BTM_SUCCESS_NO_SECURITY,            /* 17个安全通过，未设置安全*/
    BTM_FAILED_ON_SECURITY,             /* 18安全失败*/
    BTM_REPEATED_ATTEMPTS,              /* 19次重复尝试LE安全请求*/
    BTM_MODE4_LEVEL4_NOT_SUPPORTED,     /* 20不支持仅安全连接模式*/
    BTM_PEER_LE_DATA_LEN_UNSUPPORTED,   /* 21不支持对等设置数据长度*/
    BTM_CONTROL_LE_DATA_LEN_UNSUPPORTED,/* 22控制器设置数据长度不受支持*/
    BTM_SET_PRIVACY_SUCCESS,            /* 23启用/禁用本地隐私成功*/
    BTM_SET_PRIVACY_FAIL,               /* 24启用/禁用本地隐私失败*/
    BTM_SET_STATIC_RAND_ADDR_FAIL,      /* 25命令失败*/
    BTM_INVALID_STATIC_RAND_ADDR,       /* 26无效的静态rand地址*/
    BTM_SEC_DEV_REC_REMOVED,            /* 27删除与bd_addr相关的设备记录*/
};

typedef uint8_t tBTM_STATUS;

#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
typedef enum {
    BTM_BR_ONE,                         /*0第一状态或BR/EDR扫描1*/
    BTM_BLE_ONE,                        /*1BLE扫描1*/
    BTM_BR_TWO,                         /*2 BR/EDR扫描2*/
    BTM_BLE_TWO,                        /*3 BLE扫描2*/
    BTM_FINISH,                         /*4交叉扫描或正常扫描结束*/
    BTM_NO_INTERLEAVING                 /*5无交错*/
} btm_inq_state;
#endif



/*************************
**  设备控制类型
**************************/
#define BTM_DEVICE_ROLE_BR      0x01
#define BTM_DEVICE_ROLE_DUAL    0x02
#define BTM_MAX_DEVICE_ROLE     BTM_DEVICE_ROLE_DUAL
typedef UINT8 tBTM_DEVICE_ROLE;

/* 对等设备的设备名称（可以截断以节省BTM数据库中的空间）*/
typedef UINT8 tBTM_BD_NAME[BTM_MAX_REM_BD_NAME_LEN + 1];

/* 返回带有本地版本信息的结构*/
typedef struct {
    UINT8       hci_version;
    UINT16      hci_revision;
    UINT8       lmp_version;
    UINT16      manufacturer;
    UINT16      lmp_subversion;
} tBTM_VERSION_INFO;

/* 返回带有供应商特定命令完成回调的结构*/
typedef struct {
    UINT16  opcode;
    UINT16  param_len;
    UINT8   *p_param_buf;
} tBTM_VSC_CMPL;

#define  BTM_VSC_CMPL_DATA_SIZE  (BTM_MAX_VENDOR_SPECIFIC_LEN + sizeof(tBTM_VSC_CMPL))
/**************************************************
**  设备控制和一般回调功能
***************************************************/
/* 设备状态更改时的回调函数。Appl必须轮询新状态（BTM_IsDeviceUp）。每当堆栈检测到控制器状态已更改时，就会发生该事件。通过调用BTM_RegisterForDeviceStatusNotif（）启用/禁用此异步事件。
*/
enum {
    BTM_DEV_STATUS_UP,
    BTM_DEV_STATUS_DOWN,
    BTM_DEV_STATUS_CMD_TOUT
};

typedef UINT8 tBTM_DEV_STATUS;

typedef struct {
    UINT16 rx_len;
    UINT16 tx_len;
}tBTM_LE_SET_PKT_DATA_LENGTH_PARAMS;

typedef struct {
    UINT16              min_conn_int;
    UINT16              max_conn_int;
    UINT16              conn_int;
    UINT16              slave_latency;
    UINT16              supervision_tout;
}tBTM_LE_UPDATE_CONN_PRAMS;

typedef enum{
    BTM_WHITELIST_REMOVE     = 0X00,
    BTM_WHITELIST_ADD        = 0X01,
}tBTM_WL_OPERATION;


typedef void (tBTM_DEV_STATUS_CB) (tBTM_DEV_STATUS status);


/* 发生供应商特定事件时的回调函数。包括返回的参数字节的长度和数组。通过调用BTM_RegisterForVSEvents（）启用/禁用此异步事件。
*/
typedef void (tBTM_VS_EVT_CB) (UINT8 len, UINT8 *p);


/* 用于通知应用程序同步BTM功能已完成的常规回调函数。指针包含任何返回数据的地址。
*/
typedef void (tBTM_CMPL_CB) (void *p1);

typedef void (tBTM_INQ_DIS_CB) (uint32_t num_dis);

/* 用于通知应用同步BTM功能完成的VSC回调函数。指针包含任何返回数据的地址。
*/
typedef void (tBTM_VSC_CMPL_CB) (tBTM_VSC_CMPL *p1);

/* 回调应用程序以检查连接和查询筛选器。参数是远程的BD地址和远程的开发类。如果应用程序返回无零，则连接或查询结果将被丢弃。
*/
typedef UINT8 (tBTM_FILTER_CB) (BD_ADDR bd_addr, DEV_CLASS dc);

typedef void (tBTM_UPDATE_CONN_PARAM_CBACK) (UINT8 status, BD_ADDR bd_addr, tBTM_LE_UPDATE_CONN_PRAMS *update_conn_params);

typedef void (tBTM_SET_PKT_DATA_LENGTH_CBACK) (UINT8 status, tBTM_LE_SET_PKT_DATA_LENGTH_PARAMS *data_length_params);

typedef void (tBTM_SET_RAND_ADDR_CBACK) (UINT8 status);

typedef void (tBTM_ADD_WHITELIST_CBACK) (UINT8 status, tBTM_WL_OPERATION wl_opration);

typedef void (tBTM_SET_LOCAL_PRIVACY_CBACK) (UINT8 status);


/*****************************************************************************
**  DEVICE DISCOVERY-查询、远程名称、发现、设备类别
*****************************************************************************/
/*******************************
**  设备发现常量
********************************/
/* 可发现的模式*/
#define BTM_NON_DISCOVERABLE        0
#define BTM_LIMITED_DISCOVERABLE    1
#define BTM_GENERAL_DISCOVERABLE    2
#define BTM_DISCOVERABLE_MASK       (BTM_LIMITED_DISCOVERABLE|BTM_GENERAL_DISCOVERABLE)
#define BTM_MAX_DISCOVERABLE        BTM_GENERAL_DISCOVERABLE
/* BLE可发现模式的高字节*/
#define BTM_BLE_NON_DISCOVERABLE        0x0000
#define BTM_BLE_LIMITED_DISCOVERABLE    0x0100
#define BTM_BLE_GENERAL_DISCOVERABLE    0x0200
#define BTM_BLE_MAX_DISCOVERABLE        BTM_BLE_GENERAL_DISCOVERABLE
#define BTM_BLE_DISCOVERABLE_MASK       (BTM_BLE_NON_DISCOVERABLE|BTM_BLE_LIMITED_DISCOVERABLE|BTM_BLE_GENERAL_DISCOVERABLE)

/* 可连接模式*/
#define BTM_NON_CONNECTABLE         0
#define BTM_CONNECTABLE             1
#define BTM_CONNECTABLE_MASK        (BTM_NON_CONNECTABLE | BTM_CONNECTABLE)
/* BLE可连接模式的高字节*/
#define BTM_BLE_NON_CONNECTABLE      0x0000
#define BTM_BLE_CONNECTABLE          0x0100
#define BTM_BLE_MAX_CONNECTABLE      BTM_BLE_CONNECTABLE
#define BTM_BLE_CONNECTABLE_MASK    (BTM_BLE_NON_CONNECTABLE | BTM_BLE_CONNECTABLE)

/* 查询模式注意：这些模式与查询活动值（BTM_*active）相关*/
#define BTM_INQUIRY_NONE            0
#define BTM_GENERAL_INQUIRY         0x01
#define BTM_LIMITED_INQUIRY         0x02
#define BTM_BR_INQUIRY_MASK         (BTM_GENERAL_INQUIRY | BTM_LIMITED_INQUIRY)

/* BLE查询模式的查询模式的高字节*/
#define BTM_BLE_INQUIRY_NONE         0x00
#define BTM_BLE_GENERAL_INQUIRY      0x10
#define BTM_BLE_LIMITED_INQUIRY      0x20
#define BTM_BLE_INQUIRY_MASK         (BTM_BLE_GENERAL_INQUIRY|BTM_BLE_LIMITED_INQUIRY)

/* BTM_IsInquiryActive返回值（位掩码）注意：这些位掩码与查询模式（BTM_*_inquiry）相关*/
#define BTM_INQUIRY_INACTIVE        0x0     /* 没有正在进行的查询*/
#define BTM_GENERAL_INQUIRY_ACTIVE  BTM_GENERAL_INQUIRY     /* 一般性调查正在进行中*/
#define BTM_LIMITED_INQUIRY_ACTIVE  BTM_LIMITED_INQUIRY     /* 有限的调查正在进行中*/
#define BTM_PERIODIC_INQUIRY_ACTIVE 0x8     /* 定期查询处于活动状态*/
#define BTM_SSP_INQUIRY_ACTIVE      0x4     /* SSP处于活动状态，因此不允许查询（解决固件错误）*/
#define BTM_LE_GENERAL_INQUIRY_ACTIVE  BTM_BLE_GENERAL_INQUIRY     /* 一般性调查正在进行中*/
#define BTM_LE_LIMITED_INQUIRY_ACTIVE  BTM_BLE_LIMITED_INQUIRY      /* 有限的调查正在进行中*/

/* 查询活动掩码*/
#define BTM_BR_INQ_ACTIVE_MASK        (BTM_GENERAL_INQUIRY_ACTIVE|BTM_LIMITED_INQUIRY_ACTIVE|BTM_PERIODIC_INQUIRY_ACTIVE) /* BR/EDR查询活动掩码*/
#define BTM_BLE_SCAN_ACTIVE_MASK      0x01F0     /* LE扫描活动掩码*/
#define BTM_BLE_INQ_ACTIVE_MASK       (BTM_LE_GENERAL_INQUIRY_ACTIVE|BTM_LE_LIMITED_INQUIRY_ACTIVE) /* LE查询活动掩码*/
#define BTM_INQUIRY_ACTIVE_MASK       (BTM_BR_INQ_ACTIVE_MASK | BTM_BLE_INQ_ACTIVE_MASK) /* 查询活动掩码*/

/* 定义扫描类型*/
#define BTM_SCAN_TYPE_STANDARD      0
#define BTM_SCAN_TYPE_INTERLACED    1       /* 仅1.2设备*/

/* 定义查询结果模式*/
#define BTM_INQ_RESULT_STANDARD     0
#define BTM_INQ_RESULT_WITH_RSSI    1
#define BTM_INQ_RESULT_EXTENDED     2

#define BTM_INQ_RES_IGNORE_RSSI     0x7f    /* 未提供RSSI值（忽略）*/

/* 查询过滤器条件类型（请参见tBTM_INQ_PARMS）*/
#define BTM_CLR_INQUIRY_FILTER          0                   /* 查询筛选已关闭*/
#define BTM_FILTER_COND_DEVICE_CLASS    HCI_FILTER_COND_DEVICE_CLASS /* 按设备类别筛选*/
#define BTM_FILTER_COND_BD_ADDR         HCI_FILTER_COND_BD_ADDR /* 设备地址上的筛选器*/

/* 查询操作期间远程名称检索的状态。在tBTM_INQ_INFO结构中使用，并在BTM_InqDbRead、BTM_InqDbFirst和BTM_INQ DbNext函数中返回。当返回的状态为*BTM_INQ_RMT_name_DONE时，名称字段有效*/
#define BTM_INQ_RMT_NAME_EMPTY      0
#define BTM_INQ_RMT_NAME_PENDING    1
#define BTM_INQ_RMT_NAME_DONE       2
#define BTM_INQ_RMT_NAME_FAILED     3

/*********************************
 *** 设备常数类别***
 *********************************/
#define BTM_FORMAT_TYPE_1   0x00

/****************************
** 次要设备类别字段
*****************************/

/* 0x00用于所有次要设备类别的非分类*/
#define BTM_COD_MINOR_UNCLASSIFIED          0x00

/* 计算机专业类的次要设备类字段*/
/* #定义BTM_COD_MINOR_UNCLASSIFIED 0x00*/
#define BTM_COD_MINOR_DESKTOP_WORKSTATION   0x04
#define BTM_COD_MINOR_SERVER_COMPUTER       0x08
#define BTM_COD_MINOR_LAPTOP                0x0C
#define BTM_COD_MINOR_HANDHELD_PC_PDA       0x10    /* 蛤壳*/
#define BTM_COD_MINOR_PALM_SIZE_PC_PDA      0x14
#define BTM_COD_MINOR_WEARABLE_COMPUTER     0x18    /* 手表大小的*/

/* 电话主要类别的次要设备类别字段*/
/* #定义BTM_COD_MINOR_UNCLASSIFIED 0x00*/
#define BTM_COD_MINOR_CELLULAR              0x04
#define BTM_COD_MINOR_CORDLESS              0x08
#define BTM_COD_MINOR_SMART_PHONE           0x0C
#define BTM_COD_MINOR_WIRED_MDM_V_GTWY      0x10 /* 有线调制解调器或语音网关*/
#define BTM_COD_MINOR_ISDN_ACCESS           0x14

/* LAN接入点主要类别的次要设备类别字段*/
/* 负载系数字段第5-7位*/
#define BTM_COD_MINOR_FULLY_AVAILABLE       0x00
#define BTM_COD_MINOR_1_17_UTILIZED         0x20
#define BTM_COD_MINOR_17_33_UTILIZED        0x40
#define BTM_COD_MINOR_33_50_UTILIZED        0x60
#define BTM_COD_MINOR_50_67_UTILIZED        0x80
#define BTM_COD_MINOR_67_83_UTILIZED        0xA0
#define BTM_COD_MINOR_83_99_UTILIZED        0xC0
#define BTM_COD_MINOR_NO_SERVICE_AVAILABLE  0xE0
/* 子字段位2-4*/
/* #定义BTM_COD_MINOR_UNCLASSIFIED 0x00*/

/* 音频/视频主要类别的次要设备类别字段*/
/* #定义BTM_COD_MINOR_UNCLASSIFIED 0x00*/
#define BTM_COD_MINOR_CONFM_HEADSET         0x04
#define BTM_COD_MINOR_CONFM_HANDSFREE       0x08
#define BTM_COD_MINOR_MICROPHONE            0x10
#define BTM_COD_MINOR_LOUDSPEAKER           0x14
#define BTM_COD_MINOR_HEADPHONES            0x18
#define BTM_COD_MINOR_PORTABLE_AUDIO        0x1C
#define BTM_COD_MINOR_CAR_AUDIO             0x20
#define BTM_COD_MINOR_SET_TOP_BOX           0x24
#define BTM_COD_MINOR_HIFI_AUDIO            0x28
#define BTM_COD_MINOR_VCR                   0x2C
#define BTM_COD_MINOR_VIDEO_CAMERA          0x30
#define BTM_COD_MINOR_CAMCORDER             0x34
#define BTM_COD_MINOR_VIDEO_MONITOR         0x38
#define BTM_COD_MINOR_VIDDISP_LDSPKR        0x3C
#define BTM_COD_MINOR_VIDEO_CONFERENCING    0x40
#define BTM_COD_MINOR_GAMING_TOY            0x48

/* 外围设备主要类别的次要设备类别字段*/
/* 第6-7位独立指定鼠标、键盘或组合鼠标/键盘*/
#define BTM_COD_MINOR_KEYBOARD              0x40
#define BTM_COD_MINOR_POINTING              0x80
#define BTM_COD_MINOR_COMBO                 0xC0
/* 第2-5位与第6-7位的选择进行“或”运算*/
/* #定义BTM_COD_MINOR_UNCLASSIFIED 0x00*/
#define BTM_COD_MINOR_JOYSTICK              0x04
#define BTM_COD_MINOR_GAMEPAD               0x08
#define BTM_COD_MINOR_REMOTE_CONTROL        0x0C
#define BTM_COD_MINOR_SENSING_DEVICE        0x10
#define BTM_COD_MINOR_DIGITIZING_TABLET     0x14
#define BTM_COD_MINOR_CARD_READER           0x18    /* e、 g.SIM卡读取器*/
#define BTM_COD_MINOR_DIGITAL_PAN           0x1C
#define BTM_COD_MINOR_HAND_SCANNER          0x20
#define BTM_COD_MINOR_HAND_GESTURAL_INPUT   0x24

/* 成像主要类别的次要设备类别字段*/
/* 第5-7位独立指定显示器、照相机、扫描仪或打印机*/
#define BTM_COD_MINOR_DISPLAY               0x10
#define BTM_COD_MINOR_CAMERA                0x20
#define BTM_COD_MINOR_SCANNER               0x40
#define BTM_COD_MINOR_PRINTER               0x80
/* 保留2-3位*/
/* #定义BTM_COD_MINOR_UNCLASSIFIED 0x00*/

/* 可穿戴主要类别的次要设备类别字段*/
/* 第2-7位有意义*/
#define BTM_COD_MINOR_WRIST_WATCH           0x04
#define BTM_COD_MINOR_PAGER                 0x08
#define BTM_COD_MINOR_JACKET                0x0C
#define BTM_COD_MINOR_HELMET                0x10
#define BTM_COD_MINOR_GLASSES               0x14

/* 玩具大类的次要设备类字段*/
/* 第2-7位有意义*/
#define BTM_COD_MINOR_ROBOT                 0x04
#define BTM_COD_MINOR_VEHICLE               0x08
#define BTM_COD_MINOR_DOLL_ACTION_FIGURE    0x0C
#define BTM_COD_MINOR_CONTROLLER            0x10
#define BTM_COD_MINOR_GAME                  0x14

/* Health Major class的minor device class字段*/
/* 第2-7位有意义*/
#define BTM_COD_MINOR_BLOOD_MONITOR         0x04
#define BTM_COD_MINOR_THERMOMETER           0x08
#define BTM_COD_MINOR_WEIGHING_SCALE        0x0C
#define BTM_COD_MINOR_GLUCOSE_METER         0x10
#define BTM_COD_MINOR_PULSE_OXIMETER        0x14
#define BTM_COD_MINOR_HEART_PULSE_MONITOR   0x18
#define BTM_COD_MINOR_HEALTH_DATA_DISPLAY   0x1C
#define BTM_COD_MINOR_STEP_COUNTER          0x20
#define BTM_COD_MINOR_BODY_COM_ANALYZER     0x24
#define BTM_COD_MINOR_PEAK_FLOW_MONITOR     0x28
#define BTM_COD_MINOR_MEDICATION_MONITOR    0x2C
#define BTM_COD_MINOR_KNEE_PROSTHESIS       0x30
#define BTM_COD_MINOR_ANKLE_PROSTHESIS      0x34


/***************************
** 主要设备类别字段
****************************/
#define BTM_COD_MAJOR_MISCELLANEOUS         0x00
#define BTM_COD_MAJOR_COMPUTER              0x01
#define BTM_COD_MAJOR_PHONE                 0x02
#define BTM_COD_MAJOR_LAN_ACCESS_PT         0x03
#define BTM_COD_MAJOR_AUDIO                 0x04
#define BTM_COD_MAJOR_PERIPHERAL            0x05
#define BTM_COD_MAJOR_IMAGING               0x06
#define BTM_COD_MAJOR_WEARABLE              0x07
#define BTM_COD_MAJOR_TOY                   0x08
#define BTM_COD_MAJOR_HEALTH                0x09
#define BTM_COD_MAJOR_UNCLASSIFIED          0x1F

/***************************
** 服务类字段
****************************/
#define BTM_COD_SERVICE_LMTD_DISCOVER       0x0020
#define BTM_COD_SERVICE_POSITIONING         0x0100
#define BTM_COD_SERVICE_NETWORKING          0x0200
#define BTM_COD_SERVICE_RENDERING           0x0400
#define BTM_COD_SERVICE_CAPTURING           0x0800
#define BTM_COD_SERVICE_OBJ_TRANSFER        0x1000
#define BTM_COD_SERVICE_AUDIO               0x2000
#define BTM_COD_SERVICE_TELEPHONY           0x4000
#define BTM_COD_SERVICE_INFORMATION         0x8000

/* 设备字段宏类*/
#define BTM_COD_FORMAT_TYPE(u8, pd)         {u8  = pd[2]&0x03;}
#define BTM_COD_MINOR_CLASS(u8, pd)         {u8  = pd[2]&0xFC;}
#define BTM_COD_MAJOR_CLASS(u8, pd)         {u8  = pd[1]&0x1F;}
#define BTM_COD_SERVICE_CLASS(u16, pd)      {u16 = pd[0]; u16<<=8; u16 += pd[1]&0xE0;}

/* 设置字段（假设格式类型始终为0）*/
#define FIELDS_TO_COD(pd, mn, mj, sv) {pd[2] = mn; pd[1] =              \
                                       mj+ ((sv)&BTM_COD_SERVICE_CLASS_LO_B); \
                                       pd[0] = (sv) >> 8;}

/* COD掩模*/
#define BTM_COD_FORMAT_TYPE_MASK      0x03
#define BTM_COD_MINOR_CLASS_MASK      0xFC
#define BTM_COD_MAJOR_CLASS_MASK      0x1F
#define BTM_COD_SERVICE_CLASS_LO_B    0x00E0
#define BTM_COD_SERVICE_CLASS_MASK    0xFFE0


/* BTM服务定义用于将EIR数据存储到位掩码
*/
enum {
    BTM_EIR_UUID_SERVCLASS_SERVICE_DISCOVERY_SERVER,
    /*    BTM_EIR_UUID_SERVCLASS_BROWSE_GROUP_DESCRIPTOR,   */
    /*    BTM_EIR_UUID_SERVCLASS_PUBLIC_BROWSE_GROUP,       */
    BTM_EIR_UUID_SERVCLASS_SERIAL_PORT,
    BTM_EIR_UUID_SERVCLASS_LAN_ACCESS_USING_PPP,
    BTM_EIR_UUID_SERVCLASS_DIALUP_NETWORKING,
    BTM_EIR_UUID_SERVCLASS_IRMC_SYNC,
    BTM_EIR_UUID_SERVCLASS_OBEX_OBJECT_PUSH,
    BTM_EIR_UUID_SERVCLASS_OBEX_FILE_TRANSFER,
    BTM_EIR_UUID_SERVCLASS_IRMC_SYNC_COMMAND,
    BTM_EIR_UUID_SERVCLASS_HEADSET,
    BTM_EIR_UUID_SERVCLASS_CORDLESS_TELEPHONY,
    BTM_EIR_UUID_SERVCLASS_AUDIO_SOURCE,
    BTM_EIR_UUID_SERVCLASS_AUDIO_SINK,
    BTM_EIR_UUID_SERVCLASS_AV_REM_CTRL_TARGET,
    /*    BTM_EIR_UUID_SERVCLASS_ADV_AUDIO_DISTRIBUTION,    */
    BTM_EIR_UUID_SERVCLASS_AV_REMOTE_CONTROL,
    /*    BTM_EIR_UUID_SERVCLASS_VIDEO_CONFERENCING,        */
    BTM_EIR_UUID_SERVCLASS_INTERCOM,
    BTM_EIR_UUID_SERVCLASS_FAX,
    BTM_EIR_UUID_SERVCLASS_HEADSET_AUDIO_GATEWAY,
    /*    BTM_EIR_UUID_SERVCLASS_WAP,                       */
    /*    BTM_EIR_UUID_SERVCLASS_WAP_CLIENT,                */
    BTM_EIR_UUID_SERVCLASS_PANU,
    BTM_EIR_UUID_SERVCLASS_NAP,
    BTM_EIR_UUID_SERVCLASS_GN,
    BTM_EIR_UUID_SERVCLASS_DIRECT_PRINTING,
    /*    BTM_EIR_UUID_SERVCLASS_REFERENCE_PRINTING,        */
    BTM_EIR_UUID_SERVCLASS_IMAGING,
    BTM_EIR_UUID_SERVCLASS_IMAGING_RESPONDER,
    BTM_EIR_UUID_SERVCLASS_IMAGING_AUTO_ARCHIVE,
    BTM_EIR_UUID_SERVCLASS_IMAGING_REF_OBJECTS,
    BTM_EIR_UUID_SERVCLASS_HF_HANDSFREE,
    BTM_EIR_UUID_SERVCLASS_AG_HANDSFREE,
    BTM_EIR_UUID_SERVCLASS_DIR_PRT_REF_OBJ_SERVICE,
    /*    BTM_EIR_UUID_SERVCLASS_REFLECTED_UI,              */
    BTM_EIR_UUID_SERVCLASS_BASIC_PRINTING,
    BTM_EIR_UUID_SERVCLASS_PRINTING_STATUS,
    BTM_EIR_UUID_SERVCLASS_HUMAN_INTERFACE,
    BTM_EIR_UUID_SERVCLASS_CABLE_REPLACEMENT,
    BTM_EIR_UUID_SERVCLASS_HCRP_PRINT,
    BTM_EIR_UUID_SERVCLASS_HCRP_SCAN,
    /*    BTM_EIR_UUID_SERVCLASS_COMMON_ISDN_ACCESS,        */
    /*    BTM_EIR_UUID_SERVCLASS_VIDEO_CONFERENCING_GW,     */
    /*    BTM_EIR_UUID_SERVCLASS_UDI_MT,                    */
    /*    BTM_EIR_UUID_SERVCLASS_UDI_TA,                    */
    /*    BTM_EIR_UUID_SERVCLASS_VCP,                       */
    BTM_EIR_UUID_SERVCLASS_SAP,
    BTM_EIR_UUID_SERVCLASS_PBAP_PCE,
    BTM_EIR_UUID_SERVCLASS_PBAP_PSE,
    /*    BTM_EIR_UUID_SERVCLASS_TE_PHONE_ACCESS,           */
    /*    BTM_EIR_UUID_SERVCLASS_ME_PHONE_ACCESS,           */
    BTM_EIR_UUID_SERVCLASS_PHONE_ACCESS,
    BTM_EIR_UUID_SERVCLASS_HEADSET_HS,
    BTM_EIR_UUID_SERVCLASS_PNP_INFORMATION,
    /*    BTM_EIR_UUID_SERVCLASS_GENERIC_NETWORKING,        */
    /*    BTM_EIR_UUID_SERVCLASS_GENERIC_FILETRANSFER,      */
    /*    BTM_EIR_UUID_SERVCLASS_GENERIC_AUDIO,             */
    /*    BTM_EIR_UUID_SERVCLASS_GENERIC_TELEPHONY,         */
    /*    BTM_EIR_UUID_SERVCLASS_UPNP_SERVICE,              */
    /*    BTM_EIR_UUID_SERVCLASS_UPNP_IP_SERVICE,           */
    /*    BTM_EIR_UUID_SERVCLASS_ESDP_UPNP_IP_PAN,          */
    /*    BTM_EIR_UUID_SERVCLASS_ESDP_UPNP_IP_LAP,          */
    /*    BTM_EIR_UUID_SERVCLASS_ESDP_UPNP_IP_L2CAP,        */
    BTM_EIR_UUID_SERVCLASS_VIDEO_SOURCE,
    BTM_EIR_UUID_SERVCLASS_VIDEO_SINK,
    /*    BTM_EIR_UUID_SERVCLASS_VIDEO_DISTRIBUTION         */
    /*    BTM_EIR_UUID_SERVCLASS_HDP_PROFILE                */
    BTM_EIR_UUID_SERVCLASS_MESSAGE_ACCESS,
    BTM_EIR_UUID_SERVCLASS_MESSAGE_NOTIFICATION,
    BTM_EIR_UUID_SERVCLASS_HDP_SOURCE,
    BTM_EIR_UUID_SERVCLASS_HDP_SINK,
    BTM_EIR_MAX_SERVICES
};

/* 查询数据库EIR中的搜索结果*/
#define BTM_EIR_FOUND           0
#define BTM_EIR_NOT_FOUND       1
#define BTM_EIR_UNKNOWN         2

typedef UINT8 tBTM_EIR_SEARCH_RESULT;

#define BTM_EIR_FLAGS_TYPE                  HCI_EIR_FLAGS_TYPE                  /* 0x01*/
#define BTM_EIR_MORE_16BITS_UUID_TYPE       HCI_EIR_MORE_16BITS_UUID_TYPE       /* 0x02*/
#define BTM_EIR_COMPLETE_16BITS_UUID_TYPE   HCI_EIR_COMPLETE_16BITS_UUID_TYPE   /* 0x03*/
#define BTM_EIR_MORE_32BITS_UUID_TYPE       HCI_EIR_MORE_32BITS_UUID_TYPE       /* 0x04*/
#define BTM_EIR_COMPLETE_32BITS_UUID_TYPE   HCI_EIR_COMPLETE_32BITS_UUID_TYPE   /* 0x05*/
#define BTM_EIR_MORE_128BITS_UUID_TYPE      HCI_EIR_MORE_128BITS_UUID_TYPE      /* 0x06*/
#define BTM_EIR_COMPLETE_128BITS_UUID_TYPE  HCI_EIR_COMPLETE_128BITS_UUID_TYPE  /* 0x07*/
#define BTM_EIR_SHORTENED_LOCAL_NAME_TYPE   HCI_EIR_SHORTENED_LOCAL_NAME_TYPE   /* 0x08*/
#define BTM_EIR_COMPLETE_LOCAL_NAME_TYPE    HCI_EIR_COMPLETE_LOCAL_NAME_TYPE    /* 0x09*/
#define BTM_EIR_TX_POWER_LEVEL_TYPE         HCI_EIR_TX_POWER_LEVEL_TYPE         /* 0x0A*/
#define BTM_EIR_URL_TYPE                    HCI_EIR_URL_TYPE                    /* 0时24分*/
#define BTM_EIR_MANUFACTURER_SPECIFIC_TYPE  HCI_EIR_MANUFACTURER_SPECIFIC_TYPE  /* 0xFF（英尺/平方英尺）*/

#define BTM_EIR_TYPE_MAX_NUM                12                                  /* 最大EIR类型*/

/* 以下EIR标记定义为OOB，而不是常规EIR数据*/
#define BTM_EIR_OOB_BD_ADDR_TYPE            HCI_EIR_OOB_BD_ADDR_TYPE    /* 6字节*/
#define BTM_EIR_OOB_COD_TYPE                HCI_EIR_OOB_COD_TYPE        /* 3字节*/
#define BTM_EIR_OOB_SSP_HASH_C_TYPE         HCI_EIR_OOB_SSP_HASH_C_TYPE /* 16字节*/
#define BTM_EIR_OOB_SSP_RAND_R_TYPE         HCI_EIR_OOB_SSP_RAND_R_TYPE /* 16字节*/

#define BTM_OOB_MANDATORY_SIZE      8   /* 包括2字节长度和6字节bd_addr*/
#define BTM_OOB_DATA_LEN_SIZE       2
#define BTM_OOB_BD_ADDR_SIZE        6
#define BTM_OOB_COD_SIZE            BT_OOB_COD_SIZE
#define BTM_OOB_HASH_C_SIZE         BT_OOB_HASH_C_SIZE
#define BTM_OOB_RAND_R_SIZE         BT_OOB_RAND_R_SIZE


#if BLE_INCLUDED == TRUE
#define BTM_BLE_SEC_NONE                0
#define BTM_BLE_SEC_ENCRYPT             1 /* 使用当前密钥加密链接*/
#define BTM_BLE_SEC_ENCRYPT_NO_MITM     2
#define BTM_BLE_SEC_ENCRYPT_MITM        3
typedef UINT8   tBTM_BLE_SEC_ACT;
#endif
/************************************************************************************************
** BTM服务MACROS处理超过32个服务的UINT32位数组
*************************************************************************************************/
/* 确定服务所需的UINT32的数量*/
#define BTM_EIR_ARRAY_BITS          32          /* 每个数组元素中的位数*/
#define BTM_EIR_SERVICE_ARRAY_SIZE  (((UINT32)BTM_EIR_MAX_SERVICES / BTM_EIR_ARRAY_BITS) + \
                                    (((UINT32)BTM_EIR_MAX_SERVICES % BTM_EIR_ARRAY_BITS) ? 1 : 0))

/* MACRO设置位流中的服务位掩码*/
#define BTM_EIR_SET_SERVICE(p, service)  (((UINT32 *)(p))[(((UINT32)(service)) / BTM_EIR_ARRAY_BITS)] |=  \
                                    ((UINT32)1 << (((UINT32)(service)) % BTM_EIR_ARRAY_BITS)))


/* MACRO清除位流中的服务位掩码*/
#define BTM_EIR_CLR_SERVICE(p, service)  (((UINT32 *)(p))[(((UINT32)(service)) / BTM_EIR_ARRAY_BITS)] &=  \
                                    ~((UINT32)1 << (((UINT32)(service)) % BTM_EIR_ARRAY_BITS)))

/* MACRO检查位流中的服务位掩码*/
#define BTM_EIR_HAS_SERVICE(p, service)  ((((UINT32 *)(p))[(((UINT32)(service)) / BTM_EIR_ARRAY_BITS)] &  \
                                    ((UINT32)1 << (((UINT32)(service)) % BTM_EIR_ARRAY_BITS))) >> (((UINT32)(service)) % BTM_EIR_ARRAY_BITS))

/* HCI缓冲区中EIR的开始，4字节=HCI命令（2）+长度（1）+FEC_Req（1）*/
#define BTM_HCI_EIR_OFFSET          (BT_HDR_SIZE + 4)

/***************************
**  设备发现类型
****************************/
/* 传递给BTM_StartInquiry和BTM_SetPeriodicInquiryMode的参数的定义。
*/
typedef struct {            /* 包含两个设备类条件字段*/
    DEV_CLASS       dev_class;
    DEV_CLASS       dev_class_mask;
} tBTM_COD_COND;


typedef union {             /* 包含查询筛选条件*/
    BD_ADDR         bdaddr_cond;
    tBTM_COD_COND   cod_cond;
} tBTM_INQ_FILT_COND;


typedef struct {            /* 包含传递给查询函数的参数*/
    UINT8   mode;                       /* 一般或有限*/
    UINT8   duration;                   /* 查询持续时间（1.28秒增量）*/
    UINT8   max_resps;                  /* 要返回的最大响应数*/
    BOOLEAN report_dup;                 /* 报告具有较高RSSI值的重复查询响应*/
    UINT8   filter_cond_type;           /* 新设备、BD ADDR、COD或无过滤*/
    tBTM_INQ_FILT_COND  filter_cond;    /* 基于过滤器cond类型的过滤器值*/
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    UINT8   intl_duration[4];              /*存储交织扫描时间部分的持续时间数组*/
#endif
} tBTM_INQ_PARMS;

#define BTM_INQ_RESULT_BR       0x01
#define BTM_INQ_RESULT_BLE      0x02

#if (BLE_INCLUDED == TRUE)
#define BTM_BLE_EVT_CONN_ADV        0x00
#define BTM_BLE_EVT_CONN_DIR_ADV    0x01
#define BTM_BLE_EVT_DISC_ADV        0x02
#define BTM_BLE_EVT_NON_CONN_ADV    0x03
#define BTM_BLE_EVT_SCAN_RSP        0x04
typedef UINT8 tBTM_BLE_EVT_TYPE;
#endif

/* 这些是每个设备对查询的响应中返回的字段。如果已注册，则在结果回调中返回。
*/
typedef struct {
    UINT16      clock_offset;
    BD_ADDR     remote_bd_addr;
    DEV_CLASS   dev_class;
    UINT8       page_scan_rep_mode;
    UINT8       page_scan_per_mode;
    UINT8       page_scan_mode;
    INT8        rssi;       /* 如果无效，则设置为BTM_INQ_RES_IGNORE_RSI*/
    UINT32      eir_uuid[BTM_EIR_SERVICE_ARRAY_SIZE];
    BOOLEAN     eir_complete_list;
    tBT_DEVICE_TYPE         device_type;
#if (BLE_INCLUDED == TRUE)
    UINT8       inq_result_type;
    UINT8       ble_addr_type;
    tBTM_BLE_EVT_TYPE       ble_evt_type;
    UINT8                   flag;
    UINT8       adv_data_len;
    UINT8       scan_rsp_len;
#endif
} tBTM_INQ_RESULTS;


/* 这是BTM保存在其数据库中的查询响应信息，可通过BTM_InqDbRead、BTM_Inq DbFirst和BTM_Inq-DbNext向应用程序提供。
*/
typedef struct {
    tBTM_INQ_RESULTS    results;

    BOOLEAN             appl_knows_rem_name;    /* 如果应用程序知道对等设备的远程名称，则由应用程序设置。稍后应用程序将使用此选项来确定是否需要完成远程名称请求。在此处设置标志可避免重复存储查询结果*/
#if ( BLE_INCLUDED == TRUE)
    UINT16          remote_name_len;
    tBTM_BD_NAME    remote_name;
    UINT8           remote_name_state;
    UINT8           remote_name_type;
#endif

} tBTM_INQ_INFO;


/* 返回查询完成回调的结构*/
typedef struct {
    tBTM_STATUS status;
    UINT8       num_resp;       /* 当前查询的结果数*/
} tBTM_INQUIRY_CMPL;

/* 随远程名称请求返回的结构*/
typedef struct {
    UINT16      status;
    BD_ADDR     bd_addr;
    UINT16      length;
    BD_NAME     remote_bd_name;
} tBTM_REMOTE_DEV_NAME;

typedef struct {
    UINT8   pcm_intf_rate;  /* PCM接口速率：0:128kbps，1:256kbps；2： 512个基点；3： 1024kbps；4： 2048kbps*/
    UINT8   frame_type;     /* 帧类型：0：短；1： 长的，长的*/
    UINT8   sync_mode;      /* 同步模式：0：从；1： 船长，船长*/
    UINT8   clock_mode;     /* 时钟模式：0：从机；1： 船长，船长*/

} tBTM_SCO_PCM_PARAM;

/****************************************
**  设备发现回调函数
*****************************************/
/* BTM查询数据库更改时异步通知的回调功能。第一个参数是查询数据库，第二个参数是是否添加到查询数据库或从查询数据库中删除。
*/
typedef void (tBTM_INQ_DB_CHANGE_CB) (void *p1, BOOLEAN is_new);

/* BTM收到查询响应时的通知回调功能。第一个参数是查询结果数据库，第二个参数是EIR的指针。
*/
typedef void (tBTM_INQ_RESULTS_CB) (tBTM_INQ_RESULTS *p_inq_results, UINT8 *p_eir);

/*****************************************************************************
**  ACL CHANNEL MANAGEMENT
*****************************************************************************/
/******************
**  ACL常量
*******************/

/* ACL模式*/
#define BTM_ACL_MODE_NORMAL     HCI_MODE_ACTIVE
#define BTM_ACL_MODE_HOLD       HCI_MODE_HOLD
#define BTM_ACL_MODE_SNIFF      HCI_MODE_SNIFF
#define BTM_ACL_MODE_PARK       HCI_MODE_PARK

/* 返回角色切换回调（tBTM_role_switch_MPL）中的结构*/
#define BTM_ROLE_MASTER         HCI_ROLE_MASTER
#define BTM_ROLE_SLAVE          HCI_ROLE_SLAVE
#define BTM_ROLE_UNDEFINED      0xff     /* 未定义值（错误状态）*/

/* ACL数据包类型*/
#define BTM_ACL_PKT_TYPES_MASK_DM1      HCI_PKT_TYPES_MASK_DM1
#define BTM_ACL_PKT_TYPES_MASK_DH1      HCI_PKT_TYPES_MASK_DH1
#define BTM_ACL_PKT_TYPES_MASK_DM3      HCI_PKT_TYPES_MASK_DM3
#define BTM_ACL_PKT_TYPES_MASK_DH3      HCI_PKT_TYPES_MASK_DH3
#define BTM_ACL_PKT_TYPES_MASK_DM5      HCI_PKT_TYPES_MASK_DM5
#define BTM_ACL_PKT_TYPES_MASK_DH5      HCI_PKT_TYPES_MASK_DH5
#define BTM_ACL_PKT_TYPES_MASK_NO_2_DH1 HCI_PKT_TYPES_MASK_NO_2_DH1
#define BTM_ACL_PKT_TYPES_MASK_NO_3_DH1 HCI_PKT_TYPES_MASK_NO_3_DH1
#define BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 HCI_PKT_TYPES_MASK_NO_2_DH3
#define BTM_ACL_PKT_TYPES_MASK_NO_3_DH3 HCI_PKT_TYPES_MASK_NO_3_DH3
#define BTM_ACL_PKT_TYPES_MASK_NO_2_DH5 HCI_PKT_TYPES_MASK_NO_2_DH5
#define BTM_ACL_PKT_TYPES_MASK_NO_3_DH5 HCI_PKT_TYPES_MASK_NO_3_DH5

/***************
**  ACL类型
****************/

/* 响应BTM_SwitchRole调用，返回了带有角色切换信息（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    UINT8   hci_status;     /* 随事件返回的HCI状态*/
    UINT8   role;           /* BTM_ROLE_MASTER或BTM_ROLE-SLAVE*/
    BD_ADDR remote_bd_addr; /* 交换机涉及的远程BD地址*/
} tBTM_ROLE_SWITCH_CMPL;

/* 响应BTM_SetQoS调用，返回了带有QoS信息的结构（在tBTM_CMPL_CB回调函数中）。
*/
typedef struct {
    FLOW_SPEC flow;
    UINT16 handle;
    UINT8 status;
    BD_ADDR     rem_bda;
} tBTM_QOS_SETUP_CMPL;


/* 响应BTM_ReadRSSI调用，返回带有读取RSSI事件（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    tBTM_STATUS status;
    UINT8       hci_status;
    INT8        rssi;
    BD_ADDR     rem_bda;
} tBTM_RSSI_RESULTS;

/* 响应BTM_ReadTxPower调用，返回了带有读取当前TX功率事件（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    tBTM_STATUS status;
    UINT8       hci_status;
    INT8        tx_power;
    BD_ADDR     rem_bda;
} tBTM_TX_POWER_RESULTS;

/* 响应BTM_ReadLinkQuality调用，返回带有读取链接质量事件（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    tBTM_STATUS status;
    UINT8       hci_status;
    UINT8       link_quality;
    BD_ADDR     rem_bda;
} tBTM_LINK_QUALITY_RESULTS;

/* 响应BTM_SetAfhChannels调用，返回了带有set AFH channels事件（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    tBTM_STATUS status;
    UINT8       hci_status;
} tBTM_SET_AFH_CHANNELS_RESULTS;

/* 响应于BTM_BleSetChannels调用，返回了带有设置BLE通道事件（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    tBTM_STATUS status;
    UINT8       hci_status;
} tBTM_BLE_SET_CHANNELS_RESULTS;

/* 响应BTM_ReadInquiryRspTxPower调用，返回带有read-inq tx电能质量事件（在tBTM_CMPL_CB回调函数中）的结构。
*/
typedef struct {
    tBTM_STATUS status;
    UINT8       hci_status;
    INT8        tx_power;
} tBTM_INQ_TXPWR_RESULTS;

enum {
    BTM_BL_CONN_EVT,
    BTM_BL_DISCN_EVT,
    BTM_BL_UPDATE_EVT,
    BTM_BL_ROLE_CHG_EVT,
    BTM_BL_COLLISION_EVT
};
typedef UINT8 tBTM_BL_EVENT;
typedef UINT16 tBTM_BL_EVENT_MASK;

#define BTM_BL_CONN_MASK        0x0001
#define BTM_BL_DISCN_MASK       0x0002
#define BTM_BL_UPDATE_MASK      0x0004
#define BTM_BL_ROLE_CHG_MASK    0x0008

/* 设备功能掩码定义*/
#define BTM_FEATURE_BYTES_PER_PAGE  HCI_FEATURE_BYTES_PER_PAGE
#define BTM_EXT_FEATURES_PAGE_MAX   HCI_EXT_FEATURES_PAGE_MAX

/* 与BTM_BL_CONN_EVT关联的数据类型*/
typedef struct {
    tBTM_BL_EVENT   event;          /* 事件已报告。*/
    BD_ADDR_PTR     p_bda;          /* 新连接设备的地址*/
    DEV_CLASS_PTR   p_dc;           /* 设备类*/
    BD_NAME_PTR     p_bdn;          /* 设备名称*/
    UINT8          *p_features;     /* 指向远程设备功能页[0]的指针（支持的功能页）*/
    BOOLEAN         sc_downgrade;   /* 安全连接降级状态。*/
#if BLE_INCLUDED == TRUE
    UINT16          handle;         /* 连接手柄*/
    tBT_TRANSPORT   transport;      /* 链接是否为LE*/
#endif
} tBTM_BL_CONN_DATA;

/* 与BTM_BL_DISCN_EVT关联的数据类型*/
typedef struct {
    tBTM_BL_EVENT   event;  /* 事件已报告。*/
    BD_ADDR_PTR     p_bda;  /* 断开连接的设备的地址*/
#if BLE_INCLUDED == TRUE
    UINT16          handle; /* 断开连接手柄*/
    tBT_TRANSPORT   transport; /* 链接是否为LE链接*/
#endif
} tBTM_BL_DISCN_DATA;

/* 当查询/寻呼正在进行时，忙碌级别应设置查询_寻呼掩码，否则为ACL链接数*/
#define BTM_BL_INQUIRY_PAGING_MASK 0x10
#define BTM_BL_INQUIRY_STARTED   (BTM_BL_INQUIRY_PAGING_MASK | 0x1)
#define BTM_BL_INQUIRY_CANCELLED (BTM_BL_INQUIRY_PAGING_MASK | 0x2)
#define BTM_BL_INQUIRY_COMPLETE  (BTM_BL_INQUIRY_PAGING_MASK | 0x3)
#define BTM_BL_PAGING_STARTED    (BTM_BL_INQUIRY_PAGING_MASK | 0x4)
#define BTM_BL_PAGING_COMPLETE   (BTM_BL_INQUIRY_PAGING_MASK | 0x5)
/* 与BTM_BL_UPDATE_EVT关联的数据类型*/
typedef struct {
    tBTM_BL_EVENT   event;  /* 事件已报告。*/
    UINT8           busy_level;/* 分页或查询时，级别为10。否则，ACL链接数。*/
    UINT8           busy_level_flags; /* 通知实际查询/页面活动*/
} tBTM_BL_UPDATE_DATA;

/* 与BTM_BL_ROLE_CHG_EVT关联的数据类型*/
typedef struct {
    tBTM_BL_EVENT   event;      /* 事件已报告。*/
    BD_ADDR_PTR     p_bda;      /* 对等连接设备的地址*/
    UINT8           new_role;
    UINT8           hci_status; /* 随事件返回的HCI状态*/
} tBTM_BL_ROLE_CHG_DATA;

typedef union {
    tBTM_BL_EVENT           event;  /* 事件已报告。*/
    tBTM_BL_CONN_DATA       conn;   /* 与BTM_BL_CONN_EVT相关的数据*/
    tBTM_BL_DISCN_DATA      discn;  /* 与BTM_BL_DISCN_EVT相关的数据*/
    tBTM_BL_UPDATE_DATA     update; /* 与BTM_BL_UPDATE_EVT相关的数据*/
    tBTM_BL_ROLE_CHG_DATA   role_chg;/*与BTM_BL_ROLE_CHG_EVT相关的数据*/
} tBTM_BL_EVENT_DATA;

/* BTM繁忙级别更改时的通知回调功能。
*/
typedef void (tBTM_BL_CHANGE_CB) (tBTM_BL_EVENT_DATA *p_data);

/***************************
**  ACL回调函数
****************************/
/* BTM ACL连接数据库更改时的通知回调函数。第一个参数是BD地址，第二个参数是添加或删除的。通过BTM_AclRegisterForChanges调用注册。
*/
#if BLE_INCLUDED == TRUE
typedef void (tBTM_ACL_DB_CHANGE_CB) (BD_ADDR p_bda, DEV_CLASS p_dc,
                                      BD_NAME p_bdn, UINT8 *features,
                                      BOOLEAN is_new, UINT16 handle,
                                      tBT_TRANSPORT transport);
#else
typedef void (tBTM_ACL_DB_CHANGE_CB) (BD_ADDR p_bda, DEV_CLASS p_dc,
                                      BD_NAME p_bdn, UINT8 *features,
                                      BOOLEAN is_new);
#endif
/*****************************************************************************
**  SCO CHANNEL MANAGEMENT
*****************************************************************************/
/******************
**  SCO常量
*******************/

/* 定义无效的SCO索引和无效的HCI句柄*/
#define BTM_INVALID_SCO_INDEX       0xFFFF
#define BTM_INVALID_HCI_HANDLE      0xFFFF

/* 定义无效的SCO断开原因*/
#define BTM_INVALID_SCO_DISC_REASON 0xFFFF

/* 定义第一个活动SCO索引*/
#define BTM_FIRST_ACTIVE_SCO_INDEX  BTM_MAX_SCO_LINKS

/* 定义API中使用的SCO数据包类型*/
#define BTM_SCO_PKT_TYPES_MASK_HV1  HCI_ESCO_PKT_TYPES_MASK_HV1
#define BTM_SCO_PKT_TYPES_MASK_HV2  HCI_ESCO_PKT_TYPES_MASK_HV2
#define BTM_SCO_PKT_TYPES_MASK_HV3  HCI_ESCO_PKT_TYPES_MASK_HV3
#define BTM_SCO_PKT_TYPES_MASK_EV3  HCI_ESCO_PKT_TYPES_MASK_EV3
#define BTM_SCO_PKT_TYPES_MASK_EV4  HCI_ESCO_PKT_TYPES_MASK_EV4
#define BTM_SCO_PKT_TYPES_MASK_EV5  HCI_ESCO_PKT_TYPES_MASK_EV5
#define BTM_SCO_PKT_TYPES_MASK_NO_2_EV3  HCI_ESCO_PKT_TYPES_MASK_NO_2_EV3
#define BTM_SCO_PKT_TYPES_MASK_NO_3_EV3  HCI_ESCO_PKT_TYPES_MASK_NO_3_EV3
#define BTM_SCO_PKT_TYPES_MASK_NO_2_EV5  HCI_ESCO_PKT_TYPES_MASK_NO_2_EV5
#define BTM_SCO_PKT_TYPES_MASK_NO_3_EV5  HCI_ESCO_PKT_TYPES_MASK_NO_3_EV5

#define BTM_SCO_LINK_ONLY_MASK  (BTM_SCO_PKT_TYPES_MASK_HV1 | \
                                 BTM_SCO_PKT_TYPES_MASK_HV2 | \
                                 BTM_SCO_PKT_TYPES_MASK_HV3)

#define BTM_ESCO_LINK_ONLY_MASK (BTM_SCO_PKT_TYPES_MASK_EV3 | \
                                 BTM_SCO_PKT_TYPES_MASK_EV4 | \
                                 BTM_SCO_PKT_TYPES_MASK_EV5)

#define BTM_SCO_LINK_ALL_PKT_MASK   (BTM_SCO_LINK_ONLY_MASK     | \
                                     BTM_ESCO_LINK_ONLY_MASK)

#define BTM_VALID_SCO_ALL_PKT_TYPE HCI_VALID_SCO_ALL_PKT_TYPE

/* 如果应忽略数据包类型参数，则传入BTM_CreateSco*/
#define BTM_IGNORE_SCO_PKT_TYPE     0

/***************
**  SCO类型
****************/
#define BTM_LINK_TYPE_SCO           HCI_LINK_TYPE_SCO
#define BTM_LINK_TYPE_ESCO          HCI_LINK_TYPE_ESCO
typedef UINT8 tBTM_SCO_TYPE;


/*******************
** SCO路由路径
********************/
#define BTM_SCO_ROUTE_PCM           (0) // HCI_BRCM_SCO_ROUTE_PCM
#define BTM_SCO_ROUTE_HCI           (1) // HCI_BRCM_SCO_ROUTE_HCI
typedef UINT8 tBTM_SCO_ROUTE_TYPE;


/*******************
** SCO编解码器类型
********************/
// TODO（谷歌）这应该使用通用定义
// 在hci/include/hci_audio.h中
#define BTM_SCO_CODEC_NONE          0x0000
#define BTM_SCO_CODEC_CVSD          0x0001
#define BTM_SCO_CODEC_MSBC          0x0002
typedef UINT16 tBTM_SCO_CODEC_TYPE;



/*******************
** SCO空气模式类型
********************/
#define BTM_SCO_AIR_MODE_U_LAW          0
#define BTM_SCO_AIR_MODE_A_LAW          1
#define BTM_SCO_AIR_MODE_CVSD           2
#define BTM_SCO_AIR_MODE_TRANSPNT       3
#define BTM_SCO_AIR_MODE_UNKNOWN        0xFF
typedef UINT8 tBTM_SCO_AIR_MODE_TYPE;

/*******************
** SCO语音设置
********************/
#define BTM_VOICE_SETTING_CVSD  ((UINT16)  (HCI_INP_CODING_LINEAR          |   \
                                            HCI_INP_DATA_FMT_2S_COMPLEMENT |   \
                                            HCI_INP_SAMPLE_SIZE_16BIT      |   \
                                            HCI_AIR_CODING_FORMAT_CVSD))

#define BTM_VOICE_SETTING_TRANS ((UINT16)  (HCI_INP_CODING_LINEAR          |   \
                                            HCI_INP_DATA_FMT_2S_COMPLEMENT |   \
                                            HCI_INP_SAMPLE_SIZE_8BIT      |   \
                                            HCI_AIR_CODING_FORMAT_TRANSPNT))

/*******************
** SCO数据状态
********************/
enum {
    BTM_SCO_DATA_CORRECT,
    BTM_SCO_DATA_PAR_ERR,
    BTM_SCO_DATA_NONE,
    BTM_SCO_DATA_PAR_LOST
};
typedef UINT8 tBTM_SCO_DATA_FLAG;

/***************************
**  SCO回调函数
****************************/
typedef void (tBTM_SCO_CB) (UINT16 sco_inx);
typedef void (tBTM_SCO_DATA_CB) (UINT16 sco_inx, BT_HDR *p_data, tBTM_SCO_DATA_FLAG status);

/******************
**  eSCO常量
*******************/
#define BTM_64KBITS_RATE            0x00001f40  /* 64 kbit/s数据速率*/

/* 重新传输努力*/
#define BTM_ESCO_RETRANS_OFF        0
#define BTM_ESCO_RETRANS_POWER      1
#define BTM_ESCO_RETRANS_QUALITY    2
#define BTM_ESCO_RETRANS_DONTCARE   0xff

/* 最大延迟不在乎*/
#define BTM_ESCO_MAX_LAT_DONTCARE   0xffff

/***************
**  eSCO类型
****************/
/* tBTM_ESCO_CBACK事件类型*/
#define BTM_ESCO_CHG_EVT        1
#define BTM_ESCO_CONN_REQ_EVT   2
typedef UINT8 tBTM_ESCO_EVT;

/* 传递到BTM_SetEScoMode（）*/
typedef struct {
    UINT32 tx_bw;
    UINT32 rx_bw;
    UINT16 max_latency;
    UINT16 voice_contfmt;  /* 语音设置或内容格式*/
    UINT16 packet_types;
    UINT8  retrans_effort;
} tBTM_ESCO_PARAMS;

typedef struct {
    UINT16 max_latency;
    UINT16 packet_types;
    UINT8  retrans_effort;
} tBTM_CHG_ESCO_PARAMS;

/* 由BTM_ReadEScoLinkParms（）返回*/
typedef struct {
    UINT16  rx_pkt_len;
    UINT16  tx_pkt_len;
    BD_ADDR bd_addr;
    UINT8   link_type;  /* BTM_LINK_TYPE_SCO或BTM_LINK_TYPE_ESCO*/
    UINT8   tx_interval;
    UINT8   retrans_window;
    UINT8   air_mode;
} tBTM_ESCO_DATA;

typedef struct {
    UINT16  sco_inx;
    UINT16  rx_pkt_len;
    UINT16  tx_pkt_len;
    BD_ADDR bd_addr;
    UINT8   hci_status;
    UINT8   tx_interval;
    UINT8   retrans_window;
} tBTM_CHG_ESCO_EVT_DATA;

typedef struct {
    UINT16        sco_inx;
    BD_ADDR       bd_addr;
    DEV_CLASS     dev_class;
    tBTM_SCO_TYPE link_type;
} tBTM_ESCO_CONN_REQ_EVT_DATA;

typedef union {
    tBTM_CHG_ESCO_EVT_DATA      chg_evt;
    tBTM_ESCO_CONN_REQ_EVT_DATA conn_evt;
} tBTM_ESCO_EVT_DATA;

/***************************
**  eSCO回调函数
****************************/
typedef void (tBTM_ESCO_CBACK) (tBTM_ESCO_EVT event, tBTM_ESCO_EVT_DATA *p_data);


/*****************************************************************************
**  SECURITY MANAGEMENT
*****************************************************************************/
/*******************************
**  Security Manager常量
********************************/

/* 安全模式（BTM_SetSecurityMode）*/
#define BTM_SEC_MODE_UNDEFINED      0
#define BTM_SEC_MODE_NONE           1
#define BTM_SEC_MODE_SERVICE        2
#define BTM_SEC_MODE_LINK           3
#define BTM_SEC_MODE_SP             4
#define BTM_SEC_MODE_SP_DEBUG       5
#define BTM_SEC_MODE_SC             6

/* BTM安全模式的最大数量*/
#define BTM_SEC_MODES_MAX           7

/* 安全服务级别[bit mask]（BTM_SetSecurityLevel）未经身份验证，不应使用加密
*/
#define BTM_SEC_NONE               0x0000 /* 不需要任何内容*/
#define BTM_SEC_IN_AUTHORIZE       0x0001 /* 入站呼叫需要授权*/
#define BTM_SEC_IN_AUTHENTICATE    0x0002 /* 入站呼叫需要身份验证*/
#define BTM_SEC_IN_ENCRYPT         0x0004 /* 入站呼叫需要加密*/
#define BTM_SEC_OUT_AUTHORIZE      0x0008 /* 出站呼叫需要授权*/
#define BTM_SEC_OUT_AUTHENTICATE   0x0010 /* 出站呼叫需要身份验证*/
#define BTM_SEC_OUT_ENCRYPT        0x0020 /* 出站呼叫需要加密*/
#define BTM_SEC_MODE4_LEVEL4       0x0040 /* 仅安全连接模式*/
#define BTM_SEC_FORCE_MASTER       0x0100 /* 需要将连接切换为主连接*/
#define BTM_SEC_ATTEMPT_MASTER     0x0200 /* 尝试将连接切换为主连接*/
#define BTM_SEC_FORCE_SLAVE        0x0400 /* 需要将连接切换为主连接*/
#define BTM_SEC_ATTEMPT_SLAVE      0x0800 /* 尝试将连接切换为从属*/
#define BTM_SEC_IN_MITM            0x1000 /* 入境Do中间人保护*/
#define BTM_SEC_OUT_MITM           0x2000 /* 出站中间人保护*/
#define BTM_SEC_IN_MIN_16_DIGIT_PIN 0x4000 /* 对秒模式2强制至少16位*/

/* 安全标志[位掩码]（BTM_GetSecurityFlags）
*/
#define BTM_SEC_FLAG_AUTHORIZED     0x01
#define BTM_SEC_FLAG_AUTHENTICATED  0x02
#define BTM_SEC_FLAG_ENCRYPTED      0x04
#define BTM_SEC_FLAG_LKEY_KNOWN     0x10
#define BTM_SEC_FLAG_LKEY_AUTHED    0x20

/* PIN类型*/
#define BTM_PIN_TYPE_VARIABLE       HCI_PIN_TYPE_VARIABLE
#define BTM_PIN_TYPE_FIXED          HCI_PIN_TYPE_FIXED

/* 用于生成新链接密钥的链接密钥类型。在链接键通知回调函数中返回
*/
#define BTM_LKEY_TYPE_COMBINATION   HCI_LKEY_TYPE_COMBINATION
#define BTM_LKEY_TYPE_LOCAL_UNIT    HCI_LKEY_TYPE_LOCAL_UNIT
#define BTM_LKEY_TYPE_REMOTE_UNIT   HCI_LKEY_TYPE_REMOTE_UNIT
#define BTM_LKEY_TYPE_DEBUG_COMB    HCI_LKEY_TYPE_DEBUG_COMB
#define BTM_LKEY_TYPE_UNAUTH_COMB   HCI_LKEY_TYPE_UNAUTH_COMB
#define BTM_LKEY_TYPE_AUTH_COMB     HCI_LKEY_TYPE_AUTH_COMB
#define BTM_LKEY_TYPE_CHANGED_COMB  HCI_LKEY_TYPE_CHANGED_COMB

#define BTM_LKEY_TYPE_UNAUTH_COMB_P_256 HCI_LKEY_TYPE_UNAUTH_COMB_P_256
#define BTM_LKEY_TYPE_AUTH_COMB_P_256   HCI_LKEY_TYPE_AUTH_COMB_P_256

#define BTM_LTK_DERIVED_LKEY_OFFSET 0x20    /* LTK衍生的LK“简单”要求*/
#define BTM_LKEY_TYPE_IGNORE        0xff    /* 当事件是来自hci返回链接键请求的响应时使用*/

typedef UINT8 tBTM_LINK_KEY_TYPE;

/* 协议级安全性（BTM_SetSecurityLevel）*/
#define BTM_SEC_PROTO_L2CAP         0
#define BTM_SEC_PROTO_SDP           1
#define BTM_SEC_PROTO_TCS           2
#define BTM_SEC_PROTO_RFCOMM        3
#define BTM_SEC_PROTO_OBEX          4
#define BTM_SEC_PROTO_BNEP          5
#define BTM_SEC_PROTO_HID           6   /* HID      */
#define BTM_SEC_PROTO_AVDT          7
#define BTM_SEC_PROTO_MCA           8

/* 确定安全服务所需的UINT32的数量*/
#define BTM_SEC_ARRAY_BITS          32          /* 每个数组元素中的位数*/
#define BTM_SEC_SERVICE_ARRAY_SIZE  (((UINT32)BTM_SEC_MAX_SERVICES / BTM_SEC_ARRAY_BITS) + \
                                    (((UINT32)BTM_SEC_MAX_SERVICES % BTM_SEC_ARRAY_BITS) ? 1 : 0))

/* 用于授权API的安全服务定义（BTM_SetSecurityLevel）
*/
#define BTM_SEC_SERVICE_SDP_SERVER      0
#define BTM_SEC_SERVICE_SERIAL_PORT     1
#define BTM_SEC_SERVICE_LAN_ACCESS      2
#define BTM_SEC_SERVICE_DUN             3
#define BTM_SEC_SERVICE_IRMC_SYNC       4
#define BTM_SEC_SERVICE_IRMC_SYNC_CMD   5
#define BTM_SEC_SERVICE_OBEX            6
#define BTM_SEC_SERVICE_OBEX_FTP        7
#define BTM_SEC_SERVICE_HEADSET         8
#define BTM_SEC_SERVICE_CORDLESS        9
#define BTM_SEC_SERVICE_INTERCOM        10
#define BTM_SEC_SERVICE_FAX             11
#define BTM_SEC_SERVICE_HEADSET_AG      12
#define BTM_SEC_SERVICE_PNP_INFO        13
#define BTM_SEC_SERVICE_GEN_NET         14
#define BTM_SEC_SERVICE_GEN_FILE        15
#define BTM_SEC_SERVICE_GEN_AUDIO       16
#define BTM_SEC_SERVICE_GEN_TEL         17
#define BTM_SEC_SERVICE_CTP_DATA        18
#define BTM_SEC_SERVICE_HCRP_CTRL       19
#define BTM_SEC_SERVICE_HCRP_DATA       20
#define BTM_SEC_SERVICE_HCRP_NOTIF      21
#define BTM_SEC_SERVICE_BPP_JOB         22
#define BTM_SEC_SERVICE_BPP_STATUS      23
#define BTM_SEC_SERVICE_BPP_REF         24
#define BTM_SEC_SERVICE_BNEP_PANU       25
#define BTM_SEC_SERVICE_BNEP_GN         26
#define BTM_SEC_SERVICE_BNEP_NAP        27
#define BTM_SEC_SERVICE_HF_HANDSFREE    28
#define BTM_SEC_SERVICE_AG_HANDSFREE    29
#define BTM_SEC_SERVICE_TE_PHONE_ACCESS 30
#define BTM_SEC_SERVICE_ME_PHONE_ACCESS 31

#define BTM_SEC_SERVICE_HIDH_SEC_CTRL   32
#define BTM_SEC_SERVICE_HIDH_NOSEC_CTRL 33
#define BTM_SEC_SERVICE_HIDH_INTR       34
#define BTM_SEC_SERVICE_BIP             35
#define BTM_SEC_SERVICE_BIP_REF         36
#define BTM_SEC_SERVICE_AVDTP           37
#define BTM_SEC_SERVICE_AVDTP_NOSEC     38
#define BTM_SEC_SERVICE_AVCTP           39
#define BTM_SEC_SERVICE_SAP             40
#define BTM_SEC_SERVICE_PBAP            41
#define BTM_SEC_SERVICE_RFC_MUX         42
#define BTM_SEC_SERVICE_AVCTP_BROWSE    43
#define BTM_SEC_SERVICE_MAP             44
#define BTM_SEC_SERVICE_MAP_NOTIF       45
#define BTM_SEC_SERVICE_MCAP_CTRL       46
#define BTM_SEC_SERVICE_MCAP_DATA       47
#define BTM_SEC_SERVICE_HDP_SNK         48
#define BTM_SEC_SERVICE_HDP_SRC         49
#define BTM_SEC_SERVICE_ATT             50
#define BTM_SEC_SERVICE_HIDD_SEC_CTRL   51
#define BTM_SEC_SERVICE_HIDD_NOSEC_CTRL 52
#define BTM_SEC_SERVICE_HIDD_INTR       53

/* 在添加服务时更新这些*/
#define BTM_SEC_SERVICE_FIRST_EMPTY     54

#ifndef BTM_SEC_MAX_SERVICES
#define BTM_SEC_MAX_SERVICES            65
#endif

/************************************************************************************************
** 安全服务MACROS处理32个以上可信服务的UINT32位数组
*************************************************************************************************/
/* MACRO设置位流中的安全服务位掩码*/
#define BTM_SEC_SET_SERVICE(p, service)  (((UINT32 *)(p))[(((UINT32)(service)) / BTM_SEC_ARRAY_BITS)] |=  \
                                    ((UINT32)1 << (((UINT32)(service)) % BTM_SEC_ARRAY_BITS)))


/* MACRO清除位流中的安全服务位掩码*/
#define BTM_SEC_CLR_SERVICE(p, service)  (((UINT32 *)(p))[(((UINT32)(service)) / BTM_SEC_ARRAY_BITS)] &=  \
                                    ~((UINT32)1 << (((UINT32)(service)) % BTM_SEC_ARRAY_BITS)))

/* MACRO检查位流中的安全服务位掩码（返回TRUE或FALSE）*/
#define BTM_SEC_IS_SERVICE_TRUSTED(p, service)    (((((UINT32 *)(p))[(((UINT32)(service)) / BTM_SEC_ARRAY_BITS)]) &   \
                                        (UINT32)(((UINT32)1 << (((UINT32)(service)) % BTM_SEC_ARRAY_BITS)))) ? TRUE : FALSE)

/* MACRO复制两个受信任的设备位掩码*/
#define BTM_SEC_COPY_TRUSTED_DEVICE(p_src, p_dst)   {UINT32 trst; for (trst = 0; trst < BTM_SEC_SERVICE_ARRAY_SIZE; trst++) \
                                                        ((UINT32 *)(p_dst))[trst] = ((UINT32 *)(p_src))[trst];}

/* MACRO清除两个受信任的设备位掩码*/
#define BTM_SEC_CLR_TRUSTED_DEVICE(p_dst)   {UINT32 trst; for (trst = 0; trst < BTM_SEC_SERVICE_ARRAY_SIZE; trst++) \
                                                        ((UINT32 *)(p_dst))[trst] = 0;}

/* 主机可以在trusted_mask数组中提供以下位*/
/* 0..31位掩码[0]（最低有效字）*/
#define BTM_SEC_TRUST_SDP_SERVER        (1 << BTM_SEC_SERVICE_SDP_SERVER)
#define BTM_SEC_TRUST_SERIAL_PORT       (1 << BTM_SEC_SERVICE_SERIAL_PORT)
#define BTM_SEC_TRUST_LAN_ACCESS        (1 << BTM_SEC_SERVICE_LAN_ACCESS)
#define BTM_SEC_TRUST_DUN               (1 << BTM_SEC_SERVICE_DUN)
#define BTM_SEC_TRUST_IRMC_SYNC         (1 << BTM_SEC_SERVICE_IRMC_SYNC)
#define BTM_SEC_TRUST_IRMC_SYNC_CMD     (1 << BTM_SEC_SERVICE_IRMC_SYNC_CMD)
#define BTM_SEC_TRUST_OBEX              (1 << BTM_SEC_SERVICE_OBEX)
#define BTM_SEC_TRUST_OBEX_FTP          (1 << BTM_SEC_SERVICE_OBEX_FTP)
#define BTM_SEC_TRUST_HEADSET           (1 << BTM_SEC_SERVICE_HEADSET)
#define BTM_SEC_TRUST_CORDLESS          (1 << BTM_SEC_SERVICE_CORDLESS)
#define BTM_SEC_TRUST_INTERCOM          (1 << BTM_SEC_SERVICE_INTERCOM)
#define BTM_SEC_TRUST_FAX               (1 << BTM_SEC_SERVICE_FAX)
#define BTM_SEC_TRUST_HEADSET_AG        (1 << BTM_SEC_SERVICE_HEADSET_AG)
#define BTM_SEC_TRUST_PNP_INFO          (1 << BTM_SEC_SERVICE_PNP_INFO)
#define BTM_SEC_TRUST_GEN_NET           (1 << BTM_SEC_SERVICE_GEN_NET)
#define BTM_SEC_TRUST_GEN_FILE          (1 << BTM_SEC_SERVICE_GEN_FILE)
#define BTM_SEC_TRUST_GEN_AUDIO         (1 << BTM_SEC_SERVICE_GEN_AUDIO)
#define BTM_SEC_TRUST_GEN_TEL           (1 << BTM_SEC_SERVICE_GEN_TEL)
#define BTM_SEC_TRUST_CTP_DATA          (1 << BTM_SEC_SERVICE_CTP_DATA)
#define BTM_SEC_TRUST_HCRP_CTRL         (1 << BTM_SEC_SERVICE_HCRP_CTRL)
#define BTM_SEC_TRUST_HCRP_DATA         (1 << BTM_SEC_SERVICE_HCRP_DATA)
#define BTM_SEC_TRUST_HCRP_NOTIF        (1 << BTM_SEC_SERVICE_HCRP_NOTIF)
#define BTM_SEC_TRUST_BPP_JOB           (1 << BTM_SEC_SERVICE_JOB)
#define BTM_SEC_TRUST_BPP_STATUS        (1 << BTM_SEC_SERVICE_STATUS)
#define BTM_SEC_TRUST_BPP_REF           (1 << BTM_SEC_SERVICE_REF)
#define BTM_SEC_TRUST_BNEP_PANU         (1 << BTM_SEC_SERVICE_BNEP_PANU)
#define BTM_SEC_TRUST_BNEP_GN           (1 << BTM_SEC_SERVICE_BNEP_GN)
#define BTM_SEC_TRUST_BNEP_NAP          (1 << BTM_SEC_SERVICE_BNEP_NAP)
#define BTM_SEC_TRUST_HFP_HF            (1 << BTM_SEC_SERVICE_HF_HANDSFREE)
#define BTM_SEC_TRUST_HFP_AG            (1 << BTM_SEC_SERVICE_AG_HANDSFREE)
#define BTM_SEC_TRUST_TE_PHONE_ACCESS   (1 << BTM_SEC_SERVICE_TE_PHONE_ACCESS)
#define BTM_SEC_TRUST_ME_PHONE_ACCESS   (1 << BTM_SEC_SERVICE_ME_PHONE_ACCESS)

/* 0..31位掩码[1]（最高有效字）*/
#define BTM_SEC_TRUST_HIDH_CTRL         (1 << (BTM_SEC_SERVICE_HIDH_SEC_CTRL - 32))
#define BTM_SEC_TRUST_HIDH_NOSEC_CTRL   (1 << (BTM_SEC_SERVICE_HIDH_NOSEC_CTRL - 32))
#define BTM_SEC_TRUST_HIDH_INTR         (1 << (BTM_SEC_SERVICE_HIDH_INTR - 32))
#define BTM_SEC_TRUST_BIP               (1 << (BTM_SEC_SERVICE_BIP - 32))
#define BTM_SEC_TRUST_BIP_REF           (1 << (BTM_SEC_SERVICE_BIP_REF - 32))
#define BTM_SEC_TRUST_AVDTP             (1 << (BTM_SEC_SERVICE_AVDTP - 32))
#define BTM_SEC_TRUST_AVDTP_NOSEC       (1 << (BTM_SEC_SERVICE_AVDTP_NOSEC - 32))
#define BTM_SEC_TRUST_AVCTP             (1 << (BTM_SEC_SERVICE_AVCTP - 32))
#define BTM_SEC_TRUST_SAP               (1 << (BTM_SEC_SERVICE_SAP - 32))
#define BTM_SEC_TRUST_PBAP              (1 << (BTM_SEC_SERVICE_PBAP - 32))
#define BTM_SEC_TRUST_RFC_MUX           (1 << (BTM_SEC_SERVICE_RFC_MUX - 32))
#define BTM_SEC_TRUST_AVCTP_BROWSE      (1 << (BTM_SEC_SERVICE_AVCTP_BROWSE - 32))
#define BTM_SEC_TRUST_MAP               (1 << (BTM_SEC_SERVICE_MAP - 32))
#define BTM_SEC_TRUST_MAP_NOTIF         (1 << (BTM_SEC_SERVICE_MAP_NOTIF - 32))
#define BTM_SEC_TRUST_MCAP_CTRL         (1 << (BTM_SEC_SERVICE_MCAP_CTRL - 32))
#define BTM_SEC_TRUST_MCAP_DATA         (1 << (BTM_SEC_SERVICE_MCAP_DATA - 32))
#define BTM_SEC_TRUST_HDP_SNK           (1 << (BTM_SEC_SERVICE_HDP_SNK - 32))
#define BTM_SEC_TRUST_HDP_SRC           (1 << (BTM_SEC_SERVICE_HDP_SRC - 32))

#define BTM_SEC_TRUST_ALL               0xFFFFFFFF  /* 对于每个数组元素*/

/****************************************
**  Security Manager回调函数
*****************************************/
/* 授权设备进行服务。参数是远程设备的BD地址远程BD的类别远程服务名称服务Id的名称（NULL-未知服务或未使用[BTM_Service_Name_LEN设置为0]）是连接的发起者操作的结果
*/
typedef UINT8 (tBTM_AUTHORIZE_CALLBACK) (BD_ADDR bd_addr, DEV_CLASS dev_class,
        tBTM_BD_NAME bd_name, UINT8 *service_name,
        UINT8 service_id, BOOLEAN is_originator);

/* 获取连接的PIN。参数为远程设备的BD地址远程BD的类别远程标志的名称，指示最小引脚代码长度为16位
*/
typedef UINT8 (tBTM_PIN_CALLBACK) (BD_ADDR bd_addr, DEV_CLASS dev_class,
                                   tBTM_BD_NAME bd_name, BOOLEAN min_16_digit);

/* 连接的新链接密钥。参数为远程链接密钥类型的BD地址：组合、本地单元或远程单元
*/
typedef UINT8 (tBTM_LINK_KEY_CALLBACK) (BD_ADDR bd_addr, DEV_CLASS dev_class,
                                        tBTM_BD_NAME bd_name, UINT8 *key,
                                        UINT8 key_type, BOOLEAN sc_support);


/* 已解析远程名称。参数为BD远程地址BD远程名称
*/
typedef void (tBTM_RMT_NAME_CALLBACK) (BD_ADDR bd_addr, DEV_CLASS dc,
                                       tBTM_BD_NAME bd_name);


/* 连接的身份验证完成。参数为远程设备的BD地址远程设备的类别远程设备的名称
**
*/
typedef UINT8 (tBTM_AUTH_COMPLETE_CALLBACK) (BD_ADDR bd_addr, DEV_CLASS dev_class,
        tBTM_BD_NAME bd_name, int result);

enum {
    BTM_SP_IO_REQ_EVT,      /* 收到IO_CAPABILITY_REQUEST事件*/
    BTM_SP_IO_RSP_EVT,      /* 收到IO_CAPABILITY_RESPONSE事件*/
    BTM_SP_CFM_REQ_EVT,     /* 收到USER_CONFIRMATION_REQUEST事件*/
    BTM_SP_KEY_NOTIF_EVT,   /* 收到USER_PASSKEY_NOTIFY事件*/
    BTM_SP_KEY_REQ_EVT,     /* 收到USER_PASSKEY_REQUEST事件*/
    BTM_SP_KEYPRESS_EVT,    /* 收到KEYPRESS_NOTIFY事件*/
    BTM_SP_LOC_OOB_EVT,     /* 收到READ_LOCAL_OOB_DATA命令的结果*/
    BTM_SP_RMT_OOB_EVT,     /* 收到REMOTE_OOB_DATA_REQUEST事件*/
    BTM_SP_COMPLT_EVT,      /* 收到SIMPLE_PAIRING_COMPLETE事件*/
    BTM_SP_UPGRADE_EVT      /* 检查应用程序是否要升级链接密钥*/
};
typedef UINT8 tBTM_SP_EVT;

/* 与ESP_gap_ble_api.h中的ESP_IO_CAP_xxx相关*/
#define BTM_IO_CAP_OUT      0   /* 仅显示*/
#define BTM_IO_CAP_IO       1   /* 显示是否*/
#define BTM_IO_CAP_IN       2   /* 仅键盘*/
#define BTM_IO_CAP_NONE     3   /* 无输入无输出*/
// #如果BLE_INCLUDE==真和SMP_INCLUDD==真
#define BTM_IO_CAP_KBDISP   4   /* 键盘显示器*/
#define BTM_IO_CAP_MAX      5
// #其他
// #定义BTM_IO_CAP_MAX 4
// #结束符

typedef UINT8 tBTM_IO_CAP;

#define BTM_MAX_PASSKEY_VAL (999999)
#define BTM_MIN_PASSKEY_VAL (0)

#define BTM_AUTH_SP_NO      0   /* 不需要MITM保护-单剖面/无粘结数字比较，允许自动接受*/
#define BTM_AUTH_SP_YES     1   /* 需要MITM保护-单配置文件/非绑定使用IO功能来确定身份验证过程*/
#define BTM_AUTH_AP_NO      2   /* 不需要MITM保护-所有配置文件/专用键合数字比较，允许自动接受*/
#define BTM_AUTH_AP_YES     3   /* 需要MITM保护-所有配置文件/专用绑定使用IO功能来确定身份验证程序*/
#define BTM_AUTH_SPGB_NO    4   /* 不需要MITM保护-单个配置文件/通用键合数字比较，允许自动接受*/
#define BTM_AUTH_SPGB_YES   5   /* 需要MITM保护-单一配置文件/通用绑定使用IO功能确定身份验证程序*/
#define BTM_AUTH_DD_BOND    2   /* 当IO交换为专用绑定时，该位与BTM_AUTH_SP_*进行“或”运算*/
#define BTM_AUTH_GB_BIT     4   /* 通用粘结钻头*/
#define BTM_AUTH_BONDS      6   /* 通用/专用粘结钻头*/
#define BTM_AUTH_YN_BIT     1   /* 这是“是”或“否”位*/

#define BTM_BLE_ENC_KEY_MASK    (1 << 0)
#define BTM_BLE_ID_KEY_MASK     (1 << 1)
#define BTM_BLE_CSR_KEY_MASK    (1 << 2)
#define BTM_BLE_LINK_KEY_MASK   (1 << 3)

#define BTM_BLE_INITIATOR_KEY_SIZE 15
#define BTM_BLE_RESPONDER_KEY_SIZE 15
#define BTM_BLE_MAX_KEY_SIZE       16
#define BTM_BLE_MIN_KEY_SIZE       7
#define BTM_BLE_APPL_ENC_KEY_SIZE  7

typedef UINT8 tBTM_AUTH_REQ;

enum {
    BTM_OOB_NONE,
    BTM_OOB_PRESENT
#if BTM_OOB_INCLUDED == TRUE
    , BTM_OOB_UNKNOWN
#endif
};
typedef UINT8 tBTM_OOB_DATA;

/* BTM_SP_IO_REQ_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    tBTM_IO_CAP     io_cap;         /* 本地IO能力*/
    tBTM_OOB_DATA   oob_data;       /* 对等设备存在OOB数据（本地）*/
    tBTM_AUTH_REQ   auth_req;       /* 需要身份验证（对于本地设备）*/
    BOOLEAN         is_orig;        /* TRUE，如果本地设备启动了SP进程*/
} tBTM_SP_IO_REQ;

/* BTM_SP_IO_RSP_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    tBTM_IO_CAP     io_cap;         /* 对等IO能力*/
    tBTM_OOB_DATA   oob_data;       /* 本地设备的对等设备上存在OOB数据*/
    tBTM_AUTH_REQ   auth_req;       /* 对等设备需要身份验证*/
} tBTM_SP_IO_RSP;

/* BTM_SP_CFM_REQ_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    tBTM_BD_NAME    bd_name;        /* 对等设备名称*/
    UINT32          num_val;        /* 用于比较的数值。如果just_works，则不向UI显示此数字*/
    BOOLEAN         just_works;     /* TRUE，如果“Just Works”关联模型*/
    tBTM_AUTH_REQ   loc_auth_req;   /* 本地设备需要身份验证*/
    tBTM_AUTH_REQ   rmt_auth_req;   /* 对等设备需要身份验证*/
    tBTM_IO_CAP     loc_io_caps;    /* 本地设备的IO功能*/
    tBTM_IO_CAP     rmt_io_caps;    /* 远程设备的IO功能*/
} tBTM_SP_CFM_REQ;

/* BTM_SP_KEY_REQ_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    tBTM_BD_NAME    bd_name;        /* 对等设备名称*/
} tBTM_SP_KEY_REQ;

/* BTM_SP_KEY_NOTIF_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    tBTM_BD_NAME    bd_name;        /* 对等设备名称*/
    UINT32          passkey;        /* 密钥*/
} tBTM_SP_KEY_NOTIF;

enum {
    BTM_SP_KEY_STARTED,         /* 0-密钥输入已启动*/
    BTM_SP_KEY_ENTERED,         /* 1-输入密钥数字*/
    BTM_SP_KEY_ERASED,          /* 2-密钥数字已擦除*/
    BTM_SP_KEY_CLEARED,         /* 3-密钥已清除*/
    BTM_SP_KEY_COMPLT,          /* 4-密钥输入完成*/
    BTM_SP_KEY_OUT_OF_RANGE     /* 5-超出范围*/
};
typedef UINT8   tBTM_SP_KEY_TYPE;

/* BTM_SP_KEYPRESS_EVT的数据类型*/
typedef struct {
    BD_ADDR             bd_addr;        /* 对等地址*/
    tBTM_SP_KEY_TYPE   notif_type;
} tBTM_SP_KEYPRESS;

/* BTM_SP_LOC_OOB_EVT的数据类型*/
typedef struct {
    tBTM_STATUS     status;         /* */
    BT_OCTET16      c;              /* 简单配对哈希C*/
    BT_OCTET16      r;              /* 简单配对随机数器R*/
} tBTM_SP_LOC_OOB;

/* BTM_SP_RMT_OOB_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    tBTM_BD_NAME    bd_name;        /* 对等设备名称*/
} tBTM_SP_RMT_OOB;


/* BTM_SP_COMPLT_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    DEV_CLASS       dev_class;      /* 对等CoD*/
    tBTM_BD_NAME    bd_name;        /* 对等设备名称*/
    tBTM_STATUS     status;         /* 简单配对过程的状态*/
} tBTM_SP_COMPLT;

/* BTM_SP_UPGRADE_EVT的数据类型*/
typedef struct {
    BD_ADDR         bd_addr;        /* 对等地址*/
    BOOLEAN         upgrade;        /* TRUE，升级链接密钥*/
} tBTM_SP_UPGRADE;

typedef union {
    tBTM_SP_IO_REQ      io_req;     /* BTM_SP_IO_REQ_EVT      */
    tBTM_SP_IO_RSP      io_rsp;     /* BTM_SP_IO_RSP_EVT      */
    tBTM_SP_CFM_REQ     cfm_req;    /* BTM_SP_CFM_REQ_EVT     */
    tBTM_SP_KEY_NOTIF   key_notif;  /* BTM_SP_KEY_NOTIF_EVT   */
    tBTM_SP_KEY_REQ     key_req;    /* BTM_SP_KEY_REQ_EVT     */
    tBTM_SP_KEYPRESS    key_press;  /* BTM_SP_KEYPRESS_EVT    */
    tBTM_SP_LOC_OOB     loc_oob;    /* BTM_SP_LOC_OOB_EVT     */
    tBTM_SP_RMT_OOB     rmt_oob;    /* BTM_SP_RMT_OOB_EVT     */
    tBTM_SP_COMPLT      complt;     /* BTM_SP_COMPLT_EVT      */
    tBTM_SP_UPGRADE     upgrade;    /* BTM_SP_UPGRADE_EVT      */
} tBTM_SP_EVT_DATA;

/* 简单配对事件。当发生简单配对相关事件时由堆栈调用。
*/
typedef UINT8 (tBTM_SP_CALLBACK) (tBTM_SP_EVT event, tBTM_SP_EVT_DATA *p_data);


typedef void (tBTM_MKEY_CALLBACK) (BD_ADDR bd_addr, UINT8 status, UINT8 key_flag) ;

/* 加密启用/禁用完成：可选通过BTM_SetEncryption。参数是BTM_SetEncryption tBTM_STATUS-操作结果传入的远程可选数据的BD地址
*/
typedef void (tBTM_SEC_CBACK) (BD_ADDR bd_addr, tBT_TRANSPORT transport,
                               void *p_ref_data, tBTM_STATUS result);

/* 债券取消完成。参数是取消操作的结果
**
*/
typedef void (tBTM_BOND_CANCEL_CMPL_CALLBACK) (tBTM_STATUS result);

/* LE相关事件和数据结构
*/
/* 与ESP_gap_ble_api中的ESP_LE_KEY_xxx相关。小时*/
#if (SMP_INCLUDED == TRUE)
#define BTM_LE_IO_REQ_EVT       SMP_IO_CAP_REQ_EVT     /* 收到IO_CAPABILITY_REQUEST事件*/
#define BTM_LE_SEC_REQUEST_EVT  SMP_SEC_REQUEST_EVT    /* 安全请求事件*/
#define BTM_LE_KEY_NOTIF_EVT    SMP_PASSKEY_NOTIF_EVT  /* 收到USER_PASSKEY_NOTIFY事件*/
#define BTM_LE_KEY_REQ_EVT      SMP_PASSKEY_REQ_EVT    /* 收到USER_PASSKEY_REQUEST事件*/
#define BTM_LE_OOB_REQ_EVT      SMP_OOB_REQ_EVT        /* OOB数据请求事件*/
#define BTM_LE_NC_REQ_EVT       SMP_NC_REQ_EVT          /* 数字比较请求事件*/
#define BTM_LE_PR_KEYPR_NOT_EVT SMP_PEER_KEYPR_NOT_EVT /* 对等按键通知记录事件*/
/* SC OOB请求事件（本地和对等OOB数据）可以作为响应*/
#define BTM_LE_SC_OOB_REQ_EVT   SMP_SC_OOB_REQ_EVT
/* 创建SC OOB本地数据集（作为SMP_CrLocScOobData（…）的结果）*/
#define BTM_LE_SC_LOC_OOB_EVT   SMP_SC_LOC_OOB_DATA_UP_EVT
#define BTM_LE_BR_KEYS_REQ_EVT  SMP_BR_KEYS_REQ_EVT     /* SMP over BR密钥请求事件*/
#define BTM_LE_COMPLT_EVT       SMP_COMPLT_EVT         /* SMP完成事件*/
#define BTM_LE_LAST_FROM_SMP    BTM_LE_BR_KEYS_REQ_EVT
#define BTM_LE_KEY_EVT          BTM_LE_LAST_FROM_SMP + 1 /* KEY更新事件*/
#endif  ///SMP_INCLUDED == TRUE
typedef UINT8 tBTM_LE_EVT;

#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
#define BTM_LE_KEY_NONE           0
#define BTM_LE_KEY_PENC      SMP_SEC_KEY_TYPE_ENC        /* 对等设备的加密信息*/
#define BTM_LE_KEY_PID       SMP_SEC_KEY_TYPE_ID         /* 对等设备的身份密钥*/
#define BTM_LE_KEY_PCSRK     SMP_SEC_KEY_TYPE_CSRK      /* 对等SRK*/
#define BTM_LE_KEY_PLK       SMP_SEC_KEY_TYPE_LK
#define BTM_LE_KEY_LLK       (SMP_SEC_KEY_TYPE_LK << 4)
#define BTM_LE_KEY_LENC      (SMP_SEC_KEY_TYPE_ENC << 4)  /* 主角色安全信息：div*/
#define BTM_LE_KEY_LID       (SMP_SEC_KEY_TYPE_ID << 4)   /* 主设备ID密钥*/
#define BTM_LE_KEY_LCSRK     (SMP_SEC_KEY_TYPE_CSRK << 4) /* 本地CSRK已交付给同行*/
#endif  ///BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
typedef UINT8 tBTM_LE_KEY_TYPE;

/* 与ESP_gap_ble_api中的ESP_LE_AUTH_xxx相关。小时*/
#if (SMP_INCLUDED == TRUE)
#define BTM_LE_AUTH_REQ_NO_BOND SMP_AUTH_NO_BOND   /* 0 */
#define BTM_LE_AUTH_REQ_BOND    SMP_AUTH_GEN_BOND  /* 1 << 0 */
#define BTM_LE_AUTH_REQ_MITM    SMP_AUTH_YN_BIT    /* 1 << 2 */
#endif  ///SMP_INCLUDED == TRUE
typedef UINT8 tBTM_LE_AUTH_REQ;
#if (SMP_INCLUDED == TRUE)
#define BTM_LE_SC_SUPPORT_BIT           SMP_SC_SUPPORT_BIT     /* (1 << 3) */
#define BTM_LE_KP_SUPPORT_BIT           SMP_KP_SUPPORT_BIT     /* (1 << 4) */

#define BTM_LE_AUTH_REQ_SC_ONLY         SMP_AUTH_SC_ENC_ONLY    /* 1 << 3 */
#define BTM_LE_AUTH_REQ_SC_BOND         SMP_AUTH_SC_GB          /* 1001 */
#define BTM_LE_AUTH_REQ_SC_MITM         SMP_AUTH_SC_MITM_NB     /* 1100 */
#define BTM_LE_AUTH_REQ_SC_MITM_BOND    SMP_AUTH_SC_MITM_GB     /* 1101 */
#define BTM_LE_AUTH_REQ_MASK            SMP_AUTH_MASK           /* 0x1D像素*/

/* LE安全级别*/
#define BTM_LE_SEC_NONE             SMP_SEC_NONE
#define BTM_LE_SEC_UNAUTHENTICATE   SMP_SEC_UNAUTHENTICATE      /* 1 */
#define BTM_LE_SEC_AUTHENTICATED    SMP_SEC_AUTHENTICATED       /* 4 */
#endif  ///SMP_INCLUDED == TRUE
typedef UINT8 tBTM_LE_SEC;


typedef struct {
    tBTM_IO_CAP         io_cap;         /* 本地IO能力*/
    UINT8               oob_data;       /* 对等设备存在OOB数据（本地）*/
    tBTM_LE_AUTH_REQ    auth_req;       /* 身份验证请求（针对本地设备）包含绑定和MITM信息*/
    UINT8               max_key_size;   /* 最大加密密钥大小*/
    tBTM_LE_KEY_TYPE    init_keys;      /* 要分发的密钥，位掩码*/
    tBTM_LE_KEY_TYPE    resp_keys;      /* 要分发的密钥，位掩码*/
} tBTM_LE_IO_REQ;

#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
/* tBTM_LE_COMPLT的数据类型*/
typedef struct {
    UINT8 reason;
    UINT8 sec_level;
    BOOLEAN is_pair_cancel;
    BOOLEAN smp_over_br;
    tSMP_AUTH_REQ auth_mode;
} tBTM_LE_COMPLT;
#endif

/* BLE加密密钥*/
typedef struct {
    BT_OCTET16  ltk;
    BT_OCTET8   rand;
    UINT16      ediv;
    UINT8       sec_level;
    UINT8       key_size;
} tBTM_LE_PENC_KEYS;

/* BLE CSRK键*/
typedef struct {
    UINT32          counter;
    BT_OCTET16      csrk;
    UINT8           sec_level;
} tBTM_LE_PCSRK_KEYS;

/* BLE加密再现密钥*/
typedef struct {
    BT_OCTET16  ltk;
    UINT16      div;
    UINT8       key_size;
    UINT8       sec_level;
} tBTM_LE_LENC_KEYS;

/* BLE SRK键*/
typedef struct {
    UINT32          counter;
    UINT16          div;
    UINT8           sec_level;
    BT_OCTET16      csrk;
} tBTM_LE_LCSRK_KEYS;

typedef struct {
    BT_OCTET16          irk;
    tBLE_ADDR_TYPE      addr_type;
    BD_ADDR             static_addr;
} tBTM_LE_PID_KEYS;

typedef union {
    tBTM_LE_PENC_KEYS   penc_key;       /* 收到的对等加密密钥*/
    tBTM_LE_PCSRK_KEYS  pcsrk_key;      /* 接收的对等设备SRK*/
    tBTM_LE_PID_KEYS    pid_key;        /* 对等设备ID密钥*/
    tBTM_LE_LENC_KEYS   lenc_key;       /* 本地加密再现密钥LTK==d1（ER，DIV，0）*/
    tBTM_LE_LCSRK_KEYS   lcsrk_key;     /* 本地设备CSRK=d1（ER，DIV，1）*/
} tBTM_LE_KEY_VALUE;

typedef struct {
    tBTM_LE_KEY_TYPE        key_type;
    tBTM_LE_KEY_VALUE       *p_key_value;
} tBTM_LE_KEY;

typedef union {
    tBTM_LE_IO_REQ      io_req;     /* BTM_LE_IO_REQ_EVT      */
    UINT32              key_notif;  /* BTM_LE_KEY_NOTIF_EVT   */
    /* BTM_LE_NC_REQ_EVT */
    /* BTM_LE_KEY_REQ_EVT没有回调数据*/
    /* 和BTM_LE_OOB_REQ_EVT*/
#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    tBTM_LE_COMPLT      complt;     /* BTM_LE_COMPLT_EVT      */
    tSMP_OOB_DATA_TYPE  req_oob_type;
#endif
    tBTM_LE_KEY         key;
} tBTM_LE_EVT_DATA;

/* 简单配对事件。当发生简单配对相关事件时由堆栈调用。
*/
typedef UINT8 (tBTM_LE_CALLBACK) (tBTM_LE_EVT event, BD_ADDR bda, tBTM_LE_EVT_DATA *p_data);

#define BTM_BLE_KEY_TYPE_ID         1
#define BTM_BLE_KEY_TYPE_ER         2
#define BTM_BLE_KEY_TYPE_COUNTER    3  //被淘汰

typedef struct {
    BT_OCTET16       ir;
    BT_OCTET16       irk;
    BT_OCTET16       dhk;

} tBTM_BLE_LOCAL_ID_KEYS;

typedef union {
    tBTM_BLE_LOCAL_ID_KEYS  id_keys;
    BT_OCTET16              er;
} tBTM_BLE_LOCAL_KEYS;


/* 本地设备的新LE标识密钥。
*/
typedef void (tBTM_LE_KEY_CALLBACK) (UINT8 key_type, tBTM_BLE_LOCAL_KEYS *p_key);


/***************************
**  安全管理器类型
****************************/
/* 应用程序用于向BTM_SecRegister注册的结构*/
typedef struct {
    tBTM_AUTHORIZE_CALLBACK     *p_authorize_callback;
    tBTM_PIN_CALLBACK           *p_pin_callback;
    tBTM_LINK_KEY_CALLBACK      *p_link_key_callback;
    tBTM_AUTH_COMPLETE_CALLBACK *p_auth_complete_callback;
    tBTM_BOND_CANCEL_CMPL_CALLBACK *p_bond_cancel_cmpl_callback;
    tBTM_SP_CALLBACK            *p_sp_callback;
#if BLE_INCLUDED == TRUE
#if SMP_INCLUDED == TRUE
    tBTM_LE_CALLBACK            *p_le_callback;
#endif
    tBTM_LE_KEY_CALLBACK        *p_le_key_callback;
#endif
} tBTM_APPL_INFO;

/* 发生链接监视超时事件时的回调函数。通过调用BTM_RegForLstoEvt（）启用/禁用此异步事件。
*/
typedef void (tBTM_LSTO_CBACK) (BD_ADDR remote_bda, UINT16 timeout);

/*****************************************************************************
**  POWER MANAGEMENT
*****************************************************************************/
/****************************
**  Power Manager常量
*****************************/
/* BTM电源管理器状态代码*/
enum {
    BTM_PM_STS_ACTIVE = HCI_MODE_ACTIVE,
    BTM_PM_STS_HOLD   = HCI_MODE_HOLD,
    BTM_PM_STS_SNIFF  = HCI_MODE_SNIFF,
    BTM_PM_STS_PARK   = HCI_MODE_PARK,
    BTM_PM_STS_SSR,     /* 报告HCI_SNIFF_SUB_RATE_EVT中的SSR参数*/
    BTM_PM_STS_PENDING,   /* 等待控制器的状态时*/
    BTM_PM_STS_ERROR   /* 当HCI命令状态返回错误时*/
};
typedef UINT8 tBTM_PM_STATUS;

/* BTM电源管理器模式*/
enum {
    BTM_PM_MD_ACTIVE = BTM_PM_STS_ACTIVE,
    BTM_PM_MD_HOLD   = BTM_PM_STS_HOLD,
    BTM_PM_MD_SNIFF  = BTM_PM_STS_SNIFF,
    BTM_PM_MD_PARK   = BTM_PM_STS_PARK,
    BTM_PM_MD_FORCE  = 0x10 /* 或者强制ACL链接到特定模式*/
};
typedef UINT8 tBTM_PM_MODE;

#define BTM_PM_SET_ONLY_ID  0x80

/* 操作代码*/
#define BTM_PM_REG_SET      1 /* 模块想要设置所需的电源模式*/
#define BTM_PM_REG_NOTIF    2 /* 模块想要接收模式更改事件*/
#define BTM_PM_DEREG        4 /* 模块不想再涉及PM*/

/************************
**  电源管理器类型
*************************/
typedef struct {
    UINT16          max;
    UINT16          min;
    UINT16          attempt;
    UINT16          timeout;
    tBTM_PM_MODE    mode;
} tBTM_PM_PWR_MD;

/*************************************
**  Power Manager回调函数
**************************************/
typedef void (tBTM_PM_STATUS_CBACK) (BD_ADDR p_bda, tBTM_PM_STATUS status,
                                     UINT16 value, UINT8 hci_status);


/************************
**  存储的链接键类型
*************************/
#define BTM_CB_EVT_DELETE_STORED_LINK_KEYS  4

typedef struct {
    UINT8          event;
    UINT8          status;
    UINT16         num_keys;

} tBTM_DELETE_STORED_LINK_KEY_COMPLETE;

/* MIP evnets，回调*/
enum {
    BTM_MIP_MODE_CHG_EVT,
    BTM_MIP_DISCONNECT_EVT,
    BTM_MIP_PKTS_COMPL_EVT,
    BTM_MIP_RXDATA_EVT
};
typedef UINT8 tBTM_MIP_EVT;

typedef struct {
    tBTM_MIP_EVT    event;
    BD_ADDR         bd_addr;
    UINT16          mip_id;
} tBTM_MIP_MODE_CHANGE;

typedef struct {
    tBTM_MIP_EVT    event;
    UINT16          mip_id;
    UINT8           disc_reason;
} tBTM_MIP_CONN_TIMEOUT;

#define BTM_MIP_MAX_RX_LEN  17

typedef struct {
    tBTM_MIP_EVT    event;
    UINT16          mip_id;
    UINT8           rx_len;
    UINT8           rx_data[BTM_MIP_MAX_RX_LEN];
} tBTM_MIP_RXDATA;

typedef struct {
    tBTM_MIP_EVT    event;
    BD_ADDR         bd_addr;
    UINT8           data[11];       /* 数据[0]显示供应商特定的设备类型*/
} tBTM_MIP_EIR_HANDSHAKE;

typedef struct {
    tBTM_MIP_EVT    event;
    UINT16          num_sent;       /* 在控制器上完成的数据包数*/
} tBTM_MIP_PKTS_COMPL;

typedef union {
    tBTM_MIP_EVT            event;
    tBTM_MIP_MODE_CHANGE    mod_chg;
    tBTM_MIP_CONN_TIMEOUT   conn_tmo;
    tBTM_MIP_EIR_HANDSHAKE  eir;
    tBTM_MIP_PKTS_COMPL     completed;
    tBTM_MIP_RXDATA         rxdata;
} tBTM_MIP_EVENT_DATA;

/* MIP事件回调函数*/
typedef void (tBTM_MIP_EVENTS_CB) (tBTM_MIP_EVT event, tBTM_MIP_EVENT_DATA data);

/* MIP设备查询回调函数*/
typedef BOOLEAN (tBTM_MIP_QUERY_CB) (BD_ADDR dev_addr, UINT8 *p_mode, LINK_KEY link_key);

#define BTM_CONTRL_ACTIVE  1       /* ACL链接打开，SCO链接正在进行，嗅探模式*/
#define BTM_CONTRL_SCAN    2       /* 扫描状态-寻呼/查询/尝试连接*/
#define BTM_CONTRL_IDLE    3       /* 空闲状态-页面扫描、LE advt、查询扫描*/

typedef UINT8 tBTM_CONTRL_STATE;

/*****************************************************************************
**  EXTERNAL FUNCTION DECLARATIONS
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**  设备控制和通用功能
*****************************************************************************/

/*******************************************************************************
** 功能BTM_DeviceReset
**
** 说明调用此函数以重置控制器。当设备启动完成时，调用Callback函数（如果提供）。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_DeviceReset (tBTM_CMPL_CB *p_cb);


/*******************************************************************************
** 函数BTM_IsDeviceUp
**
** 说明调用此函数以检查设备是否启动。
**
** 如果设备启动，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_IsDeviceUp (void);


/*******************************************************************************
** 函数BTM_SetLocalDeviceName
**
** 说明调用此函数以设置本地设备名称。
**
** 如果成功，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetLocalDeviceName (char *p_name);

/*******************************************************************************
** 函数BTM_SetDeviceClass
**
** 说明调用此函数以设置本地设备类
**
** 如果成功，则返回BTM_SUCCESS，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_SetDeviceClass (DEV_CLASS dev_class);


/*******************************************************************************
** 函数BTM_ReadLocalDeviceName
**
** 说明调用此函数以读取本地设备名称。
**
** 返回操作状态如果成功，则返回BTM_success，p_name指向存储的本地设备名称如果BTM不存储本地设备名称，则返回BTM_NO_RESOURCES，p_name设置为NULL
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadLocalDeviceName (char **p_name);

/*******************************************************************************
** 函数BTM_ReadLocalDeviceNameFromController
**
** 说明从控制器获取本地设备名称。不要使用缓存的名称（用于在btm重置完成之前获取芯片id）。
**
** 如果成功，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadLocalDeviceNameFromController (tBTM_CMPL_CB *p_rln_cmpl_cback);

/*******************************************************************************
** 函数BTM_ReadDeviceClass
**
** 描述调用此函数以读取本地设备类
**
** 返回指向设备类的指针
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadDeviceClass (void);


/*******************************************************************************
** 函数BTM_ReadLocalFeatures
**
** 说明调用此函数以读取本地功能
**
** 返回指向本地要素字符串的指针
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadLocalFeatures (void);

/*******************************************************************************
** 函数BTM_RegisterForDeviceStatusNotif
**
** 说明调用此函数以注册设备状态更改通知。
**
** 返回指向上一个调用方的回调函数的指针，如果是首次注册，则返回NULL。
**
*******************************************************************************/
//外部
tBTM_DEV_STATUS_CB *BTM_RegisterForDeviceStatusNotif (tBTM_DEV_STATUS_CB *p_cb);


/*******************************************************************************
** 函数BTM_RegisterForVSEvents
**
** 说明调用此函数以注册/注销特定于供应商的HCI事件。
**
**                  如果is_register=TRUE，则将注册函数；如果is_register=FALSE，则函数将被注销。
**
** 如果成功，则返回BTM_SUCCESS；如果已注册最大回拨次数，则返回BTM_BUSY。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_RegisterForVSEvents (tBTM_VS_EVT_CB *p_cb, BOOLEAN is_register);


/*******************************************************************************
** 函数BTM_VendorSpecificCommand
**
** 说明向控制器发送供应商特定的HCI命令。
**
** 返回发送的BTM_SUCCESS命令。不需要命令完成事件。（命令cmpl回调参数为NULL）BTM_CMD_STARTED命令已发送。正在等待命令cmpl事件。BTM_BUSY命令未发送。正在等待上一个命令的cmd cmpl事件。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_VendorSpecificCommand(UINT16 opcode,
                                      UINT8 param_len,
                                      UINT8 *p_param_buf,
                                      tBTM_VSC_CMPL_CB *p_cb);


/*******************************************************************************
** 函数BTM_AllocateCN
**
** 描述查看服务器通道号，以找到一个用于RFCOMM连接的免费通道。
**
** 返回分配的SCN编号，如果没有，则返回0。
**
*******************************************************************************/
//外部
#if (CLASSIC_BT_INCLUDED == TRUE)
UINT8 BTM_AllocateSCN(void);

// btla特定++
/*******************************************************************************
** 函数BTM_TryAllocateCN
**
** 描述尝试分配固定服务器通道
**
** 如果服务器通道可用，则返回TRUE
**
*******************************************************************************/
//外部
BOOLEAN BTM_TryAllocateSCN(UINT8 scn);
// btla特定--


/*******************************************************************************
** 函数BTM_FreeSCN
**
** 说明释放指定的SCN。
**
** 如果成功，则返回TRUE；如果SCN未使用或无效，则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_FreeSCN(UINT8 scn);
#endif  ///CLASSIC_BT_INCLUDED == TRUE


/*******************************************************************************
** 函数BTM_SetTraceLevel
**
** 说明此功能设置BTM的跟踪级别。如果使用值0xFF调用，它只返回当前跟踪级别。
**
** 返回新的或当前的跟踪级别
**
*******************************************************************************/
//外部
UINT8 BTM_SetTraceLevel (UINT8 new_level);


/*******************************************************************************
** 函数BTM_WritePageTimeout
**
** 说明发送HCI Wite页面超时。
**
** 返回发送的BTM_SUCCESS命令。BTM_NO_RESOURCES如果资源不足，则发送命令。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_WritePageTimeout(UINT16 timeout);

/*******************************************************************************
** 函数BTM_WriteVoiceSettings
**
** 说明发送HCI写入语音设置命令。有关设置位掩码值的信息，请参见stack/hsidefs.h。
**
** 返回发送的BTM_SUCCESS命令。BTM_NO_RESOURCES如果资源不足，则发送命令。
**
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_WriteVoiceSettings(UINT16 settings);

/*******************************************************************************
** 函数BTM_EnableTestMode
**
** 说明在测试命令下向HCI发送启用设备。
**
**                  注：控制器只能通过重置控制器退出此模式。
**
** 返回发送的BTM_SUCCESS命令。BTM_NO_RESOURCES如果资源不足，则发送命令。
**
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_EnableTestMode(void);


/*****************************************************************************
**  设备发现功能-查询、远程名称、发现、设备类别
*****************************************************************************/

/*******************************************************************************
** 函数BTM_SetDiscoveryability
**
** 说明调用此函数可将设备设置为可发现模式或不可发现模式。可发现模式表示已启用查询扫描。如果为窗口或间隔输入值“0”，则使用默认值。
**
** 如果成功BTM_BUSY，则返回BTM_SUCCESS；如果过滤器的设置已在进行中，则返回BTM_NO_RESOURCES；如果无法获取内存池缓冲区BTM_ILLEGAL_VALUE，则如果设备未启动，则返回错误参数BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_SetDiscoverability (UINT16 inq_mode, UINT16 window,
                                     UINT16 interval);


/*******************************************************************************
** 函数BTM_ReadDiscoveryability
**
** 说明调用此函数以读取设备的当前可发现模式。
**
** 输出参数：p_window-当前查询扫描持续时间p_interval-当前查询搜索间隔
**
** 返回BTM_NON_DISCOVERABLE、BTM_LIMITED_DISCOVERABLE或BTM_GENERAL_DISCOVERABLE
**
*******************************************************************************/
//外部
UINT16       BTM_ReadDiscoverability (UINT16 *p_window,
                                      UINT16 *p_interval);


/*******************************************************************************
** 函数BTM_SetPeriodicInquiryMode
**
** 说明调用此函数以设置设备定期查询模式。如果持续时间为零，则取消定期查询模式。
**
** 参数：p_inqparms-查询信息模式的指针-GENERAL或LIMITED查询持续时间-1.28秒间隔内的长度（如果为“0”，则查询被取消）max_resps-结束查询之前要搜索的最大设备数量filter_cond_type-BTM_CLR_inquiry_filter、BTM_filter_cond_DEVICE_CLASS、，或BTM_FILTER_CONN_BD_ADDR FILTER_COND-过滤器的值（基于FILTER_COND_type）
**
**                  max_delay-连续查询之间的最大时间量min_delay-相继查询之间的最小时间量p_results_cb-返回结果的回调指针（tBTM_INQ_results）
**
** 如果成功启动BTM_ILLEGAL_VALUE，则返回BTM_CMD_STARTED；如果检测到错误参数，则返回BTM_NO_RESOURCES；如果无法分配消息缓冲区BTM_SUCCESS；如果取消定期查询BTM_BUSY；如果设备未启动，则返回查询BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_SetPeriodicInquiryMode (tBTM_INQ_PARMS *p_inqparms,
        UINT16 max_delay, UINT16 min_delay,
        tBTM_INQ_RESULTS_CB *p_results_cb);


/*******************************************************************************
** 函数BTM_StartInquiry
**
** 说明调用此函数以启动查询。
**
** 参数：p_inqparms-查询信息模式的指针-GENERAL或LIMITED查询持续时间-1.28秒间隔内的长度（如果为“0”，则查询被取消）max_resps-结束查询之前要搜索的最大设备数量filter_cond_type-BTM_CLR_inquiry_filter、BTM_filter_cond_DEVICE_CLASS、，或BTM_FILTER_CONN_BD_ADDR FILTER_COND-过滤器的值（基于FILTER_COND_type）
**
**                  p_results_cb-指向在收到查询结果时调用的回调例程的指针。如果此字段为NULL，则不会通知应用程序。
**
**                  p_cmpl_cb-指向在完成时调用的回调例程的指针。如果此字段为NULL，则应用程序完成时不会收到通知。如果已成功启动BTM_BUSY，则返回tBTM_STATUS BTM_CMD_STARTED；如果参数超出范围BTM_NO_RESOURCES，则返回BTM_ILLEGAL_VALUE；如果设备未启动，则无法分配资源启动命令BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_StartInquiry (tBTM_INQ_PARMS *p_inqparms,
                               tBTM_INQ_RESULTS_CB *p_results_cb,
                               tBTM_CMPL_CB *p_cmpl_cb);


/*******************************************************************************
** 函数BTM_IsInquiryActive
**
** 说明此函数返回当前查询状态的位掩码
**
** 如果非活动，返回BTM_INQUIRY_ACTIVE（0）如果受限查询处于活动状态，则返回BTM_LIMITED_INQUIRY_CTIVE BTM_GENERAL_INQUIRY_ACTIVE BTM_PERIODIC_INQUIR_ACTIVE如果定期查询处于活动
**
*******************************************************************************/
//外部
UINT16 BTM_IsInquiryActive (void);


/*******************************************************************************
** 函数BTM_CancelInquiry
**
** 说明此功能在激活时取消查询
**
** 如果设备未启动，则无法分配消息缓冲区BTM_WRONG_MODE，则返回BTM_SUCCESS（如果成功）。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_CancelInquiry(void);


/*******************************************************************************
** 函数BTM_CancelPeriodicInquiry
**
** 说明此功能取消定期查询
**
** 如果无法分配消息缓冲区BTM_SUCCESS，则返回BTM_NO_RESOURCES-如果设备未启动，则取消定期查询BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_CancelPeriodicInquiry(void);


/*******************************************************************************
** 函数BTM_SetConnectability
**
** 说明调用此函数可将设备设置为可连接模式或不可连接模式。可发现模式表示已启用页面扫描。
**
** 如果检测到错误参数，则返回BTM_SUCCESS；如果设备未启动，则无法分配消息缓冲区BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetConnectability (UINT16 page_mode, UINT16 window,
                                   UINT16 interval);


/*******************************************************************************
** 函数BTM_ReadConnectability
**
** 说明调用此函数以读取设备的当前可发现模式。输出参数p_window-当前页面扫描持续时间p_interval-页面扫描之间的当前时间
**
** 返回BTM_NON_CONNECTABLE或BTM_CONNECTABL
**
*******************************************************************************/
//外部
UINT16 BTM_ReadConnectability (UINT16 *p_window, UINT16 *p_interval);


/*******************************************************************************
** 函数BTM_SetInquiryMode
**
** 说明调用此函数以设置标准，使用RSSI模式或扩展本地设备的查询。
**
** 输入参数：BTM_INQ_RESULT_SESTANDARD、BTM_INQ-RESULT_WITH_RSSI或BTM_INQ.RESULT_EXTENDED
**
** 如果成功，则返回BTM_SUCCESS；如果设备未启动，则如果检测到错误参数，则无法获取内存池缓冲区BTM_ILLEGAL_VALUE。
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_SetInquiryMode (UINT8 mode);

/*******************************************************************************
** 函数BTM_SetInquiryScanType
**
** 说明调用此函数将液体扫描类型设置为标准或隔行扫描。
**
** 输入参数：BTM_SCAN_TYPE_STANDARD或BTM_SCAN_TYPE_INTERLACED
**
** 如果BTM_MODE_UNSUPPORTED成功，则返回BTM_SUCCESS；如果设备未启动，则返回1.2设备BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetInquiryScanType (UINT16 scan_type);

/*******************************************************************************
** 函数BTM_SetPageScanType
**
** 说明调用此函数将页面扫描类型设置为标准或隔行扫描。
**
** 输入参数：BTM_SCAN_TYPE_STANDARD或BTM_SCAN_TYPE_INTERLACED
**
** 如果BTM_MODE_UNSUPPORTED成功，则返回BTM_SUCCESS；如果设备未启动，则返回1.2设备BTM_WRONG_MODE。
**
*******************************************************************************/

//外部
tBTM_STATUS BTM_SetPageScanType (UINT16 scan_type);

/*******************************************************************************
** 函数BTM_ReadRemoteDeviceName
**
** 描述此函数向控制器启动远程设备HCI命令，并在进程完成时调用回调。
**
** 输入参数：remote_bda-要检索p_cb的名称的设备地址-返回BTM_CMD_STARTED时调用的回调函数。将指向tBTM_REMOTE_DEV_NAME的指针传递给回调。
**
** 返回BTM_CMD_STARTED。如果请求已成功发送到HCI，则返回该值。如果设备地址不正确，则BTM_BUSY；如果设备未启动，则无法分配资源启动命令BTM_WRONG_MODE。
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_ReadRemoteDeviceName (BD_ADDR remote_bda,
                                       tBTM_CMPL_CB *p_cb,
                                       tBT_TRANSPORT transport);


/*******************************************************************************
** 函数BTM_CancelRemoteDeviceName
**
** 说明此功能启动指定远程设备的取消请求。
**
** 输入参数：无
**
** 返回BTM_CMD_STARTED。如果请求已成功发送到HCI，则返回该值。如果没有活动的远程名称请求，则无法分配资源以启动命令BTM_WRONG_MODE，则为BTM_NO_RESOURCES。
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_CancelRemoteDeviceName (void);

/*******************************************************************************
** 函数BTM_ReadRemoteVersion
**
** 说明调用此函数以读取远程设备的版本
**
** 如果成功，则返回BTM_SUCCESS，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadRemoteVersion (BD_ADDR addr,
                                   UINT8 *lmp_version,
                                   UINT16 *manufacturer,
                                   UINT16 *lmp_sub_version);

/*******************************************************************************
** 函数BTM_ReadRemoteFeatures
**
** 说明调用此函数以读取远程设备支持的功能掩码（功能掩码位于第0页）
**
**                  注：设备功能掩码页面的大小为BTM_FEATURE_BYTES_PER_page字节。
**
** 返回指向远程支持功能掩码的指针
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadRemoteFeatures (BD_ADDR addr);

/*******************************************************************************
** 函数BTM_ReadRemoteExtendedFeatures
**
** 说明调用此函数以读取远程设备的特定扩展功能页
**
**                  注1：设备功能掩码页面的大小为BTM_FEATURE_BYTES_PER_page字节。注2：有效的设备功能掩码页码取决于远程设备的功能。它应在[0-BTM_EXT_FEATURES_PAGE_MAX]范围内。

** 返回指向远程扩展功能掩码的指针，如果page_number无效，则返回NULL
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadRemoteExtendedFeatures (BD_ADDR addr, UINT8 page_number);

/*******************************************************************************
** 函数BTM_ReadNumberRemoteFeaturePages
**
** 描述调用此函数以检索从远程设备读取的功能页的数量
**
** 返回从远程设备读取的功能页数
**
*******************************************************************************/
//外部
UINT8 BTM_ReadNumberRemoteFeaturesPages (BD_ADDR addr);

/*******************************************************************************
** 函数BTM_ReadAllRemoteFeatures
**
** 说明调用此函数以读取远程设备的所有功能
**
** 返回指向远程设备功能掩码页[0]的字节[0]的指针。
**
** 注意：该函数返回指向大小为BTM_FEATURE_BYTES_PER_PAGE（BTM_EXT_FEATURES_PAGE_MAX+1）的数组的指针。
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadAllRemoteFeatures (BD_ADDR addr);

/*******************************************************************************
** 函数BTM_InqDbRead
**
** 说明此功能根据蓝牙设备地址在查询数据库中查找匹配项。这是应用程序的接口，用于获取特定BD地址的查询详细信息。
**
** 返回指向条目的指针，如果找不到则返回NULL
**
*******************************************************************************/
//外部
tBTM_INQ_INFO *BTM_InqDbRead (BD_ADDR p_bda);


/*******************************************************************************
** 函数BTM_InqDbFirst
**
** 说明此函数在查询数据库中查找第一个使用的条目，并返回该条目。应用程序将其与BTM_InqDbNext结合使用，作为遍历查询数据库的方式。
**
** 返回指向第一个使用项的指针，如果数据库为空，则返回NULL
**
*******************************************************************************/
//外部
tBTM_INQ_INFO *BTM_InqDbFirst (void);


/*******************************************************************************
** 函数BTM_InqDbNext
**
** 说明此函数在查询数据库中查找下一个使用的条目，并返回该条目。如果输入参数为NULL，则返回第一个条目。
**
** 返回指向下一个正在使用的条目的指针，如果没有找到，则返回NULL。
**
*******************************************************************************/
//外部
tBTM_INQ_INFO *BTM_InqDbNext (tBTM_INQ_INFO *p_cur);


/*******************************************************************************
** 函数BTM_ClearInqDb
**
** 说明调用此函数以从查询数据库中清除一个设备或所有设备。
**
** 参数p_bda-（输入）BD_ADDR->要清除的设备地址（NULL清除所有条目）
**
** 如果查询、获取远程名称或事件筛选器处于活动状态，则返回BTM_BUSY，否则返回BTM_SUCCESS
**
*******************************************************************************/
//外部
tBTM_STATUS  BTM_ClearInqDb (BD_ADDR p_bda);

/*******************************************************************************
** 函数BTM_ReadInquiryRspTxPower
**
** 说明此命令将读取用于传输FHS和EIR数据包的查询传输功率电平。这可以直接用于Tx功率电平EIR数据类型。
**
** 如果成功，则返回BTM_SUCCESS
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadInquiryRspTxPower (tBTM_CMPL_CB *p_cb);

#if SDP_INCLUDED == TRUE
/*******************************************************************************
** 函数BTM_StartDiscovery
**
** 说明当应用程序（或配置文件）想要使用BTM的发现数据库触发服务发现时，会调用此函数。
**
** 如果发现已启动，则返回tBTM_STATUS BTM_CMD_STARTED BTM_BUSY（如果已在进行中）BTM_UNKNOWN_ADDR（如果INQ DB中没有地址）BTM_ERR_PROCESSING（如果启动命令时出错）
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_StartDiscovery (tBTM_CMPL_CB *p_cmpl_cb,
                                BD_ADDR_PTR p_rem_addr);


/*******************************************************************************
** 函数BTM_FindAttribute
**
** 说明当应用程序（或配置文件）想要查看BTM发现数据库中是否存在属性时，会调用此函数。
**
** 返回指向匹配记录的指针，或NULL
**
*******************************************************************************/
//外部
tSDP_DISC_REC *BTM_FindAttribute (UINT16 attr_id,
                                  tSDP_DISC_REC *p_start_rec);


/*******************************************************************************
** 函数BTM_FindService
**
** 说明当应用程序（或配置文件）想要查看BTM发现数据库中是否存在服务时，会调用此函数。
**
** 返回指向匹配记录的指针，或NULL
**
*******************************************************************************/
//外部
tSDP_DISC_REC *BTM_FindService (UINT16 service_uuid,
                                tSDP_DISC_REC *p_start_rec);


/*******************************************************************************
** 函数BTM_SetDiscoveryParams
**
** 说明调用此函数以设置BTM默认发现参数。这些UUID和属性筛选器在调用BTM_StartDiscovery时使用。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetDiscoveryParams (UINT16 num_uuid, tSDP_UUID *p_uuid_list,
                             UINT16 num_attr, UINT16 *p_attr_list);
#endif /*SDP_INCLUDED*/

/*****************************************************************************
**  ACL CHANNEL MANAGEMENT FUNCTIONS
*****************************************************************************/
/*******************************************************************************
** 函数BTM_SetLinkPolicy
**
** 说明创建并发送HCI“写入策略集”命令
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetLinkPolicy (BD_ADDR remote_bda,
                               UINT16 *settings);

/*******************************************************************************
** 函数BTM_SetDefaultLinkPolicy
**
** 说明设置创建ACL链接时要使用的HCI“写入策略集”命令的默认值。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetDefaultLinkPolicy (UINT16 settings);


/*******************************************************************************
** 函数BTM_SetDefaultLinkSuperTout
**
** 说明设置创建ACL链接时要使用的HCI“写入链接监控超时”命令的默认值。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetDefaultLinkSuperTout (UINT16 timeout);


/*******************************************************************************
** 函数BTM_SetLinkSuperTout
**
** 说明创建并发送HCI“写入链路监控超时”命令
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetLinkSuperTout (BD_ADDR remote_bda,
                                  UINT16 timeout);
/*******************************************************************************
** 函数BTM_GetLinkSuperTout
**
** 说明读取连接的链接监控超时值
**
** 返回操作的状态
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_GetLinkSuperTout (BD_ADDR remote_bda,
                                  UINT16 *p_timeout);

/*******************************************************************************
** 函数BTM_IsAclConnectionUp
**
** 描述调用此函数以检查是否存在到特定远程BD地址的ACL连接。
**
** 如果连接正常，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_IsAclConnectionUp (BD_ADDR remote_bda, tBT_TRANSPORT transport);


/*******************************************************************************
** 函数BTM_GetRole
**
** 描述调用此函数以获取与指定远程设备的ACL连接的本地设备的角色
**
** 如果连接存在，则返回BTM_SUCCESS。BTM_UNKNOWN_ADDR（如果未指定bd-ADDR的活动链接）
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_GetRole (BD_ADDR remote_bd_addr, UINT8 *p_role);



/*******************************************************************************
** 函数BTM_SwitchRole
**
** 描述调用此函数以在主设备和从设备之间切换角色。如果已经设置了角色，它将不起作用。如果命令已启动，则在完成时调用回调函数。
**
** 如果已在指定角色中，则返回BTM_SUCCESS。如果向控制器发出命令，则返回BTM_CMD_STARTED。BTM_NO_RESOURCES如果无法分配内存以发出命令BTM_UNKNOWN_ADDR（如果没有指定bd地址的活动链接）BTM_MODE_UNSUPPORTED（如果本地设备不支持角色切换）
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SwitchRole (BD_ADDR remote_bd_addr,
                            UINT8 new_role,
                            tBTM_CMPL_CB *p_cb);

/*******************************************************************************
** 函数BTM_ReadRSSI
**
** 描述调用此函数以读取特定传输的RSSI。结果的RSSI在回调中返回。（tBTM_RSSI_RESULTS）
**
** 如果向控制器发出命令，则返回BTM_CMD_STARTED。BTM_NO_RESOURCES，如果无法分配内存以发出命令BTM_UNKNOWN_ADDR，如果没有指定bd地址的活动链接BTM_BUSY，如果命令已在执行中
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadRSSI (BD_ADDR remote_bda, tBT_TRANSPORT transport, tBTM_CMPL_CB *p_cb);


/*******************************************************************************
** 函数BTM_ReadTxPower
**
** 描述调用此函数以读取连接的当前连接TX功率。TX功率电平结果在回调中返回。（tBTM_RSSI_RESULTS）
**
** 如果向控制器发出命令，则返回BTM_CMD_STARTED。BTM_NO_RESOURCES，如果无法分配内存以发出命令BTM_UNKNOWN_ADDR，如果没有指定bd地址的活动链接BTM_BUSY，如果命令已在执行中
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadTxPower (BD_ADDR remote_bda,
                             tBT_TRANSPORT transport, tBTM_CMPL_CB *p_cb);

tBTM_STATUS BTM_BleReadAdvTxPower(tBTM_CMPL_CB *p_cb);

void BTM_BleGetWhiteListSize(uint16_t *length);


/*******************************************************************************
** 函数BTM_ReadLinkQuality
**
** 说明调用此函数以读取链接质量。在回调中返回链接质量的值。（tBTM_LINK_质量_结果）
**
** 如果向控制器发出命令，则返回BTM_CMD_STARTED。BTM_NO_RESOURCES，如果无法分配内存以发出命令BTM_UNKNOWN_ADDR，如果没有指定bd地址的活动链接BTM_BUSY，如果命令已在执行中
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadLinkQuality (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb);

/*******************************************************************************
** 函数BTM_RegBusyLevelNotif
**
** 描述调用此函数以注册回调以接收繁忙级别更改事件。
**
** 如果成功注册，则返回BTM_SUCCESS，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_RegBusyLevelNotif (tBTM_BL_CHANGE_CB *p_cb, UINT8 *p_level,
                                   tBTM_BL_EVENT_MASK evt_mask);

/*******************************************************************************
** 函数BTM_AclRegisterForChanges
**
** 描述调用此函数以注册回调以接收ACL数据库更改事件，即新连接或已删除。
**
** 如果成功启动，则返回BTM_SUCCESS，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_AclRegisterForChanges (tBTM_ACL_DB_CHANGE_CB *p_cb);

/*******************************************************************************
** 函数BTM_GetNumAclLinks
**
** 说明调用此函数以统计活动的ACL链接数。
**
** 返回UINT16活动ACL链接数
**
*******************************************************************************/
//外部
UINT16 BTM_GetNumAclLinks (void);

/*******************************************************************************
** 函数BTM_SetQoS
**
** 描述调用此函数以设置QoS
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetQoS(BD_ADDR bd, FLOW_SPEC *p_flow,
                       tBTM_CMPL_CB *p_cb);


/*****************************************************************************
**  （e） 上海合作组织渠道管理职能
*****************************************************************************/
/*******************************************************************************
** 函数BTM_CreateSco
**
** 说明调用此函数以创建SCO连接。如果“is_orig”标志为TRUE，则连接将被发起，否则BTM将等待另一方连接。
**
** 如果ACL连接未启动，则返回BTM_UNKNOWN_ADDR；如果另一个SCO正在设置到相同的BD地址BTM_NO_RESOURCES，则返回BT M_BUSY；如果已启动连接，则已达到最大SCO限制BTM_CMD_STARTED。在本例中，“p_sco_inx”用用于连接的sco索引填充。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_CreateSco (BD_ADDR remote_bda, BOOLEAN is_orig,
                           UINT16 pkt_types, UINT16 *p_sco_inx,
                           tBTM_SCO_CB *p_conn_cb,
                           tBTM_SCO_CB *p_disc_cb);


/*******************************************************************************
** 函数BTM_RemoveSco
**
** 说明调用此函数以删除特定的SCO连接。
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_RemoveSco (UINT16 sco_inx);


/*******************************************************************************
** 函数BTM_SetCoPacketTypes
**
** 描述调用此函数以设置用于特定SCO连接的数据包类型，
**
** 参数pkt_types-以下一个或多个BTM_SCO_pkt_types_MASK_HIV1 BTM_SCO_TKT_types _MASK_HSV2 BTM_SCO_SKT_TYPE_types_MASK-V3 BTM_SCO-pkt_types_MASK_EV3 BTM_SCO_ pkt_types_MISK_EV4
**
**                  BTM_SCO_LINK_ALL_MASK-启用所有支持的类型
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetScoPacketTypes (UINT16 sco_inx, UINT16 pkt_types);


/*******************************************************************************
** 函数BTM_ReadScoPacketTypes
**
** 说明此函数用于读取用于特定SCO连接的数据包类型。
**
** 返回以下一个或多个（位掩码）BTM_SCO_PKT_TYPES_MASK_HIV1 BTM_SCO_TKT_TYPES _MASK_HSV2 BTM_SCO_ PKT_TYPES_MASK-HIV3 BTM_SCOP_PKT_TYPES _MASK-EV3 BTM_SCO_PKT_TTYPES_MASSK_EV4 BTM_SCO_SKT_TYPES_MASK_EV5
**
** 返回连接支持的数据包类型
**
*******************************************************************************/
//外部
UINT16 BTM_ReadScoPacketTypes (UINT16 sco_inx);


/*******************************************************************************
** 函数BTM_ReadDeviceScoPacketTypes
**
** 说明此功能读取设备支持的SCO数据包类型。
**
** 返回设备支持的数据包类型。
**
*******************************************************************************/
//外部
UINT16 BTM_ReadDeviceScoPacketTypes (void);


/*******************************************************************************
** 函数BTM_ReadScoHandle
**
** 说明此函数用于读取用于特定SCO连接的HCI句柄，
**
** 返回连接的句柄，如果SCO索引无效，则返回0xFFFF。
**
*******************************************************************************/
//外部
UINT16 BTM_ReadScoHandle (UINT16 sco_inx);


/*******************************************************************************
** 函数BTM_ReadScoBdAddr
**
** 说明此功能读取特定SCO连接的远程BD地址，
**
** 返回指向BD地址的指针，如果未知，则返回NULL
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadScoBdAddr (UINT16 sco_inx);


/*******************************************************************************
** 函数BTM_ReadScoDiscReason
**
** 说明此函数返回删除（e）SCO连接的原因。它包含读取之前的值，或者直到另一个（e）SCO连接断开。
**
** 如果未设置，则返回HCI原因或BTM_INVALID_SCO_DISC_reason。
**
*******************************************************************************/
//外部
UINT16 BTM_ReadScoDiscReason (void);


/*******************************************************************************
** 函数BTM_SetEScoMode
**
** 说明此函数设置SCO或eSCO的协商参数，并设置为用于调用BTM_CreateSco的默认模式。只有在没有活动的（e）SCO链路时才能调用它。
**
** 如果成功，则返回BTM_SUCCESS。BTM_BUSY，如果有一个或多个活动（e）SCO链路。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetEScoMode (tBTM_SCO_TYPE sco_mode,
                             tBTM_ESCO_PARAMS *p_parms);

/*******************************************************************************
** 函数BTM_SetWBSCodec
**
** 说明此功能向控制器发送命令，为即将到来的eSCO连接设置WBS编解码器。
**
** 返回BTM_SUCCESS。
**
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetWBSCodec (tBTM_SCO_CODEC_TYPE codec_type);

/*******************************************************************************
** 函数BTM_RegForEScoEvts
**
** 说明此函数向指定实例注册SCO事件回调。它应用于接收连接指示事件和链路参数事件的改变。
**
** 如果成功，则返回BTM_SUCCESS。BTM_ILLEGAL_VALUE（如果存在非法sco_inx）
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_RegForEScoEvts (UINT16 sco_inx,
                                tBTM_ESCO_CBACK *p_esco_cback);

/*******************************************************************************
** 函数BTM_ReadEScoLinkParms
**
** 说明此函数返回指定句柄的当前eSCO链接参数。这可以在连接处于活动状态时调用，但通常在收到SCO打开的回调后调用。
**
**                  注意：如果通过1.1控制器调用，则只有数据包类型字段有意义。注意：如果上层不知道当前的sco索引，BTM_FIRST_ACTIVE_sco_index可以用作查找第一个活动sco索引的第一个参数
**
** 如果返回的数据是有效的连接，则返回BTM_SUCCESS。BTM_ILLEGAL_VALUE，如果指定的sco_inx没有连接。如果本地控制器不支持1.2规范，则为BTM_MODE_UNSUPPORTED。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadEScoLinkParms (UINT16 sco_inx,
                                   tBTM_ESCO_DATA *p_parms);

/*******************************************************************************
** 函数BTM_ChangeEScoLinkParms
**
** 说明此功能请求重新协商当前eSCO链路上的参数。如果控制器接受任何更改，则在tBTM_ESCO_CBACK函数中发送BTM_ESCO_CHG_EVT事件以及链路的当前设置。通过调用BTM_SetEScoMode注册回调。
**
** 如果命令成功启动，则返回BTM_CMD_STARTED。BTM_ILLEGAL_VALUE，如果指定的sco_inx没有连接。BTM_NO_RESOURCES-没有足够的资源来启动命令。如果本地控制器不支持1.2规范，则为BTM_MODE_UNSUPPORTED。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ChangeEScoLinkParms (UINT16 sco_inx,
                                     tBTM_CHG_ESCO_PARAMS *p_parms);

/*******************************************************************************
** 函数BTM_EScoConnRsp
**
** 说明收到（e）SCO连接请求事件（BTM_ESCO_CONN_REQ_EVT）时调用此函数以接受或拒绝请求。用于协商eSCO链接的参数。如果p_parms为NULL，则使用通过BTM_SetEScoMode设置的值。如果传入请求的链接类型为SCO，则只有tx_bw、max_latency、content-format和packet_types有效。hci_status参数应为（[0x0]表示接受，[0x0d...0x0f]表示拒绝）
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_EScoConnRsp (UINT16 sco_inx, UINT8 hci_status,
                      tBTM_ESCO_PARAMS *p_parms);

/*******************************************************************************
** 函数BTM_GetNumScoLinks
**
** 说明此函数返回活动SCO链接的数量。
**
** 返回UINT8
**
*******************************************************************************/
//外部
UINT8 BTM_GetNumScoLinks (void);

/*****************************************************************************
**  SECURITY MANAGEMENT FUNCTIONS
*****************************************************************************/
/*******************************************************************************
** 函数BTM_SecRegister
**
** 说明应用程序管理器调用此函数以注册安全服务。可以有且只能有一个应用程序保存链接键。BTM仅允许首次注册。
**
** 如果注册为OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecRegister (tBTM_APPL_INFO *p_cb_info);

/*******************************************************************************
** 函数BTM_SecRegisterLinkKeyNotificationCallback
**
** 描述配置文件可以注册，以便在每个连接生成新的链接密钥时得到通知。
**
** 如果注册为OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecRegisterLinkKeyNotificationCallback(
    tBTM_LINK_KEY_CALLBACK *p_callback);

/*******************************************************************************
** 函数BTM_SecAddRmtNameNotifyCallback
**
** 说明配置文件可以注册以在解析远程设备名称时收到通知（最多BTM_SEC_MAX_RMT_name_CALLBACKS）。
**
** 如果注册为OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecAddRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback);


/*******************************************************************************
** 函数BTM_SecDeleteRmtNameNotifyCallback
**
** 描述当每个连接生成新的链接密钥时，配置文件可以注销通知。
**
** 如果OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecDeleteRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback);

/*******************************************************************************
** 函数BTM_GetSecurityFlags
**
** 说明获取设备的安全标志
**
** 如果找到设备，则返回BOOLEAN TRUE或FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_GetSecurityFlags (BD_ADDR bd_addr, UINT8 *p_sec_flags);

/*******************************************************************************
** 函数BTM_GetSecurityFlagsByTransport
**
** 说明获取特定传输上设备的安全标志
**
** 参数bd_addr:远程设备的bd地址p_sec_flags:Out参数，用于填充连接传输的安全标志：连接的物理传输（BR/EDR或LE）
**
** 如果找到设备，则返回BOOLEAN TRUE或FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_GetSecurityFlagsByTransport (BD_ADDR bd_addr,
        UINT8 *p_sec_flags, tBT_TRANSPORT transport);

/*******************************************************************************
** 函数BTM_ReadTrustedMask
**
** 说明获取设备的受信任掩码
**
** 如果未找到设备记录，则返回NULL。否则，可信掩码
**
*******************************************************************************/
//外部
UINT32 *BTM_ReadTrustedMask (BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_SetPinType
**
** 说明设置设备的PIN类型。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetPinType (UINT8 pin_type, PIN_CODE pin_code, UINT8 pin_code_len);


/*******************************************************************************
** 函数BTM_SetPairableMode
**
** 说明启用或禁用配对
**
** 参数allow_pairing-（TRUE或FALSE）设备是否允许配对。connect_only_paired-（TRUE或FALSE）是否仅允许配对设备连接。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetPairableMode (BOOLEAN allow_pairing, BOOLEAN connect_only_paired);

/*******************************************************************************
** 函数BTM_SetSecureConnectionsOnly
**
** 说明启用或禁用模式4 0级服务的默认处理
**
** 参数secure_connections_only_mode-（TRUE或FALSE）TRUE表示设备应将模式4级别0服务视为其他级别的服务。FALSE表示设备应为模式4级别0服务提供默认处理。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetSecureConnectionsOnly (BOOLEAN secure_connections_only_mode);

/*******************************************************************************
** 函数BTM_SetSecurityLevel
**
** 说明向security Manager注册服务安全级别。无论所使用的安全级别如何，每个服务都必须注册其需求。此API对连接的发起者和接受者分别调用一次和一次。
**
** 如果注册为OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SetSecurityLevel (BOOLEAN is_originator, const char *p_name,
                              UINT8 service_id, UINT16 sec_level,
                              UINT16 psm, UINT32 mx_proto_id,
                              UINT32 mx_chan_id);

/*******************************************************************************
** 函数BTM_SetOutService
**
** 说明调用此函数以设置传出连接的服务。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetOutService(BD_ADDR bd_addr, UINT8 service_id, UINT32 mx_chan_id);

/*******************************************************************************
** 函数BTM_SecClrService
**
** 说明从安全数据库中删除指定的服务记录。将删除具有指定名称的所有服务记录。通常仅由RAM有限的设备使用，以便可以重用旧的安全服务记录。记录（SDP除外）。
**
** 返回释放的记录数。
**
*******************************************************************************/
//外部
UINT8 BTM_SecClrService (UINT8 service_id);

/*******************************************************************************
** 函数BTM_SecAddDevice
**
** 说明添加/修改设备。该功能通常在主机启动期间调用，以恢复存储在NVRAM中的所有所需信息。如果未知，dev_class、bd_name、link_key和功能为NULL
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecAddDevice (BD_ADDR bd_addr, DEV_CLASS dev_class,
                          BD_NAME bd_name, UINT8 *features,
                          UINT32 trusted_mask[], LINK_KEY link_key,
                          UINT8 key_type, tBTM_IO_CAP io_cap, UINT8 pin_length,
                          UINT8 sc_support);


/*******************************************************************************
** 函数BTM_SecDeleteDevice
**
** 说明与设备关联的可用资源。
**
** 如果rmoved OK，则返回TRUE；如果找不到，则返回FALSE
**
*******************************************************************************/
//外部
BOOLEAN BTM_SecDeleteDevice (BD_ADDR bd_addr, tBT_TRANSPORT transport);

/*******************************************************************************
** 函数BTM_SecGetDeviceLinkKey
**
** 描述调用此函数以获取设备的链接密钥，如果链接密钥可用，则返回BTM_SUCCESS；如果安全管理器不知道设备或设备记录不包含链接密钥信息，则返回BTM_UNKNOWN_ADDR
**
** 如果成功，则返回BTM_SUCCESS，否则返回错误代码
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SecGetDeviceLinkKey (BD_ADDR bd_addr,
                                     LINK_KEY link_key);


/*******************************************************************************
** 函数BTM_SecGetDeviceLinkKeyType
**
** 描述调用此函数以获取设备的链接密钥类型。如果链接密钥可用，则返回BTM_SUCCESS；如果安全管理器不知道设备或设备记录不包含链接密钥信息，则返回BTM_UNKNOWN_ADDR
**
** 如果链接键未知，则返回BTM_LKEY_TYPE_IGNORE，否则返回链接类型。
**
*******************************************************************************/
//外部
tBTM_LINK_KEY_TYPE BTM_SecGetDeviceLinkKeyType (BD_ADDR bd_addr);


/*******************************************************************************
** 函数BTM_PINCodeReply
**
** 说明此函数在Security Manager向UI提交PIN码请求后调用。
**
** 参数：bd_addr-请求PIN的设备的地址res-操作结果BTM_SUCCESS if SUCCESS PIN_len-PIN码的字节长度p_PIN-指向具有PIN码trusted_mask的数组的指针-受信任服务的位OR（UINT32数组）
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_PINCodeReply (BD_ADDR bd_addr, UINT8 res, UINT8 pin_len,
                       UINT8 *p_pin, UINT32 trusted_mask[]);


/*******************************************************************************
** 函数BTM_SecBond
**
** 描述调用此函数以执行与对等设备的绑定。
**
** 参数：bd_addr-要绑定pin_len的设备地址-pin码的长度（字节）p_pin-指向具有pin码trusted_mask的数组的指针-受信任服务的按位OR（UINT32的数组）

** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SecBond (BD_ADDR bd_addr,
                         UINT8 pin_len, UINT8 *p_pin,
                         UINT32 trusted_mask[]);

/*******************************************************************************
** 函数BTM_SecBondByTransport
**
** 说明调用此函数以通过指定的传输执行绑定
**
** 参数：bd_addr-要绑定的设备的地址pin_len-pin码的长度（以字节为单位）p_pin-指向具有pin码trusted_mask的数组的指针-受信任服务的位OR（UINT32的数组）传输：用于绑定的物理传输（BR/EDR或LE）
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SecBondByTransport (BD_ADDR bd_addr,
                                    tBT_TRANSPORT transport,
                                    UINT8 pin_len, UINT8 *p_pin,
                                    UINT32 trusted_mask[]);

/*******************************************************************************
** 函数BTM_SecBondCancel
**
** 描述调用此函数以取消正在进行的与对等设备的绑定过程。
**
** 如果成功启动，则返回BTM_CMD_STARTED，否则返回错误
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SecBondCancel (BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_SetEncryption
**
** 说明调用此函数以确保连接已加密。只能在打开的连接上调用。通常只需要用于首先要打开未加密链接，然后再对其进行加密的连接。
**
** 参数：bd_addr-对等设备的地址p_callback-如果回调函数在完成所需过程后返回PENDING，则调用该函数的指针。如果不需要状态，则可以设置为NULL。p_ref_data-指针指向调用方希望在完成时在回调函数中接收的任何数据。如果不使用，则可以设置为NULL。
**
** 返回BTM_SUCCESS-已加密BTM_PENDING-命令将在回调BTM_WRONG_MODE-连接未启动时返回。BTM_BUSY-安全过程当前处于活动状态BTM_MODE_UNSUPPORTED-如果安全管理器未链接到。
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetEncryption (BD_ADDR bd_addr, tBT_TRANSPORT transport,
                               tBTM_SEC_CBACK *p_callback, void *p_ref_data);

/*******************************************************************************
** 函数BTM_ConfirmReqReply
**
** 说明调用此函数以确认简单配对的数值，以响应BTM_SP_CFM_REQ_EVT
**
** 参数：res-操作结果BTM_SUCCESS if SUCCESS bd_addr-对等设备的地址
**
*******************************************************************************/
//外部
void BTM_ConfirmReqReply(tBTM_STATUS res, BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_PasskeyReqReply
**
** 说明调用此函数以响应BTM_SP_KEY_REQ_EVT为简单配对提供密钥
**
** 参数：res-如果成功，则操作BTM_SUCCESS的结果bd_addr-对等设备密钥的地址-0-999999（0xF423F）范围内的数值。
**
*******************************************************************************/
//外部
void BTM_PasskeyReqReply(tBTM_STATUS res, BD_ADDR bd_addr, UINT32 passkey);

/*******************************************************************************
** 函数BTM_SendKeypressNotif
**
** 说明此功能由具有KeyboardOnly IO功能的设备（很可能是HID设备）在密钥输入模式期间使用。它由HID设备调用，以在输入或擦除密钥时通知远程设备。
**
** 参数：bd_addr-对等设备类型的地址-通知类型
**
*******************************************************************************/
//外部
void BTM_SendKeypressNotif(BD_ADDR bd_addr, tBTM_SP_KEY_TYPE type);

/*******************************************************************************
** 函数BTM_IoCapRsp
**
** 说明当事件数据IO_REQ时，响应BTM_SP_IO_REQ_EVT调用此函数。tBTM_SP_CALLBACK实现将oob_data设置为BTM_oob_UNKNOWN，调用此函数以提供实际响应
**
** 参数：bd_addr-对等设备的地址io_cap-本地设备的io能力。oob-BTM_oob_NONE或BTM_oob-PRESENT。auth_req-是否需要MITM保护。
**
*******************************************************************************/
//外部
void BTM_IoCapRsp(BD_ADDR bd_addr, tBTM_IO_CAP io_cap,
                  tBTM_OOB_DATA oob, tBTM_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTM_ReadLocalOobData
**
** 说明调用此函数以从LM读取本地OOB数据
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadLocalOobData(void);

/*******************************************************************************
** 函数BTM_RemoteOobDataReply
**
** 说明调用此函数以响应BTM_SP_RMT_OOB_EVT，为简单配对提供远程OOB数据
**
** 参数：bd_addr-对等设备的地址c-简单配对哈希c。r-简单配对随机化器c。
**
*******************************************************************************/
//外部
void BTM_RemoteOobDataReply(tBTM_STATUS res, BD_ADDR bd_addr,
                            BT_OCTET16 c, BT_OCTET16 r);

/*******************************************************************************
** 函数BTM_BuildOobData
**
** 描述调用此函数以构建通过OOB（非蓝牙）链路发送的OOB数据负载
**
** 参数：p_data-OOB数据的位置max_len-p_data大小。c-简单配对哈希c。r-简单配对随机化器c。name_len-0，不包括本地设备名称。否则，本地设备名称最多包含此指定长度
**
** 返回p_data中的字节数。
**
*******************************************************************************/
//外部
UINT16 BTM_BuildOobData(UINT8 *p_data, UINT16 max_len, BT_OCTET16 c,
                        BT_OCTET16 r, UINT8 name_len);

/*******************************************************************************
** 函数BTM_BothEndsSupportSecureConnections
**
** 说明调用此函数以检查bd_addr指定的本地设备和对等设备是否都支持BR/EDR安全连接。
**
** 参数：bd_addr-对等方的地址
**
** 如果本地和远程设备都支持BR/EDR安全连接，则返回TRUE。否则为FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_BothEndsSupportSecureConnections(BD_ADDR bd_addr);

/*******************************************************************************
** 功能BTM_PeerSupportsSecureConnections
**
** 说明调用此函数以检查对等方是否支持BR/EDR安全连接。
**
** 参数：bd_addr-对等方的地址
**
** 如果对等方支持BR/EDR安全连接，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
//外部
BOOLEAN BTM_PeerSupportsSecureConnections(BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_ReadOobData
**
** 描述调用此函数以解析通过OOB（非蓝牙）链路接收的OOB数据负载
**
** 参数：p_data-OOB数据的位置eir_tag-读取数据的关联eir标记。p_len（输出）-具有给定标记的数据的长度。
**
** 返回具有给定标记的数据的开头。如果找不到标记，则返回NULL。
**
*******************************************************************************/
//外部
UINT8 *BTM_ReadOobData(UINT8 *p_data, UINT8 eir_tag, UINT8 *p_len);

/*******************************************************************************
** 函数BTM_SecReadDevName
**
** 说明在安全数据库中查找指定BD地址的设备名称。
**
** 返回指向名称或NULL的指针
**
*******************************************************************************/
//外部
char *BTM_SecReadDevName (BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTM_SecClearSecurityFlags
**
** 说明重置给定移除设备的安全标志（标记为未配对）。
**
*******************************************************************************/
extern void BTM_SecClearSecurityFlags (BD_ADDR bd_addr);



/*****************************************************************************
**  POWER MANAGEMENT FUNCTIONS
*****************************************************************************/
/*******************************************************************************
** 函数BTM_PmRegister
**
** 向电源管理器注册或注销描述
**
** 如果成功，则返回BTM_SUCCESS；如果没有空间进行注册，则返回BTM_NO_RESOURCES BTM_ILLEGAL_VALUE
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_PmRegister (UINT8 mask, UINT8 *p_pm_id,
                            tBTM_PM_STATUS_CBACK *p_cb);


/*******************************************************************************
** 功能BTM_SetPowerMode
**
** 描述将模式存储在控制块中或更改ACL连接行为。
**
** 如果成功，返回BTM_SUCCESS；如果bd-ADDR不活动或不正确，则返回BTM_UNKNOWN_ADDR
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetPowerMode (UINT8 pm_id, BD_ADDR remote_bda,
                              tBTM_PM_PWR_MD *p_mode);


/*******************************************************************************
** 函数BTM_ReadPowerMode
**
** 说明返回特定ACL连接的当前模式。
**
** 输入Param remote_bda-所需ACL连接的设备地址
**
** 输出参数p_mode-当前模式复制到的地址。BTM_ACL_MODE_NORMAL BTM_ACL_MODE_HOLD BTM_ACI_MODE_NIFF BTM_ACL-MODE_PARK（仅当返回代码为BTM_SUCCESS时有效）
**
** 如果成功，返回BTM_SUCCESS；如果bd-ADDR不活动或不正确，则返回BTM_UNKNOWN_ADDR
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ReadPowerMode (BD_ADDR remote_bda,
                               tBTM_PM_MODE *p_mode);

/*******************************************************************************
** 函数BTM_SetSrParams
**
** 说明如果给定ACL连接处于ACTIVE模式，则发送该连接的给定SSR参数。
**
** 输入参数remote_bda-所需ACL连接的设备地址max_lat-最大延迟（0.625ms）（0-0xFFFE）min_rmt_to-最小远程超时min_loc_to-最低本地超时
**
** 如果HCI命令发出成功，返回BTM_SUCCESS；如果bd-ADDR未激活，则返回BTM_UNKNOWN_ADDR；如果存储命令，则返回错误的BTM_CMD_STORED
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_SetSsrParams (BD_ADDR remote_bda, UINT16 max_lat,
                              UINT16 min_rmt_to, UINT16 min_loc_to);

/*******************************************************************************
** 函数BTM_GetHCIConnHandle
**
** 描述调用此函数以获取到特定远程BD地址的ACL连接的句柄。
**
** 返回连接的句柄，如果没有，则返回0xFFFF。
**
*******************************************************************************/
//外部
UINT16 BTM_GetHCIConnHandle (BD_ADDR remote_bda, tBT_TRANSPORT transport);

/*******************************************************************************
** 函数BTM_DeleteStoredLinkKey
**
** 说明调用此功能可从连接到蓝牙控制器的NVRAM存储器中删除指定设备地址的链接密钥。
**
** 参数：bd_addr-设备的地址p_cb-要调用以返回结果的回调函数
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_DeleteStoredLinkKey(BD_ADDR bd_addr, tBTM_CMPL_CB *p_cb);

/*******************************************************************************
** 函数BTM_WriteEIR
**
** 描述调用此函数将EIR数据写入控制器。
**
** 参数p_buff-分配的HCI命令缓冲区，包括扩展查询响应fec_required-是否需要fec
**
** 返回BTM_SUCCESS-如果成功BTM_MODE_UNSUPPORTED-如果本地设备无法支持
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_WriteEIR( BT_HDR *p_buff, BOOLEAN fec_required);

/*******************************************************************************
** 函数BTM_CheckEirData
**
** 描述调用此函数以从重要部分获取EIR数据。
**
** 参数p_eir-eir有效部分类型的指针-查找eir数据类型p_length-返回eir数据的长度
**
** 返回EIR数据的指针
**
*******************************************************************************/
//外部
UINT8 *BTM_CheckEirData( UINT8 *p_eir, UINT8 type, UINT8 *p_length );

/*******************************************************************************
** 函数BTM_HasEirService
**
** 描述调用此函数以了解UUID是否在UUID的位图中。
**
** 参数p_eir_uid-uuid列表的位图uuid16-uuid 16位
**
** 返回TRUE-如果找到FALSE-如果找不到
**
*******************************************************************************/
//外部
BOOLEAN BTM_HasEirService( UINT32 *p_eir_uuid, UINT16 uuid16 );

/*******************************************************************************
** 函数BTM_HasInquiryEirService
**
** 描述调用此函数以了解UUID列表的位图中是否有UUID。
**
** 参数p_results-查询结果uuid16-UUID 16位
**
** 返回BTM_EIR_FOUND-如果找到BTM_EIR_NOT_FOUND-如果找不到并且它是完整列表BTM_EIR-UNKNOWN-如果找找到并且它不是完整列表
**
*******************************************************************************/
//外部
tBTM_EIR_SEARCH_RESULT BTM_HasInquiryEirService( tBTM_INQ_RESULTS *p_results,
        UINT16 uuid16 );

/*******************************************************************************
** 函数BTM_AddEirService
**
** 描述调用此函数以在UUID列表的位图中添加服务。
**
** 参数p_eir_uid-eir uuid16的uuid列表的位掩码-uuid 16位
**
** 返回None
**
*******************************************************************************/
//外部
void BTM_AddEirService( UINT32 *p_eir_uuid, UINT16 uuid16 );

/*******************************************************************************
** 函数BTM_RemoveEirService
**
** 描述调用此函数以删除UUID列表位图中的服务。
**
** 参数p_eir_uid-eir uuid16的uuid列表的位掩码-uuid 16位
**
** 返回None
**
*******************************************************************************/
//外部
void BTM_RemoveEirService( UINT32 *p_eir_uuid, UINT16 uuid16 );

/*******************************************************************************
** 函数BTM_GetEirSupportedServices
**
** 描述调用此函数以从UUID列表的位图中获取UUID列表。
**
** 参数p_eir_uid-eir的uuid列表的位掩码p-eir当前指针的引用max_num_uuid16-可以在eir num_uuid16中写入uuid的最大数量-uuid的数量已写入eir
**
** 如果BTM_EIR_MORE_16BITS_UUID_TYPE大于最大值，则返回BTM_EIR_COMPLETE_16BITS_UUID_TTYPE，否则返回
**
*******************************************************************************/
//外部
UINT8 BTM_GetEirSupportedServices( UINT32 *p_eir_uuid,    UINT8 **p,
                                   UINT8  max_num_uuid16, UINT8 *p_num_uuid16);

/*******************************************************************************
** 函数BTM_GetEirUuidList
**
** 说明此函数解析EIR并返回UUID列表。
**
** 参数p_eir-eir uuid_size-LEN_uuid_16、LEN_UID_32、LEN__uuid_128 p_num_uuid-返回找到的列表p_uuid_list中的uuid数量-返回uuid 16位列表max_num_uuid–要返回的uuid的最大数量
**
** 如果未找到BTM_EIR_COMPLETE_16BITS_UUID_TYPE BTM_EIR.MORE_16BITS_UUID_TYPE BTM_EIR_COMPLETE_32BITS_UID_TYPE BTM_EIR-MORE_32BITS_UUID，则返回0
**
*******************************************************************************/
//外部
UINT8 BTM_GetEirUuidList( UINT8 *p_eir, UINT8 uuid_size, UINT8 *p_num_uuid,
                          UINT8 *p_uuid_list, UINT8 max_num_uuid);

/*****************************************************************************
**  SCO OVER HCI
*****************************************************************************/
/*******************************************************************************
** 函数BTM_ConfigScoPath
**
** 说明此函数启用/禁用HCI上的SCO，并在启用HCI上SCO时注册SCO数据回调。
**
** 参数路径：SCO或HCI p_SCO_data_cb：回调函数或SCO数据（如果路径设置为传输）。p_pcm_param：指向pcm接口参数的指针。如果使用NULL指针，将使用控制块中维护的PCM参数；否则更新控制块值。err_data_rpt:Lisbon功能，无论是否启用错误数据报告。
**
** 如果成功，则返回BTM_SUCCESS。BTM_NO_RESOURCES：没有启动命令的资源。BTM_ILLEGAL_VALUE:回调函数指针无效。BTM_CMD_STARTED:命令已发送。正在等待命令cmpl事件。
**
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_ConfigScoPath (tBTM_SCO_ROUTE_TYPE path,
                               tBTM_SCO_DATA_CB *p_sco_data_cb,
                               tBTM_SCO_PCM_PARAM *p_pcm_param,
                               BOOLEAN err_data_rpt);

/*******************************************************************************
** 函数BTM_WriteScoData
**
** 说明此函数将SCO数据写入指定的实例。要写入的数据p_buf需要携带HCI_SCO_PREAMBLE_SIZE字节的偏移量，并且数据长度不能超过BTM_SCO_data_SIZE_MAX字节，其默认值设置为60且可配置。超过最大字节的数据将被截断。
**
** 返回BTM_SUCCESS：数据写入成功BTM_ILLEGAL_VALUE:SCO数据包含非法的偏移值。BTM_SCO_BAD_LENGTH：SCO数据长度超过了最大SCO数据包大小。BTM_NO_RESOURCES：无资源。BTM_UNKNOWN_ADDR：未知的SCO连接句柄，或SCO未通过HCI路由。
**
**
*******************************************************************************/
//外部
tBTM_STATUS BTM_WriteScoData (UINT16 sco_inx, BT_HDR *p_buf);

/*******************************************************************************
** 函数BTM_SetARCMode
**
** 说明发送音频路由控制命令。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_SetARCMode (UINT8 iface, UINT8 arc_mode, tBTM_VSC_CMPL_CB *p_arc_cb);


/*******************************************************************************
** 功能BTM_PCM2Setup_Write
**
** 说明发送PCM2_Setup写入命令。
**
** 返回void
**
*******************************************************************************/
//外部
void BTM_PCM2Setup_Write (BOOLEAN clk_master, tBTM_VSC_CMPL_CB *p_arc_cb);


/*******************************************************************************
** 函数BTM_PM_ReadControllerState
**
** 说明调用此函数以获取控制器状态
**
** 返回控制器状态（BTM_CONTROL_ACTIVE、BTM_CONTROL_SCAN和BTM_CONTROL_IDLE）
**
*******************************************************************************/
//外部
tBTM_CONTRL_STATE BTM_PM_ReadControllerState(void);

/*******************************************************************************
** 函数BTM_SetAfhChannels
**
** 说明调用此函数设置AFH信道
**
** 返回操作的状态
**
*******************************************************************************/
tBTM_STATUS BTM_SetAfhChannels (AFH_CHANNELS channels, tBTM_CMPL_CB *p_afh_channels_cmpl_cback);

/*******************************************************************************
** 函数BTM_BleSetChannels
**
** 说明调用此函数设置BLE信道
**
** 返回操作的状态
**
*******************************************************************************/
tBTM_STATUS BTM_BleSetChannels (BLE_CHANNELS channels, tBTM_CMPL_CB *p_ble_channels_cmpl_cback);

#ifdef __cplusplus
}
#endif

#endif /* BTM_API_H */

