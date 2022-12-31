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

#ifndef CO_ROUTINE_H
#define CO_ROUTINE_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h must appear in source files before include croutine.h"
#endif

#include "list.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* 用于隐藏协同例程控制块的实现。然而，由于协例程功能的宏实现，控制块结构必须包括在报头中。*/
typedef void * CoRoutineHandle_t;

/* 定义协同例程函数必须符合的原型。*/
typedef void (* crCOROUTINE_CODE)( CoRoutineHandle_t,
                                   UBaseType_t );

typedef struct corCoRoutineControlBlock
{
    crCOROUTINE_CODE pxCoRoutineFunction;
    ListItem_t xGenericListItem; /*<用于将CRCB放置在就绪队列和阻塞队列中的列表项。*/
    ListItem_t xEventListItem;   /*<用于将CRCB放置在事件列表中的列表项。*/
    UBaseType_t uxPriority;      /*<协同程序相对于其他协同程序的优先级。*/
    UBaseType_t uxIndex;         /*<当多个协同例程使用同一协同例程函数时，用于区分协同例程。*/
    uint16_t uxState;            /*<由协同例程实现在内部使用。*/
} CRCB_t;                        /* 共同程序控制块。注释的大小必须与TCB_t的uxPriority相同。*/

/**
 * @cond 面包屑。小时
 * @code{c}
 * BaseType_t xCoRoutine创建(
 *                               crCOROUTINE_CODE pxCoRoutineCode，
 *                               UBaseType_t uxPriority，
 *                               UBaseType_t uxIndex
 *                             );
 * @endcode
 * @endcond
 *
 * 创建一个新的协同例程，并将其添加到准备运行的协同例程列表中。
 *
 * @param pxCoRoutineCode 指向协同例程函数的指针。协例程函数需要特殊的语法-有关更多信息，请参阅WEB文档的协例程部分。
 *
 * @param uxPriority 相对于其他协同例程的优先级，协同例程将在该优先级下运行。
 *
 * @param uxIndex 用于区分执行相同功能的不同协同例程。有关更多信息，请参阅下面的示例和WEB文档的共同例程部分。
 *
 * @return pdPASS，如果成功创建了协同例程并将其添加到就绪列表中，否则将显示用ProjDefs.h定义的错误代码。
 *
 * 示例用法：
 * @code{c}
 * //要创建的共同例程。
 * void vFlashCoRoutine（CoRoutineHandle_t xHandle，UBaseType_t uxIndex）
 * {
 * //如果协例程中的变量必须在阻塞调用中保持值，则必须将其声明为静态。
 * //对于常量变量，这可能不是必需的。
 * 静态常量字符cLedToFlash[2]=｛5，6｝；
 * 静态常量TickType_t uxFlashRates[2]=｛200，400｝；
 *
 *   //必须通过调用crSTART（）启动每个协同例程；
 *   crSTART（xHandle）；
 *
 *   用于（；；）
 *   {
 *       //这个协同例程只是延迟一段固定的时间，然后切换
 *       //LED。使用此函数创建了两个协同例程，因此
 *       //uxIndex参数用于告诉协同例程
 *       //LED闪烁，int32_t延迟。这假设xQueue具有
 *       //已创建。
 *       vParTestToggleLED（cLedToFlash[uxIndex]）；
 *       crDELAY（xHandle，uxFlashRates[uxIndex]）；
 *   }
 *
 *   //必须以调用crEND（）结束每个协同例程；
 *   crEND（）；
 * }
 *
 * //创建两个协同例程的函数。
 * void vOtherFunction（void）
 * {
 * uint8_t ucParameterToPass；
 * 任务句柄_t xHandle；
 *
 *   //创建两个优先级为0的协同例程。第一个为索引0
 *   //因此（从上面的代码中）每200个节拍切换一次LED5。第二个
 *   //被赋予索引1，因此每400个周期切换LED 6。
 *   对于（uxIndex=0；uxIndex<2；uxIndex++）
 *   {
 *       xCoRoutineCreate（vFlashCoRoutine，0，uxIndex）；
 *   }
 * }
 * @endcode
 * @cond \定义组xCoRoutineCreate xCoRoutingeCreate
 * @endcond \内部组任务
 */
