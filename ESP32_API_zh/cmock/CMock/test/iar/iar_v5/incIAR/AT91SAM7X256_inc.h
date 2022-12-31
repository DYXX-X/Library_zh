//  ----------------------------------------------------------------------------
//          ATMEL微控制器软件支持-ROUSSET-
//  ----------------------------------------------------------------------------
//  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
//  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  ----------------------------------------------------------------------------
// 文件名：AT91SAM7X256.h
// 对象：AT91SAM7X256定义
// 生成：AT91 SW应用程序组01/16/2006（16:36:22）
// 
// CVS参考：/AT91SAM7X256.pl/15/星期三11月2日13:56:49 2005//
// CVS参考：/SYS_SAM7X.pl/1.3/2005年2月1日星期二17:01:43//
// CVS参考：/MC_SAM7X.pl/12/2005年5月20日星期五14:13:04//
// CVS参考：/PMC_SAM7X.pl/1.4/2005年2月8日星期二13:58:10//
// CVS参考：/RSTC_SAM7X.pl/12/2005年7月13日星期三14:57:50//
// CVS参考：/UDP_SAM7X.pl/11/2005年5月10日星期二11:35:35//
// CVS参考：/PWM_SAM7X.pl/11/2005年5月10日星期二11:53:07//
// CVS参考：/AIC_6075B.pl/1.3/2005年5月20日星期五14:01:30//
// CVS参考号：/PIO-6057A.pl/1.2/2005年2月3日星期四10:18:28//
// CVS参考：/RTTC_6081A.pl/12/2004年11月9日星期二14:43:58//
// CVS参考号：/PIC_6079A.pl/12/2004年11月9日星期二14:43:56//
// CVS参考：/WDTC_6080A.pl/1.3/2004年11月9日星期二14:44:00//
// CVS参考：/VREG_6085B.pl/1.1/2005年2月1日星期二16:05:48//
// CVS参考：/PDC_6074C.pl/12/2005年2月3日星期四08:48:54//
// CVS参考：/DBGU_6059D.pl/1.1/2005年1月31日星期一13:15:32//
// CVS参考号：/SPI_6088D.pl/1.3/2005年5月20日星期五14:08:59//
// CVS参考：/US_6089C.pl/11/Mon Jul 12 18:23:26 2004//
// CVS参考：/SSC_6078B.pl/1.1/2005年7月13日星期三15:19:19//
// CVS参考号：/TTWI_6061A.pl/1/11/2004年7月13日星期二07:38:06//
// CVS参考：/TC_6082A.pl/1.7/2005年3月11日星期五12:52:17//
// CVS参考号：/CAN_6019B.pl/11/2005年3月8日星期二12:42:22//
// CVS参考：/EMACB_6119A.pl/1.6/2005年7月13日星期三15:05:35//
// CVS参考号：/AADC_6051C.pl/11/10月17日星期五09:12:38 2003//
//  ----------------------------------------------------------------------------

// 硬件寄存器定义

// *****************************************************************************
//              系统外围设备的软件API定义
// *****************************************************************************

// *****************************************************************************
//              高级中断控制器的软件API定义
// *****************************************************************************
// ***AT91S_AIC结构中的寄存器偏移***
#define AIC_SMR         ( 0) // 源模式寄存器
#define AIC_SVR         (128) // 源向量寄存器
#define AIC_IVR         (256) // IRQ矢量寄存器
#define AIC_FVR         (260) // FIQ矢量寄存器
#define AIC_ISR         (264) // 中断状态寄存器
#define AIC_IPR         (268) // 中断挂起寄存器
#define AIC_IMR         (272) // 中断掩码寄存器
#define AIC_CISR        (276) // 核心中断状态寄存器
#define AIC_IECR        (288) // 中断启用命令寄存器
#define AIC_IDCR        (292) // 中断禁用命令寄存器
#define AIC_ICCR        (296) // 中断清除命令寄存器
#define AIC_ISCR        (300) // 中断设置命令寄存器
#define AIC_EOICR       (304) // 中断命令寄存器结束
#define AIC_SPU         (308) // 虚假向量寄存器
#define AIC_DCR         (312) // 调试控制寄存器（保护）
#define AIC_FFER        (320) // 快速强制启用寄存器
#define AIC_FFDR        (324) // 快速强制禁用寄存器
#define AIC_FFSR        (328) // 快速强制状态寄存器
// --------AIC_SMR：（AIC偏移：0x0）控制寄存器--------
#define AT91C_AIC_PRIOR           (0x7 <<  0) // （AIC）优先级
#define 	AT91C_AIC_PRIOR_LOWEST               (0x0) // （AIC）最低优先级
#define 	AT91C_AIC_PRIOR_HIGHEST              (0x7) // （AIC）最高优先级
#define AT91C_AIC_SRCTYPE         (0x3 <<  5) // （AIC）中断源类型
#define 	AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL        (0x0 <<  5) // （AIC）外部源代码标签低级别敏感
#define 	AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL       (0x0 <<  5) // （AIC）内部源代码标签高度敏感
#define 	AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE    (0x1 <<  5) // （AIC）内部源代码标签正边缘触发
#define 	AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE    (0x1 <<  5) // （AIC）外部源代码标签负边缘触发
#define 	AT91C_AIC_SRCTYPE_HIGH_LEVEL           (0x2 <<  5) // （AIC）内部或外部源代码标签高级别敏感
#define 	AT91C_AIC_SRCTYPE_POSITIVE_EDGE        (0x3 <<  5) // （AIC）内部或外部源代码标签正边缘触发
// --------AIC_CISR：（AIC偏移：0x114）AIC核心中断状态寄存器--------
#define AT91C_AIC_NFIQ            (0x1 <<  0) // （AIC）NFIQ状态
#define AT91C_AIC_NIRQ            (0x1 <<  1) // （AIC）NIRQ状态
// --------AIC_DCR：（AIC偏移：0x138）AIC调试控制寄存器（保护）--------
#define AT91C_AIC_DCR_PROT        (0x1 <<  0) // （AIC）保护模式
#define AT91C_AIC_DCR_GMSK        (0x1 <<  1) // （AIC）通用掩码

// *****************************************************************************
//              外设DMA控制器的软件API定义
// *****************************************************************************
// ***AT91S_PDC结构中的寄存器偏移***
#define PDC_RPR         ( 0) // 接收指针寄存器
#define PDC_RCR         ( 4) // 接收计数器寄存器
#define PDC_TPR         ( 8) // 发送指针寄存器
#define PDC_TCR         (12) // 发送计数器寄存器
#define PDC_RNPR        (16) // 接收下一个指针寄存器
#define PDC_RNCR        (20) // 接收下一计数器寄存器
#define PDC_TNPR        (24) // 发送下一指针寄存器
#define PDC_TNCR        (28) // 发送下一计数器寄存器
#define PDC_PTCR        (32) // PDC传输控制寄存器
#define PDC_PTSR        (36) // PDC传输状态寄存器
// --------PDC_PTCR：（PDC偏移：0x20）PDC传输控制寄存器--------
#define AT91C_PDC_RXTEN           (0x1 <<  0) // （PDC）接收器传输启用
#define AT91C_PDC_RXTDIS          (0x1 <<  1) // （PDC）接收器传输禁用
#define AT91C_PDC_TXTEN           (0x1 <<  8) // （PDC）发射器传输启用
#define AT91C_PDC_TXTDIS          (0x1 <<  9) // （PDC）发射器传输禁用
// --------PDC_PTSR：（PDC偏移：0x24）PDC传输状态寄存器--------

// *****************************************************************************
//              调试单元的软件API定义
// *****************************************************************************
// ***AT91S_DBGU结构中的寄存器偏移量***
#define DBGU_CR         ( 0) // 控制寄存器
#define DBGU_MR         ( 4) // 模式寄存器
#define DBGU_IER        ( 8) // 中断启用寄存器
#define DBGU_IDR        (12) // 中断禁用寄存器
#define DBGU_IMR        (16) // 中断掩码寄存器
#define DBGU_CSR        (20) // 信道状态寄存器
#define DBGU_RHR        (24) // 接收机保持寄存器
#define DBGU_THR        (28) // 变送器保持寄存器
#define DBGU_BRGR       (32) // 波特率发生器寄存器
#define DBGU_CIDR       (64) // 芯片ID寄存器
#define DBGU_EXID       (68) // 芯片ID扩展寄存器
#define DBGU_FNTR       (72) // 强制NTRST寄存器
#define DBGU_RPR        (256) // 接收指针寄存器
#define DBGU_RCR        (260) // 接收计数器寄存器
#define DBGU_TPR        (264) // 发送指针寄存器
#define DBGU_TCR        (268) // 发送计数器寄存器
#define DBGU_RNPR       (272) // 接收下一个指针寄存器
#define DBGU_RNCR       (276) // 接收下一计数器寄存器
#define DBGU_TNPR       (280) // 发送下一指针寄存器
#define DBGU_TNCR       (284) // 发送下一计数器寄存器
#define DBGU_PTCR       (288) // PDC传输控制寄存器
#define DBGU_PTSR       (292) // PDC传输状态寄存器
// --------DBGU_CR：（DBGU偏移量：0x0）调试单元控制寄存器--------
#define AT91C_US_RSTRX            (0x1 <<  2) // （DBGU）重置接收器
#define AT91C_US_RSTTX            (0x1 <<  3) // （DBGU）复位变送器
#define AT91C_US_RXEN             (0x1 <<  4) // （DBGU）接收器启用
#define AT91C_US_RXDIS            (0x1 <<  5) // （DBGU）接收器禁用
#define AT91C_US_TXEN             (0x1 <<  6) // （DBGU）变送器启用
#define AT91C_US_TXDIS            (0x1 <<  7) // （DBGU）变送器禁用
#define AT91C_US_RSTSTA           (0x1 <<  8) // （DBGU）重置状态位
// --------DBGU_MR：（DBGU偏移量：0x4）调试单元模式寄存器--------
#define AT91C_US_PAR              (0x7 <<  9) // （DBGU）奇偶校验类型
#define 	AT91C_US_PAR_EVEN                 (0x0 <<  9) // （DBGU）偶校验
#define 	AT91C_US_PAR_ODD                  (0x1 <<  9) // （DBGU）奇数奇偶校验
#define 	AT91C_US_PAR_SPACE                (0x2 <<  9) // （DBGU）奇偶校验强制为0（空格）
#define 	AT91C_US_PAR_MARK                 (0x3 <<  9) // （DBGU）奇偶校验强制为1（标记）
#define 	AT91C_US_PAR_NONE                 (0x4 <<  9) // （DBGU）无奇偶校验
#define 	AT91C_US_PAR_MULTI_DROP           (0x6 <<  9) // （DBGU）多点模式
#define AT91C_US_CHMODE           (0x3 << 14) // （DBGU）信道模式
#define 	AT91C_US_CHMODE_NORMAL               (0x0 << 14) // （DBGU）正常模式：USART信道作为RX/TX USART运行。
#define 	AT91C_US_CHMODE_AUTO                 (0x1 << 14) // （DBGU）自动回声：接收器数据输入连接到TXD引脚。
#define 	AT91C_US_CHMODE_LOCAL                (0x2 << 14) // （DBGU）本地环回：发射机输出信号连接到接收机输入信号。
#define 	AT91C_US_CHMODE_REMOTE               (0x3 << 14) // （DBGU）远程环回：RXD引脚内部连接到TXD引脚。
// --------DBGU_IER:（DBGU偏移：0x8）调试单元中断启用寄存器--------
#define AT91C_US_RXRDY            (0x1 <<  0) // （DBGU）RXRDY中断
#define AT91C_US_TXRDY            (0x1 <<  1) // （DBGU）TXRDY中断
#define AT91C_US_ENDRX            (0x1 <<  3) // （DBGU）接收传输中断结束
#define AT91C_US_ENDTX            (0x1 <<  4) // （DBGU）传输中断结束
#define AT91C_US_OVRE             (0x1 <<  5) // （DBGU）超限中断
#define AT91C_US_FRAME            (0x1 <<  6) // （DBGU）成帧错误中断
#define AT91C_US_PARE             (0x1 <<  7) // （DBGU）奇偶错误中断
#define AT91C_US_TXEMPTY          (0x1 <<  9) // （DBGU）TXEMPTY中断
#define AT91C_US_TXBUFE           (0x1 << 11) // （DBGU）TXBUFE中断
#define AT91C_US_RXBUFF           (0x1 << 12) // （DBGU）RXBUFF中断
#define AT91C_US_COMM_TX          (0x1 << 30) // （DBGU）COMM_TX中断
#define AT91C_US_COMM_RX          (0x1 << 31) // （DBGU）COMM_RX中断
// --------DBGU_IDR:（DBGU偏移量：0xc）调试单元中断禁用寄存器--------
// --------DBGU_IMR：（DBGU偏移：0x10）调试单元中断掩码寄存器--------
// --------DBGU_CSR:（DBGU偏移：0x14）调试单元信道状态寄存器--------
// --------DBGU_FNTR：（DBGU偏移量：0x48）调试单元FORCE_NRST寄存器--------
#define AT91C_US_FORCE_NTRST      (0x1 <<  0) // JTAG中的（DBGU）部队NTRST

// *****************************************************************************
//              并行输入输出控制器的软件API定义
// *****************************************************************************
// ***AT91S_PIO结构中的寄存器偏移量***
#define PIO_PER         ( 0) // PIO启用寄存器
#define PIO_PDR         ( 4) // PIO禁用寄存器
#define PIO_PSR         ( 8) // PIO状态寄存器
#define PIO_OER         (16) // 输出启用寄存器
#define PIO_ODR         (20) // 输出禁用寄存器
#define PIO_OSR         (24) // 输出状态寄存器
#define PIO_IFER        (32) // 输入滤波器启用寄存器
#define PIO_IFDR        (36) // 输入滤波器禁用寄存器
#define PIO_IFSR        (40) // 输入过滤器状态寄存器
#define PIO_SODR        (48) // 设置输出数据寄存器
#define PIO_CODR        (52) // 清除输出数据寄存器
#define PIO_ODSR        (56) // 输出数据状态寄存器
#define PIO_PDSR        (60) // 引脚数据状态寄存器
#define PIO_IER         (64) // 中断启用寄存器
#define PIO_IDR         (68) // 中断禁用寄存器
#define PIO_IMR         (72) // 中断掩码寄存器
#define PIO_ISR         (76) // 中断状态寄存器
#define PIO_MDER        (80) // 多驱动程序启用寄存器
#define PIO_MDDR        (84) // 多驱动程序禁用寄存器
#define PIO_MDSR        (88) // 多驱动程序状态寄存器
#define PIO_PPUDR       (96) // 上拉禁用寄存器
#define PIO_PPUER       (100) // 上拉启用寄存器
#define PIO_PPUSR       (104) // 拉起状态寄存器
#define PIO_ASR         (112) // 选择一个寄存器
#define PIO_BSR         (116) // 选择B寄存器
#define PIO_ABSR        (120) // AB选择状态寄存器
#define PIO_OWER        (160) // 输出写入启用寄存器
#define PIO_OWDR        (164) // 输出写入禁用寄存器
#define PIO_OWSR        (168) // 输出写入状态寄存器

// *****************************************************************************
//              时钟发生器控制器的软件API定义
// *****************************************************************************
// ***AT91S_CKGR结构中的寄存器偏移量***
#define CKGR_MOR        ( 0) // 主振荡器寄存器
#define CKGR_MCFR       ( 4) // 主时钟频率寄存器
#define CKGR_PLLR       (12) // PLL寄存器
// --------CKGR_MOR:（CKGR偏移：0x0）主振荡器寄存器--------
#define AT91C_CKGR_MOSCEN         (0x1 <<  0) // （CKGR）主振荡器启用
#define AT91C_CKGR_OSCBYPASS      (0x1 <<  1) // （CKGR）主振荡器旁路
#define AT91C_CKGR_OSCOUNT        (0xFF <<  8) // （CKGR）主振荡器启动时间
// --------CKGR_MCFR：（CKGR偏移：0x4）主时钟频率寄存器--------
#define AT91C_CKGR_MAINF          (0xFFFF <<  0) // （CKGR）主时钟频率
#define AT91C_CKGR_MAINRDY        (0x1 << 16) // （CKGR）主时钟就绪
// --------CKGR_PLLR：（CKGR偏移：0xc）PLL B寄存器--------
#define AT91C_CKGR_DIV            (0xFF <<  0) // 已选择（CKGR）分频器
#define 	AT91C_CKGR_DIV_0                    (0x0) // （CKGR）除法器输出为0
#define 	AT91C_CKGR_DIV_BYPASS               (0x1) // （CKGR）分流器旁通
#define AT91C_CKGR_PLLCOUNT       (0x3F <<  8) // （CKGR）PLL计数器
#define AT91C_CKGR_OUT            (0x3 << 14) // （CKGR）PLL输出频率范围
#define 	AT91C_CKGR_OUT_0                    (0x0 << 14) // （CKGR）请参考PLL数据表
#define 	AT91C_CKGR_OUT_1                    (0x1 << 14) // （CKGR）请参考PLL数据表
#define 	AT91C_CKGR_OUT_2                    (0x2 << 14) // （CKGR）请参考PLL数据表
#define 	AT91C_CKGR_OUT_3                    (0x3 << 14) // （CKGR）请参考PLL数据表
#define AT91C_CKGR_MUL            (0x7FF << 16) // （CKGR）PLL乘法器
#define AT91C_CKGR_USBDIV         (0x3 << 28) // （CKGR）USB时钟分频器
#define 	AT91C_CKGR_USBDIV_0                    (0x0 << 28) // （CKGR）分频器输出为PLL时钟输出
#define 	AT91C_CKGR_USBDIV_1                    (0x1 << 28) // （CKGR）分频器输出是PLL时钟输出除以2
#define 	AT91C_CKGR_USBDIV_2                    (0x2 << 28) // （CKGR）分频器输出是PLL时钟输出除以4

// *****************************************************************************
//              电源管理控制器的软件API定义
// *****************************************************************************
// ***AT91S_PMC结构中的寄存器偏移量***
#define PMC_SCER        ( 0) // 系统时钟启用寄存器
#define PMC_SCDR        ( 4) // 系统时钟禁用寄存器
#define PMC_SCSR        ( 8) // 系统时钟状态寄存器
#define PMC_PCER        (16) // 外围时钟启用寄存器
#define PMC_PCDR        (20) // 外围时钟禁用寄存器
#define PMC_PCSR        (24) // 外围时钟状态寄存器
#define PMC_MOR         (32) // 主振荡器寄存器
#define PMC_MCFR        (36) // 主时钟频率寄存器
#define PMC_PLLR        (44) // PLL寄存器
#define PMC_MCKR        (48) // 主时钟寄存器
#define PMC_PCKR        (64) // 可编程时钟寄存器
#define PMC_IER         (96) // 中断启用寄存器
#define PMC_IDR         (100) // 中断禁用寄存器
#define PMC_SR          (104) // 状态寄存器
#define PMC_IMR         (108) // 中断掩码寄存器
// --------PMC_SCER：（PMC偏移：0x0）系统时钟启用寄存器--------
#define AT91C_PMC_PCK             (0x1 <<  0) // （PMC）处理器时钟
#define AT91C_PMC_UDP             (0x1 <<  7) // （PMC）USB设备端口时钟
#define AT91C_PMC_PCK0            (0x1 <<  8) // （PMC）可编程时钟输出
#define AT91C_PMC_PCK1            (0x1 <<  9) // （PMC）可编程时钟输出
#define AT91C_PMC_PCK2            (0x1 << 10) // （PMC）可编程时钟输出
#define AT91C_PMC_PCK3            (0x1 << 11) // （PMC）可编程时钟输出
// --------PMC_SCDR：（PMC偏移：0x4）系统时钟禁用寄存器--------
// --------PMC_SCSR：（PMC偏移：0x8）系统时钟状态寄存器--------
// --------CKGR_MOR:（PMC偏移：0x20）主振荡器寄存器--------
// --------CKGR_MCFR：（PMC偏移：0x24）主时钟频率寄存器--------
// --------CKGR_PLLR：（PMC偏移：0x2c）PLL B寄存器--------
// --------PMC_MCKR：（PMC偏移：0x30）主时钟寄存器--------
#define AT91C_PMC_CSS             (0x3 <<  0) // （PMC）可编程时钟选择
#define 	AT91C_PMC_CSS_SLOW_CLK             (0x0) // （PMC）选择慢速时钟
#define 	AT91C_PMC_CSS_MAIN_CLK             (0x1) // （PMC）选择主时钟
#define 	AT91C_PMC_CSS_PLL_CLK              (0x3) // （PMC）选择PLL时钟
#define AT91C_PMC_PRES            (0x7 <<  2) // （PMC）可编程时钟预分频器
#define 	AT91C_PMC_PRES_CLK                  (0x0 <<  2) // （PMC）所选时钟
#define 	AT91C_PMC_PRES_CLK_2                (0x1 <<  2) // （PMC）所选时钟除以2
#define 	AT91C_PMC_PRES_CLK_4                (0x2 <<  2) // （PMC）所选时钟除以4
#define 	AT91C_PMC_PRES_CLK_8                (0x3 <<  2) // （PMC）所选时钟除以8
#define 	AT91C_PMC_PRES_CLK_16               (0x4 <<  2) // （PMC）所选时钟除以16
#define 	AT91C_PMC_PRES_CLK_32               (0x5 <<  2) // （PMC）所选时钟除以32
#define 	AT91C_PMC_PRES_CLK_64               (0x6 <<  2) // （PMC）所选时钟除以64
// --------PMC_PCKR：（PMC偏移：0x40）可编程时钟寄存器--------
// --------PMC_IER：（PMC偏移：0x60）PMC中断启用寄存器--------
#define AT91C_PMC_MOSCS           (0x1 <<  0) // （PMC）MOSC状态/启用/禁用/掩码
#define AT91C_PMC_LOCK            (0x1 <<  2) // （PMC）PLL状态/启用/禁用/屏蔽
#define AT91C_PMC_MCKRDY          (0x1 <<  3) // （PMC）MCK_RDY状态/启用/禁用/掩码
#define AT91C_PMC_PCK0RDY         (0x1 <<  8) // （PMC）PCK0_RDY状态/启用/禁用/屏蔽
#define AT91C_PMC_PCK1RDY         (0x1 <<  9) // （PMC）PCK1_RDY状态/启用/禁用/屏蔽
#define AT91C_PMC_PCK2RDY         (0x1 << 10) // （PMC）PCK2_RDY状态/启用/禁用/屏蔽
#define AT91C_PMC_PCK3RDY         (0x1 << 11) // （PMC）PCK3_RDY状态/启用/禁用/屏蔽
// --------PMC_IDR：（PMC偏移：0x64）PMC中断禁用寄存器--------
// --------PMC_SR：（PMC偏移量：0x68）PMC状态寄存器--------
// --------PMC_IMR：（PMC偏移：0x6c）PMC中断掩码寄存器--------

// *****************************************************************************
//              重置控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_RSTC结构中的寄存器偏移量***
#define RSTC_RCR        ( 0) // 重置控制寄存器
#define RSTC_RSR        ( 4) // 重置状态寄存器
#define RSTC_RMR        ( 8) // 重置模式寄存器
// --------RSTC_RCR：（RSTC偏移：0x0）重置控制寄存器--------
#define AT91C_RSTC_PROCRST        (0x1 <<  0) // （RSTC）处理器重置
#define AT91C_RSTC_PERRST         (0x1 <<  2) // （RSTC）外围设备重置
#define AT91C_RSTC_EXTRST         (0x1 <<  3) // （RSTC）外部复位
#define AT91C_RSTC_KEY            (0xFF << 24) // （RSTC）密码
// --------RSTC_RSR：（RSTC偏移：0x4）重置状态寄存器--------
#define AT91C_RSTC_URSTS          (0x1 <<  0) // （RSTC）用户重置状态
#define AT91C_RSTC_BODSTS         (0x1 <<  1) // （RSTC）电量不足检测状态
#define AT91C_RSTC_RSTTYP         (0x7 <<  8) // （RSTC）重置类型
#define 	AT91C_RSTC_RSTTYP_POWERUP              (0x0 <<  8) // （RSTC）加电复位。VDDCORE上升。
#define 	AT91C_RSTC_RSTTYP_WAKEUP               (0x1 <<  8) // （RSTC）唤醒重置。VDDCORE上升。
#define 	AT91C_RSTC_RSTTYP_WATCHDOG             (0x2 <<  8) // （RSTC）监视器重置。发生看门狗溢出。
#define 	AT91C_RSTC_RSTTYP_SOFTWARE             (0x3 <<  8) // （RSTC）软件重置。软件要求处理器复位。
#define 	AT91C_RSTC_RSTTYP_USER                 (0x4 <<  8) // （RSTC）用户重置。检测到NRST引脚过低。
#define 	AT91C_RSTC_RSTTYP_BROWNOUT             (0x5 <<  8) // （RSTC）发生断电重置。
#define AT91C_RSTC_NRSTL          (0x1 << 16) // （RSTC）NRST引脚电平
#define AT91C_RSTC_SRCMP          (0x1 << 17) // （RSTC）软件重置命令正在进行。
// --------RSTC_RMR：（RSTC偏移：0x8）重置模式寄存器--------
#define AT91C_RSTC_URSTEN         (0x1 <<  0) // （RSTC）用户重置启用
#define AT91C_RSTC_URSTIEN        (0x1 <<  4) // （RSTC）用户重置中断启用
#define AT91C_RSTC_ERSTL          (0xF <<  8) // （RSTC）用户重置长度
#define AT91C_RSTC_BODIEN         (0x1 << 16) // （RSTC）断电检测中断启用

