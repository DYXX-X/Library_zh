/****************************************************************************
** 版权所有（C）2017 Intel Corporation
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef COMPILERSUPPORT_H
#define COMPILERSUPPORT_H

#include "cbor.h"

#ifndef _BSD_SOURCE
#  define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
#endif
#ifndef assert
#  include <assert.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef __cplusplus
#  include <stdbool.h>
#endif

#if __STDC_VERSION__ >= 201112L || (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(__cpp_static_assert) && __cpp_static_assert >= 200410)
#  define cbor_static_assert(x)         static_assert(x, #x)
#elif !defined(__cplusplus) && defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 406) && (__STDC_VERSION__ > 199901L)
#  define cbor_static_assert(x)         _Static_assert(x, #x)
#else
#  define cbor_static_assert(x)         ((void)sizeof(char[2*!!(x) - 1]))
#endif
#if __STDC_VERSION__ >= 199901L || defined(__cplusplus)
/* inline是一个关键字*/
#else
/* 使用cbor中的定义。小时*/
#  define inline    CBOR_INLINE
#endif

#ifdef NDEBUG
#  define cbor_assert(cond)     do { if (!(cond)) unreachable(); } while (0)
#else
#  define cbor_assert(cond)     assert(cond)
#endif

#ifndef STRINGIFY
#define STRINGIFY(x)            STRINGIFY2(x)
#endif
#define STRINGIFY2(x)           #x

#if !defined(UINT32_MAX) || !defined(INT64_MAX)
/* C89？我们可以方便地定义UINT32_MAX，但不能定义INT64_MAX*/
#  error "Your system has stdint.h but that doesn't define UINT32_MAX or INT64_MAX"
#endif

#ifndef DBL_DECIMAL_DIG
/* DBL_DECIMAL_DIG为C11*/
#  define DBL_DECIMAL_DIG       17
#endif
#define DBL_DECIMAL_DIG_STR     STRINGIFY(DBL_DECIMAL_DIG)

#if defined(__GNUC__) && defined(__i386__) && !defined(__iamcu__)
#  define CBOR_INTERNAL_API_CC          __attribute__((regparm(3)))
#elif defined(_MSC_VER) && defined(_M_IX86)
#  define CBOR_INTERNAL_API_CC          __fastcall
#else
#  define CBOR_INTERNAL_API_CC
#endif

#ifndef __has_builtin
#  define __has_builtin(x)  0
#endif

#if (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 403)) || \
    (__has_builtin(__builtin_bswap64) && __has_builtin(__builtin_bswap32))
#  if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define cbor_ntohll     __builtin_bswap64
#    define cbor_htonll     __builtin_bswap64
#    define cbor_ntohl      __builtin_bswap32
#    define cbor_htonl      __builtin_bswap32
#    ifdef __INTEL_COMPILER
#      define cbor_ntohs    _bswap16
#      define cbor_htons    _bswap16
#    elif (__GNUC__ * 100 + __GNUC_MINOR__ >= 608) || __has_builtin(__builtin_bswap16)
#      define cbor_ntohs    __builtin_bswap16
#      define cbor_htons    __builtin_bswap16
#    else
#      define cbor_ntohs(x) (((uint16_t)(x) >> 8) | ((uint16_t)(x) << 8))
#      define cbor_htons    cbor_ntohs
#    endif
#  else
#    define cbor_ntohll
#    define cbor_htonll
#    define cbor_ntohl
#    define cbor_htonl
#    define cbor_ntohs
#    define cbor_htons
#  endif
#elif defined(__sun)
#  include <sys/byteorder.h>
#elif defined(_MSC_VER)
/* MSVC，表示Windows，表示小端和sizeof（long）==4*/
#  include <stdlib.h>
#  define cbor_ntohll       _byteswap_uint64
#  define cbor_htonll       _byteswap_uint64
#  define cbor_ntohl        _byteswap_ulong
#  define cbor_htonl        _byteswap_ulong
#  define cbor_ntohs        _byteswap_ushort
#  define cbor_htons        _byteswap_ushort
#endif
#ifndef cbor_ntohs
#  include <arpa/inet.h>
#  define cbor_ntohs        ntohs
#  define cbor_htons        htons
#endif
#ifndef cbor_ntohl
#  include <arpa/inet.h>
#  define cbor_ntohl        ntohl
#  define cbor_htonl        htonl
#endif
#ifndef cbor_ntohll
#  define cbor_ntohll       ntohll
#  define cbor_htonll       htonll
/* ntohll通常没有定义*/
#  ifndef ntohll
#    if (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || \
    (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) || \
    (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN) || \
    (defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)) || (defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)) || \
    defined(__ARMEB__) || defined(__MIPSEB__) || defined(__s390__) || defined(__sparc__)
#      define ntohll
#      define htonll
#    elif (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || \
    (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
    (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) && BYTE_ORDER == LITTLE_ENDIAN) || \
    defined(_LITTLE_ENDIAN) || defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) || defined(__MIPSEL__) || \
    defined(__i386) || defined(__i386__) || defined(__x86_64) || defined(__x86_64__) || defined(__amd64)
#      define ntohll(x)       ((ntohl((uint32_t)(x)) * UINT64_C(0x100000000)) + (ntohl((x) >> 32)))
#      define htonll          ntohll
#    else
#      error "Unable to determine byte order!"
#    endif
#  endif
#endif


#ifdef __cplusplus
#  define CONST_CAST(t, v)  const_cast<t>(v)
#else
/* C样式const_cast而不触发-Wcast qual警告*/
#  define CONST_CAST(t, v)  (t)(uintptr_t)(v)
#endif

#ifdef __GNUC__
#ifndef likely
#  define likely(x)     __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#  define unlikely(x)   __builtin_expect(!!(x), 0)
#endif
#  define unreachable() __builtin_unreachable()
#elif defined(_MSC_VER)
#  define likely(x)     (x)
#  define unlikely(x)   (x)
#  define unreachable() __assume(0)
#else
#  define likely(x)     (x)
#  define unlikely(x)   (x)
#  define unreachable() do {} while (0)
#endif

static inline bool add_check_overflow(size_t v1, size_t v2, size_t *r)
{
#if ((defined(__GNUC__) && (__GNUC__ >= 5)) && !defined(__INTEL_COMPILER)) || __has_builtin(__builtin_add_overflow)
    return __builtin_add_overflow(v1, v2, r);
#else
    /* 无符号加法定义明确*/
    *r = v1 + v2;
    return v1 > v1 + v2;
#endif
}

#endif /* COMPILERSUPPORT_H */


