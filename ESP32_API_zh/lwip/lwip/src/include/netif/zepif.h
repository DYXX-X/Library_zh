/**
 * @file
 *
 * 实现ZigBee封装协议（ZEP）的网络。这用于通过UDP对6LowPAN进行隧道传输。
 */

/*
 * 版权所有（c）2018 Simon Goldschmidt保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 *
 */

#ifndef LWIP_HDR_ZEPIF_H
#define LWIP_HDR_ZEPIF_H

#include "lwip/opt.h"
#include "netif/lowpan6.h"

#if LWIP_IPV6 && LWIP_UDP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ZEPIF_DEFAULT_UDP_PORT  17754

/**将此结构作为“state”传递给netif_add以控制此netif的行为。如果传递NULL，则选择默认行为*/
struct zepif_init {
  /**用于ZEP帧的UDP端口（0=默认值）*/
  u16_t               zep_src_udp_port;
  /**用于将帧ZEP到的UDP端口（0=默认值）*/
  u16_t               zep_dst_udp_port;
  /**sed ZEP帧的IP地址（NULL=ANY）*/
  const ip_addr_t    *zep_src_ip_addr;
  /**ZEP帧的IP地址（NULL=广播）*/
  const ip_addr_t    *zep_dst_ip_addr;
  /**如果！=NULL，udp pcb绑定到此netif*/
  const struct netif *zep_netif;
  /**6LowPAN设备的MAC地址*/
  u8_t                addr[6];
};

err_t zepif_init(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 && LWIP_UDP */

#endif /* LWIP_HDR_ZEPIF_H */

