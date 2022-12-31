/*
 * xtensa/coreasm。h—取决于CORE配置的汇编程序特定定义
 *
 *  独立于配置的二进制文件（链接到特定于配置的HAL库中）的源文件不得包含此文件。然而，HAL本身包含此文件是完全正常的。
 *
 *  此文件不能包含extensa/config/system.h。依赖于系统信息的任何汇编器头文件都可能包含在新的系统中。h（或sysasm.h）头文件。
 *
 *  注意：宏beqi32不依赖于配置，在我们有一个适当的独立于配置的头文件之前，它一直放在这里。
 */

/* $Id://depot/rel/Foxhill/dot.9/Xtensa/OS/include/Xtensa/coream。小时#1$*/

/*
 * 版权所有（c）2000-2014 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTENSA_COREASM_H
#define XTENSA_COREASM_H

/*
 *  告诉头文件这是程序集源，这样他们就可以避免非汇编程序定义（例如C类型等）：
 */
#ifndef _ASMLANGUAGE	/* 条件化以避免cpp警告（第三方可能使用相同的宏）*/
#define _ASMLANGUAGE
#endif

#include <xtensa/config/core.h>
#include <xtensa/config/specreg.h>
#include <xtensa/config/system.h>

/*
 *  汇编语言特定的定义（汇编宏等）。
 */

/*----------------------------------------------------------------------
 *  find_ms_set位
 *
 *  此宏查找＜as＞中设置的最高有效位，并在＜ad＞中返回其索引+＜base＞，如果＜as＞为零，则返回＜base＞-1。lsbit的索引计数从零开始，因此返回值的范围从<base>-1（无位集）到<base>+31（msbit集）。
 *
 *  参数：＜ad＞目标地址寄存器（任何寄存器）＜as＞源地址寄存器＜at＞临时地址寄存器（必须与＜as＞不同）＜base＞添加到结果的常量值（通常为0或1）输入时：＜ad＜＝undefined if different than＜as＞＜as＞＝要找到其最高有效设置位的值＜at＞＝undefine此宏不使用其他寄存器。退出时：<ad>=<base>+原始<as>中设置的msbit索引，=<base>-1，如果原始<as>=零<as>clobbed（如果不是<ad>）<at>clobbred（如果不是<ad>）示例：find_ms_setbit a0，a4，a0，0--在a4中设置的msbit的a0索引中返回
 */

	.macro	find_ms_setbit ad, as, at, base
#if XCHAL_HAVE_NSA
	movi	\at, 31+\base
	nsau	\as, \as	// 获取\as的索引，从msbit开始编号（如果没有，则为32）
	sub	\ad, \at, \as	// 从lsbit获取编号（0..31，-1如果不存在）
#else /* XCHAL_HAVE_NSA */
	movi	\at, \base	// 从0的结果开始（指向32的lsbit）

	beqz	\as, 2f		// 零参数的特殊情况：返回-1
	bltui	\as, 0x10000, 1f	// 它是16个lsbit之一吗？（如果是，检查低16位）
	addi	\at, \at, 16	// 否，将结果递增至高位16位（共32位）
	//srli\as，\as，16//检查上半部分（右移16位）
	extui	\as, \as, 16, 16	// 检查上半部分（右移16位）
1:	bltui	\as, 0x100, 1f	// 它是8个lsbit之一吗？（如果是，检查低8位）
	addi	\at, \at, 8	// 否，将结果递增到高8位（共16位）
	srli	\as, \as, 8	// 右移以检查高位8位
1:	bltui	\as, 0x10, 1f	// 它是4个lsbit之一吗？（如果是，检查低4位）
	addi	\at, \at, 4	// 否，将结果递增至高位4位（共8位）
	srli	\as, \as, 4	// 右移4位以检查上半部分
1:	bltui	\as, 0x4, 1f	// 它是2个lsbit之一吗？（如果是，检查低2位）
	addi	\at, \at, 2	// 否，将结果递增到高2位（共4位）
	srli	\as, \as, 2	// 右移2位以检查上半部分
1:	bltui	\as, 0x2, 1f	// 是lsbit吗？
	addi	\at, \at, 2	// 否，将结果递增到高位（共2位）
2:	addi	\at, \at, -1	// （从上面开始：添加1；从beqz开始：返回-1）
	//srli\as，\as，1
