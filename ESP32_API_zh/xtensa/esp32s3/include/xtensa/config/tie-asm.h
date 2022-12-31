/*
 * 领带asm。h——编译时HAL汇编程序定义，取决于CORE和TIE
 *
 *  注意：此头文件不应直接包含。
 */

/* 此头文件包含此特定Xtensa处理器的TIE扩展名和选项的汇编语言定义（汇编宏等）。它是根据Xtensa处理器配置定制的。

   客户ID=15128；内部版本=0x90f1f；版权所有（c）1999-221 Cadence Design Systems Inc。

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef _XTENSA_CORE_TIE_ASM_H
#define _XTENSA_CORE_TIE_ASM_H

/*  保存区域保存/恢复宏的选择参数值：*/
/*  期权与TIE：*/
#define XTHAL_SAS_TIE	0x0001	/* 自定义扩展或协处理器*/
#define XTHAL_SAS_OPT	0x0002	/* 可选（而不是协处理器）*/
#define XTHAL_SAS_ANYOT	0x0003	/* 以上两项*/
/*  编译器是否自动使用：*/
#define XTHAL_SAS_NOCC	0x0004	/* 编译器不使用特殊选项/代码*/
#define XTHAL_SAS_CC	0x0008	/* 由编译器使用，无需特殊opts/code*/
#define XTHAL_SAS_ANYCC	0x000C	/* 以上两项*/
/*  跨函数调用的ABI处理：*/
#define XTHAL_SAS_CALR	0x0010	/* 呼叫方已保存*/
#define XTHAL_SAS_CALE	0x0020	/* 被呼叫方已保存*/
#define XTHAL_SAS_GLOB	0x0040	/* 全局跨函数调用（线程中）*/
#define XTHAL_SAS_ANYABI	0x0070	/* 以上三项*/
/*  其他*/
#define XTHAL_SAS_ALL	0xFFFF	/* 包括所有默认NCP内容*/
#define XTHAL_SAS3(optie,ccuse,abi)	( ((optie) & XTHAL_SAS_ANYOT)  \
					| ((ccuse) & XTHAL_SAS_ANYCC)  \
					| ((abi)   & XTHAL_SAS_ANYABI) )


    /*
      *  用于存储所有非协处理器（额外）自定义TIE和可选状态（不包括零开销循环寄存器）的宏。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含一个4字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_NCP_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数：continue如果宏作为较大存储序列的一部分调用，如果这不是序列中的第一个，则设置为1。默认值为0.ofs从要存储的较大序列（从序列中第一个指针的值）开始的偏移。默认为下一个可用空间（如果<continue>为0，则为0）。选择选择要存储的寄存器类别，作为位掩码（请参阅XTHAL_SAS_xxx常量）。默认为所有寄存器。alloc选择要分配的寄存器类别；如果此处选择了不在<select>中的任何类别，则跳过相应寄存器的空间，而不进行任何存储。
      */
    .macro xchal_ncp_store  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start	\continue, \ofs
	// 编译器默认使用的可选全局寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\select)
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	rur.THREADPTR	\at1		// threadptr选项
	s32i	\at1, \ptr, .Lxchal_ofs_+0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endif
	// 编译器默认使用的可选调用方保存的寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 1012, 4, 4
	rsr.ACCLO	\at1		// MAC16选项
	s32i	\at1, \ptr, .Lxchal_ofs_+0
	rsr.ACCHI	\at1		// MAC16选项
	s32i	\at1, \ptr, .Lxchal_ofs_+4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 1012, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.endif
	// 编译器默认不使用可选的调用方保存的寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 996, 4, 4
	rsr.BR	\at1		// 布尔选项
	s32i	\at1, \ptr, .Lxchal_ofs_+0
	rsr.SCOMPARE1	\at1		// 条件存储选项
	s32i	\at1, \ptr, .Lxchal_ofs_+4
	rsr.M0	\at1		// MAC16选项
	s32i	\at1, \ptr, .Lxchal_ofs_+8
	rsr.M1	\at1		// MAC16选项
	s32i	\at1, \ptr, .Lxchal_ofs_+12
	rsr.M2	\at1		// MAC16选项
	s32i	\at1, \ptr, .Lxchal_ofs_+16
	rsr.M3	\at1		// MAC16选项
	s32i	\at1, \ptr, .Lxchal_ofs_+20
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 996, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.endif
    .endm	// xchal_ncp_存储

    /*
      *  宏加载所有非协处理器（额外）自定义TIE和可选状态（不包括零开销循环寄存器）。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含一个4字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_NCP_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数：continue如果宏作为较大加载序列的一部分调用，如果这不是序列中的第一个，则设置为1。默认值为从要加载的较大序列（从序列中第一个指针的值）开始的0.ofs偏移。默认为下一个可用空间（如果<continue>为0，则为0）。选择选择要加载的寄存器类别作为位掩码（请参阅XTHAL_SAS_xxx常量）。默认为所有寄存器。alloc选择要分配的寄存器类别；如果此处选择了不在<select>中的任何类别，则跳过相应寄存器的空间，而不进行任何加载。
      */
    .macro xchal_ncp_load  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start	\continue, \ofs
	// 编译器默认使用的可选全局寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\select)
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	l32i	\at1, \ptr, .Lxchal_ofs_+0
	wur.THREADPTR	\at1		// threadptr选项
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endif
	// 编译器默认使用的可选调用方保存的寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 1012, 4, 4
	l32i	\at1, \ptr, .Lxchal_ofs_+0
	wsr.ACCLO	\at1		// MAC16选项
	l32i	\at1, \ptr, .Lxchal_ofs_+4
	wsr.ACCHI	\at1		// MAC16选项
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 1012, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.endif
	// 编译器默认不使用可选的调用方保存的寄存器：
	.ifeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 996, 4, 4
	l32i	\at1, \ptr, .Lxchal_ofs_+0
	wsr.BR	\at1		// 布尔选项
	l32i	\at1, \ptr, .Lxchal_ofs_+4
	wsr.SCOMPARE1	\at1		// 条件存储选项
	l32i	\at1, \ptr, .Lxchal_ofs_+8
	wsr.M0	\at1		// MAC16选项
	l32i	\at1, \ptr, .Lxchal_ofs_+12
	wsr.M1	\at1		// MAC16选项
	l32i	\at1, \ptr, .Lxchal_ofs_+16
	wsr.M2	\at1		// MAC16选项
	l32i	\at1, \ptr, .Lxchal_ofs_+20
	wsr.M3	\at1		// MAC16选项
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.elseif ((XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 996, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.endif
    .endm	// xchal_ncp_负载


#define XCHAL_NCP_NUM_ATMPS	1

    /*
     *  用于存储TIE协处理器FPU状态的宏。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含一个4字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_CP0_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数与xchal_ncp_store相同。
     */
#define xchal_cp_FPU_store	xchal_cp0_store
    .macro	xchal_cp0_store  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start \continue, \ofs
	// 编译器默认不使用自定义调用方保存的寄存器：
	.ifeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 948, 4, 4
	rur.FCR	\at1		// 尿素232
	s32i	\at1, \ptr, .Lxchal_ofs_+0
	rur.FSR	\at1		// 尿素233
	s32i	\at1, \ptr, .Lxchal_ofs_+4
	ssi	f0, \ptr, .Lxchal_ofs_+8
	ssi	f1, \ptr, .Lxchal_ofs_+12
	ssi	f2, \ptr, .Lxchal_ofs_+16
	ssi	f3, \ptr, .Lxchal_ofs_+20
	ssi	f4, \ptr, .Lxchal_ofs_+24
	ssi	f5, \ptr, .Lxchal_ofs_+28
	ssi	f6, \ptr, .Lxchal_ofs_+32
	ssi	f7, \ptr, .Lxchal_ofs_+36
	ssi	f8, \ptr, .Lxchal_ofs_+40
	ssi	f9, \ptr, .Lxchal_ofs_+44
	ssi	f10, \ptr, .Lxchal_ofs_+48
	ssi	f11, \ptr, .Lxchal_ofs_+52
	ssi	f12, \ptr, .Lxchal_ofs_+56
	ssi	f13, \ptr, .Lxchal_ofs_+60
	ssi	f14, \ptr, .Lxchal_ofs_+64
	ssi	f15, \ptr, .Lxchal_ofs_+68
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 72
	.elseif ((XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 948, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 72
	.endif
    .endm	// xchal_cp0_存储

    /*
     *  宏加载TIE协处理器FPU的状态。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含一个4字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_CP0_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数与xchal_ncp_load相同。
     */
#define xchal_cp_FPU_load	xchal_cp0_load
    .macro	xchal_cp0_load  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start \continue, \ofs
	// 编译器默认不使用自定义调用方保存的寄存器：
	.ifeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 948, 4, 4
	l32i	\at1, \ptr, .Lxchal_ofs_+0
	wur.FCR	\at1		// 尿素232
	l32i	\at1, \ptr, .Lxchal_ofs_+4
	wur.FSR	\at1		// 尿素233
	lsi	f0, \ptr, .Lxchal_ofs_+8
	lsi	f1, \ptr, .Lxchal_ofs_+12
	lsi	f2, \ptr, .Lxchal_ofs_+16
	lsi	f3, \ptr, .Lxchal_ofs_+20
	lsi	f4, \ptr, .Lxchal_ofs_+24
	lsi	f5, \ptr, .Lxchal_ofs_+28
	lsi	f6, \ptr, .Lxchal_ofs_+32
	lsi	f7, \ptr, .Lxchal_ofs_+36
	lsi	f8, \ptr, .Lxchal_ofs_+40
	lsi	f9, \ptr, .Lxchal_ofs_+44
	lsi	f10, \ptr, .Lxchal_ofs_+48
	lsi	f11, \ptr, .Lxchal_ofs_+52
	lsi	f12, \ptr, .Lxchal_ofs_+56
	lsi	f13, \ptr, .Lxchal_ofs_+60
	lsi	f14, \ptr, .Lxchal_ofs_+64
	lsi	f15, \ptr, .Lxchal_ofs_+68
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 72
	.elseif ((XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 948, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 72
	.endif
    .endm	// xchal_cp0_负载

#define XCHAL_CP0_NUM_ATMPS	1
    /*
     *  用于存储TIE协处理器cop_ai状态的宏。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含16字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_CP3_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数与xchal_ncp_store相同。
     */
#define xchal_cp_cop_ai_store	xchal_cp3_store
    .macro	xchal_cp3_store  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start \continue, \ofs
	// 编译器默认不使用自定义调用方保存的寄存器：
	.ifeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 0, 16, 16
	rur.ACCX_0	\at1		// 尿素0
	s32i	\at1, \ptr, .Lxchal_ofs_+0
	rur.ACCX_1	\at1		// 尿素1
	s32i	\at1, \ptr, .Lxchal_ofs_+4
	rur.QACC_H_0	\at1		// 尿素2
	s32i	\at1, \ptr, .Lxchal_ofs_+8
	rur.QACC_H_1	\at1		// 尿素3
	s32i	\at1, \ptr, .Lxchal_ofs_+12
	rur.QACC_H_2	\at1		// 尿素4
	s32i	\at1, \ptr, .Lxchal_ofs_+16
	rur.QACC_H_3	\at1		// 尿素5
	s32i	\at1, \ptr, .Lxchal_ofs_+20
	rur.QACC_H_4	\at1		// 尿素6
	s32i	\at1, \ptr, .Lxchal_ofs_+24
	rur.QACC_L_0	\at1		// 尿素7
	s32i	\at1, \ptr, .Lxchal_ofs_+28
	rur.QACC_L_1	\at1		// 尿素8
	s32i	\at1, \ptr, .Lxchal_ofs_+32
	rur.QACC_L_2	\at1		// 尿素9
	s32i	\at1, \ptr, .Lxchal_ofs_+36
	rur.QACC_L_3	\at1		// 尿素10
	s32i	\at1, \ptr, .Lxchal_ofs_+40
	rur.QACC_L_4	\at1		// 尿素11
	s32i	\at1, \ptr, .Lxchal_ofs_+44
	rur.SAR_BYTE	\at1		// 尿素13
	s32i	\at1, \ptr, .Lxchal_ofs_+48
	rur.FFT_BIT_WIDTH	\at1		// 尿素14
	s32i	\at1, \ptr, .Lxchal_ofs_+52
	rur.UA_STATE_0	\at1		// 尿素15
	s32i	\at1, \ptr, .Lxchal_ofs_+56
	rur.UA_STATE_1	\at1		// 尿素16
	s32i	\at1, \ptr, .Lxchal_ofs_+60
	rur.UA_STATE_2	\at1		// 尿素17
	s32i	\at1, \ptr, .Lxchal_ofs_+64
	rur.UA_STATE_3	\at1		// 尿素18
	s32i	\at1, \ptr, .Lxchal_ofs_+68
	st.qr	q0, \ptr, .Lxchal_ofs_+80
	st.qr	q1, \ptr, .Lxchal_ofs_+96
	st.qr	q2, \ptr, .Lxchal_ofs_+112
	addi	\ptr, \ptr, 128
	st.qr	q3, \ptr, .Lxchal_ofs_+0
	st.qr	q4, \ptr, .Lxchal_ofs_+16
	st.qr	q5, \ptr, .Lxchal_ofs_+32
	st.qr	q6, \ptr, .Lxchal_ofs_+48
	st.qr	q7, \ptr, .Lxchal_ofs_+64
	.set	.Lxchal_pofs_, .Lxchal_pofs_ + 128
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 80
	.elseif ((XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 0, 16, 16
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 208
	.endif
    .endm	// xchal_cp3_存储

    /*
     *  宏加载TIE协处理器cop_ai的状态。必需参数：ptr保存区域指针地址寄存器（clobbered）（寄存器必须包含16字节对齐的地址）。at1.at4四个临时地址寄存器（第一个XCHAL_CP3_NUM_ATMPS寄存器被清除，其余的未使用）。可选参数与xchal_ncp_load相同。
     */
#define xchal_cp_cop_ai_load	xchal_cp3_load
    .macro	xchal_cp3_load  ptr at1 at2 at3 at4  continue=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start \continue, \ofs
	// 编译器默认不使用自定义调用方保存的寄存器：
	.ifeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 0, 16, 16
	l32i	\at1, \ptr, .Lxchal_ofs_+0
	wur.ACCX_0	\at1		// 尿素0
	l32i	\at1, \ptr, .Lxchal_ofs_+4
	wur.ACCX_1	\at1		// 尿素1
	l32i	\at1, \ptr, .Lxchal_ofs_+8
	wur.QACC_H_0	\at1		// 尿素2
	l32i	\at1, \ptr, .Lxchal_ofs_+12
	wur.QACC_H_1	\at1		// 尿素3
	l32i	\at1, \ptr, .Lxchal_ofs_+16
	wur.QACC_H_2	\at1		// 尿素4
	l32i	\at1, \ptr, .Lxchal_ofs_+20
	wur.QACC_H_3	\at1		// 尿素5
	l32i	\at1, \ptr, .Lxchal_ofs_+24
	wur.QACC_H_4	\at1		// 尿素6
	l32i	\at1, \ptr, .Lxchal_ofs_+28
	wur.QACC_L_0	\at1		// 尿素7
	l32i	\at1, \ptr, .Lxchal_ofs_+32
	wur.QACC_L_1	\at1		// 尿素8
	l32i	\at1, \ptr, .Lxchal_ofs_+36
	wur.QACC_L_2	\at1		// 尿素9
	l32i	\at1, \ptr, .Lxchal_ofs_+40
	wur.QACC_L_3	\at1		// 尿素10
	l32i	\at1, \ptr, .Lxchal_ofs_+44
	wur.QACC_L_4	\at1		// 尿素11
	l32i	\at1, \ptr, .Lxchal_ofs_+48
	wur.SAR_BYTE	\at1		// 尿素13
	l32i	\at1, \ptr, .Lxchal_ofs_+52
	wur.FFT_BIT_WIDTH	\at1		// 尿素14
	l32i	\at1, \ptr, .Lxchal_ofs_+56
	wur.UA_STATE_0	\at1		// 尿素15
	l32i	\at1, \ptr, .Lxchal_ofs_+60
	wur.UA_STATE_1	\at1		// 尿素16
	l32i	\at1, \ptr, .Lxchal_ofs_+64
	wur.UA_STATE_2	\at1		// 尿素17
	l32i	\at1, \ptr, .Lxchal_ofs_+68
	wur.UA_STATE_3	\at1		// 尿素18
	ld.qr	q0, \ptr, .Lxchal_ofs_+80
	ld.qr	q1, \ptr, .Lxchal_ofs_+96
	ld.qr	q2, \ptr, .Lxchal_ofs_+112
	addi	\ptr, \ptr, 128
	ld.qr	q3, \ptr, .Lxchal_ofs_+0
	ld.qr	q4, \ptr, .Lxchal_ofs_+16
	ld.qr	q5, \ptr, .Lxchal_ofs_+32
	ld.qr	q6, \ptr, .Lxchal_ofs_+48
	ld.qr	q7, \ptr, .Lxchal_ofs_+64
	.set	.Lxchal_pofs_, .Lxchal_pofs_ + 128
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 80
	.elseif ((XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\alloc)) == 0
	xchal_sa_align	\ptr, 0, 0, 16, 16
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 208
	.endif
    .endm	// xchal_cp3_负载

#define XCHAL_CP3_NUM_ATMPS	1
#define XCHAL_SA_NUM_ATMPS	1

	/*  未配置协处理器的空宏：*/
	.macro xchal_cp1_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp1_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp2_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp2_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp4_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp4_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp5_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp5_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp6_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp6_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp7_store	p a b c d continue=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp7_load	p a b c d continue=0 ofs=-1 select=-1 ; .endm

#endif /*_XTENSA_CORE_TIE_ASM_H*/

