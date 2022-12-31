/**
  ******************************************************************************
  * @file    stm32f4x_hal_conf.h
  * @brief   HAL配置文件。
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy；版权所有（c）2019 STMicroelectronics</center></h2>
  *
  * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用STMicroelectronics的名称或其贡献者的名称来支持或推广源自本软件的产品。
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* 定义以防止递归包含-------------------------------------*/
#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* 导出的类型------------------------------------------------------------*/
/* 导出的常量--------------------------------------------------------*/

/* ##########################模块选择########################*/
/**
  * @brief 这是HAL驱动程序中使用的模块列表
  */
#define HAL_MODULE_ENABLED

/* #定义HAL_ADC_MODULE_ENABLED*/
/* #定义HAL_CRYP_MODULE_ENABLED*/
/* #定义HAL_CAN_MODULE_ENABLED*/
/* #定义HAL_CRC_MODULE_ENABLED*/
/* #定义HAL_CRYP_MODULE_ENABLED*/
/* #定义HAL_DAC_MODULE_ENABLED*/
/* #定义HAL_DCMI_MODULE_ENABLED*/
/* #定义HAL_DMA2D_MODULE_ENABLED*/
/* #定义HAL_ETH_MODULE_ENABLED*/
/* #定义HAL_NAND_MODULE_ENABLED*/
/* #定义HAL_NOR_MODULE_ENABLED*/
/* #定义HAL_PCCARD_MODULE_ENABLED*/
/* #定义HAL_SRAM_MODULE_ENABLED*/
/* #定义HAL_SDRAM_MODULE_ENABLED*/
/* #定义HAL_HASH_MODULE_ENABLED*/
/* #定义HAL_I2C_MODULE_ENABLED*/
/* #定义HAL_I2S_MODULE_ENABLED*/
/* #定义HAL_IWDG_MODULE_ENABLED*/
/* #定义HAL_LTDC_MODULE_ENABLED*/
/* #定义HAL_RNG_MODULE_ENABLED*/
/* #定义HAL_RTC_MODULE_ENABLED*/
/* #定义HAL_SAI_MODULE_ENABLED*/
/* #定义HAL_SD_MODULE_ENABLED*/
/* #定义HAL_MMC_MODULE_ENABLED*/
/* #定义HAL_SPI_MODULE_ENABLED*/
/* #定义HAL_TIM_MODULE_ENABLED*/
#define HAL_UART_MODULE_ENABLED
/* #定义HAL_USART_MODULE_ENABLED*/
/* #定义HAL_IRDA_MODULE_ENABLED*/
/* #定义HAL_SMARTCARD_MODULE_ENABLED*/
/* #定义HAL_WWDG_MODULE_ENABLED*/
#define HAL_PCD_MODULE_ENABLED
/* #定义HAL_HCD_MODULE_ENABLED*/
/* #定义HAL_DSI_MODULE_ENABLED*/
/* #定义HAL_QSPI_MODULE_ENABLED*/
/* #定义HAL_QSPI_MODULE_ENABLED*/
/* #定义HAL_CEC_MODULE_ENABLED*/
/* #定义HAL_FMPI2C_MODULE_ENABLED*/
/* #定义HAL_SPDIFRX_MODULE_ENABLED*/
/* #定义HAL_DFSDM_MODULE_ENABLED*/
/* #定义HAL_LPTIM_MODULE_ENABLED*/
/* #定义HAL_EXTI_MODULE_ENABLED*/
#define HAL_GPIO_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

/* ##########################HSE/HSI值调整######################*/
/**
  * @brief 调整应用中使用的外部高速振荡器（HSE）的值。RCC HAL模块使用该值计算系统频率（当HSE直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)12000000U) /*!< 外部振荡器的值（Hz）*/
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint32_t)100U)   /*!< HSE启动超时时间（毫秒）*/
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief 内部高速振荡器（HSI）值。RCC HAL模块使用该值计算系统频率（当HSI直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000U) /*!< 内部振荡器的值（Hz）*/
#endif /* HSI_VALUE */

