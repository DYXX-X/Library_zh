/*
 * extensa/config/core。h——取决于CORE配置的HAL定义
 *
 *  这个头文件有时被称为“编译时HAL”或CHAL。它提取针对特定Xtensa处理器配置定制的定义。
 *
 *  二进制文件的源通常不包含此文件（它们可能使用特定于配置的HAL库）。HAL库源本身包含此文件是正常的。
 */

/*
 * 版权所有（c）2005-2015 Cadence Design Systems，Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef XTENSA_CONFIG_CORE_H
#define XTENSA_CONFIG_CORE_H

/*  CONFIGURATION INDEPENDENT DEFINITIONS:  */
#ifdef __XTENSA__
#include <xtensa/hal.h>
#include <xtensa/xtensa-versions.h>
#else
#include "../hal.h"
#include "../xtensa-versions.h"
#endif

/*  CONFIGURATION SPECIFIC DEFINITIONS:  */
#ifdef __XTENSA__
#include <xtensa/config/core-isa.h>
#include <xtensa/config/core-matmap.h>
#include <xtensa/config/tie.h>
#else
#include "core-isa.h"
#include "core-matmap.h"
#include "tie.h"
#endif

#if defined (_ASMLANGUAGE) || defined (__ASSEMBLER__)
#ifdef __XTENSA__
#include <xtensa/config/tie-asm.h>
#else
#include "tie-asm.h"
#endif
#endif /*_ASMLANGUAGE或__ASSEMBLER__*/

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------
				GENERAL
  ----------------------------------------------------------------------*/

/*
 *  展开为数组的宏的分隔符。当需要不同的分隔符时，可以通过#包含此分隔符的文件预定义这些分隔符。
 */
/*  扩展为一维数组的宏的元素分隔符：*/
#ifndef XCHAL_SEP
#define XCHAL_SEP			,
#endif
/*  展开为二维数组的宏的数组分隔符：*/
#ifndef XCHAL_SEP2
#define XCHAL_SEP2			},{
#endif


/*----------------------------------------------------------------------
                                ERRATA
  ----------------------------------------------------------------------*/

/*
 *  勘误表T1020.H13、T1030.H7、T1040.H10、T1050.H4（在T1040.3和T1050.1中已修复；仅在XEA1中相关，内核矢量模式，启用一级中断和溢出）：
 */
#define XCHAL_MAYHAVE_ERRATUM_XEA1KWIN  (XCHAL_HAVE_XEA1 && \
                                         (XCHAL_HW_RELEASE_AT_OR_BELOW(1040,2) != 0 \
                                          || XCHAL_HW_RELEASE_AT(1050,0)))
/*
 *  RE-2013.2至RF-2014.0中存在勘误表453，已在RF-2014.1中修复。适用于特定配置选项集。解决方法的一部分是在代码中的某些点添加ISYNC。如果不需要，可以通过定义_NO_ERRATUM_453禁用此宏门控的解决方法，例如，如果将禁用零开销循环缓冲区。
 */
#if (   XCHAL_HW_MAX_VERSION >= XTENSA_HWVERSION_RE_2013_2 && \
        XCHAL_HW_MIN_VERSION <= XTENSA_HWVERSION_RF_2014_0 && \
        XCHAL_ICACHE_SIZE != 0    && XCHAL_HAVE_PIF /*还包括AXI/AHB*/ && \
        XCHAL_HAVE_LOOPS          && XCHAL_LOOP_BUFFER_SIZE != 0 && \
        XCHAL_CLOCK_GATING_GLOBAL && !defined(_NO_ERRATUM_453) )
#define XCHAL_ERRATUM_453       1
#else
#define XCHAL_ERRATUM_453       0
#endif

/*
 *  RE-2012.2至RG/RF-2015.2中的勘误表497适用于特定配置选项集。解决方法是在最多8个缓存WB指令之后添加MEMW
 */
#if ( ((XCHAL_HW_MAX_VERSION >= XTENSA_HWVERSION_RE_2012_0 &&    \
        XCHAL_HW_MIN_VERSION <= XTENSA_HWVERSION_RF_2015_2) ||   \
       (XCHAL_HW_MAX_VERSION >= XTENSA_HWVERSION_RG_2015_0 &&    \
        XCHAL_HW_MIN_VERSION <= XTENSA_HWVERSION_RG_2015_2)     \
      ) && \
      XCHAL_DCACHE_IS_WRITEBACK && \
      XCHAL_HAVE_AXI && \
      XCHAL_HAVE_PIF_WR_RESP && \
      XCHAL_HAVE_PIF_REQ_ATTR &&  !defined(_NO_ERRATUM_497) \
    )
#define XCHAL_ERRATUM_497       1
#else
#define XCHAL_ERRATUM_497       0
#endif


/*----------------------------------------------------------------------
				ISA
  ----------------------------------------------------------------------*/

#if XCHAL_HAVE_BE
# define XCHAL_HAVE_LE			0
# define XCHAL_MEMORY_ORDER		XTHAL_BIGENDIAN
#else
# define XCHAL_HAVE_LE			1
# define XCHAL_MEMORY_ORDER		XTHAL_LITTLEENDIAN
#endif



/*----------------------------------------------------------------------
				INTERRUPTS
  ----------------------------------------------------------------------*/

/*  索引宏：*/
#define _XCHAL_INTLEVEL_MASK(n)		XCHAL_INTLEVEL ## n ## _MASK
#define XCHAL_INTLEVEL_MASK(n)		_XCHAL_INTLEVEL_MASK(n)		/* n=0..15*/
#define _XCHAL_INTLEVEL_ANDBELOWMASK(n)	XCHAL_INTLEVEL ## n ## _ANDBELOW_MASK
#define XCHAL_INTLEVEL_ANDBELOW_MASK(n)	_XCHAL_INTLEVEL_ANDBELOWMASK(n)	/* n=0..15*/
#define _XCHAL_INTLEVEL_NUM(n)		XCHAL_INTLEVEL ## n ## _NUM
#define XCHAL_INTLEVEL_NUM(n)		_XCHAL_INTLEVEL_NUM(n)		/* n=0..15*/
#define _XCHAL_INT_LEVEL(n)		XCHAL_INT ## n ## _LEVEL
#define XCHAL_INT_LEVEL(n)		_XCHAL_INT_LEVEL(n)		/* n=0..31*/
#define _XCHAL_INT_TYPE(n)		XCHAL_INT ## n ## _TYPE
#define XCHAL_INT_TYPE(n)		_XCHAL_INT_TYPE(n)		/* n=0..31*/
#define _XCHAL_TIMER_INTERRUPT(n)	XCHAL_TIMER ## n ## _INTERRUPT
#define XCHAL_TIMER_INTERRUPT(n)	_XCHAL_TIMER_INTERRUPT(n)	/* n=0..3*/


#define XCHAL_HAVE_HIGHLEVEL_INTERRUPTS	XCHAL_HAVE_HIGHPRI_INTERRUPTS
#define XCHAL_NUM_LOWPRI_LEVELS		1			/* 低优先级中断级别的数量（始终为1）*/
#define XCHAL_FIRST_HIGHPRI_LEVEL	(XCHAL_NUM_LOWPRI_LEVELS+1)	/* 第一个高优先级中断的级别（总是2）*/
/*  注：1<=LOWPRI_LEVELS<=EXCM_LEVEL<DEBUGLEVEL<=NUM_INTLEVELS<NMILEVEL<=15*/

/*  对于现有的Xtensa处理器实现，这些值是恒定的：*/
#define XCHAL_INTLEVEL0_MASK		0x00000000
#define XCHAL_INTLEVEL8_MASK		0x00000000
#define XCHAL_INTLEVEL9_MASK		0x00000000
#define XCHAL_INTLEVEL10_MASK		0x00000000
#define XCHAL_INTLEVEL11_MASK		0x00000000
#define XCHAL_INTLEVEL12_MASK		0x00000000
#define XCHAL_INTLEVEL13_MASK		0x00000000
#define XCHAL_INTLEVEL14_MASK		0x00000000
#define XCHAL_INTLEVEL15_MASK		0x00000000

/*  每个中断级别的中断掩码阵列：*/
#define XCHAL_INTLEVEL_MASKS		XCHAL_INTLEVEL0_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL1_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL2_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL3_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL4_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL5_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL6_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL7_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL8_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL9_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL10_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL11_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL12_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL13_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL14_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL15_MASK

/*  对于现有的Xtensa处理器实现，这些值是恒定的：*/
#define XCHAL_INTLEVEL0_ANDBELOW_MASK	0x00000000
#define XCHAL_INTLEVEL8_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL9_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL10_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL11_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL12_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL13_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL14_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK
#define XCHAL_INTLEVEL15_ANDBELOW_MASK	XCHAL_INTLEVEL7_ANDBELOW_MASK

/*  所有低优先级中断的掩码：*/
#define XCHAL_LOWPRI_MASK		XCHAL_INTLEVEL1_ANDBELOW_MASK

/*  PS.EXCM（或CEXCM）屏蔽的所有中断的屏蔽：*/
#define XCHAL_EXCM_MASK			XCHAL_INTLEVEL_ANDBELOW_MASK(XCHAL_EXCM_LEVEL)

