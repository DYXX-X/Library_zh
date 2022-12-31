/*****************************************************************************
* 第页。h-网络点对点协议头文件。
*
* 版权所有（c）2003 Marc Boucher，Services Informatiques（MBSI）inc.parts版权所有（c）1997 Global Election Systems inc。
*
* 作者特此授予出于任何目的使用、复制、修改、分发和许可本软件及其文档的权利，前提是所有副本中保留现有版权声明，并且本声明和以下免责声明均包含在任何分发中。任何授权用途都不需要书面协议、许可证或版税。
*
* THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS *AS IS* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************** REVISION HISTORY
*
* 03-01-01马克·鲍彻<marc@mbsi.ca>移植到lwIP。
* 97-11-05 Guy Lancaster <glanca@gesn.com>, Global Election Systems Inc.源于BSD代码。
*****************************************************************************/

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef PPP_H
#define PPP_H

#include "lwip/def.h"
#include "lwip/stats.h"
#include "lwip/mem.h"
#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#if PPP_IPV6_SUPPORT
#include "lwip/ip6_addr.h"
#endif /* PPP_IPV6_SUPPORT */

#ifdef __cplusplus
extern "C" {
#endif

/* 禁用不工作或很少使用的PPP功能，这样我们就不想让PPP_opts膨胀。和他们在一起*/
#ifndef PPP_OPTIONS
#define PPP_OPTIONS         0
#endif

#ifndef PPP_NOTIFY
#define PPP_NOTIFY          0
#endif

#ifndef PPP_REMOTENAME
#define PPP_REMOTENAME      0
#endif

#ifndef PPP_IDLETIMELIMIT
#define PPP_IDLETIMELIMIT   0
#endif

#ifndef PPP_LCP_ADAPTIVE
#define PPP_LCP_ADAPTIVE    0
#endif

#ifndef PPP_MAXCONNECT
#define PPP_MAXCONNECT      0
#endif

#ifndef PPP_ALLOWED_ADDRS
#define PPP_ALLOWED_ADDRS   0
#endif

#ifndef PPP_PROTOCOLNAME
#define PPP_PROTOCOLNAME    0
#endif

#ifndef PPP_STATS_SUPPORT
#define PPP_STATS_SUPPORT   0
#endif

#ifndef DEFLATE_SUPPORT
#define DEFLATE_SUPPORT     0
#endif

#ifndef BSDCOMPRESS_SUPPORT
#define BSDCOMPRESS_SUPPORT 0
#endif

#ifndef PREDICTOR_SUPPORT
#define PREDICTOR_SUPPORT   0
#endif

/*************************
*** PUBLIC DEFINITIONS ***
*************************/

/*
 * 基本PPP框架。
 */
#define PPP_HDRLEN	4	/* 标准ppp标头的八位字节*/
#define PPP_FCSLEN	2	/* FCS的八位字节*/

/*
 * 相位值。
 */
#define PPP_PHASE_DEAD          0
#define PPP_PHASE_MASTER        1
#define PPP_PHASE_HOLDOFF       2
#define PPP_PHASE_INITIALIZE    3
#define PPP_PHASE_SERIALCONN    4
#define PPP_PHASE_DORMANT       5
#define PPP_PHASE_ESTABLISH     6
#define PPP_PHASE_AUTHENTICATE  7
#define PPP_PHASE_CALLBACK      8
#define PPP_PHASE_NETWORK       9
#define PPP_PHASE_RUNNING       10
#define PPP_PHASE_TERMINATE     11
#define PPP_PHASE_DISCONNECT    12

/* 错误代码。*/
#define PPPERR_NONE         0  /* 没有错误。*/
#define PPPERR_PARAM        1  /* 无效参数。*/
#define PPPERR_OPEN         2  /* 无法打开PPP会话。*/
#define PPPERR_DEVICE       3  /* PPP的I/O设备无效。*/
#define PPPERR_ALLOC        4  /* 无法分配资源。*/
#define PPPERR_USER         5  /* 用户中断。*/
#define PPPERR_CONNECT      6  /* 连接丢失。*/
#define PPPERR_AUTHFAIL     7  /* 身份验证质询失败。*/
#define PPPERR_PROTOCOL     8  /* 未能满足协议。*/
#define PPPERR_PEERDEAD     9  /* 连接超时*/
#define PPPERR_IDLETIMEOUT  10 /* 空闲超时*/
#define PPPERR_CONNECTTIME  11 /* 已达到最大连接时间*/
#define PPPERR_LOOPBACK     12 /* 检测到环回*/

/* 是否完全启用身份验证支持*/
#define PPP_AUTH_SUPPORT (PAP_SUPPORT || CHAP_SUPPORT || EAP_SUPPORT)

/************************
*** PUBLIC DATA TYPES ***
************************/

/*
 * 其他头需要原型的ppp_pcb定义，但ppp_pcb也需要其他头的一些结构定义，我们在这里通过声明ppp_pcb类型，然后通过包含包含ppp_pcb必要结构定义的头来修复依赖循环
 */
typedef struct ppp_pcb_s ppp_pcb;

/* BSD代码的类型定义。*/
#ifndef __u_char_defined
typedef unsigned long  u_long;
typedef unsigned int   u_int;
typedef unsigned short u_short;
typedef unsigned char  u_char;
#endif

#include "fsm.h"
#include "lcp.h"
#if CCP_SUPPORT
#include "ccp.h"
#endif /* CCP_SUPPORT */
#if MPPE_SUPPORT
#include "mppe.h"
#endif /* MPPE_SUPPORT */
#if PPP_IPV4_SUPPORT
#include "ipcp.h"
#endif /* PPP_IPV4_SUPPORT */
#if PPP_IPV6_SUPPORT
#include "ipv6cp.h"
#endif /* PPP_IPV6_SUPPORT */
#if PAP_SUPPORT
#include "upap.h"
#endif /* PAP_SUPPORT */
#if CHAP_SUPPORT
#include "chap-new.h"
#endif /* CHAP_SUPPORT */
#if EAP_SUPPORT
#include "eap.h"
#endif /* EAP_SUPPORT */
#if VJ_SUPPORT
#include "vj.h"
#endif /* VJ_SUPPORT */

/* 链接状态回调函数原型*/
typedef void (*ppp_link_status_cb_fn)(ppp_pcb *pcb, int err_code, void *ctx);

/*
 * PPP配置。
 */
typedef struct ppp_settings_s {

#if PPP_SERVER && PPP_AUTH_SUPPORT
  unsigned int  auth_required       :1;      /* 需要对等方进行身份验证*/
  unsigned int  null_login          :1;      /* 用户名“”和密码“”是可接受的*/
#endif /* PPP_SERVER && PPP_AUTH_SUPPORT */
#if PPP_REMOTENAME
  unsigned int  explicit_remote     :1;      /* 使用remotename opt指定的remote_name*/
#endif /* PPP_REMOTENAME */
#if PAP_SUPPORT
  unsigned int  refuse_pap          :1;      /* 不要继续身份验证。带PAP*/
#endif /* PAP_SUPPORT */
#if CHAP_SUPPORT
  unsigned int  refuse_chap         :1;      /* 不要继续身份验证。使用CHAP*/
#endif /* CHAP_SUPPORT */
#if MSCHAP_SUPPORT
  unsigned int  refuse_mschap       :1;      /* 不要继续身份验证。使用MS-CHAP*/
  unsigned int  refuse_mschap_v2    :1;      /* 不要继续身份验证。使用MS-CHAPv2*/
#endif /* MSCHAP_SUPPORT */
#if EAP_SUPPORT
  unsigned int  refuse_eap          :1;      /* 不要继续身份验证。使用EAP*/
#endif /* EAP_SUPPORT */
#if LWIP_DNS
  unsigned int  usepeerdns          :1;      /* 询问对等方DNS添加*/
#endif /* LWIP_DNS */
  unsigned int  persist             :1;      /* 持久模式，始终尝试打开连接*/
#if PRINTPKT_SUPPORT
  unsigned int  hide_password       :1;      /* 隐藏转储数据包中的密码*/
#endif /* PRINTPKT_SUPPORT */
  unsigned int  noremoteip          :1;      /* 让他没有IP地址*/
  unsigned int  lax_recv            :1;      /* 接受异步映射中的控制字符*/
  unsigned int  noendpoint          :1;      /* 不发送/接受端点鉴别器*/
#if PPP_LCP_ADAPTIVE
  unsigned int lcp_echo_adaptive    :1;      /* 仅当链接空闲时请求回显*/
#endif /* PPP_LCP_ADAPTIVE */
#if MPPE_SUPPORT
  unsigned int require_mppe         :1;      /* 需要MPPE（Microsoft点对点加密）*/
  unsigned int refuse_mppe_40       :1;      /* 是否允许MPPE 40位模式？*/
  unsigned int refuse_mppe_128      :1;      /* 是否允许MPPE 128位模式？*/
  unsigned int refuse_mppe_stateful :1;      /* 是否允许MPPE有状态模式？*/
#endif /* MPPE_SUPPORT */

  u16_t  listen_time;                 /* 首先侦听的时间（毫秒），等待对等方发送LCP数据包*/

#if PPP_IDLETIMELIMIT
  u16_t  idle_time_limit;             /* 如果闲置了这么多秒，则断开连接*/
#endif /* PPP_IDLETIMELIMIT */
#if PPP_MAXCONNECT
  u32_t  maxconnect;                  /* 最长连接时间（秒）*/
#endif /* PPP_MAXCONNECT */

#if PPP_AUTH_SUPPORT
  /* 身份验证数据*/
  const char  *user;                   /* PAP用户名*/
  const char  *passwd;                 /* PAP密码，CHAP密码*/
#if PPP_REMOTENAME
  char  remote_name[MAXNAMELEN   + 1]; /* 用于身份验证的对等方名称*/
#endif /* PPP_REMOTENAME */

#if PAP_SUPPORT
  u8_t  pap_timeout_time;        /* 身份验证请求再培训超时（秒）。*/
  u8_t  pap_max_transmits;       /* 发送的身份验证请求数*/
#if PPP_SERVER
  u8_t  pap_req_timeout;         /* 等待对等方身份验证请求的时间*/
#endif /* PPP_SERVER */
#endif /* PAP_SUPPPORT */

#if CHAP_SUPPORT
  u8_t  chap_timeout_time;       /* 重发请求超时（秒）*/
  u8_t  chap_max_transmits;      /* 发送挑战的最大次数*/
#if PPP_SERVER
  u8_t  chap_rechallenge_time;   /* 等待对等方身份验证请求的时间*/
#endif /* PPP_SERVER */
#endif /* CHAP_SUPPPORT */

#if EAP_SUPPORT
  u8_t  eap_req_time;            /* 等待时间（重传/失败）*/
  u8_t  eap_allow_req;           /* 允许的最大请求数*/
#if PPP_SERVER
  u8_t  eap_timeout_time;        /* 等待时间（重传/失败）*/
  u8_t  eap_max_transmits;       /* 允许的最大请求数*/
#endif /* PPP_SERVER */
#endif /* EAP_SUPPORT */

#endif /* PPP_AUTH_SUPPORT */

  u8_t  fsm_timeout_time;            /* 超时时间（秒）*/
  u8_t  fsm_max_conf_req_transmits;  /* 最大配置请求传输*/
  u8_t  fsm_max_term_transmits;      /* 最大终止请求传输*/
  u8_t  fsm_max_nak_loops;           /* 允许的最大nak循环数*/

  u8_t  lcp_loopbackfail;     /* 在决定链接被环回之前，我们从对等方收到魔法数字的次数。*/
  u8_t  lcp_echo_interval;    /* LCP回波请求之间的间隔*/
  u8_t  lcp_echo_fails;       /* 对未应答回显请求的容忍度*/

} ppp_settings;

#if PPP_SERVER
struct ppp_addrs {
#if PPP_IPV4_SUPPORT
  ip4_addr_t our_ipaddr, his_ipaddr, netmask;
#if LWIP_DNS
  ip4_addr_t dns1, dns2;
#endif /* LWIP_DNS */
#endif /* PPP_IPV4_SUPPORT */
#if PPP_IPV6_SUPPORT
  ip6_addr_t our6_ipaddr, his6_ipaddr;
#endif /* PPP_IPV6_SUPPORT */
};
#endif /* PPP_SERVER */

/*
 * PPP接口控制块。
 */
struct ppp_pcb_s {
  ppp_settings settings;
  const struct link_callbacks *link_cb;
  void *link_ctx_cb;
  void (*link_status_cb)(ppp_pcb *pcb, int err_code, void *ctx);  /* 状态更改回调*/
#if PPP_NOTIFY_PHASE
  void (*notify_phase_cb)(ppp_pcb *pcb, u8_t phase, void *ctx);   /* 通知阶段回调*/
#endif /* PPP_NOTIFY_PHASE */
  void *ctx_cb;                  /* 回调可选指针*/
  struct netif *netif;           /* PPP接口*/
  u8_t phase;                    /* 链接的位置*/
  u8_t err_code;                 /* 指示接口关闭原因的代码。*/

  /* 旗帜*/
#if PPP_IPV4_SUPPORT
  unsigned int ask_for_local           :1; /* 向同行请求我们的地址*/
  unsigned int ipcp_is_open            :1; /* 尚未调用np_finished（）*/
  unsigned int ipcp_is_up              :1; /* 已调用ipcp_up（）*/
  unsigned int if4_up                  :1; /* IPv4接口启动时为True。*/
#if 0 /* UNUSED - PROXY ARP */
  unsigned int proxy_arp_set           :1; /* 已创建代理arp条目*/
#endif /* UNUSED - PROXY ARP */
#endif /* PPP_IPV4_SUPPORT */
#if PPP_IPV6_SUPPORT
  unsigned int ipv6cp_is_up            :1; /* 已调用ip6cp_up（）*/
  unsigned int if6_up                  :1; /* 当IPv6接口启动时为True。*/
#endif /* PPP_IPV6_SUPPORT */
  unsigned int lcp_echo_timer_running  :1; /* 设置计时器是否正在运行*/
#if VJ_SUPPORT
  unsigned int vj_enabled              :1; /* 指示VJ压缩已启用的标志。*/
#endif /* VJ_SUPPORT */
#if CCP_SUPPORT
  unsigned int ccp_all_rejected        :1; /* 我们拒绝了所有同行的选择*/
#endif /* CCP_SUPPORT */
#if MPPE_SUPPORT
  unsigned int mppe_keys_set           :1; /* MPPE密钥是否已设置？*/
#endif /* MPPE_SUPPORT */

#if PPP_AUTH_SUPPORT
  /* 身份验证数据*/
#if PPP_SERVER && defined(HAVE_MULTILINK)
  char peer_authname[MAXNAMELEN + 1]; /* 同行向我们证明自己的名字。*/
#endif /* PPP_SERVER&&定义（HAVE_MULTILINK）*/
  u16_t auth_pending;        /* 记录哪些身份验证操作尚未完成。*/
  u16_t auth_done;           /* 记录已完成的身份验证操作。*/

#if PAP_SUPPORT
  upap_state upap;           /* PAP数据*/
#endif /* PAP_SUPPORT */

#if CHAP_SUPPORT
  chap_client_state chap_client;  /* CHAP客户端数据*/
#if PPP_SERVER
  chap_server_state chap_server;  /* CHAP服务器数据*/
#endif /* PPP_SERVER */
#endif /* CHAP_SUPPORT */

#if EAP_SUPPORT
  eap_state eap;            /* EAP数据*/
#endif /* EAP_SUPPORT */
#endif /* PPP_AUTH_SUPPORT */

  fsm lcp_fsm;                   /* LCP fsm结构*/
  lcp_options lcp_wantoptions;   /* 我们要请求的选项*/
  lcp_options lcp_gotoptions;    /* 同行认可的选项*/
  lcp_options lcp_allowoptions;  /* 我们允许对等方请求的选项*/
  lcp_options lcp_hisoptions;    /* 我们支持的选项*/
  u16_t peer_mru;                /* 当前协商的对等MRU*/
  u8_t lcp_echos_pending;        /* 未完成的回音消息数*/
  u8_t lcp_echo_number;          /* 下一个回波帧的ID号*/

  u8_t num_np_open;              /* 我们已打开的网络协议数。*/
  u8_t num_np_up;                /* 出现的网络协议数。*/

#if VJ_SUPPORT
  struct vjcompress vj_comp;     /* Van Jacobson压缩头。*/
#endif /* VJ_SUPPORT */

#if CCP_SUPPORT
  fsm ccp_fsm;                   /* CCP fsm结构*/
  ccp_options ccp_wantoptions;   /* 请求对等方使用什么*/
  ccp_options ccp_gotoptions;    /* 同行同意做什么*/
  ccp_options ccp_allowoptions;  /* 我们同意做什么*/
  ccp_options ccp_hisoptions;    /* 我们同意做什么*/
  u8_t ccp_localstate;           /* 本地状态（主要用于处理重置请求和重置确认）。*/
  u8_t ccp_receive_method;       /* 在接收路径上选择的方法*/
  u8_t ccp_transmit_method;      /* 传输路径上选择的方法*/
#if MPPE_SUPPORT
  ppp_mppe_state mppe_comp;      /* MPPE“压缩机”结构*/
  ppp_mppe_state mppe_decomp;    /* MPPE“减压器”结构*/
#endif /* MPPE_SUPPORT */
#endif /* CCP_SUPPORT */

#if PPP_IPV4_SUPPORT
  fsm ipcp_fsm;                   /* IPCP fsm结构*/
  ipcp_options ipcp_wantoptions;  /* 我们要请求的选项*/
  ipcp_options ipcp_gotoptions;   /* 同行认可的选项*/
  ipcp_options ipcp_allowoptions; /* 我们允许对等方请求的选项*/
  ipcp_options ipcp_hisoptions;   /* 我们支持的选项*/
#endif /* PPP_IPV4_SUPPORT */

#if PPP_IPV6_SUPPORT
  fsm ipv6cp_fsm;                     /* IPV6CP fsm结构*/
  ipv6cp_options ipv6cp_wantoptions;  /* 我们要请求的选项*/
  ipv6cp_options ipv6cp_gotoptions;   /* 同行认可的选项*/
  ipv6cp_options ipv6cp_allowoptions; /* 我们允许对等方请求的选项*/
  ipv6cp_options ipv6cp_hisoptions;   /* 我们支持的选项*/
#endif /* PPP_IPV6_SUPPORT */
};

/************************
 *** PUBLIC FUNCTIONS ***
 ************************/

/*
 * 警告：对于多线程环境，所有ppp_set_*函数只能在ppp处于停滞阶段（即断开连接）时调用。
 */

#if PPP_AUTH_SUPPORT
/*
 * 设置PPP身份验证。
 *
 * 警告：使用PPPAUTHTYPE_ANY可能会产生安全后果。RFC 1994规定：
 *
 * 在实践中，在每个PPP服务器内或与之关联，都有一个将“用户”名称与身份验证信息（“机密”）关联起来的数据库。预计不会通过多个方法对特定的命名用户进行身份验证。这将使用户容易受到攻击，这些攻击会从一组（如PAP而非CHAP）中协商最不安全的方法。如果使用了相同的秘密，PAP将透露该秘密，以便稍后与CHAP一起使用。
 *
 * 相反，对于每个用户名，应该有一个用于验证该用户名的方法的指示。如果用户需要在不同的情况下使用不同的身份验证方法，则应使用不同的用户名，每个用户名仅标识一种身份验证方法。
 *
 * 默认值为无身份验证类型、未设置（NULL）用户和密码。
 */
#define PPPAUTHTYPE_NONE      0x00
#define PPPAUTHTYPE_PAP       0x01
#define PPPAUTHTYPE_CHAP      0x02
#define PPPAUTHTYPE_MSCHAP    0x04
#define PPPAUTHTYPE_MSCHAP_V2 0x08
#define PPPAUTHTYPE_EAP       0x10
#define PPPAUTHTYPE_ANY       0xff
void ppp_set_auth(ppp_pcb *pcb, u8_t authtype, const char *user, const char *passwd);

/*
 * 如果设置，则需要对等方进行身份验证。这是PPP服务器支持所必需的。
 *
 * 默认值为false。
 */
#define ppp_set_auth_required(ppp, boolval) (ppp->settings.auth_required = boolval)
#endif /* PPP_AUTH_SUPPORT */

#if PPP_IPV4_SUPPORT
/*
 * 设置PPP接口“我们的”和“他的”IPv4地址。这对于PPP服务器支持来说是非常必要的，但也可以在PPP链路上使用，其中每一方都选择自己的IP地址。
 *
 * 默认值为未设置（0.0.0.0）。
 */
#define ppp_set_ipcp_ouraddr(ppp, addr) do { ppp->ipcp_wantoptions.ouraddr = ip4_addr_get_u32(addr); \
                                             ppp->ask_for_local = ppp->ipcp_wantoptions.ouraddr != 0; } while(0)
