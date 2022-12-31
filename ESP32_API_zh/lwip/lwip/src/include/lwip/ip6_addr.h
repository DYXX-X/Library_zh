/**
 * @file
 *
 * IPv6地址。
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
 * 用于处理IPv6地址的结构和宏。
 *
 * 请与Ivan Delamer协调变更和请求
 * <delamer@inicotech.com>
 */
#ifndef LWIP_HDR_IP6_ADDR_H
#define LWIP_HDR_IP6_ADDR_H

#include "lwip/opt.h"
#include "def.h"

#if LWIP_IPV6  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/ip6_zone.h"

#ifdef __cplusplus
extern "C" {
#endif


/**这是ip6_addr_t的对齐版本，用作堆栈上的局部变量等。*/
struct ip6_addr {
  u32_t addr[4];
#if LWIP_IPV6_SCOPES
  u8_t zone;
#endif /* LWIP_IPV6_SCOPES */
};

/**IPv6地址*/
typedef struct ip6_addr ip6_addr_t;

/**设置由字节部分给定的IPv6部分地址*/
#define IP6_ADDR_PART(ip6addr, index, a,b,c,d) \
  (ip6addr)->addr[index] = PP_HTONL(LWIP_MAKEU32(a,b,c,d))

/**通过按网络字节顺序传递4个u32_t索引来设置完整的IPv6地址（常数使用PP_HTONL（））*/
#define IP6_ADDR(ip6addr, idx0, idx1, idx2, idx3) do { \
  (ip6addr)->addr[0] = idx0; \
  (ip6addr)->addr[1] = idx1; \
  (ip6addr)->addr[2] = idx2; \
  (ip6addr)->addr[3] = idx3; \
  ip6_addr_clear_zone(ip6addr); } while(0)

/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK1(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[0]) >> 16) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK2(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[0])) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK3(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[1]) >> 16) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK4(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[1])) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK5(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[2]) >> 16) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK6(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[2])) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK7(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[3]) >> 16) & 0xffff))
/**16位块中的访问地址*/
#define IP6_ADDR_BLOCK8(ip6addr) ((u16_t)((lwip_htonl((ip6addr)->addr[3])) & 0xffff))

/**复制IPv6地址-比ip6_addr_set更快：无NULL检查*/
#define ip6_addr_copy(dest, src) do{(dest).addr[0] = (src).addr[0]; \
                                    (dest).addr[1] = (src).addr[1]; \
                                    (dest).addr[2] = (src).addr[2]; \
                                    (dest).addr[3] = (src).addr[3]; \
                                    ip6_addr_copy_zone((dest), (src)); }while(0)
/**安全地将一个IPv6地址复制到另一个（src可能为NULL）*/
#define ip6_addr_set(dest, src) do{(dest)->addr[0] = (src) == NULL ? 0 : (src)->addr[0]; \
                                   (dest)->addr[1] = (src) == NULL ? 0 : (src)->addr[1]; \
                                   (dest)->addr[2] = (src) == NULL ? 0 : (src)->addr[2]; \
                                   (dest)->addr[3] = (src) == NULL ? 0 : (src)->addr[3]; \
                                   ip6_addr_set_zone((dest), (src) == NULL ? IP6_NO_ZONE : ip6_addr_zone(src)); }while(0)

/**将打包IPv6地址复制到未打包IPv6地址；未设置区域*/
#define ip6_addr_copy_from_packed(dest, src) do{(dest).addr[0] = (src).addr[0]; \
                                    (dest).addr[1] = (src).addr[1]; \
                                    (dest).addr[2] = (src).addr[2]; \
                                    (dest).addr[3] = (src).addr[3]; \
                                    ip6_addr_clear_zone(&dest); }while(0)

/**将解包的IPv6地址复制到打包的IPv6地址；区域已丢失*/
#define ip6_addr_copy_to_packed(dest, src) do{(dest).addr[0] = (src).addr[0]; \
                                    (dest).addr[1] = (src).addr[1]; \
                                    (dest).addr[2] = (src).addr[2]; \
                                    (dest).addr[3] = (src).addr[3]; }while(0)

