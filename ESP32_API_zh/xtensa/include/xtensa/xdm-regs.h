/* xdm寄存器。h-XDM（Xtensa调试模块）的通用寄存器和相关定义*/

/* 版权所有（c）2016 Cadence Design Systems Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */


#ifndef _XDM_REGS_H_
#define _XDM_REGS_H_

/*  注意：此头文件包含在C、汇编程序和其他源中。因此，任何特定于C或特定于asm的内容都必须是适当的#ifdef'd。*/


/*
 *  XDM寄存器可以使用APB、ERI或JTAG（通过NAR）访问。APB和ERI的地址偏移相同，JTAG的地址偏移不同（由于7位NAR地址有限）。
 *
 *  这里，我们首先提供常量作为APB/ERI地址偏移量。这对于汇编程序代码（通过ERI访问XDM）是必要的，因为两个地址映射之间的复杂转换宏在汇编程序中不起作用。对于使用JTAG的软件，转换宏用于将这些地址转换为JTAG（NAR）地址。
 */
/* FIXME：这里可能只提供MISC+CS寄存器，并在单独的头中保留特定的子系统寄存器？例如TRAX、PERF、OCD*/

/*       XDM_…ERI地址[NAR地址]描述。。。。。。*/

/*  TRAX  */
#define  XDM_TRAX_ID		 0x100000	/*[0x0]ID*/
#define  XDM_TRAX_CONTROL 	 0x100004	/*[0x01]控制*/
#define  XDM_TRAX_STATUS	 0x100008	/*[0x02]状态*/
#define  XDM_TRAX_DATA		 0x10000C	/*[0x03]数据*/
#define  XDM_TRAX_ADDRESS	 0x100010	/*[0x04]地址*/
#define  XDM_TRAX_TRIGGER	 0x100014	/*[0x05]停止电脑*/
#define  XDM_TRAX_MATCH		 0x100018	/*[0x06]停止PC范围*/
#define  XDM_TRAX_DELAY		 0x10001C	/*[0x07]停止后触发器捕获大小*/
#define  XDM_TRAX_STARTADDR	 0x100020	/*[0x08]跟踪内存启动*/
#define  XDM_TRAX_ENDADDR	 0x100024	/*[0x09]跟踪内存结束*/
#define  XDM_TRAX_DEBUGPC	 0x10003C	/*[0x0F]调试PC*/
#define  XDM_TRAX_P4CHANGE	 0x100040	/*[0x10]X*/
#define  XDM_TRAX_TIME0		 0x100040	/*[0x10]首次寄存器*/
#define  XDM_TRAX_P4REV		 0x100044	/*[0x11]倍*/
#define  XDM_TRAX_TIME1		 0x100044	/*[0x11]第二时间寄存器*/
#define  XDM_TRAX_P4DATE	 0x100048	/*[0x12]X*/
#define  XDM_TRAX_INTTIME_MAX	 0x100048 	/*[0x12]时间戳IntTime的最大值*/
#define  XDM_TRAX_P4TIME	 0x10004C	/*[0x13]X*/
#define  XDM_TRAX_PDSTATUS	 0x100050	/*[0x14]PDebugStatus示例*/
#define  XDM_TRAX_PDDATA	 0x100054	/*[0x15]PDebugData示例*/
#define  XDM_TRAX_STOP_PC	 0x100058	/*[0x16]X*/
#define  XDM_TRAX_STOP_ICNT	 0x10005C	/*[0x16]X*/
#define  XDM_TRAX_MSG_STATUS	 0x100060	/*[0x17]X*/
#define  XDM_TRAX_FSM_STATUS	 0x100064	/*[0x18]倍*/
#define  XDM_TRAX_IB_STATUS	 0x100068	/*[0x19]X*/
#define  XDM_TRAX_STOPCNT	 0x10006C	/*[0x1A]X*/

