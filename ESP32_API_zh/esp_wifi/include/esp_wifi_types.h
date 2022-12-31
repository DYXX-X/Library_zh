/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef __ESP_WIFI_TYPES_H__
#define __ESP_WIFI_TYPES_H__

#include "esp_private/esp_wifi_types_private.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WIFI_MODE_NULL = 0,  /**<空模式*/
    WIFI_MODE_STA,       /**<WiFi站模式*/
    WIFI_MODE_AP,        /**<WiFi软AP模式*/
    WIFI_MODE_APSTA,     /**<WiFi站+软AP模式*/
    WIFI_MODE_MAX
} wifi_mode_t;

typedef enum {
    WIFI_IF_STA = ESP_IF_WIFI_STA,
    WIFI_IF_AP  = ESP_IF_WIFI_AP,
} wifi_interface_t;

#define WIFI_OFFCHAN_TX_REQ      1
#define WIFI_OFFCHAN_TX_CANCEL   0

#define WIFI_ROC_REQ     1
#define WIFI_ROC_CANCEL  0

typedef enum {
    WIFI_COUNTRY_POLICY_AUTO,   /**<国家/地区政策是自动的，使用站点所连接的AP的国家/地区信息*/
    WIFI_COUNTRY_POLICY_MANUAL, /**<国家/地区政策是手动的，始终使用配置的国家/地区信息*/
} wifi_country_policy_t;

/** @brief 描述WiFi国家/地区限制的结构。*/
typedef struct {
    char                  cc[3];   /**<国家代码字符串*/
    uint8_t               schan;   /**<启动通道*/
    uint8_t               nchan;   /**<总通道数*/
    int8_t                max_tx_power;   /**<此字段用于获取WiFi最大发射功率，调用esp_WiFi_set_max_power设置最大发射功率。*/
    wifi_country_policy_t policy;  /**<国家政策*/
} wifi_country_t;

typedef enum {
    WIFI_AUTH_OPEN = 0,         /**<身份验证模式：打开*/
    WIFI_AUTH_WEP,              /**<认证模式：WEP*/
    WIFI_AUTH_WPA_PSK,          /**<身份验证模式：WPA_PSK*/
    WIFI_AUTH_WPA2_PSK,         /**<认证模式：WPA2_PSK*/
    WIFI_AUTH_WPA_WPA2_PSK,     /**<验证模式：WPA_WPA2_PSK*/
    WIFI_AUTH_WPA2_ENTERPRISE,  /**<认证模式：WPA2_ENTERPRISE*/
    WIFI_AUTH_WPA3_PSK,         /**<认证模式：WPA3_PSK*/
    WIFI_AUTH_WPA2_WPA3_PSK,    /**<身份验证模式：WPA2_WPA3_PSK*/
    WIFI_AUTH_WAPI_PSK,         /**<认证模式：WAPI_PSK*/
    WIFI_AUTH_MAX
} wifi_auth_mode_t;

typedef enum {
    WIFI_REASON_UNSPECIFIED              = 1,
    WIFI_REASON_AUTH_EXPIRE              = 2,
    WIFI_REASON_AUTH_LEAVE               = 3,
    WIFI_REASON_ASSOC_EXPIRE             = 4,
    WIFI_REASON_ASSOC_TOOMANY            = 5,
    WIFI_REASON_NOT_AUTHED               = 6,
    WIFI_REASON_NOT_ASSOCED              = 7,
    WIFI_REASON_ASSOC_LEAVE              = 8,
    WIFI_REASON_ASSOC_NOT_AUTHED         = 9,
    WIFI_REASON_DISASSOC_PWRCAP_BAD      = 10,
    WIFI_REASON_DISASSOC_SUPCHAN_BAD     = 11,
    WIFI_REASON_BSS_TRANSITION_DISASSOC  = 12,
    WIFI_REASON_IE_INVALID               = 13,
    WIFI_REASON_MIC_FAILURE              = 14,
    WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT   = 15,
    WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT = 16,
    WIFI_REASON_IE_IN_4WAY_DIFFERS       = 17,
    WIFI_REASON_GROUP_CIPHER_INVALID     = 18,
    WIFI_REASON_PAIRWISE_CIPHER_INVALID  = 19,
    WIFI_REASON_AKMP_INVALID             = 20,
    WIFI_REASON_UNSUPP_RSN_IE_VERSION    = 21,
    WIFI_REASON_INVALID_RSN_IE_CAP       = 22,
    WIFI_REASON_802_1X_AUTH_FAILED       = 23,
    WIFI_REASON_CIPHER_SUITE_REJECTED    = 24,

    WIFI_REASON_INVALID_PMKID            = 53,

    WIFI_REASON_BEACON_TIMEOUT           = 200,
    WIFI_REASON_NO_AP_FOUND              = 201,
    WIFI_REASON_AUTH_FAIL                = 202,
    WIFI_REASON_ASSOC_FAIL               = 203,
    WIFI_REASON_HANDSHAKE_TIMEOUT        = 204,
    WIFI_REASON_CONNECTION_FAIL          = 205,
    WIFI_REASON_AP_TSF_RESET             = 206,
    WIFI_REASON_ROAMING                  = 207,
} wifi_err_reason_t;

typedef enum {
    WIFI_SECOND_CHAN_NONE = 0,  /**<通道宽度为HT20*/
    WIFI_SECOND_CHAN_ABOVE,     /**<通道宽度为HT40，辅助通道位于主通道上方*/
    WIFI_SECOND_CHAN_BELOW,     /**<通道宽度为HT40，辅助通道低于主通道*/
} wifi_second_chan_t;

typedef enum {
    WIFI_SCAN_TYPE_ACTIVE = 0,  /**<活动扫描*/
    WIFI_SCAN_TYPE_PASSIVE,     /**<被动扫描*/
} wifi_scan_type_t;

