/* TRAX寄存器定义

   版权所有（c）2006-2012 Tensilica Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef _TRAX_REGISTERS_H_
#define _TRAX_REGISTERS_H_

#define SHOW	1
#define HIDE	0

#define RO	0
#define RW	1

/*  TRAX寄存器编号（从0..127的可能范围）*/
#if 0
#define TRAXREG_ID		0
#define TRAXREG_CONTROL		1
#define TRAXREG_STATUS		2
#define TRAXREG_DATA		3
#define TRAXREG_ADDRESS		4
#define TRAXREG_TRIGGER		5
#define TRAXREG_MATCH		6
#define TRAXREG_DELAY		7
#define TRAXREG_STARTADDR	8
#define TRAXREG_ENDADDR		9
/*  仅供内部使用（未发布）：*/
#define TRAXREG_P4CHANGE	16
#define TRAXREG_P4REV		17
#define TRAXREG_P4DATE		18
#define TRAXREG_P4TIME		19
#define TRAXREG_PDSTATUS	20
#define TRAXREG_PDDATA		21
#define TRAXREG_STOP_PC		22
#define TRAXREG_STOP_ICNT	23
#define TRAXREG_MSG_STATUS	24
#define TRAXREG_FSM_STATUS	25
#define TRAXREG_IB_STATUS	26
#define TRAXREG_MAX		27
#define TRAXREG_ITCTRL		96
#endif
/* 上述寄存器与NAR地址匹配。因此，它们的值用于NAR访问*/

/*  TRAX寄存器字段*/

/*  TRAX ID寄存器字段：*/
#define TRAX_ID_PRODNO          0xf0000000	/* 产品编号（0=TRAX）*/
#define TRAX_ID_PRODOPT         0x0f000000	/* 产品选项*/
#define TRAX_ID_MIW64		0x08000000	/* opt：指令宽度*/
#define TRAX_ID_AMTRAX		0x04000000	/* opt：选项集合，内部（VER_2_0或更高版本）*/
#define TRAX_ID_MAJVER(id)	(((id) >> 20) & 0x0f)
#define TRAX_ID_MINVER(id)	(((id) >> 17) & 0x07)
#define TRAX_ID_VER(id)		((TRAX_ID_MAJVER(id)<<4)|TRAX_ID_MINVER(id))
#define TRAX_ID_STDCFG		0x00010000	/* 标准配置*/
#define TRAX_ID_CFGID		0x0000ffff	/* TRAX配置ID*/
#define TRAX_ID_MEMSHARED	0x00001000	/* TRAX中的Memshared选项*/
#define TRAX_ID_FROM_VER(ver)	((((ver) & 0xf0) << 16) | (((ver) & 0x7) << 17))
/*  其他TRAX ID寄存器宏：*/
/*  感兴趣的TRAX版本（TRAX_ID_VER（），即MAJEVER*16+MINVER）：*/
#define TRAX_VER_1_0		0x10		/* RA */
#define TRAX_VER_1_1		0x11		/* RB至RC-2010.1*/
#define TRAX_VER_2_0		0x20		/* RC-2010.2, RD-2010.0, RD-2011.1 */
#define TRAX_VER_2_1		0x21		/* RC-2013/RD-2012.2及更高版本*/
#define TRAX_VER_3_0		0x30		/* RE-2012.0 */
#define	TRAX_VER_3_1		0x31		/* RE-2012.1 */
#define TRAX_VER_HUAWEI_3	TRAX_VER_3_0	/* 对于华为，PR：25223、25224、24880*/


/*  TRAX 1.0版需要几个软件解决方案：*/
#define TRAX_ID_1_0_ERRATUM(id)	(TRAX_ID_VER(id) == TRAX_VER_1_0)
/*  TRAX 2.0版需要PR 22161的软件解决方案：*/
#define TRAX_ID_MEMSZ_ERRATUM(id)	(TRAX_ID_VER(id) == TRAX_VER_2_0)

