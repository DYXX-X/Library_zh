/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
 * 这里声明的所有API都是仅限内部的API，它只能由espressif内部模块使用，如SSC、LWIP、TCPIP适配器等，不建议espressif客户使用它们。
 *
 * 如果有人真的想使用此处声明的指定API，请联系espressif AE/开发人员，以确保您了解API的限制或风险，否则您可能会出现意外行为！！！
 *
 */


#ifndef __ESP_WIFI_INTERNAL_H__
#define __ESP_WIFI_INTERNAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "sys/queue.h"
#include "esp_err.h"
#include "esp_wifi_types.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_smartconfig.h"
#include "wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    QueueHandle_t handle; /**<FreeRTOS队列处理程序*/
    void *storage;        /**<存储FreeRTOS队列*/
} wifi_static_queue_t;

/**
  * @brief WiFi日志级别
  *
  */
typedef enum {
    WIFI_LOG_NONE = 0,
    WIFI_LOG_ERROR ,      /*默认情况下已启用*/
    WIFI_LOG_WARNING,     /*默认情况下已启用*/
    WIFI_LOG_INFO,        /*默认情况下已启用*/
    WIFI_LOG_DEBUG,       /*可以在menuconfig中设置*/
    WIFI_LOG_VERBOSE,     /*可以在menuconfig中设置*/
} wifi_log_level_t;

/**
  * @brief WiFi日志模块定义
  *
  */
typedef enum {
    WIFI_LOG_MODULE_ALL  = 0, /*所有日志模块*/
    WIFI_LOG_MODULE_WIFI, /*与WiFi相关的日志*/
    WIFI_LOG_MODULE_COEX, /*与WiFi和BT（或BLE）相关的日志共存*/
    WIFI_LOG_MODULE_MESH, /*与网格相关的日志*/
} wifi_log_module_t;

/**
  * @brief WiFi日志子模块定义
  *
  */
#define WIFI_LOG_SUBMODULE_ALL   (0)    /*所有日志子模块*/
#define WIFI_LOG_SUBMODULE_INIT  (1)    /*与初始化相关的日志*/
#define WIFI_LOG_SUBMODULE_IOCTL (1<<1) /*与API调用相关的日志*/
#define WIFI_LOG_SUBMODULE_CONN  (1<<2) /*与连接相关的日志*/
#define WIFI_LOG_SUBMODULE_SCAN  (1<<3) /*与扫描相关的日志*/


/**
 * @brief 初始化WiFi驱动程序的Wi-Fi驱动程序分配资源，例如WiFi控制结构、RX/TX缓冲区、WiFi NVS结构等。
 *
 * 在大多数情况下，您不需要直接调用此函数。它从esp_wifi_init（）调用。
 *
 * 如果您只需要初始化Wi-Fi驱动程序而不必使用顶部的网络堆栈，则可以调用此函数。
 *
 * @param  config 提供WiFi初始化配置
 *
 * @return
 *    -ESP_OK：成功
 *    -ESP_ERR_NO_MEM：内存不足
 *    -其他：参考错误代码esp_err.h
 */
esp_err_t esp_wifi_init_internal(const wifi_init_config_t *config);

/**
 * @brief 取消初始化Wi-Fi驱动程序WiFi驱动程序的免费资源，如WiFi控制结构、RX/TX缓冲区、WiFi NVS结构等。
 *
 * 在大多数情况下，您不需要直接调用此函数。它从esp_wifi_init（）调用。
 *
 * 如果调用esp_wifi_init_internal初始化wifi驱动程序，则可能会调用此函数。
 *
 * @return
 *    -ESP_OK：成功
 *    -其他：参考错误代码esp_err.h
 */
esp_err_t esp_wifi_deinit_internal(void);

/**
  * @brief  释放wifi驱动程序分配的rx缓冲区
  *
  * @param  void* 缓冲区：rx缓冲区指针
  */
void esp_wifi_internal_free_rx_buffer(void* buffer);

