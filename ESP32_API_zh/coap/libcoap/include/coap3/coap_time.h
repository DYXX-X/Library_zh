/*
 * coap_时间。h——时钟处理
 *
 * 版权所有（C）2010-2019 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 凝结时间.h
 * @brief 时钟处理
 */

#ifndef COAP_TIME_H_
#define COAP_TIME_H_

/**
 * @defgroup 时钟处理内部时钟的默认实现@{
 */

#if defined(WITH_LWIP)

#include <stdint.h>
#include <lwip/sys.h>

/* lwIP在sys_now中提供ms*/
#define COAP_TICKS_PER_SECOND 1000

typedef uint32_t coap_tick_t;
typedef uint32_t coap_time_t;
typedef int32_t coap_tick_diff_t;

COAP_STATIC_INLINE void coap_ticks_impl(coap_tick_t *t) {
  *t = sys_now();
}

COAP_STATIC_INLINE void coap_clock_init_impl(void) {
}

#define coap_clock_init coap_clock_init_impl
#define coap_ticks coap_ticks_impl

COAP_STATIC_INLINE coap_time_t coap_ticks_to_rt(coap_tick_t t) {
  return t / COAP_TICKS_PER_SECOND;
}

COAP_STATIC_INLINE uint64_t coap_ticks_to_rt_us(coap_tick_t t) {
  return (uint64_t)t * 1000000 / COAP_TICKS_PER_SECOND;
}

#elif defined(WITH_CONTIKI)

#include "clock.h"

typedef clock_time_t coap_tick_t;
typedef clock_time_t coap_time_t;

/**
 * 此数据类型用于表示两个clock_tick_t值之间的差异。此数据类型在内存中的大小必须与coap_tick_t相同，以允许换行。
 */
typedef int coap_tick_diff_t;

#define COAP_TICKS_PER_SECOND CLOCK_SECOND

COAP_STATIC_INLINE void coap_clock_init(void) {
  clock_init();
}

COAP_STATIC_INLINE void coap_ticks(coap_tick_t *t) {
  *t = clock_time();
}

COAP_STATIC_INLINE coap_time_t coap_ticks_to_rt(coap_tick_t t) {
  return t / COAP_TICKS_PER_SECOND;
}

COAP_STATIC_INLINE uint64_t coap_ticks_to_rt_us(coap_tick_t t) {
  return (uint64_t)t * 1000000 / COAP_TICKS_PER_SECOND;
}

#elif defined(RIOT_VERSION)
#include <xtimer.h>

#ifdef XTIMER_HZ
#define COAP_TICKS_PER_SECOND (XTIMER_HZ)
#else /* XTIMER_HZ */
#define COAP_TICKS_PER_SECOND (XTIMER_HZ_BASE)
#endif /* XTIMER_HZ */

typedef uint64_t coap_tick_t;
typedef int64_t coap_tick_diff_t;
typedef uint32_t coap_time_t;

static inline void coap_clock_init(void) {}

static inline void coap_ticks(coap_tick_t *t) {
  *t = xtimer_now_usec64();
}

static inline coap_time_t coap_ticks_to_rt(coap_tick_t t) {
  return t / 1000000UL;
}

static inline uint64_t coap_ticks_to_rt_us(coap_tick_t t) {
  return t;
}

static inline coap_tick_t coap_ticks_from_rt_us(uint64_t t) {
  return t / 1000000UL;
}
#else /* !WITH_LWIP && !WITH_CONTIKI && !RIOT_VERSION */

#include <stdint.h>

/**
 * 此数据类型表示COAP_ticks_PER_SECOND分辨率的内部计时器计时。
 */
typedef uint64_t coap_tick_t;

/**
 * 自epoch以来的CoAP时间（秒）。
 */
typedef time_t coap_time_t;

/**
 * 此数据类型用于表示两个clock_tick_t值之间的差异。此数据类型在内存中的大小必须与coap_tick_t相同，以允许换行。
 */
typedef int64_t coap_tick_diff_t;

/**在POSIX系统上使用ms分辨率*/
#define COAP_TICKS_PER_SECOND ((coap_tick_t)(1000U))

/**
 * 初始化内部时钟。
 */
void coap_clock_init(void);

/**
 * Sets @p t转换为COAP_TICKS_PER_SECOND分辨率的内部时间。
 */
void coap_ticks(coap_tick_t *t);

/**
 * 助手函数，用于将coap滴答声转换为墙上时钟时间。在POSIX上，此函数返回自epoch以来的秒数。在其他系统上，它可能是自上次重新启动后计算的秒数。
 *
 * @param t 内部系统滴答作响。
 *
 * @return  自特定参考点以来经过的秒数（自POSIX上的epoch以来的秒数）。
 */
coap_time_t coap_ticks_to_rt(coap_tick_t t);

/**
* Helper函数，它将coap滴答声转换为我们的POSIX挂钟时间。
*
* @param t 内部系统滴答作响。
*
* @return  自特定参考点以来经过的秒数（自POSIX上的epoch以来的秒数）。
*/
uint64_t coap_ticks_to_rt_us(coap_tick_t t);

/**
* Helper函数，它将我们体内的POSIX挂钟时间转换为coap滴答声。
*
* @param t POSIX时间就是我们
*
* @return  凝结蜱
*/
coap_tick_t coap_ticks_from_rt_us(uint64_t t);
#endif

/**
 * Returns @c 1当且仅当@p a小于@p b，其中less是在签名数据类型上定义的。
 */
COAP_STATIC_INLINE int coap_time_lt(coap_tick_t a, coap_tick_t b) {
  return ((coap_tick_diff_t)(a - b)) < 0;
}

/**
 * Returns @c 1当且仅当@p a小于或等于@p b，其中less是在签名数据类型上定义的。
 */
COAP_STATIC_INLINE int coap_time_le(coap_tick_t a, coap_tick_t b) {
  return a == b || coap_time_lt(a,b);
}

/** @} */

#endif /* COAP_TIME_H_ */

