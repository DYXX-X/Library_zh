/*
 * xtruntime。h—单线程运行时的通用C定义
 *
 * 版权所有（c）2002-2013 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTRUNTIME_H
#define XTRUNTIME_H

#include <xtensa/config/core.h>
#include <xtensa/config/specreg.h>
#include <xtensa/xtruntime-core-state.h>

#ifndef XTSTR
#define _XTSTR(x)	# x
#define XTSTR(x)	_XTSTR(x)
#endif

/*  _xtos_core_shutdoff（）标志参数值：*/
#define XTOS_KEEPON_MEM		0x00000100	/* ==PWRCTL_MEM_WAKEUP */
#define XTOS_KEEPON_MEM_SHIFT	8
#define XTOS_KEEPON_DEBUG	0x00001000	/* ==PWRCTL_DEBUG_WAKEUP */
#define XTOS_KEEPON_DEBUG_SHIFT	12

#define XTOS_IDMA_NO_WAIT	0x00010000	/* 不要等待idma完成。必要时禁用*/
#define XTOS_IDMA_WAIT_STANDBY	0x00020000	/* 也将待机状态视为等待结束*/

#define XTOS_COREF_PSO		0x00000001	/* 关闭电源*/
#define XTOS_COREF_PSO_SHIFT	0

#define _xtos_set_execption_handler _xtos_set_exception_handler	/* 向后兼容性*/
#define _xtos_set_saved_intenable	_xtos_ints_on	/* 向后兼容性*/
#define _xtos_clear_saved_intenable	_xtos_ints_off	/* 向后兼容性*/

#if !defined(_ASMLANGUAGE) && !defined(__ASSEMBLER__)

#ifdef __cplusplus
extern "C" {
#endif

#if defined(XTOS_MISRA)
typedef void (_xtos_handler_func)(void *);
#elif defined(__cplusplus)
typedef void (_xtos_handler_func)(...);
#else
typedef void (_xtos_handler_func)(void);
#endif
typedef _xtos_handler_func *_xtos_handler;

/*
 *  无符号XTOS_SET_INTLEVEL（int INTLEVEL）；此宏设置当前中断级别。“intlevel”参数必须是常量。此宏返回一个32位值，该值必须传递给XTOS_RESTORE_INTLEVEL（）以恢复先前的中断级别。XTOS_RESTORE_JUST_INTLEVEL（）也执行此操作，但在XEA2配置中，它只恢复PS.INTLEVEL而不是整个PS寄存器，因此速度较慢。
 */
#if !XCHAL_HAVE_INTERRUPTS
# define XTOS_SET_INTLEVEL(intlevel)		0
# define XTOS_SET_MIN_INTLEVEL(intlevel)	0
# define XTOS_RESTORE_INTLEVEL(restoreval)
# define XTOS_RESTORE_JUST_INTLEVEL(restoreval)
#elif XCHAL_HAVE_XEA2
/*  在XEA2中，我们可以直接安全地设置PS.INTLEVEL：*/
/*  注意：这些asm宏不修改内存，但它们被标记为这样，作为编译器的内存访问障碍，因为这些宏有时用于描绘关键部分；除非声明为内联，否则函数调用是自然的障碍（编译器不知道函数是否修改内存）。*/
# define XTOS_SET_INTLEVEL(intlevel)	__extension__({ unsigned __tmp; \
			__asm__ __volatile__(	"rsil	%0, " XTSTR(intlevel) "\n" \
						: "=a" (__tmp) : : "memory" ); \
			__tmp;})
# define XTOS_SET_MIN_INTLEVEL(intlevel)		({ unsigned __tmp, __tmp2, __tmp3; \
			__asm__ __volatile__(	"rsr.ps	%0\n"		/* 获取旧（当前）PS.INTLEVEL*/ \
						"movi	%2, " XTSTR(intlevel) "\n" \
						"extui	%1, %0, 0, 4\n"	/* 仅保留参数的INTLEVEL位*/ \
						"blt	%2, %1, 1f\n" \
						"rsil	%0, " XTSTR(intlevel) "\n" \
						"1:\n" \
						: "=a" (__tmp), "=&a" (__tmp2), "=&a" (__tmp3) : : "memory" ); \
			__tmp;})
# define XTOS_RESTORE_INTLEVEL(restoreval)	do{ unsigned __tmp = (restoreval); \
			__asm__ __volatile__(	"wsr.ps	%0 ; rsync\n" \
						: : "a" (__tmp) : "memory" ); \
			}while(0)
# define XTOS_RESTORE_JUST_INTLEVEL(restoreval)	_xtos_set_intlevel(restoreval)
#else
/*  在XEA1中，我们必须依赖INTABLE寄存器虚拟化：*/
extern unsigned		_xtos_set_vpri( unsigned vpri );
extern unsigned		_xtos_vpri_enabled;	/* 当前虚拟优先级*/
# define XTOS_SET_INTLEVEL(intlevel)		_xtos_set_vpri(~XCHAL_INTLEVEL_ANDBELOW_MASK(intlevel))
# define XTOS_SET_MIN_INTLEVEL(intlevel)	_xtos_set_vpri(_xtos_vpri_enabled & ~XCHAL_INTLEVEL_ANDBELOW_MASK(intlevel))
# define XTOS_RESTORE_INTLEVEL(restoreval)	_xtos_set_vpri(restoreval)
# define XTOS_RESTORE_JUST_INTLEVEL(restoreval)	_xtos_set_vpri(restoreval)
#endif

