/*
 * 扩展/缓存属性。h—取决于CORE配置的汇编程序特定CACHEATTR寄存器相关定义
 *
 *  该文件在逻辑上是xtensa/coreasm的一部分。h（或者可能是xtensa/cacheasm.h），但是为了模块化/编译性能而保持独立。
 */

/*
 * 版权所有（c）2001-2009 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTENSA_CACHEATTRASM_H
#define XTENSA_CACHEATTRASM_H

#include <xtensa/coreasm.h>

/*  确定是否使用八个512MB条目控制缓存属性：*/
#define XCHAL_CA_8X512	(XCHAL_HAVE_CACHEATTR || XCHAL_HAVE_MIMIC_CACHEATTR || XCHAL_HAVE_XLT_CACHEATTR \
	|| (XCHAL_HAVE_PTP_MMU && XCHAL_HAVE_SPANNING_WAY))


/*
 *  此头文件定义了以下形式的汇编程序宏：<x>cacheattr_<func>其中：<x>是“i”、“d”或不存在于指令、数据或两个缓存中；<func>表示宏的函数。
 *
 *  定义了以下功能：
 *
 *  icachettr_get将I-cache CACHEATTR读取到a2（clobbers a3-a5）。
 *
 *  dcacheattr_get将D缓存CACHEATTR读取到a2（clobbers a3-a5）。（注意：对于具有实际CACHEATTR寄存器的配置，上述两个宏是相同的。）
 *
 *  cacheattr_set从a2写入I缓存和D缓存cacheattr（a3-a8已清除）。即使在更改自己的代码属性时也有效。
 *
 *  如果I-cache似乎已启用（例如，如果CACHEATTR包含缓存启用属性），则icachertr_is_enabled label分支到\label。（clobbers a2-a5，SAR）
 *
 *  dcacheattr_is_enabled label如果D-缓存似乎已启用（例如，如果CACHEATTR包含缓存启用属性），则分支到\label。（clobbers a2-a5，SAR）
 *
 *  cacheattr_is_enabled label如果I-cache或D-cache似乎已启用（例如，如果cacheattr包含缓存启用属性），则分支到\label。（clobbers a2-a5，SAR）
 *
 *  以下宏仅在特定条件下定义：
 *
 *  icachetter_set（如果XCHAL_HAVE_MIMIC_CHATTER | | XCHAL_HAVE_XLT_CACHEATTR）从a2（a3-a8已清除）写入I-cache CACHEATT。
 *
 *  dcacheattr_set（如果XCHAL_HAVE_MIMIC_CACHHEATTR||XCHAL_HAVE_XLT_CACHEATTR）从a2写入D-缓存CACHEATTR（a3-a8已清除）。
 */



/***************************   GENERIC -- ALL CACHES   ***************************/

/*
 *  _缓存属性集
 *
 *  （内部宏。）返回a2中CACHEATTR寄存器的值（或最接近的等效值）。
 *
 *  入口：（无）出口：从CACHEATTR a3-a5读取的a2值（临时）
 */
	.macro	_cacheattr_get	tlb
#if XCHAL_HAVE_CACHEATTR
	rsr.cacheattr	a2
#elif XCHAL_CA_8X512
	//  我们有一个配置，使用简化的
	//  “MMU”由单个静态映射方式组成。
	//  DTLB和ITLB是独立的，因此没有单独的
	//  可以描述这两者的缓存属性。所以现在
	//  只需返回DTLB状态。
	movi	a5, 0xE0000000
	movi	a2, 0
	movi	a3, XCHAL_SPANNING_WAY
1:	add	a3, a3, a5	// 下一段
	r&tlb&1	a4, a3		// 获取位于0xE0000000、0xC0000000、…、0的PPN+CA段
	dsync	// 扣紧
	slli	a2, a2, 4
	extui	a4, a4, 0, 4	// 提取CA
	or	a2, a2, a4
	bgeui	a3, 16, 1b
#else
	//  此宏不适用于任意MMU配置。
	//  只需返回零。
	movi	a2, 0
#endif
	.endm

	.macro	icacheattr_get
	_cacheattr_get	itlb
	.endm

	.macro	dcacheattr_get
	_cacheattr_get	dtlb
	.endm


/* CACHEATTR的默认（通电/复位）值，所有BYPASS模式（即禁用/绕过缓存）：*/
#if XCHAL_HAVE_PTP_MMU
# define XCHAL_CACHEATTR_ALL_BYPASS	0x33333333
#else
# define XCHAL_CACHEATTR_ALL_BYPASS	0x22222222
#endif

#if XCHAL_CA_8X512