1:				// 完成！\at包含msbit集的索引（如果未设置，则为-1）
	.if	0x\ad - 0x\at	// 目的地不同于\？（有效，因为regs为a0-a15）
	mov	\ad, \at	// 然后将结果移动到\ad
	.endif
#endif /* XCHAL_HAVE_NSA */
	.endm	// find_ms_set位

/*----------------------------------------------------------------------
 *  find_ls_set位
 *
 *  此宏查找在＜as＞中设置的最低有效位，并在＜ad＞中返回其索引。用法与find_ms_setbit宏相同。示例：find_ls_setbit a0，a4，a0，0--返回a4中设置的lsbit的a0索引
 */

	.macro	find_ls_setbit ad, as, at, base
	neg	\at, \as	// 只保留设置的最低有效位。。。
	and	\as, \at, \as	// …在\中
	find_ms_setbit	\ad, \as, \at, \base
	.endm	// find_ls_set位

/*----------------------------------------------------------------------
 *  查找_ls_one
 *
 *  与find_ls_setbit相同，基数为零。源（as）和目标（ad）寄存器必须不同。提供向后兼容性。
 */

	.macro	find_ls_one ad, as
	find_ls_setbit	\ad, \as, \ad, 0
	.endm	// 查找_ls_one

/*----------------------------------------------------------------------
 *  洪水、洪水、洪水
 *
 *  这些宏用于快速内部循环，无论是否配置了“循环”选项，这些循环都有效。如果配置了Loops选项，它们只需使用零开销LOOP指令；否则它们使用显式减量和分支指令。
 *
 *  它们成对使用，循环开始时为floop、floopnez或floopgtz，结束时为flooppend。
 *
 *  必须为每对循环宏调用指定循环计数地址寄存器和该循环的唯一标签。
 *
 *  例子：
 *
 *	movi	 a3，16//循环16次floop a3，myloop1:bnez a7，end1//退出循环，如果a7！=0：洪水a3，myloop1结束1：
 *
 *  与LOOP指令一样，这些宏不能嵌套，必须至少包含一条指令，不能调用循环内的函数等。可以通过跳到floloond之后的指令（或循环外的其他地方）来退出循环，也可以跳到flolopend之前的NOP指令来继续。
 *
 *  与LOOP指令不同，传递给floop*的寄存器不能在循环内使用，因为如果未配置Loops选项，它将用作循环计数器。退出循环后，其值未定义。因为循环计数器寄存器在循环中是活动的，所以您不能像使用loop指令那样使用ROTW轻松地使用此构造在寄存器文件中循环，除非您复制循环寄存器。
 */

	/*  宏的命名标签版本：*/

	.macro	floop		ar, endlabel
	floop_		\ar, .Lfloopstart_\endlabel, .Lfloopend_\endlabel
	.endm

	.macro	floopnez	ar, endlabel
	floopnez_	\ar, .Lfloopstart_\endlabel, .Lfloopend_\endlabel
	.endm

	.macro	floopgtz	ar, endlabel
	floopgtz_	\ar, .Lfloopstart_\endlabel, .Lfloopend_\endlabel
	.endm

	.macro	floopend	ar, endlabel
	floopend_	\ar, .Lfloopstart_\endlabel, .Lfloopend_\endlabel
	.endm

	/*  宏的编号本地标签版本：*/
#if 0 /*UNTESTED*/
	.macro	floop89		ar
	floop_		\ar, 8, 9f
	.endm

	.macro	floopnez89	ar
	floopnez_	\ar, 8, 9f
	.endm

	.macro	floopgtz89	ar
	floopgtz_	\ar, 8, 9f
	.endm

	.macro	floopend89	ar
	floopend_	\ar, 8b, 9
	.endm
#endif /*0*/

	/*  宏的基础版本：*/

	.macro	floop_	ar, startlabel, endlabelref
	.ifdef	_infloop_
	.if	_infloop_
	.err	// 错误：floop不能嵌套
	.endif
	.endif
	.set	_infloop_, 1
#if XCHAL_HAVE_LOOPS
	loop	\ar, \endlabelref
#else /* XCHAL_HAVE_LOOPS */
\startlabel:
	addi	\ar, \ar, -1
#endif /* XCHAL_HAVE_LOOPS */
	.endm	// 洪水，洪水_

	.macro	floopnez_	ar, startlabel, endlabelref
	.ifdef	_infloop_
	.if	_infloop_
	.err	// 错误：floopnez不能嵌套
	.endif
	.endif
	.set	_infloop_, 1