/*  性能监视计数器*/
#define  XDM_PERF_PMG		0x101000	/*[0x20]性能模块。全局控制寄存器*/
#define  XDM_PERF_INTPC		0x101010	/*[0x24]性能监视器。中断PC*/
#define  XDM_PERF_PM0		0x101080	/*[0x28]性能参数。计数器0值*/
#define  XDM_PERF_PM1		0x101084	/*[0x29]性能参数。计数器1值*/
#define  XDM_PERF_PM2		0x101088	/*[0x2A]性能模块。计数器2值*/
#define  XDM_PERF_PM3		0x10108C	/*[0x2B]性能模块。计数器3值*/
#define  XDM_PERF_PM4		0x101090	/*[0x2C]性能模块。计数器4值*/
#define  XDM_PERF_PM5		0x101094	/*[0x2D]性能模块。计数器5值*/
#define  XDM_PERF_PM6		0x101098	/*[0x2E]性能监视器。计数器6值*/
#define  XDM_PERF_PM7		0x10109C	/*[0x2F]性能模块。计数器7值*/
#define  XDM_PERF_PM(n)		(0x101080+((n)<<2)) /* 性能cnt n=0..7值*/
#define  XDM_PERF_PMCTRL0	0x101100	/*[0x30]性能模块。计数器0控制*/
#define  XDM_PERF_PMCTRL1	0x101104	/*[0x31]性能模块。计数器1控制*/
#define  XDM_PERF_PMCTRL2	0x101108	/*[0x32]性能模块。计数器2控制*/
#define  XDM_PERF_PMCTRL3	0x10110C	/*[0x33]性能模块。计数器3控制*/
#define  XDM_PERF_PMCTRL4	0x101110	/*[0x34]性能模块。计数器4控制*/
#define  XDM_PERF_PMCTRL5	0x101114	/*[0x35]性能参数。计数器5控制*/
#define  XDM_PERF_PMCTRL6	0x101118	/*[0x36]性能模块。计数器6控制*/
#define  XDM_PERF_PMCTRL7	0x10111C	/*[0x37]性能模块。计数器7控制*/
#define  XDM_PERF_PMCTRL(n)	(0x101100+((n)<<2)) /* perfmon cnt n=0..7控制*/
#define  XDM_PERF_PMSTAT0	0x101180	/*[0x38]性能模块。计数器0状态*/
#define  XDM_PERF_PMSTAT1	0x101184	/*[0x39]性能模块。计数器1状态*/
#define  XDM_PERF_PMSTAT2	0x101188	/*[0x3A]性能模块。计数器2状态*/
#define  XDM_PERF_PMSTAT3	0x10118C	/*[0x3B]性能模块。计数器3状态*/
#define  XDM_PERF_PMSTAT4	0x101190	/*[0x3C]性能模块。计数器4状态*/
#define  XDM_PERF_PMSTAT5	0x101194	/*[0x3D]性能模块。计数器5状态*/
#define  XDM_PERF_PMSTAT6	0x101198	/*[0x3E]性能模块。计数器6状态*/
#define  XDM_PERF_PMSTAT7	0x10119C	/*[0x3F]性能模块。计数器7状态*/
#define  XDM_PERF_PMSTAT(n)	(0x101180+((n)<<2)) /* 性能cnt n=0..7状态*/

/*  片上调试（OCD）*/
#define  XDM_OCD_ID		0x102000	/*[0x40]ID寄存器*/
#define  XDM_OCD_DCR_CLR	0x102008	/*[0x42]调试控制寄存器清除*/
#define  XDM_OCD_DCR_SET	0x10200C	/*[0x43]调试控制注册表集*/
#define  XDM_OCD_DSR		0x102010	/*[0x44]调试状态注册表*/
#define  XDM_OCD_DDR		0x102014	/*[0x45]调试数据寄存器*/
#define  XDM_OCD_DDREXEC	0x102018	/*[0x46]调试数据reg+执行DIR*/
#define  XDM_OCD_DIR0EXEC	0x10201C	/*[0x47]调试指令reg，字0+执行DIR*/
#define  XDM_OCD_DIR0		0x102020	/*[0x48]调试指令reg，字1*/
#define  XDM_OCD_DIR1		0x102024	/*[0x49]调试指令reg，字2*/
#define  XDM_OCD_DIR2		0x102028	/*[0x4A]调试指令reg，字3*/
#define  XDM_OCD_DIR3		0x10202C	/*[0x49]调试指令reg，字4*/
#define  XDM_OCD_DIR4		0x102030	/*[0x4C]调试指令reg，字5*/
#define  XDM_OCD_DIR5		0x102034	/*[0x4D]调试指令reg，字5*/
#define  XDM_OCD_DIR6		0x102038	/*[0x4E]调试指令reg，字6*/
#define  XDM_OCD_DIR7		0x10203C	/*[0x4F]调试指令reg，字7*/

