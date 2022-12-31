/*  xtruntime帧。h-单线程运行时的异常堆栈帧*/
/* $Id://depot/rel/Foxhill/dot.9/Xtensa/OS/include/Xtensa/xruntime-frames。小时#1$*/

/*
 * 版权所有（c）2002-2012 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _XTRUNTIME_FRAMES_H_
#define _XTRUNTIME_FRAMES_H_

#include <xtensa/config/core.h>

/*  帮助定义C和汇编程序结构的宏：*/
#if defined(_ASMLANGUAGE) || defined(__ASSEMBLER__)
#define STRUCT_BEGIN		.pushsection .text; .struct 0
#define STRUCT_FIELD(ctype,size,pre,name)	pre##name:	.space	size
#define STRUCT_AFIELD(ctype,size,pre,name,n)	pre##name:	.if n ; .space	(size)*(n) ; .endif
#define STRUCT_AFIELD_A(ctype,size,align,pre,name,n)	.balign align ; pre##name:	.if n ; .space (size)*(n) ; .endif
#define STRUCT_END(sname)	sname##Size:; .popsection
#else /*_ASMLANGUAGE||__ASSEMBLER__*/
#define STRUCT_BEGIN		typedef struct {
#define STRUCT_FIELD(ctype,size,pre,name)	ctype	name;
#define STRUCT_AFIELD(ctype,size,pre,name,n)	ctype	name[n];
#define STRUCT_AFIELD_A(ctype,size,align,pre,name,n)	ctype	name[n] __attribute__((aligned(align)));
#define STRUCT_END(sname)	} sname;
#endif /*_ASMLANGUAGE||__ASSEMBLER__*/


/*
 *  内核向量模式异常堆栈帧。
 *
 *  注意：由于当前内核异常向量中使用的addi范围有限，而且历史上向量限制为12字节，因此堆栈帧的大小限制为128字节（当前为64字节）。
 */
STRUCT_BEGIN
STRUCT_FIELD (long,4,KEXC_,pc)		/* “parm”*/
STRUCT_FIELD (long,4,KEXC_,ps)
STRUCT_AFIELD(long,4,KEXC_,areg, 4)	/* a12…a15*/
STRUCT_FIELD (long,4,KEXC_,sar)		/* “保存”*/
#if XCHAL_HAVE_LOOPS
STRUCT_FIELD (long,4,KEXC_,lcount)
STRUCT_FIELD (long,4,KEXC_,lbeg)
STRUCT_FIELD (long,4,KEXC_,lend)
#endif
#if XCHAL_HAVE_MAC16
STRUCT_FIELD (long,4,KEXC_,acclo)
STRUCT_FIELD (long,4,KEXC_,acchi)
STRUCT_AFIELD(long,4,KEXC_,mr, 4)
#endif
STRUCT_END(KernelFrame)


/*
 *  用户矢量模式异常堆栈帧：
 *
 *  警告：如果修改此结构，则必须相应地修改焊盘尺寸（ALIGNPAD）的计算。
 */
STRUCT_BEGIN
STRUCT_FIELD (long,4,UEXC_,pc)
STRUCT_FIELD (long,4,UEXC_,ps)
STRUCT_FIELD (long,4,UEXC_,sar)
STRUCT_FIELD (long,4,UEXC_,vpri)
#ifdef __XTENSA_CALL0_ABI__
STRUCT_FIELD (long,4,UEXC_,a0)
#endif
STRUCT_FIELD (long,4,UEXC_,a2)
STRUCT_FIELD (long,4,UEXC_,a3)
STRUCT_FIELD (long,4,UEXC_,a4)
STRUCT_FIELD (long,4,UEXC_,a5)
#ifdef __XTENSA_CALL0_ABI__
STRUCT_FIELD (long,4,UEXC_,a6)
STRUCT_FIELD (long,4,UEXC_,a7)
STRUCT_FIELD (long,4,UEXC_,a8)
STRUCT_FIELD (long,4,UEXC_,a9)
STRUCT_FIELD (long,4,UEXC_,a10)
STRUCT_FIELD (long,4,UEXC_,a11)
STRUCT_FIELD (long,4,UEXC_,a12)
STRUCT_FIELD (long,4,UEXC_,a13)
STRUCT_FIELD (long,4,UEXC_,a14)
STRUCT_FIELD (long,4,UEXC_,a15)
#endif
STRUCT_FIELD (long,4,UEXC_,exccause)	/* 注意：可能可以去掉这个（直接传递）*/
#if XCHAL_HAVE_LOOPS
STRUCT_FIELD (long,4,UEXC_,lcount)
STRUCT_FIELD (long,4,UEXC_,lbeg)
STRUCT_FIELD (long,4,UEXC_,lend)
#endif
#if XCHAL_HAVE_MAC16
STRUCT_FIELD (long,4,UEXC_,acclo)
STRUCT_FIELD (long,4,UEXC_,acchi)
STRUCT_AFIELD(long,4,UEXC_,mr, 4)
#endif
/* ALIGNPAD是16字节对齐填充。*/
#ifdef __XTENSA_CALL0_ABI__
# define CALL0_ABI	1
#else
# define CALL0_ABI	0
#endif
#define ALIGNPAD  ((3 + XCHAL_HAVE_LOOPS*1 + XCHAL_HAVE_MAC16*2 + CALL0_ABI*1) & 3)
#if ALIGNPAD
STRUCT_AFIELD(long,4,UEXC_,pad, ALIGNPAD)	/* 16字节对齐填充*/
#endif
/*STRUCT_FIELD_A（字符，1，XCHAL_CPEXTRA_SA_ALIGN，UEXC_，ureg，（XCHAL_CPE XTRA_SE_SIZE+3）&-4）*/	/* 未使用*/
STRUCT_END(UserFrame)


#if defined(_ASMLANGUAGE) || defined(__ASSEMBLER__)


/*  检查UserFrameSize是否足够小，不需要舍入…：*/
	/*  跳过16字节的保存区域，然后为8个调用寄存器12（与16字节GCC嵌套函数链接区域重叠）跳过32字节的空间，然后跳过异常堆栈帧：*/
	.set	UserFrameTotalSize, 16+32+UserFrameSize
	/*  大于112字节？（当对齐到16字节时，两个符号的ADDI的最大范围）：*/
	.ifgt	UserFrameTotalSize-112
	/*  四舍五入到256字节的倍数以加速立即相加：*/
	.set	UserFrameTotalSize, ((UserFrameTotalSize+255) & 0xFFFFFF00)
	.endif
# define ESF_TOTALSIZE	UserFrameTotalSize

#endif /* _ASMLANGUAGE || __ASSEMBLER__ */


#if XCHAL_NUM_CONTEXTS > 1
/*  存储在新上下文堆栈中用于安装的信息结构：*/
STRUCT_BEGIN
STRUCT_FIELD (long,4,INFO_,sp)
STRUCT_FIELD (long,4,INFO_,arg1)
STRUCT_FIELD (long,4,INFO_,funcpc)
STRUCT_FIELD (long,4,INFO_,prevps)
STRUCT_END(SetupInfo)
#endif


#define KERNELSTACKSIZE	1024


#endif /* _XTRUNTIME_FRAMES_H_ */

