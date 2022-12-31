/**
 * @file ICMP6协议定义
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
#ifndef LWIP_HDR_PROT_ICMP6_H
#define LWIP_HDR_PROT_ICMP6_H

#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/**ICMP类型*/
enum icmp6_type {
  /**无法访问目标*/
  ICMP6_TYPE_DUR = 1,
  /**数据包太大*/
  ICMP6_TYPE_PTB = 2,
  /**超过的时间*/
  ICMP6_TYPE_TE = 3,
  /**参数问题*/
  ICMP6_TYPE_PP = 4,
  /**私人实验*/
  ICMP6_TYPE_PE1 = 100,
  /**私人实验*/
  ICMP6_TYPE_PE2 = 101,
  /**保留用于扩展错误消息*/
  ICMP6_TYPE_RSV_ERR = 127,

  /**回显请求*/
  ICMP6_TYPE_EREQ = 128,
  /**回音回复*/
  ICMP6_TYPE_EREP = 129,
  /**多播侦听器查询*/
  ICMP6_TYPE_MLQ = 130,
  /**多播侦听器报告*/
  ICMP6_TYPE_MLR = 131,
  /**多播侦听器已完成*/
  ICMP6_TYPE_MLD = 132,
  /**路由器请求*/
  ICMP6_TYPE_RS = 133,
  /**路由器广告*/
  ICMP6_TYPE_RA = 134,
  /**邻居邀请*/
  ICMP6_TYPE_NS = 135,
  /**邻居广告*/
  ICMP6_TYPE_NA = 136,
  /**重定向*/
  ICMP6_TYPE_RD = 137,
  /**多播路由器公告*/
  ICMP6_TYPE_MRA = 151,
  /**多播路由器请求*/
  ICMP6_TYPE_MRS = 152,
  /**多播路由器终止*/
  ICMP6_TYPE_MRT = 153,
  /**私人实验*/
  ICMP6_TYPE_PE3 = 200,
  /**私人实验*/
  ICMP6_TYPE_PE4 = 201,
  /**保留用于扩展信息性消息*/
  ICMP6_TYPE_RSV_INF = 255
};

/**ICMP目标不可访问代码*/
enum icmp6_dur_code {
  /**没有到达目的地的路线*/
  ICMP6_DUR_NO_ROUTE = 0,
  /**行政禁止与目的地通信*/
  ICMP6_DUR_PROHIBITED = 1,
  /**超出源地址范围*/
  ICMP6_DUR_SCOPE = 2,
  /**无法访问地址*/
  ICMP6_DUR_ADDRESS = 3,
  /**无法访问端口*/
  ICMP6_DUR_PORT = 4,
  /**源地址入口/出口策略失败*/
  ICMP6_DUR_POLICY = 5,
  /**拒绝到目的地的路线*/
  ICMP6_DUR_REJECT_ROUTE = 6
};

/**ICMP超时代码*/
enum icmp6_te_code {
  /**传输中超过跃点限制*/
  ICMP6_TE_HL = 0,
  /**碎片重组时间超过*/
  ICMP6_TE_FRAG = 1
};

/**ICMP参数代码*/
enum icmp6_pp_code {
  /**遇到错误的标头字段*/
  ICMP6_PP_FIELD = 0,
  /**遇到无法识别的下一个标头类型*/
  ICMP6_PP_HEADER = 1,
  /**遇到无法识别的IPv6选项*/
  ICMP6_PP_OPTION = 2
};

/**这是标准ICMP6标头。*/
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct icmp6_hdr {
  PACK_STRUCT_FLD_8(u8_t type);
  PACK_STRUCT_FLD_8(u8_t code);
  PACK_STRUCT_FIELD(u16_t chksum);
  PACK_STRUCT_FIELD(u32_t data);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/**这是适用于回波请求/响应的ICMP6报头。*/
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct icmp6_echo_hdr {
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

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_ICMP6_H */

