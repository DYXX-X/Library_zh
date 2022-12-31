/**
 * @file TCP内部实现（不在应用程序代码中使用）
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
#ifndef LWIP_HDR_TCP_PRIV_H
#define LWIP_HDR_TCP_PRIV_H

#include "lwip/opt.h"

#if LWIP_TCP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/tcp.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/icmp.h"
#include "lwip/err.h"
#include "lwip/ip6.h"
#include "lwip/ip6_addr.h"
#include "lwip/prot/tcp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 与TCP接口的功能：*/

/* TCP的下层接口：*/
void             tcp_init    (void);  /* 初始化此模块。*/
void             tcp_tmr     (void);  /* 必须每TCP_TMR_INVAL ms（通常为250 ms）调用一次。*/
/* 也可以在适当的时间间隔调用这两个函数（而不是调用tcp_tmr（））。*/
void             tcp_slowtmr (void);
void             tcp_fasttmr (void);

/* 从netif驱动程序调用此命令（注意线程问题！）它在传输时返回了一个内存错误，现在有空闲的缓冲区可以发送更多。这将迭代所有出现错误的活动pcb，并尝试调用tcp_output，因此请小心使用，因为这可能会降低系统速度。*/
void             tcp_txnow   (void);

/* 仅由IP用于将TCP段传递给TCP：*/
void             tcp_input   (struct pbuf *p, struct netif *inp);
/* 仅在TCP代码中使用：*/
struct tcp_pcb * tcp_alloc   (u8_t prio);
void             tcp_free    (struct tcp_pcb *pcb);
void             tcp_abandon (struct tcp_pcb *pcb, int reset);
err_t            tcp_send_empty_ack(struct tcp_pcb *pcb);
err_t            tcp_rexmit  (struct tcp_pcb *pcb);
err_t            tcp_rexmit_rto_prepare(struct tcp_pcb *pcb);
void             tcp_rexmit_rto_commit(struct tcp_pcb *pcb);
void             tcp_rexmit_rto  (struct tcp_pcb *pcb);
void             tcp_rexmit_fast (struct tcp_pcb *pcb);
u32_t            tcp_update_rcv_ann_wnd(struct tcp_pcb *pcb);
err_t            tcp_process_refused_data(struct tcp_pcb *pcb);

/**
 * 这就是Nagle算法：尝试组合用户数据以发送尽可能少的TCP段。仅在以下情况下发送
 * -连接上没有先前传输的数据保持未确认或
 * -TF_NODELAY标志已设置（此pcb的nagle算法已关闭）或
 * -唯一未发送的段至少为pcb->mss字节长（或有多个未发送的分段-使用lwIP，尽管未发送->len<mss，但仍可能发生这种情况）
 * -或者如果我们正在快速重传（TF_INFR）
 */
#define tcp_do_output_nagle(tpcb) ((((tpcb)->unacked == NULL) || \
                            ((tpcb)->flags & (TF_NODELAY | TF_INFR)) || \
                            (((tpcb)->unsent != NULL) && (((tpcb)->unsent->next != NULL) || \
                              ((tpcb)->unsent->len >= (tpcb)->mss))) || \
                            ((tcp_sndbuf(tpcb) == 0) || (tcp_sndqueuelen(tpcb) >= TCP_SND_QUEUELEN)) \
                            ) ? 1 : 0)
#define tcp_output_nagle(tpcb) (tcp_do_output_nagle(tpcb) ? tcp_output(tpcb) : ERR_OK)


#define TCP_SEQ_LT(a,b)     ((s32_t)((u32_t)(a) - (u32_t)(b)) < 0)
#define TCP_SEQ_LEQ(a,b)    ((s32_t)((u32_t)(a) - (u32_t)(b)) <= 0)
#define TCP_SEQ_GT(a,b)     ((s32_t)((u32_t)(a) - (u32_t)(b)) > 0)
#define TCP_SEQ_GEQ(a,b)    ((s32_t)((u32_t)(a) - (u32_t)(b)) >= 0)
/* b<=a<=c？*/
#if 0 /* 参见错误#10548*/
#define TCP_SEQ_BETWEEN(a,b,c) ((c)-(b) >= (a)-(b))
#endif
#define TCP_SEQ_BETWEEN(a,b,c) (TCP_SEQ_GEQ(a,b) && TCP_SEQ_LEQ(a,c))

