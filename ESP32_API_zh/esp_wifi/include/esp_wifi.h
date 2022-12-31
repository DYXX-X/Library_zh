/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


/*               WiFi编程注意事项
 *
 *  esp32 WiFi编程模型可以描述为下图：
 *
 * 默认处理程序用户处理程序
 *  -----------------------------||event||回调或|||tcpip|--------->|event|--------->|应用程序||stack||task|event|task||----------||------------||---------------||---------|/||||||事件|||||
 *                             ---------------||||WiFi驱动程序|/__________________ |||\API调用|||-------------|
 *
 * WiFi驱动程序可以被视为黑盒，它对高层代码一无所知，例如TCPIP堆栈、应用程序任务、事件任务等，它所能做的就是接收来自高层或事件后队列的API调用到指定队列，该队列由API esp_WiFi_init（）初始化。
 *
 * 事件任务是一个守护程序任务，它从WiFi驱动程序或其他子系统（如TCPIP堆栈）接收事件，事件任务将在接收到事件时调用默认回调函数。例如，在接收到事件SYSTEM_event_STA_CONNECTED时，它将调用tcpip_adapter_start（）以在其默认处理程序中启动DHCP客户端。
 *
 * 应用程序可以通过API esp_event_init注册自己的事件回调函数，然后在默认回调后调用应用程序回调函数。此外，如果应用程序不想在事件任务中执行回调，它需要做的是在应用程序回调函数中将相关事件发布到应用程序任务。
 *
 * 应用程序任务（代码）通常将所有这些东西混合在一起，它调用API来初始化系统/WiFi并在必要时处理事件。
 *
 */

#ifndef __ESP_WIFI_H__
#define __ESP_WIFI_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_wifi_types.h"
#include "esp_event.h"
#include "esp_private/esp_wifi_private.h"
#include "esp_wifi_default.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ERR_WIFI_NOT_INIT    (ESP_ERR_WIFI_BASE + 1)   /*!< esp_WiFi_init未安装WiFi驱动程序*/
#define ESP_ERR_WIFI_NOT_STARTED (ESP_ERR_WIFI_BASE + 2)   /*!< esp_WiFi_start未启动WiFi驱动程序*/
#define ESP_ERR_WIFI_NOT_STOPPED (ESP_ERR_WIFI_BASE + 3)   /*!< esp_WiFi_stop未停止WiFi驱动程序*/
#define ESP_ERR_WIFI_IF          (ESP_ERR_WIFI_BASE + 4)   /*!< WiFi接口错误*/
#define ESP_ERR_WIFI_MODE        (ESP_ERR_WIFI_BASE + 5)   /*!< WiFi模式错误*/
#define ESP_ERR_WIFI_STATE       (ESP_ERR_WIFI_BASE + 6)   /*!< WiFi内部状态错误*/
#define ESP_ERR_WIFI_CONN        (ESP_ERR_WIFI_BASE + 7)   /*!< 站点WiFi内部控制块或软AP错误*/
#define ESP_ERR_WIFI_NVS         (ESP_ERR_WIFI_BASE + 8)   /*!< WiFi内部NVS模块错误*/
#define ESP_ERR_WIFI_MAC         (ESP_ERR_WIFI_BASE + 9)   /*!< MAC地址无效*/
#define ESP_ERR_WIFI_SSID        (ESP_ERR_WIFI_BASE + 10)   /*!< SSID无效*/
#define ESP_ERR_WIFI_PASSWORD    (ESP_ERR_WIFI_BASE + 11)  /*!< 密码无效*/
#define ESP_ERR_WIFI_TIMEOUT     (ESP_ERR_WIFI_BASE + 12)  /*!< 超时错误*/
#define ESP_ERR_WIFI_WAKE_FAIL   (ESP_ERR_WIFI_BASE + 13)  /*!< WiFi处于睡眠状态（RF关闭），唤醒失败*/
#define ESP_ERR_WIFI_WOULD_BLOCK (ESP_ERR_WIFI_BASE + 14)  /*!< 呼叫者会阻止*/
#define ESP_ERR_WIFI_NOT_CONNECT (ESP_ERR_WIFI_BASE + 15)  /*!< 站仍处于断开状态*/

#define ESP_ERR_WIFI_POST        (ESP_ERR_WIFI_BASE + 18)  /*!< 无法将事件发布到WiFi任务*/
#define ESP_ERR_WIFI_INIT_STATE  (ESP_ERR_WIFI_BASE + 19)  /*!< 调用init/deinit时WiFi状态无效*/
#define ESP_ERR_WIFI_STOP_STATE  (ESP_ERR_WIFI_BASE + 20)  /*!< WiFi停止时返回*/
#define ESP_ERR_WIFI_NOT_ASSOC   (ESP_ERR_WIFI_BASE + 21)  /*!< WiFi连接未关联*/
#define ESP_ERR_WIFI_TX_DISALLOW (ESP_ERR_WIFI_BASE + 22)  /*!< 不允许WiFi传输*/

/**
 * @brief 传递给esp_WiFi_init调用的WiFi堆栈配置参数。
 */