// *****************************************************************************
//              实时定时器控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_RTTC结构中的寄存器偏移量***
#define RTTC_RTMR       ( 0) // 实时模式寄存器
#define RTTC_RTAR       ( 4) // 实时报警寄存器
#define RTTC_RTVR       ( 8) // 实时值寄存器
#define RTTC_RTSR       (12) // 实时状态寄存器
// --------RTTC_RTMR：（RTTC偏移：0x0）实时模式寄存器--------
#define AT91C_RTTC_RTPRES         (0xFFFF <<  0) // （RTTC）实时计时器预分频器值
#define AT91C_RTTC_ALMIEN         (0x1 << 16) // （RTTC）报警中断启用
#define AT91C_RTTC_RTTINCIEN      (0x1 << 17) // （RTTC）实时定时器增量中断启用
#define AT91C_RTTC_RTTRST         (0x1 << 18) // （RTTC）实时计时器重启
// --------RTTC_RTAR：（RTTC偏移：0x4）实时报警寄存器--------
#define AT91C_RTTC_ALMV           (0x0 <<  0) // （RTTC）报警值
// --------RTTC_RTVR：（RTTC偏移：0x8）当前实时值寄存器--------
#define AT91C_RTTC_CRTV           (0x0 <<  0) // （RTTC）当前实时值
// --------RTTC_RTSR：（RTTC偏移：0xc）实时状态寄存器--------
#define AT91C_RTTC_ALMS           (0x1 <<  0) // （RTTC）实时报警状态
#define AT91C_RTTC_RTTINC         (0x1 <<  1) // （RTTC）实时计时器增量

// *****************************************************************************
//              周期间隔定时器控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_PITC结构中的寄存器偏移量***
#define PITC_PIMR       ( 0) // 周期间隔模式寄存器
#define PITC_PISR       ( 4) // 周期间隔状态寄存器
#define PITC_PIVR       ( 8) // 周期间隔值寄存器
#define PITC_PIIR       (12) // 周期间隔图像寄存器
// --------PITC_PIR:（PITC偏移：0x0）周期间隔模式寄存器--------
#define AT91C_PITC_PIV            (0xFFFFF <<  0) // （PITC）周期间隔值
#define AT91C_PITC_PITEN          (0x1 << 24) // （PITC）周期间隔计时器已启用
#define AT91C_PITC_PITIEN         (0x1 << 25) // （PITC）周期间隔定时器中断启用
// --------PITC_PISR:（PITC偏移量：0x4）周期间隔状态寄存器--------
#define AT91C_PITC_PITS           (0x1 <<  0) // （PITC）周期间隔计时器状态
// --------PITC_PIVR：（PITC偏移量：0x8）周期间隔值寄存器--------
#define AT91C_PITC_CPIV           (0xFFFFF <<  0) // （PITC）当前周期间隔值
#define AT91C_PITC_PICNT          (0xFFF << 20) // （PITC）周期间隔计数器
// --------PITC_PIR:（PITC偏移：0xc）周期间隔图像寄存器--------

// *****************************************************************************
//              看门狗定时器控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_WDTC结构中的寄存器偏移量***
#define WDTC_WDCR       ( 0) // 看门狗控制寄存器
#define WDTC_WDMR       ( 4) // 看门狗模式寄存器
#define WDTC_WDSR       ( 8) // 看门狗状态寄存器
// --------WDTC_WDCR：（WDTC偏移：0x0）周期间隔图像寄存器--------
#define AT91C_WDTC_WDRSTT         (0x1 <<  0) // （WDTC）监视器重新启动
#define AT91C_WDTC_KEY            (0xFF << 24) // （WDTC）看门狗密钥密码
// --------WDTC_WDMR：（WDTC偏移：0x4）看门狗模式寄存器--------
#define AT91C_WDTC_WDV            (0xFFF <<  0) // （WDTC）看门狗计时器重新启动
#define AT91C_WDTC_WDFIEN         (0x1 << 12) // （WDTC）看门狗故障中断启用
#define AT91C_WDTC_WDRSTEN        (0x1 << 13) // （WDTC）监视器重置启用
#define AT91C_WDTC_WDRPROC        (0x1 << 14) // （WDTC）看门狗计时器重新启动
#define AT91C_WDTC_WDDIS          (0x1 << 15) // （WDTC）看门狗禁用
#define AT91C_WDTC_WDD            (0xFFF << 16) // （WDTC）看门狗增量值
#define AT91C_WDTC_WDDBGHLT       (0x1 << 28) // （WDTC）监视器调试停止
#define AT91C_WDTC_WDIDLEHLT      (0x1 << 29) // （WDTC）看门狗空闲停止
// --------WDTC_WDSR:（WDTC偏移量：0x8）看门狗状态寄存器--------
#define AT91C_WDTC_WDUNF          (0x1 <<  0) // （WDTC）看门狗欠流
#define AT91C_WDTC_WDERR          (0x1 <<  1) // （WDTC）看门狗错误

// *****************************************************************************
//              稳压器模式控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_VREG结构中的寄存器偏移***
#define VREG_MR         ( 0) // 电压调节器模式寄存器
// --------VREG_MR：（VREG偏移：0x0）电压调节器模式寄存器--------
#define AT91C_VREG_PSTDBY         (0x1 <<  0) // （VREG）电压调节器电源待机模式

// *****************************************************************************
//              存储器控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_MC结构中的寄存器偏移量***
#define MC_RCR          ( 0) // MC重映射控制寄存器
#define MC_ASR          ( 4) // MC中止状态寄存器
#define MC_AASR         ( 8) // MC中止地址状态寄存器
#define MC_FMR          (96) // MC闪存模式寄存器
#define MC_FCR          (100) // MC闪存命令寄存器
#define MC_FSR          (104) // MC闪存状态寄存器
// --------MC_RCR：（MC偏移：0x0）MC重映射控制寄存器--------
#define AT91C_MC_RCB              (0x1 <<  0) // （MC）重映射命令位
// --------MC_ASR:（MC偏移量：0x4）MC中止状态寄存器--------
#define AT91C_MC_UNDADD           (0x1 <<  0) // （MC）未定义的地址中止状态
#define AT91C_MC_MISADD           (0x1 <<  1) // （MC）地址错误中止状态
#define AT91C_MC_ABTSZ            (0x3 <<  8) // （MC）中止大小状态
#define 	AT91C_MC_ABTSZ_BYTE                 (0x0 <<  8) // （MC）字节
#define 	AT91C_MC_ABTSZ_HWORD                (0x1 <<  8) // （MC）半字
#define 	AT91C_MC_ABTSZ_WORD                 (0x2 <<  8) // （MC）字
#define AT91C_MC_ABTTYP           (0x3 << 10) // （MC）中止类型状态
#define 	AT91C_MC_ABTTYP_DATAR                (0x0 << 10) // （MC）数据读取
#define 	AT91C_MC_ABTTYP_DATAW                (0x1 << 10) // （MC）数据写入
#define 	AT91C_MC_ABTTYP_FETCH                (0x2 << 10) // （MC）代码获取
#define AT91C_MC_MST0             (0x1 << 16) // （MC）主机0中止源
#define AT91C_MC_MST1             (0x1 << 17) // （MC）主1中止源
#define AT91C_MC_SVMST0           (0x1 << 24) // （MC）保存的主机0中止源
#define AT91C_MC_SVMST1           (0x1 << 25) // （MC）保存的主1中止源
// --------MC_FMR：（MC偏移：0x60）MC闪存模式寄存器--------
#define AT91C_MC_FRDY             (0x1 <<  0) // （MC）闪存就绪
#define AT91C_MC_LOCKE            (0x1 <<  2) // （MC）锁定错误
#define AT91C_MC_PROGE            (0x1 <<  3) // （MC）编程错误
#define AT91C_MC_NEBP             (0x1 <<  7) // （MC）编程前无擦除
#define AT91C_MC_FWS              (0x3 <<  8) // （MC）闪存等待状态
#define 	AT91C_MC_FWS_0FWS                 (0x0 <<  8) // （MC）1个周期用于读取，2个周期用于写入操作
#define 	AT91C_MC_FWS_1FWS                 (0x1 <<  8) // （MC）读取操作2个周期，写入操作3个周期
#define 	AT91C_MC_FWS_2FWS                 (0x2 <<  8) // （MC）3个周期用于读取，4个周期用于写入操作
#define 	AT91C_MC_FWS_3FWS                 (0x3 <<  8) // （MC）读操作4个周期，写操作4个
#define AT91C_MC_FMCN             (0xFF << 16) // （MC）闪存微秒循环数
// --------MC_FCR：（MC偏移：0x64）MC闪存命令寄存器--------
#define AT91C_MC_FCMD             (0xF <<  0) // （MC）闪存命令
#define 	AT91C_MC_FCMD_START_PROG           (0x1) // （MC）启动PAGEN指定页的编程。
#define 	AT91C_MC_FCMD_LOCK                 (0x2) // （MC）开始由字段PAGEN的位4至7定义的扇区的锁定序列。
#define 	AT91C_MC_FCMD_PROG_AND_LOCK        (0x3) // （MC）编程序列完成后，锁定序列自动发生。
#define 	AT91C_MC_FCMD_UNLOCK               (0x4) // （MC）开始由字段PAGEN的位4至7定义的扇区的解锁序列。
#define 	AT91C_MC_FCMD_ERASE_ALL            (0x8) // （MC）开始擦除整个闪存。如果至少有一个页面被锁定，则该命令将被取消。
#define 	AT91C_MC_FCMD_SET_GP_NVM           (0xB) // （MC）设置通用NVM位。
#define 	AT91C_MC_FCMD_CLR_GP_NVM           (0xD) // （MC）清除通用NVM位。
#define 	AT91C_MC_FCMD_SET_SECURITY         (0xF) // （MC）设置安全位。
#define AT91C_MC_PAGEN            (0x3FF <<  8) // （MC）页码
#define AT91C_MC_KEY              (0xFF << 24) // （MC）写入保护密钥
// --------MC_FSR:（MC偏移：0x68）MC闪存命令寄存器--------
#define AT91C_MC_SECURITY         (0x1 <<  4) // （MC）安全位状态
#define AT91C_MC_GPNVM0           (0x1 <<  8) // （MC）扇区0锁定状态
#define AT91C_MC_GPNVM1           (0x1 <<  9) // （MC）扇区1锁定状态
#define AT91C_MC_GPNVM2           (0x1 << 10) // （MC）扇区2锁定状态
#define AT91C_MC_GPNVM3           (0x1 << 11) // （MC）扇区3锁定状态
#define AT91C_MC_GPNVM4           (0x1 << 12) // （MC）扇区4锁定状态
#define AT91C_MC_GPNVM5           (0x1 << 13) // （MC）扇区5锁定状态
#define AT91C_MC_GPNVM6           (0x1 << 14) // （MC）扇区6锁定状态
#define AT91C_MC_GPNVM7           (0x1 << 15) // （MC）扇区7锁定状态
#define AT91C_MC_LOCKS0           (0x1 << 16) // （MC）扇区0锁定状态
#define AT91C_MC_LOCKS1           (0x1 << 17) // （MC）扇区1锁定状态
#define AT91C_MC_LOCKS2           (0x1 << 18) // （MC）扇区2锁定状态
#define AT91C_MC_LOCKS3           (0x1 << 19) // （MC）扇区3锁定状态
#define AT91C_MC_LOCKS4           (0x1 << 20) // （MC）扇区4锁定状态
#define AT91C_MC_LOCKS5           (0x1 << 21) // （MC）扇区5锁定状态
#define AT91C_MC_LOCKS6           (0x1 << 22) // （MC）扇区6锁定状态
#define AT91C_MC_LOCKS7           (0x1 << 23) // （MC）扇区7锁定状态
#define AT91C_MC_LOCKS8           (0x1 << 24) // （MC）扇区8锁定状态
#define AT91C_MC_LOCKS9           (0x1 << 25) // （MC）扇区9锁定状态
#define AT91C_MC_LOCKS10          (0x1 << 26) // （MC）扇区10锁定状态
#define AT91C_MC_LOCKS11          (0x1 << 27) // （MC）扇区11锁定状态
#define AT91C_MC_LOCKS12          (0x1 << 28) // （MC）扇区12锁定状态
#define AT91C_MC_LOCKS13          (0x1 << 29) // （MC）扇区13锁定状态
#define AT91C_MC_LOCKS14          (0x1 << 30) // （MC）扇区14锁定状态
#define AT91C_MC_LOCKS15          (0x1 << 31) // （MC）扇区15锁定状态

// *****************************************************************************
//              串行并行接口的软件API定义
// *****************************************************************************
// ***AT91S_SPI结构中的寄存器偏移***
#define SPI_CR          ( 0) // 控制寄存器
#define SPI_MR          ( 4) // 模式寄存器
#define SPI_RDR         ( 8) // 接收数据寄存器
#define SPI_TDR         (12) // 传输数据寄存器
#define SPI_SR          (16) // 状态寄存器
#define SPI_IER         (20) // 中断启用寄存器
#define SPI_IDR         (24) // 中断禁用寄存器
#define SPI_IMR         (28) // 中断掩码寄存器
#define SPI_CSR         (48) // 芯片选择寄存器
#define SPI_RPR         (256) // 接收指针寄存器
#define SPI_RCR         (260) // 接收计数器寄存器
#define SPI_TPR         (264) // 发送指针寄存器
#define SPI_TCR         (268) // 发送计数器寄存器
#define SPI_RNPR        (272) // 接收下一个指针寄存器
#define SPI_RNCR        (276) // 接收下一计数器寄存器
#define SPI_TNPR        (280) // 发送下一指针寄存器
#define SPI_TNCR        (284) // 发送下一计数器寄存器
#define SPI_PTCR        (288) // PDC传输控制寄存器
#define SPI_PTSR        (292) // PDC传输状态寄存器
// --------SPI_CR：（SPI偏移：0x0）SPI控制寄存器--------
#define AT91C_SPI_SPIEN           (0x1 <<  0) // （SPI）SPI启用
#define AT91C_SPI_SPIDIS          (0x1 <<  1) // （SPI）SPI禁用
#define AT91C_SPI_SWRST           (0x1 <<  7) // （SPI）SPI软件复位
#define AT91C_SPI_LASTXFER        (0x1 << 24) // （SPI）SPI上次传输
// --------SPI_MR：（SPI偏移量：0x4）SPI模式寄存器--------
#define AT91C_SPI_MSTR            (0x1 <<  0) // （SPI）主/从模式
#define AT91C_SPI_PS              (0x1 <<  1) // （SPI）外围设备选择
#define 	AT91C_SPI_PS_FIXED                (0x0 <<  1) // （SPI）固定外设选择
#define 	AT91C_SPI_PS_VARIABLE             (0x1 <<  1) // （SPI）可变外围设备选择
#define AT91C_SPI_PCSDEC          (0x1 <<  2) // （SPI）芯片选择解码
#define AT91C_SPI_FDIV            (0x1 <<  3) // （SPI）时钟选择
#define AT91C_SPI_MODFDIS         (0x1 <<  4) // （SPI）模式故障检测
#define AT91C_SPI_LLB             (0x1 <<  7) // （SPI）时钟选择
#define AT91C_SPI_PCS             (0xF << 16) // （SPI）外围芯片选择
#define AT91C_SPI_DLYBCS          (0xFF << 24) // 芯片选择之间的（SPI）延迟
// --------SPI_RDR:（SPI偏移量：0x8）接收数据寄存器--------
#define AT91C_SPI_RD              (0xFFFF <<  0) // （SPI）接收数据
#define AT91C_SPI_RPCS            (0xF << 16) // （SPI）外围芯片选择状态
// --------SPI_TDR：（SPI偏移量：0xc）传输数据寄存器--------
#define AT91C_SPI_TD              (0xFFFF <<  0) // （SPI）传输数据
#define AT91C_SPI_TPCS            (0xF << 16) // （SPI）外围芯片选择状态
// --------SPI_SR：（SPI偏移量：0x10）状态寄存器--------
#define AT91C_SPI_RDRF            (0x1 <<  0) // （SPI）接收数据寄存器已满
#define AT91C_SPI_TDRE            (0x1 <<  1) // （SPI）传输数据寄存器为空
#define AT91C_SPI_MODF            (0x1 <<  2) // （SPI）模式故障错误
#define AT91C_SPI_OVRES           (0x1 <<  3) // （SPI）超限错误状态
#define AT91C_SPI_ENDRX           (0x1 <<  4) // （SPI）接收器传输结束
#define AT91C_SPI_ENDTX           (0x1 <<  5) // （SPI）接收器传输结束
#define AT91C_SPI_RXBUFF          (0x1 <<  6) // （SPI）RXBUFF中断
#define AT91C_SPI_TXBUFE          (0x1 <<  7) // （SPI）TXBUFE中断
#define AT91C_SPI_NSSR            (0x1 <<  8) // （SPI）NSSR中断
#define AT91C_SPI_TXEMPTY         (0x1 <<  9) // （SPI）TXEMPTY中断
#define AT91C_SPI_SPIENS          (0x1 << 16) // （SPI）启用状态
// --------SPI_IER：（SPI偏移：0x14）中断启用寄存器--------
// --------SPI_IDR：（SPI偏移量：0x18）中断禁用寄存器--------
// --------SPI_IMR：（SPI偏移量：0x1c）中断掩码寄存器--------
// --------SPI_CSR:（SPI偏移：0x30）芯片选择寄存器--------
#define AT91C_SPI_CPOL            (0x1 <<  0) // （SPI）时钟极性
#define AT91C_SPI_NCPHA           (0x1 <<  1) // （SPI）时钟相位
#define AT91C_SPI_CSAAT           (0x1 <<  3) // 传输后激活（SPI）芯片选择
#define AT91C_SPI_BITS            (0xF <<  4) // （SPI）每次传输位
#define 	AT91C_SPI_BITS_8                    (0x0 <<  4) // （SPI）每次传输8位
#define 	AT91C_SPI_BITS_9                    (0x1 <<  4) // （SPI）每次传输9位
#define 	AT91C_SPI_BITS_10                   (0x2 <<  4) // （SPI）每次传输10位
#define 	AT91C_SPI_BITS_11                   (0x3 <<  4) // （SPI）每次传输11位
#define 	AT91C_SPI_BITS_12                   (0x4 <<  4) // （SPI）每次传输12位
#define 	AT91C_SPI_BITS_13                   (0x5 <<  4) // （SPI）每次传输13位
#define 	AT91C_SPI_BITS_14                   (0x6 <<  4) // （SPI）每次传输14位
#define 	AT91C_SPI_BITS_15                   (0x7 <<  4) // （SPI）每次传输15位
#define 	AT91C_SPI_BITS_16                   (0x8 <<  4) // （SPI）每次传输16位
#define AT91C_SPI_SCBR            (0xFF <<  8) // （SPI）串行时钟波特率
#define AT91C_SPI_DLYBS           (0xFF << 16) // SPCK之前的（SPI）延迟
#define AT91C_SPI_DLYBCT          (0xFF << 24) // （SPI）连续传输之间的延迟

// *****************************************************************************
//              用于Usart的软件API定义
// *****************************************************************************
// ***AT91S_USART结构中的寄存器偏移量***
#define US_CR           ( 0) // 控制寄存器
#define US_MR           ( 4) // 模式寄存器
#define US_IER          ( 8) // 中断启用寄存器
#define US_IDR          (12) // 中断禁用寄存器
#define US_IMR          (16) // 中断掩码寄存器
#define US_CSR          (20) // 信道状态寄存器
#define US_RHR          (24) // 接收机保持寄存器
#define US_THR          (28) // 变送器保持寄存器
#define US_BRGR         (32) // 波特率发生器寄存器
#define US_RTOR         (36) // 接收机超时寄存器
#define US_TTGR         (40) // 变送器时间保护寄存器
#define US_FIDI         (64) // FI_DI_Ratio寄存器
#define US_NER          (68) // Nb错误寄存器
#define US_IF           (76) // IRDA_FILTER寄存器
#define US_RPR          (256) // 接收指针寄存器
#define US_RCR          (260) // 接收计数器寄存器
#define US_TPR          (264) // 发送指针寄存器
#define US_TCR          (268) // 发送计数器寄存器
#define US_RNPR         (272) // 接收下一个指针寄存器
#define US_RNCR         (276) // 接收下一计数器寄存器
#define US_TNPR         (280) // 发送下一指针寄存器
#define US_TNCR         (284) // 发送下一计数器寄存器
#define US_PTCR         (288) // PDC传输控制寄存器
#define US_PTSR         (292) // PDC传输状态寄存器
// --------US_CR：（USART偏移：0x0）调试单元控制寄存器--------
#define AT91C_US_STTBRK           (0x1 <<  9) // （USART）开始休息
#define AT91C_US_STPBRK           (0x1 << 10) // （USART）停车休息
#define AT91C_US_STTTO            (0x1 << 11) // （USART）开始超时
#define AT91C_US_SENDA            (0x1 << 12) // （USART）发送地址
#define AT91C_US_RSTIT            (0x1 << 13) // （USART）重置迭代
#define AT91C_US_RSTNACK          (0x1 << 14) // （USART）重置不确认
#define AT91C_US_RETTO            (0x1 << 15) // （USART）重新排列超时
#define AT91C_US_DTREN            (0x1 << 16) // （USART）数据终端就绪启用
#define AT91C_US_DTRDIS           (0x1 << 17) // （USART）数据终端就绪禁用
#define AT91C_US_RTSEN            (0x1 << 18) // （USART）请求发送启用
#define AT91C_US_RTSDIS           (0x1 << 19) // （USART）请求发送禁用
// --------US_MR：（USART偏移：0x4）调试单元模式寄存器--------
#define AT91C_US_USMODE           (0xF <<  0) // （USART）USART模式
#define 	AT91C_US_USMODE_NORMAL               (0x0) // （USART）正常
#define 	AT91C_US_USMODE_RS485                (0x1) // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                (0x2) // （USART）硬件握手
#define 	AT91C_US_USMODE_MODEM                (0x3) // （USART）调制解调器
#define 	AT91C_US_USMODE_ISO7816_0            (0x4) // （USART）ISO7816协议：T=0
#define 	AT91C_US_USMODE_ISO7816_1            (0x6) // （USART）ISO7816协议：T=1
#define 	AT91C_US_USMODE_IRDA                 (0x8) // （USART）伊拉克陆军部
#define 	AT91C_US_USMODE_SWHSH                (0xC) // （USART）软件握手
#define AT91C_US_CLKS             (0x3 <<  4) // （USART）时钟选择（波特率发生器输入时钟
#define 	AT91C_US_CLKS_CLOCK                (0x0 <<  4) // （USART）时钟
#define 	AT91C_US_CLKS_FDIV1                (0x1 <<  4) // （美国陆军）fdiv1
#define 	AT91C_US_CLKS_SLOW                 (0x2 <<  4) // （USART）慢锁（ARM）
#define 	AT91C_US_CLKS_EXT                  (0x3 <<  4) // （USART）外部（SCK）
#define AT91C_US_CHRL             (0x3 <<  6) // （USART）时钟选择（波特率发生器输入时钟
#define 	AT91C_US_CHRL_5_BITS               (0x0 <<  6) // （USART）字符长度：5位
#define 	AT91C_US_CHRL_6_BITS               (0x1 <<  6) // （USART）字符长度：6位
#define 	AT91C_US_CHRL_7_BITS               (0x2 <<  6) // （USART）字符长度：7位
#define 	AT91C_US_CHRL_8_BITS               (0x3 <<  6) // （USART）字符长度：8位
#define AT91C_US_SYNC             (0x1 <<  8) // （USART）同步模式选择
#define AT91C_US_NBSTOP           (0x3 << 12) // （USART）停止位数
#define 	AT91C_US_NBSTOP_1_BIT                (0x0 << 12) // （USART）1个停止位
#define 	AT91C_US_NBSTOP_15_BIT               (0x1 << 12) // （USART）异步（SYNC=0）2个停止位同步（SYNC=1）2个终止位
#define 	AT91C_US_NBSTOP_2_BIT                (0x2 << 12) // （USART）2个停止位
#define AT91C_US_MSBF             (0x1 << 16) // （USART）位顺序
#define AT91C_US_MODE9            (0x1 << 17) // （USART）9位字符长度
#define AT91C_US_CKLO             (0x1 << 18) // （USART）时钟输出选择
#define AT91C_US_OVER             (0x1 << 19) // （USART）过采样模式
#define AT91C_US_INACK            (0x1 << 20) // （USART）禁止不确认
#define AT91C_US_DSNACK           (0x1 << 21) // （USART）禁用连续NACK
#define AT91C_US_MAX_ITER         (0x1 << 24) // （USART）重复次数
#define AT91C_US_FILTER           (0x1 << 28) // （USART）接收线滤波器
// --------US_IER：（USART偏移：0x8）调试单元中断启用寄存器--------
#define AT91C_US_RXBRK            (0x1 <<  2) // （USART）休息接收/休息结束
#define AT91C_US_TIMEOUT          (0x1 <<  8) // （USART）接收机超时
#define AT91C_US_ITERATION        (0x1 << 10) // （USART）达到的最大重复次数
#define AT91C_US_NACK             (0x1 << 13) // （USART）不承认
#define AT91C_US_RIIC             (0x1 << 16) // （USART）响铃指示器输入更改标志
#define AT91C_US_DSRIC            (0x1 << 17) // （USART）数据集就绪输入更改标志
#define AT91C_US_DCDIC            (0x1 << 18) // （USART）数据载体标志
#define AT91C_US_CTSIC            (0x1 << 19) // （USART）清除以发送输入更改标志
// --------US_IDR：（USART偏移：0xc）调试单元中断禁用寄存器--------
// --------US_IMR：（USART偏移：0x10）调试单元中断掩码寄存器--------
// --------US_CSR:（USART偏移：0x14）调试单元信道状态寄存器--------
#define AT91C_US_RI               (0x1 << 20) // （USART）RI输入图像
#define AT91C_US_DSR              (0x1 << 21) // （USART）DSR输入图像
#define AT91C_US_DCD              (0x1 << 22) // （USART）DCD输入图像
#define AT91C_US_CTS              (0x1 << 23) // （USART）CTS输入图像

