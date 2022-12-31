// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef _WIFI_PROV_CONFIG_H_
#define _WIFI_PROV_CONFIG_H_

#include <lwip/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   WiFi STA状态，用于传送回供应主机
 */
typedef enum {
    WIFI_PROV_STA_CONNECTING,
    WIFI_PROV_STA_CONNECTED,
    WIFI_PROV_STA_DISCONNECTED
} wifi_prov_sta_state_t;

/**
 * @brief   WiFi STA连接失败原因
 */
typedef enum {
    WIFI_PROV_STA_AUTH_ERROR,
    WIFI_PROV_STA_AP_NOT_FOUND
} wifi_prov_sta_fail_reason_t;

/**
 * @brief   WiFi STA连接状态信息
 */
typedef struct {
    /**
     * 站点接收的IP地址
     */
    char    ip_addr[IP4ADDR_STRLEN_MAX];

    char    bssid[6];   /*!< 已建立连接的AP的BSSID*/
    char    ssid[33];   /*!< 建立连接的SSID*/
    uint8_t channel;    /*!< AP频道*/
    uint8_t auth_mode;  /*!< AP的授权模式*/
} wifi_prov_sta_conn_info_t;

/**
 * @brief   响应主机的“get_status”请求而发送的WiFi状态数据
 */
typedef struct {
    wifi_prov_sta_state_t wifi_state;    /*!< 车站的WiFi状态*/
    union {
        /**
         * 断开原因（仅当“wifi_state”为“wifi_STATION_DISCONNECTED”时有效）
         */
        wifi_prov_sta_fail_reason_t fail_reason;

        /**
         * 连接信息（仅当“wifi_state”为“wifi_STATION_CONNECTED”时有效）
         */
        wifi_prov_sta_conn_info_t   conn_info;
    };
} wifi_prov_config_get_data_t;

/**
 * @brief   从设备在主设备的“set_config”请求期间接收到WiFi配置数据
 */
typedef struct {
    char    ssid[33];       /*!< 从属设备要连接到的AP的SSID*/
    char    password[64];   /*!< AP的密码*/
    char    bssid[6];       /*!< AP的BSSID*/
    uint8_t channel;        /*!< AP频道*/
} wifi_prov_config_set_data_t;

/**
 * @brief   传递给“wifi_prop_config_handlers”结构中每个get/set/apply处理程序函数集的上下文数据类型。
 *
 * 这是作为一个不透明的指针传递的，因此允许稍后根据需要在应用程序代码中定义它。
 */
typedef struct wifi_prov_ctx wifi_prov_ctx_t;

/**
 * @brief   用于接收和响应来自主机的protocomm请求的内部处理程序
 *
 * 当调用“protocomm_add_endpoint（）”时，这将作为protocomm请求处理程序的priva_data（请参阅“wifi_prop_config_data_handler（）”）传递。
 */
typedef struct wifi_prov_config_handlers {
    /**
     * 请求从属设备的连接状态（在WiFi站模式下）时调用的处理程序函数
     */
    esp_err_t (*get_status_handler)(wifi_prov_config_get_data_t *resp_data,
                                    wifi_prov_ctx_t **ctx);

    /**
     * 当从站（在WiFi站模式下）的WiFi连接配置（例如AP SSID、密码等）设置为用户提供的值时，调用处理器函数
     */
    esp_err_t (*set_config_handler)(const wifi_prov_config_set_data_t *req_data,
                                    wifi_prov_ctx_t **ctx);

    /**
     * 用于应用在“set_config_Handler”中设置的配置的处理程序函数。应用后，站点可能连接到AP或无法连接。当主设备再次调用“get_status_handler”时，从属设备必须准备好传送更新的连接状态信息。
     */
    esp_err_t (*apply_config_handler)(wifi_prov_ctx_t **ctx);

    /**
     * 调用时要传递给以上处理程序函数的上下文指针
     */
    wifi_prov_ctx_t *ctx;
} wifi_prov_config_handlers_t;

/**
 * @brief   用于接收和响应来自主机的请求的处理程序
 *
 * 使用`protocomm_add_endpoint（）将其注册为`wifi_config`端点处理程序（protocomm`protocomm_req_handler_t`）`
 */
esp_err_t wifi_prov_config_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen,
                                        uint8_t **outbuf, ssize_t *outlen, void *priv_data);

#ifdef __cplusplus
}
#endif

#endif

