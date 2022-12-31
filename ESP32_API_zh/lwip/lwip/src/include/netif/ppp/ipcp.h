/*
 * ipcp.h-IP控制协议定义。
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
 * $Id:ipcp.h，v 1.14 2002/12/04 23:03:32 paulus Exp$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PPP_IPV4_SUPPORT /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#ifndef IPCP_H
#define	IPCP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 选项。
 */
#define CI_ADDRS	1	/* IP地址*/
#if VJ_SUPPORT
#define CI_COMPRESSTYPE	2	/* 压缩类型*/
#endif /* VJ_SUPPORT */
#define	CI_ADDR		3

#if LWIP_DNS
#define CI_MS_DNS1      129	/* 主DNS值*/
#define CI_MS_DNS2      131     /* 辅助DNS值*/
#endif /* LWIP_DNS */
#if 0 /* UNUSED - WINS */
#define CI_MS_WINS1     130     /* 主WINS值*/
#define CI_MS_WINS2     132	/* 辅助WINS值*/
#endif /* UNUSED - WINS */

#if VJ_SUPPORT
#define MAX_STATES 16		/* 来自slcompress.h*/

#define IPCP_VJMODE_OLD 1	/* “旧”模式（选项#=0x0037）*/
#define IPCP_VJMODE_RFC1172 2	/* “旧rfc”模式（选项#=0x002d）*/
#define IPCP_VJMODE_RFC1332 3	/* “新rfc”模式（选项#=0x002d，*/
                                /*  maxslot和槽数压缩）*/

#define IPCP_VJ_COMP 0x002d	/* VJ压缩选项的当前值*/
#define IPCP_VJ_COMP_OLD 0x0037	/* VJ的“旧”（即断裂）值*/
				/* 压缩选项*/ 
#endif /* VJ_SUPPORT */

typedef struct ipcp_options {
    unsigned int neg_addr               :1; /* 协商IP地址？*/
    unsigned int old_addrs              :1; /* 使用旧（IP地址）选项？*/
    unsigned int req_addr               :1; /* 要求对等方发送IP地址？*/
#if 0 /* UNUSED */
    unsigned int default_route          :1; /* 是否通过接口分配默认路由？*/
    unsigned int replace_default_route  :1; /* 是否通过接口替换默认路由？*/
#endif /* UNUSED */
#if 0 /* UNUSED - PROXY ARP */
    unsigned int proxy_arp              :1; /* 为对等方创建代理ARP条目？*/
#endif /* UNUSED - PROXY ARP */
#if VJ_SUPPORT
    unsigned int neg_vj                 :1; /* Van Jacobson压缩？*/
    unsigned int old_vj                 :1; /* 使用旧（短）形式的VJ选项？*/
    unsigned int cflag                  :1;
#endif /* VJ_SUPPORT */
    unsigned int accept_local           :1; /* 接受对等方的ouraddr值*/
    unsigned int accept_remote          :1; /* 接受hisaddr的对等值*/
#if LWIP_DNS
    unsigned int req_dns1               :1; /* 要求对等方发送主DNS地址？*/
    unsigned int req_dns2               :1; /* 要求对等方发送辅助DNS地址？*/
#endif /* LWIP_DNS */

    u32_t ouraddr, hisaddr;	/* NETWORK BYTE ORDER中的地址*/
#if LWIP_DNS
    u32_t dnsaddr[2];	/* 主要和次要MS DNS条目*/
#endif /* LWIP_DNS */
#if 0 /* UNUSED - WINS */
    u32_t winsaddr[2];	/* 主要和次要MS WINS条目*/
#endif /* UNUSED - WINS */

#if VJ_SUPPORT
    u16_t vj_protocol;		/* 要在VJ选项中使用的协议值*/
    u8_t  maxslotindex;		/* RFC1332 VJ压缩值为负。*/
#endif /* VJ_SUPPORT */
} ipcp_options;

#if 0 /* 未使用，已由lwIP定义*/
char *ip_ntoa (u32_t);
#endif /* 未使用，已由lwIP定义*/

extern const struct protent ipcp_protent;

#ifdef __cplusplus
}
#endif

#endif /* IPCP_H */
#endif /* PPP_SUPPORT && PPP_IPV4_SUPPORT */