/** @brief 每个通道的活动扫描时间范围*/
typedef struct {
    uint32_t min;  /**<每个通道的最小活动扫描时间，单位：毫秒*/
    uint32_t max;  /**<每个信道的最大活动扫描时间，单位：毫秒，大于1500毫秒的值可能会导致站点与AP断开连接，不建议使用。*/
} wifi_active_scan_time_t;

/** @brief 每个通道的主动和被动扫描时间总计*/
typedef struct {
    wifi_active_scan_time_t active;  /**<每个通道的活动扫描时间，单位：毫秒。*/
    uint32_t passive;                /**<每个信道的被动扫描时间，单位：毫秒，大于1500毫秒的值可能会导致站点与AP断开连接，不建议使用。*/
} wifi_scan_time_t;

/** @brief SSID扫描的参数。*/
typedef struct {
    uint8_t *ssid;               /**<AP的SSID*/
    uint8_t *bssid;              /**<AP的MAC地址*/
    uint8_t channel;             /**<频道，扫描特定频道*/
    bool show_hidden;            /**<启用扫描SSID隐藏的AP*/
    wifi_scan_type_t scan_type;  /**<扫描类型，主动或被动*/
    wifi_scan_time_t scan_time;  /**<每个通道的扫描时间*/
} wifi_scan_config_t;

typedef enum {
    WIFI_CIPHER_TYPE_NONE = 0,   /**<密码类型为none*/
    WIFI_CIPHER_TYPE_WEP40,      /**<密码类型为WEP40*/
    WIFI_CIPHER_TYPE_WEP104,     /**<密码类型为WEP104*/
    WIFI_CIPHER_TYPE_TKIP,       /**<密码类型为TKIP*/
    WIFI_CIPHER_TYPE_CCMP,       /**<密码类型为CCMP*/
    WIFI_CIPHER_TYPE_TKIP_CCMP,  /**<密码类型为TKIP和CCMP*/
    WIFI_CIPHER_TYPE_AES_CMAC128,/**<密码类型为AES-CMAC-128*/
    WIFI_CIPHER_TYPE_SMS4,       /**<密码类型为SMS4*/
    WIFI_CIPHER_TYPE_GCMP,       /**<密码类型为GCMP*/
    WIFI_CIPHER_TYPE_GCMP256,    /**<密码类型为GCMP-256*/
    WIFI_CIPHER_TYPE_AES_GMAC128,/**<密码类型为AES-GMAC-128*/
    WIFI_CIPHER_TYPE_AES_GMAC256,/**<密码类型为AES-GMAC-256*/
    WIFI_CIPHER_TYPE_UNKNOWN,    /**<密码类型未知*/
} wifi_cipher_type_t;

/**
  * @brief WiFi天线
  *
  */
typedef enum {
    WIFI_ANT_ANT0,          /**<WiFi天线0*/
    WIFI_ANT_ANT1,          /**<WiFi天线1*/
    WIFI_ANT_MAX,           /**<无效的WiFi天线*/
} wifi_ant_t;

/** @brief WiFi AP说明*/
typedef struct {
    uint8_t bssid[6];                     /**<AP的MAC地址*/
    uint8_t ssid[33];                     /**<AP的SSID*/
    uint8_t primary;                      /**<AP通道*/
    wifi_second_chan_t second;            /**<AP的二级通道*/
    int8_t  rssi;                         /**<AP信号强度*/
    wifi_auth_mode_t authmode;            /**<AP的身份验证模式*/
    wifi_cipher_type_t pairwise_cipher;   /**<AP的成对密码*/
    wifi_cipher_type_t group_cipher;      /**<AP的群密码*/
    wifi_ant_t ant;                       /**<用于从AP接收信标的天线*/
    uint32_t phy_11b:1;                   /**<bit:0标志，用于标识11b模式是否启用*/
    uint32_t phy_11g:1;                   /**<bit:1标志，用于标识11g模式是否启用*/
    uint32_t phy_11n:1;                   /**<bit:2标志，用于标识11n模式是否启用*/
    uint32_t phy_lr:1;                    /**<bit:3标志，用于识别是否启用低速率*/
    uint32_t wps:1;                       /**<bit:4标志，用于标识WPS是否受支持*/
    uint32_t ftm_responder:1;             /**<bit:5标志，用于识别应答器模式中是否支持FTM*/
    uint32_t ftm_initiator:1;             /**<bit:6标志，用于标识在启动器模式下是否支持FTM*/
    uint32_t reserved:25;                 /**<bit:7..31保留*/
    wifi_country_t country;               /**<AP的国家信息*/
} wifi_ap_record_t;

typedef enum {
    WIFI_FAST_SCAN = 0,                   /**<执行快速扫描，查找SSID匹配AP后扫描将结束*/
    WIFI_ALL_CHANNEL_SCAN,                /**<所有频道扫描，扫描完所有频道后将结束扫描*/
}wifi_scan_method_t;

typedef enum {
    WIFI_CONNECT_AP_BY_SIGNAL = 0,        /**<按RSSI排序扫描列表中的匹配AP*/
    WIFI_CONNECT_AP_BY_SECURITY,          /**<按安全模式对扫描列表中的匹配AP进行排序*/
}wifi_sort_method_t;

/** @brief 描述WiFi快速扫描参数的结构*/
typedef struct {
    int8_t              rssi;             /**<在快速扫描模式下接受的最小rssi*/
    wifi_auth_mode_t    authmode;         /**<在快速扫描模式下接受的最弱身份验证模式*/
}wifi_scan_threshold_t;

typedef enum {
    WIFI_PS_NONE,        /**<无节能*/
    WIFI_PS_MIN_MODEM,   /**<最小调制解调器节电。在这种模式下，每个DTIM周期，电台都会醒来接收信标*/
    WIFI_PS_MAX_MODEM,   /**<最大调制解调器节电。在此模式下，接收信标的间隔由wifi_sta_config_t中的listen_interval参数确定*/
} wifi_ps_type_t;

