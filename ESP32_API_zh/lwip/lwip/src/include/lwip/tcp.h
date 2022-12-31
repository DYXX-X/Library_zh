/**
 * @file TCP API（从TCPIP线程使用）\n另请参阅@ref TCP_raw
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
#ifndef LWIP_HDR_TCP_H
#define LWIP_HDR_TCP_H

#include "lwip/opt.h"

#if LWIP_TCP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/tcpbase.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/icmp.h"
#include "lwip/err.h"
#include "lwip/ip6.h"
#include "lwip/ip6_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

struct tcp_pcb;
struct tcp_pcb_listen;

/** tcp接受回调函数的函数原型。当监听pcb上可以接受新连接时调用。
 *
 * @param arg 要传递给回调函数的附加参数（@seetcp_arg（））
 * @param newpcb 新的连接pcb
 * @param err 如果接受错误，则返回错误代码。只有当您从回调函数中调用了tcp_art时，才返回ERR_ABRT！
 */
typedef err_t (*tcp_accept_fn)(void *arg, struct tcp_pcb *newpcb, err_t err);

/** tcp接收回调函数的函数原型。收到数据后调用。
 *
 * @param arg 要传递给回调函数的附加参数（@seetcp_arg（））
 * @param tpcb 接收数据的连接pcb
 * @param p 收到的数据（或连接关闭时为NULL！）
 * @param err 如果在回调函数中调用了tcp_art，则接收时出错，返回错误代码仅返回ERR_ABRT！
 */
typedef err_t (*tcp_recv_fn)(void *arg, struct tcp_pcb *tpcb,
                             struct pbuf *p, err_t err);

/** tcp发送回调函数的函数原型。当远程端已确认发送的数据时调用。使用它释放相应的资源。这也意味着pcb现在有空间发送新数据。
 *
 * @param arg 要传递给回调函数的附加参数（@seetcp_arg（））
 * @param tpcb 已确认数据的连接pcb
 * @param len 确认的字节数
 * @return ERR_OK：尝试通过调用tcp_output发送一些数据。如果从回调函数中调用了tcp_art，则只返回ERR_ABRT！
 */
typedef err_t (*tcp_sent_fn)(void *arg, struct tcp_pcb *tpcb,
                              u16_t len);

/** tcp轮询回调函数的函数原型。按照@seetcp_poll的指定定期调用。
 *
 * @param arg 要传递给回调函数的附加参数（@seetcp_arg（））
 * @param tpcb tcp印刷电路板
 * @return ERR_OK：尝试通过调用tcp_output发送一些数据。如果从回调函数中调用了tcp_art，则只返回ERR_ABRT！
 */
typedef err_t (*tcp_poll_fn)(void *arg, struct tcp_pcb *tpcb);

/** tcp错误回调函数的函数原型。当pcb接收到RST或因任何其他原因意外关闭时调用。
 *
 * @note 调用此回调时，相应的pcb已释放！
 *
 * @param arg 要传递给回调函数的附加参数（@seetcp_arg（））
 * @param err 指示pcb关闭原因的错误代码ERR_ABRT：通过tcp_art或tcp计时器中止ERR_RST：远程主机重置了连接
 */
typedef void  (*tcp_err_fn)(void *arg, err_t err);

/** 用于tcp连接回调函数的函数原型。通过调用tcp_connect（）启动连接尝试后，当pcb连接到远程端时调用。
 *
 * @param arg 要传递给回调函数的附加参数（@seetcp_arg（））
 * @param tpcb 所连接的连接pcb
 * @param err 未使用的错误代码，当前始终为ERR_OK；-）@todo！只有当您从回调函数中调用了tcp_art时，才返回ERR_ABRT！
 *
 * @note 当连接尝试失败时，当前将调用错误回调！
 */
typedef err_t (*tcp_connected_fn)(void *arg, struct tcp_pcb *tpcb, err_t err);

