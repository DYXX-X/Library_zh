/**
 * @file lwip_napt。ip4_napt的公共API
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

#ifndef __LWIP_NAPT_H__
#define __LWIP_NAPT_H__

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#if ESP_LWIP
#if IP_FORWARD
#if IP_NAPT

/* 用于NAPT的表的默认大小*/
#ifndef IP_NAPT_MAX
#define IP_NAPT_MAX 512
#endif
#ifndef IP_PORTMAP_MAX
#define IP_PORTMAP_MAX 32
#endif

/* 各种协议类型的超时（秒）*/
#define IP_NAPT_TIMEOUT_MS_TCP (30*60*1000)
#define IP_NAPT_TIMEOUT_MS_TCP_DISCON (20*1000)
#define IP_NAPT_TIMEOUT_MS_UDP (2*1000)
#define IP_NAPT_TIMEOUT_MS_ICMP (2*1000)

#define IP_NAPT_PORT_RANGE_START 49152
#define IP_NAPT_PORT_RANGE_END   61439

/**
 * 为指定接口启用/禁用NAPT。
 *
 * @param addr 接口的ip地址
 * @param enable 非零表示启用NAPT，或0表示禁用。
 */
void
ip_napt_enable(u32_t addr, int enable);


/**
 * 为指定接口启用/禁用NAPT。
 *
 * @param netif 接口编号
 * @param enable 非零表示启用NAPT，或0表示禁用。
 */
void
ip_napt_enable_no(u8_t number, int enable);


/**
 * 注册外部接口到内部接口的端口映射。再次注册同一端口映射时，将覆盖旧映射。在此实现中，只能为每个目标地址/端口定义1个唯一的端口映射。
 *
 * @param proto 目标协议
 * @param maddr 外部接口的ip地址
 * @param mport 外部接口上的映射端口，按主机字节顺序。
 * @param daddr 目标ip地址
 * @param dport 目标端口，按主机字节顺序。
 */
u8_t
ip_portmap_add(u8_t proto, u32_t maddr, u16_t mport, u32_t daddr, u16_t dport);


/**
 * 注销外部接口到内部接口的端口映射。
 *
 * @param proto 目标协议
 * @param maddr 外部接口的ip地址
 */
u8_t
ip_portmap_remove(u8_t proto, u16_t mport);

#endif /* IP_NAPT */
#endif /* IP_FORWARD */
#endif /* ESP_LWIP */

#ifdef __cplusplus
}
#endif

#endif /* __LWIP_NAPT_H__ */

