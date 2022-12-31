/**
 * @file 内存池lwIP内部实现（不在应用程序代码中使用）
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

#ifndef LWIP_HDR_MEMP_PRIV_H
#define LWIP_HDR_MEMP_PRIV_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/mem.h"
#include "lwip/priv/mem_priv.h"

#if MEMP_OVERFLOW_CHECK


/* MEMP_SIZE：为结构MEMP和健全性检查节省空间*/
#define MEMP_SIZE          (LWIP_MEM_ALIGN_SIZE(sizeof(struct memp)) + MEM_SANITY_REGION_BEFORE_ALIGNED)
#define MEMP_ALIGN_SIZE(x) (LWIP_MEM_ALIGN_SIZE(x) + MEM_SANITY_REGION_AFTER_ALIGNED)

#else /* MEMP_OVERFLOW_CHECK */

/* 无健全性检查我们不需要在未分配时保留结构memp，因此可以节省一点空间并将memp_SIZE设置为0。
 */
#define MEMP_SIZE           0
#define MEMP_ALIGN_SIZE(x) (LWIP_MEM_ALIGN_SIZE(x))

#endif /* MEMP_OVERFLOW_CHECK */

#if !MEMP_MEM_MALLOC || MEMP_OVERFLOW_CHECK
struct memp {
  struct memp *next;
#if MEMP_OVERFLOW_CHECK
  const char *file;
  int line;
#endif /* MEMP_OVERFLOW_CHECK */
};
#endif /* !MEMP_MEM_MALLOC || MEMP_OVERFLOW_CHECK */

#if MEM_USE_POOLS && MEMP_USE_CUSTOM_POOLS
/* 使用助手类型获取mem_malloc的用户“内存池”的开始和结束*/
typedef enum {
    /* 获取第一个（通过：MEMP_POOL_HELPER_START=（（u8_t）1MEMP_POOL_A+0*MEMP_POAL_B+0*MEMP_BOOL_C+0）*/
    MEMP_POOL_HELPER_FIRST = ((u8_t)
#define LWIP_MEMPOOL(name,num,size,desc)
#define LWIP_MALLOC_MEMPOOL_START 1
#define LWIP_MALLOC_MEMPOOL(num, size) * MEMP_POOL_##size + 0
#define LWIP_MALLOC_MEMPOOL_END
#include "lwip/priv/memp_std.h"
    ) ,
    /* 获取最后一个（通过：MEMP_POOL_HELPER_END=（（u8_t）0+MEMP_POAL_A*0+MEMP_BOOL_B*0+MEMP_POOL_C*1）*/
    MEMP_POOL_HELPER_LAST = ((u8_t)
#define LWIP_MEMPOOL(name,num,size,desc)
#define LWIP_MALLOC_MEMPOOL_START
#define LWIP_MALLOC_MEMPOOL(num, size) 0 + MEMP_POOL_##size *
#define LWIP_MALLOC_MEMPOOL_END 1
#include "lwip/priv/memp_std.h"
    )
} memp_pool_helper_t;

/* 实际的开始值和停止值在这里（将它们转换为）。我们使用此帮助器类型和这些定义，因此可以避免使用常量memp_t值*/
#define MEMP_POOL_FIRST ((memp_t) MEMP_POOL_HELPER_FIRST)
#define MEMP_POOL_LAST   ((memp_t) MEMP_POOL_HELPER_LAST)
#endif /* MEM_USE_POOLS && MEMP_USE_CUSTOM_POOLS */

/**内存池描述符*/
struct memp_desc {
#if defined(LWIP_DEBUG) || MEMP_OVERFLOW_CHECK || LWIP_STATS_DISPLAY
  /**文本描述*/
  const char *desc;
#endif /* LWIP_DEBUG || MEMP_OVERFLOW_CHECK || LWIP_STATS_DISPLAY */
#if MEMP_STATS
  /**统计学*/
  struct stats_mem *stats;
#endif

  /**元素大小*/
  u16_t size;

#if !MEMP_MEM_MALLOC
  /**元件数量*/
  u16_t num;

  /**基址*/
  u8_t *base;

  /**每个池的第一个空闲元素。元素形成链接列表。*/
  struct memp **tab;
#endif /* MEMP_MEM_MALLOC */
};

#if defined(LWIP_DEBUG) || MEMP_OVERFLOW_CHECK || LWIP_STATS_DISPLAY
#define DECLARE_LWIP_MEMPOOL_DESC(desc) (desc),
#else
#define DECLARE_LWIP_MEMPOOL_DESC(desc)
#endif

#if MEMP_STATS
#define LWIP_MEMPOOL_DECLARE_STATS_INSTANCE(name) static struct stats_mem name;
#define LWIP_MEMPOOL_DECLARE_STATS_REFERENCE(name) &name,
#else
#define LWIP_MEMPOOL_DECLARE_STATS_INSTANCE(name)
#define LWIP_MEMPOOL_DECLARE_STATS_REFERENCE(name)
#endif

void memp_init_pool(const struct memp_desc *desc);

#if MEMP_OVERFLOW_CHECK
void *memp_malloc_pool_fn(const struct memp_desc* desc, const char* file, const int line);
#define memp_malloc_pool(d) memp_malloc_pool_fn((d), __FILE__, __LINE__)
#else
void *memp_malloc_pool(const struct memp_desc *desc);
#endif
void  memp_free_pool(const struct memp_desc* desc, void *mem);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_MEMP_PRIV_H */

