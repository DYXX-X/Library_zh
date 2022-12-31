/**
 * \文件bignum.h
 *
 * \简短的多精度整数库
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
#ifndef MBEDTLS_BIGNUM_H
#define MBEDTLS_BIGNUM_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#if defined(MBEDTLS_FS_IO)
#include <stdio.h>
#endif

/**读取或写入文件时出错。*/
#define MBEDTLS_ERR_MPI_FILE_IO_ERROR                     -0x0002
/**函数的输入参数错误。*/
#define MBEDTLS_ERR_MPI_BAD_INPUT_DATA                    -0x0004
/**数字字符串中有一个无效字符。*/
#define MBEDTLS_ERR_MPI_INVALID_CHARACTER                 -0x0006
/**缓冲区太小，无法写入。*/
#define MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL                  -0x0008
/**输入参数为负或导致非法输出。*/
#define MBEDTLS_ERR_MPI_NEGATIVE_VALUE                    -0x000A
/**除法的输入参数为零，这是不允许的。*/
#define MBEDTLS_ERR_MPI_DIVISION_BY_ZERO                  -0x000C
/**输入参数不可接受。*/
#define MBEDTLS_ERR_MPI_NOT_ACCEPTABLE                    -0x000E
/**内存分配失败。*/
#define MBEDTLS_ERR_MPI_ALLOC_FAILED                      -0x0010

#define MBEDTLS_MPI_CHK(f)       \
    do                           \
    {                            \
        if( ( ret = (f) ) != 0 ) \
            goto cleanup;        \
    } while( 0 )

/*
 * 允许最大大小的MPIs增长到肢体数。
 */
#define MBEDTLS_MPI_MAX_LIMBS                             10000

#if !defined(MBEDTLS_MPI_WINDOW_SIZE)
/*
 * 用于模幂运算的最大窗口大小。默认值：6最小值：1。最大值：6。
 *
 * 结果是用于滑动窗口计算的（2**MBEDTLS_MPI_WINDOW_SIZE）MPIs数组。（默认情况下为64）
 *
 * 尺寸减小，速度降低。
 */
#define MBEDTLS_MPI_WINDOW_SIZE                           6        /**<使用的最大窗口大小。*/
#endif /* !MBEDTLS_MPI_WINDOW_SIZE */

#if !defined(MBEDTLS_MPI_MAX_SIZE)
/*
 * 用户MPIs允许的最大MPIs大小（以位和字节为单位）。（默认值：512字节=>4096位，测试的最大值：2048字节=>16384位）
 *
 * 注意：计算可能会暂时导致更大的MPIs。因此，所需的肢体数量（MBEDTLS_MPI_MAX_limbs）更高。
 */
#define MBEDTLS_MPI_MAX_SIZE                              1024     /**<可用MPIs的最大字节数。*/
#endif /* !MBEDTLS_MPI_MAX_SIZE */

#define MBEDTLS_MPI_MAX_BITS                              ( 8 * MBEDTLS_MPI_MAX_SIZE )    /**<可用MPIs的最大位数。*/

/*
 * 当从具有mbedtls_mpi_read_file（）的文件中读取并写入具有mbedtls _mpi_write_file（（）的的文件时，缓冲区应具有用于（短）标签、mpi（以提供的基数）、换行符和“\0”的空间。
 *
 * 默认情况下，我们假设至少有一个10个字符标签，最小基数为10（十进制），最大位数为4096位（1234个十进制字符）。编译时自动调整至少10个字符标签的大小，MBEDTLS_MPI_MAX_BITS大小的最小基数为10（十进制）。
 *
 * 过去，它的静态大小为1250，最多4096位数字（1234个十进制字符）。
 *
 * 使用公式计算：MBEDTLS_MPI_RW_BUFFER_SIZE=ceil（MBEDTLS_MPI_MAX_BITS/ln（10）ln（2））+LabelSize+6
 */