#ifndef TCP_TMR_INTERVAL
#define TCP_TMR_INTERVAL       250  /* TCP计时器间隔（毫秒）。*/
#endif /* TCP_TMR_INTERVAL */

#ifndef TCP_FAST_INTERVAL
#define TCP_FAST_INTERVAL      TCP_TMR_INTERVAL /* 细粒度超时（毫秒）*/
#endif /* TCP_FAST_INTERVAL */

#ifndef TCP_SLOW_INTERVAL
#define TCP_SLOW_INTERVAL      (2*TCP_TMR_INTERVAL)  /* 粗粒度超时（毫秒）*/
#endif /* TCP_SLOW_INTERVAL */

#define TCP_FIN_WAIT_TIMEOUT 20000 /* 毫秒*/
#define TCP_SYN_RCVD_TIMEOUT 20000 /* 毫秒*/

#define TCP_OOSEQ_TIMEOUT        6U /* x RTO*/

#ifndef TCP_MSL
#define TCP_MSL 60000UL /* 最大段生存时间（毫秒）*/
#endif

/* Keepalive值，符合RFC 1122。除非您知道自己在做什么，否则不要更改此值*/
#ifndef  TCP_KEEPIDLE_DEFAULT
#define  TCP_KEEPIDLE_DEFAULT     7200000UL /* 默认KEEPALIVE计时器（毫秒）*/
#endif

#ifndef  TCP_KEEPINTVL_DEFAULT
#define  TCP_KEEPINTVL_DEFAULT    75000UL   /* KEEPALIVE探测之间的默认时间（毫秒）*/
#endif

#ifndef  TCP_KEEPCNT_DEFAULT
#define  TCP_KEEPCNT_DEFAULT      9U        /* KEEPALIVE探测的默认计数器*/
#endif

#define  TCP_MAXIDLE              TCP_KEEPCNT_DEFAULT * TCP_KEEPINTVL_DEFAULT  /* 最长KEEPALIVE探测时间*/

#define TCP_TCPLEN(seg) ((seg)->len + (((TCPH_FLAGS((seg)->tcphdr) & (TCP_FIN | TCP_SYN)) != 0) ? 1U : 0U))

/** 用于输入处理的标志，而不是pcb->标志
*/
#define TF_RESET     (u8_t)0x08U   /* 连接已重置。*/
#define TF_CLOSED    (u8_t)0x10U   /* 连接已成功关闭。*/
#define TF_GOT_FIN   (u8_t)0x20U   /* 远程端已关闭连接。*/


#if LWIP_EVENT_API

#define TCP_EVENT_ACCEPT(lpcb,pcb,arg,err,ret) ret = lwip_tcp_event(arg, (pcb),\
                LWIP_EVENT_ACCEPT, NULL, 0, err)
#define TCP_EVENT_SENT(pcb,space,ret) ret = lwip_tcp_event((pcb)->callback_arg, (pcb),\
                   LWIP_EVENT_SENT, NULL, space, ERR_OK)
#define TCP_EVENT_RECV(pcb,p,err,ret) ret = lwip_tcp_event((pcb)->callback_arg, (pcb),\
                LWIP_EVENT_RECV, (p), 0, (err))
#define TCP_EVENT_CLOSED(pcb,ret) ret = lwip_tcp_event((pcb)->callback_arg, (pcb),\
                LWIP_EVENT_RECV, NULL, 0, ERR_OK)
#define TCP_EVENT_CONNECTED(pcb,err,ret) ret = lwip_tcp_event((pcb)->callback_arg, (pcb),\
                LWIP_EVENT_CONNECTED, NULL, 0, (err))
#define TCP_EVENT_POLL(pcb,ret)       do { if ((pcb)->state != SYN_RCVD) {                          \
                ret = lwip_tcp_event((pcb)->callback_arg, (pcb), LWIP_EVENT_POLL, NULL, 0, ERR_OK); \
                } else {                                                                            \
                ret = ERR_ARG; } } while(0)
/* 对于事件API，这里必须排除最后状态SYN_RCVD：应用程序还没有看到这个pcb！*/
#define TCP_EVENT_ERR(last_state,errf,arg,err)  do { if (last_state != SYN_RCVD) {                \
                lwip_tcp_event((arg), NULL, LWIP_EVENT_ERR, NULL, 0, (err)); } } while(0)