/**
  * @brief  通过wifi驱动程序传输缓冲区
  *
  * 此API生成输入缓冲区的副本，然后将缓冲区副本转发给WiFi驱动程序。
  *
  * @param  wifi_interface_t wifi-if:wifi接口id
  * @param  void *缓冲区：要传输的缓冲区
  * @param  uint16_t len：缓冲区的长度
  *
  * @return
  *    -ESP_OK：成功将缓冲区传输到wifi驱动程序
  *    -ESP_ERR_NO_MEM：内存不足
  *    -ESP_ERR_WIFI_ARG：参数无效
  *    -ESP_ERR_WIFI_IF:WIFI接口无效
  *    -ESP_ERR_WIFI_CONN:未创建WIFI接口，例如，当WIFI模式为AP模式时，向STA发送数据
  *    -ESP_ERR_WIFI_NOT_STARTED:WIFI未启动
  *    -ESP_ERR_WIFI_STATE:WIFI内部状态未就绪，例如WIFI未启动
  *    -ESP_ERR_WIFI_NOT_ASSOC:WIFI未关联
  *    -ESP_ERR_WIFI_TX_DISALLOW:不允许WIFI传输，例如WIFI未通过身份验证
  *    -ESP_ERR_WIFI_POST：呼叫者无法将事件发布到WIFI任务
  */
int esp_wifi_internal_tx(wifi_interface_t wifi_if, void *buffer, uint16_t len);

/**
  * @brief     网络堆栈缓冲区引用计数器回调函数
  *
  */
typedef void (*wifi_netstack_buf_ref_cb_t)(void *netstack_buf);

/**
  * @brief     网络堆栈无缓冲区回调函数
  *
  */
typedef void (*wifi_netstack_buf_free_cb_t)(void *netstack_buf);

/**
  * @brief  通过wifi驱动程序通过引用传输缓冲区
  *
  * 该API首先增加输入缓冲区的参考计数器，然后将缓冲区转发给WiFi驱动程序。WiFi驱动程序将在处理后释放缓冲区。如果上层缓冲区不支持引用计数器，请使用esp_wifi_interal_tx（）。
  *
  * @param  wifi_if ：wifi接口id
  * @param  buffer ：要传输的缓冲区
  * @param  len ：缓冲区长度
  * @param  netstack_buf ：与缓冲区相关的网络堆栈缓冲区
  *
  * @return
  *    -ESP_OK：成功将缓冲区传输到wifi驱动程序
  *    -ESP_ERR_NO_MEM：内存不足
  *    -ESP_ERR_WIFI_ARG：参数无效
  *    -ESP_ERR_WIFI_IF:WIFI接口无效
  *    -ESP_ERR_WIFI_CONN:未创建WIFI接口，例如，当WIFI模式为AP模式时，向STA发送数据
  *    -ESP_ERR_WIFI_NOT_STARTED:WIFI未启动
  *    -ESP_ERR_WIFI_STATE:WIFI内部状态未就绪，例如WIFI未启动
  *    -ESP_ERR_WIFI_NOT_ASSOC:WIFI未关联
  *    -ESP_ERR_WIFI_TX_DISALLOW:不允许WIFI传输，例如WIFI未通过身份验证
  *    -ESP_ERR_WIFI_POST：呼叫者无法将事件发布到WIFI任务
  */
esp_err_t esp_wifi_internal_tx_by_ref(wifi_interface_t ifx, void *buffer, size_t len, void *netstack_buf);

/**
  * @brief     wpa_supplicant初始化时初始化WAPI函数。
  *
  * 此API是私人使用的，请注意不要向外部应用程序开放。
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_WAPI_INTERNAL：内部错误
  */
esp_err_t esp_wifi_internal_wapi_init(void);

/**
  * @brief     当wpa_supplicant取消初始化时，取消初始化WAPI函数。
  *
  * 此API是私人使用的，请注意不要向外部应用程序开放。
  *
  * @return
  *          -ESP_OK：成功
  */
esp_err_t esp_wifi_internal_wapi_deinit(void);