/**将完整地址设置为零*/
#define ip6_addr_set_zero(ip6addr)    do{(ip6addr)->addr[0] = 0; \
                                         (ip6addr)->addr[1] = 0; \
                                         (ip6addr)->addr[2] = 0; \
                                         (ip6addr)->addr[3] = 0; \
                                         ip6_addr_clear_zone(ip6addr);}while(0)

/**将地址设置为ipv6“any”（不需要lwip_htonl（））*/
#define ip6_addr_set_any(ip6addr)       ip6_addr_set_zero(ip6addr)
/**将地址设置为ipv6环回地址*/
#define ip6_addr_set_loopback(ip6addr) do{(ip6addr)->addr[0] = 0; \
                                          (ip6addr)->addr[1] = 0; \
                                          (ip6addr)->addr[2] = 0; \
                                          (ip6addr)->addr[3] = PP_HTONL(0x00000001UL); \
                                          ip6_addr_clear_zone(ip6addr);}while(0)
/**安全地将一个IPv6地址复制到另一个，并将字节顺序从主机更改为网络顺序。*/
#define ip6_addr_set_hton(dest, src) do{(dest)->addr[0] = (src) == NULL ? 0 : lwip_htonl((src)->addr[0]); \
                                        (dest)->addr[1] = (src) == NULL ? 0 : lwip_htonl((src)->addr[1]); \
                                        (dest)->addr[2] = (src) == NULL ? 0 : lwip_htonl((src)->addr[2]); \
                                        (dest)->addr[3] = (src) == NULL ? 0 : lwip_htonl((src)->addr[3]); \
                                        ip6_addr_set_zone((dest), (src) == NULL ? IP6_NO_ZONE : ip6_addr_zone(src));}while(0)


/**比较IPv6网络，忽略区域信息。节约使用！*/
#define ip6_addr_netcmp_zoneless(addr1, addr2) (((addr1)->addr[0] == (addr2)->addr[0]) && \
                                               ((addr1)->addr[1] == (addr2)->addr[1]))

/**
 * 确定两个IPv6地址是否位于同一网络上。
 *
 * @param addr1 IPv6地址1
 * @param addr2 IPv6地址2
 * @return 如果两个地址的网络标识符匹配，则为1；如果不匹配，则0
 */
#define ip6_addr_netcmp(addr1, addr2) (ip6_addr_netcmp_zoneless((addr1), (addr2)) && \
                                       ip6_addr_cmp_zone((addr1), (addr2)))

/* 为了提高效率，在*ip6_addr_netcmp（）之后进行了精确的主机比较。*/
#define ip6_addr_nethostcmp(addr1, addr2) (((addr1)->addr[2] == (addr2)->addr[2]) && \
                                           ((addr1)->addr[3] == (addr2)->addr[3]))

/**比较IPv6地址，忽略区域信息。节约使用！*/
#define ip6_addr_cmp_zoneless(addr1, addr2) (((addr1)->addr[0] == (addr2)->addr[0]) && \
                                    ((addr1)->addr[1] == (addr2)->addr[1]) && \
                                    ((addr1)->addr[2] == (addr2)->addr[2]) && \
                                    ((addr1)->addr[3] == (addr2)->addr[3]))
/**
 * 确定两个IPv6地址是否相同。特别是，两者的地址部分必须相同，并且区域必须兼容。
 *
 * @param addr1 IPv6地址1
 * @param addr2 IPv6地址2
 * @return 如果地址被认为相等，则为1，如果不相等则为0
 */
#define ip6_addr_cmp(addr1, addr2) (ip6_addr_cmp_zoneless((addr1), (addr2)) && \
                                    ip6_addr_cmp_zone((addr1), (addr2)))

