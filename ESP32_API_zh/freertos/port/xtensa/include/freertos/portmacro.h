/*
 * FreeRTOS内核V10.4.3版权所有（C）2019 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org http://aws.amazon.com/freertos
 *
 * 1个制表符==4个空格！
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifndef __ASSEMBLER__

#include "sdkconfig.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <xtensa/config/core.h>
#include <xtensa/hal.h>             /* xthal_get_ccount需要。[重构todo]改用cpu_hal*/
#include <xtensa/xtruntime.h>       /* XTOS_SET_INTLEVEL需要。[重构todo]向esp_hw_support添加通用intr函数*/
#include "xt_instr_macros.h"
#include "soc/spinlock.h"
#include "hal/cpu_hal.h"
#include "esp_private/crosscore_int.h"
#include "esp_attr.h"
#include "esp_timer.h"              /* esp_timer_get_time需要。[重构todo]在Arch之间实现这一点*/
#include "esp_newlib.h"             /* 任务中的esp_reent_init（）需要。c*/
#include "esp_heap_caps.h"
#include "esp_rom_sys.h"
#include "esp_system.h"             /* portable.h〔refactor todo〕更新portable中的esp_get_…（）函数所需。小时*/
#include "portbenchmark.h"

/* [refactor todo]这些includes不直接用于此文件。他们被关在里面，以防止突然的变化。移除这些。*/
#include <limits.h>
#include <xtensa/config/system.h>
#include <xtensa/xtensa_api.h>
#include "soc/cpu.h"
#ifdef CONFIG_LEGACY_INCLUDE_COMMON_HEADERS
#include "soc/soc_memory_layout.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



/* ---------------------------------------------------端口类型------------------------------------------------------
 * -端口特定类型。
 * -此文件中的设置为给定的硬件和编译器正确配置FreeRTOS。
 * -不应更改这些设置。
 * -端口类型在文件后面使用时必须在前面
 * ------------------------------------------------------------------------------------------------------------------ */

#define portCHAR                    int8_t
#define portFLOAT                   float
#define portDOUBLE                  double
#define portLONG                    int32_t
#define portSHORT                   int16_t
#define portSTACK_TYPE              uint8_t
#define portBASE_TYPE               int

typedef portSTACK_TYPE              StackType_t;
typedef portBASE_TYPE               BaseType_t;
typedef unsigned portBASE_TYPE      UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#endif

/* FreeRTOS上描述的任务函数宏。org网站。*/
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )  void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )        void vFunction( void *pvParameters )



/* -----------------------------------------------端口配置-------------------------------------------------
 * -每个端口提供的配置值
 * -FreeRTOS要求
 * ------------------------------------------------------------------------------------------------------------------ */

#define portCRITICAL_NESTING_IN_TCB     0
#define portSTACK_GROWTH                ( -1 )
#define portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT              4
#define portNOP()                       XT_NOP()



/* ----------------------------------------------转发声明-------------------------------------------------
 * -转发实现FreeRTOS移植接口所需的所有端口函数和宏的声明
 * -这些必须在定义/声明FreeRTOS移植接口之前
 * ------------------------------------------------------------------------------------------------------------------ */

// ---------------------中断------------------------

/**
 * @brief 检查当前核心是否在ISR上下文中
 *
 * -ISR上下文由低/中优先级ISR或时间刻度ISR组成
 * -这里没有检测到高优先级的ISR，但它们通常无法调用C代码，因此无论如何这应该不是问题。
 *
 * @note [refactor todo]检查是否应该内联
 * @return
 *  -pdTRUE，如果在ISR中
 *  -pdFALSE否则
 */
BaseType_t xPortInIsrContext(void);

/**
 * @brief 在ISR上下文中断言
 *
 * -内部断言xPortInIsrContext（）
 *
 * @note [refactor todo]检查是否仍然需要此API
 * @note [refactor todo]检查是否应该内联
 */
void vPortAssertIfInISR(void);

