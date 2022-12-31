/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_HTTPS_SERVER_H_
#define _ESP_HTTPS_SERVER_H_

#include <stdbool.h>
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_tls.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HTTPD_SSL_TRANSPORT_SECURE,      // 已启用SSL
    HTTPD_SSL_TRANSPORT_INSECURE     // SSL已禁用
} httpd_ssl_transport_mode_t;

/**
 * @brief 回调数据结构，包含ESP-TLS连接句柄
 */
typedef struct esp_https_server_user_cb_arg {
    const esp_tls_t *tls;
} esp_https_server_user_cb_arg_t;

/**
 * @brief 回调函数原型可用于获取连接或客户端信息（SSL上下文），例如客户端证书、套接字FD、连接状态等。
 *
 * @param user_cb 回调数据结构
 */
typedef void esp_https_server_user_cb(esp_https_server_user_cb_arg_t *user_cb);

/**
 * HTTPS服务器配置结构
 *
 * 请使用HTTPD_SSL_CONFIG_DEFAULT（）初始化它。
 */
struct httpd_ssl_config {
    /**
     * 基础HTTPD服务器配置
     *
     * 可以在此处调整任务堆栈大小和优先级等参数。
     */
    httpd_config_t httpd;

    /**CA证书（在这里它被视为服务器证书）Todo：修复版本/v5.0中的这一更改，因为这将是一个突破性的更改，即。重命名https_server组件中保存不同证书的变量命名法，以及示例1）cacert变量应保存用于验证客户端的CA（应继承client_verify_cert_pem var的当前角色）2）应该有另一个变量servercert，它将保存服务器自己的证书（应继承cacert var的当前作用）*/
    const uint8_t *cacert_pem;

    /**CA证书字节长度*/
    size_t cacert_len;

    /**客户端验证机构证书（用于对客户端或客户端证书本身进行签名的CA*/
    const uint8_t *client_verify_cert_pem;

    /**客户端验证权限证书长度*/
    size_t client_verify_cert_len;

    /**私钥*/
    const uint8_t *prvtkey_pem;

    /**私钥字节长度*/
    size_t prvtkey_len;

    /**传输模式（默认安全）*/
    httpd_ssl_transport_mode_t transport_mode;

    /**传输模式安全时使用的端口（默认443）*/
    uint16_t port_secure;

    /**传输模式不安全时使用的端口（默认值为80）*/
    uint16_t port_insecure;

    /**启用tls会话票证*/
    bool session_tickets;

    /**esp_https_server的用户回调*/
    esp_https_server_user_cb *user_cb;
};

typedef struct httpd_ssl_config httpd_ssl_config_t;

/**
 * 默认配置结构初始化
 *
 * （必须复制http_server默认配置以进行自定义）
 *
 * 笔记：
 * -启动服务器时根据“transport_mode”设置端口
 * -一个套接字使用40kB RAM和SSL，我们将默认套接字数减少到4
 * -SSL套接字通常寿命很长，关闭LRU可防止池耗尽DOS
 * -堆栈大小可能需要根据用户应用程序进行调整
 */
#define HTTPD_SSL_CONFIG_DEFAULT() {              \
    .httpd = {                                    \
        .task_priority      = tskIDLE_PRIORITY+5, \
        .stack_size         = 10240,              \
        .core_id            = tskNO_AFFINITY,     \
        .server_port        = 0,                  \
        .ctrl_port          = 32768,              \
        .max_open_sockets   = 4,                  \
        .max_uri_handlers   = 8,                  \
        .max_resp_headers   = 8,                  \
        .backlog_conn       = 5,                  \
        .lru_purge_enable   = true,               \
        .recv_wait_timeout  = 5,                  \
        .send_wait_timeout  = 5,                  \
        .global_user_ctx = NULL,                  \
        .global_user_ctx_free_fn = NULL,          \
        .global_transport_ctx = NULL,             \
        .global_transport_ctx_free_fn = NULL,     \
        .open_fn = NULL,                          \
        .close_fn = NULL,                         \
        .uri_match_fn = NULL                      \
    },                                            \
    .cacert_pem = NULL,                           \
    .cacert_len = 0,                              \
    .client_verify_cert_pem = NULL,               \
    .client_verify_cert_len = 0,                  \
    .prvtkey_pem = NULL,                          \
    .prvtkey_len = 0,                             \
    .transport_mode = HTTPD_SSL_TRANSPORT_SECURE, \
    .port_secure = 443,                           \
    .port_insecure = 80,                          \
    .session_tickets = false,                     \
    .user_cb = NULL,                              \
}

/**
 * 创建支持SSL的HTTP服务器（安全模式可能在配置中禁用）
 *
 * @param[in,out] config -服务器配置，不能为常量。调用此函数后不必保持有效。
 * @param[out] handle -服务器句柄的存储，必须是有效的指针
 * @return 成功
 */
esp_err_t httpd_ssl_start(httpd_handle_t *handle, httpd_ssl_config_t *config);

/**
 * 停止服务器。阻止，直到服务器关闭。
 *
 * @param[in] handle
 */
void httpd_ssl_stop(httpd_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif // _ESP_HTTPS_SERVER_H_

