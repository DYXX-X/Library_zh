/*
 * lcp。h-链路控制协议定义。
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
 * $Id:lcp。h、 v 1.20 2004/11/14 22:53:42 carlsonj Exp公司$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef LCP_H
#define	LCP_H

#include "ppp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 选项。
 */
#define CI_VENDOR	0	/* 供应商特定*/
#define CI_MRU		1	/* 最大接收单元*/
#define CI_ASYNCMAP	2	/* 异步控制字符映射*/
#define CI_AUTHTYPE	3	/* 身份验证类型*/
#define CI_QUALITY	4	/* 质量协议*/
#define CI_MAGICNUMBER	5	/* 魔术数字*/
#define CI_PCOMPRESSION	7	/* 协议字段压缩*/
#define CI_ACCOMPRESSION 8	/* 地址/控制字段压缩*/
#define CI_FCSALTERN	9	/* FCS备选方案*/
#define CI_SDP		10	/* 自我描述垫*/
#define CI_NUMBERED	11	/* 编号模式*/
#define CI_CALLBACK	13	/* 回调*/
#define CI_MRRU		17	/* 最大重建接收单元；多链路*/
#define CI_SSNHF	18	/* 多链路的短序列号*/
#define CI_EPDISC	19	/* 端点鉴别器*/
#define CI_MPPLUS	22	/* Multi-Link Plus程序*/
#define CI_LDISC	23	/* 链接鉴别器*/
#define CI_LCPAUTH	24	/* LCP身份验证*/
#define CI_COBS		25	/* 一致开销字节填充*/
#define CI_PREFELIS	26	/* 前缀Elision*/
#define CI_MPHDRFMT	27	/* MP标题格式*/
#define CI_I18N		28	/* 国际化*/
#define CI_SDL		29	/* 简单数据链接*/

/*
 * LCP特定数据包类型（代码编号）。
 */
#define PROTREJ		8	/* 协议拒绝*/
#define ECHOREQ		9	/* 回音请求*/
#define ECHOREP		10	/* 回显答复*/
#define DISCREQ		11	/* 放弃请求*/
#define IDENTIF		12	/* 识别*/
#define TIMEREM		13	/* 剩余时间*/

/* 用作CI_CALLBACK选项数据的值*/
#define CBCP_OPT	6	/* 使用回调控制协议*/

#if 0 /* 移动到ppp_opts。小时*/
#define DEFMRU	1500		/* 试试这个*/
#define MINMRU	128		/* 没有低于此值的MRU*/
#define MAXMRU	16384		/* 通常将MRU限制为*/
#endif /* 移动到ppp_opts。小时*/

/* 端点鉴别器，用于多链路。*/
#define MAX_ENDP_LEN	20	/* 鉴别器值的最大长度*/
struct epdisc {
    unsigned char	class_; /* --“class”一词在C++中是保留的。*/
    unsigned char	length;
    unsigned char	value[MAX_ENDP_LEN];
};

/*
 * 选项的状态由lcp_options结构描述。
 */
typedef struct lcp_options {
    unsigned int passive           :1; /* 如果我们得不到回应就别死*/
    unsigned int silent            :1; /* 等待另一端先启动*/
#if 0 /* UNUSED */
    unsigned int restart           :1; /* 重新启动与关闭后退出*/
#endif /* UNUSED */
    unsigned int neg_mru           :1; /* 协商MRU？*/
    unsigned int neg_asyncmap      :1; /* 协商异步映射？*/
#if PAP_SUPPORT
    unsigned int neg_upap          :1; /* 请求UPAP身份验证？*/
#endif /* PAP_SUPPORT */
#if CHAP_SUPPORT
    unsigned int neg_chap          :1; /* 请求CHAP身份验证？*/
#endif /* CHAP_SUPPORT */
#if EAP_SUPPORT
    unsigned int neg_eap           :1; /* 请求EAP身份验证？*/
#endif /* EAP_SUPPORT */
    unsigned int neg_magicnumber   :1; /* 问魔术数字？*/
    unsigned int neg_pcompression  :1; /* HDLC协议字段压缩？*/
    unsigned int neg_accompression :1; /* HDLC地址/控制字段压缩？*/
#if LQR_SUPPORT
    unsigned int neg_lqr           :1; /* 协商使用链路质量报告*/
#endif /* LQR_SUPPORT */
    unsigned int neg_cbcp          :1; /* 协商CBCP的使用*/
#ifdef HAVE_MULTILINK
    unsigned int neg_mrru          :1; /* 协商多链路MRRU*/
#endif /* HAVE_MULTILINK */
    unsigned int neg_ssnhf         :1; /* 协商短序列号*/
    unsigned int neg_endpoint      :1; /* 协商端点鉴别器*/

    u16_t mru;			/* MRU的价值*/
#ifdef HAVE_MULTILINK
    u16_t mrru;			/* MRRU的价值和多链路启用*/
#endif /* MULTILINK */
#if CHAP_SUPPORT
    u8_t chap_mdtype;		/* 哪些MD类型（哈希算法）*/
#endif /* CHAP_SUPPORT */
    u32_t asyncmap;		/* 异步映射的值*/
    u32_t magicnumber;
    u8_t  numloops;		/* 幻数负期间的循环数。*/
#if LQR_SUPPORT
    u32_t lqr_period;	/* LQR报告周期1/100秒*/
#endif /* LQR_SUPPORT */
    struct epdisc endpoint;	/* 端点鉴别器*/
} lcp_options;

void lcp_open(ppp_pcb *pcb);
void lcp_close(ppp_pcb *pcb, const char *reason);
void lcp_lowerup(ppp_pcb *pcb);
void lcp_lowerdown(ppp_pcb *pcb);
void lcp_sprotrej(ppp_pcb *pcb, u_char *p, int len);    /* 发送协议拒绝*/

extern const struct protent lcp_protent;

#if 0 /* 移动到ppp_opts。小时*/
/* 在决定链接被环回之前，我们从对等方收到魔法数字的默认次数。*/
#define DEFLOOPBACKFAIL	10
#endif /* 移动到ppp_opts.h*/

#ifdef __cplusplus
}
#endif

#endif /* LCP_H */
#endif /* PPP_SUPPORT */

