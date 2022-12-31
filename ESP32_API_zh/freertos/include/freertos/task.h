/*
 * FreeRTOS内核V10.4.3版权所有（C）2020 Amazon.com，Inc.或其附属公司。保留所有权利。
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


#ifndef INC_TASK_H
#define INC_TASK_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h must appear in source files before include task.h"
#endif

#include "list.h"
#ifdef ESP_PLATFORM // IDF-3793
#include "freertos/portmacro.h"
#endif // ESP_PLATFORM

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * MACROS AND DEFINITIONS
 *----------------------------------------------------------*/

#define tskKERNEL_VERSION_NUMBER       "V10.4.3"
#define tskKERNEL_VERSION_MAJOR        10
#define tskKERNEL_VERSION_MINOR        4
#define tskKERNEL_VERSION_BUILD        3

/* 在MemoryRegion_t结构的ulParameters中传递了MPU区域参数。*/
#define tskMPU_REGION_READ_ONLY        ( 1UL << 0UL )
#define tskMPU_REGION_READ_WRITE       ( 1UL << 1UL )
#define tskMPU_REGION_EXECUTE_NEVER    ( 1UL << 2UL )
#define tskMPU_REGION_NORMAL_MEMORY    ( 1UL << 3UL )
#define tskMPU_REGION_DEVICE_MEMORY    ( 1UL << 4UL )

/* 直接到任务通知功能过去每个任务只有一个通知。现在，每个任务都有一个通知数组，其大小由configTASK_NOTIFICATION_array_ENTRIES确定。为了向后兼容，任何原始直接到任务通知的使用都默认使用数组中的第一个索引。*/
#define tskDEFAULT_INDEX_TO_NOTIFY     ( 0 )

#define tskNO_AFFINITY  ( 0x7FFFFFFF )

/**
 * 任务小时
 *
 * 引用任务的类型。例如，对xTaskCreate的调用（通过指针参数）返回一个TaskHandle_t变量，然后该变量可以用作vTaskDelete的参数来删除任务。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup任务处理_任务处理_
 * @endcond \内部组任务
 */
struct tskTaskControlBlock;     /* 旧的命名约定用于防止破坏内核感知调试器。*/
#ifdef ESP_PLATFORM // IDF-3769
typedef void* TaskHandle_t;
#else
typedef struct tskTaskControlBlock* TaskHandle_t;
#endif // ESP_PLATFORM
/**
 * 定义应用程序任务挂钩函数必须符合的原型。
 */
typedef BaseType_t (* TaskHookFunction_t)( void * );

/**eTaskGetState返回的任务状态。*/
typedef enum
{
    eRunning = 0,     /* 任务正在查询其自身的状态，因此必须正在运行。*/
    eReady,           /* 正在查询的任务位于已读或挂起就绪列表中。*/
    eBlocked,         /* 正在查询的任务处于“已阻止”状态。*/
    eSuspended,       /* 正在查询的任务处于“已挂起”状态，或处于“已阻止”状态且超时无限。*/
    eDeleted,         /* 正在查询的任务已被删除，但其TCB尚未释放。*/
    eInvalid          /* 用作“无效状态”值。*/
} eTaskState;

/* 调用vTaskNotify（）时可以执行的操作。*/
typedef enum
{
    eNoAction = 0,                /* 通知任务而不更新其通知值。*/
    eSetBits,                     /* 在任务的通知值中设置位。*/
    eIncrement,                   /* 增加任务的通知值。*/
    eSetValueWithOverwrite,       /* 将任务的通知值设置为特定值，即使任务尚未读取上一个值。*/
    eSetValueWithoutOverwrite     /* 如果任务已读取上一个值，则设置任务的通知值。*/
} eNotifyAction;

/**@秒！文档_排除_标题_节*/
/**
 * 仅在内部使用。
 */
typedef struct xTIME_OUT
{
    BaseType_t xOverflowCount;
    TickType_t xTimeOnEntering;
} TimeOut_t;

/**
 * 定义使用MPU时分配给任务的内存范围。
 */
typedef struct xMEMORY_REGION
{
    void * pvBaseAddress;
    uint32_t ulLengthInBytes;
    uint32_t ulParameters;
} MemoryRegion_t;

/*
 * 创建MPU保护任务所需的参数。
 */
typedef struct xTASK_PARAMETERS
{
    TaskFunction_t pvTaskCode;
    const char * const pcName; /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
    configSTACK_DEPTH_TYPE usStackDepth;
    void * pvParameters;
    UBaseType_t uxPriority;
    StackType_t * puxStackBuffer;
    MemoryRegion_t xRegions[ portNUM_CONFIGURABLE_REGIONS ];
    #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        StaticTask_t * const pxTaskBuffer;
    #endif
} TaskParameters_t;

/* 与uxTaskGetSystemState（）函数一起使用，返回系统中每个任务的状态。*/
typedef struct xTASK_STATUS
{
    TaskHandle_t xHandle;                            /* 结构中其余信息所涉及的任务的句柄。*/
    const char * pcTaskName;                         /* 指向任务名称的指针。如果在填充结构后删除了任务，则此值将无效！*/ /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
    UBaseType_t xTaskNumber;                         /* 任务的唯一编号。*/
    eTaskState eCurrentState;                        /* 填充结构时任务存在的状态。*/
    UBaseType_t uxCurrentPriority;                   /* 填充结构时任务运行的优先级（可以继承）。*/
    UBaseType_t uxBasePriority;                      /* 如果任务的当前优先级已被继承，则任务将返回的优先级，以避免在获取互斥锁时发生无限优先级反转。仅当configUSE_MUTEXES在FreeRTOSConfig.h中定义为1时有效。*/
    uint32_t ulRunTimeCounter;                       /* 迄今为止分配给任务的总运行时间，由运行时间统计时钟定义。看见https://www.FreeRTOS.org/rtos-run-time-stats.html.仅当configGENERATE_RUN_TIME_STATS在FreeRTOSConfig.h中定义为1时有效。*/
    StackType_t * pxStackBase;                       /* 指向任务堆栈区域的最低地址。*/
    configSTACK_DEPTH_TYPE usStackHighWaterMark;     /* 自创建任务以来，任务剩余的最小堆栈空间量。该值越接近于零，任务就越接近于溢出其堆栈。*/
#if configTASKLIST_INCLUDE_COREID
    BaseType_t xCoreID;                              /*!< 核心此任务固定到（tskNO_AFINITY为0、1或-1）。如果设置了CONFIG_FREERTOS_VTAKLIST_INCLUDE_COREID，则显示此字段。*/
#endif
} TaskStatus_t;

/**@结束秒*/

/**
 * eTaskConfirmSleepModeStatus（）的可能返回值。
 */
typedef enum
{
    eAbortSleep = 0,           /* 自调用portSUPPORTESS_TICKS_AND_SLEEP（）后，任务已准备就绪或上下文开关挂起-中止进入睡眠模式。*/
    eStandardSleep,            /* 进入睡眠模式，其持续时间不会超过预期的空闲时间。*/
    eNoTasksWaitingTimeout     /* 没有任务等待超时，因此可以安全地进入只能通过外部中断退出的休眠模式。*/
} eSleepModeStatus;

/**
 * 定义空闲任务使用的优先级。不得对此进行修改。
 *
 * \内部组任务工具
 */
#define tskIDLE_PRIORITY    ( ( UBaseType_t ) 0U )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @endcond
 *
 * 用于强制上下文切换的宏。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup taskYIELD taskYIED
 * @endcond \组调度控制
 */
#define taskYIELD()                        portYIELD()

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @endcond
 *
 * 宏来标记关键代码区域的开始。处于关键区域时，不会发生抢占式上下文切换。
 *
 * @note 这可能会改变堆栈（取决于可移植实现），因此必须小心使用！
 *
 * @cond !DOC_SINGLE_GROUP\defgroup taskENTER_CCRITICAL任务ENTER_CRITICAL
 * @endcond \组调度控制
 */
#ifdef ESP_PLATFORM
#define taskENTER_CRITICAL( x )   portENTER_CRITICAL( x )
#else
#define taskENTER_CRITICAL( )     portENTER_CRITICAL( )
#endif //  ESP_PLATFORM
#define taskENTER_CRITICAL_FROM_ISR( ) portSET_INTERRUPT_MASK_FROM_ISR()

#ifdef ESP_PLATFORM
#define taskENTER_CRITICAL_ISR( x )   portENTER_CRITICAL_ISR( x )
#else
#define taskENTER_CRITICAL_ISR( )     portENTER_CRITICAL_ISR( )
#endif //  ESP_PLATFORM

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @endcond
 *
 * 用于标记关键代码区域结尾的宏。处于关键区域时，不会发生抢占式上下文切换。
 *
 * @note 这可能会改变堆栈（取决于可移植实现），因此必须小心使用！
 *
 * @cond !DOC_SINGLE_GROUP\defgroup taskEXIT_CRITICAL任务EXIT_CRICRITICAL
 * @endcond \组调度控制
 */

#ifdef ESP_PLATFORM
#define taskEXIT_CRITICAL( x )          portEXIT_CRITICAL( x )
#else
#define taskEXIT_CRITICAL( )            portEXIT_CRITICAL( )
#endif // ESP_PLATFORM
#define taskEXIT_CRITICAL_FROM_ISR( x ) portCLEAR_INTERRUPT_MASK_FROM_ISR( x )

#ifdef ESP_PLATFORM
#define taskEXIT_CRITICAL_ISR( x )      portEXIT_CRITICAL_ISR( x )
#else
#define taskEXIT_CRITICAL_ISR( )        portEXIT_CRITICAL_ISR( )
#endif // ESP_PLATFORM
/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @endcond
 *
 * 禁用所有可屏蔽中断的宏。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup任务DISABLE_INTERRUPTS任务DISABLE_INTERUPTS
 * @endcond \组调度控制
 */
#define taskDISABLE_INTERRUPTS()           portDISABLE_INTERRUPTS()

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @endcond
 *
 * 启用微控制器中断的宏。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup taskENABLE_INTERRUPTS taskENABLE_INTERRUPTS
 * @endcond \组调度控制
 */
#define taskENABLE_INTERRUPTS()            portENABLE_INTERRUPTS()

/* xTaskGetSchedulerState（）返回的定义。taskSCHEDULER_SUSPENDED为0，以便在将configASSERT（）定义为assert（）语句中使用的常量时生成更优化的代码。*/
#define taskSCHEDULER_SUSPENDED      ( ( BaseType_t ) 0 )
#define taskSCHEDULER_NOT_STARTED    ( ( BaseType_t ) 1 )
#define taskSCHEDULER_RUNNING        ( ( BaseType_t ) 2 )


/*-----------------------------------------------------------
 * TASK CREATION API
 *----------------------------------------------------------*/

/**
 * 创建具有指定相关性的新任务。
 *
 * 此函数类似于xTaskCreate，但允许在SMP系统中设置任务关联。
 *
 * @param pvTaskCode 指向任务输入函数的指针。任务必须实现为永不返回（即连续循环），或者应使用vTaskDelete函数终止。
 *
 * @param pcName 任务的描述性名称。这主要用于方便调试。configMAX_TASK_NAME_LEN定义的最大长度-默认值为16。
 *
 * @param usStackDepth 指定为字节数的任务堆栈的大小。注意，这与普通FreeRTOS不同。
 *
 * @param pvParameters 将用作所创建任务的参数的指针。
 *
 * @param uxPriority 任务应运行的优先级。包括MPU支持的系统可以通过设置优先级参数的位端口PRIVILEGE_bit以特权（系统）模式创建任务。例如，要创建优先级为2的特权任务，uxPriority参数应设置为（2|portPRIVILEGE_BIT）。
 *
 * @param pvCreatedTask 用于传递回一个句柄，通过该句柄可以引用创建的任务。
 *
 * @param xCoreID 如果值为tskNO_AFINITY，则创建的任务不会固定到任何CPU，调度器可以在任何可用的内核上运行它。值0或1表示任务应固定到的CPU的索引号。指定大于（portNUM_PROCESSORS-1）的值将导致函数失败。
 *
 * @return 如果任务已成功创建并添加到就绪列表，则为pdPASS，否则为projdefs.h文件中定义的错误代码
 *
 * \内部组任务
 */
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    BaseType_t xTaskCreatePinnedToCore( TaskFunction_t pvTaskCode,
                                        const char * const pcName,
                                        const uint32_t usStackDepth,
                                        void * const pvParameters,
                                        UBaseType_t uxPriority,
                                        TaskHandle_t * const pvCreatedTask,
                                        const BaseType_t xCoreID);

#endif

/**
 * 创建新任务并将其添加到准备运行的任务列表中。
 *
 * 在FreeRTOS实现内部，任务使用两块内存。第一个块用于保存任务的数据结构。第二个块被任务用作其堆栈。如果任务是使用xTaskCreate（）创建的，那么两个内存块都会在xTaskCreate函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xTaskCreateStatic（）创建任务，则应用程序编写器必须提供所需的内存。因此，xTaskCreateStatic（）允许在不使用任何动态内存分配的情况下创建任务。
 *
 * 有关不使用任何动态内存分配的版本，请参阅xTaskCreateStatic（）。
 *
 * xTaskCreate（）只能用于创建对整个微控制器内存映射具有无限制访问权限的任务。包含MPU支持的系统也可以使用xTaskCreateRestricted（）创建MPU约束的任务。
 *
 * @param pvTaskCode 指向任务输入函数的指针。任务必须实现为永不返回（即连续循环），或者应使用vTaskDelete函数终止。
 *
 * @param pcName 任务的描述性名称。这主要用于方便调试。configMAX_TASK_NAME_LEN定义的最大长度-默认值为16。
 *
 * @param usStackDepth 指定为字节数的任务堆栈的大小。注意，这与普通FreeRTOS不同。
 *
 * @param pvParameters 将用作所创建任务的参数的指针。
 *
 * @param uxPriority 任务应运行的优先级。包括MPU支持的系统可以通过设置优先级参数的位端口PRIVILEGE_bit以特权（系统）模式创建任务。例如，要创建优先级为2的特权任务，uxPriority参数应设置为（2|portPRIVILEGE_BIT）。
 *
 * @param pvCreatedTask 用于传递回一个句柄，通过该句柄可以引用创建的任务。
 *
 * @return 如果任务已成功创建并添加到就绪列表，则为pdPASS，否则为projdefs.h文件中定义的错误代码
 *
 * @note 如果程序使用线程本地变量（用“__thread”关键字指定的变量），则将在任务堆栈上分配它们的存储空间。
 *
 * 示例用法：
 * @code{c}
 * //要创建的任务。
 * void vTaskCode（void*pvParameters）
 * {
 *   用于（；；）
 *   {
 *       //此处显示任务代码。
 *   }
 * }
 *
 * //创建任务的函数。
 * void vOtherFunction（void）
 * {
 * 静态uint8_t ucParameterToPass；
 * TaskHandle_t xHandle=NULL；
 *
 *   //创建任务，存储句柄。注意，传递的参数ucParameterToPass
 *   //必须在任务的生存期内存在，因此在本例中声明为静态。如果只是一个
 *   //一个自动堆栈变量，到那时它可能已经不存在，或者至少已经损坏
 *   //新任务尝试访问它。
 *   xTaskCreate（vTaskCode，“NAME”，STACK_SIZE，&ucParameterToPass，tskIDLE_PRIORITY，&xHandle）；
 *   configASSERT（xHandle）；
 *
 *   //使用句柄删除任务。
 *   if（xHandle！=NULL）
 *   {
 *      vTaskDelete（xHandle）；
 *   }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskCreate xTaskCreate
 * @endcond \内部组任务
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

    static inline IRAM_ATTR BaseType_t xTaskCreate(
                            TaskFunction_t pvTaskCode,
                            const char * const pcName,     /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
                            const uint32_t usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask) PRIVILEGED_FUNCTION
    {
        return xTaskCreatePinnedToCore( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, tskNO_AFFINITY );
    }

#endif




/**
 * 创建具有指定相关性的新任务。
 *
 * 此函数类似于xTaskCreateStatic，但允许在SMP系统中指定任务关联。
 *
 * @param pvTaskCode 指向任务输入函数的指针。任务必须实现为永不返回（即连续循环），或者应使用vTaskDelete函数终止。
 *
 * @param pcName 任务的描述性名称。这主要用于方便调试。字符串的最大长度由FreeRTOSConfig.h中的configMAX_TASK_NAME_LEN定义。
 *
 * @param ulStackDepth 指定为字节数的任务堆栈的大小。注意，这与普通FreeRTOS不同。
 *
 * @param pvParameters 将用作所创建任务的参数的指针。
 *
 * @param uxPriority 任务运行的优先级。
 *
 * @param pxStackBuffer 必须指向至少具有ulStackDepth索引的StackType_t数组，然后该数组将用作任务的堆栈，不需要动态分配堆栈。
 *
 * @param pxTaskBuffer 必须指向StaticTask_t类型的变量，然后该变量将用于保存任务的数据结构，从而不需要动态分配内存。
 *
 * @param xCoreID 如果值为tskNO_AFINITY，则创建的任务不会固定到任何CPU，调度器可以在任何可用的内核上运行它。值0或1表示任务应固定到的CPU的索引号。指定大于（portNUM_PROCESSORS-1）的值将导致函数失败。
 *
 * @return 如果pxStackBuffer或pxTaskBuffer都不为NULL，则将创建任务并返回pdPASS。如果pxStackBuffer或pxTaskBuffer为NULL，则不会创建任务，并返回errCOULD_not_ALLOCATE_REQUIRED_MEMORY。
 *
 * \内部组任务
 */
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    TaskHandle_t xTaskCreateStaticPinnedToCore( TaskFunction_t pvTaskCode,
                                                const char * const pcName,
                                                const uint32_t ulStackDepth,
                                                void * const pvParameters,
                                                UBaseType_t uxPriority,
                                                StackType_t * const pxStackBuffer,
                                                StaticTask_t * const pxTaskBuffer,
                                                const BaseType_t xCoreID );