#else /* LWIP_EVENT_API */

#define TCP_EVENT_ACCEPT(lpcb,pcb,arg,err,ret)                 \
  do {                                                         \
    if((lpcb)->accept != NULL)                                 \
      (ret) = (lpcb)->accept((arg),(pcb),(err));               \
    else (ret) = ERR_ARG;                                      \
  } while (0)

#define TCP_EVENT_SENT(pcb,space,ret)                          \
  do {                                                         \
    if((pcb)->sent != NULL)                                    \
      (ret) = (pcb)->sent((pcb)->callback_arg,(pcb),(space));  \
    else (ret) = ERR_OK;                                       \
  } while (0)

#define TCP_EVENT_RECV(pcb,p,err,ret)                          \
  do {                                                         \
    if((pcb)->recv != NULL) {                                  \
      (ret) = (pcb)->recv((pcb)->callback_arg,(pcb),(p),(err));\
    } else {                                                   \
      (ret) = tcp_recv_null(NULL, (pcb), (p), (err));          \
    }                                                          \
  } while (0)

#define TCP_EVENT_CLOSED(pcb,ret)                                \
  do {                                                           \
    if(((pcb)->recv != NULL)) {                                  \
      (ret) = (pcb)->recv((pcb)->callback_arg,(pcb),NULL,ERR_OK);\
    } else {                                                     \
      (ret) = ERR_OK;                                            \
    }                                                            \
  } while (0)

#define TCP_EVENT_CONNECTED(pcb,err,ret)                         \
  do {                                                           \
    if((pcb)->connected != NULL)                                 \
      (ret) = (pcb)->connected((pcb)->callback_arg,(pcb),(err)); \
    else (ret) = ERR_OK;                                         \
  } while (0)

#define TCP_EVENT_POLL(pcb,ret)                                \
  do {                                                         \
    if((pcb)->poll != NULL)                                    \
      (ret) = (pcb)->poll((pcb)->callback_arg,(pcb));          \
    else (ret) = ERR_OK;                                       \
  } while (0)

#define TCP_EVENT_ERR(last_state,errf,arg,err)                 \
  do {                                                         \
    LWIP_UNUSED_ARG(last_state);                               \
    if((errf) != NULL)                                         \
      (errf)((arg),(err));                                     \
  } while (0)

#endif /* LWIP_EVENT_API */

/**如果启用LWIP_DEBUG，则启用TCP_OVERSIZE的额外检查*/
#if TCP_OVERSIZE && defined(LWIP_DEBUG)
#define TCP_OVERSIZE_DBGCHECK 1
#else
#define TCP_OVERSIZE_DBGCHECK 0
#endif

/**如果禁用checksum_GEN_TCP，则不在复制时生成校验和*/
#define TCP_CHECKSUM_ON_COPY  (LWIP_CHECKSUM_ON_COPY && CHECKSUM_GEN_TCP)

/* 此结构表示未发送、未激活和ooseq队列上的TCP段*/
struct tcp_seg {
  struct tcp_seg *next;    /* 将段放入队列时使用*/
  struct pbuf *p;          /* 包含数据和TCP标头的缓冲区*/
  u16_t len;               /* 此段的TCP长度*/
#if TCP_OVERSIZE_DBGCHECK
  u16_t oversize_left;     /* unsent中最后一个pbuf结尾处可用的额外字节（仅用于断言与tcp_pcb.unsent_oversize）*/
#endif /* TCP_OVERSIZE_DBGCHECK */
#if TCP_CHECKSUM_ON_COPY
  u16_t chksum;
  u8_t  chksum_swapped;
#endif /* TCP_CHECKSUM_ON_COPY */
  u8_t  flags;
#define TF_SEG_OPTS_MSS         (u8_t)0x01U /* 包括MSS选项（仅用于SYN段）*/
#define TF_SEG_OPTS_TS          (u8_t)0x02U /* 包括时间戳选项。*/
#define TF_SEG_DATA_CHECKSUMMED (u8_t)0x04U /* 所有数据（不是标头）都被校验和为“chksum”*/
#define TF_SEG_OPTS_WND_SCALE   (u8_t)0x08U /* 包括WND SCALE选项（仅用于SYN段）*/
#define TF_SEG_OPTS_SACK_PERM   (u8_t)0x10U /* 包括SACK许可选项（仅用于SYN段）*/
  struct tcp_hdr *tcphdr;  /* TCP标头*/
};

