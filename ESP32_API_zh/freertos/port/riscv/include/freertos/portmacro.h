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
#include <stdio.h>
#include "soc/spinlock.h"
#include "soc/interrupt_core0_reg.h"
#include "soc/cpu.h"
#include "esp_attr.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"              /* FreeRTOS运行时间统计所需*/
#include "esp_heap_caps.h"
#include "esp_system.h"             /* portable.h〔refactor todo〕更新portable中的esp_get_…（）函数所需。小时*/
#include "esp_newlib.h"
#include "portbenchmark.h"

/* [refactor todo]这些includes不直接用于此文件。他们被关在里面，以防止突然的变化。移除这些。*/
#include <limits.h>
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
 * -端口类型必须放在第一位，因为它们将在此文件中进一步使用
 * ------------------------------------------------------------------------------------------------------------------ */

#define portCHAR                    uint8_t
#define portFLOAT                   float
#define portDOUBLE                  double
#define portLONG                    int32_t
#define portSHORT                   int16_t
#define portSTACK_TYPE              uint8_t
#define portBASE_TYPE               int

typedef portSTACK_TYPE              StackType_t;
typedef portBASE_TYPE               BaseType_t;
typedef unsigned portBASE_TYPE      UBaseType_t;

#if (configUSE_16_BIT_TICKS == 1)
typedef uint16_t TickType_t;
#define portMAX_DELAY (TickType_t)  0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t)  0xffffffffUL
#endif

/* FreeRTOS上描述的任务函数宏。org网站。*/
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters) void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters) void vFunction(void *pvParameters)

// 中断模块将屏蔽优先级低于阈值的中断
#define RVHAL_EXCM_LEVEL            4


/* -----------------------------------------------端口配置-------------------------------------------------
 * -每个端口提供的配置值
 * -FreeRTOS要求
 * ------------------------------------------------------------------------------------------------------------------ */

#define portCRITICAL_NESTING_IN_TCB     0
#define portSTACK_GROWTH                (-1)
#define portTICK_PERIOD_MS              ((TickType_t) (1000 / configTICK_RATE_HZ))
#define portBYTE_ALIGNMENT              16
#define portNOP() __asm volatile        (" nop ")



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

/* ----------------------旋转锁------------------------
 -为使API与SMP FreeRTOS相匹配，添加了旋转锁。单核RISC-V不需要自旋锁
 -因为单核没有原始的自旋锁数据类型，所以我们必须在这里实现一个
 * @note [重构todo]重构关键部分API，使其不再需要
 * ------------------------------------------------------ */

/**
 * @brief Spinlock对象所有者：
 *  -如果未初始化，则设置为0
 *  -空闲时设置为端口MUX_FREE_VAL
 *  -锁定时设置为CORE_ID_REGVAL_PRO或CORE_ID_REGVAL_AP
 *  -任何其他值表示损坏计数：
 *  -0（如果已解锁）
 *  -锁定时的递归计数
 *
 * @note 不是真正的自旋锁，因为单核RISC-V没有原子比较和设置指令
 * @note 保持portMUX_INITIALIZER_UNLOCKED与此结构同步
 */
typedef struct {
    uint32_t owner;
    uint32_t count;
} portMUX_TYPE;
/**<Spinlock初始值设定项*/
#define portMUX_INITIALIZER_UNLOCKED {                      \
            .owner = portMUX_FREE_VAL,                      \
            .count = 0,                                     \
        }
#define portMUX_FREE_VAL                    SPINLOCK_FREE           /**<旋转锁是免费的。[refactor todo]检查这是否仍然是必需的*/
#define portMUX_NO_TIMEOUT                  SPINLOCK_WAIT_FOREVER   /**<当传递“timeout_cycles”时，如果需要，永远旋转。[refactor todo]检查这是否仍然是必需的*/
#define portMUX_TRY_LOCK                    SPINLOCK_NO_WAIT        /**<尝试只获取一次自旋锁。[refactor todo]检查这是否仍然是必需的*/
#define portMUX_INITIALIZE(mux)    ({ \
    (mux)->owner = portMUX_FREE_VAL; \
    (mux)->count = 0; \
})

