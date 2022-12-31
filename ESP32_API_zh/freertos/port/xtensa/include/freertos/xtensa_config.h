/*******************************************************************************
//版权所有（c）2003-2015 Cadence Design Systems，Inc.////特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权限，包括//但不限于使用、复制、修改、合并、发布、//分发、再许可和/或销售软件副本的权利，和//允许向其提供软件的人员这样做，但须遵守以下conditions:////上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。////软件按“原样”提供，无任何明示或暗示的保证，包括但不限于适销性、适用于特定用途和非侵权性的保证。//在任何情况下，作者或版权持有人均不对因软件或软件的使用或其他交易而产生的任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权诉讼或其他诉讼中。
--------------------------------------------------------------------------------

  Xtensa构建的配置特定信息。此文件必须包含在FreeRTOSConfig中。h正确设置依赖于配置的参数。

  注意：要启用线程安全C库支持，必须在命令行上方或上方的某个位置将XT_USE_thread_safe_CLIB定义为>0。

*******************************************************************************/

#ifndef XTENSA_CONFIG_H
#define XTENSA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <xtensa/hal.h>
#include <xtensa/config/core.h>
#include <xtensa/config/system.h>	/* XSHAL_CLIB需要*/

#include "xtensa_context.h"


/*-----------------------------------------------------------------------------
*                                 STACK REQUIREMENTS
*
* 本节定义了最小堆栈大小，以及为保存协处理器状态和/或C库状态信息所需的额外空间（如果C库启用了线程安全）。大小以字节为单位。
*
* 单个任务的堆栈大小应根据任务的最大调用深度和中断嵌套的最大级别从这些最小值中导出。最小堆栈大小由XT_stack_MIN_size定义。这个最小值是基于一个任务的要求，该任务不调用其他任务，但可以中断。这假设中断处理程序调用的深度不超过几个级别。如果这不正确，即一个或多个中断处理程序进行深度调用，则必须增加最小值。
*
* 如果Xtensa处理器配置包含协处理器，则分配空间以保存堆栈上的协处理器状态。
*
* 如果为C运行库启用了线程安全（定义了XT_USE_thread_SAFE_CLIB），则分配空间以将C库上下文保存在TCB中。
*
* 分配不足的堆栈空间是难以发现错误的常见原因。在开发期间，最好启用FreeRTOS堆栈检查功能。
*
* 用法：
*
* XT_USE_THREAD_SAFE_CLIB—将其定义为非零值，以启用C库的线程安全使用。这将需要为使用C库可重入函数的任务分配额外的堆栈空间。有关详细信息，请参见下文。
*
* 注意：Xtensa工具链支持多个C库，但并非所有库都支持线程安全。检查您的核心配置，看看为您的系统选择了哪个C库。
*
* XT_STACK_MIN_SIZE—任何任务的最小堆栈大小。对于任何任务，建议不要使用小于此值的堆栈。如果要使用小于此大小的堆栈，则必须验证较小的堆栈在所有操作条件下都能正常工作。
*
* XT_STACK_EXTRA——为不进行C库可重入调用的任务分配的额外堆栈空间量。将其添加到任务本身所需的堆栈空间量中。
*
* XT_STACK_EXTRA_CLIB—为C库状态分配的空间量。
*
-----------------------------------------------------------------------------*/

/* 中断/异常挂钩需要额外的空间。*/
#ifdef XT_INTEXC_HOOKS
  #ifdef __XTENSA_CALL0_ABI__
    #define STK_INTEXC_EXTRA        0x200
  #else
    #define STK_INTEXC_EXTRA        0x180
  #endif
#else
  #define STK_INTEXC_EXTRA          0
#endif

#define XT_CLIB_CONTEXT_AREA_SIZE         0

/*------------------------------------------------------------------------------
  额外大小——中断帧加协处理器节省区域加挂钩空间。注意：确保XT_INTEXC_HOOKS未定义，除非您确实需要钩子。
------------------------------------------------------------------------------*/
#ifdef __XTENSA_CALL0_ABI__
  #define XT_XTRA_SIZE            (XT_STK_FRMSZ + STK_INTEXC_EXTRA + 0x10 + XT_CP_SIZE)
#else
  #define XT_XTRA_SIZE            (XT_STK_FRMSZ + STK_INTEXC_EXTRA + 0x20 + XT_CP_SIZE)
#endif

/*------------------------------------------------------------------------------
  为用户代码分配的空间--函数调用和本地变量。注意：此数字可根据您的需要进行调整。您必须验证保留的空间量是否足以满足应用程序中最坏的情况。注意：窗口化的ABI需要更多的堆栈，因为必须为溢出寄存器窗口保留空间。
------------------------------------------------------------------------------*/
#ifdef __XTENSA_CALL0_ABI__
  #define XT_USER_SIZE            0x200
#else
  #define XT_USER_SIZE            0x400
#endif

/* 建议的最小堆栈大小。*/
#define XT_STACK_MIN_SIZE         ((XT_XTRA_SIZE + XT_USER_SIZE) / sizeof(unsigned char))

/* 使用和不使用C库线程上下文时的操作系统开销。*/
#define XT_STACK_EXTRA            (XT_XTRA_SIZE)
#define XT_STACK_EXTRA_CLIB       (XT_XTRA_SIZE + XT_CLIB_CONTEXT_AREA_SIZE)


#ifdef __cplusplus
}
#endif

#endif /* XTENSA_CONFIG_H */

