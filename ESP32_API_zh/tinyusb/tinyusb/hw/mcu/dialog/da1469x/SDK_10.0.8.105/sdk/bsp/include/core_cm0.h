/**************************************************************************//**
 * @file     core_cm0.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File
 * @version  V5.0.6
 * @date     13. March 2019
 ******************************************************************************/
/*
 * 版权所有（c）2009-2019 Arm Limited。保留所有权利。
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 根据Apache许可证2.0版（许可证）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按原样分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
 /* 版权所有（c）2019 Dialog Semiconductor修改*/

#if   defined ( __ICCARM__ )
  #pragma system_include         /* 将文件视为MISRA检查的系统包含文件*/
#elif defined (__clang__)
  #pragma clang system_header   /* 将文件视为系统包含文件*/
#endif

#ifndef __CORE_CM0_H_GENERIC
#define __CORE_CM0_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
  \页面CMSIS_MISRA_Exceptions MISRA-C:2004 Compliance Exceptions CMSIS违反了以下MISRA-C/2004规则：

   \li必需规则8.5，头文件中的对象/函数定义<br>头文件中的函数定义用于允许“内联”。

   \li必需的规则18.4，联合类型的声明或联合类型的对象：“｛…｝”<br>联合用于有效表示核心寄存器。

   \li咨询规则19.7，功能类宏定义<br>类似函数的宏用于实现更高效的代码。
 */


/*******************************************************************************
 *                 CMSIS定义
 ******************************************************************************/
/**
  \内部组Cortex_M0@{
 */

#include "cmsis_version.h"
 
/*  CMSIS CM0定义*/
#define __CM0_CMSIS_VERSION_MAIN  (__CM_CMSIS_VERSION_MAIN)              /*!< \已弃用[31:16]CMSIS HAL主版本*/
#define __CM0_CMSIS_VERSION_SUB   (__CM_CMSIS_VERSION_SUB)               /*!< \已弃用[15:0]CMSIS HAL子版本*/
#define __CM0_CMSIS_VERSION       ((__CM0_CMSIS_VERSION_MAIN << 16U) | \
                                    __CM0_CMSIS_VERSION_SUB           )  /*!< \已弃用的CMSIS HAL版本号*/

#define __CORTEX_M                (0U)                                   /*!< Cortex-M内核*/

/** __FPU_USED指示是否使用FPU。此内核根本不支持FPU
*/
#define __FPU_USED       0U

#if defined ( __CC_ARM )
  #if defined __TARGET_FPU_VFP
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if defined __ARM_FP
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __TI_ARM__ )
  #if defined __TI_VFP_SUPPORT__
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __TASKING__ )
  #if defined __FPU_VFP__
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __CSMC__ )
  #if ( __CSMC__ & 0x400U)
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#endif

#include "cmsis_compiler.h"               /* CMSIS编译器特定的定义*/


#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM0_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CM0_H_DEPENDANT
#define __CORE_CM0_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* 检查设备定义和使用默认值*/
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __CM0_REV
    #define __CM0_REV               0x0000U
    #warning "__CM0_REV not defined in device header file; using default!"
  #endif

  #ifndef __NVIC_PRIO_BITS
    #define __NVIC_PRIO_BITS          2U
    #warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
  #endif

  #ifndef __Vendor_SysTickConfig
    #define __Vendor_SysTickConfig    0U
    #warning "__Vendor_SysTickConfig not defined in device header file; using default!"
  #endif
#endif

/* IO定义（对外围寄存器的访问限制）*/
/**
    \defgroup CMSIS_glob_defs CMSIS全局定义

    <strong>IO类型限定符</strong>用于指定对外围变量的访问。\li用于自动生成外围寄存器调试信息。
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< 定义“只读”权限*/
#else
  #define   __I     volatile const       /*!< 定义“只读”权限*/
#endif
#define     __O     volatile             /*!< 定义“仅写”权限*/
#define     __IO    volatile             /*!< 定义“读/写”权限*/

/* 结构成员应使用以下定义*/
#define     __IM     volatile const      /*! 定义“只读”结构成员权限*/
#define     __OM     volatile            /*! 定义“仅写”结构成员权限*/
#define     __IOM    volatile            /*! 定义“读/写”结构成员权限*/

/*@}Cortex_M0组结束*/



/*******************************************************************************
 *                 寄存器抽象核心寄存器包含：
  -核心寄存器
  -核心NVIC寄存器
  -核心SCB寄存器
  -核心SysTick寄存器
 ******************************************************************************/
