/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread IEEE 802.15.4链路层API。
 */

#ifndef OPENTHREAD_LINK_H_
#define OPENTHREAD_LINK_H_

#include <openthread/commissioner.h>
#include <openthread/dataset.h>
#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api链接
 *
 * @brief 该模块包括控制链路层配置的功能。
 *
 * @{
 *
 */
#define OT_US_PER_TEN_SYMBOLS 160 ///<每10个符号的微秒数。

/**
 * 此结构表示从线程无线电接收的消息的链路特定信息。
 *
 */
typedef struct otThreadLinkInfo
{
    uint16_t mPanId;        ///<源PAN ID
    uint8_t  mChannel;      ///<802.15.4信道
    int8_t   mRss;          ///<接收信号强度（dBm）。
    uint8_t  mLqi;          ///<接收消息的链接质量指示符。
    bool     mLinkSecurity; ///<指示是否启用链接安全性。

    // 仅当启用时间同步功能（`OPENTHREAD_CONFIG_time_sync_ENABLE`）时适用/需要。
    uint8_t mTimeSyncSeq;       ///<时间同步序列。
    int64_t mNetworkTimeOffset; ///<线程网络时间的时间偏移，以微秒为单位。

    // 仅当启用OPENTHREAD_CONFIG_MULTI_RADIO功能时适用。
    uint8_t mRadioType; ///<无线电链路类型。
} otThreadLinkInfo;

/**
 * 用于指示未设置固定的接收信号强度
 *
 */
#define OT_MAC_FILTER_FIXED_RSS_DISABLED 127

#define OT_MAC_FILTER_ITERATOR_INIT 0 ///<otMacFilterIterator的初始化器。

typedef uint8_t otMacFilterIterator; ///<用于遍历mac筛选器条目。

/**
 * 定义mac筛选器的地址模式。
 *
 */
typedef enum otMacFilterAddressMode
{
    OT_MAC_FILTER_ADDRESS_MODE_DISABLED,  ///<地址筛选器已禁用。
    OT_MAC_FILTER_ADDRESS_MODE_ALLOWLIST, ///<Allowlist地址筛选器模式已启用。
    OT_MAC_FILTER_ADDRESS_MODE_DENYLIST,  ///＜Denylist地址筛选器模式已启用。
} otMacFilterAddressMode;

/**
 * 此结构表示Mac Filter条目。
 *
 */
typedef struct otMacFilterEntry
{
    otExtAddress mExtAddress; ///<IEEE 802.15.4扩展地址
    int8_t       mRssIn;      ///<接收信号强度
} otMacFilterEntry;

/**
 * 此结构表示MAC层计数器。
 *
 */
typedef struct otMacCounters
{
    /**
     * 唯一MAC帧传输请求的总数。
     *
     * 请注意，无论CCA失败、CSMA-CA尝试或重传的数量如何，此计数器对于每个MAC传输请求仅递增一。
     *
     * 此递增规则适用于以下计数器：
     *   - @p mTx单播
     *   - @p mTx广播
     *   - @p 请求的mTxAck
     *   - @p mTxNoAck请求
     *   - @p mTx数据
     *   - @p mTx数据轮询
     *   - @p mTx信标
     *   - @p mTxBeacon请求
     *   - @p mTx其他
     *   - @p mTx错误中止
     *   - @p mTxErrBusy信道
     *
     * 以下公式有效：
     *   - @p mTxTotal=@p mTx单播+@p mTX广播
     *   - @p mTxTotal=@p mTxAckRequested+@p mTxNoAckRequested
     *   - @p mTxTotal=@p mTxData+@p mTX数据轮询+@p mPTxBeacon+@p pTxBeacon请求+@p其他mTx
     *
     */
    uint32_t mTxTotal;

    /**
     * 唯一单播MAC帧传输请求的总数。
     *
     */
    uint32_t mTxUnicast;

    /**
     * 唯一广播MAC帧传输请求的总数。
     *
     */
    uint32_t mTxBroadcast;

    /**
     * 具有请求确认的唯一MAC帧传输请求的总数。
     *
     */
    uint32_t mTxAckRequested;

    /**
     * 已确认的唯一MAC帧传输请求的总数。
     *
     */
    uint32_t mTxAcked;

    /**
     * 没有请求确认的唯一MAC帧传输请求的总数。
     *
     */
    uint32_t mTxNoAckRequested;

    /**
     * 唯一MAC数据帧传输请求的总数。
     *
     */
    uint32_t mTxData;

    /**
     * 唯一MAC数据轮询帧传输请求的总数。
     *
     */
    uint32_t mTxDataPoll;

    /**
     * 唯一MAC信标帧传输请求的总数。
     *
     */
    uint32_t mTxBeacon;

    /**
     * 唯一MAC信标请求帧传输请求的总数。
     *
     */
    uint32_t mTxBeaconRequest;

    /**
     * 唯一的其他MAC帧传输请求的总数。
     *
     * 此计数器当前用于计数带外帧。
     *
     */
    uint32_t mTxOther;

    /**
     * MAC重传尝试的总数。
     *
     * 请注意，对于可能由缺少确认、CSMA/CA失败或其他类型的传输错误触发的每一次重传尝试，此计数器将递增1。
     * The @p 对于单播和广播MAC帧，mTxRetry计数器都递增。
     *
     * 修改以下配置参数以控制系统中的重传量：
     *
     * - OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_DIRECT
     * - OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_INDIRECT
     * - OPENTHREAD_CONFIG_MAC_TX_NUM_BCAST
     * - OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_DIRECT
     * - OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_INDIRECT
     *
     * 当前，如果平台的无线电驱动程序功能包括
     * @ref OT_RADIO_CAPS_TRANSMIT_RETRIES.
     *
     */
    uint32_t mTxRetry;

    /**
     * 满足直接数据包最大重试限制的唯一MAC传输数据包总数。
     *
     */
    uint32_t mTxDirectMaxRetryExpiry;

    /**
     * 满足间接数据包最大重试限制的唯一MAC传输数据包总数。
     *
     */
    uint32_t mTxIndirectMaxRetryExpiry;

    /**
     * CCA失败的总数。
     *
     * 此计数器的含义可能不同，取决于平台的无线电驱动程序功能。
     *
     * If @ref OT_RADIO_CAPS_CSMA_BACKOFF已启用，此计数器表示完全CSMA/CA失败尝试的总数，并且对于每次重传（在CSMA/CA故障的情况下）也会增加1。
     *
     * If @ref OT_RADIO_CAPS_TRANSMIT_RETRIES已启用，此计数器表示完整CSMA/CA失败尝试的总数，并对每个单独的数据帧请求递增一（无论重传次数如何）。
     *
     */
    uint32_t mTxErrCca;

    /**
     * 由中止错误导致的唯一MAC传输请求失败的总数。
     *
     */
    uint32_t mTxErrAbort;

    /**
     * 由繁忙信道（CSMA/CA失败）导致的唯一MAC传输请求失败的总数。
     *
     */
    uint32_t mTxErrBusyChannel;

    /**
     * 接收帧的总数。
     *
     * 此计数器统计平台无线电驱动程序报告的所有帧，包括例如由于FCS错误而丢失的帧。
     *
     */
    uint32_t mRxTotal;

    /**
     * 接收的单播帧总数。
     *
     */
    uint32_t mRxUnicast;

    /**
     * 接收的广播帧总数。
     *
     */
    uint32_t mRxBroadcast;

    /**
     * 接收的MAC数据帧总数。
     *
     */
    uint32_t mRxData;

    /**
     * 接收的MAC数据轮询帧总数。
     *
     */
    uint32_t mRxDataPoll;

    /**
     * 接收的MAC信标帧总数。
     *
     */
    uint32_t mRxBeacon;

    /**
     * 接收的MAC信标请求帧的总数。
     *
     */
    uint32_t mRxBeaconRequest;

    /**
     * 接收的其他类型帧的总数。
     *
     */
    uint32_t mRxOther;

    /**
     * MAC筛选器模块丢弃的帧总数，例如从denylisted节点接收的帧。
     *
     */
    uint32_t mRxAddressFiltered;

    /**
     * 目标地址检查丢弃的帧总数，例如其他节点的接收帧。
     *
     */
    uint32_t mRxDestAddrFiltered;

    /**
     * 由于重复而丢失的帧总数，即当已接收到帧时。
     *
     * 例如，当接收机生成的ACK帧尚未到达执行重传的发射机节点时，该计数器可以递增。
     *
     */
    uint32_t mRxDuplicated;

    /**
     * 由于内容丢失或格式错误而丢弃的帧总数。
     *
     */
    uint32_t mRxErrNoFrame;

    /**
     * 由于未知邻居而丢弃的帧总数。
     *
     */
    uint32_t mRxErrUnknownNeighbor;

    /**
     * 由于源地址无效而丢弃的帧总数。
     *
     */
    uint32_t mRxErrInvalidSrcAddr;

    /**
     * 由于安全错误而丢弃的帧总数。
     *
     * 例如，当使用低于预期的帧计数器来加密帧时，该计数器可以递增。
     *
     */
    uint32_t mRxErrSec;

    /**
     * 由于FCS无效而丢弃的帧总数。
     *
     */
    uint32_t mRxErrFcs;

    /**
     * 由于其他错误而丢弃的帧数总数。
     *
     */
    uint32_t mRxErrOther;
} otMacCounters;

/**
 * 该结构表示接收的IEEE 802.15.4信标。
 *
 */
typedef struct otActiveScanResult
{
    otExtAddress    mExtAddress;     ///<IEEE 802.15.4扩展地址
    otNetworkName   mNetworkName;    ///<线程网络名称
    otExtendedPanId mExtendedPanId;  ///<线程扩展PAN ID
    otSteeringData  mSteeringData;   ///<转向数据
    uint16_t        mPanId;          ///< IEEE 802.15.4 PAN ID
    uint16_t        mJoinerUdpPort;  ///<Joiner UDP端口
    uint8_t         mChannel;        ///<IEEE 802.15.4信道
    int8_t          mRssi;           ///<RSSI（dBm）
    uint8_t         mLqi;            ///< LQI
    unsigned int    mVersion : 4;    ///<版本
    bool            mIsNative : 1;   ///<土著专员旗帜
    bool            mIsJoinable : 1; ///<加入允许标志
} otActiveScanResult;

/**
 * 该结构表示能量扫描结果。
 *
 */
typedef struct otEnergyScanResult
{
    uint8_t mChannel; ///<IEEE 802.15.4信道
    int8_t  mMaxRssi; ///<最大RSSI（dBm）
} otEnergyScanResult;

/**
 * 当接收到IEEE 802.15.4信标或扫描完成时，在IEEE 802.15.4活动扫描期间调用此函数指针。
 *
 * @param[in]  aResult   当活动扫描完成时，指向信标信息的有效指针或NULL。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otHandleActiveScanResult)(otActiveScanResult *aResult, void *aContext);

/**
 * 此功能启动IEEE 802.15.4活动扫描
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aScanChannels     指示要扫描哪些信道的位向量（例如OT_CHANNEL_11_MASK）。
 * @param[in]  aScanDuration     扫描每个频道所花费的时间（毫秒）。
 * @param[in]  aCallback         指向在接收信标或扫描完成时调用的函数的指针。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE接受活动扫描请求。
 * @retval OT_ERROR_BUSY已执行活动扫描。
 *
 */
otError otLinkActiveScan(otInstance *             aInstance,
                         uint32_t                 aScanChannels,
                         uint16_t                 aScanDuration,
                         otHandleActiveScanResult aCallback,
                         void *                   aCallbackContext);

/**
 * 此函数指示IEEE 802.15.4活动扫描当前是否正在进行。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 如果IEEE 802.15.4活动扫描正在进行，则为true，否则为false。
 */
bool otLinkIsActiveScanInProgress(otInstance *aInstance);

/**
 * 当信道的结果就绪或扫描完成时，在IEEE 802.15.4能量扫描期间调用此函数指针。
 *
 * @param[in]  aResult   能量扫描结果信息的有效指针，或在能量扫描完成时为NULL。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otHandleEnergyScanResult)(otEnergyScanResult *aResult, void *aContext);

/**
 * 此功能启动IEEE 802.15.4能量扫描
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aScanChannels     指示在哪些信道上执行能量扫描的位向量。
 * @param[in]  aScanDuration     扫描每个频道所花费的时间（毫秒）。
 * @param[in]  aCallback         一个指向调用以传递扫描结果的函数的指针表示扫描完成。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE接受能量扫描请求。
 * @retval OT_ERROR_BUSY无法启动能量扫描。
 *
 */
otError otLinkEnergyScan(otInstance *             aInstance,
                         uint32_t                 aScanChannels,
                         uint16_t                 aScanDuration,
                         otHandleEnergyScanResult aCallback,
                         void *                   aCallbackContext);

/**
 * 此函数指示IEEE 802.15.4能量扫描当前是否正在进行。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 如果IEEE 802.15.4能量扫描正在进行，则为true，否则为false。
 *
 */
bool otLinkIsEnergyScanInProgress(otInstance *aInstance);

/**
 * 此函数将IEEE 802.15.4数据请求消息排入队列以进行传输。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功将IEEE 802.15.4数据请求消息排入队列。
 * @retval OT_ERROR_ALREADY IEEE 802.15.4数据请求消息已入队。
 * @retval OT_ERROR_INVALID_STATE设备在空闲模式下未处于rx关闭状态。
 * @retval OT_ERROR_NO_BUFS可用的消息缓冲区不足。
 *
 */
otError otLinkSendDataRequest(otInstance *aInstance);

/**
 * 此函数指示IEEE 802.15.4 MAC是否处于发送状态。
 *
 * MAC模块在CSMA/CA过程、CCA、数据、信标或数据请求帧发送期间处于发送状态，并接收发送帧的ACK。MAC模块在ACK帧或信标请求帧的传输期间不处于传输状态。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 如果IEEE 802.15.4 MAC处于传输状态，则为true，否则为false。
 *
 */
bool otLinkIsInTransmitState(otInstance *aInstance);

/**
 * 获取IEEE 802.15.4信道。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns IEEE 802.15.4信道。
 *
 * @sa otLinkSet频道
 *
 */
uint8_t otLinkGetChannel(otInstance *aInstance);

/**
 * 设置IEEE 802.15.4信道
 *
 * 仅当禁用线程协议时，此函数才会成功。成功调用此函数将使非易失性内存中的活动和挂起操作数据集无效。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aChannel    IEEE 802.15.4信道。
 *
 * @retval  OT_ERROR_NONE成功设置信道。
 * @retval  OT_ERROR_INVALID_ARGS如果@p aChannel不在范围[11，26]内或不在支持的信道掩码中。
 * @retval  OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otLinkGet频道
 *
 */
otError otLinkSetChannel(otInstance *aInstance, uint8_t aChannel);

/**
 * 获取MAC层支持的信道掩码。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 支持的通道掩码为“uint32_t”，位0（lsb）映射到通道0，位1映射到通道1，依此类推。
 *
 */
uint32_t otLinkGetSupportedChannelMask(otInstance *aInstance);

/**
 * 设置MAC层支持的信道掩码。
 *
 * 仅当禁用线程协议时，此函数才会成功。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aChannelMask  支持的通道掩码（位0或lsb映射到通道0，等等）。
 *
 * @retval  OT_ERROR_NONE成功设置支持的通道掩码。
 * @retval  OT_ERROR_INVALID_STATE线程协议已启用。
 *
 */
otError otLinkSetSupportedChannelMask(otInstance *aInstance, uint32_t aChannelMask);

/**
 * 获取IEEE 802.15.4扩展地址。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向IEEE 802.15.4扩展地址的指针。
 *
 */
const otExtAddress *otLinkGetExtendedAddress(otInstance *aInstance);

/**
 * 此函数设置IEEE 802.15.4扩展地址。
 *
 * 仅当禁用线程协议时，此函数才会成功。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aExtAddress  指向IEEE 802.15.4扩展地址的指针。
 *
 * @retval OT_ERROR_NONE已成功设置IEEE 802.15.4扩展地址。
 * @retval OT_ERROR_INVALID_ARGS@p aExtAddress为空。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 */
otError otLinkSetExtendedAddress(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 获取工厂指定的IEEE EUI-64。
 *
 * @param[in]   aInstance  指向OpenThread实例的指针。
 * @param[out]  aEui64     指向工厂指定的IEEE EUI-64放置位置的指针。
 *
 */
void otLinkGetFactoryAssignedIeeeEui64(otInstance *aInstance, otExtAddress *aEui64);

/**
 * 获取IEEE 802.15.4 PAN ID。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns IEEE 802.15.4 PAN ID。
 *
 * @sa otLinkSetPanId
 *
 */
otPanId otLinkGetPanId(otInstance *aInstance);

/**
 * 设置IEEE 802.15.4 PAN ID。
 *
 * 仅当禁用线程协议时，此函数才会成功。成功调用此函数也会使非易失性内存中的活动和挂起操作数据集无效。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aPanId       IEEE 802.15.4 PAN ID。
 *
 * @retval OT_ERROR_NONE成功设置PAN ID。
 * @retval OT_ERROR_INVALID_ARGS如果aPanId不在[0，65534]范围内。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otLinkGetPanId
 *
 */
otError otLinkSetPanId(otInstance *aInstance, otPanId aPanId);

/**
 * 获取休眠终端设备的数据轮询周期。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns  休眠终端设备的数据轮询周期（毫秒）。
 *
 * @sa otLinkSet轮询周期
 *
 */
uint32_t otLinkGetPollPeriod(otInstance *aInstance);

/**
 * 设置/清除休眠终端设备的用户指定/外部数据轮询周期。
 *
 * @note 此功能仅更新休眠终端设备的轮询周期。要更新子超时，应调用函数“otThreadSetChildTimeout（）”。
 *
 * @note 最小非零值应为`OPENTHREAD_CONFIGMAC_MINIMUM_POLL_PERIOD`（10ms）。或为零以清除用户指定的轮询周期。
 *
 * @note 用户指定的值不应大于允许的最大值0x3FFFFFFF（（1<<26）-1），否则将被最大值剪裁。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aPollPeriod  数据轮询周期（毫秒）。
 *
 * @retval OT_ERROR_NONE已成功设置/清除用户指定的轮询周期。
 * @retval OT_ERROR_INVALID_ARGS如果轮询周期无效。
 *
 * @sa otLinkGetPoll周期
 *
 */
otError otLinkSetPollPeriod(otInstance *aInstance, uint32_t aPollPeriod);

/**
 * 获取IEEE 802.15.4短地址。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向IEEE 802.15.4短地址的指针。
 *
 */
otShortAddress otLinkGetShortAddress(otInstance *aInstance);

/**
 * 此方法返回直接传输期间的最大帧重试次数。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 直接传输期间的最大重试次数。
 *
 */
uint8_t otLinkGetMaxFrameRetriesDirect(otInstance *aInstance);

/**
 * 此方法设置直接传输期间的最大帧重试次数。
 *
 * @param[in]  aInstance               指向OpenThread实例的指针。
 * @param[in]  aMaxFrameRetriesDirect  直接传输期间的最大重试次数。
 *
 */
void otLinkSetMaxFrameRetriesDirect(otInstance *aInstance, uint8_t aMaxFrameRetriesDirect);

/**
 * 此方法返回间接传输期间的最大帧重试次数。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 间接传输期间的最大重试次数。
 *
 */
uint8_t otLinkGetMaxFrameRetriesIndirect(otInstance *aInstance);

/**
 * 此方法设置间接传输期间的最大帧重试次数。
 *
 * @param[in]  aInstance                 指向OpenThread实例的指针。
 * @param[in]  aMaxFrameRetriesIndirect  间接传输期间的最大重试次数。
 *
 */
void otLinkSetMaxFrameRetriesIndirect(otInstance *aInstance, uint8_t aMaxFrameRetriesIndirect);

/**
 * 此函数获取MAC过滤器的地址模式。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns  地址模式。
 *
 */
otMacFilterAddressMode otLinkFilterGetAddressMode(otInstance *aInstance);

/**
 * 此功能设置MAC过滤器的地址模式。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aMode      要设置的地址模式。
 *
 */
void otLinkFilterSetAddressMode(otInstance *aInstance, otMacFilterAddressMode aMode);

/**
 * 此方法向MAC筛选器添加扩展地址。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aExtAddress  指向扩展地址的指针（不能为空）。
 *
 * @retval OT_ERROR_NONE已成功将@p aExtAddress添加到MAC筛选器。
 * @retval OT_ERROR_NO_BUFS不存在可用条目。
 *
 */
otError otLinkFilterAddAddress(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 此方法从MAC筛选器中删除扩展地址。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * 如果筛选器中没有与给定扩展地址匹配的现有条目，则不执行任何操作。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aExtAddress  指向扩展地址的指针（不能为空）。
 *
 */
void otLinkFilterRemoveAddress(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 此方法清除MAC筛选器中的所有扩展地址。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otLinkFilterClearAddresses(otInstance *aInstance);

/**
 * 此方法获取正在使用的地址筛选器条目。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向MAC筛选器迭代器上下文的指针。要获取第一个使用中的地址筛选器条目，应将其设置为OTMAC_filter_ITERATOR_INIT。不得为空。
 * @param[out]    aEntry     指向信息放置位置的指针。不得为空。
 *
 * @retval OT_ERROR_NONE已成功检索到正在使用的地址筛选器条目。
 * @retval OT_ERROR_NOT_FOUND不存在后续条目。
 *
 */
otError otLinkFilterGetNextAddress(otInstance *aInstance, otMacFilterIterator *aIterator, otMacFilterEntry *aEntry);

/**
 * 该方法为来自MAC过滤器中给定扩展地址的消息添加固定接收信号强度（单位dBm）条目。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aExtAddress  指向IEEE 802.15.4扩展地址的指针。不得为空。
 * @param[in]  aRss         接收信号强度（dBm）。
 *
 * @retval OT_ERROR_NONE已成功为@p aExtAddress和@p aRss添加条目。
 * @retval OT_ERROR_NO_BUFS不存在可用条目。
 *
 */
otError otLinkFilterAddRssIn(otInstance *aInstance, const otExtAddress *aExtAddress, int8_t aRss);

/**
 * 此方法删除给定扩展地址的固定接收信号强度设置的MAC过滤器条目。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * 如果筛选器中没有与给定扩展地址匹配的现有条目，则不执行任何操作。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aExtAddress  指向IEEE 802.15.4扩展地址的指针。不得为空。
 *
 */
void otLinkFilterRemoveRssIn(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 此方法设置MAC滤波器上的默认接收信号强度（单位dBm）。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * 默认RSS值用于从筛选器列表中没有明确RSS-IN条目的地址接收的所有帧（使用“otLinkFilterAddRssIn（）”添加）。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aRss         要设置的默认接收信号强度（dBm）。
 *
 */
void otLinkFilterSetDefaultRssIn(otInstance *aInstance, int8_t aRss);

/**
 * 此方法清除MAC滤波器上任何先前设置的默认接收信号强度（单位dBm）。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 */
void otLinkFilterClearDefaultRssIn(otInstance *aInstance);

/**
 * 此方法清除MAC过滤器上的所有接收信号强度条目（包括默认RSS）。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 */
void otLinkFilterClearAllRssIn(otInstance *aInstance);

/**
 * 此方法获取正在使用的RssIn筛选器条目。
 *
 * 启用OPENTHREAD_CONFIGMAC_FILTER_ENABLE配置时，此功能可用。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向MAC筛选器迭代器上下文的指针。不得为空。要获取第一个条目，应将其设置为OTMAC_FILTER_ITERATOR_INIT。
 * @param[out]    aEntry     指向信息放置位置的指针。最后一个条目的扩展地址将为所有0xff，以指示如果设置了默认接收信号强度@p aEntry不得为空。
 *
 * @retval OT_ERROR_NONE成功检索到下一个条目。
 * @retval OT_ERROR_NOT_FOUND不存在后续条目。
 *
 */
otError otLinkFilterGetNextRssIn(otInstance *aInstance, otMacFilterIterator *aIterator, otMacFilterEntry *aEntry);

/**
 * 该方法将接收信号强度转换为链路质量。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aRss       要转换的接收信号强度值。
 *
 * @return 将质量值映射链接到@p aRss。
 *
 */
uint8_t otLinkConvertRssToLinkQuality(otInstance *aInstance, int8_t aRss);

/**
 * 该方法将链路质量转换为典型的接收信号强度。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aLinkQuality  LinkQuality值应在[0,3]范围内。
 *
 * @return 典型的平台接收信号强度映射到@p aLinkQuality。
 *
 */
int8_t otLinkConvertLinkQualityToRss(otInstance *aInstance, uint8_t aLinkQuality);

/**
 * 此方法获取单个直接数据包的重试直方图，直到成功。
 *
 * 启用OPENTHREAD_COONFIGMAC_RETRY_SUCCESSHISTOGRAM_ENABLE配置时，此函数有效。
 *
 * @param[in]   aInstance          指向OpenThread实例的指针。
 * @param[out]  aNumberOfEntries   返回的直方图数组大小所在位置的指针。
 *
 * @returns     重试直方图的指针（以数组的形式）。第n个元素表示数据包已通过第n次重试发送。
 */
const uint32_t *otLinkGetTxDirectRetrySuccessHistogram(otInstance *aInstance, uint8_t *aNumberOfEntries);

/**
 * 此方法获取单个间接数据包的重试直方图，直到成功。
 *
 * 启用OPENTHREAD_COONFIGMAC_RETRY_SUCCESSHISTOGRAM_ENABLE配置时，此函数有效。
 *
 * @param[in]   aInstance          指向OpenThread实例的指针。
 * @param[out]  aNumberOfEntries   返回的直方图数组大小所在位置的指针。
 *
 * @returns     重试直方图的指针（以数组的形式）。第n个元素表示数据包已通过第n次重试发送。
 *
 */
const uint32_t *otLinkGetTxIndirectRetrySuccessHistogram(otInstance *aInstance, uint8_t *aNumberOfEntries);

/**
 * 此方法清除直接和间接传输的直方图统计信息。
 *
 * 启用OPENTHREAD_COONFIGMAC_RETRY_SUCCESSHISTOGRAM_ENABLE配置时，此函数有效。
 *
 * @param[in]   aInstance          指向OpenThread实例的指针。
 *
 */
void otLinkResetTxRetrySuccessHistogram(otInstance *aInstance);

/**
 * 获取MAC层计数器。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向MAC层计数器的指针。
 *
 */
const otMacCounters *otLinkGetCounters(otInstance *aInstance);

/**
 * 重置MAC层计数器。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 */
void otLinkResetCounters(otInstance *aInstance);

/**
 * 当接收到IEEE 802.15.4帧时，调用此函数指针。
 *
 * @note 此回调在FCS处理后调用，@p aFrame可能不包含接收到的实际FCS。
 *
 * @note 在IEEE 802.15.4安全处理之前调用此回调。
 *
 * @param[in]  aFrame    指向所接收的IEEE 802.15.4帧的指针。
 * @param[in]  aIsTx     是否发送此帧，而不是接收此帧。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otLinkPcapCallback)(const otRadioFrame *aFrame, bool aIsTx, void *aContext);

/**
 * 此函数注册回调以提供接收到的原始IEEE 802.15.4帧。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aPcapCallback     指向在接收IEEE 802.15.4链接帧时调用的函数的指针，或NULL以禁用回调。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 */
void otLinkSetPcapCallback(otInstance *aInstance, otLinkPcapCallback aPcapCallback, void *aCallbackContext);

/**
 * 此函数指示链路层是否启用混杂模式。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval true混杂模式已启用。
 * @retval false未启用混杂模式。
 *
 */
bool otLinkIsPromiscuous(otInstance *aInstance);

/**
 * 此函数启用或禁用链接层混杂模式。
 *
 * @note 仅当禁用线程接口时，才能启用混杂模式。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aPromiscuous  true表示启用混杂模式，否则为false。
 *
 * @retval OT_ERROR_NONE已成功启用混杂模式。
 * @retval OT_ERROR_INVALID_STATE无法启用混杂模式，因为线程接口已启用。
 *
 */
otError otLinkSetPromiscuous(otInstance *aInstance, bool aPromiscuous);

/**
 * 此函数获取CSL通道。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 *
 * @returns CSL通道。
 *
 */
uint8_t otLinkCslGetChannel(otInstance *aInstance);

/**
 * 此函数用于设置CSL信道。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 * @param[in]  aChannel       CSL样本通道。信道值应为“0”（未指定设置CSL信道）或在[1，10]（如果支持915 MHz）和[11，26]（如果2.4 GHz）范围内。
 *
 * @retval OT_ERROR_NONE成功设置CSL参数。
 * @retval OT_ERROR_INVALID_ARGS@p aChannel无效。
 *
 */
otError otLinkCslSetChannel(otInstance *aInstance, uint8_t aChannel);

/**
 * 此函数获取CSL周期。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 *
 * @returns 以10个符号为单位的CSL周期。
 *
 */
uint16_t otLinkCslGetPeriod(otInstance *aInstance);

/**
 * 此函数设置CSL周期。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 * @param[in]  aPeriod        以10个符号为单位的CSL周期。
 *
 * @retval OT_ERROR_NONE成功设置CSL时段。
 * @retval OT_ERROR_INVALID_ARGS CSL周期无效。
 *
 */
otError otLinkCslSetPeriod(otInstance *aInstance, uint16_t aPeriod);

/**
 * 此函数获取CSL超时。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 *
 * @returns CSL超时（秒）。
 *
 */
uint32_t otLinkCslGetTimeout(otInstance *aInstance);

/**
 * 此函数设置CSL超时。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 * @param[in]  aTimeout       CSL超时（秒）。
 *
 * @retval OT_ERROR_NONE成功设置CSL超时。
 * @retval OT_ERROR_INVALID_ARGS无效的CSL超时。
 *
 */
otError otLinkCslSetTimeout(otInstance *aInstance, uint32_t aTimeout);

/**
 * 此函数返回当前CCA（清除信道评估）故障率。
 *
 * 该速率在（大致）最后一次“OPENTHREAD_CONFIG_CCA_FAILURE_rate_AVERAGING_window”帧传输的窗口内保持。
 *
 * @returns 最大值为“0xffff”的CCA故障率对应于100%故障率。
 *
 */
uint16_t otLinkGetCcaFailureRate(otInstance *aInstance);

/**
 * 此功能启用或禁用链接层。
 *
 * @note 链接层只能在禁用线程接口时启用/禁用。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aEnable       true以启用链接层，否则为false。
 *
 * @retval OT_ERROR_NONE已成功启用/禁用链路层。
 * @retval OT_ERROR_INVALID_STATE无法禁用链接层，因为线程接口已启用。
 *
 */
otError otLinkSetEnabled(otInstance *aInstance, bool aEnable);

/**
 * 此函数指示链接层是否已启用。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval true链接层已启用。
 * @retval false链接层未启用。
 *
 */
bool otLinkIsEnabled(otInstance *aInstance);

/**
 * 此函数指示设备发送空的IEEE 802.15.4数据帧。
 *
 * 此功能仅在Rx Off When Idle（空闲时关闭Rx）设备上支持，以向其父设备发送空数据帧。注意：仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功将空消息排入队列。
 * @retval OT_ERROR_INVALID_STATE设备未处于空闲时关闭Rx模式。
 * @retval OT_ERROR_NO_BUFS可用的消息缓冲区不足。
 *
 */
otError otLinkSendEmptyData(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_LINK_H_

