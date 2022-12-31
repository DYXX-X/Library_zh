/**
  ******************************************************************************
  * @file    stm32f0xx_hal_conf.h
  * @author  MCD应用团队
  * @brief   HAL配置文件。
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy；版权所有（c）2016 STMicroelectronics。保留所有权利。</center></h2>
  *
  * 该软件组件由ST根据BSD 3条款许可证（“许可证”）许可；除非符合许可证，否则您不得使用此文件。您可以从以下网址获取许可证副本：opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* 定义以防止递归包含-------------------------------------*/
#ifndef __STM32F0xx_HAL_CONF_H
#define __STM32F0xx_HAL_CONF_H

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
/*#定义HAL_ADC_MODULE_ENABLED*/
/*#定义HAL_CAN_MODULE_ENABLED*/
/*#定义HAL_CEC_MODULE_ENABLED*/
/*#定义HAL_COMP_MODULE_ENABLED*/
#define HAL_CORTEX_MODULE_ENABLED
/*#定义HAL_CRC_MODULE_ENABLED*/
/*#定义HAL_DAC_MODULE_ENABLED*/
#define HAL_DMA_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
/*#定义HAL_EXTI_MODULE_ENABLED*/
/*#定义HAL_I2C_MODULE_ENABLED*/
/*#定义HAL_I2S_MODULE_ENABLED*/
/*#定义HAL_IRDA_MODULE_ENABLED*/
/*#定义HAL_IWDG_MODULE_ENABLED*/
#define HAL_PCD_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
/*#定义HAL_RTC_MODULE_ENABLED*/
/*#定义HAL_SMARTCARD_MODULE_ENABLED*/
/*#定义HAL_SMBUS_MODULE_ENABLED*/
/*#定义HAL_SPI_MODULE_ENABLED*/
/*#定义HAL_TIM_MODULE_ENABLED*/
/*#定义HAL_TSC_MODULE_ENABLED*/
#define HAL_UART_MODULE_ENABLED
/*#定义HAL_USART_MODULE_ENABLED*/
/*#定义HAL_WWDG_MODULE_ENABLED*/

/* #########################振荡器值适配#############*/
/**
  * @brief 调整应用中使用的外部高速振荡器（HSE）的值。RCC HAL模块使用该值计算系统频率（当HSE直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSE_VALUE) 
  #define HSE_VALUE            8000000U  /*!< 外部振荡器的值（Hz）*/
#endif /* HSE_VALUE */

/**
  * @brief 在以下行中，调整外部高速振荡器（HSE）启动超时值
  */
#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT  100U      /*!< HSE启动超时时间（毫秒）*/
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief 内部高速振荡器（HSI）值。RCC HAL模块使用该值计算系统频率（当HSI直接或通过PLL用作系统时钟源时）。
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE            8000000U  /*!< 内部振荡器的值（Hz）*/
#endif /* HSI_VALUE */

/**
  * @brief 在以下行中，调整内部高速振荡器（HSI）启动超时值
  */
#if !defined  (HSI_STARTUP_TIMEOUT) 
  #define HSI_STARTUP_TIMEOUT  5000U     /*!< HSI启动超时*/
#endif /* HSI_STARTUP_TIMEOUT */  

/**
  * @brief 用于ADC（HSI14）值的内部高速振荡器。
  */
#if !defined  (HSI14_VALUE) 
  #define HSI14_VALUE          14000000U /*!< ADC内部高速振荡器的值（Hz）。实际值可以根据电压和温度的变化而变化。*/
#endif /* HSI14_VALUE */

/**
  * @brief USB（HSI48）值的内部高速振荡器。
  */
#if !defined  (HSI48_VALUE) 
  #define HSI48_VALUE          48000000U /*!< USB内部高速振荡器的值（Hz）。实际值可以根据电压和温度的变化而变化。*/
#endif /* HSI48_VALUE */

/**
  * @brief 内部低速振荡器（LSI）值。
  */
#if !defined  (LSI_VALUE) 
  #define LSI_VALUE            32000U    
#endif /* LSI_VALUE */                      /*!< 内部低速振荡器的值（Hz）实际值可能会根据电压和温度的变化而变化。*/
/**
  * @brief 外部低速振荡器（LSE）值。
  */
#if !defined  (LSE_VALUE)
  #define LSE_VALUE            32768U    /*!< 外部低速振荡器的值（Hz）*/
#endif /* LSE_VALUE */     

/**
  * @brief LSE启动值超时（毫秒）。
  */
#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT  5000U     /*!< LSE启动超时（毫秒）*/
#endif /* LSE_STARTUP_TIMEOUT */


/* 提示：为了避免每次需要使用不同的HSE时修改此文件，==可以在工具链编译器预处理器中定义HSE值。*/

/* ###########################系统配置######################*/
/**
  * @brief 这是HAL系统配置部分
  */     
