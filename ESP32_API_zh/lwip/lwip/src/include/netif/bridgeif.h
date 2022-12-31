/**
 * @file lwIP netif实现IEEE 802.1D MAC桥
 */

/*
 * 版权所有（c）2017 Simon Goldschmidt。保留所有权利。
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
#ifndef LWIP_HDR_NETIF_BRIDGEIF_H
#define LWIP_HDR_NETIF_BRIDGEIF_H

#include "netif/bridgeif_opts.h"

#include "lwip/err.h"
#include "lwip/prot/ethernet.h"

#ifdef __cplusplus
extern "C" {
#endif

struct netif;

#if (BRIDGEIF_MAX_PORTS < 0) || (BRIDGEIF_MAX_PORTS >= 64)
#error BRIDGEIF_MAX_PORTS must be [1..63]
#elif BRIDGEIF_MAX_PORTS < 8
typedef u8_t bridgeif_portmask_t;
#elif BRIDGEIF_MAX_PORTS < 16
typedef u16_t bridgeif_portmask_t;
#elif BRIDGEIF_MAX_PORTS < 32
typedef u32_t bridgeif_portmask_t;
#elif BRIDGEIF_MAX_PORTS < 64
typedef u64_t bridgeif_portmask_t;
#endif

#define BR_FLOOD ((bridgeif_portmask_t)-1)

/** @ingroup @ref bridgeif_init的bridgeif初始化数据。添加网桥时，必须将此类型的实例作为参数“state”传递给@ref netif_add。
 */
typedef struct bridgeif_initdata_s {
  /**网桥的MAC地址（不能使用netif的地址）*/
  struct eth_addr ethaddr;
  /**网桥中的最大端口数（端口存储在数组中，这会影响为网桥netif->状态分配的内存）。*/
  u8_t            max_ports;
  /**网桥转发数据库中动态/学习条目的最大数量。在默认实现中，这仅控制内存消耗。*/
  u16_t           max_fdb_dynamic_entries;
  /**静态转发条目的最大数量。影响内存消耗！*/
  u16_t           max_fdb_static_entries;
} bridgeif_initdata_t;

/** @ingroup bridgeif使用此函数对bridgeif_initdat_t进行常量初始化（ethddr必须作为ETH_ADDR（）传递）
 */
#define BRIDGEIF_INITDATA1(max_ports, max_fdb_dynamic_entries, max_fdb_static_entries, ethaddr) {ethaddr, max_ports, max_fdb_dynamic_entries, max_fdb_static_entries}
/** @ingroup bridgeif使用此函数对bridgeif_initdat_t进行常量初始化（必须传递ethddr的每个字节）
 */
#define BRIDGEIF_INITDATA2(max_ports, max_fdb_dynamic_entries, max_fdb_static_entries, e0, e1, e2, e3, e4, e5) {{e0, e1, e2, e3, e4, e5}, max_ports, max_fdb_dynamic_entries, max_fdb_static_entries}

err_t bridgeif_init(struct netif *netif);
err_t bridgeif_add_port(struct netif *bridgeif, struct netif *portif);
err_t bridgeif_fdb_add(struct netif *bridgeif, const struct eth_addr *addr, bridgeif_portmask_t ports);
err_t bridgeif_fdb_remove(struct netif *bridgeif, const struct eth_addr *addr);

/* FDB接口，可由自己的实现替换*/
void                bridgeif_fdb_update_src(void *fdb_ptr, struct eth_addr *src_addr, u8_t port_idx);
bridgeif_portmask_t bridgeif_fdb_get_dst_ports(void *fdb_ptr, struct eth_addr *dst_addr);
void*               bridgeif_fdb_init(u16_t max_fdb_entries);

#if BRIDGEIF_PORT_NETIFS_OUTPUT_DIRECT
#ifndef BRIDGEIF_DECL_PROTECT
/* 将桥接保护定义为sys_arch_proctect。。。*/
#include "lwip/sys.h"
#define BRIDGEIF_DECL_PROTECT(lev)    SYS_ARCH_DECL_PROTECT(lev)
#define BRIDGEIF_READ_PROTECT(lev)    SYS_ARCH_PROTECT(lev)
#define BRIDGEIF_READ_UNPROTECT(lev)  SYS_ARCH_UNPROTECT(lev)
#define BRIDGEIF_WRITE_PROTECT(lev)
#define BRIDGEIF_WRITE_UNPROTECT(lev)
#endif
#else /* BRIDGEIF_PORT_NETIFS_OUTPUT_DIRECT */
#include "lwip/tcpip.h"
#define BRIDGEIF_DECL_PROTECT(lev)
#define BRIDGEIF_READ_PROTECT(lev)
#define BRIDGEIF_READ_UNPROTECT(lev)
#define BRIDGEIF_WRITE_PROTECT(lev)
#define BRIDGEIF_WRITE_UNPROTECT(lev)
#endif /* BRIDGEIF_PORT_NETIFS_OUTPUT_DIRECT */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_NETIF_BRIDGEIF_H */

