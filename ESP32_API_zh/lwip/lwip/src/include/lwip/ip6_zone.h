/**
 * @file
 *
 * IPv6地址范围、区域和范围策略。
 *
 * 根据RFC 4007，此标头提供了实现IPv6地址范围支持的方法。地址范围可以是全局的，也可以是更受约束的。在lwIP中，我们说一个地址“有一个作用域”，或者当它的作用域受到约束时“有作用域”。在这种情况下，地址只有在特定的“区域”中才有意义。对于单播地址，只有链接本地地址才有作用域；在这种情况下，范围是链接。对于多播地址，RFC 4007等定义了各种作用域。对于任何受限范围，系统必须在区域和本地接口之间建立（可能是一对多）映射。例如，链接本地地址仅在一个链接（其区域）上有效。该链接可以连接到一个或多个本地接口。关于哪些作用域受到约束以及区域和接口之间的映射的决定是我们所称的“作用域策略”，稍后将对此进行详细介绍。
 *
 * 在lwIP中，每个IPv6地址都有一个关联的区域索引。该区域索引可以设置为“无区域”（IP6_no_zone，0）或实际区域。我们说，当地址的区域索引未设置为“无区域”时，地址“有区域”或“已分区”。在lwIP中，原则上，每个地址都应“正确分区”，这意味着如果地址有区域，则当且仅当地址有范围时。因此，无范围（例如，全局）地址决不能有区域是一条规则。尽管有人可能会认为，即使对于全局范围，也总是有一个区域，但这一规则的存在是为了实现简单。违反规则将触发断言或导致不期望的行为。
 *
 * 向后兼容性使我们无法要求应用程序始终提供正确分区的地址。我们确实执行了这样的规则，即lwIP链接层（netif->output_ip6（）以下的所有地址，特别是ND6）中的所有地址都被正确分区。因此，在堆栈的输出路径上，不同的位置处理缺少区域的地址的情况。其中一些是为了提高效率而付出的最大努力（例如，PCB绑定和连接API调用试图添加缺失区域）；最终是IPv6输出
 * handler (@ref ip6_output_if_src）将在必要时设置区域。
 *
 * 除了处理缺少区域的作用域地址之外，正确的IPv6实现还必须确保具有作用域源和/或目标地址的数据包不会离开其区域。这目前在输入和转发功能中实现。然而，对于输出，为了保持实现的轻量级，故意省略了这些检查。这个
 * routing algorithm in @ref ip6route将做出决定，除非应用程序设置了错误的地址，否则不会导致区域冲突。
 *
 * 在作用域策略方面，lwIP使用此文件中的宏实现RFC 4007中的默认策略。此策略将链路本地单播地址和（仅）接口本地和链路本地多播地址视为具有作用域。对于所有这些地址，区域等于接口。如以下文件所示，可以实现自定义策略。
 */

/*
 * 版权所有（c）2017 MINIX 3项目。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：David van Moolenbroek<david@minix3.org>
 *
 */