BaseType_t xCoRoutineCreate( crCOROUTINE_CODE pxCoRoutineCode,
                             UBaseType_t uxPriority,
                             UBaseType_t uxIndex );


/**
 * @cond 面包屑。小时
 * @code{c}
 * 作废vCoRoutineSchedue（作废）；
 * @endcode
 * @endcond 运行联合例程。
 *
 * vCoRoutineSchedule（）执行能够运行的最高优先级协同例程。协同例程将执行，直到它阻塞、产生或被任务抢占。协同例程协同执行，因此一个协同例程不能被另一个抢占，但可以被一个任务抢占。
 *
 * 如果应用程序同时包含任务和协同例程，则应从空闲任务（在空闲任务挂钩中）调用vCoRoutineSchedule。
 *
 * 示例用法：
 * @code{c}
 * //这个空闲任务钩子将在每次调用时调度一个协同例程。
 * //其余的空闲任务将在协同例程调用之间执行。
 * void vApplicationIdleHook（void）
 * {
 *  vCoRoutineSchedule（）；
 * }
 *
 * //或者，如果您不需要空闲任务的任何其他部分
 * //执行时，空闲任务钩子可以在
 * //无限循环。
 * void vApplicationIdleHook（void）
 * {
 *  用于（；；）
 *  {
 *      vCoRoutineSchedule（）；
 *  }
 * }
 * @endcode
 * @endcode
 * @cond \defgroup vCoRoutineSchedule vCoRouineSchedule
 * @endcond \内部组任务
 */
void vCoRoutineSchedule( void );

/**
 * @cond 面包屑。小时
 * @code{c}
 * crSTART（CoRoutineHandle_t xHandle）；
 * @endcode
 * @endcond
 *
 * 必须始终在协同例程函数开始时调用此宏。
 *
 * 示例用法：
 * @code{c}
 * //要创建的共同例程。
 * void vACoRoutine（CoRoutineHandle_t xHandle，UBaseType_t uxIndex）
 * {
 * //如果协例程中的变量必须在阻塞调用中保持值，则必须将其声明为静态。
 * 静态int32_t ulAVariable；
 *
 *   //必须通过调用crSTART（）启动每个协同例程；
 *   crSTART（xHandle）；
 *
 *   用于（；；）
 *   {
 *        //这里提供了协同例程功能。
 *   }
 *
 *   //必须以调用crEND（）结束每个协同例程；
 *   crEND（）；
 * }
 * @endcode
 * @cond \defgroup crSTART crSTART
 * @endcond \内部组任务
 */