#define ppp_set_ipcp_hisaddr(ppp, addr) (ppp->ipcp_wantoptions.hisaddr = ip4_addr_get_u32(addr))
#if LWIP_DNS
/*
 * 设置对等方请求时发送的DNS服务器地址。这是PPP服务器支持所必需的。
 *
 * 默认值为未设置（0.0.0.0）。
 */
#define ppp_set_ipcp_dnsaddr(ppp, index, addr) (ppp->ipcp_allowoptions.dnsaddr[index] = ip4_addr_get_u32(addr))

/*
 * 如果已设置，我们将向对等方请求最多2个DNS服务器地址。使用DNS_setserver（）函数注册接收的DNS服务器地址。
 *
 * 默认值为false。
 */
#define ppp_set_usepeerdns(ppp, boolval) (ppp->settings.usepeerdns = boolval)
#endif /* LWIP_DNS */
#endif /* PPP_IPV4_SUPPORT */

#if MPPE_SUPPORT
/* 禁用MPPE（Microsoft点对点加密）。此参数是互斥的。*/
#define PPP_MPPE_DISABLE           0x00
/* 需要使用MPPE（Microsoft点对点加密）。*/
#define PPP_MPPE_ENABLE            0x01
/* 允许MPPE使用有状态模式。仍先尝试无状态模式。*/
#define PPP_MPPE_ALLOW_STATEFUL    0x02
/* 拒绝使用40位加密的MPPE。与PPP_MPPE_REFUSE_128冲突。*/
#define PPP_MPPE_REFUSE_40         0x04
/* 拒绝使用128位加密的MPPE。与PPP_MPPE_REFUSE_40冲突。*/
#define PPP_MPPE_REFUSE_128        0x08
/*
 * 设置MPPE配置
 *
 * 默认设置已禁用。
 */
