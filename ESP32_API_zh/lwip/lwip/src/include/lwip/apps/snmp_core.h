/**
 * @file 用于实现MIB的SNMP核心API
 */

/*
 * 版权所有（c）2006 Axon Digital Design B.V.，荷兰。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Christiaan Simons<christiaan.simons@axon.tv>马丁·亨策尔<info@cl-soft.de>
 */

#ifndef LWIP_HDR_APPS_SNMP_CORE_H
#define LWIP_HDR_APPS_SNMP_CORE_H

#include "lwip/apps/snmp_opts.h"

#if LWIP_SNMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/ip_addr.h"
#include "lwip/err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 基本ASN1定义*/
#define SNMP_ASN1_CLASS_UNIVERSAL   0x00
#define SNMP_ASN1_CLASS_APPLICATION 0x40
#define SNMP_ASN1_CLASS_CONTEXT     0x80
#define SNMP_ASN1_CLASS_PRIVATE     0xC0

#define SNMP_ASN1_CONTENTTYPE_PRIMITIVE   0x00
#define SNMP_ASN1_CONTENTTYPE_CONSTRUCTED 0x20

/* 通用标签（来自ASN.1规范）*/
#define SNMP_ASN1_UNIVERSAL_END_OF_CONTENT  0
#define SNMP_ASN1_UNIVERSAL_INTEGER         2
#define SNMP_ASN1_UNIVERSAL_OCTET_STRING    4
#define SNMP_ASN1_UNIVERSAL_NULL            5
#define SNMP_ASN1_UNIVERSAL_OBJECT_ID       6
#define SNMP_ASN1_UNIVERSAL_SEQUENCE_OF    16

/* 应用程序特定（SNMP）标记（来自SNMPv2 SMI）*/
#define SNMP_ASN1_APPLICATION_IPADDR    0  /* [APPLICATION 0] IMPLICIT OCTET STRING (SIZE (4)) */
#define SNMP_ASN1_APPLICATION_COUNTER   1  /* [应用程序1]隐式整数（0..4294967295）=>u32_t*/
#define SNMP_ASN1_APPLICATION_GAUGE     2  /* [应用程序2]隐式整数（0..4294967295）=>u32_t*/
#define SNMP_ASN1_APPLICATION_TIMETICKS 3  /* [应用程序3]隐式整数（0..4294967295）=>u32_t*/
#define SNMP_ASN1_APPLICATION_OPAQUE    4  /* [APPLICATION 4] IMPLICIT OCTET STRING */
#define SNMP_ASN1_APPLICATION_COUNTER64 6  /* [APPLICATION 6] IMPLICIT INTEGER (0..18446744073709551615) */

/* 上下文特定（SNMP）标记（来自RFC 1905）*/
#define SNMP_ASN1_CONTEXT_VARBIND_NO_SUCH_INSTANCE 1

/* 完整ASN1类型定义*/
#define SNMP_ASN1_TYPE_END_OF_CONTENT (SNMP_ASN1_CLASS_UNIVERSAL | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_UNIVERSAL_END_OF_CONTENT)
#define SNMP_ASN1_TYPE_INTEGER        (SNMP_ASN1_CLASS_UNIVERSAL | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_UNIVERSAL_INTEGER)
#define SNMP_ASN1_TYPE_OCTET_STRING   (SNMP_ASN1_CLASS_UNIVERSAL | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_UNIVERSAL_OCTET_STRING)
#define SNMP_ASN1_TYPE_NULL           (SNMP_ASN1_CLASS_UNIVERSAL | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_UNIVERSAL_NULL)
#define SNMP_ASN1_TYPE_OBJECT_ID      (SNMP_ASN1_CLASS_UNIVERSAL | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_UNIVERSAL_OBJECT_ID)
#define SNMP_ASN1_TYPE_SEQUENCE       (SNMP_ASN1_CLASS_UNIVERSAL | SNMP_ASN1_CONTENTTYPE_CONSTRUCTED | SNMP_ASN1_UNIVERSAL_SEQUENCE_OF)
#define SNMP_ASN1_TYPE_IPADDR         (SNMP_ASN1_CLASS_APPLICATION | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_APPLICATION_IPADDR)
#define SNMP_ASN1_TYPE_IPADDRESS      SNMP_ASN1_TYPE_IPADDR
#define SNMP_ASN1_TYPE_COUNTER        (SNMP_ASN1_CLASS_APPLICATION | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_APPLICATION_COUNTER)
#define SNMP_ASN1_TYPE_COUNTER32      SNMP_ASN1_TYPE_COUNTER
#define SNMP_ASN1_TYPE_GAUGE          (SNMP_ASN1_CLASS_APPLICATION | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_APPLICATION_GAUGE)
#define SNMP_ASN1_TYPE_GAUGE32        SNMP_ASN1_TYPE_GAUGE
#define SNMP_ASN1_TYPE_UNSIGNED32     SNMP_ASN1_TYPE_GAUGE
#define SNMP_ASN1_TYPE_TIMETICKS      (SNMP_ASN1_CLASS_APPLICATION | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_APPLICATION_TIMETICKS)
#define SNMP_ASN1_TYPE_OPAQUE         (SNMP_ASN1_CLASS_APPLICATION | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_APPLICATION_OPAQUE)
#if LWIP_HAVE_INT64
#define SNMP_ASN1_TYPE_COUNTER64      (SNMP_ASN1_CLASS_APPLICATION | SNMP_ASN1_CONTENTTYPE_PRIMITIVE | SNMP_ASN1_APPLICATION_COUNTER64)
#endif

