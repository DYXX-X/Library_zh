/*
   延伸/致死。h——包含核心HAL接口的定义

   此头文件中的所有定义都独立于任何特定的Xtensa处理器配置。因此，软件（例如OS、应用程序等）可以包含这个头文件，并编译成独立于配置的对象，这些对象可以被分发并最终链接到HAL库（libhal.a），以创建特定于配置的最终可执行文件。

   然而，某些定义是特定于发行版/版本的，例如XTHAL_release_xxx宏（或在更高版本中添加的）。

 $Id://depot/rel/Foxhill.dot.9/Xtensa/OS/target OS src/hal.h.tpp#1$

   版权所有（c）1999-2015 Cadence Design Systems，Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef XTENSA_HAL_H
#define XTENSA_HAL_H

/****************************************************************************
适用于任何代码、用户或特权的定义
 ****************************************************************************/


/*----------------------------------------------------------------------
常量定义（与程序集共享）
  ----------------------------------------------------------------------*/

/*
 *  软件（Xtensa Tools）版本信息。不特定于配置！
 *
 *  注意：“release”在这里用词不当，这些实际上是产品的“版本”编号。“发布”是一系列产品版本的集合，可同时（一起）提供给客户。在过去，发布和版本名称都在T####中匹配。#形式，使区别变得无关紧要。现在已经不是这样了。
 */
#define XTHAL_RELEASE_MAJOR	12000
#define XTHAL_RELEASE_MINOR	9
#define XTHAL_RELEASE_NAME	"12.0.9"
#define XTHAL_REL_12	1
#define XTHAL_REL_12_0	1
#define XTHAL_REL_12_0_9	1

/*  HAL版本号（这些名称用于向后兼容）：*/
#define XTHAL_MAJOR_REV		XTHAL_RELEASE_MAJOR
#define XTHAL_MINOR_REV		XTHAL_RELEASE_MINOR
/*
 *  关于XTHAL_{MAJOR，MINOR}_REV值的一些软件发布/版本历史：
 *
 *	SW 版本主要次要注释==============T1015.n n/a n/a（HAL尚未提供）T1020.｛0,1,2｝0 1（HAL测试版）T1020.{3,4｝2首次发布。T1020.n（n>4）0 2或>3（TBD）T1030.0 0 1（HAL beta）T1030.｛1，2｝0 3等同于首次发布。T1030.n（n>=3）0>=3（TBD）T1040.n 1040 n完整CHAL，可从T1040.2 T1050.n 1050 n 6.0.n 6000 n Xtensa Tools v6（RA-200x.n）7.0.n 7000 n Xtensa-Tools v7（RB-200x.n n个）
 *
 * 注意：编译某些内容的软件版本（可使用XTHAL_RELEASE_宏访问）与编译HAL库的软件版本之间存在差异（可使用XTHAL_RELEASE_全局变量访问）。这一区别对于分发独立于配置的二进制文件（例如OS）的供应商尤其重要，因为他们的客户可能会将其与不同Xtensa软件版本的HAL链接。在这种情况下，操作系统可以在运行时验证XTHAL_RELEASE_和XTHAL_RELEASE_是否兼容。[关于哪个版本与哪个版本兼容的指导原则目前没有明确提供，但可以从阅读所有版本的OSKit文档中推断出来--兼容性也高度依赖于使用的HAL功能。每个版本通常都是向后兼容的，只有极少数例外（如果有的话）。]
 */

/*  版本比较运算符（主要/次要对之间）：*/
#define XTHAL_REL_GE(maja,mina, majb,minb)	((maja) > (majb) || \
						 ((maja) == (majb) && (mina) >= (minb)))
#define XTHAL_REL_GT(maja,mina, majb,minb)	((maja) > (majb) || \
						 ((maja) == (majb) && (mina) > (minb)))
#define XTHAL_REL_LE(maja,mina, majb,minb)	((maja) < (majb) || \
						 ((maja) == (majb) && (mina) <= (minb)))
#define XTHAL_REL_LT(maja,mina, majb,minb)	((maja) < (majb) || \
						 ((maja) == (majb) && (mina) < (minb)))
#define XTHAL_REL_EQ(maja,mina, majb,minb)	((maja) == (majb) && (mina) == (minb))

/*  模糊（三向）逻辑运算符：*/
#define XTHAL_MAYBE		-1	/* 0=NO, 1=YES, -1=MAYBE */
#define XTHAL_FUZZY_AND(a,b)	(((a)==0 || (b)==0) ? 0 : ((a)==1 && (b)==1) ? 1 : XTHAL_MAYBE)
#define XTHAL_FUZZY_OR(a,b)	(((a)==1 || (b)==1) ? 1 : ((a)==0 && (b)==0) ? 0 : XTHAL_MAYBE)
#define XTHAL_FUZZY_NOT(a)	(((a)==0 || (a)==1) ? (1-(a)) : XTHAL_MAYBE)


/*
 *  独立于配置的架构限制：
 */
#define XTHAL_MAX_CPS		8	/* 协处理器的最大数量（0..7）*/

/*  其他：*/
#define XTHAL_LITTLEENDIAN		0
#define XTHAL_BIGENDIAN			1



#if !defined(_ASMLANGUAGE) && !defined(_NOCLANGUAGE) && !defined(__ASSEMBLER__)
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/*----------------------------------------------------------------------
				HAL
  ----------------------------------------------------------------------*/

/* 要在内部版本中检查的常量=（XTHAL_MAJOR_REV<<16）|XTHAL_MINOR_REV*/
extern const unsigned int Xthal_rev_no;


/*----------------------------------------------------------------------
可选/自定义处理器状态
  ----------------------------------------------------------------------*/

/* 保存并恢复额外的处理器状态*/
extern void xthal_save_extra(void *base);
extern void xthal_restore_extra(void *base);

extern void xthal_save_cpregs(void *base, int);
extern void xthal_restore_cpregs(void *base, int);
/* 特定于每个协处理器id的版本*/
extern void xthal_save_cp0(void *base);
extern void xthal_save_cp1(void *base);
extern void xthal_save_cp2(void *base);
extern void xthal_save_cp3(void *base);
extern void xthal_save_cp4(void *base);
extern void xthal_save_cp5(void *base);
extern void xthal_save_cp6(void *base);
extern void xthal_save_cp7(void *base);
extern void xthal_restore_cp0(void *base);
extern void xthal_restore_cp1(void *base);
extern void xthal_restore_cp2(void *base);
extern void xthal_restore_cp3(void *base);
extern void xthal_restore_cp4(void *base);
extern void xthal_restore_cp5(void *base);
extern void xthal_restore_cp6(void *base);
extern void xthal_restore_cp7(void *base);
/* 指向上述每个函数的指针*/
extern void* Xthal_cpregs_save_fn[XTHAL_MAX_CPS];
extern void* Xthal_cpregs_restore_fn[XTHAL_MAX_CPS];
/* 类似地，对于非窗口ABI（可能相同或不同）*/
extern void* Xthal_cpregs_save_nw_fn[XTHAL_MAX_CPS];
extern void* Xthal_cpregs_restore_nw_fn[XTHAL_MAX_CPS];

/*外部空隙xthal_save_all_extra（空隙*基底）；*/
/*extern void xthal_restore_all_extra（void*base）；*/

/* 处理器状态空间*/
extern const unsigned int Xthal_extra_size;
extern const unsigned int Xthal_extra_align;
extern const unsigned int Xthal_cpregs_size[XTHAL_MAX_CPS];
extern const unsigned int Xthal_cpregs_align[XTHAL_MAX_CPS];
extern const unsigned int Xthal_all_extra_size;
extern const unsigned int Xthal_all_extra_align;
/* 协处理器名称*/
extern const char * const Xthal_cp_names[XTHAL_MAX_CPS];

/* 初始化额外的处理器*/
/*外部无效xthal_init_extra（无效）；*/
/* 初始化TIE协处理器*/
/*外部无效xthal_init_cp（int）；*/

/* 初始化额外的处理器*/
extern void xthal_init_mem_extra(void *);
/* 初始化TIE协处理器*/
extern void xthal_init_mem_cp(void *, int);

/* 从零开始连续的TIE协处理器的数量（对于Tor2）*/
extern const unsigned int Xthal_num_coprocessors;

/* 协处理器的实际数量*/
extern const unsigned char Xthal_cp_num;
/* 最高编号协处理器索引，加1*/
extern const unsigned char Xthal_cp_max;
/* 每个cfg允许的最高协处理器数的索引加1*/
/*外部常量无符号字符Xtal_cp_maxcfg；*/
/* 存在协处理器的位掩码*/
extern const unsigned int  Xthal_cp_mask;

/* 读写额外状态寄存器*/
/*extern int xthal_read_extra（void*base，unsigned reg，unsigned*value）；*/
/*extern int xthal_write_extra（void*base，unsigned reg，unsignedvalue）；*/

/* 读写TIE协处理器寄存器*/
/*extern int xthal_read_cpreg（void*base，int cp，unsigned reg，unsigned*value）；*/
/*extern int xthal_write_cpreg（void*base，int cp，unsigned reg，unsignedvalue）；*/

