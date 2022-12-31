/**
 * @file 应用程序分层TCP连接API（从TCPIP线程使用）\n此接口模拟应用程序的TCP回调API，同时防止直接链接（很像虚拟函数）。通过这种方式，应用程序可以在不知道细节的情况下（例如TLS、代理连接）使用TCP之上的其他应用程序层协议。
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
#ifndef LWIP_HDR_ALTCP_PRIV_H
#define LWIP_HDR_ALTCP_PRIV_H

#include "lwip/opt.h"

#if LWIP_ALTCP /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "lwip/altcp.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

struct altcp_pcb *altcp_alloc(void);
void altcp_free(struct altcp_pcb *conn);

/* 应用程序层的功能原型*/
typedef void (*altcp_set_poll_fn)(struct altcp_pcb *conn, u8_t interval);
typedef void (*altcp_recved_fn)(struct altcp_pcb *conn, u16_t len);
typedef err_t (*altcp_bind_fn)(struct altcp_pcb *conn, const ip_addr_t *ipaddr, u16_t port);
typedef err_t (*altcp_connect_fn)(struct altcp_pcb *conn, const ip_addr_t *ipaddr, u16_t port, altcp_connected_fn connected);

typedef struct altcp_pcb *(*altcp_listen_fn)(struct altcp_pcb *conn, u8_t backlog, err_t *err);

typedef void  (*altcp_abort_fn)(struct altcp_pcb *conn);
typedef err_t (*altcp_close_fn)(struct altcp_pcb *conn);
typedef err_t (*altcp_shutdown_fn)(struct altcp_pcb *conn, int shut_rx, int shut_tx);

typedef err_t (*altcp_write_fn)(struct altcp_pcb *conn, const void *dataptr, u16_t len, u8_t apiflags);
typedef err_t (*altcp_output_fn)(struct altcp_pcb *conn);

typedef u16_t (*altcp_mss_fn)(struct altcp_pcb *conn);
typedef u16_t (*altcp_sndbuf_fn)(struct altcp_pcb *conn);
typedef u16_t (*altcp_sndqueuelen_fn)(struct altcp_pcb *conn);
typedef void  (*altcp_nagle_disable_fn)(struct altcp_pcb *conn);
typedef void  (*altcp_nagle_enable_fn)(struct altcp_pcb *conn);
typedef int   (*altcp_nagle_disabled_fn)(struct altcp_pcb *conn);

typedef void  (*altcp_setprio_fn)(struct altcp_pcb *conn, u8_t prio);

typedef void  (*altcp_dealloc_fn)(struct altcp_pcb *conn);

typedef err_t (*altcp_get_tcp_addrinfo_fn)(struct altcp_pcb *conn, int local, ip_addr_t *addr, u16_t *port);
typedef ip_addr_t *(*altcp_get_ip_fn)(struct altcp_pcb *conn, int local);
typedef u16_t (*altcp_get_port_fn)(struct altcp_pcb *conn, int local);

#if LWIP_TCP_KEEPALIVE
typedef void  (*altcp_keepalive_disable_fn)(struct altcp_pcb *conn);
typedef void  (*altcp_keepalive_enable_fn)(struct altcp_pcb *conn, u32_t idle, u32_t intvl, u32_t count);
#endif

#ifdef LWIP_DEBUG
typedef enum tcp_state (*altcp_dbg_get_tcp_state_fn)(struct altcp_pcb *conn);
#endif

struct altcp_functions {
  altcp_set_poll_fn           set_poll;
  altcp_recved_fn             recved;
  altcp_bind_fn               bind;
  altcp_connect_fn            connect;
  altcp_listen_fn             listen;
  altcp_abort_fn              abort;
  altcp_close_fn              close;
  altcp_shutdown_fn           shutdown;
  altcp_write_fn              write;
  altcp_output_fn             output;
  altcp_mss_fn                mss;
  altcp_sndbuf_fn             sndbuf;
  altcp_sndqueuelen_fn        sndqueuelen;
  altcp_nagle_disable_fn      nagle_disable;
  altcp_nagle_enable_fn       nagle_enable;
  altcp_nagle_disabled_fn     nagle_disabled;
  altcp_setprio_fn            setprio;
  altcp_dealloc_fn            dealloc;
  altcp_get_tcp_addrinfo_fn   addrinfo;
  altcp_get_ip_fn             getip;
  altcp_get_port_fn           getport;
#if LWIP_TCP_KEEPALIVE
  altcp_keepalive_disable_fn  keepalive_disable;
  altcp_keepalive_enable_fn   keepalive_enable;
#endif
#ifdef LWIP_DEBUG
  altcp_dbg_get_tcp_state_fn  dbg_get_tcp_state;
#endif
};

void  altcp_default_set_poll(struct altcp_pcb *conn, u8_t interval);
void  altcp_default_recved(struct altcp_pcb *conn, u16_t len);
err_t altcp_default_bind(struct altcp_pcb *conn, const ip_addr_t *ipaddr, u16_t port);
err_t altcp_default_shutdown(struct altcp_pcb *conn, int shut_rx, int shut_tx);
err_t altcp_default_write(struct altcp_pcb *conn, const void *dataptr, u16_t len, u8_t apiflags);
err_t altcp_default_output(struct altcp_pcb *conn);
u16_t altcp_default_mss(struct altcp_pcb *conn);
u16_t altcp_default_sndbuf(struct altcp_pcb *conn);
u16_t altcp_default_sndqueuelen(struct altcp_pcb *conn);
void  altcp_default_nagle_disable(struct altcp_pcb *conn);
void  altcp_default_nagle_enable(struct altcp_pcb *conn);
int   altcp_default_nagle_disabled(struct altcp_pcb *conn);
void  altcp_default_setprio(struct altcp_pcb *conn, u8_t prio);
void  altcp_default_dealloc(struct altcp_pcb *conn);
err_t altcp_default_get_tcp_addrinfo(struct altcp_pcb *conn, int local, ip_addr_t *addr, u16_t *port);
ip_addr_t *altcp_default_get_ip(struct altcp_pcb *conn, int local);
u16_t altcp_default_get_port(struct altcp_pcb *conn, int local);
#if LWIP_TCP_KEEPALIVE
void  altcp_default_keepalive_disable(struct altcp_pcb *conn);
void  altcp_default_keepalive_enable(struct altcp_pcb *conn, u32_t idle, u32_t intvl, u32_t count);
#endif
#ifdef LWIP_DEBUG
enum tcp_state altcp_default_dbg_get_tcp_state(struct altcp_pcb *conn);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_ALTCP */

#endif /* LWIP_HDR_ALTCP_PRIV_H */