#define crSTART( pxCRCB )                            \
    switch( ( ( CRCB_t * ) ( pxCRCB ) )->uxState ) { \
        case 0:

/**
 * @cond 面包屑。小时
 * @code{c}
 * crEND（）；
 * @endcode
 * @endcond
 *
 * 必须始终在协同例程函数的末尾调用此宏。
 *
 * 示例用法：
 * @code{c}
 * //要创建的共同例程。
 * void vACoRoutine（CoRoutineHandle_t xHandle，UBaseType_t uxIndex）
 * {
 * //如果协例程中的变量必须在阻塞调用中保持值，则必须将其声明为静态。
 * 静态int32_t ulAVariable；
 *
 *   //必须通过调用crSTART（）启动每个协同例程；
 *   crSTART（xHandle）；
 *
 *   用于（；；）
 *   {
 *        //这里提供了协同例程功能。
 *   }
 *
 *   //必须以调用crEND（）结束每个协同例程；
 *   crEND（）；
 * }
 * @endcode
 * @cond \defgroup crSTART crSTART
 * @endcond \内部组任务
 */
#define crEND()    }

/*
 * 这些宏仅供协同例程实现内部使用。应用程序编写器不应直接使用宏。
 */
#define crSET_STATE0( xHandle )                                       \
    ( ( CRCB_t * ) ( xHandle ) )->uxState = ( __LINE__ * 2 ); return; \
    case ( __LINE__ * 2 ):
#define crSET_STATE1( xHandle )                                               \
    ( ( CRCB_t * ) ( xHandle ) )->uxState = ( ( __LINE__ * 2 ) + 1 ); return; \
    case ( ( __LINE__ * 2 ) + 1 ):

/**
 * @cond 面包屑。小时
 * @code{c}
 * crDELAY（CoRoutineHandle_t xHandle，TickType_t xTicksToDelay）；
 * @endcode
 * @endcond
 *
 * 将协同例程延迟一段固定的时间。
 *
 * crDELAY只能从协同例程函数本身调用，而不能从协同例程调用的函数内部调用。这是因为协同例程不维护自己的堆栈。
 *
 * @param xHandle 要延迟的协同例程的句柄。这是协同例程函数的xHandle参数。
 *
 * @param xTickToDelay 协同例程应延迟的刻度数。这相当于的实际时间量由configTICK_RATE_HZ（在FreeRTOSConfig.h中设置）定义。常量portTICK_PERIOD_MS可用于将计时转换为毫秒。
 *
 * 示例用法：
 * @code{c}
 * //要创建的共同例程。
 * void vACoRoutine（CoRoutineHandle_t xHandle，UBaseType_t uxIndex）
 * {
 * //如果协例程中的变量必须在阻塞调用中保持值，则必须将其声明为静态。
 * //对于常量变量，这可能不是必需的。
 * //我们将延迟200毫秒。
 * 静态常量xTickType xDelayTime=200/portTICK_PERIOD_MS；
 *
 *   //必须通过调用crSTART（）启动每个协同例程；
 *   crSTART（xHandle）；
 *
 *   用于（；；）
 *   {
 *      //延迟200ms。
 *      crDELAY（xHandle，xDelayTime）；
 *
 *      //在这里做点什么。
 *   }
 *
 *   //必须以调用crEND（）结束每个协同例程；
 *   crEND（）；
 * }
 * @endcode
 * @cond \defgroup crDELAY crDELAY
 * @endcond \内部组任务
 */
#define crDELAY( xHandle, xTicksToDelay )                      \
    if( ( xTicksToDelay ) > 0 )                                \
    {                                                          \
        vCoRoutineAddToDelayedList( ( xTicksToDelay ), NULL ); \
    }                                                          \
    crSET_STATE0( ( xHandle ) );

/**
 * @cond
 * @code{c}
 * 请求_发送(
 *                CoRoutineHandle_t xHandle，
 *                QueueHandle_t pxQueue，
 *                void*pvItemToQueue，
 *                TickType_t xTicksTo等待，
 *                基本类型_t*pxResult
 *           )
 * @endcode
 * @endcond
 *
 * 宏的crQUEUE_SEND（）和crQUEUE_RECEIVE（）是与任务使用的xQueueSend（）和xQueueReceive（）函数等效的协例程。
 *
 * crQUEUE_SEND和crQUEUE_RECEIVE只能从协同例程中使用，而xQueueSend（）和xQueueReceive（）只能从任务中使用。
 *
 * crQUEUE_SEND只能从协同例程函数本身调用，而不能从协同例程调用的函数内部调用。这是因为协同例程不维护自己的堆栈。
 *
 * 有关在任务和协同程序之间以及ISR与协同程序之间传递数据的信息，请参阅WEB文档的协同程序部分。
 *
 * @param xHandle 调用协同例程的句柄。这是协同例程函数的xHandle参数。
 *
 * @param pxQueue 将在其上发布数据的队列的句柄。当使用xQueueCreate（）API函数创建队列时，获取句柄作为返回值。
 *
 * @param pvItemToQueue 指向发布到队列中的数据的指针。创建队列时指定每个排队项目的字节数。此字节数从pvItemToQueue复制到队列本身。
 *
 * @param xTickToDelay 如果空间不能立即可用，协同例程应阻止等待队列上的空间可用的标记数。这相当于的实际时间量由configTICK_RATE_HZ（在FreeRTOSConfig.h中设置）定义。常量portTICK_PERIOD_MS可用于将滴答声转换为毫秒（参见下面的示例）。
 *
 * @param pxResult 如果数据成功发布到队列中，pxResult指向的变量将设置为pdPASS，否则将设置为ProjDefs.h中定义的错误。
 *
 * 示例用法：
 * @code{c}
 * //共例程函数，在一段固定时间内阻塞，然后将一个数字发布到
 * //队列。
 * 静态void prvCoRoutineFlashTask（CoRoutine_t xHandle，UBaseType_t uxIndex）
 * {
 * //如果协例程中的变量必须在阻塞调用中保持值，则必须将其声明为静态。
 * 静态BaseType_t xNumberToPost=0；
 * 静态BaseType_t xResult；
 *
 *  //协同例程必须以调用crSTART（）开始。
 *  crSTART（xHandle）；
 *
 *  用于（；；）
 *  {
 *      //这假设队列已经创建。
 *      crQUEUE_SEND（xHandle，xCoRoutineQueue，&xNumberToPost，NO_DELAY，&xResult）；
 *
 *      如果（xResult！=pdPASS）
 *      {
 *          //消息未发布！
 *      }
 *
 *      //增加要发布到队列中的数字。
 *      xNumberToPost++；
 *
 *      //延迟100个刻度。
 *      crDELAY（x手柄，100）；
 *  }
 *
 *  //协同例程必须以调用crEND（）结束。
 *  crEND（）；
 * }
 * @endcode
 * @cond \解组crQUEUE_SEND crQUEUE_SEND
 * @endcond \内部组任务
 */
#define crQUEUE_SEND( xHandle, pxQueue, pvItemToQueue, xTicksToWait, pxResult )           \
    {                                                                                     \
        *( pxResult ) = xQueueCRSend( ( pxQueue ), ( pvItemToQueue ), ( xTicksToWait ) ); \
        if( *( pxResult ) == errQUEUE_BLOCKED )                                           \
        {                                                                                 \
            crSET_STATE0( ( xHandle ) );                                                  \
            *pxResult = xQueueCRSend( ( pxQueue ), ( pvItemToQueue ), 0 );                \
        }                                                                                 \
        if( *pxResult == errQUEUE_YIELD )                                                 \
        {                                                                                 \
            crSET_STATE1( ( xHandle ) );                                                  \
            *pxResult = pdPASS;                                                           \
        }                                                                                 \
    }

/**
 * @cond 面包屑。小时
 * @code{c}
 * 请求接收(
 *                   CoRoutineHandle_t xHandle，
 *                   QueueHandle_t pxQueue，
 *                   void*pvBuffer，
 *                   TickType_t xTicksTo等待，
 *                   基本类型_t*pxResult
 *               )
 * @endcode
 * @endcond
 *
 * 宏的crQUEUE_SEND（）和crQUEUE_RECEIVE（）是与任务使用的xQueueSend（）和xQueueReceive（）函数等效的协例程。
 *
 * crQUEUE_SEND和crQUEUE_RECEIVE只能从协同例程中使用，而xQueueSend（）和xQueueReceive（）只能从任务中使用。
 *
 * crQUEUE_RECEIVE只能从协同例程函数本身调用，而不能从协同例程调用的函数内部调用。这是因为协同例程不维护自己的堆栈。
 *
 * 有关在任务和协同程序之间以及ISR与协同程序之间传递数据的信息，请参阅WEB文档的协同程序部分。
 *
 * @param xHandle 调用协同例程的句柄。这是协同例程函数的xHandle参数。
 *
 * @param pxQueue 将从中接收数据的队列的句柄。当使用xQueueCreate（）API函数创建队列时，获取句柄作为返回值。
 *
 * @param pvBuffer 要将接收的项目复制到的缓冲区。创建队列时指定每个排队项目的字节数。此字节数复制到pvBuffer中。
 *
 * @param xTickToDelay 如果数据不能立即可用，协同例程应阻止等待队列中数据可用的标记数。这相当于的实际时间量由configTICK_RATE_HZ（在FreeRTOSConfig.h中设置）定义。常量portTICK_PERIOD_MS可用于将计时转换为毫秒（请参见crQUEUE_SEND示例）。
 *
 * @param pxResult 如果从队列中成功检索到数据，pxResult指向的变量将设置为pdPASS，否则将设置为ProjDefs.h中定义的错误代码。
 *
 * 示例用法：
 * @code{c}
 * //协同例程从队列中接收要闪烁的LED的数量。它
 * //直到接收到该号码。
 * 静态void prvCoRoutineFlashWorkTask（CoRoutine_t xHandle，UBaseType_t uxIndex）
 * {
 * //如果协例程中的变量必须在阻塞调用中保持值，则必须将其声明为静态。
 * 静态BaseType_t xResult；
 * 静态UBaseType_t uxLEDToFlash；
 *
 *  //所有协同例程都必须以调用crSTART（）开始。
 *  crSTART（xHandle）；
 *
 *  用于（；；）
 *  {
 *      //等待队列中的数据可用。
 *      crQUEUE_RECEIVE（xHandle，xCoRoutineQueue，&uxLEDToFlash，portMAX_DELAY，&xResult）；
 *
 *      如果（xResult==pdPASS）
 *      {
 *          //我们收到了闪烁的LED-闪烁！
 *          vParTestToggleLED（uxLEDToFlash）；
 *      }
 *  }
 *
 *  crEND（）；
 * }
 * @endcode
 * @cond \defgroup crQUEUE_RECEIVE crQUEUE_RECEIVE
 * @endcond \内部组任务
 */
#define crQUEUE_RECEIVE( xHandle, pxQueue, pvBuffer, xTicksToWait, pxResult )           \
    {                                                                                   \
        *( pxResult ) = xQueueCRReceive( ( pxQueue ), ( pvBuffer ), ( xTicksToWait ) ); \
        if( *( pxResult ) == errQUEUE_BLOCKED )                                         \
        {                                                                               \
            crSET_STATE0( ( xHandle ) );                                                \
            *( pxResult ) = xQueueCRReceive( ( pxQueue ), ( pvBuffer ), 0 );            \
        }                                                                               \
        if( *( pxResult ) == errQUEUE_YIELD )                                           \
        {                                                                               \
            crSET_STATE1( ( xHandle ) );                                                \
            *( pxResult ) = pdPASS;                                                     \
        }                                                                               \
    }

/**
 * @cond 面包屑。小时
 * @code{c}
 * 请求_发送_ ROM _ ISR(
 *                          QueueHandle_t pxQueue，
 *                          void*pvItemToQueue，
 *                          BaseType_t xCoRoutine以前的Woken
 *                     )
 * @endcode
 * @endcond
 *
 * 宏的crQUEUE_SEND_FROM_ISR（）和crQUEUE_RECEIVE_FROM_IRS（）是与任务使用的xQueueSendFromISR（）和xQueueReceiveFromISR）函数等效的协例程。
 *
 * crQUEUE_SEND_FROM_ISR（）和crQUEUE_RECEIVE_FROM_IRS（）只能用于在协同例程和ISR之间传递数据，而xQueueSendFromISR（）和xQueueReceiveFromISR）只能用于任务和ISR之间传输数据。
 *
 * crQUEUE_SEND_FROM_ISR只能从ISR调用，以将数据发送到协同例程中正在使用的队列。
 *
 * 有关在任务和协同程序之间以及ISR与协同程序之间传递数据的信息，请参阅WEB文档的协同程序部分。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvItemToQueue 指向要放置在队列中的项目的指针。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从pvItemToQueue复制到队列存储区域。
 *
 * @param xCoRoutinePreviouslyWoken 这包括在内，因此ISR可以从单个中断多次发布到同一队列中。第一个调用应始终以pdFALSE传递。后续调用应传入上一次调用返回的值。
 *
 * @return pdTRUE，如果协同例程被发布到队列中唤醒。ISR使用它来确定ISR之后是否需要上下文切换。
 *
 * 示例用法：
 * @code{c}
 * //在队列中等待接收字符的一种协例程。
 * 静态void vReceivingCoRoutine（CoRoutineHandle_t xHandle，UBaseType_t uxIndex）
 * {
 * 字符cRxedChar；
 * 基本类型_结果；
 *
 *   //所有协同例程都必须以调用crSTART（）开始。
 *   crSTART（xHandle）；
 *
 *   用于（；；）
 *   {
 *       //等待队列中的数据可用。这假设
 *       //队列xCommsRxQueue已创建！
 *       crQUEUE_RECEIVE（xHandle、xCommsRxQueue、&uxLEDToFlash、端口MAX_DELAY、&xResult）；
 *
 *       //收到角色了吗？
 *       如果（xResult==pdPASS）
 *       {
 *           //在此处处理角色。
 *       }
 *   }
 *
 *   //所有协同例程都必须以调用crEND（）结束。
 *   crEND（）；
 * }
 *
 * //一种ISR，使用队列将串行端口上接收的字符发送到
 * //共同程序。
 * 无效vUART_ISR（无效）
 * {
 * 字符cRxedChar；
 * BaseType_t xCRWoken ByPost=pdFALSE；
 *
 *   //我们循环读取字符，直到UART中没有剩余字符。
 *   而（UART_RX_REG_NOT_EMPTY（））
 *   {
 *       //从UART获取字符。
 *       cRxedChar=UART_RX_REG；
 *
 *       //将角色发布到队列中。xCRWokenByPost将为pdFALSE
 *       //第一次循环。如果这篇文章引起了一个共同的程序
 *       //则xCRWokenByPost将设置为pdTRUE。
 *       //通过这种方式，我们可以确保
 *       //在队列中被阻塞，无论如何，只有一个被ISR唤醒
 *       //许多字符被张贴到队列中。
 *       xCRWokenByPost=crQUEUE_SEND_FROM_ISR（xCommsRxQueue，&cRxedChar，xCRWoken ByPost）；
 *   }
 * }
 * @endcode
 * @cond \解组crQUEUE_SEND_FROM_ISR crQUEUE_SEND_FROM_ISR
 * @endcond \内部组任务
 */
#define crQUEUE_SEND_FROM_ISR( pxQueue, pvItemToQueue, xCoRoutinePreviouslyWoken ) \
    xQueueCRSendFromISR( ( pxQueue ), ( pvItemToQueue ), ( xCoRoutinePreviouslyWoken ) )


/**
 * @cond 面包屑。小时
 * @code{c}
 * 请求_发送_ ROM _ ISR(
 *                          QueueHandle_t pxQueue，
 *                          void*pvBuffer，
 *                          基本类型_t*pxCoRoutineWoken
 *                     )
 * @endcode
 * @endcond
 *
 * 宏的crQUEUE_SEND_FROM_ISR（）和crQUEUE_RECEIVE_FROM_IRS（）是与任务使用的xQueueSendFromISR（）和xQueueReceiveFromISR）函数等效的协例程。
 *
 * crQUEUE_SEND_FROM_ISR（）和crQUEUE_RECEIVE_FROM_IRS（）只能用于在协同例程和ISR之间传递数据，而xQueueSendFromISR（）和xQueueReceiveFromISR）只能用于任务和ISR之间传输数据。
 *
 * crQUEUE_RECEIVE_FROM_ISR只能从ISR调用，以从协同例程（发布到队列的协同例程）中使用的队列接收数据。
 *
 * 有关在任务和协同程序之间以及ISR与协同程序之间传递数据的信息，请参阅WEB文档的协同程序部分。
 *
 * @param xQueue 要在其上发布项目的队列的句柄。
 *
 * @param pvBuffer 指向缓冲区的指针，接收到的项目将放置在缓冲区中。队列将保存的项目的大小是在创建队列时定义的，因此这许多字节将从队列复制到pvBuffer中。
 *
 * @param pxCoRoutineWoken 协同例程可能被阻塞，等待队列上的空间变为可用。如果crQUEUE_RECEIVE_FROM_ISR导致这样的协同例程解除阻止，则pxCoRoutineWoken将设置为pdTRUE，否则pxCoRoutineWoken保持不变。
 *
 * @return pdTRUE成功从队列中接收到项目，否则pdFALSE。
 *
 * 示例用法：
 * @code{c}
 * //将一个字符发布到队列，然后阻塞固定
 * //期间。字符每次递增。
 * 静态void vSendingCoRoutine（CoRoutineHandle_t xHandle，UBaseType_t uxIndex）
 * {
 * //当此协同例程被阻止时，char保持其值，因此必须
 * //声明为静态。
 * 静态字符cCharToTx='a'；
 * 基本类型_结果；
 *
 *   //所有协同例程都必须以调用crSTART（）开始。
 *   crSTART（xHandle）；
 *
 *   用于（；；）
 *   {
 *       //将下一个字符发送到队列。
 *       crQUEUE_SEND（xHandle，xCoRoutineQueue，&cCharToTx，NO_DELAY，&xResult）；
 *
 *       如果（xResult==pdPASS）
 *       {
 *           //角色已成功发布到队列。
 *       }
 *       其他的
 *       {
 *          //无法将字符发布到队列。
 *       }
 *
 *       //启用UART Tx中断，以导致此中断
 *       //假设UART。中断将获得字符
 *       //并将其发送。
 *       ENABLE_RX_INTERRUPT();
 *
 *       //递增到下一个字符，然后在固定的时间段内阻塞。
 *       //cHarToTx将在延迟期间保持其值不变
 *       //声明为静态。
 *       cHarToTx++；
 *       如果（cHarToTx>“x”）
 *       {
 *          cHarToTx=“a”；
 *       }
 *       crDELAY（100）；
 *   }
 *
 *   //所有协同例程都必须以调用crEND（）结束。
 *   crEND（）；
 * }
 *
 * //一种ISR，使用队列接收要在UART上发送的字符。
 * 无效vUART_ISR（无效）
 * {
 * 字符cCharToTx；
 * BaseType_t xCRWoken ByPost=pdFALSE；
 *
 *   而（UART_TX_REG_EMPTY（））
 *   {
 *       //队列中是否有等待发送的字符？
 *       //如果协同例程
 *       //被post唤醒-确保只有一个协同例程
 *       //不管我们绕这个循环多少次，都会被唤醒。
 *       如果（crQUEUE_RECEIVE_FROM_ISR（pxQueue，&cCharToTx，&xCRWokenByPost））
 *       {
 *           发送字符（cCharToTx）；
 *       }
 *   }
 * }
 * @endcode
 * @cond \解组crQUEUE_RECEIVE_FROM_ISR
 * @endcond \内部组任务
 */
#define crQUEUE_RECEIVE_FROM_ISR( pxQueue, pvBuffer, pxCoRoutineWoken ) \
    xQueueCRReceiveFromISR( ( pxQueue ), ( pvBuffer ), ( pxCoRoutineWoken ) )

/*
 * 此函数仅用于协同例程宏的内部使用。协同例程实现的宏特性要求原型出现在此处。应用程序编写器不应使用该函数。
 *
 * 从其就绪列表中删除当前协同例程，并将其放置在适当的延迟列表中。
 */
void vCoRoutineAddToDelayedList( TickType_t xTicksToDelay,
                                 List_t * pxEventList );

/*
 * 此函数仅供队列实现内部使用。应用程序编写器不应使用该函数。
 *
 * 从事件列表中删除最高优先级的协同例程，并将其放置在挂起就绪列表中。
 */
BaseType_t xCoRoutineRemoveFromEventList( const List_t * pxEventList );

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* CO_ROUTINE_H */

