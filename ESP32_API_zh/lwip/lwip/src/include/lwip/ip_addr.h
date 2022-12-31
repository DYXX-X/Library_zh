/**
 * @file IP地址API（通用IPv4和IPv6）
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
#ifndef LWIP_HDR_IP_ADDR_H
#define LWIP_HDR_IP_ADDR_H

#include "lwip/opt.h"
#include "lwip/def.h"

#include "lwip/ip4_addr.h"
#include "lwip/ip6_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup IP_addr_t中使用的ipaddr IP地址类型。类型成员。
 * @see tcp_new_ip_type（）、udp_new_ip_type（）、raw_new_ip-type（）。
 */
enum lwip_ip_addr_type {
  /**IPv4*/
  IPADDR_TYPE_V4 =   0U,
  /**IPv6协议*/
  IPADDR_TYPE_V6 =   6U,
  /**IPv4+IPv6（“双堆栈”）*/
  IPADDR_TYPE_ANY = 46U
};

#if LWIP_IPV4 && LWIP_IPV6
/**
 * @ingroup ipaddr两个IP版本地址的联合结构。注意：添加IPv6地址范围时要注意其大小！
 */
typedef struct ip_addr {
  union {
    ip6_addr_t ip6;
    ip4_addr_t ip4;
  } u_addr;
  /**@ref lwip_ip_addr_type*/
  u8_t type;
} ip_addr_t;

extern const ip_addr_t ip_addr_any_type;

/**@ingroup ip4地址*/
#define IPADDR4_INIT(u32val)          { { { { u32val, 0ul, 0ul, 0ul } IPADDR6_ZONE_INIT } }, IPADDR_TYPE_V4 }
/**@ingroup ip4地址*/
#define IPADDR4_INIT_BYTES(a,b,c,d)   IPADDR4_INIT(PP_HTONL(LWIP_MAKEU32(a,b,c,d)))

/**@ingroup ip6addr*/
#define IPADDR6_INIT(a, b, c, d)      { { { { a, b, c, d } IPADDR6_ZONE_INIT } }, IPADDR_TYPE_V6 }
/**@ingroup ip6addr*/
#define IPADDR6_INIT_HOST(a, b, c, d) { { { { PP_HTONL(a), PP_HTONL(b), PP_HTONL(c), PP_HTONL(d) } IPADDR6_ZONE_INIT } }, IPADDR_TYPE_V6 }

/**@ingroup ipaddr*/
#define IP_IS_ANY_TYPE_VAL(ipaddr)    (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_ANY)
/**@ingroup ipaddr*/
#define IPADDR_ANY_TYPE_INIT          { { { { 0ul, 0ul, 0ul, 0ul } IPADDR6_ZONE_INIT } }, IPADDR_TYPE_ANY }

/**@ingroup ip4地址*/
#define IP_IS_V4_VAL(ipaddr)          (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V4)
/**@ingroup ip6addr*/
#define IP_IS_V6_VAL(ipaddr)          (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V6)
/**@ingroup ip4地址*/
#define IP_IS_V4(ipaddr)              (((ipaddr) == NULL) || IP_IS_V4_VAL(*(ipaddr)))
/**@ingroup ip6addr*/
#define IP_IS_V6(ipaddr)              (((ipaddr) != NULL) && IP_IS_V6_VAL(*(ipaddr)))

#define IP_SET_TYPE_VAL(ipaddr, iptype) do { (ipaddr).type = (iptype); }while(0)
#define IP_SET_TYPE(ipaddr, iptype)     do { if((ipaddr) != NULL) { IP_SET_TYPE_VAL(*(ipaddr), iptype); }}while(0)
#define IP_GET_TYPE(ipaddr)           ((ipaddr)->type)

#define IP_ADDR_RAW_SIZE(ipaddr)      (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V4 ? sizeof(ip4_addr_t) : sizeof(ip6_addr_t))

