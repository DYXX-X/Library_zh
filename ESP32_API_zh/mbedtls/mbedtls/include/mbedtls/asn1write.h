/**
 * \文件asn1write.h
 *
 * \简短ASN。1个缓冲区写入功能
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
#ifndef MBEDTLS_ASN1_WRITE_H
#define MBEDTLS_ASN1_WRITE_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/asn1.h"

#define MBEDTLS_ASN1_CHK_ADD(g, f)                      \
    do                                                  \
    {                                                   \
        if( ( ret = (f) ) < 0 )                         \
            return( ret );                              \
        else                                            \
            (g) += ret;                                 \
    } while( 0 )

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief在ASN中写一个长度字段。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param len要写入的长度值。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_len( unsigned char **p, unsigned char *start,
                            size_t len );
/**
 * \brief编写ASN。ASN中的1个标签。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param tag要写入的标记。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_tag( unsigned char **p, unsigned char *start,
                            unsigned char tag );

/**
 * \brief写入原始缓冲区数据。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param buf要写入的数据缓冲区。\param size数据缓冲区的长度。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_raw_buffer( unsigned char **p, unsigned char *start,
                                   const unsigned char *buf, size_t size );

#if defined(MBEDTLS_BIGNUM_C)
/**
 * \brief在ASN中写入任意精度数字（#MBEDTLS_ASN1_INTEGER）。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param X要写入的MPI。它必须是非负的。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_mpi( unsigned char **p, unsigned char *start,
                            const mbedtls_mpi *X );
#endif /* MBEDTLS_BIGNUM_C */

/**
 * \brief在ASN中使用零数据写入NULL标记（#MBEDTLS_ASN1_NULL）。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_null( unsigned char **p, unsigned char *start );

/**
 * \brief在ASN中写入OID标记（#MBEDTLS_ASN1_OID）和数据。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param oid要写入的oid。\param oid_len oid的长度。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_oid( unsigned char **p, unsigned char *start,
                            const char *oid, size_t oid_len );

/**
 * \brief在ASN中编写AlgorithmIdentifier序列。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param oid要写入的算法的oid。\param oid_len算法oid的长度。\param par_len参数的长度，必须已写入。如果为0，则添加NULL参数
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_algorithm_identifier( unsigned char **p,
                                             unsigned char *start,
                                             const char *oid, size_t oid_len,
                                             size_t par_len );

/**
 * \brief在ASN中写入布尔标记（#MBEDTLS_ASN1_boolean）和值。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param boolean要写入的布尔值，\c 0或\c 1。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_bool( unsigned char **p, unsigned char *start,
                             int boolean );

/**
 * \brief在ASN中写入int标记（#MBEDTLS_ASN1_INTEGER）和值。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param val要写入的整数值。它必须是非负的。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_int( unsigned char **p, unsigned char *start, int val );

/**
 * \brief在ASN中写一个枚举标记（#MBEDTLS_ASN1_ENUMERATED）和值。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param val要写入的整数值。
 *
 * \return成功时写入\pp的字节数。\失败时返回否定的\c MBEDTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_asn1_write_enum( unsigned char **p, unsigned char *start, int val );

/**
 * \brief在ASN中编写字符串。1格式，使用特定的字符串编码标记。

 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param tag要写入的字符串编码标记，例如#MBEDTLS_ASN1_UTF8_string。\param text要写入的字符串。\param text_len \p文本的长度（以字节为单位）（可能严格大于字符数）。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_tagged_string( unsigned char **p, unsigned char *start,
                                      int tag, const char *text,
                                      size_t text_len );

/**
 * \brief在ASN中编写字符串。1格式，使用PrintableString字符串编码标记（#MBEDTLS_ASSN1_PRINTABLE_string）。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param text要写入的字符串。\param text_len \p文本的长度（以字节为单位）（可能严格大于字符数）。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_printable_string( unsigned char **p,
                                         unsigned char *start,
                                         const char *text, size_t text_len );

/**
 * \brief在ASN中编写UTF8字符串。1格式，使用UTF8String字符串编码标记（#MBEDTLS_ASN1_UTF8_string）。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param text要写入的字符串。\param text_len \p文本的长度（以字节为单位）（可能严格大于字符数）。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_utf8_string( unsigned char **p, unsigned char *start,
                                    const char *text, size_t text_len );

/**
 * \brief在ASN中编写字符串。1格式，使用IA5String字符串编码标记（#MBEDTLS_ASN1_IA5_string）。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param text要写入的字符串。\param text_len \p文本的长度（以字节为单位）（可能严格大于字符数）。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_ia5_string( unsigned char **p, unsigned char *start,
                                   const char *text, size_t text_len );

/**
 * \brief在ASN中写入位字符串标记（#MBEDTLS_ASSN1_BIT_STRING）和值。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param buf要写入的位字符串。\param bits位串中的总位数。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_bitstring( unsigned char **p, unsigned char *start,
                                  const unsigned char *buf, size_t bits );

/**
 * \brief此函数在ASN中写入命名的位字符串标记（#MBEDTLS_ASN1_BIT_STRING）和值。1格式。
 *
 *                  如RFC 5280附录B所述，在DER中编码命名位串时，省略尾随零。
 *
 * \注意：此函数在数据缓冲区内向后工作。
 *
 * \param p当前位置指针的引用。\param start用于边界检查的缓冲区的开始。\param buf要写入的位字符串。\param bits位串中的总位数。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_named_bitstring( unsigned char **p,
                                        unsigned char *start,
                                        const unsigned char *buf,
                                        size_t bits );

/**
 * \brief在ASN中写入八位字节字符串标记（#MBEDTLS_ASN1_OCET_string）和值。1格式。
 *
 * \注意：此函数在数据缓冲区中向后工作。
 *
 * \param p当前位置指针的引用。\param start缓冲区的开始，用于边界检查。\param buf保存要写入的数据的缓冲区。\param size数据缓冲区的长度。
 *
 * \return成功时写入\pp的字节数。\失败时返回负错误代码。
 */
int mbedtls_asn1_write_octet_string( unsigned char **p, unsigned char *start,
                                     const unsigned char *buf, size_t size );

/**
 * \brief根据OID创建或查找特定的named_data条目，以便按顺序或列表写入。如果还没有，则会在列表的开头添加一个新条目。警告：val数据的破坏性行为！
 *
 * \param list指向要查找的列表头部位置的指针（在出现新条目时将更新）。\param oid要查找的oid。\param oid_len oid的大小。\param val要存储的关联数据。如果为空，则不会将数据复制到新的或现有的缓冲区。\param val_len所需数据缓冲区的最小长度。如果为0，则不要为关联数据分配缓冲区。如果OID已经存在，请放大、缩小或释放现有缓冲区以适合\pval_len。
 *
 * \return成功时指向新/现有条目的指针。\如果存在内存分配错误，则返回\c NULL。
 */
mbedtls_asn1_named_data *mbedtls_asn1_store_named_data( mbedtls_asn1_named_data **list,
                                        const char *oid, size_t oid_len,
                                        const unsigned char *val,
                                        size_t val_len );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_ASN1_WRITE_H */

