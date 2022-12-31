/*
 * 领带asm。h——编译时HAL汇编程序定义，取决于CORE和TIE
 *
 *  注意：此头文件不应直接包含。
 */

/* 此头文件包含此特定Xtensa处理器的TIE扩展名和选项的汇编语言定义（汇编宏等）。它是根据Xtensa处理器配置定制的。

   版权所有（c）1999-2018 Cadence Design Systems Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef _XTENSA_CORE_TIE_ASM_H
#define _XTENSA_CORE_TIE_ASM_H

#ifdef __cplusplus
extern "C" {
#endif

/*  保存区域保存/恢复宏的选择参数值：*/
/*  期权与TIE：*/
#define XTHAL_SAS_TIE	0x0001	/* 自定义扩展或协处理器*/
#define XTHAL_SAS_OPT	0x0002	/* 可选（而不是协处理器）*/
#define XTHAL_SAS_ANYOT	0x0003	/* 以上两项*/
/*  编译器是否自动使用：*/
#define XTHAL_SAS_NOCC	0x0004	/* 编译器不使用特殊选项/代码*/
#define XTHAL_SAS_CC	0x0008	/* 由编译器使用，无需特殊opts/code*/
#define XTHAL_SAS_ANYCC	0x000C	/* 以上两项*/
/*  跨函数调用的ABI处理：*/
#define XTHAL_SAS_CALR	0x0010	/* 呼叫方已保存*/
#define XTHAL_SAS_CALE	0x0020	/* 被呼叫方已保存*/
#define XTHAL_SAS_GLOB	0x0040	/* 全局跨函数调用（线程中）*/
#define XTHAL_SAS_ANYABI	0x0070	/* 以上三项*/
/*  其他*/
#define XTHAL_SAS_ALL	0xFFFF	/* 包括所有默认NCP内容*/
#define XTHAL_SAS3(optie,ccuse,abi)	( ((optie) & XTHAL_SAS_ANYOT)  \
					| ((ccuse) & XTHAL_SAS_ANYCC)  \
					| ((abi)   & XTHAL_SAS_ANYABI) )


    /*
      *  用于存储所有非协处理器（额外）自定义TIE和可选状态（不包括零开销循环寄存器）的宏。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含一个4字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_NCP_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数：continue如果宏作为较大存储序列的一部分调用，如果这不是序列中的第一个，则设置为1。默认值为0.ofs从要存储的较大序列（从序列中第一个指针的值）开始的偏移。默认为下一个可用空间（如果<continue>为0，则为0）。选择选择要存储的寄存器类别，作为位掩码（请参阅XTHAL_SAS_xxx常量）。默认为所有寄存器。alloc选择要分配的寄存器类别；如果此处选择了不在<select>中的任何类别，则跳过相应寄存器的空间，而不进行任何存储。
      */
    .macro xchal_ncp_store  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start	\continue, \ofs
	// 编译器默认使用的可选全局寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\select)
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	rur.THREADPTR	\at1		// threadptr选项
	s32i	\at1, \ptr, .Lxchal_ofs_+0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endif
    .endm	// xchal_ncp_存储

    /*
      *  宏加载所有非协处理器（额外）自定义TIE和可选状态（不包括零开销循环寄存器）。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含一个4字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_NCP_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数：continue如果宏作为较大加载序列的一部分调用，如果这不是序列中的第一个，则设置为1。默认值为从要加载的较大序列（从序列中第一个指针的值）开始的0.ofs偏移。默认为下一个可用空间（如果<continue>为0，则为0）。选择选择要加载的寄存器类别作为位掩码（请参阅XTHAL_SAS_xxx常量）。默认为所有寄存器。alloc选择要分配的寄存器类别；如果此处选择了不在<select>中的任何类别，则跳过相应寄存器的空间，而不进行任何加载。
      */
    .macro xchal_ncp_load  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start	\continue, \ofs
	// 编译器默认使用的可选全局寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\select)
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	l32i	\at1, \ptr, .Lxchal_ofs_+0
	wur.THREADPTR	\at1		// threadptr选项
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endif
    .endm	// xchal_ncp_负载


#define XCHAL_NCP_NUM_ATMPS	1

#define XCHAL_SA_NUM_ATMPS	1

#ifdef __cplusplus
}
#endif

#endif /*_XTENSA_CORE_TIE_ASM_H*/