#define IP_ADDR_PCB_VERSION_MATCH_EXACT(pcb, ipaddr) (IP_GET_TYPE(&pcb->local_ip) == IP_GET_TYPE(ipaddr))
#define IP_ADDR_PCB_VERSION_MATCH(pcb, ipaddr) (IP_IS_ANY_TYPE_VAL(pcb->local_ip) || IP_ADDR_PCB_VERSION_MATCH_EXACT(pcb, ipaddr))

/** @ingroup ip6addr将通用ip地址转换为特定的协议版本
 */
#define ip_2_ip6(ipaddr)   (&((ipaddr)->u_addr.ip6))
/** @ingroup ip4addr将通用ip地址转换为特定的协议版本
 */
#define ip_2_ip4(ipaddr)   (&((ipaddr)->u_addr.ip4))

/**@ingroup ip4地址*/
#define IP_ADDR4(ipaddr,a,b,c,d)      do { IP4_ADDR(ip_2_ip4(ipaddr),a,b,c,d); \
                                           IP_SET_TYPE_VAL(*(ipaddr), IPADDR_TYPE_V4); } while(0)
/**@ingroup ip6addr*/
#define IP_ADDR6(ipaddr,i0,i1,i2,i3)  do { IP6_ADDR(ip_2_ip6(ipaddr),i0,i1,i2,i3); \
                                           IP_SET_TYPE_VAL(*(ipaddr), IPADDR_TYPE_V6); } while(0)
/**@ingroup ip6addr*/
#define IP_ADDR6_HOST(ipaddr,i0,i1,i2,i3)  IP_ADDR6(ipaddr,PP_HTONL(i0),PP_HTONL(i1),PP_HTONL(i2),PP_HTONL(i3))

#define ip_clear_no4(ipaddr)  do { ip_2_ip6(ipaddr)->addr[1] = \
                                   ip_2_ip6(ipaddr)->addr[2] = \
                                   ip_2_ip6(ipaddr)->addr[3] = 0; \
                                   ip6_addr_clear_zone(ip_2_ip6(ipaddr)); }while(0)

#if ESP_IPV6
#define IP_V6_EQ_PART(ipaddr, WORD, VAL) (ip_2_ip6(ipaddr)->addr[WORD] == htonl(VAL))
#define IP_IS_V4MAPPEDV6(ipaddr) (IP_IS_V6(ipaddr) && IP_V6_EQ_PART(ipaddr, 0, 0) && IP_V6_EQ_PART(ipaddr, 1, 0) && IP_V6_EQ_PART(ipaddr, 2, 0x0000FFFF))
#endif

/**@ingroup ipaddr*/
#define ip_addr_copy(dest, src)      do{ IP_SET_TYPE_VAL(dest, IP_GET_TYPE(&src)); if(IP_IS_V6_VAL(src)){ \
  ip6_addr_copy(*ip_2_ip6(&(dest)), *ip_2_ip6(&(src))); }else{ \
  ip4_addr_copy(*ip_2_ip4(&(dest)), *ip_2_ip4(&(src))); ip_clear_no4(&dest); }}while(0)
/**@ingroup ip6addr*/
#define ip_addr_copy_from_ip6(dest, src)      do{ \
  ip6_addr_copy(*ip_2_ip6(&(dest)), src); IP_SET_TYPE_VAL(dest, IPADDR_TYPE_V6); }while(0)
/**@ingroup ip6addr*/
#define ip_addr_copy_from_ip6_packed(dest, src)      do{ \
  ip6_addr_copy_from_packed(*ip_2_ip6(&(dest)), src); IP_SET_TYPE_VAL(dest, IPADDR_TYPE_V6); }while(0)
/**@ingroup ip4地址*/
#define ip_addr_copy_from_ip4(dest, src)      do{ \
  ip4_addr_copy(*ip_2_ip4(&(dest)), src); IP_SET_TYPE_VAL(dest, IPADDR_TYPE_V4); ip_clear_no4(&dest); }while(0)
