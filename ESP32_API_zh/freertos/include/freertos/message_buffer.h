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


/*
 * 消息缓冲区在FreeRTOS流缓冲区之上构建功能。流缓冲区用于从一个任务或中断向另一个任务发送连续的数据流，而消息缓冲区用于将可变长度的离散消息从一个或中断发送到另一个。它们的实现很轻，特别适合任务中断和核心到核心通信场景。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须将对编写API函数（如xMessageBufferSend（））的每个调用置于关键部分内，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须将对读取API函数（如xMessageBufferRead（））的每次调用置于关键部分内，并将接收超时设置为0。
 *
 * 消息缓冲区保存可变长度的消息。为了实现这一点，当将消息写入消息缓冲区时，还会写入一个额外的sizeof（size_t）字节来存储消息的长度（这在内部发生，使用API函数）。sizeof（size_t）在32位体系结构上通常为4字节，因此将10字节的消息写入32位体系架构上的消息缓冲区实际上会将消息缓冲区中的可用空间减少14字节（消息使用10字节，4字节用于保存消息长度）。
 */

#ifndef FREERTOS_MESSAGE_BUFFER_H
#define FREERTOS_MESSAGE_BUFFER_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h must appear in source files before include message_buffer.h"
#endif

/* 消息缓冲区构建在流缓冲区之上。*/
#include "stream_buffer.h"

