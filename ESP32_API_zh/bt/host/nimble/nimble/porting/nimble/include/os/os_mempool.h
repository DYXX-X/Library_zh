/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/**
 * @addtogroup OS内核@{
 *   @defgroup OSMempool内存池@{
 */


#ifndef _OS_MEMPOOL_H_
#define _OS_MEMPOOL_H_

#include <stdbool.h>
#include "os/os.h"
#include "os/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 一种存储块结构。它只包含一个指向自由列表链的指针，仅在块位于自由列表上时使用。当该块从空闲列表中删除后，调用方可以使用整个内存块。
 */
struct os_memblock {
    SLIST_ENTRY(os_memblock) mb_next;
};

/* 三十： 更改此结构，以便保留池中的第一个地址？*/
/* 三十： 添加内存调试结构和相关代码*/
/* 三十： 更改此处SLIST_HEAD的编码方式。它应该命名为：SLIST_HEAD（，os_memblock）mp_HEAD；*/

/**
 * 内存池
 */
struct os_mempool {
    /**内存块的大小，以字节为单位。*/
    uint32_t mp_block_size;
    /**内存块的数量。*/
    uint16_t mp_num_blocks;
    /**剩余的可用块数*/
    uint16_t mp_num_free;
    /**所看到的最小空闲块数*/
    uint16_t mp_min_free;
    /**OS_MEMPOOL_F_[…]值的位图。*/
    uint8_t mp_flags;
    /**池使用的内存缓冲区地址*/
    uintptr_t mp_membuf_addr;
    STAILQ_ENTRY(os_mempool) mp_list;
    SLIST_HEAD(,os_memblock);
    /**内存块的名称*/
    const char *name;
};

/**
 * 表示扩展内存池。地址可以安全地强制转换为（structos_mempol_ext）。
 */
#define OS_MEMPOOL_F_EXT        0x01

struct os_mempool_ext;

/**
 * 块put回调函数。如果已配置，则每当将块释放到相应的扩展内存池时，就会执行此回调。注意：os_memblock_put（）函数调用此回调，而不是释放块本身。因此，回调负责通过调用os_memblock_put_from_cb（）释放块。
 *
 * @param ome                   将块释放回的扩展内存池。
 * @param data                  正在释放的块。
 * @param arg                   随回调一起配置的可选参数。
 *
 * @return                      指示块是否已成功释放。仅当块未成功释放回其池时，才应返回非零值。
 */
typedef os_error_t os_mempool_put_fn(struct os_mempool_ext *ome, void *data,
                                     void *arg);

struct os_mempool_ext {
    struct os_mempool mpe_mp;

    /* 释放块时立即执行的回调。*/
    os_mempool_put_fn *mpe_put_cb;
    void *mpe_put_arg;
};

#define OS_MEMPOOL_INFO_NAME_LEN (32)

/**
 * 描述内存池的信息，用于向管理层返回操作系统信息。
 */
struct os_mempool_info {
    /**池中内存块的大小*/
    int omi_block_size;
    /**池中的内存块数*/
    int omi_num_blocks;
    /**可用内存块数*/
    int omi_num_free;
    /**最小可用内存块数*/
    int omi_min_free;
    /**内存池的名称*/
    char omi_name[OS_MEMPOOL_INFO_NAME_LEN];
};

/**
 * 获取有关下一个系统内存池的信息。
 *
 * @param mempool 当前内存池，如果开始迭代，则为NULL。
 * @param info    指向要返回内存池信息的结构的指针。
 *
 * @return 列表中要获取信息的下一个内存池，或在最后一个内存池时为NULL。
 */
struct os_mempool *os_mempool_info_get_next(struct os_mempool *,
        struct os_mempool_info *);

/*
 * 计算池所需的内存缓冲区大小。注意：此大小不是以字节为单位！大小是内存池所需的os_membuf_t元素数。
 */
#if (OS_CFG_ALIGNMENT == OS_CFG_ALIGN_4)
#define OS_MEMPOOL_SIZE(n,blksize)      ((((blksize) + 3) / 4) * (n))
typedef uint32_t os_membuf_t;
#else
#define OS_MEMPOOL_SIZE(n,blksize)      ((((blksize) + 7) / 8) * (n))
typedef uint64_t os_membuf_t;
#endif

/**计算初始化内存池所需的字节数。*/
#define OS_MEMPOOL_BYTES(n,blksize)     \
    (sizeof (os_membuf_t) * OS_MEMPOOL_SIZE((n), (blksize)))

/**
 * 初始化内存池。
 *
 * @param mp            指向内存池指针的指针
 * @param blocks        池中的块数
 * @param blocks_size   块的大小，以字节为单位。
 * @param membuf        指向包含块的内存的指针。
 * @param name          池的名称。
 *
 * @return 操作系统错误
 */
os_error_t os_mempool_init(struct os_mempool *mp, uint16_t blocks,
                           uint32_t block_size, void *membuf, const char *name);

/**
 * 初始化扩展内存池。调用此函数时未指定扩展属性（例如回调）；它们在初始化后手动分配。
 *
 * @param mpe           要初始化的扩展内存池。
 * @param blocks        池中的块数。
 * @param block_size    每个块的大小，以字节为单位。
 * @param membuf        指向包含块的内存的指针。
 * @param name          池的名称。
 *
 * @return 操作系统错误
 */
os_error_t os_mempool_ext_init(struct os_mempool_ext *mpe, uint16_t blocks,
                               uint32_t block_size, void *membuf, const char *name);

/**
 * 清除内存池。
 *
 * @param mp            要清除的内存池。
 *
 * @return 操作系统错误
 */
os_error_t os_mempool_clear(struct os_mempool *mp);

/**
 * 清除扩展内存池。
 *
 * @param mpe            要清除的扩展内存池。
 *
 * @return 操作系统错误
 */
os_error_t os_mempool_ext_clear(struct os_mempool_ext *mpe);

/**
 * 对指定的内存池执行完整性检查。此函数尝试检测指定内存池中的内存损坏。
 *
 * @param mp                    要检查的内存池。
 *
 * @return                      如果内存池通过完整性检查，则为true；如果内存池损坏，则为false。
 */
bool os_mempool_is_sane(const struct os_mempool *mp);

/**
 * 检查是否从指定的内存池分配了内存块。
 *
 * @param mp                    要作为父项检查的内存池。
 * @param block_addr            要作为子项检查的内存块。
 *
 * @return                      如果块不属于内存池，则为0；如果块不属于内存池，则为1。
 */
int os_memblock_from(const struct os_mempool *mp, const void *block_addr);

/**
 * 从内存池中获取内存块
 *
 * @param mp 指向内存池的指针
 *
 * @return void*指向块的指针（如果可用）；否则为NULL
 */
void *os_memblock_get(struct os_mempool *mp);

/**
 * 将内存块放回池中，忽略put回调（如果有）。只能从put回调调用此函数以释放块，而不会导致无限递归。
 *
 * @param mp 指向内存池的指针
 * @param block_addr 指向内存块的指针
 *
 * @return 操作系统错误
 */
os_error_t os_memblock_put_from_cb(struct os_mempool *mp, void *block_addr);

/**
 * 将内存块放回池中
 *
 * @param mp 指向内存池的指针
 * @param block_addr 指向内存块的指针
 *
 * @return 操作系统错误
 */
os_error_t os_memblock_put(struct os_mempool *mp, void *block_addr);

#ifdef __cplusplus
}
#endif

#endif  /* _OS_MEMPOOL_H_ */


/**
 *   @} OS内存池
 * @} 操作系统核心
 */

