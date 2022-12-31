// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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
#include "sdkconfig.h"
#include <stdint.h>
#include <xtensa/config/core-isa.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF

#define EPCx_REGISTER_COUNT XCHAL_NUM_INTLEVELS

/**
 * @brief 回溯信息。
 *
 * 对于Xtensa，由于窗口寄存器ABI，可以在设备上生成回溯。
 */
typedef struct {
    uint32_t bt[16];        /*!< 回溯（PC阵列）*/
    uint32_t depth;         /*!< 回溯条目数*/
    bool corrupted;         /*!< 回溯的状态标志是否损坏*/
} esp_core_dump_bt_info_t;

/**
 * @brief Xtensa体系结构特定的额外信息
 */
typedef struct {
    uint32_t exc_cause;                 /*!< 异常原因*/
    uint32_t exc_vaddr;                 /*!< 异常的虚拟地址*/
    uint32_t exc_a[16];                 /*!< 发生异常时设置的寄存器*/
    uint32_t epcx[EPCx_REGISTER_COUNT]; /*!< 异常级别的PC寄存器地址（1至7）*/
    uint8_t epcx_reg_bits;              /*!< 可用EPCx寄存器的位掩码*/
} esp_core_dump_summary_extra_info_t;

#endif /* CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF */

#ifdef __cplusplus
}
#endif