#define WIFI_PROTOCOL_11B         1
#define WIFI_PROTOCOL_11G         2
#define WIFI_PROTOCOL_11N         4
#define WIFI_PROTOCOL_LR          8

typedef enum {
    WIFI_BW_HT20 = 1, /* 带宽为HT20*/
    WIFI_BW_HT40,     /* 带宽为HT40*/
} wifi_bandwidth_t;

/**受保护管理框架的配置结构*/
typedef struct {
    bool capable;            /**<不推荐的变量。如果其他设备也宣传PMF功能，则设备将始终以PMF模式连接。*/
    bool required;           /**<宣传需要受保护的管理框架。设备不会与不支持PMF的设备关联。*/
} wifi_pmf_config_t;

/** @brief ESP32的软AP配置设置*/
typedef struct {
    uint8_t ssid[32];           /**<ESP32软AP的SSID。如果ssid_len字段为0，则必须是以Null结尾的字符串。否则，根据ssid_len设置长度。*/
    uint8_t password[64];       /**<ESP32软AP的密码。*/
    uint8_t ssid_len;           /**<SSID字段的可选长度。*/
    uint8_t channel;            /**<ESP32软AP频道*/
    wifi_auth_mode_t authmode;  /**<ESP32软AP的认证模式。在软AP模式下不支持AUTH_WEP*/
    uint8_t ssid_hidden;        /**<是否广播SSID，默认为0，广播SSID*/
    uint8_t max_connection;     /**<允许连接的最大站点数，默认值为4，最大值为10*/
    uint16_t beacon_interval;   /**<信标间隔，应为100的倍数。单位：TU（时间单位，1 TU=1024 us）。范围：100～60000。默认值：100*/
    wifi_cipher_type_t pairwise_cipher;   /**<SoftAP的成对密码，将使用此导出组密码。密码值从WIFI_cipher_TYPE_TKIP开始有效，在此之前的枚举值将被视为无效，将使用默认密码套件（TKIP+CCMP）。软AP模式下的有效密码套件为WIFI_cipher_TYPE_TKIP、WIFI_CIP HER_TYPE_CCMP和WIFI_CIP-HER_TYPE-TKIP_CCMP。*/
    bool ftm_responder;         /**<启用FTM响应程序模式*/
} wifi_ap_config_t;

/** @brief ESP32的STA配置设置*/
typedef struct {
    uint8_t ssid[32];      /**<目标AP的SSID。*/
    uint8_t password[64];  /**<目标AP的密码。*/
    wifi_scan_method_t scan_method;    /**<进行全通道扫描或快速扫描*/
    bool bssid_set;        /**<是否设置目标AP的MAC地址。通常，station_config。bssid_set需要为0；并且仅当用户需要检查AP的MAC地址时才需要为1。*/
    uint8_t bssid[6];     /**<目标AP的MAC地址*/
    uint8_t channel;       /**<目标AP的通道。设置为1~13以在连接到AP之前从指定频道开始扫描。如果AP的信道未知，请将其设置为0。*/
    uint16_t listen_interval;   /**<设置WIFI_PS_MAX_MODEM时ESP32站接收信标的侦听间隔。单位：AP信标间隔。如果设置为0，则默认为3。*/
    wifi_sort_method_t sort_method;    /**<按rssi或安全模式对列表中的连接AP进行排序*/
    wifi_scan_threshold_t  threshold;     /**<当设置了sort_method时，将仅使用具有比所选身份验证模式更安全的身份验证模式和比最小RSSI更强的信号的AP。*/
    wifi_pmf_config_t pmf_cfg;    /**<受保护管理框架的配置。将在RSN IE中的RSN功能中进行宣传。*/
    uint32_t rm_enabled:1;        /**<是否为连接启用无线电测量*/
    uint32_t btm_enabled:1;       /**<是否为连接启用BSS过渡管理*/
    uint32_t mbo_enabled:1;       /**<是否为连接启用MBO*/
    uint32_t reserved:29;         /**<保留用于未来功能集*/
} wifi_sta_config_t;

/** @brief ESP32 AP或STA的配置数据。
 *
 * 此联合（用于ap或sta配置）的用法由传递给esp_wifi_set_config（）或esp_wify_get_config
 *
 */
typedef union {
    wifi_ap_config_t  ap;  /**<AP配置*/
    wifi_sta_config_t sta; /**<STA配置*/
} wifi_config_t;

/** @brief 与AP关联的STA描述*/
typedef struct {
    uint8_t mac[6];  /**<mac地址*/
    int8_t  rssi;    /**<连接的sta的当前平均rssi*/
    uint32_t phy_11b:1;      /**<bit:0标志，用于标识11b模式是否启用*/
    uint32_t phy_11g:1;      /**<bit:1标志，用于标识11g模式是否启用*/
    uint32_t phy_11n:1;      /**<bit:2标志，用于标识11n模式是否启用*/
    uint32_t phy_lr:1;       /**<bit:3标志，用于识别是否启用低速率*/
    uint32_t is_mesh_child:1;/**<bit:4标志，用于标识网格子对象*/
    uint32_t reserved:27;    /**<bit:5..31保留*/
} wifi_sta_info_t;

#define ESP_WIFI_MAX_CONN_NUM  (10)       /**<可连接到ESP32软AP的最大站点数*/

/** @brief 与ESP32软AP相关的电台列表*/
typedef struct {
    wifi_sta_info_t sta[ESP_WIFI_MAX_CONN_NUM]; /**<车站列表*/
    int       num; /**<列表中的站点数（其他条目无效）*/
} wifi_sta_list_t;