/*  中断级别的每个1..n范围内的中断掩码阵列：*/
#define XCHAL_INTLEVEL_ANDBELOW_MASKS	XCHAL_INTLEVEL0_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL1_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL2_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL3_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL4_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL5_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL6_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL7_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL8_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL9_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL10_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL11_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL12_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL13_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL14_ANDBELOW_MASK \
			XCHAL_SEP	XCHAL_INTLEVEL15_ANDBELOW_MASK

#if 0 /*XCHAL_HAVE_NMI*/
/*  NMI“中断级别”（用于EXCSAVE_n、EPS_n、EPC_n、RFI n）：*/
# define XCHAL_NMILEVEL		(XCHAL_NUM_INTLEVELS+1)
#endif

/*  每个可能中断的级别阵列：*/
#define XCHAL_INT_LEVELS		XCHAL_INT0_LEVEL \
			XCHAL_SEP	XCHAL_INT1_LEVEL \
			XCHAL_SEP	XCHAL_INT2_LEVEL \
			XCHAL_SEP	XCHAL_INT3_LEVEL \
			XCHAL_SEP	XCHAL_INT4_LEVEL \
			XCHAL_SEP	XCHAL_INT5_LEVEL \
			XCHAL_SEP	XCHAL_INT6_LEVEL \
			XCHAL_SEP	XCHAL_INT7_LEVEL \
			XCHAL_SEP	XCHAL_INT8_LEVEL \
			XCHAL_SEP	XCHAL_INT9_LEVEL \
			XCHAL_SEP	XCHAL_INT10_LEVEL \
			XCHAL_SEP	XCHAL_INT11_LEVEL \
			XCHAL_SEP	XCHAL_INT12_LEVEL \
			XCHAL_SEP	XCHAL_INT13_LEVEL \
			XCHAL_SEP	XCHAL_INT14_LEVEL \
			XCHAL_SEP	XCHAL_INT15_LEVEL \
			XCHAL_SEP	XCHAL_INT16_LEVEL \
			XCHAL_SEP	XCHAL_INT17_LEVEL \
			XCHAL_SEP	XCHAL_INT18_LEVEL \
			XCHAL_SEP	XCHAL_INT19_LEVEL \
			XCHAL_SEP	XCHAL_INT20_LEVEL \
			XCHAL_SEP	XCHAL_INT21_LEVEL \
			XCHAL_SEP	XCHAL_INT22_LEVEL \
			XCHAL_SEP	XCHAL_INT23_LEVEL \
			XCHAL_SEP	XCHAL_INT24_LEVEL \
			XCHAL_SEP	XCHAL_INT25_LEVEL \
			XCHAL_SEP	XCHAL_INT26_LEVEL \
			XCHAL_SEP	XCHAL_INT27_LEVEL \
			XCHAL_SEP	XCHAL_INT28_LEVEL \
			XCHAL_SEP	XCHAL_INT29_LEVEL \
			XCHAL_SEP	XCHAL_INT30_LEVEL \
			XCHAL_SEP	XCHAL_INT31_LEVEL

/*  每个可能中断的类型数组：*/
#define XCHAL_INT_TYPES			XCHAL_INT0_TYPE \
			XCHAL_SEP	XCHAL_INT1_TYPE \
			XCHAL_SEP	XCHAL_INT2_TYPE \
			XCHAL_SEP	XCHAL_INT3_TYPE \
			XCHAL_SEP	XCHAL_INT4_TYPE \
			XCHAL_SEP	XCHAL_INT5_TYPE \
			XCHAL_SEP	XCHAL_INT6_TYPE \
			XCHAL_SEP	XCHAL_INT7_TYPE \
			XCHAL_SEP	XCHAL_INT8_TYPE \
			XCHAL_SEP	XCHAL_INT9_TYPE \
			XCHAL_SEP	XCHAL_INT10_TYPE \
			XCHAL_SEP	XCHAL_INT11_TYPE \
			XCHAL_SEP	XCHAL_INT12_TYPE \
			XCHAL_SEP	XCHAL_INT13_TYPE \
			XCHAL_SEP	XCHAL_INT14_TYPE \
			XCHAL_SEP	XCHAL_INT15_TYPE \
			XCHAL_SEP	XCHAL_INT16_TYPE \
			XCHAL_SEP	XCHAL_INT17_TYPE \
			XCHAL_SEP	XCHAL_INT18_TYPE \
			XCHAL_SEP	XCHAL_INT19_TYPE \
			XCHAL_SEP	XCHAL_INT20_TYPE \
			XCHAL_SEP	XCHAL_INT21_TYPE \
			XCHAL_SEP	XCHAL_INT22_TYPE \
			XCHAL_SEP	XCHAL_INT23_TYPE \
			XCHAL_SEP	XCHAL_INT24_TYPE \
			XCHAL_SEP	XCHAL_INT25_TYPE \
			XCHAL_SEP	XCHAL_INT26_TYPE \
			XCHAL_SEP	XCHAL_INT27_TYPE \
			XCHAL_SEP	XCHAL_INT28_TYPE \
			XCHAL_SEP	XCHAL_INT29_TYPE \
			XCHAL_SEP	XCHAL_INT30_TYPE \
			XCHAL_SEP	XCHAL_INT31_TYPE

/*  每种中断类型的中断掩码阵列：*/
#define XCHAL_INTTYPE_MASKS		XCHAL_INTTYPE_MASK_UNCONFIGURED	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_SOFTWARE	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_EXTERN_EDGE	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_EXTERN_LEVEL	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_TIMER	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_NMI		\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_WRITE_ERROR	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_IDMA_DONE	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_IDMA_ERR	\
			XCHAL_SEP	XCHAL_INTTYPE_MASK_GS_ERR

/*  可使用INTCLEAR特殊寄存器清除的中断：*/
#define XCHAL_INTCLEARABLE_MASK	(XCHAL_INTTYPE_MASK_SOFTWARE+XCHAL_INTTYPE_MASK_EXTERN_EDGE+XCHAL_INTTYPE_MASK_WRITE_ERROR)
/*  可使用INTSET特殊寄存器触发的中断：*/
#define XCHAL_INTSETTABLE_MASK	XCHAL_INTTYPE_MASK_SOFTWARE

/*  分配给每个计时器的中断阵列（CCOMPARE0至CCOMPARE3）：*/
#define XCHAL_TIMER_INTERRUPTS		XCHAL_TIMER0_INTERRUPT \
			XCHAL_SEP	XCHAL_TIMER1_INTERRUPT \
			XCHAL_SEP	XCHAL_TIMER2_INTERRUPT \
			XCHAL_SEP	XCHAL_TIMER3_INTERRUPT



/*  为了向后兼容和数组宏，为每个未配置的中断号定义宏（不幸的是，XTHAL_INTTYPE_unconfigured的值不为零）：*/
#if XCHAL_NUM_INTERRUPTS == 0
# define XCHAL_INT0_LEVEL		0
# define XCHAL_INT0_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 1
# define XCHAL_INT1_LEVEL		0
# define XCHAL_INT1_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 2
# define XCHAL_INT2_LEVEL		0
# define XCHAL_INT2_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 3
# define XCHAL_INT3_LEVEL		0
# define XCHAL_INT3_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 4
# define XCHAL_INT4_LEVEL		0
# define XCHAL_INT4_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 5
# define XCHAL_INT5_LEVEL		0
# define XCHAL_INT5_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 6
# define XCHAL_INT6_LEVEL		0
# define XCHAL_INT6_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 7
# define XCHAL_INT7_LEVEL		0
# define XCHAL_INT7_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 8
# define XCHAL_INT8_LEVEL		0
# define XCHAL_INT8_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 9
# define XCHAL_INT9_LEVEL		0
# define XCHAL_INT9_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 10
# define XCHAL_INT10_LEVEL		0
# define XCHAL_INT10_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 11
# define XCHAL_INT11_LEVEL		0
# define XCHAL_INT11_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 12
# define XCHAL_INT12_LEVEL		0
# define XCHAL_INT12_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 13
# define XCHAL_INT13_LEVEL		0
# define XCHAL_INT13_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 14
# define XCHAL_INT14_LEVEL		0
# define XCHAL_INT14_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 15
# define XCHAL_INT15_LEVEL		0
# define XCHAL_INT15_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 16
# define XCHAL_INT16_LEVEL		0
# define XCHAL_INT16_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 17
# define XCHAL_INT17_LEVEL		0
# define XCHAL_INT17_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 18
# define XCHAL_INT18_LEVEL		0
# define XCHAL_INT18_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 19
# define XCHAL_INT19_LEVEL		0
# define XCHAL_INT19_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 20
# define XCHAL_INT20_LEVEL		0
# define XCHAL_INT20_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 21
# define XCHAL_INT21_LEVEL		0
# define XCHAL_INT21_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 22
# define XCHAL_INT22_LEVEL		0
# define XCHAL_INT22_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 23
# define XCHAL_INT23_LEVEL		0
# define XCHAL_INT23_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 24
# define XCHAL_INT24_LEVEL		0
# define XCHAL_INT24_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 25
# define XCHAL_INT25_LEVEL		0
# define XCHAL_INT25_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 26
# define XCHAL_INT26_LEVEL		0
# define XCHAL_INT26_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 27
# define XCHAL_INT27_LEVEL		0
# define XCHAL_INT27_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 28
# define XCHAL_INT28_LEVEL		0
# define XCHAL_INT28_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 29
# define XCHAL_INT29_LEVEL		0
# define XCHAL_INT29_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 30
# define XCHAL_INT30_LEVEL		0
# define XCHAL_INT30_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif
#if XCHAL_NUM_INTERRUPTS <= 31
# define XCHAL_INT31_LEVEL		0
# define XCHAL_INT31_TYPE		XTHAL_INTTYPE_UNCONFIGURED
#endif