#if XCHAL_HAVE_LOOPS
	loopnez	\ar, \endlabelref
#else /* XCHAL_HAVE_LOOPS */
	beqz	\ar, \endlabelref
\startlabel:
	addi	\ar, \ar, -1
#endif /* XCHAL_HAVE_LOOPS */
	.endm	// 洪水泛滥_

	.macro	floopgtz_	ar, startlabel, endlabelref
	.ifdef	_infloop_
	.if	_infloop_
	.err	// 错误：floopgtz不能嵌套
	.endif
	.endif
	.set	_infloop_, 1
#if XCHAL_HAVE_LOOPS
	loopgtz	\ar, \endlabelref
#else /* XCHAL_HAVE_LOOPS */
	bltz	\ar, \endlabelref
	beqz	\ar, \endlabelref
\startlabel:
	addi	\ar, \ar, -1
#endif /* XCHAL_HAVE_LOOPS */
	.endm	// 洪水泛滥_


	.macro	floopend_	ar, startlabelref, endlabel
	.ifndef	_infloop_
	.err	// 错误：flolopend没有匹配flolopXXX
	.endif
	.ifeq	_infloop_
	.err	// 错误：flolopend没有匹配flolopXXX
	.endif
	.set	_infloop_, 0
#if ! XCHAL_HAVE_LOOPS
	bnez	\ar, \startlabelref
#endif /* XCHAL_HAVE_LOOPS */
\endlabel:
	.endm	// 洪水泛滥_

/*----------------------------------------------------------------------
 *  crsil—条件RSIL（读取/设置中断级别）
 *
 *  如果RSIL指令存在，则执行它，否则只读取PS。如果未选择中断选项，则RSIL指令在新的异常架构中不存在。
 */

	.macro	crsil	ar, newlevel
#if XCHAL_HAVE_OLD_EXC_ARCH || XCHAL_HAVE_INTERRUPTS
	rsil	\ar, \newlevel
#else
	rsr.ps	\ar
#endif
	.endm	// crsil公司

/*----------------------------------------------------------------------
 *  safe_movi_a0—当L32R不安全时，将常量移到a0
 *
 *  此宏通常由中断/异常处理程序使用。在a0中加载32位常量，而不使用任何其他寄存器，也不损坏LITBASE寄存器，即使LITBASE寄存器的值是未知的（例如，当应用程序代码和中断/异常处理代码是独立构建的，因此使用独立的LITBASE注册器值时；调试监视器就是一个例子）。
 *
 *  结果代码的最坏大小：17字节。
 */

	.macro	safe_movi_a0	constant
#if XCHAL_HAVE_ABSOLUTE_LITERALS
	/*  控制PC相对文字负载，即使我们可能处于文字库相对模式：*/
	j	1f
	.begin	no-transform			// 确保以下各项按原样组装
	.align	4				// 确保常量并调用0目标。。。
	.byte	0				// …是4字节对齐的（call0指令长3字节）
1:	call0	2f				// 读取a0中的PC（在call0之后）
	.long	\constant			// 要加载到a0的32位常量
2:
	.end	no-transform
	l32i	a0, a0, 0			// 负载常数
#else
	movi	a0, \constant			// 没有LITBASE，可以假设PC相对L32R
#endif
	.endm




/*----------------------------------------------------------------------
 *  窗口_药丸｛4,8,12｝
 *
 *  这些宏将调用者的注册窗口溢出到堆栈中。他们为特权和非特权任务工作。必须从窗口ABI上下文中调用，例如在窗口ABI函数中（即有效堆栈帧、启用窗口异常、不处于异常模式等）。
 *
 *  此宏需要在同一个汇编单元和节中调用window_spill_common宏。
 *
 *  请注意，使用window_spill｛4，8，12｝宏比调用使用window_spell_function实现的函数更有效，因为后者需要额外的代码来计算溢出函数的调用大小。
 *
 *  示例用法：
 *
 *		.text .align 4.全局some_function.键入some_function，@function some_functions:条目a1，16:：
 *
 *		window_spill4	// 溢出某些函数调用方的窗口；仅保留a0..a3；//要在这个示例函数中使用window_spill｛8，12｝，我们必须//增加入口指令分配的空间，因为//16字节只允许call4；call8/window_spil8或call12/window_spill12分别需要32或48字节（+本地）。
 *
 *		:
 *
 *		retw
 *
 *		window_spill_common	// 实例化window_spill4使用的代码
 *
 * 进入时：none（如果window_spill4）堆栈帧为call8分配了足够的空间（如果window_spill8）堆栈帧已为call12分配了足够空间（如果windows_spill12）退出时：a4..a15 clobbered（如果windows_pill4的话）a8..a15 clorbered（若window_spil8的话）a12..a15 clopbered（如window_spill的话）没有调用程序窗口在活动寄存器中
 */

	.macro	window_spill4
