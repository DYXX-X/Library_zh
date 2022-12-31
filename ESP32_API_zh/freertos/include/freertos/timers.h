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


#ifndef TIMERS_H
#define TIMERS_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h must appear in source files before include timers.h"
#endif

/*lint-save-e537只有当应用程序代码恰好也包含task.h时，才包含此标头。*/
#include "task.h"
/*棉绒-还原*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * MACROS AND DEFINITIONS
 *----------------------------------------------------------*/

/* 可以在计时器队列上发送/接收的命令的ID。这些只能通过构成公共软件计时器API的宏来使用，如下所述。从中断发送的命令必须使用最高的数字，因为tmrFIRST_from_ISR_COMMAND用于确定是否应使用队列发送函数的任务或中断版本。*/
#define tmrCOMMAND_EXECUTE_CALLBACK_FROM_ISR    ( ( BaseType_t ) -2 )
#define tmrCOMMAND_EXECUTE_CALLBACK             ( ( BaseType_t ) -1 )
#define tmrCOMMAND_START_DONT_TRACE             ( ( BaseType_t ) 0 )
#define tmrCOMMAND_START                        ( ( BaseType_t ) 1 )
#define tmrCOMMAND_RESET                        ( ( BaseType_t ) 2 )
#define tmrCOMMAND_STOP                         ( ( BaseType_t ) 3 )
#define tmrCOMMAND_CHANGE_PERIOD                ( ( BaseType_t ) 4 )
#define tmrCOMMAND_DELETE                       ( ( BaseType_t ) 5 )

#define tmrFIRST_FROM_ISR_COMMAND               ( ( BaseType_t ) 6 )
#define tmrCOMMAND_START_FROM_ISR               ( ( BaseType_t ) 6 )
#define tmrCOMMAND_RESET_FROM_ISR               ( ( BaseType_t ) 7 )
#define tmrCOMMAND_STOP_FROM_ISR                ( ( BaseType_t ) 8 )
#define tmrCOMMAND_CHANGE_PERIOD_FROM_ISR       ( ( BaseType_t ) 9 )


/**
 * 引用软件计时器的类型。例如，对xTimerCreate（）的调用返回一个TimerHandle_t变量，该变量可用于在调用其他软件计时器API函数（例如，xTimerStart（）、xTimerReset（）等）时引用主题计时器。
 */
struct tmrTimerControl; /* 旧的命名约定用于防止破坏内核感知调试器。*/
#ifdef ESP_PLATFORM // IDF-3768
typedef void* TimerHandle_t;
#else
typedef struct tmrTimerControl * TimerHandle_t;
#endif // ESP_PLATFORM
/*
 * 定义计时器回调函数必须符合的原型。
 */
typedef void (* TimerCallbackFunction_t)( TimerHandle_t xTimer );

/*
 * 定义与xTimerEndFunctionCallFromISR（）函数一起使用的函数必须符合的原型。
 */
typedef void (* PendedFunction_t)( void *,
                                   uint32_t );