/**
  * @brief  注册网络堆栈缓冲区引用增加和释放回调
  *
  * @param  ref ：net堆栈缓冲区引用回调
  * @param  free: net堆栈无缓冲区回调
  *
  * @return
  *    -ESP_OK：成功将缓冲区传输到wifi驱动程序
  *    -其他：注册回调失败
  */
esp_err_t esp_wifi_internal_reg_netstack_buf_cb(wifi_netstack_buf_ref_cb_t ref, wifi_netstack_buf_free_cb_t free);


/**
  * @brief     WiFi RX回调函数
  *
  *            每当WiFi需要将数据包转发到高层时，将调用回调函数
  */
typedef esp_err_t (*wifi_rxcb_t)(void *buffer, uint16_t len, void *eb);

/**
  * @brief     设置WiFi RX回调
  *
  * @attention 1.目前我们只支持每个接口一个RX回调
  *
  * @param     wifi_interface_t ifx：接口
  * @param     wifi_rxcb_t fn:WiFi RX回调
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_wifi_internal_reg_rxcb(wifi_interface_t ifx, wifi_rxcb_t fn);

/**
  * @brief     通知WIFI驱动程序站点已成功获取ip
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_wifi_internal_set_sta_ip(void);

/**
  * @brief  启用或禁用以固定速率传输WiFi MAC帧
  *
  * @attention 1.如果启用固定速率，则以固定速率传输管理和数据帧
  * @attention 2.如果您希望接收帧，请确保接收器能够以固定速率接收帧
  *
  * @param  ifx ：wifi接口
  * @param  en ：false-禁用，true-启用
  * @param  rate ：PHY速率
  *
  * @return
  *    -ERR_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  *    -ESP_ERR_WIFI_IF:无效的WIFI接口
  *    -ESP_ERR_INVALID_ARG：无效速率
  *    -ESP_ERR_NOT_SUPPORTED：如果启用了TX AMPDU，则不支持设置固定速率
  */
esp_err_t esp_wifi_internal_set_fix_rate(wifi_interface_t ifx, bool en, wifi_phy_rate_t rate);

/**
  * @brief     启动SmartConfig，配置ESP设备以连接AP。您需要通过手机APP广播信息。设备嗅探来自空中的包含目标AP的SSID和密码的特殊数据包。
  *
  * @attention 1.此API可在站或软AP站模式下调用。
  * @attention 2.无法在完成之前调用esp_smartconfig_start两次，请先调用esp_smartconfig_stop。
  *
  * @param     config 指向smartconfig启动配置结构的指针
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_smartconfig_internal_start(const smartconfig_start_config_t *config);

/**
  * @brief     停止SmartConfig，释放esp_SmartConfig_start占用的缓冲区。
  *
  * @attention 无论连接到AP是否成功，都应调用此API以释放smartconfig_start占用的内存。
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_smartconfig_internal_stop(void);

/**
  * @brief     检查IDF和WiFi库中OS适配器头文件的MD5值
  *
  * @attention 1.用于内部CI版本检查
  *
  * @return
  *     -ESP_OK：成功
  *     -ESP_WIFI_INVALID_ARG:MD5检查失败
  */
esp_err_t esp_wifi_internal_osi_funcs_md5_check(const char *md5);

/**
  * @brief     检查IDF和WiFi库中加密类型头文件的MD5值
  *
  * @attention 1.用于内部CI版本检查
  *
  * @return
  *     -ESP_OK：成功
  *     -ESP_WIFI_INVALID_ARG:MD5检查失败
  */
esp_err_t esp_wifi_internal_crypto_funcs_md5_check(const char *md5);

/**
  * @brief     检查esp_wifi_types的MD5值。h在IDF和WiFi库中
  *
  * @attention 1.用于内部CI版本检查
  *
  * @return
  *     -ESP_OK：成功
  *     -ESP_WIFI_INVALID_ARG:MD5检查失败
  */
esp_err_t esp_wifi_internal_wifi_type_md5_check(const char *md5);