/*  其他寄存器*/
#define  XDM_MISC_PWRCTL	0x103020	/*[0x58]电源和重置控制*/
#define  XDM_MISC_PWRSTAT	0x103024	/*[0x59]电源和重置状态*/
#define  XDM_MISC_ERISTAT	0x103028	/*[0x5A]ERI事务状态*/
#define  XDM_MISC_DATETIME	0x103034
#define  XDM_MISC_CONFIGID1_V0	0x103034	/*[0x5D][INTERNAL]XDM v0/1中的ConfigID1*/
#define  XDM_MISC_CONFIGID1_V2	0x10007c	/*[0x1F][内部]自XDM v2以来的ConfigID1*/
#define  XDM_MISC_CONFIGID0_V2	0x100078	/*[0x1E][内部]自XDM v2以来的ConfigID0*/
#define  XDM_MISC_UBID		0x103038	/*[0x5E][内部]生成唯一ID*/
#define  XDM_MISC_CID		0x10303C	/*[0x5F][INTERNAL]客户ID*/

/*  CoreSight兼容性*/
#define  XDM_CS_ITCTRL		0x103F00	/*[0x60]集成模式控制寄存器*/
#define  XDM_CS_CLAIMSET	0x103FA0	/*[0x68]声明标记集reg*/
#define  XDM_CS_CLAIMCLR	0x103FA4	/*[0x69]索赔标记清除注册*/
#define  XDM_CS_LOCK_ACCESS	0x103FB0	/*[0x6B]锁定访问（写入0xC5ACCE55解锁）*/
#define  XDM_CS_LOCK_STATUS	0x103FB4	/*[0x6D]锁定状态*/
#define  XDM_CS_AUTH_STATUS	0x103FB8	/*[0x6E]身份验证状态*/
#define  XDM_CS_DEV_ID		0x103FC8	/*[0x72]设备ID*/
#define  XDM_CS_DEV_TYPE	0x103FCC	/*[0x73]设备类型*/
#define  XDM_CS_PER_ID4		0x103FD0	/*[0x74]外围设备ID reg字节4*/
#define  XDM_CS_PER_ID5		0x103FD4	/*[0x75]外围设备ID reg字节5*/
#define  XDM_CS_PER_ID6		0x103FD8	/*[0x76]外围设备ID reg字节6*/
#define  XDM_CS_PER_ID7		0x103FDC	/*[0x77]外围设备ID reg字节7*/
#define  XDM_CS_PER_ID0		0x103FE0	/*[0x78]外围设备ID reg字节0*/
#define  XDM_CS_PER_ID1		0x103FE4	/*[0x79]外围设备ID reg字节1*/
#define  XDM_CS_PER_ID2		0x103FE8	/*[0x7A]外围设备ID reg字节2*/
#define  XDM_CS_PER_ID3		0x103FEC	/*[0x7B]外围设备ID reg字节3*/
#define  XDM_CS_COMP_ID0	0x103FF0	/*[0x7C]组件ID reg字节0*/
#define  XDM_CS_COMP_ID1	0x103FF4	/*[0x7D]组件ID reg字节1*/
#define  XDM_CS_COMP_ID2	0x103FF8	/*[0x7E]组件ID reg字节2*/
#define  XDM_CS_COMP_ID3	0x103FFC	/*[0x7F]组件ID reg字节3*/

#define CS_PER_ID0	0x00000003
#define CS_PER_ID1	0x00000021
#define CS_PER_ID2	0x0000000f
#define CS_PER_ID3	0x00000000
#define CS_PER_ID4	0x00000024

#define CS_COMP_ID0	0x0000000d
#define CS_COMP_ID1	0x00000090
#define CS_COMP_ID2	0x00000005
#define CS_COMP_ID3	0x000000b1

#define CS_DEV_TYPE	0x00000015

#define XTENSA_IDCODE	0x120034e5    // FIXME（高位未指定，但BE已指定！）
#define XTENSA_MFC_ID	(XTENSA_IDCODE & 0xFFF)
#define CS_DEV_ID	XTENSA_IDCODE //FIXME-仅适用于XDM v0，对于v2是新的ID，它包括类似PRID的变量，但也可以自定义
#define CS_DEV_ID_v0_MASK	0x00000FFF // 只能比较较低的12位
#define CS_DEV_ID_v2_MASK	0xF0000000 // 只能比较高4位

#define NXS_OCD_REG(val)  ((val >= 0x40) && (val <= 0x5F))
#define NXS_TRAX_REG(val)  val <= 0x3F

#define ERI_TRAX_REG(val)  ((val & 0xFFFF) < 0x1000)
#define ERI_OCD_REG(val)   ((val & 0xFFFF) >= 0x2000) && ((val & 0xFFFF) < 0x4000))

/*  将以上14位ERI/APB地址/偏移量转换为7位NAR地址：*/
#define _XDM_ERI_TO_NAR(a)	( ((a)&0x3F80)==0x0000 ? (((a)>>2) & 0x1F) \
				: ((a)&0x3E00)==0x1000 ? (0x20 | (((a)>>2) & 7) | (((a)>>4) & 0x18)) \
				: ((a)&0x3FC0)==0x2000 ? (0x40 | (((a)>>2) & 0xF)) \
				: ((a)&0x3FE0)==0x3020 ? (0x50 | (((a)>>2) & 0xF)) \
				: ((a)&0x3FFC)==0x3F00 ? 0x60 \
				: ((a)&0x3F80)==0x3F80 ? (0x60 | (((a)>>2) & 0x1F)) \
				: -1 )

#define XDM_ERI_TO_NAR(a)	_XDM_ERI_TO_NAR(a & 0xFFFF)

/* 将7位NAR地址转换回ERI/APB地址/偏移量：*/
#define _XDM_NAR_TO_APB(a)	((a) <= 0x1f                ? ((a) << 2)                   \
				:(a) >= 0x20 && (a) <= 0x3F ? (0x1000 | (((a)&  7) << 2) | (((a)&0x18)<<4)) \
				:(a) >= 0x40 && (a) <= 0x4F ? (0x2000 | (((a)&0xF) << 2))  \
				:(a) >= 0x58 && (a) <= 0x5F ? (0x3000 | (((a)&0xF) << 2))  \
				:(a) == 0x60                ? (0x3F00)                     \
				:(a) >= 0x68 && (a) <= 0x7F ? (0x3F80 | (((a)&0x1F) << 2)) \
				: -1)

#define XDM_NAR_TO_APB(a)	_XDM_NAR_TO_APB((a & 0xFFFF))
#define XDM_NAR_TO_ERI(a)	_XDM_NAR_TO_APB((a & 0xFFFF)) | 0x100000

/* 将APB转换为ERI地址*/
#define XDM_APB_TO_ERI(a)	((a) | (0x100000))
#define XDM_ERI_TO_APB(a)	((a) & (0x0FFFFF))

/***********上述寄存器中的位定义***********/
#define OCD_ID_LSDDRP			0x01000000
#define OCD_ID_LSDDRP_SHIFT			24
#define OCD_ID_ENDIANESS		0x00000001
#define OCD_ID_ENDIANESS_SHIFT			 0
#define OCD_ID_PSO			0x0000000C
#define OCD_ID_PSO_SHIFT			 2
#define OCD_ID_TRACEPORT		0x00000080
#define OCD_ID_TRACEPORT_SHIFT			 7

#define OCD_ID_LSDDRP_XEA3		0x00000400

/*  电源状态寄存器。注：JTAG与ERI/APB中的不同比特位置！！*/
/*  ERI/APB:  */
#define PWRSTAT_CORE_DOMAIN_ON		0x00000001	/* 如果核心已通电，则设置*/
#define PWRSTAT_CORE_DOMAIN_ON_SHIFT		0
#define PWRSTAT_WAKEUP_RESET		0x00000002	/* [仅限ERI]0=冷启动，1=PSO唤醒*/
#define PWRSTAT_WAKEUP_RESET_SHIFT		1
#define PWRSTAT_CACHES_LOST_POWER	0x00000004	/* [ERI only]设置缓存（/localmems？）损失的功率*/
							/* FIX：这包括本地记忆吗？*/
#define PWRSTAT_CACHES_LOST_POWER_SHIFT		2
#define PWRSTAT_CORE_STILL_NEEDED	0x00000010	/* 如果其他人保持核心清醒*/
#define PWRSTAT_CORE_STILL_NEEDED_SHIFT		4
#define PWRSTAT_MEM_DOMAIN_ON		0x00000100	/* 设置内存域是否已通电*/
#define PWRSTAT_MEM_DOMAIN_ON_SHIFT		8
#define PWRSTAT_DEBUG_DOMAIN_ON		0x00001000	/* 设置调试域是否已通电*/
#define PWRSTAT_DEBUG_DOMAIN_ON_SHIFT		12
#define PWRSTAT_ALL_ON			(PWRSTAT_CORE_DOMAIN_ON | PWRSTAT_MEM_DOMAIN_ON | PWRSTAT_DEBUG_DOMAIN_ON)
#define PWRSTAT_CORE_WAS_RESET		0x00010000	/* [APB only]如果核心重置，则设置*/
#define PWRSTAT_CORE_WAS_RESET_SHIFT		16
#define PWRSTAT_DEBUG_WAS_RESET		0x10000000	/* 设置调试模块是否重置*/
#define PWRSTAT_DEBUG_WAS_RESET_SHIFT		28
/*  JTAG:  */
#define J_PWRSTAT_CORE_DOMAIN_ON	0x01		/* 如果核心已通电，则设置*/
#define J_PWRSTAT_MEM_DOMAIN_ON		0x02		/* 设置内存域是否已通电*/
#define J_PWRSTAT_DEBUG_DOMAIN_ON	0x04		/* 设置调试域是否已通电*/
#define J_PWRSTAT_ALL_ON		(J_PWRSTAT_CORE_DOMAIN_ON | J_PWRSTAT_MEM_DOMAIN_ON | J_PWRSTAT_DEBUG_DOMAIN_ON)
#define J_PWRSTAT_CORE_STILL_NEEDED	0x08		/* 如果其他人保持核心清醒*/
#define J_PWRSTAT_CORE_WAS_RESET	0x10		/* 如果核心重置，则设置*/
#define J_PWRSTAT_DEBUG_WAS_RESET	0x40		/* 设置调试模块是否重置*/

/*  电源控制寄存器。注：JTAG与ERI/APB中的不同比特位置！！*/
/*  ERI/APB:  */
#define PWRCTL_CORE_SHUTOFF		0x00000001	/* [ERI only]核心想在WAITI上关闭*/
#define PWRCTL_CORE_SHUTOFF_SHIFT		0
#define PWRCTL_CORE_WAKEUP		0x00000001	/* [APB only]设置为强制核心保持通电*/
#define PWRCTL_CORE_WAKEUP_SHIFT		0
#define PWRCTL_MEM_WAKEUP		0x00000100	/* 设置为强制内存域保持通电状态*/
#define PWRCTL_MEM_WAKEUP_SHIFT			8
#define PWRCTL_DEBUG_WAKEUP		0x00001000	/* 设置为强制调试域保持通电*/
#define PWRCTL_DEBUG_WAKEUP_SHIFT		12
#define PWRCTL_ALL_ON			(PWRCTL_CORE_WAKEUP | PWRCTL_MEM_WAKEUP | PWRCTL_DEBUG_WAKEUP)
#define PWRCTL_CORE_RESET		0x00010000	/* [APB only]设置为断言核心重置*/
#define PWRCTL_CORE_RESET_SHIFT			16
#define PWRCTL_DEBUG_RESET		0x10000000	/* 设置为断言调试模块重置*/
#define PWRCTL_DEBUG_RESET_SHIFT		28
/*  JTAG:  */
#define J_PWRCTL_CORE_WAKEUP		0x01		/* 设置为强制核心保持通电*/
#define J_PWRCTL_MEM_WAKEUP		0x02		/* 设置为强制内存域保持通电状态*/
#define J_PWRCTL_DEBUG_WAKEUP		0x04		/* 设置为强制调试域保持通电*/
#define J_DEBUG_USE			0x80		/*  */
#define J_PWRCTL_ALL_ON			(J_DEBUG_USE | J_PWRCTL_CORE_WAKEUP | J_PWRCTL_MEM_WAKEUP | J_PWRCTL_DEBUG_WAKEUP)
#define J_PWRCTL_DEBUG_ON		J_DEBUG_USE | J_PWRCTL_DEBUG_WAKEUP
#define J_PWRCTL_CORE_RESET		0x10		/* 设置为断言核心重置*/
#define J_PWRCTL_DEBUG_RESET		0x40		/* 设置为断言调试模块重置*/

#define J_PWRCTL_WRITE_MASK		0xFF
#define J_PWRSTAT_WRITE_MASK		0xFF

#define PWRCTL_WRITE_MASK		~0
#define PWRSTAT_WRITE_MASK		~0

/************以下内容仅与JTAG相关，因此可能仅属于OCD**************/

/*  XDM 5位JTAG指令寄存器（IR）值：*/
#define XDM_IR_PWRCTL		0x08	/* 选择8位电源/复位控制（PRC）*/
#define XDM_IR_PWRSTAT		0x09	/* 选择8位电源/复位状态（PRS）*/
#define XDM_IR_NAR_SEL		0x1c	/* 选择altern。8位NAR/32位NDR（Nexus风格）*/
#define XDM_IR_NDR_SEL		0x1d	/* 选择altern。32位NDR/8位NAR（FIXME-功能尚未在硬件中）*/
#define XDM_IR_IDCODE		0x1e	/* 选择32位JTAG IDCODE*/
#define XDM_IR_BYPASS		0x1f	/* 选择1位旁路*/

