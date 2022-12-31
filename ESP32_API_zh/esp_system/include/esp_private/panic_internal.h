// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#include <stdint.h>
#include <stdbool.h>

#include "soc/soc_caps.h"

#include "sdkconfig.h"


#ifdef __cplusplus
extern "C" {
#endif

extern bool g_panic_abort;

extern void *g_exc_frames[SOC_CPU_CORES_NUM];

// 打印更多信息（如详细信息）的功能
// 和panic_info_t的回溯字段。这些功能应限制其自身
// 打印到控制台，并且应该进行其他更复杂的处理，
// 并且必须意识到恐慌的主要逻辑。c具有激活的看门狗定时器。
typedef void (*panic_info_dump_fn_t)(const void* frame);

// 非体系结构特定异常（通常适用于所有目标）。
// 可用于向主逻辑传达发生了什么异常
// 在不了解潜在原因的情况下执行某些操作
// 架构/芯片特定异常。
typedef enum {
    PANIC_EXCEPTION_DEBUG,
    PANIC_EXCEPTION_IWDT,
    PANIC_EXCEPTION_TWDT,
    PANIC_EXCEPTION_ABORT,
    PANIC_EXCEPTION_FAULT,                  // 对所有类型的故障进行全面检查
} panic_exception_t;

typedef struct {
    int core;                               // 引发恐慌的核心
    panic_exception_t exception;            // 非体系结构特定异常代码
    const char* reason;                     // 异常字符串
    const char* description;                // 异常的简短描述
    panic_info_dump_fn_t details;           // 有关异常的详细信息
    panic_info_dump_fn_t state;             // 处理器状态，通常是寄存器的内容
    const void* addr;                       // 触发异常的指令地址
    const void* frame;                      // 参考框架
    bool pseudo_excause;                    // 指示异常原因具有特殊含义的标志
} panic_info_t;

#define PANIC_INFO_DUMP(info, dump_fn)      {if ((info)->dump_fn) (*(info)->dump_fn)((info->frame));}

// 创建自己的打印函数，因为printf可能会被破坏，并且可以被静音
// 当CONFIG_ESP_SYSTEM_PANIC_SILENT_REBOOT
#if !CONFIG_ESP_SYSTEM_PANIC_SILENT_REBOOT
void panic_print_char(char c);
void panic_print_str(const char *str);
void panic_print_dec(int d);
void panic_print_hex(int h);
#else
#define panic_print_char(c)
#define panic_print_str(str)
#define panic_print_dec(d)
#define panic_print_hex(h)
#endif

void __attribute__((noreturn)) panic_abort(const char *details);

void panic_arch_fill_info(void *frame, panic_info_t *info);

void panic_soc_fill_info(void *frame, panic_info_t *info);

void panic_print_registers(const void *frame, int core);

void panic_print_backtrace(const void *frame, int core);

uint32_t panic_get_address(const void* frame);

void panic_set_address(void *frame, uint32_t addr);

uint32_t panic_get_cause(const void* frame);

#ifdef __cplusplus
}
#endif