/**
  * @brief     检查esp_wifi的MD5值。h在IDF和WiFi库中
  *
  * @attention 1.用于内部CI版本检查
  *
  * @return
  *     -ESP_OK：成功
  *     -ESP_WIFI_INVALID_ARG:MD5检查失败
  */
esp_err_t esp_wifi_internal_esp_wifi_md5_check(const char *md5);

/**
  * @brief     为WiFi驱动程序分配一块内存
  *
  * @attention 此API不用于DMA内存分配。
  *
  * @param     size_t size：要分配的内存量的大小（以字节为单位）
  *
  * @return    指向成功时分配的内存的指针，失败时为NULL
  */
void *wifi_malloc( size_t size );

/**
  * @brief     重新分配WiFi驱动程序的内存块
  *
  * @attention 此API不用于DMA内存分配。
  *
  * @param     void *ptr：指向先前分配的内存的指针，或新分配的NULL。
  * @param     size_t size：要分配的内存量的大小（以字节为单位）
  *
  * @return    指向成功时分配的内存的指针，失败时为NULL
  */
void *wifi_realloc( void *ptr, size_t size );

/**
  * @brief     WiFi驱动程序的调用内存
  *
  * @attention 此API不用于DMA内存分配。
  *
  * @param     size_t n：要分配的连续内存块数
  * @param     size_t size：要分配的内存量的大小（以字节为单位）
  *
  * @return    指向成功时分配的内存的指针，失败时为NULL
  */
void *wifi_calloc( size_t n, size_t size );

/**
  * @brief     更新WiFi MAC时间
  *
  * @param     uint32_t time_delta：禁用WiFi/BT公共时钟后的持续时间
  *
  * @return    始终返回ESP_OK
  */
typedef esp_err_t (* wifi_mac_time_update_cb_t)( uint32_t time_delta );

/**
  * @brief     更新WiFi MAC时间
  *
  * @param     uint32_t time_delta：禁用WiFi/BT公共时钟后的持续时间
  *
  * @return    始终返回ESP_OK
  */
esp_err_t esp_wifi_internal_update_mac_time( uint32_t time_delta );

/**
  * @brief     设置当前WiFi日志级别
  *
  * @param     level   日志级别。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_FAIL:级别无效
  */
esp_err_t esp_wifi_internal_set_log_level(wifi_log_level_t level);

/**
  * @brief     设置当前日志模块和子模块
  *
  * @param     module      日志模块
  * @param     submodule   日志子模块
  * @param     enable      启用或禁用如果模块==0&&enable==0，则禁用所有日志模块。如果模块==0&&enable==1，则启用所有日志模块。如果子模块==0&&enable==0，则禁用所有日志子模块。如果子模块==0&&enable==1，则启用所有日志子模块。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_ARG：参数无效
  */
esp_err_t esp_wifi_internal_set_log_mod(wifi_log_module_t module, uint32_t submodule, bool enable);

/**
  * @brief     获取当前WiFi日志信息
  *
  * @param     log_level  返回日志级别。
  * @param     log_mod    返回日志模块和子模块
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_internal_get_log(wifi_log_level_t *log_level, uint32_t *log_mod);

/**
  * @brief     用于设置/获取WiFi内部配置的通用API，仅用于调试
  *
  * @param     cmd ：ioctl命令类型
  * @param     cfg ：命令的配置
  *
  * @return
  *    -ESP_OK：成功
  *    -其他：失败
  */
esp_err_t esp_wifi_internal_ioctl(int cmd, wifi_ioctl_config_t *cfg);

