/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_HTTP_CLIENT_H
#define _ESP_HTTP_CLIENT_H

#include "freertos/FreeRTOS.h"
#include "http_parser.h"
#include "sdkconfig.h"
#include "esp_err.h"
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_HTTP_BUF_SIZE (512)

typedef struct esp_http_client *esp_http_client_handle_t;
typedef struct esp_http_client_event *esp_http_client_event_handle_t;

/**
 * @brief   HTTP客户端事件id
 */
typedef enum {
    HTTP_EVENT_ERROR = 0,       /*!< 当执行过程中出现任何错误时，会发生此事件*/
    HTTP_EVENT_ON_CONNECTED,    /*!< 一旦HTTP连接到服务器，就不会执行任何数据交换*/
    HTTP_EVENT_HEADERS_SENT,     /*!< 将所有标头发送到服务器后*/
    HTTP_EVENT_HEADER_SENT = HTTP_EVENT_HEADERS_SENT, /*!< 为了向后兼容，保留了此标头，并将在将来的版本（特别是idf）中弃用*/
    HTTP_EVENT_ON_HEADER,       /*!< 在接收从服务器发送的每个标头时发生*/
    HTTP_EVENT_ON_DATA,         /*!< 从服务器接收数据时发生，可能是数据包的多个部分*/
    HTTP_EVENT_ON_FINISH,       /*!< 在完成HTTP会话时发生*/
    HTTP_EVENT_DISCONNECTED,    /*!< 连接已断开*/
} esp_http_client_event_id_t;

/**
 * @brief      HTTP客户端事件数据
 */
typedef struct esp_http_client_event {
    esp_http_client_event_id_t event_id;    /*!< event_id，以了解事件的原因*/
    esp_http_client_handle_t client;        /*!< esp_http_client_handle_t上下文*/
    void *data;                             /*!< 事件的数据*/
    int data_len;                           /*!< 数据的数据长度*/
    void *user_data;                        /*!< user_data上下文，来自esp_http_client_config_t user_data*/
    char *header_key;                       /*!< 对于HTTP_EVENT_ON_HEADER EVENT_id，它存储当前的HTTP头密钥*/
    char *header_value;                     /*!< 对于HTTP_EVENT_ON_HEADER EVENT_id，它存储当前的HTTP头值*/
} esp_http_client_event_t;


/**
 * @brief      HTTP客户端传输
 */
typedef enum {
    HTTP_TRANSPORT_UNKNOWN = 0x0,   /*!< 未知的*/
    HTTP_TRANSPORT_OVER_TCP,        /*!< tcp传输*/
    HTTP_TRANSPORT_OVER_SSL,        /*!< 通过ssl传输*/
} esp_http_client_transport_t;

typedef esp_err_t (*http_event_handle_cb)(esp_http_client_event_t *evt);

/**
 * @brief HTTP方法
 */
typedef enum {
    HTTP_METHOD_GET = 0,    /*!< HTTP GET方法*/
    HTTP_METHOD_POST,       /*!< HTTP POST方法*/
    HTTP_METHOD_PUT,        /*!< HTTP PUT方法*/
    HTTP_METHOD_PATCH,      /*!< HTTP PATCH方法*/
    HTTP_METHOD_DELETE,     /*!< HTTP DELETE方法*/
    HTTP_METHOD_HEAD,       /*!< HTTP HEAD方法*/
    HTTP_METHOD_NOTIFY,     /*!< HTTP NOTIFY方法*/
    HTTP_METHOD_SUBSCRIBE,  /*!< HTTP SUBSCRIBE方法*/
    HTTP_METHOD_UNSUBSCRIBE,/*!< HTTP UNSUBSCRIBE方法*/
    HTTP_METHOD_OPTIONS,    /*!< HTTP OPTIONS方法*/
    HTTP_METHOD_COPY,       /*!< HTTP COPY方法*/
    HTTP_METHOD_MOVE,       /*!< HTTP MOVE方法*/
    HTTP_METHOD_LOCK,       /*!< HTTP LOCK方法*/
    HTTP_METHOD_UNLOCK,     /*!< HTTP UNLOCK方法*/
    HTTP_METHOD_PROPFIND,   /*!< HTTP PROPFIND方法*/
    HTTP_METHOD_PROPPATCH,  /*!< HTTP PROPATCH方法*/
    HTTP_METHOD_MKCOL,      /*!< HTTP MKCOL方法*/
    HTTP_METHOD_MAX,
} esp_http_client_method_t;