/**
 * @brief 检查是否在高优先级ISR的ISR上下文中
 *
 * -从高优先级ISR调用
 * -检查前一上下文（高优先级中断之前）是否在ISR上下文中（意味着低/中等优先级）
 *
 * @note [refactor todo]检查是否应该内联
 * @return
 *  -pdTRUE，如果在ISR上下文中
 *  -pdFALSE否则
 */
BaseType_t xPortInterruptedFromISRContext(void);

/**
 * @brief 以嵌套方式禁用中断（意味着从ISR调用）
 *
 * @warning 仅适用于当前CPU。
 * @return UBaseType_t上一中断级别
 */
static inline UBaseType_t xPortSetInterruptMaskFromISR(void);

/**
 * @brief 以嵌套方式重新启用中断（意味着从ISR调用）
 *
 * @warning 仅适用于当前CPU。
 * @param prev_level 上一中断级别
 */
static inline void vPortClearInterruptMaskFromISR(UBaseType_t prev_level);

/* ----------------------旋转锁------------------------
 * -对关键部分进行修改以支持SMP
 * -请参阅docs/api guides/freertos smp中的“关键部分和禁用中断”。rst了解更多详细信息
 * -备注：对于ESP32，portENTER_CCRITICAL和portENTER_CRITICAL_ISR都别名vPortEnterCritical，这意味着可以从ISR和任务上下文调用任一函数。这不是标准的FreeRTOS行为器；如果您需要与其他FreeRTOS实现兼容，请记住这一点。
 * @note [refactor todo]检查这些注释是否仍然正确
 * ------------------------------------------------------ */

typedef spinlock_t                          portMUX_TYPE;               /**<FreeRTOS关键部分使用的Spinlock类型*/
#define portMUX_INITIALIZER_UNLOCKED        SPINLOCK_INITIALIZER        /**<Spinlock初始值设定项*/
#define portMUX_FREE_VAL                    SPINLOCK_FREE               /**<旋转锁是免费的。[refactor todo]检查这是否仍然是必需的*/
#define portMUX_NO_TIMEOUT                  SPINLOCK_WAIT_FOREVER       /**<当传递“timeout_cycles”时，如果需要，永远旋转。[refactor todo]检查这是否仍然是必需的*/
#define portMUX_TRY_LOCK                    SPINLOCK_NO_WAIT            /**<尝试只获取一次自旋锁。[refactor todo]检查这是否仍然是必需的*/
#define portMUX_INITIALIZE(mux)             spinlock_initialize(mux)    /*<将自旋锁初始化为其解锁状态*/

// ------------------关键部分--------------------

/**
 * @brief 输入具有超时的SMP关键部分
 *
 * 该函数通过禁用中断，然后在指定的超时时间内执行自旋锁，从而进入SMP关键部分。
 *
 * 可以嵌套方式调用此函数。
 *
 * @note 为了减少代码大小，特意将此函数设置为非内联
 * @param mux 旋转锁
 * @param timeout 等待自旋锁超时（以CPU周期数计）。使用portMUX_NO_TIMEOUT无限期等待使用portMUX_TRY_LOCK仅获取一次自旋锁
 * @retval pdPASS关键部分已输入（采用自旋锁）
 * @retval pdFAIL如果等待自旋锁超时（如果使用portMUX_NO_TIMEOUT，则不会发生）
 */
BaseType_t xPortEnterCriticalTimeout(portMUX_TYPE *mux, BaseType_t timeout);

/**
 * @brief 输入SMP关键部分
 *
 * 此函数通过禁用中断，然后使用无限超时的自旋锁，进入SMP关键部分。
 *
 * 可以嵌套方式调用此函数
 *
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((always_inline)) vPortEnterCritical(portMUX_TYPE *mux);

/**
 * @brief 退出SMP关键部分
 *
 * 可以嵌套方式调用此函数。在嵌套的最外层，此函数将：
 *
 * -松开旋转锁
 * -恢复进入关键部分之前的先前中断级别
 *
 * 如果仍在嵌套，此函数只需减少关键嵌套计数
 *
 * @note 为了减少代码大小，特意将此函数设置为非内联
 * @param[in] mux 旋转锁
 */
void vPortExitCritical(portMUX_TYPE *mux);

