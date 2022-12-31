/*  xtruntime核心状态。h-核心状态保存区域（例如由PSO使用）*/
/* $Id://depot/rel/Foxhill/dot.9/Xtensa/OS/include/xxtensa/xtruntime-core-state。小时#1$*/

/*
 * 版权所有（c）2012-2013 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _XTOS_CORE_STATE_H_
#define _XTOS_CORE_STATE_H_

/*  导入STRUCT_xx宏以定义结构：*/
#include <xtensa/xtruntime-frames.h>
#include <xtensa/config/core.h>
#include <xtensa/config/tie.h>
#if XCHAL_HAVE_IDMA
#include <xtensa/idma.h>
#endif

//#define XTOS_PSO_TEST 1//仅针对内部PSO测试取消注释

#define CORE_STATE_SIGNATURE	0xB1C5AFED	// 指示状态已保存的模式


/*
 *  保存区域以保存整个核心状态，例如通过电源关闭（PSO）。
 */

STRUCT_BEGIN
STRUCT_FIELD (long,4,CS_SA_,signature)		// 用于检查状态是否已保存
STRUCT_FIELD (long,4,CS_SA_,restore_label)
STRUCT_FIELD (long,4,CS_SA_,aftersave_label)
STRUCT_AFIELD(long,4,CS_SA_,areg,XCHAL_NUM_AREGS)
#if XCHAL_HAVE_WINDOWED
STRUCT_AFIELD(long,4,CS_SA_,caller_regs,16)	// 最多保存16个呼叫者寄存器
STRUCT_FIELD (long,4,CS_SA_,caller_regs_saved)  // 显示调用方是否已保存的标志
#endif
#if XCHAL_HAVE_PSO_CDM
STRUCT_FIELD (long,4,CS_SA_,pwrctl)
#endif
#if XCHAL_HAVE_WINDOWED
STRUCT_FIELD (long,4,CS_SA_,windowbase)
STRUCT_FIELD (long,4,CS_SA_,windowstart)
#endif
STRUCT_FIELD (long,4,CS_SA_,sar)
#if XCHAL_HAVE_EXCEPTIONS
STRUCT_FIELD (long,4,CS_SA_,epc1)
STRUCT_FIELD (long,4,CS_SA_,ps)
STRUCT_FIELD (long,4,CS_SA_,excsave1)
# ifdef XCHAL_DOUBLEEXC_VECTOR_VADDR
STRUCT_FIELD (long,4,CS_SA_,depc)
# endif
#endif
#if XCHAL_NUM_INTLEVELS + XCHAL_HAVE_NMI >= 2
STRUCT_AFIELD(long,4,CS_SA_,epc,    XCHAL_NUM_INTLEVELS + XCHAL_HAVE_NMI - 1)
STRUCT_AFIELD(long,4,CS_SA_,eps,    XCHAL_NUM_INTLEVELS + XCHAL_HAVE_NMI - 1)
STRUCT_AFIELD(long,4,CS_SA_,excsave,XCHAL_NUM_INTLEVELS + XCHAL_HAVE_NMI - 1)
#endif
#if XCHAL_HAVE_LOOPS
STRUCT_FIELD (long,4,CS_SA_,lcount)
STRUCT_FIELD (long,4,CS_SA_,lbeg)
STRUCT_FIELD (long,4,CS_SA_,lend)
#endif
#if XCHAL_HAVE_ABSOLUTE_LITERALS
STRUCT_FIELD (long,4,CS_SA_,litbase)
#endif
#if XCHAL_HAVE_VECBASE
STRUCT_FIELD (long,4,CS_SA_,vecbase)
#endif
#if XCHAL_HAVE_S32C1I && (XCHAL_HW_MIN_VERSION >= XTENSA_HWVERSION_RC_2009_0)	/* 有ATOMCTL吗？*/
STRUCT_FIELD (long,4,CS_SA_,atomctl)
#endif
#if XCHAL_HAVE_PREFETCH
STRUCT_FIELD (long,4,CS_SA_,prefctl)
#endif
#if XCHAL_USE_MEMCTL
STRUCT_FIELD (long,4,CS_SA_,memctl)
#endif
#if XCHAL_HAVE_CCOUNT
STRUCT_FIELD (long,4,CS_SA_,ccount)
STRUCT_AFIELD(long,4,CS_SA_,ccompare, XCHAL_NUM_TIMERS)
#endif
#if XCHAL_HAVE_INTERRUPTS
STRUCT_FIELD (long,4,CS_SA_,intenable)
STRUCT_FIELD (long,4,CS_SA_,interrupt)
#endif
#if XCHAL_HAVE_DEBUG
STRUCT_FIELD (long,4,CS_SA_,icount)
STRUCT_FIELD (long,4,CS_SA_,icountlevel)
STRUCT_FIELD (long,4,CS_SA_,debugcause)
// DDR未保存
# if XCHAL_NUM_DBREAK
STRUCT_AFIELD(long,4,CS_SA_,dbreakc, XCHAL_NUM_DBREAK)
STRUCT_AFIELD(long,4,CS_SA_,dbreaka, XCHAL_NUM_DBREAK)
# endif
# if XCHAL_NUM_IBREAK
STRUCT_AFIELD(long,4,CS_SA_,ibreaka, XCHAL_NUM_IBREAK)
STRUCT_FIELD (long,4,CS_SA_,ibreakenable)
# endif
#endif
#if XCHAL_NUM_MISC_REGS
STRUCT_AFIELD(long,4,CS_SA_,misc,XCHAL_NUM_MISC_REGS)
#endif
#if XCHAL_HAVE_MEM_ECC_PARITY
STRUCT_FIELD (long,4,CS_SA_,mepc)
STRUCT_FIELD (long,4,CS_SA_,meps)
STRUCT_FIELD (long,4,CS_SA_,mesave)
STRUCT_FIELD (long,4,CS_SA_,mesr)
STRUCT_FIELD (long,4,CS_SA_,mecr)
STRUCT_FIELD (long,4,CS_SA_,mevaddr)
#endif

