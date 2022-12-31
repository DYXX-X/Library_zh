/*****************************************************************************
* 第页。h-网络点对点协议头文件。
*
* 版权所有（c）2003 Marc Boucher，Services Informatiques（MBSI）inc.parts版权所有（c）1997 Global Election Systems inc。
*
* 作者特此授予出于任何目的使用、复制、修改、分发和许可本软件及其文档的权利，前提是所有副本中保留现有版权声明，并且本声明和以下免责声明均包含在任何分发中。任何授权用途都不需要书面协议、许可证或版税。
*
* THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS *AS IS* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************** REVISION HISTORY
*
* 03-01-01马克·鲍彻<marc@mbsi.ca>移植到lwIP。
* 97-11-05 Guy Lancaster <glanca@gesn.com>, Global Election Systems Inc.源于BSD代码。
*****************************************************************************/
#ifndef LWIP_HDR_PPP_IMPL_H
#define LWIP_HDR_PPP_IMPL_H

#include "netif/ppp/ppp_opts.h"

#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifdef PPP_INCLUDE_SETTINGS_HEADER
#include "ppp_settings.h"
#endif

#include <stdio.h> /* 格式*/
#include <stdarg.h>
#include <string.h>
#include <stdlib.h> /* strtol（）*/

#include "lwip/netif.h"
#include "lwip/def.h"
#include "lwip/timeouts.h"

#include "ppp.h"
#include "pppdebug.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 用于控制数据包的内存。
 *
 * PPP_CTRL_PBUF_MAX_SIZE是当我们无法计算在填充缓冲区之前要使用多少内存时分配的内存量。
 */
#if PPP_USE_PBUF_RAM
#define PPP_CTRL_PBUF_TYPE       PBUF_RAM
#define PPP_CTRL_PBUF_MAX_SIZE   512
#else /* PPP_USE_PBUF_RAM */
#define PPP_CTRL_PBUF_TYPE       PBUF_POOL
#define PPP_CTRL_PBUF_MAX_SIZE   PBUF_POOL_BUFSIZE
#endif /* PPP_USE_PBUF_RAM */

/*
 * 基本PPP框架。
 */
#define PPP_ADDRESS(p)	(((u_char *)(p))[0])
#define PPP_CONTROL(p)	(((u_char *)(p))[1])
#define PPP_PROTOCOL(p)	((((u_char *)(p))[2] << 8) + ((u_char *)(p))[3])

/*
 * 有效的八位字节值。
 */
#define	PPP_ALLSTATIONS	0xff	/* 所有电台广播地址*/
#define	PPP_UI		0x03	/* 未编号信息*/
#define	PPP_FLAG	0x7e	/* 标志序列*/
#define	PPP_ESCAPE	0x7d	/* 异步控制逃逸*/
#define	PPP_TRANS	0x20	/* 异步透明度修改器*/

/*
 * 协议字段值。
 */