/**
 * @brief xPortEnterCriticalTimeout（）的FreeRTOS兼容版本
 *
 * xPortEnterCriticalTimeout（）的兼容版本将确保仅从任务上下文中调用。否则调用中止。
 *
 * @note 为了减少代码大小，特意将此函数设置为非内联
 *
 * @param mux 旋转锁
 * @param timeout 超时
 * @return 基本类型（_t）
 */
BaseType_t xPortEnterCriticalTimeoutCompliance(portMUX_TYPE *mux, BaseType_t timeout);

/**
 * @brief vPortEnterCritical（）的FreeRTOS兼容版本
 *
 * vPortEnterCritical（）的兼容版本将确保仅从任务上下文中调用。否则调用中止。
 *
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((always_inline)) vPortEnterCriticalCompliance(portMUX_TYPE *mux);

/**
 * @brief vPortExitCritical（）的FreeRTOS兼容版本
 *
 * vPortExitCritical（）的兼容版本将确保仅从任务上下文中调用。否则调用中止。
 *
 * @note 为了减少代码大小，特意将此函数设置为非内联
 * @param[in] mux 旋转锁
 */
void vPortExitCriticalCompliance(portMUX_TYPE *mux);

/**
 * @brief 输入关键超时的安全版本
 *
 * entercritical的安全版本将自动在portTRY_ENDER_critical（）和portTRY_enter_critical_ISR（）之间进行选择
 *
 * @param mux 旋转锁
 * @param timeout 超时
 * @return 基本类型（_t）
 */
static inline BaseType_t __attribute__((always_inline)) xPortEnterCriticalTimeoutSafe(portMUX_TYPE *mux, BaseType_t timeout);

/**
 * @brief entercritical的安全版本
 *
 * entercritical的安全版本将自动在portENTER_critical（）和portENTER_critical_ISR（）之间进行选择
 *
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((always_inline)) vPortEnterCriticalSafe(portMUX_TYPE *mux);

/**
 * @brief 退出关键的安全版本
 *
 * entercritical的安全版本将自动在portEXIT_critical（）和portEXIT_critical_ISR（）之间进行选择
 *
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((always_inline)) vPortExitCriticalSafe(portMUX_TYPE *mux);

// ----------------------产量-------------------------

/**
 * @brief 执行请求的上下文切换
 *
 * -在portasm.S中定义
 *
 * @note [重构todo]ESP-IDF的其余部分应改为调用taskYield（）
 */
void vPortYield( void );

/**
 * @brief
 *
 * @note [重构todo]重构它以避免va_args
 * @param argc
 * @param ... 允许IDF原型不带参数和普通版本WITH参数的变量参数
 */
void vPortEvaluateYieldFromISR(int argc, ...);

/**
 * @brief 产生另一个核心
 *
 * -向另一个核心发送一个中断，以使在其上运行的任务为更高优先级的任务让位。
 * -也可用于产生电流芯
 *
 * @note [重构todo]将其放入私有宏中，作为其唯一调用自任务。c并且不是公共API
 * @param coreid 要屈服的岩芯ID
 */
void vPortYieldOtherCore(BaseType_t coreid);

/**
 * @brief 检查当前堆芯是否可以屈服
 *
 * -如果堆芯处于ISR或关键区段，则堆芯无法屈服
 *
 * @note [refactor todo]查看这是否可以与端口宏分开
 * @return 真核可以产生
 * @return 假核心不能屈服
 */
static inline bool IRAM_ATTR xPortCanYield(void);

// -------------------挂钩功能----------------------

extern void esp_vApplicationIdleHook(void);     /* 任务所需。c*/
extern void esp_vApplicationTickHook(void);     /* 任务所需。c*/

/**
 * @brief 在进入时调用Hook函数以消除空闲
 *
 * -在pm_impl.c中实现
 *
 * @param xExpectedIdleTime 预期空闲时间
 */
void vApplicationSleep(TickType_t xExpectedIdleTime);

// -----------------------系统--------------------------