/*  我们将其置于TLB和其他TIE状态之前，以将其保持在S32I/L32I偏移范围内。*/
#if XCHAL_HAVE_CP
STRUCT_FIELD (long,4,CS_SA_,cpenable)
#endif

/*  TLB状态*/
#if XCHAL_HAVE_MIMIC_CACHEATTR || XCHAL_HAVE_XLT_CACHEATTR
STRUCT_AFIELD(long,4,CS_SA_,tlbs,8*2)
#endif
#if XCHAL_HAVE_PTP_MMU
/*  将自动重新填充（ARF）条目的数量计算为I和D的最大值，以简化TLB保存逻辑。在ITLB ARF！=的异常配置上DTLB ARF条目，我们只会冗余地保存/恢复一些额外的条目。*/
#  if XCHAL_DTLB_ARF_ENTRIES_LOG2 + XCHAL_ITLB_ARF_ENTRIES_LOG2 > 4
#   define ARF_ENTRIES	8
#  else
#   define ARF_ENTRIES	4
#  endif
STRUCT_FIELD (long,4,CS_SA_,ptevaddr)
STRUCT_FIELD (long,4,CS_SA_,rasid)
STRUCT_FIELD (long,4,CS_SA_,dtlbcfg)
STRUCT_FIELD (long,4,CS_SA_,itlbcfg)
/***警告：超过此点，场偏移可能大于S32I/L32I范围***/
STRUCT_AFIELD(long,4,CS_SA_,tlbs,((4*ARF_ENTRIES+4)*2+3)*2)
# if XCHAL_HAVE_SPANNING_WAY	/* MMU v3*/
STRUCT_AFIELD(long,4,CS_SA_,tlbs_ways56,(4+8)*2*2)
# endif
#endif
/* MPU状态*/
#if XCHAL_HAVE_MPU
STRUCT_AFIELD(long,4,CS_SA_,mpuentry,8*XCHAL_MPU_ENTRIES)
STRUCT_FIELD (long,4,CS_SA_,cacheadrdis)
#endif

#if XCHAL_HAVE_IDMA
STRUCT_AFIELD(long,4,CS_SA_,idmaregs, IDMA_PSO_SAVE_SIZE)
#endif

