// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef FREERTOS_RINGBUF_H
#define FREERTOS_RINGBUF_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h" must appear in source files before "include ringbuf.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <freertos/queue.h>

/**
 * 引用环形缓冲区的类型。例如，对xRingbufferCreate（）的调用返回一个RingbufHandle_t变量，该变量可以用作xRingbbufferSend（）、xRingbafterReceive（）等的参数。
 */
typedef void * RingbufHandle_t;

typedef enum {
    /**
     * 没有拆分缓冲区将只在连续内存中存储一个项目，并且永远不会拆分一个项目。每个项需要8字节的标头开销，并且始终在内部占用32位对齐大小的空间。
     */
    RINGBUF_TYPE_NOSPLIT = 0,
    /**
     * 允许拆分缓冲区将在必要时将项目拆分为两部分，以便存储它。每个项需要8字节的头开销，拆分会导致额外的头。每个项目将始终在内部占用32位对齐大小的空间。
     */
    RINGBUF_TYPE_ALLOWSPLIT,
    /**
     * 字节缓冲区将数据存储为字节序列，不维护单独的项，因此字节缓冲区没有开销。所有数据都存储为字节序列，每次可以发送或检索任意数量的字节。
     */
    RINGBUF_TYPE_BYTEBUF,
    RINGBUF_TYPE_MAX,
} RingbufferType_t;

/**
 * @brief 与环形缓冲区的数据结构大小相等的结构
 *
 * 此结构的内容不应直接使用。该结构用于创建静态分配的环形缓冲区，其中该结构具有存储环形缓冲区的控制数据结构所需的确切大小。
 *
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1)
typedef struct xSTATIC_RINGBUFFER {
    /**@秒*/    //Doxygen命令从API参考中隐藏此结构
    size_t xDummy1[2];
    UBaseType_t uxDummy2;
    BaseType_t xDummy3;
    void *pvDummy4[11];
    StaticSemaphore_t xDummy5[2];
    portMUX_TYPE muxDummy;
    /**@结束秒*/
} StaticRingbuffer_t;
#endif

/**
 * @brief       创建环形缓冲区
 *
 * @param[in]   xBufferSize 缓冲区的大小（字节）。请注意，在不拆分/允许拆分缓冲区中，项需要空间用于开销
 * @param[in]   xBufferType 环形缓冲区的类型，请参阅文档。
 *
 * @note    无拆分/允许拆分缓冲区的xBufferSize将舍入为最接近的32位对齐大小。
 *
 * @return  创建的环形缓冲区的句柄，如果出现错误，则为NULL。
 */
RingbufHandle_t xRingbufferCreate(size_t xBufferSize, RingbufferType_t xBufferType);

/**
 * @brief 为固定的item_size创建RINGBUF_type_NOSPLIT类型的环形缓冲区
 *
 * 此API类似于xRingbufferCreate（），但它将在内部为标头分配额外的空间。
 *
 * @param[in]   xItemSize   要放入环形缓冲区的每个项目的大小
 * @param[in]   xItemNum    缓冲区需要同时保存的最大项目数
 *
 * @return  创建的环形缓冲区的RingbufHandle_t句柄，如果出现错误，则为NULL。
 */
RingbufHandle_t xRingbufferCreateNoSplit(size_t xItemSize, size_t xItemNum);


/**
 * @brief       创建环形缓冲区，但手动提供所需的内存
 *
 * @param[in]   xBufferSize 缓冲区的大小（字节）。
 * @param[in]   xBufferType 环形缓冲区的类型，请参阅文档
 * @param[in]   pucRingbufferStorage 指向环形缓冲区存储区域的指针。存储区域的大小必须与xBufferSize指定的大小相同
 * @param[in]   pxStaticRingbuffer 指向StaticRingbuffer_t类型的结构，该结构将用于保存环形缓冲区的数据结构
 *
 * @note    无拆分/允许拆分缓冲区的xBufferSize必须是32位对齐的。
 *
 * @return  创建的环形缓冲区的句柄
 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1)
RingbufHandle_t xRingbufferCreateStatic(size_t xBufferSize,
                                        RingbufferType_t xBufferType,
                                        uint8_t *pucRingbufferStorage,
                                        StaticRingbuffer_t *pxStaticRingbuffer);
#endif

/**
 * @brief       将项目插入环形缓冲区
 *
 * 尝试将项目插入环形缓冲区。此函数将阻塞，直到有足够的可用空间或超时。
 *
 * @param[in]   xRingbuffer     将项目插入到的环形缓冲区
 * @param[in]   pvItem          指向要插入的数据的指针。如果xItemSize为0，则允许NULL。
 * @param[in]   xItemSize       要插入的数据大小。
 * @param[in]   xTicksToWait    勾选以等待环形缓冲区中的空间。
 *
 * @note    对于无拆分/允许拆分环形缓冲区，项目将占用的实际内存大小将四舍五入到最接近的32位对齐大小。这样做是为了确保所有项目始终以32位对齐的方式存储。
 *
 * @return
 *      -pdTRUE（如果成功）
 *      -pdFALSE超时或数据大于缓冲区的最大允许大小时
 */
