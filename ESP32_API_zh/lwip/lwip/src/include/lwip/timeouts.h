/**
 * @file 计时器实现
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
 * 作者：Adam Dunkels<adam@sics.se>西蒙·戈德施密特
 *
 */
#ifndef LWIP_HDR_TIMEOUTS_H
#define LWIP_HDR_TIMEOUTS_H

#include "lwip/opt.h"
#include "lwip/err.h"
#if !NO_SYS
#include "lwip/sys.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LWIP_DEBUG_TIMERNAMES
#ifdef LWIP_DEBUG
#define LWIP_DEBUG_TIMERNAMES SYS_DEBUG
#else /* LWIP_DEBUG */
#define LWIP_DEBUG_TIMERNAMES 0
#endif /* LWIP_DEBUG*/
#endif

/** 由sys_timeouts_leeptime（）返回，表示没有计时器，因此我们可以永远睡觉。
 */
#define SYS_TIMEOUTS_SLEEPTIME_INFINITE 0xFFFFFFFF

/**必须以定义的间隔调用的堆栈内部计时器函数的函数原型*/
typedef void (* lwip_cyclic_timer_handler)(void);

/**此结构包含有关必须以定义的间隔调用的堆栈内部计时器函数的信息*/
struct lwip_cyclic_timer {
  u32_t interval_ms;
  lwip_cyclic_timer_handler handler;
#if LWIP_DEBUG_TIMERNAMES
  const char* handler_name;
#endif /* LWIP_DEBUG_TIMERNAMES */
};

/**此数组包含所有堆栈内部循环计时器。要获取计时器的数量，请使用lwip_num_cyclic_timers*/
extern const struct lwip_cyclic_timer lwip_cyclic_timers[];
/**lwip_cyclic_timers的数组大小[]*/
extern const int lwip_num_cyclic_timers;

#if LWIP_TIMERS

/** 超时回调函数的函数原型。使用sys_timeout（）注册这样的函数。
 *
 * @param arg 要传递给函数的附加参数-由sys_timeout（）设置
 */
typedef void (* sys_timeout_handler)(void *arg);

struct sys_timeo {
  struct sys_timeo *next;
  u32_t time;
  sys_timeout_handler h;
  void *arg;
#if LWIP_DEBUG_TIMERNAMES
  const char* handler_name;
#endif /* LWIP_DEBUG_TIMERNAMES */
};

void sys_timeouts_init(void);
void sys_timeouts_deinit(void);

#if LWIP_DEBUG_TIMERNAMES
void sys_timeout_debug(u32_t msecs, sys_timeout_handler handler, void *arg, const char* handler_name);
#define sys_timeout(msecs, handler, arg) sys_timeout_debug(msecs, handler, arg, #handler)
#else /* LWIP_DEBUG_TIMERNAMES */
void sys_timeout(u32_t msecs, sys_timeout_handler handler, void *arg);
#endif /* LWIP_DEBUG_TIMERNAMES */

void sys_untimeout(sys_timeout_handler handler, void *arg);
void sys_restart_timeouts(void);
void sys_check_timeouts(void);
u32_t sys_timeouts_sleeptime(void);

#if LWIP_TESTMODE
struct sys_timeo** sys_timeouts_get_next_timeout(void);
void lwip_cyclic_timer(void *arg);
#endif

#endif /* LWIP_TIMERS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_TIMEOUTS_H */

