/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _ESP_TLS_H_
#define _ESP_TLS_H_

#include <stdbool.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "esp_err.h"
#include "esp_tls_errors.h"
#ifdef CONFIG_ESP_TLS_USING_MBEDTLS
#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/esp_debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#ifdef CONFIG_ESP_TLS_SERVER_SESSION_TICKETS
#include "mbedtls/ssl_ticket.h"
#endif
#elif CONFIG_ESP_TLS_USING_WOLFSSL
#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/ssl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief ESP-TLS连接状态
 */
typedef enum esp_tls_conn_state {
    ESP_TLS_INIT = 0,
    ESP_TLS_CONNECTING,
    ESP_TLS_HANDSHAKE,
    ESP_TLS_FAIL,
    ESP_TLS_DONE,
} esp_tls_conn_state_t;

typedef enum esp_tls_role {
    ESP_TLS_CLIENT = 0,
    ESP_TLS_SERVER,
} esp_tls_role_t;

/**
 *  @brief ESP-TLS预共享密钥和提示结构
 */
typedef struct psk_key_hint {
    const uint8_t* key;                     /*!< 二进制格式的PSK身份验证模式中的密钥*/
    const size_t   key_size;                /*!< 钥匙的长度*/
    const char* hint;                       /*!< 字符串格式的PSK身份验证模式提示*/
} psk_hint_key_t;

/**
 * @brief esp-tls客户端会话票证ctx
 */
#ifdef CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS
typedef struct esp_tls_client_session {
    mbedtls_ssl_session saved_session;
} esp_tls_client_session_t;
#endif /* CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS */

/**
*  @brief 保持活动参数结构
*/
typedef struct tls_keep_alive_cfg {
    bool keep_alive_enable;               /*!< 启用保持活动超时*/
    int keep_alive_idle;                  /*!< 保持活动空闲时间（秒）*/
    int keep_alive_interval;              /*!< 保活间隔时间（秒）*/
    int keep_alive_count;                 /*!< 保持活动数据包重试发送计数*/
} tls_keep_alive_cfg_t;

/**
 * @brief      ESP-TLS配置参数
 *
 * @note       证书格式说明：
 *             -该结构包括证书颁发机构的证书、客户端或服务器的证书以及可以是PEM或DER格式的私钥。对于PEM格式，缓冲区必须以NULL结尾（证书大小中包含NULL字符）。
 *             -如果是PEM格式，证书颁发机构的证书可以是一系列证书，但如果是DER格式，则只能是一个证书
 *             -证书和私钥缓冲区的变量名称和大小被定义为联合，为传统的_pem_buf和_pem_bytes名称提供向后兼容性，这表明只支持pem格式。鼓励使用通用名称，如cacert_buf和cacert_bytes。
 */
