// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_GATT_DEFS_H__
#define __ESP_GATT_DEFS_H__

#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/// GATT INVALID UUID
#define ESP_GATT_ILLEGAL_UUID               0
/// GATT INVALID HANDLE
#define ESP_GATT_ILLEGAL_HANDLE             0
///GATT属性最大句柄
#define ESP_GATT_ATTR_HANDLE_MAX            100
#define ESP_GATT_MAX_READ_MULTI_HANDLES     10           /* 一个请求中读取的最大属性数*/


/**@{
 * 所有“ESP_GATT_UUID_xxx”都是属性类型
 */
#define ESP_GATT_UUID_IMMEDIATE_ALERT_SVC           0x1802          /*  即时警报服务*/
#define ESP_GATT_UUID_LINK_LOSS_SVC                 0x1803          /*  链路丢失服务*/
#define ESP_GATT_UUID_TX_POWER_SVC                  0x1804          /*  TX电源服务*/
#define ESP_GATT_UUID_CURRENT_TIME_SVC              0x1805          /*  当前时间服务*/
#define ESP_GATT_UUID_REF_TIME_UPDATE_SVC           0x1806          /*  参考时间更新服务*/
#define ESP_GATT_UUID_NEXT_DST_CHANGE_SVC           0x1807          /*  下一次DST更改服务*/
#define ESP_GATT_UUID_GLUCOSE_SVC                   0x1808          /*  葡萄糖服务*/
#define ESP_GATT_UUID_HEALTH_THERMOM_SVC            0x1809          /*  健康温度计服务*/
#define ESP_GATT_UUID_DEVICE_INFO_SVC               0x180A          /*  设备信息服务*/
#define ESP_GATT_UUID_HEART_RATE_SVC                0x180D          /*  心率服务*/
#define ESP_GATT_UUID_PHONE_ALERT_STATUS_SVC        0x180E          /* 电话警报状态服务*/
#define ESP_GATT_UUID_BATTERY_SERVICE_SVC           0x180F          /* 电池服务*/
#define ESP_GATT_UUID_BLOOD_PRESSURE_SVC            0x1810          /* 血压服务*/
#define ESP_GATT_UUID_ALERT_NTF_SVC                 0x1811          /* 警报通知服务*/
#define ESP_GATT_UUID_HID_SVC                       0x1812          /* HID服务*/
#define ESP_GATT_UUID_SCAN_PARAMETERS_SVC           0x1813          /* 扫描参数服务*/
#define ESP_GATT_UUID_RUNNING_SPEED_CADENCE_SVC     0x1814          /* 跑步速度和Cadence服务*/
#define ESP_GATT_UUID_Automation_IO_SVC             0x1815          /* 自动化IO服务*/
#define ESP_GATT_UUID_CYCLING_SPEED_CADENCE_SVC     0x1816          /* 自行车速度和Cadence服务*/
#define ESP_GATT_UUID_CYCLING_POWER_SVC             0x1818          /* 循环电源服务*/
#define ESP_GATT_UUID_LOCATION_AND_NAVIGATION_SVC   0x1819          /* 位置和导航服务*/
#define ESP_GATT_UUID_ENVIRONMENTAL_SENSING_SVC     0x181A          /* 环境传感服务*/
#define ESP_GATT_UUID_BODY_COMPOSITION              0x181B          /* 身体成分服务*/
#define ESP_GATT_UUID_USER_DATA_SVC                 0x181C          /* 用户数据服务*/
#define ESP_GATT_UUID_WEIGHT_SCALE_SVC              0x181D          /* 体重秤服务*/
#define ESP_GATT_UUID_BOND_MANAGEMENT_SVC           0x181E          /* 债券管理服务*/
#define ESP_GATT_UUID_CONT_GLUCOSE_MONITOR_SVC      0x181F          /* 持续血糖监测服务*/

#define ESP_GATT_UUID_PRI_SERVICE                   0x2800
#define ESP_GATT_UUID_SEC_SERVICE                   0x2801
#define ESP_GATT_UUID_INCLUDE_SERVICE               0x2802
#define ESP_GATT_UUID_CHAR_DECLARE                  0x2803          /*  特性声明*/

