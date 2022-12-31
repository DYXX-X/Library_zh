/*********************************************************************
*                SEGGER微控制器GmbH&Co.KG*嵌入式专家
**********************************************************************
*                                                                    *（c）2015-2017 SEGGER微控制器股份有限公司
*                                                                    *
*       网址：www.segger。com支持：support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView*实时应用程序分析*
*                                                                    *
**********************************************************************
*                                                                    *
* 保留所有权利*
*                                                                    *
* SEGGER强烈建议不要对本软件的源代码进行任何更改*或修改，以便与RTT协议和J-Link保持兼容。
*                                                                    *
* 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否经过修改：
*                                                                    *
* o源代码的重新分发必须保留上述版权*声明、本条件列表和以下免责声明。
*                                                                    *
* o二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述*版权声明、本条件列表和以下免责声明。
*                                                                    *
* o未经事先书面许可，不得使用SEGGER Microcontroller GmbH&Co.KG*的名称或其贡献者的名称来支持或推广源自本软件的产品。
*                                                                    *
* 本软件由版权持有人和贡献者“按原样”提供，不承担任何明示或暗示的保证，包括但不限于适销性和特定用途适用性的暗示保证。在任何情况下，SEGGER微控制器对任何直接、间接、附带、特殊、惩戒性或后果性损害（包括但不限于购买替代商品或服务；使用、数据或利润损失；或业务中断）均不承担责任，无论是由何原因引起的，也不以任何责任理论为依据，或因使用本软件而以任何方式产生的侵权行为（包括疏忽或其他），即使已告知此类损害的可能性。
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView版本：V2.42*
*                                                                    *
**********************************************************************
-------------------------- END-OF-HEADER -----------------------------

文件：SEGGER_SYSVIEW_Conf。h目的：SEGGER SystemView配置。版本：$Rev:5927$
*/

#ifndef SEGGER_SYSVIEW_CONF_H
#define SEGGER_SYSVIEW_CONF_H

#include "soc/soc.h"

/*********************************************************************
* 定义，固定
*
**********************************************************************
*/
//
// 已知堆芯配置的常量
//
#define SEGGER_SYSVIEW_CORE_OTHER   0
#define SEGGER_SYSVIEW_CORE_CM0     1 // Cortex-M0/M0+/M1
#define SEGGER_SYSVIEW_CORE_CM3     2 // Cortex-M3/M4/M7
#define SEGGER_SYSVIEW_CORE_RX      3 // 瑞萨RX

#if (defined __SES_ARM) || (defined __CROSSWORKS_ARM) || (defined __GNUC__)
  #ifdef __ARM_ARCH_6M__
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM0
  #elif (defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__))
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM3
  #endif
#elif defined(__ICCARM__)
  #if (defined (__ARM6M__) && (__CORE__ == __ARM6M__))
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM0
  #elif ((defined (__ARM7M__) && (__CORE__ == __ARM7M__)) || (defined (__ARM7EM__) && (__CORE__ == __ARM7EM__)))
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM3
  #endif
#elif defined(__CC_ARM)
  #if (defined(__TARGET_ARCH_6S_M))
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM0
  #elif (defined(__TARGET_ARCH_7_M) || defined(__TARGET_ARCH_7E_M))
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM3
  #endif
#elif defined(__TI_ARM__)
  #ifdef __TI_ARM_V6M0__
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM0
  #elif (defined(__TI_ARM_V7M3__) || defined(__TI_ARM_V7M4__))
    #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM3
  #endif
#elif defined(__ICCRX__)
  #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_RX
#elif defined(__RX)
  #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_RX
#endif

#ifndef   SEGGER_SYSVIEW_CORE
  #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_OTHER
#endif

/*********************************************************************
* 定义，可配置
*
**********************************************************************
*/
/*********************************************************************
* SystemView缓冲区配置
*/
#define SEGGER_SYSVIEW_RTT_BUFFER_SIZE      1024                                // SystemView用于缓冲区的字节数。
#define SEGGER_SYSVIEW_RTT_CHANNEL          1                                   // SystemView将使用的RTT频道。0：自动选择

#define SEGGER_SYSVIEW_USE_STATIC_BUFFER    1                                   // 使用静态缓冲区生成事件，而不是堆栈上的缓冲区

#define SEGGER_SYSVIEW_POST_MORTEM_MODE     0                                   // 1： 启用死后分析模式

/*********************************************************************
* SystemView时间戳配置
*/
#if SEGGER_SYSVIEW_CORE == SEGGER_SYSVIEW_CORE_CM3
  #define SEGGER_SYSVIEW_GET_TIMESTAMP()      (*(U32 *)(0xE0001004))            // 检索系统时间戳。Cortex-M循环计数器。
  #define SEGGER_SYSVIEW_TIMESTAMP_BITS       32                                // 定义时钟源提供的低位有效位数
#else
  #define SEGGER_SYSVIEW_GET_TIMESTAMP()      SEGGER_SYSVIEW_X_GetTimestamp()   // 通过用户定义的函数检索系统时间戳
  #define SEGGER_SYSVIEW_TIMESTAMP_BITS       32                                // 定义SEGGER_SYSVIEW_X_GetTimestamp（）提供的低位有效位数
#endif

/*********************************************************************
* SystemView Id配置
*/
//TODO:优化它
#define SEGGER_SYSVIEW_ID_BASE         SOC_DROM_LOW                             // 应用程序报告的最低Id的默认值。可由应用程序通过SEGGER_SYSVIEW_SetRAMBase（）覆盖。（即，当所有ID都是此RAM中的地址时，为0x20000000）
#define SEGGER_SYSVIEW_ID_SHIFT        0                                        // 移动Id以节省带宽的位数。（即当ID为4字节对齐时为2）

/*********************************************************************
* SystemView中断配置
*/
#if SEGGER_SYSVIEW_CORE == SEGGER_SYSVIEW_CORE_CM3
  #define SEGGER_SYSVIEW_GET_INTERRUPT_ID()   ((*(U32 *)(0xE000ED04)) & 0x1FF)  // 获取当前活动中断Id。（即读取Cortex-M ICSR[8:0]=活动向量）
#elif SEGGER_SYSVIEW_CORE == SEGGER_SYSVIEW_CORE_CM0
  #if defined(__ICCARM__)
    #define SEGGER_SYSVIEW_GET_INTERRUPT_ID()   (__get_IPSR())                  // IAR的解决方案，它可能会对0xE000ED04进行字节访问。请改为读取IPSR。
  #else
    #define SEGGER_SYSVIEW_GET_INTERRUPT_ID()   ((*(U32 *)(0xE000ED04)) & 0x3F) // 获取当前活动中断Id。（即读取Cortex-M ICSR[5:0]=活动向量）
  #endif
#else
  #define SEGGER_SYSVIEW_GET_INTERRUPT_ID()   SEGGER_SYSVIEW_X_GetInterruptId() // 从用户提供的函数中获取当前活动的中断Id。
#endif

unsigned SEGGER_SYSVIEW_X_SysView_Lock(void);
void SEGGER_SYSVIEW_X_SysView_Unlock(unsigned int_state);
// 要递归，请在调用方的堆栈上保存IRQ状态
#define SEGGER_SYSVIEW_LOCK()   unsigned _SYSVIEW_int_state = SEGGER_SYSVIEW_X_SysView_Lock()
#define SEGGER_SYSVIEW_UNLOCK() SEGGER_SYSVIEW_X_SysView_Unlock(_SYSVIEW_int_state)

#endif  // SEGGER_SYSVIEW_CONF_H

/***************************文件结尾****************************/