typedef enum {
    WIFI_STORAGE_FLASH,  /**<所有配置都将存储在内存和闪存中*/
    WIFI_STORAGE_RAM,    /**<所有配置将仅存储在内存中*/
} wifi_storage_t;

/**
  * @brief     供应商信息元素类型
  *
  * 确定IE将关联的帧类型。
  */
typedef enum {
    WIFI_VND_IE_TYPE_BEACON,
    WIFI_VND_IE_TYPE_PROBE_REQ,
    WIFI_VND_IE_TYPE_PROBE_RESP,
    WIFI_VND_IE_TYPE_ASSOC_REQ,
    WIFI_VND_IE_TYPE_ASSOC_RESP,
} wifi_vendor_ie_type_t;

/**
  * @brief     供应商信息要素索引
  *
  * 每个IE类型最多可以有两个关联的供应商ID元素。
  */
typedef enum {
    WIFI_VND_IE_ID_0,
    WIFI_VND_IE_ID_1,
} wifi_vendor_ie_id_t;

#define WIFI_VENDOR_IE_ELEMENT_ID 0xDD

/**
 * @brief 供应商信息元素标题
 *
 * 信息元素的第一个字节将与此标头匹配。随后是有效载荷。
 */
typedef struct {
    uint8_t element_id;      /**<应设置为WIFI_VENDOR_IE_ELEMENT_ID（0xDD）*/
    uint8_t length;          /**<此字段后面的元素数据中所有字节的长度。最低4。*/
    uint8_t vendor_oui[3];   /**<供应商标识符（OUI）。*/
    uint8_t vendor_oui_type; /**<供应商特定OUI类型。*/
    uint8_t payload[0];      /**<有效载荷。长度等于“长度”字段中的值减去4。*/
} vendor_ie_data_t;

/** @brief 接收到的分组无线电元数据头，这是所有混杂模式RX回调缓冲区开头的公共头*/
typedef struct {
    signed rssi:8;                /**<分组的接收信号强度指示符（RSSI）。单位：dBm*/
    unsigned rate:5;              /**<分组的PHY速率编码。仅对非HT（11bg）数据包有效*/
    unsigned :1;                  /**<保留*/
    unsigned sig_mode:2;          /**＜0：非HT（11bg）包；1： HT（11n）分组；3： VHT（11ac）数据包*/
    unsigned :16;                 /**<保留*/
    unsigned mcs:7;               /**<调制编码方案。如果是HT（11n）包，则显示调制，范围从0到76（MSC0～MCS76）*/
    unsigned cwb:1;               /**<数据包的信道带宽。0:20MHz；1： 40兆赫*/
    unsigned :16;                 /**<保留*/
    unsigned smoothing:1;         /**<保留*/
    unsigned not_sounding:1;      /**<保留*/
    unsigned :1;                  /**<保留*/
    unsigned aggregation:1;       /**<聚合。0:MPDU包；1： AMPDU数据包*/
    unsigned stbc:2;              /**<空时分组码（STBC）。0：非STBC报文；1： STBC数据包*/
    unsigned fec_coding:1;        /**<Flag为11n个LDPC数据包设置*/
    unsigned sgi:1;               /**<短引导间隔（SGI）。0：长GI；1： 短GI*/
#if CONFIG_IDF_TARGET_ESP32
    signed noise_floor:8;         /**<射频模块（RF）的噪声下限。单位：0.25dBm*/
#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3 || CONFIG_IDF_TARGET_ESP32C3
    unsigned :8;                  /**<保留*/
#endif
    unsigned ampdu_cnt:8;         /**<ampdu cnt*/
    unsigned channel:4;           /**<接收此数据包的主信道*/
    unsigned secondary_channel:4; /**<接收此数据包的辅助信道。0：无；1： 以上；2： 下面*/
    unsigned :8;                  /**<保留*/
    unsigned timestamp:32;        /**<时间戳。接收此数据包的本地时间。只有在未启用调制解调器睡眠或轻睡眠时，它才是精确的。单位：微秒*/
    unsigned :32;                 /**<保留*/
#if CONFIG_IDF_TARGET_ESP32S2
    unsigned :32;                 /**<保留*/
#elif CONFIG_IDF_TARGET_ESP32S3 || CONFIG_IDF_TARGET_ESP32C3
    signed noise_floor:8;         /**<射频模块（RF）的噪声下限。单位：0.25dBm*/
    unsigned :24;                 /**<保留*/
    unsigned :32;                 /**<保留*/
#endif
    unsigned :31;                 /**<保留*/
    unsigned ant:1;               /**<接收此数据包的天线号。0:WiFi天线0；1： WiFi天线1*/
#if CONFIG_IDF_TARGET_ESP32S2
    signed noise_floor:8;         /**<射频模块（RF）的噪声下限。单位：0.25dBm*/
    unsigned :24;                 /**<保留*/
#elif CONFIG_IDF_TARGET_ESP32S3 || CONFIG_IDF_TARGET_ESP32C3
    unsigned :32;                 /**<保留*/
    unsigned :32;                 /**<保留*/
    unsigned :32;                 /**<保留*/
#endif
    unsigned sig_len:12;          /**<包长度，包括帧检查序列（FCS）*/
    unsigned :12;                 /**<保留*/
    unsigned rx_state:8;          /**<数据包的状态。0：无错误；其他：不公开的错误号*/
} wifi_pkt_rx_ctrl_t;

/** @brief 负载传递给混杂模式RX回调的“buf”参数。
 */
typedef struct {
    wifi_pkt_rx_ctrl_t rx_ctrl; /**<元数据标头*/
    uint8_t payload[0];       /**<数据或管理有效负载。有效载荷的长度由rx_ctrl.sig_len描述。由回调的数据包类型参数确定的内容类型。*/
} wifi_promiscuous_pkt_t;

