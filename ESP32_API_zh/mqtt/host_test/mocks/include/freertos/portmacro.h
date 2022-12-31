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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLER__

/*-----------------------------------------------------------
 * 端口特定定义。
 *
 * 此文件中的设置为给定的硬件和编译器正确配置FreeRTOS。
 *
 * 不应更改这些设置。
 *-----------------------------------------------------------
 */

/* 类型定义。*/
#define portCHAR uint8_t
#define portFLOAT float
#define portDOUBLE double
#define portLONG int32_t
#define portSHORT int16_t
#define portSTACK_TYPE uint8_t
#define portBASE_TYPE int
// 中断模块将屏蔽优先级低于阈值的中断
#define RVHAL_EXCM_LEVEL 4

typedef portSTACK_TYPE StackType_t;
typedef portBASE_TYPE BaseType_t;
typedef unsigned portBASE_TYPE UBaseType_t;

#if (configUSE_16_BIT_TICKS == 1)
typedef uint16_t TickType_t;
#define portMAX_DELAY (TickType_t)0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t)0xffffffffUL
#endif
/*------------------------------------------------------*/

/* 架构细节。*/
#define portSTACK_GROWTH (-1)
#define portTICK_PERIOD_MS ((TickType_t)(1000 / configTICK_RATE_HZ))
#define portBYTE_ALIGNMENT 16
/*-----------------------------------------------------------*/

#define portCRITICAL_NESTING_IN_TCB 0

/*
 * 向另一个核心发送一个中断，以使在其上运行的任务为更高优先级的任务让位。
 */
void vPortYieldOtherCore(BaseType_t coreid);

/*
 回调以在堆栈末尾设置观察点。调用每个上下文开关来更改堆栈监视点。
 */
void vPortSetStackWatchpoint(void *pxStackStart);

/*
 * 如果当前核心位于ISR上下文中，则返回true；低优先级ISR、中等优先级ISR或定时器滴答ISR。这里没有检测到高优先级ISR，但它们通常无法调用C代码，因此无论如何这应该不是问题。
 */
BaseType_t xPortInIsrContext(void);

/*
 * 此函数将在高优先级ISR中调用。如果当前核心在调用高优先级ISR上下文之前处于ISR上下文中，则返回true。
 */
BaseType_t xPortInterruptedFromISRContext(void);

/* “多路复用器”数据结构（自旋锁）*/
typedef struct {
    /* 所有者字段值：0-未初始化（无效）端口Mux_FREE_VAL-多路复用器空闲，可由CPU CORE_ID_REGVAL_PRO/CORE_ID_REGVAL_APP锁定-多路复用被锁定到特定核心
     *
     * 端口MUX_FREE_VAL、CORE_ID_REGVAL_PRO、CORE_ID _REGVAL_APP以外的任何值都表示损坏
     */
    uint32_t owner;
    /* count字段：如果多路复用器未锁定，则计数应为零。如果多路复用器被锁定，则计数为非零&表示多路复用器上递归锁的数量。
     */
    uint32_t count;
} portMUX_TYPE;

#define portMUX_FREE_VAL SPINLOCK_FREE

/* vPortCPUAcquireMatexTimeout（）的特殊常量*/
#define portMUX_NO_TIMEOUT SPINLOCK_WAIT_FOREVER /* 当传递给“timeout_cycles”时，如果需要，永远旋转*/
#define portMUX_TRY_LOCK SPINLOCK_NO_WAIT        /* 尝试只获取一次自旋锁*/

// 请将其与portMUX_TYPE结构定义保持同步。
#define portMUX_INITIALIZER_UNLOCKED                                                                                   \
    { .owner = portMUX_FREE_VAL, .count = 0, }

/* 调度器实用程序。*/
extern void vPortYield(void);
extern void vPortYieldFromISR(void);

#define portYIELD() vPortYield()
#define portYIELD_FROM_ISR() vPortYieldFromISR()

/* API调用内的产量（中断关闭时）意味着产量应延迟，直到中断重新启用。为了做到这一点，我们使用“跨核”中断作为触发器，在重新启用中断时在该内核上让步。这是用于触发CPU之间产量的相同中断和代码路径，尽管在这种情况下产量发生在同一CPU上。
*/
#define portYIELD_WITHIN_API() portYIELD()
/*-----------------------------------------------------------*/

/* 关键部分管理。*/
extern int vPortSetInterruptMask(void);
extern void vPortClearInterruptMask(int);

extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);

extern void esp_vApplicationIdleHook(void);
extern void esp_vApplicationTickHook(void);

#ifndef CONFIG_FREERTOS_LEGACY_HOOKS
#define vApplicationIdleHook esp_vApplicationIdleHook
#define vApplicationTickHook esp_vApplicationTickHook
#endif /* !CONFIG_FREERTOS_LEGACY_HOOKS */

/* FreeRTOS上描述的任务函数宏。org网站。*/
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters) void vFunction(void* pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters) void vFunction(void* pvParameters)

void vApplicationSleep(TickType_t xExpectedIdleTime);
#define portSUPPRESS_TICKS_AND_SLEEP(idleTime) vApplicationSleep(idleTime)

#define portNOP() //__asm易失性（“nop”）

#define portVALID_TCB_MEM(ptr)   // esp_ptr_byte_accessible（ptr）
#define portVALID_STACK_MEM(ptr) // esp_ptr_byte_accessible（ptr）

#endif //__ASSEMBLER__

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

