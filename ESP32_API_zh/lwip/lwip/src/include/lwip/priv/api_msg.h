/**
 * @file netconn API lwIP内部实现（不在应用程序代码中使用）
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_API_MSG_H
#define LWIP_HDR_API_MSG_H

#include "lwip/opt.h"

#include "lwip/arch.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/igmp.h"
#include "lwip/api.h"
#include "lwip/priv/tcpip_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_NETCONN || LWIP_SOCKET /* 如果未配置为在lwipots中使用，请不要构建。小时*/
/* 注意：当套接字被启用时，Netconn API总是可用的-套接字是在套接字之上实现的*/

#if LWIP_MPU_COMPATIBLE
#if LWIP_NETCONN_SEM_PER_THREAD
#define API_MSG_M_DEF_SEM(m)  *m
#else
#define API_MSG_M_DEF_SEM(m)  API_MSG_M_DEF(m)
#endif
#else /* LWIP_MPU_COMPATIBLE */
#define API_MSG_M_DEF_SEM(m)  API_MSG_M_DEF(m)
#endif /* LWIP_MPU_COMPATIBLE */

/* 对于netconn API，这些值用作位掩码！*/
#define NETCONN_SHUT_RD   1
#define NETCONN_SHUT_WR   2
#define NETCONN_SHUT_RDWR (NETCONN_SHUT_RD | NETCONN_SHUT_WR)

/* IP地址和端口号的字节顺序应与相应的pcb相同。
 */
/**此结构包含在另一个线程上下文中为netconn执行函数所需的所有内容（主要用于处理tcpip_thread上下文中的netconn以确保线程安全）。*/
struct api_msg {
  /**要处理的netconn总是需要的：它包括用于阻塞应用程序线程直到函数完成的信号量。*/
  struct netconn *conn;
  /**在tcpip_thread中执行的函数的返回值。*/
  err_t err;
  /**根据执行的函数，使用这些联合成员之一*/
  union {
    /**用于lwip_netcon_do_send*/
    struct netbuf *b;
    /**用于lwip_netcon_do_newconn*/
    struct {
      u8_t proto;
    } n;
    /**用于lwip_netcon_do_bind和lwip_neton_do_connect*/
    struct {
      API_MSG_M_DEF_C(ip_addr_t, ipaddr);
      u16_t port;
      u8_t if_idx;
    } bc;
    /**用于lwip_netcon_do_getaddr*/
    struct {
      ip_addr_t API_MSG_M_DEF(ipaddr);
      u16_t API_MSG_M_DEF(port);
      u8_t local;
    } ad;
    /**用于lwip_netcon_do_write*/
    struct {
      /**要写入的电流矢量*/
      const struct netvector *vector;
      /**未写入向量数*/
      u16_t vector_cnt;
      /**偏移到电流矢量*/
      size_t vector_off;
      /**矢量的总长度*/
      size_t len;
      /**当err==err_OK时写入的字节的总长度/输出偏移量*/
      size_t offset;
      u8_t apiflags;
#if LWIP_SO_SNDTIMEO
      u32_t time_started;
#endif /* LWIP_SO_SNDTIMEO */
    } w;
    /**用于lwip_netconn_do_recv*/
    struct {
      size_t len;
    } r;
#if LWIP_TCP
    /**用于lwip_netcon_do_close（/shutdown）*/
    struct {
      u8_t shut;
#if LWIP_SO_SNDTIMEO || LWIP_SO_LINGER
      u32_t time_started;
#else /* LWIP_SO_SNDTIMEO || LWIP_SO_LINGER */
      u8_t polls_left;
#endif /* LWIP_SO_SNDTIMEO || LWIP_SO_LINGER */
    } sd;
#endif /* LWIP_TCP */
#if LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD)
    /**用于lwip_netcon_do_join_leave_group*/
    struct {
      API_MSG_M_DEF_C(ip_addr_t, multiaddr);
      API_MSG_M_DEF_C(ip_addr_t, netif_addr);
      u8_t if_idx;
      enum netconn_igmp join_or_leave;
    } jl;
#endif /* LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD) */
#if TCP_LISTEN_BACKLOG
    struct {
      u8_t backlog;
    } lb;
#endif /* TCP_LISTEN_BACKLOG */
  } msg;
#if LWIP_NETCONN_SEM_PER_THREAD
  sys_sem_t* op_completed_sem;
#endif /* LWIP_NETCONN_SEM_PER_THREAD */
};

#if LWIP_NETCONN_SEM_PER_THREAD
#define LWIP_API_MSG_SEM(msg)          ((msg)->op_completed_sem)
#else /* LWIP_NETCONN_SEM_PER_THREAD */
#define LWIP_API_MSG_SEM(msg)          (&(msg)->conn->op_completed)
#endif /* LWIP_NETCONN_SEM_PER_THREAD */


