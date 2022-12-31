/*
 * 此文件受文件“LICENSE”中定义的条款和条件约束，该文件是源代码包的一部分。Tuan PM＜Tuan PM at live dot com＞
 */

#ifndef _MQTT_CLIENT_H_
#define _MQTT_CLIENT_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "esp_err.h"
#include "esp_event.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ESP_EVENT_DECLARE_BASE
// 如果宏不可用，则定义事件循环类型
typedef void *esp_event_loop_handle_t;
typedef void *esp_event_handler_t;
#endif

typedef struct esp_mqtt_client *esp_mqtt_client_handle_t;

/**
 * @brief MQTT事件类型。
 *
 * 用户事件处理程序接收“esp_mqtt_event_t”结构中的上下文数据
 *  -`user_context`-来自`esp_mqtt_client_config_t的用户数据`
 *  -`client`-mqtt客户端句柄
 *  -取决于事件类型的各种其他数据
 *
 */
typedef enum {
    MQTT_EVENT_ANY = -1,
    MQTT_EVENT_ERROR = 0,          /*!< 发生错误事件时，附加上下文：连接返回代码，esp_tls中的错误句柄（如果支持）*/
    MQTT_EVENT_CONNECTED,          /*!< 已连接事件，附加上下文：sessionpresent标志*/
    MQTT_EVENT_DISCONNECTED,       /*!< 断开连接的事件*/
    MQTT_EVENT_SUBSCRIBED,         /*!< 订阅事件，附加上下文：msg_id*/
    MQTT_EVENT_UNSUBSCRIBED,       /*!< 未订阅事件*/
    MQTT_EVENT_PUBLISHED,          /*!< 已发布事件，附加上下文：msg_id*/
    MQTT_EVENT_DATA,               /*!< 数据事件，附加上下文：
                                        -消息id消息id
                                        -指向所接收主题的主题指针
                                        -topic_len主题长度
                                        -指向接收数据的数据指针
                                        -此事件数据的data_len长度
                                        -此事件的当前数据的current_data_offset偏移
                                        -total_data_len接收数据的总长度
                                        -消息的retain retain标志注意：如果一条消息比内部缓冲区长，则可以为该消息激发多个MQTT_EVENT_DATA。在这种情况下，只有第一个事件包含主题指针和长度，其他事件仅包含当前数据长度和当前数据偏移量更新的数据。
                                         */
    MQTT_EVENT_BEFORE_CONNECT,     /*!< 事件发生在连接之前*/
    MQTT_EVENT_DELETED,            /*!< 如果邮件在outbox_EXPIRED_TIMEOUT_MS中定义的过期之前无法发送和确认，则从内部发件箱中删除一条邮件的通知。（删除成功确认的消息后不会发布事件）
                                        -仅当MQTT_REREPORT_DELETED_MESSAGES==1时才发布此事件id
                                        -附加上下文：msg_id（已删除邮件的id）。
                                        */
} esp_mqtt_event_id_t;

/**
 * 通过error事件传播的MQTT连接错误代码
 */
typedef enum {
    MQTT_CONNECTION_ACCEPTED = 0,                   /*!< 已接受连接*/
    MQTT_CONNECTION_REFUSE_PROTOCOL,                /*!< MQTT连接被拒绝原因：协议错误*/
    MQTT_CONNECTION_REFUSE_ID_REJECTED,             /*!< MQTT连接被拒绝原因：ID被拒绝*/
    MQTT_CONNECTION_REFUSE_SERVER_UNAVAILABLE,      /*!< MQTT连接被拒绝原因：服务器不可用*/
    MQTT_CONNECTION_REFUSE_BAD_USERNAME,            /*!< MQTT连接被拒绝原因：用户错误*/
    MQTT_CONNECTION_REFUSE_NOT_AUTHORIZED           /*!< MQTT连接被拒绝原因：用户名或密码错误*/
} esp_mqtt_connect_return_code_t;

/**
 * 通过error事件传播的MQTT连接错误代码
 */
