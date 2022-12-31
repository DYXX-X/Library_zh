/*******************************************************************************
//版权所有（c）2003-2015 Cadence Design Systems，Inc.////特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权限，包括//但不限于使用、复制、修改、合并、发布、//分发、再许可和/或销售软件副本的权利，和//允许向其提供软件的人员这样做，但须遵守以下conditions:////上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。////软件按“原样”提供，无任何明示或暗示的保证，包括但不限于适销性、适用于特定用途和非侵权性的保证。//在任何情况下，作者或版权持有人均不对因软件或软件的使用或其他交易而产生的任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权诉讼或其他诉讼中。
--------------------------------------------------------------------------------

        XTENSA RTOS汇编程序源的RTOS特定信息（FreeRTOS端口）

此标头是通用Xtensa RTOS支持源和Xtensa特定RTOS端口之间的主要粘合剂。它包含定义和宏，主要由Xtensa程序集编码的源文件使用。

此标题中的宏将通用Xtensa文件的标注映射到特定的RTOS函数。它也可以包含在C源文件中。

Xtensa RTOS端口支持Xtensa体系结构的所有RTOS兼容配置，使用Xtensa硬件抽象层（HAL）处理配置细节。

应包含在所有Xtensa通用和RTOS端口特定源中。

*******************************************************************************/

#ifndef XTENSA_RTOS_H
#define XTENSA_RTOS_H

#ifdef __ASSEMBLER__
#include    <xtensa/coreasm.h>
#else
#include    <xtensa/config/core.h>
#endif

#include    <xtensa/corebits.h>
#include    <xtensa/config/system.h>
#include    "sdkconfig.h"

/*
包括此标头所需的任何RTOS特定定义。
*/
#include    "freertos/FreeRTOSConfig.h"

/*
将FreeRTOSConfig定义转换为XTENSA定义。但是，这些仍然可以从命令行覆盖。
*/

#ifndef XT_SIMULATOR
  #if configXT_SIMULATOR
    #define XT_SIMULATOR             1  /* 模拟器模式*/
  #endif
#endif

#ifndef XT_BOARD
  #if configXT_BOARD
    #define XT_BOARD                 1  /* 板模式*/
  #endif
#endif

#ifndef XT_TIMER_INDEX
  #if defined configXT_TIMER_INDEX
    #define XT_TIMER_INDEX           configXT_TIMER_INDEX  /* 要使用的硬件计时器索引*/
  #endif
#endif

#ifndef XT_INTEXC_HOOKS
  #if configXT_INTEXC_HOOKS
    #define XT_INTEXC_HOOKS          1  /* 启用异常挂钩*/
  #endif
#endif

#if !defined(XT_SIMULATOR) && !defined(XT_BOARD)
  #error Either XT_SIMULATOR or XT_BOARD must be defined.
#endif


/*
RTOS的名称（用于消息）。
*/
#define XT_RTOS_NAME    FreeRTOS

/*
检查一些Xtensa配置要求，如果不满足，则报告错误。错误消息可以自定义到RTOS端口。
*/

#if !XCHAL_HAVE_XEA2
#error "FreeRTOS/Xtensa requires XEA2 (exception architecture 2)."
#endif


/*******************************************************************************
RTOS CALLOUT MACROS MAPPED TO RTOS PORT-SPECIFIC FUNCTIONS.

定义通用Xtensa代码中使用的调用宏，以与RTOS交互。宏只是用于汇编程序代码调用的函数名。其中一些函数可能会调用extensa_context中的泛型函数。h。

*******************************************************************************/

/*
通知RTOS进入会影响它的中断处理程序。允许RTOS管理切换到任何系统堆栈和计数嵌套级别。在保存了最小上下文并禁用中断后调用。RTOS端口可以调用_xt_context_save来保存其余的上下文。只能由“call0”指令从程序集代码调用。
*/
// 无效XT_RTOS_INT_ENTER（无效）
#define XT_RTOS_INT_ENTER   _frxt_int_enter

/*
通知RTOS中断处理程序的完成，并将控制权交给RTOS以执行线程/任务调度，从任何系统堆栈切换回并恢复上下文，并返回到保存在XT_STK_exit堆栈帧中的退出调度器。RTOS端口可以通过_xt_context_save调用0 _xt_context_restore来保存保存在xt_RTOS_INT_ENTER中的上下文，只留下一小部分上下文由exitdispatcher还原。此函数不会返回到调用它的位置。只能由“call0”指令从程序集代码调用。
*/
// 无效XT_RTOS_INT_EXIT（无效）
#define XT_RTOS_INT_EXIT    _frxt_int_exit

/*
通知RTOS发生滴答计时器中断。如果RTOS没有滴答计时器，请保持XT_RTOS_timer_INT未定义。根据ABI约定，可以在C或汇编中编码或调用。RTOS可以选择以自己的方式（例如宏）定义XT_TICK_PER_SEC。
*/
// 无效XT_RTOS_TIMER_INT（无效）
#ifdef CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
#define XT_RTOS_TIMER_INT   _frxt_timer_int
#endif
#define XT_TICK_PER_SEC     configTICK_RATE_HZ

/*
在15中返回触发协处理器异常的线程的协处理器状态保存区域的基址，如果没有线程正在运行，则返回0。状态保存区域的结构如extensa_context中所定义。h并且具有sizeXT_CP_SIZE。协处理器指令只能用于线程代码、中断处理程序或RTOS内核。只能从程序集代码和通过“call0”指令调用。结果为0表示不可恢复的错误。该实现只能使用a2-4、a15（必须保留所有其他regs）。
*/
// void*XT_RTOS_CP_STATE（void）
#define XT_RTOS_CP_STATE    _frxt_task_coproc_state


/*******************************************************************************
HOOKS TO DYNAMICALLY INSTALL INTERRUPT AND EXCEPTION HANDLERS PER LEVEL.

这个Xtensa RTOS端口提供了动态安装异常和中断处理程序的钩子，以便于自动化测试，每个测试用例都可以为用户异常和每个中断优先级（级别）安装自己的处理程序。这包括一个按中断优先级索引的函数指针数组，索引0是用户异常处理程序钩子。数组中的每个条目最初都是0，可以用XT_INTEXC_HOOK类型的函数指针替换。可以通过安装0卸载处理程序。

低优先级和中等优先级的处理程序遵循ABI约定，因此可以编码为C。对于异常处理程序，原因是EXCCAUSEreg的内容，如果已处理，结果是-1，否则是原因（仍需要处理）。对于中断处理程序，原因是该级别上挂起的已启用中断的掩码，结果是已清除已处理中断的位的掩码相同（未清除的中断仍需要处理）。这允许测试用例预处理或覆盖异常或中断级别的默认处理（请参阅extensa_vectors.S）。

高优先级处理程序（包括NMI）必须在程序集中进行编码，无论ABI如何，都始终按“call0”进行缩放，必须保留除a0之外的所有寄存器，并且不得使用或修改中断的堆栈。钩子参数“cause”未被传递，结果被忽略，以免给调用者带来保存和恢复a2的负担（它假设每个级别只有一个中断-请参阅extensa_vectors.S中高优先级中断中的讨论）。前面的句柄应该被编码为原型“void h（void）”，即使它插入到原型“unsigned h（unsigned）”的句柄数组中。

要启用中断/异常挂钩，请使用“-DXT_INTEXC_hooks”编译RTOS。

*******************************************************************************/

#define XT_INTEXC_HOOK_NUM  (1 + XCHAL_NUM_INTLEVELS + XCHAL_HAVE_NMI)

#ifndef __ASSEMBLER__
typedef unsigned (*XT_INTEXC_HOOK)(unsigned cause);
extern  volatile XT_INTEXC_HOOK _xt_intexc_hooks[XT_INTEXC_HOOK_NUM];
#endif


/*******************************************************************************
CONVENIENCE INCLUSIONS.

确保特定于RTOS的文件只需要包含这一个Xtensa通用标头。这些标头包含在最后，因此它们可以使用上面的RTOS定义。

*******************************************************************************/

#include    "xtensa_context.h"

#ifdef XT_RTOS_TIMER_INT
#include    "xtensa_timer.h"
#endif


/*******************************************************************************
Xtensa端口版本。

*******************************************************************************/

#define XTENSA_PORT_VERSION             1.4.2
#define XTENSA_PORT_VERSION_STRING      "1.4.2"

#endif /* XTENSA_RTOS_H */