// *****************************************************************************
//              同步串行控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_SSC结构中的寄存器偏移***
#define SSC_CR          ( 0) // 控制寄存器
#define SSC_CMR         ( 4) // 时钟模式寄存器
#define SSC_RCMR        (16) // 接收时钟模式寄存器
#define SSC_RFMR        (20) // 接收帧模式寄存器
#define SSC_TCMR        (24) // 发送时钟模式寄存器
#define SSC_TFMR        (28) // 发送帧模式寄存器
#define SSC_RHR         (32) // 接收保持寄存器
#define SSC_THR         (36) // 发送保持寄存器
#define SSC_RSHR        (48) // 接收同步保持寄存器
#define SSC_TSHR        (52) // 传输同步保持寄存器
#define SSC_SR          (64) // 状态寄存器
#define SSC_IER         (68) // 中断启用寄存器
#define SSC_IDR         (72) // 中断禁用寄存器
#define SSC_IMR         (76) // 中断掩码寄存器
#define SSC_RPR         (256) // 接收指针寄存器
#define SSC_RCR         (260) // 接收计数器寄存器
#define SSC_TPR         (264) // 发送指针寄存器
#define SSC_TCR         (268) // 发送计数器寄存器
#define SSC_RNPR        (272) // 接收下一个指针寄存器
#define SSC_RNCR        (276) // 接收下一计数器寄存器
#define SSC_TNPR        (280) // 发送下一指针寄存器
#define SSC_TNCR        (284) // 发送下一计数器寄存器
#define SSC_PTCR        (288) // PDC传输控制寄存器
#define SSC_PTSR        (292) // PDC传输状态寄存器
// --------SSC_CR：（SSC偏移：0x0）SSC控制寄存器--------
#define AT91C_SSC_RXEN            (0x1 <<  0) // （SSC）接收启用
#define AT91C_SSC_RXDIS           (0x1 <<  1) // （SSC）接收禁用
#define AT91C_SSC_TXEN            (0x1 <<  8) // （SSC）传输启用
#define AT91C_SSC_TXDIS           (0x1 <<  9) // （SSC）发送禁用
#define AT91C_SSC_SWRST           (0x1 << 15) // （SSC）软件重置
// --------SSC_RCMR：（SSC偏移：0x10）SSC接收时钟模式寄存器--------
#define AT91C_SSC_CKS             (0x3 <<  0) // （SSC）接收/发送时钟选择
#define 	AT91C_SSC_CKS_DIV                  (0x0) // （SSC）分频时钟
#define 	AT91C_SSC_CKS_TK                   (0x1) // （SSC）TK时钟信号
#define 	AT91C_SSC_CKS_RK                   (0x2) // （SSC）RK销
#define AT91C_SSC_CKO             (0x7 <<  2) // （SSC）接收/发送时钟输出模式选择
#define 	AT91C_SSC_CKO_NONE                 (0x0 <<  2) // （SSC）接收/发送时钟输出模式：无RK引脚：仅输入
#define 	AT91C_SSC_CKO_CONTINOUS            (0x1 <<  2) // （SSC）连续接收/发送时钟RK引脚：输出
#define 	AT91C_SSC_CKO_DATA_TX              (0x2 <<  2) // （SSC）仅在数据传输期间接收/发送时钟RK引脚：输出
#define AT91C_SSC_CKI             (0x1 <<  5) // （SSC）接收/发送时钟反转
#define AT91C_SSC_CKG             (0x3 <<  6) // （SSC）接收/发送时钟门控选择
#define 	AT91C_SSC_CKG_NONE                 (0x0 <<  6) // （SSC）接收/发送时钟门控：无，连续时钟
#define 	AT91C_SSC_CKG_LOW                  (0x1 <<  6) // （SSC）仅在RF低时启用接收/发送时钟
#define 	AT91C_SSC_CKG_HIGH                 (0x2 <<  6) // （SSC）仅当RF高时才启用接收/发送时钟
#define AT91C_SSC_START           (0xF <<  8) // （SSC）接收/发送开始选择
#define 	AT91C_SSC_START_CONTINOUS            (0x0 <<  8) // （SSC）一旦启用接收器，在前一数据传输结束后立即连续。
#define 	AT91C_SSC_START_TX                   (0x1 <<  8) // （SSC）发送/接收启动
#define 	AT91C_SSC_START_LOW_RF               (0x2 <<  8) // （SSC）射频输入低电平检测
#define 	AT91C_SSC_START_HIGH_RF              (0x3 <<  8) // （SSC）射频输入高电平检测
#define 	AT91C_SSC_START_FALL_RF              (0x4 <<  8) // （SSC）检测RF输入的下降沿
#define 	AT91C_SSC_START_RISE_RF              (0x5 <<  8) // （SSC）检测RF输入上的上升沿
#define 	AT91C_SSC_START_LEVEL_RF             (0x6 <<  8) // （SSC）检测射频输入的任何电平变化
#define 	AT91C_SSC_START_EDGE_RF              (0x7 <<  8) // （SSC）检测RF输入上的任何边缘
#define 	AT91C_SSC_START_0                    (0x8 <<  8) // （SSC）比较0
#define AT91C_SSC_STOP            (0x1 << 12) // （SSC）接收停止选择
#define AT91C_SSC_STTDLY          (0xFF << 16) // （SSC）接收/发送开始延迟
#define AT91C_SSC_PERIOD          (0xFF << 24) // （SSC）接收/发送周期分频器选择
// --------SSC_RFMR：（SSC偏移：0x14）SSC接收帧模式寄存器--------
#define AT91C_SSC_DATLEN          (0x1F <<  0) // （SSC）数据长度
#define AT91C_SSC_LOOP            (0x1 <<  5) // （SSC）回路模式
#define AT91C_SSC_MSBF            (0x1 <<  7) // （SSC）最高有效位优先
#define AT91C_SSC_DATNB           (0xF <<  8) // （SSC）每帧数据数
#define AT91C_SSC_FSLEN           (0xF << 16) // （SSC）接收/发送帧同步长度
#define AT91C_SSC_FSOS            (0x7 << 20) // （SSC）接收/发送帧同步输出选择
#define 	AT91C_SSC_FSOS_NONE                 (0x0 << 20) // （SSC）所选接收/发送帧同步信号：无RK引脚输入
#define 	AT91C_SSC_FSOS_NEGATIVE             (0x1 << 20) // （SSC）所选接收/发送帧同步信号：负脉冲
#define 	AT91C_SSC_FSOS_POSITIVE             (0x2 << 20) // （SSC）所选接收/发送帧同步信号：正脉冲
#define 	AT91C_SSC_FSOS_LOW                  (0x3 << 20) // （SSC）所选接收/发送帧同步信号：数据传输期间驱动器低
#define 	AT91C_SSC_FSOS_HIGH                 (0x4 << 20) // （SSC）所选接收/发送帧同步信号：数据传输期间驱动器高
#define 	AT91C_SSC_FSOS_TOGGLE               (0x5 << 20) // （SSC）所选接收/发送帧同步信号：在每次数据传输开始时切换
#define AT91C_SSC_FSEDGE          (0x1 << 24) // （SSC）帧同步边缘检测
// --------SSC_TCMR：（SSC偏移：0x18）SSC传输时钟模式寄存器--------
// --------SSC_TFMR：（SSC偏移：0x1c）SSC传输帧模式寄存器--------
#define AT91C_SSC_DATDEF          (0x1 <<  5) // （SSC）数据默认值
#define AT91C_SSC_FSDEN           (0x1 << 23) // （SSC）帧同步数据启用
// --------SSC_SR：（SSC偏移量：0x40）SSC状态寄存器--------
#define AT91C_SSC_TXRDY           (0x1 <<  0) // （SSC）传输就绪
#define AT91C_SSC_TXEMPTY         (0x1 <<  1) // （SSC）传输空
#define AT91C_SSC_ENDTX           (0x1 <<  2) // （SSC）传输结束
#define AT91C_SSC_TXBUFE          (0x1 <<  3) // （SSC）传输缓冲区清空
#define AT91C_SSC_RXRDY           (0x1 <<  4) // （SSC）接收就绪
#define AT91C_SSC_OVRUN           (0x1 <<  5) // （SSC）接收超限
#define AT91C_SSC_ENDRX           (0x1 <<  6) // （SSC）接收结束
#define AT91C_SSC_RXBUFF          (0x1 <<  7) // （SSC）接收缓冲区已满
#define AT91C_SSC_CP0             (0x1 <<  8) // （SSC）比较0
#define AT91C_SSC_CP1             (0x1 <<  9) // （SSC）比较1
#define AT91C_SSC_TXSYN           (0x1 << 10) // （SSC）传输同步
#define AT91C_SSC_RXSYN           (0x1 << 11) // （SSC）接收同步
#define AT91C_SSC_TXENA           (0x1 << 16) // （SSC）传输启用
#define AT91C_SSC_RXENA           (0x1 << 17) // （SSC）接收启用
// --------SSC_IER:（SSC偏移：0x44）SSC中断启用寄存器--------
// --------SSC_IDR：（SSC偏移：0x48）SSC中断禁用寄存器--------
// --------SSC_IMR：（SSC偏移：0x4c）SSC中断掩码寄存器--------

// *****************************************************************************
//              双线接口的软件API定义
// *****************************************************************************
// ***AT91S_TWI结构中的寄存器偏移量***
#define TWI_CR          ( 0) // 控制寄存器
#define TWI_MMR         ( 4) // 主模式寄存器
#define TWI_IADR        (12) // 内部地址寄存器
#define TWI_CWGR        (16) // 时钟波形发生器寄存器
#define TWI_SR          (32) // 状态寄存器
#define TWI_IER         (36) // 中断启用寄存器
#define TWI_IDR         (40) // 中断禁用寄存器
#define TWI_IMR         (44) // 中断掩码寄存器
#define TWI_RHR         (48) // 接收保持寄存器
#define TWI_THR         (52) // 发送保持寄存器
// --------TWI_CR:（TWI偏移：0x0）TWI控制寄存器--------
#define AT91C_TWI_START           (0x1 <<  0) // （TWI）发送启动条件
#define AT91C_TWI_STOP            (0x1 <<  1) // （TWI）发送STOP条件
#define AT91C_TWI_MSEN            (0x1 <<  2) // （TWI）TWI主传输已启用
#define AT91C_TWI_MSDIS           (0x1 <<  3) // （TWI）TWI主传输已禁用
#define AT91C_TWI_SWRST           (0x1 <<  7) // （TWI）软件重置
// --------TWI_MMR：（TWI偏移：0x4）TWI主模式寄存器--------
#define AT91C_TWI_IADRSZ          (0x3 <<  8) // （TWI）内部设备地址大小
#define 	AT91C_TWI_IADRSZ_NO                   (0x0 <<  8) // （TWI）无内部设备地址
#define 	AT91C_TWI_IADRSZ_1_BYTE               (0x1 <<  8) // （TWI）一字节内部设备地址
#define 	AT91C_TWI_IADRSZ_2_BYTE               (0x2 <<  8) // （TWI）双字节内部设备地址
#define 	AT91C_TWI_IADRSZ_3_BYTE               (0x3 <<  8) // （TWI）三字节内部设备地址
#define AT91C_TWI_MREAD           (0x1 << 12) // （TWI）主读取方向
#define AT91C_TWI_DADR            (0x7F << 16) // （TWI）设备地址
// --------TWI_CWGR:（TWI偏移：0x10）TWI时钟波形发生器寄存器--------
#define AT91C_TWI_CLDIV           (0xFF <<  0) // （TWI）时钟低分频器
#define AT91C_TWI_CHDIV           (0xFF <<  8) // （TWI）时钟高分频器
#define AT91C_TWI_CKDIV           (0x7 << 16) // （TWI）时钟分频器
// --------TWI_SR:（TWI偏移：0x20）TWI状态寄存器--------
#define AT91C_TWI_TXCOMP          (0x1 <<  0) // （TWI）传输完成
#define AT91C_TWI_RXRDY           (0x1 <<  1) // （TWI）接收保持寄存器ReaDY
#define AT91C_TWI_TXRDY           (0x1 <<  2) // （TWI）发送保持寄存器ReaDY
#define AT91C_TWI_OVRE            (0x1 <<  6) // （TWI）超限错误
#define AT91C_TWI_UNRE            (0x1 <<  7) // （TWI）欠载错误
#define AT91C_TWI_NACK            (0x1 <<  8) // （TWI）未确认
// --------TWI_IER：（TWI偏移：0x24）TWI中断启用寄存器--------
// --------TWI_IDR:（TWI偏移：0x28）TWI中断禁用寄存器--------
// --------TWI_IR:（TWI偏移：0x2c）TWI中断掩码寄存器--------

// *****************************************************************************
//              PWMC通道接口的软件API定义
// *****************************************************************************
// ***AT91S_PWMC_CH结构中的寄存器偏移量***
#define PWMC_CMR        ( 0) // 信道模式寄存器
#define PWMC_CDTYR      ( 4) // 通道占空比寄存器
#define PWMC_CPRDR      ( 8) // 信道周期寄存器
#define PWMC_CCNTR      (12) // 信道计数器寄存器
#define PWMC_CUPDR      (16) // 信道更新寄存器
#define PWMC_Reserved   (20) // 保留
// --------PWMC_CMR：（PWMC_CH偏移：0x0）PWMC信道模式寄存器--------
#define AT91C_PWMC_CPRE           (0xF <<  0) // （PWMC_CH）信道预缩放器：PWMC_CLKx
#define 	AT91C_PWMC_CPRE_MCK                  (0x0) // (PWMC_CH) 
#define 	AT91C_PWMC_CPRE_MCKA                 (0xB) // (PWMC_CH) 
#define 	AT91C_PWMC_CPRE_MCKB                 (0xC) // (PWMC_CH) 
#define AT91C_PWMC_CALG           (0x1 <<  8) // （PWMC_CH）通道对齐
#define AT91C_PWMC_CPOL           (0x1 <<  9) // （PWMC_CH）通道极性
#define AT91C_PWMC_CPD            (0x1 << 10) // （PWMC_CH）信道更新周期
// --------PWMC_CDTYR：（PWMC_CH偏移：0x4）PWMC通道占空比寄存器--------
#define AT91C_PWMC_CDTY           (0x0 <<  0) // （PWMC_CH）通道占空比
// --------PWMC_CPRDR:（PWMC_CH偏移：0x8）PWMC信道周期寄存器--------
#define AT91C_PWMC_CPRD           (0x0 <<  0) // （PWMC_CH）信道周期
// --------PWMC_CCNTR：（PWMC_CH偏移：0xc）PWMC信道计数器寄存器--------
#define AT91C_PWMC_CCNT           (0x0 <<  0) // （PWMC_CH）信道计数器
// --------PWMC_CUPDR:（PWMC_CH偏移：0x10）PWMC信道更新寄存器--------
#define AT91C_PWMC_CUPD           (0x0 <<  0) // （PWMC_CH）信道更新

// *****************************************************************************
//              脉宽调制控制器接口的软件API定义
// *****************************************************************************
// ***AT91S_PWMC结构中的寄存器偏移***
#define PWMC_MR         ( 0) // PWMC模式寄存器
#define PWMC_ENA        ( 4) // PWMC启用寄存器
#define PWMC_DIS        ( 8) // PWMC禁用寄存器
#define PWMC_SR         (12) // PWMC状态寄存器
#define PWMC_IER        (16) // PWMC中断启用寄存器
#define PWMC_IDR        (20) // PWMC中断禁用寄存器
#define PWMC_IMR        (24) // PWMC中断掩码寄存器
#define PWMC_ISR        (28) // PWMC中断状态寄存器
#define PWMC_VR         (252) // PWMC版本寄存器
#define PWMC_CH         (512) // PWMC通道
// --------PWMC_MR：（PWMC偏移：0x0）PWMC模式寄存器--------
#define AT91C_PWMC_DIVA           (0xFF <<  0) // （PWMC）CLKA除法因子。
#define AT91C_PWMC_PREA           (0xF <<  8) // （PWMC）分频器输入时钟预分频器A
#define 	AT91C_PWMC_PREA_MCK                  (0x0 <<  8) // (PWMC) 
#define AT91C_PWMC_DIVB           (0xFF << 16) // （PWMC）CLKB除法因子。
#define AT91C_PWMC_PREB           (0xF << 24) // （PWMC）分频器输入时钟预分频器B
#define 	AT91C_PWMC_PREB_MCK                  (0x0 << 24) // (PWMC) 
// --------PWMC_ENA:（PWMC偏移：0x4）PWMC启用寄存器--------
#define AT91C_PWMC_CHID0          (0x1 <<  0) // （PWMC）信道ID 0
#define AT91C_PWMC_CHID1          (0x1 <<  1) // （PWMC）通道ID 1
#define AT91C_PWMC_CHID2          (0x1 <<  2) // （PWMC）信道ID 2
#define AT91C_PWMC_CHID3          (0x1 <<  3) // （PWMC）信道ID 3
// --------PWMC_DIS：（PWMC偏移：0x8）PWMC禁用寄存器--------
// --------PWMC_SR：（PWMC偏移：0xc）PWMC状态寄存器--------
// --------PWMC_IER:（PWMC偏移：0x10）PWMC中断启用寄存器--------
// --------PWMC_IDR:（PWMC偏移：0x14）PWMC中断禁用寄存器--------
// --------PWMC_IMR：（PWMC偏移：0x18）PWMC中断掩码寄存器--------
// --------PWMC_ISR:（PWMC偏移：0x1c）PWMC中断状态寄存器--------

// *****************************************************************************
//              USB设备接口的软件API定义
// *****************************************************************************
// ***AT91S_UDP结构中的寄存器偏移量***
#define UDP_NUM         ( 0) // 帧号寄存器
#define UDP_GLBSTATE    ( 4) // 全局状态寄存器
#define UDP_FADDR       ( 8) // 功能地址寄存器
#define UDP_IER         (16) // 中断启用寄存器
#define UDP_IDR         (20) // 中断禁用寄存器
#define UDP_IMR         (24) // 中断掩码寄存器
#define UDP_ISR         (28) // 中断状态寄存器
#define UDP_ICR         (32) // 中断清除寄存器
#define UDP_RSTEP       (40) // 重置终结点寄存器
#define UDP_CSR         (48) // 端点控制和状态寄存器
#define UDP_FDR         (80) // 端点FIFO数据寄存器
#define UDP_TXVC        (116) // 收发器控制寄存器
// --------UDP_FRM_NUM：（UDP偏移：0x0）USB帧号寄存器--------
#define AT91C_UDP_FRM_NUM         (0x7FF <<  0) // 分组字段格式中定义的（UDP）帧号
#define AT91C_UDP_FRM_ERR         (0x1 << 16) // （UDP）帧错误
#define AT91C_UDP_FRM_OK          (0x1 << 17) // （UDP）帧正常
// --------UDP_GLB_STATE:（UDP偏移：0x4）USB全局状态寄存器--------
#define AT91C_UDP_FADDEN          (0x1 <<  0) // （UDP）功能地址启用
#define AT91C_UDP_CONFG           (0x1 <<  1) // （UDP）已配置
#define AT91C_UDP_ESR             (0x1 <<  2) // （UDP）启用发送恢复
#define AT91C_UDP_RSMINPR         (0x1 <<  3) // （UDP）已将恢复发送到主机
#define AT91C_UDP_RMWUPE          (0x1 <<  4) // （UDP）远程唤醒启用
// --------UDP_FADDR:（UDP偏移量：0x8）USB功能地址寄存器--------
#define AT91C_UDP_FADD            (0xFF <<  0) // （UDP）函数地址值
#define AT91C_UDP_FEN             (0x1 <<  8) // （UDP）功能启用
// --------UDP_IER:（UDP偏移：0x10）USB中断启用寄存器--------
#define AT91C_UDP_EPINT0          (0x1 <<  0) // （UDP）端点0中断
#define AT91C_UDP_EPINT1          (0x1 <<  1) // （UDP）端点0中断
#define AT91C_UDP_EPINT2          (0x1 <<  2) // （UDP）端点2中断
#define AT91C_UDP_EPINT3          (0x1 <<  3) // （UDP）端点3中断
#define AT91C_UDP_EPINT4          (0x1 <<  4) // （UDP）端点4中断
#define AT91C_UDP_EPINT5          (0x1 <<  5) // （UDP）端点5中断
#define AT91C_UDP_RXSUSP          (0x1 <<  8) // （UDP）USB挂起中断
#define AT91C_UDP_RXRSM           (0x1 <<  9) // （UDP）USB恢复中断
#define AT91C_UDP_EXTRSM          (0x1 << 10) // （UDP）USB外部恢复中断
#define AT91C_UDP_SOFINT          (0x1 << 11) // （UDP）USB帧开始中断
#define AT91C_UDP_WAKEUP          (0x1 << 13) // （UDP）USB恢复中断
// --------UDP_IDR：（UDP偏移：0x14）USB中断禁用寄存器--------
// --------UDP_IMR：（UDP偏移：0x18）USB中断掩码寄存器--------
// --------UDP_ISR：（UDP偏移：0x1c）USB中断状态寄存器--------
#define AT91C_UDP_ENDBUSRES       (0x1 << 12) // （UDP）USB总线端重置中断
// --------UDP_ICR：（UDP偏移：0x20）USB中断清除寄存器--------
// --------UDP_RST_EP:（UDP偏移：0x28）USB重置端点寄存器--------
#define AT91C_UDP_EP0             (0x1 <<  0) // （UDP）重置终结点0
#define AT91C_UDP_EP1             (0x1 <<  1) // （UDP）重置终结点1
#define AT91C_UDP_EP2             (0x1 <<  2) // （UDP）重置终结点2
#define AT91C_UDP_EP3             (0x1 <<  3) // （UDP）重置终结点3
#define AT91C_UDP_EP4             (0x1 <<  4) // （UDP）重置终结点4
#define AT91C_UDP_EP5             (0x1 <<  5) // （UDP）重置终结点5
// --------UDP_CSR：（UDP偏移量：0x30）USB端点控制和状态寄存器--------
#define AT91C_UDP_TXCOMP          (0x1 <<  0) // （UDP）使用以前写入DPR的数据生成IN数据包
#define AT91C_UDP_RX_DATA_BK0     (0x1 <<  1) // （UDP）接收数据库0
#define AT91C_UDP_RXSETUP         (0x1 <<  2) // （UDP）向主机（控制端点）发送STALL
#define AT91C_UDP_ISOERROR        (0x1 <<  3) // （UDP）等时错误（等时端点）
#define AT91C_UDP_TXPKTRDY        (0x1 <<  4) // （UDP）传输数据包就绪
#define AT91C_UDP_FORCESTALL      (0x1 <<  5) // （UDP）强制暂停（由Control、Bulk和Isochronous端点使用）。
#define AT91C_UDP_RX_DATA_BK1     (0x1 <<  6) // （UDP）接收数据库1（仅由具有乒乓属性的端点使用）。
#define AT91C_UDP_DIR             (0x1 <<  7) // （UDP）传输方向
#define AT91C_UDP_EPTYPE          (0x7 <<  8) // （UDP）终结点类型
#define 	AT91C_UDP_EPTYPE_CTRL                 (0x0 <<  8) // （UDP）控制
#define 	AT91C_UDP_EPTYPE_ISO_OUT              (0x1 <<  8) // （UDP）等时输出
#define 	AT91C_UDP_EPTYPE_BULK_OUT             (0x2 <<  8) // （UDP）批量输出
#define 	AT91C_UDP_EPTYPE_INT_OUT              (0x3 <<  8) // （UDP）中断OUT
#define 	AT91C_UDP_EPTYPE_ISO_IN               (0x5 <<  8) // （UDP）同步输入
#define 	AT91C_UDP_EPTYPE_BULK_IN              (0x6 <<  8) // （UDP）批量输入
#define 	AT91C_UDP_EPTYPE_INT_IN               (0x7 <<  8) // （UDP）中断IN
#define AT91C_UDP_DTGLE           (0x1 << 11) // （UDP）数据切换
#define AT91C_UDP_EPEDS           (0x1 << 15) // （UDP）端点启用禁用
#define AT91C_UDP_RXBYTECNT       (0x7FF << 16) // （UDP）FIFO中可用的字节数
// --------UDP_TXVC:（UDP偏移：0x74）收发器控制寄存器--------
#define AT91C_UDP_TXVDIS          (0x1 <<  8) // (UDP) 
#define AT91C_UDP_PUON            (0x1 <<  9) // （UDP）上拉打开

