/*
 * xtensa/config/core-isa。h—依赖于Xtensa处理器CORE配置的HAL定义
 *
 *  请参见<xtensa/config/core。h> ，其中包含此文件，以了解更多详细信息。
 */

/* Xtensa处理器核心配置信息。

   客户ID=11657；内部版本=0x5fe96；版权所有（c）1999-2016 Tensilica Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef _XTENSA_CORE_CONFIGURATION_H
#define _XTENSA_CORE_CONFIGURATION_H


/****************************************************************************
对任何代码、用户或特权有用的参数
 ****************************************************************************/

/*
 *  注意：如果配置了选项，XCHAL_HAVE_***形式的宏的值为1，否则为0。始终定义这些宏。
 */


/*----------------------------------------------------------------------
				ISA
  ----------------------------------------------------------------------*/

#define XCHAL_HAVE_BE			0	/* 大端字节排序*/
#define XCHAL_HAVE_WINDOWED		1	/* 窗口寄存器选项*/
#define XCHAL_NUM_AREGS			64	/* 物理地址寄存器数*/
#define XCHAL_NUM_AREGS_LOG2		6	/* 日志2（XCHAL_NUM_AREGS）*/
#define XCHAL_MAX_INSTRUCTION_SIZE	3	/* 最大instr字节（3..8）*/
#define XCHAL_HAVE_DEBUG		1	/* 调试选项*/
#define XCHAL_HAVE_DENSITY		1	/* 16位指令*/
#define XCHAL_HAVE_LOOPS		1	/* 零开销环路*/
#define XCHAL_LOOP_BUFFER_SIZE		256	/* 零电压。循环指令缓冲区大小*/
#define XCHAL_HAVE_NSA			1	/* NSA/NSAU说明*/
#define XCHAL_HAVE_MINMAX		1	/* MIN/MAX指令*/
#define XCHAL_HAVE_SEXT			1	/* SEXT指令*/
#define XCHAL_HAVE_DEPBITS		0	/* DEPBITS指令*/
#define XCHAL_HAVE_CLAMPS		1	/* CLAMPS指令*/
#define XCHAL_HAVE_MUL16		1	/* MUL16S/MUL16U指令*/
#define XCHAL_HAVE_MUL32		1	/* MULL指令*/
#define XCHAL_HAVE_MUL32_HIGH		1	/* MULUH/MULSH指令*/
#define XCHAL_HAVE_DIV32		1	/* QUOS/QUOU/REMS/REMU说明*/
#define XCHAL_HAVE_L32R			1	/* L32R指令*/
#define XCHAL_HAVE_ABSOLUTE_LITERALS	0	/* 非PC相关（扩展）L32R*/
#define XCHAL_HAVE_CONST16		0	/* CONST16指令*/
#define XCHAL_HAVE_ADDX			1	/* ADDX#/SUBX#指令*/
#define XCHAL_HAVE_WIDE_BRANCHES	0	/* B*。W18或B*。W15仪表*/
#define XCHAL_HAVE_PREDICTED_BRANCHES	0	/* B[EQ/EQZ/NE/NEZ]仪表*/
#define XCHAL_HAVE_CALL4AND12		1	/* （过时选项）*/
#define XCHAL_HAVE_ABS			1	/* ABS指令*/
/*#定义XCHAL_HAVE_OPC 0*/	/* POPC指令*/
/*#定义XCHAL_HAVE_CRC 0*/	/* CRC指令*/
#define XCHAL_HAVE_RELEASE_SYNC		1	/* L32AI/S32RI说明*/
#define XCHAL_HAVE_S32C1I		1	/* S32C1I指令*/
#define XCHAL_HAVE_SPECULATION		0	/* 投机*/
#define XCHAL_HAVE_FULL_RESET		1	/* 所有regs/状态重置*/
#define XCHAL_NUM_CONTEXTS		1	/* */
#define XCHAL_NUM_MISC_REGS		4	/* 划痕次数（0..4）*/
#define XCHAL_HAVE_TAP_MASTER		0	/* JTAG TAP控制仪表*/
#define XCHAL_HAVE_PRID			1	/* 处理器ID寄存器*/
#define XCHAL_HAVE_EXTERN_REGS		1	/* WER/RER指令*/
#define XCHAL_HAVE_MX			0	/* MX芯（Tensilica内部）*/
#define XCHAL_HAVE_MP_INTERRUPTS	0	/* 中断分配器端口*/
#define XCHAL_HAVE_MP_RUNSTALL		0	/* 核心RunStall控制端口*/
#define XCHAL_HAVE_PSO			0	/* 电源关闭*/
#define XCHAL_HAVE_PSO_CDM		0	/* 核心/调试/内存pwr域*/
#define XCHAL_HAVE_PSO_FULL_RETENTION	0	/* PSO上保留的所有规则*/
#define XCHAL_HAVE_THREADPTR		1	/* THREADPTR寄存器*/
#define XCHAL_HAVE_BOOLEANS		1	/* 布尔寄存器*/
#define XCHAL_HAVE_CP			1	/* CPENABLE reg（协处理器）*/
#define XCHAL_CP_MAXCFG			8	/* 最大允许cp id加1*/
#define XCHAL_HAVE_MAC16		1	/* MAC16包*/

