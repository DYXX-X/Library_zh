/**
 * @file 第2层隧道协议上的网络点对点协议头文件。
 *
 */

/*
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PPPOL2TP_SUPPORT /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#ifndef PPPOL2TP_H
#define PPPOL2TP_H

#include "ppp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 超时*/
#define PPPOL2TP_CONTROL_TIMEOUT         (5*1000)  /* 快速超时计算的基础*/
#define PPPOL2TP_SLOW_RETRY              (60*1000) /* 持续重试间隔*/

#define PPPOL2TP_MAXSCCRQ                4         /* 重试SCCRQ四次（快速）*/
#define PPPOL2TP_MAXICRQ                 4         /* 重试IRCQ四次*/
#define PPPOL2TP_MAXICCN                 4         /* 重试ICCN四次*/

/* L2TP标头标志*/
#define PPPOL2TP_HEADERFLAG_CONTROL      0x8000
#define PPPOL2TP_HEADERFLAG_LENGTH       0x4000
#define PPPOL2TP_HEADERFLAG_SEQUENCE     0x0800
#define PPPOL2TP_HEADERFLAG_OFFSET       0x0200
#define PPPOL2TP_HEADERFLAG_PRIORITY     0x0100
#define PPPOL2TP_HEADERFLAG_VERSION      0x0002

/* 控制的强制位：控制、长度、序列、版本2*/
#define PPPOL2TP_HEADERFLAG_CONTROL_MANDATORY     (PPPOL2TP_HEADERFLAG_CONTROL|PPPOL2TP_HEADERFLAG_LENGTH|PPPOL2TP_HEADERFLAG_SEQUENCE|PPPOL2TP_HEADERFLAG_VERSION)
/* 禁止控制位：偏移、优先级*/
#define PPPOL2TP_HEADERFLAG_CONTROL_FORBIDDEN     (PPPOL2TP_HEADERFLAG_OFFSET|PPPOL2TP_HEADERFLAG_PRIORITY)

/* 数据的强制位：版本2*/
#define PPPOL2TP_HEADERFLAG_DATA_MANDATORY        (PPPOL2TP_HEADERFLAG_VERSION)

/* AVP（属性值对）标头*/
#define PPPOL2TP_AVPHEADERFLAG_MANDATORY  0x8000
#define PPPOL2TP_AVPHEADERFLAG_HIDDEN     0x4000
#define PPPOL2TP_AVPHEADERFLAG_LENGTHMASK 0x03ff

/* --AVP-消息类型*/
#define PPPOL2TP_AVPTYPE_MESSAGE      0 /* 消息类型*/

/* 控制连接管理*/
#define PPPOL2TP_MESSAGETYPE_SCCRQ    1 /* 启动控制连接请求*/
#define PPPOL2TP_MESSAGETYPE_SCCRP    2 /* 启动控制连接回复*/
#define PPPOL2TP_MESSAGETYPE_SCCCN    3 /* 启动控制连接已连接*/
#define PPPOL2TP_MESSAGETYPE_STOPCCN  4 /* 停止控制连接通知*/
#define PPPOL2TP_MESSAGETYPE_HELLO    6 /* 你好*/
/* 呼叫管理*/
#define PPPOL2TP_MESSAGETYPE_OCRQ     7 /* 传出呼叫请求*/
#define PPPOL2TP_MESSAGETYPE_OCRP     8 /* 呼出呼叫回复*/
#define PPPOL2TP_MESSAGETYPE_OCCN     9 /* 已连接传出呼叫*/
#define PPPOL2TP_MESSAGETYPE_ICRQ    10 /* 传入呼叫请求*/
#define PPPOL2TP_MESSAGETYPE_ICRP    11 /* 来电回复*/
#define PPPOL2TP_MESSAGETYPE_ICCN    12 /* 传入呼叫已连接*/
#define PPPOL2TP_MESSAGETYPE_CDN     14 /* 呼叫断开通知*/
/* 错误报告*/
#define PPPOL2TP_MESSAGETYPE_WEN     15 /* WAN错误通知*/
/* PPP会话控制*/
#define PPPOL2TP_MESSAGETYPE_SLI     16 /* 设置链接信息*/

/* --AVP-结果代码*/
#define PPPOL2TP_AVPTYPE_RESULTCODE   1 /* 结果代码*/
#define PPPOL2TP_RESULTCODE           1 /* 清除控制连接的一般请求*/

/* --AVP-协议版本（！=L2TP标头版本）*/
#define PPPOL2TP_AVPTYPE_VERSION      2
#define PPPOL2TP_VERSION         0x0100 /* L2TP协议版本1，修订版0*/

/* --AVP-框架功能*/
#define PPPOL2TP_AVPTYPE_FRAMINGCAPABILITIES           3 /* 承载能力*/
#define PPPOL2TP_FRAMINGCAPABILITIES          0x00000003 /* 异步+同步帧*/

/* --AVP-承载能力*/
#define PPPOL2TP_AVPTYPE_BEARERCAPABILITIES           4 /* 承载能力*/
#define PPPOL2TP_BEARERCAPABILITIES          0x00000003 /* 模拟+数字访问*/