#define MBEDTLS_MPI_MAX_BITS_SCALE100          ( 100 * MBEDTLS_MPI_MAX_BITS )
#define MBEDTLS_LN_2_DIV_LN_10_SCALE100                 332
#define MBEDTLS_MPI_RW_BUFFER_SIZE             ( ((MBEDTLS_MPI_MAX_BITS_SCALE100 + MBEDTLS_LN_2_DIV_LN_10_SCALE100 - 1) / MBEDTLS_LN_2_DIV_LN_10_SCALE100) + 10 + 6 )

#if !defined(MBEDTLS_BIGNUM_ALT)

/*
 * 定义基本整数类型（按体系结构）。
 *
 * 通过分别定义MBEDTLS_HAVE_INT32或MBEDTLS_HAVE_INT64并对MBEDTLH_HAVE_ASM进行不定义，可以强制32位或64位整数类型。
 *
 * 通过定义MBEDTLS_NO_UDBL_DIVISION，可以禁用双宽度整数（例如，64位架构中的128位）。
 */
#if !defined(MBEDTLS_HAVE_INT32)
    #if defined(_MSC_VER) && defined(_M_AMD64)
        /* 使用MSC时始终选择64位*/
        #if !defined(MBEDTLS_HAVE_INT64)
            #define MBEDTLS_HAVE_INT64
        #endif /* !MBEDTLS_HAVE_INT64 */
        typedef  int64_t mbedtls_mpi_sint;
        typedef uint64_t mbedtls_mpi_uint;
    #elif defined(__GNUC__) && (                         \
        defined(__amd64__) || defined(__x86_64__)     || \
        defined(__ppc64__) || defined(__powerpc64__)  || \
        defined(__ia64__)  || defined(__alpha__)      || \
        ( defined(__sparc__) && defined(__arch64__) ) || \
        defined(__s390x__) || defined(__mips64)       || \
        defined(__aarch64__) )
        #if !defined(MBEDTLS_HAVE_INT64)
            #define MBEDTLS_HAVE_INT64
        #endif /* MBEDTLS_HAVE_INT64 */
        typedef  int64_t mbedtls_mpi_sint;
        typedef uint64_t mbedtls_mpi_uint;
        #if !defined(MBEDTLS_NO_UDBL_DIVISION)
            /* mbedtls_t_udbl定义为128位无符号整数*/
            typedef unsigned int mbedtls_t_udbl __attribute__((mode(TI)));
            #define MBEDTLS_HAVE_UDBL
        #endif /* !MBEDTLS_NO_UDBL_DIVISION */
    #elif defined(__ARMCC_VERSION) && defined(__aarch64__)
        /*
         * __ARMCC_VERSION是为ARMCC和armclang定义的，__aarch64__仅在编译64位代码时由armclang来定义
         */
        #if !defined(MBEDTLS_HAVE_INT64)
            #define MBEDTLS_HAVE_INT64
        #endif /* !MBEDTLS_HAVE_INT64 */
        typedef  int64_t mbedtls_mpi_sint;
        typedef uint64_t mbedtls_mpi_uint;
        #if !defined(MBEDTLS_NO_UDBL_DIVISION)
            /* mbedtls_t_udbl定义为128位无符号整数*/
            typedef __uint128_t mbedtls_t_udbl;
            #define MBEDTLS_HAVE_UDBL
        #endif /* !MBEDTLS_NO_UDBL_DIVISION */
    #elif defined(MBEDTLS_HAVE_INT64)
        /* 使用未知编译器强制64位整数*/
        typedef  int64_t mbedtls_mpi_sint;
        typedef uint64_t mbedtls_mpi_uint;
    #endif
#endif /* !MBEDTLS_HAVE_INT32 */

#if !defined(MBEDTLS_HAVE_INT64)
    /* 默认为32位编译*/
    #if !defined(MBEDTLS_HAVE_INT32)
        #define MBEDTLS_HAVE_INT32
    #endif /* !MBEDTLS_HAVE_INT32 */
    typedef  int32_t mbedtls_mpi_sint;
    typedef uint32_t mbedtls_mpi_uint;
    #if !defined(MBEDTLS_NO_UDBL_DIVISION)
        typedef uint64_t mbedtls_t_udbl;
        #define MBEDTLS_HAVE_UDBL
    #endif /* !MBEDTLS_NO_UDBL_DIVISION */