#define ESP_GATT_UUID_CHAR_EXT_PROP                 0x2900          /*  特征扩展属性*/
#define ESP_GATT_UUID_CHAR_DESCRIPTION              0x2901          /*  特征用户描述*/
#define ESP_GATT_UUID_CHAR_CLIENT_CONFIG            0x2902          /*  客户端特征配置*/
#define ESP_GATT_UUID_CHAR_SRVR_CONFIG              0x2903          /*  服务器特征配置*/
#define ESP_GATT_UUID_CHAR_PRESENT_FORMAT           0x2904          /*  特色演示格式*/
#define ESP_GATT_UUID_CHAR_AGG_FORMAT               0x2905          /*  特征聚合格式*/
#define ESP_GATT_UUID_CHAR_VALID_RANGE              0x2906          /*  特征有效范围*/
#define ESP_GATT_UUID_EXT_RPT_REF_DESCR             0x2907          /*  外部报告参考*/
#define ESP_GATT_UUID_RPT_REF_DESCR                 0x2908          /*  报告参考号*/
#define ESP_GATT_UUID_NUM_DIGITALS_DESCR            0x2909          /*  数字的数量*/
#define ESP_GATT_UUID_VALUE_TRIGGER_DESCR           0x290A          /*  值触发器设置*/
#define ESP_GATT_UUID_ENV_SENSING_CONFIG_DESCR      0x290B          /*  环境传感配置*/
#define ESP_GATT_UUID_ENV_SENSING_MEASUREMENT_DESCR 0x290C          /*  环境传感测量*/
#define ESP_GATT_UUID_ENV_SENSING_TRIGGER_DESCR     0x290D          /*  环境感应触发设置*/
#define ESP_GATT_UUID_TIME_TRIGGER_DESCR            0x290E          /*  时间触发器设置*/

/* GAP配置文件属性*/
#define ESP_GATT_UUID_GAP_DEVICE_NAME               0x2A00
#define ESP_GATT_UUID_GAP_ICON                      0x2A01
#define ESP_GATT_UUID_GAP_PREF_CONN_PARAM           0x2A04
#define ESP_GATT_UUID_GAP_CENTRAL_ADDR_RESOL        0x2AA6

/* 属性配置文件属性UUID*/
#define ESP_GATT_UUID_GATT_SRV_CHGD                 0x2A05

/* 链接ESP_Loss服务*/
#define ESP_GATT_UUID_ALERT_LEVEL                   0x2A06          /* 警报级别*/
#define ESP_GATT_UUID_TX_POWER_LEVEL                0x2A07          /* TX功率电平*/

/* 当前时间服务*/
#define ESP_GATT_UUID_CURRENT_TIME                  0x2A2B          /* 当前时间*/
#define ESP_GATT_UUID_LOCAL_TIME_INFO               0x2A0F          /* 当地时间信息*/
#define ESP_GATT_UUID_REF_TIME_INFO                 0x2A14          /* 参考时间信息*/

/* 网络可用性配置文件*/
#define ESP_GATT_UUID_NW_STATUS                     0x2A18          /* 网络可用性状态*/
#define ESP_GATT_UUID_NW_TRIGGER                    0x2A1A          /* 网络可用性触发*/

/* 电话警报*/
#define ESP_GATT_UUID_ALERT_STATUS                  0x2A3F          /* 警报状态*/
#define ESP_GATT_UUID_RINGER_CP                     0x2A40          /* 振铃器控制点*/
#define ESP_GATT_UUID_RINGER_SETTING                0x2A41          /* 振铃器设置*/

/* 葡萄糖服务*/
#define ESP_GATT_UUID_GM_MEASUREMENT                0x2A18
#define ESP_GATT_UUID_GM_CONTEXT                    0x2A34
#define ESP_GATT_UUID_GM_CONTROL_POINT              0x2A52
#define ESP_GATT_UUID_GM_FEATURE                    0x2A51

/* 设备信息特性*/
#define ESP_GATT_UUID_SYSTEM_ID                     0x2A23
#define ESP_GATT_UUID_MODEL_NUMBER_STR              0x2A24
#define ESP_GATT_UUID_SERIAL_NUMBER_STR             0x2A25
#define ESP_GATT_UUID_FW_VERSION_STR                0x2A26
#define ESP_GATT_UUID_HW_VERSION_STR                0x2A27
#define ESP_GATT_UUID_SW_VERSION_STR                0x2A28
#define ESP_GATT_UUID_MANU_NAME                     0x2A29
#define ESP_GATT_UUID_IEEE_DATA                     0x2A2A
#define ESP_GATT_UUID_PNP_ID                        0x2A50