/* 基于寄存器返回协处理器号*/
/*extern int xthal_which_cp（无符号reg）；*/


/*----------------------------------------------------------------------
   注册Windows
  ----------------------------------------------------------------------*/

/* 寄存器窗口中的寄存器数*/
extern const unsigned int  Xthal_num_aregs;
extern const unsigned char Xthal_num_aregs_log2;


/*----------------------------------------------------------------------
   隐藏物
  ----------------------------------------------------------------------*/

/* log2中缓存行的大小（字节）*/
extern const unsigned char Xthal_icache_linewidth;
extern const unsigned char Xthal_dcache_linewidth;
/* 缓存行的大小（字节）（2^线宽）*/
extern const unsigned short Xthal_icache_linesize;
extern const unsigned short Xthal_dcache_linesize;

/* 缓存大小（字节）（方式*2^（线宽+设置宽度））*/
extern const unsigned int  Xthal_icache_size;
extern const unsigned int  Xthal_dcache_size;
/* 缓存功能*/
extern const unsigned char Xthal_dcache_is_writeback;

/* 缓存区域操作*/
extern void xthal_icache_region_invalidate( void *addr, unsigned size );
extern void xthal_dcache_region_invalidate( void *addr, unsigned size );
extern void xthal_dcache_region_writeback( void *addr, unsigned size );
extern void xthal_dcache_region_writeback_inv( void *addr, unsigned size );

#ifndef XTHAL_USE_CACHE_MACROS
/* 缓存行操作*/
extern void xthal_icache_line_invalidate(void *addr);
extern void xthal_dcache_line_invalidate(void *addr);
extern void xthal_dcache_line_writeback(void *addr);
extern void xthal_dcache_line_writeback_inv(void *addr);
/* 同步icache和内存*/
extern void xthal_icache_sync( void );
/* 同步dcache和内存*/
extern void xthal_dcache_sync( void );
#endif

/* 获取/设置启用的icache方式数*/
extern unsigned int xthal_icache_get_ways(void);
extern void         xthal_icache_set_ways(unsigned int ways);
/* 获取/设置已启用的dcache方式数*/
extern unsigned int xthal_dcache_get_ways(void);
extern void         xthal_dcache_set_ways(unsigned int ways);

/* 一致性（低级--通常不直接调用）*/
extern void xthal_cache_coherence_on( void );
extern void xthal_cache_coherence_off( void );
/* 一致性（高级）*/
extern void xthal_cache_coherence_optin( void );
extern void xthal_cache_coherence_optout( void );

/*
 *  缓存预取控制。xthal_set_cache_prefetch（）的参数包含PREFCTL寄存器值和要实际修改的位掩码。这允许通过“或”运算轻松组合字段宏（如下），而不修改未指定的字段。
 *
 *  为了与此例程的旧版本向后兼容（在32位参数中采用15位值和掩码，对于仅定义了较低15位PREFCTL的预RF核心），32位值和屏蔽在64位参数中交错如下：如果设置了参数[31]，则参数[63:48]为PREFCTL[31:16]；如果设置了param[31]，0如果参数[31:16]未设置，则为掩码[15:0]如果参数[31]已设置，则参数[3:16]为PREFCTL[31:16]如果参数[33]已清除，则参数[15:0]为PREFCCTL[15:0]
 *
 *  限制：PREFCTL寄存器位31不能在没有掩码的情况下设置，而位15必须在使用掩码时始终设置，因此希望这两个位保持保留，在PREFCTL中读取为零。
 */
#define XTHAL_PREFETCH_ENABLE		-1	/* 启用inst+数据预取*/
#define XTHAL_PREFETCH_DISABLE		0xFFFF0000 /* 禁用指令+数据预取*/
#define XTHAL_DCACHE_PREFETCH(n)	(0x800F0000+((n)&0xF))   /* 数据侧*/
#define XTHAL_DCACHE_PREFETCH_OFF	XTHAL_DCACHE_PREFETCH(0) /* 使残废*/
#define XTHAL_DCACHE_PREFETCH_LOW	XTHAL_DCACHE_PREFETCH(4) /* 较少聚集。*/
#define XTHAL_DCACHE_PREFETCH_MEDIUM	XTHAL_DCACHE_PREFETCH(5) /* 中间聚集。*/
#define XTHAL_DCACHE_PREFETCH_HIGH	XTHAL_DCACHE_PREFETCH(8) /* 更多聚集。*/
#define XTHAL_DCACHE_PREFETCH_L1_OFF	0x90000000	/* 预取缓冲区*/
#define XTHAL_DCACHE_PREFETCH_L1	0x90001000	/* 直接到L1 dcache*/
#define XTHAL_ICACHE_PREFETCH(n)	(0x80F00000+(((n)&0xF)<<4)) /* i侧*/
#define XTHAL_ICACHE_PREFETCH_OFF	XTHAL_ICACHE_PREFETCH(0) /* 使残废*/
#define XTHAL_ICACHE_PREFETCH_LOW	XTHAL_ICACHE_PREFETCH(4) /* 较少聚集。*/
#define XTHAL_ICACHE_PREFETCH_MEDIUM	XTHAL_ICACHE_PREFETCH(5) /* 中间聚集。*/
#define XTHAL_ICACHE_PREFETCH_HIGH	XTHAL_ICACHE_PREFETCH(8) /* 更多聚集。*/
#define XTHAL_ICACHE_PREFETCH_L1_OFF	0xA0000000	/* （未实施）*/
#define XTHAL_ICACHE_PREFETCH_L1	0xA0002000	/* （未实施）*/
#define _XTHAL_PREFETCH_BLOCKS(n)	((n)<0?0:(n)<5?(n):(n)<15?((n)>>1)+2:9)
#define XTHAL_PREFETCH_BLOCKS(n)	(0x0000000F80000000ULL + \
					(((unsigned long long)_XTHAL_PREFETCH_BLOCKS(n))<<48))

extern int  xthal_get_cache_prefetch( void );
extern int  xthal_set_cache_prefetch( int );
extern int  xthal_set_cache_prefetch_long( unsigned long long );
/*  从现在起仅使用新的扩展功能：*/
#define xthal_set_cache_prefetch	xthal_set_cache_prefetch_long
#define xthal_set_cache_prefetch_nw	xthal_set_cache_prefetch_long_nw


/*----------------------------------------------------------------------
   调试
  ----------------------------------------------------------------------*/

/*  如果配置了调试选项，则为1；如果未配置，则为0：*/
extern const int Xthal_debug_configured;

/*  设置（工厂）和删除软件断点，同时同步缓存：*/
extern unsigned int xthal_set_soft_break(void *addr);
extern void         xthal_remove_soft_break(void *addr, unsigned int);


/*----------------------------------------------------------------------
   拆卸器
  ----------------------------------------------------------------------*/

/*  反汇编指令的返回缓冲区的最大预期大小（仅提示）：*/
#define XTHAL_DISASM_BUFSIZE	80

/*  用于选择要返回的内容的反汇编选项位：*/
#define XTHAL_DISASM_OPT_ADDR	0x0001	/* 显示地址*/
#define XTHAL_DISASM_OPT_OPHEX	0x0002	/* 以十六进制显示操作码字节*/
#define XTHAL_DISASM_OPT_OPCODE	0x0004	/* 显示操作码名称（助记符）*/
#define XTHAL_DISASM_OPT_PARMS	0x0008	/* 显示参数*/
#define XTHAL_DISASM_OPT_ALL	0x0FFF	/* 显示所有内容*/

/* 获取反汇编指令字符串的例程*/
extern int xthal_disassemble( unsigned char *instr_buf, void *tgt_addr,
		       char *buffer, unsigned buflen, unsigned options );

/* 例程获取下一条指令的大小。对于非法指令，返回0*/
extern int xthal_disassemble_size( unsigned char *instr_buf );


/*----------------------------------------------------------------------
指令/数据RAM/ROM访问
  ----------------------------------------------------------------------*/

extern void* xthal_memcpy(void *dst, const void *src, unsigned len);
extern void* xthal_bcopy(const void *src, void *dst, unsigned len);


/*----------------------------------------------------------------------
                           MP同步
  ----------------------------------------------------------------------*/

extern int      xthal_compare_and_set( int *addr, int test_val, int compare_val );

/*外部常量字符Xtal_have_s32c1i；*/


/*----------------------------------------------------------------------
                             混杂的
  ----------------------------------------------------------------------*/

extern const unsigned int  Xthal_release_major;
extern const unsigned int  Xthal_release_minor;
extern const char * const  Xthal_release_name;
extern const char * const  Xthal_release_internal;

extern const unsigned char Xthal_memory_order;
extern const unsigned char Xthal_have_windowed;
extern const unsigned char Xthal_have_density;
extern const unsigned char Xthal_have_booleans;
extern const unsigned char Xthal_have_loops;
extern const unsigned char Xthal_have_nsa;
extern const unsigned char Xthal_have_minmax;
extern const unsigned char Xthal_have_sext;
extern const unsigned char Xthal_have_clamps;
extern const unsigned char Xthal_have_mac16;
extern const unsigned char Xthal_have_mul16;
extern const unsigned char Xthal_have_fp;
extern const unsigned char Xthal_have_speculation;
extern const unsigned char Xthal_have_threadptr;