#endif /* !MBEDTLS_HAVE_INT64 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简要MPI结构
 */
typedef struct mbedtls_mpi
{
    int s;              /*!<  符号：如果mpi为负，则为-1，否则为1*/
    size_t n;           /*!<  四肢总数*/
    mbedtls_mpi_uint *p;          /*!<  指向肢体的指针*/
}
mbedtls_mpi;

/**
 * \brief初始化MPI上下文。
 *
 *                  这使得MPI可以被设置或释放，但没有为MPI定义值。
 *
 * \param X要初始化的MPI上下文。此值不能为空。
 */
void mbedtls_mpi_init( mbedtls_mpi *X );

/**
 * \brief此函数释放MPI上下文的组件。
 *
 * \param X要清除的MPI上下文。这可能是空的，在这种情况下，此函数是no-op。如果不是空，则必须指向已初始化的MPI。
 */
void mbedtls_mpi_free( mbedtls_mpi *X );

/**
 * \brief将MPI放大到指定的肢体数量。
 *
 * \注意：如果MPI已经足够大，则此函数不起作用。
 *
 * \param X要增长的MPI。必须对其进行初始化。\param nblimbs肢体的目标数量。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_grow( mbedtls_mpi *X, size_t nblimbs );

/**
 * \brief此函数向下调整MPI的大小，至少保持指定的肢体数。
 *
 *                 如果\c X小于\c nblimbs，则改为调整其大小。
 *
 * \param X要收缩的MPI。这必须指向已初始化的MPI。\param nblimits要保留的最小肢体数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，则返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED（这仅在调整大小时发生）。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_shrink( mbedtls_mpi *X, size_t nblimbs );

/**
 * \brief复制MPI。
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param Y源MPI。这必须指向已初始化的MPI。
 *
 * \注意：如果需要保存源MPI中的值，将放大目标MPI中的分支缓冲区。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_copy( mbedtls_mpi *X, const mbedtls_mpi *Y );

/**
 * \brief交换两个MPIs的内容。
 *
 * \param X第一次MPI。必须对其进行初始化。\param Y第二次MPI。必须对其进行初始化。
 */
void mbedtls_mpi_swap( mbedtls_mpi *X, mbedtls_mpi *Y );

/**
 * \brief执行MPI的安全条件副本，该副本不会显示条件是否为真。
 *
 * \param X要有条件分配给的MPI。这必须指向已初始化的MPI。\param Y要从中分配的MPI。这必须指向已初始化的MPI。\param assign决定是否执行赋值的条件。可能的值：\c 1:执行赋值“X=Y”。\c 0：保留\p X的原始值。
 *
 * \注意：此函数等效于“if（assign）mbedtls_mpi_copy（X，Y）；”除了避免泄漏关于是否完成了分配的任何信息（上述代码可能通过分支预测和/或存储器访问模式分析泄漏信息）。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_safe_cond_assign( mbedtls_mpi *X, const mbedtls_mpi *Y, unsigned char assign );

/**
 * \brief执行安全的条件交换，它不会显示条件是否为真。
 *
 * \param X第一次MPI。必须对其进行初始化。\param Y第二次MPI。必须对其进行初始化。\param assign决定是否执行交换的条件。可能的值：\c 1：交换\p X和\p Y的值。\c 0：保持\p X与\p Y原始值。
 *
 * \注意：此函数等效于if（assign）mbedtls_mpi_swap（X，Y）；除了避免泄漏关于是否完成了分配的任何信息（上述代码可能通过分支预测和/或存储器访问模式分析泄漏信息）。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 *
 */
int mbedtls_mpi_safe_cond_swap( mbedtls_mpi *X, mbedtls_mpi *Y, unsigned char assign );