/* HID特性*/
#define ESP_GATT_UUID_HID_INFORMATION               0x2A4A
#define ESP_GATT_UUID_HID_REPORT_MAP                0x2A4B
#define ESP_GATT_UUID_HID_CONTROL_POINT             0x2A4C
#define ESP_GATT_UUID_HID_REPORT                    0x2A4D
#define ESP_GATT_UUID_HID_PROTO_MODE                0x2A4E
#define ESP_GATT_UUID_HID_BT_KB_INPUT               0x2A22
#define ESP_GATT_UUID_HID_BT_KB_OUTPUT              0x2A32
#define ESP_GATT_UUID_HID_BT_MOUSE_INPUT            0x2A33

 ///心率测量
#define    ESP_GATT_HEART_RATE_MEAS                 0x2A37
///车斗传感器位置
#define    ESP_GATT_BODY_SENSOR_LOCATION            0x2A38
///心率控制点
#define    ESP_GATT_HEART_RATE_CNTL_POINT           0x2A39

/* 电池使用特性*/
#define ESP_GATT_UUID_BATTERY_LEVEL                 0x2A19

/* 传感器服务*/
#define ESP_GATT_UUID_SC_CONTROL_POINT              0x2A55
#define ESP_GATT_UUID_SENSOR_LOCATION               0x2A5D

/* 跑步者速度和节奏服务*/
#define ESP_GATT_UUID_RSC_MEASUREMENT               0x2A53
#define ESP_GATT_UUID_RSC_FEATURE                   0x2A54

/* 自行车速度和节奏服务*/
#define ESP_GATT_UUID_CSC_MEASUREMENT               0x2A5B
#define ESP_GATT_UUID_CSC_FEATURE                   0x2A5C

/* 扫描ESP_Parameter特性*/
#define ESP_GATT_UUID_SCAN_INT_WINDOW               0x2A4F
#define ESP_GATT_UUID_SCAN_REFRESH                  0x2A31
/**
 * @}
 */

/* 与BTA/BTA_gat_api中的BTA_GATT_PREP_WRITE_xxx相关。小时*/
///来自客户端的属性写入数据类型
typedef enum {
    ESP_GATT_PREP_WRITE_CANCEL    = 0x00,       /*!< 准备写取消*/  /* 与BTA/BTA_gat_api中的BTA_GATT_PREP_WRITE_CANCEL相关。小时*/
    ESP_GATT_PREP_WRITE_EXEC      = 0x01,       /*!< 准备写入执行*/ /* 与BTA/BTA_gat_api中的BTA_GATT_PREP_WRITE_EXEC相关。小时*/
} esp_gatt_prep_write_type;

/* 与BTA/BTA_gat_api中的BTA_GATT_xxx相关。小时*/
/**
 * @brief GATT成功代码和错误代码
 */
