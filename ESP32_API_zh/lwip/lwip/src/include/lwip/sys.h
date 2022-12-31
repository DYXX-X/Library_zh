/**
 * @file 操作系统抽象层
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
 */

#ifndef LWIP_HDR_SYS_H
#define LWIP_HDR_SYS_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#if NO_SYS

/* 对于完全最小且独立的系统，我们提供了sys_函数的空定义。*/
typedef u8_t sys_sem_t;
typedef u8_t sys_mutex_t;
typedef u8_t sys_mbox_t;

#define sys_sem_new(s, c) ERR_OK
#define sys_sem_signal(s)
#define sys_sem_wait(s)
#define sys_arch_sem_wait(s,t)
#define sys_sem_free(s)
#define sys_sem_valid(s) 0
#define sys_sem_valid_val(s) 0
#define sys_sem_set_invalid(s)
#define sys_sem_set_invalid_val(s)
#define sys_mutex_new(mu) ERR_OK
#define sys_mutex_lock(mu)
#define sys_mutex_unlock(mu)
#define sys_mutex_free(mu)
#define sys_mutex_valid(mu) 0
#define sys_mutex_set_invalid(mu)
#define sys_mbox_new(m, s) ERR_OK
#define sys_mbox_fetch(m,d)
#define sys_mbox_tryfetch(m,d)
#define sys_mbox_post(m,d)
#define sys_mbox_trypost(m,d)
#define sys_mbox_free(m)
#define sys_mbox_valid(m)
#define sys_mbox_valid_val(m)
#define sys_mbox_set_invalid(m)
#define sys_mbox_set_invalid_val(m)

#define sys_thread_new(n,t,a,s,p)

#define sys_msleep(t)

#else /* NO_SYS */

#if ESP_LWIP_LOCK
#define SYS_ARCH_PROTECT_CONN(_conn) do {\
  sys_mutex_lock(&(_conn)->lock);\
} while(0)

#define SYS_ARCH_UNPROTECT_CONN(_conn) do {\
  sys_mutex_unlock(&(_conn)->lock);\
} while(0)

#define SYS_ARCH_PROTECT_SOCK(_sock) do {\
  sys_mutex_lock(&(_sock)->lock);\
} while(0)

#define SYS_ARCH_UNPROTECT_SOCK(_sock) do{\
  sys_mutex_unlock(&(_sock)->lock);\
} while(0)
#endif /* ESP_LWIP_LOCK */

/**sys_arch_mbox_fetch和sys_arch_sem_wait的超时返回代码*/
#define SYS_ARCH_TIMEOUT 0xffffffffUL

/** sys_mbox_tryfetch（）返回sys_mbox_EMPTY（如果合适）。目前，我们使用相同的魔法值，但我们允许这在未来发生变化。
 */
#define SYS_MBOX_EMPTY SYS_ARCH_TIMEOUT

#include "lwip/err.h"
#include "arch/sys_arch.h"

/**线程函数的函数原型*/
typedef void (*lwip_thread_fn)(void *arg);

/* 由平台端口实现的函数的函数原型（在sys_arch.c中）*/

/* Mutex函数：*/

/**如果端口没有互斥体，则定义LWIP_COMPAT_MUTEX，而应改用二进制信号量*/
#ifndef LWIP_COMPAT_MUTEX
#define LWIP_COMPAT_MUTEX 0
#endif

#if LWIP_COMPAT_MUTEX
/* 对于没有互斥锁的旧端口：将它们定义为二进制信号量*/
#define sys_mutex_t                   sys_sem_t
#define sys_mutex_new(mutex)          sys_sem_new(mutex, 1)
#define sys_mutex_lock(mutex)         sys_sem_wait(mutex)
#define sys_mutex_unlock(mutex)       sys_sem_signal(mutex)
#define sys_mutex_free(mutex)         sys_sem_free(mutex)
#define sys_mutex_valid(mutex)        sys_sem_valid(mutex)
#define sys_mutex_set_invalid(mutex)  sys_sem_set_invalid(mutex)

#else /* LWIP_COMPAT_MUTEX */