#if XCHAL_HAVE_WINDOWED
# if XCHAL_NUM_AREGS == 16
	movi	a15, 0			// 对于16个寄存器文件，无需调用即可到达结尾
# elif XCHAL_NUM_AREGS == 32
	call4	.L__wdwspill_assist28	// 呼叫深度足以清除任何现场呼叫
# elif XCHAL_NUM_AREGS == 64
	call4	.L__wdwspill_assist60	// 呼叫深度足以清除任何现场呼叫
# endif
#endif
	.endm	// 窗口_柱4

	.macro	window_spill8
#if XCHAL_HAVE_WINDOWED
# if XCHAL_NUM_AREGS == 16
	movi	a15, 0			// 对于16个寄存器文件，无需调用即可到达结尾
# elif XCHAL_NUM_AREGS == 32
	call8	.L__wdwspill_assist24	// 呼叫深度足以清除任何现场呼叫
# elif XCHAL_NUM_AREGS == 64
	call8	.L__wdwspill_assist56	// 呼叫深度足以清除任何现场呼叫
# endif
#endif
	.endm	// 窗口_柱8

	.macro	window_spill12
#if XCHAL_HAVE_WINDOWED
# if XCHAL_NUM_AREGS == 16
	movi	a15, 0			// 对于16个寄存器文件，无需调用即可到达结尾
# elif XCHAL_NUM_AREGS == 32
	call12	.L__wdwspill_assist20	// 呼叫深度足以清除任何现场呼叫
# elif XCHAL_NUM_AREGS == 64
	call12	.L__wdwspill_assist52	// 呼叫深度足以清除任何现场呼叫
# endif
#endif
	.endm	// 窗口_柱12


/*----------------------------------------------------------------------
 *  window_spill_函数
 *
 *  此宏输出一个函数，该函数会将调用方的调用方的注册窗口溢出到堆栈中。例如，它可以用于实现在非特权任务中工作的xthal_window_spill（）版本。这适用于特权和非特权任务。
 *
 *  典型用法：
 *
 *		.text .align 4.全局my_spill_function。键入my_spill函数，@function my_spille函数：window_spill
 *
 *  进入结果函数：none退出结果函数：none（活动寄存器中没有调用程序窗口）
 */

	.macro	window_spill_function
#if XCHAL_HAVE_WINDOWED
#  if XCHAL_NUM_AREGS == 32
	entry	sp, 48
	bbci.l	a0, 31, 1f		// 分支（如果使用call4调用）
	bbsi.l	a0, 30, 2f		// 分支（如果使用call12调用）
	call8	.L__wdwspill_assist16	// 用call8调用，只需要另一个8
	retw
1:	call12	.L__wdwspill_assist16	// 用call4调用，只需要另外12个
	retw
2:	call4	.L__wdwspill_assist16	// 用call12调用，只需要另外4个
	retw
#  elif XCHAL_NUM_AREGS == 64
	entry	sp, 48
	bbci.l	a0, 31, 1f		// 分支（如果使用call4调用）
	bbsi.l	a0, 30, 2f		// 分支（如果使用call12调用）
	call4	.L__wdwspill_assist52	// 用call8调用，只需要一个call4
	retw
1:	call8	.L__wdwspill_assist52	// 用call4调用，只需要一个call8
	retw
2:	call12	.L__wdwspill_assist40	// 使用call12调用，可以跳过调用12
	retw
#  elif XCHAL_NUM_AREGS == 16
	entry	sp, 16
	bbci.l	a0, 31, 1f	// 分支（如果使用call4调用）
	bbsi.l	a0, 30, 2f	// 分支（如果使用call12调用）
	movi	a7, 0		// 用call8调用
	retw
1:	movi	a11, 0		// 用call4调用
2:	retw			// 如果用call12调用，则所有内容都已溢出

