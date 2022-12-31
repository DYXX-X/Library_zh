/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread网络诊断API。
 */

#ifndef OPENTHREAD_NETDIAG_H_
#define OPENTHREAD_NETDIAG_H_

#include <openthread/ip6.h>
#include <openthread/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api线程常规
 *
 * @{
 *
 */

/**
 * 要请求或重置的网络诊断TLV类型的最大数量。
 */
#define OT_NETWORK_DIAGNOSTIC_TYPELIST_MAX_ENTRIES 19

/**
 * 网络诊断子表条目的大小。
 */
#define OT_NETWORK_DIAGNOSTIC_CHILD_TABLE_ENTRY_SIZE 3

/**
 * otNetworkDiagIterator的初始化器。
 */
#define OT_NETWORK_DIAGNOSTIC_ITERATOR_INIT 0

enum
{
    OT_NETWORK_DIAGNOSTIC_TLV_EXT_ADDRESS       = 0,  ///<MAC扩展地址TLV
    OT_NETWORK_DIAGNOSTIC_TLV_SHORT_ADDRESS     = 1,  ///<地址16 TLV
    OT_NETWORK_DIAGNOSTIC_TLV_MODE              = 2,  ///<模式TLV
    OT_NETWORK_DIAGNOSTIC_TLV_TIMEOUT           = 3,  ///＜超时TLV（SED的最大轮询时间段）
    OT_NETWORK_DIAGNOSTIC_TLV_CONNECTIVITY      = 4,  ///<连接TLV
    OT_NETWORK_DIAGNOSTIC_TLV_ROUTE             = 5,  ///<Route64 TLV
    OT_NETWORK_DIAGNOSTIC_TLV_LEADER_DATA       = 6,  ///<领导者数据TLV
    OT_NETWORK_DIAGNOSTIC_TLV_NETWORK_DATA      = 7,  ///<网络数据TLV
    OT_NETWORK_DIAGNOSTIC_TLV_IP6_ADDR_LIST     = 8,  ///<IPv6地址列表TLV
    OT_NETWORK_DIAGNOSTIC_TLV_MAC_COUNTERS      = 9,  ///<MAC计数器TLV
    OT_NETWORK_DIAGNOSTIC_TLV_BATTERY_LEVEL     = 14, ///<电池水平TLV
    OT_NETWORK_DIAGNOSTIC_TLV_SUPPLY_VOLTAGE    = 15, ///<电源电压TLV
    OT_NETWORK_DIAGNOSTIC_TLV_CHILD_TABLE       = 16, ///<子表TLV
    OT_NETWORK_DIAGNOSTIC_TLV_CHANNEL_PAGES     = 17, ///<频道页TLV
    OT_NETWORK_DIAGNOSTIC_TLV_TYPE_LIST         = 18, ///<类型列表TLV
    OT_NETWORK_DIAGNOSTIC_TLV_MAX_CHILD_TIMEOUT = 19, ///<最大子超时TLV
};

typedef uint16_t otNetworkDiagIterator; ///<用于遍历网络诊断TLV。

/**
 * 此结构表示网络诊断连接性值。
 *
 */
typedef struct otNetworkDiagConnectivity
{
    /**
     * 发件人作为父项的优先级。
     */
    int8_t mParentPriority;

    /**
     * 发送方与之共享质量链路的相邻设备的数量为3。
     */
    uint8_t mLinkQuality3;

    /**
     * 发送方与之共享质量链路2的相邻设备的数量。
     */
    uint8_t mLinkQuality2;

    /**
     * 发送方与之共享质量链路1的相邻设备的数量。
     */
    uint8_t mLinkQuality1;

    /**
     * 发件人发送给领导者的路由成本。
     */
    uint8_t mLeaderCost;

    /**
     * 发件人收到的最新ID序列号。
     */
    uint8_t mIdSequence;

    /**
     * 发送方线程网络分区中活动路由器的数量。
     */
    uint8_t mActiveRouters;

    /**
     * 指定SED的所有IPv6数据报的保证缓冲区容量（以八位字节为单位）。可选择的
     */
    uint16_t mSedBufferSize;

    /**
     * 以指定SED为目的地的IPv6数据报数量表示的保证队列容量。可选择的
     */
    uint8_t mSedDatagramCount;
} otNetworkDiagConnectivity;

/**
 * 此结构表示网络诊断路由数据。
 *
 */
typedef struct otNetworkDiagRouteData
{
    uint8_t mRouterId;           ///<分配的路由器ID。
    uint8_t mLinkQualityOut : 2; ///<链接质量输出。
    uint8_t mLinkQualityIn : 2;  ///<链接质量输入。
    uint8_t mRouteCost : 4;      ///<路由成本。无限路由成本由值0表示。
} otNetworkDiagRouteData;

/**
 * 此结构表示网络诊断路由TLV值。
 *
 */
typedef struct otNetworkDiagRoute
{
    /**
     * 与#mRouteData中的一组路由器ID分配关联的序列号。
     */
    uint8_t mIdSequence;

    /**
     * #mRouteData中的元素数。
     */
    uint8_t mRouteCount;

    /**
     * 链路质量和路由成本数据。
     */
    otNetworkDiagRouteData mRouteData[OT_NETWORK_MAX_ROUTER_ID + 1];
} otNetworkDiagRoute;

/**
 * 此结构表示网络诊断Mac计数器值。
 *
 * 参见<a href=“https://www.ietf.org/rfc/rfc2863“>RFC 2863</a>成员字段的定义。
 *
 */
typedef struct otNetworkDiagMacCounters
{
    uint32_t mIfInUnknownProtos;
    uint32_t mIfInErrors;
    uint32_t mIfOutErrors;
    uint32_t mIfInUcastPkts;
    uint32_t mIfInBroadcastPkts;
    uint32_t mIfInDiscards;
    uint32_t mIfOutUcastPkts;
    uint32_t mIfOutBroadcastPkts;
    uint32_t mIfOutDiscards;
} otNetworkDiagMacCounters;

/**
 * 此结构表示网络诊断子表条目。
 *
 */
typedef struct otNetworkDiagChildEntry
{
    /**
     * 预期轮询时间表示为2^（Timeout-4）秒。
     */
    uint16_t mTimeout : 5;

    /**
     * 可以从中生成RLOC的子ID。
     */
    uint16_t mChildId : 9;

    /**
     * 链接模式位。
     */
    otLinkModeConfig mMode;
} otNetworkDiagChildEntry;

/**
 * 此结构表示网络诊断TLV。
 *
 */
typedef struct otNetworkDiagTlv
{
    /**
     * 网络诊断TLV类型。
     */
    uint8_t mType;

    union
    {
        otExtAddress              mExtAddress;
        uint16_t                  mAddr16;
        otLinkModeConfig          mMode;
        uint32_t                  mTimeout;
        otNetworkDiagConnectivity mConnectivity;
        otNetworkDiagRoute        mRoute;
        otLeaderData              mLeaderData;
        otNetworkDiagMacCounters  mMacCounters;
        uint8_t                   mBatteryLevel;
        uint16_t                  mSupplyVoltage;
        uint32_t                  mMaxChildTimeout;
        struct
        {
            uint8_t mCount;
            uint8_t m8[OT_NETWORK_BASE_TLV_MAX_LENGTH];
        } mNetworkData;
        struct
        {
            uint8_t      mCount;
            otIp6Address mList[OT_NETWORK_BASE_TLV_MAX_LENGTH / OT_IP6_ADDRESS_SIZE];
        } mIp6AddrList;
        struct
        {
            uint8_t mCount;
            otNetworkDiagChildEntry
                mTable[OT_NETWORK_BASE_TLV_MAX_LENGTH / OT_NETWORK_DIAGNOSTIC_CHILD_TABLE_ENTRY_SIZE];
        } mChildTable;
        struct
        {
            uint8_t mCount;
            uint8_t m8[OT_NETWORK_BASE_TLV_MAX_LENGTH];
        } mChannelPages;
    } mData;
} otNetworkDiagTlv;

/**
 * 此函数获取消息中的下一个网络诊断TLV。
 *
 * @param[in]     aMessage         指向消息的指针。
 * @param[inout]  aIterator        指向网络诊断迭代器上下文的指针。要获得第一个网络诊断TLV，应将其设置为OT_Network_Diagnostic_ITERATOR_INIT。
 * @param[out]    aNetworkDiagTlv  指向将放置网络诊断TLV信息的位置的指针。
 *
 * @retval OT_ERROR_NONE成功找到下一个网络诊断TLV。
 * @retval OT_ERROR_NOT_FOUND消息中不存在后续网络诊断TLV。
 * @retval OT_ERROR_PARSE分析下一个网络诊断失败。
 *
 * @Note 仅当当前返回值为OT_ERROR_NONE时，才允许对该函数进行后续调用。
 *
 */
otError otThreadGetNextDiagnosticTlv(const otMessage *      aMessage,
                                     otNetworkDiagIterator *aIterator,
                                     otNetworkDiagTlv *     aNetworkDiagTlv);

/**
 * 当收到网络诊断获取响应时，调用此函数指针。
 *
 * @param[in]  aError        获取响应失败时出错。
 * @param[in]  aMessage      指向包含接收到的网络诊断获取响应负载的消息缓冲区的指针。仅当@p aError为“OT_ERROR_NONE”时可用。
 * @param[in]  aMessageInfo  指向@p aMessage的消息信息的指针。仅当@p aError为“OT_ERROR_NONE”时可用。
 * @param[in]  aContext      指向应用程序特定上下文的指针。
 *
 */
typedef void (*otReceiveDiagnosticGetCallback)(otError              aError,
                                               otMessage *          aMessage,
                                               const otMessageInfo *aMessageInfo,
                                               void *               aContext);

/**
 * 发送网络诊断获取请求。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aDestination      指向目标地址的指针。
 * @param[in]  aTlvTypes         网络诊断TLV类型的数组。
 * @param[in]  aCount            aTlvTypes中的类型数。
 * @param[in]  aCallback         指向在收到网络诊断获取响应时调用的函数的指针，或为NULL以禁用回调。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功将DIAG_GET.req排队。
 * @retval OT_ERROR_NO_BUFS可用的消息缓冲区不足，无法发送DIAG_GET.req。
 *
 */
otError otThreadSendDiagnosticGet(otInstance *                   aInstance,
                                  const otIp6Address *           aDestination,
                                  const uint8_t                  aTlvTypes[],
                                  uint8_t                        aCount,
                                  otReceiveDiagnosticGetCallback aCallback,
                                  void *                         aCallbackContext);

/**
 * 发送网络诊断重置请求。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 * @param[in]  aDestination   指向目标地址的指针。
 * @param[in]  aTlvTypes      网络诊断TLV类型的数组。目前只允许使用类型9。
 * @param[in]  aCount         aTlvTypes中的类型数
 *
 * @retval OT_ERROR_NONE已成功将DIAG_RST.ntf排队。
 * @retval OT_ERROR_NO_BUFS可用的消息缓冲区不足，无法发送DIAG_RST.ntf。
 *
 */
otError otThreadSendDiagnosticReset(otInstance *        aInstance,
                                    const otIp6Address *aDestination,
                                    const uint8_t       aTlvTypes[],
                                    uint8_t             aCount);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_NETDIAG_H_