#define XCHAL_HAVE_FUSION		 0	/* 融合*/
#define XCHAL_HAVE_FUSION_FP	 0	        /* Fusion FP选项*/
#define XCHAL_HAVE_FUSION_LOW_POWER 0	/* Fusion低功耗选件*/
#define XCHAL_HAVE_FUSION_AES	 0	        /* Fusion BLE/Wifi AES-128 CCM选件*/
#define XCHAL_HAVE_FUSION_CONVENC	 0       /* Fusion Conv编码选项*/
#define XCHAL_HAVE_FUSION_LFSR_CRC	 0	/* Fusion LFSR-CRC选件*/
#define XCHAL_HAVE_FUSION_BITOPS	 0	/* Fusion Bit操作支持选项*/
#define XCHAL_HAVE_FUSION_AVS	 0	/* Fusion AVS选项*/
#define XCHAL_HAVE_FUSION_16BIT_BASEBAND	 0	/* 融合16位基带选项*/
#define XCHAL_HAVE_FUSION_VITERBI        0     /* Fusion Viterbi选项*/
#define XCHAL_HAVE_FUSION_SOFTDEMAP      0   /* Fusion Soft Bit Demap选项*/
#define XCHAL_HAVE_HIFIPRO		0	/* HiFiPro音频引擎软件包*/
#define XCHAL_HAVE_HIFI4		0	/* HiFi4音频引擎软件包*/
#define XCHAL_HAVE_HIFI4_VFPU		0	/* HiFi4音频引擎VFPU选项*/
#define XCHAL_HAVE_HIFI3		0	/* HiFi3音频引擎软件包*/
#define XCHAL_HAVE_HIFI3_VFPU		0	/* HiFi3音频引擎VFPU选项*/
#define XCHAL_HAVE_HIFI2		0	/* HiFi2音频引擎软件包*/
#define XCHAL_HAVE_HIFI2EP		0	/* 高Fi2EP*/
#define XCHAL_HAVE_HIFI_MINI		0


#define XCHAL_HAVE_VECTORFPU2005	0	/* 矢量或用户浮点pkg*/
#define XCHAL_HAVE_USER_DPFPU         0       /* 用户DP浮点pkg*/
#define XCHAL_HAVE_USER_SPFPU         0       /* 用户DP浮点pkg*/
#define XCHAL_HAVE_FP                 1      /* 单预充电浮点*/
#define XCHAL_HAVE_FP_DIV             1  /* 带DIV指令的FP*/
#define XCHAL_HAVE_FP_RECIP           1        /* 带RECIP指令的FP*/
#define XCHAL_HAVE_FP_SQRT            1 /* 带SQRT指令的FP*/
#define XCHAL_HAVE_FP_RSQRT           1        /* 带RSQRT指令的FP*/
#define XCHAL_HAVE_DFP                        0     /* 双精度FP包装*/
#define XCHAL_HAVE_DFP_DIV            0 /* 带DIV指令的DFP*/
#define XCHAL_HAVE_DFP_RECIP          0       /* 带RECIP指令的DFP*/
#define XCHAL_HAVE_DFP_SQRT           0        /* 带SQRT指令的DFP*/
#define XCHAL_HAVE_DFP_RSQRT          0       /* 带RSQRT指令的DFP*/
#define XCHAL_HAVE_DFP_ACCEL		1	/* 双精度FP加速度pkg*/
#define XCHAL_HAVE_DFP_accel		XCHAL_HAVE_DFP_ACCEL				/* 用于向后兼容*/

#define XCHAL_HAVE_DFPU_SINGLE_ONLY    1                 	/* DFPU协处理器，仅限单精度*/
#define XCHAL_HAVE_DFPU_SINGLE_DOUBLE  0               	/* DFPU协处理器，单精度和双精度*/
#define XCHAL_HAVE_VECTRA1		0	/* Vectra I软件包*/
#define XCHAL_HAVE_VECTRALX		0	/* Vectra LX软件包*/
#define XCHAL_HAVE_PDX4		        0	/* PDX4 */
#define XCHAL_HAVE_CONNXD2		0	/* ConnX D2软件包*/
#define XCHAL_HAVE_CONNXD2_DUALLSFLIX   0	/* ConnX D2和双LoadStore Flix*/
#define XCHAL_HAVE_BBE16		0	/* ConnX BBE16软件包*/
#define XCHAL_HAVE_BBE16_RSQRT		0	/* BBE16矢量接收sqrt（&V）*/
#define XCHAL_HAVE_BBE16_VECDIV		0	/* BBE16矢量除法（&V）*/
#define XCHAL_HAVE_BBE16_DESPREAD	0	/* BBE16和解扩*/
#define XCHAL_HAVE_BBENEP		0	/* 连接BBENEP包*/
#define XCHAL_HAVE_BSP3			0	/* ConnX BSP3软件包*/
#define XCHAL_HAVE_BSP3_TRANSPOSE	0	/* BSP3和转置32x32*/
#define XCHAL_HAVE_SSP16		0	/* ConnX SSP16软件包*/
#define XCHAL_HAVE_SSP16_VITERBI	0	/* SSP16维特比（&V）*/
#define XCHAL_HAVE_TURBO16		0	/* ConnX Turbo16千克*/
#define XCHAL_HAVE_BBP16		0	/* ConnX BBP16软件包*/
#define XCHAL_HAVE_FLIX3		0	/* 基本三向FLIX选项*/
#define XCHAL_HAVE_GRIVPEP              0   /*  GRIVPEP是IVPEP的通用版本*/
#define XCHAL_HAVE_GRIVPEP_HISTOGRAM    0   /* GRIVPEP上的直方图选项*/


