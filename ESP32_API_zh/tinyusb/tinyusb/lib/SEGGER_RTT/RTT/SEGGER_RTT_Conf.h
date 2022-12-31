/*********************************************************************
*                    SEGGER微控制器GmbH*嵌入式专家
**********************************************************************
*                                                                    *（c）1995-2019 SEGGER微控制器有限公司
*                                                                    *
*       网址：www.segger。com支持：support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT*嵌入式目标的实时传输*
*                                                                    *
**********************************************************************
*                                                                    *
* 保留所有权利*
*                                                                    *
* SEGGER强烈建议不要对本软件的源代码进行任何更改*或修改，以便与RTT协议和J-Link保持兼容。
*                                                                    *
* 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否经过修改：
*                                                                    *
* o源代码的重新分发必须保留上述版权*声明、本条件和以下免责声明。
*                                                                    *
* 本软件由版权持有人和贡献者“按原样”提供，不承担任何明示或暗示的保证，包括但不限于适销性和特定用途适用性的暗示保证。在任何情况下，SEGGER微控制器对任何直接、间接、附带、特殊、惩戒性或后果性损害（包括但不限于购买替代商品或服务；使用、数据或利润损失；或业务中断）均不承担责任，无论是由何原因引起的，也不以任何责任理论为依据，或因使用本软件而以任何方式产生的侵权行为（包括疏忽或其他），即使已告知此类损害的可能性。
*                                                                    *
**********************************************************************
---------------------------标题结束------------------------------文件：SEGGER_RTT_Conf。h目的：实现SEGGER实时传输（RTT），允许在CPU运行时在支持调试器内存访问的目标上进行实时通信。版本：$Rev:18601$

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
#ifndef   SEGGER_RTT_MAX_NUM_UP_BUFFERS
  #define SEGGER_RTT_MAX_NUM_UP_BUFFERS             (3)     // 此目标上可用的最大上行缓冲区数（T->H）（默认值：3）
#endif

#ifndef   SEGGER_RTT_MAX_NUM_DOWN_BUFFERS
  #define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS           (3)     // 此目标上可用的最大向下缓冲区数（H->T）（默认值：3）
#endif

#ifndef   BUFFER_SIZE_UP
  #define BUFFER_SIZE_UP                            (1024)  // 目标终端输出的缓冲区大小，直到主机（默认值：1k）
#endif

#ifndef   BUFFER_SIZE_DOWN
  #define BUFFER_SIZE_DOWN                          (16)    // 从主机到目标的终端输入的缓冲区大小（通常为键盘输入）（默认值：16）
#endif

#ifndef   SEGGER_RTT_PRINTF_BUFFER_SIZE
  #define SEGGER_RTT_PRINTF_BUFFER_SIZE             (64u)    // RTT printf通过RTT批量发送字符的缓冲区大小（默认值：64）
#endif

#ifndef   SEGGER_RTT_MODE_DEFAULT
  #define SEGGER_RTT_MODE_DEFAULT                   SEGGER_RTT_MODE_NO_BLOCK_SKIP // 预初始化终端信道模式（缓冲区0）
#endif

/*********************************************************************
* RTT内存配置
*
*       memcpy（）适用于大量数据，但对于通常通过RTT存储的少量数据，开销很大。对于SEGGER_RTT_MEMCPY_USE_BYTELOOP，可以使用简单的字节循环。
*
*       SEGGER_RTT_MEMCPY（）可用于替换RTT函数中的标准MEMCPY（）。这可能需要内存访问限制，例如在带有MMU的Cortex-A设备上。
*/
#ifndef   SEGGER_RTT_MEMCPY_USE_BYTELOOP
  #define SEGGER_RTT_MEMCPY_USE_BYTELOOP              0 // 0：使用memcpy/SEGGER_RTT_memcpy，1：使用简单的字节循环
#endif
//
// SEGGER_RTT_MEMCPY到具有GCC工具链和Cortex-A目标的外部MEMCPY的示例定义
//
//#如果（定义__SES_ARM）||（定义__CROSSWORKS_ARM）||（定义__GNUC__））&&（定义（__ARM_ARCH_7A__））
//  #定义SEGGER_RTT_MEMCPY（pDest，pSrc，NumBytes）SEGGER_MEMCPY
//#结束符

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
#ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
  #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY         (0x20)   // Cortex-M3/4上SEGGER_RTT_lock上的锁定中断优先级（默认值：0x20）