#endif /* 配置支持状态分配*/

/**
 * 创建新任务并将其添加到准备运行的任务列表中。
 *
 * 在FreeRTOS实现内部，任务使用两块内存。第一个块用于保存任务的数据结构。第二个块被任务用作其堆栈。如果任务是使用xTaskCreate（）创建的，那么两个内存块都会在xTaskCreate函数内自动动态分配。（参见http://www.freertos.org/a00111.html). 如果使用xTaskCreateStatic（）创建任务，则应用程序编写器必须提供所需的内存。因此，xTaskCreateStatic（）允许在不使用任何动态内存分配的情况下创建任务。
 *
 * @param pvTaskCode 指向任务输入函数的指针。任务必须实现为永不返回（即连续循环），或者应使用vTaskDelete函数终止。
 *
 * @param pcName 任务的描述性名称。这主要用于方便调试。字符串的最大长度由FreeRTOSConfig.h中的configMAX_TASK_NAME_LEN定义。
 *
 * @param ulStackDepth 指定为字节数的任务堆栈的大小。注意，这与普通FreeRTOS不同。
 *
 * @param pvParameters 将用作所创建任务的参数的指针。
 *
 * @param uxPriority 任务运行的优先级。
 *
 * @param pxStackBuffer 必须指向至少具有ulStackDepth索引的StackType_t数组，然后该数组将用作任务的堆栈，不需要动态分配堆栈。
 *
 * @param pxTaskBuffer 必须指向StaticTask_t类型的变量，然后该变量将用于保存任务的数据结构，从而不需要动态分配内存。
 *
 * @return 如果pxStackBuffer或pxTaskBuffer都不为NULL，则将创建任务并返回pdPASS。如果pxStackBuffer或pxTaskBuffer为NULL，则不会创建任务，并返回errCOULD_not_ALLOCATE_REQUIRED_MEMORY。
 *
 * @note 如果程序使用线程本地变量（用“__thread”关键字指定的变量），则将在任务堆栈上分配它们的存储空间。
 *
 * 示例用法：
 * @code{c}
 *
 *  //标注正在创建的任务将用作其堆栈的缓冲区。
 *  //注意：这是堆栈将容纳的字节数，而不是
 *  //在vanilla FreeRTOS中找到的单词。
 * #定义STACK_SIZE 200
 *
 *  //结构，用于保存正在创建的任务的TCB。
 *  静态任务_ t x任务缓冲区；
 *
 *  //正在创建的任务将用作其堆栈的缓冲区。注意，这是
 *  //StackType_t变量数组。StackType_t的大小取决于
 *  //RTOS端口。
 *  堆栈类型_ x堆栈[STACK_SIZE]；
 *
 *  //实现正在创建的任务的函数。
 *  void vTaskCode（void*pvParameters）
 *  {
 *      //参数值应为1，因为在
 *      //pvParameters值。
 *      configASSERT（（uint32_t）pvParameters==1UL）；
 *
 *      用于（；；）
 *      {
 *          //此处显示任务代码。
 *      }
 *  }
 *
 *  //创建任务的函数。
 *  void vOtherFunction（void）
 *  {
 *      TaskHandle_t xHandle=NULL；
 *
 *      //在不使用任何动态内存分配的情况下创建任务。
 *      xHandle=xTaskCreateStatic(
 *                    vTaskCode，//实现任务的函数。
 *                    “NAME”，//任务的文本名称。
 *                    STACK_SIZE，//堆栈大小以字节为单位，而不是以单词为单位。
 *                    （void*）1，//传入任务的参数。
 *                    tskIDLE_PRIORITY，//创建任务的优先级。
 *                    xStack，//要用作任务堆栈的数组。
 *                    &xTaskBuffer）；//用于保存任务数据结构的变量。
 *
 *      //puxStackBuffer和pxTaskBuffer不为NULL，因此任务将具有
 *      //已创建，xHandle将是任务的句柄。使用手柄
 *      //以暂停任务。
 *      vTaskSuspend（xHandle）；
 *  }
 * @endcode \内部组任务
 */

#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    static inline IRAM_ATTR TaskHandle_t xTaskCreateStatic(
                                    TaskFunction_t pvTaskCode,
                                    const char * const pcName,     /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
                                    const uint32_t ulStackDepth,
                                    void * const pvParameters,
                                    UBaseType_t uxPriority,
                                    StackType_t * const puxStackBuffer,
                                    StaticTask_t * const pxTaskBuffer) PRIVILEGED_FUNCTION
    {
        return xTaskCreateStaticPinnedToCore( pvTaskCode, pcName, ulStackDepth, pvParameters, uxPriority, puxStackBuffer, pxTaskBuffer, tskNO_AFFINITY );
    }