extern const unsigned char Xthal_have_pif;
extern const unsigned short Xthal_num_writebuffer_entries;

extern const unsigned int  Xthal_build_unique_id;
/*  软件升级目标硬件的版本信息：*/
extern const unsigned int  Xthal_hw_configid0;
extern const unsigned int  Xthal_hw_configid1;
extern const unsigned int  Xthal_hw_release_major;
extern const unsigned int  Xthal_hw_release_minor;
extern const char * const  Xthal_hw_release_name;
extern const char * const  Xthal_hw_release_internal;

/*  清除任何剩余代码相关状态（即清除循环计数寄存器）。*/
extern void	xthal_clear_regcached_code( void );

#ifdef __cplusplus
}
#endif
#endif /*!_ASMLANGUAGE && !_NOCLANGUAGE && !__ASSEMBLER__ */





/****************************************************************************
    对PRIVILEGED（监管或非虚拟化）代码有用的定义
 ****************************************************************************/


#ifndef XTENSA_HAL_NON_PRIVILEGED_ONLY

/*----------------------------------------------------------------------
常量定义（与程序集共享）
  ----------------------------------------------------------------------*/

/*
 *  独立于配置的架构限制。请注意，这些是ISA定义的限制，而不是Xtensa处理器生成器强制执行的微架构实现限制（可能比下面的限制更严格）。
 */
#define XTHAL_MAX_INTERRUPTS	32	/* 最大中断数（0..31）*/
#define XTHAL_MAX_INTLEVELS	16	/* 最大中断级别数（0..15）*/
					/* （截至T1040，实施限制为7:0..6）*/
#define XTHAL_MAX_TIMERS	4	/* 最大计时器数（CCOMPARE0.COMPARE3）*/
					/* （截至T1040，实施限制为3:0..2）*/

/*  中断类型：*/
#define XTHAL_INTTYPE_UNCONFIGURED	0
#define XTHAL_INTTYPE_SOFTWARE		1
#define XTHAL_INTTYPE_EXTERN_EDGE	2
#define XTHAL_INTTYPE_EXTERN_LEVEL	3
#define XTHAL_INTTYPE_TIMER		4
#define XTHAL_INTTYPE_NMI		5
#define XTHAL_INTTYPE_WRITE_ERROR	6
#define XTHAL_INTTYPE_PROFILING		7
#define XTHAL_INTTYPE_IDMA_DONE		8
#define XTHAL_INTTYPE_IDMA_ERR		9
#define XTHAL_INTTYPE_GS_ERR		10
#define XTHAL_INTTYPE_SG_ERR		10	/* 向后兼容名称-已弃用*/
#define XTHAL_MAX_INTTYPES		11	/* 中断类型数*/

/*  计时器相关：*/
#define XTHAL_TIMER_UNCONFIGURED	-1	/* 不存在计时器的Xthal_timer_interrupt[]值*/
#define XTHAL_TIMER_UNASSIGNED	XTHAL_TIMER_UNCONFIGURED	/* （仅用于向后兼容）*/

/*  本地内存ECC/奇偶校验：*/
#define XTHAL_MEMEP_PARITY	1
#define XTHAL_MEMEP_ECC		2
/*  xthal_memep_inject_error（）的标志参数：*/
#define XTHAL_MEMEP_F_LOCAL		0	/* 本地内存（默认）*/
#define XTHAL_MEMEP_F_DCACHE_DATA	4	/* 数据缓存数据*/
#define XTHAL_MEMEP_F_DCACHE_TAG	5	/* 数据缓存标记*/
#define XTHAL_MEMEP_F_ICACHE_DATA	6	/* 指令缓存数据*/
#define XTHAL_MEMEP_F_ICACHE_TAG	7	/* 指令缓存标记*/
#define XTHAL_MEMEP_F_CORRECTABLE	16	/* 注入可纠正错误（默认为非纠正）*/


/*  访问模式位（暂定）：*/	/* bit abbr unit short_name PPC equ-描述*/
#define XTHAL_AMB_EXCEPTION	0	/* 001 E EX fls:EXception任何访问都没有异常（也称为“非法”）*/
#define XTHAL_AMB_HITCACHE	1	/* 002 C CH fls：在命中时使用缓存~（I CI）[或H HC]方式进行标记匹配；[或U UC]（ISA：除隔离情况外相同）*/
#define XTHAL_AMB_ALLOCATE	2	/* 004 A AL法兰：ALlocate none[or F FI fill]reply cache on miss，way from LRU（ISA：读/写未命中重新填充）*/
#define XTHAL_AMB_WRITETHRU	3	/* 008 W WT--s：WriteThrough W WT立即存储到内存（ISA：相同）*/
#define XTHAL_AMB_ISOLATE	4	/* 010 I IS fls：无论命中与未命中，都不使用缓存，与vaddr相去甚远（ISA：未命中+命中时使用缓存）*/
#define XTHAL_AMB_GUARD		5	/* 020克？我？：GUard G*非投机性；不允许规范/回放参考*/
#define XTHAL_AMB_COHERENT	6	/* 040 M立方米？ls：读取时Mem/MP相干M，其他CPU/总线主机可能需要提供数据；写入时，可能重定向到或刷新其他CPU脏线；等*/
#if 0
#define XTHAL_AMB_BUFFERABLE	x	/* 000 B BU--s：可提供？写入响应可能早于从最终目标返回*/
#define XTHAL_AMB_ORDERED	x	/* 000 O OR fls:ORrded G*mem访问不能无序*/
#define XTHAL_AMB_FUSEWRITES	x	/* 000 F FW--s：FuseWrites无允许将多个写入（到同一数据路径数据单元）组合/合并/合并为一个写入（由写回表示）*/
#define XTHAL_AMB_TRUSTED	x	/* 000吨吨？我？：TRusted none内存不会发生总线错误（如果发生，则作为致命的不精确中断处理）*/
#define XTHAL_AMB_PREFETCH	x	/* 000 P PR液体：P重新填充时无预取，将第+1行读取到预取缓冲区*/
#define XTHAL_AMB_STREAM	x	/* 000秒：S无需访问N个流缓冲区之一*/
#endif /*0*/

#define XTHAL_AM_EXCEPTION	(1<<XTHAL_AMB_EXCEPTION)
#define XTHAL_AM_HITCACHE	(1<<XTHAL_AMB_HITCACHE)
#define XTHAL_AM_ALLOCATE	(1<<XTHAL_AMB_ALLOCATE)
#define XTHAL_AM_WRITETHRU	(1<<XTHAL_AMB_WRITETHRU)
#define XTHAL_AM_ISOLATE	(1<<XTHAL_AMB_ISOLATE)
#define XTHAL_AM_GUARD		(1<<XTHAL_AMB_GUARD)
#define XTHAL_AM_COHERENT	(1<<XTHAL_AMB_COHERENT)
#if 0
#define XTHAL_AM_BUFFERABLE	(1<<XTHAL_AMB_BUFFERABLE)
#define XTHAL_AM_ORDERED	(1<<XTHAL_AMB_ORDERED)
#define XTHAL_AM_FUSEWRITES	(1<<XTHAL_AMB_FUSEWRITES)
#define XTHAL_AM_TRUSTED	(1<<XTHAL_AMB_TRUSTED)
#define XTHAL_AM_PREFETCH	(1<<XTHAL_AMB_PREFETCH)
#define XTHAL_AM_STREAM		(1<<XTHAL_AMB_STREAM)
#endif /*0*/

/*
 *  允许的访问模式（位组合）。
 *
 *  列为：“FOGIWACE”访问模式位（参见上文XTHAL_AMB_xxx）<letter>=位设置为'-'=位清除'。'=bit不相关/不重要，如下所示：E=1使所有其他不相关W，F仅与存储相关“2345”表示Xtensa版本支持相应的访问模式。每个字符列的版本为：2=T1020.2之前的版本：T1015（V1.5），T1020.0，T1020.1 3=T1020.2和更高版本：T1020.2+，T1030 4=T1040 5=T1050（可能），LX1，LX2，LX2.1 7=LX2.2 8=LX3，LX4 9=LX5字符列内容为：<number>=发行版支持“。”=发行版不支持“？”=支持未知
 */
						/* 传真：2345789*/