/**
 * @brief HTTP身份验证类型
 */
typedef enum {
    HTTP_AUTH_TYPE_NONE = 0,    /*!< 无认证*/
    HTTP_AUTH_TYPE_BASIC,       /*!< HTTP基本身份验证*/
    HTTP_AUTH_TYPE_DIGEST,      /*!< HTTP拒绝身份验证*/
} esp_http_client_auth_type_t;

/**
 * @brief HTTP配置
 */
typedef struct {
    const char                  *url;                /*!< HTTP URL，URL上的信息是最重要的，它会覆盖下面的其他字段（如果有的话）*/
    const char                  *host;               /*!< 域或IP作为字符串*/
    int                         port;                /*!< 要连接的端口，默认取决于esp_http_client_transport_t（80或443）*/
    const char                  *username;           /*!< 用于Http身份验证*/
    const char                  *password;           /*!< 用于Http身份验证*/
    esp_http_client_auth_type_t auth_type;           /*!< Http身份验证类型，请参见`esp_Http_client_auth_type_t`*/
    const char                  *path;               /*!< HTTP路径，如果未设置，则默认为“/”*/
    const char                  *query;              /*!< HTTP查询*/
    const char                  *cert_pem;           /*!< SSL服务器认证，PEM格式为字符串，如果客户端需要验证服务器*/
    size_t                      cert_len;            /*!< cert_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char                  *client_cert_pem;    /*!< SSL客户端认证，PEM格式为字符串，如果服务器需要验证客户端*/
    size_t                      client_cert_len;     /*!< client_cert_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char                  *client_key_pem;     /*!< SSL客户端密钥，PEM格式为字符串，如果服务器需要验证客户端*/
    size_t                      client_key_len;      /*!< client_key_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char                  *client_key_password;      /*!< 客户端密钥解密密码字符串*/
    size_t                      client_key_password_len;   /*!< client_key_password指向的密码的字符串长度*/
    const char                  *user_agent;         /*!< 要与HTTP请求一起发送的用户代理字符串*/
    esp_http_client_method_t    method;                   /*!< HTTP方法*/
    int                         timeout_ms;               /*!< 网络超时（毫秒）*/
    bool                        disable_auto_redirect;    /*!< 禁用HTTP自动重定向*/
    int                         max_redirection_count;    /*!< 接收HTTP重定向状态代码时的最大重定向次数，如果为零，则使用默认值*/
    int                         max_authorization_retries;    /*!< 接收HTTP未授权状态代码时的最大连接重试次数，如果为零，则使用默认值。如果-1，则禁用授权重试*/
    http_event_handle_cb        event_handler;             /*!< HTTP事件句柄*/
    esp_http_client_transport_t transport_type;           /*!< HTTP传输类型，请参见`esp_HTTP_client_transport_t`*/
    int                         buffer_size;              /*!< HTTP接收缓冲区大小*/
    int                         buffer_size_tx;           /*!< HTTP传输缓冲区大小*/
    void                        *user_data;               /*!< HTTP用户数据上下文*/
    bool                        is_async;                 /*!< 设置异步模式，目前仅支持HTTPS*/
    bool                        use_global_ca_store;      /*!< 为设置此布尔值的所有连接使用全局ca_store。*/
    bool                        skip_cert_common_name_check;    /*!< 跳过服务器证书CN字段的任何验证*/
    esp_err_t (*crt_bundle_attach)(void *conf);      /*!< 指向esp_crt_bundle_attach的函数指针。启用证书捆绑包用于服务器验证，必须在menuconfig中启用*/
    bool                        keep_alive_enable;   /*!< 启用保持活动超时*/
    int                         keep_alive_idle;     /*!< 保持活动空闲时间。默认值为5（秒）*/
    int                         keep_alive_interval; /*!< 保活间隔时间。默认值为5（秒）*/
    int                         keep_alive_count;    /*!< 保活数据包重试发送计数。默认值为3个计数*/
    struct ifreq                *if_name;            /*!< 数据要通过的接口的名称。使用默认界面而不设置*/
} esp_http_client_config_t;