typedef struct {
    system_event_handler_t event_handler;          /**<WiFi事件处理程序*/
    wifi_osi_funcs_t*      osi_funcs;              /**<WiFi操作系统功能*/
    wpa_crypto_funcs_t     wpa_crypto_funcs;       /**<连接时WiFi站加密功能*/
    int                    static_rx_buf_num;      /**<WiFi静态RX缓冲区编号*/
    int                    dynamic_rx_buf_num;     /**<WiFi动态RX缓冲区编号*/
    int                    tx_buf_type;            /**<WiFi TX缓冲区类型*/
    int                    static_tx_buf_num;      /**<WiFi静态TX缓冲区编号*/
    int                    dynamic_tx_buf_num;     /**<WiFi动态TX缓冲区编号*/
    int                    cache_tx_buf_num;       /**<WiFi TX缓存缓冲区编号*/
    int                    csi_enable;             /**<WiFi信道状态信息启用标志*/
    int                    ampdu_rx_enable;        /**<WiFi AMPDU RX功能启用标志*/
    int                    ampdu_tx_enable;        /**<WiFi AMPDU TX功能启用标志*/
    int                    amsdu_tx_enable;        /**<WiFi AMSDU TX功能启用标志*/
    int                    nvs_enable;             /**<WiFi NVS闪存启用标志*/
    int                    nano_enable;            /**＜用于printf/scan系列启用标志的Nano选项*/
    int                    rx_ba_win;              /**<WiFi块确认RX窗口大小*/
    int                    wifi_task_core_id;      /**<WiFi任务核心ID*/
    int                    beacon_max_len;         /**<WiFi softAP信标的最大长度*/
    int                    mgmt_sbuf_num;          /**<WiFi管理短缓冲区编号，最小值为6，最大值为32*/
    uint64_t               feature_caps;           /**<启用其他WiFi功能和功能*/
    bool                   sta_disconnected_pm;    /**<处于断开状态的站点的WiFi电源管理*/
    int                    magic;                  /**<WiFi init magic number，它应该是最后一个字段*/
} wifi_init_config_t;

#ifdef CONFIG_ESP32_WIFI_STATIC_TX_BUFFER_NUM
#define WIFI_STATIC_TX_BUFFER_NUM CONFIG_ESP32_WIFI_STATIC_TX_BUFFER_NUM
#else
#define WIFI_STATIC_TX_BUFFER_NUM 0
#endif

#if (CONFIG_ESP32_SPIRAM_SUPPORT || CONFIG_ESP32S2_SPIRAM_SUPPORT || CONFIG_ESP32S3_SPIRAM_SUPPORT)
#define WIFI_CACHE_TX_BUFFER_NUM  CONFIG_ESP32_WIFI_CACHE_TX_BUFFER_NUM
#else
#define WIFI_CACHE_TX_BUFFER_NUM  0
#endif

#ifdef CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER_NUM
#define WIFI_DYNAMIC_TX_BUFFER_NUM CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER_NUM
#else
#define WIFI_DYNAMIC_TX_BUFFER_NUM 0
#endif

#if CONFIG_ESP32_WIFI_CSI_ENABLED
#define WIFI_CSI_ENABLED         1
#else
#define WIFI_CSI_ENABLED         0
#endif

#if CONFIG_ESP32_WIFI_AMPDU_RX_ENABLED
#define WIFI_AMPDU_RX_ENABLED        1
#else
#define WIFI_AMPDU_RX_ENABLED        0
#endif

#if CONFIG_ESP32_WIFI_AMPDU_TX_ENABLED
#define WIFI_AMPDU_TX_ENABLED        1
#else
#define WIFI_AMPDU_TX_ENABLED        0
#endif

#if CONFIG_ESP32_WIFI_AMSDU_TX_ENABLED
#define WIFI_AMSDU_TX_ENABLED        1
#else
#define WIFI_AMSDU_TX_ENABLED        0
#endif

#if CONFIG_ESP32_WIFI_NVS_ENABLED
#define WIFI_NVS_ENABLED          1
#else
#define WIFI_NVS_ENABLED          0
#endif

#if CONFIG_NEWLIB_NANO_FORMAT
#define WIFI_NANO_FORMAT_ENABLED  1
#else
#define WIFI_NANO_FORMAT_ENABLED  0
#endif

extern const wpa_crypto_funcs_t g_wifi_default_wpa_crypto_funcs;
extern uint64_t g_wifi_feature_caps;

#define WIFI_INIT_CONFIG_MAGIC    0x1F2F3F4F

#ifdef CONFIG_ESP32_WIFI_AMPDU_RX_ENABLED
#define WIFI_DEFAULT_RX_BA_WIN CONFIG_ESP32_WIFI_RX_BA_WIN
#else
#define WIFI_DEFAULT_RX_BA_WIN 0 /* 如果ampdu_rx_enable==false，则未使用*/
#endif

#if CONFIG_ESP32_WIFI_TASK_PINNED_TO_CORE_1
#define WIFI_TASK_CORE_ID 1
#else
#define WIFI_TASK_CORE_ID 0
#endif

#ifdef CONFIG_ESP32_WIFI_SOFTAP_BEACON_MAX_LEN
#define WIFI_SOFTAP_BEACON_MAX_LEN CONFIG_ESP32_WIFI_SOFTAP_BEACON_MAX_LEN
#else
#define WIFI_SOFTAP_BEACON_MAX_LEN 752
#endif

#ifdef CONFIG_ESP32_WIFI_MGMT_SBUF_NUM
#define WIFI_MGMT_SBUF_NUM CONFIG_ESP32_WIFI_MGMT_SBUF_NUM
#else
#define WIFI_MGMT_SBUF_NUM 32
#endif

#if CONFIG_ESP_WIFI_STA_DISCONNECTED_PM_ENABLE
#define WIFI_STA_DISCONNECTED_PM_ENABLED true
#else
#define WIFI_STA_DISCONNECTED_PM_ENABLED false
#endif

#define CONFIG_FEATURE_WPA3_SAE_BIT     (1<<0)
#define CONFIG_FEATURE_CACHE_TX_BUF_BIT (1<<1)
#define CONFIG_FEATURE_FTM_INITIATOR_BIT (1<<2)
#define CONFIG_FEATURE_FTM_RESPONDER_BIT (1<<3)