/**
 * \brief在MPI中存储整数值。
 *
 * \param X要设置的MPI。必须对其进行初始化。\param z要使用的值。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_lset( mbedtls_mpi *X, mbedtls_mpi_sint z );

/**
 * \brief从MPI中获取特定位。
 *
 * \param X要查询的MPI。必须对其进行初始化。\param pos要查询的位的从零开始的索引。
 *
 * \成功时返回\c 0或\c 1，这取决于\c X的位位置是未设置还是已设置。\失败时返回负错误代码。
 */
int mbedtls_mpi_get_bit( const mbedtls_mpi *X, size_t pos );

/**
 * \brief修改MPI中的特定位。
 *
 * \注意：如果需要在尚未存在的分支中将位设置为\c 1，此函数将增长目标MPI。如果将位设置为\c 0，则不会增长。
 *
 * \param X要修改的MPI。必须对其进行初始化。\param pos要修改的位的从零开始的索引。\param val位\c pos:\c 0或\c 1的所需值。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_set_bit( mbedtls_mpi *X, size_t pos, unsigned char val );

/**
 * \brief返回值\c 0在值\c 1的最低有效位之前的位数。
 *
 * \注意这与值\c 1的最低有效位的从零开始的索引相同。
 *
 * \param X要查询的MPI。
 *
 * \return \p X中值\c 1的最低有效位之前值\c 0的位数。
 */
size_t mbedtls_mpi_lsb( const mbedtls_mpi *X );

/**
 * \brief返回值\c 1的最高有效位的位数。
 *
 * *\注意这与值\ c 1的最高有效位的基于一的索引相同。
 *
 * \param X要查询的MPI。这必须指向已初始化的MPI。
 *
 * \return值为\c 1的最高有效位（包括最高有效位）的位数。
 */
size_t mbedtls_mpi_bitlen( const mbedtls_mpi *X );

/**
 * \brief返回MPI值的总大小（字节）。
 *
 * \param X要使用的MPI。这必须指向已初始化的MPI。
 *
 * \注意：此函数返回的值可能小于用于在内部存储\p X的字节数。当且仅当存在值为零的尾随字节时，才会发生这种情况。
 *
 * \return能够存储\p X绝对值的最小字节数。
 */
size_t mbedtls_mpi_size( const mbedtls_mpi *X );

/**
 * \brief从ASCII字符串导入MPI。
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param radix输入字符串的数字基数。\param s以Null结尾的字符串缓冲区。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_mpi_read_string( mbedtls_mpi *X, int radix, const char *s );

/**
 * \brief将MPI导出为ASCII字符串。
 *
 * \param X源MPI。这必须指向已初始化的MPI。\param radix输出字符串的数字基数。\param buf要将字符串写入的缓冲区。这必须是长度为\p buflen Bytes的可写缓冲区。\param buflen \p buf的可用大小（字节）。\param olen存储所写字符串长度的地址，包括最后的空字节。此值不能为空。
 *
 * \注意：可以使用“buflen==0”调用此函数，以获得“olen”中所需的最小缓冲区大小。
 *
 * \如果成功，返回\c 0。\返回#MBEDTLS_ERROR_MPI_BUFFER_TOO_SMALL，如果目标缓冲区缓冲区太小，无法将X的值保持在所需的基数中。在这种情况下，“olen”仍然被更新为包含成功调用所需的缓冲区大小。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_write_string( const mbedtls_mpi *X, int radix,
                              char *buf, size_t buflen, size_t *olen );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief从打开的文件中的一行读取MPI。
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param radix源行中使用的字符串表示的数字基数。\param fin要使用的输入文件句柄。此值不能为空。
 *
 * \注意：成功时，此函数将文件流推进到当前行的末尾或EOF。
 *
 *                 函数在空行上返回\c 0。
 *
 *                 前导空格被忽略，基数\c 16的“0x”前缀也被忽略。
 *
 * \如果成功，返回\c 0。\如果文件读取缓冲区太小，则返回#MBEDTLS_ERROR_MPI_BUFFER_TOO_SMALL。\失败时返回另一个负错误代码。
 */
