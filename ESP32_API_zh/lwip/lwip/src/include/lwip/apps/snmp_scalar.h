/**
 * @file 用于实现标量节点的SNMP服务器MIB API
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
 * 作者：Martin Hentschel<info@cl-soft.de>
 *
 */

#ifndef LWIP_HDR_APPS_SNMP_SCALAR_H
#define LWIP_HDR_APPS_SNMP_SCALAR_H

#include "lwip/apps/snmp_opts.h"
#include "lwip/apps/snmp_core.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/**基本标量节点*/
struct snmp_scalar_node
{
  /**继承的“基类”成员*/
  struct snmp_leaf_node node;
  u8_t asn1_type;
  snmp_access_t access;
  node_instance_get_value_method get_value;
  node_instance_set_test_method set_test;
  node_instance_set_value_method set_value;
};


snmp_err_t snmp_scalar_get_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
snmp_err_t snmp_scalar_get_next_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);

#define SNMP_SCALAR_CREATE_NODE(oid, access, asn1_type, get_value_method, set_test_method, set_value_method) \
  {{{ SNMP_NODE_SCALAR, (oid) }, \
    snmp_scalar_get_instance, \
    snmp_scalar_get_next_instance }, \
    (asn1_type), (access), (get_value_method), (set_test_method), (set_value_method) }

#define SNMP_SCALAR_CREATE_NODE_READONLY(oid, asn1_type, get_value_method) SNMP_SCALAR_CREATE_NODE(oid, SNMP_NODE_INSTANCE_READ_ONLY, asn1_type, get_value_method, NULL, NULL)

/**标量数组节点-仅包含子级标量的树节点*/
struct snmp_scalar_array_node_def
{
  u32_t         oid;
  u8_t          asn1_type;
  snmp_access_t access;
};

typedef s16_t (*snmp_scalar_array_get_value_method)(const struct snmp_scalar_array_node_def*, void*);
typedef snmp_err_t (*snmp_scalar_array_set_test_method)(const struct snmp_scalar_array_node_def*, u16_t, void*);
typedef snmp_err_t (*snmp_scalar_array_set_value_method)(const struct snmp_scalar_array_node_def*, u16_t, void*);

/**基本标量数组节点*/
struct snmp_scalar_array_node
{
  /**继承的“基类”成员*/
  struct snmp_leaf_node node;
  u16_t array_node_count;
  const struct snmp_scalar_array_node_def* array_nodes;
  snmp_scalar_array_get_value_method get_value;
  snmp_scalar_array_set_test_method set_test;
  snmp_scalar_array_set_value_method set_value;
};

snmp_err_t snmp_scalar_array_get_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
snmp_err_t snmp_scalar_array_get_next_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);

#define SNMP_SCALAR_CREATE_ARRAY_NODE(oid, array_nodes, get_value_method, set_test_method, set_value_method) \
  {{{ SNMP_NODE_SCALAR_ARRAY, (oid) }, \
    snmp_scalar_array_get_instance, \
    snmp_scalar_array_get_next_instance }, \
    (u16_t)LWIP_ARRAYSIZE(array_nodes), (array_nodes), (get_value_method), (set_test_method), (set_value_method) }

#endif /* LWIP_SNMP */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SNMP_SCALAR_H */

