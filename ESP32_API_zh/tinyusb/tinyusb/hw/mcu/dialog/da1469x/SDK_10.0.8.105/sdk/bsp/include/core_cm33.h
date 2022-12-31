/**************************************************************************//**
 * @file     core_cm33.h
 * @brief    CMSIS Cortex-M33 Core Peripheral Access Layer Header File
 * @version  V5.1.0
 * @date     12. November 2018
 ******************************************************************************/
/*
 * 版权所有（c）2009-2018 Arm Limited。保留所有权利。
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

#ifndef __CORE_CM33_H_GENERIC
#define __CORE_CM33_H_GENERIC

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
  \内部组Cortex_M33@{
 */

#include "cmsis_version.h"

/*  CMSIS CM33定义*/
#define __CM33_CMSIS_VERSION_MAIN  (__CM_CMSIS_VERSION_MAIN)                   /*!< \已弃用[31:16]CMSIS HAL主版本*/
#define __CM33_CMSIS_VERSION_SUB   (__CM_CMSIS_VERSION_SUB)                    /*!< \已弃用[15:0]CMSIS HAL子版本*/
#define __CM33_CMSIS_VERSION       ((__CM33_CMSIS_VERSION_MAIN << 16U) | \
                                     __CM33_CMSIS_VERSION_SUB           )      /*!< \已弃用的CMSIS HAL版本号*/

#define __CORTEX_M                 (33U)                                       /*!< Cortex-M内核*/

/** __FPU_USED指示是否使用FPU。为此，在使用FPU特定寄存器和功能之前，必须检查__FPU_PRESENT。
*/
#if defined ( __CC_ARM )
  #if defined (__TARGET_FPU_VFP)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if defined (__ARM_FP)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined ( __ICCARM__ )
  #if defined (__ARMVFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined ( __TI_ARM__ )
  #if defined (__TI_VFP_SUPPORT__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TASKING__ )
  #if defined (__FPU_VFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __CSMC__ )
  #if ( __CSMC__ & 0x400U)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#endif

#include "cmsis_compiler.h"               /* CMSIS编译器特定的定义*/


#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM33_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CM33_H_DEPENDANT
#define __CORE_CM33_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* 检查设备定义和使用默认值*/
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __CM33_REV
    #define __CM33_REV                0x0000U
    #warning "__CM33_REV not defined in device header file; using default!"
  #endif

  #ifndef __FPU_PRESENT
    #define __FPU_PRESENT             0U
    #warning "__FPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __MPU_PRESENT
    #define __MPU_PRESENT             0U
    #warning "__MPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __SAUREGION_PRESENT
    #define __SAUREGION_PRESENT       0U
    #warning "__SAUREGION_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __DSP_PRESENT
    #define __DSP_PRESENT             0U
    #warning "__DSP_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __NVIC_PRIO_BITS
    #define __NVIC_PRIO_BITS          3U
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

/*@}Cortex_M33组结束*/



/*******************************************************************************
 *                 寄存器抽象核心寄存器包含：
  -核心寄存器
  -核心NVIC寄存器
  -核心SCB寄存器
  -核心SysTick寄存器
  -核心调试寄存器
  -核心MPU寄存器
  -核心SAU寄存器
  -核心FPU寄存器
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
    uint32_t _reserved0:16;              /*!< 位：0..15保留*/
    uint32_t GE:4;                       /*!< 位：16..19大于或等于标志*/
    uint32_t _reserved1:7;               /*!< 位：20..26保留*/
    uint32_t Q:1;                        /*!< bit:27饱和条件标志*/
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

#define APSR_Q_Pos                         27U                                            /*!< APSR:Q位置*/
#define APSR_Q_Msk                         (1UL << APSR_Q_Pos)                            /*!< APSR:Q掩码*/

#define APSR_GE_Pos                        16U                                            /*!< APSR:GE职位*/
#define APSR_GE_Msk                        (0xFUL << APSR_GE_Pos)                         /*!< APSR:GE面罩*/


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
    uint32_t _reserved0:7;               /*!< 位：9..15保留*/
    uint32_t GE:4;                       /*!< 位：16..19大于或等于标志*/
    uint32_t _reserved1:4;               /*!< 位：20..23保留*/
    uint32_t T:1;                        /*!< bit:24 Thumb位（读取0）*/
    uint32_t IT:2;                       /*!< 位：25..26已保存IT状态（读取0）*/
    uint32_t Q:1;                        /*!< bit:27饱和条件标志*/
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

#define xPSR_Q_Pos                         27U                                            /*!< xPSR:Q位置*/
#define xPSR_Q_Msk                         (1UL << xPSR_Q_Pos)                            /*!< xPSR:Q掩码*/

#define xPSR_IT_Pos                        25U                                            /*!< xPSR:IT职位*/
#define xPSR_IT_Msk                        (3UL << xPSR_IT_Pos)                           /*!< xPSR:IT掩码*/

#define xPSR_T_Pos                         24U                                            /*!< xPSR:T位置*/
#define xPSR_T_Msk                         (1UL << xPSR_T_Pos)                            /*!< xPSR:T掩码*/

#define xPSR_GE_Pos                        16U                                            /*!< xPSR:GE职位*/
#define xPSR_GE_Msk                        (0xFUL << xPSR_GE_Pos)                         /*!< xPSR:GE掩码*/

#define xPSR_ISR_Pos                        0U                                            /*!< xPSR:ISR位置*/
#define xPSR_ISR_Msk                       (0x1FFUL /*<<xSR_ISR_Pos*/)                  /*!< xPSR:ISR掩码*/


/**
  \简短的Union类型以访问控制寄存器（Control）。
 */
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                    /*!< bit:0线程模式下的执行权限*/
    uint32_t SPSEL:1;                    /*!< bit:1堆栈指针选择*/
    uint32_t FPCA:1;                     /*!< bit:2浮点上下文激活*/
    uint32_t SFPA:1;                     /*!< bit:3安全浮点活动*/
    uint32_t _reserved1:28;              /*!< 位：4..31保留*/
  } b;                                   /*!< 用于位访问的结构*/
  uint32_t w;                            /*!< 用于字访问的类型*/
} CONTROL_Type;

/* 控制寄存器定义*/
#define CONTROL_SFPA_Pos                    3U                                            /*!< 控制：SFPA位置*/
#define CONTROL_SFPA_Msk                   (1UL << CONTROL_SFPA_Pos)                      /*!< 控制：SFPA面罩*/

#define CONTROL_FPCA_Pos                    2U                                            /*!< 控制：FPCA位置*/
#define CONTROL_FPCA_Msk                   (1UL << CONTROL_FPCA_Pos)                      /*!< 控制：FPCA掩码*/

#define CONTROL_SPSEL_Pos                   1U                                            /*!< 控制：SPSEL位置*/
#define CONTROL_SPSEL_Msk                  (1UL << CONTROL_SPSEL_Pos)                     /*!< 控制：SPSEL掩码*/

#define CONTROL_nPRIV_Pos                   0U                                            /*!< 控制：nPRIV位置*/
#define CONTROL_nPRIV_Msk                  (1UL /*<<控制_压力_位置*/)                 /*!< 控制：nPRIV掩码*/

/*@}CMSIS_CORE组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_NVIC嵌套矢量中断控制器（NVIC）\NVIC寄存器的简要类型定义@{
 */

/**
  \访问嵌套矢量中断控制器（NVIC）的简短结构类型。
 */
typedef struct
{
  __IOM uint32_t ISER[16U];              /*!< 偏移：0x000（R/W）中断设置启用寄存器*/
        uint32_t RESERVED0[16U];
  __IOM uint32_t ICER[16U];              /*!< 偏移量：0x080（R/W）中断清除启用寄存器*/
        uint32_t RSERVED1[16U];
  __IOM uint32_t ISPR[16U];              /*!< 偏移量：0x100（R/W）中断设置挂起寄存器*/
        uint32_t RESERVED2[16U];
  __IOM uint32_t ICPR[16U];              /*!< 偏移量：0x180（R/W）中断清除挂起寄存器*/
        uint32_t RESERVED3[16U];
  __IOM uint32_t IABR[16U];              /*!< 偏移量：0x200（R/W）中断活动位寄存器*/
        uint32_t RESERVED4[16U];
  __IOM uint32_t ITNS[16U];              /*!< 偏移量：0x280（R/W）中断非安全状态寄存器*/
        uint32_t RESERVED5[16U];
  __IOM uint8_t  IPR[496U];              /*!< 偏移量：0x300（R/W）中断优先级寄存器（8位宽）*/
        uint32_t RESERVED6[580U];
  __OM  uint32_t STIR;                   /*!< 偏移量：0xE00（/W）软件触发中断寄存器*/
}  NVIC_Type;

/* 软件触发中断寄存器定义*/
#define NVIC_STIR_INTID_Pos                 0U                                         /*!< STIR：内倾位置*/
#define NVIC_STIR_INTID_Msk                (0x1FFUL /*<<NVIC_STIR_INTID_Pos*/)        /*!< STIR:INTLINESNUM面罩*/

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
  __IOM uint32_t VTOR;                   /*!< 偏移：0x008（R/W）矢量表偏移寄存器*/
  __IOM uint32_t AIRCR;                  /*!< 偏移量：0x00C（R/W）应用程序中断和复位控制寄存器*/
  __IOM uint32_t SCR;                    /*!< 偏移量：0x010（R/W）系统控制寄存器*/
  __IOM uint32_t CCR;                    /*!< 偏移量：0x014（R/W）配置控制寄存器*/
  __IOM uint8_t  SHPR[12U];              /*!< 偏移量：0x018（R/W）系统处理程序优先级寄存器（4-7、8-11、12-15）*/
  __IOM uint32_t SHCSR;                  /*!< 偏移量：0x024（R/W）系统处理程序控制和状态寄存器*/
  __IOM uint32_t CFSR;                   /*!< 偏移量：0x028（R/W）可配置故障状态寄存器*/
  __IOM uint32_t HFSR;                   /*!< 偏移量：0x02C（R/W）硬故障状态寄存器*/
  __IOM uint32_t DFSR;                   /*!< 偏移量：0x030（R/W）调试故障状态寄存器*/
  __IOM uint32_t MMFAR;                  /*!< 偏移量：0x034（R/W）MemManage故障地址寄存器*/
  __IOM uint32_t BFAR;                   /*!< 偏移量：0x038（R/W）总线故障地址寄存器*/
  __IOM uint32_t AFSR;                   /*!< 偏移量：0x03C（R/W）辅助故障状态寄存器*/
  __IM  uint32_t ID_PFR[2U];             /*!< 偏移量：0x040（R/）处理器功能寄存器*/
  __IM  uint32_t ID_DFR;                 /*!< 偏移量：0x048（R/）调试功能寄存器*/
  __IM  uint32_t ID_ADR;                 /*!< 偏移量：0x04C（R/）辅助功能寄存器*/
  __IM  uint32_t ID_MMFR[4U];            /*!< 偏移量：0x050（R/）内存型号功能寄存器*/
  __IM  uint32_t ID_ISAR[6U];            /*!< 偏移量：0x060（R/）指令集属性寄存器*/
  __IM  uint32_t CLIDR;                  /*!< 偏移量：0x078（R/）缓存级别ID寄存器*/
  __IM  uint32_t CTR;                    /*!< 偏移量：0x07C（R/）缓存类型寄存器*/
  __IM  uint32_t CCSIDR;                 /*!< 偏移量：0x080（R/）缓存大小ID寄存器*/
  __IOM uint32_t CSSELR;                 /*!< 偏移量：0x084（R/W）缓存大小选择寄存器*/
  __IOM uint32_t CPACR;                  /*!< 偏移量：0x088（R/W）协处理器访问控制寄存器*/
  __IOM uint32_t NSACR;                  /*!< 偏移量：0x08C（R/W）非安全访问控制寄存器*/
        uint32_t RESERVED3[92U];
  __OM  uint32_t STIR;                   /*!< 偏移量：0x200（/W）软件触发中断寄存器*/
        uint32_t RESERVED4[15U];
  __IM  uint32_t MVFR0;                  /*!< 偏移量：0x240（R/）介质和VFP功能寄存器0*/
  __IM  uint32_t MVFR1;                  /*!< 偏移量：0x244（R/）介质和VFP功能寄存器1*/
  __IM  uint32_t MVFR2;                  /*!< 偏移量：0x248（R/）介质和VFP功能寄存器2*/
        uint32_t RESERVED5[1U];
  __OM  uint32_t ICIALLU;                /*!< 偏移：0x250（/W）I-Cache使所有PoU无效*/
        uint32_t RESERVED6[1U];
  __OM  uint32_t ICIMVAU;                /*!< 偏移量：0x258（/W）I-Cache因MVA到PoU而无效*/
  __OM  uint32_t DCIMVAC;                /*!< 偏移量：0x25C（/W）D-Cache因MVA到PoC而无效*/
  __OM  uint32_t DCISW;                  /*!< 偏移量：0x260（/W）D-Cache按Set方式无效*/
  __OM  uint32_t DCCMVAU;                /*!< 偏移量：0x264（/W）D-Cache清理MVA到PoU*/
  __OM  uint32_t DCCMVAC;                /*!< 偏移量：0x268（/W）D-Cache Clean by MVA to PoC*/
  __OM  uint32_t DCCSW;                  /*!< 偏移量：0x26C（/W）D-缓存按设置方式清除*/
  __OM  uint32_t DCCIMVAC;               /*!< 偏移量：0x270（/W）D-Cache清理并使MVA到PoC无效*/
  __OM  uint32_t DCCISW;                 /*!< 偏移量：0x274（/W）D-缓存按设置方式清除和无效*/
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
#define SCB_ICSR_PENDNMISET_Pos            31U                                            /*!< SCB ICSR：待定位置*/
#define SCB_ICSR_PENDNMISET_Msk            (1UL << SCB_ICSR_PENDNMISET_Pos)               /*!< SCB ICSR:PENDNMISET掩码*/

#define SCB_ICSR_NMIPENDSET_Pos            SCB_ICSR_PENDNMISET_Pos                        /*!< SCB ICSR:NMIPENDSET位置，向后兼容*/
#define SCB_ICSR_NMIPENDSET_Msk            SCB_ICSR_PENDNMISET_Msk                        /*!< SCB ICSR:NMIPENDSET掩码，向后兼容*/

#define SCB_ICSR_PENDNMICLR_Pos            30U                                            /*!< SCB ICSR:PENDNMICLR位置*/
#define SCB_ICSR_PENDNMICLR_Msk            (1UL << SCB_ICSR_PENDNMICLR_Pos)               /*!< SCB ICSR:PENDNMICLR掩码*/

#define SCB_ICSR_PENDSVSET_Pos             28U                                            /*!< SCB ICSR:PENDSVSET位置*/
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR:PENDSVSET掩码*/

#define SCB_ICSR_PENDSVCLR_Pos             27U                                            /*!< SCB ICSR:PENDSVCLR位置*/
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)                /*!< SCB ICSR:PENDSVCLR掩码*/

#define SCB_ICSR_PENDSTSET_Pos             26U                                            /*!< SCB ICSR：待定设置位置*/
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR:PENDSTSET掩码*/

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            /*!< SCB ICSR：待定CLR位置*/
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR:PENDSTCLR掩码*/

#define SCB_ICSR_STTNS_Pos                 24U                                            /*!< SCB ICSR：STTNS职位（安全扩展）*/
#define SCB_ICSR_STTNS_Msk                 (1UL << SCB_ICSR_STTNS_Pos)                    /*!< SCB ICSR:STTNS掩码（安全扩展）*/

#define SCB_ICSR_ISRPREEMPT_Pos            23U                                            /*!< SCB ICSR:ISRPREEMPT位置*/
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)               /*!< SCB ICSR:ISRPREEMPT掩码*/

#define SCB_ICSR_ISRPENDING_Pos            22U                                            /*!< SCB ICSR：ISRPENDING位置*/
#define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)               /*!< SCB ICSR：ISRPENDING掩码*/

#define SCB_ICSR_VECTPENDING_Pos           12U                                            /*!< SCB ICSR：矢量结束位置*/
#define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)          /*!< SCB ICSR：VECTPENDING掩码*/

#define SCB_ICSR_RETTOBASE_Pos             11U                                            /*!< SCB ICSR：RETTOBASE位置*/
#define SCB_ICSR_RETTOBASE_Msk             (1UL << SCB_ICSR_RETTOBASE_Pos)                /*!< SCB ICSR:RETTOBASE掩码*/

#define SCB_ICSR_VECTACTIVE_Pos             0U                                            /*!< SCB ICSR：矢量位置*/
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL /*<<SCB_ICSR_VETACTIVE_Pos*/)       /*!< SCB ICSR：矢量掩模*/

/* SCB矢量表偏移寄存器定义*/
#define SCB_VTOR_TBLOFF_Pos                 7U                                            /*!< SCB VTOR:TBLOFF位置*/
#define SCB_VTOR_TBLOFF_Msk                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)           /*!< SCB VTOR:TBLOFF掩码*/

/* SCB应用程序中断和复位控制寄存器定义*/
#define SCB_AIRCR_VECTKEY_Pos              16U                                            /*!< SCB AIRCR:VECTKEY位置*/
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR:VECTKEY面罩*/

#define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                            /*!< SCB AIRCR:VETKEYSTAT位置*/
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR:VECTKEYSTAT面罩*/

#define SCB_AIRCR_ENDIANESS_Pos            15U                                            /*!< SCB AIRCR:末端位置*/
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)               /*!< SCB AIRCR:ENDIANESS面罩*/

#define SCB_AIRCR_PRIS_Pos                 14U                                            /*!< SCB AIRCR:PRIS位置*/
#define SCB_AIRCR_PRIS_Msk                 (1UL << SCB_AIRCR_PRIS_Pos)                    /*!< SCB AIRCR:PRIS面罩*/

#define SCB_AIRCR_BFHFNMINS_Pos            13U                                            /*!< SCB飞机：BFHFNMINS位置*/
#define SCB_AIRCR_BFHFNMINS_Msk            (1UL << SCB_AIRCR_BFHFNMINS_Pos)               /*!< SCB AIRCR:BFHFNMINS面罩*/

#define SCB_AIRCR_PRIGROUP_Pos              8U                                            /*!< SCB AIRCR:PRIGROUP职位*/
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR:PRIGROUP掩码*/

#define SCB_AIRCR_SYSRESETREQS_Pos          3U                                            /*!< SCB AIRCR:SYSRESETREQS位置*/
#define SCB_AIRCR_SYSRESETREQS_Msk         (1UL << SCB_AIRCR_SYSRESETREQS_Pos)            /*!< SCB AIRCR:SYSRESETREQS掩码*/

#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            /*!< SCB AIRCR:SYSRESETREQ位置*/
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR:SYSRESETREQ掩码*/

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                            /*!< SCB AIRCR:VETCLRACTIVE位置*/
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)           /*!< SCB AIRCR:VETCLRACTIVE面罩*/

