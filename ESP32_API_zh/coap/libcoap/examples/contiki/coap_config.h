#ifndef COAP_CONFIG_H_
#define COAP_CONFIG_H_

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#define WITH_CONTIKI 1

#ifndef COAP_CONSTRAINED_STACK
#define COAP_CONSTRAINED_STACK 1
#endif

#ifndef COAP_DISABLE_TCP
#define COAP_DISABLE_TCP 1
#endif

#define PACKAGE_STRING "libcoap"
#define PACKAGE_NAME "libcoap"

#ifndef COAP_DEFAULT_PDU_SIZE
#define COAP_DEFAULT_PDU_SIZE 64
#endif /* COAP_DEFAULT_PDU_SIZE */
#ifndef COAP_RXBUFFER_SIZE
#define COAP_RXBUFFER_SIZE 64
#endif /* COAP_RXBUFFER_SIZE */

/**除了@c/之外，CoAP服务器可以处理的资源数。知名/核心*/
#ifndef COAP_MAX_RESOURCES
#define COAP_MAX_RESOURCES 3
#endif /* COAP_MAX_RESOURCES */

/** 可以处理的属性数（应至少为
 * @c 2*COAP_MAX_RESOURCES。以携带内容类型和资源类型。*/
#ifndef COAP_MAX_ATTRIBUTES
#define COAP_MAX_ATTRIBUTES 4
#endif /* COAP_MAX_ATTRIBUTES */

/**
 * 可同时存储的PDU数量。该数字包括存储用于重传的PDU以及接收的PDU。请注意，选择一个太小的值可能会导致许多重传需要处理。
 */
#ifndef COAP_PDU_MAXCNT
#define COAP_PDU_MAXCNT 4
#endif /* COAP_PDU_MAXCNT */

/**
 * 最大会话数。
 */
#ifndef COAP_MAX_SESSIONS
#define COAP_MAX_SESSIONS 2
#endif /* COAP_MAX_SESSIONS */

/**
 * 订阅的最大数量。每增加一个用户就要花费36B。
 */
#ifndef COAP_MAX_SUBSCRIBERS
#define COAP_MAX_SUBSCRIBERS 3
#endif /* COAP_MAX_SUBSCRIBERS */

/**
 * 分配固定大小内存块的最大缓存键条目数。
 */
#ifndef COAP_MAX_CACHE_KEYS
#define COAP_MAX_CACHE_KEYS        (2U)
#endif /* COAP_MAX_CACHE_KEYS */

/**
 * 分配固定大小内存块的缓存条目的最大数量。
 */
#ifndef COAP_MAX_CACHE_ENTRIES
#define COAP_MAX_CACHE_ENTRIES        (2U)
#endif /* COAP_MAX_CACHE_ENTRIES */

/**
 * 大型车身变速器的最大数量。
 */
#ifndef COAP_MAX_LG_XMIT
#define COAP_MAX_LG_XMIT 2
#endif /* COAP_MAX_LG_XMIT */

/**
 * 大型客户端接收的最大数量。
 */
#ifndef COAP_MAX_LG_CRCV
#define COAP_MAX_LG_CRCV 2
#endif /* COAP_MAX_LG_CRCV */

/**
 * 大型服务器接收的最大数量。
 */
#ifndef COAP_MAX_LG_SRCV
#define COAP_MAX_LG_SRCV 2
#endif /* COAP_MAX_LG_SRCV */

/**
 * 在发送可确认消息以检测观察者是否活动之前，可能发送的不可确认通知数。此处允许的最大值为@c 15。
 */
#ifndef COAP_OBS_MAX_NON
#define COAP_OBS_MAX_NON   5
#endif /* COAP_OBS_MAX_NON */

/**
 * 删除观察者之前可能失败（即超时而未确认）的可确认通知数。COAP_OBS_MAX_FAIL的最大值为@c 3。
 */
#ifndef COAP_OBS_MAX_FAIL
#define COAP_OBS_MAX_FAIL  3
#endif /* COAP_OBS_MAX_FAIL */

#ifndef DEBUG
# define DEBUG DEBUG_PRINT
#endif

#define HAVE_STRNLEN 1
#define HAVE_SNPRINTF 1
#define HAVE_STRINGS_H 1

/* 没有面向文件的输出*/
#define COAP_DEBUG_FD NULL
#define COAP_ERR_FD   NULL

#include "contiki-conf.h"

#if (defined(PLATFORM) && PLATFORM == PLATFORM_MC1322X) || defined(CONTIKI_TARGET_ECONOTAG)
/* Redbee经济运算在这里得到了特殊的处理：显式地设置了endianness，并且
 */

#define BYTE_ORDER UIP_LITTLE_ENDIAN

#define HAVE_ASSERT_H
#define HAVE_UNISTD_H
#define HAVE_SYS_TYPES_H
#define HAVE_LIMITS_H
#endif /* PLATFORM_MC1322X || CONTIKI_TARGET_ECONOTAG */

#if defined(TMOTE_SKY) || defined(CONTIKI_TARGET_SKY) || defined(CONTIKI_TARGET_WISMOTE)
/* 需要明确设置TMote Sky的字节顺序*/

#define BYTE_ORDER UIP_LITTLE_ENDIAN
#undef COAP_DEFAULT_PDU_SIZE
#undef COAP_RXBUFFER_SIZE
#define COAP_DEFAULT_PDU_SIZE 100
#define COAP_RXBUFFER_SIZE 100

#define COAP_MAX_BLOCK_SZX 2

typedef int ssize_t;
typedef void FILE;

#define HAVE_LIMITS_H 1
#undef HAVE_ASSERT_H
#define HAVE_VPRINTF 1
#endif /* 定义（TMOTE_SKY）*/

#ifdef CONTIKI_TARGET_MINIMAL_NET
#undef COAP_DEFAULT_PDU_SIZE
#undef COAP_RXBUFFER_SIZE
#define COAP_DEFAULT_PDU_SIZE 1152
#define COAP_RXBUFFER_SIZE 1472
#define HAVE_ASSERT_H 1
#define HAVE_VPRINTF 1
#define HAVE_SYS_TYPES_H 1
#endif /* CONTIKI_TARGET_MINIMAL_NET */

#ifdef CONTIKI_TARGET_CC2538DK
#define BYTE_ORDER UIP_LITTLE_ENDIAN
#undef COAP_DEFAULT_PDU_SIZE
#undef COAP_RXBUFFER_SIZE
#define COAP_DEFAULT_PDU_SIZE 100
#define COAP_RXBUFFER_SIZE 100

#undef COAP_MAX_BLOCK_SZX
#define COAP_MAX_BLOCK_SZX 2

#define HAVE_LIMITS_H 1
#endif /* CONTIKI_TARGET_CC2538DK */

#ifndef BYTE_ORDER
# ifdef UIP_CONF_BYTE_ORDER
#  define BYTE_ORDER UIP_CONF_BYTE_ORDER
# else
#  error "UIP_CONF_BYTE_ORDER not defined"
# endif /* UIP_CONF_BYTE_ORDER */
#endif /* BYTE_ORDER */

/* 除非给定HAVE_assert_H，否则将assert（）定义为空指令。*/
#ifndef HAVE_ASSERT_H
# define assert(x)
#endif

#define ntohs uip_ntohs

#include <stdio.h>
#define coap_log(fd, ...) printf(__VA_ARGS__)

#endif /* COAP_CONFIG_H_ */


