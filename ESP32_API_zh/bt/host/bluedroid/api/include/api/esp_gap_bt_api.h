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

#ifndef __ESP_GAP_BT_API_H__
#define __ESP_GAP_BT_API_H__

#include <stdint.h>
#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

///RSSI阈值
#define ESP_BT_GAP_RSSI_HIGH_THRLD  -20             /*!< 高RSSI阈值*/
#define ESP_BT_GAP_RSSI_LOW_THRLD   -45             /*!< 低RSSI阈值*/

///设备类别
typedef struct {
    uint32_t      reserved_2: 2;                    /*!< 未定义*/
    uint32_t      minor: 6;                         /*!< 次要等级*/
    uint32_t      major: 5;                         /*!< 主要等级*/
    uint32_t      service: 11;                      /*!< 服务等级*/
    uint32_t      reserved_8: 8;                    /*!< 未定义*/
} esp_bt_cod_t;

///设备设置类别
typedef enum {
    ESP_BT_SET_COD_MAJOR_MINOR     = 0x01,          /*!< 覆盖主要类、次要类*/
    ESP_BT_SET_COD_SERVICE_CLASS   = 0x02,          /*!< 设置输入中的位，当前位将保留*/
    ESP_BT_CLR_COD_SERVICE_CLASS   = 0x04,          /*!< 清除输入中的位，其他位将保留*/
    ESP_BT_SET_COD_ALL             = 0x08,          /*!< 覆盖major、minor，设置服务类中的位*/
    ESP_BT_INIT_COD                = 0x0a,          /*!< 覆盖主要、次要和服务类*/
} esp_bt_cod_mode_t;

#define ESP_BT_GAP_AFH_CHANNELS_LEN     10
typedef uint8_t esp_bt_gap_afh_channels[ESP_BT_GAP_AFH_CHANNELS_LEN];


///可发现性和可连接性模式
typedef enum {
    ESP_BT_NON_CONNECTABLE,             /*!< 不可连接*/
    ESP_BT_CONNECTABLE,                 /*!< 可连接的*/
} esp_bt_connection_mode_t;

typedef enum {
    ESP_BT_NON_DISCOVERABLE,            /*!< 不可发现*/
    ESP_BT_LIMITED_DISCOVERABLE,        /*!< 有限的可发现性*/
    ESP_BT_GENERAL_DISCOVERABLE,        /*!< 一般可发现*/
} esp_bt_discovery_mode_t;

///蓝牙设备属性类型
typedef enum {
    ESP_BT_GAP_DEV_PROP_BDNAME = 1,                 /*!< 蓝牙设备名称，值类型为int8_t[]*/
    ESP_BT_GAP_DEV_PROP_COD,                        /*!< 设备类别，值类型为uint32_t*/
    ESP_BT_GAP_DEV_PROP_RSSI,                       /*!< 接收信号强度指示，值类型为int8_t，范围为-128至127*/
    ESP_BT_GAP_DEV_PROP_EIR,                        /*!< 扩展查询响应，值类型为uint8_t[]*/
} esp_bt_gap_dev_prop_type_t;

///蓝牙设备名称的最大字节数
#define ESP_BT_GAP_MAX_BDNAME_LEN             (248)

///EIR重要部分的最大尺寸
#define ESP_BT_GAP_EIR_DATA_LEN               (240)

///蓝牙设备属性描述符
typedef struct {
    esp_bt_gap_dev_prop_type_t type;                /*!< 设备属性类型*/
    int len;                                        /*!< 设备属性值长度*/
    void *val;                                      /*!< 设备属性值*/
} esp_bt_gap_dev_prop_t;