void ppp_set_mppe(ppp_pcb *pcb, u8_t flags);
#endif /* MPPE_SUPPORT */

/*
 * 等待来自对等端的有效PPP数据包，时间最长为intval毫秒。在这段时间结束时，或者当从对等端接收到有效的PPP数据包时，我们通过发送第一个LCP数据包开始协商。
 *
 * 默认值为0。
 */
#define ppp_set_listen_time(ppp, intval) (ppp->settings.listen_time = intval)

/*
 * 如果设置，我们将尝试启动连接，但如果没有从对等端收到回复，我们将被动等待来自对等端的有效LCP数据包。
 *
 * 默认值为false。
 */
#define ppp_set_passive(ppp, boolval) (ppp->lcp_wantoptions.passive = boolval)

/*
 * 如果设置，则在从对等端接收到有效的LCP数据包之前，我们不会发送LCP数据来启动连接。这就是我们通常所说的服务器模式。
 *
 * 默认值为false。
 */
#define ppp_set_silent(ppp, boolval) (ppp->lcp_wantoptions.silent = boolval)

/*
 * 如果设置，则在接收和发送方向上启用协议字段压缩协商。
 *
 * 默认值为true。
 */
#define ppp_set_neg_pcomp(ppp, boolval) (ppp->lcp_wantoptions.neg_pcompression = \
                                         ppp->lcp_allowoptions.neg_pcompression = boolval)

