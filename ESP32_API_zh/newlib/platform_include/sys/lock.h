#pragma once

#include_next <sys/lock.h>

#ifdef _RETARGETABLE_LOCKING

/* 结构__lock的特定定义的实际平台。这里的大小应该足以容纳FreeRTOS互斥锁。这由locks.c中的静态断言检查
 *
 * 注1：这可能需要取决于构建中是否包含FreeRTOS。
 *
 * 注意2：当启用configUSE_TRACE_FACILITY时，大小已足够。如果禁用，此定义将浪费8个字节。
 */
struct __lock {
   int reserved[23];
};

/* 传统ESP特定锁定实现的兼容性定义。这些过去由libc/sys/xxtesa/sys/lock提供。h在newlib中。较新版本的newlib没有此ESP特定的锁。h标头，并且是在启用_RETARGETABLE_LOCKING的情况下构建的。
 */

typedef _LOCK_T _lock_t;

void _lock_init(_lock_t *plock);
void _lock_init_recursive(_lock_t *plock);
void _lock_close(_lock_t *plock);
void _lock_close_recursive(_lock_t *plock);
void _lock_acquire(_lock_t *plock);
void _lock_acquire_recursive(_lock_t *plock);
int _lock_try_acquire(_lock_t *plock);
int _lock_try_acquire_recursive(_lock_t *plock);
void _lock_release(_lock_t *plock);
void _lock_release_recursive(_lock_t *plock);

#endif // _RETARGETABLE_LOCKING