/**将IPv6地址与压缩地址和区域进行比较*/
#define ip6_addr_cmp_packed(ip6addr, paddr, zone_idx) (((ip6addr)->addr[0] == (paddr)->addr[0]) && \
                                    ((ip6addr)->addr[1] == (paddr)->addr[1]) && \
                                    ((ip6addr)->addr[2] == (paddr)->addr[2]) && \
                                    ((ip6addr)->addr[3] == (paddr)->addr[3]) && \
                                    ip6_addr_equals_zone((ip6addr), (zone_idx)))

#define ip6_get_subnet_id(ip6addr)   (lwip_htonl((ip6addr)->addr[2]) & 0x0000ffffUL)

#define ip6_addr_isany_val(ip6addr) (((ip6addr).addr[0] == 0) && \
                                     ((ip6addr).addr[1] == 0) && \
                                     ((ip6addr).addr[2] == 0) && \
                                     ((ip6addr).addr[3] == 0))
#define ip6_addr_isany(ip6addr) (((ip6addr) == NULL) || ip6_addr_isany_val(*(ip6addr)))

#define ip6_addr_isloopback(ip6addr) (((ip6addr)->addr[0] == 0UL) && \
                                      ((ip6addr)->addr[1] == 0UL) && \
                                      ((ip6addr)->addr[2] == 0UL) && \
                                      ((ip6addr)->addr[3] == PP_HTONL(0x00000001UL)))

#define ip6_addr_isglobal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xe0000000UL)) == PP_HTONL(0x20000000UL))

#define ip6_addr_islinklocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xffc00000UL)) == PP_HTONL(0xfe800000UL))

#define ip6_addr_issitelocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xffc00000UL)) == PP_HTONL(0xfec00000UL))

#define ip6_addr_isuniquelocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xfe000000UL)) == PP_HTONL(0xfc000000UL))

#define ip6_addr_isipv4mappedipv6(ip6addr) (((ip6addr)->addr[0] == 0) && ((ip6addr)->addr[1] == 0) && (((ip6addr)->addr[2]) == PP_HTONL(0x0000FFFFUL)))

#define ip6_addr_ismulticast(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff000000UL)) == PP_HTONL(0xff000000UL))
#define ip6_addr_multicast_transient_flag(ip6addr)  ((ip6addr)->addr[0] & PP_HTONL(0x00100000UL))
#define ip6_addr_multicast_prefix_flag(ip6addr)     ((ip6addr)->addr[0] & PP_HTONL(0x00200000UL))
#define ip6_addr_multicast_rendezvous_flag(ip6addr) ((ip6addr)->addr[0] & PP_HTONL(0x00400000UL))
#define ip6_addr_multicast_scope(ip6addr) ((lwip_htonl((ip6addr)->addr[0]) >> 16) & 0xf)
#define IP6_MULTICAST_SCOPE_RESERVED            0x0
#define IP6_MULTICAST_SCOPE_RESERVED0           0x0
#define IP6_MULTICAST_SCOPE_INTERFACE_LOCAL     0x1
#define IP6_MULTICAST_SCOPE_LINK_LOCAL          0x2
#define IP6_MULTICAST_SCOPE_RESERVED3           0x3
#define IP6_MULTICAST_SCOPE_ADMIN_LOCAL         0x4
#define IP6_MULTICAST_SCOPE_SITE_LOCAL          0x5
#define IP6_MULTICAST_SCOPE_ORGANIZATION_LOCAL  0x8
#define IP6_MULTICAST_SCOPE_GLOBAL              0xe
#define IP6_MULTICAST_SCOPE_RESERVEDF           0xf
#define ip6_addr_ismulticast_iflocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff8f0000UL)) == PP_HTONL(0xff010000UL))
#define ip6_addr_ismulticast_linklocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff8f0000UL)) == PP_HTONL(0xff020000UL))
#define ip6_addr_ismulticast_adminlocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff8f0000UL)) == PP_HTONL(0xff040000UL))
#define ip6_addr_ismulticast_sitelocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff8f0000UL)) == PP_HTONL(0xff050000UL))
#define ip6_addr_ismulticast_orglocal(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff8f0000UL)) == PP_HTONL(0xff080000UL))
#define ip6_addr_ismulticast_global(ip6addr) (((ip6addr)->addr[0] & PP_HTONL(0xff8f0000UL)) == PP_HTONL(0xff0e0000UL))

