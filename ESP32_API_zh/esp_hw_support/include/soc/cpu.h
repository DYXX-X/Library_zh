/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _SOC_CPU_H
#define _SOC_CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "esp_cpu.h"

#if __XTENSA__
#include "xt_instr_macros.h"
// [重构todo]现在实际上不需要在这个头中，
// 但保持兼容性
#include "xtensa/corebits.h"
#include "xtensa/config/core.h"

#include "xtensa/config/specreg.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 读取当前堆栈指针地址。在esp_cpu.h中被esp_cpu_get_sp取代。
 */
static inline __attribute__((deprecated)) void *get_sp(void)
{
    return esp_cpu_get_sp();
}

static inline uint32_t esp_cpu_process_stack_pc(uint32_t pc)
{
    if (pc & 0x80000000) {
        //a0（返回地址）的前两位指定窗口增量。覆盖以映射到地址空间。
        pc = (pc & 0x3fffffff) | 0x40000000;
    }
    //减3以获得前一条指令的PC（即在返回地址之前执行的指令）
    return pc - 3;
}

/**
 * @brief 配置CPU以禁用对无效内存区域的访问
 *
 */
void esp_cpu_configure_region_protection(void);

#ifdef __cplusplus
}
#endif

#endif

