// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_SMARTCONFIG_H__
#define __ESP_SMARTCONFIG_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_event_base.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SC_TYPE_ESPTOUCH = 0,       /**<协议：ESPTouch*/
    SC_TYPE_AIRKISS,            /**<协议：AirKiss*/
    SC_TYPE_ESPTOUCH_AIRKISS,   /**<协议：ESPTouch和AirKiss*/
    SC_TYPE_ESPTOUCH_V2,        /**<协议：ESPTouch v2*/
} smartconfig_type_t;

/**Smartconfig事件声明*/
typedef enum {
    SC_EVENT_SCAN_DONE,                /*!< ESP32站点smartconfig已完成扫描AP*/
    SC_EVENT_FOUND_CHANNEL,            /*!< ESP32电台smartconfig已找到目标AP的频道*/
    SC_EVENT_GOT_SSID_PSWD,            /*!< ESP32站smartconfig获取了SSID和密码*/
    SC_EVENT_SEND_ACK_DONE,            /*!< ESP32站smartconfig已向手机发送ACK*/
} smartconfig_event_t;

/** @brief smartconfig事件基声明*/
ESP_EVENT_DECLARE_BASE(SC_EVENT);

/**SC_EVENT_GOT_SID_PSWD事件的参数结构*/
typedef struct {
    uint8_t ssid[32];           /**<AP的SSID。以Null结尾的字符串。*/
    uint8_t password[64];       /**<AP的密码。以Null结尾的字符串。*/
    bool bssid_set;             /**<是否设置目标AP的MAC地址。*/
    uint8_t bssid[6];           /**<目标AP的MAC地址。*/
    smartconfig_type_t type;    /**<智能配置类型（ESPTouch或AirKiss）。*/
    uint8_t token;              /**<来自手机的令牌，用于向手机发送ACK。*/
    uint8_t cellphone_ip[4];    /**<手机IP地址。*/
} smartconfig_event_got_ssid_pswd_t;

/**配置esp_smartconfig_start的结构*/
typedef struct {
    bool enable_log;                /**<启用smartconfig日志。*/
    bool esp_touch_v2_enable_crypt; /**<启用ESPTouch v2密码。*/
    char *esp_touch_v2_key;         /**<ESPTouch v2密码密钥，长度应为16。*/
} smartconfig_start_config_t;

#define SMARTCONFIG_START_CONFIG_DEFAULT() { \
    .enable_log = false, \
    .esp_touch_v2_enable_crypt = false,\
    .esp_touch_v2_key = NULL \
};

/**
  * @brief  获取SmartConfig的版本。
  *
  * @return
  *     -SmartConfig版本常量字符。
  */
const char *esp_smartconfig_get_version(void);

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
esp_err_t esp_smartconfig_start(const smartconfig_start_config_t *config);

/**
  * @brief     停止SmartConfig，释放esp_SmartConfig_start占用的缓冲区。
  *
  * @attention 无论连接到AP是否成功，都应调用此API以释放smartconfig_start占用的内存。
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_smartconfig_stop(void);

/**
  * @brief     设置SmartConfig进程的超时。
  *
  * @attention 计时从SC_STATUS_FIND_CHANNEL状态开始。如果超时，SmartConfig将重新启动。
  *
  * @param     time_s  范围15s～255s，偏移量：45s。
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_esptouch_set_timeout(uint8_t time_s);

/**
  * @brief     设置SmartConfig的协议类型。
  *
  * @attention 如果用户需要设置SmartConfig类型，请在调用esp_SmartConfig_start之前进行设置。
  *
  * @param     type  从smartconfig_type_t中选择。
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_smartconfig_set_type(smartconfig_type_t type);

/**
  * @brief     设置SmartConfig的模式。默认正常模式。
  *
  * @attention 1.请在API esp_smartconfig_start之前调用它。
  * @attention 2.快速模式有相应的APP（手机）。
  * @attention 3.两种模式兼容。
  *
  * @param     enable  假禁用（默认）；真使能；
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_smartconfig_fast_mode(bool enable);

/**
  * @brief     获取ESPTouch v2的保留数据。
  *
  * @param     rvd_data  保留数据
  * @param     len 保留数据长度
  *
  * @return
  *     -ESP_OK：成功
  *     -其他：失败
  */
esp_err_t esp_smartconfig_get_rvd_data(uint8_t *rvd_data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif

