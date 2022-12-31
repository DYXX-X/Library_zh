/*
 * FreeRTOS内核V10.0.0版权所有（C）2017 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。如果您希望使用我们的AmazonFreeRTOS名称，请以不引起混淆的合理使用方式使用。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org http://aws.amazon.com/freertos
 *
 * 1个制表符==4个空格！
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 特定于应用程序的定义。
 *
 * 这些定义应根据您的特定硬件和应用程序需求进行调整。
 *
 * 这些参数在FreeRTOS上提供的FreeRTOS API文档的“配置”部分中进行了描述。org网站。
 *
 * 看见http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

// 包括MCU标头
#include "bsp/board_mcu.h"

extern uint32_t SystemCoreClock;

/* Cortex M23/M33端口配置。*/
#define configENABLE_MPU								        0
#define configENABLE_FPU								        1
#define configENABLE_TRUSTZONE					        0
#define configMINIMAL_SECURE_STACK_SIZE					( 1024 )

#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configCPU_CLOCK_HZ                      SystemCoreClock
#define configTICK_RATE_HZ                      ( 1000 )
#define configMAX_PRIORITIES                    ( 5 )
#define configMINIMAL_STACK_SIZE                ( 128 )
#define configTOTAL_HEAP_SIZE                   ( 0*1024 ) // 未使用动态
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               2
#define configUSE_QUEUE_SETS                    0
#define configUSE_TIME_SLICING                  0
#define configUSE_NEWLIB_REENTRANT              0
#define configENABLE_BACKWARD_COMPATIBILITY     1
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   0

#define configSUPPORT_STATIC_ALLOCATION         1
#define configSUPPORT_DYNAMIC_ALLOCATION        0

/* 钩子函数相关定义。*/
#define configUSE_IDLE_HOOK                    0
#define configUSE_TICK_HOOK                    0
#define configUSE_MALLOC_FAILED_HOOK           0 // 导致嵌套外部警告
#define configCHECK_FOR_STACK_OVERFLOW         2

/* 运行时和任务统计信息收集相关定义。*/
#define configGENERATE_RUN_TIME_STATS          0
#define configUSE_TRACE_FACILITY               1 // 遗留痕迹
#define configUSE_STATS_FORMATTING_FUNCTIONS   0

/* 共同例程定义。*/
#define configUSE_CO_ROUTINES                  0
#define configMAX_CO_ROUTINE_PRIORITIES        2

/* 软件计时器相关定义。*/
#define configUSE_TIMERS                       1
#define configTIMER_TASK_PRIORITY              (configMAX_PRIORITIES-2)
#define configTIMER_QUEUE_LENGTH               32
#define configTIMER_TASK_STACK_DEPTH           configMINIMAL_STACK_SIZE

/* 可选函数-大多数链接器都会删除未使用的函数。*/
#define INCLUDE_vTaskPrioritySet               0
#define INCLUDE_uxTaskPriorityGet              0
#define INCLUDE_vTaskDelete                    0
#define INCLUDE_vTaskSuspend                   1 // 需要使用portMAX_DELAY无限期阻止队列、信号量和互斥
#define INCLUDE_xResumeFromISR                 0
#define INCLUDE_vTaskDelayUntil                1
#define INCLUDE_vTaskDelay                     1
#define INCLUDE_xTaskGetSchedulerState         0
#define INCLUDE_xTaskGetCurrentTaskHandle      0
#define INCLUDE_uxTaskGetStackHighWaterMark    0
#define INCLUDE_xTaskGetIdleTaskHandle         0
#define INCLUDE_xTimerGetTimerDaemonTaskHandle 0
#define INCLUDE_pcTaskGetTaskName              0
#define INCLUDE_eTaskGetState                  0
#define INCLUDE_xEventGroupSetBitFromISR       0
#define INCLUDE_xTimerPendFunctionCall         0

/* 定义以捕获开发期间的错误。*/
// 命中错误时停止CPU（断点），仅适用于Cortex M3、M4、M7
#if defined(__ARM_ARCH_7M__) || defined (__ARM_ARCH_7EM__)
  #define configASSERT(_exp) \
    do {\
      if ( !(_exp) ) { \
        volatile uint32_t* ARM_CM_DHCSR =  ((volatile uint32_t*) 0xE000EDF0UL); /* Cortex M核心调试->DHCSR*/ \
        if ( (*ARM_CM_DHCSR) & 1UL ) {  /* 仅在连接调试器时停止mcu*/ \
          taskDISABLE_INTERRUPTS(); \
           __asm("BKPT #0\n"); \
        }\
      }\
    } while(0)
#else
  #define configASSERT( x )
#endif

#ifdef __RX__
/* 瑞萨RX系列*/
#define vSoftwareInterruptISR					INT_Excep_ICU_SWINT
#define vTickISR								INT_Excep_CMT0_CMI0
#define configPERIPHERAL_CLOCK_HZ				(configCPU_CLOCK_HZ/2)
#define configKERNEL_INTERRUPT_PRIORITY			1
#define configMAX_SYSCALL_INTERRUPT_PRIORITY	4

#else

/* FreeRTOS挂钩NVIC向量*/
#define xPortPendSVHandler    PendSV_Handler
#define xPortSysTickHandler   SysTick_Handler
#define vPortSVCHandler       SVC_Handler

//--------------------------------------------------------------------+
// 中断嵌套行为配置。
//--------------------------------------------------------------------+
/* Cortex-M特定定义__NVIC_PRIO_BITS在core_cmx中定义。小时*/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       __NVIC_PRIO_BITS
#else
  #error "This port requires __NVIC_PRIO_BITS to be defined"
#endif

/* 在调用“设置优先级”函数时可以使用的最低中断优先级。*/
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			  ((1<<configPRIO_BITS) - 1)

/* 任何调用中断安全FreeRTOS API函数的中断服务例程都可以使用的最高中断优先级。不要从任何优先级高于此的中断调用中断安全的FREERTOS API函数！（优先级越高，数值越低。*/
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	2

/* 内核端口层本身使用的中断优先级。这些是所有Cortex-M端口的通用，不依赖任何特定的库函数。*/
#define configKERNEL_INTERRUPT_PRIORITY 		          ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY不能设置为零！！！！看见http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.*/
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	        ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#endif

#endif /* __FREERTOS_CONFIG__H */