/**
  \defgroup CMSIS_core_register定义和类型定义\简要类型定义和基于Cortex-M处理器的设备定义。
*/

/**
  \inggroup CMSIS_core_register\defgroup CMSIS_core状态和控制寄存器\简要核心寄存器类型定义@{
 */

/**
  \简短的Union类型以访问应用程序状态寄存器（APSR）。
 */
typedef union
{
  struct
  {
    uint32_t _reserved0:28;              /*!< 位：0..27保留*/
    uint32_t V:1;                        /*!< bit:28溢出条件代码标志*/
    uint32_t C:1;                        /*!< bit:29进位条件代码标志*/
    uint32_t Z:1;                        /*!< bit:30零条件代码标志*/
    uint32_t N:1;                        /*!< bit:31负条件代码标志*/
  } b;                                   /*!< 用于位访问的结构*/
  uint32_t w;                            /*!< 用于字访问的类型*/
} APSR_Type;

/* APSR寄存器定义*/
#define APSR_N_Pos                         31U                                            /*!< APSR:N位置*/
#define APSR_N_Msk                         (1UL << APSR_N_Pos)                            /*!< APSR:N掩码*/

#define APSR_Z_Pos                         30U                                            /*!< APSR:Z位置*/
#define APSR_Z_Msk                         (1UL << APSR_Z_Pos)                            /*!< APSR:Z掩码*/

#define APSR_C_Pos                         29U                                            /*!< APSR:C位置*/
#define APSR_C_Msk                         (1UL << APSR_C_Pos)                            /*!< APSR:C掩码*/

#define APSR_V_Pos                         28U                                            /*!< APSR:V位置*/
#define APSR_V_Msk                         (1UL << APSR_V_Pos)                            /*!< APSR:V掩码*/


/**
  \简短的Union类型以访问中断程序状态寄存器（IPSR）。
 */
typedef union
{
  struct
  {
    uint32_t ISR:9;                      /*!< 位：0..8异常编号*/
    uint32_t _reserved0:23;              /*!< 位：9..31保留*/
  } b;                                   /*!< 用于位访问的结构*/
  uint32_t w;                            /*!< 用于字访问的类型*/
} IPSR_Type;

/* IPSR寄存器定义*/
#define IPSR_ISR_Pos                        0U                                            /*!< IPSR：ISR位置*/
#define IPSR_ISR_Msk                       (0x1FFUL /*<<IPSR_ISR_Pos*/)                  /*!< IPSR：ISR掩码*/


/**
  \简短的Union类型以访问特殊用途程序状态寄存器（xPSR）。
 */
typedef union
{
  struct
  {
    uint32_t ISR:9;                      /*!< 位：0..8异常编号*/
    uint32_t _reserved0:15;              /*!< 位：9..23保留*/
    uint32_t T:1;                        /*!< bit:24 Thumb位（读取0）*/
    uint32_t _reserved1:3;               /*!< 位：25..27保留*/
    uint32_t V:1;                        /*!< bit:28溢出条件代码标志*/
    uint32_t C:1;                        /*!< bit:29进位条件代码标志*/
    uint32_t Z:1;                        /*!< bit:30零条件代码标志*/
    uint32_t N:1;                        /*!< bit:31负条件代码标志*/
  } b;                                   /*!< 用于位访问的结构*/
  uint32_t w;                            /*!< 用于字访问的类型*/
} xPSR_Type;

/* xPSR寄存器定义*/
#define xPSR_N_Pos                         31U                                            /*!< xPSR:N位置*/
#define xPSR_N_Msk                         (1UL << xPSR_N_Pos)                            /*!< xPSR:N掩码*/

#define xPSR_Z_Pos                         30U                                            /*!< xPSR:Z位置*/
#define xPSR_Z_Msk                         (1UL << xPSR_Z_Pos)                            /*!< xPSR:Z掩码*/

#define xPSR_C_Pos                         29U                                            /*!< xPSR:C位置*/
#define xPSR_C_Msk                         (1UL << xPSR_C_Pos)                            /*!< xPSR:C掩码*/

#define xPSR_V_Pos                         28U                                            /*!< xPSR:V位置*/
#define xPSR_V_Msk                         (1UL << xPSR_V_Pos)                            /*!< xPSR:V掩码*/

