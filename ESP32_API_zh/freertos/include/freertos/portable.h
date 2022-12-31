/*
 * FreeRTOS内核V10.4.3版权所有（C）2020 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org https://github.com/FreeRTOS
 *
 */

/*-----------------------------------------------------------
 * 可移植层API。必须为每个端口定义每个函数。
 *----------------------------------------------------------*/

#ifndef PORTABLE_H
#define PORTABLE_H

/* 每个FreeRTOS端口都有一个唯一的端口宏。h头文件。最初，预处理器定义用于确保预处理器找到正确的端口宏。正在使用的端口的h文件。该方案被弃用，转而支持设置编译器的include路径，以便找到正确的portmacro。h文件-不需要常量并允许portmacro。h文件位于所使用端口的任何位置。纯粹出于向后兼容性的原因，旧方法仍然有效，但为了明确新项目不应使用它，已将对端口特定常量的支持移到弃用的定义中。h头文件。*/
#include "deprecated_definitions.h"

/* 如果未定义portENTER_CRITICAL，则包括弃用的定义。h没有生成portmacro。h头文件被包括在内，它应该包括在这里。在本例中，指向正确端口宏的路径。h头文件必须设置在编译器的include路径中。*/
#ifndef portENTER_CRITICAL
    #include "freertos/portmacro.h"
#endif

#if portBYTE_ALIGNMENT == 32
    #define portBYTE_ALIGNMENT_MASK    ( 0x001f )
#endif

#if portBYTE_ALIGNMENT == 16
    #define portBYTE_ALIGNMENT_MASK    ( 0x000f )
#endif

#if portBYTE_ALIGNMENT == 8
    #define portBYTE_ALIGNMENT_MASK    ( 0x0007 )
#endif

#if portBYTE_ALIGNMENT == 4
    #define portBYTE_ALIGNMENT_MASK    ( 0x0003 )
#endif

#if portBYTE_ALIGNMENT == 2
    #define portBYTE_ALIGNMENT_MASK    ( 0x0001 )
#endif

#if portBYTE_ALIGNMENT == 1
    #define portBYTE_ALIGNMENT_MASK    ( 0x0000 )
#endif

#ifndef portBYTE_ALIGNMENT_MASK
    #error "Invalid portBYTE_ALIGNMENT definition"
#endif

#ifndef portNUM_CONFIGURABLE_REGIONS
    #define portNUM_CONFIGURABLE_REGIONS    1
#endif

#ifndef portHAS_STACK_OVERFLOW_CHECKING
    #define portHAS_STACK_OVERFLOW_CHECKING    0
#endif

#ifndef portARCH_NAME
    #define portARCH_NAME    NULL
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

#include "mpu_wrappers.h"

/*
 * 设置新任务的堆栈，以便将其置于调度程序控制之下。寄存器必须按照端口期望查找它们的顺序放置在堆栈上。
 *
 */
#if ( portUSING_MPU_WRAPPERS == 1 )
    #if ( portHAS_STACK_OVERFLOW_CHECKING == 1 )
        StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                             StackType_t * pxEndOfStack,
                                             TaskFunction_t pxCode,
                                             void * pvParameters,
                                             BaseType_t xRunPrivileged ) PRIVILEGED_FUNCTION;
    #else
        StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                             TaskFunction_t pxCode,
                                             void * pvParameters,
                                             BaseType_t xRunPrivileged ) PRIVILEGED_FUNCTION;
    #endif
#else /* 如果（端口USING_MPU_WRAPPERS==1）*/
    #if ( portHAS_STACK_OVERFLOW_CHECKING == 1 )
        StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                             StackType_t * pxEndOfStack,
                                             TaskFunction_t pxCode,
                                             void * pvParameters ) PRIVILEGED_FUNCTION;
    #else
        StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                             TaskFunction_t pxCode,
                                             void * pvParameters ) PRIVILEGED_FUNCTION;
    #endif
#endif

#ifdef configUSE_FREERTOS_PROVIDED_HEAP

/* heap_5.c用于定义每个内存区域的起始地址和大小，这些区域共同构成总的FreeRTOS堆空间。*/
typedef struct HeapRegion
{
    uint8_t * pucStartAddress;
    size_t xSizeInBytes;
} HeapRegion_t;