/*  TRAX控制寄存器字段：*/
#define TRAX_CONTROL_TREN	0x00000001
#define TRAX_CONTROL_TRSTP	0x00000002
#define TRAX_CONTROL_PCMEN	0x00000004
#define TRAX_CONTROL_PTIEN	0x00000010
#define TRAX_CONTROL_CTIEN	0x00000020
#define TRAX_CONTROL_TMEN	0x00000080	/* 2.0+ */
#define TRAX_CONTROL_CNTU	0x00000200
#define TRAX_CONTROL_BIEN	0x00000400
#define TRAX_CONTROL_BOEN	0x00000800
#define TRAX_CONTROL_TSEN	0x00000800
#define TRAX_CONTROL_SMPER	0x00007000
#define TRAX_CONTROL_SMPER_SHIFT	12
#define TRAX_CONTROL_PTOWT	0x00010000
#define TRAX_CONTROL_CTOWT	0x00020000
#define TRAX_CONTROL_PTOWS	0x00100000
#define TRAX_CONTROL_CTOWS	0x00200000
#define TRAX_CONTROL_ATID	0x7F000000	/* 2.0以上，amtrax*/
#define TRAX_CONTROL_ATID_SHIFT		24
#define TRAX_CONTROL_ATEN	0x80000000	/* 2.0以上，amtrax*/

#define TRAX_CONTROL_PTOWS_ER	0x00020000	/* 对于3.0*/
#define TRAX_CONTROL_CTOWT_ER	0x00100000	/* 对于3.0*/

#define TRAX_CONTROL_ITCTO	0x00400000	/* 对于3.0*/
#define TRAX_CONTROL_ITCTIA	0x00800000	/* 对于3.0*/
#define TRAX_CONTROL_ITATV	0x01000000	/* 对于3.0*/


/*  TRAX状态寄存器字段：*/
#define TRAX_STATUS_TRACT	0x00000001
#define TRAX_STATUS_TRIG	0x00000002
#define TRAX_STATUS_PCMTG	0x00000004
#define TRAX_STATUS_BUSY	0x00000008  /* ER ??? */
#define TRAX_STATUS_PTITG	0x00000010
#define TRAX_STATUS_CTITG	0x00000020
#define TRAX_STATUS_MEMSZ	0x00001F00
#define TRAX_STATUS_MEMSZ_SHIFT		8
#define TRAX_STATUS_PTO		0x00010000
#define TRAX_STATUS_CTO		0x00020000

#define TRAX_STATUS_ITCTOA	0x00400000	/* 对于3.0*/
#define TRAX_STATUS_ITCTI	0x00800000	/* 对于3.0*/
#define TRAX_STATUS_ITATR	0x01000000	/* 对于3.0*/


/*  TRAX地址寄存器字段：*/
#define TRAX_ADDRESS_TWSAT	0x80000000
#define TRAX_ADDRESS_TWSAT_SHIFT	31
#define TRAX_ADDRESS_TOTALMASK	0x00FFFFFF
// !!! VUAKIU。为新TRAX添加：
#define TRAX_ADDRESS_WRAPCNT	0x7FE00000	/* 版本*/
#define TRAX_ADDRESS_WRAP_SHIFT		21

/*  TRAX PCMatch寄存器字段：*/
#define TRAX_PCMATCH_PCML	0x0000001F
#define TRAX_PCMATCH_PCML_SHIFT		0
#define TRAX_PCMATCH_PCMS	0x80000000

/*  从状态寄存器计算跟踪ram缓冲区大小（字节）：*/
#define TRAX_MEM_SIZE(status)	(1L << (((status) & TRAX_STATUS_MEMSZ) >> TRAX_STATUS_MEMSZ_SHIFT))

#if 0
/*  描述寄存器中的字段：*/
typedef struct {
    const char*	name;
// 无符号宽度；
// 无符号移位；
    char	width;
    char	shift;
    char	visible;		/* 0=仅供内部使用，1=显示*/
    char	reserved;
} trax_regfield_t;
#endif

/*  描述TRAX寄存器：*/
typedef struct {
    const char*	name;
    unsigned	id;
    char	width;
    char	visible;
    char	writable;
    char	reserved;
    //常量trax_regfield_t*字段集；
} trax_regdef_t;


extern const trax_regdef_t	trax_reglist[];
extern const signed int 	trax_readable_regs[];
extern const signed int 	trax_unamed_header_regs[];

#ifdef  __cplusplus
extern "C" {
#endif

/*  原型：*/
extern int		trax_find_reg(char * regname, char **errmsg);
extern const char *	trax_regname(int regno);

#ifdef  __cplusplus
}
#endif

#endif /* _TRAX_REGISTERS_H_ */

