
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
 * 该文件描述了RISC-V的帧类型，用于解析“eh_frame”和“eh_fframe_hdr”。
 *
 */

#ifndef EH_FRAME_PARSER_IMPL_H
#define EH_FRAME_PARSER_IMPL_H

#include "riscv/rvruntime-frames.h"

/**
 * @brief 为此实现将Executionframe定义为RvExcFrame。
 */
typedef RvExcFrame ExecutionFrame;

/**
 * @brief ExecutionFrame结构中的寄存器数。
 *
 * 这将用于定义和初始化DWARF机器状态。实际上，我们只有16个被调用方保存的寄存器，因此，我们只能保存它们并忽略其余的。然而，计算CPU寄存器到DWARF寄存器的映射的代码所需的时间将超过我们将保存的16个寄存器…所以，保存所有寄存器。
 */
#define EXECUTION_FRAME_MAX_REGS   (32)

/**
 * @brief 参考执行帧的PC寄存器。
 */
#define EXECUTION_FRAME_PC(frame)   ((frame).mepc)

/**
 * @brief 参考执行帧的SP寄存器。
 */
#define EXECUTION_FRAME_SP(frame)   ((frame).sp)

/**
 * @brief 执行帧中SP寄存器的索引。
 */
#define EXECUTION_FRAME_SP_REG      (offsetof(RvExcFrame, sp)/sizeof(uint32_t))

/**
 * @brief 获取执行帧的寄存器i。
 */
#define EXECUTION_FRAME_REG(frame, i) (((uint32_t*) (frame))[(i)])

#endif // _EH_FRAME_PARSER_IMPL_H