/**
  * @brief 混杂框架类型
  *
  * 传递给混杂模式RX回调，以指示缓冲区中的参数类型。
  *
  */
typedef enum {
    WIFI_PKT_MGMT,  /**<管理框架，表示“buf”参数为wifi_prociscuous_pkt_t*/
    WIFI_PKT_CTRL,  /**<控制帧，表示“buf”参数为wifi_prociscuous_pkt_t*/
    WIFI_PKT_DATA,  /**<数据帧，标记'buf'参数为wifi_comiscuus_pkt_t*/
    WIFI_PKT_MISC,  /**<其他类型，如MIMO等。'buf'参数为wifi_prociscuous_pkt_t，但有效负载长度为零。*/
} wifi_promiscuous_pkt_type_t;


#define WIFI_PROMIS_FILTER_MASK_ALL         (0xFFFFFFFF)  /**<过滤所有数据包*/
#define WIFI_PROMIS_FILTER_MASK_MGMT        (1)           /**<过滤WIFI_PKT_MGMT类型的数据包*/
#define WIFI_PROMIS_FILTER_MASK_CTRL        (1<<1)        /**<过滤WIFI_PKT_CTRL类型的数据包*/
#define WIFI_PROMIS_FILTER_MASK_DATA        (1<<2)        /**<过滤WIFI_PKT_DATA类型的数据包*/
#define WIFI_PROMIS_FILTER_MASK_MISC        (1<<3)        /**<过滤WIFI_PKT_MISC类型的数据包*/
#define WIFI_PROMIS_FILTER_MASK_DATA_MPDU   (1<<4)        /**<过滤作为WIFI_PKT_DATA的一种的MPDU*/
#define WIFI_PROMIS_FILTER_MASK_DATA_AMPDU  (1<<5)        /**<过滤一种WIFI_PKT_DATA的AMPDU*/
#define WIFI_PROMIS_FILTER_MASK_FCSFAIL     (1<<6)        /**<过滤FCS失败的数据包，一般不打开*/

#define WIFI_PROMIS_CTRL_FILTER_MASK_ALL         (0xFF800000)  /**<过滤所有控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_WRAPPER     (1<<23)       /**<使用control Wrapper的子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_BAR         (1<<24)       /**<使用Block Ack Request子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_BA          (1<<25)       /**<过滤子类型为Block Ack的控制包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_PSPOLL      (1<<26)       /**<使用PS轮询子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_RTS         (1<<27)       /**<使用RTS子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_CTS         (1<<28)       /**<使用CTS子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_ACK         (1<<29)       /**<使用ACK子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_CFEND       (1<<30)       /**<使用CF-END子类型过滤控制数据包*/
#define WIFI_PROMIS_CTRL_FILTER_MASK_CFENDACK    (1<<31)       /**<使用CF-END+CF-ACK子类型过滤控制数据包*/

/** @brief 用于在混杂模式下过滤不同数据包类型的掩码。*/
typedef struct {
    uint32_t filter_mask; /**<一个或多个过滤器值WIFI_PROMIS_filter_*的OR*/
} wifi_promiscuous_filter_t;

#define WIFI_EVENT_MASK_ALL                 (0xFFFFFFFF)  /**<屏蔽所有WiFi事件*/
#define WIFI_EVENT_MASK_NONE                (0)           /**<屏蔽所有WiFi事件*/
#define WIFI_EVENT_MASK_AP_PROBEREQRECVED   (BIT(0))      /**<mask SYSTEM_EVENT_AP_PROBEREQRECVED事件*/

/**
  * @brief 信道状态信息（CSI）配置类型
  *
  */
typedef struct {
    bool lltf_en;           /**<允许接收遗留的长训练字段（lltf）数据。默认已启用*/
    bool htltf_en;          /**<允许接收HT长训练场（htltf）数据。默认已启用*/
    bool stbc_htltf2_en;    /**<允许接收空时分组码HT长训练字段（stbc-htltf2）数据。默认已启用*/
    bool ltf_merge_en;      /**<使能在接收ht分组时通过平均lltf和ht_ltf数据来生成htlft数据。否则，直接使用ht_ltf数据。默认已启用*/
    bool channel_filter_en; /**<启用信道滤波器以平滑相邻子载波。禁用它以保持相邻子载波的独立性。默认已启用*/
    bool manu_scale;        /**<通过左移手动缩放CSI数据或自动缩放CSI。如果设置为真，请设置移位位。false：自动。true：手动。默认值为false*/
    uint8_t shift;          /**<CSI数据规模的手动左移位。左移位位的范围为0~15*/
} wifi_csi_config_t;

/**
  * @brief CSI数据类型
  *
  */
typedef struct {
    wifi_pkt_rx_ctrl_t rx_ctrl;/**<CSI数据的接收分组无线电元数据报头*/
    uint8_t mac[6];            /**<CSI数据的源MAC地址*/
    bool first_word_invalid;   /**<CSI数据的前四个字节是否无效*/
    int8_t *buf;               /**<CSI数据缓冲区*/
    uint16_t len;              /**<CSI数据长度*/
} wifi_csi_info_t;

/**
  * @brief 用于天线选择的WiFi GPIO配置
  *
  */
typedef struct {
    uint8_t gpio_select: 1,           /**<此GPIO是否连接到外部天线开关*/
            gpio_num: 7;              /**<连接到外部天线开关的GPIO编号*/
} wifi_ant_gpio_t;

/**
  * @brief 用于天线选择的WiFi GPIO配置
  *
  */
typedef struct {
    wifi_ant_gpio_t  gpio_cfg[4];  /**<连接到外部天线开关的GPIO的配置*/
} wifi_ant_gpio_config_t;

/**
  * @brief WiFi天线模式
  *
  */