//movi a15，0//除了直接打电话的人外，其他人都被耍了
//第1页
////输入指令在汇编程序中很神奇（自动对齐）
////所以我们必须跳过去，避免从衬垫中掉下来。
////我们需要输入/返回以知道返回何处。
//1： 条目sp，16
//重新开始
#  else
#   error "unrecognized address register file size"
#  endif

#endif /* XCHAL_HAVE_WINDOWED */
	window_spill_common
	.endm	// window_spill_函数

/*----------------------------------------------------------------------
 *  window_spill_common窗口
 *
 *  任何次数的window_spill##和window_spill函数宏调用所使用的公共代码。
 *
 *  必须在给定的程序集单元内，在该程序集单元的调用/j范围内，以及与window_spill##宏调用相同的部分内，实例化一次。（由window_spill_function宏自动实例化。）
 */

	.macro	window_spill_common
#if XCHAL_HAVE_WINDOWED && (XCHAL_NUM_AREGS == 32 || XCHAL_NUM_AREGS == 64)
	.ifndef	.L__wdwspill_defined
#  if XCHAL_NUM_AREGS >= 64
.L__wdwspill_assist60:
	entry	sp, 32
	call8	.L__wdwspill_assist52
	retw
.L__wdwspill_assist56:
	entry	sp, 16
	call4	.L__wdwspill_assist52
	retw
.L__wdwspill_assist52:
	entry	sp, 48
	call12	.L__wdwspill_assist40
	retw
.L__wdwspill_assist40:
	entry	sp, 48
	call12	.L__wdwspill_assist28
	retw
#  endif
.L__wdwspill_assist28:
	entry	sp, 48
	call12	.L__wdwspill_assist16
	retw
.L__wdwspill_assist24:
	entry	sp, 32
	call8	.L__wdwspill_assist16
	retw
.L__wdwspill_assist20:
	entry	sp, 16
	call4	.L__wdwspill_assist16
	retw
.L__wdwspill_assist16:
	entry	sp, 16
	movi	a15, 0
	retw
	.set	.L__wdwspill_defined, 1
	.endif
#endif /* XCHAL_HAVE_INDOWED（带32或64 aregs）*/
	.endm	// window_spill_common窗口

/*----------------------------------------------------------------------
 *  北京32
 *
 *  宏实现任意32位立即值的beqi版本
 *
 *     beqi32 ax，ay，imm32，标签
 *
 *  将寄存器ax中的值与imm32值进行比较，如果相等则跳转到标签。Clobbers注册ay（如果需要）
 *
 */
   .macro beqi32	ax, ay, imm, label
    .ifeq ((\imm-1) & ~7)	// 1..8 ?
		beqi	\ax, \imm, \label
    .else
      .ifeq (\imm+1)		// -1 ?
		beqi	\ax, \imm, \label
      .else
        .ifeq (\imm)		// 0 ?
		beqz	\ax, \label
        .else
		//  我们还可以处理即时消息10、12、16、32、6418256
		//  但这将是一个很长的宏。。。
		movi	\ay, \imm
		beq	\ax, \ay, \label
        .endif
      .endif
    .endif
   .endm // 北京32

/*----------------------------------------------------------------------
 *  isync_retw_nop
 *
 *  如果ISYNC后面紧跟RETW（或其他修改WindowBase或WindowStart的指令），则必须在ISYNC之后立即调用该宏，在XEA1配置中，在该上下文中，可以选择内核矢量模式，并且可以启用一级中断和窗口溢出。
 *
 *  在带有勘误表“XEA1KWIN”的硬件上（有关详细信息，请参阅<extensa/core.h>），如果在内核矢量模式下运行并启用中断和窗口溢出，XEA1代码必须在ISYNC和RETW之间至少有一条指令。
 */
	.macro	isync_retw_nop
#if XCHAL_MAYHAVE_ERRATUM_XEA1KWIN
	nop
#endif
	.endm

/*----------------------------------------------------------------------
 *  isync_return_nop
 *
 *  应该使用此宏，而不是用于在窗口化和call0 ABI上运行的代码中的isync_retw_nop
 */
        .macro  isync_return_nop
#ifdef __XTENSA_WINDOWED_ABI__
        isync_retw_nop
#endif
        .endm

/*----------------------------------------------------------------------
 *  isync_erratum453
 *
 *  必须在代码中的某些点调用此宏，特别是在异常和中断向量中，以解决错误453。
 */
	.macro	isync_erratum453