/*
 *  每个*外部*中断对应的掩码和级别。
 */

#define XCHAL_EXTINT0_MASK		(1 << XCHAL_EXTINT0_NUM)
#define XCHAL_EXTINT0_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT0_NUM)
#define XCHAL_EXTINT1_MASK		(1 << XCHAL_EXTINT1_NUM)
#define XCHAL_EXTINT1_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT1_NUM)
#define XCHAL_EXTINT2_MASK		(1 << XCHAL_EXTINT2_NUM)
#define XCHAL_EXTINT2_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT2_NUM)
#define XCHAL_EXTINT3_MASK		(1 << XCHAL_EXTINT3_NUM)
#define XCHAL_EXTINT3_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT3_NUM)
#define XCHAL_EXTINT4_MASK		(1 << XCHAL_EXTINT4_NUM)
#define XCHAL_EXTINT4_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT4_NUM)
#define XCHAL_EXTINT5_MASK		(1 << XCHAL_EXTINT5_NUM)
#define XCHAL_EXTINT5_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT5_NUM)
#define XCHAL_EXTINT6_MASK		(1 << XCHAL_EXTINT6_NUM)
#define XCHAL_EXTINT6_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT6_NUM)
#define XCHAL_EXTINT7_MASK		(1 << XCHAL_EXTINT7_NUM)
#define XCHAL_EXTINT7_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT7_NUM)
#define XCHAL_EXTINT8_MASK		(1 << XCHAL_EXTINT8_NUM)
#define XCHAL_EXTINT8_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT8_NUM)
#define XCHAL_EXTINT9_MASK		(1 << XCHAL_EXTINT9_NUM)
#define XCHAL_EXTINT9_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT9_NUM)
#define XCHAL_EXTINT10_MASK		(1 << XCHAL_EXTINT10_NUM)
#define XCHAL_EXTINT10_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT10_NUM)
#define XCHAL_EXTINT11_MASK		(1 << XCHAL_EXTINT11_NUM)
#define XCHAL_EXTINT11_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT11_NUM)
#define XCHAL_EXTINT12_MASK		(1 << XCHAL_EXTINT12_NUM)
#define XCHAL_EXTINT12_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT12_NUM)
#define XCHAL_EXTINT13_MASK		(1 << XCHAL_EXTINT13_NUM)
#define XCHAL_EXTINT13_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT13_NUM)
#define XCHAL_EXTINT14_MASK		(1 << XCHAL_EXTINT14_NUM)
#define XCHAL_EXTINT14_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT14_NUM)
#define XCHAL_EXTINT15_MASK		(1 << XCHAL_EXTINT15_NUM)
#define XCHAL_EXTINT15_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT15_NUM)
#define XCHAL_EXTINT16_MASK		(1 << XCHAL_EXTINT16_NUM)
#define XCHAL_EXTINT16_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT16_NUM)
#define XCHAL_EXTINT17_MASK		(1 << XCHAL_EXTINT17_NUM)
#define XCHAL_EXTINT17_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT17_NUM)
#define XCHAL_EXTINT18_MASK		(1 << XCHAL_EXTINT18_NUM)
#define XCHAL_EXTINT18_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT18_NUM)
#define XCHAL_EXTINT19_MASK		(1 << XCHAL_EXTINT19_NUM)
#define XCHAL_EXTINT19_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT19_NUM)
#define XCHAL_EXTINT20_MASK		(1 << XCHAL_EXTINT20_NUM)
#define XCHAL_EXTINT20_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT20_NUM)
#define XCHAL_EXTINT21_MASK		(1 << XCHAL_EXTINT21_NUM)
#define XCHAL_EXTINT21_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT21_NUM)
#define XCHAL_EXTINT22_MASK		(1 << XCHAL_EXTINT22_NUM)
#define XCHAL_EXTINT22_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT22_NUM)
#define XCHAL_EXTINT23_MASK		(1 << XCHAL_EXTINT23_NUM)
#define XCHAL_EXTINT23_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT23_NUM)
#define XCHAL_EXTINT24_MASK		(1 << XCHAL_EXTINT24_NUM)
#define XCHAL_EXTINT24_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT24_NUM)
#define XCHAL_EXTINT25_MASK		(1 << XCHAL_EXTINT25_NUM)
#define XCHAL_EXTINT25_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT25_NUM)
#define XCHAL_EXTINT26_MASK		(1 << XCHAL_EXTINT26_NUM)
#define XCHAL_EXTINT26_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT26_NUM)
#define XCHAL_EXTINT27_MASK		(1 << XCHAL_EXTINT27_NUM)
#define XCHAL_EXTINT27_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT27_NUM)
#define XCHAL_EXTINT28_MASK		(1 << XCHAL_EXTINT28_NUM)
#define XCHAL_EXTINT28_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT28_NUM)
#define XCHAL_EXTINT29_MASK		(1 << XCHAL_EXTINT29_NUM)
#define XCHAL_EXTINT29_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT29_NUM)
#define XCHAL_EXTINT30_MASK		(1 << XCHAL_EXTINT30_NUM)
#define XCHAL_EXTINT30_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT30_NUM)
#define XCHAL_EXTINT31_MASK		(1 << XCHAL_EXTINT31_NUM)
#define XCHAL_EXTINT31_LEVEL		XCHAL_INT_LEVEL(XCHAL_EXTINT31_NUM)


/*----------------------------------------------------------------------
例外和向量
  ----------------------------------------------------------------------*/

/*  仅用于向后兼容--请勿使用（将在将来的版本中删除）：*/
#define XCHAL_HAVE_OLD_EXC_ARCH		XCHAL_HAVE_XEA1	/* （已弃用）如果旧异常架构（XEA1）为1，否则为0（例如XEA2）*/
#define XCHAL_HAVE_EXCM			XCHAL_HAVE_XEA2	/* （已弃用）1，如果PS.EXCM位存在（当前等于XCHAL_HAVE_TLBS）*/
#ifdef XCHAL_USER_VECTOR_VADDR
#define XCHAL_PROGRAMEXC_VECTOR_VADDR	XCHAL_USER_VECTOR_VADDR
#define XCHAL_USEREXC_VECTOR_VADDR	XCHAL_USER_VECTOR_VADDR
#endif
#ifdef XCHAL_USER_VECTOR_PADDR
# define XCHAL_PROGRAMEXC_VECTOR_PADDR	XCHAL_USER_VECTOR_PADDR
# define XCHAL_USEREXC_VECTOR_PADDR	XCHAL_USER_VECTOR_PADDR
#endif
#ifdef XCHAL_KERNEL_VECTOR_VADDR
# define XCHAL_STACKEDEXC_VECTOR_VADDR	XCHAL_KERNEL_VECTOR_VADDR
# define XCHAL_KERNELEXC_VECTOR_VADDR	XCHAL_KERNEL_VECTOR_VADDR
#endif
#ifdef XCHAL_KERNEL_VECTOR_PADDR
# define XCHAL_STACKEDEXC_VECTOR_PADDR	XCHAL_KERNEL_VECTOR_PADDR
# define XCHAL_KERNELEXC_VECTOR_PADDR	XCHAL_KERNEL_VECTOR_PADDR
#endif

#if 0
#if XCHAL_HAVE_DEBUG
# define XCHAL_DEBUG_VECTOR_VADDR	XCHAL_INTLEVEL_VECTOR_VADDR(XCHAL_DEBUGLEVEL)
/*  只有当相应的intlevel paddr宏存在时，才应定义此项：*/
# define XCHAL_DEBUG_VECTOR_PADDR	XCHAL_INTLEVEL_VECTOR_PADDR(XCHAL_DEBUGLEVEL)
#endif
#endif

/*  索引宏：*/
#define _XCHAL_INTLEVEL_VECTOR_VADDR(n)		XCHAL_INTLEVEL ## n ## _VECTOR_VADDR
#define XCHAL_INTLEVEL_VECTOR_VADDR(n)		_XCHAL_INTLEVEL_VECTOR_VADDR(n)		/* n=0..15*/

/*
 *  常规异常原因（由常规异常设置的EXCCAUSE特殊寄存器的值，该值指向用户、内核或双异常向量）。
 *
 *  已弃用。请使用<xtensa/corebits.h>中定义的等效EXCCAUSE_xxx宏。（请注意，这些名称略有不同，它们不仅删除了XCHAL_前缀。）
 */
