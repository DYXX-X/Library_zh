/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "multi_heap.h"
#include <sdkconfig.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 指示各种内存系统功能的标志
 */
#define MALLOC_CAP_EXEC             (1<<0)  ///<内存必须能够运行可执行代码
#define MALLOC_CAP_32BIT            (1<<1)  ///<内存必须允许对齐的32位数据访问
#define MALLOC_CAP_8BIT             (1<<2)  ///<内存必须允许8/16/…位数据访问
#define MALLOC_CAP_DMA              (1<<3)  ///<内存必须能够通过DMA访问
#define MALLOC_CAP_PID2             (1<<4)  ///<内存必须映射到PID2内存空间（当前未使用PID）
#define MALLOC_CAP_PID3             (1<<5)  ///<内存必须映射到PID3内存空间（当前未使用PID）
#define MALLOC_CAP_PID4             (1<<6)  ///<内存必须映射到PID4内存空间（当前未使用PID）
#define MALLOC_CAP_PID5             (1<<7)  ///<内存必须映射到PID5内存空间（当前未使用PID）
#define MALLOC_CAP_PID6             (1<<8)  ///<内存必须映射到PID6内存空间（当前未使用PID）
#define MALLOC_CAP_PID7             (1<<9)  ///<内存必须映射到PID7内存空间（当前未使用PID）
#define MALLOC_CAP_SPIRAM           (1<<10) ///<内存必须在SPI RAM中
#define MALLOC_CAP_INTERNAL         (1<<11) ///<内存必须是内部的；特别是，当flash/spiram缓存关闭时，它不会消失
#define MALLOC_CAP_DEFAULT          (1<<12) ///<内存可以在非特定功能的内存分配（例如malloc（）、calloc（））调用中返回
#define MALLOC_CAP_IRAM_8BIT        (1<<13) ///<内存必须在IRAM中并允许未对齐的访问
#define MALLOC_CAP_RETENTION        (1<<14)
#define MALLOC_CAP_RTCRAM           (1<<15) ///<内存必须在RTC快速内存中

#define MALLOC_CAP_INVALID          (1<<31) ///<无法使用内存/列出结束标记

/**
 * @brief 分配操作失败时调用的回调（如果已注册）
 * @param size 失败分配的字节数
 * @param caps 分配失败请求的容量
 * @param function_name 导致故障的函数
 */
typedef void (*esp_alloc_failed_hook_t) (size_t size, uint32_t caps, const char * function_name);

/**
 * @brief 注册在内存分配操作失败时要调用的回调函数
 * @param callback 要调用的调用者定义的回调
 * @return ESP_OK（如果已注册回调）。
 */
esp_err_t heap_caps_register_failed_alloc_callback(esp_alloc_failed_hook_t callback);

/**
 * @brief 分配具有给定功能的内存块
 *
 * 与libc malloc（）等价的语义，用于功能感知内存。
 *
 * 在IDF中，“malloc（p）”相当于“heap_caps_malloc（p，malloc_CAP_8BIT）”。
 *
 * @param size 要分配的内存量的大小（字节）
 * @param caps        MALLOC_CAP_*标志的位或，指示要返回的内存类型
 *
 * @return 指向成功时分配的内存的指针，失败时为NULL
 */
void *heap_caps_malloc(size_t size, uint32_t caps);


/**
 * @brief 释放以前通过heap_caps_malloc（）或heap_caps-relalloc（）分配的内存。
 *
 * 等效于libc-free（）的语义，用于功能感知内存。
 *
 *  在IDF中，“free（p）”等同于“heap_caps_free（p）”。
 *
 * @param ptr 指向先前从heap_caps_malloc（）或heap_caps.relalloc（）返回的内存的指针。可以为NULL。
 */
void heap_caps_free( void *ptr);

/**
 * @brief 重新分配以前通过heap_cps_malloc（）或heap_caps_alloc（）分配的内存。
 *
 * 与libc realloc（）等价的语义，用于功能感知内存。
 *
 * 在IDF中，“realloc（p，s）”等同于“heap_caps_alloc（p，s，MALLOC_CAP_8BIT）”。
 *
 * “caps”参数可以与分配给任何原始“ptr”的功能不同。这样，如果需要，可以使用realloc来“移动”缓冲区，以确保它满足一组新的功能。
 *
 * @param ptr 指向先前分配的内存的指针，或新分配的NULL。
 * @param size 请求的新缓冲区大小，或0释放缓冲区。
 * @param caps        MALLOC_CAP_*标志的位“或”表示新分配所需的内存类型。
 *
 * @return 指向大小为“size”、功能为“caps”的新缓冲区的指针，如果分配失败，则返回NULL。
 */
void *heap_caps_realloc( void *ptr, size_t size, uint32_t caps);

