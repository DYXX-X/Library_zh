/*****************************************************************************
* 第页。h-lwIP的以太网PPP实现。
*
* 版权所有（c）2006 Marc Boucher，Services Informatiques（MBSI）inc。
*
* 作者特此授予出于任何目的使用、复制、修改、分发和许可本软件及其文档的权利，前提是所有副本中保留现有版权声明，并且本声明和以下免责声明均包含在任何分发中。任何授权用途都不需要书面协议、许可证或版税。
*
* THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS *AS IS* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************** REVISION HISTORY
*
* 06-01-01马克·鲍彻<marc@mbsi.ca>移植到lwIP。
*****************************************************************************/



/* 基于NetBSD:if_pppoe。c、 v 1.64 2006/01/31 23:50:15马丁Exp*/

/*-
 * 版权所有（c）2002 The NetBSD Foundation，Inc.保留所有权利。
 *
 * 此代码源自Martin Husemann为NetBSD基金会提供的软件<martin@NetBSD.org>.
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.所有提及本软件功能或使用的广告材料必须显示以下确认信息：本产品包括NetBSD Foundation，Inc.及其贡献者开发的软件。4.未经事先书面许可，不得使用NetBSD基金会的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PPPOE_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef PPP_OE_H
#define PPP_OE_H

#include "ppp.h"
#include "lwip/etharp.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct pppoehdr {
  PACK_STRUCT_FLD_8(u8_t vertype);
  PACK_STRUCT_FLD_8(u8_t code);
  PACK_STRUCT_FIELD(u16_t session);
  PACK_STRUCT_FIELD(u16_t plen);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct pppoetag {
  PACK_STRUCT_FIELD(u16_t tag);
  PACK_STRUCT_FIELD(u16_t len);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif


#define PPPOE_STATE_INITIAL   0
#define PPPOE_STATE_PADI_SENT 1
#define PPPOE_STATE_PADR_SENT 2
#define PPPOE_STATE_SESSION   3
/* 消极的*/
#define PPPOE_STATE_PADO_SENT 1

#define PPPOE_HEADERLEN       sizeof(struct pppoehdr)
#define PPPOE_VERTYPE         0x11    /* VER=1, TYPE = 1 */

#define PPPOE_TAG_EOL         0x0000  /* 列表末尾*/
#define PPPOE_TAG_SNAME       0x0101  /* 服务名称*/
#define PPPOE_TAG_ACNAME      0x0102  /* 访问集中器名称*/
#define PPPOE_TAG_HUNIQUE     0x0103  /* 主机唯一的*/
#define PPPOE_TAG_ACCOOKIE    0x0104  /* AC cookie*/
#define PPPOE_TAG_VENDOR      0x0105  /* 特定于供应商*/
#define PPPOE_TAG_RELAYSID    0x0110  /* 中继会话id*/
#define PPPOE_TAG_SNAME_ERR   0x0201  /* 服务名称错误*/
#define PPPOE_TAG_ACSYS_ERR   0x0202  /* 交流系统错误*/
#define PPPOE_TAG_GENERIC_ERR 0x0203  /* gerneric错误*/

#define PPPOE_CODE_PADI       0x09    /* 活动发现启动*/
#define PPPOE_CODE_PADO       0x07    /* 主动发现服务*/
#define PPPOE_CODE_PADR       0x19    /* 活动发现请求*/
#define PPPOE_CODE_PADS       0x65    /* 活动发现会话确认*/
#define PPPOE_CODE_PADT       0xA7    /* 活动发现终止*/

#ifndef PPPOE_MAX_AC_COOKIE_LEN
#define PPPOE_MAX_AC_COOKIE_LEN   64
#endif

struct pppoe_softc {
  struct pppoe_softc *next;
  struct netif *sc_ethif;      /* 我们使用的以太网接口*/
  ppp_pcb *pcb;                /* PPP PCB */

  struct eth_addr sc_dest;     /* 集中器硬件地址*/
  u16_t sc_session;            /* PPPoE会话id*/
  u8_t sc_state;               /* 发现阶段或会话已连接*/

#if PPPOE_SCNAME_SUPPORT
  const char *sc_service_name;      /* 如果！=NULL：请求的服务名称*/
  const char *sc_concentrator_name; /* 如果！=NULL：请求的集中器id*/
#endif /* PPPOE_SCNAME_SUPPORT */
  u8_t sc_ac_cookie[PPPOE_MAX_AC_COOKIE_LEN]; /* 我们必须回复AC cookie的内容*/
  u8_t sc_ac_cookie_len;       /* cookie数据长度*/
#ifdef PPPOE_SERVER
  u8_t *sc_hunique;            /* 主机的内容是唯一的，我们必须回应*/
  u8_t sc_hunique_len;         /* 主机唯一长度*/
#endif
  u8_t sc_padi_retried;        /* 已完成的PADI重试次数*/
  u8_t sc_padr_retried;        /* 已完成的PADR重试次数*/
};


#define pppoe_init() /* 兼容性定义，无需初始化*/

ppp_pcb *pppoe_create(struct netif *pppif,
       struct netif *ethif,
       const char *service_name, const char *concentrator_name,
       ppp_link_status_cb_fn link_status_cb, void *ctx_cb);

/*
 * 从lwIP调用的函数不能从lwIP用户应用程序调用。
 */
void pppoe_disc_input(struct netif *netif, struct pbuf *p);
void pppoe_data_input(struct netif *netif, struct pbuf *p);

#ifdef __cplusplus
}
#endif

#endif /* PPP_OE_H */

#endif /* PPP_SUPPORT && PPPOE_SUPPORT */