#if LWIP_WND_SCALE
#define RCV_WND_SCALE(pcb, wnd) (((wnd) >> (pcb)->rcv_scale))
#define SND_WND_SCALE(pcb, wnd) (((wnd) << (pcb)->snd_scale))
#define TCPWND16(x)             ((u16_t)LWIP_MIN((x), 0xFFFF))
#define TCP_WND_MAX(pcb)        ((tcpwnd_size_t)(((pcb)->flags & TF_WND_SCALE) ? TCP_WND : TCPWND16(TCP_WND)))
#else
#define RCV_WND_SCALE(pcb, wnd) (wnd)
#define SND_WND_SCALE(pcb, wnd) (wnd)
#define TCPWND16(x)             (x)
#define TCP_WND_MAX(pcb)        TCP_WND
#endif
/* 增加tcpwnd_size_t并保持最大值而不是滚动*/
#define TCP_WND_INC(wnd, inc)   do { \
                                  if ((tcpwnd_size_t)(wnd + inc) >= wnd) { \
                                    wnd = (tcpwnd_size_t)(wnd + inc); \
                                  } else { \
                                    wnd = (tcpwnd_size_t)-1; \
                                  } \
                                } while(0)

#if LWIP_TCP_SACK_OUT
/**要包含在ACK数据包中的SACK范围。如果左==右，SACK条目无效。*/
struct tcp_sack_range {
  /**SACK的左边缘：第一个确认的序列号。*/
  u32_t left;
  /**SACK的右边缘：最后确认的序列号+1（因此第一个未确认）。*/
  u32_t right;
};
#endif /* LWIP_TCP_SACK_OUT */

/** 用于释放参数的函数原型。在释放pcb之前调用，所以不要期望能够使用这个pcb做任何事情！
 *
 * @param id ext arg id（通过@ref tcp_ext_arg_alloc_id分配）
 * @param data 指向数据的指针（之前通过@ref tcp_ext_arg_set设置）
 */
typedef void (*tcp_extarg_callback_pcb_destroyed_fn)(u8_t id, void *data);

/** 将参数从侦听pcb转换为可接受pcb的函数原型
 *
 * @param id ext arg id（通过@ref tcp_ext_arg_alloc_id分配）
 * @param lpcb 接收连接的侦听pcb
 * @param cpcb 新分配的连接pcb
 * @return 如果正常，则返回ERR_OK，如果应断开连接，则返回任何错误
 */
typedef err_t (*tcp_extarg_callback_passive_open_fn)(u8_t id, struct tcp_pcb_listen *lpcb, struct tcp_pcb *cpcb);

/**为ext参数调用的回调函数表*/
struct tcp_ext_arg_callbacks {
  /**@ref tcp_extarg_callback_pcb_destroyed_fn*/
  tcp_extarg_callback_pcb_destroyed_fn destroy;
  /**@ref tcp_extarg_callback_passive_open_fn*/
  tcp_extarg_callback_passive_open_fn passive_open;
};

#define LWIP_TCP_PCB_NUM_EXT_ARG_ID_INVALID 0xFF

#if LWIP_TCP_PCB_NUM_EXT_ARGS
/* 这是tcp pcbs中ext args的结构（用作数组）*/
struct tcp_pcb_ext_args {
  const struct tcp_ext_arg_callbacks *callbacks;
  void *data;
};
/* 这是一个帮助器定义，用于在禁用时防止零大小数组*/
#define TCP_PCB_EXTARGS struct tcp_pcb_ext_args ext_args[LWIP_TCP_PCB_NUM_EXT_ARGS];
#else
#define TCP_PCB_EXTARGS
#endif

typedef u16_t tcpflags_t;
#define TCP_ALLFLAGS 0xffffU

/**
 * 结构tcp_pcb和结构tcplisten_pcb的公共成员
 */
#define TCP_PCB_COMMON(type) \
  type *next; /* 用于链接列表*/ \
  void *callback_arg; \
  TCP_PCB_EXTARGS \
  enum tcp_state state; /* TCP状态*/ \
  u8_t prio; \
  /* 端口按主机字节顺序排列*/ \
  u16_t local_port


/**用于监听pcbs的TCP协议控制块*/
struct tcp_pcb_listen {
/**所有PCB类型的通用构件*/
  IP_PCB;
/**特定于协议的PCB成员*/
  TCP_PCB_COMMON(struct tcp_pcb_listen);

#if LWIP_CALLBACK_API
  /* 连接侦听器时调用的函数。*/
  tcp_accept_fn accept;
#endif /* LWIP_CALLBACK_API */

#if TCP_LISTEN_BACKLOG
  u8_t backlog;
  u8_t accepts_pending;
#endif /* TCP_LISTEN_BACKLOG */
};