#define WIFI_INIT_CONFIG_DEFAULT() { \
    .event_handler = &esp_event_send_internal, \
    .osi_funcs = &g_wifi_osi_funcs, \
    .wpa_crypto_funcs = g_wifi_default_wpa_crypto_funcs, \
    .static_rx_buf_num = CONFIG_ESP32_WIFI_STATIC_RX_BUFFER_NUM,\
    .dynamic_rx_buf_num = CONFIG_ESP32_WIFI_DYNAMIC_RX_BUFFER_NUM,\
    .tx_buf_type = CONFIG_ESP32_WIFI_TX_BUFFER_TYPE,\
    .static_tx_buf_num = WIFI_STATIC_TX_BUFFER_NUM,\
    .dynamic_tx_buf_num = WIFI_DYNAMIC_TX_BUFFER_NUM,\
    .cache_tx_buf_num = WIFI_CACHE_TX_BUFFER_NUM,\
    .csi_enable = WIFI_CSI_ENABLED,\
    .ampdu_rx_enable = WIFI_AMPDU_RX_ENABLED,\
    .ampdu_tx_enable = WIFI_AMPDU_TX_ENABLED,\
    .amsdu_tx_enable = WIFI_AMSDU_TX_ENABLED,\
    .nvs_enable = WIFI_NVS_ENABLED,\
    .nano_enable = WIFI_NANO_FORMAT_ENABLED,\
    .rx_ba_win = WIFI_DEFAULT_RX_BA_WIN,\
    .wifi_task_core_id = WIFI_TASK_CORE_ID,\
    .beacon_max_len = WIFI_SOFTAP_BEACON_MAX_LEN, \
    .mgmt_sbuf_num = WIFI_MGMT_SBUF_NUM, \
    .feature_caps = g_wifi_feature_caps, \
    .sta_disconnected_pm = WIFI_STA_DISCONNECTED_PM_ENABLED,  \
    .magic = WIFI_INIT_CONFIG_MAGIC\
}

/**
  * @brief  初始化WiFi为WiFi驱动程序分配资源，如WiFi控制结构、RX/TX缓冲区、WiFi NVS结构等。此WiFi还启动WiFi任务
  *
  * @attention 1.必须先调用此API，然后才能调用所有其他WiFi API
  * @attention 2.始终使用WIFI_INIT_CONFIG_DEFAULT宏将配置初始化为默认值，这可以确保在将来的版本中将更多字段添加到WIFI_INIT_CONFIG_t中时，所有字段都获得正确的值。如果要设置自己的初始值，请覆盖WIFI_INIT_CONFIG_default设置的默认值。请注意，wifi_init_config_t的字段“magic”应始终为wifi_init_config_magic！
  *
  * @param  config 指向WiFi初始化配置结构的指针；可以指向临时变量。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_NO_MEM：内存不足
  *    -其他：参考错误代码esp_err.h
  */
esp_err_t esp_wifi_init(const wifi_init_config_t *config);

/**
  * @brief  Deinit WiFi释放esp_WiFi_init中分配的所有资源并停止WiFi任务
  *
  * @attention 1.如果要从系统中删除WiFi驱动程序，应调用此API
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_deinit(void);

/**
  * @brief     设置WiFi操作模式
  *
  *            将WiFi操作模式设置为站、软AP或站+软AP，默认模式为站模式。
  *
  * @param     mode  WiFi操作模式
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -其他：请参阅esp_err.h中的错误代码
  */
esp_err_t esp_wifi_set_mode(wifi_mode_t mode);

/**
  * @brief  获取WiFi的当前操作模式
  *
  * @param[out]  mode  存储当前WiFi模式
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_mode(wifi_mode_t *mode);

/**
  * @brief  根据当前配置启动WiFi如果模式为WiFi_mode_STA，则创建站点控制块并启动站点。如果模式为WIPI_mode_AP，则创建软AP控制块并开始软AP
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_NO_MEM：内存不足
  *    -ESP_ERR_WIFI_CONN:WIFI内部错误，站点或软AP控制块错误
  *    -ESP_FAIL：其他WiFi内部错误
  */
esp_err_t esp_wifi_start(void);

/**
  * @brief  停止WiFi如果模式为WiFi_mode_STA，则停止站点和空闲站点控制块如果模式为WIPI_mode_AP，则停止软AP和空闲软AP控制块如果是WiFi_mode_APSTA，则停止站/软AP和自由站点/软AP控制模块
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_stop(void);

/**
 * @brief  将WiFi堆栈持久设置恢复为默认值
 *
 * 此函数将重置使用以下API进行的设置：
 * -_带宽，
 * -esp_wifi_set_协议，
 * -esp_wifi_set_config相关
 * -esp_wifi_set_模式
 *
 * @return
 *    -ESP_OK：成功
 *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
 */
esp_err_t esp_wifi_restore(void);

/**
  * @brief     将ESP32 WiFi站连接到AP。
  *
  * @attention 1.此API仅影响WIFI_MODE_STA或WIFI_MODE_APSTA模式
  * @attention 2.如果ESP32连接到AP，请调用esp_wifi_disconnect断开连接。
  * @attention 3.在ESP32和AP之间建立连接之前，esp_wifi_start_scan（）触发的扫描将无效。如果ESP32正在扫描并同时连接，则ESP32将中止扫描并返回警告消息和错误号ESP_ERR_WIFI_STATE。如果您想在ESP32收到断开连接事件后重新连接，请记住添加最大重试时间，否则调用的扫描将无法工作。当AP不存在时尤其如此，并且在ESP32收到断开连接事件后，您仍然尝试重新连接，原因代码为WIFI_reason_NO_AP_FOUND。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_WIFI_CONN:WIFI内部错误，站点或软AP控制块错误
  *    -ESP_ERR_WIFI_SSID:站点连接的AP的SSID无效
  */