#ifndef LWIP_HDR_IP6_ZONE_H
#define LWIP_HDR_IP6_ZONE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ip6_zones IPv6区域
 * @ingroup 第6层@{
 */

#if LWIP_IPV6  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/**“无区域”的标识符。*/
#define IP6_NO_ZONE 0

#if LWIP_IPV6_SCOPES

/**静态IPv6地址初始化的区域初始值设定项，包括逗号。*/
#define IPADDR6_ZONE_INIT , IP6_NO_ZONE

/**返回给定IPv6地址的区域索引；可能是“无区”。*/
#define ip6_addr_zone(ip6addr) ((ip6addr)->zone)

/**给定的IPv6地址是否设置了区域？(0/1) */
#define ip6_addr_has_zone(ip6addr) (ip6_addr_zone(ip6addr) != IP6_NO_ZONE)

/**将IPv6地址的区域字段设置为特定值。*/
#define ip6_addr_set_zone(ip6addr, zone_idx) ((ip6addr)->zone = (zone_idx))

/**清除IPv6地址的区域字段，将其设置为“无区域”。*/
#define ip6_addr_clear_zone(ip6addr) ((ip6addr)->zone = IP6_NO_ZONE)

/**将区域字段从第二个IPv6地址复制到第一个IPv6地址。*/
#define ip6_addr_copy_zone(ip6addr1, ip6addr2) ((ip6addr1).zone = (ip6addr2).zone)

/**给定IPv6地址的区域字段是否等于给定区域索引？(0/1)*/
#define ip6_addr_equals_zone(ip6addr, zone_idx) ((ip6addr)->zone == (zone_idx))

/**给定IPv6地址的区域字段是否相等？（0/1）此宏只能用于相同作用域的IPv6地址。*/
#define ip6_addr_cmp_zone(ip6addr1, ip6addr2) ((ip6addr1)->zone == (ip6addr2)->zone)

/** 某些宏中“类型”参数的符号常量。这些只是为了提高效率而存在的，当已知地址不是特定类型时，允许宏避免某些测试。死代码消除将完成剩下的工作。支持IP6_MULTICAST，但目前尚未优化。
 * @see ip6_addr_has_scope、ip6_addr_assign_zone和ip6_addr_lacks_zone。
 */
enum lwip_ipv6_scope_type
{
  /**未知*/
  IP6_UNKNOWN   = 0,
  /**单播*/
  IP6_UNICAST   = 1,
  /**多播*/
  IP6_MULTICAST = 2
};

/** IPV6_CUSTOM_SCOPES：以下三个宏定义，
 * @ref ip6_addr_has_scope，@ref ip6_addr_assign_zone，以及
 * @ref ip6_addr_test_zone，完全定义lwIP作用域策略。下面的定义实现了RFC 4007第6节中的默认策略。如果实现希望实现不同的策略，则可以将IPV6_CUSTOM_SCOPES定义为1，并为三个宏提供自己的定义。
 */
#ifndef IPV6_CUSTOM_SCOPES
#define IPV6_CUSTOM_SCOPES 0
#endif /* !IPV6_CUSTOM_SCOPES */

#if !IPV6_CUSTOM_SCOPES

/**
 * 确定IPv6地址是否具有受约束的作用域，因此，只有在附带区域索引以标识作用域的区域时才有意义。给定的地址类型可用于在编译时消除某些检查，这些检查无论如何都会在运行时求值为false。
 *
 * 此默认实现遵循RFC 4007的默认模型，其中仅定义接口本地和链接本地作用域。
 *
 * 尽管单播环回地址确实具有隐含的链路本地作用域，但在此实现中，它没有显式分配的区域索引。因此，不应在此宏中对其进行测试。
 *
 * @param ip6addr IPv6地址（常量）；仅检查其地址部分。
 * @param type 地址类型；请参见@ref lwip_ipv6_scope_type。
 * @return 如果地址具有受约束的范围，则为1；如果没有，则为0。
 */
#define ip6_addr_has_scope(ip6addr, type) \
  (ip6_addr_islinklocal(ip6addr) || (((type) != IP6_UNICAST) && \
   (ip6_addr_ismulticast_iflocal(ip6addr) || \
    ip6_addr_ismulticast_linklocal(ip6addr))))

/**
 * 根据网络接口为IPv6地址分配区域索引。如果给定地址具有作用域，则分配的区域索引是给定netif的作用域的区域；否则，分配的区域索引为“无区域”。
 *
 * 此默认实现遵循RFC 4007的默认模型，其中仅定义接口本地和链路本地作用域，并且这两个作用域的区域索引始终等于网络接口的索引。因此，在分配分区时，此默认实现不需要区分不同的受约束范围。
 *
 * @param ip6addr IPv6地址；检查其地址部分，并分配其区域索引。
 * @param type 地址类型；请参见@ref lwip_ipv6_scope_type。
 * @param netif 网络接口（const）。
 */
#define ip6_addr_assign_zone(ip6addr, type, netif) \
    (ip6_addr_set_zone((ip6addr), \
      ip6_addr_has_scope((ip6addr), (type)) ? netif_get_index(netif) : 0))

/**
 * 测试IPv6地址是否与网络接口“区域兼容”。也就是说，测试网络接口是否是与地址关联的区域的一部分。为了提高效率，只有在给定地址是作用域或分区的情况下才会调用此宏，因此，它不需要对此进行测试。如果一个地址有作用域但没有分区，或者分区但没有作用域，则认为它与任何netif都不兼容。
 *
 * 此默认实现遵循RFC 4007的默认模型，其中仅定义接口本地和链路本地作用域，并且这两个作用域的区域索引始终等于网络接口的索引。因此，对于特定的区域索引，始终只有一个匹配的netif，但该宏的所有调用站点当前也支持多个匹配netif（在常见情况下不需要额外的费用）。
 *
 * @param ip6addr IPv6地址（常量）。
 * @param netif 网络接口（const）。
 * @return 如果地址与netif范围兼容，则为1；如果不兼容，则0。
 */
#define ip6_addr_test_zone(ip6addr, netif) \
    (ip6_addr_equals_zone((ip6addr), netif_get_index(netif)))

#endif /* !IPV6_CUSTOM_SCOPES */

/**给定的IPv6地址是否有作用域，因此也应该有一个有意义的区域，但实际上没有区域？(0/1) */
#define ip6_addr_lacks_zone(ip6addr, type) \
    (!ip6_addr_has_zone(ip6addr) && ip6_addr_has_scope((ip6addr), (type)))

/**
 * 尝试为尚未具有区域的作用域地址选择区域。从PCB绑定和连接例程调用，原因有两个：1）为每个单独的数据包路由操作节省这种（相对昂贵的）选择；2）允许应用程序从PCB获取所选区域，这是例如getsockname/getpeername BSD套接字调用的惯例。
 *
 * 理想情况下，调用者将始终提供一个正确分区的地址，在这种情况下，不需要此函数。它既与BSD套接字API（接受无区域目标地址）兼容，也与预作用域lwIP代码向后兼容。
 *
 * 可能无法选择区域，例如，如果没有网络。在这种情况下，地址的区域字段将保持原样。
 *
 * @param dest 要为其选择和设置区域的IPv6地址。
 * @param src 源IPv6地址（常量）；可以等于dest。
 */
#define ip6_addr_select_zone(dest, src) do { struct netif *selected_netif; \
  selected_netif = ip6_route((src), (dest)); \
  if (selected_netif != NULL) { \
    ip6_addr_assign_zone((dest), IP6_UNKNOWN, selected_netif); \
  } } while (0)