#define xPSR_T_Pos                         24U                                            /*!< xPSR:T位置*/
#define xPSR_T_Msk                         (1UL << xPSR_T_Pos)                            /*!< xPSR:T掩码*/

#define xPSR_ISR_Pos                        0U                                            /*!< xPSR:ISR位置*/
#define xPSR_ISR_Msk                       (0x1FFUL /*<<xSR_ISR_Pos*/)                  /*!< xPSR:ISR掩码*/


/**
  \简短的Union类型以访问控制寄存器（Control）。
 */
typedef union
{
  struct
  {
    uint32_t _reserved0:1;               /*!< 位：0保留*/
    uint32_t SPSEL:1;                    /*!< bit:1要使用的堆栈*/
    uint32_t _reserved1:30;              /*!< 位：2..31保留*/
  } b;                                   /*!< 用于位访问的结构*/
  uint32_t w;                            /*!< 用于字访问的类型*/
} CONTROL_Type;

/* 控制寄存器定义*/
#define CONTROL_SPSEL_Pos                   1U                                            /*!< 控制：SPSEL位置*/
#define CONTROL_SPSEL_Msk                  (1UL << CONTROL_SPSEL_Pos)                     /*!< 控制：SPSEL掩码*/

/*@}CMSIS_CORE组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_NVIC嵌套矢量中断控制器（NVIC）\NVIC寄存器的简要类型定义@{
 */

/**
  \访问嵌套矢量中断控制器（NVIC）的简短结构类型。
 */
typedef struct
{
  __IOM uint32_t ISER[1U];               /*!< 偏移：0x000（R/W）中断设置启用寄存器*/
        uint32_t RESERVED0[31U];
  __IOM uint32_t ICER[1U];               /*!< 偏移量：0x080（R/W）中断清除启用寄存器*/
        uint32_t RESERVED1[31U];
  __IOM uint32_t ISPR[1U];               /*!< 偏移量：0x100（R/W）中断设置挂起寄存器*/
        uint32_t RESERVED2[31U];
  __IOM uint32_t ICPR[1U];               /*!< 偏移量：0x180（R/W）中断清除挂起寄存器*/
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  __IOM uint32_t IP[8U];                 /*!< 偏移量：0x300（R/W）中断优先级寄存器*/
}  NVIC_Type;

/*@}CMSIS_NVIC组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_SCB系统控制块（SCB）\系统控制块寄存器的简要类型定义@{
 */

/**
  \访问系统控制块（SCB）的简要结构类型。
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< 偏移量：0x000（R/）CPUID基寄存器*/
  __IOM uint32_t ICSR;                   /*!< 偏移量：0x004（R/W）中断控制和状态寄存器*/
        uint32_t RESERVED0;
  __IOM uint32_t AIRCR;                  /*!< 偏移量：0x00C（R/W）应用程序中断和复位控制寄存器*/
  __IOM uint32_t SCR;                    /*!< 偏移量：0x010（R/W）系统控制寄存器*/
  __IOM uint32_t CCR;                    /*!< 偏移量：0x014（R/W）配置控制寄存器*/
        uint32_t RESERVED1;
  __IOM uint32_t SHP[2U];                /*!< 偏移量：0x01C（R/W）系统处理程序优先级寄存器。[0]已保留*/
  __IOM uint32_t SHCSR;                  /*!< 偏移量：0x024（R/W）系统处理程序控制和状态寄存器*/
} SCB_Type;

/* SCB CPUID寄存器定义*/
#define SCB_CPUID_IMPLEMENTER_Pos          24U                                            /*!< SCB CPUID：机具位置*/
#define SCB_CPUID_IMPLEMENTER_Msk          (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)          /*!< SCB CPUID：IMPLEMENTER掩码*/

#define SCB_CPUID_VARIANT_Pos              20U                                            /*!< SCB CPUID：变量位置*/
#define SCB_CPUID_VARIANT_Msk              (0xFUL << SCB_CPUID_VARIANT_Pos)               /*!< SCB CPUID：VARIANT掩码*/

#define SCB_CPUID_ARCHITECTURE_Pos         16U                                            /*!< SCB CPUID：架构位置*/
#define SCB_CPUID_ARCHITECTURE_Msk         (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)          /*!< SCB CPUID：架构掩码*/

#define SCB_CPUID_PARTNO_Pos                4U                                            /*!< SCB CPUID：PARTNO位置*/
#define SCB_CPUID_PARTNO_Msk               (0xFFFUL << SCB_CPUID_PARTNO_Pos)              /*!< SCB CPUID：PARTNO掩码*/