/* SCB系统控制寄存器定义*/
#define SCB_SCR_SEVONPEND_Pos               4U                                            /*!< SCB SCR：SEVONPEND位置*/
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 /*!< SCB SCR：SEVONPEND掩码*/

#define SCB_SCR_SLEEPDEEPS_Pos              3U                                            /*!< SCB SCR：睡眠深度位置*/
#define SCB_SCR_SLEEPDEEPS_Msk             (1UL << SCB_SCR_SLEEPDEEPS_Pos)                /*!< SCB SCR：睡眠睡眠面罩*/

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            /*!< SCB SCR：睡眠深度位置*/
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR：睡眠深度面罩*/

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            /*!< SCB SCR：SLEEPONEXIT位置*/
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               /*!< SCB SCR：SLEPONEXIT掩码*/

/* SCB配置控制寄存器定义*/
#define SCB_CCR_BP_Pos                     18U                                            /*!< SCB CCR:BP位置*/
#define SCB_CCR_BP_Msk                     (1UL << SCB_CCR_BP_Pos)                        /*!< SCB CCR:BP掩码*/

#define SCB_CCR_IC_Pos                     17U                                            /*!< SCB CCR:IC位置*/
#define SCB_CCR_IC_Msk                     (1UL << SCB_CCR_IC_Pos)                        /*!< SCB CCR:IC掩码*/

#define SCB_CCR_DC_Pos                     16U                                            /*!< SCB CCR:DC位置*/
#define SCB_CCR_DC_Msk                     (1UL << SCB_CCR_DC_Pos)                        /*!< SCB CCR:DC掩码*/

#define SCB_CCR_STKOFHFNMIGN_Pos           10U                                            /*!< SCB CCR：STKOFHFNMIGN位置*/
#define SCB_CCR_STKOFHFNMIGN_Msk           (1UL << SCB_CCR_STKOFHFNMIGN_Pos)              /*!< SCB CCR：STKOFHFNMIGN面罩*/

#define SCB_CCR_BFHFNMIGN_Pos               8U                                            /*!< SCB CCR：BFHFNMIGN位置*/
#define SCB_CCR_BFHFNMIGN_Msk              (1UL << SCB_CCR_BFHFNMIGN_Pos)                 /*!< SCB CCR：BFHFNMIGN掩码*/

#define SCB_CCR_DIV_0_TRP_Pos               4U                                            /*!< SCB CCR:DIV_0_TRP位置*/
#define SCB_CCR_DIV_0_TRP_Msk              (1UL << SCB_CCR_DIV_0_TRP_Pos)                 /*!< SCB CCR:DIV_0_TRP掩码*/

#define SCB_CCR_UNALIGN_TRP_Pos             3U                                            /*!< SCB CCR:UNALIGN_TRP位置*/
#define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)               /*!< SCB CCR:UNALIGN_TRP掩码*/

#define SCB_CCR_USERSETMPEND_Pos            1U                                            /*!< SCB CCR:USERSETMPEND位置*/
#define SCB_CCR_USERSETMPEND_Msk           (1UL << SCB_CCR_USERSETMPEND_Pos)              /*!< SCB CCR:USERSETMPEND掩码*/

/* SCB系统处理程序控制和状态寄存器定义*/
#define SCB_SHCSR_HARDFAULTPENDED_Pos      21U                                            /*!< SCB SHCSR：硬故障端位置*/
#define SCB_SHCSR_HARDFAULTPENDED_Msk      (1UL << SCB_SHCSR_HARDFAULTPENDED_Pos)         /*!< SCB SHCSR：HARDFAULTPEND掩码*/

#define SCB_SHCSR_SECUREFAULTPENDED_Pos    20U                                            /*!< SCB SHCSR：安全故障结束位置*/
#define SCB_SHCSR_SECUREFAULTPENDED_Msk    (1UL << SCB_SHCSR_SECUREFAULTPENDED_Pos)       /*!< SCB SHCSR:SECUREFAULTPENDED面罩*/

#define SCB_SHCSR_SECUREFAULTENA_Pos       19U                                            /*!< SCB SHCSR：安全故障位置*/
#define SCB_SHCSR_SECUREFAULTENA_Msk       (1UL << SCB_SHCSR_SECUREFAULTENA_Pos)          /*!< SCB SHCSR：SECUREFULTENA面罩*/

#define SCB_SHCSR_USGFAULTENA_Pos          18U                                            /*!< SCB SHCSR：USGFULTENA位置*/
#define SCB_SHCSR_USGFAULTENA_Msk          (1UL << SCB_SHCSR_USGFAULTENA_Pos)             /*!< SCB SHCSR:USGFULTENA面罩*/

#define SCB_SHCSR_BUSFAULTENA_Pos          17U                                            /*!< SCB SHCSR：母线故障位置*/
#define SCB_SHCSR_BUSFAULTENA_Msk          (1UL << SCB_SHCSR_BUSFAULTENA_Pos)             /*!< SCB SHCSR：BUSFAULTENA掩码*/

#define SCB_SHCSR_MEMFAULTENA_Pos          16U                                            /*!< SCB SHCSR：MEMFAULTENA位置*/
#define SCB_SHCSR_MEMFAULTENA_Msk          (1UL << SCB_SHCSR_MEMFAULTENA_Pos)             /*!< SCB SHCSR：MEMFAULTENA面罩*/

#define SCB_SHCSR_SVCALLPENDED_Pos         15U                                            /*!< SCB SHCSR：SVCALLPENDED位置*/
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)            /*!< SCB SHCSR：SVCALLPENDED掩码*/

#define SCB_SHCSR_BUSFAULTPENDED_Pos       14U                                            /*!< SCB SHCSR：总线故障端位置*/
#define SCB_SHCSR_BUSFAULTPENDED_Msk       (1UL << SCB_SHCSR_BUSFAULTPENDED_Pos)          /*!< SCB SHCSR：BUSFAULTPENDED掩码*/

#define SCB_SHCSR_MEMFAULTPENDED_Pos       13U                                            /*!< SCB SHCSR：MEMFAULTPEND位置*/
#define SCB_SHCSR_MEMFAULTPENDED_Msk       (1UL << SCB_SHCSR_MEMFAULTPENDED_Pos)          /*!< SCB SHCSR：MEMFAULTPENDED掩码*/

#define SCB_SHCSR_USGFAULTPENDED_Pos       12U                                            /*!< SCB SHCSR：USGFAULTEND位置*/
#define SCB_SHCSR_USGFAULTPENDED_Msk       (1UL << SCB_SHCSR_USGFAULTPENDED_Pos)          /*!< SCB SHCSR:USGFAULTPENDED面罩*/

#define SCB_SHCSR_SYSTICKACT_Pos           11U                                            /*!< SCB SHCSR:SYSTICKACT位置*/
#define SCB_SHCSR_SYSTICKACT_Msk           (1UL << SCB_SHCSR_SYSTICKACT_Pos)              /*!< SCB SHCSR:SYSTICKACT面罩*/

#define SCB_SHCSR_PENDSVACT_Pos            10U                                            /*!< SCB SHCSR：待定位置*/
#define SCB_SHCSR_PENDSVACT_Msk            (1UL << SCB_SHCSR_PENDSVACT_Pos)               /*!< SCB SHCSR:PENDSVACT掩码*/

#define SCB_SHCSR_MONITORACT_Pos            8U                                            /*!< SCB SHCSR：监控位置*/
#define SCB_SHCSR_MONITORACT_Msk           (1UL << SCB_SHCSR_MONITORACT_Pos)              /*!< SCB SHCSR：MONITORACT面罩*/

#define SCB_SHCSR_SVCALLACT_Pos             7U                                            /*!< SCB SHCSR：SVCALLACT位置*/
#define SCB_SHCSR_SVCALLACT_Msk            (1UL << SCB_SHCSR_SVCALLACT_Pos)               /*!< SCB SHCSR：SVCALLACT掩码*/

#define SCB_SHCSR_NMIACT_Pos                5U                                            /*!< SCB SHCSR：NMIACT位置*/
#define SCB_SHCSR_NMIACT_Msk               (1UL << SCB_SHCSR_NMIACT_Pos)                  /*!< SCB SHCSR：NMIACT面罩*/

#define SCB_SHCSR_SECUREFAULTACT_Pos        4U                                            /*!< SCB SHCSR：安全故障位置*/
#define SCB_SHCSR_SECUREFAULTACT_Msk       (1UL << SCB_SHCSR_SECUREFAULTACT_Pos)          /*!< SCB SHCSR:SECUREFULTACT面罩*/

#define SCB_SHCSR_USGFAULTACT_Pos           3U                                            /*!< SCB SHCSR：USGFAULTACT位置*/
#define SCB_SHCSR_USGFAULTACT_Msk          (1UL << SCB_SHCSR_USGFAULTACT_Pos)             /*!< SCB SHCSR:USGFAULTACT面罩*/

#define SCB_SHCSR_HARDFAULTACT_Pos          2U                                            /*!< SCB SHCSR：硬故障位置*/
#define SCB_SHCSR_HARDFAULTACT_Msk         (1UL << SCB_SHCSR_HARDFAULTACT_Pos)            /*!< SCB SHCSR：HARDFULTACT面罩*/

#define SCB_SHCSR_BUSFAULTACT_Pos           1U                                            /*!< SCB SHCSR：总线故障位置*/
#define SCB_SHCSR_BUSFAULTACT_Msk          (1UL << SCB_SHCSR_BUSFAULTACT_Pos)             /*!< SCB SHCSR：BUSFAULTACT面罩*/

#define SCB_SHCSR_MEMFAULTACT_Pos           0U                                            /*!< SCB SHCSR：MEMFAULTACT位置*/
#define SCB_SHCSR_MEMFAULTACT_Msk          (1UL /*<<SCB_SHCSR_MEMFAULTACT_Pos*/)         /*!< SCB SHCSR：MEMFAULTACT面罩*/

/* SCB可配置故障状态寄存器定义*/
#define SCB_CFSR_USGFAULTSR_Pos            16U                                            /*!< SCB CFSR：使用故障状态寄存器位置*/
#define SCB_CFSR_USGFAULTSR_Msk            (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos)          /*!< SCB CFSR：使用故障状态寄存器掩码*/

#define SCB_CFSR_BUSFAULTSR_Pos             8U                                            /*!< SCB CFSR：总线故障状态寄存器位置*/
#define SCB_CFSR_BUSFAULTSR_Msk            (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)            /*!< SCB CFSR：总线故障状态寄存器掩码*/

#define SCB_CFSR_MEMFAULTSR_Pos             0U                                            /*!< SCB CFSR：内存管理故障状态寄存器位置*/
#define SCB_CFSR_MEMFAULTSR_Msk            (0xFFUL /*<<SCB_CFSR_MEMFAULTSR_Pos*/)        /*!< SCB CFSR：内存管理故障状态寄存器掩码*/

/* MemManage故障状态寄存器（SCB可配置故障状态寄存器的一部分）*/
#define SCB_CFSR_MMARVALID_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 7U)               /*!< SCB CFSR（MMFSR）：MMARVALID位置*/
#define SCB_CFSR_MMARVALID_Msk             (1UL << SCB_CFSR_MMARVALID_Pos)                /*!< SCB CFSR（MMFSR）：MMARVALID掩码*/

#define SCB_CFSR_MLSPERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 5U)               /*!< SCB CFSR（MMFSR）：MLSPERR位置*/
#define SCB_CFSR_MLSPERR_Msk               (1UL << SCB_CFSR_MLSPERR_Pos)                  /*!< SCB CFSR（MMFSR）：MLSPERR掩码*/

#define SCB_CFSR_MSTKERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 4U)               /*!< SCB CFSR（MMFSR）：MSTKER位置*/
#define SCB_CFSR_MSTKERR_Msk               (1UL << SCB_CFSR_MSTKERR_Pos)                  /*!< SCB CFSR（MMFSR）：MSTKER掩码*/

#define SCB_CFSR_MUNSTKERR_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 3U)               /*!< SCB CFSR（MMFSR）：MUNSTKER位置*/
#define SCB_CFSR_MUNSTKERR_Msk             (1UL << SCB_CFSR_MUNSTKERR_Pos)                /*!< SCB CFSR（MMFSR）：MUNSTKER掩码*/

#define SCB_CFSR_DACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 1U)               /*!< SCB CFSR（MMFSR）：DACCVIL位置*/
#define SCB_CFSR_DACCVIOL_Msk              (1UL << SCB_CFSR_DACCVIOL_Pos)                 /*!< SCB CFSR（MMFSR）：DACCVIL面罩*/

#define SCB_CFSR_IACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 0U)               /*!< SCB CFSR（MMFSR）：IACCVOL位置*/
#define SCB_CFSR_IACCVIOL_Msk              (1UL /*<<SCB_CFSR_IACCVOL_Pos*/)             /*!< SCB CFSR（MMFSR）：IACCVOL掩码*/

/* 总线故障状态寄存器（SCB可配置故障状态寄存器的一部分）*/
#define SCB_CFSR_BFARVALID_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 7U)                  /*!< SCB CFSR（BFSR）：BFARVALID位置*/
#define SCB_CFSR_BFARVALID_Msk            (1UL << SCB_CFSR_BFARVALID_Pos)                 /*!< SCB CFSR（BFSR）：BFARVALID掩码*/

#define SCB_CFSR_LSPERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 5U)                  /*!< SCB CFSR（BFSR）：LSPERR位置*/
#define SCB_CFSR_LSPERR_Msk               (1UL << SCB_CFSR_LSPERR_Pos)                    /*!< SCB CFSR（BFSR）：LSPERR掩码*/

#define SCB_CFSR_STKERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 4U)                  /*!< SCB CFSR（BFSR）：STKER位置*/
#define SCB_CFSR_STKERR_Msk               (1UL << SCB_CFSR_STKERR_Pos)                    /*!< SCB CFSR（BFSR）：STKER掩码*/

#define SCB_CFSR_UNSTKERR_Pos             (SCB_CFSR_BUSFAULTSR_Pos + 3U)                  /*!< SCB CFSR（BFSR）：UNSTKERR位置*/
#define SCB_CFSR_UNSTKERR_Msk             (1UL << SCB_CFSR_UNSTKERR_Pos)                  /*!< SCB CFSR（BFSR）：UNSTKERR掩码*/

#define SCB_CFSR_IMPRECISERR_Pos          (SCB_CFSR_BUSFAULTSR_Pos + 2U)                  /*!< SCB CFSR（BFSR）：杂质位置*/
#define SCB_CFSR_IMPRECISERR_Msk          (1UL << SCB_CFSR_IMPRECISERR_Pos)               /*!< SCB CFSR（BFSR）：IMPRECISER掩码*/

#define SCB_CFSR_PRECISERR_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 1U)                  /*!< SCB CFSR（BFSR）：精确位置*/
#define SCB_CFSR_PRECISERR_Msk            (1UL << SCB_CFSR_PRECISERR_Pos)                 /*!< SCB CFSR（BFSR）：PRECISER掩码*/

#define SCB_CFSR_IBUSERR_Pos              (SCB_CFSR_BUSFAULTSR_Pos + 0U)                  /*!< SCB CFSR（BFSR）：IBUSERR位置*/
#define SCB_CFSR_IBUSERR_Msk              (1UL << SCB_CFSR_IBUSERR_Pos)                   /*!< SCB CFSR（BFSR）：IBUSERR掩码*/

/* UsageFault状态寄存器（SCB可配置故障状态寄存器的一部分）*/
#define SCB_CFSR_DIVBYZERO_Pos            (SCB_CFSR_USGFAULTSR_Pos + 9U)                  /*!< SCB CFSR（UFSR）：DIVBYZERO位置*/
#define SCB_CFSR_DIVBYZERO_Msk            (1UL << SCB_CFSR_DIVBYZERO_Pos)                 /*!< SCB CFSR（UFSR）：DIVBYZERO掩码*/

#define SCB_CFSR_UNALIGNED_Pos            (SCB_CFSR_USGFAULTSR_Pos + 8U)                  /*!< SCB CFSR（UFSR）：未对准位置*/
#define SCB_CFSR_UNALIGNED_Msk            (1UL << SCB_CFSR_UNALIGNED_Pos)                 /*!< SCB CFSR（UFSR）：未对准掩模*/

#define SCB_CFSR_STKOF_Pos                (SCB_CFSR_USGFAULTSR_Pos + 4U)                  /*!< SCB CFSR（UFSR）：STKOF位置*/
#define SCB_CFSR_STKOF_Msk                (1UL << SCB_CFSR_STKOF_Pos)                     /*!< SCB CFSR（UFSR）：STKOF掩码*/

#define SCB_CFSR_NOCP_Pos                 (SCB_CFSR_USGFAULTSR_Pos + 3U)                  /*!< SCB CFSR（UFSR）：NOCP位置*/
#define SCB_CFSR_NOCP_Msk                 (1UL << SCB_CFSR_NOCP_Pos)                      /*!< SCB CFSR（UFSR）：NOCP掩码*/

#define SCB_CFSR_INVPC_Pos                (SCB_CFSR_USGFAULTSR_Pos + 2U)                  /*!< SCB CFSR（UFSR）：INVPC位置*/
#define SCB_CFSR_INVPC_Msk                (1UL << SCB_CFSR_INVPC_Pos)                     /*!< SCB CFSR（UFSR）：INVPC掩码*/

#define SCB_CFSR_INVSTATE_Pos             (SCB_CFSR_USGFAULTSR_Pos + 1U)                  /*!< SCB CFSR（UFSR）：INVSTATE位置*/
#define SCB_CFSR_INVSTATE_Msk             (1UL << SCB_CFSR_INVSTATE_Pos)                  /*!< SCB CFSR（UFSR）：INVSTATE掩码*/

#define SCB_CFSR_UNDEFINSTR_Pos           (SCB_CFSR_USGFAULTSR_Pos + 0U)                  /*!< SCB CFSR（UFSR）：UNDEFINSTR位置*/
#define SCB_CFSR_UNDEFINSTR_Msk           (1UL << SCB_CFSR_UNDEFINSTR_Pos)                /*!< SCB CFSR（UFSR）：UNDEFINSTR掩码*/

/* SCB硬故障状态寄存器定义*/
#define SCB_HFSR_DEBUGEVT_Pos              31U                                            /*!< SCB HFSR：调试位置*/
#define SCB_HFSR_DEBUGEVT_Msk              (1UL << SCB_HFSR_DEBUGEVT_Pos)                 /*!< SCB HFSR:DEBUGEVT掩码*/

#define SCB_HFSR_FORCED_Pos                30U                                            /*!< SCB HFSR：强制位置*/
#define SCB_HFSR_FORCED_Msk                (1UL << SCB_HFSR_FORCED_Pos)                   /*!< SCB HFSR：强制掩码*/