/**
 * TimerHandle_t xTimerCreate（const char*const pcTimerName，TickType_t xtimerPeriodnTicks，UBaseType_t uxAutoReload，void pvTimerID，TimerCallbackFunction_t pxCallbackFunction）；
 *
 * 创建一个新的软件计时器实例，并返回一个句柄，通过该句柄可以引用创建的软件计时器。
 *
 * 在FreeRTOS实现内部，软件计时器使用一块内存，其中存储计时器数据结构。如果使用xTimerCreate（）创建软件计时器，则所需的内存将在xTimerCreate（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xTimerCreateStatic（）创建软件计时器，则应用程序编写器必须提供软件计时器将使用的内存。因此，xTimerCreateStatic（）允许在不使用任何动态内存分配的情况下创建软件计时器。
 *
 * 计时器是在休眠状态下创建的。xTimerStart（）、xTimerReset（）、xDimerStartFromISR（）、xMimerResetFromISR）、xTimerChangePeriod（）和xTimerChangePeriodFromISR API函数都可以用于将计时器转换为活动状态。
 *
 * @param pcTimerName 分配给计时器的文本名称。这样做纯粹是为了帮助调试。内核本身只通过其句柄引用计时器，而从不通过其名称。
 *
 * @param xTimerPeriodInTicks 计时器周期。时间以刻度周期定义，因此常量portTICK_PERIOD_MS可用于转换以毫秒为单位指定的时间。例如，如果计时器必须在100个刻度后过期，则xTimerPeriodnTicks应设置为100。或者，如果计时器在500ms后过期，那么xPeriod可以设置为（500/portTICK_PERIOD_MS），前提是configTICK_RATE_HZ小于或等于1000。时间计时器周期必须大于0。
 *
 * @param uxAutoReload 如果uxAutoReload设置为pdTRUE，则计时器将以xTimerPeriodTicks参数设置的频率重复过期。如果uxAutoReload设置为pdFALSE，则计时器将是一次性计时器，并在到期后进入休眠状态。
 *
 * @param pvTimerID 分配给正在创建的计时器的标识符。通常，当同一个回调函数分配给多个计时器时，这将在计时器回调函数中用于标识哪个计时器过期。
 *
 * @param pxCallbackFunction 计时器过期时要调用的函数。回调函数必须具有TimerCallbackFunction_t定义的原型，即“void vCallbackFunction（TimerHandle_t xTimer）；”。
 *
 * @return 如果计时器成功创建，则返回新创建的计时器的句柄。如果无法创建计时器（因为剩余的FreeRTOS堆不足以分配计时器结构，或者计时器周期设置为0），则返回NULL。
 *
 * 示例用法：
 * @verbatim #定义NUM_TIMERS 5
 *
 * //用于保存已创建计时器句柄的数组。TimerHandle_t xTimers[NUM_TIMERS]；
 *
 * //一个数组，用于保存每个计时器过期的次数计数。int32_t lExpireCounters[NUM_TIMERS]=｛0｝；
 *
 * //定义将由多个计时器实例使用的回调函数。//回调函数只计算//相关计时器过期的次数，并在计时器过期//10次后停止计时器。void vTimerCallback（TimerHandle_t pxTimer）｛int32_t lArrayIndex；const int32\ut xMaxExpiryCountBeforeStopping=10；
 *
 *     //如果pxTimer参数为NULL，可以选择执行某些操作。configASSERT（pxTimer）；
 *
 *     //哪个计时器过期？lArrayIndex=（int32_t）pvTimerGetTimerID（pxTimer）；
 *
 *     //增加pxTimer过期的次数。lExpireCounters[lArrayIndex]+=1；
 *
 *     //如果计时器已过期10次，则停止其运行。if（lExpireCounters[lArrayIndex]==xMaxExpiryCountBeforeStopping）｛//如果从//计时器回调函数调用计时器API函数，请不要使用块时间，因为这样做可能会导致死锁！xTimerStop（pxTimer，0）；｝｝
 *
 * void main（void）{int32_tx；
 *
 *     //创建然后启动一些计时器。在调度器//启动之前启动计时器意味着定时器将在调度器启动时立即开始运行。for（x=0；x<NUM_TIMERS；x++）｛xTimers[x]=xTimerCreate（“Timer”，//只是一个文本名称，内核不使用。（100 x），//以ticks为单位的计时器周期。pdTRUE，//计时器将在过期时自动重新加载。（void）x，//为每个计时器分配一个与其数组索引相等的唯一id。vTimerCallback//每个计时器在过期时调用相同的回调。）；
 *
 *         if（xTimers[x]==NULL）｛//计时器未创建。｝else｛//启动计时器。未指定任何块时间，即使指定了块时间，//也会被忽略，因为计划程序尚未//启动。if（xTimerStart（xTimers[x]，0）！=pdPASS）｛//计时器无法设置为活动状态。｝｝
 *
 *     //…//在此处创建任务。//。。。
 *
 *     //启动调度器将启动计时器，因为它们已经//设置为活动状态。vTaskStartScheduler（）；
 *
 *     //不应该到达这里。对于（；；）；}
 * @endverbatim
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    TimerHandle_t xTimerCreate( const char * const pcTimerName, /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
                                const TickType_t xTimerPeriodInTicks,
                                const UBaseType_t uxAutoReload,
                                void * const pvTimerID,
                                TimerCallbackFunction_t pxCallbackFunction ) PRIVILEGED_FUNCTION;
#endif

/**
 * TimerHandle_t xTimerCreateStatic（const char*const pcTimerName，TickType_t xtimerPeriodTicks，UBaseType_t uxAutoReload，void pvTimerID，TimerCallbackFunction_t pxCallbackFunction，StaticTimer_t pxTimerBuffer）；
 *
 * 创建一个新的软件计时器实例，并返回一个句柄，通过该句柄可以引用创建的软件计时器。
 *
 * 在FreeRTOS实现内部，软件计时器使用一块内存，其中存储计时器数据结构。如果使用xTimerCreate（）创建软件计时器，则所需的内存将在xTimerCreate（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xTimerCreateStatic（）创建软件计时器，则应用程序编写器必须提供软件计时器将使用的内存。因此，xTimerCreateStatic（）允许在不使用任何动态内存分配的情况下创建软件计时器。
 *
 * 计时器是在休眠状态下创建的。xTimerStart（）、xTimerReset（）、xDimerStartFromISR（）、xMimerResetFromISR）、xTimerChangePeriod（）和xTimerChangePeriodFromISR API函数都可以用于将计时器转换为活动状态。
 *
 * @param pcTimerName 分配给计时器的文本名称。这样做纯粹是为了帮助调试。内核本身只通过其句柄引用计时器，而从不通过其名称。
 *
 * @param xTimerPeriodInTicks 计时器周期。时间以刻度周期定义，因此常量portTICK_PERIOD_MS可用于转换以毫秒为单位指定的时间。例如，如果计时器必须在100个刻度后过期，则xTimerPeriodnTicks应设置为100。或者，如果计时器在500ms后过期，那么xPeriod可以设置为（500/portTICK_PERIOD_MS），前提是configTICK_RATE_HZ小于或等于1000。计时器周期必须大于0。
 *
 * @param uxAutoReload 如果uxAutoReload设置为pdTRUE，则计时器将以xTimerPeriodTicks参数设置的频率重复过期。如果uxAutoReload设置为pdFALSE，则计时器将是一次性计时器，并在到期后进入休眠状态。
 *
 * @param pvTimerID 分配给正在创建的计时器的标识符。通常，当同一个回调函数分配给多个计时器时，这将在计时器回调函数中用于标识哪个计时器过期。
 *
 * @param pxCallbackFunction 计时器过期时要调用的函数。回调函数必须具有TimerCallbackFunction_t定义的原型，即“void vCallbackFunction（TimerHandle_t xTimer）；”。
 *
 * @param pxTimerBuffer 必须指向StaticTimer_t类型的变量，然后该变量将用于保存软件计时器的数据结构，从而不需要动态分配内存。
 *
 * @return 如果创建了计时器，则返回所创建计时器的句柄。如果pxTimerBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @verbatim
 *
 * //用于保存软件计时器数据结构的缓冲区。静态静态Timer_t xTimerBuffer；
 *
 * //将由软件计时器的回调//函数递增的变量。UBaseType_t uxVariableToIncrement=0；
 *
 * //一种软件计时器回调函数，在创建软件计时器时递增传递给//的变量。第5次增量后，//回调函数停止软件计时器。静态void prvTimerCallback（TimerHandle_t xExpiredTimer）｛UBaseType_t puxVariableToIncrement；BaseType_t xReturned；
 *
 *     //从计时器ID获取要递增的变量的地址。puxVariableToIncrement=（UBaseType_t）pvTimerGetTimerID（xExpiredTimer）；
 *
 *     //增加变量以显示计时器回调已执行。（puxVariableToIncrement）++；
 *
 *     //如果此回调已执行所需次数，请停止//计时器。if（puxVariableToIncrement==5）｛//这是从计时器回调调用的，因此不能阻止.xTimerStop（xExpiredTimer，staticDONT_block）；｝｝
 *
 * void main（void）｛//创建软件时间。xTimerCreateStatic（）比正常的xTimerCreate（）API函数有一个额外的参数//。该参数是一个指向StaticTimer_t结构的指针//，该结构将保存软件计时器//结构。如果该参数传递为NULL，则该结构将//动态分配，就像xTimerCreate（）一样已被呼叫。xTimer=xTimerCreateStatic（“T1”，//任务的文本名称。仅帮助调试。不由FreeRTOS使用。xTimerPeriod，//计时器的周期（以刻度为单位）。pdTRUE，//这是自动重新加载计时器。（void）&uxVariableToIncrement，//由软件计时器的回调函数prvTimerCallback递增的变量，//计时器到期时要执行的函数&xTimerBuffer）；//将保存软件计时器结构的缓冲区。
 *
 *     //调度程序尚未启动，因此未使用块时间。xReturned=xTimerStart（xTimer，0）；
 *
 *     //…//在此处创建任务。//。。。
 *
 *     //启动调度器将启动计时器，因为它们已经//设置为活动状态。vTaskStartScheduler（）；
 *
 *     //不应该到达这里。对于（；；）；}
 * @endverbatim
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    TimerHandle_t xTimerCreateStatic( const char * const pcTimerName, /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
                                      const TickType_t xTimerPeriodInTicks,
                                      const UBaseType_t uxAutoReload,
                                      void * const pvTimerID,
                                      TimerCallbackFunction_t pxCallbackFunction,
                                      StaticTimer_t * pxTimerBuffer ) PRIVILEGED_FUNCTION;
#endif /* 配置支持状态分配*/