/*
 * 如果设置，则在接收和发送方向上启用地址/控制压缩。
 *
 * 默认值为true。
 */
#define ppp_set_neg_accomp(ppp, boolval) (ppp->lcp_wantoptions.neg_accompression = \
                                          ppp->lcp_allowoptions.neg_accompression = boolval)

/*
 * 如果已设置，则启用异步映射协商。否则，强制对发送和接收方向的所有控制字符进行转义。
 *
 * 默认值为true。
 */
#define ppp_set_neg_asyncmap(ppp, boolval) (ppp->lcp_wantoptions.neg_asyncmap = \
                                            ppp->lcp_allowoptions.neg_asyncmap = boolval)

/*
 * 此选项为链接的这一端设置异步控制字符映射（ACCM）。ACCM是一组32位，每个ASCII控制字符一个，值从0到31，其中1位表示不应在发送到此系统的PPP数据包中使用相应的控制字符。映射是一个无符号32位整数，其中最低有效位（00000001）表示字符0，最高有效位（80000000）表示字符31。然后我们将要求对等方将这些字符作为2字节转义序列发送。
 *
 * 默认值为0。
 */
#define ppp_set_asyncmap(ppp, intval) (ppp->lcp_wantoptions.asyncmap = intval)

/*
 * 将PPP接口设置为默认网络接口（用于输出未找到特定路由的所有数据包）。
 */
