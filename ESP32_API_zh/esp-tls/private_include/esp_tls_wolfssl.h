/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include "esp_tls.h"

/**
 * 为wolfssl创建ssl句柄的内部回调
 */
int esp_create_wolfssl_handle(const char *hostname, size_t hostlen, const void *cfg, esp_tls_t *tls);

/**
 * wolfssl_shandshake的内部回调
 */
int esp_wolfssl_handshake(esp_tls_t *tls, const esp_tls_cfg_t *cfg);

/**
 * wolfssl_ssl_read的内部回调API
 */
ssize_t esp_wolfssl_read(esp_tls_t *tls, char *data, size_t datalen);

/**
 * wolfssl_ssl_write的内部回调API
 */
ssize_t esp_wolfssl_write(esp_tls_t *tls, const char *data, size_t datalen);

/**
 * wolfssl_cleanup的内部回调，释放wolfssl使用的所有内存
 */
void esp_wolfssl_cleanup(esp_tls_t *tls);

/**
 * wolfssl证书验证的内部回调
 */
void esp_wolfssl_verify_certificate(esp_tls_t *tls);

/**
 * 用于删除wolfssl连接的内部回调
 */
void esp_wolfssl_conn_delete(esp_tls_t *tls);

/**
 * wolfssl_get_bytes_available的内部回调
 */
ssize_t esp_wolfssl_get_bytes_avail(esp_tls_t *tls);

/**
 * 使用wolfssl为TLS/SSL设置全局CA存储数据的回调函数
 */
esp_err_t esp_wolfssl_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes);

/**
 * 使用wolfssl释放TLS/SSL的全局ca存储的回调函数
 */
void esp_wolfssl_free_global_ca_store(void);

/**
 * 用于初始化TLS的全局ca存储的回调函数？使用wolfssl的SSL
 */
esp_err_t esp_wolfssl_init_global_ca_store(void);

/**
 * 用于初始化套接字包装器的wolfSSL函数（wolfSSL无操作）
 */
static inline void esp_wolfssl_net_init(esp_tls_t *tls)
{
}

#ifdef CONFIG_ESP_TLS_SERVER

/**
 * 使用wolfssl堆栈创建ESP-TLS服务器会话的函数
 */
int esp_wolfssl_server_session_create(esp_tls_cfg_server_t *cfg, int sockfd, esp_tls_t *tls);

/*
 * 删除服务器会话
 */
void esp_wolfssl_server_session_delete(esp_tls_t *tls);

#endif

