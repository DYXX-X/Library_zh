/**
 *  恒定时间函数
 *
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef MBEDTLS_CONSTANT_TIME_INTERNAL_H
#define MBEDTLS_CONSTANT_TIME_INTERNAL_H

#include "common.h"

#if defined(MBEDTLS_BIGNUM_C)
#include "mbedtls/bignum.h"
#endif

#if defined(MBEDTLS_SSL_TLS_C)
#include "mbedtls/ssl_internal.h"
#endif

#include <stddef.h>


/** 将值转换为遮罩：
 * -如果\p值==0，则返回所有位0掩码，即0
 * -否则，返回所有位1掩码，aka（无符号）-1
 *
 * 此函数可用于通过使用掩码将分支替换为位操作来编写恒定时间代码。
 *
 * \param value要分析的值。
 *
 * \如果\p值为零，则返回零，否则返回所有位1。
 */
unsigned mbedtls_ct_uint_mask( unsigned value );

#if defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)

/** 将值转换为遮罩：
 * -如果\p值==0，则返回所有位0掩码，即0
 * -否则，返回所有位1掩码，即（size_t）-1
 *
 * 此函数可用于通过使用掩码将分支替换为位操作来编写恒定时间代码。
 *
 * \param value要分析的值。
 *
 * \如果\p值为零，则返回零，否则返回所有位1。
 */
size_t mbedtls_ct_size_mask( size_t value );

#endif /* MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC */

#if defined(MBEDTLS_BIGNUM_C)

/** 将值转换为遮罩：
 * -如果\p值==0，则返回所有位0掩码，即0
 * -否则，返回所有位1掩码，即（mbedtls_mpi_uint）-1
 *
 * 此函数可用于通过使用掩码将分支替换为位操作来编写恒定时间代码。
 *
 * \param value要分析的值。
 *
 * \如果\p值为零，则返回零，否则返回所有位1。
 */
mbedtls_mpi_uint mbedtls_ct_mpi_uint_mask( mbedtls_mpi_uint value );

#endif /* MBEDTLS_BIGNUM_C */

#if defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)

/** 用于“大于或等于”比较的恒定流量掩码生成：
 * -如果\p x>=\p y，则返回所有位1，即（size_t）-1
 * -否则，返回所有位0，即0
 *
 * 此函数可用于通过使用掩码将分支替换为位操作来编写恒定时间代码。
 *
 * \param x要分析的第一个值。\param y要分析的第二个值。
 *
 * \如果\p x大于或等于\p y，则返回所有位1，否则为零。
 */
size_t mbedtls_ct_size_mask_ge( size_t x,
                                size_t y );

#endif /* MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC */

/** 常量流布尔“相等”比较：返回x==y
 *
 * 这相当于\p x==\p y，但很可能使用按位操作而不是分支编译为代码。
 *
 * \param x要分析的第一个值。\param y要分析的第二个值。
 *
 * \如果\p x等于\p y，则返回1，否则返回0。
 */
unsigned mbedtls_ct_size_bool_eq( size_t x,
                                  size_t y );

#if defined(MBEDTLS_BIGNUM_C)

/** 确定一个整数是否小于另一个整数，不带分支。
 *
 * 这相当于\p x<\p y，但很可能使用按位操作而不是分支编译为代码。
 *
 * \param x要分析的第一个值。\param y要分析的第二个值。
 *
 * \如果\p x小于\p y，则返回1，否则返回0。
 */
unsigned mbedtls_ct_mpi_uint_lt( const mbedtls_mpi_uint x,
                                 const mbedtls_mpi_uint y );

#endif /* MBEDTLS_BIGNUM_C */

/** 在两个不带分支的整数值之间进行选择。
 *
 * 这相当于“条件”？if1:if0”，但很可能使用按位操作而不是分支编译为代码。
 *
 * \param condition要测试的条件。\param if1如果\p条件为非零时使用的值。\param if0条件为零时要使用的值。
 *
 * \如果\p条件为非零，则返回\c if1，否则返回\c if 0。
 */
unsigned mbedtls_ct_uint_if( unsigned condition,
                             unsigned if1,
                             unsigned if0 );

#if defined(MBEDTLS_BIGNUM_C)

/** 有条件地分配一个没有分支的值。
 *
 * 这相当于“if（condition）dest=src”，但很可能使用按位操作而不是分支编译为代码。
 *
 * \param n\p dest和\p src必须是大小为n的分支数组。\param dest要有条件分配给的MPI。这必须指向已初始化的MPI。\param src要从中分配的MPI。这必须指向已初始化的MPI。\param condition要测试的条件必须为0或1。
 */
void mbedtls_ct_mpi_uint_cond_assign( size_t n,
                                      mbedtls_mpi_uint *dest,
                                      const mbedtls_mpi_uint *src,
                                      unsigned char condition );

#endif /* MBEDTLS_BIGNUM_C */

#if defined(MBEDTLS_BASE64_C)

/** 给定范围为0..63的值，返回相应的Base64位。
 *
 * 该实现假定字母是连续的（例如ASCII而不是EBCDIC）。
 *
 * \param value范围为0..63的值。
 *
 * \返回从\p值转换的base64位数字。
 */
unsigned char mbedtls_ct_base64_enc_char( unsigned char value );

/** 给定Base64位，返回其值。
 *
 * 如果c不是Base64位（“a”..“Z”、“a”..“Z”、“0”..“9”、“+”或“/”），则返回-1。
 *
 * 该实现假定字母是连续的（例如ASCII而不是EBCDIC）。
 *
 * \param c以64位为基数的数字。
 *
 * \return以64位为基数的\p c的值。
 */