///扩展查询响应数据类型
#define ESP_BT_EIR_TYPE_FLAGS                   0x01      /*!< 带有BR/EDR和LE支持等信息的标志*/
#define ESP_BT_EIR_TYPE_INCMPL_16BITS_UUID      0x02      /*!< 16位服务UUID列表不完整*/
#define ESP_BT_EIR_TYPE_CMPL_16BITS_UUID        0x03      /*!< 16位服务UUID的完整列表*/
#define ESP_BT_EIR_TYPE_INCMPL_32BITS_UUID      0x04      /*!< 32位服务UUID列表不完整*/
#define ESP_BT_EIR_TYPE_CMPL_32BITS_UUID        0x05      /*!< 32位服务UUID的完整列表*/
#define ESP_BT_EIR_TYPE_INCMPL_128BITS_UUID     0x06      /*!< 128位服务UUID列表不完整*/
#define ESP_BT_EIR_TYPE_CMPL_128BITS_UUID       0x07      /*!< 128位服务UUID的完整列表*/
#define ESP_BT_EIR_TYPE_SHORT_LOCAL_NAME        0x08      /*!< 缩短的本地名称*/
#define ESP_BT_EIR_TYPE_CMPL_LOCAL_NAME         0x09      /*!< 完整的本地名称*/
#define ESP_BT_EIR_TYPE_TX_POWER_LEVEL          0x0a      /*!< Tx功率电平，值为-127至127范围内的1个八位字节，单位为dBm*/
#define ESP_BT_EIR_TYPE_URL                     0x24      /*!< 统一资源标识符*/
#define ESP_BT_EIR_TYPE_MANU_SPECIFIC           0xff      /*!< 制造商特定数据*/
#define  ESP_BT_EIR_TYPE_MAX_NUM                12        /*!< EIR类型的最大数量*/

typedef uint8_t esp_bt_eir_type_t;



/* ESP_BT_EIR_FLAG位定义*/
#define ESP_BT_EIR_FLAG_LIMIT_DISC         (0x01 << 0)
#define ESP_BT_EIR_FLAG_GEN_DISC           (0x01 << 1)
#define ESP_BT_EIR_FLAG_BREDR_NOT_SPT      (0x01 << 2)
#define ESP_BT_EIR_FLAG_DMT_CONTROLLER_SPT (0x01 << 3)
#define ESP_BT_EIR_FLAG_DMT_HOST_SPT       (0x01 << 4)

#define ESP_BT_EIR_MAX_LEN                  240
///EIR数据内容，根据“蓝牙核心规范补充”
typedef struct {
    bool                    fec_required;           /*!< 是否需要FEC，默认为true*/
    bool                    include_txpower;        /*!< EIR数据包括TX功率，默认为假*/
    bool                    include_uuid;           /*!< EIR数据包括UUID，默认为false*/
    uint8_t                 flag;                   /*!< EIR标志，有关详细信息，请参阅ESP_BT_EIR_FLAG，如果EIR默认为0，则不包含标志*/
    uint16_t                manufacturer_len;       /*!< 制造商数据长度，默认为0*/
    uint8_t                 *p_manufacturer_data;   /*!< 制造商数据点*/
    uint16_t                url_len;                /*!< URL长度，默认为0*/
    uint8_t                 *p_url;                 /*!< URL点*/
} esp_bt_eir_data_t;

///设备类别的主要服务类别字段，可设置多位
typedef enum {
    ESP_BT_COD_SRVC_NONE                     =     0,    /*!< 无表示无效值*/
    ESP_BT_COD_SRVC_LMTD_DISCOVER            =   0x1,    /*!< 有限的可发现模式*/
    ESP_BT_COD_SRVC_POSITIONING              =   0x8,    /*!< 定位（位置标识）*/
    ESP_BT_COD_SRVC_NETWORKING               =  0x10,    /*!< 网络，例如LAN、Ad-hoc*/
    ESP_BT_COD_SRVC_RENDERING                =  0x20,    /*!< 渲染，例如打印、扬声器*/
    ESP_BT_COD_SRVC_CAPTURING                =  0x40,    /*!< 捕获，例如扫描仪、麦克风*/
    ESP_BT_COD_SRVC_OBJ_TRANSFER             =  0x80,    /*!< 对象传输，例如v-Inbox、v-Folder*/
    ESP_BT_COD_SRVC_AUDIO                    = 0x100,    /*!< 音频，例如扬声器、麦克风、耳机服务*/
    ESP_BT_COD_SRVC_TELEPHONY                = 0x200,    /*!< 电话，例如无绳电话、调制解调器、耳机服务*/
    ESP_BT_COD_SRVC_INFORMATION              = 0x400,    /*!< 信息，如WEB服务器、WAP服务器*/
} esp_bt_cod_srvc_t;

