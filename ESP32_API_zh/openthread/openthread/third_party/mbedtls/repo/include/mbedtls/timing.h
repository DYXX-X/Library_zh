/**
 * \文件计时.h
 *
 * \用于超时和CPU周期计数器的简短便携式接口
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
#ifndef MBEDTLS_TIMING_H
#define MBEDTLS_TIMING_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_TIMING_ALT)
// 定期实施
//

/**
 * \简短计时器结构
 */
struct mbedtls_timing_hr_time
{
    unsigned char opaque[32];
};

/**
 * \mbedtls_timing_set/get_delay（）的简要上下文
 */
typedef struct mbedtls_timing_delay_context
{
    struct mbedtls_timing_hr_time   timer;
    uint32_t                        int_ms;
    uint32_t                        fin_ms;
} mbedtls_timing_delay_context;

#else  /* MBEDTLS_TIMING_ALT */
#include "timing_alt.h"
#endif /* MBEDTLS_TIMING_ALT */

extern volatile int mbedtls_timing_alarmed;

/**
 * \brief返回CPU周期计数器值
 *
 * \警告这只是最大的努力！不要依赖于此！特别是，它在虚拟机上是不可靠的。
 *
 * \注意：此值从未指定的原点开始，可能会换行。
 */
unsigned long mbedtls_timing_hardclock( void );

/**
 * \brief返回经过的时间（毫秒）
 *
 * \param val指向计时器结构\param reset如果为0，则查询经过的时间。否则（重新）启动计时器。
 *
 * \return自上次重置以来的经过时间（毫秒）。重新启动时，此值始终为0。
 *
 * \注意：要初始化计时器，请使用reset=1调用此函数。
 *
 *                 确定经过的时间并重置计时器在所有平台上都不是原子的，因此在序列“｛get_timer（1）；…；time1＝get_timeer（1），…；time2＝get_time（0）｝”之后，time1+time2的值仅近似于自第一次重置以来的延迟。
 */
unsigned long mbedtls_timing_get_timer( struct mbedtls_timing_hr_time *val, int reset );

/**
 * \简要设置闹钟
 *
 * \param设置“mbedtls_timing_alared”标志之前的秒延迟（必须大于等于0）
 *
 * \警告一次只支持一个报警。在线程上下文中，这意味着整个进程都有一个线程，而不是每个线程一个线程。
 */
void mbedtls_set_alarm( int seconds );

/**
 * \brief设置要监视的一对延迟（请参见\c mbedtls_timing_get_delay（）。）
 *
 * \param data指向定时数据的指针。必须指向有效的\c mbedtls_timing_delay_context结构。\param int_ms第一（中间）延迟（毫秒）。未指定int_ms>fin_ms时的效果。\param fin_ms秒（最终）延迟（毫秒）。传递0以取消当前延迟。
 *
 * \注意：若要设置单个延迟，请直接使用\c mbedtls_timing_set_timer，或将此函数与int_ms==fin_ms一起使用。
 */
void mbedtls_timing_set_delay( void *data, uint32_t int_ms, uint32_t fin_ms );

/**
 * \brief获取延迟的状态（内存助手：通过的延迟数。）
 *
 * \param data指向定时数据的指针必须指向有效的\c mbedtls_timing_delay_context结构。
 *
 * \如果取消（fin_ms=0），则返回-1；如果没有传递任何延迟，则返回0；如果只传递了中间延迟，则为1；如果传递了最终延迟，则是2。
 */
int mbedtls_timing_get_delay( void *data );

#if defined(MBEDTLS_SELF_TEST)
/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_timing_self_test( int verbose );
#endif

#ifdef __cplusplus
}
#endif

#endif /* 定时.h*/