#define XDM_IR_WIDTH		5	/* Xtensa TAP的IR宽度*/

/*  NAR寄存器位：*/
#define XDM_NAR_WRITE		0x01
#define XDM_NAR_ADDR_MASK	0xFE
#define XDM_NAR_ADDR_SHIFT	1

#define XDM_NAR_BUSY		0x02
#define XDM_NAR_ERROR		0x01

#define NEXUS_DIR_READ	0x00
#define	NEXUS_DIR_WRITE	0x01

/************定义DCR寄存器位**************/

#define DCR_ENABLEOCD		0x0000001
#define DCR_ENABLEOCD_SHIFT		0
#define DCR_DEBUG_INT		0x0000002
#define DCR_DEBUG_INT_SHIFT		1
#define DCR_DEBUG_OVERRIDE	0x0000004  //ER或更高版本
#define DCR_DEBUG_OVERRIDE_SHIFT	2
#define DCR_DEBUG_SS_REQ	0x0000008
#define DCR_DEBUG_SS_REQ_SHIFT		3
#define DCR_DEBUG_OVERRIDE_CW	0x0000010  //RD及更早版本
#define DCR_DEBUG_OVERRIDE_CW_SHIFT	4
#define DCR_MASK_NMI		0x0000020
#define DCR_MASK_NMI_SHIFT		5
#define DCR_STEP_ENABLE		0x0000040
#define DCR_STEP_ENABLE_SHIFT		6
#define DCR_BREAK_IN_EN		0x0010000
#define DCR_BREAK_IN_EN_SHIFT		16
#define DCR_BREAK_OUT_EN	0x0020000
#define DCR_BREAK_OUT_EN_SHIFT		17
#define DCR_DEBUG_INT_EN	0x0040000
#define DCR_DEBUG_INT_EN_SHIFT		18
#define DCR_DBG_SW_ACTIVE	0x0100000
#define DCR_DBG_SW_ACTIVE_SHIFT		20
#define DCR_STALL_IN_EN		0x0200000
#define DCR_STALL_IN_EN_SHIFT		21
#define DCR_DEBUG_OUT_EN	0x0400000
#define DCR_DEBUG_OUT_EN_SHIFT		22
#define DCR_BREAK_OUT_ITO	0x1000000
#define DCR_STALL_OUT_ITO	0x2000000
#define DCR_STALL_OUT_ITO_SHIFT		25

/************定义DSR寄存器位**************/

#define DOSR_STOP_CAUSE_SHIFT	5
#define DOSR_STOP_CAUSE_MASK	0xF

#define DOSR_EXECDONE_SHIFT	0
#define DOSR_EXECDONE_ER	0x01
#define DOSR_EXECDONE_SHIFT	0
#define DOSR_EXCEPTION_ER	0x02
#define DOSR_EXCEPTION_SHIFT	1
#define DOSR_BUSY		0x04
#define DOSR_BUSY_SHIFT		2
#define DOSR_OVERRUN		0x08
#define DOSR_OVERRUN_SHIFT	3
#define DOSR_INOCDMODE_ER	0x10
#define DOSR_INOCDMODE_SHIFT	4
#define DOSR_CORE_WROTE_DDR_ER		0x400
#define DOSR_CORE_WROTE_DDR_SHIFT	10
#define DOSR_CORE_READ_DDR_ER		0x800
#define DOSR_CORE_READ_DDR_SHIFT	11
#define DOSR_HOST_WROTE_DDR_ER		0x4000
#define DOSR_HOST_WROTE_DDR_SHIFT	14
#define DOSR_HOST_READ_DDR_ER		0x8000
#define DOSR_HOST_READ_DDR_SHIFT	15

#define DOSR_DEBUG_PEND_BIN		0x10000
#define DOSR_DEBUG_PEND_HOST		0x20000
#define DOSR_DEBUG_PEND_TRAX		0x40000
#define DOSR_DEBUG_BIN		 	0x100000
#define DOSR_DEBUG_HOST			0x200000
#define DOSR_DEBUG_TRAX			0x400000
#define DOSR_DEBUG_PEND_BIN_SHIFT	16
#define DOSR_DEBUG_PEND_HOST_SHIFT	17
#define DOSR_DEBUG_PEND_TRAX_SHIFT	18
#define DOSR_DEBUG_BREAKIN              0x0100000
#define DOSR_DEBUG_BREAKIN_SHIFT        20
#define DOSR_DEBUG_HOST_SHIFT		21
#define DOSR_DEBUG_TRAX_SHIFT		22