typedef enum {
    WIFI_ANT_MODE_ANT0,          /**<仅启用WiFi天线0*/
    WIFI_ANT_MODE_ANT1,          /**<仅启用WiFi天线1*/
    WIFI_ANT_MODE_AUTO,          /**<启用WiFi天线0和1，自动选择天线*/
    WIFI_ANT_MODE_MAX,           /**<启用WiFi的天线无效*/
} wifi_ant_mode_t;

/**
  * @brief WiFi天线配置
  *
  */
typedef struct {
    wifi_ant_mode_t rx_ant_mode;          /**<用于接收的WiFi天线模式*/
    wifi_ant_t      rx_ant_default;       /**<接收的默认天线模式，如果rx_ant_mode不是WIFI_ant_mode_AUTO，则忽略*/
    wifi_ant_mode_t tx_ant_mode;          /**<用于传输的WiFi天线模式，仅当rx_ANT_mode设置为WiFi_ANT_mode_AUTO时，才能将其设置为WiFi _ANT_mode_AUTO*/
    uint8_t         enabled_ant0: 4,      /**<启用WIFI_ANT_MODE_ANT0的索引（天线内GPIO配置）*/
                    enabled_ant1: 4;      /**<启用WIFI_ANT_MODE_ANT1的索引（天线内GPIO配置）*/
} wifi_ant_config_t;

/**
  * @brief     动作Tx操作的Rx回调函数
  *
  * @param     hdr 指向IEEE 802.11报头结构的指针
  * @param     payload 指向802.11报头之后的有效负载的指针
  * @param     len 有效载荷长度
  * @param     channel 接收帧的频道号
  *
  */
typedef int (* wifi_action_rx_cb_t)(uint8_t *hdr, uint8_t *payload,
                                    size_t len, uint8_t channel);

/**
 * @brief 动作帧Tx请求
 *
 *
 */
typedef struct {
    wifi_interface_t ifx;       /**<发送请求的WiFi接口*/
    uint8_t dest_mac[6];        /**<目标MAC地址*/
    bool no_ack;                /**<表示不需要确认*/
    wifi_action_rx_cb_t rx_cb;  /**<Rx回调以接收任何响应*/
    uint32_t data_len;          /**<附加数据的长度*/
    uint8_t data[0];            /**<附加数据负载*/
} wifi_action_tx_req_t;

/**
  * @brief FTM启动器配置
  *
  */
typedef struct {
    uint8_t resp_mac[6];        /**<FTM响应程序的MAC地址*/
    uint8_t channel;            /**<FTM响应程序的主通道*/
    uint8_t frm_count;          /**<根据4或8个突发请求的FTM帧数量（允许值-0（无优先权）、16、24、32、64）*/
    uint16_t burst_period;      /**<100毫秒内连续FTM脉冲之间的请求时间段（0-无优先权）*/
} wifi_ftm_initiator_cfg_t;

/**
  * @brief WiFi PHY速率编码
  *
  */
typedef enum {
    WIFI_PHY_RATE_1M_L      = 0x00, /**<1 Mbps，带长前导码*/
    WIFI_PHY_RATE_2M_L      = 0x01, /**<2 Mbps，带长前导码*/
    WIFI_PHY_RATE_5M_L      = 0x02, /**<5.5 Mbps，带长前导码*/
    WIFI_PHY_RATE_11M_L     = 0x03, /**<11 Mbps，带长前导码*/
    WIFI_PHY_RATE_2M_S      = 0x05, /**<2 Mbps，带短前导码*/
    WIFI_PHY_RATE_5M_S      = 0x06, /**<5.5 Mbps，带短前导码*/
    WIFI_PHY_RATE_11M_S     = 0x07, /**<11 Mbps，带短前导码*/
    WIFI_PHY_RATE_48M       = 0x08, /**<48 Mbps*/
    WIFI_PHY_RATE_24M       = 0x09, /**<24 Mbps*/
    WIFI_PHY_RATE_12M       = 0x0A, /**<12 Mbps*/
    WIFI_PHY_RATE_6M        = 0x0B, /**<6 Mbps*/
    WIFI_PHY_RATE_54M       = 0x0C, /**<54 Mbps*/
    WIFI_PHY_RATE_36M       = 0x0D, /**<36 Mbps*/
    WIFI_PHY_RATE_18M       = 0x0E, /**<18 Mbps*/
    WIFI_PHY_RATE_9M        = 0x0F, /**<9 Mbps*/
    WIFI_PHY_RATE_MCS0_LGI  = 0x10, /**<MCS0，具有长GI，20MHz为6.5 Mbps，40MHz为13.5 Mbps*/
    WIFI_PHY_RATE_MCS1_LGI  = 0x11, /**<MCS1，具有长GI，20MHz为13 Mbps，40MHz为27 Mbps*/
    WIFI_PHY_RATE_MCS2_LGI  = 0x12, /**<MCS2，具有长GI，20MHz为19.5 Mbps，40MHz为40.5 Mbps*/
    WIFI_PHY_RATE_MCS3_LGI  = 0x13, /**<MCS3，具有长GI，20MHz为26 Mbps，40MHz为54 Mbps*/
    WIFI_PHY_RATE_MCS4_LGI  = 0x14, /**<MCS4，具有长GI，20MHz为39 Mbps，40MHz为81 Mbps*/
    WIFI_PHY_RATE_MCS5_LGI  = 0x15, /**<MCS5，具有长GI，20MHz为52 Mbps，40MHz为108 Mbps*/
    WIFI_PHY_RATE_MCS6_LGI  = 0x16, /**<MCS6，具有长GI，20MHz为58.5 Mbps，40MHz为121.5 Mbps*/
    WIFI_PHY_RATE_MCS7_LGI  = 0x17, /**<MCS7，具有长GI，20MHz为65 Mbps，40MHz为135 Mbps*/
    WIFI_PHY_RATE_MCS0_SGI  = 0x18, /**<MCS0，具有短GI，20MHz为7.2 Mbps，40MHz为15 Mbps*/
    WIFI_PHY_RATE_MCS1_SGI  = 0x19, /**<MCS1，具有短GI，20MHz为14.4 Mbps，40MHz为30 Mbps*/
    WIFI_PHY_RATE_MCS2_SGI  = 0x1A, /**<MCS2，短GI，21.7 Mbps用于20MHz，45 Mbps用于40MHz*/
    WIFI_PHY_RATE_MCS3_SGI  = 0x1B, /**<MCS3，具有短GI，20MHz为28.9 Mbps，40MHz为60 Mbps*/
    WIFI_PHY_RATE_MCS4_SGI  = 0x1C, /**<MCS4，具有短GI，20MHz为43.3 Mbps，40MHz为90 Mbps*/
    WIFI_PHY_RATE_MCS5_SGI  = 0x1D, /**<MCS5，具有短GI，20MHz为57.8 Mbps，40MHz为120 Mbps*/
    WIFI_PHY_RATE_MCS6_SGI  = 0x1E, /**<MCS6，具有短GI，20MHz为65 Mbps，40MHz为135 Mbps*/
    WIFI_PHY_RATE_MCS7_SGI  = 0x1F, /**<MCS7，具有短GI，20MHz为72.2 Mbps，40MHz为150 Mbps*/
    WIFI_PHY_RATE_LORA_250K = 0x29, /**<250 Kbps*/
    WIFI_PHY_RATE_LORA_500K = 0x2A, /**<500 Kbps*/
    WIFI_PHY_RATE_MAX,
} wifi_phy_rate_t;


