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
---------------------------标题结束------------------------------文件：SEGGER_RTT_Conf。h目的：实现SEGGER实时传输（RTT），允许在CPU运行时在支持调试器内存访问的目标上进行实时通信。版本：$Rev:5626$

*/

#ifndef SEGGER_RTT_CONF_H
#define SEGGER_RTT_CONF_H

#ifdef __IAR_SYSTEMS_ICC__
  #include <intrinsics.h>
#endif

/*********************************************************************
* 定义，可配置
*
**********************************************************************
*/

#define SEGGER_RTT_MAX_NUM_UP_BUFFERS             (3)     // 此目标上可用的最大上行缓冲区数（T->H）（默认值：3）
#define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS           (3)     // 此目标上可用的最大向下缓冲区数（H->T）（默认值：3）

#define BUFFER_SIZE_UP                            (1024)  // 目标终端输出的缓冲区大小，直到主机（默认值：1k）
#define BUFFER_SIZE_DOWN                          (16)    // 从主机到目标的终端输入的缓冲区大小（通常为键盘输入）（默认值：16）

#define SEGGER_RTT_PRINTF_BUFFER_SIZE             (64u)    // RTT printf通过RTT批量发送字符的缓冲区大小（默认值：64）

#define SEGGER_RTT_MODE_DEFAULT                   SEGGER_RTT_MODE_NO_BLOCK_SKIP // 预初始化终端信道模式（缓冲区0）

//
// 当字符串尚未完全存储时，不允许目标执行其他RTT操作。
// 否则，缓冲区中可能会出现混合字符串。
// 如果在中断、多个任务或多个处理器中使用RTT，请在此处定义SEGGER_RTT_LOCK（）和SEGGER-RTT_UNLOC（）函数。
//
// SEGGER_RTT_MAX_INTERRUPT_PRIORITY可用于Cortex-M3/4上的示例锁例程。
// 确保屏蔽所有可能发送RTT数据的中断，即生成SystemView事件或导致任务切换。
// 如果在发送RTT数据时不能屏蔽高优先级中断，则需要相应地调整SEGGER_RTT_MAX_INTERRUPT_priority。
// （较高优先级=较低优先级编号）
// embOS的默认值：128u
// FreeRTOS中的默认配置：configMAX_SYSCALL_INTERRUPT_PRIORITY:（configLIBRARY_MAX_SYSCALI_INTERRUPT.PRIORITY<<（8-configPRIO_BITS））
// 如果有疑问，屏蔽所有中断：1<<（8-BASEPRI_PRIO_BITS），即当3位在NVIC中实现时，1<<5
// 或定义SEGGER_RTT_LOCK（）以完全禁用中断。
//

#define SEGGER_RTT_MAX_INTERRUPT_PRIORITY         (0x20)   // Cortex-M3/4上SEGGER_RTT_lock上的锁定中断优先级（默认值：0x20）

/*********************************************************************
* SEGGER Embedded Studio、Rowley CrossStudio和GCC的RTT锁配置
*/
#if (defined __SES_ARM) || (defined __CROSSWORKS_ARM) || (defined __GNUC__)
  #ifdef __ARM_ARCH_6M__
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                    unsigned int LockState;                                         \
                                  __asm volatile ("mrs   %0, primask  \n\t"                         \
                                                  "mov   r1, $1     \n\t"                           \
                                                  "msr   primask, r1  \n\t"                         \
                                                  : "=r" (LockState)                                \
                                                  :                                                 \
                                                  : "r1"                                            \
                                                  );

    #define SEGGER_RTT_UNLOCK()   __asm volatile ("msr   primask, %0  \n\t"                         \
                                                  :                                                 \
                                                  : "r" (LockState)                                 \
                                                  :                                                 \
                                                  );                                                \
                                }

  #elif (defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                    unsigned int LockState;                                         \
                                  __asm volatile ("mrs   %0, basepri  \n\t"                         \
                                                  "mov   r1, %1       \n\t"                         \
                                                  "msr   basepri, r1  \n\t"                         \
                                                  : "=r" (LockState)                                \
                                                  : "i"(SEGGER_RTT_MAX_INTERRUPT_PRIORITY)          \
                                                  : "r1"                                            \
                                                  );

    #define SEGGER_RTT_UNLOCK()   __asm volatile ("msr   basepri, %0  \n\t"                         \
                                                  :                                                 \
                                                  : "r" (LockState)                                 \
                                                  :                                                 \
                                                  );                                                \
                                }

  #elif defined(__ARM_ARCH_7A__)
    #define SEGGER_RTT_LOCK() {                                                \
                                 unsigned int LockState;                       \
                                 __asm volatile ("mrs r1, CPSR \n\t"           \
                                                 "mov %0, r1 \n\t"             \
                                                 "orr r1, r1, #0xC0 \n\t"      \
                                                 "msr CPSR_c, r1 \n\t"         \
                                                 : "=r" (LockState)            \
                                                 :                             \
                                                 : "r1"                        \
                                                 );

    #define SEGGER_RTT_UNLOCK() __asm volatile ("mov r0, %0 \n\t"              \
                                                "mrs r1, CPSR \n\t"            \
                                                "bic r1, r1, #0xC0 \n\t"       \
                                                "and r0, r0, #0xC0 \n\t"       \
                                                "orr r1, r1, r0 \n\t"          \
                                                "msr CPSR_c, r1 \n\t"          \
                                                :                              \
                                                : "r" (LockState)              \
                                                : "r0", "r1"                   \
                                                );                             \
                            }
