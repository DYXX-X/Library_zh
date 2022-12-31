/**
 * @file IPv4地址API
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
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_IP4_ADDR_H
#define LWIP_HDR_IP4_ADDR_H

#include "lwip/opt.h"
#include "lwip/def.h"

#if LWIP_IPV4

#ifdef __cplusplus
extern "C" {
#endif

/**这是ip4_addr_t的对齐版本，用作堆栈等上的局部变量。*/
struct ip4_addr {
  u32_t addr;
};

/**ip4_addrt使用结构只是为了方便，因此相同的定义可以在ip4_addr和ip4_addr_pt上操作。*/
typedef struct ip4_addr ip4_addr_t;

/* 转发声明不包含netif。小时*/
struct netif;

/** 255.255.255.255 */
#define IPADDR_NONE         ((u32_t)0xffffffffUL)
/** 127.0.0.1 */
#define IPADDR_LOOPBACK     ((u32_t)0x7f000001UL)
/** 0.0.0.0 */
#define IPADDR_ANY          ((u32_t)0x00000000UL)
/** 255.255.255.255 */
#define IPADDR_BROADCAST    ((u32_t)0xffffffffUL)

/* Internet地址整数中位的定义。

   在子网上，主机和网络部件是根据子网掩码而不是这些掩码找到的。*/
#define IP_CLASSA(a)        ((((u32_t)(a)) & 0x80000000UL) == 0)
#define IP_CLASSA_NET       0xff000000
#define IP_CLASSA_NSHIFT    24
#define IP_CLASSA_HOST      (0xffffffff & ~IP_CLASSA_NET)
#define IP_CLASSA_MAX       128

#define IP_CLASSB(a)        ((((u32_t)(a)) & 0xc0000000UL) == 0x80000000UL)
#define IP_CLASSB_NET       0xffff0000
#define IP_CLASSB_NSHIFT    16
#define IP_CLASSB_HOST      (0xffffffff & ~IP_CLASSB_NET)
#define IP_CLASSB_MAX       65536

#define IP_CLASSC(a)        ((((u32_t)(a)) & 0xe0000000UL) == 0xc0000000UL)
#define IP_CLASSC_NET       0xffffff00
#define IP_CLASSC_NSHIFT    8
#define IP_CLASSC_HOST      (0xffffffff & ~IP_CLASSC_NET)

#define IP_CLASSD(a)        (((u32_t)(a) & 0xf0000000UL) == 0xe0000000UL)
#define IP_CLASSD_NET       0xf0000000          /* 这些不是真的*/
#define IP_CLASSD_NSHIFT    28                  /*   net和host字段，但是*/
#define IP_CLASSD_HOST      0x0fffffff          /*   路由不必知道。*/
#define IP_MULTICAST(a)     IP_CLASSD(a)

#define IP_EXPERIMENTAL(a)  (((u32_t)(a) & 0xf0000000UL) == 0xf0000000UL)
#define IP_BADCLASS(a)      (((u32_t)(a) & 0xf0000000UL) == 0xf0000000UL)

#define IP_LOOPBACKNET      127                 /* 公务的*/

/**设置由四字节部分给出的IP地址*/
#define IP4_ADDR(ipaddr, a,b,c,d)  (ipaddr)->addr = PP_HTONL(LWIP_MAKEU32(a,b,c,d))

/**复制IP地址-比ip4_addr_set更快：无NULL检查*/
#define ip4_addr_copy(dest, src) ((dest).addr = (src).addr)
/**安全地将一个IP地址复制到另一个（src可能为NULL）*/
#define ip4_addr_set(dest, src) ((dest)->addr = \
                                    ((src) == NULL ? 0 : \
                                    (src)->addr))
/**将完整地址设置为零*/
#define ip4_addr_set_zero(ipaddr)     ((ipaddr)->addr = 0)
/**将地址设置为IPADDR_ANY（不需要lwip_htonl（））*/
#define ip4_addr_set_any(ipaddr)      ((ipaddr)->addr = IPADDR_ANY)
/**将地址设置为环回地址*/
#define ip4_addr_set_loopback(ipaddr) ((ipaddr)->addr = PP_HTONL(IPADDR_LOOPBACK))
/**检查地址是否在环回区域中*/
#define ip4_addr_isloopback(ipaddr)    (((ipaddr)->addr & PP_HTONL(IP_CLASSA_NET)) == PP_HTONL(((u32_t)IP_LOOPBACKNET) << 24))
/**安全地将一个IP地址复制到另一个，并将字节顺序从主机更改为网络顺序。*/
#define ip4_addr_set_hton(dest, src) ((dest)->addr = \
                               ((src) == NULL ? 0:\
                               lwip_htonl((src)->addr)))
/**仅IPv4：将给定的IP地址设置为u32_t*/
#define ip4_addr_set_u32(dest_ipaddr, src_u32) ((dest_ipaddr)->addr = (src_u32))
/**仅IPv4：获取作为u32_t的IP地址*/
#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)

/**通过将主机地址与网络掩码组合来获取网络地址*/
#define ip4_addr_get_network(target, host, netmask) do { ((target)->addr = ((host)->addr) & ((netmask)->addr)); } while(0)

