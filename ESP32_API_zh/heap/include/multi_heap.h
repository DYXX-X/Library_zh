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
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* multiheap是用于在单个程序中处理多个异构堆的堆实现。

   任何连续的内存块都可以注册为堆。
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 已注册堆的不透明句柄*/
typedef struct multi_heap_info *multi_heap_handle_t;

/**
 * @brief 分配具有特定对齐方式的内存块
 *
 * @param heap  注册堆的句柄。
 * @param size  内存块的字节大小
 * @param alignment  内存必须如何对齐
 *
 * @return 指向已分配内存的指针，失败时为NULL
 */
void *multi_heap_aligned_alloc(multi_heap_handle_t heap, size_t size, size_t alignment);

/** @brief malloc（）给定堆中的缓冲区
 *
 * 语义与标准malloc（）相同，只会在指定的堆中分配返回的缓冲区。
 *
 * @param heap 注册堆的句柄。
 * @param size 所需缓冲区的大小。
 *
 * @return 指向新内存的指针，如果分配失败，则返回NULL。
 */
void *multi_heap_malloc(multi_heap_handle_t heap, size_t size);

/** @brief free（）在给定堆中对齐的缓冲区。
 *
 * @param heap 注册堆的句柄。
 * @param p NULL，或先前从同一堆的multi_heap_aligned_alloc（）返回的指针。
 * @note 此函数已弃用，请考虑改用multi_heap_free（）
 */
void __attribute__((deprecated)) multi_heap_aligned_free(multi_heap_handle_t heap, void *p);

/** @brief free（）给定堆中的缓冲区。
 *
 * 语义与标准free（）相同，只有参数“p”必须为NULL或已在指定的堆中分配。
 *
 * @param heap 注册堆的句柄。
 * @param p NULL，或先前从同一堆的multi_heap_malloc（）或multi_heap.alloc（）返回的指针。
 */
void multi_heap_free(multi_heap_handle_t heap, void *p);

/** @brief realloc（）给定堆中的缓冲区。
 *
 * 语义与标准realloc（）相同，只有参数“p”必须为NULL或已在指定堆中分配。
 *
 * @param heap 注册堆的句柄。
 * @param p NULL，或先前从同一堆的multi_heap_malloc（）或multi_heap.alloc（）返回的指针。
 * @param size 缓冲区所需的新大小。
 *
 * @return “size”的新缓冲区包含“p”的内容，如果重新分配失败，则为NULL。
 */
void *multi_heap_realloc(multi_heap_handle_t heap, void *p, size_t size);


/** @brief 返回分配给特定指针的大小。
 *
 * @param heap 注册堆的句柄。
 * @param p 指针，必须是以前从同一堆的multi_heap_alloc（）或multi_heap.alloc（（）返回的。
 *
 * @return 此块分配的内存大小。由于填充和最小块大小，可能大于原始大小参数。
 */
size_t multi_heap_get_allocated_size(multi_heap_handle_t heap, void *p);


/** @brief 注册新堆以供使用
 *
 * 此函数在指定的地址初始化堆，并为将来的堆操作返回句柄。
 *
 * 取消注册堆没有等效的函数——如果堆中的所有块都是空闲的，您可以立即开始将内存用于其他目的。
 *
 * @param start 用于新堆的内存的起始地址。
 * @param size 新堆的大小（字节）。
 *
 * @return 准备使用的新堆的句柄，如果堆区域太小而无法初始化，则为NULL。
 */
multi_heap_handle_t multi_heap_register(void *start, size_t size);


/** @brief 将私有锁指针与堆关联
 *
 * 锁定参数提供给MULTI_HEAP_platform.h中定义的MULTI_HEAP_lock（）和MULTI_HEAD_UNLOCK（）宏。
 *
 * 有问题的锁必须是递归的。
 *
 * 当堆首次注册时，关联的锁为NULL。
 *
 * @param heap 注册堆的句柄。
 * @param lock 指向要与此堆关联的锁定结构的可选指针。
 */
void multi_heap_set_lock(multi_heap_handle_t heap, void* lock);

/** @brief 将堆信息转储到标准输出
 *
 * 出于调试目的，此函数将有关堆中每个块的信息转储到stdout。
 *
 * @param heap 注册堆的句柄。
 */
void multi_heap_dump(multi_heap_handle_t heap);

/** @brief 检查堆完整性
 *
 * 遍历堆并检查所有堆数据结构是否有效。如果检测到任何错误，可以选择将特定于错误的消息打印到stderr。通过在MULTI_heap_platform.h中定义MULTI_CHECK_FAIL_PRINTF，可以在编译时覆盖打印行为。
 *
 * @param heap 注册堆的句柄。
 * @param print_errors 如果为true，错误将打印到stderr。
 * @return 如果堆有效，则为true，否则为false。
 */
bool multi_heap_check(multi_heap_handle_t heap, bool print_errors);

/** @brief 返回空闲堆大小
 *
 * 返回堆中可用的字节数。
 *
 * 相当于multi_heap_get_heap_info（）返回的total_free_bytes成员。
 *
 * 注意，堆可能是碎片化的，因此单个malloc（）的实际最大大小可能更低。要了解此大小，请查看multi_heap_get_heap_info（）返回的largest_free_block成员。
 *
 * @param heap 注册堆的句柄。
 * @return 可用字节数。
 */
size_t multi_heap_free_size(multi_heap_handle_t heap);

/** @brief 返回生存期最小空闲堆大小
 *
 * 相当于multi_heap_get_info（）返回的minimum_free_bytes成员。
 *
 * 返回指定堆的multi_free_heap_size（）返回的可能值的生存期“低水位标记”。
 *
 * @param heap 注册堆的句柄。
 * @return 可用字节数。
 */
size_t multi_heap_minimum_free_size(multi_heap_handle_t heap);

/** @brief 通过multi_heap_get_info访问堆元数据的结构*/
typedef struct {
    size_t total_free_bytes;      ///<堆中的总可用字节数。等效于multi_free_heap_size（）。
    size_t total_allocated_bytes; ///<分配给堆中数据的总字节数。
    size_t largest_free_block;    ///<堆中最大可用块的大小。这是最大的mallocable大小。
    size_t minimum_free_bytes;    ///<生存期最小可用堆大小。等效于multi_minimum_free_heap_size（）。
    size_t allocated_blocks;      ///<堆中分配的（可变大小）块数。
    size_t free_blocks;           ///<堆中的（可变大小）可用块数。
    size_t total_blocks;          ///<堆中（可变大小）块的总数。
} multi_heap_info_t;

/** @brief 返回给定堆的元数据
 *
 * 用指定堆的信息填充multi_heap_info_t结构。
 *
 * @param heap 注册堆的句柄。
 * @param info 指向要填充堆元数据的结构的指针。
 */
void multi_heap_get_info(multi_heap_handle_t heap, multi_heap_info_t *info);

#ifdef __cplusplus
}
#endif