typedef enum{
    ESP_BT_PIN_TYPE_VARIABLE = 0,                       /*!< 请参阅BTM_PIN_TYPE_VARIABLE*/
    ESP_BT_PIN_TYPE_FIXED    = 1,                       /*!< 参考BTM_PIN_TYPE_FIXED*/
} esp_bt_pin_type_t;

#define ESP_BT_PIN_CODE_LEN        16                   /*!< 最大引脚代码长度*/
typedef uint8_t esp_bt_pin_code_t[ESP_BT_PIN_CODE_LEN]; /*!< 引脚代码（最多128位）MSB为0*/

typedef enum {
    ESP_BT_SP_IOCAP_MODE = 0,                            /*!< 设置IO模式*/
    //ESP_BT_SP_OOB_DATA, //TODO                         /*!< 设置OOB数据*/
} esp_bt_sp_param_t;

/* 与堆栈/BTM_api中的BTM_IO_CAP_xxx相关。小时*/
#define ESP_BT_IO_CAP_OUT                      0        /*!< 仅显示*/         /* 与堆栈/BTM_api中的BTM_IO_CAP_OUT相关。小时*/
#define ESP_BT_IO_CAP_IO                       1        /*!< 显示是否*/        /* 与堆栈/BTM_api中的BTM_IO_CAP_IO相关。小时*/
#define ESP_BT_IO_CAP_IN                       2        /*!< 仅键盘*/        /* 与堆栈/BTM_api中的BTM_IO_CAP_IN相关。小时*/
#define ESP_BT_IO_CAP_NONE                     3        /*!< 无输入无输出*/     /* 与堆栈/BTM_api中的BTM_IO_CAP_NONE相关。小时*/
typedef uint8_t esp_bt_io_cap_t;                        /*!< 信息作战能力的组合*/


/* BTM电源管理器模式*/
#define ESP_BT_PM_MD_ACTIVE                 0x00        /*!< 活动模式*/
#define ESP_BT_PM_MD_HOLD                   0x01        /*!< 保持模式*/
#define ESP_BT_PM_MD_SNIFF                  0x02        /*!< 嗅探模式*/
#define ESP_BT_PM_MD_PARK                   0x03        /*!< Park状态*/
typedef uint8_t esp_bt_pm_mode_t;



///主要服务类别字段的位
#define ESP_BT_COD_SRVC_BIT_MASK              (0xffe000) /*!< 主要服务位掩码*/
#define ESP_BT_COD_SRVC_BIT_OFFSET            (13)       /*!< 主要服务位偏移*/

///设备类别的主要设备类别字段
typedef enum {
    ESP_BT_COD_MAJOR_DEV_MISC                = 0,    /*!< 混杂的*/
    ESP_BT_COD_MAJOR_DEV_COMPUTER            = 1,    /*!< 计算机*/
    ESP_BT_COD_MAJOR_DEV_PHONE               = 2,    /*!< 电话（蜂窝电话、无绳电话、付费电话、调制解调器*/
    ESP_BT_COD_MAJOR_DEV_LAN_NAP             = 3,    /*!< LAN，网络接入点*/
    ESP_BT_COD_MAJOR_DEV_AV                  = 4,    /*!< 音频/视频（耳机、扬声器、立体声、视频显示器、VCR*/
    ESP_BT_COD_MAJOR_DEV_PERIPHERAL          = 5,    /*!< 外围设备（鼠标、操纵杆、键盘）*/
    ESP_BT_COD_MAJOR_DEV_IMAGING             = 6,    /*!< 成像（打印机、扫描仪、照相机、显示器*/
    ESP_BT_COD_MAJOR_DEV_WEARABLE            = 7,    /*!< 可穿戴的*/
    ESP_BT_COD_MAJOR_DEV_TOY                 = 8,    /*!< 玩具*/
    ESP_BT_COD_MAJOR_DEV_HEALTH              = 9,    /*!< 健康*/
    ESP_BT_COD_MAJOR_DEV_UNCATEGORIZED       = 31,   /*!< 未分类：未指定设备*/
} esp_bt_cod_major_dev_t;

///主要设备类别字段的位
#define ESP_BT_COD_MAJOR_DEV_BIT_MASK         (0x1f00) /*!< 主要设备位掩码*/
#define ESP_BT_COD_MAJOR_DEV_BIT_OFFSET       (8)      /*!< 主要设备位偏移*/