typedef struct esp_tls_cfg {
    const char **alpn_protos;               /*!< HTTP2所需的应用程序协议。如果需要HTTP2/ALPN支持，则应协商协议列表。格式是长度后跟协议名称。对于最常见的情况，以下是可以的：const char alpn_protos=｛“h2”，NULL｝；-其中“h2”是协议名称*/

    union {
    const unsigned char *cacert_buf;        /*!< 缓冲区中的证书颁发机构证书。格式可以是PEM或DER，具体取决于mbedtls支持。如果是PEM，缓冲区应该以NULL结尾*/
    const unsigned char *cacert_pem_buf;    /*!< CA证书缓冲区旧名称*/
    };

    union {
    unsigned int cacert_bytes;              /*!< cacert_buf指向的证书颁发机构证书的大小（如果是PEM格式，则包括NULL终止符）*/
    unsigned int cacert_pem_bytes;          /*!< 证书颁发机构证书旧名称的大小*/
    };

    union {
    const unsigned char *clientcert_buf;    /*!< 缓冲区格式的客户端证书可以是PEM或DER，具体取决于mbedtls支持。如果是PEM，此缓冲区应以NULL结尾*/
    const unsigned char *clientcert_pem_buf;     /*!< 客户端证书旧版名称*/
    };

    union {
    unsigned int clientcert_bytes;          /*!< clientcert_pem_buf指向的客户端证书的大小（如果是pem格式，则包括NULL终止符）*/
    unsigned int clientcert_pem_bytes;      /*!< 客户端证书旧名称的大小*/
    };

    union {
    const unsigned char *clientkey_buf;     /*!< 缓冲区格式中的客户端密钥可以是PEM或DER，具体取决于mbedtls支持。如果是PEM，则此缓冲区应以NULL结尾*/
    const unsigned char *clientkey_pem_buf; /*!< 客户端密钥旧名称*/
    };

    union {
    unsigned int clientkey_bytes;           /*!< clientkey_pem_buf指向的客户端密钥的大小（如果是pem格式，则包括NULL终止符）*/
    unsigned int clientkey_pem_bytes;       /*!< 客户端密钥旧名称的大小*/
    };

    const unsigned char *clientkey_password;/*!< 客户端密钥解密密码字符串*/

    unsigned int clientkey_password_len;    /*!< clientkey_password指向的密码的字符串长度*/

    bool non_block;                         /*!< 配置非阻塞模式。如果设置为true，则在tls会话建立后，底层套接字将配置为非阻塞模式*/

    bool use_secure_element;                /*!< 启用此选项以使用安全元件或atecc608a芯片（与ESP32-WROOM-32SE集成）*/

    int timeout_ms;                         /*!< 网络超时（毫秒）*/

    bool use_global_ca_store;               /*!< 为设置此布尔值的所有连接使用全局ca_store。*/

    const char *common_name;                /*!< 如果非NULL，则服务器证书CN必须与此名称匹配。如果为NULL，则服务器证书CN必须与主机名匹配。*/

    bool skip_common_name;                  /*!< 跳过服务器证书CN字段的任何验证*/

    tls_keep_alive_cfg_t *keep_alive_cfg;   /*!< 为SSL连接启用TCP保持活动超时*/

    const psk_hint_key_t* psk_hint_key;     /*!< 指向PSK提示和密钥的指针。如果不为NULL（并且证书为NULL），则使用配置的设置启用PSK身份验证。重要提示：指针必须对连接有效*/

    esp_err_t (*crt_bundle_attach)(void *conf);
                                            /*!< 指向esp_crt_bundle_attach的函数指针。启用证书捆绑包用于服务器验证，必须在menuconfig中启用*/

    void *ds_data;                          /*!< 数字签名外围上下文的指针*/
    bool is_plain_tcp;                      /*!< 使用非TLS连接：当设置为true时，esp-TLS使用普通TCP传输，而不是TLS/SSL连接。注意，可以使用普通tcp传输直接与esp_tls_plain_tcp_connect（）API连接*/

    struct ifreq *if_name;                  /*!< 数据要通过的接口的名称。使用默认界面而不设置*/

#ifdef CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS
    esp_tls_client_session_t *client_session; /*! 客户端会话票证上下文的指针。*/
#endif /* CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS */
} esp_tls_cfg_t;

#ifdef CONFIG_ESP_TLS_SERVER
#if defined(CONFIG_ESP_TLS_SERVER_SESSION_TICKETS)
/**
 * @brief 根据RFC5077，支持TLS会话票证所需的数据结构
 */
typedef struct esp_tls_server_session_ticket_ctx {
    mbedtls_entropy_context entropy;                                            /*!< mbedTLS熵上下文结构*/

    mbedtls_ctr_drbg_context ctr_drbg;                                          /*!< mbedTLS ctr-drbg上下文结构。CTR_DRBG是基于AES-256的确定性随机比特生成*/
    mbedtls_ssl_ticket_context ticket_ctx;                                     /*!< 会话票证生成上下文*/
} esp_tls_server_session_ticket_ctx_t;
#endif