/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/

#define XCHAL_NUM_LOADSTORE_UNITS	1	/* 加载/存储单元*/
#define XCHAL_NUM_WRITEBUFFER_ENTRIES	4	/* 写入缓冲区大小*/
#define XCHAL_INST_FETCH_WIDTH		4	/* instr获取宽度（字节）*/
#define XCHAL_DATA_WIDTH		4	/* 数据宽度（字节）*/
#define XCHAL_DATA_PIPE_DELAY		2	/* d侧管道延迟（1=5级，2=7级）*/
#define XCHAL_CLOCK_GATING_GLOBAL	1	/* 全局时钟门控*/
#define XCHAL_CLOCK_GATING_FUNCUNIT	1	/* 函数。单位时钟门控*/
/*  在T1050中，适用于选定的核心加载和存储指令（参见ISA）：*/
#define XCHAL_UNALIGNED_LOAD_EXCEPTION	0	/* 未对齐的负载导致异常。*/
#define XCHAL_UNALIGNED_STORE_EXCEPTION	0	/* 未对齐的存储导致异常。*/
#define XCHAL_UNALIGNED_LOAD_HW		1	/* 未对齐的负载在硬件中工作*/
#define XCHAL_UNALIGNED_STORE_HW	1	/* 未对齐的存储在硬件中工作*/

#define XCHAL_SW_VERSION		1100003	/* 此标头的sw版本*/

#define XCHAL_CORE_ID			"esp32_v3_49_prod"	/* Xtensa处理器生成器中设置的字母数字核心名称（CoreID）*/

#define XCHAL_BUILD_UNIQUE_ID		0x0005FE96	/* 22位软件版本ID*/

/*
 *  这些定义描述了该软件的目标硬件。
 */
#define XCHAL_HW_CONFIGID0		0xC2BCFFFE	/* ConfigID高32位*/
#define XCHAL_HW_CONFIGID1		0x1CC5FE96	/* ConfigID低32位*/
#define XCHAL_HW_VERSION_NAME		"LX6.0.3"	/* 完整版本名称*/
#define XCHAL_HW_VERSION_MAJOR		2600	/* 目标硬件的主要版本号*/
#define XCHAL_HW_VERSION_MINOR		3	/* 目标硬件的次要版本号*/
#define XCHAL_HW_VERSION		260003	/* 大调*100+小调*/
#define XCHAL_HW_REL_LX6		1
#define XCHAL_HW_REL_LX6_0		1
#define XCHAL_HW_REL_LX6_0_3		1
#define XCHAL_HW_CONFIGID_RELIABLE	1
/*  如果软件以硬件版本的*范围*为目标，则以下为界限：*/
#define XCHAL_HW_MIN_VERSION_MAJOR	2600	/* 最早tgt硬件的主要v*/
#define XCHAL_HW_MIN_VERSION_MINOR	3	/* 最早tgt hw的小调v*/
#define XCHAL_HW_MIN_VERSION		260003	/* 最早的目标硬件*/
#define XCHAL_HW_MAX_VERSION_MAJOR	2600	/* 最新tgt硬件的主要版本*/
#define XCHAL_HW_MAX_VERSION_MINOR	3	/* 最新tgt硬件的次要版本*/
#define XCHAL_HW_MAX_VERSION		260003	/* 最新目标硬件*/


/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#define XCHAL_ICACHE_LINESIZE		4	/* I缓存行大小（字节）*/
#define XCHAL_DCACHE_LINESIZE		4	/* D缓存行大小（字节）*/
#define XCHAL_ICACHE_LINEWIDTH		2	/* log2（I行大小，字节）*/
#define XCHAL_DCACHE_LINEWIDTH		2	/* log2（D行大小，字节）*/

#define XCHAL_ICACHE_SIZE		0	/* I缓存大小（字节或0）*/
#define XCHAL_DCACHE_SIZE		0	/* D缓存大小（字节或0）*/

#define XCHAL_DCACHE_IS_WRITEBACK	0	/* 回写功能*/
#define XCHAL_DCACHE_IS_COHERENT	0	/* MP一致性特征*/

#define XCHAL_HAVE_PREFETCH		0	/* PREFCTL寄存器*/
#define XCHAL_HAVE_PREFETCH_L1		0	/* 预取到L1 dcache*/
#define XCHAL_PREFETCH_CASTOUT_LINES	0	/* dcache首选。castout bufsz*/
#define XCHAL_PREFETCH_ENTRIES		0	/* 缓存预取条目*/
#define XCHAL_PREFETCH_BLOCK_ENTRIES	0	/* 预取块流*/
#define XCHAL_HAVE_CACHE_BLOCKOPS	0	/* 缓存的块预取*/
#define XCHAL_HAVE_ICACHE_TEST		0	/* Icache测试说明*/
#define XCHAL_HAVE_DCACHE_TEST		0	/* Dcache测试说明*/
#define XCHAL_HAVE_ICACHE_DYN_WAYS	0	/* Icache动态方式支持*/
#define XCHAL_HAVE_DCACHE_DYN_WAYS	0	/* Dcache动态方式支持*/




