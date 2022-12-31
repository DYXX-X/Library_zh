/*
 * 版权所有（c）2001-2003瑞典计算机科学研究所。保留所有权利。
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

#ifndef __SYS_ARCH_H__
#define __SYS_ARCH_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "arch/vfs_lwip.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef SemaphoreHandle_t sys_sem_t;
typedef SemaphoreHandle_t sys_mutex_t;
typedef TaskHandle_t sys_thread_t;

typedef struct sys_mbox_s {
  QueueHandle_t os_mbox;
  void *owner;
}* sys_mbox_t;

/** 这是由_fromisr（）sys函数返回的，用于告诉最外层的函数一个更高优先级的任务被唤醒，需要调用调度器。
 */
#define ERR_NEED_SCHED 123

void sys_delay_ms(uint32_t ms);
#define sys_msleep(ms) sys_delay_ms(ms)

#define LWIP_COMPAT_MUTEX 0

#if !LWIP_COMPAT_MUTEX
#define sys_mutex_valid( x ) ( ( ( *x ) == NULL) ? pdFALSE : pdTRUE )
#define sys_mutex_set_invalid( x ) ( ( *x ) = NULL )
#endif

#define sys_mbox_valid( x ) ( ( ( *x ) == NULL) ? pdFALSE : pdTRUE )

/* 将sys_mbox_set_invalid（）定义为空，以支持ESP LWIP中的无锁mbox。
 *
 * 无锁mbox的基本思想是，除非没有套接字API使用套接字并且套接字关闭，否则mbox应该始终有效。ESP LWIP通过对官方LWIP进行以下两项更改来实现这一点：1.推迟mbox到netconn_free（）的释放，换句话说，在没有人使用套接字时释放mbox。2.如果没有实际释放mbox，则将sys_mbox_set_invalid（）定义为空。

 * 第二个变化是必要的。考虑一个常见的场景：应用程序任务调用recv（）从套接字接收数据包，sys_mbox_valid（）返回true。由于mbox没有锁，LWIP CORE可以随时调用sys_mbox_set_invalid（）来设置mbox，因此可能会发生线程安全问题。
 *
 * 但是，如果在sys_mbox_free（）之后未调用sys_mbox_set_invalid（），例如在netconn_alloc（）中，我们需要显式地将mbox初始化为无效，因为sys_mbox_set_invalid（）现在为空。
 */
#define sys_mbox_set_invalid( x )  *x = NULL

#define sys_sem_valid( x ) ( ( ( *x ) == NULL) ? pdFALSE : pdTRUE )
#define sys_sem_set_invalid( x ) ( ( *x ) = NULL )

void sys_delay_ms(uint32_t ms);
sys_sem_t* sys_thread_sem_init(void);
void sys_thread_sem_deinit(void);
sys_sem_t* sys_thread_sem_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_ARCH_H__ */

