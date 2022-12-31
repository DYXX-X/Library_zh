/**
 * @file
 *
 * IPv6的常见6LowPAN例程。使用ND表进行链路层寻址。将数据包拆分为6LowPAN单元。
 */

/*
 * 版权所有（c）2015 Inico Technologies Ltd.保留所有权利。
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

#ifndef LWIP_HDR_LOWPAN6_COMMON_H
#define LWIP_HDR_LOWPAN6_COMMON_H

#include "netif/lowpan6_opts.h"

#if LWIP_IPV6 /* 如果lwipots中禁用了IPv6，则不要构建。小时*/

#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**帮助程序定义链接层地址，可以编码为0、2或8字节*/
struct lowpan6_link_addr {
  /* 地址的编码长度*/
  u8_t addr_len;
  /* 地址字节*/
  u8_t addr[8];
};

s8_t lowpan6_get_address_mode(const ip6_addr_t *ip6addr, const struct lowpan6_link_addr *mac_addr);

#if LWIP_6LOWPAN_IPHC
err_t lowpan6_compress_headers(struct netif *netif, u8_t *inbuf, size_t inbuf_size, u8_t *outbuf, size_t outbuf_size,
                               u8_t *lowpan6_header_len_out, u8_t *hidden_header_len_out, ip6_addr_t *lowpan6_contexts,
                               const struct lowpan6_link_addr *src, const struct lowpan6_link_addr *dst);
struct pbuf *lowpan6_decompress(struct pbuf *p, u16_t datagram_size, ip6_addr_t *lowpan6_contexts,
                                struct lowpan6_link_addr *src, struct lowpan6_link_addr *dest);
#endif /* LWIP_6LOWPAN_IPHC */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_LOWPAN6_COMMON_H */