BaseType_t xRingbufferSend(RingbufHandle_t xRingbuffer,
                           const void *pvItem,
                           size_t xItemSize,
                           TickType_t xTicksToWait);

/**
 * @brief       将项目插入ISR中的环形缓冲区
 *
 * 尝试从ISR将项目插入环形缓冲区。如果缓冲区中的可用空间不足，此函数将立即返回。
 *
 * @param[in]   xRingbuffer 将项目插入到的环形缓冲区
 * @param[in]   pvItem      指向要插入的数据的指针。如果xItemSize为0，则允许NULL。
 * @param[in]   xItemSize   要插入的数据大小。
 * @param[out]  pxHigherPriorityTaskWoken   如果函数唤醒了更高优先级的任务，则指向的值将设置为pdTRUE。
 *
 * @note    对于无拆分/允许拆分环形缓冲区，项目将占用的实际内存大小将四舍五入到最接近的32位对齐大小。这样做是为了确保所有项目始终以32位对齐的方式存储。
 *
 * @return
 *      -pdTRUE（如果成功）
 *      -当环形缓冲区没有空间时，pdFALSE。
 */
BaseType_t xRingbufferSendFromISR(RingbufHandle_t xRingbuffer,
                                  const void *pvItem,
                                  size_t xItemSize,
                                  BaseType_t *pxHigherPriorityTaskWoken);

/**
 * @brief 从环形缓冲区获取内存，以便由外部源写入并稍后发送。
 *
 * 尝试为要发送到环形缓冲区的项目分配缓冲区。此函数将阻塞，直到有足够的可用空间或超时。
 *
 * 该项以及其后的以下项“SendAcquire”或“Send”将无法从环形缓冲区中读取，直到该项实际发送到环形缓冲区。
 *
 * @param[in]   xRingbuffer     用于分配内存的环形缓冲区
 * @param[out]  ppvItem         已获取内存的双指针（如果未检索到内存，则设置为NULL）
 * @param[in]   xItemSize       要获取的项目的大小。
 * @param[in]   xTicksToWait    勾选以等待环形缓冲区中的空间。
 *
 * @note 现在仅适用于无拆分环形缓冲区，项目将占用的实际内存大小将四舍五入到最接近的32位对齐大小。这样做是为了确保所有项目始终以32位对齐的方式存储。
 *
 * @return
 *      -pdTRUE（如果成功）
 *      -pdFALSE超时或数据大于缓冲区的最大允许大小时
 */
BaseType_t xRingbufferSendAcquire(RingbufHandle_t xRingbuffer, void **ppvItem, size_t xItemSize, TickType_t xTicksToWait);

/**
 * @brief       实际上，将项目发送到之前由“xRingbufferSendAcquire”分配的环形缓冲区中。
 *
 * @param[in]   xRingbuffer     将项目插入到的环形缓冲区
 * @param[in]   pvItem          指向要插入的已分配内存中的项的指针。
 *
 * @note 仅适用于无拆分环形缓冲区。仅调用“xRingbufferSendAcquire”分配的项目。
 *
 * @return
 *      -pdTRUE（如果成功）
 *      -pdFALSE，如果由于某种原因失败。
 */
BaseType_t xRingbufferSendComplete(RingbufHandle_t xRingbuffer, void *pvItem);

