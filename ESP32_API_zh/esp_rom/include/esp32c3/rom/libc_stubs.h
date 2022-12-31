// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef _ROM_LIBC_STUBS_H_
#define _ROM_LIBC_STUBS_H_

#include <sys/lock.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <reent.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
ESP32-C3 ROM代码包含一些C库函数的实现。每当ROM中的函数需要使用系统调用时，它都会调用指向以下结构中定义的相应系统调用实现的指针。

默认情况下，表本身不在RAM中分配。全局指针syscall_table_ptr用于设置地址

所以，在使用任何C库函数（纯函数和memcpy/memset函数除外）之前，应用程序必须为所使用的每个CPU分配系统调用表结构，并用指针将其填充到相应系统调用的实际实现中。
*/

struct syscall_stub_table
{
    struct _reent* (*__getreent)(void);
    void* (*_malloc_r)(struct _reent *r, size_t);
    void (*_free_r)(struct _reent *r, void*);
    void* (*_realloc_r)(struct _reent *r, void*, size_t);
    void* (*_calloc_r)(struct _reent *r, size_t, size_t);
    void (*_abort)(void);
    int (*_system_r)(struct _reent *r, const char*);
    int (*_rename_r)(struct _reent *r, const char*, const char*);
    clock_t (*_times_r)(struct _reent *r, struct tms *);
    int (*_gettimeofday_r) (struct _reent *r, struct timeval *, void *);
    void (*_raise_r)(struct _reent *r);
    int (*_unlink_r)(struct _reent *r, const char*);
    int (*_link_r)(struct _reent *r, const char*, const char*);
    int (*_stat_r)(struct _reent *r, const char*, struct stat *);
    int (*_fstat_r)(struct _reent *r, int, struct stat *);
    void* (*_sbrk_r)(struct _reent *r, ptrdiff_t);
    int (*_getpid_r)(struct _reent *r);
    int (*_kill_r)(struct _reent *r, int, int);
    void (*_exit_r)(struct _reent *r, int);
    int (*_close_r)(struct _reent *r, int);
    int (*_open_r)(struct _reent *r, const char *, int, int);
    int (*_write_r)(struct _reent *r, int, const void *, int);
    int (*_lseek_r)(struct _reent *r, int, int, int);
    int (*_read_r)(struct _reent *r, int, void *, int);
    void (*_retarget_lock_init)(_LOCK_T *lock);
    void (*_retarget_lock_init_recursive)(_LOCK_T *lock);
    void (*_retarget_lock_close)(_LOCK_T lock);
    void (*_retarget_lock_close_recursive)(_LOCK_T lock);
    void (*_retarget_lock_acquire)(_LOCK_T lock);
    void (*_retarget_lock_acquire_recursive)(_LOCK_T lock);
    int (*_retarget_lock_try_acquire)(_LOCK_T lock);
    int (*_retarget_lock_try_acquire_recursive)(_LOCK_T lock);
    void (*_retarget_lock_release)(_LOCK_T lock);
    void (*_retarget_lock_release_recursive)(_LOCK_T lock);
    int (*_printf_float)(struct _reent *data, void *pdata, FILE * fp, int (*pfunc) (struct _reent *, FILE *, const char *, size_t len), va_list * ap);
    int (*_scanf_float) (struct _reent *rptr, void *pdata, FILE *fp, va_list *ap);
    void (*__assert_func) (const char *file, int line, const char * func, const char *failedexpr) __attribute__((noreturn));
    void (*__sinit) (struct _reent *r);
    void (*_cleanup_r) (struct _reent* r);
};

extern struct syscall_stub_table *syscall_table_ptr;

#ifdef __cplusplus
} // 外部“C”
#endif

#endif /* _ROM_LIBC_STUBS_H_ */

