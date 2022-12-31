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

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h" must appear in source files before "include semphr.h"
#endif

#include "queue.h"

typedef QueueHandle_t SemaphoreHandle_t;

#define semBINARY_SEMAPHORE_QUEUE_LENGTH    ( ( uint8_t ) 1U )
#define semSEMAPHORE_QUEUE_ITEM_LENGTH      ( ( uint8_t ) 0U )
#define semGIVE_BLOCK_TIME                  ( ( TickType_t ) 0U )

/**@秒！文档_排除_标题_节*/
/**
 * semphr。小时
 * @code{c}
 * vSemaphoreCreateBinary（SemaphoreHandle_t xSemaphore）；
 * @endcode
 *
 * 在许多使用场景中，使用直接到任务通知代替二进制信号量会更快、更节省内存！https://www.FreeRTOS.org/RTOS-task-notifications.html
 *
 * 这个旧的vSemaphoreCreateBinary（）宏现在已被弃用，取而代之的是xSemaphoreCoreateBinary（）函数。请注意，使用vSemaphoreCreateBinary（）宏创建的二进制信号量是在这样一种状态下创建的，即“获取”信号量的第一次调用将通过，而使用xSemaphorsCreateBinary（）创建的二进制信息量是在这种状态下创建，即在“获取”之前必须先“给定”信号量。
 *
 * <i> 宏</i>，通过使用现有队列机制实现信号量。队列长度为1，因为这是一个二进制信号量。数据大小为0，因为我们不想实际存储任何数据——我们只想知道队列是空的还是满的。
 *
 * 这种类型的信号量可用于任务之间或中断与任务之间的纯同步。一旦获得信号量，就不需要返回信号量，因此一个任务/中断可以连续地“发出”信号量，而另一个任务或中断可以连续“接收”信号量。因此，这种类型的信号量不使用优先级继承机制。有关使用优先级继承的替代方案，请参见xSemaphoreCreateMutex（）。
 *
 * @param xSemaphore 创建的信号量的句柄。应为SemaphoreHandle_t类型。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 * void vATask（void*pvParameters）
 * {
 *  //在调用vSemaphoreCreateBinary（）之前不能使用信号量。
 *  //这是一个宏，因此直接传入变量。
 *  vSemaphoreCreateBinary（xSemaphore）；
 *
 *  if（xSemaphore！=NULL）
 *  {
 *      //已成功创建信号量。
 *      //现在可以使用信号灯了。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup vSemapureCreateBinary vSemaporeCreateBinary
 * @endcond \内部组信号
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define vSemaphoreCreateBinary( xSemaphore )                                                                                     \
    {                                                                                                                                \
        ( xSemaphore ) = xQueueGenericCreate( ( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_BINARY_SEMAPHORE ); \
        if( ( xSemaphore ) != NULL )                                                                                                 \
        {                                                                                                                            \
            ( void ) xSemaphoreGive( ( xSemaphore ) );                                                                               \
        }                                                                                                                            \
    }
#endif
/**@结束秒*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * SemaphoreHandle_t xSemaphoreCreateBinary（void）；
 * @endcode
 * @endcond
 *
 * 创建一个新的二进制信号量实例，并返回一个可以引用新信号量的句柄。
 *
 * 在许多使用场景中，使用直接到任务通知代替二进制信号量会更快、更节省内存！https://www.FreeRTOS.org/RTOS-task-notifications.html
 *
 * 在FreeRTOS实现内部，二进制信号量使用存储信号量结构的内存块。如果使用xSemaphoreCreateBinary（）创建二进制信号量，则所需的内存将在xSemaphereCreateBinary（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateBinaryStatic（）创建二进制信号量，则应用程序编写器必须提供内存。因此，xSemaphoreCreateBinaryStatic（）允许在不使用任何动态内存分配的情况下创建二进制信号量。
 *
 * 旧的vSemaphoreCreateBinary（）宏现在已被弃用，取而代之的是此xSemaphoreCoreateBinry（）函数。请注意，使用vSemaphoreCreateBinary（）宏创建的二进制信号量是在这样一种状态下创建的，即“获取”信号量的第一次调用将通过，而使用xSemaphorsCreateBinary（）创建的二进制信息量是在这种状态下创建，即在“获取”之前必须先“给定”信号量。
 *
 * 这种类型的信号量可用于任务之间或中断与任务之间的纯同步。一旦获得信号量，就不需要返回信号量，因此一个任务/中断可以连续地“发出”信号量，而另一个任务或中断可以连续“接收”信号量。因此，这种类型的信号量不使用优先级继承机制。有关使用优先级继承的替代方案，请参见xSemaphoreCreateMutex（）。
 *
 * @return 创建的信号量的句柄，如果无法分配保持信号量数据结构所需的内存，则为NULL。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 * void vATask（void*pvParameters）
 * {
 *  //在调用vSemaphoreCreateBinary（）之前不能使用信号量。
 *  //这是一个宏，因此直接传入变量。
 *  xSemaphore=xSemaphereCreateBinary（）；
 *
 *  if（xSemaphore！=NULL）
 *  {
 *      //已成功创建信号量。
 *      //现在可以使用信号灯了。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemapureCreateBinary xSemaporeCreateBinary
 * @endcond \内部组信号
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define xSemaphoreCreateBinary()    xQueueGenericCreate( ( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_BINARY_SEMAPHORE )
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * SemaphoreHandle_t xSemaphoreCreateBinaryStatic（StaticSemaphore_t*pxSemaphoreBuffer）；
 * @endcode
 * @endcond
 *
 * 创建一个新的二进制信号量实例，并返回一个可以引用新信号量的句柄。
 *
 * 注意：在许多使用场景中，使用直接到任务通知代替二进制信号量会更快、更节省内存！https://www.FreeRTOS.org/RTOS-task-notifications.html
 *
 * 在FreeRTOS实现内部，二进制信号量使用存储信号量结构的内存块。如果使用xSemaphoreCreateBinary（）创建二进制信号量，则所需的内存将在xSemaphereCreateBinary（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateBinaryStatic（）创建二进制信号量，则应用程序编写器必须提供内存。因此，xSemaphoreCreateBinaryStatic（）允许在不使用任何动态内存分配的情况下创建二进制信号量。
 *
 * 这种类型的信号量可用于任务之间或中断与任务之间的纯同步。一旦获得信号量，就不需要返回信号量，因此一个任务/中断可以连续地“发出”信号量，而另一个任务或中断可以连续“接收”信号量。因此，这种类型的信号量不使用优先级继承机制。有关使用优先级继承的替代方案，请参见xSemaphoreCreateMutex（）。
 *
 * @param pxStaticSemaphore 必须指向StaticSemaphore_t类型的变量，然后该变量将用于保存信号量的数据结构，从而不需要动态分配内存。
 *
 * @return 如果创建了信号量，则返回创建的信号量的句柄。如果pxSemaphoreBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xSemaphore=NULL；
 * StaticSemaphore_t xSemaphoreBuffer；
 *
 * void vATask（void*pvParameters）
 * {
 *  //在调用xSemaphoreCreateBinary（）或
 *  //xSemaphoreCreateBinaryStatic（）。
 *  //信号量的数据结构将放置在xSemaphoreBuffer中
 *  //变量，其地址被传递到函数中。这个
 *  //函数的参数不为NULL，因此函数不会尝试
 *  //动态内存分配，因此函数不会返回
 *  //返回NULL。
 *  xSemaphore=xSemaphreCreateBinaryStatic（&xSemapherBuffer）；
 *
 *  //此处显示任务代码的其余部分。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreCreateBinaryStatic xSemaphereCreateBinary静态
 * @endcond \内部组信号
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    #define xSemaphoreCreateBinaryStatic( pxStaticSemaphore )    xQueueGenericCreateStatic( ( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH, NULL, pxStaticSemaphore, queueQUEUE_TYPE_BINARY_SEMAPHORE )
#endif /* 配置支持状态分配*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * xSemaphoreTake(
 *                   SemaphoreHandle_t x信号量，
 *                   TickType_t x区块时间
 *               );
 * @endcode
 * @endcond
 *
 * <i> 宏</i>获取信号量。信号量之前必须是通过调用xSemaphoreCreateBinary（）、xSemaphreCreateMutex（）或xSemapherCreateCount（）创建的。
 *
 * param xSemaphore创建信号量时获取的信号量句柄。
 *
 * param xBlockTime等待信号量变为可用的时间（以节拍为单位）。宏端口TICK_PERIOD_MS可用于将其转换为实时。块时间为零可用于轮询信号量。portMAX_DELAY的块时间可用于无限期块（前提是在FreeRTOSConfig.h中将INCLUDE_vTaskSuspend设置为1）。
 *
 * @return pdTRUE，如果获得了信号量。pdFALSE，如果xBlockTime过期而信号量不可用。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 * //创建信号量的任务。
 * void vATask（void*pvParameters）
 * {
 *  //创建信号量以保护共享资源。
 *  vSemaphoreCreateBinary（xSemaphore）；
 * }
 *
 * //使用信号量的任务。
 * void vAnotherTask（void*pvParameters）
 * {
 *  //……做其他事情。
 *
 *  if（xSemaphore！=NULL）
 *  {
 *      //看看我们能否获得信号量。如果信号量不可用
 *      //等待10个滴答声，看看它是否空闲。
 *      如果（xSemaphoreTake（xSemamphore，（TickType_t）10）==pdTRUE）
 *      {
 *          //我们能够获得信号量，现在可以访问
 *          //共享资源。
 *
 *          // ...
 *
 *          //我们已完成对共享资源的访问。释放
 *          //信号量。
 *          xSemaphoreGive（x信号量）；
 *      }
 *      其他的
 *      {
 *          //我们无法获取信号量，因此无法访问
 *          //安全地共享资源。
 *      }
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreTake xSemaphoeTake
 * @endcond \内部组信号
 */