///次要设备类别字段的位
#define ESP_BT_COD_MINOR_DEV_BIT_MASK         (0xfc)   /*!< 次要设备位掩码*/
#define ESP_BT_COD_MINOR_DEV_BIT_OFFSET       (2)      /*!< 次要设备位偏移*/

///格式类型的位
#define ESP_BT_COD_FORMAT_TYPE_BIT_MASK       (0x03)   /*!< 格式类型位掩码*/
#define ESP_BT_COD_FORMAT_TYPE_BIT_OFFSET     (0)      /*!< 格式类型位偏移*/

///设备格式类型1的类别
#define ESP_BT_COD_FORMAT_TYPE_1              (0x00)

/**蓝牙设备发现状态*/
typedef enum {
    ESP_BT_GAP_DISCOVERY_STOPPED,                   /*!< 设备发现已停止*/
    ESP_BT_GAP_DISCOVERY_STARTED,                   /*!< 设备发现已启动*/
} esp_bt_gap_discovery_state_t;

///BT GAP回调事件
typedef enum {
    ESP_BT_GAP_DISC_RES_EVT = 0,                    /*!< 设备发现结果事件*/
    ESP_BT_GAP_DISC_STATE_CHANGED_EVT,              /*!< 发现状态已更改事件*/
    ESP_BT_GAP_RMT_SRVCS_EVT,                       /*!< 获取远程服务事件*/
    ESP_BT_GAP_RMT_SRVC_REC_EVT,                    /*!< 获取远程服务记录事件*/
    ESP_BT_GAP_AUTH_CMPL_EVT,                       /*!< 身份验证完成事件*/
    ESP_BT_GAP_PIN_REQ_EVT,                         /*!< 传统配对Pin码请求*/
    ESP_BT_GAP_CFM_REQ_EVT,                         /*!< 安全简单配对用户确认请求。*/
    ESP_BT_GAP_KEY_NOTIF_EVT,                       /*!< 安全简单配对密钥通知*/
    ESP_BT_GAP_KEY_REQ_EVT,                         /*!< 安全简单配对密钥请求*/
    ESP_BT_GAP_READ_RSSI_DELTA_EVT,                 /*!< 读取rssi事件*/
    ESP_BT_GAP_CONFIG_EIR_DATA_EVT,                 /*!< 配置EIR数据事件*/
    ESP_BT_GAP_SET_AFH_CHANNELS_EVT,                /*!< 设置AFH通道事件*/
    ESP_BT_GAP_READ_REMOTE_NAME_EVT,                /*!< 读取远程名称事件*/
    ESP_BT_GAP_MODE_CHG_EVT,
    ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT,         /*!< 移除键合装置完成事件*/
    ESP_BT_GAP_QOS_CMPL_EVT,                        /*!< QOS完成事件*/
    ESP_BT_GAP_EVT_MAX,
} esp_bt_gap_cb_event_t;

/**查询模式*/
typedef enum {
    ESP_BT_INQ_MODE_GENERAL_INQUIRY,                /*!< 一般查询模式*/
    ESP_BT_INQ_MODE_LIMITED_INQUIRY,                /*!< 有限查询模式*/
} esp_bt_inq_mode_t;

/**最小和最大查询长度*/
#define ESP_BT_GAP_MIN_INQ_LEN                (0x01)  /*!< 最小查询持续时间，单位为1.28s*/
#define ESP_BT_GAP_MAX_INQ_LEN                (0x30)  /*!< 最大查询持续时间，单位为1.28s*/

