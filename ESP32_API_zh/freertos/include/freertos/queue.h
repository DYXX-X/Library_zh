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


#ifndef QUEUE_H
#define QUEUE_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h" must appear in source files before "include queue.h"
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

#include "task.h"

/**
 * 引用队列的类型。例如，对xQueueCreate（）的调用返回一个QueueHandle_t变量，该变量可以用作xQueueSend（）、xQueueReceive（）等的参数。
 */
struct QueueDefinition; /* 使用旧的命名约定，以免破坏内核感知调试器。*/
typedef struct QueueDefinition   * QueueHandle_t;

/**
 * 引用队列集的类型。例如，对xQueueCreateSet（）的调用返回一个xQueueSet变量，该变量可以用作xQueueSelectFromSet（）、xQueueAddToSet（）等的参数。
 */
typedef struct QueueDefinition   * QueueSetHandle_t;

/**
 * 队列集可以同时包含队列和信号量，因此QueueSetMemberHandle_t被定义为要使用的类型，其中参数或返回值可以是QueueHandle_t或SemaphoreHandle_t。
 */
typedef struct QueueDefinition   * QueueSetMemberHandle_t;

/**@秒！文档_排除_标题_节*/

/* 仅供内部使用。*/
#define queueSEND_TO_BACK                     ( ( BaseType_t ) 0 )
#define queueSEND_TO_FRONT                    ( ( BaseType_t ) 1 )
#define queueOVERWRITE                        ( ( BaseType_t ) 2 )

/* 仅供内部使用。这些定义*必须*与queue.c中的定义匹配。*/
#define queueQUEUE_TYPE_BASE                  ( ( uint8_t ) 0U )
#define queueQUEUE_TYPE_SET                   ( ( uint8_t ) 0U )
#define queueQUEUE_TYPE_MUTEX                 ( ( uint8_t ) 1U )
#define queueQUEUE_TYPE_COUNTING_SEMAPHORE    ( ( uint8_t ) 2U )
#define queueQUEUE_TYPE_BINARY_SEMAPHORE      ( ( uint8_t ) 3U )
#define queueQUEUE_TYPE_RECURSIVE_MUTEX       ( ( uint8_t ) 4U )

/**@结束秒*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * QueueHandle_t xQueueCreate(
 *                            UBaseType_t uxQueueLength，
 *                            UBaseType_t uxItemSize
 *                        );
 * @endcode
 * @endcond
 *
 * 创建一个新的队列实例，并返回一个可以引用新队列的句柄。
 *
 * 在FreeRTOS实现内部，队列使用两块内存。第一个块用于保存队列的数据结构。第二个块用于保存放入队列中的项目。如果使用xQueueCreate（）创建队列，则两个内存块都会在xQueueCreate（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xQueueCreateStatic（）创建队列，则应用程序编写器必须提供队列将使用的内存。xQueueCreateStatic（）因此允许在不使用任何动态内存分配的情况下创建队列。
 *
 * https://www.FreeRTOS.org/Embedded-RTOS-Queues.html
 *
 * @param uxQueueLength 队列可以包含的最大项目数。
 *
 * @param uxItemSize 队列中每个项目所需的字节数。项目按复制而不是引用排队，因此这是每个已发布项目将复制的字节数。队列中的每个项目的大小必须相同。
 *
 * @return 如果成功创建了队列，则返回新创建的队列的句柄。如果无法创建队列，则返回0。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * };
 *
 * void vATask（void*pvParameters）
 * {
 * QueueHandle_t xQueue1，xQueue2；
 *
 *  //创建一个能够包含10个uint32_t值的队列。
 *  xQueue1=xQueueCreate（10，sizeof（uint32_t））；
 *  如果（xQueue1==0）
 *  {
 *      //队列未创建，不能使用。
 *  }
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue2=xQueueCreate（10，sizeof（结构AMessage*））；
 *  如果（xQueue2==0）
 *  {
 *      //队列未创建，不能使用。
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueCreate xQueue创建
 * @endcond \内部组队列管理
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define xQueueCreate( uxQueueLength, uxItemSize )    xQueueGenericCreate( ( uxQueueLength ), ( uxItemSize ), ( queueQUEUE_TYPE_BASE ) )
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * QueueHandle_t xQueueCreateStatic(
 *                            UBaseType_t uxQueueLength，
 *                            UBaseType_t uxItemSize，
 *                            uint8_t*pucQueueStorageBuffer，
 *                            静态队列_t*pxQueueBuffer
 *                        );
 * @endcode
 * @endcond 创建一个新的队列实例，并返回一个可以引用新队列的句柄。
 *
 * 在FreeRTOS实现内部，队列使用两块内存。第一个块用于保存队列的数据结构。第二个块用于保存放入队列中的项目。如果使用xQueueCreate（）创建队列，则两个内存块都会在xQueueCreate（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xQueueCreateStatic（）创建队列，则应用程序编写器必须提供队列将使用的内存。xQueueCreateStatic（）因此允许在不使用任何动态内存分配的情况下创建队列。
 *
 * https://www.FreeRTOS.org/Embedded-RTOS-Queues.html
 *
 * @param uxQueueLength 队列可以包含的最大项目数。
 *
 * @param uxItemSize 队列中每个项目所需的字节数。项目按复制而不是引用排队，因此这是每个已发布项目将复制的字节数。队列中的每个项目的大小必须相同。
 *
 * @param pucQueueStorage 如果uxItemSize不为零，则pucQueueStorageBuffer必须指向一个uint8_t数组，该数组至少足够大，可以容纳任何一次队列中可以容纳的最大项目数，即（uxQueueLength uxItemsSize）字节。如果uxItemSize为零，则pucQueueStorageBuffer可以为NULL。
 *
 * @param pxQueueBuffer 必须指向StaticQueue_t类型的变量，该变量将用于保存队列的数据结构。
 *
 * @return 如果创建了队列，则返回所创建队列的句柄。如果pxQueueBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * };
 *
 * #定义QUEUE_LENGTH 10
 * #定义ITEM_SIZE sizeof（uint32_t）
 *
 * //xQueueBuffer将保存队列结构。
 * StaticQueue_t xQueueBuffer；
 *
 * //ucQueueStorage将保存发布到队列的项目。必须至少
 * //[（队列长度）*（队列项目大小）]字节长。
 * uint8_t ucQueueStorage[QUEUE_LENGTH*ITEM_SIZE]；
 *
 * void vATask（void*pvParameters）
 * {
 * QueueHandle_t xQueue1；
 *
 *  //创建一个能够包含10个uint32_t值的队列。
 *  xQueue1=xQueueCreate（QUEUE_LENGTH，//队列可以容纳的项目数。
 *                          ITEM_SIZE//队列中每个项目的大小
 *                          &（ucQueueStorage[0]），//将保存队列中项目的缓冲区。
 *                          &xQueueBuffer）；//将保存队列结构的缓冲区。
 *
 *  //由于没有动态内存，因此保证成功创建队列
 *  //使用分配。因此，xQueue1现在是有效队列的句柄。
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueCreateStatic xQueueCreate静态
 * @endcond \内部组队列管理
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    #define xQueueCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxQueueBuffer )    xQueueGenericCreateStatic( ( uxQueueLength ), ( uxItemSize ), ( pucQueueStorage ), ( pxQueueBuffer ), ( queueQUEUE_TYPE_BASE ) )
#endif /* 配置支持状态分配*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_ x队列发送到前端(
 *                                 QueueHandle_t xQueue，
 *                                 const void*pvItemToQueue，
 *                                 TickType_t xTicksTo等待
 *                             );
 * @endcode
 * @endcond
 *
 * 将项目发布到队列的前面。该项按复制而不是引用排队。不能从中断服务例程调用此函数。请参见xQueueSendFromISR（），以获取可用于ISR的替代方案。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param xTicksToWait 如果队列中的空间已满，任务应阻止等待队列中的可用空间的最长时间。如果此值设置为0且队列已满，则调用将立即返回。时间以刻度周期定义，因此如果需要，应使用常量portTICK_PERIOD_MS将其转换为实时。
 *
 * @return pdTRUE（如果项目已成功发布），否则为errQUEUE_FULL。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * }xMessage；
 *
 * uint32_t-ulVar=10UL；
 *
 * void vATask（void*pvParameters）
 * {
 * QueueHandle_t xQueue1，xQueue2；
 * 结构AMessage*pxMessage；
 *
 *  //创建一个能够包含10个uint32_t值的队列。
 *  xQueue1=xQueueCreate（10，sizeof（uint32_t））；
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue2=xQueueCreate（10，sizeof（结构AMessage*））；
 *
 *  // ...
 *
 *  如果（xQueue1！=0）
 *  {
 *      //发送uint32_t。等待10个刻度，空间变为
 *      //必要时可用。
 *      如果（xQueueSendToFront（xQueue1，（void*）&ulVar，（TickType_t）10）！=pdPASS）
 *      {
 *          //即使在10点之后，也未能发布消息。
 *      }
 *  }
 *
 *  如果（xQueue2！=0）
 *  {
 *      //发送指向结构AMessage对象的指针。如果
 *      //队列已满。
 *      pxMessage=&xMessage；
 *      xQueueSendToFront（xQueue2，（void*）&pxMessage，（TickType_t）0）；
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSend xQueueSend
 * @endcond \内部组队列管理
 */
