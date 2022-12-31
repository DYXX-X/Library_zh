/**
 * @file 与TCPIP线程同步的函数
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
#ifndef LWIP_HDR_TCPIP_H
#define LWIP_HDR_TCPIP_H

#include "lwip/opt.h"

#if !NO_SYS /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/err.h"
#include "lwip/timeouts.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_TCPIP_CORE_LOCKING
/**用于锁定堆栈的全局信号量。*/
extern sys_mutex_t lock_tcpip_core;
#if !defined LOCK_TCPIP_CORE || defined __DOXYGEN__
/**锁定lwIP核心互斥体（需要@ref lwIP_TCPIP_core_LOCKING 1）*/
#define LOCK_TCPIP_CORE()     sys_mutex_lock(&lock_tcpip_core)
/**解锁lwIP核心互斥锁（需要@ref lwIP_TCPIP_core_LOCKING 1）*/
#define UNLOCK_TCPIP_CORE()   sys_mutex_unlock(&lock_tcpip_core)
#endif /* LOCK_TCPIP_CORE */
#else /* LWIP_TCPIP_CORE_LOCKING */
#define LOCK_TCPIP_CORE()
#define UNLOCK_TCPIP_CORE()
#endif /* LWIP_TCPIP_CORE_LOCKING */

struct pbuf;
struct netif;

/**传递给tcpip_init的init_done函数的函数原型*/
typedef void (*tcpip_init_done_fn)(void *arg);
/**传递给tcpip_callback（）的函数的函数原型*/
typedef void (*tcpip_callback_fn)(void *ctx);

/* 转发声明*/
struct tcpip_callback_msg;

void   tcpip_init(tcpip_init_done_fn tcpip_init_done, void *arg);

err_t  tcpip_inpkt(struct pbuf *p, struct netif *inp, netif_input_fn input_fn);
err_t  tcpip_input(struct pbuf *p, struct netif *inp);

err_t  tcpip_try_callback(tcpip_callback_fn function, void *ctx);
err_t  tcpip_callback(tcpip_callback_fn function, void *ctx);
/**  @ingroup lwip_os
 * @deprecated 请改用tcpip_try_callback（）或tcpip_callback
 */
#define tcpip_callback_with_block(function, ctx, block) ((block != 0)? tcpip_callback(function, ctx) : tcpip_try_callback(function, ctx))

struct tcpip_callback_msg* tcpip_callbackmsg_new(tcpip_callback_fn function, void *ctx);
void   tcpip_callbackmsg_delete(struct tcpip_callback_msg* msg);
err_t  tcpip_callbackmsg_trycallback(struct tcpip_callback_msg* msg);
err_t  tcpip_callbackmsg_trycallback_fromisr(struct tcpip_callback_msg* msg);

/* 从另一个上下文释放pbufs或堆内存而不阻塞*/
err_t  pbuf_free_callback(struct pbuf *p);
err_t  mem_free_callback(void *m);

#if LWIP_TCPIP_TIMEOUT && LWIP_TIMERS
err_t  tcpip_timeout(u32_t msecs, sys_timeout_handler h, void *arg);
err_t  tcpip_untimeout(sys_timeout_handler h, void *arg);
#endif /* LWIP_TCPIP_TIMEOUT && LWIP_TIMERS */

#ifdef TCPIP_THREAD_TEST
int tcpip_thread_poll_one(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* !NO_SYS */

#endif /* LWIP_HDR_TCPIP_H */