typedef enum {
    ESP_GATT_OK                     =   0x0,                    /* 与BTA/BTA_gat_api中的BTA_GATT_OK相关。小时*/
    ESP_GATT_INVALID_HANDLE         =   0x01,   /* 0x0001号*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INVALID_HANDLE相关。小时*/
    ESP_GATT_READ_NOT_PERMIT        =   0x02,   /* 0x0002年*/    /* 与BTA/BTA_gat_api中的BTA_GATT_READ_NOT_PERMIT相关。小时*/
    ESP_GATT_WRITE_NOT_PERMIT       =   0x03,   /* 2002年03月*/    /* 与BTA/BTA_gat_api中的BTA_GATT_WRITE_NOT_PERMIT相关。小时*/
    ESP_GATT_INVALID_PDU            =   0x04,   /* 0x0004年*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INVALID_PDU相关。小时*/
    ESP_GATT_INSUF_AUTHENTICATION   =   0x05,   /* 0x0005年*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INSUF_AUTHENTICATION相关。小时*/
    ESP_GATT_REQ_NOT_SUPPORTED      =   0x06,   /* 2006年9月*/    /* 与BTA/BTA_gat_api中的BTA_GATT_REQ_NOT_SUPPORTED相关。小时*/
    ESP_GATT_INVALID_OFFSET         =   0x07,   /* 2007年9月*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INVALID_OFFSET相关。小时*/
    ESP_GATT_INSUF_AUTHORIZATION    =   0x08,   /* 2008年9月*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INSUF_AUTHORIZATION相关。小时*/
    ESP_GATT_PREPARE_Q_FULL         =   0x09,   /* 2009年9月*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PREPARE_Q_FULL相关。小时*/
    ESP_GATT_NOT_FOUND              =   0x0a,   /* 0x000a*/    /* 与BTA/BTA_gat_api中的BTA_GATT_NOT_FOUND相关。小时*/
    ESP_GATT_NOT_LONG               =   0x0b,   /* 0x000b*/    /* 与BTA/BTA_gat_api中的BTA_GATT_NOT_LONG相关。小时*/
    ESP_GATT_INSUF_KEY_SIZE         =   0x0c,   /* 0x000c*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INSUF_KEY_SIZE相关。小时*/
    ESP_GATT_INVALID_ATTR_LEN       =   0x0d,   /* 0x000d*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INVALID_ATTR_LEN相关。小时*/
    ESP_GATT_ERR_UNLIKELY           =   0x0e,   /* 0x000e*/    /* 与BTA/BTA_gat_api中的BTA_GATT_ERR_UNLIKELY相关。小时*/
    ESP_GATT_INSUF_ENCRYPTION       =   0x0f,   /* 0x000f*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INSUF_ENCRYPTION相关。小时*/
    ESP_GATT_UNSUPPORT_GRP_TYPE     =   0x10,   /* 0x0010位*/    /* 与BTA/BTA_gat_api中的BTA_GATT_UNSUPPORT_GRP_TYPE相关。小时*/
    ESP_GATT_INSUF_RESOURCE         =   0x11,   /* 0x0011年*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INSUF_REOURCE相关。小时*/

    ESP_GATT_NO_RESOURCES           =   0x80,   /* 0x80像素*/    /* 与BTA/BTA_gat_api中的BTA_GATT_NO_RESOURCES相关。小时*/
    ESP_GATT_INTERNAL_ERROR         =   0x81,   /* 0秒81*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INTERNAL_ERROR相关。小时*/
    ESP_GATT_WRONG_STATE            =   0x82,   /* 0秒82*/    /* 与BTA/BTA_gat_api中的BTA_GATT_WRONG_STATE相关。小时*/
    ESP_GATT_DB_FULL                =   0x83,   /* 0秒83*/    /* 与BTA/BTA_gat_api中的BTA_GATT_DB_FULL相关。小时*/
    ESP_GATT_BUSY                   =   0x84,   /* 第84页*/    /* 与BTA/BTA_gat_api中的BTA_GATT_BUSY相关。小时*/
    ESP_GATT_ERROR                  =   0x85,   /* 0至85*/    /* 与BTA/BTA_gat_api中的BTA_GATT_ERROR相关。小时*/
    ESP_GATT_CMD_STARTED            =   0x86,   /* 第86页*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CMD_STARTED相关。小时*/
    ESP_GATT_ILLEGAL_PARAMETER      =   0x87,   /* 第87页*/    /* 与BTA/BTA_gat_api中的BTA_GATT_ILLEGAL_PARAMETER相关。小时*/
    ESP_GATT_PENDING                =   0x88,   /* 0x88像素*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PENDING相关。小时*/
    ESP_GATT_AUTH_FAIL              =   0x89,   /* 第89页*/    /* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_FAIL相关。小时*/
    ESP_GATT_MORE                   =   0x8a,   /* 0x8a*/    /* 与BTA/BTA_gat_api中的BTA_GATT_MORE相关。小时*/
    ESP_GATT_INVALID_CFG            =   0x8b,   /* 0x8b*/    /* 与BTA/BTA_gat_api中的BTA_GATT_INVALID_CFG相关。小时*/
    ESP_GATT_SERVICE_STARTED        =   0x8c,   /* 0x8厘米*/    /* 与BTA/BTA_gat_api中的BTA_GATT_SERVICE_STARTED相关。小时*/
    ESP_GATT_ENCRYPED_MITM          =   ESP_GATT_OK,    /* 与BTA/BTA_gat_api中的BTA_GATT_ENCRYPED_MITM相关。小时*/
    ESP_GATT_ENCRYPED_NO_MITM       =   0x8d,   /* 0x8天*/    /* 与BTA/BTA_gat_api中的BTA_GATT_ENCRYPED_NO_MITM相关。小时*/
    ESP_GATT_NOT_ENCRYPTED          =   0x8e,   /* 0x8e*/    /* 与BTA/BTA_gat_api中的BTA_GATT_NOT_ENCRYPTED相关。小时*/
    ESP_GATT_CONGESTED              =   0x8f,   /* 0x8英尺*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CONGETED相关。小时*/
    ESP_GATT_DUP_REG                =   0x90,   /* 0x90倍*/    /* 与BTA/BTA_gat_api中的BTA_GATT_DUP_REG相关。小时*/
    ESP_GATT_ALREADY_OPEN           =   0x91,   /* 0秒91*/    /* 与BTA/BTA_gat_api中的BTA_GATT_ALREADY_OPEN相关。小时*/
    ESP_GATT_CANCEL                 =   0x92,   /* 0秒92*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CANCEL相关。小时*/
    /* 0xE0~0xFC保留供将来使用*/
    ESP_GATT_STACK_RSP              =   0xe0,   /* 0xe0*/    /* 与BTA/BTA_gat_api中的BTA_GATT_STACK_RSP相关。小时*/
    ESP_GATT_APP_RSP                =   0xe1,   /* 0秒1*/    /* 与BTA/BTA_gat_api中的BTA_GATT_APP_RSP相关。小时*/
    //客户应用程序或堆栈错误导致的错误
    ESP_GATT_UNKNOWN_ERROR          =   0xef,   /* 0参考*/    /* 与BTA/BTA_gat_api中的BTA_GATT_UNKNOWN_ERROR相关。小时*/
    ESP_GATT_CCC_CFG_ERR            =   0xfd,   /* 0xFD客户端特征配置描述符配置不正确*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CCC_CFG_ERR相关。小时*/
    ESP_GATT_PRC_IN_PROGRESS        =   0xfe,   /* 0xFE过程已在进行中*/  /* 与BTA/BTA_gat_api中的BTA_GATT_PRC_IN_PROGRESS相关。小时*/
    ESP_GATT_OUT_OF_RANGE           =   0xff,   /* 0xFFAttribute值超出范围*/    /* 与BTA/BTA_gat_api中的BTA_GATT_OUT_OF_RANGE相关。小时*/
} esp_gatt_status_t;