#define ppp_set_default(ppp)         netif_set_default(ppp->netif)

#if PPP_NOTIFY_PHASE
/*
 * 设置PPP通知阶段回调。
 *
 * 这可以用于例如根据PPP会话的当前阶段设置LED模式。
 */
typedef void (*ppp_notify_phase_cb_fn)(ppp_pcb *pcb, u8_t phase, void *ctx);
void ppp_set_notify_phase_callback(ppp_pcb *pcb, ppp_notify_phase_cb_fn notify_phase_cb);
#endif /* PPP_NOTIFY_PHASE */

/*
 * 启动PPP连接。
 *
 * 只有当PPP处于停滞阶段时，才能调用此项。
 *
 * Holdoff是启动连接之前等待的时间（以秒为单位）。
 *
 * 如果此端口连接到调制解调器，则必须在调用此端口之前建立调制解调器连接。
 */
err_t ppp_connect(ppp_pcb *pcb, u16_t holdoff);

#if PPP_SERVER
/*
 * 侦听传入的PPP连接。
 *
 * 只有当PPP处于停滞阶段时，才能调用此项。
 *
 * 如果此端口连接到调制解调器，则必须在调用此端口之前建立调制解调器连接。
 */
err_t ppp_listen(ppp_pcb *pcb);
#endif /* PPP_SERVER */