typedef struct esp_tls_cfg_server {
    const char **alpn_protos;                   /*!< HTTP2所需的应用程序协议。如果需要HTTP2/ALPN支持，则应协商协议列表。格式是长度后跟协议名称。对于最常见的情况，以下是可以的：const char alpn_protos=｛“h2”，NULL｝；-其中“h2”是协议名称*/

    union {
    const unsigned char *cacert_buf;        /*!< 缓冲区中的客户端CA证书。此缓冲区应以NULL结尾*/
    const unsigned char *cacert_pem_buf;    /*!< 客户端CA证书旧版名称*/
    };

    union {
    unsigned int cacert_bytes;              /*!< cacert_pem_buf指向的客户端CA证书的大小*/
    unsigned int cacert_pem_bytes;          /*!< 客户端CA证书旧名称的大小*/
    };

    union {
    const unsigned char *servercert_buf;        /*!< 缓冲区中的服务器证书此缓冲区应以NULL结尾*/
    const unsigned char *servercert_pem_buf;    /*!< 服务器证书旧版名称*/
    };

    union {
    unsigned int servercert_bytes;             /*!< servercert_pem_buf指向的服务器证书的大小*/
    unsigned int servercert_pem_bytes;          /*!< 服务器证书旧名称的大小*/
    };

    union {
    const unsigned char *serverkey_buf;         /*!< 缓冲区中的服务器密钥此缓冲区应以NULL结尾*/
    const unsigned char *serverkey_pem_buf;     /*!< 服务器密钥旧名称*/
    };

    union {
    unsigned int serverkey_bytes;               /*!< serverkey_pem_buf指向的服务器密钥的大小*/
    unsigned int serverkey_pem_bytes;           /*!< 服务器密钥旧名称的大小*/
    };

    const unsigned char *serverkey_password;    /*!< 服务器密钥解密密码字符串*/

    unsigned int serverkey_password_len;        /*!< serverkey_password指向的密码的字符串长度*/

#if defined(CONFIG_ESP_TLS_SERVER_SESSION_TICKETS)
    esp_tls_server_session_ticket_ctx_t * ticket_ctx; /*!< 会话票证生成上下文。必须调用esp_tls_cfg_server_session_tickts_init才能使用它。调用esp_tls_cfg_server_session_tickts_free释放与此上下文关联的数据。*/
#endif
} esp_tls_cfg_server_t;

/**
 * @brief 初始化服务器端TLS会话票证上下文
 *
 * 此函数初始化服务器端tls会话票证上下文，该上下文保存所有必要的数据结构，以根据RFC5077启用tls会话凭单。使用esp_tls_cfg_server_session_ctickets_free释放数据。
 *
 * @param[in]  cfg 服务器配置为esp_tls_cfg_server_t
 * @return 如果安装成功，则ESP_OK；如果上下文已初始化，则ESP_ERR_INVALID_ARG；如果内存分配失败，则ESP-ERR_NO_MEM
 */
esp_err_t esp_tls_cfg_server_session_tickets_init(esp_tls_cfg_server_t *cfg);

/**
 * @brief 释放服务器端TLS会话票证上下文
 *
 * @param cfg 服务器配置为esp_tls_cfg_server_t
 */
void esp_tls_cfg_server_session_tickets_free(esp_tls_cfg_server_t *cfg);
#endif /* ! CONFIG_ESP_TLS_SERVER */

/**
 * @brief      ESP-TLS连接手柄
 */