// *****************************************************************************
//              定时器计数器通道接口的软件API定义
// *****************************************************************************
// ***AT91S_TC结构中的寄存器偏移量***
#define TC_CCR          ( 0) // 信道控制寄存器
#define TC_CMR          ( 4) // 信道模式寄存器（捕获模式/波形模式）
#define TC_CV           (16) // 计数器值
#define TC_RA           (20) // 寄存器A
#define TC_RB           (24) // 寄存器B
#define TC_RC           (28) // 寄存器C
#define TC_SR           (32) // 状态寄存器
#define TC_IER          (36) // 中断启用寄存器
#define TC_IDR          (40) // 中断禁用寄存器
#define TC_IMR          (44) // 中断掩码寄存器
// --------TC_CCR：（TC偏移：0x0）TC信道控制寄存器--------
#define AT91C_TC_CLKEN            (0x1 <<  0) // （TC）计数器时钟启用命令
#define AT91C_TC_CLKDIS           (0x1 <<  1) // （TC）计数器时钟禁用命令
#define AT91C_TC_SWTRG            (0x1 <<  2) // （TC）软件触发命令
// --------TC_CMR：（TC偏移：0x4）TC信道模式寄存器：捕获模式/波形模式--------
#define AT91C_TC_CLKS             (0x7 <<  0) // （TC）时钟选择
#define 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     (0x0) // （TC）选择的时钟：TIMER_DIV1_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     (0x1) // （TC）选择的时钟：TIMER_DIV2_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     (0x2) // （TC）选择的时钟：TIMER_DIV3_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     (0x3) // （TC）选择的时钟：TIMER_DIV4_Clock
#define 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     (0x4) // （TC）选择的时钟：TIMER_DIV5_Clock
#define 	AT91C_TC_CLKS_XC0                  (0x5) // （TC）选择的时钟：XC0
#define 	AT91C_TC_CLKS_XC1                  (0x6) // （TC）选择的时钟：XC1
#define 	AT91C_TC_CLKS_XC2                  (0x7) // （TC）选择的时钟：XC2
#define AT91C_TC_CLKI             (0x1 <<  3) // （TC）时钟反转
#define AT91C_TC_BURST            (0x3 <<  4) // （TC）突发信号选择
#define 	AT91C_TC_BURST_NONE                 (0x0 <<  4) // （TC）时钟不受外部信号门控
#define 	AT91C_TC_BURST_XC0                  (0x1 <<  4) // （TC）XC0与所选时钟“与”
#define 	AT91C_TC_BURST_XC1                  (0x2 <<  4) // （TC）XC1与所选时钟“与”
#define 	AT91C_TC_BURST_XC2                  (0x3 <<  4) // （TC）XC2与所选时钟“与”
#define AT91C_TC_CPCSTOP          (0x1 <<  6) // （TC）计数器时钟停止，RC比较
#define AT91C_TC_LDBSTOP          (0x1 <<  6) // （TC）计数器时钟因RB加载而停止
#define AT91C_TC_LDBDIS           (0x1 <<  7) // （TC）计数器时钟禁用，RB加载
#define AT91C_TC_CPCDIS           (0x1 <<  7) // 使用RC比较禁用（TC）计数器时钟
#define AT91C_TC_ETRGEDG          (0x3 <<  8) // （TC）外部触发边缘选择
#define 	AT91C_TC_ETRGEDG_NONE                 (0x0 <<  8) // （TC）边缘：无
#define 	AT91C_TC_ETRGEDG_RISING               (0x1 <<  8) // （TC）边缘：上升边缘
#define 	AT91C_TC_ETRGEDG_FALLING              (0x2 <<  8) // （TC）边缘：下降边缘
#define 	AT91C_TC_ETRGEDG_BOTH                 (0x3 <<  8) // （TC）边缘：每个边缘
#define AT91C_TC_EEVTEDG          (0x3 <<  8) // （TC）外部事件边缘选择
#define 	AT91C_TC_EEVTEDG_NONE                 (0x0 <<  8) // （TC）边缘：无
#define 	AT91C_TC_EEVTEDG_RISING               (0x1 <<  8) // （TC）边缘：上升边缘
#define 	AT91C_TC_EEVTEDG_FALLING              (0x2 <<  8) // （TC）边缘：下降边缘
#define 	AT91C_TC_EEVTEDG_BOTH                 (0x3 <<  8) // （TC）边缘：每个边缘
#define AT91C_TC_ABETRG           (0x1 << 10) // （TC）TIOA或TIOB外部触发选择
#define AT91C_TC_EEVT             (0x3 << 10) // （TC）外部事件选择
#define 	AT91C_TC_EEVT_TIOB                 (0x0 << 10) // （TC）选择为外部事件的信号：TIOB TIOB方向：输入
#define 	AT91C_TC_EEVT_XC0                  (0x1 << 10) // （TC）选择为外部事件的信号：XC0 TIOB方向：输出
#define 	AT91C_TC_EEVT_XC1                  (0x2 << 10) // （TC）选择为外部事件的信号：XC1 TIOB方向：输出
#define 	AT91C_TC_EEVT_XC2                  (0x3 << 10) // （TC）选择为外部事件的信号：XC2 TIOB方向：输出
#define AT91C_TC_ENETRG           (0x1 << 12) // （TC）外部事件触发器启用
#define AT91C_TC_WAVESEL          (0x3 << 13) // （TC）波形选择
#define 	AT91C_TC_WAVESEL_UP                   (0x0 << 13) // RC比较上无自动触发的（TC）UP模式
#define 	AT91C_TC_WAVESEL_UPDOWN               (0x1 << 13) // （TC）UPDOWN模式，无RC比较自动触发
#define 	AT91C_TC_WAVESEL_UP_AUTO              (0x2 << 13) // RC比较自动触发的（TC）UP模式
#define 	AT91C_TC_WAVESEL_UPDOWN_AUTO          (0x3 << 13) // （TC）UPDOWN模式，RC比较时自动触发
#define AT91C_TC_CPCTRG           (0x1 << 14) // （TC）RC比较触发启用
#define AT91C_TC_WAVE             (0x1 << 15) // (TC) 
#define AT91C_TC_LDRA             (0x3 << 16) // （TC）RA加载选择
#define 	AT91C_TC_LDRA_NONE                 (0x0 << 16) // （TC）边缘：无
#define 	AT91C_TC_LDRA_RISING               (0x1 << 16) // （TC）边缘：TIOA的上升边缘
#define 	AT91C_TC_LDRA_FALLING              (0x2 << 16) // （TC）边缘：TIOA的下降边缘
#define 	AT91C_TC_LDRA_BOTH                 (0x3 << 16) // （TC）边缘：TIOA的每个边缘
#define AT91C_TC_ACPA             (0x3 << 16) // （TC）RA比较对TIOA的影响
#define 	AT91C_TC_ACPA_NONE                 (0x0 << 16) // （TC）影响：无
#define 	AT91C_TC_ACPA_SET                  (0x1 << 16) // （TC）效果：设置
#define 	AT91C_TC_ACPA_CLEAR                (0x2 << 16) // （TC）效果：清晰
#define 	AT91C_TC_ACPA_TOGGLE               (0x3 << 16) // （TC）效果：切换
#define AT91C_TC_LDRB             (0x3 << 18) // （TC）RB加载选择
#define 	AT91C_TC_LDRB_NONE                 (0x0 << 18) // （TC）边缘：无
#define 	AT91C_TC_LDRB_RISING               (0x1 << 18) // （TC）边缘：TIOA的上升边缘
#define 	AT91C_TC_LDRB_FALLING              (0x2 << 18) // （TC）边缘：TIOA的下降边缘
#define 	AT91C_TC_LDRB_BOTH                 (0x3 << 18) // （TC）边缘：TIOA的每个边缘
#define AT91C_TC_ACPC             (0x3 << 18) // （TC）RC比较对TIOA的影响
#define 	AT91C_TC_ACPC_NONE                 (0x0 << 18) // （TC）影响：无
#define 	AT91C_TC_ACPC_SET                  (0x1 << 18) // （TC）效果：设置
#define 	AT91C_TC_ACPC_CLEAR                (0x2 << 18) // （TC）效果：清晰
#define 	AT91C_TC_ACPC_TOGGLE               (0x3 << 18) // （TC）效果：切换
#define AT91C_TC_AEEVT            (0x3 << 20) // （TC）外部事件对TIOA的影响
#define 	AT91C_TC_AEEVT_NONE                 (0x0 << 20) // （TC）影响：无
#define 	AT91C_TC_AEEVT_SET                  (0x1 << 20) // （TC）效果：设置
#define 	AT91C_TC_AEEVT_CLEAR                (0x2 << 20) // （TC）效果：清晰
#define 	AT91C_TC_AEEVT_TOGGLE               (0x3 << 20) // （TC）效果：切换
#define AT91C_TC_ASWTRG           (0x3 << 22) // （TC）软件触发对TIOA的影响
#define 	AT91C_TC_ASWTRG_NONE                 (0x0 << 22) // （TC）影响：无
#define 	AT91C_TC_ASWTRG_SET                  (0x1 << 22) // （TC）效果：设置
#define 	AT91C_TC_ASWTRG_CLEAR                (0x2 << 22) // （TC）效果：清晰
#define 	AT91C_TC_ASWTRG_TOGGLE               (0x3 << 22) // （TC）效果：切换
#define AT91C_TC_BCPB             (0x3 << 24) // （TC）RB比较对TIOB的影响
#define 	AT91C_TC_BCPB_NONE                 (0x0 << 24) // （TC）影响：无
#define 	AT91C_TC_BCPB_SET                  (0x1 << 24) // （TC）效果：设置
#define 	AT91C_TC_BCPB_CLEAR                (0x2 << 24) // （TC）效果：清晰
#define 	AT91C_TC_BCPB_TOGGLE               (0x3 << 24) // （TC）效果：切换
#define AT91C_TC_BCPC             (0x3 << 26) // （TC）RC比较对TIOB的影响
#define 	AT91C_TC_BCPC_NONE                 (0x0 << 26) // （TC）影响：无
#define 	AT91C_TC_BCPC_SET                  (0x1 << 26) // （TC）效果：设置
#define 	AT91C_TC_BCPC_CLEAR                (0x2 << 26) // （TC）效果：清晰
#define 	AT91C_TC_BCPC_TOGGLE               (0x3 << 26) // （TC）效果：切换
#define AT91C_TC_BEEVT            (0x3 << 28) // （TC）外部事件对TIOB的影响
#define 	AT91C_TC_BEEVT_NONE                 (0x0 << 28) // （TC）影响：无
#define 	AT91C_TC_BEEVT_SET                  (0x1 << 28) // （TC）效果：设置
#define 	AT91C_TC_BEEVT_CLEAR                (0x2 << 28) // （TC）效果：清晰
#define 	AT91C_TC_BEEVT_TOGGLE               (0x3 << 28) // （TC）效果：切换
#define AT91C_TC_BSWTRG           (0x3 << 30) // （TC）软件触发对TIOB的影响
#define 	AT91C_TC_BSWTRG_NONE                 (0x0 << 30) // （TC）影响：无
#define 	AT91C_TC_BSWTRG_SET                  (0x1 << 30) // （TC）效果：设置
#define 	AT91C_TC_BSWTRG_CLEAR                (0x2 << 30) // （TC）效果：清晰
#define 	AT91C_TC_BSWTRG_TOGGLE               (0x3 << 30) // （TC）效果：切换
// --------TC_SR：（TC偏移：0x20）TC信道状态寄存器--------
#define AT91C_TC_COVFS            (0x1 <<  0) // （TC）计数器溢出
#define AT91C_TC_LOVRS            (0x1 <<  1) // （TC）负载超限
#define AT91C_TC_CPAS             (0x1 <<  2) // （TC）RA比较
#define AT91C_TC_CPBS             (0x1 <<  3) // （TC）RB比较
#define AT91C_TC_CPCS             (0x1 <<  4) // （TC）RC比较
#define AT91C_TC_LDRAS            (0x1 <<  5) // （TC）RA加载
#define AT91C_TC_LDRBS            (0x1 <<  6) // （TC）RB加载
#define AT91C_TC_ETRGS            (0x1 <<  7) // （TC）外部触发器
#define AT91C_TC_CLKSTA           (0x1 << 16) // （TC）时钟启用
#define AT91C_TC_MTIOA            (0x1 << 17) // （TC）TIOA后视镜
#define AT91C_TC_MTIOB            (0x1 << 18) // （TC）TIOA后视镜
// --------TC_IER：（TC偏移：0x24）TC通道中断启用寄存器--------
// --------TC_IDR：（TC偏移：0x28）TC通道中断禁用寄存器--------
// --------TC_IMR：（TC偏移：0x2c）TC通道中断掩码寄存器--------

// *****************************************************************************
//              定时器计数器接口的软件API定义
// *****************************************************************************
// ***AT91S_TCB结构中的寄存器偏移量***
#define TCB_TC0         ( 0) // TC通道0
#define TCB_TC1         (64) // TC通道1
#define TCB_TC2         (128) // TC通道2
#define TCB_BCR         (192) // TC块控制寄存器
#define TCB_BMR         (196) // TC块模式寄存器
// --------TCB_BCR：（TCB偏移量：0xc0）TC块控制寄存器--------
#define AT91C_TCB_SYNC            (0x1 <<  0) // （TCB）同步命令
// --------TCB_BMR：（TCB偏移量：0xc4）TC块模式寄存器--------
#define AT91C_TCB_TC0XC0S         (0x3 <<  0) // （TCB）外部时钟信号0选择
#define 	AT91C_TCB_TC0XC0S_TCLK0                (0x0) // （TCB）TCLK0连接到XC0
#define 	AT91C_TCB_TC0XC0S_NONE                 (0x1) // （TCB）无信号连接到XC0
#define 	AT91C_TCB_TC0XC0S_TIOA1                (0x2) // （TCB）TIOA1连接到XC0
#define 	AT91C_TCB_TC0XC0S_TIOA2                (0x3) // （TCB）TIOA2连接到XC0
#define AT91C_TCB_TC1XC1S         (0x3 <<  2) // （TCB）外部时钟信号1选择
#define 	AT91C_TCB_TC1XC1S_TCLK1                (0x0 <<  2) // （TCB）TCLK1连接到XC1
#define 	AT91C_TCB_TC1XC1S_NONE                 (0x1 <<  2) // （TCB）无信号连接到XC1
#define 	AT91C_TCB_TC1XC1S_TIOA0                (0x2 <<  2) // （TCB）TIOA0连接到XC1
#define 	AT91C_TCB_TC1XC1S_TIOA2                (0x3 <<  2) // （TCB）TIOA2连接到XC1
#define AT91C_TCB_TC2XC2S         (0x3 <<  4) // （TCB）外部时钟信号2选择
#define 	AT91C_TCB_TC2XC2S_TCLK2                (0x0 <<  4) // （TCB）TCLK2连接到XC2
#define 	AT91C_TCB_TC2XC2S_NONE                 (0x1 <<  4) // （TCB）无信号连接到XC2
#define 	AT91C_TCB_TC2XC2S_TIOA0                (0x2 <<  4) // （TCB）TIOA0连接到XC2
#define 	AT91C_TCB_TC2XC2S_TIOA1                (0x3 <<  4) // （TCB）TIOA2连接到XC2

// *****************************************************************************
//              控制区域网络邮箱接口的软件API定义
// *****************************************************************************
// ***AT91S_CAN_MB结构中的寄存器偏移量***
#define CAN_MB_MMR      ( 0) // 邮箱模式寄存器
#define CAN_MB_MAM      ( 4) // 邮箱接受掩码寄存器
#define CAN_MB_MID      ( 8) // 邮箱ID注册
#define CAN_MB_MFID     (12) // 邮箱系列ID注册
#define CAN_MB_MSR      (16) // 邮箱状态寄存器
#define CAN_MB_MDL      (20) // MailBox数据低寄存器
#define CAN_MB_MDH      (24) // 邮箱数据高位寄存器
#define CAN_MB_MCR      (28) // 邮箱控制寄存器
// --------CAN_MMR：（CAN_MB偏移：0x0）CAN消息模式寄存器--------
#define AT91C_CAN_MTIMEMARK       (0xFFFF <<  0) // （CAN_MB）邮箱时间标记
#define AT91C_CAN_PRIOR           (0xF << 16) // （CAN_MB）邮箱优先级
#define AT91C_CAN_MOT             (0x7 << 24) // （CAN_MB）邮箱对象类型
#define 	AT91C_CAN_MOT_DIS                  (0x0 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_RX                   (0x1 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_RXOVERWRITE          (0x2 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_TX                   (0x3 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_CONSUMER             (0x4 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_PRODUCER             (0x5 << 24) // (CAN_MB) 
// --------CAN_MAM：（CAN_MB偏移：0x4）CAN消息接受掩码寄存器--------
#define AT91C_CAN_MIDvB           (0x3FFFF <<  0) // （CAN_MB）扩展模式中标识符的互补位
#define AT91C_CAN_MIDvA           (0x7FF << 18) // （CAN_MB）标准帧模式标识符
#define AT91C_CAN_MIDE            (0x1 << 29) // （CAN_MB）标识符版本
// --------CAN_MID:（CAN_MB偏移：0x8）CAN消息ID寄存器--------
// --------CAN_MFID：（CAN_MB偏移：0xc）CAN消息系列ID寄存器--------
// --------CAN_MSR:（CAN_MB偏移：0x10）CAN消息状态寄存器--------
#define AT91C_CAN_MTIMESTAMP      (0xFFFF <<  0) // （CAN_MB）计时器值
#define AT91C_CAN_MDLC            (0xF << 16) // （CAN_MB）邮箱数据长度代码
#define AT91C_CAN_MRTR            (0x1 << 20) // （CAN_MB）邮箱远程传输请求
#define AT91C_CAN_MABT            (0x1 << 22) // （CAN_MB）邮箱消息中止
#define AT91C_CAN_MRDY            (0x1 << 23) // （CAN_MB）邮箱就绪
#define AT91C_CAN_MMI             (0x1 << 24) // （CAN_MB）邮箱消息已忽略
// --------CAN_MDL:（CAN_MB偏移：0x14）CAN消息数据低寄存器--------
// --------CAN_MDH:（CAN_MB偏移：0x18）CAN消息数据高位寄存器--------
// --------CAN_MCR：（CAN_MB偏移：0x1c）CAN消息控制寄存器--------
#define AT91C_CAN_MACR            (0x1 << 22) // （CAN_MB）中止邮箱请求
#define AT91C_CAN_MTCR            (0x1 << 23) // （CAN_MB）邮箱传输命令

// *****************************************************************************
//              控制区域网络接口的软件API定义
// *****************************************************************************
// ***AT91S_CAN结构中的寄存器偏移***
#define CAN_MR          ( 0) // 模式寄存器
#define CAN_IER         ( 4) // 中断启用寄存器
#define CAN_IDR         ( 8) // 中断禁用寄存器
#define CAN_IMR         (12) // 中断掩码寄存器
#define CAN_SR          (16) // 状态寄存器
#define CAN_BR          (20) // 波特率寄存器
#define CAN_TIM         (24) // 计时器寄存器
#define CAN_TIMESTP     (28) // 时间戳寄存器
#define CAN_ECR         (32) // 错误计数器寄存器
#define CAN_TCR         (36) // 传输命令寄存器
#define CAN_ACR         (40) // 中止命令寄存器
#define CAN_VR          (252) // 版本寄存器
#define CAN_MB0         (512) // CAN邮箱0
#define CAN_MB1         (544) // CAN邮箱1
#define CAN_MB2         (576) // CAN邮箱2
#define CAN_MB3         (608) // CAN邮箱3
#define CAN_MB4         (640) // CAN邮箱4
#define CAN_MB5         (672) // CAN邮箱5
#define CAN_MB6         (704) // CAN邮箱6
#define CAN_MB7         (736) // CAN邮箱7
#define CAN_MB8         (768) // CAN邮箱8
#define CAN_MB9         (800) // CAN邮箱9
#define CAN_MB10        (832) // CAN邮箱10
#define CAN_MB11        (864) // CAN邮箱11
#define CAN_MB12        (896) // CAN邮箱12
#define CAN_MB13        (928) // CAN邮箱13
#define CAN_MB14        (960) // CAN邮箱14
#define CAN_MB15        (992) // CAN邮箱15
// --------CAN_MR：（CAN偏移：0x0）CAN模式寄存器--------
#define AT91C_CAN_CANEN           (0x1 <<  0) // （CAN）CAN控制器启用
#define AT91C_CAN_LPM             (0x1 <<  1) // （CAN）禁用/启用低功率模式
#define AT91C_CAN_ABM             (0x1 <<  2) // （CAN）禁用/启用自动驾驶/监听模式
#define AT91C_CAN_OVL             (0x1 <<  3) // （CAN）禁用/启用过载框架
#define AT91C_CAN_TEOF            (0x1 <<  4) // （CAN）帧两端的时间戳消息
#define AT91C_CAN_TTM             (0x1 <<  5) // （CAN）禁用/启用时间触发模式
#define AT91C_CAN_TIMFRZ          (0x1 <<  6) // （CAN）启用计时器冻结
#define AT91C_CAN_DRPT            (0x1 <<  7) // （CAN）禁用重复
// --------CAN_IER：（CAN偏移：0x4）CAN中断启用寄存器--------
#define AT91C_CAN_MB0             (0x1 <<  0) // （CAN）邮箱0标志
#define AT91C_CAN_MB1             (0x1 <<  1) // （CAN）邮箱1标志
#define AT91C_CAN_MB2             (0x1 <<  2) // （CAN）邮箱2标志
#define AT91C_CAN_MB3             (0x1 <<  3) // （CAN）邮箱3标志
#define AT91C_CAN_MB4             (0x1 <<  4) // （CAN）邮箱4标志
#define AT91C_CAN_MB5             (0x1 <<  5) // （CAN）邮箱5标志
#define AT91C_CAN_MB6             (0x1 <<  6) // （CAN）邮箱6标志
#define AT91C_CAN_MB7             (0x1 <<  7) // （CAN）邮箱7标志
#define AT91C_CAN_MB8             (0x1 <<  8) // （CAN）邮箱8标志
#define AT91C_CAN_MB9             (0x1 <<  9) // （CAN）邮箱9标志
#define AT91C_CAN_MB10            (0x1 << 10) // （CAN）邮箱10标志
#define AT91C_CAN_MB11            (0x1 << 11) // （CAN）邮箱11标志
#define AT91C_CAN_MB12            (0x1 << 12) // （CAN）邮箱12标志
#define AT91C_CAN_MB13            (0x1 << 13) // （CAN）邮箱13标志
#define AT91C_CAN_MB14            (0x1 << 14) // （CAN）邮箱14标志
#define AT91C_CAN_MB15            (0x1 << 15) // （CAN）邮箱15标志
#define AT91C_CAN_ERRA            (0x1 << 16) // （CAN）错误激活模式标志
#define AT91C_CAN_WARN            (0x1 << 17) // （CAN）警告限制标志
#define AT91C_CAN_ERRP            (0x1 << 18) // （CAN）错误被动模式标志
#define AT91C_CAN_BOFF            (0x1 << 19) // （CAN）总线关闭模式标志
#define AT91C_CAN_SLEEP           (0x1 << 20) // （CAN）休眠标志
#define AT91C_CAN_WAKEUP          (0x1 << 21) // （CAN）唤醒标志
#define AT91C_CAN_TOVF            (0x1 << 22) // （CAN）计时器溢出标志
#define AT91C_CAN_TSTP            (0x1 << 23) // （CAN）时间戳标志
#define AT91C_CAN_CERR            (0x1 << 24) // （CAN）CRC错误
#define AT91C_CAN_SERR            (0x1 << 25) // （CAN）填充错误
#define AT91C_CAN_AERR            (0x1 << 26) // （CAN）确认错误
#define AT91C_CAN_FERR            (0x1 << 27) // （CAN）表单错误
#define AT91C_CAN_BERR            (0x1 << 28) // （CAN）位错误
// --------CAN_IDR:（CAN偏移：0x8）CAN中断禁用寄存器--------
// --------CAN_IMR：（CAN偏移：0xc）CAN中断掩码寄存器--------
// --------CAN_SR：（CAN偏移：0x10）CAN状态寄存器--------
#define AT91C_CAN_RBSY            (0x1 << 29) // （CAN）接收器忙
#define AT91C_CAN_TBSY            (0x1 << 30) // （CAN）发射器忙
#define AT91C_CAN_OVLY            (0x1 << 31) // （CAN）过载忙
// --------CAN_BR：（CAN偏移：0x14）CAN波特率寄存器--------
#define AT91C_CAN_PHASE2          (0x7 <<  0) // （CAN）阶段2段
#define AT91C_CAN_PHASE1          (0x7 <<  4) // （CAN）阶段1段
#define AT91C_CAN_PROPAG          (0x7 <<  8) // （CAN）编程时间段
#define AT91C_CAN_SYNC            (0x3 << 12) // （CAN）重新同步跳跃宽度段
#define AT91C_CAN_BRP             (0x7F << 16) // （CAN）波特率预分频器
#define AT91C_CAN_SMP             (0x1 << 24) // （CAN）采样模式
// --------CAN_TIM:（CAN偏移：0x18）CAN计时器寄存器--------
#define AT91C_CAN_TIMER           (0xFFFF <<  0) // （CAN）计时器字段
// --------CAN_TIMESTP:（CAN偏移：0x1c）CAN时间戳寄存器--------
// --------CAN_ECR:（CAN偏移：0x20）CAN错误计数器寄存器--------
#define AT91C_CAN_REC             (0xFF <<  0) // （CAN）接收错误计数器
#define AT91C_CAN_TEC             (0xFF << 16) // （CAN）传输错误计数器
// --------CAN_TCR：（CAN偏移：0x24）CAN传输命令寄存器--------
#define AT91C_CAN_TIMRST          (0x1 << 31) // （CAN）计时器重置字段
// --------CAN_ACR:（CAN偏移：0x28）CAN中止命令寄存器--------

