/*
    FreeRTOS V10-版权所有（C）2021 Real Time Engineers Ltd.保留所有权利

    访问http://www.FreeRTOS.org以确保您使用的是最新版本。

    此文件是FreeRTOS发行版的一部分。

    FreeRTOS是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证（第2版）条款重新分发和/或修改它>>！并由！修改<<FreeRTOS异常。

	*************************************************************************** >>! 注意：包括对GPL的修改，以允许您！分发一个包含FreeRTOS的组合作品，而不是！有义务提供专有组件的源代码！在FreeRTOS内核之外<<
	***************************************************************************
 FreeRTOS的发布是希望它有用，但没有任何保证；甚至没有适销性或特定用途适用性的隐含保证。完整许可文本可通过以下链接获得：http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费但专业开发的、*健壮、严格质量控制、受支持的跨平台软件，它不仅是市场领导者，而且是行业的实际标准。
     *                                                                       *
     *    通过购买FreeRTOS教程书、参考手册或两者，帮助您快速入门，同时帮助*支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation 
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html-有问题吗？首先阅读常见问题解答页面“我的应用程序无法运行，可能有什么问题？”。您是否定义了configASSERT（）？

http://www.FreeRTOS.org/support-作为免费获得此顶级嵌入式软件的回报，我们请求您通过参加支持论坛来帮助我们的全球社区。

http://www.FreeRTOS.org/training-投资培训可以让您的团队尽早提高生产力。现在，您可以直接从实时工程师有限公司（Real Time Engineers Ltd）首席执行官理查德·巴里（Richard Barry）那里接受FreeRTOS培训，他是世界领先RTOS领域的世界权威。

    http://www.FreeRTOS.org/plus-一系列FreeRTOS生态系统产品，包括FreeRTOS+Trace（一种不可或缺的生产力工具）、DOS兼容的FAT文件系统以及我们的小型线程感知UDP/IP堆栈。

    http://www.FreeRTOS.org/labs-新的FreeRTOS产品将在哪里孵化。快来试试FreeRTOS+TCP，这是我们针对FreeRTOS的新开源TCP/IP堆栈。

    http://www.OpenRTOS.com-Real Time Engineers ltd.将FreeRTOS授权给High Integrity Systems ltd.，以OpenRTOS品牌进行销售。低成本OpenRTOS许可证提供了报价支持、赔偿和商业中间件。

    http://www.SafeRTOS.com-高完整性系统还提供安全工程和独立SIL3认证版本，用于需要可证明可靠性的安全和关键任务应用。

    1个制表符==4个空格！
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "sdkconfig.h"

/* 对于可能的和不可能的*/
#include "esp_compiler.h"

// 特定于拱门的FreeRTOSConfig_arch。h在端口/<arch>/include中。
#include "freertos/FreeRTOSConfig_arch.h"

#if !(defined(FREERTOS_CONFIG_XTENSA_H) \
        || defined(FREERTOS_CONFIG_RISCV_H) \
        || defined(FREERTOS_CONFIG_LINUX_H))
#error "Needs architecture-speific FreeRTOSConfig.h!"
#endif

#ifndef CONFIG_FREERTOS_UNICORE
#define portNUM_PROCESSORS                              2
#else
#define portNUM_PROCESSORS                              1
#endif

#define portUSING_MPU_WRAPPERS                          0
#define configUSE_MUTEX                                 1

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS CONFIG_FREERTOS_THREAD_LOCAL_STORAGE_POINTERS
#define configTHREAD_LOCAL_STORAGE_DELETE_CALLBACKS     1

/* configASSERT行为*/
#ifndef __ASSEMBLER__
#include <assert.h>

// 如果设置了CONFIG_FREERTOS_ASSERT_DISABLE，则稍后在FREERTOS中将configASSERT定义为空。h和宏
// configASSERT_DEFINED保持未设置（意味着避免了某些警告）

#if defined(CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE)
#define configASSERT(a) if (unlikely(!(a))) {                               \
        esp_rom_printf("%s:%d (%s)- assert failed!\n", __FILE__, __LINE__,  \
                   __FUNCTION__);                                           \
    }
#elif defined(CONFIG_FREERTOS_ASSERT_FAIL_ABORT)
#define configASSERT(a) assert(a)
#endif

#if CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
#define UNTESTED_FUNCTION() { esp_rom_printf("Untested FreeRTOS function %s\r\n", __FUNCTION__); configASSERT(false); } while(0)
#else
#define UNTESTED_FUNCTION()
#endif

#endif /* 定义__装配工__*/

