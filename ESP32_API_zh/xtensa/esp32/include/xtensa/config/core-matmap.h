/*
 * extensa/config/core matmap。h——Xtensa处理器核心配置的内存访问和转换映射参数（CHAL）。
 *
 *  如果您使用的是Xtensa工具，请参阅<Xtensa/config/core。h> （包括此文件）以了解更多详细信息。
 *
 *  在迄今发布的Xtensa处理器产品中，本文件中定义的所有参数都可以从核心isa中包含的信息中导出（至少在理论上）。h头文件。特别是，以下核心配置参数是相关的：XCHAL_HAVE_CACHEATTR XCHAL_HAVE_MIMIC_CHATTER XCHAL-HAVE_XLT_CACHEATTR XCHAL_HVEE_TP_MMU XCHAL_ITLB_ARF_ENTRIES_LOG2 XCHAL_DTLB_ARR_ENTRIES.LOG2 XCHAR_DCACHE_IS_WRITEBACK XCHAL_ICACHE_SIZE（存在I-cache）XCHAL_DCACHE_SSIZE（存在D-缓存）XCHAL_HW_VERSION_MAJOR XCHAL_HW/VERSION_MINOR
 */

/* 客户ID=11657；内部版本=0x5fe96；版权所有（c）1999-2016 Tensilica Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */


#ifndef XTENSA_CONFIG_CORE_MATMAP_H
#define XTENSA_CONFIG_CORE_MATMAP_H


/*----------------------------------------------------------------------
			CACHE (MEMORY ACCESS) ATTRIBUTES
  ----------------------------------------------------------------------*/


/*  缓存属性编码--每个缓存属性的访问模式列表：*/
#define XCHAL_FCA_LIST		XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_BYPASS	XCHAL_SEP \
				XTHAL_FAM_BYPASS	XCHAL_SEP \
				XTHAL_FAM_BYPASS	XCHAL_SEP \
				XTHAL_FAM_BYPASS	XCHAL_SEP \
				XTHAL_FAM_BYPASS	XCHAL_SEP \
				XTHAL_FAM_BYPASS	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION	XCHAL_SEP \
				XTHAL_FAM_EXCEPTION
#define XCHAL_LCA_LIST		XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION	XCHAL_SEP \
				XTHAL_LAM_BYPASSG	XCHAL_SEP \
				XTHAL_LAM_EXCEPTION
#define XCHAL_SCA_LIST		XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION	XCHAL_SEP \
				XTHAL_SAM_BYPASS	XCHAL_SEP \
				XTHAL_SAM_EXCEPTION


/*
 *  一般感兴趣的特定编码缓存属性值。如果特定的缓存模式不可用，则返回最接近的可用模式（例如，写通过而不是写回，旁路而不是写通过）。
 */