esp_err_t esp_wifi_connect(void);

/**
  * @brief     断开ESP32 WiFi站与AP的连接。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_FAIL：其他WiFi内部错误
  */
esp_err_t esp_wifi_disconnect(void);

/**
  * @brief     目前，此API只是一个存根API
  *

  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_clear_fast_connect(void);

/**
  * @brief     取消对所有工作站或关联id的身份验证，以帮助
  *
  * @param     aid  当aid为0时，对所有工作站进行身份验证，否则对关联id为aid的工作站进行身份认证
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_MODE：WIFI模式错误
  */
esp_err_t esp_wifi_deauth_sta(uint16_t aid);

/**
  * @brief     扫描所有可用的AP。
  *
  * @attention 如果调用此API，则找到的ap将存储在WiFi驱动程序动态分配的内存中，并将在esp_WiFi_scan_get_ap_records中释放，因此通常，在扫描完成后调用esp_WiFi_scan_get_ap_records以释放内存
  * @attention 每个通道的最大主动扫描时间和被动扫描时间的值限制为1500毫秒。值超过1500ms可能会导致站点与AP断开连接，不建议使用。
  *
  * @param     config  扫描配置
  * @param     block 如果block为true，则该API将阻止调用者，直到扫描完成，否则将立即返回
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_WIFI_TIMEOUT：阻止扫描超时
  *    -ESP_ERR_WIFI_STATE:调用ESP_WIFI_scan_start时WIFI仍在连接
  *    -其他：请参阅esp_err.h中的错误代码
  */
esp_err_t esp_wifi_scan_start(const wifi_scan_config_t *config, bool block);

/**
  * @brief     停止正在进行的扫描
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  */
esp_err_t esp_wifi_scan_stop(void);

/**
  * @brief     获取上次扫描中找到的AP数
  *
  * @param[out] number  存储上次扫描中找到的API数
  *
  * @attention 只有在扫描完成时才能调用此API，否则可能会得到错误的值。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_scan_get_ap_num(uint16_t *number);

/**
  * @brief     获取上次扫描中找到的AP列表
  *
  * @param[inout]  number 作为输入参数，它存储AP_records可以容纳的最大AP数。作为输出参数，它接收此API返回的实际AP编号。
  * @param         ap_records  wifi_ap_cord_t数组，用于保存找到的ap
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_NO_MEM：内存不足
  */
esp_err_t esp_wifi_scan_get_ap_records(uint16_t *number, wifi_ap_record_t *ap_records);


/**
  * @brief     获取ESP32站点关联的AP的信息
  *
  * @attention 当获得的国家信息为空时，意味着AP不携带国家信息
  *
  * @param     ap_info  用于保存ap信息sta的wifi_ap_reccord_t可以通过wifi_ap_reccord_ t结构中的结构成员phy_11b、phy_11g、phy_11n、phy_lr获得连接的ap的phy模式信息。例如，phy_11b=1表示ap支持802.11b模式
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_CONN：站接口未初始化
  *    -ESP_ERR_WIFI_NOT_CONNECT：工作站处于断开状态
  */
esp_err_t esp_wifi_sta_get_ap_info(wifi_ap_record_t *ap_info);

/**
  * @brief     设置当前WiFi节能类型
  *
  * @attention 默认省电类型为WIFI_PS_MIN_MODEM。
  *
  * @param     type  省电型
  *
  * @return    ESP_OK：成功
  */
esp_err_t esp_wifi_set_ps(wifi_ps_type_t type);

/**
  * @brief     获取当前WiFi节能类型
  *
  * @attention 默认省电类型为WIFI_PS_MIN_MODEM。
  *
  * @param[out]  type: 存储电流节能型
  *
  * @return    ESP_OK：成功
  */
esp_err_t esp_wifi_get_ps(wifi_ps_type_t *type);

/**
  * @brief     设置指定接口的协议类型默认协议为（WIFI_protocol_11B | WIFI_PROTO COL_11G | WIFIPROTOCOL_11N）
  *
  * @attention 目前，我们仅支持802.11b或802.11bg或802.11bgn模式
  *
  * @param     ifx  接口
  * @param     protocol_bitmap  WiFi协议位图
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -其他：参考esp_err.h中的错误代码
  */
esp_err_t esp_wifi_set_protocol(wifi_interface_t ifx, uint8_t protocol_bitmap);

/**
  * @brief     获取指定接口的当前协议位图
  *
  * @param     ifx  界面
  * @param[out] protocol_bitmap  存储接口ifx的当前WiFi协议位图
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -其他：参考esp_err.h中的错误代码
  */
esp_err_t esp_wifi_get_protocol(wifi_interface_t ifx, uint8_t *protocol_bitmap);

/**
  * @brief     设置ESP32指定接口的带宽
  *
  * @attention 1.如果尝试配置未启用的接口，则API返回false
  * @attention 2.仅当接口支持11N时才支持WIFI_BW_HT40
  *
  * @param     ifx  要配置的接口
  * @param     bw  带宽，带宽
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -其他：参考esp_err.h中的错误代码
  */
esp_err_t esp_wifi_set_bandwidth(wifi_interface_t ifx, wifi_bandwidth_t bw);