typedef struct esp_tls {
#ifdef CONFIG_ESP_TLS_USING_MBEDTLS
    mbedtls_ssl_context ssl;                                                    /*!< TLS/SSL上下文*/

    mbedtls_entropy_context entropy;                                            /*!< mbedTLS熵上下文结构*/

    mbedtls_ctr_drbg_context ctr_drbg;                                          /*!< mbedTLS ctr-drbg上下文结构。CTR_DRBG是基于AES-256的确定性随机比特生成*/

    mbedtls_ssl_config conf;                                                    /*!< 要在mbedtls_SSL_context结构之间共享的TLS/SSL配置*/

    mbedtls_net_context server_fd;                                              /*!< 套接字的mbedTLS包装类型*/

    mbedtls_x509_crt cacert;                                                    /*!< X.509 CA证书的容器*/

    mbedtls_x509_crt *cacert_ptr;                                               /*!< 指向正在使用的证书的指针。*/

    mbedtls_x509_crt clientcert;                                                /*!< X.509客户端证书的容器*/

    mbedtls_pk_context clientkey;                                               /*!< 客户端证书私钥的容器*/
#ifdef CONFIG_ESP_TLS_SERVER
    mbedtls_x509_crt servercert;                                                /*!< X.509服务器证书的容器*/

    mbedtls_pk_context serverkey;                                               /*!< 服务器证书的私钥容器*/
#endif
#elif CONFIG_ESP_TLS_USING_WOLFSSL
    void *priv_ctx;
    void *priv_ssl;
#endif
    int sockfd;                                                                 /*!< 基础套接字文件描述符。*/

    ssize_t (*read)(struct esp_tls  *tls, char *data, size_t datalen);          /*!< 用于从TLS/SSL连接读取数据的回调函数。*/

    ssize_t (*write)(struct esp_tls *tls, const char *data, size_t datalen);    /*!< 用于将数据写入TLS/SSL连接的回调函数。*/

    esp_tls_conn_state_t  conn_state;                                           /*!< ESP-TLS连接状态*/

    fd_set rset;                                                                /*!< 读取文件描述符*/

    fd_set wset;                                                                /*!< 写入文件描述符*/

    bool is_tls;                                                                /*!< 表示连接类型（TLS或NON-TLS）*/

    esp_tls_role_t role;                                                        /*!< esp-tls角色
                                                                                     - ESP_TLS_CLIENT - ESP_TLS_SERVER */

    esp_tls_error_handle_t error_handle;                                        /*!< 错误描述符句柄*/

} esp_tls_t;


/**
 * @brief      创建TLS连接
 *
 * 此函数分配并初始化esp tls结构句柄。
 *
 * @return      tls指向esp tls的指针，如果成功初始化，则作为esp tls句柄；如果分配错误，则为NULL
 */
esp_tls_t *esp_tls_init(void);




/**
 * @brief      创建新的阻止TLS/SSL连接
 *
 * 此函数以阻塞方式与指定主机建立TLS/SSL连接。
 *
 * 注意：此API是出于向后兼容的原因而提供的。具有相同功能的另一个函数是“esp_tls_conn_new_sync”（及其异步版本“esp_tls _conn_new_async”）
 *
 * @param[in]  hostname  主机的主机名。
 * @param[in]  hostlen   主机名的长度。
 * @param[in]  port      主机的端口号。
 * @param[in]  cfg       TLS配置为esp_TLS_cfg_t。如果您希望打开非TLS连接，请将此值保持为NULL。对于TLS连接，传递指向esp_TLS_cfg_t的指针。至少，该结构应为零初始化。
 *
 * @return 指向esp_tls_t的指针，如果无法打开连接，则返回NULL。
 */
esp_tls_t *esp_tls_conn_new(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg)  __attribute__ ((deprecated));

/**
 * @brief      创建新的阻止TLS/SSL连接
 *
 * 此函数以阻塞方式与指定主机建立TLS/SSL连接。
 *
 * @param[in]  hostname  主机的主机名。
 * @param[in]  hostlen   主机名的长度。
 * @param[in]  port      主机的端口号。
 * @param[in]  cfg       TLS配置为esp_TLS_cfg_t。如果您希望打开非TLS连接，请将此值保持为NULL。对于TLS连接，传递指向esp_TLS_cfg_t的指针。至少，该结构应为零初始化。
 * @param[in]  tls       指向esp-tls作为esp-tls句柄的指针。
 *
 * @return
 *             --1如果连接建立失败。
 *             -1如果连接建立成功。
 *             -0如果连接状态正在进行中。
 */
int esp_tls_conn_new_sync(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg, esp_tls_t *tls);

