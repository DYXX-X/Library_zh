/*
 * extensa/core宏。h—依赖于CORE配置的C特定定义
 */

/*
 * 版权所有（c）2012 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTENSA_CACHE_H
#define XTENSA_CACHE_H

#include <xtensa/config/core.h>

/*  只定义C代码的内容。*/
#if !defined(_ASMLANGUAGE) && !defined(_NOCLANGUAGE) && !defined(__ASSEMBLER__)



/***************************   CACHE   ***************************/

/* 所有的宏现在都是小写的，其中一些宏与hal.h中的现有函数共享名称。包括这个头文件将定义XTHAL_USE_CACHE_macros，它指导hal。h不使用功能。
 *

 *
 *  C可调用内联程序集中的单缓存行操作。基本上宏版本（大写）：
 *
 *	xthal_icache_line_invalidate(void *地址）；xthal_icache_line_lock（无效地址）；xthal_icache_line_unlock（无效地址）；xthal_icache_sync（无效）；
 *
 *  注意：与上述函数不同，以下宏不会在每行操作中执行xthal_icache_sync（）。调用方必须显式调用此同步。这是为了在多条线路上运行时实现更好的优化。
 *
 *	xthal_dcache_line_invalidate(void *地址）；xthal_dcache_line_writeback（无效地址）；xthal_dcache_line_writeback_inv（无效地址）；xthal_dcache_line_lock（无效地址）；xthal_dcache_line_unlock（无效地址）；xthal_dcache_sync（无效）；xthal_dcache_line_prefetchfor_write（无效地址）；xthal_dcache_line_prefetchfor_read（无效地址）；
 *
 *  所有这些都被设置为内存屏障，因为这是它们通常使用的方式（操作在一整行上运行，因此会破坏所有内存，而不仅仅是addr）。
 *
 *  注意：所有块块缓存操作和行预取都是使用内部函数实现的，因此它们在内存屏障等方面得到了更好的优化。
 *
 * 所有块降级函数都有两种形式：带和不带“max”参数：此参数允许编译器在参数小于缓存大小时优化函数。
 *
 *	xthal_dcache_block_invalidate(void *addr、无符号大小）；xthal_dcache_block_writeback（无效地址，无符号大小）；xthal_dcache_block_writeback_inv（无效地址，无符号大小）；xthal_dcache_block_invalidate_max（无效地址，无符号大小，无符号最大值）；xthal_dcache_block_writeback_max（无效地址，无符号大小，无符号最大值）；xthal_dcache_block_writeback_inv_max（无效地址，无符号大小，无符号最大值）；
 *
 *      xthal_dcache_block_prefetch_for_read（void*addr，无符号大小）；xthal_dcache_block_prefetch_for_write（无效地址，无符号大小）；xthal_dcache_block_prefetch_modify（无效地址，无符号大小）；xthal_dcache_block_prefetch_read_write（无效地址，无符号大小）；xthal_dcache_block_prefetchfor_read_grp（无效地址，无符号大小）；xthal_dcache_block_prefetch_for_write_grp（无效地址，无符号大小）；xthal_dcache_block_prefetch_modify_grp（无效地址，无符号大小）；xthal_dcache_block_prefetch_read_write_grp（无效地址，无符号大小）
 *
 *	xthal_dcache_block_wait(); xthal_dcache_block_required_wait（）；xthal_dcache_block_abort（）；xthal_dcache_block_prefetch_end（）；xthal_dcache_block_newgrp（）；
 */

/***   INSTRUCTION CACHE   ***/

#define XTHAL_USE_CACHE_MACROS

#if XCHAL_ICACHE_SIZE > 0
# define xthal_icache_line_invalidate(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("ihi %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
#else
# define xthal_icache_line_invalidate(addr)	do {/*没有什么*/} while(0)
#endif

#if XCHAL_ICACHE_SIZE > 0 && XCHAL_ICACHE_LINE_LOCKABLE
# define xthal_icache_line_lock(addr)	do { void *__a = (void*)(addr);	 	\
		__asm__ __volatile__("ipfl %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_icache_line_unlock(addr)	do { void *__a = (void*)(addr); 	\
		__asm__ __volatile__("ihu %0, 0" :: "a"(__a) : "memory");	\
		} while(0)
#else
# define xthal_icache_line_lock(addr)		do {/*没有什么*/} while(0)
# define xthal_icache_line_unlock(addr)		do {/*没有什么*/} while(0)
#endif

/*
 * 即使一个配置没有缓存，当任何内存中的指令被修改时，无论是通过加载器还是自修改代码，仍然需要isync。因此，无论是否存在icache，此宏始终生成isync。
 */
#define xthal_icache_sync()							\
		__asm__ __volatile__("isync":::"memory")


/***   DATA CACHE   ***/

#if XCHAL_DCACHE_SIZE > 0

# include <xtensa/tie/xt_datacache.h>

# define xthal_dcache_line_invalidate(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("dhi %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_line_writeback(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("dhwb %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_line_writeback_inv(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("dhwbi %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_sync()							\
		__asm__ __volatile__("" /*“dsync”？*/:::"memory")
# define xthal_dcache_line_prefetch_for_read(addr) do {				\
		XT_DPFR((const int*)addr, 0);					\
		} while(0)