// *****************************************************************************
//              以太网MAC 10/100的软件API定义
// *****************************************************************************
// ***AT91S_EMAC结构中的寄存器偏移量***
#define EMAC_NCR        ( 0) // 网络控制寄存器
#define EMAC_NCFGR      ( 4) // 网络配置寄存器
#define EMAC_NSR        ( 8) // 网络状态寄存器
#define EMAC_TSR        (20) // 传输状态寄存器
#define EMAC_RBQP       (24) // 接收缓冲区队列指针
#define EMAC_TBQP       (28) // 传输缓冲区队列指针
#define EMAC_RSR        (32) // 接收状态寄存器
#define EMAC_ISR        (36) // 中断状态寄存器
#define EMAC_IER        (40) // 中断启用寄存器
#define EMAC_IDR        (44) // 中断禁用寄存器
#define EMAC_IMR        (48) // 中断掩码寄存器
#define EMAC_MAN        (52) // PHY维护寄存器
#define EMAC_PTR        (56) // 暂停时间寄存器
#define EMAC_PFR        (60) // 暂停帧接收寄存器
#define EMAC_FTO        (64) // 帧发送OK寄存器
#define EMAC_SCF        (68) // 单碰撞帧寄存器
#define EMAC_MCF        (72) // 多冲突帧寄存器
#define EMAC_FRO        (76) // 帧接收OK寄存器
#define EMAC_FCSE       (80) // 帧检查序列错误寄存器
#define EMAC_ALE        (84) // 对齐错误寄存器
#define EMAC_DTF        (88) // 延迟传输帧寄存器
#define EMAC_LCOL       (92) // 延迟碰撞登记
#define EMAC_ECOL       (96) // 过度碰撞寄存器
#define EMAC_TUND       (100) // 传输欠载错误寄存器
#define EMAC_CSE        (104) // 载波检测错误寄存器
#define EMAC_RRE        (108) // 接收资源错误寄存器
#define EMAC_ROV        (112) // 接收溢出错误寄存器
#define EMAC_RSE        (116) // 接收符号错误寄存器
#define EMAC_ELE        (120) // 超长错误寄存器
#define EMAC_RJA        (124) // 接收Jabbers注册
#define EMAC_USF        (128) // 缩小帧寄存器
#define EMAC_STE        (132) // SQE测试错误寄存器
#define EMAC_RLE        (136) // 接收长度字段不匹配寄存器
#define EMAC_TPF        (140) // 发送的暂停帧寄存器
#define EMAC_HRB        (144) // 哈希地址底部[31:0]
#define EMAC_HRT        (148) // 哈希地址顶部[63:32]
#define EMAC_SA1L       (152) // 特定地址1底部，前4字节
#define EMAC_SA1H       (156) // 特定地址1顶部，最后2字节
#define EMAC_SA2L       (160) // 特定地址2底部，前4字节
#define EMAC_SA2H       (164) // 特定地址2顶部，最后2个字节
#define EMAC_SA3L       (168) // 特定地址3底部，前4字节
#define EMAC_SA3H       (172) // 特定地址3顶部，最后2个字节
#define EMAC_SA4L       (176) // 特定地址4底部，前4字节
#define EMAC_SA4H       (180) // 特定地址4顶部，最后2个字节
#define EMAC_TID        (184) // 类型ID检查寄存器
#define EMAC_TPQ        (188) // 传输暂停量子寄存器
#define EMAC_USRIO      (192) // 用户输入/输出寄存器
#define EMAC_WOL        (196) // LAN唤醒寄存器
#define EMAC_REV        (252) // 修订登记簿
// --------EMAC_NCR：（EMAC偏移：0x0）--------
#define AT91C_EMAC_LB             (0x1 <<  0) // （EMAC）环回。可选择的设置后，回送信号处于高电平。
#define AT91C_EMAC_LLB            (0x1 <<  1) // （EMAC）本地环回。
#define AT91C_EMAC_RE             (0x1 <<  2) // （EMAC）接收启用。
#define AT91C_EMAC_TE             (0x1 <<  3) // （EMAC）发射启用。
#define AT91C_EMAC_MPE            (0x1 <<  4) // （EMAC）管理端口启用。
#define AT91C_EMAC_CLRSTAT        (0x1 <<  5) // （EMAC）清除统计寄存器。
#define AT91C_EMAC_INCSTAT        (0x1 <<  6) // （EMAC）增量统计寄存器。
#define AT91C_EMAC_WESTAT         (0x1 <<  7) // （EMAC）统计寄存器的写入启用。
#define AT91C_EMAC_BP             (0x1 <<  8) // （EMAC）背压。
#define AT91C_EMAC_TSTART         (0x1 <<  9) // （EMAC）开始传输。
#define AT91C_EMAC_THALT          (0x1 << 10) // （EMAC）传输停止。
#define AT91C_EMAC_TPFR           (0x1 << 11) // （EMAC）发送暂停帧
#define AT91C_EMAC_TZQ            (0x1 << 12) // （EMAC）发送零量子暂停帧
// --------EMAC_NCFGR：（EMAC偏移：0x4）网络配置寄存器--------
#define AT91C_EMAC_SPD            (0x1 <<  0) // （EMAC）速度。
#define AT91C_EMAC_FD             (0x1 <<  1) // （EMAC）全双工。
#define AT91C_EMAC_JFRAME         (0x1 <<  3) // （EMAC）巨型框架。
#define AT91C_EMAC_CAF            (0x1 <<  4) // （EMAC）复制所有帧。
#define AT91C_EMAC_NBC            (0x1 <<  5) // （EMAC）没有广播。
#define AT91C_EMAC_MTI            (0x1 <<  6) // （EMAC）多播哈希事件启用
#define AT91C_EMAC_UNI            (0x1 <<  7) // （EMAC）启用单播哈希。
#define AT91C_EMAC_BIG            (0x1 <<  8) // （EMAC）接收1522字节。
#define AT91C_EMAC_EAE            (0x1 <<  9) // （EMAC）外部地址匹配启用。
#define AT91C_EMAC_CLK            (0x3 << 10) // (EMAC) 
#define 	AT91C_EMAC_CLK_HCLK_8               (0x0 << 10) // （EMAC）HCLK除以8
#define 	AT91C_EMAC_CLK_HCLK_16              (0x1 << 10) // （EMAC）HCLK除以16
#define 	AT91C_EMAC_CLK_HCLK_32              (0x2 << 10) // （EMAC）HCLK除以32
#define 	AT91C_EMAC_CLK_HCLK_64              (0x3 << 10) // （EMAC）HCLK除以64
#define AT91C_EMAC_RTY            (0x1 << 12) // (EMAC) 
#define AT91C_EMAC_PAE            (0x1 << 13) // (EMAC) 
#define AT91C_EMAC_RBOF           (0x3 << 14) // (EMAC) 
#define 	AT91C_EMAC_RBOF_OFFSET_0             (0x0 << 14) // （EMAC）从接收缓冲区开始无偏移
#define 	AT91C_EMAC_RBOF_OFFSET_1             (0x1 << 14) // （EMAC）从接收缓冲区开始的一个字节偏移
#define 	AT91C_EMAC_RBOF_OFFSET_2             (0x2 << 14) // （EMAC）从接收缓冲区开始偏移两个字节
#define 	AT91C_EMAC_RBOF_OFFSET_3             (0x3 << 14) // （EMAC）从接收缓冲区开始偏移三个字节
#define AT91C_EMAC_RLCE           (0x1 << 16) // （EMAC）接收长度字段检查启用
#define AT91C_EMAC_DRFCS          (0x1 << 17) // （EMAC）放弃接收FCS
#define AT91C_EMAC_EFRHD          (0x1 << 18) // (EMAC) 
#define AT91C_EMAC_IRXFCS         (0x1 << 19) // （EMAC）忽略RX FCS
// --------EMAC_NSR:（EMAC偏移量：0x8）网络状态寄存器--------
#define AT91C_EMAC_LINKR          (0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_MDIO           (0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_IDLE           (0x1 <<  2) // (EMAC) 
// --------EMAC_TSR：（EMAC偏移：0x14）传输状态寄存器--------
#define AT91C_EMAC_UBR            (0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_COL            (0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_RLES           (0x1 <<  2) // (EMAC) 
#define AT91C_EMAC_TGO            (0x1 <<  3) // （EMAC）发送开始
#define AT91C_EMAC_BEX            (0x1 <<  4) // （EMAC）中间帧缓冲区耗尽
#define AT91C_EMAC_COMP           (0x1 <<  5) // (EMAC) 
#define AT91C_EMAC_UND            (0x1 <<  6) // (EMAC) 
// --------EMAC_RSR：（EMAC偏移：0x20）接收状态寄存器--------
#define AT91C_EMAC_BNA            (0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_REC            (0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_OVR            (0x1 <<  2) // (EMAC) 
// --------EMAC_ISR：（EMAC偏移：0x24）中断状态寄存器--------
#define AT91C_EMAC_MFD            (0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_RCOMP          (0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_RXUBR          (0x1 <<  2) // (EMAC) 
#define AT91C_EMAC_TXUBR          (0x1 <<  3) // (EMAC) 
#define AT91C_EMAC_TUNDR          (0x1 <<  4) // (EMAC) 
#define AT91C_EMAC_RLEX           (0x1 <<  5) // (EMAC) 
#define AT91C_EMAC_TXERR          (0x1 <<  6) // (EMAC) 
#define AT91C_EMAC_TCOMP          (0x1 <<  7) // (EMAC) 
#define AT91C_EMAC_LINK           (0x1 <<  9) // (EMAC) 
#define AT91C_EMAC_ROVR           (0x1 << 10) // (EMAC) 
#define AT91C_EMAC_HRESP          (0x1 << 11) // (EMAC) 
#define AT91C_EMAC_PFRE           (0x1 << 12) // (EMAC) 
#define AT91C_EMAC_PTZ            (0x1 << 13) // (EMAC) 
// --------EMAC_IER:（EMAC偏移：0x28）中断启用寄存器--------
// --------EMAC_IDR：（EMAC偏移：0x2c）中断禁用寄存器--------
// --------EMAC_IMR：（EMAC偏移：0x30）中断掩码寄存器--------
// --------EMAC_MAN：（EMAC偏移：0x34）PHY维护寄存器--------
#define AT91C_EMAC_DATA           (0xFFFF <<  0) // (EMAC) 
#define AT91C_EMAC_CODE           (0x3 << 16) // (EMAC) 
#define AT91C_EMAC_REGA           (0x1F << 18) // (EMAC) 
#define AT91C_EMAC_PHYA           (0x1F << 23) // (EMAC) 
#define AT91C_EMAC_RW             (0x3 << 28) // (EMAC) 
#define AT91C_EMAC_SOF            (0x3 << 30) // (EMAC) 
// --------EMAC_USRIO：（EMAC偏移：0xc0）用户输入输出寄存器--------
#define AT91C_EMAC_RMII           (0x1 <<  0) // （EMAC）减少MII
#define AT91C_EMAC_CLKEN          (0x1 <<  1) // （EMAC）时钟启用
// --------EMAC_WOL：（EMAC偏移：0xc4）LAN唤醒寄存器--------
#define AT91C_EMAC_IP             (0xFFFF <<  0) // （EMAC）ARP请求IP地址
#define AT91C_EMAC_MAG            (0x1 << 16) // （EMAC）魔术包事件启用
#define AT91C_EMAC_ARP            (0x1 << 17) // （EMAC）ARP请求事件启用
#define AT91C_EMAC_SA1            (0x1 << 18) // （EMAC）特定地址寄存器1事件启用
// --------EMAC_REV：（EMAC偏移：0xfc）修订寄存器--------
#define AT91C_EMAC_REVREF         (0xFFFF <<  0) // (EMAC) 
#define AT91C_EMAC_PARTREF        (0xFFFF << 16) // (EMAC) 