/**
 * @brief 获取每秒的节拍率
 *
 * @note [重构todo]使其内联
 * @return uint32_t滴答频率（Hz）
 */
uint32_t xPortGetTickRateHz(void);

/**
 * @brief 设置监视点以监视堆栈的最后32个字节
 *
 * 回调以在堆栈末尾设置观察点。调用每个上下文开关来更改堆栈监视点。
 *
 * @param pxStackStart 指向堆栈起点的指针
 */
void vPortSetStackWatchpoint( void *pxStackStart );

/**
 * @brief 获取当前核心的ID
 *
 * @note [重构todo]IDF应该调用类似FreeRTOS的宏，而不是直接调用端口函数
 * @return BaseType_t核心ID
 */
static inline BaseType_t IRAM_ATTR xPortGetCoreID(void);

/**
 * @brief 原子比较和设置指令的包装器
 *
 * 此子例程将自动将*addr与“compare”进行比较。如果*addr==compare，则*addr设置为*set*set用addr的上一个值（“compare”或其他值）更新
 *
 * @warning 根据ISA文档：在某些（未指定）情况下，如果未写入mem，s32c1i指令可能会返回旧mem的“位逆”。这在ESP32上似乎没有发生（portMUX断言将失败）。
 *
 * @note [refactor todo]检查是否可以弃用
 * @note [refactor-todo]检查是否应重命名此函数（由于void返回类型）
 *
 * @param[inout] addr 指向目标地址的指针
 * @param[in] compare 比较值
 * @param[inout] set 指向设定值的指针
 */
static inline void __attribute__((always_inline)) uxPortCompareSet(volatile uint32_t *addr, uint32_t compare, uint32_t *set);

/**
 * @brief 外部RAM中原子比较和设置指令的包装器
 *
 * 原子比较和设置，但目标地址放在外部RAM中
 *
 * @note [refactor todo]检查是否可以弃用
 *
 * @param[inout] addr 指向目标地址的指针
 * @param[in] compare 比较值
 * @param[inout] set 指向设定值的指针
 */
static inline void __attribute__((always_inline)) uxPortCompareSetExtram(volatile uint32_t *addr, uint32_t compare, uint32_t *set);



/* -------------------------------------------FreeRTOS移植接口----------------------------------------------
 * -包含FreeRTOS所需的宏的所有映射
 * -大多数都在转发声明之后，因为将宏映射到声明的函数
 * -映射到转发声明的函数
 * ------------------------------------------------------------------------------------------------------------------ */

// -----------------------内存--------------------------

/**
 * @brief 任务内存分配宏
 *
 * @note 因为ROM例程不一定正确处理外部RAM中的堆栈，所以我们强制堆栈内存始终是内部的。
 * @note [refactor todo]更新portable。h与v10.4.3相匹配，以使用新的malloc原型
 */
#define portTcbMemoryCaps               (MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT)
#define portStackMemoryCaps             (MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT)
#define pvPortMallocTcbMem(size)        heap_caps_malloc(size, portTcbMemoryCaps)
#define pvPortMallocStackMem(size)      heap_caps_malloc(size, portStackMemoryCaps)

// ---------------------中断------------------------

/**
 * -仅适用于当前核心
 * -这些不能嵌套。它们应该非常小心地使用，不能从中断级别调用。
 *
 * @note [refactor todo]用更高效的版本替换XTOS_SET_INTLEVEL，如果有的话？
 */
#define portDISABLE_INTERRUPTS()            do { XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL); portbenchmarkINTERRUPT_DISABLE(); } while (0)
#define portENABLE_INTERRUPTS()             do { portbenchmarkINTERRUPT_RESTORE(0); XTOS_SET_INTLEVEL(0); } while (0)

/**
 * 启用/禁用中断的ISR版本
 */
#define portSET_INTERRUPT_MASK_FROM_ISR()                   xPortSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(prev_level)       vPortClearInterruptMaskFromISR(prev_level)

#define portASSERT_IF_IN_ISR() vPortAssertIfInISR()

// ------------------关键部分--------------------

