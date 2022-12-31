/**
 * @file IPv4协议定义
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
#ifndef LWIP_HDR_PROT_IP4_H
#define LWIP_HDR_PROT_IP4_H

#include "lwip/arch.h"
#include "lwip/ip4_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**这是ip4_addr_t的打包版本，用于自身打包的网络标头*/
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ip4_addr_packed {
  PACK_STRUCT_FIELD(u32_t addr);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

typedef struct ip4_addr_packed ip4_addr_p_t;

/* IPv4标头的大小。与“sizeof（struct ip_hdr）”相同。*/
#define IP_HLEN 20
/* IPv4标头的最大大小（带选项）。*/
#define IP_HLEN_MAX 60

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
/* IPv4标头*/
struct ip_hdr {
  /* 版本/标题长度*/
  PACK_STRUCT_FLD_8(u8_t _v_hl);
  /* 服务类型*/
  PACK_STRUCT_FLD_8(u8_t _tos);
  /* 总长度*/
  PACK_STRUCT_FIELD(u16_t _len);
  /* 识别*/
  PACK_STRUCT_FIELD(u16_t _id);
  /* 碎片偏移场*/
  PACK_STRUCT_FIELD(u16_t _offset);
#define IP_RF 0x8000U        /* 保留片段标志*/
#define IP_DF 0x4000U        /* 不分段标志*/
#define IP_MF 0x2000U        /* 更多碎片标志*/
#define IP_OFFMASK 0x1fffU   /* 分段位掩码*/
  /* 生存时间*/
  PACK_STRUCT_FLD_8(u8_t _ttl);
  /* 协议*/
  PACK_STRUCT_FLD_8(u8_t _proto);
  /* 校验和*/
  PACK_STRUCT_FIELD(u16_t _chksum);
  /* 源和目标IP地址*/
  PACK_STRUCT_FLD_S(ip4_addr_p_t src);
  PACK_STRUCT_FLD_S(ip4_addr_p_t dest);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/* 获取结构ip_hdr字段的宏：*/
#define IPH_V(hdr)  ((hdr)->_v_hl >> 4)
#define IPH_HL(hdr) ((hdr)->_v_hl & 0x0f)
#define IPH_HL_BYTES(hdr) ((u8_t)(IPH_HL(hdr) * 4))
#define IPH_TOS(hdr) ((hdr)->_tos)
#define IPH_LEN(hdr) ((hdr)->_len)
#define IPH_ID(hdr) ((hdr)->_id)
#define IPH_OFFSET(hdr) ((hdr)->_offset)
#define IPH_OFFSET_BYTES(hdr) ((u16_t)((lwip_ntohs(IPH_OFFSET(hdr)) & IP_OFFMASK) * 8U))
#define IPH_TTL(hdr) ((hdr)->_ttl)
#define IPH_PROTO(hdr) ((hdr)->_proto)
#define IPH_CHKSUM(hdr) ((hdr)->_chksum)

/* 用于设置结构ip_hdr字段的宏：*/
#define IPH_VHL_SET(hdr, v, hl) (hdr)->_v_hl = (u8_t)((((v) << 4) | (hl)))
#define IPH_TOS_SET(hdr, tos) (hdr)->_tos = (tos)
#define IPH_LEN_SET(hdr, len) (hdr)->_len = (len)
#define IPH_ID_SET(hdr, id) (hdr)->_id = (id)
#define IPH_OFFSET_SET(hdr, off) (hdr)->_offset = (off)
#define IPH_TTL_SET(hdr, ttl) (hdr)->_ttl = (u8_t)(ttl)
#define IPH_PROTO_SET(hdr, proto) (hdr)->_proto = (u8_t)(proto)
#define IPH_CHKSUM_SET(hdr, chksum) (hdr)->_chksum = (chksum)


#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_IP4_H */

