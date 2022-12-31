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

/*
** 数据结构和相关常数。
*/

/*
** 由于块大小总是至少为4的倍数，因此大小字段的两个最低有效位用于存储块状态：
** -位0：块是忙还是空闲
** -位1：前一个块是忙还是空闲
*/
#define block_header_free_bit  (1 << 0)
#define block_header_prev_free_bit  (1 << 1)

/*
** 暴露给已使用块的块标头的大小是大小字段。prev_phys_block字段存储在前一个空闲块中。
*/
#define block_header_overhead  (sizeof(size_t))

/* 用户数据直接在使用的块中的大小字段之后开始。*/
#define block_start_offset (offsetof(block_header_t, size) + sizeof(size_t))

/*
** 空闲块必须足够大，以存储其标头减去prev_phys_block字段的大小，并且不能大于FL_INDEX的可寻址位数。
*/
#define block_size_min  (sizeof(block_header_t) - sizeof(block_header_t*))
#define block_size_max  (tlsf_cast(size_t, 1) << FL_INDEX_MAX)

/*
** block_header_t成员函数。
*/
static inline __attribute__((__always_inline__)) size_t block_size(const block_header_t* block)
{
	return block->size & ~(block_header_free_bit | block_header_prev_free_bit);
}

static inline __attribute__((__always_inline__)) void block_set_size(block_header_t* block, size_t size)
{
	const size_t oldsize = block->size;
	block->size = size | (oldsize & (block_header_free_bit | block_header_prev_free_bit));
}

static inline __attribute__((__always_inline__)) int block_is_last(const block_header_t* block)
{
	return block_size(block) == 0;
}

static inline __attribute__((__always_inline__)) int block_is_free(const block_header_t* block)
{
	return tlsf_cast(int, block->size & block_header_free_bit);
}

static inline __attribute__((__always_inline__)) void block_set_free(block_header_t* block)
{
	block->size |= block_header_free_bit;
}

static inline __attribute__((__always_inline__)) void block_set_used(block_header_t* block)
{
	block->size &= ~block_header_free_bit;
}

static inline __attribute__((__always_inline__)) int block_is_prev_free(const block_header_t* block)
{
	return tlsf_cast(int, block->size & block_header_prev_free_bit);
}

static inline __attribute__((__always_inline__)) void block_set_prev_free(block_header_t* block)
{
	block->size |= block_header_prev_free_bit;
}

static inline __attribute__((__always_inline__)) void block_set_prev_used(block_header_t* block)
{
	block->size &= ~block_header_prev_free_bit;
}

static inline __attribute__((__always_inline__)) block_header_t* block_from_ptr(const void* ptr)
{
	return tlsf_cast(block_header_t*,
		tlsf_cast(unsigned char*, ptr) - block_start_offset);
}

static inline __attribute__((__always_inline__)) void* block_to_ptr(const block_header_t* block)
{
	return tlsf_cast(void*,
		tlsf_cast(unsigned char*, block) + block_start_offset);
}

/* 返回给定大小的块之后的下一个块的位置。*/
static inline __attribute__((__always_inline__)) block_header_t* offset_to_block(const void* ptr, size_t size)
{
	return tlsf_cast(block_header_t*, tlsf_cast(tlsfptr_t, ptr) + size);
}

/* 返回上一个块的位置。*/
static inline __attribute__((__always_inline__)) block_header_t* block_prev(const block_header_t* block)
{
	return block->prev_phys_block;
}

/* 返回下一个现有块的位置。*/
static inline __attribute__((__always_inline__)) block_header_t* block_next(const block_header_t* block)
{
	block_header_t* next = offset_to_block(block_to_ptr(block),
		block_size(block) - block_header_overhead);
	return next;
}

/* 将新块与其物理邻居链接，返回邻居。*/
static inline __attribute__((__always_inline__)) block_header_t* block_link_next(block_header_t* block)
{
	block_header_t* next = block_next(block);
	next->prev_phys_block = block;
	return next;
}

static inline __attribute__((__always_inline__)) void block_mark_as_free(block_header_t* block)
{
	/* 首先将块链接到下一个块。*/
	block_header_t* next = block_link_next(block);
	block_set_prev_free(next);
	block_set_free(block);
}

static inline __attribute__((__always_inline__)) void block_mark_as_used(block_header_t* block)
{
	block_header_t* next = block_next(block);
	block_set_prev_used(next);
	block_set_used(block);
}