/*  对于指令获取：*/
#define XTHAL_FAM_EXCEPTION		0x001	/* E 2345789异常*/
/*定义XTHAL_FAM_ISOLATE*/	      /*0月12日*/	/* .----我-C-……隔离*/
#define XTHAL_FAM_BYPASS		0x000	/* .----.--- 2345789旁通*/
/*定义XTHAL_FAM_NCACHED*/	      /*0x002位*/	/* .----.-C-…….缓存无分配（冻结）*/
#define XTHAL_FAM_CACHED		0x006	/* .----.AC-2345789缓存*/
/*  对于数据加载：*/
#define XTHAL_LAM_EXCEPTION		0x001	/* E 2345789异常*/
#define XTHAL_LAM_ISOLATE		0x012	/* .----我-C-2345789隔离*/
#define XTHAL_LAM_BYPASS		0x000	/* .O---.--2……绕过推测*/
#define XTHAL_LAM_BYPASSG		0x020	/* .O-G-.---。345789旁路防护*/
#define XTHAL_LAM_CACHED_NOALLOC	0x002	/* .O----C-2345789缓存无分配推测*/
#define XTHAL_LAM_NACACHED		XTHAL_LAM_CACHED_NOALLOC
#define XTHAL_LAM_NACACHEDG		0x022	/* .O-G--C-。？。。。。。缓存无分配保护*/
#define XTHAL_LAM_CACHED		0x006	/* .----.AC-2345789缓存推测*/
#define XTHAL_LAM_COHCACHED		0x046	/* .-M--。AC-….*89缓存推测MP一致*/
/*  对于数据存储：*/
#define XTHAL_SAM_EXCEPTION		0x001	/* E 2345789异常*/
#define XTHAL_SAM_ISOLATE		0x032	/* .--GI-C-2345789隔离*/
#define XTHAL_SAM_BYPASS		0x028	/* -O-G-W-2345789旁路*/
#define XTHAL_SAM_WRITETHRU		0x02A	/* -O-G-W-C-2345789写入*/
/*定义XTHAL_SAM_WRITHERU_ALLOC*/   /*0x02E*/	/* -O-G-WAC-………….写入分配*/
#define XTHAL_SAM_WRITEBACK		0x026	/* F-G-AC-…5789回写*/
#define XTHAL_SAM_WRITEBACK_NOALLOC	0x022	/* ?--G---C-…..89写回无分配*/
#define XTHAL_SAM_COHWRITEBACK		0x066	/* F-MG—AC-…*89写回MP相干*/
/*  对于PIF属性：*/			/* -PIwrWCBUUUU…9*/
#define XTHAL_PAM_BYPASS		0x000	/* xxx00000xxxx…9旁路不可缓冲*/
#define XTHAL_PAM_BYPASS_BUF		0x010	/* xxx0000bxxxx…9旁通*/
#define XTHAL_PAM_CACHED_NOALLOC	0x030	/* xxx0001bxxxx…9缓存无分配*/
#define XTHAL_PAM_WRITETHRU		0x0B0	/* xxx0101bxxxx…9写入（WT）*/
#define XTHAL_PAM_WRITEBACK_NOALLOC	0x0F0	/* xxx0111bxxxx…9写回无分配（WBNA）*/
#define XTHAL_PAM_WRITEBACK		0x1F0	/* xxx1111bxxxx…9回写（WB）*/
/*定义XTHAL_PAM_NORMAL*/	      /*0x050*/	/* xxx0010bxxxx….（未实施）*/
/*定义XTHAL_PAM_WRITETHRU_WA*/      /*0x130像素*/	/* xxx1001bxxxx….（未实现，可能性较小）*/
/*定义XTHAL_PAM_WRITETHRU_RWA*/     /*0x1B0倍*/	/* xxx1101bxxxx….（未实现，可能性较小）*/
/*定义XTHAL_PAM_WRITEBACK_WA*/      /*0x170像素*/	/* xxx1011bxxxx….（未实现，可能性较小）*/


#if 0
/*
    CACHEATTR的缓存属性编码（根据ISA）：（注意：如果这与ISA参考手册不同，ISA优先）

Inst提取加载存储
---------------------------------------------------------0x0 FCA_EXCEPTION LCA_NACACHED SCA_WRIETHERU缓存未分配（以前被错误命名为“未缓存”）0x1 FCA_cached LCA_CACHEE SCA_WRITTHERU缓存0x2 FCA_BYPASS LCA_BYPASS_G SCA_BYPASS旁路缓存（大多数人称之为未缓存）0x3 FCA_CACCHED LCA_CAHED SCA_WRITEALLOCF写分配或LCA_EXCEPION SCA_EXCEPTION（如果未实现）SCA_WRITEBACK[M]写回[MP coherent]或LCA_EXCEPTION SCA_EXCEPTION（如果未实现）0x5 FCA_CACHED LCA_CACHED SCA_WRITEBACK_NOALLOC写回不分配或FCA_EXCEPION LCA_EXCEP SCA_EXCEP（如果未实施）0x6..D FCA_EXCEP LCA_EXCEPTION SCA_EXCETION（保留）0xE FCA_EXCETION LCA_ISOLATE SCA_ISOLATE隔离0xFT1020.2英寸？，不支持保护功能，这默认为推测（no_G）
*/
#endif /*0*/


#if !defined(_ASMLANGUAGE) && !defined(_NOCLANGUAGE) && !defined(__ASSEMBLER__)
#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------
   注册Windows
  ----------------------------------------------------------------------*/

/*  这会溢出任何实时注册窗口（调用方的除外）：（注意：当前实现需要特权代码，但用户可调用的实现是可能的。）*/
extern void      xthal_window_spill( void );


/*----------------------------------------------------------------------
可选/自定义处理器状态
  ----------------------------------------------------------------------*/

/* 验证TIE寄存器文件并使其无效*/
extern void xthal_validate_cp(int);
extern void xthal_invalidate_cp(int);

/* 读写cpenable寄存器*/
extern void xthal_set_cpenable(unsigned);
extern unsigned xthal_get_cpenable(void);


/*----------------------------------------------------------------------
   中断
  ----------------------------------------------------------------------*/

/* 中断级别的数量*/
extern const unsigned char Xthal_num_intlevels;
/* 中断次数*/
extern const unsigned char Xthal_num_interrupts;
/* PS.EXCM屏蔽的最高中断级别*/
extern const unsigned char Xthal_excm_level;

/* 中断级别掩码*/
extern const unsigned int Xthal_intlevel_mask[XTHAL_MAX_INTLEVELS];
/* 0到N级中断的掩码*/
extern const unsigned int Xthal_intlevel_andbelow_mask[XTHAL_MAX_INTLEVELS];

/* 每个中断的级别*/
extern const unsigned char Xthal_intlevel[XTHAL_MAX_INTERRUPTS];

/* 每个中断的类型*/
extern const unsigned char Xthal_inttype[XTHAL_MAX_INTERRUPTS];

/* 每种中断类型的掩码*/
extern const unsigned int Xthal_inttype_mask[XTHAL_MAX_INTTYPES];

/* 分配给每个定时器中断的中断编号*/
extern const int Xthal_timer_interrupt[XTHAL_MAX_TIMERS];

/*  INTABLE、INTERRUPT、INTSET、INTCLEAR寄存器访问功能：*/
extern unsigned  xthal_get_intenable( void );
extern void      xthal_set_intenable( unsigned );
extern unsigned  xthal_get_interrupt( void );
#define xthal_get_intread	xthal_get_interrupt	/* 向后兼容性*/

/*  这两个函数已弃用。请改用更新的函数xthal_interrupt_trigger和xthal_ininterrupt_clear。*/
extern void      xthal_set_intset( unsigned );
extern void      xthal_set_intclear( unsigned );


/*----------------------------------------------------------------------
   调试
  ----------------------------------------------------------------------*/

/*  指令和数据中断寄存器的数量：*/
extern const int Xthal_num_ibreak;
extern const int Xthal_num_dbreak;


/*----------------------------------------------------------------------
   核心计数器
  ----------------------------------------------------------------------*/

/* 计数器信息*/
extern const unsigned char Xthal_have_ccount;	/* 设置是否存在CCOUNT寄存器*/
extern const unsigned char Xthal_num_ccompare;	/* CCOMPAREn寄存器的数量*/

/* 获取CCOUNT寄存器（如果不存在，返回0）*/
extern unsigned xthal_get_ccount(void);

/* 设置并获取CCOMPAREn寄存器（如果不存在，则获取返回0）*/
extern void     xthal_set_ccompare(int, unsigned);
extern unsigned xthal_get_ccompare(int);


/*----------------------------------------------------------------------
                             混杂的
  ----------------------------------------------------------------------*/

extern const unsigned char Xthal_have_prid;
extern const unsigned char Xthal_have_exceptions;
extern const unsigned char Xthal_xea_version;
extern const unsigned char Xthal_have_interrupts;
extern const unsigned char Xthal_have_highlevel_interrupts;
extern const unsigned char Xthal_have_nmi;

extern unsigned xthal_get_prid( void );


/*----------------------------------------------------------------------
虚拟中断优先级（已弃用）
  ----------------------------------------------------------------------*/

/*  在中断级别（根据PS.INTLEVEL）和虚拟中断优先级之间转换：*/
extern unsigned	xthal_vpri_to_intlevel(unsigned vpri);
extern unsigned	xthal_intlevel_to_vpri(unsigned intlevel);

/*  启用/禁用给定的中断集（掩码）；返回所有int的先前启用掩码：*/
/*  这些函数已弃用。请改用xthal_interrupt_enable和xthal_ininterrupt_disable。*/
extern unsigned	xthal_int_enable(unsigned);
extern unsigned	xthal_int_disable(unsigned);