/**
 * @brief   从环形缓冲区检索项目
 *
 * 尝试从环形缓冲区中检索项。此功能将阻止，直到项目可用或超时。
 *
 * @param[in]   xRingbuffer     从中检索项目的环形缓冲区
 * @param[out]  pxItemSize      指向将写入检索项大小的变量的指针。
 * @param[in]   xTicksToWait    勾选以等待环形缓冲区中的项目。
 *
 * @note    之后需要调用vRingbufferReturnItem（）以释放检索到的项。
 *
 * @return
 *      -成功时指向检索项的指针*pxItemSize填充项目的长度。
 *      -超时时为NULL，在这种情况下，*pxItemSize不受影响。
 */
void *xRingbufferReceive(RingbufHandle_t xRingbuffer, size_t *pxItemSize, TickType_t xTicksToWait);

/**
 * @brief   从ISR中的环形缓冲区检索项目
 *
 * 尝试从环形缓冲区中检索项。如果没有可供检索的项目，此函数将立即返回
 *
 * @param[in]   xRingbuffer     从中检索项目的环形缓冲区
 * @param[out]  pxItemSize      指向将写入检索项大小的变量的指针。
 *
 * @note    之后需要调用vRingbufferReturnItemFromISR（）以释放检索到的项。
 * @note    字节缓冲区不允许在返回项之前进行多次检索
 * @note    如果字节环绕环形缓冲区的结尾，则需要对RingbufferReceiveFromISR（）进行两次调用。
 *
 * @return
 *      -成功时指向检索项的指针*pxItemSize填充项目的长度。
 *      -当环形缓冲区为空时为NULL，在这种情况下*pxItemSize不受影响。
 */
void *xRingbufferReceiveFromISR(RingbufHandle_t xRingbuffer, size_t *pxItemSize);

/**
 * @brief   从允许拆分的环形缓冲区中检索拆分项
 *
 * 尝试从允许拆分环缓冲区中检索拆分项。如果项目未拆分，则只重试单个项目。如果项目被拆分，将检索两个部分。此功能将阻止，直到项目可用或超时。
 *
 * @param[in]   xRingbuffer     从中检索项目的环形缓冲区
 * @param[out]  ppvHeadItem     指向第一部分的双指针（如果未检索到任何项，则设置为NULL）
 * @param[out]  ppvTailItem     指向第二部分的双指针（如果项目未拆分，则设置为NULL）
 * @param[out]  pxHeadItemSize  指向第一部分大小的指针（如果未检索到任何项，则未修改）
 * @param[out]  pxTailItemSize  指向第二部分大小的指针（如果项目未拆分，则未修改）
 * @param[in]   xTicksToWait    勾选以等待环形缓冲区中的项目。
 *
 * @note    在此之后，需要调用vRingbufferReturnItem（）以释放检索到的项。
 * @note    只能在允许拆分缓冲区时调用此函数
 *
 * @return
 *      -pdTRUE，如果检索到项（拆分或未拆分）
 *      -未检索到项目时pdFALSE
 */
BaseType_t xRingbufferReceiveSplit(RingbufHandle_t xRingbuffer,
                                   void **ppvHeadItem,
                                   void **ppvTailItem,
                                   size_t *pxHeadItemSize,
                                   size_t *pxTailItemSize,
                                   TickType_t xTicksToWait);

/**
 * @brief   从ISR中的允许拆分环缓冲区中检索拆分项
 *
 * 尝试从允许拆分环缓冲区中检索拆分项。如果项目未拆分，则只重试单个项目。如果项目被拆分，将检索两个部分。如果没有可供检索的项目，此函数将立即返回
 *
 * @param[in]   xRingbuffer     从中检索项目的环形缓冲区
 * @param[out]  ppvHeadItem     指向第一部分的双指针（如果未检索到任何项，则设置为NULL）
 * @param[out]  ppvTailItem     指向第二部分的双指针（如果项目未拆分，则设置为NULL）
 * @param[out]  pxHeadItemSize  指向第一部分大小的指针（如果未检索到任何项，则未修改）
 * @param[out]  pxTailItemSize  指向第二部分大小的指针（如果项目未拆分，则未修改）
 *
 * @note    在此之后，需要调用vRingbufferReturnItemFromISR（）以释放检索到的项。
 * @note    只能在允许拆分缓冲区时调用此函数
 *
 * @return
 *      -pdTRUE，如果检索到项（拆分或未拆分）
 *      -未检索到项目时pdFALSE
 */
BaseType_t xRingbufferReceiveSplitFromISR(RingbufHandle_t xRingbuffer,
                                          void **ppvHeadItem,
                                          void **ppvTailItem,
                                          size_t *pxHeadItemSize,
                                          size_t *pxTailItemSize);

