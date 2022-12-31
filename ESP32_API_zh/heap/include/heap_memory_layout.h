// 版权所有2010-2016 Espressif Systems（上海）私人有限公司
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
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "sdkconfig.h"

#define SOC_MEMORY_TYPE_NO_PRIOS 3

#ifdef __cplusplus
extern "C" {
#endif

/* 类型描述符保存特定SoC上特定类型存储器的描述。
 */
typedef struct {
    const char *name;  ///<此内存类型的名称
    uint32_t caps[SOC_MEMORY_TYPE_NO_PRIOS]; ///<此内存类型的功能（作为优先级集）
    bool aliased_iram;   ///<如果为真，则这是IRAM中也映射的数据存储器
    bool startup_stack; ///<如果为true，则在启动期间，此类型的内存用于ROM堆栈
} soc_memory_type_desc_t;

/* 所有SoC标签的标签描述符常量表*/
extern const soc_memory_type_desc_t soc_memory_types[];
extern const size_t soc_memory_type_count;

/* 区域描述符保存特定SoC上特定存储器区域的描述。
 */
typedef struct {
    intptr_t start;  ///<区域的起始地址
    size_t size;            ///<区域大小（字节）
    size_t type;             ///<区域的类型（索引到soc_memory_types数组中）
    intptr_t iram_address; ///<如果非零，则为IRAM中的等效地址
} soc_memory_region_t;

extern const soc_memory_region_t soc_memory_regions[];
extern const size_t soc_memory_region_count;

/* 区域描述符保存此SoC上为特定用途保留的特定内存区域的描述（即不可用于堆栈/堆使用）*/
typedef struct {
    intptr_t start;
    intptr_t end;
} soc_reserved_region_t;

/* 使用此宏为特定目的保留固定的RAM区域（硬编码地址）。
 *
 * 通常用于标记硬件或ROM代码所需的内存地址。
 *
 * 不要从可以使用普通C静态分配的用户代码调用此宏。
 *
 * @param START 要保留的起始地址。
 * @param END 一个在要保留的最后一个字节的地址之后。（即保留区域的长度为（END-START）字节。
 * @param NAME 保留区域的名称。必须是此源文件唯一的有效变量名。
 */
#define SOC_RESERVE_MEMORY_REGION(START, END, NAME)     \
    __attribute__((section(".reserved_memory_address"))) __attribute__((used)) \
    static soc_reserved_region_t reserved_region_##NAME = { START, END };

/* 返回此SoC的可用内存区域。每个可用内存区域都是一块连续的内存，不被静态数据使用，不被ROM代码使用，也不被使用SoC_RESERVE_memory_region（）宏的组件保留。
 *
 * 此结果是soc_memory_regions[]减去通过soc_RESERVE_memory_REGION（）宏保留的所有区域（这也可能会拆分一些区域）
 *
 * 启动时，此函数返回的所有可用内存都注册为堆空间。
 *
 * @note 仅限OS级启动功能，不建议从应用程序代码调用。
 *
 * @param regions 指向用于将可用区域读入的数组的指针。数组的大小至少应为soc_get_available_memory_region_max_count（）的结果。数组中的条目将按内存地址排序。
 *
 * @return 复制到“区域”的条目数。将不大于soc_get_available_memory_region_max_count（）的结果。
 */
size_t soc_get_available_memory_regions(soc_memory_region_t *regions);

/* 返回soc_get_available_memory_regions（）可以返回的最大可用内存区域数。用于调整传递给该函数的数组的大小。
 */
size_t soc_get_available_memory_region_max_count(void);


#ifdef __cplusplus
}
#endif

