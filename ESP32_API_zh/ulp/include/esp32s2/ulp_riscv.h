// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "esp_err.h"
#include "soc/soc.h"
#include "ulp_common.h"

/**
 * @brief 运行加载到RTC内存中的程序
 * @return  成功时ESP_OK
 */
esp_err_t ulp_riscv_run(void);

/**
 * @brief 将ULP-RISC-V程序二进制文件加载到RTC内存中
 *
 * 与ULP FSM不同，二进制程序没有特殊格式，它是RISC-V工具链生成的ELF文件，使用objcopy转换为二进制格式。
 *
 * components/ulp/ld/esp32s2.ulp.riscv中的链接器脚本。ld生成与此格式相对应的ELF文件。此链接器脚本生成load_addr==0的二进制文件。
 *
 * @param program_binary 程序二进制指针
 * @param program_size_bytes 程序二进制文件的大小
 * @return
 *      -成功时ESP_OK
 *      -如果program_SIZE_bytes大于8KiB，则为ESP_ERR_INVALID_SIZE
 */
esp_err_t ulp_riscv_load_binary(const uint8_t* program_binary, size_t program_size_bytes);

