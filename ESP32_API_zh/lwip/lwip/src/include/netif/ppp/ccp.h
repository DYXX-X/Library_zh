/*
 * Ccph-PPP压缩控制协议的定义。
 *
 * 版权所有（c）1994-2002 Paul Mackerras。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * 3.任何形式的再发行都必须保留以下确认：“本产品包括Paul Mackerras开发的软件<paulus@samba.org>".
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id:ccp。h、 v 2004年11月12日10:02:26 paulus Exp$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && CCP_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef CCP_H
#define CCP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * CCP代码。
 */

#define CCP_CONFREQ	1
#define CCP_CONFACK	2
#define CCP_TERMREQ	5
#define CCP_TERMACK	6
#define CCP_RESETREQ	14
#define CCP_RESETACK	15

/*
 * CCP选项的最大字节数
 */

#define CCP_MAX_OPTION_LENGTH	32

/*
 * CCP数据包的一部分。
 */

#define CCP_CODE(dp)		((dp)[0])
#define CCP_ID(dp)		((dp)[1])
#define CCP_LENGTH(dp)		(((dp)[2] << 8) + (dp)[3])
#define CCP_HDRLEN		4

#define CCP_OPT_CODE(dp)	((dp)[0])
#define CCP_OPT_LENGTH(dp)	((dp)[1])
#define CCP_OPT_MINLEN		2

#if BSDCOMPRESS_SUPPORT
/*
 * BSD压缩的定义。
 */

#define CI_BSD_COMPRESS		21	/* 配置。BSD压缩选项*/
#define CILEN_BSD_COMPRESS	3	/* 配置的长度。选项*/

/* 用于处理BSD压缩配置选项的第三个字节的宏。*/
#define BSD_NBITS(x)		((x) & 0x1F)	/* 请求的位数*/
#define BSD_VERSION(x)		((x) >> 5)	/* 选项格式的版本*/
#define BSD_CURRENT_VERSION	1		/* 当前版本号*/
#define BSD_MAKE_OPT(v, n)	(((v) << 5) | (n))

#define BSD_MIN_BITS		9	/* 支持的最小代码大小*/
#define BSD_MAX_BITS		15	/* 支持的最大代码大小*/
#endif /* BSDCOMPRESS_SUPPORT */

#if DEFLATE_SUPPORT
/*
 * 通货紧缩的定义。
 */

#define CI_DEFLATE		26	/* Deflate的配置选项*/
#define CI_DEFLATE_DRAFT	24	/* 原始RFC草案中使用的值*/
#define CILEN_DEFLATE		4	/* 其配置选项的长度*/

#define DEFLATE_MIN_SIZE	9
#define DEFLATE_MAX_SIZE	15
#define DEFLATE_METHOD_VAL	8
#define DEFLATE_SIZE(x)		(((x) >> 4) + 8)
#define DEFLATE_METHOD(x)	((x) & 0x0F)
#define DEFLATE_MAKE_OPT(w)	((((w) - 8) << 4) + DEFLATE_METHOD_VAL)
#define DEFLATE_CHK_SEQUENCE	0
#endif /* DEFLATE_SUPPORT */

#if MPPE_SUPPORT
/*
 * MPPE的定义。
 */

#define CI_MPPE                18      /* MPPE的配置选项*/
#define CILEN_MPPE              6      /* 配置选项的长度*/
#endif /* MPPE_SUPPORT */

#if PREDICTOR_SUPPORT
/*
 * 其他尚未支持的压缩方法的定义。
 */

#define CI_PREDICTOR_1		1	/* Predictor-1的配置选项*/
#define CILEN_PREDICTOR_1	2	/* 其配置选项的长度*/
#define CI_PREDICTOR_2		2	/* Predictor-2的配置选项*/
#define CILEN_PREDICTOR_2	2	/* 其配置选项的长度*/
#endif /* PREDICTOR_SUPPORT */

typedef struct ccp_options {
#if DEFLATE_SUPPORT
    unsigned int deflate          :1; /* 是否放气？*/
    unsigned int deflate_correct  :1; /* 使用正确的放气代码？*/
    unsigned int deflate_draft    :1; /* 使用RFC草案代码进行放气？*/
#endif /* DEFLATE_SUPPORT */
#if BSDCOMPRESS_SUPPORT
    unsigned int bsd_compress     :1; /* 做BSD压缩吗？*/
#endif /* BSDCOMPRESS_SUPPORT */
#if PREDICTOR_SUPPORT
    unsigned int predictor_1      :1; /* 做预测1？*/
    unsigned int predictor_2      :1; /* 做预测2？*/
#endif /* PREDICTOR_SUPPORT */

#if MPPE_SUPPORT
    u8_t mppe;			/* MPPE位字段*/
#endif /* MPPE_SUPPORT */
#if BSDCOMPRESS_SUPPORT
    u_short bsd_bits;		/* #BSD压缩的位/代码*/
#endif /* BSDCOMPRESS_SUPPORT */
#if DEFLATE_SUPPORT
    u_short deflate_size;	/* 放气的lg（窗口大小）*/
#endif /* DEFLATE_SUPPORT */
    u8_t method;		/* 选定压缩方法代码*/
} ccp_options;

extern const struct protent ccp_protent;

void ccp_resetrequest(ppp_pcb *pcb);  /* 发出重置请求。*/

#ifdef __cplusplus
}
#endif

#endif /* CCP_H */
#endif /* PPP_SUPPORT && CCP_SUPPORT */