/**@ingroup ip4地址*/
#define ip_addr_set_ip4_u32(ipaddr, val)  do{if(ipaddr){ip4_addr_set_u32(ip_2_ip4(ipaddr), val); \
  IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); ip_clear_no4(ipaddr); }}while(0)
/**@ingroup ip4地址*/
#define ip_addr_set_ip4_u32_val(ipaddr, val)  do{ ip4_addr_set_u32(ip_2_ip4(&(ipaddr)), val); \
  IP_SET_TYPE_VAL(ipaddr, IPADDR_TYPE_V4); ip_clear_no4(&ipaddr); }while(0)
/**@ingroup ip4地址*/
#define ip_addr_get_ip4_u32(ipaddr)  (((ipaddr) && IP_IS_V4(ipaddr)) ? \
  ip4_addr_get_u32(ip_2_ip4(ipaddr)) : 0)
/**@ingroup ipaddr*/
#define ip_addr_set(dest, src) do{ IP_SET_TYPE(dest, IP_GET_TYPE(src)); if(IP_IS_V6(src)){ \
  ip6_addr_set(ip_2_ip6(dest), ip_2_ip6(src)); }else{ \
  ip4_addr_set(ip_2_ip4(dest), ip_2_ip4(src)); ip_clear_no4(dest); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_set_ipaddr(dest, src) ip_addr_set(dest, src)
/**@ingroup ipaddr*/
#define ip_addr_set_zero(ipaddr)     do{ \
  ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, 0); }while(0)
/**@ingroup ip5addr*/
#define ip_addr_set_zero_ip4(ipaddr)     do{ \
  ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }while(0)
/**@ingroup ip6addr*/
#define ip_addr_set_zero_ip6(ipaddr)     do{ \
  ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }while(0)