/**
 * void*pvTimerGetTimerID（TimerHandle_t xTimer）；
 *
 * 返回分配给计时器的ID。
 *
 * 使用用于创建计时器的xTimerCreate（）调用的pvTimerID参数，并通过调用vTimerSetTimerID（）API函数，将ID分配给计时器。
 *
 * 如果将同一回调函数分配给多个计时器，则计时器ID可以用作时间特定（计时器本地）存储。
 *
 * @param xTimer 正在查询的计时器。
 *
 * @return 分配给正在查询的计时器的ID。
 *
 * 示例用法：
 *
 * 请参阅xTimerCreate（）API函数示例使用场景。
 */
void * pvTimerGetTimerID( const TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

/**
 * void vTimerSetTimerID（TimerHandle_t xTimer，void*pvNewID）；
 *
 * 设置分配给计时器的ID。
 *
 * 使用用于创建计时器的xTimerCreated（）调用的pvTimerID参数将ID分配给计时器。
 *
 * 如果将同一回调函数分配给多个计时器，则计时器ID可以用作时间特定（计时器本地）存储。
 *
 * @param xTimer 正在更新计时器。
 *
 * @param pvNewID 要分配给计时器的ID。
 *
 * 示例用法：
 *
 * 请参阅xTimerCreate（）API函数示例使用场景。
 */
void vTimerSetTimerID( TimerHandle_t xTimer,
                       void * pvNewID ) PRIVILEGED_FUNCTION;

/**
 * BaseType_t x TimerIsTimerActive（TimerHandle_t x计时器）；
 *
 * 查询计时器以查看它是处于活动状态还是处于休眠状态。
 *
 * 如果出现以下情况，计时器将处于休眠状态：1）计时器已创建但尚未启动，或2）计时器已过期但尚未重新启动。
 *
 * 计时器是在休眠状态下创建的。xTimerStart（）、xTimerReset（）、xDimerStartFromISR（）、xMimerResetFromISR）、xTimerChangePeriod（）和xTimerChangePeriodFromISR API函数都可以用于将计时器转换为活动状态。
 *
 * @param xTimer 正在查询的计时器。
 *
 * @return 如果计时器处于休眠状态，将返回pdFALSE。如果计时器处于活动状态，将返回pdFALSE以外的值。
 *
 * 示例用法：
 * @verbatim //此函数假定xTimer已创建。void vAFunction（TimerHandle_t xTimer）｛if（xTimerIsTimerActive（xTimer！=pdFALSE）//或更简单地等同于“if（xTimerIsTimerActive（xTimeer））”｛//xTimer处于活动状态，请执行某些操作。｝否则｛//x Timer处于非活动状态，则执行其他操作。｝｝
 * @endverbatim
 */
BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务句柄_t xTimerGetTimerDaemon任务句柄（无效）；
 * @endcond
 *
 * 只有在FreeRTOSConfig.h中将INCLUDE_xTimerGetTimerDaemonTaskHandle设置为1时，xTimerGettimerDaemontTaskHandle（）才可用。
 *
 * 只需返回计时器服务/守护进程任务的句柄。在启动调度程序之前调用xTimerGetTimerDaemonTaskHandle（）是无效的。
 */
TaskHandle_t xTimerGetTimerDaemonTaskHandle( void ) PRIVILEGED_FUNCTION;

/**
 * BaseType_t xTimerStart（TimerHandle_t x计时器，TickType_t x TicksToWait）；
 *
 * 计时器功能由计时器服务/守护程序任务提供。许多公共FreeRTOS计时器API函数通过一个称为计时器命令队列的队列向计时器服务任务发送命令。计时器命令队列对内核本身是私有的，应用程序代码无法直接访问。计时器命令队列的长度由configTIMER_queue_length配置常数设置。
 *
 * xTimerStart（）启动之前使用xTimerCreate（）API函数创建的计时器。如果计时器已经启动并且已经处于活动状态，则xTimerStart（）具有与xTimerReset（）API函数等效的功能。
 *
 * 启动计时器可确保计时器处于活动状态。如果计时器未同时停止、删除或重置，则在调用xTimerStart（）后，与计时器关联的回调函数将被调用“n”个滴答，其中“n”是计时器定义的周期。
 *
 * 在调度程序启动之前调用xTimerStart（）是有效的，但当这样做时，计时器在调度程序开始之前不会实际启动，计时器到期时间将与调度程序启动的时间相关，而不是与调用xTimerStart（）的时间相关。
 *
 * configUSE_TIMERS配置常量必须设置为1，xTimerStart（）才能可用。
 *
 * @param xTimer 正在启动/重新启动的计时器的句柄。
 *
 * @param xTicksToWait 指定在调用xTimerStart（）时，如果队列已满，则调用任务应保持在“阻止”状态以等待启动命令成功发送到计时器命令队列的时间（以记号为单位）。如果在调度程序启动之前调用xTimerStart（），则忽略xTicksToWait。
 *
 * @return 如果启动命令即使在xTicksToWait信号通过后也无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级，尽管计时器到期时间与实际调用xTimerStart（）的时间有关。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 *
 * 请参阅xTimerCreate（）API函数示例使用场景。
 *
 */
#define xTimerStart( xTimer, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_START, ( xTaskGetTickCount() ), NULL, ( xTicksToWait ) )

/**
 * BaseType_t xTimerStop（TimerHandle_t xTime，TickType_t x TicksToWait）；
 *
 * 计时器功能由计时器服务/守护程序任务提供。许多公共FreeRTOS计时器API函数通过一个称为计时器命令队列的队列向计时器服务任务发送命令。计时器命令队列对内核本身是私有的，应用程序代码无法直接访问。计时器命令队列的长度由configTIMER_queue_length配置常数设置。
 *
 * xTimerStop（）停止以前使用xTimerStart（）、xTimerReset（）、xMimerStartFromISR（）、xDimerResetFromISR）、xTimerChangePeriod（）或xTimerChangePeriodFromISR API函数启动的计时器。
 *
 * 停止计时器可确保计时器不处于活动状态。
 *
 * configUSE_TIMERS配置常量必须设置为1，xTimerStop（）才能可用。
 *
 * @param xTimer 正在停止的计时器的句柄。
 *
 * @param xTicksToWait 指定在调用xTimerStop（）时，如果队列已满，则调用任务应保持在“阻止”状态以等待停止命令成功发送到计时器命令队列的时间（以记号为单位）。如果在调度程序启动之前调用xTimerStop（），则忽略xTicksToWait。
 *
 * @return 如果停止命令即使在xTicksToWait信号通过后也无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 *
 * 请参阅xTimerCreate（）API函数示例使用场景。
 *
 */
#define xTimerStop( xTimer, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_STOP, 0U, NULL, ( xTicksToWait ) )

/**
 * BaseType_t x TimerChangePeriod（TimerHandle_t xTimer、TickType_t xNewPeriod、TickType _t xTicksToWait）；
 *
 * 计时器功能由计时器服务/守护程序任务提供。许多公共FreeRTOS计时器API函数通过一个称为计时器命令队列的队列向计时器服务任务发送命令。计时器命令队列对内核本身是私有的，应用程序代码无法直接访问。计时器命令队列的长度由configTIMER_queue_length配置常数设置。
 *
 * xTimerChangePeriod（）更改先前使用xTimerCreate（）API函数创建的计时器的周期。
 *
 * 可以调用xTimerChangePeriod（）来更改活动或休眠状态计时器的周期。
 *
 * configUSE_TIMERS配置常量必须设置为1，xTimerChangePeriod（）才能可用。
 *
 * @param xTimer 正在更改其周期的计时器的句柄。
 *
 * @param xNewPeriod xTimer的新周期。计时器周期以滴答周期指定，因此常量portTICK_PERIOD_MS可用于转换以毫秒为单位指定的时间。例如，如果计时器必须在100个滴答后过期，则xNewPeriod应设置为100。或者，如果计时器在500毫秒后过期，那么如果configTICK_RATE_HZ小于或等于1000，则xNew PERIOD可以设置为（500/portTICK_PERIOD_MS）。
 *
 * @param xTicksToWait 指定在调用xTimerChangePeriod（）时，如果队列已满，则调用任务应保持在“阻止”状态以等待将更改周期命令成功发送到计时器命令队列的时间（以记号为单位）。如果在调度程序启动之前调用了xTimerChangePeriod（），则忽略xTicksToWait。
 *
 * @return 如果即使在xTicksToWait信号经过之后，更改周期命令也无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 * @verbatim //此函数假定xTimer已创建。如果xTimer引用的计时器//在调用时已处于活动状态，则计时器//将被删除。如果xTimer引用的计时器在//调用时未激活，则计时器的周期设置为500ms，计时器//启动。void vAFunction（TimerHandle_t xTimer）｛if（xTimerIsTimerActive（xTimer）！=pdFALSE）//或更简单地等同于“if（xTimerIsTimerActive（xTimeer））”｛//xTimer已处于活动状态-将其删除。xTimerDelete（xTimers）；｝否则｛//xTimer未激活，请将其周期更改为500ms。这也将//导致计时器启动。如果//change period命令无法立即发送到计时器//命令队列，则阻止最多100个滴答。如果（xTimerChangePeriod（xTimer，500/portTICK_period_MS，100）==pdPASS）｛//命令已成功发送。｝else｛//即使在等待100个滴答声//后，也无法发送命令。请在此处采取适当的操作。｝｝
 * @endverbatim
 */
#define xTimerChangePeriod( xTimer, xNewPeriod, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_CHANGE_PERIOD, ( xNewPeriod ), NULL, ( xTicksToWait ) )

/**
 * BaseType_t xTimerDelete（TimerHandle_t xTime，TickType_t x TicksToWait）；
 *
 * 计时器功能由计时器服务/守护程序任务提供。许多公共FreeRTOS计时器API函数通过一个称为计时器命令队列的队列向计时器服务任务发送命令。计时器命令队列对内核本身是私有的，应用程序代码无法直接访问。计时器命令队列的长度由configTIMER_queue_length配置常数设置。
 *
 * xTimerDelete（）删除以前使用xTimerCreate（）API函数创建的计时器。
 *
 * configUSE_TIMERS配置常量必须设置为1，xTimerDelete（）才能可用。
 *
 * @param xTimer 正在删除的计时器的句柄。
 *
 * @param xTicksToWait 指定在调用xTimerDelete（）时，如果队列已满，则调用任务应保持在“阻止”状态以等待删除命令成功发送到计时器命令队列的时间（以刻度为单位）。如果在调度程序启动之前调用了xTimerDelete（），则忽略xTicksToWait。
 *
 * @return 如果删除命令即使在xTicksToWait信号通过后也无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 *
 * 请参阅xTimerChangePeriod（）API函数示例使用场景。
 */
#define xTimerDelete( xTimer, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_DELETE, 0U, NULL, ( xTicksToWait ) )

/**
 * BaseType_t xTimerReset（TimerHandle_t x计时器，TickType_t x TicksToWait）；
 *
 * 计时器功能由计时器服务/守护程序任务提供。许多公共FreeRTOS计时器API函数通过一个称为计时器命令队列的队列向计时器服务任务发送命令。计时器命令队列对内核本身是私有的，应用程序代码无法直接访问。计时器命令队列的长度由configTIMER_queue_length配置常数设置。
 *
 * xTimerReset（）重新启动以前使用xTimerCreate（）API函数创建的计时器。如果计时器已经启动并且已经处于活动状态，则xTimerReset（）将使计时器重新计算其到期时间，以便与调用xTimerReset（）的时间相对应。如果计时器处于休眠状态，则xTimerReset（）具有与xTimerStart（）API函数等效的功能。
 *
 * 重置计时器可确保计时器处于活动状态。如果计时器未同时停止、删除或重置，则在调用xTimerReset（）后，与计时器关联的回调函数将被调用“n”个滴答，其中“n”是计时器定义的周期。
 *
 * 在调度程序启动之前调用xTimerReset（）是有效的，但当这样做时，计时器在调度程序开始之前不会实际启动，计时器到期时间将与调度程序启动的时间相关，而不是与调用xTimer reset（（）的时间相关。
 *
 * configUSE_TIMERS配置常量必须设置为1，xTimerReset（）才能可用。
 *
 * @param xTimer 正在重置/启动/重新启动的计时器的句柄。
 *
 * @param xTicksToWait 指定在调用xTimerReset（）时，如果队列已满，则调用任务应保持在“阻止”状态以等待重置命令成功发送到计时器命令队列的时间（以刻度为单位）。如果在调度程序启动之前调用xTimerReset（），则忽略xTicksToWait。
 *
 * @return 如果重置命令即使在xTicksToWait信号通过后也无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级，尽管计时器到期时间与实际调用xTimerStart（）的时间有关。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 * @verbatim //当按下一个键时，LCD背光将打开。如果5秒过去//而没有按下一个按键，则LCD背光将关闭。在这种情况下，计时器是一次性计时器。
 *
 * TimerHandle_t xBacklightTimer=NULL；
 *
 * //分配给一次性计时器的回调函数。在这种情况下，不使用//参数。void vBacklightTimerCallback（TimerHandle_t pxTimer）｛//计时器已过期，因此按下键//后必须经过5秒。关闭LCD背光。vSetBacklightState（BACKLIGHT_off）；｝
 *
 * //按键事件处理程序。void vKeyPressEventHandler（char cKey）｛//确保LCD背光灯亮起，然后重置//负责在5秒//键不活动后关闭背光灯的计时器。如果无法立即发送命令，请等待10个滴答声，等待命令成功发送//。vSetBacklightState（BACKLIGHT_on）；if（xTimerReset（xBacklightTimer，100）！=pdPASS）｛//重置命令未成功执行。请在此处执行相应的//操作。｝
 *
 *     //在此处执行其余的密钥处理。}
 *
 * void main（void）{int32_tx；
 *
 *     //创建并启动一次计时器，该计时器负责在5秒内未按下任何键时关闭//背光。xBacklightTimer=xTimerCreate（“BacklightTimer”，//只是一个文本名称，内核不使用。（5000/portTICK_PERIOD_MS），//计时器周期（以滴答为单位）。pdFALSE，//计时器是一次性计时器。0，//回调不使用id，因此可以取任何值。vBacklightTimerCallback//关闭LCD背光的回调函数。）；
 *
 *     if（xBacklightTimer==NULL）｛//计时器未创建。｝else｛//启动计时器。未指定块时间，即使指定了块时间，//也会被忽略，因为计划程序尚未//启动。if（xTimerStart（xBacklight timer，0）！=pdPASS）｛//计时器无法设置为活动状态。｝｝
 *
 *     //…//在此处创建任务。//。。。
 *
 *     //启动调度程序将启动计时器，因为它已经//设置为活动状态。vTaskStartScheduler（）；
 *
 *     //不应该到达这里。对于（；；）；}
 * @endverbatim
 */
#define xTimerReset( xTimer, xTicksToWait ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_RESET, ( xTaskGetTickCount() ), NULL, ( xTicksToWait ) )

/**
 * BaseType_t xTimerStartFromISR（TimerHandle_txTimer，BaseType_t-pxHigherPriorityTaskWoken）；
 *
 * 可以从中断服务例程调用的xTimerStart（）版本。
 *
 * @param xTimer 正在启动/重新启动的计时器的句柄。
 *
 * @param pxHigherPriorityTaskWoken 计时器服务/守护程序任务大部分时间都处于“阻止”状态，等待消息到达计时器命令队列。调用xTimerStartFromISR（）会向计时器命令队列写入一条消息，因此有可能将计时器服务/守护进程任务转换为已阻止状态。如果调用xTimerStartFromISR（）导致计时器服务/守护程序任务离开“阻止”状态，并且计时器服务/后台程序任务的优先级等于或大于当前正在执行的任务（被中断的任务），则pxHigherPriorityTaskWoken将在xTimerSStartFromISR函数内部设置为pdTRUE。如果xTimerStartFromISR（）将此值设置为pdTRUE，则应在中断退出之前执行上下文切换。
 *
 * @return 如果启动命令无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级，尽管计时器到期时间与实际调用xTimerStartFromISR（）的时间有关。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 * @verbatim //此场景假设xBacklightTimer已经创建。当按下//键时，LCD背光将打开。如果5秒过去//而没有按下键，则LCD背光将关闭。在//这种情况下，计时器是一个单次计时器，与xTimerReset（）函数的示例不同，按键事件处理程序是一个中断//服务例程。
 *
 * //分配给一次性计时器的回调函数。在这种情况下，不使用//参数。void vBacklightTimerCallback（TimerHandle_t pxTimer）｛//计时器已过期，因此按下键//后必须经过5秒。关闭LCD背光。vSetBacklightState（BACKLIGHT_off）；｝
 *
 * //按键中断服务例程。void vKeyPressEventInterruptHandler（void）｛BaseType_t xHigherPriorityTaskWoken=pdFALSE；
 *
 *     //确保LCD背光灯亮起，然后重新启动定时器，该定时器负责//在5秒//键不活动后关闭背光灯。这是一个中断服务例程，因此只能//调用以“FromISR”结尾的FreeRTOS API函数。vSet背光状态（BACKLIGHT_ON）；
 *
 *     //此处//可以调用xTimerStartFromISR（）或xTimerResetFromISR），因为两者都会导致计时器重新计算其到期时间。//xHigherPriorityTaskWoken在//声明时（在此函数中）被初始化为pdFALSE。如果（xTimerStartFromISR（xBacklightTimer，&xHigherPriorityTaskWoken）！=pdPASS）｛//启动命令未成功执行。请在此处执行相应的//操作。｝
 *
 *     //在此执行其余的密钥处理。
 *
 *     //如果xHigherPriorityTaskWoken等于pdTRUE，则应执行上下文切换//。在ISR内部执行上下文切换//所需的语法因端口而异，也因编译器而异。检查您正在使用的端口的演示，以找到所需的//实际语法。如果（xHigherPriorityTaskWoken！=pdFALSE）｛//在此调用中断安全收益函数（实际函数//取决于所使用的FreeRTOS端口）。｝｝
 * @endverbatim
 */
#define xTimerStartFromISR( xTimer, pxHigherPriorityTaskWoken ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_START_FROM_ISR, ( xTaskGetTickCountFromISR() ), ( pxHigherPriorityTaskWoken ), 0U )

/**
 * BaseType_t xTimerStopFromISR（TimerHandle_txTimer，BaseType_t-pxHigherPriorityTaskWoken）；
 *
 * 可以从中断服务例程调用的xTimerStop（）版本。
 *
 * @param xTimer 正在停止的计时器的句柄。
 *
 * @param pxHigherPriorityTaskWoken 计时器服务/守护程序任务大部分时间都处于“阻止”状态，等待消息到达计时器命令队列。调用xTimerStopFromISR（）会向计时器命令队列写入一条消息，因此有可能将计时器服务/守护进程任务转换为已阻止状态。如果调用xTimerStopFromISR（）导致计时器服务/守护程序任务离开“阻止”状态，并且计时器服务/后台程序任务的优先级等于或大于当前正在执行的任务（被中断的任务），则pxHigherPriorityTaskWoken将在xTimerStopFromISR函数内部设置为pdTRUE。如果xTimerStopFromISR（）将此值设置为pdTRUE，则应在中断退出之前执行上下文切换。
 *
 * @return 如果停止命令无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 * @verbatim //此场景假设xTimer已经创建并启动。当//发生中断时，应简单地停止计时器。
 *
 * //停止计时器的中断服务例程。void vAnExampleInterruptServiceRoutine（void）｛BaseType_t xHigherPriorityTaskWoken=pdFALSE；
 *
 *     //中断已发生-只需停止计时器。//xHigherPriorityTaskWoken设置为pdFALSE，此处定义了//（在此函数中）。由于这是一个中断服务例程，因此只能使用以“FromISR”结尾的//FreeRTOS API函数。如果（xTimerStopFromISR（xTimer，&xHigherPriorityTaskWoken）！=pdPASS）｛//停止命令未成功执行。请在此处执行相应的//操作。｝
 *
 *     //如果xHigherPriorityTaskWoken等于pdTRUE，则应执行上下文切换//。在ISR内部执行上下文切换//所需的语法因端口而异，也因编译器而异。检查您正在使用的端口的演示，以找到所需的//实际语法。如果（xHigherPriorityTaskWoken！=pdFALSE）｛//在此调用中断安全收益函数（实际函数//取决于所使用的FreeRTOS端口）。｝｝
 * @endverbatim
 */
#define xTimerStopFromISR( xTimer, pxHigherPriorityTaskWoken ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_STOP_FROM_ISR, 0, ( pxHigherPriorityTaskWoken ), 0U )

/**
 * BaseType_t x TimerChangePeriodFromISR（TimerHandle_t xTimer，TickType_t xNewPeriod，BaseType_t-pxHigherPriorityTaskWoken）；
 *
 * 可以从中断服务例程调用的xTimerChangePeriod（）版本。
 *
 * @param xTimer 正在更改其周期的计时器的句柄。
 *
 * @param xNewPeriod xTimer的新周期。计时器周期以滴答周期指定，因此常量portTICK_PERIOD_MS可用于转换以毫秒为单位指定的时间。例如，如果计时器必须在100个滴答后过期，则xNewPeriod应设置为100。或者，如果计时器在500毫秒后过期，那么如果configTICK_RATE_HZ小于或等于1000，则xNew PERIOD可以设置为（500/portTICK_PERIOD_MS）。
 *
 * @param pxHigherPriorityTaskWoken 计时器服务/守护程序任务大部分时间都处于“阻止”状态，等待消息到达计时器命令队列。调用xTimerChangePeriodFromISR（）会向计时器命令队列写入一条消息，因此有可能将计时器服务/守护进程任务转换为已阻止状态。如果调用xTimerChangePeriodFromISR（）导致计时器服务/守护程序任务离开“阻止”状态，并且计时器服务/后台程序任务的优先级等于或大于当前正在执行的任务（被中断的任务），则pxHigherPriorityTaskWoken将在xTimerChange PeriodFromisR（）函数内部设置为pdTRUE。如果xTimerChangePeriodFromISR（）将此值设置为pdTRUE，则应在中断退出之前执行上下文切换。
 *
 * @return 如果无法将更改计时器周期的命令发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 * @verbatim //此场景假设xTimer已经创建并启动。当//发生中断时，xTimer的周期应更改为500ms。
 *
 * //改变xTimer周期的中断服务例程。void vAnExampleInterruptServiceRoutine（void）｛BaseType_t xHigherPriorityTaskWoken=pdFALSE；
 *
 *     //发生中断-将xTimer的周期更改为500ms。//xHigherPriorityTaskWoken设置为pdFALSE，此处定义了//（在此函数中）。由于这是一个中断服务例程，因此只能使用以“FromISR”结尾的//FreeRTOS API函数。如果（xTimerChangePeriodFromISR（xTimer，&xHigherPriorityTaskWoken）！=pdPASS）｛//未能成功执行更改计时器周期的命令//。请在此处采取适当的操作。｝
 *
 *     //如果xHigherPriorityTaskWoken等于pdTRUE，则应执行上下文切换//。在ISR内部执行上下文切换//所需的语法因端口而异，也因编译器而异。检查您正在使用的端口的演示，以找到所需的//实际语法。如果（xHigherPriorityTaskWoken！=pdFALSE）｛//在此调用中断安全收益函数（实际函数//取决于所使用的FreeRTOS端口）。｝｝
 * @endverbatim
 */
#define xTimerChangePeriodFromISR( xTimer, xNewPeriod, pxHigherPriorityTaskWoken ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_CHANGE_PERIOD_FROM_ISR, ( xNewPeriod ), ( pxHigherPriorityTaskWoken ), 0U )

/**
 * BaseType_t xTimerResetFromISR（TimerHandle_t xTime，BaseType_t-pxHigherPriorityTaskWoken）；
 *
 * 可以从中断服务例程调用的xTimerReset（）版本。
 *
 * @param xTimer 要启动、重置或重新启动的计时器的句柄。
 *
 * @param pxHigherPriorityTaskWoken 计时器服务/守护程序任务大部分时间都处于“阻止”状态，等待消息到达计时器命令队列。调用xTimerResetFromISR（）会向计时器命令队列写入一条消息，因此有可能将计时器服务/守护程序任务转换为已阻止状态。如果调用xTimerResetFromISR（）导致计时器服务/守护程序任务离开“阻止”状态，并且计时器服务/后台程序任务的优先级等于或大于当前正在执行的任务（被中断的任务），则pxHigherPriorityTaskWoken将在xTimerResetFromISR（）函数内部设置为pdTRUE。如果xTimerResetFromISR（）将此值设置为pdTRUE，则应在中断退出之前执行上下文切换。
 *
 * @return 如果重置命令无法发送到计时器命令队列，则将返回pdFAIL。如果命令成功发送到计时器命令队列，则将返回pdPASS。实际处理命令的时间取决于计时器服务/守护程序任务相对于系统中其他任务的优先级，尽管计时器到期时间与实际调用xTimerResetFromISR（）的时间有关。计时器服务/守护程序任务优先级由configTIMER_task_priority配置常量设置。
 *
 * 示例用法：
 * @verbatim //此场景假设xBacklightTimer已经创建。当按下//键时，LCD背光将打开。如果5秒过去//而没有按下键，则LCD背光将关闭。在//这种情况下，计时器是一个单次计时器，与xTimerReset（）函数的示例不同，按键事件处理程序是一个中断//服务例程。
 *
 * //分配给一次性计时器的回调函数。在这种情况下，不使用//参数。void vBacklightTimerCallback（TimerHandle_t pxTimer）｛//计时器已过期，因此按下键//后必须经过5秒。关闭LCD背光。vSetBacklightState（BACKLIGHT_off）；｝
 *
 * //按键中断服务例程。void vKeyPressEventInterruptHandler（void）｛BaseType_t xHigherPriorityTaskWoken=pdFALSE；
 *
 *     //确保LCD背光灯亮起，然后重置定时器，该定时器负责//在5秒//键不活动后关闭背光灯。这是一个中断服务例程，因此只能//调用以“FromISR”结尾的FreeRTOS API函数。vSet背光状态（BACKLIGHT_ON）；
 *
 *     //此处//可以调用xTimerStartFromISR（）或xTimerResetFromISR），因为两者都会导致计时器重新计算其到期时间。//xHigherPriorityTaskWoken在//声明时（在此函数中）被初始化为pdFALSE。如果（xTimerResetFromISR（xBacklightTimer，&xHigherPriorityTaskWoken）！=pdPASS）｛//重置命令未成功执行。请在此处执行相应的//操作。｝
 *
 *     //在此执行其余的密钥处理。
 *
 *     //如果xHigherPriorityTaskWoken等于pdTRUE，则应执行上下文切换//。在ISR内部执行上下文切换//所需的语法因端口而异，也因编译器而异。检查您正在使用的端口的演示，以找到所需的//实际语法。如果（xHigherPriorityTaskWoken！=pdFALSE）｛//在此调用中断安全收益函数（实际函数//取决于所使用的FreeRTOS端口）。｝｝
 * @endverbatim
 */
#define xTimerResetFromISR( xTimer, pxHigherPriorityTaskWoken ) \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_RESET_FROM_ISR, ( xTaskGetTickCountFromISR() ), ( pxHigherPriorityTaskWoken ), 0U )


/**
 * BaseType_t xTimerEndFunctionCallFromISR（PendedFunction_t xFunctionToPend，void pvParameter1，uint32_t ulParameter2，BaseType_t-pxHigherPriorityTaskWoken）；
 *
 * 从应用程序中断服务例程中使用，将函数的执行延迟到RTOS守护程序任务（计时器服务任务，因此此函数在timer.c中实现，并以“timer”为前缀）。
 *
 * 理想情况下，中断服务例程（ISR）尽可能短，但有时ISR要么有很多处理要做，要么需要执行不确定的处理。在这些情况下，xTimerEndFunctionCallFromISR（）可用于将函数的处理延迟到RTOS守护程序任务。
 *
 * 提供了一种机制，允许中断直接返回到随后将执行挂起回调函数的任务。这允许回调函数与中断在时间上连续执行，就像回调在中断本身中执行一样。
 *
 * @param xFunctionToPend 要从计时器服务/守护程序任务执行的函数。函数必须符合PendedFunction_t原型。
 *
 * @param pvParameter1 回调函数的第一个参数的值。该参数具有void类型，可用于传递任何类型。例如，可以将无符号longs转换为void，或者可以使用void指向结构。
 *
 * @param ulParameter2 回调函数的第二个参数的值。
 *
 * @param pxHigherPriorityTaskWoken 如上所述，调用此函数将导致向计时器守护进程任务发送消息。如果计时器守护程序任务（在FreeRTOSConfig.h中使用configTIMER_task_priority设置）的优先级高于当前正在运行的任务（中断中断的任务）的优先级，则pxHigherPriorityTaskWoken将在xTimerEndFunctionCallFromISR（）内设置为pdTRUE，表示应在中断退出之前请求上下文切换。因此，pxHigherPriorityTaskWoken必须初始化为pdFALSE。请参见下面的示例代码。
 *
 * @return 如果消息成功发送到计时器守护程序任务，则返回pdPASS，否则返回pdFALSE。
 *
 * 示例用法：
 * @verbatim
 *
 *  //将在后台进程任务上下文中执行的回调函数。//注意回调函数必须都使用相同的原型。void vProcessInterface（void pvParameter1，uint32_t ulParameter2）｛BaseType_t xInterfaceToService；
 *
 *      //需要维护的接口在第二个//参数中传递。在这种情况下，不使用第一个参数。xInterfaceToService=（BaseType_t）ulParameter2；
 *
 *      //…在此执行处理…｝
 *
 *  //从多个接口接收数据包的ISR void vAnISR（void）{BaseType_t xInterfaceToService，xHigherPriorityTaskWoken；
 *
 *      //查询硬件以确定哪个接口需要处理。xInterfaceToService=prvCheckInterface（）；
 *
 *      //实际处理将延迟到任务。请求执行//vProcessInterface（）回调函数，传入需要处理的接口的//编号。//服务的接口在第二个参数中传递。在这种情况下，//不使用第一个参数。xHigherPriorityTaskWoken=pdFALSE；xTimerEndFunctionCallFromISR（vProcessInterface，NULL，（uint32_t）xInterfaceToService，&xHigherPriorityTaskWoken）；
 *
 *      //如果xHigherPriorityTaskWoken现在设置为pdTRUE，则应请求上下文//开关。所使用的宏是特定于端口的，将//是portYIELD_FROM_ISR（）或portEND_SWITCHING_ISR（）-请参阅//所使用端口的文档页。端口YIELD_FROM_ISR（xHigherPriorityTaskWoken）；
 *
 *  }
 * @endverbatim
 */
BaseType_t xTimerPendFunctionCallFromISR( PendedFunction_t xFunctionToPend,
                                          void * pvParameter1,
                                          uint32_t ulParameter2,
                                          BaseType_t * pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

/**
 * BaseType_t xTimerEndFunctionCall（PendedFunction_t xFunctionToPend，void pvParameter1，uint32_t ulParameter2，TickType_t x TicksToWait）；
 *
 * 用于将函数的执行延迟到RTOS守护程序任务（计时器服务任务，因此此函数在timer.c中实现，并以“timer”为前缀）。
 *
 * @param xFunctionToPend 要从计时器服务/守护程序任务执行的函数。函数必须符合PendedFunction_t原型。
 *
 * @param pvParameter1 回调函数的第一个参数的值。该参数具有void类型，可用于传递任何类型。例如，可以将无符号longs转换为void，或者可以使用void指向结构。
 *
 * @param ulParameter2 回调函数的第二个参数的值。
 *
 * @param xTicksToWait 调用此函数将导致向队列上的计时器守护程序任务发送消息。xTicksToWait是在发现队列已满时，调用任务应保持在“阻止”状态（因此不使用任何处理时间）的时间，以便计时器队列上的空间可用。
 *
 * @return 如果消息成功发送到计时器守护程序任务，则返回pdPASS，否则返回pdFALSE。
 *
 */
BaseType_t xTimerPendFunctionCall( PendedFunction_t xFunctionToPend,
                                   void * pvParameter1,
                                   uint32_t ulParameter2,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * const char*const pcTimerGetName（TimerHandle_t xTimer）；
 *
 * 返回创建计时器时分配给计时器的名称。
 *
 * @param xTimer 正在查询的计时器的句柄。
 *
 * @return 分配给xTimer参数指定的计时器的名称。
 */
const char * pcTimerGetName( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION; /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/

/**
 * void vTimerSetReloadMode（TimerHandle_t xTimer，常量UBaseType_t uxAutoReload）；
 *
 * 将计时器更新为自动重新加载计时器（在这种情况下，计时器在每次到期时自动复位）或一次性计时器（在该情况下，除非手动重新启动计时器，否则计时器只会过期一次）。
 *
 * @param xTimer 正在更新的计时器的句柄。
 *
 * @param uxAutoReload 如果uxAutoReload设置为pdTRUE，则计时器将以计时器周期设置的频率重复过期（请参阅xTimerCreate（）API函数的xTimerPeriodTicks参数）。如果uxAutoReload设置为pdFALSE，则计时器将是一次性计时器，并在到期后进入休眠状态。
 */
void vTimerSetReloadMode( TimerHandle_t xTimer,
                          const UBaseType_t uxAutoReload ) PRIVILEGED_FUNCTION;

/**
 * UBaseType_t uxTimerGetReloadMode（TimerHandle_t xTimer）；
 *
 * 查询计时器以确定它是自动重新加载计时器（在这种情况下，计时器每次过期都会自动重置），还是单次计时器（在那种情况下，除非手动重新启动计时器，否则计时器只会过期一次）。
 *
 * @param xTimer 正在查询的计时器的句柄。
 *
 * @return 如果计时器是自动重新加载计时器，则返回pdTRUE，否则返回pdFALSE。
 */
UBaseType_t uxTimerGetReloadMode( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

/**
 * TickType_t xTimerGetPeriod（TimerHandle_t x计时器）；
 *
 * 返回计时器的周期。
 *
 * @param xTimer 正在查询的计时器的句柄。
 *
 * @return 计时器的周期（以刻度为单位）。
 */
TickType_t xTimerGetPeriod( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

/**
 * TickType_t xTimerGetExpiryTime（TimerHandle_t x计时器）；
 *
 * 返回计时器将到期的时间（以刻度为单位）。如果这小于当前刻度计数，则过期时间已从当前时间溢出。
 *
 * @param xTimer 正在查询的计时器的句柄。
 *
 * @return 如果计时器正在运行，则返回计时器下一次到期的时间（以刻度计）。如果计时器未运行，则返回值未定义。
 */
TickType_t xTimerGetExpiryTime( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

/**@秒！文档_排除_标题_节*/

/*
 * 超出此部分的函数不是公共API的一部分，仅供内核使用。
 */
BaseType_t xTimerCreateTimerTask( void ) PRIVILEGED_FUNCTION;
BaseType_t xTimerGenericCommand( TimerHandle_t xTimer,
                                 const BaseType_t xCommandID,
                                 const TickType_t xOptionalValue,
                                 BaseType_t * const pxHigherPriorityTaskWoken,
                                 const TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

#if ( configUSE_TRACE_FACILITY == 1 )
    void vTimerSetTimerNumber( TimerHandle_t xTimer,
                               UBaseType_t uxTimerNumber ) PRIVILEGED_FUNCTION;
    UBaseType_t uxTimerGetTimerNumber( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;
#endif

/**@结束秒*/

#if ( configSUPPORT_STATIC_ALLOCATION == 1 )

    /**
     * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
     * @code{c}
     * void vApplicationGetTimerTaskMemory（StaticTask_t**ppxTimerTaskTCBBuffer，StackType_t**ppxDimerTaskStackBuffer，uint32_t*pulTimerTaskStackSize）
     * @endcode
     * @endcond
     *
     * 此函数用于向FreeRTOS提供静态分配的内存块，以保存定时器任务TCB。设置configSUPPORT_STATIC_ALLOCATION时需要此函数。有关详细信息，请参阅此URI：https://www.FreeRTOS.org/a00110.html#configSUPPORT_STATIC_ALLOCATION
     *
     * @param ppxTimerTaskTCBBuffer   静态分配的TCB缓冲区的句柄
     * @param ppxTimerTaskStackBuffer 为空闲任务静态分配堆栈缓冲区的句柄
     * @param pulTimerTaskStackSize   指向将容纳在分配的堆栈缓冲区中的元素数的指针
     */
    void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                          StackType_t ** ppxTimerTaskStackBuffer,
                                              uint32_t * pulTimerTaskStackSize );

#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */
#endif /* TIMERS_H */