/**
 * @ingroup sys_mutex创建一个新的互斥体。注意，lwIP代码预期不会递归地获取互斥锁，因此两种实现类型（递归或非递归）都应该工作。互斥锁分配给“互斥锁”指向的内存（既可以是指针，也可以是实际的OS结构）。如果已创建互斥锁，则应返回ERR_OK。返回任何其他错误将提供错误的提示，但除了断言之外，没有实现真正的错误处理。
 * 
 * @param mutex 指向要创建的互斥对象的指针
 * @return 如果成功，则返回ERR_OK，否则返回另一个错误_t
 */
err_t sys_mutex_new(sys_mutex_t *mutex);
/**
 * @ingroup sys_mutex阻塞线程，直到可以获取互斥锁。
 * @param mutex 要锁定的互斥锁
 */
void sys_mutex_lock(sys_mutex_t *mutex);
/**
 * @ingroup sys_mutex释放先前通过“sys_mutex_lock（）”锁定的互斥锁。
 * @param mutex 要解锁的互斥锁
 */
void sys_mutex_unlock(sys_mutex_t *mutex);
/**
 * @ingroup sys_mutex取消分配互斥对象。
 * @param mutex 要删除的互斥体
 */
void sys_mutex_free(sys_mutex_t *mutex);
#ifndef sys_mutex_valid
/**
 * @ingroup sys_mutex如果mutes有效，则返回1；如果无效，则返回0。使用指针时，一种简单的方法是检查指针的！=无效的。当直接使用OS结构时，实现这一点可能更复杂。这也可能是一个定义，在这种情况下，函数不是原型化的。
 */
int sys_mutex_valid(sys_mutex_t *mutex);
#endif
#ifndef sys_mutex_set_invalid
/**
 * @ingroup sys_mutex使互斥体无效，以便sys_mutex_validd（）返回0。注意：这并不意味着互斥体应被解除分配：在调用此函数之前始终调用sys_mutex.free（）！这也可能是一个定义，在这种情况下，函数不是原型化的。
 */
void sys_mutex_set_invalid(sys_mutex_t *mutex);
#endif
#endif /* LWIP_COMPAT_MUTEX */

/* 信号量功能：*/

/**
 * @ingroup sys_sem创建新的信号量创建新信号量。信号量分配给“sem”所指向的内存（既可以是指针，也可以是实际的OS结构）。“count”参数指定信号量的初始状态（0或1）。如果已创建信号量，则应返回ERR_OK。返回任何其他错误将提供错误的提示，但除了断言之外，没有实现真正的错误处理。
 *
 * @param sem 指向要创建的信号量的指针
 * @param count 信号量的初始计数
 * @return 如果成功，则返回ERR_OK，否则返回另一个错误_t
 */
err_t sys_sem_new(sys_sem_t *sem, u8_t count);
/**
 * @ingroup sys_sem发出信号量
 * @param sem 信号机到信号机
 */
void sys_sem_signal(sys_sem_t *sem);

#if ESP_LWIP
/** 信号量（ISR版本）
 * @param sem如果唤醒了更高优先级的任务，则将信号量设为@return非零*/
int sys_sem_signal_isr(sys_sem_t *sem);
#endif

/**
 * @ingroup sys_sem在等待发出信号时阻塞线程。如果“timeout”参数为非零，则线程只应被阻塞指定的时间（以毫秒为单位）。如果“timeout”参数为零，则应阻塞线程，直到发出信号。
 * 
 * 如果信号量在指定时间内未发出信号，则返回值为SYS_ARCH_TIMEOUT；如果信号量发出信号（有或无等待），则返回任何其他值。请注意，lwIP实现了一个同名的函数sys_sem_wait（），它使用sys_arch_sem_wai（）函数。
 * 
 * @param sem 等待的信号量
 * @param timeout 等待超时（毫秒）（0=永远等待）
 * @return 超时时为SYS_ARCH_TIMEOUT，成功时为任何其他值
 */
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout);
/**
 * @ingroup sys_sem取消分配信号量。
 * @param sem 要删除的信号量
 */
void sys_sem_free(sys_sem_t *sem);
/**等待信号灯-永远/无超时*/
#define sys_sem_wait(sem)                  sys_arch_sem_wait(sem, 0)
#ifndef sys_sem_valid
/**
 * @ingroup sys_sem如果信号量有效，则返回1；如果信号量无效，则返回0。使用指针时，一种简单的方法是检查指针的！=无效的。当直接使用OS结构时，实现这一点可能更复杂。这也可能是一个定义，在这种情况下，函数不是原型化的。
 */