/**@ingroup ipaddr*/
#define ip_addr_set_any(is_ipv6, ipaddr)      do{if(is_ipv6){ \
  ip6_addr_set_any(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_any(ip_2_ip4(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); ip_clear_no4(ipaddr); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_set_any_val(is_ipv6, ipaddr)      do{if(is_ipv6){ \
  ip6_addr_set_any(ip_2_ip6(&(ipaddr))); IP_SET_TYPE_VAL(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_any(ip_2_ip4(&(ipaddr))); IP_SET_TYPE_VAL(ipaddr, IPADDR_TYPE_V4); ip_clear_no4(&ipaddr); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_set_loopback(is_ipv6, ipaddr) do{if(is_ipv6){ \
  ip6_addr_set_loopback(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_loopback(ip_2_ip4(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); ip_clear_no4(ipaddr); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_set_loopback_val(is_ipv6, ipaddr) do{if(is_ipv6){ \
  ip6_addr_set_loopback(ip_2_ip6(&(ipaddr))); IP_SET_TYPE_VAL(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_loopback(ip_2_ip4(&(ipaddr))); IP_SET_TYPE_VAL(ipaddr, IPADDR_TYPE_V4); ip_clear_no4(&ipaddr); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_set_hton(dest, src)  do{if(IP_IS_V6(src)){ \
  ip6_addr_set_hton(ip_2_ip6(dest), ip_2_ip6(src)); IP_SET_TYPE(dest, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_hton(ip_2_ip4(dest), ip_2_ip4(src)); IP_SET_TYPE(dest, IPADDR_TYPE_V4); ip_clear_no4(ipaddr); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_get_network(target, host, netmask) do{if(IP_IS_V6(host)){ \
  ip4_addr_set_zero(ip_2_ip4(target)); IP_SET_TYPE(target, IPADDR_TYPE_V6); } else { \
  ip4_addr_get_network(ip_2_ip4(target), ip_2_ip4(host), ip_2_ip4(netmask)); IP_SET_TYPE(target, IPADDR_TYPE_V4); }}while(0)
/**@ingroup ipaddr*/
#define ip_addr_netcmp(addr1, addr2, mask) ((IP_IS_V6(addr1) && IP_IS_V6(addr2)) ? \
  0 : \
  ip4_addr_netcmp(ip_2_ip4(addr1), ip_2_ip4(addr2), mask))
/**@ingroup ipaddr*/
#define ip_addr_cmp(addr1, addr2)    ((IP_GET_TYPE(addr1) != IP_GET_TYPE(addr2)) ? 0 : (IP_IS_V6_VAL(*(addr1)) ? \
  ip6_addr_cmp(ip_2_ip6(addr1), ip_2_ip6(addr2)) : \
  ip4_addr_cmp(ip_2_ip4(addr1), ip_2_ip4(addr2))))
/**@ingroup ipaddr*/
#define ip_addr_cmp_zoneless(addr1, addr2)    ((IP_GET_TYPE(addr1) != IP_GET_TYPE(addr2)) ? 0 : (IP_IS_V6_VAL(*(addr1)) ? \
  ip6_addr_cmp_zoneless(ip_2_ip6(addr1), ip_2_ip6(addr2)) : \
  ip4_addr_cmp(ip_2_ip4(addr1), ip_2_ip4(addr2))))
/**@ingroup ipaddr*/
#define ip_addr_isany(ipaddr)        (((ipaddr) == NULL) ? 1 : ((IP_IS_V6(ipaddr)) ? \
  ip6_addr_isany(ip_2_ip6(ipaddr)) : \
  ip4_addr_isany(ip_2_ip4(ipaddr))))
/**@ingroup ipaddr*/
#define ip_addr_isany_val(ipaddr)        ((IP_IS_V6_VAL(ipaddr)) ? \
  ip6_addr_isany_val(*ip_2_ip6(&(ipaddr))) : \
  ip4_addr_isany_val(*ip_2_ip4(&(ipaddr))))
/**@ingroup ipaddr*/
#define ip_addr_isbroadcast(ipaddr, netif) ((IP_IS_V6(ipaddr)) ? \
  0 : \
  ip4_addr_isbroadcast(ip_2_ip4(ipaddr), netif))
/**@ingroup ipaddr*/
#define ip_addr_ismulticast(ipaddr)  ((IP_IS_V6(ipaddr)) ? \
  ip6_addr_ismulticast(ip_2_ip6(ipaddr)) : \
  ip4_addr_ismulticast(ip_2_ip4(ipaddr)))
/**@ingroup ipaddr*/
#define ip_addr_isloopback(ipaddr)  ((IP_IS_V6(ipaddr)) ? \
  ip6_addr_isloopback(ip_2_ip6(ipaddr)) : \
  ip4_addr_isloopback(ip_2_ip4(ipaddr)))
/**@ingroup ipaddr*/
#define ip_addr_islinklocal(ipaddr)  ((IP_IS_V6(ipaddr)) ? \
  ip6_addr_islinklocal(ip_2_ip6(ipaddr)) : \
  ip4_addr_islinklocal(ip_2_ip4(ipaddr)))
#define ip_addr_debug_print(debug, ipaddr) do { if(IP_IS_V6(ipaddr)) { \
  ip6_addr_debug_print(debug, ip_2_ip6(ipaddr)); } else { \
  ip4_addr_debug_print(debug, ip_2_ip4(ipaddr)); }}while(0)
#define ip_addr_debug_print_val(debug, ipaddr) do { if(IP_IS_V6_VAL(ipaddr)) { \
  ip6_addr_debug_print_val(debug, *ip_2_ip6(&(ipaddr))); } else { \
  ip4_addr_debug_print_val(debug, *ip_2_ip4(&(ipaddr))); }}while(0)
char *ipaddr_ntoa(const ip_addr_t *addr);
char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen);
int ipaddr_aton(const char *cp, ip_addr_t *addr);

/**@ingroup ipaddr*/
#define IPADDR_STRLEN_MAX   IP6ADDR_STRLEN_MAX

