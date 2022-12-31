/**
 * @file ip4_napt.h这是从ip4.c使用的ip4_napt的私有接口
 *
 * @see ip4_napt.c
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
 * Adam Dunkels的原始重组代码<adam@sics.se>
 *
 */

#ifndef LWIP_HDR_IP4_NAPT_H
#define LWIP_HDR_IP4_NAPT_H

#include "lwip/opt.h"

#if ESP_LWIP
#if IP_FORWARD
#if IP_NAPT

#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/ip4_addr.h"
#include "lwip/err.h"
#include "lwip/netif.h"
#include "lwip/prot/ip4.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/err.h"
#include "lwip/ip4.h"

/**
* 转发数据包的NAPT。它检查我们是否需要NAPT，并在需要时修改数据包源地址和端口。
*
* @param p 要转发的数据包（p->有效负载指向IP报头）
* @param iphdr 输入数据包的IP标头
* @param inp 接收此数据包的netif
* @param outp 发送此数据包的netif
* @return 如果应发送数据包，则返回ERR_OK；如果应丢弃数据包，返回ERR_RTE
*/
err_t
ip_napt_forward(struct pbuf *p, struct ip_hdr *iphdr, struct netif *inp, struct netif *outp);

/**
 * 输入数据包的NAPT。它检查目的地是否在NAPT表上，并根据需要修改数据包目的地地址和端口。
 *
 * @param p 要转发的数据包（p->有效负载指向IP报头）
 * @param iphdr 输入数据包的IP标头
 * @param inp 接收此数据包的netif
 */
void
ip_napt_recv(struct pbuf *p, struct ip_hdr *iphdr);

#ifdef __cplusplus
}
#endif

#endif /* IP_NAPT */
#endif /* IP_FORWARD */
#endif /* ESP_LWIP */

#endif /* LWIP_HDR_IP4_NAPT_H */


