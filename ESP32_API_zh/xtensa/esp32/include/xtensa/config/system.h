/*
 * extensa/config/system。h——取决于SYSTEM配置的HAL定义
 *
 *  注意：此文件的位置和内容极易更改。
 *
 *  独立于配置的二进制文件（链接到特定于配置的HAL库中）的源文件不得包含此文件。HAL本身在历史上曾在某些情况下包含此文件，但这也不合适，因为HAL是特定于核心但独立于系统的。
 */

/* 客户ID=11657；内部版本=0x5fe96；版权所有（c）2000-2010 Tensilica Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */


#ifndef XTENSA_CONFIG_SYSTEM_H
#define XTENSA_CONFIG_SYSTEM_H

/*#包括<xtensa/hal.h>*/



/*----------------------------------------------------------------------
				CONFIGURED SOFTWARE OPTIONS
  ----------------------------------------------------------------------*/

#define XSHAL_USE_ABSOLUTE_LITERALS	0	/* （仅限sw选项，软件是否使用绝对文字）*/
#define XSHAL_HAVE_TEXT_SECTION_LITERALS 1 /* 设置是否存在允许代码和文字的内存。*/

#define XSHAL_ABI			XTHAL_ABI_WINDOWED	/* （仅sw选项，所选ABI）*/
/*  上述映射到以下常量之一：*/
#define XTHAL_ABI_WINDOWED		0
#define XTHAL_ABI_CALL0			1
/*  选择：*/
/*#定义XSHAL_WINDOWED_ABI 1*/	/* 如果选择了窗口ABI，则设置*/
/*#定义XSHAL_CALL0_ABI 0*/	/* 如果选择了call0 ABI，则设置*/

#define XSHAL_CLIB			XTHAL_CLIB_NEWLIB	/* （仅sw选项，所选C库）*/
/*  上述映射到以下常量之一：*/
#define XTHAL_CLIB_NEWLIB		0
#define XTHAL_CLIB_UCLIBC		1
#define XTHAL_CLIB_XCLIB		2
/*  选择：*/
/*#定义XSHAL_NEWLIB 1*/	/* 如果选择了newlib C库，则设置*/
/*#定义XSHAL_UCLIBC 0*/	/* 如果选择了uCLibC C库，则设置*/
/*#定义XSHAL_XCLIB 0*/	/* 如果选择了Xtensa C库，则设置*/

#define XSHAL_USE_FLOATING_POINT	1

#define XSHAL_FLOATING_POINT_ABI	0

/*  针对硬件错误启用的软件解决方案：*/

/*----------------------------------------------------------------------
				DEVICE ADDRESSES
  ----------------------------------------------------------------------*/

/*
 *  奇怪的地方可以找到这些，但配置GUI允许移动这些以考虑各种核心配置。特定的电路板（及其BSP软件）对这些组件具有特定的含义。
 */

/*  I/O块区域：*/
#define XSHAL_IOBLOCK_CACHED_VADDR	0x70000000
#define XSHAL_IOBLOCK_CACHED_PADDR	0x70000000
#define XSHAL_IOBLOCK_CACHED_SIZE	0x0E000000

#define XSHAL_IOBLOCK_BYPASS_VADDR	0x90000000
#define XSHAL_IOBLOCK_BYPASS_PADDR	0x90000000
#define XSHAL_IOBLOCK_BYPASS_SIZE	0x0E000000

/*  系统ROM：*/
#define XSHAL_ROM_VADDR		0x50000000
#define XSHAL_ROM_PADDR		0x50000000
#define XSHAL_ROM_SIZE		0x01000000
/*  最大可用面积（无矢量）：*/
#define XSHAL_ROM_AVAIL_VADDR	0x50000000
#define XSHAL_ROM_AVAIL_VSIZE	0x01000000

/*  系统RAM：*/
#define XSHAL_RAM_VADDR		0x60000000
#define XSHAL_RAM_PADDR		0x60000000
#define XSHAL_RAM_VSIZE		0x20000000
#define XSHAL_RAM_PSIZE		0x20000000
#define XSHAL_RAM_SIZE		XSHAL_RAM_PSIZE
/*  最大可用面积（无矢量）：*/
#define XSHAL_RAM_AVAIL_VADDR	0x60000000
#define XSHAL_RAM_AVAIL_VSIZE	0x20000000

/*
 *  影子系统RAM（与系统RAM相同的设备，位于不同的地址）。（当数据缓存配置为写回模式时，仿真板需要SONIC以太网驱动程序使用此选项。）注意：在完整MMU配置中，这指向系统RAM的BYPASS虚拟地址，即与XSHAL_RAM_相同，只是虚拟地址是通过BYPASS静态映射而不是CACHED静态映射查看的。
 */
#define XSHAL_RAM_BYPASS_VADDR		0xA0000000
#define XSHAL_RAM_BYPASS_PADDR		0xA0000000
#define XSHAL_RAM_BYPASS_PSIZE		0x20000000

/*  备用系统RAM（与系统RAM不同的设备）：*/
/*#定义XSHAL_ALTRAM_[VP]ADDR…未配置。。。*/
/*#定义XSHAL_ALTRAM_SIZE…未配置。。。*/

