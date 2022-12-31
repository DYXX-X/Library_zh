// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#ifndef _ESP_TRANSPORT_INTERNAL_H_
#define _ESP_TRANSPORT_INTERNAL_H_

#include "esp_transport.h"
#include "sys/queue.h"

typedef int (*get_socket_func)(esp_transport_handle_t t);

typedef struct esp_foundation_transport {
    struct esp_transport_error_storage  *error_handle;           /*!< 指向传输错误容器的指针*/
    struct transport_esp_tls            *transport_esp_tls;      /*!< 指向使用esp-tls的基本传输的指针*/
} esp_foundation_transport_t;

/**
 * 传输层结构，将为传输类型提供功能和基本属性
 */
struct esp_transport_item_t {
    int             port;
    char            *scheme;        /*!< 标记名称*/
    void            *data;          /*!< 其他运输数据*/
    connect_func    _connect;       /*!< 此通道的连接功能*/
    io_read_func    _read;          /*!< 阅读*/
    io_func         _write;         /*!< 写*/
    trans_func      _close;         /*!< 关*/
    poll_func       _poll_read;     /*!< 投票并阅读*/
    poll_func       _poll_write;    /*!< 轮询并写入*/
    trans_func      _destroy;       /*!< 销毁和免费运输*/
    connect_async_func _connect_async;      /*!< 此传输的非阻塞连接功能*/
    payload_transfer_func  _parent_transfer;        /*!< 返回底层传输层的函数*/
    get_socket_func        _get_socket;             /*!< 返回传输套接字的函数*/
    esp_transport_keep_alive_t *keep_alive_cfg;     /*!< TCP保持活动配置*/
    struct esp_foundation_transport *base;          /*!< 每个传输中可用的基础传输指针*/

    STAILQ_ENTRY(esp_transport_item_t) next;
};

/**
 * @brief 套接字错误号中未包含TCP连接问题的内部错误类型
 */
enum tcp_transport_errors {
    ERR_TCP_TRANSPORT_CONNECTION_TIMEOUT,
    ERR_TCP_TRANSPORT_CANNOT_RESOLVE_HOSTNAME,
    ERR_TCP_TRANSPORT_CONNECTION_CLOSED_BY_FIN,
    ERR_TCP_TRANSPORT_CONNECTION_FAILED,
    ERR_TCP_TRANSPORT_SETOPT_FAILED,
    ERR_TCP_TRANSPORT_NO_MEM,
};

/**
 * @brief      捕获内部tcp连接错误
 *
 * 这在内部被转换为esp_err_t类型的esp-tls返回代码，因为esp-tls将用作TCP传输层
 *
 * @param[in] t 运输手柄
 * @param[in] error 内部tcp传输错误
 *
 */
void capture_tcp_transport_error(esp_transport_handle_t t, enum tcp_transport_errors error);

/**
 * @brief 返回提供的传输句柄的基础套接字
 *
 * @param t 运输手柄
 *
 * @return 成功时的套接字文件描述符
 *         -错误时为1
 */
int esp_transport_get_socket(esp_transport_handle_t t);

/**
 * @brief      捕获当前错误号
 *
 * @param[in] t 运输手柄
 * @param[in] sock_errno 要存储在内部传输结构中的套接字errno
 *
 */
void esp_transport_capture_errno(esp_transport_handle_t t, int sock_errno);

/**
 * @brief      创建基础传输中使用的esp-tls传输
 *
 * @return     运输esp tls手柄
 */
struct transport_esp_tls* esp_transport_esp_tls_create(void);

/**
 * @brief      破坏基础运输中使用的esp-tls运输
 *
 * @param[in]  transport esp tls手柄
 */
void esp_transport_esp_tls_destroy(struct transport_esp_tls* transport_esp_tls);

/**
 * @brief      将错误设置为公共传输句柄
 *
 *             注意：此函数将提供的错误句柄对象复制到tcp_transport的内部错误句柄对象
 *
 * @param[in]  A 运输手柄
 *
 */
void esp_transport_set_errors(esp_transport_handle_t t, const esp_tls_error_handle_t error_handle);

#endif //_ESP_TRANSPORT_INTERNAL_H_