#if XCHAL_ERRATUM_453
	isync
#endif
	.endm


/*----------------------------------------------------------------------
 *  读写器
 *
 *  “rsr”的包装器，用于构造涉及级别的寄存器名称，例如EPCn等。使用如下：readsr epc XCHAL_DEBUGLEVEL a2
 */
	.macro	readsr  reg suf ar
	rsr.\reg\suf	\ar
	.endm

/*----------------------------------------------------------------------
 *  写入sr
 *
 *  “wsr”的包装器，用于构造涉及级别的寄存器名称，例如EPCn等。使用如下：writesr epc XCHAL_DEBUGLEVEL a2
 */
	.macro	writesr  reg suf ar
	wsr.\reg\suf	\ar
	.endm

/*----------------------------------------------------------------------
 *  xchgsr公司
 *
 *  “xsr”的包装器，用于构造涉及EPCn等级别的寄存器名称。使用如下：xchgsr epc XCHAL_DEBUGLEVEL a2
 */
	.macro	xchgsr  reg suf ar
	xsr.\reg\suf	\ar
	.endm

/*----------------------------------------------------------------------
 * INDEX_SR
 *
 * rsr/wsr/xsr的索引包装器，根据提供的基名称和当前索引构造寄存器名称。使用方式如下：.set_idx，0 INDEX_SR rsr。比较a2
 *
 * 这产生：rsr。比较0 a2
 */
	.macro	INDEX_SR  instr ar
.ifeq (_idx)
	&instr&0	\ar
.endif
.ifeq (_idx-1)
	&instr&1	\ar
.endif
.ifeq (_idx-2)
	&instr&2	\ar
.endif
.ifeq (_idx-3)
	&instr&3	\ar
.endif
.ifeq (_idx-4)
	&instr&4	\ar
.endif
.ifeq (_idx-5)
	&instr&5	\ar
.endif
.ifeq (_idx-6)
	&instr&6	\ar
.endif
.ifeq (_idx-7)
	&instr&7	\ar
.endif
	.endm


/*----------------------------------------------------------------------
 *  防抱死制动系统
 *
 *  在未配置abs的机器上实施abs
 */

#if !XCHAL_HAVE_ABS
	.macro abs arr, ars
	.ifc \arr, \ars
	//src等于dest的效率较低
	bgez \arr, 1f
	neg \arr, \arr
1:
	.else
	neg \arr, \ars
	movgez \arr, \ars, \ars
	.endif
	.endm
#endif /* !XCHAL_HAVE_ABS */


/*----------------------------------------------------------------------
 *  加法x2
 *
 *  在未配置addx2的计算机上实现addx2
 *
 */

#if !XCHAL_HAVE_ADDX
	.macro addx2 arr, ars, art
	.ifc \arr, \art
	.ifc \arr, \ars
	// addx2 a，a，a（不常见）
	.err
	.else
	add \arr, \ars, \art
	add \arr, \ars, \art
	.endif
	.else
	//添加x2 a、b、c
	//添加x2 a、a、b
	//添加x2 a、b、b
	slli \arr, \ars, 1
	add  \arr, \arr, \art
	.endif
	.endm
#endif /* !XCHAL_HAVE_ADDX */

/*----------------------------------------------------------------------
 *  添加x4
 *
 *  在未配置addx4的计算机上实现addx4
 *
 */

#if !XCHAL_HAVE_ADDX
	.macro addx4 arr, ars, art
	.ifc \arr, \art
	.ifc \arr, \ars
	// addx4 a，a，a（不常用）
	 .err
	 .else
	//#添加x4 a、b、a
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	.endif
	.else
	//添加x4 a、b、c
	//添加x4 a、a、b
	//添加x4 a、b、b
	slli \arr, \ars, 2
	add  \arr, \arr, \art
	.endif
	.endm
#endif /* !XCHAL_HAVE_ADDX */

/*----------------------------------------------------------------------
 *  添加x8
 *
 *  在未配置addx8的计算机上实现addx8
 *
 */

#if !XCHAL_HAVE_ADDX
	.macro addx8 arr, ars, art
	.ifc \arr, \art
	.ifc \arr, \ars
	//addx8 a，a，a（不常见）
	.err
	.else
	//添加x8 a、b、a
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	add \arr, \ars, \art
	.endif
	.else
	//添加x8 a、b、c
	//添加x8 a、a、b
	//添加x8 a、b、b
	slli \arr, \ars, 3
	add  \arr, \arr, \art
	.endif
	.endm