typedef enum {
    MQTT_ERROR_TYPE_NONE = 0,
    MQTT_ERROR_TYPE_TCP_TRANSPORT,
    MQTT_ERROR_TYPE_CONNECTION_REFUSED,
} esp_mqtt_error_type_t;

/**
 * MQTT_ERROR_TYPE_TCP_TTRANSPORT错误类型保存所有类型的传输层错误，包括ESP-TLS错误，但过去只报告了MQTT_EERROR_TYPE_ESP_TLS层的错误，因此为了向后兼容，这里重新定义了ESP-TLS错误类型
 */
#define MQTT_ERROR_TYPE_ESP_TLS MQTT_ERROR_TYPE_TCP_TRANSPORT

typedef enum {
    MQTT_TRANSPORT_UNKNOWN = 0x0,
    MQTT_TRANSPORT_OVER_TCP,      /*!< MQTT over TCP，使用方案：``MQTT``*/
    MQTT_TRANSPORT_OVER_SSL,      /*!< SSL上的MQTT，使用方案：``mqtts``*/
    MQTT_TRANSPORT_OVER_WS,       /*!< Websocket上的MQTT，使用方案：：`ws``*/
    MQTT_TRANSPORT_OVER_WSS       /*!< Websocket上的MQTT安全，使用方案：`wss``*/
} esp_mqtt_transport_t;

/**
 *  用于连接的MQTT协议版本
 */
typedef enum {
    MQTT_PROTOCOL_UNDEFINED = 0,
    MQTT_PROTOCOL_V_3_1,
    MQTT_PROTOCOL_V_3_1_1
} esp_mqtt_protocol_ver_t;

/**
 * @brief 要作为上下文信息传递到error事件中的MQTT错误代码结构
 *
 * 重要提示：此结构扩展了“esp_tls_last_error”错误结构，并与之向后兼容（因此可能会向下广播并被视为“esp_tls _last_eError”错误，但建议在以前使用此方法时更新应用程序）
 *
 * 首先使用此结构直接检查error_type，然后根据错误源检查相应的错误代码：
 *
 * |error_type |相关成员变量|注释||MQTT_error_type_TCP_TRANPORT|esp_tls_last_esp_err、esp_tls_stack_err、esp_tls _cert_verify_flags、sock_errno | TCP_TRANSPORT/esp tls报告的错误||MQT_error_type_CONNECTION_REFUSED|connect_return_code |连接上MQTT代理报告的内部错误|
 */
typedef struct esp_mqtt_error_codes {
    /* 与结构esp_tls_last_error对应的结构的兼容部分*/
    esp_err_t esp_tls_last_esp_err;              /*!< esp-tls组件报告的最后一个esp_err代码*/
    int       esp_tls_stack_err;                 /*!< 从基础tls堆栈报告的tls特定错误代码*/
    int       esp_tls_cert_verify_flags;         /*!< 证书验证期间从基础tls堆栈报告的tls标志*/
    /* esp mqtt特定结构扩展*/
    esp_mqtt_error_type_t error_type;            /*!< 指错误源的错误类型*/
    esp_mqtt_connect_return_code_t connect_return_code; /*!< 连接上MQTT代理报告的连接拒绝错误代码*/
    /* tcp_传输扩展*/
    int       esp_transport_sock_errno;         /*!< 来自基础套接字的errno*/

} esp_mqtt_error_codes_t;

/**
 * MQTT事件配置结构
 */
typedef struct {
    esp_mqtt_event_id_t event_id;       /*!< MQTT事件类型*/
    esp_mqtt_client_handle_t client;    /*!< 此事件的MQTT客户端句柄*/
    void *user_context;                 /*!< 从MQTT客户端配置传递的用户上下文*/
    char *data;                         /*!< 与此事件关联的数据*/
    int data_len;                       /*!< 此事件的数据长度*/
    int total_data_len;                 /*!< 数据的总长度（随多个事件提供的数据越长）*/
    int current_data_offset;            /*!< 与此事件关联的数据的实际偏移量*/
    char *topic;                        /*!< 与此事件相关的主题*/
    int topic_len;                      /*!< 与此事件关联的此事件的主题长度*/
    int msg_id;                         /*!< MQTT消息的消息id*/
    int session_present;                /*!< 连接事件的MQTT会话呈现标志*/
    esp_mqtt_error_codes_t *error_handle; /*!< esp mqtt错误处理，包括esp tls错误以及内部mqtt错误*/
    bool retain;                        /*!< 与此事件关联的消息的保留标志*/
} esp_mqtt_event_t;