/**WiFi事件声明*/
typedef enum {
    WIFI_EVENT_WIFI_READY = 0,           /**<ESP32 WiFi就绪*/
    WIFI_EVENT_SCAN_DONE,                /**<ESP32完成扫描AP*/
    WIFI_EVENT_STA_START,                /**<ESP32站启动*/
    WIFI_EVENT_STA_STOP,                 /**<ESP32站点停止*/
    WIFI_EVENT_STA_CONNECTED,            /**<ESP32站连接到AP*/
    WIFI_EVENT_STA_DISCONNECTED,         /**<ESP32站与AP断开*/
    WIFI_EVENT_STA_AUTHMODE_CHANGE,      /**<ESP32站点连接的AP的身份验证模式已更改*/

    WIFI_EVENT_STA_WPS_ER_SUCCESS,       /**<ESP32电台wps在注册人模式下成功*/
    WIFI_EVENT_STA_WPS_ER_FAILED,        /**<ESP32电台wps在注册人模式下失败*/
    WIFI_EVENT_STA_WPS_ER_TIMEOUT,       /**<ESP32电台wps在注册人模式下超时*/
    WIFI_EVENT_STA_WPS_ER_PIN,           /**<ESP32站wps pin码处于注册人模式*/
    WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP,   /**<ESP32站wps在注册人模式下重叠*/

    WIFI_EVENT_AP_START,                 /**<ESP32软AP启动*/
    WIFI_EVENT_AP_STOP,                  /**<ESP32软AP停止*/
    WIFI_EVENT_AP_STACONNECTED,          /**<连接到ESP32软AP的站点*/
    WIFI_EVENT_AP_STADISCONNECTED,       /**<与ESP32软AP断开连接的电台*/
    WIFI_EVENT_AP_PROBEREQRECVED,        /**<在软AP接口中接收探测请求包*/

    WIFI_EVENT_FTM_REPORT,               /**<接收FTM程序报告*/

    /* 仅在此之后添加下一个事件*/
    WIFI_EVENT_STA_BSS_RSSI_LOW,         /**<AP的RSSI超过配置阈值*/
    WIFI_EVENT_ACTION_TX_STATUS,         /**<动作Tx操作的状态指示*/
    WIFI_EVENT_ROC_DONE,                 /**<剩余信道操作完成*/

    WIFI_EVENT_STA_BEACON_TIMEOUT,       /**<ESP32电台信标超时*/

    WIFI_EVENT_MAX,                      /**<无效的WiFi事件ID*/
} wifi_event_t;

/**@秒**/
/** @brief WiFi事件基础声明*/
ESP_EVENT_DECLARE_BASE(WIFI_EVENT);
/**@结束秒**/

/**WIFI_EVENT_SCAN_DONE事件的参数结构*/
typedef struct {
    uint32_t status;          /**<扫描AP的状态：0-成功，1-失败*/
    uint8_t  number;          /**<扫描结果数*/
    uint8_t  scan_id;         /**<扫描序列号，用于块扫描*/
} wifi_event_sta_scan_done_t;

/**WIFI_EVENT_STA_CONNECTED事件的参数结构*/
typedef struct {
    uint8_t ssid[32];         /**<连接AP的SSID*/
    uint8_t ssid_len;         /**<连接AP的SSID长度*/
    uint8_t bssid[6];         /**<连接AP的BSSID*/
    uint8_t channel;          /**<连接AP的通道*/
    wifi_auth_mode_t authmode;/**<AP使用的身份验证模式*/
} wifi_event_sta_connected_t;

/**WIFI_EVENT_STA_DISCONNECTED事件的参数结构*/
typedef struct {
    uint8_t ssid[32];         /**<断开连接的AP的SSID*/
    uint8_t ssid_len;         /**<断开连接的AP的SSID长度*/
    uint8_t bssid[6];         /**<断开连接的AP的BSSID*/
    uint8_t reason;           /**<断开原因*/
} wifi_event_sta_disconnected_t;

/**WIFI_EVENT_STA_AUTHMODE_CHANGE事件的参数结构*/
typedef struct {
    wifi_auth_mode_t old_mode;         /**<AP的旧身份验证模式*/
    wifi_auth_mode_t new_mode;         /**<AP的新身份验证模式*/
} wifi_event_sta_authmode_change_t;