int sys_sem_valid(sys_sem_t *sem);
#endif
#ifndef sys_sem_set_invalid
/**
 * @ingroup sys_sem使信号量无效，以便sys_sem_valid（）返回0。注意：这并不意味着信号量应被释放：在调用此函数之前，总是调用sys_sem_free（）！这也可能是一个定义，在这种情况下，函数不是原型化的。
 */
void sys_sem_set_invalid(sys_sem_t *sem);
#endif
#ifndef sys_sem_valid_val
/**
 * 与sys_sem_valid（）相同，但采用值，而不是指针
 */
#define sys_sem_valid_val(sem)       sys_sem_valid(&(sem))
#endif
#ifndef sys_sem_set_invalid_val
/**
 * 与sys_sem_set_invalid（）相同，但采用值，而不是指针
 */
#define sys_sem_set_invalid_val(sem) sys_sem_set_invalid(&(sem))
#endif

#ifndef sys_msleep
/**
 * @ingroup sys_misc休眠指定的毫秒数
 */
void sys_msleep(u32_t ms); /* 只有（接近）1ms的分辨率。*/
#endif

/* 邮箱功能。*/

/**
 * @ingroup sys_mbox为最大“大小”元素创建一个空邮箱。存储在邮箱中的元素是指针。您必须在lwipopt中定义宏“_MBOX_SIZE”。h、 或者在实现中忽略此参数并使用默认大小。如果已创建邮箱，则应返回ERR_OK。返回任何其他错误将提供错误的提示，但除了断言之外，没有实现真正的错误处理。
 * 
 * @param mbox 指向要创建的mbox的指针
 * @param size 此mbox中的（最小）邮件数
 * @return 如果成功，则返回ERR_OK，否则返回另一个错误_t
 */
err_t sys_mbox_new(sys_mbox_t *mbox, int size);
/**
 * @ingroup sys_mbox向mbox发布消息-可能不会失败
 * ->块（如果已满），仅用于任务而非ISR！
 * 
 * @param mbox mbox发布消息
 * @param msg 要发布的消息（注意：可以为空）
 */
void sys_mbox_post(sys_mbox_t *mbox, void *msg);
/**
 * @ingroup sys_mbox尝试向mbox发送消息-如果已满，可能会失败。可以从ISR中使用（如果系统层允许）。如果消息已满，则返回ERR_MEM；否则，如果发布了“消息”，则返回ERROR_OK。
 * 
 * @param mbox mbox发布消息
 * @param msg 要发布的消息（注意：可以为空）
 */
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg);
/**
 * @ingroup sys_mbox尝试向mbox发送消息-如果已满，可能会失败。由ISR使用。如果消息已满，则返回ERR_MEM；否则，如果发布了“消息”，则返回ERROR_OK。
 * 
 * @param mbox mbox发布消息
 * @param msg 要发布的消息（注意：可以为空）
 */
err_t sys_mbox_trypost_fromisr(sys_mbox_t *mbox, void *msg);
/**
 * @ingroup sys_mbox在消息到达邮箱之前阻止线程，但不会阻止线程超过“超时”毫秒（类似于sys_arch_sem_wait（）函数）。如果“timeout”为0，则线程应被阻止，直到消息到达。“msg”参数是由函数设置的结果参数（即，通过执行“msg=ptr”）。“msg”参数可能为NULL，表示应该删除消息。返回值与sys_arch_sem_wait（）函数的返回值相同：如果超时，则返回sys_arch_TIMEOUT，如果收到消息，则返回任何其他值。
 * 
 * 请注意，一个同名的函数sys_mbox_fetch（）是由lwIP实现的。
 * 
 * @param mbox mbox从中获取消息
 * @param msg 存储消息的指针
 * @param timeout 等待消息的最长时间（毫秒）（0=永远等待）
 * @return SYS_ARCH_TIMEOUT超时，如果收到消息，则为任何其他值
 */
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout);
/* 允许端口使用宏重写，例如sys_arch_mbox_fetch（）的特殊超时*/
#ifndef sys_arch_mbox_tryfetch
/**
 * @ingroup sys_mbox这类似于sys_arch_mbox_fetch，但是如果邮箱中没有消息，它会立即返回代码sys_mbox_EMPTY。成功时返回0。为了实现高效的实现，可以在sys_arch中将其定义为类似函数的宏。h而不是正常函数。例如，天真的实现可能是：\#define sys_arch_mbox_tryfetch（mbox，msg）sys_arch_mbox_fetch（mbox、msg，1），尽管这会引入不必要的延迟。
 * 
 * @param mbox mbox从中获取消息
 * @param msg 存储消息的指针
 * @return 如果已收到消息，则为0（毫秒）；如果邮箱为空，则为SYS_MBOX_EMPTY
 */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg);
