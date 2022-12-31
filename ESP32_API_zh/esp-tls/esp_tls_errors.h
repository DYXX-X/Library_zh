/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_TLS_ERRORS_H_
#define _ESP_TLS_ERRORS_H_

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ERR_ESP_TLS_BASE           0x8000             /*!< ESP-TLS错误代码的起始数量*/

/* 通用esp-tls错误代码*/
#define ESP_ERR_ESP_TLS_CANNOT_RESOLVE_HOSTNAME           (ESP_ERR_ESP_TLS_BASE + 0x01)  /*!< tls连接时无法解析主机名时出错*/
#define ESP_ERR_ESP_TLS_CANNOT_CREATE_SOCKET              (ESP_ERR_ESP_TLS_BASE + 0x02)  /*!< 无法创建套接字*/
#define ESP_ERR_ESP_TLS_UNSUPPORTED_PROTOCOL_FAMILY       (ESP_ERR_ESP_TLS_BASE + 0x03)  /*!< 不支持的协议系列*/
#define ESP_ERR_ESP_TLS_FAILED_CONNECT_TO_HOST            (ESP_ERR_ESP_TLS_BASE + 0x04)  /*!< 无法连接到主机*/
#define ESP_ERR_ESP_TLS_SOCKET_SETOPT_FAILED              (ESP_ERR_ESP_TLS_BASE + 0x05)  /*!< 无法设置/获取套接字选项*/
#define ESP_ERR_ESP_TLS_CONNECTION_TIMEOUT                (ESP_ERR_ESP_TLS_BASE + 0x06)  /*!< esp_tls_low_level_conn连接中的新连接超时*/
#define ESP_ERR_ESP_TLS_SE_FAILED                         (ESP_ERR_ESP_TLS_BASE + 0x07)  /*<esp tls use返回的安全元素失败*/
#define ESP_ERR_ESP_TLS_TCP_CLOSED_FIN                    (ESP_ERR_ESP_TLS_BASE + 0x08)  /*<esp tls的TPC传输连接已关闭（以干净的方式）*/

/* mbedtls特定错误代码*/
#define ESP_ERR_MBEDTLS_CERT_PARTLY_OK                    (ESP_ERR_ESP_TLS_BASE + 0x10)  /*!< mbedtls分析证书部分成功*/
#define ESP_ERR_MBEDTLS_CTR_DRBG_SEED_FAILED              (ESP_ERR_ESP_TLS_BASE + 0x11)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_SSL_SET_HOSTNAME_FAILED           (ESP_ERR_ESP_TLS_BASE + 0x12)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_SSL_CONFIG_DEFAULTS_FAILED        (ESP_ERR_ESP_TLS_BASE + 0x13)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_SSL_CONF_ALPN_PROTOCOLS_FAILED    (ESP_ERR_ESP_TLS_BASE + 0x14)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_X509_CRT_PARSE_FAILED             (ESP_ERR_ESP_TLS_BASE + 0x15)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_SSL_CONF_OWN_CERT_FAILED          (ESP_ERR_ESP_TLS_BASE + 0x16)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_SSL_SETUP_FAILED                  (ESP_ERR_ESP_TLS_BASE + 0x17)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_SSL_WRITE_FAILED                  (ESP_ERR_ESP_TLS_BASE + 0x18)  /*!< mbedtls api返回错误*/
#define ESP_ERR_MBEDTLS_PK_PARSE_KEY_FAILED               (ESP_ERR_ESP_TLS_BASE + 0x19)  /*!< 返回的mbedtls api失败*/
#define ESP_ERR_MBEDTLS_SSL_HANDSHAKE_FAILED              (ESP_ERR_ESP_TLS_BASE + 0x1A)  /*!< 返回的mbedtls api失败*/
#define ESP_ERR_MBEDTLS_SSL_CONF_PSK_FAILED               (ESP_ERR_ESP_TLS_BASE + 0x1B)  /*!< 返回的mbedtls api失败*/
#define ESP_ERR_MBEDTLS_SSL_TICKET_SETUP_FAILED           (ESP_ERR_ESP_TLS_BASE + 0x1C)  /*!< 返回的mbedtls api失败*/