/**TCP协议控制块*/
struct tcp_pcb {
/**通用PCB构件*/
  IP_PCB;
/**协议特定PCB成员*/
  TCP_PCB_COMMON(struct tcp_pcb);

  /* 端口按主机字节顺序排列*/
  u16_t remote_port;

  tcpflags_t flags;
#define TF_ACK_DELAY   0x01U   /* 延迟确认。*/
#define TF_ACK_NOW     0x02U   /* 立即确认。*/
#define TF_INFR        0x04U   /* 快速恢复。*/
#define TF_CLOSEPEND   0x08U   /* 如果设置了此选项，tcp_close无法将FIN排入队列（在tcp_tmr中重试）*/
#define TF_RXCLOSED    0x10U   /* rx被tcpshutdown关闭*/
#define TF_FIN         0x20U   /* 连接已在本地关闭（FIN段已排队）。*/
#define TF_NODELAY     0x40U   /* 禁用Nagle算法*/
#define TF_NAGLEMEMERR 0x80U   /* 启用nagle，memerr，尝试输出以防止延迟ACK发生*/
#if LWIP_WND_SCALE
#define TF_WND_SCALE   0x0100U /* 窗口缩放选项已启用*/
#endif
#if TCP_LISTEN_BACKLOG
#define TF_BACKLOGPEND 0x0200U /* 如果设置了此选项，则连接pcb会增加其侦听器上的积压工作*/
#endif
#if LWIP_TCP_TIMESTAMPS
#define TF_TIMESTAMP   0x0400U   /* 时间戳选项已启用*/
#endif
#define TF_RTO         0x0800U /* RTO计时器已启动，飞行中的数据已移动到未发送状态并正在重新发送*/
#if LWIP_TCP_SACK_OUT
#define TF_SACK        0x1000U /* 启用选择性ACK*/
#endif

  /* 其余字段按主机字节顺序排列，因为我们必须对它们进行一些计算*/

  /* 计时器*/
  u8_t polltmr, pollinterval;
  u8_t last_timer;
  u32_t tmr;

  /* 接收机变量*/
  u32_t rcv_nxt;   /* 应为下一个seqno*/
  tcpwnd_size_t rcv_wnd;   /* 接收器窗口可用*/
  tcpwnd_size_t rcv_ann_wnd; /* 要通知的接收器窗口*/
  u32_t rcv_ann_right_edge; /* 宣布的窗口右边缘*/

#if LWIP_TCP_SACK_OUT
  /* 要包含在ACK数据包中的SACK范围（如果左==右，则条目无效）*/
  struct tcp_sack_range rcv_sacks[LWIP_TCP_MAX_SACK_NUM];
#define LWIP_TCP_SACK_VALID(pcb, idx) ((pcb)->rcv_sacks[idx].left != (pcb)->rcv_sacks[idx].right)
#endif /* LWIP_TCP_SACK_OUT */

  /* 重新传输计时器。*/
  s16_t rtime;

  u16_t mss;   /* 最大段大小*/

  /* RTT（往返时间）估计变量*/
  u32_t rttest; /* RTT估计值（以500ms为单位）*/
  u32_t rtseq;  /* 正在计时的序列号*/
  s16_t sa, sv; /* @参见Van Jacobson和Karels的《避免和控制拥堵》*/

  s16_t rto;    /* 重传超时（以TCP_SLOW_INTERVAL为单位）*/
  u8_t nrtx;    /* 重传次数*/

  /* 快速重传/恢复*/
  u8_t dupacks;
  u32_t lastack; /* 最高确认序号。*/

  /* 拥塞避免/控制变量*/
  tcpwnd_size_t cwnd;
  tcpwnd_size_t ssthresh;

  /* 最后rto字节后的第一个字节*/
  u32_t rto_end;

  /* 发送方变量*/
  u32_t snd_nxt;   /* 要发送的下一个新序列号*/
  u32_t snd_wl1, snd_wl2; /* 上次窗口更新的顺序和确认编号。*/
  u32_t snd_lbb;       /* 要缓冲的下一个字节的序列号。*/
  tcpwnd_size_t snd_wnd;   /* 发件人窗口*/
  tcpwnd_size_t snd_wnd_max; /* 远程主机宣布的最大发件人窗口*/

