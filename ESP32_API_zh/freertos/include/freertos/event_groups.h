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

#ifndef EVENT_GROUPS_H
#define EVENT_GROUPS_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h" must appear in source files before "include event_groups.h"
#endif

/* FreeRTOS包括。*/
#include "timers.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**
 * 事件组是应用程序可以为其分配意义的位的集合。例如，应用程序可以创建一个事件组来传达各种CAN总线相关事件的状态，其中位0可能表示“已接收到CAN消息并准备好进行处理”，位1可能表示“应用程序已将准备发送到CAN网络的消息排队”，位2可能表示“是时候将SYNC消息发送到CAN网了”。然后，任务可以测试位值以查看哪些事件处于活动状态，并且可以选择进入“阻止”状态以等待指定位或一组指定位处于活动状态。为了继续CAN总线示例，CAN控制任务可以进入阻止状态（因此不消耗任何处理时间），直到位0、位1或位2处于活动状态，此时实际活动的位将通知任务必须采取的操作（处理接收到的消息、发送消息或发送SYNC）。
 *
 * 事件组实现包含避免竞争条件的智能，否则，如果应用程序将简单变量用于相同目的，则会发生竞争条件。这对于何时清除事件组中的一个位，以及何时必须设置位，然后进行原子测试，尤其重要，因为事件组用于在多个任务之间创建同步点（“会合”）。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup事件组事件组
 * @endcond
 */



/**
 * 事件组.h
 *
 * 引用事件组的类型。例如，对xEventGroupCreate（）的调用返回一个EventGroupHandle_t变量，该变量可以用作其他事件组函数的参数。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup EventGroupHandle_t事件组句柄_t
 * @endcond \内部组事件组
 */
struct EventGroupDef_t;
#ifdef ESP_PLATFORM // IDF-3770
typedef void * EventGroupHandle_t;
#else
typedef struct EventGroupDef_t * EventGroupHandle_t;
#endif // ESP_PLATFORM
/*
 * 保存事件位的类型始终与TickType_t匹配，因此它保存的位数由configUSE_16_BIT_TICKS设置（如果设置为1，则为16位，如果设置为0，则为32位）。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup EventBits_t事件Bits_t
 * @endcond \内部组事件组
 */
