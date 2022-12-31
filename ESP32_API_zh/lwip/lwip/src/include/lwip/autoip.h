/**
 * @file
 *
 * AutoIP自动链接本地IP配置
 */

/*
 * 版权所有（c）2007 Dominik Spies<kontakt@dspies.de>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Dominik Spies<kontakt@dspies.de>
 *
 * 这是lwIP TCP/IP堆栈的AutoIP实现。它旨在符合RFC 3927。
 *
 */

#ifndef LWIP_HDR_AUTOIP_H
#define LWIP_HDR_AUTOIP_H

#include "lwip/opt.h"

#if LWIP_IPV4 && LWIP_AUTOIP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/netif.h"
/* #包括“lwip/udp.h”*/
#include "lwip/etharp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**AutoIP定时*/
#define AUTOIP_TMR_INTERVAL      100
#define AUTOIP_TICKS_PER_SECOND (1000 / AUTOIP_TMR_INTERVAL)

/**每个netif的AutoIP状态信息*/
struct autoip
{
  /**当前选择、探测、宣布或使用的LL IP地址*/
  ip4_addr_t llipaddr;
  /**当前AutoIP状态机状态*/
  u8_t state;
  /**发送探测或通告的数量，取决于状态*/
  u8_t sent_num;
  /**滴答声等待，滴答声为AUTOIP_TMR_INTERVAL长*/
  u16_t ttw;
  /**直到通过防御解决冲突*/
  u8_t lastconflict;
  /**探测/使用的链路本地IP地址总数*/
  u8_t tried_llipaddr;
};


void autoip_set_struct(struct netif *netif, struct autoip *autoip);
/**使用autoip_set_struct（）删除先前设置为netif的结构autoip*/
#define autoip_remove_struct(netif) do { (netif)->autoip = NULL; } while (0)
err_t autoip_start(struct netif *netif);
err_t autoip_stop(struct netif *netif);
void autoip_arp_reply(struct netif *netif, struct etharp_hdr *hdr);
void autoip_tmr(void);
void autoip_network_changed(struct netif *netif);
u8_t autoip_supplied_address(const struct netif *netif);

/* 用于lwIP内部使用ip4.c*/
u8_t autoip_accept_packet(struct netif *netif, const ip4_addr_t *addr);

#define netif_autoip_data(netif) ((struct autoip*)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_AUTOIP))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV4 && LWIP_AUTOIP */

#endif /* LWIP_HDR_AUTOIP_H */