#define SCB_HFSR_VECTTBL_Pos                1U                                            /*!< SCB HFSR:VECTTBL位置*/
#define SCB_HFSR_VECTTBL_Msk               (1UL << SCB_HFSR_VECTTBL_Pos)                  /*!< SCB HFSR:VECTTBL掩码*/

/* SCB调试故障状态寄存器定义*/
#define SCB_DFSR_EXTERNAL_Pos               4U                                            /*!< SCB DFSR：外部位置*/
#define SCB_DFSR_EXTERNAL_Msk              (1UL << SCB_DFSR_EXTERNAL_Pos)                 /*!< SCB DFSR：外部掩码*/

#define SCB_DFSR_VCATCH_Pos                 3U                                            /*!< SCB DFSR：VCATCH位置*/
#define SCB_DFSR_VCATCH_Msk                (1UL << SCB_DFSR_VCATCH_Pos)                   /*!< SCB DFSR：VCATCH掩码*/

#define SCB_DFSR_DWTTRAP_Pos                2U                                            /*!< SCB DFSR：DWTTRAP位置*/
#define SCB_DFSR_DWTTRAP_Msk               (1UL << SCB_DFSR_DWTTRAP_Pos)                  /*!< SCB DFSR：DWTTRAP掩码*/

#define SCB_DFSR_BKPT_Pos                   1U                                            /*!< SCB DFSR：BKPT位置*/
#define SCB_DFSR_BKPT_Msk                  (1UL << SCB_DFSR_BKPT_Pos)                     /*!< SCB DFSR：BKPT掩模*/

#define SCB_DFSR_HALTED_Pos                 0U                                            /*!< SCB DFSR：半位置*/
#define SCB_DFSR_HALTED_Msk                (1UL /*<<SCB_DFSR_HALTED_Pos*/)               /*!< SCB DFSR：HALTED面罩*/

/* SCB非安全访问控制寄存器定义*/
#define SCB_NSACR_CP11_Pos                 11U                                            /*!< SCB NSACR:CP11位置*/
#define SCB_NSACR_CP11_Msk                 (1UL << SCB_NSACR_CP11_Pos)                    /*!< SCB NSACR:CP11面罩*/

#define SCB_NSACR_CP10_Pos                 10U                                            /*!< SCB NSACR:CP10位置*/
#define SCB_NSACR_CP10_Msk                 (1UL << SCB_NSACR_CP10_Pos)                    /*!< SCB NSACR:CP10面罩*/

#define SCB_NSACR_CPn_Pos                   0U                                            /*!< SCB NSACR:CPn位置*/
#define SCB_NSACR_CPn_Msk                  (1UL /*<<SCB_NSACR_CPn_Pos*/)                 /*!< SCB NSACR:CPn面罩*/

/* SCB缓存级别ID寄存器定义*/
#define SCB_CLIDR_LOUU_Pos                 27U                                            /*!< SCB CLIDR:LoUU位置*/
#define SCB_CLIDR_LOUU_Msk                 (7UL << SCB_CLIDR_LOUU_Pos)                    /*!< SCB CLIDR:LoUU掩码*/

#define SCB_CLIDR_LOC_Pos                  24U                                            /*!< SCB CLIDR:LoC位置*/
#define SCB_CLIDR_LOC_Msk                  (7UL << SCB_CLIDR_LOC_Pos)                     /*!< SCB CLIDR:LoC掩码*/

/* SCB缓存类型寄存器定义*/
#define SCB_CTR_FORMAT_Pos                 29U                                            /*!< SCB CTR：格式位置*/
#define SCB_CTR_FORMAT_Msk                 (7UL << SCB_CTR_FORMAT_Pos)                    /*!< SCB CTR：格式掩码*/

#define SCB_CTR_CWG_Pos                    24U                                            /*!< SCB CTR:CWG位置*/
#define SCB_CTR_CWG_Msk                    (0xFUL << SCB_CTR_CWG_Pos)                     /*!< SCB CTR:CWG面罩*/

#define SCB_CTR_ERG_Pos                    20U                                            /*!< SCB CTR:ERG位置*/
#define SCB_CTR_ERG_Msk                    (0xFUL << SCB_CTR_ERG_Pos)                     /*!< SCB CTR:ERG面罩*/

#define SCB_CTR_DMINLINE_Pos               16U                                            /*!< SCB CTR:DminLine位置*/
#define SCB_CTR_DMINLINE_Msk               (0xFUL << SCB_CTR_DMINLINE_Pos)                /*!< SCB CTR:DminLine掩码*/

#define SCB_CTR_IMINLINE_Pos                0U                                            /*!< SCB CTR:ImInLine位置*/
#define SCB_CTR_IMINLINE_Msk               (0xFUL /*<<SCB_CTR_IMINLINE_Pos*/)            /*!< SCB CTR:ImInLine掩码*/

/* SCB缓存大小ID寄存器定义*/
#define SCB_CCSIDR_WT_Pos                  31U                                            /*!< SCB CCSIDR:WT位置*/
#define SCB_CCSIDR_WT_Msk                  (1UL << SCB_CCSIDR_WT_Pos)                     /*!< SCB CCSIDR:WT掩码*/

#define SCB_CCSIDR_WB_Pos                  30U                                            /*!< SCB CCSIDR:WB位置*/
#define SCB_CCSIDR_WB_Msk                  (1UL << SCB_CCSIDR_WB_Pos)                     /*!< SCB CCSIDR:WB掩码*/

#define SCB_CCSIDR_RA_Pos                  29U                                            /*!< SCB CCSIDR:RA位置*/
#define SCB_CCSIDR_RA_Msk                  (1UL << SCB_CCSIDR_RA_Pos)                     /*!< SCB CCSIDR:RA掩码*/

#define SCB_CCSIDR_WA_Pos                  28U                                            /*!< SCB CCSIDR:WA职位*/
#define SCB_CCSIDR_WA_Msk                  (1UL << SCB_CCSIDR_WA_Pos)                     /*!< SCB CCSIDR:WA掩码*/

#define SCB_CCSIDR_NUMSETS_Pos             13U                                            /*!< SCB CCSIDR:NumSets位置*/
#define SCB_CCSIDR_NUMSETS_Msk             (0x7FFFUL << SCB_CCSIDR_NUMSETS_Pos)           /*!< SCB CCSIDR:NumSets掩码*/

#define SCB_CCSIDR_ASSOCIATIVITY_Pos        3U                                            /*!< SCB CCSIDR：关联性位置*/
#define SCB_CCSIDR_ASSOCIATIVITY_Msk       (0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_Pos)      /*!< SCB CCSIDR：关联性掩码*/

#define SCB_CCSIDR_LINESIZE_Pos             0U                                            /*!< SCB CCSIDR：线宽位置*/
#define SCB_CCSIDR_LINESIZE_Msk            (7UL /*<<SCB_CCSIDR_LINESIZE_Pos*/)           /*!< SCB CCSIDR:LineSize掩码*/

/* SCB缓存大小选择寄存器定义*/
#define SCB_CSSELR_LEVEL_Pos                1U                                            /*!< SCB CSSELR：水平位置*/
#define SCB_CSSELR_LEVEL_Msk               (7UL << SCB_CSSELR_LEVEL_Pos)                  /*!< SCB CSSELR：电平掩码*/

#define SCB_CSSELR_IND_Pos                  0U                                            /*!< SCB CSSELR:InD位置*/
#define SCB_CSSELR_IND_Msk                 (1UL /*<<SCB_CSSELR_IND_Pos*/)                /*!< SCB CSSELR:InD掩模*/

/* SCB软件触发中断寄存器定义*/
#define SCB_STIR_INTID_Pos                  0U                                            /*!< SCB STIR:INTID位置*/
#define SCB_STIR_INTID_Msk                 (0x1FFUL /*<<SCB_STIR_INTID_Pos*/)            /*!< SCB STIR:INTID掩码*/

/* SCB D-缓存通过设置方式寄存器定义无效*/
#define SCB_DCISW_WAY_Pos                  30U                                            /*!< SCB DCISW：通道位置*/
#define SCB_DCISW_WAY_Msk                  (3UL << SCB_DCISW_WAY_Pos)                     /*!< SCB DCISW：路掩码*/

#define SCB_DCISW_SET_Pos                   5U                                            /*!< SCB DCISW：设置位置*/
#define SCB_DCISW_SET_Msk                  (0x1FFUL << SCB_DCISW_SET_Pos)                 /*!< SCB DCISW：设置掩码*/

/* SCB D缓存通过设置方式寄存器定义清除*/
#define SCB_DCCSW_WAY_Pos                  30U                                            /*!< SCB DCCSW：通道位置*/
#define SCB_DCCSW_WAY_Msk                  (3UL << SCB_DCCSW_WAY_Pos)                     /*!< SCB DCCSW：路掩码*/

#define SCB_DCCSW_SET_Pos                   5U                                            /*!< SCB DCCSW：设置位置*/
#define SCB_DCCSW_SET_Msk                  (0x1FFUL << SCB_DCCSW_SET_Pos)                 /*!< SCB DCCSW：设置掩码*/

/* SCB D缓存清除和无效（通过设置方式寄存器定义）*/
#define SCB_DCCISW_WAY_Pos                 30U                                            /*!< SCB DCCISW：方向位置*/
#define SCB_DCCISW_WAY_Msk                 (3UL << SCB_DCCISW_WAY_Pos)                    /*!< SCB DCCISW：路掩码*/

#define SCB_DCCISW_SET_Pos                  5U                                            /*!< SCB DCCISW：设置位置*/
#define SCB_DCCISW_SET_Msk                 (0x1FFUL << SCB_DCCISW_SET_Pos)                /*!< SCB DCCISW：设置掩码*/

/*@}CMSIS_SCB组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_SCnSCB系统控制不在SCB中（SCnSCB）\系统控制和ID寄存器的简要类型定义不在SCC中@{
 */

/**
  \简要结构类型，用于访问不在SCB中的系统控制和ID寄存器。
 */
typedef struct
{
        uint32_t RESERVED0[1U];
  __IM  uint32_t ICTR;                   /*!< 偏移：0x004（R/）中断控制器类型寄存器*/
  __IOM uint32_t ACTLR;                  /*!< 偏移量：0x008（R/W）辅助控制寄存器*/
  __IOM uint32_t CPPWR;                  /*!< 偏移量：0x00C（R/W）协处理器功率控制寄存器*/
} SCnSCB_Type;

/* 中断控制器类型寄存器定义*/
#define SCnSCB_ICTR_INTLINESNUM_Pos         0U                                         /*!< 卢旺达问题国际法庭：内情立场*/
#define SCnSCB_ICTR_INTLINESNUM_Msk        (0xFUL /*<<SCnSCB_ICTR_INTLINESNUM_Pos*/)  /*!< 卢旺达问题国际法庭：INTLINESNUM面具*/

/*@}CMSIS_SCnotSCB组末尾*/


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
  \ingroup CMSIS_core_register\defgroup CMSIS_ITM Instrumentation Trace Macrocell（ITM）\ Instrumentation TraceMacrocell的简要类型定义@{
 */

/**
  \用于访问Instrumentation Trace Macrocell Register（ITM）的简短结构类型。
 */
typedef struct
{
  __OM  union
  {
    __OM  uint8_t    u8;                 /*!< 偏移：0x000（/W）ITM刺激端口8位*/
    __OM  uint16_t   u16;                /*!< 偏移：0x000（/W）ITM刺激端口16位*/
    __OM  uint32_t   u32;                /*!< 偏移：0x000（/W）ITM刺激端口32位*/
  }  PORT [32U];                         /*!< 偏移：0x000（/W）ITM刺激端口寄存器*/
        uint32_t RESERVED0[864U];
  __IOM uint32_t TER;                    /*!< 偏移量：0xE00（R/W）ITM跟踪启用寄存器*/
        uint32_t RESERVED1[15U];
  __IOM uint32_t TPR;                    /*!< 偏移量：0xE40（R/W）ITM跟踪特权寄存器*/
        uint32_t RESERVED2[15U];
  __IOM uint32_t TCR;                    /*!< 偏移量：0xE80（R/W）ITM跟踪控制寄存器*/
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  __OM  uint32_t LAR;                    /*!< 偏移量：0xFB0（/W）ITM锁访问寄存器*/
  __IM  uint32_t LSR;                    /*!< 偏移量：0xFB4（R/）ITM锁定状态寄存器*/
        uint32_t RESERVED5[1U];
  __IM  uint32_t DEVARCH;                /*!< 偏移量：0xFBC（R/）ITM设备架构寄存器*/
        uint32_t RESERVED6[4U];
  __IM  uint32_t PID4;                   /*!< 偏移量：0xFD0（R/）ITM外围设备标识寄存器#4*/
  __IM  uint32_t PID5;                   /*!< 偏移量：0xFD4（R/）ITM外围设备标识寄存器#5*/
  __IM  uint32_t PID6;                   /*!< 偏移量：0xFD8（R/）ITM外围设备标识寄存器#6*/
  __IM  uint32_t PID7;                   /*!< 偏移量：0xFDC（R/）ITM外围设备标识寄存器#7*/
  __IM  uint32_t PID0;                   /*!< 偏移量：0xFE0（R/）ITM外围设备标识寄存器#0*/
  __IM  uint32_t PID1;                   /*!< 偏移量：0xFE4（R/）ITM外围设备标识寄存器#1*/
  __IM  uint32_t PID2;                   /*!< 偏移量：0xFE8（R/）ITM外围设备标识寄存器#2*/
  __IM  uint32_t PID3;                   /*!< 偏移量：0xFEC（R/）ITM外围设备标识寄存器#3*/
  __IM  uint32_t CID0;                   /*!< 偏移量：0xFF0（R/）ITM组件标识寄存器#0*/
  __IM  uint32_t CID1;                   /*!< 偏移量：0xFF4（R/）ITM组件标识寄存器#1*/
  __IM  uint32_t CID2;                   /*!< 偏移量：0xFF8（R/）ITM组件标识寄存器#2*/
  __IM  uint32_t CID3;                   /*!< 偏移量：0xFFC（R/）ITM组件标识寄存器#3*/
} ITM_Type;

/* ITM刺激端口寄存器定义*/
#define ITM_STIM_DISABLED_Pos               1U                                            /*!< ITM STIM：禁用位置*/
#define ITM_STIM_DISABLED_Msk              (0x1UL << ITM_STIM_DISABLED_Pos)               /*!< ITM STIM：禁用掩码*/

#define ITM_STIM_FIFOREADY_Pos              0U                                            /*!< ITM STIM：第五位置*/
#define ITM_STIM_FIFOREADY_Msk             (0x1UL /*<<ITM_STIM_FIFOREADY_Pos*/)          /*!< ITM STIM:FIFOREADY面罩*/

/* ITM跟踪特权寄存器定义*/
#define ITM_TPR_PRIVMASK_Pos                0U                                            /*!< ITM TPR：PRIVMASK位置*/
#define ITM_TPR_PRIVMASK_Msk               (0xFFFFFFFFUL /*<<ITM_TPR_PRIVMASK_Pos*/)     /*!< ITM TPR：PRIVMASK面罩*/

/* ITM跟踪控制寄存器定义*/
#define ITM_TCR_BUSY_Pos                   23U                                            /*!< ITM TCR：繁忙位置*/
#define ITM_TCR_BUSY_Msk                   (1UL << ITM_TCR_BUSY_Pos)                      /*!< ITM TCR:BUSY掩码*/

#define ITM_TCR_TRACEBUSID_Pos             16U                                            /*!< ITM TCR:ATBID位置*/
#define ITM_TCR_TRACEBUSID_Msk             (0x7FUL << ITM_TCR_TRACEBUSID_Pos)             /*!< ITM TCR:ATBID掩码*/

#define ITM_TCR_GTSFREQ_Pos                10U                                            /*!< ITM TCR：全局时间戳频率位置*/
#define ITM_TCR_GTSFREQ_Msk                (3UL << ITM_TCR_GTSFREQ_Pos)                   /*!< ITM TCR：全局时间戳频率掩码*/

#define ITM_TCR_TSPRESCALE_Pos              8U                                            /*!< ITM TCR：TSPRESCALE位置*/
#define ITM_TCR_TSPRESCALE_Msk             (3UL << ITM_TCR_TSPRESCALE_Pos)                /*!< ITM TCR：TSPRESCALE面罩*/

#define ITM_TCR_STALLENA_Pos                5U                                            /*!< ITM TCR：失速位置*/
#define ITM_TCR_STALLENA_Msk               (1UL << ITM_TCR_STALLENA_Pos)                  /*!< ITM TCR：STALLENA面罩*/

#define ITM_TCR_SWOENA_Pos                  4U                                            /*!< ITM TCR：SWOENA位置*/
#define ITM_TCR_SWOENA_Msk                 (1UL << ITM_TCR_SWOENA_Pos)                    /*!< ITM TCR：SWOENA面罩*/

#define ITM_TCR_DWTENA_Pos                  3U                                            /*!< ITM TCR：DWTENA位置*/
#define ITM_TCR_DWTENA_Msk                 (1UL << ITM_TCR_DWTENA_Pos)                    /*!< ITM TCR：DWTENA面罩*/

#define ITM_TCR_SYNCENA_Pos                 2U                                            /*!< ITM TCR：同步位置*/
#define ITM_TCR_SYNCENA_Msk                (1UL << ITM_TCR_SYNCENA_Pos)                   /*!< ITM TCR：SYNCENA掩码*/

#define ITM_TCR_TSENA_Pos                   1U                                            /*!< ITM TCR：TSENA位置*/
#define ITM_TCR_TSENA_Msk                  (1UL << ITM_TCR_TSENA_Pos)                     /*!< ITM TCR：TSENA面罩*/

#define ITM_TCR_ITMENA_Pos                  0U                                            /*!< ITM TCR：ITM启用位位置*/
#define ITM_TCR_ITMENA_Msk                 (1UL /*<<ITM_TCR_ITMENA_Pos*/)                /*!< ITM TCR：ITM启用位掩码*/

/* ITM锁状态寄存器定义*/
#define ITM_LSR_ByteAcc_Pos                 2U                                            /*!< ITM LSR:ByteAcc位置*/
#define ITM_LSR_ByteAcc_Msk                (1UL << ITM_LSR_ByteAcc_Pos)                   /*!< ITM LSR:ByteAcc掩码*/

#define ITM_LSR_Access_Pos                  1U                                            /*!< ITM LSR：访问位置*/
#define ITM_LSR_Access_Msk                 (1UL << ITM_LSR_Access_Pos)                    /*!< ITM LSR：访问掩码*/

#define ITM_LSR_Present_Pos                 0U                                            /*!< ITM LSR：当前位置*/
#define ITM_LSR_Present_Msk                (1UL /*<<ITM_LSR_Present_Pos*/)               /*!< ITM LSR：当前掩码*/

/*@}*/ /* CMSIS_ITM组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_DWT数据监视点和跟踪（DWT）\数据监视点与跟踪（DW）的简要类型定义@{
 */

/**
  \访问数据监视点和跟踪寄存器（DWT）的简短结构类型。
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< 偏移量：0x000（R/W）控制寄存器*/
  __IOM uint32_t CYCCNT;                 /*!< 偏移：0x004（R/W）循环计数寄存器*/
  __IOM uint32_t CPICNT;                 /*!< 偏移量：0x008（R/W）CPI计数寄存器*/
  __IOM uint32_t EXCCNT;                 /*!< 偏移量：0x00C（R/W）异常开销计数寄存器*/
  __IOM uint32_t SLEEPCNT;               /*!< 偏移量：0x010（R/W）睡眠计数寄存器*/
  __IOM uint32_t LSUCNT;                 /*!< 偏移量：0x014（R/W）LSU计数寄存器*/
  __IOM uint32_t FOLDCNT;                /*!< 偏移量：0x018（R/W）折叠指令计数寄存器*/
  __IM  uint32_t PCSR;                   /*!< 偏移量：0x01C（R/）程序计数器采样寄存器*/
  __IOM uint32_t COMP0;                  /*!< 偏移量：0x020（R/W）比较器寄存器0*/
        uint32_t RESERVED1[1U];
  __IOM uint32_t FUNCTION0;              /*!< 偏移量：0x028（R/W）功能寄存器0*/
        uint32_t RESERVED2[1U];
  __IOM uint32_t COMP1;                  /*!< 偏移量：0x030（R/W）比较器寄存器1*/
        uint32_t RESERVED3[1U];
  __IOM uint32_t FUNCTION1;              /*!< 偏移量：0x038（R/W）功能寄存器1*/
        uint32_t RESERVED4[1U];
  __IOM uint32_t COMP2;                  /*!< 偏移量：0x040（R/W）比较器寄存器2*/
        uint32_t RESERVED5[1U];
  __IOM uint32_t FUNCTION2;              /*!< 偏移量：0x048（R/W）功能寄存器2*/
        uint32_t RESERVED6[1U];
  __IOM uint32_t COMP3;                  /*!< 偏移量：0x050（R/W）比较器寄存器3*/
        uint32_t RESERVED7[1U];
  __IOM uint32_t FUNCTION3;              /*!< 偏移量：0x058（R/W）功能寄存器3*/
        uint32_t RESERVED8[1U];
  __IOM uint32_t COMP4;                  /*!< 偏移量：0x060（R/W）比较器寄存器4*/
        uint32_t RESERVED9[1U];
  __IOM uint32_t FUNCTION4;              /*!< 偏移量：0x068（R/W）功能寄存器4*/
        uint32_t RESERVED10[1U];
  __IOM uint32_t COMP5;                  /*!< 偏移量：0x070（R/W）比较器寄存器5*/
        uint32_t RESERVED11[1U];
  __IOM uint32_t FUNCTION5;              /*!< 偏移量：0x078（R/W）功能寄存器5*/
        uint32_t RESERVED12[1U];
  __IOM uint32_t COMP6;                  /*!< 偏移量：0x080（R/W）比较器寄存器6*/
        uint32_t RESERVED13[1U];
  __IOM uint32_t FUNCTION6;              /*!< 偏移量：0x088（R/W）功能寄存器6*/
        uint32_t RESERVED14[1U];
  __IOM uint32_t COMP7;                  /*!< 偏移量：0x090（R/W）比较器寄存器7*/
        uint32_t RESERVED15[1U];
  __IOM uint32_t FUNCTION7;              /*!< 偏移量：0x098（R/W）功能寄存器7*/
        uint32_t RESERVED16[1U];
  __IOM uint32_t COMP8;                  /*!< 偏移量：0x0A0（R/W）比较器寄存器8*/
        uint32_t RESERVED17[1U];
  __IOM uint32_t FUNCTION8;              /*!< 偏移量：0x0A8（R/W）功能寄存器8*/
        uint32_t RESERVED18[1U];
  __IOM uint32_t COMP9;                  /*!< 偏移量：0x0B0（R/W）比较器寄存器9*/
        uint32_t RESERVED19[1U];
  __IOM uint32_t FUNCTION9;              /*!< 偏移量：0x0B8（R/W）功能寄存器9*/
        uint32_t RESERVED20[1U];
  __IOM uint32_t COMP10;                 /*!< 偏移量：0x0C0（R/W）比较器寄存器10*/
        uint32_t RESERVED21[1U];
  __IOM uint32_t FUNCTION10;             /*!< 偏移量：0x0C8（R/W）功能寄存器10*/
        uint32_t RESERVED22[1U];
  __IOM uint32_t COMP11;                 /*!< 偏移量：0x0D0（R/W）比较器寄存器11*/
        uint32_t RESERVED23[1U];
  __IOM uint32_t FUNCTION11;             /*!< 偏移量：0x0D8（R/W）功能寄存器11*/
        uint32_t RESERVED24[1U];
  __IOM uint32_t COMP12;                 /*!< 偏移量：0x0E0（R/W）比较器寄存器12*/
        uint32_t RESERVED25[1U];
  __IOM uint32_t FUNCTION12;             /*!< 偏移量：0x0E8（R/W）功能寄存器12*/
        uint32_t RESERVED26[1U];
  __IOM uint32_t COMP13;                 /*!< 偏移量：0x0F0（R/W）比较器寄存器13*/
        uint32_t RESERVED27[1U];
  __IOM uint32_t FUNCTION13;             /*!< 偏移量：0x0F8（R/W）功能寄存器13*/
        uint32_t RESERVED28[1U];
  __IOM uint32_t COMP14;                 /*!< 偏移量：0x100（R/W）比较器寄存器14*/
        uint32_t RESERVED29[1U];
  __IOM uint32_t FUNCTION14;             /*!< 偏移量：0x108（R/W）功能寄存器14*/
        uint32_t RESERVED30[1U];
  __IOM uint32_t COMP15;                 /*!< 偏移量：0x110（R/W）比较器寄存器15*/
        uint32_t RESERVED31[1U];
  __IOM uint32_t FUNCTION15;             /*!< 偏移量：0x118（R/W）功能寄存器15*/
        uint32_t RESERVED32[934U];
  __IM  uint32_t LSR;                    /*!< 偏移量：0xFB4（R）锁定状态寄存器*/
        uint32_t RESERVED33[1U];
  __IM  uint32_t DEVARCH;                /*!< 偏移量：0xFBC（R/）设备架构寄存器*/
} DWT_Type;