/**
 * @brief      使用给定的“HTTP”url创建新的阻止TLS/SSL连接
 *
 * 行为与esp_tls_conn_new（）API相同。但是，此API接受主机的url。
 *
 * @param[in]  url  主机的url。
 * @param[in]  cfg  TLS配置为esp_TLS_cfg_t。如果您希望打开非TLS连接，请将此值保持为NULL。对于TLS连接，传递指针指向“esp_TLS_cfg_t”。至少，该结构应为零初始化。
 * @return 指向esp_tls_t的指针，如果无法打开连接，则返回NULL。
 */
esp_tls_t *esp_tls_conn_http_new(const char *url, const esp_tls_cfg_t *cfg);

/**
 * @brief      创建新的非阻塞TLS/SSL连接
 *
 * 此函数启动与指定主机的非阻塞TLS/SSL连接，但由于其非阻塞性，它不会等待连接建立。
 *
 * @param[in]  hostname  主机的主机名。
 * @param[in]  hostlen   主机名的长度。
 * @param[in]  port      主机的端口号。
 * @param[in]  cfg       TLS配置为esp_TLS_cfg_t`此结构的non_block成员应设置为true。
 * @param[in]  tls       指向esp-tls作为esp-tls句柄的指针。
 *
 * @return
 *             --1如果连接建立失败。
 *             -0如果正在建立连接。
 *             -1如果连接建立成功。
 */
int esp_tls_conn_new_async(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg, esp_tls_t *tls);

/**
 * @brief      使用给定的“HTTP”url创建新的非阻塞TLS/SSL连接
 *
 * 行为与esp_tls_conn_new（）API相同。但是，此API接受主机的url。
 *
 * @param[in]  url     主机的url。
 * @param[in]  cfg     TLS配置为esp_TLS_cfg_t。
 * @param[in]  tls     指向esp-tls作为esp-tls句柄的指针。
 *
 * @return
 *             --1如果连接建立失败。
 *             -0如果正在建立连接。
 *             -1如果连接建立成功。
 */
int esp_tls_conn_http_new_async(const char *url, const esp_tls_cfg_t *cfg, esp_tls_t *tls);

/**
 * @brief      从缓冲区“data”写入指定的tls连接。
 *
 * @param[in]  tls      指向esp-tls作为esp-tls句柄的指针。
 * @param[in]  data     将从中写入数据的缓冲区。
 * @param[in]  datalen  数据缓冲区的长度。
 *
 * @return
 *             ->=0如果写入操作成功，则返回值为实际写入TLS/SSL连接的字节数。
 *             -如果写入操作未成功，则<0，因为发生错误或调用进程必须执行操作。
 *             -ESP_TLS_ERR_SSL_WANT_READ/ESP_TLS-ERR_SSL-WANT_WRITE。如果握手不完整并等待数据可供读取。在这种情况下，当底层传输准备好运行时，需要再次调用该函数。
 */
static inline ssize_t esp_tls_conn_write(esp_tls_t *tls, const void *data, size_t datalen)
{
    return tls->write(tls, (char *)data, datalen);
}

/**
 * @brief      从指定的tls连接读取缓冲区“data”。
 *
 * @param[in]  tls      指向esp-tls作为esp-tls句柄的指针。
 * @param[in]  data     保存读取数据的缓冲区。
 * @param[in]  datalen  数据缓冲区的长度。
 *
 * @return
 *             ->0如果读取操作成功，则返回值为从TLS/SSL连接实际读取的字节数。
 *             -如果读取操作不成功，则为0。基础连接已关闭。
 *             -如果读取操作未成功，则<0，因为发生错误或调用进程必须执行操作。
 */
static inline ssize_t esp_tls_conn_read(esp_tls_t *tls, void  *data, size_t datalen)
{
    return tls->read(tls, (char *)data, datalen);
}

/**
 * @brief      用于关闭tls/SSL连接的esp_tls_conn_destroy（）的兼容版本
 *
 * @note 此API将在IDFv5.0中删除
 *
 * @param[in]  tls  指向esp-tls作为esp-tls句柄的指针。
 */
void esp_tls_conn_delete(esp_tls_t *tls);