/**
 * @brief 原子比较和设置指令的包装器
 *
 * @note 不是真正的原子CAS。
 * @note [重构todo]检查我们是否还需要这个
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
 * @note 不是真正的原子CAS。
 * @note [重构todo]检查我们是否还需要这个
 * @note [refactor-todo]检查是否应重命名此函数（由于void返回类型）
 *
 * @param[inout] addr 指向目标地址的指针
 * @param[in] compare 比较值
 * @param[inout] set 指向设定值的指针
 */
static inline void uxPortCompareSetExtram(volatile uint32_t *addr, uint32_t compare, uint32_t *set);

// ------------------关键部分--------------------

/**
 * @brief 输入关键部分
 *
 * -只需禁用中断
 * -可以嵌套
 */
void vPortEnterCritical(void);

/**
 * @brief 退出关键部分
 *
 * -重新启用中断
 * -可以嵌套
 */
void vPortExitCritical(void);

// ----------------------产量-------------------------

/**
 * @brief 设置中断掩码和返回电流中断启用寄存器
 *
 * @note [refactor-todo]检查是否应重命名此函数（由于int返回类型）
 * @return int设置前的当前中断启用寄存器
 */
int vPortSetInterruptMask(void);

/**
 * @brief 清除当前中断掩码并设置给定掩码
 *
 * @param mask 中断掩码
 */
void vPortClearInterruptMask(int mask);

/**
 * @brief 从任务执行上下文切换
 *
 * @note [重构todo]ESP-IDF的其余部分应改为调用taskYield（）
 */
void vPortYield(void);

/**
 * @brief 从ISR执行上下文切换
 */
void vPortYieldFromISR(void);

/**
 * @brief 产生另一个核心
 *
 * @note 添加以与SMP API兼容
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
 * @note [refactor-todo]检查是否应该重命名此函数（由于布尔返回类型）
 * @return 真核可以产生
 * @return 假核心不能屈服
 */
static inline bool IRAM_ATTR xPortCanYield(void);

// -------------------挂钩功能----------------------

extern void esp_vApplicationIdleHook(void);
extern void esp_vApplicationTickHook(void);

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
 * @note [refactor-todo]检查是否应重命名此函数（由于uint返回类型）
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
void vPortSetStackWatchpoint(void *pxStackStart);

/**
 * @brief 获取当前核心的ID
 *
 * @note 添加以与SMP API兼容
 * @note [重构todo]IDF应该调用类似FreeRTOS的宏，而不是直接调用端口函数
 * @return BaseType_t核心ID
 */
static inline BaseType_t IRAM_ATTR xPortGetCoreID(void)
{
    return (uint32_t) cpu_hal_get_core_id();
}



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
#define pvPortMallocTcbMem(size)        pvPortMalloc(size)
#define pvPortMallocStackMem(size)      pvPortMalloc(size)

// ---------------------中断------------------------

#define portDISABLE_INTERRUPTS()            portSET_INTERRUPT_MASK_FROM_ISR()
#define portENABLE_INTERRUPTS()             portCLEAR_INTERRUPT_MASK_FROM_ISR(1)
#define portSET_INTERRUPT_MASK_FROM_ISR()                       vPortSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedStatusValue)   vPortClearInterruptMask(uxSavedStatusValue)

// ------------------关键部分--------------------

#define portENTER_CRITICAL(mux)                 {(void)mux;  vPortEnterCritical();}
#define portEXIT_CRITICAL(mux)                  {(void)mux;  vPortExitCritical();}
#define portTRY_ENTER_CRITICAL(mux, timeout)    ({  \
    (void)mux; (void)timeout;                       \
    vPortEnterCritical();                           \
    BaseType_t ret = pdPASS;                        \
    ret;                                            \
})
//在单核RISC-V中，我们可以使用相同的关键部分API
#define portENTER_CRITICAL_ISR(mux)                 portENTER_CRITICAL(mux)
#define portEXIT_CRITICAL_ISR(mux)                  portEXIT_CRITICAL(mux)
#define portTRY_ENTER_CRITICAL_ISR(mux, timeout)    portTRY_ENTER_CRITICAL(mux, timeout)