/* DWT控制寄存器定义*/
#define DWT_CTRL_NUMCOMP_Pos               28U                                         /*!< DWT CTRL：NUMCOMP位置*/
#define DWT_CTRL_NUMCOMP_Msk               (0xFUL << DWT_CTRL_NUMCOMP_Pos)             /*!< DWT CTRL:NUMCOMP掩码*/

#define DWT_CTRL_NOTRCPKT_Pos              27U                                         /*!< DWT CTRL：NOTRCPKT位置*/
#define DWT_CTRL_NOTRCPKT_Msk              (0x1UL << DWT_CTRL_NOTRCPKT_Pos)            /*!< DWT CTRL：NOTRCPKT掩码*/

#define DWT_CTRL_NOEXTTRIG_Pos             26U                                         /*!< DWT CTRL：NOEXTTRIG位置*/
#define DWT_CTRL_NOEXTTRIG_Msk             (0x1UL << DWT_CTRL_NOEXTTRIG_Pos)           /*!< DWT CTRL:NOEXTTRIG掩码*/

#define DWT_CTRL_NOCYCCNT_Pos              25U                                         /*!< DWT CTRL:NOCYCCNT位置*/
#define DWT_CTRL_NOCYCCNT_Msk              (0x1UL << DWT_CTRL_NOCYCCNT_Pos)            /*!< DWT CTRL:NOCYCCNT掩码*/

#define DWT_CTRL_NOPRFCNT_Pos              24U                                         /*!< DWT CTRL:NOPRFCNT位置*/
#define DWT_CTRL_NOPRFCNT_Msk              (0x1UL << DWT_CTRL_NOPRFCNT_Pos)            /*!< DWT CTRL:NOPRFCNT掩码*/

#define DWT_CTRL_CYCDISS_Pos               23U                                         /*!< DWT CTRL：CYCDISS位置*/
#define DWT_CTRL_CYCDISS_Msk               (0x1UL << DWT_CTRL_CYCDISS_Pos)             /*!< DWT CTRL：CYCDISS掩码*/

#define DWT_CTRL_CYCEVTENA_Pos             22U                                         /*!< DWT CTRL：CYCEVTENA位置*/
#define DWT_CTRL_CYCEVTENA_Msk             (0x1UL << DWT_CTRL_CYCEVTENA_Pos)           /*!< DWT CTRL:CYCCEVTENA掩码*/

#define DWT_CTRL_FOLDEVTENA_Pos            21U                                         /*!< DWT CTRL：FOLDVETENA位置*/
#define DWT_CTRL_FOLDEVTENA_Msk            (0x1UL << DWT_CTRL_FOLDEVTENA_Pos)          /*!< DWT CTRL：FOLDVETENA掩码*/

#define DWT_CTRL_LSUEVTENA_Pos             20U                                         /*!< DWT CTRL：LSUEVTENA位置*/
#define DWT_CTRL_LSUEVTENA_Msk             (0x1UL << DWT_CTRL_LSUEVTENA_Pos)           /*!< DWT CTRL:LSUEVTENA掩码*/

#define DWT_CTRL_SLEEPEVTENA_Pos           19U                                         /*!< DWT CTRL：SLEEPEVENA位置*/
#define DWT_CTRL_SLEEPEVTENA_Msk           (0x1UL << DWT_CTRL_SLEEPEVTENA_Pos)         /*!< DWT CTRL：SLEEPEVENA掩码*/

#define DWT_CTRL_EXCEVTENA_Pos             18U                                         /*!< DWT CTRL：EXCEVTENA位置*/
#define DWT_CTRL_EXCEVTENA_Msk             (0x1UL << DWT_CTRL_EXCEVTENA_Pos)           /*!< DWT CTRL:EXCEVTENA掩码*/

#define DWT_CTRL_CPIEVTENA_Pos             17U                                         /*!< DWT CTRL:CPIVETENA位置*/
#define DWT_CTRL_CPIEVTENA_Msk             (0x1UL << DWT_CTRL_CPIEVTENA_Pos)           /*!< DWT CTRL:CPIVETENA掩码*/

#define DWT_CTRL_EXCTRCENA_Pos             16U                                         /*!< DWT CTRL：EXCTRCENA位置*/
#define DWT_CTRL_EXCTRCENA_Msk             (0x1UL << DWT_CTRL_EXCTRCENA_Pos)           /*!< DWT CTRL:EXCTRCENA掩码*/

#define DWT_CTRL_PCSAMPLENA_Pos            12U                                         /*!< DWT CTRL：PCSAMPLENA位置*/
#define DWT_CTRL_PCSAMPLENA_Msk            (0x1UL << DWT_CTRL_PCSAMPLENA_Pos)          /*!< DWT CTRL：PCSAMPLENA掩码*/

#define DWT_CTRL_SYNCTAP_Pos               10U                                         /*!< DWT CTRL：同步位置*/
#define DWT_CTRL_SYNCTAP_Msk               (0x3UL << DWT_CTRL_SYNCTAP_Pos)             /*!< DWT CTRL：SYNCTAP掩码*/

#define DWT_CTRL_CYCTAP_Pos                 9U                                         /*!< DWT CTRL：CYCTAP位置*/
#define DWT_CTRL_CYCTAP_Msk                (0x1UL << DWT_CTRL_CYCTAP_Pos)              /*!< DWT CTRL：CYCTAP掩码*/

#define DWT_CTRL_POSTINIT_Pos               5U                                         /*!< DWT CTRL：后初始化位置*/
#define DWT_CTRL_POSTINIT_Msk              (0xFUL << DWT_CTRL_POSTINIT_Pos)            /*!< DWT CTRL:POSINIT掩码*/

#define DWT_CTRL_POSTPRESET_Pos             1U                                         /*!< DWT CTRL：后预设位置*/
#define DWT_CTRL_POSTPRESET_Msk            (0xFUL << DWT_CTRL_POSTPRESET_Pos)          /*!< DWT CTRL:POSTPPRESET掩码*/

#define DWT_CTRL_CYCCNTENA_Pos              0U                                         /*!< DWT CTRL：CYCCNTENA位置*/
#define DWT_CTRL_CYCCNTENA_Msk             (0x1UL /*<<DWT_CTRL_CYCCNTENA_波斯*/)       /*!< DWT CTRL：CYCCNTENA掩码*/

/* DWT CPI计数寄存器定义*/
#define DWT_CPICNT_CPICNT_Pos               0U                                         /*!< DWT CPICNT：CPICNT位置*/
#define DWT_CPICNT_CPICNT_Msk              (0xFFUL /*<<DWT_CPICNT_CPICNT_Pos*/)       /*!< DWT CPICNT：CPICNT掩码*/

/* DWT异常开销计数寄存器定义*/
#define DWT_EXCCNT_EXCCNT_Pos               0U                                         /*!< DWT EXCCNT:EXCCNT位置*/
#define DWT_EXCCNT_EXCCNT_Msk              (0xFFUL /*<<DWT_EXCCNT_EXCCNT_Pos*/)       /*!< DWT EXCCNT:EXCCNT掩码*/

/* DWT休眠计数寄存器定义*/
#define DWT_SLEEPCNT_SLEEPCNT_Pos           0U                                         /*!< DWT SLEEPNT:SLEEPNT位置*/
#define DWT_SLEEPCNT_SLEEPCNT_Msk          (0xFFUL /*<<DWT_SLEEPCNT_SLEEPCNT_Pos*/)   /*!< DWT SLEEPNT:SLEEPNT掩码*/

/* DWT LSU计数寄存器定义*/
#define DWT_LSUCNT_LSUCNT_Pos               0U                                         /*!< DWT LSUCNT：LSUCNT位置*/
#define DWT_LSUCNT_LSUCNT_Msk              (0xFFUL /*<<DWT_LSUCNT_LSUCNT_Pos*/)       /*!< DWT LSUCNT:LSUCNT掩码*/

/* DWT折叠指令计数寄存器定义*/
#define DWT_FOLDCNT_FOLDCNT_Pos             0U                                         /*!< DWT折叠：折叠位置*/
#define DWT_FOLDCNT_FOLDCNT_Msk            (0xFFUL /*<<DWT_FOLDCNT_FOLDCNT_Pos*/)     /*!< DWT FOLDCNT:FOLDCNT掩码*/

/* DWT比较器功能寄存器定义*/
#define DWT_FUNCTION_ID_Pos                27U                                         /*!< DWT功能：ID位置*/
#define DWT_FUNCTION_ID_Msk                (0x1FUL << DWT_FUNCTION_ID_Pos)             /*!< DWT功能：ID掩码*/

#define DWT_FUNCTION_MATCHED_Pos           24U                                         /*!< DWT功能：匹配位置*/
#define DWT_FUNCTION_MATCHED_Msk           (0x1UL << DWT_FUNCTION_MATCHED_Pos)         /*!< DWT函数：匹配掩码*/

#define DWT_FUNCTION_DATAVSIZE_Pos         10U                                         /*!< DWT功能：数据大小位置*/
#define DWT_FUNCTION_DATAVSIZE_Msk         (0x3UL << DWT_FUNCTION_DATAVSIZE_Pos)       /*!< DWT函数：DATAVSIZE掩码*/

#define DWT_FUNCTION_ACTION_Pos             4U                                         /*!< DWT功能：动作位置*/
#define DWT_FUNCTION_ACTION_Msk            (0x1UL << DWT_FUNCTION_ACTION_Pos)          /*!< DWT FUNCTION:动作掩码*/

#define DWT_FUNCTION_MATCH_Pos              0U                                         /*!< DWT功能：匹配位置*/
#define DWT_FUNCTION_MATCH_Msk             (0xFUL /*<<DWT_FUNCTION_MATCH_Pos*/)       /*!< DWT函数：匹配掩码*/

/*@}*/ /* CMSIS_DWT组末尾*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_TPI跟踪端口接口（TPI）\跟踪端口接口的简要类型定义@{
 */

/**
  \访问跟踪端口接口寄存器（TPI）的简要结构类型。
 */
typedef struct
{
  __IM  uint32_t SSPSR;                  /*!< 偏移量：0x000（R/）支持的并行端口大小寄存器*/
  __IOM uint32_t CSPSR;                  /*!< 偏移量：0x004（R/W）当前并行端口大小寄存器*/
        uint32_t RESERVED0[2U];
  __IOM uint32_t ACPR;                   /*!< 偏移量：0x010（R/W）异步时钟预分频器寄存器*/
        uint32_t RESERVED1[55U];
  __IOM uint32_t SPPR;                   /*!< 偏移：0x0F0（R/W）所选引脚协议寄存器*/
        uint32_t RESERVED2[131U];
  __IM  uint32_t FFSR;                   /*!< 偏移量：0x300（R/）格式化程序和刷新状态寄存器*/
  __IOM uint32_t FFCR;                   /*!< 偏移量：0x304（R/W）格式化程序和刷新控制寄存器*/
  __IOM uint32_t PSCR;                   /*!< 偏移量：0x308（R/W）周期同步控制寄存器*/
        uint32_t RESERVED3[759U];
  __IM  uint32_t TRIGGER;                /*!< 偏移量：0xEE8（R/）TRIGGER寄存器*/
  __IM  uint32_t ITFTTD0;                /*!< 偏移量：0xEEC（R/）集成测试FIFO测试数据0寄存器*/
  __IOM uint32_t ITATBCTR2;              /*!< 偏移量：0xEF0（R/W）集成测试ATB控制寄存器2*/
        uint32_t RESERVED4[1U];
  __IM  uint32_t ITATBCTR0;              /*!< 偏移量：0xEF8（R/）集成测试ATB控制寄存器0*/
  __IM  uint32_t ITFTTD1;                /*!< 偏移量：0xEFC（R/）集成测试FIFO测试数据1寄存器*/
  __IOM uint32_t ITCTRL;                 /*!< 偏移：0xF00（R/W）集成模式控制*/
        uint32_t RESERVED5[39U];
  __IOM uint32_t CLAIMSET;               /*!< 偏移量：0xFA0（R/W）声明标记集*/
  __IOM uint32_t CLAIMCLR;               /*!< 偏移量：0xFA4（R/W）索赔标记清除*/
        uint32_t RESERVED7[8U];
  __IM  uint32_t DEVID;                  /*!< 偏移量：0xFC8（R/）设备配置寄存器*/
  __IM  uint32_t DEVTYPE;                /*!< 偏移量：0xFCC（R/）设备类型标识符寄存器*/
} TPI_Type;