/* 用于从vPortGetHeapStats（）传递有关堆的信息。*/
typedef struct xHeapStats
{
    size_t xAvailableHeapSpaceInBytes;          /* 当前可用的总堆大小-这是所有可用块的总和，而不是可以分配的最大块。*/
    size_t xSizeOfLargestFreeBlockInBytes;      /* 调用vPortGetHeapStats（）时堆内所有可用块的最大大小（字节）。*/
    size_t xSizeOfSmallestFreeBlockInBytes;     /* 调用vPortGetHeapStats（）时堆内所有空闲块的最小大小（字节）。*/
    size_t xNumberOfFreeBlocks;                 /* 调用vPortGetHeapStats（）时堆中可用内存块的数量。*/
    size_t xMinimumEverFreeBytesRemaining;      /* 自系统启动以来，堆中的最小可用内存总量（所有可用块的总和）。*/
    size_t xNumberOfSuccessfulAllocations;      /* 已返回有效内存块的对pvPortMalloc（）的调用数。*/
    size_t xNumberOfSuccessfulFrees;            /* 已成功释放内存块的vPortFree（）调用次数。*/
} HeapStats_t;

/*
 * 用于定义heap_5.c使用的多个堆区域。在调用pvPortMalloc（）之前，必须调用此函数-不创建任务、队列、信号量、互斥锁、软件计时器、事件组等将导致调用pvPortMalloc。
 *
 * pxHeapRegions在HeapRegion_t结构数组中传递，每个结构都定义了可用作堆的内存区域。数组由大小为0的HeapRegions_t结构终止。具有最低起始地址的区域必须首先出现在数组中。
 */
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) PRIVILEGED_FUNCTION;

/*
 * 返回填充有当前堆状态信息的HeapStats_t结构。
 */
void vPortGetHeapStats( HeapStats_t * pxHeapStats );

/*
 * 映射到端口所需的内存管理例程。
 */
void * pvPortMalloc( size_t xSize ) PRIVILEGED_FUNCTION;
void vPortFree( void * pv ) PRIVILEGED_FUNCTION;
void vPortInitialiseBlocks( void ) PRIVILEGED_FUNCTION;
size_t xPortGetFreeHeapSize( void ) PRIVILEGED_FUNCTION;
size_t xPortGetMinimumEverFreeHeapSize( void ) PRIVILEGED_FUNCTION;

#if( configSTACK_ALLOCATION_FROM_SEPARATE_HEAP == 1 )
    void *pvPortMallocStack( size_t xSize ) PRIVILEGED_FUNCTION;
    void vPortFreeStack( void *pv ) PRIVILEGED_FUNCTION;
#else
    #define pvPortMallocStack pvPortMalloc
    #define vPortFreeStack vPortFree
#endif
#else  // configUSE_FREERTOS_PROVIDED_HEAP

/*
 * 映射到端口所需的内存管理例程。
 *
 * 注意，libc标准malloc/free也可用于非FreeRTOS特定代码，其行为与pvPortMalloc（）/vPortFree（）相同。
 */
#define pvPortMalloc malloc
#define vPortFree free
#define xPortGetFreeHeapSize esp_get_free_heap_size
#define xPortGetMinimumEverFreeHeapSize esp_get_minimum_free_heap_size

#endif

/*
 * 设置硬件，以便调度程序控制。这通常会设置滴答声中断，并为正确的滴答声频率设置计时器。
 */
BaseType_t xPortStartScheduler( void ) PRIVILEGED_FUNCTION;

/*
 * 撤消由xPortStartScheduler（）执行的任何硬件/ISR设置，以便在调度器停止执行后，硬件保持其原始状态。
 */
void vPortEndScheduler( void ) PRIVILEGED_FUNCTION;

/*
 * 操作MPU的结构和方法包含在端口层中。
 *
 * 使用xRegions中包含的内存区域信息填充xMPUSettings结构。
 */
#if ( portUSING_MPU_WRAPPERS == 1 )
    struct xMEMORY_REGION;
    void vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    const struct xMEMORY_REGION * const xRegions,
                                    StackType_t * pxBottomOfStack,
                                    uint32_t ulStackDepth ) PRIVILEGED_FUNCTION;
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTABLE_H */