typedef TickType_t               EventBits_t;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 * EventGroupHandle_t xEventGroupCreate（无效）；
 * @endcode
 * @endcond
 *
 * 创建新的事件组。
 *
 * 在FreeRTOS实现内部，事件组使用一个[小]内存块，其中存储了事件组的结构。如果使用xEventGroupCreate（）创建事件组，则所需的内存将在xEventGroupCreate（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xEventGroupCreateStatic（）创建事件组，则应用程序编写器必须提供事件组将使用的内存。xEventGroupCreateStatic（）因此允许在不使用任何动态内存分配的情况下创建事件组。
 *
 * 尽管事件组与滴答不相关，但出于内部实现原因，事件组中可用的位数取决于FreeRTOSConfig.h中的configUSE_16_BIT_ticks设置。如果configUSE_16BIT_ticks为1，则每个事件组包含8个可用位（位0到位7）。如果configUSE_16_BIT_TICKS设置为0，则每个事件组有24个可用位（位0到位23）。EventBits_t类型用于存储事件组中的事件位。
 *
 * @return 如果创建了事件组，则返回事件组的句柄。如果没有足够的FreeRTOS堆可用于创建事件组，则返回NULL。看见https://www.FreeRTOS.org/a00111.html
 *
 * 示例用法：
 * @code{c}
 *  //声明一个变量以保存创建的事件组。
 *  EventGroupHandle_t xCreatedEventGroup；
 *
 *  //尝试创建事件组。
 *  xCreatedEventGroup=xEventGroupCreate（）；
 *
 *  //事件组创建成功吗？
 *  如果（xCreatedEventGroup==NULL）
 *  {
 *      //由于不足，未创建事件组
 *      //FreeRTOS堆可用。
 *  }
 *  其他的
 *  {
 *      //已创建事件组。
 *  }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupCreate xEventGroup创建
 * @endcond \内部组事件组
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    EventGroupHandle_t xEventGroupCreate( void ) PRIVILEGED_FUNCTION;
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 * EventGroupHandle_t xEventGroupCreateStatic（EventGroupHandle_t*pxEventGroupBuffer）；
 * @endcode
 * @endcond
 *
 * 创建新的事件组。
 *
 * 在FreeRTOS实现内部，事件组使用一个[小]内存块，其中存储了事件组的结构。如果使用xEventGroupCreate（）创建事件组，则所需的内存将在xEventGroupCreate（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xEventGroupCreateStatic（）创建事件组，则应用程序编写器必须提供事件组将使用的内存。xEventGroupCreateStatic（）因此允许在不使用任何动态内存分配的情况下创建事件组。
 *
 * 尽管事件组与滴答不相关，但出于内部实现原因，事件组中可用的位数取决于FreeRTOSConfig.h中的configUSE_16_BIT_ticks设置。如果configUSE_16BIT_ticks为1，则每个事件组包含8个可用位（位0到位7）。如果configUSE_16_BIT_TICKS设置为0，则每个事件组有24个可用位（位0到位23）。EventBits_t类型用于存储事件组中的事件位。
 *
 * @param pxEventGroupBuffer pxEventGroupBuffer必须指向StaticEventGroup_t类型的变量，该变量将用于保存事件组的数据结构，从而不需要动态分配内存。
 *
 * @return 如果创建了事件组，则返回事件组的句柄。如果pxEventGroupBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 *  //StaticEventGroup_t是一个具有相同
 *  //大小和对齐要求作为真实的事件组结构。它是
 *  //作为应用程序了解事件大小的机制提供
 *  //组（取决于体系结构和配置文件
 *  //设置），而不违反严格的数据隐藏策略
 *  //真实事件组内部。传递了此StaticEventGroup_t变量
 *  //到xSemaphoreCreateEventGroupStatic（）函数中，并用于存储
 *  //事件组的数据结构
 *  StaticEventGroup_t xEventGroupBuffer；
 *
 *  //创建事件组而不动态分配任何内存。
 *  xEventGroup=xEventGroupCreateStatic（&xEventGroupBuffer）；
 * @endcode
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    EventGroupHandle_t xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) PRIVILEGED_FUNCTION;
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  EventBits_t xEventGroupWaitBits（EventGroupHandle_t xEventGroup，
 *                                      const EventBits_t uxBitsTo等待，
 *                                      常量BaseType_t xClearOnExit，
 *                                      const BaseType_t xWaitForAllBits，
 *                                      const TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * [可能]块等待在先前创建的事件组中设置一个或多个位。
 *
 * 不能从中断调用此函数。
 *
 * @param xEventGroup 正在测试位的事件组。事件组之前必须使用对xEventGroupCreate（）的调用创建。
 *
 * @param uxBitsToWaitFor 一个位值，指示事件组中要测试的位。例如，要等待位0和/或位2，请将uxBitsToWaitFor设置为0x05。要等待位1和/或2，请设置uxBitsToWaitFor为0x07。
 *
 * @param xClearOnExit 如果xClearOnExit设置为pdTRUE，则如果满足等待条件（如果函数返回的原因不是超时），则在xEventGroupWaitBits（）返回之前，将清除事件组中设置的uxBitsToWaitFor中的任何位。如果xClearOnExit设置为pdFALSE，则当对xEventGroupWaitBits（）的调用返回时，不会更改事件组中设置的位。
 *
 * @param xWaitForAllBits 如果xWaitForAllBits设置为pdTRUE，则xEventGroupWaitBits（）将在uxBitsToWaitFor中的所有位被设置或指定的块时间到期时返回。如果xWaitForAllBits设置为pdFALSE，则xEventGroupWaitBits（）将在uxBitsToWaitFor中设置的任何一个位被设置或指定的块时间到期时返回。块时间由xTicksToWait参数指定。
 *
 * @param xTicksToWait 等待uxBitsToWaitFor指定的一个/所有位（取决于xWaitForAllBits值）设置的最长时间（以“ticks”指定）。
 *
 * @return 等待的位被设置或块时间到期时事件组的值。测试返回值以了解设置了哪些位。如果xEventGroupWaitBits（）因超时而返回，则不会设置所有等待的位。如果xEventGroupWaitBits（）返回是因为它等待的位被设置，则返回的值是在xClearOnExit参数设置为pdTRUE的情况下自动清除任何位之前的事件组值。
 *
 * 示例用法：
 * @code{c}
 * #定义BIT_0（1<<0）
 * #定义BIT_4（1<<4）
 *
 * void aFunction（EventGroupHandle_t xEventGroup）
 * {
 * 事件Bits_t uxBits；
 * 常量TickType_t xTicksToWait=100/portTICK_PERIOD_MS；
 *
 *      //最多等待100ms，以使第0位或第4位设置在
 *      //事件组。退出前清除位。
 *      uxBits=xEventGroupWaitBits(
 *                  xEventGroup，//正在测试的事件组。
 *                  BIT_0|BIT_4，//事件组中要等待的位。
 *                  pdTRUE、//BIT_0和BIT_4应在返回前清除。
 *                  pdFALSE，//不要等待两位，任何一位都可以。
 *                  xTicksToWait）；//最多等待100毫秒，以设置任一位。
 *
 *      如果（（uxBits&（BIT_0|BIT_4））==（BIT_0| BIT_4）
 *      {
 *          //xEventGroupWaitBits（）返回，因为两个位都已设置。
 *      }
 *      否则如果（（uxBits&BIT_0）！=0 )
 *      {
 *          //xEventGroupWaitBits（）返回，因为仅设置了BIT_0。
 *      }
 *      否则如果（（uxBits&BIT_4）！=0 )
 *      {
 *          //xEventGroupWaitBits（）返回，因为仅设置了BIT_4。
 *      }
 *      其他的
 *      {
 *          //xEventGroupWaitBits（）返回，因为xTicksToWait标记已通过
 *          //而BIT_ 0或BIT_。
 *      }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupWaitBits xEventGroupWaitBits
 * @endcond \内部组事件组
 */
EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                 const EventBits_t uxBitsToWaitFor,
                                 const BaseType_t xClearOnExit,
                                 const BaseType_t xWaitForAllBits,
                                 TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  EventBits_t xEventGroupClearBits（EventGroupHandle_t xEventGroup，常量EventBits_tuxBitsToClear）；
 * @endcode
 * @endcond
 *
 * 清除事件组中的位。不能从中断调用此函数。
 *
 * @param xEventGroup 要清除位的事件组。
 *
 * @param uxBitsToClear 一个位值，指示事件组中要清除的位。例如，要仅清除位3，请将uxBitsToClear设置为0x08。要清除位3和位0，请将ux BitsToCClear设置为0x09。
 *
 * @return 清除指定位之前事件组的值。
 *
 * 示例用法：
 * @code{c}
 * #定义BIT_0（1<<0）
 * #定义BIT_4（1<<4）
 *
 * void aFunction（EventGroupHandle_t xEventGroup）
 * {
 * 事件Bits_t uxBits；
 *
 *      //清除xEventGroup中的位0和位4。
 *      uxBits=xEventGroupClearBits(
 *                              xEventGroup，//正在更新的事件组。
 *                              BIT_0|BIT_4）；//正在清除的位。
 *
 *      如果（（uxBits&（BIT_0|BIT_4））==（BIT_0| BIT_4）
 *      {
 *          //在xEventGroupClearBits（）之前设置了位0和位4
 *          //已调用。现在，这两个选项都已清除（未设置）。
 *      }
 *      否则如果（（uxBits&BIT_0）！=0 )
 *      {
 *          //在调用xEventGroupClearBits（）之前设置了位0。它会
 *          //现在说清楚了。
 *      }
 *      否则如果（（uxBits&BIT_4）！=0 )
 *      {
 *          //在调用xEventGroupClearBits（）之前设置了位4。它会
 *          //现在说清楚了。
 *      }
 *      其他的
 *      {
 *          //首先，位0和位4都未设置。
 *      }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupClearBits xEventGroupClear Bits
 * @endcond \内部组事件组
 */