/* 作用域说明：虽然接口本地和链路本地多播地址确实有作用域（即，它们仅在特定接口的上下文中有意义），但以下函数没有分配或比较区域索引。其原因是向后兼容。任何产生非全局多播地址的呼叫站点必须根据自身情况分配多播地址。*/

#define ip6_addr_isallnodes_iflocal(ip6addr) (((ip6addr)->addr[0] == PP_HTONL(0xff010000UL)) && \
    ((ip6addr)->addr[1] == 0UL) && \
    ((ip6addr)->addr[2] == 0UL) && \
    ((ip6addr)->addr[3] == PP_HTONL(0x00000001UL)))

#define ip6_addr_isallnodes_linklocal(ip6addr) (((ip6addr)->addr[0] == PP_HTONL(0xff020000UL)) && \
    ((ip6addr)->addr[1] == 0UL) && \
    ((ip6addr)->addr[2] == 0UL) && \
    ((ip6addr)->addr[3] == PP_HTONL(0x00000001UL)))
#define ip6_addr_set_allnodes_linklocal(ip6addr) do{(ip6addr)->addr[0] = PP_HTONL(0xff020000UL); \
                (ip6addr)->addr[1] = 0; \
                (ip6addr)->addr[2] = 0; \
                (ip6addr)->addr[3] = PP_HTONL(0x00000001UL); \
                ip6_addr_clear_zone(ip6addr); }while(0)

#define ip6_addr_isallrouters_linklocal(ip6addr) (((ip6addr)->addr[0] == PP_HTONL(0xff020000UL)) && \
    ((ip6addr)->addr[1] == 0UL) && \
    ((ip6addr)->addr[2] == 0UL) && \
    ((ip6addr)->addr[3] == PP_HTONL(0x00000002UL)))
#define ip6_addr_set_allrouters_linklocal(ip6addr) do{(ip6addr)->addr[0] = PP_HTONL(0xff020000UL); \
                (ip6addr)->addr[1] = 0; \
                (ip6addr)->addr[2] = 0; \
                (ip6addr)->addr[3] = PP_HTONL(0x00000002UL); \
                ip6_addr_clear_zone(ip6addr); }while(0)

#define ip6_addr_issolicitednode(ip6addr) ( ((ip6addr)->addr[0] == PP_HTONL(0xff020000UL)) && \
        ((ip6addr)->addr[2] == PP_HTONL(0x00000001UL)) && \
        (((ip6addr)->addr[3] & PP_HTONL(0xff000000UL)) == PP_HTONL(0xff000000UL)) )

#define ip6_addr_set_solicitednode(ip6addr, if_id) do{(ip6addr)->addr[0] = PP_HTONL(0xff020000UL); \
                (ip6addr)->addr[1] = 0; \
                (ip6addr)->addr[2] = PP_HTONL(0x00000001UL); \
                (ip6addr)->addr[3] = (PP_HTONL(0xff000000UL) | (if_id)); \
                ip6_addr_clear_zone(ip6addr); }while(0)

#define ip6_addr_cmp_solicitednode(ip6addr, sn_addr) (((ip6addr)->addr[0] == PP_HTONL(0xff020000UL)) && \
                                    ((ip6addr)->addr[1] == 0) && \
                                    ((ip6addr)->addr[2] == PP_HTONL(0x00000001UL)) && \
                                    ((ip6addr)->addr[3] == (PP_HTONL(0xff000000UL) | (sn_addr)->addr[3])))