#endif /* !XCHAL_HAVE_ADDX */


/*----------------------------------------------------------------------
 *  rfe_rfue
 *
 *  映射到XEA1上的RFUE和XEA2上的RFE。XEAX上没有映射。
 */

#if XCHAL_HAVE_XEA1
	.macro	rfe_rfue
	rfue
	.endm
#elif XCHAL_HAVE_XEA2
	.macro	rfe_rfue
	rfe
	.endm
#endif


/*----------------------------------------------------------------------
 *  abi_入口
 *
 *  为当前ABI生成正确的函数输入序列（windowed或call0）。如有必要，负责分配堆栈空间（最多1kB）并保存返回的PC。相应的abi_return宏执行相应的堆栈释放和恢复返回PC。
 *
 *  参数包括：
 *
 *	locsize		Number 要在堆栈上为本地变量分配的字节数（以及传递给被调用者的参数，如果进行了任何调用）。默认为零。宏将其舍入为16的倍数。注意：允许使用大值（例如，最多1 GB）。
 *
 *	callsize	Maximum 此函数的调用大小。叶函数为零（默认值），即如果此函数不调用其他函数。否则，必须根据所做的“最大”调用是调用[x]4、调用[x]8还是调用[x]12，将其设置为4、8或12（对于call0 ABI，这是设置为4，8还是12没有区别，但必须设置为这些值之一）。
 *
 *  注意：由调用者来对齐入口点、声明函数符号、使其全局化等。
 *
 *  注意：对于较大的locsize值，此宏依赖于汇编器松弛。它可能不适用于no transform指令。注意：对于call0 ABI，此宏确保SP被干净地分配或取消分配，即不会临时分配太多（或负分配！）由于addi松弛。
 *
 *  注意：为以独立于ABI的方式进行调用生成正确的序列和寄存器分配是本宏未涉及的单独主题。
 *
 *  注意：要访问参数，不能使用SP的固定偏移量。偏移量取决于ABI、函数是否为叶等。最简单的方法可能是使用.locsz符号，该符号由此宏设置为堆栈上分配的实际字节数，换句话说，为SP到参数的偏移量。E、 g.对于一个参数都是32位整数的函数，可以使用：l32i a2，sp，.locsz l32i a3，sp，/locsz+4获得第7个和第8个参数（第一个和第二个参数存储在堆栈中）（只要locsize低于l32i的偏移限制1020减去ABI特定堆栈使用的最多48个字节，这个示例就可以工作；否则您可能首先需要执行“addi a？，sp，.locsz”或类似的序列）。
 *
 *  注意：对于call0 ABI，此宏（和ABI_return）可能会删除a9（调用方保存的寄存器）。
 *
 *  示例：abi_entry abi_entry5 abi_entry22，8 abi_entry10，4
 */

	/*
	 *  在不发出任何指令的情况下计算.locsz和.callsz。由abi_entry和abi_return使用。假设位置大小>=0。
	 */
	.macro	abi_entry_size locsize=0, callsize=0
#if XCHAL_HAVE_WINDOWED && !__XTENSA_CALL0_ABI__
	.ifeq	\callsize
	 .set	.callsz, 16
	.else
	 .ifeq	\callsize-4
	  .set	.callsz, 16
	 .else
	  .ifeq	\callsize-8
	   .set	.callsz, 32
	  .else
	   .ifeq \callsize-12
	    .set .callsz, 48
	   .else
	    .error	"abi_entry: invalid call size \callsize"
	   .endif
	  .endif
	 .endif
	.endif
	.set	.locsz, .callsz + ((\locsize + 15) & -16)
#else
	.set	.callsz, \callsize
	.if	.callsz		/* 如果调用，则需要返回PC的空间*/
	 .set	.locsz, (\locsize + 4 + 15) & -16
	.else
	 .set	.locsz, (\locsize + 15) & -16
	.endif
#endif
	.endm

	.macro abi_entry locsize=0, callsize=0
	.iflt	\locsize
	 .error	"abi_entry: invalid negative size of locals (\locsize)"
	.endif
	abi_entry_size	\locsize, \callsize