#define SNMP_VARBIND_EXCEPTION_OFFSET 0xF0
#define SNMP_VARBIND_EXCEPTION_MASK   0x0F

/**SNMP保护预定义的错误代码。*/
typedef enum {
  SNMP_ERR_NOERROR             = 0,
/* 
过时的v1错误代码。不要使用更多#define SNMP_ERR_NOSUCHNAME 2改用SNMP_ERR _NOSUCHINSTANCE#define SNMP-ERR_BADVALUE 3改用SNMP-ERR_WRONGTYPE、SNMP_EERR_WRONGLENGTH、SNMP_ERR_WRONGENCODING或SNMP_ERL_WRONGVALUE#defin SNMP_ERR_READONLY 4改用SNMP_ERR _NOTWRITEABLE
*/
  SNMP_ERR_GENERROR            = 5,
  SNMP_ERR_NOACCESS            = 6,
  SNMP_ERR_WRONGTYPE           = 7,
  SNMP_ERR_WRONGLENGTH         = 8,
  SNMP_ERR_WRONGENCODING       = 9,
  SNMP_ERR_WRONGVALUE          = 10,
  SNMP_ERR_NOCREATION          = 11,
  SNMP_ERR_INCONSISTENTVALUE   = 12,
  SNMP_ERR_RESOURCEUNAVAILABLE = 13,
  SNMP_ERR_COMMITFAILED        = 14,
  SNMP_ERR_UNDOFAILED          = 15,
  SNMP_ERR_NOTWRITABLE         = 17,
  SNMP_ERR_INCONSISTENTNAME    = 18,

  SNMP_ERR_NOSUCHINSTANCE      = SNMP_VARBIND_EXCEPTION_OFFSET + SNMP_ASN1_CONTEXT_VARBIND_NO_SUCH_INSTANCE
} snmp_err_t;

/**内部对象标识符表示*/
struct snmp_obj_id
{
  u8_t len;
  u32_t id[SNMP_MAX_OBJ_ID_LEN];
};

struct snmp_obj_id_const_ref
{
  u8_t len;
  const u32_t* id;
};

extern const struct snmp_obj_id_const_ref snmp_zero_dot_zero; /* SNMPv2 SMI的管理标识符*/

/**SNMP变量值，用作结构SNMP_node_instance和表实现中的引用*/
union snmp_variant_value
{
  void* ptr;
  const void* const_ptr;
  u32_t u32;
  s32_t s32;
#if LWIP_HAVE_INT64
  u64_t u64;
#endif
};


/**
SNMP MIB节点类型树节点是堆栈可以处理以遍历树的唯一节点，所有其他节点都假定为叶节点。这不能是枚举，因为用户可能需要定义自己的节点类型。
*/
#define SNMP_NODE_TREE         0x00
/* 预定义的叶节点类型*/
#define SNMP_NODE_SCALAR       0x01
#define SNMP_NODE_SCALAR_ARRAY 0x02
#define SNMP_NODE_TABLE        0x03
#define SNMP_NODE_THREADSYNC   0x04

/**节点“基类”布局，节点的必填字段*/
struct snmp_node
{
  /**SNMP_NODE_TREE之一或任何叶节点类型（如SNMP_NODE_SCALAR）*/
  u8_t node_type;
  /**分配给此节点的编号，用作完整OID的一部分*/
  u32_t oid;
};