/****************************************************************************
    对PRIVILEGED（监控或非虚拟化）代码有用的参数
 ****************************************************************************/


#ifndef XTENSA_HAL_NON_PRIVILEGED_ONLY

/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#define XCHAL_HAVE_PIF			1	/* 存在任何出站PIF*/
#define XCHAL_HAVE_AXI			0	/* AXI总线*/

#define XCHAL_HAVE_PIF_WR_RESP			0	/* pif写入响应*/
#define XCHAL_HAVE_PIF_REQ_ATTR			0	/* pif属性*/

/*  如果存在，缓存大小（字节）==（方式*2^（线宽+设置宽度））。*/

/*  log2中的缓存集数（每路行数）：*/
#define XCHAL_ICACHE_SETWIDTH		0
#define XCHAL_DCACHE_SETWIDTH		0

/*  缓存集关联性（方式数）：*/
#define XCHAL_ICACHE_WAYS		1
#define XCHAL_DCACHE_WAYS		1

/*  缓存功能：*/
#define XCHAL_ICACHE_LINE_LOCKABLE	0
#define XCHAL_DCACHE_LINE_LOCKABLE	0
#define XCHAL_ICACHE_ECC_PARITY		0
#define XCHAL_DCACHE_ECC_PARITY		0

/*  以字节为单位的缓存访问大小（影响SICW指令的操作）：*/
#define XCHAL_ICACHE_ACCESS_SIZE	1
#define XCHAL_DCACHE_ACCESS_SIZE	1

#define XCHAL_DCACHE_BANKS		0	/* 银行数量*/

/*  编码缓存属性位的数量（有关解码位，请参见<xtensa/hal.h>）：*/
#define XCHAL_CA_BITS			4


/*----------------------------------------------------------------------
内部I/O RAM/ROM和XLMI
  ----------------------------------------------------------------------*/

#define XCHAL_NUM_INSTROM		1	/* 核心指令ROM的数量*/
#define XCHAL_NUM_INSTRAM		2	/* 核心指令RAM的数量*/
#define XCHAL_NUM_DATAROM		1	/* 核心数据ROM的数量*/
#define XCHAL_NUM_DATARAM		2	/* 核心数据RAM的数量*/
#define XCHAL_NUM_URAM			0	/* 核心统一RAM的数量*/
#define XCHAL_NUM_XLMI			1	/* 核心XLMI端口数*/

/*  指令ROM 0：*/
#define XCHAL_INSTROM0_VADDR		0x40800000	/* 虚拟地址*/
#define XCHAL_INSTROM0_PADDR		0x40800000	/* 物理地址*/
#define XCHAL_INSTROM0_SIZE		4194304	/* 大小（字节）*/
#define XCHAL_INSTROM0_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/

/*  指令RAM 0：*/
#define XCHAL_INSTRAM0_VADDR		0x40000000	/* 虚拟地址*/
#define XCHAL_INSTRAM0_PADDR		0x40000000	/* 物理地址*/
#define XCHAL_INSTRAM0_SIZE		4194304	/* 大小（字节）*/
#define XCHAL_INSTRAM0_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/

/*  指令RAM 1：*/
#define XCHAL_INSTRAM1_VADDR		0x40400000	/* 虚拟地址*/
#define XCHAL_INSTRAM1_PADDR		0x40400000	/* 物理地址*/
#define XCHAL_INSTRAM1_SIZE		4194304	/* 大小（字节）*/
#define XCHAL_INSTRAM1_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/

/*  数据ROM 0：*/
#define XCHAL_DATAROM0_VADDR		0x3F400000	/* 虚拟地址*/
#define XCHAL_DATAROM0_PADDR		0x3F400000	/* 物理地址*/
#define XCHAL_DATAROM0_SIZE		4194304	/* 大小（字节）*/
#define XCHAL_DATAROM0_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/
#define XCHAL_DATAROM0_BANKS		1	/* 银行数量*/

/*  数据RAM 0：*/
#define XCHAL_DATARAM0_VADDR		0x3FF80000	/* 虚拟地址*/
#define XCHAL_DATARAM0_PADDR		0x3FF80000	/* 物理地址*/
#define XCHAL_DATARAM0_SIZE		524288	/* 大小（字节）*/
#define XCHAL_DATARAM0_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/
#define XCHAL_DATARAM0_BANKS		1	/* 银行数量*/

/*  数据RAM 1：*/
#define XCHAL_DATARAM1_VADDR		0x3F800000	/* 虚拟地址*/
#define XCHAL_DATARAM1_PADDR		0x3F800000	/* 物理地址*/
#define XCHAL_DATARAM1_SIZE		4194304	/* 大小（字节）*/
#define XCHAL_DATARAM1_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/
#define XCHAL_DATARAM1_BANKS		1	/* 银行数量*/

