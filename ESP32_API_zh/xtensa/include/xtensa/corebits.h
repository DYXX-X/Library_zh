/*
 * xtensa/corebits.h-xtensa特殊寄存器字段位置、掩码和值。
 *
 * （在以前的版本中，这些都是在specreg.h中定义的，这是一个生成的文件。这个文件不是生成的，也就是说，它是独立于处理器配置的。）
 */

/* $Id://depot/rel/Foxhill.dot.9/Xtensa/OS/include/Xtensa/corebits.h#1$*/

/*
 * 版权所有（c）2005-2011 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTENSA_COREBITS_H
#define XTENSA_COREBITS_H

/*  EXCCAUSE寄存器字段：*/
#define EXCCAUSE_EXCCAUSE_SHIFT	0
#define EXCCAUSE_EXCCAUSE_MASK	0x3F
/*  EXCCAUSE寄存器值：*/
/*
 *  常规异常原因（由常规异常设置的EXCCAUSE特殊寄存器的值，该值指向用户、内核或双异常向量）。
 */
#define EXCCAUSE_ILLEGAL		0	/* 非法指令*/
#define EXCCAUSE_SYSCALL		1	/* 系统调用（SYSCALL指令）*/
#define EXCCAUSE_INSTR_ERROR		2	/* 指令获取错误*/
# define EXCCAUSE_IFETCHERROR		2	/* （向后兼容宏，已弃用，请避免）*/
#define EXCCAUSE_LOAD_STORE_ERROR	3	/* 加载存储错误*/
# define EXCCAUSE_LOADSTOREERROR	3	/* （向后兼容宏，已弃用，请避免）*/
#define EXCCAUSE_LEVEL1_INTERRUPT	4	/* 1级中断*/
# define EXCCAUSE_LEVEL1INTERRUPT	4	/* （向后兼容宏，已弃用，请避免）*/
#define EXCCAUSE_ALLOCA			5	/* 用于分配的堆栈扩展辅助（MOVSP指令）*/
#define EXCCAUSE_DIVIDE_BY_ZERO		6	/* 整数除以零*/
# define EXCCAUSE_SPECULATION		7	/* 使用失败的推测访问（已弃用）*/
#define EXCCAUSE_PC_ERROR		7	/* 下一个PC值非法*/
#define EXCCAUSE_PRIVILEGED		8	/* 特权指令*/
#define EXCCAUSE_UNALIGNED		9	/* 未对齐的加载或存储*/
#define EXCCAUSE_EXTREG_PRIVILEGE	10	/* 外部注册特权错误*/
#define EXCCAUSE_EXCLUSIVE_ERROR	11	/* 以独占方式加载不受支持的内存类型或未对齐的地址*/
#define EXCCAUSE_INSTR_DATA_ERROR	12	/* 指令获取时的PIF数据错误（RB-200x及更高版本）*/
#define EXCCAUSE_LOAD_STORE_DATA_ERROR	13	/* 加载或存储时PIF数据错误（RB-200x及更高版本）*/
#define EXCCAUSE_INSTR_ADDR_ERROR	14	/* 指令获取时的PIF地址错误（RB-200x及更高版本）*/
#define EXCCAUSE_LOAD_STORE_ADDR_ERROR	15	/* 加载或存储时的PIF地址错误（RB-200x及更高版本）*/
#define EXCCAUSE_ITLB_MISS		16	/* ITLB未命中（没有ITLB条目匹配，hw重新填充也未命中）*/
#define EXCCAUSE_ITLB_MULTIHIT		17	/* ITLB多重命中（多个ITLB条目匹配）*/
#define EXCCAUSE_INSTR_RING		18	/* 指令获取时的环特权冲突*/
/* 保留19*/	/* IFetch的大小限制（未实施）*/
#define EXCCAUSE_INSTR_PROHIBITED	20	/* 缓存属性不允许指令获取*/
/* 保留21..23*/
#define EXCCAUSE_DTLB_MISS		24	/* DTLB未命中（没有DTLB条目匹配，hw重新填充也未命中）*/
#define EXCCAUSE_DTLB_MULTIHIT		25	/* DTLB多重命中（多个DTLB条目匹配）*/
#define EXCCAUSE_LOAD_STORE_RING	26	/* 加载或存储时违反环特权*/
/* 保留27*/	/* 加载/存储的大小限制（未实施）*/
#define EXCCAUSE_LOAD_PROHIBITED	28	/* 缓存属性不允许加载*/
#define EXCCAUSE_STORE_PROHIBITED	29	/* 缓存属性不允许存储*/
/* 保留30..31*/
#define EXCCAUSE_CP_DISABLED(n)		(32+(n))	/* 禁用时访问协处理器“n”*/
#define EXCCAUSE_CP0_DISABLED		32	/* 禁用时访问协处理器0*/
#define EXCCAUSE_CP1_DISABLED		33	/* 禁用时访问协处理器1*/
#define EXCCAUSE_CP2_DISABLED		34	/* 禁用时访问协处理器2*/
#define EXCCAUSE_CP3_DISABLED		35	/* 禁用时访问协处理器3*/
#define EXCCAUSE_CP4_DISABLED		36	/* 禁用时访问协处理器4*/
#define EXCCAUSE_CP5_DISABLED		37	/* 禁用时访问协处理器5*/
#define EXCCAUSE_CP6_DISABLED		38	/* 禁用时访问协处理器6*/
#define EXCCAUSE_CP7_DISABLED		39	/* 禁用时访问协处理器7*/
/* 保留40..63*/

