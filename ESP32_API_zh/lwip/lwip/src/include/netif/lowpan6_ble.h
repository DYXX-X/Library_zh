/**
 * @file 6LowPAN over BLE for IPv6（RFC7668）。
 */

/*
 * 版权所有（c）2017 Benjamin Aigner版权所有（c）2015 Inico Technologies Ltd.，作者：Ivan Delamer<delamer@inicotech.com>
 * 
 * 保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Benjamin Aigner<aignerb@technikum-wien.at>
 * 
 * 基于lwIP的原始6lowpan实现（参见6lowpan.c）
 */
 
#ifndef LWIP_HDR_LOWPAN6_BLE_H
#define LWIP_HDR_LOWPAN6_BLE_H

#include "netif/lowpan6_opts.h"

#if LWIP_IPV6 /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "netif/lowpan6_common.h"
#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

err_t rfc7668_output(struct netif *netif, struct pbuf *q, const ip6_addr_t *ip6addr);
err_t rfc7668_input(struct pbuf * p, struct netif *netif);
err_t rfc7668_set_local_addr_eui64(struct netif *netif, const u8_t *local_addr, size_t local_addr_len);
err_t rfc7668_set_local_addr_mac48(struct netif *netif, const u8_t *local_addr, size_t local_addr_len, int is_public_addr);
err_t rfc7668_set_peer_addr_eui64(struct netif *netif, const u8_t *peer_addr, size_t peer_addr_len);
err_t rfc7668_set_peer_addr_mac48(struct netif *netif, const u8_t *peer_addr, size_t peer_addr_len, int is_public_addr);
err_t rfc7668_set_context(u8_t index, const ip6_addr_t * context);
err_t rfc7668_if_init(struct netif *netif);

#if !NO_SYS
err_t tcpip_rfc7668_input(struct pbuf *p, struct netif *inp);
#endif

void ble_addr_to_eui64(uint8_t *dst, const uint8_t *src, int public_addr);
void eui64_to_ble_addr(uint8_t *dst, const uint8_t *src);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_LOWPAN6_BLE_H */