/*  在模拟中放置设备的一些可用位置（例如XTMP）：*/
#define XSHAL_SIMIO_CACHED_VADDR	0xC0000000
#define XSHAL_SIMIO_BYPASS_VADDR	0xC0000000
#define XSHAL_SIMIO_PADDR		0xC0000000
#define XSHAL_SIMIO_SIZE		0x20000000


/*----------------------------------------------------------------------
 *  供参考测试台退出和诊断程序使用。
 */
#define XSHAL_MAGIC_EXIT		0x0

/*----------------------------------------------------------------------
 *			DEVICE-ADDRESS DEPENDENT...
 *
 *  写入CACHEATTR特殊寄存器（或其等效寄存器）的值，以在各种模式下启用和禁用缓存。
 *----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
			BACKWARD COMPATIBILITY ...
  ----------------------------------------------------------------------*/

/*
 *  注意：以下两个宏已弃用。改用后一种特定于板的宏，这些宏专门针对特定目标环境的内存映射进行了调整。
 */
#define XSHAL_CACHEATTR_BYPASS		XSHAL_XT2000_CACHEATTR_BYPASS	/* 在旁路模式下禁用缓存*/
#define XSHAL_CACHEATTR_DEFAULT		XSHAL_XT2000_CACHEATTR_DEFAULT	/* 启用缓存的默认设置（无写回！）*/

/*----------------------------------------------------------------------
				GENERIC
  ----------------------------------------------------------------------*/

/*  对于以下情况，如果包含系统（PIF）RAM、系统（PIP）ROM、本地内存或XLMI，则使用512MB区域。*/

/*  这些设置将任何未使用的512MB区域设置为缓存BYPASS属性：*/
#define XSHAL_ALLVALID_CACHEATTR_WRITEBACK	0x22221112	/* 在写回模式下启用缓存*/
#define XSHAL_ALLVALID_CACHEATTR_WRITEALLOC	0x22221112	/* 在写分配模式下启用缓存*/
#define XSHAL_ALLVALID_CACHEATTR_WRITETHRU	0x22221112	/* 在直写模式下启用缓存*/
#define XSHAL_ALLVALID_CACHEATTR_BYPASS		0x22222222	/* 在旁路模式下禁用缓存*/
#define XSHAL_ALLVALID_CACHEATTR_DEFAULT	XSHAL_ALLVALID_CACHEATTR_WRITEBACK	/* 启用缓存的默认设置*/

/*  这些设置将任何未使用的512MB区域设置为ILLEGAL属性：*/
#define XSHAL_STRICT_CACHEATTR_WRITEBACK	0xFFFF111F	/* 在写回模式下启用缓存*/
#define XSHAL_STRICT_CACHEATTR_WRITEALLOC	0xFFFF111F	/* 在写分配模式下启用缓存*/
#define XSHAL_STRICT_CACHEATTR_WRITETHRU	0xFFFF111F	/* 在直写模式下启用缓存*/
#define XSHAL_STRICT_CACHEATTR_BYPASS		0xFFFF222F	/* 在旁路模式下禁用缓存*/
#define XSHAL_STRICT_CACHEATTR_DEFAULT		XSHAL_STRICT_CACHEATTR_WRITEBACK	/* 启用缓存的默认设置*/

/*  它们将第一个512MB（如果未使用）设置为ILLEGAL属性，以帮助捕获NULL指针解引用错误；所有其他未使用的512MB区域都设置为缓存BYPASS属性：*/
#define XSHAL_TRAPNULL_CACHEATTR_WRITEBACK	0x2222111F	/* 在写回模式下启用缓存*/
#define XSHAL_TRAPNULL_CACHEATTR_WRITEALLOC	0x2222111F	/* 在写分配模式下启用缓存*/
#define XSHAL_TRAPNULL_CACHEATTR_WRITETHRU	0x2222111F	/* 在直写模式下启用缓存*/
#define XSHAL_TRAPNULL_CACHEATTR_BYPASS		0x2222222F	/* 在旁路模式下禁用缓存*/
#define XSHAL_TRAPNULL_CACHEATTR_DEFAULT	XSHAL_TRAPNULL_CACHEATTR_WRITEBACK	/* 启用缓存的默认设置*/

/*----------------------------------------------------------------------
ISS（指令集模拟器）特定。。。
  ----------------------------------------------------------------------*/

/*  目前，ISS默认为TRAPNULL设置：*/
#define XSHAL_ISS_CACHEATTR_WRITEBACK	XSHAL_TRAPNULL_CACHEATTR_WRITEBACK
#define XSHAL_ISS_CACHEATTR_WRITEALLOC	XSHAL_TRAPNULL_CACHEATTR_WRITEALLOC
#define XSHAL_ISS_CACHEATTR_WRITETHRU	XSHAL_TRAPNULL_CACHEATTR_WRITETHRU
#define XSHAL_ISS_CACHEATTR_BYPASS	XSHAL_TRAPNULL_CACHEATTR_BYPASS
#define XSHAL_ISS_CACHEATTR_DEFAULT	XSHAL_TRAPNULL_CACHEATTR_WRITEBACK