/**SNMP节点实例访问类型*/
typedef enum {
  SNMP_NODE_INSTANCE_ACCESS_READ    = 1,
  SNMP_NODE_INSTANCE_ACCESS_WRITE   = 2,
  SNMP_NODE_INSTANCE_READ_ONLY      = SNMP_NODE_INSTANCE_ACCESS_READ,
  SNMP_NODE_INSTANCE_READ_WRITE     = (SNMP_NODE_INSTANCE_ACCESS_READ | SNMP_NODE_INSTANCE_ACCESS_WRITE),
  SNMP_NODE_INSTANCE_WRITE_ONLY     = SNMP_NODE_INSTANCE_ACCESS_WRITE,
  SNMP_NODE_INSTANCE_NOT_ACCESSIBLE = 0
} snmp_access_t;

struct snmp_node_instance;

typedef s16_t (*node_instance_get_value_method)(struct snmp_node_instance*, void*);
typedef snmp_err_t (*node_instance_set_test_method)(struct snmp_node_instance*, u16_t, void*);
typedef snmp_err_t (*node_instance_set_value_method)(struct snmp_node_instance*, u16_t, void*);
typedef void (*node_instance_release_method)(struct snmp_node_instance*);

#define SNMP_GET_VALUE_RAW_DATA 0x4000  /* 不要使用0x8000，因为node_instance_get_value_method的返回值是signed16，0x8000将是有符号位*/

/**SNMP节点实例*/
struct snmp_node_instance
{
  /**预先填充了节点，get_instance（）被调用；可以由用户更改为任意值，以便在调用get_instance（）和get_value/test_value/set_value之间传递任意节点*/
  const struct snmp_node* node;
  /**预先填充了请求的实例id；对于get_instance（），这是所请求的id；对于get_next_instance（），这是相对的起点，堆栈需要下一个节点的相对oid*/
  struct snmp_obj_id instance_oid;

  /**此对象的ASN类型（有关定义，请参见snmp_asn1.h）*/
  u8_t asn1_type;
  /**上面定义的实例访问类型之一（SNMP_NODE_instance_READ_ONLY，…）*/
  snmp_access_t access;

  /**返回给定对象标识符的对象值。返回值<0表示错误*/
  node_instance_get_value_method get_value;
  /**设置前测试长度和/或范围*/
  node_instance_set_test_method set_test;
  /**设置对象值，仅在set_test（）成功时调用*/
  node_instance_set_value_method set_value;
  /**在堆栈不再需要实例的任何情况下调用（用于释放在get_instance/get_next_instance方法中分配的内存）*/
  node_instance_release_method release_instance;

  /**在调用get_instance（）和get_value/test_value/set_value之间传递任意值的引用*/
  union snmp_variant_value reference;
  /**参见引用（如果引用是指针，则基础数据的长度可以存储在此处或其他任何位置）*/
  u32_t reference_len;
};


/**SNMP树节点*/
struct snmp_tree_node
{
  /**继承的“基类”成员*/
  struct snmp_node node;
  u16_t subnode_count;
  const struct snmp_node* const *subnodes;
};

#define SNMP_CREATE_TREE_NODE(oid, subnodes) \
  {{ SNMP_NODE_TREE, (oid) }, \
  (u16_t)LWIP_ARRAYSIZE(subnodes), (subnodes) }

#define SNMP_CREATE_EMPTY_TREE_NODE(oid) \
  {{ SNMP_NODE_TREE, (oid) }, \
  0, NULL }