#define SCB_CPUID_REVISION_Pos              0U                                            /*!< SCB CPUID：修订位置*/
#define SCB_CPUID_REVISION_Msk             (0xFUL /*<<SCB_CPUID_REVISION_Pos*/)          /*!< SCB CPUID：修订掩码*/

/* SCB中断控制状态寄存器定义*/
#define SCB_ICSR_NMIPENDSET_Pos            31U                                            /*!< SCB ICSR：NMIPENDSET位置*/
#define SCB_ICSR_NMIPENDSET_Msk            (1UL << SCB_ICSR_NMIPENDSET_Pos)               /*!< SCB ICSR：NMIPENDSET掩码*/

#define SCB_ICSR_PENDSVSET_Pos             28U                                            /*!< SCB ICSR:PENDSVSET位置*/
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR:PENDSVSET掩码*/

#define SCB_ICSR_PENDSVCLR_Pos             27U                                            /*!< SCB ICSR:PENDSVCLR位置*/
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)                /*!< SCB ICSR:PENDSVCLR掩码*/

#define SCB_ICSR_PENDSTSET_Pos             26U                                            /*!< SCB ICSR：待定设置位置*/
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR:PENDSTSET掩码*/

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            /*!< SCB ICSR：待定CLR位置*/
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR:PENDSTCLR掩码*/

#define SCB_ICSR_ISRPREEMPT_Pos            23U                                            /*!< SCB ICSR:ISRPREEMPT位置*/
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)               /*!< SCB ICSR:ISRPREEMPT掩码*/

#define SCB_ICSR_ISRPENDING_Pos            22U                                            /*!< SCB ICSR：ISRPENDING位置*/
#define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)               /*!< SCB ICSR：ISRPENDING掩码*/

#define SCB_ICSR_VECTPENDING_Pos           12U                                            /*!< SCB ICSR：矢量结束位置*/
#define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)          /*!< SCB ICSR：VECTPENDING掩码*/

#define SCB_ICSR_VECTACTIVE_Pos             0U                                            /*!< SCB ICSR：矢量位置*/
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL /*<<SCB_ICSR_VETACTIVE_Pos*/)       /*!< SCB ICSR：矢量掩模*/

/* SCB应用程序中断和复位控制寄存器定义*/
#define SCB_AIRCR_VECTKEY_Pos              16U                                            /*!< SCB AIRCR:VECTKEY位置*/
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR:VECTKEY面罩*/

#define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                            /*!< SCB AIRCR:VETKEYSTAT位置*/
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR:VECTKEYSTAT面罩*/

#define SCB_AIRCR_ENDIANESS_Pos            15U                                            /*!< SCB AIRCR:末端位置*/
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)               /*!< SCB AIRCR:ENDIANESS面罩*/

#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            /*!< SCB AIRCR:SYSRESETREQ位置*/
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR:SYSRESETREQ掩码*/

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                            /*!< SCB AIRCR:VETCLRACTIVE位置*/
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)           /*!< SCB AIRCR:VETCLRACTIVE面罩*/

/* SCB系统控制寄存器定义*/
#define SCB_SCR_SEVONPEND_Pos               4U                                            /*!< SCB SCR：SEVONPEND位置*/
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 /*!< SCB SCR：SEVONPEND掩码*/

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            /*!< SCB SCR：睡眠深度位置*/
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR：睡眠深度面罩*/

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            /*!< SCB SCR：SLEEPONEXIT位置*/
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               /*!< SCB SCR：SLEPONEXIT掩码*/

/* SCB配置控制寄存器定义*/
#define SCB_CCR_STKALIGN_Pos                9U                                            /*!< SCB CCR:STKALIGN位置*/
#define SCB_CCR_STKALIGN_Msk               (1UL << SCB_CCR_STKALIGN_Pos)                  /*!< SCB CCR:STKALIGN面罩*/

#define SCB_CCR_UNALIGN_TRP_Pos             3U                                            /*!< SCB CCR:UNALIGN_TRP位置*/
#define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)               /*!< SCB CCR:UNALIGN_TRP掩码*/

/* SCB系统处理程序控制和状态寄存器定义*/
#define SCB_SHCSR_SVCALLPENDED_Pos         15U                                            /*!< SCB SHCSR：SVCALLPENDED位置*/
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)            /*!< SCB SHCSR：SVCALLPENDED掩码*/