/**
 * @brief   从字节缓冲区检索字节，指定要检索的最大字节数
 *
 * 尝试从字节缓冲区检索数据，同时指定要检索的最大字节数。此函数将一直阻塞，直到有数据可供检索或超时。
 *
 * @param[in]   xRingbuffer     从中检索项目的环形缓冲区
 * @param[out]  pxItemSize      指向将写入检索项大小的变量的指针。
 * @param[in]   xTicksToWait    勾选以等待环形缓冲区中的项目。
 * @param[in]   xMaxSize        要返回的最大字节数。
 *
 * @note    之后需要调用vRingbufferReturnItem（）以释放检索到的数据。
 * @note    只能在字节缓冲区上调用此函数
 * @note    字节缓冲区不允许在返回项之前进行多次检索
 * @note    如果字节环绕环形缓冲区的结尾，则需要两次调用RingbufferReceiveUpTo（）。
 *
 * @return
 *      -成功时指向检索项的指针*pxItemSize填充项目的长度。
 *      -超时时为NULL，在这种情况下，*pxItemSize不受影响。
 */
void *xRingbufferReceiveUpTo(RingbufHandle_t xRingbuffer,
                             size_t *pxItemSize,
                             TickType_t xTicksToWait,
                             size_t xMaxSize);

/**
 * @brief   从字节缓冲区检索字节，指定要检索的最大字节数。从ISR中调用。
 *
 * 尝试从字节缓冲区中检索字节，同时指定要检索的最大字节数。如果没有可供检索的数据，此函数将立即返回。
 *
 * @param[in]   xRingbuffer 从中检索项目的环形缓冲区
 * @param[out]  pxItemSize  指向将写入检索项大小的变量的指针。
 * @param[in]   xMaxSize    要返回的最大字节数。
 *
 * @note    之后需要调用vRingbufferReturnItemFromISR（）以释放接收的数据。
 * @note    只能在字节缓冲区上调用此函数
 * @note    字节缓冲区不允许在返回项之前进行多次检索
 *
 * @return
 *      -成功时指向检索项的指针*pxItemSize填充项目的长度。
 *      -当环形缓冲区为空时为NULL，在这种情况下*pxItemSize不受影响。
 */
void *xRingbufferReceiveUpToFromISR(RingbufHandle_t xRingbuffer, size_t *pxItemSize, size_t xMaxSize);

/**
 * @brief   将以前检索的项目返回到环形缓冲区
 *
 * @param[in]   xRingbuffer 从中检索项目的环形缓冲区
 * @param[in]   pvItem      之前收到的项目
 *
 * @note    如果检索到拆分项，则应通过调用此函数两次来返回这两个部分
 */
void vRingbufferReturnItem(RingbufHandle_t xRingbuffer, void *pvItem);

/**
 * @brief   将以前从ISR检索到的项目返回到环形缓冲区
 *
 * @param[in]   xRingbuffer 从中检索项目的环形缓冲区
 * @param[in]   pvItem      之前收到的项目
 * @param[out]  pxHigherPriorityTaskWoken   如果函数唤醒了更高优先级的任务，则指向的值将设置为pdTRUE。
 *
 * @note    如果检索到拆分项，则应通过调用此函数两次来返回这两个部分
 */
void vRingbufferReturnItemFromISR(RingbufHandle_t xRingbuffer, void *pvItem, BaseType_t *pxHigherPriorityTaskWoken);

/**
 * @brief   删除环形缓冲区
 *
 * @param[in]   xRingbuffer     要删除的环形缓冲区
 *
 * @note    如果使用xRingbufferCreateStatic（）创建环形缓冲区，则此函数不会释放任何内存。取消分配必须由用户手动完成。
 */
void vRingbufferDelete(RingbufHandle_t xRingbuffer);

/**
 * @brief   获取可放置在环形缓冲区中的项目的最大大小
 *
 * 此函数返回项目放置在空环形缓冲区中时可以具有的最大大小。
 *
 * @param[in]   xRingbuffer     要查询的环形缓冲区
 *
 * @note    无拆分缓冲区的最大项目大小限制为（（buffer_size/2）-header_size）。施加此限制，以便无论缓冲区的读/写/自由指针的内部位置如何，最大项目大小的项目始终可以发送到空的无拆分缓冲区。
 *
 * @return  可以放置在环形缓冲区中的项的最大大小（以字节为单位）。
 */
