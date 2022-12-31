/*
 * 版权所有（c）2017，Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */

/* 版权所有2015-2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/* 适用于IDF FreeRTOS组件的文件，最初从zephyr RTOS代码库中提取：https://github.com/zephyrproject-rtos/zephyr/blob/dafd348/arch/xtensa/include/xtensa-asm2-s.h
 */

#ifndef __XT_ASM_UTILS_H
#define __XT_ASM_UTILS_H

/*
 * SPILL_ALL_WINDOWS
 *
 * 将所有窗口寄存器（即不可见的寄存器A0-A15）溢出到堆栈上ABI定义的溢出区域。
 *
 * 与Xtensa HAL实现不同，此代码要求在PS中启用EXCM和WOE位，并依赖于重复的硬件异常处理来执行寄存器溢出。诀窍是对高位寄存器进行noop写入，如果这些寄存器已经被现有的调用帧使用，则硬件将捕获（进入溢出异常）。然后它旋转窗口并重复，直到原始帧的A0-A3寄存器之外的所有寄存器都被保证溢出，最终旋转回到原始帧。优势：
 *
 * -大大减小了代码大小
 *
 * -如果需要更改窗口溢出/溢出异常处理，则更容易维护。
 *
 * -不需要临时寄存器来完成其工作，因此可以在任何环境中安全使用。
 *
 * -如果WOE位未启用（例如，在为CALL0ABI编写的代码中），这将成为一个无声的noop，并兼容操作。
 *
 * -有趣的是，它实际上比HAL程序快得多。而且不仅仅是一点点，它要快得多。在LX6内核（ESP-32）上有一个基本上满的寄存器文件，我测量了145个周期来溢出寄存器，而不是279个（！）使用xthal_spill_windows（）执行此操作。
 */

.macro SPILL_ALL_WINDOWS
#if XCHAL_NUM_AREGS == 64
	and a12, a12, a12
	rotw 3
	and a12, a12, a12
	rotw 3
	and a12, a12, a12
	rotw 3
	and a12, a12, a12
	rotw 3
	and a12, a12, a12
	rotw 4
#elif XCHAL_NUM_AREGS == 32
	and a12, a12, a12
	rotw 3
	and a12, a12, a12
	rotw 3
	and a4, a4, a4
	rotw 2
#else
#error Unrecognized XCHAL_NUM_AREGS
#endif
.endm

#endif