/**
 * @brief 分配具有给定功能的对齐内存块
 *
 * 与libc aligned_alloc（）等价的语义，用于功能感知内存。
 * @param alignment  接收到的指针需要如何对齐必须是2的幂
 * @param size 要分配的内存量的大小（字节）
 * @param caps        MALLOC_CAP_*标志的位或，指示要返回的内存类型
 *
 * @return 指向成功时分配的内存的指针，失败时为NULL
 *
 *
 */
void *heap_caps_aligned_alloc(size_t alignment, size_t size, uint32_t caps);

/**
 * @brief 用于释放以前分配给heap_caps_aligned_alloc的内存
 *
 * @param ptr 指向已分配内存的指针
 * @note 此函数已弃用，请考虑改用heap_caps_free（）
 */
void __attribute__((deprecated))  heap_caps_aligned_free(void *ptr);

/**
 * @brief 分配具有给定功能的对齐内存块。内存中的初始化值设置为零。
 *
 * @param alignment  接收到的指针需要如何对齐必须是2的幂
 * @param n    要分配的连续内存块数
 * @param size 要分配的内存块的大小（字节）
 * @param caps        MALLOC_CAP_*标志的位或，指示要返回的内存类型
 *
 * @return 指向成功时分配的内存的指针，失败时为NULL
 *
 */
void *heap_caps_aligned_calloc(size_t alignment, size_t n, size_t size, uint32_t caps);


/**
 * @brief 分配具有给定功能的内存块。内存中的初始化值设置为零。
 *
 * 等效于libc-calloc（）的语义，用于功能感知内存。
 *
 * 在IDF中，“calloc（p）”等同于“heap_caps_alloc（p，MALLOC_CAP_8BIT）”。
 *
 * @param n    要分配的连续内存块数
 * @param size 要分配的内存块的大小（字节）
 * @param caps        MALLOC_CAP_*标志的位或，指示要返回的内存类型
 *
 * @return 指向成功时分配的内存的指针，失败时为NULL
 */
void *heap_caps_calloc(size_t n, size_t size, uint32_t caps);

/**
 * @brief 获取具有给定功能的所有区域的总大小
 *
 * 该函数获取所有能够分配给定功能的区域，并将它们的总空间相加。
 *
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 *
 * @return 总大小（字节）
 */

size_t heap_caps_get_total_size(uint32_t caps);

/**
 * @brief 获取具有给定功能的所有区域的总可用大小
 *
 * 此函数获取所有能够分配给定功能的区域，并将它们的可用空间相加。
 *
 * 请注意，由于堆碎片，可能不可能分配此大小的单个内存块。为此，请使用heap_caps_get_largest_free_block（）。

 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 *
 * @return 区域中的可用字节数
 */
size_t heap_caps_get_free_size( uint32_t caps );


/**
 * @brief 获取具有给定功能的所有区域的总最小可用内存
 *
 * 这增加了能够以给定能力提供内存的区域的所有低水位标记。
 *
 * 请注意，由于每个区域都会追踪到“低水位标记”，因此结果可能小于全球历史上此类可用堆的最小值。个别地区的堆积物可能在不同时间点达到了“低水位”。然而，这个结果仍然给出了历史最小空闲堆的“最坏情况”指示。
 *
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 *
 * @return 区域中的可用字节数
 */
size_t heap_caps_get_minimum_free_size( uint32_t caps );

/**
 * @brief 获取可用给定功能分配的最大可用内存块。
 *
 * 返回“s”的最大值，“heap_caps_malloc（s，caps）”将成功。
 *
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 *
 * @return 最大可用块的大小（字节）。
 */
size_t heap_caps_get_largest_free_block( uint32_t caps );


/**
 * @brief 获取具有给定功能的所有区域的堆信息。
 *
 * 对共享给定功能的所有堆调用multi_heap_info（）。返回的信息是所有匹配堆的聚合。字段的含义与为multi_heap_info_t定义的含义相同，只是“minimum_free_bytes”具有heap_caps_get_minimum_free_size（）中描述的相同警告。
 *
 * @param info        指向将填充相关堆元数据的结构的指针。
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 *
 */
void heap_caps_get_info( multi_heap_info_t *info, uint32_t caps );


/**
 * @brief 打印具有给定功能的所有内存的摘要。
 *
 * 在共享给定功能的所有堆上调用multi_heap_info，并为每个堆打印两行摘要，然后打印总摘要。
 *
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 *
 */
void heap_caps_print_heap_info( uint32_t caps );

/**
 * @brief 检查系统中所有堆内存的完整性。
 *
 * 对所有堆调用multi_heap_check。如果堆损坏，可以选择打印错误。
 *
 * 调用此函数相当于在caps参数设置为MALLOC_CAP_INVALID的情况下调用heap_caps_check_integrity。
 *
 * @param print_errors 如果发现堆损坏，则打印特定错误。
 *
 * @return 如果所有堆都有效，则为True；如果至少有一个堆损坏，则为False。
 */
bool heap_caps_check_integrity_all(bool print_errors);

