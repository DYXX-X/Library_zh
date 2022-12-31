/**
 * @file 以太网输入功能-处理输入以太网级流量用于大多数低级netif实现
 */

/*
 * 版权所有（c）2001-2003瑞典计算机科学研究所。版权所有（c）2003-2004 Leon Woestenberg<leon.woestenberg@axon.tv>版权所有（c）2003-2004 Axon Digital Design B.V.，荷兰。保留所有权利。
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

#ifndef LWIP_HDR_NETIF_ETHERNET_H
#define LWIP_HDR_NETIF_ETHERNET_H

#include "lwip/opt.h"

#include "lwip/pbuf.h"
#include "lwip/netif.h"
#include "lwip/prot/ethernet.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_ARP || LWIP_ETHERNET

/** 将其定义为1，并将LWIP_ARP_FILTER_NETIF_FN（pbuf，NETIF，type）定义为一个过滤器函数，当在一个硬件接口上使用多个NETIF时，NETIF的低级接收例程无法决定正确的NETIF（例如，当将多个IP地址映射到一个硬件界面时），该过滤器函数将返回正确的NETIF。
 */
#ifndef LWIP_ARP_FILTER_NETIF
#define LWIP_ARP_FILTER_NETIF 0
#endif

err_t ethernet_input(struct pbuf *p, struct netif *netif);
err_t ethernet_output(struct netif* netif, struct pbuf* p, const struct eth_addr* src, const struct eth_addr* dst, u16_t eth_type);

extern const struct eth_addr ethbroadcast, ethzero;

#endif /* LWIP_ARP || LWIP_ETHERNET */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_NETIF_ETHERNET_H */