/**
  * @brief     获取ESP32指定接口的带宽
  *
  * @attention 1.如果尝试获取未启用的接口，则API返回false
  *
  * @param     ifx 要配置的接口
  * @param[out] bw  存储接口ifx的带宽
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_bandwidth(wifi_interface_t ifx, wifi_bandwidth_t *bw);

/**
  * @brief     设置ESP32的主/辅通道
  *
  * @attention 1.应在esp_wifi_start（）之后调用此API
  * @attention 2.当ESP32处于STA模式时，当STA扫描或连接到外部AP时，不应调用此API
  * @attention 3.当ESP32处于软AP模式时，当软AP连接到外部STA时，不应调用此API
  * @attention 4.当ESP32处于STA+软AP模式时，在上述场景中不应调用此API
  *
  * @param     primary  对于HT20，主信道是信道号，对于HT40，主信道为主信道
  * @param     second   对于HT20，忽略second，对于HT40，second是第二个通道
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_set_channel(uint8_t primary, wifi_second_chan_t second);

/**
  * @brief     获取ESP32的主/辅频道
  *
  * @attention 1.如果尝试获取未启用的接口，则API返回false
  *
  * @param     primary   存储电流主通道
  * @param[out]  second  存储当前第二通道
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_channel(uint8_t *primary, wifi_second_chan_t *second);

/**
  * @brief     配置国家信息
  *
  * @attention 1.不鼓励调用此API，因为这不会验证每个国家/地区的规则，由用户根据当地法规填写所有字段。请改用esp_wifi_set_country_code。
  * @attention 2.默认国家/地区为中国｛.cc=“CN”，.schan=1，.nchan=13，policy=WIFI_country_policy_AUTO｝
  * @attention 3.当国家政策为WIFI_country_policy_AUTO时，使用该站所连接的AP的国家信息。E、 g.如果配置的国家信息是{.cc=“USA”，.schan=1，.nchan=11}，并且站点所连接的AP的国家信息为{.cc=“JP”，.schan=1，.nchan=14}，则将使用的国家信息将是{.cc=“JP”、.schan=1，.nchan=14}。如果站点与AP断开连接，则国家信息将自动设置回站点的国家信息，在示例中｛.cc=“US”，.schan=1，.nchan=11｝。
  * @attention 4.当国家政策为WIFI_country_policy_MANUAL时，则始终使用配置的国家信息。
  * @attention 5.当国家信息由于配置或由于站连接到不同的外部AP而改变时，软AP的探测响应/信标中的国家IE也改变。
  * @attention 6.国家/地区配置存储在闪存中。
  * @attention 7.当调用此API时，PHY init数据将切换到对应于国家信息的PHY init类型。
  *
  * @param     country   配置的国家/地区信息
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_set_country(const wifi_country_t *country);

/**
  * @brief     获取当前国家/地区信息
  *
  * @param     country  国家信息
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_country(wifi_country_t *country);


/**
  * @brief     设置ESP32 WiFi站或软AP接口的MAC地址。
  *
  * @attention 1.此API只能在禁用接口时调用
  * @attention 2.ESP32软AP和站点具有不同的MAC地址，不要将它们设置为相同。
  * @attention 3.ESP32 MAC地址第一个字节的位0不能为1。例如，MAC地址可以设置为“1a:XX:XX:X:XX:XX”，但不能为“15:XX:XX:XX:XX:MX:XX”。
  *
  * @param     ifx  界面
  * @param     mac  MAC地址
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_WIFI_MAC:MAC地址无效
  *    -ESP_ERR_WIFI_MODE：WIFI模式错误
  *    -其他：参考esp_err.h中的错误代码
  */
esp_err_t esp_wifi_set_mac(wifi_interface_t ifx, const uint8_t mac[6]);

/**
  * @brief     获取指定接口的mac
  *
  * @param      ifx  界面
  * @param[out] mac  存储接口ifx的mac
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_IF：接口无效
  */
esp_err_t esp_wifi_get_mac(wifi_interface_t ifx, uint8_t mac[6]);

/**
  * @brief 处于混杂模式的RX回调函数。每次收到数据包时，都会调用回调函数。
  *
  * @param buf  收到数据。缓冲区中由“Type”参数指示的数据类型（wifi_comiscuus_pkt_t或wifi_pkt_rx_ctrl_t）。
  * @param type  混杂的数据包类型。
  *
  */
typedef void (* wifi_promiscuous_cb_t)(void *buf, wifi_promiscuous_pkt_type_t type);

/**
  * @brief 在混杂模式下注册RX回调函数。
  *
  * 每次收到数据包时，都会调用已注册的回调函数。
  *
  * @param cb  回调
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_set_promiscuous_rx_cb(wifi_promiscuous_cb_t cb);

/**
  * @brief     启用混杂模式。
  *
  * @param     en  false-禁用，true-启用
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_set_promiscuous(bool en);

/**
  * @brief     获得混乱模式。
  *
  * @param[out] en  存储混杂模式的当前状态
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_promiscuous(bool *en);

/**
  * @brief 启用混杂模式数据包类型筛选器。
  *
  * @note 默认过滤器是过滤除WIFI_PKT_MISC之外的所有数据包
  *
  * @param filter 以混杂模式过滤的分组类型。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_set_promiscuous_filter(const wifi_promiscuous_filter_t *filter);

/**
  * @brief     获取混杂过滤器。
  *
  * @param[out] filter  存储混杂过滤器的当前状态
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_promiscuous_filter(wifi_promiscuous_filter_t *filter);

/**
  * @brief 在混杂模式下启用控制数据包的子类型筛选器。
  *
  * @note 默认过滤器是不过滤控制数据包。
  *
  * @param filter 以混杂模式过滤的控制分组的子类型。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_set_promiscuous_ctrl_filter(const wifi_promiscuous_filter_t *filter);

/**
  * @brief     以混杂模式获取控制包的子类型筛选器。
  *
  * @param[out] filter  以混杂模式存储控制分组的子类型过滤器的当前状态
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效
  */
esp_err_t esp_wifi_get_promiscuous_ctrl_filter(wifi_promiscuous_filter_t *filter);