/*  XLMI端口0：*/
#define XCHAL_XLMI0_VADDR		0x3FF00000	/* 虚拟地址*/
#define XCHAL_XLMI0_PADDR		0x3FF00000	/* 物理地址*/
#define XCHAL_XLMI0_SIZE		524288	/* 大小（字节）*/
#define XCHAL_XLMI0_ECC_PARITY	0	/* ECC/奇偶校验类型，0=无*/

#define XCHAL_HAVE_IMEM_LOADSTORE	1	/* 可以加载/存储到IRAM/IRAM*/


/*----------------------------------------------------------------------
中断和计时器
  ----------------------------------------------------------------------*/

#define XCHAL_HAVE_INTERRUPTS		1	/* 中断选项*/
#define XCHAL_HAVE_HIGHPRI_INTERRUPTS	1	/* 中等/高优先级。中断*/
#define XCHAL_HAVE_NMI			1	/* 不可屏蔽中断*/
#define XCHAL_HAVE_CCOUNT		1	/* CCOUNT寄存器（计时器选项）*/
#define XCHAL_NUM_TIMERS		3	/* CCOMPAREn寄存器数*/
#define XCHAL_NUM_INTERRUPTS		32	/* 中断次数*/
#define XCHAL_NUM_INTERRUPTS_LOG2	5	/* ceil（log2（NUM_INTERRUPTS））*/
#define XCHAL_NUM_EXTINTERRUPTS		26	/* 外部中断数*/
#define XCHAL_NUM_INTLEVELS		6	/* 中断级别数（不包括零级）*/
#define XCHAL_EXCM_LEVEL		3	/* PS.EXCM屏蔽的级别*/
	/* （XEA1中始终为1；2..EXCM_LEVEL级别为“中等优先级”）*/

/*  每个中断级别的中断掩码：*/
#define XCHAL_INTLEVEL1_MASK		0x000637FF
#define XCHAL_INTLEVEL2_MASK		0x00380000
#define XCHAL_INTLEVEL3_MASK		0x28C08800
#define XCHAL_INTLEVEL4_MASK		0x53000000
#define XCHAL_INTLEVEL5_MASK		0x84010000
#define XCHAL_INTLEVEL6_MASK		0x00000000
#define XCHAL_INTLEVEL7_MASK		0x00004000

/*  中断级别的每个1..n范围内的中断掩码：*/
#define XCHAL_INTLEVEL1_ANDBELOW_MASK	0x000637FF
#define XCHAL_INTLEVEL2_ANDBELOW_MASK	0x003E37FF
#define XCHAL_INTLEVEL3_ANDBELOW_MASK	0x28FEBFFF
#define XCHAL_INTLEVEL4_ANDBELOW_MASK	0x7BFEBFFF
#define XCHAL_INTLEVEL5_ANDBELOW_MASK	0xFFFFBFFF
#define XCHAL_INTLEVEL6_ANDBELOW_MASK	0xFFFFBFFF
#define XCHAL_INTLEVEL7_ANDBELOW_MASK	0xFFFFFFFF

/*  每个中断的级别：*/
#define XCHAL_INT0_LEVEL		1
#define XCHAL_INT1_LEVEL		1
#define XCHAL_INT2_LEVEL		1
#define XCHAL_INT3_LEVEL		1
#define XCHAL_INT4_LEVEL		1
#define XCHAL_INT5_LEVEL		1
#define XCHAL_INT6_LEVEL		1
#define XCHAL_INT7_LEVEL		1
#define XCHAL_INT8_LEVEL		1
#define XCHAL_INT9_LEVEL		1
#define XCHAL_INT10_LEVEL		1
#define XCHAL_INT11_LEVEL		3
#define XCHAL_INT12_LEVEL		1
#define XCHAL_INT13_LEVEL		1
#define XCHAL_INT14_LEVEL		7
#define XCHAL_INT15_LEVEL		3
#define XCHAL_INT16_LEVEL		5
#define XCHAL_INT17_LEVEL		1
#define XCHAL_INT18_LEVEL		1
#define XCHAL_INT19_LEVEL		2
#define XCHAL_INT20_LEVEL		2
#define XCHAL_INT21_LEVEL		2
#define XCHAL_INT22_LEVEL		3
#define XCHAL_INT23_LEVEL		3
#define XCHAL_INT24_LEVEL		4
#define XCHAL_INT25_LEVEL		4
#define XCHAL_INT26_LEVEL		5
#define XCHAL_INT27_LEVEL		3
#define XCHAL_INT28_LEVEL		4
#define XCHAL_INT29_LEVEL		3
#define XCHAL_INT30_LEVEL		4
#define XCHAL_INT31_LEVEL		5
#define XCHAL_DEBUGLEVEL		6	/* 调试中断级别*/
#define XCHAL_HAVE_DEBUG_EXTERN_INT	1	/* OCD外部数据库中断*/
#define XCHAL_NMILEVEL			7	/* NMI“级别”（用于EXCSAVE/EPS/EPC_n、RFI n）*/

