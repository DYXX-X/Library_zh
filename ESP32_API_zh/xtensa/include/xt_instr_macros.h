// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#define RSR(reg, at)         asm volatile ("rsr %0, %1" : "=r" (at) : "i" (reg))
#define WSR(reg, at)         asm volatile ("wsr %0, %1" : : "r" (at), "i" (reg))
#define XSR(reg, at)         asm volatile ("xsr %0, %1" : "+r" (at) : "i" (reg))

#define RER(reg, at)         asm volatile ("rer %0, %1" : "=r" (at) : "r" (reg))

#define WITLB(at, as)        asm volatile ("witlb  %0, %1; \n isync \n " : : "r" (at), "r" (as))
#define WDTLB(at, as)        asm volatile ("wdtlb  %0, %1; \n dsync \n " : : "r" (at), "r" (as))

/* SET_STACK实现了对新堆栈指针（sp或a1）的设置。为此，需要重置PS_WOE、重置WINDOWSTART、更新SP并返回PS_WOE。
 *
 * 注意：它有两个实现，一个用于汇编程序文件（*.S），另一个用于C。
 *
 * SET_STACK的C代码原型：uint32_t ps_reg；uint32_t w_base；RSR（PS，PS_reg）；ps_reg&=~（ps_WOE_MASK|ps_OWB_MASK| ps_CALLINC_MASK）；WSR（PS，PS_reg）；
 *
 *   RSR（挡风玻璃，w_base）；WSR（Windows启动，（1<<w_base））；
 *
 *   asm易失性（“movi sp，”XTSTR（（SOC_DRAM_LOW+（SOC_DRAM_HIGH-SOC_DRAM-LOW）/2）“）”）；
 *
 *   RSR（PS，PS_reg）；ps_reg |=（ps_WOE_MASK）；WSR（PS，PS_reg）；
*/
#ifdef __ASSEMBLER__
    .macro SET_STACK  new_sp tmp1 tmp2
    rsr.ps \tmp1
    movi \tmp2, ~(PS_WOE_MASK | PS_OWB_MASK | PS_CALLINC_MASK)
    and \tmp1, \tmp1, \tmp2
    wsr.ps \tmp1
    rsync

    rsr.windowbase \tmp1
    ssl	\tmp1
    movi \tmp1, 1
    sll	\tmp1, \tmp1
    wsr.windowstart \tmp1
    rsync

    mov sp, \new_sp

    rsr.ps \tmp1
    movi \tmp2, (PS_WOE)
    or \tmp1, \tmp1, \tmp2
    wsr.ps \tmp1
    rsync
    .endm
#else
#define SET_STACK(new_sp) \
    do { \
        uint32_t tmp1 = 0, tmp2 = 0; \
        asm volatile ( \
          "rsr.ps %1 \n"\
          "movi %2, ~" XTSTR( PS_WOE_MASK | PS_OWB_MASK | PS_CALLINC_MASK ) " \n"\
          "and %1, %1, %2 \n"\
          "wsr.ps %1 \n"\
          "rsync \n"\
          " \n"\
          "rsr.windowbase %1 \n"\
          "ssl	%1 \n"\
          "movi %1, 1 \n"\
          "sll	%1, %1 \n"\
          "wsr.windowstart %1 \n"\
          "rsync \n"\
          " \n"\
          "mov sp, %0 \n"\
          "rsr.ps %1 \n"\
          " \n"\
          "movi %2, " XTSTR( PS_WOE_MASK ) "\n"\
          " \n"\
          "or %1, %1, %2 \n"\
          "wsr.ps %1 \n"\
          "rsync \n"\
          : "+r"(new_sp), "+r"(tmp1), "+r"(tmp2)); \
    } while (0);
#endif // __ASSEMBLER__

