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

#ifndef _ESP_TRANSPORT_H_
#define _ESP_TRANSPORT_H_

#include <esp_err.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
*  @brief 保持活动参数结构
*/
typedef struct esp_transport_keepalive {
    bool            keep_alive_enable;      /*!< 启用保持活动超时*/
    int             keep_alive_idle;        /*!< 保持活动空闲时间（秒）*/
    int             keep_alive_interval;    /*!< 保活间隔时间（秒）*/
    int             keep_alive_count;       /*!< 保持活动数据包重试发送计数*/
} esp_transport_keep_alive_t;

typedef struct esp_transport_internal* esp_transport_list_handle_t;
typedef struct esp_transport_item_t* esp_transport_handle_t;

typedef int (*connect_func)(esp_transport_handle_t t, const char *host, int port, int timeout_ms);
typedef int (*io_func)(esp_transport_handle_t t, const char *buffer, int len, int timeout_ms);
typedef int (*io_read_func)(esp_transport_handle_t t, char *buffer, int len, int timeout_ms);
typedef int (*trans_func)(esp_transport_handle_t t);
typedef int (*poll_func)(esp_transport_handle_t t, int timeout_ms);
typedef int (*connect_async_func)(esp_transport_handle_t t, const char *host, int port, int timeout_ms);
typedef esp_transport_handle_t (*payload_transfer_func)(esp_transport_handle_t);

typedef struct esp_tls_last_error* esp_tls_error_handle_t;

/**
 * @brief      创建传输列表
 *
 * @return     手柄可容纳所有运输工具
 */
esp_transport_list_handle_t esp_transport_list_init(void);

/**
 * @brief      清理并释放所有传输，包括自身，此函数将调用每个传输的esp_transport_destroy。已将此添加到列表中
 *
 * @param[in]  list  列表
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_transport_list_destroy(esp_transport_list_handle_t list);

/**
 * @brief      向列表中添加传输，并定义一个方案以在列表中标识此传输
 *
 * @param[in]  list    列表
 * @param[in]  t       交通
 * @param[in]  scheme  该方案
 *
 * @return
 *     - ESP_OK
 */
esp_err_t esp_transport_list_add(esp_transport_list_handle_t list, esp_transport_handle_t t, const char *scheme);

/**
 * @brief      此函数将从列表中删除所有传输，调用每个传输的esp_transport_destroy
 *
 * @param[in]  list  列表
 *
 * @return
 *     - ESP_OK
 *     - ESP_ERR_INVALID_ARG
 */
esp_err_t esp_transport_list_clean(esp_transport_list_handle_t list);

/**
 * @brief      获取在调用函数`esp_transport_list_add时定义的按方案传输`
 *
 * @param[in]  list  列表
 * @param[in]  tag   标签
 *
 * @return     运输手柄
 */
esp_transport_handle_t esp_transport_list_get_transport(esp_transport_list_handle_t list, const char *scheme);

/**
 * @brief      初始化传输句柄对象
 *
 * @return     运输手柄
 */
esp_transport_handle_t esp_transport_init(void);

/**
 * @brief      清理并释放传输中的内存
 *
 * @param[in]  t     运输手柄
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_transport_destroy(esp_transport_handle_t t);

/**
 * @brief      获取此传输使用的默认端口号
 *
 * @param[in]  t     运输手柄
 *
 * @return     端口号
 */
int esp_transport_get_default_port(esp_transport_handle_t t);

/**
 * @brief      设置此传输可以使用的默认端口号
 *
 * @param[in]  t     运输手柄
 * @param[in]  port  端口号
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_transport_set_default_port(esp_transport_handle_t t, int port);

/**
 * @brief      传输连接功能，用于连接到服务器
 *
 * @param      t           运输手柄
 * @param[in]  host        主机名
 * @param[in]  port        港口城市
 * @param[in]  timeout_ms  超时毫秒（-1表示永远等待）
 *
 * @return
 * -此传输将使用的套接字
 * -（-1）如果有任何错误，应检查errno
 */
int esp_transport_connect(esp_transport_handle_t t, const char *host, int port, int timeout_ms);

/**
 * @brief      非阻塞传输连接功能，用于连接到服务器
 *
 * @param      t           运输手柄
 * @param[in]  host        主机名
 * @param[in]  port        港口城市
 * @param[in]  timeout_ms  超时毫秒（-1表示永远等待）
 *
 * @return
 * -此传输将使用的套接字
 * -（-1）如果有任何错误，应检查errno
 */
int esp_transport_connect_async(esp_transport_handle_t t, const char *host, int port, int timeout_ms);

/**
 * @brief      传输读取功能
 *
 * @param      t           运输手柄
 * @param      buffer      缓冲区
 * @param[in]  len         长度
 * @param[in]  timeout_ms  超时毫秒（-1表示永远等待）
 *
 * @return
 *  -读取的字节数
 *  -（-1）如果有任何错误，应检查errno
 */