/* 与BTA/BTA_gat_api中的BTA_GATT_CONN_xxx相关。小时*/
/**
 * @brief Gatt连接原因枚举
 */
typedef enum {
    ESP_GATT_CONN_UNKNOWN = 0,                      /*!< Gatt连接未知*/               /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_UNKNOWN相关。小时*/
    ESP_GATT_CONN_L2C_FAILURE = 1,                  /*!< 一般L2cap故障*/                /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_L2C_FAILURE相关。小时*/
    ESP_GATT_CONN_TIMEOUT = 0x08,                   /*!< 连接超时*/                   /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_TIMEOUT相关。小时*/
    ESP_GATT_CONN_TERMINATE_PEER_USER = 0x13,       /*!< 对等用户终止连接*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_TERMINATE_PEER_USER相关。小时*/
    ESP_GATT_CONN_TERMINATE_LOCAL_HOST = 0x16,      /*!< 连接被本地主机终止*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_TERMINATE_LOCAL_HOST相关。小时*/
    ESP_GATT_CONN_FAIL_ESTABLISH = 0x3e,            /*!< 连接无法建立*/         /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_FAIL_STABLISH相关。小时*/
    ESP_GATT_CONN_LMP_TIMEOUT = 0x22,               /*!< LMP响应tout连接失败*/ /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_LMP_TIMEOUT相关。小时*/
    ESP_GATT_CONN_CONN_CANCEL = 0x0100,             /*!< L2CAP连接已取消*/           /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_CONN_CANCEL相关。小时*/
    ESP_GATT_CONN_NONE = 0x0101                     /*!< 没有要取消的连接*/              /* 与BTA/BTA_gat_api中的BTA_GATT_CONN_NONE相关。小时*/
} esp_gatt_conn_reason_t;

/**
 * @brief Gatt id，包括uuid和实例id
 */
typedef struct {
    esp_bt_uuid_t   uuid;                   /*!< UUID */
    uint8_t         inst_id;                /*!< 实例id*/
} __attribute__((packed)) esp_gatt_id_t;

/**
 * @brief Gatt服务id、include id（uuid和实例id）和主标志
 */
typedef struct {
    esp_gatt_id_t   id;                     /*!< Gatt id，包括uuid和实例*/
    bool            is_primary;             /*!< 此服务是否为主*/
} __attribute__((packed)) esp_gatt_srvc_id_t;

/* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_REQ_xxx相关。小时*/
/**
 * @brief Gatt身份验证请求类型
 */
typedef enum {
    ESP_GATT_AUTH_REQ_NONE                  = 0,                                       /* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_REQ_NONE相关。小时*/
    ESP_GATT_AUTH_REQ_NO_MITM               = 1,   /* 未经身份验证的加密*/    /* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_REQ_NO_MITM相关。小时*/
    ESP_GATT_AUTH_REQ_MITM                  = 2,   /* 经过身份验证的加密*/      /* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_REQ_MITM相关。小时*/
    ESP_GATT_AUTH_REQ_SIGNED_NO_MITM        = 3,                                       /* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_REQ_SIGNED_NO_MITM相关。小时*/
    ESP_GATT_AUTH_REQ_SIGNED_MITM           = 4,                                       /* 与BTA/BTA_gat_api中的BTA_GATT_AUTH_REQ_SIGNED_MITM相关。小时*/
} esp_gatt_auth_req_t;

/* 与BTA/BTA_gat_api中的BTA_GATT_PERM_xx相关。小时*/
/**
 * @brief 属性权限
 */
#define    ESP_GATT_PERM_READ                  (1 << 0)   /* 位0-0x0001*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_READ相关。小时*/
#define    ESP_GATT_PERM_READ_ENCRYPTED        (1 << 1)   /* 位1-0x0002*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_READ_ENCRYPTED相关。小时*/
#define    ESP_GATT_PERM_READ_ENC_MITM         (1 << 2)   /* 位2-0x0004*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_READ_ENC_MITM相关。小时*/
#define    ESP_GATT_PERM_WRITE                 (1 << 4)   /* 位4-0x0010*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_WRITE相关。小时*/
#define    ESP_GATT_PERM_WRITE_ENCRYPTED       (1 << 5)   /* 位5-0x0020*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_WRITE_ENCRYPTED相关。小时*/
#define    ESP_GATT_PERM_WRITE_ENC_MITM        (1 << 6)   /* 位6-0x0040*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_WRITE_ENC_MITM相关。小时*/
#define    ESP_GATT_PERM_WRITE_SIGNED          (1 << 7)   /* 位7-0x0080*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_WRITE_SIGNED相关。小时*/
#define    ESP_GATT_PERM_WRITE_SIGNED_MITM     (1 << 8)   /* 位8-0x0100*/    /* 与BTA/BTA_gat_api中的BTA_GATT_PERM_WRITE_SIGNED_MITM相关。小时*/
#define    ESP_GATT_PERM_READ_AUTHORIZATION    (1 << 9)   /* 位9-0x0200*/
#define    ESP_GATT_PERM_WRITE_AUTHORIZATION   (1 << 10)  /* 位10-0x0400*/
typedef uint16_t esp_gatt_perm_t;

/* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_xxx相关。小时*/
/* 特征特性的定义*/
#define    ESP_GATT_CHAR_PROP_BIT_BROADCAST    (1 << 0)       /* 0x01*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_BROADCAST相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_READ         (1 << 1)       /* 0x02*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_READ相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_WRITE_NR     (1 << 2)       /* 0x04*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_WRITE_NR相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_WRITE        (1 << 3)       /* 0x08*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_WRITE相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_NOTIFY       (1 << 4)       /* 0x10像素*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_NOTIFY相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_INDICATE     (1 << 5)       /* 20倍*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_INDICATE相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_AUTH         (1 << 6)       /* 0x40倍*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_AUTH相关。小时*/
#define    ESP_GATT_CHAR_PROP_BIT_EXT_PROP     (1 << 7)       /* 0x80像素*/    /* 与BTA/BTA_gat_api中的BTA_GATT_CHAR_PROP_BIT_EXT_PROP相关。小时*/
typedef uint8_t esp_gatt_char_prop_t;

///GATT最大属性长度
#define ESP_GATT_MAX_ATTR_LEN   600 //与GATT_MAX_ATTR_LEN相同

typedef enum {
    ESP_GATT_SERVICE_FROM_REMOTE_DEVICE         = 0,                                       /* 与BTA_gatc_int中的BTA_GATTC_SERVICE_INFO_FROM_REMOTE_DEVICE相关。小时*/
    ESP_GATT_SERVICE_FROM_NVS_FLASH             = 1,                                       /* 与BTA_gatc_int中的BTA_GATTC_SERVICE_INFO_FROM_NVS_LASH相关。小时*/
    ESP_GATT_SERVICE_FROM_UNKNOWN               = 2,                                       /* 与BTA_gatc_int.h中的BTA_GATTC_SERVICE_INFO_FROM_UNKNOWN相关*/
} esp_service_source_t;