// *****************************************************************************
//              模数转换器的软件API定义
// *****************************************************************************
// ***AT91S_ADC结构中的寄存器偏移***
#define ADC_CR          ( 0) // ADC控制寄存器
#define ADC_MR          ( 4) // ADC模式寄存器
#define ADC_CHER        (16) // ADC通道启用寄存器
#define ADC_CHDR        (20) // ADC通道禁用寄存器
#define ADC_CHSR        (24) // ADC通道状态寄存器
#define ADC_SR          (28) // ADC状态寄存器
#define ADC_LCDR        (32) // ADC上次转换的数据寄存器
#define ADC_IER         (36) // ADC中断启用寄存器
#define ADC_IDR         (40) // ADC中断禁用寄存器
#define ADC_IMR         (44) // ADC中断掩码寄存器
#define ADC_CDR0        (48) // ADC通道数据寄存器0
#define ADC_CDR1        (52) // ADC通道数据寄存器1
#define ADC_CDR2        (56) // ADC通道数据寄存器2
#define ADC_CDR3        (60) // ADC通道数据寄存器3
#define ADC_CDR4        (64) // ADC通道数据寄存器4
#define ADC_CDR5        (68) // ADC通道数据寄存器5
#define ADC_CDR6        (72) // ADC通道数据寄存器6
#define ADC_CDR7        (76) // ADC通道数据寄存器7
#define ADC_RPR         (256) // 接收指针寄存器
#define ADC_RCR         (260) // 接收计数器寄存器
#define ADC_TPR         (264) // 发送指针寄存器
#define ADC_TCR         (268) // 发送计数器寄存器
#define ADC_RNPR        (272) // 接收下一个指针寄存器
#define ADC_RNCR        (276) // 接收下一计数器寄存器
#define ADC_TNPR        (280) // 发送下一指针寄存器
#define ADC_TNCR        (284) // 发送下一计数器寄存器
#define ADC_PTCR        (288) // PDC传输控制寄存器
#define ADC_PTSR        (292) // PDC传输状态寄存器
// --------ADC_CR:（ADC偏移：0x0）ADC控制寄存器--------
#define AT91C_ADC_SWRST           (0x1 <<  0) // （ADC）软件重置
#define AT91C_ADC_START           (0x1 <<  1) // （ADC）开始转换
// --------ADC_MR:（ADC偏移：0x4）ADC模式寄存器--------
#define AT91C_ADC_TRGEN           (0x1 <<  0) // （ADC）触发启用
#define 	AT91C_ADC_TRGEN_DIS                  (0x0) // （ADC）Hradware触发器已禁用。只能通过软件启动转换
#define 	AT91C_ADC_TRGEN_EN                   (0x1) // （ADC）启用TRGSEL字段选择的硬件触发器。
#define AT91C_ADC_TRGSEL          (0x7 <<  1) // （ADC）触发选择
#define 	AT91C_ADC_TRGSEL_TIOA0                (0x0 <<  1) // （ADC）所选TRGSEL=TIAO0
#define 	AT91C_ADC_TRGSEL_TIOA1                (0x1 <<  1) // （ADC）所选TRGSEL=TIAO1
#define 	AT91C_ADC_TRGSEL_TIOA2                (0x2 <<  1) // （ADC）所选TRGSEL=TIAO2
#define 	AT91C_ADC_TRGSEL_TIOA3                (0x3 <<  1) // （ADC）所选TRGSEL=TIAO3
#define 	AT91C_ADC_TRGSEL_TIOA4                (0x4 <<  1) // （ADC）所选TRGSEL=TIAO4
#define 	AT91C_ADC_TRGSEL_TIOA5                (0x5 <<  1) // （ADC）所选TRGSEL=TIAO5
#define 	AT91C_ADC_TRGSEL_EXT                  (0x6 <<  1) // （ADC）所选TRGSEL=外部触发器
#define AT91C_ADC_LOWRES          (0x1 <<  4) // （ADC）分辨率。
#define 	AT91C_ADC_LOWRES_10_BIT               (0x0 <<  4) // （ADC）10位分辨率
#define 	AT91C_ADC_LOWRES_8_BIT                (0x1 <<  4) // （ADC）8位分辨率
#define AT91C_ADC_SLEEP           (0x1 <<  5) // （ADC）睡眠模式
#define 	AT91C_ADC_SLEEP_NORMAL_MODE          (0x0 <<  5) // （ADC）正常模式
#define 	AT91C_ADC_SLEEP_MODE                 (0x1 <<  5) // （ADC）睡眠模式
#define AT91C_ADC_PRESCAL         (0x3F <<  8) // （ADC）预缩放速率选择
#define AT91C_ADC_STARTUP         (0x1F << 16) // （ADC）启动时间
#define AT91C_ADC_SHTIM           (0xF << 24) // （ADC）采样和保持时间
// --------ADC_CHER：（ADC偏移：0x10）ADC通道启用寄存器--------
#define AT91C_ADC_CH0             (0x1 <<  0) // （ADC）通道0
#define AT91C_ADC_CH1             (0x1 <<  1) // （ADC）通道1
#define AT91C_ADC_CH2             (0x1 <<  2) // （ADC）通道2
#define AT91C_ADC_CH3             (0x1 <<  3) // （ADC）通道3
#define AT91C_ADC_CH4             (0x1 <<  4) // （ADC）通道4
#define AT91C_ADC_CH5             (0x1 <<  5) // （ADC）通道5
#define AT91C_ADC_CH6             (0x1 <<  6) // （ADC）通道6
#define AT91C_ADC_CH7             (0x1 <<  7) // （ADC）通道7
// --------ADC_CHDR：（ADC偏移：0x14）ADC通道禁用寄存器--------
// --------ADC_HSR:（ADC偏移：0x18）ADC通道状态寄存器--------
// --------ADC_SR：（ADC偏移量：0x1c）ADC状态寄存器--------
#define AT91C_ADC_EOC0            (0x1 <<  0) // （ADC）转换结束
#define AT91C_ADC_EOC1            (0x1 <<  1) // （ADC）转换结束
#define AT91C_ADC_EOC2            (0x1 <<  2) // （ADC）转换结束
#define AT91C_ADC_EOC3            (0x1 <<  3) // （ADC）转换结束
#define AT91C_ADC_EOC4            (0x1 <<  4) // （ADC）转换结束
#define AT91C_ADC_EOC5            (0x1 <<  5) // （ADC）转换结束
#define AT91C_ADC_EOC6            (0x1 <<  6) // （ADC）转换结束
#define AT91C_ADC_EOC7            (0x1 <<  7) // （ADC）转换结束
#define AT91C_ADC_OVRE0           (0x1 <<  8) // （ADC）超限错误
#define AT91C_ADC_OVRE1           (0x1 <<  9) // （ADC）超限错误
#define AT91C_ADC_OVRE2           (0x1 << 10) // （ADC）超限错误
#define AT91C_ADC_OVRE3           (0x1 << 11) // （ADC）超限错误
#define AT91C_ADC_OVRE4           (0x1 << 12) // （ADC）超限错误
#define AT91C_ADC_OVRE5           (0x1 << 13) // （ADC）超限错误
#define AT91C_ADC_OVRE6           (0x1 << 14) // （ADC）超限错误
#define AT91C_ADC_OVRE7           (0x1 << 15) // （ADC）超限错误
#define AT91C_ADC_DRDY            (0x1 << 16) // （ADC）数据就绪
#define AT91C_ADC_GOVRE           (0x1 << 17) // （ADC）一般超限
#define AT91C_ADC_ENDRX           (0x1 << 18) // （ADC）接收器传输结束
#define AT91C_ADC_RXBUFF          (0x1 << 19) // （ADC）RXBUFF中断
// --------ADC_LCD:（ADC偏移量：0x20）ADC上次转换的数据寄存器--------
#define AT91C_ADC_LDATA           (0x3FF <<  0) // （ADC）上次转换的数据
// --------ADC_IER:（ADC偏移：0x24）ADC中断启用寄存器--------
// --------ADC_IDR:（ADC偏移量：0x28）ADC中断禁用寄存器--------
// --------ADC_IMR:（ADC偏移量：0x2c）ADC中断掩码寄存器--------
// --------ADC_CDR0:（ADC偏移量：0x30）ADC通道数据寄存器0--------
#define AT91C_ADC_DATA            (0x3FF <<  0) // （ADC）转换数据
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
#define AT91C_AIC_ICCR            (0xFFFFF128) // （AIC）中断清除命令寄存器
#define AT91C_AIC_IECR            (0xFFFFF120) // （AIC）中断启用命令寄存器
#define AT91C_AIC_SMR             (0xFFFFF000) // （AIC）源模式寄存器
#define AT91C_AIC_ISCR            (0xFFFFF12C) // （AIC）中断设置命令寄存器
#define AT91C_AIC_EOICR           (0xFFFFF130) // （AIC）中断命令寄存器结束
#define AT91C_AIC_DCR             (0xFFFFF138) // （AIC）调试控制寄存器（保护）
#define AT91C_AIC_FFER            (0xFFFFF140) // （AIC）快速强制启用寄存器
#define AT91C_AIC_SVR             (0xFFFFF080) // （AIC）源矢量寄存器
#define AT91C_AIC_SPU             (0xFFFFF134) // （AIC）杂散矢量寄存器
#define AT91C_AIC_FFDR            (0xFFFFF144) // （AIC）快速强制禁用寄存器
#define AT91C_AIC_FVR             (0xFFFFF104) // （AIC）FIQ矢量寄存器
#define AT91C_AIC_FFSR            (0xFFFFF148) // （AIC）快速强制状态寄存器
#define AT91C_AIC_IMR             (0xFFFFF110) // （AIC）中断掩码寄存器
#define AT91C_AIC_ISR             (0xFFFFF108) // （AIC）中断状态寄存器
#define AT91C_AIC_IVR             (0xFFFFF100) // （AIC）IRQ矢量寄存器
#define AT91C_AIC_IDCR            (0xFFFFF124) // （AIC）中断禁用命令寄存器
#define AT91C_AIC_CISR            (0xFFFFF114) // （AIC）核心中断状态寄存器
#define AT91C_AIC_IPR             (0xFFFFF10C) // （AIC）中断挂起寄存器
// ============PDC_DBGU外围设备的寄存器定义============
#define AT91C_DBGU_TNCR           (0xFFFFF31C) // （PDC_DBGU）发送下一计数器寄存器
#define AT91C_DBGU_RNCR           (0xFFFFF314) // （PDC_DBGU）接收下一个计数器寄存器
#define AT91C_DBGU_PTCR           (0xFFFFF320) // （PDC_DBGU）PDC传输控制寄存器
#define AT91C_DBGU_PTSR           (0xFFFFF324) // （PDC_DBGU）PDC传输状态寄存器
#define AT91C_DBGU_RCR            (0xFFFFF304) // （PDC_DBGU）接收计数器寄存器
#define AT91C_DBGU_TCR            (0xFFFFF30C) // （PDC_DBGU）发送计数器寄存器
#define AT91C_DBGU_RPR            (0xFFFFF300) // （PDC_DBGU）接收指针寄存器
#define AT91C_DBGU_TPR            (0xFFFFF308) // （PDC_DBGU）发送指针寄存器
#define AT91C_DBGU_RNPR           (0xFFFFF310) // （PDC_DBGU）接收下一个指针寄存器
#define AT91C_DBGU_TNPR           (0xFFFFF318) // （PDC_DBGU）发送下一个指针寄存器
// ============DBGU外围设备的寄存器定义============
#define AT91C_DBGU_EXID           (0xFFFFF244) // （DBGU）芯片ID扩展寄存器
#define AT91C_DBGU_THR            (0xFFFFF21C) // （DBGU）发射机保持寄存器
#define AT91C_DBGU_CSR            (0xFFFFF214) // （DBGU）信道状态寄存器
#define AT91C_DBGU_IDR            (0xFFFFF20C) // （DBGU）中断禁用寄存器
#define AT91C_DBGU_MR             (0xFFFFF204) // （DBGU）模式寄存器
#define AT91C_DBGU_FNTR           (0xFFFFF248) // （DBGU）强制NTRST寄存器
#define AT91C_DBGU_CIDR           (0xFFFFF240) // （DBGU）芯片ID寄存器
#define AT91C_DBGU_BRGR           (0xFFFFF220) // （DBGU）波特率生成器寄存器
#define AT91C_DBGU_RHR            (0xFFFFF218) // （DBGU）接收机保持寄存器
#define AT91C_DBGU_IMR            (0xFFFFF210) // （DBGU）中断掩码寄存器
#define AT91C_DBGU_IER            (0xFFFFF208) // （DBGU）中断启用寄存器
#define AT91C_DBGU_CR             (0xFFFFF200) // （DBGU）控制寄存器
// ============PIOA外围设备的寄存器定义============
#define AT91C_PIOA_IMR            (0xFFFFF448) // （PIOA）中断掩码寄存器
#define AT91C_PIOA_IER            (0xFFFFF440) // （PIOA）中断启用寄存器
#define AT91C_PIOA_OWDR           (0xFFFFF4A4) // （PIOA）输出写入禁用寄存器
#define AT91C_PIOA_ISR            (0xFFFFF44C) // （PIOA）中断状态寄存器
#define AT91C_PIOA_PPUDR          (0xFFFFF460) // （PIOA）上拉禁用寄存器
#define AT91C_PIOA_MDSR           (0xFFFFF458) // （PIOA）多驱动程序状态寄存器
#define AT91C_PIOA_MDER           (0xFFFFF450) // （PIOA）多驱动程序启用寄存器
#define AT91C_PIOA_PER            (0xFFFFF400) // （PIOA）PIO启用寄存器
#define AT91C_PIOA_PSR            (0xFFFFF408) // （PIOA）PIO状态寄存器
#define AT91C_PIOA_OER            (0xFFFFF410) // （PIOA）输出启用寄存器
#define AT91C_PIOA_BSR            (0xFFFFF474) // （PIOA）选择B寄存器
#define AT91C_PIOA_PPUER          (0xFFFFF464) // （PIOA）上拉启用寄存器
#define AT91C_PIOA_MDDR           (0xFFFFF454) // （PIOA）多驱动程序禁用寄存器
#define AT91C_PIOA_PDR            (0xFFFFF404) // （PIOA）PIO禁用寄存器
#define AT91C_PIOA_ODR            (0xFFFFF414) // （PIOA）输出禁用寄存器
#define AT91C_PIOA_IFDR           (0xFFFFF424) // （PIOA）输入滤波器禁用寄存器
#define AT91C_PIOA_ABSR           (0xFFFFF478) // （PIOA）AB选择状态寄存器
#define AT91C_PIOA_ASR            (0xFFFFF470) // （PIOA）选择一个寄存器
#define AT91C_PIOA_PPUSR          (0xFFFFF468) // （PIOA）上拉状态寄存器
#define AT91C_PIOA_ODSR           (0xFFFFF438) // （PIOA）输出数据状态寄存器
#define AT91C_PIOA_SODR           (0xFFFFF430) // （PIOA）设置输出数据寄存器
#define AT91C_PIOA_IFSR           (0xFFFFF428) // （PIOA）输入滤波器状态寄存器
#define AT91C_PIOA_IFER           (0xFFFFF420) // （PIOA）输入滤波器启用寄存器
#define AT91C_PIOA_OSR            (0xFFFFF418) // （PIOA）输出状态寄存器
#define AT91C_PIOA_IDR            (0xFFFFF444) // （PIOA）中断禁用寄存器
#define AT91C_PIOA_PDSR           (0xFFFFF43C) // （PIOA）引脚数据状态寄存器
#define AT91C_PIOA_CODR           (0xFFFFF434) // （PIOA）清除输出数据寄存器
#define AT91C_PIOA_OWSR           (0xFFFFF4A8) // （PIOA）输出写入状态寄存器
#define AT91C_PIOA_OWER           (0xFFFFF4A0) // （PIOA）输出写入启用寄存器
// ============PIOB外围设备的寄存器定义============
#define AT91C_PIOB_OWSR           (0xFFFFF6A8) // （PIOB）输出写入状态寄存器
#define AT91C_PIOB_PPUSR          (0xFFFFF668) // （PIOB）上拉状态寄存器
#define AT91C_PIOB_PPUDR          (0xFFFFF660) // （PIOB）上拉禁用寄存器
#define AT91C_PIOB_MDSR           (0xFFFFF658) // （PIOB）多驱动程序状态寄存器
#define AT91C_PIOB_MDER           (0xFFFFF650) // （PIOB）多驱动器启用寄存器
#define AT91C_PIOB_IMR            (0xFFFFF648) // （PIOB）中断掩码寄存器
#define AT91C_PIOB_OSR            (0xFFFFF618) // （PIOB）输出状态寄存器
#define AT91C_PIOB_OER            (0xFFFFF610) // （PIOB）输出启用寄存器
#define AT91C_PIOB_PSR            (0xFFFFF608) // （PIOB）PIO状态寄存器
#define AT91C_PIOB_PER            (0xFFFFF600) // （PIOB）PIO启用寄存器
#define AT91C_PIOB_BSR            (0xFFFFF674) // （PIOB）选择B寄存器
#define AT91C_PIOB_PPUER          (0xFFFFF664) // （PIOB）上拉启用寄存器
#define AT91C_PIOB_IFDR           (0xFFFFF624) // （PIOB）输入滤波器禁用寄存器
#define AT91C_PIOB_ODR            (0xFFFFF614) // （PIOB）输出禁用寄存器
#define AT91C_PIOB_ABSR           (0xFFFFF678) // （PIOB）AB选择状态寄存器
#define AT91C_PIOB_ASR            (0xFFFFF670) // （PIOB）选择寄存器
#define AT91C_PIOB_IFER           (0xFFFFF620) // （PIOB）输入滤波器启用寄存器
#define AT91C_PIOB_IFSR           (0xFFFFF628) // （PIOB）输入滤波器状态寄存器
#define AT91C_PIOB_SODR           (0xFFFFF630) // （PIOB）设置输出数据寄存器
#define AT91C_PIOB_ODSR           (0xFFFFF638) // （PIOB）输出数据状态寄存器
#define AT91C_PIOB_CODR           (0xFFFFF634) // （PIOB）清除输出数据寄存器
#define AT91C_PIOB_PDSR           (0xFFFFF63C) // （PIOB）引脚数据状态寄存器
#define AT91C_PIOB_OWER           (0xFFFFF6A0) // （PIOB）输出写入启用寄存器
#define AT91C_PIOB_IER            (0xFFFFF640) // （PIOB）中断启用寄存器
#define AT91C_PIOB_OWDR           (0xFFFFF6A4) // （PIOB）输出写禁止寄存器
#define AT91C_PIOB_MDDR           (0xFFFFF654) // （PIOB）多驱动器禁用寄存器
#define AT91C_PIOB_ISR            (0xFFFFF64C) // （PIOB）中断状态寄存器
#define AT91C_PIOB_IDR            (0xFFFFF644) // （PIOB）中断禁用寄存器
#define AT91C_PIOB_PDR            (0xFFFFF604) // （PIOB）PIO禁用寄存器
// ============CKGR外围设备的寄存器定义============
#define AT91C_CKGR_PLLR           (0xFFFFFC2C) // （CKGR）PLL寄存器
#define AT91C_CKGR_MCFR           (0xFFFFFC24) // （CKGR）主时钟频率寄存器
#define AT91C_CKGR_MOR            (0xFFFFFC20) // （CKGR）主振荡器寄存器
// ===========PMC外围设备的寄存器定义===========
#define AT91C_PMC_SCSR            (0xFFFFFC08) // （PMC）系统时钟状态寄存器
#define AT91C_PMC_SCER            (0xFFFFFC00) // （PMC）系统时钟启用寄存器
#define AT91C_PMC_IMR             (0xFFFFFC6C) // （PMC）中断掩码寄存器
#define AT91C_PMC_IDR             (0xFFFFFC64) // （PMC）中断禁用寄存器
#define AT91C_PMC_PCDR            (0xFFFFFC14) // （PMC）外围时钟禁用寄存器
#define AT91C_PMC_SCDR            (0xFFFFFC04) // （PMC）系统时钟禁用寄存器
#define AT91C_PMC_SR              (0xFFFFFC68) // （PMC）状态寄存器
#define AT91C_PMC_IER             (0xFFFFFC60) // （PMC）中断启用寄存器
#define AT91C_PMC_MCKR            (0xFFFFFC30) // （PMC）主时钟寄存器
#define AT91C_PMC_MOR             (0xFFFFFC20) // （PMC）主振荡器寄存器
#define AT91C_PMC_PCER            (0xFFFFFC10) // （PMC）外围时钟启用寄存器
#define AT91C_PMC_PCSR            (0xFFFFFC18) // （PMC）外围时钟状态寄存器
#define AT91C_PMC_PLLR            (0xFFFFFC2C) // （PMC）PLL寄存器
#define AT91C_PMC_MCFR            (0xFFFFFC24) // （PMC）主时钟频率寄存器
#define AT91C_PMC_PCKR            (0xFFFFFC40) // （PMC）可编程时钟寄存器
// ============RSTC外围设备的寄存器定义============
#define AT91C_RSTC_RSR            (0xFFFFFD04) // （RSTC）重置状态寄存器
#define AT91C_RSTC_RMR            (0xFFFFFD08) // （RSTC）复位模式寄存器
#define AT91C_RSTC_RCR            (0xFFFFFD00) // （RSTC）复位控制寄存器
// ============RTTC外围设备的寄存器定义============
#define AT91C_RTTC_RTSR           (0xFFFFFD2C) // （RTTC）实时状态寄存器
#define AT91C_RTTC_RTAR           (0xFFFFFD24) // （RTTC）实时报警寄存器
#define AT91C_RTTC_RTVR           (0xFFFFFD28) // （RTTC）实时值寄存器
#define AT91C_RTTC_RTMR           (0xFFFFFD20) // （RTTC）实时模式寄存器
// ============PITC外围设备的寄存器定义============
#define AT91C_PITC_PIIR           (0xFFFFFD3C) // （PITC）周期间隔图像寄存器
#define AT91C_PITC_PISR           (0xFFFFFD34) // （PITC）周期间隔状态寄存器
#define AT91C_PITC_PIVR           (0xFFFFFD38) // （PITC）周期间隔值寄存器
#define AT91C_PITC_PIMR           (0xFFFFFD30) // （PITC）周期间隔模式寄存器
// ============WDTC外围设备的寄存器定义============
#define AT91C_WDTC_WDMR           (0xFFFFFD44) // （WDTC）看门狗模式寄存器
#define AT91C_WDTC_WDSR           (0xFFFFFD48) // （WDTC）看门狗状态寄存器
#define AT91C_WDTC_WDCR           (0xFFFFFD40) // （WDTC）看门狗控制寄存器
// ============VREG外围设备的寄存器定义============
#define AT91C_VREG_MR             (0xFFFFFD60) // （VREG）电压调节器模式寄存器
// ============MC外围设备的寄存器定义============
#define AT91C_MC_FCR              (0xFFFFFF64) // （MC）MC闪存命令寄存器
#define AT91C_MC_ASR              (0xFFFFFF04) // （MC）MC中止状态寄存器
#define AT91C_MC_FSR              (0xFFFFFF68) // （MC）MC闪存状态寄存器
#define AT91C_MC_FMR              (0xFFFFFF60) // （MC）MC闪存模式寄存器
#define AT91C_MC_AASR             (0xFFFFFF08) // （MC）MC中止地址状态寄存器
#define AT91C_MC_RCR              (0xFFFFFF00) // （MC）MC重映射控制寄存器
// ============PDC_SPI1外围设备的寄存器定义============
#define AT91C_SPI1_RNPR           (0xFFFE4110) // （PDC_SPI1）接收下一个指针寄存器
#define AT91C_SPI1_TPR            (0xFFFE4108) // （PDC_SPI1）发送指针寄存器
#define AT91C_SPI1_RPR            (0xFFFE4100) // （PDC_SPI1）接收指针寄存器
#define AT91C_SPI1_PTSR           (0xFFFE4124) // （PDC_SPI1）PDC传输状态寄存器
#define AT91C_SPI1_RCR            (0xFFFE4104) // （PDC_SPI1）接收计数器寄存器
#define AT91C_SPI1_TCR            (0xFFFE410C) // （PDC_SPI1）发送计数器寄存器
#define AT91C_SPI1_RNCR           (0xFFFE4114) // （PDC_SPI1）接收下一个计数器寄存器
#define AT91C_SPI1_TNCR           (0xFFFE411C) // （PDC_SPI1）发送下一计数器寄存器
#define AT91C_SPI1_TNPR           (0xFFFE4118) // （PDC_SPI1）发送下一个指针寄存器
#define AT91C_SPI1_PTCR           (0xFFFE4120) // （PDC_SPI1）PDC传输控制寄存器
// ============SPI1外围设备的寄存器定义============
#define AT91C_SPI1_CSR            (0xFFFE4030) // （SPI1）芯片选择寄存器
#define AT91C_SPI1_IDR            (0xFFFE4018) // （SPI1）中断禁用寄存器
#define AT91C_SPI1_SR             (0xFFFE4010) // （SPI1）状态寄存器
#define AT91C_SPI1_RDR            (0xFFFE4008) // （SPI1）接收数据寄存器
#define AT91C_SPI1_CR             (0xFFFE4000) // （SPI1）控制寄存器
#define AT91C_SPI1_IMR            (0xFFFE401C) // （SPI1）中断掩码寄存器
#define AT91C_SPI1_IER            (0xFFFE4014) // （SPI1）中断启用寄存器
#define AT91C_SPI1_TDR            (0xFFFE400C) // （SPI1）发送数据寄存器
#define AT91C_SPI1_MR             (0xFFFE4004) // （SPI1）模式寄存器
// ============PDC_SPI0外围设备的寄存器定义============
#define AT91C_SPI0_PTCR           (0xFFFE0120) // （PDC_SPI0）PDC传输控制寄存器
#define AT91C_SPI0_TNPR           (0xFFFE0118) // （PDC_SPI0）发送下一个指针寄存器
#define AT91C_SPI0_RNPR           (0xFFFE0110) // （PDC_SPI0）接收下一个指针寄存器
#define AT91C_SPI0_TPR            (0xFFFE0108) // （PDC_SPI0）传输指针寄存器
#define AT91C_SPI0_RPR            (0xFFFE0100) // （PDC_SPI0）接收指针寄存器
#define AT91C_SPI0_PTSR           (0xFFFE0124) // （PDC_SPI0）PDC传输状态寄存器
#define AT91C_SPI0_TNCR           (0xFFFE011C) // （PDC_SPI0）发送下一计数器寄存器
#define AT91C_SPI0_RNCR           (0xFFFE0114) // （PDC_SPI0）接收下一个计数器寄存器
#define AT91C_SPI0_TCR            (0xFFFE010C) // （PDC_SPI0）传输计数器寄存器
#define AT91C_SPI0_RCR            (0xFFFE0104) // （PDC_SPI0）接收计数器寄存器
// ============SPI0外围设备的寄存器定义============
#define AT91C_SPI0_CSR            (0xFFFE0030) // （SPI0）芯片选择寄存器
#define AT91C_SPI0_IDR            (0xFFFE0018) // （SPI0）中断禁用寄存器
#define AT91C_SPI0_SR             (0xFFFE0010) // （SPI0）状态寄存器
#define AT91C_SPI0_RDR            (0xFFFE0008) // （SPI0）接收数据寄存器
#define AT91C_SPI0_CR             (0xFFFE0000) // （SPI0）控制寄存器
#define AT91C_SPI0_IMR            (0xFFFE001C) // （SPI0）中断掩码寄存器
#define AT91C_SPI0_IER            (0xFFFE0014) // （SPI0）中断启用寄存器
#define AT91C_SPI0_TDR            (0xFFFE000C) // （SPI0）传输数据寄存器
#define AT91C_SPI0_MR             (0xFFFE0004) // （SPI0）模式寄存器
// ============PDC_US1外围设备的寄存器定义============
#define AT91C_US1_PTSR            (0xFFFC4124) // （PDC_US1）PDC传输状态寄存器
#define AT91C_US1_TNCR            (0xFFFC411C) // （PDC_US1）发送下一计数器寄存器
#define AT91C_US1_RNCR            (0xFFFC4114) // （PDC_US1）接收下一个计数器寄存器
#define AT91C_US1_TCR             (0xFFFC410C) // （PDC_US1）发送计数器寄存器
#define AT91C_US1_RCR             (0xFFFC4104) // （PDC_US1）接收计数器寄存器
#define AT91C_US1_PTCR            (0xFFFC4120) // （PDC_US1）PDC传输控制寄存器
#define AT91C_US1_TNPR            (0xFFFC4118) // （PDC_US1）发送下一个指针寄存器
#define AT91C_US1_RNPR            (0xFFFC4110) // （PDC_US1）接收下一个指针寄存器
#define AT91C_US1_TPR             (0xFFFC4108) // （PDC_US1）发送指针寄存器
#define AT91C_US1_RPR             (0xFFFC4100) // （PDC_US1）接收指针寄存器
// ============US1外围设备的寄存器定义============
#define AT91C_US1_RHR             (0xFFFC4018) // （US1）接收机保持寄存器
#define AT91C_US1_IMR             (0xFFFC4010) // （US1）中断掩码寄存器
#define AT91C_US1_IER             (0xFFFC4008) // （US1）中断启用寄存器
#define AT91C_US1_CR              (0xFFFC4000) // （US1）控制寄存器
#define AT91C_US1_RTOR            (0xFFFC4024) // （US1）接收机超时寄存器
#define AT91C_US1_THR             (0xFFFC401C) // （US1）发射机保持寄存器
#define AT91C_US1_CSR             (0xFFFC4014) // （US1）信道状态寄存器
#define AT91C_US1_IDR             (0xFFFC400C) // （US1）中断禁用寄存器
#define AT91C_US1_FIDI            (0xFFFC4040) // （US1）FI_DI_Ratio寄存器
#define AT91C_US1_BRGR            (0xFFFC4020) // （US1）波特率发生器寄存器
#define AT91C_US1_TTGR            (0xFFFC4028) // （US1）发射器时间保护寄存器
#define AT91C_US1_IF              (0xFFFC404C) // （US1）IRDA_FILTER寄存器
#define AT91C_US1_NER             (0xFFFC4044) // （US1）Nb错误寄存器
#define AT91C_US1_MR              (0xFFFC4004) // （US1）模式寄存器
// ============PDC_US0外围设备的寄存器定义============
#define AT91C_US0_PTCR            (0xFFFC0120) // （PDC_US0）PDC传输控制寄存器
#define AT91C_US0_TNPR            (0xFFFC0118) // （PDC_US0）发送下一个指针寄存器
#define AT91C_US0_RNPR            (0xFFFC0110) // （PDC_US0）接收下一个指针寄存器
#define AT91C_US0_TPR             (0xFFFC0108) // （PDC_US0）发送指针寄存器
#define AT91C_US0_RPR             (0xFFFC0100) // （PDC_US0）接收指针寄存器
#define AT91C_US0_PTSR            (0xFFFC0124) // （PDC_US0）PDC传输状态寄存器
#define AT91C_US0_TNCR            (0xFFFC011C) // （PDC_US0）发送下一计数器寄存器
#define AT91C_US0_RNCR            (0xFFFC0114) // （PDC_US0）接收下一个计数器寄存器
#define AT91C_US0_TCR             (0xFFFC010C) // （PDC_US0）发送计数器寄存器
#define AT91C_US0_RCR             (0xFFFC0104) // （PDC_US0）接收计数器寄存器
// ============US0外围设备的寄存器定义============
#define AT91C_US0_TTGR            (0xFFFC0028) // （US0）发射器时间保护寄存器
#define AT91C_US0_BRGR            (0xFFFC0020) // （US0）波特率发生器寄存器
#define AT91C_US0_RHR             (0xFFFC0018) // （US0）接收机保持寄存器
#define AT91C_US0_IMR             (0xFFFC0010) // （US0）中断掩码寄存器
#define AT91C_US0_NER             (0xFFFC0044) // （US0）Nb错误寄存器
#define AT91C_US0_RTOR            (0xFFFC0024) // （US0）接收机超时寄存器
#define AT91C_US0_FIDI            (0xFFFC0040) // （US0）FI_DI_Ratio寄存器
#define AT91C_US0_CR              (0xFFFC0000) // （US0）控制寄存器
#define AT91C_US0_IER             (0xFFFC0008) // （US0）中断启用寄存器
#define AT91C_US0_IF              (0xFFFC004C) // （US0）IRDA_FILTER寄存器
#define AT91C_US0_MR              (0xFFFC0004) // （US0）模式寄存器
#define AT91C_US0_IDR             (0xFFFC000C) // （US0）中断禁用寄存器
#define AT91C_US0_CSR             (0xFFFC0014) // （US0）信道状态寄存器
#define AT91C_US0_THR             (0xFFFC001C) // （US0）发射机保持寄存器
// ============PDC_SSC外围设备的寄存器定义============
#define AT91C_SSC_PTCR            (0xFFFD4120) // （PDC_SSC）PDC传输控制寄存器
#define AT91C_SSC_TNPR            (0xFFFD4118) // （PDC_SSC）发送下一个指针寄存器
#define AT91C_SSC_RNPR            (0xFFFD4110) // （PDC_SSC）接收下一个指针寄存器
#define AT91C_SSC_TPR             (0xFFFD4108) // （PDC_SSC）发送指针寄存器
#define AT91C_SSC_RPR             (0xFFFD4100) // （PDC_SSC）接收指针寄存器
#define AT91C_SSC_PTSR            (0xFFFD4124) // （PDC_SSC）PDC传输状态寄存器
#define AT91C_SSC_TNCR            (0xFFFD411C) // （PDC_SSC）发送下一计数器寄存器
#define AT91C_SSC_RNCR            (0xFFFD4114) // （PDC_SSC）接收下一计数器寄存器
#define AT91C_SSC_TCR             (0xFFFD410C) // （PDC_SSC）发送计数器寄存器
#define AT91C_SSC_RCR             (0xFFFD4104) // （PDC_SSC）接收计数器寄存器
// ============SSC外围设备的寄存器定义============
#define AT91C_SSC_RFMR            (0xFFFD4014) // （SSC）接收帧模式寄存器
#define AT91C_SSC_CMR             (0xFFFD4004) // （SSC）时钟模式寄存器
#define AT91C_SSC_IDR             (0xFFFD4048) // （SSC）中断禁用寄存器
#define AT91C_SSC_SR              (0xFFFD4040) // （SSC）状态寄存器
#define AT91C_SSC_RSHR            (0xFFFD4030) // （SSC）接收同步保持寄存器
#define AT91C_SSC_RHR             (0xFFFD4020) // （SSC）接收保持寄存器
#define AT91C_SSC_TCMR            (0xFFFD4018) // （SSC）发送时钟模式寄存器
#define AT91C_SSC_RCMR            (0xFFFD4010) // （SSC）接收时钟模式寄存器
#define AT91C_SSC_CR              (0xFFFD4000) // （SSC）控制寄存器
#define AT91C_SSC_IMR             (0xFFFD404C) // （SSC）中断掩码寄存器
#define AT91C_SSC_IER             (0xFFFD4044) // （SSC）中断启用寄存器
#define AT91C_SSC_TSHR            (0xFFFD4034) // （SSC）传输同步保持寄存器
#define AT91C_SSC_THR             (0xFFFD4024) // （SSC）发送保持寄存器
#define AT91C_SSC_TFMR            (0xFFFD401C) // （SSC）发送帧模式寄存器
// ============TWI外围设备的寄存器定义============
#define AT91C_TWI_RHR             (0xFFFB8030) // （TWI）接收保持寄存器
#define AT91C_TWI_IDR             (0xFFFB8028) // （TWI）中断禁用寄存器
#define AT91C_TWI_SR              (0xFFFB8020) // （TWI）状态寄存器
#define AT91C_TWI_CWGR            (0xFFFB8010) // （TWI）时钟波形发生器寄存器
#define AT91C_TWI_CR              (0xFFFB8000) // （TWI）控制寄存器
#define AT91C_TWI_THR             (0xFFFB8034) // （TWI）发送保持寄存器
#define AT91C_TWI_IMR             (0xFFFB802C) // （TWI）中断掩码寄存器
#define AT91C_TWI_IER             (0xFFFB8024) // （TWI）中断启用寄存器
#define AT91C_TWI_IADR            (0xFFFB800C) // （TWI）内部地址寄存器
#define AT91C_TWI_MMR             (0xFFFB8004) // （TWI）主模式寄存器
// ============PWMC_CH3外围设备的寄存器定义============
#define AT91C_PWMC_CH3_CUPDR      (0xFFFCC270) // （PWMC_CH3）信道更新寄存器
#define AT91C_PWMC_CH3_CPRDR      (0xFFFCC268) // （PWMC_CH3）信道周期寄存器
#define AT91C_PWMC_CH3_CMR        (0xFFFCC260) // （PWMC_CH3）信道模式寄存器
#define AT91C_PWMC_CH3_Reserved   (0xFFFCC274) // （PWMC_CH3）保留
#define AT91C_PWMC_CH3_CCNTR      (0xFFFCC26C) // （PWMC_CH3）信道计数器寄存器
#define AT91C_PWMC_CH3_CDTYR      (0xFFFCC264) // （PWMC_CH3）信道占空比寄存器
// ============PWMC_CH2外围设备的寄存器定义============
#define AT91C_PWMC_CH2_CUPDR      (0xFFFCC250) // （PWMC_CH2）信道更新寄存器
#define AT91C_PWMC_CH2_CPRDR      (0xFFFCC248) // （PWMC_CH2）信道周期寄存器
#define AT91C_PWMC_CH2_CMR        (0xFFFCC240) // （PWMC_CH2）信道模式寄存器
#define AT91C_PWMC_CH2_Reserved   (0xFFFCC254) // （PWMC_CH2）保留
#define AT91C_PWMC_CH2_CCNTR      (0xFFFCC24C) // （PWMC_CH2）信道计数器寄存器
#define AT91C_PWMC_CH2_CDTYR      (0xFFFCC244) // （PWMC_CH2）通道占空比寄存器
// ============PWMC_CH1外围设备的寄存器定义============
#define AT91C_PWMC_CH1_CUPDR      (0xFFFCC230) // （PWMC_CH1）信道更新寄存器
#define AT91C_PWMC_CH1_CPRDR      (0xFFFCC228) // （PWMC_CH1）信道周期寄存器
#define AT91C_PWMC_CH1_CMR        (0xFFFCC220) // （PWMC_CH1）信道模式寄存器
#define AT91C_PWMC_CH1_Reserved   (0xFFFCC234) // （PWMC_CH1）保留
#define AT91C_PWMC_CH1_CCNTR      (0xFFFCC22C) // （PWMC_CH1）信道计数器寄存器
#define AT91C_PWMC_CH1_CDTYR      (0xFFFCC224) // （PWMC_CH1）通道占空比寄存器
// ============PWMC_CH0外围设备的寄存器定义============
#define AT91C_PWMC_CH0_CUPDR      (0xFFFCC210) // （PWMC_CH0）信道更新寄存器
#define AT91C_PWMC_CH0_CPRDR      (0xFFFCC208) // （PWMC_CH0）信道周期寄存器
#define AT91C_PWMC_CH0_CMR        (0xFFFCC200) // （PWMC_CH0）信道模式寄存器
#define AT91C_PWMC_CH0_Reserved   (0xFFFCC214) // （PWMC_CH0）保留
#define AT91C_PWMC_CH0_CCNTR      (0xFFFCC20C) // （PWMC_CH0）信道计数器寄存器
#define AT91C_PWMC_CH0_CDTYR      (0xFFFCC204) // （PWMC_CH0）通道占空比寄存器
// ============PWMC外围设备的寄存器定义============
#define AT91C_PWMC_VR             (0xFFFCC0FC) // （PWMC）PWMC版本寄存器
#define AT91C_PWMC_ISR            (0xFFFCC01C) // （PWMC）PWMC中断状态寄存器
#define AT91C_PWMC_IDR            (0xFFFCC014) // （PWMC）PWMC中断禁用寄存器
#define AT91C_PWMC_SR             (0xFFFCC00C) // （PWMC）PWMC状态寄存器
#define AT91C_PWMC_ENA            (0xFFFCC004) // （PWMC）PWMC启用寄存器
#define AT91C_PWMC_IMR            (0xFFFCC018) // （PWMC）PWMC中断掩码寄存器
#define AT91C_PWMC_MR             (0xFFFCC000) // （PWMC）PWMC模式寄存器
#define AT91C_PWMC_DIS            (0xFFFCC008) // （PWMC）PWMC禁用寄存器
#define AT91C_PWMC_IER            (0xFFFCC010) // （PWMC）PWMC中断启用寄存器
// ============UDP外围设备的寄存器定义============
#define AT91C_UDP_TXVC            (0xFFFB0074) // （UDP）收发器控制寄存器
#define AT91C_UDP_ISR             (0xFFFB001C) // （UDP）中断状态寄存器
#define AT91C_UDP_IDR             (0xFFFB0014) // （UDP）中断禁用寄存器
#define AT91C_UDP_CSR             (0xFFFB0030) // （UDP）端点控制和状态寄存器
#define AT91C_UDP_RSTEP           (0xFFFB0028) // （UDP）重置终结点寄存器
#define AT91C_UDP_ICR             (0xFFFB0020) // （UDP）中断清除寄存器
#define AT91C_UDP_GLBSTATE        (0xFFFB0004) // （UDP）全局状态寄存器
#define AT91C_UDP_NUM             (0xFFFB0000) // （UDP）帧号寄存器
#define AT91C_UDP_FADDR           (0xFFFB0008) // （UDP）功能地址寄存器
#define AT91C_UDP_IER             (0xFFFB0010) // （UDP）中断启用寄存器
#define AT91C_UDP_IMR             (0xFFFB0018) // （UDP）中断掩码寄存器
#define AT91C_UDP_FDR             (0xFFFB0050) // （UDP）端点FIFO数据寄存器
// ============TC0外围设备的寄存器定义============
#define AT91C_TC0_IMR             (0xFFFA002C) // （TC0）中断掩码寄存器
#define AT91C_TC0_IER             (0xFFFA0024) // （TC0）中断启用寄存器
#define AT91C_TC0_RC              (0xFFFA001C) // （TC0）寄存器C
#define AT91C_TC0_RA              (0xFFFA0014) // （TC0）寄存器A
#define AT91C_TC0_CMR             (0xFFFA0004) // （TC0）信道模式寄存器（捕获模式/波形模式）
#define AT91C_TC0_IDR             (0xFFFA0028) // （TC0）中断禁用寄存器
#define AT91C_TC0_SR              (0xFFFA0020) // （TC0）状态寄存器
#define AT91C_TC0_RB              (0xFFFA0018) // （TC0）寄存器B
#define AT91C_TC0_CV              (0xFFFA0010) // （TC0）计数器值
#define AT91C_TC0_CCR             (0xFFFA0000) // （TC0）信道控制寄存器
// ==========TC1外围设备的寄存器定义==========
#define AT91C_TC1_IMR             (0xFFFA006C) // （TC1）中断掩码寄存器
#define AT91C_TC1_IER             (0xFFFA0064) // （TC1）中断启用寄存器
#define AT91C_TC1_RC              (0xFFFA005C) // （TC1）寄存器C
#define AT91C_TC1_RA              (0xFFFA0054) // （TC1）寄存器A
#define AT91C_TC1_CMR             (0xFFFA0044) // （TC1）信道模式寄存器（捕获模式/波形模式）
#define AT91C_TC1_IDR             (0xFFFA0068) // （TC1）中断禁用寄存器
#define AT91C_TC1_SR              (0xFFFA0060) // （TC1）状态寄存器
#define AT91C_TC1_RB              (0xFFFA0058) // （TC1）寄存器B
#define AT91C_TC1_CV              (0xFFFA0050) // （TC1）计数器值
#define AT91C_TC1_CCR             (0xFFFA0040) // （TC1）信道控制寄存器
// ============TC2外围设备的寄存器定义============
#define AT91C_TC2_IMR             (0xFFFA00AC) // （TC2）中断掩码寄存器
#define AT91C_TC2_IER             (0xFFFA00A4) // （TC2）中断启用寄存器
#define AT91C_TC2_RC              (0xFFFA009C) // （TC2）寄存器C
#define AT91C_TC2_RA              (0xFFFA0094) // （TC2）寄存器A
#define AT91C_TC2_CMR             (0xFFFA0084) // （TC2）信道模式寄存器（捕获模式/波形模式）
#define AT91C_TC2_IDR             (0xFFFA00A8) // （TC2）中断禁用寄存器
#define AT91C_TC2_SR              (0xFFFA00A0) // （TC2）状态寄存器
#define AT91C_TC2_RB              (0xFFFA0098) // （TC2）寄存器B
#define AT91C_TC2_CV              (0xFFFA0090) // （TC2）计数器值
#define AT91C_TC2_CCR             (0xFFFA0080) // （TC2）信道控制寄存器
// ==========TCB外围设备的寄存器定义==========
#define AT91C_TCB_BMR             (0xFFFA00C4) // （TCB）TC块模式寄存器
#define AT91C_TCB_BCR             (0xFFFA00C0) // （TCB）TC块控制寄存器
// ============CAN_MB0外围设备的寄存器定义============
#define AT91C_CAN_MB0_MCR         (0xFFFD021C) // （CAN_MB0）邮箱控制寄存器
#define AT91C_CAN_MB0_MDL         (0xFFFD0214) // （CAN_MB0）邮箱数据低寄存器
#define AT91C_CAN_MB0_MFID        (0xFFFD020C) // （CAN_MB0）邮箱系列ID寄存器
#define AT91C_CAN_MB0_MAM         (0xFFFD0204) // （CAN_MB0）邮箱接受掩码寄存器
#define AT91C_CAN_MB0_MDH         (0xFFFD0218) // （CAN_MB0）邮箱数据高位寄存器
#define AT91C_CAN_MB0_MSR         (0xFFFD0210) // （CAN_MB0）邮箱状态寄存器
#define AT91C_CAN_MB0_MID         (0xFFFD0208) // （CAN_MB0）邮箱ID寄存器
#define AT91C_CAN_MB0_MMR         (0xFFFD0200) // （CAN_MB0）邮箱模式寄存器
// ============CAN_MB1外围设备的寄存器定义============
#define AT91C_CAN_MB1_MCR         (0xFFFD023C) // （CAN_MB1）邮箱控制寄存器
#define AT91C_CAN_MB1_MDL         (0xFFFD0234) // （CAN_MB1）邮箱数据低寄存器
#define AT91C_CAN_MB1_MFID        (0xFFFD022C) // （CAN_MB1）邮箱系列ID寄存器
#define AT91C_CAN_MB1_MAM         (0xFFFD0224) // （CAN_MB1）邮箱接受掩码寄存器
#define AT91C_CAN_MB1_MDH         (0xFFFD0238) // （CAN_MB1）邮箱数据高位寄存器
#define AT91C_CAN_MB1_MSR         (0xFFFD0230) // （CAN_MB1）邮箱状态寄存器
#define AT91C_CAN_MB1_MID         (0xFFFD0228) // （CAN_MB1）邮箱ID寄存器
#define AT91C_CAN_MB1_MMR         (0xFFFD0220) // （CAN_MB1）邮箱模式寄存器
// ============CAN_MB2外围设备的寄存器定义============
#define AT91C_CAN_MB2_MCR         (0xFFFD025C) // （CAN_MB2）邮箱控制寄存器
#define AT91C_CAN_MB2_MDL         (0xFFFD0254) // （CAN_MB2）邮箱数据低寄存器
#define AT91C_CAN_MB2_MFID        (0xFFFD024C) // （CAN_MB2）邮箱系列ID寄存器
#define AT91C_CAN_MB2_MAM         (0xFFFD0244) // （CAN_MB2）邮箱接受掩码寄存器
#define AT91C_CAN_MB2_MDH         (0xFFFD0258) // （CAN_MB2）邮箱数据高位寄存器
#define AT91C_CAN_MB2_MSR         (0xFFFD0250) // （CAN_MB2）邮箱状态寄存器
#define AT91C_CAN_MB2_MID         (0xFFFD0248) // （CAN_MB2）邮箱ID寄存器
#define AT91C_CAN_MB2_MMR         (0xFFFD0240) // （CAN_MB2）邮箱模式寄存器
// ============CAN_MB3外围设备的寄存器定义============
#define AT91C_CAN_MB3_MCR         (0xFFFD027C) // （CAN_MB3）邮箱控制寄存器
#define AT91C_CAN_MB3_MDL         (0xFFFD0274) // （CAN_MB3）邮箱数据低寄存器
#define AT91C_CAN_MB3_MFID        (0xFFFD026C) // （CAN_MB3）邮箱系列ID寄存器
#define AT91C_CAN_MB3_MAM         (0xFFFD0264) // （CAN_MB3）邮箱接受掩码寄存器
#define AT91C_CAN_MB3_MDH         (0xFFFD0278) // （CAN_MB3）邮箱数据高位寄存器
#define AT91C_CAN_MB3_MSR         (0xFFFD0270) // （CAN_MB3）邮箱状态寄存器
#define AT91C_CAN_MB3_MID         (0xFFFD0268) // （CAN_MB3）邮箱ID寄存器
#define AT91C_CAN_MB3_MMR         (0xFFFD0260) // （CAN_MB3）邮箱模式寄存器
// ============CAN_MB4外围设备的寄存器定义============
#define AT91C_CAN_MB4_MCR         (0xFFFD029C) // （CAN_MB4）邮箱控制寄存器
#define AT91C_CAN_MB4_MDL         (0xFFFD0294) // （CAN_MB4）邮箱数据低寄存器
#define AT91C_CAN_MB4_MFID        (0xFFFD028C) // （CAN_MB4）邮箱系列ID寄存器
#define AT91C_CAN_MB4_MAM         (0xFFFD0284) // （CAN_MB4）邮箱接受掩码寄存器
#define AT91C_CAN_MB4_MDH         (0xFFFD0298) // （CAN_MB4）邮箱数据高位寄存器
#define AT91C_CAN_MB4_MSR         (0xFFFD0290) // （CAN_MB4）邮箱状态寄存器
#define AT91C_CAN_MB4_MID         (0xFFFD0288) // （CAN_MB4）邮箱ID寄存器
#define AT91C_CAN_MB4_MMR         (0xFFFD0280) // （CAN_MB4）邮箱模式寄存器
// ============CAN_MB5外围设备的寄存器定义============
#define AT91C_CAN_MB5_MCR         (0xFFFD02BC) // （CAN_MB5）邮箱控制寄存器
#define AT91C_CAN_MB5_MDL         (0xFFFD02B4) // （CAN_MB5）邮箱数据低寄存器
#define AT91C_CAN_MB5_MFID        (0xFFFD02AC) // （CAN_MB5）邮箱系列ID寄存器
#define AT91C_CAN_MB5_MAM         (0xFFFD02A4) // （CAN_MB5）邮箱接受掩码寄存器
#define AT91C_CAN_MB5_MDH         (0xFFFD02B8) // （CAN_MB5）邮箱数据高位寄存器
#define AT91C_CAN_MB5_MSR         (0xFFFD02B0) // （CAN_MB5）邮箱状态寄存器
#define AT91C_CAN_MB5_MID         (0xFFFD02A8) // （CAN_MB5）邮箱ID寄存器
#define AT91C_CAN_MB5_MMR         (0xFFFD02A0) // （CAN_MB5）邮箱模式寄存器
// ============CAN_MB6外围设备的寄存器定义============
#define AT91C_CAN_MB6_MAM         (0xFFFD02C4) // （CAN_MB6）邮箱接受掩码寄存器
#define AT91C_CAN_MB6_MDH         (0xFFFD02D8) // （CAN_MB6）邮箱数据高位寄存器
#define AT91C_CAN_MB6_MSR         (0xFFFD02D0) // （CAN_MB6）邮箱状态寄存器
#define AT91C_CAN_MB6_MID         (0xFFFD02C8) // （CAN_MB6）邮箱ID寄存器
#define AT91C_CAN_MB6_MMR         (0xFFFD02C0) // （CAN_MB6）邮箱模式寄存器
#define AT91C_CAN_MB6_MCR         (0xFFFD02DC) // （CAN_MB6）邮箱控制寄存器
#define AT91C_CAN_MB6_MDL         (0xFFFD02D4) // （CAN_MB6）邮箱数据低寄存器
#define AT91C_CAN_MB6_MFID        (0xFFFD02CC) // （CAN_MB6）邮箱系列ID寄存器
// ============CAN_MB7外围设备的寄存器定义============
#define AT91C_CAN_MB7_MDH         (0xFFFD02F8) // （CAN_MB7）邮箱数据高位寄存器
#define AT91C_CAN_MB7_MSR         (0xFFFD02F0) // （CAN_MB7）邮箱状态寄存器
#define AT91C_CAN_MB7_MID         (0xFFFD02E8) // （CAN_MB7）邮箱ID寄存器
#define AT91C_CAN_MB7_MMR         (0xFFFD02E0) // （CAN_MB7）邮箱模式寄存器
#define AT91C_CAN_MB7_MCR         (0xFFFD02FC) // （CAN_MB7）邮箱控制寄存器
#define AT91C_CAN_MB7_MDL         (0xFFFD02F4) // （CAN_MB7）邮箱数据低寄存器
#define AT91C_CAN_MB7_MFID        (0xFFFD02EC) // （CAN_MB7）邮箱系列ID寄存器
#define AT91C_CAN_MB7_MAM         (0xFFFD02E4) // （CAN_MB7）邮箱接受掩码寄存器
// ============CAN外围设备的寄存器定义============
#define AT91C_CAN_IMR             (0xFFFD000C) // （CAN）中断掩码寄存器
#define AT91C_CAN_IER             (0xFFFD0004) // （CAN）中断启用寄存器
#define AT91C_CAN_ECR             (0xFFFD0020) // （CAN）错误计数器寄存器
#define AT91C_CAN_TIM             (0xFFFD0018) // （CAN）计时器寄存器
#define AT91C_CAN_SR              (0xFFFD0010) // （CAN）状态寄存器
#define AT91C_CAN_IDR             (0xFFFD0008) // （CAN）中断禁用寄存器
#define AT91C_CAN_MR              (0xFFFD0000) // （CAN）模式寄存器
#define AT91C_CAN_BR              (0xFFFD0014) // （CAN）波特率寄存器
#define AT91C_CAN_TIMESTP         (0xFFFD001C) // （CAN）时间戳寄存器
#define AT91C_CAN_TCR             (0xFFFD0024) // （CAN）传输命令寄存器
#define AT91C_CAN_ACR             (0xFFFD0028) // （CAN）中止命令寄存器
#define AT91C_CAN_VR              (0xFFFD00FC) // （CAN）版本寄存器
// ============EMAC外围设备的寄存器定义============
#define AT91C_EMAC_TID            (0xFFFDC0B8) // （EMAC）类型ID检查寄存器
#define AT91C_EMAC_SA3L           (0xFFFDC0A8) // （EMAC）特定地址3底部，前4字节
#define AT91C_EMAC_STE            (0xFFFDC084) // （EMAC）SQE测试错误寄存器
#define AT91C_EMAC_RSE            (0xFFFDC074) // （EMAC）接收符号错误寄存器
#define AT91C_EMAC_IDR            (0xFFFDC02C) // （EMAC）中断禁用寄存器
#define AT91C_EMAC_TBQP           (0xFFFDC01C) // （EMAC）传输缓冲区队列指针
#define AT91C_EMAC_TPQ            (0xFFFDC0BC) // （EMAC）传输暂停量子寄存器
#define AT91C_EMAC_SA1L           (0xFFFDC098) // （EMAC）特定地址1底部，前4字节
#define AT91C_EMAC_RLE            (0xFFFDC088) // （EMAC）接收长度字段不匹配寄存器
#define AT91C_EMAC_IMR            (0xFFFDC030) // （EMAC）中断掩码寄存器
#define AT91C_EMAC_SA1H           (0xFFFDC09C) // （EMAC）特定地址1顶部，最后2个字节
#define AT91C_EMAC_PFR            (0xFFFDC03C) // （EMAC）暂停帧接收寄存器
#define AT91C_EMAC_FCSE           (0xFFFDC050) // （EMAC）帧检查序列错误寄存器
#define AT91C_EMAC_FTO            (0xFFFDC040) // （EMAC）帧发送OK寄存器
#define AT91C_EMAC_TUND           (0xFFFDC064) // （EMAC）传输欠载错误寄存器
#define AT91C_EMAC_ALE            (0xFFFDC054) // （EMAC）对齐错误寄存器
#define AT91C_EMAC_SCF            (0xFFFDC044) // （EMAC）单冲突帧寄存器
#define AT91C_EMAC_SA3H           (0xFFFDC0AC) // （EMAC）特定地址3顶部，最后2个字节
#define AT91C_EMAC_ELE            (0xFFFDC078) // （EMAC）过长错误寄存器
#define AT91C_EMAC_CSE            (0xFFFDC068) // （EMAC）载波检测错误寄存器
#define AT91C_EMAC_DTF            (0xFFFDC058) // （EMAC）延迟传输帧寄存器
#define AT91C_EMAC_RSR            (0xFFFDC020) // （EMAC）接收状态寄存器
#define AT91C_EMAC_USRIO          (0xFFFDC0C0) // （EMAC）用户输入/输出寄存器
#define AT91C_EMAC_SA4L           (0xFFFDC0B0) // （EMAC）特定地址4底部，前4字节
#define AT91C_EMAC_RRE            (0xFFFDC06C) // （EMAC）接收资源错误寄存器
#define AT91C_EMAC_RJA            (0xFFFDC07C) // （EMAC）接收Jabbers注册
#define AT91C_EMAC_TPF            (0xFFFDC08C) // （EMAC）发送暂停帧寄存器
#define AT91C_EMAC_ISR            (0xFFFDC024) // （EMAC）中断状态寄存器
#define AT91C_EMAC_MAN            (0xFFFDC034) // （EMAC）PHY维护寄存器
#define AT91C_EMAC_WOL            (0xFFFDC0C4) // （EMAC）LAN唤醒寄存器
#define AT91C_EMAC_USF            (0xFFFDC080) // （EMAC）缩小帧寄存器
#define AT91C_EMAC_HRB            (0xFFFDC090) // （EMAC）哈希地址底部[31:0]
#define AT91C_EMAC_PTR            (0xFFFDC038) // （EMAC）暂停时间寄存器
#define AT91C_EMAC_HRT            (0xFFFDC094) // （EMAC）哈希地址顶部[63:32]
#define AT91C_EMAC_REV            (0xFFFDC0FC) // （EMAC）修订登记簿
#define AT91C_EMAC_MCF            (0xFFFDC048) // （EMAC）多冲突帧寄存器
#define AT91C_EMAC_SA2L           (0xFFFDC0A0) // （EMAC）特定地址2底部，前4字节
#define AT91C_EMAC_NCR            (0xFFFDC000) // （EMAC）网络控制寄存器
#define AT91C_EMAC_FRO            (0xFFFDC04C) // （EMAC）帧接收OK寄存器
#define AT91C_EMAC_LCOL           (0xFFFDC05C) // （EMAC）延迟碰撞寄存器
#define AT91C_EMAC_SA4H           (0xFFFDC0B4) // （EMAC）特定地址4顶部，最后2个字节
#define AT91C_EMAC_NCFGR          (0xFFFDC004) // （EMAC）网络配置寄存器
#define AT91C_EMAC_TSR            (0xFFFDC014) // （EMAC）传输状态寄存器
#define AT91C_EMAC_SA2H           (0xFFFDC0A4) // （EMAC）特定地址2顶部，最后2个字节
#define AT91C_EMAC_ECOL           (0xFFFDC060) // （EMAC）过度冲突寄存器
#define AT91C_EMAC_ROV            (0xFFFDC070) // （EMAC）接收溢出错误寄存器
#define AT91C_EMAC_NSR            (0xFFFDC008) // （EMAC）网络状态寄存器
#define AT91C_EMAC_RBQP           (0xFFFDC018) // （EMAC）接收缓冲区队列指针
#define AT91C_EMAC_IER            (0xFFFDC028) // （EMAC）中断启用寄存器
// ============PDC_ADC外围设备的寄存器定义============
#define AT91C_ADC_PTCR            (0xFFFD8120) // （PDC_ADC）PDC传输控制寄存器
#define AT91C_ADC_TNPR            (0xFFFD8118) // （PDC_ADC）发送下一个指针寄存器
#define AT91C_ADC_RNPR            (0xFFFD8110) // （PDC_ADC）接收下一个指针寄存器
#define AT91C_ADC_TPR             (0xFFFD8108) // （PDC_ADC）传输指针寄存器
#define AT91C_ADC_RPR             (0xFFFD8100) // （PDC_ADC）接收指针寄存器
#define AT91C_ADC_PTSR            (0xFFFD8124) // （PDC_ADC）PDC传输状态寄存器
#define AT91C_ADC_TNCR            (0xFFFD811C) // （PDC_ADC）发送下一计数器寄存器
#define AT91C_ADC_RNCR            (0xFFFD8114) // （PDC_ADC）接收下一计数器寄存器
#define AT91C_ADC_TCR             (0xFFFD810C) // （PDC_ADC）发送计数器寄存器
#define AT91C_ADC_RCR             (0xFFFD8104) // （PDC_ADC）接收计数器寄存器
// ============ADC外围设备的寄存器定义============
#define AT91C_ADC_IMR             (0xFFFD802C) // （ADC）ADC中断掩码寄存器
#define AT91C_ADC_CDR4            (0xFFFD8040) // （ADC）ADC通道数据寄存器4
#define AT91C_ADC_CDR2            (0xFFFD8038) // （ADC）ADC通道数据寄存器2
#define AT91C_ADC_CDR0            (0xFFFD8030) // （ADC）ADC通道数据寄存器0
#define AT91C_ADC_CDR7            (0xFFFD804C) // （ADC）ADC通道数据寄存器7
#define AT91C_ADC_CDR1            (0xFFFD8034) // （ADC）ADC通道数据寄存器1
#define AT91C_ADC_CDR3            (0xFFFD803C) // （ADC）ADC通道数据寄存器3
#define AT91C_ADC_CDR5            (0xFFFD8044) // （ADC）ADC通道数据寄存器5
#define AT91C_ADC_MR              (0xFFFD8004) // （ADC）ADC模式寄存器
#define AT91C_ADC_CDR6            (0xFFFD8048) // （ADC）ADC通道数据寄存器6
#define AT91C_ADC_CR              (0xFFFD8000) // （ADC）ADC控制寄存器
#define AT91C_ADC_CHER            (0xFFFD8010) // （ADC）ADC通道启用寄存器
#define AT91C_ADC_CHSR            (0xFFFD8018) // （ADC）ADC通道状态寄存器
#define AT91C_ADC_IER             (0xFFFD8024) // （ADC）ADC中断启用寄存器
#define AT91C_ADC_SR              (0xFFFD801C) // （ADC）ADC状态寄存器
#define AT91C_ADC_CHDR            (0xFFFD8014) // （ADC）ADC通道禁用寄存器
#define AT91C_ADC_IDR             (0xFFFD8028) // （ADC）ADC中断禁用寄存器
#define AT91C_ADC_LCDR            (0xFFFD8020) // （ADC）ADC上次转换数据寄存器

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_PIO_PA0             (1 <<  0) // 引脚由PA0控制
#define AT91C_PA0_RXD0            (AT91C_PIO_PA0) //  USART 0接收数据
#define AT91C_PIO_PA1             (1 <<  1) // 引脚由PA1控制
#define AT91C_PA1_TXD0            (AT91C_PIO_PA1) //  USART 0传输数据
#define AT91C_PIO_PA10            (1 << 10) // 引脚由PA10控制
#define AT91C_PA10_TWD            (AT91C_PIO_PA10) //  TWI双线串行数据
#define AT91C_PIO_PA11            (1 << 11) // 引脚由PA11控制
#define AT91C_PA11_TWCK           (AT91C_PIO_PA11) //  TWI双线串行时钟
#define AT91C_PIO_PA12            (1 << 12) // 引脚由PA12控制
#define AT91C_PA12_SPI0_NPCS0     (AT91C_PIO_PA12) //  SPI 0外围芯片选择0
#define AT91C_PIO_PA13            (1 << 13) // 引脚由PA13控制
#define AT91C_PA13_SPI0_NPCS1     (AT91C_PIO_PA13) //  SPI 0外围芯片选择1
#define AT91C_PA13_PCK1           (AT91C_PIO_PA13) //  PMC可编程时钟输出1
#define AT91C_PIO_PA14            (1 << 14) // 引脚由PA14控制
#define AT91C_PA14_SPI0_NPCS2     (AT91C_PIO_PA14) //  SPI 0外围芯片选择2
#define AT91C_PA14_IRQ1           (AT91C_PIO_PA14) //  外部中断1
#define AT91C_PIO_PA15            (1 << 15) // 引脚由PA15控制
#define AT91C_PA15_SPI0_NPCS3     (AT91C_PIO_PA15) //  SPI 0外围芯片选择3
#define AT91C_PA15_TCLK2          (AT91C_PIO_PA15) //  定时器计数器2外部时钟输入
#define AT91C_PIO_PA16            (1 << 16) // 引脚由PA16控制
#define AT91C_PA16_SPI0_MISO      (AT91C_PIO_PA16) //  SPI 0主从
#define AT91C_PIO_PA17            (1 << 17) // 引脚由PA17控制
#define AT91C_PA17_SPI0_MOSI      (AT91C_PIO_PA17) //  SPI 0主输出从
#define AT91C_PIO_PA18            (1 << 18) // 引脚由PA18控制
#define AT91C_PA18_SPI0_SPCK      (AT91C_PIO_PA18) //  SPI 0串行时钟
#define AT91C_PIO_PA19            (1 << 19) // 引脚由PA19控制
#define AT91C_PA19_CANRX          (AT91C_PIO_PA19) //  CAN接收
#define AT91C_PIO_PA2             (1 <<  2) // 引脚由PA2控制
#define AT91C_PA2_SCK0            (AT91C_PIO_PA2) //  USART 0串行时钟
#define AT91C_PA2_SPI1_NPCS1      (AT91C_PIO_PA2) //  SPI 1外围芯片选择1
#define AT91C_PIO_PA20            (1 << 20) // 引脚由PA20控制
#define AT91C_PA20_CANTX          (AT91C_PIO_PA20) //  CAN传输
#define AT91C_PIO_PA21            (1 << 21) // 引脚由PA21控制
#define AT91C_PA21_TF             (AT91C_PIO_PA21) //  SSC传输帧同步
#define AT91C_PA21_SPI1_NPCS0     (AT91C_PIO_PA21) //  SPI 1外围芯片选择0
#define AT91C_PIO_PA22            (1 << 22) // 引脚由PA22控制
#define AT91C_PA22_TK             (AT91C_PIO_PA22) //  SSC发送时钟
#define AT91C_PA22_SPI1_SPCK      (AT91C_PIO_PA22) //  SPI 1串行时钟
#define AT91C_PIO_PA23            (1 << 23) // 引脚由PA23控制
#define AT91C_PA23_TD             (AT91C_PIO_PA23) //  SSC传输数据
#define AT91C_PA23_SPI1_MOSI      (AT91C_PIO_PA23) //  SPI 1主输出从
#define AT91C_PIO_PA24            (1 << 24) // 引脚由PA24控制
#define AT91C_PA24_RD             (AT91C_PIO_PA24) //  SSC接收数据
#define AT91C_PA24_SPI1_MISO      (AT91C_PIO_PA24) //  SPI 1主从
#define AT91C_PIO_PA25            (1 << 25) // 引脚由PA25控制
#define AT91C_PA25_RK             (AT91C_PIO_PA25) //  SSC接收时钟
#define AT91C_PA25_SPI1_NPCS1     (AT91C_PIO_PA25) //  SPI 1外围芯片选择1
#define AT91C_PIO_PA26            (1 << 26) // 引脚由PA26控制
#define AT91C_PA26_RF             (AT91C_PIO_PA26) //  SSC接收帧同步
#define AT91C_PA26_SPI1_NPCS2     (AT91C_PIO_PA26) //  SPI 1外围芯片选择2
#define AT91C_PIO_PA27            (1 << 27) // 引脚由PA27控制
#define AT91C_PA27_DRXD           (AT91C_PIO_PA27) //  DBGU调试接收数据
#define AT91C_PA27_PCK3           (AT91C_PIO_PA27) //  PMC可编程时钟输出3
#define AT91C_PIO_PA28            (1 << 28) // 引脚由PA28控制
#define AT91C_PA28_DTXD           (AT91C_PIO_PA28) //  DBGU调试传输数据
#define AT91C_PIO_PA29            (1 << 29) // 引脚由PA29控制
#define AT91C_PA29_FIQ            (AT91C_PIO_PA29) //  AIC快速中断输入
#define AT91C_PA29_SPI1_NPCS3     (AT91C_PIO_PA29) //  SPI 1外围芯片选择3
#define AT91C_PIO_PA3             (1 <<  3) // 引脚由PA3控制
#define AT91C_PA3_RTS0            (AT91C_PIO_PA3) //  USART 0准备发送
#define AT91C_PA3_SPI1_NPCS2      (AT91C_PIO_PA3) //  SPI 1外围芯片选择2
#define AT91C_PIO_PA30            (1 << 30) // 引脚由PA30控制
#define AT91C_PA30_IRQ0           (AT91C_PIO_PA30) //  外部中断0
#define AT91C_PA30_PCK2           (AT91C_PIO_PA30) //  PMC可编程时钟输出2
#define AT91C_PIO_PA4             (1 <<  4) // 引脚由PA4控制
#define AT91C_PA4_CTS0            (AT91C_PIO_PA4) //  USART 0清除发送
#define AT91C_PA4_SPI1_NPCS3      (AT91C_PIO_PA4) //  SPI 1外围芯片选择3
#define AT91C_PIO_PA5             (1 <<  5) // 引脚由PA5控制
#define AT91C_PA5_RXD1            (AT91C_PIO_PA5) //  USART 1接收数据
#define AT91C_PIO_PA6             (1 <<  6) // 引脚由PA6控制
#define AT91C_PA6_TXD1            (AT91C_PIO_PA6) //  USART 1传输数据
#define AT91C_PIO_PA7             (1 <<  7) // 引脚由PA7控制
#define AT91C_PA7_SCK1            (AT91C_PIO_PA7) //  USART 1串行时钟
#define AT91C_PA7_SPI0_NPCS1      (AT91C_PIO_PA7) //  SPI 0外围芯片选择1
#define AT91C_PIO_PA8             (1 <<  8) // 引脚由PA8控制
#define AT91C_PA8_RTS1            (AT91C_PIO_PA8) //  USART 1准备发送
#define AT91C_PA8_SPI0_NPCS2      (AT91C_PIO_PA8) //  SPI 0外围芯片选择2
#define AT91C_PIO_PA9             (1 <<  9) // 引脚由PA9控制
#define AT91C_PA9_CTS1            (AT91C_PIO_PA9) //  USART 1清除发送
#define AT91C_PA9_SPI0_NPCS3      (AT91C_PIO_PA9) //  SPI 0外围芯片选择3
#define AT91C_PIO_PB0             (1 <<  0) // 引脚由PB0控制
#define AT91C_PB0_ETXCK_EREFCK    (AT91C_PIO_PB0) //  以太网MAC传输时钟/参考时钟
#define AT91C_PB0_PCK0            (AT91C_PIO_PB0) //  PMC可编程时钟输出0
#define AT91C_PIO_PB1             (1 <<  1) // 引脚由PB1控制
#define AT91C_PB1_ETXEN           (AT91C_PIO_PB1) //  以太网MAC传输启用
#define AT91C_PIO_PB10            (1 << 10) // 由PB10控制的引脚
#define AT91C_PB10_ETX2           (AT91C_PIO_PB10) //  以太网MAC传输数据2
#define AT91C_PB10_SPI1_NPCS1     (AT91C_PIO_PB10) //  SPI 1外围芯片选择1
#define AT91C_PIO_PB11            (1 << 11) // 引脚由PB11控制
#define AT91C_PB11_ETX3           (AT91C_PIO_PB11) //  以太网MAC传输数据3
#define AT91C_PB11_SPI1_NPCS2     (AT91C_PIO_PB11) //  SPI 1外围芯片选择2
#define AT91C_PIO_PB12            (1 << 12) // 引脚由PB12控制
#define AT91C_PB12_ETXER          (AT91C_PIO_PB12) //  以太网MAC传输编码错误
#define AT91C_PB12_TCLK0          (AT91C_PIO_PB12) //  定时器计数器0外部时钟输入
#define AT91C_PIO_PB13            (1 << 13) // 引脚由PB13控制
#define AT91C_PB13_ERX2           (AT91C_PIO_PB13) //  以太网MAC接收数据2
#define AT91C_PB13_SPI0_NPCS1     (AT91C_PIO_PB13) //  SPI 0外围芯片选择1
#define AT91C_PIO_PB14            (1 << 14) // 引脚由PB14控制
#define AT91C_PB14_ERX3           (AT91C_PIO_PB14) //  以太网MAC接收数据3
#define AT91C_PB14_SPI0_NPCS2     (AT91C_PIO_PB14) //  SPI 0外围芯片选择2
#define AT91C_PIO_PB15            (1 << 15) // 引脚由PB15控制
#define AT91C_PB15_ERXDV_ECRSDV   (AT91C_PIO_PB15) //  以太网MAC接收数据有效
#define AT91C_PIO_PB16            (1 << 16) // 引脚由PB16控制
#define AT91C_PB16_ECOL           (AT91C_PIO_PB16) //  检测到以太网MAC冲突
#define AT91C_PB16_SPI1_NPCS3     (AT91C_PIO_PB16) //  SPI 1外围芯片选择3
#define AT91C_PIO_PB17            (1 << 17) // 引脚由PB17控制
#define AT91C_PB17_ERXCK          (AT91C_PIO_PB17) //  以太网MAC接收时钟
#define AT91C_PB17_SPI0_NPCS3     (AT91C_PIO_PB17) //  SPI 0外围芯片选择3
#define AT91C_PIO_PB18            (1 << 18) // 引脚由PB18控制
#define AT91C_PB18_EF100          (AT91C_PIO_PB18) //  以太网MAC强制100 Mbit/s
#define AT91C_PB18_ADTRG          (AT91C_PIO_PB18) //  ADC外部触发器
#define AT91C_PIO_PB19            (1 << 19) // 引脚由PB19控制
#define AT91C_PB19_PWM0           (AT91C_PIO_PB19) //  PWM通道0
#define AT91C_PB19_TCLK1          (AT91C_PIO_PB19) //  定时器计数器1外部时钟输入
#define AT91C_PIO_PB2             (1 <<  2) // 引脚由PB2控制
#define AT91C_PB2_ETX0            (AT91C_PIO_PB2) //  以太网MAC传输数据0
#define AT91C_PIO_PB20            (1 << 20) // 由PB20控制的引脚
#define AT91C_PB20_PWM1           (AT91C_PIO_PB20) //  PWM通道1
#define AT91C_PB20_PCK0           (AT91C_PIO_PB20) //  PMC可编程时钟输出0
#define AT91C_PIO_PB21            (1 << 21) // 引脚由PB21控制
#define AT91C_PB21_PWM2           (AT91C_PIO_PB21) //  PWM通道2
#define AT91C_PB21_PCK1           (AT91C_PIO_PB21) //  PMC可编程时钟输出1
#define AT91C_PIO_PB22            (1 << 22) // 引脚由PB22控制
#define AT91C_PB22_PWM3           (AT91C_PIO_PB22) //  PWM通道3
#define AT91C_PB22_PCK2           (AT91C_PIO_PB22) //  PMC可编程时钟输出2
#define AT91C_PIO_PB23            (1 << 23) // 引脚由PB23控制
#define AT91C_PB23_TIOA0          (AT91C_PIO_PB23) //  定时器计数器0多用途定时器I/O引脚A
#define AT91C_PB23_DCD1           (AT91C_PIO_PB23) //  USART 1数据载体检测
#define AT91C_PIO_PB24            (1 << 24) // 引脚由PB24控制
#define AT91C_PB24_TIOB0          (AT91C_PIO_PB24) //  定时器计数器0多用途定时器I/O引脚B
#define AT91C_PB24_DSR1           (AT91C_PIO_PB24) //  USART 1数据集就绪
#define AT91C_PIO_PB25            (1 << 25) // 由PB25控制的引脚
#define AT91C_PB25_TIOA1          (AT91C_PIO_PB25) //  定时器计数器1多用途定时器I/O引脚A
#define AT91C_PB25_DTR1           (AT91C_PIO_PB25) //  USART 1数据终端准备就绪
#define AT91C_PIO_PB26            (1 << 26) // 由PB26控制的引脚
#define AT91C_PB26_TIOB1          (AT91C_PIO_PB26) //  定时器计数器1多用途定时器I/O引脚B
#define AT91C_PB26_RI1            (AT91C_PIO_PB26) //  USART 1环指示器
#define AT91C_PIO_PB27            (1 << 27) // 引脚由PB27控制
#define AT91C_PB27_TIOA2          (AT91C_PIO_PB27) //  定时器计数器2多用途定时器I/O引脚A
#define AT91C_PB27_PWM0           (AT91C_PIO_PB27) //  PWM通道0
#define AT91C_PIO_PB28            (1 << 28) // 引脚由PB28控制
#define AT91C_PB28_TIOB2          (AT91C_PIO_PB28) //  定时器计数器2多用途定时器I/O引脚B
#define AT91C_PB28_PWM1           (AT91C_PIO_PB28) //  PWM通道1
#define AT91C_PIO_PB29            (1 << 29) // 由PB29控制的引脚
#define AT91C_PB29_PCK1           (AT91C_PIO_PB29) //  PMC可编程时钟输出1
#define AT91C_PB29_PWM2           (AT91C_PIO_PB29) //  PWM通道2
#define AT91C_PIO_PB3             (1 <<  3) // 引脚由PB3控制
#define AT91C_PB3_ETX1            (AT91C_PIO_PB3) //  以太网MAC传输数据1
#define AT91C_PIO_PB30            (1 << 30) // 引脚由PB30控制
#define AT91C_PB30_PCK2           (AT91C_PIO_PB30) //  PMC可编程时钟输出2
#define AT91C_PB30_PWM3           (AT91C_PIO_PB30) //  PWM通道3
#define AT91C_PIO_PB4             (1 <<  4) // 引脚由PB4控制
#define AT91C_PB4_ECRS            (AT91C_PIO_PB4) //  以太网MAC载波检测/载波检测和数据有效
#define AT91C_PIO_PB5             (1 <<  5) // 引脚由PB5控制
#define AT91C_PB5_ERX0            (AT91C_PIO_PB5) //  以太网MAC接收数据0
#define AT91C_PIO_PB6             (1 <<  6) // 引脚由PB6控制
#define AT91C_PB6_ERX1            (AT91C_PIO_PB6) //  以太网MAC接收数据1
#define AT91C_PIO_PB7             (1 <<  7) // 引脚由PB7控制
#define AT91C_PB7_ERXER           (AT91C_PIO_PB7) //  以太网MAC接收错误
#define AT91C_PIO_PB8             (1 <<  8) // 引脚由PB8控制
#define AT91C_PB8_EMDC            (AT91C_PIO_PB8) //  以太网MAC管理数据时钟
#define AT91C_PIO_PB9             (1 <<  9) // 引脚由PB9控制
#define AT91C_PB9_EMDIO           (AT91C_PIO_PB9) //  以太网MAC管理数据输入/输出