#if XCHAL_HAVE_PTP_MMU
# define XCHAL_FCA_ENAMASK	0x0AA0	/* 需要启用icache的获取属性位图*/
# define XCHAL_LCA_ENAMASK	0x0FF0	/* 需要启用dcache的加载属性位图*/
# define XCHAL_SCA_ENAMASK	0x0CC0	/* 需要启用dcache的存储属性位图*/
#else
# define XCHAL_FCA_ENAMASK	0x003A	/* 需要启用icache的获取属性位图*/
# define XCHAL_LCA_ENAMASK	0x0033	/* 需要启用dcache的加载属性位图*/
# define XCHAL_SCA_ENAMASK	0x0033	/* 需要启用dcache的存储属性位图*/
#endif
#define XCHAL_LSCA_ENAMASK	(XCHAL_LCA_ENAMASK|XCHAL_SCA_ENAMASK)	/* 需要启用dcache的l/s属性*/
#define XCHAL_ALLCA_ENAMASK	(XCHAL_FCA_ENAMASK|XCHAL_LSCA_ENAMASK)	/* 需要启用缓存的所有属性*/

/*
 *  _cacheattr_is_enabled（已启用缓存属性）
 *
 *  （内部宏。）如果a2中的CACHEATTR指示已启用缓存，则使用a3中的掩码，将分支到\label。
 *
 *  参数：如果启用了缓存，则分支到哪里的标签条目：a2包含用于确定是否启用缓存的CACHEATTR值a3 16位常量，其中每个位对应于16个可能的CA值之一（在CACHEATTR掩码中）；指示缓存已启用的CA值在此掩码中设置了相应的位（例如，使用上面的XCHAL_xCA_ENAMASK）退出：a2、a4、a5已清除SAR
 */
	.macro	_cacheattr_is_enabled	label
	movi	a4, 8		// 循环8次
.Lcaife\@:
	extui	a5, a2, 0, 4	// 获取CA半字节
	ssr	a5		// 根据CA索引到掩码中。。。
	srl	a5, a3		// …并在5位0中获取CA的掩码位
	bbsi.l	a5, 0, \label	// 如果CA指示已启用缓存，则跳转到标签
	srli	a2, a2, 4	// 下一个半字节
	addi	a4, a4, -1
	bnez	a4, .Lcaife\@	// 每个半字节的循环
	.endm

#else /* XCHAL_CA_8X512 */
	.macro	_cacheattr_is_enabled	label
	j	\label		// 宏不适用，假设始终启用缓存
	.endm
#endif /* XCHAL_CA_8X512 */



/*
 *  icacheatr_is已启用
 *
 *  如果启用了I-cache，则分支到\label。
 *
 *  参数：启用icache时分支到的标签入口：（无）出口：a2-a5，SAR阻塞（临时）
 */
	.macro	icacheattr_is_enabled	label
#if XCHAL_CA_8X512
	icacheattr_get
	movi	a3, XCHAL_FCA_ENAMASK
#endif
	_cacheattr_is_enabled	\label
	.endm

/*
 *  dcacheattr_is已启用
 *
 *  如果启用了D-缓存，则分支到\label。
 *
 *  参数：如果启用dcache，则分支到的标签入口：（无）出口：a2-a5，SAR阻塞（临时）
 */
	.macro	dcacheattr_is_enabled	label
#if XCHAL_CA_8X512
	dcacheattr_get
	movi	a3, XCHAL_LSCA_ENAMASK
#endif
	_cacheattr_is_enabled	\label
	.endm

/*
 *  cacheattr_is_enabled（已启用缓存属性）
 *
 *  如果启用了I缓存或D缓存，则分支到\label。
 *
 *  参数：如果启用了缓存，则分支到的标签入口：（无）出口：a2-a5，SAR阻塞（临时）
 */
	.macro	cacheattr_is_enabled	label
#if XCHAL_HAVE_CACHEATTR
	rsr.cacheattr	a2
	movi	a3, XCHAL_ALLCA_ENAMASK
#elif XCHAL_CA_8X512
	icacheattr_get
	movi	a3, XCHAL_FCA_ENAMASK
	_cacheattr_is_enabled	\label
	dcacheattr_get
	movi	a3, XCHAL_LSCA_ENAMASK
#endif
	_cacheattr_is_enabled	\label
	.endm



/*
 *  ISA没有定义的方法来更改运行代码的指令缓存属性，即包围当前PC的内存区域的属性。然而，每个微架构（或微架构中的配置类）都提供了处理此问题的方法。
 *
 *  下面是一些用于实现相关方法的宏。
 */

#if XCHAL_CA_8X512 && !XCHAL_HAVE_CACHEATTR
	//  我们有一个配置，使用简化的
	//  “MMU”由单个静态映射方式组成。

/*
 *  icacheatr_set
 *
 *  条目：a2 cacheattr值设置退出：a2未更改a3-a8已清除（临时）
 */
	.macro	icacheattr_set

	movi	a5, 0xE0000000	// 高3位掩码
	movi	a6, 3f		// 设置ITLB的PC
	movi	a3, XCHAL_SPANNING_WAY	// 从区域0（0..7）开始
	mov	a7, a2		// 复制a2，这样它就不会被破坏
	and	a6, a6, a5	// 本地PC区域的上3位
	j	3f

	//  使用微架构特定方法。
	//  对齐以下4个指令序列，以便
	//  它都适合于单个I-cache行。16字节
	//  对齐就足够了（使用XCHAL_ICACHE_LINESIZE
	//  实际上会导致问题，因为这可能大于
	//  重置向量的对齐方式，此宏通常位于
	//  调用，这将导致链接器对齐重置
	//  矢量代码远离重置矢量！！）。
	.begin	no-transform
	.align	16 /*XCHAL_ICACHE_LINESIZE*/