#define XCHAL_CA_BYPASS  		2	/* 缓存禁用（绕过）模式*/
#define XCHAL_CA_BYPASSBUF  		6	/* 缓存禁用（绕过）缓冲模式*/
#define XCHAL_CA_WRITETHRU		2	/* 缓存启用（写入）模式*/
#define XCHAL_CA_WRITEBACK		2	/* 缓存启用（写回）模式*/
#define XCHAL_HAVE_CA_WRITEBACK_NOALLOC	0	/* 写回无分配可用性*/
#define XCHAL_CA_WRITEBACK_NOALLOC	2	/* 缓存启用（写回无分配）模式*/
#define XCHAL_CA_BYPASS_RW  		0	/* 缓存禁用（绕过）模式（无执行）*/
#define XCHAL_CA_WRITETHRU_RW		0	/* 缓存启用（写入）模式（无exec）*/
#define XCHAL_CA_WRITEBACK_RW		0	/* 缓存启用（回写）模式（无执行）*/
#define XCHAL_CA_WRITEBACK_NOALLOC_RW	0	/* 缓存启用（写回无分配）模式（无执行）*/
#define XCHAL_CA_ILLEGAL		15	/* 不允许访问（所有原因异常）模式*/
#define XCHAL_CA_ISOLATE		0	/* 缓存隔离（访问到缓存而不是内存）模式*/


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*
 *  MMU参数的一般说明。
 *
 *  术语：ASID=地址空间ID（充当虚拟地址的“扩展”）VPN=虚拟页面编号PPN=物理页面编号CA=编码缓存属性（访问模式）TLB=翻译后备缓冲区（此处术语有所扩展）I=指令（提取访问）D=数据（加载和存储访问）方式=每个TLB（ITLB和DTLB）由多个同时匹配访问的虚拟地址；如果恰好一种方式与vaddr匹配，则TLB成功地转换虚拟地址；如果没有匹配，那就是错过；如果多次匹配，则会出现“多次命中”异常；每种方式都可以根据条目数量、页面大小、哪些字段是可写的或常量等独立配置。set＝具有完全相同参数的一组连续方式ARF＝自动填充；硬件通过从页表加载PTE并以自动重新填充方式之一存储PTE来服务第一级未命中；如果此PTE加载也未命中，则会为s/w发布未命中异常。最小连线=“最小连线”方式可用于在程序控制下任意映射单个（最小大小）页面；它只有一个条目，是非自动填充的（某些其他方式必须是自动填充的），它的所有字段（VPN、PPN、ASID、CA）都是可写的，并且它支持XCHAL_MMU_MIN_PTE_PAGE_SIZE页面大小（当前的限制是这是它支持的唯一页面大小）。
 *
 *  TLB方式条目被虚拟索引。支持多种页面大小的TLB方式：
 *	- 必须具有所有可写的VPN和PPN字段；
 *	- 在任何给定时间只能使用一个页面大小（例如，启动时设置），由相应的ITLBCFG或DTLBCFG特殊寄存器选择，其位n4+3..n4索引路径n的页面大小列表（XCHAL_xTLB_SETm_PAGESZ_LOG2_list对应于路径n的集合m）；该列表对于自动重新填充方式可能是稀疏的，因为自动重新填充方法具有与PTE条目共享公共编码的受支持页面大小的独立列表；编码是该列表的索引；列表中给定方式的不支持大小为零；选择不支持的大小会导致未定义的硬件行为；
 *	- 仅适用于通道0至7（由于ITLBCFG/DTLBCFG定义）。
 */

#define XCHAL_MMU_ASID_INVALID		0	/* 指示无效地址空间的ASID值*/
#define XCHAL_MMU_ASID_KERNEL		0	/* 指示内核（环0）地址空间的ASID值*/
#define XCHAL_MMU_SR_BITS		0	/* 支持的大小限制位数*/
#define XCHAL_MMU_CA_BITS		4	/* 保存缓存属性编码所需的位数*/
#define XCHAL_MMU_MAX_PTE_PAGE_SIZE	29	/* PTE结构中的最大页面大小（log2）*/
#define XCHAL_MMU_MIN_PTE_PAGE_SIZE	29	/* PTE结构中的最小页面大小（log2）*/


/***指令TLB：***/

#define XCHAL_ITLB_WAY_BITS		0	/* 保持通道的位数*/
#define XCHAL_ITLB_WAYS			1	/* 路数（n路集合关联TLB）*/
#define XCHAL_ITLB_ARF_WAYS		0	/* 自动填充方式的数量*/
#define XCHAL_ITLB_SETS			1	/* 集合数（具有相同设置的方式组）*/

/*  每条路所属的路集：*/
#define XCHAL_ITLB_WAY0_SET		0

/*  硬件自动重新填充（ARF）使用的方式集：*/
#define XCHAL_ITLB_ARF_SETS		0	/* 自动加油装置的数量*/

/*  “最小布线”的路集（见上述术语注释）：*/
#define XCHAL_ITLB_MINWIRED_SETS	0	/* “最小接线”组数*/