#if XCHAL_HAVE_WINDOWED && !__XTENSA_CALL0_ABI__
# define ABI_ENTRY_MINSIZE	3	/* abi_entry（无参数）指令的大小（字节）*/
	.ifgt	.locsz - 32760	/* .locsz>32760（入口的最大范围）？*/
	/*  尽可能让汇编器高效地使用addmi的有趣计算：*/
	entry	sp, 0x7F00 + (.locsz & 0xF0)
	addi	a12, sp, - ((.locsz & -0x100) - 0x7F00)
	movsp	sp, a12
	.else
	entry	sp, .locsz
	.endif
#else
# define ABI_ENTRY_MINSIZE	0	/* abi_entry（无参数）指令的大小（字节）*/
	.if	.locsz
	 .ifle	.locsz - 128	/* 如果locsz<=128*/
	addi	sp, sp, -.locsz
	  .if	.callsz
	s32i	a0, sp, .locsz - 4
	  .endif
	 .elseif  .callsz	/* locsz>128，电话：*/
	movi	a9, .locsz - 16		/* 注意：a9已保存呼叫方*/
	addi	sp, sp, -16
	s32i	a0, sp, 12
	sub	sp, sp, a9
	 .else			/* locsz>128，无呼叫：*/
	movi	a9, .locsz
	sub	sp, sp, a9
	 .endif			/* 终止*/
	.endif
#endif
	.endm



/*----------------------------------------------------------------------
 *  abi_返回
 *
 *  为当前ABI生成正确的函数退出序列（windowed或call0）。如有必要，请释放堆栈空间并恢复返回的PC。注意：必须在相应的abi_entry宏调用之后调用此宏。特别是对于call0 ABI，所有堆栈和PC恢复都是根据程序集文件中该宏之前调用的最后一个ABI_entry宏完成的。
 *
 *  通常，此宏不带参数。然而，为了允许将abi_return放在abi_entry之前（对于某些高度优化的程序集必须这样做），它可以选择使用与abi_entr完全相同的参数。
 */

	.macro abi_return	locsize=-1, callsize=0
	.ifge	\locsize
	abi_entry_size	\locsize, \callsize
	.endif
#if XCHAL_HAVE_WINDOWED && !__XTENSA_CALL0_ABI__
	retw
#else
	.if	.locsz
	 .iflt	.locsz - 128	/* 如果locsz<128*/
	  .if	.callsz
	l32i	a0, sp, .locsz - 4
	  .endif
	addi	sp, sp, .locsz
	 .elseif  .callsz	/* locsz>=128，呼叫：*/
	addi	a9, sp, .locsz - 16
	l32i	a0, a9, 12
	addi	sp, a9, 16
	 .else			/* locsz>=128，无呼叫：*/
	movi	a9, .locsz
	add	sp, sp, a9
	 .endif			/* 终止*/
	.endif
	ret
#endif
	.endm


/*
 * 硬件错误修复。
 */

	.macro hw_erratum_487_fix
#if defined XSHAL_ERRATUM_487_FIX
	isync
#endif
	.endm

/*
 * 这些宏是内部的，可能会更改，不应在任何新代码中使用。
 */

#define _GBL(x)    .global x
#define _TYP(x)    .type x,@function
#define _ALN(x)    .align x
#define _SIZ(x)    .size x, . - x
#define _MKEND(x)  .purgem endfunc ; .macro endfunc ; _SIZ(x) ; .purgem endfunc ; .macro endfunc ; .endm ; .endm
#define _SYMT(x)   _GBL(x); _MKEND(x); _TYP(x); _ALN(4); x:
#define _SYM2(x)   _GBL(x); _TYP(x); x:
#define _SYM(x)   _GBL(x); _MKEND(x); _ALN(4); x:
.macro endfunc ; .endm

/*
 * DECLFUNC（）宏提供了一种用单个代码副本实现标准和_nw接口的机制。
 *
 * 对于Call0 ABI，有一个函数定义用xthal_…_nw和xthal_..符号标记。
 *
 * 对于窗口ABI，涉及两个编译（一个定义了__NW_FUNCTION_符号），导致两个单独的函数（_NW个没有窗口调整）。
*/

#if defined(__NW_FUNCTION__)
# define DECLFUNC(x) _SYMT(x ## _nw)
#else
# if defined (__XTENSA_CALL0_ABI__)
#  define DECLFUNC(x)  _SYMT(x); _SYM2(x ## _nw)
# else
#  define DECLFUNC(x)  _SYMT(x)
# endif
#endif

#endif /*XTENSA_COREASM_H*/