#define PPP_IP		0x21	/* Internet协议*/
#if 0 /* UNUSED */
#define PPP_AT		0x29	/* AppleTalk协议*/
#define PPP_IPX		0x2b	/* IPX协议*/
#endif /* UNUSED */
#if VJ_SUPPORT
#define	PPP_VJC_COMP	0x2d	/* VJ压缩TCP*/
#define	PPP_VJC_UNCOMP	0x2f	/* VJ未压缩TCP*/
#endif /* VJ_SUPPORT */
#if PPP_IPV6_SUPPORT
#define PPP_IPV6	0x57	/* Internet协议版本6*/
#endif /* PPP_IPV6_SUPPORT */
#if CCP_SUPPORT
#define PPP_COMP	0xfd	/* 压缩数据包*/
#endif /* CCP_SUPPORT */
#define PPP_IPCP	0x8021	/* IP控制协议*/
#if 0 /* UNUSED */
#define PPP_ATCP	0x8029	/* AppleTalk控制协议*/
#define PPP_IPXCP	0x802b	/* IPX控制协议*/
#endif /* UNUSED */
#if PPP_IPV6_SUPPORT
#define PPP_IPV6CP	0x8057	/* IPv6控制协议*/
#endif /* PPP_IPV6_SUPPORT */
#if CCP_SUPPORT
#define PPP_CCP		0x80fd	/* 压缩控制协议*/
#endif /* CCP_SUPPORT */
#if ECP_SUPPORT
#define PPP_ECP		0x8053	/* 加密控制协议*/
#endif /* ECP_SUPPORT */
#define PPP_LCP		0xc021	/* 链路控制协议*/
#if PAP_SUPPORT
#define PPP_PAP		0xc023	/* 密码验证协议*/
#endif /* PAP_SUPPORT */
#if LQR_SUPPORT
#define PPP_LQR		0xc025	/* 链路质量报告协议*/
#endif /* LQR_SUPPORT */
#if CHAP_SUPPORT
#define PPP_CHAP	0xc223	/* 加密握手认证。协议*/
#endif /* CHAP_SUPPORT */
#if CBCP_SUPPORT
#define PPP_CBCP	0xc029	/* 回调控制协议*/
#endif /* CBCP_SUPPORT */
#if EAP_SUPPORT
#define PPP_EAP		0xc227	/* 可扩展身份验证协议*/
#endif /* EAP_SUPPORT */

/*
 * 下面的结构给出了要调用特定较低链接级别协议的过程的地址。
 */
struct link_callbacks {
  /* 启动连接（例如，启动发现阶段）*/
  void (*connect) (ppp_pcb *pcb, void *ctx);
#if PPP_SERVER
  /* 侦听传入连接（被动模式）*/
  void (*listen) (ppp_pcb *pcb, void *ctx);
#endif /* PPP_SERVER */
  /* 结束连接（即启动断开阶段）*/
  void (*disconnect) (ppp_pcb *pcb, void *ctx);
  /* 释放下层协议控制块*/
  err_t (*free) (ppp_pcb *pcb, void *ctx);
  /* 将pbuf写入ppp链接，仅用于ppp函数发送ppp数据包。*/
  err_t (*write)(ppp_pcb *pcb, void *ctx, struct pbuf *p);
  /* 从lwIP核心（IPv4或IPv6）发送数据包*/
  err_t (*netif_output)(ppp_pcb *pcb, void *ctx, struct pbuf *p, u_short protocol);
  /* 配置PPP接口的传输侧特性*/
  void (*send_config)(ppp_pcb *pcb, void *ctx, u32_t accm, int pcomp, int accomp);
  /* 确认PPP接口的接收端特性*/
  void (*recv_config)(ppp_pcb *pcb, void *ctx, u32_t accm, int pcomp, int accomp);
};

/*
 * 如何处理网络协议（NP）数据包。
 */
enum NPmode {
    NPMODE_PASS,		/* 把包裹传递出去*/
    NPMODE_DROP,		/* 默默地放下包裹*/
    NPMODE_ERROR,		/* 返回一个错误*/
    NPMODE_QUEUE		/* 把它存起来以后用。*/
};

/*
 * 统计数字
 */
#if PPP_STATS_SUPPORT
struct pppstat	{
    unsigned int ppp_ibytes;	/* 已接收字节*/
    unsigned int ppp_ipackets;	/* 收到的数据包*/
    unsigned int ppp_ierrors;	/* 接收错误*/
    unsigned int ppp_obytes;	/* 已发送字节*/
    unsigned int ppp_opackets;	/* 发送的数据包*/
    unsigned int ppp_oerrors;	/* 传输错误*/
};