// *****************************************************************************
//               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_ID_FIQ              ( 0) // 高级中断控制器（FIQ）
#define AT91C_ID_SYS              ( 1) // 系统外围设备
#define AT91C_ID_PIOA             ( 2) // 并行IO控制器A
#define AT91C_ID_PIOB             ( 3) // 并行IO控制器B
#define AT91C_ID_SPI0             ( 4) // 串行外围接口0
#define AT91C_ID_SPI1             ( 5) // 串行外围接口1
#define AT91C_ID_US0              ( 6) // USART 0
#define AT91C_ID_US1              ( 7) // USART 1
#define AT91C_ID_SSC              ( 8) // 串行同步控制器
#define AT91C_ID_TWI              ( 9) // 双线接口
#define AT91C_ID_PWMC             (10) // PWM控制器
#define AT91C_ID_UDP              (11) // USB设备端口
#define AT91C_ID_TC0              (12) // 计时器计数器0
#define AT91C_ID_TC1              (13) // 计时器计数器1
#define AT91C_ID_TC2              (14) // 计时器计数器2
#define AT91C_ID_CAN              (15) // 控制区域网络控制器
#define AT91C_ID_EMAC             (16) // 以太网MAC
#define AT91C_ID_ADC              (17) // 模数转换器
#define AT91C_ID_18_Reserved      (18) // 保留
#define AT91C_ID_19_Reserved      (19) // 保留
#define AT91C_ID_20_Reserved      (20) // 保留
#define AT91C_ID_21_Reserved      (21) // 保留
#define AT91C_ID_22_Reserved      (22) // 保留
#define AT91C_ID_23_Reserved      (23) // 保留
#define AT91C_ID_24_Reserved      (24) // 保留
#define AT91C_ID_25_Reserved      (25) // 保留
#define AT91C_ID_26_Reserved      (26) // 保留
#define AT91C_ID_27_Reserved      (27) // 保留
#define AT91C_ID_28_Reserved      (28) // 保留
#define AT91C_ID_29_Reserved      (29) // 保留
#define AT91C_ID_IRQ0             (30) // 高级中断控制器（IRQ0）
#define AT91C_ID_IRQ1             (31) // 高级中断控制器（IRQ1）
#define AT91C_ALL_INT             (0xC003FFFF) // ALL VALID INTERRUPTS