/* *INDENT-OFF* */
#if defined( __cplusplus )
    extern "C" {
#endif
/* *INDENT-ON* */

/**
 * 引用消息缓冲区的类型。例如，对xMessageBufferCreate（）的调用返回一个MessageBufferHandle_t变量，然后该变量可以用作xMessageBufferSend（）、xMessageBufferReceive（）等的参数。
 */
typedef void * MessageBufferHandle_t;

/*-----------------------------------------------------------*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * MessageBufferHandle_t xMessageBufferCreate（size_t xBufferSizeBytes）；
 * @endcode
 * @endcond
 *
 * 使用动态分配的内存创建新的消息缓冲区。有关使用静态分配内存（编译时分配的内存）的版本，请参阅xMessageBufferCreateStatic（）。
 *
 * configSUPPORT_DYNAMIC_ALLOCATION必须设置为1或在FreeRTOSConfig.h中未定义，以便xMessageBufferCreate（）可用。
 *
 * @param xBufferSizeBytes 消息缓冲区在任何时间都可以容纳的字节总数（不是消息）。当将消息写入消息缓冲区时，还会写入一个额外的sizeof（size_t）字节来存储消息的长度。sizeof（sizet）在32位架构上通常为4字节，因此在大多数32位架构中，10字节的消息将占用14字节的消息缓冲区空间。
 *
 * @return 如果返回NULL，则无法创建消息缓冲区，因为没有足够的堆内存可供FreeRTOS分配消息缓冲区数据结构和存储区域。返回的非NULL值表示消息缓冲区已成功创建-返回的值应存储为创建的消息缓冲区的句柄。
 *
 * 示例用法：
 * @code{c}
 *
 * void vA函数（void）
 * {
 * MessageBufferHandle_t xMessageBuffer；
 * const size_t xMessageBufferSizeBytes=100；
 *
 *  //创建一个可容纳100字节的消息缓冲区。用于保存的内存
 *  //消息缓冲区结构和消息本身都被分配
 *  //动态地。添加到缓冲区的每条消息将额外消耗4
 *  //用于保存消息长度的字节。
 *  xMessageBuffer=xMessageBufferCreate（xMessageBufferSizeBytes）；
 *
 *  如果（xMessageBuffer==NULL）
 *  {
 *      //没有足够的堆内存空间来创建
 *      //消息缓冲区。
 *  }
 *  其他的
 *  {
 *      //消息缓冲区已成功创建，现在可以使用。
 *  }
 *
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferCreate xMessageBuffer创建
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferCreate( xBufferSizeBytes ) \
    ( MessageBufferHandle_t ) xStreamBufferGenericCreate( xBufferSizeBytes, ( size_t ) 0, pdTRUE )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * MessageBufferHandle_t xMessageBufferCreateStatic（size_t xBufferSizeBytes，
 *                                                uint8_t*pucMessageBufferStorageArea，
 *                                                静态消息缓冲区_t*pxStaticMessageBuffer）；
 * @endcode
 * @endcond 使用静态分配的内存创建新的消息缓冲区。有关使用动态分配内存的版本，请参阅xMessageBufferCreate（）。
 *
 * @param xBufferSizeBytes pucMessageBufferStorageArea参数指向的缓冲区的大小（以字节为单位）。当将消息写入消息缓冲区时，还会写入一个额外的sizeof（size_t）字节来存储消息的长度。sizeof（sizet）在32位架构上通常为4字节，因此在大多数32位架构中，10字节的消息将占用14字节的消息缓冲区空间。消息缓冲区中可存储的最大字节数实际上是（xBufferSizeBytes-1）。
 *
 * @param pucMessageBufferStorageArea 必须指向至少xBufferSizeBytes+1大的uint8_t数组。这是将消息写入消息缓冲区时将消息复制到的数组。
 *
 * @param pxStaticMessageBuffer 必须指向StaticMessageBuffer_t类型的变量，该变量将用于保存消息缓冲区的数据结构。
 *
 * @return 如果成功创建了消息缓冲区，则返回创建的消息缓冲区的句柄。如果pucMessageBufferStorageArea或pxStaticmessageBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 *
 * //用于标注用于保存消息的数组。可用空间
 * //实际上会比这个少一个，所以999。
 * #定义STORAGE_SIZE_BYTES 1000
 *
 * //定义将在消息中实际保存消息的内存
 * //缓冲区。
 * 静态uint8_t ucStorageBuffer[STORAGE_SIZE_BYTES]；
 *
 * //用于保存消息缓冲区结构的变量。
 * StaticMessageBuffer_t xMessageBufferStruct；
 *
 * void MyFunction（void）
 * {
 * MessageBufferHandle_t xMessageBuffer；
 *
 *  xMessageBuffer=xMessageBufferCreateStatic（sizeof（ucBufferStorage），
 *                                               ucBufferStorage，
 *                                               &xMessageBufferStruct）；
 *
 *  //作为pucMessageBufferStorageArea或pxStaticMessageBuffer
 *  //参数为NULL，xMessageBuffer将不为NULL，可以用于
 *  //在其他消息缓冲区API调用中引用创建的消息缓冲区。
 *
 *  //使用消息缓冲区的其他代码可以转到此处。
 * }
 *
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferCreateStatic xMessageBufferCreate静态
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferCreateStatic( xBufferSizeBytes, pucMessageBufferStorageArea, pxStaticMessageBuffer ) \
    ( MessageBufferHandle_t ) xStreamBufferGenericCreateStatic( xBufferSizeBytes, 0, pdTRUE, pucMessageBufferStorageArea, pxStaticMessageBuffer )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * size_t xMessageBufferSend（MessageBufferHandle_t xMessage Buffer，
 *                         const void*pvTxData，
 *                         size_t xDataLengthBytes，
 *                         TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 向消息缓冲区发送离散消息。消息可以是缓冲区可用空间内的任何长度，并复制到缓冲区中。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须将对编写API函数（如xMessageBufferSend（））的每个调用置于关键部分内，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须将对读取API函数（如xMessageBufferRead（））的每次调用置于关键部分内，并将接收块时间设置为0。
 *
 * 使用xMessageBufferSend（）从任务写入消息缓冲区。使用xMessageBufferSendFromISR（）从中断服务例程（ISR）写入消息缓冲区。
 *
 * @param xMessageBuffer 消息要发送到的消息缓冲区的句柄。
 *
 * @param pvTxData 指向要复制到消息缓冲区的消息的指针。
 *
 * @param xDataLengthBytes 消息的长度。即，从pvTxData复制到消息缓冲区的字节数。当将消息写入消息缓冲区时，还会写入一个额外的sizeof（size_t）字节来存储消息的长度。sizeof（size_t）在32位架构上通常为4字节，因此在大多数32位架构中，将xDataLengthBytes设置为20将使消息缓冲区中的可用空间减少24字节（20字节的消息数据和4字节的消息长度）。
 *
 * @param xTicksToWait 如果调用xMessageBufferSend（）时消息缓冲区的空间不足，则调用任务应保持在Blocked状态以等待消息缓冲区中有足够的空间可用的最长时间。如果xTicksToWait为零，则调用任务永远不会阻塞。块时间以刻度周期指定，因此它表示的绝对时间取决于刻度频率。宏pdMS_TO_TICKS（）可用于将以毫秒为单位指定的时间转换为以刻度为单位的时间。如果在FreeRTOSConfig.h中将INCLUDE_vTaskSuspend设置为1，则将xTicksToWait设置为portMAX_DELAY将导致任务无限期等待（不超时）。当任务处于“阻止”状态时，任务不使用任何CPU时间。
 *
 * @return 写入消息缓冲区的字节数。如果对xMessageBufferSend（）的调用在有足够的空间将消息写入消息缓冲区之前超时，则返回零。如果调用未超时，则返回xDataLengthBytes。
 *
 * 示例用法：
 * @code{c}
 * void vAFunction（MessageBufferHandle_t xMessageBuffer）
 * {
 * size_t x字节发送；
 * uint8_t ucArrayToSend[]=｛0，1，2，3｝；
 * char*pcStringToSend=“要发送的字符串”；
 * 常量TickType_t x100ms=pdMS_TO_TICKS（100）；
 *
 *  //将数组发送到消息缓冲区，最多阻止100ms
 *  //等待消息缓冲区中有足够的可用空间。
 *  xBytesSsent=xMessageBufferSend（xMessageBuffer，（void*）ucArrayToSend，sizeof（ucArrayTeSend），x100ms）；
 *
 *  如果（xBytesSent！=sizeof（ucArrayToSend））
 *  {
 *      //对xMessageBufferSend（）的调用在足够的时间之前超时
 *      //缓冲区中用于写入数据的空间。
 *  }
 *
 *  //将字符串发送到消息缓冲区。如果有，立即返回
 *  //缓冲区中没有足够的空间。
 *  xBytesSsent=xMessageBufferSend（xMessageBuffer，（void*）pcStringToSend，strlen（pcStringToSend），0）；
 *
 *  if（xBytesSent！=strlen（pcStringToSend））
 *  {
 *      //无法将字符串添加到消息缓冲区，因为存在
 *      //缓冲区中没有足够的可用空间。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferSend xMessageBufferSend
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferSend( xMessageBuffer, pvTxData, xDataLengthBytes, xTicksToWait ) \
    xStreamBufferSend( ( StreamBufferHandle_t ) xMessageBuffer, pvTxData, xDataLengthBytes, xTicksToWait )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * size_t xMessageBufferSendFromISR（MessageBufferHandle_t xMessage Buffer，
 *                                const void*pvTxData，
 *                                size_t xDataLengthBytes，
 *                                BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 向消息缓冲区发送离散消息的API函数的中断安全版本。消息可以是缓冲区可用空间内的任何长度，并复制到缓冲区中。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须将对编写API函数（如xMessageBufferSend（））的每个调用置于关键部分内，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须将对读取API函数（如xMessageBufferRead（））的每次调用置于关键部分内，并将接收块时间设置为0。
 *
 * 使用xMessageBufferSend（）从任务写入消息缓冲区。使用xMessageBufferSendFromISR（）从中断服务例程（ISR）写入消息缓冲区。
 *
 * @param xMessageBuffer 消息要发送到的消息缓冲区的句柄。
 *
 * @param pvTxData 指向要复制到消息缓冲区的消息的指针。
 *
 * @param xDataLengthBytes 消息的长度。即，从pvTxData复制到消息缓冲区的字节数。当将消息写入消息缓冲区时，还会写入一个额外的sizeof（size_t）字节来存储消息的长度。sizeof（size_t）在32位架构上通常为4字节，因此在大多数32位架构中，将xDataLengthBytes设置为20将使消息缓冲区中的可用空间减少24字节（20字节的消息数据和4字节的消息长度）。
 *
 * @param pxHigherPriorityTaskWoken  消息缓冲区可能会有一个任务被阻塞，等待数据。调用xMessageBufferSendFromISR（）可以使数据可用，从而导致正在等待数据的任务离开“阻止”状态。如果调用xMessageBufferSendFromISR（）导致任务离开“阻止”状态，并且未阻止的任务的优先级高于当前正在执行的任务（被中断的任务），则在内部，xMMessageBufferSendFromisR（）将pxHigherPriorityTaskWoken设置为pdTRUE。如果xMessageBufferSendFromISR（）将此值设置为pdTRUE，则通常应在中断退出之前执行上下文切换。这将确保中断直接返回到最高优先级的就绪状态任务。pxHigherPriorityTaskWoken在传递到函数之前应设置为pdFALSE。有关示例，请参见下面的代码示例。
 *
 * @return 实际写入消息缓冲区的字节数。如果消息缓冲区没有足够的可用空间来存储消息，则返回0，否则返回xDataLengthBytes。
 *
 * 示例用法：
 * @code{c}
 * //已创建的消息缓冲区。
 * MessageBufferHandle_t xMessageBuffer；
 *
 * void vAn中断服务例程（void）
 * {
 * size_t x字节发送；
 * char*pcStringToSend=“要发送的字符串”；
 * BaseType_t xHigherPriorityTaskWoken=pdFALSE；//初始化为pdFALSE。
 *
 *  //尝试将字符串发送到消息缓冲区。
 *  xBytesSsent=xMessageBufferSendFromISR（xMessageBuffer，
 *                                          （void*）pcStringToSend，
 *                                          strlen（pcStringToSend），
 *                                          &xHigherPriorityTaskWoken）；
 *
 *  if（xBytesSent！=strlen（pcStringToSend））
 *  {
 *      //无法将字符串添加到消息缓冲区，因为存在
 *      //缓冲区中没有足够的可用空间。
 *  }
 *
 *  //如果xHigherPriorityTaskWoken在内部设置为pdTRUE
 *  //xMessageBufferSendFromISR（），然后是优先级高于
 *  //当前正在执行的任务的优先级已取消阻止，并且上下文
 *  //应执行切换以确保ISR返回到未阻塞状态
 *  //任务。在大多数FreeRTOS端口中，这是通过简单地传递
 *  //xHigherPriorityTaskWoken插入端口YIELD_FROM_ISR（），该端口将测试
 *  //变量值，并在必要时执行上下文切换。检查
 *  //用于端口特定指令的端口文档。
 *  端口YIELD_FROM_ISR（xHigherPriorityTaskWoken）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferSendFromISR xMessageBufferSend FromISR
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferSendFromISR( xMessageBuffer, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken ) \
    xStreamBufferSendFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * size_t xMessageBufferReceive（MessageBufferHandle_t xMessage Buffer，
 *                            void*pvRxData，
 *                            size_t xBufferLengthBytes，
 *                            TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 从消息缓冲区接收离散消息。消息可以是可变长度的，并从缓冲区中复制出来。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须将对编写API函数（如xMessageBufferSend（））的每个调用置于关键部分内，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须将对读取API函数（如xMessageBufferRead（））的每次调用置于关键部分内，并将接收块时间设置为0。
 *
 * 使用xMessageBufferReceive（）从任务中读取消息缓冲区。使用xMessageBufferReceiveFromISR（）从中断服务例程（ISR）中读取消息缓冲区。
 *
 * @param xMessageBuffer 从中接收消息的消息缓冲区的句柄。
 *
 * @param pvRxData 指向要将接收到的消息复制到其中的缓冲区的指针。
 *
 * @param xBufferLengthBytes pvRxData参数指向的缓冲区长度。这将设置可以接收的消息的最大长度。如果xBufferLengthBytes太小，无法容纳下一条消息，则消息将留在消息缓冲区中，并返回0。
 *
 * @param xTicksToWait 如果消息缓冲区为空，任务应保持在“阻止”状态以等待消息的最长时间。如果xTicksToWait为零且消息缓冲区为空，则xMessageBufferReceive（）将立即返回。块时间以刻度周期指定，因此它表示的绝对时间取决于刻度频率。宏pdMS_TO_TICKS（）可用于将以毫秒为单位指定的时间转换为以刻度为单位的时间。如果在FreeRTOSConfig.h中将INCLUDE_vTaskSuspend设置为1，则将xTicksToWait设置为portMAX_DELAY将导致任务无限期等待（不超时）。当任务处于“阻止”状态时，任务不使用任何CPU时间。
 *
 * @return 从消息缓冲区读取的消息的长度（以字节为单位）（如果有）。如果xMessageBufferReceive（）在消息可用之前超时，则返回零。如果消息长度大于xBufferLengthBytes，则消息将保留在消息缓冲区中，并返回零。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（MessageBuffer_t xMessageBuffer）
 * {
 * uint8_t ucRxData[20]；
 * size_t x接收字节；
 * const TickType_t xBlockTime=pdMS_TO_TICKS（20）；
 *
 *  //从消息缓冲区接收下一条消息。在封锁区等待
 *  //状态（因此不使用任何CPU处理时间）最长为100ms
 *  //消息变得可用。
 *  xReceivedBytes＝xMessageBufferReceive（xMessageBuffer，
 *                                          （void*）ucRxData，
 *                                          sizeof（ucRxData），
 *                                          xBlockTime）；
 *
 *  如果（xReceivedBytes>0）
 *  {
 *      //ucRxData包含长度为xReceivedBytes的消息。过程
 *      //这里的信息。。。。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferReceive xMessageBuffer接收
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferReceive( xMessageBuffer, pvRxData, xBufferLengthBytes, xTicksToWait ) \
    xStreamBufferReceive( ( StreamBufferHandle_t ) xMessageBuffer, pvRxData, xBufferLengthBytes, xTicksToWait )


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * size_t xMessageBufferReceiveFromISR（MessageBufferHandle_t xMessage Buffer，
 *                                   void*pvRxData，
 *                                   size_t xBufferLengthBytes，
 *                                   BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 从消息缓冲区接收离散消息的API函数的中断安全版本。消息可以是可变长度的，并从缓冲区中复制出来。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须将对编写API函数（如xMessageBufferSend（））的每个调用置于关键部分内，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须将对读取API函数（如xMessageBufferRead（））的每次调用置于关键部分内，并将接收块时间设置为0。
 *
 * 使用xMessageBufferReceive（）从任务中读取消息缓冲区。使用xMessageBufferReceiveFromISR（）从中断服务例程（ISR）中读取消息缓冲区。
 *
 * @param xMessageBuffer 从中接收消息的消息缓冲区的句柄。
 *
 * @param pvRxData 指向要将接收到的消息复制到其中的缓冲区的指针。
 *
 * @param xBufferLengthBytes pvRxData参数指向的缓冲区长度。这将设置可以接收的消息的最大长度。如果xBufferLengthBytes太小，无法容纳下一条消息，则消息将留在消息缓冲区中，并返回0。
 *
 * @param pxHigherPriorityTaskWoken  消息缓冲区可能会有一个任务被阻塞，等待空间变为可用。调用xMessageBufferReceiveFromISR（）可以使空间可用，从而使等待空间的任务离开“阻止”状态。如果调用xMessageBufferReceiveFromISR（）导致任务离开“阻止”状态，并且未阻止的任务的优先级高于当前正在执行的任务（被中断的任务），则在内部，xMessageBufferReceiveFromISR（）将pxHigherPriorityTaskWoken设置为pdTRUE。如果xMessageBufferReceiveFromISR（）将此值设置为pdTRUE，则通常应在中断退出之前执行上下文切换。这将确保中断直接返回到最高优先级的就绪状态任务。pxHigherPriorityTaskWoken在传递到函数之前应设置为pdFALSE。有关示例，请参见下面的代码示例。
 *
 * @return 从消息缓冲区读取的消息的长度（以字节为单位）（如果有）。
 *
 * 示例用法：
 * @code{c}
 * //已创建的消息缓冲区。
 * MessageBuffer_t xMessageBuffer；
 *
 * void vAn中断服务例程（void）
 * {
 * uint8_t ucRxData[20]；
 * size_t x接收字节；
 * BaseType_t xHigherPriorityTaskWoken=pdFALSE；//初始化为pdFALSE。
 *
 *  //从消息缓冲区接收下一条消息。
 *  xReceivedBytes＝xMessageBufferReceiveFromISR（xMessageBuffer，
 *                                                （void*）ucRxData，
 *                                                sizeof（ucRxData），
 *                                                &xHigherPriorityTaskWoken）；
 *
 *  如果（xReceivedBytes>0）
 *  {
 *      //ucRxData包含长度为xReceivedBytes的消息。过程
 *      //这里的信息。。。。
 *  }
 *
 *  //如果xHigherPriorityTaskWoken在内部设置为pdTRUE
 *  //xMessageBufferReceiveFromISR（），然后是优先级高于
 *  //当前正在执行的任务的优先级已取消阻止，并且上下文
 *  //应执行切换以确保ISR返回到未阻塞状态
 *  //任务。在大多数FreeRTOS端口中，这是通过简单地传递
 *  //xHigherPriorityTaskWoken插入端口YIELD_FROM_ISR（），该端口将测试
 *  //变量值，并在必要时执行上下文切换。检查
 *  //用于端口特定指令的端口文档。
 *  端口YIELD_FROM_ISR（xHigherPriorityTaskWoken）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferReceiveFromISR xMessageBufferReceiveFromISR
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferReceiveFromISR( xMessageBuffer, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken ) \
    xStreamBufferReceiveFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * void vMessageBufferDelete（MessageBufferHandle_t xMessageBuffer）；
 * @endcode
 * @endcond
 *
 * 删除以前使用调用xMessageBufferCreate（）或xMessageBufferCreateStatic（）创建的消息缓冲区。如果消息缓冲区是使用动态内存创建的（即，通过xMessageBufferCreate（）），则释放分配的内存。
 *
 * 删除消息缓冲区后，不得使用消息缓冲区句柄。
 *
 * @param xMessageBuffer 要删除的消息缓冲区的句柄。
 *
 */
#define vMessageBufferDelete( xMessageBuffer ) \
    vStreamBufferDelete( ( StreamBufferHandle_t ) xMessageBuffer )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 * @code{c}
 * BaseType_t xMessageBufferIsFull（MessageBufferHandle_t xMessageBuffer））；
 * @endcode
 * @endcond
 *
 * 测试消息缓冲区是否已满。如果消息缓冲区不能再接收任何大小的消息，则该消息缓冲区已满，直到从消息缓冲区中删除的消息释放出可用空间。
 *
 * @param xMessageBuffer 正在查询的消息缓冲区的句柄。
 *
 * @return 如果xMessageBuffer引用的消息缓冲区已满，则返回pdTRUE。否则将返回pdFALSE。
 */
#define xMessageBufferIsFull( xMessageBuffer ) \
    xStreamBufferIsFull( ( StreamBufferHandle_t ) xMessageBuffer )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 * @code{c}
 * BaseType_t xMessageBufferIsEmpty（MessageBufferHandle_t xMessageBuffer））；
 * @endcode
 * @endcond
 *
 * 测试消息缓冲区是否为空（不包含任何消息）。
 *
 * @param xMessageBuffer 正在查询的消息缓冲区的句柄。
 *
 * @return 如果xMessageBuffer引用的消息缓冲区为空，则返回pdTRUE。否则将返回pdFALSE。
 *
 */
#define xMessageBufferIsEmpty( xMessageBuffer ) \
    xStreamBufferIsEmpty( ( StreamBufferHandle_t ) xMessageBuffer )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 * @code{c}
 * BaseType_t xMessageBufferReset（MessageBufferHandle_t xMessage Buffer）；
 * @endcode
 * @endcond
 *
 * 将消息缓冲区重置为其初始空状态，丢弃其中包含的任何消息。
 *
 * 只有在没有任务被阻止时，才能重置消息缓冲区。
 *
 * @param xMessageBuffer 正在重置的消息缓冲区的句柄。
 *
 * @return 如果消息缓冲区已重置，则返回pdPASS。如果消息缓冲区无法重置，因为消息队列上有一个任务被阻止以等待空间变为可用，或者等待消息变为可用的，则返回pdFAIL。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferReset xMessageBuffer重置
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferReset( xMessageBuffer ) \
    xStreamBufferReset( ( StreamBufferHandle_t ) xMessageBuffer )


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 * @code{c}
 * size_t xMessageBufferSpaceAvailable（MessageBufferHandle_t xMessage Buffer））；
 * @endcode
 * @endcond
 *
 * 返回消息缓冲区中可用空间的字节数。
 *
 * @param xMessageBuffer 正在查询的消息缓冲区的句柄。
 *
 * @return 在消息缓冲区满之前可以写入消息缓冲区的字节数。当将消息写入消息缓冲区时，还会写入一个额外的sizeof（size_t）字节来存储消息的长度。sizeof（size_t）在32位体系结构上通常为4字节，因此如果xMessageBufferSpacesAvailable（）返回10，则可以写入消息缓冲区的最大消息的大小为6字节。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferSpaceAvailable xMessageBufferSpace Available
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferSpaceAvailable( xMessageBuffer ) \
    xStreamBufferSpacesAvailable( ( StreamBufferHandle_t ) xMessageBuffer )
#define xMessageBufferSpacesAvailable( xMessageBuffer ) \
    xStreamBufferSpacesAvailable( ( StreamBufferHandle_t ) xMessageBuffer ) /* 更正了原始宏名称中的拼写错误。*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 * @code{c}
 * size_t xMessageBufferNextLengthBytes（MessageBufferHandle_t xMessageBuffer））；
 * @endcode
 * @endcond
 *
 * 返回消息缓冲区中下一条消息的长度（以字节为单位）。如果xMessageBufferReceive（）返回0，则很有用，因为传递到xMessageBufferReceive（）的缓冲区太小，无法容纳下一条消息。
 *
 * @param xMessageBuffer 正在查询的消息缓冲区的句柄。
 *
 * @return 消息缓冲区中下一条消息的长度（字节），如果消息缓冲区为空，则为0。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferNextRengthBytes xMessageBufferNext LengthBytes
 * @endcond \内部组消息缓冲管理
 */
#define xMessageBufferNextLengthBytes( xMessageBuffer ) \
    xStreamBufferNextMessageLengthBytes( ( StreamBufferHandle_t ) xMessageBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * BaseType_t xMessageBufferSendCompletedFromISR（MessageBufferHandle_t xStreamBuffer，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 仅限高级用户。
 *
 * 当数据被发送到消息缓冲区或流缓冲区时，sbSEND_COMPLETE（）宏将从FreeRTOS API中调用。如果有一个任务在消息或流缓冲区上被阻止，等待数据到达，则sbSEND_COMPLETE（）宏会向该任务发送通知，将其从“阻止”状态中删除。xMessageBufferSendCompletedFromISR（）执行相同的操作。它是为了使应用程序编写者能够实现自己版本的sbSEND_COMPLETED（），并且在任何其他时间都不得使用。
 *
 * 请参阅FreeRTOS/Demo/Minimal/MessageBufferAMP中实现的示例。c获取更多信息。
 *
 * @param xMessageBuffer 写入数据的流缓冲区的句柄。
 *
 * @param pxHigherPriorityTaskWoken *pxHigherPriorityTaskWoken应在传递到xMessageBufferSendCompletedFromISR（）之前初始化为pdFALSE。如果调用xMessageBufferSendCompletedFromISR（）将任务从Blocked状态移除，并且该任务的优先级高于当前运行任务的优先级，则pxHigherPriorityTaskWoken将设置为pdTRUE，指示在退出ISR之前应执行上下文切换。
 *
 * @return 如果任务已从“阻止”状态删除，则返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferSendCompletedFromISR xMessageBufferSend CompletedFrom ISR
 * @endcond \ingroup流缓冲管理
 */
#define xMessageBufferSendCompletedFromISR( xMessageBuffer, pxHigherPriorityTaskWoken ) \
    xStreamBufferSendCompletedFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pxHigherPriorityTaskWoken )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * BaseType_t xMessageBufferReceiveCompletedFromISR（MessageBufferHandle_t xStreamBuffer，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 仅限高级用户。
 *
 * 当从消息缓冲区或流缓冲区中读取数据时，从FreeRTOS API中调用sbRECEIVE_COMPLETED（）宏。如果有一个任务在消息或流缓冲区上被阻止，等待数据到达，则sbRECEIVE_COMPLETED（）宏会向该任务发送通知，将其从“阻止”状态中删除。xMessageBufferReceiveCompletedFromISR（）执行相同的操作。它是为了使应用程序编写者能够实现自己版本的sbRECEIVE_COMPLETED（），并且在任何其他时间都不得使用。
 *
 * 请参阅FreeRTOS/Demo/Minimal/MessageBufferAMP中实现的示例。c获取更多信息。
 *
 * @param xMessageBuffer 从中读取数据的流缓冲区的句柄。
 *
 * @param pxHigherPriorityTaskWoken *pxHigherPriorityTaskWoken应在传递到xMessageBufferReceiveCompletedFromISR（）之前初始化为pdFALSE。如果调用xMessageBufferReceiveCompletedFromISR（）将任务从Blocked状态移除，并且该任务的优先级高于当前运行任务的优先级，则pxHigherPriorityTaskWoken将设置为pdTRUE，指示在退出ISR之前应执行上下文切换。
 *
 * @return 如果任务已从“阻止”状态删除，则返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xMessageBufferReceiveCompletedFromISR xMessageBuffer接收完成FromISR
 * @endcond \ingroup流缓冲管理
 */
#define xMessageBufferReceiveCompletedFromISR( xMessageBuffer, pxHigherPriorityTaskWoken ) \
    xStreamBufferReceiveCompletedFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pxHigherPriorityTaskWoken )

/* *INDENT-OFF* */
#if defined( __cplusplus )
    } /* 外部“C”*/
#endif
/* *INDENT-ON* */

#endif /* !已定义（FREERTOS_MESSAGE_BUFFER_H）*/