/*  ITLB通道集0（通道组0到0）：*/
#define XCHAL_ITLB_SET0_WAY			0	/* 第一种方式的索引集*/
#define XCHAL_ITLB_SET0_WAYS			1	/* 此方式集中的（连续）方式数*/
#define XCHAL_ITLB_SET0_ENTRIES_LOG2		3	/* log2（这种方式的条目数）*/
#define XCHAL_ITLB_SET0_ENTRIES			8	/* 以这种方式输入的数量（总是2的幂）*/
#define XCHAL_ITLB_SET0_ARF			0	/* 1=h/w自动填充，0=非自动填充（有线/恒定/静态）*/
#define XCHAL_ITLB_SET0_PAGESIZES		1	/* 以这种方式支持的页面大小数*/
#define XCHAL_ITLB_SET0_PAGESZ_BITS		0	/* 编码页面大小的位数*/
#define XCHAL_ITLB_SET0_PAGESZ_LOG2_MIN		29	/* log2（支持的最小页面大小）*/
#define XCHAL_ITLB_SET0_PAGESZ_LOG2_MAX		29	/* log2（支持的最大页面大小）*/
#define XCHAL_ITLB_SET0_PAGESZ_LOG2_LIST	29	/* log2（页面大小）列表，由XCHAL_SEP分隔；列表中有2^PAGESZ_BITS项，不支持的项为零*/
#define XCHAL_ITLB_SET0_ASID_CONSTMASK		0	/* 恒定ASID位；0（如果全部可写）*/
#define XCHAL_ITLB_SET0_VPN_CONSTMASK		0x00000000	/* 恒定的VPN位，不包括入口索引位；0（如果全部可写）*/
#define XCHAL_ITLB_SET0_PPN_CONSTMASK		0xE0000000	/* 恒定PPN位，包括条目索引位；0（如果全部可写）*/
#define XCHAL_ITLB_SET0_CA_CONSTMASK		0	/* 恒定CA位；0（如果全部可写）*/
#define XCHAL_ITLB_SET0_ASID_RESET		0	/* 如果定义了ASID重置值（且所有值都可写），则为1；否则为0*/
#define XCHAL_ITLB_SET0_VPN_RESET		0	/* 如果定义了VPN重置值（且所有值都可写），则为1；否则为0*/
#define XCHAL_ITLB_SET0_PPN_RESET		0	/* 1，如果PPN重置值已定义（且全部可写）；否则为0*/
#define XCHAL_ITLB_SET0_CA_RESET		1	/* 1，如果定义了CA重置值（并且所有值都是可写的）；否则为0*/
/*  ITLB方式集0的每个条目的恒定VPN值（因为VPN_CONSTMASK为非零）：*/
#define XCHAL_ITLB_SET0_E0_VPN_CONST		0x00000000
#define XCHAL_ITLB_SET0_E1_VPN_CONST		0x20000000
#define XCHAL_ITLB_SET0_E2_VPN_CONST		0x40000000
#define XCHAL_ITLB_SET0_E3_VPN_CONST		0x60000000
#define XCHAL_ITLB_SET0_E4_VPN_CONST		0x80000000
#define XCHAL_ITLB_SET0_E5_VPN_CONST		0xA0000000
#define XCHAL_ITLB_SET0_E6_VPN_CONST		0xC0000000
#define XCHAL_ITLB_SET0_E7_VPN_CONST		0xE0000000
/*  ITLB方式集0的每个条目的恒定PPN值（因为PPN_CONSTMASK为非零）：*/
#define XCHAL_ITLB_SET0_E0_PPN_CONST		0x00000000
#define XCHAL_ITLB_SET0_E1_PPN_CONST		0x20000000
#define XCHAL_ITLB_SET0_E2_PPN_CONST		0x40000000
#define XCHAL_ITLB_SET0_E3_PPN_CONST		0x60000000
#define XCHAL_ITLB_SET0_E4_PPN_CONST		0x80000000
#define XCHAL_ITLB_SET0_E5_PPN_CONST		0xA0000000
#define XCHAL_ITLB_SET0_E6_PPN_CONST		0xC0000000
#define XCHAL_ITLB_SET0_E7_PPN_CONST		0xE0000000
/*  重置ITLB通道集0的每个条目的CA值（因为SET0_CA_Reset为非零）：*/
#define XCHAL_ITLB_SET0_E0_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E1_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E2_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E3_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E4_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E5_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E6_CA_RESET		0x02
#define XCHAL_ITLB_SET0_E7_CA_RESET		0x02


/***数据TLB：***/

#define XCHAL_DTLB_WAY_BITS		0	/* 保持通道的位数*/
#define XCHAL_DTLB_WAYS			1	/* 路数（n路集合关联TLB）*/
#define XCHAL_DTLB_ARF_WAYS		0	/* 自动填充方式的数量*/
#define XCHAL_DTLB_SETS			1	/* 集合数（具有相同设置的方式组）*/

/*  每条路所属的路集：*/
#define XCHAL_DTLB_WAY0_SET		0

/*  硬件自动重新填充（ARF）使用的方式集：*/
#define XCHAL_DTLB_ARF_SETS		0	/* 自动加油装置的数量*/

/*  “最小布线”的路集（见上述术语注释）：*/
#define XCHAL_DTLB_MINWIRED_SETS	0	/* “最小接线”组数*/


