/**
 * @file ICMP协议定义
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
#ifndef LWIP_HDR_PROT_ICMP_H
#define LWIP_HDR_PROT_ICMP_H

#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ICMP_ER   0    /* 回声应答*/
#define ICMP_DUR  3    /* 无法到达目的地*/
#define ICMP_SQ   4    /* 源淬火*/
#define ICMP_RD   5    /* 重新使用*/
#define ICMP_ECHO 8    /* 回响*/
#define ICMP_TE  11    /* 超过时间*/
#define ICMP_PP  12    /* 参数问题*/
#define ICMP_TS  13    /* 时间戳*/
#define ICMP_TSR 14    /* 时间戳回复*/
#define ICMP_IRQ 15    /* 信息请求*/
#define ICMP_IR  16    /* 信息回复*/
#define ICMP_AM  17    /* 地址掩码请求*/
#define ICMP_AMR 18    /* 地址掩码回复*/

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
/** 这是标准的ICMP报头，只有u32_t数据被拆分为两个u16_t，就像ICMP echo需要它一样。此标头也用于不使用数据部分的其他ICMP类型。
 */
PACK_STRUCT_BEGIN
struct icmp_echo_hdr {
  PACK_STRUCT_FLD_8(u8_t type);
  PACK_STRUCT_FLD_8(u8_t code);
  PACK_STRUCT_FIELD(u16_t chksum);
  PACK_STRUCT_FIELD(u16_t id);
  PACK_STRUCT_FIELD(u16_t seqno);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/* 兼容性定义，旧版本用于将类型和代码组合到u16_t*/
#define ICMPH_TYPE(hdr) ((hdr)->type)
#define ICMPH_CODE(hdr) ((hdr)->code)
#define ICMPH_TYPE_SET(hdr, t) ((hdr)->type = (t))
#define ICMPH_CODE_SET(hdr, c) ((hdr)->code = (c))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_ICMP_H */

