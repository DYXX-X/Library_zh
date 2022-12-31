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

#ifdef __cplusplus
extern "C"
{
#endif

#if CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF

/**
 * @brief 回溯信息
 *
 * 对于RISCV，如果不包含和解析DWARF部分，则无法在设备上生成回溯。包括这些部分将增加二进制文件的大小，因此提供堆栈转储，稍后可以在GDB的帮助下或通过解析主机上的ELF文件来生成回溯
 */
typedef struct {
    uint8_t stackdump[CONFIG_ESP_COREDUMP_SUMMARY_STACKDUMP_SIZE];    /*!< 崩溃任务的堆栈转储。*/
    uint32_t dump_size;                                               /*!< 堆栈转储的大小（字节）*/
} esp_core_dump_bt_info_t;

/**
 * @brief RISC-V体系结构特定的额外信息
 */
typedef struct {
    uint32_t mstatus;     /* 机器状态*/
    uint32_t mtvec;       /* 机器陷阱矢量基地址*/
    uint32_t mcause;      /* 机器陷阱原因*/
    uint32_t mtval;       /* 机器陷阱值*/
    uint32_t ra;          /* 返回地址*/
    uint32_t sp;          /* 堆栈指针*/
    uint32_t exc_a[8];    /* A0-A7寄存器（当异常发生时）*/
} esp_core_dump_summary_extra_info_t;

#endif /* CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF */

#ifdef __cplusplus
}
#endif