/*
 * 启动PPP连接的结束。队列中任何未完成的数据包都将被丢弃。
 *
 * 将nocarrier设置为1关闭PPP连接，而不启动关机程序。仍然建议始终使用nocarrier=0，如果链接断开，这将需要更长的时间，但对于PPP状态机来说，这是一个更安全的选择。
 *
 * 成功时返回0，失败时返回错误代码。
 */
err_t ppp_close(ppp_pcb *pcb, u8_t nocarrier);

/*
 * 松开控制块。
 *
 * 只有当PPP处于停滞阶段时，才能调用此项。
 *
 * 如果要终止已建立的ppp会话，必须在之前使用ppp_close（）。
 *
 * 成功时返回0，失败时返回错误代码。
 */
err_t ppp_free(ppp_pcb *pcb);

/*
 * PPP IOCTL命令。
 *
 * 获取向上状态-0表示向下，非零表示向上。参数必须指向int。
 */
#define PPPCTLG_UPSTATUS 0

/*
 * 获取PPP错误代码。参数必须指向int。返回PPPERR_值。
 */
#define PPPCTLG_ERRCODE  1

/*
 * 通过串行获取与PPP关联的fd
 */
#define PPPCTLG_FD       2

/*
 * 获取并设置给定连接的参数。成功时返回0，失败时返回错误代码。
 */
err_t ppp_ioctl(ppp_pcb *pcb, u8_t cmd, void *arg);

/* 获取PPP netif接口*/
#define ppp_netif(ppp)               (ppp->netif)

/* 为所选PPP设备设置lwIP样式的状态回调*/
#define ppp_set_netif_statuscallback(ppp, status_cb)       \
        netif_set_status_callback(ppp->netif, status_cb);

/* 为所选PPP设备设置lwIP样式的链接回调*/
#define ppp_set_netif_linkcallback(ppp, link_cb)           \
        netif_set_link_callback(ppp->netif, link_cb);

#ifdef __cplusplus
}
#endif

#endif /* PPP_H */

#endif /* PPP_SUPPORT */

