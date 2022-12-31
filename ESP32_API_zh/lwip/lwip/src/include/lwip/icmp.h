/**
 * @file ICMP API
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
#ifndef LWIP_HDR_ICMP_H
#define LWIP_HDR_ICMP_H

#include "lwip/opt.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/prot/icmp.h"

#if LWIP_IPV6 && LWIP_ICMP6
#include "lwip/icmp6.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**ICMP目标不可访问代码*/
enum icmp_dur_type {
  /**网络无法访问*/
  ICMP_DUR_NET   = 0,
  /**主机无法访问*/
  ICMP_DUR_HOST  = 1,
  /**协议无法访问*/
  ICMP_DUR_PROTO = 2,
  /**无法访问端口*/
  ICMP_DUR_PORT  = 3,
  /**所需碎片和DF集合*/
  ICMP_DUR_FRAG  = 4,
  /**源路由失败*/
  ICMP_DUR_SR    = 5
};

/**ICMP超时代码*/
enum icmp_te_type {
  /**在运输过程中超过生存时间*/
  ICMP_TE_TTL  = 0,
  /**超过碎片重组时间*/
  ICMP_TE_FRAG = 1
};

#if LWIP_IPV4 && LWIP_ICMP /* 如果未配置为在lwipopts.h中使用，则不要构建*/

void icmp_input(struct pbuf *p, struct netif *inp);
void icmp_dest_unreach(struct pbuf *p, enum icmp_dur_type t);
void icmp_time_exceeded(struct pbuf *p, enum icmp_te_type t);

#endif /* LWIP_IPV4 && LWIP_ICMP */

#if LWIP_IPV4 && LWIP_IPV6
#if LWIP_ICMP && LWIP_ICMP6
#define icmp_port_unreach(isipv6, pbuf) ((isipv6) ? \
                                         icmp6_dest_unreach(pbuf, ICMP6_DUR_PORT) : \
                                         icmp_dest_unreach(pbuf, ICMP_DUR_PORT))
#elif LWIP_ICMP
#define icmp_port_unreach(isipv6, pbuf) do{ if(!(isipv6)) { icmp_dest_unreach(pbuf, ICMP_DUR_PORT);}}while(0)
#elif LWIP_ICMP6
#define icmp_port_unreach(isipv6, pbuf) do{ if(isipv6) { icmp6_dest_unreach(pbuf, ICMP6_DUR_PORT);}}while(0)
#else
#define icmp_port_unreach(isipv6, pbuf)
#endif
#elif LWIP_IPV6 && LWIP_ICMP6
#define icmp_port_unreach(isipv6, pbuf) icmp6_dest_unreach(pbuf, ICMP6_DUR_PORT)
#elif LWIP_IPV4 && LWIP_ICMP
#define icmp_port_unreach(isipv6, pbuf) icmp_dest_unreach(pbuf, ICMP_DUR_PORT)
#else /* (LWIP_IPV6 && LWIP_ICMP6) || (LWIP_IPV4 && LWIP_ICMP) */
#define icmp_port_unreach(isipv6, pbuf)
#endif /* (LWIP_IPV6 && LWIP_ICMP6) || (LWIP_IPV4 && LWIP_ICMP) LWIP_IPV4*/

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_ICMP_H */