///GAP状态回调参数
typedef union {
    /**
     * @brief ESP_BT_GAP_DISC_RES_EVT
     */
    struct disc_res_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        int num_prop;                          /*!< 获得的属性数*/
        esp_bt_gap_dev_prop_t *prop;           /*!< 从新设备中发现的属性*/
    } disc_res;                                /*!< 发现结果参数结构*/

    /**
     * @brief  ESP_BT_GAP_DISC_STATE_CHANGED_EVT
     */
    struct disc_state_changed_param {
        esp_bt_gap_discovery_state_t state;    /*!< 发现状态*/
    } disc_st_chg;                             /*!< 发现状态已更改的参数结构*/

    /**
     * @brief ESP_BT_GAP_RMT_SRVCS_EVT
     */
    struct rmt_srvcs_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        esp_bt_status_t stat;                  /*!< 服务搜索状态*/
        int num_uuids;                         /*!< UUID_list中的UUID数*/
        esp_bt_uuid_t *uuid_list;              /*!< 远程设备的服务UUID列表*/
    } rmt_srvcs;                               /*!< 远程设备参数结构的服务*/

    /**
     * @brief ESP_BT_GAP_RMT_SRVC_REC_EVT
     */
    struct rmt_srvc_rec_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        esp_bt_status_t stat;                  /*!< 服务搜索状态*/
    } rmt_srvc_rec;                            /*!< 远程设备参数结构中的特定服务记录*/

    /**
     * @brief ESP_BT_GAP_READ_RSSI_DELTA_EVT *
     */
    struct read_rssi_delta_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        esp_bt_status_t stat;                  /*!< 读取rssi状态*/
        int8_t rssi_delta;                     /*!< rssi delta值范围-128~127，零值表示rssi在黄金接收功率范围内，黄金接收功率从ESP_BT_GAP_RRSSI_LOW_THRLD到ESP_BT_GAB_RRSSI_HIGH_THRLD*/
    } read_rssi_delta;                         /*!< 读取rssi参数结构*/

    /**
     * @brief ESP_BT_GAP_CONFIG_EIR_DATA_EVT *
     */
    struct config_eir_data_param {
        esp_bt_status_t stat;                                   /*!< 配置EIR状态：ESP_BT_status_SUCCESS：配置成功ESP_BT_STAUS_EIR_TOO_LARGE：EIR数据大于240B。EIR可能不包含全部数据。其他：失败
                                                                */
        uint8_t eir_type_num;                                   /*!< EIR类型中EIR类型的数量*/
        esp_bt_eir_type_t eir_type[ESP_BT_EIR_TYPE_MAX_NUM];    /*!< EIR类型中的EIR类型*/
    } config_eir_data;                                          /*!< 配置EIR数据*/

    /**
     * @brief ESP_BT_GAP_AUTH_CMPL_EVT
     */
    struct auth_cmpl_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        esp_bt_status_t stat;                  /*!< 身份验证完成状态*/
        uint8_t device_name[ESP_BT_GAP_MAX_BDNAME_LEN + 1]; /*!< 设备名称*/
    } auth_cmpl;                               /*!< 身份验证完成参数结构*/

    /**
     * @brief ESP_BT_GAP_PIN_REQ_EVT
     */
    struct pin_req_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        bool min_16_digit;                     /*!< 如果返回的引脚必须至少为16位，则为TRUE*/
    } pin_req;                                 /*!< pin请求参数结构*/

    /**
     * @brief ESP_BT_GAP_CFM_REQ_EVT
     */
    struct cfm_req_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        uint32_t num_val;                      /*!< 用于比较的数值。*/
    } cfm_req;                                 /*!< 确认请求参数结构*/

    /**
     * @brief ESP_BT_GAP_KEY_NOTIF_EVT
     */
    struct key_notif_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        uint32_t passkey;                      /*!< 密钥项的数值。*/
    } key_notif;                               /*!< passkey notif参数结构*/

    /**
     * @brief ESP_BT_GAP_KEY_REQ_EVT
     */
    struct key_req_param {
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
    } key_req;                                 /*!< passkey请求参数结构*/

    /**
     * @brief ESP_BT_GAP_SET_AFH_CHANNELS_EVT
     */
    struct set_afh_channels_param {
        esp_bt_status_t stat;                  /*!< 设置AFH信道状态*/
    } set_afh_channels;                        /*!< 设置AFH通道参数结构*/

    /**
     * @brief ESP_BT_GAP_READ_REMOTE_NAME_EVT
     */
    struct read_rmt_name_param {
        esp_bt_status_t stat;                  /*!< 读取远程名称状态*/
        uint8_t rmt_name[ESP_BT_GAP_MAX_BDNAME_LEN + 1]; /*!< 远程设备名称*/
    } read_rmt_name;                        /*!< 读取远程名称参数结构*/

    /**
     * @brief ESP_BT_GAP_MODE_CHG_EVT
     */
    struct mode_chg_param {
        esp_bd_addr_t bda;                      /*!< 远程蓝牙设备地址*/
        esp_bt_pm_mode_t mode;                  /*!< PM模式*/
    } mode_chg;                                 /*!< 模式更改事件参数结构*/

    /**
     * @brief ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT
     */
    struct bt_remove_bond_dev_cmpl_evt_param {
        esp_bd_addr_t bda;                          /*!< 远程蓝牙设备地址*/
        esp_bt_status_t status;                     /*!< 指示移除键合设备操作成功状态*/
    }remove_bond_dev_cmpl;                           /*!< ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT的事件参数*/

    /**
     * @brief ESP_BT_GAP_QOS_CMPL_EVT
     */
    struct qos_cmpl_param {
        esp_bt_status_t stat;                  /*!< QoS状态*/
        esp_bd_addr_t bda;                     /*!< 远程蓝牙设备地址*/
        uint32_t t_poll;                       /*!< 轮询间隔，ACL逻辑传输上从主机到特定从机的传输之间的最长时间。单位为0.625ms。*/
    } qos_cmpl;                                /*!< QoS完整参数结构*/
} esp_bt_gap_cb_param_t;

