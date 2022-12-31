/**
  ******************************************************************************
  * @file    stm32l0xx_hal_conf.h
  * @author  MCD应用团队
  * @brief   HAL配置文件。
  ******************************************************************************
  * 版权所有（c）2016 STMicroelectronics International N.V.保留所有权利。
  *
  * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
  *
  * 1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经特别书面许可，不得使用STMicroelectronics的名称或本软件的其他贡献者的名称来支持或推广本软件衍生的产品。4.本软件，包括本软件的修改和/或衍生作品，必须仅在STMicroelectronics制造的微控制器或微处理器设备上执行。5.除非本许可证允许，否则重新分发和使用本软件是无效的，并将自动终止您在本许可证下的权利。
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"  AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT  SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* 定义以防止递归包含-------------------------------------*/
#ifndef __STM32L0xx_HAL_CONF_H
#define __STM32L0xx_HAL_CONF_H

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
// #定义HAL_ADC_MODULE_ENABLED
/* #定义HAL_COMP_MODULE_ENABLED*/ 
/* #定义HAL_CRC_MODULE_ENABLED*/  
/* #定义HAL_CRYP_MODULE_ENABLED*/ 
/* #定义HAL_DAC_MODULE_ENABLED*/   
#define HAL_DMA_MODULE_ENABLED
/* #定义HAL_FIREWALL_MULE_ENABLED*/
#define HAL_FLASH_MODULE_ENABLED 
#define HAL_GPIO_MODULE_ENABLED
/* #定义HAL_I2C_MODULE_ENABLED*/
/* #定义HAL_I2S_MODULE_ENABLED*/   
/* #定义HAL_IWDG_MODULE_ENABLED*/
/* #定义HAL_LCD_MODULE_ENABLED*/ 
/* #定义HAL_LPTIM_MODULE_ENABLED*/
#define HAL_PWR_MODULE_ENABLED  
#define HAL_RCC_MODULE_ENABLED 
//#定义HAL_RNG_MODULE_ENABLED
/* #定义HAL_RTC_MODULE_ENABLED*/
//#定义HAL_SPI_MODULE_ENABLED
/* #定义HAL_TIM_MODULE_ENABLED*/   
/* #定义HAL_TSC_MODULE_ENABLED*/
/* #定义HAL_UART_MODULE_ENABLED*/ 
/* #定义HAL_USART_MODULE_ENABLED*/ 
/* #定义HAL_IRDA_MODULE_ENABLED*/
/* #定义HAL_SMARTCARD_MODULE_ENABLED*/
/* #定义HAL_SMBUS_MODULE_ENABLED*/   
/* #定义HAL_WWDG_MODULE_ENABLED*/ 
//#定义HAL_PCD_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
/* #定义HAL_PCD_MODULE_ENABLED*/


/* ##########################振荡器值自适应####################*/
/**
  * @brief 调整应用中使用的外部高速振荡器（HSE）的值。RCC HAL模块使用该值计算系统频率（当HSE直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)8000000U) /*!< 外部振荡器的值（Hz）*/
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint32_t)100U)   /*!< HSE启动超时时间（毫秒）*/
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief 内部多速振荡器（MSI）默认值。此值是重置后的默认MSI范围值。
  */
#if !defined  (MSI_VALUE)
  #define MSI_VALUE    ((uint32_t)2097152U) /*!< 内部振荡器的值（Hz）*/
#endif /* MSI_VALUE */

/**
  * @brief 内部高速振荡器（HSI）值。RCC HAL模块使用该值计算系统频率（当HSI直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000U) /*!< 内部振荡器的值（Hz）*/
#endif /* HSI_VALUE */

/**
  * @brief USB（HSI48）值的内部高速振荡器。
  */
#if !defined  (HSI48_VALUE) 
#define HSI48_VALUE ((uint32_t)48000000U) /*!< USB内部高速振荡器的值（Hz）。实际值可以根据电压和温度的变化而变化。*/
#endif /* HSI48_VALUE */

/**
  * @brief 内部低速振荡器（LSI）值。
  */
#if !defined  (LSI_VALUE) 
 #define LSI_VALUE  ((uint32_t)37000U)       /*!< LSI典型值（Hz）*/