/**
  * @brief     设置ESP32 STA或AP的配置
  *
  * @attention 1.只有在启用指定接口时才能调用此API，否则API失败
  * @attention 2.对于站点配置，bssid_set需要为0；并且仅当用户需要检查AP的MAC地址时才需要为1。
  * @attention 3.ESP32仅限于一个频道，因此当处于软AP+电台模式时，软AP将自动调整其频道，使其与ESP32电台的频道相同。
  *
  * @param     interface  界面
  * @param     conf  站点或软AP配置
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_WIFI_MODE：模式无效
  *    -ESP_ERR_WIFI_PASSWORD：密码无效
  *    -ESP_ERR_WIFI_NVS:WIFI内部NVS错误
  *    -其他：参考esp_err.h中的错误代码
  */
esp_err_t esp_wifi_set_config(wifi_interface_t interface, wifi_config_t *conf);

/**
  * @brief     获取指定接口的配置
  *
  * @param     interface  界面
  * @param[out]  conf  站点或软AP配置
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_IF：接口无效
  */
esp_err_t esp_wifi_get_config(wifi_interface_t interface, wifi_config_t *conf);

/**
  * @brief     获取与软AP关联的STA
  *
  * @attention 仅限SSC API
  *
  * @param[out] sta  站点列表ap可以通过wifi-sta_infot结构中的结构成员phy_11b、phy_11g、phy_11n、phy_lr获取连接的sta的phy模式信息。例如，phy_11b=1表示sta支持802.11b模式
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_MODE：WIFI模式错误
  *    -ESP_ERR_WIFI_CONN:WIFI内部错误，站点/软AP控制块无效
  */
esp_err_t esp_wifi_ap_get_sta_list(wifi_sta_list_t *sta);

/**
  * @brief     获取与软AP连接的STA的AID
  *
  * @param     mac  STA的mac地址
  * @param[out]  aid  存储STA mac对应的AID
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_NOT_FOUND：未找到请求的资源
  *    -ESP_ERR_WIFI_MODE：WIFI模式错误
  *    -ESP_ERR_WIFI_CONN:WIFI内部错误，站点/软AP控制块无效
  */
esp_err_t esp_wifi_ap_get_sta_aid(const uint8_t mac[6], uint16_t *aid);

/**
  * @brief     设置WiFi API配置存储类型
  *
  * @attention 1.默认值为WIFI_STORAGE_FLASH
  *
  * @param     storage ：存储类型
  *
  * @return
  *   -ESP_OK：成功
  *   -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *   -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_set_storage(wifi_storage_t storage);

/**
  * @brief     收到的供应商特定信息元素回调的函数签名。
  * @param     ctx 上下文参数，在注册回调时传递给esp_wifi_set_vvendor_ie_cb（）。
  * @param     type 信息元素类型，基于接收的帧类型。
  * @param     sa 源802.11地址。
  * @param     vnd_ie 指向收到的供应商特定元素数据的指针。
  * @param     rssi 接收信号强度指示。
  */
typedef void (*esp_vendor_ie_cb_t) (void *ctx, wifi_vendor_ie_type_t type, const uint8_t sa[6], const vendor_ie_data_t *vnd_ie, int rssi);

/**
  * @brief     设置802.11供应商特定信息元素
  *
  * @param     enable 如果为true，则启用指定的IE。如果为false，则删除指定的IE。
  * @param     type 信息元素类型。确定要与IE关联的帧类型。
  * @param     idx  要设置或清除的索引。每个IE类型最多可以与两个元素（索引0和1）相关联。
  * @param     vnd_ie 指向供应商特定元素数据的指针。前6个字节应该是字段与vendor_ie_data_t匹配的标头。如果enable为false，则忽略此参数，并且可以为NULL。函数返回后，数据不需要保持有效。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT（）初始化
  *    -ESP_ERR_INVALID_ARG：参数无效，包括vnd_ie的第一个字节不是WIFI_VENDOR_ie_ELEMENT_ID（0xDD）或第二个字节的长度无效。
  *    -ESP_ERR_NO_MEM：内存不足
  */
esp_err_t esp_wifi_set_vendor_ie(bool enable, wifi_vendor_ie_type_t type, wifi_vendor_ie_id_t idx, const void *vnd_ie);

/**
  * @brief     注册供应商特定信息元素监控回调。
  *
  * @param     cb   回调函数
  * @param     ctx  上下文参数，传递给回调函数。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_set_vendor_ie_cb(esp_vendor_ie_cb_t cb, void *ctx);

/**
  * @brief     设置WiFi启动后的最大发射功率。
  *
  * @attention 1.wifi启动前的最大功率受PHY init数据箱限制。
  * @attention 2.此API设置的值将映射到结构wifi_country_t变量的max_tx_power。
  * @attention 3.映射表｛Power，max_tx_Power｝＝｛｛8，2｝，｛20，5｝，{28，7｝，｝34，8｝、｛44，11｝、{52，13｝、｝56，14｝，60，15｝，66，16｝，72，18｝，80，20｝｝。
  * @attention 4.参数功率单位为0.25dBm，范围为[8，84]，对应2dBm-20dBm。
  * @attention 5.设定值与实际值之间的关系。如下所示：｛设定值范围，实际值｝＝｛｛[8，19]，8}，｛[20，27]，20}，｛[28，33]，28}，｛[34，43]，34}，｛[44，51]，44}，｛[52，55]，52}，｛[66，59]，56}，{[60，65]，60}，{[6]，71]，66}，{[72，79]，72}，{[80，84]，80}。
  *
  * @param     power  最大WiFi传输功率。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_START：ESP_WIFI_START未启动WIFI
  *    -ESP_ERR_WIFI_ARG：参数无效，例如参数超出范围
  */
esp_err_t esp_wifi_set_max_tx_power(int8_t power);