/* TPI异步时钟预分频器寄存器定义*/
#define TPI_ACPR_PRESCALER_Pos              0U                                         /*!< TPI ACPR：预校准位置*/
#define TPI_ACPR_PRESCALER_Msk             (0x1FFFUL /*<<TPI_ACPR_PRESCALER_Pos*/)    /*!< TPI ACPR：PRESCALER面罩*/

/* TPI所选引脚协议寄存器定义*/
#define TPI_SPPR_TXMODE_Pos                 0U                                         /*!< TPI SPPR:TXMODE位置*/
#define TPI_SPPR_TXMODE_Msk                (0x3UL /*<<TPI_SPPR_TXMODE_Pos*/)          /*!< TPI SPPR:TXMODE掩码*/

/* TPI格式化程序和刷新状态寄存器定义*/
#define TPI_FFSR_FtNonStop_Pos              3U                                         /*!< TPI FFSR:ft非停止位置*/
#define TPI_FFSR_FtNonStop_Msk             (0x1UL << TPI_FFSR_FtNonStop_Pos)           /*!< TPI FFSR:FtNonStop掩码*/

#define TPI_FFSR_TCPresent_Pos              2U                                         /*!< TPI FFSR:TC当前位置*/
#define TPI_FFSR_TCPresent_Msk             (0x1UL << TPI_FFSR_TCPresent_Pos)           /*!< TPI FFSR：TCPresent掩码*/

#define TPI_FFSR_FtStopped_Pos              1U                                         /*!< TPI FFSR：F停止位置*/
#define TPI_FFSR_FtStopped_Msk             (0x1UL << TPI_FFSR_FtStopped_Pos)           /*!< TPI FFSR:ft停止面罩*/

#define TPI_FFSR_FlInProg_Pos               0U                                         /*!< TPI FFSR:FlInProg位置*/
#define TPI_FFSR_FlInProg_Msk              (0x1UL /*<<TPI_FFSR_FlInProg_Pos*/)        /*!< TPI FFSR:FlInProg掩码*/

/* TPI格式化程序和刷新控制寄存器定义*/
#define TPI_FFCR_TrigIn_Pos                 8U                                         /*!< TPI FFCR：触发位置*/
#define TPI_FFCR_TrigIn_Msk                (0x1UL << TPI_FFCR_TrigIn_Pos)              /*!< TPI FFCR：TrigIn掩码*/

#define TPI_FFCR_FOnMan_Pos                 6U                                         /*!< TPI FFCR:FOnMan位置*/
#define TPI_FFCR_FOnMan_Msk                (0x1UL << TPI_FFCR_FOnMan_Pos)              /*!< TPI FFCR:FOnMan面罩*/

#define TPI_FFCR_EnFCont_Pos                1U                                         /*!< TPI FFCR:EnFCont位置*/
#define TPI_FFCR_EnFCont_Msk               (0x1UL << TPI_FFCR_EnFCont_Pos)             /*!< TPI FFCR:EnFCont面罩*/

/* TPI触发器寄存器定义*/
#define TPI_TRIGGER_TRIGGER_Pos             0U                                         /*!< TPI触发器：触发器位置*/
#define TPI_TRIGGER_TRIGGER_Msk            (0x1UL /*<<TPI_TRIGGER_TRIGGER_Pos*/)      /*!< TPI触发器：触发器掩码*/

/* TPI集成测试FIFO测试数据0寄存器定义*/
#define TPI_ITFTTD0_ATB_IF2_ATVALID_Pos    29U                                         /*!< TPI ITFTTD0:ATB接口2 ATVALID位置*/
#define TPI_ITFTTD0_ATB_IF2_ATVALID_Msk    (0x3UL << TPI_ITFTTD0_ATB_IF2_ATVALID_Pos)  /*!< TPI ITFTTD0:ATB接口2 ATVALID掩码*/

#define TPI_ITFTTD0_ATB_IF2_bytecount_Pos  27U                                         /*!< TPI ITFTTD0:ATB接口2字节计数位置*/
#define TPI_ITFTTD0_ATB_IF2_bytecount_Msk  (0x3UL << TPI_ITFTTD0_ATB_IF2_bytecount_Pos) /*!< TPI ITFTTD0:ATB接口2字节计数掩码*/

#define TPI_ITFTTD0_ATB_IF1_ATVALID_Pos    26U                                         /*!< TPI ITFTTD0:ATB接口1 ATVALID位置*/
#define TPI_ITFTTD0_ATB_IF1_ATVALID_Msk    (0x3UL << TPI_ITFTTD0_ATB_IF1_ATVALID_Pos)  /*!< TPI ITFTTD0:ATB接口1 ATVALID掩码*/

#define TPI_ITFTTD0_ATB_IF1_bytecount_Pos  24U                                         /*!< TPI ITFTTD0:ATB接口1字节计数位置*/
#define TPI_ITFTTD0_ATB_IF1_bytecount_Msk  (0x3UL << TPI_ITFTTD0_ATB_IF1_bytecount_Pos) /*!< TPI ITFTTD0:ATB接口1字节计数掩码*/

#define TPI_ITFTTD0_ATB_IF1_data2_Pos      16U                                         /*!< TPI ITFTTD0:ATB接口1数据2位置*/
#define TPI_ITFTTD0_ATB_IF1_data2_Msk      (0xFFUL << TPI_ITFTTD0_ATB_IF1_data1_Pos)   /*!< TPI ITFTTD0:ATB接口1数据2掩码*/

#define TPI_ITFTTD0_ATB_IF1_data1_Pos       8U                                         /*!< TPI ITFTTD0:ATB接口1数据1位置*/
#define TPI_ITFTTD0_ATB_IF1_data1_Msk      (0xFFUL << TPI_ITFTTD0_ATB_IF1_data1_Pos)   /*!< TPI ITFTTD0:ATB接口1数据1掩码*/

#define TPI_ITFTTD0_ATB_IF1_data0_Pos       0U                                          /*!< TPI ITFTTD0:ATB接口1数据0位置*/
#define TPI_ITFTTD0_ATB_IF1_data0_Msk      (0xFFUL /*<<TPI_ITFTTD0_ATB_IF1_data0_Pos*/) /*!< TPI ITFTTD0:ATB接口1数据0掩码*/

/* TPI集成测试ATB控制寄存器2寄存器定义*/
#define TPI_ITATBCTR2_AFVALID2S_Pos         1U                                         /*!< TPI ITATBCTR2:AFVALID2S位置*/
#define TPI_ITATBCTR2_AFVALID2S_Msk        (0x1UL << TPI_ITATBCTR2_AFVALID2S_Pos)      /*!< TPI ITATBCTR2:AFVALID2SS掩码*/

#define TPI_ITATBCTR2_AFVALID1S_Pos         1U                                         /*!< TPI ITATBCTR2:AFVALID1S位置*/
#define TPI_ITATBCTR2_AFVALID1S_Msk        (0x1UL << TPI_ITATBCTR2_AFVALID1S_Pos)      /*!< TPI ITATBCTR2:AFVALID1SS掩码*/

#define TPI_ITATBCTR2_ATREADY2S_Pos         0U                                         /*!< TPI ITATBCTR2:ATREADY2S位置*/
#define TPI_ITATBCTR2_ATREADY2S_Msk        (0x1UL /*<<TPI_ITATBCTR2_ATREADY2S_Pos*/)  /*!< TPI ITATBCTR2:ATREADY2S面膜*/

#define TPI_ITATBCTR2_ATREADY1S_Pos         0U                                         /*!< TPI ITATBCTR2:ATREADY1S位置*/
#define TPI_ITATBCTR2_ATREADY1S_Msk        (0x1UL /*<<TPI_ITATBCTR2_ATREADY1S_Pos*/)  /*!< TPI ITATBCTR2:ATREADY1S面膜*/

/* TPI集成测试FIFO测试数据1寄存器定义*/
#define TPI_ITFTTD1_ATB_IF2_ATVALID_Pos    29U                                         /*!< TPI ITFTTD1:ATB接口2 ATVALID位置*/
#define TPI_ITFTTD1_ATB_IF2_ATVALID_Msk    (0x3UL << TPI_ITFTTD1_ATB_IF2_ATVALID_Pos)  /*!< TPI ITFTTD1:ATB接口2 ATVALID掩码*/

#define TPI_ITFTTD1_ATB_IF2_bytecount_Pos  27U                                         /*!< TPI ITFTTD1:ATB接口2字节计数位置*/
#define TPI_ITFTTD1_ATB_IF2_bytecount_Msk  (0x3UL << TPI_ITFTTD1_ATB_IF2_bytecount_Pos) /*!< TPI ITFTTD1:ATB接口2字节计数掩码*/

#define TPI_ITFTTD1_ATB_IF1_ATVALID_Pos    26U                                         /*!< TPI ITFTTD1:ATB接口1 ATVALID位置*/
#define TPI_ITFTTD1_ATB_IF1_ATVALID_Msk    (0x3UL << TPI_ITFTTD1_ATB_IF1_ATVALID_Pos)  /*!< TPI ITFTTD1:ATB接口1 ATVALID掩码*/

#define TPI_ITFTTD1_ATB_IF1_bytecount_Pos  24U                                         /*!< TPI ITFTTD1:ATB接口1字节计数位置*/
#define TPI_ITFTTD1_ATB_IF1_bytecount_Msk  (0x3UL << TPI_ITFTTD1_ATB_IF1_bytecount_Pos) /*!< TPI ITFTTD1:ATB接口1字节计数掩码*/

#define TPI_ITFTTD1_ATB_IF2_data2_Pos      16U                                         /*!< TPI ITFTTD1:ATB接口2数据2位置*/
#define TPI_ITFTTD1_ATB_IF2_data2_Msk      (0xFFUL << TPI_ITFTTD1_ATB_IF2_data1_Pos)   /*!< TPI ITFTTD1:ATB接口2数据2掩码*/

#define TPI_ITFTTD1_ATB_IF2_data1_Pos       8U                                         /*!< TPI ITFTTD1:ATB接口2数据1位置*/
#define TPI_ITFTTD1_ATB_IF2_data1_Msk      (0xFFUL << TPI_ITFTTD1_ATB_IF2_data1_Pos)   /*!< TPI ITFTTD1:ATB接口2数据1掩码*/

#define TPI_ITFTTD1_ATB_IF2_data0_Pos       0U                                          /*!< TPI ITFTTD1:ATB接口2数据0位置*/
#define TPI_ITFTTD1_ATB_IF2_data0_Msk      (0xFFUL /*<<TPI_ITFTTD1_ATB_IF2_data0_Pos*/) /*!< TPI ITFTTD1:ATB接口2数据0掩码*/

/* TPI集成测试ATB控制寄存器0定义*/
#define TPI_ITATBCTR0_AFVALID2S_Pos         1U                                         /*!< TPI ITATBCTR0:AFVALID2S位置*/
#define TPI_ITATBCTR0_AFVALID2S_Msk        (0x1UL << TPI_ITATBCTR0_AFVALID2S_Pos)      /*!< TPI ITATBCTR0:AFVALID2SS掩码*/

#define TPI_ITATBCTR0_AFVALID1S_Pos         1U                                         /*!< TPI ITATBCTR0:AFVALID1S位置*/
#define TPI_ITATBCTR0_AFVALID1S_Msk        (0x1UL << TPI_ITATBCTR0_AFVALID1S_Pos)      /*!< TPI ITATBCTR0:AFVALID1SS掩码*/

#define TPI_ITATBCTR0_ATREADY2S_Pos         0U                                         /*!< TPI ITATBCTR0:ATREADY2S位置*/
#define TPI_ITATBCTR0_ATREADY2S_Msk        (0x1UL /*<<TPI_ITATBCTR0_ATREADY2S_Pos*/)  /*!< TPI ITATBCTR0:ATREADY2S面膜*/

#define TPI_ITATBCTR0_ATREADY1S_Pos         0U                                         /*!< TPI ITATBCTR0:ATREADY1S位置*/
#define TPI_ITATBCTR0_ATREADY1S_Msk        (0x1UL /*<<TPI_ITATBCTR0_ATREADY1S_Pos*/)  /*!< TPI ITATBCTR0:ATREADY1S面膜*/

/* TPI集成模式控制寄存器定义*/
#define TPI_ITCTRL_Mode_Pos                 0U                                         /*!< TPI ITCTRL:模式位置*/
#define TPI_ITCTRL_Mode_Msk                (0x3UL /*<<TPI_ITCTRL_Mode_Pos*/)          /*!< TPI ITCTRL:模式掩码*/

/* TPI DEVID寄存器定义*/
#define TPI_DEVID_NRZVALID_Pos             11U                                         /*!< TPI DEVID:NRZVALID位置*/
#define TPI_DEVID_NRZVALID_Msk             (0x1UL << TPI_DEVID_NRZVALID_Pos)           /*!< TPI DEVID:NRZVALID掩码*/

#define TPI_DEVID_MANCVALID_Pos            10U                                         /*!< TPI DEVID:MANCVALID位置*/
#define TPI_DEVID_MANCVALID_Msk            (0x1UL << TPI_DEVID_MANCVALID_Pos)          /*!< TPI DEVID:MANCVALID掩码*/

#define TPI_DEVID_PTINVALID_Pos             9U                                         /*!< TPI DEVID:PTINVALID位置*/
#define TPI_DEVID_PTINVALID_Msk            (0x1UL << TPI_DEVID_PTINVALID_Pos)          /*!< TPI DEVID:PTINVALID掩码*/

#define TPI_DEVID_FIFOSZ_Pos                6U                                         /*!< TPI DEVID:FIFOSZ位置*/
#define TPI_DEVID_FIFOSZ_Msk               (0x7UL << TPI_DEVID_FIFOSZ_Pos)             /*!< TPI DEVID:FIFOSZ面罩*/

#define TPI_DEVID_NrTraceInput_Pos          0U                                         /*!< TPI DEVID:NrTraceInput位置*/
#define TPI_DEVID_NrTraceInput_Msk         (0x3FUL /*<<TPI_DEVID_NrTraceInput_Pos*/)  /*!< TPI DEVID:NrTraceInput掩码*/

/* TPI DEVTYPE寄存器定义*/
#define TPI_DEVTYPE_SubType_Pos             4U                                         /*!< TPI DEVTYPE：子类型位置*/
#define TPI_DEVTYPE_SubType_Msk            (0xFUL /*<<TPI_DEVTYPE_SubType_Pos*/)      /*!< TPI DEVTYPE：子类型掩码*/

#define TPI_DEVTYPE_MajorType_Pos           0U                                         /*!< TPI DEVTYPE：主要类型职位*/
#define TPI_DEVTYPE_MajorType_Msk          (0xFUL << TPI_DEVTYPE_MajorType_Pos)        /*!< TPI DEVTYPE：主要类型掩码*/

/*@}*/ /* CMSIS_TPI组结束*/


#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
/**
  \inggroup CMSIS_core_register\defgroup CMSIS_MPU内存保护单元（MPU）\内存保护单元的简要类型定义@{
 */

/**
  \访问内存保护单元（MPU）的简要结构类型。
 */
typedef struct
{
  __IM  uint32_t TYPE;                   /*!< 偏移量：0x000（R/）MPU类型寄存器*/
  __IOM uint32_t CTRL;                   /*!< 偏移量：0x004（R/W）MPU控制寄存器*/
  __IOM uint32_t RNR;                    /*!< 偏移量：0x008（R/W）MPU区域编号寄存器*/
  __IOM uint32_t RBAR;                   /*!< 偏移量：0x00C（R/W）MPU区域基址寄存器*/
  __IOM uint32_t RLAR;                   /*!< 偏移量：0x010（R/W）MPU区域限制地址寄存器*/
  __IOM uint32_t RBAR_A1;                /*!< 偏移量：0x014（R/W）MPU区域基址寄存器别名1*/
  __IOM uint32_t RLAR_A1;                /*!< 偏移量：0x018（R/W）MPU区域限制地址寄存器别名1*/
  __IOM uint32_t RBAR_A2;                /*!< 偏移量：0x01C（R/W）MPU区域基址寄存器别名2*/
  __IOM uint32_t RLAR_A2;                /*!< 偏移量：0x020（R/W）MPU区域限制地址寄存器别名2*/
  __IOM uint32_t RBAR_A3;                /*!< 偏移量：0x024（R/W）MPU区域基址寄存器别名3*/
  __IOM uint32_t RLAR_A3;                /*!< 偏移量：0x028（R/W）MPU区域限制地址寄存器别名3*/
        uint32_t RESERVED0[1];
  union {
  __IOM uint32_t MAIR[2];
  struct {
  __IOM uint32_t MAIR0;                  /*!< 偏移量：0x030（R/W）MPU内存属性定向寄存器0*/
  __IOM uint32_t MAIR1;                  /*!< 偏移量：0x034（R/W）MPU内存属性定向寄存器1*/
  };
  };
} MPU_Type;

#define MPU_TYPE_RALIASES                  4U

/* MPU类型寄存器定义*/
#define MPU_TYPE_IREGION_Pos               16U                                            /*!< MPU类型：点火位置*/
#define MPU_TYPE_IREGION_Msk               (0xFFUL << MPU_TYPE_IREGION_Pos)               /*!< MPU类型：IREGION掩模*/

#define MPU_TYPE_DREGION_Pos                8U                                            /*!< MPU类型：DREGION位置*/
#define MPU_TYPE_DREGION_Msk               (0xFFUL << MPU_TYPE_DREGION_Pos)               /*!< MPU类型：DREGION面罩*/

#define MPU_TYPE_SEPARATE_Pos               0U                                            /*!< MPU类型：分离位置*/
#define MPU_TYPE_SEPARATE_Msk              (1UL /*<<MPU_TYPE_SEPARATE_Pos*/)             /*!< MPU类型：分离面罩*/

/* MPU控制寄存器定义*/
#define MPU_CTRL_PRIVDEFENA_Pos             2U                                            /*!< MPU CTRL：PRIVDEFENA位置*/
#define MPU_CTRL_PRIVDEFENA_Msk            (1UL << MPU_CTRL_PRIVDEFENA_Pos)               /*!< MPU CTRL:PRIVDEFENA掩码*/

#define MPU_CTRL_HFNMIENA_Pos               1U                                            /*!< MPU CTRL：HFNMIENA位置*/
#define MPU_CTRL_HFNMIENA_Msk              (1UL << MPU_CTRL_HFNMIENA_Pos)                 /*!< MPU CTRL:HFNMIENA掩码*/

#define MPU_CTRL_ENABLE_Pos                 0U                                            /*!< MPU CTRL：启用位置*/
#define MPU_CTRL_ENABLE_Msk                (1UL /*<<MPU_CTRL_ENABLE_Pos*/)               /*!< MPU CTRL：启用掩码*/

/* MPU区域编号寄存器定义*/
#define MPU_RNR_REGION_Pos                  0U                                            /*!< MPU RNR：区域位置*/
#define MPU_RNR_REGION_Msk                 (0xFFUL /*<<MPU_RNR_REGION_Pos*/)             /*!< MPU RNR：区域掩码*/

