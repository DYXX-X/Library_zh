/**
 * \文件asn1.h
 *
 * \简短的通用ASN。1解析
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#ifndef MBEDTLS_ASN1_H
#define MBEDTLS_ASN1_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

#if defined(MBEDTLS_BIGNUM_C)
#include "mbedtls/bignum.h"
#endif

/**
 * \将组添加为n1_模块\{
 */

/**
 * \name ASN1错误代码这些错误代码与X509错误代码进行“或”运算，以获得更高的错误粒度。ASN1是指定数据结构的标准\{
 */
#define MBEDTLS_ERR_ASN1_OUT_OF_DATA                      -0x0060  /**<解析ASN1数据结构时数据不足。*/
#define MBEDTLS_ERR_ASN1_UNEXPECTED_TAG                   -0x0062  /**<ASN1标记具有意外值。*/
#define MBEDTLS_ERR_ASN1_INVALID_LENGTH                   -0x0064  /**<尝试确定长度或无效长度时出错。*/
#define MBEDTLS_ERR_ASN1_LENGTH_MISMATCH                  -0x0066  /**<实际长度与预期长度不同。*/
#define MBEDTLS_ERR_ASN1_INVALID_DATA                     -0x0068  /**<数据无效。*/
#define MBEDTLS_ERR_ASN1_ALLOC_FAILED                     -0x006A  /**<内存分配失败*/
#define MBEDTLS_ERR_ASN1_BUF_TOO_SMALL                    -0x006C  /**<写入ASN时缓冲区太小。1数据结构。*/

/* \}名称*/

/**
 * \name DER常量这些常量符合DER编码的ASN。1个类型标签。DER编码使用十六进制表示。DER序列示例如下：\n
 * -0x02—指示INTEGER的标记
 * -0x01—八位字节长度
 * -0x05--value此类序列通常被读取到\c:：mbedtls_x509_buf中\{
 */
#define MBEDTLS_ASN1_BOOLEAN                 0x01
#define MBEDTLS_ASN1_INTEGER                 0x02
#define MBEDTLS_ASN1_BIT_STRING              0x03
#define MBEDTLS_ASN1_OCTET_STRING            0x04
#define MBEDTLS_ASN1_NULL                    0x05
#define MBEDTLS_ASN1_OID                     0x06
#define MBEDTLS_ASN1_ENUMERATED              0x0A
#define MBEDTLS_ASN1_UTF8_STRING             0x0C
#define MBEDTLS_ASN1_SEQUENCE                0x10
#define MBEDTLS_ASN1_SET                     0x11
#define MBEDTLS_ASN1_PRINTABLE_STRING        0x13
#define MBEDTLS_ASN1_T61_STRING              0x14
#define MBEDTLS_ASN1_IA5_STRING              0x16
#define MBEDTLS_ASN1_UTC_TIME                0x17
#define MBEDTLS_ASN1_GENERALIZED_TIME        0x18
#define MBEDTLS_ASN1_UNIVERSAL_STRING        0x1C
#define MBEDTLS_ASN1_BMP_STRING              0x1E
#define MBEDTLS_ASN1_PRIMITIVE               0x00
#define MBEDTLS_ASN1_CONSTRUCTED             0x20
#define MBEDTLS_ASN1_CONTEXT_SPECIFIC        0x80

/* 与规范实现相比，检查标记是否为字符串标记的方法稍小。*/
#define MBEDTLS_ASN1_IS_STRING_TAG( tag )                                     \
    ( ( tag ) < 32u && (                                                      \
        ( ( 1u << ( tag ) ) & ( ( 1u << MBEDTLS_ASN1_BMP_STRING )       |     \
                                ( 1u << MBEDTLS_ASN1_UTF8_STRING )      |     \
                                ( 1u << MBEDTLS_ASN1_T61_STRING )       |     \
                                ( 1u << MBEDTLS_ASN1_IA5_STRING )       |     \
                                ( 1u << MBEDTLS_ASN1_UNIVERSAL_STRING ) |     \
                                ( 1u << MBEDTLS_ASN1_PRINTABLE_STRING ) |     \
                                ( 1u << MBEDTLS_ASN1_BIT_STRING ) ) ) != 0 ) )

/*
 * ASN的每个组件的位掩码。ITU X.690（08/2015）第8.1节“编码通用规则”第8.1.2.2段中规定的1个标签：
 *
 * Bit 8 7 6 5 1+-------+--------+---------------+|类别| P/C |标签号|+-------+-----+------------+
 */