/**
  * @brief 内部低速振荡器（LSI）值。
  */
#if !defined  (LSI_VALUE)
 #define LSI_VALUE  ((uint32_t)32000U)       /*!< LSI典型值（Hz）*/
#endif /* LSI_VALUE */                      /*!< 内部低速振荡器的值（Hz）实际值可能会根据电压和温度的变化而变化。*/
/**
  * @brief 外部低速振荡器（LSE）值。
  */
#if !defined  (LSE_VALUE)
 #define LSE_VALUE  ((uint32_t)32768U)    /*!< 外部低速振荡器的值（Hz）*/
#endif /* LSE_VALUE */

#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((uint32_t)5000U)   /*!< LSE启动超时（毫秒）*/
#endif /* LSE_STARTUP_TIMEOUT */

/**
  * @brief I2S外围设备的外部时钟源该值由I2S HAL模块用于计算I2S时钟源频率，该源直接通过I2S_CKIN焊盘插入。
  */
#if !defined  (EXTERNAL_CLOCK_VALUE)
  #define EXTERNAL_CLOCK_VALUE    ((uint32_t)12288000U) /*!< 外部音频频率值（Hz）*/
#endif /* EXTERNAL_CLOCK_VALUE */

/* 提示：为了避免每次需要使用不同的HSE时修改此文件，==可以在工具链编译器预处理器中定义HSE值。*/

/* ###########################系统配置######################*/
/**
  * @brief 这是HAL系统配置部分
  */
#define  VDD_VALUE		      ((uint32_t)3300U) /*!< VDD值（单位：mv）*/
#define  TICK_INT_PRIORITY            ((uint32_t)0U)   /*!< 滴答中断优先级*/
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              1U
#define  INSTRUCTION_CACHE_ENABLE     1U
#define  DATA_CACHE_ENABLE            1U