#define LWIP_TCP_OPT_EOL        0
#define LWIP_TCP_OPT_NOP        1
#define LWIP_TCP_OPT_MSS        2
#define LWIP_TCP_OPT_WS         3
#define LWIP_TCP_OPT_SACK_PERM  4
#define LWIP_TCP_OPT_TS         8

#define LWIP_TCP_OPT_LEN_MSS    4
#if LWIP_TCP_TIMESTAMPS
#define LWIP_TCP_OPT_LEN_TS     10
#define LWIP_TCP_OPT_LEN_TS_OUT 12 /* 对齐输出（包括NOP填充）*/
#else
#define LWIP_TCP_OPT_LEN_TS_OUT 0
#endif
#if LWIP_WND_SCALE
#define LWIP_TCP_OPT_LEN_WS     3
#define LWIP_TCP_OPT_LEN_WS_OUT 4 /* 对齐输出（包括NOP填充）*/
#else
#define LWIP_TCP_OPT_LEN_WS_OUT 0
#endif

#if LWIP_TCP_SACK_OUT
#define LWIP_TCP_OPT_LEN_SACK_PERM     2
#define LWIP_TCP_OPT_LEN_SACK_PERM_OUT 4 /* 对齐输出（包括NOP填充）*/
#else
#define LWIP_TCP_OPT_LEN_SACK_PERM_OUT 0
#endif

#define LWIP_TCP_OPT_LENGTH(flags) \
  ((flags) & TF_SEG_OPTS_MSS       ? LWIP_TCP_OPT_LEN_MSS           : 0) + \
  ((flags) & TF_SEG_OPTS_TS        ? LWIP_TCP_OPT_LEN_TS_OUT        : 0) + \
  ((flags) & TF_SEG_OPTS_WND_SCALE ? LWIP_TCP_OPT_LEN_WS_OUT        : 0) + \
  ((flags) & TF_SEG_OPTS_SACK_PERM ? LWIP_TCP_OPT_LEN_SACK_PERM_OUT : 0)

/**这将返回u32_t中MSS的TCP头选项*/
#define TCP_BUILD_MSS_OPTION(mss) lwip_htonl(0x02040000 | ((mss) & 0xFFFF))

#if LWIP_WND_SCALE
#define TCPWNDSIZE_F       U32_F
#define TCPWND_MAX         0xFFFFFFFFU
#define TCPWND_CHECK16(x)  LWIP_ASSERT("window size > 0xFFFF", (x) <= 0xFFFF)
#define TCPWND_MIN16(x)    ((u16_t)LWIP_MIN((x), 0xFFFF))
#else /* LWIP_WND_SCALE */
#define TCPWNDSIZE_F       U16_F
#define TCPWND_MAX         0xFFFFU
#define TCPWND_CHECK16(x)
#define TCPWND_MIN16(x)    x
#endif /* LWIP_WND_SCALE */

/* 全局变量：*/
extern struct tcp_pcb *tcp_input_pcb;
extern u32_t tcp_ticks;
extern u8_t tcp_active_pcbs_changed;

/* TCP PCB列表。*/
union tcp_listen_pcbs_t { /* 处于LISTEN状态的所有TCP PCB的列表。*/
  struct tcp_pcb_listen *listen_pcbs;
  struct tcp_pcb *pcbs;
};
extern struct tcp_pcb *tcp_bound_pcbs;
extern union tcp_listen_pcbs_t tcp_listen_pcbs;
extern struct tcp_pcb *tcp_active_pcbs;  /* 处于接受或发送数据状态的所有TCP PCB的列表。*/
extern struct tcp_pcb *tcp_tw_pcbs;      /* TIME-WAIT中所有TCP PCB的列表。*/

#define NUM_TCP_PCB_LISTS_NO_TIME_WAIT  3
#define NUM_TCP_PCB_LISTS               4
extern struct tcp_pcb ** const tcp_pcb_lists[NUM_TCP_PCB_LISTS];

