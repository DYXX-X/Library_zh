/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include "esp_tls.h"

/**
 * mbedtls_ssl_read的内部回调API
 */
ssize_t esp_mbedtls_read(esp_tls_t *tls, char *data, size_t datalen);

/**
 * mbedtls_ssl_write的内部回调API
 */
ssize_t esp_mbedtls_write(esp_tls_t *tls, const char *data, size_t datalen);

/**
 * mbedtls_handshake的内部回调
 */
int esp_mbedtls_handshake(esp_tls_t *tls, const esp_tls_cfg_t *cfg);

/**
 * mbedtls_cleanup的内部回调，释放mbedtls使用的所有内存
 */
void esp_mbedtls_cleanup(esp_tls_t *tls);

/**
 * mbedtls证书验证的内部回调
 */
void esp_mbedtls_verify_certificate(esp_tls_t *tls);

/**
 * 用于删除mbedtls连接的内部回调
 */
void esp_mbedtls_conn_delete(esp_tls_t *tls);

/**
 * mbedtls_get_bytes_available的内部回调
 */
ssize_t esp_mbedtls_get_bytes_avail(esp_tls_t *tls);

/**
 * 为mbedtls创建ssl句柄的内部回调
 */
esp_err_t esp_create_mbedtls_handle(const char *hostname, size_t hostlen, const void *cfg, esp_tls_t *tls);

/**
 * 用于初始化套接字包装器的mbedTLS函数
 */
static inline void esp_mbedtls_net_init(esp_tls_t *tls)
{
    mbedtls_net_init(&tls->server_fd);
}

#ifdef CONFIG_ESP_TLS_SERVER
/**
 * set_server_config的内部回调
 *
 * /注意：-只能与mbedtls ssl库一起使用
 */
esp_err_t set_server_config(esp_tls_cfg_server_t *cfg, esp_tls_t *tls);

/**
 * mbedtls_server_session_create的内部回调
 *
 * /注意：-该函数只能与mbedtls ssl库一起使用
 */
int esp_mbedtls_server_session_create(esp_tls_cfg_server_t *cfg, int sockfd, esp_tls_t *tls);

/**
 * mbedtls_server_session_delete的内部回调
 *
 * /注意：-该函数只能与mbedtls ssl库一起使用
 */
void esp_mbedtls_server_session_delete(esp_tls_t *tls);

#ifdef CONFIG_ESP_TLS_SERVER_SESSION_TICKETS
/**
 * 设置服务器端会话票证上下文的内部功能
 *
 * /注意：-该函数只能与mbedtls ssl库一起使用
 */
esp_err_t esp_mbedtls_server_session_ticket_ctx_init(esp_tls_server_session_ticket_ctx_t *cfg);

/**
 * 释放服务器端会话票证上下文的内部功能
 *
 * /注意：-该函数只能与mbedtls ssl库一起使用
 */
void esp_mbedtls_server_session_ticket_ctx_free(esp_tls_server_session_ticket_ctx_t *cfg);
#endif
#endif

/**
 * set_client_config_function的内部回调
 */
esp_err_t set_client_config(const char *hostname, size_t hostlen, esp_tls_cfg_t *cfg, esp_tls_t *tls);

#ifdef CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS
/**
 * mbedtls_get_client_session的内部回调
 */
esp_tls_client_session_t *esp_mbedtls_get_client_session(esp_tls_t *tls);
#endif

/**
 * mbedtls_init_global_ca_store的内部回调
 */
esp_err_t esp_mbedtls_init_global_ca_store(void);

/**
 * 使用mbedtls为TLS/SSL设置全局CA存储数据的回调函数
 */
esp_err_t esp_mbedtls_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes);

/**
 * esp_tls_global_ca_store的内部回调
 */
mbedtls_x509_crt *esp_mbedtls_get_global_ca_store(void);

/**
 * 使用mbedtls释放TLS/SSL的全局ca存储的回调函数
 */
void esp_mbedtls_free_global_ca_store(void);

