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

/* 堆块的不透明句柄*/
typedef const struct block_header_t *multi_heap_block_handle_t;

/* multi_heap.c中定义的multi_heap API“实现”的内部定义。

   如果禁用了堆中毒，则这些将直接别名到公共API。

   如果启用了堆中毒，包装函数将调用其中的每一个。
*/

void *multi_heap_malloc_impl(multi_heap_handle_t heap, size_t size);

/* 分配最小“大小”字节的内存区域，按“对齐”对齐。*/
void *multi_heap_aligned_alloc_impl(multi_heap_handle_t heap, size_t size, size_t alignment);

/* 分配最小“大小”字节的内存区域，其中内存的“偏移”与“对齐”对齐。*/
void *multi_heap_aligned_alloc_impl_offs(multi_heap_handle_t heap, size_t size, size_t alignment, size_t offset);

void multi_heap_free_impl(multi_heap_handle_t heap, void *p);
void *multi_heap_realloc_impl(multi_heap_handle_t heap, void *p, size_t size);
multi_heap_handle_t multi_heap_register_impl(void *start, size_t size);
void multi_heap_get_info_impl(multi_heap_handle_t heap, multi_heap_info_t *info);
size_t multi_heap_free_size_impl(multi_heap_handle_t heap);
size_t multi_heap_minimum_free_size_impl(multi_heap_handle_t heap);
size_t multi_heap_get_allocated_size_impl(multi_heap_handle_t heap, void *p);
void *multi_heap_get_block_address_impl(multi_heap_block_handle_t block);

/* 堆中毒使用的一些内部函数*/

/* 检查已分配块的有害字节是否正确。由multi_heap_check（）调用。*/
bool multi_heap_internal_check_block_poisoning(void *start, size_t size, bool is_free, bool print_errors);

/* 用空闲模式或mallocated模式填充内存区域。在合并块时调用，以覆盖旧块标头。
*/
void multi_heap_internal_poison_fill_region(void *start, size_t size, bool is_free);

/* 如果multi_heap_check（）同时运行，则允许堆中毒锁定/解锁堆以避免竞争条件。
*/
void multi_heap_internal_lock(multi_heap_handle_t heap);

void multi_heap_internal_unlock(multi_heap_handle_t heap);

/* 堆调试代码要使用的一些内部函数*/

/* 获取堆中第一个（固定空闲）块的句柄*/
multi_heap_block_handle_t multi_heap_get_first_block(multi_heap_handle_t heap);

/* 获取堆中下一个块的句柄，并进行验证*/
multi_heap_block_handle_t multi_heap_get_next_block(multi_heap_handle_t heap, multi_heap_block_handle_t block);

/* 测试堆块是否可用*/
bool multi_heap_is_free(const multi_heap_block_handle_t block);

/* 获取堆块的数据地址*/
void *multi_heap_get_block_address(multi_heap_block_handle_t block);

/* 获取堆块的所有者标识*/
void *multi_heap_get_block_owner(multi_heap_block_handle_t block);