/*-----------------------------------------------------------
 * 特定于应用程序的定义。
 *
 * 这些定义应根据您的特定硬件和应用程序需求进行调整。
 *
 * 请注意，默认堆大小特意保持较小，以便对于内存有限的配置，构建更有可能成功。
 *
 * 这些参数在FreeRTOS上提供的FreeRTOS API文档的“配置”部分中进行了描述。org网站。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                            1
#define configUSE_IDLE_HOOK                             1
#define configUSE_TICK_HOOK                             1
#define configRECORD_STACK_HIGH_ADDRESS                 1
#define configTICK_RATE_HZ                              ( CONFIG_FREERTOS_HZ )

/* 这会影响搜索最高优先级的速度*/
#define configMAX_PRIORITIES                            ( 25 )

/* 影响最小堆栈大小的各种因素*/

/* 较高的堆栈检查器模式会导致每个函数调用的开销*/
#if CONFIG_STACK_CHECK_ALL || CONFIG_STACK_CHECK_STRONG
#define configSTACK_OVERHEAD_CHECKER                    256
#else
#define configSTACK_OVERHEAD_CHECKER                    0
#endif

/* 禁用优化后，调度程序使用额外的堆栈*/
#if CONFIG_COMPILER_OPTIMIZATION_NONE
#define configSTACK_OVERHEAD_OPTIMIZATION               320
#else
#define configSTACK_OVERHEAD_OPTIMIZATION               0
#endif

/* apptrace mdule增加了最小堆栈使用量*/
#if CONFIG_APPTRACE_ENABLE
#define configSTACK_OVERHEAD_APPTRACE                   1280
#else
#define configSTACK_OVERHEAD_APPTRACE                   0
#endif

/* 堆栈监视点将最小可用堆栈大小减少最多60字节。请参阅Kconfig中的FreeRTOS FreeRTOS_WATTCHPOINT_END_OF_STACK选项。*/
#if CONFIG_FREERTOS_WATCHPOINT_END_OF_STACK
#define configSTACK_OVERHEAD_WATCHPOINT                   60
#else
#define configSTACK_OVERHEAD_WATCHPOINT                   0
#endif

#define configSTACK_OVERHEAD_TOTAL (                                    \
                                    configSTACK_OVERHEAD_CHECKER +      \
                                    configSTACK_OVERHEAD_OPTIMIZATION + \
                                    configSTACK_OVERHEAD_APPTRACE +     \
                                    configSTACK_OVERHEAD_WATCHPOINT     \
                                                                        )

#define configMINIMAL_STACK_SIZE                        (768 + configSTACK_OVERHEAD_TOTAL)

#ifndef configIDLE_TASK_STACK_SIZE
#define configIDLE_TASK_STACK_SIZE CONFIG_FREERTOS_IDLE_TASK_STACKSIZE
#endif

/* 最小堆大小，以确保示例可以在内存有限的配置上运行。调整它以适合您的系统。*/


//我们将堆定义为跨越所有非静态分配的共享RAM。待办事项：确保有
//是在线程外运行时留给应用程序和主cpu的一些空间。
#define configAPPLICATION_ALLOCATED_HEAP                1
#define configTOTAL_HEAP_SIZE                           (&_heap_end - &_heap_start)//（（大小_t）（64*1024））

#define configMAX_TASK_NAME_LEN                         ( CONFIG_FREERTOS_MAX_TASK_NAME_LEN )

#ifdef CONFIG_FREERTOS_USE_TRACE_FACILITY
#define configUSE_TRACE_FACILITY                        1       /* 由uxTaskGetSystemState（）和其他跟踪工具函数使用*/
#endif

#ifdef CONFIG_FREERTOS_USE_STATS_FORMATTING_FUNCTIONS
#define configUSE_STATS_FORMATTING_FUNCTIONS            1   /* 由vTaskList（）使用*/
#endif

#ifdef CONFIG_FREERTOS_VTASKLIST_INCLUDE_COREID
#define configTASKLIST_INCLUDE_COREID                   1
#endif

#ifdef CONFIG_FREERTOS_GENERATE_RUN_TIME_STATS
#define configGENERATE_RUN_TIME_STATS                   1       /* 由vTaskGetRunTimeStats（）使用*/
#endif

#define configBENCHMARK                                 0
#define configUSE_16_BIT_TICKS                          0
#define configIDLE_SHOULD_YIELD                         0
#define configQUEUE_REGISTRY_SIZE                       CONFIG_FREERTOS_QUEUE_REGISTRY_SIZE