#endif /* 配置支持状态分配*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskCreateRestricted（TaskParameters_t*pxTaskDefinition，TaskHandle_t*pxCreatedTask）；
 * @endcode
 * @endcond
 *
 * 仅当configSUPPORT_DYNAMIC_ALLOCATION设置为1时可用。
 *
 * xTaskCreateRestricted（）只能在包含MPU实现的系统中使用。
 *
 * 创建新任务并将其添加到准备运行的任务列表中。函数参数定义分配给任务的内存区域和相关访问权限。
 *
 * 有关不使用任何动态内存分配的版本，请参阅xTaskCreateRestrictedStatic（）。
 *
 * @param pxTaskDefinition 指向一个结构的指针，该结构包含每个普通xTaskCreate（）参数的成员（请参阅xTaskCreate）API文档）以及可选堆栈缓冲区和内存区域定义。
 *
 * @param pxCreatedTask 用于传递回一个句柄，通过该句柄可以引用创建的任务。
 *
 * 如果任务已成功创建并添加到就绪列表，则返回pdPASS，否则返回文件projdefs.h中定义的错误代码
 *
 * 示例用法：
 * @code{c}
 * //创建定义要创建的任务的TaskParameters_t结构。
 * 静态常量任务参数_t xCheckTaskParameters=
 * {
 *  vATask，//pvTaskCode-实现任务的函数。
 *  “ATask”，//pcName-仅任务的文本名称，以帮助调试。
 *  100，//usStackDepth-堆栈大小（以字定义）。
 *  NULL，//pvParameters-作为函数参数传入任务函数。
 *  （1UL|portPRIVILEGE_BIT），//uxPriority-任务优先级，如果任务应在特权状态下运行，则设置portPRIVILIGE_BIT。
 *  cStackBuffer，//puxStackBuffer-用作任务堆栈的缓冲区。
 *
 *  //xRegions—最多分配三个单独的内存区域，供
 *  //任务，具有适当的访问权限。不同的处理器具有
 *  //不同的内存对齐要求-请参阅FreeRTOS文档
 *  //获取完整信息。
 *  {
 *      //基址长度参数
 *      ｛cReadWriteArray，32，端口MPU_REGION_READ_WRITE｝，
 *      ｛cReadOnlyArray，32，端口MPU_REGION_READ_ONLY｝，
 *      ｛cPrivilegeOnlyAccessArray，128，端口MPU_REGION_PRIVILEGED_READ_WRITE｝
 *  }
 * };
 *
 * int main（无效）
 * {
 * 任务句柄_t xHandle；
 *
 *  //从上面定义的常量结构创建任务。任务句柄
 *  //请求（第二个参数不是NULL），但在本例中
 *  //因为它没有实际使用。
 *  xTaskCreateRestricted（&xRegTest1Parameters，&xHandle）；
 *
 *  //启动调度程序。
 *  vTaskStartScheduler（）；
 *
 *  //仅当内存不足以创建空闲时才会到达此处
 *  //和/或定时器任务。
 *  用于（；；）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskCreateRestricted xTaskCreate受限
 * @endcond \内部组任务
 */
#if ( portUSING_MPU_WRAPPERS == 1 )
    BaseType_t xTaskCreateRestricted( const TaskParameters_t * const pxTaskDefinition,
                                      TaskHandle_t * pxCreatedTask ) PRIVILEGED_FUNCTION;
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskCreateRestrictedStatic（TaskParameters_t*pxTaskDefinition，TaskHandle_t*pxCreatedTask）；
 * @endcode
 * @endcond
 *
 * 仅当configSUPPORT_STATIC_ALLOCATION设置为1时可用。
 *
 * xTaskCreateRestrictedStatic（）只能在包含MPU实现的系统中使用。
 *
 * 在FreeRTOS实现内部，任务使用两块内存。第一个块用于保存任务的数据结构。第二个块被任务用作其堆栈。如果任务是使用xTaskCreateRestricted（）创建的，则堆栈由应用程序编写器提供，用于保存任务数据结构的内存将在xTaskCreaterestrictd（）函数内自动动态分配。如果使用xTaskCreateRestrictedStatic（）创建任务，那么应用程序编写器也必须提供用于保存任务数据结构的内存。xTaskCreateRestrictedStatic（）因此允许在不使用任何动态内存分配的情况下创建内存保护任务。
 *
 * @param pxTaskDefinition 指向一个结构的指针，该结构包含每个普通xTaskCreate（）参数的成员（请参阅xTaskCreate）API文档）以及可选堆栈缓冲区和内存区域定义。如果configSUPPORT_STATIC_ALLOCATION设置为1，则该结构包含一个附加成员，该成员用于指向StaticTask_t类型的变量，然后用于保存任务的数据结构。
 *
 * @param pxCreatedTask 用于传递回一个句柄，通过该句柄可以引用创建的任务。
 *
 * 如果任务已成功创建并添加到就绪列表，则返回pdPASS，否则返回文件projdefs.h中定义的错误代码
 *
 * 示例用法：
 * @code{c}
 * //创建定义要创建的任务的TaskParameters_t结构。
 * //StaticTask_t变量仅在以下情况下包含在结构中
 * //configSUPPORT_STATIC_ALLOCATION设置为1。PRIVILEGED_DATA宏可以
 * //用于强制变量进入RTOS内核的特权数据区域。
 * 静态PRIVILEGED_DATA静态任务_ t xTaskBuffer；
 * 静态常量任务参数_t xCheckTaskParameters=
 * {
 *  vATask，//pvTaskCode-实现任务的函数。
 *  “ATask”，//pcName-仅任务的文本名称，以帮助调试。
 *   100，//usStackDepth-以字节定义的堆栈大小。
 *  NULL，//pvParameters-作为函数参数传入任务函数。
 *  （1UL|portPRIVILEGE_BIT），//uxPriority-任务优先级，如果任务应在特权状态下运行，则设置portPRIVILIGE_BIT。
 *  cStackBuffer，//puxStackBuffer-用作任务堆栈的缓冲区。
 *
 *  //xRegions—最多分配三个单独的内存区域，供
 *  //任务，具有适当的访问权限。不同的处理器具有
 *  //不同的内存对齐要求-请参阅FreeRTOS文档
 *  //获取完整信息。
 *  {
 *      //基址长度参数
 *      ｛cReadWriteArray，32，端口MPU_REGION_READ_WRITE｝，
 *      ｛cReadOnlyArray，32，端口MPU_REGION_READ_ONLY｝，
 *      ｛cPrivilegeOnlyAccessArray，128，端口MPU_REGION_PRIVILEGED_READ_WRITE｝
 *  }
 *
 *  &xTaskBuffer；//保存任务的数据结构。
 * };
 *
 * int main（无效）
 * {
 * 任务句柄_t xHandle；
 *
 *  //从上面定义的常量结构创建任务。任务句柄
 *  //请求（第二个参数不是NULL），但在本例中
 *  //因为它没有实际使用。
 *  xTaskCreateRestricted（&xRegTest1Parameters，&xHandle）；
 *
 *  //启动调度程序。
 *  vTaskStartScheduler（）；
 *
 *  //仅当内存不足以创建空闲时才会到达此处
 *  //和/或定时器任务。
 *  用于（；；）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskCreateRestrictedStatic xTaskCreateRestrictedStatic
 * @endcond \内部组任务
 */
#if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
    BaseType_t xTaskCreateRestrictedStatic( const TaskParameters_t * const pxTaskDefinition,
                                            TaskHandle_t * pxCreatedTask ) PRIVILEGED_FUNCTION;
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskAllocateMPURegions（TaskHandle_t xTask，const MemoryRegion_t*const pxRegions）；
 * @endcode
 * @endcond
 *
 * 当通过调用xTaskCreateRestricted（）创建受限制的任务时，内存区域被分配给该任务。可以使用vTaskAllocateMPURegions（）重新定义这些区域。
 *
 * @param xTask 正在更新的任务的句柄。
 *
 * @param pxRegions 指向包含新内存区域定义的MemoryRegion_t结构的指针。
 *
 * 示例用法：
 * @code{c}
 * //定义配置MPU区域的MemoryRegion_t结构数组
 * //允许从
 * //ucOneKByte数组。最大3个可定义区域中的另外两个是
 * //未使用，因此设置为零。
 * 静态常量MemoryRegion_t xAltRegions[portNUM_CONFIGURALE_REGIONS]=
 * {
 *  //基址长度参数
 *  ｛ucOneKByte，1024，端口MPU_REGION_READ_WRITE｝，
 *  { 0,                0,          0 },
 *  { 0,                0,          0 }
 * };
 *
 * void vATask（void*pvParameters）
 * {
 *  //创建此任务时，它可以访问
 *  //由MPU配置定义的存储器。在某种程度上
 *  //希望将这些MPU区域替换为
 *  //上面的xAltRegions常量结构。调用vTaskAllocateMPURegions（）
 *  //为此目的。NULL用作任务句柄，表示
 *  //函数应修改调用任务的MPU区域。
 *  vTaskAllocateMPUR区域（NULL，xAltRegions）；
 *
 *  //现在，任务可以继续其功能，但从这一点开始，只能
 *  //访问其堆栈和ucOneKByte数组（除非任何其他静态
 *  //定义或共享区域已在其他地方声明）。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskCreateRestricted xTaskCreate受限
 * @endcond \内部组任务
 */
void vTaskAllocateMPURegions( TaskHandle_t xTask,
                              const MemoryRegion_t * const pxRegions ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskDelete（TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * INCLUDE_vTaskDelete必须定义为1才能使用此函数。有关详细信息，请参阅配置部分。
 *
 * 从RTOS实时内核的管理中删除任务。正在删除的任务将从所有就绪、阻止、暂停和事件列表中删除。
 *
 * 注意：空闲任务负责从已删除的任务中释放内核分配的内存。因此，如果您的应用程序调用vTaskDelete（），则空闲任务不会耗尽微控制器处理时间，这一点非常重要。任务代码分配的内存不会自动释放，应该在删除任务之前释放。
 *
 * 有关使用vTaskDelete（）的示例代码，请参阅演示应用程序文件death.c。
 *
 * @param xTaskToDelete 要删除的任务的句柄。传递NULL将导致调用任务被删除。
 *
 * 示例用法：
 * @code{c}
 * void vOtherFunction（void）
 * {
 * 任务句柄_t xHandle；
 *
 *   //创建任务，存储句柄。
 *   xTaskCreate（vTaskCode，“NAME”，STACK_SIZE，NULL，tskIDLE_PRIORITY，&xHandle）；
 *
 *   //使用句柄删除任务。
 *   vTaskDelete（xHandle）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskDelete vTaskDelete
 * @endcond \内部组任务
 */
void vTaskDelete( TaskHandle_t xTaskToDelete ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------
 * TASK CONTROL API
 *----------------------------------------------------------*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskDelay（const TickType_t xTicksToDelay）；
 * @endcode
 * @endcond
 *
 * 将任务延迟给定的刻度数。任务保持阻塞的实际时间取决于节拍率。常量portTICK_PERIOD_MS可用于根据滴答率计算实时-分辨率为一个滴答周期。
 *
 * INCLUDE_vTaskDelay必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * vTaskDelay（）指定相对于调用vTaskDelay（）的时间，任务希望解除阻止的时间。例如，在调用vTaskDelay（）后，指定100个时间段将导致任务取消阻止100个时间。因此，vTaskDelay（）并不能提供控制周期性任务频率的好方法，因为通过代码的路径以及其他任务和中断活动将影响调用vTaskDela（）的频率，从而影响任务下一次执行的时间。请参见xTaskDelayUntil（），以获取用于促进固定频率执行的替代API函数。它通过指定调用任务应解除阻止的绝对时间（而不是相对时间）来实现这一点。
 *
 * @param xTicksToDelay 调用任务应阻止的时间量（以刻度周期为单位）。
 *
 * 示例用法：
 * @code{c}
 * void vTaskFunction（void*pvParameters）
 * {
 * //阻挡500ms。
 * 常量TickType_t xDelay=500/portTICK_PERIOD_MS；
 *
 *   用于（；；）
 *   {
 *       //只需每500毫秒切换一次LED，在每个切换之间进行切换。
 *       vToggleLED（）；
 *       vTaskDelay（xDelay）；
 *   }
 * }
 * @endcode
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskDelay vTaskDela
 * @endcond \内部组任务Ctrl
 */
void vTaskDelay( const TickType_t xTicksToDelay ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskDelayUntil（TickType_t*pxPreviousWakeTime，常量TickType_t xTimeIncrement）；
 * @endcode
 * @endcond
 *
 * INCLUDE_xTaskDelayUntil必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * 将任务延迟到指定时间。定期任务可以使用此功能，以确保恒定的执行频率。
 *
 * 此函数在一个重要方面与vTaskDelay（）不同：vTaskDela（）将导致任务从调用vTaskDela（）开始阻塞指定的时间。因此，很难单独使用vTaskDelay（）来生成固定的执行频率，因为任务开始执行和调用vTaskDela（）的任务之间的时间可能不是固定的[任务可能会通过调用之间的代码采取不同的路径，或者每次执行时可能会被中断或抢占不同的次数]。
 *
 * vTaskDelay（）指定相对于调用函数的时间的唤醒时间，而xTaskDelayUntil（）指定它希望解除阻止的绝对（精确）时间。
 *
 * 宏pdMS_TO_TICKS（）可用于计算以毫秒为单位指定的时间的刻度数，分辨率为一个刻度周期。
 *
 * @param pxPreviousWakeTime 指向保存上次取消阻止任务的时间的变量的指针。变量在首次使用前必须使用当前时间进行初始化（参见下面的示例）。此后，变量在xTaskDelayUntil（）中自动更新。
 *
 * @param xTimeIncrement 循环时间段。任务将在时间pxPreviousWakeTime+xTimeIncrement时取消阻止。使用相同的xTimeIncrement参数值调用xTaskDelayUntil将导致任务以固定的接口周期执行。
 *
 * @return 可用于检查任务是否实际延迟的值。如果任务延迟，则为pdTRUE，否则为pdFALSE。如果下一个预期唤醒时间已过，则任务不会延迟。
 *
 * 示例用法：
 * @code{c}
 * //每10个刻度执行一次操作。
 * void vTaskFunction（void*pvParameters）
 * {
 * TickType_t x上次唤醒时间；
 * 常量TickType_t x频率=10；
 * BaseType_t x延迟；
 *
 *     //用当前时间初始化xLastWakeTime变量。
 *     xLastWakeTime=xTaskGetTickCount（）；
 *     用于（；；）
 *     {
 *         //等待下一个循环。
 *         xWasDelayed=xTaskDelayUntil（&xLastWakeTime，xFrequency）；
 *
 *         //在此处执行操作。xWasDelayed值可用于确定
 *         //如果代码太长，是否错过了截止日期。
 *     }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskDelayUntil x任务延迟直到
 * @endcond \内部组任务Ctrl
 */
BaseType_t xTaskDelayUntil( TickType_t * const pxPreviousWakeTime,
                            const TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

/*
 * vTaskDelayUntil（）是旧版本的xTaskDelayUnitl（），不返回值。
 */
#define vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement )       \
{                                                                   \
    ( void ) xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement ); \
}


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskAbortDelay（TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * 在FreeRTOSConfig中，INCLUDE_xTaskAbortDelay必须定义为1。h表示此功能可用。
 *
 * 任务在等待事件时将进入“阻止”状态。它等待的事件可以是时间事件（等待一段时间），例如调用vTaskDelay（）时，也可以是对象上的事件，例如调用xQueueReceive（）或ulTaskNotifyTake（）时。如果在对xTaskAbortDelay（）的调用中使用了处于阻止状态的任务的句柄，则该任务将离开阻止状态，并从将该任务置于阻止状态的任何函数调用返回。
 *
 * 此函数没有“FromISR”版本，因为中断需要知道任务在哪个对象上被阻止，才能知道要执行哪些操作。例如，如果任务在队列中被阻止，则中断处理程序需要知道队列是否被锁定。
 *
 * @param xTask 要从“阻止”状态中删除的任务的句柄。
 *
 * @return 如果xTask引用的任务未处于“阻止”状态，则返回pdFAIL。否则将返回pdPASS。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskAbortDelay x任务中止延迟
 * @endcond \内部组任务Ctrl
 */
BaseType_t xTaskAbortDelay( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * UBaseType_t uxTaskPriorityGet（const TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * INCLUDE_uxTaskPriorityGet必须定义为1才能使用此函数。有关详细信息，请参阅配置部分。
 *
 * 获取任何任务的优先级。
 *
 * @param xTask 要查询的任务的句柄。传递NULL句柄会导致返回调用任务的优先级。
 *
 * @return xTask的优先级。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（void）
 * {
 * 任务句柄_t xHandle；
 *
 *   //创建一个任务，存储句柄。
 *   xTaskCreate（vTaskCode，“NAME”，STACK_SIZE，NULL，tskIDLE_PRIORITY，&xHandle）；
 *
 *   // ...
 *
 *   //使用句柄获取所创建任务的优先级。
 *   //它是用tskIDLE_PRIORITY创建的，但可能已更改
 *   //它本身。
 *   如果（uxTaskPriorityGet（xHandle）！=tsk空闲_优先级）
 *   {
 *       //任务已更改其优先级。
 *   }
 *
 *   // ...
 *
 *   //我们的优先级是否高于创建的任务？
 *   如果（uxTaskPriorityGet（xHandle）<uxTask优先级Get（NULL））
 *   {
 *       //我们的优先级（使用NULL句柄获得）更高。
 *   }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\解组uxTaskPriorityGet uxTask优先级Get
 * @endcond \内部组任务Ctrl
 */
UBaseType_t uxTaskPriorityGet( const TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * UBaseType_t uxTaskPriorityGetFromISR（const TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * 可以从ISR中使用的uxTaskPriorityGet（）版本。
 */
UBaseType_t uxTaskPriorityGetFromISR( const TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * eTaskState eTaskGetState（TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * INCLUDE_eTaskGetState必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * 获取任何任务的状态。状态由eTaskState枚举类型编码。
 *
 * @param xTask 要查询的任务的句柄。
 *
 * @return 调用函数时xTask的状态。注意，任务的状态可能会在被调用的函数和被调用任务测试的函数返回值之间发生变化。
 */
eTaskState eTaskGetState( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskGetInfo（TaskHandle_t xTask，TaskStatus_t*pxTaskStatus，BaseType_t xGetFreeStackSpace，eTaskState eState）；
 * @endcode
 * @endcond
 *
 * configUSE_TRACE_FACILITY必须定义为1才能使用此函数。有关详细信息，请参阅配置部分。
 *
 * 使用有关任务的信息填充TaskStatus_t结构。
 *
 * @param xTask 正在查询的任务的句柄。如果xTask为NULL，则将返回有关调用任务的信息。
 *
 * @param pxTaskStatus 指向TaskStatus_t结构的指针，该结构将填充有关使用xTask参数传递的句柄所引用的任务的信息。
 *
 * @param xGetFreeStackSpace TaskStatus_t结构包含一个成员，用于报告所查询任务的堆栈高位标记。计算堆栈高水位标记需要相对较长的时间，并且可能使系统暂时无响应-因此提供xGetFreeStackSpace参数以允许跳过高水位标记检查。如果xGetFreeStackSpace未设置为pdFALSE，则高水位线值将仅写入TaskStatus_t结构；
 *
 * @param eState TaskStatus_t结构包含一个成员，用于报告所查询任务的状态。获取任务状态不像简单的赋值那么快，因此提供了eState参数以允许从TaskStatus_t结构中省略状态信息。若要获取状态信息，请将eState设置为eInvalid，否则在eState中传递的值将作为TaskStatus_t结构中的任务状态报告。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（void）
 * {
 * 任务句柄_t xHandle；
 * 任务状态_ t x任务详细信息；
 *
 *  //从任务的名称获取任务的句柄。
 *  xHandle=xTaskGetHandle（“任务名称”）；
 *
 *  //检查句柄是否为空。
 *  configASSERT（xHandle）；
 *
 *  //使用句柄获取有关任务的更多信息。
 *  vTaskGetInfo（xHandle，
 *                &xTaskDetails，
 *                pdTRUE，//在xTaskDetails中包含高水位线。
 *                eInvalid）；//在xTaskDetails中包含任务状态。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskGetInfo vTaskGetInfo
 * @endcond \内部组任务Ctrl
 */
void vTaskGetInfo( TaskHandle_t xTask,
                   TaskStatus_t * pxTaskStatus,
                   BaseType_t xGetFreeStackSpace,
                   eTaskState eState ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskPrioritySet（TaskHandle_t xTask，UBaseType_t uxNewPriority）；
 * @endcode
 * @endcond
 *
 * INCLUDE_vTaskPrioritySet必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * 设置任何任务的优先级。
 *
 * 如果设置的优先级高于当前执行的任务，则在函数返回之前会发生上下文切换。
 *
 * @param xTask 正在为其设置优先级的任务的句柄。传递NULL句柄会导致设置调用任务的优先级。
 *
 * @param uxNewPriority 将设置任务的优先级。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（void）
 * {
 * 任务句柄_t xHandle；
 *
 *   //创建一个任务，存储句柄。
 *   xTaskCreate（vTaskCode，“NAME”，STACK_SIZE，NULL，tskIDLE_PRIORITY，&xHandle）；
 *
 *   // ...
 *
 *   //使用句柄提高所创建任务的优先级。
 *   vTaskPrioritySet（xHandle，tskIDLE_PRIORITY+1）；
 *
 *   // ...
 *
 *   //使用NULL句柄将优先级提高到相同的值。
 *   vTaskPrioritySet（空，tskIDLE_PRIORITY+1）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskPrioritySet vTaskPrioritSet
 * @endcond \内部组任务Ctrl
 */
void vTaskPrioritySet( TaskHandle_t xTask,
                       UBaseType_t uxNewPriority ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskSuspend（TaskHandle_t xTaskToSuspend）；
 * @endcode
 * @endcond
 *
 * INCLUDE_vTaskSuspend必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * 挂起任何任务。当任务被暂停时，无论其优先级如何，都不会获得任何微控制器处理时间。
 *
 * 对vTaskSuspend的调用不是累积的，即对同一任务调用两次vTaskSustain（）仍然只需要调用一次vTaskResume（）即可准备好挂起的任务。
 *
 * @param xTaskToSuspend 正在挂起的任务的句柄。传递NULL句柄将导致调用任务挂起。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（void）
 * {
 * 任务句柄_t xHandle；
 *
 *   //创建一个任务，存储句柄。
 *   xTaskCreate（vTaskCode，“NAME”，STACK_SIZE，NULL，tskIDLE_PRIORITY，&xHandle）；
 *
 *   // ...
 *
 *   //使用句柄挂起创建的任务。
 *   vTaskSuspend（xHandle）；
 *
 *   // ...
 *
 *   //创建的任务在此期间不会运行，除非
 *   //另一个任务调用vTaskResume（xHandle）。
 *
 *   //...
 *
 *
 *   //暂停我们自己。
 *   vTaskSuspend（NULL）；
 *
 *   //除非另一个任务调用vTaskResume，否则我们无法到达此处
 *   //以我们的句柄作为参数。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskSuspend vTaskSustain
 * @endcond \内部组任务Ctrl
 */
void vTaskSuspend( TaskHandle_t xTaskToSuspend ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskResume（TaskHandle_t xTaskToResume）；
 * @endcode
 * @endcond
 *
 * INCLUDE_vTaskSuspend必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * 恢复挂起的任务。
 *
 * 对vTaskSuspend（）的一次或多次调用已暂停的任务将通过对vTaskResume（）进行一次调用而可再次运行。
 *
 * @param xTaskToResume 正在准备的任务的句柄。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（void）
 * {
 * 任务句柄_t xHandle；
 *
 *   //创建一个任务，存储句柄。
 *   xTaskCreate（vTaskCode，“NAME”，STACK_SIZE，NULL，tskIDLE_PRIORITY，&xHandle）；
 *
 *   // ...
 *
 *   //使用句柄挂起创建的任务。
 *   vTaskSuspend（xHandle）；
 *
 *   // ...
 *
 *   //创建的任务在此期间不会运行，除非
 *   //另一个任务调用vTaskResume（xHandle）。
 *
 *   //...
 *
 *
 *   //自己恢复暂停的任务。
 *   vTaskResume（xHandle）；
 *
 *   //创建的任务将再次获得微控制器处理
 *   //根据其在系统内的优先级。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskResume vTaskResue
 * @endcond \内部组任务Ctrl
 */
void vTaskResume( TaskHandle_t xTaskToResume ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void xTaskResumeFromISR（TaskHandle_t xTaskToResume）；
 * @endcode
 * @endcond
 *
 * INCLUDE_xTaskResumeFromISR必须定义为1，此函数才能可用。有关详细信息，请参阅配置部分。
 *
 * vTaskResume（）的一种实现，可以从ISR中调用。
 *
 * 一个或多个对vTaskSuspend（）的调用已挂起的任务将通过对xTaskResumeFromISR（）的一次调用可再次运行。
 *
 * 如果中断有可能在任务暂停之前到达，则不应使用xTaskResumeFromISR（）将任务与中断同步，因为这可能会导致中断丢失。使用信号量作为同步机制可以避免这种可能性。
 *
 * @param xTaskToResume 正在准备的任务的句柄。
 *
 * @return pdTRUE，如果恢复任务会导致上下文切换，否则pdFALSE。ISR使用它来确定ISR之后是否需要上下文切换。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskResumeFromISR vTaskResueFromISR
 * @endcond \内部组任务Ctrl
 */
BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------
 * SCHEDULER CONTROL
 *----------------------------------------------------------*/
/**@秒！文档_排除_标题_节*/
/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskStartScheduler（void）；
 * @endcode
 * @endcond
 *
 * 启动实时内核滴答处理。在调用之后，内核可以控制执行哪些任务以及何时执行。

 * 注意：在ESP-IDF中，调度器在应用程序启动期间自动启动，不应从ESP-IDF应用程序调用vTaskStartScheduler（）。
 *
 * 请参见演示应用程序文件main。c是创建任务和启动内核的示例。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（void）
 * {
 *   //在启动内核之前至少创建一个任务。
 *   xTaskCreate（vTaskCode，“名称”，STACK_SIZE，NULL，tskIDLE_PRIORITY，NULL）；
 *
 *   //使用抢占启动实时内核。
 *   vTaskStartScheduler（）；
 *
 *   //除非任务调用vTaskEndScheduler（），否则无法到达此处
 * }
 * @endcode
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskStartScheduler vTaskStart调度器
 * @endcond \组调度控制
 */
void vTaskStartScheduler( void ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskEndScheduler（void）；
 * @endcode
 * @endcond
 *
 * 注意：在编写时，只有在PC上运行的x86实模式端口（代替DOS）实现了此功能。
 *
 * 停止实时内核滴答声。所有创建的任务将被自动删除，多任务处理（抢先或协作）将停止。然后从调用vTaskStartScheduler（）的点开始执行，就像vTaskStart调度器（）刚刚返回一样。
 *
 * 请参见演示应用程序文件main。c，例如使用vTaskEndScheduler（）的示例。
 *
 * vTaskEndScheduler（）要求在可移植层中定义退出函数（有关PC端口，请参见端口.c中的vPortEndScheduler）。这将执行特定于硬件的操作，例如停止内核滴答声。
 *
 * vTaskEndScheduler（）将释放内核分配的所有资源，但不会释放应用程序任务分配的资源。
 *
 * 示例用法：
 * @code{c}
 * void vTaskCode（void*pvParameters）
 * {
 *   用于（；；）
 *   {
 *       //此处显示任务代码。
 *
 *       //在某个时刻，我们希望结束实时内核处理
 *       //所以打电话。。。
 *       vTaskEndScheduler（）；
 *   }
 * }
 *
 * void vA函数（void）
 * {
 *   //在启动内核之前至少创建一个任务。
 *   xTaskCreate（vTaskCode，“名称”，STACK_SIZE，NULL，tskIDLE_PRIORITY，NULL）；
 *
 *   //使用抢占启动实时内核。
 *   vTaskStartScheduler（）；
 *
 *   //仅当vTaskCode（）任务调用
 *   //vTaskEndScheduler（）。当我们到达这里时，我们又回到了单一的任务
 *   //执行。
 * }
 * @endcode
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskEndScheduler vTaskEnd调度器
 * @endcond \组调度控制
 */
void vTaskEndScheduler( void ) PRIVILEGED_FUNCTION;

/**@结束秒*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskSuspendAll（void）；
 * @endcode
 * @endcond
 *
 * 挂起调度程序而不禁用中断。当调度程序挂起时，不会发生上下文切换。
 *
 * 调用vTaskSuspendAll（）后，在调用xTaskResumeAll（）之前，调用任务将继续执行，不会有被换出的风险。
 *
 * 当调度程序挂起时，不能调用可能导致上下文切换的API函数（例如，vTaskDelayUntil（）、xQueueSend（）等）。
 *
 * 示例用法：
 * @code{c}
 * void vTask1（void*pvParameters）
 * {
 *   用于（；；）
 *   {
 *       //此处显示任务代码。
 *
 *       // ...
 *
 *       //在某些情况下，任务希望在
 *       //它不想被换掉。它不能使用
 *       //taskENTER_CRICAL（）/taskEXIT_CRITICAL（）作为
 *       //操作可能会导致中断丢失-包括
 *       //滴答声。
 *
 *       //防止实时内核交换任务。
 *       vTaskSuspendAll（）；
 *
 *       //在此处执行操作。无需使用关键
 *       //因为我们有所有的微控制器处理时间。
 *       //在此期间，中断仍将运行，内核
 *       //将保持滴答计数。
 *
 *       // ...
 *
 *       //操作已完成。重新启动内核。
 *       xTaskResumeAll（）；
 *   }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskSuspendAll vTaskSuspendAll
 * @endcond \组调度控制
 */
void vTaskSuspendAll( void ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskResumeAll（无效）；
 * @endcode
 * @endcond
 *
 * 在通过调用vTaskSuspendAll（）暂停调度程序活动后，恢复该活动。
 *
 * xTaskResumeAll（）仅恢复调度程序。它不会取消暂停以前通过调用vTaskSuspend（）暂停的任务。
 *
 * @return 如果恢复调度程序导致上下文切换，则返回pdTRUE，否则返回pdFALSE。
 *
 * 示例用法：
 * @code{c}
 * void vTask1（void*pvParameters）
 * {
 *   用于（；；）
 *   {
 *       //此处显示任务代码。
 *
 *       // ...
 *
 *       //在某些情况下，任务希望在
 *       //它不想被换掉。它不能使用
 *       //taskENTER_CRICAL（）/taskEXIT_CRITICAL（）作为
 *       //操作可能会导致中断丢失-包括
 *       //滴答声。
 *
 *       //防止实时内核交换任务。
 *       vTaskSuspendAll（）；
 *
 *       //在此处执行操作。无需使用关键
 *       //因为我们有所有的微控制器处理时间。
 *       //在此期间，中断仍将运行
 *       //将保持内核计时计数。
 *
 *       // ...
 *
 *       //操作已完成。重新启动内核。我们想强迫
 *       //上下文切换-但如果恢复调度程序则没有意义
 *       //已导致上下文切换。
 *       if（！xTaskResumeAll（））
 *       {
 *            taskYIELD（）；
 *       }
 *   }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskResumeAll xTaskResueAll
 * @endcond \组调度控制
 */
BaseType_t xTaskResumeAll( void ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------
 * TASK UTILITIES
 *----------------------------------------------------------*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * TickType_t xTaskGetTickCount（无效）；
 * @endcode
 * @endcond
 *
 * @return 自调用vTaskStartScheduler以来的滴答计数。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskGetTickCount x任务获取TickCount
 * @endcond \内部组任务工具
 */
TickType_t xTaskGetTickCount( void ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * TickType_t xTaskGetTickCountFromISR（无效）；
 * @endcode
 * @endcond
 *
 * @return 自调用vTaskStartScheduler以来的滴答计数。
 *
 * 这是xTaskGetTickCount（）的一个版本，可以安全地从ISR调用，前提是TickType_t是所使用的微控制器的自然字大小，或者不支持或不使用中断嵌套。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskGetTickCountFromISR xTaskGetTickCountFromISR
 * @endcond \内部组任务工具
 */
TickType_t xTaskGetTickCountFromISR( void ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * uint16_t uxTaskGetNumberOfTasks（无效）；
 * @endcode
 * @endcond
 *
 * @return 实时内核当前正在管理的任务数。这包括所有就绪、被阻止和暂停的任务。已删除但尚未由空闲任务释放的任务也将包括在计数中。
 *
 * @cond !DOC_SINGLE_GROUP\解组uxTaskGetNumberOfTasks uxTaskGet NumberOfTask
 * @endcond \内部组任务工具
 */
UBaseType_t uxTaskGetNumberOfTasks( void ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * char*pcTaskGetName（TaskHandle_t xTaskToQuery）；
 * @endcode
 * @endcond
 *
 * @return 句柄xTaskToQuery引用的任务的文本（人类可读）名称。任务可以通过传递自己的句柄或将xTaskToQuery设置为NULL来查询自己的名称。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup pcTaskGetName pcTaskGet名称
 * @endcond \内部组任务工具
 */
char * pcTaskGetName( TaskHandle_t xTaskToQuery ) PRIVILEGED_FUNCTION;     /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * TaskHandle_t xTaskGetHandle（const char*pcNameToQuery）；
 * @endcode
 * @endcond
 *
 * 注意：此功能需要相对较长的时间才能完成，应谨慎使用。
 *
 * @return 具有可读名称pcNameToQuery的任务的句柄。如果找不到匹配的名称，则返回NULL。在FreeRTOSConfig中，INCLUDE_xTaskGetHandle必须设置为1。h表示pcTaskGetHandle（）可用。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup pcTaskGetHandle pcTaskGetHandle
 * @endcond \内部组任务工具
 */
TaskHandle_t xTaskGetHandle( const char * pcNameToQuery ) PRIVILEGED_FUNCTION;     /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/

/**
 * 返回与xTask关联的堆栈的高水位标记。
 *
 * 在FreeRTOSConfig中，INCLUDE_uxTaskGetStackHighWaterMark必须设置为1。h表示此功能可用。
 *
 * 返回与xTask关联的堆栈的高水位标记。也就是说，自任务开始以来，最小的可用堆栈空间（以字节而不是字为单位，不像普通的FreeRTOS）。返回的数字越小，任务越接近溢出堆栈。
 *
 * uxTaskGetStackHighWaterMark2（）和uxTaskgetStackHighWater Mark2（（）除了返回类型之外都是相同的。使用configSTACK_DEPTH_TYPE允许用户确定返回类型。它解决了8位类型上的值溢出问题，而不会破坏期望8位返回类型的应用程序的向后兼容性。
 *
 * @param xTask 与要检查的堆栈关联的任务的句柄。将xTask设置为NULL以检查调用任务的堆栈。
 *
 * @return 自xTask引用的任务创建以来，可用堆栈空间的最小数量（以字节而非单词表示，与普通的FreeRTOS不同）。
 */
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * 返回与xTask关联的堆栈的开头。
 *
 * 在FreeRTOSConfig中，INCLUDE_uxTaskGetStackHighWaterMark2必须设置为1。h表示此功能可用。
 *
 * 返回与xTask关联的堆栈的高水位标记。也就是说，自任务开始以来，存在的最小可用堆栈空间（换句话说，在32位机器上，值1表示4字节）。返回的数字越小，任务越接近溢出堆栈。
 *
 * uxTaskGetStackHighWaterMark2（）和uxTaskgetStackHighWater Mark2（（）除了返回类型之外都是相同的。使用configSTACK_DEPTH_TYPE允许用户确定返回类型。它解决了8位类型上的值溢出问题，而不会破坏期望8位返回类型的应用程序的向后兼容性。
 *
 * @param xTask 与要检查的堆栈关联的任务的句柄。将xTask设置为NULL以检查调用任务的堆栈。
 *
 * @return 自创建xTask引用的任务以来，已存在的最小可用堆栈空间量（即堆栈上的实际空间，而不是字节）。
 */
configSTACK_DEPTH_TYPE uxTaskGetStackHighWaterMark2( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * 返回与xTask关联的堆栈的开头。
 *
 * 在FreeRTOSConfig中，INCLUDE_pxTaskGetStackStart必须设置为1。h表示此功能可用。
 *
 * 返回最低堆栈内存地址，无论堆栈是向上还是向下增长。
 *
 * @param xTask 与返回的堆栈关联的任务的句柄。将xTask设置为NULL以返回调用任务的堆栈。
 *
 * @return 指向堆栈开头的指针。
 */
uint8_t* pxTaskGetStackStart( TaskHandle_t xTask) PRIVILEGED_FUNCTION;

/* 使用跟踪宏时，有时需要包含任务。完成后，TaskHookFunction_t尚未定义，因此以下两个原型将导致编译错误。如果configUSE_APPLICATION_TASK_TAG配置常量明确要求包含这两个原型，则可以通过简单地防止包含这两种原型来解决这一问题。*/
#ifdef configUSE_APPLICATION_TASK_TAG
    #if configUSE_APPLICATION_TASK_TAG == 1
/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code{c}
 * void vTaskSetApplicationTaskTag（TaskHandle_t xTask，TaskHookFunction_t pxHookFunction）；
 * @endcode
 * @endcond
 *
 * 将pxHookFunction设置为任务xTask使用的任务钩子函数。
 * @param xTask 将Passing xTask的钩子函数设置为NULL的任务句柄具有设置调用任务钩子函数的效果。
 * @param pxHookFunction  指向钩子函数的指针。
 */
        void vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                         TaskHookFunction_t pxHookFunction ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code{c}
 * void xTaskGetApplicationTaskTag（TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * 返回分配给任务xTask的pxHookFunction值。不要从中断服务例程调用-改为调用xTaskGetApplicationTaskTagFromISR（）。
 */
        TaskHookFunction_t xTaskGetApplicationTaskTag( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code{c}
 * void xTaskGetApplicationTaskTagFromISR（TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * 返回分配给任务xTask的pxHookFunction值。可以从中断服务例程调用。
 */
        TaskHookFunction_t xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;
    #endif /* configUSE_APPLICATION_TASK_TAG==1*/
#endif /* 如果定义configUSE_APPLICATION_TASK_TAG*/

#if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )

    /**
     * 设置特定于给定任务的本地存储指针。
     *
     * 每个任务都包含一个指针数组，其大小由FreeRTOSConfig.h中的configNUM_THREAD_LOCAL_STORAGE_pointers设置确定。内核不使用指针本身，因此应用程序编写器可以将指针用于任何目的。
     *
     * @param xTaskToSet  设置线程本地存储指针的任务
     * @param xIndex 要设置的指针的索引，从0到configNUM_THREAD_LOCAL_STORAGE_POINTERS-1。
     * @param pvValue  要设置的指针值。
     */
    void vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                            BaseType_t xIndex,
                                            void * pvValue ) PRIVILEGED_FUNCTION;


    /**
     * 获取特定于给定任务的本地存储指针。
     *
     * 每个任务都包含一个指针数组，其大小由FreeRTOSConfig.h中的configNUM_THREAD_LOCAL_STORAGE_pointers设置确定。内核不使用指针本身，因此应用程序编写器可以将指针用于任何目的。
     *
     * @param xTaskToQuery  获取线程本地存储指针的任务
     * @param xIndex 要获取的指针的索引，从0到configNUM_THREAD_LOCAL_STORAGE_POINTERS-1。
     * @return  指针值
     */
    void * pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                               BaseType_t xIndex ) PRIVILEGED_FUNCTION;

    #if ( configTHREAD_LOCAL_STORAGE_DELETE_CALLBACKS )

        /**
         * 本地存储指针删除回调的原型。
         */
        typedef void (*TlsDeleteCallbackFunction_t)( int, void * );

        /**
         * 设置本地存储指针和删除回调。
         *
         * 每个任务都包含一个指针数组，其大小由FreeRTOSConfig.h中的configNUM_THREAD_LOCAL_STORAGE_pointers设置确定。内核不使用指针本身，因此应用程序编写器可以将指针用于任何目的。
         *
         * 为任务设置的本地存储指针可以引用动态分配的资源。此函数类似于vTaskSetThreadLocalStoragePointer，但提供了在删除任务时释放这些资源的方法。对于每个指针，都可以设置回调函数。删除任务时将调用此函数，并将本地存储指针索引和值作为参数。
         *
         * @param xTaskToSet  设置线程本地存储指针的任务
         * @param xIndex 要设置的指针的索引，从0到configNUM_THREAD_LOCAL_STORAGE_POINTERS-1。
         * @param pvValue  要设置的指针值。
         * @param pvDelCallback  在删除任务时调用以释放本地存储指针的函数。
         */
        void vTaskSetThreadLocalStoragePointerAndDelCallback( TaskHandle_t xTaskToSet, BaseType_t xIndex, void *pvValue, TlsDeleteCallbackFunction_t pvDelCallback);
    #endif

#endif

#if ( configCHECK_FOR_STACK_OVERFLOW > 0 )

     /**
      * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
      * @code{c}
      * void vApplicationStackOverflowHook( TaskHandle_t xTask char *pcTaskName); @endcode @endcond当检测到任务的堆栈溢出时，调用应用程序堆栈溢出钩子。
      *
      * 有关堆栈溢出检测的详细信息，请参阅：https://www.FreeRTOS.org/Stacks-and-stack-overflow-checking.html
      *
      * @param xTask 刚刚超出堆栈边界的任务。
      * @param pcTaskName 包含违规任务名称的字符串。
      */
     void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                               char * pcTaskName );

#endif

#if  (  configUSE_TICK_HOOK > 0 )
    /**
     * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
     * @code{c}
     * void vApplicationTickHook（void）；
     * @endcode
     * @endcond
     *
     * 任何操作系统工作完成后，都会在系统滴答处理程序中调用此钩子函数。
     */
    void vApplicationTickHook( void ); /*绒毛e526符号未定义，因为它是应用程序回调。*/

#endif

#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    /**
     * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
     * @code{c}
     * void vApplicationGetIdleTaskMemory（StaticTask_t**ppxIdleTaskTCBBuffer，StackType_t**ppxMidleTaskStackBuffer，uint32_t*pulIdleTaskStackSize）
     * @endcode
     * @endcond 此函数用于向FreeRTOS提供静态分配的内存块，以保存空闲任务TCB。设置configSUPPORT_STATIC_ALLOCATION时需要此函数。有关详细信息，请参阅此URI：https://www.FreeRTOS.org/a00110.html#configSUPPORT_STATIC_ALLOCATION
     *
     * @param ppxIdleTaskTCBBuffer 静态分配的TCB缓冲区的句柄
     * @param ppxIdleTaskStackBuffer 为空闲任务静态分配堆栈缓冲区的句柄
     * @param pulIdleTaskStackSize 指向将容纳在分配的堆栈缓冲区中的元素数的指针
     */
    void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                               StackType_t ** ppxIdleTaskStackBuffer,
                                               uint32_t * pulIdleTaskStackSize ); /*绒毛e526符号未定义，因为它是应用程序回调。*/
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code{c}
 * BaseType_t xTaskCallApplicationTaskHook（TaskHandle_t xTask，void*pvParameter）；
 * @endcode
 * @endcond
 *
 * 调用与xTask关联的钩子函数。将xTask作为NULL传递具有调用正在运行的任务（调用任务）钩子函数的效果。
 *
 * @param xTask  要为其调用钩子的任务的句柄。
 * @param pvParameter  传递给任务的钩子函数的参数，以便根据需要进行解释。返回值是用户注册的任务钩子函数返回的值。
 */
BaseType_t xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                         void * pvParameter ) PRIVILEGED_FUNCTION;

/**
 * 只有在FreeRTOSConfig.h中将INCLUDE_xTaskGetIdleTaskHandle设置为1时，xTaskGetIdle TaskHandle（）才可用。
 *
 * 只需返回空闲任务的句柄。在计划程序启动之前调用xTaskGetIdleTaskHandle（）是无效的。
 */
TaskHandle_t xTaskGetIdleTaskHandle( void ) PRIVILEGED_FUNCTION;

/**
 * configUSE_TRACE_FACILITY必须在FreeRTOSConfig中定义为1。h表示uxTaskGetSystemState（）可用。
 *
 * uxTaskGetSystemState（）为系统中的每个任务填充TaskStatus_t结构。TaskStatus_t结构包含任务句柄、任务名称、任务优先级、任务状态和任务消耗的总运行时间的成员。有关完整成员列表，请参阅此文件中的TaskStatus_t结构定义。
 *
 * 注意：此函数仅用于调试，因为它的使用会导致调度程序长时间处于挂起状态。
 *
 * @param pxTaskStatusArray 指向TaskStatus_t结构数组的指针。对于受RTOS控制的每个任务，阵列必须至少包含一个TaskStatus_t结构。RTOS控制下的任务数量可以使用uxTaskGetNumberOfTasks（）API函数确定。
 *
 * @param uxArraySize pxTaskStatusArray参数指向的数组的大小。大小指定为数组中的索引数或数组中包含的TaskStatus_t结构数，而不是数组中的字节数。
 *
 * @param pulTotalRunTime 如果在FreeRTOSConfig中将configGENERATE_RUN_TIME_STATS设置为1。然后通过uxTaskGetSystemState（）将pulTotalRunTime设置为总运行时间（由运行时间统计时钟定义，请参见https://www.FreeRTOS.org/rtos-run-time-stats.html)自从目标启动以来。pulTotalRunTime可以设置为NULL以忽略总运行时间信息。
 *
 * @return uxTaskGetSystemState（）填充的TaskStatus_t结构数。这应该等于uxTaskGetNumberOfTasks（）API函数返回的数字，但如果在uxArraySize参数中传递的值太小，则将为零。
 *
 * 示例用法：
 * @code{c}
 *  //这个示例演示了一个人类可读的运行时统计表
 *  //信息由uxTaskGetSystemState（）提供的原始数据生成。
 *  //人可读表被写入pcWriteBuffer
 *  void vTaskGetRunTimeStats（char*pcWriteBuffer）
 *  {
 *  任务状态_t*pxTaskStatusArray；
 *  易失性UBaseType_t uxArraySize，x；
 *  uint32_t ulTotalRunTime，ulStatsAsPercage；
 *
 *      //确保写入缓冲区不包含字符串。
 * *pcWriteBuffer=0x0；
 *
 *      //拍摄任务数量的快照，以防在此期间发生更改
 *      //函数正在执行。
 *      uxArraySize=uxTaskGetNumberOfTasks（）；
 *
 *      //为每个任务分配一个TaskStatus_t结构。数组可以是
 *      //在编译时静态分配。
 *      pxTaskStatusArray=pvPortMalloc（uxArraySize*sizeof（TaskStatus_t））；
 *
 *      如果（pxTaskStatusArray！=NULL）
 *      {
 *          //生成每个任务的原始状态信息。
 *          uxArraySize=uxTaskGetSystemState（pxTaskStatusArray，uxArraySize，&ulTotalRunTime）；
 *
 *          //用于百分比计算。
 *          ulTotalRunTime/=100UL；
 *
 *          //避免被零除错误。
 *          如果（ulTotalRunTime>0）
 *          {
 *              //对于pxTaskStatusArray数组中的每个填充位置，
 *              //将原始数据格式化为人类可读的ASCII数据
 *              对于（x=0；x<uxArraySize；x++）
 *              {
 *                  //任务使用了总运行时间的多少百分比？
 *                  //这将始终向下舍入到最接近的整数。
 *                  //ulTotalRunTimeDiv100已经除以100。
 *                  ulStatsAsPercentage=pxTaskStatsArray[x]。ulRunTimeCounter/ulTotalRunTime；
 *
 *                  如果（ulStatsAsPercentage>0UL）
 *                  {
 *                      sprintf（pcWriteBuffer，“%s\t\t%lu\t\t%lu%%\r\n”，pxTaskStatusArray[x].pcTaskName，pxTask StatusArray[x].ulRunTimeCounter，ulStatsAsPercentage）；
 *                  }
 *                  其他的
 *                  {
 *                      //如果此处的百分比为零，则任务具有
 *                      //消耗少于总运行时间的1%。
 *                      sprintf（pcWriteBuffer，“%s\t\t%lu\t\t<1%%\r\n”，pxTaskStatusArray[x].pctTaskName，pxTask StatusArray[x].ulRunTimeCounter）；
 *                  }
 *
 *                  pcWriteBuffer+=strlen（（char*）pcWriteBuffer）；
 *              }
 *          }
 *
 *          //阵列不再需要，释放它所消耗的内存。
 *          vPortFree（pxTaskStatusArray）；
 *      }
 *  }
 *  @endcode
 */
UBaseType_t uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusArray,
                                  const UBaseType_t uxArraySize,
                                  uint32_t * const pulTotalRunTime ) PRIVILEGED_FUNCTION;

/**
 * 列出所有当前任务。
 *
 * configUSE_TRACE_FACILITY和configUSE_STATS_FORMATING_FUNCTIONS必须都定义为1才能使用此函数。请参阅FreeRTOS的配置部分。org网站获取更多信息。
 *
 * 注1：此功能将在其持续时间内禁用中断。它不是用于正常的应用程序运行时，而是作为调试辅助工具。
 *
 * 列出所有当前任务，以及它们的当前状态和堆栈使用率上限。
 *
 * 任务报告为已阻止（“B”）、已就绪（“R”）、删除（“D”）或已暂停（“S”）。
 *
 * PLEASE NOTE:
 *
 * 此功能仅为方便而提供，许多演示应用程序都使用此功能。不要将其视为计划程序的一部分。
 *
 * vTaskList（）调用uxTaskGetSystemState（），然后将uxTaskGetSystemState（（）输出的一部分格式化为可读的表，该表显示任务名称、状态和堆栈使用情况。
 *
 * vTaskList（）依赖于sprintf（）C库函数，这可能会导致代码大小膨胀，使用大量堆栈，并在不同的平台上提供不同的结果。在一个名为printf stdarg的文件中的许多FreeRTOS/Demo子目录中提供了sprintf（）的一种替代的、微小的、第三方的、功能有限的实现。c（注意printf stdarg.c没有提供完整的snprintf（）实现！）。
 *
 * 建议生产系统直接调用uxTaskGetSystemState（）来访问原始统计数据，而不是通过调用vTaskList（）来间接访问。
 *
 * @param pcWriteBuffer 一种缓冲区，上面提到的详细信息将以ASCII格式写入其中。假定该缓冲区足够大，足以容纳生成的报告。每个任务大约40个字节就足够了。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskList vTaskList
 * @endcond \内部组任务工具
 */
void vTaskList( char * pcWriteBuffer ) PRIVILEGED_FUNCTION;     /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/

/**
 * 以字符串形式获取正在运行的任务的状态
 *
 * configGENERATE_RUN_TIME_STATS和configUSE_STATS_FORMATING_FUNCTIONS必须都定义为1，此函数才能可用。然后，应用程序还必须为portCONFIGURE_TIMER_for_RUN_TIME_STATS（）和portGET_RUN_TIME_COUNTER_VALUE（）提供定义，以配置外围计时器/计数器并分别返回计时器当前计数值。计数器应至少为刻度计数频率的10倍。
 *
 * 注1：此功能将在其持续时间内禁用中断。它不是用于正常的应用程序运行时，而是作为调试辅助工具。
 *
 * 将configGENERATE_RUN_TIME_STATS设置为1将导致存储每个任务的总累计执行时间。累积时间值的分辨率取决于portCONFIGURE_timer_FOR_RUN_time_STATS（）宏配置的计时器的频率。调用vTaskGetRunTimeStats（）将每个任务的总执行时间作为绝对计数值和总系统执行时间的百分比写入缓冲区。
 *
 * NOTE 2:
 *
 * 此功能仅为方便而提供，许多演示应用程序都使用此功能。不要将其视为计划程序的一部分。
 *
 * vTaskGetRunTimeStats（）调用uxTaskGetSystemState（），然后将uxTaskGetSystemState（（）输出的一部分格式化为可读表，该表以绝对值和百分比形式显示每个任务在运行状态下花费的时间。
 *
 * vTaskGetRunTimeStats（）依赖于sprintf（）C库函数，这可能会导致代码大小膨胀，使用大量堆栈，并在不同的平台上提供不同的结果。在一个名为printf stdarg的文件中的许多FreeRTOS/Demo子目录中提供了sprintf（）的一种替代的、微小的、第三方的、功能有限的实现。c（注意printf stdarg.c没有提供完整的snprintf（）实现！）。
 *
 * 建议生产系统直接调用uxTaskGetSystemState（）来访问原始统计数据，而不是通过调用vTaskGetRunTimeStats（）来间接访问。
 *
 * @param pcWriteBuffer 以ASCII格式将执行时间写入其中的缓冲区。假定该缓冲区足够大，足以容纳生成的报告。每个任务大约40个字节就足够了。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskGetRunTimeStats vTaskGetRunTimeStats
 * @endcond \内部组任务工具
 */
void vTaskGetRunTimeStats( char * pcWriteBuffer ) PRIVILEGED_FUNCTION;     /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code
 * uint32_t ulTaskGetIdleRunTimeCounter（无效）；
 * @endcode
 * @endcond
 *
 * configGENERATE_RUN_TIME_STATS和configUSE_STATS_FORMATING_FUNCTIONS必须都定义为1，此函数才能可用。然后，应用程序还必须为portCONFIGURE_TIMER_for_RUN_TIME_STATS（）和portGET_RUN_TIME_COUNTER_VALUE（）提供定义，以配置外围计时器/计数器并分别返回计时器当前计数值。计数器应至少为刻度计数频率的10倍。
 *
 * 将configGENERATE_RUN_TIME_STATS设置为1将导致存储每个任务的总累计执行时间。累积时间值的分辨率取决于portCONFIGURE_timer_FOR_RUN_time_STATS（）宏配置的计时器的频率。当uxTaskGetSystemState（）和vTaskGetRunTimeStats（）将每个任务的总执行时间写入缓冲区时，ulTaskGetIdleRunTimeCounter（）仅返回空闲任务的总运行时间。
 *
 * @return 空闲任务的总运行时间。这是空闲任务实际执行的时间。时间单位取决于使用portCONFIGURE_TIMER_FOR_RUN_time_STATS（）和portGET_RUN_time_COUNTER_VALUE（）宏配置的频率。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup ulTaskGetIdleRunTimeCounter ulTaskGetidleRunTimeCount
 * @endcond \内部组任务工具
 */
uint32_t ulTaskGetIdleRunTimeCounter( void ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyIndexed（TaskHandle_t xTask ToNotify，UBaseType_t uxIndexToNotify、uint32_t ulValue、eNotifyAction eAction）；
 * BaseType_t xTaskNotify（TaskHandle_t xTask ToNotify，uint32_tulValue，eNotifyAction eAction）；
 * @endcode
 * @endcond
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1，这些函数才能可用。
 *
 * 向任务发送直接到任务通知，其中包含可选值和操作。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 可以使用中间对象将事件发送到任务。此类对象的示例包括队列、信号量、互斥体和事件组。任务通知是一种将事件直接发送到任务的方法，不需要这样的中间对象。
 *
 * 发送给任务的通知可以选择执行操作，例如更新、覆盖或增加任务的通知值之一。通过这种方式，任务通知可以用于向任务发送数据，或者用作轻量级快速二进制或计数信号量。
 *
 * 任务可以使用xTaskNotifyWaitIndexed（）[可选]块等待通知挂起，或使用ulTaskNotifyTakeIndexed）[可选）块等待通知值为非零值。任务处于“阻止”状态时不会占用任何CPU时间。
 *
 * 发送到任务的通知将保持挂起状态，直到该通知被调用xTaskNotifyWaitIndexed（）或ulTaskNotifyTakeIndexed）（或其未编入索引的等效任务）的任务清除。如果任务已处于阻止状态以等待通知到达时的通知，则该任务将自动从阻止状态中删除（未阻止），并清除通知。
 *
 * **注意**阵列中的每个通知都独立运行-一次任务只能阻止阵列中的一个通知，并且不会被发送到任何其他阵列索引的通知阻止。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。xTaskNotify（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用xTaskNotify（）等同于在uxIndexToNotify参数设置为0的情况下调用xTaskNotifyIndexed（）。
 *
 * @param xTaskToNotify 正在通知的任务的句柄。任务的句柄可以从用于创建任务的xTaskCreate（）API函数返回，当前运行任务的句柄可通过调用xTaskGetCurrentTaskHandle（）获得。
 *
 * @param uxIndexToNotify 要向其发送通知的目标任务的通知值数组中的索引。uxIndexToNotify必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。xTaskNotify（）没有此参数，始终向索引0发送通知。
 *
 * @param ulValue 可以随通知一起发送的数据。数据的使用方式取决于eAction参数的值。
 *
 * @param eAction 指定通知如何更新任务的通知值（如果有）。eAction的有效值如下：
 *
 * eSetBits-目标通知值与ulValue按位“或”运算。在这种情况下，xTaskNotifyIndexed（）始终返回pdPASS。
 *
 * eIncrement-目标通知值递增。在这种情况下，不使用ulValue，xTaskNotifyIndexed（）始终返回pdPASS。
 *
 * eSetValueWithOverwrite-目标通知值设置为ulValue的值，即使被通知的任务尚未在同一数组索引中处理上一个通知（该任务已在该索引中挂起通知）。在这种情况下，xTaskNotifyIndexed（）始终返回pdPASS。
 *
 * eSetValueWithoutOverwrite-如果被通知的任务在同一数组索引中没有挂起的通知，则目标通知值设置为ulValue，xTaskNotifyIndexed（）将返回pdPASS。如果被通知的任务在同一个数组索引中已经有一个挂起的通知，则不执行任何操作，并返回pdFAIL。
 *
 * eNoAction-任务在指定的数组索引处接收通知，而不更新该索引处的通知值。在这种情况下，不使用ulValue，xTaskNotifyIndexed（）始终返回pdPASS。
 *
 * pulPreviousNotificationValue-可用于在通知函数修改任何位之前传递主题任务的通知值。
 *
 * @return 取决于eAction的值。请参阅eAction参数的说明。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyIndexed xTaskNotify Indexed
 * @endcond \内部组任务通知
 */
BaseType_t xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                               UBaseType_t uxIndexToNotify,
                               uint32_t ulValue,
                               eNotifyAction eAction,
                               uint32_t * pulPreviousNotificationValue ) PRIVILEGED_FUNCTION;
#define xTaskNotify( xTaskToNotify, ulValue, eAction ) \
    xTaskGenericNotify( ( xTaskToNotify ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( ulValue ), ( eAction ), NULL )
#define xTaskNotifyIndexed( xTaskToNotify, uxIndexToNotify, ulValue, eAction ) \
    xTaskGenericNotify( ( xTaskToNotify ), ( uxIndexToNotify ), ( ulValue ), ( eAction ), NULL )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyAndQueryIndexed（TaskHandle_t xTask ToNotify，UBaseType_t uxIndexToNotify、uint32_tulValue、eNotifyAction eAction、uint22_t*pulPreviousNotifyValue）；
 * BaseType_t xTaskNotifyAndQuery（TaskHandle_t xTask ToNotify，uint32_tulValue，eNotifyAction eAction，uint22_t*pulPreviousNotifyValue）；
 * @endcode
 * @endcond
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * xTaskNotifyAndQueryIndexed（）执行与xTaskNotifyIndexed）相同的操作，但它也在附加的pulPreviousNotifyValue参数中返回主题任务的先前通知值（调用函数时的通知值，而不是函数返回时的通知）。
 *
 * xTaskNotifyAndQuery（）执行与xTaskNotify（）相同的操作，但它也在附加的pulPreviousNotifyValue参数中返回主题任务的先前通知值（调用函数时的通知值，而不是函数返回时的通知）。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyAndQueryIndexed xTaskNotIFyAndQueryIndex
 * @endcond \内部组任务通知
 */
#define xTaskNotifyAndQuery( xTaskToNotify, ulValue, eAction, pulPreviousNotifyValue ) \
    xTaskGenericNotify( ( xTaskToNotify ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( ulValue ), ( eAction ), ( pulPreviousNotifyValue ) )
#define xTaskNotifyAndQueryIndexed( xTaskToNotify, uxIndexToNotify, ulValue, eAction, pulPreviousNotifyValue ) \
    xTaskGenericNotify( ( xTaskToNotify ), ( uxIndexToNotify ), ( ulValue ), ( eAction ), ( pulPreviousNotifyValue ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyIndexedFromISR（TaskHandle_t xTask ToNotify，UBaseType_t uxIndexToNotify、uint32_tulValue、eNotifyAction eAction、BaseType_t*pxHigherPriorityTaskWoken）；
 * BaseType_t xTaskNotifyFromISR（TaskHandle_t xTask ToNotify，uint32_tulValue，eNotifyAction eAction，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1，这些函数才能可用。
 *
 * xTaskNotifyIndexed（）的一个版本，可以从中断服务例程（ISR）中使用。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 可以使用中间对象将事件发送到任务。此类对象的示例包括队列、信号量、互斥体和事件组。任务通知是一种将事件直接发送到任务的方法，不需要这样的中间对象。
 *
 * 发送给任务的通知可以选择执行操作，例如更新、覆盖或增加任务的通知值之一。通过这种方式，任务通知可以用于向任务发送数据，或者用作轻量级快速二进制或计数信号量。
 *
 * 任务可以使用xTaskNotifyWaitIndexed（）[可选]块等待通知挂起，或使用ulTaskNotifyTakeIndexed）[可选）块等待通知值为非零值。任务处于“阻止”状态时不会占用任何CPU时间。
 *
 * 发送到任务的通知将保持挂起状态，直到该通知被调用xTaskNotifyWaitIndexed（）或ulTaskNotifyTakeIndexed）（或其未编入索引的等效任务）的任务清除。如果任务已处于阻止状态以等待通知到达时的通知，则该任务将自动从阻止状态中删除（未阻止），并清除通知。
 *
 * **注意**阵列中的每个通知都独立运行-一次任务只能阻止阵列中的一个通知，并且不会被发送到任何其他阵列索引的通知阻止。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。xTaskNotifyFromISR（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用xTaskNotifyFromISR（）等同于在uxIndexToNotify参数设置为0的情况下调用xTaskNotifyIndexedFromISR。
 *
 * @param uxIndexToNotify 要向其发送通知的目标任务的通知值数组中的索引。uxIndexToNotify必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。xTaskNotifyFromISR（）没有此参数，始终向索引0发送通知。
 *
 * @param xTaskToNotify 正在通知的任务的句柄。任务的句柄可以从用于创建任务的xTaskCreate（）API函数返回，当前运行任务的句柄可通过调用xTaskGetCurrentTaskHandle（）获得。
 *
 * @param ulValue 可以随通知一起发送的数据。数据的使用方式取决于eAction参数的值。
 *
 * @param eAction 指定通知如何更新任务的通知值（如果有）。eAction的有效值如下：
 *
 * eSetBits-任务的通知值与ulValue按位“或”运算。在这种情况下，xTaskNotify（）始终返回pdPASS。
 *
 * eIncrement-任务的通知值递增。在这种情况下，不使用ulValue，xTaskNotify（）始终返回pdPASS。
 *
 * eSetValueWithOverwrite-任务的通知值设置为ulValue的值，即使被通知的任务尚未处理上一个通知（该任务已经有一个通知挂起）。在这种情况下，xTaskNotify（）始终返回pdPASS。
 *
 * eSetValueWithoutOverwrite-如果被通知的任务还没有挂起的通知，则任务的通知值设置为ulValue，xTaskNotify（）将返回pdPASS。如果被通知的任务已经有一个通知挂起，则不执行任何操作，并返回pdFAIL。
 *
 * eNoAction-任务接收通知而不更新其通知值。在这种情况下，不使用ulValue，xTaskNotify（）始终返回pdPASS。
 *
 * @param pxHigherPriorityTaskWoken  如果发送通知导致发送通知的任务离开“阻止”状态，并且未阻止的任务的优先级高于当前正在运行的任务，则xTaskNotifyFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE。如果xTaskNotifyFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。如何从ISR请求上下文切换取决于端口-请参阅所用端口的文档页。
 *
 * @return 取决于eAction的值。请参阅eAction参数的说明。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyIndexedFromISR xTaskNotIFyIndexed FromISR
 * @endcond \内部组任务通知
 */
BaseType_t xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                      UBaseType_t uxIndexToNotify,
                                      uint32_t ulValue,
                                      eNotifyAction eAction,
                                      uint32_t * pulPreviousNotificationValue,
                                      BaseType_t * pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;
#define xTaskNotifyFromISR( xTaskToNotify, ulValue, eAction, pxHigherPriorityTaskWoken ) \
    xTaskGenericNotifyFromISR( ( xTaskToNotify ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( ulValue ), ( eAction ), NULL, ( pxHigherPriorityTaskWoken ) )
#define xTaskNotifyIndexedFromISR( xTaskToNotify, uxIndexToNotify, ulValue, eAction, pxHigherPriorityTaskWoken ) \
    xTaskGenericNotifyFromISR( ( xTaskToNotify ), ( uxIndexToNotify ), ( ulValue ), ( eAction ), NULL, ( pxHigherPriorityTaskWoken ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyAndQueryIndexedFromISR（TaskHandle_t xTask ToNotify，UBaseType_t uxIndexToNotify、uint32_tulValue、eNotifyAction eAction、uint22_t*pulPreviousNotificationValue、BaseType_t*pxHigherPriorityTaskWoken）；
 * BaseType_t xTaskNotifyAndQueryFromISR（TaskHandle_t xTask ToNotify，uint32_tulValue，eNotifyAction eAction，uint22_t*pulPreviousNotificationValue，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * xTaskNotifyAndQueryIndexedFromISR（）执行与xTaskNotify IndexedfromISR（（）相同的操作，但它还返回附加pulPreviousNotifyValue参数中主题任务的先前通知值（调用函数时的通知值，而不是函数返回时的通知）。
 *
 * xTaskNotifyAndQueryFromISR（）执行与xTaskNotify FromISR）相同的操作，除了它还返回附加pulPreviousNotifyValue参数中主题任务的先前通知值（调用函数时的通知值，而不是函数返回时的通知）。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyAndQueryIndexedFromISR xTaskNotify AndQueryIndexed FromISR
 * @endcond \内部组任务通知
 */
#define xTaskNotifyAndQueryIndexedFromISR( xTaskToNotify, uxIndexToNotify, ulValue, eAction, pulPreviousNotificationValue, pxHigherPriorityTaskWoken ) \
    xTaskGenericNotifyFromISR( ( xTaskToNotify ), ( uxIndexToNotify ), ( ulValue ), ( eAction ), ( pulPreviousNotificationValue ), ( pxHigherPriorityTaskWoken ) )
#define xTaskNotifyAndQueryFromISR( xTaskToNotify, ulValue, eAction, pulPreviousNotificationValue, pxHigherPriorityTaskWoken ) \
    xTaskGenericNotifyFromISR( ( xTaskToNotify ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( ulValue ), ( eAction ), ( pulPreviousNotificationValue ), ( pxHigherPriorityTaskWoken ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyWaitIndexed（UBaseType_t uxIndexToWaitOn，uint32_t ulBitsToClearOnEntry，uint22_t ulBitsToClearOnExit，uint33_t*pulNotificationValue，TickType_t x TicksToWait）；
 *
 * BaseType_t xTaskNotifyWait（uint32_t ulBitsToClearOnEntry，uint32:t ulBitsToClearOnExit，uint22_t*pulNotificationValue，TickType_t x TicksToWait）；
 * @endcode
 * @endcond
 *
 * 等待直接任务通知在直接任务通知数组中的给定索引处挂起。
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1才能使用此函数。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 可以使用中间对象将事件发送到任务。此类对象的示例包括队列、信号量、互斥体和事件组。任务通知是一种将事件直接发送到任务的方法，不需要这样的中间对象。
 *
 * 发送给任务的通知可以选择执行操作，例如更新、覆盖或增加任务的通知值之一。通过这种方式，任务通知可以用于向任务发送数据，或者用作轻量级快速二进制或计数信号量。
 *
 * 发送到任务的通知将保持挂起状态，直到该通知被调用xTaskNotifyWaitIndexed（）或ulTaskNotifyTakeIndexed）（或其未编入索引的等效任务）的任务清除。如果任务已处于阻止状态以等待通知到达时的通知，则该任务将自动从阻止状态中删除（未阻止），并清除通知。
 *
 * 任务可以使用xTaskNotifyWaitIndexed（）[可选]块等待通知挂起，或使用ulTaskNotifyTakeIndexed）[可选）块等待通知值为非零值。任务处于“阻止”状态时不会占用任何CPU时间。
 *
 * **注意**阵列中的每个通知都独立运行-一次任务只能阻止阵列中的一个通知，并且不会被发送到任何其他阵列索引的通知阻止。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。xTaskNotifyWait（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用xTaskNotifyWait（）等同于在uxIndexToWaitOn参数设置为0的情况下调用xTaskNotifyWaitIndexed（）。
 *
 * @param uxIndexToWaitOn 调用任务的通知值数组中的索引，调用任务将在该数组上等待接收通知。uxIndexToWaitOn必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。xTaskNotifyWait（）没有此参数，始终等待索引0上的通知。
 *
 * @param ulBitsToClearOnEntry 在ulBitsToClearOnEntry值中设置的位将在任务检查是否有任何通知挂起之前在调用任务的通知值中清除，如果没有通知挂起，则可选地阻止。将ulBitsToClearOnEntry设置为ULONG_MAX（如果包含limits.h）或0xffffffUL（如果不包含limits.h）将具有将任务通知值重置为0的效果。将ulBittToClearOn Entry设置为0将使任务通知值保持不变。
 *
 * @param ulBitsToClearOnExit 如果在调用任务退出xTaskNotifyWait（）函数之前挂起或接收到通知，则使用pulNotificationValue参数传递任务的通知值（请参见xTaskNotify（）API函数）。然后，ulBitsToClearOnExit中设置的任何位都将在任务的通知值中清除（注意，在清除任何位之前设置pulNotificationValue）。将ulBitsToClearOnExit设置为ULONG_MAX（如果包含limits.h）或0xffffffUL（如果不包含limits.h）将在函数退出之前将任务的通知值重置为0。当函数退出时，将ulBitsToClearOnExit设置为0将使任务的通知值保持不变（在这种情况下，pulNotificationValue中传递的值将与任务通知值匹配）。
 *
 * @param pulNotificationValue 用于将任务的通知值传递给函数。请注意，由于ulBitsToClearOnExit为非零而导致的任何位的清除不会影响传递的值。
 *
 * @param xTicksToWait 如果在调用xTaskNotifyWait（）时通知尚未挂起，则任务应在阻止状态下等待接收通知的最长时间。任务处于“阻止”状态时不会占用任何处理时间。这是在内核时钟中指定的，宏pdMS_TO_ticks（value_in_ms）可用于将以毫秒为单位指定的时间转换为以时钟为单位指定时间。
 *
 * @return 如果收到通知（包括调用xTaskNotifyWait时已挂起的通知），则返回pdPASS。否则将返回pdFAIL。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyWaitIndexed xTaskNotIFyWaitIndex
 * @endcond \内部组任务通知
 */
BaseType_t xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                   uint32_t ulBitsToClearOnEntry,
                                   uint32_t ulBitsToClearOnExit,
                                   uint32_t * pulNotificationValue,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;
#define xTaskNotifyWait( ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait ) \
    xTaskGenericNotifyWait( tskDEFAULT_INDEX_TO_NOTIFY, ( ulBitsToClearOnEntry ), ( ulBitsToClearOnExit ), ( pulNotificationValue ), ( xTicksToWait ) )
#define xTaskNotifyWaitIndexed( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait ) \
    xTaskGenericNotifyWait( ( uxIndexToWaitOn ), ( ulBitsToClearOnEntry ), ( ulBitsToClearOnExit ), ( pulNotificationValue ), ( xTicksToWait ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyGiveIndexed（TaskHandle_t xTask ToNotify，UBaseType_t uxIndexToNotify）；
 * BaseType_t xTaskNotifyGive（TaskHandle_t xTask ToNotify）；
 * @endcode
 * @endcond
 *
 * 以类似于给出计数信号的方式，向目标任务通知数组中的特定索引发送直接到任务通知。
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html了解更多详情。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1，这些宏才能可用。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 可以使用中间对象将事件发送到任务。此类对象的示例包括队列、信号量、互斥体和事件组。任务通知是一种将事件直接发送到任务的方法，不需要这样的中间对象。
 *
 * 发送给任务的通知可以选择执行操作，例如更新、覆盖或增加任务的通知值之一。通过这种方式，任务通知可以用于向任务发送数据，或者用作轻量级快速二进制或计数信号量。
 *
 * xTaskNotifyGiveIndexed（）是一个助手宏，用于在任务通知用作轻量级和更快的二进制或计数信号量等价物时使用。实际的FreeRTOS信号量是使用xSemaphoreGive（）API函数给出的，而使用任务通知的等效操作是xTaskNotifyGiveIndexed（）。
 *
 * 当任务通知用作二进制或计数信号量等效时，被通知的任务应使用ulTaskNotificationTakeIndexed（）API函数而不是xTaskNotifyWaitIndexed（API函数等待通知。
 *
 * **注意**阵列中的每个通知都独立运行-一次任务只能阻止阵列中的一个通知，并且不会被发送到任何其他阵列索引的通知阻止。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。xTaskNotifyGive（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用xTaskNotifyGive（）等同于在uxIndexToNotify参数设置为0的情况下调用xTaskNotifyGiveIndexed（）。
 *
 * @param xTaskToNotify 正在通知的任务的句柄。任务的句柄可以从用于创建任务的xTaskCreate（）API函数返回，当前运行任务的句柄可通过调用xTaskGetCurrentTaskHandle（）获得。
 *
 * @param uxIndexToNotify 要向其发送通知的目标任务的通知值数组中的索引。uxIndexToNotify必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。xTaskNotifyGive（）没有此参数，始终向索引0发送通知。
 *
 * @return xTaskNotifyGive（）是一个调用xTaskNotify（）的宏，eAction参数设置为eIncrement，因此始终返回pdPASS。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyGiveIndexed xTaskNotify GiveIndexed
 * @endcond \内部组任务通知
 */
#define xTaskNotifyGive( xTaskToNotify ) \
    xTaskGenericNotify( ( xTaskToNotify ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( 0 ), eIncrement, NULL )
#define xTaskNotifyGiveIndexed( xTaskToNotify, uxIndexToNotify ) \
    xTaskGenericNotify( ( xTaskToNotify ), ( uxIndexToNotify ), ( 0 ), eIncrement, NULL )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * void vTaskNotifyGiveIndexedFromISR（TaskHandle_t xTaskHandle，UBaseType_t uxIndexToNotify，BaseType_t*pxHigherPriorityTaskWoken）；
 * void vTaskNotifyGiveFromISR（TaskHandle_t xTaskHandle，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 可以从中断服务例程（ISR）调用的xTaskNotifyGiveIndexed（）版本。
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html了解更多详情。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1才能使用此宏。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 可以使用中间对象将事件发送到任务。此类对象的示例包括队列、信号量、互斥体和事件组。任务通知是一种将事件直接发送到任务的方法，不需要这样的中间对象。
 *
 * 发送给任务的通知可以选择执行操作，例如更新、覆盖或增加任务的通知值之一。通过这种方式，任务通知可以用于向任务发送数据，或者用作轻量级快速二进制或计数信号量。
 *
 * vTaskNotifyGiveIndexedFromISR（）用于当任务通知用作轻量级和更快的二进制或计数信号量等价物时使用。实际的FreeRTOS信号量是使用xSemaphoreGiveFromISR（）API函数从ISR提供的，而使用任务通知的等效操作是vTaskNotifyGiveIndexedFromISR）。
 *
 * 当任务通知用作二进制或计数信号量等效时，被通知的任务应使用ulTaskNotificationTakeIndexed（）API函数而不是xTaskNotifyWaitIndexed（API函数等待通知。
 *
 * **注意**阵列中的每个通知都独立运行-一次任务只能阻止阵列中的一个通知，并且不会被发送到任何其他阵列索引的通知阻止。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。xTaskNotifyFromISR（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用xTaskNotifyGiveFromISR（）等同于在uxIndexToNotify参数设置为0的情况下调用xTasknotifyGive IndexedFromISR。
 *
 * @param xTaskToNotify 正在通知的任务的句柄。任务的句柄可以从用于创建任务的xTaskCreate（）API函数返回，当前运行任务的句柄可通过调用xTaskGetCurrentTaskHandle（）获得。
 *
 * @param uxIndexToNotify 要向其发送通知的目标任务的通知值数组中的索引。uxIndexToNotify必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。xTaskNotifyGiveFromISR（）没有此参数，始终向索引0发送通知。
 *
 * @param pxHigherPriorityTaskWoken  vTaskNotifyGiveFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE，如果发送通知导致向其发送通知的任务离开“阻止”状态，并且未阻止的任务的优先级高于当前正在运行的任务。如果vTaskNotifyGiveFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。如何从ISR请求上下文切换取决于端口-请参阅所用端口的文档页。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vTaskNotifyGiveIndexedFromISR vTaskNotify GiveIndexFromISR
 * @endcond \内部组任务通知
 */
void vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                    UBaseType_t uxIndexToNotify,
                                    BaseType_t * pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;
#define vTaskNotifyGiveFromISR( xTaskToNotify, pxHigherPriorityTaskWoken ) \
    vTaskGenericNotifyGiveFromISR( ( xTaskToNotify ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( pxHigherPriorityTaskWoken ) );
#define vTaskNotifyGiveIndexedFromISR( xTaskToNotify, uxIndexToNotify, pxHigherPriorityTaskWoken ) \
    vTaskGenericNotifyGiveFromISR( ( xTaskToNotify ), ( uxIndexToNotify ), ( pxHigherPriorityTaskWoken ) );

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * uint32_t ulTaskNotifyTakeIndexed（UBaseType_t uxIndexToWaitOn，BaseType_t xClearCountOnExit，TickType_t xTicksToWait）；
 *
 * uint32_t ulTaskNotifyTake（BaseType_t xClearCountOnExit，TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 在调用任务的通知数组中的特定索引上等待直接到任务的通知，其方式类似于获取计数信号量。
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1才能使用此函数。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 可以使用中间对象将事件发送到任务。此类对象的示例包括队列、信号量、互斥体和事件组。任务通知是一种将事件直接发送到任务的方法，不需要这样的中间对象。
 *
 * 发送给任务的通知可以选择执行操作，例如更新、覆盖或增加任务的通知值之一。通过这种方式，任务通知可以用于向任务发送数据，或者用作轻量级快速二进制或计数信号量。
 *
 * ulTaskNotifyTakeIndexed（）用于当任务通知用作更快、更轻的二进制或计数信号量替代时使用。实际的FreeRTOS信号量是使用xSemaphoreTake（）API函数获取的，而使用任务通知的等效操作是ulTaskNotifyTakeIndexed（）。
 *
 * 当任务使用其通知值作为二进制或计数信号量时，其他任务应使用xTaskNotifyGiveIndexed（）宏或xTaskNotifyIndex（）函数向其发送通知，eAction参数设置为eIncrement。
 *
 * ulTaskNotifyTakeIndexed（）可以在退出时将uxIndexToWaitOn参数指定的数组索引处的任务通知值清除为零，在这种情况下，通知值的作用类似于二进制信号量，或者在退出时减少通知值，在这种情况下，通知的作用类似计数信号量。
 *
 * 任务可以使用ulTaskNotifyTakeIndexed（）[可选]块来等待任务的通知值为非零。任务处于“阻止”状态时不会占用任何CPU时间。
 *
 * 其中，当通知挂起时，xTaskNotifyWaitIndexed（）将返回，而当任务的通知值不为零时，ulTaskNotifyTakeIndexed）将返回。
 *
 * **注意**阵列中的每个通知都独立运行-一次任务只能阻止阵列中的一个通知，并且不会被发送到任何其他阵列索引的通知阻止。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。ulTaskNotifyTake（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用ulTaskNotifyTake（）等同于在uxIndexToWaitOn参数设置为0的情况下调用ulTaskNotifyTakeIndexed（）。
 *
 * @param uxIndexToWaitOn 调用任务的通知值数组中的索引，调用任务将在该数组上等待通知为非零。uxIndexToWaitOn必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。xTaskNotifyTake（）没有此参数，始终等待索引0上的通知。
 *
 * @param xClearCountOnExit 如果xClearCountOnExit为pdFALSE，则当函数退出时，任务的通知值将递减。通过这种方式，通知值就像一个计数信号量。如果xClearCountOnExit不为pdFALSE，则当函数退出时，任务的通知值将清除为零。通过这种方式，通知值的作用类似于二进制信号量。
 *
 * @param xTicksToWait 如果在调用ulTaskNotifyTake（）时计数尚未大于零，则任务在“阻止”状态下等待任务通知值大于零的最长时间。任务处于“阻止”状态时不会占用任何处理时间。这是在内核时钟中指定的，宏pdMS_TO_ticks（value_in_ms）可用于将以毫秒为单位指定的时间转换为以时钟为单位指定时间。
 *
 * @return 任务清除为零或递减之前的通知计数（请参阅xClearCountOnExit参数）。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup ulTaskNotifyTakeIndexed ulTaskNotify Take Indexed
 * @endcond \内部组任务通知
 */
uint32_t ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                  BaseType_t xClearCountOnExit,
                                  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;
#define ulTaskNotifyTake( xClearCountOnExit, xTicksToWait ) \
    ulTaskGenericNotifyTake( ( tskDEFAULT_INDEX_TO_NOTIFY ), ( xClearCountOnExit ), ( xTicksToWait ) )
#define ulTaskNotifyTakeIndexed( uxIndexToWaitOn, xClearCountOnExit, xTicksToWait ) \
    ulTaskGenericNotifyTake( ( uxIndexToWaitOn ), ( xClearCountOnExit ), ( xTicksToWait ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * BaseType_t xTaskNotifyStateClearIndexed（TaskHandle_t xTask，UBaseType_t uxIndexToCLear）；
 *
 * BaseType_t xTaskNotifyStateClear（TaskHandle_t xTask）；
 * @endcode
 * @endcond
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1，这些函数才能可用。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * 如果通知被发送到通知数组中的索引，则该索引处的通知被称为“挂起”，直到接收任务读取或明确清除该通知。xTaskNotifyStateClearIndexed（）是在不读取通知值的情况下清除挂起通知的函数。相同数组索引处的通知值不会更改。将xTask设置为NULL以清除调用任务的通知状态。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。xTaskNotifyStateClear（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用xTaskNotifyStateClear（）等同于在uxIndexToNotify参数设置为0的情况下调用xTaskNotifyStateClearIndexed（）。
 *
 * @param xTask 将清除通知状态的RTOS任务的句柄。将xTask设置为NULL以清除调用任务中的通知状态。要获得任务的句柄，请使用xTaskCreate（）创建任务并使用pxCreatedTask参数，或者使用xTaskCreateStatic（）创建该任务并存储返回的值，或者在调用xTaskGetHandle（）时使用该任务的名称。
 *
 * @param uxIndexToClear 目标任务的通知值数组中要执行操作的索引。例如，将uxIndexToClear设置为1将清除数组中索引1处的通知状态。uxIndexToClear必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。ulTaskNotifyStateClear（）没有此参数，并且始终作用于索引0处的通知。
 *
 * @return 如果任务的通知状态设置为eNotWaitingNotification，则为pdTRUE，否则为pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskNotifyStateClearIndexed xTaskNotIFyStateClearIndex
 * @endcond \内部组任务通知
 */
BaseType_t xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                         UBaseType_t uxIndexToClear ) PRIVILEGED_FUNCTION;
#define xTaskNotifyStateClear( xTask ) \
    xTaskGenericNotifyStateClear( ( xTask ), ( tskDEFAULT_INDEX_TO_NOTIFY ) )
#define xTaskNotifyStateClearIndexed( xTask, uxIndexToClear ) \
    xTaskGenericNotifyStateClear( ( xTask ), ( uxIndexToClear ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务。小时
 * @code{c}
 * uint32_t ulTaskNotifyValueClearIndexed（TaskHandle_t xTask，UBaseType_t uxIndexToClear，uint32:t ulBitsToClear）；
 *
 * uint32_t ulTaskNotifyValueClear（TaskHandle_t xTask，uint32:t ulBitsToClear）；
 * @endcode
 * @endcond
 *
 * 看见https://www.FreeRTOS.org/RTOS-task-notifications.html详细信息。
 *
 * configUSE_TASK_NOTIFICATIONS必须未定义或定义为1，这些函数才能可用。
 *
 * 每个任务都有一个“通知值”（或“通知”）的私有数组，每个值都是32位无符号整数（uint32_t）。常量configTASK_NOTIFICATION_ARRAY_ENTRIES设置数组中的索引数，如果未定义，则（为了向后兼容）默认为1。在FreeRTOS V10.4.0之前，每个任务只有一个通知值。
 *
 * ulTaskNotifyValueClearIndexed（）清除xTask引用的任务的数组索引uxIndexToClear处的通知值中ulBitsToClear位掩码指定的位。
 *
 * 向后兼容性信息：在FreeRTOS V10.4.0之前，每个任务都有一个“通知值”，所有任务通知API函数都基于该值运行。用通知值数组替换单个通知值需要一组新的API函数，这些函数可以处理数组中的特定通知。ulTaskNotifyValueClear（）是原始的API函数，通过始终对数组中索引0处的通知值进行操作，它保持向后兼容。调用ulTaskNotifyValueClear（）等同于在uxIndexToClear参数设置为0的情况下调用ulTaskNotifyValueClearIndexed（）。
 *
 * @param xTask RTOS任务的句柄，将清除其中一个通知值中的位。将xTask设置为NULL以清除调用任务的通知值中的位。要获得任务的句柄，请使用xTaskCreate（）创建任务并使用pxCreatedTask参数，或者使用xTaskCreateStatic（）创建该任务并存储返回的值，或者在调用xTaskGetHandle（）时使用该任务的名称。
 *
 * @param uxIndexToClear 目标任务的通知值数组中用于清除位的索引。uxIndexToClear必须小于configTASK_NOTIFICATION_ARRAY_ENTRIES。ulTaskNotifyValueClear（）没有此参数，总是清除索引0处通知值中的位。
 *
 * @param ulBitsToClear xTask通知值中要清除的位的位掩码。将位设置为1以清除任务通知值中的相应位。将ulBitsToClear设置为0xffffffff（32位体系结构上的UINT_MAX）以将通知值清除为0。将ulBitsToClear设置为0以查询任务的通知值而不清除任何位。
 *
 *
 * @return 清除ulBitsToClear指定的位之前目标任务通知值的值。
 * @cond !DOC_SINGLE_GROUP\defgroup ulTaskNotifyValueClear ulTaskNotify ValueClear
 * @endcond \内部组任务通知
 */
uint32_t ulTaskGenericNotifyValueClear( TaskHandle_t xTask,
                                        UBaseType_t uxIndexToClear,
                                        uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;
#define ulTaskNotifyValueClear( xTask, ulBitsToClear ) \
    ulTaskGenericNotifyValueClear( ( xTask ), ( tskDEFAULT_INDEX_TO_NOTIFY ), ( ulBitsToClear ) )
#define ulTaskNotifyValueClearIndexed( xTask, uxIndexToClear, ulBitsToClear ) \
    ulTaskGenericNotifyValueClear( ( xTask ), ( uxIndexToClear ), ( ulBitsToClear ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code{c}
 * void vTaskSetTimeOutState（TimeOut_t*常量pxTimeOut）；
 * @endcode
 * @endcond
 *
 * 使用xTaskCheckForTimeOut（）捕获当前时间以供将来使用。
 *
 * @param pxTimeOut 指向要捕获当前时间的超时对象的指针。捕获的时间包括刻度计数和自系统首次启动以来刻度计数溢出的次数。\defgroup vTaskSetTimeOutState vTaskSetTimeOutState
 * @cond !DOC_SINGLE_GROUP\组任务Ctrl
 * @endcond
 */
void vTaskSetTimeOutState( TimeOut_t * const pxTimeOut ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code
 * BaseType_t xTaskCheckForTimeOut（TimeOut_t*常量pxTimeOut，TickType_t*常量p xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 确定自调用vTaskSetTimeOutState（）捕获时间以来，pxTicksToWait标记是否已过去。捕获的时间包括刻度计数和刻度计数溢出的次数。
 *
 * @param pxTimeOut 先前使用vTaskSetTimeOutState捕获的时间状态。如果超时尚未发生，将更新超时以反映当前时间状态。
 * @param pxTicksToWait 要检查超时的计时数，即，如果自上次更新pxTimeOut（通过vTaskSetTimeOutState（）或xTaskCheckForTimeOut（））以来，pxTicksToWait计时已过，则超时已发生。如果未发生超时，则更新pxTicksToWait以反映剩余的刻度数。
 *
 * @return 如果发生超时，则返回pdTRUE。否则，将返回pdFALSE，并更新pxTicksToWait以反映剩余刻度的数量。
 *
 * @see https://www.FreeRTOS.org/xTaskCheckForTimeOut.html
 *
 * 示例用法：
 * @code
 *  //用于从Rx缓冲区接收uxWantedBytes的驱动程序库函数
 *  //由UART中断填充。如果
 *  //Rx缓冲区，然后任务进入“阻止”状态，直到通知它
 *  //更多的数据被放入缓冲区。如果仍然不够
 *  //数据，然后任务重新进入“阻止”状态，xTaskCheckForTimeOut（）
 *  //用于重新计算块时间，以确保总时间
 *  //在阻止状态下花费的时间不超过MAX_TIME_TO_WAIT。这
 *  //直到缓冲区至少包含uxWantedBytes字节，
 *  //或在“阻止”状态下花费的总时间达到
 *  //MAX_TIME_TO_WAIT–此时任务读取多少字节
 *  //最多可使用uxWantedBytes。
 *
 *  size_t xUART_Receive（uint8_t*pucBuffer，size_t uxWantedBytes）
 *  {
 *  size_t uxReceived=0；
 *  TickType_t xTicksToWait=MAX_TIME_TO_WAIT；
 *  超时_t x超时；
 *
 *      //初始化xTimeOut。这将记录此函数的时间
 *      //已输入。
 *      vTaskSetTimeOutState（&xTimeOut）；
 *
 *      //循环，直到缓冲区包含所需的字节数，或
 *      //发生超时。
 *      而（UART_bytes_in_rx_buffer（pxUARTInstance）<uxWantedBytes）
 *      {
 *          //缓冲区没有包含足够的数据，因此此任务将
 *          //进入“阻止”状态。调整xTicksToWait以考虑
 *          //在此期间处于“阻止”状态的任何时间
 *          //功能，以确保
 *          //阻塞状态不超过MAX_TIME_TO_WAIT。
 *          如果（xTaskCheckForTimeOut（&xTimeOut，&xTicksToWait）！=pdFALSE）
 *          {
 *              //在所需字节数可用之前超时，
 *              //退出循环。
 *              打破
 *          }
 *
 *          //等待最多xTicksToWait个滴答声通知
 *          //接收中断已将更多数据放入缓冲区。
 *          ulTaskNotifyTake（pdTRUE，xTicksToWait）；
 *      }
 *
 *      //尝试将uxWantedBytes从接收缓冲区读取到pucBuffer。
 *      //实际读取的字节数（可能小于
 *      //uxWantedBytes）。
 *      uxReceived＝UART_read_from_receive_buffer（pxUARTInstance，
 *                                                  pucBuffer，
 *                                                  uxWantedBytes）；
 *
 *      返回uxReceived；
 *  }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xTaskCheckForTimeOut xTaskCheckForTimeOut
 * @endcond \内部组任务Ctrl
 */
BaseType_t xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut,
                                 TickType_t * const pxTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION任务.h
 * @code{c}
 * BaseType_t xTaskCatchUpTicks（TickType_t x TicksToCatchUp）；
 * @endcode
 * @endcond
 *
 * 在应用程序代码将中断保持禁用一段延长的时间后，此函数会更正滴答计数值，从而导致错过滴答中断。
 *
 * 此函数类似于vTaskStepTick（），但与vTaskStepTick（）不同，xTaskCatchUpTicks（）可能会将刻度计数向前移动超过一个时间，在该时间任务应该从阻止状态中移除。这意味着随着刻度计数的移动，任务可能必须从阻止状态中删除。
 *
 * @param xTicksToCatchUp 由于中断被禁用而错过的滴答中断数。它的值不是自动计算的，因此必须由应用程序编写器计算。
 *
 * @return 如果向前移动滴答计数导致任务离开阻止状态并执行上下文切换，则为pdTRUE。否则pdFALSE。
 *
 * \defgroup xTaskCatchUpTicksxTaskCatch UpTicks
 * @cond !DOC_SINGLE_GROUP\组任务Ctrl
 * @endcond
 */
BaseType_t xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) PRIVILEGED_FUNCTION;


/*-----------------------------------------------------------
 * SCHEDULER INTERNALS AVAILABLE FOR PORTING PURPOSES
 *----------------------------------------------------------*/
/**@秒！文档_排除_标题_节*/
/*
 * 返回在某个CPU上运行的任务的句柄。由于SMP处理的性质，无法保证该值在返回时仍然有效，并且只能用于调试目的。
 */
TaskHandle_t xTaskGetCurrentTaskHandleForCPU( BaseType_t cpuid );

/**
 * 获取给定CPU的空闲任务句柄。
 *
 * 只有在FreeRTOSConfig.h中将INCLUDE_xTaskGetIdleTaskHandle设置为1时，xTaskGetIdle TaskHandleForCPU（）才可用。
 *
 * @param cpuid 获取句柄的CPU
 *
 * @return 给定cpu的空闲任务句柄。在计划程序启动之前，调用xTaskGetIdleTaskHandleForCPU（）是无效的。
 */
TaskHandle_t xTaskGetIdleTaskHandleForCPU( UBaseType_t cpuid );

/*
 * 获取任务的当前核心相关性
 */
BaseType_t xTaskGetAffinity( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS ONLY INTENDED FOR USE WHEN IMPLEMENTING A PORT OF THE SCHEDULER AND IS AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * 从实时内核滴答声（抢先或协作）调用，这会增加滴答声计数，并检查是否有任何在有限时间内被阻止的任务需要从阻止列表中删除并放入就绪列表。如果返回了一个非零值，则需要上下文切换，因为：+一个任务已从阻止列表中删除，因为其超时已过期，或者+时间切片正在使用，并且有一个任务的优先级与当前正在运行的任务相同。
 */
BaseType_t xTaskIncrementTick( void ) PRIVILEGED_FUNCTION;

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED.
 *
 * 从就绪列表中删除调用任务，并将其放在等待特定事件的任务列表和延迟任务列表中。如果事件发生（并且没有更高优先级的任务在等待同一事件）或延迟期到期，则该任务将从两个列表中删除，并在就绪列表中替换。
 *
 * “无序”版本将事件列表项值替换为xItemValue值，并在列表末尾插入列表项。
 *
 * “已排序”版本使用现有事件列表项值（即所属任务的优先级）将列表项按任务优先级顺序插入事件列表。
 *
 * @param pxEventList 包含等待事件发生而被阻止的任务的列表。
 *
 * @param xItemValue 当事件列表未按任务优先级排序时，用于事件列表项的项值。
 *
 * @param xTicksToWait 任务应等待事件发生的最长时间。这在内核时钟中指定，常量portTICK_PERIOD_MS可用于将内核时钟转换为实时周期。
 */
void vTaskPlaceOnEventList( List_t * const pxEventList,
                            const TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;
void vTaskPlaceOnUnorderedEventList( List_t * pxEventList,
                                     const TickType_t xItemValue,
                                     const TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED.
 *
 * 此函数执行的函数与vTaskPlaceOnEventList（）几乎相同。不同之处在于，此函数不允许任务无限期地阻塞，而vTaskPlaceOnEventList（）允许。
 *
 */
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList,
                                      TickType_t xTicksToWait,
                                      const BaseType_t xWaitIndefinitely ) PRIVILEGED_FUNCTION;

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED.
 *
 * 从指定的事件列表和阻止的任务列表中删除任务，并将其放置在就绪队列中。
 *
 * 如果发生取消阻止任务的事件，或者块超时时间到期，将调用xTaskRemoveFromEventList（）/vTaskRemoveFromUnorderedEventList（。
 *
 * 当事件列表按任务优先级排序时，使用xTaskRemoveFromEventList（）。它将从事件列表的开头删除列表项，因为它将具有事件列表上所有任务中最高优先级的所属任务。vTaskRemoveFromUnorderedEventList（）在事件列表未排序且事件列表项包含所属任务优先级以外的内容时使用。在这种情况下，事件列表项值将更新为xItemValue参数中传递的值。
 *
 * @return 如果要删除的任务的优先级高于进行调用的任务，则为pdTRUE，否则为pdFALSE。
 */
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList ) PRIVILEGED_FUNCTION;
void vTaskRemoveFromUnorderedEventList( ListItem_t * pxEventListItem,
                                        const TickType_t xItemValue ) PRIVILEGED_FUNCTION;

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS ONLY INTENDED FOR USE WHEN IMPLEMENTING A PORT OF THE SCHEDULER AND IS AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * 将指向当前TCB的指针设置为准备运行的最高优先级任务的TCB。
 */
portDONT_DISCARD void vTaskSwitchContext( void ) PRIVILEGED_FUNCTION;

/*
 * THESE FUNCTIONS MUST NOT BE USED FROM APPLICATION CODE.  THEY ARE USED BY THE EVENT BITS MODULE.
 */
TickType_t uxTaskResetEventItemValue( void ) PRIVILEGED_FUNCTION;

/*
 * 返回调用任务的句柄。
 */
TaskHandle_t xTaskGetCurrentTaskHandle( void ) PRIVILEGED_FUNCTION;

/*
 * 队列实现用于防止不必要地调用taskYIELD（）的快捷方式；
 */
void vTaskMissedYield( void ) PRIVILEGED_FUNCTION;

/*
 * 将调度程序状态返回为taskSCHEDULER_RUNNING、taskSCHEDUR_NOT_STARTED或taskSCHEDDULER_SUSPENDED。
 */
BaseType_t xTaskGetSchedulerState( void ) PRIVILEGED_FUNCTION;

/*
 * 如果互斥持有者的优先级低于调用任务，则将互斥持有者的优先权提高到调用任务的优先权。
 */
BaseType_t xTaskPriorityInherit( TaskHandle_t const pxMutexHolder ) PRIVILEGED_FUNCTION;

/*
 * 如果任务在持有信号量时继承了更高的优先级，则将任务的优先级设置回其正确的优先级。
 */
BaseType_t xTaskPriorityDisinherit( TaskHandle_t const pxMutexHolder ) PRIVILEGED_FUNCTION;

/*
 * 如果试图获得互斥锁的较高优先级任务导致较低优先级任务继承较高优先级任务的优先级，但较高优先级任务随后超时而未获得互斥锁，那么较低优先级的任务将再次取消优先级继承权，但仅降低到仍在等待互斥锁的最高优先级任务（如果有多个任务等待互斥锁）。
 */
void vTaskPriorityDisinheritAfterTimeout( TaskHandle_t const pxMutexHolder,
                                          UBaseType_t uxHighestPriorityWaitingTask ) PRIVILEGED_FUNCTION;

/*
 * 获取分配给xTask参数引用的任务的uxTCBNumber。
 */
UBaseType_t uxTaskGetTaskNumber( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

/*
 * 将xTask参数引用的任务的uxTaskNumber设置为uxHandle。
 */
void vTaskSetTaskNumber( TaskHandle_t xTask,
                         const UBaseType_t uxHandle ) PRIVILEGED_FUNCTION;

/*
 * 仅当configUSE_TICKLESS_IDLE设置为1时才可用。如果正在使用挠痒痒模式，或者实现了低功耗模式，则在空闲期间不会执行滴答声中断。在这种情况下，调度器维护的滴答计数值需要通过向前跳过等于空闲时间的时间来保持与实际执行时间的最新。
 */
void vTaskStepTick( const TickType_t xTicksToJump ) PRIVILEGED_FUNCTION;

/*
 * 仅当configUSE_TICKLESS_IDLE设置为1时可用。提供用于portSUPPRESS_TICKS_AND_SLEEP（）中，以允许特定于端口的休眠函数确定是否可以继续休眠，是否可以继续，是否可以无限期休眠。
 *
 * 此函数是必需的，因为portSUPPRESS_TICKS_AND_SLEEP（）仅在调度程序挂起时调用，而不是在关键部分内调用。因此，中断可以请求端口SUPPRESS_TICKS_AND_SLEEP（）与实际进入的低功率模式之间的上下文切换。eTaskConfirmSleepModeStatus（）应该从计时器停止和进入睡眠模式之间的短关键部分调用，以确保可以进入睡眠模式。
 */
eSleepModeStatus eTaskConfirmSleepModeStatus( void ) PRIVILEGED_FUNCTION;

/*
 * 仅供内部使用。获取互斥锁时，增加互斥锁持有的计数，并返回获取互斥锁的任务的句柄。
 */
TaskHandle_t pvTaskIncrementMutexHeldCount( void ) PRIVILEGED_FUNCTION;

/*
 * 仅供内部使用。与vTaskSetTimeOutState（）相同，但没有关键部分。
 */
void vTaskInternalSetTimeOutState( TimeOut_t * const pxTimeOut ) PRIVILEGED_FUNCTION;

#ifdef ESP_PLATFORM
/* TODO: IDF-3683 */
#include "freertos/task_snapshot.h"
#endif // ESP_PLATFORM

/**@结束秒*/

#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */
#endif /* INC_TASK_H */