/* MPU区域基址寄存器定义*/
#define MPU_RBAR_BASE_Pos                   5U                                            /*!< MPU RBAR：基本位置*/
#define MPU_RBAR_BASE_Msk                  (0x7FFFFFFUL << MPU_RBAR_BASE_Pos)             /*!< MPU RBAR:BASE掩码*/

#define MPU_RBAR_SH_Pos                     3U                                            /*!< MPU RBAR:SH位置*/
#define MPU_RBAR_SH_Msk                    (0x3UL << MPU_RBAR_SH_Pos)                     /*!< MPU RBAR:SH掩码*/

#define MPU_RBAR_AP_Pos                     1U                                            /*!< MPU RBAR:AP位置*/
#define MPU_RBAR_AP_Msk                    (0x3UL << MPU_RBAR_AP_Pos)                     /*!< MPU RBAR:AP掩码*/

#define MPU_RBAR_XN_Pos                     0U                                            /*!< MPU RBAR:XN位置*/
#define MPU_RBAR_XN_Msk                    (01UL /*<<MPU_RBAR_XN_Pos*/)                  /*!< MPU RBAR:XN掩码*/

/* MPU区域限制地址寄存器定义*/
#define MPU_RLAR_LIMIT_Pos                  5U                                            /*!< MPU RLAR：极限位置*/
#define MPU_RLAR_LIMIT_Msk                 (0x7FFFFFFUL << MPU_RLAR_LIMIT_Pos)            /*!< MPU RLAR：极限掩码*/

#define MPU_RLAR_AttrIndx_Pos               1U                                            /*!< MPU RLAR：收件人位置*/
#define MPU_RLAR_AttrIndx_Msk              (0x7UL << MPU_RLAR_AttrIndx_Pos)               /*!< MPU RLAR：AttrIndex掩码*/

#define MPU_RLAR_EN_Pos                     0U                                            /*!< MPU RLAR：区域启用位位置*/
#define MPU_RLAR_EN_Msk                    (1UL /*<<MPU_RLAR_EN_Pos*/)                   /*!< MPU RLAR：区域启用位禁用掩码*/

/* MPU内存属性定向寄存器0定义*/
#define MPU_MAIR0_Attr3_Pos                24U                                            /*!< MPU MAIR0：Attr3位置*/
#define MPU_MAIR0_Attr3_Msk                (0xFFUL << MPU_MAIR0_Attr3_Pos)                /*!< MPU MAIR0：Attr3掩码*/

#define MPU_MAIR0_Attr2_Pos                16U                                            /*!< MPU MAIR0：收件人位置*/
#define MPU_MAIR0_Attr2_Msk                (0xFFUL << MPU_MAIR0_Attr2_Pos)                /*!< MPU MAIR0：属性2掩码*/

#define MPU_MAIR0_Attr1_Pos                 8U                                            /*!< MPU MAIR0：收件人1位置*/
#define MPU_MAIR0_Attr1_Msk                (0xFFUL << MPU_MAIR0_Attr1_Pos)                /*!< MPU MAIR0：Attr1掩码*/

#define MPU_MAIR0_Attr0_Pos                 0U                                            /*!< MPU MAIR0：Attr0位置*/
#define MPU_MAIR0_Attr0_Msk                (0xFFUL /*<<MPU_MAIR0_Attr0_Pos*/)            /*!< MPU MAIR0：Attr0掩码*/

/* MPU内存属性定向寄存器1定义*/
#define MPU_MAIR1_Attr7_Pos                24U                                            /*!< MPU MAIR1：Attr7位置*/
#define MPU_MAIR1_Attr7_Msk                (0xFFUL << MPU_MAIR1_Attr7_Pos)                /*!< MPU MAIR1：Attr7掩码*/

#define MPU_MAIR1_Attr6_Pos                16U                                            /*!< MPU MAIR1：收件人6位置*/
#define MPU_MAIR1_Attr6_Msk                (0xFFUL << MPU_MAIR1_Attr6_Pos)                /*!< MPU MAIR1：Attr6掩码*/

#define MPU_MAIR1_Attr5_Pos                 8U                                            /*!< MPU MAIR1：收件人5位置*/
#define MPU_MAIR1_Attr5_Msk                (0xFFUL << MPU_MAIR1_Attr5_Pos)                /*!< MPU MAIR1：Attr5掩码*/

#define MPU_MAIR1_Attr4_Pos                 0U                                            /*!< MPU MAIR1：收件人4位置*/
#define MPU_MAIR1_Attr4_Msk                (0xFFUL /*<<MPU_MAIR1_Attr4_Pos*/)            /*!< MPU MAIR1：Attr4掩码*/

/*@}CMSIS_MPU组末尾*/
#endif


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \inggroup CMSIS_core_register\defgroup CMSIS_SAU安全属性单元（SAU）\安全属性单元的简要类型定义@{
 */

/**
  \访问安全属性单元（SAU）的简要结构类型。
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< 偏移量：0x000（R/W）SAU控制寄存器*/
  __IM  uint32_t TYPE;                   /*!< 偏移量：0x004（R/）SAU类型寄存器*/
#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
  __IOM uint32_t RNR;                    /*!< 偏移量：0x008（R/W）SAU区域编号寄存器*/
  __IOM uint32_t RBAR;                   /*!< 偏移量：0x00C（R/W）SAU区域基址寄存器*/
  __IOM uint32_t RLAR;                   /*!< 偏移量：0x010（R/W）SAU区域限制地址寄存器*/
#else
        uint32_t RESERVED0[3];
#endif
  __IOM uint32_t SFSR;                   /*!< 偏移量：0x014（R/W）安全故障状态寄存器*/
  __IOM uint32_t SFAR;                   /*!< 偏移量：0x018（R/W）安全故障地址寄存器*/
} SAU_Type;

/* SAU控制寄存器定义*/
#define SAU_CTRL_ALLNS_Pos                  1U                                            /*!< SAU CTRL:ALLNS位置*/
#define SAU_CTRL_ALLNS_Msk                 (1UL << SAU_CTRL_ALLNS_Pos)                    /*!< SAU CTRL:ALLNS掩码*/

#define SAU_CTRL_ENABLE_Pos                 0U                                            /*!< SAU CTRL：启用位置*/
#define SAU_CTRL_ENABLE_Msk                (1UL /*<<SAU_CTRL_ENABLE_Pos*/)               /*!< SAU CTRL：启用掩码*/

/* SAU类型寄存器定义*/
#define SAU_TYPE_SREGION_Pos                0U                                            /*!< SAU类型：SREGION位置*/
#define SAU_TYPE_SREGION_Msk               (0xFFUL /*<<SAU_TYPE_SREGION_Pos*/)           /*!< SAU类型：SREGION面罩*/

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
/* SAU区域编号寄存器定义*/
#define SAU_RNR_REGION_Pos                  0U                                            /*!< SAU RNR：区域位置*/
#define SAU_RNR_REGION_Msk                 (0xFFUL /*<<SAU_RNR_REGION_Pos*/)             /*!< SAU RNR：区域掩码*/

/* SAU区域基址寄存器定义*/
#define SAU_RBAR_BADDR_Pos                  5U                                            /*!< SAU RBAR:BADR位置*/
#define SAU_RBAR_BADDR_Msk                 (0x7FFFFFFUL << SAU_RBAR_BADDR_Pos)            /*!< SAU RBAR:BADR掩码*/

/* SAU区域限制地址寄存器定义*/
#define SAU_RLAR_LADDR_Pos                  5U                                            /*!< SAU RLAR：梯子位置*/
#define SAU_RLAR_LADDR_Msk                 (0x7FFFFFFUL << SAU_RLAR_LADDR_Pos)            /*!< SAU RLAR:LADR面罩*/

#define SAU_RLAR_NSC_Pos                    1U                                            /*!< SAU RLAR：NSC职位*/
#define SAU_RLAR_NSC_Msk                   (1UL << SAU_RLAR_NSC_Pos)                      /*!< SAU RLAR:NSC面罩*/

#define SAU_RLAR_ENABLE_Pos                 0U                                            /*!< SAU RLAR：启用位置*/
#define SAU_RLAR_ENABLE_Msk                (1UL /*<<SAU_RLAR_ENABLE_Pos*/)               /*!< SAU RLAR：启用掩码*/

#endif /* 已定义（__SAUREGION_PRESENT）&&（__SAURIGION_PRESENT==1U）*/

/* 安全故障状态寄存器定义*/
#define SAU_SFSR_LSERR_Pos                  7U                                            /*!< SAU SFSR:LSERR位置*/
#define SAU_SFSR_LSERR_Msk                 (1UL << SAU_SFSR_LSERR_Pos)                    /*!< SAU SFSR:LSERR掩码*/

#define SAU_SFSR_SFARVALID_Pos              6U                                            /*!< SAU SFSR:SAFRVALID位置*/
#define SAU_SFSR_SFARVALID_Msk             (1UL << SAU_SFSR_SFARVALID_Pos)                /*!< SAU SFSR:SAFRVALID掩码*/

#define SAU_SFSR_LSPERR_Pos                 5U                                            /*!< SAU SFSR:LSPERR位置*/
#define SAU_SFSR_LSPERR_Msk                (1UL << SAU_SFSR_LSPERR_Pos)                   /*!< SAU SFSR:LSPERR掩码*/

#define SAU_SFSR_INVTRAN_Pos                4U                                            /*!< SAU SFSR：INVTRAN位置*/
#define SAU_SFSR_INVTRAN_Msk               (1UL << SAU_SFSR_INVTRAN_Pos)                  /*!< SAU SFSR:INVTRAN掩码*/

#define SAU_SFSR_AUVIOL_Pos                 3U                                            /*!< SAU SFSR：AUVIOL位置*/
#define SAU_SFSR_AUVIOL_Msk                (1UL << SAU_SFSR_AUVIOL_Pos)                   /*!< SAU SFSR:AUVOL掩码*/

#define SAU_SFSR_INVER_Pos                  2U                                            /*!< SAU SFSR：逆变器位置*/
#define SAU_SFSR_INVER_Msk                 (1UL << SAU_SFSR_INVER_Pos)                    /*!< SAU SFSR:INVER掩码*/

#define SAU_SFSR_INVIS_Pos                  1U                                            /*!< SAU SFSR:INVIS位置*/
#define SAU_SFSR_INVIS_Msk                 (1UL << SAU_SFSR_INVIS_Pos)                    /*!< SAU SFSR:INVIS掩码*/

#define SAU_SFSR_INVEP_Pos                  0U                                            /*!< SAU SFSR:INVEP位置*/
#define SAU_SFSR_INVEP_Msk                 (1UL /*<<SAU_SFSR_INVEP_Pos*/)                /*!< SAU SFSR:INVEP掩码*/

/*@}CMSIS_SAU组末尾*/
#endif /* 已定义（__ARM_FEATURE_CMDSE）&&（__ARM-FEATURE_CSME==3U）*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_FPU浮点单元（FPU）\浮点单元（FP U）的简要类型定义@{
 */

/**
  \访问浮点单元（FPU）的简短结构类型。
 */
typedef struct
{
        uint32_t RESERVED0[1U];
  __IOM uint32_t FPCCR;                  /*!< 偏移量：0x004（R/W）浮点上下文控制寄存器*/
  __IOM uint32_t FPCAR;                  /*!< 偏移量：0x008（R/W）浮点上下文地址寄存器*/
  __IOM uint32_t FPDSCR;                 /*!< 偏移量：0x00C（R/W）浮点默认状态控制寄存器*/
  __IM  uint32_t MVFR0;                  /*!< 偏移量：0x010（R/）介质和FP功能寄存器0*/
  __IM  uint32_t MVFR1;                  /*!< 偏移量：0x014（R/）介质和FP功能寄存器1*/
} FPU_Type;

/* 浮点上下文控制寄存器定义*/
#define FPU_FPCCR_ASPEN_Pos                31U                                            /*!< FPCCR:ASPEN位位置*/
#define FPU_FPCCR_ASPEN_Msk                (1UL << FPU_FPCCR_ASPEN_Pos)                   /*!< FPCCR:ASPEN位掩码*/

#define FPU_FPCCR_LSPEN_Pos                30U                                            /*!< FPCCR:LSPEN位置*/
#define FPU_FPCCR_LSPEN_Msk                (1UL << FPU_FPCCR_LSPEN_Pos)                   /*!< FPCCR:LSPEN位掩码*/

#define FPU_FPCCR_LSPENS_Pos               29U                                            /*!< FPCCR:LSPENS位置*/
#define FPU_FPCCR_LSPENS_Msk               (1UL << FPU_FPCCR_LSPENS_Pos)                  /*!< FPCCR:LSPENS位掩码*/

#define FPU_FPCCR_CLRONRET_Pos             28U                                            /*!< FPCCR：CLRONRET位置*/
#define FPU_FPCCR_CLRONRET_Msk             (1UL << FPU_FPCCR_CLRONRET_Pos)                /*!< FPCCR:CLRONRET位掩码*/

#define FPU_FPCCR_CLRONRETS_Pos            27U                                            /*!< FPCCR：CLRONRETS位置*/
#define FPU_FPCCR_CLRONRETS_Msk            (1UL << FPU_FPCCR_CLRONRETS_Pos)               /*!< FPCCR:CLRONRETS位掩码*/

#define FPU_FPCCR_TS_Pos                   26U                                            /*!< FPCCR:TS位置*/
#define FPU_FPCCR_TS_Msk                   (1UL << FPU_FPCCR_TS_Pos)                      /*!< FPCCR:TS位掩码*/

#define FPU_FPCCR_UFRDY_Pos                10U                                            /*!< FPCCR:UFRDY位置*/
#define FPU_FPCCR_UFRDY_Msk                (1UL << FPU_FPCCR_UFRDY_Pos)                   /*!< FPCCR:UFRDY位掩码*/

#define FPU_FPCCR_SPLIMVIOL_Pos             9U                                            /*!< FPCCR：分瓣位置*/
#define FPU_FPCCR_SPLIMVIOL_Msk            (1UL << FPU_FPCCR_SPLIMVIOL_Pos)               /*!< FPCCR：SPLIVIOL位掩码*/

#define FPU_FPCCR_MONRDY_Pos                8U                                            /*!< FPCCR：监控位置*/
#define FPU_FPCCR_MONRDY_Msk               (1UL << FPU_FPCCR_MONRDY_Pos)                  /*!< FPCCR:MONRDY位掩码*/

#define FPU_FPCCR_SFRDY_Pos                 7U                                            /*!< FPCCR:SFRDY位置*/
#define FPU_FPCCR_SFRDY_Msk                (1UL << FPU_FPCCR_SFRDY_Pos)                   /*!< FPCCR:SFRDY位掩码*/

#define FPU_FPCCR_BFRDY_Pos                 6U                                            /*!< FPCCR：BFRDY位置*/
#define FPU_FPCCR_BFRDY_Msk                (1UL << FPU_FPCCR_BFRDY_Pos)                   /*!< FPCCR:BFRDY位掩码*/

#define FPU_FPCCR_MMRDY_Pos                 5U                                            /*!< FPCCR：MMRDY位置*/
#define FPU_FPCCR_MMRDY_Msk                (1UL << FPU_FPCCR_MMRDY_Pos)                   /*!< FPCCR:MMRDY位掩码*/

#define FPU_FPCCR_HFRDY_Pos                 4U                                            /*!< FPCCR:HFRDY位置*/
#define FPU_FPCCR_HFRDY_Msk                (1UL << FPU_FPCCR_HFRDY_Pos)                   /*!< FPCCR:HFRDY位掩码*/

#define FPU_FPCCR_THREAD_Pos                3U                                            /*!< FPCCR：处理器模式位位置*/
#define FPU_FPCCR_THREAD_Msk               (1UL << FPU_FPCCR_THREAD_Pos)                  /*!< FPCCR：处理器模式活动位掩码*/

#define FPU_FPCCR_S_Pos                     2U                                            /*!< FPCCR：FP上下文位位置的安全状态*/
#define FPU_FPCCR_S_Msk                    (1UL << FPU_FPCCR_S_Pos)                       /*!< FPCCR：FP上下文位掩码的安全状态*/

#define FPU_FPCCR_USER_Pos                  1U                                            /*!< FPCCR：特权级别位位置*/
#define FPU_FPCCR_USER_Msk                 (1UL << FPU_FPCCR_USER_Pos)                    /*!< FPCCR：特权级别位掩码*/

#define FPU_FPCCR_LSPACT_Pos                0U                                            /*!< FPCCR：惰性状态保存活动位位置*/
#define FPU_FPCCR_LSPACT_Msk               (1UL /*<<FPU_FPCCR_SPACT_Pos*/)              /*!< FPCCR：惰性状态保存活动位掩码*/

/* 浮点上下文地址寄存器定义*/
#define FPU_FPCAR_ADDRESS_Pos               3U                                            /*!< FPCAR：地址位位置*/
#define FPU_FPCAR_ADDRESS_Msk              (0x1FFFFFFFUL << FPU_FPCAR_ADDRESS_Pos)        /*!< FPCAR：地址位掩码*/

/* 浮点默认状态控制寄存器定义*/
#define FPU_FPDSCR_AHP_Pos                 26U                                            /*!< FPDSCR：AHP位位置*/
#define FPU_FPDSCR_AHP_Msk                 (1UL << FPU_FPDSCR_AHP_Pos)                    /*!< FPDSCR：AHP位掩码*/

#define FPU_FPDSCR_DN_Pos                  25U                                            /*!< FPDSCR:DN位位置*/
#define FPU_FPDSCR_DN_Msk                  (1UL << FPU_FPDSCR_DN_Pos)                     /*!< FPDSCR:DN位掩码*/

#define FPU_FPDSCR_FZ_Pos                  24U                                            /*!< FPDSCR:FZ位位置*/
#define FPU_FPDSCR_FZ_Msk                  (1UL << FPU_FPDSCR_FZ_Pos)                     /*!< FPDSCR:FZ位掩码*/

#define FPU_FPDSCR_RMode_Pos               22U                                            /*!< FPDSCR:RMode位位置*/
#define FPU_FPDSCR_RMode_Msk               (3UL << FPU_FPDSCR_RMode_Pos)                  /*!< FPDSCR:RMode位掩码*/

/* 媒体和FP功能寄存器0定义*/
#define FPU_MVFR0_FP_rounding_modes_Pos    28U                                            /*!< MVFR0：FP舍入模式位位置*/
#define FPU_MVFR0_FP_rounding_modes_Msk    (0xFUL << FPU_MVFR0_FP_rounding_modes_Pos)     /*!< MVFR0：FP舍入模式位掩码*/

