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

/*
 * 流缓冲区用于从一个任务或中断向另一个任务发送连续的数据流。它们的实现很轻，特别适合任务中断和核心到核心通信场景。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须在关键部分内对编写API函数（如xStreamBufferSend（））进行每次调用，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须在关键部分部分内对读取API函数（如xStreamBufferReceive（））进行每次调用，并将接收块时间设置为0。
 *
 */

#ifndef STREAM_BUFFER_H
#define STREAM_BUFFER_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h must appear in source files before include stream_buffer.h"
#endif

/* *INDENT-OFF* */
#if defined( __cplusplus )
    extern "C" {
#endif
/* *INDENT-ON* */

/**
 * 引用流缓冲区的类型。例如，对xStreamBufferCreate（）的调用返回一个StreamBufferHandle_t变量，该变量可以用作xStreamBufferSend（）、xStreamBufferReceive（）等的参数。
 */
struct StreamBufferDef_t;
typedef struct StreamBufferDef_t * StreamBufferHandle_t;


/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION消息缓冲区.h
 *
 * @code{c}
 * StreamBufferHandle_t xStreamBufferCreate（size_t xBufferSizeBytes，size_t x TriggerLevelBytes）；
 * @endcode
 * @endcond
 *
 * 使用动态分配的内存创建新的流缓冲区。有关使用静态分配内存（编译时分配的内存）的版本，请参阅xStreamBufferCreateStatic（）。
 *
 * configSUPPORT_DYNAMIC_ALLOCATION必须设置为1或在FreeRTOSConfig中未定义。h表示xStreamBufferCreate（）可用。
 *
 * @param xBufferSizeBytes 流缓冲区在任何时间都可以容纳的字节总数。
 *
 * @param xTriggerLevelBytes 在流缓冲区上被阻止以等待数据的任务移出阻止状态之前，流缓冲区中必须包含的字节数。例如，如果任务在读取触发级别为1的空流缓冲区时被阻止，则当单个字节写入缓冲区或任务的阻止时间到期时，该任务将被取消阻止。作为另一个示例，如果任务在读取具有10的触发级别的空流缓冲区时被阻止，则在流缓冲区包含至少10个字节或任务的阻止时间到期之前，该任务将不会被阻止。如果读取任务的块时间在达到触发级别之前过期，则无论实际有多少字节可用，该任务仍将接收。将触发级别设置为0将导致使用触发级别1。指定大于缓冲区大小的触发器级别无效。
 *
 * @return 如果返回NULL，则无法创建流缓冲区，因为没有足够的堆内存可供FreeRTOS分配流缓冲区数据结构和存储区域。返回的非NULL值表示已成功创建流缓冲区-返回的值应存储为创建的流缓冲区的句柄。
 *
 * 示例用法：
 * @code{c}
 *
 * void vA函数（void）
 * {
 * StreamBufferHandle_t xStreamBuffer；
 * const size_t xStreamBufferSizeBytes=100，xTriggerLevel=10；
 *
 *  //创建可容纳100字节的流缓冲区。用于保存的内存
 *  //流缓冲区结构和流缓冲区中的数据都是
 *  //动态分配。
 *  xStreamBuffer=xStreamBufferCreate（xStreamBufferSizeBytes，xTriggerLevel）；
 *
 *  如果（xStreamBuffer==NULL）
 *  {
 *      //没有足够的堆内存空间来创建
 *      //流缓冲区。
 *  }
 *  其他的
 *  {
 *      //流缓冲区已成功创建，现在可以使用。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferCreate xStreamBuffer创建
 * @endcond \ingroup流缓冲管理
 */
#define xStreamBufferCreate( xBufferSizeBytes, xTriggerLevelBytes )    xStreamBufferGenericCreate( xBufferSizeBytes, xTriggerLevelBytes, pdFALSE )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * StreamBufferHandle_t xStreamBufferCreateStatic（size_t xBufferSizeBytes，
 *                                              size_t xTriggerLevelBytes，
 *                                              uint8_t*pucStreamBufferStorageArea，
 *                                              StaticStreamBuffer_t*pxStaticStreamPuffer）；
 * @endcode
 * @endcond
 *
 * 使用静态分配的内存创建新的流缓冲区。有关使用动态分配内存的版本，请参阅xStreamBufferCreate（）。
 *
 * 在FreeRTOSConfig中，configSUPPORT_STATIC_ALLOCATION必须设置为1。h表示xStreamBufferCreateStatic（）可用。
 *
 * @param xBufferSizeBytes pucStreamBufferStorageArea参数指向的缓冲区的大小（以字节为单位）。
 *
 * @param xTriggerLevelBytes 在流缓冲区上被阻止以等待数据的任务移出阻止状态之前，流缓冲区中必须包含的字节数。例如，如果任务在读取触发级别为1的空流缓冲区时被阻止，则当单个字节写入缓冲区或任务的阻止时间到期时，该任务将被取消阻止。作为另一个示例，如果任务在读取具有10的触发级别的空流缓冲区时被阻止，则在流缓冲区包含至少10个字节或任务的阻止时间到期之前，该任务将不会被阻止。如果读取任务的块时间在达到触发级别之前过期，则无论实际有多少字节可用，该任务仍将接收。将触发级别设置为0将导致使用触发级别1。指定大于缓冲区大小的触发器级别无效。
 *
 * @param pucStreamBufferStorageArea 必须指向至少xBufferSizeBytes+1大的uint8_t数组。这是将流写入流缓冲区时将其复制到的数组。
 *
 * @param pxStaticStreamBuffer 必须指向StaticStreamBuffer_t类型的变量，该变量将用于保存流缓冲区的数据结构。
 *
 * @return 如果成功创建了流缓冲区，则返回创建的流缓冲区的句柄。如果pucStreamBufferStorageArea或pxStaticstreamBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 *
 * //用于标注用于保存流的数组。可用空间
 * //实际上会比这个少一个，所以999。
 * #定义STORAGE_SIZE_BYTES 1000
 *
 * //定义将在流中实际保存流的内存
 * //缓冲区。
 * 静态uint8_t ucStorageBuffer[STORAGE_SIZE_BYTES]；
 *
 * //用于保存流缓冲区结构的变量。
 * StaticStreamBuffer_t xStreamBufferStruct；
 *
 * void MyFunction（void）
 * {
 * StreamBufferHandle_t xStreamBuffer；
 * const size_t xTriggerLevel=1；
 *
 *  xStreamBuffer=xStreamBufferCreateStatic（sizeof（ucBufferStorage），
 *                                             xTriggerLevel，
 *                                             ucBufferStorage，
 *                                             &xStreamBufferStruct）；
 *
 *  //作为pucStreamBufferStorageArea或pxStaticStreamBuffer
 *  //参数为NULL，xStreamBuffer将不为NULL，可以用于
 *  //在其他流缓冲区API调用中引用创建的流缓冲区。
 *
 *  //使用流缓冲区的其他代码可以转到此处。
 * }
 *
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferCreateStatic xStreamBufferCreate静态
 * @endcond \ingroup流缓冲管理
 */
#define xStreamBufferCreateStatic( xBufferSizeBytes, xTriggerLevelBytes, pucStreamBufferStorageArea, pxStaticStreamBuffer ) \
    xStreamBufferGenericCreateStatic( xBufferSizeBytes, xTriggerLevelBytes, pdFALSE, pucStreamBufferStorageArea, pxStaticStreamBuffer )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * size_ t xStreamBufferSend（StreamBufferHandle_t xStreamBuffer，
 *                        const void*pvTxData，
 *                        size_t xDataLengthBytes，
 *                        TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 将字节发送到流缓冲区。字节被复制到流缓冲区。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须在关键部分内对编写API函数（如xStreamBufferSend（））进行每次调用，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须在关键部分内对读取API函数（如xStreamBufferReceive（））进行每次调用，并将接收块时间设置为0。
 *
 * 使用xStreamBufferSend（）从任务写入流缓冲区。使用xStreamBufferSendFromISR（）从中断服务例程（ISR）写入流缓冲区。
 *
 * @param xStreamBuffer 要向其发送流的流缓冲区的句柄。
 *
 * @param pvTxData 指向保存要复制到流缓冲区的字节的缓冲区的指针。
 *
 * @param xDataLengthBytes   从pvTxData复制到流缓冲区的最大字节数。
 *
 * @param xTicksToWait 如果流缓冲区包含的空间太少，无法容纳另一个xDataLengthBytes字节，则任务应保持在Blocked状态以等待流缓冲区中有足够的空间可用的最长时间。块时间以刻度周期指定，因此它表示的绝对时间取决于刻度频率。宏pdMS_TO_TICKS（）可用于将以毫秒为单位指定的时间转换为以刻度为单位的时间。如果在FreeRTOSConfig.h中将INCLUDE_vTaskSuspend设置为1，则将xTicksToWait设置为portMAX_DELAY将导致任务无限期等待（不超时）。当任务处于阻塞状态时，它不使用任何CPU时间。
 *
 * @return 写入流缓冲区的字节数。如果任务在将所有xDataLengthBytes写入缓冲区之前超时，它仍将尽可能多地写入字节。
 *
 * 示例用法：
 * @code{c}
 * void vAFunction（StreamBufferHandle_t xStreamBuffer）
 * {
 * size_t x字节发送；
 * uint8_t ucArrayToSend[]=｛0，1，2，3｝；
 * char*pcStringToSend=“要发送的字符串”；
 * 常量TickType_t x100ms=pdMS_TO_TICKS（100）；
 *
 *  //将数组发送到流缓冲区，最多阻止100ms
 *  //等待流缓冲区中有足够的可用空间。
 *  xBytesSsent=xStreamBufferSend（xStreamBuffer，（void*）ucArrayToSend，sizeof（ucArrayTeSend），x100ms）；
 *
 *  如果（xBytesSent！=sizeof（ucArrayToSend））
 *  {
 *      //对xStreamBufferSend（）的调用在足够的时间之前超时
 *      //缓冲区中用于写入数据的空间，但确实存在
 *      //成功写入xBytesSent字节。
 *  }
 *
 *  //将字符串发送到流缓冲区。如果没有，立即返回
 *  //缓冲区中有足够的空间。
 *  xBytesSsent=xStreamBufferSend（xStreamBuffer，（void*）pcStringToSend，strlen（pcStringToSend），0）；
 *
 *  if（xBytesSent！=strlen（pcStringToSend））
 *  {
 *      //无法将整个字符串添加到流缓冲区，因为
 *      //缓冲区中没有足够的可用空间，但xBytesSent字节
 *      //已发送。无法再次尝试发送剩余的字节。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferSend xStreamBufferSend
 * @endcond \ingroup流缓冲管理
 */
size_t xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                          const void * pvTxData,
                          size_t xDataLengthBytes,
                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * size_ t xStreamBufferSendFromISR（StreamBufferHandle_t xStreamBuffer，
 *                               const void*pvTxData，
 *                               size_t xDataLengthBytes，
 *                               BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 将字节流发送到流缓冲区的API函数的中断安全版本。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须在关键部分内对编写API函数（如xStreamBufferSend（））进行每次调用，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须在关键部分内对读取API函数（如xStreamBufferReceive（））进行每次调用，并将接收块时间设置为0。
 *
 * 使用xStreamBufferSend（）从任务写入流缓冲区。使用xStreamBufferSendFromISR（）从中断服务例程（ISR）写入流缓冲区。
 *
 * @param xStreamBuffer 要向其发送流的流缓冲区的句柄。
 *
 * @param pvTxData 指向要复制到流缓冲区的数据的指针。
 *
 * @param xDataLengthBytes 从pvTxData复制到流缓冲区的最大字节数。
 *
 * @param pxHigherPriorityTaskWoken  流缓冲区可能会有一个任务被阻塞，等待数据。调用xStreamBufferSendFromISR（）可以使数据可用，从而导致正在等待数据的任务离开“阻止”状态。如果调用xStreamBufferSendFromISR（）导致任务离开“阻止”状态，并且未阻止的任务的优先级高于当前正在执行的任务（被中断的任务），则xStreamBufferSend FromISR将在内部将pxHigherPriorityTaskWoken设置为pdTRUE。如果xStreamBufferSendFromISR（）将此值设置为pdTRUE，则通常应在中断退出之前执行上下文切换。这将确保中断直接返回到最高优先级的就绪状态任务。pxHigherPriorityTaskWoken在传递到函数之前应设置为pdFALSE。有关示例，请参见下面的示例代码。
 *
 * @return 实际写入流缓冲区的字节数，如果流缓冲区没有足够的可用空间来写入所有字节，则该字节数将小于xDataLengthBytes。
 *
 * 示例用法：
 * @code{c}
 * //已创建的流缓冲区。
 * StreamBufferHandle_t xStreamBuffer；
 *
 * void vAn中断服务例程（void）
 * {
 * size_t x字节发送；
 * char*pcStringToSend=“要发送的字符串”；
 * BaseType_t xHigherPriorityTaskWoken=pdFALSE；//初始化为pdFALSE。
 *
 *  //尝试将字符串发送到流缓冲区。
 *  xBytesSsent＝xStreamBufferSendFromISR（xStreamBuffer，
 *                                         （void*）pcStringToSend，
 *                                         strlen（pcStringToSend），
 *                                         &xHigherPriorityTaskWoken）；
 *
 *  if（xBytesSent！=strlen（pcStringToSend））
 *  {
 *      //流缓冲区中没有足够的可用空间
 *      //要写入的字符串，但已写入xBytesSent字节。
 *  }
 *
 *  //如果xHigherPriorityTaskWoken在内部设置为pdTRUE
 *  //xStreamBufferSendFromISR（），然后是优先级高于
 *  //当前正在执行的任务的优先级已取消阻止，并且上下文
 *  //应执行切换以确保ISR返回到未阻塞状态
 *  //任务。在大多数FreeRTOS端口中，这是通过简单地传递
 *  //xHigherPriorityTaskWoken转换为taskYIELD_FROM_ISR（），该任务将测试
 *  //变量值，并在必要时执行上下文切换。检查
 *  //用于端口特定指令的端口文档。
 *  taskYIELD_FROM_ISR（xHigherPriorityTaskWoken）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferSendFromISR xStreamBufferSend FromISR
 * @endcond \ingroup流缓冲管理
 */
size_t xStreamBufferSendFromISR( StreamBufferHandle_t xStreamBuffer,
                                 const void * pvTxData,
                                 size_t xDataLengthBytes,
                                 BaseType_t * const pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * size_ t xStreamBufferReceive（StreamBufferHandle_t xStreamBuffer，
 *                           void*pvRxData，
 *                           size_t xBufferLengthBytes，
 *                           TickType_t xTicksToWait）；
 * @endcode
 * @endcond
 *
 * 从流缓冲区接收字节。
 *
 * ***注意***：在FreeRTOS对象中，流缓冲区实现（消息缓冲区实现也是如此，因为消息缓冲区构建在流缓冲区之上）假设只有一个任务或中断将写入缓冲区（写入器），只有一个工作或中断将从缓冲区（读卡器）读取。编写器和读取器是不同的任务或中断是安全的，但与其他FreeRTOS对象不同，具有多个不同的编写器或多个不同读取器是不安全的。如果要有多个不同的编写器，那么应用程序编写器必须在关键部分内对编写API函数（如xStreamBufferSend（））进行每次调用，并将发送块时间设置为0，如果要有多个不同的读取器，那么应用程序编写器必须在关键部分内对读取API函数（如xStreamBufferReceive（））进行每次调用，并将接收块时间设置为0。
 *
 * 使用xStreamBufferReceive（）从任务的流缓冲区读取数据。使用xStreamBufferReceiveFromISR（）从中断服务例程（ISR）中读取流缓冲区。
 *
 * @param xStreamBuffer 要从中接收字节的流缓冲区的句柄。
 *
 * @param pvRxData 指向缓冲区的指针，接收的字节将复制到该缓冲区中。
 *
 * @param xBufferLengthBytes pvRxData参数指向的缓冲区长度。这将设置一次调用中要接收的最大字节数。xStreamBufferReceive将返回尽可能多的字节，最大值由xBufferLengthBytes设置。
 *
 * @param xTicksToWait 如果流缓冲区为空，任务应保持在“阻止”状态以等待数据可用的最长时间。如果xTicksToWait为零，xStreamBufferReceive（）将立即返回。块时间以刻度周期指定，因此它表示的绝对时间取决于刻度频率。宏pdMS_TO_TICKS（）可用于将以毫秒为单位指定的时间转换为以刻度为单位的时间。如果在FreeRTOSConfig.h中将INCLUDE_vTaskSuspend设置为1，则将xTicksToWait设置为portMAX_DELAY将导致任务无限期等待（不超时）。任务处于“阻止”状态时，不使用任何CPU时间。
 *
 * @return 实际从流缓冲区读取的字节数，如果对xStreamBufferReceive（）的调用在xBufferLengthBytes可用之前超时，则该字节数将小于xBufferLenghBytes。
 *
 * 示例用法：
 * @code{c}
 * void vA函数（StreamBuffer_t xStreamBuffer）
 * {
 * uint8_t ucRxData[20]；
 * size_t x接收字节；
 * const TickType_t xBlockTime=pdMS_TO_TICKS（20）；
 *
 *  //从流缓冲区接收最多另一个大小的（ucRxData）字节。
 *  //在Blocked状态下等待（因此不使用任何CPU处理时间）
 *  //最大100ms，字节的完整大小（ucRxData）为
 *  //可用。
 *  xReceivedBytes＝xStreamBufferReceive（xStreamBuffer，
 *                                         （void*）ucRxData，
 *                                         sizeof（ucRxData），
 *                                         xBlockTime）；
 *
 *  如果（xReceivedBytes>0）
 *  {
 *      //ucRxData包含另一个xRecivedBytes字节的数据，它可以
 *      //在此处理。。。。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferReceive xStreamBuffer接收
 * @endcond \ingroup流缓冲管理
 */
size_t xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                             void * pvRxData,
                             size_t xBufferLengthBytes,
                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * size_ t xStreamBufferReceiveFromISR（StreamBufferHandle_t xStreamBuffer，
 *                                  void*pvRxData，
 *                                  size_t xBufferLengthBytes，
 *                                  BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 从流缓冲区接收字节的API函数的中断安全版本。
 *
 * 使用xStreamBufferReceive（）从任务的流缓冲区读取字节。使用xStreamBufferReceiveFromISR（）从中断服务例程（ISR）的流缓冲区读取字节。
 *
 * @param xStreamBuffer 从中接收流的流缓冲区的句柄。
 *
 * @param pvRxData 指向将接收到的字节复制到其中的缓冲区的指针。
 *
 * @param xBufferLengthBytes pvRxData参数指向的缓冲区长度。这将设置一次调用中要接收的最大字节数。xStreamBufferReceive将返回尽可能多的字节，最大值由xBufferLengthBytes设置。
 *
 * @param pxHigherPriorityTaskWoken  流缓冲区可能会有一个任务被阻塞，等待空间变为可用。调用xStreamBufferReceiveFromISR（）可以使空间可用，从而使等待空间的任务离开“阻止”状态。如果调用xStreamBufferReceiveFromISR（）导致任务离开“阻止”状态，并且未阻止的任务的优先级高于当前正在执行的任务（被中断的任务），则xStreamBufferReceiveFromISR将在内部将pxHigherPriorityTaskWoken设置为pdTRUE。如果xStreamBufferReceiveFromISR（）将此值设置为pdTRUE，则通常应在中断退出之前执行上下文切换。这将确保中断直接返回到最高优先级的就绪状态任务。pxHigherPriorityTaskWoken在传递到函数之前应设置为pdFALSE。有关示例，请参见下面的代码示例。
 *
 * @return 从流缓冲区读取的字节数（如果有）。
 *
 * 示例用法：
 * @code{c}
 * //已创建的流缓冲区。
 * StreamBuffer_t xStreamBuffer；
 *
 * void vAn中断服务例程（void）
 * {
 * uint8_t ucRxData[20]；
 * size_t x接收字节；
 * BaseType_t xHigherPriorityTaskWoken=pdFALSE；//初始化为pdFALSE。
 *
 *  //从流缓冲区接收下一个流。
 *  xReceivedBytes＝xStreamBufferReceiveFromISR（xStreamBuffer，
 *                                                （void*）ucRxData，
 *                                                sizeof（ucRxData），
 *                                                &xHigherPriorityTaskWoken）；
 *
 *  如果（xReceivedBytes>0）
 *  {
 *      //ucRxData包含从流缓冲区读取的xReceivedBytes。
 *      //在此处理流。。。。
 *  }
 *
 *  //如果xHigherPriorityTaskWoken在内部设置为pdTRUE
 *  //xStreamBufferReceiveFromISR（），然后是优先级高于
 *  //当前正在执行的任务的优先级已取消阻止，并且上下文
 *  //应执行切换以确保ISR返回到未阻塞状态
 *  //任务。在大多数FreeRTOS端口中，这是通过简单地传递
 *  //xHigherPriorityTaskWoken转换为taskYIELD_FROM_ISR（），该任务将测试
 *  //变量值，并在必要时执行上下文切换。检查
 *  //用于端口特定指令的端口文档。
 *  taskYIELD_FROM_ISR（xHigherPriorityTaskWoken）；
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferReceiveFromISR xStreamBufferReceiveFromISR
 * @endcond \ingroup流缓冲管理
 */
size_t xStreamBufferReceiveFromISR( StreamBufferHandle_t xStreamBuffer,
                                    void * pvRxData,
                                    size_t xBufferLengthBytes,
                                    BaseType_t * const pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * void vStreamBufferDelete（StreamBufferHandle_t xStreamBuffer）；
 * @endcode
 * @endcond
 *
 * 删除先前通过调用xStreamBufferCreate（）或xStreamBufferCreateStatic（）创建的流缓冲区。如果流缓冲区是使用动态内存创建的（即，通过xStreamBufferCreate（）），则分配的内存将被释放。
 *
 * 删除流缓冲区后，不能使用流缓冲区句柄。
 *
 * @param xStreamBuffer 要删除的流缓冲区的句柄。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup vStreamBufferDelete vStreamBuffer删除
 * @endcond \ingroup流缓冲管理
 */
void vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * BaseType_t xStreamBufferIsFull（StreamBufferHandle_t xStreamBuffer）；
 * @endcode
 * @endcond
 *
 * 查询流缓冲区以查看其是否已满。如果流缓冲区没有任何可用空间，则该缓冲区已满，因此无法接受更多数据。
 *
 * @param xStreamBuffer 正在查询的流缓冲区的句柄。
 *
 * @return 如果流缓冲区已满，则返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferIsFull xStreamBufferIsFull
 * @endcond \ingroup流缓冲管理
 */
BaseType_t xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * BaseType_t xStreamBufferIsEmpty（StreamBufferHandle_t xStreamBuffer）；
 * @endcode
 * @endcond
 *
 * 查询流缓冲区以查看它是否为空。如果流缓冲区不包含任何数据，则该缓冲区为空。
 *
 * @param xStreamBuffer 正在查询的流缓冲区的句柄。
 *
 * @return 如果流缓冲区为空，则返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferIsEmpty xStreamBufferIsEmpty
 * @endcond \ingroup流缓冲管理
 */
BaseType_t xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * BaseType_t xStreamBufferReset（StreamBufferHandle_t xStream Buffer）；
 * @endcode
 * @endcond
 *
 * 将流缓冲区重置为其初始的空状态。流缓冲区中的任何数据都将被丢弃。只有在没有任务被阻止等待发送到流缓冲区或从流缓冲区接收时，才能重置流缓冲区。
 *
 * @param xStreamBuffer 正在重置的流缓冲区的句柄。
 *
 * @return 如果流缓冲区被重置，则返回pdPASS。如果有一个任务被阻止等待发送到流缓冲区或从流缓冲区读取，则流缓冲区不会重置，并返回pdFAIL。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferReset xStreamBuffer重置
 * @endcond \ingroup流缓冲管理
 */
BaseType_t xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * size_t xStreamBufferSpaces可用（StreamBufferHandle_t xStreamBuffer）；
 * @endcode
 * @endcond
 *
 * 查询流缓冲区以查看它包含多少可用空间，这等于在流缓冲区满之前可以发送到流缓冲区的数据量。
 *
 * @param xStreamBuffer 正在查询的流缓冲区的句柄。
 *
 * @return 在流缓冲区满之前可以写入流缓冲区的字节数。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferSpaces可用xStreamBufferspaces可用
 * @endcond \ingroup流缓冲管理
 */
size_t xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * size_t xStreamBufferBytesAvailable（StreamBufferHandle_t xStreamBuffer）；
 * @endcode
 * @endcond
 *
 * 查询流缓冲区以查看它包含多少数据，这等于在流缓冲区为空之前可以从流缓冲区读取的字节数。
 *
 * @param xStreamBuffer 正在查询的流缓冲区的句柄。
 *
 * @return 在流缓冲区为空之前，可以从流缓冲区读取的字节数。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferBytesAvailable xStreamBufferBytesAvailable
 * @endcond \ingroup流缓冲管理
 */
size_t xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * BaseType_t xStreamBufferSetTriggerLevel（StreamBufferHandle_t xStream Buffer，size_t xTriggerLevel）；
 * @endcode
 * @endcond
 *
 * 流缓冲区的触发级别是在流缓冲区上被阻止以等待数据的任务移出阻止状态之前，流缓冲区中必须存在的字节数。例如，如果任务在读取触发级别为1的空流缓冲区时被阻止，则当单个字节写入缓冲区或任务的阻止时间到期时，该任务将被取消阻止。作为另一个示例，如果任务在读取具有10的触发级别的空流缓冲区时被阻止，则在流缓冲区包含至少10个字节或任务的阻止时间到期之前，该任务将不会被阻止。如果读取任务的块时间在达到触发级别之前过期，则无论实际有多少字节可用，该任务仍将接收。将触发级别设置为0将导致使用触发级别1。指定大于缓冲区大小的触发器级别无效。
 *
 * 在创建流缓冲区时设置触发级别，可以使用xStreamBufferSetTriggerLevel（）进行修改。
 *
 * @param xStreamBuffer 正在更新的流缓冲区的句柄。
 *
 * @param xTriggerLevel 流缓冲区的新触发器级别。
 *
 * @return 如果xTriggerLevel小于或等于流缓冲区的长度，则将更新触发级别并返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferSetTriggerLevel xStreamBufferSet TriggerLevel
 * @endcond \ingroup流缓冲管理
 */
BaseType_t xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * BaseType_t xStreamBufferSendCompletedFromISR（StreamBufferHandle_t xStream Buffer，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 仅限高级用户。
 *
 * 当数据被发送到消息缓冲区或流缓冲区时，sbSEND_COMPLETE（）宏将从FreeRTOS API中调用。如果有一个任务在消息或流缓冲区上被阻止，等待数据到达，则sbSEND_COMPLETE（）宏会向该任务发送通知，将其从“阻止”状态中删除。xStreamBufferSendCompletedFromISR（）执行相同的操作。它是为了使应用程序编写者能够实现自己版本的sbSEND_COMPLETED（），并且在任何其他时间都不得使用。
 *
 * 请参阅FreeRTOS/Demo/Minimal/MessageBufferAMP中实现的示例。c获取更多信息。
 *
 * @param xStreamBuffer 写入数据的流缓冲区的句柄。
 *
 * @param pxHigherPriorityTaskWoken *pxHigherPriorityTaskWoken应在传递到xStreamBufferSendCompletedFromISR（）之前初始化为pdFALSE。如果调用xStreamBufferSendCompletedFromISR（）将任务从Blocked状态移除，并且该任务的优先级高于当前运行任务的优先级，则pxHigherPriorityTaskWoken将设置为pdTRUE，指示在退出ISR之前应执行上下文切换。
 *
 * @return 如果任务已从“阻止”状态删除，则返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferSendCompletedFromISR xStreamBufferSend CompletedFrom ISR
 * @endcond \ingroup流缓冲管理
 */
BaseType_t xStreamBufferSendCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                              BaseType_t * pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION流缓冲区.h
 *
 * @code{c}
 * BaseType_t xStreamBufferReceiveCompletedFromISR（StreamBufferHandle_t xStream Buffer，BaseType_t*pxHigherPriorityTaskWoken）；
 * @endcode
 * @endcond
 *
 * 仅限高级用户。
 *
 * 当从消息缓冲区或流缓冲区中读取数据时，从FreeRTOS API中调用sbRECEIVE_COMPLETED（）宏。如果有一个任务在消息或流缓冲区上被阻止，等待数据到达，则sbRECEIVE_COMPLETED（）宏会向该任务发送通知，将其从“阻止”状态中删除。xStreamBufferReceiveCompletedFromISR（）执行相同的操作。它是为了使应用程序编写者能够实现自己版本的sbRECEIVE_COMPLETED（），并且在任何其他时间都不得使用。
 *
 * 请参阅FreeRTOS/Demo/Minimal/MessageBufferAMP中实现的示例。c获取更多信息。
 *
 * @param xStreamBuffer 从中读取数据的流缓冲区的句柄。
 *
 * @param pxHigherPriorityTaskWoken *pxHigherPriorityTaskWoken应在传递到xStreamBufferReceiveCompletedFromISR（）之前初始化为pdFALSE。如果调用xStreamBufferReceiveCompletedFromISR（）将任务从Blocked状态移除，并且该任务的优先级高于当前运行任务的优先级，则pxHigherPriorityTaskWoken将设置为pdTRUE，指示在退出ISR之前应执行上下文切换。
 *
 * @return 如果任务已从“阻止”状态删除，则返回pdTRUE。否则将返回pdFALSE。
 *
 * @cond !DOC_SINGLE_GROUP\defgroup xStreamBufferReceiveCompletedFromISR xStreamBuffer ReceiveCompletedfrom ISR
 * @endcond \ingroup流缓冲管理
 */
BaseType_t xStreamBufferReceiveCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                 BaseType_t * pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

/**@秒！文档_排除_标题_节*/
/* 下面的函数不是公共API的一部分。*/
StreamBufferHandle_t xStreamBufferGenericCreate( size_t xBufferSizeBytes,
                                                 size_t xTriggerLevelBytes,
                                                 BaseType_t xIsMessageBuffer ) PRIVILEGED_FUNCTION;

StreamBufferHandle_t xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                       size_t xTriggerLevelBytes,
                                                       BaseType_t xIsMessageBuffer,
                                                       uint8_t * const pucStreamBufferStorageArea,
                                                       StaticStreamBuffer_t * const pxStaticStreamBuffer ) PRIVILEGED_FUNCTION;

size_t xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

#if ( configUSE_TRACE_FACILITY == 1 )
    void vStreamBufferSetStreamBufferNumber( StreamBufferHandle_t xStreamBuffer,
                                             UBaseType_t uxStreamBufferNumber ) PRIVILEGED_FUNCTION;
    UBaseType_t uxStreamBufferGetStreamBufferNumber( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;
    uint8_t ucStreamBufferGetStreamBufferType( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;
#endif

/**@结束秒*/

/* *INDENT-OFF* */
#if defined( __cplusplus )
    }
#endif
/* *INDENT-ON* */

#endif /* !定义（STREAM_BUFFER_H）*/

