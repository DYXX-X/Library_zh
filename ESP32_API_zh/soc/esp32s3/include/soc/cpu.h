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
#include <stdbool.h>
#include <stddef.h>
#include "xtensa/corebits.h"

/* 用于extensa特殊寄存器读/写/交换的C宏*/

#define RSR(reg, curval)  asm volatile ("rsr %0, " #reg : "=r" (curval));
#define WSR(reg, newval)  asm volatile ("wsr %0, " #reg : : "r" (newval));
#define XSR(reg, swapval) asm volatile ("xsr %0, " #reg : "+r" (swapval));

/** @brief 读取当前堆栈指针地址
 *
 */
static inline void *get_sp(void)
{
    void *sp;
    asm volatile ("mov %0, sp;" : "=r" (sp));
    return sp;
}

/* 为CPU中的“区域保护”选项设置页面属性的功能。有关参数的解释，请参见Xtensa ISA参考手册（第4.6.3.2节）。
 */

static inline void cpu_write_dtlb(uint32_t vpn, unsigned attr)
{
    asm volatile ("wdtlb  %1, %0; dsync\n" :: "r" (vpn), "r" (attr));
}


static inline void cpu_write_itlb(unsigned vpn, unsigned attr)
{
    asm volatile ("witlb  %1, %0; isync\n" :: "r" (vpn), "r" (attr));
}

/**
 * @brief 配置内存区域保护
 *
 * 使页面0访问引发异常。还要保护一些其他未使用的页面，这样我们就可以捕捉到奇怪之处。有用的属性值：0-缓存，RW 2-绕过缓存，RWX（CPU重置后的默认值）15-无访问，引发异常
 */

static inline void cpu_configure_region_protection(void)
{
    const uint32_t pages_to_protect[] = {0x00000000, 0x80000000, 0xa0000000, 0xc0000000, 0xe0000000};
    for (int i = 0; i < sizeof(pages_to_protect) / sizeof(pages_to_protect[0]); ++i) {
        cpu_write_dtlb(pages_to_protect[i], 0xf);
        cpu_write_itlb(pages_to_protect[i], 0xf);
    }
    cpu_write_dtlb(0x20000000, 0);
    cpu_write_itlb(0x20000000, 0);
}

/**
 * @brief 使用RTC控制器暂停CPU
 * @param cpu_id 要暂停的CPU ID（0=PRO，1=APP）
 */
void esp_cpu_stall(int cpu_id);

/**
 * @brief 使用RTC控制器卸载CPU
 * @param cpu_id 要卸载的CPU ID（0=PRO，1=APP）
 */
void esp_cpu_unstall(int cpu_id);

/**
 * @brief 使用RTC控制器重置CPU
 * @param cpu_id 要重置的CPU ID（0=PRO，1=APP）
 */
void esp_cpu_reset(int cpu_id);


/**
 * @brief 如果JTAG调试器连接到CPU OCD（片上调试）端口，则返回true。
 *
 * @note 如果禁用“使异常和恐慌处理程序JTAG/OCD感知”，则此函数始终返回false。
 */
bool esp_cpu_in_ocd_debug_mode(void);

/**
 * @brief 将PC寄存器值转换为其真实地址
 *
 * 当前指令的地址未作为精确的uint32_t表示形式存储在PC寄存器中。此函数将存储在PC寄存器中的值转换为uint32_t地址。
 *
 * @param pc_raw 以寄存器格式存储的PC。
 *
 * @return uint32_t格式的地址
 */
static inline uint32_t esp_cpu_process_stack_pc(uint32_t pc)
{
    if (pc & 0x80000000) {
        //a0（返回地址）的前两位指定窗口增量。覆盖以映射到地址空间。
        pc = (pc & 0x3fffffff) | 0x40000000;
    }
    //减3以获得前一条指令的PC（即在返回地址之前执行的指令）
    return pc - 3;
}

typedef uint32_t esp_cpu_ccount_t;

static inline esp_cpu_ccount_t esp_cpu_get_ccount(void)
{
    uint32_t result;
    RSR(CCOUNT, result);
    return result;
}

