/*******************************************************************************
//版权所有（c）2003-2015 Cadence Design Systems，Inc.////特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权限，包括//但不限于使用、复制、修改、合并、发布、//分发、再许可和/或销售软件副本的权利，和//允许向其提供软件的人员这样做，但须遵守以下conditions:////上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。////软件按“原样”提供，无任何明示或暗示的保证，包括但不限于适销性、适用于特定用途和非侵权性的保证。//在任何情况下，作者或版权持有人均不对因软件或软件的使用或其他交易而产生的任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权诉讼或其他诉讼中。
--------------------------------------------------------------------------------

        XTENSA INFORMATION FOR RTOS TICK TIMER AND CLOCK FREQUENCY

此标头包含主要由XtensaRTOS汇编代码源文件使用的定义和宏。它包括并使用Xtensa硬件抽象层（HAL）来处理配置细节。它也可能包含在C源文件中。

用户可以编辑以修改定时器选择，并指定时钟频率和滴答持续时间，以使定时器中断与实时滴答持续时间相匹配。

如果RTOS没有计时器中断，那么就没有滴答计时器，时钟频率也不相关，所以所有这些宏都没有定义，Xtensa核心配置不需要计时器。

*******************************************************************************/

#ifndef XTENSA_TIMER_H
#define XTENSA_TIMER_H

#ifdef __ASSEMBLER__
#include    <xtensa/coreasm.h>
#endif

#include    <xtensa/corebits.h>
#include    <xtensa/config/system.h>

#include    "xtensa_rtos.h"     /* 如果这不是直接包含的*/

#include    "freertos/FreeRTOSConfig.h"

/*
选择用于周期性计时的计时器，并确定其中断编号和优先级。用户可以通过使用-D定义XT_timer_INDEX来指定计时器，在这种情况下，将检查其有效性（它必须存在于此内核中，并且不能处于高优先级中断上-错误将被报告为无效）。否则，选择第一个可用的低或中优先级中断定时器。
*/
#if XCHAL_NUM_TIMERS == 0

  #error "This Xtensa configuration is unsupported, it has no timers."

#else

#ifndef XT_TIMER_INDEX
  #if XCHAL_TIMER3_INTERRUPT != XTHAL_TIMER_UNCONFIGURED
    #if XCHAL_INT_LEVEL(XCHAL_TIMER3_INTERRUPT) <= XCHAL_EXCM_LEVEL
      #undef  XT_TIMER_INDEX
      #define XT_TIMER_INDEX    3
    #endif
  #endif
  #if XCHAL_TIMER2_INTERRUPT != XTHAL_TIMER_UNCONFIGURED
    #if XCHAL_INT_LEVEL(XCHAL_TIMER2_INTERRUPT) <= XCHAL_EXCM_LEVEL
      #undef  XT_TIMER_INDEX
      #define XT_TIMER_INDEX    2
    #endif
  #endif
  #if XCHAL_TIMER1_INTERRUPT != XTHAL_TIMER_UNCONFIGURED
    #if XCHAL_INT_LEVEL(XCHAL_TIMER1_INTERRUPT) <= XCHAL_EXCM_LEVEL
      #undef  XT_TIMER_INDEX
      #define XT_TIMER_INDEX    1
    #endif
  #endif
  #if XCHAL_TIMER0_INTERRUPT != XTHAL_TIMER_UNCONFIGURED
    #if XCHAL_INT_LEVEL(XCHAL_TIMER0_INTERRUPT) <= XCHAL_EXCM_LEVEL
      #undef  XT_TIMER_INDEX
      #define XT_TIMER_INDEX    0
    #endif
  #endif
#endif
#ifndef XT_TIMER_INDEX
  #error "There is no suitable timer in this Xtensa configuration."
#endif

#define XT_CCOMPARE             (CCOMPARE + XT_TIMER_INDEX)
#define XT_TIMER_INTNUM         XCHAL_TIMER_INTERRUPT(XT_TIMER_INDEX)
#define XT_TIMER_INTPRI         XCHAL_INT_LEVEL(XT_TIMER_INTNUM)
#define XT_TIMER_INTEN          (1 << XT_TIMER_INTNUM)

#if XT_TIMER_INTNUM == XTHAL_TIMER_UNCONFIGURED
  #error "The timer selected by XT_TIMER_INDEX does not exist in this core."
#elif XT_TIMER_INTPRI > XCHAL_EXCM_LEVEL
  #error "The timer interrupt cannot be high priority (use medium or low)."
#endif

#endif /* XCHAL_NUM_TIMERS */

/*
设置处理器时钟频率，用于确定计时器刻度的时钟除数。用户应确保对所使用的Xtensa平台进行调整。如果通过xtbsp。h、 这可能是未定义的，并且在运行时初始化期间将计算和缓存频率和滴答除数。

模拟器注意事项：在Xtensa指令集模拟器下，只能估计频率，因为它取决于主机的速度和模拟器的版本。此外，由于它的运行速度比硬件慢得多，因此在模拟器下无法实现大多数应用程序的实时性能。频率过低不允许在计时器中断之间有足够的时间，导致线程饥饿。要在模拟器上获得更方便但非实时的滴答声持续时间，请使用xt xcc选项“-DXT_simulator”进行编译。调整此频率以适应口味（反正不是实时的！）。
*/
#if defined(XT_SIMULATOR) && !defined(XT_CLOCK_FREQ)
#define XT_CLOCK_FREQ       configCPU_CLOCK_HZ
#endif

#if !defined(XT_CLOCK_FREQ) && !defined(XT_BOARD)
  #error "XT_CLOCK_FREQ must be defined for the target platform."
#endif

/*
每秒计时器“滴答声”的默认数量（10ms滴答声的默认值为100）。RTOS可以在extensa_RTOS.h中以自己的方式（如果适用）定义它。用户可以通过在此处或在extensa_RTOS中编辑它，将其重新定义为应用程序的最佳值。h、 或使用xt xcc选项“-DXT_TICK_PER_SEC=<value>”进行编译，其中<value>是一个合适的数字。
*/
#ifndef XT_TICK_PER_SEC
#define XT_TICK_PER_SEC    configTICK_RATE_HZ        /* 10毫秒滴答声=每秒100次滴答声*/
#endif

/*
计时器刻度和中断的时钟除数的推导（每刻度一个）。
*/
#ifdef XT_CLOCK_FREQ
#define XT_TICK_DIVISOR     (XT_CLOCK_FREQ / XT_TICK_PER_SEC)
#endif

#ifndef __ASSEMBLER__
extern unsigned _xt_tick_divisor;
extern void     _xt_tick_divisor_init(void);
#endif

#endif  /* XTENSA_TIMER_H */