1:	witlb	a4, a3		// 将512MB段的有线PTE（CA，无PPN）写入ITLB
	isync
	.end	no-transform
	nop
	nop

	sub	a3, a3, a5	// 下一段（添加0x20000000）
	bltui	a3, 16, 4f	// 完成？

	//  注意，在WITLB循环中，我们不执行任何加载/存储
	//  （这里可能不是问题，但在DTLB案例中很重要）。
2:	srli	a7, a7, 4	// 下一个CA
3:
# if XCHAL_HAVE_MIMIC_CACHEATTR
	extui	a4, a7, 0, 4	// 提取CA以设置
# else	/* 有翻译，保留它：*/
	ritlb1	a8, a3		// 获取段的当前PPN+CA
	//dsync//互锁？？？
	extui	a4, a7, 0, 4	// 提取CA以设置
	srli	a8, a8, 4	// 清除CA但保留PPN。。。
	slli	a8, a8, 4	// ...
	add	a4, a4, a8	// 将新CA与PPN结合以保留
# endif
	beq	a3, a6, 1b	// 当前PC的区域？如果是，请以安全的方式进行
	witlb	a4, a3		// 将512MB段的有线PTE（CA[+PPN]）写入ITLB
	sub	a3, a3, a5	// 下一段（添加0x20000000）
	bgeui	a3, 16, 2b
	isync			// 确保所有ifetch更改生效
4:
	.endm	// icacheatr_set


/*
 *  数据缓存属性集
 *
 *  条目：a2 cacheattr值设置退出：a2未更改a3-a8已清除（临时）
 */

	.macro	dcacheattr_set

	movi	a5, 0xE0000000	// 高3位掩码
	movi	a3, XCHAL_SPANNING_WAY	// 从区域0（0..7）开始
	mov	a7, a2		// 复制a2，这样它就不会被破坏
	//  注意，在WDTLB循环中，我们不执行任何加载/存储
2:	//  （包括通过movi隐式l32r），因为它不安全。
# if XCHAL_HAVE_MIMIC_CACHEATTR
	extui	a4, a7, 0, 4	// 提取CA以设置
# else	/* 有翻译，保留它：*/
	rdtlb1	a8, a3		// 获取段的当前PPN+CA
	//dsync//互锁？？？
	extui	a4, a7, 0, 4	// 提取CA以设置
	srli	a8, a8, 4	// 清除CA但保留PPN。。。
	slli	a8, a8, 4	// ...
	add	a4, a4, a8	// 将新CA与PPN结合以保留
# endif
	wdtlb	a4, a3		// 将512MB段的有线PTE（CA[+PPN]）写入DTLB
	sub	a3, a3, a5	// 下一段（添加0x20000000）
	srli	a7, a7, 4	// 下一个CA
	bgeui	a3, 16, 2b
	dsync			// 确保所有数据路径更改生效
	.endm	// 数据缓存属性集

#endif /* XCHAL_CA_8X512 && !XCHAL_HAVE_CACHEATTR */



/*
 *  缓存属性集
 *
 *  根据a2的当前内容安全设置当前CACHEATTR（i和d）的宏。即使在更改当前运行代码的缓存属性时，它也能正常工作。
 *
 *  条目：a2 cacheattr值设置退出：a2未更改a3-a8已清除（临时）
 */
	.macro	cacheattr_set

#if XCHAL_HAVE_CACHEATTR
# if XCHAL_ICACHE_LINESIZE < 4
	//  没有i-cache，因此可以始终安全地写入CACHEATTR：
	wsr.cacheattr	a2
# else
	//  雅典微型建筑，当使用旧的
	//  异常体系结构选项（即使用CACHEATTR寄存器）
	//  允许更改运行代码的缓存属性
	//  使用以下精确序列对齐
	//  指令缓存行。（注意：使用XCHAL_ICACHE_LINESIZE
	//  对齐实际上会导致问题，因为这可能会更大
	//  而不是重置向量的对齐方式，该宏通常
	//  调用，这将导致链接器对齐重置
	//  矢量代码远离重置矢量！！）。
	j	1f
	.begin	no-transform
	.align	16 /*XCHAL_ICACHE_LINESIZE*/	// 对齐到I-cache行内
1:	wsr.cacheattr	a2
	isync
	.end	no-transform
	nop
	nop
# endif
#elif XCHAL_CA_8X512
	//  DTLB和ITLB是独立的，但要保持语义
	//  对于这个宏，我们只需同时写入两者。
	icacheattr_set
	dcacheattr_set
#else
	//  此宏不适用于任意MMU配置。
	//  在这种情况下什么都不要做。
#endif
	.endm


#endif /*XTENSA_CACHEATTRASM_H*/