/*  DTLB通道集0（通道组0到0）：*/
#define XCHAL_DTLB_SET0_WAY			0	/* 第一种方式的索引集*/
#define XCHAL_DTLB_SET0_WAYS			1	/* 此方式集中的（连续）方式数*/
#define XCHAL_DTLB_SET0_ENTRIES_LOG2		3	/* log2（这种方式的条目数）*/
#define XCHAL_DTLB_SET0_ENTRIES			8	/* 以这种方式输入的数量（总是2的幂）*/
#define XCHAL_DTLB_SET0_ARF			0	/* 1=h/w自动填充，0=非自动填充（有线/恒定/静态）*/
#define XCHAL_DTLB_SET0_PAGESIZES		1	/* 以这种方式支持的页面大小数*/
#define XCHAL_DTLB_SET0_PAGESZ_BITS		0	/* 编码页面大小的位数*/
#define XCHAL_DTLB_SET0_PAGESZ_LOG2_MIN		29	/* log2（支持的最小页面大小）*/
#define XCHAL_DTLB_SET0_PAGESZ_LOG2_MAX		29	/* log2（支持的最大页面大小）*/
#define XCHAL_DTLB_SET0_PAGESZ_LOG2_LIST	29	/* log2（页面大小）列表，由XCHAL_SEP分隔；列表中有2^PAGESZ_BITS项，不支持的项为零*/
#define XCHAL_DTLB_SET0_ASID_CONSTMASK		0	/* 恒定ASID位；0（如果全部可写）*/
#define XCHAL_DTLB_SET0_VPN_CONSTMASK		0x00000000	/* 恒定的VPN位，不包括入口索引位；0（如果全部可写）*/
#define XCHAL_DTLB_SET0_PPN_CONSTMASK		0xE0000000	/* 恒定PPN位，包括条目索引位；0（如果全部可写）*/
#define XCHAL_DTLB_SET0_CA_CONSTMASK		0	/* 恒定CA位；0（如果全部可写）*/
#define XCHAL_DTLB_SET0_ASID_RESET		0	/* 如果定义了ASID重置值（且所有值都可写），则为1；否则为0*/
#define XCHAL_DTLB_SET0_VPN_RESET		0	/* 如果定义了VPN重置值（且所有值都可写），则为1；否则为0*/
#define XCHAL_DTLB_SET0_PPN_RESET		0	/* 1，如果PPN重置值已定义（且全部可写）；否则为0*/
#define XCHAL_DTLB_SET0_CA_RESET		1	/* 1，如果定义了CA重置值（并且所有值都是可写的）；否则为0*/
/*  DTLB方式集0的每个条目的恒定VPN值（因为VPN_CONSTMASK为非零）：*/
#define XCHAL_DTLB_SET0_E0_VPN_CONST		0x00000000
#define XCHAL_DTLB_SET0_E1_VPN_CONST		0x20000000
#define XCHAL_DTLB_SET0_E2_VPN_CONST		0x40000000
#define XCHAL_DTLB_SET0_E3_VPN_CONST		0x60000000
#define XCHAL_DTLB_SET0_E4_VPN_CONST		0x80000000
#define XCHAL_DTLB_SET0_E5_VPN_CONST		0xA0000000
#define XCHAL_DTLB_SET0_E6_VPN_CONST		0xC0000000
#define XCHAL_DTLB_SET0_E7_VPN_CONST		0xE0000000
/*  DTLB方式集0的每个条目的恒定PPN值（因为PPN_CONSTMASK为非零）：*/
#define XCHAL_DTLB_SET0_E0_PPN_CONST		0x00000000
#define XCHAL_DTLB_SET0_E1_PPN_CONST		0x20000000
#define XCHAL_DTLB_SET0_E2_PPN_CONST		0x40000000
#define XCHAL_DTLB_SET0_E3_PPN_CONST		0x60000000
#define XCHAL_DTLB_SET0_E4_PPN_CONST		0x80000000
#define XCHAL_DTLB_SET0_E5_PPN_CONST		0xA0000000
#define XCHAL_DTLB_SET0_E6_PPN_CONST		0xC0000000
#define XCHAL_DTLB_SET0_E7_PPN_CONST		0xE0000000
/*  重置DTLB方式集0的每个条目的CA值（因为SET0_CA_Reset为非零）：*/
#define XCHAL_DTLB_SET0_E0_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E1_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E2_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E3_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E4_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E5_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E6_CA_RESET		0x02
#define XCHAL_DTLB_SET0_E7_CA_RESET		0x02




#endif /*XTENSA_CONFIG_CORE_MATMAP_H*/