/**SNMP叶节点*/
struct snmp_leaf_node
{
  /**继承的“基类”成员*/
  struct snmp_node node;
  snmp_err_t (*get_instance)(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
  snmp_err_t (*get_next_instance)(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
};

/**表示具有其基oid和根节点的单个mib*/
struct snmp_mib
{
  const u32_t *base_oid;
  u8_t base_oid_len;
  const struct snmp_node *root_node;
};

#define SNMP_MIB_CREATE(oid_list, root_node) { (oid_list), (u8_t)LWIP_ARRAYSIZE(oid_list), root_node }

/**OID范围结构*/
struct snmp_oid_range
{
  u32_t min;
  u32_t max;
};

/**检查传入OID长度和值是否在允许的范围内*/
u8_t snmp_oid_in_range(const u32_t *oid_in, u8_t oid_len, const struct snmp_oid_range *oid_ranges, u8_t oid_ranges_len);

typedef enum {
  SNMP_NEXT_OID_STATUS_SUCCESS,
  SNMP_NEXT_OID_STATUS_NO_MATCH,
  SNMP_NEXT_OID_STATUS_BUF_TO_SMALL
} snmp_next_oid_status_t;

/**next_oid_init/next_oid_check函数的状态*/
struct snmp_next_oid_state
{
  const u32_t* start_oid;
  u8_t start_oid_len;

  u32_t* next_oid;
  u8_t next_oid_len;
  u8_t next_oid_max_len;

  snmp_next_oid_status_t status;
  void* reference;
};

void snmp_next_oid_init(struct snmp_next_oid_state *state,
  const u32_t *start_oid, u8_t start_oid_len,
  u32_t *next_oid_buf, u8_t next_oid_max_len);
u8_t snmp_next_oid_precheck(struct snmp_next_oid_state *state, const u32_t *oid, u8_t oid_len);
u8_t snmp_next_oid_check(struct snmp_next_oid_state *state, const u32_t *oid, u8_t oid_len, void* reference);

void snmp_oid_assign(struct snmp_obj_id* target, const u32_t *oid, u8_t oid_len);
void snmp_oid_combine(struct snmp_obj_id* target, const u32_t *oid1, u8_t oid1_len, const u32_t *oid2, u8_t oid2_len);
void snmp_oid_prefix(struct snmp_obj_id* target, const u32_t *oid, u8_t oid_len);
void snmp_oid_append(struct snmp_obj_id* target, const u32_t *oid, u8_t oid_len);
u8_t snmp_oid_equal(const u32_t *oid1, u8_t oid1_len, const u32_t *oid2, u8_t oid2_len);
s8_t snmp_oid_compare(const u32_t *oid1, u8_t oid1_len, const u32_t *oid2, u8_t oid2_len);

#if LWIP_IPV4
u8_t snmp_oid_to_ip4(const u32_t *oid, ip4_addr_t *ip);
void snmp_ip4_to_oid(const ip4_addr_t *ip, u32_t *oid);
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
u8_t snmp_oid_to_ip6(const u32_t *oid, ip6_addr_t *ip);
void snmp_ip6_to_oid(const ip6_addr_t *ip, u32_t *oid);
#endif /* LWIP_IPV6 */
#if LWIP_IPV4 || LWIP_IPV6
u8_t snmp_ip_to_oid(const ip_addr_t *ip, u32_t *oid);
u8_t snmp_ip_port_to_oid(const ip_addr_t *ip, u16_t port, u32_t *oid);

u8_t snmp_oid_to_ip(const u32_t *oid, u8_t oid_len, ip_addr_t *ip);
u8_t snmp_oid_to_ip_port(const u32_t *oid, u8_t oid_len, ip_addr_t *ip, u16_t *port);
#endif /* LWIP_IPV4 || LWIP_IPV6 */

struct netif;
u8_t netif_to_num(const struct netif *netif);

snmp_err_t snmp_set_test_ok(struct snmp_node_instance* instance, u16_t value_len, void* value); /* 如果测试总是成功，可以使用的通用函数*/

err_t snmp_decode_bits(const u8_t *buf, u32_t buf_len, u32_t *bit_value);
err_t snmp_decode_truthvalue(const s32_t *asn1_value, u8_t *bool_value);
u8_t  snmp_encode_bits(u8_t *buf, u32_t buf_len, u32_t bit_value, u8_t bit_count);
u8_t  snmp_encode_truthvalue(s32_t *asn1_value, u32_t bool_value);

struct snmp_statistics
{
  u32_t inpkts;
  u32_t outpkts;
  u32_t inbadversions;
  u32_t inbadcommunitynames;
  u32_t inbadcommunityuses;
  u32_t inasnparseerrs;
  u32_t intoobigs;
  u32_t innosuchnames;
  u32_t inbadvalues;
  u32_t inreadonlys;
  u32_t ingenerrs;
  u32_t intotalreqvars;
  u32_t intotalsetvars;
  u32_t ingetrequests;
  u32_t ingetnexts;
  u32_t insetrequests;
  u32_t ingetresponses;
  u32_t intraps;
  u32_t outtoobigs;
  u32_t outnosuchnames;
  u32_t outbadvalues;
  u32_t outgenerrs;
  u32_t outgetrequests;
  u32_t outgetnexts;
  u32_t outsetrequests;
  u32_t outgetresponses;
  u32_t outtraps;
#if LWIP_SNMP_V3
  u32_t unsupportedseclevels;
  u32_t notintimewindows;
  u32_t unknownusernames;
  u32_t unknownengineids;
  u32_t wrongdigests;
  u32_t decryptionerrors;
#endif
};

extern struct snmp_statistics snmp_stats;

#ifdef __cplusplus
}
#endif

#endif /* LWIP_SNMP */

#endif /* LWIP_HDR_APPS_SNMP_CORE_H */

