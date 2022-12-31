/*
 * 此文件受文件“LICENSE”中定义的条款和条件约束，该文件是源代码包的一部分。Tuan PM＜Tuan PM at live dot com＞
 */

#ifndef _ESP_TRANSPORT_WS_H_
#define _ESP_TRANSPORT_WS_H_

#include "esp_transport.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ws_transport_opcodes {
    WS_TRANSPORT_OPCODES_CONT =  0x00,
    WS_TRANSPORT_OPCODES_TEXT =  0x01,
    WS_TRANSPORT_OPCODES_BINARY = 0x02,
    WS_TRANSPORT_OPCODES_CLOSE = 0x08,
    WS_TRANSPORT_OPCODES_PING = 0x09,
    WS_TRANSPORT_OPCODES_PONG = 0x0a,
    WS_TRANSPORT_OPCODES_FIN = 0x80,
    WS_TRANSPORT_OPCODES_NONE = 0x100,   /*!< 不是一个有效的操作码，表示以前没有从API esp_transport_ws_get_read_opcode（）接收到消息*/
} ws_transport_opcodes_t;

/**
 * WS传输配置结构
 */
typedef struct {
    const char *ws_path;                    /*!< 将协议更新到websocket的HTTP路径*/
    const char *sub_protocol;               /*!< WS子协议*/
    const char *user_agent;                 /*!< WS用户代理*/
    const char *headers;                    /*!< WS附加标头*/
    bool        propagate_control_frames;   /*!< 如果为true，则将控制帧传递给读取器如果为false，则仅传播用户帧，在读取操作期间自动处理控制帧
                                             */
} esp_transport_ws_config_t;

/**
 * @brief      创建web套接字传输
 *
 * @return
 *  -运输
 *  - NULL
 */
esp_transport_handle_t esp_transport_ws_init(esp_transport_handle_t parent_handle);

/**
 * @brief       设置HTTP路径以更新websocket的协议
 *
 * @param t     websocket传输句柄
 * @param path  HTTP路径
 */
void esp_transport_ws_set_path(esp_transport_handle_t t, const char *path);

/**
 * @brief               设置websocket子协议头
 *
 * @param t             websocket传输句柄
 * @param sub_protocol  子协议字符串
 *
 * @return
 *      -成功时ESP_OK
 *      -错误代码之一
 */
esp_err_t esp_transport_ws_set_subprotocol(esp_transport_handle_t t, const char *sub_protocol);

/**
 * @brief               设置websocket用户代理标头
 *
 * @param t             websocket传输句柄
 * @param sub_protocol  用户代理字符串
 *
 * @return
 *      -成功时ESP_OK
 *      -错误代码之一
 */
esp_err_t esp_transport_ws_set_user_agent(esp_transport_handle_t t, const char *user_agent);

/**
 * @brief               设置websocket附加标头
 *
 * @param t             websocket传输句柄
 * @param sub_protocol  附加标头字符串，每个字符串都以\r\n
 *
 * @return
 *      -成功时ESP_OK
 *      -错误代码之一
 */
esp_err_t esp_transport_ws_set_headers(esp_transport_handle_t t, const char *headers);

/**
 * @brief               设置websocket传输参数
 *
 * @param t             websocket传输句柄
 * @param config        指向websocket配置结构的指针
 *
 * @return
 *      -成功时ESP_OK
 *      -错误代码之一
 */
esp_err_t esp_transport_ws_set_config(esp_transport_handle_t t, const esp_transport_ws_config_t *config);

/**
 * @brief               发送带有自定义操作码和负载的websocket原始消息
 *
 * 请注意，如果大小大于0，wshandle的通用esp_transport_write将默认发送二进制消息，如果消息大小设置为0，则发送ping消息。如果是带有任意数据的ping、PONG或TEXT消息，则提供此API以支持带有任意操作码的显式消息。
 *
 * @param[in]  t           Websocket传输句柄
 * @param[in]  opcode      ws操作代码
 * @param[in]  buffer      缓冲区
 * @param[in]  len         长度
 * @param[in]  timeout_ms  超时毫秒（-1表示永远阻塞）
 *
 * @return
 *  -写入的字节数
 *  -（-1）如果有任何错误，应检查errno
 */
int esp_transport_ws_send_raw(esp_transport_handle_t t, ws_transport_opcodes_t opcode, const char *b, int len, int timeout_ms);

/**
 * @brief               返回上次接收数据的websocket操作代码
 *
 * @param t             websocket传输句柄
 *
 * @return
 *      -接收到作为枚举的操作代码
 */
ws_transport_opcodes_t esp_transport_ws_get_read_opcode(esp_transport_handle_t t);

/**
 * @brief               返回上次接收数据的有效负载长度
 *
 * @param t             websocket传输句柄
 *
 * @return
 *      -有效负载中的字节数
 */
int esp_transport_ws_get_read_payload_len(esp_transport_handle_t t);

/**
 * @brief               轮询活动连接以终止
 *
 * 客户端通常使用此API来等待websocket服务器关闭干净的连接
 *
 * @param t             Websocket传输句柄
 * @param[in] timeout_ms 超时毫秒
 *
 * @return 0-在超时1内没有读取和错误套接字描述符的活动-成功：连接被FIN或最常见的RST错误代码终止
 *      -1-失败：意外错误代码或套接字通常可读
 */
int esp_transport_ws_poll_connection_closed(esp_transport_handle_t t, int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_TRANSPORT_WS_H_ */