/*  每个中断的类型：*/
#define XCHAL_INT0_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT1_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT2_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT3_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT4_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT5_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT6_TYPE 	XTHAL_INTTYPE_TIMER
#define XCHAL_INT7_TYPE 	XTHAL_INTTYPE_SOFTWARE
#define XCHAL_INT8_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT9_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT10_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#define XCHAL_INT11_TYPE 	XTHAL_INTTYPE_PROFILING
#define XCHAL_INT12_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT13_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT14_TYPE 	XTHAL_INTTYPE_NMI
#define XCHAL_INT15_TYPE 	XTHAL_INTTYPE_TIMER
#define XCHAL_INT16_TYPE 	XTHAL_INTTYPE_TIMER
#define XCHAL_INT17_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT18_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT19_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT20_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT21_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT22_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#define XCHAL_INT23_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT24_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT25_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT26_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT27_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#define XCHAL_INT28_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#define XCHAL_INT29_TYPE 	XTHAL_INTTYPE_SOFTWARE
#define XCHAL_INT30_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#define XCHAL_INT31_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL

/*  每种中断类型的中断掩码：*/
#define XCHAL_INTTYPE_MASK_UNCONFIGURED	0x00000000
#define XCHAL_INTTYPE_MASK_SOFTWARE	0x20000080
#define XCHAL_INTTYPE_MASK_EXTERN_EDGE	0x50400400
#define XCHAL_INTTYPE_MASK_EXTERN_LEVEL	0x8FBE333F
#define XCHAL_INTTYPE_MASK_TIMER	0x00018040
#define XCHAL_INTTYPE_MASK_NMI		0x00004000
#define XCHAL_INTTYPE_MASK_WRITE_ERROR	0x00000000
#define XCHAL_INTTYPE_MASK_PROFILING	0x00000800

/*  分配给特定中断源的中断编号：*/
#define XCHAL_TIMER0_INTERRUPT		6	/* CCOMPARE0 */
#define XCHAL_TIMER1_INTERRUPT		15	/* CCOMPARE1 */
#define XCHAL_TIMER2_INTERRUPT		16	/* CCOMPARE2 */
#define XCHAL_TIMER3_INTERRUPT		XTHAL_TIMER_UNCONFIGURED
#define XCHAL_NMI_INTERRUPT		14	/* 不可屏蔽中断*/
#define XCHAL_PROFILING_INTERRUPT	11	/* 剖析中断*/

/*  仅配置一个中断的级别的中断编号：*/
#define XCHAL_INTLEVEL7_NUM		14
/*  （在1、2、3、4、5级有许多中断。）*/


/*
 *  外部中断映射。这些宏描述了Xtensa处理器中断号（内部编号，如interrupt和INTENABLE寄存器）如何映射到外部BInterrupt＜n＞引脚，用于配置为外部（电平触发、边缘触发或NMI）的中断。有关详细信息，请参阅Xtensa处理器数据手册。
 */

/*  映射到每个EXTERNAL BIInterrupt引脚号的核心中断号：*/
#define XCHAL_EXTINT0_NUM		0	/* （内部级别1）*/
#define XCHAL_EXTINT1_NUM		1	/* （内部级别1）*/
#define XCHAL_EXTINT2_NUM		2	/* （内部级别1）*/
#define XCHAL_EXTINT3_NUM		3	/* （内部级别1）*/
#define XCHAL_EXTINT4_NUM		4	/* （内部级别1）*/
#define XCHAL_EXTINT5_NUM		5	/* （内部级别1）*/
#define XCHAL_EXTINT6_NUM		8	/* （内部级别1）*/
#define XCHAL_EXTINT7_NUM		9	/* （内部级别1）*/
#define XCHAL_EXTINT8_NUM		10	/* （内部级别1）*/
#define XCHAL_EXTINT9_NUM		12	/* （内部级别1）*/
#define XCHAL_EXTINT10_NUM		13	/* （内部级别1）*/
#define XCHAL_EXTINT11_NUM		14	/* （内部级别7）*/
#define XCHAL_EXTINT12_NUM		17	/* （内部级别1）*/
#define XCHAL_EXTINT13_NUM		18	/* （内部级别1）*/
#define XCHAL_EXTINT14_NUM		19	/* （内部级别2）*/
#define XCHAL_EXTINT15_NUM		20	/* （内部级别2）*/
#define XCHAL_EXTINT16_NUM		21	/* （内部级别2）*/
#define XCHAL_EXTINT17_NUM		22	/* （内部级别3）*/
#define XCHAL_EXTINT18_NUM		23	/* （内部级别3）*/
#define XCHAL_EXTINT19_NUM		24	/* （内部级别4）*/
#define XCHAL_EXTINT20_NUM		25	/* （内部级别4）*/
#define XCHAL_EXTINT21_NUM		26	/* （内部级别5）*/
#define XCHAL_EXTINT22_NUM		27	/* （内部级别3）*/
#define XCHAL_EXTINT23_NUM		28	/* （内部级别4）*/
#define XCHAL_EXTINT24_NUM		30	/* （内部级别4）*/
#define XCHAL_EXTINT25_NUM		31	/* （内部级别5）*/
/*  外部B映射到每个核心中断号的中断引脚号：*/
#define XCHAL_INT0_EXTNUM		0	/* （内部级别1）*/
#define XCHAL_INT1_EXTNUM		1	/* （内部级别1）*/
#define XCHAL_INT2_EXTNUM		2	/* （内部级别1）*/
#define XCHAL_INT3_EXTNUM		3	/* （内部级别1）*/
#define XCHAL_INT4_EXTNUM		4	/* （内部级别1）*/
#define XCHAL_INT5_EXTNUM		5	/* （内部级别1）*/
#define XCHAL_INT8_EXTNUM		6	/* （内部级别1）*/
#define XCHAL_INT9_EXTNUM		7	/* （内部级别1）*/
#define XCHAL_INT10_EXTNUM		8	/* （内部级别1）*/
#define XCHAL_INT12_EXTNUM		9	/* （内部级别1）*/
#define XCHAL_INT13_EXTNUM		10	/* （内部级别1）*/
#define XCHAL_INT14_EXTNUM		11	/* （内部级别7）*/
#define XCHAL_INT17_EXTNUM		12	/* （内部级别1）*/
#define XCHAL_INT18_EXTNUM		13	/* （内部级别1）*/
#define XCHAL_INT19_EXTNUM		14	/* （内部级别2）*/
#define XCHAL_INT20_EXTNUM		15	/* （内部级别2）*/
#define XCHAL_INT21_EXTNUM		16	/* （内部级别2）*/
#define XCHAL_INT22_EXTNUM		17	/* （内部级别3）*/
#define XCHAL_INT23_EXTNUM		18	/* （内部级别3）*/
#define XCHAL_INT24_EXTNUM		19	/* （内部级别4）*/
#define XCHAL_INT25_EXTNUM		20	/* （内部级别4）*/
#define XCHAL_INT26_EXTNUM		21	/* （内部级别5）*/
#define XCHAL_INT27_EXTNUM		22	/* （内部级别3）*/
#define XCHAL_INT28_EXTNUM		23	/* （内部级别4）*/
#define XCHAL_INT30_EXTNUM		24	/* （内部级别4）*/
#define XCHAL_INT31_EXTNUM		25	/* （内部级别5）*/