/**
 * @brief           蓝牙GAP回调函数类型
 *
 * @param           event ：事件类型
 *
 * @param           param ：指向回调参数的指针
 */
typedef void (* esp_bt_gap_cb_t)(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

/**
 * @brief           获取COD的主要服务领域
 *
 * @param[in]       cod: 设备类别
 *
 * @return          主要服务位
 */
static inline uint32_t esp_bt_gap_get_cod_srvc(uint32_t cod)
{
    return (cod & ESP_BT_COD_SRVC_BIT_MASK) >> ESP_BT_COD_SRVC_BIT_OFFSET;
}

/**
 * @brief           获取COD的主要设备字段
 *
 * @param[in]       cod: 设备类别
 *
 * @return          主要设备位
 */
static inline uint32_t esp_bt_gap_get_cod_major_dev(uint32_t cod)
{
    return (cod & ESP_BT_COD_MAJOR_DEV_BIT_MASK) >> ESP_BT_COD_MAJOR_DEV_BIT_OFFSET;
}

/**
 * @brief           获取COD的次要服务字段
 *
 * @param[in]       cod: 设备类别
 *
 * @return          次要服务位
 */
static inline uint32_t esp_bt_gap_get_cod_minor_dev(uint32_t cod)
{
    return (cod & ESP_BT_COD_MINOR_DEV_BIT_MASK) >> ESP_BT_COD_MINOR_DEV_BIT_OFFSET;
}

/**
 * @brief           获取COD的格式类型
 *
 * @param[in]       cod: 设备类别
 *
 * @return          格式类型
 */
static inline uint32_t esp_bt_gap_get_cod_format_type(uint32_t cod)
{
    return (cod & ESP_BT_COD_FORMAT_TYPE_BIT_MASK);
}

/**
 * @brief           决定COD的完整性
 *
 * @param[in]       cod: 设备类别
 *
 * @return
 *                  -如果cod有效，则为true
 *                  -假他者
 */
static inline bool esp_bt_gap_is_valid_cod(uint32_t cod)
{
    if (esp_bt_gap_get_cod_format_type(cod) == ESP_BT_COD_FORMAT_TYPE_1 &&
            esp_bt_gap_get_cod_srvc(cod) != ESP_BT_COD_SRVC_NONE) {
        return true;
    }

    return false;
}

/**
 * @brief           寄存器回调函数。应在esp_bluedroid_enable（）成功完成后调用此函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_register_callback(esp_bt_gap_cb_t callback);

/**
 * @brief           为传统蓝牙设置可发现性和可连接性模式。应在esp_bluedroid_enable（）成功完成后调用此函数
 *
 * @param[in]       c_mode ：esp_bt_connection_mode_t的枚举之一
 *
 * @param[in]       d_mode ：esp_bt_discovery_mode_t的枚举之一
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_ARG：如果参数无效
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_set_scan_mode(esp_bt_connection_mode_t c_mode, esp_bt_discovery_mode_t d_mode);

/**
 * @brief           此功能启动查询和名称查找。应在esp_bluedroid_enable（）成功完成后调用此函数。当查询停止并且缓存的结果不包含设备名称时，名称发现将连接到对等目标以获取设备名称。当Inquriry启动或名称发现完成时，将使用esp_bt_gap_DISC_STATE_CHANGED_EVT调用esp_bt_gap_cb_t。每当获得两种类型的发现结果时，esp_bt_gap_cb_t。
 *
 * @param[in]       mode -查询模式
 *
 * @param[in]       inq_len -以1.28秒为单位的查询持续时间，范围从0x01到0x30。此参数仅指定查询过程的总持续时间，
 *                          -当该时间到期时，查询将停止。
 *
 * @param[in]       num_rsps -在暂停查询之前可以接收的响应数，值0表示响应数不受限制。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_ERR_INVALID_ARG：如果提供了无效参数
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_start_discovery(esp_bt_inq_mode_t mode, uint8_t inq_len, uint8_t num_rsps);

/**
 * @brief           取消查询和名称发现。应在esp_bluedroid_enable（）成功完成后调用此函数。如果通过调用此函数取消查询或名称发现，则将使用esp_bt_gap_DISC_STATE_CHANGED_EVT调用esp_bt_gap_cb_t。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_cancel_discovery(void);

/**
 * @brief           启动SDP以获取远程服务。应在esp_bluedroid_enable（）成功完成后调用此函数。在服务发现结束后，将使用esp_bt_gap_RMT_SRVCS_EVT调用esp_bt_gap_cb_t。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_get_remote_services(esp_bd_addr_t remote_bda);

/**
 * @brief           启动SDP以在远程设备上查找与uuid匹配的服务。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 *                  服务发现结束后，将使用esp_bt_gap_RMT_SRVC_REC_EVT调用esp_bt_gap_cb_t
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_get_remote_service_record(esp_bd_addr_t remote_bda, esp_bt_uuid_t *uuid);

/**
 * @brief           调用此函数以获取特定类型的EIR数据。
 *
 * @param[in]       eir -要解析的原始eir数据指针
 * @param[in]       type   -特定EIR数据类型
 * @param[out]      length -返回EIR数据的长度，不包括长度和数据类型的字段
 *
 * @return          eir数据起始位置的指针，不包括eir数据类型，如果找不到，则为NULL
 *
 */
uint8_t *esp_bt_gap_resolve_eir_data(uint8_t *eir, esp_bt_eir_type_t type, uint8_t *length);

/**
 * @brief           调用此函数以配置EIR数据。
 *
 *                  在配置EIR结束后，将使用esp_bt_gap_CONFIG_EIR_DATA_EVT调用esp_bt_gap_cb_t。
 *
 * @param[in]       eir_data -EIR数据内容指针
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_ERR_INVALID_ARG：如果参数无效
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_config_eir_data(esp_bt_eir_data_t *eir_data);

/**
 * @brief           调用此函数以设置设备类别。设置COD结束后，将使用esp_bt_gap_SET_COD_EVT调用结构esp_bt_gap_cb_t。某些配置文件对设备类别有特殊限制，更改可能导致这些配置文件无法工作。
 *
 * @param[in]       cod -设备类别
 * @param[in]       mode -设置模式
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_ERR_INVALID_ARG：如果参数无效
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_set_cod(esp_bt_cod_t cod, esp_bt_cod_mode_t mode);

/**
 * @brief           调用此函数以获取设备类。
 *
 * @param[out]      cod -设备类别
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_bt_gap_get_cod(esp_bt_cod_t *cod);

/**
 * @brief           连接后，调用此函数按地址读取RSSI增量。ESP_BT_GAP_READ_RSSI_DELTA_EVT返回的RSSI值。
 *
 *
 * @param[in]       remote_addr -远程设备地址，对应于某个连接句柄
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_gap_read_rssi_delta(esp_bd_addr_t remote_addr);

/**
* @brief           从对等设备的安全数据库列表中删除设备。
*
* @param[in]       bd_addr ：对等设备的BD地址
*
* @return          -ESP_OK：成功
*                  -ESP_FAIL:失败
*
*/
esp_err_t esp_bt_gap_remove_bond_device(esp_bd_addr_t bd_addr);

/**
* @brief           从对等设备的安全数据库列表中获取设备编号。它将立即返回设备绑定编号。
*
* @return          ->=0：键合设备编号
*                  -ESP_FAIL:失败
*
*/
int esp_bt_gap_get_bond_device_num(void);

/**
* @brief           从对等设备的安全数据库列表中获取设备。它将立即返回设备绑定信息。
*
* @param[inout]    dev_num: 指示dev_list数组（缓冲区）大小作为输入。如果dev_num足够大，则表示输出的实际数量。建议dev_num值等于esp_ble_get_bond_device_num（）。
*
* @param[out]      dev_list: “esp_bd_addr_t”类型的数组（缓冲区）。用于存储绑定的设备地址。dev_list应由调用此API的人分配。
*
* @return
*                  -ESP_OK：成功
*                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                  -ESP_FAIL：其他
*/
esp_err_t esp_bt_gap_get_bond_device_list(int *dev_num, esp_bd_addr_t *dev_list);

/**
* @brief            为传统配对设置引脚类型和默认引脚代码。
*
* @param[in]        pin_type:       使用可变或固定销。如果pin_type为ESP_BT_pin_type_VARIABLE，则pin_code和pin_code_len将被忽略，并且当控制请求pin代码时，ESP_BT_GAP_pin_REQ_EVT将出现。否则，将使用固定的pin代码，而不回调给用户。
*
* @param[in]        pin_code_len:   pin_code的长度
*
* @param[in]        pin_code:       Pin_code（引脚代码）
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*/
esp_err_t esp_bt_gap_set_pin(esp_bt_pin_type_t pin_type, uint8_t pin_code_len, esp_bt_pin_code_t pin_code);

/**
* @brief            当ESP_BT_GAP_pin_REQ_EVT即将到来时，向对等设备回复pin_code以进行传统配对。
*
* @param[in]        bd_addr:        对等方的BD地址
*
* @param[in]        accept:         Pin_code回复成功或被拒绝。
*
* @param[in]        pin_code_len:   pin_code的长度
*
* @param[in]        pin_code:       Pin_code（引脚代码）
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*/
esp_err_t esp_bt_gap_pin_reply(esp_bd_addr_t bd_addr, bool accept, uint8_t pin_code_len, esp_bt_pin_code_t pin_code);

#if (BT_SSP_INCLUDED == TRUE)
/**
* @brief            设置GAP安全参数值。替代默认值。
*
* @param[in]        param_type ：要设置的参数的类型
*
* @param[in]        value  ：参数值
*
* @param[in]        len ：参数值的长度
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_bt_gap_set_security_param(esp_bt_sp_param_t param_type,
                                        void *value, uint8_t len);

/**
* @brief            在传统连接阶段向对等设备回复密钥值。
*
* @param[in]        bd_addr ：对等方的BD地址
*
* @param[in]        accept ：密钥输入成功或被拒绝。
*
* @param[in]        passkey ：密钥值，必须是6位数字，可以以0开头。
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_bt_gap_ssp_passkey_reply(esp_bd_addr_t bd_addr, bool accept, uint32_t passkey);


/**
* @brief            在传统连接阶段向对等设备回复确认值。
*
* @param[in]        bd_addr ：对等设备的BD地址
*
* @param[in]        accept ：要比较的数字相同或不同
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_bt_gap_ssp_confirm_reply(esp_bd_addr_t bd_addr, bool accept);

#endif /*(BT_SSP_INCLUDED == TRUE)*/

/**
* @brief            设置AFH通道
*
* @param[in]        channels ：第n个此类字段（在0到78的范围内）包含通道n的值：0表示通道n坏。1表示信道n未知。保留最高有效位，并将其设置为0。至少20个通道应标记为未知。
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_bt_gap_set_afh_channels(esp_bt_gap_afh_channels channels);

/**
* @brief            读取远程设备名称
*
* @param[in]        remote_bda: 远程设备的地址
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_bt_gap_read_remote_name(esp_bd_addr_t remote_bda);

/**
* @brief            配置服务质量
*
* @param[in]        remote_bda: 远程设备的地址
* @param[in]        t_poll:     轮询间隔，ACL逻辑传输上从主机到特定从机的传输之间的最长时间。单位为0.625ms
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_bt_gap_set_qos(esp_bd_addr_t remote_bda, uint32_t t_poll);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_GAP_BT_API_H__ */