  tcpwnd_size_t snd_buf;   /* 用于发送的可用缓冲区空间（字节）。*/
#define TCP_SNDQUEUELEN_OVERFLOW (0xffffU-3)
  u16_t snd_queuelen; /* 当前在发送缓冲区中的pbuf数。*/

#if TCP_OVERSIZE
  /* 在未发送的最后一个pbuf结尾处可用的额外字节。*/
  u16_t unsent_oversize;
#endif /* TCP_OVERSIZE */

  tcpwnd_size_t bytes_acked;

  /* 这些按序列号排序：*/
  struct tcp_seg *unsent;   /* 未发送（排队）的段。*/
  struct tcp_seg *unacked;  /* 已发送但未确认的段。*/
#if TCP_QUEUE_OOSEQ
  struct tcp_seg *ooseq;    /* 接收到顺序错误的段。*/
#endif /* TCP_QUEUE_OOSEQ */

  struct pbuf *refused_data; /* 上层先前接收但尚未获取的数据*/

#if LWIP_CALLBACK_API || TCP_LISTEN_BACKLOG
  struct tcp_pcb_listen* listener;
#endif /* LWIP_CALLBACK_API || TCP_LISTEN_BACKLOG */

#if LWIP_CALLBACK_API
  /* 当更多的发送缓冲区空间可用时调用的函数。*/
  tcp_sent_fn sent;
  /* 数据到达时（按顺序）调用的函数。*/
  tcp_recv_fn recv;
  /* 建立连接后要调用的函数。*/
  tcp_connected_fn connected;
  /* 定期调用的函数。*/
  tcp_poll_fn poll;
  /* 发生致命错误时调用的函数。*/
  tcp_err_fn errf;
#endif /* LWIP_CALLBACK_API */

#if LWIP_TCP_TIMESTAMPS
  u32_t ts_lastacksent;
  u32_t ts_recent;
#endif /* LWIP_TCP_TIMESTAMPS */

  /* 发送KEEPALIVE之前的空闲时间*/
  u32_t keep_idle;
#if LWIP_TCP_KEEPALIVE
  u32_t keep_intvl;
  u32_t keep_cnt;
#endif /* LWIP_TCP_KEEPALIVE */

  /* 持续计时器计数器*/
  u8_t persist_cnt;
  /* 保持计时器关闭*/
  u8_t persist_backoff;
  /* 持续探测数*/
  u8_t persist_probe;

  /* KEEPALIVE计数器*/
  u8_t keep_cnt_sent;

#if LWIP_WND_SCALE
  u8_t snd_scale;
  u8_t rcv_scale;
#endif
};

#if LWIP_EVENT_API

enum lwip_event {
  LWIP_EVENT_ACCEPT,
  LWIP_EVENT_SENT,
  LWIP_EVENT_RECV,
  LWIP_EVENT_CONNECTED,
  LWIP_EVENT_POLL,
  LWIP_EVENT_ERR
};

err_t lwip_tcp_event(void *arg, struct tcp_pcb *pcb,
         enum lwip_event,
         struct pbuf *p,
         u16_t size,
         err_t err);

#endif /* LWIP_EVENT_API */

/* 应用程序界面：*/
struct tcp_pcb * tcp_new     (void);
struct tcp_pcb * tcp_new_ip_type (u8_t type);

void             tcp_arg     (struct tcp_pcb *pcb, void *arg);
#if LWIP_CALLBACK_API
void             tcp_recv    (struct tcp_pcb *pcb, tcp_recv_fn recv);
void             tcp_sent    (struct tcp_pcb *pcb, tcp_sent_fn sent);
void             tcp_err     (struct tcp_pcb *pcb, tcp_err_fn err);
void             tcp_accept  (struct tcp_pcb *pcb, tcp_accept_fn accept);
#endif /* LWIP_CALLBACK_API */
void             tcp_poll    (struct tcp_pcb *pcb, tcp_poll_fn poll, u8_t interval);

#define          tcp_set_flags(pcb, set_flags)     do { (pcb)->flags = (tcpflags_t)((pcb)->flags |  (set_flags)); } while(0)
#define          tcp_clear_flags(pcb, clr_flags)   do { (pcb)->flags = (tcpflags_t)((pcb)->flags & (tcpflags_t)(~(clr_flags) & TCP_ALLFLAGS)); } while(0)
#define          tcp_is_flag_set(pcb, flag)        (((pcb)->flags & (flag)) != 0)

