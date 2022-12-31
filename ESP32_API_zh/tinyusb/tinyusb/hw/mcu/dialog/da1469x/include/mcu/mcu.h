/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __MCU_MCU_H_
#define __MCU_MCU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DA1469xAB.h"

#define sec_text_ram_core   __attribute__((section(".text_ram"))) __attribute__((noinline))

#define MCU_SYSVIEW_INTERRUPTS \
    "I#1=Reset,I#2=MNI,I#3=HardFault,I#4=MemoryMgmt,I#5=BusFault,I#6=UsageFault," \
    "I#7=SecureFault,I#11=SVCall,I#12=DebugMonitor,I#14=PendSV,I#15=SysTick," \
    "I#16=SENSOR_NODE,I#17=DMA,I#18=CHARGER_STATE,I#19=CHARGER_ERROR," \
    "I#20=CMAC2SYS,I#21=UART,I#22=UART2,I#23=UART3,I#24=I2C,I#25=I2C2,I#26=SPI," \
    "I#27=SPI2,I#28=PCM,I#29=SRC_IN,I#30=SRC_OUT,I#31=USB,I#32=TIMER," \
    "I#33=TIMER2,I#34=RTC,I#35=KEY_WKUP_GPIO,I#36=PDC,I#37=VBUS,I#38=MRM," \
    "I#39=MOTOR_CONTROLLER,I#40=TRNG,I#41=DCDC,I#42=XTAL32M_RDY,I#43=ADC," \
    "I#44=ADC2,I#45=CRYPTO,I#46=CAPTIMER1,I#47=RFDIAG,I#48=LCD_CONTROLLER," \
    "I#49=PLL_LOCK,I#50=TIMER3,I#51=TIMER4,I#52=LRA,I#53=RTC_EVENT," \
    "I#54=GPIO_P0,I#55=GPIO_P1"