#else
# define xthal_dcache_line_invalidate(addr)		do {/*没有什么*/} while(0)
# define xthal_dcache_line_writeback(addr)		do {/*没有什么*/} while(0)
# define xthal_dcache_line_writeback_inv(addr)		do {/*没有什么*/} while(0)
# define xthal_dcache_sync()				__asm__ __volatile__("":::"memory")
# define xthal_dcache_line_prefetch_for_read(addr)	do {/*没有什么*/} while(0)
#endif

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_DCACHE_LINE_LOCKABLE
# define xthal_dcache_line_lock(addr)	do { void *__a = (void*)(addr); 	\
		__asm__ __volatile__("dpfl %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_line_unlock(addr)	do { void *__a = (void*)(addr); 	\
		__asm__ __volatile__("dhu %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
#else
# define xthal_dcache_line_lock(addr)		do {/*没有什么*/} while(0)
# define xthal_dcache_line_unlock(addr)		do {/*没有什么*/} while(0)
#endif

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_DCACHE_IS_WRITEBACK

# define xthal_dcache_line_prefetch_for_write(addr) do {			\
		XT_DPFW((const int*)addr, 0);					\
		} while(0)
#else
# define xthal_dcache_line_prefetch_for_write(addr)	do {/*没有什么*/} while(0)
#endif


/*****阻止操作*****/

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_HAVE_CACHE_BLOCKOPS

/* 升级*/

# define _XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, type)		\
		{						\
		type((const int*)addr, size);			\
		}

/*降级*/

# define _XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, type)	\
	unsigned _s = size;					\
	unsigned _a = (unsigned) addr;					\
	do {							\
		unsigned __s = (_s > XCHAL_DCACHE_SIZE) ? 	\
				XCHAL_DCACHE_SIZE : _s; 	\
		type((const int*)_a, __s);			\
		_s -= __s; 					\
		_a += __s;					\
	} while(_s > 0);

# define _XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, type, max)	\
	if (max <= XCHAL_DCACHE_SIZE) {					\
		unsigned _s = size;					\
		unsigned _a = (unsigned) addr;					\
		type((const int*)_a, _s);				\
	}								\
	else {								\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, type);	\
	}

# define xthal_dcache_block_invalidate(addr, size)	do { 		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, XT_DHI_B);	\
		} while(0)
# define xthal_dcache_block_writeback(addr, size)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, XT_DHWB_B);	\
		} while(0)
# define xthal_dcache_block_writeback_inv(addr, size)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, XT_DHWBI_B);	\
		} while(0)

# define xthal_dcache_block_invalidate_max(addr, size, max)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, XT_DHI_B, max);	\
		} while(0)
# define xthal_dcache_block_writeback_max(addr, size, max)	do { 		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, XT_DHWB_B, max);	\
		} while(0)
# define xthal_dcache_block_writeback_inv_max(addr, size, max)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, XT_DHWBI_B, max);	\
		} while(0)

/* 即使使用直写缓存也可以执行的升级*/

# define xthal_dcache_block_prefetch_read_write(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_read_write_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_BF);	\
		} while(0)
# define xthal_dcache_block_prefetch_for_read(addr, size) do {		\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFR_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_for_read_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFR_BF);	\
		} while(0)

/* 中止所有或结束可选的块缓存操作*/
# define xthal_dcache_block_abort()	do { 		\
		XT_PFEND_A();				\
		} while(0)
# define xthal_dcache_block_end()	do { 		\
		XT_PFEND_O();				\
		} while(0)

/* 等待所有/所需的块缓存操作完成*/
# define xthal_dcache_block_wait()	do { 		\
		XT_PFWAIT_A();				\
		} while(0)
# define xthal_dcache_block_required_wait()	do { 	\
		XT_PFWAIT_R();				\
		} while(0)
/* 启动新组*/
# define xthal_dcache_block_newgrp()	do { 		\
		XT_PFNXT_F();				\
		} while(0)
