// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ESP_WEBSOCKET_CLIENT_H_
#define _ESP_WEBSOCKET_CLIENT_H_


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "esp_event.h"
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_websocket_client *esp_websocket_client_handle_t;

ESP_EVENT_DECLARE_BASE(WEBSOCKET_EVENTS);         // 任务事件系列的声明

/**
 * @brief Websocket客户端事件id
 */
typedef enum {
    WEBSOCKET_EVENT_ANY = -1,
    WEBSOCKET_EVENT_ERROR = 0,      /*!< 当执行过程中出现任何错误时，会发生此事件*/
    WEBSOCKET_EVENT_CONNECTED,      /*!< 一旦Websocket连接到服务器，就不会执行任何数据交换*/
    WEBSOCKET_EVENT_DISCONNECTED,   /*!< 连接已断开*/
    WEBSOCKET_EVENT_DATA,           /*!< 从服务器接收数据时，可能是数据包的多个部分*/
    WEBSOCKET_EVENT_CLOSED,         /*!< 连接已完全关闭*/
    WEBSOCKET_EVENT_MAX
} esp_websocket_event_id_t;

/**
 * @brief Websocket事件数据
 */
typedef struct {
    const char *data_ptr;                   /*!< 数据指针*/
    int data_len;                           /*!< 数据长度*/
    uint8_t op_code;                        /*!< 收到的操作码*/
    esp_websocket_client_handle_t client;   /*!< esp_websocket_client_handle_t上下文*/
    void *user_context;                     /*!< 用户数据上下文，来自esp_websocket_client_config_t用户数据*/
    int payload_len;                        /*!< 总有效载荷长度，超过缓冲区的有效载荷将通过多个事件发布*/
    int payload_offset;                     /*!< 与此事件关联的数据的实际偏移量*/
} esp_websocket_event_data_t;

/**
 * @brief Websocket客户端传输
 */
typedef enum {
    WEBSOCKET_TRANSPORT_UNKNOWN = 0x0,  /*!< 传输未知*/
    WEBSOCKET_TRANSPORT_OVER_TCP,       /*!< tcp传输*/
    WEBSOCKET_TRANSPORT_OVER_SSL,       /*!< 通过ssl传输*/
} esp_websocket_transport_t;

/**
 * @brief Websocket客户端安装配置
 */
typedef struct {
    const char                  *uri;                       /*!< Websocket URI，URI上的信息可以覆盖下面的其他字段（如果有的话）*/
    const char                  *host;                      /*!< 域或IP作为字符串*/
    int                         port;                       /*!< 要连接的端口，默认取决于esp_websocket_transport_t（80或443）*/
    const char                  *username;                  /*!< 用于Http身份验证-目前不支持*/
    const char                  *password;                  /*!< 用于Http身份验证-目前不支持*/
    const char                  *path;                      /*!< HTTP路径，如果未设置，则默认为“/”*/
    bool                        disable_auto_reconnect;     /*!< 断开连接时禁用自动重新连接功能*/
    void                        *user_context;              /*!< HTTP用户数据上下文*/
    int                         task_prio;                  /*!< Websocket任务优先级*/
    int                         task_stack;                 /*!< Websocket任务堆栈*/
    int                         buffer_size;                /*!< Websocket缓冲区大小*/
    const char                  *cert_pem;                  /*!< 指向PEM或DER格式的证书数据的指针，用于服务器验证（使用SSL），默认值为NULL，不需要验证服务器。PEM格式必须具有终止NULL字符。DER格式要求在cert_len中传递长度。*/
    size_t                      cert_len;                   /*!< cert_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char                  *client_cert;               /*!< 指向用于SSL相互认证的PEM或DER格式的证书数据的指针，默认值为NULL，如果不需要相互认证，则不需要。如果不为NULL，还必须提供“client_key”。PEM格式必须具有终止NULL字符。DER格式要求在client_cert_len中传递长度。*/
    size_t                      client_cert_len;            /*!< client_cert指向的缓冲区长度。对于空终止的pem，可以为0*/
    const char                  *client_key;                /*!< 指向PEM或DER格式的私钥数据的指针，用于SSL相互认证，默认值为NULL，如果不需要相互认证，则不需要。如果不为NULL，还必须提供“client_cert”。PEM格式必须具有终止NULL字符。DER格式要求在client_key_len中传递长度*/
    size_t                      client_key_len;             /*!< client_key_pem指向的缓冲区长度。对于空终止的pem，可以为0*/
    esp_websocket_transport_t   transport;                  /*!< Websocket传输类型，请参见`esp_Websocket_transport_t*/
    const char                  *subprotocol;               /*!< Websocket子协议*/
    const char                  *user_agent;                /*!< Websocket用户代理*/
    const char                  *headers;                   /*!< Websocket附加标头*/
    int                         pingpong_timeout_sec;       /*!< 由于未接收到PONG而中止连接之前的时间段*/
    bool                        disable_pingpong_discon;    /*!< 由于pingpong_timeout_sec内未接收到PONG，因此禁用自动断开连接*/
    bool                        use_global_ca_store;        /*!< 为设置此布尔值的所有连接使用全局ca_store。*/
    bool                        skip_cert_common_name_check;/*!< 跳过服务器证书CN字段的任何验证*/
    bool                        keep_alive_enable;          /*!< 启用保持活动超时*/
    int                         keep_alive_idle;            /*!< 保持活动空闲时间。默认值为5（秒）*/
    int                         keep_alive_interval;        /*!< 保活间隔时间。默认值为5（秒）*/
    int                         keep_alive_count;           /*!< 保活数据包重试发送计数。默认值为3个计数*/
    size_t                      ping_interval_sec;          /*!< 网络套接字ping间隔，如果未设置，则默认为10秒*/
    struct ifreq                *if_name;                   /*!< 数据要通过的接口的名称。使用默认界面而不设置*/
} esp_websocket_client_config_t;

