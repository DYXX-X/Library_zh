/**
 * @file 应用程序分层TCP连接API（从TCPIP线程使用）\n
 *
 * 此文件包含通用API。有关详细信息，请参阅@ref altcp_api。
 */

/*
 * 版权所有（c）2017 Simon Goldschmidt保留所有权利。
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
#ifndef LWIP_HDR_ALTCP_H
#define LWIP_HDR_ALTCP_H

#include "lwip/opt.h"

#if LWIP_ALTCP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/tcpbase.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

struct altcp_pcb;
struct altcp_functions;

typedef err_t (*altcp_accept_fn)(void *arg, struct altcp_pcb *new_conn, err_t err);
typedef err_t (*altcp_connected_fn)(void *arg, struct altcp_pcb *conn, err_t err);
typedef err_t (*altcp_recv_fn)(void *arg, struct altcp_pcb *conn, struct pbuf *p, err_t err);
typedef err_t (*altcp_sent_fn)(void *arg, struct altcp_pcb *conn, u16_t len);
typedef err_t (*altcp_poll_fn)(void *arg, struct altcp_pcb *conn);
typedef void  (*altcp_err_fn)(void *arg, err_t err);

typedef struct altcp_pcb* (*altcp_new_fn)(void *arg, u8_t ip_type);

struct altcp_pcb {
  const struct altcp_functions *fns;
  struct altcp_pcb *inner_conn;
  void *arg;
  void *state;
  /* 应用程序回调*/
  altcp_accept_fn     accept;
  altcp_connected_fn  connected;
  altcp_recv_fn       recv;
  altcp_sent_fn       sent;
  altcp_poll_fn       poll;
  altcp_err_fn        err;
  u8_t pollinterval;
};

/**@ingroup altcp*/
typedef struct altcp_allocator_s {
  /**分配器功能*/
  altcp_new_fn  alloc;
  /**分配器函数的参数*/
  void         *arg;
} altcp_allocator_t;

struct altcp_pcb *altcp_new(altcp_allocator_t *allocator);
struct altcp_pcb *altcp_new_ip6(altcp_allocator_t *allocator);
struct altcp_pcb *altcp_new_ip_type(altcp_allocator_t *allocator, u8_t ip_type);

void altcp_arg(struct altcp_pcb *conn, void *arg);
void altcp_accept(struct altcp_pcb *conn, altcp_accept_fn accept);
void altcp_recv(struct altcp_pcb *conn, altcp_recv_fn recv);
void altcp_sent(struct altcp_pcb *conn, altcp_sent_fn sent);
void altcp_poll(struct altcp_pcb *conn, altcp_poll_fn poll, u8_t interval);
void altcp_err(struct altcp_pcb *conn, altcp_err_fn err);

void  altcp_recved(struct altcp_pcb *conn, u16_t len);
err_t altcp_bind(struct altcp_pcb *conn, const ip_addr_t *ipaddr, u16_t port);
err_t altcp_connect(struct altcp_pcb *conn, const ip_addr_t *ipaddr, u16_t port, altcp_connected_fn connected);

/* 仅返回源代码与tcp回调API兼容的conn*/
struct altcp_pcb *altcp_listen_with_backlog_and_err(struct altcp_pcb *conn, u8_t backlog, err_t *err);
#define altcp_listen_with_backlog(conn, backlog) altcp_listen_with_backlog_and_err(conn, backlog, NULL)
/**@ingroup altcp*/
#define altcp_listen(conn) altcp_listen_with_backlog_and_err(conn, TCP_DEFAULT_LISTEN_BACKLOG, NULL)

void altcp_abort(struct altcp_pcb *conn);
err_t altcp_close(struct altcp_pcb *conn);
err_t altcp_shutdown(struct altcp_pcb *conn, int shut_rx, int shut_tx);

err_t altcp_write(struct altcp_pcb *conn, const void *dataptr, u16_t len, u8_t apiflags);
err_t altcp_output(struct altcp_pcb *conn);

u16_t altcp_mss(struct altcp_pcb *conn);
u16_t altcp_sndbuf(struct altcp_pcb *conn);
u16_t altcp_sndqueuelen(struct altcp_pcb *conn);
void  altcp_nagle_disable(struct altcp_pcb *conn);
void  altcp_nagle_enable(struct altcp_pcb *conn);
int   altcp_nagle_disabled(struct altcp_pcb *conn);

void  altcp_setprio(struct altcp_pcb *conn, u8_t prio);

err_t altcp_get_tcp_addrinfo(struct altcp_pcb *conn, int local, ip_addr_t *addr, u16_t *port);
ip_addr_t *altcp_get_ip(struct altcp_pcb *conn, int local);
u16_t altcp_get_port(struct altcp_pcb *conn, int local);

#if LWIP_TCP_KEEPALIVE
void  altcp_keepalive_disable(struct altcp_pcb *conn);
void  altcp_keepalive_enable(struct altcp_pcb *conn, u32_t idle, u32_t intvl, u32_t count);
#endif

#ifdef LWIP_DEBUG
enum tcp_state altcp_dbg_get_tcp_state(struct altcp_pcb *conn);
#endif

#ifdef __cplusplus
}
#endif

#else /* LWIP_ALTCP */

/* ALTCP已禁用，请根据tcp回调API定义所有链接（例如，获取一个小的非ssl httpd）*/

#include "lwip/tcp.h"

#define altcp_accept_fn tcp_accept_fn
#define altcp_connected_fn tcp_connected_fn
#define altcp_recv_fn tcp_recv_fn
#define altcp_sent_fn tcp_sent_fn
#define altcp_poll_fn tcp_poll_fn
#define altcp_err_fn tcp_err_fn

#define altcp_pcb tcp_pcb
#define altcp_tcp_new_ip_type tcp_new_ip_type
#define altcp_tcp_new tcp_new
#define altcp_tcp_new_ip6 tcp_new_ip6

#define altcp_new(allocator) tcp_new()
#define altcp_new_ip6(allocator) tcp_new_ip6()
#define altcp_new_ip_type(allocator, ip_type) tcp_new_ip_type(ip_type)

#define altcp_arg tcp_arg
#define altcp_accept tcp_accept
#define altcp_recv tcp_recv
#define altcp_sent tcp_sent
#define altcp_poll tcp_poll
#define altcp_err tcp_err

#define altcp_recved tcp_recved
#define altcp_bind tcp_bind
#define altcp_connect tcp_connect

#define altcp_listen_with_backlog_and_err tcp_listen_with_backlog_and_err
#define altcp_listen_with_backlog tcp_listen_with_backlog
#define altcp_listen tcp_listen

#define altcp_abort tcp_abort
#define altcp_close tcp_close
#define altcp_shutdown tcp_shutdown

#define altcp_write tcp_write
#define altcp_output tcp_output

#define altcp_mss tcp_mss
#define altcp_sndbuf tcp_sndbuf
#define altcp_sndqueuelen tcp_sndqueuelen
#define altcp_nagle_disable tcp_nagle_disable
#define altcp_nagle_enable tcp_nagle_enable
#define altcp_nagle_disabled tcp_nagle_disabled
#define altcp_setprio tcp_setprio

#define altcp_get_tcp_addrinfo tcp_get_tcp_addrinfo
#define altcp_get_ip(pcb, local) ((local) ? (&(pcb)->local_ip) : (&(pcb)->remote_ip))

#ifdef LWIP_DEBUG
#define altcp_dbg_get_tcp_state tcp_dbg_get_tcp_state
#endif

#endif /* LWIP_ALTCP */

#endif /* LWIP_HDR_ALTCP_H */