/* 关于以上列表的公理：1）每个未关闭的TCP PCB都在其中一个列表中。2） PCB仅在其中一个列表中。3） tcp_listen_PCBs列表中的所有PCB都处于listen状态。4） tcp_tw_PCBs列表中的所有PCB都处于TIME-WAIT状态。
*/
/* 定义两个宏TCP_REG和TCP_RMV，分别在PCB列表中注册TCP PCB或从列表中删除PCB。*/
#ifndef TCP_DEBUG_PCB_LISTS
#define TCP_DEBUG_PCB_LISTS 0
#endif
#if TCP_DEBUG_PCB_LISTS
#define TCP_REG(pcbs, npcb) do {\
                            struct tcp_pcb *tcp_tmp_pcb; \
                            LWIP_DEBUGF(TCP_DEBUG, ("TCP_REG %p local port %"U16_F"\n", (void *)(npcb), (npcb)->local_port)); \
                            for (tcp_tmp_pcb = *(pcbs); \
          tcp_tmp_pcb != NULL; \
        tcp_tmp_pcb = tcp_tmp_pcb->next) { \
                                LWIP_ASSERT("TCP_REG: already registered\n", tcp_tmp_pcb != (npcb)); \
                            } \
                            LWIP_ASSERT("TCP_REG: pcb->state != CLOSED", ((pcbs) == &tcp_bound_pcbs) || ((npcb)->state != CLOSED)); \
                            (npcb)->next = *(pcbs); \
                            LWIP_ASSERT("TCP_REG: npcb->next != npcb", (npcb)->next != (npcb)); \
                            *(pcbs) = (npcb); \
                            LWIP_ASSERT("TCP_REG: tcp_pcbs sane", tcp_pcbs_sane()); \
              tcp_timer_needed(); \
                            } while(0)
#define TCP_RMV(pcbs, npcb) do { \
                            struct tcp_pcb *tcp_tmp_pcb; \
                            LWIP_ASSERT("TCP_RMV: pcbs != NULL", *(pcbs) != NULL); \
                            LWIP_DEBUGF(TCP_DEBUG, ("TCP_RMV: removing %p from %p\n", (void *)(npcb), (void *)(*(pcbs)))); \
                            if(*(pcbs) == (npcb)) { \
                               *(pcbs) = (*pcbs)->next; \
                            } else for (tcp_tmp_pcb = *(pcbs); tcp_tmp_pcb != NULL; tcp_tmp_pcb = tcp_tmp_pcb->next) { \
                               if(tcp_tmp_pcb->next == (npcb)) { \
                                  tcp_tmp_pcb->next = (npcb)->next; \
                                  break; \
                               } \
                            } \
                            (npcb)->next = NULL; \
                            LWIP_ASSERT("TCP_RMV: tcp_pcbs sane", tcp_pcbs_sane()); \
                            LWIP_DEBUGF(TCP_DEBUG, ("TCP_RMV: removed %p from %p\n", (void *)(npcb), (void *)(*(pcbs)))); \
                            } while(0)

#else /* LWIP_DEBUG */

#define TCP_REG(pcbs, npcb)                        \
  do {                                             \
    (npcb)->next = *pcbs;                          \
    *(pcbs) = (npcb);                              \
    tcp_timer_needed();                            \
  } while (0)

#define TCP_RMV(pcbs, npcb)                        \
  do {                                             \
    if(*(pcbs) == (npcb)) {                        \
      (*(pcbs)) = (*pcbs)->next;                   \
    }                                              \
    else {                                         \
      struct tcp_pcb *tcp_tmp_pcb;                 \
      for (tcp_tmp_pcb = *pcbs;                    \
          tcp_tmp_pcb != NULL;                     \
          tcp_tmp_pcb = tcp_tmp_pcb->next) {       \
        if(tcp_tmp_pcb->next == (npcb)) {          \
          tcp_tmp_pcb->next = (npcb)->next;        \
          break;                                   \
        }                                          \
      }                                            \
    }                                              \
    (npcb)->next = NULL;                           \
  } while(0)

#endif /* LWIP_DEBUG */

#define TCP_REG_ACTIVE(npcb)                       \
  do {                                             \
    TCP_REG(&tcp_active_pcbs, npcb);               \
    tcp_active_pcbs_changed = 1;                   \
  } while (0)

