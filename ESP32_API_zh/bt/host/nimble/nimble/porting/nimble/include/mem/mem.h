/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_UTIL_MEM_
#define H_UTIL_MEM_

#ifdef __cplusplus
extern "C" {
#endif

struct os_mempool;
struct os_mbuf_pool;

int mem_malloc_mempool(struct os_mempool *mempool, uint16_t num_blocks,
                       uint32_t block_size, char *name, void **out_buf);
int mem_malloc_mempool_ext(struct os_mempool_ext *mempool, uint16_t num_blocks,
                           uint32_t block_size, char *name, void **out_buf);

int mem_malloc_mbuf_pool(struct os_mempool *mempool,
                         struct os_mbuf_pool *mbuf_pool, uint16_t num_blocks,
                         uint32_t block_size, char *name,
                         void **out_buf);
int mem_malloc_mbufpkt_pool(struct os_mempool *mempool,
                            struct os_mbuf_pool *mbuf_pool, int num_blocks,
                            int block_size, char *name,
                            void **out_buf);
int mem_init_mbuf_pool(void *mem, struct os_mempool *mempool,
                       struct os_mbuf_pool *mbuf_pool, int num_blocks,
                       int block_size, const char *name);

/**
 * 指定用作回调的函数。这种类型的函数分配一个mbuf链，用于保存数据包片段。生成的mbuf必须包含pkthdr。
 *
 * @param frag_size             mbuf最终包含的数据字节数。
 * @param arg                   泛型参数。
 *
 * @return                      成功时分配的mbuf链；失败时为NULL。
 */
typedef struct os_mbuf *mem_frag_alloc_fn(uint16_t frag_size, void *arg);

struct os_mbuf *mem_split_frag(struct os_mbuf **om, uint16_t max_frag_sz,
                               mem_frag_alloc_fn *alloc_cb, void *cb_arg);

#ifdef __cplusplus
}
#endif

#endif