EventBits_t xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                  const EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  BaseType_t xEventGroupClearBitsFromISR（EventGroupHandle_t xEvent Group，常量EventBits_t uxBitsToSet）；
 * @endcode
 * @endcond
 *
 * 可以从中断调用的xEventGroupClearBits（）版本。
 *
 * 在事件组中设置位不是确定性操作，因为可能有未知数量的任务正在等待设置位。FreeRTOS不允许在中断被禁用时执行非确定性操作，因此通过暂停调度程序而不是禁用中断来保护从任务中访问的事件组。因此，不能从中断服务例程直接访问事件组。因此，xEventGroupClearBitsFromISR（）向计时器任务发送消息，以在计时器任务的上下文中执行清除操作。
 *
 * @param xEventGroup 要清除位的事件组。
 *
 * @param uxBitsToClear 一种按位值，指示要清除的位。例如，要仅清除位3，请将uxBitsToClear设置为0x08。要清除位3和位0，请将ux BitsToCClear设置为0x09。
 *
 * @return 如果成功发布了执行函数的请求，则返回pdPASS，否则返回pdFALSE。如果计时器服务队列已满，将返回pdFALSE。
 *
 * 示例用法：
 * @code{c}
 * #定义BIT_0（1<<0）
 * #定义BIT_4（1<<4）
 *
 * //假定已通过调用创建了事件组
 * //xEventGroupCreate（）。
 * EventGroupHandle_t xEventGroup；
 *
 * void anInterruptHandler（void）
 * {
 *      //清除xEventGroup中的位0和位4。
 *      xResult=xEventGroupClearBitsFromISR(
 *                          xEventGroup，//正在更新的事件组。
 *                          BIT_0|BIT_4）；//正在设置的位。
 *
 *      如果（xResult==pdPASS）
 *      {
 *          //邮件已成功发布。
 *      }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupClearBitsFromISR xEventGroup ClearBitsFrom ISR
 * @endcond \内部组事件组
 */
#if ( configUSE_TRACE_FACILITY == 1 )
    BaseType_t xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                            const EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;
#else
    #define xEventGroupClearBitsFromISR( xEventGroup, uxBitsToClear ) \
    xTimerPendFunctionCallFromISR( vEventGroupClearBitsCallback, ( void * ) xEventGroup, ( uint32_t ) uxBitsToClear, NULL )
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  EventBits_t xEventGroupSetBits（EventGroupHandle_t xEventGroup，常量EventBits_tuxBitsToSet）；
 * @endcode
 * @endcond
 *
 * 在事件组中设置位。不能从中断调用此函数。xEventGroupSetBitsFromISR（）是一个可以从中断调用的版本。
 *
 * 在事件组中设置位将自动解除阻止等待位的任务。
 *
 * @param xEventGroup 要设置位的事件组。
 *
 * @param uxBitsToSet 指示要设置的位的按位值。例如，若要仅设置位3，请将uxBitsToSet设置为0x08。若要设置位3和位0，请将ux BitsToSSet设置为0x09。
 *
 * @return 调用xEventGroupSetBits（）返回时事件组的值。返回的值可能会清除uxBitsToSet参数指定的位，原因有两个。首先，如果设置一个位导致任务等待该位离开阻止状态，则该位可能会被自动清除（请参阅xEventGroupWaitBits（）的xClearBitOnExit参数）。第二，任何优先级高于调用xEventGroupSetBits（）的任务的未阻塞（或就绪状态）任务都将执行，并可能在调用xEventGroup SetBits）返回之前更改事件组值。
 *
 * 示例用法：
 * @code{c}
 * #定义BIT_0（1<<0）
 * #定义BIT_4（1<<4）
 *
 * void aFunction（EventGroupHandle_t xEventGroup）
 * {
 * 事件Bits_t uxBits；
 *
 *      //在xEventGroup中设置位0和位4。
 *      uxBits=xEventGroupSetBits(
 *                          xEventGroup，//正在更新的事件组。
 *                          BIT_0|BIT_4）；//正在设置的位。
 *
 *      如果（（uxBits&（BIT_0|BIT_4））==（BIT_0| BIT_4）
 *      {
 *          //当函数返回时，位0和位4都保持置位。
 *      }
 *      否则如果（（uxBits&BIT_0）！=0 )
 *      {
 *          //当函数返回时，位0保持设置，但位4为
 *          //清除。可能是第4位被自动清除为
 *          //正在等待第4位的任务已从阻止的
 *          //州。
 *      }
 *      否则如果（（uxBits&BIT_4）！=0 )
 *      {
 *          //当函数返回时，位4保持设置，但位0为
 *          //清除。可能是位0被自动清除为
 *          //正在等待位0的任务已从阻止的
 *          //州。
 *      }
 *      其他的
 *      {
 *          //位0和位4均未设置。这可能是一项任务
 *          //正在等待设置两个位
 *          //在任务离开“阻止”状态时清除。
 *      }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupSetBits xEventGroupSet Bits
 * @endcond \内部组事件组
 */
EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                const EventBits_t uxBitsToSet ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  BaseType_t xEventGroupSetBitsFromISR（EventGroupHandle_t xEvent Group，const EventBits_tuxBitsToSet，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 可以从中断调用的xEventGroupSetBits（）版本。
 *
 * 在事件组中设置位不是确定性操作，因为可能有未知数量的任务正在等待设置位。FreeRTOS不允许在中断或关键部分执行非确定性操作。因此，xEventGroupSetBitsFromISR（）向计时器任务发送一条消息，以便在计时器任务的上下文中执行设置操作，其中使用调度程序锁代替关键部分。
 *
 * @param xEventGroup 要设置位的事件组。
 *
 * @param uxBitsToSet 指示要设置的位的按位值。例如，若要仅设置位3，请将uxBitsToSet设置为0x08。若要设置位3和位0，请将ux BitsToSSet设置为0x09。
 *
 * @param pxHigherPriorityTaskWoken 如上所述，调用此函数将导致向计时器守护进程任务发送消息。如果计时器守护程序任务的优先级高于当前正在运行的任务（中断中断的任务）的优先级，则xEventGroupSetBitsFromISR（）会将pxHigherPriorityTaskWoken设置为pdTRUE，表示中断退出前应请求上下文切换。因此，pxHigherPriorityTaskWoken必须初始化为pdFALSE。请参见下面的示例代码。
 *
 * @return 如果成功发布了执行函数的请求，则返回pdPASS，否则返回pdFALSE。如果计时器服务队列已满，将返回pdFALSE。
 *
 * 示例用法：
 * @code{c}
 * #定义BIT_0（1<<0）
 * #定义BIT_4（1<<4）
 *
 * //假定已通过调用创建了事件组
 * //xEventGroupCreate（）。
 * EventGroupHandle_t xEventGroup；
 *
 * void anInterruptHandler（void）
 * {
 * BaseType_t xHigherPriorityTaskWoken，xResult；
 *
 *      //xHigherPriorityTaskWoken必须初始化为pdFALSE。
 *      xHigherPriorityTaskWoken=pdFALSE；
 *
 *      //在xEventGroup中设置位0和位4。
 *      xResult=xEventGroupSetBitsFromISR(
 *                          xEventGroup，//正在更新的事件组。
 *                          BIT_0|BIT_4//正在设置的位。
 *                          &xHigherPriorityTaskWoken）；
 *
 *      //邮件发布成功吗？
 *      如果（xResult==pdPASS）
 *      {
 *          //如果xHigherPriorityTaskWoken现在设置为pdTRUE，则上下文
 *          //应请求切换。所使用的宏是特定于端口的
 *          //将是portYIELD_FROM_ISR（）或portEND_SWITCHING_ISR（）-
 *          //请参阅所使用端口的文档页面。
 *          端口YIELD_FROM_ISR（xHigherPriorityTaskWoken）；
 *      }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupSetBitsFromISR xEventGroupSet BitsFromISR
 * @endcond \内部组事件组
 */
#if ( configUSE_TRACE_FACILITY == 1 )
    BaseType_t xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                          const EventBits_t uxBitsToSet,
                                          BaseType_t * pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;
#else
    #define xEventGroupSetBitsFromISR( xEventGroup, uxBitsToSet, pxHigherPriorityTaskWoken ) \
    xTimerPendFunctionCallFromISR( vEventGroupSetBitsCallback, ( void * ) xEventGroup, ( uint32_t ) uxBitsToSet, pxHigherPriorityTaskWoken )
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  EventBits_t xEventGroupSync（EventGroupHandle_t xEventGroup，
 *                                  常量事件Bits_t uxBitsToSet，
 *                                  const EventBits_t uxBitsTo等待，
 *                                  TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 在事件组中原子地设置位，然后等待在同一事件组中设置位的组合。此功能通常用于同步多个任务，其中每个任务必须等待其他任务到达同步点才能继续。
 *
 * 此功能不能从中断中使用。
 *
 * 如果uxBitsToWait参数指定的位被设置或在该时间内被设置，则函数将在其块时间到期之前返回。在这种情况下，uxBitsToWait指定的所有位将在函数返回之前自动清除。
 *
 * @param xEventGroup 正在测试位的事件组。事件组之前必须使用对xEventGroupCreate（）的调用创建。
 *
 * @param uxBitsToSet 在确定是否设置了uxBitsToWait参数指定的所有位并可能等待这些位之前，要在事件组中设置的位。
 *
 * @param uxBitsToWaitFor 一个位值，指示事件组中要测试的位。例如，要等待第0位和第2位，请将uxBitsToWaitFor设置为0x05。要等待第1位和第1位，请设置uxBitsToWaitFor为0x07。
 *
 * @param xTicksToWait 等待设置uxBitsToWaitFor指定的所有位的最长时间（以“ticks”指定）。
 *
 * @return 等待的位被设置或块时间到期时事件组的值。测试返回值以了解设置了哪些位。如果xEventGroupSync（）因超时而返回，则不会设置等待的所有位。如果xEventGroupSync（）返回，因为它等待的所有位都已设置，则返回的值是自动清除任何位之前的事件组值。
 *
 * 示例用法：
 * @code{c}
 * //三个任务使用的位。
 * #定义TASK_0_BIT（1<<0）
 * #定义TASK_1_BIT（1<<1）
 * #定义TASK_2_BIT（1<<2）
 *
 * #定义ALL_SYNC_BITS（TASK_0_BIT | TASK_1_BIT | TASK_2_BIT）
 *
 * //使用事件组同步三项任务。假设该事件
 * //已经在其他地方创建了组。
 * EventGroupHandle_t xEventBits；
 *
 * void vTask0（void*pvParameters）
 * {
 * 事件Bits_t uxReturn；
 * TickType_t xTicksToWait=100/portTICK_PERIOD_MS；
 *
 *   用于（；；）
 *   {
 *      //在此处执行任务功能。
 *
 *      //在事件标志中设置位0，以注意此任务已到达
 *      //同步点。其他两个任务将设置定义的其他两个位
 *      //由ALL_SYNC_ BITS执行。所有三项任务都已达到同步
 *      //设置所有all_SYNC_BITS时的点。最多等待100毫秒
 *      //让这一切发生。
 *      uxReturn=xEventGroupSync（xEventBits，TASK_0_BIT，ALL_SYNC_BITS，xTicksToWait）；
 *
 *      如果（（uxReturn&ALL_SYNC_BITS）==ALL_SYNC_BITS）
 *      {
 *          //所有三项任务都在通话前到达同步点
 *          //到xEventGroupSync（）超时。
 *      }
 *  }
 * }
 *
 * void vTask1（void*pvParameters）
 * {
 *   用于（；；）
 *   {
 *      //在此处执行任务功能。
 *
 *      //在事件标志中设置位1，以注意此任务已到达
 *      //同步点。其他两项任务将设置其他两项
 *      //由ALL_SYNC_bits定义的位。所有三项任务都已达到
 *      //当设置了所有all_SYNC_ BITS时的同步点。等待
 *      //无限期地等待这种情况发生。
 *      xEventGroupSync（xEventBits，TASK_1_BIT，ALL_SYNC_BITS，端口MAX_DELAY）；
 *
 *      //调用xEventGroupSync（）的块时间不确定，因此
 *      //只有在所有人进行同步时，此任务才会到达此处
 *      //三个任务，因此不需要测试返回值。
 *   }
 * }
 *
 * void vTask2（void*pvParameters）
 * {
 *   用于（；；）
 *   {
 *      //在此处执行任务功能。
 *
 *      //在事件标志中设置第2位，以注意此任务已到达
 *      //同步点。其他两项任务将设置其他两项
 *      //由ALL_SYNC_bits定义的位。所有三项任务都已达到
 *      //当设置了所有all_SYNC_ BITS时的同步点。等待
 *      //无限期地等待这种情况发生。
 *      xEventGroupSync（xEventBits，TASK_2_BIT，ALL_SYNC_BITS，端口MAX_DELAY）；
 *
 *      //调用xEventGroupSync（）的块时间不确定，因此
 *      //只有在所有人进行同步时，此任务才会到达此处
 *      //三个任务，因此不需要测试返回值。
 *  }
 * }
 *
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupSync x EventGroupSync
 * @endcond \内部组事件组
 */
EventBits_t xEventGroupSync( EventGroupHandle_t xEventGroup,
                             const EventBits_t uxBitsToSet,
                             const EventBits_t uxBitsToWaitFor,
                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  EventBits_t xEventGroupGetBits（EventGroupHandle_t xEventGroup）；
 * @endcode
 * @endcond
 *
 * 返回事件组中位的当前值。此功能不能从中断中使用。
 *
 * @param xEventGroup 正在查询的事件组。
 *
 * @return 调用xEventGroupGetBits（）时的事件组位。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupGetBits xEventGroupGet Bits
 * @endcond \内部组事件组
 */
#define xEventGroupGetBits( xEventGroup )    xEventGroupClearBits( xEventGroup, 0 )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  EventBits_t xEventGroupGetBitsFromISR（EventGroupHandle_t xEventGroup）；
 * @endcode
 * @endcond
 *
 * 可以从ISR调用的xEventGroupGetBits（）版本。
 *
 * @param xEventGroup 正在查询的事件组。
 *
 * @return 调用xEventGroupGetBitsFromISR（）时的事件组位。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xEventGroupGetBitsFromISR xEventGroup GetBitsFrom ISR
 * @endcond \内部组事件组
 */
EventBits_t xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION事件组.h
 * @code{c}
 *  void xEventGroupDelete（EventGroupHandle_t xEventGroup）；
 * @endcode
 * @endcond
 *
 * 删除以前通过调用xEventGroupCreate（）创建的事件组。事件组中被阻止的任务将被取消阻止，并获得0作为事件组的值。
 *
 * @param xEventGroup 正在删除的事件组。
 */
void vEventGroupDelete( EventGroupHandle_t xEventGroup ) PRIVILEGED_FUNCTION;

/**@秒！文档_排除_标题_节*/

/* 仅供内部使用。*/
void vEventGroupSetBitsCallback( void * pvEventGroup,
                                 const uint32_t ulBitsToSet ) PRIVILEGED_FUNCTION;
void vEventGroupClearBitsCallback( void * pvEventGroup,
                                   const uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;


#if ( configUSE_TRACE_FACILITY == 1 )
    UBaseType_t uxEventGroupGetNumber( void * xEventGroup ) PRIVILEGED_FUNCTION;
    void vEventGroupSetNumber( void * xEventGroup,
                               UBaseType_t uxEventGroupNumber ) PRIVILEGED_FUNCTION;
#endif

/**@结束秒*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* EVENT_GROUPS_H */

