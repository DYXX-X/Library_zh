/*
 * eap。h-PPP的可扩展认证协议（RFC 2284）
 *
 * 版权所有（c）2001 Sun Microsystems，Inc.保留所有权利。
 *
 * 特此授予全部或部分以源代码和二进制形式重新分发、修改、翻译和使用本软件的非排他性权利，前提是上述版权声明以任何源代码形式复制，且版权持有人或作者的姓名均不得用于背书或推广本软件衍生的产品。
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * James Carlson原创
 *
 * $Id:eap。h、 v 1.2 2003/06/11 23:56:26 paulus展览$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && EAP_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef PPP_EAP_H
#define	PPP_EAP_H

#include "ppp.h"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * 数据包标头=代码、id、长度。
 */
#define	EAP_HEADERLEN	4


/* EAP消息代码。*/
#define	EAP_REQUEST	1
#define	EAP_RESPONSE	2
#define	EAP_SUCCESS	3
#define	EAP_FAILURE	4

/* EAP类型*/
#define	EAPT_IDENTITY		1
#define	EAPT_NOTIFICATION	2
#define	EAPT_NAK		3	/* （仅响应）*/
#define	EAPT_MD5CHAP		4
#define	EAPT_OTP		5	/* 一次性密码；1938年*/
#define	EAPT_TOKEN		6	/* 通用令牌卡*/
/* 7和8未分配。*/
#define	EAPT_RSA		9	/* RSA公钥身份验证*/
#define	EAPT_DSS		10	/* DSS单边*/
#define	EAPT_KEA		11	/* KEA */
#define	EAPT_KEA_VALIDATE	12	/* KEA-VALIDATE	*/
#define	EAPT_TLS		13	/* EAP-TLS */
#define	EAPT_DEFENDER		14	/* Defender令牌（AXENT）*/
#define	EAPT_W2K		15	/* Windows 2000 EAP*/
#define	EAPT_ARCOT		16	/* Arcot系统*/
#define	EAPT_CISCOWIRELESS	17	/* Cisco无线*/
#define	EAPT_NOKIACARD		18	/* 诺基亚IP智能卡*/
#define	EAPT_SRP		19	/* 安全远程密码*/
/* 20已弃用*/

/* EAP SRP-SHA1子类型*/
#define	EAPSRP_CHALLENGE	1	/* 请求1-挑战*/
#define	EAPSRP_CKEY		1	/* 响应1-客户端密钥*/
#define	EAPSRP_SKEY		2	/* 请求2-服务器密钥*/
#define	EAPSRP_CVALIDATOR	2	/* 响应2-客户端验证程序*/
#define	EAPSRP_SVALIDATOR	3	/* 请求3-服务器验证程序*/
#define	EAPSRP_ACK		3	/* 响应3-最终确认*/
#define	EAPSRP_LWRECHALLENGE	4	/* 要求/要求4-轻量化再充电*/

#define	SRPVAL_EBIT	0x00000001	/* 为ECP使用共享密钥*/

#define	SRP_PSEUDO_ID	"pseudo_"
#define	SRP_PSEUDO_LEN	7

#define MD5_SIGNATURE_SIZE	16
#define EAP_MIN_CHALLENGE_LENGTH	17
#define EAP_MAX_CHALLENGE_LENGTH	24
#define EAP_MIN_MAX_POWER_OF_TWO_CHALLENGE_LENGTH     3   /* 2^3-1 = 7, 17+7 = 24 */

#define	EAP_STATES	\
	"Initial", "Pending", "Closed", "Listen", "Identify", \
	"SRP1", "SRP2", "SRP3", "MD5Chall", "Open", "SRP4", "BadAuth"

#define	eap_client_active(pcb)	((pcb)->eap.es_client.ea_state == eapListen)
#if PPP_SERVER
#define	eap_server_active(pcb)	\
	((pcb)->eap.es_server.ea_state >= eapIdentify && \
	 (pcb)->eap.es_server.ea_state <= eapMD5Chall)
#endif /* PPP_SERVER */

/*
 * 一个PPP会话的完整EAP状态。
 */
enum eap_state_code {
	eapInitial = 0,	/* 尚未请求EAP身份验证*/
	eapPending,	/* 等待LCP（无计时器）*/
	eapClosed,	/* 身份验证未使用*/
	eapListen,	/* 客户端就绪（计时器正在运行）*/
	eapIdentify,	/* EAP标识已发送*/
	eapSRP1,	/* 发送EAP SRP-SHA1子类型1*/
	eapSRP2,	/* 发送EAP SRP-SHA1子类型2*/
	eapSRP3,	/* 发送EAP SRP-SHA1子类型3*/
	eapMD5Chall,	/* 已发送MD5质询*/
	eapOpen,	/* 已完成身份验证*/
	eapSRP4,	/* 发送EAP SRP-SHA1子类型4*/
	eapBadAuth	/* 身份验证失败*/
};

struct eap_auth {
	const char *ea_name;	/* 我们的名字*/
	char ea_peer[MAXNAMELEN +1];	/* 同行姓名*/
	void *ea_session;	/* 身份验证库链接*/
	u_char *ea_skey;	/* 共享加密密钥*/
	u_short ea_namelen;	/* 我们姓名的长度*/
	u_short ea_peerlen;	/* 同行姓名的长度*/
	enum eap_state_code ea_state;
	u_char ea_id;		/* 当前id*/
	u_char ea_requests;	/* 发送/接收的请求数*/
	u_char ea_responses;	/* 响应的数量*/
	u_char ea_type;		/* EAPT_*之一*/
	u32_t ea_keyflags;	/* SRP共享密钥使用标志*/
};

#ifndef EAP_MAX_CHALLENGE_LENGTH
#define EAP_MAX_CHALLENGE_LENGTH	24
#endif
typedef struct eap_state {
	struct eap_auth es_client;	/* 客户端（被认证者）数据*/
#if PPP_SERVER
	struct eap_auth es_server;	/* 服务器（验证器）数据*/
#endif /* PPP_SERVER */
	int es_savedtime;		/* 保存的超时*/
	int es_rechallenge;		/* EAP再激发间隔*/
	int es_lwrechallenge;		/* SRP轻量级再挑战inter*/
	u8_t es_usepseudo;		/* 使用SRP假名（如果提供）*/
	int es_usedpseudo;		/* 设置是否已发送PN*/
	int es_challen;			/* 挑战字符串的长度*/
	u_char es_challenge[EAP_MAX_CHALLENGE_LENGTH];
} eap_state;

/*
 * 超时。
 */
#if 0 /* 移动到ppp_opts。小时*/
#define	EAP_DEFTIMEOUT		3	/* rexmit超时（秒）*/
#define	EAP_DEFTRANSMITS	10	/* 最大发送次数*/
#define	EAP_DEFREQTIME		20	/* 等待对等请求的时间*/
#define	EAP_DEFALLOWREQ		20	/* 接受请求的最大次数*/
#endif /* 移动到ppp_opts.h*/

void eap_authwithpeer(ppp_pcb *pcb, const char *localname);
void eap_authpeer(ppp_pcb *pcb, const char *localname);

extern const struct protent eap_protent;

#ifdef	__cplusplus
}
#endif

#endif /* PPP_EAP_H */

#endif /* PPP_SUPPORT && EAP_SUPPORT */

