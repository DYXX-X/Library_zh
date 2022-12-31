/**
 * @file 用于实现表节点的SNMP服务器MIB API
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

#ifndef LWIP_HDR_APPS_SNMP_TABLE_H
#define LWIP_HDR_APPS_SNMP_TABLE_H

#include "lwip/apps/snmp_opts.h"
#include "lwip/apps/snmp_core.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/**默认（可自定义）读/写表*/
struct snmp_table_col_def
{
  u32_t index;
  u8_t asn1_type;
  snmp_access_t access;
};

/**表节点*/
struct snmp_table_node
{
  /**继承的“基类”成员*/
  struct snmp_leaf_node node;
  u16_t column_count;
  const struct snmp_table_col_def* columns;
  snmp_err_t (*get_cell_instance)(const u32_t* column, const u32_t* row_oid, u8_t row_oid_len, struct snmp_node_instance* cell_instance);
  snmp_err_t (*get_next_cell_instance)(const u32_t* column, struct snmp_obj_id* row_oid, struct snmp_node_instance* cell_instance);
  /**返回给定对象标识符的对象值*/
  node_instance_get_value_method get_value;
  /**设置前测试长度和/或范围*/
  node_instance_set_test_method set_test;
  /**设置对象值，仅在set_test（）成功时调用*/
  node_instance_set_value_method set_value;
};

snmp_err_t snmp_table_get_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
snmp_err_t snmp_table_get_next_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);

#define SNMP_TABLE_CREATE(oid, columns, get_cell_instance_method, get_next_cell_instance_method, get_value_method, set_test_method, set_value_method) \
  {{{ SNMP_NODE_TABLE, (oid) }, \
  snmp_table_get_instance, \
  snmp_table_get_next_instance }, \
  (u16_t)LWIP_ARRAYSIZE(columns), (columns), \
  (get_cell_instance_method), (get_next_cell_instance_method), \
  (get_value_method), (set_test_method), (set_value_method)}

#define SNMP_TABLE_GET_COLUMN_FROM_OID(oid) ((oid)[1]) /* 第一个数组值是（固定的）行条目（固定为1），第二个值是列，后跟实例*/


/**简单只读表*/
typedef enum {
  SNMP_VARIANT_VALUE_TYPE_U32,
  SNMP_VARIANT_VALUE_TYPE_S32,
  SNMP_VARIANT_VALUE_TYPE_PTR,
  SNMP_VARIANT_VALUE_TYPE_CONST_PTR
} snmp_table_column_data_type_t;

struct snmp_table_simple_col_def
{
  u32_t index;
  u8_t asn1_type;
  snmp_table_column_data_type_t data_type; /* 取决于用于存储值的联合成员*/
};

/**简单只读表节点*/
struct snmp_table_simple_node
{
  /* 继承的“基类”成员*/
  struct snmp_leaf_node node;
  u16_t column_count;
  const struct snmp_table_simple_col_def* columns;
  snmp_err_t (*get_cell_value)(const u32_t* column, const u32_t* row_oid, u8_t row_oid_len, union snmp_variant_value* value, u32_t* value_len);
  snmp_err_t (*get_next_cell_instance_and_value)(const u32_t* column, struct snmp_obj_id* row_oid, union snmp_variant_value* value, u32_t* value_len);
};

snmp_err_t snmp_table_simple_get_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
snmp_err_t snmp_table_simple_get_next_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);

#define SNMP_TABLE_CREATE_SIMPLE(oid, columns, get_cell_value_method, get_next_cell_instance_and_value_method) \
  {{{ SNMP_NODE_TABLE, (oid) }, \
  snmp_table_simple_get_instance, \
  snmp_table_simple_get_next_instance }, \
  (u16_t)LWIP_ARRAYSIZE(columns), (columns), (get_cell_value_method), (get_next_cell_instance_and_value_method) }

s16_t snmp_table_extract_value_from_s32ref(struct snmp_node_instance* instance, void* value);
s16_t snmp_table_extract_value_from_u32ref(struct snmp_node_instance* instance, void* value);
s16_t snmp_table_extract_value_from_refconstptr(struct snmp_node_instance* instance, void* value);

#endif /* LWIP_SNMP */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SNMP_TABLE_H */