#define XCHAL_EXCCAUSE_ILLEGAL_INSTRUCTION		0	/* 非法指令*/
#define XCHAL_EXCCAUSE_SYSTEM_CALL			1	/* 系统调用*/
#define XCHAL_EXCCAUSE_INSTRUCTION_FETCH_ERROR		2	/* 指令获取错误*/
#define XCHAL_EXCCAUSE_LOAD_STORE_ERROR			3	/* 加载存储错误*/
#define XCHAL_EXCCAUSE_LEVEL1_INTERRUPT			4	/* 1级中断*/
#define XCHAL_EXCCAUSE_ALLOCA				5	/* 堆栈扩展辅助*/
#define XCHAL_EXCCAUSE_INTEGER_DIVIDE_BY_ZERO		6	/* 整数除以零*/
#define XCHAL_EXCCAUSE_SPECULATION			7	/* 投机*/
#define XCHAL_EXCCAUSE_PRIVILEGED			8	/* 特权指令*/
#define XCHAL_EXCCAUSE_UNALIGNED			9	/* 未对齐的加载存储*/
/*10..15保留*/
#define XCHAL_EXCCAUSE_ITLB_MISS			16	/* ITlb未命中异常*/
#define XCHAL_EXCCAUSE_ITLB_MULTIHIT			17	/* ITlb多重命中异常*/
#define XCHAL_EXCCAUSE_ITLB_PRIVILEGE			18	/* ITlb特权异常*/
#define XCHAL_EXCCAUSE_ITLB_SIZE_RESTRICTION		19	/* ITlb大小限制异常*/
#define XCHAL_EXCCAUSE_FETCH_CACHE_ATTRIBUTE		20	/* 获取缓存属性异常*/
/*21-.23保留*/
#define XCHAL_EXCCAUSE_DTLB_MISS			24	/* DTlb未命中异常*/
#define XCHAL_EXCCAUSE_DTLB_MULTIHIT			25	/* DTlb多重命中异常*/
#define XCHAL_EXCCAUSE_DTLB_PRIVILEGE			26	/* DTlb特权异常*/
#define XCHAL_EXCCAUSE_DTLB_SIZE_RESTRICTION		27	/* DTlb大小限制异常*/
#define XCHAL_EXCCAUSE_LOAD_CACHE_ATTRIBUTE		28	/* 加载缓存属性异常*/
#define XCHAL_EXCCAUSE_STORE_CACHE_ATTRIBUTE		29	/* 存储缓存属性异常*/
/*30..31保留*/
#define XCHAL_EXCCAUSE_COPROCESSOR0_DISABLED		32	/* 协处理器0已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR1_DISABLED		33	/* 协处理器1已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR2_DISABLED		34	/* 协处理器2已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR3_DISABLED		35	/* 协处理器3已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR4_DISABLED		36	/* 协处理器4已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR5_DISABLED		37	/* 协处理器5已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR6_DISABLED		38	/* 协处理器6已禁用*/
#define XCHAL_EXCCAUSE_COPROCESSOR7_DISABLED		39	/* 协处理器7已禁用*/
/*40..63保留*/


/*
 *  其他特殊寄存器字段。
 *
 *  对于每个特殊寄存器和每个寄存器中的每个字段：XCHAL_<regname>_VALIDMASK是寄存器中定义的一组位。XCHAL_<regname>_<field>_BITS是字段中的位数。XCHAL_<regname>_<field>_NUM是2^位，即字段的可能值数。XCHAL_<regname>_<field>_SHIFT是寄存器中字段的位置，从最低有效位开始。
 *
 *  已弃用。请使用<xtensa/corebits.h>中定义的等效宏。（请注意，这些名称不同。）
 */

/*  DBREAKC（特殊寄存器编号160）：*/
#define XCHAL_DBREAKC_VALIDMASK		0xC000003F
#define XCHAL_DBREAKC_MASK_BITS 	6
#define XCHAL_DBREAKC_MASK_NUM  	64
#define XCHAL_DBREAKC_MASK_SHIFT	0
#define XCHAL_DBREAKC_MASK_MASK 	0x0000003F
#define XCHAL_DBREAKC_LOADBREAK_BITS 	1
#define XCHAL_DBREAKC_LOADBREAK_NUM  	2
#define XCHAL_DBREAKC_LOADBREAK_SHIFT	30
#define XCHAL_DBREAKC_LOADBREAK_MASK 	0x40000000
#define XCHAL_DBREAKC_STOREBREAK_BITS 	1
#define XCHAL_DBREAKC_STOREBREAK_NUM  	2
#define XCHAL_DBREAKC_STOREBREAK_SHIFT	31
#define XCHAL_DBREAKC_STOREBREAK_MASK 	0x80000000
/*  PS（特殊寄存器编号230）：*/
#define XCHAL_PS_VALIDMASK		0x00070F3F
#define XCHAL_PS_INTLEVEL_BITS 		4
#define XCHAL_PS_INTLEVEL_NUM  		16
#define XCHAL_PS_INTLEVEL_SHIFT		0
#define XCHAL_PS_INTLEVEL_MASK 		0x0000000F
#define XCHAL_PS_EXCM_BITS 		1
#define XCHAL_PS_EXCM_NUM  		2
#define XCHAL_PS_EXCM_SHIFT		4
#define XCHAL_PS_EXCM_MASK 		0x00000010
#define XCHAL_PS_UM_BITS 		1
#define XCHAL_PS_UM_NUM  		2
#define XCHAL_PS_UM_SHIFT		5
#define XCHAL_PS_UM_MASK 		0x00000020
#define XCHAL_PS_RING_BITS 		2
#define XCHAL_PS_RING_NUM  		4
#define XCHAL_PS_RING_SHIFT		6
#define XCHAL_PS_RING_MASK 		0x000000C0
#define XCHAL_PS_OWB_BITS 		4
#define XCHAL_PS_OWB_NUM  		16
#define XCHAL_PS_OWB_SHIFT		8
#define XCHAL_PS_OWB_MASK 		0x00000F00
#define XCHAL_PS_CALLINC_BITS 		2
#define XCHAL_PS_CALLINC_NUM  		4
#define XCHAL_PS_CALLINC_SHIFT		16
#define XCHAL_PS_CALLINC_MASK 		0x00030000
#define XCHAL_PS_WOE_BITS 		1
#define XCHAL_PS_WOE_NUM  		2
#define XCHAL_PS_WOE_SHIFT		18
#define XCHAL_PS_WOE_MASK 		0x00040000
/*  EXCCAUSE（特殊寄存器编号232）：*/
#define XCHAL_EXCCAUSE_VALIDMASK	0x0000003F
#define XCHAL_EXCCAUSE_BITS 		6
#define XCHAL_EXCCAUSE_NUM  		64
#define XCHAL_EXCCAUSE_SHIFT		0
#define XCHAL_EXCCAUSE_MASK 		0x0000003F
/*  调试原因（特殊寄存器编号233）：*/
#define XCHAL_DEBUGCAUSE_VALIDMASK	0x0000003F
#define XCHAL_DEBUGCAUSE_ICOUNT_BITS 	1
#define XCHAL_DEBUGCAUSE_ICOUNT_NUM  	2
#define XCHAL_DEBUGCAUSE_ICOUNT_SHIFT	0
#define XCHAL_DEBUGCAUSE_ICOUNT_MASK 	0x00000001
#define XCHAL_DEBUGCAUSE_IBREAK_BITS 	1
#define XCHAL_DEBUGCAUSE_IBREAK_NUM  	2
#define XCHAL_DEBUGCAUSE_IBREAK_SHIFT	1
#define XCHAL_DEBUGCAUSE_IBREAK_MASK 	0x00000002
#define XCHAL_DEBUGCAUSE_DBREAK_BITS 	1
#define XCHAL_DEBUGCAUSE_DBREAK_NUM  	2
#define XCHAL_DEBUGCAUSE_DBREAK_SHIFT	2
#define XCHAL_DEBUGCAUSE_DBREAK_MASK 	0x00000004
#define XCHAL_DEBUGCAUSE_BREAK_BITS 	1
#define XCHAL_DEBUGCAUSE_BREAK_NUM  	2
#define XCHAL_DEBUGCAUSE_BREAK_SHIFT	3
#define XCHAL_DEBUGCAUSE_BREAK_MASK 	0x00000008
#define XCHAL_DEBUGCAUSE_BREAKN_BITS 	1
#define XCHAL_DEBUGCAUSE_BREAKN_NUM  	2
#define XCHAL_DEBUGCAUSE_BREAKN_SHIFT	4
#define XCHAL_DEBUGCAUSE_BREAKN_MASK 	0x00000010
#define XCHAL_DEBUGCAUSE_DEBUGINT_BITS 	1
#define XCHAL_DEBUGCAUSE_DEBUGINT_NUM  	2
#define XCHAL_DEBUGCAUSE_DEBUGINT_SHIFT	5
#define XCHAL_DEBUGCAUSE_DEBUGINT_MASK 	0x00000020




/*----------------------------------------------------------------------
				TIMERS
  ----------------------------------------------------------------------*/

/*#定义XCHAL_HAVE_TIMERS XCHAL_HAVE_CCOUNT*/