/**@ingroup ipaddr*/
#define ip4_2_ipv4_mapped_ipv6(ip6addr, ip4addr) do { \
  (ip6addr)->addr[3] = (ip4addr)->addr; \
  (ip6addr)->addr[2] = PP_HTONL(0x0000FFFFUL); \
  (ip6addr)->addr[1] = 0; \
  (ip6addr)->addr[0] = 0; \
  ip6_addr_clear_zone(ip6addr); } while(0);

/**@ingroup ipaddr*/
#define unmap_ipv4_mapped_ipv6(ip4addr, ip6addr) \
  (ip4addr)->addr = (ip6addr)->addr[3];

#define IP46_ADDR_ANY(type) (((type) == IPADDR_TYPE_V6)? IP6_ADDR_ANY : IP4_ADDR_ANY)

#else /* LWIP_IPV4 && LWIP_IPV6 */

#define IP_ADDR_PCB_VERSION_MATCH(addr, pcb)          1
#define IP_ADDR_PCB_VERSION_MATCH_EXACT(pcb, ipaddr)  1

#define ip_addr_set_any_val(is_ipv6, ipaddr)          ip_addr_set_any(is_ipv6, &(ipaddr))
#define ip_addr_set_loopback_val(is_ipv6, ipaddr)     ip_addr_set_loopback(is_ipv6, &(ipaddr))

#if LWIP_IPV4

typedef ip4_addr_t ip_addr_t;
#define IPADDR4_INIT(u32val)                    { u32val }
#define IPADDR4_INIT_BYTES(a,b,c,d)             IPADDR4_INIT(PP_HTONL(LWIP_MAKEU32(a,b,c,d)))
#define IP_IS_V4_VAL(ipaddr)                    1
#define IP_IS_V6_VAL(ipaddr)                    0
#define IP_IS_V4(ipaddr)                        1
#define IP_IS_V6(ipaddr)                        0
#define IP_IS_ANY_TYPE_VAL(ipaddr)              0
#define IP_SET_TYPE_VAL(ipaddr, iptype)
#define IP_SET_TYPE(ipaddr, iptype)
#define IP_GET_TYPE(ipaddr)                     IPADDR_TYPE_V4
#define IP_ADDR_RAW_SIZE(ipaddr)                sizeof(ip4_addr_t)
#define ip_2_ip4(ipaddr)                        (ipaddr)
#define IP_ADDR4(ipaddr,a,b,c,d)                IP4_ADDR(ipaddr,a,b,c,d)

#define ip_addr_copy(dest, src)                 ip4_addr_copy(dest, src)
#define ip_addr_copy_from_ip4(dest, src)        ip4_addr_copy(dest, src)
#define ip_addr_set_ip4_u32(ipaddr, val)        ip4_addr_set_u32(ip_2_ip4(ipaddr), val)
#define ip_addr_set_ip4_u32_val(ipaddr, val)    ip_addr_set_ip4_u32(&(ipaddr), val)
#define ip_addr_get_ip4_u32(ipaddr)             ip4_addr_get_u32(ip_2_ip4(ipaddr))
#define ip_addr_set(dest, src)                  ip4_addr_set(dest, src)
#define ip_addr_set_ipaddr(dest, src)           ip4_addr_set(dest, src)
#define ip_addr_set_zero(ipaddr)                ip4_addr_set_zero(ipaddr)
#define ip_addr_set_zero_ip4(ipaddr)            ip4_addr_set_zero(ipaddr)
#define ip_addr_set_any(is_ipv6, ipaddr)        ip4_addr_set_any(ipaddr)
#define ip_addr_set_loopback(is_ipv6, ipaddr)   ip4_addr_set_loopback(ipaddr)
#define ip_addr_set_hton(dest, src)             ip4_addr_set_hton(dest, src)
#define ip_addr_get_network(target, host, mask) ip4_addr_get_network(target, host, mask)
#define ip_addr_netcmp(addr1, addr2, mask)      ip4_addr_netcmp(addr1, addr2, mask)
#define ip_addr_cmp(addr1, addr2)               ip4_addr_cmp(addr1, addr2)
#define ip_addr_isany(ipaddr)                   ip4_addr_isany(ipaddr)
#define ip_addr_isany_val(ipaddr)               ip4_addr_isany_val(ipaddr)
#define ip_addr_isloopback(ipaddr)              ip4_addr_isloopback(ipaddr)
#define ip_addr_islinklocal(ipaddr)             ip4_addr_islinklocal(ipaddr)
#define ip_addr_isbroadcast(addr, netif)        ip4_addr_isbroadcast(addr, netif)
#define ip_addr_ismulticast(ipaddr)             ip4_addr_ismulticast(ipaddr)
#define ip_addr_debug_print(debug, ipaddr)      ip4_addr_debug_print(debug, ipaddr)
#define ip_addr_debug_print_val(debug, ipaddr)  ip4_addr_debug_print_val(debug, ipaddr)
#define ipaddr_ntoa(ipaddr)                     ip4addr_ntoa(ipaddr)
#define ipaddr_ntoa_r(ipaddr, buf, buflen)      ip4addr_ntoa_r(ipaddr, buf, buflen)
#define ipaddr_aton(cp, addr)                   ip4addr_aton(cp, addr)

