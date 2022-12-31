/*
 * 领带h——编译时HAL定义取决于CORE和TIE配置
 *
 *  注意：此头文件不应直接包含。
 */

/* 此头文件描述了扩展基本Xtensa核心功能的特定Xtensa处理器的TIE扩展。它是根据Xtensa处理器配置定制的。

   版权所有（c）1999-2018 Cadence Design Systems Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef _XTENSA_CORE_TIE_H
#define _XTENSA_CORE_TIE_H

#define XCHAL_CP_NUM			0	/* 协处理器数量*/
#define XCHAL_CP_MAX			0	/* 最大CP ID+1（如果没有，则为0）*/
#define XCHAL_CP_MASK			0x00	/* 按ID列出的所有CP的位掩码*/
#define XCHAL_CP_PORT_MASK		0x00	/* 仅端口CP的位掩码*/

/*  非协处理器可选和自定义（TIE）状态的保存区域：*/
#define XCHAL_NCP_SA_SIZE		4
#define XCHAL_NCP_SA_ALIGN		4

/*  可选和自定义状态的总保存区域（NCP+CPn）：*/
#define XCHAL_TOTAL_SA_SIZE		16	/* 带16字节对齐填充*/
#define XCHAL_TOTAL_SA_ALIGN		4	/* 实际最小对齐*/

/*
 * 保存区域的详细内容。注意：在展开XCHAL_xxx_SA_LIST（）宏之前，调用者必须定义XCHAL_SA_REG宏（此处未定义）。
 *
 * XCHAL_SA_REG（s，ccused，abikind，kind，opt，name，galign，align，asize，dbnum，base，regnum，bitsz，gapsz，reset，x…）
 *
 *	s =从XCHAL_*_LIST传递，例如，如果编译器使用时没有特殊选项或代码，则选择如何扩展ccused=set abikind=0（调用方保存）、1（被调用方保存的）或2（线程全局）kind=0（特殊reg）、1或2（TIE用户reg）opt=0（自定义TIE扩展名或协处理器），或1（可选reg）name=小写reg name（无引号）galign=组字节对齐（2次幂）（galign>=align）align=寄存器字节对齐（二次幂）asize=以字节为单位的分配大小（asize8==bitsz+gapsz+padsz）（不包括galign此或下一个reg所需的任何pad字节）dbnum=唯一目标编号f/debug（请参阅<extensa libdb macros.h>）base=reg shortname w/o索引（或sr=特殊，ur=TIE用户reg）regnum=regfile中的reg索引，或特殊/TIE用户reg编号bitsz=有效位数（regfile宽度，或ur/sr掩码位）gapsz=中间位，如果bitsz位未连续存储（padsz=末尾[TIE regfile]或asize的msbits[ur，sr]处的pad位）reset=寄存器重置值（如果重置时未定义，则为0）x=保留供将来使用（0直到那时）
 *
 *  要过滤掉某些寄存器，例如仅扩展编译器使用的非全局寄存器，可以执行以下操作：
 *
 *  #define XCHAL_SA_REG（s，ccused，p…）SELCC##ccused（p）#define SELCC0（p…）#defined SELCC1（abikind，p..）SELAK##abikind（p。。。
 */

#define XCHAL_NCP_SA_NUM	1
#define XCHAL_NCP_SA_LIST(s)	\
 XCHAL_SA_REG(s,1,2,1,1,      threadptr, 4, 4, 4,0x03E7,  ur,231, 32,0,0,0)

#define XCHAL_CP0_SA_NUM	0
#define XCHAL_CP0_SA_LIST(s)	/* 空的*/

#define XCHAL_CP1_SA_NUM	0
#define XCHAL_CP1_SA_LIST(s)	/* 空的*/

#define XCHAL_CP2_SA_NUM	0
#define XCHAL_CP2_SA_LIST(s)	/* 空的*/

#define XCHAL_CP3_SA_NUM	0
#define XCHAL_CP3_SA_LIST(s)	/* 空的*/

#define XCHAL_CP4_SA_NUM	0
#define XCHAL_CP4_SA_LIST(s)	/* 空的*/

#define XCHAL_CP5_SA_NUM	0
#define XCHAL_CP5_SA_LIST(s)	/* 空的*/

#define XCHAL_CP6_SA_NUM	0
#define XCHAL_CP6_SA_LIST(s)	/* 空的*/

#define XCHAL_CP7_SA_NUM	0
#define XCHAL_CP7_SA_LIST(s)	/* 空的*/

/* 每个FLIX从其第一个半字节（op0字段）开始的指令的字节长度。*/
#define XCHAL_OP0_FORMAT_LENGTHS	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3
/* 每个FLIX从第一个字节开始的指令的字节长度。*/
#define XCHAL_BYTE0_FORMAT_LENGTHS	\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3

#endif /*_XTENSA_CORE_TIE_H*/