/*----------------------------------------------------------------------
内部I/O RAM/ROM和XLMI
  ----------------------------------------------------------------------*/

#define  XCHAL_NUM_IROM		XCHAL_NUM_INSTROM	/* (DEPRECATED) */
#define  XCHAL_NUM_IRAM		XCHAL_NUM_INSTRAM	/* (DEPRECATED) */
#define  XCHAL_NUM_DROM		XCHAL_NUM_DATAROM	/* (DEPRECATED) */
#define  XCHAL_NUM_DRAM		XCHAL_NUM_DATARAM	/* (DEPRECATED) */

#define XCHAL_IROM0_VADDR	XCHAL_INSTROM0_VADDR	/* (DEPRECATED) */
#define XCHAL_IROM0_PADDR	XCHAL_INSTROM0_PADDR	/* (DEPRECATED) */
#define XCHAL_IROM0_SIZE	XCHAL_INSTROM0_SIZE	/* (DEPRECATED) */
#define XCHAL_IROM1_VADDR	XCHAL_INSTROM1_VADDR	/* (DEPRECATED) */
#define XCHAL_IROM1_PADDR	XCHAL_INSTROM1_PADDR	/* (DEPRECATED) */
#define XCHAL_IROM1_SIZE	XCHAL_INSTROM1_SIZE	/* (DEPRECATED) */
#define XCHAL_IRAM0_VADDR	XCHAL_INSTRAM0_VADDR	/* (DEPRECATED) */
#define XCHAL_IRAM0_PADDR	XCHAL_INSTRAM0_PADDR	/* (DEPRECATED) */
#define XCHAL_IRAM0_SIZE	XCHAL_INSTRAM0_SIZE	/* (DEPRECATED) */
#define XCHAL_IRAM1_VADDR	XCHAL_INSTRAM1_VADDR	/* (DEPRECATED) */
#define XCHAL_IRAM1_PADDR	XCHAL_INSTRAM1_PADDR	/* (DEPRECATED) */
#define XCHAL_IRAM1_SIZE	XCHAL_INSTRAM1_SIZE	/* (DEPRECATED) */
#define XCHAL_DROM0_VADDR	XCHAL_DATAROM0_VADDR	/* (DEPRECATED) */
#define XCHAL_DROM0_PADDR	XCHAL_DATAROM0_PADDR	/* (DEPRECATED) */
#define XCHAL_DROM0_SIZE	XCHAL_DATAROM0_SIZE	/* (DEPRECATED) */
#define XCHAL_DROM1_VADDR	XCHAL_DATAROM1_VADDR	/* (DEPRECATED) */
#define XCHAL_DROM1_PADDR	XCHAL_DATAROM1_PADDR	/* (DEPRECATED) */
#define XCHAL_DROM1_SIZE	XCHAL_DATAROM1_SIZE	/* (DEPRECATED) */
#define XCHAL_DRAM0_VADDR	XCHAL_DATARAM0_VADDR	/* (DEPRECATED) */
#define XCHAL_DRAM0_PADDR	XCHAL_DATARAM0_PADDR	/* (DEPRECATED) */
#define XCHAL_DRAM0_SIZE	XCHAL_DATARAM0_SIZE	/* (DEPRECATED) */
#define XCHAL_DRAM1_VADDR	XCHAL_DATARAM1_VADDR	/* (DEPRECATED) */
#define XCHAL_DRAM1_PADDR	XCHAL_DATARAM1_PADDR	/* (DEPRECATED) */
#define XCHAL_DRAM1_SIZE	XCHAL_DATARAM1_SIZE	/* (DEPRECATED) */



/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/


/*  启用预取的默认PREFCTL值。*/
#if XCHAL_HW_MIN_VERSION < XTENSA_HWVERSION_RE_2012_0
#define XCHAL_CACHE_PREFCTL_DEFAULT	0x00044	/* 启用，不具有攻击性*/
#elif XCHAL_HW_MIN_VERSION < XTENSA_HWVERSION_RF_2014_0
#define XCHAL_CACHE_PREFCTL_DEFAULT	0x01044	/* +启用L1预取*/
#elif ((XCHAL_PREFETCH_ENTRIES >= 16) && XCHAL_HAVE_CACHE_BLOCKOPS)
#define XCHAL_CACHE_PREFCTL_DEFAULT	0x81044	/* 块操作的12个条目*/
#elif ((XCHAL_PREFETCH_ENTRIES >= 8) && XCHAL_HAVE_CACHE_BLOCKOPS)
#define XCHAL_CACHE_PREFCTL_DEFAULT	0x51044	/* 块操作的5个条目*/
#else
#define XCHAL_CACHE_PREFCTL_DEFAULT	0x01044	/* 块操作的0个条目*/
#endif


/*  I缓存和D缓存的最大值（用于常规对齐）：*/
#if XCHAL_ICACHE_LINESIZE > XCHAL_DCACHE_LINESIZE
# define XCHAL_CACHE_LINEWIDTH_MAX	XCHAL_ICACHE_LINEWIDTH
# define XCHAL_CACHE_LINESIZE_MAX	XCHAL_ICACHE_LINESIZE
#else
# define XCHAL_CACHE_LINEWIDTH_MAX	XCHAL_DCACHE_LINEWIDTH
# define XCHAL_CACHE_LINESIZE_MAX	XCHAL_DCACHE_LINESIZE
#endif

#define XCHAL_ICACHE_SETSIZE		(1<<XCHAL_ICACHE_SETWIDTH)
#define XCHAL_DCACHE_SETSIZE		(1<<XCHAL_DCACHE_SETWIDTH)
/*  I和D缓存的最大值（用于缓存一致性页面对齐）：*/
#if XCHAL_ICACHE_SETWIDTH > XCHAL_DCACHE_SETWIDTH
# define XCHAL_CACHE_SETWIDTH_MAX	XCHAL_ICACHE_SETWIDTH
# define XCHAL_CACHE_SETSIZE_MAX	XCHAL_ICACHE_SETSIZE
#else
# define XCHAL_CACHE_SETWIDTH_MAX	XCHAL_DCACHE_SETWIDTH
# define XCHAL_CACHE_SETSIZE_MAX	XCHAL_DCACHE_SETSIZE
#endif

/*  指令缓存标记位：*/
#define XCHAL_ICACHE_TAG_V_SHIFT	0
#define XCHAL_ICACHE_TAG_V		0x1	/* 有效位*/
#if XCHAL_ICACHE_WAYS > 1
# define XCHAL_ICACHE_TAG_F_SHIFT	1
# define XCHAL_ICACHE_TAG_F		0x2	/* 填充（LRU）位*/
#else
# define XCHAL_ICACHE_TAG_F_SHIFT	0
# define XCHAL_ICACHE_TAG_F		0	/* 无填充（LRU）位*/
#endif
#if XCHAL_ICACHE_LINE_LOCKABLE
# define XCHAL_ICACHE_TAG_L_SHIFT	(XCHAL_ICACHE_TAG_F_SHIFT+1)
# define XCHAL_ICACHE_TAG_L		(1 << XCHAL_ICACHE_TAG_L_SHIFT)	/* 锁定钻头*/
#else
# define XCHAL_ICACHE_TAG_L_SHIFT	XCHAL_ICACHE_TAG_F_SHIFT
# define XCHAL_ICACHE_TAG_L		0	/* 无锁定钻头*/
#endif
/*  数据缓存标记位：*/
#define XCHAL_DCACHE_TAG_V_SHIFT	0
#define XCHAL_DCACHE_TAG_V		0x1	/* 有效位*/
#if XCHAL_DCACHE_WAYS > 1
# define XCHAL_DCACHE_TAG_F_SHIFT	1
# define XCHAL_DCACHE_TAG_F		0x2	/* 填充（LRU）位*/
#else
# define XCHAL_DCACHE_TAG_F_SHIFT	0
# define XCHAL_DCACHE_TAG_F		0	/* 无填充（LRU）位*/
#endif
#if XCHAL_DCACHE_IS_WRITEBACK
# define XCHAL_DCACHE_TAG_D_SHIFT	(XCHAL_DCACHE_TAG_F_SHIFT+1)
# define XCHAL_DCACHE_TAG_D		(1 << XCHAL_DCACHE_TAG_D_SHIFT)	/* 脏钻头*/
#else
# define XCHAL_DCACHE_TAG_D_SHIFT	XCHAL_DCACHE_TAG_F_SHIFT
# define XCHAL_DCACHE_TAG_D		0	/* 无脏钻头*/
#endif
#if XCHAL_DCACHE_LINE_LOCKABLE
# define XCHAL_DCACHE_TAG_L_SHIFT	(XCHAL_DCACHE_TAG_D_SHIFT+1)
# define XCHAL_DCACHE_TAG_L		(1 << XCHAL_DCACHE_TAG_L_SHIFT)	/* 锁定钻头*/
#else
# define XCHAL_DCACHE_TAG_L_SHIFT	XCHAL_DCACHE_TAG_D_SHIFT
# define XCHAL_DCACHE_TAG_L		0	/* 无锁定钻头*/
#endif