int mbedtls_mpi_read_file( mbedtls_mpi *X, int radix, FILE *fin );

/**
 * \brief将MPI导出到打开的文件中。
 *
 * \param p要在MPI数据之前发出的字符串前缀。例如，这可能是一个标签，当以基数\c 16打印时，可能是“0x”。如果不需要前缀，则可能是\c NULL。\param X源MPI。这必须指向已初始化的MPI。\param radix要在发出的字符串中使用的数字基数。\param fout输出文件句柄。这可能是\c NULL，在这种情况下，输出将写入\c stdout。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_mpi_write_file( const char *p, const mbedtls_mpi *X,
                            int radix, FILE *fout );
#endif /* MBEDTLS_FS_IO */

/**
 * \brief从无符号大端二进制数据导入MPI。
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param buf输入缓冲区。这必须是长度为\p buflen Bytes的可读缓冲区。\param buflen输入缓冲区的长度（字节）。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_read_binary( mbedtls_mpi *X, const unsigned char *buf,
                             size_t buflen );

/**
 * \brief从无符号二进制数据导入X，little-endian
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param buf输入缓冲区。这必须是长度为\p buflen Bytes的可读缓冲区。\param buflen输入缓冲区的长度（字节）。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_read_binary_le( mbedtls_mpi *X,
                                const unsigned char *buf, size_t buflen );

/**
 * \brief将X导出为无符号二进制数据，big endian。始终填充整个缓冲区，如果数字较小，缓冲区将以零开始。
 *
 * \param X源MPI。这必须指向已初始化的MPI。\param buf输出缓冲区。这必须是长度为\p buflen Bytes的可写缓冲区。\param buflen输出缓冲区的大小，以字节为单位。
 *
 * \如果成功，返回\c 0。\return#MBEDTLS_error_MPI_BUFFER_TOO_SMALL，如果\p buf不够大，无法保存\p X的值。\ return其他类型失败的负错误代码。
 */
int mbedtls_mpi_write_binary( const mbedtls_mpi *X, unsigned char *buf,
                              size_t buflen );

/**
 * \brief将X导出为无符号二进制数据，little-endian。始终填充整个缓冲区，如果数字较小，将以零结尾。
 *
 * \param X源MPI。这必须指向已初始化的MPI。\param buf输出缓冲区。这必须是长度为\p buflen Bytes的可写缓冲区。\param buflen输出缓冲区的大小，以字节为单位。
 *
 * \如果成功，返回\c 0。\return#MBEDTLS_error_MPI_BUFFER_TOO_SMALL，如果\p buf不够大，无法保存\p X的值。\ return其他类型失败的负错误代码。
 */
int mbedtls_mpi_write_binary_le( const mbedtls_mpi *X,
                                 unsigned char *buf, size_t buflen );

/**
 * \brief在MPI上执行左移：X<<=count
 *
 * \param X要移动的MPI。这必须指向已初始化的MPI。\param count要移位的位数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_shift_l( mbedtls_mpi *X, size_t count );

/**
 * \brief在MPI上执行右移：X>>=计数
 *
 * \param X要移动的MPI。这必须指向已初始化的MPI。\param count要移位的位数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_shift_r( mbedtls_mpi *X, size_t count );

/**
 * \brief比较两个MPIs的绝对值。
 *
 * \param X左侧MPI。这必须指向已初始化的MPI。\param Y右侧MPI。这必须指向已初始化的MPI。
 *
 * \如果“|X|”大于“|Y|”，则返回\c 1。\如果“|X|”小于“|Y|”，则返回\c-1。\如果“|X|”等于“|Y|”，则返回\c 0。
 */
int mbedtls_mpi_cmp_abs( const mbedtls_mpi *X, const mbedtls_mpi *Y );

/**
 * \brief比较两个MPI。
 *
 * \param X左侧MPI。这必须指向已初始化的MPI。\param Y右侧MPI。这必须指向已初始化的MPI。
 *
 * \如果\p X大于\p Y，则返回\c 1。如果\p Y小于\p X，则返回/c 1。
 */