/*  设置/获取中断的虚拟优先级：*/
extern int	xthal_set_int_vpri(int intnum, int vpri);
extern int	xthal_get_int_vpri(int intnum);

/*  设置/获取对虚拟优先级数据结构的独占访问的中断锁定级别：*/
extern void	xthal_set_vpri_locklevel(unsigned intlevel);
extern unsigned	xthal_get_vpri_locklevel(void);

/*  设置/获取当前虚拟中断优先级：*/
extern unsigned	xthal_set_vpri(unsigned vpri);
extern unsigned	xthal_get_vpri(void);
extern unsigned	xthal_set_vpri_intlevel(unsigned intlevel);
extern unsigned	xthal_set_vpri_lock(void);


/*----------------------------------------------------------------------
通用中断转移支持（已弃用）
  ----------------------------------------------------------------------*/

typedef void (XtHalVoidFunc)(void);

/*  当前正在踩踏的中断位掩码：*/
extern unsigned Xthal_tram_pending;

/*
 *  实际启用了当前同步下行中断的位掩码；此位掩码是必需的，因为INTENABLE无法保持该状态（同步蹦床中断在蹦床时必须保持禁用状态）；在当前实现中，此处设置的任何位都未设置为INTABLE，反之亦然；一旦处理了同步蹦床（在一级），其启用位必须从这里移动到INTABLE：
 */
extern unsigned Xthal_tram_enabled;

/*  为同步蹦床配置的中断的位掩码：*/
extern unsigned Xthal_tram_sync;

/*  蹦床支撑功能：*/
extern unsigned  xthal_tram_pending_to_service( void );
extern void      xthal_tram_done( unsigned serviced_mask );
extern int       xthal_tram_set_sync( int intnum, int sync );
extern XtHalVoidFunc* xthal_set_tram_trigger_func( XtHalVoidFunc *trigger_fn );


/*----------------------------------------------------------------------
内部存储器
  ----------------------------------------------------------------------*/

extern const unsigned char Xthal_num_instrom;
extern const unsigned char Xthal_num_instram;
extern const unsigned char Xthal_num_datarom;
extern const unsigned char Xthal_num_dataram;
extern const unsigned char Xthal_num_xlmi;

/*  以下每个数组至少包含一个条目，如果有多个条目，则根据需要包含多个条目：*/
extern const unsigned int  Xthal_instrom_vaddr[];
extern const unsigned int  Xthal_instrom_paddr[];
extern const unsigned int  Xthal_instrom_size [];
extern const unsigned int  Xthal_instram_vaddr[];
extern const unsigned int  Xthal_instram_paddr[];
extern const unsigned int  Xthal_instram_size [];
extern const unsigned int  Xthal_datarom_vaddr[];
extern const unsigned int  Xthal_datarom_paddr[];
extern const unsigned int  Xthal_datarom_size [];
extern const unsigned int  Xthal_dataram_vaddr[];
extern const unsigned int  Xthal_dataram_paddr[];
extern const unsigned int  Xthal_dataram_size [];
extern const unsigned int  Xthal_xlmi_vaddr[];
extern const unsigned int  Xthal_xlmi_paddr[];
extern const unsigned int  Xthal_xlmi_size [];


/*----------------------------------------------------------------------
   隐藏物
  ----------------------------------------------------------------------*/

/* log2中的缓存集数（每路行数）*/
extern const unsigned char Xthal_icache_setwidth;
extern const unsigned char Xthal_dcache_setwidth;
/* 缓存集关联性（路径数）*/
extern const unsigned int  Xthal_icache_ways;
extern const unsigned int  Xthal_dcache_ways;
/* 缓存功能*/
extern const unsigned char Xthal_icache_line_lockable;
extern const unsigned char Xthal_dcache_line_lockable;

/* 缓存属性寄存器控制（由其他HAL例程使用）*/
extern unsigned xthal_get_cacheattr( void );
extern unsigned xthal_get_icacheattr( void );
extern unsigned xthal_get_dcacheattr( void );
extern void     xthal_set_cacheattr( unsigned );
extern void     xthal_set_icacheattr( unsigned );
extern void     xthal_set_dcacheattr( unsigned );
/* 设置内存范围的缓存属性（访问模式）*/
extern int      xthal_set_region_attribute( void *addr, unsigned size,
					    unsigned cattr, unsigned flags );
/*  xthal_set_region_attribute（）的标志位参数：*/
#define XTHAL_CAFLAG_EXPAND		0x000100	/* 只扩大允许的范围，不要缩小*/
#define XTHAL_CAFLAG_EXACT		0x000200	/* 如果无法将更改应用于指定的精确范围，则返回错误*/
#define XTHAL_CAFLAG_NO_PARTIAL		0x000400	/* 不将更改应用于范围部分覆盖的区域*/
#define XTHAL_CAFLAG_NO_AUTO_WB		0x000800	/* 离开writeback属性后不写回数据*/
#define XTHAL_CAFLAG_NO_AUTO_INV	0x001000	/* 禁用缓存后不失效（进入旁路）*/

/* 启用缓存*/
extern void xthal_icache_enable( void );	/* DEPRECATED */
extern void xthal_dcache_enable( void );	/* DEPRECATED */
/* 禁用缓存*/
extern void xthal_icache_disable( void );	/* DEPRECATED */
extern void xthal_dcache_disable( void );	/* DEPRECATED */

/* 整个缓存操作（特权）*/
extern void xthal_icache_all_invalidate( void );
extern void xthal_dcache_all_invalidate( void );
extern void xthal_dcache_all_writeback( void );
extern void xthal_dcache_all_writeback_inv( void );
extern void xthal_icache_all_unlock( void );
extern void xthal_dcache_all_unlock( void );

/* 地址范围缓存操作（特权）*/
/* 将指定的内存范围预取并锁定到缓存中*/
extern void xthal_icache_region_lock( void *addr, unsigned size );
extern void xthal_dcache_region_lock( void *addr, unsigned size );
/* 从缓存解锁*/
extern void xthal_icache_region_unlock( void *addr, unsigned size );
extern void xthal_dcache_region_unlock( void *addr, unsigned size );

/* 大范围缓存操作（特权）（实验）*/
extern void xthal_icache_hugerange_invalidate( void *addr, unsigned size );
extern void xthal_icache_hugerange_unlock( void *addr, unsigned size );
extern void xthal_dcache_hugerange_invalidate( void *addr, unsigned size );
extern void xthal_dcache_hugerange_unlock( void *addr, unsigned size );
extern void xthal_dcache_hugerange_writeback( void *addr, unsigned size );
extern void xthal_dcache_hugerange_writeback_inv( void *addr, unsigned size );

# ifndef XTHAL_USE_CACHE_MACROS
/* 缓存行操作（特权）*/
extern void xthal_icache_line_lock(void *addr);
extern void xthal_dcache_line_lock(void *addr);
extern void xthal_icache_line_unlock(void *addr);
extern void xthal_dcache_line_unlock(void *addr);
# endif



/*----------------------------------------------------------------------
                         本地内存ECC/奇偶校验
  ----------------------------------------------------------------------*/

/*  注入内存错误；标志是XTHAL_MEMEPF_xxx的位组合：*/
extern void xthal_memep_inject_error(void *addr, int size, int flags);



/*----------------------------------------------------------------------
                         内存管理单元
  ----------------------------------------------------------------------*/

extern const unsigned char Xthal_have_spanning_way;
extern const unsigned char Xthal_have_identity_map;
extern const unsigned char Xthal_have_mimic_cacheattr;
extern const unsigned char Xthal_have_xlt_cacheattr;
extern const unsigned char Xthal_have_cacheattr;
extern const unsigned char Xthal_have_tlbs;

extern const unsigned char Xthal_mmu_asid_bits;		/* 0 .. 8 */
extern const unsigned char Xthal_mmu_asid_kernel;
extern const unsigned char Xthal_mmu_rings;		/* 1..4（如果没有MMU和/或没有保护，则可能为0？）*/
extern const unsigned char Xthal_mmu_ring_bits;
extern const unsigned char Xthal_mmu_sr_bits;
extern const unsigned char Xthal_mmu_ca_bits;
extern const unsigned int  Xthal_mmu_max_pte_page_size;
extern const unsigned int  Xthal_mmu_min_pte_page_size;

extern const unsigned char Xthal_itlb_way_bits;
extern const unsigned char Xthal_itlb_ways;
extern const unsigned char Xthal_itlb_arf_ways;
extern const unsigned char Xthal_dtlb_way_bits;
extern const unsigned char Xthal_dtlb_ways;
extern const unsigned char Xthal_dtlb_arf_ways;

/* 返回hal函数的错误代码*/