#define DOSR_DEBUG_STALL		0x1000000
#define DOSR_DEBUG_STALL_SHIFT		24

#define DOSR_CORE_ON			0x40000000
#define DOSR_CORE_ON_SHIFT		30
#define DOSR_DEBUG_ON			0x80000000
#define DOSR_DEBUG_ON_SHIFT		31

/**********性能监视器寄存器位**********/

#define PERF_PMG_ENABLE                 0x00000001 /* 全局使能位*/
#define PERF_PMG_ENABLE_SHIFT           0

#define PERF_PMCTRL_INT_ENABLE          0x00000001 /* 溢出时断言中断*/
#define PERF_PMCTRL_INT_ENABLE_SHIFT    0
#define PERF_PMCTRL_KRNLCNT             0x00000008 /* 忽略TRACELEVEL*/
#define PERF_PMCTRL_KRNLCNT_SHIFT       3
#define PERF_PMCTRL_TRACELEVEL          0x000000F0 /* CINTLEVEL<=TRACELEVEL时计数*/
#define PERF_PMCTRL_TRACELEVEL_SHIFT    4
#define PERF_PMCTRL_SELECT              0x00001F00 /* 事件组选择器*/
#define PERF_PMCTRL_SELECT_SHIFT        8
#define PERF_PMCTRL_MASK                0xFFFF0000 /* 事件掩码*/
#define PERF_PMCTRL_MASK_SHIFT          16

#define PERF_PMSTAT_OVERFLOW            0x00000001 /* 计数器溢出*/
#define PERF_PMSTAT_OVERFLOW_SHIFT      0
#define PERF_PMSTAT_INT                 0x00000010 /* 中断断言*/
#define PERF_PMSTAT_INT_SHIFT           4

#if defined (USE_XDM_REGNAME) || defined (USE_DAP_REGNAME)
/*  描述XDM寄存器：*/
typedef struct {
    int    reg;
    char*  name;
} regdef_t;

/*
 *  返回指定XDM寄存器号的名称，或简单地“？？”如果寄存器号未被识别。FIXME-需要-1作为最后一个条目-更改以将名称与？？？进行比较？？？或者更好，让上面的代码工作。
 */
static char*
regname(regdef_t* list, int reg)
{
  int i = 0;
  while (list[i].reg != -1) {
    if (list[i].reg == reg)
      break;
    i++;
  }
  return list[i].name;
}

