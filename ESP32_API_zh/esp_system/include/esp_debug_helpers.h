// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include "esp_err.h"
#include "soc/soc.h"  // 〔重构todo〕IDF-2297
#include "esp_cpu.h"

/*
 * @brief   用于回溯的结构
 *
 * 该结构存储特定堆栈帧（即PC和SP）的回溯信息。该结构与esp_cpu_get_next_backtrace_frame（）函数一起迭代使用，以遍历单个堆栈中的每个帧。next_pc表示当前帧调用方的pc，因此next_pc为0表示当前帧是堆栈上的最后一帧。
 *
 * @note    调用esp_backtrace_get_start（）获取此结构的初始化值
 */
typedef struct {
    uint32_t pc;       /* 当前帧的PC*/
    uint32_t sp;       /* 当前帧的SP*/
    uint32_t next_pc;  /* 当前帧呼叫方的PC*/
    const void *exc_frame;  /* 指向全帧数据结构的指针（如果适用）*/
} esp_backtrace_frame_t;

/**
 * @brief 如果OCD通过JTAG连接。将断点0设置为给定的函数地址。不要做其他事情。
 * @param fn  指向目标断点位置的指针
 */
void esp_set_breakpoint_if_jtag(void *fn);

/**
 * 获取当前堆栈回溯的第一帧
 *
 * 给定以下函数调用流（B->A->X->esp_backtrace_get_start），此函数将执行以下操作。
 * -将CPU寄存器和窗口帧刷新到当前堆栈
 * -返回函数A的PC和SP（即堆栈回溯的开始）
 * -返回功能B的PC（即next_PC）
 *
 * @note 此函数在程序集中实现
 *
 * @param[out] pc       回溯中第一帧的PC
 * @param[out] sp       回溯中第一帧的SP
 * @param[out] next_pc  第一帧呼叫方的PC
 */
extern void esp_backtrace_get_start(uint32_t *pc, uint32_t *sp, uint32_t *next_pc);

/**
 * 获取堆栈上的下一帧以进行回溯
 *
 * 给定堆栈帧（i），此函数将获得同一调用堆栈（即帧（i的调用方）上的下一个堆栈帧（i-1）。在执行回溯时，该函数将被迭代调用。
 *
 * 进入条件：包含有效SP和next_pc退出条件的框架结构：
 *  -用帧（i-1）的SP和PC更新帧结构。next_pc现在指向帧（i-2）。
 *  -如果返回的next_pc为0，则表示帧（i-1）是堆栈上的最后一帧
 *
 * @param[inout] frame  指向框架结构的指针
 *
 * @return
 *  -如果下一帧（i-1）的SP和PC正常，则为True
 *  -否则为False
 */
bool esp_backtrace_get_next_frame(esp_backtrace_frame_t *frame);

/**
 * @brief 打印指定帧的回溯。
 *
 * @param depth 要打印的最大堆栈帧数（应大于0）
 * @param frame 要打印的起始帧
 * @param panic 指示系统死机期间是否存在回溯打印
 *
 * @note 在ESP32上，用户必须首先调用esp_backtrace_get_start（）来刷新堆栈。
 * @note 如果通过从某个示例函数func_a（）调用esp_backtrace_get_start（）获得esp_backtrace_frame_t*帧，则该帧仅在func_a的帧/范围内有效。用户不应试图在不同堆栈的同一堆栈中传递/使用其他帧。
 *
 * @return
 *      -ESP_OK回溯已成功打印到完成或深度限制
 *      -ESP_FAIL回溯已损坏
 */
esp_err_t IRAM_ATTR esp_backtrace_print_from_frame(int depth, const esp_backtrace_frame_t* frame, bool panic);

/**
 * @brief 打印当前堆栈的回溯
 *
 * @param depth 要打印的最大堆栈帧数（应大于0）
 *
 * @return
 *      -ESP_OK回溯已成功打印到完成或深度限制
 *      -ESP_FAIL回溯已损坏
 */
esp_err_t esp_backtrace_print(int depth);

/**
 * @brief 设置一个观察点，以在访问特定内存范围时中断/死机。在esp_cpu.h中被esp_cpu_set_watchpoint取代。
 */
static inline __attribute__((deprecated)) esp_err_t esp_set_watchpoint(int no, void *adr, int size, int flags)
{
    return esp_cpu_set_watchpoint(no, adr, size, flags);
}

/**
 * @brief 设置一个观察点，以在访问特定内存范围时中断/死机。在esp_cpu.h中被esp_cpu_clear_watchpoint取代。
 */
static inline __attribute__((deprecated)) void esp_clear_watchpoint(int no)
{
    esp_cpu_clear_watchpoint(no);
}

#endif
#ifdef __cplusplus
}
#endif