#else
# define xthal_dcache_block_invalidate(addr, size)		do {/*没有什么*/} while(0)
# define xthal_dcache_block_writeback(addr, size)		do {/*没有什么*/} while(0)
# define xthal_dcache_block_writeback_inv(addr, size)		do {/*没有什么*/} while(0)
# define xthal_dcache_block_invalidate_max(addr, size, max)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_writeback_max(addr, size, max)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_writeback_inv_max(addr, size, max) 	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_read_write(addr, size)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_read_write_grp(addr, size)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_for_read(addr, size)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_for_read_grp(addr, size)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_end()   				do {/*没有什么*/} while(0)
# define xthal_dcache_block_abort()  				do {/*没有什么*/} while(0)
# define xthal_dcache_block_wait()  				do {/*没有什么*/} while(0)
# define xthal_dcache_block_required_wait()   			do {/*没有什么*/} while(0)
# define xthal_dcache_block_newgrp()				do {/*没有什么*/} while(0)
#endif

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_HAVE_CACHE_BLOCKOPS && XCHAL_DCACHE_IS_WRITEBACK

# define xthal_dcache_block_prefetch_for_write(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_modify(addr, size) do {		\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFM_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_for_write_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_BF);	\
		} while(0)
# define xthal_dcache_block_prefetch_modify_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFM_BF);	\
		} while(0)
#else
# define xthal_dcache_block_prefetch_for_write(addr, size)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_modify(addr, size) 	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_for_write_grp(addr, size)	do {/*没有什么*/} while(0)
# define xthal_dcache_block_prefetch_modify_grp(addr, size)  	do {/*没有什么*/} while(0)
#endif

/***************************   INTERRUPTS   ***************************/

/*
 *  宏版本：unsigned xthal_get_intenable（void）；无效xthal_set_intenable（无符号）；无符号xthal_get_interrupt（无效）；无效xthal_set_intset（无符号）；无效xthal_set_intclear（无符号）；无符号xthal_get_ccount（void）；无效xthal_set_ccompare（int，无符号）；无符号xthal_get_ccompare（int）；
 *
 *  注意：对于｛set，get｝_ccompare，第一个参数必须是十进制常量。
 */

#if XCHAL_HAVE_INTERRUPTS
# define XTHAL_GET_INTENABLE()	({ int __intenable; \
				__asm__("rsr.intenable %0" : "=a"(__intenable)); \
				__intenable; })
# define XTHAL_SET_INTENABLE(v)	do { int __intenable = (int)(v); \
			__asm__ __volatile__("wsr.intenable %0" :: "a"(__intenable):"memory"); \
				} while(0)
# define XTHAL_GET_INTERRUPT()	({ int __interrupt; \
				__asm__ __volatile__("rsr.interrupt %0" : "=a"(__interrupt)); \
				__interrupt; })
# define XTHAL_SET_INTSET(v)	do { int __interrupt = (int)(v); \
			__asm__ __volatile__("wsr.intset %0" :: "a"(__interrupt):"memory"); \
				} while(0)
# define XTHAL_SET_INTCLEAR(v)	do { int __interrupt = (int)(v); \
			__asm__ __volatile__("wsr.intclear %0" :: "a"(__interrupt):"memory"); \
				} while(0)
# define XTHAL_GET_CCOUNT()	({ int __ccount; \
				__asm__ __volatile__("rsr.ccount %0" : "=a"(__ccount)); \
				__ccount; })
# define XTHAL_SET_CCOUNT(v)	do { int __ccount = (int)(v); \
			__asm__ __volatile__("wsr.ccount %0" :: "a"(__ccount):"memory"); \
				} while(0)
# define _XTHAL_GET_CCOMPARE(n)	({ int __ccompare; \
				__asm__("rsr.ccompare" #n " %0" : "=a"(__ccompare)); \
				__ccompare; })
# define XTHAL_GET_CCOMPARE(n)	_XTHAL_GET_CCOMPARE(n)
# define _XTHAL_SET_CCOMPARE(n,v) do { int __ccompare = (int)(v); \
			__asm__ __volatile__("wsr.ccompare" #n " %0 ; esync" :: "a"(__ccompare):"memory"); \
				} while(0)
# define XTHAL_SET_CCOMPARE(n,v) _XTHAL_SET_CCOMPARE(n,v)
#else
# define XTHAL_GET_INTENABLE()		0
# define XTHAL_SET_INTENABLE(v)		do {/*没有什么*/} while(0)
# define XTHAL_GET_INTERRUPT()		0
# define XTHAL_SET_INTSET(v)		do {/*没有什么*/} while(0)
# define XTHAL_SET_INTCLEAR(v)		do {/*没有什么*/} while(0)
# define XTHAL_GET_CCOUNT()		0
# define XTHAL_SET_CCOUNT(v)		do {/*没有什么*/} while(0)
# define XTHAL_GET_CCOMPARE(n)		0
# define XTHAL_SET_CCOMPARE(n,v)	do {/*没有什么*/} while(0)
#endif