/**
 * HTTP状态代码的枚举。
 */
typedef enum {
    /* 2xx-成功*/
    HttpStatus_Ok                = 200,

    /* 3xx-重定向*/
    HttpStatus_MultipleChoices   = 300,
    HttpStatus_MovedPermanently  = 301,
    HttpStatus_Found             = 302,
    HttpStatus_TemporaryRedirect = 307,

    /* 4xx-客户端错误*/
    HttpStatus_BadRequest        = 400,
    HttpStatus_Unauthorized      = 401,
    HttpStatus_Forbidden         = 403,
    HttpStatus_NotFound          = 404,

    /* 5xx-服务器错误*/
    HttpStatus_InternalError     = 500
} HttpStatus_Code;

#define ESP_ERR_HTTP_BASE               (0x7000)                    /*!< HTTP错误代码的起始数量*/
#define ESP_ERR_HTTP_MAX_REDIRECT       (ESP_ERR_HTTP_BASE + 1)     /*!< 错误超过HTTP重定向数*/
#define ESP_ERR_HTTP_CONNECT            (ESP_ERR_HTTP_BASE + 2)     /*!< 打开HTTP连接时出错*/
#define ESP_ERR_HTTP_WRITE_DATA         (ESP_ERR_HTTP_BASE + 3)     /*!< 写入HTTP数据时出错*/
#define ESP_ERR_HTTP_FETCH_HEADER       (ESP_ERR_HTTP_BASE + 4)     /*!< 从服务器读取HTTP标头时出错*/
#define ESP_ERR_HTTP_INVALID_TRANSPORT  (ESP_ERR_HTTP_BASE + 5)     /*!< 输入方案不支持传输*/
#define ESP_ERR_HTTP_CONNECTING         (ESP_ERR_HTTP_BASE + 6)     /*!< 尚未建立HTTP连接*/
#define ESP_ERR_HTTP_EAGAIN             (ESP_ERR_HTTP_BASE + 7)     /*!< errno EAGAIN到esp_err_t的映射*/
#define ESP_ERR_HTTP_CONNECTION_CLOSED  (ESP_ERR_HTTP_BASE + 8)     /*!< 从对等端读取FIN并关闭连接*/

/**
 * @brief      启动HTTP会话此函数必须是要调用的第一个函数，并且它返回esp_HTTP_client_handle_t，您必须将其用作接口中其他函数的输入。操作完成后，此调用必须对esp_http_client_cleanup进行相应的调用。
 *
 * @param[in]  config   配置，请参见`http_client_config_t`
 *
 * @return
 *     -`esp_http_client_handle_t`
 *     -如果有错误，则为NULL
 */
esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config);