/*  MEMCTL寄存器是否有任何有用的内容*/
#define XCHAL_USE_MEMCTL		(((XCHAL_LOOP_BUFFER_SIZE > 0)	||      \
					XCHAL_DCACHE_IS_COHERENT	||      \
					XCHAL_HAVE_ICACHE_DYN_WAYS	||      \
					XCHAL_HAVE_DCACHE_DYN_WAYS)	&&      \
					(XCHAL_HW_MIN_VERSION >= XTENSA_HWVERSION_RE_2012_0))

#if XCHAL_DCACHE_IS_COHERENT
#define _MEMCTL_SNOOP_EN		0x02		/* 启用窥探*/
#else
#define _MEMCTL_SNOOP_EN		0x00		/* 不启用窥探*/
#endif

#if (XCHAL_LOOP_BUFFER_SIZE == 0) || XCHAL_ERRATUM_453
#define _MEMCTL_L0IBUF_EN		0x00		/* 无循环缓冲区或不启用*/
#else
#define _MEMCTL_L0IBUF_EN		0x01		/* 启用循环缓冲区*/
#endif

/*  默认MEMCTL值：*/
#if XCHAL_HAVE_ICACHE_DYN_WAYS || XCHAL_HAVE_DCACHE_DYN_WAYS
#define XCHAL_CACHE_MEMCTL_DEFAULT	(0xFFFFFF00 | _MEMCTL_L0IBUF_EN)
#else
#define XCHAL_CACHE_MEMCTL_DEFAULT	(0x00000000 | _MEMCTL_L0IBUF_EN)
#endif

#define XCHAL_SNOOP_LB_MEMCTL_DEFAULT	(_MEMCTL_SNOOP_EN | _MEMCTL_L0IBUF_EN)


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*  请参见<extensa/config/core matmap。h> 了解更多详情。*/

/*  在开源标头中有不同的语义（这里它的意思是HAVE_PTP_MMU），所以从RB-2008.3版本开始注释；稍后，可能会被重新引入为XCHAL_HAVE_PTP_MMU的同义词：*/
/*#定义XCHAL_HAVE_MMU XCHAL_HAVE_TLBS*/	/* （已弃用；请改用XCHAL_HAVE_TLBS）*/

/*  索引宏：*/
#define _XCHAL_ITLB_SET(n,_what)	XCHAL_ITLB_SET ## n ## _what
#define XCHAL_ITLB_SET(n,what)		_XCHAL_ITLB_SET(n, _ ## what )
#define _XCHAL_ITLB_SET_E(n,i,_what)	XCHAL_ITLB_SET ## n ## _E ## i ## _what
#define XCHAL_ITLB_SET_E(n,i,what)	_XCHAL_ITLB_SET_E(n,i, _ ## what )
#define _XCHAL_DTLB_SET(n,_what)	XCHAL_DTLB_SET ## n ## _what
#define XCHAL_DTLB_SET(n,what)		_XCHAL_DTLB_SET(n, _ ## what )
#define _XCHAL_DTLB_SET_E(n,i,_what)	XCHAL_DTLB_SET ## n ## _E ## i ## _what
#define XCHAL_DTLB_SET_E(n,i,what)	_XCHAL_DTLB_SET_E(n,i, _ ## what )
/*
 *  示例使用：XCHAL_ITLB_SET（XCHAL_ITLB_ARF_SET0，ENTRIES）获取XCHAL_ITL B_SET＜n＞_ENTRIES的值，其中＜n＞是第一个自动重新填充集。
 */

/*  每个自动填充方式的条目数：*/
#define XCHAL_ITLB_ARF_ENTRIES		(1<<XCHAL_ITLB_ARF_ENTRIES_LOG2)
#define XCHAL_DTLB_ARF_ENTRIES		(1<<XCHAL_DTLB_ARF_ENTRIES_LOG2)

/*
 *  确定我们是否有可用于基于MMU的操作系统的完整MMU（具有页面表和保护）：
 */
#if 0
#if XCHAL_HAVE_TLBS && !XCHAL_HAVE_SPANNING_WAY && XCHAL_ITLB_ARF_WAYS > 0 && XCHAL_DTLB_ARF_WAYS > 0 && XCHAL_MMU_RINGS >= 2
# define XCHAL_HAVE_PTP_MMU		1	/* 具有完整的MMU（具有页表[自动填充]和保护）*/
#else
# define XCHAL_HAVE_PTP_MMU		0	/* 没有完整的MMU*/
#endif
#endif

/*
 *  对于完整的MMU，报告内核RAM段和内核I/O段静态页面映射：
 */
#if XCHAL_HAVE_PTP_MMU && !XCHAL_HAVE_SPANNING_WAY
#define XCHAL_KSEG_CACHED_VADDR		0xD0000000	/* 处女座。内核RAM缓存静态映射的地址*/
#define XCHAL_KSEG_CACHED_PADDR		0x00000000	/* 物理。kseg_cached的地址*/
#define XCHAL_KSEG_CACHED_SIZE		0x08000000	/* kseg_cached的字节大小（假定为2！！！的幂）*/
#define XCHAL_KSEG_BYPASS_VADDR		0xD8000000	/* 处女座。内核RAM旁路（未缓存）静态映射的地址*/
#define XCHAL_KSEG_BYPASS_PADDR		0x00000000	/* 物理。kseg_bypass的地址*/
#define XCHAL_KSEG_BYPASS_SIZE		0x08000000	/* kseg_bypass的字节大小（假设为2！！！的幂）*/

#define XCHAL_KIO_CACHED_VADDR		0xE0000000	/* 处女座。内核I/O缓存静态映射的地址*/
#define XCHAL_KIO_CACHED_PADDR		0xF0000000	/* 物理。kio_cached的地址*/
#define XCHAL_KIO_CACHED_SIZE		0x10000000	/* kio_cached的字节大小（假设为2！！！的幂）*/
#define XCHAL_KIO_BYPASS_VADDR		0xF0000000	/* 处女座。内核I/O旁路（未缓存）静态映射的地址*/
#define XCHAL_KIO_BYPASS_PADDR		0xF0000000	/* 物理。kio旁路地址*/
#define XCHAL_KIO_BYPASS_SIZE		0x10000000	/* kio_bypass的字节大小（假设为2！！！的幂）*/

#define XCHAL_SEG_MAPPABLE_VADDR	0x00000000	/* 最大非静态映射虚拟地址区域的开始*/
#define XCHAL_SEG_MAPPABLE_SIZE		0xD0000000	/* 大小（字节）“*/
/* 如果存在更多区域，请定义XCHAL_SEG_MAPPABLE2_xxx，按大小降序排序。*/
#endif


/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/

/*  如果用于说明，则需要数据对齐：*/
#if XCHAL_INST_FETCH_WIDTH > XCHAL_DATA_WIDTH
# define XCHAL_ALIGN_MAX		XCHAL_INST_FETCH_WIDTH
#else
# define XCHAL_ALIGN_MAX		XCHAL_DATA_WIDTH
#endif

/*
 *  为向后兼容而保留的名称。（这里的“RELEASE”现在用词不当；这些是产品版本，而不是发布它们的版本。在T10###.#时代没有区别。）
 */
#define XCHAL_HW_RELEASE_MAJOR		XCHAL_HW_VERSION_MAJOR
#define XCHAL_HW_RELEASE_MINOR		XCHAL_HW_VERSION_MINOR
#define XCHAL_HW_RELEASE_NAME		XCHAL_HW_VERSION_NAME




/*----------------------------------------------------------------------
共同主持人和额外状态
  ----------------------------------------------------------------------*/

#define XCHAL_EXTRA_SA_SIZE		XCHAL_NCP_SA_SIZE
#define XCHAL_EXTRA_SA_ALIGN		XCHAL_NCP_SA_ALIGN
#define XCHAL_CPEXTRA_SA_SIZE		XCHAL_TOTAL_SA_SIZE
#define XCHAL_CPEXTRA_SA_ALIGN		XCHAL_TOTAL_SA_ALIGN