/*  TIE状态*/
/*  注：NCP区域与XCHAL_TOTAL_SA_ALIGN对齐，而不是XCHAL_NCP_SA_ALIGN对齐，因为所有后续协处理器保存区域的偏移量都与NCP保存区域相关。*/
STRUCT_AFIELD_A(char,1,XCHAL_TOTAL_SA_ALIGN,CS_SA_,ncp,XCHAL_NCP_SA_SIZE)
#if XCHAL_HAVE_CP
#if XCHAL_CP0_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP0_SA_ALIGN,CS_SA_,cp0,XCHAL_CP0_SA_SIZE)
#endif
#if XCHAL_CP1_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP1_SA_ALIGN,CS_SA_,cp1,XCHAL_CP1_SA_SIZE)
#endif
#if XCHAL_CP2_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP2_SA_ALIGN,CS_SA_,cp2,XCHAL_CP2_SA_SIZE)
#endif
#if XCHAL_CP3_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP3_SA_ALIGN,CS_SA_,cp3,XCHAL_CP3_SA_SIZE)
#endif
#if XCHAL_CP4_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP4_SA_ALIGN,CS_SA_,cp4,XCHAL_CP4_SA_SIZE)
#endif
#if XCHAL_CP5_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP5_SA_ALIGN,CS_SA_,cp5,XCHAL_CP5_SA_SIZE)
#endif
#if XCHAL_CP6_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP6_SA_ALIGN,CS_SA_,cp6,XCHAL_CP6_SA_SIZE)
#endif
#if XCHAL_CP7_SA_SIZE > 0
STRUCT_AFIELD_A(char,1,XCHAL_CP7_SA_ALIGN,CS_SA_,cp7,XCHAL_CP7_SA_SIZE)
#endif
//STRUCT_FIELD_A（字符，1，XCHAL_CP8_SA_ALIGN，CS_SA_，CP8，XCHAL-CP8_SA_SIZE）
//STRUCT_FIELD_A（字符，1，XCHAL_CP9_SA_ALIGN，CS_SA_，CP9，XCHAL-CP9_SA_SIZE）
//STRUCT_FIELD_A（字符，1，XCHAL_CP10_SA_ALIGN，CS_SA_，CP10，XCHAL-CP10_SA_SIZE）
//结构_AFIELD_A（字符，1，XCHAL_CP11_SA_ALIGN，CS_SA_，CP11，XCHAL-CP11_SA_SIZE）
//STRUCT_FIELD_A（字符，1，XCHAL_CP12_SA_ALIGN，CS_SA_，CP12，XCHAL-CP12_SA_SIZE）
//STRUCT_FIELD_A（字符，1，XCHAL_CP13_SA_ALIGN，CS_SA_，CP13，XCHAL-CP13_SA_SIZE）
//STRUCT_FIELD_A（字符，1，XCHAL_CP14_SA_ALIGN，CS_SA_，CP14，XCHAL-CP14_SA_SIZE）
//STRUCT_FIELD_A（字符，1，XCHAL_CP15_SA_ALIGN，CS_SA_，CP15，XCHAL-CP15_SA_SIZE）
#endif

STRUCT_END(XtosCoreState)



//  这些是非协处理器状态（ncp）的一部分：
#if XCHAL_HAVE_MAC16
//STRUCT_FIELD（长，4，CS_SA_，acclo）
//STRUCT_FIELD（长，4，CS_SA_，acchi）
//STRUCT_AFIELD（长，4，CS_SA_，mr，4）
#endif
#if XCHAL_HAVE_THREADPTR
//STRUCT_FIELD（长，4，CS_SA_，threadptr）
#endif
#if XCHAL_HAVE_S32C1I
//STRUCT_FIELD（长，4，CS_SA_，短1）
#endif
#if XCHAL_HAVE_BOOLEANS
//STRUCT_FIELD（长，4，CS_SA_，br）
#endif

//  未保存：
//	EXCCAUSE ??
//	DEBUGCAUSE ??
//	EXCVADDR ??
//	DDR
//	INTERRUPT
//…锁定的缓存线。。。

#endif /* _XTOS_CORE_STATE_H_ */