#if LWIP_DNS
/**由于lwip_netconn_do_ggethostbyname需要更多的参数，但不需要netconn，因此它有自己的结构（以避免结构api_msg变得过大）。lwip_netcon_do_gethostbyname必须使用tcpip_callback而不是tcpip_apimsg来调用（请参阅netconn_gethostbyname）。*/
struct dns_api_msg {
  /**要查询的主机名或虚线IP地址字符串*/
#if LWIP_MPU_COMPATIBLE
  char name[DNS_MAX_NAME_LENGTH];
#else /* LWIP_MPU_COMPATIBLE */
  const char *name;
#endif /* LWIP_MPU_COMPATIBLE */
  /**解析地址存储在此处*/
  ip_addr_t API_MSG_M_DEF(addr);
#if LWIP_IPV4 && LWIP_IPV6
  /**解析调用类型*/
  u8_t dns_addrtype;
#endif /* LWIP_IPV4 && LWIP_IPV6 */
  /**这个信号在解析名称时发出，应用程序线程应该等待它。*/
  sys_sem_t API_MSG_M_DEF_SEM(sem);
  /**此处返回错误*/
  err_t API_MSG_M_DEF(err);
};
#endif /* LWIP_DNS */

#if LWIP_NETCONN_SEM_PER_THREAD
#if ESP_THREAD_SAFE
#define LWIP_NETCONN_THREAD_SEM_GET() sys_thread_sem_get()
#define LWIP_NETCONN_THREAD_SEM_ALLOC() sys_thread_sem_init()
#define LWIP_NETCONN_THREAD_SEM_FREE() sys_thread_sem_deinit()
#endif
#endif


#if LWIP_NETCONN_FULLDUPLEX
int lwip_netconn_is_deallocated_msg(void *msg);
#endif
int lwip_netconn_is_err_msg(void *msg, err_t *err);
void lwip_netconn_do_newconn         (void *m);
void lwip_netconn_do_delconn         (void *m);
void lwip_netconn_do_bind            (void *m);
void lwip_netconn_do_bind_if         (void *m);
void lwip_netconn_do_connect         (void *m);
void lwip_netconn_do_disconnect      (void *m);
void lwip_netconn_do_listen          (void *m);
void lwip_netconn_do_send            (void *m);
void lwip_netconn_do_recv            (void *m);
#if TCP_LISTEN_BACKLOG
void lwip_netconn_do_accepted        (void *m);
#endif /* TCP_LISTEN_BACKLOG */
void lwip_netconn_do_write           (void *m);
void lwip_netconn_do_getaddr         (void *m);
void lwip_netconn_do_close           (void *m);
void lwip_netconn_do_shutdown        (void *m);
#if LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD)
void lwip_netconn_do_join_leave_group(void *m);
void lwip_netconn_do_join_leave_group_netif(void *m);
#endif /* LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD) */

#if LWIP_DNS
void lwip_netconn_do_gethostbyname(void *arg);
#endif /* LWIP_DNS */

struct netconn* netconn_alloc(enum netconn_type t, netconn_callback callback);
void netconn_free(struct netconn *conn);

#endif /* LWIP_NETCONN || LWIP_SOCKET */

#if LWIP_NETIF_API /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/* netifapi相关lwIP内部定义*/

#if LWIP_MPU_COMPATIBLE
#define NETIFAPI_IPADDR_DEF(type, m)  type m
#else /* LWIP_MPU_COMPATIBLE */
#define NETIFAPI_IPADDR_DEF(type, m)  const type * m
#endif /* LWIP_MPU_COMPATIBLE */

typedef void (*netifapi_void_fn)(struct netif *netif);
typedef err_t (*netifapi_errt_fn)(struct netif *netif);

struct netifapi_msg {
  struct tcpip_api_call_data call;
  struct netif *netif;
  union {
    struct {
#if LWIP_IPV4
      NETIFAPI_IPADDR_DEF(ip4_addr_t, ipaddr);
      NETIFAPI_IPADDR_DEF(ip4_addr_t, netmask);
      NETIFAPI_IPADDR_DEF(ip4_addr_t, gw);
#endif /* LWIP_IPV4 */
      void *state;
      netif_init_fn init;
      netif_input_fn input;
    } add;
    struct {
      netifapi_void_fn voidfunc;
      netifapi_errt_fn errtfunc;
    } common;
    struct {
#if LWIP_MPU_COMPATIBLE
      char name[NETIF_NAMESIZE];
#else /* LWIP_MPU_COMPATIBLE */
      char *name;
#endif /* LWIP_MPU_COMPATIBLE */
      u8_t index;
    } ifs;
  } msg;
};

#endif /* LWIP_NETIF_API */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_API_MSG_H */