/* 函数成功，操作按预期完成*/
#define XTHAL_SUCCESS                                    0
/* 指定了XTHAL_CAFLAGS_NO_PARTIAL，地址范围未覆盖任何完整区域。*/
#define XTHAL_NO_REGIONS_COVERED                        -1
/* 给出了XTHAL_CAFLAGS_EXACT标志，但无法进行精确映射。*/
#define XTHAL_INEXACT                                   -2
/* 提供的地址与区域的开头不对应。*/
#define XTHAL_INVALID_ADDRESS                           -3
/* 此功能在此体系结构上不可用。*/
#define XTHAL_UNSUPPORTED                               -4
/* 由于vaddr和paddr未对齐，转换失败。*/
#define XTHAL_ADDRESS_MISALIGNED                        -5
/* 提供的地址存在映射。*/
#define XTHAL_NO_MAPPING                                -6
/* 不支持请求的访问权限*/
#define XTHAL_BAD_ACCESS_RIGHTS                         -7
/* 不支持请求的内存类型*/
#define XTHAL_BAD_MEMORY_TYPE                           -8
/* 提供的条目未正确对齐MPU的背景图。*/
#define XTHAL_MAP_NOT_ALIGNED                           -9
/* 没有足够的MPU条目可用于执行请求映射。*/
#define XTHAL_OUT_OF_ENTRIES                           -10
/* 为MPU提供的条目顺序不正确。*/
#define XTHAL_OUT_OF_ORDER_MAP                         -11
/* 向函数提供了无效参数（如空指针）*/
#define XTHAL_INVALID                                  -12
/* 指定区域的大小为零，因此不进行映射。*/
#define XTHAL_ZERO_SIZED_REGION                        -13
/* 指定的范围环绕“0”*/
#define XTHAL_INVALID_ADDRESS_RANGE                    -14

/*
   为了向后兼容，我们保留以下命名不一致的常量。不要使用它们，因为它们可能会在将来的版本中删除。
 */
#define XCHAL_SUCCESS XTHAL_SUCCESS
#define XCHAL_ADDRESS_MISALIGNED XTHAL_ADDRESS_MISALIGNED
#define XCHAL_INEXACT XTHAL_INEXACT
#define XCHAL_INVALID_ADDRESS XTHAL_INVALID_ADDRESS
#define XCHAL_UNSUPPORTED_ON_THIS_ARCH XTHAL_UNSUPPORTED
#define XCHAL_NO_PAGES_MAPPED XTHAL_NO_REGIONS_COVERED


/*  在虚拟地址和物理地址之间转换（仅通过静态映射）警告：这两个功能可能会在将来的版本中消失；不要依赖他们！
*/
extern int  xthal_static_v2p( unsigned vaddr, unsigned *paddrp );
extern int  xthal_static_p2v( unsigned paddr, unsigned *vaddrp, unsigned cached );

extern int xthal_set_region_translation(void* vaddr, void* paddr,
                  unsigned size, unsigned cache_atr, unsigned flags);
extern int xthal_v2p(void*, void**, unsigned*, unsigned*);
extern int xthal_invalidate_region(void* addr);
extern int xthal_set_region_translation_raw(void *vaddr, void *paddr, unsigned cattr);

/*------------------------------------------------------------------------
MPU（内存保护单元）
-------------------------------------------------------------------------*/

/*
 *  MPU（内存保护单元）的一般说明：
 *
 *  MPU支持设置内存区域的访问权限（读、写、执行）以及内存类型（可缓存性…）。粒度可以小到32字节。（XCHAL_MPU_ALIGN指定任何特定MPU配置的粒度）
 *
 *  MPU不支持虚拟地址和物理地址之间的映射。
 *
 *  MPU包含固定数量的可更改地图条目，以及在配置时固定的背景地图。
 *
 *  每个条目都有一个起始地址（最多27位）、有效标志、访问权限（4位）和内存类型（9位）；
 *
 */


/*
    MPU访问权限常量：MPU仅支持下面列出的组合。
*/

#define XTHAL_AR_NONE    0 /* 无访问权限*/
#define XTHAL_AR_R       4 /* 内核已读取，用户无法访问*/
#define XTHAL_AR_RX      5 /* 内核读取/执行，用户无权访问*/
#define XTHAL_AR_RW      6 /* 内核读/写，用户无权访问*/
#define XTHAL_AR_RWX     7 /* 内核读/写/执行，用户无权访问*/
#define XTHAL_AR_Ww      8 /* 内核写入，用户写入*/
#define XTHAL_AR_RWrwx   9 /* 内核读/写，用户读/写/执行*/
#define XTHAL_AR_RWr    10 /* 内核读/写，用户读*/
#define XTHAL_AR_RWXrx  11 /* 内核读/写/执行，用户读/执行*/
#define XTHAL_AR_Rr     12 /* 内核读取，用户读取*/
#define XTHAL_AR_RXrx   13 /* 内核读取/执行，用户读取/执行*/
#define XTHAL_AR_RWrw   14 /* 内核读/写，用户读/写*/
#define XTHAL_AR_RWXrwx 15 /* 内核读/写/执行，用户读/写或执行*/

#define XTHAL_AR_WIDTH  4  /* #用于编码访问权限的位*/

/* 如果位XTHAL_MPU_USE_EXISTING_ACCESS_RIGHTS设置在XTHAL_MPU_set_region_attribute（）的accessRights参数或XTHAL_set_regia_attributes（）的catter参数中，则区域的第一个字节的现有访问权限将用作新区域的访问权限。
 */
#define XTHAL_MPU_USE_EXISTING_ACCESS_RIGHTS     0x00002000

/* 如果在memoryType参数中将位XTHAL_MPU_USE_EXISTING_MEMORY_TYPE设置为XTHAL_MPU_set_region_attribute（）或XTHAL_set_region_attribute的catter参数，则区域的第一个字节的现有内存类型将用作新区域的内存类型。
 */
#define XTHAL_MPU_USE_EXISTING_MEMORY_TYPE       0x00004000

/* 以下常量组按位或组合在一起，以将内存类型指定为接受未编码内存类型说明符的宏和函数的输入：XTHAL_ENCODE_memory_type、XTHAL_ENCODE_memory_type、XTHAL_mpu_set_region_attribute（）和XTHAL_set_regia_attributes（）。
 *
 * 示例：XTHAL_MEM_DEVICE | XTHAL_MEM _INTERRUPTIBLE | XTHAL-MEM_SYSTEM_SHARABLE
 *
 * 或XTHAL_MEM_WRITEBACK | XTHAL_MEM _INNER_SHAREABLE
 *
 * 如果需要为系统和本地缓存指定不同的属性，则使用宏XTHAL_MEM_PROC_cache：
 *
 * XTHAL_MEM_PROC_CACHE(XTHAL_MEM_WRITEBACK, XTHAL_MEM_WRITETHRU)
 *
 * 表示共享缓存是写回的，但处理器的本地缓存是写通的。
 *
 */

/* 以下一组常量用于指定MPU条目的缓存属性。如果处理器的本地缓存和系统的共享缓存具有相同的属性（或者如果没有不同的本地和共享缓存），则可以直接使用常量。如果共享缓存和本地缓存的属性不同，则使用这些常量作为XTHAL_MEM_PROC_CACHE（）宏的参数。
 */
#define XTHAL_MEM_DEVICE                         0x00008000
#define XTHAL_MEM_NON_CACHEABLE                  0x00090000
#define XTHAL_MEM_WRITETHRU_NOALLOC              0x00080000
#define XTHAL_MEM_WRITETHRU                      0x00040000
#define XTHAL_MEM_WRITETHRU_WRITEALLOC           0x00060000
#define XTHAL_MEM_WRITEBACK_NOALLOC              0x00050000
#define XTHAL_MEM_WRITEBACK                      0x00070000

/* 指示读取可中断。仅适用于设备*/
#define XTHAL_MEM_INTERRUPTIBLE                  0x08000000

/* 指示对该内存的写入是否可缓冲…仅适用于设备和不可缓存内存。
 */
#define XTHAL_MEM_BUFFERABLE                     0x01000000

/* 以下一组常数表示内存区域的共享范围。XTHAL_MEM_INNER_SHARABLE和XTHAL_MEM _OUTER_SHARABLE仅适用于可缓存区域。XTHAL_MEM_SYSTEM_SHAREABLE仅适用于设备和不可缓存区域。
 */
#define XTHAL_MEM_NON_SHAREABLE                  0x00000000
#define XTHAL_MEM_INNER_SHAREABLE                0x02000000
#define XTHAL_MEM_OUTER_SHAREABLE                0x04000000
#define XTHAL_MEM_SYSTEM_SHAREABLE               0x06000000


/*
 * 当共享缓存和处理器的本地缓存的缓存属性不同时，需要此宏。例如：
 *
 * XTHAL_MEM_PROC_CACHE（XTHAL_MEM_WRITEBACK，XTHAL_MEM _NON_CACHEABLE）创建的内存类型可在系统缓存中写回缓存，而不可在处理器的本地缓存中缓存。
 */
#define XTHAL_MEM_PROC_CACHE(system, processor) \
    (((system) & 0x000f0000) | (((processor) & 0x000f0000 ) << 4) | \
    (((system) & XTHAL_MEM_DEVICE) | ((processor) & XTHAL_MEM_DEVICE)))