int mbedtls_mpi_cmp_mpi( const mbedtls_mpi *X, const mbedtls_mpi *Y );

/**
 * \brief检查一个MPI是否在恒定时间内小于另一个MPI。
 *
 * \param X左侧MPI。这必须指向具有与Y相同的分配长度的初始化MPI。\param Y右侧MPI。这必须指向具有与X相同的分配长度的初始化MPI。\param ret比较结果：如果\p X小于\p Y，则为\c 1。
 *
 * \成功时返回0。\如果两个输入MPIs的分配长度不相同，则返回MBEDTLS_ERROR_MPI_BAD_INPUT_DATA。
 */
int mbedtls_mpi_lt_mpi_ct( const mbedtls_mpi *X, const mbedtls_mpi *Y,
        unsigned *ret );

/**
 * \brief将MPI与整数进行比较。
 *
 * \param X左侧MPI。这必须指向已初始化的MPI。\param z要比较\p X的整数值。
 *
 * \如果\p X大于\p z，则返回\c 1。如果\p X小于\p z时，返回\c-1。
 */
int mbedtls_mpi_cmp_int( const mbedtls_mpi *X, mbedtls_mpi_sint z );

/**
 * \brief执行MPIs的无符号加法：X=|A|+|B|
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A第一个被加数。这必须指向已初始化的MPI。\param B第二个被加数。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_add_abs( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief执行MPIs的无符号减法：X=|A|-|B|
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A被减数。这必须指向已初始化的MPI。\param B减数。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\return#MBEDTLS_error_MPI_NEGATIVE_VALUE，如果\p B大于\p A。\返回不同类型故障的另一个负错误代码。
 *
 */