/*
 *  以下宏建立在上述基础上。通常使用它们来代替直接调用SET_INTLEVEL和SET_MIN_INTLEVE宏。它们都会返回一个值，该值可以与XTOS_RESTORE_INTLEVEL（）或_XTOS_RESTORE_INTLEVEL（）或x_tos_RESTORE_just_intlelevel（）一起使用，以将有效中断级别恢复到调用宏之前的状态。在XEA2中，DISABLE宏比MASK宏快得多（在所有配置中，DISADISABLE设置有效中断级别，而MASK确保有效中断级别至少是给定的级别而不降低；在具有INTABLE虚拟化的XEA2中这些宏仅影响PS.INTLEVEL，而不影响虚拟优先级，因此DISABLE具有部分MASK语义）。
 *
 *  典型的关键段序列可能是：无符号rval=XTOS_DISABLE_EXCM_INTERRUPTS。。。关键部分…XTOS_RESTORE_INTLEVEL（rval）；
 */
/*  启用所有中断（使用_xtos_ints_on（）激活的中断）：*/
#define XTOS_ENABLE_INTERRUPTS		XTOS_SET_INTLEVEL(0)
/*  禁用低优先级中断（它们可以与操作系统交互）：*/
#define XTOS_DISABLE_LOWPRI_INTERRUPTS	XTOS_SET_INTLEVEL(XCHAL_NUM_LOWPRI_LEVELS)
#define XTOS_MASK_LOWPRI_INTERRUPTS	XTOS_SET_MIN_INTLEVEL(XCHAL_NUM_LOWPRI_LEVELS)
/*  禁用可以与操作系统交互的中断：*/
#define XTOS_DISABLE_EXCM_INTERRUPTS	XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL)
#define XTOS_MASK_EXCM_INTERRUPTS	XTOS_SET_MIN_INTLEVEL(XCHAL_EXCM_LEVEL)
#if 0 /* XTOS_LOCK_LEVEL未导出到应用程序*/
/*  禁用可以与操作系统交互的中断，或操作虚拟INTABLE：*/
#define XTOS_DISABLE_LOCK_INTERRUPTS	XTOS_SET_INTLEVEL(XTOS_LOCK_LEVEL)
#define XTOS_MASK_LOCK_INTERRUPTS	XTOS_SET_MIN_INTLEVEL(XTOS_LOCK_LEVEL)
#endif
/*  禁用所有中断（不常用，尤其是当处理器配置具有高级中断且担心其延迟时）：*/
#define XTOS_DISABLE_ALL_INTERRUPTS	XTOS_SET_INTLEVEL(15)

/*  这两个都已弃用。使用以下更新的功能。*/
extern unsigned int	_xtos_ints_off( unsigned int mask );
extern unsigned int	_xtos_ints_on( unsigned int mask );

/* 启用/禁用指定中断的较新功能。*/
static inline void _xtos_interrupt_enable(unsigned int intnum)
{
    _xtos_ints_on(1U << intnum);
}

static inline void _xtos_interrupt_disable(unsigned int intnum)
{
    _xtos_ints_off(1U << intnum);
}

extern unsigned		_xtos_set_intlevel( int intlevel );
extern unsigned		_xtos_set_min_intlevel( int intlevel );
extern unsigned		_xtos_restore_intlevel( unsigned restoreval );
extern unsigned		_xtos_restore_just_intlevel( unsigned restoreval );
extern _xtos_handler	_xtos_set_interrupt_handler( int n, _xtos_handler f );
extern _xtos_handler	_xtos_set_interrupt_handler_arg( int n, _xtos_handler f, void *arg );
extern _xtos_handler	_xtos_set_exception_handler( int n, _xtos_handler f );

extern void		_xtos_memep_initrams( void );
extern void		_xtos_memep_enable( int flags );

/*  用于小型LSP（参见LSP参考手册）。*/
#if XCHAL_NUM_INTLEVELS >= 1
extern void		_xtos_dispatch_level1_interrupts( void );
#endif
#if XCHAL_NUM_INTLEVELS >= 2
extern void		_xtos_dispatch_level2_interrupts( void );
#endif
#if XCHAL_NUM_INTLEVELS >= 3
extern void		_xtos_dispatch_level3_interrupts( void );
#endif
#if XCHAL_NUM_INTLEVELS >= 4
extern void		_xtos_dispatch_level4_interrupts( void );
#endif
#if XCHAL_NUM_INTLEVELS >= 5
extern void		_xtos_dispatch_level5_interrupts( void );
#endif
#if XCHAL_NUM_INTLEVELS >= 6
extern void		_xtos_dispatch_level6_interrupts( void );
#endif

/*  已弃用（但因已记录而保留）：*/
extern unsigned int	_xtos_read_ints( void );
extern void		_xtos_clear_ints( unsigned int mask );


/*  电源关闭相关程序。*/
extern int		_xtos_core_shutoff(unsigned flags);
extern int		_xtos_core_save(unsigned flags, XtosCoreState *savearea, void *code);
extern void		_xtos_core_restore(unsigned retvalue, XtosCoreState *savearea);


#if XCHAL_NUM_CONTEXTS > 1
extern unsigned		_xtos_init_context(int context_num, int stack_size,
					    _xtos_handler_func *start_func, int arg1);
#endif

/*  不推荐：*/
#if XCHAL_NUM_TIMERS > 0
extern void		_xtos_timer_0_delta( int cycles );
#endif
#if XCHAL_NUM_TIMERS > 1
extern void		_xtos_timer_1_delta( int cycles );
#endif
#if XCHAL_NUM_TIMERS > 2
extern void		_xtos_timer_2_delta( int cycles );
#endif
#if XCHAL_NUM_TIMERS > 3
extern void		_xtos_timer_3_delta( int cycles );
#endif

#ifdef __cplusplus
}
#endif

#endif /* !_ASMLANGUAGE && !__ASSEMBLER__ */

#endif /* XTRUNTIME_H */