/**
 * 确定两个地址是否在同一网络上。
 *
 * @arg addr1 IP地址1
 * @arg addr2 IP地址2
 * @arg 掩码网络标识符掩码
 * @return !如果两个地址的网络标识符匹配，则为0
 */
#define ip4_addr_netcmp(addr1, addr2, mask) (((addr1)->addr & \
                                              (mask)->addr) == \
                                             ((addr2)->addr & \
                                              (mask)->addr))
#define ip4_addr_cmp(addr1, addr2) ((addr1)->addr == (addr2)->addr)

#define ip4_addr_isany_val(addr1)   ((addr1).addr == IPADDR_ANY)
#define ip4_addr_isany(addr1) ((addr1) == NULL || ip4_addr_isany_val(*(addr1)))

#define ip4_addr_isbroadcast(addr1, netif) ip4_addr_isbroadcast_u32((addr1)->addr, netif)
u8_t ip4_addr_isbroadcast_u32(u32_t addr, const struct netif *netif);

#define ip_addr_netmask_valid(netmask) ip4_addr_netmask_valid((netmask)->addr)
u8_t ip4_addr_netmask_valid(u32_t netmask);

#define ip4_addr_ismulticast(addr1) (((addr1)->addr & PP_HTONL(0xf0000000UL)) == PP_HTONL(0xe0000000UL))

#define ip4_addr_islinklocal(addr1) (((addr1)->addr & PP_HTONL(0xffff0000UL)) == PP_HTONL(0xa9fe0000UL))

#define ip4_addr_debug_print_parts(debug, a, b, c, d) \
  LWIP_DEBUGF(debug, ("%" U16_F ".%" U16_F ".%" U16_F ".%" U16_F, a, b, c, d))
#define ip4_addr_debug_print(debug, ipaddr) \
  ip4_addr_debug_print_parts(debug, \
                      (u16_t)((ipaddr) != NULL ? ip4_addr1_16(ipaddr) : 0),       \
                      (u16_t)((ipaddr) != NULL ? ip4_addr2_16(ipaddr) : 0),       \
                      (u16_t)((ipaddr) != NULL ? ip4_addr3_16(ipaddr) : 0),       \
                      (u16_t)((ipaddr) != NULL ? ip4_addr4_16(ipaddr) : 0))
#define ip4_addr_debug_print_val(debug, ipaddr) \
  ip4_addr_debug_print_parts(debug, \
                      ip4_addr1_16_val(ipaddr),       \
                      ip4_addr2_16_val(ipaddr),       \
                      ip4_addr3_16_val(ipaddr),       \
                      ip4_addr4_16_val(ipaddr))

/* 从4字节地址中获取一个字节*/
#define ip4_addr_get_byte(ipaddr, idx) (((const u8_t*)(&(ipaddr)->addr))[idx])
#define ip4_addr1(ipaddr) ip4_addr_get_byte(ipaddr, 0)
#define ip4_addr2(ipaddr) ip4_addr_get_byte(ipaddr, 1)
#define ip4_addr3(ipaddr) ip4_addr_get_byte(ipaddr, 2)
#define ip4_addr4(ipaddr) ip4_addr_get_byte(ipaddr, 3)
/* 从4字节地址中获取一个字节，但参数是“ip4_addr_t”，而不是指针*/
#define ip4_addr_get_byte_val(ipaddr, idx) ((u8_t)(((ipaddr).addr >> (idx * 8)) & 0xff))
#define ip4_addr1_val(ipaddr) ip4_addr_get_byte_val(ipaddr, 0)
#define ip4_addr2_val(ipaddr) ip4_addr_get_byte_val(ipaddr, 1)
#define ip4_addr3_val(ipaddr) ip4_addr_get_byte_val(ipaddr, 2)
#define ip4_addr4_val(ipaddr) ip4_addr_get_byte_val(ipaddr, 3)
/* 它们被强制转换为u16_t，目的是它们通常是使用cc.h中的u16_F格式打印F的参数。*/
#define ip4_addr1_16(ipaddr) ((u16_t)ip4_addr1(ipaddr))
#define ip4_addr2_16(ipaddr) ((u16_t)ip4_addr2(ipaddr))
#define ip4_addr3_16(ipaddr) ((u16_t)ip4_addr3(ipaddr))
#define ip4_addr4_16(ipaddr) ((u16_t)ip4_addr4(ipaddr))
#define ip4_addr1_16_val(ipaddr) ((u16_t)ip4_addr1_val(ipaddr))
#define ip4_addr2_16_val(ipaddr) ((u16_t)ip4_addr2_val(ipaddr))
#define ip4_addr3_16_val(ipaddr) ((u16_t)ip4_addr3_val(ipaddr))
#define ip4_addr4_16_val(ipaddr) ((u16_t)ip4_addr4_val(ipaddr))

#define IP4ADDR_STRLEN_MAX  16

/**为了向后兼容*/
#define ip_ntoa(ipaddr)  ipaddr_ntoa(ipaddr)

u32_t ipaddr_addr(const char *cp);
int ip4addr_aton(const char *cp, ip4_addr_t *addr);
/**将ptr返回到静态缓冲区；不可重入！*/
char *ip4addr_ntoa(const ip4_addr_t *addr);
char *ip4addr_ntoa_r(const ip4_addr_t *addr, char *buf, int buflen);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV4 */

#endif /* LWIP_HDR_IP_ADDR_H */

