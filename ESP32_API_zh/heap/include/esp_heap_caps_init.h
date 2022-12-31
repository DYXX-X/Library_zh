// 版权所有2017 Espressif Systems（上海）私人有限公司
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

#include "esp_err.h"
#include "esp_heap_caps.h"
#include "soc/soc_memory_layout.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化能力感知堆分配器。
 *
 * 这在IDF启动代码中调用一次。不要在其他时间拨打电话。
 */
void heap_caps_init(void);

/**
 * @brief 在启动堆栈所在的内存区域中启用堆。
 *
 * 在启动时，pro/app CPU有一个特定的内存区域用作堆栈，因此我们无法在这些堆栈帧所在的区域中进行分配。当FreeRTOS完全启动时，它们不再使用该内存，可以启用那里的堆。
 */
void heap_caps_enable_nonos_stack_heaps(void);

/**
 * @brief 在运行时向堆集合中添加内存区域。
 *
 * 大多数内存区域在soc_memory_layout中定义。c表示SoC，并通过heap_caps_init（）注册。某些区域无法立即使用，稍后将通过heap_caps_enable_nonos_stack_heaps（）启用。
 *
 * 稍后调用此函数将内存区域添加到堆中。
 *
 * 此函数不考虑soc_memory_layout中的任何“保留”区域或其他数据，调用者需要自己考虑。
 *
 * 由开始和结束参数指定的区域内的所有内存必须未使用。
 *
 * 新注册内存的容量将由起始地址决定，在soc_memory_layout.c中指定的区域中查找。
 *
 * 使用heap_caps_add_region_with_caps（）注册具有自定义功能的区域。
 *
 * @param start 新区域的起始地址。
 * @param end 新区域的结束地址。
 *
 * @return 成功时为ESP_OK，如果参数无效，则为ESP_ERR_INVALID_ARG，如果指定的起始地址不在已知区域中，则为ESP _ERR_NOT_FOUND，或heap_caps_add_region_with_caps（）返回的任何错误。
 */
esp_err_t heap_caps_add_region(intptr_t start, intptr_t end);


/**
 * @brief 使用自定义功能，在运行时向堆集合中添加内存区域。
 *
 * 与heap_caps_add_region（）类似，调用者只指定自定义内存功能。
 *
 * @param caps 按优先级顺序排列新区域的能力掩码。长度必须为SOC_MEMORY_TYPE_NO_PRIOS。在调用返回后不需要保持有效。
 * @param start 新区域的起始地址。
 * @param end 新区域的结束地址。
 *
 * @return
 *         -成功时ESP_OK
 *         -如果参数无效，则返回ESP_ERR_INVALID_ARG
 *         -如果没有内存注册新堆，则返回ESP_ERR_NO_MEM。
 *         -如果内存区域太小，无法容纳堆，则返回ESP_ERR_INVALID_SIZE
 *         -如果区域与现有区域的开始和/或结束重叠，则为ESP_FAIL
 */
esp_err_t heap_caps_add_region_with_caps(const uint32_t caps[], intptr_t start, intptr_t end);


#ifdef __cplusplus
}
#endif

