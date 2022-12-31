/**
 * @file HTTP客户端
 */

/*
 * 版权所有（c）2018 Simon Goldschmidt<goldsimon@gmx.de>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 *
 */

#ifndef LWIP_HDR_APPS_HTTP_CLIENT_H
#define LWIP_HDR_APPS_HTTP_CLIENT_H

#include "lwip/opt.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/altcp.h"
#include "lwip/prot/iana.h"
#include "lwip/pbuf.h"

#if LWIP_TCP && LWIP_CALLBACK_API

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup httpc httpc_HAVE_FILE_IO：将其定义为1，使函数通过fopen/fwrite直接下载到磁盘。这些函数只是接口的示例实现。
 */
#ifndef LWIP_HTTPC_HAVE_FILE_IO
#define LWIP_HTTPC_HAVE_FILE_IO   0
#endif

/**
 * @ingroup httpc用于HTTP的默认TCP端口
 */
#define HTTP_DEFAULT_PORT         LWIP_IANA_PORT_HTTP

/**
 * @ingroup httpc HTTP客户端结果代码
 */
typedef enum ehttpc_result {
  /**文件已成功接收*/
  HTTPC_RESULT_OK            = 0,
  /**未知错误*/
  HTTPC_RESULT_ERR_UNKNOWN   = 1,
  /**连接到服务器失败*/
  HTTPC_RESULT_ERR_CONNECT   = 2,
  /**无法解析服务器主机名*/
  HTTPC_RESULT_ERR_HOSTNAME  = 3,
  /**远程服务器意外关闭了连接*/
  HTTPC_RESULT_ERR_CLOSED    = 4,
  /**连接超时（服务器未及时响应）*/
  HTTPC_RESULT_ERR_TIMEOUT   = 5,
  /**服务器响应错误代码*/
  HTTPC_RESULT_ERR_SVR_RESP  = 6,
  /**本地内存错误*/
  HTTPC_RESULT_ERR_MEM       = 7,
  /**本地中止*/
  HTTPC_RESULT_LOCAL_ABORT   = 8,
  /**内容长度不匹配*/
  HTTPC_RESULT_ERR_CONTENT_LEN = 9
} httpc_result_t;

typedef struct _httpc_state httpc_state_t;

/**
 * @ingroup http客户端回调函数的httpc原型
 *
 * @param arg 启动请求时指定的参数
 * @param httpc_result http传输的结果（请参见enum-httpc_resultt）
 * @param rx_content_len 接收的字节数（无标头）
 * @param srv_res 这包含收到的http状态代码（如果有）
 * @param err 内部lwip函数返回的错误可以帮助指定错误的来源，但不一定是！=错误（_O）
 */
typedef void (*httpc_result_fn)(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err);

/**
 * @ingroup http客户端回调的httpc原型：在收到标头时调用
 *
 * @param connection http客户端连接
 * @param arg 启动请求时指定的参数
 * @param hdr 标头pbuf（s）（也可以包含数据）
 * @param hdr_len “hdr”中综框的长度
 * @param content_len 标头中接收的内容长度（如果未接收，则为-1）
 * @return 如果！=返回ERR_OK，连接中止
 */
typedef err_t (*httpc_headers_done_fn)(httpc_state_t *connection, void *arg, struct pbuf *hdr, u16_t hdr_len, u32_t content_len);

typedef struct _httpc_connection {
  ip_addr_t proxy_addr;
  u16_t proxy_port;
  u8_t use_proxy;
  /* @todo：添加用户名：pass？*/

#if LWIP_ALTCP
  altcp_allocator_t *altcp_allocator;
#endif

  /* 当传输完成（或中止）时调用此回调*/
  httpc_result_fn result_fn;
  /* 此回调是在收到http标头后调用的。它可以通过返回！=错误（_O）*/
  httpc_headers_done_fn headers_done_fn;
} httpc_connection_t;

err_t httpc_get_file(const ip_addr_t* server_addr, u16_t port, const char* uri, const httpc_connection_t *settings,
                     altcp_recv_fn recv_fn, void* callback_arg, httpc_state_t **connection);
err_t httpc_get_file_dns(const char* server_name, u16_t port, const char* uri, const httpc_connection_t *settings,
                     altcp_recv_fn recv_fn, void* callback_arg, httpc_state_t **connection);

#if LWIP_HTTPC_HAVE_FILE_IO
err_t httpc_get_file_to_disk(const ip_addr_t* server_addr, u16_t port, const char* uri, const httpc_connection_t *settings,
                     void* callback_arg, const char* local_file_name, httpc_state_t **connection);
err_t httpc_get_file_dns_to_disk(const char* server_name, u16_t port, const char* uri, const httpc_connection_t *settings,
                     void* callback_arg, const char* local_file_name, httpc_state_t **connection);
#endif /* LWIP_HTTPC_HAVE_FILE_IO */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_TCP && LWIP_CALLBACK_API */

#endif /* LWIP_HDR_APPS_HTTP_CLIENT_H */