/*----------------------------------------------------------------------
例外和向量
  ----------------------------------------------------------------------*/

#define XCHAL_XEA_VERSION		2	/* Xtensa异常体系结构编号：1==XEA1（旧）2==XEA2（新）0==XEAX（外部）或TX*/
#define XCHAL_HAVE_XEA1			0	/* 异常体系结构1*/
#define XCHAL_HAVE_XEA2			1	/* 异常体系结构2*/
#define XCHAL_HAVE_XEAX			0	/* 外部异常架构。*/
#define XCHAL_HAVE_EXCEPTIONS		1	/* 异常选项*/
#define XCHAL_HAVE_HALT			0	/* 停止体系结构选项*/
#define XCHAL_HAVE_BOOTLOADER		0	/* 引导加载程序（用于TX）*/
#define XCHAL_HAVE_MEM_ECC_PARITY	0	/* 本地存储器ECC/奇偶校验*/
#define XCHAL_HAVE_VECTOR_SELECT	1	/* 可重定位向量*/
#define XCHAL_HAVE_VECBASE		1	/* 可重定位向量*/
#define XCHAL_VECBASE_RESET_VADDR	0x40000000  /* VECBASE重置值*/
#define XCHAL_VECBASE_RESET_PADDR	0x40000000
#define XCHAL_RESET_VECBASE_OVERLAP	0