/**
 * @brief      关闭TLS/SSL连接并释放所有分配的资源。
 *
 * 应调用此函数以关闭使用esp_tls_conn_new（）或esp_tls-conn_http_new（）API打开的每个tls连接。
 *
 * @param[in]  tls  指向esp-tls作为esp-tls句柄的指针。
 *
 * @return    -成功时为0
 *            --1如果套接字错误或无效参数
 */
int esp_tls_conn_destroy(esp_tls_t *tls);

/**
 * @brief      返回要从当前记录中读取的剩余应用程序数据字节数
 *
 * 此API是mbedtls的mbedtls_ssl_get_bytes_available（）API的包装。
 *
 * @param[in]  tls  指向esp-tls作为esp-tls句柄的指针。
 *
 * @return
 *            -如果参数无效，则为-1
 *            -应用程序数据记录读取缓冲区中可用的字节数
 */
ssize_t esp_tls_get_bytes_avail(esp_tls_t *tls);

/**
 * @brief       从esp_tls会话返回连接套接字文件描述符
 *
 * @param[in]   tls          esp_tls上下文的句柄
 *
 * @param[out]  sockfd       指向sockfd值的int指针。
 *
 * @return     -成功时的ESP_OK，将使用连接的套接字文件描述符更新sockfd的值
 *             -ESP_ERR_INVALID_ARG如果（tls==NULL | | sockfd==NULL）
 */
esp_err_t esp_tls_get_conn_sockfd(esp_tls_t *tls, int *sockfd);

/**
 * @brief      创建一个初始为空的全局CA存储。
 *
 * 如果应用程序希望对多个连接使用相同的CA存储，则应调用此函数。此函数初始化全局CA存储，然后可以通过调用esp_tls_set_global_CA_store（）来设置该存储。要有效，必须在调用esp_tls_set_global_ca_store（）之前调用此函数。
 *
 * @return
 *             -如果创建全局CA存储成功，则ESP_OK。
 *             -如果分配mbedTLS资源时发生错误，则返回ESP_ERR_NO_MEM。
 */
esp_err_t esp_tls_init_global_ca_store(void);

/**
 * @brief      使用pem格式提供的缓冲区设置全局CA存储。
 *
 * 如果应用程序希望为多个连接设置全局CA存储，即将提供的缓冲区中的证书添加到证书链，则应调用此函数。如果尚未调用该函数，则该函数隐式调用esp_tls_init_global_ca_store（）。应用程序必须在调用esp_tls_conn_new（）之前调用此函数。
 *
 * @param[in]  cacert_pem_buf    具有pem格式证书的缓冲区。此缓冲区用于创建全局CA存储，其他tls连接可以使用该存储。
 * @param[in]  cacert_pem_bytes  缓冲区的长度。
 *
 * @return
 *             -如果添加证书成功，则返回ESP_OK。
 *             -如果发生错误或调用进程必须采取操作，则为其他。
 */
esp_err_t esp_tls_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes);

/**
 * @brief      释放当前正在使用的全局CA存储。
 *
 * 全局CA存储用于存储所有已解析证书的内存被释放。如果应用程序不再需要全局CA存储，则可以调用此API。
 */
void esp_tls_free_global_ca_store(void);

/**
 * @brief      返回esp_tls中的最后一个错误以及详细的mbedtls相关错误代码。返回时内部清除错误信息
 *
 * @param[in]  h              esp-tls错误句柄。
 * @param[out] esp_tls_code   从mbedtls api返回的最后一个错误代码（如果没有，则设置为零）如果调用者不关心esp_tls_code，则该指针可能为NULL
 * @param[out] esp_tls_flags  最后一个认证验证标志（如果没有，则设置为零）如果调用者不关心esp_tls_code，则该指针可能为NULL
 *
 * @return
 *            -如果参数无效，则返回ESP_ERR_INVALID_STATE
 *            -如果未发生错误，则ESP_OK（0）
 *            -特定错误代码（基于ESP_ERR_ESP_TLS_BASE），否则
 */
esp_err_t esp_tls_get_and_clear_last_error(esp_tls_error_handle_t h, int *esp_tls_code, int *esp_tls_flags);