#endif

/*********************************************************************
* SEGGER Embedded Studio、Rowley CrossStudio和GCC的RTT锁配置
*/
#if ((defined(__SES_ARM) || defined(__SES_RISCV) || defined(__CROSSWORKS_ARM) || defined(__GNUC__) || defined(__clang__)) && !defined (__CC_ARM) && !defined(WIN32))
  #if (defined(__ARM_ARCH_6M__) || defined(__ARM_ARCH_8M_BASE__))
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                    unsigned int LockState;                                         \
                                  __asm volatile ("mrs   %0, primask  \n\t"                         \
                                                  "movs  r1, $1       \n\t"                         \
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
  #elif (defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_8M_MAIN__))
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
  #elif defined(__riscv) || defined(__riscv_xlen)
    #define SEGGER_RTT_LOCK()  {                                               \
                                 unsigned int LockState;                       \
                                 __asm volatile ("csrr  %0, mstatus  \n\t"     \
                                                 "csrci mstatus, 8   \n\t"     \
                                                 "andi  %0, %0,  8   \n\t"     \
                                                 : "=r" (LockState)            \
                                                 :                             \
                                                 :                             \
                                                );
                               
  #define SEGGER_RTT_UNLOCK()    __asm volatile ("csrr  a1, mstatus  \n\t"     \
                                                 "or    %0, %0, a1   \n\t"     \
                                                 "csrs  mstatus, %0  \n\t"     \
                                                 :                             \
                                                 : "r"  (LockState)            \
                                                 : "a1"                        \
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
  #if (defined (__ARM6M__)          && (__CORE__ == __ARM6M__))             ||                      \
      (defined (__ARM8M_BASELINE__) && (__CORE__ == __ARM8M_BASELINE__))
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int LockState;                                           \
                                  LockState = __get_PRIMASK();                                      \
                                  __set_PRIMASK(1);

    #define SEGGER_RTT_UNLOCK()   __set_PRIMASK(LockState);                                         \
                                }
  #elif (defined (__ARM7EM__)         && (__CORE__ == __ARM7EM__))          ||                      \
        (defined (__ARM7M__)          && (__CORE__ == __ARM7M__))           ||                      \
        (defined (__ARM8M_MAINLINE__) && (__CORE__ == __ARM8M_MAINLINE__))  ||                      \
        (defined (__ARM8M_MAINLINE__) && (__CORE__ == __ARM8M_MAINLINE__))
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
* IAR RL78的RTT锁配置
*/
#ifdef __ICCRL78__
  #define SEGGER_RTT_LOCK()   {                                                                     \
                                __istate_t LockState;                                               \
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
                                  LockState = _set_interrupt_priority(SEGGER_RTT_MAX_INTERRUPT_PRIORITY);

    #define SEGGER_RTT_UNLOCK()   _set_interrupt_priority(LockState);                               \
                                }
  #endif
#endif

/*********************************************************************
* CCRX的RTT锁配置
*/
#ifdef __RX
  #define SEGGER_RTT_LOCK()   {                                                                     \
                                unsigned long LockState;                                            \
                                LockState = get_psw() & 0x010000;                                   \
                                clrpsw_i();                           
                                    
  #define SEGGER_RTT_UNLOCK()   set_psw(get_psw() | LockState);                                     \
                              }
#endif

/*********************************************************************
* Windows上embOS仿真的RTT锁配置（也可用于embOS的通用RTT锁）
*/
#if defined(WIN32) || defined(SEGGER_RTT_LOCK_EMBOS)

void OS_SIM_EnterCriticalSection(void);
void OS_SIM_LeaveCriticalSection(void);

#define SEGGER_RTT_LOCK()       {                                                                   \
                                  OS_SIM_EnterCriticalSection();

#define SEGGER_RTT_UNLOCK()       OS_SIM_LeaveCriticalSection();                                    \
                                }
#endif

/*********************************************************************
* RTT锁配置回退
*/
#ifndef   SEGGER_RTT_LOCK
  #define SEGGER_RTT_LOCK()                // 锁定RTT（可嵌套）（即禁用中断）
#endif

#ifndef   SEGGER_RTT_UNLOCK
  #define SEGGER_RTT_UNLOCK()              // 解锁RTT（可嵌套）（即启用先前的中断锁定状态）
#endif

#endif
/***************************文件结尾****************************/