int mbedtls_mpi_sub_abs( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief执行MPIs的签名添加：X=a+B
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A第一个被加数。这必须指向已初始化的MPI。\param B第二个被加数。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_add_mpi( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief执行MPIs的有符号减法：X=a-B
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A被减数。这必须指向已初始化的MPI。\param B减数。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_sub_mpi( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief执行MPI和整数的有符号加法：X=a+b
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A第一个被加数。这必须指向已初始化的MPI。\param b第二个被加数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_add_int( mbedtls_mpi *X, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief执行MPI和整数的有符号减法：X=a-b
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A被减数。这必须指向已初始化的MPI。\param b减数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_sub_int( mbedtls_mpi *X, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief执行两个MPI:X=a*B的乘法
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A第一个因素。这必须指向已初始化的MPI。\param B第二个因素。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 *
 */
int mbedtls_mpi_mul_mpi( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief执行MPI与无符号整数的乘法：X=a b
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A第一个因素。这必须指向已初始化的MPI。\param b第二个因素。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 *
 */
int mbedtls_mpi_mul_int( mbedtls_mpi *X, const mbedtls_mpi *A,
                         mbedtls_mpi_uint b );

/**
 * \brief使用两个MPI:a=Q B+R的剩余部分执行除法
 *
 * \param Q商的目标MPI。如果不需要商的值，则该值可能为空。\param R余数值的目标MPI。如果不需要余数的值，则该值可能为空。\param A股息。这必须指向已初始化的MPi。\param B除数。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p B等于零，则返回#MBEDTLS_ERROR_MPI_DIVISION_BY_ZERO。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_div_mpi( mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief将MPI的剩余部分除以整数：a=Q b+R
 *
 * \param Q商的目标MPI。如果不需要商的值，则该值可能为空。\param R余数值的目标MPI。如果不需要余数的值，则该值可能为空。\param A股息。这必须指向已初始化的MPi。\param b除数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p b等于零，则返回#MBEDTLS_ERROR_MPI_DIVISION_BY_ZERO。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_div_int( mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief执行模块化缩减。R=A模B
 *
 * \param R剩余值的目标MPI。这必须指向已初始化的MPI。\param A要计算其余数的MPI。这必须指向已初始化的MPI。\param B模块化约简的基础。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p B等于零，则返回#MBEDTLS_ERROR_MPI_DIVISION_BY_ZERO。\如果\p B为负，则返回#MBEDTLS_ERROR_MPI_NEGATIVE_VALUE。\返回不同类型失败的另一个负错误代码。
 *
 */
int mbedtls_mpi_mod_mpi( mbedtls_mpi *R, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief相对于整数执行模化约简。r=A模b
 *
 * \param r存储剩余量的地址。此值不能为空。\param A要计算其余数的MPI。这必须指向已初始化的MPi。\param b模归约的整数基数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p b等于零，则返回#MBEDTLS_ERROR_MPI_DIVISION_BY_ZERO。\如果\p b为负，则返回#MBEDTLS_ERROR_MPI_NEGATIVE_VALUE。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_mod_int( mbedtls_mpi_uint *r, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief执行滑动窗口求幂：X=a^E mod N
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A求幂的基数。这必须指向已初始化的MPI。\param E指数MPI。这必须指向已初始化的MPI。\param N模块化约简的基础。这必须指向已初始化的MPI。\param prec_RR一个仅依赖于\p N的帮助器MPI，它可用于为相同的\p N值加速多个模幂运算。这可能是空的。如果不是空，则必须指向已初始化的MPI。如果在调用mbedtls_mpi_init（）后未使用它，则此函数将计算助手值并将其存储在\p prec_RR中，以便在后续调用此函数时重用。否则，该函数将假定\p prec_RR保存由先前对mbedtls_mpi_exp_mod（）的调用设置的帮助值，并重用它。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\c N为负或偶数，或\c E为负，则返回#MBEDTLS_ERROR_MPI_BAD_INPUT_DATA。\返回不同类型失败的另一个负错误代码。
 *
 */
int mbedtls_mpi_exp_mod( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *E, const mbedtls_mpi *N,
                         mbedtls_mpi *prec_RR );

/**
 * \brief用随机字节数填充MPI。
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param size要生成的随机字节数。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\失败时返回另一个负错误代码。
 *
 * \注意从RNG获得的字节被解释为MPI的大端表示；这可能与确定性ECDSA等应用相关。
 */
int mbedtls_mpi_fill_random( mbedtls_mpi *X, size_t size,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng );

/** 在一定范围内均匀生成随机数。
 *
 * 此函数生成一个介于\p min（含）和\p N（不含）之间的随机数。
 *
 * 当RNG是HMAC_DRBG的适当参数化实例且最小值为1时，程序符合RFC 6979§3.3（确定性ECDSA）。
 *
 * \注意有“N-min”可能的输出。可以达到下限值，但不能达到上限值。
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param min要返回的最小值。它必须是非负的。\param N范围的上限，不包括在内。换句话说，这是一加上要返回的最大值。\p N必须严格大于\p min.\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p min或\p N无效或不兼容，则返回#MBEDTLS_ERROR_MPI_BAD_INPUT_DATA。\如果实现在有限的尝试次数内无法找到合适的值，则返回#MBEDTLS_ERROR_MPI_NOT_ACCEPTABLE。如果\p N显著大于\p min，则这种概率可以忽略不计，这是所有常用加密应用程序的情况。\失败时返回另一个负错误代码。
 */
int mbedtls_mpi_random( mbedtls_mpi *X,
                        mbedtls_mpi_sint min,
                        const mbedtls_mpi *N,
                        int (*f_rng)(void *, unsigned char *, size_t),
                        void *p_rng );

/**
 * \计算最大公约数：G=gcd（A，B）
 *
 * \param G目标MPI。这必须指向已初始化的MPI。\param A第一个操作数。这必须指向已初始化的MPI。\param B第二个操作数。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\返回不同类型失败的另一个负错误代码。
 */
int mbedtls_mpi_gcd( mbedtls_mpi *G, const mbedtls_mpi *A,
                     const mbedtls_mpi *B );

/**
 * \简要计算模逆：X=A^-1 mod N
 *
 * \param X目标MPI。这必须指向已初始化的MPI。\param A要计算的模逆的MPI。这必须指向已初始化的MPI。\param N模块化反转的基础。这必须指向已初始化的MPI。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p N小于或等于1，则返回#MBEDTLS_ERROR_MPI_BAD_INPUT_DATA。\返回#MBEDTLS_ERROR_MPI_NOT_ACCEPTABLE，如果\p没有与N相关的模逆。
 */
int mbedtls_mpi_inv_mod( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *N );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief以2<sup>-80</sup>的错误概率进行Miller-Rabin素性测试。
 *
 * \已弃用被mbedtls_mpi_is_prime_ext（）取代，它允许指定Miller Rabin循环数。
 *
 * \param X要检查原始性的MPI。这必须指向已初始化的MPI。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng未使用上下文参数，则该值可能为空。
 *
 * \如果成功，则返回\c 0，即\p X可能是素数。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p X不是素数，则返回#MBEDTLS_ERROR_MPI_NOT_ACCEPTABLE。\返回其他类型失败的另一个负错误代码。
 */
MBEDTLS_DEPRECATED int mbedtls_mpi_is_prime( const mbedtls_mpi *X,
                          int (*f_rng)(void *, unsigned char *, size_t),
                          void *p_rng );
#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \简单的米勒-拉宾素性测试。
 *
 * \警告如果\p X可能是由对手生成的，例如，在验证您自己没有生成并且应该是素数的密码参数时，那么\p回合应该至少是密码算法安全强度的一半。另一方面，如果一致地或非相反地选择\p X（就像mbedtls_mpi_gen_prime调用此函数时的情况一样），则\p轮数可以低得多。
 *
 * \param X要检查原始性的MPI。这必须指向已初始化的MPI。\param rounds要执行Miller-Rabin素性测试的基数。复合物上返回0的概率最多为2<sup>-2\p轮</sup>。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng未使用上下文参数，则该值可能为空。
 *
 * \如果成功，则返回\c 0，即\p X可能是素数。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果\p X不是素数，则返回#MBEDTLS_ERROR_MPI_NOT_ACCEPTABLE。\返回其他类型失败的另一个负错误代码。
 */
int mbedtls_mpi_is_prime_ext( const mbedtls_mpi *X, int rounds,
                              int (*f_rng)(void *, unsigned char *, size_t),
                              void *p_rng );
/**
 * \mbedtls_mpi_gen_prime（）的简要标志
 *
 * 这些标志中的每一个都是对mbedtls_mpi_gen_prime（）返回的结果X的约束。
 */
typedef enum {
    MBEDTLS_MPI_GEN_PRIME_FLAG_DH =      0x0001, /**<（X-1）/2也是素数*/
    MBEDTLS_MPI_GEN_PRIME_FLAG_LOW_ERR = 0x0002, /**<错误率从2<sup>-80</sup>降低到2<sup>-128</sup>*/
} mbedtls_mpi_gen_prime_flag_t;

/**
 * \brief生成素数。
 *
 * \param X存储生成的素数的目标MPI。这必须指向已初始化的MPi。\param nbits目标MPI所需的大小（以位为单位）。这必须介于\c 3和#MBEDTLS_MPI_MAX_BITS之间。\param flags#mbedtls_mpi_gen_prime_flag_t类型的标志掩码。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng参数。如果\p f_rng未使用上下文参数，则该值可能为空。
 *
 * \如果成功，则返回\c 0，在这种情况下，\p X可能持有一个素数。\如果内存分配失败，返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。\如果“nbits”不在\c 3和#MBEDTLS_MPI_MAX_BITS之间，则返回#MBEDTLS_ERR_MPI_BAD_INPUT_DATA。
 */
int mbedtls_mpi_gen_prime( mbedtls_mpi *X, size_t nbits, int flags,
                   int (*f_rng)(void *, unsigned char *, size_t),
                   void *p_rng );
#else /* MBEDTLS_BIGNUM_ALT */
#include "bignum_alt.h"
#endif /* MBEDTLS_BIGNUM_ALT */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_mpi_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 最大值h*/