/* IPv6地址状态。*/
#define IP6_ADDR_INVALID      0x00
#define IP6_ADDR_TENTATIVE    0x08
#define IP6_ADDR_TENTATIVE_1  0x09 /* 发送1个探针*/
#define IP6_ADDR_TENTATIVE_2  0x0a /* 发送了2个探针*/
#define IP6_ADDR_TENTATIVE_3  0x0b /* 发送了3个探针*/
#define IP6_ADDR_TENTATIVE_4  0x0c /* 发送4个探针*/
#define IP6_ADDR_TENTATIVE_5  0x0d /* 发送5个探针*/
#define IP6_ADDR_TENTATIVE_6  0x0e /* 发送6个探针*/
#define IP6_ADDR_TENTATIVE_7  0x0f /* 发送了7个探针*/
#define IP6_ADDR_VALID        0x10 /* 此位将地址标记为有效（首选或不推荐）*/
#define IP6_ADDR_PREFERRED    0x30
#define IP6_ADDR_DEPRECATED   0x10 /* 与VALID相同（有效但不首选）*/
#define IP6_ADDR_DUPLICATED   0x40 /* DAD测试失败，无效*/

#define IP6_ADDR_TENTATIVE_COUNT_MASK 0x07 /* 发送1-7个探针*/

#define ip6_addr_isinvalid(addr_state) (addr_state == IP6_ADDR_INVALID)
#define ip6_addr_istentative(addr_state) (addr_state & IP6_ADDR_TENTATIVE)
#define ip6_addr_isvalid(addr_state) (addr_state & IP6_ADDR_VALID) /* 包括有效的、首选的和不推荐的。*/
#define ip6_addr_ispreferred(addr_state) (addr_state == IP6_ADDR_PREFERRED)
#define ip6_addr_isdeprecated(addr_state) (addr_state == IP6_ADDR_DEPRECATED)
#define ip6_addr_isduplicated(addr_state) (addr_state == IP6_ADDR_DUPLICATED)

#if LWIP_IPV6_ADDRESS_LIFETIMES
#define IP6_ADDR_LIFE_STATIC   (0)
#define IP6_ADDR_LIFE_INFINITE (0xffffffffUL)
#define ip6_addr_life_isstatic(addr_life) ((addr_life) == IP6_ADDR_LIFE_STATIC)
#define ip6_addr_life_isinfinite(addr_life) ((addr_life) == IP6_ADDR_LIFE_INFINITE)
#endif /* LWIP_IPV6_ADDRESS_LIFETIMES */

#define ip6_addr_debug_print_parts(debug, a, b, c, d, e, f, g, h) \
  LWIP_DEBUGF(debug, ("%" X16_F ":%" X16_F ":%" X16_F ":%" X16_F ":%" X16_F ":%" X16_F ":%" X16_F ":%" X16_F, \
                      a, b, c, d, e, f, g, h))
#define ip6_addr_debug_print(debug, ipaddr) \
  ip6_addr_debug_print_parts(debug, \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK1(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK2(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK3(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK4(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK5(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK6(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK7(ipaddr) : 0),    \
                      (u16_t)((ipaddr) != NULL ? IP6_ADDR_BLOCK8(ipaddr) : 0))
#define ip6_addr_debug_print_val(debug, ipaddr) \
  ip6_addr_debug_print_parts(debug, \
                      IP6_ADDR_BLOCK1(&(ipaddr)),    \
                      IP6_ADDR_BLOCK2(&(ipaddr)),    \
                      IP6_ADDR_BLOCK3(&(ipaddr)),    \
                      IP6_ADDR_BLOCK4(&(ipaddr)),    \
                      IP6_ADDR_BLOCK5(&(ipaddr)),    \
                      IP6_ADDR_BLOCK6(&(ipaddr)),    \
                      IP6_ADDR_BLOCK7(&(ipaddr)),    \
                      IP6_ADDR_BLOCK8(&(ipaddr)))

#define IP6ADDR_STRLEN_MAX    46

int ip6addr_aton(const char *cp, ip6_addr_t *addr);
/**将ptr返回到静态缓冲区；不可重入！*/
char *ip6addr_ntoa(const ip6_addr_t *addr);
char *ip6addr_ntoa_r(const ip6_addr_t *addr, char *buf, int buflen);



#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_IP6_ADDR_H */

