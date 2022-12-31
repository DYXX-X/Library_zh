/**
 * @file
 *
 * ICMP的IPv6版本，符合RFC 4443。
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
#ifndef LWIP_HDR_ICMP6_H
#define LWIP_HDR_ICMP6_H

#include "lwip/opt.h"
#include "lwip/pbuf.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"
#include "lwip/prot/icmp6.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_ICMP6 && LWIP_IPV6 /* 如果未配置为在lwipopts.h中使用，则不要构建*/

void icmp6_input(struct pbuf *p, struct netif *inp);
void icmp6_dest_unreach(struct pbuf *p, enum icmp6_dur_code c);
void icmp6_packet_too_big(struct pbuf *p, u32_t mtu);
void icmp6_time_exceeded(struct pbuf *p, enum icmp6_te_code c);
void icmp6_time_exceeded_with_addrs(struct pbuf *p, enum icmp6_te_code c,
    const ip6_addr_t *src_addr, const ip6_addr_t *dest_addr);
void icmp6_param_problem(struct pbuf *p, enum icmp6_pp_code c, const void *pointer);

#endif /* LWIP_ICMP6 && LWIP_IPV6 */


#ifdef __cplusplus
}
#endif


#endif /* LWIP_HDR_ICMP6_H */