/*  PS寄存器字段：*/
#define PS_WOE_SHIFT		18
#define PS_WOE_MASK		0x00040000
#define PS_WOE			PS_WOE_MASK
#define PS_CALLINC_SHIFT	16
#define PS_CALLINC_MASK		0x00030000
#define PS_CALLINC(n)		(((n)&3)<<PS_CALLINC_SHIFT)	/* n=0..3*/
#define PS_OWB_SHIFT		8
#define PS_OWB_MASK		0x00000F00
#define PS_OWB(n)		(((n)&15)<<PS_OWB_SHIFT)	/* n=0..15（或0..7）*/
#define PS_RING_SHIFT		6
#define PS_RING_MASK		0x000000C0
#define PS_RING(n)		(((n)&3)<<PS_RING_SHIFT)	/* n=0..3*/
#define PS_UM_SHIFT		5
#define PS_UM_MASK		0x00000020
#define PS_UM			PS_UM_MASK
#define PS_EXCM_SHIFT		4
#define PS_EXCM_MASK		0x00000010
#define PS_EXCM			PS_EXCM_MASK
#define PS_INTLEVEL_SHIFT	0
#define PS_INTLEVEL_MASK	0x0000000F
#define PS_INTLEVEL(n)		((n)&PS_INTLEVEL_MASK)		/* n=0..15*/
/*  ABI导出的字段值：*/
#ifdef __XTENSA_CALL0_ABI__
#define PS_WOE_ABI		0
#define PS_WOECALL4_ABI		0
#else
#define PS_WOE_ABI		PS_WOE				/* 0x40000美元*/
#define PS_WOECALL4_ABI		(PS_WOE | PS_CALLINC(1))	/* 0x50000，每次调用4*/
#endif
/*  向后兼容性（已弃用）：*/
#define PS_PROGSTACK_SHIFT	PS_UM_SHIFT
#define PS_PROGSTACK_MASK	PS_UM_MASK
#define PS_PROG_SHIFT		PS_UM_SHIFT
#define PS_PROG_MASK		PS_UM_MASK
#define PS_PROG			PS_UM

/*  DBREAKCn寄存器字段：*/
#define DBREAKC_MASK_SHIFT		0
#define DBREAKC_MASK_MASK		0x0000003F
#define DBREAKC_LOADBREAK_SHIFT		30
#define DBREAKC_LOADBREAK_MASK		0x40000000
#define DBREAKC_STOREBREAK_SHIFT	31
#define DBREAKC_STOREBREAK_MASK		0x80000000