// *****************************************************************************
//               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_BASE_SYS            (0xFFFFF000) // （SYS）基址
#define AT91C_BASE_AIC            (0xFFFFF000) // （AIC）基本地址
#define AT91C_BASE_PDC_DBGU       (0xFFFFF300) // （PDC_DBGU）基址
#define AT91C_BASE_DBGU           (0xFFFFF200) // （DBGU）基址
#define AT91C_BASE_PIOA           (0xFFFFF400) // （PIOA）基本地址
#define AT91C_BASE_PIOB           (0xFFFFF600) // （PIOB）基址
#define AT91C_BASE_CKGR           (0xFFFFFC20) // （CKGR）基址
#define AT91C_BASE_PMC            (0xFFFFFC00) // （PMC）基址
#define AT91C_BASE_RSTC           (0xFFFFFD00) // （RSTC）基址
#define AT91C_BASE_RTTC           (0xFFFFFD20) // （RTTC）基址
#define AT91C_BASE_PITC           (0xFFFFFD30) // （PITC）基址
#define AT91C_BASE_WDTC           (0xFFFFFD40) // （WDTC）基址
#define AT91C_BASE_VREG           (0xFFFFFD60) // （VREG）基址
#define AT91C_BASE_MC             (0xFFFFFF00) // （MC）基址
#define AT91C_BASE_PDC_SPI1       (0xFFFE4100) // （PDC_SPI1）基址
#define AT91C_BASE_SPI1           (0xFFFE4000) // （SPI1）基址
#define AT91C_BASE_PDC_SPI0       (0xFFFE0100) // （PDC_SPI0）基址
#define AT91C_BASE_SPI0           (0xFFFE0000) // （SPI0）基址
#define AT91C_BASE_PDC_US1        (0xFFFC4100) // （PDC_US1）基址
#define AT91C_BASE_US1            (0xFFFC4000) // （US1）基址
#define AT91C_BASE_PDC_US0        (0xFFFC0100) // （PDC_US0）基址
#define AT91C_BASE_US0            (0xFFFC0000) // （US0）基址
#define AT91C_BASE_PDC_SSC        (0xFFFD4100) // （PDC_SSC）基址
#define AT91C_BASE_SSC            (0xFFFD4000) // （SSC）基址
#define AT91C_BASE_TWI            (0xFFFB8000) // （TWI）基址
#define AT91C_BASE_PWMC_CH3       (0xFFFCC260) // （PWMC_CH3）基址
#define AT91C_BASE_PWMC_CH2       (0xFFFCC240) // （PWMC_CH2）基址
#define AT91C_BASE_PWMC_CH1       (0xFFFCC220) // （PWMC_CH1）基址
#define AT91C_BASE_PWMC_CH0       (0xFFFCC200) // （PWMC_CH0）基址
#define AT91C_BASE_PWMC           (0xFFFCC000) // （PWMC）基址
#define AT91C_BASE_UDP            (0xFFFB0000) // （UDP）基址
#define AT91C_BASE_TC0            (0xFFFA0000) // （TC0）基址
#define AT91C_BASE_TC1            (0xFFFA0040) // （TC1）基址
#define AT91C_BASE_TC2            (0xFFFA0080) // （TC2）基址
#define AT91C_BASE_TCB            (0xFFFA0000) // （TCB）基址
#define AT91C_BASE_CAN_MB0        (0xFFFD0200) // （CAN_MB0）基址
#define AT91C_BASE_CAN_MB1        (0xFFFD0220) // （CAN_MB1）基址
#define AT91C_BASE_CAN_MB2        (0xFFFD0240) // （CAN_MB2）基址
#define AT91C_BASE_CAN_MB3        (0xFFFD0260) // （CAN_MB3）基址
#define AT91C_BASE_CAN_MB4        (0xFFFD0280) // （CAN_MB4）基址
#define AT91C_BASE_CAN_MB5        (0xFFFD02A0) // （CAN_MB5）基址
#define AT91C_BASE_CAN_MB6        (0xFFFD02C0) // （CAN_MB6）基址
#define AT91C_BASE_CAN_MB7        (0xFFFD02E0) // （CAN_MB7）基址
#define AT91C_BASE_CAN            (0xFFFD0000) // （CAN）基址
#define AT91C_BASE_EMAC           (0xFFFDC000) // （EMAC）基本地址
#define AT91C_BASE_PDC_ADC        (0xFFFD8100) // （PDC_ADC）基址
#define AT91C_BASE_ADC            (0xFFFD8000) // （ADC）基址

// *****************************************************************************
//               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
// ISRAM
#define AT91C_ISRAM	              (0x00200000) // 内部SRAM基址
#define AT91C_ISRAM_SIZE	         (0x00010000) // 内部SRAM大小（字节）（64 KB）
// IFLASH
#define AT91C_IFLASH	             (0x00100000) // 内部FLASH基地址
#define AT91C_IFLASH_SIZE	        (0x00040000) // 内部FLASH大小（字节）（256 KB）
#define AT91C_IFLASH_PAGE_SIZE	   (256) // 内部FLASH页面大小：256字节
#define AT91C_IFLASH_LOCK_REGION_SIZE	 (16384) // 内部FLASH锁定区域大小：16 KB
#define AT91C_IFLASH_NB_OF_PAGES	 (1024) // 内部FLASH页数：1024字节
#define AT91C_IFLASH_NB_OF_LOCK_BITS	 (16) // 内部FLASH锁定位数：16字节



