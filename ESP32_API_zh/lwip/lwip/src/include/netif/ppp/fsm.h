/*
 * fsm。h-{链路，IP}控制协议有限状态机定义。
 *
 * 版权所有（c）1984-2000卡内基梅隆大学。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用“卡耐基梅隆大学”的名称来支持或推广源自本软件的产品。如需获得许可或任何法律详情，请联系卡内基梅隆大学技术转让办公室，地址：宾夕法尼亚州匹兹堡福布斯大道5000号，邮编：15213-3890（412）268-4387，传真：（412）268-7395tech-transfer@andrew.cmu.edu
 *
 * 4.任何形式的再分发都必须保留以下确认：“本产品包括由卡内基梅隆大学计算服务部开发的软件(http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id:fsm。h、 v 1.10 2004/11/13 02:28:15 paulus Exp公司$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef FSM_H
#define	FSM_H

#include "ppp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 数据包标头=代码、id、长度。
 */
#define HEADERLEN	4


/*
 *  CP（LCP、IPCP等）代码。
 */
#define CONFREQ		1	/* 配置请求*/
#define CONFACK		2	/* 配置确认*/
#define CONFNAK		3	/* 配置Nak*/
#define CONFREJ		4	/* 配置拒绝*/
#define TERMREQ		5	/* 终止请求*/
#define TERMACK		6	/* 终止确认*/
#define CODEREJ		7	/* 代码拒绝*/


/*
 * 每个FSM由FSM结构和FSM回调来描述。
 */
typedef struct fsm {
    ppp_pcb *pcb;		/* PPP接口*/
    const struct fsm_callbacks *callbacks;	/* 回调例程*/
    const char *term_reason;	/* 关闭协议的原因*/
    u8_t seen_ack;		/* 已收到请求的有效确认/否定/拒绝*/
				  /* --这是我们唯一的标志，如果我们有更多的标志，我们可以使用u_int:1*/
    u16_t protocol;		/* 数据链路层协议字段值*/
    u8_t state;			/* 状态*/
    u8_t flags;			/* 包含选项位*/
    u8_t id;			/* 当前id*/
    u8_t reqid;			/* 当前请求id*/
    u8_t retransmits;		/* 剩余的重传次数*/
    u8_t nakloops;		/* 自上次确认以来的nak循环数*/
    u8_t rnakloops;		/* 收到的nak数*/
    u8_t maxnakloops;		/* 允许的最大nak循环数（这是必要的，因为IPCP需要自定义的最大nak-loops值）*/
    u8_t term_reason_len;	/* 期限_原因*/
} fsm;


typedef struct fsm_callbacks {
    void (*resetci)		/* 重置我们的配置信息*/
		(fsm *);
    int  (*cilen)		/* 配置信息的长度*/
		(fsm *);
    void (*addci) 		/* 添加我们的配置信息*/
		(fsm *, u_char *, int *);
    int  (*ackci)		/* 确认我们的配置信息*/
		(fsm *, u_char *, int);
    int  (*nakci)		/* NAK我们的配置信息*/
		(fsm *, u_char *, int, int);
    int  (*rejci)		/* 拒绝我们的配置信息*/
		(fsm *, u_char *, int);
    int  (*reqci)		/* 请求对等方的配置信息*/
		(fsm *, u_char *, int *, int);
    void (*up)			/* 当fsm达到PPP_fsm_OPENED状态时调用*/
		(fsm *);
    void (*down)		/* 当fsm离开PPP_fsm_OPENED状态时调用*/
		(fsm *);
    void (*starting)		/* 当我们需要下层时调用*/
		(fsm *);
    void (*finished)		/* 当我们不需要下层时调用*/
		(fsm *);
    void (*protreject)		/* 收到协议拒绝时调用*/
		(int);
    void (*retransmit)		/* 需要重新传输*/
		(fsm *);
    int  (*extcode)		/* 收到未知代码时调用*/
		(fsm *, int, int, u_char *, int);
    const char *proto_name;	/* 协议的字符串名称（用于消息）*/
} fsm_callbacks;


/*
 * 链接状态。
 */
#define PPP_FSM_INITIAL		0	/* 向下，尚未打开*/
#define PPP_FSM_STARTING	1	/* 向下，已打开*/
#define PPP_FSM_CLOSED		2	/* 向上，尚未打开*/
#define PPP_FSM_STOPPED		3	/* 打开，等待关闭事件*/
#define PPP_FSM_CLOSING		4	/* 终止连接，未打开*/
#define PPP_FSM_STOPPING	5	/* 正在终止，但打开*/
#define PPP_FSM_REQSENT		6	/* 我们已发送配置请求*/
#define PPP_FSM_ACKRCVD		7	/* 我们收到了配置确认*/
#define PPP_FSM_ACKSENT		8	/* 我们已发送配置确认*/
#define PPP_FSM_OPENED		9	/* 可用的连接*/


/*
 * 标志-指示控制FSM操作的选项
 */
#define OPT_PASSIVE	1	/* 如果我们得不到回应就别死*/
#define OPT_RESTART	2	/* 将第二次打开视为向下、向上*/
#define OPT_SILENT	4	/* 等待同伴先发言*/


/*
 * 超时。
 */
#if 0 /* 移动到ppp_opts。小时*/
#define DEFTIMEOUT	3	/* 超时时间（秒）*/
#define DEFMAXTERMREQS	2	/* 最大终止请求传输*/
#define DEFMAXCONFREQS	10	/* 最大配置请求传输*/
#define DEFMAXNAKLOOPS	5	/* nak循环的最大数量*/
#endif /* 移动到ppp_opts。小时*/


/*
 * 原型
 */
void fsm_init(fsm *f);
void fsm_lowerup(fsm *f);
void fsm_lowerdown(fsm *f);
void fsm_open(fsm *f);
void fsm_close(fsm *f, const char *reason);
void fsm_input(fsm *f, u_char *inpacket, int l);
void fsm_protreject(fsm *f);
void fsm_sdata(fsm *f, u_char code, u_char id, const u_char *data, int datalen);

#ifdef __cplusplus
}
#endif

#endif /* FSM_H */
#endif /* PPP_SUPPORT */

