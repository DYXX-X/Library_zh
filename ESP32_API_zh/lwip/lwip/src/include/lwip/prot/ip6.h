/**
 * @file IPv6协议定义
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
#ifndef LWIP_HDR_PROT_IP6_H
#define LWIP_HDR_PROT_IP6_H

#include "lwip/arch.h"
#include "lwip/ip6_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**这是ip6_addr_t的打包版本，用于自身打包的网络标头*/
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_addr_packed {
  PACK_STRUCT_FIELD(u32_t addr[4]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
typedef struct ip6_addr_packed ip6_addr_p_t;

#define IP6_HLEN 40

#define IP6_NEXTH_HOPBYHOP  0
#define IP6_NEXTH_TCP       6
#define IP6_NEXTH_UDP       17
#define IP6_NEXTH_ENCAPS    41
#define IP6_NEXTH_ROUTING   43
#define IP6_NEXTH_FRAGMENT  44
#define IP6_NEXTH_ICMP6     58
#define IP6_NEXTH_NONE      59
#define IP6_NEXTH_DESTOPTS  60
#define IP6_NEXTH_UDPLITE   136

/**IPv6标头。*/
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_hdr {
  /**版本/流量等级/流量标签*/
  PACK_STRUCT_FIELD(u32_t _v_tc_fl);
  /**有效载荷长度*/
  PACK_STRUCT_FIELD(u16_t _plen);
  /**下一个标题*/
  PACK_STRUCT_FLD_8(u8_t _nexth);
  /**跳跃极限*/
  PACK_STRUCT_FLD_8(u8_t _hoplim);
  /**源和目标IP地址*/
  PACK_STRUCT_FLD_S(ip6_addr_p_t src);
  PACK_STRUCT_FLD_S(ip6_addr_p_t dest);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define IP6H_V(hdr)  ((lwip_ntohl((hdr)->_v_tc_fl) >> 28) & 0x0f)
#define IP6H_TC(hdr) ((lwip_ntohl((hdr)->_v_tc_fl) >> 20) & 0xff)
#define IP6H_FL(hdr) (lwip_ntohl((hdr)->_v_tc_fl) & 0x000fffff)
#define IP6H_PLEN(hdr) (lwip_ntohs((hdr)->_plen))
#define IP6H_NEXTH(hdr) ((hdr)->_nexth)
#define IP6H_NEXTH_P(hdr) ((u8_t *)(hdr) + 6)
#define IP6H_HOPLIM(hdr) ((hdr)->_hoplim)
#define IP6H_VTCFL_SET(hdr, v, tc, fl) (hdr)->_v_tc_fl = (lwip_htonl((((u32_t)(v)) << 28) | (((u32_t)(tc)) << 20) | (fl)))
#define IP6H_PLEN_SET(hdr, plen) (hdr)->_plen = lwip_htons(plen)
#define IP6H_NEXTH_SET(hdr, nexth) (hdr)->_nexth = (nexth)
#define IP6H_HOPLIM_SET(hdr, hl) (hdr)->_hoplim = (u8_t)(hl)

/* ipv6扩展选项标头*/
#define IP6_PAD1_OPTION             0
#define IP6_PADN_OPTION             1
#define IP6_ROUTER_ALERT_OPTION     5
#define IP6_JUMBO_OPTION            194
#define IP6_HOME_ADDRESS_OPTION     201
#define IP6_ROUTER_ALERT_DLEN       2
#define IP6_ROUTER_ALERT_VALUE_MLD  0

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_opt_hdr {
  /* 路由器警报选项类型*/
  PACK_STRUCT_FLD_8(u8_t _opt_type);
  /* 路由器警报选项数据长度*/
  PACK_STRUCT_FLD_8(u8_t _opt_dlen);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define IP6_OPT_HLEN 2
#define IP6_OPT_TYPE_ACTION(hdr) ((((hdr)->_opt_type) >> 6) & 0x3)
#define IP6_OPT_TYPE_CHANGE(hdr) ((((hdr)->_opt_type) >> 5) & 0x1)
#define IP6_OPT_TYPE(hdr) ((hdr)->_opt_type)
#define IP6_OPT_DLEN(hdr) ((hdr)->_opt_dlen)

/* 逐跳标头。*/
#define IP6_HBH_HLEN    2

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_hbh_hdr {
  /* 下一个标题*/
  PACK_STRUCT_FLD_8(u8_t _nexth);
  /* 8位字节单位的报头长度*/
  PACK_STRUCT_FLD_8(u8_t _hlen);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define IP6_HBH_NEXTH(hdr) ((hdr)->_nexth)

/* 目标标头。*/
#define IP6_DEST_HLEN   2

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_dest_hdr {
  /* 下一个标题*/
  PACK_STRUCT_FLD_8(u8_t _nexth);
  /* 8位字节单位的报头长度*/
  PACK_STRUCT_FLD_8(u8_t _hlen);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define IP6_DEST_NEXTH(hdr) ((hdr)->_nexth)

/* 路由标头*/
#define IP6_ROUT_TYPE2  2
#define IP6_ROUT_RPL    3

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_rout_hdr {
  /* 下一个标题*/
  PACK_STRUCT_FLD_8(u8_t _nexth);
  /* 保留*/
  PACK_STRUCT_FLD_8(u8_t _hlen);
  /* 碎片偏移量*/
  PACK_STRUCT_FIELD(u8_t _routing_type);
  /* 分段数据包识别*/
  PACK_STRUCT_FIELD(u8_t _segments_left);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define IP6_ROUT_NEXTH(hdr) ((hdr)->_nexth)
#define IP6_ROUT_TYPE(hdr) ((hdr)->_routing_type)
#define IP6_ROUT_SEG_LEFT(hdr) ((hdr)->_segments_left)

/* 片段标头。*/
#define IP6_FRAG_HLEN    8
#define IP6_FRAG_OFFSET_MASK    0xfff8
#define IP6_FRAG_MORE_FLAG      0x0001

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip6_frag_hdr {
  /* 下一个标题*/
  PACK_STRUCT_FLD_8(u8_t _nexth);
  /* 保留*/
  PACK_STRUCT_FLD_8(u8_t reserved);
  /* 碎片偏移量*/
  PACK_STRUCT_FIELD(u16_t _fragment_offset);
  /* 分段数据包识别*/
  PACK_STRUCT_FIELD(u32_t _identification);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define IP6_FRAG_NEXTH(hdr) ((hdr)->_nexth)
#define IP6_FRAG_MBIT(hdr) (lwip_ntohs((hdr)->_fragment_offset) & 0x1)
#define IP6_FRAG_ID(hdr) (lwip_ntohl((hdr)->_identification))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_IP6_H */