#define MBEDTLS_ASN1_TAG_CLASS_MASK          0xC0
#define MBEDTLS_ASN1_TAG_PC_MASK             0x20
#define MBEDTLS_ASN1_TAG_VALUE_MASK          0x1F

/* \}名称*/
/* \}将组添加为n1_模块*/

/**返回二进制字符串的大小，不带尾部\\0*/
#define MBEDTLS_OID_SIZE(x) (sizeof(x) - 1)

/**
 * 将mbedtls_asn1_buf结构与引用OID进行比较。
 *
 * 仅适用于“定义的”oid_str值（MBEDTLS_oid_MAC_SHA1），此处不能使用“无符号字符oid”！
 */
#define MBEDTLS_OID_CMP(oid_str, oid_buf)                                   \
        ( ( MBEDTLS_OID_SIZE(oid_str) != (oid_buf)->len ) ||                \
          memcmp( (oid_str), (oid_buf)->p, (oid_buf)->len) != 0 )

#define MBEDTLS_OID_CMP_RAW(oid_str, oid_buf, oid_buf_len)              \
        ( ( MBEDTLS_OID_SIZE(oid_str) != (oid_buf_len) ) ||             \
          memcmp( (oid_str), (oid_buf), (oid_buf_len) ) != 0 )

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name解析ASN的函数。1数据结构\{
 */

/**
 * 类型长度值结构，允许ASN1使用DER。
 */
typedef struct mbedtls_asn1_buf
{
    int tag;                /**<ASN1类型，例如MBEDTLS_ASN1_UTF8_STRING。*/
    size_t len;             /**<ASN1长度，以八位字节为单位。*/
    unsigned char *p;       /**<ASN1数据，例如ASCII。*/
}
mbedtls_asn1_buf;

/**
 * ASN1位字符串的容器。
 */
typedef struct mbedtls_asn1_bitstring
{
    size_t len;                 /**<ASN1长度，以八位字节为单位。*/
    unsigned char unused_bits;  /**<字符串末尾未使用的位数*/
    unsigned char *p;           /**<位串的原始ASN1数据*/
}
mbedtls_asn1_bitstring;

/**
 * ASN序列的容器。1项
 */
typedef struct mbedtls_asn1_sequence
{
    mbedtls_asn1_buf buf;                   /**<包含给定ASN的缓冲区。1项。*/
    struct mbedtls_asn1_sequence *next;    /**<序列中的下一个条目。*/
}
mbedtls_asn1_sequence;

/**
 * “命名”ASN序列或列表的容器。1个数据项
 */
typedef struct mbedtls_asn1_named_data
{
    mbedtls_asn1_buf oid;                   /**<对象标识符。*/
    mbedtls_asn1_buf val;                   /**<命名值。*/
    struct mbedtls_asn1_named_data *next;  /**<序列中的下一个条目。*/
    unsigned char next_merged;      /**<将下一项合并到当前项？*/
}
mbedtls_asn1_named_data;

/**
 * \brief获取ASN的长度。1个元素。将指针更新到长度的正后方。
 *
 * \param p输入时，\c*p指向长度的第一个字节，即紧跟在标记之后。成功完成后，\c p指向长度后的第一个字节，即内容的第一个。出现错误时，\c p的值未定义。\param end数据结束。\param len成功完成后，\c len包含从ASN读取的长度。1输入。
 *
 * \如果成功，则返回0。\如果ASN。1个元素将结束于\p end之外。\如果长度不可分析，则返回#MBEDTLS_ERROR_ASN1_INVALID_LENGTH。
 */
int mbedtls_asn1_get_len( unsigned char **p,
                          const unsigned char *end,
                          size_t *len );

/**
 * \brief获取元素的标签和长度。检查请求的标记。将指针更新到标记和长度后面。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向长度后的第一个字节，即内容的第一个。出现错误时，\c p的值未定义。\param end数据结束。\param len成功完成后，\c len包含从ASN读取的长度。1输入。\param tag预期的标记。
 *
 * \如果成功，则返回0。\如果数据不是以请求的标记开头，则返回#MBEDTLS_ERROR_ASN1_UNEXPECTED_TAG。\如果ASN。1个元素将结束于\p end之外。\如果长度不可分析，则返回#MBEDTLS_ERROR_ASN1_INVALID_LENGTH。
 */
int mbedtls_asn1_get_tag( unsigned char **p,
                          const unsigned char *end,
                          size_t *len, int tag );

/**
 * \brief检索布尔ASN。1标记及其值。将指针更新到紧接在完整标记后面的位置。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向ASN之外的第一个字节。1个元素。出现错误时，\c p的值未定义。\param end数据结束。\param val成功时，解析值（\c 0或\c 1）。
 *
 * \如果成功，则返回0。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1布尔值。
 */
int mbedtls_asn1_get_bool( unsigned char **p,
                           const unsigned char *end,
                           int *val );

/**
 * \brief检索整数ASN。1标记及其值。将指针更新到紧接在完整标记后面的位置。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向ASN之外的第一个字节。1个元素。出现错误时，\c p的值未定义。\param end数据结束。\param val成功时，解析值。
 *
 * \如果成功，则返回0。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1整数。\返回#MBEDTLS_ERROR_ASN1_INVALID_LENGTH，如果解析的值不符合\c int。
 */
int mbedtls_asn1_get_int( unsigned char **p,
                          const unsigned char *end,
                          int *val );

/**
 * \brief检索枚举ASN。1标记及其值。将指针更新到紧接在完整标记后面的位置。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向ASN之外的第一个字节。1个元素。出现错误时，\c p的值未定义。\param end数据结束。\param val成功时，解析值。
 *
 * \如果成功，则返回0。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1列举。\返回#MBEDTLS_ERROR_ASN1_INVALID_LENGTH，如果解析的值不符合\c int。
 */
int mbedtls_asn1_get_enum( unsigned char **p,
                           const unsigned char *end,
                           int *val );

/**
 * \brief检索位字符串ASN。1标记及其值。将指针更新到紧接在完整标记后面的位置。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p等于\p end。出现错误时，\c p的值未定义。\param end数据结束。\param bs成功时，：：mbedtls_asn1_bitstring有关解析值的信息。
 *
 * \如果成功，则返回0。\如果输入包含有效位字符串之后的额外数据，则返回#MBEDTLS_ERROR_ASN1_LENGTH_MISMACH。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1位字符串。
 */
int mbedtls_asn1_get_bitstring( unsigned char **p, const unsigned char *end,
                                mbedtls_asn1_bitstring *bs );

/**
 * \brief检索位字符串ASN。1标记，没有未使用的位及其值。更新指向位/八位字节字符串开头的指针。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向位字符串内容的第一个字节。出现错误时，\c p的值未定义。\param end数据结束。\param len成功时，\c len是内容的长度（以字节为单位）。
 *
 * \如果成功，则返回0。\如果输入以具有非零未使用位数的有效位字符串开始，则返回#MBEDTLS_ERROR_ASN1_INVALID_DATA。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1位字符串。
 */
int mbedtls_asn1_get_bitstring_null( unsigned char **p,
                                     const unsigned char *end,
                                     size_t *len );

/**
 * \简要分析和拆分ASN。1“＜tag＞序列”。将指针更新到紧挨着完整序列标记后面的位置。
 *
 * 此函数为序列元素分配内存。您可以使用mbedtls_asn1_sequence_free（）释放分配的内存。
 *
 * \注意：出现错误时，此函数可能会返回\p cur中的部分列表。在调用此函数之前，必须设置“cur->next=NULL”！否则，无法将以前的非空指针与指向此函数分配的对象的指针区分开来。
 *
 * \注意：如果序列为空，则此函数不会修改\c cur。如果序列有效且非空，则此函数将设置`cur->buf。标记`to\p标记。这允许调用者区分空序列和单元素序列。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p等于\p end。出现错误时，\c p的值未定义。\param end数据结束。\param cur A:：mbedtls_asn1_sequence，此函数将填充该序列。当此函数返回时，\c cur是链接列表的开头。此列表中的每个节点都分配了mbedtls_calloc（），而不是\pcur本身，因此应该使用mbedtls_free（）释放。该列表描述了序列的内容。列表的开头（即\c cur本身）描述第一个元素，“cur->next”描述第二个元素，等等。对于每个元素，“buf”。tag==tag`，`buf。len是元素内容的长度，buf。“p”指向内容的第一个字节（即，正好超过元素的长度）。注意，即使出现错误，也可能分配列表元素。\param tag序列的每个元素都必须具有此标记。
 *
 * \如果成功，则返回0。\如果输入包含有效SEQUENCE OF \p标记后的额外数据，则返回#MBEDTLS_ERROR_ASN1_LENGTH_MISPACH。\如果输入以ASN开头，则返回#MBEDTLS_ERROR_ASN1_UNEXPECTED_TAG。1 SEQUENCE，其中元素具有不同于\p标记的标记。\如果内存分配失败，返回#MBEDTLS_ERROR_ASN1_ALLOC_FAILED。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1序列。
 */
int mbedtls_asn1_get_sequence_of( unsigned char **p,
                                  const unsigned char *end,
                                  mbedtls_asn1_sequence *cur,
                                  int tag );
/**
 * \brief释放ASN的堆分配链接列表演示。1序列，包括第一个元素。
 *
 * 有两种常用的方法来管理用于表示已解析ASN的内存。1序列：
 * -使用mbedtls_calloc（）分配头节点`mbedtls_asn1_sequence*head`。将此节点作为“cur”参数传递给mbedtls_asn1_get_sequence_of（）。处理完序列后，在“head”上调用mbedtls_asn1_sequence_free（）。
 * -以任何方式分配头节点`mbedtls_asn1_sequence*head`，例如在堆栈上。确保“head->next==NULL”。将“head”作为“cur”参数传递给mbedtls_asn1_get_sequence_of（）。处理完序列后，对“head->cur”调用mbedtls_asn1_sequence_free（），然后以适当的方式释放“head”本身。
 *
 * \param seq第一个序列组件的地址。这可能是空的，在这种情况下，该函数会立即返回。
 */
void mbedtls_asn1_sequence_free( mbedtls_asn1_sequence *seq );

/**
 * \简要介绍ASN。1 SEQUENCE容器，并为每个条目调用回调。
 *
 * 此函数检查输入是否是每个元素都有“必须”标记的SEQUENCE元素，并对具有“可能”标记的元素调用回调函数。
 *
 * 例如，要验证输入是“tag1”的SEQUENCE，并对每个元素调用“cb”，请使用“``mbedtls_asn1_traverse_SEQUENCE_of（&p，end，0xff，tag1，0，0，cb，ctx）```
 *
 * 要验证输入是否为“任意序列”并对每个元素调用“cb”，请使用“``mbedtls_asn1_traverse_SEQUENCE_of（&p，end，0，0，0,0，cb，ctx）```
 *
 * 要验证输入是否为CHOICE｛NULL，八位字节字符串｝的序列，并对作为八位字节串的每个元素调用“cb”，请使用“``mbedtls_asn1_traverse_SEQUENCE_of（&p，end，0xfe，0x04，0xff，0x04、cb，ctx）```
 *
 * 从左到右用“may”标记对元素调用回调。如果输入不是带有“必须”标记的元素的有效SEQUENCE，则对元素调用回调，直到输入无效的最左端。
 *
 * \警告此功能仍处于实验阶段，可能随时更改。
 *
 * \param p指向ASN开头的指针的地址。1 SEQUENCE标头。这将更新为指向ASN的结尾。1 SEQUENCE容器。\param end ASN的结束。1 SEQUENCE容器。\param tag_must_mask要应用于ASN的掩码。在与\p tag_must_value进行比较之前，在SEQUENCE中找到1个标记。\param tag_must_val每个ASN的所需值。使用\p tag_must_mask屏蔽后，在SEQUENCE中找到1个标记。不匹配的标记会导致错误。例如，\p tag_must_mask和\p tag_must_val的值都为\c 0表示允许每个标记，而\p tag-must_mask的值为\c 0xFF则表示\p tag_fust_val是唯一允许的标记。\param tag_may_mask要应用于ASN的掩码。在与\p tag_may_value进行比较之前，在SEQUENCE中找到1个标记。\param tag_may_val每个ASN的期望值。使用\p tag_may_mask屏蔽后，在SEQUENCE中找到1个标记。不匹配的标记将被忽略。例如，\p tag_may_mask和\p tag-may_val的值为\c 0表示将考虑任何标记，而\p tag.may_mask的值为/c 0xFF表示将忽略值与\p taggmay_val不同的所有标记。\param cb ASN中每个组件要触发的回调。1与\p tag_may_val匹配的SEQUENCE。使用以下参数调用回调函数：
 *                       -\p ctx。
 *                       -当前元素的标记。
 *                       -指向输入中当前元素内容开头的指针。
 *                       -当前元素内容的长度。如果回调返回非零值，函数将立即停止，并转发回调的返回值。\param ctx要传递给回调\p cb的上下文。
 *
 * \如果整个ASN成功，则返回\c 0。1 SEQUENCE被遍历，没有解析或回调错误。\返回#MBEDTLS_ERROR_ASN1_LENGTH_MISMATCH，如果输入在具有接受标记的元素的有效序列之后包含额外数据。\如果输入以ASN开头，则返回#MBEDTLS_ERROR_ASN1_UNEXPECTED_TAG。1 SEQUENCE，其中元素具有不被接受的标记。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1序列。\return从回调\p cb转发的非零错误代码，以防后者返回非零值。
 */
int mbedtls_asn1_traverse_sequence_of(
    unsigned char **p,
    const unsigned char *end,
    unsigned char tag_must_mask, unsigned char tag_must_val,
    unsigned char tag_may_mask, unsigned char tag_may_val,
    int (*cb)( void *ctx, int tag,
               unsigned char* start, size_t len ),
    void *ctx );

#if defined(MBEDTLS_BIGNUM_C)
/**
 * \brief检索整数ASN。1标记及其值。将指针更新到紧接在完整标记后面的位置。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向ASN之外的第一个字节。1个元素。出现错误时，\c p的值未定义。\param end数据结束。\param X成功时，解析值。
 *
 * \如果成功，则返回0。\返回ASN。如果输入不是以有效ASN开头，则返回1个错误代码。1整数。\return#MBEDTLS_error_ASN1_INVALID_LENGTH，如果解析的值不符合\c int。\如果解析的数值太大，则返回MPI错误代码。
 */
int mbedtls_asn1_get_mpi( unsigned char **p,
                          const unsigned char *end,
                          mbedtls_mpi *X );
#endif /* MBEDTLS_BIGNUM_C */

/**
 * \brief检索算法标识符ASN。1序列。将指针更新到完整AlgorithmIdentifier后面。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向AlgorithmIdentifier元素之外的第一个字节。出现错误时，\c p的值未定义。\param end数据结束。\param alg接收OID的缓冲区。\param params接收参数的缓冲区。如果没有参数，则归零。
 *
 * \如果成功，返回0或特定ASN。1或MPI错误代码。
 */
int mbedtls_asn1_get_alg( unsigned char **p,
                  const unsigned char *end,
                  mbedtls_asn1_buf *alg, mbedtls_asn1_buf *params );

/**
 * \brief检索算法标识符ASN。1序列，带NULL或无参数。将指针更新到完整AlgorithmIdentifier后面。
 *
 * \param p输入时，\c*p指向ASN的开始。1个元素。成功完成后，\c p指向AlgorithmIdentifier元素之外的第一个字节。出现错误时，\c p的值未定义。\param end数据结束。\param alg接收OID的缓冲区。
 *
 * \如果成功，返回0或特定ASN。1或MPI错误代码。
 */
int mbedtls_asn1_get_alg_null( unsigned char **p,
                       const unsigned char *end,
                       mbedtls_asn1_buf *alg );

/**
 * \brief根据OID在序列或列表中查找特定的named_data条目。
 *
 * \param list要查找的列表\param oid要查找的oid \param len oid的大小
 *
 * \如果未找到，则返回NULL，或指向现有项的指针。
 */
mbedtls_asn1_named_data *mbedtls_asn1_find_named_data( mbedtls_asn1_named_data *list,
                                       const char *oid, size_t len );

/**
 * \brief释放mbedtls_asn1_named_data条目
 *
 * \param entry要释放的命名数据项。此函数对`entry->oid调用mbedtls_free（）。p`和`entry->val.p`。
 */
void mbedtls_asn1_free_named_data( mbedtls_asn1_named_data *entry );

/**
 * \brief释放mbedtls_asn1_named_data列表中的所有条目。
 *
 * \param head指向要释放的命名数据项列表的头的指针。此函数对每个列表元素调用mbedtls_asn1_free_named_data（）和mbedtls_free（），并将\chead设置为\c NULL。
 */
void mbedtls_asn1_free_named_data_list( mbedtls_asn1_named_data **head );

#ifdef __cplusplus
}
#endif

#endif /* asn1小时*/