/**
 * @brief      在“esp_http_client_init”和所有选项调用完成后调用此函数，并将按照选项中的描述执行传输。必须使用与返回的esp_http_client_init调用相同的esp_hhttp_client_handle_t作为输入来调用它。esp_http_client_express以阻塞或非阻塞方式执行整个请求。默认情况下，API以阻塞方式执行请求，并在完成或失败时返回；如果遇到EAGAIN/EWOULDBLOCK或EINPROGRESS或失败，则以非阻塞方式返回。在非阻塞请求的情况下，用户可以多次调用此API，除非请求和响应完成或出现故障。要启用非阻塞esp_http_client_perform（），必须在调用esp_http_client_init（）API时设置esp_http/client_config_t的“is_async”成员。在使用相同的esp_http_client_handle_t时，可以对esp_http_client_express执行任意数量的调用。如果服务器允许，则基础连接可以保持打开状态。如果您打算传输多个文件，我们甚至鼓励您这样做。esp_http_client随后将尝试在以下传输中重复使用相同的连接，从而使操作更快，CPU占用更少，使用更少的网络资源。请注意，您必须在调用之间使用“esp_http_client_set_”，以设置以下esp_http_client_execut的选项。
 *
 * @note       决不能使用同一客户端句柄从两个位置同时调用此函数。让函数在下次调用之前先返回。如果要并行传输，必须使用多个esp_http_client_handle_t。此函数包括“esp_http_client_open”->“esp_http_client_write”->”esp_http_client_fetch_headers“->”esp_http_client_read'（和选项）“esp_hhttp_client_close”。
 *
 * @param      client  esp_http_client句柄
 *
 * @return
 *  -ESP_OK打开成功
 *  -ESP_FAIL出错
 */
esp_err_t esp_http_client_perform(esp_http_client_handle_t client);

/**
 * @brief      为客户端设置URL，当执行此行为时，URL中的选项将替换旧选项
 *
 * @param[in]  client  esp_http_client句柄
 * @param[in]  url     url
 *
 * @return
 *  - ESP_OK
 *  - ESP_FAIL
 */
esp_err_t esp_http_client_set_url(esp_http_client_handle_t client, const char *url);

/**
 * @brief      设置post数据时，必须在“esp_http_client_execut”之前调用此函数。注意：传递给此函数的数据参数是指针，此函数不会复制数据
 *
 * @param[in]  client  esp_http_client句柄
 * @param[in]  data    后数据指针
 * @param[in]  len     支柱长度
 *
 * @return
 *  - ESP_OK
 *  - ESP_FAIL
 */
esp_err_t esp_http_client_set_post_field(esp_http_client_handle_t client, const char *data, int len);

/**
 * @brief      获取当前帖子字段信息
 *
 * @param[in]  client  客户
 * @param[out] data    指向后数据指针
 *
 * @return     后期数据大小
 */
int esp_http_client_get_post_field(esp_http_client_handle_t client, char **data);

/**
 * @brief      设置http请求头，必须在esp_http_client_init之后和任何执行函数之前调用此函数
 *
 * @param[in]  client  esp_http_client句柄
 * @param[in]  key     标题键
 * @param[in]  value   标题值
 *
 * @return
 *  - ESP_OK
 *  - ESP_FAIL
 */
esp_err_t esp_http_client_set_header(esp_http_client_handle_t client, const char *key, const char *value);

/**
 * @brief      获取http请求标头。如果没有与指定的键相同的标头，value参数将设置为NULL，否则标头值的地址将分配给value参数。必须在“esp_http_client_init”之后调用此函数。
 *
 * @param[in]  client  esp_http_client句柄
 * @param[in]  key     标题键
 * @param[out] value   标题值
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_http_client_get_header(esp_http_client_handle_t client, const char *key, char **value);

/**
 * @brief      获取http请求用户名。用户名缓冲区的地址将分配给value参数。必须在“esp_http_client_init”之后调用此函数。
 *
 * @param[in]  client  esp_http_client句柄
 * @param[out] value   用户名值
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_get_username(esp_http_client_handle_t client, char **value);

/**
 * @brief      设置http请求用户名。用户名参数的值将分配给用户名缓冲区。如果用户名参数为NULL，则将释放用户名缓冲区。
 *
 * @param[in]  client    esp_http_client句柄
 * @param[in]  username  用户名值
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_set_username(esp_http_client_handle_t client, const char *username);

/**
 * @brief      获取http请求密码。密码缓冲区的地址将分配给值参数。必须在“esp_http_client_init”之后调用此函数。
 *
 * @param[in]  client  esp_http_client句柄
 * @param[out] value   密码值
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_get_password(esp_http_client_handle_t client, char **value);

/**
 * @brief      设置http请求密码。密码参数的值将分配给密码缓冲区。如果密码参数为NULL，则将释放密码缓冲区。
 *
 * @param[in]  client    esp_http_client句柄
 * @param[in]  password  密码值
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_set_password(esp_http_client_handle_t client, const char *password);

/**
 * @brief      设置http请求auth_type。
 *
 * @param[in]  client    esp_http_client句柄
 * @param[in]  auth_type esp_http_client身份验证类型
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_set_authtype(esp_http_client_handle_t client, esp_http_client_auth_type_t auth_type);

/**
 * @brief      获取HTTP客户端会话错误号
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return
 *         -（-1）如果参数无效
 *         -错误No
 */