typedef esp_mqtt_event_t *esp_mqtt_event_handle_t;

typedef esp_err_t (* mqtt_event_callback_t)(esp_mqtt_event_handle_t event);

/**
 * MQTT客户机配置结构
 */
typedef struct {
    mqtt_event_callback_t event_handle;     /*!< 将MQTT事件处理为传统模式中的回调*/
    esp_event_loop_handle_t event_loop_handle; /*!< MQTT事件循环库的句柄*/
    const char *host;                       /*!< MQTT服务器域（ipv4作为字符串）*/
    const char *uri;                        /*!< 完整的MQTT代理URI*/
    uint32_t port;                          /*!< MQTT服务器端口*/
    const char *client_id;                  /*!< 默认客户端id为``ESP32_%CHIPID%``，其中%CHIPID%是十六进制格式的MAC地址的最后3个字节*/
    const char *username;                   /*!< MQTT用户名*/
    const char *password;                   /*!< MQTT密码*/
    const char *lwt_topic;                  /*!< LWT（遗愿和遗嘱）消息主题（默认为NULL）*/
    const char *lwt_msg;                    /*!< LWT消息（默认为NULL）*/
    int lwt_qos;                            /*!< LWT消息qos*/
    int lwt_retain;                         /*!< LWT保留消息标志*/
    int lwt_msg_len;                        /*!< LWT消息长度*/
    int disable_clean_session;              /*!< mqtt clean会话，默认clean_session为true*/
    int keepalive;                          /*!< mqtt keepalive，默认值为120秒*/
    bool disable_auto_reconnect;            /*!< 这个mqtt客户端将重新连接到服务器（当出现错误/断开连接时）。将disable_auto_reconnect=true设置为禁用*/
    void *user_context;                     /*!< 将用户上下文传递给此选项，然后可以在`event->user_context``中接收该上下文*/
    int task_prio;                          /*!< MQTT任务优先级，默认值为5，可以在`makemenuconfig``中更改*/
    int task_stack;                         /*!< MQTT任务堆栈大小，默认为6144字节，可以在`makemenuconfig``中更改*/
    int buffer_size;                        /*!< MQTT发送/接收缓冲区的大小，默认值为1024（如果定义了“out_buffer_size”，则仅接收缓冲区大小）*/
    const char *cert_pem;                   /*!< 指向PEM或DER格式的证书数据的指针，用于服务器验证（使用SSL），默认值为NULL，不需要验证服务器。PEM格式必须具有终止NULL字符。DER格式要求在cert_len中传递长度。*/
    size_t cert_len;                        /*!< cert_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char *client_cert_pem;            /*!< 指向用于SSL相互认证的PEM或DER格式的证书数据的指针，默认值为NULL，如果不需要相互认证，则不需要。如果不为NULL，还必须提供“client_key_pem”。PEM格式必须具有终止NULL字符。DER格式要求在client_cert_len中传递长度。*/
    size_t client_cert_len;                 /*!< client_cert_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char *client_key_pem;             /*!< 指向PEM或DER格式的私钥数据的指针，用于SSL相互认证，默认值为NULL，如果不需要相互认证，则不需要。如果不为NULL，还必须提供“client_cert_pem”。PEM格式必须具有终止NULL字符。DER格式要求在client_key_len中传递长度*/
    size_t client_key_len;                  /*!< client_key_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    esp_mqtt_transport_t transport;         /*!< 重写URI传输*/
    int refresh_connection_after_ms;        /*!< 在此值之后刷新连接（以毫秒为单位）*/
    const struct psk_key_hint *psk_hint_key;     /*!< 指向esp_tls中定义的PSK结构的指针。h以启用PSK认证（作为证书验证的替代）。如果不为NULL且服务器/客户端证书为NULL，则启用PSK*/
    bool          use_global_ca_store;      /*!< 为设置此布尔值的所有连接使用全局ca_store。*/
    esp_err_t (*crt_bundle_attach)(void *conf); /*!< 指向用于在mqtts中使用证书捆绑包的ESP x509证书捆绑包附加函数的指针*/
    int reconnect_timeout_ms;               /*!< 如果未禁用自动重新连接（默认为10秒），则在此值之后重新连接到代理（毫秒）*/
    const char **alpn_protos;               /*!< 用于ALPN的受支持应用程序协议的NULL终止列表*/
    const char *clientkey_password;         /*!< 客户端密钥解密密码字符串*/
    int clientkey_password_len;             /*!< clientkey_password指向的密码的字符串长度*/
    esp_mqtt_protocol_ver_t protocol_ver;   /*!< 用于连接的MQTT协议版本，默认为menuconfig中的值*/
    int out_buffer_size;                    /*!< MQTT输出缓冲区的大小。如果未定义，则输出和输入缓冲区的大小都定义为“buffer_size”*/
    bool skip_cert_common_name_check;       /*!< 跳过服务器证书CN字段的任何验证，这会降低TLS的安全性，并使mqtt客户端容易受到MITM攻击*/
    bool use_secure_element;                /*!< 启用安全元素以启用SSL连接*/
    void *ds_data;                          /*!< 数字签名参数句柄的载体*/
    int network_timeout_ms;                 /*!< 如果在该值之后未完成网络操作，则中止网络操作，以毫秒为单位（默认为10秒）*/
    bool disable_keepalive;                 /*!< 设置disable_keepalive=true以关闭keepalive机制，默认情况下为false（默认情况下keepalive处于活动状态）。注意：将配置值“keepalive”设置为“0”不会禁用keepalive功能，而是使用默认的keepalive周期*/
    const char *path;                       /*!< URI中的路径*/
    int message_retransmit_timeout;         /*!< 重新发送失败数据包超时*/
} esp_mqtt_client_config_t;