/**
 * @brief 属性描述（用于创建数据库）
 */
 typedef struct
 {
     uint16_t uuid_length;              /*!< UUID长度*/
     uint8_t  *uuid_p;                  /*!< UUID值*/
     uint16_t perm;                     /*!< 属性权限*/
     uint16_t max_length;               /*!< 元素的最大长度*/
     uint16_t length;                   /*!< 元素的当前长度*/
     uint8_t  *value;                   /*!< 元素值数组*/
 } esp_attr_desc_t;


/**
 * @brief 属性自动响应标志
 */
typedef struct
{
#define ESP_GATT_RSP_BY_APP             0
#define ESP_GATT_AUTO_RSP               1
    /**
     * @brief 如果auto_rsp设置为ESP_GATT_rsp_BY_APP，则表示应用程序将回复写入/读取操作的响应。如果auto_rsp设置为ESP_GATT_auto_rsp，则意味着GATT堆栈将自动回复写入/读取操作的响应。
     */
    uint8_t auto_rsp;
} esp_attr_control_t;


/**
 * @brief 添加到gatt服务器数据库的属性类型
 */
typedef struct
{
    esp_attr_control_t      attr_control;                   /*!< 属性控件类型*/
    esp_attr_desc_t         att_desc;                       /*!< 属性类型*/
} esp_gatts_attr_db_t;


/**
  * @brief 设置属性值类型
  */
typedef struct
{
    uint16_t attr_max_len;                                  /*!<  属性最大值长度*/
    uint16_t attr_len;                                      /*!<  属性当前值长度*/
    uint8_t  *attr_value;                                   /*!<  指向属性值的指针*/
} esp_attr_value_t;


/**
  * @brief Gatt包含服务条目元素
  */
typedef struct
{
    uint16_t start_hdl;                                     /*!< 包含服务的Gatt启动句柄值*/
    uint16_t end_hdl;                                       /*!< 包含服务的门控端句柄值*/
    uint16_t uuid;                                          /*!< 包含服务的Gatt属性值UUID*/
} esp_gatts_incl_svc_desc_t;                                /*!< Gatt包含服务条目元素*/

/**
  * @brief Gatt包括128位服务入口元素
  */
typedef struct
{
    uint16_t start_hdl;                                     /*!< 包含128位服务的Gatt启动句柄值*/
    uint16_t end_hdl;                                       /*!< 包含128位服务的Gatt结束句柄值*/
} esp_gatts_incl128_svc_desc_t;                             /*!< Gatt包括128位服务入口元素*/

///Gatt属性值
typedef struct {
    uint8_t           value[ESP_GATT_MAX_ATTR_LEN];         /*!< Gatt属性值*/
    uint16_t          handle;                               /*!< 门控属性控制柄*/
    uint16_t          offset;                               /*!< Gatt属性值偏移*/
    uint16_t          len;                                  /*!< Gatt属性值长度*/
    uint8_t           auth_req;                             /*!< Gatt身份验证请求*/
} esp_gatt_value_t;

///GATT远程读取请求响应类型
typedef union {
    esp_gatt_value_t attr_value;                            /*!< Gatt属性结构*/
    uint16_t            handle;                             /*!< 门控属性控制柄*/
} esp_gatt_rsp_t;

/**
  * @brief 门控写入类型
  */
typedef enum {
    ESP_GATT_WRITE_TYPE_NO_RSP  =   1,                      /*!< Gatt写入属性无需响应*/
    ESP_GATT_WRITE_TYPE_RSP,                                /*!< Gatt写入属性需要远程响应*/
} esp_gatt_write_type_t;

/**
  * @brief 连接参数信息
  */
typedef struct {
    uint16_t             interval;                         /*!< 连接间隔*/
    uint16_t             latency;                          /*!< 连接的从属延迟（以连接事件数表示）。范围：0x0000到0x01F3*/
    uint16_t             timeout;                          /*!< LE链路的监控超时。范围：0x000A到0x0C80。强制范围：0x000A-0x0C80时间=N 10毫秒时间范围：100毫秒到32秒*/
} esp_gatt_conn_params_t;

