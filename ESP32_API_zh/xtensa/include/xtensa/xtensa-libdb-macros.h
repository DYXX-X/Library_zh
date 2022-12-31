/*
 *  扩展libdb宏.h
 */

/* $Id://depot/rel/Foxhill/dot.9/Xtensa/Software/libdb/extensa-libdb-macros。小时#1$*/

/* 版权所有（c）2004-2008 Tensilica Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __H_LIBDB_MACROS
#define __H_LIBDB_MACROS

/*
 *  此头文件提供宏，用于构造、标识和使用分配给各种类型的Xtensa处理器寄存器和状态的“目标编号”。这些目标编号由GDB在远程协议中使用，因此所有GDB调试器代理（目标）都使用这些编号。它们也用于ELF调试器信息部分（stabs、dwarf等）。
 *
 *  这些宏与xtensa-libdb分开。h，因为某些不使用或无法访问libdb的调试器代理需要它们，例如OCD守护程序、RedBoot、XMON等。
 *
 *  目前，为了与某些第三方调试器软件供应商兼容，目标数限制为16位。可以想象，这将在未来扩展到32位。
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef uint32
 #define uint32	unsigned int
#endif
#ifndef int32
 #define int32	int
#endif


/*
 *  用于形成各种标准寄存器/状态的寄存器“目标编号”的宏：
 */
#define XTENSA_DBREGN_INVALID		-1		/* 不是有效的目标号码*/
#define XTENSA_DBREGN_A(n)		(0x0000+(n))	/* 地址寄存器a0..a15*/
#define XTENSA_DBREGN_B(n)		(0x0010+(n))	/* 布尔位b0..b15*/
#define XTENSA_DBREGN_PC		 0x0020		/* 程序计数器*/
				      /* 0x0021保留供Tensilica使用*/
#define XTENSA_DBREGN_BO(n)		(0x0022+(n))	/* 布尔八元组位bo0..bo1*/
#define XTENSA_DBREGN_BQ(n)		(0x0024+(n))	/* 布尔四位bq0..bq3*/
#define XTENSA_DBREGN_BD(n)		(0x0028+(n))	/* 布尔双位bd0..bd7*/
#define XTENSA_DBREGN_F(n)		(0x0030+(n))	/* 浮点寄存器f0..f15*/
#define XTENSA_DBREGN_VEC(n)		(0x0040+(n))	/* Vectra vec regs v0..v15*/
#define XTENSA_DBREGN_VSEL(n)		(0x0050+(n))	/* 车辆选择s0..s3（V1）..s7（V2）*/
#define XTENSA_DBREGN_VALIGN(n)		(0x0058+(n))	/* Vectra有效规则u0…u3*/
#define XTENSA_DBREGN_VCOEFF(n)		(0x005C+(n))	/* Vectra I vcoeff调节器c0..c1*/
				      /* 0x005E…0x005F保留供Tensilica使用*/
#define XTENSA_DBREGN_AEP(n)		(0x0060+(n))	/* HiFi2音频引擎regs aep0..aep7*/
#define XTENSA_DBREGN_AEQ(n)		(0x0068+(n))	/* HiFi2音频引擎regs aeq0..aeq3*/
				      /* 0x006C..0x00FF保留供Tensilica使用*/
#define XTENSA_DBREGN_AR(n)		(0x0100+(n))	/* 物理地址regs ar0..ar63（注意：仅使用窗口选项）*/
				      /* 0x0140..0x01FF保留供Tensilica使用*/
#define XTENSA_DBREGN_SREG(n)		(0x0200+(n))	/* 特殊寄存器0..255（核心）*/
#define XTENSA_DBREGN_BR		XTENSA_DBREGN_SREG(0x04)	/* 所有16个布尔位，BR*/
#define XTENSA_DBREGN_MR(n)		XTENSA_DBREGN_SREG(0x20+(n))	/* MAC16寄存器m0..m3*/
#define XTENSA_DBREGN_UREG(n)		(0x0300+(n))	/* 用户寄存器0..255（TIE）*/
				      /* 0x0400..0x0FFF保留供Tensilica使用*/
				      /* 0x1000..0x1FFF用户定义的regfile*/
				      /* 0x2000..0xEFFF其他状态（和regfile）*/
#define XTENSA_DBREGN_DBAGENT(n)	(0xF000+(n))	/* 非处理器“寄存器”0..4095，供第三方调试器代理定义使用*/
				      /* >0xFFFF（32位）保留供Tensilica使用*/
/*#定义XTENSA_DBREGN_CONTEXT（n）（0x02000000+（（n）<<20））*/	/* 将此宏的值添加到目标编号，以标识上下文复制寄存器的特定上下文0..31*/
#define XTENSA_DBREGN_MASK		0xFFFF		/* 有效target_number位掩码*/
#define XTENSA_DBREGN_WRITE_SIDE	0x04000000	/* 用于请求写入寄存器的一半的标志，该寄存器被拆分为具有相同目标编号的不同读写条目（当前仅在两个libdbAPI函数中有效；有关详细信息，请参阅xtensa-libdb.h）*/

/*
 *  用于识别特定范围的目标编号（如上所述）的宏：注意：任何上下文编号（或其他高12位）都被视为修饰符，因此出于识别目的而被去除。
 */
