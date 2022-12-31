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
 * 作者：Martin Hentschel<info@cl-soft.de>
 *
 */

#ifndef LWIP_HDR_APPS_SNMP_CORE_PRIV_H
#define LWIP_HDR_APPS_SNMP_CORE_PRIV_H

#include "lwip/apps/snmp_opts.h"

#if LWIP_SNMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/apps/snmp_core.h"
#include "snmp_asn1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* （过时）SNMPv1错误代码不再由MIBS使用，但核心需要正确响应v1请求
 */
#define SNMP_ERR_NOSUCHNAME 2
#define SNMP_ERR_BADVALUE   3
#define SNMP_ERR_READONLY   4
/* MIBS不得再使用内部错误代码，但核心需要正确响应v1请求
 */
#define SNMP_ERR_TOOBIG               1
#define SNMP_ERR_AUTHORIZATIONERROR   16

#define SNMP_ERR_UNKNOWN_ENGINEID     30
#define SNMP_ERR_UNKNOWN_SECURITYNAME 31
#define SNMP_ERR_UNSUPPORTED_SECLEVEL 32
#define SNMP_ERR_NOTINTIMEWINDOW      33
#define SNMP_ERR_DECRYIPTION_ERROR    34

#define SNMP_ERR_NOSUCHOBJECT         SNMP_VARBIND_EXCEPTION_OFFSET + SNMP_ASN1_CONTEXT_VARBIND_NO_SUCH_OBJECT
#define SNMP_ERR_ENDOFMIBVIEW         SNMP_VARBIND_EXCEPTION_OFFSET + SNMP_ASN1_CONTEXT_VARBIND_END_OF_MIB_VIEW


const struct snmp_node *snmp_mib_tree_resolve_exact(const struct snmp_mib *mib, const u32_t *oid, u8_t oid_len, u8_t *oid_instance_len);
const struct snmp_node *snmp_mib_tree_resolve_next(const struct snmp_mib *mib, const u32_t *oid, u8_t oid_len, struct snmp_obj_id *oidret);

typedef u8_t (*snmp_validate_node_instance_method)(struct snmp_node_instance *, void *);

u8_t snmp_get_node_instance_from_oid(const u32_t *oid, u8_t oid_len, struct snmp_node_instance *node_instance);
u8_t snmp_get_next_node_instance_from_oid(const u32_t *oid, u8_t oid_len, snmp_validate_node_instance_method validate_node_instance_method, void *validate_node_instance_arg, struct snmp_obj_id *node_oid, struct snmp_node_instance *node_instance);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_SNMP */

#endif /* LWIP_HDR_APPS_SNMP_CORE_PRIV_H */