#if defined (_ASMLANGUAGE) || defined (__ASSEMBLER__)

	/*  在保存区域加载/存储顺序宏开始时调用，以设置宏内部偏移。通常不直接调用。第一个序列继续0，后续连续序列继续1。从原始ptr到下一个加载/存储位置的totofs偏移量。
	 */
	.macro	xchal_sa_start	continue totofs
	.ifeq \continue
	 .set	.Lxchal_pofs_, 0	/* 从原始ptr到当前ptr的偏移量*/
	 .set	.Lxchal_ofs_, 0		/* 从当前\ptr到下一个加载/存储位置的偏移量*/
	.endif
	.if \totofs + 1			/* 如果指定了totofs（非-1）*/
	 .set	.Lxchal_ofs_, \totofs - .Lxchal_pofs_	/* 与原始ptr的特定偏移*/
	.endif
	.endm

	/*  对齐保存区域的一部分，如有必要，将指针置于范围内。用于保存区域加载/存储序列。通常不直接调用。允许任意组合多个（子）序列。保存区域的ptr指针（可能已关闭，请参见.Lxchal_pofs_）minofs，从当前ptr到下一个加载/存储位置的最大偏移范围；minofs<=0<=maxofs（0必须始终是有效的偏移量）范围必须在+/-30kB左右。ofalign对齐粒度为minofs.maxofs（pow of 2）（限制从ptr到下一个加载/存储位置的偏移量）从原始ptr到上一个加载或存储位置的totalign对齐（pow为2）
	 */
	.macro	xchal_sa_align	ptr minofs maxofs ofsalign totalign
	/*  首先对齐开始访问相对于原始ptr的下一个寄存器的位置（即保存区域的开始位置）：
	 */
	.set	.Lxchal_ofs_, ((.Lxchal_pofs_ + .Lxchal_ofs_ + \totalign - 1) & -\totalign) - .Lxchal_pofs_
	/*  如有必要，调整\ptr使.Lxchal_ofs_处于可接受范围内：*/
	.if (((\maxofs) - .Lxchal_ofs_) & 0xC0000000) | ((.Lxchal_ofs_ - (\minofs)) & 0xC0000000) | (.Lxchal_ofs_ & (\ofsalign-1))
	 .set	.Ligmask, 0xFFFFFFFF	/* TODO:优化为addmi、per alignment和.Lxchal_ofs_*/
	 addi	\ptr, \ptr, (.Lxchal_ofs_ & .Ligmask)
	 .set	.Lxchal_pofs_, .Lxchal_pofs_ + (.Lxchal_ofs_ & .Ligmask)
	 .set	.Lxchal_ofs_, (.Lxchal_ofs_ & ~.Ligmask)
	.endif
	.endm
	/*
	 *  如果可能的话，我们可以优化addi扩展到仅addmi而不是“addmi；addi”。下面是一个部分示例：.set.Lmaxmask，-（\ofalign）&-（\totasign）.if（（（\maxofs）+~。Lmaxmask+1）&0xFFFFFF00）&&（（.Lxchal_ofs_&~.Lmaxmask）==0）.set.Ligmask，0xFFFFFF00.elif…对于负的ofs范围，同上…set.Ligmask，0xFFFFF00.set…按偏移调整…else.set.Ligmask，0xFFFFFFF.endif
	 */

	/*  在xchal_XXX_｛load，store｝宏恢复\ptr后调用此命令。*/
	.macro	xchal_sa_ptr_restore	ptr
	.if .Lxchal_pofs_
	 addi	\ptr, \ptr, - .Lxchal_pofs_
	 .set	.Lxchal_ofs_, .Lxchal_ofs_ + .Lxchal_pofs_
	 .set	.Lxchal_pofs_, 0
	.endif
	.endm

	/*
	 *  用作示例：xchal_atmps_store a1、SOMEOFS、xchal_SA_NUM_atmps、a4、a5 xchal_ncp_load a2、a0、a3、a4，a5 xchal_atmps_load a1、SOMOFS、xchal_AA_NUM_atmps、a5、a5
	 *
	 *  仅指定您尚未*保存/还原的AR，最多4个。它们必须是为保存区域加载/存储序列而指定的最后一个AR（顺序相同）。在上面的示例中，a0和a3已经保存/恢复并且未使用（因此可用），但a4和a5没有。
	 */
#define xchal_atmps_store	xchal_atmps_loadstore s32i,
#define xchal_atmps_load	xchal_atmps_loadstore l32i,
	.macro	xchal_atmps_loadstore	inst ptr offset nreq aa=0 ab=0 ac=0 ad=0
	.set	.Lnsaved_, 0
	.irp	reg,\aa,\ab,\ac,\ad
	 .ifeq 0x\reg ; .set .Lnsaved_,.Lnsaved_+1 ; .endif
	.endr
	.set	.Laofs_, 0
	.irp	reg,\aa,\ab,\ac,\ad
	 .ifgt (\nreq)-.Lnsaved_
	  \inst	\reg, \ptr, .Laofs_+\offset
	  .set	.Laofs_,.Laofs_+4
	  .set	.Lnsaved_,.Lnsaved_+1
	 .endif
	.endr
	.endm

/*#定义xchal_ncp_load_a2 xchal_ncp _load a2、a3、a4、a5、a6*/
/*#定义xchal_ncp_store_a2 xchal_ncp _store a2、a3、a4、a5、a6*/
#define xchal_extratie_load		xchal_ncptie_load
#define xchal_extratie_store		xchal_ncptie_store
#define xchal_extratie_load_a2		xchal_ncptie_load  a2,a3,a4,a5,a6
#define xchal_extratie_store_a2		xchal_ncptie_store a2,a3,a4,a5,a6
#define xchal_extra_load		xchal_ncp_load
#define xchal_extra_store		xchal_ncp_store
#define xchal_extra_load_a2		xchal_ncp_load  a2,a3,a4,a5,a6
#define xchal_extra_store_a2		xchal_ncp_store a2,a3,a4,a5,a6
#define xchal_extra_load_funcbody	xchal_ncp_load  a2,a3,a4,a5,a6
#define xchal_extra_store_funcbody	xchal_ncp_store a2,a3,a4,a5,a6
#define xchal_cp0_store_a2		xchal_cp0_store  a2,a3,a4,a5,a6
#define xchal_cp0_load_a2		xchal_cp0_load   a2,a3,a4,a5,a6
#define xchal_cp1_store_a2		xchal_cp1_store  a2,a3,a4,a5,a6
#define xchal_cp1_load_a2		xchal_cp1_load   a2,a3,a4,a5,a6
#define xchal_cp2_store_a2		xchal_cp2_store  a2,a3,a4,a5,a6
#define xchal_cp2_load_a2		xchal_cp2_load   a2,a3,a4,a5,a6
#define xchal_cp3_store_a2		xchal_cp3_store  a2,a3,a4,a5,a6
#define xchal_cp3_load_a2		xchal_cp3_load   a2,a3,a4,a5,a6
#define xchal_cp4_store_a2		xchal_cp4_store  a2,a3,a4,a5,a6
#define xchal_cp4_load_a2		xchal_cp4_load   a2,a3,a4,a5,a6
#define xchal_cp5_store_a2		xchal_cp5_store  a2,a3,a4,a5,a6
#define xchal_cp5_load_a2		xchal_cp5_load   a2,a3,a4,a5,a6
#define xchal_cp6_store_a2		xchal_cp6_store  a2,a3,a4,a5,a6
#define xchal_cp6_load_a2		xchal_cp6_load   a2,a3,a4,a5,a6
#define xchal_cp7_store_a2		xchal_cp7_store  a2,a3,a4,a5,a6
#define xchal_cp7_load_a2		xchal_cp7_load   a2,a3,a4,a5,a6

/*  未定义协处理器的空占位符宏：*/
#if (XCHAL_CP_MASK & ~XCHAL_CP_PORT_MASK) == 0
# if XCHAL_CP0_SA_SIZE == 0
	.macro xchal_cp0_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp0_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP1_SA_SIZE == 0
	.macro xchal_cp1_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp1_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP2_SA_SIZE == 0
	.macro xchal_cp2_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp2_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP3_SA_SIZE == 0
	.macro xchal_cp3_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp3_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP4_SA_SIZE == 0
	.macro xchal_cp4_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp4_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP5_SA_SIZE == 0
	.macro xchal_cp5_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp5_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP6_SA_SIZE == 0
	.macro xchal_cp6_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp6_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
# if XCHAL_CP7_SA_SIZE == 0
	.macro xchal_cp7_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp7_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
# endif
#endif

	/********************
	 *  宏，用于创建保存和恢复*any*TIE协处理器状态的函数（通过动态索引）。
	 */

	/*
	 *  宏，扩展到存储所选协处理器状态（寄存器等）的函数体。条目：a2=保存cp状态a3=协处理器编号的保存区域的指针退出：任何寄存器a2-a15（？）可能被打了。
	 */
	.macro	xchal_cpi_store_funcbody
#if (XCHAL_CP_MASK & ~XCHAL_CP_PORT_MASK)
# if XCHAL_CP0_SA_SIZE
	bnez	a3, 99f
	xchal_cp0_store_a2
	j	90f
99:
# endif
# if XCHAL_CP1_SA_SIZE
	bnei	a3, 1, 99f
	xchal_cp1_store_a2
	j	90f
99:
# endif
# if XCHAL_CP2_SA_SIZE
	bnei	a3, 2, 99f
	xchal_cp2_store_a2
	j	90f
99:
# endif
# if XCHAL_CP3_SA_SIZE
	bnei	a3, 3, 99f
	xchal_cp3_store_a2
	j	90f
99:
# endif
# if XCHAL_CP4_SA_SIZE
	bnei	a3, 4, 99f
	xchal_cp4_store_a2
	j	90f
99:
# endif
# if XCHAL_CP5_SA_SIZE
	bnei	a3, 5, 99f
	xchal_cp5_store_a2
	j	90f
99:
# endif
# if XCHAL_CP6_SA_SIZE
	bnei	a3, 6, 99f
	xchal_cp6_store_a2
	j	90f
99:
# endif
# if XCHAL_CP7_SA_SIZE
	bnei	a3, 7, 99f
	xchal_cp7_store_a2
	j	90f
