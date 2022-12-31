/**
 * @file 各种实用宏
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
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */

/**
 * @defgroup 性能测量
 * @ingroup sys_layer与此节相关的所有定义都不能放在lwipopts中。h、 但在拱/性能上。啊！通过lwip进行的测量调用，这些调用可以被定义为空。
 * -PERF_START：开始测量一些东西。
 * -PERF_STOP（x）：停止测量，并记录结果。
 */

#ifndef LWIP_HDR_DEF_H
#define LWIP_HDR_DEF_H

/* 拱h可能已经定义了NULL*/
#include "lwip/arch.h"
#include "lwip/opt.h"
#if LWIP_PERF
#include "arch/perf.h"
#else /* LWIP_PERF */
#define PERF_START    /* 空定义*/
#define PERF_STOP(x)  /* 空定义*/
#endif /* LWIP_PERF */

#ifdef __cplusplus
extern "C" {
#endif

#define LWIP_MAX(x , y)  (((x) > (y)) ? (x) : (y))
#define LWIP_MIN(x , y)  (((x) < (y)) ? (x) : (y))

/* 获取数组中的条目数（'x'不能是指针！）*/
#define LWIP_ARRAYSIZE(x) (sizeof(x)/sizeof((x)[0]))

/**从字节创建u32_t值*/
#define LWIP_MAKEU32(a,b,c,d) (((u32_t)((a) & 0xff) << 24) | \
                               ((u32_t)((b) & 0xff) << 16) | \
                               ((u32_t)((c) & 0xff) << 8)  | \
                                (u32_t)((d) & 0xff))

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#if BYTE_ORDER == BIG_ENDIAN
#define lwip_htons(x) ((u16_t)(x))
#define lwip_ntohs(x) ((u16_t)(x))
#define lwip_htonl(x) ((u32_t)(x))
#define lwip_ntohl(x) ((u32_t)(x))
#define PP_HTONS(x)   ((u16_t)(x))
#define PP_NTOHS(x)   ((u16_t)(x))
#define PP_HTONL(x)   ((u32_t)(x))
#define PP_NTOHL(x)   ((u32_t)(x))
#else /* BYTE_ORDER != BIG_ENDIAN */
#ifndef lwip_htons
u16_t lwip_htons(u16_t x);
#endif
#define lwip_ntohs(x) lwip_htons(x)

#ifndef lwip_htonl
u32_t lwip_htonl(u32_t x);
#endif
#define lwip_ntohl(x) lwip_htonl(x)

/* 这些宏应该由预处理器计算，并且只与编译时常数一起使用（这样在运行时就不会有太多的端序开销）。*/
#define PP_HTONS(x) ((u16_t)((((x) & (u16_t)0x00ffU) << 8) | (((x) & (u16_t)0xff00U) >> 8)))
#define PP_NTOHS(x) PP_HTONS(x)
#define PP_HTONL(x) ((((x) & (u32_t)0x000000ffUL) << 24) | \
                     (((x) & (u32_t)0x0000ff00UL) <<  8) | \
                     (((x) & (u32_t)0x00ff0000UL) >>  8) | \
                     (((x) & (u32_t)0xff000000UL) >> 24))
#define PP_NTOHL(x) PP_HTONL(x)
#endif /* BYTE_ORDER == BIG_ENDIAN */

/* 为用户提供常用的函数名作为宏，但这可以关闭*/
#ifndef LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS
#define htons(x) lwip_htons(x)
#define ntohs(x) lwip_ntohs(x)
#define htonl(x) lwip_htonl(x)
#define ntohl(x) lwip_ntohl(x)
#endif

/* 作为标准实现不可用的函数。单位：cc。h、 如果在应用程序中也使用这些函数，则可以将这些函数定义为平台上可用的实现，以节省一些代码字节。
 */

#ifndef lwip_itoa
/* 根据您的平台，可以将其#定义为itoa（）或snprintf（result，bufsize，“%d”，number）*/
void  lwip_itoa(char* result, size_t bufsize, int number);
#endif
#ifndef lwip_strnicmp
/* 根据您的平台，它可以#定义为strnicmp（）或strncasecmp（）*/
int   lwip_strnicmp(const char* str1, const char* str2, size_t len);
#endif
#ifndef lwip_stricmp
/* 根据您的平台，它可以#定义为stricmp（）或strcasecmp（）*/
int   lwip_stricmp(const char* str1, const char* str2);
#endif
#ifndef lwip_strnstr
/* 这可以根据您的平台#定义为strnstr（）*/
char* lwip_strnstr(const char* buffer, const char* token, size_t n);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_DEF_H */

