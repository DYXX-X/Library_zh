/**
 * @file 其他SNMPv3功能RFC3414和RFC3826（内部API，不在客户端代码中使用）。
 */

/*
 * 版权所有（c）2016 Elias Oenal。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Elias Oenal<lwip@eliasoenal.com>
 */

#ifndef LWIP_HDR_APPS_SNMP_V3_PRIV_H
#define LWIP_HDR_APPS_SNMP_V3_PRIV_H

#include "lwip/apps/snmp_opts.h"

#if LWIP_SNMP && LWIP_SNMP_V3

#include "lwip/apps/snmpv3.h"
#include "snmp_pbuf_stream.h"

/* 根据RFC 3411*/
#define SNMP_V3_MAX_ENGINE_ID_LENGTH  32
#define SNMP_V3_MAX_USER_LENGTH       32

#define SNMP_V3_MAX_AUTH_PARAM_LENGTH  12
#define SNMP_V3_MAX_PRIV_PARAM_LENGTH  8

#define SNMP_V3_MD5_LEN        16
#define SNMP_V3_SHA_LEN        20

typedef enum {
  SNMP_V3_PRIV_MODE_DECRYPT = 0,
  SNMP_V3_PRIV_MODE_ENCRYPT = 1
} snmpv3_priv_mode_t;

s32_t snmpv3_get_engine_boots_internal(void);
err_t snmpv3_auth(struct snmp_pbuf_stream *stream, u16_t length, const u8_t *key, snmpv3_auth_algo_t algo, u8_t *hmac_out);
err_t snmpv3_crypt(struct snmp_pbuf_stream *stream, u16_t length, const u8_t *key,
                   const u8_t *priv_param, const u32_t engine_boots, const u32_t engine_time, snmpv3_priv_algo_t algo, snmpv3_priv_mode_t mode);
err_t snmpv3_build_priv_param(u8_t *priv_param);
void snmpv3_enginetime_timer(void *arg);

#endif

#endif /* LWIP_HDR_APPS_SNMP_V3_PRIV_H */