/* 手动复制-STM32Cube由于某种原因没有生成这些。*/
#define  USE_HAL_ADC_REGISTER_CALLBACKS     0U /* ADC寄存器回调已禁用*/
#define  USE_HAL_CEC_REGISTER_CALLBACKS     0U /* CEC寄存器回调已禁用*/
#define  USE_HAL_COMP_REGISTER_CALLBACKS    0U /* COMP寄存器回调已禁用*/
#define  USE_HAL_CRYP_REGISTER_CALLBACKS    0U /* CRYP寄存器回调已禁用*/
#define  USE_HAL_DAC_REGISTER_CALLBACKS     0U /* DAC寄存器回调已禁用*/
#define  USE_HAL_DCMI_REGISTER_CALLBACKS    0U /* DCMI寄存器回调已禁用*/
#define  USE_HAL_DFSDM_REGISTER_CALLBACKS   0U /* DFSDM寄存器回调已禁用*/
#define  USE_HAL_DMA2D_REGISTER_CALLBACKS   0U /* DMA2D寄存器回调已禁用*/
#define  USE_HAL_DSI_REGISTER_CALLBACKS     0U /* DSI寄存器回调已禁用*/
#define  USE_HAL_ETH_REGISTER_CALLBACKS     0U /* ETH寄存器回调已禁用*/
#define  USE_HAL_FDCAN_REGISTER_CALLBACKS   0U /* FDCAN寄存器回调已禁用*/
#define  USE_HAL_NAND_REGISTER_CALLBACKS    0U /* NAND寄存器回调已禁用*/
#define  USE_HAL_NOR_REGISTER_CALLBACKS     0U /* NOR寄存器回调已禁用*/
#define  USE_HAL_SDRAM_REGISTER_CALLBACKS   0U /* SDRAM寄存器回调已禁用*/
#define  USE_HAL_SRAM_REGISTER_CALLBACKS    0U /* SRAM寄存器回调已禁用*/
#define  USE_HAL_HASH_REGISTER_CALLBACKS    0U /* HASH寄存器回调已禁用*/
#define  USE_HAL_HCD_REGISTER_CALLBACKS     0U /* HCD寄存器回调已禁用*/
#define  USE_HAL_HRTIM_REGISTER_CALLBACKS   0U /* HRTEM寄存器回调已禁用*/
#define  USE_HAL_I2C_REGISTER_CALLBACKS     0U /* I2C寄存器回调已禁用*/
#define  USE_HAL_I2S_REGISTER_CALLBACKS     0U /* I2S寄存器回调已禁用*/
#define  USE_HAL_JPEG_REGISTER_CALLBACKS    0U /* JPEG寄存器回调已禁用*/
#define  USE_HAL_LPTIM_REGISTER_CALLBACKS   0U /* LPTIM寄存器回调已禁用*/
#define  USE_HAL_LTDC_REGISTER_CALLBACKS    0U /* LTDC寄存器回调已禁用*/
#define  USE_HAL_MDIOS_REGISTER_CALLBACKS   0U /* MDIO寄存器回调已禁用*/
#define  USE_HAL_OPAMP_REGISTER_CALLBACKS   0U /* MDIO寄存器回调已禁用*/
#define  USE_HAL_PCD_REGISTER_CALLBACKS     0U /* PCD寄存器回调已禁用*/
#define  USE_HAL_QSPI_REGISTER_CALLBACKS    0U /* QSPI寄存器回调已禁用*/
#define  USE_HAL_RNG_REGISTER_CALLBACKS     0U /* RNG寄存器回调已禁用*/
#define  USE_HAL_RTC_REGISTER_CALLBACKS     0U /* RTC寄存器回调已禁用*/
#define  USE_HAL_SAI_REGISTER_CALLBACKS     0U /* SAI寄存器回调已禁用*/
#define  USE_HAL_SPDIFRX_REGISTER_CALLBACKS 0U /* SPDIFRX寄存器回调已禁用*/
#define  USE_HAL_SMBUS_REGISTER_CALLBACKS   0U /* SMBUS寄存器回调已禁用*/
#define  USE_HAL_SPI_REGISTER_CALLBACKS     0U /* SPI寄存器回调已禁用*/
#define  USE_HAL_SWPMI_REGISTER_CALLBACKS   0U /* SWPMI寄存器回调已禁用*/
#define  USE_HAL_TIM_REGISTER_CALLBACKS     0U /* TIM寄存器回调已禁用*/
#define  USE_HAL_UART_REGISTER_CALLBACKS    0U /* UART寄存器回调已禁用*/
#define  USE_HAL_USART_REGISTER_CALLBACKS   0U /* USART寄存器回调已禁用*/
#define  USE_HAL_WWDG_REGISTER_CALLBACKS    0U /* WWDG寄存器回调已禁用*/

/* ##########################断言选择######################*/
/**
  * @brief 取消注释下面的行以扩展HAL驱动程序代码中的“assert_param”宏
  */
/* #定义USE_FULL_ASSERT 1U*/

/* ##################以太网外围设备配置#############*/

/* 第1节：以太网外围设备配置*/

/* MAC ADDRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0   2U
#define MAC_ADDR1   0U
#define MAC_ADDR2   0U
#define MAC_ADDR3   0U
#define MAC_ADDR4   0U
#define MAC_ADDR5   0U

/* 以太网驱动程序缓冲区大小和计数的定义*/
#define ETH_RX_BUF_SIZE                ETH_MAX_PACKET_SIZE /* 接收缓冲区大小*/
#define ETH_TX_BUF_SIZE                ETH_MAX_PACKET_SIZE /* 传输缓冲区大小*/
#define ETH_RXBUFNB                    ((uint32_t)4U)       /* 4个大小为ETH_Rx_BUF_size的Rx缓冲区*/
#define ETH_TXBUFNB                    ((uint32_t)4U)       /* 4个大小为ETH_Tx_BUF_size的Tx缓冲区*/

/* 第2节：PHY配置部分*/

