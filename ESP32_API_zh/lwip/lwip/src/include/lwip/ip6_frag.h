/**
 * @file
 *
 * IPv6分段和重组。
 */

/*
 * 版权所有（c）2010 Inico Technologies Ltd.保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Ivan Delamer<delamer@inicotech.com>
 *
 * 请与Ivan Delamer协调变更和请求
 * <delamer@inicotech.com>
 */
#ifndef LWIP_HDR_IP6_FRAG_H
#define LWIP_HDR_IP6_FRAG_H

#include "lwip/opt.h"
#include "lwip/pbuf.h"
#include "lwip/ip6_addr.h"
#include "lwip/ip6.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif


#if LWIP_IPV6 && LWIP_IPV6_REASS  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/**IPv6重新组装计时器间隔（毫秒）。*/
#define IP6_REASS_TMR_INTERVAL 1000

/**IP6_FRAG_COPYHEADER==1：对于sizeof（void*）>4的平台，“struct IP6_reads_helper”太大，无法存储在IPv6片段标头中，并将渗入其前面的标头，该标头可能是IPv6标头或扩展标头。这意味着，对于每个第一个片段数据包，我们需要1）制作稍后需要的一些IPv6报头字段（src+dest）的副本，以防覆盖部分IPv6报头，2）制作覆盖的报头数据的副本，以便在完成重新组装或发送ICMPv6回复之前将其还原。即使禁用了此设置，最后一部分也是正确的，但是如果启用了它，我们需要保存更多的数据（最多一个指针的大小），因为我们会覆盖更多的数据。*/
#ifndef IPV6_FRAG_COPYHEADER
#define IPV6_FRAG_COPYHEADER   0
#endif

/* 在IPV6_FRAG_COPYHEADER==1的情况下，帮助器结构可以（或者，根据扩展的存在，可以不）覆盖IP报头的一部分。因此，只要帮助器结构仍然存在，我们就从IP头中复制所需的字段。这比每次需要对IP标头中的字段执行检查时临时恢复这些字段更容易。*/
#if IPV6_FRAG_COPYHEADER
#define IPV6_FRAG_SRC(ipr) ((ipr)->src)
#define IPV6_FRAG_DEST(ipr) ((ipr)->dest)
#else /* IPV6_FRAG_COPYHEADER */
#define IPV6_FRAG_SRC(ipr) ((ipr)->iphdr->src)
#define IPV6_FRAG_DEST(ipr) ((ipr)->iphdr->dest)
#endif /* IPV6_FRAG_COPYHEADER */

/** IPv6重新组装帮助结构。这是导出的，因为memp需要知道大小。
 */
struct ip6_reassdata {
  struct ip6_reassdata *next;
  struct pbuf *p;
  struct ip6_hdr *iphdr; /* 指向第一个（原始）IPv6标头的指针*/
#if IPV6_FRAG_COPYHEADER
  ip6_addr_p_t src; /* IP标头中源地址的副本*/
  ip6_addr_p_t dest; /* IP标头中目标地址的副本*/
  /* 这个缓冲区（对于我们覆盖的原始标头部分）将稍微过大，但我们无法从这里计算确切的大小。*/
  u8_t orig_hdr[sizeof(struct ip6_frag_hdr) + sizeof(void*)];
#else /* IPV6_FRAG_COPYHEADER */
  /* 在这种情况下，我们仍然需要缓冲区，用于发送ICMPv6回复。*/
  u8_t orig_hdr[sizeof(struct ip6_frag_hdr)];
#endif /* IPV6_FRAG_COPYHEADER */
  u32_t identification;
  u16_t datagram_len;
  u8_t nexth;
  u8_t timer;
#if LWIP_IPV6_SCOPES
  u8_t src_zone; /* 原始数据包源地址的区域*/
  u8_t dest_zone; /* 原始数据包的目标地址区域*/
#endif /* LWIP_IPV6_SCOPES */
};

#define ip6_reass_init() /* 兼容性定义*/
void ip6_reass_tmr(void);
struct pbuf *ip6_reass(struct pbuf *p);

#endif /* LWIP_IPV6 && LWIP_IPV6_REASS */

#if LWIP_IPV6 && LWIP_IPV6_FRAG  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef LWIP_PBUF_CUSTOM_REF_DEFINED
#define LWIP_PBUF_CUSTOM_REF_DEFINED
/**一个自定义pbuf，它保存对另一个pbuf的引用，当释放该自定义pbuf时，该pbuf将被释放。这用于创建指向原始PBUF的自定义PBUF_REF。*/
struct pbuf_custom_ref {
  /**'基类'*/
  struct pbuf_custom pc;
  /**指向引用的原始pbuf的指针*/
  struct pbuf *original;
};
#endif /* LWIP_PBUF_CUSTOM_REF_DEFINED */

err_t ip6_frag(struct pbuf *p, struct netif *netif, const ip6_addr_t *dest);

#endif /* LWIP_IPV6 && LWIP_IPV6_FRAG */


#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_IP6_FRAG_H */