#define IPADDR_STRLEN_MAX   IP4ADDR_STRLEN_MAX

#define IP46_ADDR_ANY(type) (IP4_ADDR_ANY)

#else /* LWIP_IPV4 */

typedef ip6_addr_t ip_addr_t;
#define IPADDR6_INIT(a, b, c, d)                { { a, b, c, d } IPADDR6_ZONE_INIT }
#define IPADDR6_INIT_HOST(a, b, c, d)           { { PP_HTONL(a), PP_HTONL(b), PP_HTONL(c), PP_HTONL(d) } IPADDR6_ZONE_INIT }
#define IP_IS_V4_VAL(ipaddr)                    0
#define IP_IS_V6_VAL(ipaddr)                    1
#define IP_IS_V4(ipaddr)                        0
#define IP_IS_V6(ipaddr)                        1
#define IP_IS_ANY_TYPE_VAL(ipaddr)              0
#define IP_SET_TYPE_VAL(ipaddr, iptype)
#define IP_SET_TYPE(ipaddr, iptype)
#define IP_GET_TYPE(ipaddr)                     IPADDR_TYPE_V6
#define IP_ADDR_RAW_SIZE(ipaddr)                sizeof(ip6_addr_t)
#define ip_2_ip6(ipaddr)                        (ipaddr)
#define IP_ADDR6(ipaddr,i0,i1,i2,i3)            IP6_ADDR(ipaddr,i0,i1,i2,i3)
#define IP_ADDR6_HOST(ipaddr,i0,i1,i2,i3)       IP_ADDR6(ipaddr,PP_HTONL(i0),PP_HTONL(i1),PP_HTONL(i2),PP_HTONL(i3))