99:
# endif
90:
#endif
	.endm

	/*
	 *  宏，扩展到加载所选协处理器状态（寄存器等）的函数体。条目：a2=保存要从中恢复cp状态的区域的ptr a3=协处理器编号退出：任何寄存器a2-a15（？）可能被打了。
	 */
	.macro	xchal_cpi_load_funcbody
#if (XCHAL_CP_MASK & ~XCHAL_CP_PORT_MASK)
# if XCHAL_CP0_SA_SIZE
	bnez	a3, 99f
	xchal_cp0_load_a2
	j	90f
99:
# endif
# if XCHAL_CP1_SA_SIZE
	bnei	a3, 1, 99f
	xchal_cp1_load_a2
	j	90f
99:
# endif
# if XCHAL_CP2_SA_SIZE
	bnei	a3, 2, 99f
	xchal_cp2_load_a2
	j	90f
99:
# endif
# if XCHAL_CP3_SA_SIZE
	bnei	a3, 3, 99f
	xchal_cp3_load_a2
	j	90f
99:
# endif
# if XCHAL_CP4_SA_SIZE
	bnei	a3, 4, 99f
	xchal_cp4_load_a2
	j	90f
99:
# endif
# if XCHAL_CP5_SA_SIZE
	bnei	a3, 5, 99f
	xchal_cp5_load_a2
	j	90f
99:
# endif
# if XCHAL_CP6_SA_SIZE
	bnei	a3, 6, 99f
	xchal_cp6_load_a2
	j	90f
99:
# endif
# if XCHAL_CP7_SA_SIZE
	bnei	a3, 7, 99f
	xchal_cp7_load_a2
	j	90f
99:
# endif
90:
#endif
	.endm

#endif /*_ASMLANGUAGE或__ASSEMBLER__*/


/*  未定义协处理器的其他默认宏：*/
#ifndef XCHAL_CP0_NAME
# define XCHAL_CP0_NAME				0
# define XCHAL_CP0_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP0_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP1_NAME
# define XCHAL_CP1_NAME				0
# define XCHAL_CP1_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP1_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP2_NAME
# define XCHAL_CP2_NAME				0
# define XCHAL_CP2_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP2_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP3_NAME
# define XCHAL_CP3_NAME				0
# define XCHAL_CP3_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP3_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP4_NAME
# define XCHAL_CP4_NAME				0
# define XCHAL_CP4_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP4_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP5_NAME
# define XCHAL_CP5_NAME				0
# define XCHAL_CP5_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP5_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP6_NAME
# define XCHAL_CP6_NAME				0
# define XCHAL_CP6_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP6_SA_CONTENTS_LIBDB		/* 空的*/
#endif
#ifndef XCHAL_CP7_NAME
# define XCHAL_CP7_NAME				0
# define XCHAL_CP7_SA_CONTENTS_LIBDB_NUM	0
# define XCHAL_CP7_SA_CONTENTS_LIBDB		/* 空的*/
#endif

#if XCHAL_CP_MASK == 0
/*  未分配协处理器的填充信息，以简化阵列等：*/
#define XCHAL_CP0_SA_SIZE               0
#define XCHAL_CP0_SA_ALIGN              1
#define XCHAL_CP1_SA_SIZE               0
#define XCHAL_CP1_SA_ALIGN              1
#define XCHAL_CP2_SA_SIZE               0
#define XCHAL_CP2_SA_ALIGN              1
#define XCHAL_CP3_SA_SIZE               0
#define XCHAL_CP3_SA_ALIGN              1
#define XCHAL_CP4_SA_SIZE               0
#define XCHAL_CP4_SA_ALIGN              1
#define XCHAL_CP5_SA_SIZE               0
#define XCHAL_CP5_SA_ALIGN              1
#define XCHAL_CP6_SA_SIZE               0
#define XCHAL_CP6_SA_ALIGN              1
#define XCHAL_CP7_SA_SIZE               0
#define XCHAL_CP7_SA_ALIGN              1
#endif


/*  索引宏：*/
#define _XCHAL_CP_SA_SIZE(n)		XCHAL_CP ## n ## _SA_SIZE
#define XCHAL_CP_SA_SIZE(n)		_XCHAL_CP_SA_SIZE(n)	/* n=0..7*/
#define _XCHAL_CP_SA_ALIGN(n)		XCHAL_CP ## n ## _SA_ALIGN
#define XCHAL_CP_SA_ALIGN(n)		_XCHAL_CP_SA_ALIGN(n)	/* n=0..7*/

#define XCHAL_CPEXTRA_SA_SIZE_TOR2      XCHAL_CPEXTRA_SA_SIZE	/* 仅Tor2Beta-请勿使用*/

/*  按名称报告协处理器编号的链接时间HAL全局变量（名称保留原始TIE的大小写）：*/
#if !defined(_ASMLANGUAGE) && !defined(_NOCLANGUAGE) && !defined(__ASSEMBLER__)
# define _XCJOIN(a,b)	a ## b
# define XCJOIN(a,b)	_XCJOIN(a,b)
# ifdef XCHAL_CP0_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP0_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP0_IDENT);
# endif
# ifdef XCHAL_CP1_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP1_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP1_IDENT);
# endif
# ifdef XCHAL_CP2_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP2_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP2_IDENT);
# endif
# ifdef XCHAL_CP3_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP3_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP3_IDENT);
# endif
# ifdef XCHAL_CP4_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP4_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP4_IDENT);
# endif
# ifdef XCHAL_CP5_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP5_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP5_IDENT);
# endif
# ifdef XCHAL_CP6_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP6_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP6_IDENT);
# endif
# ifdef XCHAL_CP7_NAME
extern const unsigned char XCJOIN(Xthal_cp_id_,XCHAL_CP7_IDENT);
extern const unsigned int  XCJOIN(Xthal_cp_mask_,XCHAL_CP7_IDENT);
# endif
#endif




/*----------------------------------------------------------------------
				DERIVED
  ----------------------------------------------------------------------*/

#if XCHAL_HAVE_BE
#define XCHAL_INST_ILLN			0xD60F		/* 2字节非法指令，msb优先*/
#define XCHAL_INST_ILLN_BYTE0		0xD6		/* 2字节非法指令，第1字节*/
#define XCHAL_INST_ILLN_BYTE1		0x0F		/* 2字节非法指令，第2字节*/
#else
#define XCHAL_INST_ILLN			0xF06D		/* 2字节非法指令，lsb优先*/
#define XCHAL_INST_ILLN_BYTE0		0x6D		/* 2字节非法指令，第1字节*/
#define XCHAL_INST_ILLN_BYTE1		0xF0		/* 2字节非法指令，第2字节*/
#endif
/*  属于extensa/hal。小时：*/
#define XTHAL_INST_ILL			0x000000	/* 3字节非法指令*/


/*
 *  由于给定软件版本所针对的硬件版本的确切信息并不总是可用的，因此编译时HAL hardware Release“_AT”宏是模糊的（返回0、1或XCHAL_MAYBE）：（这里的“Release”现在用词不当；这些是产品版本，而不是发布它们的版本。在T10###时代没有区别。）
 */
#if XCHAL_HW_CONFIGID_RELIABLE
# define XCHAL_HW_RELEASE_AT_OR_BELOW(major,minor)	(XTHAL_REL_LE( XCHAL_HW_VERSION_MAJOR,XCHAL_HW_VERSION_MINOR, major,minor ) ? 1 : 0)
# define XCHAL_HW_RELEASE_AT_OR_ABOVE(major,minor)	(XTHAL_REL_GE( XCHAL_HW_VERSION_MAJOR,XCHAL_HW_VERSION_MINOR, major,minor ) ? 1 : 0)
# define XCHAL_HW_RELEASE_AT(major,minor)		(XTHAL_REL_EQ( XCHAL_HW_VERSION_MAJOR,XCHAL_HW_VERSION_MINOR, major,minor ) ? 1 : 0)
# define XCHAL_HW_RELEASE_MAJOR_AT(major)		((XCHAL_HW_VERSION_MAJOR == (major)) ? 1 : 0)
#else
# define XCHAL_HW_RELEASE_AT_OR_BELOW(major,minor)	( ((major) < 1040 && XCHAL_HAVE_XEA2) ? 0 \
							: ((major) > 1050 && XCHAL_HAVE_XEA1) ? 1 \
							: XTHAL_MAYBE )
# define XCHAL_HW_RELEASE_AT_OR_ABOVE(major,minor)	( ((major) >= 2000 && XCHAL_HAVE_XEA1) ? 0 \
							: (XTHAL_REL_LE(major,minor, 1040,0) && XCHAL_HAVE_XEA2) ? 1 \
							: XTHAL_MAYBE )
# define XCHAL_HW_RELEASE_AT(major,minor)		( (((major) < 1040 && XCHAL_HAVE_XEA2) || \
							   ((major) >= 2000 && XCHAL_HAVE_XEA1)) ? 0 : XTHAL_MAYBE)
# define XCHAL_HW_RELEASE_MAJOR_AT(major)		XCHAL_HW_RELEASE_AT(major,0)
#endif

#ifdef __cplusplus
}
#endif

#endif /*XTENSA_CONFIG_CORE_H*/