/* 在RISC-V上，ISR和非ISR情况都会导致相同的调用。我们可以重新定义此宏*/
#define portENTER_CRITICAL_SAFE(mux)    ({  \
    if (xPortInIsrContext()) {              \
        portENTER_CRITICAL_ISR(mux);        \
    } else {                                \
        portENTER_CRITICAL(mux);            \
    }                                       \
})
#define portEXIT_CRITICAL_SAFE(mux)     ({  \
    if (xPortInIsrContext()) {              \
        portEXIT_CRITICAL_ISR(mux);         \
    } else {                                \
        portEXIT_CRITICAL(mux);             \
    }                                       \
})
#define portTRY_ENTER_CRITICAL_SAFE(mux, timeout)   portENTER_CRITICAL_SAFE(mux, timeout)

// ----------------------产量-------------------------

#define portYIELD() vPortYield()
#define portYIELD_FROM_ISR() vPortYieldFromISR()
#define portEND_SWITCHING_ISR(xSwitchRequired) if(xSwitchRequired) vPortYield()
/* API调用内的产量（中断关闭时）意味着产量应延迟，直到中断重新启用。为了做到这一点，我们使用“跨核”中断作为触发器，在重新启用中断时在该内核上让步。这是用于触发CPU之间产量的相同中断和代码路径，尽管在这种情况下产量发生在同一CPU上。
*/
#define portYIELD_WITHIN_API() portYIELD()

// -------------------挂钩功能----------------------

#ifndef CONFIG_FREERTOS_LEGACY_HOOKS
#define vApplicationIdleHook    esp_vApplicationIdleHook
#define vApplicationTickHook    esp_vApplicationTickHook
#endif /* !CONFIG_FREERTOS_LEGACY_HOOKS */
#define portSUPPRESS_TICKS_AND_SLEEP(idleTime) vApplicationSleep(idleTime)

// -------------------运行时间统计信息----------------------

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE() 0
#ifdef CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
/* 粗略分辨率时间（us）*/
#define portALT_GET_RUN_TIME_COUNTER_VALUE(x)    do {x = (uint32_t)esp_timer_get_time();} while(0)
#endif



/* ---------------------------------------------内联实现------------------------------------------------
 * -forward声明的内联函数的实现
 * -应该在转发声明和FreeRTOS移植接口之后，因为实现可能同时使用这两个接口。
 * -有关非内联函数的实现，请参见port.c，port_common。c、 或其他程序集文件
 * ------------------------------------------------------------------------------------------------------------------ */

// ---------------------中断------------------------



// ----------------------旋转锁------------------------

static inline void __attribute__((always_inline)) uxPortCompareSet(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
    compare_and_set_native(addr, compare, set);
}

static inline void uxPortCompareSetExtram(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
#if defined(CONFIG_SPIRAM)
    compare_and_set_extram(addr, compare, set);
#endif
}

// ----------------------产量-------------------------

static inline bool IRAM_ATTR xPortCanYield(void)
{
    uint32_t threshold = REG_READ(INTERRUPT_CORE0_CPU_INT_THRESH_REG);
    /* 当输入关键代码时，FreeRTOS将阈值屏蔽为RVHAL_EXCM_LEVEL，并退出关键代码，将恢复阈值（1）。因此阈值<=1表示不在关键代码中
     */
    return (threshold <= 1);
}



/* ------------------------------------------------------其他---------------------------------------------------------
 * -其他移植宏
 * -这些不是FreeRTOS移植接口的端口，但由其他FreeRTOS相关组件使用
 * ------------------------------------------------------------------------------------------------------------------ */

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

#endif //__ASSEMBLER__

#endif /* PORTMACRO_H */