#endif
/**
 * 现在，我们直接映射到sys_arch实现。
 */
#define sys_mbox_tryfetch(mbox, msg) sys_arch_mbox_tryfetch(mbox, msg)
/**
 * @ingroup sys_mbox取消分配邮箱。如果在解除分配邮箱时邮箱中仍然存在邮件，则表明lwIP中存在编程错误，应通知开发人员。
 * 
 * @param mbox 要删除的mbox
 */
void sys_mbox_free(sys_mbox_t *mbox);
#define sys_mbox_fetch(mbox, msg) sys_arch_mbox_fetch(mbox, msg, 0)
#ifndef sys_mbox_valid
/**
 * @ingroup sys_mbox如果邮箱有效，则返回1；如果无效，则返回0。使用指针时，一种简单的方法是检查指针的！=无效的。当直接使用OS结构时，实现这一点可能更复杂。这也可能是一个定义，在这种情况下，函数不是原型化的。
 */
int sys_mbox_valid(sys_mbox_t *mbox);
#endif
#ifndef sys_mbox_set_invalid
/**
 * @ingroup sys_mbox使邮箱无效，以便sys_mbox_valid（）返回0。注意：这并不意味着应该取消分配邮箱：在调用此函数之前，总是调用sys_mbox_free（）！这也可能是一个定义，在这种情况下，函数不是原型化的。
 */
void sys_mbox_set_invalid(sys_mbox_t *mbox);
#endif
#ifndef sys_mbox_valid_val
/**
 * 与sys_mbox_valid（）相同，但采用值，而不是指针
 */
#define sys_mbox_valid_val(mbox)       sys_mbox_valid(&(mbox))
#endif
#ifndef sys_mbox_set_invalid_val
/**
 * 与sys_mbox_set_invalid（）相同，但采用值而不是指针
 */
#define sys_mbox_set_invalid_val(mbox) sys_mbox_set_invalid(&(mbox))
#endif


/**
 * @ingroup sys_misc唯一的线程函数：启动一个名为“name”、优先级为“prio”的新线程，该线程将在函数“thread（）”中开始执行。“arg”参数将作为参数传递给thread（）函数。用于此线程的堆栈大小是“stacksize”参数。将返回新线程的id。id和优先级都取决于系统。注意：虽然此函数返回一个值，但绝对不能失败（端口必须声明此值！）
 * 
 * @param name 线程的可读名称（用于调试目的）
 * @param thread 线程函数
 * @param arg 传递给“thread”的参数
 * @param stacksize新线程的堆栈大小（以字节为单位）（端口可以忽略）@param新线程的prio优先级（端口可以忽视）*/
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio);

#endif /* NO_SYS */

/**
 * @ingroup 必须先调用sys_misc sys_init（），然后再调用其他命令。初始化sys_arch层。
 */
void sys_init(void);

#ifndef sys_jiffies
/**
 * 通电后的滴答声。
 */
u32_t sys_jiffies(void);
#endif

/**
 * @ingroup sys_time返回当前时间（以毫秒为单位），可以与sys_jiffies相同或至少基于它。不要在意包装，这只用于时间差异。不实现此功能意味着您不能使用某些模块（例如，TCP时间戳、NO_SYS==1的内部超时）。
 */
u32_t sys_now(void);

