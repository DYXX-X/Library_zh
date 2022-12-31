/*
 * 版权所有（C）2019 Dialog Semiconductor。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 * -源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 * -二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 * -未经事先书面许可，Dialog Semiconductor的名称或其贡献者的姓名均不得用于支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @file     DA1469xAB.h型
 * @brief    CMSIS头文件
 * @version  1.2
 * @date     22.2019年4月
 * @note     由SVDConv V3.3.25于2019年4月22日星期一11:06:30从文件“DA1469xAB.xml”生成，
 */



/** @addtogroup PLA_BSP_REGISTERS @{
  */


/** @addtogroup DA1469倍@{
  */


#ifndef DA1469X_H
#define DA1469X_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup CMSIS配置@{
  */


/* =========================================================================================================================== */
/* ====================中断号定义====================*/
/* =========================================================================================================================== */

/**
  * @brief 中断编号定义
  */

typedef enum {
/* ===================================ARM Cortex-M33特定中断号==========================================*/
  Reset_IRQn                = -15,              /*!< -15重置矢量，在通电和热重置时调用*/
  NonMaskableInt_IRQn       = -14,              /*!< -14不可屏蔽中断，无法停止或抢占*/
  HardFault_IRQn            = -13,              /*!< -13硬故障，所有类型的故障*/
  MemoryManagement_IRQn     = -12,              /*!< -12内存管理，MPU不匹配，包括访问冲突和不匹配*/
  BusFault_IRQn             = -11,              /*!< -11总线故障、预取、内存访问故障、其他地址/内存相关故障*/
  UsageFault_IRQn           = -10,              /*!< -10使用故障，即未定义指令、非法状态转换*/
  SecureFault_IRQn          =  -9,              /*!< -9安全故障处理程序*/
  SVCall_IRQn               =  -5,              /*!< -5通过SVC指令的系统服务呼叫*/
  DebugMonitor_IRQn         =  -4,              /*!< -4调试监视器*/
  PendSV_IRQn               =  -2,              /*!< -2系统服务的可挂起请求*/
  SysTick_IRQn              =  -1,              /*!< -1系统滴答计时器*/
/* ===================================DA1469x特定中断数==========================================*/
  SNC_IRQn                  =   0,              /*!< 0传感器节点控制器中断请求。*/
  DMA_IRQn                  =   1,              /*!< 1通用DMA中断请求。*/
  CHARGER_STATE_IRQn        =   2,              /*!< 2充电器状态中断请求。*/
  CHARGER_ERROR_IRQn        =   3,              /*!< 3充电器错误中断请求。*/
  CMAC2SYS_IRQn             =   4,              /*!< 4 CMAC和邮箱中断请求。*/
  UART_IRQn                 =   5,              /*!< 5 UART中断请求。*/
  UART2_IRQn                =   6,              /*!< 6 UART2中断请求。*/
  UART3_IRQn                =   7,              /*!< 7 UART3中断请求。*/
  I2C_IRQn                  =   8,              /*!< 8 I2C中断请求。*/
  I2C2_IRQn                 =   9,              /*!< 9 I2C2中断请求。*/
  SPI_IRQn                  =  10,              /*!< 10 SPI中断请求。*/
  SPI2_IRQn                 =  11,              /*!< 11 SPI2中断请求。*/
  PCM_IRQn                  =  12,              /*!< 12 PCM中断请求。*/
  SRC_IN_IRQn               =  13,              /*!< 13 SRC输入中断请求。*/
  SRC_OUT_IRQn              =  14,              /*!< 14 SRC输出中断请求。*/
  USB_IRQn                  =  15,              /*!< 15 USB中断请求。*/
  TIMER_IRQn                =  16,              /*!< 16 TIMER中断请求。*/
  TIMER2_IRQn               =  17,              /*!< 17 TIMER2中断请求。*/
  RTC_IRQn                  =  18,              /*!< 18 RTC中断请求。*/
  KEY_WKUP_GPIO_IRQn        =  19,              /*!< 19释放按钮按下中断请求。*/
  PDC_IRQn                  =  20,              /*!< 20从PDC到CM33唤醒IRQ*/
  VBUS_IRQn                 =  21,              /*!< 21 VBUS存在中断请求。*/
  MRM_IRQn                  =  22,              /*!< 22高速缓存未命中率监视器中断请求。*/
  MOTOR_CONTROLLER_IRQn     =  23,              /*!< 23 MOTOR和邮箱中断请求。*/
  TRNG_IRQn                 =  24,              /*!< 24真随机数生成中断请求。*/
  DCDC_IRQn                 =  25,              /*!< 25 DCDC中断请求。*/
  XTAL32M_RDY_IRQn          =  26,              /*!< 26 XTAL32M修整和就绪中断请求。*/
  GPADC_IRQn                =  27,              /*!< 27通用模数转换器中断请求。*/
  SDADC_IRQn                =  28,              /*!< 28 Sigma Delta模数转换器中断请求。*/
  CRYPTO_IRQn               =  29,              /*!< 29加密中断请求。*/
  CAPTIMER_IRQn             =  30,              /*!< 30 GPIO触发的定时器捕获中断请求。*/
  RFDIAG_IRQn               =  31,              /*!< 31基带或无线电诊断中断请求。*/
  LCD_CONTROLLER_IRQn       =  32,              /*!< 32并行LCD控制器中断请求。*/
  PLL_LOCK_IRQn             =  33,              /*!< 33 Pll锁定中断请求。*/
  TIMER3_IRQn               =  34,              /*!< 34 TIMER3中断请求。*/
  TIMER4_IRQn               =  35,              /*!< 35 TIMER4中断请求。*/
  LRA_IRQn                  =  36,              /*!< 36 LRA/ERM中断请求。*/
  RTC_EVENT_IRQn            =  37,              /*!< 37 RTC事件中断请求。*/
  GPIO_P0_IRQn              =  38,              /*!< 38 GPIO端口0切换中断请求。*/
  GPIO_P1_IRQn              =  39               /*!< 39 GPIO端口1触发中断请求。*/
} IRQn_Type;



/* =========================================================================================================================== */
/* ====================处理器和核心外围部分====================*/
/* =========================================================================================================================== */

/* =========================ARM Cortex-M33处理器和核心外围设备的配置============================*/
#define __CM33_REV                 0x0000U      /*!< CM33核心版本*/
#define __NVIC_PRIO_BITS               4        /*!< 用于优先级的位数*/
#define __Vendor_SysTickConfig         0        /*!< 如果使用不同的SysTick配置，则设置为1*/
#define __VTOR_PRESENT                 1        /*!< 如果CPU支持矢量表偏移寄存器，则设置为1*/
#define __MPU_PRESENT                  1        /*!< MPU存在*/
#define __FPU_PRESENT                  1        /*!< FPU存在*/
#define __FPU_DP                       0        /*!< 双精度FPU*/
#define __DSP_PRESENT                  1        /*!< 存在DSP扩展*/
#define __SAU_REGION_PRESENT           0        /*!< SAU存在*/


/** @} */ /* 组结束Configuration_of_CSIS*/

#include "core_cm33.h"                          /*!< ARM Cortex-M33处理器和核心外设*/
#include "system_DA1469x.h"                     /*!< DA1469x系统*/

#ifndef __IM                                    /*!< 旧CMSIS版本的回退*/
  #define __IM   __I
#endif
#ifndef __OM                                    /*!< 旧CMSIS版本的回退*/
  #define __OM   __O
#endif
#ifndef __IOM                                   /*!< 旧CMSIS版本的回退*/
  #define __IOM  __IO
#endif


/* =========================================================================================================================== */
/* ====================设备特定外围部分====================*/
/* =========================================================================================================================== */


/** @addtogroup 设备外围设备@{
  */



/* =========================================================================================================================== */
/* ================                                         AES_HASH                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief AES_HASH寄存器（AES_HASH）
  */

typedef struct {                                /*!< （@0x30040000）AES_HASH结构*/
  __IOM uint32_t  CRYPTO_CTRL_REG;              /*!< （@0x00000000）加密控制寄存器*/
  __IOM uint32_t  CRYPTO_START_REG;             /*!< （@0x00000004）加密开始计算*/
  __IOM uint32_t  CRYPTO_FETCH_ADDR_REG;        /*!< （@0x00000008）加密DMA提取寄存器*/
  __IOM uint32_t  CRYPTO_LEN_REG;               /*!< （@0x0000000C）输入块的加密长度（字节）*/
  __IOM uint32_t  CRYPTO_DEST_ADDR_REG;         /*!< （@0x00000010）加密DMA目标内存*/
  __IOM uint32_t  CRYPTO_STATUS_REG;            /*!< （@0x00000014）加密状态寄存器*/
  __IOM uint32_t  CRYPTO_CLRIRQ_REG;            /*!< （@0x00000018）加密清除中断请求*/
  __IOM uint32_t  CRYPTO_MREG0_REG;             /*!< （@0x0000001C）依赖于加密模式的寄存器0*/
  __IOM uint32_t  CRYPTO_MREG1_REG;             /*!< （@0x00000020）依赖于加密模式的寄存器1*/
  __IOM uint32_t  CRYPTO_MREG2_REG;             /*!< （@0x00000024）依赖于加密模式的寄存器2*/
  __IOM uint32_t  CRYPTO_MREG3_REG;             /*!< （@0x00000028）依赖于加密模式的寄存器3*/
  __IM  uint32_t  RESERVED[53];
  __IOM uint32_t  CRYPTO_KEYS_START;            /*!< （@0x00000100）加密AES密钥存储存储器的第一个位置*/
} AES_HASH_Type;                                /*!< 尺寸=260（0x104）*/



/* =========================================================================================================================== */
/* ================                                        ANAMISC_BIF                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief ANAMISC_BIF寄存器（ANAMISC_BINF）
  */

typedef struct {                                /*!< （@0x50030B00）ANAMISC_BIF结构*/
  __IM  uint32_t  RESERVED[4];
  __IOM uint32_t  CLK_REF_SEL_REG;              /*!< （@0x00000010）选择振荡器校准时钟*/
  __IOM uint32_t  CLK_REF_CNT_REG;              /*!< （@0x00000014）振荡器校准的计数值*/
  __IOM uint32_t  CLK_REF_VAL_REG;              /*!< （@0x00000018）DIVN参考周期，低16位*/
} ANAMISC_BIF_Type;                             /*!< 尺寸=28（0x1c）*/



/* =========================================================================================================================== */
/* ================                                            APU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief APU寄存器（APU）
  */

typedef struct {                                /*!< （@0x50030600）APU结构*/
  __IOM uint32_t  SRC1_CTRL_REG;                /*!< （@0x00000000）SRC1控制寄存器*/
  __IOM uint32_t  SRC1_IN_FS_REG;               /*!< （@0x00000004）SRC1样本输入速率*/
  __IOM uint32_t  SRC1_OUT_FS_REG;              /*!< （@0x00000008）SRC1样本输出速率*/
  __IOM uint32_t  SRC1_IN1_REG;                 /*!< （@0x0000000C）1中的SRC1数据*/
  __IOM uint32_t  SRC1_IN2_REG;                 /*!< （@0x00000010）SRC1数据在2*/
  __IOM uint32_t  SRC1_OUT1_REG;                /*!< （@0x00000014）SRC1数据输出1*/
  __IOM uint32_t  SRC1_OUT2_REG;                /*!< （@0x00000018）SRC1数据输出2*/
  __IOM uint32_t  APU_MUX_REG;                  /*!< （@0x0000001C）APU多路复用器寄存器*/
  __IOM uint32_t  COEF10_SET1_REG;              /*!< （@0x00000020）SRC系数1,0设置为1*/
  __IOM uint32_t  COEF32_SET1_REG;              /*!< （@0x00000024）SRC系数3,2设置1*/
  __IOM uint32_t  COEF54_SET1_REG;              /*!< （@0x00000028）SRC系数5,4设置1*/
  __IOM uint32_t  COEF76_SET1_REG;              /*!< （@0x0000002C）SRC系数7,6设置1*/
  __IOM uint32_t  COEF98_SET1_REG;              /*!< （@0x00000030）SRC系数9,8设置1*/
  __IOM uint32_t  COEF0A_SET1_REG;              /*!< （@0x00000034）SRC系数10设置1*/
  __IM  uint32_t  RESERVED[50];
  __IOM uint32_t  PCM1_CTRL_REG;                /*!< （@0x00000100）PCM1控制寄存器*/
  __IOM uint32_t  PCM1_IN1_REG;                 /*!< （@0x00000104）PCM1数据输入1*/
  __IOM uint32_t  PCM1_IN2_REG;                 /*!< （@0x00000108）PCM1数据输入2*/
  __IOM uint32_t  PCM1_OUT1_REG;                /*!< （@0x0000010C）PCM1数据输出1*/
  __IOM uint32_t  PCM1_OUT2_REG;                /*!< （@0x00000110）PCM1数据输出2*/
} APU_Type;                                     /*!< 尺寸=276（0x114）*/



/* =========================================================================================================================== */
/* ================                                           CACHE                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief CACHE寄存器（CACHE）
  */

typedef struct {                                /*!< （@0x100C0000）CACHE结构*/
  __IOM uint32_t  CACHE_CTRL1_REG;              /*!< （@0x00000000）缓存控制寄存器1*/
  __IOM uint32_t  CACHE_LNSIZECFG_REG;          /*!< （@0x00000004）缓存线大小配置寄存器*/
  __IOM uint32_t  CACHE_ASSOCCFG_REG;           /*!< （@0x00000008）缓存关联性配置寄存器*/
  __IM  uint32_t  RESERVED[5];
  __IOM uint32_t  CACHE_CTRL2_REG;              /*!< （@0x00000020）缓存控制寄存器2*/
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  CACHE_MRM_HITS_REG;           /*!< （@0x00000028）高速缓存MRM（未命中率监视器）HITS寄存器*/
  __IOM uint32_t  CACHE_MRM_MISSES_REG;         /*!< （@0x0000002C）高速缓存MRM（未命中率监视器）MISSES寄存器*/
  __IOM uint32_t  CACHE_MRM_CTRL_REG;           /*!< （@0x00000030）高速缓存MRM（未命中率监视器）控制寄存器*/
  __IOM uint32_t  CACHE_MRM_TINT_REG;           /*!< （@0x00000034）缓存MRM（未命中率监视器）时间间隔寄存器*/
  __IOM uint32_t  CACHE_MRM_MISSES_THRES_REG;   /*!< （@0x00000038）缓存MRM（未命中率监视器）阈值寄存器*/
  __IOM uint32_t  CACHE_MRM_HITS_THRES_REG;     /*!< （@0x0000003C）缓存MRM（未命中率监视器）命中阈值寄存器*/
  __IOM uint32_t  CACHE_FLASH_REG;              /*!< （@0x00000040）缓存闪存程序大小和基址寄存器*/
  __IM  uint32_t  RESERVED2[3];
  __IOM uint32_t  SWD_RESET_REG;                /*!< （@0x00000050）SWD HW复位控制寄存器*/
} CACHE_Type;                                   /*!< 大小=84（0x54）*/



/* =========================================================================================================================== */
/* ================                                          CHARGER                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CHARGER寄存器（CHARGER）
  */

typedef struct {                                /*!< （@0x50040400）充电器结构*/
  __IOM uint32_t  CHARGER_CTRL_REG;             /*!< （@0x00000000）充电器主控制寄存器*/
  __IOM uint32_t  CHARGER_TEST_CTRL_REG;        /*!< （@0x00000004）充电器测试控制寄存器*/
  __IOM uint32_t  CHARGER_STATUS_REG;           /*!< （@0x00000008）充电器主状态寄存器*/
  __IOM uint32_t  CHARGER_VOLTAGE_PARAM_REG;    /*!< （@0x0000000C）充电器电压设置寄存器*/
  __IOM uint32_t  CHARGER_CURRENT_PARAM_REG;    /*!< （@0x00000010）充电器电流设置寄存器*/
  __IOM uint32_t  CHARGER_TEMPSET_PARAM_REG;    /*!< （@0x00000014）充电器电池温度设置寄存器*/
  __IOM uint32_t  CHARGER_PRE_CHARGE_TIMER_REG; /*!< （@0x00000018）最大预充电时间限制寄存器*/
  __IOM uint32_t  CHARGER_CC_CHARGE_TIMER_REG;  /*!< （@0x0000001C）最大CC充电时间限制寄存器*/
  __IOM uint32_t  CHARGER_CV_CHARGE_TIMER_REG;  /*!< （@0x00000020）最大CV充电时间限制寄存器*/
  __IOM uint32_t  CHARGER_TOTAL_CHARGE_TIMER_REG;/*!< （@0x00000024）最大总充电时间限制寄存器*/
  __IOM uint32_t  CHARGER_JEITA_V_CHARGE_REG;   /*!< （@0x00000028）符合JEITA的充电电压设置寄存器*/
  __IOM uint32_t  CHARGER_JEITA_V_PRECHARGE_REG;/*!< （@0x0000002C）符合JEITA的预充电电压设置寄存器*/
  __IOM uint32_t  CHARGER_JEITA_V_REPLENISH_REG;/*!< （@0x00000030）符合JEITA的补货设置寄存器*/
  __IOM uint32_t  CHARGER_JEITA_V_OVP_REG;      /*!< （@0x00000034）JEITA兼容OVP设置寄存器*/
  __IOM uint32_t  CHARGER_JEITA_CURRENT_REG;    /*!< （@0x00000038）符合JEITA的当前设置寄存器*/
  __IOM uint32_t  CHARGER_VBAT_COMP_TIMER_REG;  /*!< （@0x0000003C）主Vbat比较器定时器寄存器*/
  __IOM uint32_t  CHARGER_VOVP_COMP_TIMER_REG;  /*!< （@0x00000040）Vbat OVP比较器定时器寄存器*/
  __IOM uint32_t  CHARGER_TDIE_COMP_TIMER_REG;  /*!< （@0x00000044）模具温度比较器定时器寄存器*/
  __IOM uint32_t  CHARGER_TBAT_MON_TIMER_REG;   /*!< （@0x00000048）电池温度监测间隔计时器*/
  __IOM uint32_t  CHARGER_TBAT_COMP_TIMER_REG;  /*!< （@0x0000004C）电池温度（主）比较器计时器*/
  __IOM uint32_t  CHARGER_THOT_COMP_TIMER_REG;  /*!< （@0x00000050）“热”区的电池温度比较器计时器*/
  __IOM uint32_t  CHARGER_PWR_UP_TIMER_REG;     /*!< （@0x00000054）充电器通电（稳定）计时器*/
  __IOM uint32_t  CHARGER_STATE_IRQ_MASK_REG;   /*!< （@0x00000058）充电器FSM IRQ的掩码寄存器*/
  __IOM uint32_t  CHARGER_ERROR_IRQ_MASK_REG;   /*!< （@0x0000005C）充电器错误IRQ的掩码寄存器*/
  __IOM uint32_t  CHARGER_STATE_IRQ_STATUS_REG; /*!< （@0x00000060）充电器FSM IRQ状态寄存器*/
  __IOM uint32_t  CHARGER_ERROR_IRQ_STATUS_REG; /*!< （@0x00000064）充电器错误IRQ状态寄存器*/
  __IOM uint32_t  CHARGER_STATE_IRQ_CLR_REG;    /*!< （@0x00000068）充电器FSM IRQ的中断清除寄存器*/
  __IOM uint32_t  CHARGER_ERROR_IRQ_CLR_REG;    /*!< （@0x0000006C）充电器错误IRQ的中断清除寄存器*/
} CHARGER_Type;                                 /*!< 大小=112（0x70）*/



/* =========================================================================================================================== */
/* ================                                       CHIP_VERSION                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief CHIP_VERSION寄存器（CHIP_VERION）
  */

typedef struct {                                /*!< （@0x50040200）CHIP_VERSION结构*/
  __IOM uint32_t  CHIP_ID1_REG;                 /*!< （@0x00000000）芯片识别寄存器1。*/
  __IOM uint32_t  CHIP_ID2_REG;                 /*!< （@0x00000004）芯片识别寄存器2。*/
  __IOM uint32_t  CHIP_ID3_REG;                 /*!< （@0x00000008）芯片识别寄存器3。*/
  __IOM uint32_t  CHIP_ID4_REG;                 /*!< （@0x0000000C）芯片识别寄存器4。*/
  __IOM uint32_t  CHIP_SWC_REG;                 /*!< （@0x00000010）软件兼容性寄存器。*/
  __IOM uint32_t  CHIP_REVISION_REG;            /*!< （@0x00000014）芯片修订寄存器。*/
  __IM  uint32_t  RESERVED[56];
  __IOM uint32_t  CHIP_TEST1_REG;               /*!< （@0x000000F8）芯片测试寄存器1。*/
  __IOM uint32_t  CHIP_TEST2_REG;               /*!< （@0x000000FC）芯片测试寄存器2。*/
} CHIP_VERSION_Type;                            /*!< 尺寸=256（0x100）*/



/* =========================================================================================================================== */
/* ================                                          CRG_COM                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CRG_COM寄存器（CRG_COM）
  */

typedef struct {                                /*!< （@0x50020900）CRG_COM结构*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  CLK_COM_REG;                  /*!< （@0x00000004）外围除法器寄存器*/
  __IOM uint32_t  SET_CLK_COM_REG;              /*!< （@0x00000008）外围除法器寄存器SET寄存器。读回0x0000*/
  __IOM uint32_t  RESET_CLK_COM_REG;            /*!< （@0x0000000C）外围除法器寄存器复位寄存器。读回0x0000*/
} CRG_COM_Type;                                 /*!< 尺寸=16（0x10）*/



/* =========================================================================================================================== */
/* ================                                          CRG_PER                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CRG_PER寄存器（CRG_PER）
  */

typedef struct {                                /*!< （@0x50030C00）CRG_PER结构*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  CLK_PER_REG;                  /*!< （@0x00000004）外围除法器寄存器*/
  __IOM uint32_t  SET_CLK_PER_REG;              /*!< （@0x00000008）外围除法器寄存器SET寄存器，读取0x0000*/
  __IOM uint32_t  RESET_CLK_PER_REG;            /*!< （@0x0000000C）外围除法器寄存器复位寄存器，读取0x0000*/
  __IM  uint32_t  RESERVED1[12];
  __IOM uint32_t  PCM_DIV_REG;                  /*!< （@0x00000040）PCM除法器并启用*/
  __IOM uint32_t  PCM_FDIV_REG;                 /*!< （@0x00000044）PCM小数分频寄存器*/
  __IOM uint32_t  PDM_DIV_REG;                  /*!< （@0x00000048）PDM除法器并启用*/
  __IOM uint32_t  SRC_DIV_REG;                  /*!< （@0x0000004C）SRC除法器并启用*/
} CRG_PER_Type;                                 /*!< 大小=80（0x50）*/



/* =========================================================================================================================== */
/* ================                                          CRG_SYS                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CRG_SYS寄存器（CRG_SYS）
  */

typedef struct {                                /*!< （@0x50040500）CRG_SYS结构*/
  __IOM uint32_t  CLK_SYS_REG;                  /*!< （@0x00000000）外围除法器寄存器*/
  __IOM uint32_t  BATCHECK_REG;                 /*!< （@0x00000004）BATCHECK_REG*/
} CRG_SYS_Type;                                 /*!< 大小=8（0x8）*/



/* =========================================================================================================================== */
/* ================                                          CRG_TOP                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CRG_TOP寄存器（CRG_TOP）
  */

typedef struct {                                /*!< （@0x50000000）CRG_TOP结构*/
  __IOM uint32_t  CLK_AMBA_REG;                 /*!< （@0x00000000）HCLK、PCLK、分频器和时钟门*/
  __IM  uint32_t  RESERVED[3];
  __IOM uint32_t  CLK_RADIO_REG;                /*!< （@0x00000010）无线电PLL控制寄存器*/
  __IOM uint32_t  CLK_CTRL_REG;                 /*!< （@0x00000014）时钟控制寄存器*/
  __IOM uint32_t  CLK_TMR_REG;                  /*!< （@0x00000018）计时器的时钟控制*/
  __IOM uint32_t  CLK_SWITCH2XTAL_REG;          /*!< （@0x0000001C）将时钟从RC32M切换到XTAL32M*/
  __IOM uint32_t  PMU_CTRL_REG;                 /*!< （@0x00000020）电源管理单元控制寄存器*/
  __IOM uint32_t  SYS_CTRL_REG;                 /*!< （@0x00000024）系统控制寄存器*/
  __IOM uint32_t  SYS_STAT_REG;                 /*!< （@0x00000028）系统状态寄存器*/
  __IM  uint32_t  RESERVED1[4];
  __IOM uint32_t  CLK_RC32K_REG;                /*!< （@0x0000003C）32 kHz RC振荡器寄存器*/
  __IOM uint32_t  CLK_XTAL32K_REG;              /*!< （@0x00000040）32 kHz XTAL振荡器寄存器*/
  __IOM uint32_t  CLK_RC32M_REG;                /*!< （@0x00000044）快速RC控制寄存器*/
  __IOM uint32_t  CLK_RCX_REG;                  /*!< （@0x00000048）RCX振荡器控制寄存器*/
  __IOM uint32_t  CLK_RTCDIV_REG;               /*!< （@0x0000004C）RTC 100Hz时钟分频器*/
  __IOM uint32_t  BANDGAP_REG;                  /*!< （@0x00000050）带隙微调*/
  __IOM uint32_t  VBUS_IRQ_MASK_REG;            /*!< （@0x00000054）IRQ屏蔽*/
  __IOM uint32_t  VBUS_IRQ_CLEAR_REG;           /*!< （@0x00000058）清除挂起的IRQ寄存器*/
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  BOD_CTRL_REG;                 /*!< （@0x00000060）褐光检测控制寄存器*/
  __IOM uint32_t  BOD_LVL_CTRL0_REG;            /*!< （@0x00000064）BOD_LVL_CTRL0_REG*/
  __IOM uint32_t  BOD_LVL_CTRL1_REG;            /*!< （@0x00000068）BOD_LVL_CTRL1_REG*/
  __IOM uint32_t  BOD_LVL_CTRL2_REG;            /*!< （@0x0000006C）BOD_LVL_CTRL2_REG*/
  __IOM uint32_t  P0_PAD_LATCH_REG;             /*!< （@0x00000070）控制GPIO端口的状态保持*/
  __IOM uint32_t  P0_SET_PAD_LATCH_REG;         /*!< （@0x00000074）控制GPIO端口的状态保持*/
  __IOM uint32_t  P0_RESET_PAD_LATCH_REG;       /*!< （@0x00000078）控制GPIO端口的状态保持*/
  __IOM uint32_t  P1_PAD_LATCH_REG;             /*!< （@0x0000007C）控制GPIO端口的状态保持*/
  __IOM uint32_t  P1_SET_PAD_LATCH_REG;         /*!< （@0x00000080）控制GPIO端口的状态保持*/
  __IOM uint32_t  P1_RESET_PAD_LATCH_REG;       /*!< （@0x00000084）控制GPIO端口的状态保持*/
  __IM  uint32_t  RESERVED3[2];
  __IOM uint32_t  BOD_STATUS_REG;               /*!< （@0x00000090）BOD_STATUS_REG*/
  __IOM uint32_t  POR_VBAT_CTRL_REG;            /*!< （@0x00000094）控制VBAT上的POR*/
  __IOM uint32_t  POR_PIN_REG;                  /*!< （@0x00000098）为POR生成选择GPIO引脚*/
  __IOM uint32_t  POR_TIMER_REG;                /*!< （@0x0000009C）POR发生的时间*/
  __IOM uint32_t  LDO_VDDD_HIGH_CTRL_REG;       /*!< （@0x000000A0）LDO控制寄存器*/
  __IOM uint32_t  BIAS_VREF_SEL_REG;            /*!< （@0x000000A4）BIAS_VREF_SEL_REG*/
  __IM  uint32_t  RESERVED4[5];
  __IOM uint32_t  RESET_STAT_REG;               /*!< （@0x000000BC）重置状态寄存器*/
  __IOM uint32_t  RAM_PWR_CTRL_REG;             /*!< （@0x000000C0）系统RAMS的控制电源状态*/
  __IM  uint32_t  RESERVED5[2];
  __IOM uint32_t  SECURE_BOOT_REG;              /*!< （@0x000000CC）控制安全启动*/
  __IM  uint32_t  RESERVED6;
  __IOM uint32_t  DISCHARGE_RAIL_REG;           /*!< （@0x000000D4）立即复位导轨。没有LDO/DCDC门控*/
  __IM  uint32_t  RESERVED7[5];
  __IOM uint32_t  ANA_STATUS_REG;               /*!< （@0x000000EC）模拟信号状态寄存器*/
  __IOM uint32_t  POWER_CTRL_REG;               /*!< （@0x000000F0）电源控制寄存器*/
  __IOM uint32_t  PMU_SLEEP_REG;                /*!< （@0x000000F4）配置休眠/唤醒策略*/
  __IOM uint32_t  PMU_TRIM_REG;                 /*!< （@0x000000F8）LDO微调寄存器*/
} CRG_TOP_Type;                                 /*!< 大小=252（0xfc）*/



/* =========================================================================================================================== */
/* ================                                         CRG_XTAL                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CRG_XTAL寄存器（CRG_XTL）
  */

typedef struct {                                /*!< （@0x50010000）CRG_XTAL结构*/
  __IOM uint32_t  CLK_FREQ_TRIM_REG;            /*!< （@0x00000000）Xtal频率微调寄存器。*/
  __IM  uint32_t  RESERVED[3];
  __IOM uint32_t  TRIM_CTRL_REG;                /*!< （@0x00000010）控制XTAL32M的微调*/
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  XTALRDY_CTRL_REG;             /*!< （@0x00000018）XTALRDY IRQ的控制寄存器*/
  __IOM uint32_t  XTALRDY_STAT_REG;             /*!< （@0x0000001C）LP时钟周期中XTAL_OK和XTALRDY_IRQ之间的差异*/
  __IM  uint32_t  RESERVED2[4];
  __IOM uint32_t  XTAL32M_CTRL0_REG;            /*!< （@0x00000030）XTAL32M的控制寄存器*/
  __IOM uint32_t  XTAL32M_CTRL1_REG;            /*!< （@0x00000034）XTAL32M的控制寄存器*/
  __IOM uint32_t  XTAL32M_CTRL2_REG;            /*!< （@0x00000038）XTAL32M的控制寄存器*/
  __IOM uint32_t  XTAL32M_CTRL3_REG;            /*!< （@0x0000003C）XTAL32M的控制寄存器*/
  __IOM uint32_t  XTAL32M_CTRL4_REG;            /*!< （@0x00000040）XTAL32M的控制寄存器*/
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  XTAL32M_STAT0_REG;            /*!< （@0x00000050）XTAL32M的状态寄存器*/
  __IOM uint32_t  XTAL32M_STAT1_REG;            /*!< （@0x00000054）XTAL32M的状态寄存器*/
  __IM  uint32_t  RESERVED4[2];
  __IOM uint32_t  PLL_SYS_CTRL1_REG;            /*!< （@0x00000060）系统PLL控制寄存器1。*/
  __IOM uint32_t  PLL_SYS_CTRL2_REG;            /*!< （@0x00000064）系统PLL控制寄存器2。*/
  __IOM uint32_t  PLL_SYS_CTRL3_REG;            /*!< （@0x00000068）系统PLL控制寄存器3。*/
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  PLL_SYS_STATUS_REG;           /*!< （@0x00000070）系统PLL状态寄存器。*/
} CRG_XTAL_Type;                                /*!< 大小=116（0x74）*/



/* =========================================================================================================================== */
/* ================                                           DCDC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief DCDC寄存器（DCDC）
  */

typedef struct {                                /*!< （@0x50000300）DCDC结构*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  DCDC_CTRL1_REG;               /*!< （@0x00000004）DCDC第一控制寄存器*/
  __IOM uint32_t  DCDC_CTRL2_REG;               /*!< （@0x00000008）DCDC第二控制寄存器*/
  __IOM uint32_t  DCDC_V14_REG;                 /*!< （@0x0000000C）DCDC V14控制寄存器*/
  __IOM uint32_t  DCDC_VDD_REG;                 /*!< （@0x00000010）DCDC VDD控制寄存器*/
  __IOM uint32_t  DCDC_V18_REG;                 /*!< （@0x00000014）DCDC V18控制寄存器*/
  __IOM uint32_t  DCDC_V18P_REG;                /*!< （@0x00000018）DCDC V18P控制寄存器*/
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  DCDC_STATUS1_REG;             /*!< （@0x00000020）DCDC第一状态寄存器*/
  __IM  uint32_t  RESERVED2[3];
  __IOM uint32_t  DCDC_IRQ_STATUS_REG;          /*!< （@0x00000030）DCDC中断状态寄存器*/
  __IOM uint32_t  DCDC_IRQ_CLEAR_REG;           /*!< （@0x00000034）DCDC中断清除寄存器*/
  __IOM uint32_t  DCDC_IRQ_MASK_REG;            /*!< （@0x00000038）DCDC中断掩码寄存器*/
} DCDC_Type;                                    /*!< 尺寸=60（0x3c）*/



/* =========================================================================================================================== */
/* ================                                            DMA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief DMA寄存器（DMA）
  */

typedef struct {                                /*!< （@0x50040800）DMA结构*/
  __IOM uint32_t  DMA0_A_START_REG;             /*!< （@0x00000000）DMA通道0的起始地址A*/
  __IOM uint32_t  DMA0_B_START_REG;             /*!< （@0x00000004）DMA通道0的起始地址B*/
  __IOM uint32_t  DMA0_INT_REG;                 /*!< （@0x00000008）DMA接收中断寄存器通道0*/
  __IOM uint32_t  DMA0_LEN_REG;                 /*!< （@0x0000000C）DMA接收长度寄存器通道0*/
  __IOM uint32_t  DMA0_CTRL_REG;                /*!< （@0x00000010）DMA通道0的控制寄存器*/
  __IOM uint32_t  DMA0_IDX_REG;                 /*!< （@0x00000014）DMA通道0的索引值*/
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  DMA1_A_START_REG;             /*!< （@0x00000020）DMA通道1的起始地址A*/
  __IOM uint32_t  DMA1_B_START_REG;             /*!< （@0x00000024）DMA通道1的起始地址B*/
  __IOM uint32_t  DMA1_INT_REG;                 /*!< （@0x00000028）DMA接收中断寄存器通道1*/
  __IOM uint32_t  DMA1_LEN_REG;                 /*!< （@0x0000002C）DMA接收长度寄存器通道1*/
  __IOM uint32_t  DMA1_CTRL_REG;                /*!< （@0x00000030）DMA通道1的控制寄存器*/
  __IOM uint32_t  DMA1_IDX_REG;                 /*!< （@0x00000034）DMA通道1的索引值*/
  __IM  uint32_t  RESERVED1[2];
  __IOM uint32_t  DMA2_A_START_REG;             /*!< （@0x00000040）DMA通道2的起始地址A*/
  __IOM uint32_t  DMA2_B_START_REG;             /*!< （@0x00000044）DMA通道2的起始地址B*/
  __IOM uint32_t  DMA2_INT_REG;                 /*!< （@0x00000048）DMA接收中断寄存器通道2*/
  __IOM uint32_t  DMA2_LEN_REG;                 /*!< （@0x0000004C）DMA接收长度寄存器通道2*/
  __IOM uint32_t  DMA2_CTRL_REG;                /*!< （@0x00000050）DMA通道2的控制寄存器*/
  __IOM uint32_t  DMA2_IDX_REG;                 /*!< （@0x00000054）DMA通道2的索引值*/
  __IM  uint32_t  RESERVED2[2];
  __IOM uint32_t  DMA3_A_START_REG;             /*!< （@0x00000060）DMA通道3的起始地址A*/
  __IOM uint32_t  DMA3_B_START_REG;             /*!< （@0x00000064）DMA通道3的起始地址B*/
  __IOM uint32_t  DMA3_INT_REG;                 /*!< （@0x00000068）DMA接收中断寄存器通道3*/
  __IOM uint32_t  DMA3_LEN_REG;                 /*!< （@0x0000006C）DMA接收长度寄存器通道3*/
  __IOM uint32_t  DMA3_CTRL_REG;                /*!< （@0x00000070）DMA通道3的控制寄存器*/
  __IOM uint32_t  DMA3_IDX_REG;                 /*!< （@0x00000074）DMA通道3的索引值*/
  __IM  uint32_t  RESERVED3[2];
  __IOM uint32_t  DMA4_A_START_REG;             /*!< （@0x00000080）DMA通道4的起始地址A*/
  __IOM uint32_t  DMA4_B_START_REG;             /*!< （@0x00000084）DMA通道4的起始地址B*/
  __IOM uint32_t  DMA4_INT_REG;                 /*!< （@0x00000088）DMA接收中断寄存器通道4*/
  __IOM uint32_t  DMA4_LEN_REG;                 /*!< （@0x0000008C）DMA接收长度寄存器通道4*/
  __IOM uint32_t  DMA4_CTRL_REG;                /*!< （@0x00000090）DMA通道4的控制寄存器*/
  __IOM uint32_t  DMA4_IDX_REG;                 /*!< （@0x00000094）DMA通道4的索引值*/
  __IM  uint32_t  RESERVED4[2];
  __IOM uint32_t  DMA5_A_START_REG;             /*!< （@0x000000A0）DMA通道5的起始地址A*/
  __IOM uint32_t  DMA5_B_START_REG;             /*!< （@0x000000A4）DMA通道5的起始地址B*/
  __IOM uint32_t  DMA5_INT_REG;                 /*!< （@0x000000A8）DMA接收中断寄存器通道5*/
  __IOM uint32_t  DMA5_LEN_REG;                 /*!< （@0x000000AC）DMA接收长度寄存器通道5*/
  __IOM uint32_t  DMA5_CTRL_REG;                /*!< （@0x000000B0）DMA通道5的控制寄存器*/
  __IOM uint32_t  DMA5_IDX_REG;                 /*!< （@0x000000B4）DMA通道5的索引值*/
  __IM  uint32_t  RESERVED5[2];
  __IOM uint32_t  DMA6_A_START_REG;             /*!< （@0x000000C0）DMA通道6的起始地址A*/
  __IOM uint32_t  DMA6_B_START_REG;             /*!< （@0x000000C4）DMA通道6的起始地址B*/
  __IOM uint32_t  DMA6_INT_REG;                 /*!< （@0x000000C8）DMA接收中断寄存器通道6*/
  __IOM uint32_t  DMA6_LEN_REG;                 /*!< （@0x000000CC）DMA接收长度寄存器通道6*/
  __IOM uint32_t  DMA6_CTRL_REG;                /*!< （@0x000000D0）DMA通道6的控制寄存器*/
  __IOM uint32_t  DMA6_IDX_REG;                 /*!< （@0x000000D4）DMA通道6的索引值*/
  __IM  uint32_t  RESERVED6[2];
  __IOM uint32_t  DMA7_A_START_REG;             /*!< （@0x000000E0）DMA通道7的起始地址A*/
  __IOM uint32_t  DMA7_B_START_REG;             /*!< （@0x000000E4）DMA通道7的起始地址B*/
  __IOM uint32_t  DMA7_INT_REG;                 /*!< （@0x000000E8）DMA接收中断寄存器通道7*/
  __IOM uint32_t  DMA7_LEN_REG;                 /*!< （@0x000000EC）DMA接收长度寄存器通道7*/
  __IOM uint32_t  DMA7_CTRL_REG;                /*!< （@0x000000F0）DMA通道7的控制寄存器*/
  __IOM uint32_t  DMA7_IDX_REG;                 /*!< （@0x000000F4）DMA通道7的索引值*/
  __IM  uint32_t  RESERVED7[2];
  __IOM uint32_t  DMA_REQ_MUX_REG;              /*!< （@0x00000100）DMA通道分配*/
  __IOM uint32_t  DMA_INT_STATUS_REG;           /*!< （@0x00000104）DMA中断状态寄存器*/
  __IOM uint32_t  DMA_CLEAR_INT_REG;            /*!< （@0x00000108）DMA清除中断寄存器*/
  __IOM uint32_t  DMA_INT_MASK_REG;             /*!< （@0x0000010C）DMA中断掩码寄存器*/
} DMA_Type;                                     /*!< 尺寸=272（0x110）*/



/* =========================================================================================================================== */
/* ================                                            DW                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief DW寄存器（DW）
  */

typedef struct {                                /*!< （@0x30020000）DW结构*/
  __IOM uint32_t  AHB_DMA_PL1_REG;              /*!< （@0x00000000）RFTP的AHB-DMA层优先级（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_PL2_REG;              /*!< （@0x00000004）LCD的AHB-DMA层优先级（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_PL3_REG;              /*!< （@0x00000008）GEN-DMA的AHB-DMA层优先级（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_PL4_REG;              /*!< （@0x0000000C）AHB-DMA层CRYPTO-DMA的优先级（仅AHB DMA层）*/
  __IM  uint32_t  RESERVED[14];
  __IOM uint32_t  AHB_DMA_DFLT_MASTER_REG;      /*!< （@0x00000048）默认主机ID号（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_WTEN_REG;             /*!< （@0x0000004C）加权令牌仲裁方案启用（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_TCL_REG;              /*!< （@0x00000050）主时钟刷新周期（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_CCLM1_REG;            /*!< （@0x00000054）USB主时钟令牌（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_CCLM2_REG;            /*!< （@0x00000058）GenDMA主时钟令牌（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_CCLM3_REG;            /*!< （@0x0000005C）CRYPTO主时钟令牌（仅AHB DMA层）*/
  __IOM uint32_t  AHB_DMA_CCLM4_REG;            /*!< （@0x00000060）CRYPTO主时钟令牌（仅AHB DMA层）*/
  __IM  uint32_t  RESERVED1[11];
  __IOM uint32_t  AHB_DMA_VERSION_REG;          /*!< （@0x00000090）版本ID（仅AHB DMA层）*/
} DW_Type;                                      /*!< 大小=148（0x94）*/



/* =========================================================================================================================== */
/* ================                                           GPADC                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief GPADC寄存器（GPADC）
  */

typedef struct {                                /*!< （@0x50030900）GPADC结构*/
  __IOM uint32_t  GP_ADC_CTRL_REG;              /*!< （@0x00000000）通用ADC控制寄存器*/
  __IOM uint32_t  GP_ADC_CTRL2_REG;             /*!< （@0x00000004）通用ADC第二控制寄存器*/
  __IOM uint32_t  GP_ADC_CTRL3_REG;             /*!< （@0x00000008）通用ADC第三控制寄存器*/
  __IOM uint32_t  GP_ADC_OFFP_REG;              /*!< （@0x0000000C）通用ADC正偏移寄存器*/
  __IOM uint32_t  GP_ADC_OFFN_REG;              /*!< （@0x00000010）通用ADC负偏移寄存器*/
  __IOM uint32_t  GP_ADC_CLEAR_INT_REG;         /*!< （@0x00000014）通用ADC清除中断寄存器*/
  __IOM uint32_t  GP_ADC_RESULT_REG;            /*!< （@0x00000018）通用ADC结果寄存器*/
} GPADC_Type;                                   /*!< 尺寸=28（0x1c）*/



/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief GPIO寄存器（GPIO）
  */

typedef struct {                                /*!< （@0x50020A00）GPIO结构*/
  __IOM uint32_t  P0_DATA_REG;                  /*!< （@0x00000000）P0数据输入/输出寄存器*/
  __IOM uint32_t  P1_DATA_REG;                  /*!< （@0x00000004）P1数据输入/输出寄存器*/
  __IOM uint32_t  P0_SET_DATA_REG;              /*!< （@0x00000008）P0设置端口引脚寄存器*/
  __IOM uint32_t  P1_SET_DATA_REG;              /*!< （@0x0000000C）P1设置端口引脚寄存器*/
  __IOM uint32_t  P0_RESET_DATA_REG;            /*!< （@0x00000010）P0重置端口引脚寄存器*/
  __IOM uint32_t  P1_RESET_DATA_REG;            /*!< （@0x00000014）P1重置端口引脚寄存器*/
  __IOM uint32_t  P0_00_MODE_REG;               /*!< （@0x00000018）P0_00模式寄存器*/
  __IOM uint32_t  P0_01_MODE_REG;               /*!< （@0x0000001C）P0_01模式寄存器*/
  __IOM uint32_t  P0_02_MODE_REG;               /*!< （@0x00000020）P0_02模式寄存器*/
  __IOM uint32_t  P0_03_MODE_REG;               /*!< （@0x00000024）P0_03模式寄存器*/
  __IOM uint32_t  P0_04_MODE_REG;               /*!< （@0x00000028）P0_04模式寄存器*/
  __IOM uint32_t  P0_05_MODE_REG;               /*!< （@0x0000002C）P0_05模式寄存器*/
  __IOM uint32_t  P0_06_MODE_REG;               /*!< （@0x00000030）P0_06模式寄存器*/
  __IOM uint32_t  P0_07_MODE_REG;               /*!< （@0x00000034）P0_07模式寄存器*/
  __IOM uint32_t  P0_08_MODE_REG;               /*!< （@0x00000038）P0_08模式寄存器*/
  __IOM uint32_t  P0_09_MODE_REG;               /*!< （@0x0000003C）P0_09模式寄存器*/
  __IOM uint32_t  P0_10_MODE_REG;               /*!< （@0x00000040）P0_10模式寄存器*/
  __IOM uint32_t  P0_11_MODE_REG;               /*!< （@0x00000044）P0_11模式寄存器*/
  __IOM uint32_t  P0_12_MODE_REG;               /*!< （@0x00000048）P0_12模式寄存器*/
  __IOM uint32_t  P0_13_MODE_REG;               /*!< （@0x0000004C）P0_13模式寄存器*/
  __IOM uint32_t  P0_14_MODE_REG;               /*!< （@0x00000050）P0_14模式寄存器*/
  __IOM uint32_t  P0_15_MODE_REG;               /*!< （@0x00000054）P0_15模式寄存器*/
  __IOM uint32_t  P0_16_MODE_REG;               /*!< （@0x00000058）P0_16模式寄存器*/
  __IOM uint32_t  P0_17_MODE_REG;               /*!< （@0x0000005C）P0_17模式寄存器*/
  __IOM uint32_t  P0_18_MODE_REG;               /*!< （@0x00000060）P0_18模式寄存器*/
  __IOM uint32_t  P0_19_MODE_REG;               /*!< （@0x00000064）P0_19模式寄存器*/
  __IOM uint32_t  P0_20_MODE_REG;               /*!< （@0x00000068）P0_20模式寄存器*/
  __IOM uint32_t  P0_21_MODE_REG;               /*!< （@0x0000006C）P0_21模式寄存器*/
  __IOM uint32_t  P0_22_MODE_REG;               /*!< （@0x00000070）P0_22模式寄存器*/
  __IOM uint32_t  P0_23_MODE_REG;               /*!< （@0x00000074）P0_23模式寄存器*/
  __IOM uint32_t  P0_24_MODE_REG;               /*!< （@0x00000078）P0_24模式寄存器*/
  __IOM uint32_t  P0_25_MODE_REG;               /*!< （@0x0000007C）P0_25模式寄存器*/
  __IOM uint32_t  P0_26_MODE_REG;               /*!< （@0x00000080）P0_26模式寄存器*/
  __IOM uint32_t  P0_27_MODE_REG;               /*!< （@0x00000084）P0_27模式寄存器*/
  __IOM uint32_t  P0_28_MODE_REG;               /*!< （@0x00000088）P0_28模式寄存器*/
  __IOM uint32_t  P0_29_MODE_REG;               /*!< （@0x0000008C）P0_29模式寄存器*/
  __IOM uint32_t  P0_30_MODE_REG;               /*!< （@0x00000090）P0_30模式寄存器*/
  __IOM uint32_t  P0_31_MODE_REG;               /*!< （@0x00000094）P0_31模式寄存器*/
  __IOM uint32_t  P1_00_MODE_REG;               /*!< （@0x00000098）P1_00模式寄存器*/
  __IOM uint32_t  P1_01_MODE_REG;               /*!< （@0x0000009C）P1_01模式寄存器*/
  __IOM uint32_t  P1_02_MODE_REG;               /*!< （@0x000000A0）P1_02模式寄存器*/
  __IOM uint32_t  P1_03_MODE_REG;               /*!< （@0x000000A4）P1_03模式寄存器*/
  __IOM uint32_t  P1_04_MODE_REG;               /*!< （@0x000000A8）P1_04模式寄存器*/
  __IOM uint32_t  P1_05_MODE_REG;               /*!< （@0x000000AC）P1_05模式寄存器*/
  __IOM uint32_t  P1_06_MODE_REG;               /*!< （@0x000000B0）P1_06模式寄存器*/
  __IOM uint32_t  P1_07_MODE_REG;               /*!< （@0x000000B4）P1_07模式寄存器*/
  __IOM uint32_t  P1_08_MODE_REG;               /*!< （@0x000000B8）P1_08模式寄存器*/
  __IOM uint32_t  P1_09_MODE_REG;               /*!< （@0x000000BC）P1_09模式寄存器*/
  __IOM uint32_t  P1_10_MODE_REG;               /*!< （@0x000000C0）P1_10模式寄存器*/
  __IOM uint32_t  P1_11_MODE_REG;               /*!< （@0x000000C4）P1_11模式寄存器*/
  __IOM uint32_t  P1_12_MODE_REG;               /*!< （@0x000000C8）P1_12模式寄存器*/
  __IOM uint32_t  P1_13_MODE_REG;               /*!< （@0x000000CC）P1_13模式寄存器*/
  __IOM uint32_t  P1_14_MODE_REG;               /*!< （@0x000000D0）P1_14模式寄存器*/
  __IOM uint32_t  P1_15_MODE_REG;               /*!< （@0x000000D4）P1_15模式寄存器*/
  __IOM uint32_t  P1_16_MODE_REG;               /*!< （@0x000000D8）P1_16模式寄存器*/
  __IOM uint32_t  P1_17_MODE_REG;               /*!< （@0x000000DC）P1_17模式寄存器*/
  __IOM uint32_t  P1_18_MODE_REG;               /*!< （@0x000000E0）P1_18模式寄存器*/
  __IOM uint32_t  P1_19_MODE_REG;               /*!< （@0x000000E4）P1_19模式寄存器*/
  __IOM uint32_t  P1_20_MODE_REG;               /*!< （@0x000000E8）P1_20模式寄存器*/
  __IOM uint32_t  P1_21_MODE_REG;               /*!< （@0x000000EC）P1_21模式寄存器*/
  __IOM uint32_t  P1_22_MODE_REG;               /*!< （@0x000000F0）P1_22模式寄存器*/
  __IOM uint32_t  P0_PADPWR_CTRL_REG;           /*!< （@0x000000F4）P0输出功率控制寄存器*/
  __IOM uint32_t  P1_PADPWR_CTRL_REG;           /*!< （@0x000000F8）P1输出功率控制寄存器*/
  __IOM uint32_t  GPIO_CLK_SEL_REG;             /*!< （@0x000000FC）选择要映射到端口P0/P1的时钟*/
  __IOM uint32_t  PAD_WEAK_CTRL_REG;            /*!< （@0x00000100）弱焊盘控制寄存器*/
} GPIO_Type;                                    /*!< 尺寸=260（0x104）*/



/* =========================================================================================================================== */
/* ================                                           GPREG                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief GPREG寄存器（GPREG）
  */

typedef struct {                                /*!< （@0x50040300）GPREG结构*/
  __IOM uint32_t  SET_FREEZE_REG;               /*!< （@0x00000000）控制各种计时器/计数器（包括DMA和USB）的冻结。*/
  __IOM uint32_t  RESET_FREEZE_REG;             /*!< （@0x00000004）控制各种计时器/计数器（包括DMA和USB）的解冻。*/
  __IOM uint32_t  DEBUG_REG;                    /*!< （@0x00000008）各种调试信息寄存器。*/
  __IOM uint32_t  GP_STATUS_REG;                /*!< （@0x0000000C）通用系统状态寄存器。*/
  __IOM uint32_t  GP_CONTROL_REG;               /*!< （@0x00000010）通用系统控制寄存器。*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  USBPAD_REG;                   /*!< （@0x00000018）USB焊盘控制寄存器*/
} GPREG_Type;                                   /*!< 尺寸=28（0x1c）*/



/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief I2C寄存器（I2C）
  */

typedef struct {                                /*!< （@0x50020600）I2C结构*/
  __IOM uint32_t  I2C_CON_REG;                  /*!< （@0x00000000）I2C控制寄存器*/
  __IOM uint32_t  I2C_TAR_REG;                  /*!< （@0x00000004）I2C目标地址寄存器*/
  __IOM uint32_t  I2C_SAR_REG;                  /*!< （@0x00000008）I2C从地址寄存器*/
  __IOM uint32_t  I2C_HS_MADDR_REG;             /*!< （@0x0000000C）I2C高速主模式代码地址寄存器*/
  __IOM uint32_t  I2C_DATA_CMD_REG;             /*!< （@0x00000010）I2C Rx/Tx数据缓冲区和命令寄存器*/
  __IOM uint32_t  I2C_SS_SCL_HCNT_REG;          /*!< （@0x00000014）标准速度I2C时钟SCL高计数寄存器*/
  __IOM uint32_t  I2C_SS_SCL_LCNT_REG;          /*!< （@0x00000018）标准速度I2C时钟SCL低计数寄存器*/
  __IOM uint32_t  I2C_FS_SCL_HCNT_REG;          /*!< （@0x0000001C）快速I2C时钟SCL高计数寄存器*/
  __IOM uint32_t  I2C_FS_SCL_LCNT_REG;          /*!< （@0x00000020）快速I2C时钟SCL低计数寄存器*/
  __IOM uint32_t  I2C_HS_SCL_HCNT_REG;          /*!< （@0x00000024）高速I2C时钟SCL高计数寄存器*/
  __IOM uint32_t  I2C_HS_SCL_LCNT_REG;          /*!< （@0x00000028）高速I2C时钟SCL低计数寄存器*/
  __IOM uint32_t  I2C_INTR_STAT_REG;            /*!< （@0x0000002C）I2C中断状态寄存器*/
  __IOM uint32_t  I2C_INTR_MASK_REG;            /*!< （@0x00000030）I2C中断掩码寄存器*/
  __IOM uint32_t  I2C_RAW_INTR_STAT_REG;        /*!< （@0x00000034）I2C原始中断状态寄存器*/
  __IOM uint32_t  I2C_RX_TL_REG;                /*!< （@0x00000038）I2C接收FIFO阈值寄存器*/
  __IOM uint32_t  I2C_TX_TL_REG;                /*!< （@0x0000003C）I2C传输FIFO阈值寄存器*/
  __IOM uint32_t  I2C_CLR_INTR_REG;             /*!< （@0x00000040）清除组合和单独中断寄存器*/
  __IOM uint32_t  I2C_CLR_RX_UNDER_REG;         /*!< （@0x00000044）清除RX_UNDER中断寄存器*/
  __IOM uint32_t  I2C_CLR_RX_OVER_REG;          /*!< （@0x00000048）清除RX_OVER中断寄存器*/
  __IOM uint32_t  I2C_CLR_TX_OVER_REG;          /*!< （@0x0000004C）清除TX_OVER中断寄存器*/
  __IOM uint32_t  I2C_CLR_RD_REQ_REG;           /*!< （@0x00000050）清除RD_REQ中断寄存器*/
  __IOM uint32_t  I2C_CLR_TX_ABRT_REG;          /*!< （@0x00000054）清除TX_ABRT中断寄存器*/
  __IOM uint32_t  I2C_CLR_RX_DONE_REG;          /*!< （@0x00000058）清除RX_DONE中断寄存器*/
  __IOM uint32_t  I2C_CLR_ACTIVITY_REG;         /*!< （@0x0000005C）清除活动中断寄存器*/
  __IOM uint32_t  I2C_CLR_STOP_DET_REG;         /*!< （@0x00000060）清除STOP_DET中断寄存器*/
  __IOM uint32_t  I2C_CLR_START_DET_REG;        /*!< （@0x00000064）清除START_DET中断寄存器*/
  __IOM uint32_t  I2C_CLR_GEN_CALL_REG;         /*!< （@0x00000068）清除GEN_CALL中断寄存器*/
  __IOM uint32_t  I2C_ENABLE_REG;               /*!< （@0x0000006C）I2C启用寄存器*/
  __IOM uint32_t  I2C_STATUS_REG;               /*!< （@0x00000070）I2C状态寄存器*/
  __IOM uint32_t  I2C_TXFLR_REG;                /*!< （@0x00000074）I2C传输FIFO电平寄存器*/
  __IOM uint32_t  I2C_RXFLR_REG;                /*!< （@0x00000078）I2C接收FIFO电平寄存器*/
  __IOM uint32_t  I2C_SDA_HOLD_REG;             /*!< （@0x0000007C）I2C SDA保持时间长度寄存器*/
  __IOM uint32_t  I2C_TX_ABRT_SOURCE_REG;       /*!< （@0x00000080）I2C传输中止源寄存器*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  I2C_DMA_CR_REG;               /*!< （@0x00000088）DMA控制寄存器*/
  __IOM uint32_t  I2C_DMA_TDLR_REG;             /*!< （@0x0000008C）DMA传输数据电平寄存器*/
  __IOM uint32_t  I2C_DMA_RDLR_REG;             /*!< （@0x00000090）I2C接收数据电平寄存器*/
  __IOM uint32_t  I2C_SDA_SETUP_REG;            /*!< （@0x00000094）I2C SDA设置寄存器*/
  __IOM uint32_t  I2C_ACK_GENERAL_CALL_REG;     /*!< （@0x00000098）I2C ACK通用调用寄存器*/
  __IOM uint32_t  I2C_ENABLE_STATUS_REG;        /*!< （@0x0000009C）I2C启用状态寄存器*/
  __IOM uint32_t  I2C_IC_FS_SPKLEN_REG;         /*!< （@0x000000A0）I2C SS和FS尖峰抑制限制大小*/
  __IOM uint32_t  I2C_IC_HS_SPKLEN_REG;         /*!< （@0x000000A4）I2C HS尖峰抑制限制大小*/
} I2C_Type;                                     /*!< 大小=168（0xa8）*/



/* =========================================================================================================================== */
/* ================                                           I2C2                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief I2C2寄存器（I2C2）
  */

typedef struct {                                /*!< （@0x50020700）I2C2结构*/
  __IOM uint32_t  I2C2_CON_REG;                 /*!< （@0x00000000）I2C控制寄存器*/
  __IOM uint32_t  I2C2_TAR_REG;                 /*!< （@0x00000004）I2C目标地址寄存器*/
  __IOM uint32_t  I2C2_SAR_REG;                 /*!< （@0x00000008）I2C从地址寄存器*/
  __IOM uint32_t  I2C2_HS_MADDR_REG;            /*!< （@0x0000000C）I2C高速主模式代码地址寄存器*/
  __IOM uint32_t  I2C2_DATA_CMD_REG;            /*!< （@0x00000010）I2C Rx/Tx数据缓冲区和命令寄存器*/
  __IOM uint32_t  I2C2_SS_SCL_HCNT_REG;         /*!< （@0x00000014）标准速度I2C时钟SCL高计数寄存器*/
  __IOM uint32_t  I2C2_SS_SCL_LCNT_REG;         /*!< （@0x00000018）标准速度I2C时钟SCL低计数寄存器*/
  __IOM uint32_t  I2C2_FS_SCL_HCNT_REG;         /*!< （@0x0000001C）快速I2C时钟SCL高计数寄存器*/
  __IOM uint32_t  I2C2_FS_SCL_LCNT_REG;         /*!< （@0x00000020）快速I2C时钟SCL低计数寄存器*/
  __IOM uint32_t  I2C2_HS_SCL_HCNT_REG;         /*!< （@0x00000024）高速I2C时钟SCL高计数寄存器*/
  __IOM uint32_t  I2C2_HS_SCL_LCNT_REG;         /*!< （@0x00000028）高速I2C时钟SCL低计数寄存器*/
  __IOM uint32_t  I2C2_INTR_STAT_REG;           /*!< （@0x0000002C）I2C中断状态寄存器*/
  __IOM uint32_t  I2C2_INTR_MASK_REG;           /*!< （@0x00000030）I2C中断掩码寄存器*/
  __IOM uint32_t  I2C2_RAW_INTR_STAT_REG;       /*!< （@0x00000034）I2C原始中断状态寄存器*/
  __IOM uint32_t  I2C2_RX_TL_REG;               /*!< （@0x00000038）I2C接收FIFO阈值寄存器*/
  __IOM uint32_t  I2C2_TX_TL_REG;               /*!< （@0x0000003C）I2C传输FIFO阈值寄存器*/
  __IOM uint32_t  I2C2_CLR_INTR_REG;            /*!< （@0x00000040）清除组合和单独中断寄存器*/
  __IOM uint32_t  I2C2_CLR_RX_UNDER_REG;        /*!< （@0x00000044）清除RX_UNDER中断寄存器*/
  __IOM uint32_t  I2C2_CLR_RX_OVER_REG;         /*!< （@0x00000048）清除RX_OVER中断寄存器*/
  __IOM uint32_t  I2C2_CLR_TX_OVER_REG;         /*!< （@0x0000004C）清除TX_OVER中断寄存器*/
  __IOM uint32_t  I2C2_CLR_RD_REQ_REG;          /*!< （@0x00000050）清除RD_REQ中断寄存器*/
  __IOM uint32_t  I2C2_CLR_TX_ABRT_REG;         /*!< （@0x00000054）清除TX_ABRT中断寄存器*/
  __IOM uint32_t  I2C2_CLR_RX_DONE_REG;         /*!< （@0x00000058）清除RX_DONE中断寄存器*/
  __IOM uint32_t  I2C2_CLR_ACTIVITY_REG;        /*!< （@0x0000005C）清除活动中断寄存器*/
  __IOM uint32_t  I2C2_CLR_STOP_DET_REG;        /*!< （@0x00000060）清除STOP_DET中断寄存器*/
  __IOM uint32_t  I2C2_CLR_START_DET_REG;       /*!< （@0x00000064）清除START_DET中断寄存器*/
  __IOM uint32_t  I2C2_CLR_GEN_CALL_REG;        /*!< （@0x00000068）清除GEN_CALL中断寄存器*/
  __IOM uint32_t  I2C2_ENABLE_REG;              /*!< （@0x0000006C）I2C启用寄存器*/
  __IOM uint32_t  I2C2_STATUS_REG;              /*!< （@0x00000070）I2C状态寄存器*/
  __IOM uint32_t  I2C2_TXFLR_REG;               /*!< （@0x00000074）I2C传输FIFO电平寄存器*/
  __IOM uint32_t  I2C2_RXFLR_REG;               /*!< （@0x00000078）I2C接收FIFO电平寄存器*/
  __IOM uint32_t  I2C2_SDA_HOLD_REG;            /*!< （@0x0000007C）I2C SDA保持时间长度寄存器*/
  __IOM uint32_t  I2C2_TX_ABRT_SOURCE_REG;      /*!< （@0x00000080）I2C传输中止源寄存器*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  I2C2_DMA_CR_REG;              /*!< （@0x00000088）DMA控制寄存器*/
  __IOM uint32_t  I2C2_DMA_TDLR_REG;            /*!< （@0x0000008C）DMA传输数据电平寄存器*/
  __IOM uint32_t  I2C2_DMA_RDLR_REG;            /*!< （@0x00000090）I2C接收数据电平寄存器*/
  __IOM uint32_t  I2C2_SDA_SETUP_REG;           /*!< （@0x00000094）I2C SDA设置寄存器*/
  __IOM uint32_t  I2C2_ACK_GENERAL_CALL_REG;    /*!< （@0x00000098）I2C ACK通用调用寄存器*/
  __IOM uint32_t  I2C2_ENABLE_STATUS_REG;       /*!< （@0x0000009C）I2C启用状态寄存器*/
  __IOM uint32_t  I2C2_IC_FS_SPKLEN_REG;        /*!< （@0x000000A0）I2C SS和FS尖峰抑制限制大小*/
  __IOM uint32_t  I2C2_IC_HS_SPKLEN_REG;        /*!< （@0x000000A4）I2C HS尖峰抑制限制大小*/
} I2C2_Type;                                    /*!< 大小=168（0xa8）*/



/* =========================================================================================================================== */
/* ================                                           LCDC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief LCDC寄存器（LCDC）
  */

typedef struct {                                /*!< （@0x30030000）LCDC结构*/
  __IOM uint32_t  LCDC_MODE_REG;                /*!< （@0x00000000）显示模式*/
  __IOM uint32_t  LCDC_CLKCTRL_REG;             /*!< （@0x00000004）时钟分频器*/
  __IOM uint32_t  LCDC_BGCOLOR_REG;             /*!< （@0x00000008）背景色*/
  __IOM uint32_t  LCDC_RESXY_REG;               /*!< （@0x0000000C）分辨率X，Y*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  LCDC_FRONTPORCHXY_REG;        /*!< （@0x00000014）前廊X和Y*/
  __IOM uint32_t  LCDC_BLANKINGXY_REG;          /*!< （@0x00000018）清空X和Y*/
  __IOM uint32_t  LCDC_BACKPORCHXY_REG;         /*!< （@0x0000001C）后廊X和Y*/
  __IM  uint32_t  RESERVED1[2];
  __IOM uint32_t  LCDC_DBIB_CFG_REG;            /*!< （@0x00000028）MIPI配置寄存器*/
  __IOM uint32_t  LCDC_GPIO_REG;                /*!< （@0x0000002C）通用IO（2位）*/
  __IOM uint32_t  LCDC_LAYER0_MODE_REG;         /*!< （@0x00000030）第0层模式*/
  __IOM uint32_t  LCDC_LAYER0_STARTXY_REG;      /*!< （@0x00000034）层0开始XY*/
  __IOM uint32_t  LCDC_LAYER0_SIZEXY_REG;       /*!< （@0x00000038）层0大小XY*/
  __IOM uint32_t  LCDC_LAYER0_BASEADDR_REG;     /*!< （@0x0000003C）第0层基本地址*/
  __IOM uint32_t  LCDC_LAYER0_STRIDE_REG;       /*!< （@0x00000040）第0层跨步*/
  __IOM uint32_t  LCDC_LAYER0_RESXY_REG;        /*!< （@0x00000044）层0分辨率XY*/
  __IM  uint32_t  RESERVED2[18];
  __IOM uint32_t  LCDC_JDI_RESXY_REG;           /*!< （@0x00000090）JDI并行I/F的分辨率XY*/
  __IOM uint32_t  LCDC_JDI_FBX_BLANKING_REG;    /*!< （@0x00000094）水平前/后消隐（hck半周期）*/
  __IOM uint32_t  LCDC_JDI_FBY_BLANKING_REG;    /*!< （@0x00000098）垂直前/后消隐（vck半周期）*/
  __IOM uint32_t  LCDC_JDI_HCK_WIDTH_REG;       /*!< （@0x0000009C）HCK高/低宽度*/
  __IOM uint32_t  LCDC_JDI_XRST_WIDTH_REG;      /*!< （@0x000000A0）XRST宽度*/
  __IOM uint32_t  LCDC_JDI_VST_DELAY_REG;       /*!< （@0x000000A4）XRST到VST延迟*/
  __IOM uint32_t  LCDC_JDI_VST_WIDTH_REG;       /*!< （@0x000000A8）VST宽度*/
  __IOM uint32_t  LCDC_JDI_VCK_DELAY_REG;       /*!< （@0x000000AC）XRST到VCK延迟*/
  __IOM uint32_t  LCDC_JDI_HST_DELAY_REG;       /*!< （@0x000000B0）VCK到HST延迟*/
  __IOM uint32_t  LCDC_JDI_HST_WIDTH_REG;       /*!< （@0x000000B4）HST宽度*/
  __IOM uint32_t  LCDC_JDI_ENB_START_HLINE_REG; /*!< （@0x000000B8）ENB起始水平线*/
  __IOM uint32_t  LCDC_JDI_ENB_END_HLINE_REG;   /*!< （@0x000000BC）ENB端水平线*/
  __IOM uint32_t  LCDC_JDI_ENB_START_CLK_REG;   /*!< （@0x000000C0）ENB启动延迟*/
  __IOM uint32_t  LCDC_JDI_ENB_WIDTH_CLK_REG;   /*!< （@0x000000C4）ENB宽度*/
  __IM  uint32_t  RESERVED3[8];
  __IOM uint32_t  LCDC_DBIB_CMD_REG;            /*!< （@0x000000E8）MIPI DBIB命令寄存器*/
  __IM  uint32_t  RESERVED4[2];
  __IOM uint32_t  LCDC_IDREG_REG;               /*!< （@0x000000F4）标识寄存器*/
  __IOM uint32_t  LCDC_INTERRUPT_REG;           /*!< （@0x000000F8）中断寄存器*/
  __IOM uint32_t  LCDC_STATUS_REG;              /*!< （@0x000000FC）状态寄存器*/
  __IM  uint32_t  RESERVED5[33];
  __IOM uint32_t  LCDC_CRC_REG;                 /*!< （@0x00000184）CRC检查*/
  __IOM uint32_t  LCDC_LAYER0_OFFSETX_REG;      /*!< （@0x00000188）Layer0 OffsetX和DMA预取*/
} LCDC_Type;                                    /*!< 尺寸=396（0x18c）*/



/* =========================================================================================================================== */
/* ================                                            LRA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief LRA登记册（LRA）
  */

typedef struct {                                /*!< （@0x50030A00）LRA结构*/
  __IOM uint32_t  LRA_CTRL1_REG;                /*!< （@0x00000000）通用LRA控制寄存器*/
  __IOM uint32_t  LRA_CTRL2_REG;                /*!< （@0x00000004）通用LRA控制寄存器*/
  __IOM uint32_t  LRA_CTRL3_REG;                /*!< （@0x00000008）通用LRA控制寄存器*/
  __IOM uint32_t  LRA_FLT_SMP1_REG;             /*!< （@0x0000000C）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP2_REG;             /*!< （@0x00000010）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP3_REG;             /*!< （@0x00000014）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP4_REG;             /*!< （@0x00000018）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP5_REG;             /*!< （@0x0000001C）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP6_REG;             /*!< （@0x00000020）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP7_REG;             /*!< （@0x00000024）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_SMP8_REG;             /*!< （@0x00000028）LRA样本寄存器*/
  __IOM uint32_t  LRA_FLT_COEF1_REG;            /*!< （@0x0000002C）LRA滤波器系数寄存器*/
  __IOM uint32_t  LRA_FLT_COEF2_REG;            /*!< （@0x00000030）LRA滤波器系数寄存器*/
  __IOM uint32_t  LRA_FLT_COEF3_REG;            /*!< （@0x00000034）LRA滤波器系数寄存器*/
  __IOM uint32_t  LRA_BRD_LS_REG;               /*!< （@0x00000038）LRA桥寄存器*/
  __IOM uint32_t  LRA_BRD_HS_REG;               /*!< （@0x0000003C）LRA桥寄存器*/
  __IOM uint32_t  LRA_BRD_STAT_REG;             /*!< （@0x00000040）LRA桥Staus寄存器*/
  __IOM uint32_t  LRA_ADC_CTRL1_REG;            /*!< （@0x00000044）通用ADC控制寄存器*/
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  LRA_ADC_RESULT_REG;           /*!< （@0x00000050）通用ADC结果寄存器*/
  __IOM uint32_t  LRA_LDO_REG;                  /*!< （@0x00000054）LRA LDO注册*/
  __IOM uint32_t  LRA_DFT_REG;                  /*!< （@0x00000058）LRA测试寄存器*/
} LRA_Type;                                     /*!< 大小=92（0x5c）*/



/* =========================================================================================================================== */
/* ================                                          MEMCTRL                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief MEMCTRL寄存器（MEMCTRL）
  */

typedef struct {                                /*!< （@0x50050000）MEMCTRL结构*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  MEM_PRIO_REG;                 /*!< （@0x00000004）优先级控制寄存器*/
  __IOM uint32_t  MEM_STALL_REG;                /*!< （@0x00000008）最大暂停周期控制寄存器*/
  __IOM uint32_t  MEM_STATUS_REG;               /*!< （@0x0000000C）内存仲裁器状态寄存器*/
  __IOM uint32_t  MEM_STATUS2_REG;              /*!< （@0x00000010）RAM单元状态寄存器*/
  __IM  uint32_t  RESERVED1[3];
  __IOM uint32_t  CMI_CODE_BASE_REG;            /*!< （@0x00000020）CMAC代码基址寄存器*/
  __IOM uint32_t  CMI_DATA_BASE_REG;            /*!< （@0x00000024）CMAC数据基地址寄存器*/
  __IOM uint32_t  CMI_SHARED_BASE_REG;          /*!< （@0x00000028）CMAC共享数据基地址寄存器*/
  __IOM uint32_t  CMI_END_REG;                  /*!< （@0x0000002C）CMAC结束地址寄存器*/
  __IOM uint32_t  SNC_BASE_REG;                 /*!< （@0x00000030）传感器节点控制器基址寄存器*/
  __IM  uint32_t  RESERVED2[16];
  __IOM uint32_t  BUSY_SET_REG;                 /*!< （@0x00000074）BSR设置寄存器*/
  __IOM uint32_t  BUSY_RESET_REG;               /*!< （@0x00000078）BSR复位寄存器*/
  __IOM uint32_t  BUSY_STAT_REG;                /*!< （@0x0000007C）BSR状态寄存器*/
} MEMCTRL_Type;                                 /*!< 大小=128（0x80）*/



/* =========================================================================================================================== */
/* ================                                           OTPC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief OTPC寄存器（OTPC）
  */

typedef struct {                                /*!< （@0x300700000）OTPC结构*/
  __IOM uint32_t  OTPC_MODE_REG;                /*!< （@0x00000000）模式寄存器*/
  __IOM uint32_t  OTPC_STAT_REG;                /*!< （@0x00000004）状态寄存器*/
  __IOM uint32_t  OTPC_PADDR_REG;               /*!< （@0x00000008）当使用PROG模式时，将被编程的字的地址。*/
  __IOM uint32_t  OTPC_PWORD_REG;               /*!< （@0x0000000C）使用PROG模式时将编程的32位字。*/
  __IOM uint32_t  OTPC_TIM1_REG;                /*!< （@0x00000010）OTP单元的各种定时参数。*/
  __IOM uint32_t  OTPC_TIM2_REG;                /*!< （@0x00000014）OTP单元的各种定时参数。*/
} OTPC_Type;                                    /*!< 尺寸=24（0x18）*/



/* =========================================================================================================================== */
/* ================                                            PDC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PDC寄存器（PDC）
  */

typedef struct {                                /*!< （@0x50000200）PDC结构*/
  __IOM uint32_t  PDC_CTRL0_REG;                /*!< （@0x00000000）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL1_REG;                /*!< （@0x00000004）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL2_REG;                /*!< （@0x00000008）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL3_REG;                /*!< （@0x0000000C）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL4_REG;                /*!< （@0x00000010）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL5_REG;                /*!< （@0x00000014）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL6_REG;                /*!< （@0x00000018）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL7_REG;                /*!< （@0x0000001C）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL8_REG;                /*!< （@0x00000020）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL9_REG;                /*!< （@0x00000024）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL10_REG;               /*!< （@0x00000028）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL11_REG;               /*!< （@0x0000002C）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL12_REG;               /*!< （@0x00000030）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL13_REG;               /*!< （@0x00000034）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL14_REG;               /*!< （@0x00000038）PDC控制寄存器*/
  __IOM uint32_t  PDC_CTRL15_REG;               /*!< （@0x0000003C）PDC控制寄存器*/
  __IM  uint32_t  RESERVED[16];
  __IOM uint32_t  PDC_ACKNOWLEDGE_REG;          /*!< （@0x00000080）清除挂起的PDC位*/
  __IOM uint32_t  PDC_PENDING_REG;              /*!< （@0x00000084）显示任何未决唤醒事件*/
  __IOM uint32_t  PDC_PENDING_SNC_REG;          /*!< （@0x00000088）向SNC显示任何未决IRQ*/
  __IOM uint32_t  PDC_PENDING_CM33_REG;         /*!< （@0x0000008C）向CM33显示任何未决IRQ*/
  __IOM uint32_t  PDC_PENDING_CMAC_REG;         /*!< （@0x00000090）向CM33显示任何未决IRQ*/
  __IOM uint32_t  PDC_SET_PENDING_REG;          /*!< （@0x00000094）设置挂起的PDC位*/
} PDC_Type;                                     /*!< 大小=152（0x98）*/



/* =========================================================================================================================== */
/* ================                                          PWMLED                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief PWMLED寄存器（PWMLED）
  */

typedef struct {                                /*!< （@0x50030500）PWMLED结构*/
  __IOM uint32_t  PWMLED_DUTY_CYCLE_LED1_REG;   /*!< （@0x00000000）定义PWM1的占空比*/
  __IOM uint32_t  PWMLED_DUTY_CYCLE_LED2_REG;   /*!< （@0x00000004）定义PWM2的占空比*/
  __IOM uint32_t  PWMLED_FREQUENCY_REG;         /*!< （@0x00000008）定义PWM频率*/
  __IOM uint32_t  PWMLED_CTRL_REG;              /*!< （@0x0000000C）PWM控制寄存器*/
} PWMLED_Type;                                  /*!< 尺寸=16（0x10）*/



/* =========================================================================================================================== */
/* ================                                           QSPIC                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief QSPIC寄存器（QSPIC）
  */

typedef struct {                                /*!< （@0x3800000）QSPIC结构*/
  __IOM uint32_t  QSPIC_CTRLBUS_REG;            /*!< （@0x00000000）用于手动模式的SPI总线控制寄存器*/
  __IOM uint32_t  QSPIC_CTRLMODE_REG;           /*!< （@0x00000004）模式控制寄存器*/
  __IOM uint32_t  QSPIC_RECVDATA_REG;           /*!< （@0x00000008）收到手动模式的数据*/
  __IOM uint32_t  QSPIC_BURSTCMDA_REG;          /*!< （@0x0000000C）自动模式下的读取方式（命令寄存器A）*/
  __IOM uint32_t  QSPIC_BURSTCMDB_REG;          /*!< （@0x00000010）自动模式下的读取方式（命令寄存器B）*/
  __IOM uint32_t  QSPIC_STATUS_REG;             /*!< （@0x00000014）QSPI控制器的状态寄存器*/
  __IOM uint32_t  QSPIC_WRITEDATA_REG;          /*!< （@0x00000018）将数据写入SPI总线，用于手动模式*/
  __IOM uint32_t  QSPIC_READDATA_REG;           /*!< （@0x0000001C）从SPI总线读取手动模式的数据*/
  __IOM uint32_t  QSPIC_DUMMYDATA_REG;          /*!< （@0x00000020）将伪时钟发送到SPI总线，用于手动模式*/
  __IOM uint32_t  QSPIC_ERASECTRL_REG;          /*!< （@0x00000024）QSPI擦除控制寄存器*/
  __IOM uint32_t  QSPIC_ERASECMDA_REG;          /*!< （@0x00000028）自动模式下的擦除方式（命令寄存器A）*/
  __IOM uint32_t  QSPIC_ERASECMDB_REG;          /*!< （@0x0000002C）自动模式下的擦除方式（命令寄存器B）*/
  __IOM uint32_t  QSPIC_BURSTBRK_REG;           /*!< （@0x00000030）在自动模式下读取中断序列*/
  __IOM uint32_t  QSPIC_STATUSCMD_REG;          /*!< （@0x00000034）在自动模式下读取外部设备状态的方法*/
  __IOM uint32_t  QSPIC_CHCKERASE_REG;          /*!< （@0x00000038）检查自动模式下的擦除进度*/
  __IOM uint32_t  QSPIC_GP_REG;                 /*!< （@0x0000003C）QSPI通用控制寄存器*/
  __IOM uint32_t  QSPIC_UCODE_START;            /*!< （@0x00000040）QSPIC uCode内存*/
  __IM  uint32_t  RESERVED[15];
  __IOM uint32_t  QSPIC_CTR_CTRL_REG;           /*!< （@0x00000080）QSPIC解密引擎的控制寄存器*/
  __IOM uint32_t  QSPIC_CTR_SADDR_REG;          /*!< （@0x00000084）QSPI闪存中加密内容的起始地址*/
  __IOM uint32_t  QSPIC_CTR_EADDR_REG;          /*!< （@0x00000088）QSPI闪存中加密内容的结束地址*/
  __IOM uint32_t  QSPIC_CTR_NONCE_0_3_REG;      /*!< （@0x0000008C）AES-CTR算法的非字节0到3*/
  __IOM uint32_t  QSPIC_CTR_NONCE_4_7_REG;      /*!< （@0x00000090）AES-CTR算法的Nonce字节4到7*/
  __IOM uint32_t  QSPIC_CTR_KEY_0_3_REG;        /*!< （@0x00000094）AES-CTR算法的密钥字节0到3*/
  __IOM uint32_t  QSPIC_CTR_KEY_4_7_REG;        /*!< （@0x00000098）AES-CTR算法的密钥字节4到7*/
  __IOM uint32_t  QSPIC_CTR_KEY_8_11_REG;       /*!< （@0x0000009C）AES-CTR算法的密钥字节8到11*/
  __IOM uint32_t  QSPIC_CTR_KEY_12_15_REG;      /*!< （@0x000000A0）AES-CTR算法的密钥字节12到15*/
  __IOM uint32_t  QSPIC_CTR_KEY_16_19_REG;      /*!< （@0x000000A4）AES-CTR算法的密钥字节16至19*/
  __IOM uint32_t  QSPIC_CTR_KEY_20_23_REG;      /*!< （@0x000000A8）AES-CTR算法的密钥字节20至23*/
  __IOM uint32_t  QSPIC_CTR_KEY_24_27_REG;      /*!< （@0x000000AC）AES-CTR算法的密钥字节24至27*/
  __IOM uint32_t  QSPIC_CTR_KEY_28_31_REG;      /*!< （@0x000000B0）AES-CTR算法的密钥字节28至31*/
} QSPIC_Type;                                   /*!< 大小=180（0xb4）*/



/* =========================================================================================================================== */
/* ================                                          QSPIC2                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief QSPIC2寄存器（QSPIC2）
  */

typedef struct {                                /*!< （@0x3400000）QSPIC2结构*/
  __IOM uint32_t  QSPIC2_CTRLBUS_REG;           /*!< （@0x00000000）用于手动模式的SPI总线控制寄存器*/
  __IOM uint32_t  QSPIC2_CTRLMODE_REG;          /*!< （@0x00000004）模式控制寄存器*/
  __IOM uint32_t  QSPIC2_RECVDATA_REG;          /*!< （@0x00000008）收到手动模式的数据*/
  __IOM uint32_t  QSPIC2_BURSTCMDA_REG;         /*!< （@0x0000000C）自动模式下的读取方式（命令寄存器A）*/
  __IOM uint32_t  QSPIC2_BURSTCMDB_REG;         /*!< （@0x00000010）自动模式下的读取方式（命令寄存器B）*/
  __IOM uint32_t  QSPIC2_STATUS_REG;            /*!< （@0x00000014）QSPI控制器的状态寄存器*/
  __IOM uint32_t  QSPIC2_WRITEDATA_REG;         /*!< （@0x00000018）将数据写入SPI总线，用于手动模式*/
  __IOM uint32_t  QSPIC2_READDATA_REG;          /*!< （@0x0000001C）从SPI总线读取手动模式的数据*/
  __IOM uint32_t  QSPIC2_DUMMYDATA_REG;         /*!< （@0x00000020）将伪时钟发送到SPI总线，用于手动模式*/
  __IOM uint32_t  QSPIC2_ERASECTRL_REG;         /*!< （@0x00000024）擦除控制寄存器*/
  __IOM uint32_t  QSPIC2_ERASECMDA_REG;         /*!< （@0x00000028）自动模式下的擦除方式（命令寄存器A）*/
  __IOM uint32_t  QSPIC2_ERASECMDB_REG;         /*!< （@0x0000002C）自动模式下的擦除方式（命令寄存器B）*/
  __IOM uint32_t  QSPIC2_BURSTBRK_REG;          /*!< （@0x00000030）在自动模式下读取中断序列*/
  __IOM uint32_t  QSPIC2_STATUSCMD_REG;         /*!< （@0x00000034）在自动模式下读取外部设备状态的方法*/
  __IOM uint32_t  QSPIC2_CHCKERASE_REG;         /*!< （@0x00000038）检查自动模式下的擦除进度*/
  __IOM uint32_t  QSPIC2_GP_REG;                /*!< （@0x0000003C）通用QSPIC2寄存器*/
  __IOM uint32_t  QSPIC2_AWRITECMD_REG;         /*!< （@0x00000040）当外部设备是串行SRAM时，以自动模式写入的方式*/
  __IOM uint32_t  QSPIC2_MEMBLEN_REG;           /*!< （@0x00000044）外部内存突发长度配置*/
} QSPIC2_Type;                                  /*!< 大小=72（0x48）*/



/* =========================================================================================================================== */
/* ================                                           RFMON                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief RFMON寄存器（RFMON）
  */

typedef struct {                                /*!< （@0x50040600）RFMON结构*/
  __IOM uint32_t  RFMON_CTRL_REG;               /*!< （@0x00000000）控制寄存器*/
  __IOM uint32_t  RFMON_ADDR_REG;               /*!< （@0x00000004）AHB主启动地址*/
  __IOM uint32_t  RFMON_LEN_REG;                /*!< （@0x00000008）数据长度寄存器*/
  __IOM uint32_t  RFMON_STAT_REG;               /*!< （@0x0000000C）状态寄存器*/
  __IOM uint32_t  RFMON_CRV_ADDR_REG;           /*!< （@0x00000010）AHB主电流地址*/
  __IOM uint32_t  RFMON_CRV_LEN_REG;            /*!< （@0x00000014）要传输的剩余数据*/
} RFMON_Type;                                   /*!< 尺寸=24（0x18）*/



/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief RTC寄存器（RTC）
  */

typedef struct {                                /*!< （@0x50000400）RTC结构*/
  __IOM uint32_t  RTC_CONTROL_REG;              /*!< （@0x00000000）RTC控制寄存器*/
  __IOM uint32_t  RTC_HOUR_MODE_REG;            /*!< （@0x00000004）RTC小时模式寄存器*/
  __IOM uint32_t  RTC_TIME_REG;                 /*!< （@0x00000008）RTC时间寄存器*/
  __IOM uint32_t  RTC_CALENDAR_REG;             /*!< （@0x0000000C）RTC日历寄存器*/
  __IOM uint32_t  RTC_TIME_ALARM_REG;           /*!< （@0x00000010）RTC时间报警寄存器*/
  __IOM uint32_t  RTC_CALENDAR_ALARM_REG;       /*!< （@0x00000014）RTC日历警报寄存器*/
  __IOM uint32_t  RTC_ALARM_ENABLE_REG;         /*!< （@0x00000018）RTC报警启用寄存器*/
  __IOM uint32_t  RTC_EVENT_FLAGS_REG;          /*!< （@0x0000001C）RTC事件标志寄存器*/
  __IOM uint32_t  RTC_INTERRUPT_ENABLE_REG;     /*!< （@0x00000020）RTC中断启用寄存器*/
  __IOM uint32_t  RTC_INTERRUPT_DISABLE_REG;    /*!< （@0x00000024）RTC中断禁用寄存器*/
  __IOM uint32_t  RTC_INTERRUPT_MASK_REG;       /*!< （@0x00000028）RTC中断掩码寄存器*/
  __IOM uint32_t  RTC_STATUS_REG;               /*!< （@0x0000002C）RTC状态寄存器*/
  __IOM uint32_t  RTC_KEEP_RTC_REG;             /*!< （@0x00000030）RTC保留RTC寄存器*/
  __IM  uint32_t  RESERVED[19];
  __IOM uint32_t  RTC_EVENT_CTRL_REG;           /*!< （@0x00000080）RTC事件控制寄存器*/
  __IOM uint32_t  RTC_MOTOR_EVENT_PERIOD_REG;   /*!< （@0x00000084）RTC电机事件周期寄存器*/
  __IOM uint32_t  RTC_PDC_EVENT_PERIOD_REG;     /*!< （@0x00000088）RTC PDC事件周期寄存器*/
  __IOM uint32_t  RTC_PDC_EVENT_CLEAR_REG;      /*!< （@0x0000008C）RTC PDC事件清除寄存器*/
  __IOM uint32_t  RTC_MOTOR_EVENT_CNT_REG;      /*!< （@0x00000090）RTC电机事件计数器寄存器*/
  __IOM uint32_t  RTC_PDC_EVENT_CNT_REG;        /*!< （@0x00000094）RTC PDC事件计数器寄存器*/
} RTC_Type;                                     /*!< 大小=152（0x98）*/



/* =========================================================================================================================== */
/* ================                                           SDADC                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief SDADC寄存器（SDADC）
  */

typedef struct {                                /*!< （@0x50020800）SDADC结构*/
  __IOM uint32_t  SDADC_CTRL_REG;               /*!< （@0x00000000）Sigma Delta ADC控制寄存器*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  SDADC_TEST_REG;               /*!< （@0x00000008）Sigma Delta ADC测试寄存器*/
  __IOM uint32_t  SDADC_GAIN_CORR_REG;          /*!< （@0x0000000C）Sigma Delta ADC增益校正寄存器*/
  __IOM uint32_t  SDADC_OFFS_CORR_REG;          /*!< （@0x00000010）Sigma Delta ADC偏移校正寄存器*/
  __IOM uint32_t  SDADC_CLEAR_INT_REG;          /*!< （@0x00000014）Sigma Delta ADC清除中断寄存器*/
  __IOM uint32_t  SDADC_RESULT_REG;             /*!< （@0x00000018）Sigma Delta ADC结果寄存器*/
} SDADC_Type;                                   /*!< 尺寸=28（0x1c）*/



/* =========================================================================================================================== */
/* ================                                          SMOTOR                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief SMOTOR寄存器（SMOTOR）
  */

typedef struct {                                /*!< （@0x50030E00）SMOTOR结构*/
  __IOM uint32_t  SMOTOR_CTRL_REG;              /*!< （@0x00000000）电机控制寄存器*/
  __IOM uint32_t  PG0_CTRL_REG;                 /*!< （@0x00000004）模式发生器0控制寄存器*/
  __IOM uint32_t  PG1_CTRL_REG;                 /*!< （@0x00000008）模式发生器1控制寄存器*/
  __IOM uint32_t  PG2_CTRL_REG;                 /*!< （@0x0000000C）模式发生器2控制寄存器*/
  __IOM uint32_t  PG3_CTRL_REG;                 /*!< （@0x00000010）模式发生器3控制寄存器*/
  __IOM uint32_t  PG4_CTRL_REG;                 /*!< （@0x00000014）模式发生器4控制寄存器*/
  __IOM uint32_t  SMOTOR_TRIGGER_REG;           /*!< （@0x00000018）电机控制器触发寄存器*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  SMOTOR_CMD_FIFO_REG;          /*!< （@0x00000020）电机控制命令FIFO寄存器*/
  __IOM uint32_t  SMOTOR_CMD_READ_PTR_REG;      /*!< （@0x00000024）命令读取指针寄存器*/
  __IOM uint32_t  SMOTOR_CMD_WRITE_PTR_REG;     /*!< （@0x00000028）命令写入指针寄存器*/
  __IOM uint32_t  SMOTOR_STATUS_REG;            /*!< （@0x0000002C）电机控制器状态寄存器*/
  __IOM uint32_t  SMOTOR_IRQ_CLEAR_REG;         /*!< （@0x00000030）电机控制IRQ清除寄存器*/
  __IM  uint32_t  RESERVED1[3];
  __IOM uint32_t  WAVETABLE_BASE;               /*!< （@0x00000040）波形表的基址*/
  __IM  uint32_t  RESERVED2[15];
  __IOM uint32_t  CMD_TABLE_BASE;               /*!< （@0x00000080）命令表的基地址*/
} SMOTOR_Type;                                  /*!< 大小=132（0x84）*/



/* =========================================================================================================================== */
/* ================                                            SNC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SNC寄存器（SNC）
  */

typedef struct {                                /*!< （@0x50020C00）SNC结构*/
  __IOM uint32_t  SNC_CTRL_REG;                 /*!< （@0x00000000）传感器节点控制寄存器*/
  __IOM uint32_t  SNC_STATUS_REG;               /*!< （@0x00000004）传感器节点状态寄存器*/
  __IOM uint32_t  SNC_LP_TIMER_REG;             /*!< （@0x00000008）传感器节点低功耗定时器寄存器*/
  __IOM uint32_t  SNC_PC_REG;                   /*!< （@0x0000000C）传感器节点程序计数器*/
  __IOM uint32_t  SNC_R1_REG;                   /*!< （@0x00000010）传感器节点核心-操作数1寄存器*/
  __IOM uint32_t  SNC_R2_REG;                   /*!< （@0x00000014）传感器节点核心-操作数2寄存器*/
  __IOM uint32_t  SNC_TMP1_REG;                 /*!< （@0x00000018）传感器节点核心-临时寄存器1*/
  __IOM uint32_t  SNC_TMP2_REG;                 /*!< （@0x0000001C）传感器节点核心-临时寄存器2*/
} SNC_Type;                                     /*!< 大小=32（0x20）*/



/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SPI寄存器（SPI）
  */

typedef struct {                                /*!< （@0x50020300）SPI结构*/
  __IOM uint32_t  SPI_CTRL_REG;                 /*!< （@0x00000000）SPI控制寄存器0*/
  __IOM uint32_t  SPI_RX_TX_REG;                /*!< （@0x00000004）SPI RX/TX寄存器0*/
  __IOM uint32_t  SPI_CLEAR_INT_REG;            /*!< （@0x00000008）SPI清除中断寄存器*/
} SPI_Type;                                     /*!< 大小=12（0xc）*/



/* =========================================================================================================================== */
/* ================                                           SPI2                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SPI2寄存器（SPI2）
  */

typedef struct {                                /*!< （@0x50020400）SPI2结构*/
  __IOM uint32_t  SPI2_CTRL_REG;                /*!< （@0x00000000）SPI控制寄存器0*/
  __IOM uint32_t  SPI2_RX_TX_REG;               /*!< （@0x00000004）SPI RX/TX寄存器0*/
  __IOM uint32_t  SPI2_CLEAR_INT_REG;           /*!< （@0x00000008）SPI清除中断寄存器*/
} SPI2_Type;                                    /*!< 大小=12（0xc）*/



/* =========================================================================================================================== */
/* ================                                         SYS_WDOG                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief SYS_WDOG寄存器（SYS_WDOG）
  */

typedef struct {                                /*!< （@0x50000700）SYS_WDOG结构*/
  __IOM uint32_t  WATCHDOG_REG;                 /*!< （@0x00000000）看门狗定时器寄存器。*/
  __IOM uint32_t  WATCHDOG_CTRL_REG;            /*!< （@0x00000004）看门狗控制寄存器。*/
} SYS_WDOG_Type;                                /*!< 大小=8（0x8）*/



/* =========================================================================================================================== */
/* ================                                           TIMER                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER寄存器（TIMER）
  */

typedef struct {                                /*!< （@0x50010200）TIMER结构*/
  __IOM uint32_t  TIMER_CTRL_REG;               /*!< （@0x00000000）定时器控制寄存器*/
  __IOM uint32_t  TIMER_TIMER_VAL_REG;          /*!< （@0x00000004）计时器计数器值*/
  __IOM uint32_t  TIMER_STATUS_REG;             /*!< （@0x00000008）计时器状态寄存器*/
  __IOM uint32_t  TIMER_GPIO1_CONF_REG;         /*!< （@0x0000000C）计时器gpio1选择*/
  __IOM uint32_t  TIMER_GPIO2_CONF_REG;         /*!< （@0x00000010）计时器gpio2选择*/
  __IOM uint32_t  TIMER_RELOAD_REG;             /*!< （@0x00000014）放炮模式下的计时器重新加载值和延迟*/
  __IOM uint32_t  TIMER_SHOTWIDTH_REG;          /*!< （@0x00000018）放炮模式下的计时器放炮持续时间*/
  __IOM uint32_t  TIMER_PRESCALER_REG;          /*!< （@0x0000001C）定时器预分频器值*/
  __IOM uint32_t  TIMER_CAPTURE_GPIO1_REG;      /*!< （@0x00000020）GPIO1上事件的计时器值*/
  __IOM uint32_t  TIMER_CAPTURE_GPIO2_REG;      /*!< （@0x00000024）GPIO2上事件的计时器值*/
  __IOM uint32_t  TIMER_PRESCALER_VAL_REG;      /*!< （@0x00000028）计时器预分频器计数器值w*/
  __IOM uint32_t  TIMER_PWM_FREQ_REG;           /*!< （@0x0000002C）定时器pwm频率寄存器*/
  __IOM uint32_t  TIMER_PWM_DC_REG;             /*!< （@0x00000030）定时器pwm dc寄存器*/
  __IOM uint32_t  TIMER_GPIO3_CONF_REG;         /*!< （@0x00000034）计时器gpio3选择*/
  __IOM uint32_t  TIMER_GPIO4_CONF_REG;         /*!< （@0x00000038）计时器gpio4选择*/
  __IOM uint32_t  TIMER_CAPTURE_GPIO3_REG;      /*!< （@0x0000003C）GPIO1上事件的计时器值*/
  __IOM uint32_t  TIMER_CAPTURE_GPIO4_REG;      /*!< （@0x00000040）GPIO1上事件的计时器值*/
  __IOM uint32_t  TIMER_CLEAR_GPIO_EVENT_REG;   /*!< （@0x00000044）计时器清除gpio事件寄存器*/
  __IOM uint32_t  TIMER_CLEAR_IRQ_REG;          /*!< （@0x00000048）定时器清除中断*/
} TIMER_Type;                                   /*!< 尺寸=76（0x4c）*/



/* =========================================================================================================================== */
/* ================                                          TIMER2                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER2寄存器（TIMER2）
  */

typedef struct {                                /*!< （@0x50010300）TIMER2结构*/
  __IOM uint32_t  TIMER2_CTRL_REG;              /*!< （@0x00000000）定时器控制寄存器*/
  __IOM uint32_t  TIMER2_TIMER_VAL_REG;         /*!< （@0x00000004）计时器计数器值*/
  __IOM uint32_t  TIMER2_STATUS_REG;            /*!< （@0x00000008）计时器状态寄存器*/
  __IOM uint32_t  TIMER2_GPIO1_CONF_REG;        /*!< （@0x0000000C）计时器gpio1选择*/
  __IOM uint32_t  TIMER2_GPIO2_CONF_REG;        /*!< （@0x00000010）计时器gpio2选择*/
  __IOM uint32_t  TIMER2_RELOAD_REG;            /*!< （@0x00000014）放炮模式下的计时器重新加载值和延迟*/
  __IOM uint32_t  TIMER2_SHOTWIDTH_REG;         /*!< （@0x00000018）放炮模式下的计时器放炮持续时间*/
  __IOM uint32_t  TIMER2_PRESCALER_REG;         /*!< （@0x0000001C）定时器预分频器值*/
  __IOM uint32_t  TIMER2_CAPTURE_GPIO1_REG;     /*!< （@0x00000020）GPIO1上事件的计时器值*/
  __IOM uint32_t  TIMER2_CAPTURE_GPIO2_REG;     /*!< （@0x00000024）GPIO2上事件的计时器值*/
  __IOM uint32_t  TIMER2_PRESCALER_VAL_REG;     /*!< （@0x00000028）计时器预分频器计数器值w*/
  __IOM uint32_t  TIMER2_PWM_FREQ_REG;          /*!< （@0x0000002C）定时器pwm频率寄存器*/
  __IOM uint32_t  TIMER2_PWM_DC_REG;            /*!< （@0x00000030）定时器pwm dc寄存器*/
  __IOM uint32_t  TIMER2_CLEAR_IRQ_REG;         /*!< （@0x00000034）定时器清除中断*/
} TIMER2_Type;                                  /*!< 大小=56（0x38）*/



/* =========================================================================================================================== */
/* ================                                          TIMER3                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER3寄存器（TIMER3）
  */

typedef struct {                                /*!< （@0x50040A00）TIMER3结构*/
  __IOM uint32_t  TIMER3_CTRL_REG;              /*!< （@0x00000000）定时器控制寄存器*/
  __IOM uint32_t  TIMER3_TIMER_VAL_REG;         /*!< （@0x00000004）计时器计数器值*/
  __IOM uint32_t  TIMER3_STATUS_REG;            /*!< （@0x00000008）计时器状态寄存器*/
  __IOM uint32_t  TIMER3_GPIO1_CONF_REG;        /*!< （@0x0000000C）计时器gpio1选择*/
  __IOM uint32_t  TIMER3_GPIO2_CONF_REG;        /*!< （@0x00000010）计时器gpio2选择*/
  __IOM uint32_t  TIMER3_RELOAD_REG;            /*!< （@0x00000014）放炮模式下的计时器重新加载值和延迟*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  TIMER3_PRESCALER_REG;         /*!< （@0x0000001C）定时器预分频器值*/
  __IOM uint32_t  TIMER3_CAPTURE_GPIO1_REG;     /*!< （@0x00000020）GPIO1上事件的计时器值*/
  __IOM uint32_t  TIMER3_CAPTURE_GPIO2_REG;     /*!< （@0x00000024）GPIO2上事件的计时器值*/
  __IOM uint32_t  TIMER3_PRESCALER_VAL_REG;     /*!< （@0x00000028）计时器预分频器计数器值w*/
  __IOM uint32_t  TIMER3_PWM_FREQ_REG;          /*!< （@0x0000002C）定时器pwm频率寄存器*/
  __IOM uint32_t  TIMER3_PWM_DC_REG;            /*!< （@0x00000030）定时器pwm dc寄存器*/
  __IOM uint32_t  TIMER3_CLEAR_IRQ_REG;         /*!< （@0x00000034）定时器清除中断*/
} TIMER3_Type;                                  /*!< 大小=56（0x38）*/



/* =========================================================================================================================== */
/* ================                                          TIMER4                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER4寄存器（TIMER4）
  */

typedef struct {                                /*!< （@0x50040B00）TIMER4结构*/
  __IOM uint32_t  TIMER4_CTRL_REG;              /*!< （@0x00000000）定时器控制寄存器*/
  __IOM uint32_t  TIMER4_TIMER_VAL_REG;         /*!< （@0x00000004）计时器计数器值*/
  __IOM uint32_t  TIMER4_STATUS_REG;            /*!< （@0x00000008）计时器状态寄存器*/
  __IOM uint32_t  TIMER4_GPIO1_CONF_REG;        /*!< （@0x0000000C）计时器gpio1选择*/
  __IOM uint32_t  TIMER4_GPIO2_CONF_REG;        /*!< （@0x00000010）计时器gpio2选择*/
  __IOM uint32_t  TIMER4_RELOAD_REG;            /*!< （@0x00000014）放炮模式下的计时器重新加载值和延迟*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  TIMER4_PRESCALER_REG;         /*!< （@0x0000001C）定时器预分频器值*/
  __IOM uint32_t  TIMER4_CAPTURE_GPIO1_REG;     /*!< （@0x00000020）GPIO1上事件的计时器值*/
  __IOM uint32_t  TIMER4_CAPTURE_GPIO2_REG;     /*!< （@0x00000024）GPIO2上事件的计时器值*/
  __IOM uint32_t  TIMER4_PRESCALER_VAL_REG;     /*!< （@0x00000028）计时器预分频器计数器值w*/
  __IOM uint32_t  TIMER4_PWM_FREQ_REG;          /*!< （@0x0000002C）定时器pwm频率寄存器*/
  __IOM uint32_t  TIMER4_PWM_DC_REG;            /*!< （@0x00000030）定时器pwm dc寄存器*/
  __IOM uint32_t  TIMER4_CLEAR_IRQ_REG;         /*!< （@0x00000034）定时器清除中断*/
} TIMER4_Type;                                  /*!< 大小=56（0x38）*/



/* =========================================================================================================================== */
/* ================                                           TRNG                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief TRNG寄存器（TRNG）
  */

typedef struct {                                /*!< （@0x50040C00）TRNG结构*/
  __IOM uint32_t  TRNG_CTRL_REG;                /*!< （@0x00000000）TRNG控制寄存器*/
  __IOM uint32_t  TRNG_FIFOLVL_REG;             /*!< （@0x00000004）TRNG FIFO电平寄存器*/
  __IOM uint32_t  TRNG_VER_REG;                 /*!< （@0x00000008）TRNG版本寄存器*/
} TRNG_Type;                                    /*!< 大小=12（0xc）*/



/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief UART寄存器（UART）
  */

typedef struct {                                /*!< （@0x50020000）UART结构*/
  __IOM uint32_t  UART_RBR_THR_DLL_REG;         /*!< （@0x00000000）接收缓冲寄存器*/
  __IOM uint32_t  UART_IER_DLH_REG;             /*!< （@0x00000004）中断启用寄存器*/
  __IOM uint32_t  UART_IIR_FCR_REG;             /*!< （@0x00000008）中断识别寄存器/FIFO控制寄存器*/
  __IOM uint32_t  UART_LCR_REG;                 /*!< （@0x0000000C）线路控制寄存器*/
  __IOM uint32_t  UART_MCR_REG;                 /*!< （@0x00000010）调制解调器控制寄存器*/
  __IOM uint32_t  UART_LSR_REG;                 /*!< （@0x00000014）线路状态寄存器*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  UART_SCR_REG;                 /*!< （@0x0000001C）暂存寄存器*/
  __IM  uint32_t  RESERVED1[4];
  __IOM uint32_t  UART_SRBR_STHR0_REG;          /*!< （@0x00000030）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR1_REG;          /*!< （@0x00000034）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR2_REG;          /*!< （@0x00000038）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR3_REG;          /*!< （@0x0000003C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR4_REG;          /*!< （@0x00000040）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR5_REG;          /*!< （@0x00000044）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR6_REG;          /*!< （@0x00000048）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR7_REG;          /*!< （@0x0000004C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR8_REG;          /*!< （@0x00000050）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR9_REG;          /*!< （@0x00000054）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR10_REG;         /*!< （@0x00000058）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR11_REG;         /*!< （@0x0000005C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR12_REG;         /*!< （@0x00000060）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR13_REG;         /*!< （@0x00000064）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR14_REG;         /*!< （@0x00000068）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART_SRBR_STHR15_REG;         /*!< （@0x0000006C）影子接收/发送缓冲寄存器*/
  __IM  uint32_t  RESERVED2[3];
  __IOM uint32_t  UART_USR_REG;                 /*!< （@0x0000007C）UART状态寄存器。*/
  __IOM uint32_t  UART_TFL_REG;                 /*!< （@0x00000080）传输FIFO电平*/
  __IOM uint32_t  UART_RFL_REG;                 /*!< （@0x00000084）接收FIFO级别。*/
  __IOM uint32_t  UART_SRR_REG;                 /*!< （@0x00000088）软件重置寄存器。*/
  __IM  uint32_t  RESERVED3;
  __IOM uint32_t  UART_SBCR_REG;                /*!< （@0x00000090）阴影中断控制寄存器*/
  __IOM uint32_t  UART_SDMAM_REG;               /*!< （@0x00000094）影子DMA模式*/
  __IOM uint32_t  UART_SFE_REG;                 /*!< （@0x00000098）影子FIFO启用*/
  __IOM uint32_t  UART_SRT_REG;                 /*!< （@0x0000009C）阴影RCVR触发器*/
  __IOM uint32_t  UART_STET_REG;                /*!< （@0x000000A0）影子TX空触发器*/
  __IOM uint32_t  UART_HTX_REG;                 /*!< （@0x000000A4）停止发送*/
  __IOM uint32_t  UART_DMASA_REG;               /*!< （@0x000000A8）DMA软件确认*/
  __IM  uint32_t  RESERVED4[5];
  __IOM uint32_t  UART_DLF_REG;                 /*!< （@0x000000C0）除数锁存分数寄存器*/
  __IM  uint32_t  RESERVED5[13];
  __IOM uint32_t  UART_UCV_REG;                 /*!< （@0x000000F8）组件版本*/
  __IOM uint32_t  UART_CTR_REG;                 /*!< （@0x000000FC）组件类型寄存器*/
} UART_Type;                                    /*!< 尺寸=256（0x100）*/



/* =========================================================================================================================== */
/* ================                                           UART2                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief UART2寄存器（UART2）
  */

typedef struct {                                /*!< （@0x50020100）UART2结构*/
  __IOM uint32_t  UART2_RBR_THR_DLL_REG;        /*!< （@0x00000000）接收缓冲寄存器*/
  __IOM uint32_t  UART2_IER_DLH_REG;            /*!< （@0x00000004）中断启用寄存器*/
  __IOM uint32_t  UART2_IIR_FCR_REG;            /*!< （@0x00000008）中断识别寄存器/FIFO控制寄存器*/
  __IOM uint32_t  UART2_LCR_REG;                /*!< （@0x0000000C）线路控制寄存器*/
  __IOM uint32_t  UART2_MCR_REG;                /*!< （@0x00000010）调制解调器控制寄存器*/
  __IOM uint32_t  UART2_LSR_REG;                /*!< （@0x00000014）线路状态寄存器*/
  __IOM uint32_t  UART2_MSR_REG;                /*!< （@0x00000018）调制解调器状态寄存器*/
  __IOM uint32_t  UART2_SCR_REG;                /*!< （@0x0000001C）暂存寄存器*/
  __IM  uint32_t  RESERVED[4];
  __IOM uint32_t  UART2_SRBR_STHR0_REG;         /*!< （@0x00000030）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR1_REG;         /*!< （@0x00000034）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR2_REG;         /*!< （@0x00000038）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR3_REG;         /*!< （@0x0000003C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR4_REG;         /*!< （@0x00000040）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR5_REG;         /*!< （@0x00000044）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR6_REG;         /*!< （@0x00000048）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR7_REG;         /*!< （@0x0000004C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR8_REG;         /*!< （@0x00000050）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR9_REG;         /*!< （@0x00000054）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR10_REG;        /*!< （@0x00000058）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR11_REG;        /*!< （@0x0000005C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR12_REG;        /*!< （@0x00000060）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR13_REG;        /*!< （@0x00000064）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR14_REG;        /*!< （@0x00000068）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART2_SRBR_STHR15_REG;        /*!< （@0x0000006C）影子接收/发送缓冲寄存器*/
  __IM  uint32_t  RESERVED1[3];
  __IOM uint32_t  UART2_USR_REG;                /*!< （@0x0000007C）UART状态寄存器。*/
  __IOM uint32_t  UART2_TFL_REG;                /*!< （@0x00000080）传输FIFO电平*/
  __IOM uint32_t  UART2_RFL_REG;                /*!< （@0x00000084）接收FIFO级别。*/
  __IOM uint32_t  UART2_SRR_REG;                /*!< （@0x00000088）软件重置寄存器。*/
  __IOM uint32_t  UART2_SRTS_REG;               /*!< （@0x0000008C）要发送的影子请求*/
  __IOM uint32_t  UART2_SBCR_REG;               /*!< （@0x00000090）阴影中断控制寄存器*/
  __IOM uint32_t  UART2_SDMAM_REG;              /*!< （@0x00000094）影子DMA模式*/
  __IOM uint32_t  UART2_SFE_REG;                /*!< （@0x00000098）影子FIFO启用*/
  __IOM uint32_t  UART2_SRT_REG;                /*!< （@0x0000009C）阴影RCVR触发器*/
  __IOM uint32_t  UART2_STET_REG;               /*!< （@0x000000A0）影子TX空触发器*/
  __IOM uint32_t  UART2_HTX_REG;                /*!< （@0x000000A4）停止发送*/
  __IOM uint32_t  UART2_DMASA_REG;              /*!< （@0x000000A8）DMA软件确认*/
  __IM  uint32_t  RESERVED2[5];
  __IOM uint32_t  UART2_DLF_REG;                /*!< （@0x000000C0）除数锁存分数寄存器*/
  __IOM uint32_t  UART2_RAR_REG;                /*!< （@0x000000C4）接收地址寄存器*/
  __IOM uint32_t  UART2_TAR_REG;                /*!< （@0x000000C8）发送地址寄存器*/
  __IOM uint32_t  UART2_LCR_EXT;                /*!< （@0x000000CC）线路扩展控制寄存器*/
  __IM  uint32_t  RESERVED3[10];
  __IOM uint32_t  UART2_UCV_REG;                /*!< （@0x000000F8）组件版本*/
  __IOM uint32_t  UART2_CTR_REG;                /*!< （@0x000000FC）组件类型寄存器*/
} UART2_Type;                                   /*!< 尺寸=256（0x100）*/



/* =========================================================================================================================== */
/* ================                                           UART3                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief UART3寄存器（UART3）
  */

typedef struct {                                /*!< （@0x50020200）UART3结构*/
  __IOM uint32_t  UART3_RBR_THR_DLL_REG;        /*!< （@0x00000000）接收缓冲寄存器*/
  __IOM uint32_t  UART3_IER_DLH_REG;            /*!< （@0x00000004）中断启用寄存器*/
  __IOM uint32_t  UART3_IIR_FCR_REG;            /*!< （@0x00000008）中断识别寄存器/FIFO控制寄存器*/
  __IOM uint32_t  UART3_LCR_REG;                /*!< （@0x0000000C）线路控制寄存器*/
  __IOM uint32_t  UART3_MCR_REG;                /*!< （@0x00000010）调制解调器控制寄存器*/
  __IOM uint32_t  UART3_LSR_REG;                /*!< （@0x00000014）线路状态寄存器*/
  __IOM uint32_t  UART3_MSR_REG;                /*!< （@0x00000018）调制解调器状态寄存器*/
  __IOM uint32_t  UART3_CONFIG_REG;             /*!< （@0x0000001C）ISO7816配置寄存器*/
  __IM  uint32_t  RESERVED[4];
  __IOM uint32_t  UART3_SRBR_STHR0_REG;         /*!< （@0x00000030）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR1_REG;         /*!< （@0x00000034）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR2_REG;         /*!< （@0x00000038）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR3_REG;         /*!< （@0x0000003C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR4_REG;         /*!< （@0x00000040）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR5_REG;         /*!< （@0x00000044）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR6_REG;         /*!< （@0x00000048）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR7_REG;         /*!< （@0x0000004C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR8_REG;         /*!< （@0x00000050）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR9_REG;         /*!< （@0x00000054）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR10_REG;        /*!< （@0x00000058）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR11_REG;        /*!< （@0x0000005C）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR12_REG;        /*!< （@0x00000060）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR13_REG;        /*!< （@0x00000064）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR14_REG;        /*!< （@0x00000068）影子接收/发送缓冲寄存器*/
  __IOM uint32_t  UART3_SRBR_STHR15_REG;        /*!< （@0x0000006C）影子接收/发送缓冲寄存器*/
  __IM  uint32_t  RESERVED1[3];
  __IOM uint32_t  UART3_USR_REG;                /*!< （@0x0000007C）UART状态寄存器。*/
  __IOM uint32_t  UART3_TFL_REG;                /*!< （@0x00000080）传输FIFO电平*/
  __IOM uint32_t  UART3_RFL_REG;                /*!< （@0x00000084）接收FIFO级别。*/
  __IOM uint32_t  UART3_SRR_REG;                /*!< （@0x00000088）软件重置寄存器。*/
  __IOM uint32_t  UART3_SRTS_REG;               /*!< （@0x0000008C）要发送的影子请求*/
  __IOM uint32_t  UART3_SBCR_REG;               /*!< （@0x00000090）阴影中断控制寄存器*/
  __IOM uint32_t  UART3_SDMAM_REG;              /*!< （@0x00000094）影子DMA模式*/
  __IOM uint32_t  UART3_SFE_REG;                /*!< （@0x00000098）影子FIFO启用*/
  __IOM uint32_t  UART3_SRT_REG;                /*!< （@0x0000009C）阴影RCVR触发器*/
  __IOM uint32_t  UART3_STET_REG;               /*!< （@0x000000A0）影子TX空触发器*/
  __IOM uint32_t  UART3_HTX_REG;                /*!< （@0x000000A4）停止发送*/
  __IOM uint32_t  UART3_DMASA_REG;              /*!< （@0x000000A8）DMA软件确认*/
  __IM  uint32_t  RESERVED2[5];
  __IOM uint32_t  UART3_DLF_REG;                /*!< （@0x000000C0）除数锁存分数寄存器*/
  __IOM uint32_t  UART3_RAR_REG;                /*!< （@0x000000C4）接收地址寄存器*/
  __IOM uint32_t  UART3_TAR_REG;                /*!< （@0x000000C8）发送地址寄存器*/
  __IOM uint32_t  UART3_LCR_EXT;                /*!< （@0x000000CC）线路扩展控制寄存器*/
  __IM  uint32_t  RESERVED3[4];
  __IOM uint32_t  UART3_CTRL_REG;               /*!< （@0x000000E0）ISO7816控制寄存器*/
  __IOM uint32_t  UART3_TIMER_REG;              /*!< （@0x000000E4）ISO7816定时器寄存器*/
  __IOM uint32_t  UART3_ERR_CTRL_REG;           /*!< （@0x000000E8）ISO7816错误信号控制寄存器*/
  __IOM uint32_t  UART3_IRQ_STATUS_REG;         /*!< （@0x000000EC）ISO7816中断状态寄存器*/
  __IM  uint32_t  RESERVED4[2];
  __IOM uint32_t  UART3_UCV_REG;                /*!< （@0x000000F8）组件版本*/
  __IOM uint32_t  UART3_CTR_REG;                /*!< （@0x000000FC）组件类型寄存器*/
} UART3_Type;                                   /*!< 尺寸=256（0x100）*/



/* =========================================================================================================================== */
/* ================                                            USB                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief USB寄存器（USB）
  */

typedef struct {                                /*!< （@0x50040000）USB结构*/
  __IOM uint32_t  USB_MCTRL_REG;                /*!< （@0x00000000）主控制寄存器）*/
  __IOM uint32_t  USB_XCVDIAG_REG;              /*!< （@0x00000004）收发器诊断寄存器（仅用于测试）*/
  __IOM uint32_t  USB_TCR_REG;                  /*!< （@0x00000008）收发器配置寄存器*/
  __IOM uint32_t  USB_UTR_REG;                  /*!< （@0x0000000C）USB测试寄存器（仅用于测试）*/
  __IOM uint32_t  USB_FAR_REG;                  /*!< （@0x00000010）函数地址寄存器*/
  __IOM uint32_t  USB_NFSR_REG;                 /*!< （@0x00000014）节点功能状态寄存器*/
  __IOM uint32_t  USB_MAEV_REG;                 /*!< （@0x00000018）主事件寄存器*/
  __IOM uint32_t  USB_MAMSK_REG;                /*!< （@0x0000001C）主掩码寄存器*/
  __IOM uint32_t  USB_ALTEV_REG;                /*!< （@0x00000020）备用事件寄存器*/
  __IOM uint32_t  USB_ALTMSK_REG;               /*!< （@0x00000024）备用掩码寄存器*/
  __IOM uint32_t  USB_TXEV_REG;                 /*!< （@0x00000028）传输事件寄存器*/
  __IOM uint32_t  USB_TXMSK_REG;                /*!< （@0x0000002C）传输掩码寄存器*/
  __IOM uint32_t  USB_RXEV_REG;                 /*!< （@0x00000030）接收事件寄存器*/
  __IOM uint32_t  USB_RXMSK_REG;                /*!< （@0x00000034）接收掩码寄存器*/
  __IOM uint32_t  USB_NAKEV_REG;                /*!< （@0x00000038）NAK事件寄存器*/
  __IOM uint32_t  USB_NAKMSK_REG;               /*!< （@0x0000003C）NAK掩码寄存器*/
  __IOM uint32_t  USB_FWEV_REG;                 /*!< （@0x00000040）FIFO警告事件寄存器*/
  __IOM uint32_t  USB_FWMSK_REG;                /*!< （@0x00000044）FIFO警告掩码寄存器*/
  __IOM uint32_t  USB_FNH_REG;                  /*!< （@0x00000048）帧号高字节寄存器*/
  __IOM uint32_t  USB_FNL_REG;                  /*!< （@0x0000004C）帧号低字节寄存器*/
  __IM  uint32_t  RESERVED[11];
  __IOM uint32_t  USB_UX20CDR_REG;              /*!< （@0x0000007C）收发器2.0配置和诊断寄存器（仅用于测试）*/
  __IOM uint32_t  USB_EPC0_REG;                 /*!< （@0x00000080）端点控制0寄存器*/
  __IOM uint32_t  USB_TXD0_REG;                 /*!< （@0x00000084）传输数据0寄存器*/
  __IOM uint32_t  USB_TXS0_REG;                 /*!< （@0x00000088）传输状态0寄存器*/
  __IOM uint32_t  USB_TXC0_REG;                 /*!< （@0x0000008C）发送命令0寄存器*/
  __IOM uint32_t  USB_EP0_NAK_REG;              /*!< （@0x00000090）EP0 INNAK和OUTNAK寄存器*/
  __IOM uint32_t  USB_RXD0_REG;                 /*!< （@0x00000094）接收数据0寄存器*/
  __IOM uint32_t  USB_RXS0_REG;                 /*!< （@0x00000098）接收状态0寄存器*/
  __IOM uint32_t  USB_RXC0_REG;                 /*!< （@0x0000009C）接收命令0寄存器*/
  __IOM uint32_t  USB_EPC1_REG;                 /*!< （@0x000000A0）端点控制寄存器1*/
  __IOM uint32_t  USB_TXD1_REG;                 /*!< （@0x000000A4）传输数据寄存器1*/
  __IOM uint32_t  USB_TXS1_REG;                 /*!< （@0x000000A8）传输状态寄存器1*/
  __IOM uint32_t  USB_TXC1_REG;                 /*!< （@0x000000AC）传输命令寄存器1*/
  __IOM uint32_t  USB_EPC2_REG;                 /*!< （@0x000000B0）端点控制寄存器2*/
  __IOM uint32_t  USB_RXD1_REG;                 /*!< （@0x000000B4）接收数据寄存器，1*/
  __IOM uint32_t  USB_RXS1_REG;                 /*!< （@0x000000B8）接收状态寄存器1*/
  __IOM uint32_t  USB_RXC1_REG;                 /*!< （@0x000000BC）接收命令寄存器1*/
  __IOM uint32_t  USB_EPC3_REG;                 /*!< （@0x000000C0）端点控制寄存器3*/
  __IOM uint32_t  USB_TXD2_REG;                 /*!< （@0x000000C4）传输数据寄存器2*/
  __IOM uint32_t  USB_TXS2_REG;                 /*!< （@0x000000C8）传输状态寄存器2*/
  __IOM uint32_t  USB_TXC2_REG;                 /*!< （@0x000000CC）传输命令寄存器2*/
  __IOM uint32_t  USB_EPC4_REG;                 /*!< （@0x000000D0）端点控制寄存器4*/
  __IOM uint32_t  USB_RXD2_REG;                 /*!< （@0x000000D4）接收数据寄存器2*/
  __IOM uint32_t  USB_RXS2_REG;                 /*!< （@0x000000D8）接收状态寄存器2*/
  __IOM uint32_t  USB_RXC2_REG;                 /*!< （@0x000000DC）接收命令寄存器2*/
  __IOM uint32_t  USB_EPC5_REG;                 /*!< （@0x000000E0）端点控制寄存器5*/
  __IOM uint32_t  USB_TXD3_REG;                 /*!< （@0x000000E4）传输数据寄存器3*/
  __IOM uint32_t  USB_TXS3_REG;                 /*!< （@0x000000E8）传输状态寄存器3*/
  __IOM uint32_t  USB_TXC3_REG;                 /*!< （@0x000000EC）传输命令寄存器3*/
  __IOM uint32_t  USB_EPC6_REG;                 /*!< （@0x000000F0）端点控制寄存器6*/
  __IOM uint32_t  USB_RXD3_REG;                 /*!< （@0x000000F4）接收数据寄存器3*/
  __IOM uint32_t  USB_RXS3_REG;                 /*!< （@0x000000F8）接收状态寄存器3*/
  __IOM uint32_t  USB_RXC3_REG;                 /*!< （@0x000000FC）接收命令寄存器3*/
  __IM  uint32_t  RESERVED1[40];
  __IOM uint32_t  USB_DMA_CTRL_REG;             /*!< （@0x000001A0）USB DMA控制寄存器*/
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  USB_CHARGER_CTRL_REG;         /*!< （@0x000001A8）USB充电器控制寄存器*/
  __IOM uint32_t  USB_CHARGER_STAT_REG;         /*!< （@0x000001AC）USB充电器状态寄存器*/
} USB_Type;                                     /*!< 尺寸=432（0x1b0）*/



/* =========================================================================================================================== */
/* ================                                          WAKEUP                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief WAKEUP寄存器（WAKEUP）
  */

typedef struct {                                /*!< （@0x50000100）唤醒结构*/
  __IOM uint32_t  WKUP_CTRL_REG;                /*!< （@0x00000000）唤醒计数器的控制寄存器*/
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  WKUP_RESET_IRQ_REG;           /*!< （@0x00000008）重置唤醒中断*/
  __IM  uint32_t  RESERVED1[2];
  __IOM uint32_t  WKUP_SELECT_P0_REG;           /*!< （@0x00000014）选择P0端口的哪些输入可以触发工作计数器*/
  __IOM uint32_t  WKUP_SELECT_P1_REG;           /*!< （@0x00000018）选择P1端口的哪些输入可以触发工作计数器*/
  __IM  uint32_t  RESERVED2[3];
  __IOM uint32_t  WKUP_POL_P0_REG;              /*!< （@0x00000028）为每个P0输入选择倍性极性*/
  __IOM uint32_t  WKUP_POL_P1_REG;              /*!< （@0x0000002C）为每个P1输入选择倍性极性*/
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  WKUP_STATUS_P0_REG;           /*!< （@0x0000003C）P0的事件状态寄存器*/
  __IOM uint32_t  WKUP_STATUS_P1_REG;           /*!< （@0x00000040）P1的事件状态寄存器*/
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  WKUP_CLEAR_P0_REG;            /*!< （@0x00000048）清除P0的事件寄存器*/
  __IOM uint32_t  WKUP_CLEAR_P1_REG;            /*!< （@0x0000004C）清除P1的事件寄存器*/
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  WKUP_SEL_GPIO_P0_REG;         /*!< （@0x00000054）选择P0端口的哪些输入可以触发中断*/
  __IOM uint32_t  WKUP_SEL_GPIO_P1_REG;         /*!< （@0x00000058）选择P1端口的哪些输入可以触发中断*/
} WAKEUP_Type;                                  /*!< 大小=92（0x5c）*/


/** @} */ /* 组末Device_Peripheral_eperipherals*/


/* =========================================================================================================================== */
/* ====================特定于设备的外围地址映射====================*/
/* =========================================================================================================================== */


#define AES_HASH_BASE               0x30040000UL
#define ANAMISC_BIF_BASE            0x50030B00UL
#define APU_BASE                    0x50030600UL
#define CACHE_BASE                  0x100C0000UL
#define CHARGER_BASE                0x50040400UL
#define CHIP_VERSION_BASE           0x50040200UL
#define CRG_COM_BASE                0x50020900UL
#define CRG_PER_BASE                0x50030C00UL
#define CRG_SYS_BASE                0x50040500UL
#define CRG_TOP_BASE                0x50000000UL
#define CRG_XTAL_BASE               0x50010000UL
#define DCDC_BASE                   0x50000300UL
#define DMA_BASE                    0x50040800UL
#define DW_BASE                     0x30020000UL
#define GPADC_BASE                  0x50030900UL
#define GPIO_BASE                   0x50020A00UL
#define GPREG_BASE                  0x50040300UL
#define I2C_BASE                    0x50020600UL
#define I2C2_BASE                   0x50020700UL
#define LCDC_BASE                   0x30030000UL
#define LRA_BASE                    0x50030A00UL
#define MEMCTRL_BASE                0x50050000UL
#define OTPC_BASE                   0x30070000UL
#define PDC_BASE                    0x50000200UL
#define PWMLED_BASE                 0x50030500UL
#define QSPIC_BASE                  0x38000000UL
#define QSPIC2_BASE                 0x34000000UL
#define RFMON_BASE                  0x50040600UL
#define RTC_BASE                    0x50000400UL
#define SDADC_BASE                  0x50020800UL
#define SMOTOR_BASE                 0x50030E00UL
#define SNC_BASE                    0x50020C00UL
#define SPI_BASE                    0x50020300UL
#define SPI2_BASE                   0x50020400UL
#define SYS_WDOG_BASE               0x50000700UL
#define TIMER_BASE                  0x50010200UL
#define TIMER2_BASE                 0x50010300UL
#define TIMER3_BASE                 0x50040A00UL
#define TIMER4_BASE                 0x50040B00UL
#define TRNG_BASE                   0x50040C00UL
#define UART_BASE                   0x50020000UL
#define UART2_BASE                  0x50020100UL
#define UART3_BASE                  0x50020200UL
#define USB_BASE                    0x50040000UL
#define WAKEUP_BASE                 0x50000100UL


/* =========================================================================================================================== */
/* ====================外围声明====================*/
/* =========================================================================================================================== */


#define AES_HASH                    ((AES_HASH_Type*)          AES_HASH_BASE)
#define ANAMISC_BIF                 ((ANAMISC_BIF_Type*)       ANAMISC_BIF_BASE)
#define APU                         ((APU_Type*)               APU_BASE)
#define CACHE                       ((CACHE_Type*)             CACHE_BASE)
#define CHARGER                     ((CHARGER_Type*)           CHARGER_BASE)
#define CHIP_VERSION                ((CHIP_VERSION_Type*)      CHIP_VERSION_BASE)
#define CRG_COM                     ((CRG_COM_Type*)           CRG_COM_BASE)
#define CRG_PER                     ((CRG_PER_Type*)           CRG_PER_BASE)
#define CRG_SYS                     ((CRG_SYS_Type*)           CRG_SYS_BASE)
#define CRG_TOP                     ((CRG_TOP_Type*)           CRG_TOP_BASE)
#define CRG_XTAL                    ((CRG_XTAL_Type*)          CRG_XTAL_BASE)
#define DCDC                        ((DCDC_Type*)              DCDC_BASE)
#define DMA                         ((DMA_Type*)               DMA_BASE)
#define DW                          ((DW_Type*)                DW_BASE)
#define GPADC                       ((GPADC_Type*)             GPADC_BASE)
#define GPIO                        ((GPIO_Type*)              GPIO_BASE)
#define GPREG                       ((GPREG_Type*)             GPREG_BASE)
#define I2C                         ((I2C_Type*)               I2C_BASE)
#define I2C2                        ((I2C2_Type*)              I2C2_BASE)
#define LCDC                        ((LCDC_Type*)              LCDC_BASE)
#define LRA                         ((LRA_Type*)               LRA_BASE)
#define MEMCTRL                     ((MEMCTRL_Type*)           MEMCTRL_BASE)
#define OTPC                        ((OTPC_Type*)              OTPC_BASE)
#define PDC                         ((PDC_Type*)               PDC_BASE)
#define PWMLED                      ((PWMLED_Type*)            PWMLED_BASE)
#define QSPIC                       ((QSPIC_Type*)             QSPIC_BASE)
#define QSPIC2                      ((QSPIC2_Type*)            QSPIC2_BASE)
#define RFMON                       ((RFMON_Type*)             RFMON_BASE)
#define RTC                         ((RTC_Type*)               RTC_BASE)
#define SDADC                       ((SDADC_Type*)             SDADC_BASE)
#define SMOTOR                      ((SMOTOR_Type*)            SMOTOR_BASE)
#define SNC                         ((SNC_Type*)               SNC_BASE)
#define SPI                         ((SPI_Type*)               SPI_BASE)
#define SPI2                        ((SPI2_Type*)              SPI2_BASE)
#define SYS_WDOG                    ((SYS_WDOG_Type*)          SYS_WDOG_BASE)
#define TIMER                       ((TIMER_Type*)             TIMER_BASE)
#define TIMER2                      ((TIMER2_Type*)            TIMER2_BASE)
#define TIMER3                      ((TIMER3_Type*)            TIMER3_BASE)
#define TIMER4                      ((TIMER4_Type*)            TIMER4_BASE)
#define TRNG                        ((TRNG_Type*)              TRNG_BASE)
#define UART                        ((UART_Type*)              UART_BASE)
#define UART2                       ((UART2_Type*)             UART2_BASE)
#define UART3                       ((UART3_Type*)             UART3_BASE)
#define USB                         ((USB_Type*)               USB_BASE)
#define WAKEUP                      ((WAKEUP_Type*)            WAKEUP_BASE)


/* =========================================================================================================================== */
/* ====================位置/掩码外围部分====================*/
/* =========================================================================================================================== */


/** @addtogroup PosMask_外围@{
  */



/* =========================================================================================================================== */
/* ================                                         AES_HASH                                          ================ */
/* =========================================================================================================================== */

/* ===================================================  CRYPTO_CLRIRQ_REG  =================================================== */
#define AES_HASH_CRYPTO_CLRIRQ_REG_CRYPTO_CLRIRQ_Pos (0UL)          /*!< CRYPTO_CLRIRQ（位0）*/
#define AES_HASH_CRYPTO_CLRIRQ_REG_CRYPTO_CLRIRQ_Msk (0x1UL)        /*!< CRYPTO_CLRIRQ（位字段掩码：0x01）*/
/* ====================================================  CRYPTO_CTRL_REG  ==================================================== */
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_AES_KEXP_Pos (17UL)         /*!< CRYPTO_AES_KEXP（位17）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_AES_KEXP_Msk (0x20000UL)    /*!< CRYPTO_AES_KEXP（位域掩码：0x01）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_MORE_IN_Pos (16UL)          /*!< CRYPTO_MORE_IN（位16）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_MORE_IN_Msk (0x10000UL)     /*!< CRYPTO_MORE_IN（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_HASH_OUT_LEN_Pos (10UL)     /*!< CRYPTO_HASH_OUT_LEN（位10）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_HASH_OUT_LEN_Msk (0xfc00UL) /*!< CRYPTO_HASH_OUT_LEN（位域掩码：0x3f）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_HASH_SEL_Pos (9UL)          /*!< CRYPTO_HASH_SEL（第9位）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_HASH_SEL_Msk (0x200UL)      /*!< CRYPTO_HASH_SEL（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_IRQ_EN_Pos (8UL)            /*!< CRYPTO_IRQ_EN（位8）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_IRQ_EN_Msk (0x100UL)        /*!< CRYPTO_IRQ_EN（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_ENCDEC_Pos (7UL)            /*!< CRYPTO_ENCDEC（第7位）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_ENCDEC_Msk (0x80UL)         /*!< CRYPTO_ENCDEC（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_AES_KEY_SZ_Pos (5UL)        /*!< CRYPTO_AES_KEY_SZ（位5）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_AES_KEY_SZ_Msk (0x60UL)     /*!< CRYPTO_AES_KEY_SZ（位域掩码：0x03）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_OUT_MD_Pos (4UL)            /*!< CRYPTO_OUT_MD（位4）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_OUT_MD_Msk (0x10UL)         /*!< CRYPTO_OUT_MD（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_ALG_MD_Pos (2UL)            /*!< CRYPTO_ALG_MD（位2）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_ALG_MD_Msk (0xcUL)          /*!< CRYPTO_ALG_MD（位字段掩码：0x03）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_ALG_Pos (0UL)               /*!< CRYPTO_ALG（位0）*/
#define AES_HASH_CRYPTO_CTRL_REG_CRYPTO_ALG_Msk (0x3UL)             /*!< CRYPTO_ALG（位域掩码：0x03）*/
/* =================================================  CRYPTO_DEST_ADDR_REG  ================================================== */
#define AES_HASH_CRYPTO_DEST_ADDR_REG_CRYPTO_DEST_ADDR_Pos (0UL)    /*!< CRYPTO_DEST_ADDR（位0）*/
#define AES_HASH_CRYPTO_DEST_ADDR_REG_CRYPTO_DEST_ADDR_Msk (0xffffffffUL) /*!< CRYPTO_DEST_ADDR（位字段掩码：0xffffff）*/
/* =================================================  CRYPTO_FETCH_ADDR_REG  ================================================= */
#define AES_HASH_CRYPTO_FETCH_ADDR_REG_CRYPTO_FETCH_ADDR_Pos (0UL)  /*!< CRYPTO_FETCH_ADDR（位0）*/
#define AES_HASH_CRYPTO_FETCH_ADDR_REG_CRYPTO_FETCH_ADDR_Msk (0xffffffffUL) /*!< CRYPTO_FETCH_ADDR（位字段掩码：0xffffff）*/
/* ===================================================  CRYPTO_KEYS_START  =================================================== */
#define AES_HASH_CRYPTO_KEYS_START_CRYPTO_KEY_X_Pos (0UL)           /*!< CRYPTO_KEY_X（位0）*/
#define AES_HASH_CRYPTO_KEYS_START_CRYPTO_KEY_X_Msk (0xffffffffUL)  /*!< CRYPTO_KEY_X（位域掩码：0xffffffff）*/
/* ====================================================  CRYPTO_LEN_REG  ===================================================== */
#define AES_HASH_CRYPTO_LEN_REG_CRYPTO_LEN_Pos (0UL)                /*!< CRYPTO_LEN（位0）*/
#define AES_HASH_CRYPTO_LEN_REG_CRYPTO_LEN_Msk (0xffffffUL)         /*!< CRYPTO_LEN（位域掩码：0xffffff）*/
/* ===================================================  CRYPTO_MREG0_REG  ==================================================== */
#define AES_HASH_CRYPTO_MREG0_REG_CRYPTO_MREG0_Pos (0UL)            /*!< CRYPTO_MREG0（位0）*/
#define AES_HASH_CRYPTO_MREG0_REG_CRYPTO_MREG0_Msk (0xffffffffUL)   /*!< CRYPTO_MREG0（位域掩码：0xffffff）*/
/* ===================================================  CRYPTO_MREG1_REG  ==================================================== */
#define AES_HASH_CRYPTO_MREG1_REG_CRYPTO_MREG1_Pos (0UL)            /*!< CRYPTO_MREG1（位0）*/
#define AES_HASH_CRYPTO_MREG1_REG_CRYPTO_MREG1_Msk (0xffffffffUL)   /*!< CRYPTO_MREG1（位域掩码：0xffffff）*/
/* ===================================================  CRYPTO_MREG2_REG  ==================================================== */
#define AES_HASH_CRYPTO_MREG2_REG_CRYPTO_MREG2_Pos (0UL)            /*!< CRYPTO_MREG2（位0）*/
#define AES_HASH_CRYPTO_MREG2_REG_CRYPTO_MREG2_Msk (0xffffffffUL)   /*!< CRYPTO_MREG2（位域掩码：0xffffff）*/
/* ===================================================  CRYPTO_MREG3_REG  ==================================================== */
#define AES_HASH_CRYPTO_MREG3_REG_CRYPTO_MREG3_Pos (0UL)            /*!< CRYPTO_MREG3（位0）*/
#define AES_HASH_CRYPTO_MREG3_REG_CRYPTO_MREG3_Msk (0xffffffffUL)   /*!< CRYPTO_MREG3（位域掩码：0xffffff）*/
/* ===================================================  CRYPTO_START_REG  ==================================================== */
#define AES_HASH_CRYPTO_START_REG_CRYPTO_START_Pos (0UL)            /*!< CRYPTO_START（位0）*/
#define AES_HASH_CRYPTO_START_REG_CRYPTO_START_Msk (0x1UL)          /*!< CRYPTO_START（位字段掩码：0x01）*/
/* ===================================================  CRYPTO_STATUS_REG  =================================================== */
#define AES_HASH_CRYPTO_STATUS_REG_CRYPTO_IRQ_ST_Pos (2UL)          /*!< CRYPTO_IRQ_ST（位2）*/
#define AES_HASH_CRYPTO_STATUS_REG_CRYPTO_IRQ_ST_Msk (0x4UL)        /*!< CRYPTO_IRQ_ST（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_STATUS_REG_CRYPTO_WAIT_FOR_IN_Pos (1UL)     /*!< CRYPTO_WAIT_FOR_IN（位1）*/
#define AES_HASH_CRYPTO_STATUS_REG_CRYPTO_WAIT_FOR_IN_Msk (0x2UL)   /*!< CRYPTO_WAIT_FOR_IN（位字段掩码：0x01）*/
#define AES_HASH_CRYPTO_STATUS_REG_CRYPTO_INACTIVE_Pos (0UL)        /*!< CRYPTO_INACTIVE（位0）*/
#define AES_HASH_CRYPTO_STATUS_REG_CRYPTO_INACTIVE_Msk (0x1UL)      /*!< CRYPTO_INACTIVE（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                        ANAMISC_BIF                                        ================ */
/* =========================================================================================================================== */

/* ====================================================  CLK_REF_CNT_REG  ==================================================== */
#define ANAMISC_BIF_CLK_REF_CNT_REG_REF_CNT_VAL_Pos (0UL)           /*!< REF_CNT_VAL（位0）*/
#define ANAMISC_BIF_CLK_REF_CNT_REG_REF_CNT_VAL_Msk (0xffffUL)      /*!< REF_CNT_VAL（位域掩码：0xffff）*/
/* ====================================================  CLK_REF_SEL_REG  ==================================================== */
#define ANAMISC_BIF_CLK_REF_SEL_REG_CAL_CLK_SEL_Pos (5UL)           /*!< CAL_CLK_SEL（位5）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_CAL_CLK_SEL_Msk (0xe0UL)        /*!< CAL_CLK_SEL（位字段掩码：0x07）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_EXT_CNT_EN_SEL_Pos (4UL)        /*!< EXT_CNT_EN_SEL（位4）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_EXT_CNT_EN_SEL_Msk (0x10UL)     /*!< EXT_CNT_EN_SEL（位域掩码：0x01）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_REF_CAL_START_Pos (3UL)         /*!< REF_CAL_START（位3）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_REF_CAL_START_Msk (0x8UL)       /*!< REF_CAL_START（位字段掩码：0x01）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_REF_CLK_SEL_Pos (0UL)           /*!< REF_CLK_SEL（位0）*/
#define ANAMISC_BIF_CLK_REF_SEL_REG_REF_CLK_SEL_Msk (0x7UL)         /*!< REF_CLK_SEL（位字段掩码：0x07）*/
/* ====================================================  CLK_REF_VAL_REG  ==================================================== */
#define ANAMISC_BIF_CLK_REF_VAL_REG_XTAL_CNT_VAL_Pos (0UL)          /*!< XTAL_CNT_VAL（位0）*/
#define ANAMISC_BIF_CLK_REF_VAL_REG_XTAL_CNT_VAL_Msk (0xffffffffUL) /*!< XTAL_CNT_VAL（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                            APU                                            ================ */
/* =========================================================================================================================== */

/* ======================================================  APU_MUX_REG  ====================================================== */
#define APU_APU_MUX_REG_PDM1_MUX_IN_Pos   (6UL)                     /*!< PDM1_MUX_IN（位6）*/
#define APU_APU_MUX_REG_PDM1_MUX_IN_Msk   (0x40UL)                  /*!< PDM1_MUX_IN（位域掩码：0x01）*/
#define APU_APU_MUX_REG_PCM1_MUX_IN_Pos   (3UL)                     /*!< PCM1_MUX_IN（位3）*/
#define APU_APU_MUX_REG_PCM1_MUX_IN_Msk   (0x38UL)                  /*!< PCM1_MUX_IN（位字段掩码：0x07）*/
#define APU_APU_MUX_REG_SRC1_MUX_IN_Pos   (0UL)                     /*!< SRC1_MUX_IN（位0）*/
#define APU_APU_MUX_REG_SRC1_MUX_IN_Msk   (0x7UL)                   /*!< SRC1_MUX_IN（位域掩码：0x07）*/
/* ====================================================  COEF0A_SET1_REG  ==================================================== */
#define APU_COEF0A_SET1_REG_SRC_COEF10_Pos (0UL)                    /*!< SRC_COEF10（位0）*/
#define APU_COEF0A_SET1_REG_SRC_COEF10_Msk (0xffffUL)               /*!< SRC_COEF10（位域掩码：0xffff）*/
/* ====================================================  COEF10_SET1_REG  ==================================================== */
#define APU_COEF10_SET1_REG_SRC_COEF1_Pos (16UL)                    /*!< SRC_COEF1（位16）*/
#define APU_COEF10_SET1_REG_SRC_COEF1_Msk (0xffff0000UL)            /*!< SRC_COEF1（位域掩码：0xffff）*/
#define APU_COEF10_SET1_REG_SRC_COEF0_Pos (0UL)                     /*!< SRC_COEF0（位0）*/
#define APU_COEF10_SET1_REG_SRC_COEF0_Msk (0xffffUL)                /*!< SRC_COEF0（位域掩码：0xffff）*/
/* ====================================================  COEF32_SET1_REG  ==================================================== */
#define APU_COEF32_SET1_REG_SRC_COEF3_Pos (16UL)                    /*!< SRC_COEF3（位16）*/
#define APU_COEF32_SET1_REG_SRC_COEF3_Msk (0xffff0000UL)            /*!< SRC_COEF3（位域掩码：0xffff）*/
#define APU_COEF32_SET1_REG_SRC_COEF2_Pos (0UL)                     /*!< SRC_COEF2（位0）*/
#define APU_COEF32_SET1_REG_SRC_COEF2_Msk (0xffffUL)                /*!< SRC_COEF2（位域掩码：0xffff）*/
/* ====================================================  COEF54_SET1_REG  ==================================================== */
#define APU_COEF54_SET1_REG_SRC_COEF5_Pos (16UL)                    /*!< SRC_COEF5（位16）*/
#define APU_COEF54_SET1_REG_SRC_COEF5_Msk (0xffff0000UL)            /*!< SRC_COEF5（位域掩码：0xffff）*/
#define APU_COEF54_SET1_REG_SRC_COEF4_Pos (0UL)                     /*!< SRC_COEF4（位0）*/
#define APU_COEF54_SET1_REG_SRC_COEF4_Msk (0xffffUL)                /*!< SRC_COEF4（位域掩码：0xffff）*/
/* ====================================================  COEF76_SET1_REG  ==================================================== */
#define APU_COEF76_SET1_REG_SRC_COEF7_Pos (16UL)                    /*!< SRC_COEF7（位16）*/
#define APU_COEF76_SET1_REG_SRC_COEF7_Msk (0xffff0000UL)            /*!< SRC_COEF7（位域掩码：0xffff）*/
#define APU_COEF76_SET1_REG_SRC_COEF6_Pos (0UL)                     /*!< SRC_COEF6（位0）*/
#define APU_COEF76_SET1_REG_SRC_COEF6_Msk (0xffffUL)                /*!< SRC_COEF6（位域掩码：0xffff）*/
/* ====================================================  COEF98_SET1_REG  ==================================================== */
#define APU_COEF98_SET1_REG_SRC_COEF9_Pos (16UL)                    /*!< SRC_COEF9（位16）*/
#define APU_COEF98_SET1_REG_SRC_COEF9_Msk (0xffff0000UL)            /*!< SRC_COEF9（位域掩码：0xffff）*/
#define APU_COEF98_SET1_REG_SRC_COEF8_Pos (0UL)                     /*!< SRC_COEF8（位0）*/
#define APU_COEF98_SET1_REG_SRC_COEF8_Msk (0xffffUL)                /*!< SRC_COEF8（位域掩码：0xffff）*/
/* =====================================================  PCM1_CTRL_REG  ===================================================== */
#define APU_PCM1_CTRL_REG_PCM_FSC_DIV_Pos (20UL)                    /*!< PCM_FSC_DIV（位20）*/
#define APU_PCM1_CTRL_REG_PCM_FSC_DIV_Msk (0xfff00000UL)            /*!< PCM_FSC_DIV（位字段掩码：0xfff）*/
#define APU_PCM1_CTRL_REG_PCM_FSC_EDGE_Pos (16UL)                   /*!< PCM_FSC_EDGE（位16）*/
#define APU_PCM1_CTRL_REG_PCM_FSC_EDGE_Msk (0x10000UL)              /*!< PCM_FSC_EDGE（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_CH_DEL_Pos  (11UL)                    /*!< PCM_CH_DEL（位11）*/
#define APU_PCM1_CTRL_REG_PCM_CH_DEL_Msk  (0xf800UL)                /*!< PCM_CH_DEL（位场掩码：0x1f）*/
#define APU_PCM1_CTRL_REG_PCM_CLK_BIT_Pos (10UL)                    /*!< PCM_CLK_BIT（位10）*/
#define APU_PCM1_CTRL_REG_PCM_CLK_BIT_Msk (0x400UL)                 /*!< PCM_CLK_BIT（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_FSCINV_Pos  (9UL)                     /*!< PCM_FSCINV（位9）*/
#define APU_PCM1_CTRL_REG_PCM_FSCINV_Msk  (0x200UL)                 /*!< PCM_FSCINV（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_CLKINV_Pos  (8UL)                     /*!< PCM_CLKINV（位8）*/
#define APU_PCM1_CTRL_REG_PCM_CLKINV_Msk  (0x100UL)                 /*!< PCM_CLKINV（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_PPOD_Pos    (7UL)                     /*!< PCM_PPOD（位7）*/
#define APU_PCM1_CTRL_REG_PCM_PPOD_Msk    (0x80UL)                  /*!< PCM_PPOD（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_FSCDEL_Pos  (6UL)                     /*!< PCM_FSCDEL（位6）*/
#define APU_PCM1_CTRL_REG_PCM_FSCDEL_Msk  (0x40UL)                  /*!< PCM_FSCDEL（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_FSCLEN_Pos  (2UL)                     /*!< PCM_FSCLEN（位2）*/
#define APU_PCM1_CTRL_REG_PCM_FSCLEN_Msk  (0x3cUL)                  /*!< PCM_FSCLEN（位字段掩码：0x0f）*/
#define APU_PCM1_CTRL_REG_PCM_MASTER_Pos  (1UL)                     /*!< PCM_MASTER（位1）*/
#define APU_PCM1_CTRL_REG_PCM_MASTER_Msk  (0x2UL)                   /*!< PCM_MASTER（位字段掩码：0x01）*/
#define APU_PCM1_CTRL_REG_PCM_EN_Pos      (0UL)                     /*!< PCM_EN（位0）*/
#define APU_PCM1_CTRL_REG_PCM_EN_Msk      (0x1UL)                   /*!< PCM_EN（位域掩码：0x01）*/
/* =====================================================  PCM1_IN1_REG  ====================================================== */
#define APU_PCM1_IN1_REG_PCM_IN_Pos       (0UL)                     /*!< PCM_IN（位0）*/
#define APU_PCM1_IN1_REG_PCM_IN_Msk       (0xffffffffUL)            /*!< PCM_IN（位字段掩码：0xffffffff）*/
/* =====================================================  PCM1_IN2_REG  ====================================================== */
#define APU_PCM1_IN2_REG_PCM_IN_Pos       (0UL)                     /*!< PCM_IN（位0）*/
#define APU_PCM1_IN2_REG_PCM_IN_Msk       (0xffffffffUL)            /*!< PCM_IN（位字段掩码：0xffffffff）*/
/* =====================================================  PCM1_OUT1_REG  ===================================================== */
#define APU_PCM1_OUT1_REG_PCM_OUT_Pos     (0UL)                     /*!< PCM_OUT（位0）*/
#define APU_PCM1_OUT1_REG_PCM_OUT_Msk     (0xffffffffUL)            /*!< PCM_OUT（位字段掩码：0xffffffff）*/
/* =====================================================  PCM1_OUT2_REG  ===================================================== */
#define APU_PCM1_OUT2_REG_PCM_OUT_Pos     (0UL)                     /*!< PCM_OUT（位0）*/
#define APU_PCM1_OUT2_REG_PCM_OUT_Msk     (0xffffffffUL)            /*!< PCM_OUT（位字段掩码：0xffffffff）*/
/* =====================================================  SRC1_CTRL_REG  ===================================================== */
#define APU_SRC1_CTRL_REG_SRC_PDM_DO_DEL_Pos (30UL)                 /*!< SRC_PDM_DO_DEL（位30）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_DO_DEL_Msk (0xc0000000UL)         /*!< SRC_PDM_DO_DEL（位字段掩码：0x03）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_MODE_Pos (28UL)                   /*!< SRC_PDM_MODE（位28）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_MODE_Msk (0x30000000UL)           /*!< SRC_PDM_MODE（位字段掩码：0x03）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_DI_DEL_Pos (26UL)                 /*!< SRC_PDM_DI_DEL（位26）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_DI_DEL_Msk (0xc000000UL)          /*!< SRC_PDM_DI_DEL（位字段掩码：0x03）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_FLOWCLR_Pos (25UL)                /*!< SRC_OUT_FLOWCLR（位25）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_FLOWCLR_Msk (0x2000000UL)         /*!< SRC_OUT_FLOWCLR（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_FLOWCLR_Pos (24UL)                 /*!< SRC_IN_FLOWCLR（位24）*/
#define APU_SRC1_CTRL_REG_SRC_IN_FLOWCLR_Msk (0x1000000UL)          /*!< SRC_IN_FLOWCLR（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_UNFLOW_Pos (23UL)                 /*!< SRC_OUT_UNFLOW（位23）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_UNFLOW_Msk (0x800000UL)           /*!< SRC_OUT_UNFLOW（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_OVFLOW_Pos (22UL)                 /*!< SRC_OUT_OVFLOW（位22）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_OVFLOW_Msk (0x400000UL)           /*!< SRC_OUT_OVFLOW（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_UNFLOW_Pos (21UL)                  /*!< SRC_IN_UNFLOW（第21位）*/
#define APU_SRC1_CTRL_REG_SRC_IN_UNFLOW_Msk (0x200000UL)            /*!< SRC_IN_UNFLOW（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_OVFLOW_Pos (20UL)                  /*!< SRC_IN_OVFLOW（位20）*/
#define APU_SRC1_CTRL_REG_SRC_IN_OVFLOW_Msk (0x100000UL)            /*!< SRC_IN_OVFLOW（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_RESYNC_Pos  (19UL)                    /*!< SRC_RESYNC（位19）*/
#define APU_SRC1_CTRL_REG_SRC_RESYNC_Msk  (0x80000UL)               /*!< SRC_RESYNC（位域掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_OK_Pos  (18UL)                    /*!< SRC_OUT_OK（位18）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_OK_Msk  (0x40000UL)               /*!< SRC_OUT_OK（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_US_Pos  (16UL)                    /*!< SRC_OUT_US（位16）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_US_Msk  (0x30000UL)               /*!< SRC_OUT_US（位字段掩码：0x03）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_CAL_BYPASS_Pos (14UL)             /*!< SRC_OUT_CAL_BYPASS（位14）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_CAL_BYPASS_Msk (0x4000UL)         /*!< SRC_OUT_CAL_BYPASS（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_AMODE_Pos (13UL)                  /*!< SRC_OUT_AMODE（位13）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_AMODE_Msk (0x2000UL)              /*!< SRC_OUT_AMODE（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_OUT_INV_Pos (12UL)                /*!< SRC_PDM_OUT_INV（位12）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_OUT_INV_Msk (0x1000UL)            /*!< SRC_PDM_OUT_INV（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_FIFO_DIRECTION_Pos (11UL)             /*!< SRC_FIFO_DIRECTION（位11）*/
#define APU_SRC1_CTRL_REG_SRC_FIFO_DIRECTION_Msk (0x800UL)          /*!< SRC_FIFO_DIRECTION（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_FIFO_ENABLE_Pos (10UL)                /*!< SRC_FIFO_ENABLE（位10）*/
#define APU_SRC1_CTRL_REG_SRC_FIFO_ENABLE_Msk (0x400UL)             /*!< SRC_FIFO_ENABLE（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_DSD_MODE_Pos (9UL)                /*!< SRC_OUT_DSD_MODE（第9位）*/
#define APU_SRC1_CTRL_REG_SRC_OUT_DSD_MODE_Msk (0x200UL)            /*!< SRC_OUT_DSD_MODE（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_DSD_MODE_Pos (8UL)                 /*!< SRC_IN_DSD_MODE（位8）*/
#define APU_SRC1_CTRL_REG_SRC_IN_DSD_MODE_Msk (0x100UL)             /*!< SRC_IN_DSD_MODE（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_DITHER_DISABLE_Pos (7UL)              /*!< SRC_DITHER_DISABLE（位7）*/
#define APU_SRC1_CTRL_REG_SRC_DITHER_DISABLE_Msk (0x80UL)           /*!< SRC_DITHER_DISABLE（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_OK_Pos   (6UL)                     /*!< SRC_IN_OK（位6）*/
#define APU_SRC1_CTRL_REG_SRC_IN_OK_Msk   (0x40UL)                  /*!< SRC_IN_OK（位域掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_DS_Pos   (4UL)                     /*!< SRC_IN_DS（位4）*/
#define APU_SRC1_CTRL_REG_SRC_IN_DS_Msk   (0x30UL)                  /*!< SRC_IN_DS（位域掩码：0x03）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_IN_INV_Pos (3UL)                  /*!< SRC_PDM_IN_INV（位3）*/
#define APU_SRC1_CTRL_REG_SRC_PDM_IN_INV_Msk (0x8UL)                /*!< SRC_PDM_IN_INV（位字段掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_CAL_BYPASS_Pos (2UL)               /*!< SRC_IN_CAL_BYPASS（位2）*/
#define APU_SRC1_CTRL_REG_SRC_IN_CAL_BYPASS_Msk (0x4UL)             /*!< SRC_IN_CAL_BYPASS（位域掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_IN_AMODE_Pos (1UL)                    /*!< SRC_IN_AMODE（位1）*/
#define APU_SRC1_CTRL_REG_SRC_IN_AMODE_Msk (0x2UL)                  /*!< SRC_IN_AMODE（位域掩码：0x01）*/
#define APU_SRC1_CTRL_REG_SRC_EN_Pos      (0UL)                     /*!< SRC_EN（位0）*/
#define APU_SRC1_CTRL_REG_SRC_EN_Msk      (0x1UL)                   /*!< SRC_EN（位域掩码：0x01）*/
/* =====================================================  SRC1_IN1_REG  ====================================================== */
#define APU_SRC1_IN1_REG_SRC_IN_Pos       (0UL)                     /*!< SRC_IN（位0）*/
#define APU_SRC1_IN1_REG_SRC_IN_Msk       (0xffffffffUL)            /*!< SRC_IN（位域掩码：0xffffffff）*/
/* =====================================================  SRC1_IN2_REG  ====================================================== */
#define APU_SRC1_IN2_REG_SRC_IN_Pos       (0UL)                     /*!< SRC_IN（位0）*/
#define APU_SRC1_IN2_REG_SRC_IN_Msk       (0xffffffffUL)            /*!< SRC_IN（位域掩码：0xffffffff）*/
/* ====================================================  SRC1_IN_FS_REG  ===================================================== */
#define APU_SRC1_IN_FS_REG_SRC_IN_FS_Pos  (0UL)                     /*!< SRC_IN_FS（位0）*/
#define APU_SRC1_IN_FS_REG_SRC_IN_FS_Msk  (0xffffffUL)              /*!< SRC_IN_FS（位域掩码：0xffffff）*/
/* =====================================================  SRC1_OUT1_REG  ===================================================== */
#define APU_SRC1_OUT1_REG_SRC_OUT_Pos     (0UL)                     /*!< SRC_OUT（位0）*/
#define APU_SRC1_OUT1_REG_SRC_OUT_Msk     (0xffffffffUL)            /*!< SRC_OUT（位域掩码：0xffffffff）*/
/* =====================================================  SRC1_OUT2_REG  ===================================================== */
#define APU_SRC1_OUT2_REG_SRC_OUT_Pos     (0UL)                     /*!< SRC_OUT（位0）*/
#define APU_SRC1_OUT2_REG_SRC_OUT_Msk     (0xffffffffUL)            /*!< SRC_OUT（位域掩码：0xffffffff）*/
/* ====================================================  SRC1_OUT_FS_REG  ==================================================== */
#define APU_SRC1_OUT_FS_REG_SRC_OUT_FS_Pos (0UL)                    /*!< SRC_OUT_FS（位0）*/
#define APU_SRC1_OUT_FS_REG_SRC_OUT_FS_Msk (0xffffffUL)             /*!< SRC_OUT_FS（位域掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                           CACHE                                           ================ */
/* =========================================================================================================================== */

/* ==================================================  CACHE_ASSOCCFG_REG  =================================================== */
#define CACHE_CACHE_ASSOCCFG_REG_CACHE_ASSOC_Pos (0UL)              /*!< CACHE_ASSOC（位0）*/
#define CACHE_CACHE_ASSOCCFG_REG_CACHE_ASSOC_Msk (0x3UL)            /*!< CACHE_ASSOC（位域掩码：0x03）*/
/* ====================================================  CACHE_CTRL1_REG  ==================================================== */
#define CACHE_CACHE_CTRL1_REG_CACHE_RES1_Pos (1UL)                  /*!< CACHE_RES1（位1）*/
#define CACHE_CACHE_CTRL1_REG_CACHE_RES1_Msk (0x2UL)                /*!< CACHE_RES1（位字段掩码：0x01）*/
#define CACHE_CACHE_CTRL1_REG_CACHE_FLUSH_Pos (0UL)                 /*!< CACHE_FLUSH（位0）*/
#define CACHE_CACHE_CTRL1_REG_CACHE_FLUSH_Msk (0x1UL)               /*!< CACHE_FLUSH（位字段掩码：0x01）*/
/* ====================================================  CACHE_CTRL2_REG  ==================================================== */
#define CACHE_CACHE_CTRL2_REG_CACHE_CGEN_Pos (10UL)                 /*!< CACHE_CGEN（位10）*/
#define CACHE_CACHE_CTRL2_REG_CACHE_CGEN_Msk (0x400UL)              /*!< CACHE_CGEN（位字段掩码：0x01）*/
#define CACHE_CACHE_CTRL2_REG_CACHE_WEN_Pos (9UL)                   /*!< CACHE_WEN（第9位）*/
#define CACHE_CACHE_CTRL2_REG_CACHE_WEN_Msk (0x200UL)               /*!< CACHE_WEN（位字段掩码：0x01）*/
#define CACHE_CACHE_CTRL2_REG_CACHE_LEN_Pos (0UL)                   /*!< CACHE_LEN（位0）*/
#define CACHE_CACHE_CTRL2_REG_CACHE_LEN_Msk (0x1ffUL)               /*!< CACHE_LEN（位域掩码：0x1ff）*/
/* ====================================================  CACHE_FLASH_REG  ==================================================== */
#define CACHE_CACHE_FLASH_REG_FLASH_REGION_BASE_Pos (16UL)          /*!< FLASH_REGION_BASE（位16）*/
#define CACHE_CACHE_FLASH_REG_FLASH_REGION_BASE_Msk (0xffff0000UL)  /*!< FLASH_REGION_BASE（位字段掩码：0xffff）*/
#define CACHE_CACHE_FLASH_REG_FLASH_REGION_OFFSET_Pos (4UL)         /*!< FLASH_REGION_OFFSET（位4）*/
#define CACHE_CACHE_FLASH_REG_FLASH_REGION_OFFSET_Msk (0xfff0UL)    /*!< FLASH_REGION_OFFSET（位字段掩码：0xfff）*/
#define CACHE_CACHE_FLASH_REG_FLASH_REGION_SIZE_Pos (0UL)           /*!< FLASH_REGION_SIZE（位0）*/
#define CACHE_CACHE_FLASH_REG_FLASH_REGION_SIZE_Msk (0x7UL)         /*!< FLASH_REGION_SIZE（位字段掩码：0x07）*/
/* ==================================================  CACHE_LNSIZECFG_REG  ================================================== */
#define CACHE_CACHE_LNSIZECFG_REG_CACHE_LINE_Pos (0UL)              /*!< CACHE_LINE（位0）*/
#define CACHE_CACHE_LNSIZECFG_REG_CACHE_LINE_Msk (0x3UL)            /*!< CACHE_LINE（位字段掩码：0x03）*/
/* ==================================================  CACHE_MRM_CTRL_REG  =================================================== */
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_HITS_THRES_STATUS_Pos (4UL) /*!< MRM_IRQ_HITS_THRES_STATUS（位4）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_HITS_THRES_STATUS_Msk (0x10UL) /*!< MRM_IRQ_HITS_THRES_STATUS（位字段掩码：0x01）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_MISSES_THRES_STATUS_Pos (3UL) /*!< MRM_IRQ_MISSES_THRES_STATUS（位3）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_MISSES_THRES_STATUS_Msk (0x8UL) /*!< MRM_IRQ_MISSES_THRES_STATUS（位字段掩码：0x01）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_TINT_STATUS_Pos (2UL)      /*!< MRM_IRQ_TINT_STATUS（位2）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_TINT_STATUS_Msk (0x4UL)    /*!< MRM_IRQ_TINT_STATUS（位字段掩码：0x01）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_MASK_Pos (1UL)             /*!< MRM_IRQ_MASK（位1）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_IRQ_MASK_Msk (0x2UL)           /*!< MRM_IRQ_MASK（位域掩码：0x01）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_START_Pos (0UL)                /*!< MRM_START（位0）*/
#define CACHE_CACHE_MRM_CTRL_REG_MRM_START_Msk (0x1UL)              /*!< MRM_START（位域掩码：0x01）*/
/* ==================================================  CACHE_MRM_HITS_REG  =================================================== */
#define CACHE_CACHE_MRM_HITS_REG_MRM_HITS_Pos (0UL)                 /*!< MRM_HITS（位0）*/
#define CACHE_CACHE_MRM_HITS_REG_MRM_HITS_Msk (0xffffffffUL)        /*!< MRM_HITS（位域掩码：0xffffffff）*/
/* ===============================================  CACHE_MRM_HITS_THRES_REG  ================================================ */
#define CACHE_CACHE_MRM_HITS_THRES_REG_MRM_HITS_THRES_Pos (0UL)     /*!< MRM_HITS_TRES（位0）*/
#define CACHE_CACHE_MRM_HITS_THRES_REG_MRM_HITS_THRES_Msk (0xffffffffUL) /*!< MRM_HITS_TRES（位域掩码：0xffffffff）*/
/* =================================================  CACHE_MRM_MISSES_REG  ================================================== */
#define CACHE_CACHE_MRM_MISSES_REG_MRM_MISSES_Pos (0UL)             /*!< MRM_MISSES（位0）*/
#define CACHE_CACHE_MRM_MISSES_REG_MRM_MISSES_Msk (0xffffffffUL)    /*!< MRM_MISSES（位域掩码：0xffffffff）*/
/* ==============================================  CACHE_MRM_MISSES_THRES_REG  =============================================== */
#define CACHE_CACHE_MRM_MISSES_THRES_REG_MRM_MISSES_THRES_Pos (0UL) /*!< MRM_MISSES_THRES（位0）*/
#define CACHE_CACHE_MRM_MISSES_THRES_REG_MRM_MISSES_THRES_Msk (0xffffffffUL) /*!< MRM_MISSES_THRES（位字段掩码：0xffffff）*/
/* ==================================================  CACHE_MRM_TINT_REG  =================================================== */
#define CACHE_CACHE_MRM_TINT_REG_MRM_TINT_Pos (0UL)                 /*!< MRM_TINT（位0）*/
#define CACHE_CACHE_MRM_TINT_REG_MRM_TINT_Msk (0x7ffffUL)           /*!< MRM_TINT（位域掩码：0x7ffff）*/
/* =====================================================  SWD_RESET_REG  ===================================================== */
#define CACHE_SWD_RESET_REG_SWD_HW_RESET_REQ_Pos (0UL)              /*!< SWD_HW_RESET_REQ（位0）*/
#define CACHE_SWD_RESET_REG_SWD_HW_RESET_REQ_Msk (0x1UL)            /*!< SWD_HW_RESET_REQ（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                          CHARGER                                          ================ */
/* =========================================================================================================================== */

/* ==============================================  CHARGER_CC_CHARGE_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_CC_CHARGE_TIMER_REG_CC_CHARGE_TIMER_Pos (16UL) /*!< CC_CHARGE_TIMER（位16）*/
#define CHARGER_CHARGER_CC_CHARGE_TIMER_REG_CC_CHARGE_TIMER_Msk (0x7fff0000UL) /*!< CC_CHARGE_TIMER（位域掩码：0x7fff）*/
#define CHARGER_CHARGER_CC_CHARGE_TIMER_REG_MAX_CC_CHARGE_TIME_Pos (0UL) /*!< MAX_CC_CHARGE_TIME（位0）*/
#define CHARGER_CHARGER_CC_CHARGE_TIMER_REG_MAX_CC_CHARGE_TIME_Msk (0x7fffUL) /*!< MAX_CC_CHARGE_TIME（位域掩码：0x7fff）*/
/* ===================================================  CHARGER_CTRL_REG  ==================================================== */
#define CHARGER_CHARGER_CTRL_REG_EOC_INTERVAL_CHECK_TIMER_Pos (22UL) /*!< EOC_INTERVAL_CHECK_TIMER（位22）*/
#define CHARGER_CHARGER_CTRL_REG_EOC_INTERVAL_CHECK_TIMER_Msk (0xfc00000UL) /*!< EOC_INTERVAL_CHECK_TIMER（位域掩码：0x3f）*/
#define CHARGER_CHARGER_CTRL_REG_EOC_INTERVAL_CHECK_THRES_Pos (16UL) /*!< EOC_INTERVAL_CHECK_THRES（位16）*/
#define CHARGER_CHARGER_CTRL_REG_EOC_INTERVAL_CHECK_THRES_Msk (0x3f0000UL) /*!< EOC_INTERVAL_CHECK_THRES（位域掩码：0x3f）*/
#define CHARGER_CHARGER_CTRL_REG_REPLENISH_MODE_Pos (15UL)          /*!< REPLENISH_MODE（第15位）*/
#define CHARGER_CHARGER_CTRL_REG_REPLENISH_MODE_Msk (0x8000UL)      /*!< REPLENISH_MODE（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_PRE_CHARGE_MODE_Pos (14UL)         /*!< PRE_CHARGE_MODE（位14）*/
#define CHARGER_CHARGER_CTRL_REG_PRE_CHARGE_MODE_Msk (0x4000UL)     /*!< PRE_CHARGE_MODE（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGE_LOOP_HOLD_Pos (13UL)        /*!< CHARGE_LOOP_HOLD（位13）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGE_LOOP_HOLD_Msk (0x2000UL)    /*!< CHARGE_LOOP_HOLD（位域掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_JEITA_SUPPORT_DISABLED_Pos (12UL)  /*!< JEITA_SUPPORT_DISABLED（位12）*/
#define CHARGER_CHARGER_CTRL_REG_JEITA_SUPPORT_DISABLED_Msk (0x1000UL) /*!< JEITA_SUPPORT_DISABLED（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_TBAT_MONITOR_MODE_Pos (10UL)       /*!< TBAT_MONITOR_MODE（位10）*/
#define CHARGER_CHARGER_CTRL_REG_TBAT_MONITOR_MODE_Msk (0xc00UL)    /*!< TBAT_MONITOR_MODE（位字段掩码：0x03）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGE_TIMERS_HALT_ENABLE_Pos (9UL) /*!< CHARGE_TIMERS_HALT_ENABLE（位9）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGE_TIMERS_HALT_ENABLE_Msk (0x200UL) /*!< CHARGE_TIMERS_HALT_ENABLE（位域掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_NTC_LOW_DISABLE_Pos (7UL)          /*!< NTC_LOW_DISABLE（位7）*/
#define CHARGER_CHARGER_CTRL_REG_NTC_LOW_DISABLE_Msk (0x80UL)       /*!< NTC_LOW_DISABLE（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_TBAT_PROT_ENABLE_Pos (6UL)         /*!< TBAT_PROT_ENABLE（位6）*/
#define CHARGER_CHARGER_CTRL_REG_TBAT_PROT_ENABLE_Msk (0x40UL)      /*!< TBAT_PROT_ENABLE（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_TDIE_ERROR_RESUME_Pos (5UL)        /*!< TDIE_ERROR_RESUME（第5位）*/
#define CHARGER_CHARGER_CTRL_REG_TDIE_ERROR_RESUME_Msk (0x20UL)     /*!< TDIE_ERROR_RESUME（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_TDIE_PROT_ENABLE_Pos (4UL)         /*!< TDIE_PROT_ENABLE（位4）*/
#define CHARGER_CHARGER_CTRL_REG_TDIE_PROT_ENABLE_Msk (0x10UL)      /*!< TDIE_PROT_ENABLE（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGER_RESUME_Pos (3UL)           /*!< CHARGER_RESUME（位3）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGER_RESUME_Msk (0x8UL)         /*!< CHARGER_RESUME（位域掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGER_BYPASS_Pos (2UL)           /*!< CHARGER_BYPASS（位2）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGER_BYPASS_Msk (0x4UL)         /*!< CHARGER_BYPASS（位域掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGE_START_Pos (1UL)             /*!< CHARGE_START（位1）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGE_START_Msk (0x2UL)           /*!< CHARGE_START（位域掩码：0x01）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGER_ENABLE_Pos (0UL)           /*!< CHARGER_ENABLE（位0）*/
#define CHARGER_CHARGER_CTRL_REG_CHARGER_ENABLE_Msk (0x1UL)         /*!< CHARGER_ENABLE（位域掩码：0x01）*/
/* ===============================================  CHARGER_CURRENT_PARAM_REG  =============================================== */
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_EOC_DOUBLE_RANGE_Pos (15UL) /*!< I_EOC_DOUBLE_RANGE（位15）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_EOC_DOUBLE_RANGE_Msk (0x8000UL) /*!< I_EOC_DOUBLE_RANGE（位字段掩码：0x01）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_END_OF_CHARGE_Pos (12UL) /*!< I_END_OF_CHARGE（位12）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_END_OF_CHARGE_Msk (0x7000UL) /*!< I_END_OF_CHARGE（位域掩码：0x07）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_PRECHARGE_Pos (6UL)     /*!< I_PRECHARGE（位6）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_PRECHARGE_Msk (0xfc0UL) /*!< I_PRECHARGE（位域掩码：0x3f）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_CHARGE_Pos (0UL)        /*!< I_CHARGE（位0）*/
#define CHARGER_CHARGER_CURRENT_PARAM_REG_I_CHARGE_Msk (0x3fUL)     /*!< I_CHARGE（位域掩码：0x3f）*/
/* ==============================================  CHARGER_CV_CHARGE_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_CV_CHARGE_TIMER_REG_CV_CHARGE_TIMER_Pos (16UL) /*!< CV_CHARGE_TIMER（位16）*/
#define CHARGER_CHARGER_CV_CHARGE_TIMER_REG_CV_CHARGE_TIMER_Msk (0x7fff0000UL) /*!< CV_CHARGE_TIMER（位域掩码：0x7fff）*/
#define CHARGER_CHARGER_CV_CHARGE_TIMER_REG_MAX_CV_CHARGE_TIME_Pos (0UL) /*!< MAX_CV_CHARGE_TIME（位0）*/
#define CHARGER_CHARGER_CV_CHARGE_TIMER_REG_MAX_CV_CHARGE_TIME_Msk (0x7fffUL) /*!< MAX_CV_CHARGE_TIME（位域掩码：0x7fff）*/
/* ===============================================  CHARGER_ERROR_IRQ_CLR_REG  =============================================== */
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_TBAT_ERROR_IRQ_CLR_Pos (6UL) /*!< TBAT_ERROR_IRQ_CLR（位6）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_TBAT_ERROR_IRQ_CLR_Msk (0x40UL) /*!< TBAT_ERROR_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_TDIE_ERROR_IRQ_CLR_Pos (5UL) /*!< TDIE_ERROR_IRQ_CLR（第5位）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_TDIE_ERROR_IRQ_CLR_Msk (0x20UL) /*!< TDIE_ERROR_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_VBAT_OVP_ERROR_IRQ_CLR_Pos (4UL) /*!< VBAT_OVP_ERROR_IRQ_CLR（位4）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_VBAT_OVP_ERROR_IRQ_CLR_Msk (0x10UL) /*!< VBAT_OVP_ERROR_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_TOTAL_CHARGE_TIMEOUT_IRQ_CLR_Pos (3UL) /*!< TOTAL_CHARGE_TIMEOUT_IRQ_CLR（位3）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_TOTAL_CHARGE_TIMEOUT_IRQ_CLR_Msk (0x8UL) /*!< TOTAL_CHARGE_TIMEOUT_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_CV_CHARGE_TIMEOUT_IRQ_CLR_Pos (2UL) /*!< CV_CHARGE_TIMEOUT_IRQ_CLR（位2）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_CV_CHARGE_TIMEOUT_IRQ_CLR_Msk (0x4UL) /*!< CV_CHARGE_TIMEOUT_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_CC_CHARGE_TIMEOUT_IRQ_CLR_Pos (1UL) /*!< CC_CHARGE_TIMEOUT_IRQ_CLR（位1）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_CC_CHARGE_TIMEOUT_IRQ_CLR_Msk (0x2UL) /*!< CC_CHARGE_TIMEOUT_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_PRECHARGE_TIMEOUT_IRQ_CLR_Pos (0UL) /*!< PRECHARGE_TIMEOUT_IRQ_CLR（位0）*/
#define CHARGER_CHARGER_ERROR_IRQ_CLR_REG_PRECHARGE_TIMEOUT_IRQ_CLR_Msk (0x1UL) /*!< PRECHARGE_TIMEOUT_IRQ_CLR（位字段掩码：0x01）*/
/* ==============================================  CHARGER_ERROR_IRQ_MASK_REG  =============================================== */
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_TBAT_ERROR_IRQ_EN_Pos (6UL) /*!< TBAT_ERROR_IRQ_EN（位6）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_TBAT_ERROR_IRQ_EN_Msk (0x40UL) /*!< TBAT_ERROR_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_TDIE_ERROR_IRQ_EN_Pos (5UL) /*!< TDIE_ERROR_IRQ_EN（第5位）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_TDIE_ERROR_IRQ_EN_Msk (0x20UL) /*!< TDIE_ERROR_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_VBAT_OVP_ERROR_IRQ_EN_Pos (4UL) /*!< VBAT_OVP_ERROR_IRQ_EN（位4）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_VBAT_OVP_ERROR_IRQ_EN_Msk (0x10UL) /*!< VBAT_OVP_ERROR_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_TOTAL_CHARGE_TIMEOUT_IRQ_EN_Pos (3UL) /*!< TOTAL_CHARGE_TIMEOUT_IRQ_EN（位3）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_TOTAL_CHARGE_TIMEOUT_IRQ_EN_Msk (0x8UL) /*!< TOTAL_CHARGE_TIMEOUT_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_CV_CHARGE_TIMEOUT_IRQ_EN_Pos (2UL) /*!< CV_CHARGE_TIMEOUT_IRQ_EN（位2）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_CV_CHARGE_TIMEOUT_IRQ_EN_Msk (0x4UL) /*!< CV_CHARGE_TIMEOUT_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_CC_CHARGE_TIMEOUT_IRQ_EN_Pos (1UL) /*!< CC_CHARGE_TIMEOUT_IRQ_EN（位1）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_CC_CHARGE_TIMEOUT_IRQ_EN_Msk (0x2UL) /*!< CC_CHARGE_TIMEOUT_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_PRECHARGE_TIMEOUT_IRQ_EN_Pos (0UL) /*!< PRECHARGE_TIMEOUT_IRQ_EN（位0）*/
#define CHARGER_CHARGER_ERROR_IRQ_MASK_REG_PRECHARGE_TIMEOUT_IRQ_EN_Msk (0x1UL) /*!< PRECHARGE_TIMEOUT_IRQ_EN（位字段掩码：0x01）*/
/* =============================================  CHARGER_ERROR_IRQ_STATUS_REG  ============================================== */
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_TBAT_ERROR_IRQ_Pos (6UL) /*!< TBAT_ERROR_IRQ（位6）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_TBAT_ERROR_IRQ_Msk (0x40UL) /*!< TBAT_ERROR_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_TDIE_ERROR_IRQ_Pos (5UL) /*!< TDIE_ERROR_IRQ（第5位）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_TDIE_ERROR_IRQ_Msk (0x20UL) /*!< TDIE_ERROR_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_VBAT_OVP_ERROR_IRQ_Pos (4UL) /*!< VBAT_OVP_ERROR_IRQ（位4）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_VBAT_OVP_ERROR_IRQ_Msk (0x10UL) /*!< VBAT_OVP_ERROR_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_TOTAL_CHARGE_TIMEOUT_IRQ_Pos (3UL) /*!< TOTAL_CHARGE_TIMEOUT_IRQ（位3）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_TOTAL_CHARGE_TIMEOUT_IRQ_Msk (0x8UL) /*!< TOTAL_CHARGE_TIMEOUT_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_CV_CHARGE_TIMEOUT_IRQ_Pos (2UL) /*!< CV_CHARGE_TIMEOUT_IRQ（位2）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_CV_CHARGE_TIMEOUT_IRQ_Msk (0x4UL) /*!< CV_CHARGE_TIMEOUT_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_CC_CHARGE_TIMEOUT_IRQ_Pos (1UL) /*!< CC_CHARGE_TIMEOUT_IRQ（位1）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_CC_CHARGE_TIMEOUT_IRQ_Msk (0x2UL) /*!< CC_CHARGE_TIMEOUT_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_PRECHARGE_TIMEOUT_IRQ_Pos (0UL) /*!< PRECHARGE_TIMEOUT_IRQ（位0）*/
#define CHARGER_CHARGER_ERROR_IRQ_STATUS_REG_PRECHARGE_TIMEOUT_IRQ_Msk (0x1UL) /*!< PRECHARGE_TIMEOUT_IRQ（位字段掩码：0x01）*/
/* ===============================================  CHARGER_JEITA_CURRENT_REG  =============================================== */
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_PRECHARGE_TWARM_Pos (18UL) /*!< I_PRECHARGE_WARM（位18）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_PRECHARGE_TWARM_Msk (0xfc0000UL) /*!< I_PRECHARGE_WARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_PRECHARGE_TCOOL_Pos (12UL) /*!< I_PRECHARGE_TCOOL（第12位）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_PRECHARGE_TCOOL_Msk (0x3f000UL) /*!< I_PRECHARGE_TCOOL（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_CHARGE_TWARM_Pos (6UL)  /*!< I_CHARGE_WARM（位6）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_CHARGE_TWARM_Msk (0xfc0UL) /*!< I_CHARGE_WARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_CHARGE_TCOOL_Pos (0UL)  /*!< I_CHARGE_TCOOL（位0）*/
#define CHARGER_CHARGER_JEITA_CURRENT_REG_I_CHARGE_TCOOL_Msk (0x3fUL) /*!< I_CHARGE_TCOOL（位域掩码：0x3f）*/
/* ==============================================  CHARGER_JEITA_V_CHARGE_REG  =============================================== */
#define CHARGER_CHARGER_JEITA_V_CHARGE_REG_V_CHARGE_TWARM_Pos (6UL) /*!< V_CHARGE_WARM（位6）*/
#define CHARGER_CHARGER_JEITA_V_CHARGE_REG_V_CHARGE_TWARM_Msk (0xfc0UL) /*!< V_CHARGE_WARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_V_CHARGE_REG_V_CHARGE_TCOOL_Pos (0UL) /*!< V_CHARGE_TCOOL（位0）*/
#define CHARGER_CHARGER_JEITA_V_CHARGE_REG_V_CHARGE_TCOOL_Msk (0x3fUL) /*!< V_CHARGE_TCOOL（位域掩码：0x3f）*/
/* ================================================  CHARGER_JEITA_V_OVP_REG  ================================================ */
#define CHARGER_CHARGER_JEITA_V_OVP_REG_V_OVP_TWARM_Pos (6UL)       /*!< V_OVP_TWARM（位6）*/
#define CHARGER_CHARGER_JEITA_V_OVP_REG_V_OVP_TWARM_Msk (0xfc0UL)   /*!< V_OVP_TWARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_V_OVP_REG_V_OVP_TCOOL_Pos (0UL)       /*!< V_OVP_TCOOL（位0）*/
#define CHARGER_CHARGER_JEITA_V_OVP_REG_V_OVP_TCOOL_Msk (0x3fUL)    /*!< V_OVP_TCOOL（位域掩码：0x3f）*/
/* =============================================  CHARGER_JEITA_V_PRECHARGE_REG  ============================================= */
#define CHARGER_CHARGER_JEITA_V_PRECHARGE_REG_V_PRECHARGE_TWARM_Pos (6UL) /*!< V_PRECHARGE_WARM（位6）*/
#define CHARGER_CHARGER_JEITA_V_PRECHARGE_REG_V_PRECHARGE_TWARM_Msk (0xfc0UL) /*!< V_PRECHARGE_WARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_V_PRECHARGE_REG_V_PRECHARGE_TCOOL_Pos (0UL) /*!< V_PRECHARGE_TCOOL（位0）*/
#define CHARGER_CHARGER_JEITA_V_PRECHARGE_REG_V_PRECHARGE_TCOOL_Msk (0x3fUL) /*!< V_PRECHARGE_TCOOL（位域掩码：0x3f）*/
/* =============================================  CHARGER_JEITA_V_REPLENISH_REG  ============================================= */
#define CHARGER_CHARGER_JEITA_V_REPLENISH_REG_V_REPLENISH_TWARM_Pos (6UL) /*!< V_REPLENISH_TWARM（位6）*/
#define CHARGER_CHARGER_JEITA_V_REPLENISH_REG_V_REPLENISH_TWARM_Msk (0xfc0UL) /*!< V_REPLENISH_TWARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_JEITA_V_REPLENISH_REG_V_REPLENISH_TCOOL_Pos (0UL) /*!< V_REPLENISH_TCOOL（位0）*/
#define CHARGER_CHARGER_JEITA_V_REPLENISH_REG_V_REPLENISH_TCOOL_Msk (0x3fUL) /*!< V_REPLENISH_TCOOL（位域掩码：0x3f）*/
/* =============================================  CHARGER_PRE_CHARGE_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_PRE_CHARGE_TIMER_REG_PRE_CHARGE_TIMER_Pos (16UL) /*!< PRE_CHARGE_TIMER（位16）*/
#define CHARGER_CHARGER_PRE_CHARGE_TIMER_REG_PRE_CHARGE_TIMER_Msk (0x7fff0000UL) /*!< PRE_CHARGE_TIMER（位域掩码：0x7fff）*/
#define CHARGER_CHARGER_PRE_CHARGE_TIMER_REG_MAX_PRE_CHARGE_TIME_Pos (0UL) /*!< MAX_PRE_CHARGE_TIME（位0）*/
#define CHARGER_CHARGER_PRE_CHARGE_TIMER_REG_MAX_PRE_CHARGE_TIME_Msk (0x7fffUL) /*!< MAX_PRE_CHARGE_TIME（位域掩码：0x7fff）*/
/* ===============================================  CHARGER_PWR_UP_TIMER_REG  ================================================ */
#define CHARGER_CHARGER_PWR_UP_TIMER_REG_CHARGER_PWR_UP_TIMER_Pos (16UL) /*!< CHARGER_PWR_UP_TIMER（位16）*/
#define CHARGER_CHARGER_PWR_UP_TIMER_REG_CHARGER_PWR_UP_TIMER_Msk (0x3ff0000UL) /*!< CHARGER_PWR_UP_TIMER（位域掩码：0x3ff）*/
#define CHARGER_CHARGER_PWR_UP_TIMER_REG_CHARGER_PWR_UP_SETTLING_Pos (0UL) /*!< CHARGER_PWR_UP_SETLING（位0）*/
#define CHARGER_CHARGER_PWR_UP_TIMER_REG_CHARGER_PWR_UP_SETTLING_Msk (0x3ffUL) /*!< CHARGER_PWR_UP_SETTING（位域掩码：0x3ff）*/
/* ===============================================  CHARGER_STATE_IRQ_CLR_REG  =============================================== */
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CV_TO_PRECHARGE_IRQ_CLR_Pos (11UL) /*!< CV_TO_PRECHARGE_IRQ_CLR（第11位）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CV_TO_PRECHARGE_IRQ_CLR_Msk (0x800UL) /*!< CV_TO_PRECHARGE_IRQ_CLR（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CC_TO_PRECHARGE_IRQ_CLR_Pos (10UL) /*!< CC_TO_PRECHARGE_IRQ_CLR（第10位）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CC_TO_PRECHARGE_IRQ_CLR_Msk (0x400UL) /*!< CC_TO_PRECHARGE_IRQ_CLR（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CV_TO_CC_IRQ_CLR_Pos (9UL) /*!< CV_TO_CC_IRQ_CLR（第9位）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CV_TO_CC_IRQ_CLR_Msk (0x200UL) /*!< CV_TO_CC_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_TBAT_STATUS_UPDATE_IRQ_CLR_Pos (8UL) /*!< TBAT_STATUS_UPDATE_IRQ_CLR（位8）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_TBAT_STATUS_UPDATE_IRQ_CLR_Msk (0x100UL) /*!< TBAT_STATUS_UPDATE_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_TBAT_PROT_TO_PRECHARGE_IRQ_CLR_Pos (7UL) /*!< TBAT_PROT_TO_PRECHARGE_IRQ_CLR（第7位）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_TBAT_PROT_TO_PRECHARGE_IRQ_CLR_Msk (0x80UL) /*!< TBAT_PROT_TO_PRECHARGE_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_TDIE_PROT_TO_PRECHARGE_IRQ_CLR_Pos (6UL) /*!< TDIE_PROT_TO_PRECHARGE_IRQ_CLR（位6）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_TDIE_PROT_TO_PRECHARGE_IRQ_CLR_Msk (0x40UL) /*!< TDIE_PROT_TO_PRECHARGE_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_EOC_TO_PRECHARGE_IRQ_CLR_Pos (5UL) /*!< EOC_TO_PRECHARGE_IRQ_CLR（位5）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_EOC_TO_PRECHARGE_IRQ_CLR_Msk (0x20UL) /*!< EOC_TO_PRECHARGE_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CV_TO_EOC_IRQ_CLR_Pos (4UL) /*!< CV_TO_EOC_IRQ_CLR（位4）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CV_TO_EOC_IRQ_CLR_Msk (0x10UL) /*!< CV_TO_EOC_IRQ_CLR（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CC_TO_EOC_IRQ_CLR_Pos (3UL) /*!< CC_TO_EOC_IRQ_CLR（位3）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CC_TO_EOC_IRQ_CLR_Msk (0x8UL) /*!< CC_TO_EOC_IRQ_CLR（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CC_TO_CV_IRQ_CLR_Pos (2UL) /*!< CC_TO_CV_IRQ_CLR（第2位）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_CC_TO_CV_IRQ_CLR_Msk (0x4UL) /*!< CC_TO_CV_IRQ_CLR（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_PRECHARGE_TO_CC_IRQ_CLR_Pos (1UL) /*!< 预充电_TO_CC_IRQ_CLR（位1）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_PRECHARGE_TO_CC_IRQ_CLR_Msk (0x2UL) /*!< PRECHARGE_TO_CC_IRQ_CLR（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_DISABLED_TO_PRECHARGE_IRQ_CLR_Pos (0UL) /*!< DISABLED_TO_PRECHARGE_IRQ_CLR（位0）*/
#define CHARGER_CHARGER_STATE_IRQ_CLR_REG_DISABLED_TO_PRECHARGE_IRQ_CLR_Msk (0x1UL) /*!< DISABLED_TO_PRECHARGE_IRQ_CLR（位字段掩码：0x01）*/
/* ==============================================  CHARGER_STATE_IRQ_MASK_REG  =============================================== */
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CV_TO_PRECHARGE_IRQ_EN_Pos (11UL) /*!< CV_TO_PRECHARGE_IRQ_EN（第11位）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CV_TO_PRECHARGE_IRQ_EN_Msk (0x800UL) /*!< CV_TO_PRECHARGE_IRQ_EN（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CC_TO_PRECHARGE_IRQ_EN_Pos (10UL) /*!< CC_TO_PRECHARGE_IRQ_EN（第10位）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CC_TO_PRECHARGE_IRQ_EN_Msk (0x400UL) /*!< CC_TO_PRECHARGE_IRQ_EN（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CV_TO_CC_IRQ_EN_Pos (9UL) /*!< CV_TO_CC_IRQ_EN（第9位）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CV_TO_CC_IRQ_EN_Msk (0x200UL) /*!< CV_TO_CC_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_TBAT_STATUS_UPDATE_IRQ_EN_Pos (8UL) /*!< TBAT_STATUS_UPDATE_IRQ_EN（位8）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_TBAT_STATUS_UPDATE_IRQ_EN_Msk (0x100UL) /*!< TBAT_STATUS_UPDATE_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_TBAT_PROT_TO_PRECHARGE_IRQ_EN_Pos (7UL) /*!< TBAT_PROT_TO_PRECHARGE_IRQ_EN（第7位）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_TBAT_PROT_TO_PRECHARGE_IRQ_EN_Msk (0x80UL) /*!< TBAT_PROT_TO_PRECHARGE_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_TDIE_PROT_TO_PRECHARGE_IRQ_EN_Pos (6UL) /*!< TDIE_PROT_TO_PRECHARGE_IRQ_EN（第6位）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_TDIE_PROT_TO_PRECHARGE_IRQ_EN_Msk (0x40UL) /*!< TDIE_PROT_TO_PRECHARGE_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_EOC_TO_PRECHARGE_IRQ_EN_Pos (5UL) /*!< EOC_TO_PRECHARGE_IRQ_EN（位5）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_EOC_TO_PRECHARGE_IRQ_EN_Msk (0x20UL) /*!< EOC_TO_PRECHARGE_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CV_TO_EOC_IRQ_EN_Pos (4UL) /*!< CV_TO_EOC_IRQ_EN（位4）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CV_TO_EOC_IRQ_EN_Msk (0x10UL) /*!< CV_TO_EOC_IRQ_EN（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CC_TO_EOC_IRQ_EN_Pos (3UL) /*!< CC_TO_EOC_IRQ_EN（位3）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CC_TO_EOC_IRQ_EN_Msk (0x8UL) /*!< CC_TO_EOC_IRQ_EN（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CC_TO_CV_IRQ_EN_Pos (2UL) /*!< CC_TO_CV_IRQ_EN（位2）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_CC_TO_CV_IRQ_EN_Msk (0x4UL) /*!< CC_TO_CV_IRQ_EN（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_PRECHARGE_TO_CC_IRQ_EN_Pos (1UL) /*!< 预充电_TO_CC_IRQ_EN（位1）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_PRECHARGE_TO_CC_IRQ_EN_Msk (0x2UL) /*!< PRECHARGE_TO_CC_IRQ_EN（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_DISABLED_TO_PRECHARGE_IRQ_EN_Pos (0UL) /*!< DISABLED_TO_PRECHARGE_IRQ_EN（位0）*/
#define CHARGER_CHARGER_STATE_IRQ_MASK_REG_DISABLED_TO_PRECHARGE_IRQ_EN_Msk (0x1UL) /*!< DISABLED_TO_PRECHARGE_IRQ_EN（位字段掩码：0x01）*/
/* =============================================  CHARGER_STATE_IRQ_STATUS_REG  ============================================== */
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CV_TO_PRECHARGE_IRQ_Pos (11UL) /*!< CV_TO_PRECHARGE_IRQ（第11位）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CV_TO_PRECHARGE_IRQ_Msk (0x800UL) /*!< CV_TO_PRECHARGE_IRQ（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CC_TO_PRECHARGE_IRQ_Pos (10UL) /*!< CC_TO_PRECHARGE_IRQ（第10位）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CC_TO_PRECHARGE_IRQ_Msk (0x400UL) /*!< CC_TO_PRECHARGE_IRQ（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CV_TO_CC_IRQ_Pos (9UL) /*!< CV_TO_CC_IRQ（第9位）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CV_TO_CC_IRQ_Msk (0x200UL) /*!< CV_TO_CC_IRQ（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_TBAT_STATUS_UPDATE_IRQ_Pos (8UL) /*!< TBAT_STATUS_UPDATE_IRQ（位8）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_TBAT_STATUS_UPDATE_IRQ_Msk (0x100UL) /*!< TBAT_STATUS_UPDATE_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_TBAT_PROT_TO_PRECHARGE_IRQ_Pos (7UL) /*!< TBAT_PROT_TO_PRECHARGE_IRQ（位7）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_TBAT_PROT_TO_PRECHARGE_IRQ_Msk (0x80UL) /*!< TBAT_PROT_TO_PRECHARGE_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_TDIE_PROT_TO_PRECHARGE_IRQ_Pos (6UL) /*!< TDIE_PROT_TO_PRECHARGE_IRQ（位6）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_TDIE_PROT_TO_PRECHARGE_IRQ_Msk (0x40UL) /*!< TDIE_PROT_TO_PRECHARGE_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_EOC_TO_PRECHARGE_IRQ_Pos (5UL) /*!< EOC_TO_PRECHARGE_IRQ（位5）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_EOC_TO_PRECHARGE_IRQ_Msk (0x20UL) /*!< EOC_TO_PRECHARGE_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CV_TO_EOC_IRQ_Pos (4UL) /*!< CV_TO_EOC_IRQ（位4）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CV_TO_EOC_IRQ_Msk (0x10UL) /*!< CV_TO_EOC_IRQ（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CC_TO_EOC_IRQ_Pos (3UL) /*!< CC_TO_EOC_IRQ（位3）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CC_TO_EOC_IRQ_Msk (0x8UL) /*!< CC_TO_EOC_IRQ（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CC_TO_CV_IRQ_Pos (2UL) /*!< CC_TO_CV_IRQ（位2）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_CC_TO_CV_IRQ_Msk (0x4UL) /*!< CC_TO_CV_IRQ（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_PRECHARGE_TO_CC_IRQ_Pos (1UL) /*!< 预充电_TO_CC_IRQ（位1）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_PRECHARGE_TO_CC_IRQ_Msk (0x2UL) /*!< PRECHARGE_TO_CC_IRQ（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_DISABLED_TO_PRECHARGE_IRQ_Pos (0UL) /*!< DISABLED_TO_PRECHARGE_IRQ（位0）*/
#define CHARGER_CHARGER_STATE_IRQ_STATUS_REG_DISABLED_TO_PRECHARGE_IRQ_Msk (0x1UL) /*!< DISABLED_TO_PRECHARGE_IRQ（位字段掩码：0x01）*/
/* ==================================================  CHARGER_STATUS_REG  =================================================== */
#define CHARGER_CHARGER_STATUS_REG_OVP_EVENTS_DEBOUNCE_CNT_Pos (27UL) /*!< OVP_EVENTS_DEBOUNCE_CNT（第27位）*/
#define CHARGER_CHARGER_STATUS_REG_OVP_EVENTS_DEBOUNCE_CNT_Msk (0x38000000UL) /*!< OVP_EVENTS_DEBOUNCE_CNT（位字段掩码：0x07）*/
#define CHARGER_CHARGER_STATUS_REG_EOC_EVENTS_DEBOUNCE_CNT_Pos (24UL) /*!< EOC_EVENTS_DEBOUNCE_CNT（位24）*/
#define CHARGER_CHARGER_STATUS_REG_EOC_EVENTS_DEBOUNCE_CNT_Msk (0x7000000UL) /*!< EOC_EVENTS_DEBOUNCE_CNT（位字段掩码：0x07）*/
#define CHARGER_CHARGER_STATUS_REG_TDIE_ERROR_DEBOUNCE_CNT_Pos (21UL) /*!< TDIE_ERROR_DEBOUNCE_CNT（第21位）*/
#define CHARGER_CHARGER_STATUS_REG_TDIE_ERROR_DEBOUNCE_CNT_Msk (0xe00000UL) /*!< TDIE_ERROR_DEBOUNCE_CNT（位字段掩码：0x07）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_JEITA_STATE_Pos (18UL)   /*!< CHARGER_JEITA_STATE（位18）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_JEITA_STATE_Msk (0x1c0000UL) /*!< CHARGER_JEITA_STATE（位域掩码：0x07）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_STATE_Pos (14UL)         /*!< CHARGER_STATE（位14）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_STATE_Msk (0x3c000UL)    /*!< CHARGER_STATE（位域掩码：0x0f）*/
#define CHARGER_CHARGER_STATUS_REG_TBAT_STATUS_Pos (9UL)            /*!< TBAT_STATUS（位9）*/
#define CHARGER_CHARGER_STATUS_REG_TBAT_STATUS_Msk (0x3e00UL)       /*!< TBAT_STATUS（位字段掩码：0x1f）*/
#define CHARGER_CHARGER_STATUS_REG_MAIN_TBAT_COMP_OUT_Pos (8UL)     /*!< MAIN_BAT_COMP_OUT（位8）*/
#define CHARGER_CHARGER_STATUS_REG_MAIN_TBAT_COMP_OUT_Msk (0x100UL) /*!< MAIN_BAT_COMP_OUT（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_TBAT_HOT_COMP_OUT_Pos (7UL)      /*!< TBAT_HOT_COMP_OUT（位7）*/
#define CHARGER_CHARGER_STATUS_REG_TBAT_HOT_COMP_OUT_Msk (0x80UL)   /*!< TBAT_HOT_COMP_OUT（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_TDIE_COMP_OUT_Pos (6UL)          /*!< TDIE_COMP_OUT（位6）*/
#define CHARGER_CHARGER_STATUS_REG_TDIE_COMP_OUT_Msk (0x40UL)       /*!< TDIE_COMP_OUT（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_VBAT_OVP_COMP_OUT_Pos (5UL)      /*!< VBAT_OVP_COMP_OUT（位5）*/
#define CHARGER_CHARGER_STATUS_REG_VBAT_OVP_COMP_OUT_Msk (0x20UL)   /*!< VBAT_OVP_COMP_OUT（位字段掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_MAIN_VBAT_COMP_OUT_Pos (4UL)     /*!< MAIN_BAT_COMP_OUT（位4）*/
#define CHARGER_CHARGER_STATUS_REG_MAIN_VBAT_COMP_OUT_Msk (0x10UL)  /*!< MAIN_BAT_COMP_OUT（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_END_OF_CHARGE_Pos (3UL)          /*!< END_OF_CHARGE（位3）*/
#define CHARGER_CHARGER_STATUS_REG_END_OF_CHARGE_Msk (0x8UL)        /*!< END_OF_CHARGE（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_CV_MODE_Pos (2UL)        /*!< CHARGER_CV_MODE（位2）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_CV_MODE_Msk (0x4UL)      /*!< CHARGER_CV_MODE（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_CC_MODE_Pos (1UL)        /*!< CHARGER_CC_MODE（位1）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_CC_MODE_Msk (0x2UL)      /*!< CHARGER_CC_MODE（位域掩码：0x01）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_IS_POWERED_UP_Pos (0UL)  /*!< CHARGER_IS_POWERED_UP（位0）*/
#define CHARGER_CHARGER_STATUS_REG_CHARGER_IS_POWERED_UP_Msk (0x1UL) /*!< CHARGER_IS_POWERED_UP（位域掩码：0x01）*/
/* ==============================================  CHARGER_TBAT_COMP_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_TBAT_COMP_TIMER_REG_TBAT_COMP_TIMER_Pos (16UL) /*!< TBAT_COMP_TIMER（位16）*/
#define CHARGER_CHARGER_TBAT_COMP_TIMER_REG_TBAT_COMP_TIMER_Msk (0x3ff0000UL) /*!< TBAT_COMP_TIMER（位字段掩码：0x3ff）*/
#define CHARGER_CHARGER_TBAT_COMP_TIMER_REG_TBAT_COMP_SETTLING_Pos (0UL) /*!< TBAT_COMP_SETTLING（位0）*/
#define CHARGER_CHARGER_TBAT_COMP_TIMER_REG_TBAT_COMP_SETTLING_Msk (0x3ffUL) /*!< TBAT_COMP_SETTLING（位字段掩码：0x3ff）*/
/* ==============================================  CHARGER_TBAT_MON_TIMER_REG  =============================================== */
#define CHARGER_CHARGER_TBAT_MON_TIMER_REG_TBAT_MON_TIMER_Pos (16UL) /*!< TBAT_MON_TIMER（位16）*/
#define CHARGER_CHARGER_TBAT_MON_TIMER_REG_TBAT_MON_TIMER_Msk (0x3ff0000UL) /*!< TBAT_MON_TIMER（位字段掩码：0x3ff）*/
#define CHARGER_CHARGER_TBAT_MON_TIMER_REG_TBAT_MON_INTERVAL_Pos (0UL) /*!< TBAT_MON_INTERVAL（位0）*/
#define CHARGER_CHARGER_TBAT_MON_TIMER_REG_TBAT_MON_INTERVAL_Msk (0x3ffUL) /*!< TBAT_MON_INTERVAL（位字段掩码：0x3ff）*/
/* ==============================================  CHARGER_TDIE_COMP_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_TDIE_COMP_TIMER_REG_TDIE_COMP_TIMER_Pos (16UL) /*!< TDIE_COMP_TIMER（位16）*/
#define CHARGER_CHARGER_TDIE_COMP_TIMER_REG_TDIE_COMP_TIMER_Msk (0x3ff0000UL) /*!< TDIE_COMP_TIMER（位域掩码：0x3ff）*/
#define CHARGER_CHARGER_TDIE_COMP_TIMER_REG_TDIE_COMP_SETTLING_Pos (0UL) /*!< TDIE_COMP_SETTLING（位0）*/
#define CHARGER_CHARGER_TDIE_COMP_TIMER_REG_TDIE_COMP_SETTLING_Msk (0x3ffUL) /*!< TDIE_COMP_SETTLING（位域掩码：0x3ff）*/
/* ===============================================  CHARGER_TEMPSET_PARAM_REG  =============================================== */
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TDIE_MAX_Pos (24UL)       /*!< TDIE_MAX（位24）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TDIE_MAX_Msk (0x7000000UL) /*!< TDIE_MAX（位字段掩码：0x07）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_HOT_Pos (18UL)       /*!< TBAT_HOT（位18）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_HOT_Msk (0xfc0000UL) /*!< TBAT_HOT（位域掩码：0x3f）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_WARM_Pos (12UL)      /*!< TBAT_WARM（位12）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_WARM_Msk (0x3f000UL) /*!< TBAT_WARM（位域掩码：0x3f）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_COOL_Pos (6UL)       /*!< TBAT_COOL（位6）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_COOL_Msk (0xfc0UL)   /*!< TBAT_COOL（位域掩码：0x3f）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_COLD_Pos (0UL)       /*!< TBAT_COLD（位0）*/
#define CHARGER_CHARGER_TEMPSET_PARAM_REG_TBAT_COLD_Msk (0x3fUL)    /*!< TBAT_COLD（位字段掩码：0x3f）*/
/* =================================================  CHARGER_TEST_CTRL_REG  ================================================= */
/* ==============================================  CHARGER_THOT_COMP_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_THOT_COMP_TIMER_REG_THOT_COMP_TIMER_Pos (16UL) /*!< THOT_COMP_TIMER（位16）*/
#define CHARGER_CHARGER_THOT_COMP_TIMER_REG_THOT_COMP_TIMER_Msk (0x3ff0000UL) /*!< THOT_COMP_TIMER（位域掩码：0x3ff）*/
#define CHARGER_CHARGER_THOT_COMP_TIMER_REG_THOT_COMP_SETTLING_Pos (0UL) /*!< THOT_COMP_SETTLING（位0）*/
#define CHARGER_CHARGER_THOT_COMP_TIMER_REG_THOT_COMP_SETTLING_Msk (0x3ffUL) /*!< THOT_COMP_SETTLING（位域掩码：0x3ff）*/
/* ============================================  CHARGER_TOTAL_CHARGE_TIMER_REG  ============================================= */
#define CHARGER_CHARGER_TOTAL_CHARGE_TIMER_REG_TOTAL_CHARGE_TIMER_Pos (16UL) /*!< TOTAL_CHARGE_TIMER（位16）*/
#define CHARGER_CHARGER_TOTAL_CHARGE_TIMER_REG_TOTAL_CHARGE_TIMER_Msk (0xffff0000UL) /*!< TOTAL_CHARGE_TIMER（位字段掩码：0xffff）*/
#define CHARGER_CHARGER_TOTAL_CHARGE_TIMER_REG_MAX_TOTAL_CHARGE_TIME_Pos (0UL) /*!< MAX_TOTAL_CHARGE_TIME（位0）*/
#define CHARGER_CHARGER_TOTAL_CHARGE_TIMER_REG_MAX_TOTAL_CHARGE_TIME_Msk (0xffffUL) /*!< MAX_TOTAL_CHARGE_TIME（位域掩码：0xffff）*/
/* ==============================================  CHARGER_VBAT_COMP_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_VBAT_COMP_TIMER_REG_VBAT_COMP_TIMER_Pos (16UL) /*!< VBAT_COMP_TIMER（位16）*/
#define CHARGER_CHARGER_VBAT_COMP_TIMER_REG_VBAT_COMP_TIMER_Msk (0x3ff0000UL) /*!< VBAT_COMP_TIMER（位域掩码：0x3ff）*/
#define CHARGER_CHARGER_VBAT_COMP_TIMER_REG_VBAT_COMP_SETTLING_Pos (0UL) /*!< VBAT_COMP_SETTLING（位0）*/
#define CHARGER_CHARGER_VBAT_COMP_TIMER_REG_VBAT_COMP_SETTLING_Msk (0x3ffUL) /*!< VBAT_COMP_SETTLING（位字段掩码：0x3ff）*/
/* ===============================================  CHARGER_VOLTAGE_PARAM_REG  =============================================== */
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_OVP_Pos (18UL)          /*!< V_OVP（位18）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_OVP_Msk (0xfc0000UL)    /*!< V_OVP（位域掩码：0x3f）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_REPLENISH_Pos (12UL)    /*!< V_REPLENISH（第12位）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_REPLENISH_Msk (0x3f000UL) /*!< V_REPLENISH（位域掩码：0x3f）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_PRECHARGE_Pos (6UL)     /*!< V_PRECHARGE（位6）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_PRECHARGE_Msk (0xfc0UL) /*!< V_PRECHARGE（位域掩码：0x3f）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_CHARGE_Pos (0UL)        /*!< V_CHARGE（位0）*/
#define CHARGER_CHARGER_VOLTAGE_PARAM_REG_V_CHARGE_Msk (0x3fUL)     /*!< V_CHARGE（位域掩码：0x3f）*/
/* ==============================================  CHARGER_VOVP_COMP_TIMER_REG  ============================================== */
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_OVP_INTERVAL_CHECK_TIMER_Pos (26UL) /*!< OVP_INTERVAL_CHECK_TIMER（位26）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_OVP_INTERVAL_CHECK_TIMER_Msk (0xfc000000UL) /*!< OVP_INTERVAL_CHECK_TIMER（位域掩码：0x3f）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_VBAT_OVP_COMP_TIMER_Pos (16UL) /*!< VBAT_OVP_COMP_TIMER（位16）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_VBAT_OVP_COMP_TIMER_Msk (0x3ff0000UL) /*!< VBAT_OVP_COMP_TIMER（位域掩码：0x3ff）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_OVP_INTERVAL_CHECK_THRES_Pos (10UL) /*!< OVP_INTERVAL_CHECK_THRES（位10）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_OVP_INTERVAL_CHECK_THRES_Msk (0xfc00UL) /*!< OVP_INTERVAL_CHECK_THRES（位域掩码：0x3f）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_VBAT_OVP_COMP_SETTLING_Pos (0UL) /*!< VBAT_OVP_COMP_SETTLING（位0）*/
#define CHARGER_CHARGER_VOVP_COMP_TIMER_REG_VBAT_OVP_COMP_SETTLING_Msk (0x3ffUL) /*!< VBAT_OVP_COMP_SETTLING（位字段掩码：0x3ff）*/


/* =========================================================================================================================== */
/* ================                                       CHIP_VERSION                                        ================ */
/* =========================================================================================================================== */

/* =====================================================  CHIP_ID1_REG  ====================================================== */
#define CHIP_VERSION_CHIP_ID1_REG_CHIP_ID1_Pos (0UL)                /*!< CHIP_ID1（位0）*/
#define CHIP_VERSION_CHIP_ID1_REG_CHIP_ID1_Msk (0xffUL)             /*!< CHIP_ID1（位域掩码：0xff）*/
/* =====================================================  CHIP_ID2_REG  ====================================================== */
#define CHIP_VERSION_CHIP_ID2_REG_CHIP_ID2_Pos (0UL)                /*!< CHIP_ID2（位0）*/
#define CHIP_VERSION_CHIP_ID2_REG_CHIP_ID2_Msk (0xffUL)             /*!< CHIP_ID2（位域掩码：0xff）*/
/* =====================================================  CHIP_ID3_REG  ====================================================== */
#define CHIP_VERSION_CHIP_ID3_REG_CHIP_ID3_Pos (0UL)                /*!< CHIP_ID3（位0）*/
#define CHIP_VERSION_CHIP_ID3_REG_CHIP_ID3_Msk (0xffUL)             /*!< CHIP_ID3（位域掩码：0xff）*/
/* =====================================================  CHIP_ID4_REG  ====================================================== */
#define CHIP_VERSION_CHIP_ID4_REG_CHIP_ID4_Pos (0UL)                /*!< CHIP_ID4（位0）*/
#define CHIP_VERSION_CHIP_ID4_REG_CHIP_ID4_Msk (0xffUL)             /*!< CHIP_ID4（位域掩码：0xff）*/
/* ===================================================  CHIP_REVISION_REG  =================================================== */
#define CHIP_VERSION_CHIP_REVISION_REG_CHIP_REVISION_Pos (0UL)      /*!< 芯片修订（位0）*/
#define CHIP_VERSION_CHIP_REVISION_REG_CHIP_REVISION_Msk (0xffUL)   /*!< CHIP_REVISION（位域掩码：0xff）*/
/* =====================================================  CHIP_SWC_REG  ====================================================== */
#define CHIP_VERSION_CHIP_SWC_REG_CHIP_SWC_Pos (0UL)                /*!< CHIP_SWC（位0）*/
#define CHIP_VERSION_CHIP_SWC_REG_CHIP_SWC_Msk (0xfUL)              /*!< CHIP_SWC（位域掩码：0x0f）*/
/* ====================================================  CHIP_TEST1_REG  ===================================================== */
#define CHIP_VERSION_CHIP_TEST1_REG_CHIP_LAYOUT_REVISION_Pos (0UL)  /*!< CHIP_LAYOUT_REVISION（位0）*/
#define CHIP_VERSION_CHIP_TEST1_REG_CHIP_LAYOUT_REVISION_Msk (0xffUL) /*!< CHIP_LAYOUT_REVISION（位域掩码：0xff）*/
/* ====================================================  CHIP_TEST2_REG  ===================================================== */
#define CHIP_VERSION_CHIP_TEST2_REG_CHIP_METAL_OPTION_Pos (0UL)     /*!< CHIP_METAL_OPTION（位0）*/
#define CHIP_VERSION_CHIP_TEST2_REG_CHIP_METAL_OPTION_Msk (0xfUL)   /*!< CHIP_METAL_OPTION（位字段掩码：0x0f）*/


/* =========================================================================================================================== */
/* ================                                          CRG_COM                                          ================ */
/* =========================================================================================================================== */

/* ======================================================  CLK_COM_REG  ====================================================== */
#define CRG_COM_CLK_COM_REG_LCD_EXT_CLK_SEL_Pos (16UL)              /*!< LCD_EXT_CLK_SEL（位16）*/
#define CRG_COM_CLK_COM_REG_LCD_EXT_CLK_SEL_Msk (0x30000UL)         /*!< LCD_EXT_CLK_SEL（位字段掩码：0x03）*/
#define CRG_COM_CLK_COM_REG_SNC_DIV_Pos   (14UL)                    /*!< SNC_DIV（位14）*/
#define CRG_COM_CLK_COM_REG_SNC_DIV_Msk   (0xc000UL)                /*!< SNC_DIV（位域掩码：0x03）*/
#define CRG_COM_CLK_COM_REG_I2C2_CLK_SEL_Pos (12UL)                 /*!< I2C2_CLK_SEL（位12）*/
#define CRG_COM_CLK_COM_REG_I2C2_CLK_SEL_Msk (0x1000UL)             /*!< I2C2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_I2C2_ENABLE_Pos (11UL)                  /*!< I2C2_ENABLE（位11）*/
#define CRG_COM_CLK_COM_REG_I2C2_ENABLE_Msk (0x800UL)               /*!< I2C2_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_I2C_CLK_SEL_Pos (10UL)                  /*!< I2C_CLK_SEL（位10）*/
#define CRG_COM_CLK_COM_REG_I2C_CLK_SEL_Msk (0x400UL)               /*!< I2C_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_I2C_ENABLE_Pos (9UL)                    /*!< I2C_ENABLE（第9位）*/
#define CRG_COM_CLK_COM_REG_I2C_ENABLE_Msk (0x200UL)                /*!< I2C_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_SPI2_CLK_SEL_Pos (8UL)                  /*!< SPI2_CLK_SEL（位8）*/
#define CRG_COM_CLK_COM_REG_SPI2_CLK_SEL_Msk (0x100UL)              /*!< SPI2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_SPI2_ENABLE_Pos (7UL)                   /*!< SPI2_ENABLE（位7）*/
#define CRG_COM_CLK_COM_REG_SPI2_ENABLE_Msk (0x80UL)                /*!< SPI2_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_SPI_CLK_SEL_Pos (6UL)                   /*!< SPI_CLK_SEL（位6）*/
#define CRG_COM_CLK_COM_REG_SPI_CLK_SEL_Msk (0x40UL)                /*!< SPI_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_SPI_ENABLE_Pos (5UL)                    /*!< SPI_ENABLE（位5）*/
#define CRG_COM_CLK_COM_REG_SPI_ENABLE_Msk (0x20UL)                 /*!< SPI_ENABLE（位域掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_UART3_CLK_SEL_Pos (4UL)                 /*!< UART3_CLK_SEL（位4）*/
#define CRG_COM_CLK_COM_REG_UART3_CLK_SEL_Msk (0x10UL)              /*!< UART3_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_UART3_ENABLE_Pos (3UL)                  /*!< UART3_ENABLE（位3）*/
#define CRG_COM_CLK_COM_REG_UART3_ENABLE_Msk (0x8UL)                /*!< UART3_ENABLE（位域掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_UART2_CLK_SEL_Pos (2UL)                 /*!< UART2_CLK_SEL（位2）*/
#define CRG_COM_CLK_COM_REG_UART2_CLK_SEL_Msk (0x4UL)               /*!< UART2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_UART2_ENABLE_Pos (1UL)                  /*!< UART2_ENABLE（位1）*/
#define CRG_COM_CLK_COM_REG_UART2_ENABLE_Msk (0x2UL)                /*!< UART2_ENABLE（位域掩码：0x01）*/
#define CRG_COM_CLK_COM_REG_UART_ENABLE_Pos (0UL)                   /*!< UART_ENABLE（位0）*/
#define CRG_COM_CLK_COM_REG_UART_ENABLE_Msk (0x1UL)                 /*!< UART_ENABLE（位字段掩码：0x01）*/
/* ===================================================  RESET_CLK_COM_REG  =================================================== */
#define CRG_COM_RESET_CLK_COM_REG_LCD_EXT_CLK_SEL_Pos (16UL)        /*!< LCD_EXT_CLK_SEL（位16）*/
#define CRG_COM_RESET_CLK_COM_REG_LCD_EXT_CLK_SEL_Msk (0x30000UL)   /*!< LCD_EXT_CLK_SEL（位字段掩码：0x03）*/
#define CRG_COM_RESET_CLK_COM_REG_SNC_DIV_Pos (14UL)                /*!< SNC_DIV（位14）*/
#define CRG_COM_RESET_CLK_COM_REG_SNC_DIV_Msk (0xc000UL)            /*!< SNC_DIV（位域掩码：0x03）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C2_CLK_SEL_Pos (12UL)           /*!< I2C2_CLK_SEL（位12）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C2_CLK_SEL_Msk (0x1000UL)       /*!< I2C2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C2_ENABLE_Pos (11UL)            /*!< I2C2_ENABLE（位11）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C2_ENABLE_Msk (0x800UL)         /*!< I2C2_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C_CLK_SEL_Pos (10UL)            /*!< I2C_CLK_SEL（位10）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C_CLK_SEL_Msk (0x400UL)         /*!< I2C_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C_ENABLE_Pos (9UL)              /*!< I2C_ENABLE（第9位）*/
#define CRG_COM_RESET_CLK_COM_REG_I2C_ENABLE_Msk (0x200UL)          /*!< I2C_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI2_CLK_SEL_Pos (8UL)            /*!< SPI2_CLK_SEL（位8）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI2_CLK_SEL_Msk (0x100UL)        /*!< SPI2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI2_ENABLE_Pos (7UL)             /*!< SPI2_ENABLE（位7）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI2_ENABLE_Msk (0x80UL)          /*!< SPI2_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI_CLK_SEL_Pos (6UL)             /*!< SPI_CLK_SEL（位6）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI_CLK_SEL_Msk (0x40UL)          /*!< SPI_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI_ENABLE_Pos (5UL)              /*!< SPI_ENABLE（位5）*/
#define CRG_COM_RESET_CLK_COM_REG_SPI_ENABLE_Msk (0x20UL)           /*!< SPI_ENABLE（位域掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_UART3_CLK_SEL_Pos (4UL)           /*!< UART3_CLK_SEL（位4）*/
#define CRG_COM_RESET_CLK_COM_REG_UART3_CLK_SEL_Msk (0x10UL)        /*!< UART3_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_UART3_ENABLE_Pos (3UL)            /*!< UART3_ENABLE（位3）*/
#define CRG_COM_RESET_CLK_COM_REG_UART3_ENABLE_Msk (0x8UL)          /*!< UART3_ENABLE（位域掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_UART2_CLK_SEL_Pos (2UL)           /*!< UART2_CLK_SEL（位2）*/
#define CRG_COM_RESET_CLK_COM_REG_UART2_CLK_SEL_Msk (0x4UL)         /*!< UART2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_UART2_ENABLE_Pos (1UL)            /*!< UART2_ENABLE（位1）*/
#define CRG_COM_RESET_CLK_COM_REG_UART2_ENABLE_Msk (0x2UL)          /*!< UART2_ENABLE（位域掩码：0x01）*/
#define CRG_COM_RESET_CLK_COM_REG_UART_ENABLE_Pos (0UL)             /*!< UART_ENABLE（位0）*/
#define CRG_COM_RESET_CLK_COM_REG_UART_ENABLE_Msk (0x1UL)           /*!< UART_ENABLE（位字段掩码：0x01）*/
/* ====================================================  SET_CLK_COM_REG  ==================================================== */
#define CRG_COM_SET_CLK_COM_REG_LCD_EXT_CLK_SEL_Pos (16UL)          /*!< LCD_EXT_CLK_SEL（位16）*/
#define CRG_COM_SET_CLK_COM_REG_LCD_EXT_CLK_SEL_Msk (0x30000UL)     /*!< LCD_EXT_CLK_SEL（位字段掩码：0x03）*/
#define CRG_COM_SET_CLK_COM_REG_SNC_DIV_Pos (14UL)                  /*!< SNC_DIV（位14）*/
#define CRG_COM_SET_CLK_COM_REG_SNC_DIV_Msk (0xc000UL)              /*!< SNC_DIV（位域掩码：0x03）*/
#define CRG_COM_SET_CLK_COM_REG_I2C2_CLK_SEL_Pos (12UL)             /*!< I2C2_CLK_SEL（位12）*/
#define CRG_COM_SET_CLK_COM_REG_I2C2_CLK_SEL_Msk (0x1000UL)         /*!< I2C2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_I2C2_ENABLE_Pos (11UL)              /*!< I2C2_ENABLE（位11）*/
#define CRG_COM_SET_CLK_COM_REG_I2C2_ENABLE_Msk (0x800UL)           /*!< I2C2_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_I2C_CLK_SEL_Pos (10UL)              /*!< I2C_CLK_SEL（位10）*/
#define CRG_COM_SET_CLK_COM_REG_I2C_CLK_SEL_Msk (0x400UL)           /*!< I2C_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_I2C_ENABLE_Pos (9UL)                /*!< I2C_ENABLE（第9位）*/
#define CRG_COM_SET_CLK_COM_REG_I2C_ENABLE_Msk (0x200UL)            /*!< I2C_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_SPI2_CLK_SEL_Pos (8UL)              /*!< SPI2_CLK_SEL（位8）*/
#define CRG_COM_SET_CLK_COM_REG_SPI2_CLK_SEL_Msk (0x100UL)          /*!< SPI2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_SPI2_ENABLE_Pos (7UL)               /*!< SPI2_ENABLE（位7）*/
#define CRG_COM_SET_CLK_COM_REG_SPI2_ENABLE_Msk (0x80UL)            /*!< SPI2_ENABLE（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_SPI_CLK_SEL_Pos (6UL)               /*!< SPI_CLK_SEL（位6）*/
#define CRG_COM_SET_CLK_COM_REG_SPI_CLK_SEL_Msk (0x40UL)            /*!< SPI_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_SPI_ENABLE_Pos (5UL)                /*!< SPI_ENABLE（位5）*/
#define CRG_COM_SET_CLK_COM_REG_SPI_ENABLE_Msk (0x20UL)             /*!< SPI_ENABLE（位域掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_UART3_CLK_SEL_Pos (4UL)             /*!< UART3_CLK_SEL（位4）*/
#define CRG_COM_SET_CLK_COM_REG_UART3_CLK_SEL_Msk (0x10UL)          /*!< UART3_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_UART3_ENABLE_Pos (3UL)              /*!< UART3_ENABLE（位3）*/
#define CRG_COM_SET_CLK_COM_REG_UART3_ENABLE_Msk (0x8UL)            /*!< UART3_ENABLE（位域掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_UART2_CLK_SEL_Pos (2UL)             /*!< UART2_CLK_SEL（位2）*/
#define CRG_COM_SET_CLK_COM_REG_UART2_CLK_SEL_Msk (0x4UL)           /*!< UART2_CLK_SEL（位字段掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_UART2_ENABLE_Pos (1UL)              /*!< UART2_ENABLE（位1）*/
#define CRG_COM_SET_CLK_COM_REG_UART2_ENABLE_Msk (0x2UL)            /*!< UART2_ENABLE（位域掩码：0x01）*/
#define CRG_COM_SET_CLK_COM_REG_UART_ENABLE_Pos (0UL)               /*!< UART_ENABLE（位0）*/
#define CRG_COM_SET_CLK_COM_REG_UART_ENABLE_Msk (0x1UL)             /*!< UART_ENABLE（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                          CRG_PER                                          ================ */
/* =========================================================================================================================== */

/* ======================================================  CLK_PER_REG  ====================================================== */
#define CRG_PER_CLK_PER_REG_MC_TRIG_DIV_Pos (8UL)                   /*!< MC_TRIG_DIV（位8）*/
#define CRG_PER_CLK_PER_REG_MC_TRIG_DIV_Msk (0x1f00UL)              /*!< MC_TRIG_DIV（位域掩码：0x1f）*/
#define CRG_PER_CLK_PER_REG_MC_CLK_DIV_Pos (3UL)                    /*!< MC_CLK_DIV（位3）*/
#define CRG_PER_CLK_PER_REG_MC_CLK_DIV_Msk (0xf8UL)                 /*!< MC_CLK_DIV（位域掩码：0x1f）*/
#define CRG_PER_CLK_PER_REG_MC_CLK_EN_Pos (2UL)                     /*!< MC_CLK_EN（位2）*/
#define CRG_PER_CLK_PER_REG_MC_CLK_EN_Msk (0x4UL)                   /*!< MC_CLK_EN（位字段掩码：0x01）*/
#define CRG_PER_CLK_PER_REG_LRA_CLK_EN_Pos (1UL)                    /*!< LRA_CLK_EN（位1）*/
#define CRG_PER_CLK_PER_REG_LRA_CLK_EN_Msk (0x2UL)                  /*!< LRA_CLK_EN（位字段掩码：0x01）*/
#define CRG_PER_CLK_PER_REG_GPADC_CLK_SEL_Pos (0UL)                 /*!< GPADC_CLK_SEL（位0）*/
#define CRG_PER_CLK_PER_REG_GPADC_CLK_SEL_Msk (0x1UL)               /*!< GPADC_CLK_SEL（位字段掩码：0x01）*/
/* ======================================================  PCM_DIV_REG  ====================================================== */
#define CRG_PER_PCM_DIV_REG_PCM_SRC_SEL_Pos (13UL)                  /*!< PCM_SRC_SEL（位13）*/
#define CRG_PER_PCM_DIV_REG_PCM_SRC_SEL_Msk (0x2000UL)              /*!< PCM_SRC_SEL（位字段掩码：0x01）*/
#define CRG_PER_PCM_DIV_REG_CLK_PCM_EN_Pos (12UL)                   /*!< CLK_PCM_EN（位12）*/
#define CRG_PER_PCM_DIV_REG_CLK_PCM_EN_Msk (0x1000UL)               /*!< CLK_PCM_EN（位字段掩码：0x01）*/
#define CRG_PER_PCM_DIV_REG_PCM_DIV_Pos   (0UL)                     /*!< PCM_DIV（位0）*/
#define CRG_PER_PCM_DIV_REG_PCM_DIV_Msk   (0xfffUL)                 /*!< PCM_DIV（位域掩码：0xfff）*/
/* =====================================================  PCM_FDIV_REG  ====================================================== */
#define CRG_PER_PCM_FDIV_REG_PCM_FDIV_Pos (0UL)                     /*!< PCM_FDIV（位0）*/
#define CRG_PER_PCM_FDIV_REG_PCM_FDIV_Msk (0xffffUL)                /*!< PCM_FDIV（位字段掩码：0xffff）*/
/* ======================================================  PDM_DIV_REG  ====================================================== */
#define CRG_PER_PDM_DIV_REG_PDM_MASTER_MODE_Pos (9UL)               /*!< PDM_MASTER_MODE（位9）*/
#define CRG_PER_PDM_DIV_REG_PDM_MASTER_MODE_Msk (0x200UL)           /*!< PDM_MASTER_MODE（位字段掩码：0x01）*/
#define CRG_PER_PDM_DIV_REG_CLK_PDM_EN_Pos (8UL)                    /*!< CLK_PDM_EN（位8）*/
#define CRG_PER_PDM_DIV_REG_CLK_PDM_EN_Msk (0x100UL)                /*!< CLK_PDM_EN（位字段掩码：0x01）*/
#define CRG_PER_PDM_DIV_REG_PDM_DIV_Pos   (0UL)                     /*!< PDM_DIV（位0）*/
#define CRG_PER_PDM_DIV_REG_PDM_DIV_Msk   (0xffUL)                  /*!< PDM_DIV（位字段掩码：0xff）*/
/* ===================================================  RESET_CLK_PER_REG  =================================================== */
#define CRG_PER_RESET_CLK_PER_REG_MC_TRIG_DIV_Pos (8UL)             /*!< MC_TRIG_DIV（位8）*/
#define CRG_PER_RESET_CLK_PER_REG_MC_TRIG_DIV_Msk (0x1f00UL)        /*!< MC_TRIG_DIV（位域掩码：0x1f）*/
#define CRG_PER_RESET_CLK_PER_REG_MC_CLK_DIV_Pos (3UL)              /*!< MC_CLK_DIV（位3）*/
#define CRG_PER_RESET_CLK_PER_REG_MC_CLK_DIV_Msk (0xf8UL)           /*!< MC_CLK_DIV（位域掩码：0x1f）*/
#define CRG_PER_RESET_CLK_PER_REG_MC_CLK_EN_Pos (2UL)               /*!< MC_CLK_EN（位2）*/
#define CRG_PER_RESET_CLK_PER_REG_MC_CLK_EN_Msk (0x4UL)             /*!< MC_CLK_EN（位字段掩码：0x01）*/
#define CRG_PER_RESET_CLK_PER_REG_LRA_CLK_EN_Pos (1UL)              /*!< LRA_CLK_EN（位1）*/
#define CRG_PER_RESET_CLK_PER_REG_LRA_CLK_EN_Msk (0x2UL)            /*!< LRA_CLK_EN（位字段掩码：0x01）*/
#define CRG_PER_RESET_CLK_PER_REG_GPADC_CLK_SEL_Pos (0UL)           /*!< GPADC_CLK_SEL（位0）*/
#define CRG_PER_RESET_CLK_PER_REG_GPADC_CLK_SEL_Msk (0x1UL)         /*!< GPADC_CLK_SEL（位字段掩码：0x01）*/
/* ====================================================  SET_CLK_PER_REG  ==================================================== */
#define CRG_PER_SET_CLK_PER_REG_MC_TRIG_DIV_Pos (8UL)               /*!< MC_TRIG_DIV（位8）*/
#define CRG_PER_SET_CLK_PER_REG_MC_TRIG_DIV_Msk (0x1f00UL)          /*!< MC_TRIG_DIV（位域掩码：0x1f）*/
#define CRG_PER_SET_CLK_PER_REG_MC_CLK_DIV_Pos (3UL)                /*!< MC_CLK_DIV（位3）*/
#define CRG_PER_SET_CLK_PER_REG_MC_CLK_DIV_Msk (0xf8UL)             /*!< MC_CLK_DIV（位域掩码：0x1f）*/
#define CRG_PER_SET_CLK_PER_REG_MC_CLK_EN_Pos (2UL)                 /*!< MC_CLK_EN（位2）*/
#define CRG_PER_SET_CLK_PER_REG_MC_CLK_EN_Msk (0x4UL)               /*!< MC_CLK_EN（位字段掩码：0x01）*/
#define CRG_PER_SET_CLK_PER_REG_LRA_CLK_EN_Pos (1UL)                /*!< LRA_CLK_EN（位1）*/
#define CRG_PER_SET_CLK_PER_REG_LRA_CLK_EN_Msk (0x2UL)              /*!< LRA_CLK_EN（位字段掩码：0x01）*/
#define CRG_PER_SET_CLK_PER_REG_GPADC_CLK_SEL_Pos (0UL)             /*!< GPADC_CLK_SEL（位0）*/
#define CRG_PER_SET_CLK_PER_REG_GPADC_CLK_SEL_Msk (0x1UL)           /*!< GPADC_CLK_SEL（位字段掩码：0x01）*/
/* ======================================================  SRC_DIV_REG  ====================================================== */
#define CRG_PER_SRC_DIV_REG_CLK_SRC_EN_Pos (8UL)                    /*!< CLK_SRC_EN（位8）*/
#define CRG_PER_SRC_DIV_REG_CLK_SRC_EN_Msk (0x100UL)                /*!< CLK_SRC_EN（位字段掩码：0x01）*/
#define CRG_PER_SRC_DIV_REG_SRC_DIV_Pos   (0UL)                     /*!< SRC_DIV（位0）*/
#define CRG_PER_SRC_DIV_REG_SRC_DIV_Msk   (0xffUL)                  /*!< SRC_DIV（位字段掩码：0xff）*/


/* =========================================================================================================================== */
/* ================                                          CRG_SYS                                          ================ */
/* =========================================================================================================================== */

/* =====================================================  BATCHECK_REG  ====================================================== */
#define CRG_SYS_BATCHECK_REG_BATCHECK_LOAD_ENABLE_Pos (7UL)         /*!< BATCHECK_LOAD_ENABLE（位7）*/
#define CRG_SYS_BATCHECK_REG_BATCHECK_LOAD_ENABLE_Msk (0x80UL)      /*!< BATCHECK_LOAD_ENABLE（位字段掩码：0x01）*/
#define CRG_SYS_BATCHECK_REG_BATCHECK_ILOAD_Pos (4UL)               /*!< BATCHECK_ILOAD（位4）*/
#define CRG_SYS_BATCHECK_REG_BATCHECK_ILOAD_Msk (0x70UL)            /*!< BATCHECK_ILOAD（位字段掩码：0x07）*/
#define CRG_SYS_BATCHECK_REG_BATCHECK_TRIM_Pos (0UL)                /*!< BATCHECK_TRIM（位0）*/
#define CRG_SYS_BATCHECK_REG_BATCHECK_TRIM_Msk (0xfUL)              /*!< BATCHECK_TRIM（位字段掩码：0x0f）*/
/* ======================================================  CLK_SYS_REG  ====================================================== */
#define CRG_SYS_CLK_SYS_REG_CLK_CHG_EN_Pos (5UL)                    /*!< CLK_CHG_EN（位5）*/
#define CRG_SYS_CLK_SYS_REG_CLK_CHG_EN_Msk (0x20UL)                 /*!< CLK_CHG_EN（位字段掩码：0x01）*/
#define CRG_SYS_CLK_SYS_REG_LCD_RESET_REQ_Pos (4UL)                 /*!< LCD_RESET_REQ（第4位）*/
#define CRG_SYS_CLK_SYS_REG_LCD_RESET_REQ_Msk (0x10UL)              /*!< LCD_RESET_REQ（位字段掩码：0x01）*/
#define CRG_SYS_CLK_SYS_REG_LCD_CLK_SEL_Pos (1UL)                   /*!< LCD_CLK_SEL（位1）*/
#define CRG_SYS_CLK_SYS_REG_LCD_CLK_SEL_Msk (0x2UL)                 /*!< LCD_CLK_SEL（位字段掩码：0x01）*/
#define CRG_SYS_CLK_SYS_REG_LCD_ENABLE_Pos (0UL)                    /*!< LCD_ENABLE（位0）*/
#define CRG_SYS_CLK_SYS_REG_LCD_ENABLE_Msk (0x1UL)                  /*!< LCD_ENABLE（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                          CRG_TOP                                          ================ */
/* =========================================================================================================================== */

/* ====================================================  ANA_STATUS_REG  ===================================================== */
#define CRG_TOP_ANA_STATUS_REG_COMP_VBUS_HIGH_Pos (14UL)            /*!< COMP_VBUS_HIGH（位14）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBUS_HIGH_Msk (0x4000UL)        /*!< COMP_VBUS_HIGH（位字段掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBUS_LOW_Pos (13UL)             /*!< COMP_VBUS_LOW（位13）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBUS_LOW_Msk (0x2000UL)         /*!< COMP_VBUS_LOW（位字段掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBAT_HIGH_Pos (12UL)            /*!< COMP_VBAT_HIGH（位12）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBAT_HIGH_Msk (0x1000UL)        /*!< COMP_VBAT_HIGH（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBAT_LOW_Pos (11UL)             /*!< COMP_VBAT_LOW（位11）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VBAT_LOW_Msk (0x800UL)          /*!< COMP_VBAT_LOW（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VDD_OK_Pos (10UL)               /*!< COMP_VDD_OK（位10）*/
#define CRG_TOP_ANA_STATUS_REG_COMP_VDD_OK_Msk (0x400UL)            /*!< COMP_VDD_OK（位字段掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_VBUS_AVAILABLE_Pos (9UL)             /*!< VBUS_AVAILABLE（位9）*/
#define CRG_TOP_ANA_STATUS_REG_VBUS_AVAILABLE_Msk (0x200UL)         /*!< VBUS_AVAILABLE（位字段掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_BANDGAP_OK_Pos (8UL)                 /*!< BANDGAP_OK（位8）*/
#define CRG_TOP_ANA_STATUS_REG_BANDGAP_OK_Msk (0x100UL)             /*!< BANDGAP_OK（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_3V0_VBAT_OK_Pos (7UL)            /*!< LDO_3V0_VBAT_OK（位7）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_3V0_VBAT_OK_Msk (0x80UL)         /*!< LDO_3V0_VBAT_OK（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_3V0_VBUS_OK_Pos (6UL)            /*!< LDO_3V0_VBUS_OK（位6）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_3V0_VBUS_OK_Msk (0x40UL)         /*!< LDO_3V0_VBUS_OK（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_1V8P_OK_Pos (5UL)                /*!< LDO_1V8P_OK（位5）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_1V8P_OK_Msk (0x20UL)             /*!< LDO_1V8P_OK（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_1V8_OK_Pos (4UL)                 /*!< LDO_1V8_OK（位4）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_1V8_OK_Msk (0x10UL)              /*!< LDO_1V8_OK（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_RADIO_OK_Pos (3UL)               /*!< LDO_RADIO_OK（位3）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_RADIO_OK_Msk (0x8UL)             /*!< LDO_RADIO_OK（位域掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_CORE_OK_Pos (2UL)                /*!< LDO_CORE_OK（位2）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_CORE_OK_Msk (0x4UL)              /*!< LDO_CORE_OK（位字段掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_VDD_HIGH_OK_Pos (1UL)            /*!< LDO_VDD_HIGH_OK（位1）*/
#define CRG_TOP_ANA_STATUS_REG_LDO_VDD_HIGH_OK_Msk (0x2UL)          /*!< LDO_VDD_HIGH_OK（位字段掩码：0x01）*/
#define CRG_TOP_ANA_STATUS_REG_BOD_VIN_NOK_Pos (0UL)                /*!< BOD_VIN_NOK（位0）*/
#define CRG_TOP_ANA_STATUS_REG_BOD_VIN_NOK_Msk (0x1UL)              /*!< BOD_VIN_NOK（位域掩码：0x01）*/
/* ======================================================  BANDGAP_REG  ====================================================== */
#define CRG_TOP_BANDGAP_REG_BANDGAP_ENABLE_CLAMP_Pos (12UL)         /*!< BANDGAP_ENABLE_CLAMP（位12）*/
#define CRG_TOP_BANDGAP_REG_BANDGAP_ENABLE_CLAMP_Msk (0x1000UL)     /*!< BANDGAP_ENABLE_CLAMP（位字段掩码：0x01）*/
#define CRG_TOP_BANDGAP_REG_BGR_ITRIM_Pos (6UL)                     /*!< BGR_ITRIM（位6）*/
#define CRG_TOP_BANDGAP_REG_BGR_ITRIM_Msk (0xfc0UL)                 /*!< BGR_ITRIM（位域掩码：0x3f）*/
#define CRG_TOP_BANDGAP_REG_SYSRAM_LPMX_Pos (5UL)                   /*!< SYSRAM_LPMX（位5）*/
#define CRG_TOP_BANDGAP_REG_SYSRAM_LPMX_Msk (0x20UL)                /*!< SYSRAM_LPMX（位字段掩码：0x01）*/
#define CRG_TOP_BANDGAP_REG_BGR_TRIM_Pos  (0UL)                     /*!< BGR_TRIM（位0）*/
#define CRG_TOP_BANDGAP_REG_BGR_TRIM_Msk  (0x1fUL)                  /*!< BGR_TRIM（位域掩码：0x1f）*/
/* ===================================================  BIAS_VREF_SEL_REG  =================================================== */
#define CRG_TOP_BIAS_VREF_SEL_REG_BIAS_VREF_RF2_SEL_Pos (4UL)       /*!< BIAS_VREF_RF2_SEL（位4）*/
#define CRG_TOP_BIAS_VREF_SEL_REG_BIAS_VREF_RF2_SEL_Msk (0xf0UL)    /*!< BIAS_VREF_RF2_SEL（位字段掩码：0x0f）*/
#define CRG_TOP_BIAS_VREF_SEL_REG_BIAS_VREF_RF1_SEL_Pos (0UL)       /*!< BIAS_VREF_RF1_SEL（位0）*/
#define CRG_TOP_BIAS_VREF_SEL_REG_BIAS_VREF_RF1_SEL_Msk (0xfUL)     /*!< BIAS_VREF_RF1_SEL（位字段掩码：0x0f）*/
/* =====================================================  BOD_CTRL_REG  ====================================================== */
#define CRG_TOP_BOD_CTRL_REG_BOD_V14_RST_EN_Pos (16UL)              /*!< BOD_V14_RST_EN（位16）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V14_RST_EN_Msk (0x10000UL)         /*!< BOD_V14_RST_EN（位字段掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18F_RST_EN_Pos (15UL)             /*!< BOD_V18F_RST_EN（位15）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18F_RST_EN_Msk (0x8000UL)         /*!< BOD_V18F_RST_EN（位字段掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VDD_RST_EN_Pos (14UL)              /*!< BOD_VDD_RST_EN（第14位）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VDD_RST_EN_Msk (0x4000UL)          /*!< BOD_VDD_RST_EN（位字段掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18P_RST_EN_Pos (13UL)             /*!< BOD_V18P_RST_EN（第13位）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18P_RST_EN_Msk (0x2000UL)         /*!< BOD_V18P_RST_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18_RST_EN_Pos (12UL)              /*!< BOD_V18_RST_EN（位12）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18_RST_EN_Msk (0x1000UL)          /*!< BOD_V18_RST_EN（位字段掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V30_RST_EN_Pos (11UL)              /*!< BOD_V30_RST_EN（位11）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V30_RST_EN_Msk (0x800UL)           /*!< BOD_V30_RST_EN（位字段掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VBAT_RST_EN_Pos (10UL)             /*!< BOD_VBAT_RST_EN（位10）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VBAT_RST_EN_Msk (0x400UL)          /*!< BOD_VBAT_RST_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V14_EN_Pos (9UL)                   /*!< BOD_V14_EN（第9位）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V14_EN_Msk (0x200UL)               /*!< BOD_V14_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18F_EN_Pos (8UL)                  /*!< BOD_V18F_EN（位8）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18F_EN_Msk (0x100UL)              /*!< BOD_V18F_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VDD_EN_Pos (7UL)                   /*!< BOD_VDD_EN（第7位）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VDD_EN_Msk (0x80UL)                /*!< BOD_VDD_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18P_EN_Pos (6UL)                  /*!< BOD_V18P_EN（位6）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18P_EN_Msk (0x40UL)               /*!< BOD_V18P_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18_EN_Pos (5UL)                   /*!< BOD_V18_EN（位5）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V18_EN_Msk (0x20UL)                /*!< BOD_V18_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V30_EN_Pos (4UL)                   /*!< BOD_V30_EN（位4）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_V30_EN_Msk (0x10UL)                /*!< BOD_V30_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VBAT_EN_Pos (3UL)                  /*!< BOD_VBAT_EN（位3）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_VBAT_EN_Msk (0x8UL)                /*!< BOD_VBAT_EN（位域掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_STATUS_CLEAR_Pos (2UL)             /*!< BOD_STATUS_CLEAR（位2）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_STATUS_CLEAR_Msk (0x4UL)           /*!< BOD_STATUS_CLEAR（位字段掩码：0x01）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_CLK_DIV_Pos (0UL)                  /*!< BOD_CLK_DIV（位0）*/
#define CRG_TOP_BOD_CTRL_REG_BOD_CLK_DIV_Msk (0x3UL)                /*!< BOD_CLK_DIV（位域掩码：0x03）*/
/* ===================================================  BOD_LVL_CTRL0_REG  =================================================== */
#define CRG_TOP_BOD_LVL_CTRL0_REG_BOD_LVL_V18_Pos (18UL)            /*!< BOD_LVL_V18（位18）*/
#define CRG_TOP_BOD_LVL_CTRL0_REG_BOD_LVL_V18_Msk (0x7fc0000UL)     /*!< BOD_LVL_V18（位场掩码：0x1ff）*/
#define CRG_TOP_BOD_LVL_CTRL0_REG_BOD_LVL_V30_Pos (9UL)             /*!< BOD_LVL_V30（第9位）*/
#define CRG_TOP_BOD_LVL_CTRL0_REG_BOD_LVL_V30_Msk (0x3fe00UL)       /*!< BOD_LVL_V30（位域掩码：0x1ff）*/
#define CRG_TOP_BOD_LVL_CTRL0_REG_BOD_LVL_VBAT_Pos (0UL)            /*!< BOD_LVL_VBAT（位0）*/
#define CRG_TOP_BOD_LVL_CTRL0_REG_BOD_LVL_VBAT_Msk (0x1ffUL)        /*!< BOD_LVL_VBAT（位场掩码：0x1ff）*/
/* ===================================================  BOD_LVL_CTRL1_REG  =================================================== */
#define CRG_TOP_BOD_LVL_CTRL1_REG_BOD_LVL_VDD_RET_Pos (17UL)        /*!< BOD_LVL_VDD_RET（第17位）*/
#define CRG_TOP_BOD_LVL_CTRL1_REG_BOD_LVL_VDD_RET_Msk (0x1fe0000UL) /*!< BOD_LVL_VDD_RET（位字段掩码：0xff）*/
#define CRG_TOP_BOD_LVL_CTRL1_REG_BOD_LVL_VDD_ON_Pos (9UL)          /*!< BOD_LVL_VDD_ON（第9位）*/
#define CRG_TOP_BOD_LVL_CTRL1_REG_BOD_LVL_VDD_ON_Msk (0x1fe00UL)    /*!< BOD_LVL_VDD_ON（位域掩码：0xff）*/
#define CRG_TOP_BOD_LVL_CTRL1_REG_BOD_LVL_V18P_Pos (0UL)            /*!< BOD_LVL_V18P（位0）*/
#define CRG_TOP_BOD_LVL_CTRL1_REG_BOD_LVL_V18P_Msk (0x1ffUL)        /*!< BOD_LVL_V18P（位场掩码：0x1ff）*/
/* ===================================================  BOD_LVL_CTRL2_REG  =================================================== */
#define CRG_TOP_BOD_LVL_CTRL2_REG_BOD_LVL_V14_Pos (9UL)             /*!< BOD_LVL_V14（第9位）*/
#define CRG_TOP_BOD_LVL_CTRL2_REG_BOD_LVL_V14_Msk (0x3fe00UL)       /*!< BOD_LVL_V14（位域掩码：0x1ff）*/
#define CRG_TOP_BOD_LVL_CTRL2_REG_BOD_LVL_V18F_Pos (0UL)            /*!< BOD_LVL_V18F（位0）*/
#define CRG_TOP_BOD_LVL_CTRL2_REG_BOD_LVL_V18F_Msk (0x1ffUL)        /*!< BOD_LVL_V18F（位场掩码：0x1ff）*/
/* ====================================================  BOD_STATUS_REG  ===================================================== */
#define CRG_TOP_BOD_STATUS_REG_BOD_V14_Pos (6UL)                    /*!< BOD_V14（位6）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V14_Msk (0x40UL)                 /*!< BOD_V14（位域掩码：0x01）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V18F_Pos (5UL)                   /*!< BOD_V18F（位5）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V18F_Msk (0x20UL)                /*!< BOD_V18F（位域掩码：0x01）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_VDD_Pos (4UL)                    /*!< BOD_VDD（位4）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_VDD_Msk (0x10UL)                 /*!< BOD_VDD（位域掩码：0x01）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V18P_Pos (3UL)                   /*!< BOD_V18P（位3）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V18P_Msk (0x8UL)                 /*!< BOD_V18P（位域掩码：0x01）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V18_Pos (2UL)                    /*!< BOD_V18（位2）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V18_Msk (0x4UL)                  /*!< BOD_V18（位域掩码：0x01）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V30_Pos (1UL)                    /*!< BOD_V30（位1）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_V30_Msk (0x2UL)                  /*!< BOD_V30（位域掩码：0x01）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_VBAT_Pos (0UL)                   /*!< BOD_VBAT（位0）*/
#define CRG_TOP_BOD_STATUS_REG_BOD_VBAT_Msk (0x1UL)                 /*!< BOD_VBAT（位域掩码：0x01）*/
/* =====================================================  CLK_AMBA_REG  ====================================================== */
#define CRG_TOP_CLK_AMBA_REG_QSPI2_ENABLE_Pos (15UL)                /*!< QSPI2_ENABLE（第15位）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI2_ENABLE_Msk (0x8000UL)            /*!< QSPI2_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI2_DIV_Pos (13UL)                   /*!< QSPI2_DIV（第13位）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI2_DIV_Msk (0x6000UL)               /*!< QSPI2_DIV（位字段掩码：0x03）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI_ENABLE_Pos (12UL)                 /*!< QSPI_ENABLE（位12）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI_ENABLE_Msk (0x1000UL)             /*!< QSPI_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI_DIV_Pos (10UL)                    /*!< QSPI_DIV（位10）*/
#define CRG_TOP_CLK_AMBA_REG_QSPI_DIV_Msk (0xc00UL)                 /*!< QSPI_DIV（位字段掩码：0x03）*/
#define CRG_TOP_CLK_AMBA_REG_OTP_ENABLE_Pos (9UL)                   /*!< OTP_ENABLE（位9）*/
#define CRG_TOP_CLK_AMBA_REG_OTP_ENABLE_Msk (0x200UL)               /*!< OTP_ENABLE（位域掩码：0x01）*/
#define CRG_TOP_CLK_AMBA_REG_TRNG_CLK_ENABLE_Pos (8UL)              /*!< TRNG_CLK_ENABLE（位8）*/
#define CRG_TOP_CLK_AMBA_REG_TRNG_CLK_ENABLE_Msk (0x100UL)          /*!< TRNG_CLK_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_AMBA_REG_AES_CLK_ENABLE_Pos (6UL)               /*!< AES_CLK_ENABLE（位6）*/
#define CRG_TOP_CLK_AMBA_REG_AES_CLK_ENABLE_Msk (0x40UL)            /*!< AES_CLK_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_AMBA_REG_PCLK_DIV_Pos (4UL)                     /*!< PCLK_DIV（位4）*/
#define CRG_TOP_CLK_AMBA_REG_PCLK_DIV_Msk (0x30UL)                  /*!< PCLK_DIV（位字段掩码：0x03）*/
#define CRG_TOP_CLK_AMBA_REG_HCLK_DIV_Pos (0UL)                     /*!< HCLK_DIV（位0）*/
#define CRG_TOP_CLK_AMBA_REG_HCLK_DIV_Msk (0x7UL)                   /*!< HCLK_DIV（位字段掩码：0x07）*/
/* =====================================================  CLK_CTRL_REG  ====================================================== */
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_PLL96M_Pos (15UL)           /*!< RUNNING_AT_PLL96M（位15）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_PLL96M_Msk (0x8000UL)       /*!< RUNNING_AT_PLL96M（位字段掩码：0x01）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_XTAL32M_Pos (14UL)          /*!< RUNNING_AT_XTAL32M（位14）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_XTAL32M_Msk (0x4000UL)      /*!< RUNNING_AT_XTAL32M（位字段掩码：0x01）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_RC32M_Pos (13UL)            /*!< RUNNING_AT_RC32M（位13）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_RC32M_Msk (0x2000UL)        /*!< RUNNING_AT_RC32M（位字段掩码：0x01）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_LP_CLK_Pos (12UL)           /*!< RUNNING_AT_LP_CLK（位12）*/
#define CRG_TOP_CLK_CTRL_REG_RUNNING_AT_LP_CLK_Msk (0x1000UL)       /*!< RUNNING_AT_LP_CLK（位字段掩码：0x01）*/
#define CRG_TOP_CLK_CTRL_REG_USB_CLK_SRC_Pos (4UL)                  /*!< USB_CLK_SRC（位4）*/
#define CRG_TOP_CLK_CTRL_REG_USB_CLK_SRC_Msk (0x10UL)               /*!< USB_CLK_SRC（位域掩码：0x01）*/
#define CRG_TOP_CLK_CTRL_REG_LP_CLK_SEL_Pos (2UL)                   /*!< LP_CLK_SEL（位2）*/
#define CRG_TOP_CLK_CTRL_REG_LP_CLK_SEL_Msk (0xcUL)                 /*!< LP_CLK_SEL（位字段掩码：0x03）*/
#define CRG_TOP_CLK_CTRL_REG_SYS_CLK_SEL_Pos (0UL)                  /*!< SYS_CLK_SEL（位0）*/
#define CRG_TOP_CLK_CTRL_REG_SYS_CLK_SEL_Msk (0x3UL)                /*!< SYS_CLK_SEL（位字段掩码：0x03）*/
/* =====================================================  CLK_RADIO_REG  ===================================================== */
#define CRG_TOP_CLK_RADIO_REG_RFCU_ENABLE_Pos (5UL)                 /*!< RFCU_ENABLE（位5）*/
#define CRG_TOP_CLK_RADIO_REG_RFCU_ENABLE_Msk (0x20UL)              /*!< RFCU_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_SYNCH_RESET_Pos (4UL)            /*!< CMAC_SYNCH_RESET（位4）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_SYNCH_RESET_Msk (0x10UL)         /*!< CMAC_SYNCH_RESET（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_CLK_SEL_Pos (3UL)                /*!< CMAC_CLK_SEL（位3）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_CLK_SEL_Msk (0x8UL)              /*!< CMAC_CLK_SEL（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_CLK_ENABLE_Pos (2UL)             /*!< CMAC_CLK_ENABLE（位2）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_CLK_ENABLE_Msk (0x4UL)           /*!< CMAC_CLK_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_DIV_Pos (0UL)                    /*!< CMAC_DIV（位0）*/
#define CRG_TOP_CLK_RADIO_REG_CMAC_DIV_Msk (0x3UL)                  /*!< CMAC_DIV（位域掩码：0x03）*/
/* =====================================================  CLK_RC32K_REG  ===================================================== */
#define CRG_TOP_CLK_RC32K_REG_RC32K_TRIM_Pos (1UL)                  /*!< RC32K_TRIM（位1）*/
#define CRG_TOP_CLK_RC32K_REG_RC32K_TRIM_Msk (0x1eUL)               /*!< RC32K_TRIM（位字段掩码：0x0f）*/
#define CRG_TOP_CLK_RC32K_REG_RC32K_ENABLE_Pos (0UL)                /*!< RC32K_ENABLE（位0）*/
#define CRG_TOP_CLK_RC32K_REG_RC32K_ENABLE_Msk (0x1UL)              /*!< RC32K_ENABLE（位字段掩码：0x01）*/
/* =====================================================  CLK_RC32M_REG  ===================================================== */
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_RANGE_Pos (20UL)           /*!< RC32M_INIT_RANGE（位20）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_RANGE_Msk (0x300000UL)     /*!< RC32M_INIT_RANGE（位域掩码：0x03）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_DEL_Pos (12UL)             /*!< RC32M_INIT_DEL（位12）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_DEL_Msk (0xff000UL)        /*!< RC32M_INIT_DEL（位字段掩码：0xff）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_DTCF_Pos (9UL)             /*!< RC32M_INIT_DTCF（第9位）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_DTCF_Msk (0xe00UL)         /*!< RC32M_INIT_DTCF（位字段掩码：0x07）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_DTC_Pos (5UL)              /*!< RC32M_INIT_DTC（位5）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_INIT_DTC_Msk (0x1e0UL)          /*!< RC32M_INIT_DTC（位域掩码：0x0f）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_BIAS_Pos (1UL)                  /*!< RC32M_BIAS（位1）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_BIAS_Msk (0x1eUL)               /*!< RC32M_BIAS（位字段掩码：0x0f）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_ENABLE_Pos (0UL)                /*!< RC32M_ENABLE（位0）*/
#define CRG_TOP_CLK_RC32M_REG_RC32M_ENABLE_Msk (0x1UL)              /*!< RC32M_ENABLE（位字段掩码：0x01）*/
/* ======================================================  CLK_RCX_REG  ====================================================== */
#define CRG_TOP_CLK_RCX_REG_RCX_BIAS_Pos  (8UL)                     /*!< RCX_BIAS（位8）*/
#define CRG_TOP_CLK_RCX_REG_RCX_BIAS_Msk  (0xf00UL)                 /*!< RCX_BIAS（位字段掩码：0x0f）*/
#define CRG_TOP_CLK_RCX_REG_RCX_C0_Pos    (7UL)                     /*!< RCX_C0（第7位）*/
#define CRG_TOP_CLK_RCX_REG_RCX_C0_Msk    (0x80UL)                  /*!< RCX_C0（位域掩码：0x01）*/
#define CRG_TOP_CLK_RCX_REG_RCX_CADJUST_Pos (2UL)                   /*!< RCX_CADJUST（位2）*/
#define CRG_TOP_CLK_RCX_REG_RCX_CADJUST_Msk (0x7cUL)                /*!< RCX_CADJUST（位域掩码：0x1f）*/
#define CRG_TOP_CLK_RCX_REG_RCX_RADJUST_Pos (1UL)                   /*!< RCX_RADJUST（位1）*/
#define CRG_TOP_CLK_RCX_REG_RCX_RADJUST_Msk (0x2UL)                 /*!< RCX_RADJUST（位域掩码：0x01）*/
#define CRG_TOP_CLK_RCX_REG_RCX_ENABLE_Pos (0UL)                    /*!< RCX_ENABLE（位0）*/
#define CRG_TOP_CLK_RCX_REG_RCX_ENABLE_Msk (0x1UL)                  /*!< RCX_ENABLE（位字段掩码：0x01）*/
/* ====================================================  CLK_RTCDIV_REG  ===================================================== */
#define CRG_TOP_CLK_RTCDIV_REG_RTC_RESET_REQ_Pos (21UL)             /*!< RTC_RESET_REQ（第21位）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_RESET_REQ_Msk (0x200000UL)       /*!< RTC_RESET_REQ（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_ENABLE_Pos (20UL)            /*!< RTC_DIV_ENABLE（第20位）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_ENABLE_Msk (0x100000UL)      /*!< RTC_DIV_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_DENOM_Pos (19UL)             /*!< RTC_DIV_DENOM（第19位）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_DENOM_Msk (0x80000UL)        /*!< RTC_DIV_DENOM（位字段掩码：0x01）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_INT_Pos (10UL)               /*!< RTC_DIV_INT（第10位）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_INT_Msk (0x7fc00UL)          /*!< RTC_DIV_INT（位字段掩码：0x1ff）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_FRAC_Pos (0UL)               /*!< RTC_DIV_FRAC（位0）*/
#define CRG_TOP_CLK_RTCDIV_REG_RTC_DIV_FRAC_Msk (0x3ffUL)           /*!< RTC_DIV_FRAC（位域掩码：0x3ff）*/
/* ==================================================  CLK_SWITCH2XTAL_REG  ================================================== */
#define CRG_TOP_CLK_SWITCH2XTAL_REG_SWITCH2XTAL_Pos (0UL)           /*!< 开关2XTAL（位0）*/
#define CRG_TOP_CLK_SWITCH2XTAL_REG_SWITCH2XTAL_Msk (0x1UL)         /*!< SWITCH2XTAL（位域掩码：0x01）*/
/* ======================================================  CLK_TMR_REG  ====================================================== */
#define CRG_TOP_CLK_TMR_REG_TMR2_PWM_AON_MODE_Pos (2UL)             /*!< TMR2_PWM_AON_MODE（位2）*/
#define CRG_TOP_CLK_TMR_REG_TMR2_PWM_AON_MODE_Msk (0x4UL)           /*!< TMR2_PWM_AON_MODE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_TMR_REG_TMR_PWM_AON_MODE_Pos (1UL)              /*!< TMR_PWM_AON_MODE（位1）*/
#define CRG_TOP_CLK_TMR_REG_TMR_PWM_AON_MODE_Msk (0x2UL)            /*!< TMR_PWM_AON_MODE（位字段掩码：0x01）*/
#define CRG_TOP_CLK_TMR_REG_WAKEUPCT_ENABLE_Pos (0UL)               /*!< 唤醒_启用（位0）*/
#define CRG_TOP_CLK_TMR_REG_WAKEUPCT_ENABLE_Msk (0x1UL)             /*!< WAKEUPCT_ENABLE（位域掩码：0x01）*/
/* ====================================================  CLK_XTAL32K_REG  ==================================================== */
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_DISABLE_OUTPUT_Pos (9UL)    /*!< XTAL32K_DISABLE_OUTPUT（位9）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_DISABLE_OUTPUT_Msk (0x200UL) /*!< XTAL32K_DISABLE_OUTPUT（位字段掩码：0x01）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_DISABLE_AMPREG_Pos (7UL)    /*!< XTAL32K_DISABLE_AMPREG（位7）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_DISABLE_AMPREG_Msk (0x80UL) /*!< XTAL32K_DISABLE_AMPREG（位字段掩码：0x01）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_CUR_Pos (3UL)               /*!< XTAL32K_CUR（位3）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_CUR_Msk (0x78UL)            /*!< XTAL32K_CUR（位字段掩码：0x0f）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_RBIAS_Pos (1UL)             /*!< XTAL32K_RBIAS（位1）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_RBIAS_Msk (0x6UL)           /*!< XTAL32K_RBIAS（位字段掩码：0x03）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_ENABLE_Pos (0UL)            /*!< XTAL32K_ENABLE（位0）*/
#define CRG_TOP_CLK_XTAL32K_REG_XTAL32K_ENABLE_Msk (0x1UL)          /*!< XTAL32K_ENABLE（位字段掩码：0x01）*/
/* ==================================================  DISCHARGE_RAIL_REG  =================================================== */
#define CRG_TOP_DISCHARGE_RAIL_REG_RESET_V18P_Pos (2UL)             /*!< RESET_V18P（位2）*/
#define CRG_TOP_DISCHARGE_RAIL_REG_RESET_V18P_Msk (0x4UL)           /*!< RESET_V18P（位域掩码：0x01）*/
#define CRG_TOP_DISCHARGE_RAIL_REG_RESET_V18_Pos (1UL)              /*!< RESET_V18（位1）*/
#define CRG_TOP_DISCHARGE_RAIL_REG_RESET_V18_Msk (0x2UL)            /*!< RESET_V18（位字段掩码：0x01）*/
#define CRG_TOP_DISCHARGE_RAIL_REG_RESET_V14_Pos (0UL)              /*!< RESET_V14（位0）*/
#define CRG_TOP_DISCHARGE_RAIL_REG_RESET_V14_Msk (0x1UL)            /*!< RESET_V14（位字段掩码：0x01）*/
/* ================================================  LDO_VDDD_HIGH_CTRL_REG  ================================================= */
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_LOW_ZOUT_DISABLE_Pos (3UL) /*!< LDO_VDDD_HIGH_LOW_ZOUT_DISABLE（位3）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_LOW_ZOUT_DISABLE_Msk (0x8UL) /*!< LDO_VDDD_HIGH_LOW_ZOUT_DISABLE（位字段掩码：0x01）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_STATIC_LOAD_ENABLE_Pos (2UL) /*!< LDO_VDDD_HIGH_STATIC_LOAD_ENABLE（位2）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_STATIC_LOAD_ENABLE_Msk (0x4UL) /*!< LDO_VDDD_HIGH_STATIC_LOAD_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_ENABLE_Pos (1UL) /*!< LDO_VDDD_HIGH_ENABLE（位1）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_ENABLE_Msk (0x2UL) /*!< LDO_VDDD_HIGH_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_VREF_HOLD_Pos (0UL) /*!< LDO_VDDD_HIGH_VREF_HOLD（位0）*/
#define CRG_TOP_LDO_VDDD_HIGH_CTRL_REG_LDO_VDDD_HIGH_VREF_HOLD_Msk (0x1UL) /*!< LDO_VDDD_HIGH_VREF_HOLD（位字段掩码：0x01）*/
/* ===================================================  P0_PAD_LATCH_REG  ==================================================== */
#define CRG_TOP_P0_PAD_LATCH_REG_P0_LATCH_EN_Pos (0UL)              /*!< P0_LATCH_EN（位0）*/
#define CRG_TOP_P0_PAD_LATCH_REG_P0_LATCH_EN_Msk (0xffffffffUL)     /*!< P0_LATCH_EN（位域掩码：0xffffff）*/
/* ================================================  P0_RESET_PAD_LATCH_REG  ================================================= */
#define CRG_TOP_P0_RESET_PAD_LATCH_REG_P0_RESET_LATCH_EN_Pos (0UL)  /*!< P0_RESET_LATCH_EN（位0）*/
#define CRG_TOP_P0_RESET_PAD_LATCH_REG_P0_RESET_LATCH_EN_Msk (0xffffffffUL) /*!< P0_RESET_LATCH_EN（位域掩码：0xffffff）*/
/* =================================================  P0_SET_PAD_LATCH_REG  ================================================== */
#define CRG_TOP_P0_SET_PAD_LATCH_REG_P0_SET_LATCH_EN_Pos (0UL)      /*!< P0_SET_LATCH_EN（位0）*/
#define CRG_TOP_P0_SET_PAD_LATCH_REG_P0_SET_LATCH_EN_Msk (0xffffffffUL) /*!< P0_SET_LATCH_EN（位域掩码：0xffffffff）*/
/* ===================================================  P1_PAD_LATCH_REG  ==================================================== */
#define CRG_TOP_P1_PAD_LATCH_REG_P1_LATCH_EN_Pos (0UL)              /*!< P1_LATCH_EN（位0）*/
#define CRG_TOP_P1_PAD_LATCH_REG_P1_LATCH_EN_Msk (0x7fffffUL)       /*!< P1_LATCH_EN（位域掩码：0x7fffff）*/
/* ================================================  P1_RESET_PAD_LATCH_REG  ================================================= */
#define CRG_TOP_P1_RESET_PAD_LATCH_REG_P1_RESET_LATCH_EN_Pos (0UL)  /*!< P1_RESET_LATCH_EN（位0）*/
#define CRG_TOP_P1_RESET_PAD_LATCH_REG_P1_RESET_LATCH_EN_Msk (0x7fffffUL) /*!< P1_RESET_LATCH_EN（位域掩码：0x7fffff）*/
/* =================================================  P1_SET_PAD_LATCH_REG  ================================================== */
#define CRG_TOP_P1_SET_PAD_LATCH_REG_P1_SET_LATCH_EN_Pos (0UL)      /*!< P1_SET_LATCH_EN（位0）*/
#define CRG_TOP_P1_SET_PAD_LATCH_REG_P1_SET_LATCH_EN_Msk (0x7fffffUL) /*!< P1_SET_LATCH_EN（位字段掩码：0x7fffff）*/
/* =====================================================  PMU_CTRL_REG  ====================================================== */
#define CRG_TOP_PMU_CTRL_REG_ENABLE_CLKLESS_Pos (8UL)               /*!< ENABLE_CLKLESS（位8）*/
#define CRG_TOP_PMU_CTRL_REG_ENABLE_CLKLESS_Msk (0x100UL)           /*!< ENABLE_CLKLESS（位字段掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_RETAIN_CACHE_Pos (7UL)                 /*!< RETAIN_CACHE（位7）*/
#define CRG_TOP_PMU_CTRL_REG_RETAIN_CACHE_Msk (0x80UL)              /*!< RETAIN_CACHE（位字段掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_SYS_SLEEP_Pos (6UL)                    /*!< SYS_SLEEP（位6）*/
#define CRG_TOP_PMU_CTRL_REG_SYS_SLEEP_Msk (0x40UL)                 /*!< SYS_SLEEP（位字段掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_RESET_ON_WAKEUP_Pos (5UL)              /*!< RESET_ON_WAKEUP（位5）*/
#define CRG_TOP_PMU_CTRL_REG_RESET_ON_WAKEUP_Msk (0x20UL)           /*!< RESET_ON_WAKEUP（位字段掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_MAP_BANDGAP_EN_Pos (4UL)               /*!< MAP_BANDGAP_EN（位4）*/
#define CRG_TOP_PMU_CTRL_REG_MAP_BANDGAP_EN_Msk (0x10UL)            /*!< MAP_BANDGAP_EN（位域掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_COM_SLEEP_Pos (3UL)                    /*!< COM_SLEEP（位3）*/
#define CRG_TOP_PMU_CTRL_REG_COM_SLEEP_Msk (0x8UL)                  /*!< COM_SLEEP（位字段掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_TIM_SLEEP_Pos (2UL)                    /*!< TIM_SLEEP（位2）*/
#define CRG_TOP_PMU_CTRL_REG_TIM_SLEEP_Msk (0x4UL)                  /*!< TIM_SLEEP（位域掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_RADIO_SLEEP_Pos (1UL)                  /*!< RADIO_SLEEP（位1）*/
#define CRG_TOP_PMU_CTRL_REG_RADIO_SLEEP_Msk (0x2UL)                /*!< RADIO_SLEEP（位域掩码：0x01）*/
#define CRG_TOP_PMU_CTRL_REG_PERIPH_SLEEP_Pos (0UL)                 /*!< PERIPH_SLEEP（位0）*/
#define CRG_TOP_PMU_CTRL_REG_PERIPH_SLEEP_Msk (0x1UL)               /*!< PERIPH_SLEEP（位域掩码：0x01）*/
/* =====================================================  PMU_SLEEP_REG  ===================================================== */
#define CRG_TOP_PMU_SLEEP_REG_CLAMP_VDD_WKUP_MAX_Pos (18UL)         /*!< CLAMP_VDD_WKUP_MAX（位18）*/
#define CRG_TOP_PMU_SLEEP_REG_CLAMP_VDD_WKUP_MAX_Msk (0x40000UL)    /*!< CLAMP_VDD_WKUP_MAX（位字段掩码：0x01）*/
#define CRG_TOP_PMU_SLEEP_REG_ULTRA_FAST_WAKEUP_Pos (17UL)          /*!< ULTRA_FAST_WAKEUP（位17）*/
#define CRG_TOP_PMU_SLEEP_REG_ULTRA_FAST_WAKEUP_Msk (0x20000UL)     /*!< ULTRA_FAST_WAKEUP（位字段掩码：0x01）*/
#define CRG_TOP_PMU_SLEEP_REG_FAST_WAKEUP_Pos (16UL)                /*!< FAST_WAKEUP（位16）*/
#define CRG_TOP_PMU_SLEEP_REG_FAST_WAKEUP_Msk (0x10000UL)           /*!< FAST_WAKEUP（位字段掩码：0x01）*/
#define CRG_TOP_PMU_SLEEP_REG_BOD_SLEEP_INTERVAL_Pos (12UL)         /*!< BOD_SLEEP_INTERVAL（位12）*/
#define CRG_TOP_PMU_SLEEP_REG_BOD_SLEEP_INTERVAL_Msk (0xf000UL)     /*!< BOD_SLEEP_INTERVAL（位域掩码：0x0f）*/
#define CRG_TOP_PMU_SLEEP_REG_BG_REFRESH_INTERVAL_Pos (0UL)         /*!< BG_REFRESH_INTERVAL（位0）*/
#define CRG_TOP_PMU_SLEEP_REG_BG_REFRESH_INTERVAL_Msk (0xfffUL)     /*!< BG_REFRESH_INTERVAL（位字段掩码：0xfff）*/
/* =====================================================  PMU_TRIM_REG  ====================================================== */
#define CRG_TOP_PMU_TRIM_REG_LDO_1V8_TRIM_Pos (12UL)                /*!< LDO_1V8_TRIM（位12）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_1V8_TRIM_Msk (0xf000UL)            /*!< LDO_1V8_TRIM（位域掩码：0x0f）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_1V8P_TRIM_Pos (8UL)                /*!< LDO_1V8P_TRIM（位8）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_1V8P_TRIM_Msk (0xf00UL)            /*!< LDO_1V8P_TRIM（位域掩码：0x0f）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_SUPPLY_VBAT_TRIM_Pos (4UL)         /*!< LDO_SUPPLY_BAT_TRIM（位4）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_SUPPLY_VBAT_TRIM_Msk (0xf0UL)      /*!< LDO_SUPPLY_BAT_TRIM（位域掩码：0x0f）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_SUPPLY_VBUS_TRIM_Pos (0UL)         /*!< LDO_SUPPLY_VBUS_TRIM（位0）*/
#define CRG_TOP_PMU_TRIM_REG_LDO_SUPPLY_VBUS_TRIM_Msk (0xfUL)       /*!< LDO_SUPPLY_VBUS_TRIM（位字段掩码：0x0f）*/
/* ======================================================  POR_PIN_REG  ====================================================== */
#define CRG_TOP_POR_PIN_REG_POR_PIN_POLARITY_Pos (7UL)              /*!< POR_PIN_POLARITY（位7）*/
#define CRG_TOP_POR_PIN_REG_POR_PIN_POLARITY_Msk (0x80UL)           /*!< POR_PIN_POLARITY（位字段掩码：0x01）*/
#define CRG_TOP_POR_PIN_REG_POR_PIN_SELECT_Pos (0UL)                /*!< POR_PIN_SELECT（位0）*/
#define CRG_TOP_POR_PIN_REG_POR_PIN_SELECT_Msk (0x3fUL)             /*!< POR_PIN_SELECT（位域掩码：0x3f）*/
/* =====================================================  POR_TIMER_REG  ===================================================== */
#define CRG_TOP_POR_TIMER_REG_POR_TIME_Pos (0UL)                    /*!< POR_TIME（位0）*/
#define CRG_TOP_POR_TIMER_REG_POR_TIME_Msk (0x7fUL)                 /*!< POR_TIME（位域掩码：0x7f）*/
/* ===================================================  POR_VBAT_CTRL_REG  =================================================== */
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_MASK_N_Pos (13UL)        /*!< POR_VBAT_MASK_N（位13）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_MASK_N_Msk (0x2000UL)    /*!< POR_VBAT_MASK_N（位域掩码：0x01）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_ENABLE_Pos (12UL)        /*!< POR_VBAT_ENABLE（位12）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_ENABLE_Msk (0x1000UL)    /*!< POR_VBAT_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_HYST_LOW_Pos (8UL)       /*!< POR_VBAT_HYST_LOW（位8）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_HYST_LOW_Msk (0xf00UL)   /*!< POR_VBAT_HYST_LOW（位字段掩码：0x0f）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_THRES_HIGH_Pos (4UL)     /*!< POR_VBAT_THRES_HIGH（位4）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_THRES_HIGH_Msk (0xf0UL)  /*!< POR_VBAT_THRES_HIGH（位域掩码：0x0f）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_THRES_LOW_Pos (0UL)      /*!< POR_VBAT_THRES_LOW（位0）*/
#define CRG_TOP_POR_VBAT_CTRL_REG_POR_VBAT_THRES_LOW_Msk (0xfUL)    /*!< POR_VBAT_THRES_LOW（位域掩码：0x0f）*/
/* ====================================================  POWER_CTRL_REG  ===================================================== */
#define CRG_TOP_POWER_CTRL_REG_VDD_SLEEP_LEVEL_Pos (29UL)           /*!< VDD_SLEEP_LEVEL（位29）*/
#define CRG_TOP_POWER_CTRL_REG_VDD_SLEEP_LEVEL_Msk (0xe0000000UL)   /*!< VDD_SLEEP_LEVEL（位字段掩码：0x07）*/
#define CRG_TOP_POWER_CTRL_REG_VDD_CLAMP_LEVEL_Pos (25UL)           /*!< VDD_CLAMP_LEVEL（位25）*/
#define CRG_TOP_POWER_CTRL_REG_VDD_CLAMP_LEVEL_Msk (0x1e000000UL)   /*!< VDD_CLAMP_LEVEL（位字段掩码：0x0f）*/
#define CRG_TOP_POWER_CTRL_REG_CLAMP_3V0_VBAT_ENABLE_Pos (24UL)     /*!< CLAMP_3V0_VBAT_ENABLE（位24）*/
#define CRG_TOP_POWER_CTRL_REG_CLAMP_3V0_VBAT_ENABLE_Msk (0x1000000UL) /*!< CLAMP_3V0_VBAT_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_V18_LEVEL_Pos (23UL)                 /*!< V18_LEVEL（位23）*/
#define CRG_TOP_POWER_CTRL_REG_V18_LEVEL_Msk (0x800000UL)           /*!< V18_LEVEL（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_V14_LEVEL_Pos (20UL)                 /*!< V14_LEVEL（第20位）*/
#define CRG_TOP_POWER_CTRL_REG_V14_LEVEL_Msk (0x700000UL)           /*!< V14_LEVEL（位域掩码：0x07）*/
#define CRG_TOP_POWER_CTRL_REG_V30_LEVEL_Pos (18UL)                 /*!< V30_LEVEL（位18）*/
#define CRG_TOP_POWER_CTRL_REG_V30_LEVEL_Msk (0xc0000UL)            /*!< V30_LEVEL（位域掩码：0x03）*/
#define CRG_TOP_POWER_CTRL_REG_VDD_LEVEL_Pos (16UL)                 /*!< VDD_LEVEL（位16）*/
#define CRG_TOP_POWER_CTRL_REG_VDD_LEVEL_Msk (0x30000UL)            /*!< VDD_LEVEL（位字段掩码：0x03）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_REF_Pos (15UL)               /*!< LDO_3V0_REF（第15位）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_REF_Msk (0x8000UL)           /*!< LDO_3V0_REF（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_CORE_RET_ENABLE_SLEEP_Pos (14UL) /*!< LDO_CORE_RET_ENABLE_SLEEP（位14）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_CORE_RET_ENABLE_SLEEP_Msk (0x4000UL) /*!< LDO_CORE_RET_ENABLE_SLEEP（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_CORE_RET_ENABLE_ACTIVE_Pos (13UL) /*!< LDO_CORE_RET_ENABLE_ACTIVE（位13）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_CORE_RET_ENABLE_ACTIVE_Msk (0x2000UL) /*!< LDO_CORE_RET_ENABLE_ACTIVE（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_CORE_ENABLE_Pos (12UL)           /*!< LDO_CORE_ENABLE（位12）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_CORE_ENABLE_Msk (0x1000UL)       /*!< LDO_CORE_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_RET_ENABLE_SLEEP_Pos (11UL)  /*!< LDO_3V0_RET_ENABLE_SLEEP（位11）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_RET_ENABLE_SLEEP_Msk (0x800UL) /*!< LDO_3V0_RET_ENABLE_SLEEP（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_RET_ENABLE_ACTIVE_Pos (10UL) /*!< LDO_3V0_RET_ENABLE_ACTIVE（位10）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_RET_ENABLE_ACTIVE_Msk (0x400UL) /*!< LDO_3V0_RET_ENABLE_ACTIVE（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_MODE_Pos (8UL)               /*!< LDO_3V0_MODE（位8）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_3V0_MODE_Msk (0x300UL)           /*!< LDO_3V0_MODE（位域掩码：0x03）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_RADIO_ENABLE_Pos (7UL)           /*!< LDO_RADIO_ENABLE（位7）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_RADIO_ENABLE_Msk (0x80UL)        /*!< LDO_RADIO_ENABLE（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8_RET_ENABLE_SLEEP_Pos (6UL)   /*!< LDO_1V8_RET_ENABLE_SLEEP（位6）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8_RET_ENABLE_SLEEP_Msk (0x40UL) /*!< LDO_1V8_RET_ENABLE_SLEEP（位字段掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8_RET_ENABLE_ACTIVE_Pos (5UL)  /*!< LDO_1V8_RET_ENABLE_ACTIVE（位5）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8_RET_ENABLE_ACTIVE_Msk (0x20UL) /*!< LDO_1V8_RET_ENABLE_ACTIVE（位字段掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8_ENABLE_Pos (4UL)             /*!< LDO_1V8_ENABLE（位4）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8_ENABLE_Msk (0x10UL)          /*!< LDO_1V8_ENABLE（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_SW_1V8F_ENABLE_FORCE_Pos (3UL)       /*!< SW_1V8F_ENABLE_FORCE（位3）*/
#define CRG_TOP_POWER_CTRL_REG_SW_1V8F_ENABLE_FORCE_Msk (0x8UL)     /*!< SW_1V8F_ENABLE_FORCE（位字段掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8P_RET_ENABLE_SLEEP_Pos (2UL)  /*!< LDO_1V8P_RET_ENABLE_SLEEP（位2）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8P_RET_ENABLE_SLEEP_Msk (0x4UL) /*!< LDO_1V8P_RET_ENABLE_SLEEP（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8P_RET_ENABLE_ACTIVE_Pos (1UL) /*!< LDO_1V8P_RET_ENABLE_ACTIVE（位1）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8P_RET_ENABLE_ACTIVE_Msk (0x2UL) /*!< LDO_1V8P_RET_ENABLE_ACTIVE（位域掩码：0x01）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8P_ENABLE_Pos (0UL)            /*!< LDO_1V8P_ENABLE（位0）*/
#define CRG_TOP_POWER_CTRL_REG_LDO_1V8P_ENABLE_Msk (0x1UL)          /*!< LDO_1V8P_ENABLE（位域掩码：0x01）*/
/* ===================================================  RAM_PWR_CTRL_REG  ==================================================== */
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM8_PWR_CTRL_Pos (14UL)           /*!< RAM8_PWR_CTRL（位14）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM8_PWR_CTRL_Msk (0xc000UL)       /*!< RAM8_PWR_CTRL（位字段掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM7_PWR_CTRL_Pos (12UL)           /*!< RAM7_PWR_CTRL（位12）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM7_PWR_CTRL_Msk (0x3000UL)       /*!< RAM7_PWR_CTRL（位字段掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM6_PWR_CTRL_Pos (10UL)           /*!< RAM6_PWR_CTRL（位10）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM6_PWR_CTRL_Msk (0xc00UL)        /*!< RAM6_PWR_CTRL（位字段掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM5_PWR_CTRL_Pos (8UL)            /*!< RAM5_PWR_CTRL（位8）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM5_PWR_CTRL_Msk (0x300UL)        /*!< RAM5_PWR_CTRL（位域掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM4_PWR_CTRL_Pos (6UL)            /*!< RAM4_PWR_CTRL（位6）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM4_PWR_CTRL_Msk (0xc0UL)         /*!< RAM4_PWR_CTRL（位字段掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM3_PWR_CTRL_Pos (4UL)            /*!< RAM3_PWR_CTRL（位4）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM3_PWR_CTRL_Msk (0x30UL)         /*!< RAM3_PWR_CTRL（位字段掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM2_PWR_CTRL_Pos (2UL)            /*!< RAM2_PWR_CTRL（位2）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM2_PWR_CTRL_Msk (0xcUL)          /*!< RAM2_PWR_CTRL（位字段掩码：0x03）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM1_PWR_CTRL_Pos (0UL)            /*!< RAM1_PWR_CTRL（位0）*/
#define CRG_TOP_RAM_PWR_CTRL_REG_RAM1_PWR_CTRL_Msk (0x3UL)          /*!< RAM1_PWR_CTRL（位字段掩码：0x03）*/
/* ====================================================  RESET_STAT_REG  ===================================================== */
#define CRG_TOP_RESET_STAT_REG_CMAC_WDOGRESET_STAT_Pos (5UL)        /*!< CMAC_WOGRESET_STAT（位5）*/
#define CRG_TOP_RESET_STAT_REG_CMAC_WDOGRESET_STAT_Msk (0x20UL)     /*!< CMAC_WOGRESET_STAT（位字段掩码：0x01）*/
#define CRG_TOP_RESET_STAT_REG_SWD_HWRESET_STAT_Pos (4UL)           /*!< SWD_HWRESET_STAT（位4）*/
#define CRG_TOP_RESET_STAT_REG_SWD_HWRESET_STAT_Msk (0x10UL)        /*!< SWD_HWRESET_STAT（位字段掩码：0x01）*/
#define CRG_TOP_RESET_STAT_REG_WDOGRESET_STAT_Pos (3UL)             /*!< WDOGRESET_STAT（位3）*/
#define CRG_TOP_RESET_STAT_REG_WDOGRESET_STAT_Msk (0x8UL)           /*!< WDOGRESET_STAT（位字段掩码：0x01）*/
#define CRG_TOP_RESET_STAT_REG_SWRESET_STAT_Pos (2UL)               /*!< SWRESET_STAT（位2）*/
#define CRG_TOP_RESET_STAT_REG_SWRESET_STAT_Msk (0x4UL)             /*!< SWRESET_STAT（位字段掩码：0x01）*/
#define CRG_TOP_RESET_STAT_REG_HWRESET_STAT_Pos (1UL)               /*!< HWRESET_STAT（位1）*/
#define CRG_TOP_RESET_STAT_REG_HWRESET_STAT_Msk (0x2UL)             /*!< HWRESET_STAT（位字段掩码：0x01）*/
#define CRG_TOP_RESET_STAT_REG_PORESET_STAT_Pos (0UL)               /*!< PORESET_STAT（位0）*/
#define CRG_TOP_RESET_STAT_REG_PORESET_STAT_Msk (0x1UL)             /*!< PORESET_STAT（位字段掩码：0x01）*/
/* ====================================================  SECURE_BOOT_REG  ==================================================== */
#define CRG_TOP_SECURE_BOOT_REG_PROT_QSPI_KEY_READ_Pos (7UL)        /*!< PROT_QSPI_KEY_READ（位7）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_QSPI_KEY_READ_Msk (0x80UL)     /*!< PROT_QSPI_KEY_READ（位字段掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_QSPI_KEY_WRITE_Pos (6UL)       /*!< PROT_QSPI_KEY_WRITE（位6）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_QSPI_KEY_WRITE_Msk (0x40UL)    /*!< PROT_QSPI_KEY_WRITE（位域掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_AES_KEY_READ_Pos (5UL)         /*!< PROT_AES_KEY_READ（位5）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_AES_KEY_READ_Msk (0x20UL)      /*!< PROT_AES_KEY_READ（位字段掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_AES_KEY_WRITE_Pos (4UL)        /*!< PROT_AES_KEY_WRITE（位4）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_AES_KEY_WRITE_Msk (0x10UL)     /*!< PROT_AES_KEY_WRITE（位域掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_SIG_KEY_WRITE_Pos (3UL)        /*!< PROT_SIG_KEY_WRITE（位3）*/
#define CRG_TOP_SECURE_BOOT_REG_PROT_SIG_KEY_WRITE_Msk (0x8UL)      /*!< PROT_SIG_KEY_WRITE（位域掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_FORCE_CMAC_DEBUGGER_OFF_Pos (2UL)   /*!< FORCE_CMAC_DEBUGGER_OFF（位2）*/
#define CRG_TOP_SECURE_BOOT_REG_FORCE_CMAC_DEBUGGER_OFF_Msk (0x4UL) /*!< FORCE_CMAC_DEBUGGER_OFF（位字段掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_FORCE_DEBUGGER_OFF_Pos (1UL)        /*!< FORCE_DEBUGGER_OFF（位1）*/
#define CRG_TOP_SECURE_BOOT_REG_FORCE_DEBUGGER_OFF_Msk (0x2UL)      /*!< FORCE_DEBUGGER_OFF（位字段掩码：0x01）*/
#define CRG_TOP_SECURE_BOOT_REG_SECURE_BOOT_Pos (0UL)               /*!< SECURE_BOOT（位0）*/
#define CRG_TOP_SECURE_BOOT_REG_SECURE_BOOT_Msk (0x1UL)             /*!< SECURE_BOOT（位域掩码：0x01）*/
/* =====================================================  SYS_CTRL_REG  ====================================================== */
#define CRG_TOP_SYS_CTRL_REG_SW_RESET_Pos (15UL)                    /*!< SW_RESET（第15位）*/
#define CRG_TOP_SYS_CTRL_REG_SW_RESET_Msk (0x8000UL)                /*!< SW_RESET（位字段掩码：0x01）*/
#define CRG_TOP_SYS_CTRL_REG_CACHERAM_MUX_Pos (10UL)                /*!< CACHERAM_MUX（位10）*/
#define CRG_TOP_SYS_CTRL_REG_CACHERAM_MUX_Msk (0x400UL)             /*!< CACHERAM_MUX（位域掩码：0x01）*/
#define CRG_TOP_SYS_CTRL_REG_TIMEOUT_DISABLE_Pos (9UL)              /*!< TIMEOUT_DISABLE（位9）*/
#define CRG_TOP_SYS_CTRL_REG_TIMEOUT_DISABLE_Msk (0x200UL)          /*!< TIMEOUT_DISABLE（位字段掩码：0x01）*/
#define CRG_TOP_SYS_CTRL_REG_DEBUGGER_ENABLE_Pos (7UL)              /*!< DEBUGGER_ENABLE（位7）*/
#define CRG_TOP_SYS_CTRL_REG_DEBUGGER_ENABLE_Msk (0x80UL)           /*!< DEBUGGER_ENABLE（位字段掩码：0x01）*/
#define CRG_TOP_SYS_CTRL_REG_QSPI_INIT_Pos (4UL)                    /*!< QSPI_INIT（位4）*/
#define CRG_TOP_SYS_CTRL_REG_QSPI_INIT_Msk (0x10UL)                 /*!< QSPI_INIT（位字段掩码：0x01）*/
#define CRG_TOP_SYS_CTRL_REG_REMAP_INTVECT_Pos (3UL)                /*!< REMAP_INTVECT（位3）*/
#define CRG_TOP_SYS_CTRL_REG_REMAP_INTVECT_Msk (0x8UL)              /*!< REMAP_INTVECT（位域掩码：0x01）*/
#define CRG_TOP_SYS_CTRL_REG_REMAP_ADR0_Pos (0UL)                   /*!< REMAP_ADR0（位0）*/
#define CRG_TOP_SYS_CTRL_REG_REMAP_ADR0_Msk (0x7UL)                 /*!< REMAP_ADR0（位字段掩码：0x07）*/
/* =====================================================  SYS_STAT_REG  ====================================================== */
#define CRG_TOP_SYS_STAT_REG_POWER_IS_UP_Pos (13UL)                 /*!< POWER_IS_UP（位13）*/
#define CRG_TOP_SYS_STAT_REG_POWER_IS_UP_Msk (0x2000UL)             /*!< POWER_IS_UP（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_DBG_IS_ACTIVE_Pos (12UL)               /*!< DBG_IS_ACTIVE（位12）*/
#define CRG_TOP_SYS_STAT_REG_DBG_IS_ACTIVE_Msk (0x1000UL)           /*!< DBG_IS_ACTIVE（位域掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_COM_IS_UP_Pos (11UL)                   /*!< COM_IS_UP（位11）*/
#define CRG_TOP_SYS_STAT_REG_COM_IS_UP_Msk (0x800UL)                /*!< COM_IS_UP（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_COM_IS_DOWN_Pos (10UL)                 /*!< COM_IS_DOWN（位10）*/
#define CRG_TOP_SYS_STAT_REG_COM_IS_DOWN_Msk (0x400UL)              /*!< COM_IS_DOWN（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_TIM_IS_UP_Pos (9UL)                    /*!< TIM_IS_UP（位9）*/
#define CRG_TOP_SYS_STAT_REG_TIM_IS_UP_Msk (0x200UL)                /*!< TIM_IS_UP（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_TIM_IS_DOWN_Pos (8UL)                  /*!< TIM_IS_DOWN（位8）*/
#define CRG_TOP_SYS_STAT_REG_TIM_IS_DOWN_Msk (0x100UL)              /*!< TIM_IS_DOWN（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_MEM_IS_UP_Pos (7UL)                    /*!< MEM_IS_UP（位7）*/
#define CRG_TOP_SYS_STAT_REG_MEM_IS_UP_Msk (0x80UL)                 /*!< MEM_IS_UP（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_MEM_IS_DOWN_Pos (6UL)                  /*!< MEM_IS_DOWN（位6）*/
#define CRG_TOP_SYS_STAT_REG_MEM_IS_DOWN_Msk (0x40UL)               /*!< MEM_IS_DOWN（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_SYS_IS_UP_Pos (5UL)                    /*!< SYS_IS_UP（位5）*/
#define CRG_TOP_SYS_STAT_REG_SYS_IS_UP_Msk (0x20UL)                 /*!< SYS_IS_UP（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_SYS_IS_DOWN_Pos (4UL)                  /*!< SYS_IS_DOWN（位4）*/
#define CRG_TOP_SYS_STAT_REG_SYS_IS_DOWN_Msk (0x10UL)               /*!< SYS_IS_DOWN（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_PER_IS_UP_Pos (3UL)                    /*!< PER_IS_UP（位3）*/
#define CRG_TOP_SYS_STAT_REG_PER_IS_UP_Msk (0x8UL)                  /*!< PER_IS_UP（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_PER_IS_DOWN_Pos (2UL)                  /*!< PER_IS_DOWN（位2）*/
#define CRG_TOP_SYS_STAT_REG_PER_IS_DOWN_Msk (0x4UL)                /*!< PER_IS_DOWN（位字段掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_RAD_IS_UP_Pos (1UL)                    /*!< RAD_IS_UP（位1）*/
#define CRG_TOP_SYS_STAT_REG_RAD_IS_UP_Msk (0x2UL)                  /*!< RAD_IS_UP（位域掩码：0x01）*/
#define CRG_TOP_SYS_STAT_REG_RAD_IS_DOWN_Pos (0UL)                  /*!< RAD_IS_DOWN（位0）*/
#define CRG_TOP_SYS_STAT_REG_RAD_IS_DOWN_Msk (0x1UL)                /*!< RAD_IS_DOWN（位域掩码：0x01）*/
/* ==================================================  VBUS_IRQ_CLEAR_REG  =================================================== */
#define CRG_TOP_VBUS_IRQ_CLEAR_REG_VBUS_IRQ_CLEAR_Pos (0UL)         /*!< VBUS_IRQ_CLEAR（位0）*/
#define CRG_TOP_VBUS_IRQ_CLEAR_REG_VBUS_IRQ_CLEAR_Msk (0xffffUL)    /*!< VBUS_IRQ_CLEAR（位字段掩码：0xffff）*/
/* ===================================================  VBUS_IRQ_MASK_REG  =================================================== */
#define CRG_TOP_VBUS_IRQ_MASK_REG_VBUS_IRQ_EN_RISE_Pos (1UL)        /*!< VBUS_IRQ_EN_RISE（位1）*/
#define CRG_TOP_VBUS_IRQ_MASK_REG_VBUS_IRQ_EN_RISE_Msk (0x2UL)      /*!< VBUS_IRQ_EN_RISE（位字段掩码：0x01）*/
#define CRG_TOP_VBUS_IRQ_MASK_REG_VBUS_IRQ_EN_FALL_Pos (0UL)        /*!< VBUS_IRQ_EN_FALL（位0）*/
#define CRG_TOP_VBUS_IRQ_MASK_REG_VBUS_IRQ_EN_FALL_Msk (0x1UL)      /*!< VBUS_IRQ_EN_FALL（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                         CRG_XTAL                                          ================ */
/* =========================================================================================================================== */

/* ===================================================  CLK_FREQ_TRIM_REG  =================================================== */
#define CRG_XTAL_CLK_FREQ_TRIM_REG_XTAL32M_START_Pos (20UL)         /*!< XTAL32M_START（位20）*/
#define CRG_XTAL_CLK_FREQ_TRIM_REG_XTAL32M_START_Msk (0x3ff00000UL) /*!< XTAL32M_START（位字段掩码：0x3ff）*/
#define CRG_XTAL_CLK_FREQ_TRIM_REG_XTAL32M_RAMP_Pos (10UL)          /*!< XTAL32M_RAMP（位10）*/
#define CRG_XTAL_CLK_FREQ_TRIM_REG_XTAL32M_RAMP_Msk (0xffc00UL)     /*!< XTAL32M_RAMP（位字段掩码：0x3ff）*/
#define CRG_XTAL_CLK_FREQ_TRIM_REG_XTAL32M_TRIM_Pos (0UL)           /*!< XTAL32M_TRIM（位0）*/
#define CRG_XTAL_CLK_FREQ_TRIM_REG_XTAL32M_TRIM_Msk (0x3ffUL)       /*!< XTAL32M_TRIM（位字段掩码：0x3ff）*/
/* ===================================================  PLL_SYS_CTRL1_REG  =================================================== */
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_SEL_MIN_CUR_INT_Pos (14UL)   /*!< PLL_SEL_MIN_CUR_INT（位14）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_SEL_MIN_CUR_INT_Msk (0x4000UL) /*!< PLL_SEL_MIN_CUR_INT（位字段掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_PRE_DIV_Pos (11UL)           /*!< PLL_PRE_DIV（位11）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_PRE_DIV_Msk (0x800UL)        /*!< PLL_PRE_DIV（位域掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_N_DIV_Pos (4UL)              /*!< PLL_N_DIV（位4）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_N_DIV_Msk (0x7f0UL)          /*!< PLL_N_DIV（位字段掩码：0x7f）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_LDO_PLL_VREF_HOLD_Pos (3UL)      /*!< LDO_PLL_VREF_HOLD（位3）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_LDO_PLL_VREF_HOLD_Msk (0x8UL)    /*!< LDO_PLL_VREF_HOLD（位字段掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_LDO_PLL_ENABLE_Pos (2UL)         /*!< LDO_PLL_ENABLE（位2）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_LDO_PLL_ENABLE_Msk (0x4UL)       /*!< LDO_PLL_ENABLE（位字段掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_EN_Pos (1UL)                 /*!< PLL_EN（位1）*/
#define CRG_XTAL_PLL_SYS_CTRL1_REG_PLL_EN_Msk (0x2UL)               /*!< PLL_EN（位域掩码：0x01）*/
/* ===================================================  PLL_SYS_CTRL2_REG  =================================================== */
#define CRG_XTAL_PLL_SYS_CTRL2_REG_PLL_RECALIB_Pos (15UL)           /*!< PLL_RECALIB（位15）*/
#define CRG_XTAL_PLL_SYS_CTRL2_REG_PLL_RECALIB_Msk (0x8000UL)       /*!< PLL_RECALIB（位字段掩码：0x01）*/
/* ===================================================  PLL_SYS_CTRL3_REG  =================================================== */
#define CRG_XTAL_PLL_SYS_CTRL3_REG_PLL_TEST_VCTR_Pos (7UL)          /*!< PLL_TEST_VCTR（位7）*/
#define CRG_XTAL_PLL_SYS_CTRL3_REG_PLL_TEST_VCTR_Msk (0x80UL)       /*!< PLL_TEST_VCTR（位字段掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_CTRL3_REG_PLL_MIN_CURRENT_Pos (1UL)        /*!< PLL_MIN_CURRENT（位1）*/
#define CRG_XTAL_PLL_SYS_CTRL3_REG_PLL_MIN_CURRENT_Msk (0x7eUL)     /*!< PLL_MIN_CURRENT（位域掩码：0x3f）*/
/* ==================================================  PLL_SYS_STATUS_REG  =================================================== */
#define CRG_XTAL_PLL_SYS_STATUS_REG_LDO_PLL_OK_Pos (15UL)           /*!< LDO_PLL_OK（位15）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_LDO_PLL_OK_Msk (0x8000UL)       /*!< LDO_PLL_OK（位字段掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_PLL_CALIBRATION_END_Pos (11UL)  /*!< PLL_CALIBRION_END（位11）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_PLL_CALIBRATION_END_Msk (0x800UL) /*!< PLL_CALIBRION_END（位字段掩码：0x01）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_PLL_BEST_MIN_CUR_Pos (5UL)      /*!< PLL_BEST_MIN_CUR（位5）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_PLL_BEST_MIN_CUR_Msk (0x7e0UL)  /*!< PLL_BEST_MIN_CUR（位域掩码：0x3f）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_PLL_LOCK_FINE_Pos (0UL)         /*!< PLL_LOCK_FINE（位0）*/
#define CRG_XTAL_PLL_SYS_STATUS_REG_PLL_LOCK_FINE_Msk (0x1UL)       /*!< PLL_LOCK_FINE（位字段掩码：0x01）*/
/* =====================================================  TRIM_CTRL_REG  ===================================================== */
#define CRG_XTAL_TRIM_CTRL_REG_XTAL_SETTLE_N_Pos (8UL)              /*!< XTAL_SETTLE_N（位8）*/
#define CRG_XTAL_TRIM_CTRL_REG_XTAL_SETTLE_N_Msk (0x3f00UL)         /*!< XTAL_SETTLE_N（位字段掩码：0x3f）*/
#define CRG_XTAL_TRIM_CTRL_REG_XTAL_TRIM_SELECT_Pos (6UL)           /*!< XTAL_TRIM_SELECT（位6）*/
#define CRG_XTAL_TRIM_CTRL_REG_XTAL_TRIM_SELECT_Msk (0xc0UL)        /*!< XTAL_TRIM_SELECT（位字段掩码：0x03）*/
#define CRG_XTAL_TRIM_CTRL_REG_XTAL_COUNT_N_Pos (0UL)               /*!< XTAL_COUNT_N（位0）*/
#define CRG_XTAL_TRIM_CTRL_REG_XTAL_COUNT_N_Msk (0x3fUL)            /*!< XTAL_COUNT_N（位域掩码：0x3f）*/
/* ===================================================  XTAL32M_CTRL0_REG  =================================================== */
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_DXTAL_SYSPLL_ENABLE_Pos (30UL) /*!< XTAL32M_DXTAL_SYSPLL_ENABLE（位30）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_DXTAL_SYSPLL_ENABLE_Msk (0x40000000UL) /*!< XTAL32M_DXTAL_SYSPLL_ENABLE（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_CORE_CUR_SET_Pos (15UL)  /*!< XTAL32M_CORE_CUR_SET（位15）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_CORE_CUR_SET_Msk (0x38000UL) /*!< XTAL32M_CORE_CUR_SET（位字段掩码：0x07）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_RCOSC_CALIBRATE_Pos (3UL) /*!< XTAL32M_RCOSC_CALIBRATE（位3）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_RCOSC_CALIBRATE_Msk (0x8UL) /*!< XTAL32M_RCOSC_CALIBRATE（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_RCOSC_XTAL_DRIVE_Pos (1UL) /*!< XTAL32M_RCOSC_XTAL_DRIVE（位1）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_RCOSC_XTAL_DRIVE_Msk (0x2UL) /*!< XTAL32M_RCOSC_XTAL_DRIVE（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_CXCOMP_ENABLE_Pos (0UL)  /*!< XTAL32M_CXCOMP_ENABLE（位0）*/
#define CRG_XTAL_XTAL32M_CTRL0_REG_XTAL32M_CXCOMP_ENABLE_Msk (0x1UL) /*!< XTAL32M_CXCOMP_ENABLE（位字段掩码：0x01）*/
/* ===================================================  XTAL32M_CTRL1_REG  =================================================== */
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TDISCHARGE_Pos (28UL) /*!< XTAL32M_STARTUP_DISCHARGE（位28）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TDISCHARGE_Msk (0x70000000UL) /*!< XTAL32M_STARTUP_DISCHARGE（位字段掩码：0x07）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TSETTLE_Pos (24UL) /*!< XTAL32M_STARTUP_SETTLE（位24）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TSETTLE_Msk (0x7000000UL) /*!< XTAL32M_STARTUP_SETTLE（位字段掩码：0x07）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_XTAL_ENABLE_Pos (23UL)   /*!< XTAL32M_XTAL_ENABLE（位23）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_XTAL_ENABLE_Msk (0x800000UL) /*!< XTAL32M_XTAL_ENABLE（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TDRIVE_LSB_Pos (13UL) /*!< XTAL32M_STARTUP_TDRIVE_LSB（第13位）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TDRIVE_LSB_Msk (0x7fe000UL) /*!< XTAL32M_STARTUP_DRIVE_LSB（位字段掩码：0x3ff）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_DRIVE_CYCLES_Pos (8UL)   /*!< XTAL32M_DRIVE_CYCLES（位8）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_DRIVE_CYCLES_Msk (0x1f00UL) /*!< XTAL32M_DRIVE_CYCLES（位域掩码：0x1f）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TDRIVE_Pos (5UL) /*!< XTAL32M_STARTUP_TDRIVE（位5）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_STARTUP_TDRIVE_Msk (0xe0UL) /*!< XTAL32M_STARTUP_TDRIVE（位域掩码：0x07）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_RCOSC_SYNC_DELAY_TRIM_Pos (0UL) /*!< XTAL32M_RCOSC_SYNC_DELAY_TRIM（位0）*/
#define CRG_XTAL_XTAL32M_CTRL1_REG_XTAL32M_RCOSC_SYNC_DELAY_TRIM_Msk (0x1fUL) /*!< XTAL32M_RCOSC_SYNC_DELAY_TRIM（位字段掩码：0x1f）*/
/* ===================================================  XTAL32M_CTRL2_REG  =================================================== */
#define CRG_XTAL_XTAL32M_CTRL2_REG_XTAL32M_RCOSC_TRIM_SNS_Pos (14UL) /*!< XTAL32M_RCOSC_TRIM_NS（位14）*/
#define CRG_XTAL_XTAL32M_CTRL2_REG_XTAL32M_RCOSC_TRIM_SNS_Msk (0x3fc000UL) /*!< XTAL32M_RCOSC_TRIM_NS（位字段掩码：0xff）*/
#define CRG_XTAL_XTAL32M_CTRL2_REG_XTAL32M_CXCOMP_PHI_TRIM_Pos (12UL) /*!< XTAL32M_CXCOMP_PHI_TRIM（位12）*/
#define CRG_XTAL_XTAL32M_CTRL2_REG_XTAL32M_CXCOMP_PHI_TRIM_Msk (0x3000UL) /*!< XTAL32M_CXCOMP_PHI_TRIM（位字段掩码：0x03）*/
#define CRG_XTAL_XTAL32M_CTRL2_REG_XTAL32M_CXCOMP_TRIM_CAP_Pos (3UL) /*!< XTAL32M_CXCOMP_TRIM_CAP（位3）*/
#define CRG_XTAL_XTAL32M_CTRL2_REG_XTAL32M_CXCOMP_TRIM_CAP_Msk (0xff8UL) /*!< XTAL32M_CXCOMP_TRIM_CAP（位字段掩码：0x1ff）*/
/* ===================================================  XTAL32M_CTRL3_REG  =================================================== */
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_RCOSC_TRIM_STROBE_Pos (30UL) /*!< XTAL32M_RCOSC_TRIM_STROBE（位30）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_RCOSC_TRIM_STROBE_Msk (0x40000000UL) /*!< XTAL32M_RCOSC_TRIM_STROBE（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_FREQ_DET_START_Pos (22UL) /*!< XTAL32M_FREQ_DET_START（位22）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_FREQ_DET_START_Msk (0x400000UL) /*!< XTAL32M_FREQ_DET_START（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_SW_CTRL_MODE_Pos (18UL)  /*!< XTAL32M_SW_CTRL_MODE（位18）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_SW_CTRL_MODE_Msk (0x40000UL) /*!< XTAL32M_SW_CTRL_MODE（位字段掩码：0x01）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_RCOSC_BAND_SELECT_Pos (14UL) /*!< XTAL32M_RCOSC_BAND_SELECT（位14）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_RCOSC_BAND_SELECT_Msk (0x3c000UL) /*!< XTAL32M_RCOSC_BAND_SELECT（位字段掩码：0x0f）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_RCOSC_TRIM_Pos (4UL)     /*!< XTAL32M_RCOSC_TRIM（位4）*/
#define CRG_XTAL_XTAL32M_CTRL3_REG_XTAL32M_RCOSC_TRIM_Msk (0x3ff0UL) /*!< XTAL32M_RCOSC_TRIM（位字段掩码：0x3ff）*/
/* ===================================================  XTAL32M_CTRL4_REG  =================================================== */
/* ===================================================  XTAL32M_STAT0_REG  =================================================== */
#define CRG_XTAL_XTAL32M_STAT0_REG_XTAL32M_RCOSC_BAND_SELECT_STAT_Pos (28UL) /*!< XTAL32M_RCOSC_BAND_SELECT_STAT（位28）*/
#define CRG_XTAL_XTAL32M_STAT0_REG_XTAL32M_RCOSC_BAND_SELECT_STAT_Msk (0xf0000000UL) /*!< XTAL32M_RCOSC_BAND_SELECT_STAT（位字段掩码：0x0f）*/
#define CRG_XTAL_XTAL32M_STAT0_REG_XTAL32M_RCOSC_CALIBRATION_DONE_Pos (15UL) /*!< XTAL32M_RCOSC_CALIBRATION_DONE（位15）*/
#define CRG_XTAL_XTAL32M_STAT0_REG_XTAL32M_RCOSC_CALIBRATION_DONE_Msk (0x8000UL) /*!< XTAL32M_RCOSC_CALIBRATION_DONE（位字段掩码：0x01）*/
/* ===================================================  XTAL32M_STAT1_REG  =================================================== */
#define CRG_XTAL_XTAL32M_STAT1_REG_XTAL32M_CAL_STATE_Pos (4UL)      /*!< XTAL32M_CAL_STATE（位4）*/
#define CRG_XTAL_XTAL32M_STAT1_REG_XTAL32M_CAL_STATE_Msk (0xf0UL)   /*!< XTAL32M_CAL_STATE（位字段掩码：0x0f）*/
#define CRG_XTAL_XTAL32M_STAT1_REG_XTAL32M_STATE_Pos (0UL)          /*!< XTAL32M_STATE（位0）*/
#define CRG_XTAL_XTAL32M_STAT1_REG_XTAL32M_STATE_Msk (0xfUL)        /*!< XTAL32M_STATE（位字段掩码：0x0f）*/
/* ===================================================  XTALRDY_CTRL_REG  ==================================================== */
#define CRG_XTAL_XTALRDY_CTRL_REG_XTALRDY_CLK_SEL_Pos (8UL)         /*!< XTALRDY_CLK_SEL（位8）*/
#define CRG_XTAL_XTALRDY_CTRL_REG_XTALRDY_CLK_SEL_Msk (0x100UL)     /*!< XTALRDY_CLK_SEL（位字段掩码：0x01）*/
#define CRG_XTAL_XTALRDY_CTRL_REG_XTALRDY_CNT_Pos (0UL)             /*!< XTALRDY_CNT（位0）*/
#define CRG_XTAL_XTALRDY_CTRL_REG_XTALRDY_CNT_Msk (0xffUL)          /*!< XTALRDY_CNT（位字段掩码：0xff）*/
/* ===================================================  XTALRDY_STAT_REG  ==================================================== */
#define CRG_XTAL_XTALRDY_STAT_REG_XTALRDY_COUNT_Pos (8UL)           /*!< XTALRDY_COUNT（位8）*/
#define CRG_XTAL_XTALRDY_STAT_REG_XTALRDY_COUNT_Msk (0xff00UL)      /*!< XTALRDY_COUNT（位字段掩码：0xff）*/
#define CRG_XTAL_XTALRDY_STAT_REG_XTALRDY_STAT_Pos (0UL)            /*!< XTALRDY_STAT（位0）*/
#define CRG_XTAL_XTALRDY_STAT_REG_XTALRDY_STAT_Msk (0xffUL)         /*!< XTALRDY_STAT（位字段掩码：0xff）*/


/* =========================================================================================================================== */
/* ================                                           DCDC                                            ================ */
/* =========================================================================================================================== */

/* ====================================================  DCDC_CTRL1_REG  ===================================================== */
#define DCDC_DCDC_CTRL1_REG_DCDC_SH_ENABLE_Pos (31UL)               /*!< DCDC_SH_ENABLE（第31位）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_SH_ENABLE_Msk (0x80000000UL)       /*!< DCDC_SH_ENABLE（位字段掩码：0x01）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_STARTUP_DELAY_Pos (26UL)           /*!< DCDC_STARTUP_DELAY（第26位）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_STARTUP_DELAY_Msk (0x7c000000UL)   /*!< DCDC_STARTUP_DELAY（位字段掩码：0x1f）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_IDLE_MAX_FAST_DOWNRAMP_Pos (20UL)  /*!< DCDC_IDLE_MAX_FAST_DOWSRAMP（位20）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_IDLE_MAX_FAST_DOWNRAMP_Msk (0x3f00000UL) /*!< DCDC_IDLE_MAX_FAST_DOWSRAMP（位域掩码：0x3f）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_SW_TIMEOUT_Pos (15UL)              /*!< DCDC_SW_TIMEOUT（第15位）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_SW_TIMEOUT_Msk (0xf8000UL)         /*!< DCDC_SW_TIMEOUT（位字段掩码：0x1f）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_FAST_STARTUP_Pos (14UL)            /*!< DCDC_FAST_STARTUP（位14）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_FAST_STARTUP_Msk (0x4000UL)        /*!< DCDC_FAST_STARTUP（位字段掩码：0x01）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_MAN_LV_MODE_Pos (13UL)             /*!< DCDC_MAN_LV_MODE（第13位）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_MAN_LV_MODE_Msk (0x2000UL)         /*!< DCDC_MAN_LV_MODE（位字段掩码：0x01）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_AUTO_LV_MODE_Pos (12UL)            /*!< DCDC_AUTO_LV_MODE（位12）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_AUTO_LV_MODE_Msk (0x1000UL)        /*!< DCDC_AUTO_LV_MODE（位域掩码：0x01）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_IDLE_CLK_DIV_Pos (10UL)            /*!< DCDC_IDLE_CLK_DIV（位10）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_IDLE_CLK_DIV_Msk (0xc00UL)         /*!< DCDC_IDLE_CLK_DIV（位字段掩码：0x03）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_PRIORITY_Pos (2UL)                 /*!< DCDC_PRIORITY（位2）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_PRIORITY_Msk (0x3fcUL)             /*!< DCDC_PRIORITY（位域掩码：0xff）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_FW_ENABLE_Pos (1UL)                /*!< DCDC_FW_ENABLE（位1）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_FW_ENABLE_Msk (0x2UL)              /*!< DCDC_FW_ENABLE（位字段掩码：0x01）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_ENABLE_Pos (0UL)                   /*!< DCDC_ENABLE（位0）*/
#define DCDC_DCDC_CTRL1_REG_DCDC_ENABLE_Msk (0x1UL)                 /*!< DCDC_ENABLE（位字段掩码：0x01）*/
/* ====================================================  DCDC_CTRL2_REG  ===================================================== */
#define DCDC_DCDC_CTRL2_REG_DCDC_V_NOK_CNT_MAX_Pos (24UL)           /*!< DCDC_V_NOK_CNT_MAX（位24）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_V_NOK_CNT_MAX_Msk (0xf000000UL)    /*!< DCDC_V_NOK_CNT_MAX（位字段掩码：0x0f）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_N_COMP_TRIM_MAN_Pos (22UL)         /*!< DCDC_N_COMP_TRIM_MAN（第22位）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_N_COMP_TRIM_MAN_Msk (0x400000UL)   /*!< DCDC_N_COMP_TRIM_MAN（位域掩码：0x01）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_N_COMP_TRIM_VAL_Pos (16UL)         /*!< DCDC_N_COMP_TRIM_VAL（第16位）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_N_COMP_TRIM_VAL_Msk (0x3f0000UL)   /*!< DCDC_N_COMP_TRIM_VAL（位域掩码：0x3f）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_TIMEOUT_IRQ_TRIG_Pos (12UL)        /*!< DCDC_TIMEOUT_IRQ_TRIG（第12位）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_TIMEOUT_IRQ_TRIG_Msk (0xf000UL)    /*!< DCDC_TIMEOUT_IRQ_TRIG（位字段掩码：0x0f）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_TIMEOUT_IRQ_RES_Pos (8UL)          /*!< DCDC_TIMEOUT_IRQ_RES（位8）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_TIMEOUT_IRQ_RES_Msk (0xf00UL)      /*!< DCDC_TIMEOUT_IRQ_RES（位字段掩码：0x0f）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_SLOPE_CONTROL_Pos (6UL)            /*!< DCDC_SLOPE_CONTROL（位6）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_SLOPE_CONTROL_Msk (0xc0UL)         /*!< DCDC_SLOPE_CONTROL（位域掩码：0x03）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_VBTSTRP_TRIM_Pos (4UL)             /*!< DCDC_VBTSTRP_TRIM（位4）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_VBTSTRP_TRIM_Msk (0x30UL)          /*!< DCDC_VBTSTRP_TRIM（位字段掩码：0x03）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_LSSUP_TRIM_Pos (2UL)               /*!< DCDC_LSSUP_TRIM（位2）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_LSSUP_TRIM_Msk (0xcUL)             /*!< DCDC_LSSUP_TRIM（位字段掩码：0x03）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_HSGND_TRIM_Pos (0UL)               /*!< DCDC_HSGND_TRIM（位0）*/
#define DCDC_DCDC_CTRL2_REG_DCDC_HSGND_TRIM_Msk (0x3UL)             /*!< DCDC_HSGND_TRIM（位字段掩码：0x03）*/
/* ==================================================  DCDC_IRQ_CLEAR_REG  =================================================== */
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_LOW_VBAT_IRQ_CLEAR_Pos (4UL)   /*!< DCDC_LOW_VBAT_IRQ_CLEAR（位4）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_LOW_VBAT_IRQ_CLEAR_Msk (0x10UL) /*!< DCDC_LOW_VBAT_IRQ_CLEAR（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_V18P_TIMEOUT_IRQ_CLEAR_Pos (3UL) /*!< DCDC_V18P_TIMEOUT_IRQ_CLEAR（位3）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_V18P_TIMEOUT_IRQ_CLEAR_Msk (0x8UL) /*!< DCDC_V18P_TIMEOUT_IRQ_CLEAR（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_VDD_TIMEOUT_IRQ_CLEAR_Pos (2UL) /*!< DCDC_VDD_TIMEOUT_IRQ_CLEAR（位2）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_VDD_TIMEOUT_IRQ_CLEAR_Msk (0x4UL) /*!< DCDC_VDD_TIMEOUT_IRQ_CLEAR（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_V18_TIMEOUT_IRQ_CLEAR_Pos (1UL) /*!< DCDC_V18_TIMEOUT_IRQ_CLEAR（位1）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_V18_TIMEOUT_IRQ_CLEAR_Msk (0x2UL) /*!< DCDC_V18_TIMEOUT_IRQ_CLEAR（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_V14_TIMEOUT_IRQ_CLEAR_Pos (0UL) /*!< DCDC_V14_TIMEOUT_IRQ_CLEAR（位0）*/
#define DCDC_DCDC_IRQ_CLEAR_REG_DCDC_V14_TIMEOUT_IRQ_CLEAR_Msk (0x1UL) /*!< DCDC_V14_TIMEOUT_IRQ_CLEAR（位字段掩码：0x01）*/
/* ===================================================  DCDC_IRQ_MASK_REG  =================================================== */
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_LOW_VBAT_IRQ_MASK_Pos (4UL)     /*!< DCDC_LOW_VBAT_IRQ_MASK（位4）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_LOW_VBAT_IRQ_MASK_Msk (0x10UL)  /*!< DCDC_LOW_VBAT_IRQ_MASK（位域掩码：0x01）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_V18P_TIMEOUT_IRQ_MASK_Pos (3UL) /*!< DCDC_V18P_TIMEOUT_IRQ_MASK（位3）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_V18P_TIMEOUT_IRQ_MASK_Msk (0x8UL) /*!< DCDC_V18P_TIMEOUT_IRQ_MASK（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_VDD_TIMEOUT_IRQ_MASK_Pos (2UL)  /*!< DCDC_VDD_TIMEOUT_IRQ_MASK（位2）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_VDD_TIMEOUT_IRQ_MASK_Msk (0x4UL) /*!< DCDC_VDD_TIMEOUT_IRQ_MASK（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_V18_TIMEOUT_IRQ_MASK_Pos (1UL)  /*!< DCDC_V18_TIMEOUT_IRQ_MASK（位1）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_V18_TIMEOUT_IRQ_MASK_Msk (0x2UL) /*!< DCDC_V18_TIMEOUT_IRQ_MASK（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_V14_TIMEOUT_IRQ_MASK_Pos (0UL)  /*!< DCDC_V14_TIMEOUT_IRQ_MASK（位0）*/
#define DCDC_DCDC_IRQ_MASK_REG_DCDC_V14_TIMEOUT_IRQ_MASK_Msk (0x1UL) /*!< DCDC_V14_TIMEOUT_IRQ_MASK（位字段掩码：0x01）*/
/* ==================================================  DCDC_IRQ_STATUS_REG  ================================================== */
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_LOW_VBAT_IRQ_STATUS_Pos (4UL) /*!< DCDC_LOW_VBAT_IRQ_STATUS（位4）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_LOW_VBAT_IRQ_STATUS_Msk (0x10UL) /*!< DCDC_LOW_VBAT_IRQ_STATUS（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_V18P_TIMEOUT_IRQ_STATUS_Pos (3UL) /*!< DCDC_V18P_TIMEOUT_IRQ_STATUS（位3）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_V18P_TIMEOUT_IRQ_STATUS_Msk (0x8UL) /*!< DCDC_V18P_TIMEOUT_IRQ_STATUS（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_VDD_TIMEOUT_IRQ_STATUS_Pos (2UL) /*!< DCDC_VDD_TIMEOUT_IRQ_STATUS（位2）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_VDD_TIMEOUT_IRQ_STATUS_Msk (0x4UL) /*!< DCDC_VDD_TIMEOUT_IRQ_STATUS（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_V18_TIMEOUT_IRQ_STATUS_Pos (1UL) /*!< DCDC_V18_TIMEOUT_IRQ_STATUS（位1）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_V18_TIMEOUT_IRQ_STATUS_Msk (0x2UL) /*!< DCDC_V18_TIMEOUT_IRQ_STATUS（位字段掩码：0x01）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_V14_TIMEOUT_IRQ_STATUS_Pos (0UL) /*!< DCDC_V14_TIMEOUT_IRQ_STATUS（位0）*/
#define DCDC_DCDC_IRQ_STATUS_REG_DCDC_V14_TIMEOUT_IRQ_STATUS_Msk (0x1UL) /*!< DCDC_V14_TIMEOUT_IRQ_STATUS（位字段掩码：0x01）*/
/* ===================================================  DCDC_STATUS1_REG  ==================================================== */
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_AVAILABLE_Pos (27UL)        /*!< DCDC_V18P_AVAILABLE（第27位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_AVAILABLE_Msk (0x8000000UL) /*!< DCDC_V18P_AVAILABLE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_AVAILABLE_Pos (26UL)         /*!< DCDC_VDD_AVAILABLE（位26）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_AVAILABLE_Msk (0x4000000UL)  /*!< DCDC_VDD_AVAILABLE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_AVAILABLE_Pos (25UL)         /*!< DCDC_V18_AVAILABLE（位25）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_AVAILABLE_Msk (0x2000000UL)  /*!< DCDC_V18_AVAILABLE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_AVAILABLE_Pos (24UL)         /*!< DCDC_V14_AVAILABLE（位24）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_AVAILABLE_Msk (0x1000000UL)  /*!< DCDC_V14_AVAILABLE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_COMP_OK_Pos (23UL)          /*!< DCDC_V18P_COMP_OK（位23）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_COMP_OK_Msk (0x800000UL)    /*!< DCDC_V18P_COMP_OK（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_COMP_OK_Pos (22UL)           /*!< DCDC_VDD_COMP_OK（第22位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_COMP_OK_Msk (0x400000UL)     /*!< DCDC_VDD_COMP_OK（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_COMP_OK_Pos (21UL)           /*!< DCDC_V18_COMP_OK（第21位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_COMP_OK_Msk (0x200000UL)     /*!< DCDC_V18_COMP_OK（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_COMP_OK_Pos (20UL)           /*!< DCDC_V14_COMP_OK（位20）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_COMP_OK_Msk (0x100000UL)     /*!< DCDC_V14_COMP_OK（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_COMP_NOK_Pos (19UL)         /*!< DCDC_V18P_COMP_NOK（位19）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_COMP_NOK_Msk (0x80000UL)    /*!< DCDC_V18P_COMP_NOK（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_COMP_NOK_Pos (18UL)          /*!< DCDC_VDD_COMP_NOK（第18位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_COMP_NOK_Msk (0x40000UL)     /*!< DCDC_VDD_COMP_NOK（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_COMP_NOK_Pos (17UL)          /*!< DCDC_V18_COMP_NOK（第17位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_COMP_NOK_Msk (0x20000UL)     /*!< DCDC_V18_COMP_NOK（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_COMP_NOK_Pos (16UL)          /*!< DCDC_V14_COMP_NOK（第16位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_COMP_NOK_Msk (0x10000UL)     /*!< DCDC_V14_COMP_NOK（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_COMP_P_Pos (11UL)              /*!< DCDC_N_COMP_P（位11）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_COMP_P_Msk (0x800UL)           /*!< DCDC_N_COMP_P（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_COMP_N_Pos (10UL)              /*!< DCDC_N_COMP_N（位10）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_COMP_N_Msk (0x400UL)           /*!< DCDC_N_COMP_N（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_P_COMP_Pos (9UL)                 /*!< DCDC_P_COMP（位9）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_P_COMP_Msk (0x200UL)             /*!< DCDC_P_COMP（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_COMP_Pos (8UL)                 /*!< DCDC_N_COMP（位8）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_COMP_Msk (0x100UL)             /*!< DCDC_N_COMP（位域掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_LV_MODE_Pos (7UL)                /*!< DCDC_LV_MODE（第7位）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_LV_MODE_Msk (0x80UL)             /*!< DCDC_LV_MODE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_SW_STATE_Pos (6UL)          /*!< DCDC_V18P_SW_STATE（位6）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18P_SW_STATE_Msk (0x40UL)       /*!< DCDC_V18P_SW_STATE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_SW_STATE_Pos (5UL)           /*!< DCDC_VDD_SW_STATE（位5）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_VDD_SW_STATE_Msk (0x20UL)        /*!< DCDC_VDD_SW_STATE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_SW_STATE_Pos (4UL)           /*!< DCDC_V18_SW_STATE（位4）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V18_SW_STATE_Msk (0x10UL)        /*!< DCDC_V18_SW_STATE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_SW_STATE_Pos (3UL)           /*!< DCDC_V14_SW_STATE（位3）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_V14_SW_STATE_Msk (0x8UL)         /*!< DCDC_V14_SW_STATE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_SW_STATE_Pos (2UL)             /*!< DCDC_N_SW_STATE（位2）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_N_SW_STATE_Msk (0x4UL)           /*!< DCDC_N_SW_STATE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_P_SW_STATE_Pos (1UL)             /*!< DCDC_P_SW_STATE（位1）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_P_SW_STATE_Msk (0x2UL)           /*!< DCDC_P_SW_STATE（位字段掩码：0x01）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_STARTUP_COMPLETE_Pos (0UL)       /*!< DCDC_STARTUP_COMPLETE（位0）*/
#define DCDC_DCDC_STATUS1_REG_DCDC_STARTUP_COMPLETE_Msk (0x1UL)     /*!< DCDC_STARTUP_COMPLETE（位字段掩码：0x01）*/
/* =====================================================  DCDC_V14_REG  ====================================================== */
#define DCDC_DCDC_V14_REG_DCDC_V14_FAST_RAMPING_Pos (31UL)          /*!< DCDC_V14_FAST_RAMPING（第31位）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_FAST_RAMPING_Msk (0x80000000UL)  /*!< DCDC_V14_FAST_RAMPING（位字段掩码：0x01）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_TRIM_Pos (27UL)                  /*!< DCDC_V14_TRIM（第27位）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_TRIM_Msk (0x8000000UL)           /*!< DCDC_V14_TRIM（位字段掩码：0x01）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_CUR_LIM_MAX_HV_Pos (22UL)        /*!< DCDC_V14_CUR_LIM_MAX_HV（位22）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_CUR_LIM_MAX_HV_Msk (0x7c00000UL) /*!< DCDC_V14_CUR_LIM_MAX_HV（位域掩码：0x1f）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_CUR_LIM_MAX_LV_Pos (17UL)        /*!< DCDC_V14_CUR_LIM_MAX_LV（第17位）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_CUR_LIM_MAX_LV_Msk (0x3e0000UL)  /*!< DCDC_V14_CUR_LIM_MAX_LV（位域掩码：0x1f）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_CUR_LIM_MIN_Pos (12UL)           /*!< DCDC_V14_CUR_LIM_MIN（位12）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_CUR_LIM_MIN_Msk (0x1f000UL)      /*!< DCDC_V14_CUR_LIM_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_IDLE_HYST_Pos (7UL)              /*!< DCDC_V14_IDLE_SYSTEM（位7）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_IDLE_HYST_Msk (0xf80UL)          /*!< DCDC_V14_IDLE_SYSTEM（位字段掩码：0x1f）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_IDLE_MIN_Pos (2UL)               /*!< DCDC_V14_IDLE_MIN（位2）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_IDLE_MIN_Msk (0x7cUL)            /*!< DCDC_V14_IDLE_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_ENABLE_HV_Pos (1UL)              /*!< DCDC_V14_ENABLE_HV（位1）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_ENABLE_HV_Msk (0x2UL)            /*!< DCDC_V14_ENABLE_HV（位域掩码：0x01）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_ENABLE_LV_Pos (0UL)              /*!< DCDC_V14_ENABLE_LV（位0）*/
#define DCDC_DCDC_V14_REG_DCDC_V14_ENABLE_LV_Msk (0x1UL)            /*!< DCDC_V14_ENABLE_LV（位域掩码：0x01）*/
/* =====================================================  DCDC_V18P_REG  ===================================================== */
#define DCDC_DCDC_V18P_REG_DCDC_V18P_FAST_RAMPING_Pos (31UL)        /*!< DCDC_V18P_FAST_RAMPING（位31）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_FAST_RAMPING_Msk (0x80000000UL) /*!< DCDC_V18P_FAST_RAMPING（位字段掩码：0x01）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_TRIM_Pos (27UL)                /*!< DCDC_V18P_TRIM（位27）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_TRIM_Msk (0x78000000UL)        /*!< DCDC_V18P_TRIM（位字段掩码：0x0f）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_CUR_LIM_MAX_HV_Pos (22UL)      /*!< DCDC_V18P_CUR_LIM_MAX_HV（位22）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_CUR_LIM_MAX_HV_Msk (0x7c00000UL) /*!< DCDC_V18P_CUR_LIM_MAX_HV（位场掩码：0x1f）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_CUR_LIM_MAX_LV_Pos (17UL)      /*!< DCDC_V18P_CUR_LIM_MAX_LV（位17）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_CUR_LIM_MAX_LV_Msk (0x3e0000UL) /*!< DCDC_V18P_CUR_LIM_MAX_LV（位域掩码：0x1f）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_CUR_LIM_MIN_Pos (12UL)         /*!< DCDC_V18P_CUR_LIM_MIN（位12）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_CUR_LIM_MIN_Msk (0x1f000UL)    /*!< DCDC_V18P_CUR_LIM_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_IDLE_HYST_Pos (7UL)            /*!< DCDC_V18P_IDLE_SYSTEM（位7）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_IDLE_HYST_Msk (0xf80UL)        /*!< DCDC_V18P_IDLE_SYSTEM（位字段掩码：0x1f）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_IDLE_MIN_Pos (2UL)             /*!< DCDC_V18P_IDLE_MIN（位2）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_IDLE_MIN_Msk (0x7cUL)          /*!< DCDC_V18P_IDLE_MIN（位字段掩码：0x1f）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_ENABLE_HV_Pos (1UL)            /*!< DCDC_V18P_ENABLE_HV（位1）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_ENABLE_HV_Msk (0x2UL)          /*!< DCDC_V18P_ENABLE_HV（位字段掩码：0x01）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_ENABLE_LV_Pos (0UL)            /*!< DCDC_V18P_ENABLE_LV（位0）*/
#define DCDC_DCDC_V18P_REG_DCDC_V18P_ENABLE_LV_Msk (0x1UL)          /*!< DCDC_V18P_ENABLE_LV（位字段掩码：0x01）*/
/* =====================================================  DCDC_V18_REG  ====================================================== */
#define DCDC_DCDC_V18_REG_DCDC_V18_FAST_RAMPING_Pos (31UL)          /*!< DCDC_V18_FAST_RAMPING（第31位）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_FAST_RAMPING_Msk (0x80000000UL)  /*!< DCDC_V18_FAST_RAMPING（位字段掩码：0x01）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_TRIM_Pos (27UL)                  /*!< DCDC_V18_TRIM（第27位）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_TRIM_Msk (0x78000000UL)          /*!< DCDC_V18_TRIM（位字段掩码：0x0f）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_CUR_LIM_MAX_HV_Pos (22UL)        /*!< DCDC_V18_CUR_LIM_MAX_HV（位22）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_CUR_LIM_MAX_HV_Msk (0x7c00000UL) /*!< DCDC_V18_CUR_LIM_MAX_HV（位域掩码：0x1f）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_CUR_LIM_MAX_LV_Pos (17UL)        /*!< DCDC_V18_CUR_LIM_MAX_LV（第17位）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_CUR_LIM_MAX_LV_Msk (0x3e0000UL)  /*!< DCDC_V18_CUR_LIM_MAX_LV（位域掩码：0x1f）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_CUR_LIM_MIN_Pos (12UL)           /*!< DCDC_V18_CUR_LIM_MIN（位12）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_CUR_LIM_MIN_Msk (0x1f000UL)      /*!< DCDC_V18_CUR_LIM_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_IDLE_HYST_Pos (7UL)              /*!< DCDC_V18_IDLE_SYSTEM（位7）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_IDLE_HYST_Msk (0xf80UL)          /*!< DCDC_V18_IDLE_SYSTEM（位字段掩码：0x1f）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_IDLE_MIN_Pos (2UL)               /*!< DCDC_V18_IDLE_MIN（位2）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_IDLE_MIN_Msk (0x7cUL)            /*!< DCDC_V18_IDLE_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_ENABLE_HV_Pos (1UL)              /*!< DCDC_V18_ENABLE_HV（位1）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_ENABLE_HV_Msk (0x2UL)            /*!< DCDC_V18_ENABLE_HV（位域掩码：0x01）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_ENABLE_LV_Pos (0UL)              /*!< DCDC_V18_ENABLE_LV（位0）*/
#define DCDC_DCDC_V18_REG_DCDC_V18_ENABLE_LV_Msk (0x1UL)            /*!< DCDC_V18_ENABLE_LV（位域掩码：0x01）*/
/* =====================================================  DCDC_VDD_REG  ====================================================== */
#define DCDC_DCDC_VDD_REG_DCDC_VDD_FAST_RAMPING_Pos (31UL)          /*!< DCDC_VDD_FAST_RAMPING（第31位）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_FAST_RAMPING_Msk (0x80000000UL)  /*!< DCDC_VDD_FAST_RAMPING（位字段掩码：0x01）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_TRIM_Pos (27UL)                  /*!< DCDC_VDD_TRIM（第27位）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_TRIM_Msk (0x38000000UL)          /*!< DCDC_VDD_TRIM（位字段掩码：0x07）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_CUR_LIM_MAX_HV_Pos (22UL)        /*!< DCDC_VDD_CUR_LIM_MAX_HV（第22位）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_CUR_LIM_MAX_HV_Msk (0x7c00000UL) /*!< DCDC_VDD_CUR_LIM_MAX_HV（位域掩码：0x1f）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_CUR_LIM_MAX_LV_Pos (17UL)        /*!< DCDC_VDD_CUR_LIM_MAX_LV（第17位）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_CUR_LIM_MAX_LV_Msk (0x3e0000UL)  /*!< DCDC_VDD_CUR_LIM_MAX_LV（位域掩码：0x1f）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_CUR_LIM_MIN_Pos (12UL)           /*!< DCDC_VDD_CUR_LIM_MIN（位12）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_CUR_LIM_MIN_Msk (0x1f000UL)      /*!< DCDC_VDD_CUR_LIM_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_IDLE_HYST_Pos (7UL)              /*!< DCDC_VDD_IDLE_SYSTEM（位7）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_IDLE_HYST_Msk (0xf80UL)          /*!< DCDC_VDD_IDLE_SYSTEM（位字段掩码：0x1f）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_IDLE_MIN_Pos (2UL)               /*!< DCDC_VDD_IDLE_MIN（位2）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_IDLE_MIN_Msk (0x7cUL)            /*!< DCDC_VDD_IDLE_MIN（位域掩码：0x1f）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_ENABLE_HV_Pos (1UL)              /*!< DCDC_VDD_ENABLE_HV（位1）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_ENABLE_HV_Msk (0x2UL)            /*!< DCDC_VDD_ENABLE_HV（位域掩码：0x01）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_ENABLE_LV_Pos (0UL)              /*!< DCDC_VDD_ENABLE_LV（位0）*/
#define DCDC_DCDC_VDD_REG_DCDC_VDD_ENABLE_LV_Msk (0x1UL)            /*!< DCDC_VDD_ENABLE_LV（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                            DMA                                            ================ */
/* =========================================================================================================================== */

/* ===================================================  DMA0_A_START_REG  ==================================================== */
#define DMA_DMA0_A_START_REG_DMA0_A_START_Pos (0UL)                 /*!< DMA0_A_START（位0）*/
#define DMA_DMA0_A_START_REG_DMA0_A_START_Msk (0xffffffffUL)        /*!< DMA0_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA0_B_START_REG  ==================================================== */
#define DMA_DMA0_B_START_REG_DMA0_B_START_Pos (0UL)                 /*!< DMA0_B_START（位0）*/
#define DMA_DMA0_B_START_REG_DMA0_B_START_Msk (0xffffffffUL)        /*!< DMA0_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA0_CTRL_REG  ===================================================== */
#define DMA_DMA0_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA0_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA0_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA0_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA0_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA0_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA0_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA0_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA0_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA0_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA0_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA0_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA0_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA0_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA0_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA0_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA0_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA0_IDX_REG  ====================================================== */
#define DMA_DMA0_IDX_REG_DMA0_IDX_Pos     (0UL)                     /*!< DMA0_IDX（位0）*/
#define DMA_DMA0_IDX_REG_DMA0_IDX_Msk     (0xffffUL)                /*!< DMA0_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA0_INT_REG  ====================================================== */
#define DMA_DMA0_INT_REG_DMA0_INT_Pos     (0UL)                     /*!< DMA0_INT（位0）*/
#define DMA_DMA0_INT_REG_DMA0_INT_Msk     (0xffffUL)                /*!< DMA0_INT（位域掩码：0xffff）*/
/* =====================================================  DMA0_LEN_REG  ====================================================== */
#define DMA_DMA0_LEN_REG_DMA0_LEN_Pos     (0UL)                     /*!< DMA0_LEN（位0）*/
#define DMA_DMA0_LEN_REG_DMA0_LEN_Msk     (0xffffUL)                /*!< DMA0_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA1_A_START_REG  ==================================================== */
#define DMA_DMA1_A_START_REG_DMA1_A_START_Pos (0UL)                 /*!< DMA1_A_START（位0）*/
#define DMA_DMA1_A_START_REG_DMA1_A_START_Msk (0xffffffffUL)        /*!< DMA1_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA1_B_START_REG  ==================================================== */
#define DMA_DMA1_B_START_REG_DMA1_B_START_Pos (0UL)                 /*!< DMA1_B_START（位0）*/
#define DMA_DMA1_B_START_REG_DMA1_B_START_Msk (0xffffffffUL)        /*!< DMA1_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA1_CTRL_REG  ===================================================== */
#define DMA_DMA1_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA1_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA1_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA1_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA1_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA1_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA1_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA1_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA1_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA1_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA1_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA1_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA1_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA1_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA1_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA1_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA1_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA1_IDX_REG  ====================================================== */
#define DMA_DMA1_IDX_REG_DMA1_IDX_Pos     (0UL)                     /*!< DMA1_IDX（位0）*/
#define DMA_DMA1_IDX_REG_DMA1_IDX_Msk     (0xffffUL)                /*!< DMA1_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA1_INT_REG  ====================================================== */
#define DMA_DMA1_INT_REG_DMA1_INT_Pos     (0UL)                     /*!< DMA1_INT（位0）*/
#define DMA_DMA1_INT_REG_DMA1_INT_Msk     (0xffffUL)                /*!< DMA1_INT（位域掩码：0xffff）*/
/* =====================================================  DMA1_LEN_REG  ====================================================== */
#define DMA_DMA1_LEN_REG_DMA1_LEN_Pos     (0UL)                     /*!< DMA1_LEN（位0）*/
#define DMA_DMA1_LEN_REG_DMA1_LEN_Msk     (0xffffUL)                /*!< DMA1_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA2_A_START_REG  ==================================================== */
#define DMA_DMA2_A_START_REG_DMA2_A_START_Pos (0UL)                 /*!< DMA2_A_START（位0）*/
#define DMA_DMA2_A_START_REG_DMA2_A_START_Msk (0xffffffffUL)        /*!< DMA2_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA2_B_START_REG  ==================================================== */
#define DMA_DMA2_B_START_REG_DMA2_B_START_Pos (0UL)                 /*!< DMA2_B_START（位0）*/
#define DMA_DMA2_B_START_REG_DMA2_B_START_Msk (0xffffffffUL)        /*!< DMA2_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA2_CTRL_REG  ===================================================== */
#define DMA_DMA2_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA2_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA2_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA2_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA2_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA2_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA2_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA2_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA2_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA2_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA2_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA2_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA2_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA2_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA2_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA2_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA2_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA2_IDX_REG  ====================================================== */
#define DMA_DMA2_IDX_REG_DMA2_IDX_Pos     (0UL)                     /*!< DMA2_IDX（位0）*/
#define DMA_DMA2_IDX_REG_DMA2_IDX_Msk     (0xffffUL)                /*!< DMA2_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA2_INT_REG  ====================================================== */
#define DMA_DMA2_INT_REG_DMA2_INT_Pos     (0UL)                     /*!< DMA2_INT（位0）*/
#define DMA_DMA2_INT_REG_DMA2_INT_Msk     (0xffffUL)                /*!< DMA2_INT（位域掩码：0xffff）*/
/* =====================================================  DMA2_LEN_REG  ====================================================== */
#define DMA_DMA2_LEN_REG_DMA2_LEN_Pos     (0UL)                     /*!< DMA2_LEN（位0）*/
#define DMA_DMA2_LEN_REG_DMA2_LEN_Msk     (0xffffUL)                /*!< DMA2_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA3_A_START_REG  ==================================================== */
#define DMA_DMA3_A_START_REG_DMA3_A_START_Pos (0UL)                 /*!< DMA3_A_START（位0）*/
#define DMA_DMA3_A_START_REG_DMA3_A_START_Msk (0xffffffffUL)        /*!< DMA3_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA3_B_START_REG  ==================================================== */
#define DMA_DMA3_B_START_REG_DMA3_B_START_Pos (0UL)                 /*!< DMA3_B_START（位0）*/
#define DMA_DMA3_B_START_REG_DMA3_B_START_Msk (0xffffffffUL)        /*!< DMA3_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA3_CTRL_REG  ===================================================== */
#define DMA_DMA3_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA3_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA3_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA3_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA3_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA3_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA3_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA3_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA3_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA3_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA3_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA3_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA3_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA3_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA3_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA3_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA3_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA3_IDX_REG  ====================================================== */
#define DMA_DMA3_IDX_REG_DMA3_IDX_Pos     (0UL)                     /*!< DMA3_IDX（位0）*/
#define DMA_DMA3_IDX_REG_DMA3_IDX_Msk     (0xffffUL)                /*!< DMA3_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA3_INT_REG  ====================================================== */
#define DMA_DMA3_INT_REG_DMA3_INT_Pos     (0UL)                     /*!< DMA3_INT（位0）*/
#define DMA_DMA3_INT_REG_DMA3_INT_Msk     (0xffffUL)                /*!< DMA3_INT（位域掩码：0xffff）*/
/* =====================================================  DMA3_LEN_REG  ====================================================== */
#define DMA_DMA3_LEN_REG_DMA3_LEN_Pos     (0UL)                     /*!< DMA3_LEN（位0）*/
#define DMA_DMA3_LEN_REG_DMA3_LEN_Msk     (0xffffUL)                /*!< DMA3_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA4_A_START_REG  ==================================================== */
#define DMA_DMA4_A_START_REG_DMA4_A_START_Pos (0UL)                 /*!< DMA4_A_START（位0）*/
#define DMA_DMA4_A_START_REG_DMA4_A_START_Msk (0xffffffffUL)        /*!< DMA4_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA4_B_START_REG  ==================================================== */
#define DMA_DMA4_B_START_REG_DMA4_B_START_Pos (0UL)                 /*!< DMA4_B_START（位0）*/
#define DMA_DMA4_B_START_REG_DMA4_B_START_Msk (0xffffffffUL)        /*!< DMA4_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA4_CTRL_REG  ===================================================== */
#define DMA_DMA4_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA4_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA4_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA4_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA4_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA4_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA4_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA4_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA4_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA4_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA4_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA4_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA4_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA4_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA4_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA4_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA4_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA4_IDX_REG  ====================================================== */
#define DMA_DMA4_IDX_REG_DMA4_IDX_Pos     (0UL)                     /*!< DMA4_IDX（位0）*/
#define DMA_DMA4_IDX_REG_DMA4_IDX_Msk     (0xffffUL)                /*!< DMA4_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA4_INT_REG  ====================================================== */
#define DMA_DMA4_INT_REG_DMA4_INT_Pos     (0UL)                     /*!< DMA4_INT（位0）*/
#define DMA_DMA4_INT_REG_DMA4_INT_Msk     (0xffffUL)                /*!< DMA4_INT（位域掩码：0xffff）*/
/* =====================================================  DMA4_LEN_REG  ====================================================== */
#define DMA_DMA4_LEN_REG_DMA4_LEN_Pos     (0UL)                     /*!< DMA4_LEN（位0）*/
#define DMA_DMA4_LEN_REG_DMA4_LEN_Msk     (0xffffUL)                /*!< DMA4_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA5_A_START_REG  ==================================================== */
#define DMA_DMA5_A_START_REG_DMA5_A_START_Pos (0UL)                 /*!< DMA5_A_START（位0）*/
#define DMA_DMA5_A_START_REG_DMA5_A_START_Msk (0xffffffffUL)        /*!< DMA5_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA5_B_START_REG  ==================================================== */
#define DMA_DMA5_B_START_REG_DMA5_B_START_Pos (0UL)                 /*!< DMA5_B_START（位0）*/
#define DMA_DMA5_B_START_REG_DMA5_B_START_Msk (0xffffffffUL)        /*!< DMA5_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA5_CTRL_REG  ===================================================== */
#define DMA_DMA5_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA5_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA5_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA5_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA5_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA5_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA5_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA5_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA5_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA5_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA5_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA5_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA5_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA5_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA5_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA5_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA5_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA5_IDX_REG  ====================================================== */
#define DMA_DMA5_IDX_REG_DMA5_IDX_Pos     (0UL)                     /*!< DMA5_IDX（位0）*/
#define DMA_DMA5_IDX_REG_DMA5_IDX_Msk     (0xffffUL)                /*!< DMA5_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA5_INT_REG  ====================================================== */
#define DMA_DMA5_INT_REG_DMA5_INT_Pos     (0UL)                     /*!< DMA5_INT（位0）*/
#define DMA_DMA5_INT_REG_DMA5_INT_Msk     (0xffffUL)                /*!< DMA5_INT（位域掩码：0xffff）*/
/* =====================================================  DMA5_LEN_REG  ====================================================== */
#define DMA_DMA5_LEN_REG_DMA5_LEN_Pos     (0UL)                     /*!< DMA5_LEN（位0）*/
#define DMA_DMA5_LEN_REG_DMA5_LEN_Msk     (0xffffUL)                /*!< DMA5_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA6_A_START_REG  ==================================================== */
#define DMA_DMA6_A_START_REG_DMA6_A_START_Pos (0UL)                 /*!< DMA6_A_START（位0）*/
#define DMA_DMA6_A_START_REG_DMA6_A_START_Msk (0xffffffffUL)        /*!< DMA6_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA6_B_START_REG  ==================================================== */
#define DMA_DMA6_B_START_REG_DMA6_B_START_Pos (0UL)                 /*!< DMA6_B_START（位0）*/
#define DMA_DMA6_B_START_REG_DMA6_B_START_Msk (0xffffffffUL)        /*!< DMA6_BR_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA6_CTRL_REG  ===================================================== */
#define DMA_DMA6_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA6_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA6_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA6_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA6_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA6_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA6_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA6_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA6_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA6_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA6_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA6_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA6_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA6_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA6_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA6_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA6_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA6_IDX_REG  ====================================================== */
#define DMA_DMA6_IDX_REG_DMA6_IDX_Pos     (0UL)                     /*!< DMA6_IDX（位0）*/
#define DMA_DMA6_IDX_REG_DMA6_IDX_Msk     (0xffffUL)                /*!< DMA6_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA6_INT_REG  ====================================================== */
#define DMA_DMA6_INT_REG_DMA6_INT_Pos     (0UL)                     /*!< DMA6_INT（位0）*/
#define DMA_DMA6_INT_REG_DMA6_INT_Msk     (0xffffUL)                /*!< DMA6_INT（位字段掩码：0xffff）*/
/* =====================================================  DMA6_LEN_REG  ====================================================== */
#define DMA_DMA6_LEN_REG_DMA6_LEN_Pos     (0UL)                     /*!< DMA6_LEN（位0）*/
#define DMA_DMA6_LEN_REG_DMA6_LEN_Msk     (0xffffUL)                /*!< DMA6_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA7_A_START_REG  ==================================================== */
#define DMA_DMA7_A_START_REG_DMA7_A_START_Pos (0UL)                 /*!< DMA7_A_START（位0）*/
#define DMA_DMA7_A_START_REG_DMA7_A_START_Msk (0xffffffffUL)        /*!< DMA7_A_START（位域掩码：0xffffffff）*/
/* ===================================================  DMA7_B_START_REG  ==================================================== */
#define DMA_DMA7_B_START_REG_DMA7_B_START_Pos (0UL)                 /*!< DMA7_B_START（位0）*/
#define DMA_DMA7_B_START_REG_DMA7_B_START_Msk (0xffffffffUL)        /*!< DMA7_B_START（位域掩码：0xffffffff）*/
/* =====================================================  DMA7_CTRL_REG  ===================================================== */
#define DMA_DMA7_CTRL_REG_BUS_ERROR_DETECT_Pos (15UL)               /*!< BUS_ERROR_DETECT（第15位）*/
#define DMA_DMA7_CTRL_REG_BUS_ERROR_DETECT_Msk (0x8000UL)           /*!< BUS_ERROR_DETECT（位字段掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_BURST_MODE_Pos  (13UL)                    /*!< BURST_MODE（第13位）*/
#define DMA_DMA7_CTRL_REG_BURST_MODE_Msk  (0x6000UL)                /*!< BURST_MODE（位字段掩码：0x03）*/
#define DMA_DMA7_CTRL_REG_REQ_SENSE_Pos   (12UL)                    /*!< REQ_SENSE（第12位）*/
#define DMA_DMA7_CTRL_REG_REQ_SENSE_Msk   (0x1000UL)                /*!< REQ_SENSE（位域掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_DMA_INIT_Pos    (11UL)                    /*!< DMA_INIT（位11）*/
#define DMA_DMA7_CTRL_REG_DMA_INIT_Msk    (0x800UL)                 /*!< DMA_INIT（位字段掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_DMA_IDLE_Pos    (10UL)                    /*!< DMA_IDLE（位10）*/
#define DMA_DMA7_CTRL_REG_DMA_IDLE_Msk    (0x400UL)                 /*!< DMA_IDLE（位域掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_DMA_PRIO_Pos    (7UL)                     /*!< DMA_PRIO（位7）*/
#define DMA_DMA7_CTRL_REG_DMA_PRIO_Msk    (0x380UL)                 /*!< DMA_PRIO（位域掩码：0x07）*/
#define DMA_DMA7_CTRL_REG_CIRCULAR_Pos    (6UL)                     /*!< 圆形（第6位）*/
#define DMA_DMA7_CTRL_REG_CIRCULAR_Msk    (0x40UL)                  /*!< CIRCULAR（位域掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_AINC_Pos        (5UL)                     /*!< AINC（位5）*/
#define DMA_DMA7_CTRL_REG_AINC_Msk        (0x20UL)                  /*!< AINC（位域掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_BINC_Pos        (4UL)                     /*!< BINC（位4）*/
#define DMA_DMA7_CTRL_REG_BINC_Msk        (0x10UL)                  /*!< BINC（位域掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_DREQ_MODE_Pos   (3UL)                     /*!< DREQ_MODE（位3）*/
#define DMA_DMA7_CTRL_REG_DREQ_MODE_Msk   (0x8UL)                   /*!< DREQ_MODE（位域掩码：0x01）*/
#define DMA_DMA7_CTRL_REG_BW_Pos          (1UL)                     /*!< BW（位1）*/
#define DMA_DMA7_CTRL_REG_BW_Msk          (0x6UL)                   /*!< BW（位域掩码：0x03）*/
#define DMA_DMA7_CTRL_REG_DMA_ON_Pos      (0UL)                     /*!< DMA_ON（位0）*/
#define DMA_DMA7_CTRL_REG_DMA_ON_Msk      (0x1UL)                   /*!< DMA_ON（位域掩码：0x01）*/
/* =====================================================  DMA7_IDX_REG  ====================================================== */
#define DMA_DMA7_IDX_REG_DMA7_IDX_Pos     (0UL)                     /*!< DMA7_IDX（位0）*/
#define DMA_DMA7_IDX_REG_DMA7_IDX_Msk     (0xffffUL)                /*!< DMA7_IDX（位域掩码：0xffff）*/
/* =====================================================  DMA7_INT_REG  ====================================================== */
#define DMA_DMA7_INT_REG_DMA7_INT_Pos     (0UL)                     /*!< DMA7_INT（位0）*/
#define DMA_DMA7_INT_REG_DMA7_INT_Msk     (0xffffUL)                /*!< DMA7_INT（位域掩码：0xffff）*/
/* =====================================================  DMA7_LEN_REG  ====================================================== */
#define DMA_DMA7_LEN_REG_DMA7_LEN_Pos     (0UL)                     /*!< DMA7_LEN（位0）*/
#define DMA_DMA7_LEN_REG_DMA7_LEN_Msk     (0xffffUL)                /*!< DMA7_LEN（位域掩码：0xffff）*/
/* ===================================================  DMA_CLEAR_INT_REG  =================================================== */
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH7_Pos (7UL)             /*!< DMA_RST_IRQ_CH7（第7位）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH7_Msk (0x80UL)          /*!< DMA_RST_IRQ_CH7（位字段掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH6_Pos (6UL)             /*!< DMA_RST_IRQ_CH6（第6位）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH6_Msk (0x40UL)          /*!< DMA_RST_IRQ_CH6（位字段掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH5_Pos (5UL)             /*!< DMA_RST_IRQ_CH5（第5位）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH5_Msk (0x20UL)          /*!< DMA_RST_IRQ_CH5（位域掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH4_Pos (4UL)             /*!< DMA_RST_IRQ_CH4（第4位）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH4_Msk (0x10UL)          /*!< DMA_RST_IRQ_CH4（位字段掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH3_Pos (3UL)             /*!< DMA_RST_IRQ_CH3（位3）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH3_Msk (0x8UL)           /*!< DMA_RST_IRQ_CH3（位字段掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH2_Pos (2UL)             /*!< DMA_RST_IRQ_CH2（位2）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH2_Msk (0x4UL)           /*!< DMA_RST_IRQ_CH2（位字段掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH1_Pos (1UL)             /*!< DMA_RST_IRQ_CH1（位1）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH1_Msk (0x2UL)           /*!< DMA_RST_IRQ_CH1（位字段掩码：0x01）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH0_Pos (0UL)             /*!< DMA_RST_IRQ_CH0（位0）*/
#define DMA_DMA_CLEAR_INT_REG_DMA_RST_IRQ_CH0_Msk (0x1UL)           /*!< DMA_RST_IRQ_CH0（位字段掩码：0x01）*/
/* ===================================================  DMA_INT_MASK_REG  ==================================================== */
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE7_Pos (7UL)              /*!< DMA_IRQ_ENABLE7（第7位）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE7_Msk (0x80UL)           /*!< DMA_IRQ_ENABLE7（位域掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE6_Pos (6UL)              /*!< DMA_IRQ_ENABLE6（位6）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE6_Msk (0x40UL)           /*!< DMA_IRQ_ENABLE6（位字段掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE5_Pos (5UL)              /*!< DMA_IRQ_ENABLE5（第5位）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE5_Msk (0x20UL)           /*!< DMA_IRQ_ENABLE5（位字段掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE4_Pos (4UL)              /*!< DMA_IRQ_ENABLE4（位4）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE4_Msk (0x10UL)           /*!< DMA_IRQ_ENABLE4（位字段掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE3_Pos (3UL)              /*!< DMA_IRQ_ENABLE3（位3）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE3_Msk (0x8UL)            /*!< DMA_IRQ_ENABLE3（位域掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE2_Pos (2UL)              /*!< DMA_IRQ_ENABLE2（位2）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE2_Msk (0x4UL)            /*!< DMA_IRQ_ENABLE2（位字段掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE1_Pos (1UL)              /*!< DMA_IRQ_ENABLE1（位1）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE1_Msk (0x2UL)            /*!< DMA_IRQ_ENABLE1（位字段掩码：0x01）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE0_Pos (0UL)              /*!< DMA_IRQ_ENABLE0（位0）*/
#define DMA_DMA_INT_MASK_REG_DMA_IRQ_ENABLE0_Msk (0x1UL)            /*!< DMA_IRQ_ENABLE0（位字段掩码：0x01）*/
/* ==================================================  DMA_INT_STATUS_REG  =================================================== */
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR7_Pos (15UL)              /*!< DMA_BUS_ERR7（位15）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR7_Msk (0x8000UL)          /*!< DMA_BUS_ERR7（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR6_Pos (14UL)              /*!< DMA_BUS_ERR6（位14）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR6_Msk (0x4000UL)          /*!< DMA_BUS_ERR6（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR5_Pos (13UL)              /*!< DMA_BUS_ERR5（位13）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR5_Msk (0x2000UL)          /*!< DMA_BUS_ERR5（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR4_Pos (12UL)              /*!< DMA_BUS_ERR4（位12）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR4_Msk (0x1000UL)          /*!< DMA_BUS_ERR4（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR3_Pos (11UL)              /*!< DMA_BUS_ERR3（位11）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR3_Msk (0x800UL)           /*!< DMA_BUS_ERR3（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR2_Pos (10UL)              /*!< DMA_BUS_ERR2（位10）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR2_Msk (0x400UL)           /*!< DMA_BUS_ERR2（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR1_Pos (9UL)               /*!< DMA_BUS_ERR1（位9）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR1_Msk (0x200UL)           /*!< DMA_BUS_ERR1（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR0_Pos (8UL)               /*!< DMA_BUS_ERR0（位8）*/
#define DMA_DMA_INT_STATUS_REG_DMA_BUS_ERR0_Msk (0x100UL)           /*!< DMA_BUS_ERR0（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH7_Pos (7UL)                /*!< DMA_IRQ_CH7（第7位）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH7_Msk (0x80UL)             /*!< DMA_IRQ_CH7（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH6_Pos (6UL)                /*!< DMA_IRQ_CH6（位6）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH6_Msk (0x40UL)             /*!< DMA_IRQ_CH6（位域掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH5_Pos (5UL)                /*!< DMA_IRQ_CH5（第5位）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH5_Msk (0x20UL)             /*!< DMA_IRQ_CH5（位域掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH4_Pos (4UL)                /*!< DMA_IRQ_CH4（位4）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH4_Msk (0x10UL)             /*!< DMA_IRQ_CH4（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH3_Pos (3UL)                /*!< DMA_IRQ_CH3（位3）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH3_Msk (0x8UL)              /*!< DMA_IRQ_CH3（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH2_Pos (2UL)                /*!< DMA_IRQ_CH2（位2）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH2_Msk (0x4UL)              /*!< DMA_IRQ_CH2（位字段掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH1_Pos (1UL)                /*!< DMA_IRQ_CH1（位1）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH1_Msk (0x2UL)              /*!< DMA_IRQ_CH1（位域掩码：0x01）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH0_Pos (0UL)                /*!< DMA_IRQ_CH0（位0）*/
#define DMA_DMA_INT_STATUS_REG_DMA_IRQ_CH0_Msk (0x1UL)              /*!< DMA_IRQ_CH0（位字段掩码：0x01）*/
/* ====================================================  DMA_REQ_MUX_REG  ==================================================== */
#define DMA_DMA_REQ_MUX_REG_DMA67_SEL_Pos (12UL)                    /*!< DMA67_SEL（第12位）*/
#define DMA_DMA_REQ_MUX_REG_DMA67_SEL_Msk (0xf000UL)                /*!< DMA67_SEL（位字段掩码：0x0f）*/
#define DMA_DMA_REQ_MUX_REG_DMA45_SEL_Pos (8UL)                     /*!< DMA45_SEL（位8）*/
#define DMA_DMA_REQ_MUX_REG_DMA45_SEL_Msk (0xf00UL)                 /*!< DMA45_SEL（位字段掩码：0x0f）*/
#define DMA_DMA_REQ_MUX_REG_DMA23_SEL_Pos (4UL)                     /*!< DMA23_SEL（位4）*/
#define DMA_DMA_REQ_MUX_REG_DMA23_SEL_Msk (0xf0UL)                  /*!< DMA23_SEL（位字段掩码：0x0f）*/
#define DMA_DMA_REQ_MUX_REG_DMA01_SEL_Pos (0UL)                     /*!< DMA01_SEL（位0）*/
#define DMA_DMA_REQ_MUX_REG_DMA01_SEL_Msk (0xfUL)                   /*!< DMA01_SEL（位字段掩码：0x0f）*/


/* =========================================================================================================================== */
/* ================                                            DW                                             ================ */
/* =========================================================================================================================== */

/* ===================================================  AHB_DMA_CCLM1_REG  =================================================== */
#define DW_AHB_DMA_CCLM1_REG_AHB_DMA_CCLM_Pos (0UL)                 /*!< AHB_DMA_CCLM（位0）*/
#define DW_AHB_DMA_CCLM1_REG_AHB_DMA_CCLM_Msk (0xffffUL)            /*!< AHB_DMA_CCLM（位域掩码：0xffff）*/
/* ===================================================  AHB_DMA_CCLM2_REG  =================================================== */
#define DW_AHB_DMA_CCLM2_REG_AHB_DMA_CCLM_Pos (0UL)                 /*!< AHB_DMA_CCLM（位0）*/
#define DW_AHB_DMA_CCLM2_REG_AHB_DMA_CCLM_Msk (0xffffUL)            /*!< AHB_DMA_CCLM（位域掩码：0xffff）*/
/* ===================================================  AHB_DMA_CCLM3_REG  =================================================== */
#define DW_AHB_DMA_CCLM3_REG_AHB_DMA_CCLM_Pos (0UL)                 /*!< AHB_DMA_CCLM（位0）*/
#define DW_AHB_DMA_CCLM3_REG_AHB_DMA_CCLM_Msk (0xffffUL)            /*!< AHB_DMA_CCLM（位域掩码：0xffff）*/
/* ===================================================  AHB_DMA_CCLM4_REG  =================================================== */
#define DW_AHB_DMA_CCLM4_REG_AHB_DMA_CCLM_Pos (0UL)                 /*!< AHB_DMA_CCLM（位0）*/
#define DW_AHB_DMA_CCLM4_REG_AHB_DMA_CCLM_Msk (0xffffUL)            /*!< AHB_DMA_CCLM（位域掩码：0xffff）*/
/* ================================================  AHB_DMA_DFLT_MASTER_REG  ================================================ */
#define DW_AHB_DMA_DFLT_MASTER_REG_AHB_DMA_DFLT_MASTER_Pos (0UL)    /*!< AHB_DMA_DFLT_MASTER（位0）*/
#define DW_AHB_DMA_DFLT_MASTER_REG_AHB_DMA_DFLT_MASTER_Msk (0xfUL)  /*!< AHB_DMA_DFLT_MASTER（位域掩码：0x0f）*/
/* ====================================================  AHB_DMA_PL1_REG  ==================================================== */
#define DW_AHB_DMA_PL1_REG_AHB_DMA_PL1_Pos (0UL)                    /*!< AHB_DMA_PL1（位0）*/
#define DW_AHB_DMA_PL1_REG_AHB_DMA_PL1_Msk (0xfUL)                  /*!< AHB_DMA_PL1（位域掩码：0x0f）*/
/* ====================================================  AHB_DMA_PL2_REG  ==================================================== */
#define DW_AHB_DMA_PL2_REG_AHB_DMA_PL2_Pos (0UL)                    /*!< AHB_DMA_PL2（位0）*/
#define DW_AHB_DMA_PL2_REG_AHB_DMA_PL2_Msk (0xfUL)                  /*!< AHB_DMA_PL2（位字段掩码：0x0f）*/
/* ====================================================  AHB_DMA_PL3_REG  ==================================================== */
#define DW_AHB_DMA_PL3_REG_AHB_DMA_PL3_Pos (0UL)                    /*!< AHB_DMA_PL3（位0）*/
#define DW_AHB_DMA_PL3_REG_AHB_DMA_PL3_Msk (0xfUL)                  /*!< AHB_DMA_PL3（位字段掩码：0x0f）*/
/* ====================================================  AHB_DMA_PL4_REG  ==================================================== */
#define DW_AHB_DMA_PL4_REG_AHB_DMA_PL4_Pos (0UL)                    /*!< AHB_DMA_PL4（位0）*/
#define DW_AHB_DMA_PL4_REG_AHB_DMA_PL4_Msk (0xfUL)                  /*!< AHB_DMA_PL4（位字段掩码：0x0f）*/
/* ====================================================  AHB_DMA_TCL_REG  ==================================================== */
#define DW_AHB_DMA_TCL_REG_AHB_DMA_TCL_Pos (0UL)                    /*!< AHB_DMA_TCL（位0）*/
#define DW_AHB_DMA_TCL_REG_AHB_DMA_TCL_Msk (0xffffUL)               /*!< AHB_DMA_TCL（位域掩码：0xffff）*/
/* ==================================================  AHB_DMA_VERSION_REG  ================================================== */
#define DW_AHB_DMA_VERSION_REG_AHB_DMA_VERSION_Pos (0UL)            /*!< AHB_DMA_VERSION（位0）*/
#define DW_AHB_DMA_VERSION_REG_AHB_DMA_VERSION_Msk (0xffffffffUL)   /*!< AHB_DMA_VERSION（位域掩码：0xffffff）*/
/* ===================================================  AHB_DMA_WTEN_REG  ==================================================== */
#define DW_AHB_DMA_WTEN_REG_AHB_DMA_WTEN_Pos (0UL)                  /*!< AHB_DMA_WTEN（位0）*/
#define DW_AHB_DMA_WTEN_REG_AHB_DMA_WTEN_Msk (0x1UL)                /*!< AHB_DMA_WTEN（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                           GPADC                                           ================ */
/* =========================================================================================================================== */

/* =================================================  GP_ADC_CLEAR_INT_REG  ================================================== */
#define GPADC_GP_ADC_CLEAR_INT_REG_GP_ADC_CLR_INT_Pos (0UL)         /*!< GP_ADC_CLR_INT（位0）*/
#define GPADC_GP_ADC_CLEAR_INT_REG_GP_ADC_CLR_INT_Msk (0xffffUL)    /*!< GP_ADC_CLR_INT（位字段掩码：0xffff）*/
/* ===================================================  GP_ADC_CTRL2_REG  ==================================================== */
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_STORE_DEL_Pos (12UL)          /*!< GP_ADC_STORE_DEL（第12位）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_STORE_DEL_Msk (0xf000UL)      /*!< GP_ADC_STORE_DEL（位字段掩码：0x0f）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_SMPL_TIME_Pos (8UL)           /*!< GP_ADC_SMPL_TIME（位8）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_SMPL_TIME_Msk (0xf00UL)       /*!< GP_ADC_SMPL_TIME（位域掩码：0x0f）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_CONV_NRS_Pos (5UL)            /*!< GP_ADC_CONV_NRS（位5）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_CONV_NRS_Msk (0xe0UL)         /*!< GP_ADC_CONV_NRS（位域掩码：0x07）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_DMA_EN_Pos (3UL)              /*!< GP_ADC_DMA_EN（位3）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_DMA_EN_Msk (0x8UL)            /*!< GP_ADC_DMA_EN（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_I20U_Pos (2UL)                /*!< GP_ADC_I20U（位2）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_I20U_Msk (0x4UL)              /*!< GP_ADC_I20U（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_IDYN_Pos (1UL)                /*!< GP_ADC_IDYN（位1）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_IDYN_Msk (0x2UL)              /*!< GP_ADC_IDYN（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_ATTN3X_Pos (0UL)              /*!< GP_ADC_ATTN3X（位0）*/
#define GPADC_GP_ADC_CTRL2_REG_GP_ADC_ATTN3X_Msk (0x1UL)            /*!< GP_ADC_ATTN3X（位域掩码：0x01）*/
/* ===================================================  GP_ADC_CTRL3_REG  ==================================================== */
#define GPADC_GP_ADC_CTRL3_REG_GP_ADC_INTERVAL_Pos (8UL)            /*!< GP_ADC_INTERVAL（位8）*/
#define GPADC_GP_ADC_CTRL3_REG_GP_ADC_INTERVAL_Msk (0xff00UL)       /*!< GP_ADC_INTERVAL（位字段掩码：0xff）*/
#define GPADC_GP_ADC_CTRL3_REG_GP_ADC_EN_DEL_Pos (0UL)              /*!< GP_ADC_EN_DEL（位0）*/
#define GPADC_GP_ADC_CTRL3_REG_GP_ADC_EN_DEL_Msk (0xffUL)           /*!< GP_ADC_EN_DEL（位字段掩码：0xff）*/
/* ====================================================  GP_ADC_CTRL_REG  ==================================================== */
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_DIFF_TEMP_EN_Pos (18UL)        /*!< GP_ADC_DIFF_TEMP_EN（位18）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_DIFF_TEMP_EN_Msk (0x40000UL)   /*!< GP_ADC_DIFF_TEMP_EN（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_DIFF_TEMP_SEL_Pos (16UL)       /*!< GP_ADC_DIFF_TEMP_SEL（位16）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_DIFF_TEMP_SEL_Msk (0x30000UL)  /*!< GP_ADC_DIFF_TEMP_SEL（位字段掩码：0x03）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_LDO_ZERO_Pos (15UL)            /*!< GP_ADC_LDO_ZERO（位15）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_LDO_ZERO_Msk (0x8000UL)        /*!< GP_ADC_LDO_ZERO（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_CHOP_Pos (14UL)                /*!< GP_ADC_CHOP（位14）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_CHOP_Msk (0x4000UL)            /*!< GP_ADC_CHOP（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_SIGN_Pos (13UL)                /*!< GP_ADC_SIGN（位13）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_SIGN_Msk (0x2000UL)            /*!< GP_ADC_SIGN（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_SEL_Pos (8UL)                  /*!< GP_ADC_SEL（位8）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_SEL_Msk (0x1f00UL)             /*!< GP_ADC_SEL（位域掩码：0x1f）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_MUTE_Pos (7UL)                 /*!< GP_ADC_MUTE（位7）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_MUTE_Msk (0x80UL)              /*!< GP_ADC_MUTE（位字段掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_SE_Pos (6UL)                   /*!< GP_ADC_SE（位6）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_SE_Msk (0x40UL)                /*!< GP_ADC_SE（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_MINT_Pos (5UL)                 /*!< GP_ADC_MINT（位5）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_MINT_Msk (0x20UL)              /*!< GP_ADC_MINT（位字段掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_INT_Pos (4UL)                  /*!< GP_ADC_INT（位4）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_INT_Msk (0x10UL)               /*!< GP_ADC_INT（位字段掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_CLK_SEL_Pos (3UL)              /*!< GP_ADC_CLK_SEL（位3）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_CLK_SEL_Msk (0x8UL)            /*!< GP_ADC_CLK_SEL（位字段掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_CONT_Pos (2UL)                 /*!< GP_ADC_CONT（位2）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_CONT_Msk (0x4UL)               /*!< GP_ADC_CONT（位域掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_START_Pos (1UL)                /*!< GP_ADC_START（位1）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_START_Msk (0x2UL)              /*!< GP_ADC_START（位字段掩码：0x01）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_EN_Pos (0UL)                   /*!< GP_ADC_EN（位0）*/
#define GPADC_GP_ADC_CTRL_REG_GP_ADC_EN_Msk (0x1UL)                 /*!< GP_ADC_EN（位域掩码：0x01）*/
/* ====================================================  GP_ADC_OFFN_REG  ==================================================== */
#define GPADC_GP_ADC_OFFN_REG_GP_ADC_OFFN_Pos (0UL)                 /*!< GP_ADC_OFFN（位0）*/
#define GPADC_GP_ADC_OFFN_REG_GP_ADC_OFFN_Msk (0x3ffUL)             /*!< GP_ADC_OFFN（位域掩码：0x3ff）*/
/* ====================================================  GP_ADC_OFFP_REG  ==================================================== */
#define GPADC_GP_ADC_OFFP_REG_GP_ADC_OFFP_Pos (0UL)                 /*!< GP_ADC_OFFP（位0）*/
#define GPADC_GP_ADC_OFFP_REG_GP_ADC_OFFP_Msk (0x3ffUL)             /*!< GP_ADC_OFFP（位域掩码：0x3ff）*/
/* ===================================================  GP_ADC_RESULT_REG  =================================================== */
#define GPADC_GP_ADC_RESULT_REG_GP_ADC_VAL_Pos (0UL)                /*!< GP_ADC_VAL（位0）*/
#define GPADC_GP_ADC_RESULT_REG_GP_ADC_VAL_Msk (0xffffUL)           /*!< GP_ADC_VAL（位域掩码：0xffff）*/


/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */

/* ===================================================  GPIO_CLK_SEL_REG  ==================================================== */
#define GPIO_GPIO_CLK_SEL_REG_DIVN_OUTPUT_EN_Pos (9UL)              /*!< DIVN_OUTPUT_EN（位9）*/
#define GPIO_GPIO_CLK_SEL_REG_DIVN_OUTPUT_EN_Msk (0x200UL)          /*!< DIVN_OUTPUT_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_RC32M_OUTPUT_EN_Pos (8UL)             /*!< RC32M_OUTPUT_EN（位8）*/
#define GPIO_GPIO_CLK_SEL_REG_RC32M_OUTPUT_EN_Msk (0x100UL)         /*!< RC32M_OUTPUT_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_XTAL32M_OUTPUT_EN_Pos (7UL)           /*!< XTAL32M_OUTPUT_EN（位7）*/
#define GPIO_GPIO_CLK_SEL_REG_XTAL32M_OUTPUT_EN_Msk (0x80UL)        /*!< XTAL32M_OUTPUT_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_RCX_OUTPUT_EN_Pos (6UL)               /*!< RCX_OUTPUT_EN（位6）*/
#define GPIO_GPIO_CLK_SEL_REG_RCX_OUTPUT_EN_Msk (0x40UL)            /*!< RCX_OUTPUT_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_RC32K_OUTPUT_EN_Pos (5UL)             /*!< RC32K_OUTPUT_EN（位5）*/
#define GPIO_GPIO_CLK_SEL_REG_RC32K_OUTPUT_EN_Msk (0x20UL)          /*!< RC32K_OUTPUT_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_XTAL32K_OUTPUT_EN_Pos (4UL)           /*!< XTAL32K_OUTPUT_EN（位4）*/
#define GPIO_GPIO_CLK_SEL_REG_XTAL32K_OUTPUT_EN_Msk (0x10UL)        /*!< XTAL32K_OUTPUT_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_FUNC_CLOCK_EN_Pos (3UL)               /*!< FUNC_CLOCK_EN（位3）*/
#define GPIO_GPIO_CLK_SEL_REG_FUNC_CLOCK_EN_Msk (0x8UL)             /*!< FUNC_CLOCK_EN（位字段掩码：0x01）*/
#define GPIO_GPIO_CLK_SEL_REG_FUNC_CLOCK_SEL_Pos (0UL)              /*!< FUNC_CLOCK_SEL（位0）*/
#define GPIO_GPIO_CLK_SEL_REG_FUNC_CLOCK_SEL_Msk (0x7UL)            /*!< FUNC_CLOCK_SEL（位字段掩码：0x07）*/
/* ====================================================  P0_00_MODE_REG  ===================================================== */
#define GPIO_P0_00_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_00_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_00_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_00_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_00_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_00_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_01_MODE_REG  ===================================================== */
#define GPIO_P0_01_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_01_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_01_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_01_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_01_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_01_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_02_MODE_REG  ===================================================== */
#define GPIO_P0_02_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_02_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_02_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_02_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_02_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_02_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_03_MODE_REG  ===================================================== */
#define GPIO_P0_03_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_03_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_03_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_03_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_03_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_03_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_04_MODE_REG  ===================================================== */
#define GPIO_P0_04_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_04_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_04_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_04_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_04_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_04_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_05_MODE_REG  ===================================================== */
#define GPIO_P0_05_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_05_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_05_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_05_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_05_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_05_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_06_MODE_REG  ===================================================== */
#define GPIO_P0_06_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_06_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_06_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_06_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_06_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_06_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_07_MODE_REG  ===================================================== */
#define GPIO_P0_07_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_07_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_07_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_07_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_07_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_07_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_08_MODE_REG  ===================================================== */
#define GPIO_P0_08_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_08_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_08_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_08_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_08_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_08_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_09_MODE_REG  ===================================================== */
#define GPIO_P0_09_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_09_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_09_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_09_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_09_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_09_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_10_MODE_REG  ===================================================== */
#define GPIO_P0_10_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_10_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_10_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_10_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_10_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_10_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_11_MODE_REG  ===================================================== */
#define GPIO_P0_11_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_11_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_11_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_11_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_11_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_11_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_12_MODE_REG  ===================================================== */
#define GPIO_P0_12_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_12_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_12_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_12_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_12_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_12_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_13_MODE_REG  ===================================================== */
#define GPIO_P0_13_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_13_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_13_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_13_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_13_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_13_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_14_MODE_REG  ===================================================== */
#define GPIO_P0_14_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_14_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_14_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_14_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_14_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_14_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_15_MODE_REG  ===================================================== */
#define GPIO_P0_15_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_15_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_15_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_15_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_15_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_15_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_16_MODE_REG  ===================================================== */
#define GPIO_P0_16_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_16_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_16_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_16_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_16_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_16_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_17_MODE_REG  ===================================================== */
#define GPIO_P0_17_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_17_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_17_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_17_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_17_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_17_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_18_MODE_REG  ===================================================== */
#define GPIO_P0_18_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_18_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_18_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_18_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_18_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_18_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_19_MODE_REG  ===================================================== */
#define GPIO_P0_19_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_19_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_19_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_19_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_19_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_19_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_20_MODE_REG  ===================================================== */
#define GPIO_P0_20_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_20_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_20_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_20_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_20_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_20_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_21_MODE_REG  ===================================================== */
#define GPIO_P0_21_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_21_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_21_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_21_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_21_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_21_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_22_MODE_REG  ===================================================== */
#define GPIO_P0_22_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_22_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_22_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_22_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_22_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_22_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_23_MODE_REG  ===================================================== */
#define GPIO_P0_23_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_23_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_23_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_23_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_23_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_23_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_24_MODE_REG  ===================================================== */
#define GPIO_P0_24_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_24_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_24_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_24_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_24_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_24_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_25_MODE_REG  ===================================================== */
#define GPIO_P0_25_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_25_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_25_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_25_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_25_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_25_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_26_MODE_REG  ===================================================== */
#define GPIO_P0_26_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_26_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_26_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_26_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_26_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_26_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_27_MODE_REG  ===================================================== */
#define GPIO_P0_27_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_27_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_27_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_27_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_27_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_27_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_28_MODE_REG  ===================================================== */
#define GPIO_P0_28_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_28_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_28_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_28_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_28_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_28_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_29_MODE_REG  ===================================================== */
#define GPIO_P0_29_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_29_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_29_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_29_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_29_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_29_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_30_MODE_REG  ===================================================== */
#define GPIO_P0_30_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_30_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_30_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_30_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_30_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_30_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P0_31_MODE_REG  ===================================================== */
#define GPIO_P0_31_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P0_31_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P0_31_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P0_31_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P0_31_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P0_31_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ======================================================  P0_DATA_REG  ====================================================== */
#define GPIO_P0_DATA_REG_P0_DATA_Pos      (0UL)                     /*!< P0_DATA（位0）*/
#define GPIO_P0_DATA_REG_P0_DATA_Msk      (0xffffffffUL)            /*!< P0_DATA（位域掩码：0xffffffff）*/
/* ==================================================  P0_PADPWR_CTRL_REG  =================================================== */
#define GPIO_P0_PADPWR_CTRL_REG_P0_OUT_CTRL_Pos (6UL)               /*!< P0_OUT_CTRL（位6）*/
#define GPIO_P0_PADPWR_CTRL_REG_P0_OUT_CTRL_Msk (0xffffffc0UL)      /*!< P0_OUT_CTRL（位域掩码：0x3ffffff）*/
/* ===================================================  P0_RESET_DATA_REG  =================================================== */
#define GPIO_P0_RESET_DATA_REG_P0_RESET_Pos (0UL)                   /*!< P0_RESET（位0）*/
#define GPIO_P0_RESET_DATA_REG_P0_RESET_Msk (0xffffffffUL)          /*!< P0_RESET（位域掩码：0xffffffff）*/
/* ====================================================  P0_SET_DATA_REG  ==================================================== */
#define GPIO_P0_SET_DATA_REG_P0_SET_Pos   (0UL)                     /*!< P0_SET（位0）*/
#define GPIO_P0_SET_DATA_REG_P0_SET_Msk   (0xffffffffUL)            /*!< P0_SET（位域掩码：0xffffffff）*/
/* ====================================================  P1_00_MODE_REG  ===================================================== */
#define GPIO_P1_00_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_00_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_00_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_00_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_00_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_00_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_01_MODE_REG  ===================================================== */
#define GPIO_P1_01_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_01_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_01_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_01_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_01_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_01_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_02_MODE_REG  ===================================================== */
#define GPIO_P1_02_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_02_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_02_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_02_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_02_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_02_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_03_MODE_REG  ===================================================== */
#define GPIO_P1_03_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_03_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_03_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_03_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_03_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_03_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_04_MODE_REG  ===================================================== */
#define GPIO_P1_04_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_04_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_04_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_04_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_04_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_04_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_05_MODE_REG  ===================================================== */
#define GPIO_P1_05_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_05_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_05_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_05_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_05_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_05_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_06_MODE_REG  ===================================================== */
#define GPIO_P1_06_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_06_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_06_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_06_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_06_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_06_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_07_MODE_REG  ===================================================== */
#define GPIO_P1_07_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_07_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_07_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_07_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_07_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_07_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_08_MODE_REG  ===================================================== */
#define GPIO_P1_08_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_08_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_08_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_08_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_08_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_08_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_09_MODE_REG  ===================================================== */
#define GPIO_P1_09_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_09_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_09_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_09_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_09_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_09_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_10_MODE_REG  ===================================================== */
#define GPIO_P1_10_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_10_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_10_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_10_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_10_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_10_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_11_MODE_REG  ===================================================== */
#define GPIO_P1_11_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_11_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_11_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_11_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_11_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_11_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_12_MODE_REG  ===================================================== */
#define GPIO_P1_12_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_12_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_12_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_12_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_12_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_12_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_13_MODE_REG  ===================================================== */
#define GPIO_P1_13_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_13_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_13_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_13_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_13_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_13_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_14_MODE_REG  ===================================================== */
#define GPIO_P1_14_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_14_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_14_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_14_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_14_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_14_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_15_MODE_REG  ===================================================== */
#define GPIO_P1_15_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_15_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_15_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_15_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_15_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_15_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_16_MODE_REG  ===================================================== */
#define GPIO_P1_16_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_16_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_16_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_16_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_16_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_16_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_17_MODE_REG  ===================================================== */
#define GPIO_P1_17_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_17_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_17_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_17_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_17_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_17_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_18_MODE_REG  ===================================================== */
#define GPIO_P1_18_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_18_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_18_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_18_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_18_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_18_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_19_MODE_REG  ===================================================== */
#define GPIO_P1_19_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_19_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_19_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_19_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_19_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_19_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_20_MODE_REG  ===================================================== */
#define GPIO_P1_20_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_20_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_20_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_20_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_20_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_20_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_21_MODE_REG  ===================================================== */
#define GPIO_P1_21_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_21_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_21_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_21_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_21_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_21_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ====================================================  P1_22_MODE_REG  ===================================================== */
#define GPIO_P1_22_MODE_REG_PPOD_Pos      (10UL)                    /*!< PPOD（位10）*/
#define GPIO_P1_22_MODE_REG_PPOD_Msk      (0x400UL)                 /*!< PPOD（位域掩码：0x01）*/
#define GPIO_P1_22_MODE_REG_PUPD_Pos      (8UL)                     /*!< PUPD（位8）*/
#define GPIO_P1_22_MODE_REG_PUPD_Msk      (0x300UL)                 /*!< PUPD（位域掩码：0x03）*/
#define GPIO_P1_22_MODE_REG_PID_Pos       (0UL)                     /*!< PID（位0）*/
#define GPIO_P1_22_MODE_REG_PID_Msk       (0x3fUL)                  /*!< PID（位域掩码：0x3f）*/
/* ======================================================  P1_DATA_REG  ====================================================== */
#define GPIO_P1_DATA_REG_P1_DATA_Pos      (0UL)                     /*!< P1_DATA（位0）*/
#define GPIO_P1_DATA_REG_P1_DATA_Msk      (0x7fffffUL)              /*!< P1_DATA（位字段掩码：0x7fffff）*/
/* ==================================================  P1_PADPWR_CTRL_REG  =================================================== */
#define GPIO_P1_PADPWR_CTRL_REG_P1_OUT_CTRL_Pos (0UL)               /*!< P1_OUT_CTRL（位0）*/
#define GPIO_P1_PADPWR_CTRL_REG_P1_OUT_CTRL_Msk (0x7fffffUL)        /*!< P1_OUT_CTRL（位域掩码：0x7fffff）*/
/* ===================================================  P1_RESET_DATA_REG  =================================================== */
#define GPIO_P1_RESET_DATA_REG_P1_RESET_Pos (0UL)                   /*!< P1_RESET（位0）*/
#define GPIO_P1_RESET_DATA_REG_P1_RESET_Msk (0x7fffffUL)            /*!< P1_RESET（位字段掩码：0x7fffff）*/
/* ====================================================  P1_SET_DATA_REG  ==================================================== */
#define GPIO_P1_SET_DATA_REG_P1_SET_Pos   (0UL)                     /*!< P1_SET（位0）*/
#define GPIO_P1_SET_DATA_REG_P1_SET_Msk   (0x7fffffUL)              /*!< P1_SET（位域掩码：0x7fffff）*/
/* ===================================================  PAD_WEAK_CTRL_REG  =================================================== */
#define GPIO_PAD_WEAK_CTRL_REG_P1_09_LOWDRV_Pos (12UL)              /*!< P1_09_LOWDRV（第12位）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_09_LOWDRV_Msk (0x1000UL)          /*!< P1_09_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_06_LOWDRV_Pos (11UL)              /*!< P1_06_LOWDRV（位11）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_06_LOWDRV_Msk (0x800UL)           /*!< P1_06_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_02_LOWDRV_Pos (10UL)              /*!< P1_02_LOWDRV（位10）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_02_LOWDRV_Msk (0x400UL)           /*!< P1_02_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_01_LOWDRV_Pos (9UL)               /*!< P1_01_LOWDRV（位9）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_01_LOWDRV_Msk (0x200UL)           /*!< P1_01_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_00_LOWDRV_Pos (8UL)               /*!< P1_00_LOWDRV（位8）*/
#define GPIO_PAD_WEAK_CTRL_REG_P1_00_LOWDRV_Msk (0x100UL)           /*!< P1_00_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_27_LOWDRV_Pos (7UL)               /*!< P0_27_LOWDRV（位7）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_27_LOWDRV_Msk (0x80UL)            /*!< P0_27_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_26_LOWDRV_Pos (6UL)               /*!< P0_26_LOWDRV（位6）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_26_LOWDRV_Msk (0x40UL)            /*!< P0_26_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_25_LOWDRV_Pos (5UL)               /*!< P0_25_LOWDRV（位5）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_25_LOWDRV_Msk (0x20UL)            /*!< P0_25_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_18_LOWDRV_Pos (4UL)               /*!< P0_18_LOWDRV（位4）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_18_LOWDRV_Msk (0x10UL)            /*!< P0_18_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_17_LOWDRV_Pos (3UL)               /*!< P0_17_LOWDRV（位3）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_17_LOWDRV_Msk (0x8UL)             /*!< P0_17_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_16_LOWDRV_Pos (2UL)               /*!< P0_16_LOWDRV（位2）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_16_LOWDRV_Msk (0x4UL)             /*!< P0_16_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_07_LOWDRV_Pos (1UL)               /*!< P0_07_LOWDRV（位1）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_07_LOWDRV_Msk (0x2UL)             /*!< P0_07_LOWDRV（位域掩码：0x01）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_06_LOWDRV_Pos (0UL)               /*!< P0_06_LOWDRV（位0）*/
#define GPIO_PAD_WEAK_CTRL_REG_P0_06_LOWDRV_Msk (0x1UL)             /*!< P0_06_LOWDRV（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                           GPREG                                           ================ */
/* =========================================================================================================================== */

/* =======================================================  DEBUG_REG  ======================================================= */
#define GPREG_DEBUG_REG_CROSS_CPU_HALT_SENSITIVITY_Pos (8UL)        /*!< CROSS_CPU_HALT_SENSTIVITY（位8）*/
#define GPREG_DEBUG_REG_CROSS_CPU_HALT_SENSITIVITY_Msk (0x100UL)    /*!< CROSS_CPU_HALT_SENSITIVITY（位字段掩码：0x01）*/
#define GPREG_DEBUG_REG_SYS_CPUWAIT_ON_JTAG_Pos (7UL)               /*!< SYS_CPUWAIT_ON_JTAG（位7）*/
#define GPREG_DEBUG_REG_SYS_CPUWAIT_ON_JTAG_Msk (0x80UL)            /*!< SYS_CPUWAIT_ON_JTAG（位字段掩码：0x01）*/
#define GPREG_DEBUG_REG_SYS_CPUWAIT_Pos   (6UL)                     /*!< SYS_CPUWAIT（位6）*/
#define GPREG_DEBUG_REG_SYS_CPUWAIT_Msk   (0x40UL)                  /*!< SYS_CPUWAIT（位字段掩码：0x01）*/
#define GPREG_DEBUG_REG_CMAC_CPU_IS_HALTED_Pos (5UL)                /*!< CMAC_PU_IS_HALTED（位5）*/
#define GPREG_DEBUG_REG_CMAC_CPU_IS_HALTED_Msk (0x20UL)             /*!< CMAC_PU_IS_HALTED（位字段掩码：0x01）*/
#define GPREG_DEBUG_REG_SYS_CPU_IS_HALTED_Pos (4UL)                 /*!< SYS_CPU_IS_HALTED（位4）*/
#define GPREG_DEBUG_REG_SYS_CPU_IS_HALTED_Msk (0x10UL)              /*!< SYS_CPU_IS_HALTED（位字段掩码：0x01）*/
#define GPREG_DEBUG_REG_HALT_CMAC_SYS_CPU_EN_Pos (3UL)              /*!< HALT_CMAC_SYS_CPU_EN（位3）*/
#define GPREG_DEBUG_REG_HALT_CMAC_SYS_CPU_EN_Msk (0x8UL)            /*!< HALT_CMAC_SYS_CPU_EN（位域掩码：0x01）*/
#define GPREG_DEBUG_REG_HALT_SYS_CMAC_CPU_EN_Pos (2UL)              /*!< HALT_SYS_CMAC_CPU_EN（位2）*/
#define GPREG_DEBUG_REG_HALT_SYS_CMAC_CPU_EN_Msk (0x4UL)            /*!< HALT_SYS_CMAC_CPU_EN（位字段掩码：0x01）*/
#define GPREG_DEBUG_REG_CMAC_CPU_FREEZE_EN_Pos (1UL)                /*!< CMAC_PU_FREEZE_EN（位1）*/
#define GPREG_DEBUG_REG_CMAC_CPU_FREEZE_EN_Msk (0x2UL)              /*!< CMAC_PU_FREEZE_EN（位域掩码：0x01）*/
#define GPREG_DEBUG_REG_SYS_CPU_FREEZE_EN_Pos (0UL)                 /*!< SYS_CPU_FREEZE_EN（位0）*/
#define GPREG_DEBUG_REG_SYS_CPU_FREEZE_EN_Msk (0x1UL)               /*!< SYS_CPU_FREEZE_EN（位字段掩码：0x01）*/
/* ====================================================  GP_CONTROL_REG  ===================================================== */
#define GPREG_GP_CONTROL_REG_CMAC_H2H_BRIDGE_BYPASS_Pos (1UL)       /*!< CMAC_2H_BRIDGE_BYPASS（位1）*/
#define GPREG_GP_CONTROL_REG_CMAC_H2H_BRIDGE_BYPASS_Msk (0x2UL)     /*!< CMAC_2H_BRIDGE_BYPASS（位域掩码：0x01）*/
/* =====================================================  GP_STATUS_REG  ===================================================== */
#define GPREG_GP_STATUS_REG_CAL_PHASE_Pos (0UL)                     /*!< CAL_PHASE（位0）*/
#define GPREG_GP_STATUS_REG_CAL_PHASE_Msk (0x1UL)                   /*!< CAL_PHASE（位字段掩码：0x01）*/
/* ===================================================  RESET_FREEZE_REG  ==================================================== */
#define GPREG_RESET_FREEZE_REG_FRZ_CMAC_WDOG_Pos (10UL)             /*!< FRZ_CMAC_WDOG（位10）*/
#define GPREG_RESET_FREEZE_REG_FRZ_CMAC_WDOG_Msk (0x400UL)          /*!< FRZ_CMAC_WDOG（位域掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM4_Pos (9UL)                 /*!< FRZ_SWTIM4（位9）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM4_Msk (0x200UL)             /*!< FRZ_SWTIM4（位字段掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM3_Pos (8UL)                 /*!< FRZ_SWTIM3（位8）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM3_Msk (0x100UL)             /*!< FRZ_SWTIM3（位字段掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_PWMLED_Pos (7UL)                 /*!< FRZ_PWMLED（位7）*/
#define GPREG_RESET_FREEZE_REG_FRZ_PWMLED_Msk (0x80UL)              /*!< FRZ_PWMLED（位域掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM2_Pos (6UL)                 /*!< FRZ_SWTIM2（位6）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM2_Msk (0x40UL)              /*!< FRZ_SWTIM2（位字段掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_DMA_Pos (5UL)                    /*!< FRZ_DMA（第5位）*/
#define GPREG_RESET_FREEZE_REG_FRZ_DMA_Msk (0x20UL)                 /*!< FRZ_DMA（位域掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_USB_Pos (4UL)                    /*!< FRZ_USB（位4）*/
#define GPREG_RESET_FREEZE_REG_FRZ_USB_Msk (0x10UL)                 /*!< FRZ_USB（位域掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SYS_WDOG_Pos (3UL)               /*!< FRZ_SYS_WDOG（位3）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SYS_WDOG_Msk (0x8UL)             /*!< FRZ_SYS_WDOG（位域掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_RESERVED_Pos (2UL)               /*!< FRZ_RESERVED（位2）*/
#define GPREG_RESET_FREEZE_REG_FRZ_RESERVED_Msk (0x4UL)             /*!< FRZ_RESERVED（位字段掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM_Pos (1UL)                  /*!< FRZ_SWTIM（位1）*/
#define GPREG_RESET_FREEZE_REG_FRZ_SWTIM_Msk (0x2UL)                /*!< FRZ_SWTIM（位字段掩码：0x01）*/
#define GPREG_RESET_FREEZE_REG_FRZ_WKUPTIM_Pos (0UL)                /*!< FRZ_WKUPTIM（位0）*/
#define GPREG_RESET_FREEZE_REG_FRZ_WKUPTIM_Msk (0x1UL)              /*!< FRZ_WKUPTIM（位域掩码：0x01）*/
/* ====================================================  SET_FREEZE_REG  ===================================================== */
#define GPREG_SET_FREEZE_REG_FRZ_CMAC_WDOG_Pos (10UL)               /*!< FRZ_CMAC_WDOG（位10）*/
#define GPREG_SET_FREEZE_REG_FRZ_CMAC_WDOG_Msk (0x400UL)            /*!< FRZ_CMAC_WDOG（位域掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM4_Pos (9UL)                   /*!< FRZ_SWTIM4（位9）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM4_Msk (0x200UL)               /*!< FRZ_SWTIM4（位字段掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM3_Pos (8UL)                   /*!< FRZ_SWTIM3（位8）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM3_Msk (0x100UL)               /*!< FRZ_SWTIM3（位字段掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_PWMLED_Pos (7UL)                   /*!< FRZ_PWMLED（位7）*/
#define GPREG_SET_FREEZE_REG_FRZ_PWMLED_Msk (0x80UL)                /*!< FRZ_PWMLED（位域掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM2_Pos (6UL)                   /*!< FRZ_SWTIM2（位6）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM2_Msk (0x40UL)                /*!< FRZ_SWTIM2（位字段掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_DMA_Pos  (5UL)                     /*!< FRZ_DMA（第5位）*/
#define GPREG_SET_FREEZE_REG_FRZ_DMA_Msk  (0x20UL)                  /*!< FRZ_DMA（位域掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_USB_Pos  (4UL)                     /*!< FRZ_USB（位4）*/
#define GPREG_SET_FREEZE_REG_FRZ_USB_Msk  (0x10UL)                  /*!< FRZ_USB（位域掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_SYS_WDOG_Pos (3UL)                 /*!< FRZ_SYS_WDOG（位3）*/
#define GPREG_SET_FREEZE_REG_FRZ_SYS_WDOG_Msk (0x8UL)               /*!< FRZ_SYS_WDOG（位域掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_RESERVED_Pos (2UL)                 /*!< FRZ_RESERVED（位2）*/
#define GPREG_SET_FREEZE_REG_FRZ_RESERVED_Msk (0x4UL)               /*!< FRZ_RESERVED（位字段掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM_Pos (1UL)                    /*!< FRZ_SWTIM（位1）*/
#define GPREG_SET_FREEZE_REG_FRZ_SWTIM_Msk (0x2UL)                  /*!< FRZ_SWTIM（位字段掩码：0x01）*/
#define GPREG_SET_FREEZE_REG_FRZ_WKUPTIM_Pos (0UL)                  /*!< FRZ_WKUPTIM（位0）*/
#define GPREG_SET_FREEZE_REG_FRZ_WKUPTIM_Msk (0x1UL)                /*!< FRZ_WKUPTIM（位域掩码：0x01）*/
/* ======================================================  USBPAD_REG  ======================================================= */
#define GPREG_USBPAD_REG_USBPHY_FORCE_SW2_ON_Pos (2UL)              /*!< USBPHY_FORCE_SW2_ON（位2）*/
#define GPREG_USBPAD_REG_USBPHY_FORCE_SW2_ON_Msk (0x4UL)            /*!< USBPHY_FORCE_SW2_ON（位域掩码：0x01）*/
#define GPREG_USBPAD_REG_USBPHY_FORCE_SW1_OFF_Pos (1UL)             /*!< USBPHY_FORCE_SSW1_OFF（位1）*/
#define GPREG_USBPAD_REG_USBPHY_FORCE_SW1_OFF_Msk (0x2UL)           /*!< USBPHY_FORCE_SSW1_OFF（位域掩码：0x01）*/
#define GPREG_USBPAD_REG_USBPAD_EN_Pos    (0UL)                     /*!< USBPAD_EN（位0）*/
#define GPREG_USBPAD_REG_USBPAD_EN_Msk    (0x1UL)                   /*!< USBPAD_EN（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */

/* ===============================================  I2C_ACK_GENERAL_CALL_REG  ================================================ */
#define I2C_I2C_ACK_GENERAL_CALL_REG_ACK_GEN_CALL_Pos (0UL)         /*!< ACK_GEN_CALL（位0）*/
#define I2C_I2C_ACK_GENERAL_CALL_REG_ACK_GEN_CALL_Msk (0x1UL)       /*!< ACK_GEN_CALL（位字段掩码：0x01）*/
/* =================================================  I2C_CLR_ACTIVITY_REG  ================================================== */
#define I2C_I2C_CLR_ACTIVITY_REG_CLR_ACTIVITY_Pos (0UL)             /*!< CLR_ACTIVITY（位0）*/
#define I2C_I2C_CLR_ACTIVITY_REG_CLR_ACTIVITY_Msk (0x1UL)           /*!< CLR_ACTIVITY（位字段掩码：0x01）*/
/* =================================================  I2C_CLR_GEN_CALL_REG  ================================================== */
#define I2C_I2C_CLR_GEN_CALL_REG_CLR_GEN_CALL_Pos (0UL)             /*!< CLR_GEN_CALL（位0）*/
#define I2C_I2C_CLR_GEN_CALL_REG_CLR_GEN_CALL_Msk (0x1UL)           /*!< CLR_GEN_CALL（位字段掩码：0x01）*/
/* ===================================================  I2C_CLR_INTR_REG  ==================================================== */
#define I2C_I2C_CLR_INTR_REG_CLR_INTR_Pos (0UL)                     /*!< CLR_INTR（位0）*/
#define I2C_I2C_CLR_INTR_REG_CLR_INTR_Msk (0x1UL)                   /*!< CLR_INTR（位字段掩码：0x01）*/
/* ==================================================  I2C_CLR_RD_REQ_REG  =================================================== */
#define I2C_I2C_CLR_RD_REQ_REG_CLR_RD_REQ_Pos (0UL)                 /*!< CLR_RD_REQ（位0）*/
#define I2C_I2C_CLR_RD_REQ_REG_CLR_RD_REQ_Msk (0x1UL)               /*!< CLR_RD_REQ（位字段掩码：0x01）*/
/* ==================================================  I2C_CLR_RX_DONE_REG  ================================================== */
#define I2C_I2C_CLR_RX_DONE_REG_CLR_RX_DONE_Pos (0UL)               /*!< CLR_RX_DONE（位0）*/
#define I2C_I2C_CLR_RX_DONE_REG_CLR_RX_DONE_Msk (0x1UL)             /*!< CLR_RX_DONE（位域掩码：0x01）*/
/* ==================================================  I2C_CLR_RX_OVER_REG  ================================================== */
#define I2C_I2C_CLR_RX_OVER_REG_CLR_RX_OVER_Pos (0UL)               /*!< CLR_RX_OVER（位0）*/
#define I2C_I2C_CLR_RX_OVER_REG_CLR_RX_OVER_Msk (0x1UL)             /*!< CLR_RX_OVER（位字段掩码：0x01）*/
/* =================================================  I2C_CLR_RX_UNDER_REG  ================================================== */
#define I2C_I2C_CLR_RX_UNDER_REG_CLR_RX_UNDER_Pos (0UL)             /*!< CLR_RX_UND（位0）*/
#define I2C_I2C_CLR_RX_UNDER_REG_CLR_RX_UNDER_Msk (0x1UL)           /*!< CLR_RX_UNDER（位字段掩码：0x01）*/
/* =================================================  I2C_CLR_START_DET_REG  ================================================= */
#define I2C_I2C_CLR_START_DET_REG_CLR_START_DET_Pos (0UL)           /*!< CLR_START_DET（位0）*/
#define I2C_I2C_CLR_START_DET_REG_CLR_START_DET_Msk (0x1UL)         /*!< CLR_START_DET（位字段掩码：0x01）*/
/* =================================================  I2C_CLR_STOP_DET_REG  ================================================== */
#define I2C_I2C_CLR_STOP_DET_REG_CLR_STOP_DET_Pos (0UL)             /*!< CLR_STOP_DET（位0）*/
#define I2C_I2C_CLR_STOP_DET_REG_CLR_STOP_DET_Msk (0x1UL)           /*!< CLR_STOP_DET（位字段掩码：0x01）*/
/* ==================================================  I2C_CLR_TX_ABRT_REG  ================================================== */
#define I2C_I2C_CLR_TX_ABRT_REG_CLR_TX_ABRT_Pos (0UL)               /*!< CLR_TX_ABRT（位0）*/
#define I2C_I2C_CLR_TX_ABRT_REG_CLR_TX_ABRT_Msk (0x1UL)             /*!< CLR_TX_ABRT（位字段掩码：0x01）*/
/* ==================================================  I2C_CLR_TX_OVER_REG  ================================================== */
#define I2C_I2C_CLR_TX_OVER_REG_CLR_TX_OVER_Pos (0UL)               /*!< CLR_TX_OVER（位0）*/
#define I2C_I2C_CLR_TX_OVER_REG_CLR_TX_OVER_Msk (0x1UL)             /*!< CLR_TX_OVER（位字段掩码：0x01）*/
/* ======================================================  I2C_CON_REG  ====================================================== */
#define I2C_I2C_CON_REG_I2C_STOP_DET_IF_MASTER_ACTIVE_Pos (10UL)    /*!< I2C_STOP_DET_IF_MASTER_ACTIVE（位10）*/
#define I2C_I2C_CON_REG_I2C_STOP_DET_IF_MASTER_ACTIVE_Msk (0x400UL) /*!< I2C_STOP_DET_IF_MASTER_ACTIVE（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_RX_FIFO_FULL_HLD_CTRL_Pos (9UL)         /*!< I2C_RX_FIFO_FULL_HLD_CTRL（第9位）*/
#define I2C_I2C_CON_REG_I2C_RX_FIFO_FULL_HLD_CTRL_Msk (0x200UL)     /*!< I2C_RX_FIFO_FULL_HLD_CTRL（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_TX_EMPTY_CTRL_Pos (8UL)                 /*!< I2C_TX_EMPTY_CTRL（位8）*/
#define I2C_I2C_CON_REG_I2C_TX_EMPTY_CTRL_Msk (0x100UL)             /*!< I2C_TX_EMPTY_CTRL（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_STOP_DET_IFADDRESSED_Pos (7UL)          /*!< I2C_STOP_DET_IFADDRESSED（第7位）*/
#define I2C_I2C_CON_REG_I2C_STOP_DET_IFADDRESSED_Msk (0x80UL)       /*!< I2C_STOP_DET_IFADDRESSED（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_SLAVE_DISABLE_Pos (6UL)                 /*!< I2C_SLAVE_DISABLE（位6）*/
#define I2C_I2C_CON_REG_I2C_SLAVE_DISABLE_Msk (0x40UL)              /*!< I2C_SLAVE_DISABLE（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_RESTART_EN_Pos (5UL)                    /*!< I2C_RESTART_EN（位5）*/
#define I2C_I2C_CON_REG_I2C_RESTART_EN_Msk (0x20UL)                 /*!< I2C_RESTART_EN（位域掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_10BITADDR_MASTER_Pos (4UL)              /*!< I2C_10BITADDR_MASTER（位4）*/
#define I2C_I2C_CON_REG_I2C_10BITADDR_MASTER_Msk (0x10UL)           /*!< I2C_10BITADDR_MASTER（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_10BITADDR_SLAVE_Pos (3UL)               /*!< I2C_10BITADDR_SLAVE（位3）*/
#define I2C_I2C_CON_REG_I2C_10BITADDR_SLAVE_Msk (0x8UL)             /*!< I2C_10BITADDR_SLAVE（位字段掩码：0x01）*/
#define I2C_I2C_CON_REG_I2C_SPEED_Pos     (1UL)                     /*!< I2C_SPEED（位1）*/
#define I2C_I2C_CON_REG_I2C_SPEED_Msk     (0x6UL)                   /*!< I2C_SPEED（位字段掩码：0x03）*/
#define I2C_I2C_CON_REG_I2C_MASTER_MODE_Pos (0UL)                   /*!< I2C_MASTER_MODE（位0）*/
#define I2C_I2C_CON_REG_I2C_MASTER_MODE_Msk (0x1UL)                 /*!< I2C_MASTER_MODE（位字段掩码：0x01）*/
/* ===================================================  I2C_DATA_CMD_REG  ==================================================== */
#define I2C_I2C_DATA_CMD_REG_I2C_RESTART_Pos (10UL)                 /*!< I2C_RESTART（位10）*/
#define I2C_I2C_DATA_CMD_REG_I2C_RESTART_Msk (0x400UL)              /*!< I2C_RESTART（位字段掩码：0x01）*/
#define I2C_I2C_DATA_CMD_REG_I2C_STOP_Pos (9UL)                     /*!< I2C_STOP（第9位）*/
#define I2C_I2C_DATA_CMD_REG_I2C_STOP_Msk (0x200UL)                 /*!< I2C_STOP（位字段掩码：0x01）*/
#define I2C_I2C_DATA_CMD_REG_I2C_CMD_Pos  (8UL)                     /*!< I2C_CMD（位8）*/
#define I2C_I2C_DATA_CMD_REG_I2C_CMD_Msk  (0x100UL)                 /*!< I2C_CMD（位字段掩码：0x01）*/
#define I2C_I2C_DATA_CMD_REG_I2C_DAT_Pos  (0UL)                     /*!< I2C_DAT（位0）*/
#define I2C_I2C_DATA_CMD_REG_I2C_DAT_Msk  (0xffUL)                  /*!< I2C_DAT（位字段掩码：0xff）*/
/* ====================================================  I2C_DMA_CR_REG  ===================================================== */
#define I2C_I2C_DMA_CR_REG_TDMAE_Pos      (1UL)                     /*!< TDMAE（位1）*/
#define I2C_I2C_DMA_CR_REG_TDMAE_Msk      (0x2UL)                   /*!< TDMAE（位域掩码：0x01）*/
#define I2C_I2C_DMA_CR_REG_RDMAE_Pos      (0UL)                     /*!< RDMAE（位0）*/
#define I2C_I2C_DMA_CR_REG_RDMAE_Msk      (0x1UL)                   /*!< RDMAE（位域掩码：0x01）*/
/* ===================================================  I2C_DMA_RDLR_REG  ==================================================== */
#define I2C_I2C_DMA_RDLR_REG_DMARDL_Pos   (0UL)                     /*!< DMARDL（位0）*/
#define I2C_I2C_DMA_RDLR_REG_DMARDL_Msk   (0x1fUL)                  /*!< DMARDL（位域掩码：0x1f）*/
/* ===================================================  I2C_DMA_TDLR_REG  ==================================================== */
#define I2C_I2C_DMA_TDLR_REG_DMATDL_Pos   (0UL)                     /*!< DMATDL（位0）*/
#define I2C_I2C_DMA_TDLR_REG_DMATDL_Msk   (0x1fUL)                  /*!< DMATDL（位域掩码：0x1f）*/
/* ====================================================  I2C_ENABLE_REG  ===================================================== */
#define I2C_I2C_ENABLE_REG_I2C_TX_CMD_BLOCK_Pos (2UL)               /*!< I2C_TX_CMD_BLOCK（位2）*/
#define I2C_I2C_ENABLE_REG_I2C_TX_CMD_BLOCK_Msk (0x4UL)             /*!< I2C_TX_CMD_BLOCK（位字段掩码：0x01）*/
#define I2C_I2C_ENABLE_REG_I2C_ABORT_Pos  (1UL)                     /*!< I2C_ABORT（位1）*/
#define I2C_I2C_ENABLE_REG_I2C_ABORT_Msk  (0x2UL)                   /*!< I2C_ABORT（位字段掩码：0x01）*/
#define I2C_I2C_ENABLE_REG_I2C_EN_Pos     (0UL)                     /*!< I2C_EN（位0）*/
#define I2C_I2C_ENABLE_REG_I2C_EN_Msk     (0x1UL)                   /*!< I2C_EN（位域掩码：0x01）*/
/* =================================================  I2C_ENABLE_STATUS_REG  ================================================= */
#define I2C_I2C_ENABLE_STATUS_REG_SLV_RX_DATA_LOST_Pos (2UL)        /*!< SLV_RX_DATA_LOST（位2）*/
#define I2C_I2C_ENABLE_STATUS_REG_SLV_RX_DATA_LOST_Msk (0x4UL)      /*!< SLV_RX_DATA_LOST（位字段掩码：0x01）*/
#define I2C_I2C_ENABLE_STATUS_REG_SLV_DISABLED_WHILE_BUSY_Pos (1UL) /*!< SLV_DISABLED_WHILE_BUSY（位1）*/
#define I2C_I2C_ENABLE_STATUS_REG_SLV_DISABLED_WHILE_BUSY_Msk (0x2UL) /*!< SLV_DISABLED_WHILE_BUSY（位字段掩码：0x01）*/
#define I2C_I2C_ENABLE_STATUS_REG_IC_EN_Pos (0UL)                   /*!< IC_EN（位0）*/
#define I2C_I2C_ENABLE_STATUS_REG_IC_EN_Msk (0x1UL)                 /*!< IC_EN（位域掩码：0x01）*/
/* ==================================================  I2C_FS_SCL_HCNT_REG  ================================================== */
#define I2C_I2C_FS_SCL_HCNT_REG_IC_FS_SCL_HCNT_Pos (0UL)            /*!< IC_FS_SCL_HCNT（位0）*/
#define I2C_I2C_FS_SCL_HCNT_REG_IC_FS_SCL_HCNT_Msk (0xffffUL)       /*!< IC_FS_SCL_HCNT（位字段掩码：0xffff）*/
/* ==================================================  I2C_FS_SCL_LCNT_REG  ================================================== */
#define I2C_I2C_FS_SCL_LCNT_REG_IC_FS_SCL_LCNT_Pos (0UL)            /*!< IC_FS_SCL_LCNT（位0）*/
#define I2C_I2C_FS_SCL_LCNT_REG_IC_FS_SCL_LCNT_Msk (0xffffUL)       /*!< IC_FS_SCL_LCNT（位字段掩码：0xffff）*/
/* ===================================================  I2C_HS_MADDR_REG  ==================================================== */
#define I2C_I2C_HS_MADDR_REG_I2C_IC_HS_MAR_Pos (0UL)                /*!< I2C_IC_HS_MAR（位0）*/
#define I2C_I2C_HS_MADDR_REG_I2C_IC_HS_MAR_Msk (0x7UL)              /*!< I2C_IC_HS_MAR（位字段掩码：0x07）*/
/* ==================================================  I2C_HS_SCL_HCNT_REG  ================================================== */
#define I2C_I2C_HS_SCL_HCNT_REG_IC_HS_SCL_HCNT_Pos (0UL)            /*!< IC_HS_SCL_HCNT（位0）*/
#define I2C_I2C_HS_SCL_HCNT_REG_IC_HS_SCL_HCNT_Msk (0xffffUL)       /*!< IC_HS_SCL_HCNT（位域掩码：0xffff）*/
/* ==================================================  I2C_HS_SCL_LCNT_REG  ================================================== */
#define I2C_I2C_HS_SCL_LCNT_REG_IC_HS_SCL_LCNT_Pos (0UL)            /*!< IC_HS_SCL_LCNT（位0）*/
#define I2C_I2C_HS_SCL_LCNT_REG_IC_HS_SCL_LCNT_Msk (0xffffUL)       /*!< IC_HS_SCL_LCNT（位域掩码：0xffff）*/
/* =================================================  I2C_IC_FS_SPKLEN_REG  ================================================== */
#define I2C_I2C_IC_FS_SPKLEN_REG_I2C_FS_SPKLEN_Pos (0UL)            /*!< I2C_FS_SPKLEN（位0）*/
#define I2C_I2C_IC_FS_SPKLEN_REG_I2C_FS_SPKLEN_Msk (0xffUL)         /*!< I2C_FS_SPKLEN（位字段掩码：0xff）*/
/* =================================================  I2C_IC_HS_SPKLEN_REG  ================================================== */
#define I2C_I2C_IC_HS_SPKLEN_REG_I2C_HS_SPKLEN_Pos (0UL)            /*!< I2C_HS_SPKLEN（位0）*/
#define I2C_I2C_IC_HS_SPKLEN_REG_I2C_HS_SPKLEN_Msk (0xffUL)         /*!< I2C_HS_SPKLEN（位字段掩码：0xff）*/
/* ===================================================  I2C_INTR_MASK_REG  =================================================== */
#define I2C_I2C_INTR_MASK_REG_M_SCL_STUCK_AT_LOW_Pos (14UL)         /*!< M_SCL_STUCK_AT_LOW（第14位）*/
#define I2C_I2C_INTR_MASK_REG_M_SCL_STUCK_AT_LOW_Msk (0x4000UL)     /*!< M_SCL_STUCK_AT_LOW（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_MASTER_ON_HOLD_Pos (13UL)           /*!< M_MASTER_ON_HOLD（位13）*/
#define I2C_I2C_INTR_MASK_REG_M_MASTER_ON_HOLD_Msk (0x2000UL)       /*!< M_MASTER_ON_HOLD（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_RESTART_DET_Pos (12UL)              /*!< M_RESTART_DET（第12位）*/
#define I2C_I2C_INTR_MASK_REG_M_RESTART_DET_Msk (0x1000UL)          /*!< M_RESTART_DET（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_GEN_CALL_Pos (11UL)                 /*!< M_GEN_CALL（位11）*/
#define I2C_I2C_INTR_MASK_REG_M_GEN_CALL_Msk (0x800UL)              /*!< M_GEN_CALL（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_START_DET_Pos (10UL)                /*!< M_START_DET（第10位）*/
#define I2C_I2C_INTR_MASK_REG_M_START_DET_Msk (0x400UL)             /*!< M_START_DET（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_STOP_DET_Pos (9UL)                  /*!< M_STOP_DET（第9位）*/
#define I2C_I2C_INTR_MASK_REG_M_STOP_DET_Msk (0x200UL)              /*!< M_STOP_DET（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_ACTIVITY_Pos (8UL)                  /*!< M_ACTIVITY（位8）*/
#define I2C_I2C_INTR_MASK_REG_M_ACTIVITY_Msk (0x100UL)              /*!< M_ACTIVITY（位域掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_DONE_Pos (7UL)                   /*!< M_RX_DONE（位7）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_DONE_Msk (0x80UL)                /*!< M_RX_DONE（位域掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_TX_ABRT_Pos (6UL)                   /*!< M_TX_ABRT（位6）*/
#define I2C_I2C_INTR_MASK_REG_M_TX_ABRT_Msk (0x40UL)                /*!< M_TX_ABRT（位域掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_RD_REQ_Pos (5UL)                    /*!< M_RD_REQ（第5位）*/
#define I2C_I2C_INTR_MASK_REG_M_RD_REQ_Msk (0x20UL)                 /*!< M_RD_REQ（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_TX_EMPTY_Pos (4UL)                  /*!< M_TX_EMPTY（位4）*/
#define I2C_I2C_INTR_MASK_REG_M_TX_EMPTY_Msk (0x10UL)               /*!< M_TX_EMPTY（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_TX_OVER_Pos (3UL)                   /*!< M_TX_OVER（位3）*/
#define I2C_I2C_INTR_MASK_REG_M_TX_OVER_Msk (0x8UL)                 /*!< M_TX_OVER（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_FULL_Pos (2UL)                   /*!< M_RX_FULL（位2）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_FULL_Msk (0x4UL)                 /*!< M_RX_FULL（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_OVER_Pos (1UL)                   /*!< M_RX_OVER（位1）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_OVER_Msk (0x2UL)                 /*!< M_RX_OVER（位字段掩码：0x01）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_UNDER_Pos (0UL)                  /*!< M_RX_UNDER（位0）*/
#define I2C_I2C_INTR_MASK_REG_M_RX_UNDER_Msk (0x1UL)                /*!< M_RX_UNDER（位域掩码：0x01）*/
/* ===================================================  I2C_INTR_STAT_REG  =================================================== */
#define I2C_I2C_INTR_STAT_REG_R_SCL_STUCK_AT_LOW_Pos (14UL)         /*!< R_SCL_STUCK_AT_LOW（第14位）*/
#define I2C_I2C_INTR_STAT_REG_R_SCL_STUCK_AT_LOW_Msk (0x4000UL)     /*!< R_SCL_STUCK_AT_LOW（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_MASTER_ON_HOLD_Pos (13UL)           /*!< R_MASTER_ON_HOLD（位13）*/
#define I2C_I2C_INTR_STAT_REG_R_MASTER_ON_HOLD_Msk (0x2000UL)       /*!< R_MASTER_ON_HOLD（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_RESTART_DET_Pos (12UL)              /*!< R_RESTART_DET（第12位）*/
#define I2C_I2C_INTR_STAT_REG_R_RESTART_DET_Msk (0x1000UL)          /*!< R_RESTART_DET（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_GEN_CALL_Pos (11UL)                 /*!< R_GEN_CALL（位11）*/
#define I2C_I2C_INTR_STAT_REG_R_GEN_CALL_Msk (0x800UL)              /*!< R_GEN_CALL（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_START_DET_Pos (10UL)                /*!< R_START_DET（第10位）*/
#define I2C_I2C_INTR_STAT_REG_R_START_DET_Msk (0x400UL)             /*!< R_START_DET（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_STOP_DET_Pos (9UL)                  /*!< R_STOP_DET（第9位）*/
#define I2C_I2C_INTR_STAT_REG_R_STOP_DET_Msk (0x200UL)              /*!< R_STOP_DET（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_ACTIVITY_Pos (8UL)                  /*!< R_ACTIVITY（位8）*/
#define I2C_I2C_INTR_STAT_REG_R_ACTIVITY_Msk (0x100UL)              /*!< R_ACTIVITY（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_DONE_Pos (7UL)                   /*!< R_RX_DONE（位7）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_DONE_Msk (0x80UL)                /*!< R_RX_DONE（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_TX_ABRT_Pos (6UL)                   /*!< R_TX_ABRT（位6）*/
#define I2C_I2C_INTR_STAT_REG_R_TX_ABRT_Msk (0x40UL)                /*!< R_TX_ABRT（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_RD_REQ_Pos (5UL)                    /*!< R_RD_REQ（第5位）*/
#define I2C_I2C_INTR_STAT_REG_R_RD_REQ_Msk (0x20UL)                 /*!< R_RD_REQ（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_TX_EMPTY_Pos (4UL)                  /*!< R_TX_EMPTY（位4）*/
#define I2C_I2C_INTR_STAT_REG_R_TX_EMPTY_Msk (0x10UL)               /*!< R_TX_EMPTY（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_TX_OVER_Pos (3UL)                   /*!< R_TX_OVER（位3）*/
#define I2C_I2C_INTR_STAT_REG_R_TX_OVER_Msk (0x8UL)                 /*!< R_TX_OVER（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_FULL_Pos (2UL)                   /*!< R_RX_FULL（位2）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_FULL_Msk (0x4UL)                 /*!< R_RX_FULL（位字段掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_OVER_Pos (1UL)                   /*!< R_RX_OVER（位1）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_OVER_Msk (0x2UL)                 /*!< R_RX_OVER（位域掩码：0x01）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_UNDER_Pos (0UL)                  /*!< R_RX_UNDER（位0）*/
#define I2C_I2C_INTR_STAT_REG_R_RX_UNDER_Msk (0x1UL)                /*!< R_RX_UNDER（位域掩码：0x01）*/
/* =================================================  I2C_RAW_INTR_STAT_REG  ================================================= */
#define I2C_I2C_RAW_INTR_STAT_REG_SCL_STUCK_AT_LOW_Pos (14UL)       /*!< SCL_STUCK_AT_LOW（第14位）*/
#define I2C_I2C_RAW_INTR_STAT_REG_SCL_STUCK_AT_LOW_Msk (0x4000UL)   /*!< SCL_STUCK_AT_LOW（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_MASTER_ON_HOLD_Pos (13UL)         /*!< MASTER_ON_HOLD（位13）*/
#define I2C_I2C_RAW_INTR_STAT_REG_MASTER_ON_HOLD_Msk (0x2000UL)     /*!< MASTER_ON_HOLD（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RESTART_DET_Pos (12UL)            /*!< RESTART_DET（第12位）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RESTART_DET_Msk (0x1000UL)        /*!< RESTART_DET（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_GEN_CALL_Pos (11UL)               /*!< GEN_CALL（位11）*/
#define I2C_I2C_RAW_INTR_STAT_REG_GEN_CALL_Msk (0x800UL)            /*!< GEN_CALL（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_START_DET_Pos (10UL)              /*!< START_DET（第10位）*/
#define I2C_I2C_RAW_INTR_STAT_REG_START_DET_Msk (0x400UL)           /*!< START_DET（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_STOP_DET_Pos (9UL)                /*!< STOP_DET（第9位）*/
#define I2C_I2C_RAW_INTR_STAT_REG_STOP_DET_Msk (0x200UL)            /*!< STOP_DET（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_ACTIVITY_Pos (8UL)                /*!< 活动（位8）*/
#define I2C_I2C_RAW_INTR_STAT_REG_ACTIVITY_Msk (0x100UL)            /*!< 活动（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_DONE_Pos (7UL)                 /*!< RX_DONE（位7）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_DONE_Msk (0x80UL)              /*!< RX_DONE（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_TX_ABRT_Pos (6UL)                 /*!< TX_ABRT（位6）*/
#define I2C_I2C_RAW_INTR_STAT_REG_TX_ABRT_Msk (0x40UL)              /*!< TX_ABRT（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RD_REQ_Pos (5UL)                  /*!< RD_REQ（第5位）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RD_REQ_Msk (0x20UL)               /*!< RD_REQ（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_TX_EMPTY_Pos (4UL)                /*!< TX_EMPTY（位4）*/
#define I2C_I2C_RAW_INTR_STAT_REG_TX_EMPTY_Msk (0x10UL)             /*!< TX_EMPTY（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_TX_OVER_Pos (3UL)                 /*!< TX_OVER（位3）*/
#define I2C_I2C_RAW_INTR_STAT_REG_TX_OVER_Msk (0x8UL)               /*!< TX_OVER（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_FULL_Pos (2UL)                 /*!< RX_FULL（位2）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_FULL_Msk (0x4UL)               /*!< RX_FULL（位字段掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_OVER_Pos (1UL)                 /*!< RX_OVER（位1）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_OVER_Msk (0x2UL)               /*!< RX_OVER（位域掩码：0x01）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_UNDER_Pos (0UL)                /*!< RX_UNDER（位0）*/
#define I2C_I2C_RAW_INTR_STAT_REG_RX_UNDER_Msk (0x1UL)              /*!< RX_UNDER（位域掩码：0x01）*/
/* =====================================================  I2C_RXFLR_REG  ===================================================== */
#define I2C_I2C_RXFLR_REG_RXFLR_Pos       (0UL)                     /*!< RXFLR（位0）*/
#define I2C_I2C_RXFLR_REG_RXFLR_Msk       (0x3fUL)                  /*!< RXFLR（位域掩码：0x3f）*/
/* =====================================================  I2C_RX_TL_REG  ===================================================== */
#define I2C_I2C_RX_TL_REG_RX_TL_Pos       (0UL)                     /*!< RX_TL（位0）*/
#define I2C_I2C_RX_TL_REG_RX_TL_Msk       (0x1fUL)                  /*!< RX_TL（位域掩码：0x1f）*/
/* ======================================================  I2C_SAR_REG  ====================================================== */
#define I2C_I2C_SAR_REG_IC_SAR_Pos        (0UL)                     /*!< IC_SAR（位0）*/
#define I2C_I2C_SAR_REG_IC_SAR_Msk        (0x3ffUL)                 /*!< IC_SAR（位域掩码：0x3ff）*/
/* ===================================================  I2C_SDA_HOLD_REG  ==================================================== */
#define I2C_I2C_SDA_HOLD_REG_I2C_SDA_RX_HOLD_Pos (16UL)             /*!< I2C_SDA_RX_HOLD（位16）*/
#define I2C_I2C_SDA_HOLD_REG_I2C_SDA_RX_HOLD_Msk (0xff0000UL)       /*!< I2C_SDA_RX_HOLD（位字段掩码：0xff）*/
#define I2C_I2C_SDA_HOLD_REG_I2C_SDA_TX_HOLD_Pos (0UL)              /*!< I2C_SDA_TX_HOLD（位0）*/
#define I2C_I2C_SDA_HOLD_REG_I2C_SDA_TX_HOLD_Msk (0xffffUL)         /*!< I2C_SDA_TX_HOLD（位字段掩码：0xffff）*/
/* ===================================================  I2C_SDA_SETUP_REG  =================================================== */
#define I2C_I2C_SDA_SETUP_REG_SDA_SETUP_Pos (0UL)                   /*!< SDA_SETUP（位0）*/
#define I2C_I2C_SDA_SETUP_REG_SDA_SETUP_Msk (0xffUL)                /*!< SDA_SETUP（位字段掩码：0xff）*/
/* ==================================================  I2C_SS_SCL_HCNT_REG  ================================================== */
#define I2C_I2C_SS_SCL_HCNT_REG_IC_SS_SCL_HCNT_Pos (0UL)            /*!< IC_SS_SCL_HCNT（位0）*/
#define I2C_I2C_SS_SCL_HCNT_REG_IC_SS_SCL_HCNT_Msk (0xffffUL)       /*!< IC_SS_SCL_HCNT（位字段掩码：0xffff）*/
/* ==================================================  I2C_SS_SCL_LCNT_REG  ================================================== */
#define I2C_I2C_SS_SCL_LCNT_REG_IC_SS_SCL_LCNT_Pos (0UL)            /*!< IC_SS_SCL_LCNT（位0）*/
#define I2C_I2C_SS_SCL_LCNT_REG_IC_SS_SCL_LCNT_Msk (0xffffUL)       /*!< IC_SS_SCL_LCNT（位字段掩码：0xffff）*/
/* ====================================================  I2C_STATUS_REG  ===================================================== */
#define I2C_I2C_STATUS_REG_LV_HOLD_RX_FIFO_FULL_Pos (10UL)          /*!< LV_HOLD_RX_FIFO_FULL（位10）*/
#define I2C_I2C_STATUS_REG_LV_HOLD_RX_FIFO_FULL_Msk (0x400UL)       /*!< LV_HOLD_RX_FIFO_FULL（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_SLV_HOLD_TX_FIFO_EMPTY_Pos (9UL)         /*!< SLV_HOLD_TX_FIFO_EMPTY（位9）*/
#define I2C_I2C_STATUS_REG_SLV_HOLD_TX_FIFO_EMPTY_Msk (0x200UL)     /*!< SLV_HOLD_TX_FIFO_EMPTY（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_MST_HOLD_RX_FIFO_FULL_Pos (8UL)          /*!< MST_HOLD_RX_FIFO_FULL（位8）*/
#define I2C_I2C_STATUS_REG_MST_HOLD_RX_FIFO_FULL_Msk (0x100UL)      /*!< MST_HOLD_RX_FIFO_FULL（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_MST_HOLD_TX_FIFO_EMPTY_Pos (7UL)         /*!< MST_HOLD_TX_FIFO_EMPTY（位7）*/
#define I2C_I2C_STATUS_REG_MST_HOLD_TX_FIFO_EMPTY_Msk (0x80UL)      /*!< MST_HOLD_TX_FIFO_EMPTY（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_SLV_ACTIVITY_Pos (6UL)                   /*!< SLV_ACTIVITY（位6）*/
#define I2C_I2C_STATUS_REG_SLV_ACTIVITY_Msk (0x40UL)                /*!< SLV_ACTIVITY（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_MST_ACTIVITY_Pos (5UL)                   /*!< MST_ACTIVITY（位5）*/
#define I2C_I2C_STATUS_REG_MST_ACTIVITY_Msk (0x20UL)                /*!< MST_ACTIVITY（位域掩码：0x01）*/
#define I2C_I2C_STATUS_REG_RFF_Pos        (4UL)                     /*!< RFF（位4）*/
#define I2C_I2C_STATUS_REG_RFF_Msk        (0x10UL)                  /*!< RFF（位域掩码：0x01）*/
#define I2C_I2C_STATUS_REG_RFNE_Pos       (3UL)                     /*!< RFNE（位3）*/
#define I2C_I2C_STATUS_REG_RFNE_Msk       (0x8UL)                   /*!< RFNE（位域掩码：0x01）*/
#define I2C_I2C_STATUS_REG_TFE_Pos        (2UL)                     /*!< TFE（位2）*/
#define I2C_I2C_STATUS_REG_TFE_Msk        (0x4UL)                   /*!< TFE（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_TFNF_Pos       (1UL)                     /*!< TFNF（位1）*/
#define I2C_I2C_STATUS_REG_TFNF_Msk       (0x2UL)                   /*!< TFNF（位字段掩码：0x01）*/
#define I2C_I2C_STATUS_REG_I2C_ACTIVITY_Pos (0UL)                   /*!< I2C_ACTIVITY（位0）*/
#define I2C_I2C_STATUS_REG_I2C_ACTIVITY_Msk (0x1UL)                 /*!< I2C_ACTIVITY（位字段掩码：0x01）*/
/* ======================================================  I2C_TAR_REG  ====================================================== */
#define I2C_I2C_TAR_REG_SPECIAL_Pos       (11UL)                    /*!< 特殊（位11）*/
#define I2C_I2C_TAR_REG_SPECIAL_Msk       (0x800UL)                 /*!< SPECIAL（位域掩码：0x01）*/
#define I2C_I2C_TAR_REG_GC_OR_START_Pos   (10UL)                    /*!< GC_OR_START（位10）*/
#define I2C_I2C_TAR_REG_GC_OR_START_Msk   (0x400UL)                 /*!< GC_OR_START（位域掩码：0x01）*/
#define I2C_I2C_TAR_REG_IC_TAR_Pos        (0UL)                     /*!< IC_TAR（位0）*/
#define I2C_I2C_TAR_REG_IC_TAR_Msk        (0x3ffUL)                 /*!< IC_TAR（位域掩码：0x3ff）*/
/* =====================================================  I2C_TXFLR_REG  ===================================================== */
#define I2C_I2C_TXFLR_REG_TXFLR_Pos       (0UL)                     /*!< TXFLR（位0）*/
#define I2C_I2C_TXFLR_REG_TXFLR_Msk       (0x3fUL)                  /*!< TXFLR（位域掩码：0x3f）*/
/* ================================================  I2C_TX_ABRT_SOURCE_REG  ================================================= */
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_USER_ABRT_Pos (16UL)        /*!< ABRT_USER_ABRT（位16）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_USER_ABRT_Msk (0x10000UL)   /*!< ABRT_USER_ABRT（位域掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SLVRD_INTX_Pos (15UL)       /*!< ABRT_SLVRD_INTX（位15）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SLVRD_INTX_Msk (0x8000UL)   /*!< ABRT_SLVRD_INTX（位域掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SLV_ARBLOST_Pos (14UL)      /*!< ABRT_SLV_ARBLOST（位14）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SLV_ARBLOST_Msk (0x4000UL)  /*!< ABRT_SLV_ARBLOST（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SLVFLUSH_TXFIFO_Pos (13UL)  /*!< ABRT_SLVFLUSH_TXFIFO（第13位）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SLVFLUSH_TXFIFO_Msk (0x2000UL) /*!< ABRT_SLVFLUSH_TXFIFO（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ARB_LOST_Pos (12UL)              /*!< ARB_LOST（位12）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ARB_LOST_Msk (0x1000UL)          /*!< ARB_LOST（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_MASTER_DIS_Pos (11UL)       /*!< ABRT_MASTER_DIS（位11）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_MASTER_DIS_Msk (0x800UL)    /*!< ABRT_MASTER_DIS（位域掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_10B_RD_NORSTRT_Pos (10UL)   /*!< ABRT_10B_RD_NORSTRT（位10）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_10B_RD_NORSTRT_Msk (0x400UL) /*!< ABRT_10B_RD_NORSTRT（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SBYTE_NORSTRT_Pos (9UL)     /*!< ABRT_SBYTE_NORSTRT（第9位）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SBYTE_NORSTRT_Msk (0x200UL) /*!< ABRT_SBYTE_NORSTRT（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_HS_NORSTRT_Pos (8UL)        /*!< ABRT_HS_NORSTRT（位8）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_HS_NORSTRT_Msk (0x100UL)    /*!< ABRT_HS_NORSTRT（位域掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SBYTE_ACKDET_Pos (7UL)      /*!< ABRT_SBYTE_ACKDET（位7）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_SBYTE_ACKDET_Msk (0x80UL)   /*!< ABRT_SBYTE_ACKDET（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_HS_ACKDET_Pos (6UL)         /*!< ABRT_HS_ACKDET（位6）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_HS_ACKDET_Msk (0x40UL)      /*!< ABRT_HS_ACKDET（位域掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_GCALL_READ_Pos (5UL)        /*!< ABRT_GCALL_READ（位5）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_GCALL_READ_Msk (0x20UL)     /*!< ABRT_GCALL_READ（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_GCALL_NOACK_Pos (4UL)       /*!< ABRT_GCALL_NOACK（位4）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_GCALL_NOACK_Msk (0x10UL)    /*!< ABRT_GCALL_NOACK（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_TXDATA_NOACK_Pos (3UL)      /*!< ABRT_TXDATA_NOACK（位3）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_TXDATA_NOACK_Msk (0x8UL)    /*!< ABRT_TXDATA_NOACK（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_10ADDR2_NOACK_Pos (2UL)     /*!< ABRT_10ADDR2_NOACK（位2）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_10ADDR2_NOACK_Msk (0x4UL)   /*!< ABRT_10ADDR2_NOACK（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_10ADDR1_NOACK_Pos (1UL)     /*!< ABRT_10ADDR1_NOACK（位1）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_10ADDR1_NOACK_Msk (0x2UL)   /*!< ABRT_10ADDR1_NOACK（位字段掩码：0x01）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_7B_ADDR_NOACK_Pos (0UL)     /*!< ABRT_7B_ADDR_NOACK（位0）*/
#define I2C_I2C_TX_ABRT_SOURCE_REG_ABRT_7B_ADDR_NOACK_Msk (0x1UL)   /*!< ABRT_7B_ADDR_NOACK（位字段掩码：0x01）*/
/* =====================================================  I2C_TX_TL_REG  ===================================================== */
#define I2C_I2C_TX_TL_REG_TX_TL_Pos       (0UL)                     /*!< TX_TL（位0）*/
#define I2C_I2C_TX_TL_REG_TX_TL_Msk       (0x1fUL)                  /*!< TX_TL（位域掩码：0x1f）*/


/* =========================================================================================================================== */
/* ================                                           I2C2                                            ================ */
/* =========================================================================================================================== */

/* ===============================================  I2C2_ACK_GENERAL_CALL_REG  =============================================== */
#define I2C2_I2C2_ACK_GENERAL_CALL_REG_ACK_GEN_CALL_Pos (0UL)       /*!< ACK_GEN_CALL（位0）*/
#define I2C2_I2C2_ACK_GENERAL_CALL_REG_ACK_GEN_CALL_Msk (0x1UL)     /*!< ACK_GEN_CALL（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_ACTIVITY_REG  ================================================= */
#define I2C2_I2C2_CLR_ACTIVITY_REG_CLR_ACTIVITY_Pos (0UL)           /*!< CLR_ACTIVITY（位0）*/
#define I2C2_I2C2_CLR_ACTIVITY_REG_CLR_ACTIVITY_Msk (0x1UL)         /*!< CLR_ACTIVITY（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_GEN_CALL_REG  ================================================= */
#define I2C2_I2C2_CLR_GEN_CALL_REG_CLR_GEN_CALL_Pos (0UL)           /*!< CLR_GEN_CALL（位0）*/
#define I2C2_I2C2_CLR_GEN_CALL_REG_CLR_GEN_CALL_Msk (0x1UL)         /*!< CLR_GEN_CALL（位字段掩码：0x01）*/
/* ===================================================  I2C2_CLR_INTR_REG  =================================================== */
#define I2C2_I2C2_CLR_INTR_REG_CLR_INTR_Pos (0UL)                   /*!< CLR_INTR（位0）*/
#define I2C2_I2C2_CLR_INTR_REG_CLR_INTR_Msk (0x1UL)                 /*!< CLR_INTR（位字段掩码：0x01）*/
/* ==================================================  I2C2_CLR_RD_REQ_REG  ================================================== */
#define I2C2_I2C2_CLR_RD_REQ_REG_CLR_RD_REQ_Pos (0UL)               /*!< CLR_RD_REQ（位0）*/
#define I2C2_I2C2_CLR_RD_REQ_REG_CLR_RD_REQ_Msk (0x1UL)             /*!< CLR_RD_REQ（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_RX_DONE_REG  ================================================== */
#define I2C2_I2C2_CLR_RX_DONE_REG_CLR_RX_DONE_Pos (0UL)             /*!< CLR_RX_DONE（位0）*/
#define I2C2_I2C2_CLR_RX_DONE_REG_CLR_RX_DONE_Msk (0x1UL)           /*!< CLR_RX_DONE（位域掩码：0x01）*/
/* =================================================  I2C2_CLR_RX_OVER_REG  ================================================== */
#define I2C2_I2C2_CLR_RX_OVER_REG_CLR_RX_OVER_Pos (0UL)             /*!< CLR_RX_OVER（位0）*/
#define I2C2_I2C2_CLR_RX_OVER_REG_CLR_RX_OVER_Msk (0x1UL)           /*!< CLR_RX_OVER（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_RX_UNDER_REG  ================================================= */
#define I2C2_I2C2_CLR_RX_UNDER_REG_CLR_RX_UNDER_Pos (0UL)           /*!< CLR_RX_UND（位0）*/
#define I2C2_I2C2_CLR_RX_UNDER_REG_CLR_RX_UNDER_Msk (0x1UL)         /*!< CLR_RX_UNDER（位字段掩码：0x01）*/
/* ================================================  I2C2_CLR_START_DET_REG  ================================================= */
#define I2C2_I2C2_CLR_START_DET_REG_CLR_START_DET_Pos (0UL)         /*!< CLR_START_DET（位0）*/
#define I2C2_I2C2_CLR_START_DET_REG_CLR_START_DET_Msk (0x1UL)       /*!< CLR_START_DET（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_STOP_DET_REG  ================================================= */
#define I2C2_I2C2_CLR_STOP_DET_REG_CLR_STOP_DET_Pos (0UL)           /*!< CLR_STOP_DET（位0）*/
#define I2C2_I2C2_CLR_STOP_DET_REG_CLR_STOP_DET_Msk (0x1UL)         /*!< CLR_STOP_DET（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_TX_ABRT_REG  ================================================== */
#define I2C2_I2C2_CLR_TX_ABRT_REG_CLR_TX_ABRT_Pos (0UL)             /*!< CLR_TX_ABRT（位0）*/
#define I2C2_I2C2_CLR_TX_ABRT_REG_CLR_TX_ABRT_Msk (0x1UL)           /*!< CLR_TX_ABRT（位字段掩码：0x01）*/
/* =================================================  I2C2_CLR_TX_OVER_REG  ================================================== */
#define I2C2_I2C2_CLR_TX_OVER_REG_CLR_TX_OVER_Pos (0UL)             /*!< CLR_TX_OVER（位0）*/
#define I2C2_I2C2_CLR_TX_OVER_REG_CLR_TX_OVER_Msk (0x1UL)           /*!< CLR_TX_OVER（位字段掩码：0x01）*/
/* =====================================================  I2C2_CON_REG  ====================================================== */
#define I2C2_I2C2_CON_REG_I2C_STOP_DET_IF_MASTER_ACTIVE_Pos (10UL)  /*!< I2C_STOP_DET_IF_MASTER_ACTIVE（位10）*/
#define I2C2_I2C2_CON_REG_I2C_STOP_DET_IF_MASTER_ACTIVE_Msk (0x400UL) /*!< I2C_STOP_DET_IF_MASTER_ACTIVE（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_RX_FIFO_FULL_HLD_CTRL_Pos (9UL)       /*!< I2C_RX_FIFO_FULL_HLD_CTRL（第9位）*/
#define I2C2_I2C2_CON_REG_I2C_RX_FIFO_FULL_HLD_CTRL_Msk (0x200UL)   /*!< I2C_RX_FIFO_FULL_HLD_CTRL（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_TX_EMPTY_CTRL_Pos (8UL)               /*!< I2C_TX_EMPTY_CTRL（位8）*/
#define I2C2_I2C2_CON_REG_I2C_TX_EMPTY_CTRL_Msk (0x100UL)           /*!< I2C_TX_EMPTY_CTRL（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_STOP_DET_IFADDRESSED_Pos (7UL)        /*!< I2C_STOP_DET_IFADDRESSED（第7位）*/
#define I2C2_I2C2_CON_REG_I2C_STOP_DET_IFADDRESSED_Msk (0x80UL)     /*!< I2C_STOP_DET_IFADDRESSED（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_SLAVE_DISABLE_Pos (6UL)               /*!< I2C_SLAVE_DISABLE（位6）*/
#define I2C2_I2C2_CON_REG_I2C_SLAVE_DISABLE_Msk (0x40UL)            /*!< I2C_SLAVE_DISABLE（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_RESTART_EN_Pos (5UL)                  /*!< I2C_RESTART_EN（位5）*/
#define I2C2_I2C2_CON_REG_I2C_RESTART_EN_Msk (0x20UL)               /*!< I2C_RESTART_EN（位域掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_10BITADDR_MASTER_Pos (4UL)            /*!< I2C_10BITADDR_MASTER（位4）*/
#define I2C2_I2C2_CON_REG_I2C_10BITADDR_MASTER_Msk (0x10UL)         /*!< I2C_10BITADDR_MASTER（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_10BITADDR_SLAVE_Pos (3UL)             /*!< I2C_10BITADDR_SLAVE（位3）*/
#define I2C2_I2C2_CON_REG_I2C_10BITADDR_SLAVE_Msk (0x8UL)           /*!< I2C_10BITADDR_SLAVE（位字段掩码：0x01）*/
#define I2C2_I2C2_CON_REG_I2C_SPEED_Pos   (1UL)                     /*!< I2C_SPEED（位1）*/
#define I2C2_I2C2_CON_REG_I2C_SPEED_Msk   (0x6UL)                   /*!< I2C_SPEED（位字段掩码：0x03）*/
#define I2C2_I2C2_CON_REG_I2C_MASTER_MODE_Pos (0UL)                 /*!< I2C_MASTER_MODE（位0）*/
#define I2C2_I2C2_CON_REG_I2C_MASTER_MODE_Msk (0x1UL)               /*!< I2C_MASTER_MODE（位字段掩码：0x01）*/
/* ===================================================  I2C2_DATA_CMD_REG  =================================================== */
#define I2C2_I2C2_DATA_CMD_REG_I2C_RESTART_Pos (10UL)               /*!< I2C_RESTART（位10）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_RESTART_Msk (0x400UL)            /*!< I2C_RESTART（位字段掩码：0x01）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_STOP_Pos (9UL)                   /*!< I2C_STOP（第9位）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_STOP_Msk (0x200UL)               /*!< I2C_STOP（位字段掩码：0x01）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_CMD_Pos (8UL)                    /*!< I2C_CMD（位8）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_CMD_Msk (0x100UL)                /*!< I2C_CMD（位字段掩码：0x01）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_DAT_Pos (0UL)                    /*!< I2C_DAT（位0）*/
#define I2C2_I2C2_DATA_CMD_REG_I2C_DAT_Msk (0xffUL)                 /*!< I2C_DAT（位字段掩码：0xff）*/
/* ====================================================  I2C2_DMA_CR_REG  ==================================================== */
#define I2C2_I2C2_DMA_CR_REG_TDMAE_Pos    (1UL)                     /*!< TDMAE（位1）*/
#define I2C2_I2C2_DMA_CR_REG_TDMAE_Msk    (0x2UL)                   /*!< TDMAE（位域掩码：0x01）*/
#define I2C2_I2C2_DMA_CR_REG_RDMAE_Pos    (0UL)                     /*!< RDMAE（位0）*/
#define I2C2_I2C2_DMA_CR_REG_RDMAE_Msk    (0x1UL)                   /*!< RDMAE（位域掩码：0x01）*/
/* ===================================================  I2C2_DMA_RDLR_REG  =================================================== */
#define I2C2_I2C2_DMA_RDLR_REG_DMARDL_Pos (0UL)                     /*!< DMARDL（位0）*/
#define I2C2_I2C2_DMA_RDLR_REG_DMARDL_Msk (0x1fUL)                  /*!< DMARDL（位域掩码：0x1f）*/
/* ===================================================  I2C2_DMA_TDLR_REG  =================================================== */
#define I2C2_I2C2_DMA_TDLR_REG_DMATDL_Pos (0UL)                     /*!< DMATDL（位0）*/
#define I2C2_I2C2_DMA_TDLR_REG_DMATDL_Msk (0x1fUL)                  /*!< DMATDL（位域掩码：0x1f）*/
/* ====================================================  I2C2_ENABLE_REG  ==================================================== */
#define I2C2_I2C2_ENABLE_REG_I2C_TX_CMD_BLOCK_Pos (2UL)             /*!< I2C_TX_CMD_BLOCK（位2）*/
#define I2C2_I2C2_ENABLE_REG_I2C_TX_CMD_BLOCK_Msk (0x4UL)           /*!< I2C_TX_CMD_BLOCK（位字段掩码：0x01）*/
#define I2C2_I2C2_ENABLE_REG_I2C_ABORT_Pos (1UL)                    /*!< I2C_ABORT（位1）*/
#define I2C2_I2C2_ENABLE_REG_I2C_ABORT_Msk (0x2UL)                  /*!< I2C_ABORT（位字段掩码：0x01）*/
#define I2C2_I2C2_ENABLE_REG_I2C_EN_Pos   (0UL)                     /*!< I2C_EN（位0）*/
#define I2C2_I2C2_ENABLE_REG_I2C_EN_Msk   (0x1UL)                   /*!< I2C_EN（位域掩码：0x01）*/
/* ================================================  I2C2_ENABLE_STATUS_REG  ================================================= */
#define I2C2_I2C2_ENABLE_STATUS_REG_SLV_RX_DATA_LOST_Pos (2UL)      /*!< SLV_RX_DATA_LOST（位2）*/
#define I2C2_I2C2_ENABLE_STATUS_REG_SLV_RX_DATA_LOST_Msk (0x4UL)    /*!< SLV_RX_DATA_LOST（位字段掩码：0x01）*/
#define I2C2_I2C2_ENABLE_STATUS_REG_SLV_DISABLED_WHILE_BUSY_Pos (1UL) /*!< SLV_DISABLED_WHILE_BUSY（位1）*/
#define I2C2_I2C2_ENABLE_STATUS_REG_SLV_DISABLED_WHILE_BUSY_Msk (0x2UL) /*!< SLV_DISABLED_WHILE_BUSY（位字段掩码：0x01）*/
#define I2C2_I2C2_ENABLE_STATUS_REG_IC_EN_Pos (0UL)                 /*!< IC_EN（位0）*/
#define I2C2_I2C2_ENABLE_STATUS_REG_IC_EN_Msk (0x1UL)               /*!< IC_EN（位域掩码：0x01）*/
/* =================================================  I2C2_FS_SCL_HCNT_REG  ================================================== */
#define I2C2_I2C2_FS_SCL_HCNT_REG_IC_FS_SCL_HCNT_Pos (0UL)          /*!< IC_FS_SCL_HCNT（位0）*/
#define I2C2_I2C2_FS_SCL_HCNT_REG_IC_FS_SCL_HCNT_Msk (0xffffUL)     /*!< IC_FS_SCL_HCNT（位字段掩码：0xffff）*/
/* =================================================  I2C2_FS_SCL_LCNT_REG  ================================================== */
#define I2C2_I2C2_FS_SCL_LCNT_REG_IC_FS_SCL_LCNT_Pos (0UL)          /*!< IC_FS_SCL_LCNT（位0）*/
#define I2C2_I2C2_FS_SCL_LCNT_REG_IC_FS_SCL_LCNT_Msk (0xffffUL)     /*!< IC_FS_SCL_LCNT（位字段掩码：0xffff）*/
/* ===================================================  I2C2_HS_MADDR_REG  =================================================== */
#define I2C2_I2C2_HS_MADDR_REG_I2C_IC_HS_MAR_Pos (0UL)              /*!< I2C_IC_HS_MAR（位0）*/
#define I2C2_I2C2_HS_MADDR_REG_I2C_IC_HS_MAR_Msk (0x7UL)            /*!< I2C_IC_HS_MAR（位字段掩码：0x07）*/
/* =================================================  I2C2_HS_SCL_HCNT_REG  ================================================== */
#define I2C2_I2C2_HS_SCL_HCNT_REG_IC_HS_SCL_HCNT_Pos (0UL)          /*!< IC_HS_SCL_HCNT（位0）*/
#define I2C2_I2C2_HS_SCL_HCNT_REG_IC_HS_SCL_HCNT_Msk (0xffffUL)     /*!< IC_HS_SCL_HCNT（位域掩码：0xffff）*/
/* =================================================  I2C2_HS_SCL_LCNT_REG  ================================================== */
#define I2C2_I2C2_HS_SCL_LCNT_REG_IC_HS_SCL_LCNT_Pos (0UL)          /*!< IC_HS_SCL_LCNT（位0）*/
#define I2C2_I2C2_HS_SCL_LCNT_REG_IC_HS_SCL_LCNT_Msk (0xffffUL)     /*!< IC_HS_SCL_LCNT（位域掩码：0xffff）*/
/* =================================================  I2C2_IC_FS_SPKLEN_REG  ================================================= */
#define I2C2_I2C2_IC_FS_SPKLEN_REG_I2C_FS_SPKLEN_Pos (0UL)          /*!< I2C_FS_SPKLEN（位0）*/
#define I2C2_I2C2_IC_FS_SPKLEN_REG_I2C_FS_SPKLEN_Msk (0xffUL)       /*!< I2C_FS_SPKLEN（位字段掩码：0xff）*/
/* =================================================  I2C2_IC_HS_SPKLEN_REG  ================================================= */
#define I2C2_I2C2_IC_HS_SPKLEN_REG_I2C_HS_SPKLEN_Pos (0UL)          /*!< I2C_HS_SPKLEN（位0）*/
#define I2C2_I2C2_IC_HS_SPKLEN_REG_I2C_HS_SPKLEN_Msk (0xffUL)       /*!< I2C_HS_SPKLEN（位字段掩码：0xff）*/
/* ==================================================  I2C2_INTR_MASK_REG  =================================================== */
#define I2C2_I2C2_INTR_MASK_REG_M_SCL_STUCK_AT_LOW_Pos (14UL)       /*!< M_SCL_STUCK_AT_LOW（第14位）*/
#define I2C2_I2C2_INTR_MASK_REG_M_SCL_STUCK_AT_LOW_Msk (0x4000UL)   /*!< M_SCL_STUCK_AT_LOW（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_MASTER_ON_HOLD_Pos (13UL)         /*!< M_MASTER_ON_HOLD（位13）*/
#define I2C2_I2C2_INTR_MASK_REG_M_MASTER_ON_HOLD_Msk (0x2000UL)     /*!< M_MASTER_ON_HOLD（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RESTART_DET_Pos (12UL)            /*!< M_RESTART_DET（第12位）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RESTART_DET_Msk (0x1000UL)        /*!< M_RESTART_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_GEN_CALL_Pos (11UL)               /*!< M_GEN_CALL（位11）*/
#define I2C2_I2C2_INTR_MASK_REG_M_GEN_CALL_Msk (0x800UL)            /*!< M_GEN_CALL（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_START_DET_Pos (10UL)              /*!< M_START_DET（第10位）*/
#define I2C2_I2C2_INTR_MASK_REG_M_START_DET_Msk (0x400UL)           /*!< M_START_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_STOP_DET_Pos (9UL)                /*!< M_STOP_DET（第9位）*/
#define I2C2_I2C2_INTR_MASK_REG_M_STOP_DET_Msk (0x200UL)            /*!< M_STOP_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_ACTIVITY_Pos (8UL)                /*!< M_ACTIVITY（位8）*/
#define I2C2_I2C2_INTR_MASK_REG_M_ACTIVITY_Msk (0x100UL)            /*!< M_ACTIVITY（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_DONE_Pos (7UL)                 /*!< M_RX_DONE（位7）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_DONE_Msk (0x80UL)              /*!< M_RX_DONE（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_TX_ABRT_Pos (6UL)                 /*!< M_TX_ABRT（位6）*/
#define I2C2_I2C2_INTR_MASK_REG_M_TX_ABRT_Msk (0x40UL)              /*!< M_TX_ABRT（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RD_REQ_Pos (5UL)                  /*!< M_RD_REQ（第5位）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RD_REQ_Msk (0x20UL)               /*!< M_RD_REQ（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_TX_EMPTY_Pos (4UL)                /*!< M_TX_EMPTY（位4）*/
#define I2C2_I2C2_INTR_MASK_REG_M_TX_EMPTY_Msk (0x10UL)             /*!< M_TX_EMPTY（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_TX_OVER_Pos (3UL)                 /*!< M_TX_OVER（位3）*/
#define I2C2_I2C2_INTR_MASK_REG_M_TX_OVER_Msk (0x8UL)               /*!< M_TX_OVER（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_FULL_Pos (2UL)                 /*!< M_RX_FULL（位2）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_FULL_Msk (0x4UL)               /*!< M_RX_FULL（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_OVER_Pos (1UL)                 /*!< M_RX_OVER（位1）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_OVER_Msk (0x2UL)               /*!< M_RX_OVER（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_UNDER_Pos (0UL)                /*!< M_RX_UNDER（位0）*/
#define I2C2_I2C2_INTR_MASK_REG_M_RX_UNDER_Msk (0x1UL)              /*!< M_RX_UNDER（位域掩码：0x01）*/
/* ==================================================  I2C2_INTR_STAT_REG  =================================================== */
#define I2C2_I2C2_INTR_STAT_REG_R_SCL_STUCK_AT_LOW_Pos (14UL)       /*!< R_SCL_STUCK_AT_LOW（第14位）*/
#define I2C2_I2C2_INTR_STAT_REG_R_SCL_STUCK_AT_LOW_Msk (0x4000UL)   /*!< R_SCL_STUCK_AT_LOW（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_MASTER_ON_HOLD_Pos (13UL)         /*!< R_MASTER_ON_HOLD（位13）*/
#define I2C2_I2C2_INTR_STAT_REG_R_MASTER_ON_HOLD_Msk (0x2000UL)     /*!< R_MASTER_ON_HOLD（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RESTART_DET_Pos (12UL)            /*!< R_RESTART_DET（第12位）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RESTART_DET_Msk (0x1000UL)        /*!< R_RESTART_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_GEN_CALL_Pos (11UL)               /*!< R_GEN_CALL（位11）*/
#define I2C2_I2C2_INTR_STAT_REG_R_GEN_CALL_Msk (0x800UL)            /*!< R_GEN_CALL（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_START_DET_Pos (10UL)              /*!< R_START_DET（第10位）*/
#define I2C2_I2C2_INTR_STAT_REG_R_START_DET_Msk (0x400UL)           /*!< R_START_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_STOP_DET_Pos (9UL)                /*!< R_STOP_DET（第9位）*/
#define I2C2_I2C2_INTR_STAT_REG_R_STOP_DET_Msk (0x200UL)            /*!< R_STOP_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_ACTIVITY_Pos (8UL)                /*!< R_ACTIVITY（位8）*/
#define I2C2_I2C2_INTR_STAT_REG_R_ACTIVITY_Msk (0x100UL)            /*!< R_ACTIVITY（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_DONE_Pos (7UL)                 /*!< R_RX_DONE（位7）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_DONE_Msk (0x80UL)              /*!< R_RX_DONE（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_TX_ABRT_Pos (6UL)                 /*!< R_TX_ABRT（位6）*/
#define I2C2_I2C2_INTR_STAT_REG_R_TX_ABRT_Msk (0x40UL)              /*!< R_TX_ABRT（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RD_REQ_Pos (5UL)                  /*!< R_RD_REQ（第5位）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RD_REQ_Msk (0x20UL)               /*!< R_RD_REQ（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_TX_EMPTY_Pos (4UL)                /*!< R_TX_EMPTY（位4）*/
#define I2C2_I2C2_INTR_STAT_REG_R_TX_EMPTY_Msk (0x10UL)             /*!< R_TX_EMPTY（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_TX_OVER_Pos (3UL)                 /*!< R_TX_OVER（位3）*/
#define I2C2_I2C2_INTR_STAT_REG_R_TX_OVER_Msk (0x8UL)               /*!< R_TX_OVER（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_FULL_Pos (2UL)                 /*!< R_RX_FULL（位2）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_FULL_Msk (0x4UL)               /*!< R_RX_FULL（位字段掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_OVER_Pos (1UL)                 /*!< R_RX_OVER（位1）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_OVER_Msk (0x2UL)               /*!< R_RX_OVER（位域掩码：0x01）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_UNDER_Pos (0UL)                /*!< R_RX_UNDER（位0）*/
#define I2C2_I2C2_INTR_STAT_REG_R_RX_UNDER_Msk (0x1UL)              /*!< R_RX_UNDER（位域掩码：0x01）*/
/* ================================================  I2C2_RAW_INTR_STAT_REG  ================================================= */
#define I2C2_I2C2_RAW_INTR_STAT_REG_SCL_STUCK_AT_LOW_Pos (14UL)     /*!< SCL_STUCK_AT_LOW（第14位）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_SCL_STUCK_AT_LOW_Msk (0x4000UL) /*!< SCL_STUCK_AT_LOW（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_MASTER_ON_HOLD_Pos (13UL)       /*!< MASTER_ON_HOLD（位13）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_MASTER_ON_HOLD_Msk (0x2000UL)   /*!< MASTER_ON_HOLD（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RESTART_DET_Pos (12UL)          /*!< RESTART_DET（第12位）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RESTART_DET_Msk (0x1000UL)      /*!< RESTART_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_GEN_CALL_Pos (11UL)             /*!< GEN_CALL（位11）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_GEN_CALL_Msk (0x800UL)          /*!< GEN_CALL（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_START_DET_Pos (10UL)            /*!< START_DET（第10位）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_START_DET_Msk (0x400UL)         /*!< START_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_STOP_DET_Pos (9UL)              /*!< STOP_DET（第9位）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_STOP_DET_Msk (0x200UL)          /*!< STOP_DET（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_ACTIVITY_Pos (8UL)              /*!< 活动（位8）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_ACTIVITY_Msk (0x100UL)          /*!< 活动（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_DONE_Pos (7UL)               /*!< RX_DONE（位7）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_DONE_Msk (0x80UL)            /*!< RX_DONE（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_TX_ABRT_Pos (6UL)               /*!< TX_ABRT（位6）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_TX_ABRT_Msk (0x40UL)            /*!< TX_ABRT（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RD_REQ_Pos (5UL)                /*!< RD_REQ（第5位）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RD_REQ_Msk (0x20UL)             /*!< RD_REQ（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_TX_EMPTY_Pos (4UL)              /*!< TX_EMPTY（位4）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_TX_EMPTY_Msk (0x10UL)           /*!< TX_EMPTY（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_TX_OVER_Pos (3UL)               /*!< TX_OVER（位3）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_TX_OVER_Msk (0x8UL)             /*!< TX_OVER（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_FULL_Pos (2UL)               /*!< RX_FULL（位2）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_FULL_Msk (0x4UL)             /*!< RX_FULL（位字段掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_OVER_Pos (1UL)               /*!< RX_OVER（位1）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_OVER_Msk (0x2UL)             /*!< RX_OVER（位域掩码：0x01）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_UNDER_Pos (0UL)              /*!< RX_UNDER（位0）*/
#define I2C2_I2C2_RAW_INTR_STAT_REG_RX_UNDER_Msk (0x1UL)            /*!< RX_UNDER（位域掩码：0x01）*/
/* ====================================================  I2C2_RXFLR_REG  ===================================================== */
#define I2C2_I2C2_RXFLR_REG_RXFLR_Pos     (0UL)                     /*!< RXFLR（位0）*/
#define I2C2_I2C2_RXFLR_REG_RXFLR_Msk     (0x3fUL)                  /*!< RXFLR（位域掩码：0x3f）*/
/* ====================================================  I2C2_RX_TL_REG  ===================================================== */
#define I2C2_I2C2_RX_TL_REG_RX_TL_Pos     (0UL)                     /*!< RX_TL（位0）*/
#define I2C2_I2C2_RX_TL_REG_RX_TL_Msk     (0x1fUL)                  /*!< RX_TL（位域掩码：0x1f）*/
/* =====================================================  I2C2_SAR_REG  ====================================================== */
#define I2C2_I2C2_SAR_REG_IC_SAR_Pos      (0UL)                     /*!< IC_SAR（位0）*/
#define I2C2_I2C2_SAR_REG_IC_SAR_Msk      (0x3ffUL)                 /*!< IC_SAR（位域掩码：0x3ff）*/
/* ===================================================  I2C2_SDA_HOLD_REG  =================================================== */
#define I2C2_I2C2_SDA_HOLD_REG_I2C_SDA_RX_HOLD_Pos (16UL)           /*!< I2C_SDA_RX_HOLD（位16）*/
#define I2C2_I2C2_SDA_HOLD_REG_I2C_SDA_RX_HOLD_Msk (0xff0000UL)     /*!< I2C_SDA_RX_HOLD（位字段掩码：0xff）*/
#define I2C2_I2C2_SDA_HOLD_REG_I2C_SDA_TX_HOLD_Pos (0UL)            /*!< I2C_SDA_TX_HOLD（位0）*/
#define I2C2_I2C2_SDA_HOLD_REG_I2C_SDA_TX_HOLD_Msk (0xffffUL)       /*!< I2C_SDA_TX_HOLD（位字段掩码：0xffff）*/
/* ==================================================  I2C2_SDA_SETUP_REG  =================================================== */
#define I2C2_I2C2_SDA_SETUP_REG_SDA_SETUP_Pos (0UL)                 /*!< SDA_SETUP（位0）*/
#define I2C2_I2C2_SDA_SETUP_REG_SDA_SETUP_Msk (0xffUL)              /*!< SDA_SETUP（位字段掩码：0xff）*/
/* =================================================  I2C2_SS_SCL_HCNT_REG  ================================================== */
#define I2C2_I2C2_SS_SCL_HCNT_REG_IC_SS_SCL_HCNT_Pos (0UL)          /*!< IC_SS_SCL_HCNT（位0）*/
#define I2C2_I2C2_SS_SCL_HCNT_REG_IC_SS_SCL_HCNT_Msk (0xffffUL)     /*!< IC_SS_SCL_HCNT（位字段掩码：0xffff）*/
/* =================================================  I2C2_SS_SCL_LCNT_REG  ================================================== */
#define I2C2_I2C2_SS_SCL_LCNT_REG_IC_SS_SCL_LCNT_Pos (0UL)          /*!< IC_SS_SCL_LCNT（位0）*/
#define I2C2_I2C2_SS_SCL_LCNT_REG_IC_SS_SCL_LCNT_Msk (0xffffUL)     /*!< IC_SS_SCL_LCNT（位字段掩码：0xffff）*/
/* ====================================================  I2C2_STATUS_REG  ==================================================== */
#define I2C2_I2C2_STATUS_REG_LV_HOLD_RX_FIFO_FULL_Pos (10UL)        /*!< LV_HOLD_RX_FIFO_FULL（位10）*/
#define I2C2_I2C2_STATUS_REG_LV_HOLD_RX_FIFO_FULL_Msk (0x400UL)     /*!< LV_HOLD_RX_FIFO_FULL（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_SLV_HOLD_TX_FIFO_EMPTY_Pos (9UL)       /*!< SLV_HOLD_TX_FIFO_EMPTY（位9）*/
#define I2C2_I2C2_STATUS_REG_SLV_HOLD_TX_FIFO_EMPTY_Msk (0x200UL)   /*!< SLV_HOLD_TX_FIFO_EMPTY（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_MST_HOLD_RX_FIFO_FULL_Pos (8UL)        /*!< MST_HOLD_RX_FIFO_FULL（位8）*/
#define I2C2_I2C2_STATUS_REG_MST_HOLD_RX_FIFO_FULL_Msk (0x100UL)    /*!< MST_HOLD_RX_FIFO_FULL（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_MST_HOLD_TX_FIFO_EMPTY_Pos (7UL)       /*!< MST_HOLD_TX_FIFO_EMPTY（位7）*/
#define I2C2_I2C2_STATUS_REG_MST_HOLD_TX_FIFO_EMPTY_Msk (0x80UL)    /*!< MST_HOLD_TX_FIFO_EMPTY（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_SLV_ACTIVITY_Pos (6UL)                 /*!< SLV_ACTIVITY（位6）*/
#define I2C2_I2C2_STATUS_REG_SLV_ACTIVITY_Msk (0x40UL)              /*!< SLV_ACTIVITY（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_MST_ACTIVITY_Pos (5UL)                 /*!< MST_ACTIVITY（位5）*/
#define I2C2_I2C2_STATUS_REG_MST_ACTIVITY_Msk (0x20UL)              /*!< MST_ACTIVITY（位域掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_RFF_Pos      (4UL)                     /*!< RFF（位4）*/
#define I2C2_I2C2_STATUS_REG_RFF_Msk      (0x10UL)                  /*!< RFF（位域掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_RFNE_Pos     (3UL)                     /*!< RFNE（位3）*/
#define I2C2_I2C2_STATUS_REG_RFNE_Msk     (0x8UL)                   /*!< RFNE（位域掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_TFE_Pos      (2UL)                     /*!< TFE（位2）*/
#define I2C2_I2C2_STATUS_REG_TFE_Msk      (0x4UL)                   /*!< TFE（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_TFNF_Pos     (1UL)                     /*!< TFNF（位1）*/
#define I2C2_I2C2_STATUS_REG_TFNF_Msk     (0x2UL)                   /*!< TFNF（位字段掩码：0x01）*/
#define I2C2_I2C2_STATUS_REG_I2C_ACTIVITY_Pos (0UL)                 /*!< I2C_ACTIVITY（位0）*/
#define I2C2_I2C2_STATUS_REG_I2C_ACTIVITY_Msk (0x1UL)               /*!< I2C_ACTIVITY（位字段掩码：0x01）*/
/* =====================================================  I2C2_TAR_REG  ====================================================== */
#define I2C2_I2C2_TAR_REG_SPECIAL_Pos     (11UL)                    /*!< 特殊（位11）*/
#define I2C2_I2C2_TAR_REG_SPECIAL_Msk     (0x800UL)                 /*!< SPECIAL（位域掩码：0x01）*/
#define I2C2_I2C2_TAR_REG_GC_OR_START_Pos (10UL)                    /*!< GC_OR_START（位10）*/
#define I2C2_I2C2_TAR_REG_GC_OR_START_Msk (0x400UL)                 /*!< GC_OR_START（位域掩码：0x01）*/
#define I2C2_I2C2_TAR_REG_IC_TAR_Pos      (0UL)                     /*!< IC_TAR（位0）*/
#define I2C2_I2C2_TAR_REG_IC_TAR_Msk      (0x3ffUL)                 /*!< IC_TAR（位域掩码：0x3ff）*/
/* ====================================================  I2C2_TXFLR_REG  ===================================================== */
#define I2C2_I2C2_TXFLR_REG_TXFLR_Pos     (0UL)                     /*!< TXFLR（位0）*/
#define I2C2_I2C2_TXFLR_REG_TXFLR_Msk     (0x3fUL)                  /*!< TXFLR（位域掩码：0x3f）*/
/* ================================================  I2C2_TX_ABRT_SOURCE_REG  ================================================ */
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_USER_ABRT_Pos (16UL)      /*!< ABRT_USER_ABRT（位16）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_USER_ABRT_Msk (0x10000UL) /*!< ABRT_USER_ABRT（位域掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SLVRD_INTX_Pos (15UL)     /*!< ABRT_SLVRD_INTX（位15）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SLVRD_INTX_Msk (0x8000UL) /*!< ABRT_SLVRD_INTX（位域掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SLV_ARBLOST_Pos (14UL)    /*!< ABRT_SLV_ARBLOST（位14）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SLV_ARBLOST_Msk (0x4000UL) /*!< ABRT_SLV_ARBLOST（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SLVFLUSH_TXFIFO_Pos (13UL) /*!< ABRT_SLVFLUSH_TXFIFO（第13位）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SLVFLUSH_TXFIFO_Msk (0x2000UL) /*!< ABRT_SLVFLUSH_TXFIFO（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ARB_LOST_Pos (12UL)            /*!< ARB_LOST（位12）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ARB_LOST_Msk (0x1000UL)        /*!< ARB_LOST（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_MASTER_DIS_Pos (11UL)     /*!< ABRT_MASTER_DIS（位11）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_MASTER_DIS_Msk (0x800UL)  /*!< ABRT_MASTER_DIS（位域掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_10B_RD_NORSTRT_Pos (10UL) /*!< ABRT_10B_RD_NORSTRT（位10）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_10B_RD_NORSTRT_Msk (0x400UL) /*!< ABRT_10B_RD_NORSTRT（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SBYTE_NORSTRT_Pos (9UL)   /*!< ABRT_SBYTE_NORSTRT（第9位）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SBYTE_NORSTRT_Msk (0x200UL) /*!< ABRT_SBYTE_NORSTRT（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_HS_NORSTRT_Pos (8UL)      /*!< ABRT_HS_NORSTRT（位8）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_HS_NORSTRT_Msk (0x100UL)  /*!< ABRT_HS_NORSTRT（位域掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SBYTE_ACKDET_Pos (7UL)    /*!< ABRT_SBYTE_ACKDET（位7）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_SBYTE_ACKDET_Msk (0x80UL) /*!< ABRT_SBYTE_ACKDET（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_HS_ACKDET_Pos (6UL)       /*!< ABRT_HS_ACKDET（位6）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_HS_ACKDET_Msk (0x40UL)    /*!< ABRT_HS_ACKDET（位域掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_GCALL_READ_Pos (5UL)      /*!< ABRT_GCALL_READ（位5）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_GCALL_READ_Msk (0x20UL)   /*!< ABRT_GCALL_READ（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_GCALL_NOACK_Pos (4UL)     /*!< ABRT_GCALL_NOACK（位4）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_GCALL_NOACK_Msk (0x10UL)  /*!< ABRT_GCALL_NOACK（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_TXDATA_NOACK_Pos (3UL)    /*!< ABRT_TXDATA_NOACK（位3）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_TXDATA_NOACK_Msk (0x8UL)  /*!< ABRT_TXDATA_NOACK（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_10ADDR2_NOACK_Pos (2UL)   /*!< ABRT_10ADDR2_NOACK（位2）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_10ADDR2_NOACK_Msk (0x4UL) /*!< ABRT_10ADDR2_NOACK（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_10ADDR1_NOACK_Pos (1UL)   /*!< ABRT_10ADDR1_NOACK（位1）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_10ADDR1_NOACK_Msk (0x2UL) /*!< ABRT_10ADDR1_NOACK（位字段掩码：0x01）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_7B_ADDR_NOACK_Pos (0UL)   /*!< ABRT_7B_ADDR_NOACK（位0）*/
#define I2C2_I2C2_TX_ABRT_SOURCE_REG_ABRT_7B_ADDR_NOACK_Msk (0x1UL) /*!< ABRT_7B_ADDR_NOACK（位字段掩码：0x01）*/
/* ====================================================  I2C2_TX_TL_REG  ===================================================== */
#define I2C2_I2C2_TX_TL_REG_TX_TL_Pos     (0UL)                     /*!< TX_TL（位0）*/
#define I2C2_I2C2_TX_TL_REG_TX_TL_Msk     (0x1fUL)                  /*!< TX_TL（位域掩码：0x1f）*/


/* =========================================================================================================================== */
/* ================                                           LCDC                                            ================ */
/* =========================================================================================================================== */

/* =================================================  LCDC_BACKPORCHXY_REG  ================================================== */
#define LCDC_LCDC_BACKPORCHXY_REG_LCDC_BPORCH_X_Pos (16UL)          /*!< LCDC_BPORCH_X（位16）*/
#define LCDC_LCDC_BACKPORCHXY_REG_LCDC_BPORCH_X_Msk (0xffff0000UL)  /*!< LCDC_BPORCH_X（位域掩码：0xffff）*/
#define LCDC_LCDC_BACKPORCHXY_REG_LCDC_BPORCH_Y_Pos (0UL)           /*!< LCDC_BORCH_Y（位0）*/
#define LCDC_LCDC_BACKPORCHXY_REG_LCDC_BPORCH_Y_Msk (0xffffUL)      /*!< LCDC_BORCH_Y（位域掩码：0xffff）*/
/* ===================================================  LCDC_BGCOLOR_REG  ==================================================== */
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_RED_Pos (24UL)                /*!< LCDC_BG_RED（位24）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_RED_Msk (0xff000000UL)        /*!< LCDC_BG_RED（位字段掩码：0xff）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_GREEN_Pos (16UL)              /*!< LCDC_BG_GREN（第16位）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_GREEN_Msk (0xff0000UL)        /*!< LCDC_BG_GREEN（位域掩码：0xff）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_BLUE_Pos (8UL)                /*!< LCDC_BG_BLUE（位8）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_BLUE_Msk (0xff00UL)           /*!< LCDC_BG_BLOE（位域掩码：0xff）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_ALPHA_Pos (0UL)               /*!< LCDC_BG_ALPHA（位0）*/
#define LCDC_LCDC_BGCOLOR_REG_LCDC_BG_ALPHA_Msk (0xffUL)            /*!< LCDC_BG_ALPHA（位域掩码：0xff）*/
/* ==================================================  LCDC_BLANKINGXY_REG  ================================================== */
#define LCDC_LCDC_BLANKINGXY_REG_LCDC_BLANKING_X_Pos (16UL)         /*!< LCDC_BLANKING_X（位16）*/
#define LCDC_LCDC_BLANKINGXY_REG_LCDC_BLANKING_X_Msk (0xffff0000UL) /*!< LCDC_BLANKING_X（位域掩码：0xffff）*/
#define LCDC_LCDC_BLANKINGXY_REG_LCDC_BLANKING_Y_Pos (0UL)          /*!< LCDC_BLANKING_Y（位0）*/
#define LCDC_LCDC_BLANKINGXY_REG_LCDC_BLANKING_Y_Msk (0xffffUL)     /*!< LCDC_BLANKING_Y（位域掩码：0xffff）*/
/* ===================================================  LCDC_CLKCTRL_REG  ==================================================== */
#define LCDC_LCDC_CLKCTRL_REG_LCDC_SEC_CLK_DIV_Pos (27UL)           /*!< LCDC_SEC_CLK_DIV（第27位）*/
#define LCDC_LCDC_CLKCTRL_REG_LCDC_SEC_CLK_DIV_Msk (0xf8000000UL)   /*!< LCDC_SEC_CLK_DIV（位域掩码：0x1f）*/
#define LCDC_LCDC_CLKCTRL_REG_LCDC_DMA_HOLD_Pos (8UL)               /*!< LCDC_DMA_HOLD（位8）*/
#define LCDC_LCDC_CLKCTRL_REG_LCDC_DMA_HOLD_Msk (0x3f00UL)          /*!< LCDC_DMA_HOLD（位域掩码：0x3f）*/
#define LCDC_LCDC_CLKCTRL_REG_LCDC_CLK_DIV_Pos (0UL)                /*!< LCDC_CLK_DIV（位0）*/
#define LCDC_LCDC_CLKCTRL_REG_LCDC_CLK_DIV_Msk (0x3fUL)             /*!< LCDC_CLK_DIV（位域掩码：0x3f）*/
/* =====================================================  LCDC_CRC_REG  ====================================================== */
#define LCDC_LCDC_CRC_REG_LCDC_CRC_Pos    (0UL)                     /*!< LCDC_CRC（位0）*/
#define LCDC_LCDC_CRC_REG_LCDC_CRC_Msk    (0xffffffffUL)            /*!< LCDC_CRC（位域掩码：0xffffffff）*/
/* ===================================================  LCDC_DBIB_CFG_REG  =================================================== */
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_TE_DIS_Pos (31UL)          /*!< LCDC_DIB_TE_DIS（第31位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_TE_DIS_Msk (0x80000000UL)  /*!< LCDC_DIB_TE_DIS（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_CSX_FORCE_Pos (30UL)       /*!< LCDC_DIB_CSX_FORCE（位30）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_CSX_FORCE_Msk (0x40000000UL) /*!< LCDC_DIB_CSX_FORCE（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_CSX_FORCE_VAL_Pos (29UL)   /*!< LCDC_DIB_CSX_FORCE_VAL（第29位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_CSX_FORCE_VAL_Msk (0x20000000UL) /*!< LCDC_DIB_CSX_FORCE_VAL（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_PAD_Pos (28UL)         /*!< LCDC_DIB_SPI_PAD（第28位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_PAD_Msk (0x10000000UL) /*!< LCDC_DIB_SPI_PAD（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_RESX_Pos (25UL)            /*!< LCDC_DIB_RESX（第25位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_RESX_Msk (0x2000000UL)     /*!< LCDC_DIB_RESX（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_DMA_EN_Pos (24UL)          /*!< LCDC_DIB_DMA_EN（位24）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_DMA_EN_Msk (0x1000000UL)   /*!< LCDC_DIB_DMA_EN（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI3_EN_Pos (23UL)         /*!< LCDC_DIB_SPI3_EN（第23位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI3_EN_Msk (0x800000UL)   /*!< LCDC_DIB_SPI3_EN（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI4_EN_Pos (22UL)         /*!< LCDC_DIB_SPI4_EN（第22位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI4_EN_Msk (0x400000UL)   /*!< LCDC_DIB_SPI4_EN（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_CPHA_Pos (20UL)        /*!< LCDC_DIB_SPI_CPHA（第20位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_CPHA_Msk (0x100000UL)  /*!< LCDC_DIB_SPI_CPHA（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_CPOL_Pos (19UL)        /*!< LCDC_DIB_SPI_CPOL（第19位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_CPOL_Msk (0x80000UL)   /*!< LCDC_DIB_SPI_CPOL（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_JDI_Pos (18UL)         /*!< LCDC_DIB_SPI_JDI（位18）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_JDI_Msk (0x40000UL)    /*!< LCDC_DIB_SPI_JDI（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_HOLD_Pos (17UL)        /*!< LCDC_DIB_SPI_HOLD（第17位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_HOLD_Msk (0x20000UL)   /*!< LCDC_DIB_SPI_HOLD（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_INV_ADDR_Pos (16UL)    /*!< LCDC_DIB_SPI_INV_ADDR（位16）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_SPI_INV_ADDR_Msk (0x10000UL) /*!< LCDC_DIB_SPI_INV_ADDR（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_INV_DATA_Pos (15UL)        /*!< LCDC_DIB_INV_DATA（第15位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_INV_DATA_Msk (0x8000UL)    /*!< LCDC_DIB_INV_DATA（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_JDI_INV_PIX_Pos (14UL)     /*!< LCDC_DIB_JDI_INV_PIX（位14）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_JDI_INV_PIX_Msk (0x4000UL) /*!< LCDC_DIB_JDI_INV_PIX（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_JDI_SOFT_RST_Pos (13UL)    /*!< LCDC_DIB_JDI_SOFT_RST（第13位）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_JDI_SOFT_RST_Msk (0x2000UL) /*!< LCDC_DIB_JDI_SOFT_RST（位域掩码：0x01）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_FMT_Pos (0UL)              /*!< LCDC_DIB_FMT（位0）*/
#define LCDC_LCDC_DBIB_CFG_REG_LCDC_DBIB_FMT_Msk (0x1fUL)           /*!< LCDC_DIB_FMT（位域掩码：0x1f）*/
/* ===================================================  LCDC_DBIB_CMD_REG  =================================================== */
#define LCDC_LCDC_DBIB_CMD_REG_LCDC_DBIB_CMD_SEND_Pos (30UL)        /*!< LCDC_DIB_CMD_SEND（位30）*/
#define LCDC_LCDC_DBIB_CMD_REG_LCDC_DBIB_CMD_SEND_Msk (0x40000000UL) /*!< LCDC_DBIB_CMD_SEND（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CMD_REG_LCDC_DBIB_CMD_STORE_Pos (27UL)       /*!< LCDC_DIB_CMD_STORE（第27位）*/
#define LCDC_LCDC_DBIB_CMD_REG_LCDC_DBIB_CMD_STORE_Msk (0x8000000UL) /*!< LCDC_DBIB_CMD_STORE（位字段掩码：0x01）*/
#define LCDC_LCDC_DBIB_CMD_REG_LCDC_DBIB_CMD_VAL_Pos (0UL)          /*!< LCDC_DIB_CMD_VAL（位0）*/
#define LCDC_LCDC_DBIB_CMD_REG_LCDC_DBIB_CMD_VAL_Msk (0xffffUL)     /*!< LCDC_DIB_CMD_VAL（位域掩码：0xffff）*/
/* =================================================  LCDC_FRONTPORCHXY_REG  ================================================= */
#define LCDC_LCDC_FRONTPORCHXY_REG_LCDC_FPORCH_X_Pos (16UL)         /*!< LCDC_FORCH_X（位16）*/
#define LCDC_LCDC_FRONTPORCHXY_REG_LCDC_FPORCH_X_Msk (0xffff0000UL) /*!< LCDC_FORCH_X（位域掩码：0xffff）*/
#define LCDC_LCDC_FRONTPORCHXY_REG_LCDC_FPORCH_Y_Pos (0UL)          /*!< LCDC_FORCH_Y（位0）*/
#define LCDC_LCDC_FRONTPORCHXY_REG_LCDC_FPORCH_Y_Msk (0xffffUL)     /*!< LCDC_FORCH_Y（位域掩码：0xffff）*/
/* =====================================================  LCDC_GPIO_REG  ===================================================== */
#define LCDC_LCDC_GPIO_REG_LCDC_TE_INV_Pos (1UL)                    /*!< LCDC_TE_INV（位1）*/
#define LCDC_LCDC_GPIO_REG_LCDC_TE_INV_Msk (0x2UL)                  /*!< LCDC_TE_INV（位字段掩码：0x01）*/
#define LCDC_LCDC_GPIO_REG_LCDC_PARIF_SEL_Pos (0UL)                 /*!< LCDC_PARIF_SEL（位0）*/
#define LCDC_LCDC_GPIO_REG_LCDC_PARIF_SEL_Msk (0x1UL)               /*!< LCDC_PARIF_SEL（位字段掩码：0x01）*/
/* ====================================================  LCDC_IDREG_REG  ===================================================== */
#define LCDC_LCDC_IDREG_REG_LCDC_ID_Pos   (0UL)                     /*!< LCDC_ID（位0）*/
#define LCDC_LCDC_IDREG_REG_LCDC_ID_Msk   (0xffffffffUL)            /*!< LCDC_ID（位域掩码：0xffffffff）*/
/* ==================================================  LCDC_INTERRUPT_REG  =================================================== */
#define LCDC_LCDC_INTERRUPT_REG_LCDC_IRQ_TRIGGER_SEL_Pos (31UL)     /*!< LCDC_IRQ_TRIGGER_SEL（第31位）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_IRQ_TRIGGER_SEL_Msk (0x80000000UL) /*!< LCDC_IRQ_TRIGGER_SEL（位字段掩码：0x01）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_FRAME_END_IRQ_EN_Pos (5UL)     /*!< LCDC_FRAME_END_IRQ_EN（第5位）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_FRAME_END_IRQ_EN_Msk (0x20UL)  /*!< LCDC_FRAME_END_IRQ_EN（位字段掩码：0x01）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_TE_IRQ_EN_Pos (3UL)            /*!< LCDC_TE_IRQ_EN（位3）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_TE_IRQ_EN_Msk (0x8UL)          /*!< LCDC_TE_IRQ_EN（位字段掩码：0x01）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_HSYNC_IRQ_EN_Pos (1UL)         /*!< LCDC_HYNC_IRQ_EN（位1）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_HSYNC_IRQ_EN_Msk (0x2UL)       /*!< LCDC_HYNC_IRQ_EN（位域掩码：0x01）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_VSYNC_IRQ_EN_Pos (0UL)         /*!< LCDC_VSYNC_IRQ_EN（位0）*/
#define LCDC_LCDC_INTERRUPT_REG_LCDC_VSYNC_IRQ_EN_Msk (0x1UL)       /*!< LCDC_VSYNC_IRQ_EN（位域掩码：0x01）*/
/* ==============================================  LCDC_JDI_ENB_END_HLINE_REG  =============================================== */
#define LCDC_LCDC_JDI_ENB_END_HLINE_REG_LCDC_JDI_ENB_END_HLINE_Pos (0UL) /*!< LCDC_JDI_ENB_END_HLINE（位0）*/
#define LCDC_LCDC_JDI_ENB_END_HLINE_REG_LCDC_JDI_ENB_END_HLINE_Msk (0xffffffffUL) /*!< LCDC_JDI_ENB_END_HLINE（位域掩码：0xffffff）*/
/* ==============================================  LCDC_JDI_ENB_START_CLK_REG  =============================================== */
#define LCDC_LCDC_JDI_ENB_START_CLK_REG_LCDC_JDI_ENB_START_CLK_Pos (0UL) /*!< LCDC_JDI_ENB_START_CLK（位0）*/
#define LCDC_LCDC_JDI_ENB_START_CLK_REG_LCDC_JDI_ENB_START_CLK_Msk (0xffffffffUL) /*!< LCDC_JDI_ENB_START_CLK（位域掩码：0xffffff）*/
/* =============================================  LCDC_JDI_ENB_START_HLINE_REG  ============================================== */
#define LCDC_LCDC_JDI_ENB_START_HLINE_REG_LCDC_JDI_ENB_START_HLINE_Pos (0UL) /*!< LCDC_JDI_ENB_START_HLINE（位0）*/
#define LCDC_LCDC_JDI_ENB_START_HLINE_REG_LCDC_JDI_ENB_START_HLINE_Msk (0xffffffffUL) /*!< LCDC_JDI_ENB_START_HLINE（位域掩码：0xffffff）*/
/* ==============================================  LCDC_JDI_ENB_WIDTH_CLK_REG  =============================================== */
#define LCDC_LCDC_JDI_ENB_WIDTH_CLK_REG_LCDC_JDI_ENB_WIDTH_CLK_Pos (0UL) /*!< LCDC_JDI_ENB_WIDTH_CLK（位0）*/
#define LCDC_LCDC_JDI_ENB_WIDTH_CLK_REG_LCDC_JDI_ENB_WIDTH_CLK_Msk (0xffffffffUL) /*!< LCDC_JDI_ENB_WIDTH_CLK（位域掩码：0xffffff）*/
/* ===============================================  LCDC_JDI_FBX_BLANKING_REG  =============================================== */
#define LCDC_LCDC_JDI_FBX_BLANKING_REG_LCDC_JDI_FXBLANKING_Pos (16UL) /*!< LCDC_JDI_FXBLANKING（位16）*/
#define LCDC_LCDC_JDI_FBX_BLANKING_REG_LCDC_JDI_FXBLANKING_Msk (0xffff0000UL) /*!< LCDC_JDI_FXBLANKING（位域掩码：0xffff）*/
#define LCDC_LCDC_JDI_FBX_BLANKING_REG_LCDC_JDI_BXBLANKING_Pos (0UL) /*!< LCDC_JDI_BX BLANKING（位0）*/
#define LCDC_LCDC_JDI_FBX_BLANKING_REG_LCDC_JDI_BXBLANKING_Msk (0xffffUL) /*!< LCDC_JDI_BXBLANKING（位域掩码：0xffff）*/
/* ===============================================  LCDC_JDI_FBY_BLANKING_REG  =============================================== */
#define LCDC_LCDC_JDI_FBY_BLANKING_REG_LCDC_JDI_FYBLANKING_Pos (16UL) /*!< LCDC_JDI_FYBLANKING（位16）*/
#define LCDC_LCDC_JDI_FBY_BLANKING_REG_LCDC_JDI_FYBLANKING_Msk (0xffff0000UL) /*!< LCDC_JDI_FYBLANKING（位域掩码：0xffff）*/
#define LCDC_LCDC_JDI_FBY_BLANKING_REG_LCDC_JDI_BYBLANKING_Pos (0UL) /*!< LCDC_JDI_BYBLANKING（位0）*/
#define LCDC_LCDC_JDI_FBY_BLANKING_REG_LCDC_JDI_BYBLANKING_Msk (0xffffUL) /*!< LCDC_JDI_BYBLANKING（位域掩码：0xffff）*/
/* ================================================  LCDC_JDI_HCK_WIDTH_REG  ================================================= */
#define LCDC_LCDC_JDI_HCK_WIDTH_REG_LCDC_JDI_HCK_WIDTH_Pos (0UL)    /*!< LCDC_JDI_HCK_WIDTH（位0）*/
#define LCDC_LCDC_JDI_HCK_WIDTH_REG_LCDC_JDI_HCK_WIDTH_Msk (0xffffffffUL) /*!< LCDC_JDI_HCK_WIDTH（位域掩码：0xffffff）*/
/* ================================================  LCDC_JDI_HST_DELAY_REG  ================================================= */
#define LCDC_LCDC_JDI_HST_DELAY_REG_LCDC_JDI_HST_DELAY_Pos (0UL)    /*!< LCDC_JDI_HST_DELAY（位0）*/
#define LCDC_LCDC_JDI_HST_DELAY_REG_LCDC_JDI_HST_DELAY_Msk (0xffffffffUL) /*!< LCDC_JDI_HST_DELAY（位字段掩码：0xffffff）*/
/* ================================================  LCDC_JDI_HST_WIDTH_REG  ================================================= */
#define LCDC_LCDC_JDI_HST_WIDTH_REG_LCDC_JDI_HST_WIDTH_Pos (0UL)    /*!< LCDC_JDI_HST_WIDTH（位0）*/
#define LCDC_LCDC_JDI_HST_WIDTH_REG_LCDC_JDI_HST_WIDTH_Msk (0xffffffffUL) /*!< LCDC_JDI_HST_WIDTH（位域掩码：0xffffff）*/
/* ==================================================  LCDC_JDI_RESXY_REG  =================================================== */
#define LCDC_LCDC_JDI_RESXY_REG_LCDC_JDI_RES_X_Pos (16UL)           /*!< LCDC_JDI_RES_X（位16）*/
#define LCDC_LCDC_JDI_RESXY_REG_LCDC_JDI_RES_X_Msk (0xffff0000UL)   /*!< LCDC_JDI_RES_X（位域掩码：0xffff）*/
#define LCDC_LCDC_JDI_RESXY_REG_LCDC_JDI_RES_Y_Pos (0UL)            /*!< LCDC_JDI_RES_Y（位0）*/
#define LCDC_LCDC_JDI_RESXY_REG_LCDC_JDI_RES_Y_Msk (0xffffUL)       /*!< LCDC_JDI_RES_Y（位域掩码：0xffff）*/
/* ================================================  LCDC_JDI_VCK_DELAY_REG  ================================================= */
#define LCDC_LCDC_JDI_VCK_DELAY_REG_LCDC_JDI_VCK_DELAY_Pos (0UL)    /*!< LCDC_JDI_VCK_DELAY（位0）*/
#define LCDC_LCDC_JDI_VCK_DELAY_REG_LCDC_JDI_VCK_DELAY_Msk (0xffffffffUL) /*!< LCDC_JDI_VCK_DELAY（位字段掩码：0xffffff）*/
/* ================================================  LCDC_JDI_VST_DELAY_REG  ================================================= */
#define LCDC_LCDC_JDI_VST_DELAY_REG_LCDC_JDI_VST_DELAY_Pos (0UL)    /*!< LCDC_JDI_VST_DELAY（位0）*/
#define LCDC_LCDC_JDI_VST_DELAY_REG_LCDC_JDI_VST_DELAY_Msk (0xffffffffUL) /*!< LCDC_JDI_VST_DELAY（位字段掩码：0xffffff）*/
/* ================================================  LCDC_JDI_VST_WIDTH_REG  ================================================= */
#define LCDC_LCDC_JDI_VST_WIDTH_REG_LCDC_JDI_VST_WIDTH_Pos (0UL)    /*!< LCDC_JDI_VST_WIDTH（位0）*/
#define LCDC_LCDC_JDI_VST_WIDTH_REG_LCDC_JDI_VST_WIDTH_Msk (0xffffffffUL) /*!< LCDC_JDI_VST_WIDTH（位域掩码：0xffffff）*/
/* ================================================  LCDC_JDI_XRST_WIDTH_REG  ================================================ */
#define LCDC_LCDC_JDI_XRST_WIDTH_REG_LCDC_JDI_XRST_WIDTH_Pos (0UL)  /*!< LCDC_JDI_XRST_WIDTH（位0）*/
#define LCDC_LCDC_JDI_XRST_WIDTH_REG_LCDC_JDI_XRST_WIDTH_Msk (0xffffffffUL) /*!< LCDC_JDI_XRST_WIDTH（位域掩码：0xffffff）*/
/* ===============================================  LCDC_LAYER0_BASEADDR_REG  ================================================ */
#define LCDC_LCDC_LAYER0_BASEADDR_REG_LCDC_L0_FB_ADDR_Pos (0UL)     /*!< LCDC_L0_FB_ADDR（位0）*/
#define LCDC_LCDC_LAYER0_BASEADDR_REG_LCDC_L0_FB_ADDR_Msk (0xffffffffUL) /*!< LCDC_L0_FB_ADDR（位字段掩码：0xffffff）*/
/* =================================================  LCDC_LAYER0_MODE_REG  ================================================== */
#define LCDC_LCDC_LAYER0_MODE_REG_LCDC_L0_EN_Pos (31UL)             /*!< LCDC_L0_EN（第31位）*/
#define LCDC_LCDC_LAYER0_MODE_REG_LCDC_L0_EN_Msk (0x80000000UL)     /*!< LCDC_L0_EN（位字段掩码：0x01）*/
#define LCDC_LCDC_LAYER0_MODE_REG_LCDC_L0_COLOUR_MODE_Pos (0UL)     /*!< LCDC_L0_COLOUR_MODE（位0）*/
#define LCDC_LCDC_LAYER0_MODE_REG_LCDC_L0_COLOUR_MODE_Msk (0x1fUL)  /*!< LCDC_L0_COLOUR_MODE（位场掩码：0x1f）*/
/* ================================================  LCDC_LAYER0_OFFSETX_REG  ================================================ */
#define LCDC_LCDC_LAYER0_OFFSETX_REG_LCDC_L0_DMA_PREFETCH_Pos (16UL) /*!< LCDC_L0_DMA_PREFETCH（第16位）*/
#define LCDC_LCDC_LAYER0_OFFSETX_REG_LCDC_L0_DMA_PREFETCH_Msk (0xffff0000UL) /*!< LCDC_L0_DMA_PREFETCH（位域掩码：0xffff）*/
#define LCDC_LCDC_LAYER0_OFFSETX_REG_LCDC_L0_OFFSETX_Pos (0UL)      /*!< LCDC_L0_OFFSETX（位0）*/
#define LCDC_LCDC_LAYER0_OFFSETX_REG_LCDC_L0_OFFSETX_Msk (0xffffUL) /*!< LCDC_L0_OFFSETX（位域掩码：0xffff）*/
/* =================================================  LCDC_LAYER0_RESXY_REG  ================================================= */
#define LCDC_LCDC_LAYER0_RESXY_REG_LCDC_L0_RES_X_Pos (16UL)         /*!< LCDC_L0_RES_X（位16）*/
#define LCDC_LCDC_LAYER0_RESXY_REG_LCDC_L0_RES_X_Msk (0xffff0000UL) /*!< LCDC_L0_RES_X（位字段掩码：0xffff）*/
#define LCDC_LCDC_LAYER0_RESXY_REG_LCDC_L0_RES_Y_Pos (0UL)          /*!< LCDC_L0_RES_Y（位0）*/
#define LCDC_LCDC_LAYER0_RESXY_REG_LCDC_L0_RES_Y_Msk (0xffffUL)     /*!< LCDC_L0_RES_Y（位字段掩码：0xffff）*/
/* ================================================  LCDC_LAYER0_SIZEXY_REG  ================================================= */
#define LCDC_LCDC_LAYER0_SIZEXY_REG_LCDC_L0_SIZE_X_Pos (16UL)       /*!< LCDC_L0_SIZE_X（位16）*/
#define LCDC_LCDC_LAYER0_SIZEXY_REG_LCDC_L0_SIZE_X_Msk (0xffff0000UL) /*!< LCDC_L0_SIZE_X（位域掩码：0xffff）*/
#define LCDC_LCDC_LAYER0_SIZEXY_REG_LCDC_L0_SIZE_Y_Pos (0UL)        /*!< LCDC_L0_SIZE_Y（位0）*/
#define LCDC_LCDC_LAYER0_SIZEXY_REG_LCDC_L0_SIZE_Y_Msk (0xffffUL)   /*!< LCDC_L0_SIZE_Y（位域掩码：0xffff）*/
/* ================================================  LCDC_LAYER0_STARTXY_REG  ================================================ */
#define LCDC_LCDC_LAYER0_STARTXY_REG_LCDC_L0_START_X_Pos (16UL)     /*!< LCDC_L0_START_X（位16）*/
#define LCDC_LCDC_LAYER0_STARTXY_REG_LCDC_L0_START_X_Msk (0xffff0000UL) /*!< LCDC_L0_START_X（位域掩码：0xffff）*/
#define LCDC_LCDC_LAYER0_STARTXY_REG_LCDC_L0_START_Y_Pos (0UL)      /*!< LCDC_L0_START_Y（位0）*/
#define LCDC_LCDC_LAYER0_STARTXY_REG_LCDC_L0_START_Y_Msk (0xffffUL) /*!< LCDC_L0_START_Y（位字段掩码：0xffff）*/
/* ================================================  LCDC_LAYER0_STRIDE_REG  ================================================= */
#define LCDC_LCDC_LAYER0_STRIDE_REG_LCDC_L0_FIFO_THR_Pos (19UL)     /*!< LCDC_L0_FIFO_THR（第19位）*/
#define LCDC_LCDC_LAYER0_STRIDE_REG_LCDC_L0_FIFO_THR_Msk (0x180000UL) /*!< LCDC_L0_FIFO_THR（位域掩码：0x03）*/
#define LCDC_LCDC_LAYER0_STRIDE_REG_LCDC_L0_BURST_LEN_Pos (16UL)    /*!< LCDC_L0_BURST_LEN（第16位）*/
#define LCDC_LCDC_LAYER0_STRIDE_REG_LCDC_L0_BURST_LEN_Msk (0x70000UL) /*!< LCDC_L0_BURST_LEN（位字段掩码：0x07）*/
#define LCDC_LCDC_LAYER0_STRIDE_REG_LCDC_L0_STRIDE_Pos (0UL)        /*!< LCDC_L0_STRIDE（位0）*/
#define LCDC_LCDC_LAYER0_STRIDE_REG_LCDC_L0_STRIDE_Msk (0xffffUL)   /*!< LCDC_L0_STRIDE（位字段掩码：0xffff）*/
/* =====================================================  LCDC_MODE_REG  ===================================================== */
#define LCDC_LCDC_MODE_REG_LCDC_MODE_EN_Pos (31UL)                  /*!< LCDC_MODE_EN（第31位）*/
#define LCDC_LCDC_MODE_REG_LCDC_MODE_EN_Msk (0x80000000UL)          /*!< LCDC_MODE_EN（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_VSYNC_POL_Pos (28UL)                /*!< LCDC_VSYNC_POL（位28）*/
#define LCDC_LCDC_MODE_REG_LCDC_VSYNC_POL_Msk (0x10000000UL)        /*!< LCDC_VSYNC_POL（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_HSYNC_POL_Pos (27UL)                /*!< LCDC_HYNC_POL（第27位）*/
#define LCDC_LCDC_MODE_REG_LCDC_HSYNC_POL_Msk (0x8000000UL)         /*!< LCDC_HYNC_POL（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_DE_POL_Pos (26UL)                   /*!< LCDC_DE_POL（位26）*/
#define LCDC_LCDC_MODE_REG_LCDC_DE_POL_Msk (0x4000000UL)            /*!< LCDC_DE_POL（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_VSYNC_SCPL_Pos (23UL)               /*!< LCDC_VSYNC_SCPL（第23位）*/
#define LCDC_LCDC_MODE_REG_LCDC_VSYNC_SCPL_Msk (0x800000UL)         /*!< LCDC_VSYNC_SCPL（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_PIXCLKOUT_POL_Pos (22UL)            /*!< LCDC_PIXCLKOUT_POL（第22位）*/
#define LCDC_LCDC_MODE_REG_LCDC_PIXCLKOUT_POL_Msk (0x400000UL)      /*!< LCDC_PIXCLKOUT_POL（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_FORCE_BLANK_Pos (19UL)              /*!< LCDC_FORCE_BBLANK（位19）*/
#define LCDC_LCDC_MODE_REG_LCDC_FORCE_BLANK_Msk (0x80000UL)         /*!< LCDC_FORCE_BLANK（位域掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_SFRAME_UPD_Pos (17UL)               /*!< LCDC_SFRAME_UPD（位17）*/
#define LCDC_LCDC_MODE_REG_LCDC_SFRAME_UPD_Msk (0x20000UL)          /*!< LCDC_SFRAME_UPD（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_PIXCLKOUT_SEL_Pos (11UL)            /*!< LCDC_PIXCLKOUT_SEL（位11）*/
#define LCDC_LCDC_MODE_REG_LCDC_PIXCLKOUT_SEL_Msk (0x800UL)         /*!< LCDC_PIXCLKOUT_SEL（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_OUT_MODE_Pos (5UL)                  /*!< LCDC_OUT_MODE（位5）*/
#define LCDC_LCDC_MODE_REG_LCDC_OUT_MODE_Msk (0x1e0UL)              /*!< LCDC_OUT_MODE（位字段掩码：0x0f）*/
#define LCDC_LCDC_MODE_REG_LCDC_MIPI_OFF_Pos (4UL)                  /*!< LCDC_MIPI_OFF（位4）*/
#define LCDC_LCDC_MODE_REG_LCDC_MIPI_OFF_Msk (0x10UL)               /*!< LCDC_MIPI_OFF（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_FORM_OFF_Pos (3UL)                  /*!< LCDC_FORM_OFF（位3）*/
#define LCDC_LCDC_MODE_REG_LCDC_FORM_OFF_Msk (0x8UL)                /*!< LCDC_FORM_OFF（位字段掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_DSCAN_Pos (1UL)                     /*!< LCDC_DSCAN（位1）*/
#define LCDC_LCDC_MODE_REG_LCDC_DSCAN_Msk (0x2UL)                   /*!< LCDC_DSCAN（位域掩码：0x01）*/
#define LCDC_LCDC_MODE_REG_LCDC_TMODE_Pos (0UL)                     /*!< LCDC_TMODE（位0）*/
#define LCDC_LCDC_MODE_REG_LCDC_TMODE_Msk (0x1UL)                   /*!< LCDC_TMODE（位字段掩码：0x01）*/
/* ====================================================  LCDC_RESXY_REG  ===================================================== */
#define LCDC_LCDC_RESXY_REG_LCDC_RES_X_Pos (16UL)                   /*!< LCDC_RES_X（位16）*/
#define LCDC_LCDC_RESXY_REG_LCDC_RES_X_Msk (0xffff0000UL)           /*!< LCDC_RES_X（位域掩码：0xffff）*/
#define LCDC_LCDC_RESXY_REG_LCDC_RES_Y_Pos (0UL)                    /*!< LCDC_RES_Y（位0）*/
#define LCDC_LCDC_RESXY_REG_LCDC_RES_Y_Msk (0xffffUL)               /*!< LCDC_RES_Y（位域掩码：0xffff）*/
/* ====================================================  LCDC_STATUS_REG  ==================================================== */
#define LCDC_LCDC_STATUS_REG_LCDC_JDI_TIM_SW_RST_Pos (15UL)         /*!< LCDC_JDI_TIM_SW_RST（第15位）*/
#define LCDC_LCDC_STATUS_REG_LCDC_JDI_TIM_SW_RST_Msk (0x8000UL)     /*!< LCDC_JDI_TIM_SW_RST（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_FRAME_START_Pos (14UL)            /*!< LCDC_FRAME_START（位14）*/
#define LCDC_LCDC_STATUS_REG_LCDC_FRAME_START_Msk (0x4000UL)        /*!< LCDC_FRAME_START（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_FRAME_END_Pos (13UL)              /*!< LCDC_FRAME_END（第13位）*/
#define LCDC_LCDC_STATUS_REG_LCDC_FRAME_END_Msk (0x2000UL)          /*!< LCDC_FRAME_END（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_CMD_PENDING_Pos (12UL)       /*!< LCDC_DIB_CMD_PENDING（第12位）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_CMD_PENDING_Msk (0x1000UL)   /*!< LCDC_DIB_CMD_PENDING（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_CMD_FIFO_FULL_Pos (11UL)     /*!< LCDC_DIB_CMD_FIFO_FULL（第11位）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_CMD_FIFO_FULL_Msk (0x800UL)  /*!< LCDC_DBIB_CMD_FIFO_FULL（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_CMD_FIFO_EMPTY_N_Pos (10UL)  /*!< LCDC_DIB_CMD_FIFO_EMPTY_N（位10）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_CMD_FIFO_EMPTY_N_Msk (0x400UL) /*!< LCDC_DBIB_CMD_FIFO_EMPTY_N（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_TE_Pos (8UL)                 /*!< LCDC_DIB_TE（位8）*/
#define LCDC_LCDC_STATUS_REG_LCDC_DBIB_TE_Msk (0x100UL)             /*!< LCDC_DBIB_TE（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STICKY_UNDERFLOW_Pos (7UL)        /*!< LCDC_STICKY_UNDERFLOW（第7位）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STICKY_UNDERFLOW_Msk (0x80UL)     /*!< LCDC_STICKY_UNDERFLOW（位域掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_UNDERFLOW_Pos (6UL)               /*!< LCDC_BUNDERFLOW（位6）*/
#define LCDC_LCDC_STATUS_REG_LCDC_UNDERFLOW_Msk (0x40UL)            /*!< LCDC_UNDERFLOW（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_LAST_ROW_Pos (5UL)                /*!< LCDC_LAST_ROW（位5）*/
#define LCDC_LCDC_STATUS_REG_LCDC_LAST_ROW_Msk (0x20UL)             /*!< LCDC_LAST_ROW（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_CSYNC_Pos (4UL)              /*!< LCDC_STAT_CSYNC（位4）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_CSYNC_Msk (0x10UL)           /*!< LCDC_STAT_CSYNC（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_VSYNC_Pos (3UL)              /*!< LCDC_STAT_VSYNC（位3）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_VSYNC_Msk (0x8UL)            /*!< LCDC_STAT_VSYNC（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_HSYNC_Pos (2UL)              /*!< LCDC_STAT_HSYNC（位2）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_HSYNC_Msk (0x4UL)            /*!< LCDC_STAT_HSYNC（位字段掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_FRAMEGEN_BUSY_Pos (1UL)           /*!< LCDC_FRAMEGEN_BUSY（位1）*/
#define LCDC_LCDC_STATUS_REG_LCDC_FRAMEGEN_BUSY_Msk (0x2UL)         /*!< LCDC_FRAMEGEN_BUSY（位域掩码：0x01）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_ACTIVE_Pos (0UL)             /*!< LCDC_STAT_ACTIVE（位0）*/
#define LCDC_LCDC_STATUS_REG_LCDC_STAT_ACTIVE_Msk (0x1UL)           /*!< LCDC_STAT_ACTIVE（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                            LRA                                            ================ */
/* =========================================================================================================================== */

/* ===================================================  LRA_ADC_CTRL1_REG  =================================================== */
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_BUSY_Pos (31UL)               /*!< LRA_ADC_BUSY（第31位）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_BUSY_Msk (0x80000000UL)       /*!< LRA_ADC_BUSY（位字段掩码：0x01）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_OFFSET_Pos (9UL)              /*!< LRA_ADC_OFFSET（位9）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_OFFSET_Msk (0x1fe00UL)        /*!< LRA_ADC_OFFSET（位字段掩码：0xff）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_TEST_PARAM_Pos (8UL)          /*!< LRA_ADC_TEST_PARAM（第8位）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_TEST_PARAM_Msk (0x100UL)      /*!< LRA_ADC_TEST_PARAM（位字段掩码：0x01）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_TEST_IN_SEL_Pos (7UL)         /*!< LRA_ADC_TEST_IN_SEL（第7位）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_TEST_IN_SEL_Msk (0x80UL)      /*!< LRA_ADC_TEST_IN_SEL（位字段掩码：0x01）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_FREQ_Pos (3UL)                /*!< LRA_ADC_REQ（位3）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_FREQ_Msk (0x78UL)             /*!< LRA_ADC_FREQ（位字段掩码：0x0f）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_SIGN_Pos (2UL)                /*!< LRA_ADC_SIGN（位2）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_SIGN_Msk (0x4UL)              /*!< LRA_ADC_SIGN（位域掩码：0x01）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_MUTE_Pos (1UL)                /*!< LRA_ADC_MUTE（位1）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_MUTE_Msk (0x2UL)              /*!< LRA_ADC_MUTE（位字段掩码：0x01）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_START_Pos (0UL)               /*!< LRA_ADC_START（位0）*/
#define LRA_LRA_ADC_CTRL1_REG_LRA_ADC_START_Msk (0x1UL)             /*!< LRA_ADC_START（位字段掩码：0x01）*/
/* ==================================================  LRA_ADC_RESULT_REG  =================================================== */
#define LRA_LRA_ADC_RESULT_REG_MAN_FLT_IN_Pos (16UL)                /*!< MAN_FLT_IN（位16）*/
#define LRA_LRA_ADC_RESULT_REG_MAN_FLT_IN_Msk (0xffff0000UL)        /*!< MAN_FLT_IN（位字段掩码：0xffff）*/
#define LRA_LRA_ADC_RESULT_REG_GP_ADC_VAL_Pos (0UL)                 /*!< GP_ADC_VAL（位0）*/
#define LRA_LRA_ADC_RESULT_REG_GP_ADC_VAL_Msk (0xffffUL)            /*!< GP_ADC_VAL（位域掩码：0xffff）*/
/* ====================================================  LRA_BRD_HS_REG  ===================================================== */
#define LRA_LRA_BRD_HS_REG_TRIM_GAIN_Pos  (11UL)                    /*!< TRIM_GAIN（位11）*/
#define LRA_LRA_BRD_HS_REG_TRIM_GAIN_Msk  (0x7800UL)                /*!< TRIM_GAIN（位域掩码：0x0f）*/
#define LRA_LRA_BRD_HS_REG_HSGND_TRIM_Pos (8UL)                     /*!< HSGND_TRIM（位8）*/
#define LRA_LRA_BRD_HS_REG_HSGND_TRIM_Msk (0x700UL)                 /*!< HSGND_TRIM（位域掩码：0x07）*/
#define LRA_LRA_BRD_HS_REG_SCP_HS_TRIM_Pos (4UL)                    /*!< SCP_HS_TRIM（位4）*/
#define LRA_LRA_BRD_HS_REG_SCP_HS_TRIM_Msk (0xf0UL)                 /*!< SCP_HS_TRIM（位字段掩码：0x0f）*/
#define LRA_LRA_BRD_HS_REG_SCP_HS_EN_Pos  (3UL)                     /*!< SCP_HS_EN（位3）*/
#define LRA_LRA_BRD_HS_REG_SCP_HS_EN_Msk  (0x8UL)                   /*!< SCP_HS_EN（位域掩码：0x01）*/
#define LRA_LRA_BRD_HS_REG_ERC_HS_TRIM_Pos (1UL)                    /*!< ERC_HS_TRIM（位1）*/
#define LRA_LRA_BRD_HS_REG_ERC_HS_TRIM_Msk (0x6UL)                  /*!< ERC_HS_TRIM（位域掩码：0x03）*/
#define LRA_LRA_BRD_HS_REG_ERC_HS_EN_Pos  (0UL)                     /*!< ERC_HS_EN（位0）*/
#define LRA_LRA_BRD_HS_REG_ERC_HS_EN_Msk  (0x1UL)                   /*!< ERC_HS_EN（位域掩码：0x01）*/
/* ====================================================  LRA_BRD_LS_REG  ===================================================== */
#define LRA_LRA_BRD_LS_REG_SCP_LS_TRIM_N_Pos (8UL)                  /*!< SCP_LS_TRIM_N（第8位）*/
#define LRA_LRA_BRD_LS_REG_SCP_LS_TRIM_N_Msk (0xf00UL)              /*!< SCP_LS_TRIM_N（位字段掩码：0x0f）*/
#define LRA_LRA_BRD_LS_REG_SCP_LS_TRIM_P_Pos (4UL)                  /*!< SCP_LS_TRIM_P（位4）*/
#define LRA_LRA_BRD_LS_REG_SCP_LS_TRIM_P_Msk (0xf0UL)               /*!< SCP_LS_TRIM_P（位字段掩码：0x0f）*/
#define LRA_LRA_BRD_LS_REG_SCP_LS_EN_Pos  (3UL)                     /*!< SCP_LS_EN（位3）*/
#define LRA_LRA_BRD_LS_REG_SCP_LS_EN_Msk  (0x8UL)                   /*!< SCP_LS_EN（位字段掩码：0x01）*/
#define LRA_LRA_BRD_LS_REG_ERC_LS_TRIM_Pos (1UL)                    /*!< ERC_LS_TRIM（位1）*/
#define LRA_LRA_BRD_LS_REG_ERC_LS_TRIM_Msk (0x6UL)                  /*!< ERC_LS_TRIM（位域掩码：0x03）*/
#define LRA_LRA_BRD_LS_REG_ERC_LS_EN_Pos  (0UL)                     /*!< ERC_LS_EN（位0）*/
#define LRA_LRA_BRD_LS_REG_ERC_LS_EN_Msk  (0x1UL)                   /*!< ERC_LS_EN（位域掩码：0x01）*/
/* ===================================================  LRA_BRD_STAT_REG  ==================================================== */
#define LRA_LRA_BRD_STAT_REG_SCP_HS_OUT_Pos (13UL)                  /*!< SCP_HS_OUT（第13位）*/
#define LRA_LRA_BRD_STAT_REG_SCP_HS_OUT_Msk (0x2000UL)              /*!< SCP_HS_OUT（位字段掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_SCP_LS_COMP_OUT_N_Pos (12UL)           /*!< SCP_LS_COMP_OUT_N（第12位）*/
#define LRA_LRA_BRD_STAT_REG_SCP_LS_COMP_OUT_N_Msk (0x1000UL)       /*!< SCP_LS_COMP_OUT_N（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_SCP_LS_COMP_OUT_P_Pos (11UL)           /*!< SCP_LS_COMP_OUT_P（位11）*/
#define LRA_LRA_BRD_STAT_REG_SCP_LS_COMP_OUT_P_Msk (0x800UL)        /*!< SCP_LS_COMP_OUT_P（位字段掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_SC_EVENT_LS_Pos (10UL)                 /*!< SC_EVENT_LS（位10）*/
#define LRA_LRA_BRD_STAT_REG_SC_EVENT_LS_Msk (0x400UL)              /*!< SC_EVENT_LS（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_SC_EVENT_HS_Pos (9UL)                  /*!< SC_EVENT_HS（第9位）*/
#define LRA_LRA_BRD_STAT_REG_SC_EVENT_HS_Msk (0x200UL)              /*!< SC_EVENT_HS（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_LOOP_STAT_Pos (8UL)                    /*!< LOOP_STAT（位8）*/
#define LRA_LRA_BRD_STAT_REG_LOOP_STAT_Msk (0x100UL)                /*!< LOOP_STAT（位字段掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_LSN_ON_Pos   (7UL)                     /*!< LSN_ON（位7）*/
#define LRA_LRA_BRD_STAT_REG_LSN_ON_Msk   (0x80UL)                  /*!< LSN_ON（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_LSP_ON_Pos   (6UL)                     /*!< LSP_ON（位6）*/
#define LRA_LRA_BRD_STAT_REG_LSP_ON_Msk   (0x40UL)                  /*!< LSP_ON（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_HSN_ON_Pos   (5UL)                     /*!< HSN_ON（位5）*/
#define LRA_LRA_BRD_STAT_REG_HSN_ON_Msk   (0x20UL)                  /*!< HSN_ON（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_HSP_ON_Pos   (4UL)                     /*!< HSP_ON（第4位）*/
#define LRA_LRA_BRD_STAT_REG_HSP_ON_Msk   (0x10UL)                  /*!< HSP_ON（位域掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_LSN_STAT_Pos (3UL)                     /*!< LSN_STAT（位3）*/
#define LRA_LRA_BRD_STAT_REG_LSN_STAT_Msk (0x8UL)                   /*!< LSN_STAT（位字段掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_LSP_STAT_Pos (2UL)                     /*!< LSP_STAT（位2）*/
#define LRA_LRA_BRD_STAT_REG_LSP_STAT_Msk (0x4UL)                   /*!< LSP_STAT（位字段掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_HSN_STAT_Pos (1UL)                     /*!< HSN_STAT（位1）*/
#define LRA_LRA_BRD_STAT_REG_HSN_STAT_Msk (0x2UL)                   /*!< HSN_STAT（位字段掩码：0x01）*/
#define LRA_LRA_BRD_STAT_REG_HSP_STAT_Pos (0UL)                     /*!< HSP_STAT（位0）*/
#define LRA_LRA_BRD_STAT_REG_HSP_STAT_Msk (0x1UL)                   /*!< HSP_STAT（位字段掩码：0x01）*/
/* =====================================================  LRA_CTRL1_REG  ===================================================== */
#define LRA_LRA_CTRL1_REG_SMP_IDX_Pos     (24UL)                    /*!< SMP_IDX（位24）*/
#define LRA_LRA_CTRL1_REG_SMP_IDX_Msk     (0xf000000UL)             /*!< SMP_IDX（位域掩码：0x0f）*/
#define LRA_LRA_CTRL1_REG_IRQ_SCP_EVENT_EN_Pos (18UL)               /*!< IRQ_SCP_EVENT_EN（位18）*/
#define LRA_LRA_CTRL1_REG_IRQ_SCP_EVENT_EN_Msk (0x40000UL)          /*!< IRQ_SCP_EVENT_EN（位域掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_IRQ_ADC_EN_Pos  (17UL)                    /*!< IRQ_ADC_EN（位17）*/
#define LRA_LRA_CTRL1_REG_IRQ_ADC_EN_Msk  (0x20000UL)               /*!< IRQ_ADC_EN（位域掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_IRQ_CTRL_EN_Pos (16UL)                    /*!< IRQ_CTRL_EN（位16）*/
#define LRA_LRA_CTRL1_REG_IRQ_CTRL_EN_Msk (0x10000UL)               /*!< IRQ_CTRL_EN（位域掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_IRQ_IDX_Pos     (12UL)                    /*!< IRQ_IDX（第12位）*/
#define LRA_LRA_CTRL1_REG_IRQ_IDX_Msk     (0xf000UL)                /*!< IRQ_IDX（位域掩码：0x0f）*/
#define LRA_LRA_CTRL1_REG_IRQ_DIV_Pos     (8UL)                     /*!< IRQ_DIV（位8）*/
#define LRA_LRA_CTRL1_REG_IRQ_DIV_Msk     (0xf00UL)                 /*!< IRQ_DIV（位域掩码：0x0f）*/
#define LRA_LRA_CTRL1_REG_SMP_SEL_Pos     (6UL)                     /*!< SMP_SEL（位6）*/
#define LRA_LRA_CTRL1_REG_SMP_SEL_Msk     (0xc0UL)                  /*!< SMP_SEL（位字段掩码：0x03）*/
#define LRA_LRA_CTRL1_REG_PULLDOWN_EN_Pos (5UL)                     /*!< PULLDOWN_EN（位5）*/
#define LRA_LRA_CTRL1_REG_PULLDOWN_EN_Msk (0x20UL)                  /*!< PULLDOWN_EN（位字段掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_LOOP_EN_Pos     (4UL)                     /*!< LOOP_EN（位4）*/
#define LRA_LRA_CTRL1_REG_LOOP_EN_Msk     (0x10UL)                  /*!< LOOP_EN（位域掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_LDO_EN_Pos      (3UL)                     /*!< LDO_EN（位3）*/
#define LRA_LRA_CTRL1_REG_LDO_EN_Msk      (0x8UL)                   /*!< LDO_EN（位域掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_ADC_EN_Pos      (2UL)                     /*!< ADC_EN（位2）*/
#define LRA_LRA_CTRL1_REG_ADC_EN_Msk      (0x4UL)                   /*!< ADC_EN（位域掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_HBRIDGE_EN_Pos  (1UL)                     /*!< HBRIDGE_EN（位1）*/
#define LRA_LRA_CTRL1_REG_HBRIDGE_EN_Msk  (0x2UL)                   /*!< HBRIDGE_EN（位字段掩码：0x01）*/
#define LRA_LRA_CTRL1_REG_LRA_EN_Pos      (0UL)                     /*!< LRA_EN（位0）*/
#define LRA_LRA_CTRL1_REG_LRA_EN_Msk      (0x1UL)                   /*!< LRA_EN（位域掩码：0x01）*/
/* =====================================================  LRA_CTRL2_REG  ===================================================== */
#define LRA_LRA_CTRL2_REG_HALF_PERIOD_Pos (16UL)                    /*!< 半周期（位16）*/
#define LRA_LRA_CTRL2_REG_HALF_PERIOD_Msk (0xffff0000UL)            /*!< HALF_PERIOD（位域掩码：0xffff）*/
#define LRA_LRA_CTRL2_REG_AUTO_MODE_Pos   (5UL)                     /*!< AUTO_MODE（位5）*/
#define LRA_LRA_CTRL2_REG_AUTO_MODE_Msk   (0x20UL)                  /*!< AUTO_MODE（位域掩码：0x01）*/
#define LRA_LRA_CTRL2_REG_SMP_MODE_Pos    (4UL)                     /*!< SMP_MODE（位4）*/
#define LRA_LRA_CTRL2_REG_SMP_MODE_Msk    (0x10UL)                  /*!< SMP_MODE（位字段掩码：0x01）*/
#define LRA_LRA_CTRL2_REG_POLARITY_Pos    (3UL)                     /*!< 极性（位3）*/
#define LRA_LRA_CTRL2_REG_POLARITY_Msk    (0x8UL)                   /*!< POLARITY（位域掩码：0x01）*/
#define LRA_LRA_CTRL2_REG_FLT_IN_SEL_Pos  (2UL)                     /*!< FLT_IN_SEL（位2）*/
#define LRA_LRA_CTRL2_REG_FLT_IN_SEL_Msk  (0x4UL)                   /*!< FLT_IN_SEL（位字段掩码：0x01）*/
#define LRA_LRA_CTRL2_REG_PWM_MODE_Pos    (0UL)                     /*!< PWM_MODE（位0）*/
#define LRA_LRA_CTRL2_REG_PWM_MODE_Msk    (0x3UL)                   /*!< PWM_MODE（位字段掩码：0x03）*/
/* =====================================================  LRA_CTRL3_REG  ===================================================== */
#define LRA_LRA_CTRL3_REG_VREF_Pos        (16UL)                    /*!< VREF（位16）*/
#define LRA_LRA_CTRL3_REG_VREF_Msk        (0xffff0000UL)            /*!< VREF（位域掩码：0xffff）*/
#define LRA_LRA_CTRL3_REG_DREF_Pos        (0UL)                     /*!< DREF（位0）*/
#define LRA_LRA_CTRL3_REG_DREF_Msk        (0xffffUL)                /*!< DREF（位域掩码：0xffff）*/
/* ======================================================  LRA_DFT_REG  ====================================================== */
#define LRA_LRA_DFT_REG_SPARE_Pos         (29UL)                    /*!< 备用（第29位）*/
#define LRA_LRA_DFT_REG_SPARE_Msk         (0xe0000000UL)            /*!< 备用（位字段掩码：0x07）*/
#define LRA_LRA_DFT_REG_SWM_SEL_Pos       (28UL)                    /*!< SWM_SEL（第28位）*/
#define LRA_LRA_DFT_REG_SWM_SEL_Msk       (0x10000000UL)            /*!< SWM_SEL（位字段掩码：0x01）*/
#define LRA_LRA_DFT_REG_SWM_MAN_Pos       (27UL)                    /*!< SWM_MAN（第27位）*/
#define LRA_LRA_DFT_REG_SWM_MAN_Msk       (0x8000000UL)             /*!< SWM_MAN（位域掩码：0x01）*/
#define LRA_LRA_DFT_REG_PWM_SEL_Pos       (26UL)                    /*!< PWM_SEL（位26）*/
#define LRA_LRA_DFT_REG_PWM_SEL_Msk       (0x4000000UL)             /*!< PWM_SEL（位字段掩码：0x01）*/
#define LRA_LRA_DFT_REG_PWM_MAN_Pos       (25UL)                    /*!< PWM_MAN（位25）*/
#define LRA_LRA_DFT_REG_PWM_MAN_Msk       (0x2000000UL)             /*!< PWM_MAN（位域掩码：0x01）*/
#define LRA_LRA_DFT_REG_TIMER_TRIM_Pos    (23UL)                    /*!< TIMER_TRIM（位23）*/
#define LRA_LRA_DFT_REG_TIMER_TRIM_Msk    (0x1800000UL)             /*!< TIMER_TRIM（位字段掩码：0x03）*/
#define LRA_LRA_DFT_REG_TIMER_SCALE_TRIM_Pos (21UL)                 /*!< TIMER_SCALE_TRIM（位21）*/
#define LRA_LRA_DFT_REG_TIMER_SCALE_TRIM_Msk (0x600000UL)           /*!< TIMER_SCALE_TRIM（位字段掩码：0x03）*/
#define LRA_LRA_DFT_REG_DFT_SEL_Pos       (20UL)                    /*!< DFT_SEL（位20）*/
#define LRA_LRA_DFT_REG_DFT_SEL_Msk       (0x100000UL)              /*!< DFT_SEL（位字段掩码：0x01）*/
#define LRA_LRA_DFT_REG_DFT_FORCE_HSPN_Pos (19UL)                   /*!< DFT_FORCE_HSN（位19）*/
#define LRA_LRA_DFT_REG_DFT_FORCE_HSPN_Msk (0x80000UL)              /*!< DFT_FORCE_HSN（位字段掩码：0x01）*/
#define LRA_LRA_DFT_REG_DFT_EN_TIMER_Pos  (18UL)                    /*!< DFT_EN_TIMER（位18）*/
#define LRA_LRA_DFT_REG_DFT_EN_TIMER_Msk  (0x40000UL)               /*!< DFT_EN_TIMER（位字段掩码：0x01）*/
#define LRA_LRA_DFT_REG_DFT_STALL_Pos     (16UL)                    /*!< DFT_STALL（位16）*/
#define LRA_LRA_DFT_REG_DFT_STALL_Msk     (0x30000UL)               /*!< DFT_STALL（位字段掩码：0x03）*/
#define LRA_LRA_DFT_REG_DFT_CTRL_Pos      (0UL)                     /*!< DFT_CTRL（位0）*/
#define LRA_LRA_DFT_REG_DFT_CTRL_Msk      (0xffffUL)                /*!< DFT_CTRL（位字段掩码：0xffff）*/
/* ===================================================  LRA_FLT_COEF1_REG  =================================================== */
#define LRA_LRA_FLT_COEF1_REG_FLT_COEF_01_Pos (16UL)                /*!< FLT_COEF_01（位16）*/
#define LRA_LRA_FLT_COEF1_REG_FLT_COEF_01_Msk (0xffff0000UL)        /*!< FLT_COEF_01（位字段掩码：0xffff）*/
#define LRA_LRA_FLT_COEF1_REG_FLT_COEF_00_Pos (0UL)                 /*!< FLT_COEF_00（位0）*/
#define LRA_LRA_FLT_COEF1_REG_FLT_COEF_00_Msk (0xffffUL)            /*!< FLT_COEF_00（位字段掩码：0xffff）*/
/* ===================================================  LRA_FLT_COEF2_REG  =================================================== */
#define LRA_LRA_FLT_COEF2_REG_FLT_COEF_10_Pos (16UL)                /*!< FLT_COEF_10（位16）*/
#define LRA_LRA_FLT_COEF2_REG_FLT_COEF_10_Msk (0xffff0000UL)        /*!< FLT_COEF_10（位域掩码：0xffff）*/
#define LRA_LRA_FLT_COEF2_REG_FLT_COEF_02_Pos (0UL)                 /*!< FLT_COEF_02（位0）*/
#define LRA_LRA_FLT_COEF2_REG_FLT_COEF_02_Msk (0xffffUL)            /*!< FLT_COEF_02（位字段掩码：0xffff）*/
/* ===================================================  LRA_FLT_COEF3_REG  =================================================== */
#define LRA_LRA_FLT_COEF3_REG_FLT_COEF_12_Pos (16UL)                /*!< FLT_COEF_12（位16）*/
#define LRA_LRA_FLT_COEF3_REG_FLT_COEF_12_Msk (0xffff0000UL)        /*!< FLT_COEF_12（位字段掩码：0xffff）*/
#define LRA_LRA_FLT_COEF3_REG_FLT_COEF_11_Pos (0UL)                 /*!< FLT_COEF_11（位0）*/
#define LRA_LRA_FLT_COEF3_REG_FLT_COEF_11_Msk (0xffffUL)            /*!< FLT_COEF_11（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP1_REG  ==================================================== */
#define LRA_LRA_FLT_SMP1_REG_LRA_SMP_2_Pos (16UL)                   /*!< LRA_SMP_2（位16）*/
#define LRA_LRA_FLT_SMP1_REG_LRA_SMP_2_Msk (0xffff0000UL)           /*!< LRA_SMP_2（位域掩码：0xffff）*/
#define LRA_LRA_FLT_SMP1_REG_LRA_SMP_1_Pos (0UL)                    /*!< LRA_SMP_1（位0）*/
#define LRA_LRA_FLT_SMP1_REG_LRA_SMP_1_Msk (0xffffUL)               /*!< LRA_SMP_1（位字段掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP2_REG  ==================================================== */
#define LRA_LRA_FLT_SMP2_REG_LRA_SMP_4_Pos (16UL)                   /*!< LRA_SMP_4（位16）*/
#define LRA_LRA_FLT_SMP2_REG_LRA_SMP_4_Msk (0xffff0000UL)           /*!< LRA_SMP_4（位域掩码：0xffff）*/
#define LRA_LRA_FLT_SMP2_REG_LRA_SMP_3_Pos (0UL)                    /*!< LRA_SMP_3（位0）*/
#define LRA_LRA_FLT_SMP2_REG_LRA_SMP_3_Msk (0xffffUL)               /*!< LRA_SMP_3（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP3_REG  ==================================================== */
#define LRA_LRA_FLT_SMP3_REG_LRA_SMP_6_Pos (16UL)                   /*!< LRA_SMP_6（位16）*/
#define LRA_LRA_FLT_SMP3_REG_LRA_SMP_6_Msk (0xffff0000UL)           /*!< LRA_SMP_6（位场掩码：0xffff）*/
#define LRA_LRA_FLT_SMP3_REG_LRA_SMP_5_Pos (0UL)                    /*!< LRA_SMP_5（位0）*/
#define LRA_LRA_FLT_SMP3_REG_LRA_SMP_5_Msk (0xffffUL)               /*!< LRA_SMP_5（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP4_REG  ==================================================== */
#define LRA_LRA_FLT_SMP4_REG_LRA_SMP_8_Pos (16UL)                   /*!< LRA_SMP_8（位16）*/
#define LRA_LRA_FLT_SMP4_REG_LRA_SMP_8_Msk (0xffff0000UL)           /*!< LRA_SMP_8（位场掩码：0xffff）*/
#define LRA_LRA_FLT_SMP4_REG_LRA_SMP_7_Pos (0UL)                    /*!< LRA_SMP_7（位0）*/
#define LRA_LRA_FLT_SMP4_REG_LRA_SMP_7_Msk (0xffffUL)               /*!< LRA_SMP_7（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP5_REG  ==================================================== */
#define LRA_LRA_FLT_SMP5_REG_LRA_SMP_10_Pos (16UL)                  /*!< LRA_SMP_10（位16）*/
#define LRA_LRA_FLT_SMP5_REG_LRA_SMP_10_Msk (0xffff0000UL)          /*!< LRA_SMP_10（位域掩码：0xffff）*/
#define LRA_LRA_FLT_SMP5_REG_LRA_SMP_9_Pos (0UL)                    /*!< LRA_SMP_9（位0）*/
#define LRA_LRA_FLT_SMP5_REG_LRA_SMP_9_Msk (0xffffUL)               /*!< LRA_SMP_9（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP6_REG  ==================================================== */
#define LRA_LRA_FLT_SMP6_REG_LRA_SMP_12_Pos (16UL)                  /*!< LRA_SMP_12（位16）*/
#define LRA_LRA_FLT_SMP6_REG_LRA_SMP_12_Msk (0xffff0000UL)          /*!< LRA_SMP_12（位域掩码：0xffff）*/
#define LRA_LRA_FLT_SMP6_REG_LRA_SMP_11_Pos (0UL)                   /*!< LRA_SMP_11（位0）*/
#define LRA_LRA_FLT_SMP6_REG_LRA_SMP_11_Msk (0xffffUL)              /*!< LRA_SMP_11（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP7_REG  ==================================================== */
#define LRA_LRA_FLT_SMP7_REG_LRA_SMP_14_Pos (16UL)                  /*!< LRA_SMP_14（位16）*/
#define LRA_LRA_FLT_SMP7_REG_LRA_SMP_14_Msk (0xffff0000UL)          /*!< LRA_SMP_14（位域掩码：0xffff）*/
#define LRA_LRA_FLT_SMP7_REG_LRA_SMP_13_Pos (0UL)                   /*!< LRA_SMP_13（位0）*/
#define LRA_LRA_FLT_SMP7_REG_LRA_SMP_13_Msk (0xffffUL)              /*!< LRA_SMP_13（位域掩码：0xffff）*/
/* ===================================================  LRA_FLT_SMP8_REG  ==================================================== */
#define LRA_LRA_FLT_SMP8_REG_LRA_SMP_16_Pos (16UL)                  /*!< LRA_SMP_16（位16）*/
#define LRA_LRA_FLT_SMP8_REG_LRA_SMP_16_Msk (0xffff0000UL)          /*!< LRA_SMP_16（位域掩码：0xffff）*/
#define LRA_LRA_FLT_SMP8_REG_LRA_SMP_15_Pos (0UL)                   /*!< LRA_SMP_15（位0）*/
#define LRA_LRA_FLT_SMP8_REG_LRA_SMP_15_Msk (0xffffUL)              /*!< LRA_SMP_15（位域掩码：0xffff）*/
/* ======================================================  LRA_LDO_REG  ====================================================== */
#define LRA_LRA_LDO_REG_LDO_OK_Pos        (31UL)                    /*!< LDO_OK（位31）*/
#define LRA_LRA_LDO_REG_LDO_OK_Msk        (0x80000000UL)            /*!< LDO_OK（位字段掩码：0x01）*/
#define LRA_LRA_LDO_REG_LDO_TST_Pos       (1UL)                     /*!< LDO_TST（位1）*/
#define LRA_LRA_LDO_REG_LDO_TST_Msk       (0x2UL)                   /*!< LDO_TST（位域掩码：0x01）*/
#define LRA_LRA_LDO_REG_LDO_VREF_HOLD_Pos (0UL)                     /*!< LDO_VREF_HOLD（位0）*/
#define LRA_LRA_LDO_REG_LDO_VREF_HOLD_Msk (0x1UL)                   /*!< LDO_VREF_HOLD（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                          MEMCTRL                                          ================ */
/* =========================================================================================================================== */

/* ====================================================  BUSY_RESET_REG  ===================================================== */
#define MEMCTRL_BUSY_RESET_REG_BUSY_SPARE_Pos (30UL)                /*!< BUSY_SPARE（位30）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SPARE_Msk (0xc0000000UL)        /*!< BUSY_SPARE（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_MOTOR_Pos (28UL)                /*!< BUSY_MOTOR（位28）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_MOTOR_Msk (0x30000000UL)        /*!< BUSY_MOTOR（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_TIMER2_Pos (26UL)               /*!< BUSY_TIMER2（位26）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_TIMER2_Msk (0xc000000UL)        /*!< BUSY_TIMER2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_TIMER_Pos (24UL)                /*!< BUSY_TIMER（位24）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_TIMER_Msk (0x3000000UL)         /*!< BUSY_TIMER（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_UART3_Pos (22UL)                /*!< BUSY_UART3（位22）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_UART3_Msk (0xc00000UL)          /*!< BUSY_UART3（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_GPADC_Pos (20UL)                /*!< BUSY_GPADC（位20）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_GPADC_Msk (0x300000UL)          /*!< BUSY_GPADC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_PDM_Pos (18UL)                  /*!< BUSY_PDM（位18）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_PDM_Msk (0xc0000UL)             /*!< BUSY_PDM（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SRC_Pos (16UL)                  /*!< BUSY_SRC（位16）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SRC_Msk (0x30000UL)             /*!< BUSY_SRC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_PCM_Pos (14UL)                  /*!< BUSY_PCM（位14）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_PCM_Msk (0xc000UL)              /*!< BUSY_PCM（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SDADC_Pos (12UL)                /*!< BUSY_SDADC（位12）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SDADC_Msk (0x3000UL)            /*!< BUSY_SDADC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_I2C2_Pos (10UL)                 /*!< BUSY_I2C2（位10）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_I2C2_Msk (0xc00UL)              /*!< BUSY_I2C2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_I2C_Pos (8UL)                   /*!< BUSY_I2C（位8）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_I2C_Msk (0x300UL)               /*!< BUSY_I2C（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SPI2_Pos (6UL)                  /*!< BUSY_SPI2（位6）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SPI2_Msk (0xc0UL)               /*!< BUSY_SPI2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SPI_Pos (4UL)                   /*!< BUSY_SPI（位4）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_SPI_Msk (0x30UL)                /*!< BUSY_SPI（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_UART2_Pos (2UL)                 /*!< BUSY_UART2（位2）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_UART2_Msk (0xcUL)               /*!< BUSY_UART2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_UART_Pos (0UL)                  /*!< BUSY_UART（位0）*/
#define MEMCTRL_BUSY_RESET_REG_BUSY_UART_Msk (0x3UL)                /*!< BUSY_UART（位字段掩码：0x03）*/
/* =====================================================  BUSY_SET_REG  ====================================================== */
#define MEMCTRL_BUSY_SET_REG_BUSY_SPARE_Pos (30UL)                  /*!< BUSY_SPARE（位30）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SPARE_Msk (0xc0000000UL)          /*!< BUSY_SPARE（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_MOTOR_Pos (28UL)                  /*!< BUSY_MOTOR（位28）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_MOTOR_Msk (0x30000000UL)          /*!< BUSY_MOTOR（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_TIMER2_Pos (26UL)                 /*!< BUSY_TIMER2（位26）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_TIMER2_Msk (0xc000000UL)          /*!< BUSY_TIMER2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_TIMER_Pos (24UL)                  /*!< BUSY_TIMER（位24）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_TIMER_Msk (0x3000000UL)           /*!< BUSY_TIMER（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_UART3_Pos (22UL)                  /*!< BUSY_UART3（位22）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_UART3_Msk (0xc00000UL)            /*!< BUSY_UART3（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_GPADC_Pos (20UL)                  /*!< BUSY_GPADC（位20）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_GPADC_Msk (0x300000UL)            /*!< BUSY_GPADC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_PDM_Pos (18UL)                    /*!< BUSY_PDM（位18）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_PDM_Msk (0xc0000UL)               /*!< BUSY_PDM（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SRC_Pos (16UL)                    /*!< BUSY_SRC（位16）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SRC_Msk (0x30000UL)               /*!< BUSY_SRC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_PCM_Pos (14UL)                    /*!< BUSY_PCM（位14）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_PCM_Msk (0xc000UL)                /*!< BUSY_PCM（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SDADC_Pos (12UL)                  /*!< BUSY_SDADC（位12）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SDADC_Msk (0x3000UL)              /*!< BUSY_SDADC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_I2C2_Pos (10UL)                   /*!< BUSY_I2C2（位10）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_I2C2_Msk (0xc00UL)                /*!< BUSY_I2C2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_I2C_Pos (8UL)                     /*!< BUSY_I2C（位8）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_I2C_Msk (0x300UL)                 /*!< BUSY_I2C（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SPI2_Pos (6UL)                    /*!< BUSY_SPI2（位6）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SPI2_Msk (0xc0UL)                 /*!< BUSY_SPI2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SPI_Pos (4UL)                     /*!< BUSY_SPI（位4）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_SPI_Msk (0x30UL)                  /*!< BUSY_SPI（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_UART2_Pos (2UL)                   /*!< BUSY_UART2（位2）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_UART2_Msk (0xcUL)                 /*!< BUSY_UART2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_UART_Pos (0UL)                    /*!< BUSY_UART（位0）*/
#define MEMCTRL_BUSY_SET_REG_BUSY_UART_Msk (0x3UL)                  /*!< BUSY_UART（位字段掩码：0x03）*/
/* =====================================================  BUSY_STAT_REG  ===================================================== */
#define MEMCTRL_BUSY_STAT_REG_BUSY_SPARE_Pos (30UL)                 /*!< BUSY_SPARE（位30）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SPARE_Msk (0xc0000000UL)         /*!< BUSY_SPARE（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_MOTOR_Pos (28UL)                 /*!< BUSY_MOTOR（位28）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_MOTOR_Msk (0x30000000UL)         /*!< BUSY_MOTOR（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_TIMER2_Pos (26UL)                /*!< BUSY_TIMER2（位26）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_TIMER2_Msk (0xc000000UL)         /*!< BUSY_TIMER2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_TIMER_Pos (24UL)                 /*!< BUSY_TIMER（位24）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_TIMER_Msk (0x3000000UL)          /*!< BUSY_TIMER（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_UART3_Pos (22UL)                 /*!< BUSY_UART3（位22）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_UART3_Msk (0xc00000UL)           /*!< BUSY_UART3（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_GPADC_Pos (20UL)                 /*!< BUSY_GPADC（位20）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_GPADC_Msk (0x300000UL)           /*!< BUSY_GPADC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_PDM_Pos (18UL)                   /*!< BUSY_PDM（位18）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_PDM_Msk (0xc0000UL)              /*!< BUSY_PDM（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SRC_Pos (16UL)                   /*!< BUSY_SRC（位16）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SRC_Msk (0x30000UL)              /*!< BUSY_SRC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_PCM_Pos (14UL)                   /*!< BUSY_PCM（位14）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_PCM_Msk (0xc000UL)               /*!< BUSY_PCM（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SDADC_Pos (12UL)                 /*!< BUSY_SDADC（位12）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SDADC_Msk (0x3000UL)             /*!< BUSY_SDADC（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_I2C2_Pos (10UL)                  /*!< BUSY_I2C2（位10）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_I2C2_Msk (0xc00UL)               /*!< BUSY_I2C2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_I2C_Pos (8UL)                    /*!< BUSY_I2C（位8）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_I2C_Msk (0x300UL)                /*!< BUSY_I2C（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SPI2_Pos (6UL)                   /*!< BUSY_SPI2（位6）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SPI2_Msk (0xc0UL)                /*!< BUSY_SPI2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SPI_Pos (4UL)                    /*!< BUSY_SPI（位4）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_SPI_Msk (0x30UL)                 /*!< BUSY_SPI（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_UART2_Pos (2UL)                  /*!< BUSY_UART2（位2）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_UART2_Msk (0xcUL)                /*!< BUSY_UART2（位字段掩码：0x03）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_UART_Pos (0UL)                   /*!< BUSY_UART（位0）*/
#define MEMCTRL_BUSY_STAT_REG_BUSY_UART_Msk (0x3UL)                 /*!< BUSY_UART（位字段掩码：0x03）*/
/* ===================================================  CMI_CODE_BASE_REG  =================================================== */
#define MEMCTRL_CMI_CODE_BASE_REG_CMI_CODE_BASE_ADDR_Pos (10UL)     /*!< CMI_CODE_BASE_ADDR（位10）*/
#define MEMCTRL_CMI_CODE_BASE_REG_CMI_CODE_BASE_ADDR_Msk (0x7fc00UL) /*!< CMI_CODE_BASE_ADDR（位字段掩码：0x1ff）*/
/* ===================================================  CMI_DATA_BASE_REG  =================================================== */
#define MEMCTRL_CMI_DATA_BASE_REG_CMI_DATA_BASE_ADDR_Pos (2UL)      /*!< CMI_DATA_BASE_DDR（位2）*/
#define MEMCTRL_CMI_DATA_BASE_REG_CMI_DATA_BASE_ADDR_Msk (0x7fffcUL) /*!< CMI_DATA_BASE_ADDR（位字段掩码：0x1ffff）*/
/* ======================================================  CMI_END_REG  ====================================================== */
#define MEMCTRL_CMI_END_REG_CMI_END_ADDR_Pos (10UL)                 /*!< CMI_END_ADDR（位10）*/
#define MEMCTRL_CMI_END_REG_CMI_END_ADDR_Msk (0x7fc00UL)            /*!< CMI_END_ADDR（位字段掩码：0x1ff）*/
/* ==================================================  CMI_SHARED_BASE_REG  ================================================== */
#define MEMCTRL_CMI_SHARED_BASE_REG_CMI_SHARED_BASE_ADDR_Pos (10UL) /*!< CMI_SHARED_BASE_ADDR（位10）*/
#define MEMCTRL_CMI_SHARED_BASE_REG_CMI_SHARED_BASE_ADDR_Msk (0x7fc00UL) /*!< CMI_SHARED_BASE_ADDR（位字段掩码：0x1ff）*/
/* =====================================================  MEM_PRIO_REG  ====================================================== */
#define MEMCTRL_MEM_PRIO_REG_AHB_PRIO_Pos (4UL)                     /*!< AHB_PRIO（位4）*/
#define MEMCTRL_MEM_PRIO_REG_AHB_PRIO_Msk (0x30UL)                  /*!< AHB_PRIO（位域掩码：0x03）*/
#define MEMCTRL_MEM_PRIO_REG_AHB2_PRIO_Pos (2UL)                    /*!< AHB2_PRIO（位2）*/
#define MEMCTRL_MEM_PRIO_REG_AHB2_PRIO_Msk (0xcUL)                  /*!< AHB2_PRIO（位域掩码：0x03）*/
#define MEMCTRL_MEM_PRIO_REG_SNC_PRIO_Pos (0UL)                     /*!< SNC_PRIO（位0）*/
#define MEMCTRL_MEM_PRIO_REG_SNC_PRIO_Msk (0x3UL)                   /*!< SNC_PRIO（位域掩码：0x03）*/
/* =====================================================  MEM_STALL_REG  ===================================================== */
#define MEMCTRL_MEM_STALL_REG_AHB_MAX_STALL_Pos (8UL)               /*!< AHB_MAX_STALL（位8）*/
#define MEMCTRL_MEM_STALL_REG_AHB_MAX_STALL_Msk (0xf00UL)           /*!< AHB_MAX_STALL（位字段掩码：0x0f）*/
#define MEMCTRL_MEM_STALL_REG_AHB2_MAX_STALL_Pos (4UL)              /*!< AHB2_MAX_STALL（位4）*/
#define MEMCTRL_MEM_STALL_REG_AHB2_MAX_STALL_Msk (0xf0UL)           /*!< AHB2_MAX_STALL（位字段掩码：0x0f）*/
#define MEMCTRL_MEM_STALL_REG_SNC_MAX_STALL_Pos (0UL)               /*!< SNC_MAX_STALL（位0）*/
#define MEMCTRL_MEM_STALL_REG_SNC_MAX_STALL_Msk (0xfUL)             /*!< SNC_MAX_STALL（位域掩码：0x0f）*/
/* ====================================================  MEM_STATUS2_REG  ==================================================== */
#define MEMCTRL_MEM_STATUS2_REG_RAM8_OFF_BUT_ACCESS_Pos (7UL)       /*!< RAM8_OFF_BUT_ACCESS（位7）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM8_OFF_BUT_ACCESS_Msk (0x80UL)    /*!< RAM8_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM7_OFF_BUT_ACCESS_Pos (6UL)       /*!< RAM7_OFF_BUT_ACCESS（位6）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM7_OFF_BUT_ACCESS_Msk (0x40UL)    /*!< RAM7_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM6_OFF_BUT_ACCESS_Pos (5UL)       /*!< RAM6_OFF_BUT_ACCESS（位5）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM6_OFF_BUT_ACCESS_Msk (0x20UL)    /*!< RAM6_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM5_OFF_BUT_ACCESS_Pos (4UL)       /*!< RAM5_OFF_BUT_ACCESS（位4）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM5_OFF_BUT_ACCESS_Msk (0x10UL)    /*!< RAM5_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM4_OFF_BUT_ACCESS_Pos (3UL)       /*!< RAM4_OFF_BUT_ACCESS（位3）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM4_OFF_BUT_ACCESS_Msk (0x8UL)     /*!< RAM4_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM3_OFF_BUT_ACCESS_Pos (2UL)       /*!< RAM3_OFF_BUT_ACCESS（位2）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM3_OFF_BUT_ACCESS_Msk (0x4UL)     /*!< RAM3_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM2_OFF_BUT_ACCESS_Pos (1UL)       /*!< RAM2_OFF_BUT_ACCESS（位1）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM2_OFF_BUT_ACCESS_Msk (0x2UL)     /*!< RAM2_OFF_BUT_ACCESS（位域掩码：0x01）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM1_OFF_BUT_ACCESS_Pos (0UL)       /*!< RAM1_OFF_BUT_ACCESS（位0）*/
#define MEMCTRL_MEM_STATUS2_REG_RAM1_OFF_BUT_ACCESS_Msk (0x1UL)     /*!< RAM1_OFF_BUT_ACCESS（位域掩码：0x01）*/
/* ====================================================  MEM_STATUS_REG  ===================================================== */
#define MEMCTRL_MEM_STATUS_REG_CMI_CLEAR_READY_Pos (13UL)           /*!< CMI_CLEAR_READY（位13）*/
#define MEMCTRL_MEM_STATUS_REG_CMI_CLEAR_READY_Msk (0x2000UL)       /*!< CMI_CLEAR_READY（位字段掩码：0x01）*/
#define MEMCTRL_MEM_STATUS_REG_CMI_NOT_READY_Pos (12UL)             /*!< CMI_NOT_READY（位12）*/
#define MEMCTRL_MEM_STATUS_REG_CMI_NOT_READY_Msk (0x1000UL)         /*!< CMI_NOT_READY（位字段掩码：0x01）*/
#define MEMCTRL_MEM_STATUS_REG_AHB2_WR_BUFF_CNT_Pos (8UL)           /*!< AHB2_WR_BUFF_CNT（位8）*/
#define MEMCTRL_MEM_STATUS_REG_AHB2_WR_BUFF_CNT_Msk (0xf00UL)       /*!< AHB2_WR_BUFF_CNT（位字段掩码：0x0f）*/
#define MEMCTRL_MEM_STATUS_REG_AHB_WR_BUFF_CNT_Pos (4UL)            /*!< AHB_WR_BUFF_CNT（位4）*/
#define MEMCTRL_MEM_STATUS_REG_AHB_WR_BUFF_CNT_Msk (0xf0UL)         /*!< AHB_WR_BUFF_CNT（位域掩码：0x0f）*/
#define MEMCTRL_MEM_STATUS_REG_AHB2_CLR_WR_BUFF_Pos (3UL)           /*!< AHB2_CLR_WR_BUFF（位3）*/
#define MEMCTRL_MEM_STATUS_REG_AHB2_CLR_WR_BUFF_Msk (0x8UL)         /*!< AHB2_CLR_WR_BUFF（位字段掩码：0x01）*/
#define MEMCTRL_MEM_STATUS_REG_AHB_CLR_WR_BUFF_Pos (2UL)            /*!< AHB_CLR_WR_BUFF（位2）*/
#define MEMCTRL_MEM_STATUS_REG_AHB_CLR_WR_BUFF_Msk (0x4UL)          /*!< AHB_CLR_WR_BUFF（位字段掩码：0x01）*/
#define MEMCTRL_MEM_STATUS_REG_AHB2_WRITE_BUFF_Pos (1UL)            /*!< AHB2_WRITE_BUFF（位1）*/
#define MEMCTRL_MEM_STATUS_REG_AHB2_WRITE_BUFF_Msk (0x2UL)          /*!< AHB2_WRITE_BUFF（位字段掩码：0x01）*/
#define MEMCTRL_MEM_STATUS_REG_AHB_WRITE_BUFF_Pos (0UL)             /*!< AHB_WRITE_BUFF（位0）*/
#define MEMCTRL_MEM_STATUS_REG_AHB_WRITE_BUFF_Msk (0x1UL)           /*!< AHB_WRITE_BUFF（位字段掩码：0x01）*/
/* =====================================================  SNC_BASE_REG  ====================================================== */
#define MEMCTRL_SNC_BASE_REG_SNC_BASE_ADDRESS_Pos (2UL)             /*!< SNC_BASE_ADDRESS（位2）*/
#define MEMCTRL_SNC_BASE_REG_SNC_BASE_ADDRESS_Msk (0x7fffcUL)       /*!< SNC_BASE_ADDRESS（位域掩码：0x1ffff）*/


/* =========================================================================================================================== */
/* ================                                           OTPC                                            ================ */
/* =========================================================================================================================== */

/* =====================================================  OTPC_MODE_REG  ===================================================== */
#define OTPC_OTPC_MODE_REG_OTPC_MODE_PRG_SEL_Pos (6UL)              /*!< OTPC_MODE_PRG_SEL（位6）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_PRG_SEL_Msk (0xc0UL)           /*!< OTPC_MODE_PRG_SEL（位字段掩码：0x03）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_HT_MARG_EN_Pos (5UL)           /*!< OTPC_MODE_HT_MARG_EN（位5）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_HT_MARG_EN_Msk (0x20UL)        /*!< OTPC_MODE_HT_MARG_EN（位域掩码：0x01）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_USE_TST_ROW_Pos (4UL)          /*!< OTPC_MODE_USE_TST_ROW（位4）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_USE_TST_ROW_Msk (0x10UL)       /*!< OTPC_MODE_USE_TST_ROW（位字段掩码：0x01）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_MODE_Pos (0UL)                 /*!< OTPC_MODE_MODE（位0）*/
#define OTPC_OTPC_MODE_REG_OTPC_MODE_MODE_Msk (0x7UL)               /*!< OTPC_MODE_MODE（位字段掩码：0x07）*/
/* ====================================================  OTPC_PADDR_REG  ===================================================== */
#define OTPC_OTPC_PADDR_REG_OTPC_PADDR_Pos (0UL)                    /*!< OTPC_PADDR（位0）*/
#define OTPC_OTPC_PADDR_REG_OTPC_PADDR_Msk (0x3ffUL)                /*!< OTPC_PADDR（位域掩码：0x3ff）*/
/* ====================================================  OTPC_PWORD_REG  ===================================================== */
#define OTPC_OTPC_PWORD_REG_OTPC_PWORD_Pos (0UL)                    /*!< OTPC_PORD（位0）*/
#define OTPC_OTPC_PWORD_REG_OTPC_PWORD_Msk (0xffffffffUL)           /*!< OTPC_PORD（位域掩码：0xffffffff）*/
/* =====================================================  OTPC_STAT_REG  ===================================================== */
#define OTPC_OTPC_STAT_REG_OTPC_STAT_MRDY_Pos (2UL)                 /*!< OTPC_STAT_MRDY（位2）*/
#define OTPC_OTPC_STAT_REG_OTPC_STAT_MRDY_Msk (0x4UL)               /*!< OTPC_STAT_MRDY（位字段掩码：0x01）*/
#define OTPC_OTPC_STAT_REG_OTPC_STAT_PBUF_EMPTY_Pos (1UL)           /*!< OTPC_STAT_PBUF_EMPTY（位1）*/
#define OTPC_OTPC_STAT_REG_OTPC_STAT_PBUF_EMPTY_Msk (0x2UL)         /*!< OTPC_STAT_PBUF_EMPTY（位字段掩码：0x01）*/
#define OTPC_OTPC_STAT_REG_OTPC_STAT_PRDY_Pos (0UL)                 /*!< OTPC_STAT_PRDY（位0）*/
#define OTPC_OTPC_STAT_REG_OTPC_STAT_PRDY_Msk (0x1UL)               /*!< OTPC_STAT_PRDY（位字段掩码：0x01）*/
/* =====================================================  OTPC_TIM1_REG  ===================================================== */
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CSP_Pos (24UL)            /*!< OTPC_TIM1_US_T_CSP（位24）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CSP_Msk (0x7f000000UL)    /*!< OTPC_TIM1_US_T_CSP（位域掩码：0x7f）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CS_Pos (20UL)             /*!< OTPC_TIM1_US_T_CS（位20）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CS_Msk (0xf00000UL)       /*!< OTPC_TIM1_US_T_CS（位字段掩码：0x0f）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_PL_Pos (16UL)             /*!< OTPC_TIM1_US_T_PL（位16）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_PL_Msk (0xf0000UL)        /*!< OTPC_TIM1_US_T_PL（位字段掩码：0x0f）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_RD_Pos (12UL)             /*!< OTPC_TIM1_CC_T_RD（位12）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_RD_Msk (0x7000UL)         /*!< OTPC_TIM1_CC_T_RD（位字段掩码：0x07）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_20NS_Pos (8UL)            /*!< OTPC_TIM1_CC_T_20NS（位8）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_20NS_Msk (0x300UL)        /*!< OTPC_TIM1_CC_T_20NS（位域掩码：0x03）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_1US_Pos (0UL)             /*!< OTPC_TIM1_CC_T_1US（位0）*/
#define OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_1US_Msk (0x7fUL)          /*!< OTPC_TIM1_CC_T_1US（位域掩码：0x7f）*/
/* =====================================================  OTPC_TIM2_REG  ===================================================== */
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_ADD_CC_EN_Pos (31UL)        /*!< OTPC_TIM2_US_ADD_CC_EN（第31位）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_ADD_CC_EN_Msk (0x80000000UL) /*!< OTPC_TIM2_US_ADD_CC_EN（位域掩码：0x01）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_SAS_Pos (29UL)            /*!< OTPC_TIM2_US_T_SAS（第29位）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_SAS_Msk (0x60000000UL)    /*!< OTPC_TIM2_US_T_SAS（位字段掩码：0x03）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PPH_Pos (24UL)            /*!< OTPC_TIM2_US_T_PPH（位24）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PPH_Msk (0x1f000000UL)    /*!< OTPC_TIM2_US_T_PPH（位域掩码：0x1f）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_VDS_Pos (21UL)            /*!< OTPC_TIM2_US_T_VDS（第21位）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_VDS_Msk (0xe00000UL)      /*!< OTPC_TIM2_US_T_VDS（位字段掩码：0x07）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PPS_Pos (16UL)            /*!< OTPC_TIM2_US_T_PPS（位16）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PPS_Msk (0x1f0000UL)      /*!< OTPC_TIM2_US_T_PPS（位域掩码：0x1f）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PPR_Pos (8UL)             /*!< OTPC_TIM2_US_T_PPR（位8）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PPR_Msk (0x7f00UL)        /*!< OTPC_TIM2_US_T_PPR（位字段掩码：0x7f）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PWI_Pos (5UL)             /*!< OTPC_TIM2_US_T_PWI（位5）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PWI_Msk (0xe0UL)          /*!< OTPC_TIM2_US_T_PWI（位字段掩码：0x07）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PW_Pos (0UL)              /*!< OTPC_TIM2_US_T_PW（位0）*/
#define OTPC_OTPC_TIM2_REG_OTPC_TIM2_US_T_PW_Msk (0x1fUL)           /*!< OTPC_TIM2_US_T_PW（位域掩码：0x1f）*/


/* =========================================================================================================================== */
/* ================                                            PDC                                            ================ */
/* =========================================================================================================================== */

/* ==================================================  PDC_ACKNOWLEDGE_REG  ================================================== */
#define PDC_PDC_ACKNOWLEDGE_REG_PDC_ACKNOWLEDGE_Pos (0UL)           /*!< PDC_ACKNOWLEDGE（位0）*/
#define PDC_PDC_ACKNOWLEDGE_REG_PDC_ACKNOWLEDGE_Msk (0x1fUL)        /*!< PDC_ACKNOWLEDGE（位域掩码：0x1f）*/
/* =====================================================  PDC_CTRL0_REG  ===================================================== */
#define PDC_PDC_CTRL0_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL0_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL0_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL0_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL0_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL0_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL0_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL0_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL0_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL0_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL0_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL0_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL0_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL0_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* ====================================================  PDC_CTRL10_REG  ===================================================== */
#define PDC_PDC_CTRL10_REG_PDC_MASTER_Pos (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL10_REG_PDC_MASTER_Msk (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL10_REG_EN_COM_Pos     (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL10_REG_EN_COM_Msk     (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL10_REG_EN_PER_Pos     (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL10_REG_EN_PER_Msk     (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL10_REG_EN_TMR_Pos     (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL10_REG_EN_TMR_Msk     (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL10_REG_EN_XTAL_Pos    (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL10_REG_EN_XTAL_Msk    (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL10_REG_TRIG_ID_Pos    (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL10_REG_TRIG_ID_Msk    (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL10_REG_TRIG_SELECT_Pos (0UL)                    /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL10_REG_TRIG_SELECT_Msk (0x3UL)                  /*!< TRIG_SELECT（位域掩码：0x03）*/
/* ====================================================  PDC_CTRL11_REG  ===================================================== */
#define PDC_PDC_CTRL11_REG_PDC_MASTER_Pos (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL11_REG_PDC_MASTER_Msk (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL11_REG_EN_COM_Pos     (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL11_REG_EN_COM_Msk     (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL11_REG_EN_PER_Pos     (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL11_REG_EN_PER_Msk     (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL11_REG_EN_TMR_Pos     (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL11_REG_EN_TMR_Msk     (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL11_REG_EN_XTAL_Pos    (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL11_REG_EN_XTAL_Msk    (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL11_REG_TRIG_ID_Pos    (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL11_REG_TRIG_ID_Msk    (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL11_REG_TRIG_SELECT_Pos (0UL)                    /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL11_REG_TRIG_SELECT_Msk (0x3UL)                  /*!< TRIG_SELECT（位域掩码：0x03）*/
/* ====================================================  PDC_CTRL12_REG  ===================================================== */
#define PDC_PDC_CTRL12_REG_PDC_MASTER_Pos (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL12_REG_PDC_MASTER_Msk (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL12_REG_EN_COM_Pos     (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL12_REG_EN_COM_Msk     (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL12_REG_EN_PER_Pos     (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL12_REG_EN_PER_Msk     (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL12_REG_EN_TMR_Pos     (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL12_REG_EN_TMR_Msk     (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL12_REG_EN_XTAL_Pos    (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL12_REG_EN_XTAL_Msk    (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL12_REG_TRIG_ID_Pos    (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL12_REG_TRIG_ID_Msk    (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL12_REG_TRIG_SELECT_Pos (0UL)                    /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL12_REG_TRIG_SELECT_Msk (0x3UL)                  /*!< TRIG_SELECT（位域掩码：0x03）*/
/* ====================================================  PDC_CTRL13_REG  ===================================================== */
#define PDC_PDC_CTRL13_REG_PDC_MASTER_Pos (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL13_REG_PDC_MASTER_Msk (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL13_REG_EN_COM_Pos     (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL13_REG_EN_COM_Msk     (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL13_REG_EN_PER_Pos     (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL13_REG_EN_PER_Msk     (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL13_REG_EN_TMR_Pos     (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL13_REG_EN_TMR_Msk     (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL13_REG_EN_XTAL_Pos    (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL13_REG_EN_XTAL_Msk    (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL13_REG_TRIG_ID_Pos    (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL13_REG_TRIG_ID_Msk    (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL13_REG_TRIG_SELECT_Pos (0UL)                    /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL13_REG_TRIG_SELECT_Msk (0x3UL)                  /*!< TRIG_SELECT（位域掩码：0x03）*/
/* ====================================================  PDC_CTRL14_REG  ===================================================== */
#define PDC_PDC_CTRL14_REG_PDC_MASTER_Pos (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL14_REG_PDC_MASTER_Msk (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL14_REG_EN_COM_Pos     (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL14_REG_EN_COM_Msk     (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL14_REG_EN_PER_Pos     (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL14_REG_EN_PER_Msk     (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL14_REG_EN_TMR_Pos     (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL14_REG_EN_TMR_Msk     (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL14_REG_EN_XTAL_Pos    (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL14_REG_EN_XTAL_Msk    (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL14_REG_TRIG_ID_Pos    (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL14_REG_TRIG_ID_Msk    (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL14_REG_TRIG_SELECT_Pos (0UL)                    /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL14_REG_TRIG_SELECT_Msk (0x3UL)                  /*!< TRIG_SELECT（位域掩码：0x03）*/
/* ====================================================  PDC_CTRL15_REG  ===================================================== */
#define PDC_PDC_CTRL15_REG_PDC_MASTER_Pos (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL15_REG_PDC_MASTER_Msk (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL15_REG_EN_COM_Pos     (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL15_REG_EN_COM_Msk     (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL15_REG_EN_PER_Pos     (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL15_REG_EN_PER_Msk     (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL15_REG_EN_TMR_Pos     (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL15_REG_EN_TMR_Msk     (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL15_REG_EN_XTAL_Pos    (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL15_REG_EN_XTAL_Msk    (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL15_REG_TRIG_ID_Pos    (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL15_REG_TRIG_ID_Msk    (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL15_REG_TRIG_SELECT_Pos (0UL)                    /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL15_REG_TRIG_SELECT_Msk (0x3UL)                  /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL1_REG  ===================================================== */
#define PDC_PDC_CTRL1_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL1_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL1_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL1_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL1_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL1_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL1_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL1_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL1_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL1_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL1_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL1_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL1_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL1_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL2_REG  ===================================================== */
#define PDC_PDC_CTRL2_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL2_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL2_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL2_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL2_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL2_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL2_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL2_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL2_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL2_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL2_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL2_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL2_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL2_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL3_REG  ===================================================== */
#define PDC_PDC_CTRL3_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL3_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL3_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL3_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL3_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL3_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL3_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL3_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL3_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL3_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL3_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL3_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL3_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL3_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL4_REG  ===================================================== */
#define PDC_PDC_CTRL4_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL4_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL4_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL4_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL4_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL4_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL4_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL4_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL4_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL4_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL4_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL4_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL4_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL4_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL5_REG  ===================================================== */
#define PDC_PDC_CTRL5_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL5_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL5_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL5_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL5_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL5_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL5_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL5_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL5_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL5_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL5_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL5_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL5_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL5_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL6_REG  ===================================================== */
#define PDC_PDC_CTRL6_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL6_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL6_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL6_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL6_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL6_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL6_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL6_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL6_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL6_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL6_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL6_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL6_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL6_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL7_REG  ===================================================== */
#define PDC_PDC_CTRL7_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL7_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL7_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL7_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL7_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL7_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL7_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL7_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL7_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL7_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL7_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL7_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL7_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL7_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL8_REG  ===================================================== */
#define PDC_PDC_CTRL8_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL8_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL8_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL8_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL8_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL8_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL8_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL8_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL8_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL8_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL8_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL8_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL8_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL8_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =====================================================  PDC_CTRL9_REG  ===================================================== */
#define PDC_PDC_CTRL9_REG_PDC_MASTER_Pos  (11UL)                    /*!< PDC_MASTER（位11）*/
#define PDC_PDC_CTRL9_REG_PDC_MASTER_Msk  (0x1800UL)                /*!< PDC_MASTER（位域掩码：0x03）*/
#define PDC_PDC_CTRL9_REG_EN_COM_Pos      (10UL)                    /*!< EN_COM（位10）*/
#define PDC_PDC_CTRL9_REG_EN_COM_Msk      (0x400UL)                 /*!< EN_COM（位域掩码：0x01）*/
#define PDC_PDC_CTRL9_REG_EN_PER_Pos      (9UL)                     /*!< EN_PER（第9位）*/
#define PDC_PDC_CTRL9_REG_EN_PER_Msk      (0x200UL)                 /*!< EN_PER（位域掩码：0x01）*/
#define PDC_PDC_CTRL9_REG_EN_TMR_Pos      (8UL)                     /*!< EN_TMR（第8位）*/
#define PDC_PDC_CTRL9_REG_EN_TMR_Msk      (0x100UL)                 /*!< EN_TMR（位域掩码：0x01）*/
#define PDC_PDC_CTRL9_REG_EN_XTAL_Pos     (7UL)                     /*!< EN_XTAL（位7）*/
#define PDC_PDC_CTRL9_REG_EN_XTAL_Msk     (0x80UL)                  /*!< EN_XTAL（位域掩码：0x01）*/
#define PDC_PDC_CTRL9_REG_TRIG_ID_Pos     (2UL)                     /*!< TRIG_ID（位2）*/
#define PDC_PDC_CTRL9_REG_TRIG_ID_Msk     (0x7cUL)                  /*!< TRIG_ID（位域掩码：0x1f）*/
#define PDC_PDC_CTRL9_REG_TRIG_SELECT_Pos (0UL)                     /*!< TRIG_SELECT（位0）*/
#define PDC_PDC_CTRL9_REG_TRIG_SELECT_Msk (0x3UL)                   /*!< TRIG_SELECT（位域掩码：0x03）*/
/* =================================================  PDC_PENDING_CM33_REG  ================================================== */
#define PDC_PDC_PENDING_CM33_REG_PDC_PENDING_Pos (0UL)              /*!< PDC_PENDING（位0）*/
#define PDC_PDC_PENDING_CM33_REG_PDC_PENDING_Msk (0xffffUL)         /*!< PDC_PENDING（位字段掩码：0xffff）*/
/* =================================================  PDC_PENDING_CMAC_REG  ================================================== */
#define PDC_PDC_PENDING_CMAC_REG_PDC_PENDING_Pos (0UL)              /*!< PDC_PENDING（位0）*/
#define PDC_PDC_PENDING_CMAC_REG_PDC_PENDING_Msk (0xffffUL)         /*!< PDC_PENDING（位字段掩码：0xffff）*/
/* ====================================================  PDC_PENDING_REG  ==================================================== */
#define PDC_PDC_PENDING_REG_PDC_PENDING_Pos (0UL)                   /*!< PDC_PENDING（位0）*/
#define PDC_PDC_PENDING_REG_PDC_PENDING_Msk (0xffffUL)              /*!< PDC_PENDING（位字段掩码：0xffff）*/
/* ==================================================  PDC_PENDING_SNC_REG  ================================================== */
#define PDC_PDC_PENDING_SNC_REG_PDC_PENDING_Pos (0UL)               /*!< PDC_PENDING（位0）*/
#define PDC_PDC_PENDING_SNC_REG_PDC_PENDING_Msk (0xffffUL)          /*!< PDC_PENDING（位字段掩码：0xffff）*/
/* ==================================================  PDC_SET_PENDING_REG  ================================================== */
#define PDC_PDC_SET_PENDING_REG_PDC_SET_PENDING_Pos (0UL)           /*!< PDC_SET_PENDING（位0）*/
#define PDC_PDC_SET_PENDING_REG_PDC_SET_PENDING_Msk (0x1fUL)        /*!< PDC_SET_PENDING（位字段掩码：0x1f）*/


/* =========================================================================================================================== */
/* ================                                          PWMLED                                           ================ */
/* =========================================================================================================================== */

/* ====================================================  PWMLED_CTRL_REG  ==================================================== */
#define PWMLED_PWMLED_CTRL_REG_LED2_LOAD_SEL_Pos (11UL)             /*!< LED2_LOAD_SEL（位11）*/
#define PWMLED_PWMLED_CTRL_REG_LED2_LOAD_SEL_Msk (0x3800UL)         /*!< LED2_LOAD_SEL（位字段掩码：0x07）*/
#define PWMLED_PWMLED_CTRL_REG_LED1_LOAD_SEL_Pos (8UL)              /*!< LED1_LOAD_SEL（位8）*/
#define PWMLED_PWMLED_CTRL_REG_LED1_LOAD_SEL_Msk (0x700UL)          /*!< LED1_LOAD_SEL（位字段掩码：0x07）*/
#define PWMLED_PWMLED_CTRL_REG_LED2_EN_Pos (7UL)                    /*!< LED2_EN（第7位）*/
#define PWMLED_PWMLED_CTRL_REG_LED2_EN_Msk (0x80UL)                 /*!< LED2_EN（位域掩码：0x01）*/
#define PWMLED_PWMLED_CTRL_REG_LED1_EN_Pos (6UL)                    /*!< LED1_EN（位6）*/
#define PWMLED_PWMLED_CTRL_REG_LED1_EN_Msk (0x40UL)                 /*!< LED1_EN（位域掩码：0x01）*/
#define PWMLED_PWMLED_CTRL_REG_LED_TRIM_Pos (2UL)                   /*!< LED_TRIM（位2）*/
#define PWMLED_PWMLED_CTRL_REG_LED_TRIM_Msk (0x3cUL)                /*!< LED_TRIM（位域掩码：0x0f）*/
#define PWMLED_PWMLED_CTRL_REG_SW_PAUSE_EN_Pos (1UL)                /*!< SW_PAUSE_EN（位1）*/
#define PWMLED_PWMLED_CTRL_REG_SW_PAUSE_EN_Msk (0x2UL)              /*!< SW_PAUSE_EN（位字段掩码：0x01）*/
#define PWMLED_PWMLED_CTRL_REG_PWM_ENABLE_Pos (0UL)                 /*!< PWM_ENABLE（位0）*/
#define PWMLED_PWMLED_CTRL_REG_PWM_ENABLE_Msk (0x1UL)               /*!< PWM_ENABLE（位字段掩码：0x01）*/
/* ==============================================  PWMLED_DUTY_CYCLE_LED1_REG  =============================================== */
#define PWMLED_PWMLED_DUTY_CYCLE_LED1_REG_LED1_PWM_START_CYCLE_Pos (8UL) /*!< LED1_PWM_START_CYCLE（位8）*/
#define PWMLED_PWMLED_DUTY_CYCLE_LED1_REG_LED1_PWM_START_CYCLE_Msk (0xff00UL) /*!< LED1_PWM_START_CYCLE（位域掩码：0xff）*/
#define PWMLED_PWMLED_DUTY_CYCLE_LED1_REG_LED1_PWM_END_CYCLE_Pos (0UL) /*!< LED1_PWM_END_CYCLE（位0）*/
#define PWMLED_PWMLED_DUTY_CYCLE_LED1_REG_LED1_PWM_END_CYCLE_Msk (0xffUL) /*!< LED1_PWM_END_CYCLE（位域掩码：0xff）*/
/* ==============================================  PWMLED_DUTY_CYCLE_LED2_REG  =============================================== */
#define PWMLED_PWMLED_DUTY_CYCLE_LED2_REG_LED2_PWM_START_CYCLE_Pos (8UL) /*!< LED2_PWM_START_CYCLE（位8）*/
#define PWMLED_PWMLED_DUTY_CYCLE_LED2_REG_LED2_PWM_START_CYCLE_Msk (0xff00UL) /*!< LED2_PWM_START_CYCLE（位域掩码：0xff）*/
#define PWMLED_PWMLED_DUTY_CYCLE_LED2_REG_LED2_PWM_END_CYCLE_Pos (0UL) /*!< LED2_PWM_END_CYCLE（位0）*/
#define PWMLED_PWMLED_DUTY_CYCLE_LED2_REG_LED2_PWM_END_CYCLE_Msk (0xffUL) /*!< LED2_PWM_END_CYCLE（位域掩码：0xff）*/
/* =================================================  PWMLED_FREQUENCY_REG  ================================================== */
#define PWMLED_PWMLED_FREQUENCY_REG_LED_PWM_FREQUENCY_Pos (0UL)     /*!< LED_PWM_FREQUENCY（位0）*/
#define PWMLED_PWMLED_FREQUENCY_REG_LED_PWM_FREQUENCY_Msk (0xffUL)  /*!< LED_PWM_FREQUENCY（位域掩码：0xff）*/


/* =========================================================================================================================== */
/* ================                                           QSPIC                                           ================ */
/* =========================================================================================================================== */

/* ==================================================  QSPIC_BURSTBRK_REG  =================================================== */
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_SEC_HF_DS_Pos (20UL)         /*!< QSPIC_SEC_HF_DS（位20）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_SEC_HF_DS_Msk (0x100000UL)   /*!< QSPIC_SEC_HF_DS（位字段掩码：0x01）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_TX_MD_Pos (18UL)         /*!< QSPIC_BRK_TX_MD（第18位）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_TX_MD_Msk (0xc0000UL)    /*!< QSPIC_BRK_TX_MD（位域掩码：0x03）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_SZ_Pos (17UL)            /*!< QSPIC_BRK_SZ（位17）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_SZ_Msk (0x20000UL)       /*!< QSPIC_BRK_SZ（位域掩码：0x01）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_EN_Pos (16UL)            /*!< QSPIC_BRK_EN（位16）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_EN_Msk (0x10000UL)       /*!< QSPIC_BRK_EN（位字段掩码：0x01）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_WRD_Pos (0UL)            /*!< QSPIC_BRK_WRD（位0）*/
#define QSPIC_QSPIC_BURSTBRK_REG_QSPIC_BRK_WRD_Msk (0xffffUL)       /*!< QSPIC_BRK_WRD（位字段掩码：0xffff）*/
/* ==================================================  QSPIC_BURSTCMDA_REG  ================================================== */
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_DMY_TX_MD_Pos (30UL)        /*!< QSPIC_DMY_TX_MD（位30）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_DMY_TX_MD_Msk (0xc0000000UL) /*!< QSPIC_DMY_TX_MD（位域掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_EXT_TX_MD_Pos (28UL)        /*!< QSPIC_EXT_TX_MD（第28位）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_EXT_TX_MD_Msk (0x30000000UL) /*!< QSPIC_EXT_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_ADR_TX_MD_Pos (26UL)        /*!< QSPIC_ADR_TX_MD（位26）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_ADR_TX_MD_Msk (0xc000000UL) /*!< QSPIC_ADR_TX_MD（位域掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_INST_TX_MD_Pos (24UL)       /*!< QSPIC_INST_TX_MD（第24位）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_INST_TX_MD_Msk (0x3000000UL) /*!< QSPIC_INST_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_EXT_BYTE_Pos (16UL)         /*!< QSPIC_EXT_BYTE（位16）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_EXT_BYTE_Msk (0xff0000UL)   /*!< QSPIC_EXT_BYTE（位字段掩码：0xff）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_INST_WB_Pos (8UL)           /*!< QSPIC_INST_WB（位8）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_INST_WB_Msk (0xff00UL)      /*!< QSPIC_INST_WB（位字段掩码：0xff）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_INST_Pos (0UL)              /*!< QSPIC_INST（位0）*/
#define QSPIC_QSPIC_BURSTCMDA_REG_QSPIC_INST_Msk (0xffUL)           /*!< QSPIC_INST（位字段掩码：0xff）*/
/* ==================================================  QSPIC_BURSTCMDB_REG  ================================================== */
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_DMY_FORCE_Pos (15UL)        /*!< QSPIC_DMY_FORCE（位15）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_DMY_FORCE_Msk (0x8000UL)    /*!< QSPIC_DMY_FORCE（位域掩码：0x01）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_CS_HIGH_MIN_Pos (12UL)      /*!< QSPIC_CS_HIGH_MIN（位12）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_CS_HIGH_MIN_Msk (0x7000UL)  /*!< QSPIC_CS_HIGH_MIN（位字段掩码：0x07）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_WRAP_SIZE_Pos (10UL)        /*!< QSPIC_WRAP_SIZE（位10）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_WRAP_SIZE_Msk (0xc00UL)     /*!< QSPIC_WRAP_SIZE（位字段掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_WRAP_LEN_Pos (8UL)          /*!< QSPIC_WRAP_LEN（位8）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_WRAP_LEN_Msk (0x300UL)      /*!< QSPIC_WRAP_LEN（位字段掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_WRAP_MD_Pos (7UL)           /*!< QSPIC_WRAP_MD（第7位）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_WRAP_MD_Msk (0x80UL)        /*!< QSPIC_WRAP_MD（位字段掩码：0x01）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_INST_MD_Pos (6UL)           /*!< QSPIC_INST_MD（位6）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_INST_MD_Msk (0x40UL)        /*!< QSPIC_INST_MD（位字段掩码：0x01）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_DMY_NUM_Pos (4UL)           /*!< QSPIC_DMY_NUM（位4）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_DMY_NUM_Msk (0x30UL)        /*!< QSPIC_DMY_NUM（位字段掩码：0x03）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_EXT_HF_DS_Pos (3UL)         /*!< QSPIC_EXT_HF_DS（位3）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_EXT_HF_DS_Msk (0x8UL)       /*!< QSPIC_EXT_HF_DS（位字段掩码：0x01）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_EXT_BYTE_EN_Pos (2UL)       /*!< QSPIC_EXT_BYTE_EN（位2）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_EXT_BYTE_EN_Msk (0x4UL)     /*!< QSPIC_EXT_BYTE_EN（位字段掩码：0x01）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_DAT_RX_MD_Pos (0UL)         /*!< QSPIC_DAT_RX_MD（位0）*/
#define QSPIC_QSPIC_BURSTCMDB_REG_QSPIC_DAT_RX_MD_Msk (0x3UL)       /*!< QSPIC_DAT_RX_MD（位字段掩码：0x03）*/
/* ==================================================  QSPIC_CHCKERASE_REG  ================================================== */
#define QSPIC_QSPIC_CHCKERASE_REG_QSPIC_CHCKERASE_Pos (0UL)         /*!< QSPIC_CHCKERASE（位0）*/
#define QSPIC_QSPIC_CHCKERASE_REG_QSPIC_CHCKERASE_Msk (0xffffffffUL) /*!< QSPIC_CHCKERASE（位域掩码：0xffffffff）*/
/* ===================================================  QSPIC_CTRLBUS_REG  =================================================== */
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Pos (4UL)              /*!< QSPIC_DIS_CS（位4）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Msk (0x10UL)           /*!< QSPIC_DIS_CS（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_EN_CS_Pos (3UL)               /*!< QSPIC_EN_CS（位3）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_EN_CS_Msk (0x8UL)             /*!< QSPIC_EN_CS（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_SET_QUAD_Pos (2UL)            /*!< QSPIC_SET_QUAD（位2）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_SET_QUAD_Msk (0x4UL)          /*!< QSPIC_SET_QUAD（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_SET_DUAL_Pos (1UL)            /*!< QSPIC_SET_DUAL（位1）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_SET_DUAL_Msk (0x2UL)          /*!< QSPIC_SET_DUAL（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_SET_SINGLE_Pos (0UL)          /*!< QSPIC_SET_SINGLE（位0）*/
#define QSPIC_QSPIC_CTRLBUS_REG_QSPIC_SET_SINGLE_Msk (0x1UL)        /*!< QSPIC_SET_SINGLE（位字段掩码：0x01）*/
/* ==================================================  QSPIC_CTRLMODE_REG  =================================================== */
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_USE_32BA_Pos (13UL)          /*!< QSPIC_USE_32BA（第13位）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_USE_32BA_Msk (0x2000UL)      /*!< QSPIC_USE_32BA（位域掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_BUF_LIM_EN_Pos (12UL)        /*!< QSPIC_BUF_LIM_EN（第12位）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_BUF_LIM_EN_Msk (0x1000UL)    /*!< QSPIC_BUF_LIM_EN（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_PCLK_MD_Pos (9UL)            /*!< QSPIC_PCLK_MD（位9）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_PCLK_MD_Msk (0xe00UL)        /*!< QSPIC_PCLK_MD（位字段掩码：0x07）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_RPIPE_EN_Pos (8UL)           /*!< QSPIC_RPIPE_EN（位8）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_RPIPE_EN_Msk (0x100UL)       /*!< QSPIC_RPIPE_EN（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_RXD_NEG_Pos (7UL)            /*!< QSPIC_RXD_NEG（位7）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_RXD_NEG_Msk (0x80UL)         /*!< QSPIC_RXD_NEG（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_HRDY_MD_Pos (6UL)            /*!< QSPIC_HRDY_MD（位6）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_HRDY_MD_Msk (0x40UL)         /*!< QSPIC_HRDY_MD（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO3_DAT_Pos (5UL)            /*!< QSPIC_IO3_DAT（位5）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO3_DAT_Msk (0x20UL)         /*!< QSPIC_IO3_DAT（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO2_DAT_Pos (4UL)            /*!< QSPIC_IO2_DAT（位4）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO2_DAT_Msk (0x10UL)         /*!< QSPIC_IO2_DAT（位域掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO3_OEN_Pos (3UL)            /*!< QSPIC_IO3_OEN（位3）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO3_OEN_Msk (0x8UL)          /*!< QSPIC_IO3_OEN（位域掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO2_OEN_Pos (2UL)            /*!< QSPIC_IO2_OEN（位2）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_IO2_OEN_Msk (0x4UL)          /*!< QSPIC_IO2_OEN（位域掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_CLK_MD_Pos (1UL)             /*!< QSPIC_CLK_MD（位1）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_CLK_MD_Msk (0x2UL)           /*!< QSPIC_CLK_MD（位字段掩码：0x01）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_AUTO_MD_Pos (0UL)            /*!< QSPIC_AUTO_MD（位0）*/
#define QSPIC_QSPIC_CTRLMODE_REG_QSPIC_AUTO_MD_Msk (0x1UL)          /*!< QSPIC_AUTO_MD（位域掩码：0x01）*/
/* ==================================================  QSPIC_CTR_CTRL_REG  =================================================== */
#define QSPIC_QSPIC_CTR_CTRL_REG_QSPIC_CTR_EN_Pos (0UL)             /*!< QSPIC_CTR_EN（位0）*/
#define QSPIC_QSPIC_CTR_CTRL_REG_QSPIC_CTR_EN_Msk (0x1UL)           /*!< QSPIC_CTR_EN（位字段掩码：0x01）*/
/* ==================================================  QSPIC_CTR_EADDR_REG  ================================================== */
#define QSPIC_QSPIC_CTR_EADDR_REG_QSPIC_CTR_EADDR_Pos (10UL)        /*!< QSPIC_CTR_EADDR（位10）*/
#define QSPIC_QSPIC_CTR_EADDR_REG_QSPIC_CTR_EADDR_Msk (0xfffffc00UL) /*!< QSPIC_CTR_EADDR（位域掩码：0x3fffff）*/
/* =================================================  QSPIC_CTR_KEY_0_3_REG  ================================================= */
#define QSPIC_QSPIC_CTR_KEY_0_3_REG_QSPIC_CTR_KEY_0_3_Pos (0UL)     /*!< QSPIC_CTR_KEY_0_3（位0）*/
#define QSPIC_QSPIC_CTR_KEY_0_3_REG_QSPIC_CTR_KEY_0_3_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_0_3（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_KEY_12_15_REG  ================================================ */
#define QSPIC_QSPIC_CTR_KEY_12_15_REG_QSPIC_CTR_KEY_12_15_Pos (0UL) /*!< QSPIC_CTR_KEY_12_15（位0）*/
#define QSPIC_QSPIC_CTR_KEY_12_15_REG_QSPIC_CTR_KEY_12_15_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_12_15（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_KEY_16_19_REG  ================================================ */
#define QSPIC_QSPIC_CTR_KEY_16_19_REG_QSPIC_CTR_KEY_16_19_Pos (0UL) /*!< QSPIC_CTR_KEY_16_19（位0）*/
#define QSPIC_QSPIC_CTR_KEY_16_19_REG_QSPIC_CTR_KEY_16_19_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_16_19（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_KEY_20_23_REG  ================================================ */
#define QSPIC_QSPIC_CTR_KEY_20_23_REG_QSPIC_CTR_KEY_20_23_Pos (0UL) /*!< QSPIC_CTR_KEY_20_23（位0）*/
#define QSPIC_QSPIC_CTR_KEY_20_23_REG_QSPIC_CTR_KEY_20_23_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_20_23（位域掩码：0xffffff）*/
/* ================================================  QSPIC_CTR_KEY_24_27_REG  ================================================ */
#define QSPIC_QSPIC_CTR_KEY_24_27_REG_QSPIC_CTR_KEY_24_27_Pos (0UL) /*!< QSPIC_CTR_KEY_24_27（位0）*/
#define QSPIC_QSPIC_CTR_KEY_24_27_REG_QSPIC_CTR_KEY_24_27_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_24_27（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_KEY_28_31_REG  ================================================ */
#define QSPIC_QSPIC_CTR_KEY_28_31_REG_QSPIC_CTR_KEY_28_31_Pos (0UL) /*!< QSPIC_CTR_KEY_28_31（位0）*/
#define QSPIC_QSPIC_CTR_KEY_28_31_REG_QSPIC_CTR_KEY_28_31_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_28_31（位域掩码：0xffffffff）*/
/* =================================================  QSPIC_CTR_KEY_4_7_REG  ================================================= */
#define QSPIC_QSPIC_CTR_KEY_4_7_REG_QSPIC_CTR_KEY_4_7_Pos (0UL)     /*!< QSPIC_CTR_KEY_4_7（位0）*/
#define QSPIC_QSPIC_CTR_KEY_4_7_REG_QSPIC_CTR_KEY_4_7_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_4_7（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_KEY_8_11_REG  ================================================= */
#define QSPIC_QSPIC_CTR_KEY_8_11_REG_QSPIC_CTR_KEY_8_11_Pos (0UL)   /*!< QSPIC_CTR_KEY_8_11（位0）*/
#define QSPIC_QSPIC_CTR_KEY_8_11_REG_QSPIC_CTR_KEY_8_11_Msk (0xffffffffUL) /*!< QSPIC_CTR_KEY_8_11（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_NONCE_0_3_REG  ================================================ */
#define QSPIC_QSPIC_CTR_NONCE_0_3_REG_QSPIC_CTR_NONCE_0_3_Pos (0UL) /*!< QSPIC_CTR_NONCE_0_3（位0）*/
#define QSPIC_QSPIC_CTR_NONCE_0_3_REG_QSPIC_CTR_NONCE_0_3_Msk (0xffffffffUL) /*!< QSPIC_CTR_NONCE_0_3（位域掩码：0xffffffff）*/
/* ================================================  QSPIC_CTR_NONCE_4_7_REG  ================================================ */
#define QSPIC_QSPIC_CTR_NONCE_4_7_REG_QSPIC_CTR_NONCE_4_7_Pos (0UL) /*!< QSPIC_CTR_NONCE_4_7（位0）*/
#define QSPIC_QSPIC_CTR_NONCE_4_7_REG_QSPIC_CTR_NONCE_4_7_Msk (0xffffffffUL) /*!< QSPIC_CTR_NONCE_4_7（位域掩码：0xffffffff）*/
/* ==================================================  QSPIC_CTR_SADDR_REG  ================================================== */
#define QSPIC_QSPIC_CTR_SADDR_REG_QSPIC_CTR_SADDR_Pos (10UL)        /*!< QSPIC_CTR_SADDR（位10）*/
#define QSPIC_QSPIC_CTR_SADDR_REG_QSPIC_CTR_SADDR_Msk (0xfffffc00UL) /*!< QSPIC_CTR_SADDR（位域掩码：0x3fffff）*/
/* ==================================================  QSPIC_DUMMYDATA_REG  ================================================== */
#define QSPIC_QSPIC_DUMMYDATA_REG_QSPIC_DUMMYDATA_Pos (0UL)         /*!< QSPIC_DUMMYDATA（位0）*/
#define QSPIC_QSPIC_DUMMYDATA_REG_QSPIC_DUMMYDATA_Msk (0xffffffffUL) /*!< QSPIC_DUMMYDATA（位字段掩码：0xffffff）*/
/* ==================================================  QSPIC_ERASECMDA_REG  ================================================== */
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_RES_INST_Pos (24UL)         /*!< QSPIC_RES_INST（位24）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_RES_INST_Msk (0xff000000UL) /*!< QSPIC_RES_INST（位字段掩码：0xff）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_SUS_INST_Pos (16UL)         /*!< QSPIC_SUS_INST（位16）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_SUS_INST_Msk (0xff0000UL)   /*!< QSPIC_SUS_INST（位字段掩码：0xff）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_WEN_INST_Pos (8UL)          /*!< QSPIC_WEN_INST（位8）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_WEN_INST_Msk (0xff00UL)     /*!< QSPIC_WEN_INST（位字段掩码：0xff）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_ERS_INST_Pos (0UL)          /*!< QSPIC_ERS_INST（位0）*/
#define QSPIC_QSPIC_ERASECMDA_REG_QSPIC_ERS_INST_Msk (0xffUL)       /*!< QSPIC_ERS_INST（位字段掩码：0xff）*/
/* ==================================================  QSPIC_ERASECMDB_REG  ================================================== */
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_RESSUS_DLY_Pos (24UL)       /*!< QSPIC_RESSUS_DLY（位24）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_RESSUS_DLY_Msk (0x3f000000UL) /*!< QSPIC_RESSUS_DLY（位字段掩码：0x3f）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_ERSRES_HLD_Pos (16UL)       /*!< QSPIC_ERSRES_HLD（位16）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_ERSRES_HLD_Msk (0xf0000UL)  /*!< QSPIC_ERSRES_HLD（位字段掩码：0x0f）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_ERS_CS_HI_Pos (10UL)        /*!< QSPIC_ERS_CS_HI（位10）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_ERS_CS_HI_Msk (0x7c00UL)    /*!< QSPIC_ERS_CS_HI（位字段掩码：0x1f）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_EAD_TX_MD_Pos (8UL)         /*!< QSPIC_EAD_TX_MD（位8）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_EAD_TX_MD_Msk (0x300UL)     /*!< QSPIC_EAD_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_RES_TX_MD_Pos (6UL)         /*!< QSPIC_RES_TX_MD（位6）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_RES_TX_MD_Msk (0xc0UL)      /*!< QSPIC_RES_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_SUS_TX_MD_Pos (4UL)         /*!< QSPIC_SUS_TX_MD（位4）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_SUS_TX_MD_Msk (0x30UL)      /*!< QSPIC_SUS_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_WEN_TX_MD_Pos (2UL)         /*!< QSPIC_WEN_TX_MD（位2）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_WEN_TX_MD_Msk (0xcUL)       /*!< QSPIC_WEN_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_ERS_TX_MD_Pos (0UL)         /*!< QSPIC_ERS_TX_MD（位0）*/
#define QSPIC_QSPIC_ERASECMDB_REG_QSPIC_ERS_TX_MD_Msk (0x3UL)       /*!< QSPIC_ERS_TX_MD（位字段掩码：0x03）*/
/* ==================================================  QSPIC_ERASECTRL_REG  ================================================== */
#define QSPIC_QSPIC_ERASECTRL_REG_QSPIC_ERS_STATE_Pos (25UL)        /*!< QSPIC_ERS_STATE（位25）*/
#define QSPIC_QSPIC_ERASECTRL_REG_QSPIC_ERS_STATE_Msk (0xe000000UL) /*!< QSPIC_ERS_STATE（位字段掩码：0x07）*/
#define QSPIC_QSPIC_ERASECTRL_REG_QSPIC_ERASE_EN_Pos (24UL)         /*!< QSPIC_ERASE_EN（位24）*/
#define QSPIC_QSPIC_ERASECTRL_REG_QSPIC_ERASE_EN_Msk (0x1000000UL)  /*!< QSPIC_ERASE_EN（位字段掩码：0x01）*/
#define QSPIC_QSPIC_ERASECTRL_REG_QSPIC_ERS_ADDR_Pos (4UL)          /*!< QSPIC_ERS_ADDR（位4）*/
#define QSPIC_QSPIC_ERASECTRL_REG_QSPIC_ERS_ADDR_Msk (0xfffff0UL)   /*!< QSPIC_ERS_ADDR（位字段掩码：0xfffff）*/
/* =====================================================  QSPIC_GP_REG  ====================================================== */
#define QSPIC_QSPIC_GP_REG_QSPIC_PADS_SLEW_Pos (3UL)                /*!< QSPIC_PADS_SLEW（位3）*/
#define QSPIC_QSPIC_GP_REG_QSPIC_PADS_SLEW_Msk (0x18UL)             /*!< QSPIC_PADS_SLEW（位域掩码：0x03）*/
#define QSPIC_QSPIC_GP_REG_QSPIC_PADS_DRV_Pos (1UL)                 /*!< QSPIC_PADS_DRV（位1）*/
#define QSPIC_QSPIC_GP_REG_QSPIC_PADS_DRV_Msk (0x6UL)               /*!< QSPIC_PADS_DRV（位字段掩码：0x03）*/
/* ==================================================  QSPIC_READDATA_REG  =================================================== */
#define QSPIC_QSPIC_READDATA_REG_QSPIC_READDATA_Pos (0UL)           /*!< QSPIC_READDATA（位0）*/
#define QSPIC_QSPIC_READDATA_REG_QSPIC_READDATA_Msk (0xffffffffUL)  /*!< QSPIC_READDATA（位字段掩码：0xffffffff）*/
/* ==================================================  QSPIC_RECVDATA_REG  =================================================== */
#define QSPIC_QSPIC_RECVDATA_REG_QSPIC_RECVDATA_Pos (0UL)           /*!< QSPIC_RECVDATA（位0）*/
#define QSPIC_QSPIC_RECVDATA_REG_QSPIC_RECVDATA_Msk (0xffffffffUL)  /*!< QSPIC_RECVDATA（位字段掩码：0xffffffff）*/
/* ==================================================  QSPIC_STATUSCMD_REG  ================================================== */
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_STSDLY_SEL_Pos (22UL)       /*!< QSPIC_STSDLY_SEL（位22）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_STSDLY_SEL_Msk (0x400000UL) /*!< QSPIC_STSDLY_SEL（位字段掩码：0x01）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RESSTS_DLY_Pos (16UL)       /*!< QSPIC_RESSTS_DLY（位16）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RESSTS_DLY_Msk (0x3f0000UL) /*!< QSPIC_RESSTS_DLY（位字段掩码：0x3f）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_BUSY_VAL_Pos (15UL)         /*!< QSPIC_BUSY_VAL（第15位）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_BUSY_VAL_Msk (0x8000UL)     /*!< QSPIC_BUSY_VAL（位字段掩码：0x01）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_BUSY_POS_Pos (12UL)         /*!< QSPIC_BUSY_POS（位12）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_BUSY_POS_Msk (0x7000UL)     /*!< QSPIC_BUSY_POS（位字段掩码：0x07）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RSTAT_RX_MD_Pos (10UL)      /*!< QSPIC_RSTAT_RX_MD（位10）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RSTAT_RX_MD_Msk (0xc00UL)   /*!< QSPIC_RSTAT_RX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RSTAT_TX_MD_Pos (8UL)       /*!< QSPIC_RSTAT_TX_MD（位8）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RSTAT_TX_MD_Msk (0x300UL)   /*!< QSPIC_RSTAT_TX_MD（位字段掩码：0x03）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RSTAT_INST_Pos (0UL)        /*!< QSPIC_RSTAT_INST（位0）*/
#define QSPIC_QSPIC_STATUSCMD_REG_QSPIC_RSTAT_INST_Msk (0xffUL)     /*!< QSPIC_RSTAT_INST（位字段掩码：0xff）*/
/* ===================================================  QSPIC_STATUS_REG  ==================================================== */
#define QSPIC_QSPIC_STATUS_REG_QSPIC_BUSY_Pos (0UL)                 /*!< QSPIC_BUSY（位0）*/
#define QSPIC_QSPIC_STATUS_REG_QSPIC_BUSY_Msk (0x1UL)               /*!< QSPIC_BUSY（位字段掩码：0x01）*/
/* ===================================================  QSPIC_UCODE_START  =================================================== */
#define QSPIC_QSPIC_UCODE_START_QSPIC_UCODE_X_Pos (0UL)             /*!< QSPIC_UCODE_X（位0）*/
#define QSPIC_QSPIC_UCODE_START_QSPIC_UCODE_X_Msk (0xffffffffUL)    /*!< QSPIC_UCODE_X（位字段掩码：0xffffff）*/
/* ==================================================  QSPIC_WRITEDATA_REG  ================================================== */
#define QSPIC_QSPIC_WRITEDATA_REG_QSPIC_WRITEDATA_Pos (0UL)         /*!< QSPIC_WRITEDATA（位0）*/
#define QSPIC_QSPIC_WRITEDATA_REG_QSPIC_WRITEDATA_Msk (0xffffffffUL) /*!< QSPIC_WRITEDATA（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                          QSPIC2                                           ================ */
/* =========================================================================================================================== */

/* =================================================  QSPIC2_AWRITECMD_REG  ================================================== */
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_CS_HIGH_MIN_Pos (14UL) /*!< QSPIC_WR_CS_HIGH_MIN（位14）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_CS_HIGH_MIN_Msk (0x7c000UL) /*!< QSPIC_WR_CS_HIGH_MIN（位域掩码：0x1f）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_DAT_TX_MD_Pos (12UL)   /*!< QSPIC_WR_DAT_TX_MD（第12位）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_DAT_TX_MD_Msk (0x3000UL) /*!< QSPIC_WR_DAT_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_ADR_TX_MD_Pos (10UL)   /*!< QSPIC_WR_ADR_TX_MD（位10）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_ADR_TX_MD_Msk (0xc00UL) /*!< QSPIC_WR_ADR_TX_MD（位域掩码：0x03）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_INST_TX_MD_Pos (8UL)   /*!< QSPIC_WR_INST_TX_MD（第8位）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_INST_TX_MD_Msk (0x300UL) /*!< QSPIC_WR_INST_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_INST_Pos (0UL)         /*!< QSPIC_WR_INST（位0）*/
#define QSPIC2_QSPIC2_AWRITECMD_REG_QSPIC_WR_INST_Msk (0xffUL)      /*!< QSPIC_WR_INST（位字段掩码：0xff）*/
/* ==================================================  QSPIC2_BURSTBRK_REG  ================================================== */
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_SEC_HF_DS_Pos (20UL)       /*!< QSPIC_SEC_HF_DS（位20）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_SEC_HF_DS_Msk (0x100000UL) /*!< QSPIC_SEC_HF_DS（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_TX_MD_Pos (18UL)       /*!< QSPIC_BRK_TX_MD（第18位）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_TX_MD_Msk (0xc0000UL)  /*!< QSPIC_BRK_TX_MD（位域掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_SZ_Pos (17UL)          /*!< QSPIC_BRK_SZ（位17）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_SZ_Msk (0x20000UL)     /*!< QSPIC_BRK_SZ（位域掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_EN_Pos (16UL)          /*!< QSPIC_BRK_EN（位16）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_EN_Msk (0x10000UL)     /*!< QSPIC_BRK_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_WRD_Pos (0UL)          /*!< QSPIC_BRK_WRD（位0）*/
#define QSPIC2_QSPIC2_BURSTBRK_REG_QSPIC_BRK_WRD_Msk (0xffffUL)     /*!< QSPIC_BRK_WRD（位字段掩码：0xffff）*/
/* =================================================  QSPIC2_BURSTCMDA_REG  ================================================== */
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_DMY_TX_MD_Pos (30UL)      /*!< QSPIC_DMY_TX_MD（位30）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_DMY_TX_MD_Msk (0xc0000000UL) /*!< QSPIC_DMY_TX_MD（位域掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_EXT_TX_MD_Pos (28UL)      /*!< QSPIC_EXT_TX_MD（第28位）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_EXT_TX_MD_Msk (0x30000000UL) /*!< QSPIC_EXT_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_ADR_TX_MD_Pos (26UL)      /*!< QSPIC_ADR_TX_MD（位26）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_ADR_TX_MD_Msk (0xc000000UL) /*!< QSPIC_ADR_TX_MD（位域掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_INST_TX_MD_Pos (24UL)     /*!< QSPIC_INST_TX_MD（第24位）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_INST_TX_MD_Msk (0x3000000UL) /*!< QSPIC_INST_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_EXT_BYTE_Pos (16UL)       /*!< QSPIC_EXT_BYTE（位16）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_EXT_BYTE_Msk (0xff0000UL) /*!< QSPIC_EXT_BYTE（位字段掩码：0xff）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_INST_WB_Pos (8UL)         /*!< QSPIC_INST_WB（位8）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_INST_WB_Msk (0xff00UL)    /*!< QSPIC_INST_WB（位字段掩码：0xff）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_INST_Pos (0UL)            /*!< QSPIC_INST（位0）*/
#define QSPIC2_QSPIC2_BURSTCMDA_REG_QSPIC_INST_Msk (0xffUL)         /*!< QSPIC_INST（位字段掩码：0xff）*/
/* =================================================  QSPIC2_BURSTCMDB_REG  ================================================== */
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_DMY_FORCE_Pos (15UL)      /*!< QSPIC_DMY_FORCE（位15）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_DMY_FORCE_Msk (0x8000UL)  /*!< QSPIC_DMY_FORCE（位域掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_CS_HIGH_MIN_Pos (12UL)    /*!< QSPIC_CS_HIGH_MIN（位12）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_CS_HIGH_MIN_Msk (0x7000UL) /*!< QSPIC_CS_HIGH_MIN（位域掩码：0x07）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_WRAP_SIZE_Pos (10UL)      /*!< QSPIC_WRAP_SIZE（位10）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_WRAP_SIZE_Msk (0xc00UL)   /*!< QSPIC_WRAP_SIZE（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_WRAP_LEN_Pos (8UL)        /*!< QSPIC_WRAP_LEN（位8）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_WRAP_LEN_Msk (0x300UL)    /*!< QSPIC_WRAP_LEN（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_WRAP_MD_Pos (7UL)         /*!< QSPIC_WRAP_MD（第7位）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_WRAP_MD_Msk (0x80UL)      /*!< QSPIC_WRAP_MD（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_INST_MD_Pos (6UL)         /*!< QSPIC_INST_MD（位6）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_INST_MD_Msk (0x40UL)      /*!< QSPIC_INST_MD（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_DMY_NUM_Pos (4UL)         /*!< QSPIC_DMY_NUM（位4）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_DMY_NUM_Msk (0x30UL)      /*!< QSPIC_DMY_NUM（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_EXT_HF_DS_Pos (3UL)       /*!< QSPIC_EXT_HF_DS（位3）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_EXT_HF_DS_Msk (0x8UL)     /*!< QSPIC_EXT_HF_DS（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_EXT_BYTE_EN_Pos (2UL)     /*!< QSPIC_EXT_BYTE_EN（位2）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_EXT_BYTE_EN_Msk (0x4UL)   /*!< QSPIC_EXT_BYTE_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_DAT_RX_MD_Pos (0UL)       /*!< QSPIC_DAT_RX_MD（位0）*/
#define QSPIC2_QSPIC2_BURSTCMDB_REG_QSPIC_DAT_RX_MD_Msk (0x3UL)     /*!< QSPIC_DAT_RX_MD（位字段掩码：0x03）*/
/* =================================================  QSPIC2_CHCKERASE_REG  ================================================== */
#define QSPIC2_QSPIC2_CHCKERASE_REG_QSPIC_CHCKERASE_Pos (0UL)       /*!< QSPIC_CHCKERASE（位0）*/
#define QSPIC2_QSPIC2_CHCKERASE_REG_QSPIC_CHCKERASE_Msk (0xffffffffUL) /*!< QSPIC_CHCKERASE（位域掩码：0xffffffff）*/
/* ==================================================  QSPIC2_CTRLBUS_REG  =================================================== */
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_DIS_CS_Pos (4UL)            /*!< QSPIC_DIS_CS（位4）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_DIS_CS_Msk (0x10UL)         /*!< QSPIC_DIS_CS（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_EN_CS_Pos (3UL)             /*!< QSPIC_EN_CS（位3）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_EN_CS_Msk (0x8UL)           /*!< QSPIC_EN_CS（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_SET_QUAD_Pos (2UL)          /*!< QSPIC_SET_QUAD（位2）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_SET_QUAD_Msk (0x4UL)        /*!< QSPIC_SET_QUAD（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_SET_DUAL_Pos (1UL)          /*!< QSPIC_SET_DUAL（位1）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_SET_DUAL_Msk (0x2UL)        /*!< QSPIC_SET_DUAL（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_SET_SINGLE_Pos (0UL)        /*!< QSPIC_SET_SINGLE（位0）*/
#define QSPIC2_QSPIC2_CTRLBUS_REG_QSPIC_SET_SINGLE_Msk (0x1UL)      /*!< QSPIC_SET_SINGLE（位字段掩码：0x01）*/
/* ==================================================  QSPIC2_CTRLMODE_REG  ================================================== */
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_CLK_FREE_EN_Pos (16UL)     /*!< QSPIC_CLK_FREE_EN（第16位）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_CLK_FREE_EN_Msk (0x10000UL) /*!< QSPIC_CLK_FREE_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_CS_MD_Pos (15UL)           /*!< QSPIC_CS_MD（位15）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_CS_MD_Msk (0x8000UL)       /*!< QSPIC_CS_MD（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_SRAM_EN_Pos (14UL)         /*!< QSPIC_SRAM_EN（位14）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_SRAM_EN_Msk (0x4000UL)     /*!< QSPIC_SRAM_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_USE_32BA_Pos (13UL)        /*!< QSPIC_USE_32BA（第13位）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_USE_32BA_Msk (0x2000UL)    /*!< QSPIC_USE_32BA（位域掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_FORCENSEQ_EN_Pos (12UL)    /*!< QSPIC_FORCENEQ_EN（位12）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_FORCENSEQ_EN_Msk (0x1000UL) /*!< QSPIC_FORCENEQ_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_PCLK_MD_Pos (9UL)          /*!< QSPIC_PCLK_MD（位9）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_PCLK_MD_Msk (0xe00UL)      /*!< QSPIC_PCLK_MD（位字段掩码：0x07）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_RPIPE_EN_Pos (8UL)         /*!< QSPIC_RPIPE_EN（位8）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_RPIPE_EN_Msk (0x100UL)     /*!< QSPIC_RPIPE_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_RXD_NEG_Pos (7UL)          /*!< QSPIC_RXD_NEG（位7）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_RXD_NEG_Msk (0x80UL)       /*!< QSPIC_RXD_NEG（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_HRDY_MD_Pos (6UL)          /*!< QSPIC_HRDY_MD（位6）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_HRDY_MD_Msk (0x40UL)       /*!< QSPIC_HRDY_MD（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO3_DAT_Pos (5UL)          /*!< QSPIC_IO3_DAT（位5）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO3_DAT_Msk (0x20UL)       /*!< QSPIC_IO3_DAT（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO2_DAT_Pos (4UL)          /*!< QSPIC_IO2_DAT（位4）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO2_DAT_Msk (0x10UL)       /*!< QSPIC_IO2_DAT（位域掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO3_OEN_Pos (3UL)          /*!< QSPIC_IO3_OEN（位3）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO3_OEN_Msk (0x8UL)        /*!< QSPIC_IO3_OEN（位域掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO2_OEN_Pos (2UL)          /*!< QSPIC_IO2_OEN（位2）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_IO2_OEN_Msk (0x4UL)        /*!< QSPIC_IO2_OEN（位域掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_CLK_MD_Pos (1UL)           /*!< QSPIC_CLK_MD（位1）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_CLK_MD_Msk (0x2UL)         /*!< QSPIC_CLK_MD（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_AUTO_MD_Pos (0UL)          /*!< QSPIC_AUTO_MD（位0）*/
#define QSPIC2_QSPIC2_CTRLMODE_REG_QSPIC_AUTO_MD_Msk (0x1UL)        /*!< QSPIC_AUTO_MD（位域掩码：0x01）*/
/* =================================================  QSPIC2_DUMMYDATA_REG  ================================================== */
#define QSPIC2_QSPIC2_DUMMYDATA_REG_QSPIC_DUMMYDATA_Pos (0UL)       /*!< QSPIC_DUMMYDATA（位0）*/
#define QSPIC2_QSPIC2_DUMMYDATA_REG_QSPIC_DUMMYDATA_Msk (0xffffffffUL) /*!< QSPIC_DUMMYDATA（位字段掩码：0xffffff）*/
/* =================================================  QSPIC2_ERASECMDA_REG  ================================================== */
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_RES_INST_Pos (24UL)       /*!< QSPIC_RES_INST（位24）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_RES_INST_Msk (0xff000000UL) /*!< QSPIC_RES_INST（位字段掩码：0xff）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_SUS_INST_Pos (16UL)       /*!< QSPIC_SUS_INST（位16）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_SUS_INST_Msk (0xff0000UL) /*!< QSPIC_SUS_INST（位字段掩码：0xff）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_WEN_INST_Pos (8UL)        /*!< QSPIC_WEN_INST（位8）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_WEN_INST_Msk (0xff00UL)   /*!< QSPIC_WEN_INST（位字段掩码：0xff）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_ERS_INST_Pos (0UL)        /*!< QSPIC_ERS_INST（位0）*/
#define QSPIC2_QSPIC2_ERASECMDA_REG_QSPIC_ERS_INST_Msk (0xffUL)     /*!< QSPIC_ERS_INST（位字段掩码：0xff）*/
/* =================================================  QSPIC2_ERASECMDB_REG  ================================================== */
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_RESSUS_DLY_Pos (24UL)     /*!< QSPIC_RESSUS_DLY（位24）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_RESSUS_DLY_Msk (0x3f000000UL) /*!< QSPIC_RESSUS_DLY（位字段掩码：0x3f）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_ERSRES_HLD_Pos (16UL)     /*!< QSPIC_ERSRES_HLD（位16）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_ERSRES_HLD_Msk (0xf0000UL) /*!< QSPIC_ERSRES_HLD（位字段掩码：0x0f）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_ERS_CS_HI_Pos (10UL)      /*!< QSPIC_ERS_CS_HI（位10）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_ERS_CS_HI_Msk (0x7c00UL)  /*!< QSPIC_ERS_CS_HI（位字段掩码：0x1f）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_EAD_TX_MD_Pos (8UL)       /*!< QSPIC_EAD_TX_MD（位8）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_EAD_TX_MD_Msk (0x300UL)   /*!< QSPIC_EAD_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_RES_TX_MD_Pos (6UL)       /*!< QSPIC_RES_TX_MD（位6）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_RES_TX_MD_Msk (0xc0UL)    /*!< QSPIC_RES_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_SUS_TX_MD_Pos (4UL)       /*!< QSPIC_SUS_TX_MD（位4）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_SUS_TX_MD_Msk (0x30UL)    /*!< QSPIC_SUS_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_WEN_TX_MD_Pos (2UL)       /*!< QSPIC_WEN_TX_MD（位2）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_WEN_TX_MD_Msk (0xcUL)     /*!< QSPIC_WEN_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_ERS_TX_MD_Pos (0UL)       /*!< QSPIC_ERS_TX_MD（位0）*/
#define QSPIC2_QSPIC2_ERASECMDB_REG_QSPIC_ERS_TX_MD_Msk (0x3UL)     /*!< QSPIC_ERS_TX_MD（位字段掩码：0x03）*/
/* =================================================  QSPIC2_ERASECTRL_REG  ================================================== */
#define QSPIC2_QSPIC2_ERASECTRL_REG_QSPIC_ERS_STATE_Pos (25UL)      /*!< QSPIC_ERS_STATE（位25）*/
#define QSPIC2_QSPIC2_ERASECTRL_REG_QSPIC_ERS_STATE_Msk (0xe000000UL) /*!< QSPIC_ERS_STATE（位字段掩码：0x07）*/
#define QSPIC2_QSPIC2_ERASECTRL_REG_QSPIC_ERASE_EN_Pos (24UL)       /*!< QSPIC_ERASE_EN（位24）*/
#define QSPIC2_QSPIC2_ERASECTRL_REG_QSPIC_ERASE_EN_Msk (0x1000000UL) /*!< QSPIC_ERASE_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_ERASECTRL_REG_QSPIC_ERS_ADDR_Pos (4UL)        /*!< QSPIC_ERS_ADDR（位4）*/
#define QSPIC2_QSPIC2_ERASECTRL_REG_QSPIC_ERS_ADDR_Msk (0xfffff0UL) /*!< QSPIC_ERS_ADDR（位字段掩码：0xfffff）*/
/* =====================================================  QSPIC2_GP_REG  ===================================================== */
#define QSPIC2_QSPIC2_GP_REG_QSPIC_PADS_SLEW_Pos (3UL)              /*!< QSPIC_PADS_SLEW（位3）*/
#define QSPIC2_QSPIC2_GP_REG_QSPIC_PADS_SLEW_Msk (0x18UL)           /*!< QSPIC_PADS_SLEW（位域掩码：0x03）*/
#define QSPIC2_QSPIC2_GP_REG_QSPIC_PADS_DRV_Pos (1UL)               /*!< QSPIC_PADS_DRV（位1）*/
#define QSPIC2_QSPIC2_GP_REG_QSPIC_PADS_DRV_Msk (0x6UL)             /*!< QSPIC_PADS_DRV（位字段掩码：0x03）*/
/* ==================================================  QSPIC2_MEMBLEN_REG  =================================================== */
#define QSPIC2_QSPIC2_MEMBLEN_REG_QSPIC_T_CEM_CC_Pos (4UL)          /*!< QSPIC_T_CEM_CC（位4）*/
#define QSPIC2_QSPIC2_MEMBLEN_REG_QSPIC_T_CEM_CC_Msk (0x3ff0UL)     /*!< QSPIC_T_CEM_CC（位域掩码：0x3ff）*/
#define QSPIC2_QSPIC2_MEMBLEN_REG_QSPIC_T_CEM_EN_Pos (3UL)          /*!< QSPIC_T_CEM_EN（位3）*/
#define QSPIC2_QSPIC2_MEMBLEN_REG_QSPIC_T_CEM_EN_Msk (0x8UL)        /*!< QSPIC_T_CEM_EN（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_MEMBLEN_REG_QSPIC_MEMBLEN_Pos (0UL)           /*!< QSPIC_MEMBLEN（位0）*/
#define QSPIC2_QSPIC2_MEMBLEN_REG_QSPIC_MEMBLEN_Msk (0x7UL)         /*!< QSPIC_MEMBLEN（位字段掩码：0x07）*/
/* ==================================================  QSPIC2_READDATA_REG  ================================================== */
#define QSPIC2_QSPIC2_READDATA_REG_QSPIC_READDATA_Pos (0UL)         /*!< QSPIC_READDATA（位0）*/
#define QSPIC2_QSPIC2_READDATA_REG_QSPIC_READDATA_Msk (0xffffffffUL) /*!< QSPIC_READDATA（位字段掩码：0xffffffff）*/
/* ==================================================  QSPIC2_RECVDATA_REG  ================================================== */
#define QSPIC2_QSPIC2_RECVDATA_REG_QSPIC_RECVDATA_Pos (0UL)         /*!< QSPIC_RECVDATA（位0）*/
#define QSPIC2_QSPIC2_RECVDATA_REG_QSPIC_RECVDATA_Msk (0xffffffffUL) /*!< QSPIC_RECVDATA（位字段掩码：0xffffffff）*/
/* =================================================  QSPIC2_STATUSCMD_REG  ================================================== */
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_STSDLY_SEL_Pos (22UL)     /*!< QSPIC_STSDLY_SEL（位22）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_STSDLY_SEL_Msk (0x400000UL) /*!< QSPIC_STSDLY_SEL（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RESSTS_DLY_Pos (16UL)     /*!< QSPIC_RESSTS_DLY（位16）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RESSTS_DLY_Msk (0x3f0000UL) /*!< QSPIC_RESSTS_DLY（位字段掩码：0x3f）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_BUSY_VAL_Pos (15UL)       /*!< QSPIC_BUSY_VAL（第15位）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_BUSY_VAL_Msk (0x8000UL)   /*!< QSPIC_BUSY_VAL（位字段掩码：0x01）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_BUSY_POS_Pos (12UL)       /*!< QSPIC_BUSY_POS（位12）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_BUSY_POS_Msk (0x7000UL)   /*!< QSPIC_BUSY_POS（位字段掩码：0x07）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RSTAT_RX_MD_Pos (10UL)    /*!< QSPIC_RSTAT_RX_MD（位10）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RSTAT_RX_MD_Msk (0xc00UL) /*!< QSPIC_RSTAT_RX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RSTAT_TX_MD_Pos (8UL)     /*!< QSPIC_RSTAT_TX_MD（位8）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RSTAT_TX_MD_Msk (0x300UL) /*!< QSPIC_RSTAT_TX_MD（位字段掩码：0x03）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RSTAT_INST_Pos (0UL)      /*!< QSPIC_RSTAT_INST（位0）*/
#define QSPIC2_QSPIC2_STATUSCMD_REG_QSPIC_RSTAT_INST_Msk (0xffUL)   /*!< QSPIC_RSTAT_INST（位字段掩码：0xff）*/
/* ===================================================  QSPIC2_STATUS_REG  =================================================== */
#define QSPIC2_QSPIC2_STATUS_REG_QSPIC_BUSY_Pos (0UL)               /*!< QSPIC_BUSY（位0）*/
#define QSPIC2_QSPIC2_STATUS_REG_QSPIC_BUSY_Msk (0x1UL)             /*!< QSPIC_BUSY（位字段掩码：0x01）*/
/* =================================================  QSPIC2_WRITEDATA_REG  ================================================== */
#define QSPIC2_QSPIC2_WRITEDATA_REG_QSPIC_WRITEDATA_Pos (0UL)       /*!< QSPIC_WRITEDATA（位0）*/
#define QSPIC2_QSPIC2_WRITEDATA_REG_QSPIC_WRITEDATA_Msk (0xffffffffUL) /*!< QSPIC_WRITEDATA（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                           RFMON                                           ================ */
/* =========================================================================================================================== */

/* ====================================================  RFMON_ADDR_REG  ===================================================== */
#define RFMON_RFMON_ADDR_REG_RFMON_ADDR_Pos (2UL)                   /*!< RFMON_ADDR（位2）*/
#define RFMON_RFMON_ADDR_REG_RFMON_ADDR_Msk (0xfffffffcUL)          /*!< RFMON_ADDR（位域掩码：0x3fffffff）*/
/* ==================================================  RFMON_CRV_ADDR_REG  =================================================== */
#define RFMON_RFMON_CRV_ADDR_REG_RFMON_CRV_ADDR_Pos (2UL)           /*!< RFMON_CRV_ADDR（位2）*/
#define RFMON_RFMON_CRV_ADDR_REG_RFMON_CRV_ADDR_Msk (0xfffffffcUL)  /*!< RFMON_CRV_ADDR（位域掩码：0x3fffffff）*/
/* ===================================================  RFMON_CRV_LEN_REG  =================================================== */
#define RFMON_RFMON_CRV_LEN_REG_RFMON_CRV_LEN_Pos (0UL)             /*!< RFMON_CRV_LEN（位0）*/
#define RFMON_RFMON_CRV_LEN_REG_RFMON_CRV_LEN_Msk (0x1ffffUL)       /*!< RFMON_CRV_LEN（位域掩码：0x1ffff）*/
/* ====================================================  RFMON_CTRL_REG  ===================================================== */
#define RFMON_RFMON_CTRL_REG_RFMON_BREQ_FORCE_Pos (2UL)             /*!< RFMON_BREQ_FORCE（位2）*/
#define RFMON_RFMON_CTRL_REG_RFMON_BREQ_FORCE_Msk (0x4UL)           /*!< RFMON_BREQ_FORCE（位域掩码：0x01）*/
#define RFMON_RFMON_CTRL_REG_RFMON_CIRC_EN_Pos (1UL)                /*!< RFMON_CIRC_EN（位1）*/
#define RFMON_RFMON_CTRL_REG_RFMON_CIRC_EN_Msk (0x2UL)              /*!< RFMON_CIRC_EN（位域掩码：0x01）*/
#define RFMON_RFMON_CTRL_REG_RFMON_PACK_EN_Pos (0UL)                /*!< RFMON_PACK_EN（位0）*/
#define RFMON_RFMON_CTRL_REG_RFMON_PACK_EN_Msk (0x1UL)              /*!< RFMON_PACK_EN（位字段掩码：0x01）*/
/* =====================================================  RFMON_LEN_REG  ===================================================== */
#define RFMON_RFMON_LEN_REG_RFMON_LEN_Pos (0UL)                     /*!< RFMON_LEN（位0）*/
#define RFMON_RFMON_LEN_REG_RFMON_LEN_Msk (0x1ffffUL)               /*!< RFMON_LEN（位场掩码：0x1ffff）*/
/* ====================================================  RFMON_STAT_REG  ===================================================== */
#define RFMON_RFMON_STAT_REG_RFMON_OFLOW_STK_Pos (1UL)              /*!< RFMON_OFLOW_STK（位1）*/
#define RFMON_RFMON_STAT_REG_RFMON_OFLOW_STK_Msk (0x2UL)            /*!< RFMON_OFLOW_STK（位字段掩码：0x01）*/
#define RFMON_RFMON_STAT_REG_RFMON_ACTIVE_Pos (0UL)                 /*!< RFMON_ACTIVE（位0）*/
#define RFMON_RFMON_STAT_REG_RFMON_ACTIVE_Msk (0x1UL)               /*!< RFMON_ACTIVE（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */

/* =================================================  RTC_ALARM_ENABLE_REG  ================================================== */
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_MNTH_EN_Pos (5UL)        /*!< RTC_ALARM_MNTH_EN（第5位）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_MNTH_EN_Msk (0x20UL)     /*!< RTC_ALARM_MNTH_EN（位字段掩码：0x01）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_DATE_EN_Pos (4UL)        /*!< RTC_ALARM_DATE_EN（位4）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_DATE_EN_Msk (0x10UL)     /*!< RTC_ALARM_DATE_EN（位字段掩码：0x01）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_HOUR_EN_Pos (3UL)        /*!< RTC_ALARM_HOUR_EN（位3）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_HOUR_EN_Msk (0x8UL)      /*!< RTC_ALARM_HOUR_EN（位字段掩码：0x01）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_MIN_EN_Pos (2UL)         /*!< RTC_ALARM_MIN_EN（位2）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_MIN_EN_Msk (0x4UL)       /*!< RTC_ALARM_MIN_EN（位字段掩码：0x01）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_SEC_EN_Pos (1UL)         /*!< RTC_ALARM_SEC_EN（位1）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_SEC_EN_Msk (0x2UL)       /*!< RTC_ALARM_SEC_EN（位字段掩码：0x01）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_HOS_EN_Pos (0UL)         /*!< RTC_ALARM_HOS_EN（位0）*/
#define RTC_RTC_ALARM_ENABLE_REG_RTC_ALARM_HOS_EN_Msk (0x1UL)       /*!< RTC_ALARM_HOS_EN（位字段掩码：0x01）*/
/* ================================================  RTC_CALENDAR_ALARM_REG  ================================================= */
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_D_T_Pos (12UL)           /*!< RTC_CAL_D_T（第12位）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_D_T_Msk (0x3000UL)       /*!< RTC_CAL_D_T（位字段掩码：0x03）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_D_U_Pos (8UL)            /*!< RTC_CAL_D_U（位8）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_D_U_Msk (0xf00UL)        /*!< RTC_CAL_D_U（位字段掩码：0x0f）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_M_T_Pos (7UL)            /*!< RTC_CAL_M_T（第7位）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_M_T_Msk (0x80UL)         /*!< RTC_CAL_M_T（位字段掩码：0x01）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_M_U_Pos (3UL)            /*!< RTC_CAL_M_U（位3）*/
#define RTC_RTC_CALENDAR_ALARM_REG_RTC_CAL_M_U_Msk (0x78UL)         /*!< RTC_CAL_M_U（位字段掩码：0x0f）*/
/* ===================================================  RTC_CALENDAR_REG  ==================================================== */
#define RTC_RTC_CALENDAR_REG_RTC_CAL_CH_Pos (31UL)                  /*!< RTC_CAL_CH（第31位）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_CH_Msk (0x80000000UL)          /*!< RTC_CAL_CH（位字段掩码：0x01）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_C_T_Pos (28UL)                 /*!< RTC_CAL_C_T（第28位）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_C_T_Msk (0x30000000UL)         /*!< RTC_CAL_C_T（位字段掩码：0x03）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_C_U_Pos (24UL)                 /*!< RTC_CAL_C_U（位24）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_C_U_Msk (0xf000000UL)          /*!< RTC_CAL_C_U（位字段掩码：0x0f）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_Y_T_Pos (20UL)                 /*!< RTC_CAL_Y_T（第20位）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_Y_T_Msk (0xf00000UL)           /*!< RTC_CAL_Y_T（位字段掩码：0x0f）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_Y_U_Pos (16UL)                 /*!< RTC_CAL_Y_U（位16）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_Y_U_Msk (0xf0000UL)            /*!< RTC_CAL_Y_U（位字段掩码：0x0f）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_D_T_Pos (12UL)                 /*!< RTC_CAL_D_T（第12位）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_D_T_Msk (0x3000UL)             /*!< RTC_CAL_D_T（位字段掩码：0x03）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_D_U_Pos (8UL)                  /*!< RTC_CAL_D_U（位8）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_D_U_Msk (0xf00UL)              /*!< RTC_CAL_D_U（位字段掩码：0x0f）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_M_T_Pos (7UL)                  /*!< RTC_CAL_M_T（第7位）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_M_T_Msk (0x80UL)               /*!< RTC_CAL_M_T（位字段掩码：0x01）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_M_U_Pos (3UL)                  /*!< RTC_CAL_M_U（位3）*/
#define RTC_RTC_CALENDAR_REG_RTC_CAL_M_U_Msk (0x78UL)               /*!< RTC_CAL_M_U（位字段掩码：0x0f）*/
#define RTC_RTC_CALENDAR_REG_RTC_DAY_Pos  (0UL)                     /*!< RTC_DAY（位0）*/
#define RTC_RTC_CALENDAR_REG_RTC_DAY_Msk  (0x7UL)                   /*!< RTC_DAY（位字段掩码：0x07）*/
/* ====================================================  RTC_CONTROL_REG  ==================================================== */
#define RTC_RTC_CONTROL_REG_RTC_CAL_DISABLE_Pos (1UL)               /*!< RTC_CAL_DISABLE（位1）*/
#define RTC_RTC_CONTROL_REG_RTC_CAL_DISABLE_Msk (0x2UL)             /*!< RTC_CAL_DISABLE（位字段掩码：0x01）*/
#define RTC_RTC_CONTROL_REG_RTC_TIME_DISABLE_Pos (0UL)              /*!< RTC_TIME_DISABLE（位0）*/
#define RTC_RTC_CONTROL_REG_RTC_TIME_DISABLE_Msk (0x1UL)            /*!< RTC_TIME_DISABLE（位字段掩码：0x01）*/
/* ==================================================  RTC_EVENT_CTRL_REG  =================================================== */
#define RTC_RTC_EVENT_CTRL_REG_RTC_PDC_EVENT_EN_Pos (1UL)           /*!< RTC_PDC_EVENT_EN（位1）*/
#define RTC_RTC_EVENT_CTRL_REG_RTC_PDC_EVENT_EN_Msk (0x2UL)         /*!< RTC_PDC_EVENT_EN（位字段掩码：0x01）*/
#define RTC_RTC_EVENT_CTRL_REG_RTC_MOTOR_EVENT_EN_Pos (0UL)         /*!< RTC_MOTOR_EVENT_EN（位0）*/
#define RTC_RTC_EVENT_CTRL_REG_RTC_MOTOR_EVENT_EN_Msk (0x1UL)       /*!< RTC_MOTOR_EVENT_EN（位域掩码：0x01）*/
/* ==================================================  RTC_EVENT_FLAGS_REG  ================================================== */
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_ALRM_Pos (6UL)            /*!< RTC_EVENT_ALRM（位6）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_ALRM_Msk (0x40UL)         /*!< RTC_EVENT_ALRM（位字段掩码：0x01）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_MNTH_Pos (5UL)            /*!< RTC_EVENT_MMTH（第5位）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_MNTH_Msk (0x20UL)         /*!< RTC_EVENT_MNTH（位域掩码：0x01）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_DATE_Pos (4UL)            /*!< RTC_EVENT_DATE（位4）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_DATE_Msk (0x10UL)         /*!< RTC_EVENT_DATE（位字段掩码：0x01）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_HOUR_Pos (3UL)            /*!< RTC_EVENT_HOUR（位3）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_HOUR_Msk (0x8UL)          /*!< RTC_EVENT_HOUR（位字段掩码：0x01）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_MIN_Pos (2UL)             /*!< RTC_EVENT_MIN（位2）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_MIN_Msk (0x4UL)           /*!< RTC_EVENT_MIN（位域掩码：0x01）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_SEC_Pos (1UL)             /*!< RTC_EVENT_SEC（位1）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_SEC_Msk (0x2UL)           /*!< RTC_EVENT_SEC（位字段掩码：0x01）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_HOS_Pos (0UL)             /*!< RTC_EVENT_HOS（位0）*/
#define RTC_RTC_EVENT_FLAGS_REG_RTC_EVENT_HOS_Msk (0x1UL)           /*!< RTC_EVENT_HOS（位字段掩码：0x01）*/
/* ===================================================  RTC_HOUR_MODE_REG  =================================================== */
#define RTC_RTC_HOUR_MODE_REG_RTC_HMS_Pos (0UL)                     /*!< RTC_HMS（位0）*/
#define RTC_RTC_HOUR_MODE_REG_RTC_HMS_Msk (0x1UL)                   /*!< RTC_HMS（位域掩码：0x01）*/
/* ===============================================  RTC_INTERRUPT_DISABLE_REG  =============================================== */
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_ALRM_INT_DIS_Pos (6UL)    /*!< RTC_ALRM_INT_DIS（位6）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_ALRM_INT_DIS_Msk (0x40UL) /*!< RTC_ALRM_INT_DIS（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_MNTH_INT_DIS_Pos (5UL)    /*!< RTC_MNTH_INT_DIS（位5）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_MNTH_INT_DIS_Msk (0x20UL) /*!< RTC_MNTH_INT_DIS（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_DATE_INT_DIS_Pos (4UL)    /*!< RTC_DATE_INT_DIS（位4）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_DATE_INT_DIS_Msk (0x10UL) /*!< RTC_DATE_INT_DIS（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_HOUR_INT_DIS_Pos (3UL)    /*!< RTC_HOUR_INT_DIS（位3）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_HOUR_INT_DIS_Msk (0x8UL)  /*!< RTC_HOUR_INT_DIS（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_MIN_INT_DIS_Pos (2UL)     /*!< RTC_MIN_INT_DIS（位2）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_MIN_INT_DIS_Msk (0x4UL)   /*!< RTC_MIN_INT_DIS（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_SEC_INT_DIS_Pos (1UL)     /*!< RTC_SEC_INT_DIS（位1）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_SEC_INT_DIS_Msk (0x2UL)   /*!< RTC_SEC_INT_DIS（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_HOS_INT_DIS_Pos (0UL)     /*!< RTC_HOS_INT_DIS（位0）*/
#define RTC_RTC_INTERRUPT_DISABLE_REG_RTC_HOS_INT_DIS_Msk (0x1UL)   /*!< RTC_HOS_INT_DIS（位字段掩码：0x01）*/
/* ===============================================  RTC_INTERRUPT_ENABLE_REG  ================================================ */
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_ALRM_INT_EN_Pos (6UL)      /*!< RTC_ALRM_INT_EN（位6）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_ALRM_INT_EN_Msk (0x40UL)   /*!< RTC_ALRM_INT_EN（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_MNTH_INT_EN_Pos (5UL)      /*!< RTC_MNTH_INT_EN（位5）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_MNTH_INT_EN_Msk (0x20UL)   /*!< RTC_MNTH_INT_EN（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_DATE_INT_EN_Pos (4UL)      /*!< RTC_DATE_INT_EN（位4）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_DATE_INT_EN_Msk (0x10UL)   /*!< RTC_DATE_INT_EN（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_HOUR_INT_EN_Pos (3UL)      /*!< RTC_HOUR_INT_EN（位3）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_HOUR_INT_EN_Msk (0x8UL)    /*!< RTC_HOUR_INT_EN（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_MIN_INT_EN_Pos (2UL)       /*!< RTC_MIN_INT_EN（位2）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_MIN_INT_EN_Msk (0x4UL)     /*!< RTC_MIN_INT_EN（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_SEC_INT_EN_Pos (1UL)       /*!< RTC_SEC_INT_EN（位1）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_SEC_INT_EN_Msk (0x2UL)     /*!< RTC_SEC_INT_EN（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_HOS_INT_EN_Pos (0UL)       /*!< RTC_HOS_INT_EN（位0）*/
#define RTC_RTC_INTERRUPT_ENABLE_REG_RTC_HOS_INT_EN_Msk (0x1UL)     /*!< RTC_HOS_INT_EN（位字段掩码：0x01）*/
/* ================================================  RTC_INTERRUPT_MASK_REG  ================================================= */
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_ALRM_INT_MSK_Pos (6UL)       /*!< RTC_ALRM_INT_MSK（位6）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_ALRM_INT_MSK_Msk (0x40UL)    /*!< RTC_ALRM_INT_MSK（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_MNTH_INT_MSK_Pos (5UL)       /*!< RTC_MNTH_INT_MSK（位5）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_MNTH_INT_MSK_Msk (0x20UL)    /*!< RTC_MNTH_INT_MSK（位域掩码：0x01）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_DATE_INT_MSK_Pos (4UL)       /*!< RTC_DATE_INT_MSK（位4）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_DATE_INT_MSK_Msk (0x10UL)    /*!< RTC_DATE_INT_MSK（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_HOUR_INT_MSK_Pos (3UL)       /*!< RTC_HOUR_INT_MSK（位3）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_HOUR_INT_MSK_Msk (0x8UL)     /*!< RTC_HOUR_INT_MSK（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_MIN_INT_MSK_Pos (2UL)        /*!< RTC_MIN_INT_MSK（位2）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_MIN_INT_MSK_Msk (0x4UL)      /*!< RTC_MIN_INT_MSK（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_SEC_INT_MSK_Pos (1UL)        /*!< RTC_SEC_INT_MSK（位1）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_SEC_INT_MSK_Msk (0x2UL)      /*!< RTC_SEC_INT_MSK（位字段掩码：0x01）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_HOS_INT_MSK_Pos (0UL)        /*!< RTC_HOS_INT_MSK（位0）*/
#define RTC_RTC_INTERRUPT_MASK_REG_RTC_HOS_INT_MSK_Msk (0x1UL)      /*!< RTC_HOS_INT_MSK（位字段掩码：0x01）*/
/* ===================================================  RTC_KEEP_RTC_REG  ==================================================== */
#define RTC_RTC_KEEP_RTC_REG_RTC_KEEP_Pos (0UL)                     /*!< RTC_KEEP（位0）*/
#define RTC_RTC_KEEP_RTC_REG_RTC_KEEP_Msk (0x1UL)                   /*!< RTC_KEEP（位字段掩码：0x01）*/
/* ================================================  RTC_MOTOR_EVENT_CNT_REG  ================================================ */
#define RTC_RTC_MOTOR_EVENT_CNT_REG_RTC_MOTOR_EVENT_CNT_Pos (0UL)   /*!< RTC_MOTOR_EVENT_CNT（位0）*/
#define RTC_RTC_MOTOR_EVENT_CNT_REG_RTC_MOTOR_EVENT_CNT_Msk (0xfffUL) /*!< RTC_MOTOR_EVENT_CNT（位域掩码：0xfff）*/
/* ==============================================  RTC_MOTOR_EVENT_PERIOD_REG  =============================================== */
#define RTC_RTC_MOTOR_EVENT_PERIOD_REG_RTC_MOTOR_EVENT_PERIOD_Pos (0UL) /*!< RTC_MOTOR_EVENT_PERIOD（位0）*/
#define RTC_RTC_MOTOR_EVENT_PERIOD_REG_RTC_MOTOR_EVENT_PERIOD_Msk (0xfffUL) /*!< RTC_MOTOR_EVENT_PERIOD（位域掩码：0xfff）*/
/* ================================================  RTC_PDC_EVENT_CLEAR_REG  ================================================ */
#define RTC_RTC_PDC_EVENT_CLEAR_REG_PDC_EVENT_CLEAR_Pos (0UL)       /*!< PDC_EVENT_CLEAR（位0）*/
#define RTC_RTC_PDC_EVENT_CLEAR_REG_PDC_EVENT_CLEAR_Msk (0x1UL)     /*!< PDC_EVENT_CLEAR（位字段掩码：0x01）*/
/* =================================================  RTC_PDC_EVENT_CNT_REG  ================================================= */
#define RTC_RTC_PDC_EVENT_CNT_REG_RTC_PDC_EVENT_CNT_Pos (0UL)       /*!< RTC_PDC_EVENT_CNT（位0）*/
#define RTC_RTC_PDC_EVENT_CNT_REG_RTC_PDC_EVENT_CNT_Msk (0x1fffUL)  /*!< RTC_PDC_EVENT_CNT（位域掩码：0x1fff）*/
/* ===============================================  RTC_PDC_EVENT_PERIOD_REG  ================================================ */
#define RTC_RTC_PDC_EVENT_PERIOD_REG_RTC_PDC_EVENT_PERIOD_Pos (0UL) /*!< RTC_PDC_EVENT_PERIOD（位0）*/
#define RTC_RTC_PDC_EVENT_PERIOD_REG_RTC_PDC_EVENT_PERIOD_Msk (0x1fffUL) /*!< RTC_PDC_EVENT_PERIOD（位域掩码：0x1fff）*/
/* ====================================================  RTC_STATUS_REG  ===================================================== */
#define RTC_RTC_STATUS_REG_RTC_VALID_CAL_ALM_Pos (3UL)              /*!< RTC_VALID_CAL_ALM（位3）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_CAL_ALM_Msk (0x8UL)            /*!< RTC_VALID_CAL_ALM（位字段掩码：0x01）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_TIME_ALM_Pos (2UL)             /*!< RTC_VALID_TIME_ALM（位2）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_TIME_ALM_Msk (0x4UL)           /*!< RTC_VALID_TIME_ALM（位字段掩码：0x01）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_CAL_Pos (1UL)                  /*!< RTC_VALID_CAL（位1）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_CAL_Msk (0x2UL)                /*!< RTC_VALID_CAL（位字段掩码：0x01）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_TIME_Pos (0UL)                 /*!< RTC_VALID_TIME（位0）*/
#define RTC_RTC_STATUS_REG_RTC_VALID_TIME_Msk (0x1UL)               /*!< RTC_VALID_TIME（位字段掩码：0x01）*/
/* ==================================================  RTC_TIME_ALARM_REG  =================================================== */
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_PM_Pos (30UL)               /*!< RTC_TIME_PM（位30）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_PM_Msk (0x40000000UL)       /*!< RTC_TIME_PM（位字段掩码：0x01）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_HR_T_Pos (28UL)             /*!< RTC_TIME_HR_T（位28）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_HR_T_Msk (0x30000000UL)     /*!< RTC_TIME_HR_T（位字段掩码：0x03）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_HR_U_Pos (24UL)             /*!< RTC_TIME_HR_U（位24）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_HR_U_Msk (0xf000000UL)      /*!< RTC_TIME_HR_U（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_M_T_Pos (20UL)              /*!< RTC_TIME_M_T（位20）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_M_T_Msk (0x700000UL)        /*!< RTC_TIME_M_T（位字段掩码：0x07）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_M_U_Pos (16UL)              /*!< RTC_TIME_M_U（位16）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_M_U_Msk (0xf0000UL)         /*!< RTC_TIME_M_U（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_S_T_Pos (12UL)              /*!< RTC_TIME_S_T（位12）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_S_T_Msk (0x7000UL)          /*!< RTC_TIME_S_T（位字段掩码：0x07）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_S_U_Pos (8UL)               /*!< RTC_TIME_S_U（位8）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_S_U_Msk (0xf00UL)           /*!< RTC_TIME_S_U（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_H_T_Pos (4UL)               /*!< RTC_TIME_H_T（位4）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_H_T_Msk (0xf0UL)            /*!< RTC_TIME_H_T（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_H_U_Pos (0UL)               /*!< RTC_TIME_H_U（位0）*/
#define RTC_RTC_TIME_ALARM_REG_RTC_TIME_H_U_Msk (0xfUL)             /*!< RTC_TIME_H_U（位字段掩码：0x0f）*/
/* =====================================================  RTC_TIME_REG  ====================================================== */
#define RTC_RTC_TIME_REG_RTC_TIME_CH_Pos  (31UL)                    /*!< RTC_TIME_CH（位31）*/
#define RTC_RTC_TIME_REG_RTC_TIME_CH_Msk  (0x80000000UL)            /*!< RTC_TIME_CH（位字段掩码：0x01）*/
#define RTC_RTC_TIME_REG_RTC_TIME_PM_Pos  (30UL)                    /*!< RTC_TIME_PM（位30）*/
#define RTC_RTC_TIME_REG_RTC_TIME_PM_Msk  (0x40000000UL)            /*!< RTC_TIME_PM（位字段掩码：0x01）*/
#define RTC_RTC_TIME_REG_RTC_TIME_HR_T_Pos (28UL)                   /*!< RTC_TIME_HR_T（位28）*/
#define RTC_RTC_TIME_REG_RTC_TIME_HR_T_Msk (0x30000000UL)           /*!< RTC_TIME_HR_T（位字段掩码：0x03）*/
#define RTC_RTC_TIME_REG_RTC_TIME_HR_U_Pos (24UL)                   /*!< RTC_TIME_HR_U（位24）*/
#define RTC_RTC_TIME_REG_RTC_TIME_HR_U_Msk (0xf000000UL)            /*!< RTC_TIME_HR_U（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_REG_RTC_TIME_M_T_Pos (20UL)                    /*!< RTC_TIME_M_T（位20）*/
#define RTC_RTC_TIME_REG_RTC_TIME_M_T_Msk (0x700000UL)              /*!< RTC_TIME_M_T（位字段掩码：0x07）*/
#define RTC_RTC_TIME_REG_RTC_TIME_M_U_Pos (16UL)                    /*!< RTC_TIME_M_U（位16）*/
#define RTC_RTC_TIME_REG_RTC_TIME_M_U_Msk (0xf0000UL)               /*!< RTC_TIME_M_U（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_REG_RTC_TIME_S_T_Pos (12UL)                    /*!< RTC_TIME_S_T（位12）*/
#define RTC_RTC_TIME_REG_RTC_TIME_S_T_Msk (0x7000UL)                /*!< RTC_TIME_S_T（位字段掩码：0x07）*/
#define RTC_RTC_TIME_REG_RTC_TIME_S_U_Pos (8UL)                     /*!< RTC_TIME_S_U（位8）*/
#define RTC_RTC_TIME_REG_RTC_TIME_S_U_Msk (0xf00UL)                 /*!< RTC_TIME_S_U（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_REG_RTC_TIME_H_T_Pos (4UL)                     /*!< RTC_TIME_H_T（位4）*/
#define RTC_RTC_TIME_REG_RTC_TIME_H_T_Msk (0xf0UL)                  /*!< RTC_TIME_H_T（位字段掩码：0x0f）*/
#define RTC_RTC_TIME_REG_RTC_TIME_H_U_Pos (0UL)                     /*!< RTC_TIME_H_U（位0）*/
#define RTC_RTC_TIME_REG_RTC_TIME_H_U_Msk (0xfUL)                   /*!< RTC_TIME_H_U（位字段掩码：0x0f）*/


/* =========================================================================================================================== */
/* ================                                           SDADC                                           ================ */
/* =========================================================================================================================== */

/* ==================================================  SDADC_CLEAR_INT_REG  ================================================== */
#define SDADC_SDADC_CLEAR_INT_REG_SDADC_CLR_INT_Pos (0UL)           /*!< SDADC_CLR_INT（位0）*/
#define SDADC_SDADC_CLEAR_INT_REG_SDADC_CLR_INT_Msk (0xffffUL)      /*!< SDADC_CLR_INT（位字段掩码：0xffff）*/
/* ====================================================  SDADC_CTRL_REG  ===================================================== */
#define SDADC_SDADC_CTRL_REG_SDADC_DMA_EN_Pos (17UL)                /*!< SDADC_DMA_EN（位17）*/
#define SDADC_SDADC_CTRL_REG_SDADC_DMA_EN_Msk (0x20000UL)           /*!< SDADC_DMA_EN（位域掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_MINT_Pos (16UL)                  /*!< SDADC_MINT（位16）*/
#define SDADC_SDADC_CTRL_REG_SDADC_MINT_Msk (0x10000UL)             /*!< SDADC_MINT（位字段掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_INT_Pos (15UL)                   /*!< SDADC_INT（第15位）*/
#define SDADC_SDADC_CTRL_REG_SDADC_INT_Msk (0x8000UL)               /*!< SDADC_INT（位字段掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_LDO_OK_Pos (14UL)                /*!< SDADC_LDO_OK（位14）*/
#define SDADC_SDADC_CTRL_REG_SDADC_LDO_OK_Msk (0x4000UL)            /*!< SDADC_LDO_OK（位域掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_VREF_SEL_Pos (13UL)              /*!< SDADC_VREF_SEL（第13位）*/
#define SDADC_SDADC_CTRL_REG_SDADC_VREF_SEL_Msk (0x2000UL)          /*!< SDADC_VREF_SEL（位字段掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_CONT_Pos (12UL)                  /*!< SDADC_CONT（位12）*/
#define SDADC_SDADC_CTRL_REG_SDADC_CONT_Msk (0x1000UL)              /*!< SDADC_CONT（位域掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_OSR_Pos (10UL)                   /*!< SDADC_OSR（位10）*/
#define SDADC_SDADC_CTRL_REG_SDADC_OSR_Msk (0xc00UL)                /*!< SDADC_OSR（位域掩码：0x03）*/
#define SDADC_SDADC_CTRL_REG_SDADC_SE_Pos (9UL)                     /*!< SDADC_SE（位9）*/
#define SDADC_SDADC_CTRL_REG_SDADC_SE_Msk (0x200UL)                 /*!< SDADC_SE（位字段掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_INN_SEL_Pos (6UL)                /*!< SDADC_IN_SEL（位6）*/
#define SDADC_SDADC_CTRL_REG_SDADC_INN_SEL_Msk (0x1c0UL)            /*!< SDADC_IN_SEL（位字段掩码：0x07）*/
#define SDADC_SDADC_CTRL_REG_SDADC_INP_SEL_Pos (2UL)                /*!< SDADC_INP_SEL（位2）*/
#define SDADC_SDADC_CTRL_REG_SDADC_INP_SEL_Msk (0x3cUL)             /*!< SDADC_INP_SEL（位字段掩码：0x0f）*/
#define SDADC_SDADC_CTRL_REG_SDADC_START_Pos (1UL)                  /*!< SDADC_START（位1）*/
#define SDADC_SDADC_CTRL_REG_SDADC_START_Msk (0x2UL)                /*!< SDADC_START（位字段掩码：0x01）*/
#define SDADC_SDADC_CTRL_REG_SDADC_EN_Pos (0UL)                     /*!< SDADC_EN（位0）*/
#define SDADC_SDADC_CTRL_REG_SDADC_EN_Msk (0x1UL)                   /*!< SDADC_EN（位字段掩码：0x01）*/
/* ==================================================  SDADC_GAIN_CORR_REG  ================================================== */
#define SDADC_SDADC_GAIN_CORR_REG_SDADC_GAIN_CORR_Pos (0UL)         /*!< SDADC_GAN_CORR（位0）*/
#define SDADC_SDADC_GAIN_CORR_REG_SDADC_GAIN_CORR_Msk (0x3ffUL)     /*!< SDADC_GAN_CORR（位域掩码：0x3ff）*/
/* ==================================================  SDADC_OFFS_CORR_REG  ================================================== */
#define SDADC_SDADC_OFFS_CORR_REG_SDADC_OFFS_CORR_Pos (0UL)         /*!< SDADC_OFFS_CORR（位0）*/
#define SDADC_SDADC_OFFS_CORR_REG_SDADC_OFFS_CORR_Msk (0x3ffUL)     /*!< SDADC_OFFS_CORR（位域掩码：0x3ff）*/
/* ===================================================  SDADC_RESULT_REG  ==================================================== */
#define SDADC_SDADC_RESULT_REG_SDADC_VAL_Pos (0UL)                  /*!< SDADC_VAL（位0）*/
#define SDADC_SDADC_RESULT_REG_SDADC_VAL_Msk (0xffffUL)             /*!< SDADC_VAL（位字段掩码：0xffff）*/
/* ====================================================  SDADC_TEST_REG  ===================================================== */
#define SDADC_SDADC_TEST_REG_SDADC_CLK_FREQ_Pos (6UL)               /*!< SDADC_CLK_FREQ（位6）*/
#define SDADC_SDADC_TEST_REG_SDADC_CLK_FREQ_Msk (0xc0UL)            /*!< SDADC_CLK_FREQ（位字段掩码：0x03）*/


/* =========================================================================================================================== */
/* ================                                          SMOTOR                                           ================ */
/* =========================================================================================================================== */

/* ====================================================  CMD_TABLE_BASE  ===================================================== */
/* =====================================================  PG0_CTRL_REG  ====================================================== */
#define SMOTOR_PG0_CTRL_REG_GENEND_IRQ_EN_Pos (15UL)                /*!< GENEND_IRQ_EN（位15）*/
#define SMOTOR_PG0_CTRL_REG_GENEND_IRQ_EN_Msk (0x8000UL)            /*!< GENEND_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_GENSTART_IRQ_EN_Pos (14UL)              /*!< GENSTART_IRQ_EN（位14）*/
#define SMOTOR_PG0_CTRL_REG_GENSTART_IRQ_EN_Msk (0x4000UL)          /*!< GENSTART_IRQ_EN（位域掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_PG_START_MODE_Pos (13UL)                /*!< PG_START_MODE（第13位）*/
#define SMOTOR_PG0_CTRL_REG_PG_START_MODE_Msk (0x2000UL)            /*!< PG_START_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_PG_MODE_Pos   (12UL)                    /*!< PG_MODE（位12）*/
#define SMOTOR_PG0_CTRL_REG_PG_MODE_Msk   (0x1000UL)                /*!< PG_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_SIG3_EN_Pos   (11UL)                    /*!< SIG3_EN（位11）*/
#define SMOTOR_PG0_CTRL_REG_SIG3_EN_Msk   (0x800UL)                 /*!< SIG3_EN（位域掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_SIG2_EN_Pos   (10UL)                    /*!< SIG2_EN（位10）*/
#define SMOTOR_PG0_CTRL_REG_SIG2_EN_Msk   (0x400UL)                 /*!< SIG2_EN（位域掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_SIG1_EN_Pos   (9UL)                     /*!< SIG1_EN（第9位）*/
#define SMOTOR_PG0_CTRL_REG_SIG1_EN_Msk   (0x200UL)                 /*!< SIG1_EN（位域掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_SIG0_EN_Pos   (8UL)                     /*!< SIG0_EN（位8）*/
#define SMOTOR_PG0_CTRL_REG_SIG0_EN_Msk   (0x100UL)                 /*!< SIG0_EN（位域掩码：0x01）*/
#define SMOTOR_PG0_CTRL_REG_OUT3_SIG_Pos  (6UL)                     /*!< OUT3_SIG（位6）*/
#define SMOTOR_PG0_CTRL_REG_OUT3_SIG_Msk  (0xc0UL)                  /*!< OUT3_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG0_CTRL_REG_OUT2_SIG_Pos  (4UL)                     /*!< OUT2_SIG（位4）*/
#define SMOTOR_PG0_CTRL_REG_OUT2_SIG_Msk  (0x30UL)                  /*!< OUT2_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG0_CTRL_REG_OUT1_SIG_Pos  (2UL)                     /*!< OUT1_SIG（位2）*/
#define SMOTOR_PG0_CTRL_REG_OUT1_SIG_Msk  (0xcUL)                   /*!< OUT1_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG0_CTRL_REG_OUT0_SIG_Pos  (0UL)                     /*!< OUT0_SIG（位0）*/
#define SMOTOR_PG0_CTRL_REG_OUT0_SIG_Msk  (0x3UL)                   /*!< OUT0_SIG（位字段掩码：0x03）*/
/* =====================================================  PG1_CTRL_REG  ====================================================== */
#define SMOTOR_PG1_CTRL_REG_GENEND_IRQ_EN_Pos (15UL)                /*!< GENEND_IRQ_EN（位15）*/
#define SMOTOR_PG1_CTRL_REG_GENEND_IRQ_EN_Msk (0x8000UL)            /*!< GENEND_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_GENSTART_IRQ_EN_Pos (14UL)              /*!< GENSTART_IRQ_EN（位14）*/
#define SMOTOR_PG1_CTRL_REG_GENSTART_IRQ_EN_Msk (0x4000UL)          /*!< GENSTART_IRQ_EN（位域掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_PG_START_MODE_Pos (13UL)                /*!< PG_START_MODE（第13位）*/
#define SMOTOR_PG1_CTRL_REG_PG_START_MODE_Msk (0x2000UL)            /*!< PG_START_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_PG_MODE_Pos   (12UL)                    /*!< PG_MODE（位12）*/
#define SMOTOR_PG1_CTRL_REG_PG_MODE_Msk   (0x1000UL)                /*!< PG_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_SIG3_EN_Pos   (11UL)                    /*!< SIG3_EN（位11）*/
#define SMOTOR_PG1_CTRL_REG_SIG3_EN_Msk   (0x800UL)                 /*!< SIG3_EN（位域掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_SIG2_EN_Pos   (10UL)                    /*!< SIG2_EN（位10）*/
#define SMOTOR_PG1_CTRL_REG_SIG2_EN_Msk   (0x400UL)                 /*!< SIG2_EN（位域掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_SIG1_EN_Pos   (9UL)                     /*!< SIG1_EN（第9位）*/
#define SMOTOR_PG1_CTRL_REG_SIG1_EN_Msk   (0x200UL)                 /*!< SIG1_EN（位域掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_SIG0_EN_Pos   (8UL)                     /*!< SIG0_EN（位8）*/
#define SMOTOR_PG1_CTRL_REG_SIG0_EN_Msk   (0x100UL)                 /*!< SIG0_EN（位域掩码：0x01）*/
#define SMOTOR_PG1_CTRL_REG_OUT3_SIG_Pos  (6UL)                     /*!< OUT3_SIG（位6）*/
#define SMOTOR_PG1_CTRL_REG_OUT3_SIG_Msk  (0xc0UL)                  /*!< OUT3_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG1_CTRL_REG_OUT2_SIG_Pos  (4UL)                     /*!< OUT2_SIG（位4）*/
#define SMOTOR_PG1_CTRL_REG_OUT2_SIG_Msk  (0x30UL)                  /*!< OUT2_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG1_CTRL_REG_OUT1_SIG_Pos  (2UL)                     /*!< OUT1_SIG（位2）*/
#define SMOTOR_PG1_CTRL_REG_OUT1_SIG_Msk  (0xcUL)                   /*!< OUT1_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG1_CTRL_REG_OUT0_SIG_Pos  (0UL)                     /*!< OUT0_SIG（位0）*/
#define SMOTOR_PG1_CTRL_REG_OUT0_SIG_Msk  (0x3UL)                   /*!< OUT0_SIG（位字段掩码：0x03）*/
/* =====================================================  PG2_CTRL_REG  ====================================================== */
#define SMOTOR_PG2_CTRL_REG_GENEND_IRQ_EN_Pos (15UL)                /*!< GENEND_IRQ_EN（位15）*/
#define SMOTOR_PG2_CTRL_REG_GENEND_IRQ_EN_Msk (0x8000UL)            /*!< GENEND_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_GENSTART_IRQ_EN_Pos (14UL)              /*!< GENSTART_IRQ_EN（位14）*/
#define SMOTOR_PG2_CTRL_REG_GENSTART_IRQ_EN_Msk (0x4000UL)          /*!< GENSTART_IRQ_EN（位域掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_PG_START_MODE_Pos (13UL)                /*!< PG_START_MODE（第13位）*/
#define SMOTOR_PG2_CTRL_REG_PG_START_MODE_Msk (0x2000UL)            /*!< PG_START_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_PG_MODE_Pos   (12UL)                    /*!< PG_MODE（位12）*/
#define SMOTOR_PG2_CTRL_REG_PG_MODE_Msk   (0x1000UL)                /*!< PG_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_SIG3_EN_Pos   (11UL)                    /*!< SIG3_EN（位11）*/
#define SMOTOR_PG2_CTRL_REG_SIG3_EN_Msk   (0x800UL)                 /*!< SIG3_EN（位域掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_SIG2_EN_Pos   (10UL)                    /*!< SIG2_EN（位10）*/
#define SMOTOR_PG2_CTRL_REG_SIG2_EN_Msk   (0x400UL)                 /*!< SIG2_EN（位域掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_SIG1_EN_Pos   (9UL)                     /*!< SIG1_EN（第9位）*/
#define SMOTOR_PG2_CTRL_REG_SIG1_EN_Msk   (0x200UL)                 /*!< SIG1_EN（位域掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_SIG0_EN_Pos   (8UL)                     /*!< SIG0_EN（位8）*/
#define SMOTOR_PG2_CTRL_REG_SIG0_EN_Msk   (0x100UL)                 /*!< SIG0_EN（位域掩码：0x01）*/
#define SMOTOR_PG2_CTRL_REG_OUT3_SIG_Pos  (6UL)                     /*!< OUT3_SIG（位6）*/
#define SMOTOR_PG2_CTRL_REG_OUT3_SIG_Msk  (0xc0UL)                  /*!< OUT3_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG2_CTRL_REG_OUT2_SIG_Pos  (4UL)                     /*!< OUT2_SIG（位4）*/
#define SMOTOR_PG2_CTRL_REG_OUT2_SIG_Msk  (0x30UL)                  /*!< OUT2_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG2_CTRL_REG_OUT1_SIG_Pos  (2UL)                     /*!< OUT1_SIG（位2）*/
#define SMOTOR_PG2_CTRL_REG_OUT1_SIG_Msk  (0xcUL)                   /*!< OUT1_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG2_CTRL_REG_OUT0_SIG_Pos  (0UL)                     /*!< OUT0_SIG（位0）*/
#define SMOTOR_PG2_CTRL_REG_OUT0_SIG_Msk  (0x3UL)                   /*!< OUT0_SIG（位字段掩码：0x03）*/
/* =====================================================  PG3_CTRL_REG  ====================================================== */
#define SMOTOR_PG3_CTRL_REG_GENEND_IRQ_EN_Pos (15UL)                /*!< GENEND_IRQ_EN（位15）*/
#define SMOTOR_PG3_CTRL_REG_GENEND_IRQ_EN_Msk (0x8000UL)            /*!< GENEND_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_GENSTART_IRQ_EN_Pos (14UL)              /*!< GENSTART_IRQ_EN（位14）*/
#define SMOTOR_PG3_CTRL_REG_GENSTART_IRQ_EN_Msk (0x4000UL)          /*!< GENSTART_IRQ_EN（位域掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_PG_START_MODE_Pos (13UL)                /*!< PG_START_MODE（第13位）*/
#define SMOTOR_PG3_CTRL_REG_PG_START_MODE_Msk (0x2000UL)            /*!< PG_START_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_PG_MODE_Pos   (12UL)                    /*!< PG_MODE（位12）*/
#define SMOTOR_PG3_CTRL_REG_PG_MODE_Msk   (0x1000UL)                /*!< PG_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_SIG3_EN_Pos   (11UL)                    /*!< SIG3_EN（位11）*/
#define SMOTOR_PG3_CTRL_REG_SIG3_EN_Msk   (0x800UL)                 /*!< SIG3_EN（位域掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_SIG2_EN_Pos   (10UL)                    /*!< SIG2_EN（位10）*/
#define SMOTOR_PG3_CTRL_REG_SIG2_EN_Msk   (0x400UL)                 /*!< SIG2_EN（位域掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_SIG1_EN_Pos   (9UL)                     /*!< SIG1_EN（第9位）*/
#define SMOTOR_PG3_CTRL_REG_SIG1_EN_Msk   (0x200UL)                 /*!< SIG1_EN（位域掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_SIG0_EN_Pos   (8UL)                     /*!< SIG0_EN（位8）*/
#define SMOTOR_PG3_CTRL_REG_SIG0_EN_Msk   (0x100UL)                 /*!< SIG0_EN（位域掩码：0x01）*/
#define SMOTOR_PG3_CTRL_REG_OUT3_SIG_Pos  (6UL)                     /*!< OUT3_SIG（位6）*/
#define SMOTOR_PG3_CTRL_REG_OUT3_SIG_Msk  (0xc0UL)                  /*!< OUT3_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG3_CTRL_REG_OUT2_SIG_Pos  (4UL)                     /*!< OUT2_SIG（位4）*/
#define SMOTOR_PG3_CTRL_REG_OUT2_SIG_Msk  (0x30UL)                  /*!< OUT2_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG3_CTRL_REG_OUT1_SIG_Pos  (2UL)                     /*!< OUT1_SIG（位2）*/
#define SMOTOR_PG3_CTRL_REG_OUT1_SIG_Msk  (0xcUL)                   /*!< OUT1_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG3_CTRL_REG_OUT0_SIG_Pos  (0UL)                     /*!< OUT0_SIG（位0）*/
#define SMOTOR_PG3_CTRL_REG_OUT0_SIG_Msk  (0x3UL)                   /*!< OUT0_SIG（位字段掩码：0x03）*/
/* =====================================================  PG4_CTRL_REG  ====================================================== */
#define SMOTOR_PG4_CTRL_REG_GENEND_IRQ_EN_Pos (15UL)                /*!< GENEND_IRQ_EN（位15）*/
#define SMOTOR_PG4_CTRL_REG_GENEND_IRQ_EN_Msk (0x8000UL)            /*!< GENEND_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_GENSTART_IRQ_EN_Pos (14UL)              /*!< GENSTART_IRQ_EN（位14）*/
#define SMOTOR_PG4_CTRL_REG_GENSTART_IRQ_EN_Msk (0x4000UL)          /*!< GENSTART_IRQ_EN（位域掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_PG_START_MODE_Pos (13UL)                /*!< PG_START_MODE（第13位）*/
#define SMOTOR_PG4_CTRL_REG_PG_START_MODE_Msk (0x2000UL)            /*!< PG_START_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_PG_MODE_Pos   (12UL)                    /*!< PG_MODE（位12）*/
#define SMOTOR_PG4_CTRL_REG_PG_MODE_Msk   (0x1000UL)                /*!< PG_MODE（位字段掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_SIG3_EN_Pos   (11UL)                    /*!< SIG3_EN（位11）*/
#define SMOTOR_PG4_CTRL_REG_SIG3_EN_Msk   (0x800UL)                 /*!< SIG3_EN（位域掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_SIG2_EN_Pos   (10UL)                    /*!< SIG2_EN（位10）*/
#define SMOTOR_PG4_CTRL_REG_SIG2_EN_Msk   (0x400UL)                 /*!< SIG2_EN（位域掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_SIG1_EN_Pos   (9UL)                     /*!< SIG1_EN（第9位）*/
#define SMOTOR_PG4_CTRL_REG_SIG1_EN_Msk   (0x200UL)                 /*!< SIG1_EN（位域掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_SIG0_EN_Pos   (8UL)                     /*!< SIG0_EN（位8）*/
#define SMOTOR_PG4_CTRL_REG_SIG0_EN_Msk   (0x100UL)                 /*!< SIG0_EN（位域掩码：0x01）*/
#define SMOTOR_PG4_CTRL_REG_OUT3_SIG_Pos  (6UL)                     /*!< OUT3_SIG（位6）*/
#define SMOTOR_PG4_CTRL_REG_OUT3_SIG_Msk  (0xc0UL)                  /*!< OUT3_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG4_CTRL_REG_OUT2_SIG_Pos  (4UL)                     /*!< OUT2_SIG（位4）*/
#define SMOTOR_PG4_CTRL_REG_OUT2_SIG_Msk  (0x30UL)                  /*!< OUT2_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG4_CTRL_REG_OUT1_SIG_Pos  (2UL)                     /*!< OUT1_SIG（位2）*/
#define SMOTOR_PG4_CTRL_REG_OUT1_SIG_Msk  (0xcUL)                   /*!< OUT1_SIG（位字段掩码：0x03）*/
#define SMOTOR_PG4_CTRL_REG_OUT0_SIG_Pos  (0UL)                     /*!< OUT0_SIG（位0）*/
#define SMOTOR_PG4_CTRL_REG_OUT0_SIG_Msk  (0x3UL)                   /*!< OUT0_SIG（位字段掩码：0x03）*/
/* ==================================================  SMOTOR_CMD_FIFO_REG  ================================================== */
#define SMOTOR_SMOTOR_CMD_FIFO_REG_SMOTOR_CMD_FIFO_Pos (0UL)        /*!< SMOTOR_CMD_FIFO（位0）*/
#define SMOTOR_SMOTOR_CMD_FIFO_REG_SMOTOR_CMD_FIFO_Msk (0xffffUL)   /*!< SMOTOR_CMD_FIFO（位字段掩码：0xffff）*/
/* ================================================  SMOTOR_CMD_READ_PTR_REG  ================================================ */
#define SMOTOR_SMOTOR_CMD_READ_PTR_REG_SMOTOR_CMD_READ_PTR_Pos (0UL) /*!< SMOTOR_CMD_READ_PTR（位0）*/
#define SMOTOR_SMOTOR_CMD_READ_PTR_REG_SMOTOR_CMD_READ_PTR_Msk (0x3fUL) /*!< SMOTOR_CMD_READ_PTR（位字段掩码：0x3f）*/
/* ===============================================  SMOTOR_CMD_WRITE_PTR_REG  ================================================ */
#define SMOTOR_SMOTOR_CMD_WRITE_PTR_REG_SMOTOR_CMD_WRITE_PTR_Pos (0UL) /*!< SMOTOR_CMD_WRITE_PTR（位0）*/
#define SMOTOR_SMOTOR_CMD_WRITE_PTR_REG_SMOTOR_CMD_WRITE_PTR_Msk (0x3fUL) /*!< SMOTOR_CMD_WRITE_PTR（位域掩码：0x3f）*/
/* ====================================================  SMOTOR_CTRL_REG  ==================================================== */
#define SMOTOR_SMOTOR_CTRL_REG_TRIG_RTC_EVENT_EN_Pos (28UL)         /*!< TRIG_RTC_EVENT_EN（位28）*/
#define SMOTOR_SMOTOR_CTRL_REG_TRIG_RTC_EVENT_EN_Msk (0x10000000UL) /*!< TRIG_RTC_EVENT_EN（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_MC_LP_CLK_TRIG_EN_Pos (27UL)         /*!< MC_LP_CLK_TRIG_EN（位27）*/
#define SMOTOR_SMOTOR_CTRL_REG_MC_LP_CLK_TRIG_EN_Msk (0x8000000UL)  /*!< MC_LP_CLK_TRIG_EN（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_THRESHOLD_IRQ_EN_Pos (26UL)   /*!< SMOTOR_THRESHOLD_IRQ_EN（位26）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_THRESHOLD_IRQ_EN_Msk (0x4000000UL) /*!< SMOTOR_THRESHOLD_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_THRESHOLD_Pos (21UL)          /*!< SMOTOR_THRESHOLD（位21）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_THRESHOLD_Msk (0x3e00000UL)   /*!< SMOTOR_THRESHOLD（位域掩码：0x1f）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_FIFO_UNR_IRQ_EN_Pos (20UL)    /*!< SMOTOR_FIFO_UNR_IRQ_EN（位20）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_FIFO_UNR_IRQ_EN_Msk (0x100000UL) /*!< SMOTOR_FIFO_UNR_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_FIFO_OVF_IRQ_EN_Pos (19UL)    /*!< SMOTOR_FIFO_OVF_IRQ_EN（位19）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_FIFO_OVF_IRQ_EN_Msk (0x80000UL) /*!< SMOTOR_FIFO_OVF_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_GENEND_IRQ_EN_Pos (18UL)      /*!< SMOTOR_GENEND_IRQ_EN（位18）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_GENEND_IRQ_EN_Msk (0x40000UL) /*!< SMOTOR_GENEND_IRQ_EN（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_GENSTART_IRQ_EN_Pos (17UL)    /*!< SMOTOR_GENSTART_IRQ_EN（位17）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_GENSTART_IRQ_EN_Msk (0x20000UL) /*!< SMOTOR_GENSTART_IRQ_EN（位域掩码：0x01）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_MOI_Pos (7UL)                 /*!< SMOTOR_MOI（位7）*/
#define SMOTOR_SMOTOR_CTRL_REG_SMOTOR_MOI_Msk (0x1ff80UL)           /*!< SMOTOR_MOI（位域掩码：0x3ff）*/
#define SMOTOR_SMOTOR_CTRL_REG_CYCLIC_SIZE_Pos (1UL)                /*!< CYCLIC_SIZE（位1）*/
#define SMOTOR_SMOTOR_CTRL_REG_CYCLIC_SIZE_Msk (0x7eUL)             /*!< CYCLIC_SIZE（位域掩码：0x3f）*/
#define SMOTOR_SMOTOR_CTRL_REG_CYCLIC_MODE_Pos (0UL)                /*!< CYCLIC_MODE（位0）*/
#define SMOTOR_SMOTOR_CTRL_REG_CYCLIC_MODE_Msk (0x1UL)              /*!< CYCLIC_MODE（位字段掩码：0x01）*/
/* =================================================  SMOTOR_IRQ_CLEAR_REG  ================================================== */
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_THRESHOLD_IRQ_CLEAR_Pos (4UL)   /*!< THRESHOLD_IRQ_CLEAR（位4）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_THRESHOLD_IRQ_CLEAR_Msk (0x10UL) /*!< THRESHOLD_IRQ_CLEAR（位域掩码：0x01）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_FIFO_UNR_IRQ_CLEAR_Pos (3UL)    /*!< FIFO_UNR_IRQ_CLEAR（位3）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_FIFO_UNR_IRQ_CLEAR_Msk (0x8UL)  /*!< FIFO_UNR_IRQ_CLEAR（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_FIFO_OVF_IRQ_CLEAR_Pos (2UL)    /*!< FIFO_OVF_IRQ_CLEAR（位2）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_FIFO_OVF_IRQ_CLEAR_Msk (0x4UL)  /*!< FIFO_OVF_IRQ_CLEAR（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_GENEND_IRQ_CLEAR_Pos (1UL)      /*!< GENEND_IRQ_CLEAR（位1）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_GENEND_IRQ_CLEAR_Msk (0x2UL)    /*!< GENEND_IRQ_CLEAR（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_GENSTART_IRQ_CLEAR_Pos (0UL)    /*!< GENSTART_IRQ_CLEAR（位0）*/
#define SMOTOR_SMOTOR_IRQ_CLEAR_REG_GENSTART_IRQ_CLEAR_Msk (0x1UL)  /*!< GENSTART_IRQ_CLEAR（位字段掩码：0x01）*/
/* ===================================================  SMOTOR_STATUS_REG  =================================================== */
#define SMOTOR_SMOTOR_STATUS_REG_PG4_BUSY_Pos (9UL)                 /*!< PG4_BUSY（第9位）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG4_BUSY_Msk (0x200UL)             /*!< PG4_BUSY（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG3_BUSY_Pos (8UL)                 /*!< PG3_BUSY（位8）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG3_BUSY_Msk (0x100UL)             /*!< PG3_BUSY（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG2_BUSY_Pos (7UL)                 /*!< PG2_BUSY（第7位）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG2_BUSY_Msk (0x80UL)              /*!< PG2_BUSY（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG1_BUSY_Pos (6UL)                 /*!< PG1_BUSY（位6）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG1_BUSY_Msk (0x40UL)              /*!< PG1_BUSY（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG0_BUSY_Pos (5UL)                 /*!< PG0_BUSY（位5）*/
#define SMOTOR_SMOTOR_STATUS_REG_PG0_BUSY_Msk (0x20UL)              /*!< PG0_BUSY（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_THRESHOLD_IRQ_STATUS_Pos (4UL)     /*!< THRESHOLD_IRQ_STATUS（位4）*/
#define SMOTOR_SMOTOR_STATUS_REG_THRESHOLD_IRQ_STATUS_Msk (0x10UL)  /*!< THRESHOLD_IRQ_STATUS（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_FIFO_UNR_IRQ_STATUS_Pos (3UL)      /*!< FIFO_UNR_IRQ_STATUS（位3）*/
#define SMOTOR_SMOTOR_STATUS_REG_FIFO_UNR_IRQ_STATUS_Msk (0x8UL)    /*!< FIFO_UNR_IRQ_STATUS（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_FIFO_OVF_IRQ_STATUS_Pos (2UL)      /*!< FIFO_OVF_IRQ_STATUS（位2）*/
#define SMOTOR_SMOTOR_STATUS_REG_FIFO_OVF_IRQ_STATUS_Msk (0x4UL)    /*!< FIFO_OVF_IRQ_STATUS（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_GENEND_IRQ_STATUS_Pos (1UL)        /*!< GENEND_IRQ_STATUS（位1）*/
#define SMOTOR_SMOTOR_STATUS_REG_GENEND_IRQ_STATUS_Msk (0x2UL)      /*!< GENEND_IRQ_STATUS（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_STATUS_REG_GENSTART_IRQ_STATUS_Pos (0UL)      /*!< GENSTART_IRQ_STATUS（位0）*/
#define SMOTOR_SMOTOR_STATUS_REG_GENSTART_IRQ_STATUS_Msk (0x1UL)    /*!< GENSTART_IRQ_STATUS（位字段掩码：0x01）*/
/* ==================================================  SMOTOR_TRIGGER_REG  =================================================== */
#define SMOTOR_SMOTOR_TRIGGER_REG_PG4_START_Pos (5UL)               /*!< PG4_START（第5位）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG4_START_Msk (0x20UL)            /*!< PG4_START（位域掩码：0x01）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG3_START_Pos (4UL)               /*!< PG3_START（位4）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG3_START_Msk (0x10UL)            /*!< PG3_START（位域掩码：0x01）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG2_START_Pos (3UL)               /*!< PG2_START（位3）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG2_START_Msk (0x8UL)             /*!< PG2_START（位字段掩码：0x01）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG1_START_Pos (2UL)               /*!< PG1_START（位2）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG1_START_Msk (0x4UL)             /*!< PG1_START（位域掩码：0x01）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG0_START_Pos (1UL)               /*!< PG0_START（位1）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_PG0_START_Msk (0x2UL)             /*!< PG0_START（位域掩码：0x01）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_POP_CMD_Pos (0UL)                 /*!< POP_CMD（位0）*/
#define SMOTOR_SMOTOR_TRIGGER_REG_POP_CMD_Msk (0x1UL)               /*!< POP_CMD（位字段掩码：0x01）*/
/* ====================================================  WAVETABLE_BASE  ===================================================== */


/* =========================================================================================================================== */
/* ================                                            SNC                                            ================ */
/* =========================================================================================================================== */

/* =====================================================  SNC_CTRL_REG  ====================================================== */
#define SNC_SNC_CTRL_REG_SNC_IRQ_ACK_Pos  (8UL)                     /*!< SNC_IRQ_ACK（位8）*/
#define SNC_SNC_CTRL_REG_SNC_IRQ_ACK_Msk  (0x100UL)                 /*!< SNC_IRQ_ACK（位域掩码：0x01）*/
#define SNC_SNC_CTRL_REG_SNC_IRQ_CONFIG_Pos (6UL)                   /*!< SNC_IRQ_CONFIG（位6）*/
#define SNC_SNC_CTRL_REG_SNC_IRQ_CONFIG_Msk (0xc0UL)                /*!< SNC_IRQ_CONFIG（位域掩码：0x03）*/
#define SNC_SNC_CTRL_REG_SNC_IRQ_EN_Pos   (5UL)                     /*!< SNC_IRQ_EN（位5）*/
#define SNC_SNC_CTRL_REG_SNC_IRQ_EN_Msk   (0x20UL)                  /*!< SNC_IRQ_EN（位域掩码：0x01）*/
#define SNC_SNC_CTRL_REG_SNC_BRANCH_LOOP_INIT_Pos (4UL)             /*!< SNC_BRANCH_LOOP_INIT（位4）*/
#define SNC_SNC_CTRL_REG_SNC_BRANCH_LOOP_INIT_Msk (0x10UL)          /*!< SNC_BRANCH_LOOP_INIT（位域掩码：0x01）*/
#define SNC_SNC_CTRL_REG_SNC_RESET_Pos    (3UL)                     /*!< SNC_RESET（位3）*/
#define SNC_SNC_CTRL_REG_SNC_RESET_Msk    (0x8UL)                   /*!< SNC_RESET（位域掩码：0x01）*/
#define SNC_SNC_CTRL_REG_BUS_ERROR_DETECT_EN_Pos (2UL)              /*!< BUS_ERROR_DETECT_EN（位2）*/
#define SNC_SNC_CTRL_REG_BUS_ERROR_DETECT_EN_Msk (0x4UL)            /*!< BUS_ERROR_DETECT_EN（位字段掩码：0x01）*/
#define SNC_SNC_CTRL_REG_SNC_SW_CTRL_Pos  (1UL)                     /*!< SNC_SW_CTRL（位1）*/
#define SNC_SNC_CTRL_REG_SNC_SW_CTRL_Msk  (0x2UL)                   /*!< SNC_SW_CTRL（位域掩码：0x01）*/
#define SNC_SNC_CTRL_REG_SNC_EN_Pos       (0UL)                     /*!< SNC_EN（位0）*/
#define SNC_SNC_CTRL_REG_SNC_EN_Msk       (0x1UL)                   /*!< SNC_EN（位域掩码：0x01）*/
/* ===================================================  SNC_LP_TIMER_REG  ==================================================== */
#define SNC_SNC_LP_TIMER_REG_LP_TIMER_Pos (0UL)                     /*!< LP_TIMER（位0）*/
#define SNC_SNC_LP_TIMER_REG_LP_TIMER_Msk (0xffUL)                  /*!< LP_TIMER（位字段掩码：0xff）*/
/* ======================================================  SNC_PC_REG  ======================================================= */
#define SNC_SNC_PC_REG_PC_REG_Pos         (2UL)                     /*!< PC_REG（位2）*/
#define SNC_SNC_PC_REG_PC_REG_Msk         (0x7fffcUL)               /*!< PC_REG（位域掩码：0x1ffff）*/
/* ======================================================  SNC_R1_REG  ======================================================= */
#define SNC_SNC_R1_REG_R1_REG_Pos         (0UL)                     /*!< R1_REG（位0）*/
#define SNC_SNC_R1_REG_R1_REG_Msk         (0xffffffffUL)            /*!< R1_REG（位域掩码：0xffffffff）*/
/* ======================================================  SNC_R2_REG  ======================================================= */
#define SNC_SNC_R2_REG_R2_REG_Pos         (0UL)                     /*!< R2_REG（位0）*/
#define SNC_SNC_R2_REG_R2_REG_Msk         (0xffffffffUL)            /*!< R2_REG（位字段掩码：0xffffffff）*/
/* ====================================================  SNC_STATUS_REG  ===================================================== */
#define SNC_SNC_STATUS_REG_SNC_PC_LOADED_Pos (6UL)                  /*!< SNC_PC_LOADED（位6）*/
#define SNC_SNC_STATUS_REG_SNC_PC_LOADED_Msk (0x40UL)               /*!< SNC_PC_LOADED（位字段掩码：0x01）*/
#define SNC_SNC_STATUS_REG_SNC_IS_STOPPED_Pos (5UL)                 /*!< SNC_IS_STOPPED（位5）*/
#define SNC_SNC_STATUS_REG_SNC_IS_STOPPED_Msk (0x20UL)              /*!< SNC_IS_STOPPED（位域掩码：0x01）*/
#define SNC_SNC_STATUS_REG_HARD_FAULT_STATUS_Pos (4UL)              /*!< HARD_FAULT_STATUS（位4）*/
#define SNC_SNC_STATUS_REG_HARD_FAULT_STATUS_Msk (0x10UL)           /*!< HARD_FAULT_STATUS（位字段掩码：0x01）*/
#define SNC_SNC_STATUS_REG_BUS_ERROR_STATUS_Pos (3UL)               /*!< BUS_ERROR_STATUS（位3）*/
#define SNC_SNC_STATUS_REG_BUS_ERROR_STATUS_Msk (0x8UL)             /*!< BUS_ERROR_STATUS（位字段掩码：0x01）*/
#define SNC_SNC_STATUS_REG_SNC_DONE_STATUS_Pos (2UL)                /*!< SNC_DONE_STATUS（位2）*/
#define SNC_SNC_STATUS_REG_SNC_DONE_STATUS_Msk (0x4UL)              /*!< SNC_DONE_STATUS（位字段掩码：0x01）*/
#define SNC_SNC_STATUS_REG_GR_FLAG_Pos    (1UL)                     /*!< GR_FLAG（位1）*/
#define SNC_SNC_STATUS_REG_GR_FLAG_Msk    (0x2UL)                   /*!< GR_FLAG（位字段掩码：0x01）*/
#define SNC_SNC_STATUS_REG_EQ_FLAG_Pos    (0UL)                     /*!< EQ_FLAG（位0）*/
#define SNC_SNC_STATUS_REG_EQ_FLAG_Msk    (0x1UL)                   /*!< EQ_FLAG（位字段掩码：0x01）*/
/* =====================================================  SNC_TMP1_REG  ====================================================== */
#define SNC_SNC_TMP1_REG_TMP1_REG_Pos     (0UL)                     /*!< TMP1_REG（位0）*/
#define SNC_SNC_TMP1_REG_TMP1_REG_Msk     (0xffffffffUL)            /*!< TMP1_REG（位域掩码：0xffffffff）*/
/* =====================================================  SNC_TMP2_REG  ====================================================== */
#define SNC_SNC_TMP2_REG_TMP2_REG_Pos     (0UL)                     /*!< TMP2_REG（位0）*/
#define SNC_SNC_TMP2_REG_TMP2_REG_Msk     (0xffffffffUL)            /*!< TMP2_REG（位域掩码：0xffffffff）*/


/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */

/* ===================================================  SPI_CLEAR_INT_REG  =================================================== */
#define SPI_SPI_CLEAR_INT_REG_SPI_CLEAR_INT_Pos (0UL)               /*!< SPI_CLEAR_INT（位0）*/
#define SPI_SPI_CLEAR_INT_REG_SPI_CLEAR_INT_Msk (0xffffffffUL)      /*!< SPI_CLEAR_INT（位字段掩码：0xffffff）*/
/* =====================================================  SPI_CTRL_REG  ====================================================== */
#define SPI_SPI_CTRL_REG_SPI_TX_FIFO_NOTFULL_MASK_Pos (25UL)        /*!< SPI_TX_FIFO_NOTFULL_MASK（位25）*/
#define SPI_SPI_CTRL_REG_SPI_TX_FIFO_NOTFULL_MASK_Msk (0x2000000UL) /*!< SPI_TX_FIFO_NOTFULL_MASK（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_DMA_TXREQ_MODE_Pos (24UL)              /*!< SPI_DMA_TXREQ_MODE（位24）*/
#define SPI_SPI_CTRL_REG_SPI_DMA_TXREQ_MODE_Msk (0x1000000UL)       /*!< SPI_DMA_TXREQ_MODE（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_TX_FIFO_EMPTY_Pos (23UL)               /*!< SPI_TX_FIFO_EMPTY（位23）*/
#define SPI_SPI_CTRL_REG_SPI_TX_FIFO_EMPTY_Msk (0x800000UL)         /*!< SPI_TX_FIFO_EMPTY（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_RX_FIFO_FULL_Pos (22UL)                /*!< SPI_RX_FIFO_FULL（第22位）*/
#define SPI_SPI_CTRL_REG_SPI_RX_FIFO_FULL_Msk (0x400000UL)          /*!< SPI_RX_FIFO_FULL（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_RX_FIFO_EMPTY_Pos (21UL)               /*!< SPI_RX_FIFO_EMPTY（位21）*/
#define SPI_SPI_CTRL_REG_SPI_RX_FIFO_EMPTY_Msk (0x200000UL)         /*!< SPI_RX_FIFO_EMPTY（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_9BIT_VAL_Pos (20UL)                    /*!< SPI_9BIT_VAL（位20）*/
#define SPI_SPI_CTRL_REG_SPI_9BIT_VAL_Msk (0x100000UL)              /*!< SPI_9BIT_VAL（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_BUSY_Pos     (19UL)                    /*!< SPI_BUSY（位19）*/
#define SPI_SPI_CTRL_REG_SPI_BUSY_Msk     (0x80000UL)               /*!< SPI_BUSY（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_PRIORITY_Pos (18UL)                    /*!< SPI_PRIORITY（位18）*/
#define SPI_SPI_CTRL_REG_SPI_PRIORITY_Msk (0x40000UL)               /*!< SPI_PRIORITY（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_FIFO_MODE_Pos (16UL)                   /*!< SPI_FIFO_MODE（位16）*/
#define SPI_SPI_CTRL_REG_SPI_FIFO_MODE_Msk (0x30000UL)              /*!< SPI_FIFO_MODE（位字段掩码：0x03）*/
#define SPI_SPI_CTRL_REG_SPI_EN_CTRL_Pos  (15UL)                    /*!< SPI_EN_CTRL（第15位）*/
#define SPI_SPI_CTRL_REG_SPI_EN_CTRL_Msk  (0x8000UL)                /*!< SPI_EN_CTRL（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_MINT_Pos     (14UL)                    /*!< SPI_MINT（位14）*/
#define SPI_SPI_CTRL_REG_SPI_MINT_Msk     (0x4000UL)                /*!< SPI_MINT（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_INT_BIT_Pos  (13UL)                    /*!< SPI_INT_BIT（位13）*/
#define SPI_SPI_CTRL_REG_SPI_INT_BIT_Msk  (0x2000UL)                /*!< SPI_INT_BIT（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_DI_Pos       (12UL)                    /*!< SPI_DI（位12）*/
#define SPI_SPI_CTRL_REG_SPI_DI_Msk       (0x1000UL)                /*!< SPI_DI（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_TXH_Pos      (11UL)                    /*!< SPI_TXH（位11）*/
#define SPI_SPI_CTRL_REG_SPI_TXH_Msk      (0x800UL)                 /*!< SPI_TXH（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_FORCE_DO_Pos (10UL)                    /*!< SPI_FORCE_DO（位10）*/
#define SPI_SPI_CTRL_REG_SPI_FORCE_DO_Msk (0x400UL)                 /*!< SPI_FORCE_DO（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_WORD_Pos     (8UL)                     /*!< SPI_WORD（位8）*/
#define SPI_SPI_CTRL_REG_SPI_WORD_Msk     (0x300UL)                 /*!< SPI_WORD（位域掩码：0x03）*/
#define SPI_SPI_CTRL_REG_SPI_RST_Pos      (7UL)                     /*!< SPI_RST（第7位）*/
#define SPI_SPI_CTRL_REG_SPI_RST_Msk      (0x80UL)                  /*!< SPI_RST（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_SMN_Pos      (6UL)                     /*!< SPI_SMN（第6位）*/
#define SPI_SPI_CTRL_REG_SPI_SMN_Msk      (0x40UL)                  /*!< SPI_SMN（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_DO_Pos       (5UL)                     /*!< SPI_DO（位5）*/
#define SPI_SPI_CTRL_REG_SPI_DO_Msk       (0x20UL)                  /*!< SPI_DO（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_CLK_Pos      (3UL)                     /*!< SPI_CLK（位3）*/
#define SPI_SPI_CTRL_REG_SPI_CLK_Msk      (0x18UL)                  /*!< SPI_CLK（位域掩码：0x03）*/
#define SPI_SPI_CTRL_REG_SPI_POL_Pos      (2UL)                     /*!< SPI_POL（位2）*/
#define SPI_SPI_CTRL_REG_SPI_POL_Msk      (0x4UL)                   /*!< SPI_POL（位字段掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_PHA_Pos      (1UL)                     /*!< SPI_PHA（位1）*/
#define SPI_SPI_CTRL_REG_SPI_PHA_Msk      (0x2UL)                   /*!< SPI_PHA（位域掩码：0x01）*/
#define SPI_SPI_CTRL_REG_SPI_ON_Pos       (0UL)                     /*!< SPI_ON（位0）*/
#define SPI_SPI_CTRL_REG_SPI_ON_Msk       (0x1UL)                   /*!< SPI_ON（位域掩码：0x01）*/
/* =====================================================  SPI_RX_TX_REG  ===================================================== */
#define SPI_SPI_RX_TX_REG_SPI_DATA_Pos    (0UL)                     /*!< SPI_DATA（位0）*/
#define SPI_SPI_RX_TX_REG_SPI_DATA_Msk    (0xffffffffUL)            /*!< SPI_DATA（位域掩码：0xffffffff）*/


/* =========================================================================================================================== */
/* ================                                           SPI2                                            ================ */
/* =========================================================================================================================== */

/* ==================================================  SPI2_CLEAR_INT_REG  =================================================== */
#define SPI2_SPI2_CLEAR_INT_REG_SPI_CLEAR_INT_Pos (0UL)             /*!< SPI_CLEAR_INT（位0）*/
#define SPI2_SPI2_CLEAR_INT_REG_SPI_CLEAR_INT_Msk (0xffffffffUL)    /*!< SPI_CLEAR_INT（位字段掩码：0xffffff）*/
/* =====================================================  SPI2_CTRL_REG  ===================================================== */
#define SPI2_SPI2_CTRL_REG_SPI_TX_FIFO_NOTFULL_MASK_Pos (25UL)      /*!< SPI_TX_FIFO_NOTFULL_MASK（位25）*/
#define SPI2_SPI2_CTRL_REG_SPI_TX_FIFO_NOTFULL_MASK_Msk (0x2000000UL) /*!< SPI_TX_FIFO_NOTFULL_MASK（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_DMA_TXREQ_MODE_Pos (24UL)            /*!< SPI_DMA_TXREQ_MODE（位24）*/
#define SPI2_SPI2_CTRL_REG_SPI_DMA_TXREQ_MODE_Msk (0x1000000UL)     /*!< SPI_DMA_TXREQ_MODE（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_TX_FIFO_EMPTY_Pos (23UL)             /*!< SPI_TX_FIFO_EMPTY（位23）*/
#define SPI2_SPI2_CTRL_REG_SPI_TX_FIFO_EMPTY_Msk (0x800000UL)       /*!< SPI_TX_FIFO_EMPTY（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_RX_FIFO_FULL_Pos (22UL)              /*!< SPI_RX_FIFO_FULL（第22位）*/
#define SPI2_SPI2_CTRL_REG_SPI_RX_FIFO_FULL_Msk (0x400000UL)        /*!< SPI_RX_FIFO_FULL（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_RX_FIFO_EMPTY_Pos (21UL)             /*!< SPI_RX_FIFO_EMPTY（位21）*/
#define SPI2_SPI2_CTRL_REG_SPI_RX_FIFO_EMPTY_Msk (0x200000UL)       /*!< SPI_RX_FIFO_EMPTY（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_9BIT_VAL_Pos (20UL)                  /*!< SPI_9BIT_VAL（位20）*/
#define SPI2_SPI2_CTRL_REG_SPI_9BIT_VAL_Msk (0x100000UL)            /*!< SPI_9BIT_VAL（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_BUSY_Pos   (19UL)                    /*!< SPI_BUSY（位19）*/
#define SPI2_SPI2_CTRL_REG_SPI_BUSY_Msk   (0x80000UL)               /*!< SPI_BUSY（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_PRIORITY_Pos (18UL)                  /*!< SPI_PRIORITY（位18）*/
#define SPI2_SPI2_CTRL_REG_SPI_PRIORITY_Msk (0x40000UL)             /*!< SPI_PRIORITY（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_FIFO_MODE_Pos (16UL)                 /*!< SPI_FIFO_MODE（位16）*/
#define SPI2_SPI2_CTRL_REG_SPI_FIFO_MODE_Msk (0x30000UL)            /*!< SPI_FIFO_MODE（位字段掩码：0x03）*/
#define SPI2_SPI2_CTRL_REG_SPI_EN_CTRL_Pos (15UL)                   /*!< SPI_EN_CTRL（第15位）*/
#define SPI2_SPI2_CTRL_REG_SPI_EN_CTRL_Msk (0x8000UL)               /*!< SPI_EN_CTRL（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_MINT_Pos   (14UL)                    /*!< SPI_MINT（位14）*/
#define SPI2_SPI2_CTRL_REG_SPI_MINT_Msk   (0x4000UL)                /*!< SPI_MINT（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_INT_BIT_Pos (13UL)                   /*!< SPI_INT_BIT（位13）*/
#define SPI2_SPI2_CTRL_REG_SPI_INT_BIT_Msk (0x2000UL)               /*!< SPI_INT_BIT（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_DI_Pos     (12UL)                    /*!< SPI_DI（位12）*/
#define SPI2_SPI2_CTRL_REG_SPI_DI_Msk     (0x1000UL)                /*!< SPI_DI（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_TXH_Pos    (11UL)                    /*!< SPI_TXH（位11）*/
#define SPI2_SPI2_CTRL_REG_SPI_TXH_Msk    (0x800UL)                 /*!< SPI_TXH（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_FORCE_DO_Pos (10UL)                  /*!< SPI_FORCE_DO（位10）*/
#define SPI2_SPI2_CTRL_REG_SPI_FORCE_DO_Msk (0x400UL)               /*!< SPI_FORCE_DO（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_WORD_Pos   (8UL)                     /*!< SPI_WORD（位8）*/
#define SPI2_SPI2_CTRL_REG_SPI_WORD_Msk   (0x300UL)                 /*!< SPI_WORD（位域掩码：0x03）*/
#define SPI2_SPI2_CTRL_REG_SPI_RST_Pos    (7UL)                     /*!< SPI_RST（第7位）*/
#define SPI2_SPI2_CTRL_REG_SPI_RST_Msk    (0x80UL)                  /*!< SPI_RST（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_SMN_Pos    (6UL)                     /*!< SPI_SMN（第6位）*/
#define SPI2_SPI2_CTRL_REG_SPI_SMN_Msk    (0x40UL)                  /*!< SPI_SMN（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_DO_Pos     (5UL)                     /*!< SPI_DO（位5）*/
#define SPI2_SPI2_CTRL_REG_SPI_DO_Msk     (0x20UL)                  /*!< SPI_DO（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_CLK_Pos    (3UL)                     /*!< SPI_CLK（位3）*/
#define SPI2_SPI2_CTRL_REG_SPI_CLK_Msk    (0x18UL)                  /*!< SPI_CLK（位域掩码：0x03）*/
#define SPI2_SPI2_CTRL_REG_SPI_POL_Pos    (2UL)                     /*!< SPI_POL（位2）*/
#define SPI2_SPI2_CTRL_REG_SPI_POL_Msk    (0x4UL)                   /*!< SPI_POL（位字段掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_PHA_Pos    (1UL)                     /*!< SPI_PHA（位1）*/
#define SPI2_SPI2_CTRL_REG_SPI_PHA_Msk    (0x2UL)                   /*!< SPI_PHA（位域掩码：0x01）*/
#define SPI2_SPI2_CTRL_REG_SPI_ON_Pos     (0UL)                     /*!< SPI_ON（位0）*/
#define SPI2_SPI2_CTRL_REG_SPI_ON_Msk     (0x1UL)                   /*!< SPI_ON（位域掩码：0x01）*/
/* ====================================================  SPI2_RX_TX_REG  ===================================================== */
#define SPI2_SPI2_RX_TX_REG_SPI_DATA_Pos  (0UL)                     /*!< SPI_DATA（位0）*/
#define SPI2_SPI2_RX_TX_REG_SPI_DATA_Msk  (0xffffffffUL)            /*!< SPI_DATA（位域掩码：0xffffffff）*/


/* =========================================================================================================================== */
/* ================                                         SYS_WDOG                                          ================ */
/* =========================================================================================================================== */

/* ===================================================  WATCHDOG_CTRL_REG  =================================================== */
#define SYS_WDOG_WATCHDOG_CTRL_REG_WRITE_BUSY_Pos (3UL)             /*!< WRITE_BUSY（位3）*/
#define SYS_WDOG_WATCHDOG_CTRL_REG_WRITE_BUSY_Msk (0x8UL)           /*!< WRITE_BUSY（位字段掩码：0x01）*/
#define SYS_WDOG_WATCHDOG_CTRL_REG_WDOG_FREEZE_EN_Pos (2UL)         /*!< WDOG_FREEZE_EN（位2）*/
#define SYS_WDOG_WATCHDOG_CTRL_REG_WDOG_FREEZE_EN_Msk (0x4UL)       /*!< WDOG_FREEZE_EN（位域掩码：0x01）*/
#define SYS_WDOG_WATCHDOG_CTRL_REG_NMI_RST_Pos (0UL)                /*!< NMI_RST（位0）*/
#define SYS_WDOG_WATCHDOG_CTRL_REG_NMI_RST_Msk (0x1UL)              /*!< NMI_RST（位字段掩码：0x01）*/
/* =====================================================  WATCHDOG_REG  ====================================================== */
#define SYS_WDOG_WATCHDOG_REG_WDOG_WEN_Pos (14UL)                   /*!< WDOG_WEN（第14位）*/
#define SYS_WDOG_WATCHDOG_REG_WDOG_WEN_Msk (0xffffc000UL)           /*!< WDOG_WEN（位域掩码：0x3ffff）*/
#define SYS_WDOG_WATCHDOG_REG_WDOG_VAL_NEG_Pos (13UL)               /*!< WDOG_VAL_NEG（第13位）*/
#define SYS_WDOG_WATCHDOG_REG_WDOG_VAL_NEG_Msk (0x2000UL)           /*!< WDOG_VAL_NEG（位字段掩码：0x01）*/
#define SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Pos (0UL)                    /*!< WDOG_VAL（位0）*/
#define SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Msk (0x1fffUL)               /*!< WDOG_VAL（位域掩码：0x1fff）*/


/* =========================================================================================================================== */
/* ================                                           TIMER                                           ================ */
/* =========================================================================================================================== */

/* ================================================  TIMER_CAPTURE_GPIO1_REG  ================================================ */
#define TIMER_TIMER_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Pos (0UL)   /*!< TIM_CAPTURE_GPIO1（位0）*/
#define TIMER_TIMER_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO1（位域掩码：0xffffff）*/
/* ================================================  TIMER_CAPTURE_GPIO2_REG  ================================================ */
#define TIMER_TIMER_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Pos (0UL)   /*!< TIM_CAPTURE_GPIO2（位0）*/
#define TIMER_TIMER_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO2（位域掩码：0xffffff）*/
/* ================================================  TIMER_CAPTURE_GPIO3_REG  ================================================ */
#define TIMER_TIMER_CAPTURE_GPIO3_REG_TIM_CAPTURE_GPIO3_Pos (0UL)   /*!< TIM_CAPTURE_GPIO3（位0）*/
#define TIMER_TIMER_CAPTURE_GPIO3_REG_TIM_CAPTURE_GPIO3_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO3（位域掩码：0xffffff）*/
/* ================================================  TIMER_CAPTURE_GPIO4_REG  ================================================ */
#define TIMER_TIMER_CAPTURE_GPIO4_REG_TIM_CAPTURE_GPIO4_Pos (0UL)   /*!< TIM_CAPTURE_GPIO4（位0）*/
#define TIMER_TIMER_CAPTURE_GPIO4_REG_TIM_CAPTURE_GPIO4_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO4（位域掩码：0xffffff）*/
/* ==============================================  TIMER_CLEAR_GPIO_EVENT_REG  =============================================== */
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO4_EVENT_Pos (3UL) /*!< TIM_CLEAR_GPIO4_EVENT（位3）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO4_EVENT_Msk (0x8UL) /*!< TIM_CLEAR_GPIO4_EVENT（位字段掩码：0x01）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO3_EVENT_Pos (2UL) /*!< TIM_CLEAR_GPIO3_EVENT（位2）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO3_EVENT_Msk (0x4UL) /*!< TIM_CLEAR_GPIO3_EVENT（位字段掩码：0x01）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO2_EVENT_Pos (1UL) /*!< TIM_CLEAR_GPIO2_EVENT（位1）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO2_EVENT_Msk (0x2UL) /*!< TIM_CLEAR_GPIO2_EVENT（位字段掩码：0x01）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO1_EVENT_Pos (0UL) /*!< TIM_CLEAR_GPIO1_EVENT（位0）*/
#define TIMER_TIMER_CLEAR_GPIO_EVENT_REG_TIM_CLEAR_GPIO1_EVENT_Msk (0x1UL) /*!< TIM_CLEAR_GPIO1_EVENT（位字段掩码：0x01）*/
/* ==================================================  TIMER_CLEAR_IRQ_REG  ================================================== */
#define TIMER_TIMER_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Pos (0UL)           /*!< TIM_CLEAR_IRQ（位0）*/
#define TIMER_TIMER_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Msk (0x1UL)         /*!< TIM_CLEAR_IRQ（位字段掩码：0x01）*/
/* ====================================================  TIMER_CTRL_REG  ===================================================== */
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Pos (14UL)        /*!< TIM_CAP_GPIO4_IRQ_EN（位14）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Msk (0x4000UL)    /*!< TIM_CAP_GPIO4_IRQ_EN（位域掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Pos (13UL)        /*!< TIM_CAP_GPIO3_IRQ_EN（位13）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Msk (0x2000UL)    /*!< TIM_CAP_GPIO3_IRQ_EN（位域掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Pos (12UL)        /*!< TIM_CAP_GPIO2_IRQ_EN（位12）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Msk (0x1000UL)    /*!< TIM_CAP_GPIO2_IRQ_EN（位域掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Pos (11UL)        /*!< TIM_CAP_GPIO1_IRQ_EN（位11）*/
#define TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Msk (0x800UL)     /*!< TIM_CAP_GPIO1_IRQ_EN（位域掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN4_EVENT_FALL_EN_Pos (10UL)       /*!< TIM_IN4_EVENT_FALL_EN（位10）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN4_EVENT_FALL_EN_Msk (0x400UL)    /*!< TIM_IN4_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN3_EVENT_FALL_EN_Pos (9UL)        /*!< TIM_IN3_EVENT_FALL_EN（第9位）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN3_EVENT_FALL_EN_Msk (0x200UL)    /*!< TIM_IN3_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_CLK_EN_Pos (8UL)                   /*!< TIM_CLK_EN（位8）*/
#define TIMER_TIMER_CTRL_REG_TIM_CLK_EN_Msk (0x100UL)               /*!< TIM_CLK_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_SYS_CLK_EN_Pos (7UL)               /*!< TIM_SYS_CLK_EN（第7位）*/
#define TIMER_TIMER_CTRL_REG_TIM_SYS_CLK_EN_Msk (0x80UL)            /*!< TIM_SYS_CLK_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_FREE_RUN_MODE_EN_Pos (6UL)         /*!< TIM_FREE_RUN_MODE_EN（位6）*/
#define TIMER_TIMER_CTRL_REG_TIM_FREE_RUN_MODE_EN_Msk (0x40UL)      /*!< TIM_FREE_RUN_MODE_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_IRQ_EN_Pos (5UL)                   /*!< TIM_IRQ_EN（第5位）*/
#define TIMER_TIMER_CTRL_REG_TIM_IRQ_EN_Msk (0x20UL)                /*!< TIM_IRQ_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Pos (4UL)        /*!< TIM_IN2_EVENT_FALL_EN（位4）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Msk (0x10UL)     /*!< TIM_IN2_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Pos (3UL)        /*!< TIM_IN1_EVENT_FALL_EN（位3）*/
#define TIMER_TIMER_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Msk (0x8UL)      /*!< TIM_IN1_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_COUNT_DOWN_EN_Pos (2UL)            /*!< TIM_COUNT_DOWN_EN（位2）*/
#define TIMER_TIMER_CTRL_REG_TIM_COUNT_DOWN_EN_Msk (0x4UL)          /*!< TIM_COUNT_DOWN_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_ONESHOT_MODE_EN_Pos (1UL)          /*!< TIM_ONESHOT_MODE_EN（位1）*/
#define TIMER_TIMER_CTRL_REG_TIM_ONESHOT_MODE_EN_Msk (0x2UL)        /*!< TIM_ONESHOT_MODE_EN（位字段掩码：0x01）*/
#define TIMER_TIMER_CTRL_REG_TIM_EN_Pos   (0UL)                     /*!< TIM_EN（位0）*/
#define TIMER_TIMER_CTRL_REG_TIM_EN_Msk   (0x1UL)                   /*!< TIM_EN（位域掩码：0x01）*/
/* =================================================  TIMER_GPIO1_CONF_REG  ================================================== */
#define TIMER_TIMER_GPIO1_CONF_REG_TIM_GPIO1_CONF_Pos (0UL)         /*!< TIM_GPIO1_CONF（位0）*/
#define TIMER_TIMER_GPIO1_CONF_REG_TIM_GPIO1_CONF_Msk (0x3fUL)      /*!< TIM_GPIO1_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER_GPIO2_CONF_REG  ================================================== */
#define TIMER_TIMER_GPIO2_CONF_REG_TIM_GPIO2_CONF_Pos (0UL)         /*!< TIM_GPIO2_CONF（位0）*/
#define TIMER_TIMER_GPIO2_CONF_REG_TIM_GPIO2_CONF_Msk (0x3fUL)      /*!< TIM_GPIO2_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER_GPIO3_CONF_REG  ================================================== */
#define TIMER_TIMER_GPIO3_CONF_REG_TIM_GPIO3_CONF_Pos (0UL)         /*!< TIM_GPIO3_CONF（位0）*/
#define TIMER_TIMER_GPIO3_CONF_REG_TIM_GPIO3_CONF_Msk (0x3fUL)      /*!< TIM_GPIO3_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER_GPIO4_CONF_REG  ================================================== */
#define TIMER_TIMER_GPIO4_CONF_REG_TIM_GPIO4_CONF_Pos (0UL)         /*!< TIM_GPIO4_CONF（位0）*/
#define TIMER_TIMER_GPIO4_CONF_REG_TIM_GPIO4_CONF_Msk (0x3fUL)      /*!< TIM_GPIO4_CONF（位域掩码：0x3f）*/
/* ==================================================  TIMER_PRESCALER_REG  ================================================== */
#define TIMER_TIMER_PRESCALER_REG_TIM_PRESCALER_Pos (0UL)           /*!< TIM_PRESCALER（位0）*/
#define TIMER_TIMER_PRESCALER_REG_TIM_PRESCALER_Msk (0x1fUL)        /*!< TIM_PRESCALER（位字段掩码：0x1f）*/
/* ================================================  TIMER_PRESCALER_VAL_REG  ================================================ */
#define TIMER_TIMER_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Pos (0UL)   /*!< TIM_PRESCALER_VAL（位0）*/
#define TIMER_TIMER_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Msk (0x1fUL) /*!< TIM_PRESCALER_VAL（位字段掩码：0x1f）*/
/* ===================================================  TIMER_PWM_DC_REG  ==================================================== */
#define TIMER_TIMER_PWM_DC_REG_TIM_PWM_DC_Pos (0UL)                 /*!< TIM_PWM_DC（位0）*/
#define TIMER_TIMER_PWM_DC_REG_TIM_PWM_DC_Msk (0xffffUL)            /*!< TIM_PWM_DC（位字段掩码：0xffff）*/
/* ==================================================  TIMER_PWM_FREQ_REG  =================================================== */
#define TIMER_TIMER_PWM_FREQ_REG_TIM_PWM_FREQ_Pos (0UL)             /*!< TIM_PWM_FREQ（位0）*/
#define TIMER_TIMER_PWM_FREQ_REG_TIM_PWM_FREQ_Msk (0xffffUL)        /*!< TIM_PWM_FREQ（位字段掩码：0xffff）*/
/* ===================================================  TIMER_RELOAD_REG  ==================================================== */
#define TIMER_TIMER_RELOAD_REG_TIM_RELOAD_Pos (0UL)                 /*!< TIM_RELOAD（位0）*/
#define TIMER_TIMER_RELOAD_REG_TIM_RELOAD_Msk (0xffffffUL)          /*!< TIM_RELOAD（位字段掩码：0xffffff）*/
/* ==================================================  TIMER_SHOTWIDTH_REG  ================================================== */
#define TIMER_TIMER_SHOTWIDTH_REG_TIM_SHOTWIDTH_Pos (0UL)           /*!< TIM_SHOTWITH（位0）*/
#define TIMER_TIMER_SHOTWIDTH_REG_TIM_SHOTWIDTH_Msk (0xffffffUL)    /*!< TIM_SHOTWITH（位域掩码：0xffffff）*/
/* ===================================================  TIMER_STATUS_REG  ==================================================== */
#define TIMER_TIMER_STATUS_REG_TIM_GPIO4_EVENT_PENDING_Pos (7UL)    /*!< TIM_GPIO4_EVENT_PENDING（位7）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO4_EVENT_PENDING_Msk (0x80UL) /*!< TIM_GPIO4_EVENT_PENDING（位域掩码：0x01）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO3_EVENT_PENDING_Pos (6UL)    /*!< TIM_GPIO3_EVENT_PENDING（位6）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO3_EVENT_PENDING_Msk (0x40UL) /*!< TIM_GPIO3_EVENT_PENDING（位域掩码：0x01）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO2_EVENT_PENDING_Pos (5UL)    /*!< TIM_GPIO2_EVENT_PENDING（位5）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO2_EVENT_PENDING_Msk (0x20UL) /*!< TIM_GPIO2_EVENT_PENDING（位域掩码：0x01）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO1_EVENT_PENDING_Pos (4UL)    /*!< TIM_GPIO1_EVENT_PENDING（位4）*/
#define TIMER_TIMER_STATUS_REG_TIM_GPIO1_EVENT_PENDING_Msk (0x10UL) /*!< TIM_GPIO1_EVENT_PENDING（位字段掩码：0x01）*/
#define TIMER_TIMER_STATUS_REG_TIM_ONESHOT_PHASE_Pos (2UL)          /*!< TIM_ONESHOT_PHASE（位2）*/
#define TIMER_TIMER_STATUS_REG_TIM_ONESHOT_PHASE_Msk (0xcUL)        /*!< TIM_ONESHOT_PHASE（位字段掩码：0x03）*/
#define TIMER_TIMER_STATUS_REG_TIM_IN2_STATE_Pos (1UL)              /*!< TIM_IN2_STATE（位1）*/
#define TIMER_TIMER_STATUS_REG_TIM_IN2_STATE_Msk (0x2UL)            /*!< TIM_IN2_STATE（位字段掩码：0x01）*/
#define TIMER_TIMER_STATUS_REG_TIM_IN1_STATE_Pos (0UL)              /*!< TIM_IN1_STATE（位0）*/
#define TIMER_TIMER_STATUS_REG_TIM_IN1_STATE_Msk (0x1UL)            /*!< TIM_IN1_STATE（位字段掩码：0x01）*/
/* ==================================================  TIMER_TIMER_VAL_REG  ================================================== */
#define TIMER_TIMER_TIMER_VAL_REG_TIM_TIMER_VALUE_Pos (0UL)         /*!< TIM_TIMER_VALUE（位0）*/
#define TIMER_TIMER_TIMER_VAL_REG_TIM_TIMER_VALUE_Msk (0xffffffUL)  /*!< TIM_TIMER_VALUE（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                          TIMER2                                           ================ */
/* =========================================================================================================================== */

/* ===============================================  TIMER2_CAPTURE_GPIO1_REG  ================================================ */
#define TIMER2_TIMER2_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Pos (0UL) /*!< TIM_CAPTURE_GPIO1（位0）*/
#define TIMER2_TIMER2_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO1（位域掩码：0xffffff）*/
/* ===============================================  TIMER2_CAPTURE_GPIO2_REG  ================================================ */
#define TIMER2_TIMER2_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Pos (0UL) /*!< TIM_CAPTURE_GPIO2（位0）*/
#define TIMER2_TIMER2_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO2（位域掩码：0xffffff）*/
/* =================================================  TIMER2_CLEAR_IRQ_REG  ================================================== */
#define TIMER2_TIMER2_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Pos (0UL)         /*!< TIM_CLEAR_IRQ（位0）*/
#define TIMER2_TIMER2_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Msk (0x1UL)       /*!< TIM_CLEAR_IRQ（位字段掩码：0x01）*/
/* ====================================================  TIMER2_CTRL_REG  ==================================================== */
#define TIMER2_TIMER2_CTRL_REG_TIM_CLK_EN_Pos (8UL)                 /*!< TIM_CLK_EN（位8）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_CLK_EN_Msk (0x100UL)             /*!< TIM_CLK_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_SYS_CLK_EN_Pos (7UL)             /*!< TIM_SYS_CLK_EN（第7位）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_SYS_CLK_EN_Msk (0x80UL)          /*!< TIM_SYS_CLK_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_FREE_RUN_MODE_EN_Pos (6UL)       /*!< TIM_FREE_RUN_MODE_EN（位6）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_FREE_RUN_MODE_EN_Msk (0x40UL)    /*!< TIM_FREE_RUN_MODE_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_IRQ_EN_Pos (5UL)                 /*!< TIM_IRQ_EN（第5位）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_IRQ_EN_Msk (0x20UL)              /*!< TIM_IRQ_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Pos (4UL)      /*!< TIM_IN2_EVENT_FALL_EN（位4）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Msk (0x10UL)   /*!< TIM_IN2_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Pos (3UL)      /*!< TIM_IN1_EVENT_FALL_EN（位3）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Msk (0x8UL)    /*!< TIM_IN1_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_COUNT_DOWN_EN_Pos (2UL)          /*!< TIM_COUNT_DOWN_EN（位2）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_COUNT_DOWN_EN_Msk (0x4UL)        /*!< TIM_COUNT_DOWN_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_ONESHOT_MODE_EN_Pos (1UL)        /*!< TIM_ONESHOT_MODE_EN（位1）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_ONESHOT_MODE_EN_Msk (0x2UL)      /*!< TIM_ONESHOT_MODE_EN（位字段掩码：0x01）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_EN_Pos (0UL)                     /*!< TIM_EN（位0）*/
#define TIMER2_TIMER2_CTRL_REG_TIM_EN_Msk (0x1UL)                   /*!< TIM_EN（位域掩码：0x01）*/
/* =================================================  TIMER2_GPIO1_CONF_REG  ================================================= */
#define TIMER2_TIMER2_GPIO1_CONF_REG_TIM_GPIO1_CONF_Pos (0UL)       /*!< TIM_GPIO1_CONF（位0）*/
#define TIMER2_TIMER2_GPIO1_CONF_REG_TIM_GPIO1_CONF_Msk (0x3fUL)    /*!< TIM_GPIO1_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER2_GPIO2_CONF_REG  ================================================= */
#define TIMER2_TIMER2_GPIO2_CONF_REG_TIM_GPIO2_CONF_Pos (0UL)       /*!< TIM_GPIO2_CONF（位0）*/
#define TIMER2_TIMER2_GPIO2_CONF_REG_TIM_GPIO2_CONF_Msk (0x3fUL)    /*!< TIM_GPIO2_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER2_PRESCALER_REG  ================================================== */
#define TIMER2_TIMER2_PRESCALER_REG_TIM_PRESCALER_Pos (0UL)         /*!< TIM_PRESCALER（位0）*/
#define TIMER2_TIMER2_PRESCALER_REG_TIM_PRESCALER_Msk (0x1fUL)      /*!< TIM_PRESCALER（位字段掩码：0x1f）*/
/* ===============================================  TIMER2_PRESCALER_VAL_REG  ================================================ */
#define TIMER2_TIMER2_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Pos (0UL) /*!< TIM_PRESCALER_VAL（位0）*/
#define TIMER2_TIMER2_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Msk (0x1fUL) /*!< TIM_PRESCALER_VAL（位字段掩码：0x1f）*/
/* ===================================================  TIMER2_PWM_DC_REG  =================================================== */
#define TIMER2_TIMER2_PWM_DC_REG_TIM_PWM_DC_Pos (0UL)               /*!< TIM_PWM_DC（位0）*/
#define TIMER2_TIMER2_PWM_DC_REG_TIM_PWM_DC_Msk (0xffffUL)          /*!< TIM_PWM_DC（位字段掩码：0xffff）*/
/* ==================================================  TIMER2_PWM_FREQ_REG  ================================================== */
#define TIMER2_TIMER2_PWM_FREQ_REG_TIM_PWM_FREQ_Pos (0UL)           /*!< TIM_PWM_FREQ（位0）*/
#define TIMER2_TIMER2_PWM_FREQ_REG_TIM_PWM_FREQ_Msk (0xffffUL)      /*!< TIM_PWM_FREQ（位字段掩码：0xffff）*/
/* ===================================================  TIMER2_RELOAD_REG  =================================================== */
#define TIMER2_TIMER2_RELOAD_REG_TIM_RELOAD_Pos (0UL)               /*!< TIM_RELOAD（位0）*/
#define TIMER2_TIMER2_RELOAD_REG_TIM_RELOAD_Msk (0xffffffUL)        /*!< TIM_RELOAD（位字段掩码：0xffffff）*/
/* =================================================  TIMER2_SHOTWIDTH_REG  ================================================== */
#define TIMER2_TIMER2_SHOTWIDTH_REG_TIM_SHOTWIDTH_Pos (0UL)         /*!< TIM_SHOTWITH（位0）*/
#define TIMER2_TIMER2_SHOTWIDTH_REG_TIM_SHOTWIDTH_Msk (0xffffffUL)  /*!< TIM_SHOTWITH（位域掩码：0xffffff）*/
/* ===================================================  TIMER2_STATUS_REG  =================================================== */
#define TIMER2_TIMER2_STATUS_REG_TIM_ONESHOT_PHASE_Pos (2UL)        /*!< TIM_ONESHOT_PHASE（位2）*/
#define TIMER2_TIMER2_STATUS_REG_TIM_ONESHOT_PHASE_Msk (0xcUL)      /*!< TIM_ONESHOT_PHASE（位字段掩码：0x03）*/
#define TIMER2_TIMER2_STATUS_REG_TIM_IN2_STATE_Pos (1UL)            /*!< TIM_IN2_STATE（位1）*/
#define TIMER2_TIMER2_STATUS_REG_TIM_IN2_STATE_Msk (0x2UL)          /*!< TIM_IN2_STATE（位字段掩码：0x01）*/
#define TIMER2_TIMER2_STATUS_REG_TIM_IN1_STATE_Pos (0UL)            /*!< TIM_IN1_STATE（位0）*/
#define TIMER2_TIMER2_STATUS_REG_TIM_IN1_STATE_Msk (0x1UL)          /*!< TIM_IN1_STATE（位字段掩码：0x01）*/
/* =================================================  TIMER2_TIMER_VAL_REG  ================================================== */
#define TIMER2_TIMER2_TIMER_VAL_REG_TIM_TIMER_VALUE_Pos (0UL)       /*!< TIM_TIMER_VALUE（位0）*/
#define TIMER2_TIMER2_TIMER_VAL_REG_TIM_TIMER_VALUE_Msk (0xffffffUL) /*!< TIM_TIMER_VALUE（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                          TIMER3                                           ================ */
/* =========================================================================================================================== */

/* ===============================================  TIMER3_CAPTURE_GPIO1_REG  ================================================ */
#define TIMER3_TIMER3_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Pos (0UL) /*!< TIM_CAPTURE_GPIO1（位0）*/
#define TIMER3_TIMER3_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO1（位域掩码：0xffffff）*/
/* ===============================================  TIMER3_CAPTURE_GPIO2_REG  ================================================ */
#define TIMER3_TIMER3_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Pos (0UL) /*!< TIM_CAPTURE_GPIO2（位0）*/
#define TIMER3_TIMER3_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO2（位域掩码：0xffffff）*/
/* =================================================  TIMER3_CLEAR_IRQ_REG  ================================================== */
#define TIMER3_TIMER3_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Pos (0UL)         /*!< TIM_CLEAR_IRQ（位0）*/
#define TIMER3_TIMER3_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Msk (0x1UL)       /*!< TIM_CLEAR_IRQ（位字段掩码：0x01）*/
/* ====================================================  TIMER3_CTRL_REG  ==================================================== */
#define TIMER3_TIMER3_CTRL_REG_TIM_CLK_EN_Pos (8UL)                 /*!< TIM_CLK_EN（位8）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_CLK_EN_Msk (0x100UL)             /*!< TIM_CLK_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_SYS_CLK_EN_Pos (7UL)             /*!< TIM_SYS_CLK_EN（第7位）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_SYS_CLK_EN_Msk (0x80UL)          /*!< TIM_SYS_CLK_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_FREE_RUN_MODE_EN_Pos (6UL)       /*!< TIM_FREE_RUN_MODE_EN（位6）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_FREE_RUN_MODE_EN_Msk (0x40UL)    /*!< TIM_FREE_RUN_MODE_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_IRQ_EN_Pos (5UL)                 /*!< TIM_IRQ_EN（第5位）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_IRQ_EN_Msk (0x20UL)              /*!< TIM_IRQ_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Pos (4UL)      /*!< TIM_IN2_EVENT_FALL_EN（位4）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Msk (0x10UL)   /*!< TIM_IN2_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Pos (3UL)      /*!< TIM_IN1_EVENT_FALL_EN（位3）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Msk (0x8UL)    /*!< TIM_IN1_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_COUNT_DOWN_EN_Pos (2UL)          /*!< TIM_COUNT_DOWN_EN（位2）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_COUNT_DOWN_EN_Msk (0x4UL)        /*!< TIM_COUNT_DOWN_EN（位字段掩码：0x01）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_EN_Pos (0UL)                     /*!< TIM_EN（位0）*/
#define TIMER3_TIMER3_CTRL_REG_TIM_EN_Msk (0x1UL)                   /*!< TIM_EN（位域掩码：0x01）*/
/* =================================================  TIMER3_GPIO1_CONF_REG  ================================================= */
#define TIMER3_TIMER3_GPIO1_CONF_REG_TIM_GPIO1_CONF_Pos (0UL)       /*!< TIM_GPIO1_CONF（位0）*/
#define TIMER3_TIMER3_GPIO1_CONF_REG_TIM_GPIO1_CONF_Msk (0x3fUL)    /*!< TIM_GPIO1_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER3_GPIO2_CONF_REG  ================================================= */
#define TIMER3_TIMER3_GPIO2_CONF_REG_TIM_GPIO2_CONF_Pos (0UL)       /*!< TIM_GPIO2_CONF（位0）*/
#define TIMER3_TIMER3_GPIO2_CONF_REG_TIM_GPIO2_CONF_Msk (0x3fUL)    /*!< TIM_GPIO2_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER3_PRESCALER_REG  ================================================== */
#define TIMER3_TIMER3_PRESCALER_REG_TIM_PRESCALER_Pos (0UL)         /*!< TIM_PRESCALER（位0）*/
#define TIMER3_TIMER3_PRESCALER_REG_TIM_PRESCALER_Msk (0x1fUL)      /*!< TIM_PRESCALER（位字段掩码：0x1f）*/
/* ===============================================  TIMER3_PRESCALER_VAL_REG  ================================================ */
#define TIMER3_TIMER3_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Pos (0UL) /*!< TIM_PRESCALER_VAL（位0）*/
#define TIMER3_TIMER3_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Msk (0x1fUL) /*!< TIM_PRESCALER_VAL（位字段掩码：0x1f）*/
/* ===================================================  TIMER3_PWM_DC_REG  =================================================== */
#define TIMER3_TIMER3_PWM_DC_REG_TIM_PWM_DC_Pos (0UL)               /*!< TIM_PWM_DC（位0）*/
#define TIMER3_TIMER3_PWM_DC_REG_TIM_PWM_DC_Msk (0xffffUL)          /*!< TIM_PWM_DC（位字段掩码：0xffff）*/
/* ==================================================  TIMER3_PWM_FREQ_REG  ================================================== */
#define TIMER3_TIMER3_PWM_FREQ_REG_TIM_PWM_FREQ_Pos (0UL)           /*!< TIM_PWM_FREQ（位0）*/
#define TIMER3_TIMER3_PWM_FREQ_REG_TIM_PWM_FREQ_Msk (0xffffUL)      /*!< TIM_PWM_FREQ（位字段掩码：0xffff）*/
/* ===================================================  TIMER3_RELOAD_REG  =================================================== */
#define TIMER3_TIMER3_RELOAD_REG_TIM_RELOAD_Pos (0UL)               /*!< TIM_RELOAD（位0）*/
#define TIMER3_TIMER3_RELOAD_REG_TIM_RELOAD_Msk (0xffffffUL)        /*!< TIM_RELOAD（位字段掩码：0xffffff）*/
/* ===================================================  TIMER3_STATUS_REG  =================================================== */
#define TIMER3_TIMER3_STATUS_REG_TIM_ONESHOT_PHASE_Pos (2UL)        /*!< TIM_ONESHOT_PHASE（位2）*/
#define TIMER3_TIMER3_STATUS_REG_TIM_ONESHOT_PHASE_Msk (0xcUL)      /*!< TIM_ONESHOT_PHASE（位字段掩码：0x03）*/
#define TIMER3_TIMER3_STATUS_REG_TIM_IN2_STATE_Pos (1UL)            /*!< TIM_IN2_STATE（位1）*/
#define TIMER3_TIMER3_STATUS_REG_TIM_IN2_STATE_Msk (0x2UL)          /*!< TIM_IN2_STATE（位字段掩码：0x01）*/
#define TIMER3_TIMER3_STATUS_REG_TIM_IN1_STATE_Pos (0UL)            /*!< TIM_IN1_STATE（位0）*/
#define TIMER3_TIMER3_STATUS_REG_TIM_IN1_STATE_Msk (0x1UL)          /*!< TIM_IN1_STATE（位字段掩码：0x01）*/
/* =================================================  TIMER3_TIMER_VAL_REG  ================================================== */
#define TIMER3_TIMER3_TIMER_VAL_REG_TIM_TIMER_VALUE_Pos (0UL)       /*!< TIM_TIMER_VALUE（位0）*/
#define TIMER3_TIMER3_TIMER_VAL_REG_TIM_TIMER_VALUE_Msk (0xffffffUL) /*!< TIM_TIMER_VALUE（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                          TIMER4                                           ================ */
/* =========================================================================================================================== */

/* ===============================================  TIMER4_CAPTURE_GPIO1_REG  ================================================ */
#define TIMER4_TIMER4_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Pos (0UL) /*!< TIM_CAPTURE_GPIO1（位0）*/
#define TIMER4_TIMER4_CAPTURE_GPIO1_REG_TIM_CAPTURE_GPIO1_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO1（位域掩码：0xffffff）*/
/* ===============================================  TIMER4_CAPTURE_GPIO2_REG  ================================================ */
#define TIMER4_TIMER4_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Pos (0UL) /*!< TIM_CAPTURE_GPIO2（位0）*/
#define TIMER4_TIMER4_CAPTURE_GPIO2_REG_TIM_CAPTURE_GPIO2_Msk (0xffffffUL) /*!< TIM_CAPTURE_GPIO2（位域掩码：0xffffff）*/
/* =================================================  TIMER4_CLEAR_IRQ_REG  ================================================== */
#define TIMER4_TIMER4_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Pos (0UL)         /*!< TIM_CLEAR_IRQ（位0）*/
#define TIMER4_TIMER4_CLEAR_IRQ_REG_TIM_CLEAR_IRQ_Msk (0x1UL)       /*!< TIM_CLEAR_IRQ（位字段掩码：0x01）*/
/* ====================================================  TIMER4_CTRL_REG  ==================================================== */
#define TIMER4_TIMER4_CTRL_REG_TIM_CLK_EN_Pos (8UL)                 /*!< TIM_CLK_EN（位8）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_CLK_EN_Msk (0x100UL)             /*!< TIM_CLK_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_SYS_CLK_EN_Pos (7UL)             /*!< TIM_SYS_CLK_EN（第7位）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_SYS_CLK_EN_Msk (0x80UL)          /*!< TIM_SYS_CLK_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_FREE_RUN_MODE_EN_Pos (6UL)       /*!< TIM_FREE_RUN_MODE_EN（位6）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_FREE_RUN_MODE_EN_Msk (0x40UL)    /*!< TIM_FREE_RUN_MODE_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_IRQ_EN_Pos (5UL)                 /*!< TIM_IRQ_EN（第5位）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_IRQ_EN_Msk (0x20UL)              /*!< TIM_IRQ_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Pos (4UL)      /*!< TIM_IN2_EVENT_FALL_EN（位4）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Msk (0x10UL)   /*!< TIM_IN2_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Pos (3UL)      /*!< TIM_IN1_EVENT_FALL_EN（位3）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Msk (0x8UL)    /*!< TIM_IN1_EVENT_FALL_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_COUNT_DOWN_EN_Pos (2UL)          /*!< TIM_COUNT_DOWN_EN（位2）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_COUNT_DOWN_EN_Msk (0x4UL)        /*!< TIM_COUNT_DOWN_EN（位字段掩码：0x01）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_EN_Pos (0UL)                     /*!< TIM_EN（位0）*/
#define TIMER4_TIMER4_CTRL_REG_TIM_EN_Msk (0x1UL)                   /*!< TIM_EN（位域掩码：0x01）*/
/* =================================================  TIMER4_GPIO1_CONF_REG  ================================================= */
#define TIMER4_TIMER4_GPIO1_CONF_REG_TIM_GPIO1_CONF_Pos (0UL)       /*!< TIM_GPIO1_CONF（位0）*/
#define TIMER4_TIMER4_GPIO1_CONF_REG_TIM_GPIO1_CONF_Msk (0x3fUL)    /*!< TIM_GPIO1_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER4_GPIO2_CONF_REG  ================================================= */
#define TIMER4_TIMER4_GPIO2_CONF_REG_TIM_GPIO2_CONF_Pos (0UL)       /*!< TIM_GPIO2_CONF（位0）*/
#define TIMER4_TIMER4_GPIO2_CONF_REG_TIM_GPIO2_CONF_Msk (0x3fUL)    /*!< TIM_GPIO2_CONF（位域掩码：0x3f）*/
/* =================================================  TIMER4_PRESCALER_REG  ================================================== */
#define TIMER4_TIMER4_PRESCALER_REG_TIM_PRESCALER_Pos (0UL)         /*!< TIM_PRESCALER（位0）*/
#define TIMER4_TIMER4_PRESCALER_REG_TIM_PRESCALER_Msk (0x1fUL)      /*!< TIM_PRESCALER（位字段掩码：0x1f）*/
/* ===============================================  TIMER4_PRESCALER_VAL_REG  ================================================ */
#define TIMER4_TIMER4_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Pos (0UL) /*!< TIM_PRESCALER_VAL（位0）*/
#define TIMER4_TIMER4_PRESCALER_VAL_REG_TIM_PRESCALER_VAL_Msk (0x1fUL) /*!< TIM_PRESCALER_VAL（位字段掩码：0x1f）*/
/* ===================================================  TIMER4_PWM_DC_REG  =================================================== */
#define TIMER4_TIMER4_PWM_DC_REG_TIM_PWM_DC_Pos (0UL)               /*!< TIM_PWM_DC（位0）*/
#define TIMER4_TIMER4_PWM_DC_REG_TIM_PWM_DC_Msk (0xffffUL)          /*!< TIM_PWM_DC（位字段掩码：0xffff）*/
/* ==================================================  TIMER4_PWM_FREQ_REG  ================================================== */
#define TIMER4_TIMER4_PWM_FREQ_REG_TIM_PWM_FREQ_Pos (0UL)           /*!< TIM_PWM_FREQ（位0）*/
#define TIMER4_TIMER4_PWM_FREQ_REG_TIM_PWM_FREQ_Msk (0xffffUL)      /*!< TIM_PWM_FREQ（位字段掩码：0xffff）*/
/* ===================================================  TIMER4_RELOAD_REG  =================================================== */
#define TIMER4_TIMER4_RELOAD_REG_TIM_RELOAD_Pos (0UL)               /*!< TIM_RELOAD（位0）*/
#define TIMER4_TIMER4_RELOAD_REG_TIM_RELOAD_Msk (0xffffffUL)        /*!< TIM_RELOAD（位字段掩码：0xffffff）*/
/* ===================================================  TIMER4_STATUS_REG  =================================================== */
#define TIMER4_TIMER4_STATUS_REG_TIM_ONESHOT_PHASE_Pos (2UL)        /*!< TIM_ONESHOT_PHASE（位2）*/
#define TIMER4_TIMER4_STATUS_REG_TIM_ONESHOT_PHASE_Msk (0xcUL)      /*!< TIM_ONESHOT_PHASE（位字段掩码：0x03）*/
#define TIMER4_TIMER4_STATUS_REG_TIM_IN2_STATE_Pos (1UL)            /*!< TIM_IN2_STATE（位1）*/
#define TIMER4_TIMER4_STATUS_REG_TIM_IN2_STATE_Msk (0x2UL)          /*!< TIM_IN2_STATE（位字段掩码：0x01）*/
#define TIMER4_TIMER4_STATUS_REG_TIM_IN1_STATE_Pos (0UL)            /*!< TIM_IN1_STATE（位0）*/
#define TIMER4_TIMER4_STATUS_REG_TIM_IN1_STATE_Msk (0x1UL)          /*!< TIM_IN1_STATE（位字段掩码：0x01）*/
/* =================================================  TIMER4_TIMER_VAL_REG  ================================================== */
#define TIMER4_TIMER4_TIMER_VAL_REG_TIM_TIMER_VALUE_Pos (0UL)       /*!< TIM_TIMER_VALUE（位0）*/
#define TIMER4_TIMER4_TIMER_VAL_REG_TIM_TIMER_VALUE_Msk (0xffffffUL) /*!< TIM_TIMER_VALUE（位字段掩码：0xffffff）*/


/* =========================================================================================================================== */
/* ================                                           TRNG                                            ================ */
/* =========================================================================================================================== */

/* =====================================================  TRNG_CTRL_REG  ===================================================== */
#define TRNG_TRNG_CTRL_REG_TRNG_ENABLE_Pos (0UL)                    /*!< TRNG_ENABLE（位0）*/
#define TRNG_TRNG_CTRL_REG_TRNG_ENABLE_Msk (0x1UL)                  /*!< TRNG_ENABLE（位字段掩码：0x01）*/
/* ===================================================  TRNG_FIFOLVL_REG  ==================================================== */
#define TRNG_TRNG_FIFOLVL_REG_TRNG_FIFOFULL_Pos (5UL)               /*!< TRNG_FIFOFULL（位5）*/
#define TRNG_TRNG_FIFOLVL_REG_TRNG_FIFOFULL_Msk (0x20UL)            /*!< TRNG_FIFOFULL（位字段掩码：0x01）*/
#define TRNG_TRNG_FIFOLVL_REG_TRNG_FIFOLVL_Pos (0UL)                /*!< TRNG_FIFOLVL（位0）*/
#define TRNG_TRNG_FIFOLVL_REG_TRNG_FIFOLVL_Msk (0x1fUL)             /*!< TRNG_FIFOLVL（位域掩码：0x1f）*/
/* =====================================================  TRNG_VER_REG  ====================================================== */
#define TRNG_TRNG_VER_REG_TRNG_MAJ_Pos    (24UL)                    /*!< TRNG_MAJ（位24）*/
#define TRNG_TRNG_VER_REG_TRNG_MAJ_Msk    (0xff000000UL)            /*!< TRNG_MAJ（位域掩码：0xff）*/
#define TRNG_TRNG_VER_REG_TRNG_MIN_Pos    (16UL)                    /*!< TRNG_MIN（位16）*/
#define TRNG_TRNG_VER_REG_TRNG_MIN_Msk    (0xff0000UL)              /*!< TRNG_MIN（位域掩码：0xff）*/
#define TRNG_TRNG_VER_REG_TRNG_SVN_Pos    (0UL)                     /*!< TRNG_SVN（位0）*/
#define TRNG_TRNG_VER_REG_TRNG_SVN_Msk    (0xffffUL)                /*!< TRNG_SVN（位域掩码：0xffff）*/


/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */

/* =====================================================  UART_CTR_REG  ====================================================== */
#define UART_UART_CTR_REG_UART_CTR_Pos    (0UL)                     /*!< UART_CTR（位0）*/
#define UART_UART_CTR_REG_UART_CTR_Msk    (0xffffffffUL)            /*!< UART_CTR（位域掩码：0xffffffff）*/
/* =====================================================  UART_DLF_REG  ====================================================== */
#define UART_UART_DLF_REG_UART_DLF_Pos    (0UL)                     /*!< UART_DLF（位0）*/
#define UART_UART_DLF_REG_UART_DLF_Msk    (0xfUL)                   /*!< UART_DLF（位域掩码：0x0f）*/
/* ====================================================  UART_DMASA_REG  ===================================================== */
#define UART_UART_DMASA_REG_UART_DMASA_Pos (0UL)                    /*!< UART_DMASA（位0）*/
#define UART_UART_DMASA_REG_UART_DMASA_Msk (0x1UL)                  /*!< UART_DMASA（位域掩码：0x01）*/
/* =====================================================  UART_HTX_REG  ====================================================== */
#define UART_UART_HTX_REG_UART_HALT_TX_Pos (0UL)                    /*!< UART_HALT_TX（位0）*/
#define UART_UART_HTX_REG_UART_HALT_TX_Msk (0x1UL)                  /*!< UART_HALT_TX（位域掩码：0x01）*/
/* ===================================================  UART_IER_DLH_REG  ==================================================== */
#define UART_UART_IER_DLH_REG_PTIME_DLH7_Pos (7UL)                  /*!< PTIME_DLH7（第7位）*/
#define UART_UART_IER_DLH_REG_PTIME_DLH7_Msk (0x80UL)               /*!< PTIME_DLH7（位域掩码：0x01）*/
#define UART_UART_IER_DLH_REG_DLH6_5_Pos  (5UL)                     /*!< DLH6_5（第5位）*/
#define UART_UART_IER_DLH_REG_DLH6_5_Msk  (0x60UL)                  /*!< DLH6_5（位域掩码：0x03）*/
#define UART_UART_IER_DLH_REG_ELCOLR_DLH4_Pos (4UL)                 /*!< ELCOLR_DLH4（位4）*/
#define UART_UART_IER_DLH_REG_ELCOLR_DLH4_Msk (0x10UL)              /*!< ELCOLR_DLH4（位字段掩码：0x01）*/
#define UART_UART_IER_DLH_REG_EDSSI_DLH3_Pos (3UL)                  /*!< EDSSI_DLH3（位3）*/
#define UART_UART_IER_DLH_REG_EDSSI_DLH3_Msk (0x8UL)                /*!< EDSSI_DLH3（位字段掩码：0x01）*/
#define UART_UART_IER_DLH_REG_ELSI_DLH2_Pos (2UL)                   /*!< ELSI_DLH2（位2）*/
#define UART_UART_IER_DLH_REG_ELSI_DLH2_Msk (0x4UL)                 /*!< ELSI_DLH2（位字段掩码：0x01）*/
#define UART_UART_IER_DLH_REG_ETBEI_DLH1_Pos (1UL)                  /*!< ETBEI_DLH1（位1）*/
#define UART_UART_IER_DLH_REG_ETBEI_DLH1_Msk (0x2UL)                /*!< ETBEI_DLH1（位域掩码：0x01）*/
#define UART_UART_IER_DLH_REG_ERBFI_DLH0_Pos (0UL)                  /*!< ERBFI_DLH0（位0）*/
#define UART_UART_IER_DLH_REG_ERBFI_DLH0_Msk (0x1UL)                /*!< ERBFI_DLH0（位字段掩码：0x01）*/
/* ===================================================  UART_IIR_FCR_REG  ==================================================== */
#define UART_UART_IIR_FCR_REG_IIR_FCR_Pos (0UL)                     /*!< IIR_FCR（位0）*/
#define UART_UART_IIR_FCR_REG_IIR_FCR_Msk (0xffUL)                  /*!< IIR_FCR（位域掩码：0xff）*/
/* =====================================================  UART_LCR_REG  ====================================================== */
#define UART_UART_LCR_REG_UART_DLAB_Pos   (7UL)                     /*!< UART_DLAB（位7）*/
#define UART_UART_LCR_REG_UART_DLAB_Msk   (0x80UL)                  /*!< UART_DLAB（位域掩码：0x01）*/
#define UART_UART_LCR_REG_UART_BC_Pos     (6UL)                     /*!< UART_BC（位6）*/
#define UART_UART_LCR_REG_UART_BC_Msk     (0x40UL)                  /*!< UART_BC（位域掩码：0x01）*/
#define UART_UART_LCR_REG_UART_EPS_Pos    (4UL)                     /*!< UART_EPS（位4）*/
#define UART_UART_LCR_REG_UART_EPS_Msk    (0x10UL)                  /*!< UART_EPS（位域掩码：0x01）*/
#define UART_UART_LCR_REG_UART_PEN_Pos    (3UL)                     /*!< UART_PEN（位3）*/
#define UART_UART_LCR_REG_UART_PEN_Msk    (0x8UL)                   /*!< UART_PEN（位字段掩码：0x01）*/
#define UART_UART_LCR_REG_UART_STOP_Pos   (2UL)                     /*!< UART_STOP（位2）*/
#define UART_UART_LCR_REG_UART_STOP_Msk   (0x4UL)                   /*!< UART_STOP（位域掩码：0x01）*/
#define UART_UART_LCR_REG_UART_DLS_Pos    (0UL)                     /*!< UART_DLS（位0）*/
#define UART_UART_LCR_REG_UART_DLS_Msk    (0x3UL)                   /*!< UART_DLS（位域掩码：0x03）*/
/* =====================================================  UART_LSR_REG  ====================================================== */
#define UART_UART_LSR_REG_UART_RFE_Pos    (7UL)                     /*!< UART_RFE（位7）*/
#define UART_UART_LSR_REG_UART_RFE_Msk    (0x80UL)                  /*!< UART_RFE（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_TEMT_Pos   (6UL)                     /*!< UART_TEMT（位6）*/
#define UART_UART_LSR_REG_UART_TEMT_Msk   (0x40UL)                  /*!< UART_TEMT（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_THRE_Pos   (5UL)                     /*!< UART_THRE（位5）*/
#define UART_UART_LSR_REG_UART_THRE_Msk   (0x20UL)                  /*!< UART_THRE（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_BI_Pos     (4UL)                     /*!< UART_BI（位4）*/
#define UART_UART_LSR_REG_UART_BI_Msk     (0x10UL)                  /*!< UART_BI（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_FE_Pos     (3UL)                     /*!< UART_FE（位3）*/
#define UART_UART_LSR_REG_UART_FE_Msk     (0x8UL)                   /*!< UART_FE（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_PE_Pos     (2UL)                     /*!< UART_PE（位2）*/
#define UART_UART_LSR_REG_UART_PE_Msk     (0x4UL)                   /*!< UART_PE（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_OE_Pos     (1UL)                     /*!< UART_OE（位1）*/
#define UART_UART_LSR_REG_UART_OE_Msk     (0x2UL)                   /*!< UART_OE（位域掩码：0x01）*/
#define UART_UART_LSR_REG_UART_DR_Pos     (0UL)                     /*!< UART_DR（位0）*/
#define UART_UART_LSR_REG_UART_DR_Msk     (0x1UL)                   /*!< UART_DR（位域掩码：0x01）*/
/* =====================================================  UART_MCR_REG  ====================================================== */
#define UART_UART_MCR_REG_UART_LB_Pos     (4UL)                     /*!< UART_LB（位4）*/
#define UART_UART_MCR_REG_UART_LB_Msk     (0x10UL)                  /*!< UART_LB（位域掩码：0x01）*/
/* =================================================  UART_RBR_THR_DLL_REG  ================================================== */
#define UART_UART_RBR_THR_DLL_REG_RBR_THR_DLL_Pos (0UL)             /*!< RBR_THR_DLL（位0）*/
#define UART_UART_RBR_THR_DLL_REG_RBR_THR_DLL_Msk (0xffUL)          /*!< RBR_THR_DLL（位域掩码：0xff）*/
/* =====================================================  UART_RFL_REG  ====================================================== */
#define UART_UART_RFL_REG_UART_RECEIVE_FIFO_LEVEL_Pos (0UL)         /*!< UART_RECEIVE_FIFO_LEVEL（位0）*/
#define UART_UART_RFL_REG_UART_RECEIVE_FIFO_LEVEL_Msk (0x1fUL)      /*!< UART_RECEIVE_FIFO_LEVEL（位域掩码：0x1f）*/
/* =====================================================  UART_SBCR_REG  ===================================================== */
#define UART_UART_SBCR_REG_UART_SHADOW_BREAK_CONTROL_Pos (0UL)      /*!< UART_SHADOW_BREAK_CONTROL（位0）*/
#define UART_UART_SBCR_REG_UART_SHADOW_BREAK_CONTROL_Msk (0x1UL)    /*!< UART_SHADOW_BREAK_CONTROL（位域掩码：0x01）*/
/* =====================================================  UART_SCR_REG  ====================================================== */
#define UART_UART_SCR_REG_UART_SCRATCH_PAD_Pos (0UL)                /*!< UART_SCRATCH_PAD（位0）*/
#define UART_UART_SCR_REG_UART_SCRATCH_PAD_Msk (0xffUL)             /*!< UART_SCRATCH_PAD（位域掩码：0xff）*/
/* ====================================================  UART_SDMAM_REG  ===================================================== */
#define UART_UART_SDMAM_REG_UART_SHADOW_DMA_MODE_Pos (0UL)          /*!< UART_SHADOW_DMA_MODE（位0）*/
#define UART_UART_SDMAM_REG_UART_SHADOW_DMA_MODE_Msk (0x1UL)        /*!< UART_SHADOW_DMA_MODE（位域掩码：0x01）*/
/* =====================================================  UART_SFE_REG  ====================================================== */
#define UART_UART_SFE_REG_UART_SHADOW_FIFO_ENABLE_Pos (0UL)         /*!< UART_SHADOW_FIFO_ENABLE（位0）*/
#define UART_UART_SFE_REG_UART_SHADOW_FIFO_ENABLE_Msk (0x1UL)       /*!< UART_SHADOW_FIFO_ENABLE（位字段掩码：0x01）*/
/* ==================================================  UART_SRBR_STHR0_REG  ================================================== */
#define UART_UART_SRBR_STHR0_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR0_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART_SRBR_STHR10_REG  ================================================== */
#define UART_UART_SRBR_STHR10_REG_SRBR_STHRx_Pos (0UL)              /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR10_REG_SRBR_STHRx_Msk (0xffUL)           /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART_SRBR_STHR11_REG  ================================================== */
#define UART_UART_SRBR_STHR11_REG_SRBR_STHRx_Pos (0UL)              /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR11_REG_SRBR_STHRx_Msk (0xffUL)           /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART_SRBR_STHR12_REG  ================================================== */
#define UART_UART_SRBR_STHR12_REG_SRBR_STHRx_Pos (0UL)              /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR12_REG_SRBR_STHRx_Msk (0xffUL)           /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART_SRBR_STHR13_REG  ================================================== */
#define UART_UART_SRBR_STHR13_REG_SRBR_STHRx_Pos (0UL)              /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR13_REG_SRBR_STHRx_Msk (0xffUL)           /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART_SRBR_STHR14_REG  ================================================== */
#define UART_UART_SRBR_STHR14_REG_SRBR_STHRx_Pos (0UL)              /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR14_REG_SRBR_STHRx_Msk (0xffUL)           /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART_SRBR_STHR15_REG  ================================================== */
#define UART_UART_SRBR_STHR15_REG_SRBR_STHRx_Pos (0UL)              /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR15_REG_SRBR_STHRx_Msk (0xffUL)           /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR1_REG  ================================================== */
#define UART_UART_SRBR_STHR1_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR1_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR2_REG  ================================================== */
#define UART_UART_SRBR_STHR2_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR2_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR3_REG  ================================================== */
#define UART_UART_SRBR_STHR3_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR3_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR4_REG  ================================================== */
#define UART_UART_SRBR_STHR4_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR4_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR5_REG  ================================================== */
#define UART_UART_SRBR_STHR5_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR5_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR6_REG  ================================================== */
#define UART_UART_SRBR_STHR6_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR6_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR7_REG  ================================================== */
#define UART_UART_SRBR_STHR7_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR7_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR8_REG  ================================================== */
#define UART_UART_SRBR_STHR8_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR8_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* ==================================================  UART_SRBR_STHR9_REG  ================================================== */
#define UART_UART_SRBR_STHR9_REG_SRBR_STHRx_Pos (0UL)               /*!< SRBR_STHRx（位0）*/
#define UART_UART_SRBR_STHR9_REG_SRBR_STHRx_Msk (0xffUL)            /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =====================================================  UART_SRR_REG  ====================================================== */
#define UART_UART_SRR_REG_UART_XFR_Pos    (2UL)                     /*!< UART_XFR（位2）*/
#define UART_UART_SRR_REG_UART_XFR_Msk    (0x4UL)                   /*!< UART_XFR（位域掩码：0x01）*/
#define UART_UART_SRR_REG_UART_RFR_Pos    (1UL)                     /*!< UART_RFR（位1）*/
#define UART_UART_SRR_REG_UART_RFR_Msk    (0x2UL)                   /*!< UART_RFR（位域掩码：0x01）*/
#define UART_UART_SRR_REG_UART_UR_Pos     (0UL)                     /*!< UART_UR（位0）*/
#define UART_UART_SRR_REG_UART_UR_Msk     (0x1UL)                   /*!< UART_UR（位域掩码：0x01）*/
/* =====================================================  UART_SRT_REG  ====================================================== */
#define UART_UART_SRT_REG_UART_SHADOW_RCVR_TRIGGER_Pos (0UL)        /*!< UART_SHADOW_RCVR_TRIGGER（位0）*/
#define UART_UART_SRT_REG_UART_SHADOW_RCVR_TRIGGER_Msk (0x3UL)      /*!< UART_SHADOW_RCVR_TRIGGER（位域掩码：0x03）*/
/* =====================================================  UART_STET_REG  ===================================================== */
#define UART_UART_STET_REG_UART_SHADOW_TX_EMPTY_TRIGGER_Pos (0UL)   /*!< UART_SHADOW_TX_EMPTY_TRIGGER（位0）*/
#define UART_UART_STET_REG_UART_SHADOW_TX_EMPTY_TRIGGER_Msk (0x3UL) /*!< UART_SHADOW_TX_EMPTY_TRIGGER（位域掩码：0x03）*/
/* =====================================================  UART_TFL_REG  ====================================================== */
#define UART_UART_TFL_REG_UART_TRANSMIT_FIFO_LEVEL_Pos (0UL)        /*!< UART_TRANSMIT_FIFO_LEVEL（位0）*/
#define UART_UART_TFL_REG_UART_TRANSMIT_FIFO_LEVEL_Msk (0x1fUL)     /*!< UART_TRANSMIT_FIFO_LEVEL（位域掩码：0x1f）*/
/* =====================================================  UART_UCV_REG  ====================================================== */
#define UART_UART_UCV_REG_UART_UCV_Pos    (0UL)                     /*!< UART_UCV（位0）*/
#define UART_UART_UCV_REG_UART_UCV_Msk    (0xffffffffUL)            /*!< UART_UCV（位域掩码：0xffffffff）*/
/* =====================================================  UART_USR_REG  ====================================================== */
#define UART_UART_USR_REG_UART_RFF_Pos    (4UL)                     /*!< UART_RFF（位4）*/
#define UART_UART_USR_REG_UART_RFF_Msk    (0x10UL)                  /*!< UART_RFF（位域掩码：0x01）*/
#define UART_UART_USR_REG_UART_RFNE_Pos   (3UL)                     /*!< UART_RFNE（位3）*/
#define UART_UART_USR_REG_UART_RFNE_Msk   (0x8UL)                   /*!< UART_RFNE（位域掩码：0x01）*/
#define UART_UART_USR_REG_UART_TFE_Pos    (2UL)                     /*!< UART_TFE（位2）*/
#define UART_UART_USR_REG_UART_TFE_Msk    (0x4UL)                   /*!< UART_TFE（位字段掩码：0x01）*/
#define UART_UART_USR_REG_UART_TFNF_Pos   (1UL)                     /*!< UART_TFNF（位1）*/
#define UART_UART_USR_REG_UART_TFNF_Msk   (0x2UL)                   /*!< UART_TFNF（位域掩码：0x01）*/
#define UART_UART_USR_REG_UART_BUSY_Pos   (0UL)                     /*!< UART_BUSY（位0）*/
#define UART_UART_USR_REG_UART_BUSY_Msk   (0x1UL)                   /*!< UART_BUSY（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                           UART2                                           ================ */
/* =========================================================================================================================== */

/* =====================================================  UART2_CTR_REG  ===================================================== */
#define UART2_UART2_CTR_REG_UART_CTR_Pos  (0UL)                     /*!< UART_CTR（位0）*/
#define UART2_UART2_CTR_REG_UART_CTR_Msk  (0xffffffffUL)            /*!< UART_CTR（位域掩码：0xffffffff）*/
/* =====================================================  UART2_DLF_REG  ===================================================== */
#define UART2_UART2_DLF_REG_UART_DLF_Pos  (0UL)                     /*!< UART_DLF（位0）*/
#define UART2_UART2_DLF_REG_UART_DLF_Msk  (0xfUL)                   /*!< UART_DLF（位域掩码：0x0f）*/
/* ====================================================  UART2_DMASA_REG  ==================================================== */
#define UART2_UART2_DMASA_REG_UART_DMASA_Pos (0UL)                  /*!< UART_DMASA（位0）*/
#define UART2_UART2_DMASA_REG_UART_DMASA_Msk (0x1UL)                /*!< UART_DMASA（位域掩码：0x01）*/
/* =====================================================  UART2_HTX_REG  ===================================================== */
#define UART2_UART2_HTX_REG_UART_HALT_TX_Pos (0UL)                  /*!< UART_HALT_TX（位0）*/
#define UART2_UART2_HTX_REG_UART_HALT_TX_Msk (0x1UL)                /*!< UART_HALT_TX（位域掩码：0x01）*/
/* ===================================================  UART2_IER_DLH_REG  =================================================== */
#define UART2_UART2_IER_DLH_REG_PTIME_DLH7_Pos (7UL)                /*!< PTIME_DLH7（第7位）*/
#define UART2_UART2_IER_DLH_REG_PTIME_DLH7_Msk (0x80UL)             /*!< PTIME_DLH7（位域掩码：0x01）*/
#define UART2_UART2_IER_DLH_REG_DLH6_5_Pos (5UL)                    /*!< DLH6_5（第5位）*/
#define UART2_UART2_IER_DLH_REG_DLH6_5_Msk (0x60UL)                 /*!< DLH6_5（位域掩码：0x03）*/
#define UART2_UART2_IER_DLH_REG_ELCOLR_DLH4_Pos (4UL)               /*!< ELCOLR_DLH4（位4）*/
#define UART2_UART2_IER_DLH_REG_ELCOLR_DLH4_Msk (0x10UL)            /*!< ELCOLR_DLH4（位字段掩码：0x01）*/
#define UART2_UART2_IER_DLH_REG_EDSSI_DLH3_Pos (3UL)                /*!< EDSSI_DLH3（位3）*/
#define UART2_UART2_IER_DLH_REG_EDSSI_DLH3_Msk (0x8UL)              /*!< EDSSI_DLH3（位字段掩码：0x01）*/
#define UART2_UART2_IER_DLH_REG_ELSI_DLH2_Pos (2UL)                 /*!< ELSI_DLH2（位2）*/
#define UART2_UART2_IER_DLH_REG_ELSI_DLH2_Msk (0x4UL)               /*!< ELSI_DLH2（位字段掩码：0x01）*/
#define UART2_UART2_IER_DLH_REG_ETBEI_DLH1_Pos (1UL)                /*!< ETBEI_DLH1（位1）*/
#define UART2_UART2_IER_DLH_REG_ETBEI_DLH1_Msk (0x2UL)              /*!< ETBEI_DLH1（位域掩码：0x01）*/
#define UART2_UART2_IER_DLH_REG_ERBFI_DLH0_Pos (0UL)                /*!< ERBFI_DLH0（位0）*/
#define UART2_UART2_IER_DLH_REG_ERBFI_DLH0_Msk (0x1UL)              /*!< ERBFI_DLH0（位字段掩码：0x01）*/
/* ===================================================  UART2_IIR_FCR_REG  =================================================== */
#define UART2_UART2_IIR_FCR_REG_IIR_FCR_Pos (0UL)                   /*!< IIR_FCR（位0）*/
#define UART2_UART2_IIR_FCR_REG_IIR_FCR_Msk (0xffUL)                /*!< IIR_FCR（位域掩码：0xff）*/
/* =====================================================  UART2_LCR_EXT  ===================================================== */
#define UART2_UART2_LCR_EXT_UART_TRANSMIT_MODE_Pos (3UL)            /*!< UART_TRANSMIT_MODE（位3）*/
#define UART2_UART2_LCR_EXT_UART_TRANSMIT_MODE_Msk (0x8UL)          /*!< UART_TRANSMIT_MODE（位字段掩码：0x01）*/
#define UART2_UART2_LCR_EXT_UART_SEND_ADDR_Pos (2UL)                /*!< UART_SEND_ADDR（位2）*/
#define UART2_UART2_LCR_EXT_UART_SEND_ADDR_Msk (0x4UL)              /*!< UART_SEND_ADDR（位字段掩码：0x01）*/
#define UART2_UART2_LCR_EXT_UART_ADDR_MATCH_Pos (1UL)               /*!< UART_ADDR_MATCH（位1）*/
#define UART2_UART2_LCR_EXT_UART_ADDR_MATCH_Msk (0x2UL)             /*!< UART_ADDR_MATCH（位字段掩码：0x01）*/
#define UART2_UART2_LCR_EXT_UART_DLS_E_Pos (0UL)                    /*!< UART_DLS_E（位0）*/
#define UART2_UART2_LCR_EXT_UART_DLS_E_Msk (0x1UL)                  /*!< UART_DLS_E（位域掩码：0x01）*/
/* =====================================================  UART2_LCR_REG  ===================================================== */
#define UART2_UART2_LCR_REG_UART_DLAB_Pos (7UL)                     /*!< UART_DLAB（位7）*/
#define UART2_UART2_LCR_REG_UART_DLAB_Msk (0x80UL)                  /*!< UART_DLAB（位域掩码：0x01）*/
#define UART2_UART2_LCR_REG_UART_BC_Pos   (6UL)                     /*!< UART_BC（位6）*/
#define UART2_UART2_LCR_REG_UART_BC_Msk   (0x40UL)                  /*!< UART_BC（位域掩码：0x01）*/
#define UART2_UART2_LCR_REG_UART_SP_Pos   (5UL)                     /*!< UART_SP（位5）*/
#define UART2_UART2_LCR_REG_UART_SP_Msk   (0x20UL)                  /*!< UART_SP（位域掩码：0x01）*/
#define UART2_UART2_LCR_REG_UART_EPS_Pos  (4UL)                     /*!< UART_EPS（位4）*/
#define UART2_UART2_LCR_REG_UART_EPS_Msk  (0x10UL)                  /*!< UART_EPS（位域掩码：0x01）*/
#define UART2_UART2_LCR_REG_UART_PEN_Pos  (3UL)                     /*!< UART_PEN（位3）*/
#define UART2_UART2_LCR_REG_UART_PEN_Msk  (0x8UL)                   /*!< UART_PEN（位字段掩码：0x01）*/
#define UART2_UART2_LCR_REG_UART_STOP_Pos (2UL)                     /*!< UART_STOP（位2）*/
#define UART2_UART2_LCR_REG_UART_STOP_Msk (0x4UL)                   /*!< UART_STOP（位域掩码：0x01）*/
#define UART2_UART2_LCR_REG_UART_DLS_Pos  (0UL)                     /*!< UART_DLS（位0）*/
#define UART2_UART2_LCR_REG_UART_DLS_Msk  (0x3UL)                   /*!< UART_DLS（位域掩码：0x03）*/
/* =====================================================  UART2_LSR_REG  ===================================================== */
#define UART2_UART2_LSR_REG_UART_ADDR_RCVD_Pos (8UL)                /*!< UART_ADDR_RCVD（位8）*/
#define UART2_UART2_LSR_REG_UART_ADDR_RCVD_Msk (0x100UL)            /*!< UART_ADDR_RCVD（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_RFE_Pos  (7UL)                     /*!< UART_RFE（位7）*/
#define UART2_UART2_LSR_REG_UART_RFE_Msk  (0x80UL)                  /*!< UART_RFE（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_TEMT_Pos (6UL)                     /*!< UART_TEMT（位6）*/
#define UART2_UART2_LSR_REG_UART_TEMT_Msk (0x40UL)                  /*!< UART_TEMT（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_THRE_Pos (5UL)                     /*!< UART_THRE（位5）*/
#define UART2_UART2_LSR_REG_UART_THRE_Msk (0x20UL)                  /*!< UART_THRE（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_BI_Pos   (4UL)                     /*!< UART_BI（位4）*/
#define UART2_UART2_LSR_REG_UART_BI_Msk   (0x10UL)                  /*!< UART_BI（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_FE_Pos   (3UL)                     /*!< UART_FE（位3）*/
#define UART2_UART2_LSR_REG_UART_FE_Msk   (0x8UL)                   /*!< UART_FE（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_PE_Pos   (2UL)                     /*!< UART_PE（位2）*/
#define UART2_UART2_LSR_REG_UART_PE_Msk   (0x4UL)                   /*!< UART_PE（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_OE_Pos   (1UL)                     /*!< UART_OE（位1）*/
#define UART2_UART2_LSR_REG_UART_OE_Msk   (0x2UL)                   /*!< UART_OE（位域掩码：0x01）*/
#define UART2_UART2_LSR_REG_UART_DR_Pos   (0UL)                     /*!< UART_DR（位0）*/
#define UART2_UART2_LSR_REG_UART_DR_Msk   (0x1UL)                   /*!< UART_DR（位域掩码：0x01）*/
/* =====================================================  UART2_MCR_REG  ===================================================== */
#define UART2_UART2_MCR_REG_UART_AFCE_Pos (5UL)                     /*!< UART_AFCE（位5）*/
#define UART2_UART2_MCR_REG_UART_AFCE_Msk (0x20UL)                  /*!< UART_AFCE（位域掩码：0x01）*/
#define UART2_UART2_MCR_REG_UART_LB_Pos   (4UL)                     /*!< UART_LB（位4）*/
#define UART2_UART2_MCR_REG_UART_LB_Msk   (0x10UL)                  /*!< UART_LB（位域掩码：0x01）*/
#define UART2_UART2_MCR_REG_UART_RTS_Pos  (1UL)                     /*!< UART_RTS（位1）*/
#define UART2_UART2_MCR_REG_UART_RTS_Msk  (0x2UL)                   /*!< UART_RTS（位域掩码：0x01）*/
/* =====================================================  UART2_MSR_REG  ===================================================== */
#define UART2_UART2_MSR_REG_UART_CTS_Pos  (4UL)                     /*!< UART_CTS（位4）*/
#define UART2_UART2_MSR_REG_UART_CTS_Msk  (0x10UL)                  /*!< UART_CTS（位域掩码：0x01）*/
#define UART2_UART2_MSR_REG_UART_DCTS_Pos (0UL)                     /*!< UART_DCTS（位0）*/
#define UART2_UART2_MSR_REG_UART_DCTS_Msk (0x1UL)                   /*!< UART_DCTS（位域掩码：0x01）*/
/* =====================================================  UART2_RAR_REG  ===================================================== */
#define UART2_UART2_RAR_REG_UART_RAR_Pos  (0UL)                     /*!< UART_RAR（位0）*/
#define UART2_UART2_RAR_REG_UART_RAR_Msk  (0xffUL)                  /*!< UART_RAR（位域掩码：0xff）*/
/* =================================================  UART2_RBR_THR_DLL_REG  ================================================= */
#define UART2_UART2_RBR_THR_DLL_REG_RBR_THR_9BIT_Pos (8UL)          /*!< RBR_THR_9BIT（位8）*/
#define UART2_UART2_RBR_THR_DLL_REG_RBR_THR_9BIT_Msk (0x100UL)      /*!< RBR_THR_9BIT（位字段掩码：0x01）*/
#define UART2_UART2_RBR_THR_DLL_REG_RBR_THR_DLL_Pos (0UL)           /*!< RBR_THR_DLL（位0）*/
#define UART2_UART2_RBR_THR_DLL_REG_RBR_THR_DLL_Msk (0xffUL)        /*!< RBR_THR_DLL（位域掩码：0xff）*/
/* =====================================================  UART2_RFL_REG  ===================================================== */
#define UART2_UART2_RFL_REG_UART_RECEIVE_FIFO_LEVEL_Pos (0UL)       /*!< UART_RECEIVE_FIFO_LEVEL（位0）*/
#define UART2_UART2_RFL_REG_UART_RECEIVE_FIFO_LEVEL_Msk (0x1fUL)    /*!< UART_RECEIVE_FIFO_LEVEL（位域掩码：0x1f）*/
/* ====================================================  UART2_SBCR_REG  ===================================================== */
#define UART2_UART2_SBCR_REG_UART_SHADOW_BREAK_CONTROL_Pos (0UL)    /*!< UART_SHADOW_BREAK_CONTROL（位0）*/
#define UART2_UART2_SBCR_REG_UART_SHADOW_BREAK_CONTROL_Msk (0x1UL)  /*!< UART_SHADOW_BREAK_CONTROL（位域掩码：0x01）*/
/* =====================================================  UART2_SCR_REG  ===================================================== */
#define UART2_UART2_SCR_REG_UART_SCRATCH_PAD_Pos (0UL)              /*!< UART_SCRATCH_PAD（位0）*/
#define UART2_UART2_SCR_REG_UART_SCRATCH_PAD_Msk (0xffUL)           /*!< UART_SCRATCH_PAD（位域掩码：0xff）*/
/* ====================================================  UART2_SDMAM_REG  ==================================================== */
#define UART2_UART2_SDMAM_REG_UART_SHADOW_DMA_MODE_Pos (0UL)        /*!< UART_SHADOW_DMA_MODE（位0）*/
#define UART2_UART2_SDMAM_REG_UART_SHADOW_DMA_MODE_Msk (0x1UL)      /*!< UART_SHADOW_DMA_MODE（位域掩码：0x01）*/
/* =====================================================  UART2_SFE_REG  ===================================================== */
#define UART2_UART2_SFE_REG_UART_SHADOW_FIFO_ENABLE_Pos (0UL)       /*!< UART_SHADOW_FIFO_ENABLE（位0）*/
#define UART2_UART2_SFE_REG_UART_SHADOW_FIFO_ENABLE_Msk (0x1UL)     /*!< UART_SHADOW_FIFO_ENABLE（位字段掩码：0x01）*/
/* =================================================  UART2_SRBR_STHR0_REG  ================================================== */
#define UART2_UART2_SRBR_STHR0_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR0_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR10_REG  ================================================= */
#define UART2_UART2_SRBR_STHR10_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR10_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR11_REG  ================================================= */
#define UART2_UART2_SRBR_STHR11_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR11_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR12_REG  ================================================= */
#define UART2_UART2_SRBR_STHR12_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR12_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR13_REG  ================================================= */
#define UART2_UART2_SRBR_STHR13_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR13_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR14_REG  ================================================= */
#define UART2_UART2_SRBR_STHR14_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR14_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR15_REG  ================================================= */
#define UART2_UART2_SRBR_STHR15_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR15_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR1_REG  ================================================== */
#define UART2_UART2_SRBR_STHR1_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR1_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR2_REG  ================================================== */
#define UART2_UART2_SRBR_STHR2_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR2_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR3_REG  ================================================== */
#define UART2_UART2_SRBR_STHR3_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR3_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR4_REG  ================================================== */
#define UART2_UART2_SRBR_STHR4_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR4_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR5_REG  ================================================== */
#define UART2_UART2_SRBR_STHR5_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR5_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR6_REG  ================================================== */
#define UART2_UART2_SRBR_STHR6_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR6_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR7_REG  ================================================== */
#define UART2_UART2_SRBR_STHR7_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR7_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR8_REG  ================================================== */
#define UART2_UART2_SRBR_STHR8_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR8_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART2_SRBR_STHR9_REG  ================================================== */
#define UART2_UART2_SRBR_STHR9_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART2_UART2_SRBR_STHR9_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =====================================================  UART2_SRR_REG  ===================================================== */
#define UART2_UART2_SRR_REG_UART_XFR_Pos  (2UL)                     /*!< UART_XFR（位2）*/
#define UART2_UART2_SRR_REG_UART_XFR_Msk  (0x4UL)                   /*!< UART_XFR（位域掩码：0x01）*/
#define UART2_UART2_SRR_REG_UART_RFR_Pos  (1UL)                     /*!< UART_RFR（位1）*/
#define UART2_UART2_SRR_REG_UART_RFR_Msk  (0x2UL)                   /*!< UART_RFR（位域掩码：0x01）*/
#define UART2_UART2_SRR_REG_UART_UR_Pos   (0UL)                     /*!< UART_UR（位0）*/
#define UART2_UART2_SRR_REG_UART_UR_Msk   (0x1UL)                   /*!< UART_UR（位域掩码：0x01）*/
/* ====================================================  UART2_SRTS_REG  ===================================================== */
#define UART2_UART2_SRTS_REG_UART_SHADOW_REQUEST_TO_SEND_Pos (0UL)  /*!< UART_SHADOW_REQUEST_TO_SEND（位0）*/
#define UART2_UART2_SRTS_REG_UART_SHADOW_REQUEST_TO_SEND_Msk (0x1UL) /*!< UART_SHADOW_REQUEST_TO_SEND（位字段掩码：0x01）*/
/* =====================================================  UART2_SRT_REG  ===================================================== */
#define UART2_UART2_SRT_REG_UART_SHADOW_RCVR_TRIGGER_Pos (0UL)      /*!< UART_SHADOW_RCVR_TRIGGER（位0）*/
#define UART2_UART2_SRT_REG_UART_SHADOW_RCVR_TRIGGER_Msk (0x3UL)    /*!< UART_SHADOW_RCVR_TRIGGER（位域掩码：0x03）*/
/* ====================================================  UART2_STET_REG  ===================================================== */
#define UART2_UART2_STET_REG_UART_SHADOW_TX_EMPTY_TRIGGER_Pos (0UL) /*!< UART_SHADOW_TX_EMPTY_TRIGGER（位0）*/
#define UART2_UART2_STET_REG_UART_SHADOW_TX_EMPTY_TRIGGER_Msk (0x3UL) /*!< UART_SHADOW_TX_EMPTY_TRIGGER（位域掩码：0x03）*/
/* =====================================================  UART2_TAR_REG  ===================================================== */
#define UART2_UART2_TAR_REG_UART_TAR_Pos  (0UL)                     /*!< UART_TAR（位0）*/
#define UART2_UART2_TAR_REG_UART_TAR_Msk  (0xffUL)                  /*!< UART_TAR（位域掩码：0xff）*/
/* =====================================================  UART2_TFL_REG  ===================================================== */
#define UART2_UART2_TFL_REG_UART_TRANSMIT_FIFO_LEVEL_Pos (0UL)      /*!< UART_TRANSMIT_FIFO_LEVEL（位0）*/
#define UART2_UART2_TFL_REG_UART_TRANSMIT_FIFO_LEVEL_Msk (0x1fUL)   /*!< UART_TRANSMIT_FIFO_LEVEL（位域掩码：0x1f）*/
/* =====================================================  UART2_UCV_REG  ===================================================== */
#define UART2_UART2_UCV_REG_UART_UCV_Pos  (0UL)                     /*!< UART_UCV（位0）*/
#define UART2_UART2_UCV_REG_UART_UCV_Msk  (0xffffffffUL)            /*!< UART_UCV（位域掩码：0xffffffff）*/
/* =====================================================  UART2_USR_REG  ===================================================== */
#define UART2_UART2_USR_REG_UART_RFF_Pos  (4UL)                     /*!< UART_RFF（位4）*/
#define UART2_UART2_USR_REG_UART_RFF_Msk  (0x10UL)                  /*!< UART_RFF（位域掩码：0x01）*/
#define UART2_UART2_USR_REG_UART_RFNE_Pos (3UL)                     /*!< UART_RFNE（位3）*/
#define UART2_UART2_USR_REG_UART_RFNE_Msk (0x8UL)                   /*!< UART_RFNE（位域掩码：0x01）*/
#define UART2_UART2_USR_REG_UART_TFE_Pos  (2UL)                     /*!< UART_TFE（位2）*/
#define UART2_UART2_USR_REG_UART_TFE_Msk  (0x4UL)                   /*!< UART_TFE（位字段掩码：0x01）*/
#define UART2_UART2_USR_REG_UART_TFNF_Pos (1UL)                     /*!< UART_TFNF（位1）*/
#define UART2_UART2_USR_REG_UART_TFNF_Msk (0x2UL)                   /*!< UART_TFNF（位域掩码：0x01）*/
#define UART2_UART2_USR_REG_UART_BUSY_Pos (0UL)                     /*!< UART_BUSY（位0）*/
#define UART2_UART2_USR_REG_UART_BUSY_Msk (0x1UL)                   /*!< UART_BUSY（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                           UART3                                           ================ */
/* =========================================================================================================================== */

/* ===================================================  UART3_CONFIG_REG  ==================================================== */
#define UART3_UART3_CONFIG_REG_ISO7816_SCRATCH_PAD_Pos (3UL)        /*!< ISO7816_SCRATCH_PAD（位3）*/
#define UART3_UART3_CONFIG_REG_ISO7816_SCRATCH_PAD_Msk (0xf8UL)     /*!< ISO7816_CRATCH_PAD（位域掩码：0x1f）*/
#define UART3_UART3_CONFIG_REG_ISO7816_ENABLE_Pos (2UL)             /*!< ISO7816_ENABLE（位2）*/
#define UART3_UART3_CONFIG_REG_ISO7816_ENABLE_Msk (0x4UL)           /*!< ISO7816_ENABLE（位域掩码：0x01）*/
#define UART3_UART3_CONFIG_REG_ISO7816_ERR_SIG_EN_Pos (1UL)         /*!< ISO7816_ERROR_SIG_EN（位1）*/
#define UART3_UART3_CONFIG_REG_ISO7816_ERR_SIG_EN_Msk (0x2UL)       /*!< ISO7816_ERROR_SIG_EN（位域掩码：0x01）*/
#define UART3_UART3_CONFIG_REG_ISO7816_CONVENTION_Pos (0UL)         /*!< ISO7816_CONVENTION（位0）*/
#define UART3_UART3_CONFIG_REG_ISO7816_CONVENTION_Msk (0x1UL)       /*!< ISO7816_CONVENTION（位域掩码：0x01）*/
/* ====================================================  UART3_CTRL_REG  ===================================================== */
#define UART3_UART3_CTRL_REG_ISO7816_AUTO_GT_Pos (11UL)             /*!< ISO7816_AUTO_GT（位11）*/
#define UART3_UART3_CTRL_REG_ISO7816_AUTO_GT_Msk (0x800UL)          /*!< ISO7816_AUTO_GT（位域掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_ERR_TX_VALUE_IRQMASK_Pos (10UL) /*!< ISO7816_ERROR_TX_VALUE_IRQMASK（第10位）*/
#define UART3_UART3_CTRL_REG_ISO7816_ERR_TX_VALUE_IRQMASK_Msk (0x400UL) /*!< ISO7816_ERROR_TX_VALUE_IRQMASK（位域掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_ERR_TX_TIME_IRQMASK_Pos (9UL)  /*!< ISO7816_ERROR_TX_TIME_IRQMASK（第9位）*/
#define UART3_UART3_CTRL_REG_ISO7816_ERR_TX_TIME_IRQMASK_Msk (0x200UL) /*!< ISO7816_ERROR_TX_TIME_IRQMASK（位域掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_TIM_EXPIRED_IRQMASK_Pos (8UL)  /*!< ISO7816_TIM_EXPIRED_IRQMASK（第8位）*/
#define UART3_UART3_CTRL_REG_ISO7816_TIM_EXPIRED_IRQMASK_Msk (0x100UL) /*!< ISO7816_TIM_EXPIRED_IRQMASK（位域掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_STATUS_Pos (7UL)           /*!< ISO7816_CLK_STATUS（第7位）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_STATUS_Msk (0x80UL)        /*!< ISO7816_CLK_STATUS（位字段掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_LEVEL_Pos (6UL)            /*!< ISO7816_CLK_LEVEL（位6）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_LEVEL_Msk (0x40UL)         /*!< ISO7816_CLK_LEVEL（位域掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_EN_Pos (5UL)               /*!< ISO7816_CLK_EN（第5位）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_EN_Msk (0x20UL)            /*!< ISO7816_CLK_EN（位字段掩码：0x01）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_DIV_Pos (0UL)              /*!< ISO7816_CLK_DIV（位0）*/
#define UART3_UART3_CTRL_REG_ISO7816_CLK_DIV_Msk (0x1fUL)           /*!< ISO7816_CLK_DIV（位域掩码：0x1f）*/
/* =====================================================  UART3_CTR_REG  ===================================================== */
#define UART3_UART3_CTR_REG_UART_CTR_Pos  (0UL)                     /*!< UART_CTR（位0）*/
#define UART3_UART3_CTR_REG_UART_CTR_Msk  (0xffffffffUL)            /*!< UART_CTR（位域掩码：0xffffffff）*/
/* =====================================================  UART3_DLF_REG  ===================================================== */
#define UART3_UART3_DLF_REG_UART_DLF_Pos  (0UL)                     /*!< UART_DLF（位0）*/
#define UART3_UART3_DLF_REG_UART_DLF_Msk  (0xfUL)                   /*!< UART_DLF（位域掩码：0x0f）*/
/* ====================================================  UART3_DMASA_REG  ==================================================== */
#define UART3_UART3_DMASA_REG_UART_DMASA_Pos (0UL)                  /*!< UART_DMASA（位0）*/
#define UART3_UART3_DMASA_REG_UART_DMASA_Msk (0x1UL)                /*!< UART_DMASA（位域掩码：0x01）*/
/* ==================================================  UART3_ERR_CTRL_REG  =================================================== */
#define UART3_UART3_ERR_CTRL_REG_ISO7816_ERR_PULSE_WIDTH_Pos (4UL)  /*!< ISO7816_ERROR_PULSE_WITH（位4）*/
#define UART3_UART3_ERR_CTRL_REG_ISO7816_ERR_PULSE_WIDTH_Msk (0x1f0UL) /*!< ISO7816_ERROR_PULSE_WIDTH（位域掩码：0x1f）*/
#define UART3_UART3_ERR_CTRL_REG_ISO7816_ERR_PULSE_OFFSET_Pos (0UL) /*!< ISO7816_ERROR_PULSE_OFFSET（位0）*/
#define UART3_UART3_ERR_CTRL_REG_ISO7816_ERR_PULSE_OFFSET_Msk (0xfUL) /*!< ISO7816_ERROR_PULSE_OFFSET（位字段掩码：0x0f）*/
/* =====================================================  UART3_HTX_REG  ===================================================== */
#define UART3_UART3_HTX_REG_UART_HALT_TX_Pos (0UL)                  /*!< UART_HALT_TX（位0）*/
#define UART3_UART3_HTX_REG_UART_HALT_TX_Msk (0x1UL)                /*!< UART_HALT_TX（位域掩码：0x01）*/
/* ===================================================  UART3_IER_DLH_REG  =================================================== */
#define UART3_UART3_IER_DLH_REG_PTIME_DLH7_Pos (7UL)                /*!< PTIME_DLH7（第7位）*/
#define UART3_UART3_IER_DLH_REG_PTIME_DLH7_Msk (0x80UL)             /*!< PTIME_DLH7（位域掩码：0x01）*/
#define UART3_UART3_IER_DLH_REG_DLH6_5_Pos (5UL)                    /*!< DLH6_5（第5位）*/
#define UART3_UART3_IER_DLH_REG_DLH6_5_Msk (0x60UL)                 /*!< DLH6_5（位域掩码：0x03）*/
#define UART3_UART3_IER_DLH_REG_ELCOLR_DLH4_Pos (4UL)               /*!< ELCOLR_DLH4（位4）*/
#define UART3_UART3_IER_DLH_REG_ELCOLR_DLH4_Msk (0x10UL)            /*!< ELCOLR_DLH4（位字段掩码：0x01）*/
#define UART3_UART3_IER_DLH_REG_EDSSI_DLH3_Pos (3UL)                /*!< EDSSI_DLH3（位3）*/
#define UART3_UART3_IER_DLH_REG_EDSSI_DLH3_Msk (0x8UL)              /*!< EDSSI_DLH3（位字段掩码：0x01）*/
#define UART3_UART3_IER_DLH_REG_ELSI_DLH2_Pos (2UL)                 /*!< ELSI_DLH2（位2）*/
#define UART3_UART3_IER_DLH_REG_ELSI_DLH2_Msk (0x4UL)               /*!< ELSI_DLH2（位字段掩码：0x01）*/
#define UART3_UART3_IER_DLH_REG_ETBEI_DLH1_Pos (1UL)                /*!< ETBEI_DLH1（位1）*/
#define UART3_UART3_IER_DLH_REG_ETBEI_DLH1_Msk (0x2UL)              /*!< ETBEI_DLH1（位域掩码：0x01）*/
#define UART3_UART3_IER_DLH_REG_ERBFI_DLH0_Pos (0UL)                /*!< ERBFI_DLH0（位0）*/
#define UART3_UART3_IER_DLH_REG_ERBFI_DLH0_Msk (0x1UL)              /*!< ERBFI_DLH0（位字段掩码：0x01）*/
/* ===================================================  UART3_IIR_FCR_REG  =================================================== */
#define UART3_UART3_IIR_FCR_REG_IIR_FCR_Pos (0UL)                   /*!< IIR_FCR（位0）*/
#define UART3_UART3_IIR_FCR_REG_IIR_FCR_Msk (0xffUL)                /*!< IIR_FCR（位域掩码：0xff）*/
/* =================================================  UART3_IRQ_STATUS_REG  ================================================== */
#define UART3_UART3_IRQ_STATUS_REG_ISO7816_ERR_TX_VALUE_IRQ_Pos (2UL) /*!< ISO7816_ERROR_TX_VALUE_IRQ（第2位）*/
#define UART3_UART3_IRQ_STATUS_REG_ISO7816_ERR_TX_VALUE_IRQ_Msk (0x4UL) /*!< ISO7816_ERROR_TX_VALUE_IRQ（位域掩码：0x01）*/
#define UART3_UART3_IRQ_STATUS_REG_ISO7816_ERR_TX_TIME_IRQ_Pos (1UL) /*!< ISO7816_ERROR_TX_TIME_IRQ（位1）*/
#define UART3_UART3_IRQ_STATUS_REG_ISO7816_ERR_TX_TIME_IRQ_Msk (0x2UL) /*!< ISO7816_ERROR_TX_TIME_IRQ（位字段掩码：0x01）*/
#define UART3_UART3_IRQ_STATUS_REG_ISO7816_TIM_EXPIRED_IRQ_Pos (0UL) /*!< ISO7816_TIM_EXPIRED_IRQ（位0）*/
#define UART3_UART3_IRQ_STATUS_REG_ISO7816_TIM_EXPIRED_IRQ_Msk (0x1UL) /*!< ISO7816_TIM_EXPIRED_IRQ（位域掩码：0x01）*/
/* =====================================================  UART3_LCR_EXT  ===================================================== */
#define UART3_UART3_LCR_EXT_UART_TRANSMIT_MODE_Pos (3UL)            /*!< UART_TRANSMIT_MODE（位3）*/
#define UART3_UART3_LCR_EXT_UART_TRANSMIT_MODE_Msk (0x8UL)          /*!< UART_TRANSMIT_MODE（位字段掩码：0x01）*/
#define UART3_UART3_LCR_EXT_UART_SEND_ADDR_Pos (2UL)                /*!< UART_SEND_ADDR（位2）*/
#define UART3_UART3_LCR_EXT_UART_SEND_ADDR_Msk (0x4UL)              /*!< UART_SEND_ADDR（位字段掩码：0x01）*/
#define UART3_UART3_LCR_EXT_UART_ADDR_MATCH_Pos (1UL)               /*!< UART_ADDR_MATCH（位1）*/
#define UART3_UART3_LCR_EXT_UART_ADDR_MATCH_Msk (0x2UL)             /*!< UART_ADDR_MATCH（位字段掩码：0x01）*/
#define UART3_UART3_LCR_EXT_UART_DLS_E_Pos (0UL)                    /*!< UART_DLS_E（位0）*/
#define UART3_UART3_LCR_EXT_UART_DLS_E_Msk (0x1UL)                  /*!< UART_DLS_E（位域掩码：0x01）*/
/* =====================================================  UART3_LCR_REG  ===================================================== */
#define UART3_UART3_LCR_REG_UART_DLAB_Pos (7UL)                     /*!< UART_DLAB（位7）*/
#define UART3_UART3_LCR_REG_UART_DLAB_Msk (0x80UL)                  /*!< UART_DLAB（位域掩码：0x01）*/
#define UART3_UART3_LCR_REG_UART_BC_Pos   (6UL)                     /*!< UART_BC（位6）*/
#define UART3_UART3_LCR_REG_UART_BC_Msk   (0x40UL)                  /*!< UART_BC（位域掩码：0x01）*/
#define UART3_UART3_LCR_REG_UART_SP_Pos   (5UL)                     /*!< UART_SP（位5）*/
#define UART3_UART3_LCR_REG_UART_SP_Msk   (0x20UL)                  /*!< UART_SP（位域掩码：0x01）*/
#define UART3_UART3_LCR_REG_UART_EPS_Pos  (4UL)                     /*!< UART_EPS（位4）*/
#define UART3_UART3_LCR_REG_UART_EPS_Msk  (0x10UL)                  /*!< UART_EPS（位域掩码：0x01）*/
#define UART3_UART3_LCR_REG_UART_PEN_Pos  (3UL)                     /*!< UART_PEN（位3）*/
#define UART3_UART3_LCR_REG_UART_PEN_Msk  (0x8UL)                   /*!< UART_PEN（位字段掩码：0x01）*/
#define UART3_UART3_LCR_REG_UART_STOP_Pos (2UL)                     /*!< UART_STOP（位2）*/
#define UART3_UART3_LCR_REG_UART_STOP_Msk (0x4UL)                   /*!< UART_STOP（位域掩码：0x01）*/
#define UART3_UART3_LCR_REG_UART_DLS_Pos  (0UL)                     /*!< UART_DLS（位0）*/
#define UART3_UART3_LCR_REG_UART_DLS_Msk  (0x3UL)                   /*!< UART_DLS（位域掩码：0x03）*/
/* =====================================================  UART3_LSR_REG  ===================================================== */
#define UART3_UART3_LSR_REG_UART_ADDR_RCVD_Pos (8UL)                /*!< UART_ADDR_RCVD（位8）*/
#define UART3_UART3_LSR_REG_UART_ADDR_RCVD_Msk (0x100UL)            /*!< UART_ADDR_RCVD（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_RFE_Pos  (7UL)                     /*!< UART_RFE（位7）*/
#define UART3_UART3_LSR_REG_UART_RFE_Msk  (0x80UL)                  /*!< UART_RFE（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_TEMT_Pos (6UL)                     /*!< UART_TEMT（位6）*/
#define UART3_UART3_LSR_REG_UART_TEMT_Msk (0x40UL)                  /*!< UART_TEMT（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_THRE_Pos (5UL)                     /*!< UART_THRE（位5）*/
#define UART3_UART3_LSR_REG_UART_THRE_Msk (0x20UL)                  /*!< UART_THRE（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_BI_Pos   (4UL)                     /*!< UART_BI（位4）*/
#define UART3_UART3_LSR_REG_UART_BI_Msk   (0x10UL)                  /*!< UART_BI（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_FE_Pos   (3UL)                     /*!< UART_FE（位3）*/
#define UART3_UART3_LSR_REG_UART_FE_Msk   (0x8UL)                   /*!< UART_FE（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_PE_Pos   (2UL)                     /*!< UART_PE（位2）*/
#define UART3_UART3_LSR_REG_UART_PE_Msk   (0x4UL)                   /*!< UART_PE（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_OE_Pos   (1UL)                     /*!< UART_OE（位1）*/
#define UART3_UART3_LSR_REG_UART_OE_Msk   (0x2UL)                   /*!< UART_OE（位域掩码：0x01）*/
#define UART3_UART3_LSR_REG_UART_DR_Pos   (0UL)                     /*!< UART_DR（位0）*/
#define UART3_UART3_LSR_REG_UART_DR_Msk   (0x1UL)                   /*!< UART_DR（位域掩码：0x01）*/
/* =====================================================  UART3_MCR_REG  ===================================================== */
#define UART3_UART3_MCR_REG_UART_AFCE_Pos (5UL)                     /*!< UART_AFCE（位5）*/
#define UART3_UART3_MCR_REG_UART_AFCE_Msk (0x20UL)                  /*!< UART_AFCE（位域掩码：0x01）*/
#define UART3_UART3_MCR_REG_UART_LB_Pos   (4UL)                     /*!< UART_LB（位4）*/
#define UART3_UART3_MCR_REG_UART_LB_Msk   (0x10UL)                  /*!< UART_LB（位域掩码：0x01）*/
#define UART3_UART3_MCR_REG_UART_RTS_Pos  (1UL)                     /*!< UART_RTS（位1）*/
#define UART3_UART3_MCR_REG_UART_RTS_Msk  (0x2UL)                   /*!< UART_RTS（位域掩码：0x01）*/
/* =====================================================  UART3_MSR_REG  ===================================================== */
#define UART3_UART3_MSR_REG_UART_CTS_Pos  (4UL)                     /*!< UART_CTS（位4）*/
#define UART3_UART3_MSR_REG_UART_CTS_Msk  (0x10UL)                  /*!< UART_CTS（位域掩码：0x01）*/
#define UART3_UART3_MSR_REG_UART_DCTS_Pos (0UL)                     /*!< UART_DCTS（位0）*/
#define UART3_UART3_MSR_REG_UART_DCTS_Msk (0x1UL)                   /*!< UART_DCTS（位域掩码：0x01）*/
/* =====================================================  UART3_RAR_REG  ===================================================== */
#define UART3_UART3_RAR_REG_UART_RAR_Pos  (0UL)                     /*!< UART_RAR（位0）*/
#define UART3_UART3_RAR_REG_UART_RAR_Msk  (0xffUL)                  /*!< UART_RAR（位域掩码：0xff）*/
/* =================================================  UART3_RBR_THR_DLL_REG  ================================================= */
#define UART3_UART3_RBR_THR_DLL_REG_RBR_THR_9BIT_Pos (8UL)          /*!< RBR_THR_9BIT（位8）*/
#define UART3_UART3_RBR_THR_DLL_REG_RBR_THR_9BIT_Msk (0x100UL)      /*!< RBR_THR_9BIT（位字段掩码：0x01）*/
#define UART3_UART3_RBR_THR_DLL_REG_RBR_THR_DLL_Pos (0UL)           /*!< RBR_THR_DLL（位0）*/
#define UART3_UART3_RBR_THR_DLL_REG_RBR_THR_DLL_Msk (0xffUL)        /*!< RBR_THR_DLL（位域掩码：0xff）*/
/* =====================================================  UART3_RFL_REG  ===================================================== */
#define UART3_UART3_RFL_REG_UART_RECEIVE_FIFO_LEVEL_Pos (0UL)       /*!< UART_RECEIVE_FIFO_LEVEL（位0）*/
#define UART3_UART3_RFL_REG_UART_RECEIVE_FIFO_LEVEL_Msk (0x1fUL)    /*!< UART_RECEIVE_FIFO_LEVEL（位域掩码：0x1f）*/
/* ====================================================  UART3_SBCR_REG  ===================================================== */
#define UART3_UART3_SBCR_REG_UART_SHADOW_BREAK_CONTROL_Pos (0UL)    /*!< UART_SHADOW_BREAK_CONTROL（位0）*/
#define UART3_UART3_SBCR_REG_UART_SHADOW_BREAK_CONTROL_Msk (0x1UL)  /*!< UART_SHADOW_BREAK_CONTROL（位域掩码：0x01）*/
/* ====================================================  UART3_SDMAM_REG  ==================================================== */
#define UART3_UART3_SDMAM_REG_UART_SHADOW_DMA_MODE_Pos (0UL)        /*!< UART_SHADOW_DMA_MODE（位0）*/
#define UART3_UART3_SDMAM_REG_UART_SHADOW_DMA_MODE_Msk (0x1UL)      /*!< UART_SHADOW_DMA_MODE（位域掩码：0x01）*/
/* =====================================================  UART3_SFE_REG  ===================================================== */
#define UART3_UART3_SFE_REG_UART_SHADOW_FIFO_ENABLE_Pos (0UL)       /*!< UART_SHADOW_FIFO_ENABLE（位0）*/
#define UART3_UART3_SFE_REG_UART_SHADOW_FIFO_ENABLE_Msk (0x1UL)     /*!< UART_SHADOW_FIFO_ENABLE（位字段掩码：0x01）*/
/* =================================================  UART3_SRBR_STHR0_REG  ================================================== */
#define UART3_UART3_SRBR_STHR0_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR0_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR10_REG  ================================================= */
#define UART3_UART3_SRBR_STHR10_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR10_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR11_REG  ================================================= */
#define UART3_UART3_SRBR_STHR11_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR11_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR12_REG  ================================================= */
#define UART3_UART3_SRBR_STHR12_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR12_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR13_REG  ================================================= */
#define UART3_UART3_SRBR_STHR13_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR13_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR14_REG  ================================================= */
#define UART3_UART3_SRBR_STHR14_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR14_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR15_REG  ================================================= */
#define UART3_UART3_SRBR_STHR15_REG_SRBR_STHRx_Pos (0UL)            /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR15_REG_SRBR_STHRx_Msk (0xffUL)         /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR1_REG  ================================================== */
#define UART3_UART3_SRBR_STHR1_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR1_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR2_REG  ================================================== */
#define UART3_UART3_SRBR_STHR2_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR2_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR3_REG  ================================================== */
#define UART3_UART3_SRBR_STHR3_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR3_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR4_REG  ================================================== */
#define UART3_UART3_SRBR_STHR4_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR4_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR5_REG  ================================================== */
#define UART3_UART3_SRBR_STHR5_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR5_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR6_REG  ================================================== */
#define UART3_UART3_SRBR_STHR6_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR6_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR7_REG  ================================================== */
#define UART3_UART3_SRBR_STHR7_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR7_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR8_REG  ================================================== */
#define UART3_UART3_SRBR_STHR8_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR8_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =================================================  UART3_SRBR_STHR9_REG  ================================================== */
#define UART3_UART3_SRBR_STHR9_REG_SRBR_STHRx_Pos (0UL)             /*!< SRBR_STHRx（位0）*/
#define UART3_UART3_SRBR_STHR9_REG_SRBR_STHRx_Msk (0xffUL)          /*!< SRBR_STHRx（位字段掩码：0xff）*/
/* =====================================================  UART3_SRR_REG  ===================================================== */
#define UART3_UART3_SRR_REG_UART_XFR_Pos  (2UL)                     /*!< UART_XFR（位2）*/
#define UART3_UART3_SRR_REG_UART_XFR_Msk  (0x4UL)                   /*!< UART_XFR（位域掩码：0x01）*/
#define UART3_UART3_SRR_REG_UART_RFR_Pos  (1UL)                     /*!< UART_RFR（位1）*/
#define UART3_UART3_SRR_REG_UART_RFR_Msk  (0x2UL)                   /*!< UART_RFR（位域掩码：0x01）*/
#define UART3_UART3_SRR_REG_UART_UR_Pos   (0UL)                     /*!< UART_UR（位0）*/
#define UART3_UART3_SRR_REG_UART_UR_Msk   (0x1UL)                   /*!< UART_UR（位域掩码：0x01）*/
/* ====================================================  UART3_SRTS_REG  ===================================================== */
#define UART3_UART3_SRTS_REG_UART_SHADOW_REQUEST_TO_SEND_Pos (0UL)  /*!< UART_SHADOW_REQUEST_TO_SEND（位0）*/
#define UART3_UART3_SRTS_REG_UART_SHADOW_REQUEST_TO_SEND_Msk (0x1UL) /*!< UART_SHADOW_REQUEST_TO_SEND（位字段掩码：0x01）*/
/* =====================================================  UART3_SRT_REG  ===================================================== */
#define UART3_UART3_SRT_REG_UART_SHADOW_RCVR_TRIGGER_Pos (0UL)      /*!< UART_SHADOW_RCVR_TRIGGER（位0）*/
#define UART3_UART3_SRT_REG_UART_SHADOW_RCVR_TRIGGER_Msk (0x3UL)    /*!< UART_SHADOW_RCVR_TRIGGER（位域掩码：0x03）*/
/* ====================================================  UART3_STET_REG  ===================================================== */
#define UART3_UART3_STET_REG_UART_SHADOW_TX_EMPTY_TRIGGER_Pos (0UL) /*!< UART_SHADOW_TX_EMPTY_TRIGGER（位0）*/
#define UART3_UART3_STET_REG_UART_SHADOW_TX_EMPTY_TRIGGER_Msk (0x3UL) /*!< UART_SHADOW_TX_EMPTY_TRIGGER（位域掩码：0x03）*/
/* =====================================================  UART3_TAR_REG  ===================================================== */
#define UART3_UART3_TAR_REG_UART_TAR_Pos  (0UL)                     /*!< UART_TAR（位0）*/
#define UART3_UART3_TAR_REG_UART_TAR_Msk  (0xffUL)                  /*!< UART_TAR（位域掩码：0xff）*/
/* =====================================================  UART3_TFL_REG  ===================================================== */
#define UART3_UART3_TFL_REG_UART_TRANSMIT_FIFO_LEVEL_Pos (0UL)      /*!< UART_TRANSMIT_FIFO_LEVEL（位0）*/
#define UART3_UART3_TFL_REG_UART_TRANSMIT_FIFO_LEVEL_Msk (0x1fUL)   /*!< UART_TRANSMIT_FIFO_LEVEL（位域掩码：0x1f）*/
/* ====================================================  UART3_TIMER_REG  ==================================================== */
#define UART3_UART3_TIMER_REG_ISO7816_TIM_MODE_Pos (17UL)           /*!< ISO7816_TIM_MODE（第17位）*/
#define UART3_UART3_TIMER_REG_ISO7816_TIM_MODE_Msk (0x20000UL)      /*!< ISO7816_TIM_MODE（位字段掩码：0x01）*/
#define UART3_UART3_TIMER_REG_ISO7816_TIM_EN_Pos (16UL)             /*!< ISO7816_TIM_EN（第16位）*/
#define UART3_UART3_TIMER_REG_ISO7816_TIM_EN_Msk (0x10000UL)        /*!< ISO7816_TIM_EN（位域掩码：0x01）*/
#define UART3_UART3_TIMER_REG_ISO7816_TIM_MAX_Pos (0UL)             /*!< ISO7816_TIM_MAX（位0）*/
#define UART3_UART3_TIMER_REG_ISO7816_TIM_MAX_Msk (0xffffUL)        /*!< ISO7816_TIM_MAX（位域掩码：0xffff）*/
/* =====================================================  UART3_UCV_REG  ===================================================== */
#define UART3_UART3_UCV_REG_UART_UCV_Pos  (0UL)                     /*!< UART_UCV（位0）*/
#define UART3_UART3_UCV_REG_UART_UCV_Msk  (0xffffffffUL)            /*!< UART_UCV（位域掩码：0xffffffff）*/
/* =====================================================  UART3_USR_REG  ===================================================== */
#define UART3_UART3_USR_REG_UART_RFF_Pos  (4UL)                     /*!< UART_RFF（位4）*/
#define UART3_UART3_USR_REG_UART_RFF_Msk  (0x10UL)                  /*!< UART_RFF（位域掩码：0x01）*/
#define UART3_UART3_USR_REG_UART_RFNE_Pos (3UL)                     /*!< UART_RFNE（位3）*/
#define UART3_UART3_USR_REG_UART_RFNE_Msk (0x8UL)                   /*!< UART_RFNE（位域掩码：0x01）*/
#define UART3_UART3_USR_REG_UART_TFE_Pos  (2UL)                     /*!< UART_TFE（位2）*/
#define UART3_UART3_USR_REG_UART_TFE_Msk  (0x4UL)                   /*!< UART_TFE（位字段掩码：0x01）*/
#define UART3_UART3_USR_REG_UART_TFNF_Pos (1UL)                     /*!< UART_TFNF（位1）*/
#define UART3_UART3_USR_REG_UART_TFNF_Msk (0x2UL)                   /*!< UART_TFNF（位域掩码：0x01）*/
#define UART3_UART3_USR_REG_UART_BUSY_Pos (0UL)                     /*!< UART_BUSY（位0）*/
#define UART3_UART3_USR_REG_UART_BUSY_Msk (0x1UL)                   /*!< UART_BUSY（位字段掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                            USB                                            ================ */
/* =========================================================================================================================== */

/* =====================================================  USB_ALTEV_REG  ===================================================== */
#define USB_USB_ALTEV_REG_USB_RESUME_Pos  (7UL)                     /*!< USB_RESUME（第7位）*/
#define USB_USB_ALTEV_REG_USB_RESUME_Msk  (0x80UL)                  /*!< USB_RESUME（位字段掩码：0x01）*/
#define USB_USB_ALTEV_REG_USB_RESET_Pos   (6UL)                     /*!< USB_RESET（位6）*/
#define USB_USB_ALTEV_REG_USB_RESET_Msk   (0x40UL)                  /*!< USB_RESET（位域掩码：0x01）*/
#define USB_USB_ALTEV_REG_USB_SD5_Pos     (5UL)                     /*!< USB_SD5（位5）*/
#define USB_USB_ALTEV_REG_USB_SD5_Msk     (0x20UL)                  /*!< USB_SD5（位域掩码：0x01）*/
#define USB_USB_ALTEV_REG_USB_SD3_Pos     (4UL)                     /*!< USB_SD3（位4）*/
#define USB_USB_ALTEV_REG_USB_SD3_Msk     (0x10UL)                  /*!< USB_SD3（位域掩码：0x01）*/
#define USB_USB_ALTEV_REG_USB_EOP_Pos     (3UL)                     /*!< USB_EOP（位3）*/
#define USB_USB_ALTEV_REG_USB_EOP_Msk     (0x8UL)                   /*!< USB_EOP（位域掩码：0x01）*/
/* ====================================================  USB_ALTMSK_REG  ===================================================== */
#define USB_USB_ALTMSK_REG_USB_M_RESUME_Pos (7UL)                   /*!< USB_M_RESUME（第7位）*/
#define USB_USB_ALTMSK_REG_USB_M_RESUME_Msk (0x80UL)                /*!< USB_M_RESUME（位字段掩码：0x01）*/
#define USB_USB_ALTMSK_REG_USB_M_RESET_Pos (6UL)                    /*!< USB_M_RESET（位6）*/
#define USB_USB_ALTMSK_REG_USB_M_RESET_Msk (0x40UL)                 /*!< USB_M_RESET（位字段掩码：0x01）*/
#define USB_USB_ALTMSK_REG_USB_M_SD5_Pos  (5UL)                     /*!< USB_M_SD5（位5）*/
#define USB_USB_ALTMSK_REG_USB_M_SD5_Msk  (0x20UL)                  /*!< USB_M_SD5（位域掩码：0x01）*/
#define USB_USB_ALTMSK_REG_USB_M_SD3_Pos  (4UL)                     /*!< USB_M_SD3（位4）*/
#define USB_USB_ALTMSK_REG_USB_M_SD3_Msk  (0x10UL)                  /*!< USB_M_SD3（位域掩码：0x01）*/
#define USB_USB_ALTMSK_REG_USB_M_EOP_Pos  (3UL)                     /*!< USB_M_EOP（位3）*/
#define USB_USB_ALTMSK_REG_USB_M_EOP_Msk  (0x8UL)                   /*!< USB_M_EOP（位域掩码：0x01）*/
/* =================================================  USB_CHARGER_CTRL_REG  ================================================== */
#define USB_USB_CHARGER_CTRL_REG_IDM_SINK_ON_Pos (5UL)              /*!< IDM_SINK_ON（位5）*/
#define USB_USB_CHARGER_CTRL_REG_IDM_SINK_ON_Msk (0x20UL)           /*!< IDM_SINK_ON（位字段掩码：0x01）*/
#define USB_USB_CHARGER_CTRL_REG_IDP_SINK_ON_Pos (4UL)              /*!< IDP_INK_ON（位4）*/
#define USB_USB_CHARGER_CTRL_REG_IDP_SINK_ON_Msk (0x10UL)           /*!< IDP_INK_ON（位域掩码：0x01）*/
#define USB_USB_CHARGER_CTRL_REG_VDM_SRC_ON_Pos (3UL)               /*!< VDM_SRC_ON（位3）*/
#define USB_USB_CHARGER_CTRL_REG_VDM_SRC_ON_Msk (0x8UL)             /*!< VDM_SRC_ON（位字段掩码：0x01）*/
#define USB_USB_CHARGER_CTRL_REG_VDP_SRC_ON_Pos (2UL)               /*!< VDP_SRC_ON（位2）*/
#define USB_USB_CHARGER_CTRL_REG_VDP_SRC_ON_Msk (0x4UL)             /*!< VDP_SRC_ON（位字段掩码：0x01）*/
#define USB_USB_CHARGER_CTRL_REG_IDP_SRC_ON_Pos (1UL)               /*!< IDP_SRC_ON（位1）*/
#define USB_USB_CHARGER_CTRL_REG_IDP_SRC_ON_Msk (0x2UL)             /*!< IDP_SRC_ON（位域掩码：0x01）*/
#define USB_USB_CHARGER_CTRL_REG_USB_CHARGE_ON_Pos (0UL)            /*!< USB_CHARGE_ON（位0）*/
#define USB_USB_CHARGER_CTRL_REG_USB_CHARGE_ON_Msk (0x1UL)          /*!< USB_CHARGE_ON（位域掩码：0x01）*/
/* =================================================  USB_CHARGER_STAT_REG  ================================================== */
#define USB_USB_CHARGER_STAT_REG_USB_DM_VAL2_Pos (5UL)              /*!< USB_DM_VAL2（位5）*/
#define USB_USB_CHARGER_STAT_REG_USB_DM_VAL2_Msk (0x20UL)           /*!< USB_DM_VAL2（位字段掩码：0x01）*/
#define USB_USB_CHARGER_STAT_REG_USB_DP_VAL2_Pos (4UL)              /*!< USB_DP_VAL2（位4）*/
#define USB_USB_CHARGER_STAT_REG_USB_DP_VAL2_Msk (0x10UL)           /*!< USB_DP_VAL2（位字段掩码：0x01）*/
#define USB_USB_CHARGER_STAT_REG_USB_DM_VAL_Pos (3UL)               /*!< USB_DM_VAL（位3）*/
#define USB_USB_CHARGER_STAT_REG_USB_DM_VAL_Msk (0x8UL)             /*!< USB_DM_VAL（位字段掩码：0x01）*/
#define USB_USB_CHARGER_STAT_REG_USB_DP_VAL_Pos (2UL)               /*!< USB_DP_VAL（位2）*/
#define USB_USB_CHARGER_STAT_REG_USB_DP_VAL_Msk (0x4UL)             /*!< USB_DP_VAL（位字段掩码：0x01）*/
#define USB_USB_CHARGER_STAT_REG_USB_CHG_DET_Pos (1UL)              /*!< USB_CHG_DET（位1）*/
#define USB_USB_CHARGER_STAT_REG_USB_CHG_DET_Msk (0x2UL)            /*!< USB_CHG_DET（位字段掩码：0x01）*/
#define USB_USB_CHARGER_STAT_REG_USB_DCP_DET_Pos (0UL)              /*!< USB_DCP_DET（位0）*/
#define USB_USB_CHARGER_STAT_REG_USB_DCP_DET_Msk (0x1UL)            /*!< USB_DCP_DET（位字段掩码：0x01）*/
/* ===================================================  USB_DMA_CTRL_REG  ==================================================== */
#define USB_USB_DMA_CTRL_REG_USB_DMA_EN_Pos (6UL)                   /*!< USB_DMA_EN（位6）*/
#define USB_USB_DMA_CTRL_REG_USB_DMA_EN_Msk (0x40UL)                /*!< USB_DMA_EN（位域掩码：0x01）*/
#define USB_USB_DMA_CTRL_REG_USB_DMA_TX_Pos (3UL)                   /*!< USB_DMA_TX（位3）*/
#define USB_USB_DMA_CTRL_REG_USB_DMA_TX_Msk (0x38UL)                /*!< USB_DMA_TX（位域掩码：0x07）*/
#define USB_USB_DMA_CTRL_REG_USB_DMA_RX_Pos (0UL)                   /*!< USB_DMA_RX（位0）*/
#define USB_USB_DMA_CTRL_REG_USB_DMA_RX_Msk (0x7UL)                 /*!< USB_DMA_RX（位域掩码：0x07）*/
/* ====================================================  USB_EP0_NAK_REG  ==================================================== */
#define USB_USB_EP0_NAK_REG_USB_EP0_OUTNAK_Pos (1UL)                /*!< USB_EP0_OUTNAK（位1）*/
#define USB_USB_EP0_NAK_REG_USB_EP0_OUTNAK_Msk (0x2UL)              /*!< USB_EP0_OUTNAK（位域掩码：0x01）*/
#define USB_USB_EP0_NAK_REG_USB_EP0_INNAK_Pos (0UL)                 /*!< USB_EP0_INNAK（位0）*/
#define USB_USB_EP0_NAK_REG_USB_EP0_INNAK_Msk (0x1UL)               /*!< USB_EP0_INNAK（位域掩码：0x01）*/
/* =====================================================  USB_EPC0_REG  ====================================================== */
#define USB_USB_EPC0_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC0_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC0_REG_USB_DEF_Pos      (6UL)                     /*!< USB_DEF（位6）*/
#define USB_USB_EPC0_REG_USB_DEF_Msk      (0x40UL)                  /*!< USB_DEF（位字段掩码：0x01）*/
#define USB_USB_EPC0_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC0_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* =====================================================  USB_EPC1_REG  ====================================================== */
#define USB_USB_EPC1_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC1_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC1_REG_USB_ISO_Pos      (5UL)                     /*!< USB_ISO（位5）*/
#define USB_USB_EPC1_REG_USB_ISO_Msk      (0x20UL)                  /*!< USB_ISO（位域掩码：0x01）*/
#define USB_USB_EPC1_REG_USB_EP_EN_Pos    (4UL)                     /*!< USB_EP_EN（位4）*/
#define USB_USB_EPC1_REG_USB_EP_EN_Msk    (0x10UL)                  /*!< USB_EP_EN（位域掩码：0x01）*/
#define USB_USB_EPC1_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC1_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* =====================================================  USB_EPC2_REG  ====================================================== */
#define USB_USB_EPC2_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC2_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC2_REG_USB_ISO_Pos      (5UL)                     /*!< USB_ISO（位5）*/
#define USB_USB_EPC2_REG_USB_ISO_Msk      (0x20UL)                  /*!< USB_ISO（位域掩码：0x01）*/
#define USB_USB_EPC2_REG_USB_EP_EN_Pos    (4UL)                     /*!< USB_EP_EN（位4）*/
#define USB_USB_EPC2_REG_USB_EP_EN_Msk    (0x10UL)                  /*!< USB_EP_EN（位域掩码：0x01）*/
#define USB_USB_EPC2_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC2_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* =====================================================  USB_EPC3_REG  ====================================================== */
#define USB_USB_EPC3_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC3_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC3_REG_USB_ISO_Pos      (5UL)                     /*!< USB_ISO（位5）*/
#define USB_USB_EPC3_REG_USB_ISO_Msk      (0x20UL)                  /*!< USB_ISO（位域掩码：0x01）*/
#define USB_USB_EPC3_REG_USB_EP_EN_Pos    (4UL)                     /*!< USB_EP_EN（位4）*/
#define USB_USB_EPC3_REG_USB_EP_EN_Msk    (0x10UL)                  /*!< USB_EP_EN（位域掩码：0x01）*/
#define USB_USB_EPC3_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC3_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* =====================================================  USB_EPC4_REG  ====================================================== */
#define USB_USB_EPC4_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC4_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC4_REG_USB_ISO_Pos      (5UL)                     /*!< USB_ISO（位5）*/
#define USB_USB_EPC4_REG_USB_ISO_Msk      (0x20UL)                  /*!< USB_ISO（位域掩码：0x01）*/
#define USB_USB_EPC4_REG_USB_EP_EN_Pos    (4UL)                     /*!< USB_EP_EN（位4）*/
#define USB_USB_EPC4_REG_USB_EP_EN_Msk    (0x10UL)                  /*!< USB_EP_EN（位域掩码：0x01）*/
#define USB_USB_EPC4_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC4_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* =====================================================  USB_EPC5_REG  ====================================================== */
#define USB_USB_EPC5_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC5_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC5_REG_USB_ISO_Pos      (5UL)                     /*!< USB_ISO（位5）*/
#define USB_USB_EPC5_REG_USB_ISO_Msk      (0x20UL)                  /*!< USB_ISO（位域掩码：0x01）*/
#define USB_USB_EPC5_REG_USB_EP_EN_Pos    (4UL)                     /*!< USB_EP_EN（位4）*/
#define USB_USB_EPC5_REG_USB_EP_EN_Msk    (0x10UL)                  /*!< USB_EP_EN（位域掩码：0x01）*/
#define USB_USB_EPC5_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC5_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* =====================================================  USB_EPC6_REG  ====================================================== */
#define USB_USB_EPC6_REG_USB_STALL_Pos    (7UL)                     /*!< USB_STALL（第7位）*/
#define USB_USB_EPC6_REG_USB_STALL_Msk    (0x80UL)                  /*!< USB_STALL（位域掩码：0x01）*/
#define USB_USB_EPC6_REG_USB_ISO_Pos      (5UL)                     /*!< USB_ISO（位5）*/
#define USB_USB_EPC6_REG_USB_ISO_Msk      (0x20UL)                  /*!< USB_ISO（位域掩码：0x01）*/
#define USB_USB_EPC6_REG_USB_EP_EN_Pos    (4UL)                     /*!< USB_EP_EN（位4）*/
#define USB_USB_EPC6_REG_USB_EP_EN_Msk    (0x10UL)                  /*!< USB_EP_EN（位域掩码：0x01）*/
#define USB_USB_EPC6_REG_USB_EP_Pos       (0UL)                     /*!< USB_EP（位0）*/
#define USB_USB_EPC6_REG_USB_EP_Msk       (0xfUL)                   /*!< USB_EP（位域掩码：0x0f）*/
/* ======================================================  USB_FAR_REG  ====================================================== */
#define USB_USB_FAR_REG_USB_AD_EN_Pos     (7UL)                     /*!< USB_AD_EN（第7位）*/
#define USB_USB_FAR_REG_USB_AD_EN_Msk     (0x80UL)                  /*!< USB_AD_EN（位域掩码：0x01）*/
#define USB_USB_FAR_REG_USB_AD_Pos        (0UL)                     /*!< USB_AD（位0）*/
#define USB_USB_FAR_REG_USB_AD_Msk        (0x7fUL)                  /*!< USB_AD（位域掩码：0x7f）*/
/* ======================================================  USB_FNH_REG  ====================================================== */
#define USB_USB_FNH_REG_USB_MF_Pos        (7UL)                     /*!< USB_MF（第7位）*/
#define USB_USB_FNH_REG_USB_MF_Msk        (0x80UL)                  /*!< USB_MF（位域掩码：0x01）*/
#define USB_USB_FNH_REG_USB_UL_Pos        (6UL)                     /*!< USB_UL（位6）*/
#define USB_USB_FNH_REG_USB_UL_Msk        (0x40UL)                  /*!< USB_UL（位域掩码：0x01）*/
#define USB_USB_FNH_REG_USB_RFC_Pos       (5UL)                     /*!< USB_RFC（第5位）*/
#define USB_USB_FNH_REG_USB_RFC_Msk       (0x20UL)                  /*!< USB_RFC（位域掩码：0x01）*/
#define USB_USB_FNH_REG_USB_FN_10_8_Pos   (0UL)                     /*!< USB_FN_10_8（位0）*/
#define USB_USB_FNH_REG_USB_FN_10_8_Msk   (0x7UL)                   /*!< USB_FN_10_8（位域掩码：0x07）*/
/* ======================================================  USB_FNL_REG  ====================================================== */
#define USB_USB_FNL_REG_USB_FN_Pos        (0UL)                     /*!< USB_FN（位0）*/
#define USB_USB_FNL_REG_USB_FN_Msk        (0xffUL)                  /*!< USB_FN（位域掩码：0xff）*/
/* =====================================================  USB_FWEV_REG  ====================================================== */
#define USB_USB_FWEV_REG_USB_RXWARN31_Pos (4UL)                     /*!< USB_RXWARN31（位4）*/
#define USB_USB_FWEV_REG_USB_RXWARN31_Msk (0x70UL)                  /*!< USB_RXWARN31（位域掩码：0x07）*/
#define USB_USB_FWEV_REG_USB_TXWARN31_Pos (0UL)                     /*!< USB_TXWARN31（位0）*/
#define USB_USB_FWEV_REG_USB_TXWARN31_Msk (0x7UL)                   /*!< USB_TXWARN31（位域掩码：0x07）*/
/* =====================================================  USB_FWMSK_REG  ===================================================== */
#define USB_USB_FWMSK_REG_USB_M_RXWARN31_Pos (4UL)                  /*!< USB_M_RXWARN31（位4）*/
#define USB_USB_FWMSK_REG_USB_M_RXWARN31_Msk (0x70UL)               /*!< USB_M_RXWARN31（位域掩码：0x07）*/
#define USB_USB_FWMSK_REG_USB_M_TXWARN31_Pos (0UL)                  /*!< USB_M_TXWARN31（位0）*/
#define USB_USB_FWMSK_REG_USB_M_TXWARN31_Msk (0x7UL)                /*!< USB_M_TXWARN31（位域掩码：0x07）*/
/* =====================================================  USB_MAEV_REG  ====================================================== */
#define USB_USB_MAEV_REG_USB_CH_EV_Pos    (11UL)                    /*!< USB_CH_EV（位11）*/
#define USB_USB_MAEV_REG_USB_CH_EV_Msk    (0x800UL)                 /*!< USB_CH_EV（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_EP0_NAK_Pos  (10UL)                    /*!< USB_EP0_NK（位10）*/
#define USB_USB_MAEV_REG_USB_EP0_NAK_Msk  (0x400UL)                 /*!< USB_EP0_NK（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_EP0_RX_Pos   (9UL)                     /*!< USB_EP0_RX（第9位）*/
#define USB_USB_MAEV_REG_USB_EP0_RX_Msk   (0x200UL)                 /*!< USB_EP0_RX（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_EP0_TX_Pos   (8UL)                     /*!< USB_EP0_TX（位8）*/
#define USB_USB_MAEV_REG_USB_EP0_TX_Msk   (0x100UL)                 /*!< USB_EP0_TX（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_INTR_Pos     (7UL)                     /*!< USB_INTR（第7位）*/
#define USB_USB_MAEV_REG_USB_INTR_Msk     (0x80UL)                  /*!< USB_INTR（位字段掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_RX_EV_Pos    (6UL)                     /*!< USB_RX_EV（位6）*/
#define USB_USB_MAEV_REG_USB_RX_EV_Msk    (0x40UL)                  /*!< USB_RX_EV（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_ULD_Pos      (5UL)                     /*!< USB_ULD（第5位）*/
#define USB_USB_MAEV_REG_USB_ULD_Msk      (0x20UL)                  /*!< USB_ULD（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_NAK_Pos      (4UL)                     /*!< USB_NK（位4）*/
#define USB_USB_MAEV_REG_USB_NAK_Msk      (0x10UL)                  /*!< USB_NK（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_FRAME_Pos    (3UL)                     /*!< USB_FRAME（位3）*/
#define USB_USB_MAEV_REG_USB_FRAME_Msk    (0x8UL)                   /*!< USB_FRAME（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_TX_EV_Pos    (2UL)                     /*!< USB_TX_EV（位2）*/
#define USB_USB_MAEV_REG_USB_TX_EV_Msk    (0x4UL)                   /*!< USB_TX_EV（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_ALT_Pos      (1UL)                     /*!< USB_ALT（位1）*/
#define USB_USB_MAEV_REG_USB_ALT_Msk      (0x2UL)                   /*!< USB_ALT（位域掩码：0x01）*/
#define USB_USB_MAEV_REG_USB_WARN_Pos     (0UL)                     /*!< USB_WARN（位0）*/
#define USB_USB_MAEV_REG_USB_WARN_Msk     (0x1UL)                   /*!< USB_WARN（位域掩码：0x01）*/
/* =====================================================  USB_MAMSK_REG  ===================================================== */
#define USB_USB_MAMSK_REG_USB_M_CH_EV_Pos (11UL)                    /*!< USB_M_CH_EV（位11）*/
#define USB_USB_MAMSK_REG_USB_M_CH_EV_Msk (0x800UL)                 /*!< USB_M_CH_EV（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_EP0_NAK_Pos (10UL)                  /*!< USB_M_EP0_NAMEK（位10）*/
#define USB_USB_MAMSK_REG_USB_M_EP0_NAK_Msk (0x400UL)               /*!< USB_M_EP0_NAMEK（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_EP0_RX_Pos (9UL)                    /*!< USB_M_EP0_RX（位9）*/
#define USB_USB_MAMSK_REG_USB_M_EP0_RX_Msk (0x200UL)                /*!< USB_M_EP0_RX（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_EP0_TX_Pos (8UL)                    /*!< USB_M_EP0_TX（位8）*/
#define USB_USB_MAMSK_REG_USB_M_EP0_TX_Msk (0x100UL)                /*!< USB_M_EP0_TX（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_INTR_Pos  (7UL)                     /*!< USB_M_INTR（第7位）*/
#define USB_USB_MAMSK_REG_USB_M_INTR_Msk  (0x80UL)                  /*!< USB_M_INTR（位字段掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_RX_EV_Pos (6UL)                     /*!< USB_M_RX_EV（位6）*/
#define USB_USB_MAMSK_REG_USB_M_RX_EV_Msk (0x40UL)                  /*!< USB_M_RX_EV（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_ULD_Pos   (5UL)                     /*!< USB_M_ULD（第5位）*/
#define USB_USB_MAMSK_REG_USB_M_ULD_Msk   (0x20UL)                  /*!< USB_M_ULD（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_NAK_Pos   (4UL)                     /*!< USB_M_NAK（位4）*/
#define USB_USB_MAMSK_REG_USB_M_NAK_Msk   (0x10UL)                  /*!< USB_M_NK（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_FRAME_Pos (3UL)                     /*!< USB_M_FRAME（位3）*/
#define USB_USB_MAMSK_REG_USB_M_FRAME_Msk (0x8UL)                   /*!< USB_M_FRAME（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_TX_EV_Pos (2UL)                     /*!< USB_M_TX_EV（位2）*/
#define USB_USB_MAMSK_REG_USB_M_TX_EV_Msk (0x4UL)                   /*!< USB_M_TX_EV（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_ALT_Pos   (1UL)                     /*!< USB_M_ALT（位1）*/
#define USB_USB_MAMSK_REG_USB_M_ALT_Msk   (0x2UL)                   /*!< USB_M_ALT（位域掩码：0x01）*/
#define USB_USB_MAMSK_REG_USB_M_WARN_Pos  (0UL)                     /*!< USB_M_WARN（位0）*/
#define USB_USB_MAMSK_REG_USB_M_WARN_Msk  (0x1UL)                   /*!< USB_M_WARN（位域掩码：0x01）*/
/* =====================================================  USB_MCTRL_REG  ===================================================== */
#define USB_USB_MCTRL_REG_LSMODE_Pos      (4UL)                     /*!< LSMODE（位4）*/
#define USB_USB_MCTRL_REG_LSMODE_Msk      (0x10UL)                  /*!< LSMODE（位域掩码：0x01）*/
#define USB_USB_MCTRL_REG_USB_NAT_Pos     (3UL)                     /*!< USB_NAT（位3）*/
#define USB_USB_MCTRL_REG_USB_NAT_Msk     (0x8UL)                   /*!< USB_NAT（位域掩码：0x01）*/
#define USB_USB_MCTRL_REG_USB_DBG_Pos     (1UL)                     /*!< USB_DBG（位1）*/
#define USB_USB_MCTRL_REG_USB_DBG_Msk     (0x2UL)                   /*!< USB_DBG（位域掩码：0x01）*/
#define USB_USB_MCTRL_REG_USBEN_Pos       (0UL)                     /*!< USBEN（位0）*/
#define USB_USB_MCTRL_REG_USBEN_Msk       (0x1UL)                   /*!< USBEN（位域掩码：0x01）*/
/* =====================================================  USB_NAKEV_REG  ===================================================== */
#define USB_USB_NAKEV_REG_USB_OUT31_Pos   (4UL)                     /*!< USB_OUT31（位4）*/
#define USB_USB_NAKEV_REG_USB_OUT31_Msk   (0x70UL)                  /*!< USB_OUT31（位域掩码：0x07）*/
#define USB_USB_NAKEV_REG_USB_IN31_Pos    (0UL)                     /*!< USB_IN31（位0）*/
#define USB_USB_NAKEV_REG_USB_IN31_Msk    (0x7UL)                   /*!< USB_IN31（位域掩码：0x07）*/
/* ====================================================  USB_NAKMSK_REG  ===================================================== */
#define USB_USB_NAKMSK_REG_USB_M_OUT31_Pos (4UL)                    /*!< USB_M_OUT31（位4）*/
#define USB_USB_NAKMSK_REG_USB_M_OUT31_Msk (0x70UL)                 /*!< USB_M_OUT31（位域掩码：0x07）*/
#define USB_USB_NAKMSK_REG_USB_M_IN31_Pos (0UL)                     /*!< USB_M_IN31（位0）*/
#define USB_USB_NAKMSK_REG_USB_M_IN31_Msk (0x7UL)                   /*!< USB_M_IN31（位字段掩码：0x07）*/
/* =====================================================  USB_NFSR_REG  ====================================================== */
#define USB_USB_NFSR_REG_USB_NFS_Pos      (0UL)                     /*!< USB_NFS（位0）*/
#define USB_USB_NFSR_REG_USB_NFS_Msk      (0x3UL)                   /*!< USB_NFS（位域掩码：0x03）*/
/* =====================================================  USB_RXC0_REG  ====================================================== */
#define USB_USB_RXC0_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_RXC0_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_RXC0_REG_USB_IGN_SETUP_Pos (2UL)                    /*!< USB_IGN_SETUP（位2）*/
#define USB_USB_RXC0_REG_USB_IGN_SETUP_Msk (0x4UL)                  /*!< USB_IGN_SETUP（位域掩码：0x01）*/
#define USB_USB_RXC0_REG_USB_IGN_OUT_Pos  (1UL)                     /*!< USB_IGN_OUT（位1）*/
#define USB_USB_RXC0_REG_USB_IGN_OUT_Msk  (0x2UL)                   /*!< USB_IGN_OUT（位域掩码：0x01）*/
#define USB_USB_RXC0_REG_USB_RX_EN_Pos    (0UL)                     /*!< USB_RX_EN（位0）*/
#define USB_USB_RXC0_REG_USB_RX_EN_Msk    (0x1UL)                   /*!< USB_RX_EN（位域掩码：0x01）*/
/* =====================================================  USB_RXC1_REG  ====================================================== */
#define USB_USB_RXC1_REG_USB_RFWL_Pos     (5UL)                     /*!< USB_RFWL（第5位）*/
#define USB_USB_RXC1_REG_USB_RFWL_Msk     (0x60UL)                  /*!< USB_RFWL（位域掩码：0x03）*/
#define USB_USB_RXC1_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_RXC1_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_RXC1_REG_USB_IGN_SETUP_Pos (2UL)                    /*!< USB_IGN_SETUP（位2）*/
#define USB_USB_RXC1_REG_USB_IGN_SETUP_Msk (0x4UL)                  /*!< USB_IGN_SETUP（位域掩码：0x01）*/
#define USB_USB_RXC1_REG_USB_RX_EN_Pos    (0UL)                     /*!< USB_RX_EN（位0）*/
#define USB_USB_RXC1_REG_USB_RX_EN_Msk    (0x1UL)                   /*!< USB_RX_EN（位域掩码：0x01）*/
/* =====================================================  USB_RXC2_REG  ====================================================== */
#define USB_USB_RXC2_REG_USB_RFWL_Pos     (5UL)                     /*!< USB_RFWL（第5位）*/
#define USB_USB_RXC2_REG_USB_RFWL_Msk     (0x60UL)                  /*!< USB_RFWL（位域掩码：0x03）*/
#define USB_USB_RXC2_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_RXC2_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_RXC2_REG_USB_IGN_SETUP_Pos (2UL)                    /*!< USB_IGN_SETUP（位2）*/
#define USB_USB_RXC2_REG_USB_IGN_SETUP_Msk (0x4UL)                  /*!< USB_IGN_SETUP（位域掩码：0x01）*/
#define USB_USB_RXC2_REG_USB_RX_EN_Pos    (0UL)                     /*!< USB_RX_EN（位0）*/
#define USB_USB_RXC2_REG_USB_RX_EN_Msk    (0x1UL)                   /*!< USB_RX_EN（位域掩码：0x01）*/
/* =====================================================  USB_RXC3_REG  ====================================================== */
#define USB_USB_RXC3_REG_USB_RFWL_Pos     (5UL)                     /*!< USB_RFWL（第5位）*/
#define USB_USB_RXC3_REG_USB_RFWL_Msk     (0x60UL)                  /*!< USB_RFWL（位域掩码：0x03）*/
#define USB_USB_RXC3_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_RXC3_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_RXC3_REG_USB_IGN_SETUP_Pos (2UL)                    /*!< USB_IGN_SETUP（位2）*/
#define USB_USB_RXC3_REG_USB_IGN_SETUP_Msk (0x4UL)                  /*!< USB_IGN_SETUP（位域掩码：0x01）*/
#define USB_USB_RXC3_REG_USB_RX_EN_Pos    (0UL)                     /*!< USB_RX_EN（位0）*/
#define USB_USB_RXC3_REG_USB_RX_EN_Msk    (0x1UL)                   /*!< USB_RX_EN（位域掩码：0x01）*/
/* =====================================================  USB_RXD0_REG  ====================================================== */
#define USB_USB_RXD0_REG_USB_RXFD_Pos     (0UL)                     /*!< USB_RXFD（位0）*/
#define USB_USB_RXD0_REG_USB_RXFD_Msk     (0xffUL)                  /*!< USB_RXFD（位域掩码：0xff）*/
/* =====================================================  USB_RXD1_REG  ====================================================== */
#define USB_USB_RXD1_REG_USB_RXFD_Pos     (0UL)                     /*!< USB_RXFD（位0）*/
#define USB_USB_RXD1_REG_USB_RXFD_Msk     (0xffUL)                  /*!< USB_RXFD（位域掩码：0xff）*/
/* =====================================================  USB_RXD2_REG  ====================================================== */
#define USB_USB_RXD2_REG_USB_RXFD_Pos     (0UL)                     /*!< USB_RXFD（位0）*/
#define USB_USB_RXD2_REG_USB_RXFD_Msk     (0xffUL)                  /*!< USB_RXFD（位域掩码：0xff）*/
/* =====================================================  USB_RXD3_REG  ====================================================== */
#define USB_USB_RXD3_REG_USB_RXFD_Pos     (0UL)                     /*!< USB_RXFD（位0）*/
#define USB_USB_RXD3_REG_USB_RXFD_Msk     (0xffUL)                  /*!< USB_RXFD（位域掩码：0xff）*/
/* =====================================================  USB_RXEV_REG  ====================================================== */
#define USB_USB_RXEV_REG_USB_RXOVRRN31_Pos (4UL)                    /*!< USB_RXOVRRN31（位4）*/
#define USB_USB_RXEV_REG_USB_RXOVRRN31_Msk (0x70UL)                 /*!< USB_RXOVRRN31（位域掩码：0x07）*/
#define USB_USB_RXEV_REG_USB_RXFIFO31_Pos (0UL)                     /*!< USB_RXFIFO31（位0）*/
#define USB_USB_RXEV_REG_USB_RXFIFO31_Msk (0x7UL)                   /*!< USB_RXFIFO31（位域掩码：0x07）*/
/* =====================================================  USB_RXMSK_REG  ===================================================== */
#define USB_USB_RXMSK_REG_USB_M_RXOVRRN31_Pos (4UL)                 /*!< USB_M_RXOVRRN31（位4）*/
#define USB_USB_RXMSK_REG_USB_M_RXOVRRN31_Msk (0x70UL)              /*!< USB_M_RXOVRRN31（位域掩码：0x07）*/
#define USB_USB_RXMSK_REG_USB_M_RXFIFO31_Pos (0UL)                  /*!< USB_M_RXFIFO31（位0）*/
#define USB_USB_RXMSK_REG_USB_M_RXFIFO31_Msk (0x7UL)                /*!< USB_M_RXFIFO31（位域掩码：0x07）*/
/* =====================================================  USB_RXS0_REG  ====================================================== */
#define USB_USB_RXS0_REG_USB_SETUP_Pos    (6UL)                     /*!< USB_SETUP（位6）*/
#define USB_USB_RXS0_REG_USB_SETUP_Msk    (0x40UL)                  /*!< USB_SETUP（位域掩码：0x01）*/
#define USB_USB_RXS0_REG_USB_TOGGLE_RX0_Pos (5UL)                   /*!< USB_TOGGLE_RX0（第5位）*/
#define USB_USB_RXS0_REG_USB_TOGGLE_RX0_Msk (0x20UL)                /*!< USB_TOGGLE_RX0（位域掩码：0x01）*/
#define USB_USB_RXS0_REG_USB_RX_LAST_Pos  (4UL)                     /*!< USB_RX_LAST（位4）*/
#define USB_USB_RXS0_REG_USB_RX_LAST_Msk  (0x10UL)                  /*!< USB_RX_LAST（位域掩码：0x01）*/
#define USB_USB_RXS0_REG_USB_RCOUNT_Pos   (0UL)                     /*!< USB_RCOUNT（位0）*/
#define USB_USB_RXS0_REG_USB_RCOUNT_Msk   (0xfUL)                   /*!< USB_RCOUNT（位域掩码：0x0f）*/
/* =====================================================  USB_RXS1_REG  ====================================================== */
#define USB_USB_RXS1_REG_USB_RXCOUNT_Pos  (8UL)                     /*!< USB_RXCOUNT（位8）*/
#define USB_USB_RXS1_REG_USB_RXCOUNT_Msk  (0x7f00UL)                /*!< USB_RXCOUNT（位域掩码：0x7f）*/
#define USB_USB_RXS1_REG_USB_RX_ERR_Pos   (7UL)                     /*!< USB_RX_ERR（第7位）*/
#define USB_USB_RXS1_REG_USB_RX_ERR_Msk   (0x80UL)                  /*!< USB_RX_ERR（位字段掩码：0x01）*/
#define USB_USB_RXS1_REG_USB_SETUP_Pos    (6UL)                     /*!< USB_SETUP（位6）*/
#define USB_USB_RXS1_REG_USB_SETUP_Msk    (0x40UL)                  /*!< USB_SETUP（位域掩码：0x01）*/
#define USB_USB_RXS1_REG_USB_TOGGLE_RX_Pos (5UL)                    /*!< USB_TOGGLE_RX（第5位）*/
#define USB_USB_RXS1_REG_USB_TOGGLE_RX_Msk (0x20UL)                 /*!< USB_TOGGLE_RX（位域掩码：0x01）*/
#define USB_USB_RXS1_REG_USB_RX_LAST_Pos  (4UL)                     /*!< USB_RX_LAST（位4）*/
#define USB_USB_RXS1_REG_USB_RX_LAST_Msk  (0x10UL)                  /*!< USB_RX_LAST（位域掩码：0x01）*/
#define USB_USB_RXS1_REG_USB_RCOUNT_Pos   (0UL)                     /*!< USB_RCOUNT（位0）*/
#define USB_USB_RXS1_REG_USB_RCOUNT_Msk   (0xfUL)                   /*!< USB_RCOUNT（位域掩码：0x0f）*/
/* =====================================================  USB_RXS2_REG  ====================================================== */
#define USB_USB_RXS2_REG_USB_RXCOUNT_Pos  (8UL)                     /*!< USB_RXCOUNT（位8）*/
#define USB_USB_RXS2_REG_USB_RXCOUNT_Msk  (0x7f00UL)                /*!< USB_RXCOUNT（位域掩码：0x7f）*/
#define USB_USB_RXS2_REG_USB_RX_ERR_Pos   (7UL)                     /*!< USB_RX_ERR（第7位）*/
#define USB_USB_RXS2_REG_USB_RX_ERR_Msk   (0x80UL)                  /*!< USB_RX_ERR（位字段掩码：0x01）*/
#define USB_USB_RXS2_REG_USB_SETUP_Pos    (6UL)                     /*!< USB_SETUP（位6）*/
#define USB_USB_RXS2_REG_USB_SETUP_Msk    (0x40UL)                  /*!< USB_SETUP（位域掩码：0x01）*/
#define USB_USB_RXS2_REG_USB_TOGGLE_RX_Pos (5UL)                    /*!< USB_TOGGLE_RX（第5位）*/
#define USB_USB_RXS2_REG_USB_TOGGLE_RX_Msk (0x20UL)                 /*!< USB_TOGGLE_RX（位域掩码：0x01）*/
#define USB_USB_RXS2_REG_USB_RX_LAST_Pos  (4UL)                     /*!< USB_RX_LAST（位4）*/
#define USB_USB_RXS2_REG_USB_RX_LAST_Msk  (0x10UL)                  /*!< USB_RX_LAST（位域掩码：0x01）*/
#define USB_USB_RXS2_REG_USB_RCOUNT_Pos   (0UL)                     /*!< USB_RCOUNT（位0）*/
#define USB_USB_RXS2_REG_USB_RCOUNT_Msk   (0xfUL)                   /*!< USB_RCOUNT（位域掩码：0x0f）*/
/* =====================================================  USB_RXS3_REG  ====================================================== */
#define USB_USB_RXS3_REG_USB_RXCOUNT_Pos  (8UL)                     /*!< USB_RXCOUNT（位8）*/
#define USB_USB_RXS3_REG_USB_RXCOUNT_Msk  (0x7f00UL)                /*!< USB_RXCOUNT（位域掩码：0x7f）*/
#define USB_USB_RXS3_REG_USB_RX_ERR_Pos   (7UL)                     /*!< USB_RX_ERR（第7位）*/
#define USB_USB_RXS3_REG_USB_RX_ERR_Msk   (0x80UL)                  /*!< USB_RX_ERR（位字段掩码：0x01）*/
#define USB_USB_RXS3_REG_USB_SETUP_Pos    (6UL)                     /*!< USB_SETUP（位6）*/
#define USB_USB_RXS3_REG_USB_SETUP_Msk    (0x40UL)                  /*!< USB_SETUP（位域掩码：0x01）*/
#define USB_USB_RXS3_REG_USB_TOGGLE_RX_Pos (5UL)                    /*!< USB_TOGGLE_RX（第5位）*/
#define USB_USB_RXS3_REG_USB_TOGGLE_RX_Msk (0x20UL)                 /*!< USB_TOGGLE_RX（位域掩码：0x01）*/
#define USB_USB_RXS3_REG_USB_RX_LAST_Pos  (4UL)                     /*!< USB_RX_LAST（位4）*/
#define USB_USB_RXS3_REG_USB_RX_LAST_Msk  (0x10UL)                  /*!< USB_RX_LAST（位域掩码：0x01）*/
#define USB_USB_RXS3_REG_USB_RCOUNT_Pos   (0UL)                     /*!< USB_RCOUNT（位0）*/
#define USB_USB_RXS3_REG_USB_RCOUNT_Msk   (0xfUL)                   /*!< USB_RCOUNT（位域掩码：0x0f）*/
/* ======================================================  USB_TCR_REG  ====================================================== */
#define USB_USB_TCR_REG_USB_VADJ_Pos      (5UL)                     /*!< USB_VADJ（第5位）*/
#define USB_USB_TCR_REG_USB_VADJ_Msk      (0xe0UL)                  /*!< USB_VADJ（位域掩码：0x07）*/
#define USB_USB_TCR_REG_USB_CADJ_Pos      (0UL)                     /*!< USB_CADJ（位0）*/
#define USB_USB_TCR_REG_USB_CADJ_Msk      (0x1fUL)                  /*!< USB_CADJ（位域掩码：0x1f）*/
/* =====================================================  USB_TXC0_REG  ====================================================== */
#define USB_USB_TXC0_REG_USB_IGN_IN_Pos   (4UL)                     /*!< USB_IGN_IN（位4）*/
#define USB_USB_TXC0_REG_USB_IGN_IN_Msk   (0x10UL)                  /*!< USB_IGN_IN（位域掩码：0x01）*/
#define USB_USB_TXC0_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_TXC0_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_TXC0_REG_USB_TOGGLE_TX0_Pos (2UL)                   /*!< USB_TOGGLE_TX0（位2）*/
#define USB_USB_TXC0_REG_USB_TOGGLE_TX0_Msk (0x4UL)                 /*!< USB_TOGGLE_TX0（位域掩码：0x01）*/
#define USB_USB_TXC0_REG_USB_TX_EN_Pos    (0UL)                     /*!< USB_TX_EN（位0）*/
#define USB_USB_TXC0_REG_USB_TX_EN_Msk    (0x1UL)                   /*!< USB_TX_EN（位域掩码：0x01）*/
/* =====================================================  USB_TXC1_REG  ====================================================== */
#define USB_USB_TXC1_REG_USB_IGN_ISOMSK_Pos (7UL)                   /*!< USB_IGN_ISOMSK（位7）*/
#define USB_USB_TXC1_REG_USB_IGN_ISOMSK_Msk (0x80UL)                /*!< USB_IGN_ISOMSK（位域掩码：0x01）*/
#define USB_USB_TXC1_REG_USB_TFWL_Pos     (5UL)                     /*!< USB_TFWL（第5位）*/
#define USB_USB_TXC1_REG_USB_TFWL_Msk     (0x60UL)                  /*!< USB_TFWL（位域掩码：0x03）*/
#define USB_USB_TXC1_REG_USB_RFF_Pos      (4UL)                     /*!< USB_RFF（位4）*/
#define USB_USB_TXC1_REG_USB_RFF_Msk      (0x10UL)                  /*!< USB_RFF（位域掩码：0x01）*/
#define USB_USB_TXC1_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_TXC1_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_TXC1_REG_USB_TOGGLE_TX_Pos (2UL)                    /*!< USB_TOGGLE_TX（位2）*/
#define USB_USB_TXC1_REG_USB_TOGGLE_TX_Msk (0x4UL)                  /*!< USB_TOGGLE_TX（位域掩码：0x01）*/
#define USB_USB_TXC1_REG_USB_LAST_Pos     (1UL)                     /*!< USB_LAST（位1）*/
#define USB_USB_TXC1_REG_USB_LAST_Msk     (0x2UL)                   /*!< USB_LAST（位域掩码：0x01）*/
#define USB_USB_TXC1_REG_USB_TX_EN_Pos    (0UL)                     /*!< USB_TX_EN（位0）*/
#define USB_USB_TXC1_REG_USB_TX_EN_Msk    (0x1UL)                   /*!< USB_TX_EN（位域掩码：0x01）*/
/* =====================================================  USB_TXC2_REG  ====================================================== */
#define USB_USB_TXC2_REG_USB_IGN_ISOMSK_Pos (7UL)                   /*!< USB_IGN_ISOMSK（位7）*/
#define USB_USB_TXC2_REG_USB_IGN_ISOMSK_Msk (0x80UL)                /*!< USB_IGN_ISOMSK（位域掩码：0x01）*/
#define USB_USB_TXC2_REG_USB_TFWL_Pos     (5UL)                     /*!< USB_TFWL（第5位）*/
#define USB_USB_TXC2_REG_USB_TFWL_Msk     (0x60UL)                  /*!< USB_TFWL（位域掩码：0x03）*/
#define USB_USB_TXC2_REG_USB_RFF_Pos      (4UL)                     /*!< USB_RFF（位4）*/
#define USB_USB_TXC2_REG_USB_RFF_Msk      (0x10UL)                  /*!< USB_RFF（位域掩码：0x01）*/
#define USB_USB_TXC2_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_TXC2_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_TXC2_REG_USB_TOGGLE_TX_Pos (2UL)                    /*!< USB_TOGGLE_TX（位2）*/
#define USB_USB_TXC2_REG_USB_TOGGLE_TX_Msk (0x4UL)                  /*!< USB_TOGGLE_TX（位域掩码：0x01）*/
#define USB_USB_TXC2_REG_USB_LAST_Pos     (1UL)                     /*!< USB_LAST（位1）*/
#define USB_USB_TXC2_REG_USB_LAST_Msk     (0x2UL)                   /*!< USB_LAST（位域掩码：0x01）*/
#define USB_USB_TXC2_REG_USB_TX_EN_Pos    (0UL)                     /*!< USB_TX_EN（位0）*/
#define USB_USB_TXC2_REG_USB_TX_EN_Msk    (0x1UL)                   /*!< USB_TX_EN（位域掩码：0x01）*/
/* =====================================================  USB_TXC3_REG  ====================================================== */
#define USB_USB_TXC3_REG_USB_IGN_ISOMSK_Pos (7UL)                   /*!< USB_IGN_ISOMSK（位7）*/
#define USB_USB_TXC3_REG_USB_IGN_ISOMSK_Msk (0x80UL)                /*!< USB_IGN_ISOMSK（位域掩码：0x01）*/
#define USB_USB_TXC3_REG_USB_TFWL_Pos     (5UL)                     /*!< USB_TFWL（第5位）*/
#define USB_USB_TXC3_REG_USB_TFWL_Msk     (0x60UL)                  /*!< USB_TFWL（位域掩码：0x03）*/
#define USB_USB_TXC3_REG_USB_RFF_Pos      (4UL)                     /*!< USB_RFF（位4）*/
#define USB_USB_TXC3_REG_USB_RFF_Msk      (0x10UL)                  /*!< USB_RFF（位域掩码：0x01）*/
#define USB_USB_TXC3_REG_USB_FLUSH_Pos    (3UL)                     /*!< USB_FLUSH（位3）*/
#define USB_USB_TXC3_REG_USB_FLUSH_Msk    (0x8UL)                   /*!< USB_FLUSH（位域掩码：0x01）*/
#define USB_USB_TXC3_REG_USB_TOGGLE_TX_Pos (2UL)                    /*!< USB_TOGGLE_TX（位2）*/
#define USB_USB_TXC3_REG_USB_TOGGLE_TX_Msk (0x4UL)                  /*!< USB_TOGGLE_TX（位域掩码：0x01）*/
#define USB_USB_TXC3_REG_USB_LAST_Pos     (1UL)                     /*!< USB_LAST（位1）*/
#define USB_USB_TXC3_REG_USB_LAST_Msk     (0x2UL)                   /*!< USB_LAST（位域掩码：0x01）*/
#define USB_USB_TXC3_REG_USB_TX_EN_Pos    (0UL)                     /*!< USB_TX_EN（位0）*/
#define USB_USB_TXC3_REG_USB_TX_EN_Msk    (0x1UL)                   /*!< USB_TX_EN（位域掩码：0x01）*/
/* =====================================================  USB_TXD0_REG  ====================================================== */
#define USB_USB_TXD0_REG_USB_TXFD_Pos     (0UL)                     /*!< USB_TXFD（位0）*/
#define USB_USB_TXD0_REG_USB_TXFD_Msk     (0xffUL)                  /*!< USB_TXFD（位域掩码：0xff）*/
/* =====================================================  USB_TXD1_REG  ====================================================== */
#define USB_USB_TXD1_REG_USB_TXFD_Pos     (0UL)                     /*!< USB_TXFD（位0）*/
#define USB_USB_TXD1_REG_USB_TXFD_Msk     (0xffUL)                  /*!< USB_TXFD（位域掩码：0xff）*/
/* =====================================================  USB_TXD2_REG  ====================================================== */
#define USB_USB_TXD2_REG_USB_TXFD_Pos     (0UL)                     /*!< USB_TXFD（位0）*/
#define USB_USB_TXD2_REG_USB_TXFD_Msk     (0xffUL)                  /*!< USB_TXFD（位域掩码：0xff）*/
/* =====================================================  USB_TXD3_REG  ====================================================== */
#define USB_USB_TXD3_REG_USB_TXFD_Pos     (0UL)                     /*!< USB_TXFD（位0）*/
#define USB_USB_TXD3_REG_USB_TXFD_Msk     (0xffUL)                  /*!< USB_TXFD（位域掩码：0xff）*/
/* =====================================================  USB_TXEV_REG  ====================================================== */
#define USB_USB_TXEV_REG_USB_TXUDRRN31_Pos (4UL)                    /*!< USB_TXUDRRN31（位4）*/
#define USB_USB_TXEV_REG_USB_TXUDRRN31_Msk (0x70UL)                 /*!< USB_TXUDRRN31（位域掩码：0x07）*/
#define USB_USB_TXEV_REG_USB_TXFIFO31_Pos (0UL)                     /*!< USB_TXFIFO31（位0）*/
#define USB_USB_TXEV_REG_USB_TXFIFO31_Msk (0x7UL)                   /*!< USB_TXFIFO31（位域掩码：0x07）*/
/* =====================================================  USB_TXMSK_REG  ===================================================== */
#define USB_USB_TXMSK_REG_USB_M_TXUDRRN31_Pos (4UL)                 /*!< USB_M_TXUDRRN31（位4）*/
#define USB_USB_TXMSK_REG_USB_M_TXUDRRN31_Msk (0x70UL)              /*!< USB_M_TXUDRRN31（位域掩码：0x07）*/
#define USB_USB_TXMSK_REG_USB_M_TXFIFO31_Pos (0UL)                  /*!< USB_M_TXFIFO31（位0）*/
#define USB_USB_TXMSK_REG_USB_M_TXFIFO31_Msk (0x7UL)                /*!< USB_M_TXFIFO31（位域掩码：0x07）*/
/* =====================================================  USB_TXS0_REG  ====================================================== */
#define USB_USB_TXS0_REG_USB_ACK_STAT_Pos (6UL)                     /*!< USB_ACK_STAT（位6）*/
#define USB_USB_TXS0_REG_USB_ACK_STAT_Msk (0x40UL)                  /*!< USB_ACK_STAT（位字段掩码：0x01）*/
#define USB_USB_TXS0_REG_USB_TX_DONE_Pos  (5UL)                     /*!< USB_TX_DONE（第5位）*/
#define USB_USB_TXS0_REG_USB_TX_DONE_Msk  (0x20UL)                  /*!< USB_TX_DONE（位域掩码：0x01）*/
#define USB_USB_TXS0_REG_USB_TCOUNT_Pos   (0UL)                     /*!< USB_TCOUNT（位0）*/
#define USB_USB_TXS0_REG_USB_TCOUNT_Msk   (0x1fUL)                  /*!< USB_TCOUNT（位域掩码：0x1f）*/
/* =====================================================  USB_TXS1_REG  ====================================================== */
#define USB_USB_TXS1_REG_USB_TX_URUN_Pos  (7UL)                     /*!< USB_TX_URUN（第7位）*/
#define USB_USB_TXS1_REG_USB_TX_URUN_Msk  (0x80UL)                  /*!< USB_TX_URUN（位域掩码：0x01）*/
#define USB_USB_TXS1_REG_USB_ACK_STAT_Pos (6UL)                     /*!< USB_ACK_STAT（位6）*/
#define USB_USB_TXS1_REG_USB_ACK_STAT_Msk (0x40UL)                  /*!< USB_ACK_STAT（位字段掩码：0x01）*/
#define USB_USB_TXS1_REG_USB_TX_DONE_Pos  (5UL)                     /*!< USB_TX_DONE（第5位）*/
#define USB_USB_TXS1_REG_USB_TX_DONE_Msk  (0x20UL)                  /*!< USB_TX_DONE（位域掩码：0x01）*/
#define USB_USB_TXS1_REG_USB_TCOUNT_Pos   (0UL)                     /*!< USB_TCOUNT（位0）*/
#define USB_USB_TXS1_REG_USB_TCOUNT_Msk   (0x1fUL)                  /*!< USB_TCOUNT（位域掩码：0x1f）*/
/* =====================================================  USB_TXS2_REG  ====================================================== */
#define USB_USB_TXS2_REG_USB_TX_URUN_Pos  (7UL)                     /*!< USB_TX_URUN（第7位）*/
#define USB_USB_TXS2_REG_USB_TX_URUN_Msk  (0x80UL)                  /*!< USB_TX_URUN（位域掩码：0x01）*/
#define USB_USB_TXS2_REG_USB_ACK_STAT_Pos (6UL)                     /*!< USB_ACK_STAT（位6）*/
#define USB_USB_TXS2_REG_USB_ACK_STAT_Msk (0x40UL)                  /*!< USB_ACK_STAT（位字段掩码：0x01）*/
#define USB_USB_TXS2_REG_USB_TX_DONE_Pos  (5UL)                     /*!< USB_TX_DONE（第5位）*/
#define USB_USB_TXS2_REG_USB_TX_DONE_Msk  (0x20UL)                  /*!< USB_TX_DONE（位域掩码：0x01）*/
#define USB_USB_TXS2_REG_USB_TCOUNT_Pos   (0UL)                     /*!< USB_TCOUNT（位0）*/
#define USB_USB_TXS2_REG_USB_TCOUNT_Msk   (0x1fUL)                  /*!< USB_TCOUNT（位域掩码：0x1f）*/
/* =====================================================  USB_TXS3_REG  ====================================================== */
#define USB_USB_TXS3_REG_USB_TX_URUN_Pos  (7UL)                     /*!< USB_TX_URUN（第7位）*/
#define USB_USB_TXS3_REG_USB_TX_URUN_Msk  (0x80UL)                  /*!< USB_TX_URUN（位域掩码：0x01）*/
#define USB_USB_TXS3_REG_USB_ACK_STAT_Pos (6UL)                     /*!< USB_ACK_STAT（位6）*/
#define USB_USB_TXS3_REG_USB_ACK_STAT_Msk (0x40UL)                  /*!< USB_ACK_STAT（位字段掩码：0x01）*/
#define USB_USB_TXS3_REG_USB_TX_DONE_Pos  (5UL)                     /*!< USB_TX_DONE（第5位）*/
#define USB_USB_TXS3_REG_USB_TX_DONE_Msk  (0x20UL)                  /*!< USB_TX_DONE（位域掩码：0x01）*/
#define USB_USB_TXS3_REG_USB_TCOUNT_Pos   (0UL)                     /*!< USB_TCOUNT（位0）*/
#define USB_USB_TXS3_REG_USB_TCOUNT_Msk   (0x1fUL)                  /*!< USB_TCOUNT（位域掩码：0x1f）*/
/* ======================================================  USB_UTR_REG  ====================================================== */
#define USB_USB_UTR_REG_USB_DIAG_Pos      (7UL)                     /*!< USB_DIAG（第7位）*/
#define USB_USB_UTR_REG_USB_DIAG_Msk      (0x80UL)                  /*!< USB_DIAG（位域掩码：0x01）*/
#define USB_USB_UTR_REG_USB_NCRC_Pos      (6UL)                     /*!< USB_NCRC（第6位）*/
#define USB_USB_UTR_REG_USB_NCRC_Msk      (0x40UL)                  /*!< USB_NCRC（位域掩码：0x01）*/
#define USB_USB_UTR_REG_USB_SF_Pos        (5UL)                     /*!< USB_SF（位5）*/
#define USB_USB_UTR_REG_USB_SF_Msk        (0x20UL)                  /*!< USB_SF（位域掩码：0x01）*/
#define USB_USB_UTR_REG_USB_UTR_RES_Pos   (0UL)                     /*!< USB_UTR_RES（位0）*/
#define USB_USB_UTR_REG_USB_UTR_RES_Msk   (0x1fUL)                  /*!< USB_UTR_RES（位域掩码：0x1f）*/
/* ====================================================  USB_UX20CDR_REG  ==================================================== */
#define USB_USB_UX20CDR_REG_RPU_TEST7_Pos (7UL)                     /*!< RPU_TEST7（第7位）*/
#define USB_USB_UX20CDR_REG_RPU_TEST7_Msk (0x80UL)                  /*!< RPU_TEST7（位字段掩码：0x01）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_SW2_Pos (6UL)                  /*!< RPU_TEST_SW2（位6）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_SW2_Msk (0x40UL)               /*!< RPU_TEST_SW2（位字段掩码：0x01）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_SW1_Pos (5UL)                  /*!< RPU_TEST_SW1（位5）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_SW1_Msk (0x20UL)               /*!< RPU_TEST_SW1（位字段掩码：0x01）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_EN_Pos (4UL)                   /*!< RPU_TEST_EN（位4）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_EN_Msk (0x10UL)                /*!< RPU_TEST_EN（位字段掩码：0x01）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_SW1DM_Pos (2UL)                /*!< RPU_TEST_SW1DM（位2）*/
#define USB_USB_UX20CDR_REG_RPU_TEST_SW1DM_Msk (0x4UL)              /*!< RPU_TEST_SW1DM（位字段掩码：0x01）*/
#define USB_USB_UX20CDR_REG_RPU_RCDELAY_Pos (1UL)                   /*!< RPU_RCDELAY（位1）*/
#define USB_USB_UX20CDR_REG_RPU_RCDELAY_Msk (0x2UL)                 /*!< RPU_RCDELAY（位字段掩码：0x01）*/
#define USB_USB_UX20CDR_REG_RPU_SSPROTEN_Pos (0UL)                  /*!< RPU_SSPROTEN（位0）*/
#define USB_USB_UX20CDR_REG_RPU_SSPROTEN_Msk (0x1UL)                /*!< RPU_SSPROTEN（位字段掩码：0x01）*/
/* ====================================================  USB_XCVDIAG_REG  ==================================================== */
#define USB_USB_XCVDIAG_REG_USB_VPIN_Pos  (7UL)                     /*!< USB_VPIN（第7位）*/
#define USB_USB_XCVDIAG_REG_USB_VPIN_Msk  (0x80UL)                  /*!< USB_VPIN（位域掩码：0x01）*/
#define USB_USB_XCVDIAG_REG_USB_VMIN_Pos  (6UL)                     /*!< USB_VMIN（位6）*/
#define USB_USB_XCVDIAG_REG_USB_VMIN_Msk  (0x40UL)                  /*!< USB_VMIN（位域掩码：0x01）*/
#define USB_USB_XCVDIAG_REG_USB_RCV_Pos   (5UL)                     /*!< USB_RCV（第5位）*/
#define USB_USB_XCVDIAG_REG_USB_RCV_Msk   (0x20UL)                  /*!< USB_RCV（位域掩码：0x01）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TXEN_Pos (3UL)                  /*!< USB_XCV_TXEN（位3）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TXEN_Msk (0x8UL)                /*!< USB_XCV_TXEN（位域掩码：0x01）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TXn_Pos (2UL)                   /*!< USB_XCV_TXn（位2）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TXn_Msk (0x4UL)                 /*!< USB_XCV_TXn（位域掩码：0x01）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TXp_Pos (1UL)                   /*!< USB_XCV_TXp（位1）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TXp_Msk (0x2UL)                 /*!< USB_XCV_TXp（位域掩码：0x01）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TEST_Pos (0UL)                  /*!< USB_XCV_TEST（位0）*/
#define USB_USB_XCVDIAG_REG_USB_XCV_TEST_Msk (0x1UL)                /*!< USB_XCV_TEST（位域掩码：0x01）*/


/* =========================================================================================================================== */
/* ================                                          WAKEUP                                           ================ */
/* =========================================================================================================================== */

/* ===================================================  WKUP_CLEAR_P0_REG  =================================================== */
#define WAKEUP_WKUP_CLEAR_P0_REG_WKUP_CLEAR_P0_Pos (0UL)            /*!< WKUP_CLEAR_P0（位0）*/
#define WAKEUP_WKUP_CLEAR_P0_REG_WKUP_CLEAR_P0_Msk (0xffffffffUL)   /*!< WKUP_CLEAR_P0（位字段掩码：0xffffff）*/
/* ===================================================  WKUP_CLEAR_P1_REG  =================================================== */
#define WAKEUP_WKUP_CLEAR_P1_REG_WKUP_CLEAR_P1_Pos (0UL)            /*!< WKUP_CLEAR_P1（位0）*/
#define WAKEUP_WKUP_CLEAR_P1_REG_WKUP_CLEAR_P1_Msk (0x7fffffUL)     /*!< WKUP_CLEAR_P1（位字段掩码：0x7fffff）*/
/* =====================================================  WKUP_CTRL_REG  ===================================================== */
#define WAKEUP_WKUP_CTRL_REG_WKUP_ENABLE_IRQ_Pos (7UL)              /*!< WKUP_ENABLE_IRQ（位7）*/
#define WAKEUP_WKUP_CTRL_REG_WKUP_ENABLE_IRQ_Msk (0x80UL)           /*!< WKUP_ENABLE_IRQ（位字段掩码：0x01）*/
#define WAKEUP_WKUP_CTRL_REG_WKUP_SFT_KEYHIT_Pos (6UL)              /*!< WKUP_SFT_KEYHIT（位6）*/
#define WAKEUP_WKUP_CTRL_REG_WKUP_SFT_KEYHIT_Msk (0x40UL)           /*!< WKUP_SFT_KEYHIT（位字段掩码：0x01）*/
#define WAKEUP_WKUP_CTRL_REG_WKUP_DEB_VALUE_Pos (0UL)               /*!< WKUP_DEB_VALUE（位0）*/
#define WAKEUP_WKUP_CTRL_REG_WKUP_DEB_VALUE_Msk (0x3fUL)            /*!< WKUP_DEB_VALUE（位字段掩码：0x3f）*/
/* ====================================================  WKUP_POL_P0_REG  ==================================================== */
#define WAKEUP_WKUP_POL_P0_REG_WKUP_POL_P0_Pos (0UL)                /*!< WKUP_POL_P0（位0）*/
#define WAKEUP_WKUP_POL_P0_REG_WKUP_POL_P0_Msk (0xffffffffUL)       /*!< WKUP_POL_P0（位字段掩码：0xffffff）*/
/* ====================================================  WKUP_POL_P1_REG  ==================================================== */
#define WAKEUP_WKUP_POL_P1_REG_WKUP_POL_P1_Pos (0UL)                /*!< WKUP_POL_P1（位0）*/
#define WAKEUP_WKUP_POL_P1_REG_WKUP_POL_P1_Msk (0x7fffffUL)         /*!< WKUP_POL_P1（位字段掩码：0x7fffff）*/
/* ==================================================  WKUP_RESET_IRQ_REG  =================================================== */
#define WAKEUP_WKUP_RESET_IRQ_REG_WKUP_IRQ_RST_Pos (0UL)            /*!< WKUP_IRQ_RST（位0）*/
#define WAKEUP_WKUP_RESET_IRQ_REG_WKUP_IRQ_RST_Msk (0xffffUL)       /*!< WKUP_IRQ_RST（位字段掩码：0xffff）*/
/* ==================================================  WKUP_SELECT_P0_REG  =================================================== */
#define WAKEUP_WKUP_SELECT_P0_REG_WKUP_SELECT_P0_Pos (0UL)          /*!< WKUP_SELECT_P0（位0）*/
#define WAKEUP_WKUP_SELECT_P0_REG_WKUP_SELECT_P0_Msk (0xffffffffUL) /*!< WKUP_SELECT_P0（位字段掩码：0xffffff）*/
/* ==================================================  WKUP_SELECT_P1_REG  =================================================== */
#define WAKEUP_WKUP_SELECT_P1_REG_WKUP_SELECT_P1_Pos (0UL)          /*!< WKUP_SELECT_P1（位0）*/
#define WAKEUP_WKUP_SELECT_P1_REG_WKUP_SELECT_P1_Msk (0x7fffffUL)   /*!< WKUP_SELECT_P1（位字段掩码：0x7fffff）*/
/* =================================================  WKUP_SEL_GPIO_P0_REG  ================================================== */
#define WAKEUP_WKUP_SEL_GPIO_P0_REG_WKUP_SEL_GPIO_P0_Pos (0UL)      /*!< WKUP_SEL_GPIO_P0（位0）*/
#define WAKEUP_WKUP_SEL_GPIO_P0_REG_WKUP_SEL_GPIO_P0_Msk (0xffffffffUL) /*!< WKUP_SEL_GPIO_P0（位字段掩码：0xffffff）*/
/* =================================================  WKUP_SEL_GPIO_P1_REG  ================================================== */
#define WAKEUP_WKUP_SEL_GPIO_P1_REG_WKUP_SEL_GPIO_P1_Pos (0UL)      /*!< WKUP_SEL_GPIO_P1（位0）*/
#define WAKEUP_WKUP_SEL_GPIO_P1_REG_WKUP_SEL_GPIO_P1_Msk (0x7fffffUL) /*!< WKUP_SEL_GPIO_P1（位字段掩码：0x7fffff）*/
/* ==================================================  WKUP_STATUS_P0_REG  =================================================== */
#define WAKEUP_WKUP_STATUS_P0_REG_WKUP_STAT_P0_Pos (0UL)            /*!< WKUP_STAT_P0（位0）*/
#define WAKEUP_WKUP_STATUS_P0_REG_WKUP_STAT_P0_Msk (0xffffffffUL)   /*!< WKUP_STAT_P0（位字段掩码：0xffffff）*/
/* ==================================================  WKUP_STATUS_P1_REG  =================================================== */
#define WAKEUP_WKUP_STATUS_P1_REG_WKUP_STAT_P1_Pos (0UL)            /*!< WKUP_STAT_P1（位0）*/
#define WAKEUP_WKUP_STATUS_P1_REG_WKUP_STAT_P1_Msk (0x7fffffUL)     /*!< WKUP_STAT_P1（位字段掩码：0x7fffff）*/

/** @} */ /* PosMask_peripherals组结束*/


#ifdef __cplusplus
}
#endif

#endif /* DA1469X_H */


/** @} */ /* DA1469x组结束*/

/** @} */ /* PLA_BSP_REGISTERS组结束*/

