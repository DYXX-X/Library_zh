/**
 * @file IGMP协议定义
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
#ifndef LWIP_HDR_PROT_IGMP_H
#define LWIP_HDR_PROT_IGMP_H

#include "lwip/arch.h"
#include "lwip/prot/ip4.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * IGMP常量
 */
#define IGMP_TTL                       1
#define IGMP_MINLEN                    8
#define ROUTER_ALERT                   0x9404U
#define ROUTER_ALERTLEN                4

/*
 * IGMP消息类型，包括版本号。
 */
#define IGMP_MEMB_QUERY                0x11 /* 会员资格查询*/
#define IGMP_V1_MEMB_REPORT            0x12 /* 第1版成员报告*/
#define IGMP_V2_MEMB_REPORT            0x16 /* 第2版成员报告*/
#define IGMP_LEAVE_GROUP               0x17 /* 留下组消息*/

/* 组成员状态*/
#define IGMP_GROUP_NON_MEMBER          0
#define IGMP_GROUP_DELAYING_MEMBER     1
#define IGMP_GROUP_IDLE_MEMBER         2

/**
 * IGMP数据包格式。
 */
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct igmp_msg {
  PACK_STRUCT_FLD_8(u8_t         igmp_msgtype);
  PACK_STRUCT_FLD_8(u8_t         igmp_maxresp);
  PACK_STRUCT_FIELD(u16_t        igmp_checksum);
  PACK_STRUCT_FLD_S(ip4_addr_p_t igmp_group_address);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_IGMP_H */