#if VJ_SUPPORT
struct vjstat {
    unsigned int vjs_packets;	/* 出站数据包*/
    unsigned int vjs_compressed; /* 出站压缩数据包*/
    unsigned int vjs_searches;	/* 搜索连接状态*/
    unsigned int vjs_misses;	/* 时报找不到康涅狄格州*/
    unsigned int vjs_uncompressedin; /* 入站未压缩数据包*/
    unsigned int vjs_compressedin; /* 入站压缩数据包*/
    unsigned int vjs_errorin;	/* 入站未知类型数据包*/
    unsigned int vjs_tossed;	/* 由于错误而丢弃的入站数据包*/
};
#endif /* VJ_SUPPORT */

struct ppp_stats {
    struct pppstat p;		/* 基本购买力平价统计*/
#if VJ_SUPPORT
    struct vjstat vj;		/* VJ标头压缩统计信息*/
#endif /* VJ_SUPPORT */
};

#if CCP_SUPPORT
struct compstat {
    unsigned int unc_bytes;	/* 未压缩字节总数*/
    unsigned int unc_packets;	/* 未压缩数据包总数*/
    unsigned int comp_bytes;	/* 压缩字节*/
    unsigned int comp_packets;	/* 压缩数据包*/
    unsigned int inc_bytes;	/* 不可压缩字节*/
    unsigned int inc_packets;	/* 不可压缩包*/
    unsigned int ratio;		/* 最近压缩比<<8*/
};

struct ppp_comp_stats {
    struct compstat c;		/* 数据包压缩统计*/
    struct compstat d;		/* 数据包解压缩统计*/
};
#endif /* CCP_SUPPORT */

#endif /* PPP_STATS_SUPPORT */

#if PPP_IDLETIMELIMIT
/*
 * 以下结构记录自发送或接收最后一个NP数据包以来的时间（秒）。
 */
struct ppp_idle {
    time_t xmit_idle;		/* 自上次发送NP数据包以来的时间*/
    time_t recv_idle;		/* 自上次接收NP数据包以来的时间*/
};
#endif /* PPP_IDLETIMELIMIT */

/* epdisc的值。班*/
#define EPD_NULL	0	/* 空鉴别器，无数据*/
#define EPD_LOCAL	1
#define EPD_IP		2
#define EPD_MAC		3
#define EPD_MAGIC	4
#define EPD_PHONENUM	5

/*
 * 全局变量。
 */
#ifdef HAVE_MULTILINK
extern u8_t	multilink;	/* 启用多链路操作*/
extern u8_t	doing_multilink;
extern u8_t	multilink_master;
extern u8_t	bundle_eof;
extern u8_t	bundle_terminating;
#endif

#ifdef MAXOCTETS
extern unsigned int maxoctets;	     /* 每个会话的最大八位字节数（字节）*/
extern int       maxoctets_dir;      /* 方向：0-输入+输出（默认）1-输入2-输出3-最大（输入、输出）*/
extern int       maxoctets_timeout;  /* 八位字节限制检查超时*/
#define PPP_OCTETS_DIRECTION_SUM        0
#define PPP_OCTETS_DIRECTION_IN         1
#define PPP_OCTETS_DIRECTION_OUT        2
#define PPP_OCTETS_DIRECTION_MAXOVERAL  3
/* 与previos相同，但在RADIUS侧略有不同*/
#define PPP_OCTETS_DIRECTION_MAXSESSION 4
#endif

/* CCP和ECP可能会使用数据输入，请从结构保护中删除此条目以保存一些闪存
 */
#define PPP_DATAINPUT 0

/*
 * 下面的结构给出了为特定协议调用的过程的地址。
 */