#else
    #define SEGGER_RTT_LOCK()
    #define SEGGER_RTT_UNLOCK()
  #endif
#endif

/*********************************************************************
* IAR EWARM的RTT锁配置
*/
#ifdef __ICCARM__
  #if (defined (__ARM6M__) && (__CORE__ == __ARM6M__))
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  LockState = __get_PRIMASK();                                      \
                                  __set_PRIMASK(1);

    #define SEGGER_RTT_UNLOCK()   __set_PRIMASK(LockState);                                         \
                                }
  #elif ((defined (__ARM7EM__) && (__CORE__ == __ARM7EM__)) || (defined (__ARM7M__) && (__CORE__ == __ARM7M__)))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  LockState = __get_BASEPRI();                                      \
                                  __set_BASEPRI(SEGGER_RTT_MAX_INTERRUPT_PRIORITY);

    #define SEGGER_RTT_UNLOCK()   __set_BASEPRI(LockState);                                         \
                                }
  #endif
#endif

/*********************************************************************
* IAR RX的RTT锁配置
*/
#ifdef __ICCRX__
  #define SEGGER_RTT_LOCK()   {                                                                     \
                                unsigned long LockState;                                            \
                                LockState = __get_interrupt_state();                                \
                                __disable_interrupt();

  #define SEGGER_RTT_UNLOCK()   __set_interrupt_state(LockState);                                   \
                              }
#endif

/*********************************************************************
* KEIL ARM的RTT锁配置
*/
#ifdef __CC_ARM
  #if (defined __TARGET_ARCH_6S_M)
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  register unsigned char PRIMASK __asm( "primask");                 \
                                  LockState = PRIMASK;                                              \
                                  PRIMASK = 1u;                                                     \
                                  __schedule_barrier();

    #define SEGGER_RTT_UNLOCK()   PRIMASK = LockState;                                              \
                                  __schedule_barrier();                                             \
                                }
  #elif (defined(__TARGET_ARCH_7_M) || defined(__TARGET_ARCH_7E_M))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  register unsigned char BASEPRI __asm( "basepri");                 \
                                  LockState = BASEPRI;                                              \
                                  BASEPRI = SEGGER_RTT_MAX_INTERRUPT_PRIORITY;                      \
                                  __schedule_barrier();

    #define SEGGER_RTT_UNLOCK()   BASEPRI = LockState;                                              \
                                  __schedule_barrier();                                             \
                                }
  #endif
#endif

/*********************************************************************
* TI ARM的RTT锁配置
*/
#ifdef __TI_ARM__
  #if defined (__TI_ARM_V6M0__)
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  LockState = __get_PRIMASK();                                      \
                                  __set_PRIMASK(1);

    #define SEGGER_RTT_UNLOCK()   __set_PRIMASK(LockState);                                         \
                                }
  #elif (defined (__TI_ARM_V7M3__) || defined (__TI_ARM_V7M4__))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  LockState = OS_GetBASEPRI();                                      \
                                  OS_SetBASEPRI(SEGGER_RTT_MAX_INTERRUPT_PRIORITY);

    #define SEGGER_RTT_UNLOCK()   OS_SetBASEPRI(LockState);                                         \
                                }
  #endif
#endif

/*********************************************************************
* RTT锁配置回退
*/
#ifndef   SEGGER_RTT_LOCK
  void SEGGER_SYSVIEW_X_RTT_Lock(void);
  #define SEGGER_RTT_LOCK()                SEGGER_SYSVIEW_X_RTT_Lock() // 锁定RTT（可嵌套）（即禁用中断）
#endif

#ifndef   SEGGER_RTT_UNLOCK
  void SEGGER_SYSVIEW_X_RTT_Unlock(void);
  #define SEGGER_RTT_UNLOCK()              SEGGER_SYSVIEW_X_RTT_Unlock() // 解锁RTT（可嵌套）（即启用先前的中断锁定状态）
#endif

#endif
/***************************文件结尾****************************/