/*@}CMSIS_SCB组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_SysTick System Tick Timer（SysTick）\系统计时器寄存器的简要类型定义@{
 */

/**
  \访问系统计时器（SysTick）的简要结构类型。
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< 偏移：0x000（R/W）SysTick控制和状态寄存器*/
  __IOM uint32_t LOAD;                   /*!< 偏移：0x004（R/W）SysTick重新加载值寄存器*/
  __IOM uint32_t VAL;                    /*!< 偏移：0x008（R/W）SysTick当前值寄存器*/
  __IM  uint32_t CALIB;                  /*!< 偏移：0x00C（R/）SysTick校准寄存器*/
} SysTick_Type;

/* SysTick控制/状态寄存器定义*/
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL：COUNTFLAG位置*/
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL：COUNTFLAG掩码*/

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL：CLKSOURCE位置*/
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL:CLKSOURCE掩码*/

#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL:TICKINT位置*/
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL:TICKINT掩码*/

#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL：启用位置*/
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<<系统Tick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL:ENABLE掩码*/

/* SysTick重新加载寄存器定义*/
#define SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD:RELOAD位置*/
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<<系统Tick_LOAD_LOAD_Pos*/)    /*!< SysTick LOAD:RELOAD掩码*/

/* SysTick当前寄存器定义*/
#define SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL:当前位置*/
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<<系统Tick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL:当前掩码*/

/* SysTick校准寄存器定义*/
#define SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB:NOREF位置*/
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB:NOREF掩码*/

#define SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB:倾斜位置*/
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB:SKEW掩码*/

#define SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB:TEMS位置*/
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<<系统Tick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB:TEMS掩码*/

/*@}CMSIS_SysTick组结束*/


/**
  \ingroup CMSIS_core_register\defgroup CMSIS_CoreDebug核心调试寄存器（CoreDebug）\brief Cortex-M0核心调试寄存器，（DCB寄存器、SHCSR和DFSR）只能通过DAP访问，不能通过处理器访问。因此，Cortex-M0头文件不包含这些文件@{
 */
/*@}CMSIS_CoreDebug组结束*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS-core_bitfield核心寄存器位字段宏\用于位字段定义（xxx_Pos，xxx_Msk）的简短宏@{
 */

/**
  \简短掩码和移位位字段值，以便在寄存器位范围中使用。\param[in]field寄存器位字段的名称。\param[in]value位字段的值。此参数被解释为uint32_t类型。\返回掩码和移位值。
*/
#define _VAL2FLD(field, value)    (((uint32_t)(value) << field ## _Pos) & field ## _Msk)

/**
  \简短掩码并移位寄存器值以提取位字段值。\param[in]field寄存器位字段的名称。\param[in]value寄存器的值。此参数被解释为uint32_t类型。\返回掩码和移位位字段值。
*/
#define _FLD2VAL(field, value)    (((uint32_t)(value) & field ## _Msk) >> field ## _Pos)

/*@}组末尾CMSIS_core_bitfield*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS-core_base核心定义\基址、联合和结构的简要定义@{
 */

/* 核心硬件的内存映射*/
#define SCS_BASE            (0xE000E000UL)                            /*!< 系统控制空间基地址*/
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick基地址*/
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC基址*/
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< 系统控制块基址*/

#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB配置结构*/
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick配置结构*/
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC配置结构*/


/*@} */



/*******************************************************************************
 *                硬件抽象层核心功能接口包含：
  -核心NVIC功能
  -核心SysTick功能
  -核心寄存器访问功能
 ******************************************************************************/
/**
  \defgroup CMSIS_Core_FunctionInterface函数和指令参考
*/



/* ##########################NVIC功能#############*/
/**
  \ingroup CMSIS_Core_FunctionInterface\defgroup CMSIS-Core_NVICFunctions NVIC Functions\brief通过NVIC管理中断和异常的函数@{
 */

#ifdef CMSIS_NVIC_VIRTUAL
  #ifndef CMSIS_NVIC_VIRTUAL_HEADER_FILE
    #define CMSIS_NVIC_VIRTUAL_HEADER_FILE "cmsis_nvic_virtual.h"
  #endif
  #include CMSIS_NVIC_VIRTUAL_HEADER_FILE