struct protent {
    u_short protocol;		/* PPP协议编号*/
    /* 初始化过程*/
    void (*init) (ppp_pcb *pcb);
    /* 处理收到的数据包*/
    void (*input) (ppp_pcb *pcb, u_char *pkt, int len);
    /* 处理接收到的协议拒绝*/
    void (*protrej) (ppp_pcb *pcb);
    /* 下层已上升*/
    void (*lowerup) (ppp_pcb *pcb);
    /* 下层已下降*/
    void (*lowerdown) (ppp_pcb *pcb);
    /* 打开协议*/
    void (*open) (ppp_pcb *pcb);
    /* 关闭协议*/
    void (*close) (ppp_pcb *pcb, const char *reason);
#if PRINTPKT_SUPPORT
    /* 以可读形式打印数据包*/
    int  (*printpkt) (const u_char *pkt, int len,
			  void (*printer) (void *, const char *, ...),
			  void *arg);
#endif /* PRINTPKT_SUPPORT */
#if PPP_DATAINPUT
    /* 处理接收到的数据包*/
    void (*datainput) (ppp_pcb *pcb, u_char *pkt, int len);
#endif /* PPP_DATAINPUT */
#if PRINTPKT_SUPPORT
    const char *name;		/* 协议的文本名称*/
    const char *data_name;	/* 对应数据协议的文本名称*/
#endif /* PRINTPKT_SUPPORT */
#if PPP_OPTIONS
    option_t *options;		/* 命令行选项列表*/
    /* 检查请求的选项，分配默认值*/
    void (*check_options) (void);
#endif /* PPP_OPTIONS */
#if DEMAND_SUPPORT
    /* 配置请求拨号接口*/
    int  (*demand_conf) (int unit);
    /* 说明是否为此pkt打开链接*/
    int  (*active_pkt) (u_char *pkt, int len);
#endif /* DEMAND_SUPPORT */
};

/* 指向受支持协议的指针表*/
extern const struct protent* const protocols[];


/* auth_pending、auth_done的值*/
#if PAP_SUPPORT
#define PAP_WITHPEER	0x1
#define PAP_PEER	0x2
#endif /* PAP_SUPPORT */
#if CHAP_SUPPORT
#define CHAP_WITHPEER	0x4
#define CHAP_PEER	0x8
#endif /* CHAP_SUPPORT */
#if EAP_SUPPORT
#define EAP_WITHPEER	0x10
#define EAP_PEER	0x20
#endif /* EAP_SUPPORT */

/* 仅用于auth_done的值*/
#if CHAP_SUPPORT
#define CHAP_MD5_WITHPEER	0x40
#define CHAP_MD5_PEER		0x80
#if MSCHAP_SUPPORT
#define CHAP_MS_SHIFT		8	/* MS身份验证的LSB位置*/
#define CHAP_MS_WITHPEER	0x100
#define CHAP_MS_PEER		0x200
#define CHAP_MS2_WITHPEER	0x400
#define CHAP_MS2_PEER		0x800
#endif /* MSCHAP_SUPPORT */
#endif /* CHAP_SUPPORT */

/* 支持的CHAP协议*/
#if CHAP_SUPPORT

#if MSCHAP_SUPPORT
#define CHAP_MDTYPE_SUPPORTED (MDTYPE_MICROSOFT_V2 | MDTYPE_MICROSOFT | MDTYPE_MD5)
#else /* MSCHAP_SUPPORT */
#define CHAP_MDTYPE_SUPPORTED (MDTYPE_MD5)
#endif /* MSCHAP_SUPPORT */

#else /* CHAP_SUPPORT */
#define CHAP_MDTYPE_SUPPORTED (MDTYPE_NONE)
#endif /* CHAP_SUPPORT */

#if PPP_STATS_SUPPORT
/*
 * PPP统计结构
 */
struct pppd_stats {
    unsigned int	bytes_in;
    unsigned int	bytes_out;
    unsigned int	pkts_in;
    unsigned int	pkts_out;
};
#endif /* PPP_STATS_SUPPORT */


/*
 * PPP专用功能
 */

 
/*
 * 从lwIP核心调用的函数。
 */

/* 初始化PPP子系统*/
int ppp_init(void);

/*
 * 从PPP链路协议调用的函数。
 */

