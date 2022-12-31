/*
** 两级隔离适配内存分配器，3.1版。Matthew Conte编写http://tlsf.baisoku.org
**
** 根据Miguel Masmano的原始文件：http://www.gii.upv.es/tlsf/main/docs
**
** 此实现是根据文档规范编写的，因此不适用GPL限制。
**
** 版权所有（c）2006-2016，Matthew Conte保留所有权利。
**
** 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名来支持或推广源自本软件的产品。
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHEW CONTE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "heap_tlsf_config.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*
** 强制转换和最小/最大宏。
*/
#define tlsf_cast(t, exp)	((t) (exp))
#define tlsf_min(a, b)		((a) < (b) ? (a) : (b))
#define tlsf_max(a, b)		((a) > (b) ? (a) : (b))

/* 执行指针运算时用于强制转换的类型。*/
typedef ptrdiff_t tlsfptr_t;

typedef struct block_header_t
{
	/* 指向上一个物理块。*/
	struct block_header_t* prev_phys_block;

	/* 此块的大小，不包括块标头。*/
	size_t size;

	/* 下一个和上一个空闲块。*/
	struct block_header_t* next_free;
	struct block_header_t* prev_free;
} block_header_t;

/* TLSF控制结构。*/
typedef struct control_t
{
	/* 空列表指向此块，表示它们是空闲的。*/
	block_header_t block_null;

	/* 免费列表的位图。*/
	unsigned int fl_bitmap;
	unsigned int sl_bitmap[FL_INDEX_COUNT];

	/* 免费列表负责人。*/
	block_header_t* blocks[FL_INDEX_COUNT][SL_INDEX_COUNT];
} control_t;

#include "heap_tlsf_block_functions.h"

/* tlsf_t：tlsf结构。可以包含1到N个池。*/
/* pool_t：TLSF可以管理的内存块。*/
typedef void* tlsf_t;
typedef void* pool_t;

/* 创建/销毁内存池。*/
tlsf_t tlsf_create(void* mem);
tlsf_t tlsf_create_with_pool(void* mem, size_t bytes);
pool_t tlsf_get_pool(tlsf_t tlsf);

/* 添加/删除内存池。*/
pool_t tlsf_add_pool(tlsf_t tlsf, void* mem, size_t bytes);
void tlsf_remove_pool(tlsf_t tlsf, pool_t pool);

/* malloc/memalalign/realloc/free替换。*/
void* tlsf_malloc(tlsf_t tlsf, size_t size);
void* tlsf_memalign(tlsf_t tlsf, size_t align, size_t size);
void* tlsf_memalign_offs(tlsf_t tlsf, size_t align, size_t size, size_t offset);
void* tlsf_realloc(tlsf_t tlsf, void* ptr, size_t size);
void tlsf_free(tlsf_t tlsf, void* ptr);

/* 返回内部块大小，而不是原始请求大小*/
size_t tlsf_block_size(void* ptr);

/* 内部结构的开销/限制。*/
size_t tlsf_size(void);
size_t tlsf_align_size(void);
size_t tlsf_block_size_min(void);
size_t tlsf_block_size_max(void);
size_t tlsf_pool_overhead(void);
size_t tlsf_alloc_overhead(void);

/* 调试。*/
typedef void (*tlsf_walker)(void* ptr, size_t size, int used, void* user);
void tlsf_walk_pool(pool_t pool, tlsf_walker walker, void* user);
/* 如果任何内部一致性检查失败，则返回非零。*/
int tlsf_check(tlsf_t tlsf);
int tlsf_check_pool(pool_t pool);

#if defined(__cplusplus)
};
#endif