/* wolfssl特定错误代码*/
#define ESP_ERR_WOLFSSL_SSL_SET_HOSTNAME_FAILED           (ESP_ERR_ESP_TLS_BASE + 0x31)  /*!< wolfSSL api返回错误*/
#define ESP_ERR_WOLFSSL_SSL_CONF_ALPN_PROTOCOLS_FAILED    (ESP_ERR_ESP_TLS_BASE + 0x32)  /*!< wolfSSL api返回错误*/
#define ESP_ERR_WOLFSSL_CERT_VERIFY_SETUP_FAILED          (ESP_ERR_ESP_TLS_BASE + 0x33)  /*!< wolfSSL api返回错误*/
#define ESP_ERR_WOLFSSL_KEY_VERIFY_SETUP_FAILED           (ESP_ERR_ESP_TLS_BASE + 0x34)  /*!< wolfSSL api返回错误*/
#define ESP_ERR_WOLFSSL_SSL_HANDSHAKE_FAILED              (ESP_ERR_ESP_TLS_BASE + 0x35)  /*!< wolfSSL api返回失败*/
#define ESP_ERR_WOLFSSL_CTX_SETUP_FAILED                  (ESP_ERR_ESP_TLS_BASE + 0x36)  /*!< wolfSSL api返回失败*/
#define ESP_ERR_WOLFSSL_SSL_SETUP_FAILED                  (ESP_ERR_ESP_TLS_BASE + 0x37)  /*!< wolfSSL api返回失败*/
#define ESP_ERR_WOLFSSL_SSL_WRITE_FAILED                  (ESP_ERR_ESP_TLS_BASE + 0x38)  /*!< wolfSSL api返回失败*/


/**
* 错误情况下IO API报告的错误定义（可能非阻塞）：
* -esp_tls_conn_read（）
* -esp_tls_conn_write（）
*/
#ifdef CONFIG_ESP_TLS_USING_MBEDTLS
#define ESP_TLS_ERR_SSL_WANT_READ                          MBEDTLS_ERR_SSL_WANT_READ
#define ESP_TLS_ERR_SSL_WANT_WRITE                         MBEDTLS_ERR_SSL_WANT_WRITE
#define ESP_TLS_ERR_SSL_TIMEOUT                            MBEDTLS_ERR_SSL_TIMEOUT
#elif CONFIG_ESP_TLS_USING_WOLFSSL /* CONFIG_ESP_TLS_USING_MBEDTLS */
#define ESP_TLS_ERR_SSL_WANT_READ                          -0x6900
#define ESP_TLS_ERR_SSL_WANT_WRITE                         -0x6880
#define ESP_TLS_ERR_SSL_TIMEOUT                            WOLFSSL_CBIO_ERR_TIMEOUT
#endif /*CONFIG_ESP_TLS_USING_WOLFSSL */

/**
* 不同组件报告的不同类型/错误代码来源的定义
*/
typedef enum {
    ESP_TLS_ERR_TYPE_UNKNOWN = 0,
    ESP_TLS_ERR_TYPE_SYSTEM,                /*!< 系统错误--错误号*/
    ESP_TLS_ERR_TYPE_MBEDTLS,               /*!< mbedTLS库中的错误代码*/
    ESP_TLS_ERR_TYPE_MBEDTLS_CERT_FLAGS,    /*!< mbedTLS中定义的证书标志*/
    ESP_TLS_ERR_TYPE_ESP,                   /*!< ESP-IDF错误类型--ESP_err_t*/
    ESP_TLS_ERR_TYPE_WOLFSSL,               /*!< wolfSSL库中的错误代码*/
    ESP_TLS_ERR_TYPE_WOLFSSL_CERT_FLAGS,    /*!< wolfSSL中定义的证书标志*/
    ESP_TLS_ERR_TYPE_MAX,                   /*!< 最后一个错误类型--条目无效*/
} esp_tls_error_type_t;

typedef struct esp_tls_last_error* esp_tls_error_handle_t;

/**
*  @brief 发生tls错误时包含相关错误的错误结构
*/
typedef struct esp_tls_last_error {
    esp_err_t last_error;               /*!< 上次发生错误的错误代码（基于ESP_ERR_ESP_TLS_BASE）*/
    int       esp_tls_error_code;       /*!< 来自上次esp_tls失败api的esp_tls错误代码*/
    int       esp_tls_flags;            /*!< 最后一次认证验证标志*/
} esp_tls_last_error_t;

#ifdef __cplusplus
}
#endif

#endif //_ESP_TLS_ERRORS_H_