/*  添加新功能以适应XEA3，并允许弃用旧功能。对于这个版本，它们只映射到旧版本。*/

/*  启用指定的中断。*/
static inline void xthal_interrupt_enable(unsigned intnum)
{
    xthal_int_enable(1 << intnum);
}

/*  禁用指定的中断。*/
static inline void xthal_interrupt_disable(unsigned intnum)
{
    xthal_int_disable(1 << intnum);
}

/*  触发指定的中断。*/
static inline void xthal_interrupt_trigger(unsigned intnum)
{
    xthal_set_intset(1 << intnum);
}

/*  清除指定的中断。*/
static inline void xthal_interrupt_clear(unsigned intnum)
{
    xthal_set_intclear(1 << intnum);
}


/***************************   MISC   ***************************/

/*
 *  宏或内联版本：void xthal_clear_regcached_code（void）；无符号xthal_get_prid（void）；无符号xthal_compare_and_set（int addr，int testval，int setval）；
 */

#if XCHAL_HAVE_LOOPS
# define XTHAL_CLEAR_REGCACHED_CODE()		\
		__asm__ __volatile__("wsr.lcount %0" :: "a"(0) : "memory")
#else
# define XTHAL_CLEAR_REGCACHED_CODE()		do {/*没有什么*/} while(0)
#endif

#if XCHAL_HAVE_PRID
# define XTHAL_GET_PRID()	({ int __prid; \
				__asm__("rsr.prid %0" : "=a"(__prid)); \
				__prid; })
#else
# define XTHAL_GET_PRID()	0
#endif


static inline unsigned  XTHAL_COMPARE_AND_SET( int *addr, int testval, int setval )
{
    int result;

#if XCHAL_HAVE_S32C1I && XCHAL_HW_MIN_VERSION_MAJOR >= 2200
    __asm__ __volatile__ (
	"   wsr.scompare1 %2 \n"
	"   s32c1i %0, %3, 0 \n"
	    : "=a"(result) : "0" (setval), "a" (testval), "a" (addr)
	    : "memory");
#elif XCHAL_HAVE_INTERRUPTS
    int tmp;
    __asm__ __volatile__ (
        "   rsil   %4, 15 \n"		// %4==已保存ps
        "   l32i   %0, %3, 0 \n"	// %0==要测试的值，返回值
        "   bne    %2, %0, 9f \n"	// 测验
        "   s32i   %1, %3, 0 \n"	// 写入新值
	"9: wsr.ps %4 ; rsync \n"	// 恢复PS
	: "=a"(result)
	: "0" (setval), "a" (testval), "a" (addr), "a" (tmp)
	: "memory");
#else
    __asm__ __volatile__ (
        "   l32i  %0, %3, 0 \n"		// %0==要测试的值，返回值
        "   bne   %2, %0, 9f \n"	// 测验
        "   s32i  %1, %3, 0 \n"		// 写入新值
	"9: \n"
	    : "=a"(result) : "0" (setval), "a" (testval), "a" (addr)
	    : "memory");
#endif
    return result;
}

#if XCHAL_HAVE_EXTERN_REGS

static inline unsigned XTHAL_RER (unsigned int reg)
{
  unsigned result;

  __asm__ __volatile__ (
	"   rer     %0, %1"
	: "=a" (result) : "a" (reg) : "memory");

  return result;
}

static inline void XTHAL_WER (unsigned reg, unsigned value)
{
  __asm__ __volatile__ (
	"   wer     %0, %1"
	: : "a" (value), "a" (reg) : "memory");
}

#endif /* XCHAL_HAVE_EXTERN_REGS */

/*
 * 在MPU内的“索引”处设置单个条目
 *
 * 调用方必须确保生成的MPU映射是有序的。
 */
static inline void xthal_mpu_set_entry (xthal_MPU_entry entry)
{
#if XCHAL_HAVE_MPU
  __asm__ __volatile__("j 1f\n\t.align 8\n\t1: memw\n\twptlb %0, %1\n\t" : : "a" (entry.at), "a"(entry.as));
#endif
}

/* 与xthal_mpu_set_entry相同，但此函数不能用于更改当前执行指令的mpu条目…请改用xthal_mpu_set_entr。*/
static inline void xthal_mpu_set_entry_ (xthal_MPU_entry entry)
{
#if XCHAL_HAVE_MPU
  __asm__ __volatile__("wptlb %0, %1\n\t" : : "a" (entry.at), "a"(entry.as));
#endif
}



#endif /* C代码*/

#endif /*XTENSA_CACHE_H*/