/* 创建新的PPP控制块*/
ppp_pcb *ppp_new(struct netif *pppif, const struct link_callbacks *callbacks, void *link_ctx_cb,
                 ppp_link_status_cb_fn link_status_cb, void *ctx_cb);

/* 启动LCP打开请求*/
void ppp_start(ppp_pcb *pcb);

/* 当链接设置失败时调用*/
void ppp_link_failed(ppp_pcb *pcb);

/* 当链接正常关闭时调用（即被要求结束）*/
void ppp_link_end(ppp_pcb *pcb);

/* 调用函数处理输入数据包*/
void ppp_input(ppp_pcb *pcb, struct pbuf *pb);


/*
 * PPP协议调用的函数。
 */

/* 所有PPP子系统调用的发送数据包的函数*/
err_t ppp_write(ppp_pcb *pcb, struct pbuf *p);

/* auth调用的函数。c链接_终止（）*/
void ppp_link_terminated(ppp_pcb *pcb);

void new_phase(ppp_pcb *pcb, int p);

int ppp_send_config(ppp_pcb *pcb, int mtu, u32_t accm, int pcomp, int accomp);
int ppp_recv_config(ppp_pcb *pcb, int mru, u32_t accm, int pcomp, int accomp);

#if PPP_IPV4_SUPPORT
int sifaddr(ppp_pcb *pcb, u32_t our_adr, u32_t his_adr, u32_t netmask);
int cifaddr(ppp_pcb *pcb, u32_t our_adr, u32_t his_adr);
#if 0 /* UNUSED - PROXY ARP */
int sifproxyarp(ppp_pcb *pcb, u32_t his_adr);
int cifproxyarp(ppp_pcb *pcb, u32_t his_adr);
#endif /* UNUSED - PROXY ARP */
#if LWIP_DNS
int sdns(ppp_pcb *pcb, u32_t ns1, u32_t ns2);
int cdns(ppp_pcb *pcb, u32_t ns1, u32_t ns2);
#endif /* LWIP_DNS */
#if VJ_SUPPORT
int sifvjcomp(ppp_pcb *pcb, int vjcomp, int cidcomp, int maxcid);
#endif /* VJ_SUPPORT */
int sifup(ppp_pcb *pcb);
int sifdown (ppp_pcb *pcb);
u32_t get_mask(u32_t addr);
#endif /* PPP_IPV4_SUPPORT */

#if PPP_IPV6_SUPPORT
int sif6addr(ppp_pcb *pcb, eui64_t our_eui64, eui64_t his_eui64);
int cif6addr(ppp_pcb *pcb, eui64_t our_eui64, eui64_t his_eui64);
int sif6up(ppp_pcb *pcb);
int sif6down (ppp_pcb *pcb);
#endif /* PPP_IPV6_SUPPORT */

#if DEMAND_SUPPORT
int sifnpmode(ppp_pcb *pcb, int proto, enum NPmode mode);
#endif /* 需求_供应*/

void netif_set_mtu(ppp_pcb *pcb, int mtu);
int netif_get_mtu(ppp_pcb *pcb);

#if CCP_SUPPORT
#if 0 /* 未使用的*/
int ccp_test(ppp_pcb *pcb, u_char *opt_ptr, int opt_len, int for_transmit);
#endif /* 未使用的*/
void ccp_set(ppp_pcb *pcb, u8_t isopen, u8_t isup, u8_t receive_method, u8_t transmit_method);
void ccp_reset_comp(ppp_pcb *pcb);
void ccp_reset_decomp(ppp_pcb *pcb);
#if 0 /* 未使用的*/
int ccp_fatal_error(ppp_pcb *pcb);
#endif /* 未使用的*/
#endif /* CCP_SUPPORT */

#if PPP_IDLETIMELIMIT
int get_idle_time(ppp_pcb *pcb, struct ppp_idle *ip);
#endif /* PPP_IDLETIMELIMIT */

#if DEMAND_SUPPORT
int get_loop_output(void);
#endif /* DEMAND_SUPPORT */

/* 可选的协议名称列表，使我们的消息更具信息性。*/
#if PPP_PROTOCOLNAME
const char * protocol_name(int proto);
#endif /* PPP_PROTOCOLNAME  */

/* 可选统计数据支持，以获取PPP接口上的一些统计数据*/
#if PPP_STATS_SUPPORT
void print_link_stats(void); /* 打印统计数据（如果可用）*/
void reset_link_stats(int u); /* 链接启动时重置（初始化）状态*/
void update_link_stats(int u); /* 获取链接终止时的统计信息*/
#endif /* PPP_STATS_SUPPORT */



/*
 * get/put char/short/long的内联版本。指针提前；我们假设这两个参数都是lvalues，并且已经在寄存器中。cp必须是u_char。
 */
#define GETCHAR(c, cp) { \
	(c) = *(cp)++; \
}
#define PUTCHAR(c, cp) { \
	*(cp)++ = (u_char) (c); \
}
#define GETSHORT(s, cp) { \
	(s) = *(cp)++ << 8; \
	(s) |= *(cp)++; \
}
#define PUTSHORT(s, cp) { \
	*(cp)++ = (u_char) ((s) >> 8); \
	*(cp)++ = (u_char) (s); \
}
#define GETLONG(l, cp) { \
	(l) = *(cp)++ << 8; \
	(l) |= *(cp)++; (l) <<= 8; \
	(l) |= *(cp)++; (l) <<= 8; \
	(l) |= *(cp)++; \
}
#define PUTLONG(l, cp) { \
	*(cp)++ = (u_char) ((l) >> 24); \
	*(cp)++ = (u_char) ((l) >> 16); \
	*(cp)++ = (u_char) ((l) >> 8); \
	*(cp)++ = (u_char) (l); \
}

#define INCPTR(n, cp)	((cp) += (n))
#define DECPTR(n, cp)	((cp) -= (n))

/*
 * 用户级别4.3BSD UNIX实现的系统相关定义。
 */
#define TIMEOUT(f, a, t)        do { sys_untimeout((f), (a)); sys_timeout((t)*1000, (f), (a)); } while(0)
#define TIMEOUTMS(f, a, t)      do { sys_untimeout((f), (a)); sys_timeout((t), (f), (a)); } while(0)
#define UNTIMEOUT(f, a)         sys_untimeout((f), (a))

#define BZERO(s, n)		memset(s, 0, n)
#define	BCMP(s1, s2, l)		memcmp(s1, s2, l)

#define PRINTMSG(m, l)		{ ppp_info("Remote message: %0.*v", l, m); }

/*
 * MAKEHADER-向数据包添加标头字段。
 */
#define MAKEHEADER(p, t) { \
    PUTCHAR(PPP_ALLSTATIONS, p); \
    PUTCHAR(PPP_UI, p); \
    PUTSHORT(t, p); }

/* 从身份验证导出的过程。c*/
void link_required(ppp_pcb *pcb);     /* 我们开始使用链接*/
void link_terminated(ppp_pcb *pcb);   /* 我们完成了链接*/
void link_down(ppp_pcb *pcb);	      /* LCP层已离开“打开”状态*/
void upper_layers_down(ppp_pcb *pcb); /* 关闭所有NCP*/
void link_established(ppp_pcb *pcb);  /* 链接已打开；立即进行身份验证*/
void start_networks(ppp_pcb *pcb);    /* 启动所有网络控制原型*/
void continue_networks(ppp_pcb *pcb); /* 启动网络[ip等]控制协议*/
#if PPP_AUTH_SUPPORT
#if PPP_SERVER
int auth_check_passwd(ppp_pcb *pcb, char *auser, int userlen, char *apasswd, int passwdlen, const char **msg, int *msglen);
                                /* 根据配置检查用户名和密码*/
