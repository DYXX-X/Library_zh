/*
 * 向上。h-用户/密码认证协议定义。
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
 * $Id:upap。h、 v 1.8 2002/12/04 23:03:33 paulus展览$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PAP_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef UPAP_H
#define UPAP_H

#include "ppp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 数据包标头=代码、id、长度。
 */
#define UPAP_HEADERLEN	4


/*
 * UPAP代码。
 */
#define UPAP_AUTHREQ	1	/* 身份验证请求*/
#define UPAP_AUTHACK	2	/* 身份验证确认*/
#define UPAP_AUTHNAK	3	/* 验证Nak*/


/*
 * 客户端状态。
 */
#define UPAPCS_INITIAL	0	/* 连接已断开*/
#define UPAPCS_CLOSED	1	/* 连接已建立，尚未请求身份验证*/
#define UPAPCS_PENDING	2	/* 连接已断开，已请求身份验证*/
#define UPAPCS_AUTHREQ	3	/* 我们已发送身份验证请求*/
#define UPAPCS_OPEN	4	/* 我们收到了确认*/
#define UPAPCS_BADAUTH	5	/* 我们收到了一个Nak*/

/*
 * 服务器状态。
 */
#define UPAPSS_INITIAL	0	/* 连接已断开*/
#define UPAPSS_CLOSED	1	/* 连接已建立，尚未请求身份验证*/
#define UPAPSS_PENDING	2	/* 连接已断开，已请求身份验证*/
#define UPAPSS_LISTEN	3	/* 侦听身份验证*/
#define UPAPSS_OPEN	4	/* 我们已经发送了确认*/
#define UPAPSS_BADAUTH	5	/* 我们已经发送了一个Nak*/


/*
 * 超时。
 */
#if 0 /* 移动到ppp_opts。小时*/
#define UPAP_DEFTIMEOUT	3	/* 重发请求超时（秒）*/
#define UPAP_DEFREQTIME	30	/* 等待对等方身份验证请求的时间*/
#endif /* 移动到ppp_opts。小时*/

/*
 * 每个接口由upap结构描述。
 */
#if PAP_SUPPORT
typedef struct upap_state {
    const char *us_user;	/* 使用者*/
    u8_t us_userlen;		/* 用户长度*/
    const char *us_passwd;	/* 暗语*/
    u8_t us_passwdlen;		/* 密码长度*/
    u8_t us_clientstate;	/* 客户端状态*/
#if PPP_SERVER
    u8_t us_serverstate;	/* 服务器状态*/
#endif /* PPP_SERVER */
    u8_t us_id;		        /* 当前id*/
    u8_t us_transmits;		/* 发送的身份验证请求数*/
} upap_state;
#endif /* PAP_SUPPORT */


void upap_authwithpeer(ppp_pcb *pcb, const char *user, const char *password);
#if PPP_SERVER
void upap_authpeer(ppp_pcb *pcb);
#endif /* PPP_SERVER */

extern const struct protent pap_protent;

#ifdef __cplusplus
}
#endif

#endif /* UPAP_H */
#endif /* PPP_SUPPORT && PAP_SUPPORT */