/**
 * @brief 检查具有给定功能的所有堆的完整性。
 *
 * 对共享给定功能的所有堆调用multi_heap_check。如果堆损坏，可以选择打印错误。
 *
 * 另请参见heap_caps_check_integrity_all以检查系统中的所有堆内存，heap_cap_check_integrity_Adr以检查单个地址周围的内存。
 *
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 * @param print_errors 如果发现堆损坏，则打印特定错误。
 *
 * @return 如果所有堆都有效，则为True；如果至少有一个堆损坏，则为False。
 */
bool heap_caps_check_integrity(uint32_t caps, bool print_errors);

/**
 * @brief 检查给定地址周围堆内存的完整性。
 *
 * 此函数可用于检查包含给定地址的单个堆内存区域的完整性。
 *
 * 如果在已知地址处调试堆完整性以防止损坏，这可能很有用，因为它比检查所有堆区域开销更低。请注意，如果损坏的地址在两次运行之间来回移动（由于时间或其他因素），那么这种方法将不起作用，您应该调用heap_caps_check_integrity或heap_cap_check_integrity_all。
 *
 * @note 检查地址周围的整个堆区域，而不仅仅是相邻的堆块。
 *
 * @param addr 内存中的地址。检查包含此地址的区域是否损坏。
 * @param print_errors 如果发现堆损坏，则打印特定错误。
 *
 * @return 如果包含指定地址的堆有效，则为True；如果至少有一个堆损坏或地址不属于堆区域，则为False。
 */
bool heap_caps_check_integrity_addr(intptr_t addr, bool print_errors);

/**
 * @brief 在外部内存中启用malloc（），并设置在内部内存中尝试malloc的限制。
 *
 * 当使用外部内存时，分配策略是首先尝试用内部内存满足较小的分配请求，用外部内存满足较大的分配请求。这设置了两者之间的限制，并且通常允许在外部内存中进行分配。
 *
 * @param limit       限制，以字节为单位。
 */
void heap_caps_malloc_extmem_enable(size_t limit);

/**
 * @brief 按降序分配一块内存作为首选项。
 *
 * @attention 变量参数是指示内存类型的MALLOC_CAP_*标志的位或。此API倾向于使用第一个参数分配内存。如果失败，请使用下一个参数分配内存。它将按此顺序尝试，直到成功分配内存块，或者无法使用任何参数分配内存。
 *
 * @param size 要分配的内存量的大小（字节）
 * @param num 变量参数数
 *
 * @return 指向成功时分配的内存的指针，失败时为NULL
 */
void *heap_caps_malloc_prefer( size_t size, size_t num, ... );

/**
 * @brief 按降序分配一块内存作为首选项。
 *
 * @param ptr 指向先前分配的内存的指针，或新分配的NULL。
 * @param size 请求的新缓冲区大小，或0释放缓冲区。
 * @param num 变量参数数
 *
 * @return 指向大小为“size”的新缓冲区的指针，如果分配失败，则为NULL。
 */
void *heap_caps_realloc_prefer( void *ptr, size_t size, size_t num, ... );

/**
 * @brief 按降序分配一块内存作为首选项。
 *
 * @param n    要分配的连续内存块数
 * @param size 要分配的内存块的大小（字节）
 * @param num  变量参数数
 *
 * @return 指向成功时分配的内存的指针，失败时为NULL
 */
void *heap_caps_calloc_prefer( size_t n, size_t size, size_t num, ... );

/**
 * @brief 转储具有匹配功能的所有堆的完整结构。
 *
 * 将大量输出打印为串行（由于锁定限制，输出绕过stdout/stderr）。对于每个匹配堆中的每个（可变大小）块，以下输出打印在单行上：
 *
 * -块地址（如果堆调试设置为Basic，则malloc返回的数据缓冲区在此之后为4字节，否则为8字节）。
 * -数据大小（由于堆碎片或由于堆调试级别，数据大小可能大于malloc请求的大小）。
 * -堆中下一个块的地址。
 * -如果该块空闲，则还将打印下一个空闲块的地址。
 *
 * @param caps        MALLOC_CAP_*标志的位“或”表示内存类型
 */
void heap_caps_dump(uint32_t caps);

/**
 * @brief 转储所有堆的完整结构。
 *
 * 覆盖所有注册的堆。将大量输出打印为串行。
 *
 * 输出与heap_caps_dump的输出相同。
 *
 */
void heap_caps_dump_all(void);

/**
 * @brief 返回分配给特定指针的大小。
 *
 * @param ptr 指向当前分配的堆内存的指针。必须是heap_caps_malloc、malloc和calloc等先前返回的指针值，但尚未释放。
 *
 * @note 如果指针无效，应用程序将因断言失败而崩溃。
 *
 * @return 此块分配的内存大小。
 *
 */
size_t heap_caps_get_allocated_size( void *ptr );

#ifdef __cplusplus
}
#endif

