/**
 * @file DNS-主机名到IP地址解析程序。
 */

/*
 * Jim Pettinato 2007年4月从uIP到lwIP的端口
 *
 * Simon Goldschmidt提供的安全修复和更多
 *
 * uIP版本版权所有（c）2002-2003，Adam Dunkels。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LWIP_HDR_PROT_DNS_H
#define LWIP_HDR_PROT_DNS_H

#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/**DNS服务器端口地址*/
#ifndef DNS_SERVER_PORT
#define DNS_SERVER_PORT           53
#endif

/* 用于“资源记录”的DNS字段TYPE*/
#define DNS_RRTYPE_A              1     /* 主机地址*/
#define DNS_RRTYPE_NS             2     /* 权威名称服务器*/
#define DNS_RRTYPE_MD             3     /* 邮件目的地（过时-使用MX）*/
#define DNS_RRTYPE_MF             4     /* 邮件转发器（过时-使用MX）*/
#define DNS_RRTYPE_CNAME          5     /* 别名的规范名称*/
#define DNS_RRTYPE_SOA            6     /* 标志着权力区域的开始*/
#define DNS_RRTYPE_MB             7     /* 邮箱域名（实验）*/
#define DNS_RRTYPE_MG             8     /* 邮件组成员（实验）*/
#define DNS_RRTYPE_MR             9     /* 邮件重命名域名（实验）*/
#define DNS_RRTYPE_NULL           10    /* 空RR（实验）*/
#define DNS_RRTYPE_WKS            11    /* 众所周知的服务描述*/
#define DNS_RRTYPE_PTR            12    /* 域名指针*/
#define DNS_RRTYPE_HINFO          13    /* 主机信息*/
#define DNS_RRTYPE_MINFO          14    /* 邮箱或邮件列表信息*/
#define DNS_RRTYPE_MX             15    /* 邮件交换*/
#define DNS_RRTYPE_TXT            16    /* 文本字符串*/
#define DNS_RRTYPE_AAAA           28    /* IPv6地址*/
#define DNS_RRTYPE_SRV            33    /* 服务地点*/
#define DNS_RRTYPE_ANY            255   /* 任何类型*/

/* 用于“资源记录”的DNS字段CLASS*/
#define DNS_RRCLASS_IN            1     /* 互联网*/
#define DNS_RRCLASS_CS            2     /* CSNET类（过时-仅用于某些过时RFC中的示例）*/
#define DNS_RRCLASS_CH            3     /* CHAOS类*/
#define DNS_RRCLASS_HS            4     /* 赫西奥德[戴尔87]*/
#define DNS_RRCLASS_ANY           255   /* 任何类别*/
#define DNS_RRCLASS_FLUSH         0x800 /* 平头钻头*/

/* DNS协议标志*/
#define DNS_FLAG1_RESPONSE        0x80
#define DNS_FLAG1_OPCODE_STATUS   0x10
#define DNS_FLAG1_OPCODE_INVERSE  0x08
#define DNS_FLAG1_OPCODE_STANDARD 0x00
#define DNS_FLAG1_AUTHORATIVE     0x04
#define DNS_FLAG1_TRUNC           0x02
#define DNS_FLAG1_RD              0x01
#define DNS_FLAG2_RA              0x80
#define DNS_FLAG2_ERR_MASK        0x0f
#define DNS_FLAG2_ERR_NONE        0x00
#define DNS_FLAG2_ERR_NAME        0x03

#define DNS_HDR_GET_OPCODE(hdr) ((((hdr)->flags1) >> 3) & 0xF)

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
/**DNS消息头*/
struct dns_hdr {
  PACK_STRUCT_FIELD(u16_t id);
  PACK_STRUCT_FLD_8(u8_t flags1);
  PACK_STRUCT_FLD_8(u8_t flags2);
  PACK_STRUCT_FIELD(u16_t numquestions);
  PACK_STRUCT_FIELD(u16_t numanswers);
  PACK_STRUCT_FIELD(u16_t numauthrr);
  PACK_STRUCT_FIELD(u16_t numextrarr);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif
#define SIZEOF_DNS_HDR 12


/* 多播DNS定义*/

/**用于多播DNS查询的UDP端口*/
#ifndef DNS_MQUERY_PORT
#define DNS_MQUERY_PORT             5353
#endif

/* 用于多播DNS查询的IPv4组：224.0.0.251*/
#ifndef DNS_MQUERY_IPV4_GROUP_INIT
#define DNS_MQUERY_IPV4_GROUP_INIT  IPADDR4_INIT_BYTES(224,0,0,251)
#endif

/* 用于多播DNS查询的IPv6组：FF02:：FB*/
#ifndef DNS_MQUERY_IPV6_GROUP_INIT
#define DNS_MQUERY_IPV6_GROUP_INIT  IPADDR6_INIT_HOST(0xFF020000,0,0,0xFB)
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_DNS_H */