#if LWIP_TCP_TIMESTAMPS
#define          tcp_mss(pcb)             (((pcb)->flags & TF_TIMESTAMP) ? ((pcb)->mss - 12)  : (pcb)->mss)
#else /* LWIP_TCP_TIMESTAMPS */
/**@inggroup tcp_raw*/
#define          tcp_mss(pcb)             ((pcb)->mss)
#endif /* LWIP_TCP_TIMESTAMPS */
/**@inggroup tcp_raw*/
#define          tcp_sndbuf(pcb)          (TCPWND16((pcb)->snd_buf))
/**@inggroup tcp_raw*/
#define          tcp_sndqueuelen(pcb)     ((pcb)->snd_queuelen)
/**@inggroup tcp_raw*/
#define          tcp_nagle_disable(pcb)   tcp_set_flags(pcb, TF_NODELAY)
/**@inggroup tcp_raw*/
#define          tcp_nagle_enable(pcb)    tcp_clear_flags(pcb, TF_NODELAY)
/**@inggroup tcp_raw*/
#define          tcp_nagle_disabled(pcb)  tcp_is_flag_set(pcb, TF_NODELAY)

#if TCP_LISTEN_BACKLOG
#define          tcp_backlog_set(pcb, new_backlog) do { \
  LWIP_ASSERT("pcb->state == LISTEN (called for wrong pcb?)", (pcb)->state == LISTEN); \
  ((struct tcp_pcb_listen *)(pcb))->backlog = ((new_backlog) ? (new_backlog) : 1); } while(0)
void             tcp_backlog_delayed(struct tcp_pcb* pcb);
void             tcp_backlog_accepted(struct tcp_pcb* pcb);
#else  /* TCP_LISTEN_BACKLOG */
#define          tcp_backlog_set(pcb, new_backlog)
#define          tcp_backlog_delayed(pcb)
#define          tcp_backlog_accepted(pcb)
#endif /* TCP_LISTEN_BACKLOG */
#define          tcp_accepted(pcb) do { LWIP_UNUSED_ARG(pcb); } while(0) /* 兼容性定义，不再需要*/

void             tcp_recved  (struct tcp_pcb *pcb, u16_t len);
err_t            tcp_bind    (struct tcp_pcb *pcb, const ip_addr_t *ipaddr,
                              u16_t port);
void             tcp_bind_netif(struct tcp_pcb *pcb, const struct netif *netif);
err_t            tcp_connect (struct tcp_pcb *pcb, const ip_addr_t *ipaddr,
                              u16_t port, tcp_connected_fn connected);

struct tcp_pcb * tcp_listen_with_backlog_and_err(struct tcp_pcb *pcb, u8_t backlog, err_t *err);
struct tcp_pcb * tcp_listen_with_backlog(struct tcp_pcb *pcb, u8_t backlog);
/**@inggroup tcp_raw*/
#define          tcp_listen(pcb) tcp_listen_with_backlog(pcb, TCP_DEFAULT_LISTEN_BACKLOG)

void             tcp_abort (struct tcp_pcb *pcb);
err_t            tcp_close   (struct tcp_pcb *pcb);
err_t            tcp_shutdown(struct tcp_pcb *pcb, int shut_rx, int shut_tx);

err_t            tcp_write   (struct tcp_pcb *pcb, const void *dataptr, u16_t len,
                              u8_t apiflags);

void             tcp_setprio (struct tcp_pcb *pcb, u8_t prio);

err_t            tcp_output  (struct tcp_pcb *pcb);

err_t            tcp_tcp_get_tcp_addrinfo(struct tcp_pcb *pcb, int local, ip_addr_t *addr, u16_t *port);

#define tcp_dbg_get_tcp_state(pcb) ((pcb)->state)

/* 以与较旧的实现兼容*/
#define tcp_new_ip6() tcp_new_ip_type(IPADDR_TYPE_V6)

#if LWIP_TCP_PCB_NUM_EXT_ARGS
u8_t tcp_ext_arg_alloc_id(void);
void tcp_ext_arg_set_callbacks(struct tcp_pcb *pcb, uint8_t id, const struct tcp_ext_arg_callbacks * const callbacks);
void tcp_ext_arg_set(struct tcp_pcb *pcb, uint8_t id, void *arg);
void *tcp_ext_arg_get(const struct tcp_pcb *pcb, uint8_t id);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_TCP */

#endif /* LWIP_HDR_TCP_H */