/**
  * @brief     获取用户配置的频道信息
  *
  * @param     ifx ：WiFi接口
  * @param     primary ：存储配置的主通道
  * @param     second ：存储配置的第二个通道
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_internal_get_config_channel(wifi_interface_t ifx, uint8_t *primary, uint8_t *second);

/**
  * @brief     建立WiFi连接后获取协商的频道信息
  *
  * @param     ifx ：WiFi接口
  * @param     aid ：STA连接到软AP时的连接编号
  * @param     primary ：存储协商的主通道
  * @param     second ：存储协商的第二个通道
  * @attention 辅助参数仅在ESP32处于softAP/softAP+STA模式时有效
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_internal_get_negotiated_channel(wifi_interface_t ifx, uint8_t aid, uint8_t *primary, uint8_t *second);

/**
  * @brief     建立WiFi连接后获取协商的带宽信息
  *
  * @param     ifx ：WiFi接口
  * @param     bw ：存储协商的带宽
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_internal_get_negotiated_bandwidth(wifi_interface_t ifx, uint8_t aid, uint8_t *bw);

#if SOC_WIFI_HW_TSF
/**
  * @brief     检查WiFi TSF是否处于活动状态
  *
  * @return
  *    -true：活动
  *    -false:未激活
  */
bool esp_wifi_internal_is_tsf_active(void);

/**
  * @brief     提前更新WIFI轻睡眠唤醒时间
  *
  */
void esp_wifi_internal_update_light_sleep_wake_ahead_time(uint32_t);
#endif

/**
 * @brief Wifi电源域电源打开
 */
void esp_wifi_power_domain_on(void);

/**
 * @brief Wifi电源域电源关闭
 */
void esp_wifi_power_domain_off(void);

#if CONFIG_MAC_BB_PD
/**
  * @brief     当Wi-Fi处于休眠状态时，启用或禁用关闭MAC和基带电源。
  *
  * @param     enable ：启用或禁用
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_internal_set_mac_sleep(bool enable);

/**
 * @brief mac bb睡眠。
 */
void pm_mac_sleep(void);

/**
 * @brief mac bb唤醒。
 */
void pm_mac_wakeup(void);
#endif

/**
  * @breif    TxDone回调函数类型。应使用esp_wifi_set_tx_done_cb（）注册
  *
  * @param    ifidx 触发tx回调的接口id
  * @param    data 指向传输数据的指针
  * @param    data_len 传输数据的长度
  * @param    txStatus True：如果数据传输成功False：如果数据发送失败
  */
typedef void (* wifi_tx_done_cb_t)(uint8_t ifidx, uint8_t *data, uint16_t *data_len, bool txStatus);

/**
  * @brief    注册wifi_tx_done_cb_t类型的txDone回调函数
  *
  * @param    cb 回调函数
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
  *    -ESP_ERR_WIFI_NOT_STARTED:ESP_WIFI_start未启动WIFI
  */
esp_err_t esp_wifi_set_tx_done_cb(wifi_tx_done_cb_t cb);

/**
 * @brief     设置设备spp-amsdu属性
 *
 * @param     ifx: WiFi接口
 * @param     spp_cap: 支持spp amsdu
 * @param     spp_req: spp amsdu要求
 *
 * @return
 *     -ESP_OK：成功
 *     -ESP_ERR_WIFI_NOT_INIT:WIFI未由ESP_WIFI_INIT初始化
 *     -ESP_ERR_WIFI_IF:无效的WIFI接口
 */
esp_err_t esp_wifi_internal_set_spp_amsdu(wifi_interface_t ifidx, bool spp_cap, bool spp_req);

/**
 * @brief   更新WIFI轻睡眠默认参数
 *
 * @param   min_freq_mhz: DFS最小频率
 * @param   max_freq_mhz: DFS最大频率
 */
void esp_wifi_internal_update_light_sleep_default_params(int min_freq_mhz, int max_freq_mhz);

/**
 * @brief   设置轻睡眠时wifi进入睡眠状态的延迟时间
 *
 * @param   return_to_sleep_delay: 等待接收数据的最短超时时间，当在超时期间没有接收到数据时，wifi将进入休眠过程。
 */
void esp_wifi_set_sleep_delay_time(uint32_t return_to_sleep_delay);

/**
 * @brief   设置wifi保活时间
 *
 * @param   keep_alive_time: 保活时间
 */
void esp_wifi_set_keep_alive_time(uint32_t keep_alive_time);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_WIFI_H__ */