#define configUSE_MUTEXES                               1
#define configUSE_RECURSIVE_MUTEXES                     1
#define configUSE_COUNTING_SEMAPHORES                   1

#if CONFIG_FREERTOS_CHECK_STACKOVERFLOW_NONE
#define configCHECK_FOR_STACK_OVERFLOW                  0
#elif CONFIG_FREERTOS_CHECK_STACKOVERFLOW_PTRVAL
#define configCHECK_FOR_STACK_OVERFLOW                  1
#elif CONFIG_FREERTOS_CHECK_STACKOVERFLOW_CANARY
#define configCHECK_FOR_STACK_OVERFLOW                  2
#endif


/* 共同例程定义。*/
#define configUSE_CO_ROUTINES                           0
#define configMAX_CO_ROUTINE_PRIORITIES                 ( 2 )

/* 将以下定义设置为1以包含API函数，或设置为0以排除API函数。*/

#define INCLUDE_vTaskPrioritySet                        1
#define INCLUDE_uxTaskPriorityGet                       1
#define INCLUDE_vTaskDelete                             1
#define INCLUDE_vTaskCleanUpResources                   0
#define INCLUDE_vTaskSuspend                            1
#define INCLUDE_vTaskDelayUntil                         1
#define INCLUDE_vTaskDelay                              1
#define INCLUDE_uxTaskGetStackHighWaterMark             1
#define INCLUDE_pcTaskGetTaskName                       1
#define INCLUDE_xTaskGetIdleTaskHandle                  1
#define INCLUDE_pxTaskGetStackStart                     1
#define INCLUDE_eTaskGetState                           1
#define INCLUDE_xTaskAbortDelay                         1
#define INCLUDE_xTaskGetHandle                          1
#define INCLUDE_xSemaphoreGetMutexHolder                1
#define INCLUDE_xTimerPendFunctionCall                  1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle          0   //目前不需要此API

/* 滴答声中断运行的优先级。这可能应该保持在1。*/
#define configKERNEL_INTERRUPT_PRIORITY                 1

#if !CONFIG_IDF_TARGET_LINUX
#define configUSE_NEWLIB_REENTRANT                      1
#endif

#define configSUPPORT_DYNAMIC_ALLOCATION                1
#define configSUPPORT_STATIC_ALLOCATION                 1

#ifndef __ASSEMBLER__
#if CONFIG_FREERTOS_ENABLE_STATIC_TASK_CLEAN_UP
extern void vPortCleanUpTCB ( void *pxTCB );
#define portCLEAN_UP_TCB( pxTCB )           vPortCleanUpTCB( pxTCB )
#endif
#endif

/* 测试FreeRTOS计时器（带计时器任务）等。*/
/* 如果禁用此标志，某些文件将无法编译*/
#define configUSE_TIMERS                                1
#define configTIMER_TASK_PRIORITY                       CONFIG_FREERTOS_TIMER_TASK_PRIORITY
#define configTIMER_QUEUE_LENGTH                        CONFIG_FREERTOS_TIMER_QUEUE_LENGTH
#define configTIMER_TASK_STACK_DEPTH                    CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH

#define configUSE_QUEUE_SETS                            1

#define configUSE_TICKLESS_IDLE                         CONFIG_FREERTOS_USE_TICKLESS_IDLE
#if configUSE_TICKLESS_IDLE
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP           CONFIG_FREERTOS_IDLE_TIME_BEFORE_SLEEP
#endif //配置_TICKLESS_IDLE


#if CONFIG_FREERTOS_ENABLE_TASK_SNAPSHOT
#define configENABLE_TASK_SNAPSHOT                      1
#endif
#ifndef configENABLE_TASK_SNAPSHOT
#define configENABLE_TASK_SNAPSHOT                      0
#endif

#if CONFIG_SYSVIEW_ENABLE
#ifndef __ASSEMBLER__
#include "SEGGER_SYSVIEW_FreeRTOS.h"
#undef INLINE // 避免重新定义
#endif /* 定义__装配工__*/
#endif

#if CONFIG_FREERTOS_CHECK_MUTEX_GIVEN_BY_OWNER
#define configCHECK_MUTEX_GIVEN_BY_OWNER                1
#else
#define configCHECK_MUTEX_GIVEN_BY_OWNER                0
#endif


#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H       1

#define configTASK_NOTIFICATION_ARRAY_ENTRIES           1

// 4.4的向后兼容性
#define xTaskRemoveFromUnorderedEventList vTaskRemoveFromUnorderedEventList

#define configNUM_CORES                                 portNUM_PROCESSORS

#endif /* FREERTOS_CONFIG_H */