/*
 * 此宏将XTHAL_MEM_…常量的位组合转换为相应的MPU内存类型（9位）。
 *
 * 不支持的组合将映射到最佳可用替代项。
 *
 * xthal_encode_memory_type（）提供了相同的功能和错误检查。
 */
#define XTHAL_ENCODE_MEMORY_TYPE(x) \
    (((x) & 0xffffe000) ? \
    (_XTHAL_MEM_IS_DEVICE((x)) ?  _XTHAL_ENCODE_DEVICE((x)) : \
      (_XTHAL_IS_SYSTEM_NONCACHEABLE((x)) ? \
        _XTHAL_ENCODE_SYSTEM_NONCACHEABLE((x)) : \
        _XTHAL_ENCODE_SYSTEM_CACHEABLE((x)))) : (x))

/*
 * 此结构用于表示每个MPU条目（前台和后台）。结构的内部表示可能会更改，因此只能通过下面的XTHAL_MPU_ENTRY_…宏访问。
 */
typedef struct xthal_MPU_entry
{
	uint32_t as;	/* 虚拟起始地址和有效位*/
	uint32_t at;	/* 访问权限和内存类型（以及条目索引的空间）*/
} xthal_MPU_entry;

extern const xthal_MPU_entry Xthal_mpu_bgmap[];




/*
 * XTHAL_MPU_ENTRY从其组件值创建MPU条目。它用于初始化MPU映射。示例：const struct xthal_MPU_entry mpumap[]=｛xthal_MPU_entry（0x00000000，1，xthal_AR_RWXrwx，xthal_MEM_WRITEBACK）、xthal_MPU _entry；xthal_write_map（mpumap，sizeof（mpuma）/sizeof（结构xthal_MPU_entry））；
 *
 */
#define XTHAL_MPU_ENTRY(vaddr, valid, access, memtype) \
    { (((vaddr) & 0xffffffe0) | ((valid & 0x1))), \
    (((XTHAL_ENCODE_MEMORY_TYPE(memtype)) << 12) | (((access) & 0xf) << 8)) }

/*
 * 这些宏获取（或设置）MPU条目的指定字段。
 */
#define XTHAL_MPU_ENTRY_GET_VSTARTADDR(x) ((x).as & 0xffffffe0)

#define XTHAL_MPU_ENTRY_SET_VSTARTADDR(x, vaddr) (x).as = \
    (((x).as) & 0x1) | ((vaddr) & 0xffffffe0)

#define XTHAL_MPU_ENTRY_GET_VALID(x) (((x).as & 0x1))

#define XTHAL_MPU_ENTRY_SET_VALID(x, valid) (x).as = \
    (((x).as & 0xfffffffe) | ((valid) & 0x1))
#define XTHAL_MPU_ENTRY_GET_ACCESS(x) ((((x).at) >> 8) & 0xf)

#define XTHAL_MPU_ENTRY_SET_ACCESS(x, accessRights) ((x).at = \
        ((x).at & 0xfffff0ff) | (((accessRights) & 0xf) << 8))

#define XTHAL_MPU_ENTRY_GET_MEMORY_TYPE(x) ((((x).at) >> 12) & 0x1ff)

#define XTHAL_MPU_ENTRY_SET_MEMORY_TYPE(x, memtype) ((x).at = \
        ((x).at & 0xffe00fff) | (((XTHAL_ENCODE_MEMORY_TYPE(memtype)) & 0x1ff) << 12))

/*
 * 这些函数接受编码的访问权限，如果提供的内存类型具有由函数名指定的属性，则返回1，否则返回0。
 */
extern int32_t xthal_is_kernel_readable(uint32_t accessRights);
extern int32_t xthal_is_kernel_writeable(uint32_t accessRights);
extern int32_t xthal_is_kernel_executable(uint32_t accessRights);
extern int32_t xthal_is_user_readable(uint32_t accessRights);
extern int32_t xthal_is_user_writeable (uint32_t accessRights);
extern int32_t xthal_is_user_executable(uint32_t accessRights);


/*
 * 此函数将XTHAL_MEM_..常量的位组合转换为相应的MPU内存类型（9位）。
 *
 * 如果参数中不存在XTHAL_MEM_..位，则返回位4-12（9位）……这支持使用已编码的memoryType（可能从XTHAL_MPU_entry结构获得）作为XTHAL_set_region_attribute（）的输入。
 *
 * 此函数首先检查提供的常量是否为有效且受支持的组合。如果不是，则返回XTHAL_BAD_MEMORY_TYPE。
 */
extern int xthal_encode_memory_type(uint32_t x);

/*
 * 此函数接受9位内存类型值（例如由XTHAL_MEM_ENTRY_GET_memory_type（）或XTHAL_encode_memory_type（）返回）。如果memoryType具有在函数名中指定的属性，则返回1，否则返回0。
 */
extern int32_t xthal_is_cacheable(uint32_t memoryType);
extern int32_t xthal_is_writeback(uint32_t memoryType);
extern int32_t xthal_is_device(uint32_t  memoryType);

/*
 * 将当前MPU条目列表复制到“条目”中，该条目必须指向大小至少为（结构xthal_MPU_entry）XCHAL_MPU_entries的可用内存。
 *
 * 此函数返回XTHAL_SUCCESS。XTHAL_INVALID或XTHAL_UNSUPPORTED。
 */
extern int32_t xthal_read_map(struct xthal_MPU_entry* entries);

/*
 * 将“entries”指向的映射写入MPU。在更新映射之前，它将提交任何未提交的缓存写入，并在必要时使缓存无效。
 *
 * 此函数不会检查地图的正确性。通常，应该首先调用xthal_check_map（）来检查映射。
 *
 * 如果n==0，则清除现有映射，并且不写入新映射（有助于返回到重置状态）
 *
 * 如果（n>0&&n<XCHAL_MPU_ENTRIES），则将使用添加的（XCHAL_MPU _ENTRIES-n）填充条目来写入新映射，以确保正确排序的映射。生成的前景地图将等同于地图向量fg，但不应依赖填充项的位置。
 *
 * 如果n==XCHAL_MPU_ENTRIES，则写入fg指定的完整映射。
 *
 * CACHEARDIS寄存器将被设置为允许缓存与具有可缓存内存类型的MPU区域重叠的任何512MB区域。如果512 MB区域都不可缓存，则将禁用缓存。
 *
 * xthal_write_map（）在MPU更新期间禁用MPU前景贴图，并依赖于背景贴图。
 *
 * 因此，在调用xthal_write_map（）之前，必须禁用任何不满足以下条件的中断：1）中断所需的所有代码和数据必须由具有足够访问权限的后台映射映射。2） 中断代码不得访问MPU。
 *
 */
extern void xthal_write_map(const struct xthal_MPU_entry* entries, uint32_t n);

/*
 * 检查长度为“n”的条目向量“entries”是否为有效的MPU访问映射。返回：XTHAL_SUCCESS（如果有效）、XTHAL_OUT_OF_ENTRIES XTHAL_MAP_NOT_ALIGNED、XTHAL_BAD_ACCESS_RIGHTS、XTHAL-OUT_OF_ORDER_MAP或XTHAL_UNSUPPORTED（如果配置没有MPU）。
 */
extern int xthal_check_map(const struct xthal_MPU_entry* entries, uint32_t n);

/*
 * 返回映射“vaddr”的MPU条目。如果“infgmap”为非NULL，则如果前景映射映射了“vaddr”，则infgmap将设置为1；如果背景映射映射了”vaddr“，则将infgmap设置为0。
 */
extern struct xthal_MPU_entry xthal_get_entry_for_address(void* vaddr,
	int32_t* infgmap);

/*
 * 扫描提供的MPU映射，并返回一个适合写入CACHEARDIS寄存器的值：如果对应的512MB区域中没有可缓存区域，则位0-7->1，否则为0。位8-31->未定义。此函数可以以与xthal_write_map（）相同的方式接受部分内存映射，*/
extern uint32_t
xthal_calc_cacheadrdis(const struct xthal_MPU_entry* e, uint32_t n);

/*
 * 此函数用于特定于MPU的xthal_set_region_attributes（）版本。xthal_set_region_attributes（）为MPU配置调用此函数。
 *
 * 此函数设置MPU中区域[vaddr，vaddr+size）的属性。
 *
 * 根据MPU的状态，此功能需要0到3个未使用的MPU条目。
 *
 * 此函数通常会在执行期间从MPU映射中移动、添加和减去条目，因此生成的映射可能与调用该函数时的映射截然不同。
 *
 * 该功能确实提供了以下保证：1）MPU访问映射在执行过程中始终保持有效状态。2） 在完成期间（和之后）的所有时间点，对于不在范围[vaddr，vaddr+size）内的所有地址，memoryType和accessRights保持相同。3）如果返回XTHAL_SUCCESS，则范围[vaddr，vaddr+size）将指定accessRights和memoryType。4）CACHEARDIS寄存器将设置为允许缓存与具有可缓存内存类型的MPU区域重叠的任何512MB区域。如果512 MB区域都不可缓存，则将禁用缓存。
 *
 * accessRights参数应为对应于MPU访问模式的4位值（由XTHAL_AR_..常量定义）或XTHAL_MPU_USE_EXISTING_access_RIGHTS。
 *
 * memoryType参数应为位或XTHAL_MEM_..常量的ing，这些常量表示有效的MPU memoryType、9位MPU memoryType值或XTHAL-MPU_USE_EXISTING_MEMORY_TYPE。
 *
 * 除了xthal_set_region_attribute（）返回的错误代码外，此函数还可以返回：xthal_BAD_ACCESS_RIGHTS（如果访问权限位映射到不支持的组合）或xthal_OUT_OF_map_ENTRIES（如果没有足够的未使用MPU条目）
 *
 * 如果使用无效的MPU映射调用此函数，则此函数将返回xthal_check_map（）返回的代码之一。
 *
 * 不支持标志XTHAL_CAFLAG_EXPAND
 *
 */