/**
 * @brief 基于配置创建mqtt客户端句柄
 *
 * @param config    mqtt配置结构
 *
 * @return mqtt_client_handle（如果成功创建），出错时为NULL
 */
esp_mqtt_client_handle_t esp_mqtt_client_init(const esp_mqtt_client_config_t *config);

/**
 * @brief 设置mqtt连接URI。此API通常用于重写esp_mqtt_client_init中配置的URI
 *
 * @param client    mqtt客户端句柄
 * @param uri
 *
 * @return 如果URI解析错误，则返回ESP_FAIL，成功时返回ESP_OK
 */
esp_err_t esp_mqtt_client_set_uri(esp_mqtt_client_handle_t client, const char *uri);

/**
 * @brief 使用已创建的客户端句柄启动mqtt客户端
 *
 * @param client    mqtt客户端句柄
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG错误初始化时ESP_FAIL其他错误
 */
esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client);

/**
 * @brief 此api通常用于在特定事件时强制重新连接
 *
 * @param client    mqtt客户端句柄
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG错误初始化ESP_FAIL（如果客户端处于无效状态）
 */
esp_err_t esp_mqtt_client_reconnect(esp_mqtt_client_handle_t client);

/**
 * @brief 此api通常用于强制断开与代理的连接
 *
 * @param client    mqtt客户端句柄
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG初始化错误
 */
esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client);

/**
 * @brief 停止mqtt客户端任务
 *
 *  *注释：
 *  -无法从mqtt事件处理程序调用
 *
 * @param client    mqtt客户端句柄
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG错误初始化ESP_FAIL（如果客户端处于无效状态）
 */
esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client);

/**
 * @brief 向客户端订阅具有定义的qos的定义主题
 *
 * 笔记：
 * -必须连接客户端才能发送订阅消息
 * -该API可以从用户任务或mqtt事件回调执行，即内部mqtt任务（API受内部互斥锁保护，因此如果正在进行较长的数据接收操作，它可能会阻塞。
 *
 * @param client    mqtt客户端句柄
 * @param topic
 * @param qos
 *
 * @return 成功时订阅消息的message_id
 *         -1出现故障
 */