/* DP83848_PHY_ADDRESS地址*/
#define DP83848_PHY_ADDRESS           0x01U
/* PHY重置延迟这些值基于1ms Systick中断*/
#define PHY_RESET_DELAY                 ((uint32_t)0x000000FFU)
/* PHY配置延迟*/
#define PHY_CONFIG_DELAY                ((uint32_t)0x00000FFFU)

#define PHY_READ_TO                     ((uint32_t)0x0000FFFFU)
#define PHY_WRITE_TO                    ((uint32_t)0x0000FFFFU)

/* 第3节：公共PHY寄存器*/

#define PHY_BCR                         ((uint16_t)0x0000U)    /*!< 收发器基本控制寄存器*/
#define PHY_BSR                         ((uint16_t)0x0001U)    /*!< 收发器基本状态寄存器*/

#define PHY_RESET                       ((uint16_t)0x8000U)  /*!< PHY重置*/
#define PHY_LOOPBACK                    ((uint16_t)0x4000U)  /*!< 选择环回模式*/
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100U)  /*!< 将全双工模式设置为100 Mb/s*/
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000U)  /*!< 将半双工模式设置为100 Mb/s*/
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100U)  /*!< 将全双工模式设置为10 Mb/s*/
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000U)  /*!< 将半双工模式设置为10 Mb/s*/
#define PHY_AUTONEGOTIATION             ((uint16_t)0x1000U)  /*!< 启用自动协商功能*/
#define PHY_RESTART_AUTONEGOTIATION     ((uint16_t)0x0200U)  /*!< 重新启动自动协商功能*/
#define PHY_POWERDOWN                   ((uint16_t)0x0800U)  /*!< 选择断电模式*/
#define PHY_ISOLATE                     ((uint16_t)0x0400U)  /*!< 将PHY与MII隔离*/

#define PHY_AUTONEGO_COMPLETE           ((uint16_t)0x0020U)  /*!< 自动协商过程已完成*/
#define PHY_LINKED_STATUS               ((uint16_t)0x0004U)  /*!< 已建立有效链接*/
#define PHY_JABBER_DETECTION            ((uint16_t)0x0002U)  /*!< 检测到Jabber状况*/

/* 第4节：扩展PHY寄存器*/
#define PHY_SR                          ((uint16_t)0x10U)    /*!< PHY状态寄存器偏移*/

#define PHY_SPEED_STATUS                ((uint16_t)0x0002U)  /*!< PHY速度掩码*/
#define PHY_DUPLEX_STATUS               ((uint16_t)0x0004U)  /*!< PHY双工掩码*/

/* ##################SPI外设配置######################*/

/* CRC功能：用于激活HAL SPI驱动程序内的CRC功能激活：驱动程序内存在CRC代码停用：从驱动程序中清除CRC代码
*/

#define USE_SPI_CRC                     0U

/* 包括------------------------------------------------------------------*/
/**
  * @brief 包括模块的头文件
  */

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32f4xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
  #include "stm32f4xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32f4xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32f4xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32f4xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32f4xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CAN_MODULE_ENABLED
  #include "stm32f4xx_hal_can.h"
#endif /* HAL_CAN_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
  #include "stm32f4xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_CRYP_MODULE_ENABLED
  #include "stm32f4xx_hal_cryp.h"
#endif /* HAL_CRYP_MODULE_ENABLED */

#ifdef HAL_DMA2D_MODULE_ENABLED
  #include "stm32f4xx_hal_dma2d.h"
#endif /* HAL_DMA2D_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
  #include "stm32f4xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_DCMI_MODULE_ENABLED
  #include "stm32f4xx_hal_dcmi.h"
#endif /* HAL_DCMI_MODULE_ENABLED */

#ifdef HAL_ETH_MODULE_ENABLED
  #include "stm32f4xx_hal_eth.h"
#endif /* HAL_ETH_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32f4xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_SRAM_MODULE_ENABLED
  #include "stm32f4xx_hal_sram.h"