signed char mbedtls_ct_base64_dec_value( unsigned char c );

#endif /* MBEDTLS_BASE64_C */

#if defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)

/** 无分支的条件内存。
 *
 * 这相当于“if（c1==c2）memcpy（dest，src，len）”，但很可能使用按位操作而不是分支编译为代码。
 *
 * \param dest要有条件复制到的指针。\param src要从中复制的指针。不应与目标重叠。\param len要复制的字节数。\param c1条件中要分析的第一个值。\param c2条件中要分析的第二个值。
 */
void mbedtls_ct_memcpy_if_eq( unsigned char *dest,
                              const unsigned char *src,
                              size_t len,
                              size_t c1, size_t c2 );

/** 以恒定流从秘密位置复制数据。
 *
 * 此函数使用代码流和内存访问模式将\p len字节从\p src_base+\p offset_secret复制到\p dst，该模式不依赖于\p offset _secret，而仅依赖于\poffset_min、\p offset_max和\p len。功能上等同于“memcpy（dst，src+offset_secret，len）”。
 *
 * \param dest目标缓冲区。这必须指向至少为\plen字节的可写缓冲区。\param src源缓冲区的基。这必须指向至少为\p offset_max+\p len字节的可读缓冲区。不应与目标重叠。\param offset要从中复制的源缓冲区中的偏移量。该值必须不小于\p offset_min且不大于\p offset _max。\param offset_min \p offset的最小值。\param offset_max \p offset的最大值。\param len要复制的字节数。
 */
void mbedtls_ct_memcpy_offset( unsigned char *dest,
                               const unsigned char *src,
                               size_t offset,
                               size_t offset_min,
                               size_t offset_max,
                               size_t len );

/** 计算具有恒定流量的可变长度数据的HMAC。
 *
 * 此函数计算add_data和数据级联的HMAC，并使用不依赖于data_len_secret但仅依赖于min_data_len和max_data_ln的代码流和内存访问模式。特别是，此函数始终从数据中精确读取\p max_data_len字节。
 *
 * \param ctx HMAC上下文。它必须使用mbedtls_md_hmac_starts（）配置密钥，并使用以下哈希之一：SHA-384、SHA-256、SHA-1或md-5。计算完成后，将使用mbedtls _md_hmc_reset（）重置密钥，以准备下一次计算。\param add_data正在计算其HMAC的消息的第一部分。这必须指向\p add_data_len字节的可读缓冲区。\param add_data_len add_data的长度（以字节为单位）。\param data包含消息第二部分的缓冲区。这必须指向\p max_data_len字节的可读缓冲区。\param data_len_secret数据中要处理的数据的长度。这必须不小于\p min_data_len且不大于\p max_data_ln。\param min_data_len从\p数据读取的消息第二部分的最小长度。\param max_data_len从\p数据读取的消息第二部分的最大长度。\param output将在此处写入HMAC。这必须指向大小足以容纳HMAC值的可写缓冲区。
 *
 * \成功时返回0。\retval#MBEDTLS_ERROR_PLATFORM_HW_ACCEL_FAILED硬件加速器失败。
 */
int mbedtls_ct_hmac( mbedtls_md_context_t *ctx,
                     const unsigned char *add_data,
                     size_t add_data_len,
                     const unsigned char *data,
                     size_t data_len_secret,
                     size_t min_data_len,
                     size_t max_data_len,
                     unsigned char *output );

#endif /* MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC */

#if defined(MBEDTLS_PKCS1_V15) && defined(MBEDTLS_RSA_C) && !defined(MBEDTLS_RSA_ALT)

/** 此函数执行PKCS#1 v1.5解密操作（EME-PKCS1-v1_5解码）的取消添加部分。
 *
 * \注意：此函数的返回值是一个敏感值（这是不寻常的）#MBEDTLS_ERROR_RSA_OUTPUT_TOO_LARGE不应发生在编写良好的应用程序中，但0与#MBEDTLS_ERROR_RSA_INVALID_PADDING之间的冲突通常是攻击者可以引发并泄漏的情况，而泄漏的信息正是攻击者想要的信息。
 *
 * \param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param input输入缓冲区是PKCS#1v1.5加密填充中的有效载荷，术语称为“编码消息EM”。\param ilen输入缓冲区中有效负载的长度。\param output有效负载的缓冲区，PKCS#1术语称为“消息M”。这必须是长度为\p output_max_len字节的可写缓冲区。\param olen存储有效负载长度的地址。此值不能为空。\param output_max_len输出缓冲区\p输出的字节长度。
 *
 * \成功时返回\c 0。\return#MBEDTLS_ERROR_RSA_OUTPUT_TOO_LARGE输出缓冲区对于未添加的负载太小。\return#MBEDTLS_ERROR_RSA_INVALID_PADDING输入不包含格式正确的填充。
 */
int mbedtls_ct_rsaes_pkcs1_v15_unpadding( int mode,
                                          unsigned char *input,
                                          size_t ilen,
                                          unsigned char *output,
                                          size_t output_max_len,
                                          size_t *olen );

#endif /* MBEDTLS_PKCS1_V15 && MBEDTLS_RSA_C && ! MBEDTLS_RSA_ALT */

#endif /* MBEDTLS_CONSTANT_TIME_INTERNAL_H */

