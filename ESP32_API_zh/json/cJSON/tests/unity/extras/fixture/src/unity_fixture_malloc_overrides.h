/* 版权所有（c）2010 James Grenning和对Unity项目的贡献===================================Unity项目-c测试框架版权所有（c）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
 * ========================================== */

#ifndef UNITY_FIXTURE_MALLOC_OVERRIDES_H_
#define UNITY_FIXTURE_MALLOC_OVERRIDES_H_

#include <stddef.h>

#ifdef UNITY_EXCLUDE_STDLIB_MALLOC
/* 定义此宏以删除stdlib.h、malloc和free的使用。许多嵌入式系统默认没有堆或malloc/free。这个内部unity_malloc（）仅从数组末尾确定地提供分配的内存，unity_free（）只从数组末尾释放，块不合并，未按LIFO顺序释放的内存被搁浅。*/
    #ifndef UNITY_INTERNAL_HEAP_SIZE_BYTES
    #define UNITY_INTERNAL_HEAP_SIZE_BYTES 256
    #endif
#endif

/* Unity Fixture使用这些函数来分配和释放堆上的内存，并且可以使用特定于平台的实现来覆盖这些函数。例如，当使用FreeRTOS时，UNITY_FIXTURE_MALLOC变为pvPortMalloc（），UNITY_FIX _FREE变为vPortFree（）。*/
#if !defined(UNITY_FIXTURE_MALLOC) || !defined(UNITY_FIXTURE_FREE)
    #include <stdlib.h>
    #define UNITY_FIXTURE_MALLOC(size) malloc(size)
    #define UNITY_FIXTURE_FREE(ptr)    free(ptr)
#else
    extern void* UNITY_FIXTURE_MALLOC(size_t size);
    extern void UNITY_FIXTURE_FREE(void* ptr);
#endif

#define malloc  unity_malloc
#define calloc  unity_calloc
#define realloc unity_realloc
#define free    unity_free

void* unity_malloc(size_t size);
void* unity_calloc(size_t num, size_t size);
void* unity_realloc(void * oldMem, size_t size);
void unity_free(void * mem);

#endif /* UNITY_FIXTURE_MALLOC_OVERRIDES_H_ */