int esp_transport_read(esp_transport_handle_t t, char *buffer, int len, int timeout_ms);

/**
 * @brief      轮询传输，直到可读或超时
 *
 * @param[in]  t           运输手柄
 * @param[in]  timeout_ms  超时毫秒（-1表示永远等待）
 *
 * @return
 *     -0超时
 *     -（-1）如果有任何错误，应检查errno
 *     -其他传输可以读取
 */
int esp_transport_poll_read(esp_transport_handle_t t, int timeout_ms);

/**
 * @brief      传输写入功能
 *
 * @param      t           运输手柄
 * @param      buffer      缓冲区
 * @param[in]  len         长度
 * @param[in]  timeout_ms  超时毫秒（-1表示永远等待）
 *
 * @return
 *  -写入的字节数
 *  -（-1）如果有任何错误，应检查errno
 */
int esp_transport_write(esp_transport_handle_t t, const char *buffer, int len, int timeout_ms);

/**
 * @brief      轮询传输，直到可写或超时
 *
 * @param[in]  t           运输手柄
 * @param[in]  timeout_ms  超时毫秒（-1表示永远等待）
 *
 * @return
 *     -0超时
 *     -（-1）如果有任何错误，应检查errno
 *     -其他传输可以写入
 */
int esp_transport_poll_write(esp_transport_handle_t t, int timeout_ms);

/**
 * @brief      运输关闭
 *
 * @param      t     运输手柄
 *
 * @return
 * -0（如果正常）
 * -（-1）如果有任何错误，应检查errno
 */
int esp_transport_close(esp_transport_handle_t t);

/**
 * @brief      获取此传输的用户数据上下文
 *
 * @param[in]  t        运输手柄
 *
 * @return     用户数据上下文
 */
void *esp_transport_get_context_data(esp_transport_handle_t t);

/**
 * @brief      获取可以直接访问该协议有效负载的底层协议的传输句柄（用于多次接收较长的消息）
 *
 * @param[in]  t        运输手柄
 *
 * @return     有效载荷运输手柄
 */
esp_transport_handle_t esp_transport_get_payload_transport_handle(esp_transport_handle_t t);

/**
 * @brief      设置此传输的用户上下文数据
 *
 * @param[in]  t        运输手柄
 * @param      data     用户数据上下文
 *
 * @return
 *     - ESP_OK
 */
esp_err_t esp_transport_set_context_data(esp_transport_handle_t t, void *data);

/**
 * @brief      设置运输手柄的运输功能
 *
 * @param[in]  t            运输手柄
 * @param[in]  _connect     connect函数指针
 * @param[in]  _read        读取函数指针
 * @param[in]  _write       写入函数指针
 * @param[in]  _close       关闭函数指针
 * @param[in]  _poll_read   轮询读取函数指针
 * @param[in]  _poll_write  轮询写入函数指针
 * @param[in]  _destroy     销毁函数指针
 *
 * @return
 *     - ESP_OK
 */
esp_err_t esp_transport_set_func(esp_transport_handle_t t,
                             connect_func _connect,
                             io_read_func _read,
                             io_func _write,
                             trans_func _close,
                             poll_func _poll_read,
                             poll_func _poll_write,
                             trans_func _destroy);


/**
 * @brief      设置运输手柄的运输功能
 *
 * @param[in]  t                    运输手柄
 * @param[in]  _connect_async_func  connect_async函数指针
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_transport_set_async_connect_func(esp_transport_handle_t t, connect_async_func _connect_async_func);

/**
 * @brief      将父传输函数设置为句柄
 *
 * @param[in]  t                    运输手柄
 * @param[in]  _parent_transport    基础传输getter指针
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t esp_transport_set_parent_transport_func(esp_transport_handle_t t, payload_transfer_func _parent_transport);

/**
 * @brief      返回esp_tls错误句柄。警告：仅当esp_transport_handle_t存在时，返回的指针才有效。一旦传输句柄被破坏，该值（esp_tls_error_handle_t）将自动释放。
 *
 * @param[in]  A 运输手柄
 *
 * @return
 *            -esp_error_handle_t的有效指针
 *            -如果传输句柄无效，则为NULL
 */
esp_tls_error_handle_t esp_transport_get_error_handle(esp_transport_handle_t t);

/**
 * @brief      获取并清除上次捕获的套接字错误号
 *
 * 每当用于读取、写入、轮询或连接的任何面向公共的API返回负返回代码失败时，套接字errno都会在内部存储。错误代码对应于使用“getsockopt（）”API从基础传输套接字检索的“SO_error”值。读取捕获的errno后，内部值将清除为0。
 *
 * @param[in] t 运输手柄
 *
 * @return
 *   ->=0上次捕获的套接字错误号
 *   --1无效的传输句柄或无效的传输内部错误存储
 */
int esp_transport_get_errno(esp_transport_handle_t t);

#ifdef __cplusplus
}
#endif
#endif /* _ESP_TRANSPORT_ */