/**
 * @brief      启动Websocket会话此函数必须是要调用的第一个函数，并且它返回esp_Websocket_client_handle_t，您必须将其用作接口中其他函数的输入。当操作完成时，此调用必须具有对esp_websocket_client_delete的相应调用。
 *
 * @param[in]  config  配置
 *
 * @return
 *     -`esp_websocket_client_handle_t`
 *     -如果有错误，则为NULL
 */
esp_websocket_client_handle_t esp_websocket_client_init(const esp_websocket_client_config_t *config);

/**
 * @brief      为客户端设置URL，当执行此行为时，URL中的选项将替换旧选项。如果客户端已连接，则必须在设置URI之前停止WebSocket客户端
 *
 * @param[in]  client  客户
 * @param[in]  uri     uri
 *
 * @return     电子邮箱地址
 */
esp_err_t esp_websocket_client_set_uri(esp_websocket_client_handle_t client, const char *uri);

/**
 * @brief      打开WebSocket连接
 *
 * @param[in]  client  客户
 *
 * @return     电子邮箱地址
 */
esp_err_t esp_websocket_client_start(esp_websocket_client_handle_t client);

/**
 * @brief      在没有WebSocket关闭握手的情况下停止WebSocket连接
 *
 * 此API停止ws客户端并直接关闭TCP连接，而不发送关闭帧。最好使用esp_websocket_client_close（）以干净的方式关闭连接。
 *
 *  笔记：
 *  -无法从websocket事件处理程序调用
 *
 * @param[in]  client  客户
 *
 * @return     电子邮箱地址
 */
esp_err_t esp_websocket_client_stop(esp_websocket_client_handle_t client);

/**
 * @brief      销毁WebSocket连接并释放所有资源。此函数必须是调用会话的最后一个函数。它与esp_websocket_client_init函数相反，必须使用与esp_wwebsocket_client/init调用返回的输入相同的句柄来调用。这可能会关闭此句柄使用的所有连接。
 *
 *  笔记：
 *  -无法从websocket事件处理程序调用
 *
 * @param[in]  client  客户
 *
 * @return     电子邮箱地址
 */
esp_err_t esp_websocket_client_destroy(esp_websocket_client_handle_t client);

/**
 * @brief      向WebSocket连接写入通用数据；默认为二进制发送
 *
 * @param[in]  client  客户
 * @param[in]  data    数据
 * @param[in]  len     长度
 * @param[in]  timeout 写入数据超时（以RTOS为单位）
 *
 * @return
 *     -发送的数据数
 *     -（-1）如果有错误
 */
int esp_websocket_client_send(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      将二进制数据写入WebSocket连接（数据发送时WS OPCODE=02，即二进制）
 *
 * @param[in]  client  客户
 * @param[in]  data    数据
 * @param[in]  len     长度
 * @param[in]  timeout 写入数据超时（以RTOS为单位）
 *
 * @return
 *     -发送的数据数
 *     -（-1）如果有错误
 */
int esp_websocket_client_send_bin(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      将文本数据写入WebSocket连接（数据发送时WS OPCODE=01，即文本）
 *
 * @param[in]  client  客户
 * @param[in]  data    数据
 * @param[in]  len     长度
 * @param[in]  timeout 写入数据超时（以RTOS为单位）
 *
 * @return
 *     -发送的数据数
 *     -（-1）如果有错误
 */
int esp_websocket_client_send_text(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      以干净的方式关闭WebSocket连接
 *
 * 客户端启动的清理关闭序列：客户端发送close帧客户端等待直到服务器回显close帧客户等待直到服务器关闭连接客户端停止的方式与`esp_websocket_client_stop（）相同`
 *
 *  笔记：
 *  -无法从websocket事件处理程序调用
 *
 * @param[in]  client  客户
 * @param[in]  timeout 等待的RTOS计时超时
 *
 * @return     电子邮箱地址
 */
esp_err_t esp_websocket_client_close(esp_websocket_client_handle_t client, TickType_t timeout);

/**
 * @brief      使用自定义代码/数据以干净的方式关闭WebSocket连接。关闭顺序与esp_WebSocket_client_Close（）相同
 *
 *  笔记：
 *  -无法从websocket事件处理程序调用
 *
 * @param[in]  client  客户
 * @param[in]  code    关闭RFC6455第7.4节中定义的状态代码
 * @param[in]  data    结束消息的附加数据
 * @param[in]  len     附加数据的长度
 * @param[in]  timeout 等待的RTOS计时超时
 *
 * @return     电子邮箱地址
 */
esp_err_t esp_websocket_client_close_with_code(esp_websocket_client_handle_t client, int code, const char *data, int len, TickType_t timeout);

/**
 * @brief      检查WebSocket客户端连接状态
 *
 * @param[in]  client  客户端句柄
 *
 * @return
 *     -真的
 *     -假的
 */
bool esp_websocket_client_is_connected(esp_websocket_client_handle_t client);

/**
 * @brief 注册Websocket事件
 *
 * @param client            客户端句柄
 * @param event             事件id
 * @param event_handler     回调函数
 * @param event_handler_arg 用户上下文
 * @return 电子邮箱地址
 */
esp_err_t esp_websocket_register_events(esp_websocket_client_handle_t client,
                                        esp_websocket_event_id_t event,
                                        esp_event_handler_t event_handler,
                                        void *event_handler_arg);

#ifdef __cplusplus
}
#endif

#endif

