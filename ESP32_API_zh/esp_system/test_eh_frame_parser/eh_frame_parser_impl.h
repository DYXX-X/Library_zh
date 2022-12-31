
// 版权所有2020 Espressif Systems（上海）私人有限公司
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

/**
 * @file DWARF异常帧解析器头
 *
 * 此文件描述了解析“eh_frame”和“eh_fframe_hdr”所需的x86帧类型。
 */

#ifndef EH_FRAME_PARSER_IMPL_H
#define EH_FRAME_PARSER_IMPL_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief ExecutionFrame结构中的寄存器数。
 */
#define EXECUTION_FRAME_MAX_REGS   (11)

/**
 * @brief x86 DWARF tegisters集的定义。以下寄存器顺序取自GCC的“i386.c”文件：
 */
typedef struct x86ExcFrame
{
    union {
        struct {
            uint32_t eax;
            uint32_t ecx;
            uint32_t edx;
            uint32_t ebx;
            uint32_t esp;
            uint32_t ebp;
            uint32_t esi;
            uint32_t edi;
            uint32_t eip;
            uint32_t eflags;
            uint32_t trapno;
        };
        uint32_t registers[EXECUTION_FRAME_MAX_REGS];
    };
} x86ExcFrame;

/**
 * @brief 为此实现将Executionframe定义为RvExcFrame。
 */
typedef x86ExcFrame ExecutionFrame;

/**
 * @brief 参考执行帧的PC寄存器
 */
#define EXECUTION_FRAME_PC(struct)  ((struct).eip)

/**
 * @brief 参考执行帧的SP寄存器
 */
#define EXECUTION_FRAME_SP(struct)  ((struct).esp)

/**
 * @brief 执行帧中SP寄存器的索引。
 */
#define EXECUTION_FRAME_SP_REG      (offsetof(x86ExcFrame, esp)/sizeof(uint32_t))

/**
 * @brief 获取执行帧的寄存器i
 */
#define EXECUTION_FRAME_REG(frame, i) ((frame)->registers[(i)])

#endif // _EH_FRAME_PARSER_IMPL_H