size_t xRingbufferGetMaxItemSize(RingbufHandle_t xRingbuffer);

/**
 * @brief   获取缓冲区中项目/数据的当前可用大小
 *
 * 这为环形缓冲区中的项目/数据提供了实时可用空间。这表示项目/数据当前发送到环形缓冲区时可以具有的最大大小。
 *
 * @warning 此API不是线程安全的。因此，如果多个线程正在访问同一个环形缓冲区，则应用程序有责任确保对该API和后续发送的原子访问
 *
 * @note    空的无拆分缓冲区的最大当前可用大小限制为（（buffer_size/2）-header_size）。请参阅xRingbufferGetMaxItemSize（）的API参考。
 *
 * @param[in]   xRingbuffer     要查询的环形缓冲区
 *
 * @return  条目可用的当前可用大小（字节）
 */
size_t xRingbufferGetCurFreeSize(RingbufHandle_t xRingbuffer);

/**
 * @brief   将环形缓冲区的读信号量添加到队列集。
 *
 * 环形缓冲区的读信号指示数据已写入环形缓冲区。此函数将环形缓冲区的读信号量添加到队列集。
 *
 * @param[in]   xRingbuffer     要添加到队列集的环形缓冲区
 * @param[in]   xQueueSet       将环形缓冲区的读信号量添加到的队列集
 *
 * @return
 *      -成功时为pdTRUE，否则为pdFALSE
 */
BaseType_t xRingbufferAddToQueueSetRead(RingbufHandle_t xRingbuffer, QueueSetHandle_t xQueueSet);


/**
 * @brief   检查所选队列集成员是否为环形缓冲区的读信号量
 *
 * 此API检查从xQueueSelectFromSet（）返回的队列集成员是否是此环形缓冲区的读取信号量。如果是，则表示环形缓冲区有等待检索的项。
 *
 * @param[in]   xRingbuffer     应检查的环形缓冲区
 * @param[in]   xMember         从xQueueSelectFromSet返回的成员
 *
 * @return
 *      -pdTRUE，当信号属于环形缓冲区时
 *      -否则为pdFALSE。
 */
BaseType_t xRingbufferCanRead(RingbufHandle_t xRingbuffer, QueueSetMemberHandle_t xMember);

/**
 * @brief   从队列集中删除环形缓冲区的读信号量。
 *
 * 这特别是从队列集中删除环形缓冲区的读信号量。读取信号量用于指示数据何时已写入环形缓冲区
 *
 * @param[in]   xRingbuffer     要从队列集中删除的环形缓冲区
 * @param[in]   xQueueSet       队列设置为从中删除环形缓冲区的读信号量
 *
 * @return
 *      -成功时pdTRUE
 *      -pdFALSE否则
 */
BaseType_t xRingbufferRemoveFromQueueSetRead(RingbufHandle_t xRingbuffer, QueueSetHandle_t xQueueSet);

/**
 * @brief   获取有关环形缓冲区状态的信息
 *
 * 获取环形缓冲区的当前状态信息，例如空闲/读/写指针位置，以及等待检索的项目数。如果不需要参数，则可以将其设置为NULL。
 *
 * @param[in]   xRingbuffer     要从队列集中删除的环形缓冲区
 * @param[out]  uxFree          用于存储自由指针位置的指针
 * @param[out]  uxRead          用于存储读取指针位置的指针
 * @param[out]  uxWrite         用于存储写指针位置的指针
 * @param[out]  uxAcquire       用于存储获取指针位置的指针
 * @param[out]  uxItemsWaiting  用于存储等待检索的项目数（字节缓冲区的字节数）的指针
 */
void vRingbufferGetInfo(RingbufHandle_t xRingbuffer,
                        UBaseType_t *uxFree,
                        UBaseType_t *uxRead,
                        UBaseType_t *uxWrite,
                        UBaseType_t *uxAcquire,
                        UBaseType_t *uxItemsWaiting);

/**
 * @brief   调试函数以打印环形缓冲区中的内部指针
 *
 * @param   xRingbuffer 要显示的环形缓冲区
 */
void xRingbufferPrintInfo(RingbufHandle_t xRingbuffer);

#ifdef __cplusplus
}
#endif

#endif /* FREERTOS_RINGBUF_H */