/**
 * @brief      返回在特定类型的esp_tls中捕获的最后一个错误。返回时内部清除错误信息
 *
 * @param[in]  h              esp-tls错误句柄。
 * @param[in]  err_type       特定错误类型
 * @param[out] error_code     从mbedtls api返回的最后一个错误代码（如果没有，则设置为零）如果调用者不关心esp_tls_code，则该指针可能为NULL
 * @return
 *            -如果参数无效，则返回ESP_ERR_INVALID_STATE
 *            -如果返回并清除了有效错误，则ESP_OK
 */
esp_err_t esp_tls_get_and_clear_error_type(esp_tls_error_handle_t h, esp_tls_error_type_t err_type, int *error_code);

#if CONFIG_ESP_TLS_USING_MBEDTLS
/**
 * @brief      获取当前正在使用的全局CA存储的指针。
 *
 * 应用程序必须首先调用esp_tls_set_global_ca_store（）。然后，应用程序可以将相同的CA存储用于除esp_tls之外的API。
 *
 * @note       修改指针可能会导致验证证书失败。
 *
 * @return
 *             -如果成功，则指向当前正在使用的全局CA存储的指针。
 *             -如果没有全局CA存储集，则为NULL。
 */
mbedtls_x509_crt *esp_tls_get_global_ca_store(void);

#endif /* CONFIG_ESP_TLS_USING_MBEDTLS */
#ifdef CONFIG_ESP_TLS_SERVER
/**
 * @brief      创建TLS/SSL服务器会话
 *
 * 此函数为已接受的客户端连接创建TLS/SSL服务器上下文，并与客户端执行TLS/SSL握手
 *
 * @param[in]  cfg      指向esp_tls_cfg_server_t的指针
 * @param[in]  sockfd   已接受连接的FD
 * @param[out] tls      指向已分配esp_tls_t的指针
 *
 * @return
 *          -如果成功，则为0
 *          -出现错误时<0
 *
 */
int esp_tls_server_session_create(esp_tls_cfg_server_t *cfg, int sockfd, esp_tls_t *tls);

/**
 * @brief      关闭服务器端TLS/SSL连接并释放所有分配的资源。
 *
 * 应调用此函数以关闭使用esp_tls_server_session_create（）打开的每个tls连接
 *
 * @param[in]  tls  指向esp_tls_t的指针
 */
void esp_tls_server_session_delete(esp_tls_t *tls);
#endif /* ! CONFIG_ESP_TLS_SERVER */

/**
 * @brief 创建普通TCP连接，成功时返回有效的套接字fd或错误句柄
 *
 * @param[in]  host      主机的主机名。
 * @param[in]  hostlen   主机名的长度。
 * @param[in]  port      主机的端口号。
 * @param[in]  cfg       ESP-TLS配置为ESP_TLS_cfg_t。
 * @param[out] error_handle ESP-TLS错误句柄保持连接期间发生的潜在错误
 * @param[out] sockfd    套接字描述符（如果在TCP层上成功连接）
 * @return     成功时ESP_OK ESP_ERR_INVALID_ARG，如果失败时输出参数基于ESP-TLS的错误代码无效
 */
esp_err_t esp_tls_plain_tcp_connect(const char *host, int hostlen, int port, const esp_tls_cfg_t *cfg, esp_tls_error_handle_t error_handle, int *sockfd);

#ifdef CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS
/**
 * @brief 获取客户端会话票证
 *
 * 当TLS连接已建立时，应调用此函数。这可以在esp_tls_cfg_t结构中再次传递给相应的tls会话创建（例如esp_tls_conn_http_new）API，用于会话恢复。
 *
 * @param[in]  esp_tls 上下文为esp_tls_t
 * @return 指向保存的客户端会话的指针。失败时为NULL
 */
esp_tls_client_session_t *esp_tls_get_client_session(esp_tls_t *tls);
#endif /* CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS */
#ifdef __cplusplus
}
#endif

#endif /* ! _ESP_TLS_H_ */