/**
  * @brief     WiFi启动后获得最大发射功率
  *
  * @param     power 最大WiFi发射功率，单位为0.25dBm。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_START：ESP_WIFI_START未启动WIFI
  *    -ESP_ERR_WIFI_ARG：参数无效
  */
esp_err_t esp_wifi_get_max_tx_power(int8_t *power);

/**
  * @brief     设置掩码以启用或禁用某些WiFi事件
  *
  * @attention 1.掩码可以通过各种WIFI_EVENT_Mask_常量的逻辑或来创建。掩码中设置了相应位的事件将不会传递给系统事件处理程序。
  * @attention 2.默认WiFi事件掩码为WiFi_event_mask_AP_PROBEREQRECVED。
  * @attention 3.周围可能有许多站点发送探测请求数据。除非您需要接收探测请求数据，否则不要取消屏蔽此事件。
  *
  * @param     mask  WiFi事件掩码。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */
esp_err_t esp_wifi_set_event_mask(uint32_t mask);

/**
  * @brief     获取WiFi事件的掩码
  *
  * @param     mask  WiFi事件掩码。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效
  */
esp_err_t esp_wifi_get_event_mask(uint32_t *mask);

/**
  * @brief     发送原始ieee80211数据
  *
  * @attention 当前仅支持发送信标/探测请求/探测响应/动作和非QoS数据帧
  *
  * @param     ifx 如果Wi-Fi模式为Station，则ifx应为WIFI_if_STA。如果Wi-Fi模式为SoftAP，则ifx应为WIFI_If_AP。如果Wi-Fi模式为Station+SoftAP，则ifx应为WIFI_If_STA或WIFI_ID_AP。如果ifx错误，API将返回ESP_ERR_WIFI_If。
  * @param     buffer 原始ieee80211缓冲区
  * @param     len 原始缓冲区的长度，长度必须小于等于1500字节且大于等于24字节
  * @param     en_sys_seq 指示是否使用内部序列号。如果en_sys_seq为false，则原始缓冲区中的序列不变，否则WiFi驱动程序将使用系统序列号覆盖该序列。通常，如果在建立Wi-Fi连接之前调用esp_wifi_80211_tx，则en_sys_seq==true和en_sys-seq==false都可以。但是，如果在建立Wi-Fi连接后调用API，则en_sys_seq必须为true，否则返回ESP_ERR_WIFI_ARG。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_IF：接口无效
  *    -ESP_ERR_INVALID_ARG：参数无效
  *    -ESP_ERR_WIFI_NO_MEM：内存不足
  */

esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);

/**
  * @brief 信道状态信息（CSI）数据的RX回调函数。
  *
  *        每次收到CSI数据时，都会调用回调函数。
  *
  * @param ctx 上下文参数，在注册回调函数时传递给esp_wifi_set_csi_rx_cb（）。
  * @param data 接收到CSI数据。它所指向的内存将在回调函数返回后被释放。
  *
  */
typedef void (* wifi_csi_cb_t)(void *ctx, wifi_csi_info_t *data);


/**
  * @brief 注册CSI数据的RX回调函数。
  *
  *        每次收到CSI数据时，都会调用回调函数。
  *
  * @param cb  回调
  * @param ctx 上下文参数，传递给回调函数
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  */

esp_err_t esp_wifi_set_csi_rx_cb(wifi_csi_cb_t cb, void *ctx);

/**
  * @brief 设置CSI数据配置
  *
  * @param config 配置
  *
  * 回来
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_START:ESP_WIFI_START未启动WIFI或未启用混杂模式
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_set_csi_config(const wifi_csi_config_t *config);

/**
  * @brief 启用或禁用CSI
  *
  * @param en true-启用，false-禁用
  *
  * 回来
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_START:ESP_WIFI_START未启动WIFI或未启用混杂模式
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_set_csi(bool en);

/**
  * @brief     设置天线GPIO配置
  *
  * @param     config  天线GPIO配置。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效，例如参数为NULL、GPIO编号无效等
  */
esp_err_t esp_wifi_set_ant_gpio(const wifi_ant_gpio_config_t *config);

/**
  * @brief     获取当前天线GPIO配置
  *
  * @param     config  天线GPIO配置。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效，例如参数为NULL
  */
esp_err_t esp_wifi_get_ant_gpio(wifi_ant_gpio_config_t *config);


/**
  * @brief     设置天线配置
  *
  * @param     config  天线配置。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效，例如参数为NULL、天线模式无效或GPIO编号无效
  */
esp_err_t esp_wifi_set_ant(const wifi_ant_config_t *config);

/**
  * @brief     获取当前天线配置
  *
  * @param     config  天线配置。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效，例如参数为NULL
  */
esp_err_t esp_wifi_get_ant(wifi_ant_config_t *config);

/**
 * @brief      如果站点未连接或站点在连接后未接收到至少一个信标，则在站点模式或SoftAP+站点模式下获取TSF时间，将返回0
 *
 * @attention  启用省电可能会导致返回值不准确，WiFi调制解调器睡眠除外
 *
 * @param      interface 要检索其tsf_time的接口。
 *
 * @return     0或TSF时间
 */
int64_t esp_wifi_get_tsf_time(wifi_interface_t interface);

/**
  * @brief     设置ESP32 STA或AP的非活动时间
  *
  * @attention 1.对于站点，如果站点在非活动时间内未从连接的SoftAP接收到信标帧，请断开与SoftAP的连接。默认6s。
  * @attention 2.对于软AP，如果软AP在非活动时间内没有从连接的STA接收到任何数据，则软AP将强制对STA进行认证。默认值为300秒。
  * @attention 3.非活动时间配置未存储到闪存中
  *
  * @param     ifx  要配置的接口。
  * @param     sec  非活动时间。单位秒。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_WIFI_ARG：参数无效，对于Station，如果sec小于3。对于SoftAP，如果sec大于10。
  */