/* 关键区域保护*/
/* 这些函数必须在sys_arch中实现。c文件。在一些实现中，它们可以提供比使用信号量更轻的保护机制。否则，信号量可用于实现*/
#ifndef SYS_ARCH_PROTECT
/** SYS_LIGHTWEIGHT_PROT在lwipots中定义SYS_LIGHT WEIGHTPROT。h如果您希望在缓冲区分配、解除分配和内存分配和解除分配期间对某些关键区域进行任务间保护。
 */
#if SYS_LIGHTWEIGHT_PROT

/**
 * @ingroup sys_prot sys_ARCH_DECL_PROTECT声明保护变量。此宏将默认定义sys_prot_t类型的变量。如果特定端口需要不同的实现，则可以在sys_arch.h中定义此宏。
 */
#define SYS_ARCH_DECL_PROTECT(lev) sys_prot_t lev
/**
 * @ingroup sys_prot sys_ARCH_PROTECT执行“快速”保护。这可以通过禁用嵌入式系统的中断或使用信号量或互斥量来实现。实现应允许在已受保护时调用SYS_ARCH_PROTECT。旧的保护级别在变量“lev”中返回。此宏将默认调用sys_arch_proctect（）函数，该函数应在sys_arch.c中实现。如果特定端口需要不同的实现，则可以在sys_aarch.h中定义此宏
 */
#define SYS_ARCH_PROTECT(lev) lev = sys_arch_protect()
/**
 * @ingroup sys_prot sys_ARCH_UNPROTECT将保护级别“快速”设置为“lev”。这可以通过在MACRO中将中断级别设置为“lev”或使用信号量或互斥量来实现。此宏将默认调用sys_arch_unprotect（）函数，该函数应在sys_arch.c中实现。如果特定端口需要不同的实现，则可以在sys_aarch.h中定义此宏
 */
#define SYS_ARCH_UNPROTECT(lev) sys_arch_unprotect(lev)
sys_prot_t sys_arch_protect(void);
void sys_arch_unprotect(sys_prot_t pval);

#else

#define SYS_ARCH_DECL_PROTECT(lev)
#define SYS_ARCH_PROTECT(lev)
#define SYS_ARCH_UNPROTECT(lev)

#endif /* SYS_LIGHTWEIGHT_PROT */

#endif /* SYS_ARCH_PROTECT */

/*
 * 以线程安全的方式设置/获取和增加/减少变量的宏。使用它们访问从多个线程使用的变量。
 */

#ifndef SYS_ARCH_INC
#define SYS_ARCH_INC(var, val) do { \
                                SYS_ARCH_DECL_PROTECT(old_level); \
                                SYS_ARCH_PROTECT(old_level); \
                                var += val; \
                                SYS_ARCH_UNPROTECT(old_level); \
                              } while(0)
#endif /* SYS_ARCH_INC */

#ifndef SYS_ARCH_DEC
#define SYS_ARCH_DEC(var, val) do { \
                                SYS_ARCH_DECL_PROTECT(old_level); \
                                SYS_ARCH_PROTECT(old_level); \
                                var -= val; \
                                SYS_ARCH_UNPROTECT(old_level); \
                              } while(0)
#endif /* SYS_ARCH_DEC */

#ifndef SYS_ARCH_GET
#define SYS_ARCH_GET(var, ret) do { \
                                SYS_ARCH_DECL_PROTECT(old_level); \
                                SYS_ARCH_PROTECT(old_level); \
                                ret = var; \
                                SYS_ARCH_UNPROTECT(old_level); \
                              } while(0)
#endif /* SYS_ARCH_GET */

#ifndef SYS_ARCH_SET
#define SYS_ARCH_SET(var, val) do { \
                                SYS_ARCH_DECL_PROTECT(old_level); \
                                SYS_ARCH_PROTECT(old_level); \
                                var = val; \
                                SYS_ARCH_UNPROTECT(old_level); \
                              } while(0)
#endif /* SYS_ARCH_SET */

#ifndef SYS_ARCH_LOCKED
#define SYS_ARCH_LOCKED(code) do { \
                                SYS_ARCH_DECL_PROTECT(old_level); \
                                SYS_ARCH_PROTECT(old_level); \
                                code; \
                                SYS_ARCH_UNPROTECT(old_level); \
                              } while(0)
#endif /* SYS_ARCH_LOCKED */


#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_SYS_H */