#define xQueueSendToFront( xQueue, pvItemToQueue, xTicksToWait ) \
    xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_FRONT )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_ x队列发送回(
 *                                 QueueHandle_t xQueue，
 *                                 const void*pvItemToQueue，
 *                                 TickType_t xTicksTo等待
 *                             );
 * @endcode
 * @endcond
 *
 * 这是一个调用xQueueGenericSend（）的宏。
 *
 * 将项目发布到队列的后面。该项按复制而不是引用排队。不能从中断服务例程调用此函数。请参见xQueueSendFromISR（），以获取可用于ISR的替代方案。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param xTicksToWait 如果队列中的空间已满，任务应阻止等待队列中的可用空间的最长时间。如果此值设置为0且队列已满，则调用将立即返回。时间以刻度周期定义，因此如果需要，应使用常量portTICK_PERIOD_MS将其转换为实时。
 *
 * @return pdTRUE（如果项目已成功发布），否则为errQUEUE_FULL。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * }xMessage；
 *
 * uint32_t-ulVar=10UL；
 *
 * void vATask（void*pvParameters）
 * {
 * QueueHandle_t xQueue1，xQueue2；
 * 结构AMessage*pxMessage；
 *
 *  //创建一个能够包含10个uint32_t值的队列。
 *  xQueue1=xQueueCreate（10，sizeof（uint32_t））；
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue2=xQueueCreate（10，sizeof（结构AMessage*））；
 *
 *  // ...
 *
 *  如果（xQueue1！=0）
 *  {
 *      //发送uint32_t。等待10个刻度，空间变为
 *      //必要时可用。
 *      如果（xQueueSendToBack（xQueue1，（void*）&ulVar，（TickType_t）10）！=pdPASS）
 *      {
 *          //即使在10点之后，也未能发布消息。
 *      }
 *  }
 *
 *  如果（xQueue2！=0）
 *  {
 *      //发送指向结构AMessage对象的指针。如果
 *      //队列已满。
 *      pxMessage=&xMessage；
 *      xQueueSendToBack（xQueue2，（void*）&pxMessage，（TickType_t）0）；
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSend xQueueSend
 * @endcond \内部组队列管理
 */
#define xQueueSendToBack( xQueue, pvItemToQueue, xTicksToWait ) \
    xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_ x队列发送(
 *                            QueueHandle_t xQueue，
 *                            const void*pvItemToQueue，
 *                            TickType_t xTicksTo等待
 *                       );
 * @endcode
 * @endcond
 *
 * 这是一个调用xQueueGenericSend（）的宏。它与FreeRTOS版本向后兼容。org，不包含xQueueSendToFront（）和xQueueSendToBack（）宏。它相当于xQueueSendToBack（）。
 *
 * 在队列中发布项目。该项按复制而不是引用排队。不能从中断服务例程调用此函数。请参见xQueueSendFromISR（），以获取可用于ISR的替代方案。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param xTicksToWait 如果队列中的空间已满，任务应阻止等待队列中的可用空间的最长时间。如果此值设置为0且队列已满，则调用将立即返回。时间以刻度周期定义，因此如果需要，应使用常量portTICK_PERIOD_MS将其转换为实时。
 *
 * @return pdTRUE（如果项目已成功发布），否则为errQUEUE_FULL。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * }xMessage；
 *
 * uint32_t-ulVar=10UL；
 *
 * void vATask（void*pvParameters）
 * {
 * QueueHandle_t xQueue1，xQueue2；
 * 结构AMessage*pxMessage；
 *
 *  //创建一个能够包含10个uint32_t值的队列。
 *  xQueue1=xQueueCreate（10，sizeof（uint32_t））；
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue2=xQueueCreate（10，sizeof（结构AMessage*））；
 *
 *  // ...
 *
 *  如果（xQueue1！=0）
 *  {
 *      //发送uint32_t。等待10个刻度，空间变为
 *      //必要时可用。
 *      如果（xQueueSend（xQueue1，（void*）&ulVar，（TickType_t）10）！=pdPASS）
 *      {
 *          //即使在10点之后，也未能发布消息。
 *      }
 *  }
 *
 *  如果（xQueue2！=0）
 *  {
 *      //发送指向结构AMessage对象的指针。如果
 *      //队列已满。
 *      pxMessage=&xMessage；
 *      xQueueSend（xQueue2，（void*）&pxMessage，（TickType_t）0）；
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSend xQueueSend
 * @endcond \内部组队列管理
 */
#define xQueueSend( xQueue, pvItemToQueue, xTicksToWait ) \
    xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_队列覆盖(
 *                            QueueHandle_t xQueue，
 *                            const void*pvItemToQueue
 *                       );
 * @endcode
 * @endcond
 *
 * 仅用于长度为1的队列，因此队列为空或已满。
 *
 * 在队列中发布项目。如果队列已满，则覆盖队列中保存的值。该项按复制而不是引用排队。
 *
 * 不能从中断服务例程调用此函数。请参见xQueueOverwriteFromISR（），以获取可用于ISR的替代方案。
 *
 * @param xQueue 将数据发送到的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @return xQueueOverwrite（）是一个调用xQueueGenericSend（）的宏，因此具有与xQueueSendToFront（）相同的返回值。然而，pdPASS是唯一可以返回的值，因为即使队列已满，xQueueOverwrite（）也会写入队列。
 *
 * 示例用法：
 * @code{c}
 *
 * void vFunction（void*pvParameters）
 * {
 * QueueHandle_t xQueue；
 * uint32_t ulVarToSend，ulValReceived；
 *
 *  //创建一个队列以保存一个uint32_t值。它是强烈的
 *  //建议*不要*在可以
 *  //包含多个值，这样做将触发断言
 *  //如果定义了configASSERT（）。
 *  xQueue=xQueueCreate（1，sizeof（uint32_t））；
 *
 *  //使用xQueueOverwrite（）将值10写入队列。
 *  ulVarToSend=10；
 *  xQueueOverwrite（xQueue，&ulVarToSend）；
 *
 *  //窥探队列现在应该返回10，但将值10保留在
 *  //队列。块时间为零，因为已知
 *  //队列保存一个值。
 *  ulValReceived=0；
 *  xQueuePeek（xQueue，&ulValReceived，0）；
 *
 *  如果（ulValReceived！=10）
 *  {
 *      //错误，除非该项目已被其他任务删除。
 *  }
 *
 *  //队列仍然已满。使用xQueueOverwrite（）覆盖
 *  //队列中保持的值为100。
 *  ulVarToSend=100；
 *  xQueueOverwrite（xQueue，&ulVarToSend）；
 *
 *  //这一次从队列中读取，再次将队列留空。
 *  //再次使用块时间0。
 *  xQueueReceive（xQueue，&ulValReceived，0）；
 *
 *  //读取的值应该是最后写入的值，即使
 *  //写入值时队列已满。
 *  如果（ulValReceived！=100）
 *  {
 *      //错误！
 *  }
 *
 *  // ...
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueOverwrite xQueueOverwrite
 * @endcond \内部组队列管理
 */
#define xQueueOverwrite( xQueue, pvItemToQueue ) \
    xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), 0, queueOVERWRITE )


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_ xQueueGenericSend(
 *                                  QueueHandle_t xQueue，
 *                                  const void*pvItemToQueue，
 *                                  TickType_t xTicksTo等待
 *                                  基本类型_ xCopyPosition
 *                              );
 * @endcode
 * @endcond
 *
 * 最好使用宏xQueueSend（）、xQueueSendToFront（）和xQueueSendToBack（）来代替直接调用此函数。
 *
 * 在队列中发布项目。该项按复制而不是引用排队。不能从中断服务例程调用此函数。请参见xQueueSendFromISR（），以获取可用于ISR的替代方案。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param xTicksToWait 如果队列中的空间已满，任务应阻止等待队列中的可用空间的最长时间。如果此值设置为0且队列已满，则调用将立即返回。时间以刻度周期定义，因此如果需要，应使用常量portTICK_PERIOD_MS将其转换为实时。
 *
 * @param xCopyPosition 可以采用值queueSEND_TO_BACK将项目放在队列的后面，也可以采用值queue SEND_TO_FRONT将项目放队列的前面（对于高优先级消息）。
 *
 * @return pdTRUE（如果项目已成功发布），否则为errQUEUE_FULL。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * }xMessage；
 *
 * uint32_t-ulVar=10UL；
 *
 * void vATask（void*pvParameters）
 * {
 * QueueHandle_t xQueue1，xQueue2；
 * 结构AMessage*pxMessage；
 *
 *  //创建一个能够包含10个uint32_t值的队列。
 *  xQueue1=xQueueCreate（10，sizeof（uint32_t））；
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue2=xQueueCreate（10，sizeof（结构AMessage*））；
 *
 *  // ...
 *
 *  如果（xQueue1！=0）
 *  {
 *      //发送uint32_t。等待10个刻度，空间变为
 *      //必要时可用。
 *      如果（xQueueGenericSend（xQueue1，（void*）&ulVar，（TickType_t）10，queueSEND_TO_BACK）！=pdPASS）
 *      {
 *          //即使在10点之后，也未能发布消息。
 *      }
 *  }
 *
 *  如果（xQueue2！=0）
 *  {
 *      //发送指向结构AMessage对象的指针。如果
 *      //队列已满。
 *      pxMessage=&xMessage；
 *      xQueueGenericSend（xQueue2，（void*）&pxMessage，（TickType_t）0，queueSEND_TO_BACK）；
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSend xQueueSend
 * @endcond \内部组队列管理
 */
BaseType_t xQueueGenericSend( QueueHandle_t xQueue,
                              const void * const pvItemToQueue,
                              TickType_t xTicksToWait,
                              const BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_队列Peek(
 *                           QueueHandle_t xQueue，
 *                           void*const pvBuffer，
 *                           TickType_t xTicksTo等待
 *                       );
 * @endcode
 * @endcond
 *
 * 从队列中接收项目，而不从队列中删除该项目。该项目通过副本接收，因此必须提供足够大小的缓冲区。复制到缓冲区的字节数是在创建队列时定义的。
 *
 * 成功接收的项目仍保留在队列中，因此下次调用或调用xQueueReceive（）时将再次返回。
 *
 * 此宏不能用于中断服务例程。请参阅xQueuePeekFromISR（）以获取可从中断服务例程调用的替代方法。
 *
 * @param xQueue 要从中接收项目的队列的句柄。
 *
 * @param pvBuffer 指向接收到的项将复制到其中的缓冲区的指针。
 *
 * @param xTicksToWait 如果在调用时队列为空，任务应阻止等待项目接收的最长时间。时间以刻度周期定义，因此如果需要，应使用常量portTICK_PERIOD_MS将其转换为实时。如果xTicksToWait为0且队列为空，xQueuePeek（）将立即返回。
 *
 * @return 如果从队列中成功接收到项目，则为pdTRUE，否则为pdFALSE。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * }xMessage；
 *
 * QueueHandle_t xQueue；
 *
 * //任务创建队列并发布值。
 * void vATask（void*pvParameters）
 * {
 * 结构AMessage*pxMessage；
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue=xQueueCreate（10，sizeof（结构AMessage*））；
 *  如果（xQueue==0）
 *  {
 *      //无法创建队列。
 *  }
 *
 *  // ...
 *
 *  //发送指向结构AMessage对象的指针。如果
 *  //队列已满。
 *  pxMessage=&xMessage；
 *  xQueueSend（xQueue，（void*）&pxMessage，（TickType_t）0）；
 *
 *  //…任务代码的其余部分。
 * }
 *
 * //任务以查看队列中的数据。
 * void vADdifferentialTask（void*pvParameters）
 * {
 * 结构AMessage*pxRxedMessage；
 *
 *  如果（xQueue！=0）
 *  {
 *      //在创建的队列上查看消息。如果
 *      //消息不立即可用。
 *      如果（xQueuePeek（xQueue，&（pxRxedMessage），（TickType_t）10））
 *      {
 *          //pcRxedMessage现在指向发布的结构AMessage变量
 *          //通过vATask，但该项目仍保留在队列中。
 *      }
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueuePeek xQueuePeek
 * @endcond \内部组队列管理
 */
BaseType_t xQueuePeek( QueueHandle_t xQueue,
                       void * const pvBuffer,
                       TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 来自ISR的BaseType_t xQueuePeek(
 *                                  QueueHandle_t xQueue，
 *                                  void*pvBuffer，
 *                              );
 * @endcode
 * @endcond
 *
 * 可以从中断服务例程（ISR）调用的xQueuePeek（）版本。
 *
 * 从队列中接收项目，而不从队列中删除该项目。该项目通过副本接收，因此必须提供足够大小的缓冲区。复制到缓冲区的字节数是在创建队列时定义的。
 *
 * 成功接收的项目仍保留在队列中，因此下次调用或调用xQueueReceive（）时将再次返回。
 *
 * @param xQueue 要从中接收项目的队列的句柄。
 *
 * @param pvBuffer 指向接收到的项将复制到其中的缓冲区的指针。
 *
 * @return 如果从队列中成功接收到项目，则为pdTRUE，否则为pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xQueuePeekFromISR xQueuePeekFromISR
 * @endcond \内部组队列管理
 */
BaseType_t xQueuePeekFromISR( QueueHandle_t xQueue,
                              void * const pvBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 基本类型_队列接收(
 *                               QueueHandle_t xQueue，
 *                               void*pvBuffer，
 *                               TickType_t xTicksTo等待
 *                          );
 * @endcode
 * @endcond
 *
 * 从队列中接收项目。该项目通过副本接收，因此必须提供足够大小的缓冲区。复制到缓冲区的字节数是在创建队列时定义的。
 *
 * 成功接收的项目将从队列中删除。
 *
 * 中断服务例程中不得使用此功能。请参见xQueueReceiveFromISR以了解可以的替代方案。
 *
 * @param xQueue 要从中接收项目的队列的句柄。
 *
 * @param pvBuffer 指向接收到的项将复制到其中的缓冲区的指针。
 *
 * @param xTicksToWait 如果在调用时队列为空，任务应阻止等待项目接收的最长时间。如果xTicksToWait为零且队列为空，xQueueReceive（）将立即返回。时间以刻度周期定义，因此如果需要，应使用常量portTICK_PERIOD_MS将其转换为实时。
 *
 * @return 如果从队列中成功接收到项目，则为pdTRUE，否则为pdFALSE。
 *
 * 示例用法：
 * @code{c}
 * 结构AMessage
 * {
 *  char ucMessageID；
 *  char ucData[20]；
 * }xMessage；
 *
 * QueueHandle_t xQueue；
 *
 * //任务创建队列并发布值。
 * void vATask（void*pvParameters）
 * {
 * 结构AMessage*pxMessage；
 *
 *  //创建一个能够包含10个指向AMessage结构的指针的队列。
 *  //这些应该通过指针传递，因为它们包含大量数据。
 *  xQueue=xQueueCreate（10，sizeof（结构AMessage*））；
 *  如果（xQueue==0）
 *  {
 *      //无法创建队列。
 *  }
 *
 *  // ...
 *
 *  //发送指向结构AMessage对象的指针。如果
 *  //队列已满。
 *  pxMessage=&xMessage；
 *  xQueueSend（xQueue，（void*）&pxMessage，（TickType_t）0）；
 *
 *  //…任务代码的其余部分。
 * }
 *
 * //要从队列中接收的任务。
 * void vADdifferentialTask（void*pvParameters）
 * {
 * 结构AMessage*pxRxedMessage；
 *
 *  如果（xQueue！=0）
 *  {
 *      //在创建的队列上接收消息。如果
 *      //消息不立即可用。
 *      如果（xQueueReceive（xQueue，&（pxRxedMessage），（TickType_t）10））
 *      {
 *          //pcRxedMessage现在指向发布的结构AMessage变量
 *          //通过vATask。
 *      }
 *  }
 *
 *  //…任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueReceive xQueueReceive
 * @endcond \内部组队列管理
 */
BaseType_t xQueueReceive( QueueHandle_t xQueue,
                          void * const pvBuffer,
                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * UBaseType_t uxQueueMessagesWaiting（const QueueHandle_t xQueue）；
 * @endcode
 * @endcond
 *
 * 返回存储在队列中的消息数。
 *
 * @param xQueue 正在查询的队列的句柄。
 *
 * @return 队列中可用的消息数。
 *
 * @cond !DOC_SINGLE_GROUP\解组uxQueueMessagesWaiting uxQueQueueMessages Waiting
 * @endcond \内部组队列管理
 */
UBaseType_t uxQueueMessagesWaiting( const QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * UBaseType_t uxQueueSpaces可用（const QueueHandle_t xQueue）；
 * @endcode
 * @endcond
 *
 * 返回队列中可用的可用空间数。这等于如果没有删除任何项目，在队列变满之前可以发送到队列的项目数。
 *
 * @param xQueue 正在查询的队列的句柄。
 *
 * @return 队列中可用的空间数。
 *
 * @cond !DOC_SINGLE_GROUP\解组uxQueueMessagesWaiting uxQueQueueMessages Waiting
 * @endcond \内部组队列管理
 */
UBaseType_t uxQueueSpacesAvailable( const QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * void vQueueDelete（QueueHandle_t xQueue）；
 * @endcode
 * @endcond
 *
 * 删除队列-释放为存储放置在队列中的项目而分配的所有内存。
 *
 * @param xQueue 要删除的队列的句柄。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vQueueDelete vQueue删除
 * @endcond \内部组队列管理
 */
void vQueueDelete( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * BaseType_t xQueueSendToFrontFromISR(
 *                                       QueueHandle_t xQueue，
 *                                       const void*pvItemToQueue，
 *                                       基本类型_t*pxHigherPriorityTaskWoken
 *                                    );
 * @endcode
 * @endcond
 *
 * 这是一个调用xQueueGenericSendFromISR（）的宏。
 *
 * 将项目发布到队列的前面。在中断服务例程中使用此宏是安全的。
 *
 * 项目按复制而非引用进行排队，因此最好只对小项目进行排队，特别是从ISR调用时。在大多数情况下，最好存储一个指向正在排队的项目的指针。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param[out] pxHigherPriorityTaskWoken xQueueSendToFrontFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE，如果发送到队列导致任务取消阻止，并且取消阻止的任务的优先级高于当前正在运行的任务。如果xQueueSendToFromFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @return 如果数据已成功发送到队列，则为pdTRUE，否则为errQUEUE_FULL。
 *
 * 缓冲IO的示例用法（ISR每次调用可以获得多个值）：
 * @code{c}
 * void vBufferISR（void）
 * {
 * 字符cIn；
 * BaseType_t xHigherPriorityTaskWoken；
 *
 *  //ISR开始时，我们还没有唤醒任务。
 *  xHigherPriorityTaskWoken=pdFALSE；
 *
 *  //循环，直到缓冲区为空。
 *  做
 *  {
 *      //从缓冲区中获取一个字节。
 *      cIn=端口INPUT_BYTE（RX_REREGISTER_ADDRESS）；
 *
 *      //发布字节。
 *      xQueueSendToFrontFromISR（xRxQueue，&cIn，&xHigherPriorityTaskWoken）；
 *
 *  }而（端口INPUT_BYTE（BUFFER_COUNT））；
 *
 *  //现在缓冲区是空的，我们可以根据需要切换上下文。
 *  如果（xHigherPriorityTaskWoken）
 *  {
 *      portYIELD_FROM_ISR（）；
 *  }
 * }
 * @endcode
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSendFromISR xQueueSendFromISR
 * @endcond \内部组队列管理
 */
#define xQueueSendToFrontFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueSEND_TO_FRONT )


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * BaseType_t xQueueSendToBackFromISR(
 *                                       QueueHandle_t xQueue，
 *                                       const void*pvItemToQueue，
 *                                       基本类型_t*pxHigherPriorityTaskWoken
 *                                    );
 * @endcode
 * @endcond
 *
 * 这是一个调用xQueueGenericSendFromISR（）的宏。
 *
 * 将项目发布到队列的后面。在中断服务例程中使用此宏是安全的。
 *
 * 项目按复制而非引用进行排队，因此最好只对小项目进行排队，特别是从ISR调用时。在大多数情况下，最好存储一个指向正在排队的项目的指针。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param[out] pxHigherPriorityTaskWoken xQueueSendToBackFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE，如果发送到队列导致任务取消阻止，并且取消阻止的任务的优先级高于当前正在运行的任务。如果xQueueSendToBackFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @return 如果数据已成功发送到队列，则为pdTRUE，否则为errQUEUE_FULL。
 *
 * 缓冲IO的示例用法（ISR每次调用可以获得多个值）：
 * @code{c}
 * void vBufferISR（void）
 * {
 * 字符cIn；
 * BaseType_t xHigherPriorityTaskWoken；
 *
 *  //ISR开始时，我们还没有唤醒任务。
 *  xHigherPriorityTaskWoken=pdFALSE；
 *
 *  //循环，直到缓冲区为空。
 *  做
 *  {
 *      //从缓冲区中获取一个字节。
 *      cIn=端口INPUT_BYTE（RX_REREGISTER_ADDRESS）；
 *
 *      //发布字节。
 *      xQueueSendToBackFromISR（xRxQueue，&cIn，&xHigherPriorityTaskWoken）；
 *
 *  }而（端口INPUT_BYTE（BUFFER_COUNT））；
 *
 *  //现在缓冲区是空的，我们可以根据需要切换上下文。
 *  如果（xHigherPriorityTaskWoken）
 *  {
 *      portYIELD_FROM_ISR（）；
 *  }
 * }
 * @endcode
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSendFromISR xQueueSendFromISR
 * @endcond \内部组队列管理
 */
#define xQueueSendToBackFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 来自ISR的BaseType_t xQueueOverwrite(
 *                            QueueHandle_t xQueue，
 *                            const void*pvItemToQueue，
 *                            基本类型_t*pxHigherPriorityTaskWoken
 *                       );
 * @endcode
 * @endcond
 *
 * xQueueOverwrite（）的一种版本，可用于中断服务例程（ISR）。
 *
 * 仅用于可容纳单个项目的队列，因此队列为空或已满。
 *
 * 在队列中发布项目。如果队列已满，则覆盖队列中保存的值。该项按复制而不是引用排队。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param[out] pxHigherPriorityTaskWoken xQueueOverwriteFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE，如果发送到队列导致任务取消阻止，并且取消阻止的任务的优先级高于当前正在运行的任务。如果xQueueOverwriteFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @return xQueueOverwriteFromISR（）是一个调用xQueueGenericSendFromISR的宏，因此具有与xQueueSendToFrontFromISR相同的返回值。但是，pdPASS是唯一可以返回的值，因为即使队列已满，xQueueOverwriteFromISR（）也会写入队列。
 *
 * 示例用法：
 * @code{c}
 *
 * QueueHandle_t xQueue；
 *
 * void vFunction（void*pvParameters）
 * {
 *  //创建一个队列以保存一个uint32_t值。它是强烈的
 *  //建议*不要*在可以
 *  //包含多个值，这样做将触发断言
 *  //如果定义了configASSERT（）。
 *  xQueue=xQueueCreate（1，sizeof（uint32_t））；
 * }
 *
 * void vAnInterruptHandler（void）
 * {
 * //xHigherPriorityTaskWoken在使用前必须设置为pdFALSE。
 * BaseType_t xHigherPriorityTaskWoken=pdFALSE；
 * uint32_t ulVarToSend，ulValReceived；
 *
 *  //使用xQueueOverwriteFromISR（）将值10写入队列。
 *  ulVarToSend=10；
 *  xQueueOverwriteFromISR（xQueue，&ulVarToSend，&xHigherPriorityTaskWoken）；
 *
 *  //队列已满，但再次调用xQueueOverwriteFromISR（）仍将
 *  //传递，因为队列中保存的值将被
 *  //新值。
 *  ulVarToSend=100；
 *  xQueueOverwriteFromISR（xQueue，&ulVarToSend，&xHigherPriorityTaskWoken）；
 *
 *  //从队列中读取现在将返回100。
 *
 *  // ...
 *
 *  如果（xHigherPriorityaskWoken==pdTRUE）
 *  {
 *      //写入队列导致任务取消阻止，并且取消阻止的任务
 *      //具有高于或等于当前优先级的
 *      //执行任务（该中断中断的任务）。执行上下文
 *      //开关，使该中断直接返回到未阻塞的任务。
 *      portYIELD_FROM_ISR（）；//或portEND_SWITCHING_ISR（），具体取决于端口。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueOverwriteFromISR xQueueOverwriteFromISR
 * @endcond \内部组队列管理
 */
#define xQueueOverwriteFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueOVERWRITE )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 来自ISR的BaseType_t xQueueSendFromISR(
 *                                   QueueHandle_t xQueue，
 *                                   const void*pvItemToQueue，
 *                                   基本类型_t*pxHigherPriorityTaskWoken
 *                              );
 * @endcode
 * @endcond
 *
 * 这是一个调用xQueueGenericSendFromISR（）的宏。它与FreeRTOS版本向后兼容。org，不包括xQueueSendToBackFromISR（）和xQueueSend ToFrontFromISR）宏。
 *
 * 将项目发布到队列的后面。在中断服务例程中使用此功能是安全的。
 *
 * 项目按复制而非引用进行排队，因此最好只对小项目进行排队，特别是从ISR调用时。在大多数情况下，最好存储一个指向正在排队的项目的指针。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param[out] pxHigherPriorityTaskWoken xQueueSendFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE，如果发送到队列导致任务取消阻止，并且取消阻止的任务的优先级高于当前正在运行的任务。如果xQueueSendFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @return 如果数据已成功发送到队列，则为pdTRUE，否则为errQUEUE_FULL。
 *
 * 缓冲IO的示例用法（ISR每次调用可以获得多个值）：
 * @code{c}
 * void vBufferISR（void）
 * {
 * 字符cIn；
 * BaseType_t xHigherPriorityTaskWoken；
 *
 *  //ISR开始时，我们还没有唤醒任务。
 *  xHigherPriorityTaskWoken=pdFALSE；
 *
 *  //循环，直到缓冲区为空。
 *  做
 *  {
 *      //从缓冲区中获取一个字节。
 *      cIn=端口INPUT_BYTE（RX_REREGISTER_ADDRESS）；
 *
 *      //发布字节。
 *      xQueueSendFromISR（xRxQueue，&cIn，&xHigherPriorityTaskWoken）；
 *
 *  }而（端口INPUT_BYTE（BUFFER_COUNT））；
 *
 *  //现在缓冲区是空的，我们可以根据需要切换上下文。
 *  如果（xHigherPriorityTaskWoken）
 *  {
 *      //此处使用的实际宏是特定于端口的。
 *      portYIELD_FROM_ISR（）；
 *  }
 * }
 * @endcode
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueSendFromISR xQueueSendFromISR
 * @endcond \内部组队列管理
 */
#define xQueueSendFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )

/**@秒！文档_排除_标题_节*/
/**@{*/
/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 来自ISR的BaseType_t xQueueGenericSendFromISR(
 *                                         QueueHandle_t xQueue，
 *                                         const void*pvItemToQueue，
 *                                         BaseType_t*pxHigherPriorityTaskWoken，
 *                                         基本类型_ xCopyPosition
 *                                     );
 * @endcode
 * @endcond
 *
 * 最好使用宏xQueueSendFromISR（）、xQueueSendToFrontFromISR（）和xQueueSend ToBackFromISR）来代替直接调用此函数。xQueueGiveFromISR（）是实际上不复制任何数据的信号量使用的等效函数。
 *
 * 在队列中发布项目。在中断服务例程中使用此功能是安全的。
 *
 * 项目按复制而非引用进行排队，因此最好只对小项目进行排队，特别是从ISR调用时。在大多数情况下，最好存储一个指向正在排队的项目的指针。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param[out] pxHigherPriorityTaskWoken xQueueGenericSendFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE，如果发送到队列导致任务取消阻止，并且取消阻止的任务的优先级高于当前正在运行的任务。如果xQueueGenericSendFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @param xCopyPosition 可以采用值queueSEND_TO_BACK将项目放在队列的后面，也可以采用值queue SEND_TO_FRONT将项目放队列的前面（对于高优先级消息）。
 *
 * @return 如果数据已成功发送到队列，则为pdTRUE，否则为errQUEUE_FULL。
 *
 * 缓冲IO的示例用法（ISR每次调用可以获得多个值）：
 * @code{c}
 * void vBufferISR（void）
 * {
 * 字符cIn；
 * BaseType_t xHigherPriorityTaskWokenByPost；
 *
 *  //ISR开始时，我们还没有唤醒任务。
 *  xHigherPriorityTaskWokenByPost=pdFALSE；
 *
 *  //循环，直到缓冲区为空。
 *  做
 *  {
 *      //从缓冲区中获取一个字节。
 *      cIn=端口INPUT_BYTE（RX_REREGISTER_ADDRESS）；
 *
 *      //张贴每个字节。
 *      xQueueGenericSendFromISR（xRxQueue，&cIn，&xHigherPriorityTaskWokenByPost，queueSEND_TO_BACK）；
 *
 *  }而（端口INPUT_BYTE（BUFFER_COUNT））；
 *
 *  //现在缓冲区是空的，我们可以根据需要切换上下文。注意
 *  //所需的yield函数的名称是特定于端口的。
 *  如果（xHigherPriorityTaskWokenByPost）
 *  {
 *      taskYIELD_YIELD_FROM_ISR（）；
 *  }
 * }
 * @endcode
 *
 * \内部组队列管理
 */
BaseType_t xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                     const void * const pvItemToQueue,
                                     BaseType_t * const pxHigherPriorityTaskWoken,
                                     const BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;
BaseType_t xQueueGiveFromISR( QueueHandle_t xQueue,
                              BaseType_t * const pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;
/**@}*/
/**@结束秒*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION队列。小时
 * @code{c}
 * 来自ISR的BaseType_t xQueueReceive(
 *                                     QueueHandle_t xQueue，
 *                                     void*pvBuffer，
 *                                     基本类型_t*pxTaskWoken
 *                                 );
 * @endcode
 * @endcond
 *
 * 从队列中接收项目。在中断服务例程中使用此功能是安全的。
 *
 * @param xQueue 要从中接收项目的队列的句柄。
 *
 * @param pvBuffer 指向接收到的项将复制到其中的缓冲区的指针。
 *
 * @param[out] pxHigherPriorityTaskWoken 任务可能会被阻止，等待队列上的空间变为可用。如果xQueueReceiveFromISR导致此类任务解除阻止，pxTaskWoken将设置为pdTRUE，否则pxTaskWoken将保持不变。
 *
 * @return 如果从队列中成功接收到项目，则为pdTRUE，否则为pdFALSE。
 *
 * 示例用法：
 * @code{c}
 *
 * QueueHandle_t xQueue；
 *
 * //函数创建队列并发布一些值。
 * void vA函数（void*pvParameters）
 * {
 * char cValueToPost；
 * const TickType_t xTicksToWait=（TickType_t）0xff；
 *
 *  //创建一个能够包含10个字符的队列。
 *  xQueue=xQueueCreate（10，sizeof（char））；
 *  如果（xQueue==0）
 *  {
 *      //无法创建队列。
 *  }
 *
 *  // ...
 *
 *  //发布将在ISR中使用的一些字符。如果队列
 *  //如果已满，则此任务将阻止xTicksToWait标记。
 *  cValueToPost=“a”；
 *  xQueueSend（xQueue，（void*）&cValueToPost，xTicksToWait）；
 *  cValueToPost=“b”；
 *  xQueueSend（xQueue，（void*）&cValueToPost，xTicksToWait）；
 *
 *  //…继续发布字符…此任务可能会在队列
 *  //变满。
 *
 *  cValueToPost=“c”；
 *  xQueueSend（xQueue，（void*）&cValueToPost，xTicksToWait）；
 * }
 *
 * //ISR，输出队列上接收的所有字符。
 * void vISR_例程（void）
 * {
 * BaseType_t xTaskWokenByReceive=pdFALSE；
 * 字符cRxedChar；
 *
 *  while（xQueueReceiveFromISR（xQueue，（void*）&cRxedChar，&xTaskWokenByReceive））
 *  {
 *      //收到一个字符。现在输出角色。
 *      vOutputCharacter（cRxedChar）；
 *
 *      //如果从队列中删除角色
 *      //发布到队列cTaskWokenByReceive将设置为
 *      //pdTRUE。无论此循环重复多少次，都只重复一次
 *      //任务将被唤醒。
 *  }
 *
 *  如果（cTaskWokenByPost！=（char）pdFALSE；
 *  {
 *      taskYIELD（）；
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xQueueReceiveFromISR xQueueReceiveFromISR
 * @endcond \内部组队列管理
 */
BaseType_t xQueueReceiveFromISR( QueueHandle_t xQueue,
                                 void * const pvBuffer,
                                 BaseType_t * const pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

/*
 * 用于从ISR查询安全使用的队列的实用程序。这些实用程序只能在ISR中或关键部分内使用。
 */
BaseType_t xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;
BaseType_t xQueueIsQueueFullFromISR( const QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;
UBaseType_t uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

/**@秒！文档_排除_标题_节*/
/*
 * 上面定义的函数用于向任务传递数据和从任务传递数据。下面的函数是将数据传递到协例程和从协例程传递数据的等价函数。
 *
 * 这些函数是从协例程宏实现调用的，不应直接从应用程序代码调用。而是使用croutine.h中定义的宏包装器。
 */
BaseType_t xQueueCRSendFromISR( QueueHandle_t xQueue,
                                const void * pvItemToQueue,
                                BaseType_t xCoRoutinePreviouslyWoken );
BaseType_t xQueueCRReceiveFromISR( QueueHandle_t xQueue,
                                   void * pvBuffer,
                                   BaseType_t * pxTaskWoken );
BaseType_t xQueueCRSend( QueueHandle_t xQueue,
                         const void * pvItemToQueue,
                         TickType_t xTicksToWait );
BaseType_t xQueueCRReceive( QueueHandle_t xQueue,
                            void * pvBuffer,
                            TickType_t xTicksToWait );

/**
 * 仅供内部使用。使用xSemaphoreCreateMutex（）、xSemaphoeCreateCount（）或xSemapphoreGetMutexHolder（），而不是直接调用这些函数。
 */
QueueHandle_t xQueueCreateMutex( const uint8_t ucQueueType ) PRIVILEGED_FUNCTION;
QueueHandle_t xQueueCreateMutexStatic( const uint8_t ucQueueType,
                                       StaticQueue_t * pxStaticQueue ) PRIVILEGED_FUNCTION;
QueueHandle_t xQueueCreateCountingSemaphore( const UBaseType_t uxMaxCount,
                                             const UBaseType_t uxInitialCount ) PRIVILEGED_FUNCTION;
QueueHandle_t xQueueCreateCountingSemaphoreStatic( const UBaseType_t uxMaxCount,
                                                   const UBaseType_t uxInitialCount,
                                                   StaticQueue_t * pxStaticQueue ) PRIVILEGED_FUNCTION;
BaseType_t xQueueSemaphoreTake( QueueHandle_t xQueue,
                                TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;
TaskHandle_t xQueueGetMutexHolder( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;
TaskHandle_t xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

/**
 * 仅供内部使用。使用xSemaphoreTakeMutexRecursive（）或xSemaphreGiveMutex递归（），而不是直接调用这些函数。
 */
BaseType_t xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                     TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;
BaseType_t xQueueGiveMutexRecursive( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

/**@结束秒*/

/**
 * 将队列重置回其原始空状态。返回值现在已过时，始终设置为pdPASS。
 */
#define xQueueReset( xQueue )    xQueueGenericReset( xQueue, pdFALSE )

/**
 * 注册表是作为内核感知调试器定位队列、信号量和互斥体的一种方法提供的。调用vQueueAddToRegistry（）将队列、信号量或互斥句柄添加到注册表中，如果您希望该句柄可用于内核感知调试器。如果没有使用内核感知调试器，则可以忽略此函数。
 *
 * configQUEUE_REGISTRY_SIZE定义注册表可以容纳的最大句柄数。configQUEUE_REGISTRY_SIZE在FreeRTOSConfig中必须大于0。h表示注册表可用。它的值不影响可以创建的队列、信号量和互斥量的数量，只影响注册表可以保存的数量。
 *
 * @param xQueue 正在添加到注册表的队列的句柄。这是调用xQueueCreate（）返回的句柄。信号量和互斥量句柄也可以在这里传递。
 *
 * @param pcQueueName 要与句柄关联的名称。这是内核感知调试器将显示的名称。队列注册表只存储一个指向字符串的指针，因此字符串必须是持久的（全局的，最好是在ROM/Flash中），而不是在堆栈上。
 */
#if ( configQUEUE_REGISTRY_SIZE > 0 )
    void vQueueAddToRegistry( QueueHandle_t xQueue,
                              const char * pcQueueName ) PRIVILEGED_FUNCTION; /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
#endif

/**
 * 注册表是作为内核感知调试器定位队列、信号量和互斥体的一种方法提供的。调用vQueueAddToRegistry（）将队列、信号量或互斥量句柄添加到注册表中（如果您希望该句柄可用于内核感知调试器），并调用vQueuiUnregisterQueue（）从寄存器中删除队列、信号或互斥量。如果没有使用内核感知调试器，则可以忽略此函数。
 *
 * @param xQueue 从注册表中删除的队列的句柄。
 */
#if ( configQUEUE_REGISTRY_SIZE > 0 )
    void vQueueUnregisterQueue( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;
#endif

/**
 * 队列注册表是内核感知调试器定位队列、信号量和互斥量的一种方法。调用pcQueueGetName（）从队列句柄中查找并返回队列注册表中的队列名称。
 *
 * @param xQueue 将返回其名称的队列的句柄。
 * @return 如果队列在注册表中，则返回指向队列名称的指针。如果队列不在注册表中，则返回NULL。
 */
#if ( configQUEUE_REGISTRY_SIZE > 0 )
    const char * pcQueueGetName( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION; /*绒毛e971不合格的字符类型仅允许用于字符串和单个字符。*/
#endif

/**
 * 用于使用动态内存分配创建队列的函数的通用版本。这由其他函数和宏调用，这些函数和宏创建使用队列结构作为基础的其他RTOS对象。
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength,
                                       const UBaseType_t uxItemSize,
                                       const uint8_t ucQueueType ) PRIVILEGED_FUNCTION;
#endif

/**
 * 用于使用动态内存分配创建队列的函数的通用版本。这由其他函数和宏调用，这些函数和宏创建使用队列结构作为基础的其他RTOS对象。
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    QueueHandle_t xQueueGenericCreateStatic( const UBaseType_t uxQueueLength,
                                             const UBaseType_t uxItemSize,
                                             uint8_t * pucQueueStorage,
                                             StaticQueue_t * pxStaticQueue,
                                             const uint8_t ucQueueType ) PRIVILEGED_FUNCTION;
#endif

/**
 * 队列集提供了一种机制，允许任务同时阻止（挂起）来自多个队列或信号量的读取操作。
 *
 * 请参阅FreeRTOS/Source/Demo/Common/Minimal/QueueSet。c表示使用此函数的示例。
 *
 * 在使用队列集之前，必须使用对xQueueCreateSet（）的调用显式创建队列集。创建后，可以使用对xQueueAddToSet（）的调用将标准FreeRTOS队列和信号量添加到集合中。然后使用xQueueSelectFromSet（）确定集合中包含的队列或信号量中的哪一个（如果有的话）处于队列读取或信号量获取操作将成功的状态。
 *
 * 注1：请参阅https://www.FreeRTOS.org/RTOS-queue-sets.html因为在实践中很少需要队列集，因为在多个对象上有更简单的阻塞方法。
 *
 * 注意2：对包含互斥锁的队列集进行阻塞不会导致互斥锁持有者继承被阻塞任务的优先级。
 *
 * 注3：添加到队列集的每个队列中的每个空间需要额外的4字节RAM。因此，最大计数值较高的计数信号量不应添加到队列集。
 *
 * 注意4：除非对xQueueSelectFromSet（）的调用首先向队列集成员返回了句柄，否则不能对队列集的成员执行receive（在队列的情况下）或take（在信号量的情况）操作。
 *
 * @param uxEventQueueLength 队列集存储发生在队列上的事件和集中包含的信号量。uxEventQueueLength指定一次可以排队的最大事件数。为了确保事件不会丢失，uxEventQueueLength应设置为添加到集合中的队列长度的总和，其中二进制信号量和互斥量的长度为1，计数信号量的长度由其最大计数值设置。示例：+如果队列集包含长度为5的队列、长度为12的另一个队列和二进制信号量，则uxEventQueueLength应设置为（5+12+1）或18。+如果队列集中包含三个二进制信号量则uxEvent QueueLength应该设置为（1+1+1）或3。+如果一个队列集包含最大计数为5的计数信号量，以及最大计数为3的计数信号量，则uxEventQueueLength应设置为（5+3）或8。
 *
 * @return 如果成功创建了队列集，则返回创建的队列集的句柄。否则返回NULL。
 */
QueueSetHandle_t xQueueCreateSet( const UBaseType_t uxEventQueueLength ) PRIVILEGED_FUNCTION;

/**
 * 将队列或信号量添加到先前通过调用xQueueCreateSet（）创建的队列集。
 *
 * 请参阅FreeRTOS/Source/Demo/Common/Minimal/QueueSet。c表示使用此函数的示例。
 *
 * 注意1：除非对xQueueSelectFromSet（）的调用首先向队列集成员返回了句柄，否则不能对队列集的成员执行receive（在队列的情况下）或take（在信号量的情况）操作。
 *
 * @param xQueueOrSemaphore 要添加到队列集的队列或信号量的句柄（强制转换为QueueSetMemberHandle_t类型）。
 *
 * @param xQueueSet 要添加队列或信号量的队列集的句柄。
 *
 * @return 如果队列或信号已成功添加到队列集，则返回pdPASS。如果由于队列已是其他队列集的成员，因此无法成功将其添加到队列集，则返回pdFAIL。
 */
BaseType_t xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                           QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

/**
 * 从队列集中删除队列或信号量。只有当队列或信号为空时，才能从集合中删除队列或信号。
 *
 * 请参阅FreeRTOS/Source/Demo/Common/Minimal/QueueSet。c表示使用此函数的示例。
 *
 * @param xQueueOrSemaphore 从队列集中删除的队列或信号量的句柄（强制转换为QueueSetMemberHandle_t类型）。
 *
 * @param xQueueSet 包含队列或信号量的队列集的句柄。
 *
 * @return 如果队列或信号已从队列集中成功删除，则返回pdPASS。如果队列不在队列集中，或者队列（或信号量）不为空，则返回pdFAIL。
 */
BaseType_t xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

/**
 * xQueueSelectFromSet（）从队列集的成员中选择包含数据（在队列的情况下）或可获取数据（在信号量的情况下，）的队列或信号量。xQueueSelectFromSet（）有效地允许任务同时阻止（挂起）队列集中所有队列和信号量的读取操作。
 *
 * 请参阅FreeRTOS/Source/Demo/Common/Minimal/QueueSet。c表示使用此函数的示例。
 *
 * 注1：请参阅https://www.FreeRTOS.org/RTOS-queue-sets.html因为在实践中很少需要队列集，因为在多个对象上有更简单的阻塞方法。
 *
 * 注意2：对包含互斥锁的队列集进行阻塞不会导致互斥锁持有者继承被阻塞任务的优先级。
 *
 * 注意3：除非对xQueueSelectFromSet（）的调用首先向队列集成员返回了句柄，否则不能对队列集的成员执行receive（在队列的情况下）或take（在信号量的情况）操作。
 *
 * @param xQueueSet 任务将（可能）阻塞的队列集。
 *
 * @param xTicksToWait 调用任务保持在“已阻止”状态（其他任务正在执行）以等待队列集的成员准备好成功执行队列读取或信号量获取操作的最长时间（以节拍为单位）。
 *
 * @return xQueueSelectFromSet（）将返回包含数据的队列集中包含的队列句柄（强制转换为QueueSetMemberHandle_t类型），或可用的队列集中所包含的信号量句柄（强制转化为QueueSetMemberHandle_t类型），如果在指定的块时间到期之前不存在此类队列或信号量，则返回NULL。
 */
QueueSetMemberHandle_t xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                            const TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * 可以从ISR中使用的xQueueSelectFromSet（）版本。
 */
QueueSetMemberHandle_t xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

/**@秒！文档_排除_标题_节*/

/* 不是公共API函数。*/
void vQueueWaitForMessageRestricted( QueueHandle_t xQueue,
                                     TickType_t xTicksToWait,
                                     const BaseType_t xWaitIndefinitely ) PRIVILEGED_FUNCTION;
BaseType_t xQueueGenericReset( QueueHandle_t xQueue,
                               BaseType_t xNewQueue ) PRIVILEGED_FUNCTION;
void vQueueSetQueueNumber( QueueHandle_t xQueue,
                           UBaseType_t uxQueueNumber ) PRIVILEGED_FUNCTION;
UBaseType_t uxQueueGetQueueNumber( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;
uint8_t ucQueueGetQueueType( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

/**@结束秒*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* QUEUE_H */