#define FPU_MVFR0_Short_vectors_Pos        24U                                            /*!< MVFR0：短矢量位位置*/
#define FPU_MVFR0_Short_vectors_Msk        (0xFUL << FPU_MVFR0_Short_vectors_Pos)         /*!< MVFR0：短矢量位掩码*/

#define FPU_MVFR0_Square_root_Pos          20U                                            /*!< MVFR0：平方根位位置*/
#define FPU_MVFR0_Square_root_Msk          (0xFUL << FPU_MVFR0_Square_root_Pos)           /*!< MVFR0：平方根位掩码*/

#define FPU_MVFR0_Divide_Pos               16U                                            /*!< MVFR0：除法位位置*/
#define FPU_MVFR0_Divide_Msk               (0xFUL << FPU_MVFR0_Divide_Pos)                /*!< MVFR0：除法位掩码*/

#define FPU_MVFR0_FP_excep_trapping_Pos    12U                                            /*!< MVFR0:FP异常捕获位位置*/
#define FPU_MVFR0_FP_excep_trapping_Msk    (0xFUL << FPU_MVFR0_FP_excep_trapping_Pos)     /*!< MVFR0:FP异常捕获位掩码*/

#define FPU_MVFR0_Double_precision_Pos      8U                                            /*!< MVFR0：双精度位位置*/
#define FPU_MVFR0_Double_precision_Msk     (0xFUL << FPU_MVFR0_Double_precision_Pos)      /*!< MVFR0：双精度位掩码*/

#define FPU_MVFR0_Single_precision_Pos      4U                                            /*!< MVFR0：单精度位位置*/
#define FPU_MVFR0_Single_precision_Msk     (0xFUL << FPU_MVFR0_Single_precision_Pos)      /*!< MVFR0：单精度位掩码*/

#define FPU_MVFR0_A_SIMD_registers_Pos      0U                                            /*!< MVFR0:A_SIMD寄存器位位置*/
#define FPU_MVFR0_A_SIMD_registers_Msk     (0xFUL /*<<FPU_MVFR0_A_SIMD_寄存器_Pos*/)  /*!< MVFR0:A_SIMD寄存器位掩码*/

/* 媒体和FP功能寄存器1定义*/
#define FPU_MVFR1_FP_fused_MAC_Pos         28U                                            /*!< MVFR1:FP融合MAC位位置*/
#define FPU_MVFR1_FP_fused_MAC_Msk         (0xFUL << FPU_MVFR1_FP_fused_MAC_Pos)          /*!< MVFR1:FP融合MAC位掩码*/

#define FPU_MVFR1_FP_HPFP_Pos              24U                                            /*!< MVFR1:FP HPFP位位置*/
#define FPU_MVFR1_FP_HPFP_Msk              (0xFUL << FPU_MVFR1_FP_HPFP_Pos)               /*!< MVFR1:FP HPFP位掩码*/

#define FPU_MVFR1_D_NaN_mode_Pos            4U                                            /*!< MVFR1:D_NaN模式位位置*/
#define FPU_MVFR1_D_NaN_mode_Msk           (0xFUL << FPU_MVFR1_D_NaN_mode_Pos)            /*!< MVFR1:D_NaN模式位掩码*/

#define FPU_MVFR1_FtZ_mode_Pos              0U                                            /*!< MVFR1:FtZ模式位位置*/
#define FPU_MVFR1_FtZ_mode_Msk             (0xFUL /*<<FPU_MVFR1_FtZ_mode_Pos*/)          /*!< MVFR1:FtZ模式位掩码*/

/*@}CMSIS_FPU组结束*/


/**
  \inggroup CMSIS_core_register\defgroup CMSIS_CoreDebug核心调试寄存器（CoreDebug）\核心调试寄存器的简要类型定义@{
 */

/**
  \用于访问核心调试寄存器（CoreDebug）的简短结构类型。
 */
typedef struct
{
  __IOM uint32_t DHCSR;                  /*!< 偏移量：0x000（R/W）调试暂停控制和状态寄存器*/
  __OM  uint32_t DCRSR;                  /*!< 偏移量：0x004（/W）调试核心寄存器选择器寄存器*/
  __IOM uint32_t DCRDR;                  /*!< 偏移量：0x008（R/W）调试核心寄存器数据寄存器*/
  __IOM uint32_t DEMCR;                  /*!< 偏移量：0x00C（R/W）调试异常和监控寄存器*/
        uint32_t RESERVED4[1U];
  __IOM uint32_t DAUTHCTRL;              /*!< 偏移量：0x014（R/W）调试验证控制寄存器*/
  __IOM uint32_t DSCSR;                  /*!< 偏移量：0x018（R/W）调试安全控制和状态寄存器*/
} CoreDebug_Type;

/* 调试暂停控制和状态寄存器定义*/
#define CoreDebug_DHCSR_DBGKEY_Pos         16U                                            /*!< CoreDebug DHCSR:DBGKEY位置*/
#define CoreDebug_DHCSR_DBGKEY_Msk         (0xFFFFUL << CoreDebug_DHCSR_DBGKEY_Pos)       /*!< CoreDebug DHCSR:DBGKEY掩码*/

#define CoreDebug_DHCSR_S_RESTART_ST_Pos   26U                                            /*!< 核心调试DHCSR:S_RESTART_ST位置*/
#define CoreDebug_DHCSR_S_RESTART_ST_Msk   (1UL << CoreDebug_DHCSR_S_RESTART_ST_Pos)      /*!< CoreDebug DHCSR:S_RESTART_ST掩码*/

#define CoreDebug_DHCSR_S_RESET_ST_Pos     25U                                            /*!< 核心调试DHCSR:S_RESET_ST位置*/
#define CoreDebug_DHCSR_S_RESET_ST_Msk     (1UL << CoreDebug_DHCSR_S_RESET_ST_Pos)        /*!< CoreDebug DHCSR:S_RESET_ST掩码*/

#define CoreDebug_DHCSR_S_RETIRE_ST_Pos    24U                                            /*!< 核心调试DHCSR:S_RETIRE_ST位置*/
#define CoreDebug_DHCSR_S_RETIRE_ST_Msk    (1UL << CoreDebug_DHCSR_S_RETIRE_ST_Pos)       /*!< CoreDebug DHCSR:S_RETIRE_ST掩码*/

#define CoreDebug_DHCSR_S_LOCKUP_Pos       19U                                            /*!< CoreDebug DHCSR:S_LOCKUP位置*/
#define CoreDebug_DHCSR_S_LOCKUP_Msk       (1UL << CoreDebug_DHCSR_S_LOCKUP_Pos)          /*!< CoreDebug DHCSR:S_LOCKUP掩码*/

#define CoreDebug_DHCSR_S_SLEEP_Pos        18U                                            /*!< CoreDebug DHCSR:S_SLEEP位置*/
#define CoreDebug_DHCSR_S_SLEEP_Msk        (1UL << CoreDebug_DHCSR_S_SLEEP_Pos)           /*!< CoreDebug DHCSR:S_SLEEP掩码*/

#define CoreDebug_DHCSR_S_HALT_Pos         17U                                            /*!< CoreDebug DHCSR:S_HALT位置*/
#define CoreDebug_DHCSR_S_HALT_Msk         (1UL << CoreDebug_DHCSR_S_HALT_Pos)            /*!< CoreDebug DHCSR:S_HALT掩码*/

#define CoreDebug_DHCSR_S_REGRDY_Pos       16U                                            /*!< CoreDebug DHCSR:S_REGRDY位置*/
#define CoreDebug_DHCSR_S_REGRDY_Msk       (1UL << CoreDebug_DHCSR_S_REGRDY_Pos)          /*!< CoreDebug DHCSR:S_REGRDY掩码*/

#define CoreDebug_DHCSR_C_SNAPSTALL_Pos     5U                                            /*!< CoreDebug DHCSR:C_SNAPSTALL位置*/
#define CoreDebug_DHCSR_C_SNAPSTALL_Msk    (1UL << CoreDebug_DHCSR_C_SNAPSTALL_Pos)       /*!< CoreDebug DHCSR:C_SNAPSTALL掩码*/

#define CoreDebug_DHCSR_C_MASKINTS_Pos      3U                                            /*!< CoreDebug DHCSR:C_MASKINTS位置*/
#define CoreDebug_DHCSR_C_MASKINTS_Msk     (1UL << CoreDebug_DHCSR_C_MASKINTS_Pos)        /*!< CoreDebug DHCSR:C_MASKINTS掩码*/

#define CoreDebug_DHCSR_C_STEP_Pos          2U                                            /*!< CoreDebug DHCSR:C_PSTEP位置*/
#define CoreDebug_DHCSR_C_STEP_Msk         (1UL << CoreDebug_DHCSR_C_STEP_Pos)            /*!< CoreDebug DHCSR:C_PSTEP掩码*/

#define CoreDebug_DHCSR_C_HALT_Pos          1U                                            /*!< CoreDebug DHCSR:C_HALL位置*/
#define CoreDebug_DHCSR_C_HALT_Msk         (1UL << CoreDebug_DHCSR_C_HALT_Pos)            /*!< CoreDebug DHCSR:C_HART掩码*/

#define CoreDebug_DHCSR_C_DEBUGEN_Pos       0U                                            /*!< CoreDebug DHCSR:C_DEBUGEN位置*/
#define CoreDebug_DHCSR_C_DEBUGEN_Msk      (1UL /*<<CoreDebug_DHCSR_C_DEBUGEN_Pos*/)     /*!< CoreDebug DHCSR:C_DEBUGEN掩码*/

/* 调试核心寄存器选择器寄存器定义*/
#define CoreDebug_DCRSR_REGWnR_Pos         16U                                            /*!< CoreDebug DCRSR:REGWnR位置*/
#define CoreDebug_DCRSR_REGWnR_Msk         (1UL << CoreDebug_DCRSR_REGWnR_Pos)            /*!< CoreDebug DCRSR:REGWnR掩码*/

#define CoreDebug_DCRSR_REGSEL_Pos          0U                                            /*!< CoreDebug DCRSR:REGSEL位置*/
#define CoreDebug_DCRSR_REGSEL_Msk         (0x1FUL /*<<核心调试DCRSR_REGSEL_Pos*/)     /*!< CoreDebug DCRSR:REGSEL掩码*/

/* 调试异常和监视器控制寄存器定义*/
#define CoreDebug_DEMCR_TRCENA_Pos         24U                                            /*!< CoreDebug DEMCR:TRCENA位置*/
#define CoreDebug_DEMCR_TRCENA_Msk         (1UL << CoreDebug_DEMCR_TRCENA_Pos)            /*!< CoreDebug DEMCR:TRCENA掩码*/

#define CoreDebug_DEMCR_MON_REQ_Pos        19U                                            /*!< CoreDebug DEMCR:MON_REQ位置*/
#define CoreDebug_DEMCR_MON_REQ_Msk        (1UL << CoreDebug_DEMCR_MON_REQ_Pos)           /*!< CoreDebug DEMCR:MON_REQ掩码*/

#define CoreDebug_DEMCR_MON_STEP_Pos       18U                                            /*!< CoreDebug DEMCR:MON_STEP位置*/
#define CoreDebug_DEMCR_MON_STEP_Msk       (1UL << CoreDebug_DEMCR_MON_STEP_Pos)          /*!< CoreDebug DEMCR:MON_STEP掩码*/

#define CoreDebug_DEMCR_MON_PEND_Pos       17U                                            /*!< 核心调试DEMCR:MON_PEND位置*/
#define CoreDebug_DEMCR_MON_PEND_Msk       (1UL << CoreDebug_DEMCR_MON_PEND_Pos)          /*!< CoreDebug DEMCR:MON_PEND掩码*/

#define CoreDebug_DEMCR_MON_EN_Pos         16U                                            /*!< 核心调试DEMCR:MON_EN位置*/
#define CoreDebug_DEMCR_MON_EN_Msk         (1UL << CoreDebug_DEMCR_MON_EN_Pos)            /*!< CoreDebug DEMCR:MON_EN掩码*/

#define CoreDebug_DEMCR_VC_HARDERR_Pos     10U                                            /*!< 核心调试DEMCR:VC_HARDERR位置*/
#define CoreDebug_DEMCR_VC_HARDERR_Msk     (1UL << CoreDebug_DEMCR_VC_HARDERR_Pos)        /*!< CoreDebug DEMCR:VC_HARDERR掩码*/

#define CoreDebug_DEMCR_VC_INTERR_Pos       9U                                            /*!< 核心调试DEMCR:VC_INTERR位置*/
#define CoreDebug_DEMCR_VC_INTERR_Msk      (1UL << CoreDebug_DEMCR_VC_INTERR_Pos)         /*!< CoreDebug DEMCR:VC_INTERR掩码*/

#define CoreDebug_DEMCR_VC_BUSERR_Pos       8U                                            /*!< 核心调试DEMCR:VC_BUSERR位置*/
#define CoreDebug_DEMCR_VC_BUSERR_Msk      (1UL << CoreDebug_DEMCR_VC_BUSERR_Pos)         /*!< CoreDebug DEMCR:VC_BUSERR掩码*/

#define CoreDebug_DEMCR_VC_STATERR_Pos      7U                                            /*!< CoreDebug DEMCR:VC_STATERR位置*/
#define CoreDebug_DEMCR_VC_STATERR_Msk     (1UL << CoreDebug_DEMCR_VC_STATERR_Pos)        /*!< CoreDebug DEMCR:VC_STATERR掩码*/

#define CoreDebug_DEMCR_VC_CHKERR_Pos       6U                                            /*!< 核心调试DEMCR:VC_CHKERR位置*/
#define CoreDebug_DEMCR_VC_CHKERR_Msk      (1UL << CoreDebug_DEMCR_VC_CHKERR_Pos)         /*!< CoreDebug DEMCR:VC_CHKERR掩码*/

#define CoreDebug_DEMCR_VC_NOCPERR_Pos      5U                                            /*!< 核心调试DEMCR:VC_NOCPERR位置*/
#define CoreDebug_DEMCR_VC_NOCPERR_Msk     (1UL << CoreDebug_DEMCR_VC_NOCPERR_Pos)        /*!< CoreDebug DEMCR:VC_NOCPERR掩码*/

#define CoreDebug_DEMCR_VC_MMERR_Pos        4U                                            /*!< 核心调试DEMCR:VC_MMERR位置*/
#define CoreDebug_DEMCR_VC_MMERR_Msk       (1UL << CoreDebug_DEMCR_VC_MMERR_Pos)          /*!< CoreDebug DEMCR:VC_MMERR掩码*/

#define CoreDebug_DEMCR_VC_CORERESET_Pos    0U                                            /*!< CoreDebug DEMCR:VC_CORERESET位置*/
#define CoreDebug_DEMCR_VC_CORERESET_Msk   (1UL /*<<CoreDebug_DEMCR_VC_CORERESET_Pos*/)  /*!< CoreDebug DEMCR:VC_CORERESET掩码*/

/* 调试身份验证控制寄存器定义*/
#define CoreDebug_DAUTHCTRL_INTSPNIDEN_Pos  3U                                            /*!< CoreDebug DAUTHCTRL:INTSPNIDEN，位置*/
#define CoreDebug_DAUTHCTRL_INTSPNIDEN_Msk (1UL << CoreDebug_DAUTHCTRL_INTSPNIDEN_Pos)    /*!< CoreDebug DAUTHCTRL:INTSPNIDEN，掩码*/

#define CoreDebug_DAUTHCTRL_SPNIDENSEL_Pos  2U                                            /*!< CoreDebug DAUTHCTRL:SPNDENSEL位置*/
#define CoreDebug_DAUTHCTRL_SPNIDENSEL_Msk (1UL << CoreDebug_DAUTHCTRL_SPNIDENSEL_Pos)    /*!< CoreDebug DAUTHCTRL:SPNDENSEL掩码*/

#define CoreDebug_DAUTHCTRL_INTSPIDEN_Pos   1U                                            /*!< CoreDebug DAUTHCTRL:INTSPIDEN位置*/
#define CoreDebug_DAUTHCTRL_INTSPIDEN_Msk  (1UL << CoreDebug_DAUTHCTRL_INTSPIDEN_Pos)     /*!< CoreDebug DAUTHCTRL:INTSPIDEN掩码*/

#define CoreDebug_DAUTHCTRL_SPIDENSEL_Pos   0U                                            /*!< CoreDebug DAUTHCTRL：SPIDENSEL位置*/
#define CoreDebug_DAUTHCTRL_SPIDENSEL_Msk  (1UL /*<<核心调试_ DAUTHCTRL_SPIDENSEL_Pos*/) /*!< CoreDebug DAUTHCTRL：SPIDENSEL掩码*/

/* 调试安全控制和状态寄存器定义*/
#define CoreDebug_DSCSR_CDS_Pos            16U                                            /*!< CoreDebug DSCSR:CDS位置*/
#define CoreDebug_DSCSR_CDS_Msk            (1UL << CoreDebug_DSCSR_CDS_Pos)               /*!< CoreDebug DSCSR:CDS掩码*/

#define CoreDebug_DSCSR_SBRSEL_Pos          1U                                            /*!< CoreDebug DSCSR:SBRSEL位置*/
#define CoreDebug_DSCSR_SBRSEL_Msk         (1UL << CoreDebug_DSCSR_SBRSEL_Pos)            /*!< CoreDebug DSCSR:SBRSEL掩码*/