/*  DEBUGCUSE寄存器字段：*/
#define DEBUGCAUSE_DEBUGINT_SHIFT	5
#define DEBUGCAUSE_DEBUGINT_MASK	0x20	/* 调试中断*/
#define DEBUGCAUSE_BREAKN_SHIFT		4
#define DEBUGCAUSE_BREAKN_MASK		0x10	/* BREAK.N指令*/
#define DEBUGCAUSE_BREAK_SHIFT		3
#define DEBUGCAUSE_BREAK_MASK		0x08	/* BREAK指令*/
#define DEBUGCAUSE_DBREAK_SHIFT		2
#define DEBUGCAUSE_DBREAK_MASK		0x04	/* DBREAK匹配*/
#define DEBUGCAUSE_IBREAK_SHIFT		1
#define DEBUGCAUSE_IBREAK_MASK		0x02	/* IBREAK匹配*/
#define DEBUGCAUSE_ICOUNT_SHIFT		0
#define DEBUGCAUSE_ICOUNT_MASK		0x01	/* ICOUNT将增加到零*/

/*  MESR寄存器字段：*/
#define MESR_MEME		0x00000001	/* 存储器错误*/
#define MESR_MEME_SHIFT		0
#define MESR_DME		0x00000002	/* 双存储器错误*/
#define MESR_DME_SHIFT		1
#define MESR_RCE		0x00000010	/* 记录的存储器错误*/
#define MESR_RCE_SHIFT		4
#define MESR_LCE
#define MESR_LCE_SHIFT		?
#define MESR_LCE_L
#define MESR_ERRENAB		0x00000100
#define MESR_ERRENAB_SHIFT	8
#define MESR_ERRTEST		0x00000200
#define MESR_ERRTEST_SHIFT	9
#define MESR_DATEXC		0x00000400
#define MESR_DATEXC_SHIFT	10
#define MESR_INSEXC		0x00000800
#define MESR_INSEXC_SHIFT	11
#define MESR_WAYNUM_SHIFT	16
#define MESR_ACCTYPE_SHIFT	20
#define MESR_MEMTYPE_SHIFT	24
#define MESR_ERRTYPE_SHIFT	30

/*  MEMCTL寄存器字段：*/
#define MEMCTL_SNOOP_EN_SHIFT	1
#define MEMCTL_SNOOP_EN		0x02	/* 启用侦听响应（默认为0）*/
#define MEMCTL_L0IBUF_EN_SHIFT	0
#define MEMCTL_L0IBUF_EN	0x01	/* 启用循环指令缓冲区（默认值为1）*/
#define MEMCTL_INV_EN_SHIFT	23
#define MEMCTL_INV_EN		0x00800000	/* 正在增加的无效缓存方式*/
#define MEMCTL_DCWU_SHIFT	8
#define MEMCTL_DCWU_BITS	5
#define MEMCTL_DCWA_SHIFT	13
#define MEMCTL_DCWA_BITS	5
#define MEMCTL_ICWU_SHIFT	18
#define MEMCTL_ICWU_BITS	5
#define MEMCTL_DCWU_MASK	0x00001F00	/* 使用中的位8-12数据缓存方式*/
#define MEMCTL_DCWA_MASK	0x0003E000	/* 位13-17可分配数据缓存方式*/
#define MEMCTL_ICWU_MASK	0x007C0000	/* 使用中的18-22位icache方式*/
#define MEMCTL_DCWU_CLR_MASK	~(MEMCTL_DCWU_MASK)
#define MEMCTL_DCWA_CLR_MASK	~(MEMCTL_DCWA_MASK)
#define MEMCTL_ICWU_CLR_MASK	~(MEMCTL_ICWU_MASK)
#define MEMCTL_DCW_CLR_MASK	(MEMCTL_DCWU_CLR_MASK | MEMCTL_DCWA_CLR_MASK)
#define MEMCTL_IDCW_CLR_MASK	(MEMCTL_DCW_CLR_MASK | MEMCTL_ICWU_CLR_MASK)


#endif /*XTENSA_COREBITS_H*/

