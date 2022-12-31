/**
 * @file DHCP协议定义
 */

/*
 * Copyright (c) 2001-2004 Leon Woestenberg <leon.woestenberg@gmx.net> 版权所有（c）2001-2004 Axon Digital Design B.V.，荷兰。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Leon Woestenberg<leon.woestenberg@gmx.net>
 *
 */
#ifndef LWIP_HDR_PROT_DHCP_H
#define LWIP_HDR_PROT_DHCP_H

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/prot/ip4.h"

#ifdef __cplusplus
extern "C" {
#endif

 /* DHCP消息项偏移量和长度*/
#define DHCP_CHADDR_LEN   16U
#define DHCP_SNAME_OFS    44U
#define DHCP_SNAME_LEN    64U
#define DHCP_FILE_OFS     108U
#define DHCP_FILE_LEN     128U
#define DHCP_MSG_LEN      236U
#define DHCP_OPTIONS_OFS  (DHCP_MSG_LEN + 4U) /* 4字节：cookie*/

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
/**任何DHCP消息的最小字段集*/
struct dhcp_msg
{
  PACK_STRUCT_FLD_8(u8_t op);
  PACK_STRUCT_FLD_8(u8_t htype);
  PACK_STRUCT_FLD_8(u8_t hlen);
  PACK_STRUCT_FLD_8(u8_t hops);
  PACK_STRUCT_FIELD(u32_t xid);
  PACK_STRUCT_FIELD(u16_t secs);
  PACK_STRUCT_FIELD(u16_t flags);
  PACK_STRUCT_FLD_S(ip4_addr_p_t ciaddr);
  PACK_STRUCT_FLD_S(ip4_addr_p_t yiaddr);
  PACK_STRUCT_FLD_S(ip4_addr_p_t siaddr);
  PACK_STRUCT_FLD_S(ip4_addr_p_t giaddr);
  PACK_STRUCT_FLD_8(u8_t chaddr[DHCP_CHADDR_LEN]);
  PACK_STRUCT_FLD_8(u8_t sname[DHCP_SNAME_LEN]);
  PACK_STRUCT_FLD_8(u8_t file[DHCP_FILE_LEN]);
  PACK_STRUCT_FIELD(u32_t cookie);
#define DHCP_MIN_OPTIONS_LEN 68U
/**确保用户没有将其配置得太小*/
#if ((defined(DHCP_OPTIONS_LEN)) && (DHCP_OPTIONS_LEN < DHCP_MIN_OPTIONS_LEN))
#  undef DHCP_OPTIONS_LEN
#endif
/**允许在lwipopt中配置。h、 但不要太小*/
#if (!defined(DHCP_OPTIONS_LEN))
/**将此设置为足以满足传出DHCP消息中的选项*/
#  define DHCP_OPTIONS_LEN DHCP_MIN_OPTIONS_LEN
#endif
  PACK_STRUCT_FLD_8(u8_t options[DHCP_OPTIONS_LEN]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif


/* DHCP客户端状态*/
typedef enum {
  DHCP_STATE_OFF             = 0,
  DHCP_STATE_REQUESTING      = 1,
  DHCP_STATE_INIT            = 2,
  DHCP_STATE_REBOOTING       = 3,
  DHCP_STATE_REBINDING       = 4,
  DHCP_STATE_RENEWING        = 5,
  DHCP_STATE_SELECTING       = 6,
  DHCP_STATE_INFORMING       = 7,
  DHCP_STATE_CHECKING        = 8,
  DHCP_STATE_PERMANENT       = 9,  /* 尚未实施*/
  DHCP_STATE_BOUND           = 10,
  DHCP_STATE_RELEASING       = 11, /* 尚未实施*/
  DHCP_STATE_BACKING_OFF     = 12
} dhcp_state_enum_t;

/* DHCP操作码*/
#define DHCP_BOOTREQUEST            1
#define DHCP_BOOTREPLY              2

/* DHCP消息类型*/
#define DHCP_DISCOVER               1
#define DHCP_OFFER                  2
#define DHCP_REQUEST                3
#define DHCP_DECLINE                4
#define DHCP_ACK                    5
#define DHCP_NAK                    6
#define DHCP_RELEASE                7
#define DHCP_INFORM                 8

#define DHCP_MAGIC_COOKIE           0x63825363UL

/* 这是BOOTP和DHCP的选项列表，有关说明，请参阅RFC 2132*/

/* BootP选项*/
#define DHCP_OPTION_PAD             0
#define DHCP_OPTION_SUBNET_MASK     1 /* RFC 2132 3.3 */
#define DHCP_OPTION_ROUTER          3
#define DHCP_OPTION_DNS_SERVER      6
#define DHCP_OPTION_HOSTNAME        12
#define DHCP_OPTION_IP_TTL          23
#define DHCP_OPTION_MTU             26
#define DHCP_OPTION_BROADCAST       28
#define DHCP_OPTION_TCP_TTL         37
#define DHCP_OPTION_NTP             42
#define DHCP_OPTION_END             255

/* DHCP选项*/
#define DHCP_OPTION_REQUESTED_IP    50 /* RFC 2132 9.1，请求的IP地址*/
#define DHCP_OPTION_LEASE_TIME      51 /* RFC 2132 9.2，时间（秒），4字节*/
#define DHCP_OPTION_OVERLOAD        52 /* RFC2132 9.3，使用file和/或sname字段作为选项*/

#define DHCP_OPTION_MESSAGE_TYPE    53 /* RFC 2132 9.6，对DHCP很重要*/
#define DHCP_OPTION_MESSAGE_TYPE_LEN 1

#define DHCP_OPTION_SERVER_ID       54 /* RFC 2132 9.7，服务器IP地址*/
#define DHCP_OPTION_PARAMETER_REQUEST_LIST  55 /* RFC 2132 9.8，请求的选项类型*/

#define DHCP_OPTION_MAX_MSG_SIZE    57 /* RFC 2132 9.10，接受的消息大小>=576*/
#define DHCP_OPTION_MAX_MSG_SIZE_LEN 2

#define DHCP_OPTION_T1              58 /* T1更新时间*/
#define DHCP_OPTION_T2              59 /* T2再结合时间*/
#define DHCP_OPTION_VCI             60
#define DHCP_OPTION_VSI             43
#define DHCP_OPTION_CLIENT_ID       61
#define DHCP_OPTION_TFTP_SERVERNAME 66
#define DHCP_OPTION_BOOTFILE        67

/* 使用选项重载file和sname字段的可能组合*/
#define DHCP_OVERLOAD_NONE          0
#define DHCP_OVERLOAD_FILE          1
#define DHCP_OVERLOAD_SNAME         2
#define DHCP_OVERLOAD_SNAME_FILE    3

/* DHCP OPTION 61 TYPE */
#if ESP_DHCP
#define DHCP_OPTION_CLIENT_ID_MAC   0x01
#define DHCP_OPTION_CLIENT_ID_DUID  0x02
#define DHCP_OPTION_CLIENT_ID_IAID  0xff

#define DHCP_OPTION_CLIENT_ID_MAC_LEN   7
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_DHCP_H */

