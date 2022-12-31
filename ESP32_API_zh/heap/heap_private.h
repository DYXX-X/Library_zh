// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <soc/soc_memory_layout.h>
#include "multi_heap.h"
#include "multi_heap_platform.h"
#include "sys/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/* heap_caps_init使用的一些常见堆注册数据结构。c与heap_caps.c共享堆信息
*/

#define HEAP_SIZE_MAX (SOC_MAX_CONTIGUOUS_RAM_SIZE)

/* 用于描述每个已注册堆的类型*/
typedef struct heap_t_ {
    uint32_t caps[SOC_MEMORY_TYPE_NO_PRIOS]; ///<此堆中内存类型的功能（作为优先级集）。从soc_memory_types复制，因此它在RAM中而不是闪存中。
    intptr_t start;
    intptr_t end;
    multi_heap_lock_t heap_mux;
    multi_heap_handle_t heap;
    SLIST_ENTRY(heap_t_) next;
} heap_t;

/* 所有已注册的堆。

   形成单个链接列表，即使大多数条目是连续的。这意味着以每堆4字节为代价，可以在运行时以快速和线程安全的方式添加新堆。
*/
extern SLIST_HEAD(registered_heap_ll, heap_t_) registered_heaps;

bool heap_caps_match(const heap_t *heap, uint32_t caps);

/* 返回给定堆的所有可能功能（跨所有优先级）*/
inline static IRAM_ATTR uint32_t get_all_caps(const heap_t *heap)
{
    if (heap->heap == NULL) {
        return 0;
    }
    uint32_t all_caps = 0;
    for (int prio = 0; prio < SOC_MEMORY_TYPE_NO_PRIOS; prio++) {
        all_caps |= heap->caps[prio];
    }
    return all_caps;
}

/*
 因为我们不想向函数堆栈中添加其他已知的分配方法来跟踪wrt内存跟踪，所以这些方法被声明为私有的。newlibmalloc（）/realloc（）实现也调用这些，因此它们在newlib/syscalls.c中单独声明。
*/
void *heap_caps_realloc_default(void *p, size_t size);
void *heap_caps_malloc_default(size_t size);


#ifdef __cplusplus
}
#endif