/* --AVP-断路器*/
#define PPPOL2TP_AVPTYPE_TIEBREAKER   5

/* --AVP-主机名*/
#define PPPOL2TP_AVPTYPE_HOSTNAME     7 /* 主机名*/
#define PPPOL2TP_HOSTNAME        "lwIP" /* FIXME：使其可配置*/

/* --AVP-供应商名称*/
#define PPPOL2TP_AVPTYPE_VENDORNAME   8 /* 供应商名称*/
#define PPPOL2TP_VENDORNAME      "lwIP" /* FIXME：使其可配置*/

/* --AVP-分配隧道ID*/
#define PPPOL2TP_AVPTYPE_TUNNELID     9 /* 分配隧道ID*/

/* --AVP-接收窗口大小*/
#define PPPOL2TP_AVPTYPE_RECEIVEWINDOWSIZE  10 /* 接收窗口大小*/
#define PPPOL2TP_RECEIVEWINDOWSIZE           8 /* FIXME：使其可配置*/

/* --AVP-挑战*/
#define PPPOL2TP_AVPTYPE_CHALLENGE   11 /* 挑战*/

/* --AVP-原因代码*/
#define PPPOL2TP_AVPTYPE_CAUSECODE   12 /* 原因代码*/

/* --AVP-挑战响应*/
#define PPPOL2TP_AVPTYPE_CHALLENGERESPONSE   13 /* 挑战响应*/
#define PPPOL2TP_AVPTYPE_CHALLENGERESPONSE_SIZE  16

/* --AVP-分配会话ID*/
#define PPPOL2TP_AVPTYPE_SESSIONID   14 /* 分配会话ID*/

/* --AVP-呼叫序列号*/
#define PPPOL2TP_AVPTYPE_CALLSERIALNUMBER   15 /* 呼叫序列号*/

/* --AVP-框架类型*/
#define PPPOL2TP_AVPTYPE_FRAMINGTYPE         19 /* 框架类型*/
#define PPPOL2TP_FRAMINGTYPE         0x00000001 /* 同步帧*/

/* --AVP-TX连接速度*/
#define PPPOL2TP_AVPTYPE_TXCONNECTSPEED      24 /* TX连接速度*/
#define PPPOL2TP_TXCONNECTSPEED       100000000 /* 连接速度：100 Mbit/s*/

/* L2TP会话状态*/
#define PPPOL2TP_STATE_INITIAL     0
#define PPPOL2TP_STATE_SCCRQ_SENT  1
#define PPPOL2TP_STATE_ICRQ_SENT   2
#define PPPOL2TP_STATE_ICCN_SENT   3
#define PPPOL2TP_STATE_DATA        4

#define PPPOL2TP_OUTPUT_DATA_HEADER_LEN   6 /* 我们的数据头长度*/

/*
 * PPPoL2TP接口控制块。
 */
typedef struct pppol2tp_pcb_s pppol2tp_pcb;
struct pppol2tp_pcb_s {
  ppp_pcb *ppp;                /* PPP PCB */
  u8_t phase;                  /* L2TP阶段*/
  struct udp_pcb *udp;         /* UDP L2TP套接字*/
  struct netif *netif;         /* 输出接口，用作默认路由*/
  ip_addr_t remote_ip;         /* LNS IP地址*/
  u16_t remote_port;           /* LNS端口*/
#if PPPOL2TP_AUTH_SUPPORT
  const u8_t *secret;          /* 机密字符串*/
  u8_t secret_len;             /* 机密字符串长度*/
  u8_t secret_rv[16];          /* 随机向量*/
  u8_t challenge_hash[16];     /* 挑战响应*/
  u8_t send_challenge;         /* 布尔值下一个发送的数据包是否应包含质询响应*/
#endif /* PPPOL2TP_AUTH_SUPPORT */

  u16_t tunnel_port;           /* 隧道端口*/
  u16_t our_ns;                /* NS到对等*/
  u16_t peer_nr;               /* 来自对等方的NR*/
  u16_t peer_ns;               /* 预期来自对等端的NS*/
  u16_t source_tunnel_id;      /* 对等方分配的隧道ID*/
  u16_t remote_tunnel_id;      /* 分配给对等方的隧道ID*/
  u16_t source_session_id;     /* 对等方分配的会话ID*/
  u16_t remote_session_id;     /* 分配给对等方的会话ID*/

  u8_t sccrq_retried;          /* 已完成的SCCRQ重试次数*/
  u8_t icrq_retried;           /* 已完成的ICRQ重试次数*/
  u8_t iccn_retried;           /* 已完成的ICCN重试次数*/
};


/* 创建新的L2TP会话。*/
ppp_pcb *pppol2tp_create(struct netif *pppif,
       struct netif *netif, const ip_addr_t *ipaddr, u16_t port,
       const u8_t *secret, u8_t secret_len,
       ppp_link_status_cb_fn link_status_cb, void *ctx_cb);

#ifdef __cplusplus
}
#endif

#endif /* PPPOL2TP_H */
#endif /* PPP_SUPPORT && PPPOL2TP_SUPPORT */