/**
 * @brief FreeRTOS关键部分宏
 *
 * -为SMP添加了自旋锁参数
 * -可以嵌套
 * -如果ISR上下文中使用了常规关键部分API，则合规性版本将进行断言
 * -可以从任一上下文调用安全版本
 */
#ifdef CONFIG_FREERTOS_CHECK_PORT_CRITICAL_COMPLIANCE
#define portTRY_ENTER_CRITICAL(mux, timeout)        xPortEnterCriticalTimeoutCompliance(mux, timeout)
#define portENTER_CRITICAL(mux)                     vPortEnterCriticalCompliance(mux)
#define portEXIT_CRITICAL(mux)                      vPortExitCriticalCompliance(mux)
#else
#define portTRY_ENTER_CRITICAL(mux, timeout)        xPortEnterCriticalTimeout(mux, timeout)
#define portENTER_CRITICAL(mux)                     vPortEnterCritical(mux)
#define portEXIT_CRITICAL(mux)                      vPortExitCritical(mux)
#endif /* CONFIG_FREERTOS_CHECK_PORT_CRITICAL_COMPLIANCE */

#define portTRY_ENTER_CRITICAL_ISR(mux, timeout)    xPortEnterCriticalTimeout(mux, timeout)
#define portENTER_CRITICAL_ISR(mux)                 vPortEnterCritical(mux)
#define portEXIT_CRITICAL_ISR(mux)                  vPortExitCritical(mux)

#define portTRY_ENTER_CRITICAL_SAFE(mux, timeout)   xPortEnterCriticalTimeoutSafe(mux)
#define portENTER_CRITICAL_SAFE(mux)                vPortEnterCriticalSafe(mux)
#define portEXIT_CRITICAL_SAFE(mux)                 vPortExitCriticalSafe(mux)

// ----------------------产量-------------------------

#define portYIELD() vPortYield()

/**
 * @note    下面的宏可以在传递单个参数时使用，也可以在没有任何参数的情况下使用，它是为了支持ISR内部portYIELD的两种用法而开发的。任何其他使用形式都可能导致不期望的行为
 *
 * @note [重构todo]重构它以避免va_args
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define portYIELD_FROM_ISR(...) vPortEvaluateYieldFromISR(portGET_ARGUMENT_COUNT(__VA_ARGS__) __VA_OPT__(,) __VA_ARGS__)
#else
#define portYIELD_FROM_ISR(...) vPortEvaluateYieldFromISR(portGET_ARGUMENT_COUNT(__VA_ARGS__), ##__VA_ARGS__)
#endif

/* API调用内的产量（中断关闭时）意味着产量应延迟，直到中断重新启用。

   为了做到这一点，我们使用“跨核”中断作为触发器，在重新启用中断时在该内核上让步。这是用于触发CPU之间产量的相同中断和代码路径，尽管在这种情况下产量发生在同一CPU上。
*/
#define portYIELD_WITHIN_API() esp_crosscore_int_send_yield(xPortGetCoreID())

// -------------------挂钩功能----------------------

#ifndef CONFIG_FREERTOS_LEGACY_HOOKS
#define vApplicationIdleHook esp_vApplicationIdleHook
#define vApplicationTickHook esp_vApplicationTickHook
#endif /* !CONFIG_FREERTOS_LEGACY_HOOKS */

#define portSUPPRESS_TICKS_AND_SLEEP(idleTime) vApplicationSleep(idleTime)

// -------------------运行时间统计信息----------------------

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

/**
 * -精细解析使用帐户
 * -ALT是粗略的，使用esp_timer
 * @note [重构todo]使fine和alt计时器互斥
 */
#define portGET_RUN_TIME_COUNTER_VALUE() xthal_get_ccount()
#ifdef CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
#define portALT_GET_RUN_TIME_COUNTER_VALUE(x) do {x = (uint32_t)esp_timer_get_time();} while(0)
#endif

// --------------优化的任务选择-----------------

#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
/* 检查配置。*/
#if( configMAX_PRIORITIES > 32 )
#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice.
#endif

/* 在位图中存储/清除就绪优先级。*/
#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )
#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )
#endif /* 配置端口选项任务选择*/