#define CoreDebug_DSCSR_SBRSELEN_Pos        0U                                            /*!< CoreDebug DSCSR:SBRSELEN位置*/
#define CoreDebug_DSCSR_SBRSELEN_Msk       (1UL /*<<CoreDebug_DSCSR_SBRSELEN_Pos*/)      /*!< CoreDebug DSCSR:SBRSELEN掩码*/

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
  #define SCS_BASE            (0xE000E000UL)                             /*!< 系统控制空间基地址*/
  #define ITM_BASE            (0xE0000000UL)                             /*!< ITM基本地址*/
  #define DWT_BASE            (0xE0001000UL)                             /*!< DWT基本地址*/
  #define TPI_BASE            (0xE0040000UL)                             /*!< TPI基本地址*/
  #define CoreDebug_BASE      (0xE000EDF0UL)                             /*!< 核心调试基地址*/
  #define SysTick_BASE        (SCS_BASE +  0x0010UL)                     /*!< SysTick基地址*/
  #define NVIC_BASE           (SCS_BASE +  0x0100UL)                     /*!< NVIC基址*/
  #define SCB_BASE            (SCS_BASE +  0x0D00UL)                     /*!< 系统控制块基址*/

  #define SCnSCB              ((SCnSCB_Type    *)     SCS_BASE         ) /*!< 系统控制寄存器不在SCB中*/
  #define SCB                 ((SCB_Type       *)     SCB_BASE         ) /*!< SCB配置结构*/
  #define SysTick             ((SysTick_Type   *)     SysTick_BASE     ) /*!< SysTick配置结构*/
  #define NVIC                ((NVIC_Type      *)     NVIC_BASE        ) /*!< NVIC配置结构*/
  #define ITM                 ((ITM_Type       *)     ITM_BASE         ) /*!< ITM配置结构*/
  #define DWT                 ((DWT_Type       *)     DWT_BASE         ) /*!< DWT配置结构*/
  #define TPI                 ((TPI_Type       *)     TPI_BASE         ) /*!< TPI配置结构*/
  #define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE   ) /*!< 核心调试配置结构*/

  #if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
    #define MPU_BASE          (SCS_BASE +  0x0D90UL)                     /*!< 内存保护单元*/
    #define MPU               ((MPU_Type       *)     MPU_BASE         ) /*!< 内存保护单元*/
  #endif

  #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    #define SAU_BASE          (SCS_BASE +  0x0DD0UL)                     /*!< 安全归属单位*/
    #define SAU               ((SAU_Type       *)     SAU_BASE         ) /*!< 安全归属单位*/
  #endif

  #define FPU_BASE            (SCS_BASE +  0x0F30UL)                     /*!< 浮点单位*/
  #define FPU                 ((FPU_Type       *)     FPU_BASE         ) /*!< 浮点单位*/

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  #define SCS_BASE_NS         (0xE002E000UL)                             /*!< 系统控制空间基地址（非安全地址空间）*/
  #define CoreDebug_BASE_NS   (0xE002EDF0UL)                             /*!< 核心调试基地址（非安全地址空间）*/
  #define SysTick_BASE_NS     (SCS_BASE_NS +  0x0010UL)                  /*!< SysTick基址（非安全地址空间）*/
  #define NVIC_BASE_NS        (SCS_BASE_NS +  0x0100UL)                  /*!< NVIC基址（非安全地址空间）*/
  #define SCB_BASE_NS         (SCS_BASE_NS +  0x0D00UL)                  /*!< 系统控制块基地址（非安全地址空间）*/

  #define SCnSCB_NS           ((SCnSCB_Type    *)     SCS_BASE_NS      ) /*!< 系统控制寄存器不在SCB中（非安全地址空间）*/
  #define SCB_NS              ((SCB_Type       *)     SCB_BASE_NS      ) /*!< SCB配置结构（非安全地址空间）*/
  #define SysTick_NS          ((SysTick_Type   *)     SysTick_BASE_NS  ) /*!< SysTick配置结构（非安全地址空间）*/
  #define NVIC_NS             ((NVIC_Type      *)     NVIC_BASE_NS     ) /*!< NVIC配置结构（非安全地址空间）*/
  #define CoreDebug_NS        ((CoreDebug_Type *)     CoreDebug_BASE_NS) /*!< 核心调试配置结构（非安全地址空间）*/

  #if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
    #define MPU_BASE_NS       (SCS_BASE_NS +  0x0D90UL)                  /*!< 内存保护单元（非安全地址空间）*/
    #define MPU_NS            ((MPU_Type       *)     MPU_BASE_NS      ) /*!< 内存保护单元（非安全地址空间）*/
  #endif

  #define FPU_BASE_NS         (SCS_BASE_NS +  0x0F30UL)                  /*!< 浮点单元（非安全地址空间）*/
  #define FPU_NS              ((FPU_Type       *)     FPU_BASE_NS      ) /*!< 浮点单元（非安全地址空间）*/

#endif /* 已定义（__ARM_FEATURE_CMDSE）&&（__ARM-FEATURE_CSME==3U）*/
/*@} */



/*******************************************************************************
 *                硬件抽象层核心功能接口包含：
  -核心NVIC功能
  -核心SysTick功能
  -核心调试功能
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
  #define NVIC_GetActive              __NVIC_GetActive
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


/* 安全/非安全呼叫处理和异常处理的特殊LR值*/

/* 安全BLXNS输入时的功能返回有效载荷（来自ARMv8-M架构参考手册）LR值*/ 
#define FNC_RETURN                 (0xFEFFFFFFUL)     /* 处理分支时忽略位[0]*/

/* 以下EXC_RETURN掩码值用于评估异常条目时的LR*/
#define EXC_RETURN_PREFIX          (0xFF000000UL)     /* 位[31:24]设置为指示EXC_RETURN值*/
#define EXC_RETURN_S               (0x00000040UL)     /* 用于推送寄存器的位[6]堆栈：0=非安全1=安全*/
#define EXC_RETURN_DCRS            (0x00000020UL)     /* 位[5]调用寄存器的堆栈规则：0=跳过1=保存*/
#define EXC_RETURN_FTYPE           (0x00000010UL)     /* bit[4]为浮点上下文分配堆栈：0=已完成1=已跳过*/
#define EXC_RETURN_MODE            (0x00000008UL)     /* bit[3]返回的处理器模式：0=处理程序模式1=线程模式*/
#define EXC_RETURN_SPSEL           (0x00000004UL)     /* 用于还原上下文的位[2]堆栈指针：0=MSP 1=PSP*/
#define EXC_RETURN_ES              (0x00000001UL)     /* 位[0]安全状态异常被设置为：0=不安全1=安全*/

/* 异常上下文堆栈的完整性签名（来自ARMv8-M架构参考手册）*/
#if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)  /* 具有浮点扩展名的处理器的值：*/
#define EXC_INTEGRITY_SIGNATURE     (0xFEFA125AUL)     /* 位[0]SFTC必须与LR位[4]EXC_RETURN_TYPE匹配*/
#else 
#define EXC_INTEGRITY_SIGNATURE     (0xFEFA125BUL)     /* 不带浮点扩展名的处理器的值*/
#endif


/**
  \brief Set Priority Grouping\details使用所需的解锁顺序设置优先级分组字段。参数PriorityGroup分配给字段SCB->AIRCR[10:8]PRIGROUP字段。仅使用从0到7的值。如果优先级分组和可用优先级位（__NVIC_PRIO_bits）之间发生冲突，则设置最小的可能优先级组。\param[in]PriorityGroup Priority分组字段。
 */
__STATIC_INLINE void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* 仅使用值0..7*/

  reg_value  =  SCB->AIRCR;                                                   /* 读取旧寄存器配置*/
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* 清除要更改的位*/
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)  );              /* 插入写入密钥和优先级组*/
  SCB->AIRCR =  reg_value;
}


/**
  \brief Get Priority Grouping\details从NVIC中断控制器读取优先级分组字段。\return Priority分组字段（SCB->AIRCR[10:8]PRIGROUP字段）。
 */
__STATIC_INLINE uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}


/**
  \brief Enable Interrupt\details启用NVIC中断控制器中的设备特定中断。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Get Interrupt Enable status \details从NVIC中断控制器返回设备特定的中断启用状态。\param[in]IRQn设备特定中断号。\return 0未启用中断。\return 1中断被启用。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
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
    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
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
    return((uint32_t)(((NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
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
    NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Clear Pending Interrupt\details清除NVIC挂起寄存器中设备特定中断的挂起位。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Get Active Interrupt\details读取NVIC中的活动寄存器，并返回设备特定中断的活动位。\param[in]IRQn设备特定中断号。\return 0中断状态未激活。\return 1中断状态为活动状态。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief Get Interrupt Target State\details读取NVIC中的中断目标字段，并返回设备特定中断的中断目标位。\param[in]IRQn设备特定中断号。\如果中断分配给非安全，则返回0。注意IRQn不能为负。
 */
__STATIC_INLINE uint32_t NVIC_GetTargetState(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief Set Interrupt Target State\details设置NVIC中的中断目标字段，并返回设备特定中断的中断目标位。\param[in]IRQn设备特定中断号。\如果中断分配给非安全，则返回0。注意IRQn不能为负。
 */
__STATIC_INLINE uint32_t NVIC_SetTargetState(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] |=  ((uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL)));
    return((uint32_t)(((NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief Clear Interrupt Target State\details清除NVIC中的中断目标字段，并返回设备特定中断的中断目标位。\param[in]IRQn设备特定中断号。\如果中断分配给非安全，则返回0。注意IRQn不能为负。
 */
__STATIC_INLINE uint32_t NVIC_ClearTargetState(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] &= ~((uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL)));
    return((uint32_t)(((NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
#endif /* 已定义（__ARM_FEATURE_CMDSE）&&（__ARM-FEATURE_CSME==3U）*/


/**
  \brief Set Interrupt Priority\details设置设备特定中断或处理器异常的优先级。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\param[in]要设置的优先级。\注意：不能为每个处理器异常设置优先级。
 */
__STATIC_INLINE void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IPR[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}


/**
  \brief Get Interrupt Priority\details读取设备特定中断或处理器异常的优先级。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\return中断优先级。值自动与微控制器的实现优先级位对齐。
 */
__STATIC_INLINE uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)NVIC->IPR[((uint32_t)IRQn)]               >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((uint32_t)SCB->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
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
  \brief Decode Priority\details将具有给定优先级组的中断优先级值解码为抢占优先级值和子优先级值。如果优先级分组和可用优先级位（__NVIC_PRIO_bits）之间存在冲突，则设置最小的可能优先级组。\param[in]Priority Priority值，可使用\ref __NVIC_GetPriority（）检索。\param[in]PriorityGroup使用的优先级组。\param[out]pPreemptPriority抢占优先级值（从0开始）。\param[out]pSubPrioritySubpriority值（从0开始）。
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
  \brief Set Interrupt Vector\details在基于SRAM的中断向量表中设置中断向量。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。VTOR之前必须重新定位到SRAM。\param[in]IRQn中断号\param[in]vector中断处理程序函数的地址
 */
__STATIC_INLINE void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET] = vector;
}


/**
  \brief Get Interrupt Vector\details从中断向量表中读取中断向量。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\return中断处理程序函数的地址
 */
__STATIC_INLINE uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  return vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET];
}


/**
  \brief System Reset \details启动系统重置请求以重置MCU。
 */
__NO_RETURN __STATIC_INLINE void __NVIC_SystemReset(void)
{
  __DSB();                                                          /* 确保所有未完成的内存访问（包括缓冲写入）在重置前完成*/
  SCB->AIRCR  = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)    |
                           (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                            SCB_AIRCR_SYSRESETREQ_Msk    );         /* 保持优先级组不变*/
  __DSB();                                                          /* 确保完成内存访问*/

  for(;;)                                                           /* 等待重置*/
  {
    __NOP();
  }
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief Set Priority Grouping（非安全）\details使用所需的解锁序列设置处于安全状态时的非安全优先级分组字段。参数PriorityGroup分配给字段SCB->AIRCR[10:8]PRIGROUP字段。仅使用从0到7的值。如果优先级分组和可用优先级位（__NVIC_PRIO_bits）之间发生冲突，则设置最小的可能优先级组。\param[in]PriorityGroup Priority分组字段。
 */
__STATIC_INLINE void TZ_NVIC_SetPriorityGrouping_NS(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* 仅使用值0..7*/

  reg_value  =  SCB_NS->AIRCR;                                                /* 读取旧寄存器配置*/
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* 清除要更改的位*/
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)  );              /* 插入写入密钥和优先级组*/
  SCB_NS->AIRCR =  reg_value;
}


/**
  \brief Get Priority Grouping（非安全）\details在安全状态下从非安全NVIC读取优先级分组字段。\return Priority分组字段（SCB->AIRCR[10:8]PRIGROUP字段）。
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetPriorityGrouping_NS(void)
{
  return ((uint32_t)((SCB_NS->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}


/**
  \brief Enable Interrupt（非安全）\details当处于安全状态时，在非安全NVIC中断控制器中启用设备特定中断。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void TZ_NVIC_EnableIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Get Interrupt Enable status（非安全）\details当处于安全状态时，从非安全NVIC中断控制器返回设备特定的中断启用状态。\param[in]IRQn设备特定中断号。\return 0未启用中断。\return 1中断被启用。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetEnableIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC_NS->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief Disable Interrupt（非安全）\details在处于安全状态时禁用非安全NVIC中断控制器中的设备特定中断。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void TZ_NVIC_DisableIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Get Pending Interrupt（非安全）\details在处于安全状态时读取非安全NVIC中的NVIC挂起寄存器，并返回指定设备特定中断的挂起位。\param[in]IRQn设备特定中断号。\return 0中断状态未挂起。\return 1中断状态为待定。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetPendingIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC_NS->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief Set Pending Interrupt（非安全）\details设置处于安全状态时非安全NVIC挂起寄存器中特定于设备的中断的挂起位。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void TZ_NVIC_SetPendingIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Clear Pending Interrupt（非安全）\ details在处于安全状态时，清除非安全NVIC挂起寄存器中特定于设备的中断的挂起位。\param[in]IRQn设备特定中断号。\注意IRQn不能为负数。
 */
__STATIC_INLINE void TZ_NVIC_ClearPendingIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief Get Active Interrupt（非安全）\details在处于安全状态时读取非安全NVIC中的活动寄存器，并返回设备特定中断的活动位。\param[in]IRQn设备特定中断号。\return 0中断状态未激活。\return 1中断状态为活动状态。\注意IRQn不能为负数。
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetActive_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC_NS->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief设置中断优先级（非安全）\details设置处于安全状态时非安全设备特定中断或非安全处理器异常的优先级。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\param[in]要设置的优先级。\注意：不能为每个非安全处理器异常设置优先级。
 */
__STATIC_INLINE void TZ_NVIC_SetPriority_NS(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->IPR[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB_NS->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}


/**
  \brief Get Interrupt Priority（非安全）\details在安全状态下读取非安全设备特定中断或非安全处理器异常的优先级。中断号可以是正数以指定设备特定中断，也可以是负数以指定处理器异常。\param[in]IRQn中断编号。\return中断优先级。值自动与微控制器的实现优先级位对齐。
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetPriority_NS(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)NVIC_NS->IPR[((uint32_t)IRQn)]               >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((uint32_t)SCB_NS->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
  }
}
#endif /*  已定义（__ARM_FEATURE_CMDSE）&&（__ARM-FEATURE_CSME==3U）*/

/*@}CMSIS_Core_NVICFunctions结束*/

/* ##########################MPU功能#############*/

#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)

#include "mpu_armv8.h"

#endif

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
  uint32_t mvfr0;

  mvfr0 = FPU->MVFR0;
  if      ((mvfr0 & (FPU_MVFR0_Single_precision_Msk | FPU_MVFR0_Double_precision_Msk)) == 0x220U)
  {
    return 2U;           /* 双精度+单精度FPU*/
  }
  else if ((mvfr0 & (FPU_MVFR0_Single_precision_Msk | FPU_MVFR0_Double_precision_Msk)) == 0x020U)
  {
    return 1U;           /* 单精度FPU*/
  }
  else
  {
    return 0U;           /* 无FPU*/
  }
}


/*@}CMSIS_Core_FpuFunctions结束*/



/* ##########################SAU函数######################*/
/**
  \inggroup CMSIS_Core_FunctionInterface\defgroup CMSIS-Core_SAUFunctions SAU Functions\brief配置SAU的函数@{
 */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  \brief Enable SAU\details启用安全属性单元（SAU）。
 */
__STATIC_INLINE void TZ_SAU_Enable(void)
{
    SAU->CTRL |=  (SAU_CTRL_ENABLE_Msk);
}



/**
  \brief禁用SAU\details禁用安全属性单元（SAU）。
 */
__STATIC_INLINE void TZ_SAU_Disable(void)
{
    SAU->CTRL &= ~(SAU_CTRL_ENABLE_Msk);
}

#endif /* 已定义（__ARM_FEATURE_CMDSE）&&（__ARM-FEATURE_CSME==3U）*/

/*@}CMSIS_Core_SAUFunctions结束*/




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

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief System Tick Configuration（非安全）\details在安全状态下初始化非安全系统计时器及其中断，并启动系统Tick Timer。计数器处于自由运行模式，以生成周期性中断。\param[in]ticks两个中断之间的刻度数。\return 0函数成功。\return 1函数失败。\注意：当变量<b>__Vendor_SysTickConfig</b>设置为1时，则不包括函数<b>TZ_SysTik_Config_NS</b>。在这种情况下，文件<b><i>设备</i>。h</b>必须包含此函数的供应商特定实现。

 */
__STATIC_INLINE uint32_t TZ_SysTick_Config_NS(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                         /* 无法重新加载值*/
  }

  SysTick_NS->LOAD  = (uint32_t)(ticks - 1UL);                            /* 设置重新加载寄存器*/
  TZ_NVIC_SetPriority_NS (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* 设置Systick中断的优先级*/
  SysTick_NS->VAL   = 0UL;                                                /* 加载SysTick计数器值*/
  SysTick_NS->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                      SysTick_CTRL_TICKINT_Msk   |
                      SysTick_CTRL_ENABLE_Msk;                            /* 启用SysTick IRQ和SysTick计时器*/
  return (0UL);                                                           /* 功能成功*/
}
#endif /* 已定义（__ARM_FEATURE_CMDSE）&&（__ARM-FEATURE_CSME==3U）*/

#endif

/*@}CMSIS_Core_SysTickFunctions结束*/



/* #####################################调试输入/输出函数#############*/
/**
  \inggroup CMSIS_Core_FunctionInterface\defgroup CMSIS_Core_DebugFunctions ITM Functions\brief访问ITM调试接口的函数@{
 */

extern volatile int32_t ITM_RxBuffer;                              /*!< 用于接收字符的外部变量。*/
#define                 ITM_RXBUFFER_EMPTY  ((int32_t)0x5AA55AA5U) /*!< 标识\ref ITM_RxBuffer的值已准备好用于下一个字符。*/


/**
  \brief ITM发送字符\details通过ITM通道0发送字符，当未连接任何已预订输出的调试器时返回。\li在连接调试器时阻塞，但发送的前一个字符尚未传输。\param[in]ch要传输的字符。\返回要传输的字符。
 */
__STATIC_INLINE uint32_t ITM_SendChar (uint32_t ch)
{
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&      /* ITM已启用*/
      ((ITM->TER & 1UL               ) != 0UL)   )     /* ITM端口#0已启用*/
  {
    while (ITM->PORT[0U].u32 == 0UL)
    {
      __NOP();
    }
    ITM->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}


/**
  \brief ITM Receive Character\details通过外部变量\ref ITM_RxBuffer输入字符。\return接收的字符。\return-1没有挂起的字符。
 */
__STATIC_INLINE int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                           /* 没有可用字符*/

  if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY)
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ITM_RXBUFFER_EMPTY;       /* 为下一个角色做好准备*/
  }

  return (ch);
}


/**
  \brief ITM Check Character\details检查变量\ref ITM_RxBuffer中是否有待读取的字符。\return 0无可用字符。\return 1个字符可用。
 */
__STATIC_INLINE int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ITM_RXBUFFER_EMPTY)
  {
    return (0);                              /* 没有可用字符*/
  }
  else
  {
    return (1);                              /*    字符可用*/
  }
}

/*@}CMSIS_core_DebugFunctions结束*/




#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM33_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */

