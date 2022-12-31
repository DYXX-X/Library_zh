/*******************************************************************************
版权所有（c）2006-2015 Cadence Design Systems Inc。

特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地使用本软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或出售本软件副本的权利，并允许向其提供本软件的人员这样做，符合以下条件：

上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OFMERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANYCLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THESOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
--------------------------------------------------------------------------------

        XTENSA CONTEXT FRAMES AND MACROS FOR RTOS ASSEMBLER SOURCES

此标头包含主要由XtensaRTOS汇编代码源文件使用的定义和宏。它包括并使用Xtensa硬件抽象层（HAL）来处理配置细节。它也可能包含在C源文件中。

!! 仅支持Xtensa异常体系结构2（XEA2）。不支持XEA1！！

注意：Xtensa架构要求堆栈指针对齐到16字节。

*******************************************************************************/

#ifndef XTENSA_CONTEXT_H
#define XTENSA_CONTEXT_H

#ifdef __ASSEMBLER__
#include    <xtensa/coreasm.h>
#endif

#include    <xtensa/config/tie.h>
#include    <xtensa/corebits.h>
#include    <xtensa/config/system.h>
#include <xtensa/xtruntime-frames.h>


/* 将值对齐到最近的n字节边界，其中n是2的幂。*/
#define ALIGNUP(n, val) (((val) + (n)-1) & -(n))


/*
-------------------------------------------------------------------------------帮助定义C和汇编程序结构的宏。
-------------------------------------------------------------------------------
*/

#ifdef STRUCT_BEGIN
#undef STRUCT_BEGIN
#undef STRUCT_FIELD
#undef STRUCT_AFIELD
#undef STRUCT_END
#endif

#if defined(_ASMLANGUAGE) || defined(__ASSEMBLER__)

#define STRUCT_BEGIN            .pushsection .text; .struct 0
#define STRUCT_FIELD(ctype,size,asname,name)    asname: .space  size
#define STRUCT_AFIELD(ctype,size,asname,name,n) asname: .space  (size)*(n)
#define STRUCT_END(sname)       sname##Size:; .popsection

#else

#define STRUCT_BEGIN            typedef struct {
#define STRUCT_FIELD(ctype,size,asname,name)    ctype   name;
#define STRUCT_AFIELD(ctype,size,asname,name,n) ctype   name[n];
#define STRUCT_END(sname)       } sname;

#endif //_ASMLANGUAGE || __ASSEMBLER__


/*
------------------------------------------------------------------------------- INTERRUPT/EXCEPTION STACK FRAME FOR A THREAD OR NESTED INTERRUPT

  这种结构的堆栈帧被分配给任何中断或异常。它位于当前堆栈上。如果RTOS有一个用于处理中断的系统堆栈，则每个线程堆栈必须只为一个中断堆栈帧留出空间，然后嵌套的中断堆栈帧将进入系统堆栈。

  框架包括用户TIE引入的基本寄存器（显式）和“额外”寄存器，或用户Xtensa配置中MAC16选项的使用。通过省略不适用于用户配置的regs，可以最小化帧大小。

  对于Windowed ABI，此堆栈框架包括中断者的基本保存区域、管理gcc嵌套函数的另一个基本保存区域，以及帮助管理寄存器窗口溢出的一点临时空间。
-------------------------------------------------------------------------------
*/

STRUCT_BEGIN
STRUCT_FIELD (long, 4, XT_STK_EXIT,     exit) /* 调度出口点*/
STRUCT_FIELD (long, 4, XT_STK_PC,       pc)   /* 返回PC*/
STRUCT_FIELD (long, 4, XT_STK_PS,       ps)   /* 返回PS*/
STRUCT_FIELD (long, 4, XT_STK_A0,       a0)
STRUCT_FIELD (long, 4, XT_STK_A1,       a1)   /* 中断前堆栈指针*/
STRUCT_FIELD (long, 4, XT_STK_A2,       a2)
STRUCT_FIELD (long, 4, XT_STK_A3,       a3)
STRUCT_FIELD (long, 4, XT_STK_A4,       a4)
STRUCT_FIELD (long, 4, XT_STK_A5,       a5)
STRUCT_FIELD (long, 4, XT_STK_A6,       a6)
STRUCT_FIELD (long, 4, XT_STK_A7,       a7)
STRUCT_FIELD (long, 4, XT_STK_A8,       a8)
STRUCT_FIELD (long, 4, XT_STK_A9,       a9)
STRUCT_FIELD (long, 4, XT_STK_A10,      a10)
STRUCT_FIELD (long, 4, XT_STK_A11,      a11)
STRUCT_FIELD (long, 4, XT_STK_A12,      a12)
STRUCT_FIELD (long, 4, XT_STK_A13,      a13)
STRUCT_FIELD (long, 4, XT_STK_A14,      a14)
STRUCT_FIELD (long, 4, XT_STK_A15,      a15)
STRUCT_FIELD (long, 4, XT_STK_SAR,      sar)
STRUCT_FIELD (long, 4, XT_STK_EXCCAUSE, exccause)
STRUCT_FIELD (long, 4, XT_STK_EXCVADDR, excvaddr)
#if XCHAL_HAVE_LOOPS
STRUCT_FIELD (long, 4, XT_STK_LBEG,   lbeg)
STRUCT_FIELD (long, 4, XT_STK_LEND,   lend)
STRUCT_FIELD (long, 4, XT_STK_LCOUNT, lcount)
#endif
#ifndef __XTENSA_CALL0_ABI__
/* 窗户溢出时的临时空间*/
STRUCT_FIELD (long, 4, XT_STK_TMP0,   tmp0)
STRUCT_FIELD (long, 4, XT_STK_TMP1,   tmp1)
STRUCT_FIELD (long, 4, XT_STK_TMP2,   tmp2)
#endif
#ifdef XT_USE_SWPRI
/* 虚拟优先级掩码的存储*/
STRUCT_FIELD (long, 4, XT_STK_VPRI,   vpri)
#endif
#ifdef XT_USE_OVLY
/* 覆盖状态的存储*/
STRUCT_FIELD (long, 4, XT_STK_OVLY,   ovly)
#endif
STRUCT_END(XtExcFrame)

#if defined(_ASMLANGUAGE) || defined(__ASSEMBLER__)
#define XT_STK_NEXT1      XtExcFrameSize
#else
#define XT_STK_NEXT1      sizeof(XtExcFrame)
#endif

/* 如果需要，分配额外的存储*/
#if XCHAL_EXTRA_SA_SIZE != 0

#if XCHAL_EXTRA_SA_ALIGN <= 16
#define XT_STK_EXTRA            ALIGNUP(XCHAL_EXTRA_SA_ALIGN, XT_STK_NEXT1)
#else
/* 如果需要比堆栈更多的对齐，请为动态对齐添加空间*/
#define XT_STK_EXTRA            (ALIGNUP(XCHAL_EXTRA_SA_ALIGN, XT_STK_NEXT1) + XCHAL_EXTRA_SA_ALIGN)
#endif
#define XT_STK_NEXT2            (XT_STK_EXTRA + XCHAL_EXTRA_SA_SIZE)

#else

#define XT_STK_NEXT2            XT_STK_NEXT1

#endif

/*
-------------------------------------------------------------------------------这是帧大小。为4个寄存器（中断者的基本保存区域）添加空间，如果有，为gcc嵌套函数添加一些空间。
-------------------------------------------------------------------------------
*/
#define XT_STK_FRMSZ            (ALIGNUP(0x10, XT_STK_NEXT2) + 0x20)


/*
------------------------------------------------------------------------------- SOLICITED STACK FRAME FOR A THREAD

  每当线程有意（同步）进入RTOS内核以服从线程调度时，就会分配这种结构的堆栈帧。它位于当前线程的堆栈上。

  请求的帧只包括被调用者根据编译器的ABI约定需要保留的寄存器、一些空间来保存返回给调用者的返回地址，以及调用者的PS寄存器。

  对于Windowed ABI，此堆栈帧包括调用者的基本保存区域。

  关于XT_SOL_EXIT字段的说明：有必要区分请求和中断堆栈帧。该字段对应于中断堆栈帧中的XT_STK_EXIT，并且始终处于相同的偏移量（0）。它可以用代码（通常为0）编写，以区分请求帧和中断帧。如果RTOS端口有另一种区分帧的方式，则可以选择忽略此字段。
-------------------------------------------------------------------------------
*/

STRUCT_BEGIN
#ifdef __XTENSA_CALL0_ABI__
STRUCT_FIELD (long, 4, XT_SOL_EXIT, exit)
STRUCT_FIELD (long, 4, XT_SOL_PC,   pc)
STRUCT_FIELD (long, 4, XT_SOL_PS,   ps)
STRUCT_FIELD (long, 4, XT_SOL_NEXT, next)
STRUCT_FIELD (long, 4, XT_SOL_A12,  a12)    /* 应为16字节对齐*/
STRUCT_FIELD (long, 4, XT_SOL_A13,  a13)
STRUCT_FIELD (long, 4, XT_SOL_A14,  a14)
STRUCT_FIELD (long, 4, XT_SOL_A15,  a15)
#else
STRUCT_FIELD (long, 4, XT_SOL_EXIT, exit)
STRUCT_FIELD (long, 4, XT_SOL_PC,   pc)
STRUCT_FIELD (long, 4, XT_SOL_PS,   ps)
STRUCT_FIELD (long, 4, XT_SOL_NEXT, next)
STRUCT_FIELD (long, 4, XT_SOL_A0,   a0)    /* 应为16字节对齐*/
STRUCT_FIELD (long, 4, XT_SOL_A1,   a1)
STRUCT_FIELD (long, 4, XT_SOL_A2,   a2)
STRUCT_FIELD (long, 4, XT_SOL_A3,   a3)
#endif
STRUCT_END(XtSolFrame)

/* 请求堆栈框架的大小*/
#define XT_SOL_FRMSZ            ALIGNUP(0x10, XtSolFrameSize)


/*
------------------------------------------------------------------------------- CO-PROCESSOR STATE SAVE AREA FOR A THREAD

  RTOS必须为每个线程提供一个区域，以在该线程没有控制权时保存协处理器的状态。只有当新线程使用协处理器指令时，协处理器才会延迟地（按需）进行上下文切换，否则线程即使失去对处理器的控制，也会保留协处理器的所有权。当不是所有者的线程执行任何协处理器指令时，会触发Xtensa协处理器异常，然后由处理器执行该协处理器的上下文切换。所有权表示协处理器中当前的线程状态。

  协处理器不能被中断或异常处理程序使用。如果协处理器指令由中断或异常处理程序执行，协处理器异常处理程序将触发内核死机和冻结。引入此限制是为了减少保存和恢复协处理器状态的开销（可能非常大），特别是从中断处理程序中删除该开销。

  协处理器状态保存区域可以位于任何方便的每线程位置，例如在线程控制块中或线程堆栈区域上方。它不需要在中断堆栈帧中，因为中断不使用协处理器。

  除了每个协处理器的保存区域外，每个协处理器有两个带标志的位掩码（如CPENABLE reg中所示）有助于尽可能高效地管理上下文切换协处理器：

  XT_CPENABLE非运行线程的CPENABLE寄存器的内容。它表示线程拥有的协处理器（其状态仍然需要）。当线程被抢占时，其CPENABLE保存在此处。当线程请求上下文swtich时，其CPENABLE将被清除-如果需要，编译器已保存（调用方保存）协处理状态。当非运行线程失去CP的所有权时，其位将被清除。当线程运行时，它的XT_CPENABLE将加载到CPENABLE reg中。当不需要更改所有权时，避免协处理器异常。

  XT_CPSTORED具有与CPENABLE相同布局的位掩码，每个协处理器一位。指示是否将每个协处理器的状态保存在状态保存区域中。当线程进入内核时，仅保存在CPENABLE中仍然启用的协进程的状态。当协处理器异常处理程序将协处理器的所有权分配给线程时，它仅在设置了该位时恢复保存状态，并清除该位。

  XT_CP_CS_ST具有与CPENABLE相同布局的位掩码，每个协处理器一位。指示是否将被调用方保存的状态保存在状态保存区域中。被调用方保存的状态在请求的上下文开关上自行保存，并在协处理器异常处理程序需要时恢复。未经请求的开关将导致在必要时保存整个协处理器。

  XT_CP_ASA指向对齐保存区域的指针。允许其对齐超过整个保存区域（可能仅对齐堆栈或TCB）。特别适用于配置有非常大的数据路径的Xtensa内核，该路径需要大于16字节的对齐（ABI堆栈对齐）。
-------------------------------------------------------------------------------
*/

#if XCHAL_CP_NUM > 0

/*  “对齐保存区域”内每个协处理器保存区域的偏移量：*/
#define XT_CP0_SA   0
#define XT_CP1_SA   ALIGNUP(XCHAL_CP1_SA_ALIGN, XT_CP0_SA + XCHAL_CP0_SA_SIZE)
#define XT_CP2_SA   ALIGNUP(XCHAL_CP2_SA_ALIGN, XT_CP1_SA + XCHAL_CP1_SA_SIZE)
#define XT_CP3_SA   ALIGNUP(XCHAL_CP3_SA_ALIGN, XT_CP2_SA + XCHAL_CP2_SA_SIZE)
#define XT_CP4_SA   ALIGNUP(XCHAL_CP4_SA_ALIGN, XT_CP3_SA + XCHAL_CP3_SA_SIZE)
#define XT_CP5_SA   ALIGNUP(XCHAL_CP5_SA_ALIGN, XT_CP4_SA + XCHAL_CP4_SA_SIZE)
#define XT_CP6_SA   ALIGNUP(XCHAL_CP6_SA_ALIGN, XT_CP5_SA + XCHAL_CP5_SA_SIZE)
#define XT_CP7_SA   ALIGNUP(XCHAL_CP7_SA_ALIGN, XT_CP6_SA + XCHAL_CP6_SA_SIZE)
#define XT_CP_SA_SIZE   ALIGNUP(16, XT_CP7_SA + XCHAL_CP7_SA_SIZE)

/*  整个保存区域内的偏移量：*/
#define XT_CPENABLE 0   /* （2字节）此线程的协处理器处于活动状态*/
#define XT_CPSTORED 2   /* 为此线程保存的（2字节）协处理器*/
#define XT_CP_CS_ST 4   /* （2字节）协处理器被调用方为此线程保存的寄存器*/
#define XT_CP_ASA   8   /* （4字节）指向对齐保存区域的指针*/
/*  整体尺寸允许动态对齐：*/
#define XT_CP_SIZE  (12 + XT_CP_SA_SIZE + XCHAL_TOTAL_SA_ALIGN)
#else
#define XT_CP_SIZE  0
#endif


/*
 获取当前核心ID的宏。仅使用给定的reg作为参数。在ESP32上读取PRID，在PRO处理器上获得0xCDCD（0），在APP CPU上获得0xABAB（1）。我们可以通过检查第13位来区分两者：APP上是1，PRO处理器上是0。
*/
#ifdef __ASSEMBLER__
	.macro getcoreid reg
	rsr.prid \reg
	extui \reg,\reg,13,1
	.endm
#endif

/* 注：这与ESP-IDF FreeRTOS中使用的xCoreID不同，大多数地方使用0和1，这是通过检查第13位确定的（参见前面的注释）
*/
#define CORE_ID_REGVAL_PRO 0xCDCD
#define CORE_ID_REGVAL_APP 0xABAB

/* 包括兼容性，建议改用CORE_ID_REGVAL_PRO*/
#define CORE_ID_PRO CORE_ID_REGVAL_PRO

/* 包括兼容性，建议改用CORE_ID_REGVAL_APP*/
#define CORE_ID_APP CORE_ID_REGVAL_APP

/*
------------------------------------------------------------------------------- MACROS TO HANDLE ABI SPECIFICS OF FUNCTION ENTRY AND RETURN

  如果两个ABI的框架尺寸要求相同，则非常方便。ENTRY（sz）、RET（sz）用于框架函数（具有局部函数或进行调用）。ENTRY0、RET0用于无框架函数（无局部变量，无调用）。

  其中size=堆栈帧的大小（以字节为单位）（必须大于0并对齐到16）。对于框架函数，创建框架，并将返回地址保存在框架底部（Call0 ABI）或由硬件确定（窗口ABI）。对于无帧函数，a0中没有帧和返回地址。注意：因为CPP宏扩展到单行，所以需要多行扩展的宏被实现为汇编宏。
-------------------------------------------------------------------------------
*/

#ifdef __ASSEMBLER__
#ifdef __XTENSA_CALL0_ABI__
  /* 呼叫0*/
  #define ENTRY(sz)     entry1  sz
    .macro  entry1 size=0x10
    addi    sp, sp, -\size
    s32i    a0, sp, 0
    .endm
  #define ENTRY0
  #define RET(sz)       ret1    sz
    .macro  ret1 size=0x10
    l32i    a0, sp, 0
    addi    sp, sp, \size
    ret
    .endm
  #define RET0          ret
#else
  /* 已打开窗口*/
  #define ENTRY(sz)     entry   sp, sz
  #define ENTRY0        entry   sp, 0x10
  #define RET(sz)       retw
  #define RET0          retw
#endif
#endif





#endif /* XTENSA_CONTEXT_H */