#else
  #define NVIC_SetPriorityGrouping    __NVIC_SetPriorityGrouping
  #define NVIC_GetPriorityGrouping    __NVIC_GetPriorityGrouping
  #define NVIC_EnableIRQ              __NVIC_EnableIRQ
  #define NVIC_GetEnableIRQ           __NVIC_GetEnableIRQ
  #define NVIC_DisableIRQ             __NVIC_DisableIRQ
  #define NVIC_GetPendingIRQ          __NVIC_GetPendingIRQ
  #define NVIC_SetPendingIRQ          __NVIC_SetPendingIRQ
  #define NVIC_ClearPendingIRQ        __NVIC_ClearPendingIRQ
/*#定义NVIC_GetActive __NVIC_Get-Active不适用于Cortex-M0*/
  #define NVIC_SetPriority            __NVIC_SetPriority
  #define NVIC_GetPriority            __NVIC_GetPriority
  #define NVIC_SystemReset            __NVIC_SystemReset
#endif /* CMSIS_NVIC_VIRTUAL */

#ifdef CMSIS_VECTAB_VIRTUAL
  #ifndef CMSIS_VECTAB_VIRTUAL_HEADER_FILE
    #define CMSIS_VECTAB_VIRTUAL_HEADER_FILE "cmsis_vectab_virtual.h"
  #endif
  #include CMSIS_VECTAB_VIRTUAL_HEADER_FILE
#else
  #define NVIC_SetVector              __NVIC_SetVector
  #define NVIC_GetVector              __NVIC_GetVector
#endif  /* (CMSIS_VECTAB_VIRTUAL) */

#define NVIC_USER_IRQ_OFFSET          16


/* 以下EXC_RETURN值保存在LR on异常条目中*/
#define EXC_RETURN_HANDLER         (0xFFFFFFF1UL)     /* 返回到处理程序模式，返回后使用MSP*/
#define EXC_RETURN_THREAD_MSP      (0xFFFFFFF9UL)     /* 返回到线程模式，返回后使用MSP*/
#define EXC_RETURN_THREAD_PSP      (0xFFFFFFFDUL)     /* 返回线程模式，返回后使用PSP*/


/* 中断优先级只能在Armv6-M下访问WORD*/
/* 以下MACROS处理寄存器偏移量和字节掩码的生成*/
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _SHP_IDX(IRQn)           ( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >>    2UL)      )
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

#define __NVIC_SetPriorityGrouping(X) (void)(X)
#define __NVIC_GetPriorityGrouping()  (0U)

/**
  \brief Enable Interrupt\details启用NVIC中断控制器中的设备特定中断。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Get Interrupt Enable status \details从NVIC中断控制器返回设备特定的中断启用状态。\param[in]IRQn设备特定中断号。\return 0未启用中断。\return 1中断被启用。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISER[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief Disable Interrupt\details禁用NVIC中断控制器中的设备特定中断。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}


/**
  \brief Get Pending Interrupt\details读取NVIC挂起寄存器并返回指定设备特定中断的挂起位。\param[in]IRQn设备特定中断号。\return 0中断状态未挂起。\return 1中断状态为待定。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISPR[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief Set Pending Interrupt\details设置NVIC挂起寄存器中设备特定中断的挂起位。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Clear Pending Interrupt\details清除NVIC挂起寄存器中设备特定中断的挂起位。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Set Interrupt Priority\details设置设备特定中断或处理器异常的优先级。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\param[in]要设置的优先级。\注意：不能为每个处理器异常设置优先级。
 */
__STATIC_INLINE void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IP[_IP_IDX(IRQn)]  = ((uint32_t)(NVIC->IP[_IP_IDX(IRQn)]  & ~(0xFFUL << _BIT_SHIFT(IRQn))) |
       (((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << _BIT_SHIFT(IRQn)));
  }
  else
  {
    SCB->SHP[_SHP_IDX(IRQn)] = ((uint32_t)(SCB->SHP[_SHP_IDX(IRQn)] & ~(0xFFUL << _BIT_SHIFT(IRQn))) |
       (((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << _BIT_SHIFT(IRQn)));
  }
}


/**
  \brief Get Interrupt Priority\details读取设备特定中断或处理器异常的优先级。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\return中断优先级。值自动与微控制器的实现优先级位对齐。
 */
__STATIC_INLINE uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->IP[ _IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) & (uint32_t)0xFFUL) >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return((uint32_t)(((SCB->SHP[_SHP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) & (uint32_t)0xFFUL) >> (8U - __NVIC_PRIO_BITS)));
  }
}