#define XSHAL_ISS_PIPE_REGIONS	0
#define XSHAL_ISS_SDRAM_REGIONS	0


/*----------------------------------------------------------------------
			XT2000 BOARD SPECIFIC ...
  ----------------------------------------------------------------------*/

/*  对于以下情况，如果包含任何系统RAM、系统ROM、本地内存、XLMI或其他XT2000板设备或内存，则使用512MB区域。无论宏是_WRITEBACK还是_BYPASS等，包含设备的区域都将强制缓存BYPASS模式。*/

/*  这些设置将XT2000上未使用的任何512MB区域设置为ILLEGAL属性：*/
#define XSHAL_XT2000_CACHEATTR_WRITEBACK	0xFF22111F	/* 在写回模式下启用缓存*/
#define XSHAL_XT2000_CACHEATTR_WRITEALLOC	0xFF22111F	/* 在写分配模式下启用缓存*/
#define XSHAL_XT2000_CACHEATTR_WRITETHRU	0xFF22111F	/* 在直写模式下启用缓存*/
#define XSHAL_XT2000_CACHEATTR_BYPASS		0xFF22222F	/* 在旁路模式下禁用缓存*/
#define XSHAL_XT2000_CACHEATTR_DEFAULT		XSHAL_XT2000_CACHEATTR_WRITEBACK	/* 启用缓存的默认设置*/

#define XSHAL_XT2000_PIPE_REGIONS	0x00000000	/* BusInt管道区域*/
#define XSHAL_XT2000_SDRAM_REGIONS	0x00000440	/* BusInt SDRAM区域*/


/*----------------------------------------------------------------------
				VECTOR INFO AND SIZES
  ----------------------------------------------------------------------*/

#define XSHAL_VECTORS_PACKED		0
#define XSHAL_STATIC_VECTOR_SELECT	1
#define XSHAL_RESET_VECTOR_VADDR	0x40000400
#define XSHAL_RESET_VECTOR_PADDR	0x40000400

/*
 *  系统（内存映射）配置分配给向量的大小。这些大小受核心配置的限制（例如，一个向量的代码不能溢出到另一个向量中），但取决于系统或板（或LSP）内存映射配置。
 *
 *  每个向量是否恰好位于系统ROM中也是一个系统配置问题，有时很有用，这里也包括：
 */
#define XSHAL_RESET_VECTOR_SIZE	0x00000300
#define XSHAL_RESET_VECTOR_ISROM	0
#define XSHAL_USER_VECTOR_SIZE	0x00000038
#define XSHAL_USER_VECTOR_ISROM	0
#define XSHAL_PROGRAMEXC_VECTOR_SIZE	XSHAL_USER_VECTOR_SIZE	/* 用于向后兼容*/
#define XSHAL_USEREXC_VECTOR_SIZE	XSHAL_USER_VECTOR_SIZE	/* 用于向后兼容*/
#define XSHAL_KERNEL_VECTOR_SIZE	0x00000038
#define XSHAL_KERNEL_VECTOR_ISROM	0
#define XSHAL_STACKEDEXC_VECTOR_SIZE	XSHAL_KERNEL_VECTOR_SIZE	/* 用于向后兼容*/
#define XSHAL_KERNELEXC_VECTOR_SIZE	XSHAL_KERNEL_VECTOR_SIZE	/* 用于向后兼容*/
#define XSHAL_DOUBLEEXC_VECTOR_SIZE	0x00000040
#define XSHAL_DOUBLEEXC_VECTOR_ISROM	0
#define XSHAL_WINDOW_VECTORS_SIZE	0x00000178
#define XSHAL_WINDOW_VECTORS_ISROM	0
#define XSHAL_INTLEVEL2_VECTOR_SIZE	0x00000038
#define XSHAL_INTLEVEL2_VECTOR_ISROM	0
#define XSHAL_INTLEVEL3_VECTOR_SIZE	0x00000038
#define XSHAL_INTLEVEL3_VECTOR_ISROM	0
#define XSHAL_INTLEVEL4_VECTOR_SIZE	0x00000038
#define XSHAL_INTLEVEL4_VECTOR_ISROM	0
#define XSHAL_INTLEVEL5_VECTOR_SIZE	0x00000038
#define XSHAL_INTLEVEL5_VECTOR_ISROM	0
#define XSHAL_INTLEVEL6_VECTOR_SIZE	0x00000038
#define XSHAL_INTLEVEL6_VECTOR_ISROM	0
#define XSHAL_DEBUG_VECTOR_SIZE		XSHAL_INTLEVEL6_VECTOR_SIZE
#define XSHAL_DEBUG_VECTOR_ISROM	XSHAL_INTLEVEL6_VECTOR_ISROM
#define XSHAL_NMI_VECTOR_SIZE	0x00000038
#define XSHAL_NMI_VECTOR_ISROM	0
#define XSHAL_INTLEVEL7_VECTOR_SIZE	XSHAL_NMI_VECTOR_SIZE


#endif /*XTENSA_CONFIG_SYSTEM_H*/

