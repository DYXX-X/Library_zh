/**
 * @file
 *
 * 6LowPAN输出用于IPv6。使用ND表进行链路层寻址。将数据包拆分为6LowPAN单元。
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

#ifndef LWIP_HDR_LOWPAN6_H
#define LWIP_HDR_LOWPAN6_H

#include "netif/lowpan6_opts.h"

#if LWIP_IPV6

#include "netif/lowpan6_common.h"
#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**重新组装的1秒时间*/
#define LOWPAN6_TMR_INTERVAL 1000

void lowpan6_tmr(void);

err_t lowpan6_set_context(u8_t idx, const ip6_addr_t * context);
err_t lowpan6_set_short_addr(u8_t addr_high, u8_t addr_low);

#if LWIP_IPV4
err_t lowpan4_output(struct netif *netif, struct pbuf *q, const ip4_addr_t *ipaddr);
#endif /* LWIP_IPV4 */
err_t lowpan6_output(struct netif *netif, struct pbuf *q, const ip6_addr_t *ip6addr);
err_t lowpan6_input(struct pbuf * p, struct netif *netif);
err_t lowpan6_if_init(struct netif *netif);

/* pan_id的网络字节顺序。*/
err_t lowpan6_set_pan_id(u16_t pan_id);

u16_t lowpan6_calc_crc(const void *buf, u16_t len);

#if !NO_SYS
err_t tcpip_6lowpan_input(struct pbuf *p, struct netif *inp);
#endif /* !NO_SYS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_LOWPAN6_H */

