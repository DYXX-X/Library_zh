/**
 * @file 内存池API
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

#ifndef LWIP_HDR_MEMP_H
#define LWIP_HDR_MEMP_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 使用空定义运行一次，以处理lwippools中的所有自定义包含。小时*/
#define LWIP_MEMPOOL(name,num,size,desc)
#include "lwip/priv/memp_std.h"

/**创建由memp管理的所有内存池的列表。MEMP_MAX表示结尾处的空池*/
typedef enum {
#define LWIP_MEMPOOL(name,num,size,desc)  MEMP_##name,
#include "lwip/priv/memp_std.h"
  MEMP_MAX
} memp_t;

#include "lwip/priv/memp_priv.h"
#include "lwip/stats.h"

extern const struct memp_desc* const memp_pools[MEMP_MAX];

/**
 * @ingroup mempool如果在多个文件中使用，则声明专用内存池的原型
 */
#define LWIP_MEMPOOL_PROTOTYPE(name) extern const struct memp_desc memp_ ## name

#if MEMP_MEM_MALLOC

#define LWIP_MEMPOOL_DECLARE(name,num,size,desc) \
  LWIP_MEMPOOL_DECLARE_STATS_INSTANCE(memp_stats_ ## name) \
  const struct memp_desc memp_ ## name = { \
    DECLARE_LWIP_MEMPOOL_DESC(desc) \
    LWIP_MEMPOOL_DECLARE_STATS_REFERENCE(memp_stats_ ## name) \
    LWIP_MEM_ALIGN_SIZE(size) \
  };

#else /* MEMP_MEM_MALLOC */

/**
 * @ingroup mempool声明专用内存池专用内存池示例：.h：仅当在多个.c文件中使用池时：LWIP_mempool_PROTTYPE（my_private_pool）。c：
 *   -在全局变量部分：LWIP_MEMPOOL_DECLARE（my_private_pool，10，sizeof（foo），“Some description”）
 *   -在使用池之前调用ONCE（例如在某些init（）函数中）：LWIP_MEMPOOL_init（my_private_pool）；
 *   -allocate:void*my_new_mem=LWIP_MEMPOOL_ALLOC（my_private_pool）；
 *   -free:LWIP_MEMPOOL_free（my_private_pool，my_new_mem）；
 *
 * 要重新定位池，请在cc.h中将其声明为extern。GCC示例：extern u8_t\__attribute\_\_（（section（“.onchip_mem”）））memp_memory_my_private_pool_base[]；
 */
#define LWIP_MEMPOOL_DECLARE(name,num,size,desc) \
  LWIP_DECLARE_MEMORY_ALIGNED(memp_memory_ ## name ## _base, ((num) * (MEMP_SIZE + MEMP_ALIGN_SIZE(size)))); \
    \
  LWIP_MEMPOOL_DECLARE_STATS_INSTANCE(memp_stats_ ## name) \
    \
  static struct memp *memp_tab_ ## name; \
    \
  const struct memp_desc memp_ ## name = { \
    DECLARE_LWIP_MEMPOOL_DESC(desc) \
    LWIP_MEMPOOL_DECLARE_STATS_REFERENCE(memp_stats_ ## name) \
    LWIP_MEM_ALIGN_SIZE(size), \
    (num), \
    memp_memory_ ## name ## _base, \
    &memp_tab_ ## name \
  };

#endif /* MEMP_MEM_MALLOC */

/**
 * @ingroup mempool初始化专用内存池
 */
#define LWIP_MEMPOOL_INIT(name)    memp_init_pool(&memp_ ## name)
/**
 * @ingroup mempool从专用内存池分配
 */
#define LWIP_MEMPOOL_ALLOC(name)   memp_malloc_pool(&memp_ ## name)
/**
 * @ingroup mempool从专用内存池中释放元素
 */
#define LWIP_MEMPOOL_FREE(name, x) memp_free_pool(&memp_ ## name, (x))

#if MEM_USE_POOLS
/**此结构用于保存一个元素来自的池。这必须在此处定义，因为它是池大小计算所必需的。*/
struct memp_malloc_helper
{
   memp_t poolnr;
#if MEMP_OVERFLOW_CHECK || (LWIP_STATS && MEM_STATS)
   u16_t size;
#endif /* MEMP_OVERFLOW_CHECK || (LWIP_STATS && MEM_STATS) */
};
#endif /* MEM_USE_POOLS */

void  memp_init(void);

#if MEMP_OVERFLOW_CHECK
void *memp_malloc_fn(memp_t type, const char* file, const int line);
#define memp_malloc(t) memp_malloc_fn((t), __FILE__, __LINE__)
#else
void *memp_malloc(memp_t type);
#endif
void  memp_free(memp_t type, void *mem);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_MEMP_H */

