// 版权所有（c）2013年，加州大学（Regents）校长。
// 版权所有（c）2018-2019，libfemto作者
// 版权所有（c）2020 Espressif Systems（上海）私人有限公司
// 保留所有权利。

// 以源代码和二进制形式重新分发和使用，无论有无
// 如果满足以下条件，则允许进行修改：
// 1.源代码的重新分发必须保留上述版权
//    注意，此条件列表和以下免责声明。
// 2.二进制形式的再发行必须复制上述版权
//    注意，此条件列表和以下免责声明
//    文件和/或分发时提供的其他材料。
// 3.无论是摄政者的名字还是
//    其贡献者的姓名可用于支持或推广产品
//    未经事先书面许可，从本软件派生。

// IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
// OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
// HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
// MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/param.h>
#include "encoding.h"

/********************************************************
 物理内存保护（PMP）寄存器字段（特权规范）
 ********************************************************/

/* pmpcfg0 CSR的值。请注意，此宏仅用于（CSR_PMPCFG0+1）等计算，在编译时必须保持不变。在其他情况下，请使用汇编器名称pmpcfg0、pmpcfg1、pmpcfg2等*/
#define CSR_PMPCFG0 0x3A0

/* pmpaddr0 CSR的值。注意，如上所述，此宏仅用于计算，否则应使用汇编器名称pmpaddr0、pmpaddr1、pmpadder2等。*/
#define CSR_PMPADDR0 0x3B0

/* PMPCFG时生成PMP地址字段值。A==餐巾

   开始和结束应在编译时计算。区域的大小（END-START）必须是2的幂，START必须与此大小对齐。

   注意：写入PMDDR寄存器时，此值必须右移PMP_SHIFT。PMP_ENTRY_SET宏将执行此操作。
 */
#define PMPADDR_NAPOT(START, END) ({                                    \
            _Static_assert(__builtin_popcount((END)-(START)) == 1, "Size must be a power of 2"); \
            _Static_assert((START) % ((END)-(START)) == 0, "Start must be aligned to size"); \
            (((START)) | (((END)-(START)-1)>>1));                       \
        })

#define PMPADDR_ALL 0xFFFFFFFF


/* 设置PMP条目。

   -ENTRY是要设置的PMP条目的编号。这必须是编译时间常数，因为它用于生成特定的程序集指令。
   -ADDR是写入PMPADDRx寄存器的地址。请注意，这是未移位的地址。
   -CFG是写入正确CFG条目寄存器的配置值。请注意，宏只设置CFG寄存器中的位，因此它应该已经归零。
*/
#define PMP_ENTRY_SET(ENTRY, ADDR, CFG) do {  \
    RV_WRITE_CSR((CSR_PMPADDR0) + (ENTRY), (ADDR) >> (PMP_SHIFT));    \
    RV_SET_CSR((CSR_PMPCFG0) + (ENTRY)/4, ((CFG)&0xFF) << (ENTRY%4)*8); \
    } while(0)

/********************************************************
   触发器模块寄存器字段（调试规范）
 ********************************************************/

/* t刀具链当前无法识别控制CSR*/
#define CSR_TCONTROL        0x7a5
#define CSR_TDATA1          0x7a1

#define TCONTROL_MTE     (1<<3)    /*R/W，当前M模式触发启用位*/
#define TCONTROL_MPTE    (1<<7)    /*R/W，前M模式触发启用位*/

#define TDATA1_LOAD      (1<<0)  /*R/W，加载地址匹配时触发*/
#define TDATA1_STORE     (1<<1)  /*R/W，商店地址垫上的火灾触发器*/
#define TDATA1_EXECUTE   (1<<2)  /*R/W，指令获取地址匹配时触发*/
#define TDATA1_USER      (1<<3)  /*R/W，允许在用户模式下触发*/
#define TDATA1_MACHINE   (1<<6)  /*R/W，允许在hart以机器模式执行时触发触发器*/
#define TDATA1_MATCH     (1<<7)
#define TDATA1_MATCH_V   (0xF)   /*R/W，地址匹配类型：0：精确字节匹配1：NAPOT范围匹配*/
#define TDATA1_MATCH_S   (7)


/* RISC-V CSR宏改编自https://github.com/michaeljclark/riscv-probe/blob/master/libfemto/include/arch/riscv/machine.h
 */

#define RV_READ_CONST_CSR(reg) ({ unsigned long __tmp; \
  asm ("csrr %0, " _CSR_STRINGIFY(reg) : "=r"(__tmp)); __tmp; })

#define RV_READ_CSR(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " _CSR_STRINGIFY(reg) : "=r"(__tmp)); __tmp; })

#define RV_WRITE_CSR(reg, val) ({ \
  asm volatile ("csrw " _CSR_STRINGIFY(reg) ", %0" :: "rK"(val)); })

#define RV_SWAP_CSR(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " _CSR_STRINGIFY(reg) ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })

/* 注意：这使用原子读取和设置指令，因此可以读取旧的CSR值*/
#define RV_SET_CSR(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " _CSR_STRINGIFY(reg) ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

/* 注意：这使用原子读取和清除指令，因此可以读取旧的CSR值*/
#define RV_CLEAR_CSR(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " _CSR_STRINGIFY(reg) ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

#define RV_SET_CSR_FIELD(_r, _f, _v) ({ (RV_WRITE_CSR((_r),((RV_READ_CSR(_r) & ~((_f##_V) << (_f##_S)))|(((_v) & (_f##_V))<<(_f##_S)))));})
#define RV_CLEAR_CSR_FIELD(_r, _f) ({ (RV_WRITE_CSR((_r),(RV_READ_CSR(_r) & ~((_f##_V) << (_f##_S)))));})

#define _CSR_STRINGIFY(REG) #REG /* 需要，所以“reg”参数可以是宏或寄存器名*/

#ifdef __cplusplus
}
#endif