/**WIFI_EVENT_STA_WPS_ER_PIN事件的参数结构*/
typedef struct {
    uint8_t pin_code[8];         /**<登记人模式下车站的PIN码*/
} wifi_event_sta_wps_er_pin_t;

/**WIFI_EVENT_STA_WPS_ER_FAILED事件的参数结构*/
typedef enum {
    WPS_FAIL_REASON_NORMAL = 0,     /**<ESP32 WPS正常故障原因*/
    WPS_FAIL_REASON_RECV_M2D,       /**<ESP32 WPS接收M2D帧*/
    WPS_FAIL_REASON_MAX
} wifi_event_sta_wps_fail_reason_t;

#define MAX_SSID_LEN        32
#define MAX_PASSPHRASE_LEN  64
#define MAX_WPS_AP_CRED     3

/**WIFI_EVENT_STA_WPS_ER_SUCCESS事件的参数结构*/
typedef struct {
    uint8_t ap_cred_cnt;                        /**<收到的AP凭据数*/
    struct {
        uint8_t ssid[MAX_SSID_LEN];             /**<AP的SSID*/
        uint8_t passphrase[MAX_PASSPHRASE_LEN]; /**<AP的密码短语*/
    } ap_cred[MAX_WPS_AP_CRED];                 /**<从WPS握手收到的所有AP凭据*/
} wifi_event_sta_wps_er_success_t;

/**WIFI_EVENT_AP_STACONNECTED事件的参数结构*/
typedef struct {
    uint8_t mac[6];           /**<连接到ESP32软AP的站点的MAC地址*/
    uint8_t aid;              /**<ESP32软AP为连接到的电台提供的帮助*/
    bool is_mesh_child;       /**<标识网格子对象的标志*/
} wifi_event_ap_staconnected_t;

/**WIFI_EVENT_AP_STADISCONNECTED事件的参数结构*/
typedef struct {
    uint8_t mac[6];           /**<站点的MAC地址与ESP32软AP断开连接*/
    uint8_t aid;              /**<ESP32软AP给电台的帮助断开*/
    bool is_mesh_child;       /**<标识网格子对象的标志*/
} wifi_event_ap_stadisconnected_t;

/**WIFI_EVENT_AP_PROBEREQRECVED事件的参数结构*/
typedef struct {
    int rssi;                 /**<收到的探测请求信号强度*/
    uint8_t mac[6];           /**<发送探测请求的站点的MAC地址*/
} wifi_event_ap_probe_req_rx_t;

/**WIFI_EVENT_STA_BSS_RSSI_LOW事件的参数结构*/
typedef struct {
    int32_t rssi;                 /**<bss的RSSI值*/
} wifi_event_bss_rssi_low_t;

/**
  * @brief FTM运行状态类型
  *
  */
typedef enum {
    FTM_STATUS_SUCCESS = 0,     /**<FTM交换成功*/
    FTM_STATUS_UNSUPPORTED,     /**<Peer不支持FTM*/
    FTM_STATUS_CONF_REJECTED,   /**<FTM请求中的对等拒绝FTM配置*/
    FTM_STATUS_NO_RESPONSE,     /**<Peer未响应FTM请求*/
    FTM_STATUS_FAIL,            /**<FTM交换期间发生未知错误*/
} wifi_ftm_status_t;

/**的参数结构*/
typedef struct {
    uint8_t dlog_token;     /**<FTM帧的对话令牌*/
    int8_t rssi;            /**<接收的FTM帧的RSSI*/
    uint32_t rtt;           /**<与对等方的pSec往返时间*/
    uint64_t t1;            /**<pSec中FTM帧与FTM响应程序的偏离时间*/
    uint64_t t2;            /**<pSec中FTM帧到达FTM启动器的时间*/
    uint64_t t3;            /**<pSec中从FTM发起方发出ACK的时间*/
    uint64_t t4;            /**<pSec中FTM应答器的ACK到达时间*/
} wifi_ftm_report_entry_t;

/**WIFI_EVENT_FTM_REPORT事件的参数结构*/
typedef struct {
    uint8_t peer_mac[6];                        /**<FTM对等体的MAC地址*/
    wifi_ftm_status_t status;                   /**<FTM操作状态*/
    uint32_t rtt_raw;                           /**<原始平均往返时间（单位：毫微秒）*/
    uint32_t rtt_est;                           /**<估计的同行往返时间（单位：毫微秒）*/
    uint32_t dist_est;                          /**<估计单程距离（单位：Centi米）*/
    wifi_ftm_report_entry_t *ftm_report_data;   /**<指向具有多个条目的FTM报告的指针，应在使用后释放*/
    uint8_t ftm_report_num_entries;             /**<FTM报告数据中的条目数*/
} wifi_event_ftm_report_t;

#define WIFI_STATIS_BUFFER    (1<<0)
#define WIFI_STATIS_RXTX      (1<<1)
#define WIFI_STATIS_HW        (1<<2)
#define WIFI_STATIS_DIAG      (1<<3)
#define WIFI_STATIS_PS        (1<<4)
#define WIFI_STATIS_ALL       (-1)

/**WIFI_EVENT_ACTION_TX_STATUS事件的参数结构*/
typedef struct {
    wifi_interface_t ifx;     /**<发送请求的WiFi接口*/
    uint32_t context;         /**<标识请求的上下文*/
    uint8_t da[6];            /**<目标MAC地址*/
    uint8_t status;           /**<操作状态*/
} wifi_event_action_tx_status_t;

/**WIFI_EVENT_ROC_DONE事件的参数结构*/
typedef struct {
    uint32_t context;         /**<标识请求的上下文*/
} wifi_event_roc_done_t;

#ifdef __cplusplus
}
#endif

#endif /* __ESP_WIFI_TYPES_H__ */