#if defined (USE_XDM_REGNAME)
static regdef_t xdm_reglist[] =
{
  {XDM_OCD_DSR        ,"DOSR"    },
  {XDM_OCD_DDR        ,"DDR"     },
  {XDM_OCD_DDREXEC    ,"DDREXEC" },
  {XDM_OCD_DIR0EXEC   ,"DIR0EXEC"},
  {XDM_OCD_DCR_CLR    ,"DCR_CLR" },
  {XDM_OCD_DCR_SET    ,"DCR_SET" },
  {XDM_TRAX_CONTROL   ,"CONTROL" },
  {XDM_TRAX_STATUS    ,"STATUS"  },
  {XDM_TRAX_DATA      ,"DATA"    },
  {XDM_TRAX_ADDRESS   ,"ADDRESS" },

  {XDM_TRAX_ID        ,"TRAX_ID"      },

  {XDM_TRAX_TRIGGER   ,"TRIGGER PC"   },
  {XDM_TRAX_MATCH     ,"PC MATCH"     },
  {XDM_TRAX_DELAY     ,"DELAY CNT."   },
  {XDM_TRAX_STARTADDR ,"START ADDRESS"},
  {XDM_TRAX_ENDADDR   ,"END ADDRESS"  },
  {XDM_TRAX_DEBUGPC   ,"DEBUG PC"  },
  {XDM_TRAX_P4CHANGE  ,"P4 CHANGE"    },
  {XDM_TRAX_P4REV     ,"P4 REV."      },
  {XDM_TRAX_P4DATE    ,"P4 DATE"      },
  {XDM_TRAX_P4TIME    ,"P4 TIME"      },
  {XDM_TRAX_PDSTATUS  ,"PD STATUS"    },
  {XDM_TRAX_PDDATA    ,"PD DATA"      },
  {XDM_TRAX_STOP_PC   ,"STOP PC"      },
  {XDM_TRAX_STOP_ICNT ,"STOP ICNT"    },
  {XDM_TRAX_MSG_STATUS,"MSG STAT."    },
  {XDM_TRAX_FSM_STATUS,"FSM STAT."    },
  {XDM_TRAX_IB_STATUS ,"IB STAT."     },

  {XDM_OCD_ID         ,"OCD_ID"  },
  {XDM_OCD_DIR0       ,"DIR0"    },
  {XDM_OCD_DIR1       ,"DIR1"    },
  {XDM_OCD_DIR2       ,"DIR2"    },
  {XDM_OCD_DIR3       ,"DIR3"    },
  {XDM_OCD_DIR4       ,"DIR4"    },
  {XDM_OCD_DIR5       ,"DIR5"    },
  {XDM_OCD_DIR6       ,"DIR6"    },
  {XDM_OCD_DIR7       ,"DIR7"    },

  {XDM_PERF_PMG       ,"PMG"    },
  {XDM_PERF_INTPC     ,"INTPC"  },
  {XDM_PERF_PM0       ,"PM0 "   },
  {XDM_PERF_PM1       ,"PM1 "   },
  {XDM_PERF_PM2       ,"PM2 "   },
  {XDM_PERF_PM3       ,"PM3 "   },
  {XDM_PERF_PM4       ,"PM4 "   },
  {XDM_PERF_PM5       ,"PM5 "   },
  {XDM_PERF_PM6       ,"PM6 "   },
  {XDM_PERF_PM7       ,"PM7 "   },
  {XDM_PERF_PMCTRL0   ,"PMCTRL0"},
  {XDM_PERF_PMCTRL1   ,"PMCTRL1"},
  {XDM_PERF_PMCTRL2   ,"PMCTRL2"},
  {XDM_PERF_PMCTRL3   ,"PMCTRL3"},
  {XDM_PERF_PMCTRL4   ,"PMCTRL4"},
  {XDM_PERF_PMCTRL5   ,"PMCTRL5"},
  {XDM_PERF_PMCTRL6   ,"PMCTRL6"},
  {XDM_PERF_PMCTRL7   ,"PMCTRL7"},
  {XDM_PERF_PMSTAT0   ,"PMSTAT0"},
  {XDM_PERF_PMSTAT1   ,"PMSTAT1"},
  {XDM_PERF_PMSTAT2   ,"PMSTAT2"},
  {XDM_PERF_PMSTAT3   ,"PMSTAT3"},
  {XDM_PERF_PMSTAT4   ,"PMSTAT4"},
  {XDM_PERF_PMSTAT5   ,"PMSTAT5"},
  {XDM_PERF_PMSTAT6   ,"PMSTAT6"},
  {XDM_PERF_PMSTAT7   ,"PMSTAT7"},

  {XDM_MISC_PWRCTL    ,"PWRCTL"  },
  {XDM_MISC_PWRSTAT   ,"PWRSTAT" },
  {XDM_MISC_ERISTAT   ,"ERISTAT" },
  {XDM_MISC_DATETIME  ,"DATETIME"},
  {XDM_MISC_UBID      ,"UBID"    },
  {XDM_MISC_CID       ,"CID"     },

  {XDM_CS_ITCTRL      ,"ITCTRL"     },
  {XDM_CS_CLAIMSET    ,"CLAIMSET"   },
  {XDM_CS_CLAIMCLR    ,"CLAIMCLR"   },
  {XDM_CS_LOCK_ACCESS ,"LOCK_ACCESS"},
  {XDM_CS_LOCK_STATUS ,"LOCK_STATUS"},
  {XDM_CS_AUTH_STATUS ,"AUTH_STATUS"},
  {XDM_CS_DEV_ID      ,"DEV_ID"     },
  {XDM_CS_DEV_TYPE    ,"DEV_TYPE"   },
  {XDM_CS_PER_ID4     ,"PER_ID4"    },
  {XDM_CS_PER_ID5     ,"PER_ID5"    },
  {XDM_CS_PER_ID6     ,"PER_ID6"    },
  {XDM_CS_PER_ID7     ,"PER_ID7"    },
  {XDM_CS_PER_ID0     ,"PER_ID0"    },
  {XDM_CS_PER_ID1     ,"PER_ID1"    },
  {XDM_CS_PER_ID2     ,"PER_ID2"    },
  {XDM_CS_PER_ID3     ,"PER_ID3"    },
  {XDM_CS_COMP_ID0    ,"COMP_ID0"   },
  {XDM_CS_COMP_ID1    ,"COMP_ID1"   },
  {XDM_CS_COMP_ID2    ,"COMP_ID2"   },
  {XDM_CS_COMP_ID3    ,"COMP_ID3"   },
  {-1                 ,"???"        },
};
#endif

#endif

#endif /* _XDM_REGS_H_ */