/* ---------------------------------------------内联实现------------------------------------------------
 * -forward声明的内联函数的实现
 * -应该在转发声明和FreeRTOS移植接口之后，因为实现可能同时使用这两个接口。
 * -有关非内联函数的实现，请参阅port.c
 * ------------------------------------------------------------------------------------------------------------------ */

// ---------------------中断------------------------

static inline UBaseType_t __attribute__((always_inline)) xPortSetInterruptMaskFromISR(void)
{
    UBaseType_t prev_int_level = XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL);
    portbenchmarkINTERRUPT_DISABLE();
    return prev_int_level;
}

static inline void __attribute__((always_inline)) vPortClearInterruptMaskFromISR(UBaseType_t prev_level)
{
    portbenchmarkINTERRUPT_RESTORE(prev_level);
    XTOS_RESTORE_JUST_INTLEVEL(prev_level);
}

// ------------------关键部分--------------------

static inline void __attribute__((always_inline)) vPortEnterCritical(portMUX_TYPE *mux)
{
    xPortEnterCriticalTimeout(mux, portMUX_NO_TIMEOUT);
}

static inline void __attribute__((always_inline)) vPortEnterCriticalCompliance(portMUX_TYPE *mux)
{
    xPortEnterCriticalTimeoutCompliance(mux, portMUX_NO_TIMEOUT);
}

static inline BaseType_t __attribute__((always_inline)) xPortEnterCriticalTimeoutSafe(portMUX_TYPE *mux, BaseType_t timeout)
{
    BaseType_t ret;
    if (xPortInIsrContext()) {
        ret = portTRY_ENTER_CRITICAL_ISR(mux, timeout);
    } else {
        ret = portTRY_ENTER_CRITICAL(mux, timeout);
    }
    return ret;
}

static inline void __attribute__((always_inline)) vPortEnterCriticalSafe(portMUX_TYPE *mux)
{
    xPortEnterCriticalTimeoutSafe(mux, portMUX_NO_TIMEOUT);
}

static inline void __attribute__((always_inline)) vPortExitCriticalSafe(portMUX_TYPE *mux)
{
    if (xPortInIsrContext()) {
        portEXIT_CRITICAL_ISR(mux);
    } else {
        portEXIT_CRITICAL(mux);
    }
}

// ----------------------产量-------------------------

static inline bool IRAM_ATTR xPortCanYield(void)
{
    uint32_t ps_reg = 0;

    //获取PS（处理器状态）寄存器的当前值
    RSR(PS, ps_reg);

    /*
     * intlevel=（ps_reg&0xf）；excm=（ps_reg>>4）&0x1；CINTLEVEL为max（excm EXCMLEVEL，INTLEVEL），其中EXCMLEVE为3。然而，只需返回true，只有INTLEVEL为零。
     */

    return ((ps_reg & PS_INTLEVEL_MASK) == 0);
}

// -----------------------系统--------------------------

static inline BaseType_t IRAM_ATTR xPortGetCoreID(void)
{
    return (uint32_t) cpu_hal_get_core_id();
}

static inline void __attribute__((always_inline)) uxPortCompareSet(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
    compare_and_set_native(addr, compare, set);
}

static inline void __attribute__((always_inline)) uxPortCompareSetExtram(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
#ifdef CONFIG_SPIRAM
    compare_and_set_extram(addr, compare, set);
#endif
}



/* ------------------------------------------------------其他---------------------------------------------------------
 * -其他移植宏
 * -这些不是FreeRTOS移植接口的端口，但由其他FreeRTOS相关组件使用
 * -[重构todo]通过修改TCB删除对MPU包装器的依赖
 * ------------------------------------------------------------------------------------------------------------------ */

// --------------------协处理器-----------------------