#define ip_addr_copy(dest, src)                 ip6_addr_copy(dest, src)
#define ip_addr_copy_from_ip6(dest, src)        ip6_addr_copy(dest, src)
#define ip_addr_copy_from_ip6_packed(dest, src) ip6_addr_copy_from_packed(dest, src)
#define ip_addr_set(dest, src)                  ip6_addr_set(dest, src)
#define ip_addr_set_ipaddr(dest, src)           ip6_addr_set(dest, src)
#define ip_addr_set_zero(ipaddr)                ip6_addr_set_zero(ipaddr)
#define ip_addr_set_zero_ip6(ipaddr)            ip6_addr_set_zero(ipaddr)
#define ip_addr_set_any(is_ipv6, ipaddr)        ip6_addr_set_any(ipaddr)
#define ip_addr_set_loopback(is_ipv6, ipaddr)   ip6_addr_set_loopback(ipaddr)
#define ip_addr_set_hton(dest, src)             ip6_addr_set_hton(dest, src)
#define ip_addr_get_network(target, host, mask) ip6_addr_set_zero(target)
#define ip_addr_netcmp(addr1, addr2, mask)      0
#define ip_addr_cmp(addr1, addr2)               ip6_addr_cmp(addr1, addr2)
#define ip_addr_cmp_zoneless(addr1, addr2)      ip6_addr_cmp_zoneless(addr1, addr2)
#define ip_addr_isany(ipaddr)                   ip6_addr_isany(ipaddr)
#define ip_addr_isany_val(ipaddr)               ip6_addr_isany_val(ipaddr)
#define ip_addr_isloopback(ipaddr)              ip6_addr_isloopback(ipaddr)
#define ip_addr_islinklocal(ipaddr)             ip6_addr_islinklocal(ipaddr)
#define ip_addr_isbroadcast(addr, netif)        0
#define ip_addr_ismulticast(ipaddr)             ip6_addr_ismulticast(ipaddr)
#define ip_addr_debug_print(debug, ipaddr)      ip6_addr_debug_print(debug, ipaddr)
#define ip_addr_debug_print_val(debug, ipaddr)  ip6_addr_debug_print_val(debug, ipaddr)
#define ipaddr_ntoa(ipaddr)                     ip6addr_ntoa(ipaddr)
#define ipaddr_ntoa_r(ipaddr, buf, buflen)      ip6addr_ntoa_r(ipaddr, buf, buflen)
#define ipaddr_aton(cp, addr)                   ip6addr_aton(cp, addr)

#define IPADDR_STRLEN_MAX   IP6ADDR_STRLEN_MAX

#define IP46_ADDR_ANY(type) (IP6_ADDR_ANY)

#endif /* LWIP_IPV4 */
#endif /* LWIP_IPV4 && LWIP_IPV6 */

#if LWIP_IPV4

extern const ip_addr_t ip_addr_any;
extern const ip_addr_t ip_addr_broadcast;

/**
 * @ingroup ip4addr可以用作ip通配符的固定/常量ip_addr_t。
 * Defined to @ref 启用IPv4时为IP4_ADDR_ANY。
 * Defined to @ref 仅IPv6系统中的IP6_ADDR_ANY。如果可以处理IPv4 _AND_ IPv6地址，请使用此选项。
 * Use @ref IP类型重要时，IP4_ADDR_ANY或@ref IP6_ADDR_ANY。
 */
#define IP_ADDR_ANY         IP4_ADDR_ANY
/**
 * @ingroup ip4addr可以用作IPv4通配符和广播地址的固定/常量ip_addr_t
 */
#define IP4_ADDR_ANY        (&ip_addr_any)
/**
 * @ingroup ip4addr可以用作通配符和广播地址的固定/常量ip4_addr_t
 */
#define IP4_ADDR_ANY4       (ip_2_ip4(&ip_addr_any))

/**@ingroup ip4地址*/
#define IP_ADDR_BROADCAST   (&ip_addr_broadcast)
/**@ingroup ip4地址*/
#define IP4_ADDR_BROADCAST  (ip_2_ip4(&ip_addr_broadcast))

#endif /* LWIP_IPV4*/

#if LWIP_IPV6

extern const ip_addr_t ip6_addr_any;

/** 
 * @ingroup ip6addr IP6_ADDR_ANY可以用作IPv6通配符地址的固定ip_ADDR_t
 */
#define IP6_ADDR_ANY   (&ip6_addr_any)
/**
 * @ingroup ip6addr IP6_ADDR_ANY6可以用作IPv6通配符地址的固定IP6_ADDR_t
 */
#define IP6_ADDR_ANY6  (ip_2_ip6(&ip6_addr_any))

#if !LWIP_IPV4
/**仅IPv6配置*/
#define IP_ADDR_ANY IP6_ADDR_ANY
#endif /* !LWIP_IPV4 */

#endif

#if LWIP_IPV4 && LWIP_IPV6
/**@ingroup ipaddr*/
#define IP_ANY_TYPE    (&ip_addr_any_type)
#else
#define IP_ANY_TYPE    IP_ADDR_ANY
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_IP_ADDR_H */

