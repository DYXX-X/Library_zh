/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread TCP API。
 *
 */

#ifndef OPENTHREAD_TCP_H_
#define OPENTHREAD_TCP_H_

#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api tcp
 *
 * @brief 该模块包括控制TCP通信的功能。
 *
 * @{
 *
 */

/**
 * 用于TCP的链接缓冲区结构。
 *
 * 单个otLinkedBuffer结构通过mData和mLength引用内存中的字节数组。mNext字段用于形成otLinkedBuffer结构链。
 *
 */
typedef struct otLinkedBuffer
{
    struct otLinkedBuffer *mNext;   ///<指向链中下一个链接缓冲区的指针，如果是结尾，则为NULL。
    const uint8_t *        mData;   ///<指向此链接缓冲区引用的数据的指针。
    uint16_t               mLength; ///<此链接缓冲区的长度（字节数）。
} otLinkedBuffer;

struct otTcpEndpoint;
typedef struct otTcpEndpoint otTcpEndpoint;

/**
 * 此回调通知应用程序TCP三向握手已完成，连接现在已建立。
 *
 * @param[in]  aEndpoint  现在已建立连接的TCP端点。
 *
 */
typedef void (*otTcpEstablished)(otTcpEndpoint *aEndpoint);

/**
 * 此回调通知应用程序
 * @p aData已被连接对等方确认，并且@p aData及其包含的数据可以由应用程序回收。
 *
 * The @p aData保证与通过otTcpSendByReference（）传递到TCP的数据相同，包括通过otTcpSendByExtension（）实现的任何扩展。
 *
 * @param[in]  aEndpoint  连接的TCP端点。
 * @param[in]  aData      指向可回收的otLinkedBuffer的指针。
 *
 */
typedef void (*otTcpSendDone)(otTcpEndpoint *aEndpoint, otLinkedBuffer *aData);

/**
 * This callback informs the application that the first @p 发送缓冲区中的aNumBytes已被连接对等体确认，并且应用程序可以回收其底层内存。
 *
 * 正确的TCP操作不需要此回调。大多数应用程序只能依赖otTcpSendDone（）回调。如果应用程序希望在发送缓冲区中的内存再次可用时（而不是等待整个链接缓冲区的数据变得可用）或在连接是否正在向前进展时获得细粒度反馈，则可以注册此回调。
 *
 * @param[in]  aEndpoint  连接的TCP端点。
 * @param[in]  aNumBytes  连接对等方新确认的字节数。
 *
 */
typedef void (*otTcpBytesAcked)(otTcpEndpoint *aEndpoint, size_t aNumBytes);

/**
 * 此回调通知应用程序，如果将数据添加到发送缓冲区，则其中一些数据将立即传输，而不会延迟，而不是在对等方确认某些数据后排队等待传输。
 *
 * 在调用otTcpSendByReference（）或otTcpSendByExtension（）后，保证立即（如果连接已经就绪）或将来某个时候（一旦连接准备好接收更多数据）调用otTcpSendReady（）回调。
 *
 * 正确的TCP操作不需要此回调。如果添加到发送缓冲区的数据超过了可以无延迟传输的数据量，则只需将其排队等待稍后传输。仅当需要确保添加到发送缓冲区的数据将很快被发送时（例如，TCP不会在发送该数据之前等待接收方先确认其他数据），才应使用此回调。例如，如果您希望数据被丢弃，而不是在发送缓冲区中生成积压数据，则可以使用此回调。但对于大多数应用程序来说，如果这不是一个问题，预计根本不会使用此回调。
 *
 * @param[in]  aEndpoint  连接的TCP端点。
 *
 */
typedef void (*otTcpSendReady)(otTcpEndpoint *aEndpoint);

/**
 * 此回调指示接收缓冲区中可供使用的字节数。
 *
 * 每当字节被添加到接收缓冲区以及到达流的结尾时，都会调用它。如果已到达流的结尾（即，如果由于连接对等方已关闭其连接的结尾以进行写入，因此不再有数据可供读取），则@p aEndOfStream为
 * true. Finally, @p aBytesRemaining表示接收缓冲区中剩余多少容量以容纳到达的附加数据。
 *
 * @param[in]  aEndpoint        连接的TCP端点。
 * @param[in]  aBytesAvailable  连接的接收缓冲区中的字节数。
 * @param[in]  aEndOfStream     指示是否可以接收连接的接收缓冲区中已存在的数据之外的其他数据。
 * @param[in]  aBytesRemaining  在接收缓冲区变满之前可以接收的附加字节数。
 *
 */
typedef void (*otTcpReceiveAvailable)(otTcpEndpoint *aEndpoint,
                                      size_t         aBytesAvailable,
                                      bool           aEndOfStream,
                                      size_t         aBytesRemaining);

typedef enum otTcpDisconnectedReason
{
    OT_TCP_DISCONNECTED_REASON_NORMAL,
    OT_TCP_DISCONNECTED_REASON_REFUSED,
    OT_TCP_DISCONNECTED_REASON_RESET,
    OT_TCP_DISCONNECTED_REASON_TIME_WAIT,
    OT_TCP_DISCONNECTED_REASON_TIMED_OUT,
} otTcpDisconnectedReason;

/**
 * 此回调表示连接已断开，不应再使用，或者连接已进入TIME-WAIT状态。
 *
 * 如果连接建立尝试（通过调用otTcpConnect（）启动）失败，或之后的任何时间点（例如，如果连接超时或从连接对等端接收到RST段），则可能发生这种情况。一旦此回调触发，应用程序为此连接提供的所有资源（即，任何“otLinkedBuffers”及其引用的内存，但不包括TCP端点本身或接收缓冲区的空间）都可以回收。在连接进入TIME-WAIT状态的情况下，该回调将被调用两次，一次是进入TIME-WAIT状态时（使用OT_TCP_DISCONNECTED_REASON_TIME_WAIT），另一次是在TIME-WAIT状态到期时（使用OTS_TCP_DDISCONNECTEd_REASON_NORMAL）。
 *
 * @param[in]  aEndpoint  连接已丢失的TCP终结点。
 * @param[in]  aReason    连接丢失的原因。
 *
 */
typedef void (*otTcpDisconnected)(otTcpEndpoint *aEndpoint, otTcpDisconnectedReason aReason);

/**
 * 此结构表示TCP端点。
 *
 * TCP端点充当TCP连接的端点。它可以用于启动TCP连接，一旦建立了TCP连接，就可以向连接对等端发送数据和从连接对等端接收数据。
 *
 * 应用程序不应直接检查此结构的字段；它应该仅通过TCP API函数与其交互，该函数的签名在该文件中提供。
 *
 */
struct otTcpEndpoint
{
    struct otTcpEndpoint *mNext;     ///<指向下一个TCP端点的指针（仅限内部使用）
    otInstance *          mInstance; ///<指向与此TCP终结点关联的OpenThread实例的指针
    void *                mContext;  ///<指向应用程序特定上下文的指针

    otTcpEstablished      mEstablishedCallback;      ///<“已建立”回调函数
    otTcpSendDone         mSendDoneCallback;         ///<“发送完成”回调函数
    otTcpSendReady        mSendReadyCallback;        ///<“发送就绪”回调函数
    otTcpReceiveAvailable mReceiveAvailableCallback; ///<“接收可用”回调函数
    otTcpDisconnected     mDisconnectedCallback;     ///<“Disconnected”回调函数

    uint32_t mTimers[4];

    /* 此处显示其他实现定义的字段。*/
};

/**
 * 此结构包含otTcpEndpointInitialize（）函数的参数。
 *
 */
typedef struct otTcpEndpointInitializeArgs
{
    void *mContext; ///<指向应用程序特定上下文的指针

    otTcpEstablished      mEstablishedCallback;      ///<“已建立”回调函数
    otTcpSendDone         mSendDoneCallback;         ///<“发送完成”回调函数
    otTcpBytesAcked       mBytesAckedCallback;       ///<“已确认字节数”回调
    otTcpSendReady        mSendReadyCallback;        ///<“发送就绪”回调函数
    otTcpReceiveAvailable mReceiveAvailableCallback; ///<“接收可用”回调函数
    otTcpDisconnected     mDisconnectedCallback;     ///<“Disconnected”回调函数

    void * mReceiveBuffer;     ///<指向为TCP接收缓冲区提供给系统的内存的指针
    size_t mReceiveBufferSize; ///<为TCP接收缓冲区提供给系统的内存大小
} otTcpEndpointInitializeArgs;

/**
 * @def OT_TCP_RECEIVE_BUFFER_SIZE_FEW_HOPS
 *
 * 对于穿越约3个无线跃点或更少的TCP连接，建议使用缓冲区大小。
 *
 * 在内存特别受限的平台上，在不需要高带宽的情况下，可能需要手动选择较小的缓冲区大小。
 *
 */
#define OT_TCP_RECEIVE_BUFFER_SIZE_FEW_HOPS 2599

/**
 * @def OT_TCP_RECEIVE_BUFFER_SIZE_MANY_HOPS
 *
 * 建议的TCP连接的缓冲区大小，该连接可以通过许多无线跃点。
 *
 * 如果TCP连接经过非常多的跳数（超过6个左右），则建议手动选择大的缓冲区大小。
 *
 */
#define OT_TCP_RECEIVE_BUFFER_SIZE_MANY_HOPS 4158

/**
 * 初始化TCP终结点。
 *
 * 调用此函数会导致OpenThread跟踪TCP端点，并在@paEndpoint中存储和检索TCP数据。应用程序应避免直接访问或修改
 * @p a端点。如果应用程序需要回收内存备份
 * @p aEndpoint，它应该调用otTcpEndpointDeinitialize（）。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aEndpoint  指向TCP端点结构的指针。
 * @param[in]  aArgs      指向参数结构的指针。
 *
 * @retval OT_ERROR_NONE已成功打开TCP终结点。
 * @retval OT_ERROR_FAILED无法打开TCP终结点。
 *
 */
otError otTcpEndpointInitialize(otInstance *aInstance, otTcpEndpoint *aEndpoint, otTcpEndpointInitializeArgs *aArgs);

/**
 * 获取初始化时与@p aEndpoint关联的otInstance。
 *
 * @param[in]  aEndpoint  要获取其实例的TCP端点。
 *
 * @returns  与@p aEndpoint关联的otInstance指针。
 *
 */
otInstance *otTcpEndpointGetInstance(otTcpEndpoint *aEndpoint);

/**
 * 获取初始化时与@p aEndpoint关联的上下文指针。
 *
 * @param[in]  aEndpoint  要获取其上下文的TCP终结点。
 *
 * @returns  与@p aEndpoint关联的上下文指针。
 *
 */
void *otTcpEndpointGetContext(otTcpEndpoint *aEndpoint);

/**
 * 获取指向TCP端点的本地主机和端口的指针。
 *
 * 如果此套接字未处于连接状态，并且在上次断开连接后未绑定，则主机和端口的内容可能已过时。
 *
 * @param[in]  aEndpoint  要获取其本地主机和端口的TCP端点。
 *
 * @returns  @p aEndpoint的本地主机和端口。
 *
 */
const otSockAddr *otTcpGetLocalAddress(const otTcpEndpoint *aEndpoint);

/**
 * 获取指向TCP端点的对等端主机和端口的指针。
 *
 * 如果此套接字未处于连接状态，则主机和端口的内容可能已过时。
 *
 * @param[in]  aEndpoint  要获取其对等端的主机和端口的TCP端点。
 *
 * @returns  @p aEndpoint的连接对等端的主机和端口。
 *
 */
const otSockAddr *otTcpGetPeerAddress(const otTcpEndpoint *aEndpoint);

/**
 * 将TCP端点绑定到IP地址和端口。
 *
 * @param[in]  aEndpoint   指向要绑定的TCP端点结构的指针。
 * @param[in]  aSockName   要绑定此TCP终结点的地址和端口。
 *
 * @retval OT_ERROR_NONE已成功绑定TCP终结点。
 * @retval OT_ERROR_FAILED无法绑定TCP终结点。
 *
 */
otError otTcpBind(otTcpEndpoint *aEndpoint, const otSockAddr *aSockName);

/**
 * 此枚举定义传递给otTcpConnect（）的标志。
 *
 */
enum
{
    OT_TCP_CONNECT_NO_FAST_OPEN = 1 << 0,
};

/**
 * 记录此连接的远程主机和端口。
 *
 * 默认情况下，使用TCP Fast Open。这意味着该函数仅记录远程主机和端口，TCP连接建立握手仅在第一次调用otTcpSendByReference（）时发生。可以使用@p aFlags显式禁用TCP快速打开，在这种情况下，立即启动TCP连接建立握手。
 *
 * @param[in]  aEndpoint  指向要连接的TCP端点结构的指针。
 * @param[in]  aSockName  要连接到的主机的IP地址和端口。
 * @param[in]  aFlags     指定此操作选项的标志（请参阅上面的枚举）。
 *
 * @retval OT_ERROR_NONE已成功完成操作。
 * @retval OT_ERROR_FAILED无法完成操作。
 *
 */
otError otTcpConnect(otTcpEndpoint *aEndpoint, const otSockAddr *aSockName, uint32_t aFlags);

/**
 * 此枚举定义传递给@p otTcpSendByReference的标志。
 *
 */
enum
{
    OT_TCP_SEND_MORE_TO_COME = 1 << 0,
};

/**
 * 将@p aBuffer指向的链接缓冲区引用的数据添加到发送缓冲区。
 *
 * 成功调用此函数后，链接缓冲区及其引用的数据归TCP堆栈所有；在“send-done”回调将这些对象的所有权返回给应用程序之前，应用程序不应修改这些对象。调用此函数将另一个链接缓冲区添加到发送队列是可以接受的，即使之前调用此函数的“send-done”回调尚未触发。
 *
 * Note that @p a缓冲器不应被锁住；其mNext字段应为NULL。如果在此调用后立即添加其他数据，则应使用OT_TCP_SEND_MORE_TO_COME标志作为TCP实现的提示。
 *
 * @param[in]  aEndpoint  指向TCP端点结构的指针，表示要在其上发送数据的TCP端点。
 * @param[in]  aBuffer    指向链接缓冲区链的指针，引用要添加到发送缓冲区的数据。
 * @param[in]  aFlags     指定此操作选项的标志（请参阅上面的枚举）。
 *
 * @retval OT_ERROR_NONE已成功将数据添加到发送缓冲区。
 * @retval OT_ERROR_FAILED无法将数据添加到发送缓冲区。
 *
 */
otError otTcpSendByReference(otTcpEndpoint *aEndpoint, otLinkedBuffer *aBuffer, uint32_t aFlags);

/**
 * 通过将发送缓冲区中的最终otLinkedBuffer的长度延长指定的长度，将数据添加到发送缓冲区。
 *
 * 如果发送缓冲区为空，则操作失败。
 *
 * @param[in]  aEndpoint  指向TCP端点结构的指针，表示要在其上发送数据的TCP端点。
 * @param[in]  aNumBytes  用于扩展最终链接缓冲区长度的字节数。
 * @param[in]  aFlags     指定此操作选项的标志（请参阅上面的枚举）。
 *
 * @retval OT_ERROR_NONE已成功将数据添加到发送缓冲区。
 * @retval OT_ERROR_FAILED无法将数据添加到发送缓冲区。
 *
 */
otError otTcpSendByExtension(otTcpEndpoint *aEndpoint, size_t aNumBytes, uint32_t aFlags);

/**
 * 为应用程序提供引用TCP接收缓冲区中当前数据的链接缓冲区链。
 *
 * 链接的缓冲链在下一次调用“receive ready”回调之前有效，或者在下一个调用otTcpReceiveContiguify（）或otTcpCommitReceive（）之前有效。
 *
 * @param[in]   aEndpoint  指向TCP端点结构的指针，表示要在其上接收数据的TCP端点。
 * @param[out]  aBuffer    指向链接缓冲区链的指针，引用当前接收缓冲区中的数据。
 *
 * @retval OT_ERROR_NONE已成功完成操作。
 * @retval OT_ERROR_FAILED无法完成操作。
 *
 */
otError otTcpReceiveByReference(const otTcpEndpoint *aEndpoint, const otLinkedBuffer **aBuffer);

/**
 * 重新组织接收缓冲区，使其在内存中完全连续。
 *
 * 这是可选的；应用程序可以简单地遍历链接缓冲区
 * chain obtained by calling @p otTcpReceiveByReference。一些应用程序可能希望调用此函数以使接收缓冲区邻接以简化其数据处理，但这是以CPU时间为代价的，以重新组织接收缓冲区中的数据。
 *
 * @param[in]   aEndpoint  指向要重新组织其接收缓冲区的TCP端点的指针。
 *
 * @retval OT_ERROR_NONE已成功完成操作。
 * @retval OT_ERROR_FAILED无法完成操作。
 *
 */
otError otTcpReceiveContiguify(otTcpEndpoint *aEndpoint);

/**
 * 通知TCP堆栈应用程序已完成处理
 * @p aNumBytes字节的数据，并且TCP堆栈不需要继续在接收缓冲区中维护这些字节。
 *
 * @param[in]  aEndpoint  指向TCP端点结构的指针，表示要在其上接收数据的TCP端点。
 * @param[in]  aNumBytes  消耗的字节数。
 * @param[in]  aFlags     指定此操作选项的标志（尚未设置）。
 *
 * @retval OT_ERROR_NONE已成功完成接收操作。
 * @retval OT_ERROR_FAILED无法完成接收操作。
 *
 */
otError otTcpCommitReceive(otTcpEndpoint *aEndpoint, size_t aNumBytes, uint32_t aFlags);

/**
 * 通知连接对等方此TCP端点将不会发送更多数据。
 *
 * 当应用程序没有更多数据要发送到连接对等端时，应使用此选项。对于此连接，连接对等端上的未来读取将导致“流结束”情况，而此连接端点上的未来写入将失败。
 *
 * “流结束”条件仅在连接对等方接收到之前提供给TCP堆栈以发送的任何数据后适用。
 *
 * @param[in]  aEndpoint  指向TCP端点结构的指针，表示要关闭的TCP端点。
 *
 * @retval OT_ERROR_NONE已成功将传输的“流结束”条件排入队列。
 * @retval OT_ERROR_FAILED未能将传输的“流结束”条件排队。
 *
 */
otError otTcpSendEndOfStream(otTcpEndpoint *aEndpoint);

/**
 * 强制结束与此TCP终结点关联的TCP连接。
 *
 * 这将立即使TCP端点可供另一个连接使用，并清空发送和接收缓冲区，从而将应用程序在otTcpSendByReferences（）调用中提供的任何数据的所有权转移回应用程序。TCP端点的回调和接收缓冲区的内存与TCP端点保持关联。
 *
 * @param[in]  aEndpoint  指向TCP端点结构的指针，表示要中止的TCP端点。
 *
 * @retval OT_ERROR_NONE已成功中止TCP终结点的连接。
 * @retval OT_ERROR_FAILED无法中止TCP终结点的连接。
 *
 */
otError otTcpAbort(otTcpEndpoint *aEndpoint);

/**
 * 取消初始化此TCP终结点。
 *
 * 这意味着OpenThread不再跟踪此TCP端点，并释放其内部为此TCP端点分配的所有资源。应用程序可以根据需要重用支持TCP端点的内存。
 *
 * 如果它对应于实时TCP连接，则该连接将不确定地终止（如otTcpAbort（））。应用程序为此TCP端点提供的所有资源（发送缓冲区的链接缓冲区、内存
 * for the receive buffer, the @p 端点结构本身等）立即返回到应用程序。
 *
 * @param[in]  aEndpoint  指向要取消初始化的TCP端点结构的指针。
 *
 * @retval OT_ERROR_NONE已成功取消初始化TCP终结点。
 * @retval OT_ERROR_FAILED无法取消初始化TCP终结点。
 *
 */
otError otTcpEndpointDeinitialize(otTcpEndpoint *aEndpoint);

struct otTcpListener;
typedef struct otTcpListener otTcpListener;

/**
 * 此枚举定义传入连接操作。
 *
 * 这在otTcpAcceptReady（）回调中使用。
 *
 */
typedef enum otTcpIncomingConnectionAction
{
    OT_TCP_INCOMING_CONNECTION_ACTION_ACCEPT, ///<接受传入连接。
    OT_TCP_INCOMING_CONNECTION_ACTION_DEFER,  ///<延迟（忽略）传入连接。
    OT_TCP_INCOMING_CONNECTION_ACTION_REFUSE, ///<拒绝传入连接。
} otTcpIncomingConnectionAction;

/**
 * 此回调表示已到达与此TCP侦听器匹配的传入连接。
 *
 * The typical response is for the application to accept the incoming connection. It does so by populating @p aAcceptInto，带有指向要接受传入连接的otTcpEndpoint的指针。此otTcpEndpoint必须已使用otTcpEndpointInitialize（）初始化。然后，应用程序返回OT_TCP_INCOMING_CONNECTION_ACTION_ACCEPT。
 *
 * 或者，应用程序可以拒绝接受传入连接。应用程序有两种方法可以做到这一点。首先，如果应用程序返回OT_TCP_INCOMING_CONNECTION_ACTION_DEFER，则OpenThread会自动忽略连接建立请求；连接对等方可能会重新发送请求，此时将再次调用回调。如果资源当前不可用于接受连接，则这是有价值的，但当连接对等体重新发送其连接建立尝试时，这些资源可能可用。其次，如果应用程序返回OT_TCP_INCOMING_CONNECTION_ACTION_REFUSE，则OpenThread会向试图建立连接的主机发送“连接被拒绝”消息。如果应用程序拒绝传入连接，则不需要填充@p aAcceptInto。
 *
 * @param[in]   aListener    与传入连接匹配的TCP侦听器。
 * @param[in]   aPeer        发起传入连接的主机和端口。
 * @param[out]  aAcceptInto  要接受传入连接的TCP端点。
 *
 * @returns  如何处理传入连接的说明。
 *
 */
typedef otTcpIncomingConnectionAction (*otTcpAcceptReady)(otTcpListener *   aListener,
                                                          const otSockAddr *aPeer,
                                                          otTcpEndpoint **  aAcceptInto);

/**
 * 此回调表示TCP连接现在已准备好进行双向通信。
 *
 * 在TCP Fast Open的情况下，这可能是在TCP连接握手实际完成之前。为应用程序提供了接受连接的TCP侦听器和接受该连接的TCP端点的上下文指针。提供的上下文是与TCP侦听器关联的上下文。
 *
 * @param[in]  aListener  与传入连接匹配的TCP侦听器。
 * @param[in]  aEndpoint  接受传入连接的TCP端点。
 * @param[in]  aPeer      发起传入连接的主机和端口。
 *
 */
typedef void (*otTcpAcceptDone)(otTcpListener *aListener, otTcpEndpoint *aEndpoint, const otSockAddr *aPeer);

/**
 * 此结构表示TCP侦听器。
 *
 * TCP侦听器用于侦听和接受传入的TCP连接。
 *
 * 应用程序不应直接检查此结构的字段；它应该仅通过TCP API函数与其交互，该函数的签名在该文件中提供。
 *
 */
struct otTcpListener
{
    struct otTcpListener *mNext;     ///<指向下一个TCP侦听器的指针（仅限内部使用）
    otInstance *          mInstance; ///<指向与此TCP侦听器关联的OpenThread实例的指针
    void *                mContext;  ///<指向应用程序特定上下文的指针

    otTcpAcceptReady mAcceptReadyCallback; ///<“Accept ready”回调函数
    otTcpAcceptDone  mAcceptDoneCallback;  ///<“Accept done”回调函数

    /* 此处显示其他实现定义的字段。*/
};

/**
 * 此结构包含otTcpListenerInitialize（）函数的参数。
 *
 */
typedef struct otTcpListenerInitializeArgs
{
    void *mContext; ///<指向应用程序特定上下文的指针

    otTcpAcceptReady mAcceptReadyCallback; ///<“Accept ready”回调函数
    otTcpAcceptDone  mAcceptDoneCallback;  ///<“Accept done”回调函数
} otTcpListenerInitializeArgs;

/**
 * 初始化TCP侦听器。
 *
 * Calling this function causes OpenThread to keep track of the TCP listener and store and retrieve TCP data inside @p a听众。应用程序应避免直接访问或修改@p aListener中的字段。如果应用程序需要回收支持@paListener的内存，它应该调用otTcpListenerDeinitialize（）。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aListener  指向TCP侦听器结构的指针。
 * @param[in]  aArgs      指向参数结构的指针。
 *
 * @retval OT_ERROR_NONE已成功打开TCP侦听器。
 * @retval OT_ERROR_FAILED无法打开TCP侦听器。
 *
 */
otError otTcpListenerInitialize(otInstance *aInstance, otTcpListener *aListener, otTcpListenerInitializeArgs *aArgs);

/**
 * 获取初始化时与@p aListener关联的otInstance。
 *
 * @param[in]  aListener  要获取其实例的TCP侦听器。
 *
 * @returns  与@p aListener关联的otInstance指针。
 *
 */
otInstance *otTcpListenerGetInstance(otTcpListener *aListener);

/**
 * 获取初始化时与@p aListener关联的上下文指针。
 *
 * @param[in]  aListener  要获取其上下文的TCP侦听器。
 *
 * @returns  与@p aListener关联的上下文指针。
 *
 */
void *otTcpListenerGetContext(otTcpListener *aListener);

/**
 * 使与指定IP地址和端口匹配的传入TCP连接触发此TCP侦听器的回调。
 *
 * @param[in]  aListener  指向应该开始侦听的TCP侦听器结构的指针。
 * @param[in]  aSockName  侦听传入连接的地址和端口。
 *
 * @retval OT_ERROR_NONE已成功启动TCP侦听器上的侦听。
 * @retval OT_ERROR_FAILED无法在TCP侦听器上启动侦听。
 *
 */
otError otTcpListen(otTcpListener *aListener, const otSockAddr *aSockName);

/**
 * 使此TCP侦听器停止侦听传入连接。
 *
 * @param[in]  aListener  指向应该停止侦听的TCP侦听器结构的指针。
 *
 * @retval OT_ERROR_NONE已成功停止侦听TCP侦听器。
 * @retval OT_ERROR_FAILED无法停止侦听TCP侦听器。
 *
 */
otError otTcpStopListening(otTcpListener *aListener);

/**
 * 取消初始化此TCP侦听器。
 *
 * 这意味着OpenThread不再跟踪此TCP侦听器，并释放其内部为此TCP侦听器分配的所有资源。应用程序可以根据需要重用支持TCP侦听器的内存。
 *
 * 如果TCP侦听器当前正在侦听，它将停止侦听。
 *
 * @param[in]  aListener  指向要取消初始化的TCP侦听器结构的指针。
 *
 * @retval OT_ERROR_NONE已成功取消初始化TCP侦听器。
 * @retval OT_ERROR_FAILED无法取消初始化TCP侦听器。
 *
 */
otError otTcpListenerDeinitialize(otTcpListener *aListener);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_TCP_H_