esp_err_t esp_wifi_set_inactive_time(wifi_interface_t ifx, uint16_t sec);

/**
  * @brief     获取指定接口的非活动时间
  *
  * @param     ifx  要配置的接口。
  * @param     sec  非活动时间。单位秒。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效
  */
esp_err_t esp_wifi_get_inactive_time(wifi_interface_t ifx, uint16_t *sec);

/**
  * @brief     转储WiFi统计信息
  *
  * @param     modules 要转储的统计模块
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_statis_dump(uint32_t modules);

/**
  * @brief      设置RSSI阈值，低于该阈值APP将获得事件
  *
  * @attention  每次收到WIFI_EVENT_STA_BSS_RSSI_LOW事件后，都需要调用此API。
  *
  * @param      rssi dbm中的阈值介于-100到0之间
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效
  */
esp_err_t esp_wifi_set_rssi_threshold(int32_t rssi);

/**
  * @brief      通过发送FTM请求启动FTM Initiator会话。如果成功，将使用FTM过程的结果生成事件WIFI_event_FTM_REPORT
  *
  * @attention  仅在Station模式下使用此API
  *
  * @param      cfg  FTM启动器会话配置
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_ftm_initiate_session(wifi_ftm_initiator_cfg_t *cfg);

/**
  * @brief      结束正在进行的FTM Initiator会话
  *
  * @attention  此API仅适用于FTM Initiator
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_ftm_end_session(void);

/**
  * @brief      设置FTM响应程序的偏移量（cm）。以皮秒为单位计算等效偏移，并将其添加到FTM测量帧（T1）的TOD中。
  *
  * @attention  在作为响应者执行FTM之前，仅在AP模式下使用此API
  *
  * @param      offset_cm  T1以厘米为单位添加的偏移
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_ftm_resp_set_offset(int16_t offset_cm);

/**
  * @brief      启用或禁用指定接口的11b速率
  *
  * @attention  1.应在esp_wifi_init（）之后和esp_wify_start（）之前调用此API。
  * @attention  2.只有当真正需要禁用11b速率时，才调用此API，否则不要调用此API。
  *
  * @param      ifx  要配置的接口。
  * @param      disable true表示禁用11b速率，而false表示启用11b速率。
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_config_11b_rate(wifi_interface_t ifx, bool disable);

/**
  * @brief      配置指定接口的ESPNOW速率
  *
  * @attention  1.应在esp_wifi_init（）之后和esp_wify_start（）之前调用此API。
  *
  * @param      ifx  要配置的接口。
  * @param      rate 要配置的物理速率。
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_config_espnow_rate(wifi_interface_t ifx, wifi_phy_rate_t rate);

/**
  * @brief      设置工作站在断开连接时定期唤醒的间隔。
  *
  * @attention 1.仅当启用ESP_WIFI_STA_DISCONNECTED_PM_ENABLE时，此配置才能工作
  * @attention 2.此配置仅适用于站模式和断开状态
  * @attention 3.在某些模块配置wake_window之前，此配置不会产生任何影响
  * @attention 4.建议使用不太小的合理间隔（例如100ms）
  *
  * @param      interval  芯片将唤醒多少毫秒，从1到65535。
  */
esp_err_t esp_wifi_set_connectionless_wake_interval(uint16_t interval);

/**
  * @brief     配置国家/地区
  *
  * @attention 1.当ieee80211d_enabled时，使用站点所连接的AP的国家信息。E、 g.如果配置的国家是美国，并且站点所连接的AP的国家信息是日本，则将使用的国家信息为日本。如果站点与AP断开连接，则国家信息将自动设置回站点的国家信息，在示例中为美国。
  * @attention 2.如果禁用ieee80211d_enabled，则始终使用配置的国家/地区信息。
  * @attention 3.当国家信息由于配置或由于站连接到不同的外部AP而改变时，软AP的探测响应/信标中的国家IE也改变。
  * @attention 4.国家/地区配置存储在闪存中。
  * @attention 5.当调用此API时，PHY init数据将切换到对应于国家信息的PHY init类型。
  * @attention 6.支持的国家/地区代码为“01”（世界安全模式）“AT”、“AU”、“BE”、“BG”、“BR”、“CA”、“CH”、“CN”、“CY”、”CZ“、”DE“、”DK“、“EE”、“ES”、“FI”、“FR”、“GB”、“GR”、“HK”、“HR”、“HU”、、“IE”、“IN”、“IS”、“IT”、“JP”、“KR”、NL、NO、NZ、PL、PT、RO、SE、SI、SK、TW、US
  *
  * @attention 7.当设置国家代码“01”（世界安全模式）时，SoftAP模式将不包含国家IE。
  * @attention 8.默认国家为“CN”，ieee80211d_enabled为TRUE。
  *
  * @param     country   配置的国家/地区ISO代码
  * @param     ieee80211d_enabled   802.11d是否已启用
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_set_country_code(const char *country, bool ieee80211d_enabled);

/**
  * @brief     获取当前国家/地区代码
  *
  * @param     country  国家代码
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_INVALID_ARG：参数无效
  */
esp_err_t esp_wifi_get_country_code(char *country);

/**
  * @brief      配置指定接口的80211传输速率
  *
  * @attention  1.应在esp_wifi_init（）之后和esp_wify_start（）之前调用此API。
  *
  * @param      ifx  要配置的接口。
  * @param      rate 要配置的物理速率。
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_config_80211_tx_rate(wifi_interface_t ifx, wifi_phy_rate_t rate);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_WIFI_H__ */