/**
  \brief Encode Priority\details使用给定的优先级组、抢占优先级值和子优先级值对中断的优先级进行编码。如果优先级分组和可用优先级位（__NVIC_PRIO_bits）之间发生冲突，则设置最小的可能优先级组。\param[in]PriorityGroup使用的优先级组。\param[in]抢占优先级抢占优先级值（从0开始）。\param[in]SubPriority SubPriority值（从0开始）。\return编码的优先级。值可以在函数\ref __NVIC_SetPriority（）中使用。
 */
__STATIC_INLINE uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* 仅使用值0..7*/
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}


/**
  \brief Decode Priority\details将具有给定优先级组的中断优先级值解码为抢占优先级值和子优先级值。如果优先级分组和可用优先级位（__NVIC_PRIO_bits）之间存在冲突，则设置最小的可能优先级组。\param[in]Priority Priority值，可使用函数\ref __NVIC_GetPriority（）检索。\param[in]PriorityGroup使用的优先级组。\param[out]pPreemptPriority抢占优先级值（从0开始）。\param[out]pSubPrioritySubpriority值（从0开始）。
 */
__STATIC_INLINE void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* 仅使用值0..7*/
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}



/**
  \brief Set Interrupt Vector\details在基于SRAM的中断向量表中设置中断向量。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。地址0必须映射到SRAM。\param[in]IRQn中断号\param[in]vector中断处理程序函数的地址
 */
__STATIC_INLINE void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t vectors = 0x0U;
  (* (int *) (vectors + ((int32_t)IRQn + NVIC_USER_IRQ_OFFSET) * 4)) = vector;
}


/**
  \brief Get Interrupt Vector\details从中断向量表中读取中断向量。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\return中断处理程序函数的地址
 */
__STATIC_INLINE uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t vectors = 0x0U;
  return (uint32_t)(* (int *) (vectors + ((int32_t)IRQn + NVIC_USER_IRQ_OFFSET) * 4));
}


/**
  \brief System Reset \details启动系统重置请求以重置MCU。
 */
__NO_RETURN __STATIC_INLINE void __NVIC_SystemReset(void)
{
  __DSB();                                                          /* 确保所有未完成的内存访问（包括缓冲写入）在重置前完成*/
  SCB->AIRCR  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                 SCB_AIRCR_SYSRESETREQ_Msk);
  __DSB();                                                          /* 确保完成内存访问*/

  for(;;)                                                           /* 等待重置*/
  {
    __NOP();
  }
}

/*@}CMSIS_Core_NVICFunctions结束*/


/* ##########################FPU功能#############*/
/**
  \ingroup CMSIS_Core_FunctionInterface\defgroup CMSIS-Core_FpuFunctions FPU Functions\brief提供FPU类型的函数@{
 */

/**
  \brief get FPU type\details返回FPU类型\return
   -\b 0：无FPU
   -\b 1：单精度FPU
   -\b 2：双精度+单精度FPU
 */
__STATIC_INLINE uint32_t SCB_GetFPUType(void)
{
    return 0U;           /* 无FPU*/
}


/*@}CMSIS_Core_FpuFunctions结束*/



/* ##################################SysTick函数#############*/
/**
  \ingroup CMSIS_Core_FunctionInterface\defgroup CMSIS-Core_SysTickFunctions SysTick Functions\brief配置系统的函数@{
 */

#if defined (__Vendor_SysTickConfig) && (__Vendor_SysTickConfig == 0U)

/**
  \brief System Tick Configuration \ details初始化System Timer及其中断，并启动System Tick Timer。计数器处于自由运行模式，以生成周期性中断。\param[in]ticks两个中断之间的刻度数。\return 0函数成功。\return 1函数失败。\注意：当变量<b>__Vendor_SysTickConfig</b>设置为1时，则不包括函数<b>SysTick_Config</b>。在这种情况下，文件<b><i>设备</i>。h</b>必须包含此函数的供应商特定实现。
 */
__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   /* 无法重新加载值*/
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* 设置重新加载寄存器*/
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* 设置Systick中断的优先级*/
  SysTick->VAL   = 0UL;                                             /* 加载SysTick计数器值*/
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* 启用SysTick IRQ和SysTick计时器*/
  return (0UL);                                                     /* 功能成功*/
}

#endif

/*@}CMSIS_Core_SysTickFunctions结束*/




#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM0_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */

