// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#ifndef ESP_CORE_DUMP_PORT_IMPL_H_
#define ESP_CORE_DUMP_PORT_IMPL_H_

/**
 * @file
 * @brief RISC-V的核心转储端口接口实现。
 */

#include "esp_core_dump_types.h"
#include "esp_app_format.h"

/**
 * @brief 与此实现相关的芯片ID。
 */
#define COREDUMP_VERSION_CHIP ESP_CHIP_ID_ESP32C3

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 将堆栈指针设置为作为参数传递的地址。
 * @note 此函数必须内联。
 *
 * @param new_sp 要在sp寄存器中设置的新堆栈指针。
 *
 * @return 前堆栈指针地址（sp寄存器值）。
 */
FORCE_INLINE_ATTR void* esp_core_dump_replace_sp(void* new_sp)
{
    void* current_sp = NULL;
    asm volatile ("mv %0, sp \n\t\
                   mv sp, %1 \n\t\
                  "
                   : "=&r"(current_sp)
                   : "r"(new_sp));
    return current_sp;
}

#ifdef __cplusplus
}
#endif

#endif