// 当定义协处理器时，我们维护一个指向协处理器区域的指针。
// 我们目前使用一个黑客：在TCB块中重新定义字段xMPU_SETTINGS作为一个结构，可以保存：
// MPU包装器、协处理器区域指针、跟踪代码结构等（如果需要）。
// 该字段通常用于内存保护。FreeRTOS应创建另一个通用字段。
typedef struct {
#if XCHAL_CP_NUM > 0
    volatile StackType_t *coproc_area; // 指向协处理器保存区域的指针；必须是第一个
#endif

#if portUSING_MPU_WRAPPERS
    // 此处定义mpu_settings，它取决于端口
    int mpu_setting; // 这里只是一个虚设的例子；MPU尚未移植到Xtensa
#endif
} xMPU_SETTINGS;

// 即使未定义MPU，也可以使用MPU_wrappers（警告：不应访问MPU_setting；否则将其移到xMPU_SETTINGS以上）
#if (XCHAL_CP_NUM > 0) && !portUSING_MPU_WRAPPERS   // 如果未使用MPU包装器，我们仍然需要分配协处理区域
#undef portUSING_MPU_WRAPPERS
#define portUSING_MPU_WRAPPERS 1   // 使其能够分配协处理区域
#define MPU_WRAPPERS_H             // 覆盖mpu_wrapper。h禁用不需要的代码
#define PRIVILEGED_FUNCTION
#define PRIVILEGED_DATA
#endif

void _xt_coproc_release(volatile void *coproc_sa_base);

/*
 * 操作MPU的结构和方法包含在端口层中。
 *
 * 使用xRegions中包含的内存区域信息填充xMPUSettings结构。
 */
#if( portUSING_MPU_WRAPPERS == 1 )
struct xMEMORY_REGION;
void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION *const xRegions, StackType_t *pxBottomOfStack, uint32_t usStackDepth ) PRIVILEGED_FUNCTION;
void vPortReleaseTaskMPUSettings( xMPU_SETTINGS *xMPUSettings );
#endif

// --------------------VA_ARGS产量----------------------

/**
 * 用于计算__VA_ARGS__的参数数量的宏，该__VA_ARGS__用于支持带或不带参数的端口YIELD_FROM_ISR。宏仅统计0或1个参数。
 *
 * 在未来，我们希望切换到C++20。我们还希望与clang兼容。因此，我们提供了以下宏的两个版本，它们使用可变参数。第一个是使用GNU扩展##__VA_ARGS__。第二种是使用C++20特性__VA_OPT__（，）。这允许用户使用标准C++20而不是GNU扩展来编译代码。在C++20以下，我们还没有找到使用##__VA_ARGS__的好替代方案。
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define portGET_ARGUMENT_COUNT(...) portGET_ARGUMENT_COUNT_INNER(0 __VA_OPT__(,) __VA_ARGS__,1,0)
#else
#define portGET_ARGUMENT_COUNT(...) portGET_ARGUMENT_COUNT_INNER(0, ##__VA_ARGS__,1,0)
#endif
#define portGET_ARGUMENT_COUNT_INNER(zero, one, count, ...) count

_Static_assert(portGET_ARGUMENT_COUNT() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments");
_Static_assert(portGET_ARGUMENT_COUNT(1) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument");

// --------------------堆相关-----------------------

/**
 * @brief 检查给定内存块是否可用于存储任务的TCB
 *
 * -在port_common.c中定义
 *
 * @param ptr 指向内存的指针
 * @return 真内存可用于存储TCB
 * @return false否则
 */
bool xPortCheckValidTCBMem(const void *ptr);

/**
 * @brief 检查给定内存块是否可用于存储任务堆栈
 *
 * -在port_common.c中定义
 *
 * @param ptr 指向内存的指针
 * @return true内存可用于存储任务堆栈
 * @return false否则
 */
bool xPortcheckValidStackMem(const void *ptr);

#define portVALID_TCB_MEM(ptr) xPortCheckValidTCBMem(ptr)
#define portVALID_STACK_MEM(ptr) xPortcheckValidStackMem(ptr)



/* ----------------------------------------------------弃用------------------------------------------------------
 * -此处包含不推荐使用的宏的拉入标头
 * ------------------------------------------------------------------------------------------------------------------ */

#include "portmacro_deprecated.h"

#ifdef __cplusplus
}
#endif

#endif // __ASSEMBLER__

#endif /* PORTMACRO_H */