#define TCP_RMV_ACTIVE(npcb)                       \
  do {                                             \
    TCP_RMV(&tcp_active_pcbs, npcb);               \
    tcp_active_pcbs_changed = 1;                   \
  } while (0)

#define TCP_PCB_REMOVE_ACTIVE(pcb)                 \
  do {                                             \
    tcp_pcb_remove(&tcp_active_pcbs, pcb);         \
    tcp_active_pcbs_changed = 1;                   \
  } while (0)


/* 内部功能：*/
struct tcp_pcb *tcp_pcb_copy(struct tcp_pcb *pcb);
void tcp_pcb_purge(struct tcp_pcb *pcb);
void tcp_pcb_remove(struct tcp_pcb **pcblist, struct tcp_pcb *pcb);

void tcp_segs_free(struct tcp_seg *seg);
void tcp_seg_free(struct tcp_seg *seg);
struct tcp_seg *tcp_seg_copy(struct tcp_seg *seg);

#define tcp_ack(pcb)                               \
  do {                                             \
    if((pcb)->flags & TF_ACK_DELAY) {              \
      tcp_clear_flags(pcb, TF_ACK_DELAY);          \
      tcp_ack_now(pcb);                            \
    }                                              \
    else {                                         \
      tcp_set_flags(pcb, TF_ACK_DELAY);            \
    }                                              \
  } while (0)

#define tcp_ack_now(pcb)                           \
  tcp_set_flags(pcb, TF_ACK_NOW)

err_t tcp_send_fin(struct tcp_pcb *pcb);
err_t tcp_enqueue_flags(struct tcp_pcb *pcb, u8_t flags);

void tcp_rexmit_seg(struct tcp_pcb *pcb, struct tcp_seg *seg);

void tcp_rst(const struct tcp_pcb* pcb, u32_t seqno, u32_t ackno,
       const ip_addr_t *local_ip, const ip_addr_t *remote_ip,
       u16_t local_port, u16_t remote_port);

u32_t tcp_next_iss(struct tcp_pcb *pcb);

err_t tcp_keepalive(struct tcp_pcb *pcb);
err_t tcp_split_unsent_seg(struct tcp_pcb *pcb, u16_t split);
err_t tcp_zero_window_probe(struct tcp_pcb *pcb);
void  tcp_trigger_input_pcb_close(void);

#if TCP_CALCULATE_EFF_SEND_MSS
u16_t tcp_eff_send_mss_netif(u16_t sendmss, struct netif *outif,
                             const ip_addr_t *dest);
#define tcp_eff_send_mss(sendmss, src, dest) \
    tcp_eff_send_mss_netif(sendmss, ip_route(src, dest), dest)
#endif /* TCP_CALCULATE_EFF_SEND_MSS */

#if LWIP_CALLBACK_API
err_t tcp_recv_null(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);
#endif /* LWIP_CALLBACK_API */

#if TCP_DEBUG || TCP_INPUT_DEBUG || TCP_OUTPUT_DEBUG
void tcp_debug_print(struct tcp_hdr *tcphdr);
void tcp_debug_print_flags(u8_t flags);
void tcp_debug_print_state(enum tcp_state s);
void tcp_debug_print_pcbs(void);
s16_t tcp_pcbs_sane(void);
#else
#  define tcp_debug_print(tcphdr)
#  define tcp_debug_print_flags(flags)
#  define tcp_debug_print_state(s)
#  define tcp_debug_print_pcbs()
#  define tcp_pcbs_sane() 1
#endif /* TCP_DEBUG */

/**外部函数（在timer.c中实现），当TCP检测到需要计时器时调用（即找到活动或时间等待pcb）。*/
void tcp_timer_needed(void);

void tcp_netif_ip_addr_changed(const ip_addr_t* old_addr, const ip_addr_t* new_addr);

#if TCP_QUEUE_OOSEQ
void tcp_free_ooseq(struct tcp_pcb *pcb);
#endif

#if LWIP_TCP_PCB_NUM_EXT_ARGS
err_t tcp_ext_arg_invoke_callbacks_passive_open(struct tcp_pcb_listen *lpcb, struct tcp_pcb *cpcb);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_TCP */

#endif /* LWIP_HDR_TCP_PRIV_H */