#define XTENSA_DBREGN_IS_VALID(tn)	(((tn) & ~0xFFFF) == 0)	/* 只是测试它是16位无符号的*/
#define XTENSA_DBREGN_IS_A(tn)		(((tn) & 0xFFF0)==0x0000)	/* 为a0..a15*/
#define XTENSA_DBREGN_IS_B(tn)		(((tn) & 0xFFF0)==0x0010)	/* 为b0..b15*/
#define XTENSA_DBREGN_IS_PC(tn)		(((tn) & 0xFFFF)==0x0020)	/* 是程序计数器*/
#define XTENSA_DBREGN_IS_BO(tn)		(((tn) & 0xFFFE)==0x0022)	/* 是bo0..bo1*/
#define XTENSA_DBREGN_IS_BQ(tn)		(((tn) & 0xFFFC)==0x0024)	/* 是bq0..bq3*/
#define XTENSA_DBREGN_IS_BD(tn)		(((tn) & 0xFFF8)==0x0028)	/* 为bd0..bd7*/
#define XTENSA_DBREGN_IS_F(tn)		(((tn) & 0xFFF0)==0x0030)	/* 为f0..f15*/
#define XTENSA_DBREGN_IS_VEC(tn)	(((tn) & 0xFFF0)==0x0040)	/* 是v0..v15*/
#define XTENSA_DBREGN_IS_VSEL(tn)	(((tn) & 0xFFF8)==0x0050)	/* 是s0..s7（V1中的s0..s3）*/
#define XTENSA_DBREGN_IS_VALIGN(tn)	(((tn) & 0xFFFC)==0x0058)	/* 是u0..u3*/
#define XTENSA_DBREGN_IS_VCOEFF(tn)	(((tn) & 0xFFFE)==0x005C)	/* 是c0..c1*/
#define XTENSA_DBREGN_IS_AEP(tn)	(((tn) & 0xFFF8)==0x0060)	/* 是aep0..aep7*/
#define XTENSA_DBREGN_IS_AEQ(tn)	(((tn) & 0xFFFC)==0x0068)	/* 是aeq0..aeq3*/
#define XTENSA_DBREGN_IS_AR(tn)		(((tn) & 0xFFC0)==0x0100)	/* 是ar0..ar63*/
#define XTENSA_DBREGN_IS_SREG(tn)	(((tn) & 0xFF00)==0x0200)	/* 是特殊寄存器*/
#define XTENSA_DBREGN_IS_BR(tn)		(((tn) & 0xFFFF)==XTENSA_DBREGN_SREG(0x04))	/* 是BR*/
#define XTENSA_DBREGN_IS_MR(tn)		(((tn) & 0xFFFC)==XTENSA_DBREGN_SREG(0x20))	/* m0..m3*/
#define XTENSA_DBREGN_IS_UREG(tn)	(((tn) & 0xFF00)==0x0300)	/* 是用户注册*/
#define XTENSA_DBREGN_IS_DBAGENT(tn)	(((tn) & 0xF000)==0xF000)	/* 是非处理器*/
/*#定义XTENSA_DBREGN_IS_CONTEXT（tn）（（（tn）&0x02000000）！=0)*/	/* 指定上下文#*/

/*
 *  当使用上面的一个_IS_宏标识了特定范围时，从寄存器“目标编号”中提取寄存器索引的宏。只有当相应的_IS_宏返回true时，这些宏才会返回有用的值。
 */
#define XTENSA_DBREGN_A_INDEX(tn)	((tn) & 0x0F)		/* a0..a15为0..15*/
#define XTENSA_DBREGN_B_INDEX(tn)	((tn) & 0x0F)		/* b0..b15的0..15*/
#define XTENSA_DBREGN_BO_INDEX(tn)	((tn) & 0x01)		/* bo0..bo1的0..1*/
#define XTENSA_DBREGN_BQ_INDEX(tn)	((tn) & 0x03)		/* bq0..bq3的0..3*/
#define XTENSA_DBREGN_BD_INDEX(tn)	((tn) & 0x07)		/* 用于bd0..bd7的0..7*/
#define XTENSA_DBREGN_F_INDEX(tn)	((tn) & 0x0F)		/* f0..f15为0..15*/
#define XTENSA_DBREGN_VEC_INDEX(tn)	((tn) & 0x0F)		/* v0..v15的0..15*/
#define XTENSA_DBREGN_VSEL_INDEX(tn)	((tn) & 0x07)		/* s0..s7的0..7*/
#define XTENSA_DBREGN_VALIGN_INDEX(tn)	((tn) & 0x03)		/* u0..u3的0..3*/
#define XTENSA_DBREGN_VCOEFF_INDEX(tn)	((tn) & 0x01)		/* c0..c1的0..1*/
#define XTENSA_DBREGN_AEP_INDEX(tn)	((tn) & 0x07)		/* 用于aep0..aep7的0..7*/
#define XTENSA_DBREGN_AEQ_INDEX(tn)	((tn) & 0x03)		/* 用于aeq0..aeq3的0..3*/
#define XTENSA_DBREGN_AR_INDEX(tn)	((tn) & 0x3F)		/* ar0..ar63为0..63*/
#define XTENSA_DBREGN_SREG_INDEX(tn)	((tn) & 0xFF)		/* 0..255用于特殊寄存器*/
#define XTENSA_DBREGN_MR_INDEX(tn)	((tn) & 0x03)		/* m0..m3为0..3*/
#define XTENSA_DBREGN_UREG_INDEX(tn)	((tn) & 0xFF)		/* 0..255用于用户寄存器*/
#define XTENSA_DBREGN_DBAGENT_INDEX(tn)	((tn) & 0xFFF)		/* 0..4095用于非处理器*/
/*#定义XTENSA_DBREGN_CONTEXT_INDEX（tn）（（tn>>20）&0x1F）*/	/* 0..31上下文编号*/




#ifdef __cplusplus
}
#endif

#endif /* __H_LIBDB_MACROS */

