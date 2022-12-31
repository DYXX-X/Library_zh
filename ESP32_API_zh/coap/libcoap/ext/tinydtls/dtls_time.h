/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现
 *
 *******************************************************************************/

/**
 * @file dtls_时间.h
 * @brief 时钟处理
 */

#ifndef _DTLS_DTLS_TIME_H_
#define _DTLS_DTLS_TIME_H_

#include <stdint.h>
#include <sys/time.h>

#include "tinydtls.h"

/**
 * @defgroup 时钟处理内部时钟的默认实现。如果没有time（）和gettimeofday（），则应该重新定义它@{
 */

#ifdef WITH_CONTIKI
#include "clock.h"

#elif defined(RIOT_VERSION)

#include <xtimer.h>

/* FreeBSD上已经存在此宏，否则会导致重定义错误*/
#ifndef CLOCK_SECOND
#define CLOCK_SECOND (xtimer_ticks_from_usec64(1000000UL).ticks64)
#endif

typedef uint64_t clock_time_t;
#else /* WITH_CONTIKI || RIOT_VERSION */

#include <time.h>

#ifndef CLOCK_SECOND
# define CLOCK_SECOND 1000
#endif

typedef uint32_t clock_time_t;
#endif /* WITH_CONTIKI || RIOT_VERSION */

typedef clock_time_t dtls_tick_t;

#ifndef DTLS_TICKS_PER_SECOND
#define DTLS_TICKS_PER_SECOND CLOCK_SECOND
#endif /* DTLS_TICKS_PER_SECOND */

void dtls_clock_init(void);
void dtls_ticks(dtls_tick_t *t);

/** @} */

#endif /* _DTLS_DTLS_TIME_H_ */