void auth_peer_fail(ppp_pcb *pcb, int protocol);
				/* 对等方无法验证自身*/
void auth_peer_success(ppp_pcb *pcb, int protocol, int prot_flavor, const char *name, int namelen);
				/* 对等方已成功验证自己*/
#endif /* PPP_SERVER */
void auth_withpeer_fail(ppp_pcb *pcb, int protocol);
				/* 我们未能验证自己*/
void auth_withpeer_success(ppp_pcb *pcb, int protocol, int prot_flavor);
				/* 我们成功地验证了自己*/
#endif /* PPP_AUTH_SUPPORT */
void np_up(ppp_pcb *pcb, int proto);    /* 出现了一种网络协议*/
void np_down(ppp_pcb *pcb, int proto);  /* 网络协议已失效*/
void np_finished(ppp_pcb *pcb, int proto); /* 网络协议不再需要链接*/
#if PPP_AUTH_SUPPORT
int get_secret(ppp_pcb *pcb, const char *client, const char *server, char *secret, int *secret_len, int am_server);
				/* 为小伙子获取“秘密”*/
#endif /* PPP_AUTH_SUPPORT */

/* 从ipcp导出的过程。c*/
/* int parse_dotted_ip（char*，u32_t*）；*/

/* 从需求导出的程序。c*/
#if DEMAND_SUPPORT
void demand_conf (void);	/* 请求拨号的配置接口*/
void demand_block (void);	/* 设置所有NP来排队数据包*/
void demand_unblock (void); /* 设置所有NP以传递数据包*/
void demand_discard (void); /* 将所有NP设置为丢弃数据包*/
void demand_rexmit (int, u32_t); /* 为NP重新发送保存的帧*/
int  loop_chars (unsigned char *, int); /* 处理环回中的字符*/
int  loop_frame (unsigned char *, int); /* 我们应该把链接提出来吗？*/
#endif /* DEMAND_SUPPORT */

/* 从多链接导出的过程。c*/
#ifdef HAVE_MULTILINK
void mp_check_options (void); /* 检查多链接相关选项*/
int  mp_join_bundle (void);  /* 将我们的链接添加到适当的捆绑包*/
void mp_exit_bundle (void);  /* 已断开我们与捆绑包的链接*/
void mp_bundle_terminated (void);
char *epdisc_to_str (struct epdisc *); /* 来自端点描述的字符串。*/
int  str_to_epdisc (struct epdisc *, char *); /* 端部椎间盘。来自str*/
#else
#define mp_bundle_terminated()	/* 没有什么*/
#define mp_exit_bundle()	/* 没有什么*/
#define doing_multilink		0
#define multilink_master	0
#endif

/* 从utils.c导出的过程。*/
void ppp_print_string(const u_char *p, int len, void (*printer) (void *, const char *, ...), void *arg);   /* 为输出设置字符串格式*/
int ppp_slprintf(char *buf, int buflen, const char *fmt, ...);            /* 冲刺++*/
int ppp_vslprintf(char *buf, int buflen, const char *fmt, va_list args);  /* vsprintf++*/
size_t ppp_strlcpy(char *dest, const char *src, size_t len);        /* 安全结构*/
size_t ppp_strlcat(char *dest, const char *src, size_t len);        /* 安全字符串*/
void ppp_dbglog(const char *fmt, ...);    /* 记录调试消息*/
void ppp_info(const char *fmt, ...);      /* 记录信息性消息*/
void ppp_notice(const char *fmt, ...);    /* 记录通知级别消息*/
void ppp_warn(const char *fmt, ...);      /* 记录警告消息*/
void ppp_error(const char *fmt, ...);     /* 记录错误消息*/
void ppp_fatal(const char *fmt, ...);     /* 记录错误消息并死亡（1）*/
#if PRINTPKT_SUPPORT
void ppp_dump_packet(ppp_pcb *pcb, const char *tag, unsigned char *p, int len);
                                /* 如果感兴趣，将数据包转储到调试日志*/