/**
* \简要GPIO功能
*
*/
typedef enum {
    MCU_GPIO_FUNC_GPIO = 0,                  /**< GPIO */
    MCU_GPIO_FUNC_UART_RX = 1,               /**<GPIO作为UART RX*/
    MCU_GPIO_FUNC_UART_TX = 2,               /**<GPIO作为UART TX*/
    MCU_GPIO_FUNC_UART2_RX = 3,              /**<GPIO作为UART2 RX*/
    MCU_GPIO_FUNC_UART2_TX = 4,              /**<GPIO作为UART2 TX*/
    MCU_GPIO_FUNC_UART2_CTSN = 5,            /**<GPIO作为UART2 CTSN*/
    MCU_GPIO_FUNC_UART2_RTSN = 6,            /**<GPIO作为UART2 RTSN*/
    MCU_GPIO_FUNC_UART3_RX = 7,              /**<GPIO作为UART3 RX*/
    MCU_GPIO_FUNC_UART3_TX = 8,              /**<GPIO作为UART3 TX*/
    MCU_GPIO_FUNC_UART3_CTSN = 9,            /**<GPIO作为UART3 CTSN*/
    MCU_GPIO_FUNC_UART3_RTSN = 10,           /**<GPIO作为UART3 RTSN*/
    MCU_GPIO_FUNC_ISO_CLK = 11,              /**<GPIO作为ISO CLK*/
    MCU_GPIO_FUNC_ISO_DATA = 12,             /**<GPIO作为ISO数据*/
    MCU_GPIO_FUNC_SPI_DI = 13,               /**<GPIO作为SPI DI*/
    MCU_GPIO_FUNC_SPI_DO = 14,               /**<GPIO作为SPI DO*/
    MCU_GPIO_FUNC_SPI_CLK = 15,              /**<GPIO作为SPI CLK*/
    MCU_GPIO_FUNC_SPI_EN = 16,               /**<GPIO作为SPI EN*/
    MCU_GPIO_FUNC_SPI2_DI = 17,              /**<GPIO作为SPI2 DI*/
    MCU_GPIO_FUNC_SPI2_DO = 18,              /**<GPIO作为SPI2 DO*/
    MCU_GPIO_FUNC_SPI2_CLK = 19,             /**<GPIO作为SPI2 CLK*/
    MCU_GPIO_FUNC_SPI2_EN = 20,              /**<GPIO作为SPI2 EN*/
    MCU_GPIO_FUNC_I2C_SCL = 21,              /**<GPIO作为I2C SCL*/
    MCU_GPIO_FUNC_I2C_SDA = 22,              /**<GPIO作为I2C SDA*/
    MCU_GPIO_FUNC_I2C2_SCL = 23,             /**<GPIO作为I2C2 SCL*/
    MCU_GPIO_FUNC_I2C2_SDA = 24,             /**<GPIO作为I2C2 SDA*/
    MCU_GPIO_FUNC_USB_SOF = 25,              /**<GPIO作为USB SOF*/
    MCU_GPIO_FUNC_ADC = 26,                  /**<GPIO作为ADC（专用引脚）*/
    MCU_GPIO_FUNC_USB = 27,                  /**<GPIO作为USB*/
    MCU_GPIO_FUNC_PCM_DI = 28,               /**<GPIO作为PCM DI*/
    MCU_GPIO_FUNC_PCM_DO = 29,               /**<GPIO作为PCM DO*/
    MCU_GPIO_FUNC_PCM_FSC = 30,              /**<GPIO作为PCM FSC*/
    MCU_GPIO_FUNC_PCM_CLK = 31,              /**<GPIO作为PCM CLK*/
    MCU_GPIO_FUNC_PDM_DATA = 32,             /**<GPIO作为PDM数据*/
    MCU_GPIO_FUNC_PDM_CLK = 33,              /**<GPIO作为PDM CLK*/
    MCU_GPIO_FUNC_COEX_EXT_ACT = 34,         /**<GPIO作为COEX EXT ACT0*/
    MCU_GPIO_FUNC_COEX_SMART_ACT = 35,       /**<GPIO作为COEX SMART ACT*/
    MCU_GPIO_FUNC_COEX_SMART_PRI = 36,       /**<GPIO作为COEX SMART PRI*/
    MCU_GPIO_FUNC_PORT0_DCF = 37,            /**<GPIO作为PORT0 DCF*/
    MCU_GPIO_FUNC_PORT1_DCF = 38,            /**<GPIO作为PORT1 DCF*/
    MCU_GPIO_FUNC_PORT2_DCF = 39,            /**<GPIO作为PORT2 DCF*/
    MCU_GPIO_FUNC_PORT3_DCF = 40,            /**<GPIO作为PORT3 DCF*/
    MCU_GPIO_FUNC_PORT4_DCF = 41,            /**<GPIO作为PORT4 DCF*/
    MCU_GPIO_FUNC_CLOCK = 42,                /**<GPIO作为时钟*/
    MCU_GPIO_FUNC_PG = 43,                   /**<GPIO作为PG*/
    MCU_GPIO_FUNC_LCD = 44,                  /**<GPIO作为LCD*/
    MCU_GPIO_FUNC_LCD_SPI_DC = 45,           /**<GPIO作为LCD SPI DC*/
    MCU_GPIO_FUNC_LCD_SPI_DO = 46,           /**<GPIO作为LCD SPI DO*/
    MCU_GPIO_FUNC_LCD_SPI_CLK = 47,          /**<GPIO作为LCD SPI CLK*/
    MCU_GPIO_FUNC_LCD_SPI_EN = 48,           /**<GPIO作为LCD SPI EN*/
    MCU_GPIO_FUNC_TIM_PWM = 49,              /**<GPIO作为TIM PWM*/
    MCU_GPIO_FUNC_TIM2_PWM = 50,             /**<GPIO作为TIM2 PWM*/
    MCU_GPIO_FUNC_TIM_1SHOT = 51,            /**<GPIO作为TIM 1SHOT*/
    MCU_GPIO_FUNC_TIM2_1SHOT = 52,           /**<GPIO作为TIM2 1SHOT*/
    MCU_GPIO_FUNC_TIM3_PWM = 53,             /**<GPIO作为TIM3 PWM*/
    MCU_GPIO_FUNC_TIM4_PWM = 54,             /**<GPIO作为TIM4 PWM*/
    MCU_GPIO_FUNC_AGC_EXT = 55,              /**<GPIO作为AGC EXT*/
    MCU_GPIO_FUNC_CMAC_DIAG0 = 56,           /**<GPIO作为CMAC DIAG0*/
    MCU_GPIO_FUNC_CMAC_DIAG1 = 57,           /**<GPIO作为CMAC DIAG1*/
    MCU_GPIO_FUNC_CMAC_DIAG2 = 58,           /**<GPIO作为CMAC DIAG2*/
    MCU_GPIO_FUNC_CMAC_DIAGX = 59,           /**<GPIO作为CMAC DIAGX*/
    MCU_GPIO_FUNC_LAST,
} mcu_gpio_func;

