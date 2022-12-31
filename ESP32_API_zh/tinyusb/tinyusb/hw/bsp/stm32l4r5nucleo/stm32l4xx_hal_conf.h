/**
  ******************************************************************************
  * @file    stm32l4xx_hal_conf.h
  * @author  MCD应用团队
  * @brief   HAL配置模板文件。应将此文件复制到应用程序文件夹并重命名为stm32l4xx_hal_conf.h。
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy；版权所有（c）2017 STMicroelectronics。保留所有权利。</center></h2>
  *
  * 该软件组件由ST根据BSD 3条款许可证（“许可证”）许可；除非符合许可证，否则您不得使用此文件。您可以从以下网址获取许可证副本：opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* 定义以防止递归包含-------------------------------------*/
#ifndef __STM32L4xx_HAL_CONF_H
#define __STM32L4xx_HAL_CONF_H

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
/* #定义HAL_CAN_MODULE_ENABLED*/
/* #定义HAL_CAN_LEGACY_MODULE_ENABLED*/
/* #定义HAL_COMP_MODULE_ENABLED*/
#define HAL_CORTEX_MODULE_ENABLED
/* #定义HAL_CRC_MODULE_ENABLED*/
/* #定义HAL_CRYP_MODULE_ENABLED*/
/* #定义HAL_DAC_MODULE_ENABLED*/
/* #定义HAL_DFSDM_MODULE_ENABLED*/
#define HAL_DMA_MODULE_ENABLED
/* #定义HAL_FIREWALL_MULE_ENABLED*/
#define HAL_FLASH_MODULE_ENABLED
/* #定义HAL_NAND_MODULE_ENABLED*/
// #定义HAL_NOR_MODULE_ENABLED
// #定义HAL_SRAM_MODULE_ENABLED
/* #定义HAL_HCD_MODULE_ENABLED*/ 
#define HAL_GPIO_MODULE_ENABLED
//#定义HAL_I2C_MODULE_ENABLED
/* #定义HAL_IRDA_MODULE_ENABLED*/
/* #定义HAL_IWDG_MODULE_ENABLED*/
//#定义HAL_LCD_MODULE_ENABLED
/* #定义HAL_LPTIM_MODULE_ENABLED*/
/* #定义HAL_OPAMP_MODULE_ENABLED*/
//#定义HAL_PCD_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
/* #定义HAL_QSPI_MODULE_ENABLED*/
#define HAL_RCC_MODULE_ENABLED
/* #定义HAL_RNG_MODULE_ENABLED*/
/* #定义HAL_RTC_MODULE_ENABLED*/
//#定义HAL_SAI_MODULE_ENABLED
//#定义HAL_SD_MODULE_ENABLED
/* #定义HAL_SMARTCARD_MODULE_ENABLED*/
/* #定义HAL_SMBUS_MODULE_ENABLED*/
/* #定义HAL_SPI_MODULE_ENABLED*/
/* #定义HAL_SWPMI_MODULE_ENABLED*/
/* #定义HAL_TIM_MODULE_ENABLED*/
/* #定义HAL_TSC_MODULE_ENABLED*/
#define HAL_UART_MODULE_ENABLED
/* #定义HAL_USART_MODULE_ENABLED*/
/* #定义HAL_WWDG_MODULE_ENABLED*/


/* ##########################振荡器值自适应####################*/
/**
  * @brief 调整应用中使用的外部高速振荡器（HSE）的值。RCC HAL模块使用该值计算系统频率（当HSE直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    8000000U /*!< 外部振荡器的值（Hz）*/
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    100U   /*!< HSE启动超时时间（毫秒）*/
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief 内部多速振荡器（MSI）默认值。此值是重置后的默认MSI范围值。
  */
#if !defined  (MSI_VALUE)
  #define MSI_VALUE    4000000U /*!< 内部振荡器的值（Hz）*/
#endif /* MSI_VALUE */

/**
  * @brief 内部高速振荡器（HSI）值。RCC HAL模块使用该值计算系统频率（当HSI直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE    16000000U /*!< 内部振荡器的值（Hz）*/
#endif /* HSI_VALUE */

/**
  * @brief USB FS、SDMMC和RNG的内部高速振荡器（HSI48）值。该内部振荡器主要用于通过专用时钟恢复系统（CRS）电路向USB外围设备提供高精度时钟。当不使用CRS时，HSI48 RC振荡器在其默认频率上运行，该频率受制造工艺变化的影响。
  */
#if !defined  (HSI48_VALUE) 
 #define HSI48_VALUE   48000000U             /*!< USB FS/SDMMC/RNG内部高速振荡器的值（Hz）。实际价值可能因制造工艺的不同而不同。*/
#endif /* HSI48_VALUE */

/**
  * @brief 内部低速振荡器（LSI）值。
  */
#if !defined  (LSI_VALUE) 
 #define LSI_VALUE  32000U                 /*!< LSI典型值（Hz）*/
#endif /* LSI_VALUE */                     /*!< 内部低速振荡器的值（Hz）实际值可能会根据电压和温度的变化而变化。*/
/**
  * @brief 外部低速振荡器（LSE）值。该值由UART、RTC HAL模块用于计算系统频率
  */
#if !defined  (LSE_VALUE)
  #define LSE_VALUE    32768U /*!< 外部振荡器的值（Hz）*/
#endif /* LSE_VALUE */

#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    5000U  /*!< LSE启动超时（毫秒）*/
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief SAI1外围设备的外部时钟源此值由RCC HAL模块用于计算SAI1和SAI2时钟源频率。
  */