#endif /* LSI_VALUE */                      /*!< 内部低速振荡器的值（Hz）实际值可能会根据电压和温度的变化而变化。*/
/**
  * @brief 外部低速振荡器（LSE）值。该值由UART、RTC HAL模块用于计算系统频率
  */
#if !defined  (LSE_VALUE)
  #define LSE_VALUE    ((uint32_t)32768U) /*!< 外部振荡器的值（Hz）*/
#endif /* LSE_VALUE */

/**
  * @brief LSE启动值超时（毫秒）。
  */
#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((uint32_t)5000U)   /*!< LSE启动超时（毫秒）*/
#endif /* LSE_STARTUP_TIMEOUT */

   
/* 提示：为了避免每次需要使用不同的HSE时修改此文件，==可以在工具链编译器预处理器中定义HSE值。*/

/* ###########################系统配置######################*/
/**
  * @brief 这是HAL系统配置部分
  */     
#define  VDD_VALUE                    ((uint32_t)3300U) /*!< VDD值（单位：mv）*/ 
#define  TICK_INT_PRIORITY            ((uint32_t)0U)    /*!< 滴答中断优先级*/           
#define  USE_RTOS                     0U     
#define  PREFETCH_ENABLE              1U              
#define  PREREAD_ENABLE               1U
#define  BUFFER_CACHE_DISABLE         0U

/* ##########################断言选择######################*/
/**
  * @brief 取消注释下面的行以扩展HAL驱动程序代码中的“assert_param”宏
  */
/* #定义USE_FULL_ASSERT 1*/

/* ##################SPI外设配置######################*/

/* CRC功能：用于激活HAL SPI驱动程序内的CRC功能激活：驱动程序内存在CRC代码停用：从驱动程序中清除CRC代码
 */

#define USE_SPI_CRC                   1U

/* 包括------------------------------------------------------------------*/
/**
  * @brief 包括模块的头文件
  */

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32l0xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32l0xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32l0xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */
   
#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32l0xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32l0xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_COMP_MODULE_ENABLED
  #include "stm32l0xx_hal_comp.h"
#endif /* HAL_COMP_MODULE_ENABLED */
   
#ifdef HAL_CRC_MODULE_ENABLED
  #include "stm32l0xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_CRYP_MODULE_ENABLED
  #include "stm32l0xx_hal_cryp.h"
#endif /* HAL_CRYP_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
  #include "stm32l0xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_FIREWALL_MODULE_ENABLED
  #include "stm32l0xx_hal_firewall.h"
#endif /* HAL_FIREWALL_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32l0xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */
 
#ifdef HAL_I2C_MODULE_ENABLED
 #include "stm32l0xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
 #include "stm32l0xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
 #include "stm32l0xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_LCD_MODULE_ENABLED
 #include "stm32l0xx_hal_lcd.h"
#endif /* HAL_LCD_MODULE_ENABLED */

#ifdef HAL_LPTIM_MODULE_ENABLED
#include "stm32l0xx_hal_lptim.h"
#endif /* HAL_LPTIM_MODULE_ENABLED */
   
#ifdef HAL_PWR_MODULE_ENABLED
 #include "stm32l0xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RNG_MODULE_ENABLED
 #include "stm32l0xx_hal_rng.h"
#endif /* HAL_RNG_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
  #include "stm32l0xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
 #include "stm32l0xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
 #include "stm32l0xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_TSC_MODULE_ENABLED
  #include "stm32l0xx_hal_tsc.h"
#endif /* HAL_TSC_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
 #include "stm32l0xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
 #include "stm32l0xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
 #include "stm32l0xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
 #include "stm32l0xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_SMBUS_MODULE_ENABLED
 #include "stm32l0xx_hal_smbus.h"
#endif /* HAL_SMBUS_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
 #include "stm32l0xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
 #include "stm32l0xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

/* 导出的宏------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  assert_param宏用于函数的参数检查。
  * @param  expr 如果expr为false，它将调用assert_failed函数，该函数报告源文件的名称和失败调用的源行号。如果expr为真，则不返回值。
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

#endif /* __STM320xx_HAL_CONF_H钢*/
 

/************************（C）STMicroelectronics*****版权文件结束****/