#endif /* PRINTPKT_SUPPORT */

/*
 * 必要的计时器分析数量。
 *
 * PPP每个协议至少使用一个定时器，但并非所有协议都同时处于活动状态，因此所需超时的数量实际上低于启用的协议。以下是基于代码分析的实际必要超时。
 *
 * 请注意，这里分析的许多功能根本不起作用，只是为了对必要的计时器进行全面分析，以防止每次添加功能时都必须重做。
 *
 * 计时器列表
 *
 * |延迟超时|低级别协议超时（PPPoE或PPPoL2P）|LCP延迟UP |LCP重传（FSM）|LCPEcho计时器。|PAP或CHAP或EAP身份验证。|ECP重传，FSM）。|MPPE启用时，CCP重传（FEM）。| MPPE未启用时，CP重传（TDM）。.|CCP机架超时…PPP_PHASE_DEAD PPP_PHASE _HOLDOFF |…PPP_ PHASE _INITIALIZE |…PPP PHASE _ESTABLISH |…|…|。PPP_PHASE_AUTHENTICATE|..||..PPP_PHASE.NETWORK|||..|||.pppp_PHASE_RUNNING|.||||||.|||| PPP_phaser_TERMINATE|.||| PPP-PHASE_NETWORK|。PPP_PHASE_ESTABLISH PPP_PHASE-DISCONNECT PPP_PHASE.DEAD
 *
 * 好的，PPP基本重传和LCP Echo消耗一个定时器。1.
 *
 * 如果启用了身份验证，则在身份验证期间需要一个计时器。1+PPP_AUTH_SUPPORT
 *
 * 如果启用了ECP，则在IPCP和/或IP6CP之前需要一个计时器，如果启用了CCP，则需要另一个计时器（仅支持MPPE，但我们不太关心此详细级别）。1+ECP_SUPPORT+CCP_SUPPORT
 *
 * 如果启用CCP，它可能会在IPCP或IP6CP期间消耗计时器，因此我们可能会同时使用IPCP、IP6CP和CCP计时器。1+PPP_IPV4_SUPPORT+PPP_IPV6_SUPPORT+CCP_SUPPORT
 *
 * 进入运行阶段时，IPCP或IP6CP仍在运行。如果启用了空闲时间限制，则需要一个计时器。对于最大连接时间和最大八位字节功能也是如此。此外，CCP RACK可用于超过此点。1+PPP_IPV4_SUPPORT+PPP_IPV6_SUPPORT-1+PPP_IDLETIMELIMIT+PPP_MAXCONNECT+MAXOCTETS+CCP_SUPPORT
 *
 * 必须启用IPv4或IPv6，因此我们不需要考虑身份验证和CCP+ECP情况，从而降低总体复杂性。1+LWIP_MAX（PPP_IPV4_SUPPORT+PPP_IPV6_SUPPORT+CCP_SUPPORT，PPP_IPV4_SUPPORT+PPP_ipv26_SUPPORT-1+PPP_IDLETIMELIMIT+PPP_MAXCONNECT+MAXOCTETS+CCP_upport）
 *
 * 我们不支持PPP_IDLETIMELIMIT+PPP_MAXCONNECT+MAXOCETS功能，也不支持将这些定义添加到PPP_opts。h仅仅因为总是将值定义为0是不值得的。1+LWIP_MAX（PPP_IPV4_SUPPORT+PPP_IPV6_SUPPORT+CCP_SUPPORT，PPP_IPV4_SUPPORT+PPP_IPV6 _SUPPORT-1+CCP_upport）
 *
 * 因此，以下内容就足够了。1+PPP_IPV4_SUPPORT+PPP_IPV6_SUPPORT+CCP_SUPPORT
 */

#ifdef __cplusplus
}
#endif

#endif /* PPP_SUPPORT */
#endif /* LWIP_HDR_PPP_IMPL_H */