#define xSemaphoreTake( xSemaphore, xBlockTime )    xQueueSemaphoreTake( ( xSemaphore ), ( xBlockTime ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * xSemaphoreTakeRecursive(
 *                          SemaphoreHandle_t xMutex，
 *                          TickType_t x区块时间
 *                        );
 * @endcode
 * @endcond
 *
 * <i> 宏</i>递归获取或“获取”互斥类型信号量。互斥体之前必须使用对xSemaphoreCreateRecursiveMutex（）的调用创建；
 *
 * configUSE_RECURSIVE_MUTEXES必须在FreeRTOSConfig中设置为1。h表示此宏可用。
 *
 * 此宏不能用于使用xSemaphoreCreateMutex（）创建的互斥对象。
 *
 * 递归使用的互斥锁可以由所有者重复“获取”。直到所有者为每个成功的“take”请求调用了xSemaphoreGiveRecursive（），互斥锁才会再次可用。例如，如果一个任务成功地“获取”了同一个互斥体5次，那么该互斥体将不可用于任何其他任务，直到它也恰好“返回”了互斥体五次。
 *
 * @param xMutex 正在获取的互斥对象的句柄。这是xSemaphoreCreateRecursiveMutex（）返回的句柄；
 *
 * @param xBlockTime 等待信号量变为可用的时间（以滴答为单位）。宏端口TICK_PERIOD_MS可用于将其转换为实时。块时间为零可用于轮询信号量。如果任务已经拥有信号量，则无论xBlockTime的值如何，xSemaphoreTakeRecursive（）都将立即返回。
 *
 * @return pdTRUE，如果获得了信号量。pdFALSE，如果xBlockTime过期而信号量不可用。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xMutex=NULL；
 *
 * //创建互斥对象的任务。
 * void vATask（void*pvParameters）
 * {
 *  //创建互斥锁以保护共享资源。
 *  xMutex=xSemaphoreCreateRecursiveMutex（）；
 * }
 *
 * //使用互斥锁的任务。
 * void vAnotherTask（void*pvParameters）
 * {
 *  //……做其他事情。
 *
 *  如果（xMutex！=NULL）
 *  {
 *      //看看我们能否获得互斥锁。如果互斥锁不可用
 *      //等待10个滴答声，看看它是否空闲。
 *      如果（xSemaphoreTakeRecursive（xSemamphore，（TickType_t）10）==pdTRUE）
 *      {
 *          //我们能够获得互斥锁，现在可以访问
 *          //共享资源。
 *
 *          // ...
 *          //由于代码的性质
 *          //xSemaphoreTakeRecursive（）是在同一互斥对象上生成的。实际上
 *          //这些代码不会像这样只是顺序调用
 *          //没有意义。相反，电话很可能被隐藏在里面
 *          //更复杂的呼叫结构。
 *          xSemaphoreTakeRecursive（xMutex，（TickType_t）10）；
 *          xSemaphoreTakeRecursive（xMutex，（TickType_t）10）；
 *
 *          //互斥锁现在已被“占用”三次，因此不会被占用
 *          //可用于另一个任务，直到它也被退回
 *          //三次。同样，真正的代码不太可能
 *          //这些调用是按顺序进行的，但却隐藏在更复杂的
 *          //调用结构。这只是为了说明目的。
 *          xSemaphoreGiveRecursive（xMutex）；
 *          xSemaphoreGiveRecursive（xMutex）；
 *          xSemaphoreGiveRecursive（xMutex）；
 *
 *          //现在互斥锁可以被其他任务占用。
 *      }
 *      其他的
 *      {
 *          //我们无法获取互斥锁，因此无法访问
 *          //安全地共享资源。
 *      }
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreTakeRecursive xSemaphereTakeRecrusive
 * @endcond \内部组信号
 */
#define xSemaphoreTakeRecursive( xMutex, xBlockTime )   xQueueTakeMutexRecursive( ( xMutex ), ( xBlockTime ) )

/**
 * <i> 宏</i>以释放信号量。信号量之前必须是通过调用xSemaphoreCreateBinary（）、xSemaphreCreateMutex（）或xSemapherCreateCount（）创建的。并使用sSemaphoreTake（）获得。
 *
 * 不能从ISR中使用此宏。请参见xSemaphoreGiveFromISR（）以获取可从ISR中使用的替代方案。
 *
 * 此宏也不能用于使用xSemaphoreCreateRecursiveMutex（）创建的信号量。
 *
 * @param xSemaphore 正在释放的信号量的句柄。这是创建信号量时返回的句柄。
 *
 * @return pdTRUE，如果信号量已释放。pdFALSE，如果发生错误。信号量是使用队列实现的。如果队列上没有空间来发布消息，则可能会发生错误，这表明信号量最初没有正确获得。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 * void vATask（void*pvParameters）
 * {
 *  //创建信号量以保护共享资源。
 *  vSemaphoreCreateBinary（xSemaphore）；
 *
 *  if（xSemaphore！=NULL）
 *  {
 *      如果（xSemaphoreGive（xSemamphore）！=pdTRUE）
 *      {
 *          //我们预计这一呼吁会失败，因为我们无法给予
 *          //一个信号量，没有先“接受”它！
 *      }
 *
 *      //获取信号量-如果信号量不是，不要阻塞
 *      //立即可用。
 *      如果（xSemaphoreTake（xSemamphore，（TickType_t）0））
 *      {
 *          //我们现在有了信号量，可以访问共享资源。
 *
 *          // ...
 *
 *          //我们已完成对共享资源的访问，因此可以释放
 *          //信号量。
 *          如果（xSemaphoreGive（xSemamphore）！=pdTRUE）
 *          {
 *              //我们不希望这次通话失败，因为我们必须
 *              //获得了到达这里的信号量。
 *          }
 *      }
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreGive xSemaphoeGive
 * @endcond \内部组信号
 */
#define xSemaphoreGive( xSemaphore )    xQueueGenericSend( ( QueueHandle_t ) ( xSemaphore ), NULL, semGIVE_BLOCK_TIME, queueSEND_TO_BACK )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * xSemaphoreGiveRecursive（Semaphore_Handle_t xMutex）；
 * @endcode
 * @endcond
 *
 * <i> Macro</i>递归释放或“给定”互斥类型信号量。互斥体之前必须使用对xSemaphoreCreateRecursiveMutex（）的调用创建；
 *
 * configUSE_RECURSIVE_MUTEXES必须在FreeRTOSConfig中设置为1。h表示此宏可用。
 *
 * 此宏不能用于使用xSemaphoreCreateMutex（）创建的互斥对象。
 *
 * 递归使用的互斥锁可以由所有者重复“获取”。直到所有者为每个成功的“take”请求调用了xSemaphoreGiveRecursive（），互斥锁才会再次可用。例如，如果一个任务成功地“获取”了同一个互斥体5次，那么该互斥体将不可用于任何其他任务，直到它也恰好“返回”了互斥体五次。
 *
 * @param xMutex 被释放或“给定”的互斥对象的句柄。这是xSemaphoreCreateMutex（）返回的句柄；
 *
 * @return pdTRUE，如果给定了信号量。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t xMutex=NULL；
 *
 * //创建互斥对象的任务。
 * void vATask（void*pvParameters）
 * {
 *  //创建互斥锁以保护共享资源。
 *  xMutex=xSemaphoreCreateRecursiveMutex（）；
 * }
 *
 * //使用互斥锁的任务。
 * void vAnotherTask（void*pvParameters）
 * {
 *  //……做其他事情。
 *
 *  如果（xMutex！=NULL）
 *  {
 *      //看看我们能否获得互斥锁。如果互斥锁不可用
 *      //等待10个滴答声，看看它是否空闲。
 *      如果（xSemaphoreTakeRecursive（xMutex，（TickType_t）10）==pdTRUE）
 *      {
 *          //我们能够获得互斥锁，现在可以访问
 *          //共享资源。
 *
 *          // ...
 *          //由于代码的性质
 *          //xSemaphoreTakeRecursive（）是在同一互斥对象上生成的。实际上
 *          //这些代码不会像这样只是顺序调用
 *          //没有意义。相反，电话很可能被隐藏在里面
 *          //更复杂的呼叫结构。
 *          xSemaphoreTakeRecursive（xMutex，（TickType_t）10）；
 *          xSemaphoreTakeRecursive（xMutex，（TickType_t）10）；
 *
 *          //互斥锁现在已被“占用”三次，因此不会被占用
 *          //可用于另一个任务，直到它也被退回
 *          //三次。同样，真正的代码不太可能
 *          //这些调用顺序进行
 *          //将作为调用堆栈调用xSemaphoreGiveRecursive（）
 *          //展开。这只是为了说明目的。
 *          xSemaphoreGiveRecursive（xMutex）；
 *          xSemaphoreGiveRecursive（xMutex）；
 *          xSemaphoreGiveRecursive（xMutex）；
 *
 *          //现在互斥锁可以被其他任务占用。
 *      }
 *      其他的
 *      {
 *          //我们无法获取互斥锁，因此无法访问
 *          //安全地共享资源。
 *      }
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreGiveRecursive xSemaphoeGive递归
 * @endcond \内部组信号
 */
#define xSemaphoreGiveRecursive( xMutex )   xQueueGiveMutexRecursive( ( xMutex ) )

/**
 * <i> 宏</i>以释放信号量。信号量之前必须是通过调用xSemaphoreCreateBinary（）或xSemaphoeCreateCount（）创建的。
 *
 * Mutex类型的信号量（通过调用xSemaphoreCreateMutex（）创建的信号量）不能与此宏一起使用。
 *
 * 此宏可以从ISR中使用。
 *
 * @param xSemaphore 正在释放的信号量的句柄。这是创建信号量时返回的句柄。
 *
 * @param pxHigherPriorityTaskWoken 如果给定信号量导致任务取消阻止，并且取消阻止的任务的优先级高于当前运行的任务，则xSemaphoreGiveFromISR（）会将pxHigherPriorityTaskWoken设置为pdTRUE。如果xSemaphoreGiveFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @return pdTRUE（如果信号量已成功给定），否则为errQUEUE_FULL。
 *
 * 示例用法：
 * @code{c}
 * #定义LONG_TIME 0xffff
 * #定义TICKS_TO_WAIT 10
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 * //重复性任务。
 * void vATask（void*pvParameters）
 * {
 *  用于（；；）
 *  {
 *      //我们希望此任务每10个计时器周期运行一次。信号灯
 *      //在启动此任务之前创建。
 *
 *      //等待信号量变为可用的块。
 *      如果（xSemaphoreTake（xSemamphore，LONG_TIME）==pdTRUE）
 *      {
 *          //是时候执行了。
 *
 *          // ...
 *
 *          //我们已经完成了任务。返回到循环的顶部，其中
 *          //我们将阻塞信号量，直到该执行为止
 *          //再次。使用信号量与
 *          //以这种方式，ISR无需“返回”信号量。
 *      }
 *  }
 * }
 *
 * //计时器ISR
 * void vTimerISR（void*pvParameters）
 * {
 * 静态uint8_t ucLocalTickCount=0；
 * 静态BaseType_t xHigherPriorityTaskWoken；
 *
 *  //出现计时器滴答声。
 *
 *  //…执行其他时间功能。
 *
 *  //vATask（）是时候运行了吗？
 *  xHigherPriorityTaskWoken=pdFALSE；
 *  ucLocalTickCount++；
 *  如果（ucLocalTickCount>=TICKS_TO_WAIT）
 *  {
 *      //通过释放信号量解除任务锁定。
 *      xSemaphoreGiveFromISR（xSemaphoe，&xHigherPriorityTaskWoken）；
 *
 *      //重置计数，以便我们在10个时钟周期内再次释放信号量。
 *      ucLocalTickCount=0；
 *  }
 *
 *  如果（xHigherPriorityTaskWoken！=pdFALSE）
 *  {
 *      //我们可以在这里强制切换上下文。上下文从
 *      //ISR使用特定于端口的语法。检查端口的演示任务
 *      //查找所需的语法。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreGiveFromISR xSemaphoeGivefrom ISR
 * @endcond \内部组信号
 */
#define xSemaphoreGiveFromISR( xSemaphore, pxHigherPriorityTaskWoken )    xQueueGiveFromISR( ( QueueHandle_t ) ( xSemaphore ), ( pxHigherPriorityTaskWoken ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * 来自ISR的xSemaphoreTake(
 *                        SemaphoreHandle_t x信号量，
 *                        基本类型_t*pxHigherPriorityTaskWoken
 *                    );
 * @endcode
 * @endcond
 *
 * <i> 宏</i>从ISR获取信号量。信号量之前必须是通过调用xSemaphoreCreateBinary（）或xSemaphoeCreateCount（）创建的。
 *
 * Mutex类型的信号量（通过调用xSemaphoreCreateMutex（）创建的信号量）不能与此宏一起使用。
 *
 * 这个宏可以从ISR中使用，但是从ISR中获取信号量不是一个常见的操作。当中断从资源池获取对象时（当信号量计数指示可用资源的数量时），它可能只在使用计数信号量时有用。
 *
 * @param xSemaphore 正在获取的信号量的句柄。这是创建信号量时返回的句柄。
 *
 * @param[out] pxHigherPriorityTaskWoken 如果使用信号量导致任务取消阻止，并且取消阻止的任务的优先级高于当前运行的任务，则xSemaphoreTakeFromISR（）会将pxHigherPriorityTaskWoken设置为pdTRUE。如果xSemaphoreTakeFromISR（）将此值设置为pdTRUE，则应在中断退出之前请求上下文切换。
 *
 * @return 如果信号量被成功获取，则为pdTRUE，否则为pdFALSE
 */
#define xSemaphoreTakeFromISR( xSemaphore, pxHigherPriorityTaskWoken )    xQueueReceiveFromISR( ( QueueHandle_t ) ( xSemaphore ), NULL, ( pxHigherPriorityTaskWoken ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * SemaphoreHandle_t xSemaphoreCreateMutex（无效）；
 * @endcode
 * @endcond
 *
 * 创建一个新的互斥类型信号量实例，并返回一个句柄，通过该句柄可以引用新的互斥。
 *
 * 在FreeRTOS实现内部，互斥信号量使用一块内存，互斥结构存储在内存中。如果使用xSemaphoreCreateMutex（）创建互斥锁，则所需的内存将在xSemaphreCreateMutex（（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateMutexStatic（）创建互斥锁，则应用程序编写器必须提供内存。因此，xSemaphoreCreateMutexStatic（）允许在不使用任何动态内存分配的情况下创建互斥体。
 *
 * 使用此函数创建的互斥体可以使用xSemaphoreTake（）和xSemaphreGive（）宏访问。不得使用xSemaphoreTakeRecursive（）和xSemaphreGiveRecursive）宏。
 *
 * 这种类型的信号量使用优先级继承机制，因此“获取”信号量的任务必须始终在不再需要信号量时“返回”信号量。
 *
 * 不能在中断服务例程中使用多路信号量。
 *
 * 请参阅xSemaphoreCreateBinary（），了解可用于纯同步（其中一个任务或中断总是“给出”信号量，另一个任务总是“获取”信号量）和中断服务例程内的另一种实现。
 *
 * @return 如果成功创建了互斥体，则返回创建的信号量的句柄。如果没有足够的堆来分配互斥锁数据结构，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t x信号量；
 *
 * void vATask（void*pvParameters）
 * {
 *  //在调用xSemaphoreCreateMutex（）之前不能使用信号量。
 *  //这是一个宏，因此直接传入变量。
 *  xSemaphore=xSemaphereCreateMutex（）；
 *
 *  if（xSemaphore！=NULL）
 *  {
 *      //已成功创建信号量。
 *      //现在可以使用信号灯了。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreCreateMutex x SemaphoreCoreateMutex
 * @endcond \内部组信号
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define xSemaphoreCreateMutex()    xQueueCreateMutex( queueQUEUE_TYPE_MUTEX )
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * SemaphoreHandle_t xSemaphoreCreateMutexStatic（StaticSemaphore_t*pxMutexBuffer）；
 * @endcode
 * @endcond
 *
 * 创建一个新的互斥类型信号量实例，并返回一个句柄，通过该句柄可以引用新的互斥。
 *
 * 在FreeRTOS实现内部，互斥信号量使用一块内存，互斥结构存储在内存中。如果使用xSemaphoreCreateMutex（）创建互斥锁，则所需的内存将在xSemaphreCreateMutex（（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateMutexStatic（）创建互斥锁，则应用程序编写器必须提供内存。因此，xSemaphoreCreateMutexStatic（）允许在不使用任何动态内存分配的情况下创建互斥体。
 *
 * 使用此函数创建的互斥体可以使用xSemaphoreTake（）和xSemaphreGive（）宏访问。不得使用xSemaphoreTakeRecursive（）和xSemaphreGiveRecursive）宏。
 *
 * 这种类型的信号量使用优先级继承机制，因此“获取”信号量的任务必须始终在不再需要信号量时“返回”信号量。
 *
 * 不能在中断服务例程中使用多路信号量。
 *
 * 请参阅xSemaphoreCreateBinary（），了解可用于纯同步（其中一个任务或中断总是“给出”信号量，另一个任务总是“获取”信号量）和中断服务例程内的另一种实现。
 *
 * @param pxMutexBuffer 必须指向StaticSemaphore_t类型的变量，该变量将用于保存互斥对象的数据结构，从而不需要动态分配内存。
 *
 * @return 如果成功创建了互斥体，则返回创建的互斥体的句柄。如果pxMutexBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t x信号量；
 * StaticSemaphore_t xMutexBuffer；
 *
 * void vATask（void*pvParameters）
 * {
 *  //在创建互斥体之前，不能使用它。xMultexBuffer是
 *  //到xSemaphoreCreateMutexStatic（）中，因此没有动态内存分配
 *  //尝试。
 *  xSemaphore=xSemaphereCreateMutexStatic（&xMutexBuffer）；
 *
 *  //由于未执行动态内存分配，xSemaphore不能为NULL，
 *  //因此无需检查。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemapureCreateMutexStatic xSemaporeCreateMutex静态
 * @endcond \内部组信号
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    #define xSemaphoreCreateMutexStatic( pxMutexBuffer )    xQueueCreateMutexStatic( queueQUEUE_TYPE_MUTEX, ( pxMutexBuffer ) )
#endif /* 配置支持状态分配*/


/**
 * 创建一个新的递归互斥类型信号量实例，并返回一个句柄，通过该句柄可以引用新的递归mutex。
 *
 * 在FreeRTOS实现内部，递归互斥锁使用一块内存，互斥锁结构存储在内存中。如果使用xSemaphoreCreateRecursiveMutex（）创建递归互斥体，则所需的内存将在xSemaphreCreateRecursiveMUtex（）函数内自动动态分配。（参见http://www.freertos.org/a00111.html). 如果使用xSemaphoreCreateRecursiveMutexStatic（）创建递归互斥体，则应用程序编写器必须提供互斥体将使用的内存。因此，xSemaphoreCreateRecursiveMutexStatic（）允许在不使用任何动态内存分配的情况下创建递归互斥。
 *
 * 使用此宏创建的互斥体可以使用xSemaphoreTakeRecursive（）和xSemaphreGiveRecursive）宏访问。不得使用xSemaphoreTake（）和xSemaphreGive（）宏。
 *
 * 递归使用的互斥锁可以由所有者重复“获取”。直到所有者为每个成功的“take”请求调用了xSemaphoreGiveRecursive（），互斥锁才会再次可用。例如，如果一个任务成功地“获取”了同一个互斥体5次，那么该互斥体将不可用于任何其他任务，直到它也恰好“返回”了互斥体五次。
 *
 * 这种类型的信号量使用优先级继承机制，因此“获取”信号量的任务必须始终在不再需要信号量时“返回”信号量。
 *
 * 不能在中断服务例程中使用多路信号量。
 *
 * 请参阅vSemaphoreCreateBinary（），了解可用于纯同步（其中一个任务或中断总是“给出”信号量，另一个任务总是“获取”信号量）和中断服务例程内的另一种实现。
 *
 * @return xSemaphore创建的互斥信号量的句柄。应为SemaphoreHandle_t类型。
 *
 * 示例用法：
 * @code{c}
 *  SemaphoreHandle_t x信号量；
 *
 *  void vATask（void*pvParameters）
 *  {
 *     //在调用xSemaphoreCreateMutex（）之前不能使用信号量。
 *     //这是一个宏，因此直接传入变量。
 *     xSemaphore=xSemaphereCreateRecursiveMutex（）；
 *
 *     if（xSemaphore！=NULL）
 *     {
 *         //已成功创建信号量。
 *         //现在可以使用信号灯了。
 *     }
 *  }
 * @endcode \内部组信号
 */
#if( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_RECURSIVE_MUTEXES == 1 ) )
    #define xSemaphoreCreateRecursiveMutex() xQueueCreateMutex( queueQUEUE_TYPE_RECURSIVE_MUTEX )
#endif

/**
 * 创建一个新的递归互斥类型信号量实例，并返回一个句柄，通过该句柄可以引用新的递归mutex。
 *
 * 在FreeRTOS实现内部，递归互斥锁使用一块内存，互斥锁结构存储在内存中。如果使用xSemaphoreCreateRecursiveMutex（）创建递归互斥体，则所需的内存将在xSemaphreCreateRecursiveMUtex（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateRecursiveMutexStatic（）创建递归互斥体，则应用程序编写器必须提供互斥体将使用的内存。因此，xSemaphoreCreateRecursiveMutexStatic（）允许在不使用任何动态内存分配的情况下创建递归互斥。
 *
 * 使用此宏创建的互斥体可以使用xSemaphoreTakeRecursive（）和xSemaphreGiveRecursive）宏访问。不得使用xSemaphoreTake（）和xSemaphreGive（）宏。
 *
 * 递归使用的互斥锁可以由所有者重复“获取”。直到所有者为每个成功的“take”请求调用了xSemaphoreGiveRecursive（），互斥锁才会再次可用。例如，如果一个任务成功地“获取”了同一个互斥体5次，那么该互斥体将不可用于任何其他任务，直到它也恰好“返回”了互斥体五次。
 *
 * 这种类型的信号量使用优先级继承机制，因此“获取”信号量的任务必须始终在不再需要信号量时“返回”信号量。
 *
 * 不能在中断服务例程中使用多路信号量。
 *
 * 请参阅xSemaphoreCreateBinary（），了解可用于纯同步（其中一个任务或中断总是“给出”信号量，另一个任务总是“获取”信号量）和中断服务例程内的另一种实现。
 *
 * @param pxStaticSemaphore 必须指向StaticSemaphore_t类型的变量，该变量随后将用于保存递归互斥体的数据结构，从而不需要动态分配内存。
 *
 * @return 如果成功创建了递归互斥体，则返回创建的递归互斥体的句柄。如果pxMutexBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 *  SemaphoreHandle_t x信号量；
 *  StaticSemaphore_t xMutexBuffer；
 *
 *  void vATask（void*pvParameters）
 *  {
 *     //递归信号量在创建之前不能使用。这里是
 *     //递归互斥体是使用xSemaphoreCreateRecursiveMutexStatic（）创建的。
 *     //xMutexBuffer的地址被传递到函数中
 *     //互斥锁数据结构-因此不会进行动态内存分配
 *     //尝试。
 *     xSemaphore=xSemaphereCreateRecursiveMutexStatic（&xMutexBuffer）；
 *
 *     //由于未执行动态内存分配，xSemaphore不能为NULL，
 *     //因此无需检查。
 *  }
 * @endcode \内部组信号
 */
#if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_RECURSIVE_MUTEXES == 1 ) )
    #define xSemaphoreCreateRecursiveMutexStatic( pxStaticSemaphore )    xQueueCreateMutexStatic( queueQUEUE_TYPE_RECURSIVE_MUTEX, pxStaticSemaphore )
#endif /* 配置支持状态分配*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * SemaphoreHandle_t xSemaphoreCreateCount（UBaseType_t uxMaxCount，UBaseType_t uxInitialCount）；
 * @endcode
 * @endcond
 *
 * 创建一个新的计数信号量实例，并返回一个可以引用新计数信号量的句柄。
 *
 * 在许多使用场景中，使用直接到任务通知代替计数信号量会更快、更节省内存！https://www.FreeRTOS.org/RTOS-task-notifications.html
 *
 * 在FreeRTOS实现内部，计数信号量使用一块内存，其中存储了计数信号量结构。如果使用xSemaphoreCreateCount（）创建计数信号量，则所需的内存将在xSemaphreCreateCount（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateCountingStatic（）创建计数信号量，那么应用程序编写器可以选择提供计数信号量将使用的内存。因此，xSemaphoreCreateCountingStatic（）允许在不使用任何动态内存分配的情况下创建计数信号量。
 *
 * 计数信号量通常用于两件事：
 *
 * 1） 计数事件。
 *
 *    在此使用场景中，事件处理程序将在每次事件发生时“发出”信号量（增加信号量计数值），而处理程序任务将在每次处理事件时“发出信号量”（减少信号量计值）。因此，计数值是已发生事件数与已处理事件数之间的差值。在这种情况下，期望初始计数值为零。
 *
 * 2） 资源管理。
 *
 *    在此使用场景中，计数值表示可用资源的数量。为了获得对资源的控制，任务必须首先获得一个信号量——递减信号量计数值。当计数值达到零时，没有可用资源。当一个任务用资源完成时，它会“返回”信号量——增加信号量计数值。在这种情况下，期望初始计数值等于最大计数值，指示所有资源都是空闲的。
 *
 * @param uxMaxCount 可以达到的最大计数值。当信号量达到这个值时，它就不能再被“给定”了。
 *
 * @param uxInitialCount 创建信号量时分配给它的计数值。
 *
 * @return 创建的信号量的句柄。如果无法创建信号量，则为空。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t x信号量；
 *
 * void vATask（void*pvParameters）
 * {
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 *  //在调用xSemaphoreCreateCount（）之前不能使用信号量。
 *  //信号量可计数的最大值应为10
 *  //分配给计数的初始值应为0。
 *  x信号量=x信号量创建计数（10，0）；
 *
 *  if（xSemaphore！=NULL）
 *  {
 *      //已成功创建信号量。
 *      //现在可以使用信号灯了。
 *  }
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreCreateCounting x SemaphoreCoreateCounting
 * @endcond \内部组信号
 */
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define xSemaphoreCreateCounting( uxMaxCount, uxInitialCount )    xQueueCreateCountingSemaphore( ( uxMaxCount ), ( uxInitialCount ) )
#endif

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * SemaphoreHandle_t xSemaphoreCreateCountingStatic（UBaseType_t uxMaxCount，UBaseType_t uxInitialCount，StaticSemaphore_t*pxSemaphoreBuffer）；
 * @endcode
 * @endcond
 *
 * 创建一个新的计数信号量实例，并返回一个可以引用新计数信号量的句柄。
 *
 * 在许多使用场景中，使用直接到任务通知代替计数信号量会更快、更节省内存！https://www.FreeRTOS.org/RTOS-task-notifications.html
 *
 * 在FreeRTOS实现内部，计数信号量使用一块内存，其中存储了计数信号量结构。如果使用xSemaphoreCreateCount（）创建计数信号量，则所需的内存将在xSemaphreCreateCount（）函数内自动动态分配。（参见https://www.FreeRTOS.org/a00111.html). 如果使用xSemaphoreCreateCountingStatic（）创建计数信号量，则应用程序编写器必须提供内存。因此，xSemaphoreCreateCountingStatic（）允许在不使用任何动态内存分配的情况下创建计数信号量。
 *
 * 计数信号量通常用于两件事：
 *
 * 1） 计数事件。
 *
 *    在此使用场景中，事件处理程序将在每次事件发生时“发出”信号量（增加信号量计数值），而处理程序任务将在每次处理事件时“发出信号量”（减少信号量计值）。因此，计数值是已发生事件数与已处理事件数之间的差值。在这种情况下，期望初始计数值为零。
 *
 * 2） 资源管理。
 *
 *    在此使用场景中，计数值表示可用资源的数量。为了获得对资源的控制，任务必须首先获得一个信号量——递减信号量计数值。当计数值达到零时，没有可用资源。当一个任务用资源完成时，它会“返回”信号量——增加信号量计数值。在这种情况下，期望初始计数值等于最大计数值，指示所有资源都是空闲的。
 *
 * @param uxMaxCount 可以达到的最大计数值。当信号量达到这个值时，它就不能再被“给定”了。
 *
 * @param uxInitialCount 创建信号量时分配给它的计数值。
 *
 * @param pxSemaphoreBuffer 必须指向StaticSemaphore_t类型的变量，然后该变量将用于保存信号量的数据结构，从而不需要动态分配内存。
 *
 * @return 如果成功创建了计数信号量，则返回创建的计数信号量的句柄。如果pxSemaphoreBuffer为NULL，则返回NULL。
 *
 * 示例用法：
 * @code{c}
 * SemaphoreHandle_t x信号量；
 * StaticSemaphore_t xSemaphoreBuffer；
 *
 * void vATask（void*pvParameters）
 * {
 * SemaphoreHandle_t xSemaphore=NULL；
 *
 *  //计数信号量在创建之前不能使用。创造
 *  //使用xSemaphoreCreateCountingStatic（）计算信号量。最大值
 *  //信号量可以计数的值为10，初始值为
 *  //分配给计数的值将为0。xSemaphoreBuffer的地址为
 *  //传入并将用于保存信号量结构，因此没有动态
 *  //将使用内存分配。
 *  xSemaphore=xSemaphoreCreateCount（10，0，&xSemapphoreBuffer）；
 *
 *  //未尝试内存分配，因此xSemaphore不能为NULL，因此
 *  //无需检查其值。
 * }
 * @endcode
 * @cond !DOC_SINGLE_GROUP\defgroup xSemaphoreCreateCountingStatic xSemaphoeCreateCountngStatic
 * @endcond \内部组信号
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    #define xSemaphoreCreateCountingStatic( uxMaxCount, uxInitialCount, pxSemaphoreBuffer )    xQueueCreateCountingSemaphoreStatic( ( uxMaxCount ), ( uxInitialCount ), ( pxSemaphoreBuffer ) )
#endif /* 配置支持状态分配*/

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION信号。小时
 * @code{c}
 * void vSemaphoreDelete（SemaphoreHandle_t xSemaphore）；
 * @endcode
 * @endcond
 *
 * 删除信号量。必须小心使用此功能。例如，如果互斥量由任务持有，则不要删除互斥量类型的信号量。
 *
 * @param xSemaphore 要删除的信号量的句柄。
 *
 * @cond !DOC_EXCLUDE_HEADER_SECTION\defgroup vSemaphoreDelete vSemaphoeDelete
 * @endcond \内部组信号
 */
#define vSemaphoreDelete( xSemaphore )                   vQueueDelete( ( QueueHandle_t ) ( xSemaphore ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION半小时
 * @code{c}
 * TaskHandle_t xSemaphoreGetMutexHolder（Semaphore_Handle_t xMultex）；
 * @endcode
 * @endcond
 *
 * 如果xMutex确实是互斥类型信号量，则返回当前互斥持有者。如果xMutex不是互斥类型信号量，或者互斥可用（不由任务持有），则返回NULL。
 *
 * 注意：这是确定调用任务是否是互斥锁持有者的一种好方法，但不是确定互斥锁持有者身份的好方法，因为持有者可能会在退出的函数和正在测试的返回值之间发生变化。
 */
#define xSemaphoreGetMutexHolder( xSemaphore )           xQueueGetMutexHolder( ( xSemaphore ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION半小时
 * @code{c}
 * TaskHandle_t xSemaphoreGetMutexHolderFromISR（Semaphore_Handle_t xMultex）；
 * @endcode
 * @endcond
 *
 * 如果xMutex确实是互斥类型信号量，则返回当前互斥持有者。如果xMutex不是互斥类型信号量，或者互斥可用（不由任务持有），则返回NULL。
 *
 */
#define xSemaphoreGetMutexHolderFromISR( xSemaphore )    xQueueGetMutexHolderFromISR( ( xSemaphore ) )

/**
 * @cond !DOC_EXCLUDE_HEADER_SECTION半小时
 * @code{c}
 * UBaseType_t uxSemaphoreGetCount（信号句柄_t x信号量）；
 * @endcode
 * @endcond
 *
 * 如果信号量是计数信号量，则uxSemaphoreGetCount（）返回其当前计数值。如果信号量是二进制信号量，则如果信号量可用，则uxSemaphoreGetCount（）返回1，如果信号量不可用，则返回0。
 *
 */
#define uxSemaphoreGetCount( xSemaphore )                uxQueueMessagesWaiting( ( QueueHandle_t ) ( xSemaphore ) )

#endif /* SEMAPHORE_H */