int esp_http_client_get_errno(esp_http_client_handle_t client);

/**
 * @brief      设置http请求方法
 *
 * @param[in]  client  esp_http_client句柄
 * @param[in]  method  方法
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_set_method(esp_http_client_handle_t client, esp_http_client_method_t method);

/**
 * @brief      设置http请求超时
 *
 * @param[in]  client      esp_http_client句柄
 * @param[in]  timeout_ms  超时值
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_http_client_set_timeout_ms(esp_http_client_handle_t client, int timeout_ms);

/**
 * @brief      删除http请求标头
 *
 * @param[in]  client  esp_http_client句柄
 * @param[in]  key     钥匙
 *
 * @return
 *  - ESP_OK
 *  - ESP_FAIL
 */
esp_err_t esp_http_client_delete_header(esp_http_client_handle_t client, const char *key);

/**
 * @brief      此函数将打开连接，写入所有标头字符串并返回
 *
 * @param[in]  client     esp_http_client句柄
 * @param[in]  write_len  需要写入服务器的HTTP内容长度
 *
 * @return
 *  - ESP_OK
 *  - ESP_FAIL
 */
esp_err_t esp_http_client_open(esp_http_client_handle_t client, int write_len);

/**
 * @brief     此函数将向esp_HTTP_client_open（）之前打开的HTTP连接写入数据
 *
 * @param[in]  client  esp_http_client句柄
 * @param      buffer  缓冲区
 * @param[in]  len     此值不能大于提供给esp_http_client_open（）的write_len参数
 *
 * @return
 *     -（-1）如果有错误
 *     -写入数据的长度
 */
int esp_http_client_write(esp_http_client_handle_t client, const char *buffer, int len);

/**
 * @brief      此函数需要在esp_http_client_open之后调用，它将从http流中读取，处理所有接收头
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return
 *     -（0）如果流不包含内容长度标头或分块编码（由“esp_http_client_is_chunked”响应检查）
 *     -（-1:ESP_FAIL）如果有任何错误
 *     -下载由内容长度标头定义的数据长度
 */
int esp_http_client_fetch_headers(esp_http_client_handle_t client);


/**
 * @brief      检查响应数据是否分块
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return     真或假
 */
bool esp_http_client_is_chunked_response(esp_http_client_handle_t client);

/**
 * @brief      从http流读取数据
 *
 * @param[in]  client  esp_http_client句柄
 * @param      buffer  缓冲区
 * @param[in]  len     长度
 *
 * @return
 *     -（-1）如果有错误
 *     -读取的数据长度
 */
int esp_http_client_read(esp_http_client_handle_t client, char *buffer, int len);


/**
 * @brief      获取http响应状态代码，如果此函数在`esp_http_client_execut之后调用，则为有效值`
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return     状态代码
 */
int esp_http_client_get_status_code(esp_http_client_handle_t client);

/**
 * @brief      如果此函数在`esp_http_client_execut之后调用，则获取http响应内容长度（从标头内容长度）的有效值`
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return
 *     -（-1）分块传输
 *     -内容长度值（字节）
 */
int esp_http_client_get_content_length(esp_http_client_handle_t client);