#endif /* HAL_SRAM_MODULE_ENABLED */

#ifdef HAL_NOR_MODULE_ENABLED
  #include "stm32f4xx_hal_nor.h"
#endif /* HAL_NOR_MODULE_ENABLED */

#ifdef HAL_NAND_MODULE_ENABLED
  #include "stm32f4xx_hal_nand.h"
#endif /* HAL_NAND_MODULE_ENABLED */

#ifdef HAL_PCCARD_MODULE_ENABLED
  #include "stm32f4xx_hal_pccard.h"
#endif /* HAL_PCCARD_MODULE_ENABLED */

#ifdef HAL_SDRAM_MODULE_ENABLED
  #include "stm32f4xx_hal_sdram.h"
#endif /* HAL_SDRAM_MODULE_ENABLED */

#ifdef HAL_HASH_MODULE_ENABLED
 #include "stm32f4xx_hal_hash.h"
#endif /* HAL_HASH_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
 #include "stm32f4xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
 #include "stm32f4xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
 #include "stm32f4xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_LTDC_MODULE_ENABLED
 #include "stm32f4xx_hal_ltdc.h"
#endif /* HAL_LTDC_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
 #include "stm32f4xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RNG_MODULE_ENABLED
 #include "stm32f4xx_hal_rng.h"
#endif /* HAL_RNG_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
 #include "stm32f4xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SAI_MODULE_ENABLED
 #include "stm32f4xx_hal_sai.h"
#endif /* HAL_SAI_MODULE_ENABLED */

#ifdef HAL_SD_MODULE_ENABLED
 #include "stm32f4xx_hal_sd.h"
#endif /* HAL_SD_MODULE_ENABLED */

#ifdef HAL_MMC_MODULE_ENABLED
 #include "stm32f4xx_hal_mmc.h"
#endif /* HAL_MMC_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
 #include "stm32f4xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
 #include "stm32f4xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
 #include "stm32f4xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
 #include "stm32f4xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
 #include "stm32f4xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
 #include "stm32f4xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
 #include "stm32f4xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
 #include "stm32f4xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_HCD_MODULE_ENABLED
 #include "stm32f4xx_hal_hcd.h"
#endif /* HAL_HCD_MODULE_ENABLED */

#ifdef HAL_DSI_MODULE_ENABLED
 #include "stm32f4xx_hal_dsi.h"
#endif /* HAL_DSI_MODULE_ENABLED */

#ifdef HAL_QSPI_MODULE_ENABLED
 #include "stm32f4xx_hal_qspi.h"
#endif /* HAL_QSPI_MODULE_ENABLED */

#ifdef HAL_CEC_MODULE_ENABLED
 #include "stm32f4xx_hal_cec.h"
#endif /* HAL_CEC_MODULE_ENABLED */

#ifdef HAL_FMPI2C_MODULE_ENABLED
 #include "stm32f4xx_hal_fmpi2c.h"
#endif /* HAL_FMPI2C_MODULE_ENABLED */

#ifdef HAL_SPDIFRX_MODULE_ENABLED
 #include "stm32f4xx_hal_spdifrx.h"
#endif /* HAL_SPDIFRX_MODULE_ENABLED */

#ifdef HAL_DFSDM_MODULE_ENABLED
 #include "stm32f4xx_hal_dfsdm.h"
#endif /* HAL_DFSDM_MODULE_ENABLED */

#ifdef HAL_LPTIM_MODULE_ENABLED
 #include "stm32f4xx_hal_lptim.h"
#endif /* HAL_LPTIM_MODULE_ENABLED */

/* 导出的宏------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  assert_param宏用于函数的参数检查。
  * @param  expr: 如果expr为false，它将调用assert_failed函数，该函数报告源文件的名称和失败调用的源行号。如果expr为真，则不返回值。
  * @retval 没有一个
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* 导出的函数------------------------------------------------------*/
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4x_HAL_CONF_H钢*/


/************************（C）STMicroelectronics*****版权文件结束****/