#define MCU_GPIO_MODE_INPUT                 0x000    /**<GPIO作为输入*/
#define MCU_GPIO_MODE_INPUT_PULLUP          0x100    /**<GPIO作为上拉输入*/
#define MCU_GPIO_MODE_INPUT_PULLDOWN        0x200    /**<GPIO作为下拉输入*/
#define MCU_GPIO_MODE_OUTPUT                0x300    /**<GPIO作为输出*/
#define MCU_GPIO_MODE_OUTPUT_OPEN_DRAIN     0x700    /**<GPIO作为漏极开路输出*/

#define MCU_GPIO_PORT0_PIN_COUNT            32
#define MCU_GPIO_PORT0(pin)		((0 * 32) + (pin))
#define MCU_GPIO_PORT1(pin)		((1 * 32) + (pin))
#define MCU_DMA_CHAN_MAX                    8

#define MCU_PIN_GPADC_SEL0               MCU_GPIO_PORT1(9)
#define MCU_PIN_GPADC_SEL1               MCU_GPIO_PORT0(25)
#define MCU_PIN_GPADC_SEL2               MCU_GPIO_PORT0(8)
#define MCU_PIN_GPADC_SEL3               MCU_GPIO_PORT0(9)
#define MCU_PIN_GPADC_SEL16              MCU_GPIO_PORT1(13)
#define MCU_PIN_GPADC_SEL17              MCU_GPIO_PORT1(12)
#define MCU_PIN_GPADC_SEL18              MCU_GPIO_PORT1(18)
#define MCU_PIN_GPADC_SEL19              MCU_GPIO_PORT1(19)
#define MCU_PIN_GPADC_DIFF0_P0           MCU_GPIO_PORT1(9)
#define MCU_PIN_GPADC_DIFF0_P1           MCU_GPIO_PORT0(25)
#define MCU_PIN_GPADC_DIFF1_P0           MCU_GPIO_PORT0(8)
#define MCU_PIN_GPADC_DIFF1_P1           MCU_GPIO_PORT0(9)

#define MCU_PIN_SDADC0               MCU_GPIO_PORT1(9)
#define MCU_PIN_SDADC1               MCU_GPIO_PORT0(25)
#define MCU_PIN_SDADC2               MCU_GPIO_PORT0(8)
#define MCU_PIN_SDADC3               MCU_GPIO_PORT0(9)
#define MCU_PIN_SDADC4               MCU_GPIO_PORT1(14)
#define MCU_PIN_SDADC5               MCU_GPIO_PORT1(20)
#define MCU_PIN_SDADC6               MCU_GPIO_PORT1(21)
#define MCU_PIN_SDADC7               MCU_GPIO_PORT1(22)

void mcu_gpio_set_pin_function(int pin, int mode, mcu_gpio_func func);
void mcu_gpio_enter_sleep(void);
void mcu_gpio_exit_sleep(void);

#define MCU_MEM_QSPIF_M_END_REMAP_ADDRESS (0x800000)
#define MCU_MEM_QSPIF_M_START_ADDRESS   (0x16000000)
#define MCU_MEM_QSPIF_M_END_ADDRESS     (0x18000000)
#define MCU_MEM_SYSRAM_START_ADDRESS    (0x20000000)
#define MCU_MEM_SYSRAM_END_ADDRESS      (0x20080000)

#define MCU_OTPM_BASE 0x30080000UL
#define MCU_OTPM_SIZE 4096

/* 迄今为止，在DA14699上看到的最大组id为18*/
#define MCU_TRIMV_GROUP_ID_MAX          (18)

#ifdef __cplusplus
}
#endif

#endif /* __MCU_MCU_H_ */