/**
 * @}
 */

#else /* LWIP_IPV6_SCOPES */

#define IPADDR6_ZONE_INIT
#define ip6_addr_zone(ip6addr) (IP6_NO_ZONE)
#define ip6_addr_has_zone(ip6addr) (0)
#define ip6_addr_set_zone(ip6addr, zone_idx)
#define ip6_addr_clear_zone(ip6addr)
#define ip6_addr_copy_zone(ip6addr1, ip6addr2)
#define ip6_addr_equals_zone(ip6addr, zone_idx) (1)
#define ip6_addr_cmp_zone(ip6addr1, ip6addr2) (1)
#define IPV6_CUSTOM_SCOPES 0
#define ip6_addr_has_scope(ip6addr, type) (0)
#define ip6_addr_assign_zone(ip6addr, type, netif)
#define ip6_addr_test_zone(ip6addr, netif) (1)
#define ip6_addr_lacks_zone(ip6addr, type) (0)
#define ip6_addr_select_zone(ip6addr, src)

#endif /* LWIP_IPV6_SCOPES */

#if LWIP_IPV6_SCOPES && LWIP_IPV6_SCOPES_DEBUG

/**验证给定的IPv6地址是否已正确分区。*/
#define IP6_ADDR_ZONECHECK(ip6addr) LWIP_ASSERT("IPv6 zone check failed", \
    ip6_addr_has_scope(ip6addr, IP6_UNKNOWN) == ip6_addr_has_zone(ip6addr))

/**验证给定的IPv6地址是否为给定netif正确分区。*/
#define IP6_ADDR_ZONECHECK_NETIF(ip6addr, netif) LWIP_ASSERT("IPv6 netif zone check failed", \
    ip6_addr_has_scope(ip6addr, IP6_UNKNOWN) ? \
    (ip6_addr_has_zone(ip6addr) && \
     (((netif) == NULL) || ip6_addr_test_zone((ip6addr), (netif)))) : \
    !ip6_addr_has_zone(ip6addr))

#else /* LWIP_IPV6_SCOPES && LWIP_IPV6_SCOPES_DEBUG */

#define IP6_ADDR_ZONECHECK(ip6addr)
#define IP6_ADDR_ZONECHECK_NETIF(ip6addr, netif)

#endif /* LWIP_IPV6_SCOPES && LWIP_IPV6_SCOPES_DEBUG */

#endif /* LWIP_IPV6 */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_IP6_ZONE_H */