#define ESP_GATT_IF_NONE    0xff                            /*!< 如果回调报告gattc_If/gatts_If作为此宏，则表示此事件与任何应用程序都不对应*/

typedef uint8_t    esp_gatt_if_t;                           /*!< Gatt接口类型，Gatt客户端上的不同应用程序使用不同的Gatt_if*/

/**
  * @brief 属性元素的类型
  */
typedef enum {
    ESP_GATT_DB_PRIMARY_SERVICE,                            /*!< 缓存中的Gattc主服务属性类型*/
    ESP_GATT_DB_SECONDARY_SERVICE,                          /*!< 缓存中的Gattc辅助服务属性类型*/
    ESP_GATT_DB_CHARACTERISTIC,                             /*!< 缓存中的Gattc特性属性类型*/
    ESP_GATT_DB_DESCRIPTOR,                                 /*!< 缓存中的Gattc特性描述符属性类型*/
    ESP_GATT_DB_INCLUDED_SERVICE,                           /*!< Gattc在缓存中包含服务属性类型*/
    ESP_GATT_DB_ALL,                                        /*!< Gattc缓存中的所有属性（主服务和辅助服务以及包含服务和字符描述符）类型*/
} esp_gatt_db_attr_type_t;                                  /*!< Gattc属性类型元素*/

/**
  * @brief 读取多重属性
  */
typedef struct {
    uint8_t  num_attr;                                      /*!< 属性的编号*/
    uint16_t handles[ESP_GATT_MAX_READ_MULTI_HANDLES];      /*!< 手柄列表*/
} esp_gattc_multi_t;                                        /*!< gattc多重读取元素*/

/**
  * @brief 数据库属性元素
  */
typedef struct {
    esp_gatt_db_attr_type_t     type;                       /*!< 属性类型*/
    uint16_t                    attribute_handle;           /*!< 属性句柄，它对所有类型都有效*/
    uint16_t                    start_handle;               /*!< 服务启动句柄，仅当类型=ESP_GATT_DB_PRIMARY_service或ESP_GATT_DB_SECONDARY_service时有效*/
    uint16_t                    end_handle;                 /*!< 服务结束句柄，仅当类型=ESP_GATT_DB_PRIMARY_service或ESP_GATT_DB_SECONDARY_service时有效*/
    esp_gatt_char_prop_t        properties;                 /*!< 特性属性，仅当类型=ESP_GATT_DB_CHARACTIC时有效*/
    esp_bt_uuid_t               uuid;                       /*!< 属性uuid，它对所有类型都有效*/
} esp_gattc_db_elem_t;                                      /*!< 缓存中的gattc服务数据库元素*/

/**
  * @brief 服务元素
  */
typedef struct {
    bool                        is_primary;                 /*!< 如果服务是主要服务，则服务标志为true，否则为次要服务*/
    uint16_t                    start_handle;               /*!< 服务的启动句柄*/
    uint16_t                    end_handle;                 /*!< 服务的结束句柄*/
    esp_bt_uuid_t               uuid;                       /*!< 服务的uuid*/
} esp_gattc_service_elem_t;                                 /*!< gattc服务元素*/

/**
  * @brief 特征元素
  */
typedef struct {
    uint16_t                    char_handle;                /*!< 特色手柄*/
    esp_gatt_char_prop_t        properties;                 /*!< 特性特性*/
    esp_bt_uuid_t               uuid;                       /*!< 特征uuid*/
} esp_gattc_char_elem_t;                                    /*!< gattc特征元素*/

/**
  * @brief 描述符元素
  */
typedef struct {
    uint16_t                   handle;                      /*!< 特征描述符句柄*/
    esp_bt_uuid_t              uuid;                        /*!< 特征描述符uuid*/
} esp_gattc_descr_elem_t;                                   /*!< gattc描述符类型元素*/

/**
  * @brief 包含服务元素
  */
typedef struct {
    uint16_t                   handle;                      /*!< include服务当前属性句柄*/
    uint16_t                   incl_srvc_s_handle;          /*!< 已包含的服务的启动句柄*/
    uint16_t                   incl_srvc_e_handle;          /*!< 已包含的服务的结束句柄*/
    esp_bt_uuid_t              uuid;                        /*!< 包含服务uuid*/
} esp_gattc_incl_svc_elem_t;                                /*!< gattc include服务元素*/


#ifdef __cplusplus
}
#endif

#endif /* __ESP_GATT_DEFS_H__ */

