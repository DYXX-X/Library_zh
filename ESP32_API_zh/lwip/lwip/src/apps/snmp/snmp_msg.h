/**
 * @file SNMP代理消息处理结构（内部API，不在客户端代码中使用）。
 */

/*
 * 版权所有（c）2006 Axon Digital Design B.V.，荷兰。版权所有（c）2016 Elias Oenal。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Christiaan Simons <christiaan.simons@axon.tv> 马丁·亨策尔<info@cl-soft.de>埃利亚斯·欧纳尔<lwip@eliasoenal.com>
 */

#ifndef LWIP_HDR_APPS_SNMP_MSG_H
#define LWIP_HDR_APPS_SNMP_MSG_H

#include "lwip/apps/snmp_opts.h"

#if LWIP_SNMP

#include "lwip/apps/snmp.h"
#include "lwip/apps/snmp_core.h"
#include "snmp_pbuf_stream.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"

#if LWIP_SNMP_V3
#include "snmpv3_priv.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* PDU中使用的版本定义*/
#define SNMP_VERSION_1  0
#define SNMP_VERSION_2c 1
#define SNMP_VERSION_3  3

struct snmp_varbind_enumerator {
  struct snmp_pbuf_stream pbuf_stream;
  u16_t varbind_count;
};

typedef enum {
  SNMP_VB_ENUMERATOR_ERR_OK            = 0,
  SNMP_VB_ENUMERATOR_ERR_EOVB          = 1,
  SNMP_VB_ENUMERATOR_ERR_ASN1ERROR     = 2,
  SNMP_VB_ENUMERATOR_ERR_INVALIDLENGTH = 3
} snmp_vb_enumerator_err_t;

void snmp_vb_enumerator_init(struct snmp_varbind_enumerator *enumerator, struct pbuf *p, u16_t offset, u16_t length);
snmp_vb_enumerator_err_t snmp_vb_enumerator_get_next(struct snmp_varbind_enumerator *enumerator, struct snmp_varbind *varbind);

struct snmp_request {
  /* 通信手柄*/
  void *handle;
  /* 源IP地址*/
  const ip_addr_t *source_ip;
  /* 源UDP端口*/
  u16_t source_port;
  /* 传入snmp版本*/
  u8_t version;
  /* 社区名称（以零结尾）*/
  u8_t community[SNMP_MAX_COMMUNITY_STR_LEN + 1];
  /* 团体字符串长度（不包括零项）*/
  u16_t community_strlen;
  /* 请求类型*/
  u8_t request_type;
  /* 请求ID*/
  s32_t request_id;
  /* 错误状态*/
  s32_t error_status;
  /* 误差指数*/
  s32_t error_index;
  /* 非中继器（getBulkRequest（SNMPv2c））*/
  s32_t non_repeaters;
  /* 最大重复次数（getBulkRequest（SNMPv2c））*/
  s32_t max_repetitions;

  /* 通常响应pdu（2）。当检测到snmpv3错误时，报告pdu（8）*/
  u8_t request_out_type;

#if LWIP_SNMP_V3
  s32_t msg_id;
  s32_t msg_max_size;
  u8_t  msg_flags;
  s32_t msg_security_model;
  u8_t  msg_authoritative_engine_id[SNMP_V3_MAX_ENGINE_ID_LENGTH];
  u8_t  msg_authoritative_engine_id_len;
  s32_t msg_authoritative_engine_boots;
  s32_t msg_authoritative_engine_time;
  u8_t  msg_user_name[SNMP_V3_MAX_USER_LENGTH];
  u8_t  msg_user_name_len;
  u8_t  msg_authentication_parameters[SNMP_V3_MAX_AUTH_PARAM_LENGTH];
  u8_t  msg_authentication_parameters_len;
  u8_t  msg_privacy_parameters[SNMP_V3_MAX_PRIV_PARAM_LENGTH];
  u8_t  msg_privacy_parameters_len;
  u8_t  context_engine_id[SNMP_V3_MAX_ENGINE_ID_LENGTH];
  u8_t  context_engine_id_len;
  u8_t  context_name[SNMP_V3_MAX_ENGINE_ID_LENGTH];
  u8_t  context_name_len;
#endif

  struct pbuf *inbound_pbuf;
  struct snmp_varbind_enumerator inbound_varbind_enumerator;
  u16_t inbound_varbind_offset;
  u16_t inbound_varbind_len;
  u16_t inbound_padding_len;

  struct pbuf *outbound_pbuf;
  struct snmp_pbuf_stream outbound_pbuf_stream;
  u16_t outbound_pdu_offset;
  u16_t outbound_error_status_offset;
  u16_t outbound_error_index_offset;
  u16_t outbound_varbind_offset;
#if LWIP_SNMP_V3
  u16_t outbound_msg_global_data_offset;
  u16_t outbound_msg_global_data_end;
  u16_t outbound_msg_security_parameters_str_offset;
  u16_t outbound_msg_security_parameters_seq_offset;
  u16_t outbound_msg_security_parameters_end;
  u16_t outbound_msg_authentication_parameters_offset;
  u16_t outbound_scoped_pdu_seq_offset;
  u16_t outbound_scoped_pdu_string_offset;
#endif

  u8_t value_buffer[SNMP_MAX_VALUE_SIZE];
};

/**保存varbinds长度信息的帮助结构*/
struct snmp_varbind_len {
  u8_t  vb_len_len;
  u16_t vb_value_len;
  u8_t  oid_len_len;
  u16_t oid_value_len;
  u8_t  value_len_len;
  u16_t value_value_len;
};

/**代理社区字符串*/
extern const char *snmp_community;
/**用于写访问的代理社区字符串*/
extern const char *snmp_community_write;
/**发送陷阱的句柄*/
extern void *snmp_traps_handle;

void snmp_receive(void *handle, struct pbuf *p, const ip_addr_t *source_ip, u16_t port);
err_t snmp_sendto(void *handle, struct pbuf *p, const ip_addr_t *dst, u16_t port);
u8_t snmp_get_local_ip_for_dst(void *handle, const ip_addr_t *dst, ip_addr_t *result);
err_t snmp_varbind_length(struct snmp_varbind *varbind, struct snmp_varbind_len *len);
err_t snmp_append_outbound_varbind(struct snmp_pbuf_stream *pbuf_stream, struct snmp_varbind *varbind);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_SNMP */

#endif /* LWIP_HDR_APPS_SNMP_MSG_H */