int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos);

/**
 * @brief 从定义的主题中取消订阅客户端
 *
 * 笔记：
 * -必须连接客户端才能发送取消订阅消息
 * -它是线程安全的，有关详细信息，请参阅“esp_mqtt_client_subscribe”
 *
 * @param client    mqtt客户端句柄
 * @param topic
 *
 * @return 成功时订阅消息的message_id
 *         -1出现故障
 */
int esp_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic);

/**
 * @brief 客户端向代理发送发布消息
 *
 * 笔记：
 * -由于网络超时（10秒）或发布的有效载荷比内部缓冲区长（由于消息碎片），此API可能会阻塞数秒
 * -客户端无需连接，此API即可工作，将qos>1的消息排入队列（如果断开连接，则所有qos=0的消息返回-1）。如果MQTT_SKIP_PUBLISH_If_DISCONNECTED已启用，则当客户端未连接时，此API将不会尝试发布，并且始终返回-1。
 * -它是线程安全的，有关详细信息，请参阅“esp_mqtt_client_subscribe”
 *
 * @param client    mqtt客户端句柄
 * @param topic     主题字符串
 * @param data      有效负载字符串（设置为NULL，发送空有效负载消息）
 * @param len       数据长度，如果设置为0，则根据有效负载字符串计算长度
 * @param qos       发布消息的qos
 * @param retain    保留标志
 *
 * @return 成功时发布消息的message_id（对于QoS 0，message_id将始终为零）。
 *         -失败时为1。
 */
int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain);

/**
 * @brief 将邮件排队到发件箱，以便稍后发送。通常用于qos>0的消息，但如果store=true，也可以用于qos=0的消息。
 *
 * 此API生成发布消息并将其存储到内部发件箱中，实际发送到网络是在mqtt任务上下文中执行的（与esp_mqtt_client_publish（）不同，后者在用户任务上下文中立即发送发布消息）。因此，它可以用作esp_mqtt_client_publish（）的非阻塞版本。
 *
 * @param client    mqtt客户端句柄
 * @param topic     主题字符串
 * @param data      有效负载字符串（设置为NULL，发送空有效负载消息）
 * @param len       数据长度，如果设置为0，则根据有效负载字符串计算长度
 * @param qos       发布消息的qos
 * @param retain    保留标志
 * @param store     如果为真，则所有消息都被排队；否则，只有qos1和qos 2被排队
 *
 * @return 如果成功排队，则为message_id，否则为-1
 */
int esp_mqtt_client_enqueue(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain, bool store);

/**
 * @brief 销毁客户端句柄
 *
 * 笔记：
 *  -无法从mqtt事件处理程序调用
 *
 * @param client    mqtt客户端句柄
 *
 * @return 初始化错误时ESP_OK ESP_ERR_INVALID_ARG
 */
esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client);

/**
 * @brief 设置配置结构，通常在更新配置时使用（即在“before_connect”事件上）
 *
 * @param client    mqtt客户端句柄
 *
 * @param config    mqtt配置结构
 *
 * @return 如果传输配置发生冲突，则无法分配ESP_ERR_INVALID_ARG，则为ESP_ERR_NO_MEM。成功时ESP_OK
 */
esp_err_t esp_mqtt_set_config(esp_mqtt_client_handle_t client, const esp_mqtt_client_config_t *config);

/**
 * @brief 注册mqtt事件
 *
 * @param client            mqtt客户端句柄
 * @param event             事件类型
 * @param event_handler     处理程序回调
 * @param event_handler_arg 处理程序上下文
 *
 * @return 如果在错误初始化时未能分配ESP_ERR_INVALID_ARG，则为ESP_ERR_NO_MEM，成功时为ESP_OK
 */
esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event, esp_event_handler_t event_handler, void *event_handler_arg);

/**
 * @brief 获取发件箱尺寸
 *
 * @param client            mqtt客户端句柄
 * @return 错误初始化时发件箱大小为0
 */
int esp_mqtt_client_get_outbox_size(esp_mqtt_client_handle_t client);

#ifdef __cplusplus
}
#endif //__cplusplus公司

#endif

