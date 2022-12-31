// - ----------------------------------------------------------------------------
// -ATMEL微控制器软件支持-ROUSSET-
// - ----------------------------------------------------------------------------
// -  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// -  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// -  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// -  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// -  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// -  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// -  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// -  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// -  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// -  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// - ----------------------------------------------------------------------------
// -文件名：AT91SAM7X256.h
// -对象：AT91SAM7X256定义
// -生成：AT91 SW应用程序组11/02/2005（15:17:24）
// - 
// -CVS参考号：/AT91SAM7X256.pl/1/114/2005年9月13日星期二15:06:52//
// -CVS参考：/SYS_SAM7X.pl/1.3/2005年2月1日星期二17:01:43//
// -CVS参考：/MC_SAM7X.pl/12/2005年5月20日星期五14:13:04//
// -CVS参考：/PMC_SAM7X.pl/1.4/2005年2月8日星期二13:58:10//
// -CVS参考：/RSTC_SAM7X.pl/12/2005年7月13日星期三14:57:50//
// -CVS参考：/UDP_SAM7X.pl/11/2005年5月10日星期二11:35:35//
// -CVS参考：/PWM_SAM7X.pl/11/2005年5月10日星期二11:53:07//
// -CVS参考：/AIC_6075B.pl/1.3/2005年5月20日星期五14:01:30//
// -CVS参考号：/PIO-6057A.pl/1.2/2005年2月3日星期四10:18:28//
// -CVS参考：/RTTC_6081A.pl/12/2004年11月9日星期二14:43:58//
// -CVS参考号：/PIC_6079A.pl/12/2004年11月9日星期二14:43:56//
// -CVS参考：/WDTC_6080A.pl/1.3/2004年11月9日星期二14:44:00//
// -CVS参考：/VREG_6085B.pl/1.1/2005年2月1日星期二16:05:48//
// -CVS参考：/PDC_6074C.pl/12/2005年2月3日星期四08:48:54//
// -CVS参考：/DBGU_6059D.pl/1.1/2005年1月31日星期一13:15:32//
// -CVS参考号：/SPI_6088D.pl/1.3/2005年5月20日星期五14:08:59//
// -CVS参考：/US_6089C.pl/11/Mon Jul 12 18:23:26 2004//
// -CVS参考：/SSC_6078B.pl/1.1/2005年7月13日星期三15:19:19//
// -CVS参考号：/TTWI_6061A.pl/1/11/2004年7月13日星期二07:38:06//
// -CVS参考：/TC_6082A.pl/1.7/2005年3月11日星期五12:52:17//
// -CVS参考号：/CAN_6019B.pl/11/2005年3月8日星期二12:42:22//
// -CVS参考：/EMACB_6119A.pl/1.6/2005年7月13日星期三15:05:35//
// -CVS参考号：/AADC_6051C.pl/11/10月17日星期五09:12:38 2003//
// - ----------------------------------------------------------------------------

#ifndef AT91SAM7X256_H
#define AT91SAM7X256_H

#ifdef __IAR_SYSTEMS_ICC__

typedef volatile unsigned int AT91_REG;// 硬件寄存器定义

// *****************************************************************************
//              系统外围设备的软件API定义
// *****************************************************************************
typedef struct _AT91S_SYS {
	AT91_REG	 AIC_SMR[32]; 	// 源模式寄存器
	AT91_REG	 AIC_SVR[32]; 	// 源向量寄存器
	AT91_REG	 AIC_IVR; 	// IRQ矢量寄存器
	AT91_REG	 AIC_FVR; 	// FIQ矢量寄存器
	AT91_REG	 AIC_ISR; 	// 中断状态寄存器
	AT91_REG	 AIC_IPR; 	// 中断挂起寄存器
	AT91_REG	 AIC_IMR; 	// 中断掩码寄存器
	AT91_REG	 AIC_CISR; 	// 核心中断状态寄存器
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 AIC_IECR; 	// 中断启用命令寄存器
	AT91_REG	 AIC_IDCR; 	// 中断禁用命令寄存器
	AT91_REG	 AIC_ICCR; 	// 中断清除命令寄存器
	AT91_REG	 AIC_ISCR; 	// 中断设置命令寄存器
	AT91_REG	 AIC_EOICR; 	// 中断命令寄存器结束
	AT91_REG	 AIC_SPU; 	// 虚假向量寄存器
	AT91_REG	 AIC_DCR; 	// 调试控制寄存器（保护）
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 AIC_FFER; 	// 快速强制启用寄存器
	AT91_REG	 AIC_FFDR; 	// 快速强制禁用寄存器
	AT91_REG	 AIC_FFSR; 	// 快速强制状态寄存器
	AT91_REG	 Reserved2[45]; 	// 
	AT91_REG	 DBGU_CR; 	// 控制寄存器
	AT91_REG	 DBGU_MR; 	// 模式寄存器
	AT91_REG	 DBGU_IER; 	// 中断启用寄存器
	AT91_REG	 DBGU_IDR; 	// 中断禁用寄存器
	AT91_REG	 DBGU_IMR; 	// 中断掩码寄存器
	AT91_REG	 DBGU_CSR; 	// 信道状态寄存器
	AT91_REG	 DBGU_RHR; 	// 接收机保持寄存器
	AT91_REG	 DBGU_THR; 	// 变送器保持寄存器
	AT91_REG	 DBGU_BRGR; 	// 波特率发生器寄存器
	AT91_REG	 Reserved3[7]; 	// 
	AT91_REG	 DBGU_CIDR; 	// 芯片ID寄存器
	AT91_REG	 DBGU_EXID; 	// 芯片ID扩展寄存器
	AT91_REG	 DBGU_FNTR; 	// 强制NTRST寄存器
	AT91_REG	 Reserved4[45]; 	// 
	AT91_REG	 DBGU_RPR; 	// 接收指针寄存器
	AT91_REG	 DBGU_RCR; 	// 接收计数器寄存器
	AT91_REG	 DBGU_TPR; 	// 发送指针寄存器
	AT91_REG	 DBGU_TCR; 	// 发送计数器寄存器
	AT91_REG	 DBGU_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 DBGU_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 DBGU_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 DBGU_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 DBGU_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 DBGU_PTSR; 	// PDC传输状态寄存器
	AT91_REG	 Reserved5[54]; 	// 
	AT91_REG	 PIOA_PER; 	// PIO启用寄存器
	AT91_REG	 PIOA_PDR; 	// PIO禁用寄存器
	AT91_REG	 PIOA_PSR; 	// PIO状态寄存器
	AT91_REG	 Reserved6[1]; 	// 
	AT91_REG	 PIOA_OER; 	// 输出启用寄存器
	AT91_REG	 PIOA_ODR; 	// 输出禁用寄存器
	AT91_REG	 PIOA_OSR; 	// 输出状态寄存器
	AT91_REG	 Reserved7[1]; 	// 
	AT91_REG	 PIOA_IFER; 	// 输入滤波器启用寄存器
	AT91_REG	 PIOA_IFDR; 	// 输入滤波器禁用寄存器
	AT91_REG	 PIOA_IFSR; 	// 输入过滤器状态寄存器
	AT91_REG	 Reserved8[1]; 	// 
	AT91_REG	 PIOA_SODR; 	// 设置输出数据寄存器
	AT91_REG	 PIOA_CODR; 	// 清除输出数据寄存器
	AT91_REG	 PIOA_ODSR; 	// 输出数据状态寄存器
	AT91_REG	 PIOA_PDSR; 	// 引脚数据状态寄存器
	AT91_REG	 PIOA_IER; 	// 中断启用寄存器
	AT91_REG	 PIOA_IDR; 	// 中断禁用寄存器
	AT91_REG	 PIOA_IMR; 	// 中断掩码寄存器
	AT91_REG	 PIOA_ISR; 	// 中断状态寄存器
	AT91_REG	 PIOA_MDER; 	// 多驱动程序启用寄存器
	AT91_REG	 PIOA_MDDR; 	// 多驱动程序禁用寄存器
	AT91_REG	 PIOA_MDSR; 	// 多驱动程序状态寄存器
	AT91_REG	 Reserved9[1]; 	// 
	AT91_REG	 PIOA_PPUDR; 	// 上拉禁用寄存器
	AT91_REG	 PIOA_PPUER; 	// 上拉启用寄存器
	AT91_REG	 PIOA_PPUSR; 	// 拉起状态寄存器
	AT91_REG	 Reserved10[1]; 	// 
	AT91_REG	 PIOA_ASR; 	// 选择一个寄存器
	AT91_REG	 PIOA_BSR; 	// 选择B寄存器
	AT91_REG	 PIOA_ABSR; 	// AB选择状态寄存器
	AT91_REG	 Reserved11[9]; 	// 
	AT91_REG	 PIOA_OWER; 	// 输出写入启用寄存器
	AT91_REG	 PIOA_OWDR; 	// 输出写入禁用寄存器
	AT91_REG	 PIOA_OWSR; 	// 输出写入状态寄存器
	AT91_REG	 Reserved12[85]; 	// 
	AT91_REG	 PIOB_PER; 	// PIO启用寄存器
	AT91_REG	 PIOB_PDR; 	// PIO禁用寄存器
	AT91_REG	 PIOB_PSR; 	// PIO状态寄存器
	AT91_REG	 Reserved13[1]; 	// 
	AT91_REG	 PIOB_OER; 	// 输出启用寄存器
	AT91_REG	 PIOB_ODR; 	// 输出禁用寄存器
	AT91_REG	 PIOB_OSR; 	// 输出状态寄存器
	AT91_REG	 Reserved14[1]; 	// 
	AT91_REG	 PIOB_IFER; 	// 输入滤波器启用寄存器
	AT91_REG	 PIOB_IFDR; 	// 输入滤波器禁用寄存器
	AT91_REG	 PIOB_IFSR; 	// 输入过滤器状态寄存器
	AT91_REG	 Reserved15[1]; 	// 
	AT91_REG	 PIOB_SODR; 	// 设置输出数据寄存器
	AT91_REG	 PIOB_CODR; 	// 清除输出数据寄存器
	AT91_REG	 PIOB_ODSR; 	// 输出数据状态寄存器
	AT91_REG	 PIOB_PDSR; 	// 引脚数据状态寄存器
	AT91_REG	 PIOB_IER; 	// 中断启用寄存器
	AT91_REG	 PIOB_IDR; 	// 中断禁用寄存器
	AT91_REG	 PIOB_IMR; 	// 中断掩码寄存器
	AT91_REG	 PIOB_ISR; 	// 中断状态寄存器
	AT91_REG	 PIOB_MDER; 	// 多驱动程序启用寄存器
	AT91_REG	 PIOB_MDDR; 	// 多驱动程序禁用寄存器
	AT91_REG	 PIOB_MDSR; 	// 多驱动程序状态寄存器
	AT91_REG	 Reserved16[1]; 	// 
	AT91_REG	 PIOB_PPUDR; 	// 上拉禁用寄存器
	AT91_REG	 PIOB_PPUER; 	// 上拉启用寄存器
	AT91_REG	 PIOB_PPUSR; 	// 拉起状态寄存器
	AT91_REG	 Reserved17[1]; 	// 
	AT91_REG	 PIOB_ASR; 	// 选择一个寄存器
	AT91_REG	 PIOB_BSR; 	// 选择B寄存器
	AT91_REG	 PIOB_ABSR; 	// AB选择状态寄存器
	AT91_REG	 Reserved18[9]; 	// 
	AT91_REG	 PIOB_OWER; 	// 输出写入启用寄存器
	AT91_REG	 PIOB_OWDR; 	// 输出写入禁用寄存器
	AT91_REG	 PIOB_OWSR; 	// 输出写入状态寄存器
	AT91_REG	 Reserved19[341]; 	// 
	AT91_REG	 PMC_SCER; 	// 系统时钟启用寄存器
	AT91_REG	 PMC_SCDR; 	// 系统时钟禁用寄存器
	AT91_REG	 PMC_SCSR; 	// 系统时钟状态寄存器
	AT91_REG	 Reserved20[1]; 	// 
	AT91_REG	 PMC_PCER; 	// 外围时钟启用寄存器
	AT91_REG	 PMC_PCDR; 	// 外围时钟禁用寄存器
	AT91_REG	 PMC_PCSR; 	// 外围时钟状态寄存器
	AT91_REG	 Reserved21[1]; 	// 
	AT91_REG	 PMC_MOR; 	// 主振荡器寄存器
	AT91_REG	 PMC_MCFR; 	// 主时钟频率寄存器
	AT91_REG	 Reserved22[1]; 	// 
	AT91_REG	 PMC_PLLR; 	// PLL寄存器
	AT91_REG	 PMC_MCKR; 	// 主时钟寄存器
	AT91_REG	 Reserved23[3]; 	// 
	AT91_REG	 PMC_PCKR[4]; 	// 可编程时钟寄存器
	AT91_REG	 Reserved24[4]; 	// 
	AT91_REG	 PMC_IER; 	// 中断启用寄存器
	AT91_REG	 PMC_IDR; 	// 中断禁用寄存器
	AT91_REG	 PMC_SR; 	// 状态寄存器
	AT91_REG	 PMC_IMR; 	// 中断掩码寄存器
	AT91_REG	 Reserved25[36]; 	// 
	AT91_REG	 RSTC_RCR; 	// 重置控制寄存器
	AT91_REG	 RSTC_RSR; 	// 重置状态寄存器
	AT91_REG	 RSTC_RMR; 	// 重置模式寄存器
	AT91_REG	 Reserved26[5]; 	// 
	AT91_REG	 RTTC_RTMR; 	// 实时模式寄存器
	AT91_REG	 RTTC_RTAR; 	// 实时报警寄存器
	AT91_REG	 RTTC_RTVR; 	// 实时值寄存器
	AT91_REG	 RTTC_RTSR; 	// 实时状态寄存器
	AT91_REG	 PITC_PIMR; 	// 周期间隔模式寄存器
	AT91_REG	 PITC_PISR; 	// 周期间隔状态寄存器
	AT91_REG	 PITC_PIVR; 	// 周期间隔值寄存器
	AT91_REG	 PITC_PIIR; 	// 周期间隔图像寄存器
	AT91_REG	 WDTC_WDCR; 	// 看门狗控制寄存器
	AT91_REG	 WDTC_WDMR; 	// 看门狗模式寄存器
	AT91_REG	 WDTC_WDSR; 	// 看门狗状态寄存器
	AT91_REG	 Reserved27[5]; 	// 
	AT91_REG	 VREG_MR; 	// 电压调节器模式寄存器
} AT91S_SYS, *AT91PS_SYS;


// *****************************************************************************
//              高级中断控制器的软件API定义
// *****************************************************************************
typedef struct _AT91S_AIC {
	AT91_REG	 AIC_SMR[32]; 	// 源模式寄存器
	AT91_REG	 AIC_SVR[32]; 	// 源向量寄存器
	AT91_REG	 AIC_IVR; 	// IRQ矢量寄存器
	AT91_REG	 AIC_FVR; 	// FIQ矢量寄存器
	AT91_REG	 AIC_ISR; 	// 中断状态寄存器
	AT91_REG	 AIC_IPR; 	// 中断挂起寄存器
	AT91_REG	 AIC_IMR; 	// 中断掩码寄存器
	AT91_REG	 AIC_CISR; 	// 核心中断状态寄存器
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 AIC_IECR; 	// 中断启用命令寄存器
	AT91_REG	 AIC_IDCR; 	// 中断禁用命令寄存器
	AT91_REG	 AIC_ICCR; 	// 中断清除命令寄存器
	AT91_REG	 AIC_ISCR; 	// 中断设置命令寄存器
	AT91_REG	 AIC_EOICR; 	// 中断命令寄存器结束
	AT91_REG	 AIC_SPU; 	// 虚假向量寄存器
	AT91_REG	 AIC_DCR; 	// 调试控制寄存器（保护）
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 AIC_FFER; 	// 快速强制启用寄存器
	AT91_REG	 AIC_FFDR; 	// 快速强制禁用寄存器
	AT91_REG	 AIC_FFSR; 	// 快速强制状态寄存器
} AT91S_AIC, *AT91PS_AIC;

// --------AIC_SMR：（AIC偏移：0x0）控制寄存器--------
#define AT91C_AIC_PRIOR       ((unsigned int) 0x7 <<  0) // （AIC）优先级
#define 	AT91C_AIC_PRIOR_LOWEST               ((unsigned int) 0x0) // （AIC）最低优先级
#define 	AT91C_AIC_PRIOR_HIGHEST              ((unsigned int) 0x7) // （AIC）最高优先级
#define AT91C_AIC_SRCTYPE     ((unsigned int) 0x3 <<  5) // （AIC）中断源类型
#define 	AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL       ((unsigned int) 0x0 <<  5) // （AIC）内部源代码标签高度敏感
#define 	AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL        ((unsigned int) 0x0 <<  5) // （AIC）外部源代码标签低级别敏感
#define 	AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE    ((unsigned int) 0x1 <<  5) // （AIC）内部源代码标签正边缘触发
#define 	AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE    ((unsigned int) 0x1 <<  5) // （AIC）外部源代码标签负边缘触发
#define 	AT91C_AIC_SRCTYPE_HIGH_LEVEL           ((unsigned int) 0x2 <<  5) // （AIC）内部或外部源代码标签高级别敏感
#define 	AT91C_AIC_SRCTYPE_POSITIVE_EDGE        ((unsigned int) 0x3 <<  5) // （AIC）内部或外部源代码标签正边缘触发
// --------AIC_CISR：（AIC偏移：0x114）AIC核心中断状态寄存器--------
#define AT91C_AIC_NFIQ        ((unsigned int) 0x1 <<  0) // （AIC）NFIQ状态
#define AT91C_AIC_NIRQ        ((unsigned int) 0x1 <<  1) // （AIC）NIRQ状态
// --------AIC_DCR：（AIC偏移：0x138）AIC调试控制寄存器（保护）--------
#define AT91C_AIC_DCR_PROT    ((unsigned int) 0x1 <<  0) // （AIC）保护模式
#define AT91C_AIC_DCR_GMSK    ((unsigned int) 0x1 <<  1) // （AIC）通用掩码

// *****************************************************************************
//              外设DMA控制器的软件API定义
// *****************************************************************************
typedef struct _AT91S_PDC {
	AT91_REG	 PDC_RPR; 	// 接收指针寄存器
	AT91_REG	 PDC_RCR; 	// 接收计数器寄存器
	AT91_REG	 PDC_TPR; 	// 发送指针寄存器
	AT91_REG	 PDC_TCR; 	// 发送计数器寄存器
	AT91_REG	 PDC_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 PDC_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 PDC_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 PDC_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 PDC_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 PDC_PTSR; 	// PDC传输状态寄存器
} AT91S_PDC, *AT91PS_PDC;

// --------PDC_PTCR：（PDC偏移：0x20）PDC传输控制寄存器--------
#define AT91C_PDC_RXTEN       ((unsigned int) 0x1 <<  0) // （PDC）接收器传输启用
#define AT91C_PDC_RXTDIS      ((unsigned int) 0x1 <<  1) // （PDC）接收器传输禁用
#define AT91C_PDC_TXTEN       ((unsigned int) 0x1 <<  8) // （PDC）发射器传输启用
#define AT91C_PDC_TXTDIS      ((unsigned int) 0x1 <<  9) // （PDC）发射器传输禁用
// --------PDC_PTSR：（PDC偏移：0x24）PDC传输状态寄存器--------

// *****************************************************************************
//              调试单元的软件API定义
// *****************************************************************************
typedef struct _AT91S_DBGU {
	AT91_REG	 DBGU_CR; 	// 控制寄存器
	AT91_REG	 DBGU_MR; 	// 模式寄存器
	AT91_REG	 DBGU_IER; 	// 中断启用寄存器
	AT91_REG	 DBGU_IDR; 	// 中断禁用寄存器
	AT91_REG	 DBGU_IMR; 	// 中断掩码寄存器
	AT91_REG	 DBGU_CSR; 	// 信道状态寄存器
	AT91_REG	 DBGU_RHR; 	// 接收机保持寄存器
	AT91_REG	 DBGU_THR; 	// 变送器保持寄存器
	AT91_REG	 DBGU_BRGR; 	// 波特率发生器寄存器
	AT91_REG	 Reserved0[7]; 	// 
	AT91_REG	 DBGU_CIDR; 	// 芯片ID寄存器
	AT91_REG	 DBGU_EXID; 	// 芯片ID扩展寄存器
	AT91_REG	 DBGU_FNTR; 	// 强制NTRST寄存器
	AT91_REG	 Reserved1[45]; 	// 
	AT91_REG	 DBGU_RPR; 	// 接收指针寄存器
	AT91_REG	 DBGU_RCR; 	// 接收计数器寄存器
	AT91_REG	 DBGU_TPR; 	// 发送指针寄存器
	AT91_REG	 DBGU_TCR; 	// 发送计数器寄存器
	AT91_REG	 DBGU_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 DBGU_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 DBGU_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 DBGU_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 DBGU_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 DBGU_PTSR; 	// PDC传输状态寄存器
} AT91S_DBGU, *AT91PS_DBGU;

// --------DBGU_CR：（DBGU偏移量：0x0）调试单元控制寄存器--------
#define AT91C_US_RSTRX        ((unsigned int) 0x1 <<  2) // （DBGU）重置接收器
#define AT91C_US_RSTTX        ((unsigned int) 0x1 <<  3) // （DBGU）复位变送器
#define AT91C_US_RXEN         ((unsigned int) 0x1 <<  4) // （DBGU）接收器启用
#define AT91C_US_RXDIS        ((unsigned int) 0x1 <<  5) // （DBGU）接收器禁用
#define AT91C_US_TXEN         ((unsigned int) 0x1 <<  6) // （DBGU）变送器启用
#define AT91C_US_TXDIS        ((unsigned int) 0x1 <<  7) // （DBGU）变送器禁用
#define AT91C_US_RSTSTA       ((unsigned int) 0x1 <<  8) // （DBGU）重置状态位
// --------DBGU_MR：（DBGU偏移量：0x4）调试单元模式寄存器--------
#define AT91C_US_PAR          ((unsigned int) 0x7 <<  9) // （DBGU）奇偶校验类型
#define 	AT91C_US_PAR_EVEN                 ((unsigned int) 0x0 <<  9) // （DBGU）偶校验
#define 	AT91C_US_PAR_ODD                  ((unsigned int) 0x1 <<  9) // （DBGU）奇数奇偶校验
#define 	AT91C_US_PAR_SPACE                ((unsigned int) 0x2 <<  9) // （DBGU）奇偶校验强制为0（空格）
#define 	AT91C_US_PAR_MARK                 ((unsigned int) 0x3 <<  9) // （DBGU）奇偶校验强制为1（标记）
#define 	AT91C_US_PAR_NONE                 ((unsigned int) 0x4 <<  9) // （DBGU）无奇偶校验
#define 	AT91C_US_PAR_MULTI_DROP           ((unsigned int) 0x6 <<  9) // （DBGU）多点模式
#define AT91C_US_CHMODE       ((unsigned int) 0x3 << 14) // （DBGU）信道模式
#define 	AT91C_US_CHMODE_NORMAL               ((unsigned int) 0x0 << 14) // （DBGU）正常模式：USART信道作为RX/TX USART运行。
#define 	AT91C_US_CHMODE_AUTO                 ((unsigned int) 0x1 << 14) // （DBGU）自动回声：接收器数据输入连接到TXD引脚。
#define 	AT91C_US_CHMODE_LOCAL                ((unsigned int) 0x2 << 14) // （DBGU）本地环回：发射机输出信号连接到接收机输入信号。
#define 	AT91C_US_CHMODE_REMOTE               ((unsigned int) 0x3 << 14) // （DBGU）远程环回：RXD引脚内部连接到TXD引脚。
// --------DBGU_IER:（DBGU偏移：0x8）调试单元中断启用寄存器--------
#define AT91C_US_RXRDY        ((unsigned int) 0x1 <<  0) // （DBGU）RXRDY中断
#define AT91C_US_TXRDY        ((unsigned int) 0x1 <<  1) // （DBGU）TXRDY中断
#define AT91C_US_ENDRX        ((unsigned int) 0x1 <<  3) // （DBGU）接收传输中断结束
#define AT91C_US_ENDTX        ((unsigned int) 0x1 <<  4) // （DBGU）传输中断结束
#define AT91C_US_OVRE         ((unsigned int) 0x1 <<  5) // （DBGU）超限中断
#define AT91C_US_FRAME        ((unsigned int) 0x1 <<  6) // （DBGU）成帧错误中断
#define AT91C_US_PARE         ((unsigned int) 0x1 <<  7) // （DBGU）奇偶错误中断
#define AT91C_US_TXEMPTY      ((unsigned int) 0x1 <<  9) // （DBGU）TXEMPTY中断
#define AT91C_US_TXBUFE       ((unsigned int) 0x1 << 11) // （DBGU）TXBUFE中断
#define AT91C_US_RXBUFF       ((unsigned int) 0x1 << 12) // （DBGU）RXBUFF中断
#define AT91C_US_COMM_TX      ((unsigned int) 0x1 << 30) // （DBGU）COMM_TX中断
#define AT91C_US_COMM_RX      ((unsigned int) 0x1 << 31) // （DBGU）COMM_RX中断
// --------DBGU_IDR:（DBGU偏移量：0xc）调试单元中断禁用寄存器--------
// --------DBGU_IMR：（DBGU偏移：0x10）调试单元中断掩码寄存器--------
// --------DBGU_CSR:（DBGU偏移：0x14）调试单元信道状态寄存器--------
// --------DBGU_FNTR：（DBGU偏移量：0x48）调试单元FORCE_NRST寄存器--------
#define AT91C_US_FORCE_NTRST  ((unsigned int) 0x1 <<  0) // JTAG中的（DBGU）部队NTRST

// *****************************************************************************
//              并行输入输出控制器的软件API定义
// *****************************************************************************
typedef struct _AT91S_PIO {
	AT91_REG	 PIO_PER; 	// PIO启用寄存器
	AT91_REG	 PIO_PDR; 	// PIO禁用寄存器
	AT91_REG	 PIO_PSR; 	// PIO状态寄存器
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PIO_OER; 	// 输出启用寄存器
	AT91_REG	 PIO_ODR; 	// 输出禁用寄存器
	AT91_REG	 PIO_OSR; 	// 输出状态寄存器
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PIO_IFER; 	// 输入滤波器启用寄存器
	AT91_REG	 PIO_IFDR; 	// 输入滤波器禁用寄存器
	AT91_REG	 PIO_IFSR; 	// 输入过滤器状态寄存器
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 PIO_SODR; 	// 设置输出数据寄存器
	AT91_REG	 PIO_CODR; 	// 清除输出数据寄存器
	AT91_REG	 PIO_ODSR; 	// 输出数据状态寄存器
	AT91_REG	 PIO_PDSR; 	// 引脚数据状态寄存器
	AT91_REG	 PIO_IER; 	// 中断启用寄存器
	AT91_REG	 PIO_IDR; 	// 中断禁用寄存器
	AT91_REG	 PIO_IMR; 	// 中断掩码寄存器
	AT91_REG	 PIO_ISR; 	// 中断状态寄存器
	AT91_REG	 PIO_MDER; 	// 多驱动程序启用寄存器
	AT91_REG	 PIO_MDDR; 	// 多驱动程序禁用寄存器
	AT91_REG	 PIO_MDSR; 	// 多驱动程序状态寄存器
	AT91_REG	 Reserved3[1]; 	// 
	AT91_REG	 PIO_PPUDR; 	// 上拉禁用寄存器
	AT91_REG	 PIO_PPUER; 	// 上拉启用寄存器
	AT91_REG	 PIO_PPUSR; 	// 拉起状态寄存器
	AT91_REG	 Reserved4[1]; 	// 
	AT91_REG	 PIO_ASR; 	// 选择一个寄存器
	AT91_REG	 PIO_BSR; 	// 选择B寄存器
	AT91_REG	 PIO_ABSR; 	// AB选择状态寄存器
	AT91_REG	 Reserved5[9]; 	// 
	AT91_REG	 PIO_OWER; 	// 输出写入启用寄存器
	AT91_REG	 PIO_OWDR; 	// 输出写入禁用寄存器
	AT91_REG	 PIO_OWSR; 	// 输出写入状态寄存器
} AT91S_PIO, *AT91PS_PIO;


// *****************************************************************************
//              时钟发生器控制器的软件API定义
// *****************************************************************************
typedef struct _AT91S_CKGR {
	AT91_REG	 CKGR_MOR; 	// 主振荡器寄存器
	AT91_REG	 CKGR_MCFR; 	// 主时钟频率寄存器
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 CKGR_PLLR; 	// PLL寄存器
} AT91S_CKGR, *AT91PS_CKGR;

// --------CKGR_MOR:（CKGR偏移：0x0）主振荡器寄存器--------
#define AT91C_CKGR_MOSCEN     ((unsigned int) 0x1 <<  0) // （CKGR）主振荡器启用
#define AT91C_CKGR_OSCBYPASS  ((unsigned int) 0x1 <<  1) // （CKGR）主振荡器旁路
#define AT91C_CKGR_OSCOUNT    ((unsigned int) 0xFF <<  8) // （CKGR）主振荡器启动时间
// --------CKGR_MCFR：（CKGR偏移：0x4）主时钟频率寄存器--------
#define AT91C_CKGR_MAINF      ((unsigned int) 0xFFFF <<  0) // （CKGR）主时钟频率
#define AT91C_CKGR_MAINRDY    ((unsigned int) 0x1 << 16) // （CKGR）主时钟就绪
// --------CKGR_PLLR：（CKGR偏移：0xc）PLL B寄存器--------
#define AT91C_CKGR_DIV        ((unsigned int) 0xFF <<  0) // 已选择（CKGR）分频器
#define 	AT91C_CKGR_DIV_0                    ((unsigned int) 0x0) // （CKGR）除法器输出为0
#define 	AT91C_CKGR_DIV_BYPASS               ((unsigned int) 0x1) // （CKGR）分流器旁通
#define AT91C_CKGR_PLLCOUNT   ((unsigned int) 0x3F <<  8) // （CKGR）PLL计数器
#define AT91C_CKGR_OUT        ((unsigned int) 0x3 << 14) // （CKGR）PLL输出频率范围
#define 	AT91C_CKGR_OUT_0                    ((unsigned int) 0x0 << 14) // （CKGR）请参考PLL数据表
#define 	AT91C_CKGR_OUT_1                    ((unsigned int) 0x1 << 14) // （CKGR）请参考PLL数据表
#define 	AT91C_CKGR_OUT_2                    ((unsigned int) 0x2 << 14) // （CKGR）请参考PLL数据表
#define 	AT91C_CKGR_OUT_3                    ((unsigned int) 0x3 << 14) // （CKGR）请参考PLL数据表
#define AT91C_CKGR_MUL        ((unsigned int) 0x7FF << 16) // （CKGR）PLL乘法器
#define AT91C_CKGR_USBDIV     ((unsigned int) 0x3 << 28) // （CKGR）USB时钟分频器
#define 	AT91C_CKGR_USBDIV_0                    ((unsigned int) 0x0 << 28) // （CKGR）分频器输出为PLL时钟输出
#define 	AT91C_CKGR_USBDIV_1                    ((unsigned int) 0x1 << 28) // （CKGR）分频器输出是PLL时钟输出除以2
#define 	AT91C_CKGR_USBDIV_2                    ((unsigned int) 0x2 << 28) // （CKGR）分频器输出是PLL时钟输出除以4

// *****************************************************************************
//              电源管理控制器的软件API定义
// *****************************************************************************
typedef struct _AT91S_PMC {
	AT91_REG	 PMC_SCER; 	// 系统时钟启用寄存器
	AT91_REG	 PMC_SCDR; 	// 系统时钟禁用寄存器
	AT91_REG	 PMC_SCSR; 	// 系统时钟状态寄存器
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PMC_PCER; 	// 外围时钟启用寄存器
	AT91_REG	 PMC_PCDR; 	// 外围时钟禁用寄存器
	AT91_REG	 PMC_PCSR; 	// 外围时钟状态寄存器
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PMC_MOR; 	// 主振荡器寄存器
	AT91_REG	 PMC_MCFR; 	// 主时钟频率寄存器
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 PMC_PLLR; 	// PLL寄存器
	AT91_REG	 PMC_MCKR; 	// 主时钟寄存器
	AT91_REG	 Reserved3[3]; 	// 
	AT91_REG	 PMC_PCKR[4]; 	// 可编程时钟寄存器
	AT91_REG	 Reserved4[4]; 	// 
	AT91_REG	 PMC_IER; 	// 中断启用寄存器
	AT91_REG	 PMC_IDR; 	// 中断禁用寄存器
	AT91_REG	 PMC_SR; 	// 状态寄存器
	AT91_REG	 PMC_IMR; 	// 中断掩码寄存器
} AT91S_PMC, *AT91PS_PMC;

// --------PMC_SCER：（PMC偏移：0x0）系统时钟启用寄存器--------
#define AT91C_PMC_PCK         ((unsigned int) 0x1 <<  0) // （PMC）处理器时钟
#define AT91C_PMC_UDP         ((unsigned int) 0x1 <<  7) // （PMC）USB设备端口时钟
#define AT91C_PMC_PCK0        ((unsigned int) 0x1 <<  8) // （PMC）可编程时钟输出
#define AT91C_PMC_PCK1        ((unsigned int) 0x1 <<  9) // （PMC）可编程时钟输出
#define AT91C_PMC_PCK2        ((unsigned int) 0x1 << 10) // （PMC）可编程时钟输出
#define AT91C_PMC_PCK3        ((unsigned int) 0x1 << 11) // （PMC）可编程时钟输出
// --------PMC_SCDR：（PMC偏移：0x4）系统时钟禁用寄存器--------
// --------PMC_SCSR：（PMC偏移：0x8）系统时钟状态寄存器--------
// --------CKGR_MOR:（PMC偏移：0x20）主振荡器寄存器--------
// --------CKGR_MCFR：（PMC偏移：0x24）主时钟频率寄存器--------
// --------CKGR_PLLR：（PMC偏移：0x2c）PLL B寄存器--------
// --------PMC_MCKR：（PMC偏移：0x30）主时钟寄存器--------
#define AT91C_PMC_CSS         ((unsigned int) 0x3 <<  0) // （PMC）可编程时钟选择
#define 	AT91C_PMC_CSS_SLOW_CLK             ((unsigned int) 0x0) // （PMC）选择慢速时钟
#define 	AT91C_PMC_CSS_MAIN_CLK             ((unsigned int) 0x1) // （PMC）选择主时钟
#define 	AT91C_PMC_CSS_PLL_CLK              ((unsigned int) 0x3) // （PMC）选择PLL时钟
#define AT91C_PMC_PRES        ((unsigned int) 0x7 <<  2) // （PMC）可编程时钟预分频器
#define 	AT91C_PMC_PRES_CLK                  ((unsigned int) 0x0 <<  2) // （PMC）所选时钟
#define 	AT91C_PMC_PRES_CLK_2                ((unsigned int) 0x1 <<  2) // （PMC）所选时钟除以2
#define 	AT91C_PMC_PRES_CLK_4                ((unsigned int) 0x2 <<  2) // （PMC）所选时钟除以4
#define 	AT91C_PMC_PRES_CLK_8                ((unsigned int) 0x3 <<  2) // （PMC）所选时钟除以8
#define 	AT91C_PMC_PRES_CLK_16               ((unsigned int) 0x4 <<  2) // （PMC）所选时钟除以16
#define 	AT91C_PMC_PRES_CLK_32               ((unsigned int) 0x5 <<  2) // （PMC）所选时钟除以32
#define 	AT91C_PMC_PRES_CLK_64               ((unsigned int) 0x6 <<  2) // （PMC）所选时钟除以64
// --------PMC_PCKR：（PMC偏移：0x40）可编程时钟寄存器--------
// --------PMC_IER：（PMC偏移：0x60）PMC中断启用寄存器--------
#define AT91C_PMC_MOSCS       ((unsigned int) 0x1 <<  0) // （PMC）MOSC状态/启用/禁用/掩码
#define AT91C_PMC_LOCK        ((unsigned int) 0x1 <<  2) // （PMC）PLL状态/启用/禁用/屏蔽
#define AT91C_PMC_MCKRDY      ((unsigned int) 0x1 <<  3) // （PMC）MCK_RDY状态/启用/禁用/掩码
#define AT91C_PMC_PCK0RDY     ((unsigned int) 0x1 <<  8) // （PMC）PCK0_RDY状态/启用/禁用/屏蔽
#define AT91C_PMC_PCK1RDY     ((unsigned int) 0x1 <<  9) // （PMC）PCK1_RDY状态/启用/禁用/屏蔽
#define AT91C_PMC_PCK2RDY     ((unsigned int) 0x1 << 10) // （PMC）PCK2_RDY状态/启用/禁用/屏蔽
#define AT91C_PMC_PCK3RDY     ((unsigned int) 0x1 << 11) // （PMC）PCK3_RDY状态/启用/禁用/屏蔽
// --------PMC_IDR：（PMC偏移：0x64）PMC中断禁用寄存器--------
// --------PMC_SR：（PMC偏移量：0x68）PMC状态寄存器--------
// --------PMC_IMR：（PMC偏移：0x6c）PMC中断掩码寄存器--------

// *****************************************************************************
//              重置控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_RSTC {
	AT91_REG	 RSTC_RCR; 	// 重置控制寄存器
	AT91_REG	 RSTC_RSR; 	// 重置状态寄存器
	AT91_REG	 RSTC_RMR; 	// 重置模式寄存器
} AT91S_RSTC, *AT91PS_RSTC;

// --------RSTC_RCR：（RSTC偏移：0x0）重置控制寄存器--------
#define AT91C_RSTC_PROCRST    ((unsigned int) 0x1 <<  0) // （RSTC）处理器重置
#define AT91C_RSTC_PERRST     ((unsigned int) 0x1 <<  2) // （RSTC）外围设备重置
#define AT91C_RSTC_EXTRST     ((unsigned int) 0x1 <<  3) // （RSTC）外部复位
#define AT91C_RSTC_KEY        ((unsigned int) 0xFF << 24) // （RSTC）密码
// --------RSTC_RSR：（RSTC偏移：0x4）重置状态寄存器--------
#define AT91C_RSTC_URSTS      ((unsigned int) 0x1 <<  0) // （RSTC）用户重置状态
#define AT91C_RSTC_BODSTS     ((unsigned int) 0x1 <<  1) // （RSTC）电量不足检测状态
#define AT91C_RSTC_RSTTYP     ((unsigned int) 0x7 <<  8) // （RSTC）重置类型
#define 	AT91C_RSTC_RSTTYP_POWERUP              ((unsigned int) 0x0 <<  8) // （RSTC）加电复位。VDDCORE上升。
#define 	AT91C_RSTC_RSTTYP_WAKEUP               ((unsigned int) 0x1 <<  8) // （RSTC）唤醒重置。VDDCORE上升。
#define 	AT91C_RSTC_RSTTYP_WATCHDOG             ((unsigned int) 0x2 <<  8) // （RSTC）监视器重置。发生看门狗溢出。
#define 	AT91C_RSTC_RSTTYP_SOFTWARE             ((unsigned int) 0x3 <<  8) // （RSTC）软件重置。软件要求处理器复位。
#define 	AT91C_RSTC_RSTTYP_USER                 ((unsigned int) 0x4 <<  8) // （RSTC）用户重置。检测到NRST引脚过低。
#define 	AT91C_RSTC_RSTTYP_BROWNOUT             ((unsigned int) 0x5 <<  8) // （RSTC）发生断电重置。
#define AT91C_RSTC_NRSTL      ((unsigned int) 0x1 << 16) // （RSTC）NRST引脚电平
#define AT91C_RSTC_SRCMP      ((unsigned int) 0x1 << 17) // （RSTC）软件重置命令正在进行。
// --------RSTC_RMR：（RSTC偏移：0x8）重置模式寄存器--------
#define AT91C_RSTC_URSTEN     ((unsigned int) 0x1 <<  0) // （RSTC）用户重置启用
#define AT91C_RSTC_URSTIEN    ((unsigned int) 0x1 <<  4) // （RSTC）用户重置中断启用
#define AT91C_RSTC_ERSTL      ((unsigned int) 0xF <<  8) // （RSTC）用户重置长度
#define AT91C_RSTC_BODIEN     ((unsigned int) 0x1 << 16) // （RSTC）断电检测中断启用

// *****************************************************************************
//              实时定时器控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_RTTC {
	AT91_REG	 RTTC_RTMR; 	// 实时模式寄存器
	AT91_REG	 RTTC_RTAR; 	// 实时报警寄存器
	AT91_REG	 RTTC_RTVR; 	// 实时值寄存器
	AT91_REG	 RTTC_RTSR; 	// 实时状态寄存器
} AT91S_RTTC, *AT91PS_RTTC;

// --------RTTC_RTMR：（RTTC偏移：0x0）实时模式寄存器--------
#define AT91C_RTTC_RTPRES     ((unsigned int) 0xFFFF <<  0) // （RTTC）实时计时器预分频器值
#define AT91C_RTTC_ALMIEN     ((unsigned int) 0x1 << 16) // （RTTC）报警中断启用
#define AT91C_RTTC_RTTINCIEN  ((unsigned int) 0x1 << 17) // （RTTC）实时定时器增量中断启用
#define AT91C_RTTC_RTTRST     ((unsigned int) 0x1 << 18) // （RTTC）实时计时器重启
// --------RTTC_RTAR：（RTTC偏移：0x4）实时报警寄存器--------
#define AT91C_RTTC_ALMV       ((unsigned int) 0x0 <<  0) // （RTTC）报警值
// --------RTTC_RTVR：（RTTC偏移：0x8）当前实时值寄存器--------
#define AT91C_RTTC_CRTV       ((unsigned int) 0x0 <<  0) // （RTTC）当前实时值
// --------RTTC_RTSR：（RTTC偏移：0xc）实时状态寄存器--------
#define AT91C_RTTC_ALMS       ((unsigned int) 0x1 <<  0) // （RTTC）实时报警状态
#define AT91C_RTTC_RTTINC     ((unsigned int) 0x1 <<  1) // （RTTC）实时计时器增量

// *****************************************************************************
//              周期间隔定时器控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_PITC {
	AT91_REG	 PITC_PIMR; 	// 周期间隔模式寄存器
	AT91_REG	 PITC_PISR; 	// 周期间隔状态寄存器
	AT91_REG	 PITC_PIVR; 	// 周期间隔值寄存器
	AT91_REG	 PITC_PIIR; 	// 周期间隔图像寄存器
} AT91S_PITC, *AT91PS_PITC;

// --------PITC_PIR:（PITC偏移：0x0）周期间隔模式寄存器--------
#define AT91C_PITC_PIV        ((unsigned int) 0xFFFFF <<  0) // （PITC）周期间隔值
#define AT91C_PITC_PITEN      ((unsigned int) 0x1 << 24) // （PITC）周期间隔计时器已启用
#define AT91C_PITC_PITIEN     ((unsigned int) 0x1 << 25) // （PITC）周期间隔定时器中断启用
// --------PITC_PISR:（PITC偏移量：0x4）周期间隔状态寄存器--------
#define AT91C_PITC_PITS       ((unsigned int) 0x1 <<  0) // （PITC）周期间隔计时器状态
// --------PITC_PIVR：（PITC偏移量：0x8）周期间隔值寄存器--------
#define AT91C_PITC_CPIV       ((unsigned int) 0xFFFFF <<  0) // （PITC）当前周期间隔值
#define AT91C_PITC_PICNT      ((unsigned int) 0xFFF << 20) // （PITC）周期间隔计数器
// --------PITC_PIR:（PITC偏移：0xc）周期间隔图像寄存器--------

// *****************************************************************************
//              看门狗定时器控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_WDTC {
	AT91_REG	 WDTC_WDCR; 	// 看门狗控制寄存器
	AT91_REG	 WDTC_WDMR; 	// 看门狗模式寄存器
	AT91_REG	 WDTC_WDSR; 	// 看门狗状态寄存器
} AT91S_WDTC, *AT91PS_WDTC;

// --------WDTC_WDCR：（WDTC偏移：0x0）周期间隔图像寄存器--------
#define AT91C_WDTC_WDRSTT     ((unsigned int) 0x1 <<  0) // （WDTC）监视器重新启动
#define AT91C_WDTC_KEY        ((unsigned int) 0xFF << 24) // （WDTC）看门狗密钥密码
// --------WDTC_WDMR：（WDTC偏移：0x4）看门狗模式寄存器--------
#define AT91C_WDTC_WDV        ((unsigned int) 0xFFF <<  0) // （WDTC）看门狗计时器重新启动
#define AT91C_WDTC_WDFIEN     ((unsigned int) 0x1 << 12) // （WDTC）看门狗故障中断启用
#define AT91C_WDTC_WDRSTEN    ((unsigned int) 0x1 << 13) // （WDTC）监视器重置启用
#define AT91C_WDTC_WDRPROC    ((unsigned int) 0x1 << 14) // （WDTC）看门狗计时器重新启动
#define AT91C_WDTC_WDDIS      ((unsigned int) 0x1 << 15) // （WDTC）看门狗禁用
#define AT91C_WDTC_WDD        ((unsigned int) 0xFFF << 16) // （WDTC）看门狗增量值
#define AT91C_WDTC_WDDBGHLT   ((unsigned int) 0x1 << 28) // （WDTC）监视器调试停止
#define AT91C_WDTC_WDIDLEHLT  ((unsigned int) 0x1 << 29) // （WDTC）看门狗空闲停止
// --------WDTC_WDSR:（WDTC偏移量：0x8）看门狗状态寄存器--------
#define AT91C_WDTC_WDUNF      ((unsigned int) 0x1 <<  0) // （WDTC）看门狗欠流
#define AT91C_WDTC_WDERR      ((unsigned int) 0x1 <<  1) // （WDTC）看门狗错误

// *****************************************************************************
//              稳压器模式控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_VREG {
	AT91_REG	 VREG_MR; 	// 电压调节器模式寄存器
} AT91S_VREG, *AT91PS_VREG;

// --------VREG_MR：（VREG偏移：0x0）电压调节器模式寄存器--------
#define AT91C_VREG_PSTDBY     ((unsigned int) 0x1 <<  0) // （VREG）电压调节器电源待机模式

// *****************************************************************************
//              存储器控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_MC {
	AT91_REG	 MC_RCR; 	// MC重映射控制寄存器
	AT91_REG	 MC_ASR; 	// MC中止状态寄存器
	AT91_REG	 MC_AASR; 	// MC中止地址状态寄存器
	AT91_REG	 Reserved0[21]; 	// 
	AT91_REG	 MC_FMR; 	// MC闪存模式寄存器
	AT91_REG	 MC_FCR; 	// MC闪存命令寄存器
	AT91_REG	 MC_FSR; 	// MC闪存状态寄存器
} AT91S_MC, *AT91PS_MC;

// --------MC_RCR：（MC偏移：0x0）MC重映射控制寄存器--------
#define AT91C_MC_RCB          ((unsigned int) 0x1 <<  0) // （MC）重映射命令位
// --------MC_ASR:（MC偏移量：0x4）MC中止状态寄存器--------
#define AT91C_MC_UNDADD       ((unsigned int) 0x1 <<  0) // （MC）未定义的地址中止状态
#define AT91C_MC_MISADD       ((unsigned int) 0x1 <<  1) // （MC）地址错误中止状态
#define AT91C_MC_ABTSZ        ((unsigned int) 0x3 <<  8) // （MC）中止大小状态
#define 	AT91C_MC_ABTSZ_BYTE                 ((unsigned int) 0x0 <<  8) // （MC）字节
#define 	AT91C_MC_ABTSZ_HWORD                ((unsigned int) 0x1 <<  8) // （MC）半字
#define 	AT91C_MC_ABTSZ_WORD                 ((unsigned int) 0x2 <<  8) // （MC）字
#define AT91C_MC_ABTTYP       ((unsigned int) 0x3 << 10) // （MC）中止类型状态
#define 	AT91C_MC_ABTTYP_DATAR                ((unsigned int) 0x0 << 10) // （MC）数据读取
#define 	AT91C_MC_ABTTYP_DATAW                ((unsigned int) 0x1 << 10) // （MC）数据写入
#define 	AT91C_MC_ABTTYP_FETCH                ((unsigned int) 0x2 << 10) // （MC）代码获取
#define AT91C_MC_MST0         ((unsigned int) 0x1 << 16) // （MC）主机0中止源
#define AT91C_MC_MST1         ((unsigned int) 0x1 << 17) // （MC）主1中止源
#define AT91C_MC_SVMST0       ((unsigned int) 0x1 << 24) // （MC）保存的主机0中止源
#define AT91C_MC_SVMST1       ((unsigned int) 0x1 << 25) // （MC）保存的主1中止源
// --------MC_FMR：（MC偏移：0x60）MC闪存模式寄存器--------
#define AT91C_MC_FRDY         ((unsigned int) 0x1 <<  0) // （MC）闪存就绪
#define AT91C_MC_LOCKE        ((unsigned int) 0x1 <<  2) // （MC）锁定错误
#define AT91C_MC_PROGE        ((unsigned int) 0x1 <<  3) // （MC）编程错误
#define AT91C_MC_NEBP         ((unsigned int) 0x1 <<  7) // （MC）编程前无擦除
#define AT91C_MC_FWS          ((unsigned int) 0x3 <<  8) // （MC）闪存等待状态
#define 	AT91C_MC_FWS_0FWS                 ((unsigned int) 0x0 <<  8) // （MC）1个周期用于读取，2个周期用于写入操作
#define 	AT91C_MC_FWS_1FWS                 ((unsigned int) 0x1 <<  8) // （MC）读取操作2个周期，写入操作3个周期
#define 	AT91C_MC_FWS_2FWS                 ((unsigned int) 0x2 <<  8) // （MC）3个周期用于读取，4个周期用于写入操作
#define 	AT91C_MC_FWS_3FWS                 ((unsigned int) 0x3 <<  8) // （MC）读操作4个周期，写操作4个
#define AT91C_MC_FMCN         ((unsigned int) 0xFF << 16) // （MC）闪存微秒循环数
// --------MC_FCR：（MC偏移：0x64）MC闪存命令寄存器--------
#define AT91C_MC_FCMD         ((unsigned int) 0xF <<  0) // （MC）闪存命令
#define 	AT91C_MC_FCMD_START_PROG           ((unsigned int) 0x1) // （MC）启动PAGEN指定页的编程。
#define 	AT91C_MC_FCMD_LOCK                 ((unsigned int) 0x2) // （MC）开始由字段PAGEN的位4至7定义的扇区的锁定序列。
#define 	AT91C_MC_FCMD_PROG_AND_LOCK        ((unsigned int) 0x3) // （MC）编程序列完成后，锁定序列自动发生。
#define 	AT91C_MC_FCMD_UNLOCK               ((unsigned int) 0x4) // （MC）开始由字段PAGEN的位4至7定义的扇区的解锁序列。
#define 	AT91C_MC_FCMD_ERASE_ALL            ((unsigned int) 0x8) // （MC）开始擦除整个闪存。如果至少有一个页面被锁定，则该命令将被取消。
#define 	AT91C_MC_FCMD_SET_GP_NVM           ((unsigned int) 0xB) // （MC）设置通用NVM位。
#define 	AT91C_MC_FCMD_CLR_GP_NVM           ((unsigned int) 0xD) // （MC）清除通用NVM位。
#define 	AT91C_MC_FCMD_SET_SECURITY         ((unsigned int) 0xF) // （MC）设置安全位。
#define AT91C_MC_PAGEN        ((unsigned int) 0x3FF <<  8) // （MC）页码
#define AT91C_MC_KEY          ((unsigned int) 0xFF << 24) // （MC）写入保护密钥
// --------MC_FSR:（MC偏移：0x68）MC闪存命令寄存器--------
#define AT91C_MC_SECURITY     ((unsigned int) 0x1 <<  4) // （MC）安全位状态
#define AT91C_MC_GPNVM0       ((unsigned int) 0x1 <<  8) // （MC）扇区0锁定状态
#define AT91C_MC_GPNVM1       ((unsigned int) 0x1 <<  9) // （MC）扇区1锁定状态
#define AT91C_MC_GPNVM2       ((unsigned int) 0x1 << 10) // （MC）扇区2锁定状态
#define AT91C_MC_GPNVM3       ((unsigned int) 0x1 << 11) // （MC）扇区3锁定状态
#define AT91C_MC_GPNVM4       ((unsigned int) 0x1 << 12) // （MC）扇区4锁定状态
#define AT91C_MC_GPNVM5       ((unsigned int) 0x1 << 13) // （MC）扇区5锁定状态
#define AT91C_MC_GPNVM6       ((unsigned int) 0x1 << 14) // （MC）扇区6锁定状态
#define AT91C_MC_GPNVM7       ((unsigned int) 0x1 << 15) // （MC）扇区7锁定状态
#define AT91C_MC_LOCKS0       ((unsigned int) 0x1 << 16) // （MC）扇区0锁定状态
#define AT91C_MC_LOCKS1       ((unsigned int) 0x1 << 17) // （MC）扇区1锁定状态
#define AT91C_MC_LOCKS2       ((unsigned int) 0x1 << 18) // （MC）扇区2锁定状态
#define AT91C_MC_LOCKS3       ((unsigned int) 0x1 << 19) // （MC）扇区3锁定状态
#define AT91C_MC_LOCKS4       ((unsigned int) 0x1 << 20) // （MC）扇区4锁定状态
#define AT91C_MC_LOCKS5       ((unsigned int) 0x1 << 21) // （MC）扇区5锁定状态
#define AT91C_MC_LOCKS6       ((unsigned int) 0x1 << 22) // （MC）扇区6锁定状态
#define AT91C_MC_LOCKS7       ((unsigned int) 0x1 << 23) // （MC）扇区7锁定状态
#define AT91C_MC_LOCKS8       ((unsigned int) 0x1 << 24) // （MC）扇区8锁定状态
#define AT91C_MC_LOCKS9       ((unsigned int) 0x1 << 25) // （MC）扇区9锁定状态
#define AT91C_MC_LOCKS10      ((unsigned int) 0x1 << 26) // （MC）扇区10锁定状态
#define AT91C_MC_LOCKS11      ((unsigned int) 0x1 << 27) // （MC）扇区11锁定状态
#define AT91C_MC_LOCKS12      ((unsigned int) 0x1 << 28) // （MC）扇区12锁定状态
#define AT91C_MC_LOCKS13      ((unsigned int) 0x1 << 29) // （MC）扇区13锁定状态
#define AT91C_MC_LOCKS14      ((unsigned int) 0x1 << 30) // （MC）扇区14锁定状态
#define AT91C_MC_LOCKS15      ((unsigned int) 0x1 << 31) // （MC）扇区15锁定状态

// *****************************************************************************
//              串行并行接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_SPI {
	AT91_REG	 SPI_CR; 	// 控制寄存器
	AT91_REG	 SPI_MR; 	// 模式寄存器
	AT91_REG	 SPI_RDR; 	// 接收数据寄存器
	AT91_REG	 SPI_TDR; 	// 传输数据寄存器
	AT91_REG	 SPI_SR; 	// 状态寄存器
	AT91_REG	 SPI_IER; 	// 中断启用寄存器
	AT91_REG	 SPI_IDR; 	// 中断禁用寄存器
	AT91_REG	 SPI_IMR; 	// 中断掩码寄存器
	AT91_REG	 Reserved0[4]; 	// 
	AT91_REG	 SPI_CSR[4]; 	// 芯片选择寄存器
	AT91_REG	 Reserved1[48]; 	// 
	AT91_REG	 SPI_RPR; 	// 接收指针寄存器
	AT91_REG	 SPI_RCR; 	// 接收计数器寄存器
	AT91_REG	 SPI_TPR; 	// 发送指针寄存器
	AT91_REG	 SPI_TCR; 	// 发送计数器寄存器
	AT91_REG	 SPI_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 SPI_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 SPI_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 SPI_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 SPI_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 SPI_PTSR; 	// PDC传输状态寄存器
} AT91S_SPI, *AT91PS_SPI;

// --------SPI_CR：（SPI偏移：0x0）SPI控制寄存器--------
#define AT91C_SPI_SPIEN       ((unsigned int) 0x1 <<  0) // （SPI）SPI启用
#define AT91C_SPI_SPIDIS      ((unsigned int) 0x1 <<  1) // （SPI）SPI禁用
#define AT91C_SPI_SWRST       ((unsigned int) 0x1 <<  7) // （SPI）SPI软件复位
#define AT91C_SPI_LASTXFER    ((unsigned int) 0x1 << 24) // （SPI）SPI上次传输
// --------SPI_MR：（SPI偏移量：0x4）SPI模式寄存器--------
#define AT91C_SPI_MSTR        ((unsigned int) 0x1 <<  0) // （SPI）主/从模式
#define AT91C_SPI_PS          ((unsigned int) 0x1 <<  1) // （SPI）外围设备选择
#define 	AT91C_SPI_PS_FIXED                ((unsigned int) 0x0 <<  1) // （SPI）固定外设选择
#define 	AT91C_SPI_PS_VARIABLE             ((unsigned int) 0x1 <<  1) // （SPI）可变外围设备选择
#define AT91C_SPI_PCSDEC      ((unsigned int) 0x1 <<  2) // （SPI）芯片选择解码
#define AT91C_SPI_FDIV        ((unsigned int) 0x1 <<  3) // （SPI）时钟选择
#define AT91C_SPI_MODFDIS     ((unsigned int) 0x1 <<  4) // （SPI）模式故障检测
#define AT91C_SPI_LLB         ((unsigned int) 0x1 <<  7) // （SPI）时钟选择
#define AT91C_SPI_PCS         ((unsigned int) 0xF << 16) // （SPI）外围芯片选择
#define AT91C_SPI_DLYBCS      ((unsigned int) 0xFF << 24) // 芯片选择之间的（SPI）延迟
// --------SPI_RDR:（SPI偏移量：0x8）接收数据寄存器--------
#define AT91C_SPI_RD          ((unsigned int) 0xFFFF <<  0) // （SPI）接收数据
#define AT91C_SPI_RPCS        ((unsigned int) 0xF << 16) // （SPI）外围芯片选择状态
// --------SPI_TDR：（SPI偏移量：0xc）传输数据寄存器--------
#define AT91C_SPI_TD          ((unsigned int) 0xFFFF <<  0) // （SPI）传输数据
#define AT91C_SPI_TPCS        ((unsigned int) 0xF << 16) // （SPI）外围芯片选择状态
// --------SPI_SR：（SPI偏移量：0x10）状态寄存器--------
#define AT91C_SPI_RDRF        ((unsigned int) 0x1 <<  0) // （SPI）接收数据寄存器已满
#define AT91C_SPI_TDRE        ((unsigned int) 0x1 <<  1) // （SPI）传输数据寄存器为空
#define AT91C_SPI_MODF        ((unsigned int) 0x1 <<  2) // （SPI）模式故障错误
#define AT91C_SPI_OVRES       ((unsigned int) 0x1 <<  3) // （SPI）超限错误状态
#define AT91C_SPI_ENDRX       ((unsigned int) 0x1 <<  4) // （SPI）接收器传输结束
#define AT91C_SPI_ENDTX       ((unsigned int) 0x1 <<  5) // （SPI）接收器传输结束
#define AT91C_SPI_RXBUFF      ((unsigned int) 0x1 <<  6) // （SPI）RXBUFF中断
#define AT91C_SPI_TXBUFE      ((unsigned int) 0x1 <<  7) // （SPI）TXBUFE中断
#define AT91C_SPI_NSSR        ((unsigned int) 0x1 <<  8) // （SPI）NSSR中断
#define AT91C_SPI_TXEMPTY     ((unsigned int) 0x1 <<  9) // （SPI）TXEMPTY中断
#define AT91C_SPI_SPIENS      ((unsigned int) 0x1 << 16) // （SPI）启用状态
// --------SPI_IER：（SPI偏移：0x14）中断启用寄存器--------
// --------SPI_IDR：（SPI偏移量：0x18）中断禁用寄存器--------
// --------SPI_IMR：（SPI偏移量：0x1c）中断掩码寄存器--------
// --------SPI_CSR:（SPI偏移：0x30）芯片选择寄存器--------
#define AT91C_SPI_CPOL        ((unsigned int) 0x1 <<  0) // （SPI）时钟极性
#define AT91C_SPI_NCPHA       ((unsigned int) 0x1 <<  1) // （SPI）时钟相位
#define AT91C_SPI_CSAAT       ((unsigned int) 0x1 <<  3) // 传输后激活（SPI）芯片选择
#define AT91C_SPI_BITS        ((unsigned int) 0xF <<  4) // （SPI）每次传输位
#define 	AT91C_SPI_BITS_8                    ((unsigned int) 0x0 <<  4) // （SPI）每次传输8位
#define 	AT91C_SPI_BITS_9                    ((unsigned int) 0x1 <<  4) // （SPI）每次传输9位
#define 	AT91C_SPI_BITS_10                   ((unsigned int) 0x2 <<  4) // （SPI）每次传输10位
#define 	AT91C_SPI_BITS_11                   ((unsigned int) 0x3 <<  4) // （SPI）每次传输11位
#define 	AT91C_SPI_BITS_12                   ((unsigned int) 0x4 <<  4) // （SPI）每次传输12位
#define 	AT91C_SPI_BITS_13                   ((unsigned int) 0x5 <<  4) // （SPI）每次传输13位
#define 	AT91C_SPI_BITS_14                   ((unsigned int) 0x6 <<  4) // （SPI）每次传输14位
#define 	AT91C_SPI_BITS_15                   ((unsigned int) 0x7 <<  4) // （SPI）每次传输15位
#define 	AT91C_SPI_BITS_16                   ((unsigned int) 0x8 <<  4) // （SPI）每次传输16位
#define AT91C_SPI_SCBR        ((unsigned int) 0xFF <<  8) // （SPI）串行时钟波特率
#define AT91C_SPI_DLYBS       ((unsigned int) 0xFF << 16) // SPCK之前的（SPI）延迟
#define AT91C_SPI_DLYBCT      ((unsigned int) 0xFF << 24) // （SPI）连续传输之间的延迟

// *****************************************************************************
//              用于Usart的软件API定义
// *****************************************************************************
typedef struct _AT91S_USART {
	AT91_REG	 US_CR; 	// 控制寄存器
	AT91_REG	 US_MR; 	// 模式寄存器
	AT91_REG	 US_IER; 	// 中断启用寄存器
	AT91_REG	 US_IDR; 	// 中断禁用寄存器
	AT91_REG	 US_IMR; 	// 中断掩码寄存器
	AT91_REG	 US_CSR; 	// 信道状态寄存器
	AT91_REG	 US_RHR; 	// 接收机保持寄存器
	AT91_REG	 US_THR; 	// 变送器保持寄存器
	AT91_REG	 US_BRGR; 	// 波特率发生器寄存器
	AT91_REG	 US_RTOR; 	// 接收机超时寄存器
	AT91_REG	 US_TTGR; 	// 变送器时间保护寄存器
	AT91_REG	 Reserved0[5]; 	// 
	AT91_REG	 US_FIDI; 	// FI_DI_Ratio寄存器
	AT91_REG	 US_NER; 	// Nb错误寄存器
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 US_IF; 	// IRDA_FILTER寄存器
	AT91_REG	 Reserved2[44]; 	// 
	AT91_REG	 US_RPR; 	// 接收指针寄存器
	AT91_REG	 US_RCR; 	// 接收计数器寄存器
	AT91_REG	 US_TPR; 	// 发送指针寄存器
	AT91_REG	 US_TCR; 	// 发送计数器寄存器
	AT91_REG	 US_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 US_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 US_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 US_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 US_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 US_PTSR; 	// PDC传输状态寄存器
} AT91S_USART, *AT91PS_USART;

// --------US_CR：（USART偏移：0x0）调试单元控制寄存器--------
#define AT91C_US_STTBRK       ((unsigned int) 0x1 <<  9) // （USART）开始休息
#define AT91C_US_STPBRK       ((unsigned int) 0x1 << 10) // （USART）停车休息
#define AT91C_US_STTTO        ((unsigned int) 0x1 << 11) // （USART）开始超时
#define AT91C_US_SENDA        ((unsigned int) 0x1 << 12) // （USART）发送地址
#define AT91C_US_RSTIT        ((unsigned int) 0x1 << 13) // （USART）重置迭代
#define AT91C_US_RSTNACK      ((unsigned int) 0x1 << 14) // （USART）重置不确认
#define AT91C_US_RETTO        ((unsigned int) 0x1 << 15) // （USART）重新排列超时
#define AT91C_US_DTREN        ((unsigned int) 0x1 << 16) // （USART）数据终端就绪启用
#define AT91C_US_DTRDIS       ((unsigned int) 0x1 << 17) // （USART）数据终端就绪禁用
#define AT91C_US_RTSEN        ((unsigned int) 0x1 << 18) // （USART）请求发送启用
#define AT91C_US_RTSDIS       ((unsigned int) 0x1 << 19) // （USART）请求发送禁用
// --------US_MR：（USART偏移：0x4）调试单元模式寄存器--------
#define AT91C_US_USMODE       ((unsigned int) 0xF <<  0) // （USART）USART模式
#define 	AT91C_US_USMODE_NORMAL               ((unsigned int) 0x0) // （USART）正常
#define 	AT91C_US_USMODE_RS485                ((unsigned int) 0x1) // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                ((unsigned int) 0x2) // （USART）硬件握手
#define 	AT91C_US_USMODE_MODEM                ((unsigned int) 0x3) // （USART）调制解调器
#define 	AT91C_US_USMODE_ISO7816_0            ((unsigned int) 0x4) // （USART）ISO7816协议：T=0
#define 	AT91C_US_USMODE_ISO7816_1            ((unsigned int) 0x6) // （USART）ISO7816协议：T=1
#define 	AT91C_US_USMODE_IRDA                 ((unsigned int) 0x8) // （USART）伊拉克陆军部
#define 	AT91C_US_USMODE_SWHSH                ((unsigned int) 0xC) // （USART）软件握手
#define AT91C_US_CLKS         ((unsigned int) 0x3 <<  4) // （USART）时钟选择（波特率发生器输入时钟
#define 	AT91C_US_CLKS_CLOCK                ((unsigned int) 0x0 <<  4) // （USART）时钟
#define 	AT91C_US_CLKS_FDIV1                ((unsigned int) 0x1 <<  4) // （美国陆军）fdiv1
#define 	AT91C_US_CLKS_SLOW                 ((unsigned int) 0x2 <<  4) // （USART）慢锁（ARM）
#define 	AT91C_US_CLKS_EXT                  ((unsigned int) 0x3 <<  4) // （USART）外部（SCK）
#define AT91C_US_CHRL         ((unsigned int) 0x3 <<  6) // （USART）时钟选择（波特率发生器输入时钟
#define 	AT91C_US_CHRL_5_BITS               ((unsigned int) 0x0 <<  6) // （USART）字符长度：5位
#define 	AT91C_US_CHRL_6_BITS               ((unsigned int) 0x1 <<  6) // （USART）字符长度：6位
#define 	AT91C_US_CHRL_7_BITS               ((unsigned int) 0x2 <<  6) // （USART）字符长度：7位
#define 	AT91C_US_CHRL_8_BITS               ((unsigned int) 0x3 <<  6) // （USART）字符长度：8位
#define AT91C_US_SYNC         ((unsigned int) 0x1 <<  8) // （USART）同步模式选择
#define AT91C_US_NBSTOP       ((unsigned int) 0x3 << 12) // （USART）停止位数
#define 	AT91C_US_NBSTOP_1_BIT                ((unsigned int) 0x0 << 12) // （USART）1个停止位
#define 	AT91C_US_NBSTOP_15_BIT               ((unsigned int) 0x1 << 12) // （USART）异步（SYNC=0）2个停止位同步（SYNC=1）2个终止位
#define 	AT91C_US_NBSTOP_2_BIT                ((unsigned int) 0x2 << 12) // （USART）2个停止位
#define AT91C_US_MSBF         ((unsigned int) 0x1 << 16) // （USART）位顺序
#define AT91C_US_MODE9        ((unsigned int) 0x1 << 17) // （USART）9位字符长度
#define AT91C_US_CKLO         ((unsigned int) 0x1 << 18) // （USART）时钟输出选择
#define AT91C_US_OVER         ((unsigned int) 0x1 << 19) // （USART）过采样模式
#define AT91C_US_INACK        ((unsigned int) 0x1 << 20) // （USART）禁止不确认
#define AT91C_US_DSNACK       ((unsigned int) 0x1 << 21) // （USART）禁用连续NACK
#define AT91C_US_MAX_ITER     ((unsigned int) 0x1 << 24) // （USART）重复次数
#define AT91C_US_FILTER       ((unsigned int) 0x1 << 28) // （USART）接收线滤波器
// --------US_IER：（USART偏移：0x8）调试单元中断启用寄存器--------
#define AT91C_US_RXBRK        ((unsigned int) 0x1 <<  2) // （USART）休息接收/休息结束
#define AT91C_US_TIMEOUT      ((unsigned int) 0x1 <<  8) // （USART）接收机超时
#define AT91C_US_ITERATION    ((unsigned int) 0x1 << 10) // （USART）达到的最大重复次数
#define AT91C_US_NACK         ((unsigned int) 0x1 << 13) // （USART）不承认
#define AT91C_US_RIIC         ((unsigned int) 0x1 << 16) // （USART）响铃指示器输入更改标志
#define AT91C_US_DSRIC        ((unsigned int) 0x1 << 17) // （USART）数据集就绪输入更改标志
#define AT91C_US_DCDIC        ((unsigned int) 0x1 << 18) // （USART）数据载体标志
#define AT91C_US_CTSIC        ((unsigned int) 0x1 << 19) // （USART）清除以发送输入更改标志
// --------US_IDR：（USART偏移：0xc）调试单元中断禁用寄存器--------
// --------US_IMR：（USART偏移：0x10）调试单元中断掩码寄存器--------
// --------US_CSR:（USART偏移：0x14）调试单元信道状态寄存器--------
#define AT91C_US_RI           ((unsigned int) 0x1 << 20) // （USART）RI输入图像
#define AT91C_US_DSR          ((unsigned int) 0x1 << 21) // （USART）DSR输入图像
#define AT91C_US_DCD          ((unsigned int) 0x1 << 22) // （USART）DCD输入图像
#define AT91C_US_CTS          ((unsigned int) 0x1 << 23) // （USART）CTS输入图像

// *****************************************************************************
//              同步串行控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_SSC {
	AT91_REG	 SSC_CR; 	// 控制寄存器
	AT91_REG	 SSC_CMR; 	// 时钟模式寄存器
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 SSC_RCMR; 	// 接收时钟模式寄存器
	AT91_REG	 SSC_RFMR; 	// 接收帧模式寄存器
	AT91_REG	 SSC_TCMR; 	// 发送时钟模式寄存器
	AT91_REG	 SSC_TFMR; 	// 发送帧模式寄存器
	AT91_REG	 SSC_RHR; 	// 接收保持寄存器
	AT91_REG	 SSC_THR; 	// 发送保持寄存器
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 SSC_RSHR; 	// 接收同步保持寄存器
	AT91_REG	 SSC_TSHR; 	// 传输同步保持寄存器
	AT91_REG	 Reserved2[2]; 	// 
	AT91_REG	 SSC_SR; 	// 状态寄存器
	AT91_REG	 SSC_IER; 	// 中断启用寄存器
	AT91_REG	 SSC_IDR; 	// 中断禁用寄存器
	AT91_REG	 SSC_IMR; 	// 中断掩码寄存器
	AT91_REG	 Reserved3[44]; 	// 
	AT91_REG	 SSC_RPR; 	// 接收指针寄存器
	AT91_REG	 SSC_RCR; 	// 接收计数器寄存器
	AT91_REG	 SSC_TPR; 	// 发送指针寄存器
	AT91_REG	 SSC_TCR; 	// 发送计数器寄存器
	AT91_REG	 SSC_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 SSC_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 SSC_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 SSC_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 SSC_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 SSC_PTSR; 	// PDC传输状态寄存器
} AT91S_SSC, *AT91PS_SSC;

// --------SSC_CR：（SSC偏移：0x0）SSC控制寄存器--------
#define AT91C_SSC_RXEN        ((unsigned int) 0x1 <<  0) // （SSC）接收启用
#define AT91C_SSC_RXDIS       ((unsigned int) 0x1 <<  1) // （SSC）接收禁用
#define AT91C_SSC_TXEN        ((unsigned int) 0x1 <<  8) // （SSC）传输启用
#define AT91C_SSC_TXDIS       ((unsigned int) 0x1 <<  9) // （SSC）发送禁用
#define AT91C_SSC_SWRST       ((unsigned int) 0x1 << 15) // （SSC）软件重置
// --------SSC_RCMR：（SSC偏移：0x10）SSC接收时钟模式寄存器--------
#define AT91C_SSC_CKS         ((unsigned int) 0x3 <<  0) // （SSC）接收/发送时钟选择
#define 	AT91C_SSC_CKS_DIV                  ((unsigned int) 0x0) // （SSC）分频时钟
#define 	AT91C_SSC_CKS_TK                   ((unsigned int) 0x1) // （SSC）TK时钟信号
#define 	AT91C_SSC_CKS_RK                   ((unsigned int) 0x2) // （SSC）RK销
#define AT91C_SSC_CKO         ((unsigned int) 0x7 <<  2) // （SSC）接收/发送时钟输出模式选择
#define 	AT91C_SSC_CKO_NONE                 ((unsigned int) 0x0 <<  2) // （SSC）接收/发送时钟输出模式：无RK引脚：仅输入
#define 	AT91C_SSC_CKO_CONTINOUS            ((unsigned int) 0x1 <<  2) // （SSC）连续接收/发送时钟RK引脚：输出
#define 	AT91C_SSC_CKO_DATA_TX              ((unsigned int) 0x2 <<  2) // （SSC）仅在数据传输期间接收/发送时钟RK引脚：输出
#define AT91C_SSC_CKI         ((unsigned int) 0x1 <<  5) // （SSC）接收/发送时钟反转
#define AT91C_SSC_CKG         ((unsigned int) 0x3 <<  6) // （SSC）接收/发送时钟门控选择
#define 	AT91C_SSC_CKG_NONE                 ((unsigned int) 0x0 <<  6) // （SSC）接收/发送时钟门控：无，连续时钟
#define 	AT91C_SSC_CKG_LOW                  ((unsigned int) 0x1 <<  6) // （SSC）仅在RF低时启用接收/发送时钟
#define 	AT91C_SSC_CKG_HIGH                 ((unsigned int) 0x2 <<  6) // （SSC）仅当RF高时才启用接收/发送时钟
#define AT91C_SSC_START       ((unsigned int) 0xF <<  8) // （SSC）接收/发送开始选择
#define 	AT91C_SSC_START_CONTINOUS            ((unsigned int) 0x0 <<  8) // （SSC）一旦启用接收器，在前一数据传输结束后立即连续。
#define 	AT91C_SSC_START_TX                   ((unsigned int) 0x1 <<  8) // （SSC）发送/接收启动
#define 	AT91C_SSC_START_LOW_RF               ((unsigned int) 0x2 <<  8) // （SSC）射频输入低电平检测
#define 	AT91C_SSC_START_HIGH_RF              ((unsigned int) 0x3 <<  8) // （SSC）射频输入高电平检测
#define 	AT91C_SSC_START_FALL_RF              ((unsigned int) 0x4 <<  8) // （SSC）检测RF输入的下降沿
#define 	AT91C_SSC_START_RISE_RF              ((unsigned int) 0x5 <<  8) // （SSC）检测RF输入上的上升沿
#define 	AT91C_SSC_START_LEVEL_RF             ((unsigned int) 0x6 <<  8) // （SSC）检测射频输入的任何电平变化
#define 	AT91C_SSC_START_EDGE_RF              ((unsigned int) 0x7 <<  8) // （SSC）检测RF输入上的任何边缘
#define 	AT91C_SSC_START_0                    ((unsigned int) 0x8 <<  8) // （SSC）比较0
#define AT91C_SSC_STOP        ((unsigned int) 0x1 << 12) // （SSC）接收停止选择
#define AT91C_SSC_STTDLY      ((unsigned int) 0xFF << 16) // （SSC）接收/发送开始延迟
#define AT91C_SSC_PERIOD      ((unsigned int) 0xFF << 24) // （SSC）接收/发送周期分频器选择
// --------SSC_RFMR：（SSC偏移：0x14）SSC接收帧模式寄存器--------
#define AT91C_SSC_DATLEN      ((unsigned int) 0x1F <<  0) // （SSC）数据长度
#define AT91C_SSC_LOOP        ((unsigned int) 0x1 <<  5) // （SSC）回路模式
#define AT91C_SSC_MSBF        ((unsigned int) 0x1 <<  7) // （SSC）最高有效位优先
#define AT91C_SSC_DATNB       ((unsigned int) 0xF <<  8) // （SSC）每帧数据数
#define AT91C_SSC_FSLEN       ((unsigned int) 0xF << 16) // （SSC）接收/发送帧同步长度
#define AT91C_SSC_FSOS        ((unsigned int) 0x7 << 20) // （SSC）接收/发送帧同步输出选择
#define 	AT91C_SSC_FSOS_NONE                 ((unsigned int) 0x0 << 20) // （SSC）所选接收/发送帧同步信号：无RK引脚输入
#define 	AT91C_SSC_FSOS_NEGATIVE             ((unsigned int) 0x1 << 20) // （SSC）所选接收/发送帧同步信号：负脉冲
#define 	AT91C_SSC_FSOS_POSITIVE             ((unsigned int) 0x2 << 20) // （SSC）所选接收/发送帧同步信号：正脉冲
#define 	AT91C_SSC_FSOS_LOW                  ((unsigned int) 0x3 << 20) // （SSC）所选接收/发送帧同步信号：数据传输期间驱动器低
#define 	AT91C_SSC_FSOS_HIGH                 ((unsigned int) 0x4 << 20) // （SSC）所选接收/发送帧同步信号：数据传输期间驱动器高
#define 	AT91C_SSC_FSOS_TOGGLE               ((unsigned int) 0x5 << 20) // （SSC）所选接收/发送帧同步信号：在每次数据传输开始时切换
#define AT91C_SSC_FSEDGE      ((unsigned int) 0x1 << 24) // （SSC）帧同步边缘检测
// --------SSC_TCMR：（SSC偏移：0x18）SSC传输时钟模式寄存器--------
// --------SSC_TFMR：（SSC偏移：0x1c）SSC传输帧模式寄存器--------
#define AT91C_SSC_DATDEF      ((unsigned int) 0x1 <<  5) // （SSC）数据默认值
#define AT91C_SSC_FSDEN       ((unsigned int) 0x1 << 23) // （SSC）帧同步数据启用
// --------SSC_SR：（SSC偏移量：0x40）SSC状态寄存器--------
#define AT91C_SSC_TXRDY       ((unsigned int) 0x1 <<  0) // （SSC）传输就绪
#define AT91C_SSC_TXEMPTY     ((unsigned int) 0x1 <<  1) // （SSC）传输空
#define AT91C_SSC_ENDTX       ((unsigned int) 0x1 <<  2) // （SSC）传输结束
#define AT91C_SSC_TXBUFE      ((unsigned int) 0x1 <<  3) // （SSC）传输缓冲区清空
#define AT91C_SSC_RXRDY       ((unsigned int) 0x1 <<  4) // （SSC）接收就绪
#define AT91C_SSC_OVRUN       ((unsigned int) 0x1 <<  5) // （SSC）接收超限
#define AT91C_SSC_ENDRX       ((unsigned int) 0x1 <<  6) // （SSC）接收结束
#define AT91C_SSC_RXBUFF      ((unsigned int) 0x1 <<  7) // （SSC）接收缓冲区已满
#define AT91C_SSC_CP0         ((unsigned int) 0x1 <<  8) // （SSC）比较0
#define AT91C_SSC_CP1         ((unsigned int) 0x1 <<  9) // （SSC）比较1
#define AT91C_SSC_TXSYN       ((unsigned int) 0x1 << 10) // （SSC）传输同步
#define AT91C_SSC_RXSYN       ((unsigned int) 0x1 << 11) // （SSC）接收同步
#define AT91C_SSC_TXENA       ((unsigned int) 0x1 << 16) // （SSC）传输启用
#define AT91C_SSC_RXENA       ((unsigned int) 0x1 << 17) // （SSC）接收启用
// --------SSC_IER:（SSC偏移：0x44）SSC中断启用寄存器--------
// --------SSC_IDR：（SSC偏移：0x48）SSC中断禁用寄存器--------
// --------SSC_IMR：（SSC偏移：0x4c）SSC中断掩码寄存器--------

// *****************************************************************************
//              双线接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_TWI {
	AT91_REG	 TWI_CR; 	// 控制寄存器
	AT91_REG	 TWI_MMR; 	// 主模式寄存器
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 TWI_IADR; 	// 内部地址寄存器
	AT91_REG	 TWI_CWGR; 	// 时钟波形发生器寄存器
	AT91_REG	 Reserved1[3]; 	// 
	AT91_REG	 TWI_SR; 	// 状态寄存器
	AT91_REG	 TWI_IER; 	// 中断启用寄存器
	AT91_REG	 TWI_IDR; 	// 中断禁用寄存器
	AT91_REG	 TWI_IMR; 	// 中断掩码寄存器
	AT91_REG	 TWI_RHR; 	// 接收保持寄存器
	AT91_REG	 TWI_THR; 	// 发送保持寄存器
} AT91S_TWI, *AT91PS_TWI;

// --------TWI_CR:（TWI偏移：0x0）TWI控制寄存器--------
#define AT91C_TWI_START       ((unsigned int) 0x1 <<  0) // （TWI）发送启动条件
#define AT91C_TWI_STOP        ((unsigned int) 0x1 <<  1) // （TWI）发送STOP条件
#define AT91C_TWI_MSEN        ((unsigned int) 0x1 <<  2) // （TWI）TWI主传输已启用
#define AT91C_TWI_MSDIS       ((unsigned int) 0x1 <<  3) // （TWI）TWI主传输已禁用
#define AT91C_TWI_SWRST       ((unsigned int) 0x1 <<  7) // （TWI）软件重置
// --------TWI_MMR：（TWI偏移：0x4）TWI主模式寄存器--------
#define AT91C_TWI_IADRSZ      ((unsigned int) 0x3 <<  8) // （TWI）内部设备地址大小
#define 	AT91C_TWI_IADRSZ_NO                   ((unsigned int) 0x0 <<  8) // （TWI）无内部设备地址
#define 	AT91C_TWI_IADRSZ_1_BYTE               ((unsigned int) 0x1 <<  8) // （TWI）一字节内部设备地址
#define 	AT91C_TWI_IADRSZ_2_BYTE               ((unsigned int) 0x2 <<  8) // （TWI）双字节内部设备地址
#define 	AT91C_TWI_IADRSZ_3_BYTE               ((unsigned int) 0x3 <<  8) // （TWI）三字节内部设备地址
#define AT91C_TWI_MREAD       ((unsigned int) 0x1 << 12) // （TWI）主读取方向
#define AT91C_TWI_DADR        ((unsigned int) 0x7F << 16) // （TWI）设备地址
// --------TWI_CWGR:（TWI偏移：0x10）TWI时钟波形发生器寄存器--------
#define AT91C_TWI_CLDIV       ((unsigned int) 0xFF <<  0) // （TWI）时钟低分频器
#define AT91C_TWI_CHDIV       ((unsigned int) 0xFF <<  8) // （TWI）时钟高分频器
#define AT91C_TWI_CKDIV       ((unsigned int) 0x7 << 16) // （TWI）时钟分频器
// --------TWI_SR:（TWI偏移：0x20）TWI状态寄存器--------
#define AT91C_TWI_TXCOMP      ((unsigned int) 0x1 <<  0) // （TWI）传输完成
#define AT91C_TWI_RXRDY       ((unsigned int) 0x1 <<  1) // （TWI）接收保持寄存器ReaDY
#define AT91C_TWI_TXRDY       ((unsigned int) 0x1 <<  2) // （TWI）发送保持寄存器ReaDY
#define AT91C_TWI_OVRE        ((unsigned int) 0x1 <<  6) // （TWI）超限错误
#define AT91C_TWI_UNRE        ((unsigned int) 0x1 <<  7) // （TWI）欠载错误
#define AT91C_TWI_NACK        ((unsigned int) 0x1 <<  8) // （TWI）未确认
// --------TWI_IER：（TWI偏移：0x24）TWI中断启用寄存器--------
// --------TWI_IDR:（TWI偏移：0x28）TWI中断禁用寄存器--------
// --------TWI_IR:（TWI偏移：0x2c）TWI中断掩码寄存器--------

// *****************************************************************************
//              PWMC通道接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_PWMC_CH {
	AT91_REG	 PWMC_CMR; 	// 信道模式寄存器
	AT91_REG	 PWMC_CDTYR; 	// 通道占空比寄存器
	AT91_REG	 PWMC_CPRDR; 	// 信道周期寄存器
	AT91_REG	 PWMC_CCNTR; 	// 信道计数器寄存器
	AT91_REG	 PWMC_CUPDR; 	// 信道更新寄存器
	AT91_REG	 PWMC_Reserved[3]; 	// 保留
} AT91S_PWMC_CH, *AT91PS_PWMC_CH;

// --------PWMC_CMR：（PWMC_CH偏移：0x0）PWMC信道模式寄存器--------
#define AT91C_PWMC_CPRE       ((unsigned int) 0xF <<  0) // （PWMC_CH）信道预缩放器：PWMC_CLKx
#define 	AT91C_PWMC_CPRE_MCK                  ((unsigned int) 0x0) // (PWMC_CH) 
#define 	AT91C_PWMC_CPRE_MCKA                 ((unsigned int) 0xB) // (PWMC_CH) 
#define 	AT91C_PWMC_CPRE_MCKB                 ((unsigned int) 0xC) // (PWMC_CH) 
#define AT91C_PWMC_CALG       ((unsigned int) 0x1 <<  8) // （PWMC_CH）通道对齐
#define AT91C_PWMC_CPOL       ((unsigned int) 0x1 <<  9) // （PWMC_CH）通道极性
#define AT91C_PWMC_CPD        ((unsigned int) 0x1 << 10) // （PWMC_CH）信道更新周期
// --------PWMC_CDTYR：（PWMC_CH偏移：0x4）PWMC通道占空比寄存器--------
#define AT91C_PWMC_CDTY       ((unsigned int) 0x0 <<  0) // （PWMC_CH）通道占空比
// --------PWMC_CPRDR:（PWMC_CH偏移：0x8）PWMC信道周期寄存器--------
#define AT91C_PWMC_CPRD       ((unsigned int) 0x0 <<  0) // （PWMC_CH）信道周期
// --------PWMC_CCNTR：（PWMC_CH偏移：0xc）PWMC信道计数器寄存器--------
#define AT91C_PWMC_CCNT       ((unsigned int) 0x0 <<  0) // （PWMC_CH）信道计数器
// --------PWMC_CUPDR:（PWMC_CH偏移：0x10）PWMC信道更新寄存器--------
#define AT91C_PWMC_CUPD       ((unsigned int) 0x0 <<  0) // （PWMC_CH）信道更新

// *****************************************************************************
//              脉宽调制控制器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_PWMC {
	AT91_REG	 PWMC_MR; 	// PWMC模式寄存器
	AT91_REG	 PWMC_ENA; 	// PWMC启用寄存器
	AT91_REG	 PWMC_DIS; 	// PWMC禁用寄存器
	AT91_REG	 PWMC_SR; 	// PWMC状态寄存器
	AT91_REG	 PWMC_IER; 	// PWMC中断启用寄存器
	AT91_REG	 PWMC_IDR; 	// PWMC中断禁用寄存器
	AT91_REG	 PWMC_IMR; 	// PWMC中断掩码寄存器
	AT91_REG	 PWMC_ISR; 	// PWMC中断状态寄存器
	AT91_REG	 Reserved0[55]; 	// 
	AT91_REG	 PWMC_VR; 	// PWMC版本寄存器
	AT91_REG	 Reserved1[64]; 	// 
	AT91S_PWMC_CH	 PWMC_CH[4]; 	// PWMC通道
} AT91S_PWMC, *AT91PS_PWMC;

// --------PWMC_MR：（PWMC偏移：0x0）PWMC模式寄存器--------
#define AT91C_PWMC_DIVA       ((unsigned int) 0xFF <<  0) // （PWMC）CLKA除法因子。
#define AT91C_PWMC_PREA       ((unsigned int) 0xF <<  8) // （PWMC）分频器输入时钟预分频器A
#define 	AT91C_PWMC_PREA_MCK                  ((unsigned int) 0x0 <<  8) // (PWMC) 
#define AT91C_PWMC_DIVB       ((unsigned int) 0xFF << 16) // （PWMC）CLKB除法因子。
#define AT91C_PWMC_PREB       ((unsigned int) 0xF << 24) // （PWMC）分频器输入时钟预分频器B
#define 	AT91C_PWMC_PREB_MCK                  ((unsigned int) 0x0 << 24) // (PWMC) 
// --------PWMC_ENA:（PWMC偏移：0x4）PWMC启用寄存器--------
#define AT91C_PWMC_CHID0      ((unsigned int) 0x1 <<  0) // （PWMC）信道ID 0
#define AT91C_PWMC_CHID1      ((unsigned int) 0x1 <<  1) // （PWMC）通道ID 1
#define AT91C_PWMC_CHID2      ((unsigned int) 0x1 <<  2) // （PWMC）信道ID 2
#define AT91C_PWMC_CHID3      ((unsigned int) 0x1 <<  3) // （PWMC）信道ID 3
// --------PWMC_DIS：（PWMC偏移：0x8）PWMC禁用寄存器--------
// --------PWMC_SR：（PWMC偏移：0xc）PWMC状态寄存器--------
// --------PWMC_IER:（PWMC偏移：0x10）PWMC中断启用寄存器--------
// --------PWMC_IDR:（PWMC偏移：0x14）PWMC中断禁用寄存器--------
// --------PWMC_IMR：（PWMC偏移：0x18）PWMC中断掩码寄存器--------
// --------PWMC_ISR:（PWMC偏移：0x1c）PWMC中断状态寄存器--------

// *****************************************************************************
//              USB设备接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_UDP {
	AT91_REG	 UDP_NUM; 	// 帧号寄存器
	AT91_REG	 UDP_GLBSTATE; 	// 全局状态寄存器
	AT91_REG	 UDP_FADDR; 	// 功能地址寄存器
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 UDP_IER; 	// 中断启用寄存器
	AT91_REG	 UDP_IDR; 	// 中断禁用寄存器
	AT91_REG	 UDP_IMR; 	// 中断掩码寄存器
	AT91_REG	 UDP_ISR; 	// 中断状态寄存器
	AT91_REG	 UDP_ICR; 	// 中断清除寄存器
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 UDP_RSTEP; 	// 重置终结点寄存器
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 UDP_CSR[6]; 	// 端点控制和状态寄存器
	AT91_REG	 Reserved3[2]; 	// 
	AT91_REG	 UDP_FDR[6]; 	// 端点FIFO数据寄存器
	AT91_REG	 Reserved4[3]; 	// 
	AT91_REG	 UDP_TXVC; 	// 收发器控制寄存器
} AT91S_UDP, *AT91PS_UDP;

// --------UDP_FRM_NUM：（UDP偏移：0x0）USB帧号寄存器--------
#define AT91C_UDP_FRM_NUM     ((unsigned int) 0x7FF <<  0) // 分组字段格式中定义的（UDP）帧号
#define AT91C_UDP_FRM_ERR     ((unsigned int) 0x1 << 16) // （UDP）帧错误
#define AT91C_UDP_FRM_OK      ((unsigned int) 0x1 << 17) // （UDP）帧正常
// --------UDP_GLB_STATE:（UDP偏移：0x4）USB全局状态寄存器--------
#define AT91C_UDP_FADDEN      ((unsigned int) 0x1 <<  0) // （UDP）功能地址启用
#define AT91C_UDP_CONFG       ((unsigned int) 0x1 <<  1) // （UDP）已配置
#define AT91C_UDP_ESR         ((unsigned int) 0x1 <<  2) // （UDP）启用发送恢复
#define AT91C_UDP_RSMINPR     ((unsigned int) 0x1 <<  3) // （UDP）已将恢复发送到主机
#define AT91C_UDP_RMWUPE      ((unsigned int) 0x1 <<  4) // （UDP）远程唤醒启用
// --------UDP_FADDR:（UDP偏移量：0x8）USB功能地址寄存器--------
#define AT91C_UDP_FADD        ((unsigned int) 0xFF <<  0) // （UDP）函数地址值
#define AT91C_UDP_FEN         ((unsigned int) 0x1 <<  8) // （UDP）功能启用
// --------UDP_IER:（UDP偏移：0x10）USB中断启用寄存器--------
#define AT91C_UDP_EPINT0      ((unsigned int) 0x1 <<  0) // （UDP）端点0中断
#define AT91C_UDP_EPINT1      ((unsigned int) 0x1 <<  1) // （UDP）端点0中断
#define AT91C_UDP_EPINT2      ((unsigned int) 0x1 <<  2) // （UDP）端点2中断
#define AT91C_UDP_EPINT3      ((unsigned int) 0x1 <<  3) // （UDP）端点3中断
#define AT91C_UDP_EPINT4      ((unsigned int) 0x1 <<  4) // （UDP）端点4中断
#define AT91C_UDP_EPINT5      ((unsigned int) 0x1 <<  5) // （UDP）端点5中断
#define AT91C_UDP_RXSUSP      ((unsigned int) 0x1 <<  8) // （UDP）USB挂起中断
#define AT91C_UDP_RXRSM       ((unsigned int) 0x1 <<  9) // （UDP）USB恢复中断
#define AT91C_UDP_EXTRSM      ((unsigned int) 0x1 << 10) // （UDP）USB外部恢复中断
#define AT91C_UDP_SOFINT      ((unsigned int) 0x1 << 11) // （UDP）USB帧开始中断
#define AT91C_UDP_WAKEUP      ((unsigned int) 0x1 << 13) // （UDP）USB恢复中断
// --------UDP_IDR：（UDP偏移：0x14）USB中断禁用寄存器--------
// --------UDP_IMR：（UDP偏移：0x18）USB中断掩码寄存器--------
// --------UDP_ISR：（UDP偏移：0x1c）USB中断状态寄存器--------
#define AT91C_UDP_ENDBUSRES   ((unsigned int) 0x1 << 12) // （UDP）USB总线端重置中断
// --------UDP_ICR：（UDP偏移：0x20）USB中断清除寄存器--------
// --------UDP_RST_EP:（UDP偏移：0x28）USB重置端点寄存器--------
#define AT91C_UDP_EP0         ((unsigned int) 0x1 <<  0) // （UDP）重置终结点0
#define AT91C_UDP_EP1         ((unsigned int) 0x1 <<  1) // （UDP）重置终结点1
#define AT91C_UDP_EP2         ((unsigned int) 0x1 <<  2) // （UDP）重置终结点2
#define AT91C_UDP_EP3         ((unsigned int) 0x1 <<  3) // （UDP）重置终结点3
#define AT91C_UDP_EP4         ((unsigned int) 0x1 <<  4) // （UDP）重置终结点4
#define AT91C_UDP_EP5         ((unsigned int) 0x1 <<  5) // （UDP）重置终结点5
// --------UDP_CSR：（UDP偏移量：0x30）USB端点控制和状态寄存器--------
#define AT91C_UDP_TXCOMP      ((unsigned int) 0x1 <<  0) // （UDP）使用以前写入DPR的数据生成IN数据包
#define AT91C_UDP_RX_DATA_BK0 ((unsigned int) 0x1 <<  1) // （UDP）接收数据库0
#define AT91C_UDP_RXSETUP     ((unsigned int) 0x1 <<  2) // （UDP）向主机（控制端点）发送STALL
#define AT91C_UDP_ISOERROR    ((unsigned int) 0x1 <<  3) // （UDP）等时错误（等时端点）
#define AT91C_UDP_TXPKTRDY    ((unsigned int) 0x1 <<  4) // （UDP）传输数据包就绪
#define AT91C_UDP_FORCESTALL  ((unsigned int) 0x1 <<  5) // （UDP）强制暂停（由Control、Bulk和Isochronous端点使用）。
#define AT91C_UDP_RX_DATA_BK1 ((unsigned int) 0x1 <<  6) // （UDP）接收数据库1（仅由具有乒乓属性的端点使用）。
#define AT91C_UDP_DIR         ((unsigned int) 0x1 <<  7) // （UDP）传输方向
#define AT91C_UDP_EPTYPE      ((unsigned int) 0x7 <<  8) // （UDP）终结点类型
#define 	AT91C_UDP_EPTYPE_CTRL                 ((unsigned int) 0x0 <<  8) // （UDP）控制
#define 	AT91C_UDP_EPTYPE_ISO_OUT              ((unsigned int) 0x1 <<  8) // （UDP）等时输出
#define 	AT91C_UDP_EPTYPE_BULK_OUT             ((unsigned int) 0x2 <<  8) // （UDP）批量输出
#define 	AT91C_UDP_EPTYPE_INT_OUT              ((unsigned int) 0x3 <<  8) // （UDP）中断OUT
#define 	AT91C_UDP_EPTYPE_ISO_IN               ((unsigned int) 0x5 <<  8) // （UDP）同步输入
#define 	AT91C_UDP_EPTYPE_BULK_IN              ((unsigned int) 0x6 <<  8) // （UDP）批量输入
#define 	AT91C_UDP_EPTYPE_INT_IN               ((unsigned int) 0x7 <<  8) // （UDP）中断IN
#define AT91C_UDP_DTGLE       ((unsigned int) 0x1 << 11) // （UDP）数据切换
#define AT91C_UDP_EPEDS       ((unsigned int) 0x1 << 15) // （UDP）端点启用禁用
#define AT91C_UDP_RXBYTECNT   ((unsigned int) 0x7FF << 16) // （UDP）FIFO中可用的字节数
// --------UDP_TXVC:（UDP偏移：0x74）收发器控制寄存器--------
#define AT91C_UDP_TXVDIS      ((unsigned int) 0x1 <<  8) // (UDP) 
#define AT91C_UDP_PUON        ((unsigned int) 0x1 <<  9) // （UDP）上拉打开

// *****************************************************************************
//              定时器计数器通道接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_TC {
	AT91_REG	 TC_CCR; 	// 信道控制寄存器
	AT91_REG	 TC_CMR; 	// 信道模式寄存器（捕获模式/波形模式）
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 TC_CV; 	// 计数器值
	AT91_REG	 TC_RA; 	// 寄存器A
	AT91_REG	 TC_RB; 	// 寄存器B
	AT91_REG	 TC_RC; 	// 寄存器C
	AT91_REG	 TC_SR; 	// 状态寄存器
	AT91_REG	 TC_IER; 	// 中断启用寄存器
	AT91_REG	 TC_IDR; 	// 中断禁用寄存器
	AT91_REG	 TC_IMR; 	// 中断掩码寄存器
} AT91S_TC, *AT91PS_TC;

// --------TC_CCR：（TC偏移：0x0）TC信道控制寄存器--------
#define AT91C_TC_CLKEN        ((unsigned int) 0x1 <<  0) // （TC）计数器时钟启用命令
#define AT91C_TC_CLKDIS       ((unsigned int) 0x1 <<  1) // （TC）计数器时钟禁用命令
#define AT91C_TC_SWTRG        ((unsigned int) 0x1 <<  2) // （TC）软件触发命令
// --------TC_CMR：（TC偏移：0x4）TC信道模式寄存器：捕获模式/波形模式--------
#define AT91C_TC_CLKS         ((unsigned int) 0x7 <<  0) // （TC）时钟选择
#define 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     ((unsigned int) 0x0) // （TC）选择的时钟：TIMER_DIV1_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     ((unsigned int) 0x1) // （TC）选择的时钟：TIMER_DIV2_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     ((unsigned int) 0x2) // （TC）选择的时钟：TIMER_DIV3_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     ((unsigned int) 0x3) // （TC）选择的时钟：TIMER_DIV4_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     ((unsigned int) 0x4) // （TC）选择的时钟：TIMER_DIV5_Clock
#define 	AT91C_TC_CLKS_XC0                  ((unsigned int) 0x5) // （TC）选择的时钟：XC0
#define 	AT91C_TC_CLKS_XC1                  ((unsigned int) 0x6) // （TC）选择的时钟：XC1
#define 	AT91C_TC_CLKS_XC2                  ((unsigned int) 0x7) // （TC）选择的时钟：XC2
#define AT91C_TC_CLKI         ((unsigned int) 0x1 <<  3) // （TC）时钟反转
#define AT91C_TC_BURST        ((unsigned int) 0x3 <<  4) // （TC）突发信号选择
#define 	AT91C_TC_BURST_NONE                 ((unsigned int) 0x0 <<  4) // （TC）时钟不受外部信号门控
#define 	AT91C_TC_BURST_XC0                  ((unsigned int) 0x1 <<  4) // （TC）XC0与所选时钟“与”
#define 	AT91C_TC_BURST_XC1                  ((unsigned int) 0x2 <<  4) // （TC）XC1与所选时钟“与”
#define 	AT91C_TC_BURST_XC2                  ((unsigned int) 0x3 <<  4) // （TC）XC2与所选时钟“与”
#define AT91C_TC_CPCSTOP      ((unsigned int) 0x1 <<  6) // （TC）计数器时钟停止，RC比较
#define AT91C_TC_LDBSTOP      ((unsigned int) 0x1 <<  6) // （TC）计数器时钟因RB加载而停止
#define AT91C_TC_CPCDIS       ((unsigned int) 0x1 <<  7) // 使用RC比较禁用（TC）计数器时钟
#define AT91C_TC_LDBDIS       ((unsigned int) 0x1 <<  7) // （TC）计数器时钟禁用，RB加载
#define AT91C_TC_ETRGEDG      ((unsigned int) 0x3 <<  8) // （TC）外部触发边缘选择
#define 	AT91C_TC_ETRGEDG_NONE                 ((unsigned int) 0x0 <<  8) // （TC）边缘：无
#define 	AT91C_TC_ETRGEDG_RISING               ((unsigned int) 0x1 <<  8) // （TC）边缘：上升边缘
#define 	AT91C_TC_ETRGEDG_FALLING              ((unsigned int) 0x2 <<  8) // （TC）边缘：下降边缘
#define 	AT91C_TC_ETRGEDG_BOTH                 ((unsigned int) 0x3 <<  8) // （TC）边缘：每个边缘
#define AT91C_TC_EEVTEDG      ((unsigned int) 0x3 <<  8) // （TC）外部事件边缘选择
#define 	AT91C_TC_EEVTEDG_NONE                 ((unsigned int) 0x0 <<  8) // （TC）边缘：无
#define 	AT91C_TC_EEVTEDG_RISING               ((unsigned int) 0x1 <<  8) // （TC）边缘：上升边缘
#define 	AT91C_TC_EEVTEDG_FALLING              ((unsigned int) 0x2 <<  8) // （TC）边缘：下降边缘
#define 	AT91C_TC_EEVTEDG_BOTH                 ((unsigned int) 0x3 <<  8) // （TC）边缘：每个边缘
#define AT91C_TC_EEVT         ((unsigned int) 0x3 << 10) // （TC）外部事件选择
#define 	AT91C_TC_EEVT_TIOB                 ((unsigned int) 0x0 << 10) // （TC）选择为外部事件的信号：TIOB TIOB方向：输入
#define 	AT91C_TC_EEVT_XC0                  ((unsigned int) 0x1 << 10) // （TC）选择为外部事件的信号：XC0 TIOB方向：输出
#define 	AT91C_TC_EEVT_XC1                  ((unsigned int) 0x2 << 10) // （TC）选择为外部事件的信号：XC1 TIOB方向：输出
#define 	AT91C_TC_EEVT_XC2                  ((unsigned int) 0x3 << 10) // （TC）选择为外部事件的信号：XC2 TIOB方向：输出
#define AT91C_TC_ABETRG       ((unsigned int) 0x1 << 10) // （TC）TIOA或TIOB外部触发选择
#define AT91C_TC_ENETRG       ((unsigned int) 0x1 << 12) // （TC）外部事件触发器启用
#define AT91C_TC_WAVESEL      ((unsigned int) 0x3 << 13) // （TC）波形选择
#define 	AT91C_TC_WAVESEL_UP                   ((unsigned int) 0x0 << 13) // RC比较上无自动触发的（TC）UP模式
#define 	AT91C_TC_WAVESEL_UPDOWN               ((unsigned int) 0x1 << 13) // （TC）UPDOWN模式，无RC比较自动触发
#define 	AT91C_TC_WAVESEL_UP_AUTO              ((unsigned int) 0x2 << 13) // RC比较自动触发的（TC）UP模式
#define 	AT91C_TC_WAVESEL_UPDOWN_AUTO          ((unsigned int) 0x3 << 13) // （TC）UPDOWN模式，RC比较时自动触发
#define AT91C_TC_CPCTRG       ((unsigned int) 0x1 << 14) // （TC）RC比较触发启用
#define AT91C_TC_WAVE         ((unsigned int) 0x1 << 15) // (TC) 
#define AT91C_TC_ACPA         ((unsigned int) 0x3 << 16) // （TC）RA比较对TIOA的影响
#define 	AT91C_TC_ACPA_NONE                 ((unsigned int) 0x0 << 16) // （TC）影响：无
#define 	AT91C_TC_ACPA_SET                  ((unsigned int) 0x1 << 16) // （TC）效果：设置
#define 	AT91C_TC_ACPA_CLEAR                ((unsigned int) 0x2 << 16) // （TC）效果：清晰
#define 	AT91C_TC_ACPA_TOGGLE               ((unsigned int) 0x3 << 16) // （TC）效果：切换
#define AT91C_TC_LDRA         ((unsigned int) 0x3 << 16) // （TC）RA加载选择
#define 	AT91C_TC_LDRA_NONE                 ((unsigned int) 0x0 << 16) // （TC）边缘：无
#define 	AT91C_TC_LDRA_RISING               ((unsigned int) 0x1 << 16) // （TC）边缘：TIOA的上升边缘
#define 	AT91C_TC_LDRA_FALLING              ((unsigned int) 0x2 << 16) // （TC）边缘：TIOA的下降边缘
#define 	AT91C_TC_LDRA_BOTH                 ((unsigned int) 0x3 << 16) // （TC）边缘：TIOA的每个边缘
#define AT91C_TC_ACPC         ((unsigned int) 0x3 << 18) // （TC）RC比较对TIOA的影响
#define 	AT91C_TC_ACPC_NONE                 ((unsigned int) 0x0 << 18) // （TC）影响：无
#define 	AT91C_TC_ACPC_SET                  ((unsigned int) 0x1 << 18) // （TC）效果：设置
#define 	AT91C_TC_ACPC_CLEAR                ((unsigned int) 0x2 << 18) // （TC）效果：清晰
#define 	AT91C_TC_ACPC_TOGGLE               ((unsigned int) 0x3 << 18) // （TC）效果：切换
#define AT91C_TC_LDRB         ((unsigned int) 0x3 << 18) // （TC）RB加载选择
#define 	AT91C_TC_LDRB_NONE                 ((unsigned int) 0x0 << 18) // （TC）边缘：无
#define 	AT91C_TC_LDRB_RISING               ((unsigned int) 0x1 << 18) // （TC）边缘：TIOA的上升边缘
#define 	AT91C_TC_LDRB_FALLING              ((unsigned int) 0x2 << 18) // （TC）边缘：TIOA的下降边缘
#define 	AT91C_TC_LDRB_BOTH                 ((unsigned int) 0x3 << 18) // （TC）边缘：TIOA的每个边缘
#define AT91C_TC_AEEVT        ((unsigned int) 0x3 << 20) // （TC）外部事件对TIOA的影响
#define 	AT91C_TC_AEEVT_NONE                 ((unsigned int) 0x0 << 20) // （TC）影响：无
#define 	AT91C_TC_AEEVT_SET                  ((unsigned int) 0x1 << 20) // （TC）效果：设置
#define 	AT91C_TC_AEEVT_CLEAR                ((unsigned int) 0x2 << 20) // （TC）效果：清晰
#define 	AT91C_TC_AEEVT_TOGGLE               ((unsigned int) 0x3 << 20) // （TC）效果：切换
#define AT91C_TC_ASWTRG       ((unsigned int) 0x3 << 22) // （TC）软件触发对TIOA的影响
#define 	AT91C_TC_ASWTRG_NONE                 ((unsigned int) 0x0 << 22) // （TC）影响：无
#define 	AT91C_TC_ASWTRG_SET                  ((unsigned int) 0x1 << 22) // （TC）效果：设置
#define 	AT91C_TC_ASWTRG_CLEAR                ((unsigned int) 0x2 << 22) // （TC）效果：清晰
#define 	AT91C_TC_ASWTRG_TOGGLE               ((unsigned int) 0x3 << 22) // （TC）效果：切换
#define AT91C_TC_BCPB         ((unsigned int) 0x3 << 24) // （TC）RB比较对TIOB的影响
#define 	AT91C_TC_BCPB_NONE                 ((unsigned int) 0x0 << 24) // （TC）影响：无
#define 	AT91C_TC_BCPB_SET                  ((unsigned int) 0x1 << 24) // （TC）效果：设置
#define 	AT91C_TC_BCPB_CLEAR                ((unsigned int) 0x2 << 24) // （TC）效果：清晰
#define 	AT91C_TC_BCPB_TOGGLE               ((unsigned int) 0x3 << 24) // （TC）效果：切换
#define AT91C_TC_BCPC         ((unsigned int) 0x3 << 26) // （TC）RC比较对TIOB的影响
#define 	AT91C_TC_BCPC_NONE                 ((unsigned int) 0x0 << 26) // （TC）影响：无
#define 	AT91C_TC_BCPC_SET                  ((unsigned int) 0x1 << 26) // （TC）效果：设置
#define 	AT91C_TC_BCPC_CLEAR                ((unsigned int) 0x2 << 26) // （TC）效果：清晰
#define 	AT91C_TC_BCPC_TOGGLE               ((unsigned int) 0x3 << 26) // （TC）效果：切换
#define AT91C_TC_BEEVT        ((unsigned int) 0x3 << 28) // （TC）外部事件对TIOB的影响
#define 	AT91C_TC_BEEVT_NONE                 ((unsigned int) 0x0 << 28) // （TC）影响：无
#define 	AT91C_TC_BEEVT_SET                  ((unsigned int) 0x1 << 28) // （TC）效果：设置
#define 	AT91C_TC_BEEVT_CLEAR                ((unsigned int) 0x2 << 28) // （TC）效果：清晰
#define 	AT91C_TC_BEEVT_TOGGLE               ((unsigned int) 0x3 << 28) // （TC）效果：切换
#define AT91C_TC_BSWTRG       ((unsigned int) 0x3 << 30) // （TC）软件触发对TIOB的影响
#define 	AT91C_TC_BSWTRG_NONE                 ((unsigned int) 0x0 << 30) // （TC）影响：无
#define 	AT91C_TC_BSWTRG_SET                  ((unsigned int) 0x1 << 30) // （TC）效果：设置
#define 	AT91C_TC_BSWTRG_CLEAR                ((unsigned int) 0x2 << 30) // （TC）效果：清晰
#define 	AT91C_TC_BSWTRG_TOGGLE               ((unsigned int) 0x3 << 30) // （TC）效果：切换
// --------TC_SR：（TC偏移：0x20）TC信道状态寄存器--------
#define AT91C_TC_COVFS        ((unsigned int) 0x1 <<  0) // （TC）计数器溢出
#define AT91C_TC_LOVRS        ((unsigned int) 0x1 <<  1) // （TC）负载超限
#define AT91C_TC_CPAS         ((unsigned int) 0x1 <<  2) // （TC）RA比较
#define AT91C_TC_CPBS         ((unsigned int) 0x1 <<  3) // （TC）RB比较
#define AT91C_TC_CPCS         ((unsigned int) 0x1 <<  4) // （TC）RC比较
#define AT91C_TC_LDRAS        ((unsigned int) 0x1 <<  5) // （TC）RA加载
#define AT91C_TC_LDRBS        ((unsigned int) 0x1 <<  6) // （TC）RB加载
#define AT91C_TC_ETRGS        ((unsigned int) 0x1 <<  7) // （TC）外部触发器
#define AT91C_TC_CLKSTA       ((unsigned int) 0x1 << 16) // （TC）时钟启用
#define AT91C_TC_MTIOA        ((unsigned int) 0x1 << 17) // （TC）TIOA后视镜
#define AT91C_TC_MTIOB        ((unsigned int) 0x1 << 18) // （TC）TIOA后视镜
// --------TC_IER：（TC偏移：0x24）TC通道中断启用寄存器--------
// --------TC_IDR：（TC偏移：0x28）TC通道中断禁用寄存器--------
// --------TC_IMR：（TC偏移：0x2c）TC通道中断掩码寄存器--------

// *****************************************************************************
//              定时器计数器接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_TCB {
	AT91S_TC	 TCB_TC0; 	// TC通道0
	AT91_REG	 Reserved0[4]; 	// 
	AT91S_TC	 TCB_TC1; 	// TC通道1
	AT91_REG	 Reserved1[4]; 	// 
	AT91S_TC	 TCB_TC2; 	// TC通道2
	AT91_REG	 Reserved2[4]; 	// 
	AT91_REG	 TCB_BCR; 	// TC块控制寄存器
	AT91_REG	 TCB_BMR; 	// TC块模式寄存器
} AT91S_TCB, *AT91PS_TCB;

// --------TCB_BCR：（TCB偏移量：0xc0）TC块控制寄存器--------
#define AT91C_TCB_SYNC        ((unsigned int) 0x1 <<  0) // （TCB）同步命令
// --------TCB_BMR：（TCB偏移量：0xc4）TC块模式寄存器--------
#define AT91C_TCB_TC0XC0S     ((unsigned int) 0x3 <<  0) // （TCB）外部时钟信号0选择
#define 	AT91C_TCB_TC0XC0S_TCLK0                ((unsigned int) 0x0) // （TCB）TCLK0连接到XC0
#define 	AT91C_TCB_TC0XC0S_NONE                 ((unsigned int) 0x1) // （TCB）无信号连接到XC0
#define 	AT91C_TCB_TC0XC0S_TIOA1                ((unsigned int) 0x2) // （TCB）TIOA1连接到XC0
#define 	AT91C_TCB_TC0XC0S_TIOA2                ((unsigned int) 0x3) // （TCB）TIOA2连接到XC0
#define AT91C_TCB_TC1XC1S     ((unsigned int) 0x3 <<  2) // （TCB）外部时钟信号1选择
#define 	AT91C_TCB_TC1XC1S_TCLK1                ((unsigned int) 0x0 <<  2) // （TCB）TCLK1连接到XC1
#define 	AT91C_TCB_TC1XC1S_NONE                 ((unsigned int) 0x1 <<  2) // （TCB）无信号连接到XC1
#define 	AT91C_TCB_TC1XC1S_TIOA0                ((unsigned int) 0x2 <<  2) // （TCB）TIOA0连接到XC1
#define 	AT91C_TCB_TC1XC1S_TIOA2                ((unsigned int) 0x3 <<  2) // （TCB）TIOA2连接到XC1
#define AT91C_TCB_TC2XC2S     ((unsigned int) 0x3 <<  4) // （TCB）外部时钟信号2选择
#define 	AT91C_TCB_TC2XC2S_TCLK2                ((unsigned int) 0x0 <<  4) // （TCB）TCLK2连接到XC2
#define 	AT91C_TCB_TC2XC2S_NONE                 ((unsigned int) 0x1 <<  4) // （TCB）无信号连接到XC2
#define 	AT91C_TCB_TC2XC2S_TIOA0                ((unsigned int) 0x2 <<  4) // （TCB）TIOA0连接到XC2
#define 	AT91C_TCB_TC2XC2S_TIOA1                ((unsigned int) 0x3 <<  4) // （TCB）TIOA2连接到XC2

// *****************************************************************************
//              控制区域网络邮箱接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_CAN_MB {
	AT91_REG	 CAN_MB_MMR; 	// 邮箱模式寄存器
	AT91_REG	 CAN_MB_MAM; 	// 邮箱接受掩码寄存器
	AT91_REG	 CAN_MB_MID; 	// 邮箱ID注册
	AT91_REG	 CAN_MB_MFID; 	// 邮箱系列ID注册
	AT91_REG	 CAN_MB_MSR; 	// 邮箱状态寄存器
	AT91_REG	 CAN_MB_MDL; 	// MailBox数据低寄存器
	AT91_REG	 CAN_MB_MDH; 	// 邮箱数据高位寄存器
	AT91_REG	 CAN_MB_MCR; 	// 邮箱控制寄存器
} AT91S_CAN_MB, *AT91PS_CAN_MB;

// --------CAN_MMR：（CAN_MB偏移：0x0）CAN消息模式寄存器--------
#define AT91C_CAN_MTIMEMARK   ((unsigned int) 0xFFFF <<  0) // （CAN_MB）邮箱时间标记
#define AT91C_CAN_PRIOR       ((unsigned int) 0xF << 16) // （CAN_MB）邮箱优先级
#define AT91C_CAN_MOT         ((unsigned int) 0x7 << 24) // （CAN_MB）邮箱对象类型
#define 	AT91C_CAN_MOT_DIS                  ((unsigned int) 0x0 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_RX                   ((unsigned int) 0x1 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_RXOVERWRITE          ((unsigned int) 0x2 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_TX                   ((unsigned int) 0x3 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_CONSUMER             ((unsigned int) 0x4 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_PRODUCER             ((unsigned int) 0x5 << 24) // (CAN_MB) 
// --------CAN_MAM：（CAN_MB偏移：0x4）CAN消息接受掩码寄存器--------
#define AT91C_CAN_MIDvB       ((unsigned int) 0x3FFFF <<  0) // （CAN_MB）扩展模式中标识符的互补位
#define AT91C_CAN_MIDvA       ((unsigned int) 0x7FF << 18) // （CAN_MB）标准帧模式标识符
#define AT91C_CAN_MIDE        ((unsigned int) 0x1 << 29) // （CAN_MB）标识符版本
// --------CAN_MID:（CAN_MB偏移：0x8）CAN消息ID寄存器--------
// --------CAN_MFID：（CAN_MB偏移：0xc）CAN消息系列ID寄存器--------
// --------CAN_MSR:（CAN_MB偏移：0x10）CAN消息状态寄存器--------
#define AT91C_CAN_MTIMESTAMP  ((unsigned int) 0xFFFF <<  0) // （CAN_MB）计时器值
#define AT91C_CAN_MDLC        ((unsigned int) 0xF << 16) // （CAN_MB）邮箱数据长度代码
#define AT91C_CAN_MRTR        ((unsigned int) 0x1 << 20) // （CAN_MB）邮箱远程传输请求
#define AT91C_CAN_MABT        ((unsigned int) 0x1 << 22) // （CAN_MB）邮箱消息中止
#define AT91C_CAN_MRDY        ((unsigned int) 0x1 << 23) // （CAN_MB）邮箱就绪
#define AT91C_CAN_MMI         ((unsigned int) 0x1 << 24) // （CAN_MB）邮箱消息已忽略
// --------CAN_MDL:（CAN_MB偏移：0x14）CAN消息数据低寄存器--------
// --------CAN_MDH:（CAN_MB偏移：0x18）CAN消息数据高位寄存器--------
// --------CAN_MCR：（CAN_MB偏移：0x1c）CAN消息控制寄存器--------
#define AT91C_CAN_MACR        ((unsigned int) 0x1 << 22) // （CAN_MB）中止邮箱请求
#define AT91C_CAN_MTCR        ((unsigned int) 0x1 << 23) // （CAN_MB）邮箱传输命令

// *****************************************************************************
//              控制区域网络接口的软件API定义
// *****************************************************************************
typedef struct _AT91S_CAN {
	AT91_REG	 CAN_MR; 	// 模式寄存器
	AT91_REG	 CAN_IER; 	// 中断启用寄存器
	AT91_REG	 CAN_IDR; 	// 中断禁用寄存器
	AT91_REG	 CAN_IMR; 	// 中断掩码寄存器
	AT91_REG	 CAN_SR; 	// 状态寄存器
	AT91_REG	 CAN_BR; 	// 波特率寄存器
	AT91_REG	 CAN_TIM; 	// 计时器寄存器
	AT91_REG	 CAN_TIMESTP; 	// 时间戳寄存器
	AT91_REG	 CAN_ECR; 	// 错误计数器寄存器
	AT91_REG	 CAN_TCR; 	// 传输命令寄存器
	AT91_REG	 CAN_ACR; 	// 中止命令寄存器
	AT91_REG	 Reserved0[52]; 	// 
	AT91_REG	 CAN_VR; 	// 版本寄存器
	AT91_REG	 Reserved1[64]; 	// 
	AT91S_CAN_MB	 CAN_MB0; 	// CAN邮箱0
	AT91S_CAN_MB	 CAN_MB1; 	// CAN邮箱1
	AT91S_CAN_MB	 CAN_MB2; 	// CAN邮箱2
	AT91S_CAN_MB	 CAN_MB3; 	// CAN邮箱3
	AT91S_CAN_MB	 CAN_MB4; 	// CAN邮箱4
	AT91S_CAN_MB	 CAN_MB5; 	// CAN邮箱5
	AT91S_CAN_MB	 CAN_MB6; 	// CAN邮箱6
	AT91S_CAN_MB	 CAN_MB7; 	// CAN邮箱7
	AT91S_CAN_MB	 CAN_MB8; 	// CAN邮箱8
	AT91S_CAN_MB	 CAN_MB9; 	// CAN邮箱9
	AT91S_CAN_MB	 CAN_MB10; 	// CAN邮箱10
	AT91S_CAN_MB	 CAN_MB11; 	// CAN邮箱11
	AT91S_CAN_MB	 CAN_MB12; 	// CAN邮箱12
	AT91S_CAN_MB	 CAN_MB13; 	// CAN邮箱13
	AT91S_CAN_MB	 CAN_MB14; 	// CAN邮箱14
	AT91S_CAN_MB	 CAN_MB15; 	// CAN邮箱15
} AT91S_CAN, *AT91PS_CAN;

// --------CAN_MR：（CAN偏移：0x0）CAN模式寄存器--------
#define AT91C_CAN_CANEN       ((unsigned int) 0x1 <<  0) // （CAN）CAN控制器启用
#define AT91C_CAN_LPM         ((unsigned int) 0x1 <<  1) // （CAN）禁用/启用低功率模式
#define AT91C_CAN_ABM         ((unsigned int) 0x1 <<  2) // （CAN）禁用/启用自动驾驶/监听模式
#define AT91C_CAN_OVL         ((unsigned int) 0x1 <<  3) // （CAN）禁用/启用过载框架
#define AT91C_CAN_TEOF        ((unsigned int) 0x1 <<  4) // （CAN）帧两端的时间戳消息
#define AT91C_CAN_TTM         ((unsigned int) 0x1 <<  5) // （CAN）禁用/启用时间触发模式
#define AT91C_CAN_TIMFRZ      ((unsigned int) 0x1 <<  6) // （CAN）启用计时器冻结
#define AT91C_CAN_DRPT        ((unsigned int) 0x1 <<  7) // （CAN）禁用重复
// --------CAN_IER：（CAN偏移：0x4）CAN中断启用寄存器--------
#define AT91C_CAN_MB0         ((unsigned int) 0x1 <<  0) // （CAN）邮箱0标志
#define AT91C_CAN_MB1         ((unsigned int) 0x1 <<  1) // （CAN）邮箱1标志
#define AT91C_CAN_MB2         ((unsigned int) 0x1 <<  2) // （CAN）邮箱2标志
#define AT91C_CAN_MB3         ((unsigned int) 0x1 <<  3) // （CAN）邮箱3标志
#define AT91C_CAN_MB4         ((unsigned int) 0x1 <<  4) // （CAN）邮箱4标志
#define AT91C_CAN_MB5         ((unsigned int) 0x1 <<  5) // （CAN）邮箱5标志
#define AT91C_CAN_MB6         ((unsigned int) 0x1 <<  6) // （CAN）邮箱6标志
#define AT91C_CAN_MB7         ((unsigned int) 0x1 <<  7) // （CAN）邮箱7标志
#define AT91C_CAN_MB8         ((unsigned int) 0x1 <<  8) // （CAN）邮箱8标志
#define AT91C_CAN_MB9         ((unsigned int) 0x1 <<  9) // （CAN）邮箱9标志
#define AT91C_CAN_MB10        ((unsigned int) 0x1 << 10) // （CAN）邮箱10标志
#define AT91C_CAN_MB11        ((unsigned int) 0x1 << 11) // （CAN）邮箱11标志
#define AT91C_CAN_MB12        ((unsigned int) 0x1 << 12) // （CAN）邮箱12标志
#define AT91C_CAN_MB13        ((unsigned int) 0x1 << 13) // （CAN）邮箱13标志
#define AT91C_CAN_MB14        ((unsigned int) 0x1 << 14) // （CAN）邮箱14标志
#define AT91C_CAN_MB15        ((unsigned int) 0x1 << 15) // （CAN）邮箱15标志
#define AT91C_CAN_ERRA        ((unsigned int) 0x1 << 16) // （CAN）错误激活模式标志
#define AT91C_CAN_WARN        ((unsigned int) 0x1 << 17) // （CAN）警告限制标志
#define AT91C_CAN_ERRP        ((unsigned int) 0x1 << 18) // （CAN）错误被动模式标志
#define AT91C_CAN_BOFF        ((unsigned int) 0x1 << 19) // （CAN）总线关闭模式标志
#define AT91C_CAN_SLEEP       ((unsigned int) 0x1 << 20) // （CAN）休眠标志
#define AT91C_CAN_WAKEUP      ((unsigned int) 0x1 << 21) // （CAN）唤醒标志
#define AT91C_CAN_TOVF        ((unsigned int) 0x1 << 22) // （CAN）计时器溢出标志
#define AT91C_CAN_TSTP        ((unsigned int) 0x1 << 23) // （CAN）时间戳标志
#define AT91C_CAN_CERR        ((unsigned int) 0x1 << 24) // （CAN）CRC错误
#define AT91C_CAN_SERR        ((unsigned int) 0x1 << 25) // （CAN）填充错误
#define AT91C_CAN_AERR        ((unsigned int) 0x1 << 26) // （CAN）确认错误
#define AT91C_CAN_FERR        ((unsigned int) 0x1 << 27) // （CAN）表单错误
#define AT91C_CAN_BERR        ((unsigned int) 0x1 << 28) // （CAN）位错误
// --------CAN_IDR:（CAN偏移：0x8）CAN中断禁用寄存器--------
// --------CAN_IMR：（CAN偏移：0xc）CAN中断掩码寄存器--------
// --------CAN_SR：（CAN偏移：0x10）CAN状态寄存器--------
#define AT91C_CAN_RBSY        ((unsigned int) 0x1 << 29) // （CAN）接收器忙
#define AT91C_CAN_TBSY        ((unsigned int) 0x1 << 30) // （CAN）发射器忙
#define AT91C_CAN_OVLY        ((unsigned int) 0x1 << 31) // （CAN）过载忙
// --------CAN_BR：（CAN偏移：0x14）CAN波特率寄存器--------
#define AT91C_CAN_PHASE2      ((unsigned int) 0x7 <<  0) // （CAN）阶段2段
#define AT91C_CAN_PHASE1      ((unsigned int) 0x7 <<  4) // （CAN）阶段1段
#define AT91C_CAN_PROPAG      ((unsigned int) 0x7 <<  8) // （CAN）编程时间段
#define AT91C_CAN_SYNC        ((unsigned int) 0x3 << 12) // （CAN）重新同步跳跃宽度段
#define AT91C_CAN_BRP         ((unsigned int) 0x7F << 16) // （CAN）波特率预分频器
#define AT91C_CAN_SMP         ((unsigned int) 0x1 << 24) // （CAN）采样模式
// --------CAN_TIM:（CAN偏移：0x18）CAN计时器寄存器--------
#define AT91C_CAN_TIMER       ((unsigned int) 0xFFFF <<  0) // （CAN）计时器字段
// --------CAN_TIMESTP:（CAN偏移：0x1c）CAN时间戳寄存器--------
// --------CAN_ECR:（CAN偏移：0x20）CAN错误计数器寄存器--------
#define AT91C_CAN_REC         ((unsigned int) 0xFF <<  0) // （CAN）接收错误计数器
#define AT91C_CAN_TEC         ((unsigned int) 0xFF << 16) // （CAN）传输错误计数器
// --------CAN_TCR：（CAN偏移：0x24）CAN传输命令寄存器--------
#define AT91C_CAN_TIMRST      ((unsigned int) 0x1 << 31) // （CAN）计时器重置字段
// --------CAN_ACR:（CAN偏移：0x28）CAN中止命令寄存器--------

// *****************************************************************************
//              以太网MAC 10/100的软件API定义
// *****************************************************************************
typedef struct _AT91S_EMAC {
	AT91_REG	 EMAC_NCR; 	// 网络控制寄存器
	AT91_REG	 EMAC_NCFGR; 	// 网络配置寄存器
	AT91_REG	 EMAC_NSR; 	// 网络状态寄存器
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 EMAC_TSR; 	// 传输状态寄存器
	AT91_REG	 EMAC_RBQP; 	// 接收缓冲区队列指针
	AT91_REG	 EMAC_TBQP; 	// 传输缓冲区队列指针
	AT91_REG	 EMAC_RSR; 	// 接收状态寄存器
	AT91_REG	 EMAC_ISR; 	// 中断状态寄存器
	AT91_REG	 EMAC_IER; 	// 中断启用寄存器
	AT91_REG	 EMAC_IDR; 	// 中断禁用寄存器
	AT91_REG	 EMAC_IMR; 	// 中断掩码寄存器
	AT91_REG	 EMAC_MAN; 	// PHY维护寄存器
	AT91_REG	 EMAC_PTR; 	// 暂停时间寄存器
	AT91_REG	 EMAC_PFR; 	// 暂停帧接收寄存器
	AT91_REG	 EMAC_FTO; 	// 帧发送OK寄存器
	AT91_REG	 EMAC_SCF; 	// 单碰撞帧寄存器
	AT91_REG	 EMAC_MCF; 	// 多冲突帧寄存器
	AT91_REG	 EMAC_FRO; 	// 帧接收OK寄存器
	AT91_REG	 EMAC_FCSE; 	// 帧检查序列错误寄存器
	AT91_REG	 EMAC_ALE; 	// 对齐错误寄存器
	AT91_REG	 EMAC_DTF; 	// 延迟传输帧寄存器
	AT91_REG	 EMAC_LCOL; 	// 延迟碰撞登记
	AT91_REG	 EMAC_ECOL; 	// 过度碰撞寄存器
	AT91_REG	 EMAC_TUND; 	// 传输欠载错误寄存器
	AT91_REG	 EMAC_CSE; 	// 载波检测错误寄存器
	AT91_REG	 EMAC_RRE; 	// 接收资源错误寄存器
	AT91_REG	 EMAC_ROV; 	// 接收溢出错误寄存器
	AT91_REG	 EMAC_RSE; 	// 接收符号错误寄存器
	AT91_REG	 EMAC_ELE; 	// 超长错误寄存器
	AT91_REG	 EMAC_RJA; 	// 接收Jabbers注册
	AT91_REG	 EMAC_USF; 	// 缩小帧寄存器
	AT91_REG	 EMAC_STE; 	// SQE测试错误寄存器
	AT91_REG	 EMAC_RLE; 	// 接收长度字段不匹配寄存器
	AT91_REG	 EMAC_TPF; 	// 发送的暂停帧寄存器
	AT91_REG	 EMAC_HRB; 	// 哈希地址底部[31:0]
	AT91_REG	 EMAC_HRT; 	// 哈希地址顶部[63:32]
	AT91_REG	 EMAC_SA1L; 	// 特定地址1底部，前4字节
	AT91_REG	 EMAC_SA1H; 	// 特定地址1顶部，最后2字节
	AT91_REG	 EMAC_SA2L; 	// 特定地址2底部，前4字节
	AT91_REG	 EMAC_SA2H; 	// 特定地址2顶部，最后2个字节
	AT91_REG	 EMAC_SA3L; 	// 特定地址3底部，前4字节
	AT91_REG	 EMAC_SA3H; 	// 特定地址3顶部，最后2个字节
	AT91_REG	 EMAC_SA4L; 	// 特定地址4底部，前4字节
	AT91_REG	 EMAC_SA4H; 	// 特定地址4顶部，最后2个字节
	AT91_REG	 EMAC_TID; 	// 类型ID检查寄存器
	AT91_REG	 EMAC_TPQ; 	// 传输暂停量子寄存器
	AT91_REG	 EMAC_USRIO; 	// 用户输入/输出寄存器
	AT91_REG	 EMAC_WOL; 	// LAN唤醒寄存器
	AT91_REG	 Reserved1[13]; 	// 
	AT91_REG	 EMAC_REV; 	// 修订登记簿
} AT91S_EMAC, *AT91PS_EMAC;

// --------EMAC_NCR：（EMAC偏移：0x0）--------
#define AT91C_EMAC_LB         ((unsigned int) 0x1 <<  0) // （EMAC）环回。可选择的设置后，回送信号处于高电平。
#define AT91C_EMAC_LLB        ((unsigned int) 0x1 <<  1) // （EMAC）本地环回。
#define AT91C_EMAC_RE         ((unsigned int) 0x1 <<  2) // （EMAC）接收启用。
#define AT91C_EMAC_TE         ((unsigned int) 0x1 <<  3) // （EMAC）发射启用。
#define AT91C_EMAC_MPE        ((unsigned int) 0x1 <<  4) // （EMAC）管理端口启用。
#define AT91C_EMAC_CLRSTAT    ((unsigned int) 0x1 <<  5) // （EMAC）清除统计寄存器。
#define AT91C_EMAC_INCSTAT    ((unsigned int) 0x1 <<  6) // （EMAC）增量统计寄存器。
#define AT91C_EMAC_WESTAT     ((unsigned int) 0x1 <<  7) // （EMAC）统计寄存器的写入启用。
#define AT91C_EMAC_BP         ((unsigned int) 0x1 <<  8) // （EMAC）背压。
#define AT91C_EMAC_TSTART     ((unsigned int) 0x1 <<  9) // （EMAC）开始传输。
#define AT91C_EMAC_THALT      ((unsigned int) 0x1 << 10) // （EMAC）传输停止。
#define AT91C_EMAC_TPFR       ((unsigned int) 0x1 << 11) // （EMAC）发送暂停帧
#define AT91C_EMAC_TZQ        ((unsigned int) 0x1 << 12) // （EMAC）发送零量子暂停帧
// --------EMAC_NCFGR：（EMAC偏移：0x4）网络配置寄存器--------
#define AT91C_EMAC_SPD        ((unsigned int) 0x1 <<  0) // （EMAC）速度。
#define AT91C_EMAC_FD         ((unsigned int) 0x1 <<  1) // （EMAC）全双工。
#define AT91C_EMAC_JFRAME     ((unsigned int) 0x1 <<  3) // （EMAC）巨型框架。
#define AT91C_EMAC_CAF        ((unsigned int) 0x1 <<  4) // （EMAC）复制所有帧。
#define AT91C_EMAC_NBC        ((unsigned int) 0x1 <<  5) // （EMAC）没有广播。
#define AT91C_EMAC_MTI        ((unsigned int) 0x1 <<  6) // （EMAC）多播哈希事件启用
#define AT91C_EMAC_UNI        ((unsigned int) 0x1 <<  7) // （EMAC）启用单播哈希。
#define AT91C_EMAC_BIG        ((unsigned int) 0x1 <<  8) // （EMAC）接收1522字节。
#define AT91C_EMAC_EAE        ((unsigned int) 0x1 <<  9) // （EMAC）外部地址匹配启用。
#define AT91C_EMAC_CLK        ((unsigned int) 0x3 << 10) // (EMAC) 
#define 	AT91C_EMAC_CLK_HCLK_8               ((unsigned int) 0x0 << 10) // （EMAC）HCLK除以8
#define 	AT91C_EMAC_CLK_HCLK_16              ((unsigned int) 0x1 << 10) // （EMAC）HCLK除以16
#define 	AT91C_EMAC_CLK_HCLK_32              ((unsigned int) 0x2 << 10) // （EMAC）HCLK除以32
#define 	AT91C_EMAC_CLK_HCLK_64              ((unsigned int) 0x3 << 10) // （EMAC）HCLK除以64
#define AT91C_EMAC_RTY        ((unsigned int) 0x1 << 12) // (EMAC) 
#define AT91C_EMAC_PAE        ((unsigned int) 0x1 << 13) // (EMAC) 
#define AT91C_EMAC_RBOF       ((unsigned int) 0x3 << 14) // (EMAC) 
#define 	AT91C_EMAC_RBOF_OFFSET_0             ((unsigned int) 0x0 << 14) // （EMAC）从接收缓冲区开始无偏移
#define 	AT91C_EMAC_RBOF_OFFSET_1             ((unsigned int) 0x1 << 14) // （EMAC）从接收缓冲区开始的一个字节偏移
#define 	AT91C_EMAC_RBOF_OFFSET_2             ((unsigned int) 0x2 << 14) // （EMAC）从接收缓冲区开始偏移两个字节
#define 	AT91C_EMAC_RBOF_OFFSET_3             ((unsigned int) 0x3 << 14) // （EMAC）从接收缓冲区开始偏移三个字节
#define AT91C_EMAC_RLCE       ((unsigned int) 0x1 << 16) // （EMAC）接收长度字段检查启用
#define AT91C_EMAC_DRFCS      ((unsigned int) 0x1 << 17) // （EMAC）放弃接收FCS
#define AT91C_EMAC_EFRHD      ((unsigned int) 0x1 << 18) // (EMAC) 
#define AT91C_EMAC_IRXFCS     ((unsigned int) 0x1 << 19) // （EMAC）忽略RX FCS
// --------EMAC_NSR:（EMAC偏移量：0x8）网络状态寄存器--------
#define AT91C_EMAC_LINKR      ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_MDIO       ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_IDLE       ((unsigned int) 0x1 <<  2) // (EMAC) 
// --------EMAC_TSR：（EMAC偏移：0x14）传输状态寄存器--------
#define AT91C_EMAC_UBR        ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_COL        ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_RLES       ((unsigned int) 0x1 <<  2) // (EMAC) 
#define AT91C_EMAC_TGO        ((unsigned int) 0x1 <<  3) // （EMAC）发送开始
#define AT91C_EMAC_BEX        ((unsigned int) 0x1 <<  4) // （EMAC）中间帧缓冲区耗尽
#define AT91C_EMAC_COMP       ((unsigned int) 0x1 <<  5) // (EMAC) 
#define AT91C_EMAC_UND        ((unsigned int) 0x1 <<  6) // (EMAC) 
// --------EMAC_RSR：（EMAC偏移：0x20）接收状态寄存器--------
#define AT91C_EMAC_BNA        ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_REC        ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_OVR        ((unsigned int) 0x1 <<  2) // (EMAC) 
// --------EMAC_ISR：（EMAC偏移：0x24）中断状态寄存器--------
#define AT91C_EMAC_MFD        ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_RCOMP      ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_RXUBR      ((unsigned int) 0x1 <<  2) // (EMAC) 
#define AT91C_EMAC_TXUBR      ((unsigned int) 0x1 <<  3) // (EMAC) 
#define AT91C_EMAC_TUNDR      ((unsigned int) 0x1 <<  4) // (EMAC) 
#define AT91C_EMAC_RLEX       ((unsigned int) 0x1 <<  5) // (EMAC) 
#define AT91C_EMAC_TXERR      ((unsigned int) 0x1 <<  6) // (EMAC) 
#define AT91C_EMAC_TCOMP      ((unsigned int) 0x1 <<  7) // (EMAC) 
#define AT91C_EMAC_LINK       ((unsigned int) 0x1 <<  9) // (EMAC) 
#define AT91C_EMAC_ROVR       ((unsigned int) 0x1 << 10) // (EMAC) 
#define AT91C_EMAC_HRESP      ((unsigned int) 0x1 << 11) // (EMAC) 
#define AT91C_EMAC_PFRE       ((unsigned int) 0x1 << 12) // (EMAC) 
#define AT91C_EMAC_PTZ        ((unsigned int) 0x1 << 13) // (EMAC) 
// --------EMAC_IER:（EMAC偏移：0x28）中断启用寄存器--------
// --------EMAC_IDR：（EMAC偏移：0x2c）中断禁用寄存器--------
// --------EMAC_IMR：（EMAC偏移：0x30）中断掩码寄存器--------
// --------EMAC_MAN：（EMAC偏移：0x34）PHY维护寄存器--------
#define AT91C_EMAC_DATA       ((unsigned int) 0xFFFF <<  0) // (EMAC) 
#define AT91C_EMAC_CODE       ((unsigned int) 0x3 << 16) // (EMAC) 
#define AT91C_EMAC_REGA       ((unsigned int) 0x1F << 18) // (EMAC) 
#define AT91C_EMAC_PHYA       ((unsigned int) 0x1F << 23) // (EMAC) 
#define AT91C_EMAC_RW         ((unsigned int) 0x3 << 28) // (EMAC) 
#define AT91C_EMAC_SOF        ((unsigned int) 0x3 << 30) // (EMAC) 
// --------EMAC_USRIO：（EMAC偏移：0xc0）用户输入输出寄存器--------
#define AT91C_EMAC_RMII       ((unsigned int) 0x1 <<  0) // （EMAC）减少MII
#define AT91C_EMAC_CLKEN      ((unsigned int) 0x1 <<  1) // （EMAC）时钟启用
// --------EMAC_WOL：（EMAC偏移：0xc4）LAN唤醒寄存器--------
#define AT91C_EMAC_IP         ((unsigned int) 0xFFFF <<  0) // （EMAC）ARP请求IP地址
#define AT91C_EMAC_MAG        ((unsigned int) 0x1 << 16) // （EMAC）魔术包事件启用
#define AT91C_EMAC_ARP        ((unsigned int) 0x1 << 17) // （EMAC）ARP请求事件启用
#define AT91C_EMAC_SA1        ((unsigned int) 0x1 << 18) // （EMAC）特定地址寄存器1事件启用
// --------EMAC_REV：（EMAC偏移：0xfc）修订寄存器--------
#define AT91C_EMAC_REVREF     ((unsigned int) 0xFFFF <<  0) // (EMAC) 
#define AT91C_EMAC_PARTREF    ((unsigned int) 0xFFFF << 16) // (EMAC) 

// *****************************************************************************
//              模数转换器的软件API定义
// *****************************************************************************
typedef struct _AT91S_ADC {
	AT91_REG	 ADC_CR; 	// ADC控制寄存器
	AT91_REG	 ADC_MR; 	// ADC模式寄存器
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 ADC_CHER; 	// ADC通道启用寄存器
	AT91_REG	 ADC_CHDR; 	// ADC通道禁用寄存器
	AT91_REG	 ADC_CHSR; 	// ADC通道状态寄存器
	AT91_REG	 ADC_SR; 	// ADC状态寄存器
	AT91_REG	 ADC_LCDR; 	// ADC上次转换的数据寄存器
	AT91_REG	 ADC_IER; 	// ADC中断启用寄存器
	AT91_REG	 ADC_IDR; 	// ADC中断禁用寄存器
	AT91_REG	 ADC_IMR; 	// ADC中断掩码寄存器
	AT91_REG	 ADC_CDR0; 	// ADC通道数据寄存器0
	AT91_REG	 ADC_CDR1; 	// ADC通道数据寄存器1
	AT91_REG	 ADC_CDR2; 	// ADC通道数据寄存器2
	AT91_REG	 ADC_CDR3; 	// ADC通道数据寄存器3
	AT91_REG	 ADC_CDR4; 	// ADC通道数据寄存器4
	AT91_REG	 ADC_CDR5; 	// ADC通道数据寄存器5
	AT91_REG	 ADC_CDR6; 	// ADC通道数据寄存器6
	AT91_REG	 ADC_CDR7; 	// ADC通道数据寄存器7
	AT91_REG	 Reserved1[44]; 	// 
	AT91_REG	 ADC_RPR; 	// 接收指针寄存器
	AT91_REG	 ADC_RCR; 	// 接收计数器寄存器
	AT91_REG	 ADC_TPR; 	// 发送指针寄存器
	AT91_REG	 ADC_TCR; 	// 发送计数器寄存器
	AT91_REG	 ADC_RNPR; 	// 接收下一个指针寄存器
	AT91_REG	 ADC_RNCR; 	// 接收下一计数器寄存器
	AT91_REG	 ADC_TNPR; 	// 发送下一指针寄存器
	AT91_REG	 ADC_TNCR; 	// 发送下一计数器寄存器
	AT91_REG	 ADC_PTCR; 	// PDC传输控制寄存器
	AT91_REG	 ADC_PTSR; 	// PDC传输状态寄存器
} AT91S_ADC, *AT91PS_ADC;

// --------ADC_CR:（ADC偏移：0x0）ADC控制寄存器--------
#define AT91C_ADC_SWRST       ((unsigned int) 0x1 <<  0) // （ADC）软件重置
#define AT91C_ADC_START       ((unsigned int) 0x1 <<  1) // （ADC）开始转换
// --------ADC_MR:（ADC偏移：0x4）ADC模式寄存器--------
#define AT91C_ADC_TRGEN       ((unsigned int) 0x1 <<  0) // （ADC）触发启用
#define 	AT91C_ADC_TRGEN_DIS                  ((unsigned int) 0x0) // （ADC）Hradware触发器已禁用。只能通过软件启动转换
#define 	AT91C_ADC_TRGEN_EN                   ((unsigned int) 0x1) // （ADC）启用TRGSEL字段选择的硬件触发器。
#define AT91C_ADC_TRGSEL      ((unsigned int) 0x7 <<  1) // （ADC）触发选择
#define 	AT91C_ADC_TRGSEL_TIOA0                ((unsigned int) 0x0 <<  1) // （ADC）所选TRGSEL=TIAO0
#define 	AT91C_ADC_TRGSEL_TIOA1                ((unsigned int) 0x1 <<  1) // （ADC）所选TRGSEL=TIAO1
#define 	AT91C_ADC_TRGSEL_TIOA2                ((unsigned int) 0x2 <<  1) // （ADC）所选TRGSEL=TIAO2
#define 	AT91C_ADC_TRGSEL_TIOA3                ((unsigned int) 0x3 <<  1) // （ADC）所选TRGSEL=TIAO3
#define 	AT91C_ADC_TRGSEL_TIOA4                ((unsigned int) 0x4 <<  1) // （ADC）所选TRGSEL=TIAO4
#define 	AT91C_ADC_TRGSEL_TIOA5                ((unsigned int) 0x5 <<  1) // （ADC）所选TRGSEL=TIAO5
#define 	AT91C_ADC_TRGSEL_EXT                  ((unsigned int) 0x6 <<  1) // （ADC）所选TRGSEL=外部触发器
#define AT91C_ADC_LOWRES      ((unsigned int) 0x1 <<  4) // （ADC）分辨率。
#define 	AT91C_ADC_LOWRES_10_BIT               ((unsigned int) 0x0 <<  4) // （ADC）10位分辨率
#define 	AT91C_ADC_LOWRES_8_BIT                ((unsigned int) 0x1 <<  4) // （ADC）8位分辨率
#define AT91C_ADC_SLEEP       ((unsigned int) 0x1 <<  5) // （ADC）睡眠模式
#define 	AT91C_ADC_SLEEP_NORMAL_MODE          ((unsigned int) 0x0 <<  5) // （ADC）正常模式
#define 	AT91C_ADC_SLEEP_MODE                 ((unsigned int) 0x1 <<  5) // （ADC）睡眠模式
#define AT91C_ADC_PRESCAL     ((unsigned int) 0x3F <<  8) // （ADC）预缩放速率选择
#define AT91C_ADC_STARTUP     ((unsigned int) 0x1F << 16) // （ADC）启动时间
#define AT91C_ADC_SHTIM       ((unsigned int) 0xF << 24) // （ADC）采样和保持时间
// --------ADC_CHER：（ADC偏移：0x10）ADC通道启用寄存器--------
#define AT91C_ADC_CH0         ((unsigned int) 0x1 <<  0) // （ADC）通道0
#define AT91C_ADC_CH1         ((unsigned int) 0x1 <<  1) // （ADC）通道1
#define AT91C_ADC_CH2         ((unsigned int) 0x1 <<  2) // （ADC）通道2
#define AT91C_ADC_CH3         ((unsigned int) 0x1 <<  3) // （ADC）通道3
#define AT91C_ADC_CH4         ((unsigned int) 0x1 <<  4) // （ADC）通道4
#define AT91C_ADC_CH5         ((unsigned int) 0x1 <<  5) // （ADC）通道5
#define AT91C_ADC_CH6         ((unsigned int) 0x1 <<  6) // （ADC）通道6
#define AT91C_ADC_CH7         ((unsigned int) 0x1 <<  7) // （ADC）通道7
// --------ADC_CHDR：（ADC偏移：0x14）ADC通道禁用寄存器--------
// --------ADC_HSR:（ADC偏移：0x18）ADC通道状态寄存器--------
// --------ADC_SR：（ADC偏移量：0x1c）ADC状态寄存器--------
#define AT91C_ADC_EOC0        ((unsigned int) 0x1 <<  0) // （ADC）转换结束
#define AT91C_ADC_EOC1        ((unsigned int) 0x1 <<  1) // （ADC）转换结束
#define AT91C_ADC_EOC2        ((unsigned int) 0x1 <<  2) // （ADC）转换结束
#define AT91C_ADC_EOC3        ((unsigned int) 0x1 <<  3) // （ADC）转换结束
#define AT91C_ADC_EOC4        ((unsigned int) 0x1 <<  4) // （ADC）转换结束
#define AT91C_ADC_EOC5        ((unsigned int) 0x1 <<  5) // （ADC）转换结束
#define AT91C_ADC_EOC6        ((unsigned int) 0x1 <<  6) // （ADC）转换结束
#define AT91C_ADC_EOC7        ((unsigned int) 0x1 <<  7) // （ADC）转换结束
#define AT91C_ADC_OVRE0       ((unsigned int) 0x1 <<  8) // （ADC）超限错误
#define AT91C_ADC_OVRE1       ((unsigned int) 0x1 <<  9) // （ADC）超限错误
#define AT91C_ADC_OVRE2       ((unsigned int) 0x1 << 10) // （ADC）超限错误
#define AT91C_ADC_OVRE3       ((unsigned int) 0x1 << 11) // （ADC）超限错误
#define AT91C_ADC_OVRE4       ((unsigned int) 0x1 << 12) // （ADC）超限错误
#define AT91C_ADC_OVRE5       ((unsigned int) 0x1 << 13) // （ADC）超限错误
#define AT91C_ADC_OVRE6       ((unsigned int) 0x1 << 14) // （ADC）超限错误
#define AT91C_ADC_OVRE7       ((unsigned int) 0x1 << 15) // （ADC）超限错误
#define AT91C_ADC_DRDY        ((unsigned int) 0x1 << 16) // （ADC）数据就绪
#define AT91C_ADC_GOVRE       ((unsigned int) 0x1 << 17) // （ADC）一般超限
#define AT91C_ADC_ENDRX       ((unsigned int) 0x1 << 18) // （ADC）接收器传输结束
#define AT91C_ADC_RXBUFF      ((unsigned int) 0x1 << 19) // （ADC）RXBUFF中断
// --------ADC_LCD:（ADC偏移量：0x20）ADC上次转换的数据寄存器--------
#define AT91C_ADC_LDATA       ((unsigned int) 0x3FF <<  0) // （ADC）上次转换的数据
// --------ADC_IER:（ADC偏移：0x24）ADC中断启用寄存器--------
// --------ADC_IDR:（ADC偏移量：0x28）ADC中断禁用寄存器--------
// --------ADC_IMR:（ADC偏移量：0x2c）ADC中断掩码寄存器--------
// --------ADC_CDR0:（ADC偏移量：0x30）ADC通道数据寄存器0--------
#define AT91C_ADC_DATA        ((unsigned int) 0x3FF <<  0) // （ADC）转换数据
// --------ADC_CDR1:（ADC偏移：0x34）ADC通道数据寄存器1---------
// --------ADC_CDR2:（ADC偏移：0x38）ADC通道数据寄存器2---------
// --------ADC_CDR3:（ADC偏移：0x3c）ADC通道数据寄存器3---------
// --------ADC_CDR4:（ADC偏移：0x40）ADC通道数据寄存器4---------
// --------ADC_CDR5:（ADC偏移：0x44）ADC通道数据寄存器5---------
// --------ADC_CDR6：（ADC偏移量：0x48）ADC通道数据寄存器6---------
// --------ADC_CDR7：（ADC偏移量：0x4c）ADC通道数据寄存器7---------

// *****************************************************************************
//               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256
// *****************************************************************************
// ============SYS外围设备的寄存器定义============
// ============AIC外围设备的寄存器定义============
#define AT91C_AIC_IVR   ((AT91_REG *) 	0xFFFFF100) // （AIC）IRQ矢量寄存器
#define AT91C_AIC_SMR   ((AT91_REG *) 	0xFFFFF000) // （AIC）源模式寄存器
#define AT91C_AIC_FVR   ((AT91_REG *) 	0xFFFFF104) // （AIC）FIQ矢量寄存器
#define AT91C_AIC_DCR   ((AT91_REG *) 	0xFFFFF138) // （AIC）调试控制寄存器（保护）
#define AT91C_AIC_EOICR ((AT91_REG *) 	0xFFFFF130) // （AIC）中断命令寄存器结束
#define AT91C_AIC_SVR   ((AT91_REG *) 	0xFFFFF080) // （AIC）源矢量寄存器
#define AT91C_AIC_FFSR  ((AT91_REG *) 	0xFFFFF148) // （AIC）快速强制状态寄存器
#define AT91C_AIC_ICCR  ((AT91_REG *) 	0xFFFFF128) // （AIC）中断清除命令寄存器
#define AT91C_AIC_ISR   ((AT91_REG *) 	0xFFFFF108) // （AIC）中断状态寄存器
#define AT91C_AIC_IMR   ((AT91_REG *) 	0xFFFFF110) // （AIC）中断掩码寄存器
#define AT91C_AIC_IPR   ((AT91_REG *) 	0xFFFFF10C) // （AIC）中断挂起寄存器
#define AT91C_AIC_FFER  ((AT91_REG *) 	0xFFFFF140) // （AIC）快速强制启用寄存器
#define AT91C_AIC_IECR  ((AT91_REG *) 	0xFFFFF120) // （AIC）中断启用命令寄存器
#define AT91C_AIC_ISCR  ((AT91_REG *) 	0xFFFFF12C) // （AIC）中断设置命令寄存器
#define AT91C_AIC_FFDR  ((AT91_REG *) 	0xFFFFF144) // （AIC）快速强制禁用寄存器
#define AT91C_AIC_CISR  ((AT91_REG *) 	0xFFFFF114) // （AIC）核心中断状态寄存器
#define AT91C_AIC_IDCR  ((AT91_REG *) 	0xFFFFF124) // （AIC）中断禁用命令寄存器
#define AT91C_AIC_SPU   ((AT91_REG *) 	0xFFFFF134) // （AIC）杂散矢量寄存器
// ============PDC_DBGU外围设备的寄存器定义============
#define AT91C_DBGU_TCR  ((AT91_REG *) 	0xFFFFF30C) // （PDC_DBGU）发送计数器寄存器
#define AT91C_DBGU_RNPR ((AT91_REG *) 	0xFFFFF310) // （PDC_DBGU）接收下一个指针寄存器
#define AT91C_DBGU_TNPR ((AT91_REG *) 	0xFFFFF318) // （PDC_DBGU）发送下一个指针寄存器
#define AT91C_DBGU_TPR  ((AT91_REG *) 	0xFFFFF308) // （PDC_DBGU）发送指针寄存器
#define AT91C_DBGU_RPR  ((AT91_REG *) 	0xFFFFF300) // （PDC_DBGU）接收指针寄存器
#define AT91C_DBGU_RCR  ((AT91_REG *) 	0xFFFFF304) // （PDC_DBGU）接收计数器寄存器
#define AT91C_DBGU_RNCR ((AT91_REG *) 	0xFFFFF314) // （PDC_DBGU）接收下一个计数器寄存器
#define AT91C_DBGU_PTCR ((AT91_REG *) 	0xFFFFF320) // （PDC_DBGU）PDC传输控制寄存器
#define AT91C_DBGU_PTSR ((AT91_REG *) 	0xFFFFF324) // （PDC_DBGU）PDC传输状态寄存器
#define AT91C_DBGU_TNCR ((AT91_REG *) 	0xFFFFF31C) // （PDC_DBGU）发送下一计数器寄存器
// ============DBGU外围设备的寄存器定义============
#define AT91C_DBGU_EXID ((AT91_REG *) 	0xFFFFF244) // （DBGU）芯片ID扩展寄存器
#define AT91C_DBGU_BRGR ((AT91_REG *) 	0xFFFFF220) // （DBGU）波特率生成器寄存器
#define AT91C_DBGU_IDR  ((AT91_REG *) 	0xFFFFF20C) // （DBGU）中断禁用寄存器
#define AT91C_DBGU_CSR  ((AT91_REG *) 	0xFFFFF214) // （DBGU）信道状态寄存器
#define AT91C_DBGU_CIDR ((AT91_REG *) 	0xFFFFF240) // （DBGU）芯片ID寄存器
#define AT91C_DBGU_MR   ((AT91_REG *) 	0xFFFFF204) // （DBGU）模式寄存器
#define AT91C_DBGU_IMR  ((AT91_REG *) 	0xFFFFF210) // （DBGU）中断掩码寄存器
#define AT91C_DBGU_CR   ((AT91_REG *) 	0xFFFFF200) // （DBGU）控制寄存器
#define AT91C_DBGU_FNTR ((AT91_REG *) 	0xFFFFF248) // （DBGU）强制NTRST寄存器
#define AT91C_DBGU_THR  ((AT91_REG *) 	0xFFFFF21C) // （DBGU）发射机保持寄存器
#define AT91C_DBGU_RHR  ((AT91_REG *) 	0xFFFFF218) // （DBGU）接收机保持寄存器
#define AT91C_DBGU_IER  ((AT91_REG *) 	0xFFFFF208) // （DBGU）中断启用寄存器
// ============PIOA外围设备的寄存器定义============
#define AT91C_PIOA_ODR  ((AT91_REG *) 	0xFFFFF414) // （PIOA）输出禁用寄存器
#define AT91C_PIOA_SODR ((AT91_REG *) 	0xFFFFF430) // （PIOA）设置输出数据寄存器
#define AT91C_PIOA_ISR  ((AT91_REG *) 	0xFFFFF44C) // （PIOA）中断状态寄存器
#define AT91C_PIOA_ABSR ((AT91_REG *) 	0xFFFFF478) // （PIOA）AB选择状态寄存器
#define AT91C_PIOA_IER  ((AT91_REG *) 	0xFFFFF440) // （PIOA）中断启用寄存器
#define AT91C_PIOA_PPUDR ((AT91_REG *) 	0xFFFFF460) // （PIOA）上拉禁用寄存器
#define AT91C_PIOA_IMR  ((AT91_REG *) 	0xFFFFF448) // （PIOA）中断掩码寄存器
#define AT91C_PIOA_PER  ((AT91_REG *) 	0xFFFFF400) // （PIOA）PIO启用寄存器
#define AT91C_PIOA_IFDR ((AT91_REG *) 	0xFFFFF424) // （PIOA）输入滤波器禁用寄存器
#define AT91C_PIOA_OWDR ((AT91_REG *) 	0xFFFFF4A4) // （PIOA）输出写入禁用寄存器
#define AT91C_PIOA_MDSR ((AT91_REG *) 	0xFFFFF458) // （PIOA）多驱动程序状态寄存器
#define AT91C_PIOA_IDR  ((AT91_REG *) 	0xFFFFF444) // （PIOA）中断禁用寄存器
#define AT91C_PIOA_ODSR ((AT91_REG *) 	0xFFFFF438) // （PIOA）输出数据状态寄存器
#define AT91C_PIOA_PPUSR ((AT91_REG *) 	0xFFFFF468) // （PIOA）上拉状态寄存器
#define AT91C_PIOA_OWSR ((AT91_REG *) 	0xFFFFF4A8) // （PIOA）输出写入状态寄存器
#define AT91C_PIOA_BSR  ((AT91_REG *) 	0xFFFFF474) // （PIOA）选择B寄存器
#define AT91C_PIOA_OWER ((AT91_REG *) 	0xFFFFF4A0) // （PIOA）输出写入启用寄存器
#define AT91C_PIOA_IFER ((AT91_REG *) 	0xFFFFF420) // （PIOA）输入滤波器启用寄存器
#define AT91C_PIOA_PDSR ((AT91_REG *) 	0xFFFFF43C) // （PIOA）引脚数据状态寄存器
#define AT91C_PIOA_PPUER ((AT91_REG *) 	0xFFFFF464) // （PIOA）上拉启用寄存器
#define AT91C_PIOA_OSR  ((AT91_REG *) 	0xFFFFF418) // （PIOA）输出状态寄存器
#define AT91C_PIOA_ASR  ((AT91_REG *) 	0xFFFFF470) // （PIOA）选择一个寄存器
#define AT91C_PIOA_MDDR ((AT91_REG *) 	0xFFFFF454) // （PIOA）多驱动程序禁用寄存器
#define AT91C_PIOA_CODR ((AT91_REG *) 	0xFFFFF434) // （PIOA）清除输出数据寄存器
#define AT91C_PIOA_MDER ((AT91_REG *) 	0xFFFFF450) // （PIOA）多驱动程序启用寄存器
#define AT91C_PIOA_PDR  ((AT91_REG *) 	0xFFFFF404) // （PIOA）PIO禁用寄存器
#define AT91C_PIOA_IFSR ((AT91_REG *) 	0xFFFFF428) // （PIOA）输入滤波器状态寄存器
#define AT91C_PIOA_OER  ((AT91_REG *) 	0xFFFFF410) // （PIOA）输出启用寄存器
#define AT91C_PIOA_PSR  ((AT91_REG *) 	0xFFFFF408) // （PIOA）PIO状态寄存器
// ============PIOB外围设备的寄存器定义============
#define AT91C_PIOB_OWDR ((AT91_REG *) 	0xFFFFF6A4) // （PIOB）输出写禁止寄存器
#define AT91C_PIOB_MDER ((AT91_REG *) 	0xFFFFF650) // （PIOB）多驱动器启用寄存器
#define AT91C_PIOB_PPUSR ((AT91_REG *) 	0xFFFFF668) // （PIOB）上拉状态寄存器
#define AT91C_PIOB_IMR  ((AT91_REG *) 	0xFFFFF648) // （PIOB）中断掩码寄存器
#define AT91C_PIOB_ASR  ((AT91_REG *) 	0xFFFFF670) // （PIOB）选择寄存器
#define AT91C_PIOB_PPUDR ((AT91_REG *) 	0xFFFFF660) // （PIOB）上拉禁用寄存器
#define AT91C_PIOB_PSR  ((AT91_REG *) 	0xFFFFF608) // （PIOB）PIO状态寄存器
#define AT91C_PIOB_IER  ((AT91_REG *) 	0xFFFFF640) // （PIOB）中断启用寄存器
#define AT91C_PIOB_CODR ((AT91_REG *) 	0xFFFFF634) // （PIOB）清除输出数据寄存器
#define AT91C_PIOB_OWER ((AT91_REG *) 	0xFFFFF6A0) // （PIOB）输出写入启用寄存器
#define AT91C_PIOB_ABSR ((AT91_REG *) 	0xFFFFF678) // （PIOB）AB选择状态寄存器
#define AT91C_PIOB_IFDR ((AT91_REG *) 	0xFFFFF624) // （PIOB）输入滤波器禁用寄存器
#define AT91C_PIOB_PDSR ((AT91_REG *) 	0xFFFFF63C) // （PIOB）引脚数据状态寄存器
#define AT91C_PIOB_IDR  ((AT91_REG *) 	0xFFFFF644) // （PIOB）中断禁用寄存器
#define AT91C_PIOB_OWSR ((AT91_REG *) 	0xFFFFF6A8) // （PIOB）输出写入状态寄存器
#define AT91C_PIOB_PDR  ((AT91_REG *) 	0xFFFFF604) // （PIOB）PIO禁用寄存器
#define AT91C_PIOB_ODR  ((AT91_REG *) 	0xFFFFF614) // （PIOB）输出禁用寄存器
#define AT91C_PIOB_IFSR ((AT91_REG *) 	0xFFFFF628) // （PIOB）输入滤波器状态寄存器
#define AT91C_PIOB_PPUER ((AT91_REG *) 	0xFFFFF664) // （PIOB）上拉启用寄存器
#define AT91C_PIOB_SODR ((AT91_REG *) 	0xFFFFF630) // （PIOB）设置输出数据寄存器
#define AT91C_PIOB_ISR  ((AT91_REG *) 	0xFFFFF64C) // （PIOB）中断状态寄存器
#define AT91C_PIOB_ODSR ((AT91_REG *) 	0xFFFFF638) // （PIOB）输出数据状态寄存器
#define AT91C_PIOB_OSR  ((AT91_REG *) 	0xFFFFF618) // （PIOB）输出状态寄存器
#define AT91C_PIOB_MDSR ((AT91_REG *) 	0xFFFFF658) // （PIOB）多驱动程序状态寄存器
#define AT91C_PIOB_IFER ((AT91_REG *) 	0xFFFFF620) // （PIOB）输入滤波器启用寄存器
#define AT91C_PIOB_BSR  ((AT91_REG *) 	0xFFFFF674) // （PIOB）选择B寄存器
#define AT91C_PIOB_MDDR ((AT91_REG *) 	0xFFFFF654) // （PIOB）多驱动器禁用寄存器
#define AT91C_PIOB_OER  ((AT91_REG *) 	0xFFFFF610) // （PIOB）输出启用寄存器
#define AT91C_PIOB_PER  ((AT91_REG *) 	0xFFFFF600) // （PIOB）PIO启用寄存器
// ============CKGR外围设备的寄存器定义============
#define AT91C_CKGR_MOR  ((AT91_REG *) 	0xFFFFFC20) // （CKGR）主振荡器寄存器
#define AT91C_CKGR_PLLR ((AT91_REG *) 	0xFFFFFC2C) // （CKGR）PLL寄存器
#define AT91C_CKGR_MCFR ((AT91_REG *) 	0xFFFFFC24) // （CKGR）主时钟频率寄存器
// ===========PMC外围设备的寄存器定义==========
#define AT91C_PMC_IDR   ((AT91_REG *) 	0xFFFFFC64) // （PMC）中断禁用寄存器
#define AT91C_PMC_MOR   ((AT91_REG *) 	0xFFFFFC20) // （PMC）主振荡器寄存器
#define AT91C_PMC_PLLR  ((AT91_REG *) 	0xFFFFFC2C) // （PMC）PLL寄存器
#define AT91C_PMC_PCER  ((AT91_REG *) 	0xFFFFFC10) // （PMC）外围时钟启用寄存器
#define AT91C_PMC_PCKR  ((AT91_REG *) 	0xFFFFFC40) // （PMC）可编程时钟寄存器
#define AT91C_PMC_MCKR  ((AT91_REG *) 	0xFFFFFC30) // （PMC）主时钟寄存器
#define AT91C_PMC_SCDR  ((AT91_REG *) 	0xFFFFFC04) // （PMC）系统时钟禁用寄存器
#define AT91C_PMC_PCDR  ((AT91_REG *) 	0xFFFFFC14) // （PMC）外围时钟禁用寄存器
#define AT91C_PMC_SCSR  ((AT91_REG *) 	0xFFFFFC08) // （PMC）系统时钟状态寄存器
#define AT91C_PMC_PCSR  ((AT91_REG *) 	0xFFFFFC18) // （PMC）外围时钟状态寄存器
#define AT91C_PMC_MCFR  ((AT91_REG *) 	0xFFFFFC24) // （PMC）主时钟频率寄存器
#define AT91C_PMC_SCER  ((AT91_REG *) 	0xFFFFFC00) // （PMC）系统时钟启用寄存器
#define AT91C_PMC_IMR   ((AT91_REG *) 	0xFFFFFC6C) // （PMC）中断掩码寄存器
#define AT91C_PMC_IER   ((AT91_REG *) 	0xFFFFFC60) // （PMC）中断启用寄存器
#define AT91C_PMC_SR    ((AT91_REG *) 	0xFFFFFC68) // （PMC）状态寄存器
// ============RSTC外围设备的寄存器定义============
#define AT91C_RSTC_RCR  ((AT91_REG *) 	0xFFFFFD00) // （RSTC）复位控制寄存器
#define AT91C_RSTC_RMR  ((AT91_REG *) 	0xFFFFFD08) // （RSTC）复位模式寄存器
#define AT91C_RSTC_RSR  ((AT91_REG *) 	0xFFFFFD04) // （RSTC）重置状态寄存器
// ============RTTC外围设备的寄存器定义============
#define AT91C_RTTC_RTSR ((AT91_REG *) 	0xFFFFFD2C) // （RTTC）实时状态寄存器
#define AT91C_RTTC_RTMR ((AT91_REG *) 	0xFFFFFD20) // （RTTC）实时模式寄存器
#define AT91C_RTTC_RTVR ((AT91_REG *) 	0xFFFFFD28) // （RTTC）实时值寄存器
#define AT91C_RTTC_RTAR ((AT91_REG *) 	0xFFFFFD24) // （RTTC）实时报警寄存器
// ============PITC外围设备的寄存器定义============
#define AT91C_PITC_PIVR ((AT91_REG *) 	0xFFFFFD38) // （PITC）周期间隔值寄存器
#define AT91C_PITC_PISR ((AT91_REG *) 	0xFFFFFD34) // （PITC）周期间隔状态寄存器
#define AT91C_PITC_PIIR ((AT91_REG *) 	0xFFFFFD3C) // （PITC）周期间隔图像寄存器
#define AT91C_PITC_PIMR ((AT91_REG *) 	0xFFFFFD30) // （PITC）周期间隔模式寄存器
// ============WDTC外围设备的寄存器定义============
#define AT91C_WDTC_WDCR ((AT91_REG *) 	0xFFFFFD40) // （WDTC）看门狗控制寄存器
#define AT91C_WDTC_WDSR ((AT91_REG *) 	0xFFFFFD48) // （WDTC）看门狗状态寄存器
#define AT91C_WDTC_WDMR ((AT91_REG *) 	0xFFFFFD44) // （WDTC）看门狗模式寄存器
// ============VREG外围设备的寄存器定义============
#define AT91C_VREG_MR   ((AT91_REG *) 	0xFFFFFD60) // （VREG）电压调节器模式寄存器
// ============MC外围设备的寄存器定义============
#define AT91C_MC_ASR    ((AT91_REG *) 	0xFFFFFF04) // （MC）MC中止状态寄存器
#define AT91C_MC_RCR    ((AT91_REG *) 	0xFFFFFF00) // （MC）MC重映射控制寄存器
#define AT91C_MC_FCR    ((AT91_REG *) 	0xFFFFFF64) // （MC）MC闪存命令寄存器
#define AT91C_MC_AASR   ((AT91_REG *) 	0xFFFFFF08) // （MC）MC中止地址状态寄存器
#define AT91C_MC_FSR    ((AT91_REG *) 	0xFFFFFF68) // （MC）MC闪存状态寄存器
#define AT91C_MC_FMR    ((AT91_REG *) 	0xFFFFFF60) // （MC）MC闪存模式寄存器
// ============PDC_SPI1外围设备的寄存器定义============
#define AT91C_SPI1_PTCR ((AT91_REG *) 	0xFFFE4120) // （PDC_SPI1）PDC传输控制寄存器
#define AT91C_SPI1_RPR  ((AT91_REG *) 	0xFFFE4100) // （PDC_SPI1）接收指针寄存器
#define AT91C_SPI1_TNCR ((AT91_REG *) 	0xFFFE411C) // （PDC_SPI1）发送下一计数器寄存器
#define AT91C_SPI1_TPR  ((AT91_REG *) 	0xFFFE4108) // （PDC_SPI1）发送指针寄存器
#define AT91C_SPI1_TNPR ((AT91_REG *) 	0xFFFE4118) // （PDC_SPI1）发送下一个指针寄存器
#define AT91C_SPI1_TCR  ((AT91_REG *) 	0xFFFE410C) // （PDC_SPI1）发送计数器寄存器
#define AT91C_SPI1_RCR  ((AT91_REG *) 	0xFFFE4104) // （PDC_SPI1）接收计数器寄存器
#define AT91C_SPI1_RNPR ((AT91_REG *) 	0xFFFE4110) // （PDC_SPI1）接收下一个指针寄存器
#define AT91C_SPI1_RNCR ((AT91_REG *) 	0xFFFE4114) // （PDC_SPI1）接收下一个计数器寄存器
#define AT91C_SPI1_PTSR ((AT91_REG *) 	0xFFFE4124) // （PDC_SPI1）PDC传输状态寄存器
// ============SPI1外围设备的寄存器定义============
#define AT91C_SPI1_IMR  ((AT91_REG *) 	0xFFFE401C) // （SPI1）中断掩码寄存器
#define AT91C_SPI1_IER  ((AT91_REG *) 	0xFFFE4014) // （SPI1）中断启用寄存器
#define AT91C_SPI1_MR   ((AT91_REG *) 	0xFFFE4004) // （SPI1）模式寄存器
#define AT91C_SPI1_RDR  ((AT91_REG *) 	0xFFFE4008) // （SPI1）接收数据寄存器
#define AT91C_SPI1_IDR  ((AT91_REG *) 	0xFFFE4018) // （SPI1）中断禁用寄存器
#define AT91C_SPI1_SR   ((AT91_REG *) 	0xFFFE4010) // （SPI1）状态寄存器
#define AT91C_SPI1_TDR  ((AT91_REG *) 	0xFFFE400C) // （SPI1）发送数据寄存器
#define AT91C_SPI1_CR   ((AT91_REG *) 	0xFFFE4000) // （SPI1）控制寄存器
#define AT91C_SPI1_CSR  ((AT91_REG *) 	0xFFFE4030) // （SPI1）芯片选择寄存器
// ============PDC_SPI0外围设备的寄存器定义============
#define AT91C_SPI0_PTCR ((AT91_REG *) 	0xFFFE0120) // （PDC_SPI0）PDC传输控制寄存器
#define AT91C_SPI0_TPR  ((AT91_REG *) 	0xFFFE0108) // （PDC_SPI0）传输指针寄存器
#define AT91C_SPI0_TCR  ((AT91_REG *) 	0xFFFE010C) // （PDC_SPI0）传输计数器寄存器
#define AT91C_SPI0_RCR  ((AT91_REG *) 	0xFFFE0104) // （PDC_SPI0）接收计数器寄存器
#define AT91C_SPI0_PTSR ((AT91_REG *) 	0xFFFE0124) // （PDC_SPI0）PDC传输状态寄存器
#define AT91C_SPI0_RNPR ((AT91_REG *) 	0xFFFE0110) // （PDC_SPI0）接收下一个指针寄存器
#define AT91C_SPI0_RPR  ((AT91_REG *) 	0xFFFE0100) // （PDC_SPI0）接收指针寄存器
#define AT91C_SPI0_TNCR ((AT91_REG *) 	0xFFFE011C) // （PDC_SPI0）发送下一计数器寄存器
#define AT91C_SPI0_RNCR ((AT91_REG *) 	0xFFFE0114) // （PDC_SPI0）接收下一个计数器寄存器
#define AT91C_SPI0_TNPR ((AT91_REG *) 	0xFFFE0118) // （PDC_SPI0）发送下一个指针寄存器
// ============SPI0外围设备的寄存器定义============
#define AT91C_SPI0_IER  ((AT91_REG *) 	0xFFFE0014) // （SPI0）中断启用寄存器
#define AT91C_SPI0_SR   ((AT91_REG *) 	0xFFFE0010) // （SPI0）状态寄存器
#define AT91C_SPI0_IDR  ((AT91_REG *) 	0xFFFE0018) // （SPI0）中断禁用寄存器
#define AT91C_SPI0_CR   ((AT91_REG *) 	0xFFFE0000) // （SPI0）控制寄存器
#define AT91C_SPI0_MR   ((AT91_REG *) 	0xFFFE0004) // （SPI0）模式寄存器
#define AT91C_SPI0_IMR  ((AT91_REG *) 	0xFFFE001C) // （SPI0）中断掩码寄存器
#define AT91C_SPI0_TDR  ((AT91_REG *) 	0xFFFE000C) // （SPI0）传输数据寄存器
#define AT91C_SPI0_RDR  ((AT91_REG *) 	0xFFFE0008) // （SPI0）接收数据寄存器
#define AT91C_SPI0_CSR  ((AT91_REG *) 	0xFFFE0030) // （SPI0）芯片选择寄存器
// ============PDC_US1外围设备的寄存器定义============
#define AT91C_US1_RNCR  ((AT91_REG *) 	0xFFFC4114) // （PDC_US1）接收下一个计数器寄存器
#define AT91C_US1_PTCR  ((AT91_REG *) 	0xFFFC4120) // （PDC_US1）PDC传输控制寄存器
#define AT91C_US1_TCR   ((AT91_REG *) 	0xFFFC410C) // （PDC_US1）发送计数器寄存器
#define AT91C_US1_PTSR  ((AT91_REG *) 	0xFFFC4124) // （PDC_US1）PDC传输状态寄存器
#define AT91C_US1_TNPR  ((AT91_REG *) 	0xFFFC4118) // （PDC_US1）发送下一个指针寄存器
#define AT91C_US1_RCR   ((AT91_REG *) 	0xFFFC4104) // （PDC_US1）接收计数器寄存器
#define AT91C_US1_RNPR  ((AT91_REG *) 	0xFFFC4110) // （PDC_US1）接收下一个指针寄存器
#define AT91C_US1_RPR   ((AT91_REG *) 	0xFFFC4100) // （PDC_US1）接收指针寄存器
#define AT91C_US1_TNCR  ((AT91_REG *) 	0xFFFC411C) // （PDC_US1）发送下一计数器寄存器
#define AT91C_US1_TPR   ((AT91_REG *) 	0xFFFC4108) // （PDC_US1）发送指针寄存器
// ============US1外围设备的寄存器定义============
#define AT91C_US1_IF    ((AT91_REG *) 	0xFFFC404C) // （US1）IRDA_FILTER寄存器
#define AT91C_US1_NER   ((AT91_REG *) 	0xFFFC4044) // （US1）Nb错误寄存器
#define AT91C_US1_RTOR  ((AT91_REG *) 	0xFFFC4024) // （US1）接收机超时寄存器
#define AT91C_US1_CSR   ((AT91_REG *) 	0xFFFC4014) // （US1）信道状态寄存器
#define AT91C_US1_IDR   ((AT91_REG *) 	0xFFFC400C) // （US1）中断禁用寄存器
#define AT91C_US1_IER   ((AT91_REG *) 	0xFFFC4008) // （US1）中断启用寄存器
#define AT91C_US1_THR   ((AT91_REG *) 	0xFFFC401C) // （US1）发射机保持寄存器
#define AT91C_US1_TTGR  ((AT91_REG *) 	0xFFFC4028) // （US1）发射器时间保护寄存器
#define AT91C_US1_RHR   ((AT91_REG *) 	0xFFFC4018) // （US1）接收机保持寄存器
#define AT91C_US1_BRGR  ((AT91_REG *) 	0xFFFC4020) // （US1）波特率发生器寄存器
#define AT91C_US1_IMR   ((AT91_REG *) 	0xFFFC4010) // （US1）中断掩码寄存器
#define AT91C_US1_FIDI  ((AT91_REG *) 	0xFFFC4040) // （US1）FI_DI_Ratio寄存器
#define AT91C_US1_CR    ((AT91_REG *) 	0xFFFC4000) // （US1）控制寄存器
#define AT91C_US1_MR    ((AT91_REG *) 	0xFFFC4004) // （US1）模式寄存器
// ============PDC_US0外围设备的寄存器定义============
#define AT91C_US0_TNPR  ((AT91_REG *) 	0xFFFC0118) // （PDC_US0）发送下一个指针寄存器
#define AT91C_US0_RNPR  ((AT91_REG *) 	0xFFFC0110) // （PDC_US0）接收下一个指针寄存器
#define AT91C_US0_TCR   ((AT91_REG *) 	0xFFFC010C) // （PDC_US0）发送计数器寄存器
#define AT91C_US0_PTCR  ((AT91_REG *) 	0xFFFC0120) // （PDC_US0）PDC传输控制寄存器
#define AT91C_US0_PTSR  ((AT91_REG *) 	0xFFFC0124) // （PDC_US0）PDC传输状态寄存器
#define AT91C_US0_TNCR  ((AT91_REG *) 	0xFFFC011C) // （PDC_US0）发送下一计数器寄存器
#define AT91C_US0_TPR   ((AT91_REG *) 	0xFFFC0108) // （PDC_US0）发送指针寄存器
#define AT91C_US0_RCR   ((AT91_REG *) 	0xFFFC0104) // （PDC_US0）接收计数器寄存器
#define AT91C_US0_RPR   ((AT91_REG *) 	0xFFFC0100) // （PDC_US0）接收指针寄存器
#define AT91C_US0_RNCR  ((AT91_REG *) 	0xFFFC0114) // （PDC_US0）接收下一个计数器寄存器
// ============US0外围设备的寄存器定义============
#define AT91C_US0_BRGR  ((AT91_REG *) 	0xFFFC0020) // （US0）波特率发生器寄存器
#define AT91C_US0_NER   ((AT91_REG *) 	0xFFFC0044) // （US0）Nb错误寄存器
#define AT91C_US0_CR    ((AT91_REG *) 	0xFFFC0000) // （US0）控制寄存器
#define AT91C_US0_IMR   ((AT91_REG *) 	0xFFFC0010) // （US0）中断掩码寄存器
#define AT91C_US0_FIDI  ((AT91_REG *) 	0xFFFC0040) // （US0）FI_DI_Ratio寄存器
#define AT91C_US0_TTGR  ((AT91_REG *) 	0xFFFC0028) // （US0）发射器时间保护寄存器
#define AT91C_US0_MR    ((AT91_REG *) 	0xFFFC0004) // （US0）模式寄存器
#define AT91C_US0_RTOR  ((AT91_REG *) 	0xFFFC0024) // （US0）接收机超时寄存器
#define AT91C_US0_CSR   ((AT91_REG *) 	0xFFFC0014) // （US0）信道状态寄存器
#define AT91C_US0_RHR   ((AT91_REG *) 	0xFFFC0018) // （US0）接收机保持寄存器
#define AT91C_US0_IDR   ((AT91_REG *) 	0xFFFC000C) // （US0）中断禁用寄存器
#define AT91C_US0_THR   ((AT91_REG *) 	0xFFFC001C) // （US0）发射机保持寄存器
#define AT91C_US0_IF    ((AT91_REG *) 	0xFFFC004C) // （US0）IRDA_FILTER寄存器
#define AT91C_US0_IER   ((AT91_REG *) 	0xFFFC0008) // （US0）中断启用寄存器
// ============PDC_SSC外围设备的寄存器定义============
#define AT91C_SSC_TNCR  ((AT91_REG *) 	0xFFFD411C) // （PDC_SSC）发送下一计数器寄存器
#define AT91C_SSC_RPR   ((AT91_REG *) 	0xFFFD4100) // （PDC_SSC）接收指针寄存器
#define AT91C_SSC_RNCR  ((AT91_REG *) 	0xFFFD4114) // （PDC_SSC）接收下一计数器寄存器
#define AT91C_SSC_TPR   ((AT91_REG *) 	0xFFFD4108) // （PDC_SSC）发送指针寄存器
#define AT91C_SSC_PTCR  ((AT91_REG *) 	0xFFFD4120) // （PDC_SSC）PDC传输控制寄存器
#define AT91C_SSC_TCR   ((AT91_REG *) 	0xFFFD410C) // （PDC_SSC）发送计数器寄存器
#define AT91C_SSC_RCR   ((AT91_REG *) 	0xFFFD4104) // （PDC_SSC）接收计数器寄存器
#define AT91C_SSC_RNPR  ((AT91_REG *) 	0xFFFD4110) // （PDC_SSC）接收下一个指针寄存器
#define AT91C_SSC_TNPR  ((AT91_REG *) 	0xFFFD4118) // （PDC_SSC）发送下一个指针寄存器
#define AT91C_SSC_PTSR  ((AT91_REG *) 	0xFFFD4124) // （PDC_SSC）PDC传输状态寄存器
// ============SSC外围设备的寄存器定义============
#define AT91C_SSC_RHR   ((AT91_REG *) 	0xFFFD4020) // （SSC）接收保持寄存器
#define AT91C_SSC_RSHR  ((AT91_REG *) 	0xFFFD4030) // （SSC）接收同步保持寄存器
#define AT91C_SSC_TFMR  ((AT91_REG *) 	0xFFFD401C) // （SSC）发送帧模式寄存器
#define AT91C_SSC_IDR   ((AT91_REG *) 	0xFFFD4048) // （SSC）中断禁用寄存器
#define AT91C_SSC_THR   ((AT91_REG *) 	0xFFFD4024) // （SSC）发送保持寄存器
#define AT91C_SSC_RCMR  ((AT91_REG *) 	0xFFFD4010) // （SSC）接收时钟模式寄存器
#define AT91C_SSC_IER   ((AT91_REG *) 	0xFFFD4044) // （SSC）中断启用寄存器
#define AT91C_SSC_TSHR  ((AT91_REG *) 	0xFFFD4034) // （SSC）传输同步保持寄存器
#define AT91C_SSC_SR    ((AT91_REG *) 	0xFFFD4040) // （SSC）状态寄存器
#define AT91C_SSC_CMR   ((AT91_REG *) 	0xFFFD4004) // （SSC）时钟模式寄存器
#define AT91C_SSC_TCMR  ((AT91_REG *) 	0xFFFD4018) // （SSC）发送时钟模式寄存器
#define AT91C_SSC_CR    ((AT91_REG *) 	0xFFFD4000) // （SSC）控制寄存器
#define AT91C_SSC_IMR   ((AT91_REG *) 	0xFFFD404C) // （SSC）中断掩码寄存器
#define AT91C_SSC_RFMR  ((AT91_REG *) 	0xFFFD4014) // （SSC）接收帧模式寄存器
// ============TWI外围设备的寄存器定义============
#define AT91C_TWI_IER   ((AT91_REG *) 	0xFFFB8024) // （TWI）中断启用寄存器
#define AT91C_TWI_CR    ((AT91_REG *) 	0xFFFB8000) // （TWI）控制寄存器
#define AT91C_TWI_SR    ((AT91_REG *) 	0xFFFB8020) // （TWI）状态寄存器
#define AT91C_TWI_IMR   ((AT91_REG *) 	0xFFFB802C) // （TWI）中断掩码寄存器
#define AT91C_TWI_THR   ((AT91_REG *) 	0xFFFB8034) // （TWI）发送保持寄存器
#define AT91C_TWI_IDR   ((AT91_REG *) 	0xFFFB8028) // （TWI）中断禁用寄存器
#define AT91C_TWI_IADR  ((AT91_REG *) 	0xFFFB800C) // （TWI）内部地址寄存器
#define AT91C_TWI_MMR   ((AT91_REG *) 	0xFFFB8004) // （TWI）主模式寄存器
#define AT91C_TWI_CWGR  ((AT91_REG *) 	0xFFFB8010) // （TWI）时钟波形发生器寄存器
#define AT91C_TWI_RHR   ((AT91_REG *) 	0xFFFB8030) // （TWI）接收保持寄存器
// ============PWMC_CH3外围设备的寄存器定义============
#define AT91C_PWMC_CH3_CUPDR ((AT91_REG *) 	0xFFFCC270) // （PWMC_CH3）信道更新寄存器
#define AT91C_PWMC_CH3_Reserved ((AT91_REG *) 	0xFFFCC274) // （PWMC_CH3）保留
#define AT91C_PWMC_CH3_CPRDR ((AT91_REG *) 	0xFFFCC268) // （PWMC_CH3）信道周期寄存器
#define AT91C_PWMC_CH3_CDTYR ((AT91_REG *) 	0xFFFCC264) // （PWMC_CH3）信道占空比寄存器
#define AT91C_PWMC_CH3_CCNTR ((AT91_REG *) 	0xFFFCC26C) // （PWMC_CH3）信道计数器寄存器
#define AT91C_PWMC_CH3_CMR ((AT91_REG *) 	0xFFFCC260) // （PWMC_CH3）信道模式寄存器
// ============PWMC_CH2外围设备的寄存器定义============
#define AT91C_PWMC_CH2_Reserved ((AT91_REG *) 	0xFFFCC254) // （PWMC_CH2）保留
#define AT91C_PWMC_CH2_CMR ((AT91_REG *) 	0xFFFCC240) // （PWMC_CH2）信道模式寄存器
#define AT91C_PWMC_CH2_CCNTR ((AT91_REG *) 	0xFFFCC24C) // （PWMC_CH2）信道计数器寄存器
#define AT91C_PWMC_CH2_CPRDR ((AT91_REG *) 	0xFFFCC248) // （PWMC_CH2）信道周期寄存器
#define AT91C_PWMC_CH2_CUPDR ((AT91_REG *) 	0xFFFCC250) // （PWMC_CH2）信道更新寄存器
#define AT91C_PWMC_CH2_CDTYR ((AT91_REG *) 	0xFFFCC244) // （PWMC_CH2）通道占空比寄存器
// ============PWMC_CH1外围设备的寄存器定义============
#define AT91C_PWMC_CH1_Reserved ((AT91_REG *) 	0xFFFCC234) // （PWMC_CH1）保留
#define AT91C_PWMC_CH1_CUPDR ((AT91_REG *) 	0xFFFCC230) // （PWMC_CH1）信道更新寄存器
#define AT91C_PWMC_CH1_CPRDR ((AT91_REG *) 	0xFFFCC228) // （PWMC_CH1）信道周期寄存器
#define AT91C_PWMC_CH1_CCNTR ((AT91_REG *) 	0xFFFCC22C) // （PWMC_CH1）信道计数器寄存器
#define AT91C_PWMC_CH1_CDTYR ((AT91_REG *) 	0xFFFCC224) // （PWMC_CH1）通道占空比寄存器
#define AT91C_PWMC_CH1_CMR ((AT91_REG *) 	0xFFFCC220) // （PWMC_CH1）信道模式寄存器
// ============PWMC_CH0外围设备的寄存器定义============
#define AT91C_PWMC_CH0_Reserved ((AT91_REG *) 	0xFFFCC214) // （PWMC_CH0）保留
#define AT91C_PWMC_CH0_CPRDR ((AT91_REG *) 	0xFFFCC208) // （PWMC_CH0）信道周期寄存器
#define AT91C_PWMC_CH0_CDTYR ((AT91_REG *) 	0xFFFCC204) // （PWMC_CH0）通道占空比寄存器
#define AT91C_PWMC_CH0_CMR ((AT91_REG *) 	0xFFFCC200) // （PWMC_CH0）信道模式寄存器
#define AT91C_PWMC_CH0_CUPDR ((AT91_REG *) 	0xFFFCC210) // （PWMC_CH0）信道更新寄存器
#define AT91C_PWMC_CH0_CCNTR ((AT91_REG *) 	0xFFFCC20C) // （PWMC_CH0）信道计数器寄存器
// ============PWMC外围设备的寄存器定义============
#define AT91C_PWMC_IDR  ((AT91_REG *) 	0xFFFCC014) // （PWMC）PWMC中断禁用寄存器
#define AT91C_PWMC_DIS  ((AT91_REG *) 	0xFFFCC008) // （PWMC）PWMC禁用寄存器
#define AT91C_PWMC_IER  ((AT91_REG *) 	0xFFFCC010) // （PWMC）PWMC中断启用寄存器
#define AT91C_PWMC_VR   ((AT91_REG *) 	0xFFFCC0FC) // （PWMC）PWMC版本寄存器
#define AT91C_PWMC_ISR  ((AT91_REG *) 	0xFFFCC01C) // （PWMC）PWMC中断状态寄存器
#define AT91C_PWMC_SR   ((AT91_REG *) 	0xFFFCC00C) // （PWMC）PWMC状态寄存器
#define AT91C_PWMC_IMR  ((AT91_REG *) 	0xFFFCC018) // （PWMC）PWMC中断掩码寄存器
#define AT91C_PWMC_MR   ((AT91_REG *) 	0xFFFCC000) // （PWMC）PWMC模式寄存器
#define AT91C_PWMC_ENA  ((AT91_REG *) 	0xFFFCC004) // （PWMC）PWMC启用寄存器
// ============UDP外围设备的寄存器定义============
#define AT91C_UDP_IMR   ((AT91_REG *) 	0xFFFB0018) // （UDP）中断掩码寄存器
#define AT91C_UDP_FADDR ((AT91_REG *) 	0xFFFB0008) // （UDP）功能地址寄存器
#define AT91C_UDP_NUM   ((AT91_REG *) 	0xFFFB0000) // （UDP）帧号寄存器
#define AT91C_UDP_FDR   ((AT91_REG *) 	0xFFFB0050) // （UDP）端点FIFO数据寄存器
#define AT91C_UDP_ISR   ((AT91_REG *) 	0xFFFB001C) // （UDP）中断状态寄存器
#define AT91C_UDP_CSR   ((AT91_REG *) 	0xFFFB0030) // （UDP）端点控制和状态寄存器
#define AT91C_UDP_IDR   ((AT91_REG *) 	0xFFFB0014) // （UDP）中断禁用寄存器
#define AT91C_UDP_ICR   ((AT91_REG *) 	0xFFFB0020) // （UDP）中断清除寄存器
#define AT91C_UDP_RSTEP ((AT91_REG *) 	0xFFFB0028) // （UDP）重置终结点寄存器
#define AT91C_UDP_TXVC  ((AT91_REG *) 	0xFFFB0074) // （UDP）收发器控制寄存器
#define AT91C_UDP_GLBSTATE ((AT91_REG *) 	0xFFFB0004) // （UDP）全局状态寄存器
#define AT91C_UDP_IER   ((AT91_REG *) 	0xFFFB0010) // （UDP）中断启用寄存器
// ============TC0外围设备的寄存器定义============
#define AT91C_TC0_SR    ((AT91_REG *) 	0xFFFA0020) // （TC0）状态寄存器
#define AT91C_TC0_RC    ((AT91_REG *) 	0xFFFA001C) // （TC0）寄存器C
#define AT91C_TC0_RB    ((AT91_REG *) 	0xFFFA0018) // （TC0）寄存器B
#define AT91C_TC0_CCR   ((AT91_REG *) 	0xFFFA0000) // （TC0）信道控制寄存器
#define AT91C_TC0_CMR   ((AT91_REG *) 	0xFFFA0004) // （TC0）信道模式寄存器（捕获模式/波形模式）
#define AT91C_TC0_IER   ((AT91_REG *) 	0xFFFA0024) // （TC0）中断启用寄存器
#define AT91C_TC0_RA    ((AT91_REG *) 	0xFFFA0014) // （TC0）寄存器A
#define AT91C_TC0_IDR   ((AT91_REG *) 	0xFFFA0028) // （TC0）中断禁用寄存器
#define AT91C_TC0_CV    ((AT91_REG *) 	0xFFFA0010) // （TC0）计数器值
#define AT91C_TC0_IMR   ((AT91_REG *) 	0xFFFA002C) // （TC0）中断掩码寄存器
// ==========TC1外围设备的寄存器定义==========
#define AT91C_TC1_RB    ((AT91_REG *) 	0xFFFA0058) // （TC1）寄存器B
#define AT91C_TC1_CCR   ((AT91_REG *) 	0xFFFA0040) // （TC1）信道控制寄存器
#define AT91C_TC1_IER   ((AT91_REG *) 	0xFFFA0064) // （TC1）中断启用寄存器
#define AT91C_TC1_IDR   ((AT91_REG *) 	0xFFFA0068) // （TC1）中断禁用寄存器
#define AT91C_TC1_SR    ((AT91_REG *) 	0xFFFA0060) // （TC1）状态寄存器
#define AT91C_TC1_CMR   ((AT91_REG *) 	0xFFFA0044) // （TC1）信道模式寄存器（捕获模式/波形模式）
#define AT91C_TC1_RA    ((AT91_REG *) 	0xFFFA0054) // （TC1）寄存器A
#define AT91C_TC1_RC    ((AT91_REG *) 	0xFFFA005C) // （TC1）寄存器C
#define AT91C_TC1_IMR   ((AT91_REG *) 	0xFFFA006C) // （TC1）中断掩码寄存器
#define AT91C_TC1_CV    ((AT91_REG *) 	0xFFFA0050) // （TC1）计数器值
// ============TC2外围设备的寄存器定义============
#define AT91C_TC2_CMR   ((AT91_REG *) 	0xFFFA0084) // （TC2）信道模式寄存器（捕获模式/波形模式）
#define AT91C_TC2_CCR   ((AT91_REG *) 	0xFFFA0080) // （TC2）信道控制寄存器
#define AT91C_TC2_CV    ((AT91_REG *) 	0xFFFA0090) // （TC2）计数器值
#define AT91C_TC2_RA    ((AT91_REG *) 	0xFFFA0094) // （TC2）寄存器A
#define AT91C_TC2_RB    ((AT91_REG *) 	0xFFFA0098) // （TC2）寄存器B
#define AT91C_TC2_IDR   ((AT91_REG *) 	0xFFFA00A8) // （TC2）中断禁用寄存器
#define AT91C_TC2_IMR   ((AT91_REG *) 	0xFFFA00AC) // （TC2）中断掩码寄存器
#define AT91C_TC2_RC    ((AT91_REG *) 	0xFFFA009C) // （TC2）寄存器C
#define AT91C_TC2_IER   ((AT91_REG *) 	0xFFFA00A4) // （TC2）中断启用寄存器
#define AT91C_TC2_SR    ((AT91_REG *) 	0xFFFA00A0) // （TC2）状态寄存器
// ==========TCB外围设备的寄存器定义==========
#define AT91C_TCB_BMR   ((AT91_REG *) 	0xFFFA00C4) // （TCB）TC块模式寄存器
#define AT91C_TCB_BCR   ((AT91_REG *) 	0xFFFA00C0) // （TCB）TC块控制寄存器
// ============CAN_MB0外围设备的寄存器定义============
#define AT91C_CAN_MB0_MDL ((AT91_REG *) 	0xFFFD0214) // （CAN_MB0）邮箱数据低寄存器
#define AT91C_CAN_MB0_MAM ((AT91_REG *) 	0xFFFD0204) // （CAN_MB0）邮箱接受掩码寄存器
#define AT91C_CAN_MB0_MCR ((AT91_REG *) 	0xFFFD021C) // （CAN_MB0）邮箱控制寄存器
#define AT91C_CAN_MB0_MID ((AT91_REG *) 	0xFFFD0208) // （CAN_MB0）邮箱ID寄存器
#define AT91C_CAN_MB0_MSR ((AT91_REG *) 	0xFFFD0210) // （CAN_MB0）邮箱状态寄存器
#define AT91C_CAN_MB0_MFID ((AT91_REG *) 	0xFFFD020C) // （CAN_MB0）邮箱系列ID寄存器
#define AT91C_CAN_MB0_MDH ((AT91_REG *) 	0xFFFD0218) // （CAN_MB0）邮箱数据高位寄存器
#define AT91C_CAN_MB0_MMR ((AT91_REG *) 	0xFFFD0200) // （CAN_MB0）邮箱模式寄存器
// ============CAN_MB1外围设备的寄存器定义============
#define AT91C_CAN_MB1_MDL ((AT91_REG *) 	0xFFFD0234) // （CAN_MB1）邮箱数据低寄存器
#define AT91C_CAN_MB1_MID ((AT91_REG *) 	0xFFFD0228) // （CAN_MB1）邮箱ID寄存器
#define AT91C_CAN_MB1_MMR ((AT91_REG *) 	0xFFFD0220) // （CAN_MB1）邮箱模式寄存器
#define AT91C_CAN_MB1_MSR ((AT91_REG *) 	0xFFFD0230) // （CAN_MB1）邮箱状态寄存器
#define AT91C_CAN_MB1_MAM ((AT91_REG *) 	0xFFFD0224) // （CAN_MB1）邮箱接受掩码寄存器
#define AT91C_CAN_MB1_MDH ((AT91_REG *) 	0xFFFD0238) // （CAN_MB1）邮箱数据高位寄存器
#define AT91C_CAN_MB1_MCR ((AT91_REG *) 	0xFFFD023C) // （CAN_MB1）邮箱控制寄存器
#define AT91C_CAN_MB1_MFID ((AT91_REG *) 	0xFFFD022C) // （CAN_MB1）邮箱系列ID寄存器
// ============CAN_MB2外围设备的寄存器定义============
#define AT91C_CAN_MB2_MCR ((AT91_REG *) 	0xFFFD025C) // （CAN_MB2）邮箱控制寄存器
#define AT91C_CAN_MB2_MDH ((AT91_REG *) 	0xFFFD0258) // （CAN_MB2）邮箱数据高位寄存器
#define AT91C_CAN_MB2_MID ((AT91_REG *) 	0xFFFD0248) // （CAN_MB2）邮箱ID寄存器
#define AT91C_CAN_MB2_MDL ((AT91_REG *) 	0xFFFD0254) // （CAN_MB2）邮箱数据低寄存器
#define AT91C_CAN_MB2_MMR ((AT91_REG *) 	0xFFFD0240) // （CAN_MB2）邮箱模式寄存器
#define AT91C_CAN_MB2_MAM ((AT91_REG *) 	0xFFFD0244) // （CAN_MB2）邮箱接受掩码寄存器
#define AT91C_CAN_MB2_MFID ((AT91_REG *) 	0xFFFD024C) // （CAN_MB2）邮箱系列ID寄存器
#define AT91C_CAN_MB2_MSR ((AT91_REG *) 	0xFFFD0250) // （CAN_MB2）邮箱状态寄存器
// ============CAN_MB3外围设备的寄存器定义============
#define AT91C_CAN_MB3_MFID ((AT91_REG *) 	0xFFFD026C) // （CAN_MB3）邮箱系列ID寄存器
#define AT91C_CAN_MB3_MAM ((AT91_REG *) 	0xFFFD0264) // （CAN_MB3）邮箱接受掩码寄存器
#define AT91C_CAN_MB3_MID ((AT91_REG *) 	0xFFFD0268) // （CAN_MB3）邮箱ID寄存器
#define AT91C_CAN_MB3_MCR ((AT91_REG *) 	0xFFFD027C) // （CAN_MB3）邮箱控制寄存器
#define AT91C_CAN_MB3_MMR ((AT91_REG *) 	0xFFFD0260) // （CAN_MB3）邮箱模式寄存器
#define AT91C_CAN_MB3_MSR ((AT91_REG *) 	0xFFFD0270) // （CAN_MB3）邮箱状态寄存器
#define AT91C_CAN_MB3_MDL ((AT91_REG *) 	0xFFFD0274) // （CAN_MB3）邮箱数据低寄存器
#define AT91C_CAN_MB3_MDH ((AT91_REG *) 	0xFFFD0278) // （CAN_MB3）邮箱数据高位寄存器
// ============CAN_MB4外围设备的寄存器定义============
#define AT91C_CAN_MB4_MID ((AT91_REG *) 	0xFFFD0288) // （CAN_MB4）邮箱ID寄存器
#define AT91C_CAN_MB4_MMR ((AT91_REG *) 	0xFFFD0280) // （CAN_MB4）邮箱模式寄存器
#define AT91C_CAN_MB4_MDH ((AT91_REG *) 	0xFFFD0298) // （CAN_MB4）邮箱数据高位寄存器
#define AT91C_CAN_MB4_MFID ((AT91_REG *) 	0xFFFD028C) // （CAN_MB4）邮箱系列ID寄存器
#define AT91C_CAN_MB4_MSR ((AT91_REG *) 	0xFFFD0290) // （CAN_MB4）邮箱状态寄存器
#define AT91C_CAN_MB4_MCR ((AT91_REG *) 	0xFFFD029C) // （CAN_MB4）邮箱控制寄存器
#define AT91C_CAN_MB4_MDL ((AT91_REG *) 	0xFFFD0294) // （CAN_MB4）邮箱数据低寄存器
#define AT91C_CAN_MB4_MAM ((AT91_REG *) 	0xFFFD0284) // （CAN_MB4）邮箱接受掩码寄存器
// ============CAN_MB5外围设备的寄存器定义============
#define AT91C_CAN_MB5_MSR ((AT91_REG *) 	0xFFFD02B0) // （CAN_MB5）邮箱状态寄存器
#define AT91C_CAN_MB5_MCR ((AT91_REG *) 	0xFFFD02BC) // （CAN_MB5）邮箱控制寄存器
#define AT91C_CAN_MB5_MFID ((AT91_REG *) 	0xFFFD02AC) // （CAN_MB5）邮箱系列ID寄存器
#define AT91C_CAN_MB5_MDH ((AT91_REG *) 	0xFFFD02B8) // （CAN_MB5）邮箱数据高位寄存器
#define AT91C_CAN_MB5_MID ((AT91_REG *) 	0xFFFD02A8) // （CAN_MB5）邮箱ID寄存器
#define AT91C_CAN_MB5_MMR ((AT91_REG *) 	0xFFFD02A0) // （CAN_MB5）邮箱模式寄存器
#define AT91C_CAN_MB5_MDL ((AT91_REG *) 	0xFFFD02B4) // （CAN_MB5）邮箱数据低寄存器
#define AT91C_CAN_MB5_MAM ((AT91_REG *) 	0xFFFD02A4) // （CAN_MB5）邮箱接受掩码寄存器
// ============CAN_MB6外围设备的寄存器定义============
#define AT91C_CAN_MB6_MFID ((AT91_REG *) 	0xFFFD02CC) // （CAN_MB6）邮箱系列ID寄存器
#define AT91C_CAN_MB6_MID ((AT91_REG *) 	0xFFFD02C8) // （CAN_MB6）邮箱ID寄存器
#define AT91C_CAN_MB6_MAM ((AT91_REG *) 	0xFFFD02C4) // （CAN_MB6）邮箱接受掩码寄存器
#define AT91C_CAN_MB6_MSR ((AT91_REG *) 	0xFFFD02D0) // （CAN_MB6）邮箱状态寄存器
#define AT91C_CAN_MB6_MDL ((AT91_REG *) 	0xFFFD02D4) // （CAN_MB6）邮箱数据低寄存器
#define AT91C_CAN_MB6_MCR ((AT91_REG *) 	0xFFFD02DC) // （CAN_MB6）邮箱控制寄存器
#define AT91C_CAN_MB6_MDH ((AT91_REG *) 	0xFFFD02D8) // （CAN_MB6）邮箱数据高位寄存器
#define AT91C_CAN_MB6_MMR ((AT91_REG *) 	0xFFFD02C0) // （CAN_MB6）邮箱模式寄存器
// ============CAN_MB7外围设备的寄存器定义============
#define AT91C_CAN_MB7_MCR ((AT91_REG *) 	0xFFFD02FC) // （CAN_MB7）邮箱控制寄存器
#define AT91C_CAN_MB7_MDH ((AT91_REG *) 	0xFFFD02F8) // （CAN_MB7）邮箱数据高位寄存器
#define AT91C_CAN_MB7_MFID ((AT91_REG *) 	0xFFFD02EC) // （CAN_MB7）邮箱系列ID寄存器
#define AT91C_CAN_MB7_MDL ((AT91_REG *) 	0xFFFD02F4) // （CAN_MB7）邮箱数据低寄存器
#define AT91C_CAN_MB7_MID ((AT91_REG *) 	0xFFFD02E8) // （CAN_MB7）邮箱ID寄存器
#define AT91C_CAN_MB7_MMR ((AT91_REG *) 	0xFFFD02E0) // （CAN_MB7）邮箱模式寄存器
#define AT91C_CAN_MB7_MAM ((AT91_REG *) 	0xFFFD02E4) // （CAN_MB7）邮箱接受掩码寄存器
#define AT91C_CAN_MB7_MSR ((AT91_REG *) 	0xFFFD02F0) // （CAN_MB7）邮箱状态寄存器
// ============CAN外围设备的寄存器定义============
#define AT91C_CAN_TCR   ((AT91_REG *) 	0xFFFD0024) // （CAN）传输命令寄存器
#define AT91C_CAN_IMR   ((AT91_REG *) 	0xFFFD000C) // （CAN）中断掩码寄存器
#define AT91C_CAN_IER   ((AT91_REG *) 	0xFFFD0004) // （CAN）中断启用寄存器
#define AT91C_CAN_ECR   ((AT91_REG *) 	0xFFFD0020) // （CAN）错误计数器寄存器
#define AT91C_CAN_TIMESTP ((AT91_REG *) 	0xFFFD001C) // （CAN）时间戳寄存器
#define AT91C_CAN_MR    ((AT91_REG *) 	0xFFFD0000) // （CAN）模式寄存器
#define AT91C_CAN_IDR   ((AT91_REG *) 	0xFFFD0008) // （CAN）中断禁用寄存器
#define AT91C_CAN_ACR   ((AT91_REG *) 	0xFFFD0028) // （CAN）中止命令寄存器
#define AT91C_CAN_TIM   ((AT91_REG *) 	0xFFFD0018) // （CAN）计时器寄存器
#define AT91C_CAN_SR    ((AT91_REG *) 	0xFFFD0010) // （CAN）状态寄存器
#define AT91C_CAN_BR    ((AT91_REG *) 	0xFFFD0014) // （CAN）波特率寄存器
#define AT91C_CAN_VR    ((AT91_REG *) 	0xFFFD00FC) // （CAN）版本寄存器
// ============EMAC外围设备的寄存器定义============
#define AT91C_EMAC_ISR  ((AT91_REG *) 	0xFFFDC024) // （EMAC）中断状态寄存器
#define AT91C_EMAC_SA4H ((AT91_REG *) 	0xFFFDC0B4) // （EMAC）特定地址4顶部，最后2个字节
#define AT91C_EMAC_SA1L ((AT91_REG *) 	0xFFFDC098) // （EMAC）特定地址1底部，前4字节
#define AT91C_EMAC_ELE  ((AT91_REG *) 	0xFFFDC078) // （EMAC）过长错误寄存器
#define AT91C_EMAC_LCOL ((AT91_REG *) 	0xFFFDC05C) // （EMAC）延迟碰撞寄存器
#define AT91C_EMAC_RLE  ((AT91_REG *) 	0xFFFDC088) // （EMAC）接收长度字段不匹配寄存器
#define AT91C_EMAC_WOL  ((AT91_REG *) 	0xFFFDC0C4) // （EMAC）LAN唤醒寄存器
#define AT91C_EMAC_DTF  ((AT91_REG *) 	0xFFFDC058) // （EMAC）延迟传输帧寄存器
#define AT91C_EMAC_TUND ((AT91_REG *) 	0xFFFDC064) // （EMAC）传输欠载错误寄存器
#define AT91C_EMAC_NCR  ((AT91_REG *) 	0xFFFDC000) // （EMAC）网络控制寄存器
#define AT91C_EMAC_SA4L ((AT91_REG *) 	0xFFFDC0B0) // （EMAC）特定地址4底部，前4字节
#define AT91C_EMAC_RSR  ((AT91_REG *) 	0xFFFDC020) // （EMAC）接收状态寄存器
#define AT91C_EMAC_SA3L ((AT91_REG *) 	0xFFFDC0A8) // （EMAC）特定地址3底部，前4字节
#define AT91C_EMAC_TSR  ((AT91_REG *) 	0xFFFDC014) // （EMAC）传输状态寄存器
#define AT91C_EMAC_IDR  ((AT91_REG *) 	0xFFFDC02C) // （EMAC）中断禁用寄存器
#define AT91C_EMAC_RSE  ((AT91_REG *) 	0xFFFDC074) // （EMAC）接收符号错误寄存器
#define AT91C_EMAC_ECOL ((AT91_REG *) 	0xFFFDC060) // （EMAC）过度冲突寄存器
#define AT91C_EMAC_TID  ((AT91_REG *) 	0xFFFDC0B8) // （EMAC）类型ID检查寄存器
#define AT91C_EMAC_HRB  ((AT91_REG *) 	0xFFFDC090) // （EMAC）哈希地址底部[31:0]
#define AT91C_EMAC_TBQP ((AT91_REG *) 	0xFFFDC01C) // （EMAC）传输缓冲区队列指针
#define AT91C_EMAC_USRIO ((AT91_REG *) 	0xFFFDC0C0) // （EMAC）用户输入/输出寄存器
#define AT91C_EMAC_PTR  ((AT91_REG *) 	0xFFFDC038) // （EMAC）暂停时间寄存器
#define AT91C_EMAC_SA2H ((AT91_REG *) 	0xFFFDC0A4) // （EMAC）特定地址2顶部，最后2个字节
#define AT91C_EMAC_ROV  ((AT91_REG *) 	0xFFFDC070) // （EMAC）接收溢出错误寄存器
#define AT91C_EMAC_ALE  ((AT91_REG *) 	0xFFFDC054) // （EMAC）对齐错误寄存器
#define AT91C_EMAC_RJA  ((AT91_REG *) 	0xFFFDC07C) // （EMAC）接收Jabbers注册
#define AT91C_EMAC_RBQP ((AT91_REG *) 	0xFFFDC018) // （EMAC）接收缓冲区队列指针
#define AT91C_EMAC_TPF  ((AT91_REG *) 	0xFFFDC08C) // （EMAC）发送暂停帧寄存器
#define AT91C_EMAC_NCFGR ((AT91_REG *) 	0xFFFDC004) // （EMAC）网络配置寄存器
#define AT91C_EMAC_HRT  ((AT91_REG *) 	0xFFFDC094) // （EMAC）哈希地址顶部[63:32]
#define AT91C_EMAC_USF  ((AT91_REG *) 	0xFFFDC080) // （EMAC）缩小帧寄存器
#define AT91C_EMAC_FCSE ((AT91_REG *) 	0xFFFDC050) // （EMAC）帧检查序列错误寄存器
#define AT91C_EMAC_TPQ  ((AT91_REG *) 	0xFFFDC0BC) // （EMAC）传输暂停量子寄存器
#define AT91C_EMAC_MAN  ((AT91_REG *) 	0xFFFDC034) // （EMAC）PHY维护寄存器
#define AT91C_EMAC_FTO  ((AT91_REG *) 	0xFFFDC040) // （EMAC）帧发送OK寄存器
#define AT91C_EMAC_REV  ((AT91_REG *) 	0xFFFDC0FC) // （EMAC）修订登记簿
#define AT91C_EMAC_IMR  ((AT91_REG *) 	0xFFFDC030) // （EMAC）中断掩码寄存器
#define AT91C_EMAC_SCF  ((AT91_REG *) 	0xFFFDC044) // （EMAC）单冲突帧寄存器
#define AT91C_EMAC_PFR  ((AT91_REG *) 	0xFFFDC03C) // （EMAC）暂停帧接收寄存器
#define AT91C_EMAC_MCF  ((AT91_REG *) 	0xFFFDC048) // （EMAC）多冲突帧寄存器
#define AT91C_EMAC_NSR  ((AT91_REG *) 	0xFFFDC008) // （EMAC）网络状态寄存器
#define AT91C_EMAC_SA2L ((AT91_REG *) 	0xFFFDC0A0) // （EMAC）特定地址2底部，前4字节
#define AT91C_EMAC_FRO  ((AT91_REG *) 	0xFFFDC04C) // （EMAC）帧接收OK寄存器
#define AT91C_EMAC_IER  ((AT91_REG *) 	0xFFFDC028) // （EMAC）中断启用寄存器
#define AT91C_EMAC_SA1H ((AT91_REG *) 	0xFFFDC09C) // （EMAC）特定地址1顶部，最后2个字节
#define AT91C_EMAC_CSE  ((AT91_REG *) 	0xFFFDC068) // （EMAC）载波检测错误寄存器
#define AT91C_EMAC_SA3H ((AT91_REG *) 	0xFFFDC0AC) // （EMAC）特定地址3顶部，最后2个字节
#define AT91C_EMAC_RRE  ((AT91_REG *) 	0xFFFDC06C) // （EMAC）接收资源错误寄存器
#define AT91C_EMAC_STE  ((AT91_REG *) 	0xFFFDC084) // （EMAC）SQE测试错误寄存器
// ============PDC_ADC外围设备的寄存器定义============
#define AT91C_ADC_PTSR  ((AT91_REG *) 	0xFFFD8124) // （PDC_ADC）PDC传输状态寄存器
#define AT91C_ADC_PTCR  ((AT91_REG *) 	0xFFFD8120) // （PDC_ADC）PDC传输控制寄存器
#define AT91C_ADC_TNPR  ((AT91_REG *) 	0xFFFD8118) // （PDC_ADC）发送下一个指针寄存器
#define AT91C_ADC_TNCR  ((AT91_REG *) 	0xFFFD811C) // （PDC_ADC）发送下一计数器寄存器
#define AT91C_ADC_RNPR  ((AT91_REG *) 	0xFFFD8110) // （PDC_ADC）接收下一个指针寄存器
#define AT91C_ADC_RNCR  ((AT91_REG *) 	0xFFFD8114) // （PDC_ADC）接收下一计数器寄存器
#define AT91C_ADC_RPR   ((AT91_REG *) 	0xFFFD8100) // （PDC_ADC）接收指针寄存器
#define AT91C_ADC_TCR   ((AT91_REG *) 	0xFFFD810C) // （PDC_ADC）发送计数器寄存器
#define AT91C_ADC_TPR   ((AT91_REG *) 	0xFFFD8108) // （PDC_ADC）传输指针寄存器
#define AT91C_ADC_RCR   ((AT91_REG *) 	0xFFFD8104) // （PDC_ADC）接收计数器寄存器
// ============ADC外围设备的寄存器定义============
#define AT91C_ADC_CDR2  ((AT91_REG *) 	0xFFFD8038) // （ADC）ADC通道数据寄存器2
#define AT91C_ADC_CDR3  ((AT91_REG *) 	0xFFFD803C) // （ADC）ADC通道数据寄存器3
#define AT91C_ADC_CDR0  ((AT91_REG *) 	0xFFFD8030) // （ADC）ADC通道数据寄存器0
#define AT91C_ADC_CDR5  ((AT91_REG *) 	0xFFFD8044) // （ADC）ADC通道数据寄存器5
#define AT91C_ADC_CHDR  ((AT91_REG *) 	0xFFFD8014) // （ADC）ADC通道禁用寄存器
#define AT91C_ADC_SR    ((AT91_REG *) 	0xFFFD801C) // （ADC）ADC状态寄存器
#define AT91C_ADC_CDR4  ((AT91_REG *) 	0xFFFD8040) // （ADC）ADC通道数据寄存器4
#define AT91C_ADC_CDR1  ((AT91_REG *) 	0xFFFD8034) // （ADC）ADC通道数据寄存器1
#define AT91C_ADC_LCDR  ((AT91_REG *) 	0xFFFD8020) // （ADC）ADC上次转换数据寄存器
#define AT91C_ADC_IDR   ((AT91_REG *) 	0xFFFD8028) // （ADC）ADC中断禁用寄存器
#define AT91C_ADC_CR    ((AT91_REG *) 	0xFFFD8000) // （ADC）ADC控制寄存器
#define AT91C_ADC_CDR7  ((AT91_REG *) 	0xFFFD804C) // （ADC）ADC通道数据寄存器7
#define AT91C_ADC_CDR6  ((AT91_REG *) 	0xFFFD8048) // （ADC）ADC通道数据寄存器6
#define AT91C_ADC_IER   ((AT91_REG *) 	0xFFFD8024) // （ADC）ADC中断启用寄存器
#define AT91C_ADC_CHER  ((AT91_REG *) 	0xFFFD8010) // （ADC）ADC通道启用寄存器
#define AT91C_ADC_CHSR  ((AT91_REG *) 	0xFFFD8018) // （ADC）ADC通道状态寄存器
#define AT91C_ADC_MR    ((AT91_REG *) 	0xFFFD8004) // （ADC）ADC模式寄存器
#define AT91C_ADC_IMR   ((AT91_REG *) 	0xFFFD802C) // （ADC）ADC中断掩码寄存器

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_PIO_PA0        ((unsigned int) 1 <<  0) // 引脚由PA0控制
#define AT91C_PA0_RXD0     ((unsigned int) AT91C_PIO_PA0) //  USART 0接收数据
#define AT91C_PIO_PA1        ((unsigned int) 1 <<  1) // 引脚由PA1控制
#define AT91C_PA1_TXD0     ((unsigned int) AT91C_PIO_PA1) //  USART 0传输数据
#define AT91C_PIO_PA10       ((unsigned int) 1 << 10) // 引脚由PA10控制
#define AT91C_PA10_TWD      ((unsigned int) AT91C_PIO_PA10) //  TWI双线串行数据
#define AT91C_PIO_PA11       ((unsigned int) 1 << 11) // 引脚由PA11控制
#define AT91C_PA11_TWCK     ((unsigned int) AT91C_PIO_PA11) //  TWI双线串行时钟
#define AT91C_PIO_PA12       ((unsigned int) 1 << 12) // 引脚由PA12控制
#define AT91C_PA12_SPI0_NPCS0 ((unsigned int) AT91C_PIO_PA12) //  SPI 0外围芯片选择0
#define AT91C_PIO_PA13       ((unsigned int) 1 << 13) // 引脚由PA13控制
#define AT91C_PA13_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA13) //  SPI 0外围芯片选择1
#define AT91C_PA13_PCK1     ((unsigned int) AT91C_PIO_PA13) //  PMC可编程时钟输出1
#define AT91C_PIO_PA14       ((unsigned int) 1 << 14) // 引脚由PA14控制
#define AT91C_PA14_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PA14) //  SPI 0外围芯片选择2
#define AT91C_PA14_IRQ1     ((unsigned int) AT91C_PIO_PA14) //  外部中断1
#define AT91C_PIO_PA15       ((unsigned int) 1 << 15) // 引脚由PA15控制
#define AT91C_PA15_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PA15) //  SPI 0外围芯片选择3
#define AT91C_PA15_TCLK2    ((unsigned int) AT91C_PIO_PA15) //  定时器计数器2外部时钟输入
#define AT91C_PIO_PA16       ((unsigned int) 1 << 16) // 引脚由PA16控制
#define AT91C_PA16_SPI0_MISO ((unsigned int) AT91C_PIO_PA16) //  SPI 0主从
#define AT91C_PIO_PA17       ((unsigned int) 1 << 17) // 引脚由PA17控制
#define AT91C_PA17_SPI0_MOSI ((unsigned int) AT91C_PIO_PA17) //  SPI 0主输出从
#define AT91C_PIO_PA18       ((unsigned int) 1 << 18) // 引脚由PA18控制
#define AT91C_PA18_SPI0_SPCK ((unsigned int) AT91C_PIO_PA18) //  SPI 0串行时钟
#define AT91C_PIO_PA19       ((unsigned int) 1 << 19) // 引脚由PA19控制
#define AT91C_PA19_CANRX    ((unsigned int) AT91C_PIO_PA19) //  CAN接收
#define AT91C_PIO_PA2        ((unsigned int) 1 <<  2) // 引脚由PA2控制
#define AT91C_PA2_SCK0     ((unsigned int) AT91C_PIO_PA2) //  USART 0串行时钟
#define AT91C_PA2_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PA2) //  SPI 1外围芯片选择1
#define AT91C_PIO_PA20       ((unsigned int) 1 << 20) // 引脚由PA20控制
#define AT91C_PA20_CANTX    ((unsigned int) AT91C_PIO_PA20) //  CAN传输
#define AT91C_PIO_PA21       ((unsigned int) 1 << 21) // 引脚由PA21控制
#define AT91C_PA21_TF       ((unsigned int) AT91C_PIO_PA21) //  SSC传输帧同步
#define AT91C_PA21_SPI1_NPCS0 ((unsigned int) AT91C_PIO_PA21) //  SPI 1外围芯片选择0
#define AT91C_PIO_PA22       ((unsigned int) 1 << 22) // 引脚由PA22控制
#define AT91C_PA22_TK       ((unsigned int) AT91C_PIO_PA22) //  SSC发送时钟
#define AT91C_PA22_SPI1_SPCK ((unsigned int) AT91C_PIO_PA22) //  SPI 1串行时钟
#define AT91C_PIO_PA23       ((unsigned int) 1 << 23) // 引脚由PA23控制
#define AT91C_PA23_TD       ((unsigned int) AT91C_PIO_PA23) //  SSC传输数据
#define AT91C_PA23_SPI1_MOSI ((unsigned int) AT91C_PIO_PA23) //  SPI 1主输出从
#define AT91C_PIO_PA24       ((unsigned int) 1 << 24) // 引脚由PA24控制
#define AT91C_PA24_RD       ((unsigned int) AT91C_PIO_PA24) //  SSC接收数据
#define AT91C_PA24_SPI1_MISO ((unsigned int) AT91C_PIO_PA24) //  SPI 1主从
#define AT91C_PIO_PA25       ((unsigned int) 1 << 25) // 引脚由PA25控制
#define AT91C_PA25_RK       ((unsigned int) AT91C_PIO_PA25) //  SSC接收时钟
#define AT91C_PA25_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PA25) //  SPI 1外围芯片选择1
#define AT91C_PIO_PA26       ((unsigned int) 1 << 26) // 引脚由PA26控制
#define AT91C_PA26_RF       ((unsigned int) AT91C_PIO_PA26) //  SSC接收帧同步
#define AT91C_PA26_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PA26) //  SPI 1外围芯片选择2
#define AT91C_PIO_PA27       ((unsigned int) 1 << 27) // 引脚由PA27控制
#define AT91C_PA27_DRXD     ((unsigned int) AT91C_PIO_PA27) //  DBGU调试接收数据
#define AT91C_PA27_PCK3     ((unsigned int) AT91C_PIO_PA27) //  PMC可编程时钟输出3
#define AT91C_PIO_PA28       ((unsigned int) 1 << 28) // 引脚由PA28控制
#define AT91C_PA28_DTXD     ((unsigned int) AT91C_PIO_PA28) //  DBGU调试传输数据
#define AT91C_PIO_PA29       ((unsigned int) 1 << 29) // 引脚由PA29控制
#define AT91C_PA29_FIQ      ((unsigned int) AT91C_PIO_PA29) //  AIC快速中断输入
#define AT91C_PA29_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PA29) //  SPI 1外围芯片选择3
#define AT91C_PIO_PA3        ((unsigned int) 1 <<  3) // 引脚由PA3控制
#define AT91C_PA3_RTS0     ((unsigned int) AT91C_PIO_PA3) //  USART 0准备发送
#define AT91C_PA3_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PA3) //  SPI 1外围芯片选择2
#define AT91C_PIO_PA30       ((unsigned int) 1 << 30) // 引脚由PA30控制
#define AT91C_PA30_IRQ0     ((unsigned int) AT91C_PIO_PA30) //  外部中断0
#define AT91C_PA30_PCK2     ((unsigned int) AT91C_PIO_PA30) //  PMC可编程时钟输出2
#define AT91C_PIO_PA4        ((unsigned int) 1 <<  4) // 引脚由PA4控制
#define AT91C_PA4_CTS0     ((unsigned int) AT91C_PIO_PA4) //  USART 0清除发送
#define AT91C_PA4_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PA4) //  SPI 1外围芯片选择3
#define AT91C_PIO_PA5        ((unsigned int) 1 <<  5) // 引脚由PA5控制
#define AT91C_PA5_RXD1     ((unsigned int) AT91C_PIO_PA5) //  USART 1接收数据
#define AT91C_PIO_PA6        ((unsigned int) 1 <<  6) // 引脚由PA6控制
#define AT91C_PA6_TXD1     ((unsigned int) AT91C_PIO_PA6) //  USART 1传输数据
#define AT91C_PIO_PA7        ((unsigned int) 1 <<  7) // 引脚由PA7控制
#define AT91C_PA7_SCK1     ((unsigned int) AT91C_PIO_PA7) //  USART 1串行时钟
#define AT91C_PA7_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA7) //  SPI 0外围芯片选择1
#define AT91C_PIO_PA8        ((unsigned int) 1 <<  8) // 引脚由PA8控制
#define AT91C_PA8_RTS1     ((unsigned int) AT91C_PIO_PA8) //  USART 1准备发送
#define AT91C_PA8_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PA8) //  SPI 0外围芯片选择2
#define AT91C_PIO_PA9        ((unsigned int) 1 <<  9) // 引脚由PA9控制
#define AT91C_PA9_CTS1     ((unsigned int) AT91C_PIO_PA9) //  USART 1清除发送
#define AT91C_PA9_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PA9) //  SPI 0外围芯片选择3
#define AT91C_PIO_PB0        ((unsigned int) 1 <<  0) // 引脚由PB0控制
#define AT91C_PB0_ETXCK_EREFCK ((unsigned int) AT91C_PIO_PB0) //  以太网MAC传输时钟/参考时钟
#define AT91C_PB0_PCK0     ((unsigned int) AT91C_PIO_PB0) //  PMC可编程时钟输出0
#define AT91C_PIO_PB1        ((unsigned int) 1 <<  1) // 引脚由PB1控制
#define AT91C_PB1_ETXEN    ((unsigned int) AT91C_PIO_PB1) //  以太网MAC传输启用
#define AT91C_PIO_PB10       ((unsigned int) 1 << 10) // 由PB10控制的引脚
#define AT91C_PB10_ETX2     ((unsigned int) AT91C_PIO_PB10) //  以太网MAC传输数据2
#define AT91C_PB10_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PB10) //  SPI 1外围芯片选择1
#define AT91C_PIO_PB11       ((unsigned int) 1 << 11) // 引脚由PB11控制
#define AT91C_PB11_ETX3     ((unsigned int) AT91C_PIO_PB11) //  以太网MAC传输数据3
#define AT91C_PB11_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PB11) //  SPI 1外围芯片选择2
#define AT91C_PIO_PB12       ((unsigned int) 1 << 12) // 引脚由PB12控制
#define AT91C_PB12_ETXER    ((unsigned int) AT91C_PIO_PB12) //  以太网MAC传输编码错误
#define AT91C_PB12_TCLK0    ((unsigned int) AT91C_PIO_PB12) //  定时器计数器0外部时钟输入
#define AT91C_PIO_PB13       ((unsigned int) 1 << 13) // 引脚由PB13控制
#define AT91C_PB13_ERX2     ((unsigned int) AT91C_PIO_PB13) //  以太网MAC接收数据2
#define AT91C_PB13_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PB13) //  SPI 0外围芯片选择1
#define AT91C_PIO_PB14       ((unsigned int) 1 << 14) // 引脚由PB14控制
#define AT91C_PB14_ERX3     ((unsigned int) AT91C_PIO_PB14) //  以太网MAC接收数据3
#define AT91C_PB14_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PB14) //  SPI 0外围芯片选择2
#define AT91C_PIO_PB15       ((unsigned int) 1 << 15) // 引脚由PB15控制
#define AT91C_PB15_ERXDV_ECRSDV ((unsigned int) AT91C_PIO_PB15) //  以太网MAC接收数据有效
#define AT91C_PIO_PB16       ((unsigned int) 1 << 16) // 引脚由PB16控制
#define AT91C_PB16_ECOL     ((unsigned int) AT91C_PIO_PB16) //  检测到以太网MAC冲突
#define AT91C_PB16_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PB16) //  SPI 1外围芯片选择3
#define AT91C_PIO_PB17       ((unsigned int) 1 << 17) // 引脚由PB17控制
#define AT91C_PB17_ERXCK    ((unsigned int) AT91C_PIO_PB17) //  以太网MAC接收时钟
#define AT91C_PB17_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PB17) //  SPI 0外围芯片选择3
#define AT91C_PIO_PB18       ((unsigned int) 1 << 18) // 引脚由PB18控制
#define AT91C_PB18_EF100    ((unsigned int) AT91C_PIO_PB18) //  以太网MAC强制100 Mbit/s
#define AT91C_PB18_ADTRG    ((unsigned int) AT91C_PIO_PB18) //  ADC外部触发器
#define AT91C_PIO_PB19       ((unsigned int) 1 << 19) // 引脚由PB19控制
#define AT91C_PB19_PWM0     ((unsigned int) AT91C_PIO_PB19) //  PWM通道0
#define AT91C_PB19_TCLK1    ((unsigned int) AT91C_PIO_PB19) //  定时器计数器1外部时钟输入
#define AT91C_PIO_PB2        ((unsigned int) 1 <<  2) // 引脚由PB2控制
#define AT91C_PB2_ETX0     ((unsigned int) AT91C_PIO_PB2) //  以太网MAC传输数据0
#define AT91C_PIO_PB20       ((unsigned int) 1 << 20) // 由PB20控制的引脚
#define AT91C_PB20_PWM1     ((unsigned int) AT91C_PIO_PB20) //  PWM通道1
#define AT91C_PB20_PCK0     ((unsigned int) AT91C_PIO_PB20) //  PMC可编程时钟输出0
#define AT91C_PIO_PB21       ((unsigned int) 1 << 21) // 引脚由PB21控制
#define AT91C_PB21_PWM2     ((unsigned int) AT91C_PIO_PB21) //  PWM通道2
#define AT91C_PB21_PCK1     ((unsigned int) AT91C_PIO_PB21) //  PMC可编程时钟输出1
#define AT91C_PIO_PB22       ((unsigned int) 1 << 22) // 引脚由PB22控制
#define AT91C_PB22_PWM3     ((unsigned int) AT91C_PIO_PB22) //  PWM通道3
#define AT91C_PB22_PCK2     ((unsigned int) AT91C_PIO_PB22) //  PMC可编程时钟输出2
#define AT91C_PIO_PB23       ((unsigned int) 1 << 23) // 引脚由PB23控制
#define AT91C_PB23_TIOA0    ((unsigned int) AT91C_PIO_PB23) //  定时器计数器0多用途定时器I/O引脚A
#define AT91C_PB23_DCD1     ((unsigned int) AT91C_PIO_PB23) //  USART 1数据载体检测
#define AT91C_PIO_PB24       ((unsigned int) 1 << 24) // 引脚由PB24控制
#define AT91C_PB24_TIOB0    ((unsigned int) AT91C_PIO_PB24) //  定时器计数器0多用途定时器I/O引脚B
#define AT91C_PB24_DSR1     ((unsigned int) AT91C_PIO_PB24) //  USART 1数据集就绪
#define AT91C_PIO_PB25       ((unsigned int) 1 << 25) // 由PB25控制的引脚
#define AT91C_PB25_TIOA1    ((unsigned int) AT91C_PIO_PB25) //  定时器计数器1多用途定时器I/O引脚A
#define AT91C_PB25_DTR1     ((unsigned int) AT91C_PIO_PB25) //  USART 1数据终端准备就绪
#define AT91C_PIO_PB26       ((unsigned int) 1 << 26) // 由PB26控制的引脚
#define AT91C_PB26_TIOB1    ((unsigned int) AT91C_PIO_PB26) //  定时器计数器1多用途定时器I/O引脚B
#define AT91C_PB26_RI1      ((unsigned int) AT91C_PIO_PB26) //  USART 1环指示器
#define AT91C_PIO_PB27       ((unsigned int) 1 << 27) // 引脚由PB27控制
#define AT91C_PB27_TIOA2    ((unsigned int) AT91C_PIO_PB27) //  定时器计数器2多用途定时器I/O引脚A
#define AT91C_PB27_PWM0     ((unsigned int) AT91C_PIO_PB27) //  PWM通道0
#define AT91C_PIO_PB28       ((unsigned int) 1 << 28) // 引脚由PB28控制
#define AT91C_PB28_TIOB2    ((unsigned int) AT91C_PIO_PB28) //  定时器计数器2多用途定时器I/O引脚B
#define AT91C_PB28_PWM1     ((unsigned int) AT91C_PIO_PB28) //  PWM通道1
#define AT91C_PIO_PB29       ((unsigned int) 1 << 29) // 由PB29控制的引脚
#define AT91C_PB29_PCK1     ((unsigned int) AT91C_PIO_PB29) //  PMC可编程时钟输出1
#define AT91C_PB29_PWM2     ((unsigned int) AT91C_PIO_PB29) //  PWM通道2
#define AT91C_PIO_PB3        ((unsigned int) 1 <<  3) // 引脚由PB3控制
#define AT91C_PB3_ETX1     ((unsigned int) AT91C_PIO_PB3) //  以太网MAC传输数据1
#define AT91C_PIO_PB30       ((unsigned int) 1 << 30) // 引脚由PB30控制
#define AT91C_PB30_PCK2     ((unsigned int) AT91C_PIO_PB30) //  PMC可编程时钟输出2
#define AT91C_PB30_PWM3     ((unsigned int) AT91C_PIO_PB30) //  PWM通道3
#define AT91C_PIO_PB4        ((unsigned int) 1 <<  4) // 引脚由PB4控制
#define AT91C_PB4_ECRS     ((unsigned int) AT91C_PIO_PB4) //  以太网MAC载波检测/载波检测和数据有效
#define AT91C_PIO_PB5        ((unsigned int) 1 <<  5) // 引脚由PB5控制
#define AT91C_PB5_ERX0     ((unsigned int) AT91C_PIO_PB5) //  以太网MAC接收数据0
#define AT91C_PIO_PB6        ((unsigned int) 1 <<  6) // 引脚由PB6控制
#define AT91C_PB6_ERX1     ((unsigned int) AT91C_PIO_PB6) //  以太网MAC接收数据1
#define AT91C_PIO_PB7        ((unsigned int) 1 <<  7) // 引脚由PB7控制
#define AT91C_PB7_ERXER    ((unsigned int) AT91C_PIO_PB7) //  以太网MAC接收错误
#define AT91C_PIO_PB8        ((unsigned int) 1 <<  8) // 引脚由PB8控制
#define AT91C_PB8_EMDC     ((unsigned int) AT91C_PIO_PB8) //  以太网MAC管理数据时钟
#define AT91C_PIO_PB9        ((unsigned int) 1 <<  9) // 引脚由PB9控制
#define AT91C_PB9_EMDIO    ((unsigned int) AT91C_PIO_PB9) //  以太网MAC管理数据输入/输出

// *****************************************************************************
//               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_ID_FIQ    ((unsigned int)  0) // 高级中断控制器（FIQ）
#define AT91C_ID_SYS    ((unsigned int)  1) // 系统外围设备
#define AT91C_ID_PIOA   ((unsigned int)  2) // 并行IO控制器A
#define AT91C_ID_PIOB   ((unsigned int)  3) // 并行IO控制器B
#define AT91C_ID_SPI0   ((unsigned int)  4) // 串行外围接口0
#define AT91C_ID_SPI1   ((unsigned int)  5) // 串行外围接口1
#define AT91C_ID_US0    ((unsigned int)  6) // USART 0
#define AT91C_ID_US1    ((unsigned int)  7) // USART 1
#define AT91C_ID_SSC    ((unsigned int)  8) // 串行同步控制器
#define AT91C_ID_TWI    ((unsigned int)  9) // 双线接口
#define AT91C_ID_PWMC   ((unsigned int) 10) // PWM控制器
#define AT91C_ID_UDP    ((unsigned int) 11) // USB设备端口
#define AT91C_ID_TC0    ((unsigned int) 12) // 计时器计数器0
#define AT91C_ID_TC1    ((unsigned int) 13) // 计时器计数器1
#define AT91C_ID_TC2    ((unsigned int) 14) // 计时器计数器2
#define AT91C_ID_CAN    ((unsigned int) 15) // 控制区域网络控制器
#define AT91C_ID_EMAC   ((unsigned int) 16) // 以太网MAC
#define AT91C_ID_ADC    ((unsigned int) 17) // 模数转换器
#define AT91C_ID_18_Reserved ((unsigned int) 18) // 保留
#define AT91C_ID_19_Reserved ((unsigned int) 19) // 保留
#define AT91C_ID_20_Reserved ((unsigned int) 20) // 保留
#define AT91C_ID_21_Reserved ((unsigned int) 21) // 保留
#define AT91C_ID_22_Reserved ((unsigned int) 22) // 保留
#define AT91C_ID_23_Reserved ((unsigned int) 23) // 保留
#define AT91C_ID_24_Reserved ((unsigned int) 24) // 保留
#define AT91C_ID_25_Reserved ((unsigned int) 25) // 保留
#define AT91C_ID_26_Reserved ((unsigned int) 26) // 保留
#define AT91C_ID_27_Reserved ((unsigned int) 27) // 保留
#define AT91C_ID_28_Reserved ((unsigned int) 28) // 保留
#define AT91C_ID_29_Reserved ((unsigned int) 29) // 保留
#define AT91C_ID_IRQ0   ((unsigned int) 30) // 高级中断控制器（IRQ0）
#define AT91C_ID_IRQ1   ((unsigned int) 31) // 高级中断控制器（IRQ1）
#define AT91C_ALL_INT   ((unsigned int) 0xC003FFFF) // ALL VALID INTERRUPTS

// *****************************************************************************
//               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_BASE_SYS       ((AT91PS_SYS) 	0xFFFFF000) // （SYS）基址
#define AT91C_BASE_AIC       ((AT91PS_AIC) 	0xFFFFF000) // （AIC）基本地址
#define AT91C_BASE_PDC_DBGU  ((AT91PS_PDC) 	0xFFFFF300) // （PDC_DBGU）基址
#define AT91C_BASE_DBGU      ((AT91PS_DBGU) 	0xFFFFF200) // （DBGU）基址
#define AT91C_BASE_PIOA      ((AT91PS_PIO) 	0xFFFFF400) // （PIOA）基本地址
#define AT91C_BASE_PIOB      ((AT91PS_PIO) 	0xFFFFF600) // （PIOB）基址
#define AT91C_BASE_CKGR      ((AT91PS_CKGR) 	0xFFFFFC20) // （CKGR）基址
#define AT91C_BASE_PMC       ((AT91PS_PMC) 	0xFFFFFC00) // （PMC）基址
#define AT91C_BASE_RSTC      ((AT91PS_RSTC) 	0xFFFFFD00) // （RSTC）基址
#define AT91C_BASE_RTTC      ((AT91PS_RTTC) 	0xFFFFFD20) // （RTTC）基址
#define AT91C_BASE_PITC      ((AT91PS_PITC) 	0xFFFFFD30) // （PITC）基址
#define AT91C_BASE_WDTC      ((AT91PS_WDTC) 	0xFFFFFD40) // （WDTC）基址
#define AT91C_BASE_VREG      ((AT91PS_VREG) 	0xFFFFFD60) // （VREG）基址
#define AT91C_BASE_MC        ((AT91PS_MC) 	0xFFFFFF00) // （MC）基址
#define AT91C_BASE_PDC_SPI1  ((AT91PS_PDC) 	0xFFFE4100) // （PDC_SPI1）基址
#define AT91C_BASE_SPI1      ((AT91PS_SPI) 	0xFFFE4000) // （SPI1）基址
#define AT91C_BASE_PDC_SPI0  ((AT91PS_PDC) 	0xFFFE0100) // （PDC_SPI0）基址
#define AT91C_BASE_SPI0      ((AT91PS_SPI) 	0xFFFE0000) // （SPI0）基址
#define AT91C_BASE_PDC_US1   ((AT91PS_PDC) 	0xFFFC4100) // （PDC_US1）基址
#define AT91C_BASE_US1       ((AT91PS_USART) 	0xFFFC4000) // （US1）基址
#define AT91C_BASE_PDC_US0   ((AT91PS_PDC) 	0xFFFC0100) // （PDC_US0）基址
#define AT91C_BASE_US0       ((AT91PS_USART) 	0xFFFC0000) // （US0）基址
#define AT91C_BASE_PDC_SSC   ((AT91PS_PDC) 	0xFFFD4100) // （PDC_SSC）基址
#define AT91C_BASE_SSC       ((AT91PS_SSC) 	0xFFFD4000) // （SSC）基址
#define AT91C_BASE_TWI       ((AT91PS_TWI) 	0xFFFB8000) // （TWI）基址
#define AT91C_BASE_PWMC_CH3  ((AT91PS_PWMC_CH) 	0xFFFCC260) // （PWMC_CH3）基址
#define AT91C_BASE_PWMC_CH2  ((AT91PS_PWMC_CH) 	0xFFFCC240) // （PWMC_CH2）基址
#define AT91C_BASE_PWMC_CH1  ((AT91PS_PWMC_CH) 	0xFFFCC220) // （PWMC_CH1）基址
#define AT91C_BASE_PWMC_CH0  ((AT91PS_PWMC_CH) 	0xFFFCC200) // （PWMC_CH0）基址
#define AT91C_BASE_PWMC      ((AT91PS_PWMC) 	0xFFFCC000) // （PWMC）基址
#define AT91C_BASE_UDP       ((AT91PS_UDP) 	0xFFFB0000) // （UDP）基址
#define AT91C_BASE_TC0       ((AT91PS_TC) 	0xFFFA0000) // （TC0）基址
#define AT91C_BASE_TC1       ((AT91PS_TC) 	0xFFFA0040) // （TC1）基址
#define AT91C_BASE_TC2       ((AT91PS_TC) 	0xFFFA0080) // （TC2）基址
#define AT91C_BASE_TCB       ((AT91PS_TCB) 	0xFFFA0000) // （TCB）基址
#define AT91C_BASE_CAN_MB0   ((AT91PS_CAN_MB) 	0xFFFD0200) // （CAN_MB0）基址
#define AT91C_BASE_CAN_MB1   ((AT91PS_CAN_MB) 	0xFFFD0220) // （CAN_MB1）基址
#define AT91C_BASE_CAN_MB2   ((AT91PS_CAN_MB) 	0xFFFD0240) // （CAN_MB2）基址
#define AT91C_BASE_CAN_MB3   ((AT91PS_CAN_MB) 	0xFFFD0260) // （CAN_MB3）基址
#define AT91C_BASE_CAN_MB4   ((AT91PS_CAN_MB) 	0xFFFD0280) // （CAN_MB4）基址
#define AT91C_BASE_CAN_MB5   ((AT91PS_CAN_MB) 	0xFFFD02A0) // （CAN_MB5）基址
#define AT91C_BASE_CAN_MB6   ((AT91PS_CAN_MB) 	0xFFFD02C0) // （CAN_MB6）基址
#define AT91C_BASE_CAN_MB7   ((AT91PS_CAN_MB) 	0xFFFD02E0) // （CAN_MB7）基址
#define AT91C_BASE_CAN       ((AT91PS_CAN) 	0xFFFD0000) // （CAN）基址
#define AT91C_BASE_EMAC      ((AT91PS_EMAC) 	0xFFFDC000) // （EMAC）基本地址
#define AT91C_BASE_PDC_ADC   ((AT91PS_PDC) 	0xFFFD8100) // （PDC_ADC）基址
#define AT91C_BASE_ADC       ((AT91PS_ADC) 	0xFFFD8000) // （ADC）基址

// *****************************************************************************
//               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
// ISRAM
#define AT91C_ISRAM	 ((char *) 	0x00200000) // 内部SRAM基址
#define AT91C_ISRAM_SIZE	 ((unsigned int) 0x00010000) // 内部SRAM大小（字节）（64 KB）
// IFLASH
#define AT91C_IFLASH	 ((char *) 	0x00100000) // 内部FLASH基地址
#define AT91C_IFLASH_SIZE	 ((unsigned int) 0x00040000) // 内部FLASH大小（字节）（256 KB）
#define AT91C_IFLASH_PAGE_SIZE	 ((unsigned int) 256) // 内部FLASH页面大小：256字节
#define AT91C_IFLASH_LOCK_REGION_SIZE	 ((unsigned int) 16384) // 内部FLASH锁定区域大小：16 KB
#define AT91C_IFLASH_NB_OF_PAGES	 ((unsigned int) 1024) // 内部FLASH页数：1024字节
#define AT91C_IFLASH_NB_OF_LOCK_BITS	 ((unsigned int) 16) // 内部FLASH锁定位数：16字节
#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

// -硬件寄存器定义

// - *****************************************************************************
// -系统外围设备的软件API定义
// - *****************************************************************************

// - *****************************************************************************
// -高级中断控制器的软件API定义
// - *****************************************************************************
// ---------AIC_SMR：（AIC偏移：0x0）控制寄存器--------
AT91C_AIC_PRIOR           EQU (0x7 <<  0) ;- (AIC) Priority Level
AT91C_AIC_PRIOR_LOWEST    EQU (0x0) ;- (AIC) Lowest priority level
AT91C_AIC_PRIOR_HIGHEST   EQU (0x7) ;- (AIC) Highest priority level
AT91C_AIC_SRCTYPE         EQU (0x3 <<  5) ;- (AIC) Interrupt Source Type
AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL EQU (0x0 <<  5) ;- (AIC) Internal Sources Code Label High-level Sensitive
AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL EQU (0x0 <<  5) ;- (AIC) External Sources Code Label Low-level Sensitive
AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE EQU (0x1 <<  5) ;- (AIC) Internal Sources Code Label Positive Edge triggered
AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE EQU (0x1 <<  5) ;- (AIC) External Sources Code Label Negative Edge triggered
AT91C_AIC_SRCTYPE_HIGH_LEVEL EQU (0x2 <<  5) ;- (AIC) Internal Or External Sources Code Label High-level Sensitive
AT91C_AIC_SRCTYPE_POSITIVE_EDGE EQU (0x3 <<  5) ;- (AIC) Internal Or External Sources Code Label Positive Edge triggered
// ---------AIC_CISR：（AIC偏移：0x114）AIC核心中断状态寄存器--------
AT91C_AIC_NFIQ            EQU (0x1 <<  0) ;- (AIC) NFIQ Status
AT91C_AIC_NIRQ            EQU (0x1 <<  1) ;- (AIC) NIRQ Status
// ---------AIC_DCR：（AIC偏移：0x138）AIC调试控制寄存器（保护）--------
AT91C_AIC_DCR_PROT        EQU (0x1 <<  0) ;- (AIC) Protection Mode
AT91C_AIC_DCR_GMSK        EQU (0x1 <<  1) ;- (AIC) General Mask

// - *****************************************************************************
// -外设DMA控制器的软件API定义
// - *****************************************************************************
// ---------PDC_PTCR：（PDC偏移：0x20）PDC传输控制寄存器--------
AT91C_PDC_RXTEN           EQU (0x1 <<  0) ;- (PDC) Receiver Transfer Enable
AT91C_PDC_RXTDIS          EQU (0x1 <<  1) ;- (PDC) Receiver Transfer Disable
AT91C_PDC_TXTEN           EQU (0x1 <<  8) ;- (PDC) Transmitter Transfer Enable
AT91C_PDC_TXTDIS          EQU (0x1 <<  9) ;- (PDC) Transmitter Transfer Disable
// ---------PDC_PTSR：（PDC偏移：0x24）PDC传输状态寄存器--------

// - *****************************************************************************
// -调试单元的软件API定义
// - *****************************************************************************
// ---------DBGU_CR：（DBGU偏移量：0x0）调试单元控制寄存器--------
AT91C_US_RSTRX            EQU (0x1 <<  2) ;- (DBGU) Reset Receiver
AT91C_US_RSTTX            EQU (0x1 <<  3) ;- (DBGU) Reset Transmitter
AT91C_US_RXEN             EQU (0x1 <<  4) ;- (DBGU) Receiver Enable
AT91C_US_RXDIS            EQU (0x1 <<  5) ;- (DBGU) Receiver Disable
AT91C_US_TXEN             EQU (0x1 <<  6) ;- (DBGU) Transmitter Enable
AT91C_US_TXDIS            EQU (0x1 <<  7) ;- (DBGU) Transmitter Disable
AT91C_US_RSTSTA           EQU (0x1 <<  8) ;- (DBGU) Reset Status Bits
// ---------DBGU_MR：（DBGU偏移量：0x4）调试单元模式寄存器--------
AT91C_US_PAR              EQU (0x7 <<  9) ;- (DBGU) Parity type
AT91C_US_PAR_EVEN         EQU (0x0 <<  9) ;- (DBGU) Even Parity
AT91C_US_PAR_ODD          EQU (0x1 <<  9) ;- (DBGU) Odd Parity
AT91C_US_PAR_SPACE        EQU (0x2 <<  9) ;- (DBGU) Parity forced to 0 (Space)
AT91C_US_PAR_MARK         EQU (0x3 <<  9) ;- (DBGU) Parity forced to 1 (Mark)
AT91C_US_PAR_NONE         EQU (0x4 <<  9) ;- (DBGU) No Parity
AT91C_US_PAR_MULTI_DROP   EQU (0x6 <<  9) ;- (DBGU) Multi-drop mode
AT91C_US_CHMODE           EQU (0x3 << 14) ;- (DBGU) Channel Mode
AT91C_US_CHMODE_NORMAL    EQU (0x0 << 14) ;- (DBGU) Normal Mode: The USART channel operates as an RX/TX USART.
AT91C_US_CHMODE_AUTO      EQU (0x1 << 14) ;- (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
AT91C_US_CHMODE_LOCAL     EQU (0x2 << 14) ;- (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
AT91C_US_CHMODE_REMOTE    EQU (0x3 << 14) ;- (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// ---------DBGU_IER：（DBGU偏移量：0x8）调试单元中断启用寄存器--------
AT91C_US_RXRDY            EQU (0x1 <<  0) ;- (DBGU) RXRDY Interrupt
AT91C_US_TXRDY            EQU (0x1 <<  1) ;- (DBGU) TXRDY Interrupt
AT91C_US_ENDRX            EQU (0x1 <<  3) ;- (DBGU) End of Receive Transfer Interrupt
AT91C_US_ENDTX            EQU (0x1 <<  4) ;- (DBGU) End of Transmit Interrupt
AT91C_US_OVRE             EQU (0x1 <<  5) ;- (DBGU) Overrun Interrupt
AT91C_US_FRAME            EQU (0x1 <<  6) ;- (DBGU) Framing Error Interrupt
AT91C_US_PARE             EQU (0x1 <<  7) ;- (DBGU) Parity Error Interrupt
AT91C_US_TXEMPTY          EQU (0x1 <<  9) ;- (DBGU) TXEMPTY Interrupt
AT91C_US_TXBUFE           EQU (0x1 << 11) ;- (DBGU) TXBUFE Interrupt
AT91C_US_RXBUFF           EQU (0x1 << 12) ;- (DBGU) RXBUFF Interrupt
AT91C_US_COMM_TX          EQU (0x1 << 30) ;- (DBGU) COMM_TX Interrupt
AT91C_US_COMM_RX          EQU (0x1 << 31) ;- (DBGU) COMM_RX Interrupt
// ---------DBGU_IDR:（DBGU偏移量：0xc）调试单元中断禁用寄存器--------
// ---------DBGU_IMR：（DBGU偏移量：0x10）调试单元中断掩码寄存器--------
// ---------DBGU_CSR:（DBGU偏移量：0x14）调试单元信道状态寄存器--------
// ---------DBGU_FNTR：（DBGU偏移量：0x48）调试单元FORCE_NRST寄存器--------
AT91C_US_FORCE_NTRST      EQU (0x1 <<  0) ;- (DBGU) Force NTRST in JTAG

// - *****************************************************************************
// -并行输入输出控制器的软件API定义
// - *****************************************************************************

// - *****************************************************************************
// -时钟发生器控制器的软件API定义
// - *****************************************************************************
// ---------CKGR_MOR:（CKGR偏移：0x0）主振荡器寄存器--------
AT91C_CKGR_MOSCEN         EQU (0x1 <<  0) ;- (CKGR) Main Oscillator Enable
AT91C_CKGR_OSCBYPASS      EQU (0x1 <<  1) ;- (CKGR) Main Oscillator Bypass
AT91C_CKGR_OSCOUNT        EQU (0xFF <<  8) ;- (CKGR) Main Oscillator Start-up Time
// ---------CKGR_MCFR：（CKGR偏移：0x4）主时钟频率寄存器--------
AT91C_CKGR_MAINF          EQU (0xFFFF <<  0) ;- (CKGR) Main Clock Frequency
AT91C_CKGR_MAINRDY        EQU (0x1 << 16) ;- (CKGR) Main Clock Ready
// ---------CKGR_PLLR：（CKGR偏移：0xc）PLL B寄存器--------
AT91C_CKGR_DIV            EQU (0xFF <<  0) ;- (CKGR) Divider Selected
AT91C_CKGR_DIV_0          EQU (0x0) ;- (CKGR) Divider output is 0
AT91C_CKGR_DIV_BYPASS     EQU (0x1) ;- (CKGR) Divider is bypassed
AT91C_CKGR_PLLCOUNT       EQU (0x3F <<  8) ;- (CKGR) PLL Counter
AT91C_CKGR_OUT            EQU (0x3 << 14) ;- (CKGR) PLL Output Frequency Range
AT91C_CKGR_OUT_0          EQU (0x0 << 14) ;- (CKGR) Please refer to the PLL datasheet
AT91C_CKGR_OUT_1          EQU (0x1 << 14) ;- (CKGR) Please refer to the PLL datasheet
AT91C_CKGR_OUT_2          EQU (0x2 << 14) ;- (CKGR) Please refer to the PLL datasheet
AT91C_CKGR_OUT_3          EQU (0x3 << 14) ;- (CKGR) Please refer to the PLL datasheet
AT91C_CKGR_MUL            EQU (0x7FF << 16) ;- (CKGR) PLL Multiplier
AT91C_CKGR_USBDIV         EQU (0x3 << 28) ;- (CKGR) Divider for USB Clocks
AT91C_CKGR_USBDIV_0       EQU (0x0 << 28) ;- (CKGR) Divider output is PLL clock output
AT91C_CKGR_USBDIV_1       EQU (0x1 << 28) ;- (CKGR) Divider output is PLL clock output divided by 2
AT91C_CKGR_USBDIV_2       EQU (0x2 << 28) ;- (CKGR) Divider output is PLL clock output divided by 4

// - *****************************************************************************
// -电源管理控制器的软件API定义
// - *****************************************************************************
// ---------PMC_SCER：（PMC偏移：0x0）系统时钟启用寄存器--------
AT91C_PMC_PCK             EQU (0x1 <<  0) ;- (PMC) Processor Clock
AT91C_PMC_UDP             EQU (0x1 <<  7) ;- (PMC) USB Device Port Clock
AT91C_PMC_PCK0            EQU (0x1 <<  8) ;- (PMC) Programmable Clock Output
AT91C_PMC_PCK1            EQU (0x1 <<  9) ;- (PMC) Programmable Clock Output
AT91C_PMC_PCK2            EQU (0x1 << 10) ;- (PMC) Programmable Clock Output
AT91C_PMC_PCK3            EQU (0x1 << 11) ;- (PMC) Programmable Clock Output
// ---------PMC_SCDR：（PMC偏移：0x4）系统时钟禁用寄存器--------
// ---------PMC_SCSR：（PMC偏移量：0x8）系统时钟状态寄存器--------
// ---------CKGR_MOR:（PMC偏移：0x20）主振荡器寄存器--------
// ---------CKGR_MCFR：（PMC偏移：0x24）主时钟频率寄存器--------
// ---------CKGR_PLLR：（PMC偏移：0x2c）PLL B寄存器--------
// ---------PMC_MCKR：（PMC偏移：0x30）主时钟寄存器--------
AT91C_PMC_CSS             EQU (0x3 <<  0) ;- (PMC) Programmable Clock Selection
AT91C_PMC_CSS_SLOW_CLK    EQU (0x0) ;- (PMC) Slow Clock is selected
AT91C_PMC_CSS_MAIN_CLK    EQU (0x1) ;- (PMC) Main Clock is selected
AT91C_PMC_CSS_PLL_CLK     EQU (0x3) ;- (PMC) Clock from PLL is selected
AT91C_PMC_PRES            EQU (0x7 <<  2) ;- (PMC) Programmable Clock Prescaler
AT91C_PMC_PRES_CLK        EQU (0x0 <<  2) ;- (PMC) Selected clock
AT91C_PMC_PRES_CLK_2      EQU (0x1 <<  2) ;- (PMC) Selected clock divided by 2
AT91C_PMC_PRES_CLK_4      EQU (0x2 <<  2) ;- (PMC) Selected clock divided by 4
AT91C_PMC_PRES_CLK_8      EQU (0x3 <<  2) ;- (PMC) Selected clock divided by 8
AT91C_PMC_PRES_CLK_16     EQU (0x4 <<  2) ;- (PMC) Selected clock divided by 16
AT91C_PMC_PRES_CLK_32     EQU (0x5 <<  2) ;- (PMC) Selected clock divided by 32
AT91C_PMC_PRES_CLK_64     EQU (0x6 <<  2) ;- (PMC) Selected clock divided by 64
// ---------PMC_PCKR：（PMC偏移：0x40）可编程时钟寄存器--------
// ---------PMC_IER:（PMC偏移：0x60）PMC中断启用寄存器--------
AT91C_PMC_MOSCS           EQU (0x1 <<  0) ;- (PMC) MOSC Status/Enable/Disable/Mask
AT91C_PMC_LOCK            EQU (0x1 <<  2) ;- (PMC) PLL Status/Enable/Disable/Mask
AT91C_PMC_MCKRDY          EQU (0x1 <<  3) ;- (PMC) MCK_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK0RDY         EQU (0x1 <<  8) ;- (PMC) PCK0_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK1RDY         EQU (0x1 <<  9) ;- (PMC) PCK1_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK2RDY         EQU (0x1 << 10) ;- (PMC) PCK2_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK3RDY         EQU (0x1 << 11) ;- (PMC) PCK3_RDY Status/Enable/Disable/Mask
// ---------PMC_IDR：（PMC偏移：0x64）PMC中断禁用寄存器--------
// ---------PMC_SR：（PMC偏移量：0x68）PMC状态寄存器--------
// ---------PMC_IMR：（PMC偏移量：0x6c）PMC中断掩码寄存器--------

// - *****************************************************************************
// -重置控制器接口的软件API定义
// - *****************************************************************************
// ---------RSTC_RCR：（RSTC偏移：0x0）重置控制寄存器--------
AT91C_RSTC_PROCRST        EQU (0x1 <<  0) ;- (RSTC) Processor Reset
AT91C_RSTC_PERRST         EQU (0x1 <<  2) ;- (RSTC) Peripheral Reset
AT91C_RSTC_EXTRST         EQU (0x1 <<  3) ;- (RSTC) External Reset
AT91C_RSTC_KEY            EQU (0xFF << 24) ;- (RSTC) Password
// ---------RSTC_RSR：（RSTC偏移：0x4）重置状态寄存器--------
AT91C_RSTC_URSTS          EQU (0x1 <<  0) ;- (RSTC) User Reset Status
AT91C_RSTC_BODSTS         EQU (0x1 <<  1) ;- (RSTC) Brownout Detection Status
AT91C_RSTC_RSTTYP         EQU (0x7 <<  8) ;- (RSTC) Reset Type
AT91C_RSTC_RSTTYP_POWERUP EQU (0x0 <<  8) ;- (RSTC) Power-up Reset. VDDCORE rising.
AT91C_RSTC_RSTTYP_WAKEUP  EQU (0x1 <<  8) ;- (RSTC) WakeUp Reset. VDDCORE rising.
AT91C_RSTC_RSTTYP_WATCHDOG EQU (0x2 <<  8) ;- (RSTC) Watchdog Reset. Watchdog overflow occured.
AT91C_RSTC_RSTTYP_SOFTWARE EQU (0x3 <<  8) ;- (RSTC) Software Reset. Processor reset required by the software.
AT91C_RSTC_RSTTYP_USER    EQU (0x4 <<  8) ;- (RSTC) User Reset. NRST pin detected low.
AT91C_RSTC_RSTTYP_BROWNOUT EQU (0x5 <<  8) ;- (RSTC) Brownout Reset occured.
AT91C_RSTC_NRSTL          EQU (0x1 << 16) ;- (RSTC) NRST pin level
AT91C_RSTC_SRCMP          EQU (0x1 << 17) ;- (RSTC) Software Reset Command in Progress.
// ---------RSTC_RMR：（RSTC偏移：0x8）重置模式寄存器--------
AT91C_RSTC_URSTEN         EQU (0x1 <<  0) ;- (RSTC) User Reset Enable
AT91C_RSTC_URSTIEN        EQU (0x1 <<  4) ;- (RSTC) User Reset Interrupt Enable
AT91C_RSTC_ERSTL          EQU (0xF <<  8) ;- (RSTC) User Reset Length
AT91C_RSTC_BODIEN         EQU (0x1 << 16) ;- (RSTC) Brownout Detection Interrupt Enable

// - *****************************************************************************
// -实时定时器控制器接口的软件API定义
// - *****************************************************************************
// ---------RTTC_RTMR：（RTTC偏移：0x0）实时模式寄存器--------
AT91C_RTTC_RTPRES         EQU (0xFFFF <<  0) ;- (RTTC) Real-time Timer Prescaler Value
AT91C_RTTC_ALMIEN         EQU (0x1 << 16) ;- (RTTC) Alarm Interrupt Enable
AT91C_RTTC_RTTINCIEN      EQU (0x1 << 17) ;- (RTTC) Real Time Timer Increment Interrupt Enable
AT91C_RTTC_RTTRST         EQU (0x1 << 18) ;- (RTTC) Real Time Timer Restart
// ---------RTTC_RTAR：（RTTC偏移：0x4）实时报警寄存器--------
AT91C_RTTC_ALMV           EQU (0x0 <<  0) ;- (RTTC) Alarm Value
// ---------RTTC_RTVR：（RTTC偏移：0x8）当前实时值寄存器--------
AT91C_RTTC_CRTV           EQU (0x0 <<  0) ;- (RTTC) Current Real-time Value
// ---------RTTC_RTSR：（RTTC偏移量：0xc）实时状态寄存器--------
AT91C_RTTC_ALMS           EQU (0x1 <<  0) ;- (RTTC) Real-time Alarm Status
AT91C_RTTC_RTTINC         EQU (0x1 <<  1) ;- (RTTC) Real-time Timer Increment

// - *****************************************************************************
// -周期间隔定时器控制器接口的软件API定义
// - *****************************************************************************
// ---------PITC_PIR:（PITC偏移：0x0）周期间隔模式寄存器--------
AT91C_PITC_PIV            EQU (0xFFFFF <<  0) ;- (PITC) Periodic Interval Value
AT91C_PITC_PITEN          EQU (0x1 << 24) ;- (PITC) Periodic Interval Timer Enabled
AT91C_PITC_PITIEN         EQU (0x1 << 25) ;- (PITC) Periodic Interval Timer Interrupt Enable
// ---------PITC_PISR：（PITC偏移量：0x4）周期间隔状态寄存器--------
AT91C_PITC_PITS           EQU (0x1 <<  0) ;- (PITC) Periodic Interval Timer Status
// ---------PITC_PIVR：（PITC偏移量：0x8）周期间隔值寄存器--------
AT91C_PITC_CPIV           EQU (0xFFFFF <<  0) ;- (PITC) Current Periodic Interval Value
AT91C_PITC_PICNT          EQU (0xFFF << 20) ;- (PITC) Periodic Interval Counter
// ---------PITC_PIR:（PITC偏移：0xc）周期间隔图像寄存器--------

// - *****************************************************************************
// -看门狗定时器控制器接口的软件API定义
// - *****************************************************************************
// ---------WDTC_WDCR：（WDTC偏移：0x0）周期间隔图像寄存器--------
AT91C_WDTC_WDRSTT         EQU (0x1 <<  0) ;- (WDTC) Watchdog Restart
AT91C_WDTC_KEY            EQU (0xFF << 24) ;- (WDTC) Watchdog KEY Password
// ---------WDTC_WDMR：（WDTC偏移量：0x4）看门狗模式寄存器--------
AT91C_WDTC_WDV            EQU (0xFFF <<  0) ;- (WDTC) Watchdog Timer Restart
AT91C_WDTC_WDFIEN         EQU (0x1 << 12) ;- (WDTC) Watchdog Fault Interrupt Enable
AT91C_WDTC_WDRSTEN        EQU (0x1 << 13) ;- (WDTC) Watchdog Reset Enable
AT91C_WDTC_WDRPROC        EQU (0x1 << 14) ;- (WDTC) Watchdog Timer Restart
AT91C_WDTC_WDDIS          EQU (0x1 << 15) ;- (WDTC) Watchdog Disable
AT91C_WDTC_WDD            EQU (0xFFF << 16) ;- (WDTC) Watchdog Delta Value
AT91C_WDTC_WDDBGHLT       EQU (0x1 << 28) ;- (WDTC) Watchdog Debug Halt
AT91C_WDTC_WDIDLEHLT      EQU (0x1 << 29) ;- (WDTC) Watchdog Idle Halt
// ---------WDTC_WDSR:（WDTC偏移量：0x8）看门狗状态寄存器--------
AT91C_WDTC_WDUNF          EQU (0x1 <<  0) ;- (WDTC) Watchdog Underflow
AT91C_WDTC_WDERR          EQU (0x1 <<  1) ;- (WDTC) Watchdog Error

// - *****************************************************************************
// -稳压器模式控制器接口的软件API定义
// - *****************************************************************************
// ---------VREG_MR：（VREG偏移：0x0）电压调节器模式寄存器--------
AT91C_VREG_PSTDBY         EQU (0x1 <<  0) ;- (VREG) Voltage Regulator Power Standby Mode

// - *****************************************************************************
// -存储器控制器接口的软件API定义
// - *****************************************************************************
// ---------MC_RCR:（MC偏移：0x0）MC重映射控制寄存器--------
AT91C_MC_RCB              EQU (0x1 <<  0) ;- (MC) Remap Command Bit
// ---------MC_ASR:（MC偏移量：0x4）MC中止状态寄存器--------
AT91C_MC_UNDADD           EQU (0x1 <<  0) ;- (MC) Undefined Addess Abort Status
AT91C_MC_MISADD           EQU (0x1 <<  1) ;- (MC) Misaligned Addess Abort Status
AT91C_MC_ABTSZ            EQU (0x3 <<  8) ;- (MC) Abort Size Status
AT91C_MC_ABTSZ_BYTE       EQU (0x0 <<  8) ;- (MC) Byte
AT91C_MC_ABTSZ_HWORD      EQU (0x1 <<  8) ;- (MC) Half-word
AT91C_MC_ABTSZ_WORD       EQU (0x2 <<  8) ;- (MC) Word
AT91C_MC_ABTTYP           EQU (0x3 << 10) ;- (MC) Abort Type Status
AT91C_MC_ABTTYP_DATAR     EQU (0x0 << 10) ;- (MC) Data Read
AT91C_MC_ABTTYP_DATAW     EQU (0x1 << 10) ;- (MC) Data Write
AT91C_MC_ABTTYP_FETCH     EQU (0x2 << 10) ;- (MC) Code Fetch
AT91C_MC_MST0             EQU (0x1 << 16) ;- (MC) Master 0 Abort Source
AT91C_MC_MST1             EQU (0x1 << 17) ;- (MC) Master 1 Abort Source
AT91C_MC_SVMST0           EQU (0x1 << 24) ;- (MC) Saved Master 0 Abort Source
AT91C_MC_SVMST1           EQU (0x1 << 25) ;- (MC) Saved Master 1 Abort Source
// ---------MC_FMR：（MC偏移：0x60）MC闪存模式寄存器--------
AT91C_MC_FRDY             EQU (0x1 <<  0) ;- (MC) Flash Ready
AT91C_MC_LOCKE            EQU (0x1 <<  2) ;- (MC) Lock Error
AT91C_MC_PROGE            EQU (0x1 <<  3) ;- (MC) Programming Error
AT91C_MC_NEBP             EQU (0x1 <<  7) ;- (MC) No Erase Before Programming
AT91C_MC_FWS              EQU (0x3 <<  8) ;- (MC) Flash Wait State
AT91C_MC_FWS_0FWS         EQU (0x0 <<  8) ;- (MC) 1 cycle for Read, 2 for Write operations
AT91C_MC_FWS_1FWS         EQU (0x1 <<  8) ;- (MC) 2 cycles for Read, 3 for Write operations
AT91C_MC_FWS_2FWS         EQU (0x2 <<  8) ;- (MC) 3 cycles for Read, 4 for Write operations
AT91C_MC_FWS_3FWS         EQU (0x3 <<  8) ;- (MC) 4 cycles for Read, 4 for Write operations
AT91C_MC_FMCN             EQU (0xFF << 16) ;- (MC) Flash Microsecond Cycle Number
// ---------MC_FCR：（MC偏移：0x64）MC闪存命令寄存器--------
AT91C_MC_FCMD             EQU (0xF <<  0) ;- (MC) Flash Command
AT91C_MC_FCMD_START_PROG  EQU (0x1) ;- (MC) Starts the programming of th epage specified by PAGEN.
AT91C_MC_FCMD_LOCK        EQU (0x2) ;- (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN.
AT91C_MC_FCMD_PROG_AND_LOCK EQU (0x3) ;- (MC) The lock sequence automatically happens after the programming sequence is completed.
AT91C_MC_FCMD_UNLOCK      EQU (0x4) ;- (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN.
AT91C_MC_FCMD_ERASE_ALL   EQU (0x8) ;- (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled.
AT91C_MC_FCMD_SET_GP_NVM  EQU (0xB) ;- (MC) Set General Purpose NVM bits.
AT91C_MC_FCMD_CLR_GP_NVM  EQU (0xD) ;- (MC) Clear General Purpose NVM bits.
AT91C_MC_FCMD_SET_SECURITY EQU (0xF) ;- (MC) Set Security Bit.
AT91C_MC_PAGEN            EQU (0x3FF <<  8) ;- (MC) Page Number
AT91C_MC_KEY              EQU (0xFF << 24) ;- (MC) Writing Protect Key
// ---------MC_FSR:（MC偏移量：0x68）MC闪存命令寄存器--------
AT91C_MC_SECURITY         EQU (0x1 <<  4) ;- (MC) Security Bit Status
AT91C_MC_GPNVM0           EQU (0x1 <<  8) ;- (MC) Sector 0 Lock Status
AT91C_MC_GPNVM1           EQU (0x1 <<  9) ;- (MC) Sector 1 Lock Status
AT91C_MC_GPNVM2           EQU (0x1 << 10) ;- (MC) Sector 2 Lock Status
AT91C_MC_GPNVM3           EQU (0x1 << 11) ;- (MC) Sector 3 Lock Status
AT91C_MC_GPNVM4           EQU (0x1 << 12) ;- (MC) Sector 4 Lock Status
AT91C_MC_GPNVM5           EQU (0x1 << 13) ;- (MC) Sector 5 Lock Status
AT91C_MC_GPNVM6           EQU (0x1 << 14) ;- (MC) Sector 6 Lock Status
AT91C_MC_GPNVM7           EQU (0x1 << 15) ;- (MC) Sector 7 Lock Status
AT91C_MC_LOCKS0           EQU (0x1 << 16) ;- (MC) Sector 0 Lock Status
AT91C_MC_LOCKS1           EQU (0x1 << 17) ;- (MC) Sector 1 Lock Status
AT91C_MC_LOCKS2           EQU (0x1 << 18) ;- (MC) Sector 2 Lock Status
AT91C_MC_LOCKS3           EQU (0x1 << 19) ;- (MC) Sector 3 Lock Status
AT91C_MC_LOCKS4           EQU (0x1 << 20) ;- (MC) Sector 4 Lock Status
AT91C_MC_LOCKS5           EQU (0x1 << 21) ;- (MC) Sector 5 Lock Status
AT91C_MC_LOCKS6           EQU (0x1 << 22) ;- (MC) Sector 6 Lock Status
AT91C_MC_LOCKS7           EQU (0x1 << 23) ;- (MC) Sector 7 Lock Status
AT91C_MC_LOCKS8           EQU (0x1 << 24) ;- (MC) Sector 8 Lock Status
AT91C_MC_LOCKS9           EQU (0x1 << 25) ;- (MC) Sector 9 Lock Status
AT91C_MC_LOCKS10          EQU (0x1 << 26) ;- (MC) Sector 10 Lock Status
AT91C_MC_LOCKS11          EQU (0x1 << 27) ;- (MC) Sector 11 Lock Status
AT91C_MC_LOCKS12          EQU (0x1 << 28) ;- (MC) Sector 12 Lock Status
AT91C_MC_LOCKS13          EQU (0x1 << 29) ;- (MC) Sector 13 Lock Status
AT91C_MC_LOCKS14          EQU (0x1 << 30) ;- (MC) Sector 14 Lock Status
AT91C_MC_LOCKS15          EQU (0x1 << 31) ;- (MC) Sector 15 Lock Status

// - *****************************************************************************
// -串行并行接口的软件API定义
// - *****************************************************************************
// ---------SPI_CR：（SPI偏移量：0x0）SPI控制寄存器--------
AT91C_SPI_SPIEN           EQU (0x1 <<  0) ;- (SPI) SPI Enable
AT91C_SPI_SPIDIS          EQU (0x1 <<  1) ;- (SPI) SPI Disable
AT91C_SPI_SWRST           EQU (0x1 <<  7) ;- (SPI) SPI Software reset
AT91C_SPI_LASTXFER        EQU (0x1 << 24) ;- (SPI) SPI Last Transfer
// ---------SPI_MR：（SPI偏移量：0x4）SPI模式寄存器--------
AT91C_SPI_MSTR            EQU (0x1 <<  0) ;- (SPI) Master/Slave Mode
AT91C_SPI_PS              EQU (0x1 <<  1) ;- (SPI) Peripheral Select
AT91C_SPI_PS_FIXED        EQU (0x0 <<  1) ;- (SPI) Fixed Peripheral Select
AT91C_SPI_PS_VARIABLE     EQU (0x1 <<  1) ;- (SPI) Variable Peripheral Select
AT91C_SPI_PCSDEC          EQU (0x1 <<  2) ;- (SPI) Chip Select Decode
AT91C_SPI_FDIV            EQU (0x1 <<  3) ;- (SPI) Clock Selection
AT91C_SPI_MODFDIS         EQU (0x1 <<  4) ;- (SPI) Mode Fault Detection
AT91C_SPI_LLB             EQU (0x1 <<  7) ;- (SPI) Clock Selection
AT91C_SPI_PCS             EQU (0xF << 16) ;- (SPI) Peripheral Chip Select
AT91C_SPI_DLYBCS          EQU (0xFF << 24) ;- (SPI) Delay Between Chip Selects
// ---------SPI_RDR:（SPI偏移量：0x8）接收数据寄存器--------
AT91C_SPI_RD              EQU (0xFFFF <<  0) ;- (SPI) Receive Data
AT91C_SPI_RPCS            EQU (0xF << 16) ;- (SPI) Peripheral Chip Select Status
// ---------SPI_TDR：（SPI偏移量：0xc）传输数据寄存器--------
AT91C_SPI_TD              EQU (0xFFFF <<  0) ;- (SPI) Transmit Data
AT91C_SPI_TPCS            EQU (0xF << 16) ;- (SPI) Peripheral Chip Select Status
// ---------SPI_SR：（SPI偏移量：0x10）状态寄存器--------
AT91C_SPI_RDRF            EQU (0x1 <<  0) ;- (SPI) Receive Data Register Full
AT91C_SPI_TDRE            EQU (0x1 <<  1) ;- (SPI) Transmit Data Register Empty
AT91C_SPI_MODF            EQU (0x1 <<  2) ;- (SPI) Mode Fault Error
AT91C_SPI_OVRES           EQU (0x1 <<  3) ;- (SPI) Overrun Error Status
AT91C_SPI_ENDRX           EQU (0x1 <<  4) ;- (SPI) End of Receiver Transfer
AT91C_SPI_ENDTX           EQU (0x1 <<  5) ;- (SPI) End of Receiver Transfer
AT91C_SPI_RXBUFF          EQU (0x1 <<  6) ;- (SPI) RXBUFF Interrupt
AT91C_SPI_TXBUFE          EQU (0x1 <<  7) ;- (SPI) TXBUFE Interrupt
AT91C_SPI_NSSR            EQU (0x1 <<  8) ;- (SPI) NSSR Interrupt
AT91C_SPI_TXEMPTY         EQU (0x1 <<  9) ;- (SPI) TXEMPTY Interrupt
AT91C_SPI_SPIENS          EQU (0x1 << 16) ;- (SPI) Enable Status
// ---------SPI_IER：（SPI偏移量：0x14）中断启用寄存器--------
// ---------SPI_IDR：（SPI偏移量：0x18）中断禁用寄存器--------
// ---------SPI_IMR：（SPI偏移量：0x1c）中断掩码寄存器--------
// ---------SPI_CSR:（SPI偏移量：0x30）芯片选择寄存器--------
AT91C_SPI_CPOL            EQU (0x1 <<  0) ;- (SPI) Clock Polarity
AT91C_SPI_NCPHA           EQU (0x1 <<  1) ;- (SPI) Clock Phase
AT91C_SPI_CSAAT           EQU (0x1 <<  3) ;- (SPI) Chip Select Active After Transfer
AT91C_SPI_BITS            EQU (0xF <<  4) ;- (SPI) Bits Per Transfer
AT91C_SPI_BITS_8          EQU (0x0 <<  4) ;- (SPI) 8 Bits Per transfer
AT91C_SPI_BITS_9          EQU (0x1 <<  4) ;- (SPI) 9 Bits Per transfer
AT91C_SPI_BITS_10         EQU (0x2 <<  4) ;- (SPI) 10 Bits Per transfer
AT91C_SPI_BITS_11         EQU (0x3 <<  4) ;- (SPI) 11 Bits Per transfer
AT91C_SPI_BITS_12         EQU (0x4 <<  4) ;- (SPI) 12 Bits Per transfer
AT91C_SPI_BITS_13         EQU (0x5 <<  4) ;- (SPI) 13 Bits Per transfer
AT91C_SPI_BITS_14         EQU (0x6 <<  4) ;- (SPI) 14 Bits Per transfer
AT91C_SPI_BITS_15         EQU (0x7 <<  4) ;- (SPI) 15 Bits Per transfer
AT91C_SPI_BITS_16         EQU (0x8 <<  4) ;- (SPI) 16 Bits Per transfer
AT91C_SPI_SCBR            EQU (0xFF <<  8) ;- (SPI) Serial Clock Baud Rate
AT91C_SPI_DLYBS           EQU (0xFF << 16) ;- (SPI) Delay Before SPCK
AT91C_SPI_DLYBCT          EQU (0xFF << 24) ;- (SPI) Delay Between Consecutive Transfers

// - *****************************************************************************
// -用于Usart的软件API定义
// - *****************************************************************************
// ---------US_CR：（USART偏移：0x0）调试单元控制寄存器--------
AT91C_US_STTBRK           EQU (0x1 <<  9) ;- (USART) Start Break
AT91C_US_STPBRK           EQU (0x1 << 10) ;- (USART) Stop Break
AT91C_US_STTTO            EQU (0x1 << 11) ;- (USART) Start Time-out
AT91C_US_SENDA            EQU (0x1 << 12) ;- (USART) Send Address
AT91C_US_RSTIT            EQU (0x1 << 13) ;- (USART) Reset Iterations
AT91C_US_RSTNACK          EQU (0x1 << 14) ;- (USART) Reset Non Acknowledge
AT91C_US_RETTO            EQU (0x1 << 15) ;- (USART) Rearm Time-out
AT91C_US_DTREN            EQU (0x1 << 16) ;- (USART) Data Terminal ready Enable
AT91C_US_DTRDIS           EQU (0x1 << 17) ;- (USART) Data Terminal ready Disable
AT91C_US_RTSEN            EQU (0x1 << 18) ;- (USART) Request to Send enable
AT91C_US_RTSDIS           EQU (0x1 << 19) ;- (USART) Request to Send Disable
// ---------US_MR：（USART偏移量：0x4）调试单元模式寄存器--------
AT91C_US_USMODE           EQU (0xF <<  0) ;- (USART) Usart mode
AT91C_US_USMODE_NORMAL    EQU (0x0) ;- (USART) Normal
AT91C_US_USMODE_RS485     EQU (0x1) ;- (USART) RS485
AT91C_US_USMODE_HWHSH     EQU (0x2) ;- (USART) Hardware Handshaking
AT91C_US_USMODE_MODEM     EQU (0x3) ;- (USART) Modem
AT91C_US_USMODE_ISO7816_0 EQU (0x4) ;- (USART) ISO7816 protocol: T = 0
AT91C_US_USMODE_ISO7816_1 EQU (0x6) ;- (USART) ISO7816 protocol: T = 1
AT91C_US_USMODE_IRDA      EQU (0x8) ;- (USART) IrDA
AT91C_US_USMODE_SWHSH     EQU (0xC) ;- (USART) Software Handshaking
AT91C_US_CLKS             EQU (0x3 <<  4) ;- (USART) Clock Selection (Baud Rate generator Input Clock
AT91C_US_CLKS_CLOCK       EQU (0x0 <<  4) ;- (USART) Clock
AT91C_US_CLKS_FDIV1       EQU (0x1 <<  4) ;- (USART) fdiv1
AT91C_US_CLKS_SLOW        EQU (0x2 <<  4) ;- (USART) slow_clock (ARM)
AT91C_US_CLKS_EXT         EQU (0x3 <<  4) ;- (USART) External (SCK)
AT91C_US_CHRL             EQU (0x3 <<  6) ;- (USART) Clock Selection (Baud Rate generator Input Clock
AT91C_US_CHRL_5_BITS      EQU (0x0 <<  6) ;- (USART) Character Length: 5 bits
AT91C_US_CHRL_6_BITS      EQU (0x1 <<  6) ;- (USART) Character Length: 6 bits
AT91C_US_CHRL_7_BITS      EQU (0x2 <<  6) ;- (USART) Character Length: 7 bits
AT91C_US_CHRL_8_BITS      EQU (0x3 <<  6) ;- (USART) Character Length: 8 bits
AT91C_US_SYNC             EQU (0x1 <<  8) ;- (USART) Synchronous Mode Select
AT91C_US_NBSTOP           EQU (0x3 << 12) ;- (USART) Number of Stop bits
AT91C_US_NBSTOP_1_BIT     EQU (0x0 << 12) ;- (USART) 1 stop bit
AT91C_US_NBSTOP_15_BIT    EQU (0x1 << 12) ;- (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
AT91C_US_NBSTOP_2_BIT     EQU (0x2 << 12) ;- (USART) 2 stop bits
AT91C_US_MSBF             EQU (0x1 << 16) ;- (USART) Bit Order
AT91C_US_MODE9            EQU (0x1 << 17) ;- (USART) 9-bit Character length
AT91C_US_CKLO             EQU (0x1 << 18) ;- (USART) Clock Output Select
AT91C_US_OVER             EQU (0x1 << 19) ;- (USART) Over Sampling Mode
AT91C_US_INACK            EQU (0x1 << 20) ;- (USART) Inhibit Non Acknowledge
AT91C_US_DSNACK           EQU (0x1 << 21) ;- (USART) Disable Successive NACK
AT91C_US_MAX_ITER         EQU (0x1 << 24) ;- (USART) Number of Repetitions
AT91C_US_FILTER           EQU (0x1 << 28) ;- (USART) Receive Line Filter
// ---------US_IER：（USART偏移：0x8）调试单元中断启用寄存器--------
AT91C_US_RXBRK            EQU (0x1 <<  2) ;- (USART) Break Received/End of Break
AT91C_US_TIMEOUT          EQU (0x1 <<  8) ;- (USART) Receiver Time-out
AT91C_US_ITERATION        EQU (0x1 << 10) ;- (USART) Max number of Repetitions Reached
AT91C_US_NACK             EQU (0x1 << 13) ;- (USART) Non Acknowledge
AT91C_US_RIIC             EQU (0x1 << 16) ;- (USART) Ring INdicator Input Change Flag
AT91C_US_DSRIC            EQU (0x1 << 17) ;- (USART) Data Set Ready Input Change Flag
AT91C_US_DCDIC            EQU (0x1 << 18) ;- (USART) Data Carrier Flag
AT91C_US_CTSIC            EQU (0x1 << 19) ;- (USART) Clear To Send Input Change Flag
// ---------US_IDR：（USART偏移量：0xc）调试单元中断禁用寄存器--------
// ---------US_IMR：（USART偏移：0x10）调试单元中断掩码寄存器--------
// ---------US_CSR:（USART偏移：0x14）调试单元信道状态寄存器--------
AT91C_US_RI               EQU (0x1 << 20) ;- (USART) Image of RI Input
AT91C_US_DSR              EQU (0x1 << 21) ;- (USART) Image of DSR Input
AT91C_US_DCD              EQU (0x1 << 22) ;- (USART) Image of DCD Input
AT91C_US_CTS              EQU (0x1 << 23) ;- (USART) Image of CTS Input

// - *****************************************************************************
// -同步串行控制器接口的软件API定义
// - *****************************************************************************
// ---------SSC_CR：（SSC偏移量：0x0）SSC控制寄存器--------
AT91C_SSC_RXEN            EQU (0x1 <<  0) ;- (SSC) Receive Enable
AT91C_SSC_RXDIS           EQU (0x1 <<  1) ;- (SSC) Receive Disable
AT91C_SSC_TXEN            EQU (0x1 <<  8) ;- (SSC) Transmit Enable
AT91C_SSC_TXDIS           EQU (0x1 <<  9) ;- (SSC) Transmit Disable
AT91C_SSC_SWRST           EQU (0x1 << 15) ;- (SSC) Software Reset
// ---------SSC_RCMR：（SSC偏移：0x10）SSC接收时钟模式寄存器--------
AT91C_SSC_CKS             EQU (0x3 <<  0) ;- (SSC) Receive/Transmit Clock Selection
AT91C_SSC_CKS_DIV         EQU (0x0) ;- (SSC) Divided Clock
AT91C_SSC_CKS_TK          EQU (0x1) ;- (SSC) TK Clock signal
AT91C_SSC_CKS_RK          EQU (0x2) ;- (SSC) RK pin
AT91C_SSC_CKO             EQU (0x7 <<  2) ;- (SSC) Receive/Transmit Clock Output Mode Selection
AT91C_SSC_CKO_NONE        EQU (0x0 <<  2) ;- (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only
AT91C_SSC_CKO_CONTINOUS   EQU (0x1 <<  2) ;- (SSC) Continuous Receive/Transmit Clock RK pin: Output
AT91C_SSC_CKO_DATA_TX     EQU (0x2 <<  2) ;- (SSC) Receive/Transmit Clock only during data transfers RK pin: Output
AT91C_SSC_CKI             EQU (0x1 <<  5) ;- (SSC) Receive/Transmit Clock Inversion
AT91C_SSC_CKG             EQU (0x3 <<  6) ;- (SSC) Receive/Transmit Clock Gating Selection
AT91C_SSC_CKG_NONE        EQU (0x0 <<  6) ;- (SSC) Receive/Transmit Clock Gating: None, continuous clock
AT91C_SSC_CKG_LOW         EQU (0x1 <<  6) ;- (SSC) Receive/Transmit Clock enabled only if RF Low
AT91C_SSC_CKG_HIGH        EQU (0x2 <<  6) ;- (SSC) Receive/Transmit Clock enabled only if RF High
AT91C_SSC_START           EQU (0xF <<  8) ;- (SSC) Receive/Transmit Start Selection
AT91C_SSC_START_CONTINOUS EQU (0x0 <<  8) ;- (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data.
AT91C_SSC_START_TX        EQU (0x1 <<  8) ;- (SSC) Transmit/Receive start
AT91C_SSC_START_LOW_RF    EQU (0x2 <<  8) ;- (SSC) Detection of a low level on RF input
AT91C_SSC_START_HIGH_RF   EQU (0x3 <<  8) ;- (SSC) Detection of a high level on RF input
AT91C_SSC_START_FALL_RF   EQU (0x4 <<  8) ;- (SSC) Detection of a falling edge on RF input
AT91C_SSC_START_RISE_RF   EQU (0x5 <<  8) ;- (SSC) Detection of a rising edge on RF input
AT91C_SSC_START_LEVEL_RF  EQU (0x6 <<  8) ;- (SSC) Detection of any level change on RF input
AT91C_SSC_START_EDGE_RF   EQU (0x7 <<  8) ;- (SSC) Detection of any edge on RF input
AT91C_SSC_START_0         EQU (0x8 <<  8) ;- (SSC) Compare 0
AT91C_SSC_STOP            EQU (0x1 << 12) ;- (SSC) Receive Stop Selection
AT91C_SSC_STTDLY          EQU (0xFF << 16) ;- (SSC) Receive/Transmit Start Delay
AT91C_SSC_PERIOD          EQU (0xFF << 24) ;- (SSC) Receive/Transmit Period Divider Selection
// ---------SSC_RFMR：（SSC偏移：0x14）SSC接收帧模式寄存器--------
AT91C_SSC_DATLEN          EQU (0x1F <<  0) ;- (SSC) Data Length
AT91C_SSC_LOOP            EQU (0x1 <<  5) ;- (SSC) Loop Mode
AT91C_SSC_MSBF            EQU (0x1 <<  7) ;- (SSC) Most Significant Bit First
AT91C_SSC_DATNB           EQU (0xF <<  8) ;- (SSC) Data Number per Frame
AT91C_SSC_FSLEN           EQU (0xF << 16) ;- (SSC) Receive/Transmit Frame Sync length
AT91C_SSC_FSOS            EQU (0x7 << 20) ;- (SSC) Receive/Transmit Frame Sync Output Selection
AT91C_SSC_FSOS_NONE       EQU (0x0 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only
AT91C_SSC_FSOS_NEGATIVE   EQU (0x1 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse
AT91C_SSC_FSOS_POSITIVE   EQU (0x2 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse
AT91C_SSC_FSOS_LOW        EQU (0x3 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer
AT91C_SSC_FSOS_HIGH       EQU (0x4 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer
AT91C_SSC_FSOS_TOGGLE     EQU (0x5 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer
AT91C_SSC_FSEDGE          EQU (0x1 << 24) ;- (SSC) Frame Sync Edge Detection
// ---------SSC_TCMR：（SSC偏移：0x18）SSC传输时钟模式寄存器--------
// ---------SSC_TFMR：（SSC偏移：0x1c）SSC传输帧模式寄存器--------
AT91C_SSC_DATDEF          EQU (0x1 <<  5) ;- (SSC) Data Default Value
AT91C_SSC_FSDEN           EQU (0x1 << 23) ;- (SSC) Frame Sync Data Enable
// ---------SSC_SR：（SSC偏移量：0x40）SSC状态寄存器--------
AT91C_SSC_TXRDY           EQU (0x1 <<  0) ;- (SSC) Transmit Ready
AT91C_SSC_TXEMPTY         EQU (0x1 <<  1) ;- (SSC) Transmit Empty
AT91C_SSC_ENDTX           EQU (0x1 <<  2) ;- (SSC) End Of Transmission
AT91C_SSC_TXBUFE          EQU (0x1 <<  3) ;- (SSC) Transmit Buffer Empty
AT91C_SSC_RXRDY           EQU (0x1 <<  4) ;- (SSC) Receive Ready
AT91C_SSC_OVRUN           EQU (0x1 <<  5) ;- (SSC) Receive Overrun
AT91C_SSC_ENDRX           EQU (0x1 <<  6) ;- (SSC) End of Reception
AT91C_SSC_RXBUFF          EQU (0x1 <<  7) ;- (SSC) Receive Buffer Full
AT91C_SSC_CP0             EQU (0x1 <<  8) ;- (SSC) Compare 0
AT91C_SSC_CP1             EQU (0x1 <<  9) ;- (SSC) Compare 1
AT91C_SSC_TXSYN           EQU (0x1 << 10) ;- (SSC) Transmit Sync
AT91C_SSC_RXSYN           EQU (0x1 << 11) ;- (SSC) Receive Sync
AT91C_SSC_TXENA           EQU (0x1 << 16) ;- (SSC) Transmit Enable
AT91C_SSC_RXENA           EQU (0x1 << 17) ;- (SSC) Receive Enable
// ---------SSC_IER：（SSC偏移量：0x44）SSC中断启用寄存器--------
// ---------SSC_IDR：（SSC偏移量：0x48）SSC中断禁用寄存器--------
// ---------SSC_IMR：（SSC偏移量：0x4c）SSC中断掩码寄存器--------

// - *****************************************************************************
// -双线接口的软件API定义
// - *****************************************************************************
// ---------TWI_CR:（TWI偏移：0x0）TWI控制寄存器--------
AT91C_TWI_START           EQU (0x1 <<  0) ;- (TWI) Send a START Condition
AT91C_TWI_STOP            EQU (0x1 <<  1) ;- (TWI) Send a STOP Condition
AT91C_TWI_MSEN            EQU (0x1 <<  2) ;- (TWI) TWI Master Transfer Enabled
AT91C_TWI_MSDIS           EQU (0x1 <<  3) ;- (TWI) TWI Master Transfer Disabled
AT91C_TWI_SWRST           EQU (0x1 <<  7) ;- (TWI) Software Reset
// ---------TWI_MMR：（TWI偏移：0x4）TWI主模式寄存器--------
AT91C_TWI_IADRSZ          EQU (0x3 <<  8) ;- (TWI) Internal Device Address Size
AT91C_TWI_IADRSZ_NO       EQU (0x0 <<  8) ;- (TWI) No internal device address
AT91C_TWI_IADRSZ_1_BYTE   EQU (0x1 <<  8) ;- (TWI) One-byte internal device address
AT91C_TWI_IADRSZ_2_BYTE   EQU (0x2 <<  8) ;- (TWI) Two-byte internal device address
AT91C_TWI_IADRSZ_3_BYTE   EQU (0x3 <<  8) ;- (TWI) Three-byte internal device address
AT91C_TWI_MREAD           EQU (0x1 << 12) ;- (TWI) Master Read Direction
AT91C_TWI_DADR            EQU (0x7F << 16) ;- (TWI) Device Address
// ---------TWI_CWGR：（TWI偏移：0x10）TWI时钟波形发生器寄存器--------
AT91C_TWI_CLDIV           EQU (0xFF <<  0) ;- (TWI) Clock Low Divider
AT91C_TWI_CHDIV           EQU (0xFF <<  8) ;- (TWI) Clock High Divider
AT91C_TWI_CKDIV           EQU (0x7 << 16) ;- (TWI) Clock Divider
// ---------TWI_SR:（TWI偏移量：0x20）TWI状态寄存器--------
AT91C_TWI_TXCOMP          EQU (0x1 <<  0) ;- (TWI) Transmission Completed
AT91C_TWI_RXRDY           EQU (0x1 <<  1) ;- (TWI) Receive holding register ReaDY
AT91C_TWI_TXRDY           EQU (0x1 <<  2) ;- (TWI) Transmit holding register ReaDY
AT91C_TWI_OVRE            EQU (0x1 <<  6) ;- (TWI) Overrun Error
AT91C_TWI_UNRE            EQU (0x1 <<  7) ;- (TWI) Underrun Error
AT91C_TWI_NACK            EQU (0x1 <<  8) ;- (TWI) Not Acknowledged
// ---------TWI_IER:（TWI偏移：0x24）TWI中断启用寄存器--------
// ---------TWI_IDR:（TWI偏移：0x28）TWI中断禁用寄存器--------
// ---------TWI_MR：（TWI偏移：0x2c）TWI中断掩码寄存器--------

// - *****************************************************************************
// -PWMC通道接口的软件API定义
// - *****************************************************************************
// ---------PWMC_CMR：（PWMC_CH偏移：0x0）PWMC信道模式寄存器--------
AT91C_PWMC_CPRE           EQU (0xF <<  0) ;- (PWMC_CH) Channel Pre-scaler : PWMC_CLKx
AT91C_PWMC_CPRE_MCK       EQU (0x0) ;- (PWMC_CH) 
AT91C_PWMC_CPRE_MCKA      EQU (0xB) ;- (PWMC_CH) 
AT91C_PWMC_CPRE_MCKB      EQU (0xC) ;- (PWMC_CH) 
AT91C_PWMC_CALG           EQU (0x1 <<  8) ;- (PWMC_CH) Channel Alignment
AT91C_PWMC_CPOL           EQU (0x1 <<  9) ;- (PWMC_CH) Channel Polarity
AT91C_PWMC_CPD            EQU (0x1 << 10) ;- (PWMC_CH) Channel Update Period
// ---------PWMC_CDTYR：（PWMC_CH偏移：0x4）PWMC通道占空比寄存器--------
AT91C_PWMC_CDTY           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Duty Cycle
// ---------PWMC_CPRDR:（PWMC_CH偏移量：0x8）PWMC信道周期寄存器--------
AT91C_PWMC_CPRD           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Period
// ---------PWMC_CCNTR：（PWMC_CH偏移量：0xc）PWMC信道计数器寄存器--------
AT91C_PWMC_CCNT           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Counter
// ---------PWMC_CUPDR:（PWMC_CH偏移：0x10）PWMC信道更新寄存器--------
AT91C_PWMC_CUPD           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Update

// - *****************************************************************************
// -脉宽调制控制器接口的软件API定义
// - *****************************************************************************
// ---------PWMC_MR：（PWMC偏移：0x0）PWMC模式寄存器--------
AT91C_PWMC_DIVA           EQU (0xFF <<  0) ;- (PWMC) CLKA divide factor.
AT91C_PWMC_PREA           EQU (0xF <<  8) ;- (PWMC) Divider Input Clock Prescaler A
AT91C_PWMC_PREA_MCK       EQU (0x0 <<  8) ;- (PWMC) 
AT91C_PWMC_DIVB           EQU (0xFF << 16) ;- (PWMC) CLKB divide factor.
AT91C_PWMC_PREB           EQU (0xF << 24) ;- (PWMC) Divider Input Clock Prescaler B
AT91C_PWMC_PREB_MCK       EQU (0x0 << 24) ;- (PWMC) 
// ---------PWMC_ENA:（PWMC偏移：0x4）PWMC启用寄存器--------
AT91C_PWMC_CHID0          EQU (0x1 <<  0) ;- (PWMC) Channel ID 0
AT91C_PWMC_CHID1          EQU (0x1 <<  1) ;- (PWMC) Channel ID 1
AT91C_PWMC_CHID2          EQU (0x1 <<  2) ;- (PWMC) Channel ID 2
AT91C_PWMC_CHID3          EQU (0x1 <<  3) ;- (PWMC) Channel ID 3
// ---------PWMC_DIS:（PWMC偏移：0x8）PWMC禁用寄存器--------
// ---------PWMC_SR：（PWMC偏移量：0xc）PWMC状态寄存器--------
// ---------PWMC_IER:（PWMC偏移：0x10）PWMC中断启用寄存器--------
// ---------PWMC_IDR：（PWMC偏移：0x14）PWMC中断禁用寄存器--------
// ---------PWMC_IMR：（PWMC偏移：0x18）PWMC中断掩码寄存器--------
// ---------PWMC_ISR:（PWMC偏移：0x1c）PWMC中断状态寄存器--------

// - *****************************************************************************
// -USB设备接口的软件API定义
// - *****************************************************************************
// ---------UDP_FRM_NUM：（UDP偏移：0x0）USB帧号寄存器--------
AT91C_UDP_FRM_NUM         EQU (0x7FF <<  0) ;- (UDP) Frame Number as Defined in the Packet Field Formats
AT91C_UDP_FRM_ERR         EQU (0x1 << 16) ;- (UDP) Frame Error
AT91C_UDP_FRM_OK          EQU (0x1 << 17) ;- (UDP) Frame OK
// ---------UDP_GLB_STATE:（UDP偏移量：0x4）USB全局状态寄存器--------
AT91C_UDP_FADDEN          EQU (0x1 <<  0) ;- (UDP) Function Address Enable
AT91C_UDP_CONFG           EQU (0x1 <<  1) ;- (UDP) Configured
AT91C_UDP_ESR             EQU (0x1 <<  2) ;- (UDP) Enable Send Resume
AT91C_UDP_RSMINPR         EQU (0x1 <<  3) ;- (UDP) A Resume Has Been Sent to the Host
AT91C_UDP_RMWUPE          EQU (0x1 <<  4) ;- (UDP) Remote Wake Up Enable
// ---------UDP_FADDR:（UDP偏移量：0x8）USB功能地址寄存器--------
AT91C_UDP_FADD            EQU (0xFF <<  0) ;- (UDP) Function Address Value
AT91C_UDP_FEN             EQU (0x1 <<  8) ;- (UDP) Function Enable
// ---------UDP_IER:（UDP偏移：0x10）USB中断启用寄存器--------
AT91C_UDP_EPINT0          EQU (0x1 <<  0) ;- (UDP) Endpoint 0 Interrupt
AT91C_UDP_EPINT1          EQU (0x1 <<  1) ;- (UDP) Endpoint 0 Interrupt
AT91C_UDP_EPINT2          EQU (0x1 <<  2) ;- (UDP) Endpoint 2 Interrupt
AT91C_UDP_EPINT3          EQU (0x1 <<  3) ;- (UDP) Endpoint 3 Interrupt
AT91C_UDP_EPINT4          EQU (0x1 <<  4) ;- (UDP) Endpoint 4 Interrupt
AT91C_UDP_EPINT5          EQU (0x1 <<  5) ;- (UDP) Endpoint 5 Interrupt
AT91C_UDP_RXSUSP          EQU (0x1 <<  8) ;- (UDP) USB Suspend Interrupt
AT91C_UDP_RXRSM           EQU (0x1 <<  9) ;- (UDP) USB Resume Interrupt
AT91C_UDP_EXTRSM          EQU (0x1 << 10) ;- (UDP) USB External Resume Interrupt
AT91C_UDP_SOFINT          EQU (0x1 << 11) ;- (UDP) USB Start Of frame Interrupt
AT91C_UDP_WAKEUP          EQU (0x1 << 13) ;- (UDP) USB Resume Interrupt
// ---------UDP_IDR：（UDP偏移：0x14）USB中断禁用寄存器--------
// ---------UDP_IMR：（UDP偏移：0x18）USB中断掩码寄存器--------
// ---------UDP_ISR：（UDP偏移量：0x1c）USB中断状态寄存器--------
AT91C_UDP_ENDBUSRES       EQU (0x1 << 12) ;- (UDP) USB End Of Bus Reset Interrupt
// ---------UDP_ICR：（UDP偏移量：0x20）USB中断清除寄存器--------
// ---------UDP_RST_EP:（UDP偏移量：0x28）USB重置端点寄存器--------
AT91C_UDP_EP0             EQU (0x1 <<  0) ;- (UDP) Reset Endpoint 0
AT91C_UDP_EP1             EQU (0x1 <<  1) ;- (UDP) Reset Endpoint 1
AT91C_UDP_EP2             EQU (0x1 <<  2) ;- (UDP) Reset Endpoint 2
AT91C_UDP_EP3             EQU (0x1 <<  3) ;- (UDP) Reset Endpoint 3
AT91C_UDP_EP4             EQU (0x1 <<  4) ;- (UDP) Reset Endpoint 4
AT91C_UDP_EP5             EQU (0x1 <<  5) ;- (UDP) Reset Endpoint 5
// ---------UDP_CSR：（UDP偏移量：0x30）USB端点控制和状态寄存器--------
AT91C_UDP_TXCOMP          EQU (0x1 <<  0) ;- (UDP) Generates an IN packet with data previously written in the DPR
AT91C_UDP_RX_DATA_BK0     EQU (0x1 <<  1) ;- (UDP) Receive Data Bank 0
AT91C_UDP_RXSETUP         EQU (0x1 <<  2) ;- (UDP) Sends STALL to the Host (Control endpoints)
AT91C_UDP_ISOERROR        EQU (0x1 <<  3) ;- (UDP) Isochronous error (Isochronous endpoints)
AT91C_UDP_TXPKTRDY        EQU (0x1 <<  4) ;- (UDP) Transmit Packet Ready
AT91C_UDP_FORCESTALL      EQU (0x1 <<  5) ;- (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints).
AT91C_UDP_RX_DATA_BK1     EQU (0x1 <<  6) ;- (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes).
AT91C_UDP_DIR             EQU (0x1 <<  7) ;- (UDP) Transfer Direction
AT91C_UDP_EPTYPE          EQU (0x7 <<  8) ;- (UDP) Endpoint type
AT91C_UDP_EPTYPE_CTRL     EQU (0x0 <<  8) ;- (UDP) Control
AT91C_UDP_EPTYPE_ISO_OUT  EQU (0x1 <<  8) ;- (UDP) Isochronous OUT
AT91C_UDP_EPTYPE_BULK_OUT EQU (0x2 <<  8) ;- (UDP) Bulk OUT
AT91C_UDP_EPTYPE_INT_OUT  EQU (0x3 <<  8) ;- (UDP) Interrupt OUT
AT91C_UDP_EPTYPE_ISO_IN   EQU (0x5 <<  8) ;- (UDP) Isochronous IN
AT91C_UDP_EPTYPE_BULK_IN  EQU (0x6 <<  8) ;- (UDP) Bulk IN
AT91C_UDP_EPTYPE_INT_IN   EQU (0x7 <<  8) ;- (UDP) Interrupt IN
AT91C_UDP_DTGLE           EQU (0x1 << 11) ;- (UDP) Data Toggle
AT91C_UDP_EPEDS           EQU (0x1 << 15) ;- (UDP) Endpoint Enable Disable
AT91C_UDP_RXBYTECNT       EQU (0x7FF << 16) ;- (UDP) Number Of Bytes Available in the FIFO
// ---------UDP_TXVC:（UDP偏移：0x74）收发器控制寄存器--------
AT91C_UDP_TXVDIS          EQU (0x1 <<  8) ;- (UDP) 
AT91C_UDP_PUON            EQU (0x1 <<  9) ;- (UDP) Pull-up ON

// - *****************************************************************************
// -定时器计数器通道接口的软件API定义
// - *****************************************************************************
// ---------TC_CCR：（TC偏移：0x0）TC信道控制寄存器--------
AT91C_TC_CLKEN            EQU (0x1 <<  0) ;- (TC) Counter Clock Enable Command
AT91C_TC_CLKDIS           EQU (0x1 <<  1) ;- (TC) Counter Clock Disable Command
AT91C_TC_SWTRG            EQU (0x1 <<  2) ;- (TC) Software Trigger Command
// ---------TC_CMR：（TC偏移：0x4）TC信道模式寄存器：捕获模式/波形模式--------
AT91C_TC_CLKS             EQU (0x7 <<  0) ;- (TC) Clock Selection
AT91C_TC_CLKS_TIMER_DIV1_CLOCK EQU (0x0) ;- (TC) Clock selected: TIMER_DIV1_CLOCK
AT91C_TC_CLKS_TIMER_DIV2_CLOCK EQU (0x1) ;- (TC) Clock selected: TIMER_DIV2_CLOCK
AT91C_TC_CLKS_TIMER_DIV3_CLOCK EQU (0x2) ;- (TC) Clock selected: TIMER_DIV3_CLOCK
AT91C_TC_CLKS_TIMER_DIV4_CLOCK EQU (0x3) ;- (TC) Clock selected: TIMER_DIV4_CLOCK
AT91C_TC_CLKS_TIMER_DIV5_CLOCK EQU (0x4) ;- (TC) Clock selected: TIMER_DIV5_CLOCK
AT91C_TC_CLKS_XC0         EQU (0x5) ;- (TC) Clock selected: XC0
AT91C_TC_CLKS_XC1         EQU (0x6) ;- (TC) Clock selected: XC1
AT91C_TC_CLKS_XC2         EQU (0x7) ;- (TC) Clock selected: XC2
AT91C_TC_CLKI             EQU (0x1 <<  3) ;- (TC) Clock Invert
AT91C_TC_BURST            EQU (0x3 <<  4) ;- (TC) Burst Signal Selection
AT91C_TC_BURST_NONE       EQU (0x0 <<  4) ;- (TC) The clock is not gated by an external signal
AT91C_TC_BURST_XC0        EQU (0x1 <<  4) ;- (TC) XC0 is ANDed with the selected clock
AT91C_TC_BURST_XC1        EQU (0x2 <<  4) ;- (TC) XC1 is ANDed with the selected clock
AT91C_TC_BURST_XC2        EQU (0x3 <<  4) ;- (TC) XC2 is ANDed with the selected clock
AT91C_TC_CPCSTOP          EQU (0x1 <<  6) ;- (TC) Counter Clock Stopped with RC Compare
AT91C_TC_LDBSTOP          EQU (0x1 <<  6) ;- (TC) Counter Clock Stopped with RB Loading
AT91C_TC_CPCDIS           EQU (0x1 <<  7) ;- (TC) Counter Clock Disable with RC Compare
AT91C_TC_LDBDIS           EQU (0x1 <<  7) ;- (TC) Counter Clock Disabled with RB Loading
AT91C_TC_ETRGEDG          EQU (0x3 <<  8) ;- (TC) External Trigger Edge Selection
AT91C_TC_ETRGEDG_NONE     EQU (0x0 <<  8) ;- (TC) Edge: None
AT91C_TC_ETRGEDG_RISING   EQU (0x1 <<  8) ;- (TC) Edge: rising edge
AT91C_TC_ETRGEDG_FALLING  EQU (0x2 <<  8) ;- (TC) Edge: falling edge
AT91C_TC_ETRGEDG_BOTH     EQU (0x3 <<  8) ;- (TC) Edge: each edge
AT91C_TC_EEVTEDG          EQU (0x3 <<  8) ;- (TC) External Event Edge Selection
AT91C_TC_EEVTEDG_NONE     EQU (0x0 <<  8) ;- (TC) Edge: None
AT91C_TC_EEVTEDG_RISING   EQU (0x1 <<  8) ;- (TC) Edge: rising edge
AT91C_TC_EEVTEDG_FALLING  EQU (0x2 <<  8) ;- (TC) Edge: falling edge
AT91C_TC_EEVTEDG_BOTH     EQU (0x3 <<  8) ;- (TC) Edge: each edge
AT91C_TC_EEVT             EQU (0x3 << 10) ;- (TC) External Event  Selection
AT91C_TC_EEVT_TIOB        EQU (0x0 << 10) ;- (TC) Signal selected as external event: TIOB TIOB direction: input
AT91C_TC_EEVT_XC0         EQU (0x1 << 10) ;- (TC) Signal selected as external event: XC0 TIOB direction: output
AT91C_TC_EEVT_XC1         EQU (0x2 << 10) ;- (TC) Signal selected as external event: XC1 TIOB direction: output
AT91C_TC_EEVT_XC2         EQU (0x3 << 10) ;- (TC) Signal selected as external event: XC2 TIOB direction: output
AT91C_TC_ABETRG           EQU (0x1 << 10) ;- (TC) TIOA or TIOB External Trigger Selection
AT91C_TC_ENETRG           EQU (0x1 << 12) ;- (TC) External Event Trigger enable
AT91C_TC_WAVESEL          EQU (0x3 << 13) ;- (TC) Waveform  Selection
AT91C_TC_WAVESEL_UP       EQU (0x0 << 13) ;- (TC) UP mode without atomatic trigger on RC Compare
AT91C_TC_WAVESEL_UPDOWN   EQU (0x1 << 13) ;- (TC) UPDOWN mode without automatic trigger on RC Compare
AT91C_TC_WAVESEL_UP_AUTO  EQU (0x2 << 13) ;- (TC) UP mode with automatic trigger on RC Compare
AT91C_TC_WAVESEL_UPDOWN_AUTO EQU (0x3 << 13) ;- (TC) UPDOWN mode with automatic trigger on RC Compare
AT91C_TC_CPCTRG           EQU (0x1 << 14) ;- (TC) RC Compare Trigger Enable
AT91C_TC_WAVE             EQU (0x1 << 15) ;- (TC) 
AT91C_TC_ACPA             EQU (0x3 << 16) ;- (TC) RA Compare Effect on TIOA
AT91C_TC_ACPA_NONE        EQU (0x0 << 16) ;- (TC) Effect: none
AT91C_TC_ACPA_SET         EQU (0x1 << 16) ;- (TC) Effect: set
AT91C_TC_ACPA_CLEAR       EQU (0x2 << 16) ;- (TC) Effect: clear
AT91C_TC_ACPA_TOGGLE      EQU (0x3 << 16) ;- (TC) Effect: toggle
AT91C_TC_LDRA             EQU (0x3 << 16) ;- (TC) RA Loading Selection
AT91C_TC_LDRA_NONE        EQU (0x0 << 16) ;- (TC) Edge: None
AT91C_TC_LDRA_RISING      EQU (0x1 << 16) ;- (TC) Edge: rising edge of TIOA
AT91C_TC_LDRA_FALLING     EQU (0x2 << 16) ;- (TC) Edge: falling edge of TIOA
AT91C_TC_LDRA_BOTH        EQU (0x3 << 16) ;- (TC) Edge: each edge of TIOA
AT91C_TC_ACPC             EQU (0x3 << 18) ;- (TC) RC Compare Effect on TIOA
AT91C_TC_ACPC_NONE        EQU (0x0 << 18) ;- (TC) Effect: none
AT91C_TC_ACPC_SET         EQU (0x1 << 18) ;- (TC) Effect: set
AT91C_TC_ACPC_CLEAR       EQU (0x2 << 18) ;- (TC) Effect: clear
AT91C_TC_ACPC_TOGGLE      EQU (0x3 << 18) ;- (TC) Effect: toggle
AT91C_TC_LDRB             EQU (0x3 << 18) ;- (TC) RB Loading Selection
AT91C_TC_LDRB_NONE        EQU (0x0 << 18) ;- (TC) Edge: None
AT91C_TC_LDRB_RISING      EQU (0x1 << 18) ;- (TC) Edge: rising edge of TIOA
AT91C_TC_LDRB_FALLING     EQU (0x2 << 18) ;- (TC) Edge: falling edge of TIOA
AT91C_TC_LDRB_BOTH        EQU (0x3 << 18) ;- (TC) Edge: each edge of TIOA
AT91C_TC_AEEVT            EQU (0x3 << 20) ;- (TC) External Event Effect on TIOA
AT91C_TC_AEEVT_NONE       EQU (0x0 << 20) ;- (TC) Effect: none
AT91C_TC_AEEVT_SET        EQU (0x1 << 20) ;- (TC) Effect: set
AT91C_TC_AEEVT_CLEAR      EQU (0x2 << 20) ;- (TC) Effect: clear
AT91C_TC_AEEVT_TOGGLE     EQU (0x3 << 20) ;- (TC) Effect: toggle
AT91C_TC_ASWTRG           EQU (0x3 << 22) ;- (TC) Software Trigger Effect on TIOA
AT91C_TC_ASWTRG_NONE      EQU (0x0 << 22) ;- (TC) Effect: none
AT91C_TC_ASWTRG_SET       EQU (0x1 << 22) ;- (TC) Effect: set
AT91C_TC_ASWTRG_CLEAR     EQU (0x2 << 22) ;- (TC) Effect: clear
AT91C_TC_ASWTRG_TOGGLE    EQU (0x3 << 22) ;- (TC) Effect: toggle
AT91C_TC_BCPB             EQU (0x3 << 24) ;- (TC) RB Compare Effect on TIOB
AT91C_TC_BCPB_NONE        EQU (0x0 << 24) ;- (TC) Effect: none
AT91C_TC_BCPB_SET         EQU (0x1 << 24) ;- (TC) Effect: set
AT91C_TC_BCPB_CLEAR       EQU (0x2 << 24) ;- (TC) Effect: clear
AT91C_TC_BCPB_TOGGLE      EQU (0x3 << 24) ;- (TC) Effect: toggle
AT91C_TC_BCPC             EQU (0x3 << 26) ;- (TC) RC Compare Effect on TIOB
AT91C_TC_BCPC_NONE        EQU (0x0 << 26) ;- (TC) Effect: none
AT91C_TC_BCPC_SET         EQU (0x1 << 26) ;- (TC) Effect: set
AT91C_TC_BCPC_CLEAR       EQU (0x2 << 26) ;- (TC) Effect: clear
AT91C_TC_BCPC_TOGGLE      EQU (0x3 << 26) ;- (TC) Effect: toggle
AT91C_TC_BEEVT            EQU (0x3 << 28) ;- (TC) External Event Effect on TIOB
AT91C_TC_BEEVT_NONE       EQU (0x0 << 28) ;- (TC) Effect: none
AT91C_TC_BEEVT_SET        EQU (0x1 << 28) ;- (TC) Effect: set
AT91C_TC_BEEVT_CLEAR      EQU (0x2 << 28) ;- (TC) Effect: clear
AT91C_TC_BEEVT_TOGGLE     EQU (0x3 << 28) ;- (TC) Effect: toggle
AT91C_TC_BSWTRG           EQU (0x3 << 30) ;- (TC) Software Trigger Effect on TIOB
AT91C_TC_BSWTRG_NONE      EQU (0x0 << 30) ;- (TC) Effect: none
AT91C_TC_BSWTRG_SET       EQU (0x1 << 30) ;- (TC) Effect: set
AT91C_TC_BSWTRG_CLEAR     EQU (0x2 << 30) ;- (TC) Effect: clear
AT91C_TC_BSWTRG_TOGGLE    EQU (0x3 << 30) ;- (TC) Effect: toggle
// ---------TC_SR：（TC偏移：0x20）TC信道状态寄存器--------
AT91C_TC_COVFS            EQU (0x1 <<  0) ;- (TC) Counter Overflow
AT91C_TC_LOVRS            EQU (0x1 <<  1) ;- (TC) Load Overrun
AT91C_TC_CPAS             EQU (0x1 <<  2) ;- (TC) RA Compare
AT91C_TC_CPBS             EQU (0x1 <<  3) ;- (TC) RB Compare
AT91C_TC_CPCS             EQU (0x1 <<  4) ;- (TC) RC Compare
AT91C_TC_LDRAS            EQU (0x1 <<  5) ;- (TC) RA Loading
AT91C_TC_LDRBS            EQU (0x1 <<  6) ;- (TC) RB Loading
AT91C_TC_ETRGS            EQU (0x1 <<  7) ;- (TC) External Trigger
AT91C_TC_CLKSTA           EQU (0x1 << 16) ;- (TC) Clock Enabling
AT91C_TC_MTIOA            EQU (0x1 << 17) ;- (TC) TIOA Mirror
AT91C_TC_MTIOB            EQU (0x1 << 18) ;- (TC) TIOA Mirror
// ---------TC_IER：（TC偏移：0x24）TC通道中断启用寄存器--------
// ---------TC_IDR：（TC偏移：0x28）TC通道中断禁用寄存器--------
// ---------TC_IMR：（TC偏移：0x2c）TC通道中断掩码寄存器--------

// - *****************************************************************************
// -定时器计数器接口的软件API定义
// - *****************************************************************************
// ---------TCB_BCR：（TCB偏移量：0xc0）TC块控制寄存器--------
AT91C_TCB_SYNC            EQU (0x1 <<  0) ;- (TCB) Synchro Command
// ---------TCB_BMR：（TCB偏移量：0xc4）TC块模式寄存器--------
AT91C_TCB_TC0XC0S         EQU (0x3 <<  0) ;- (TCB) External Clock Signal 0 Selection
AT91C_TCB_TC0XC0S_TCLK0   EQU (0x0) ;- (TCB) TCLK0 connected to XC0
AT91C_TCB_TC0XC0S_NONE    EQU (0x1) ;- (TCB) None signal connected to XC0
AT91C_TCB_TC0XC0S_TIOA1   EQU (0x2) ;- (TCB) TIOA1 connected to XC0
AT91C_TCB_TC0XC0S_TIOA2   EQU (0x3) ;- (TCB) TIOA2 connected to XC0
AT91C_TCB_TC1XC1S         EQU (0x3 <<  2) ;- (TCB) External Clock Signal 1 Selection
AT91C_TCB_TC1XC1S_TCLK1   EQU (0x0 <<  2) ;- (TCB) TCLK1 connected to XC1
AT91C_TCB_TC1XC1S_NONE    EQU (0x1 <<  2) ;- (TCB) None signal connected to XC1
AT91C_TCB_TC1XC1S_TIOA0   EQU (0x2 <<  2) ;- (TCB) TIOA0 connected to XC1
AT91C_TCB_TC1XC1S_TIOA2   EQU (0x3 <<  2) ;- (TCB) TIOA2 connected to XC1
AT91C_TCB_TC2XC2S         EQU (0x3 <<  4) ;- (TCB) External Clock Signal 2 Selection
AT91C_TCB_TC2XC2S_TCLK2   EQU (0x0 <<  4) ;- (TCB) TCLK2 connected to XC2
AT91C_TCB_TC2XC2S_NONE    EQU (0x1 <<  4) ;- (TCB) None signal connected to XC2
AT91C_TCB_TC2XC2S_TIOA0   EQU (0x2 <<  4) ;- (TCB) TIOA0 connected to XC2
AT91C_TCB_TC2XC2S_TIOA1   EQU (0x3 <<  4) ;- (TCB) TIOA2 connected to XC2

// - *****************************************************************************
// -控制区域网络邮箱接口的软件API定义
// - *****************************************************************************
// ---------CAN_MMR：（CAN_MB偏移：0x0）CAN消息模式寄存器--------
AT91C_CAN_MTIMEMARK       EQU (0xFFFF <<  0) ;- (CAN_MB) Mailbox Timemark
AT91C_CAN_PRIOR           EQU (0xF << 16) ;- (CAN_MB) Mailbox Priority
AT91C_CAN_MOT             EQU (0x7 << 24) ;- (CAN_MB) Mailbox Object Type
AT91C_CAN_MOT_DIS         EQU (0x0 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_RX          EQU (0x1 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_RXOVERWRITE EQU (0x2 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_TX          EQU (0x3 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_CONSUMER    EQU (0x4 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_PRODUCER    EQU (0x5 << 24) ;- (CAN_MB) 
// ---------CAN_MAM：（CAN_MB偏移：0x4）CAN消息接受掩码寄存器--------
AT91C_CAN_MIDvB           EQU (0x3FFFF <<  0) ;- (CAN_MB) Complementary bits for identifier in extended mode
AT91C_CAN_MIDvA           EQU (0x7FF << 18) ;- (CAN_MB) Identifier for standard frame mode
AT91C_CAN_MIDE            EQU (0x1 << 29) ;- (CAN_MB) Identifier Version
// ---------CAN_MID:（CAN_MB偏移：0x8）CAN消息ID寄存器--------
// ---------CAN_MFID：（CAN_MB偏移：0xc）CAN消息系列ID寄存器--------
// ---------CAN_MSR:（CAN_MB偏移：0x10）CAN消息状态寄存器--------
AT91C_CAN_MTIMESTAMP      EQU (0xFFFF <<  0) ;- (CAN_MB) Timer Value
AT91C_CAN_MDLC            EQU (0xF << 16) ;- (CAN_MB) Mailbox Data Length Code
AT91C_CAN_MRTR            EQU (0x1 << 20) ;- (CAN_MB) Mailbox Remote Transmission Request
AT91C_CAN_MABT            EQU (0x1 << 22) ;- (CAN_MB) Mailbox Message Abort
AT91C_CAN_MRDY            EQU (0x1 << 23) ;- (CAN_MB) Mailbox Ready
AT91C_CAN_MMI             EQU (0x1 << 24) ;- (CAN_MB) Mailbox Message Ignored
// ---------CAN_MDL:（CAN_MB偏移：0x14）CAN消息数据低寄存器--------
// ---------CAN_MDH:（CAN_MB偏移：0x18）CAN消息数据高位寄存器--------
// ---------CAN_MCR：（CAN_MB偏移：0x1c）CAN消息控制寄存器--------
AT91C_CAN_MACR            EQU (0x1 << 22) ;- (CAN_MB) Abort Request for Mailbox
AT91C_CAN_MTCR            EQU (0x1 << 23) ;- (CAN_MB) Mailbox Transfer Command

// - *****************************************************************************
// -控制区域网络接口的软件API定义
// - *****************************************************************************
// ---------CAN_MR：（CAN偏移：0x0）CAN模式寄存器--------
AT91C_CAN_CANEN           EQU (0x1 <<  0) ;- (CAN) CAN Controller Enable
AT91C_CAN_LPM             EQU (0x1 <<  1) ;- (CAN) Disable/Enable Low Power Mode
AT91C_CAN_ABM             EQU (0x1 <<  2) ;- (CAN) Disable/Enable Autobaud/Listen Mode
AT91C_CAN_OVL             EQU (0x1 <<  3) ;- (CAN) Disable/Enable Overload Frame
AT91C_CAN_TEOF            EQU (0x1 <<  4) ;- (CAN) Time Stamp messages at each end of Frame
AT91C_CAN_TTM             EQU (0x1 <<  5) ;- (CAN) Disable/Enable Time Trigger Mode
AT91C_CAN_TIMFRZ          EQU (0x1 <<  6) ;- (CAN) Enable Timer Freeze
AT91C_CAN_DRPT            EQU (0x1 <<  7) ;- (CAN) Disable Repeat
// ---------CAN_IER:（CAN偏移：0x4）CAN中断启用寄存器--------
AT91C_CAN_MB0             EQU (0x1 <<  0) ;- (CAN) Mailbox 0 Flag
AT91C_CAN_MB1             EQU (0x1 <<  1) ;- (CAN) Mailbox 1 Flag
AT91C_CAN_MB2             EQU (0x1 <<  2) ;- (CAN) Mailbox 2 Flag
AT91C_CAN_MB3             EQU (0x1 <<  3) ;- (CAN) Mailbox 3 Flag
AT91C_CAN_MB4             EQU (0x1 <<  4) ;- (CAN) Mailbox 4 Flag
AT91C_CAN_MB5             EQU (0x1 <<  5) ;- (CAN) Mailbox 5 Flag
AT91C_CAN_MB6             EQU (0x1 <<  6) ;- (CAN) Mailbox 6 Flag
AT91C_CAN_MB7             EQU (0x1 <<  7) ;- (CAN) Mailbox 7 Flag
AT91C_CAN_MB8             EQU (0x1 <<  8) ;- (CAN) Mailbox 8 Flag
AT91C_CAN_MB9             EQU (0x1 <<  9) ;- (CAN) Mailbox 9 Flag
AT91C_CAN_MB10            EQU (0x1 << 10) ;- (CAN) Mailbox 10 Flag
AT91C_CAN_MB11            EQU (0x1 << 11) ;- (CAN) Mailbox 11 Flag
AT91C_CAN_MB12            EQU (0x1 << 12) ;- (CAN) Mailbox 12 Flag
AT91C_CAN_MB13            EQU (0x1 << 13) ;- (CAN) Mailbox 13 Flag
AT91C_CAN_MB14            EQU (0x1 << 14) ;- (CAN) Mailbox 14 Flag
AT91C_CAN_MB15            EQU (0x1 << 15) ;- (CAN) Mailbox 15 Flag
AT91C_CAN_ERRA            EQU (0x1 << 16) ;- (CAN) Error Active Mode Flag
AT91C_CAN_WARN            EQU (0x1 << 17) ;- (CAN) Warning Limit Flag
AT91C_CAN_ERRP            EQU (0x1 << 18) ;- (CAN) Error Passive Mode Flag
AT91C_CAN_BOFF            EQU (0x1 << 19) ;- (CAN) Bus Off Mode Flag
AT91C_CAN_SLEEP           EQU (0x1 << 20) ;- (CAN) Sleep Flag
AT91C_CAN_WAKEUP          EQU (0x1 << 21) ;- (CAN) Wakeup Flag
AT91C_CAN_TOVF            EQU (0x1 << 22) ;- (CAN) Timer Overflow Flag
AT91C_CAN_TSTP            EQU (0x1 << 23) ;- (CAN) Timestamp Flag
AT91C_CAN_CERR            EQU (0x1 << 24) ;- (CAN) CRC Error
AT91C_CAN_SERR            EQU (0x1 << 25) ;- (CAN) Stuffing Error
AT91C_CAN_AERR            EQU (0x1 << 26) ;- (CAN) Acknowledgment Error
AT91C_CAN_FERR            EQU (0x1 << 27) ;- (CAN) Form Error
AT91C_CAN_BERR            EQU (0x1 << 28) ;- (CAN) Bit Error
// ---------CAN_IDR:（CAN偏移：0x8）CAN中断禁用寄存器--------
// ---------CAN_IMR：（CAN偏移：0xc）CAN中断掩码寄存器--------
// ---------CAN_SR：（CAN偏移：0x10）CAN状态寄存器--------
AT91C_CAN_RBSY            EQU (0x1 << 29) ;- (CAN) Receiver Busy
AT91C_CAN_TBSY            EQU (0x1 << 30) ;- (CAN) Transmitter Busy
AT91C_CAN_OVLY            EQU (0x1 << 31) ;- (CAN) Overload Busy
// ---------CAN_BR：（CAN偏移：0x14）CAN波特率寄存器--------
AT91C_CAN_PHASE2          EQU (0x7 <<  0) ;- (CAN) Phase 2 segment
AT91C_CAN_PHASE1          EQU (0x7 <<  4) ;- (CAN) Phase 1 segment
AT91C_CAN_PROPAG          EQU (0x7 <<  8) ;- (CAN) Programmation time segment
AT91C_CAN_SYNC            EQU (0x3 << 12) ;- (CAN) Re-synchronization jump width segment
AT91C_CAN_BRP             EQU (0x7F << 16) ;- (CAN) Baudrate Prescaler
AT91C_CAN_SMP             EQU (0x1 << 24) ;- (CAN) Sampling mode
// ---------CAN_TIM:（CAN偏移：0x18）CAN计时器寄存器--------
AT91C_CAN_TIMER           EQU (0xFFFF <<  0) ;- (CAN) Timer field
// ---------CAN_TIMESTP:（CAN偏移：0x1c）CAN时间戳寄存器--------
// ---------CAN_ECR:（CAN偏移：0x20）CAN错误计数器寄存器--------
AT91C_CAN_REC             EQU (0xFF <<  0) ;- (CAN) Receive Error Counter
AT91C_CAN_TEC             EQU (0xFF << 16) ;- (CAN) Transmit Error Counter
// ---------CAN_TCR：（CAN偏移：0x24）CAN传输命令寄存器--------
AT91C_CAN_TIMRST          EQU (0x1 << 31) ;- (CAN) Timer Reset Field
// ---------CAN_ACR:（CAN偏移：0x28）CAN中止命令寄存器--------

// - *****************************************************************************
// -以太网MAC 10/100的软件API定义
// - *****************************************************************************
// ---------EMAC_NCR：（EMAC偏移：0x0）--------
AT91C_EMAC_LB             EQU (0x1 <<  0) ;- (EMAC) Loopback. Optional. When set, loopback signal is at high level.
AT91C_EMAC_LLB            EQU (0x1 <<  1) ;- (EMAC) Loopback local. 
AT91C_EMAC_RE             EQU (0x1 <<  2) ;- (EMAC) Receive enable. 
AT91C_EMAC_TE             EQU (0x1 <<  3) ;- (EMAC) Transmit enable. 
AT91C_EMAC_MPE            EQU (0x1 <<  4) ;- (EMAC) Management port enable. 
AT91C_EMAC_CLRSTAT        EQU (0x1 <<  5) ;- (EMAC) Clear statistics registers. 
AT91C_EMAC_INCSTAT        EQU (0x1 <<  6) ;- (EMAC) Increment statistics registers. 
AT91C_EMAC_WESTAT         EQU (0x1 <<  7) ;- (EMAC) Write enable for statistics registers. 
AT91C_EMAC_BP             EQU (0x1 <<  8) ;- (EMAC) Back pressure. 
AT91C_EMAC_TSTART         EQU (0x1 <<  9) ;- (EMAC) Start Transmission. 
AT91C_EMAC_THALT          EQU (0x1 << 10) ;- (EMAC) Transmission Halt. 
AT91C_EMAC_TPFR           EQU (0x1 << 11) ;- (EMAC) Transmit pause frame 
AT91C_EMAC_TZQ            EQU (0x1 << 12) ;- (EMAC) Transmit zero quantum pause frame
// ---------EMAC_NCFGR：（EMAC偏移：0x4）网络配置寄存器--------
AT91C_EMAC_SPD            EQU (0x1 <<  0) ;- (EMAC) Speed. 
AT91C_EMAC_FD             EQU (0x1 <<  1) ;- (EMAC) Full duplex. 
AT91C_EMAC_JFRAME         EQU (0x1 <<  3) ;- (EMAC) Jumbo Frames. 
AT91C_EMAC_CAF            EQU (0x1 <<  4) ;- (EMAC) Copy all frames. 
AT91C_EMAC_NBC            EQU (0x1 <<  5) ;- (EMAC) No broadcast. 
AT91C_EMAC_MTI            EQU (0x1 <<  6) ;- (EMAC) Multicast hash event enable
AT91C_EMAC_UNI            EQU (0x1 <<  7) ;- (EMAC) Unicast hash enable. 
AT91C_EMAC_BIG            EQU (0x1 <<  8) ;- (EMAC) Receive 1522 bytes. 
AT91C_EMAC_EAE            EQU (0x1 <<  9) ;- (EMAC) External address match enable. 
AT91C_EMAC_CLK            EQU (0x3 << 10) ;- (EMAC) 
AT91C_EMAC_CLK_HCLK_8     EQU (0x0 << 10) ;- (EMAC) HCLK divided by 8
AT91C_EMAC_CLK_HCLK_16    EQU (0x1 << 10) ;- (EMAC) HCLK divided by 16
AT91C_EMAC_CLK_HCLK_32    EQU (0x2 << 10) ;- (EMAC) HCLK divided by 32
AT91C_EMAC_CLK_HCLK_64    EQU (0x3 << 10) ;- (EMAC) HCLK divided by 64
AT91C_EMAC_RTY            EQU (0x1 << 12) ;- (EMAC) 
AT91C_EMAC_PAE            EQU (0x1 << 13) ;- (EMAC) 
AT91C_EMAC_RBOF           EQU (0x3 << 14) ;- (EMAC) 
AT91C_EMAC_RBOF_OFFSET_0  EQU (0x0 << 14) ;- (EMAC) no offset from start of receive buffer
AT91C_EMAC_RBOF_OFFSET_1  EQU (0x1 << 14) ;- (EMAC) one byte offset from start of receive buffer
AT91C_EMAC_RBOF_OFFSET_2  EQU (0x2 << 14) ;- (EMAC) two bytes offset from start of receive buffer
AT91C_EMAC_RBOF_OFFSET_3  EQU (0x3 << 14) ;- (EMAC) three bytes offset from start of receive buffer
AT91C_EMAC_RLCE           EQU (0x1 << 16) ;- (EMAC) Receive Length field Checking Enable
AT91C_EMAC_DRFCS          EQU (0x1 << 17) ;- (EMAC) Discard Receive FCS
AT91C_EMAC_EFRHD          EQU (0x1 << 18) ;- (EMAC) 
AT91C_EMAC_IRXFCS         EQU (0x1 << 19) ;- (EMAC) Ignore RX FCS
// ---------EMAC_NSR:（EMAC偏移量：0x8）网络状态寄存器--------
AT91C_EMAC_LINKR          EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_MDIO           EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_IDLE           EQU (0x1 <<  2) ;- (EMAC) 
// ---------EMAC_TSR：（EMAC偏移：0x14）传输状态寄存器--------
AT91C_EMAC_UBR            EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_COL            EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_RLES           EQU (0x1 <<  2) ;- (EMAC) 
AT91C_EMAC_TGO            EQU (0x1 <<  3) ;- (EMAC) Transmit Go
AT91C_EMAC_BEX            EQU (0x1 <<  4) ;- (EMAC) Buffers exhausted mid frame
AT91C_EMAC_COMP           EQU (0x1 <<  5) ;- (EMAC) 
AT91C_EMAC_UND            EQU (0x1 <<  6) ;- (EMAC) 
// ---------EMAC_RSR：（EMAC偏移量：0x20）接收状态寄存器--------
AT91C_EMAC_BNA            EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_REC            EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_OVR            EQU (0x1 <<  2) ;- (EMAC) 
// ---------EMAC_ISR：（EMAC偏移量：0x24）中断状态寄存器--------
AT91C_EMAC_MFD            EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_RCOMP          EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_RXUBR          EQU (0x1 <<  2) ;- (EMAC) 
AT91C_EMAC_TXUBR          EQU (0x1 <<  3) ;- (EMAC) 
AT91C_EMAC_TUNDR          EQU (0x1 <<  4) ;- (EMAC) 
AT91C_EMAC_RLEX           EQU (0x1 <<  5) ;- (EMAC) 
AT91C_EMAC_TXERR          EQU (0x1 <<  6) ;- (EMAC) 
AT91C_EMAC_TCOMP          EQU (0x1 <<  7) ;- (EMAC) 
AT91C_EMAC_LINK           EQU (0x1 <<  9) ;- (EMAC) 
AT91C_EMAC_ROVR           EQU (0x1 << 10) ;- (EMAC) 
AT91C_EMAC_HRESP          EQU (0x1 << 11) ;- (EMAC) 
AT91C_EMAC_PFRE           EQU (0x1 << 12) ;- (EMAC) 
AT91C_EMAC_PTZ            EQU (0x1 << 13) ;- (EMAC) 
// ---------EMAC_IER:（EMAC偏移量：0x28）中断启用寄存器--------
// ---------EMAC_IDR：（EMAC偏移：0x2c）中断禁用寄存器--------
// ---------EMAC_IMR：（EMAC偏移：0x30）中断掩码寄存器--------
// ---------EMAC_MAN：（EMAC偏移量：0x34）PHY维护寄存器--------
AT91C_EMAC_DATA           EQU (0xFFFF <<  0) ;- (EMAC) 
AT91C_EMAC_CODE           EQU (0x3 << 16) ;- (EMAC) 
AT91C_EMAC_REGA           EQU (0x1F << 18) ;- (EMAC) 
AT91C_EMAC_PHYA           EQU (0x1F << 23) ;- (EMAC) 
AT91C_EMAC_RW             EQU (0x3 << 28) ;- (EMAC) 
AT91C_EMAC_SOF            EQU (0x3 << 30) ;- (EMAC) 
// ---------EMAC_USRIO：（EMAC偏移：0xc0）用户输入输出寄存器--------
AT91C_EMAC_RMII           EQU (0x1 <<  0) ;- (EMAC) Reduce MII
AT91C_EMAC_CLKEN          EQU (0x1 <<  1) ;- (EMAC) Clock Enable
// ---------EMAC_WOL：（EMAC偏移：0xc4）LAN唤醒寄存器--------
AT91C_EMAC_IP             EQU (0xFFFF <<  0) ;- (EMAC) ARP request IP address
AT91C_EMAC_MAG            EQU (0x1 << 16) ;- (EMAC) Magic packet event enable
AT91C_EMAC_ARP            EQU (0x1 << 17) ;- (EMAC) ARP request event enable
AT91C_EMAC_SA1            EQU (0x1 << 18) ;- (EMAC) Specific address register 1 event enable
// ---------EMAC_REV：（EMAC偏移：0xfc）修订寄存器--------
AT91C_EMAC_REVREF         EQU (0xFFFF <<  0) ;- (EMAC) 
AT91C_EMAC_PARTREF        EQU (0xFFFF << 16) ;- (EMAC) 

// - *****************************************************************************
// -模数转换器的软件API定义
// - *****************************************************************************
// ---------ADC_CR:（ADC偏移：0x0）ADC控制寄存器--------
AT91C_ADC_SWRST           EQU (0x1 <<  0) ;- (ADC) Software Reset
AT91C_ADC_START           EQU (0x1 <<  1) ;- (ADC) Start Conversion
// ---------ADC_MR：（ADC偏移量：0x4）ADC模式寄存器--------
AT91C_ADC_TRGEN           EQU (0x1 <<  0) ;- (ADC) Trigger Enable
AT91C_ADC_TRGEN_DIS       EQU (0x0) ;- (ADC) Hradware triggers are disabled. Starting a conversion is only possible by software
AT91C_ADC_TRGEN_EN        EQU (0x1) ;- (ADC) Hardware trigger selected by TRGSEL field is enabled.
AT91C_ADC_TRGSEL          EQU (0x7 <<  1) ;- (ADC) Trigger Selection
AT91C_ADC_TRGSEL_TIOA0    EQU (0x0 <<  1) ;- (ADC) Selected TRGSEL = TIAO0
AT91C_ADC_TRGSEL_TIOA1    EQU (0x1 <<  1) ;- (ADC) Selected TRGSEL = TIAO1
AT91C_ADC_TRGSEL_TIOA2    EQU (0x2 <<  1) ;- (ADC) Selected TRGSEL = TIAO2
AT91C_ADC_TRGSEL_TIOA3    EQU (0x3 <<  1) ;- (ADC) Selected TRGSEL = TIAO3
AT91C_ADC_TRGSEL_TIOA4    EQU (0x4 <<  1) ;- (ADC) Selected TRGSEL = TIAO4
AT91C_ADC_TRGSEL_TIOA5    EQU (0x5 <<  1) ;- (ADC) Selected TRGSEL = TIAO5
AT91C_ADC_TRGSEL_EXT      EQU (0x6 <<  1) ;- (ADC) Selected TRGSEL = External Trigger
AT91C_ADC_LOWRES          EQU (0x1 <<  4) ;- (ADC) Resolution.
AT91C_ADC_LOWRES_10_BIT   EQU (0x0 <<  4) ;- (ADC) 10-bit resolution
AT91C_ADC_LOWRES_8_BIT    EQU (0x1 <<  4) ;- (ADC) 8-bit resolution
AT91C_ADC_SLEEP           EQU (0x1 <<  5) ;- (ADC) Sleep Mode
AT91C_ADC_SLEEP_NORMAL_MODE EQU (0x0 <<  5) ;- (ADC) Normal Mode
AT91C_ADC_SLEEP_MODE      EQU (0x1 <<  5) ;- (ADC) Sleep Mode
AT91C_ADC_PRESCAL         EQU (0x3F <<  8) ;- (ADC) Prescaler rate selection
AT91C_ADC_STARTUP         EQU (0x1F << 16) ;- (ADC) Startup Time
AT91C_ADC_SHTIM           EQU (0xF << 24) ;- (ADC) Sample & Hold Time
// ---------ADC_CHER：（ADC偏移：0x10）ADC通道启用寄存器--------
AT91C_ADC_CH0             EQU (0x1 <<  0) ;- (ADC) Channel 0
AT91C_ADC_CH1             EQU (0x1 <<  1) ;- (ADC) Channel 1
AT91C_ADC_CH2             EQU (0x1 <<  2) ;- (ADC) Channel 2
AT91C_ADC_CH3             EQU (0x1 <<  3) ;- (ADC) Channel 3
AT91C_ADC_CH4             EQU (0x1 <<  4) ;- (ADC) Channel 4
AT91C_ADC_CH5             EQU (0x1 <<  5) ;- (ADC) Channel 5
AT91C_ADC_CH6             EQU (0x1 <<  6) ;- (ADC) Channel 6
AT91C_ADC_CH7             EQU (0x1 <<  7) ;- (ADC) Channel 7
// ---------ADC_CHDR：（ADC偏移：0x14）ADC通道禁用寄存器--------
// ---------ADC_HSR：（ADC偏移：0x18）ADC通道状态寄存器--------
// ---------ADC_SR:（ADC偏移：0x1c）ADC状态寄存器--------
AT91C_ADC_EOC0            EQU (0x1 <<  0) ;- (ADC) End of Conversion
AT91C_ADC_EOC1            EQU (0x1 <<  1) ;- (ADC) End of Conversion
AT91C_ADC_EOC2            EQU (0x1 <<  2) ;- (ADC) End of Conversion
AT91C_ADC_EOC3            EQU (0x1 <<  3) ;- (ADC) End of Conversion
AT91C_ADC_EOC4            EQU (0x1 <<  4) ;- (ADC) End of Conversion
AT91C_ADC_EOC5            EQU (0x1 <<  5) ;- (ADC) End of Conversion
AT91C_ADC_EOC6            EQU (0x1 <<  6) ;- (ADC) End of Conversion
AT91C_ADC_EOC7            EQU (0x1 <<  7) ;- (ADC) End of Conversion
AT91C_ADC_OVRE0           EQU (0x1 <<  8) ;- (ADC) Overrun Error
AT91C_ADC_OVRE1           EQU (0x1 <<  9) ;- (ADC) Overrun Error
AT91C_ADC_OVRE2           EQU (0x1 << 10) ;- (ADC) Overrun Error
AT91C_ADC_OVRE3           EQU (0x1 << 11) ;- (ADC) Overrun Error
AT91C_ADC_OVRE4           EQU (0x1 << 12) ;- (ADC) Overrun Error
AT91C_ADC_OVRE5           EQU (0x1 << 13) ;- (ADC) Overrun Error
AT91C_ADC_OVRE6           EQU (0x1 << 14) ;- (ADC) Overrun Error
AT91C_ADC_OVRE7           EQU (0x1 << 15) ;- (ADC) Overrun Error
AT91C_ADC_DRDY            EQU (0x1 << 16) ;- (ADC) Data Ready
AT91C_ADC_GOVRE           EQU (0x1 << 17) ;- (ADC) General Overrun
AT91C_ADC_ENDRX           EQU (0x1 << 18) ;- (ADC) End of Receiver Transfer
AT91C_ADC_RXBUFF          EQU (0x1 << 19) ;- (ADC) RXBUFF Interrupt
// ---------ADC_LCD:（ADC偏移量：0x20）ADC上次转换的数据寄存器--------
AT91C_ADC_LDATA           EQU (0x3FF <<  0) ;- (ADC) Last Data Converted
// ---------ADC_IER:（ADC偏移量：0x24）ADC中断启用寄存器--------
// ---------ADC_IDR:（ADC偏移量：0x28）ADC中断禁用寄存器--------
// ---------ADC_IMR：（ADC偏移量：0x2c）ADC中断掩码寄存器--------
// ---------ADC_CDR0:（ADC偏移：0x30）ADC通道数据寄存器0--------
AT91C_ADC_DATA            EQU (0x3FF <<  0) ;- (ADC) Converted Data
// ---------ADC_CDR1:（ADC偏移：0x34）ADC通道数据寄存器1---------
// ---------ADC_CDR2:（ADC偏移量：0x38）ADC通道数据寄存器2---------
// ---------ADC_CDR3:（ADC偏移：0x3c）ADC通道数据寄存器3---------
// ---------ADC_CDR4：（ADC偏移量：0x40）ADC通道数据寄存器4---------
// ---------ADC_CDR5:（ADC偏移量：0x44）ADC通道数据寄存器5--------
// ---------ADC_CDR6：（ADC偏移量：0x48）ADC通道数据寄存器6---------
// ---------ADC_CDR7：（ADC偏移量：0x4c）ADC通道数据寄存器7--------

// - *****************************************************************************
// -               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256
// - *****************************************************************************
// -============SYS外围设备的寄存器定义============
// -============AIC外围设备的寄存器定义============
AT91C_AIC_IVR             EQU (0xFFFFF100) ;- (AIC) IRQ Vector Register
AT91C_AIC_SMR             EQU (0xFFFFF000) ;- (AIC) Source Mode Register
AT91C_AIC_FVR             EQU (0xFFFFF104) ;- (AIC) FIQ Vector Register
AT91C_AIC_DCR             EQU (0xFFFFF138) ;- (AIC) Debug Control Register (Protect)
AT91C_AIC_EOICR           EQU (0xFFFFF130) ;- (AIC) End of Interrupt Command Register
AT91C_AIC_SVR             EQU (0xFFFFF080) ;- (AIC) Source Vector Register
AT91C_AIC_FFSR            EQU (0xFFFFF148) ;- (AIC) Fast Forcing Status Register
AT91C_AIC_ICCR            EQU (0xFFFFF128) ;- (AIC) Interrupt Clear Command Register
AT91C_AIC_ISR             EQU (0xFFFFF108) ;- (AIC) Interrupt Status Register
AT91C_AIC_IMR             EQU (0xFFFFF110) ;- (AIC) Interrupt Mask Register
AT91C_AIC_IPR             EQU (0xFFFFF10C) ;- (AIC) Interrupt Pending Register
AT91C_AIC_FFER            EQU (0xFFFFF140) ;- (AIC) Fast Forcing Enable Register
AT91C_AIC_IECR            EQU (0xFFFFF120) ;- (AIC) Interrupt Enable Command Register
AT91C_AIC_ISCR            EQU (0xFFFFF12C) ;- (AIC) Interrupt Set Command Register
AT91C_AIC_FFDR            EQU (0xFFFFF144) ;- (AIC) Fast Forcing Disable Register
AT91C_AIC_CISR            EQU (0xFFFFF114) ;- (AIC) Core Interrupt Status Register
AT91C_AIC_IDCR            EQU (0xFFFFF124) ;- (AIC) Interrupt Disable Command Register
AT91C_AIC_SPU             EQU (0xFFFFF134) ;- (AIC) Spurious Vector Register
// -============PDC_DBGU外围设备的寄存器定义============
AT91C_DBGU_TCR            EQU (0xFFFFF30C) ;- (PDC_DBGU) Transmit Counter Register
AT91C_DBGU_RNPR           EQU (0xFFFFF310) ;- (PDC_DBGU) Receive Next Pointer Register
AT91C_DBGU_TNPR           EQU (0xFFFFF318) ;- (PDC_DBGU) Transmit Next Pointer Register
AT91C_DBGU_TPR            EQU (0xFFFFF308) ;- (PDC_DBGU) Transmit Pointer Register
AT91C_DBGU_RPR            EQU (0xFFFFF300) ;- (PDC_DBGU) Receive Pointer Register
AT91C_DBGU_RCR            EQU (0xFFFFF304) ;- (PDC_DBGU) Receive Counter Register
AT91C_DBGU_RNCR           EQU (0xFFFFF314) ;- (PDC_DBGU) Receive Next Counter Register
AT91C_DBGU_PTCR           EQU (0xFFFFF320) ;- (PDC_DBGU) PDC Transfer Control Register
AT91C_DBGU_PTSR           EQU (0xFFFFF324) ;- (PDC_DBGU) PDC Transfer Status Register
AT91C_DBGU_TNCR           EQU (0xFFFFF31C) ;- (PDC_DBGU) Transmit Next Counter Register
// -============DBGU外围设备的寄存器定义============
AT91C_DBGU_EXID           EQU (0xFFFFF244) ;- (DBGU) Chip ID Extension Register
AT91C_DBGU_BRGR           EQU (0xFFFFF220) ;- (DBGU) Baud Rate Generator Register
AT91C_DBGU_IDR            EQU (0xFFFFF20C) ;- (DBGU) Interrupt Disable Register
AT91C_DBGU_CSR            EQU (0xFFFFF214) ;- (DBGU) Channel Status Register
AT91C_DBGU_CIDR           EQU (0xFFFFF240) ;- (DBGU) Chip ID Register
AT91C_DBGU_MR             EQU (0xFFFFF204) ;- (DBGU) Mode Register
AT91C_DBGU_IMR            EQU (0xFFFFF210) ;- (DBGU) Interrupt Mask Register
AT91C_DBGU_CR             EQU (0xFFFFF200) ;- (DBGU) Control Register
AT91C_DBGU_FNTR           EQU (0xFFFFF248) ;- (DBGU) Force NTRST Register
AT91C_DBGU_THR            EQU (0xFFFFF21C) ;- (DBGU) Transmitter Holding Register
AT91C_DBGU_RHR            EQU (0xFFFFF218) ;- (DBGU) Receiver Holding Register
AT91C_DBGU_IER            EQU (0xFFFFF208) ;- (DBGU) Interrupt Enable Register
// -============PIOA外围设备的寄存器定义============
AT91C_PIOA_ODR            EQU (0xFFFFF414) ;- (PIOA) Output Disable Registerr
AT91C_PIOA_SODR           EQU (0xFFFFF430) ;- (PIOA) Set Output Data Register
AT91C_PIOA_ISR            EQU (0xFFFFF44C) ;- (PIOA) Interrupt Status Register
AT91C_PIOA_ABSR           EQU (0xFFFFF478) ;- (PIOA) AB Select Status Register
AT91C_PIOA_IER            EQU (0xFFFFF440) ;- (PIOA) Interrupt Enable Register
AT91C_PIOA_PPUDR          EQU (0xFFFFF460) ;- (PIOA) Pull-up Disable Register
AT91C_PIOA_IMR            EQU (0xFFFFF448) ;- (PIOA) Interrupt Mask Register
AT91C_PIOA_PER            EQU (0xFFFFF400) ;- (PIOA) PIO Enable Register
AT91C_PIOA_IFDR           EQU (0xFFFFF424) ;- (PIOA) Input Filter Disable Register
AT91C_PIOA_OWDR           EQU (0xFFFFF4A4) ;- (PIOA) Output Write Disable Register
AT91C_PIOA_MDSR           EQU (0xFFFFF458) ;- (PIOA) Multi-driver Status Register
AT91C_PIOA_IDR            EQU (0xFFFFF444) ;- (PIOA) Interrupt Disable Register
AT91C_PIOA_ODSR           EQU (0xFFFFF438) ;- (PIOA) Output Data Status Register
AT91C_PIOA_PPUSR          EQU (0xFFFFF468) ;- (PIOA) Pull-up Status Register
AT91C_PIOA_OWSR           EQU (0xFFFFF4A8) ;- (PIOA) Output Write Status Register
AT91C_PIOA_BSR            EQU (0xFFFFF474) ;- (PIOA) Select B Register
AT91C_PIOA_OWER           EQU (0xFFFFF4A0) ;- (PIOA) Output Write Enable Register
AT91C_PIOA_IFER           EQU (0xFFFFF420) ;- (PIOA) Input Filter Enable Register
AT91C_PIOA_PDSR           EQU (0xFFFFF43C) ;- (PIOA) Pin Data Status Register
AT91C_PIOA_PPUER          EQU (0xFFFFF464) ;- (PIOA) Pull-up Enable Register
AT91C_PIOA_OSR            EQU (0xFFFFF418) ;- (PIOA) Output Status Register
AT91C_PIOA_ASR            EQU (0xFFFFF470) ;- (PIOA) Select A Register
AT91C_PIOA_MDDR           EQU (0xFFFFF454) ;- (PIOA) Multi-driver Disable Register
AT91C_PIOA_CODR           EQU (0xFFFFF434) ;- (PIOA) Clear Output Data Register
AT91C_PIOA_MDER           EQU (0xFFFFF450) ;- (PIOA) Multi-driver Enable Register
AT91C_PIOA_PDR            EQU (0xFFFFF404) ;- (PIOA) PIO Disable Register
AT91C_PIOA_IFSR           EQU (0xFFFFF428) ;- (PIOA) Input Filter Status Register
AT91C_PIOA_OER            EQU (0xFFFFF410) ;- (PIOA) Output Enable Register
AT91C_PIOA_PSR            EQU (0xFFFFF408) ;- (PIOA) PIO Status Register
// -============PIOB外围设备的寄存器定义============
AT91C_PIOB_OWDR           EQU (0xFFFFF6A4) ;- (PIOB) Output Write Disable Register
AT91C_PIOB_MDER           EQU (0xFFFFF650) ;- (PIOB) Multi-driver Enable Register
AT91C_PIOB_PPUSR          EQU (0xFFFFF668) ;- (PIOB) Pull-up Status Register
AT91C_PIOB_IMR            EQU (0xFFFFF648) ;- (PIOB) Interrupt Mask Register
AT91C_PIOB_ASR            EQU (0xFFFFF670) ;- (PIOB) Select A Register
AT91C_PIOB_PPUDR          EQU (0xFFFFF660) ;- (PIOB) Pull-up Disable Register
AT91C_PIOB_PSR            EQU (0xFFFFF608) ;- (PIOB) PIO Status Register
AT91C_PIOB_IER            EQU (0xFFFFF640) ;- (PIOB) Interrupt Enable Register
AT91C_PIOB_CODR           EQU (0xFFFFF634) ;- (PIOB) Clear Output Data Register
AT91C_PIOB_OWER           EQU (0xFFFFF6A0) ;- (PIOB) Output Write Enable Register
AT91C_PIOB_ABSR           EQU (0xFFFFF678) ;- (PIOB) AB Select Status Register
AT91C_PIOB_IFDR           EQU (0xFFFFF624) ;- (PIOB) Input Filter Disable Register
AT91C_PIOB_PDSR           EQU (0xFFFFF63C) ;- (PIOB) Pin Data Status Register
AT91C_PIOB_IDR            EQU (0xFFFFF644) ;- (PIOB) Interrupt Disable Register
AT91C_PIOB_OWSR           EQU (0xFFFFF6A8) ;- (PIOB) Output Write Status Register
AT91C_PIOB_PDR            EQU (0xFFFFF604) ;- (PIOB) PIO Disable Register
AT91C_PIOB_ODR            EQU (0xFFFFF614) ;- (PIOB) Output Disable Registerr
AT91C_PIOB_IFSR           EQU (0xFFFFF628) ;- (PIOB) Input Filter Status Register
AT91C_PIOB_PPUER          EQU (0xFFFFF664) ;- (PIOB) Pull-up Enable Register
AT91C_PIOB_SODR           EQU (0xFFFFF630) ;- (PIOB) Set Output Data Register
AT91C_PIOB_ISR            EQU (0xFFFFF64C) ;- (PIOB) Interrupt Status Register
AT91C_PIOB_ODSR           EQU (0xFFFFF638) ;- (PIOB) Output Data Status Register
AT91C_PIOB_OSR            EQU (0xFFFFF618) ;- (PIOB) Output Status Register
AT91C_PIOB_MDSR           EQU (0xFFFFF658) ;- (PIOB) Multi-driver Status Register
AT91C_PIOB_IFER           EQU (0xFFFFF620) ;- (PIOB) Input Filter Enable Register
AT91C_PIOB_BSR            EQU (0xFFFFF674) ;- (PIOB) Select B Register
AT91C_PIOB_MDDR           EQU (0xFFFFF654) ;- (PIOB) Multi-driver Disable Register
AT91C_PIOB_OER            EQU (0xFFFFF610) ;- (PIOB) Output Enable Register
AT91C_PIOB_PER            EQU (0xFFFFF600) ;- (PIOB) PIO Enable Register
// -============CKGR外围设备的寄存器定义============
AT91C_CKGR_MOR            EQU (0xFFFFFC20) ;- (CKGR) Main Oscillator Register
AT91C_CKGR_PLLR           EQU (0xFFFFFC2C) ;- (CKGR) PLL Register
AT91C_CKGR_MCFR           EQU (0xFFFFFC24) ;- (CKGR) Main Clock  Frequency Register
// -===========PMC外围设备的寄存器定义===========
AT91C_PMC_IDR             EQU (0xFFFFFC64) ;- (PMC) Interrupt Disable Register
AT91C_PMC_MOR             EQU (0xFFFFFC20) ;- (PMC) Main Oscillator Register
AT91C_PMC_PLLR            EQU (0xFFFFFC2C) ;- (PMC) PLL Register
AT91C_PMC_PCER            EQU (0xFFFFFC10) ;- (PMC) Peripheral Clock Enable Register
AT91C_PMC_PCKR            EQU (0xFFFFFC40) ;- (PMC) Programmable Clock Register
AT91C_PMC_MCKR            EQU (0xFFFFFC30) ;- (PMC) Master Clock Register
AT91C_PMC_SCDR            EQU (0xFFFFFC04) ;- (PMC) System Clock Disable Register
AT91C_PMC_PCDR            EQU (0xFFFFFC14) ;- (PMC) Peripheral Clock Disable Register
AT91C_PMC_SCSR            EQU (0xFFFFFC08) ;- (PMC) System Clock Status Register
AT91C_PMC_PCSR            EQU (0xFFFFFC18) ;- (PMC) Peripheral Clock Status Register
AT91C_PMC_MCFR            EQU (0xFFFFFC24) ;- (PMC) Main Clock  Frequency Register
AT91C_PMC_SCER            EQU (0xFFFFFC00) ;- (PMC) System Clock Enable Register
AT91C_PMC_IMR             EQU (0xFFFFFC6C) ;- (PMC) Interrupt Mask Register
AT91C_PMC_IER             EQU (0xFFFFFC60) ;- (PMC) Interrupt Enable Register
AT91C_PMC_SR              EQU (0xFFFFFC68) ;- (PMC) Status Register
// -============RSTC外围设备的寄存器定义============
AT91C_RSTC_RCR            EQU (0xFFFFFD00) ;- (RSTC) Reset Control Register
AT91C_RSTC_RMR            EQU (0xFFFFFD08) ;- (RSTC) Reset Mode Register
AT91C_RSTC_RSR            EQU (0xFFFFFD04) ;- (RSTC) Reset Status Register
// -============RTTC外围设备的寄存器定义============
AT91C_RTTC_RTSR           EQU (0xFFFFFD2C) ;- (RTTC) Real-time Status Register
AT91C_RTTC_RTMR           EQU (0xFFFFFD20) ;- (RTTC) Real-time Mode Register
AT91C_RTTC_RTVR           EQU (0xFFFFFD28) ;- (RTTC) Real-time Value Register
AT91C_RTTC_RTAR           EQU (0xFFFFFD24) ;- (RTTC) Real-time Alarm Register
// -============PITC外围设备的寄存器定义============
AT91C_PITC_PIVR           EQU (0xFFFFFD38) ;- (PITC) Period Interval Value Register
AT91C_PITC_PISR           EQU (0xFFFFFD34) ;- (PITC) Period Interval Status Register
AT91C_PITC_PIIR           EQU (0xFFFFFD3C) ;- (PITC) Period Interval Image Register
AT91C_PITC_PIMR           EQU (0xFFFFFD30) ;- (PITC) Period Interval Mode Register
// -============WDTC外围设备的寄存器定义============
AT91C_WDTC_WDCR           EQU (0xFFFFFD40) ;- (WDTC) Watchdog Control Register
AT91C_WDTC_WDSR           EQU (0xFFFFFD48) ;- (WDTC) Watchdog Status Register
AT91C_WDTC_WDMR           EQU (0xFFFFFD44) ;- (WDTC) Watchdog Mode Register
// -============VREG外围设备的寄存器定义============
AT91C_VREG_MR             EQU (0xFFFFFD60) ;- (VREG) Voltage Regulator Mode Register
// -============MC外围设备的寄存器定义============
AT91C_MC_ASR              EQU (0xFFFFFF04) ;- (MC) MC Abort Status Register
AT91C_MC_RCR              EQU (0xFFFFFF00) ;- (MC) MC Remap Control Register
AT91C_MC_FCR              EQU (0xFFFFFF64) ;- (MC) MC Flash Command Register
AT91C_MC_AASR             EQU (0xFFFFFF08) ;- (MC) MC Abort Address Status Register
AT91C_MC_FSR              EQU (0xFFFFFF68) ;- (MC) MC Flash Status Register
AT91C_MC_FMR              EQU (0xFFFFFF60) ;- (MC) MC Flash Mode Register
// -============PDC_SPI1外围设备的寄存器定义============
AT91C_SPI1_PTCR           EQU (0xFFFE4120) ;- (PDC_SPI1) PDC Transfer Control Register
AT91C_SPI1_RPR            EQU (0xFFFE4100) ;- (PDC_SPI1) Receive Pointer Register
AT91C_SPI1_TNCR           EQU (0xFFFE411C) ;- (PDC_SPI1) Transmit Next Counter Register
AT91C_SPI1_TPR            EQU (0xFFFE4108) ;- (PDC_SPI1) Transmit Pointer Register
AT91C_SPI1_TNPR           EQU (0xFFFE4118) ;- (PDC_SPI1) Transmit Next Pointer Register
AT91C_SPI1_TCR            EQU (0xFFFE410C) ;- (PDC_SPI1) Transmit Counter Register
AT91C_SPI1_RCR            EQU (0xFFFE4104) ;- (PDC_SPI1) Receive Counter Register
AT91C_SPI1_RNPR           EQU (0xFFFE4110) ;- (PDC_SPI1) Receive Next Pointer Register
AT91C_SPI1_RNCR           EQU (0xFFFE4114) ;- (PDC_SPI1) Receive Next Counter Register
AT91C_SPI1_PTSR           EQU (0xFFFE4124) ;- (PDC_SPI1) PDC Transfer Status Register
// -============SPI1外围设备的寄存器定义============
AT91C_SPI1_IMR            EQU (0xFFFE401C) ;- (SPI1) Interrupt Mask Register
AT91C_SPI1_IER            EQU (0xFFFE4014) ;- (SPI1) Interrupt Enable Register
AT91C_SPI1_MR             EQU (0xFFFE4004) ;- (SPI1) Mode Register
AT91C_SPI1_RDR            EQU (0xFFFE4008) ;- (SPI1) Receive Data Register
AT91C_SPI1_IDR            EQU (0xFFFE4018) ;- (SPI1) Interrupt Disable Register
AT91C_SPI1_SR             EQU (0xFFFE4010) ;- (SPI1) Status Register
AT91C_SPI1_TDR            EQU (0xFFFE400C) ;- (SPI1) Transmit Data Register
AT91C_SPI1_CR             EQU (0xFFFE4000) ;- (SPI1) Control Register
AT91C_SPI1_CSR            EQU (0xFFFE4030) ;- (SPI1) Chip Select Register
// -============PDC_SPI0外围设备的寄存器定义============
AT91C_SPI0_PTCR           EQU (0xFFFE0120) ;- (PDC_SPI0) PDC Transfer Control Register
AT91C_SPI0_TPR            EQU (0xFFFE0108) ;- (PDC_SPI0) Transmit Pointer Register
AT91C_SPI0_TCR            EQU (0xFFFE010C) ;- (PDC_SPI0) Transmit Counter Register
AT91C_SPI0_RCR            EQU (0xFFFE0104) ;- (PDC_SPI0) Receive Counter Register
AT91C_SPI0_PTSR           EQU (0xFFFE0124) ;- (PDC_SPI0) PDC Transfer Status Register
AT91C_SPI0_RNPR           EQU (0xFFFE0110) ;- (PDC_SPI0) Receive Next Pointer Register
AT91C_SPI0_RPR            EQU (0xFFFE0100) ;- (PDC_SPI0) Receive Pointer Register
AT91C_SPI0_TNCR           EQU (0xFFFE011C) ;- (PDC_SPI0) Transmit Next Counter Register
AT91C_SPI0_RNCR           EQU (0xFFFE0114) ;- (PDC_SPI0) Receive Next Counter Register
AT91C_SPI0_TNPR           EQU (0xFFFE0118) ;- (PDC_SPI0) Transmit Next Pointer Register
// -============SPI0外围设备的寄存器定义============
AT91C_SPI0_IER            EQU (0xFFFE0014) ;- (SPI0) Interrupt Enable Register
AT91C_SPI0_SR             EQU (0xFFFE0010) ;- (SPI0) Status Register
AT91C_SPI0_IDR            EQU (0xFFFE0018) ;- (SPI0) Interrupt Disable Register
AT91C_SPI0_CR             EQU (0xFFFE0000) ;- (SPI0) Control Register
AT91C_SPI0_MR             EQU (0xFFFE0004) ;- (SPI0) Mode Register
AT91C_SPI0_IMR            EQU (0xFFFE001C) ;- (SPI0) Interrupt Mask Register
AT91C_SPI0_TDR            EQU (0xFFFE000C) ;- (SPI0) Transmit Data Register
AT91C_SPI0_RDR            EQU (0xFFFE0008) ;- (SPI0) Receive Data Register
AT91C_SPI0_CSR            EQU (0xFFFE0030) ;- (SPI0) Chip Select Register
// -============PDC_US1外围设备的寄存器定义============
AT91C_US1_RNCR            EQU (0xFFFC4114) ;- (PDC_US1) Receive Next Counter Register
AT91C_US1_PTCR            EQU (0xFFFC4120) ;- (PDC_US1) PDC Transfer Control Register
AT91C_US1_TCR             EQU (0xFFFC410C) ;- (PDC_US1) Transmit Counter Register
AT91C_US1_PTSR            EQU (0xFFFC4124) ;- (PDC_US1) PDC Transfer Status Register
AT91C_US1_TNPR            EQU (0xFFFC4118) ;- (PDC_US1) Transmit Next Pointer Register
AT91C_US1_RCR             EQU (0xFFFC4104) ;- (PDC_US1) Receive Counter Register
AT91C_US1_RNPR            EQU (0xFFFC4110) ;- (PDC_US1) Receive Next Pointer Register
AT91C_US1_RPR             EQU (0xFFFC4100) ;- (PDC_US1) Receive Pointer Register
AT91C_US1_TNCR            EQU (0xFFFC411C) ;- (PDC_US1) Transmit Next Counter Register
AT91C_US1_TPR             EQU (0xFFFC4108) ;- (PDC_US1) Transmit Pointer Register
// -============US1外围设备的寄存器定义============
AT91C_US1_IF              EQU (0xFFFC404C) ;- (US1) IRDA_FILTER Register
AT91C_US1_NER             EQU (0xFFFC4044) ;- (US1) Nb Errors Register
AT91C_US1_RTOR            EQU (0xFFFC4024) ;- (US1) Receiver Time-out Register
AT91C_US1_CSR             EQU (0xFFFC4014) ;- (US1) Channel Status Register
AT91C_US1_IDR             EQU (0xFFFC400C) ;- (US1) Interrupt Disable Register
AT91C_US1_IER             EQU (0xFFFC4008) ;- (US1) Interrupt Enable Register
AT91C_US1_THR             EQU (0xFFFC401C) ;- (US1) Transmitter Holding Register
AT91C_US1_TTGR            EQU (0xFFFC4028) ;- (US1) Transmitter Time-guard Register
AT91C_US1_RHR             EQU (0xFFFC4018) ;- (US1) Receiver Holding Register
AT91C_US1_BRGR            EQU (0xFFFC4020) ;- (US1) Baud Rate Generator Register
AT91C_US1_IMR             EQU (0xFFFC4010) ;- (US1) Interrupt Mask Register
AT91C_US1_FIDI            EQU (0xFFFC4040) ;- (US1) FI_DI_Ratio Register
AT91C_US1_CR              EQU (0xFFFC4000) ;- (US1) Control Register
AT91C_US1_MR              EQU (0xFFFC4004) ;- (US1) Mode Register
// -============PDC_US0外围设备的寄存器定义============
AT91C_US0_TNPR            EQU (0xFFFC0118) ;- (PDC_US0) Transmit Next Pointer Register
AT91C_US0_RNPR            EQU (0xFFFC0110) ;- (PDC_US0) Receive Next Pointer Register
AT91C_US0_TCR             EQU (0xFFFC010C) ;- (PDC_US0) Transmit Counter Register
AT91C_US0_PTCR            EQU (0xFFFC0120) ;- (PDC_US0) PDC Transfer Control Register
AT91C_US0_PTSR            EQU (0xFFFC0124) ;- (PDC_US0) PDC Transfer Status Register
AT91C_US0_TNCR            EQU (0xFFFC011C) ;- (PDC_US0) Transmit Next Counter Register
AT91C_US0_TPR             EQU (0xFFFC0108) ;- (PDC_US0) Transmit Pointer Register
AT91C_US0_RCR             EQU (0xFFFC0104) ;- (PDC_US0) Receive Counter Register
AT91C_US0_RPR             EQU (0xFFFC0100) ;- (PDC_US0) Receive Pointer Register
AT91C_US0_RNCR            EQU (0xFFFC0114) ;- (PDC_US0) Receive Next Counter Register
// -============US0外围设备的寄存器定义============
AT91C_US0_BRGR            EQU (0xFFFC0020) ;- (US0) Baud Rate Generator Register
AT91C_US0_NER             EQU (0xFFFC0044) ;- (US0) Nb Errors Register
AT91C_US0_CR              EQU (0xFFFC0000) ;- (US0) Control Register
AT91C_US0_IMR             EQU (0xFFFC0010) ;- (US0) Interrupt Mask Register
AT91C_US0_FIDI            EQU (0xFFFC0040) ;- (US0) FI_DI_Ratio Register
AT91C_US0_TTGR            EQU (0xFFFC0028) ;- (US0) Transmitter Time-guard Register
AT91C_US0_MR              EQU (0xFFFC0004) ;- (US0) Mode Register
AT91C_US0_RTOR            EQU (0xFFFC0024) ;- (US0) Receiver Time-out Register
AT91C_US0_CSR             EQU (0xFFFC0014) ;- (US0) Channel Status Register
AT91C_US0_RHR             EQU (0xFFFC0018) ;- (US0) Receiver Holding Register
AT91C_US0_IDR             EQU (0xFFFC000C) ;- (US0) Interrupt Disable Register
AT91C_US0_THR             EQU (0xFFFC001C) ;- (US0) Transmitter Holding Register
AT91C_US0_IF              EQU (0xFFFC004C) ;- (US0) IRDA_FILTER Register
AT91C_US0_IER             EQU (0xFFFC0008) ;- (US0) Interrupt Enable Register
// -============PDC_SSC外围设备的寄存器定义============
AT91C_SSC_TNCR            EQU (0xFFFD411C) ;- (PDC_SSC) Transmit Next Counter Register
AT91C_SSC_RPR             EQU (0xFFFD4100) ;- (PDC_SSC) Receive Pointer Register
AT91C_SSC_RNCR            EQU (0xFFFD4114) ;- (PDC_SSC) Receive Next Counter Register
AT91C_SSC_TPR             EQU (0xFFFD4108) ;- (PDC_SSC) Transmit Pointer Register
AT91C_SSC_PTCR            EQU (0xFFFD4120) ;- (PDC_SSC) PDC Transfer Control Register
AT91C_SSC_TCR             EQU (0xFFFD410C) ;- (PDC_SSC) Transmit Counter Register
AT91C_SSC_RCR             EQU (0xFFFD4104) ;- (PDC_SSC) Receive Counter Register
AT91C_SSC_RNPR            EQU (0xFFFD4110) ;- (PDC_SSC) Receive Next Pointer Register
AT91C_SSC_TNPR            EQU (0xFFFD4118) ;- (PDC_SSC) Transmit Next Pointer Register
AT91C_SSC_PTSR            EQU (0xFFFD4124) ;- (PDC_SSC) PDC Transfer Status Register
// -============SSC外围设备的寄存器定义============
AT91C_SSC_RHR             EQU (0xFFFD4020) ;- (SSC) Receive Holding Register
AT91C_SSC_RSHR            EQU (0xFFFD4030) ;- (SSC) Receive Sync Holding Register
AT91C_SSC_TFMR            EQU (0xFFFD401C) ;- (SSC) Transmit Frame Mode Register
AT91C_SSC_IDR             EQU (0xFFFD4048) ;- (SSC) Interrupt Disable Register
AT91C_SSC_THR             EQU (0xFFFD4024) ;- (SSC) Transmit Holding Register
AT91C_SSC_RCMR            EQU (0xFFFD4010) ;- (SSC) Receive Clock ModeRegister
AT91C_SSC_IER             EQU (0xFFFD4044) ;- (SSC) Interrupt Enable Register
AT91C_SSC_TSHR            EQU (0xFFFD4034) ;- (SSC) Transmit Sync Holding Register
AT91C_SSC_SR              EQU (0xFFFD4040) ;- (SSC) Status Register
AT91C_SSC_CMR             EQU (0xFFFD4004) ;- (SSC) Clock Mode Register
AT91C_SSC_TCMR            EQU (0xFFFD4018) ;- (SSC) Transmit Clock Mode Register
AT91C_SSC_CR              EQU (0xFFFD4000) ;- (SSC) Control Register
AT91C_SSC_IMR             EQU (0xFFFD404C) ;- (SSC) Interrupt Mask Register
AT91C_SSC_RFMR            EQU (0xFFFD4014) ;- (SSC) Receive Frame Mode Register
// -============TWI外围设备的寄存器定义============
AT91C_TWI_IER             EQU (0xFFFB8024) ;- (TWI) Interrupt Enable Register
AT91C_TWI_CR              EQU (0xFFFB8000) ;- (TWI) Control Register
AT91C_TWI_SR              EQU (0xFFFB8020) ;- (TWI) Status Register
AT91C_TWI_IMR             EQU (0xFFFB802C) ;- (TWI) Interrupt Mask Register
AT91C_TWI_THR             EQU (0xFFFB8034) ;- (TWI) Transmit Holding Register
AT91C_TWI_IDR             EQU (0xFFFB8028) ;- (TWI) Interrupt Disable Register
AT91C_TWI_IADR            EQU (0xFFFB800C) ;- (TWI) Internal Address Register
AT91C_TWI_MMR             EQU (0xFFFB8004) ;- (TWI) Master Mode Register
AT91C_TWI_CWGR            EQU (0xFFFB8010) ;- (TWI) Clock Waveform Generator Register
AT91C_TWI_RHR             EQU (0xFFFB8030) ;- (TWI) Receive Holding Register
// -============PWMC_CH3外围设备的寄存器定义============
AT91C_PWMC_CH3_CUPDR      EQU (0xFFFCC270) ;- (PWMC_CH3) Channel Update Register
AT91C_PWMC_CH3_Reserved   EQU (0xFFFCC274) ;- (PWMC_CH3) Reserved
AT91C_PWMC_CH3_CPRDR      EQU (0xFFFCC268) ;- (PWMC_CH3) Channel Period Register
AT91C_PWMC_CH3_CDTYR      EQU (0xFFFCC264) ;- (PWMC_CH3) Channel Duty Cycle Register
AT91C_PWMC_CH3_CCNTR      EQU (0xFFFCC26C) ;- (PWMC_CH3) Channel Counter Register
AT91C_PWMC_CH3_CMR        EQU (0xFFFCC260) ;- (PWMC_CH3) Channel Mode Register
// -============PWMC_CH2外围设备的寄存器定义============
AT91C_PWMC_CH2_Reserved   EQU (0xFFFCC254) ;- (PWMC_CH2) Reserved
AT91C_PWMC_CH2_CMR        EQU (0xFFFCC240) ;- (PWMC_CH2) Channel Mode Register
AT91C_PWMC_CH2_CCNTR      EQU (0xFFFCC24C) ;- (PWMC_CH2) Channel Counter Register
AT91C_PWMC_CH2_CPRDR      EQU (0xFFFCC248) ;- (PWMC_CH2) Channel Period Register
AT91C_PWMC_CH2_CUPDR      EQU (0xFFFCC250) ;- (PWMC_CH2) Channel Update Register
AT91C_PWMC_CH2_CDTYR      EQU (0xFFFCC244) ;- (PWMC_CH2) Channel Duty Cycle Register
// -============PWMC_CH1外围设备的寄存器定义============
AT91C_PWMC_CH1_Reserved   EQU (0xFFFCC234) ;- (PWMC_CH1) Reserved
AT91C_PWMC_CH1_CUPDR      EQU (0xFFFCC230) ;- (PWMC_CH1) Channel Update Register
AT91C_PWMC_CH1_CPRDR      EQU (0xFFFCC228) ;- (PWMC_CH1) Channel Period Register
AT91C_PWMC_CH1_CCNTR      EQU (0xFFFCC22C) ;- (PWMC_CH1) Channel Counter Register
AT91C_PWMC_CH1_CDTYR      EQU (0xFFFCC224) ;- (PWMC_CH1) Channel Duty Cycle Register
AT91C_PWMC_CH1_CMR        EQU (0xFFFCC220) ;- (PWMC_CH1) Channel Mode Register
// -============PWMC_CH0外围设备的寄存器定义============
AT91C_PWMC_CH0_Reserved   EQU (0xFFFCC214) ;- (PWMC_CH0) Reserved
AT91C_PWMC_CH0_CPRDR      EQU (0xFFFCC208) ;- (PWMC_CH0) Channel Period Register
AT91C_PWMC_CH0_CDTYR      EQU (0xFFFCC204) ;- (PWMC_CH0) Channel Duty Cycle Register
AT91C_PWMC_CH0_CMR        EQU (0xFFFCC200) ;- (PWMC_CH0) Channel Mode Register
AT91C_PWMC_CH0_CUPDR      EQU (0xFFFCC210) ;- (PWMC_CH0) Channel Update Register
AT91C_PWMC_CH0_CCNTR      EQU (0xFFFCC20C) ;- (PWMC_CH0) Channel Counter Register
// -============PWMC外围设备的寄存器定义============
AT91C_PWMC_IDR            EQU (0xFFFCC014) ;- (PWMC) PWMC Interrupt Disable Register
AT91C_PWMC_DIS            EQU (0xFFFCC008) ;- (PWMC) PWMC Disable Register
AT91C_PWMC_IER            EQU (0xFFFCC010) ;- (PWMC) PWMC Interrupt Enable Register
AT91C_PWMC_VR             EQU (0xFFFCC0FC) ;- (PWMC) PWMC Version Register
AT91C_PWMC_ISR            EQU (0xFFFCC01C) ;- (PWMC) PWMC Interrupt Status Register
AT91C_PWMC_SR             EQU (0xFFFCC00C) ;- (PWMC) PWMC Status Register
AT91C_PWMC_IMR            EQU (0xFFFCC018) ;- (PWMC) PWMC Interrupt Mask Register
AT91C_PWMC_MR             EQU (0xFFFCC000) ;- (PWMC) PWMC Mode Register
AT91C_PWMC_ENA            EQU (0xFFFCC004) ;- (PWMC) PWMC Enable Register
// -============UDP外围设备的寄存器定义============
AT91C_UDP_IMR             EQU (0xFFFB0018) ;- (UDP) Interrupt Mask Register
AT91C_UDP_FADDR           EQU (0xFFFB0008) ;- (UDP) Function Address Register
AT91C_UDP_NUM             EQU (0xFFFB0000) ;- (UDP) Frame Number Register
AT91C_UDP_FDR             EQU (0xFFFB0050) ;- (UDP) Endpoint FIFO Data Register
AT91C_UDP_ISR             EQU (0xFFFB001C) ;- (UDP) Interrupt Status Register
AT91C_UDP_CSR             EQU (0xFFFB0030) ;- (UDP) Endpoint Control and Status Register
AT91C_UDP_IDR             EQU (0xFFFB0014) ;- (UDP) Interrupt Disable Register
AT91C_UDP_ICR             EQU (0xFFFB0020) ;- (UDP) Interrupt Clear Register
AT91C_UDP_RSTEP           EQU (0xFFFB0028) ;- (UDP) Reset Endpoint Register
AT91C_UDP_TXVC            EQU (0xFFFB0074) ;- (UDP) Transceiver Control Register
AT91C_UDP_GLBSTATE        EQU (0xFFFB0004) ;- (UDP) Global State Register
AT91C_UDP_IER             EQU (0xFFFB0010) ;- (UDP) Interrupt Enable Register
// -============TC0外围设备的寄存器定义============
AT91C_TC0_SR              EQU (0xFFFA0020) ;- (TC0) Status Register
AT91C_TC0_RC              EQU (0xFFFA001C) ;- (TC0) Register C
AT91C_TC0_RB              EQU (0xFFFA0018) ;- (TC0) Register B
AT91C_TC0_CCR             EQU (0xFFFA0000) ;- (TC0) Channel Control Register
AT91C_TC0_CMR             EQU (0xFFFA0004) ;- (TC0) Channel Mode Register (Capture Mode / Waveform Mode)
AT91C_TC0_IER             EQU (0xFFFA0024) ;- (TC0) Interrupt Enable Register
AT91C_TC0_RA              EQU (0xFFFA0014) ;- (TC0) Register A
AT91C_TC0_IDR             EQU (0xFFFA0028) ;- (TC0) Interrupt Disable Register
AT91C_TC0_CV              EQU (0xFFFA0010) ;- (TC0) Counter Value
AT91C_TC0_IMR             EQU (0xFFFA002C) ;- (TC0) Interrupt Mask Register
// -==========TC1外围设备的寄存器定义==========
AT91C_TC1_RB              EQU (0xFFFA0058) ;- (TC1) Register B
AT91C_TC1_CCR             EQU (0xFFFA0040) ;- (TC1) Channel Control Register
AT91C_TC1_IER             EQU (0xFFFA0064) ;- (TC1) Interrupt Enable Register
AT91C_TC1_IDR             EQU (0xFFFA0068) ;- (TC1) Interrupt Disable Register
AT91C_TC1_SR              EQU (0xFFFA0060) ;- (TC1) Status Register
AT91C_TC1_CMR             EQU (0xFFFA0044) ;- (TC1) Channel Mode Register (Capture Mode / Waveform Mode)
AT91C_TC1_RA              EQU (0xFFFA0054) ;- (TC1) Register A
AT91C_TC1_RC              EQU (0xFFFA005C) ;- (TC1) Register C
AT91C_TC1_IMR             EQU (0xFFFA006C) ;- (TC1) Interrupt Mask Register
AT91C_TC1_CV              EQU (0xFFFA0050) ;- (TC1) Counter Value
// -============TC2外围设备的寄存器定义============
AT91C_TC2_CMR             EQU (0xFFFA0084) ;- (TC2) Channel Mode Register (Capture Mode / Waveform Mode)
AT91C_TC2_CCR             EQU (0xFFFA0080) ;- (TC2) Channel Control Register
AT91C_TC2_CV              EQU (0xFFFA0090) ;- (TC2) Counter Value
AT91C_TC2_RA              EQU (0xFFFA0094) ;- (TC2) Register A
AT91C_TC2_RB              EQU (0xFFFA0098) ;- (TC2) Register B
AT91C_TC2_IDR             EQU (0xFFFA00A8) ;- (TC2) Interrupt Disable Register
AT91C_TC2_IMR             EQU (0xFFFA00AC) ;- (TC2) Interrupt Mask Register
AT91C_TC2_RC              EQU (0xFFFA009C) ;- (TC2) Register C
AT91C_TC2_IER             EQU (0xFFFA00A4) ;- (TC2) Interrupt Enable Register
AT91C_TC2_SR              EQU (0xFFFA00A0) ;- (TC2) Status Register
// -==========TCB外围设备的寄存器定义==========
AT91C_TCB_BMR             EQU (0xFFFA00C4) ;- (TCB) TC Block Mode Register
AT91C_TCB_BCR             EQU (0xFFFA00C0) ;- (TCB) TC Block Control Register
// -============CAN_MB0外围设备的寄存器定义============
AT91C_CAN_MB0_MDL         EQU (0xFFFD0214) ;- (CAN_MB0) MailBox Data Low Register
AT91C_CAN_MB0_MAM         EQU (0xFFFD0204) ;- (CAN_MB0) MailBox Acceptance Mask Register
AT91C_CAN_MB0_MCR         EQU (0xFFFD021C) ;- (CAN_MB0) MailBox Control Register
AT91C_CAN_MB0_MID         EQU (0xFFFD0208) ;- (CAN_MB0) MailBox ID Register
AT91C_CAN_MB0_MSR         EQU (0xFFFD0210) ;- (CAN_MB0) MailBox Status Register
AT91C_CAN_MB0_MFID        EQU (0xFFFD020C) ;- (CAN_MB0) MailBox Family ID Register
AT91C_CAN_MB0_MDH         EQU (0xFFFD0218) ;- (CAN_MB0) MailBox Data High Register
AT91C_CAN_MB0_MMR         EQU (0xFFFD0200) ;- (CAN_MB0) MailBox Mode Register
// -============CAN_MB1外围设备的寄存器定义============
AT91C_CAN_MB1_MDL         EQU (0xFFFD0234) ;- (CAN_MB1) MailBox Data Low Register
AT91C_CAN_MB1_MID         EQU (0xFFFD0228) ;- (CAN_MB1) MailBox ID Register
AT91C_CAN_MB1_MMR         EQU (0xFFFD0220) ;- (CAN_MB1) MailBox Mode Register
AT91C_CAN_MB1_MSR         EQU (0xFFFD0230) ;- (CAN_MB1) MailBox Status Register
AT91C_CAN_MB1_MAM         EQU (0xFFFD0224) ;- (CAN_MB1) MailBox Acceptance Mask Register
AT91C_CAN_MB1_MDH         EQU (0xFFFD0238) ;- (CAN_MB1) MailBox Data High Register
AT91C_CAN_MB1_MCR         EQU (0xFFFD023C) ;- (CAN_MB1) MailBox Control Register
AT91C_CAN_MB1_MFID        EQU (0xFFFD022C) ;- (CAN_MB1) MailBox Family ID Register
// -============CAN_MB2外围设备的寄存器定义============
AT91C_CAN_MB2_MCR         EQU (0xFFFD025C) ;- (CAN_MB2) MailBox Control Register
AT91C_CAN_MB2_MDH         EQU (0xFFFD0258) ;- (CAN_MB2) MailBox Data High Register
AT91C_CAN_MB2_MID         EQU (0xFFFD0248) ;- (CAN_MB2) MailBox ID Register
AT91C_CAN_MB2_MDL         EQU (0xFFFD0254) ;- (CAN_MB2) MailBox Data Low Register
AT91C_CAN_MB2_MMR         EQU (0xFFFD0240) ;- (CAN_MB2) MailBox Mode Register
AT91C_CAN_MB2_MAM         EQU (0xFFFD0244) ;- (CAN_MB2) MailBox Acceptance Mask Register
AT91C_CAN_MB2_MFID        EQU (0xFFFD024C) ;- (CAN_MB2) MailBox Family ID Register
AT91C_CAN_MB2_MSR         EQU (0xFFFD0250) ;- (CAN_MB2) MailBox Status Register
// -============CAN_MB3外围设备的寄存器定义============
AT91C_CAN_MB3_MFID        EQU (0xFFFD026C) ;- (CAN_MB3) MailBox Family ID Register
AT91C_CAN_MB3_MAM         EQU (0xFFFD0264) ;- (CAN_MB3) MailBox Acceptance Mask Register
AT91C_CAN_MB3_MID         EQU (0xFFFD0268) ;- (CAN_MB3) MailBox ID Register
AT91C_CAN_MB3_MCR         EQU (0xFFFD027C) ;- (CAN_MB3) MailBox Control Register
AT91C_CAN_MB3_MMR         EQU (0xFFFD0260) ;- (CAN_MB3) MailBox Mode Register
AT91C_CAN_MB3_MSR         EQU (0xFFFD0270) ;- (CAN_MB3) MailBox Status Register
AT91C_CAN_MB3_MDL         EQU (0xFFFD0274) ;- (CAN_MB3) MailBox Data Low Register
AT91C_CAN_MB3_MDH         EQU (0xFFFD0278) ;- (CAN_MB3) MailBox Data High Register
// -============CAN_MB4外围设备的寄存器定义============
AT91C_CAN_MB4_MID         EQU (0xFFFD0288) ;- (CAN_MB4) MailBox ID Register
AT91C_CAN_MB4_MMR         EQU (0xFFFD0280) ;- (CAN_MB4) MailBox Mode Register
AT91C_CAN_MB4_MDH         EQU (0xFFFD0298) ;- (CAN_MB4) MailBox Data High Register
AT91C_CAN_MB4_MFID        EQU (0xFFFD028C) ;- (CAN_MB4) MailBox Family ID Register
AT91C_CAN_MB4_MSR         EQU (0xFFFD0290) ;- (CAN_MB4) MailBox Status Register
AT91C_CAN_MB4_MCR         EQU (0xFFFD029C) ;- (CAN_MB4) MailBox Control Register
AT91C_CAN_MB4_MDL         EQU (0xFFFD0294) ;- (CAN_MB4) MailBox Data Low Register
AT91C_CAN_MB4_MAM         EQU (0xFFFD0284) ;- (CAN_MB4) MailBox Acceptance Mask Register
// -============CAN_MB5外围设备的寄存器定义============
AT91C_CAN_MB5_MSR         EQU (0xFFFD02B0) ;- (CAN_MB5) MailBox Status Register
AT91C_CAN_MB5_MCR         EQU (0xFFFD02BC) ;- (CAN_MB5) MailBox Control Register
AT91C_CAN_MB5_MFID        EQU (0xFFFD02AC) ;- (CAN_MB5) MailBox Family ID Register
AT91C_CAN_MB5_MDH         EQU (0xFFFD02B8) ;- (CAN_MB5) MailBox Data High Register
AT91C_CAN_MB5_MID         EQU (0xFFFD02A8) ;- (CAN_MB5) MailBox ID Register
AT91C_CAN_MB5_MMR         EQU (0xFFFD02A0) ;- (CAN_MB5) MailBox Mode Register
AT91C_CAN_MB5_MDL         EQU (0xFFFD02B4) ;- (CAN_MB5) MailBox Data Low Register
AT91C_CAN_MB5_MAM         EQU (0xFFFD02A4) ;- (CAN_MB5) MailBox Acceptance Mask Register
// -============CAN_MB6外围设备的寄存器定义============
AT91C_CAN_MB6_MFID        EQU (0xFFFD02CC) ;- (CAN_MB6) MailBox Family ID Register
AT91C_CAN_MB6_MID         EQU (0xFFFD02C8) ;- (CAN_MB6) MailBox ID Register
AT91C_CAN_MB6_MAM         EQU (0xFFFD02C4) ;- (CAN_MB6) MailBox Acceptance Mask Register
AT91C_CAN_MB6_MSR         EQU (0xFFFD02D0) ;- (CAN_MB6) MailBox Status Register
AT91C_CAN_MB6_MDL         EQU (0xFFFD02D4) ;- (CAN_MB6) MailBox Data Low Register
AT91C_CAN_MB6_MCR         EQU (0xFFFD02DC) ;- (CAN_MB6) MailBox Control Register
AT91C_CAN_MB6_MDH         EQU (0xFFFD02D8) ;- (CAN_MB6) MailBox Data High Register
AT91C_CAN_MB6_MMR         EQU (0xFFFD02C0) ;- (CAN_MB6) MailBox Mode Register
// -============CAN_MB7外围设备的寄存器定义============
AT91C_CAN_MB7_MCR         EQU (0xFFFD02FC) ;- (CAN_MB7) MailBox Control Register
AT91C_CAN_MB7_MDH         EQU (0xFFFD02F8) ;- (CAN_MB7) MailBox Data High Register
AT91C_CAN_MB7_MFID        EQU (0xFFFD02EC) ;- (CAN_MB7) MailBox Family ID Register
AT91C_CAN_MB7_MDL         EQU (0xFFFD02F4) ;- (CAN_MB7) MailBox Data Low Register
AT91C_CAN_MB7_MID         EQU (0xFFFD02E8) ;- (CAN_MB7) MailBox ID Register
AT91C_CAN_MB7_MMR         EQU (0xFFFD02E0) ;- (CAN_MB7) MailBox Mode Register
AT91C_CAN_MB7_MAM         EQU (0xFFFD02E4) ;- (CAN_MB7) MailBox Acceptance Mask Register
AT91C_CAN_MB7_MSR         EQU (0xFFFD02F0) ;- (CAN_MB7) MailBox Status Register
// -============CAN外围设备的寄存器定义============
AT91C_CAN_TCR             EQU (0xFFFD0024) ;- (CAN) Transfer Command Register
AT91C_CAN_IMR             EQU (0xFFFD000C) ;- (CAN) Interrupt Mask Register
AT91C_CAN_IER             EQU (0xFFFD0004) ;- (CAN) Interrupt Enable Register
AT91C_CAN_ECR             EQU (0xFFFD0020) ;- (CAN) Error Counter Register
AT91C_CAN_TIMESTP         EQU (0xFFFD001C) ;- (CAN) Time Stamp Register
AT91C_CAN_MR              EQU (0xFFFD0000) ;- (CAN) Mode Register
AT91C_CAN_IDR             EQU (0xFFFD0008) ;- (CAN) Interrupt Disable Register
AT91C_CAN_ACR             EQU (0xFFFD0028) ;- (CAN) Abort Command Register
AT91C_CAN_TIM             EQU (0xFFFD0018) ;- (CAN) Timer Register
AT91C_CAN_SR              EQU (0xFFFD0010) ;- (CAN) Status Register
AT91C_CAN_BR              EQU (0xFFFD0014) ;- (CAN) Baudrate Register
AT91C_CAN_VR              EQU (0xFFFD00FC) ;- (CAN) Version Register
// -============EMAC外围设备的寄存器定义============
AT91C_EMAC_ISR            EQU (0xFFFDC024) ;- (EMAC) Interrupt Status Register
AT91C_EMAC_SA4H           EQU (0xFFFDC0B4) ;- (EMAC) Specific Address 4 Top, Last 2 bytes
AT91C_EMAC_SA1L           EQU (0xFFFDC098) ;- (EMAC) Specific Address 1 Bottom, First 4 bytes
AT91C_EMAC_ELE            EQU (0xFFFDC078) ;- (EMAC) Excessive Length Errors Register
AT91C_EMAC_LCOL           EQU (0xFFFDC05C) ;- (EMAC) Late Collision Register
AT91C_EMAC_RLE            EQU (0xFFFDC088) ;- (EMAC) Receive Length Field Mismatch Register
AT91C_EMAC_WOL            EQU (0xFFFDC0C4) ;- (EMAC) Wake On LAN Register
AT91C_EMAC_DTF            EQU (0xFFFDC058) ;- (EMAC) Deferred Transmission Frame Register
AT91C_EMAC_TUND           EQU (0xFFFDC064) ;- (EMAC) Transmit Underrun Error Register
AT91C_EMAC_NCR            EQU (0xFFFDC000) ;- (EMAC) Network Control Register
AT91C_EMAC_SA4L           EQU (0xFFFDC0B0) ;- (EMAC) Specific Address 4 Bottom, First 4 bytes
AT91C_EMAC_RSR            EQU (0xFFFDC020) ;- (EMAC) Receive Status Register
AT91C_EMAC_SA3L           EQU (0xFFFDC0A8) ;- (EMAC) Specific Address 3 Bottom, First 4 bytes
AT91C_EMAC_TSR            EQU (0xFFFDC014) ;- (EMAC) Transmit Status Register
AT91C_EMAC_IDR            EQU (0xFFFDC02C) ;- (EMAC) Interrupt Disable Register
AT91C_EMAC_RSE            EQU (0xFFFDC074) ;- (EMAC) Receive Symbol Errors Register
AT91C_EMAC_ECOL           EQU (0xFFFDC060) ;- (EMAC) Excessive Collision Register
AT91C_EMAC_TID            EQU (0xFFFDC0B8) ;- (EMAC) Type ID Checking Register
AT91C_EMAC_HRB            EQU (0xFFFDC090) ;- (EMAC) Hash Address Bottom[31:0]
AT91C_EMAC_TBQP           EQU (0xFFFDC01C) ;- (EMAC) Transmit Buffer Queue Pointer
AT91C_EMAC_USRIO          EQU (0xFFFDC0C0) ;- (EMAC) USER Input/Output Register
AT91C_EMAC_PTR            EQU (0xFFFDC038) ;- (EMAC) Pause Time Register
AT91C_EMAC_SA2H           EQU (0xFFFDC0A4) ;- (EMAC) Specific Address 2 Top, Last 2 bytes
AT91C_EMAC_ROV            EQU (0xFFFDC070) ;- (EMAC) Receive Overrun Errors Register
AT91C_EMAC_ALE            EQU (0xFFFDC054) ;- (EMAC) Alignment Error Register
AT91C_EMAC_RJA            EQU (0xFFFDC07C) ;- (EMAC) Receive Jabbers Register
AT91C_EMAC_RBQP           EQU (0xFFFDC018) ;- (EMAC) Receive Buffer Queue Pointer
AT91C_EMAC_TPF            EQU (0xFFFDC08C) ;- (EMAC) Transmitted Pause Frames Register
AT91C_EMAC_NCFGR          EQU (0xFFFDC004) ;- (EMAC) Network Configuration Register
AT91C_EMAC_HRT            EQU (0xFFFDC094) ;- (EMAC) Hash Address Top[63:32]
AT91C_EMAC_USF            EQU (0xFFFDC080) ;- (EMAC) Undersize Frames Register
AT91C_EMAC_FCSE           EQU (0xFFFDC050) ;- (EMAC) Frame Check Sequence Error Register
AT91C_EMAC_TPQ            EQU (0xFFFDC0BC) ;- (EMAC) Transmit Pause Quantum Register
AT91C_EMAC_MAN            EQU (0xFFFDC034) ;- (EMAC) PHY Maintenance Register
AT91C_EMAC_FTO            EQU (0xFFFDC040) ;- (EMAC) Frames Transmitted OK Register
AT91C_EMAC_REV            EQU (0xFFFDC0FC) ;- (EMAC) Revision Register
AT91C_EMAC_IMR            EQU (0xFFFDC030) ;- (EMAC) Interrupt Mask Register
AT91C_EMAC_SCF            EQU (0xFFFDC044) ;- (EMAC) Single Collision Frame Register
AT91C_EMAC_PFR            EQU (0xFFFDC03C) ;- (EMAC) Pause Frames received Register
AT91C_EMAC_MCF            EQU (0xFFFDC048) ;- (EMAC) Multiple Collision Frame Register
AT91C_EMAC_NSR            EQU (0xFFFDC008) ;- (EMAC) Network Status Register
AT91C_EMAC_SA2L           EQU (0xFFFDC0A0) ;- (EMAC) Specific Address 2 Bottom, First 4 bytes
AT91C_EMAC_FRO            EQU (0xFFFDC04C) ;- (EMAC) Frames Received OK Register
AT91C_EMAC_IER            EQU (0xFFFDC028) ;- (EMAC) Interrupt Enable Register
AT91C_EMAC_SA1H           EQU (0xFFFDC09C) ;- (EMAC) Specific Address 1 Top, Last 2 bytes
AT91C_EMAC_CSE            EQU (0xFFFDC068) ;- (EMAC) Carrier Sense Error Register
AT91C_EMAC_SA3H           EQU (0xFFFDC0AC) ;- (EMAC) Specific Address 3 Top, Last 2 bytes
AT91C_EMAC_RRE            EQU (0xFFFDC06C) ;- (EMAC) Receive Ressource Error Register
AT91C_EMAC_STE            EQU (0xFFFDC084) ;- (EMAC) SQE Test Error Register
// -============PDC_ADC外围设备的寄存器定义============
AT91C_ADC_PTSR            EQU (0xFFFD8124) ;- (PDC_ADC) PDC Transfer Status Register
AT91C_ADC_PTCR            EQU (0xFFFD8120) ;- (PDC_ADC) PDC Transfer Control Register
AT91C_ADC_TNPR            EQU (0xFFFD8118) ;- (PDC_ADC) Transmit Next Pointer Register
AT91C_ADC_TNCR            EQU (0xFFFD811C) ;- (PDC_ADC) Transmit Next Counter Register
AT91C_ADC_RNPR            EQU (0xFFFD8110) ;- (PDC_ADC) Receive Next Pointer Register
AT91C_ADC_RNCR            EQU (0xFFFD8114) ;- (PDC_ADC) Receive Next Counter Register
AT91C_ADC_RPR             EQU (0xFFFD8100) ;- (PDC_ADC) Receive Pointer Register
AT91C_ADC_TCR             EQU (0xFFFD810C) ;- (PDC_ADC) Transmit Counter Register
AT91C_ADC_TPR             EQU (0xFFFD8108) ;- (PDC_ADC) Transmit Pointer Register
AT91C_ADC_RCR             EQU (0xFFFD8104) ;- (PDC_ADC) Receive Counter Register
// -===========ADC外围设备的寄存器定义==========
AT91C_ADC_CDR2            EQU (0xFFFD8038) ;- (ADC) ADC Channel Data Register 2
AT91C_ADC_CDR3            EQU (0xFFFD803C) ;- (ADC) ADC Channel Data Register 3
AT91C_ADC_CDR0            EQU (0xFFFD8030) ;- (ADC) ADC Channel Data Register 0
AT91C_ADC_CDR5            EQU (0xFFFD8044) ;- (ADC) ADC Channel Data Register 5
AT91C_ADC_CHDR            EQU (0xFFFD8014) ;- (ADC) ADC Channel Disable Register
AT91C_ADC_SR              EQU (0xFFFD801C) ;- (ADC) ADC Status Register
AT91C_ADC_CDR4            EQU (0xFFFD8040) ;- (ADC) ADC Channel Data Register 4
AT91C_ADC_CDR1            EQU (0xFFFD8034) ;- (ADC) ADC Channel Data Register 1
AT91C_ADC_LCDR            EQU (0xFFFD8020) ;- (ADC) ADC Last Converted Data Register
AT91C_ADC_IDR             EQU (0xFFFD8028) ;- (ADC) ADC Interrupt Disable Register
AT91C_ADC_CR              EQU (0xFFFD8000) ;- (ADC) ADC Control Register
AT91C_ADC_CDR7            EQU (0xFFFD804C) ;- (ADC) ADC Channel Data Register 7
AT91C_ADC_CDR6            EQU (0xFFFD8048) ;- (ADC) ADC Channel Data Register 6
AT91C_ADC_IER             EQU (0xFFFD8024) ;- (ADC) ADC Interrupt Enable Register
AT91C_ADC_CHER            EQU (0xFFFD8010) ;- (ADC) ADC Channel Enable Register
AT91C_ADC_CHSR            EQU (0xFFFD8018) ;- (ADC) ADC Channel Status Register
AT91C_ADC_MR              EQU (0xFFFD8004) ;- (ADC) ADC Mode Register
AT91C_ADC_IMR             EQU (0xFFFD802C) ;- (ADC) ADC Interrupt Mask Register

// - *****************************************************************************
// -               PIO DEFINITIONS FOR AT91SAM7X256
// - *****************************************************************************
AT91C_PIO_PA0             EQU (1 <<  0) ;- Pin Controlled by PA0
AT91C_PA0_RXD0            EQU (AT91C_PIO_PA0) ;-  USART 0 Receive Data
AT91C_PIO_PA1             EQU (1 <<  1) ;- Pin Controlled by PA1
AT91C_PA1_TXD0            EQU (AT91C_PIO_PA1) ;-  USART 0 Transmit Data
AT91C_PIO_PA10            EQU (1 << 10) ;- Pin Controlled by PA10
AT91C_PA10_TWD            EQU (AT91C_PIO_PA10) ;-  TWI Two-wire Serial Data
AT91C_PIO_PA11            EQU (1 << 11) ;- Pin Controlled by PA11
AT91C_PA11_TWCK           EQU (AT91C_PIO_PA11) ;-  TWI Two-wire Serial Clock
AT91C_PIO_PA12            EQU (1 << 12) ;- Pin Controlled by PA12
AT91C_PA12_SPI0_NPCS0     EQU (AT91C_PIO_PA12) ;-  SPI 0 Peripheral Chip Select 0
AT91C_PIO_PA13            EQU (1 << 13) ;- Pin Controlled by PA13
AT91C_PA13_SPI0_NPCS1     EQU (AT91C_PIO_PA13) ;-  SPI 0 Peripheral Chip Select 1
AT91C_PA13_PCK1           EQU (AT91C_PIO_PA13) ;-  PMC Programmable Clock Output 1
AT91C_PIO_PA14            EQU (1 << 14) ;- Pin Controlled by PA14
AT91C_PA14_SPI0_NPCS2     EQU (AT91C_PIO_PA14) ;-  SPI 0 Peripheral Chip Select 2
AT91C_PA14_IRQ1           EQU (AT91C_PIO_PA14) ;-  External Interrupt 1
AT91C_PIO_PA15            EQU (1 << 15) ;- Pin Controlled by PA15
AT91C_PA15_SPI0_NPCS3     EQU (AT91C_PIO_PA15) ;-  SPI 0 Peripheral Chip Select 3
AT91C_PA15_TCLK2          EQU (AT91C_PIO_PA15) ;-  Timer Counter 2 external clock input
AT91C_PIO_PA16            EQU (1 << 16) ;- Pin Controlled by PA16
AT91C_PA16_SPI0_MISO      EQU (AT91C_PIO_PA16) ;-  SPI 0 Master In Slave
AT91C_PIO_PA17            EQU (1 << 17) ;- Pin Controlled by PA17
AT91C_PA17_SPI0_MOSI      EQU (AT91C_PIO_PA17) ;-  SPI 0 Master Out Slave
AT91C_PIO_PA18            EQU (1 << 18) ;- Pin Controlled by PA18
AT91C_PA18_SPI0_SPCK      EQU (AT91C_PIO_PA18) ;-  SPI 0 Serial Clock
AT91C_PIO_PA19            EQU (1 << 19) ;- Pin Controlled by PA19
AT91C_PA19_CANRX          EQU (AT91C_PIO_PA19) ;-  CAN Receive
AT91C_PIO_PA2             EQU (1 <<  2) ;- Pin Controlled by PA2
AT91C_PA2_SCK0            EQU (AT91C_PIO_PA2) ;-  USART 0 Serial Clock
AT91C_PA2_SPI1_NPCS1      EQU (AT91C_PIO_PA2) ;-  SPI 1 Peripheral Chip Select 1
AT91C_PIO_PA20            EQU (1 << 20) ;- Pin Controlled by PA20
AT91C_PA20_CANTX          EQU (AT91C_PIO_PA20) ;-  CAN Transmit
AT91C_PIO_PA21            EQU (1 << 21) ;- Pin Controlled by PA21
AT91C_PA21_TF             EQU (AT91C_PIO_PA21) ;-  SSC Transmit Frame Sync
AT91C_PA21_SPI1_NPCS0     EQU (AT91C_PIO_PA21) ;-  SPI 1 Peripheral Chip Select 0
AT91C_PIO_PA22            EQU (1 << 22) ;- Pin Controlled by PA22
AT91C_PA22_TK             EQU (AT91C_PIO_PA22) ;-  SSC Transmit Clock
AT91C_PA22_SPI1_SPCK      EQU (AT91C_PIO_PA22) ;-  SPI 1 Serial Clock
AT91C_PIO_PA23            EQU (1 << 23) ;- Pin Controlled by PA23
AT91C_PA23_TD             EQU (AT91C_PIO_PA23) ;-  SSC Transmit data
AT91C_PA23_SPI1_MOSI      EQU (AT91C_PIO_PA23) ;-  SPI 1 Master Out Slave
AT91C_PIO_PA24            EQU (1 << 24) ;- Pin Controlled by PA24
AT91C_PA24_RD             EQU (AT91C_PIO_PA24) ;-  SSC Receive Data
AT91C_PA24_SPI1_MISO      EQU (AT91C_PIO_PA24) ;-  SPI 1 Master In Slave
AT91C_PIO_PA25            EQU (1 << 25) ;- Pin Controlled by PA25
AT91C_PA25_RK             EQU (AT91C_PIO_PA25) ;-  SSC Receive Clock
AT91C_PA25_SPI1_NPCS1     EQU (AT91C_PIO_PA25) ;-  SPI 1 Peripheral Chip Select 1
AT91C_PIO_PA26            EQU (1 << 26) ;- Pin Controlled by PA26
AT91C_PA26_RF             EQU (AT91C_PIO_PA26) ;-  SSC Receive Frame Sync
AT91C_PA26_SPI1_NPCS2     EQU (AT91C_PIO_PA26) ;-  SPI 1 Peripheral Chip Select 2
AT91C_PIO_PA27            EQU (1 << 27) ;- Pin Controlled by PA27
AT91C_PA27_DRXD           EQU (AT91C_PIO_PA27) ;-  DBGU Debug Receive Data
AT91C_PA27_PCK3           EQU (AT91C_PIO_PA27) ;-  PMC Programmable Clock Output 3
AT91C_PIO_PA28            EQU (1 << 28) ;- Pin Controlled by PA28
AT91C_PA28_DTXD           EQU (AT91C_PIO_PA28) ;-  DBGU Debug Transmit Data
AT91C_PIO_PA29            EQU (1 << 29) ;- Pin Controlled by PA29
AT91C_PA29_FIQ            EQU (AT91C_PIO_PA29) ;-  AIC Fast Interrupt Input
AT91C_PA29_SPI1_NPCS3     EQU (AT91C_PIO_PA29) ;-  SPI 1 Peripheral Chip Select 3
AT91C_PIO_PA3             EQU (1 <<  3) ;- Pin Controlled by PA3
AT91C_PA3_RTS0            EQU (AT91C_PIO_PA3) ;-  USART 0 Ready To Send
AT91C_PA3_SPI1_NPCS2      EQU (AT91C_PIO_PA3) ;-  SPI 1 Peripheral Chip Select 2
AT91C_PIO_PA30            EQU (1 << 30) ;- Pin Controlled by PA30
AT91C_PA30_IRQ0           EQU (AT91C_PIO_PA30) ;-  External Interrupt 0
AT91C_PA30_PCK2           EQU (AT91C_PIO_PA30) ;-  PMC Programmable Clock Output 2
AT91C_PIO_PA4             EQU (1 <<  4) ;- Pin Controlled by PA4
AT91C_PA4_CTS0            EQU (AT91C_PIO_PA4) ;-  USART 0 Clear To Send
AT91C_PA4_SPI1_NPCS3      EQU (AT91C_PIO_PA4) ;-  SPI 1 Peripheral Chip Select 3
AT91C_PIO_PA5             EQU (1 <<  5) ;- Pin Controlled by PA5
AT91C_PA5_RXD1            EQU (AT91C_PIO_PA5) ;-  USART 1 Receive Data
AT91C_PIO_PA6             EQU (1 <<  6) ;- Pin Controlled by PA6
AT91C_PA6_TXD1            EQU (AT91C_PIO_PA6) ;-  USART 1 Transmit Data
AT91C_PIO_PA7             EQU (1 <<  7) ;- Pin Controlled by PA7
AT91C_PA7_SCK1            EQU (AT91C_PIO_PA7) ;-  USART 1 Serial Clock
AT91C_PA7_SPI0_NPCS1      EQU (AT91C_PIO_PA7) ;-  SPI 0 Peripheral Chip Select 1
AT91C_PIO_PA8             EQU (1 <<  8) ;- Pin Controlled by PA8
AT91C_PA8_RTS1            EQU (AT91C_PIO_PA8) ;-  USART 1 Ready To Send
AT91C_PA8_SPI0_NPCS2      EQU (AT91C_PIO_PA8) ;-  SPI 0 Peripheral Chip Select 2
AT91C_PIO_PA9             EQU (1 <<  9) ;- Pin Controlled by PA9
AT91C_PA9_CTS1            EQU (AT91C_PIO_PA9) ;-  USART 1 Clear To Send
AT91C_PA9_SPI0_NPCS3      EQU (AT91C_PIO_PA9) ;-  SPI 0 Peripheral Chip Select 3
AT91C_PIO_PB0             EQU (1 <<  0) ;- Pin Controlled by PB0
AT91C_PB0_ETXCK_EREFCK    EQU (AT91C_PIO_PB0) ;-  Ethernet MAC Transmit Clock/Reference Clock
AT91C_PB0_PCK0            EQU (AT91C_PIO_PB0) ;-  PMC Programmable Clock Output 0
AT91C_PIO_PB1             EQU (1 <<  1) ;- Pin Controlled by PB1
AT91C_PB1_ETXEN           EQU (AT91C_PIO_PB1) ;-  Ethernet MAC Transmit Enable
AT91C_PIO_PB10            EQU (1 << 10) ;- Pin Controlled by PB10
AT91C_PB10_ETX2           EQU (AT91C_PIO_PB10) ;-  Ethernet MAC Transmit Data 2
AT91C_PB10_SPI1_NPCS1     EQU (AT91C_PIO_PB10) ;-  SPI 1 Peripheral Chip Select 1
AT91C_PIO_PB11            EQU (1 << 11) ;- Pin Controlled by PB11
AT91C_PB11_ETX3           EQU (AT91C_PIO_PB11) ;-  Ethernet MAC Transmit Data 3
AT91C_PB11_SPI1_NPCS2     EQU (AT91C_PIO_PB11) ;-  SPI 1 Peripheral Chip Select 2
AT91C_PIO_PB12            EQU (1 << 12) ;- Pin Controlled by PB12
AT91C_PB12_ETXER          EQU (AT91C_PIO_PB12) ;-  Ethernet MAC Transmikt Coding Error
AT91C_PB12_TCLK0          EQU (AT91C_PIO_PB12) ;-  Timer Counter 0 external clock input
AT91C_PIO_PB13            EQU (1 << 13) ;- Pin Controlled by PB13
AT91C_PB13_ERX2           EQU (AT91C_PIO_PB13) ;-  Ethernet MAC Receive Data 2
AT91C_PB13_SPI0_NPCS1     EQU (AT91C_PIO_PB13) ;-  SPI 0 Peripheral Chip Select 1
AT91C_PIO_PB14            EQU (1 << 14) ;- Pin Controlled by PB14
AT91C_PB14_ERX3           EQU (AT91C_PIO_PB14) ;-  Ethernet MAC Receive Data 3
AT91C_PB14_SPI0_NPCS2     EQU (AT91C_PIO_PB14) ;-  SPI 0 Peripheral Chip Select 2
AT91C_PIO_PB15            EQU (1 << 15) ;- Pin Controlled by PB15
AT91C_PB15_ERXDV_ECRSDV   EQU (AT91C_PIO_PB15) ;-  Ethernet MAC Receive Data Valid
AT91C_PIO_PB16            EQU (1 << 16) ;- Pin Controlled by PB16
AT91C_PB16_ECOL           EQU (AT91C_PIO_PB16) ;-  Ethernet MAC Collision Detected
AT91C_PB16_SPI1_NPCS3     EQU (AT91C_PIO_PB16) ;-  SPI 1 Peripheral Chip Select 3
AT91C_PIO_PB17            EQU (1 << 17) ;- Pin Controlled by PB17
AT91C_PB17_ERXCK          EQU (AT91C_PIO_PB17) ;-  Ethernet MAC Receive Clock
AT91C_PB17_SPI0_NPCS3     EQU (AT91C_PIO_PB17) ;-  SPI 0 Peripheral Chip Select 3
AT91C_PIO_PB18            EQU (1 << 18) ;- Pin Controlled by PB18
AT91C_PB18_EF100          EQU (AT91C_PIO_PB18) ;-  Ethernet MAC Force 100 Mbits/sec
AT91C_PB18_ADTRG          EQU (AT91C_PIO_PB18) ;-  ADC External Trigger
AT91C_PIO_PB19            EQU (1 << 19) ;- Pin Controlled by PB19
AT91C_PB19_PWM0           EQU (AT91C_PIO_PB19) ;-  PWM Channel 0
AT91C_PB19_TCLK1          EQU (AT91C_PIO_PB19) ;-  Timer Counter 1 external clock input
AT91C_PIO_PB2             EQU (1 <<  2) ;- Pin Controlled by PB2
AT91C_PB2_ETX0            EQU (AT91C_PIO_PB2) ;-  Ethernet MAC Transmit Data 0
AT91C_PIO_PB20            EQU (1 << 20) ;- Pin Controlled by PB20
AT91C_PB20_PWM1           EQU (AT91C_PIO_PB20) ;-  PWM Channel 1
AT91C_PB20_PCK0           EQU (AT91C_PIO_PB20) ;-  PMC Programmable Clock Output 0
AT91C_PIO_PB21            EQU (1 << 21) ;- Pin Controlled by PB21
AT91C_PB21_PWM2           EQU (AT91C_PIO_PB21) ;-  PWM Channel 2
AT91C_PB21_PCK1           EQU (AT91C_PIO_PB21) ;-  PMC Programmable Clock Output 1
AT91C_PIO_PB22            EQU (1 << 22) ;- Pin Controlled by PB22
AT91C_PB22_PWM3           EQU (AT91C_PIO_PB22) ;-  PWM Channel 3
AT91C_PB22_PCK2           EQU (AT91C_PIO_PB22) ;-  PMC Programmable Clock Output 2
AT91C_PIO_PB23            EQU (1 << 23) ;- Pin Controlled by PB23
AT91C_PB23_TIOA0          EQU (AT91C_PIO_PB23) ;-  Timer Counter 0 Multipurpose Timer I/O Pin A
AT91C_PB23_DCD1           EQU (AT91C_PIO_PB23) ;-  USART 1 Data Carrier Detect
AT91C_PIO_PB24            EQU (1 << 24) ;- Pin Controlled by PB24
AT91C_PB24_TIOB0          EQU (AT91C_PIO_PB24) ;-  Timer Counter 0 Multipurpose Timer I/O Pin B
AT91C_PB24_DSR1           EQU (AT91C_PIO_PB24) ;-  USART 1 Data Set ready
AT91C_PIO_PB25            EQU (1 << 25) ;- Pin Controlled by PB25
AT91C_PB25_TIOA1          EQU (AT91C_PIO_PB25) ;-  Timer Counter 1 Multipurpose Timer I/O Pin A
AT91C_PB25_DTR1           EQU (AT91C_PIO_PB25) ;-  USART 1 Data Terminal ready
AT91C_PIO_PB26            EQU (1 << 26) ;- Pin Controlled by PB26
AT91C_PB26_TIOB1          EQU (AT91C_PIO_PB26) ;-  Timer Counter 1 Multipurpose Timer I/O Pin B
AT91C_PB26_RI1            EQU (AT91C_PIO_PB26) ;-  USART 1 Ring Indicator
AT91C_PIO_PB27            EQU (1 << 27) ;- Pin Controlled by PB27
AT91C_PB27_TIOA2          EQU (AT91C_PIO_PB27) ;-  Timer Counter 2 Multipurpose Timer I/O Pin A
AT91C_PB27_PWM0           EQU (AT91C_PIO_PB27) ;-  PWM Channel 0
AT91C_PIO_PB28            EQU (1 << 28) ;- Pin Controlled by PB28
AT91C_PB28_TIOB2          EQU (AT91C_PIO_PB28) ;-  Timer Counter 2 Multipurpose Timer I/O Pin B
AT91C_PB28_PWM1           EQU (AT91C_PIO_PB28) ;-  PWM Channel 1
AT91C_PIO_PB29            EQU (1 << 29) ;- Pin Controlled by PB29
AT91C_PB29_PCK1           EQU (AT91C_PIO_PB29) ;-  PMC Programmable Clock Output 1
AT91C_PB29_PWM2           EQU (AT91C_PIO_PB29) ;-  PWM Channel 2
AT91C_PIO_PB3             EQU (1 <<  3) ;- Pin Controlled by PB3
AT91C_PB3_ETX1            EQU (AT91C_PIO_PB3) ;-  Ethernet MAC Transmit Data 1
AT91C_PIO_PB30            EQU (1 << 30) ;- Pin Controlled by PB30
AT91C_PB30_PCK2           EQU (AT91C_PIO_PB30) ;-  PMC Programmable Clock Output 2
AT91C_PB30_PWM3           EQU (AT91C_PIO_PB30) ;-  PWM Channel 3
AT91C_PIO_PB4             EQU (1 <<  4) ;- Pin Controlled by PB4
AT91C_PB4_ECRS            EQU (AT91C_PIO_PB4) ;-  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid
AT91C_PIO_PB5             EQU (1 <<  5) ;- Pin Controlled by PB5
AT91C_PB5_ERX0            EQU (AT91C_PIO_PB5) ;-  Ethernet MAC Receive Data 0
AT91C_PIO_PB6             EQU (1 <<  6) ;- Pin Controlled by PB6
AT91C_PB6_ERX1            EQU (AT91C_PIO_PB6) ;-  Ethernet MAC Receive Data 1
AT91C_PIO_PB7             EQU (1 <<  7) ;- Pin Controlled by PB7
AT91C_PB7_ERXER           EQU (AT91C_PIO_PB7) ;-  Ethernet MAC Receive Error
AT91C_PIO_PB8             EQU (1 <<  8) ;- Pin Controlled by PB8
AT91C_PB8_EMDC            EQU (AT91C_PIO_PB8) ;-  Ethernet MAC Management Data Clock
AT91C_PIO_PB9             EQU (1 <<  9) ;- Pin Controlled by PB9
AT91C_PB9_EMDIO           EQU (AT91C_PIO_PB9) ;-  Ethernet MAC Management Data Input/Output

// - *****************************************************************************
// -               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256
// - *****************************************************************************
AT91C_ID_FIQ              EQU ( 0) ;- Advanced Interrupt Controller (FIQ)
AT91C_ID_SYS              EQU ( 1) ;- System Peripheral
AT91C_ID_PIOA             EQU ( 2) ;- Parallel IO Controller A
AT91C_ID_PIOB             EQU ( 3) ;- Parallel IO Controller B
AT91C_ID_SPI0             EQU ( 4) ;- Serial Peripheral Interface 0
AT91C_ID_SPI1             EQU ( 5) ;- Serial Peripheral Interface 1
AT91C_ID_US0              EQU ( 6) ;- USART 0
AT91C_ID_US1              EQU ( 7) ;- USART 1
AT91C_ID_SSC              EQU ( 8) ;- Serial Synchronous Controller
AT91C_ID_TWI              EQU ( 9) ;- Two-Wire Interface
AT91C_ID_PWMC             EQU (10) ;- PWM Controller
AT91C_ID_UDP              EQU (11) ;- USB Device Port
AT91C_ID_TC0              EQU (12) ;- Timer Counter 0
AT91C_ID_TC1              EQU (13) ;- Timer Counter 1
AT91C_ID_TC2              EQU (14) ;- Timer Counter 2
AT91C_ID_CAN              EQU (15) ;- Control Area Network Controller
AT91C_ID_EMAC             EQU (16) ;- Ethernet MAC
AT91C_ID_ADC              EQU (17) ;- Analog-to-Digital Converter
AT91C_ID_18_Reserved      EQU (18) ;- Reserved
AT91C_ID_19_Reserved      EQU (19) ;- Reserved
AT91C_ID_20_Reserved      EQU (20) ;- Reserved
AT91C_ID_21_Reserved      EQU (21) ;- Reserved
AT91C_ID_22_Reserved      EQU (22) ;- Reserved
AT91C_ID_23_Reserved      EQU (23) ;- Reserved
AT91C_ID_24_Reserved      EQU (24) ;- Reserved
AT91C_ID_25_Reserved      EQU (25) ;- Reserved
AT91C_ID_26_Reserved      EQU (26) ;- Reserved
AT91C_ID_27_Reserved      EQU (27) ;- Reserved
AT91C_ID_28_Reserved      EQU (28) ;- Reserved
AT91C_ID_29_Reserved      EQU (29) ;- Reserved
AT91C_ID_IRQ0             EQU (30) ;- Advanced Interrupt Controller (IRQ0)
AT91C_ID_IRQ1             EQU (31) ;- Advanced Interrupt Controller (IRQ1)
AT91C_ALL_INT             EQU (0xC003FFFF) ;- ALL VALID INTERRUPTS

// - *****************************************************************************
// -               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256
// - *****************************************************************************
AT91C_BASE_SYS            EQU (0xFFFFF000) ;- (SYS) Base Address
AT91C_BASE_AIC            EQU (0xFFFFF000) ;- (AIC) Base Address
AT91C_BASE_PDC_DBGU       EQU (0xFFFFF300) ;- (PDC_DBGU) Base Address
AT91C_BASE_DBGU           EQU (0xFFFFF200) ;- (DBGU) Base Address
AT91C_BASE_PIOA           EQU (0xFFFFF400) ;- (PIOA) Base Address
AT91C_BASE_PIOB           EQU (0xFFFFF600) ;- (PIOB) Base Address
AT91C_BASE_CKGR           EQU (0xFFFFFC20) ;- (CKGR) Base Address
AT91C_BASE_PMC            EQU (0xFFFFFC00) ;- (PMC) Base Address
AT91C_BASE_RSTC           EQU (0xFFFFFD00) ;- (RSTC) Base Address
AT91C_BASE_RTTC           EQU (0xFFFFFD20) ;- (RTTC) Base Address
AT91C_BASE_PITC           EQU (0xFFFFFD30) ;- (PITC) Base Address
AT91C_BASE_WDTC           EQU (0xFFFFFD40) ;- (WDTC) Base Address
AT91C_BASE_VREG           EQU (0xFFFFFD60) ;- (VREG) Base Address
AT91C_BASE_MC             EQU (0xFFFFFF00) ;- (MC) Base Address
AT91C_BASE_PDC_SPI1       EQU (0xFFFE4100) ;- (PDC_SPI1) Base Address
AT91C_BASE_SPI1           EQU (0xFFFE4000) ;- (SPI1) Base Address
AT91C_BASE_PDC_SPI0       EQU (0xFFFE0100) ;- (PDC_SPI0) Base Address
AT91C_BASE_SPI0           EQU (0xFFFE0000) ;- (SPI0) Base Address
AT91C_BASE_PDC_US1        EQU (0xFFFC4100) ;- (PDC_US1) Base Address
AT91C_BASE_US1            EQU (0xFFFC4000) ;- (US1) Base Address
AT91C_BASE_PDC_US0        EQU (0xFFFC0100) ;- (PDC_US0) Base Address
AT91C_BASE_US0            EQU (0xFFFC0000) ;- (US0) Base Address
AT91C_BASE_PDC_SSC        EQU (0xFFFD4100) ;- (PDC_SSC) Base Address
AT91C_BASE_SSC            EQU (0xFFFD4000) ;- (SSC) Base Address
AT91C_BASE_TWI            EQU (0xFFFB8000) ;- (TWI) Base Address
AT91C_BASE_PWMC_CH3       EQU (0xFFFCC260) ;- (PWMC_CH3) Base Address
AT91C_BASE_PWMC_CH2       EQU (0xFFFCC240) ;- (PWMC_CH2) Base Address
AT91C_BASE_PWMC_CH1       EQU (0xFFFCC220) ;- (PWMC_CH1) Base Address
AT91C_BASE_PWMC_CH0       EQU (0xFFFCC200) ;- (PWMC_CH0) Base Address
AT91C_BASE_PWMC           EQU (0xFFFCC000) ;- (PWMC) Base Address
AT91C_BASE_UDP            EQU (0xFFFB0000) ;- (UDP) Base Address
AT91C_BASE_TC0            EQU (0xFFFA0000) ;- (TC0) Base Address
AT91C_BASE_TC1            EQU (0xFFFA0040) ;- (TC1) Base Address
AT91C_BASE_TC2            EQU (0xFFFA0080) ;- (TC2) Base Address
AT91C_BASE_TCB            EQU (0xFFFA0000) ;- (TCB) Base Address
AT91C_BASE_CAN_MB0        EQU (0xFFFD0200) ;- (CAN_MB0) Base Address
AT91C_BASE_CAN_MB1        EQU (0xFFFD0220) ;- (CAN_MB1) Base Address
AT91C_BASE_CAN_MB2        EQU (0xFFFD0240) ;- (CAN_MB2) Base Address
AT91C_BASE_CAN_MB3        EQU (0xFFFD0260) ;- (CAN_MB3) Base Address
AT91C_BASE_CAN_MB4        EQU (0xFFFD0280) ;- (CAN_MB4) Base Address
AT91C_BASE_CAN_MB5        EQU (0xFFFD02A0) ;- (CAN_MB5) Base Address
AT91C_BASE_CAN_MB6        EQU (0xFFFD02C0) ;- (CAN_MB6) Base Address
AT91C_BASE_CAN_MB7        EQU (0xFFFD02E0) ;- (CAN_MB7) Base Address
AT91C_BASE_CAN            EQU (0xFFFD0000) ;- (CAN) Base Address
AT91C_BASE_EMAC           EQU (0xFFFDC000) ;- (EMAC) Base Address
AT91C_BASE_PDC_ADC        EQU (0xFFFD8100) ;- (PDC_ADC) Base Address
AT91C_BASE_ADC            EQU (0xFFFD8000) ;- (ADC) Base Address

// - *****************************************************************************
// -               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256
// - *****************************************************************************
// - ISRAM
AT91C_ISRAM               EQU (0x00200000) ;- Internal SRAM base address
AT91C_ISRAM_SIZE          EQU (0x00010000) ;- Internal SRAM size in byte (64 Kbytes)
// - IFLASH
AT91C_IFLASH              EQU (0x00100000) ;- Internal FLASH base address
AT91C_IFLASH_SIZE         EQU (0x00040000) ;- Internal FLASH size in byte (256 Kbytes)
AT91C_IFLASH_PAGE_SIZE    EQU (256) ;- Internal FLASH Page Size: 256 bytes
AT91C_IFLASH_LOCK_REGION_SIZE EQU (16384) ;- Internal FLASH Lock Region Size: 16 Kbytes
AT91C_IFLASH_NB_OF_PAGES  EQU (1024) ;- Internal FLASH Number of Pages: 1024 bytes
AT91C_IFLASH_NB_OF_LOCK_BITS EQU (16) ;- Internal FLASH Number of Lock Bits: 16 bytes
#endif /* __IAR_SYSTEMS_ASM__ */


#endif /* AT91SAM7X256_H */