extern int xthal_mpu_set_region_attribute(void* vaddr, size_t size,
	int32_t accessRights, int32_t memoryType, uint32_t flags);

/* 以下是内部实现宏。除hal代码和标头外，这些不应直接使用。
*/

/*
 * MPU说明符的布局：XTHAL_ENCODE_MEMORY_TYPE（）、XTHAL_ENCODE_MEMORY_TYPE（）、XTHAL_set_region_attribute（）和XTHAL_MPU_set_regia_attribute（）。这可能会发生变化：
 *
 * 位0-3-保留用于访问权限的传递位4-12-保留用于内存类型位13-指示使用区域的现有访问权限位14-指示使用现有的区域内存类型位15-指示设备位16-19-系统缓存属性位20-23-本地缓存属性位24-指示可缓冲位25-26-编码可共享性（1=内部，2=外部，3=系统）第27位-表示可中断的第28-31位-保留供将来使用
 */
#define _XTHAL_SYSTEM_CACHE_BITS 0x000f0000
#define _XTHAL_LOCAL_CACHE_BITS 0x00f00000
#define _XTHAL_MEM_SYSTEM_RWC_MASK 0x00070000
#define _XTHAL_MEM_LOCAL_RWC_MASK  0x00700000
#define _XTHAL_SHIFT_RWC 16

#define _XTHAL_MEM_ANY_SHAREABLE(x) (((x) & XTHAL_MEM_SYSTEM_SHAREABLE) ? 1 : 0)

#define _XTHAL_MEM_INNER_SHAREABLE(x) ((((x) & XTHAL_MEM_SYSTEM_SHAREABLE) \
        == XTHAL_MEM_INNER_SHAREABLE) ? 1 : 0)

#define _XTHAL_MEM_IS_BUFFERABLE(x) (((x) & XTHAL_MEM_BUFFERABLE) ? 1 : 0)

#define _XTHAL_MEM_IS_DEVICE(x) (((x) & XTHAL_MEM_DEVICE) ? 1 : 0)

#define _XTHAL_NON_CACHEABLE_DOMAIN(x) \
    (_XTHAL_MEM_IS_DEVICE(x) || _XTHAL_MEM_ANY_SHAREABLE(x)? 0x3 : 0)

#define _XTHAL_CACHEABLE_DOMAIN(x)  (_XTHAL_MEM_ANY_SHAREABLE(x) ? \
        0x3 : 0x1)

#define _XTHAL_MEM_CACHE_MASK(x) ((x) & _XTHAL_SYSTEM_CACHE_BITS)

#define _XTHAL_IS_SYSTEM_NONCACHEABLE(x) \
        (((_XTHAL_MEM_CACHE_MASK(x) & XTHAL_MEM_NON_CACHEABLE) == \
                XTHAL_MEM_NON_CACHEABLE) ? 1 : 0)

#define _XTHAL_ENCODE_DEVICE(x) \
         (((((x) & XTHAL_MEM_INTERRUPTIBLE) ? 1 : 0) << 3) | \
         (_XTHAL_NON_CACHEABLE_DOMAIN(x) << 1) | _XTHAL_MEM_IS_BUFFERABLE(x))

#define _XTHAL_ENCODE_SYSTEM_NONCACHEABLE(x) \
        (0x18 | (_XTHAL_NON_CACHEABLE_DOMAIN(x) << 1) \
                | _XTHAL_MEM_IS_BUFFERABLE(x))

#define _XTHAL_ENCODE_SYSTEM_CACHEABLE(x) \
        (((((((x) & _XTHAL_LOCAL_CACHE_BITS) >> 4) & XTHAL_MEM_NON_CACHEABLE) == \
                XTHAL_MEM_NON_CACHEABLE) ? 1 : 0) ? \
         (_XTHAL_CACHEABLE_DOMAIN(x) << 4) : \
         _XTHAL_ENCODE_SYSTEM_CACHEABLE_LOCAL_CACHEABLE(x)) | \
         ((_XTHAL_MEM_INNER_SHAREABLE(x) << 3) | \
                  (_XTHAL_MEM_CACHE_MASK(x) & _XTHAL_MEM_SYSTEM_RWC_MASK) \
                  >> _XTHAL_SHIFT_RWC)

#define _XTHAL_ENCODE_SYSTEM_CACHEABLE_LOCAL_CACHEABLE(x) \
        ((_XTHAL_CACHEABLE_DOMAIN(x) << 7) | (((((x) & _XTHAL_LOCAL_CACHE_BITS) ? \
                ((x) & _XTHAL_LOCAL_CACHE_BITS) : \
                (_XTHAL_MEM_CACHE_MASK(x) << 4)) \
        & (_XTHAL_MEM_LOCAL_RWC_MASK)) >> _XTHAL_SHIFT_RWC ))

/* 内部宏结束*/

/* 下面的函数和常量已被弃用。*/
#define XTHAL_MEM_NON_CACHED                     XTHAL_MEM_NON_CACHEABLE
#define XTHAL_MEM_NON_SHARED                     XTHAL_MEM_NON_SHAREABLE
#define XTHAL_MEM_INNER_SHARED                   XTHAL_MEM_INNER_SHAREABLE
#define XTHAL_MEM_OUTER_SHARED                   XTHAL_MEM_OUTER_SHAREABLE
#define XTHAL_MEM_SYSTEM_SHARED                  XTHAL_MEM_SYSTEM_SHAREABLE
#define XTHAL_MEM_SW_SHAREABLE 0

#define xthal_is_cached(memoryType) (xthal_is_cacheable((memoryType)))
extern int32_t xthal_read_background_map(struct xthal_MPU_entry* entries);

/* 结束弃用的函数和常量*/

#ifdef __cplusplus
}
#endif
#endif /*!_ASMLANGUAGE && !_NOCLANGUAGE && !__ASSEMBLER__ */

#endif /* !XTENSA_HAL_NON_PRIVILEGED_ONLY */




/****************************************************************************
实验和弃用定义
 ****************************************************************************/


#if !defined(_ASMLANGUAGE) && !defined(_NOCLANGUAGE) && !defined(__ASSEMBLER__)
#ifdef __cplusplus
extern "C" {
#endif

#ifdef INCLUDE_DEPRECATED_HAL_DEBUG_CODE
#define XTHAL_24_BIT_BREAK		0x80000000
#define XTHAL_16_BIT_BREAK		0x40000000
extern const unsigned short	Xthal_ill_inst_16[16];
#define XTHAL_DEST_REG		0xf0000000	/* 目标寄存器掩码*/
#define XTHAL_DEST_REG_INST	0x08000000	/* 分支机构地址在寄存器中*/
#define XTHAL_DEST_REL_INST	0x04000000	/* 分支地址是相对的*/
#define XTHAL_RFW_INST		0x00000800
#define XTHAL_RFUE_INST		0x00000400
#define XTHAL_RFI_INST		0x00000200
#define XTHAL_RFE_INST		0x00000100
#define XTHAL_RET_INST		0x00000080
#define XTHAL_BREAK_INST	0x00000040
#define XTHAL_SYSCALL_INST	0x00000020
#define XTHAL_LOOP_END		0x00000010	/* 不由xthal_inst_type设置*/
#define XTHAL_JUMP_INST		0x00000008	/* 呼叫或跳转指令*/
#define XTHAL_BRANCH_INST	0x00000004	/* 分支机构指令*/
#define XTHAL_24_BIT_INST	0x00000002
#define XTHAL_16_BIT_INST   0x00000001
typedef struct xthal_state {
    unsigned	pc;
    unsigned	ar[16];
    unsigned	lbeg;
    unsigned	lend;
    unsigned	lcount;
    unsigned	extra_ptr;
    unsigned	cpregs_ptr[XTHAL_MAX_CPS];
} XTHAL_STATE;
extern unsigned int xthal_inst_type(void *addr);
extern unsigned int xthal_branch_addr(void *addr);
extern unsigned int xthal_get_npc(XTHAL_STATE *user_state);
#endif /* INCLUDE_DEPRECATED_HAL_DEBUG_CODE */

#ifdef __cplusplus
}
#endif
#endif /*!_ASMLANGUAGE && !_NOCLANGUAGE && !__ASSEMBLER__ */

#endif /*XTENSA_HAL_H*/