#if !defined  (EXTERNAL_SAI1_CLOCK_VALUE)
  #define EXTERNAL_SAI1_CLOCK_VALUE    48000U /*!< SAI1外部时钟源的值（Hz）*/
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

/**
  * @brief SAI2外围设备的外部时钟源此值由RCC HAL模块用于计算SAI1和SAI2时钟源频率。
  */
#if !defined  (EXTERNAL_SAI2_CLOCK_VALUE)
  #define EXTERNAL_SAI2_CLOCK_VALUE    48000U /*!< SAI2外部时钟源的值（Hz）*/
#endif /* EXTERNAL_SAI2_CLOCK_VALUE */

/* 提示：为了避免每次需要使用不同的HSE时修改此文件，==可以在工具链编译器预处理器中定义HSE值。*/

/* ###########################系统配置######################*/
/**
  * @brief 这是HAL系统配置部分
  */
#define  VDD_VALUE                    3300U /*!< VDD值（单位：mv）*/
#define  TICK_INT_PRIORITY            0U /*!< 滴答中断优先级*/
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              0U
#define  INSTRUCTION_CACHE_ENABLE     1U
#define  DATA_CACHE_ENABLE            1U

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

/* ##################SPI外设配置######################*/

/* CRC功能：用于激活HAL SPI驱动程序内的CRC功能激活：驱动程序内存在CRC代码停用：从驱动程序中清除CRC代码
 */

#define USE_SPI_CRC                   1U

/* 包括------------------------------------------------------------------*/
/**
  * @brief 包括模块的头文件
  */

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32l4xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32l4xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32l4xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_DFSDM_MODULE_ENABLED
  #include "stm32l4xx_hal_dfsdm.h"
#endif /* HAL_DFSDM_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32l4xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32l4xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CAN_MODULE_ENABLED
  #include "stm32l4xx_hal_can.h"
#endif /* HAL_CAN_MODULE_ENABLED */

#ifdef HAL_CAN_LEGACY_MODULE_ENABLED
  #include "Legacy/stm32l4xx_hal_can_legacy.h"
#endif /* HAL_CAN_LEGACY_MODULE_ENABLED */

#ifdef HAL_COMP_MODULE_ENABLED
  #include "stm32l4xx_hal_comp.h"
#endif /* HAL_COMP_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
  #include "stm32l4xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_CRYP_MODULE_ENABLED
  #include "stm32l4xx_hal_cryp.h"
#endif /* HAL_CRYP_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
  #include "stm32l4xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_FIREWALL_MODULE_ENABLED
  #include "stm32l4xx_hal_firewall.h"
#endif /* HAL_FIREWALL_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32l4xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_SRAM_MODULE_ENABLED
  #include "stm32l4xx_hal_sram.h"
#endif /* HAL_SRAM_MODULE_ENABLED */

#ifdef HAL_NOR_MODULE_ENABLED
  #include "stm32l4xx_hal_nor.h"
#endif /* HAL_NOR_MODULE_ENABLED */

#ifdef HAL_NAND_MODULE_ENABLED
  #include "stm32l4xx_hal_nand.h"
#endif /* HAL_NAND_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
 #include "stm32l4xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
 #include "stm32l4xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_LCD_MODULE_ENABLED
 #include "stm32l4xx_hal_lcd.h"
#endif /* HAL_LCD_MODULE_ENABLED */

#ifdef HAL_LPTIM_MODULE_ENABLED
#include "stm32l4xx_hal_lptim.h"
#endif /* HAL_LPTIM_MODULE_ENABLED */

#ifdef HAL_OPAMP_MODULE_ENABLED
#include "stm32l4xx_hal_opamp.h"
#endif /* HAL_OPAMP_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
 #include "stm32l4xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_QSPI_MODULE_ENABLED
 #include "stm32l4xx_hal_qspi.h"
#endif /* HAL_QSPI_MODULE_ENABLED */

#ifdef HAL_RNG_MODULE_ENABLED
 #include "stm32l4xx_hal_rng.h"
#endif /* HAL_RNG_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
 #include "stm32l4xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SAI_MODULE_ENABLED
 #include "stm32l4xx_hal_sai.h"
#endif /* HAL_SAI_MODULE_ENABLED */

#ifdef HAL_SD_MODULE_ENABLED
 #include "stm32l4xx_hal_sd.h"
#endif /* HAL_SD_MODULE_ENABLED */

#ifdef HAL_SMBUS_MODULE_ENABLED
 #include "stm32l4xx_hal_smbus.h"
#endif /* HAL_SMBUS_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
 #include "stm32l4xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_SWPMI_MODULE_ENABLED
 #include "stm32l4xx_hal_swpmi.h"
#endif /* HAL_SWPMI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
 #include "stm32l4xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_TSC_MODULE_ENABLED
 #include "stm32l4xx_hal_tsc.h"
#endif /* HAL_TSC_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
 #include "stm32l4xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
 #include "stm32l4xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
 #include "stm32l4xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
 #include "stm32l4xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
 #include "stm32l4xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
 #include "stm32l4xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_HCD_MODULE_ENABLED
 #include "stm32l4xx_hal_hcd.h"
#endif /* HAL_HCD_MODULE_ENABLED */

/* 导出的宏------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  assert_param宏用于函数的参数检查。
  * @param  expr: 如果expr为false，它将调用assert_failed函数，该函数报告源文件的名称和失败调用的源行号。如果expr为真，则不返回值。
  * @retval 没有一个
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* 导出的函数------------------------------------------------------*/
  void assert_failed(uint8_t *file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L4xx_HAL_CONF_H钢*/


/************************（C）STMicroelectronics*****版权文件结束****/