#define XCHAL_RESET_VECTOR0_VADDR	0x50000000
#define XCHAL_RESET_VECTOR0_PADDR	0x50000000
#define XCHAL_RESET_VECTOR1_VADDR	0x40000400
#define XCHAL_RESET_VECTOR1_PADDR	0x40000400
#define XCHAL_RESET_VECTOR_VADDR	0x40000400
#define XCHAL_RESET_VECTOR_PADDR	0x40000400
#define XCHAL_USER_VECOFS		0x00000340
#define XCHAL_USER_VECTOR_VADDR		0x40000340
#define XCHAL_USER_VECTOR_PADDR		0x40000340
#define XCHAL_KERNEL_VECOFS		0x00000300
#define XCHAL_KERNEL_VECTOR_VADDR	0x40000300
#define XCHAL_KERNEL_VECTOR_PADDR	0x40000300
#define XCHAL_DOUBLEEXC_VECOFS		0x000003C0
#define XCHAL_DOUBLEEXC_VECTOR_VADDR	0x400003C0
#define XCHAL_DOUBLEEXC_VECTOR_PADDR	0x400003C0
#define XCHAL_WINDOW_OF4_VECOFS		0x00000000
#define XCHAL_WINDOW_UF4_VECOFS		0x00000040
#define XCHAL_WINDOW_OF8_VECOFS		0x00000080
#define XCHAL_WINDOW_UF8_VECOFS		0x000000C0
#define XCHAL_WINDOW_OF12_VECOFS	0x00000100
#define XCHAL_WINDOW_UF12_VECOFS	0x00000140
#define XCHAL_WINDOW_VECTORS_VADDR	0x40000000
#define XCHAL_WINDOW_VECTORS_PADDR	0x40000000
#define XCHAL_INTLEVEL2_VECOFS		0x00000180
#define XCHAL_INTLEVEL2_VECTOR_VADDR	0x40000180
#define XCHAL_INTLEVEL2_VECTOR_PADDR	0x40000180
#define XCHAL_INTLEVEL3_VECOFS		0x000001C0
#define XCHAL_INTLEVEL3_VECTOR_VADDR	0x400001C0
#define XCHAL_INTLEVEL3_VECTOR_PADDR	0x400001C0
#define XCHAL_INTLEVEL4_VECOFS		0x00000200
#define XCHAL_INTLEVEL4_VECTOR_VADDR	0x40000200
#define XCHAL_INTLEVEL4_VECTOR_PADDR	0x40000200
#define XCHAL_INTLEVEL5_VECOFS		0x00000240
#define XCHAL_INTLEVEL5_VECTOR_VADDR	0x40000240
#define XCHAL_INTLEVEL5_VECTOR_PADDR	0x40000240
#define XCHAL_INTLEVEL6_VECOFS		0x00000280
#define XCHAL_INTLEVEL6_VECTOR_VADDR	0x40000280
#define XCHAL_INTLEVEL6_VECTOR_PADDR	0x40000280
#define XCHAL_DEBUG_VECOFS		XCHAL_INTLEVEL6_VECOFS
#define XCHAL_DEBUG_VECTOR_VADDR	XCHAL_INTLEVEL6_VECTOR_VADDR
#define XCHAL_DEBUG_VECTOR_PADDR	XCHAL_INTLEVEL6_VECTOR_PADDR
#define XCHAL_NMI_VECOFS		0x000002C0
#define XCHAL_NMI_VECTOR_VADDR		0x400002C0
#define XCHAL_NMI_VECTOR_PADDR		0x400002C0
#define XCHAL_INTLEVEL7_VECOFS		XCHAL_NMI_VECOFS
#define XCHAL_INTLEVEL7_VECTOR_VADDR	XCHAL_NMI_VECTOR_VADDR
#define XCHAL_INTLEVEL7_VECTOR_PADDR	XCHAL_NMI_VECTOR_PADDR


/*----------------------------------------------------------------------
				DEBUG MODULE
  ----------------------------------------------------------------------*/

/*  其他*/
#define XCHAL_HAVE_DEBUG_ERI		1	/* ERI到调试模块*/
#define XCHAL_HAVE_DEBUG_APB		1	/* APB到调试模块*/
#define XCHAL_HAVE_DEBUG_JTAG		1	/* JTAG到调试模块*/

/*  片上调试（OCD）*/
#define XCHAL_HAVE_OCD			1	/* OnChipDebug选项*/
#define XCHAL_NUM_IBREAK		2	/* IBREAKn寄存器数*/
#define XCHAL_NUM_DBREAK		2	/* DBREAKn规则数*/
#define XCHAL_HAVE_OCD_DIR_ARRAY	0	/* 更快的OCD选项（至LX4）*/
#define XCHAL_HAVE_OCD_LS32DDR		1	/* L32DDR/S32DR（更快的OCD）*/

/*  TRAX（核心）*/
#define XCHAL_HAVE_TRAX			1	/* 调试模块中的TRAX*/
#define XCHAL_TRAX_MEM_SIZE		16384	/* TRAX内存大小（字节）*/
#define XCHAL_TRAX_MEM_SHAREABLE	1	/* 开始/结束规则；就绪信号。*/
#define XCHAL_TRAX_ATB_WIDTH		32	/* ATB宽度（位），0=无ATB*/
#define XCHAL_TRAX_TIME_WIDTH		0	/* 时间戳位宽，0=无*/

/*  性能计数器*/
#define XCHAL_NUM_PERF_COUNTERS		2	/* 性能计数器*/


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*  参见核心matmap。h头文件获取更多详细信息。*/

#define XCHAL_HAVE_TLBS			1	/* HAVE_CACHEATTR的倒数*/
#define XCHAL_HAVE_SPANNING_WAY		1	/* 单向映射I+D 4GB vaddr*/
#define XCHAL_SPANNING_WAY		0	/* TLB跨越方式编号*/
#define XCHAL_HAVE_IDENTITY_MAP		1	/* vaddr==始终填充*/
#define XCHAL_HAVE_CACHEATTR		0	/* CACHEATTR寄存器存在*/
#define XCHAL_HAVE_MIMIC_CACHEATTR	1	/* 区域保护*/
#define XCHAL_HAVE_XLT_CACHEATTR	0	/* 区域保护。w/翻译*/
#define XCHAL_HAVE_PTP_MMU		0	/* 可用于基于MMU的操作系统的完整MMU（具有页表[autorefill]和保护）*/
/*  如果没有设置上述最后4项，则为自定义TLB配置。*/

#define XCHAL_MMU_ASID_BITS		0	/* ASID中的位数*/
#define XCHAL_MMU_RINGS			1	/* 环数（1..4）*/
#define XCHAL_MMU_RING_BITS		0	/* RING字段中的位数*/

#endif /* !XTENSA_HAL_NON_PRIVILEGED_ONLY */


#endif /* _XTENSA_CORE_CONFIGURATION_H */