/**
 * @brief      关闭http连接，仍保留所有http请求资源
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_http_client_close(esp_http_client_handle_t client);

/**
 * @brief      此函数必须是调用会话的最后一个函数。它与esp_http_client_init函数相反，必须使用与esp_hhttp_client_int调用返回的输入相同的句柄来调用。这可能会关闭此句柄使用的所有连接，并且可能一直保持打开状态。如果要传输更多文件，请不要调用此函数，重新使用句柄是esp_http_client性能良好的关键。
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_http_client_cleanup(esp_http_client_handle_t client);

/**
 * @brief      获取传输类型
 *
 * @param[in]  client   esp_http_client句柄
 *
 * @return
 *     - HTTP_TRANSPORT_UNKNOWN
 *     - HTTP_TRANSPORT_OVER_TCP
 *     - HTTP_TRANSPORT_OVER_SSL
 */
esp_http_client_transport_t esp_http_client_get_transport_type(esp_http_client_handle_t client);

/**
 * @brief      设置重定向URL。当从服务器接收到30x代码时，客户端存储服务器提供的重定向URL。此函数将设置要重定向的当前URL，以使客户端能够执行重定向请求。
 *
 * @param[in]  client  esp_http_client句柄
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_http_client_set_redirection(esp_http_client_handle_t client);

/**
 * @brief      在接收到HTTP状态代码401时，可以调用该API来添加授权信息。
 *
 * @note       有可能接收带有重定向状态代码的正文消息，因此请确保在调用此API后清除正文数据。
 *
 * @param[in]  client   esp_http_client句柄
 */
void esp_http_client_add_auth(esp_http_client_handle_t client);

/**
 * @brief      检查是否已读取响应中的全部数据而没有任何错误。
 *
 * @param[in]  client   esp_http_client句柄
 *
 * @return
 *     -真的
 *     -假的
 */
bool esp_http_client_is_complete_data_received(esp_http_client_handle_t client);

/**
 * @brief      用于读取较大数据块的助手API这是一个助手API，它在内部多次调用“esp_http_client_read”，直到到达数据结尾或缓冲区已满。
 *
 * @param[in]  client   esp_http_client句柄
 * @param      buffer   缓冲区
 * @param[in]  len      缓冲区长度
 *
 * @return
 *     -读取的数据长度
 */

int esp_http_client_read_response(esp_http_client_handle_t client, char *buffer, int len);

/**
 * @brief       处理所有剩余的响应数据这使用内部缓冲区重复接收、解析和丢弃响应数据，直到处理完完整的数据。由于不需要额外的用户提供的缓冲区，因此在可能忽略响应内容的情况下，这可能优于“esp_http_client_read_response”。
 *
 * @param[in]  client  esp_http_client句柄
 * @param      len     丢弃的数据长度
 *
 * @return
 *     -ESP_OK如果成功，len将丢弃长度
 *     -ESP_FAIL如果读取响应失败
 *     -ESP_ERR_INVALID_ARG如果客户端为空
 */
esp_err_t esp_http_client_flush_response(esp_http_client_handle_t client, int *len);

/**
 * @brief          从客户端获取URL
 *
 * @param[in]      client   esp_http_client句柄
 * @param[inout]   url      用于存储URL的缓冲区
 * @param[in]      len      缓冲区长度
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */

esp_err_t esp_http_client_get_url(esp_http_client_handle_t client, char *url, const int len);

/**
 * @brief          从客户端获取区块长度
 *
 * @param[in]      client   esp_http_client句柄
 * @param[out]     len      存储长度的变量
 *
 * @return
 *     -ESP_OK如果成功，len将具有当前块的长度
 *     -ESP_FAIL如果服务器不是分块服务器
 *     -ESP_ERR_INVALID_ARG如果客户端或len为空
 */
esp_err_t esp_http_client_get_chunk_length(esp_http_client_handle_t client, int *len);

#ifdef __cplusplus
}
#endif


#endif