#define  VDD_VALUE                    3300U  /*!< VDD值（单位：mv）*/           
#define  TICK_INT_PRIORITY            ((uint32_t)(1U<<__NVIC_PRIO_BITS) - 1U) /*!< 滴答声中断优先级（默认最低）*/
                                                                              /*  警告：必须为HAL_Delay（）设置更高的优先级*/
                                                                              /*  和中断上下文下的HAL_GetTick（）用法*/
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              1U
#define  INSTRUCTION_CACHE_ENABLE     0U
#define  DATA_CACHE_ENABLE            0U
#define  USE_SPI_CRC                  1U

#define  USE_HAL_ADC_REGISTER_CALLBACKS         0U /* ADC寄存器回调已禁用*/
#define  USE_HAL_CAN_REGISTER_CALLBACKS         0U /* CAN寄存器回调已禁用*/
#define  USE_HAL_COMP_REGISTER_CALLBACKS        0U /* COMP寄存器回调已禁用*/
#define  USE_HAL_CEC_REGISTER_CALLBACKS         0U /* CEC寄存器回调已禁用*/
#define  USE_HAL_DAC_REGISTER_CALLBACKS         0U /* DAC寄存器回调已禁用*/
#define  USE_HAL_I2C_REGISTER_CALLBACKS         0U /* I2C寄存器回调已禁用*/
#define  USE_HAL_SMBUS_REGISTER_CALLBACKS       0U /* SMBUS寄存器回调已禁用*/
#define  USE_HAL_UART_REGISTER_CALLBACKS        0U /* UART寄存器回调已禁用*/
#define  USE_HAL_USART_REGISTER_CALLBACKS       0U /* USART寄存器回调已禁用*/
#define  USE_HAL_IRDA_REGISTER_CALLBACKS        0U /* IRDA寄存器回调已禁用*/
#define  USE_HAL_SMARTCARD_REGISTER_CALLBACKS   0U /* SMARTCARD寄存器回调已禁用*/
#define  USE_HAL_WWDG_REGISTER_CALLBACKS        0U /* WWDG寄存器回调已禁用*/
#define  USE_HAL_RTC_REGISTER_CALLBACKS         0U /* RTC寄存器回调已禁用*/
#define  USE_HAL_SPI_REGISTER_CALLBACKS         0U /* SPI寄存器回调已禁用*/
#define  USE_HAL_I2S_REGISTER_CALLBACKS         0U /* I2S寄存器回调已禁用*/
#define  USE_HAL_TIM_REGISTER_CALLBACKS         0U /* TIM寄存器回调已禁用*/
#define  USE_HAL_TSC_REGISTER_CALLBACKS         0U /* TSC寄存器回调已禁用*/
#define  USE_HAL_PCD_REGISTER_CALLBACKS         0U /* PCD寄存器回调已禁用*/

/* ##########################断言选择######################*/
/**
  * @brief 取消注释下面的行以扩展HAL驱动程序代码中的“assert_param”宏
  */
 #define USE_FULL_ASSERT   1 

/* 包括------------------------------------------------------------------*/
/**
  * @brief 包括模块的头文件
  */

#ifdef HAL_RCC_MODULE_ENABLED
 #include "stm32f0xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
 #include "stm32f0xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
  #include "stm32f0xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32f0xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
 #include "stm32f0xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
 #include "stm32f0xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CAN_MODULE_ENABLED
 #include "stm32f0xx_hal_can.h"
#endif /* HAL_CAN_MODULE_ENABLED */

#ifdef HAL_CEC_MODULE_ENABLED
 #include "stm32f0xx_hal_cec.h"
#endif /* HAL_CEC_MODULE_ENABLED */

#ifdef HAL_COMP_MODULE_ENABLED
 #include "stm32f0xx_hal_comp.h"
#endif /* HAL_COMP_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
 #include "stm32f0xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
 #include "stm32f0xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
 #include "stm32f0xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
 #include "stm32f0xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
 #include "stm32f0xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
 #include "stm32f0xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
 #include "stm32f0xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
 #include "stm32f0xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
 #include "stm32f0xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
 #include "stm32f0xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
 #include "stm32f0xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_SMBUS_MODULE_ENABLED
 #include "stm32f0xx_hal_smbus.h"
#endif /* HAL_SMBUS_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
 #include "stm32f0xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
 #include "stm32f0xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_TSC_MODULE_ENABLED
 #include "stm32f0xx_hal_tsc.h"
#endif /* HAL_TSC_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
 #include "stm32f0xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
 #include "stm32f0xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
 #include "stm32f0xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

/* 导出的宏------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  assert_param宏用于函数的参数检查。
  * @param  expr 如果expr为false，它将调用assert_failed函数，该函数报告源文件的名称和失败调用的源行号。如果expr为真，则不返回值。
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

#endif /* __STM32F00xx_HAL_CONF_H钢*/


/************************（C）STMicroelectronics*****版权文件结束****/


