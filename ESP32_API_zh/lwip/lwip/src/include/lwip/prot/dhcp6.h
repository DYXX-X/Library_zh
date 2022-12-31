/**
 * @file DHCPv6协议定义
 */

/*
 * 版权所有（c）2017 Simon Goldschmidt<goldsimon@gmx.de>保留所有权利。
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
#ifndef LWIP_HDR_PROT_DHCP6_H
#define LWIP_HDR_PROT_DHCP6_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DHCP6_CLIENT_PORT  546
#define DHCP6_SERVER_PORT  547


 /* DHCPv6消息项偏移量和长度*/
#define DHCP6_TRANSACTION_ID_LEN   3

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
/**任何DHCPv6消息的最小字段集*/
struct dhcp6_msg
{
  PACK_STRUCT_FLD_8(u8_t msgtype);
  PACK_STRUCT_FLD_8(u8_t transaction_id[DHCP6_TRANSACTION_ID_LEN]);
  /* 选项如下*/
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif


/* DHCP6客户端状态*/
typedef enum {
  DHCP6_STATE_OFF               = 0,
  DHCP6_STATE_STATELESS_IDLE    = 1,
  DHCP6_STATE_REQUESTING_CONFIG = 2
} dhcp6_state_enum_t;

/* DHCPv6消息类型*/
#define DHCP6_SOLICIT               1
#define DHCP6_ADVERTISE             2
#define DHCP6_REQUEST               3
#define DHCP6_CONFIRM               4
#define DHCP6_RENEW                 5
#define DHCP6_REBIND                6
#define DHCP6_REPLY                 7
#define DHCP6_RELEASE               8
#define DHCP6_DECLINE               9
#define DHCP6_RECONFIGURE           10
#define DHCP6_INFOREQUEST           11
#define DHCP6_RELAYFORW             12
#define DHCP6_RELAYREPL             13
/* 更多消息类型请参见https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml */

/**DHCPv6状态代码*/
#define DHCP6_STATUS_SUCCESS        0 /* 成功*/
#define DHCP6_STATUS_UNSPECFAIL     1 /* 失败，原因不明；此状态代码由客户端或服务器发送，以指示本文档中未明确指定的故障。*/
#define DHCP6_STATUS_NOADDRSAVAIL   2 /* 服务器没有可分配给IA的地址。*/
#define DHCP6_STATUS_NOBINDING      3 /* 客户端记录（绑定）不可用。*/
#define DHCP6_STATUS_NOTONLINK      4 /* 地址的前缀不适用于客户端所连接的链接。*/
#define DHCP6_STATUS_USEMULTICAST   5 /* 由服务器发送给客户端，以强制客户端使用All_DHCP_Relay_Agents_and_Servers地址向服务器发送消息。*/
/* 更多状态代码请参阅https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml */

/**DHCPv6 DUID类型*/
#define DHCP6_DUID_LLT              1 /* LLT：链路层地址加时间*/
#define DHCP6_DUID_EN               2 /* EN：企业编号*/
#define DHCP6_DUID_LL               3 /* LL：链路层地址*/
#define DHCP6_DUID_UUID             4 /* UUID (RFC 6355) */

/* DHCPv6选项*/
#define DHCP6_OPTION_CLIENTID       1
#define DHCP6_OPTION_SERVERID       2
#define DHCP6_OPTION_IA_NA          3
#define DHCP6_OPTION_IA_TA          4
#define DHCP6_OPTION_IAADDR         5
#define DHCP6_OPTION_ORO            6
#define DHCP6_OPTION_PREFERENCE     7
#define DHCP6_OPTION_ELAPSED_TIME   8
#define DHCP6_OPTION_RELAY_MSG      9
#define DHCP6_OPTION_AUTH           11
#define DHCP6_OPTION_UNICAST        12
#define DHCP6_OPTION_STATUS_CODE    13
#define DHCP6_OPTION_RAPID_COMMIT   14
#define DHCP6_OPTION_USER_CLASS     15
#define DHCP6_OPTION_VENDOR_CLASS   16
#define DHCP6_OPTION_VENDOR_OPTS    17
#define DHCP6_OPTION_INTERFACE_ID   18
#define DHCP6_OPTION_RECONF_MSG     19
#define DHCP6_OPTION_RECONF_ACCEPT  20
/* 更多选项请参见https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml*/
#define DHCP6_OPTION_DNS_SERVERS    23 /* RFC 3646 */
#define DHCP6_OPTION_DOMAIN_LIST    24 /* RFC 3646 */
#define DHCP6_OPTION_SNTP_SERVERS   31 /* RFC 4075 */


#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_DHCP6_H */

