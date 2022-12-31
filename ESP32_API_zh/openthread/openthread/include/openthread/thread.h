/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread线程API（用于FTD和MTD）。
 */

#ifndef OPENTHREAD_THREAD_H_
#define OPENTHREAD_THREAD_H_

#include <openthread/dataset.h>
#include <openthread/link.h>
#include <openthread/message.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api线程常规
 *
 * @note 此模块中的函数要求“OPENTHREAD_FTD=1”或“OPENTHRAD_MTD=1”。
 *
 * @{
 *
 */

/**
 * 线程基TLV的最大值长度。
 */
#define OT_NETWORK_BASE_TLV_MAX_LENGTH 254

#define OT_NETWORK_MAX_ROUTER_ID 62 ///<最大路由器ID

/**
 * 表示线程设备角色。
 *
 */
typedef enum
{
    OT_DEVICE_ROLE_DISABLED = 0, ///<线程堆栈已禁用。
    OT_DEVICE_ROLE_DETACHED = 1, ///<当前未参与线程网络/分区。
    OT_DEVICE_ROLE_CHILD    = 2, ///<线程子角色。
    OT_DEVICE_ROLE_ROUTER   = 3, ///<线程路由器角色。
    OT_DEVICE_ROLE_LEADER   = 4, ///<线程负责人角色。
} otDeviceRole;

/**
 * 此结构表示MLE链路模式配置。
 */
typedef struct otLinkModeConfig
{
    bool mRxOnWhenIdle : 1; ///<1，如果发送方在不发送时打开了其接收器。否则为0。
    bool mDeviceType : 1;   ///<1，如果发送方是FTD。否则为0。
    bool mNetworkData : 1;  ///<1，如果发件人需要完整的网络数据。否则为0。
} otLinkModeConfig;

/**
 * 此结构保存相邻线程节点的诊断信息
 *
 */
typedef struct
{
    otExtAddress mExtAddress;           ///<IEEE 802.15.4扩展地址
    uint32_t     mAge;                  ///<上次听到的时间
    uint16_t     mRloc16;               ///< RLOC16
    uint32_t     mLinkFrameCounter;     ///<链接帧计数器
    uint32_t     mMleFrameCounter;      ///<MLE帧计数器
    uint8_t      mLinkQualityIn;        ///<链接质量输入
    int8_t       mAverageRssi;          ///<平均RSSI
    int8_t       mLastRssi;             ///<最后观察到的RSSI
    uint16_t     mFrameErrorRate;       ///<帧错误率（0xffff->100%）。需要错误跟踪功能。
    uint16_t     mMessageErrorRate;     ///<（IPv6）消息错误率（0xffff->100%）。需要错误跟踪功能。
    bool         mRxOnWhenIdle : 1;     ///空闲时<rx打开
    bool         mFullThreadDevice : 1; ///<全线程设备
    bool         mFullNetworkData : 1;  ///<完整网络数据
    bool         mIsChild : 1;          ///<邻居是孩子吗
} otNeighborInfo;

#define OT_NEIGHBOR_INFO_ITERATOR_INIT 0 ///<otNeighborInfoIterator的初始化器。

typedef int16_t otNeighborInfoIterator; ///<用于遍历邻居表。

/**
 * 此结构表示线程引线数据。
 *
 */
typedef struct otLeaderData
{
    uint32_t mPartitionId;       ///<分区ID
    uint8_t  mWeighting;         ///<引线重量
    uint8_t  mDataVersion;       ///<完整网络数据版本
    uint8_t  mStableDataVersion; ///<稳定的网络数据版本
    uint8_t  mLeaderRouterId;    ///<领队路由器ID
} otLeaderData;

/**
 * 此结构保存线程路由器的诊断信息
 *
 */
typedef struct
{
    otExtAddress mExtAddress;          ///<IEEE 802.15.4扩展地址
    uint16_t     mRloc16;              ///< RLOC16
    uint8_t      mRouterId;            ///<路由器ID
    uint8_t      mNextHop;             ///<下一跳到路由器
    uint8_t      mPathCost;            ///<路由器路径成本
    uint8_t      mLinkQualityIn;       ///<链接质量输入
    uint8_t      mLinkQualityOut;      ///<链接质量输出
    uint8_t      mAge;                 ///<上次听到的时间
    bool         mAllocated : 1;       ///<是否分配了路由器ID
    bool         mLinkEstablished : 1; ///<是否使用路由器ID建立了链接
} otRouterInfo;

/**
 * 此结构表示IP级别计数器。
 *
 */
typedef struct otIpCounters
{
    uint32_t mTxSuccess; ///<成功传输的IPv6数据包数。
    uint32_t mRxSuccess; ///<成功接收的IPv6数据包数。
    uint32_t mTxFailure; ///<传输失败的IPv6数据包数。
    uint32_t mRxFailure; ///<无法接收的IPv6数据包数。
} otIpCounters;

/**
 * 此结构表示线程MLE计数器。
 *
 */
typedef struct otMleCounters
{
    uint16_t mDisabledRole;                  ///<设备进入OT_device_ROLE_DISABLED角色的次数。
    uint16_t mDetachedRole;                  ///<设备进入OT_device_ROLE_DETACHED角色的次数。
    uint16_t mChildRole;                     ///<设备进入OT_device_ROLE_CHILD角色的次数。
    uint16_t mRouterRole;                    ///<设备进入OT_device_ROLE_ROUTER角色的次数。
    uint16_t mLeaderRole;                    ///<设备进入OT_device_ROLE_LEADER角色的次数。
    uint16_t mAttachAttempts;                ///<设备分离时的连接尝试次数。
    uint16_t mPartitionIdChanges;            ///<分区ID的更改数。
    uint16_t mBetterPartitionAttachAttempts; ///<尝试连接到更好分区的次数。

    /**
     * 设备更改其父级的次数。
     *
     * 支持此计数器需要启用功能选项OPENTHREAD_CONFIG_MLE_INFORM_PREVIOUS_PARTENT_ON_REATTACH。
     *
     * 如果设备从其当前父级分离并连接到另一个父级，甚至在启用定期父级搜索功能时连接设备时（请参阅选项OPENTHREAD_COONFIG_parent_search_ENABLE），也可能发生父级更改。
     *
     */
    uint16_t mParentChanges;
} otMleCounters;

/**
 * 此结构表示MLE父响应数据。
 *
 */
typedef struct otThreadParentResponseInfo
{
    otExtAddress mExtAddr;      ///<IEEE 802.15.4父级扩展地址
    uint16_t     mRloc16;       ///<母公司的短地址
    int8_t       mRssi;         ///<母公司的Rssi
    int8_t       mPriority;     ///<父优先级
    uint8_t      mLinkQuality3; ///<父链接质量3
    uint8_t      mLinkQuality2; ///<父链接质量2
    uint8_t      mLinkQuality1; ///<父链接质量1
    bool         mIsAttached;   ///<是否附加了接收父响应的节点
} otThreadParentResponseInfo;

/**
 * 此函数启动线程协议操作。
 *
 * 调用此函数时，接口必须打开。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 * @param[in] aEnabled  如果线程已启用，则为TRUE，否则为FALSE。
 *
 * @retval OT_ERROR_NONE已成功启动线程协议操作。
 * @retval OT_ERROR_INVALID_STATE网络接口未启动。
 *
 */
otError otThreadSetEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此函数获取线程协议版本。
 *
 * @returns 线程协议版本。
 *
 */
uint16_t otThreadGetVersion(void);

/**
 * 此函数指示节点是否是网络上唯一的路由器。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @retval TRUE它是网络中唯一的路由器。
 * @retval FALSE它是子路由器或不是网络中的单个路由器。
 *
 */
bool otThreadIsSingleton(otInstance *aInstance);

/**
 * 此函数启动线程发现扫描。
 *
 * @param[in]  aInstance              指向OpenThread实例的指针。
 * @param[in]  aScanChannels          指示要扫描哪些信道的位向量（例如OT_CHANNEL_11_MASK）。
 * @param[in]  aPanId                 PAN ID筛选器（设置为广播PAN以禁用筛选器）。
 * @param[in]  aJoiner                发现请求TLV中加入者标志的值。
 * @param[in]  aEnableEui64Filtering  TRUE用于过滤EUI-64上的响应，否则为FALSE。
 * @param[in]  aCallback              指向在接收MLE发现响应或扫描完成时调用的函数的指针。
 * @param[in]  aCallbackContext       指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功启动线程发现扫描。
 * @retval OT_ERROR_INVALID_STATE IPv6接口未启用（netif未启动）。
 * @retval OT_ERROR_NO_BUFS无法为发现请求分配消息。
 * @retval OT_ERROR_BUSY线程发现扫描已在进行中。
 *
 */
otError otThreadDiscover(otInstance *             aInstance,
                         uint32_t                 aScanChannels,
                         uint16_t                 aPanId,
                         bool                     aJoiner,
                         bool                     aEnableEui64Filtering,
                         otHandleActiveScanResult aCallback,
                         void *                   aCallbackContext);

/**
 * 此函数确定当前是否正在进行MLE线程发现。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 */
bool otThreadIsDiscoverInProgress(otInstance *aInstance);

/**
 * 此方法在发现线程网络时设置线程连接程序播发。
 *
 * 线程加入者广告用于允许加入者通过新提议的加入者广告TLV发布其自己的应用程序特定信息（如供应商ID、产品ID、鉴别器等），并使专员或专员候选人无需人工交互即可获得该信息。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aOui             加入者广告中包含的供应商IEEE OUI值。只使用最低有效的3个字节，而最高有效的字节将被忽略。
 * @param[in]  aAdvData         指向将包含在Joiner广告中的AdvData的指针。
 * @param[in]  aAdvDataLength   AdvData的长度（字节）。
 *
 * @retval OT_ERROR_NONE已成功设置加入者播发。
 * @retval OT_ERROR_INVALID_ARGS AdvData无效。
 *
 */
otError otThreadSetJoinerAdvertisement(otInstance *   aInstance,
                                       uint32_t       aOui,
                                       const uint8_t *aAdvData,
                                       uint8_t        aAdvDataLength);

#define OT_JOINER_ADVDATA_MAX_LENGTH 64 ///<加入者广告的最大AdvData长度

/**
 * 获取在子角色中操作时使用的线程子超时。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 线程子超时值（秒）。
 *
 * @sa otThreadSet子超时
 *
 */
uint32_t otThreadGetChildTimeout(otInstance *aInstance);

/**
 * 设置在子角色中操作时使用的线程子超时。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aTimeout  超时值（秒）。
 *
 * @sa otThreadGetChildTimeout
 *
 */
void otThreadSetChildTimeout(otInstance *aInstance, uint32_t aTimeout);

/**
 * 获取IEEE 802.15.4扩展PAN ID。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向IEEE 802.15.4扩展PAN ID的指针。
 *
 * @sa otThreadSet扩展PanId
 *
 */
const otExtendedPanId *otThreadGetExtendedPanId(otInstance *aInstance);

/**
 * 设置IEEE 802.15.4扩展PAN ID。
 *
 * 只有在禁用线程协议时才能调用此函数。成功调用此函数将使非易失性内存中的活动和挂起操作数据集无效。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aExtendedPanId  指向IEEE 802.15.4扩展PAN ID的指针。
 *
 * @retval OT_ERROR_NONE已成功设置扩展PAN ID。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThreadGetExtendedPanId
 *
 */
otError otThreadSetExtendedPanId(otInstance *aInstance, const otExtendedPanId *aExtendedPanId);

/**
 * 此函数返回指向Leader的RLOC的指针。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aLeaderRloc  指向领导者RLOC的指针。
 *
 * @retval OT_ERROR_NONE领导者的RLOC已成功写入@p aLeaderRloc。
 * @retval OT_ERROR_INVALID_ARGS@p aLeaderRloc为空。
 * @retval OT_ERROR_DETACHED当前未连接到线程分区。
 *
 */
otError otThreadGetLeaderRloc(otInstance *aInstance, otIp6Address *aLeaderRloc);

/**
 * 获取MLE链接模式配置。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns MLE链路模式配置。
 *
 * @sa otThreadSet链接模式
 *
 */
otLinkModeConfig otThreadGetLinkMode(otInstance *aInstance);

/**
 * 设置MLE链路模式配置。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aConfig   指向链接模式配置的指针。
 *
 * @retval OT_ERROR_NONE成功设置MLE链路模式配置。
 *
 * @sa otThreadGetLinkMode（ot线程获取链接模式）
 *
 */
otError otThreadSetLinkMode(otInstance *aInstance, otLinkModeConfig aConfig);

/**
 * 获取线程网络密钥。
 *
 * @param[in]   aInstance     指向OpenThread实例的指针。
 * @param[out]  aNetworkKey   指向“otNetworkkey”以返回线程网络密钥的指针。
 *
 * @sa otThreadSet网络密钥
 *
 */
void otThreadGetNetworkKey(otInstance *aInstance, otNetworkKey *aNetworkKey);

/**
 * 获取线程网络密钥的`otNetworkKeyRef`。
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`。
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 *
 * @returns 对内存中存储的线程网络密钥的引用。
 *
 * @sa otThreadSetNetworkKeyRef
 *
 */
otNetworkKeyRef otThreadGetNetworkKeyRef(otInstance *aInstance);

/**
 * 设置线程网络密钥。
 *
 * 仅当禁用线程协议时，此函数才会成功。成功调用此函数将使非易失性内存中的活动和挂起操作数据集无效。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aKey        指向包含线程网络密钥的缓冲区的指针。
 *
 * @retval OT_ERROR_NONE已成功设置线程网络密钥。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThreadGetNetworkKey
 *
 */
otError otThreadSetNetworkKey(otInstance *aInstance, const otNetworkKey *aKey);

/**
 * 将线程网络密钥设置为`otNetworkKeyRef`。
 *
 * 仅当禁用线程协议时，此函数才会成功。成功调用此函数将使非易失性内存中的活动和挂起操作数据集无效。
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aKeyRef     对线程网络密钥的引用。
 *
 * @retval OT_ERROR_NONE已成功设置线程网络密钥。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThreadGetNetworkKeyRef
 *
 */
otError otThreadSetNetworkKeyRef(otInstance *aInstance, otNetworkKeyRef aKeyRef);

/**
 * 此函数返回指向线程路由定位器（RLOC）地址的指针。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向线程路由定位器（RLOC）地址的指针。
 *
 */
const otIp6Address *otThreadGetRloc(otInstance *aInstance);

/**
 * 此函数返回指向网格本地EID地址的指针。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向网格本地EID地址的指针。
 *
 */
const otIp6Address *otThreadGetMeshLocalEid(otInstance *aInstance);

/**
 * 此函数返回指向网格本地前缀的指针。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向网格本地前缀的指针。
 *
 */
const otMeshLocalPrefix *otThreadGetMeshLocalPrefix(otInstance *aInstance);

/**
 * 此函数用于设置网格本地前缀。
 *
 * 仅当禁用线程协议时，此函数才会成功。成功调用此函数将使非易失性内存中的活动和挂起操作数据集无效。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aMeshLocalPrefix  指向网格本地前缀的指针。
 *
 * @retval OT_ERROR_NONE已成功设置网格本地前缀。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 */
otError otThreadSetMeshLocalPrefix(otInstance *aInstance, const otMeshLocalPrefix *aMeshLocalPrefix);

/**
 * 此函数返回线程链接本地IPv6地址。
 *
 * 使用IEEE802.15.4扩展地址作为接口标识符导出线程链接本地地址。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向线程链接本地IPv6地址的指针。
 *
 */
const otIp6Address *otThreadGetLinkLocalIp6Address(otInstance *aInstance);

/**
 * 此函数返回线程链接本地所有线程节点多播地址。
 *
 * 该地址是基于单播前缀的多播地址[RFC 3306]的链接本地地址，具有：
 *   -flgs设置为3（P=1和T=1）
 *   -范围设置为2
 *   -plen设置为64
 *   -网络前缀设置为“网格本地前缀”
 *   -组ID设置为1
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向线程链接本地所有线程节点多播地址的指针。
 *
 */
const otIp6Address *otThreadGetLinkLocalAllThreadNodesMulticastAddress(otInstance *aInstance);

/**
 * 此函数返回线程领域本地所有线程节点多播地址。
 *
 * 该地址是基于域本地单播前缀的多播地址[RFC 3306]，具有：
 *   -flgs设置为3（P=1和T=1）
 *   -范围设置为3
 *   -plen设置为64
 *   -网络前缀设置为“网格本地前缀”
 *   -组ID设置为1
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向线程领域本地所有线程节点多播地址的指针。
 *
 */
const otIp6Address *otThreadGetRealmLocalAllThreadNodesMulticastAddress(otInstance *aInstance);

/**
 * 此函数检索给定服务ID的服务ALOC。
 *
 * @param[in]   aInstance     指向OpenThread实例的指针。
 * @param[in]   aServiceId    要获取ALOC的服务ID。
 * @param[out]  aServiceAloc  用于输出服务ALOC的指针。不能为空。
 *
 * @retval OT_ERROR_NONE已成功检索服务ALOC。
 * @retval OT_ERROR_DETACHED线程接口当前未连接到线程分区。
 */
otError otThreadGetServiceAloc(otInstance *aInstance, uint8_t aServiceId, otIp6Address *aServiceAloc);

/**
 * 获取线程网络名称。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向线程网络名称的指针。
 *
 * @sa otThreadSet网络名称
 *
 */
const char *otThreadGetNetworkName(otInstance *aInstance);

/**
 * 设置线程网络名称。
 *
 * 仅当禁用线程协议时，此函数才会成功。成功调用此函数将使非易失性内存中的活动和挂起操作数据集无效。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aNetworkName  指向线程网络名称的指针。
 *
 * @retval OT_ERROR_NONE已成功设置线程网络名称。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThreadGetNetworkName（ot线程获取网络名称）
 *
 */
otError otThreadSetNetworkName(otInstance *aInstance, const char *aNetworkName);

/**
 * 获取线程域名。
 *
 * 此函数仅在线程1.2之后可用。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向线程域名的指针。
 *
 * @sa otThreadSet域名
 *
 */
const char *otThreadGetDomainName(otInstance *aInstance);

/**
 * 设置线程域名。
 *
 * 此函数仅在线程1.2之后可用。仅当禁用线程协议时，此函数才会成功。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aDomainName   指向线程域名的指针。
 *
 * @retval OT_ERROR_NONE已成功设置线程域名。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThread获取域名
 *
 */
otError otThreadSetDomainName(otInstance *aInstance, const char *aDomainName);

/**
 * 设置/清除为线程域单播地址手动指定的接口标识符。
 *
 * 此函数仅在启用“OPENTHREAD_CONFIG_DUA_ENABLE”时从线程1.2开始可用。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aIid        指向要设置的接口标识符或要清除的NULL的指针。
 *
 * @retval OT_ERROR_NONE成功设置/清除接口标识符。
 * @retval OT_ERROR_INVALID_ARGS保留指定的接口标识符。
 *
 * @sa otThreadGetFixedDua接口标识符
 */
otError otThreadSetFixedDuaInterfaceIdentifier(otInstance *aInstance, const otIp6InterfaceIdentifier *aIid);

/**
 * 获取为线程域单播地址手动指定的接口标识符。
 *
 * 此函数仅在启用“OPENTHREAD_CONFIG_DUA_ENABLE”时从线程1.2开始可用。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向手动设置的接口标识符的指针，如果未设置，则为NULL。
 *
 * @sa otThreadSetFixedDua接口标识符
 *
 */
const otIp6InterfaceIdentifier *otThreadGetFixedDuaInterfaceIdentifier(otInstance *aInstance);

/**
 * 获取thrKeySequenceCounter。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns thrKeySequenceCounter值。
 *
 * @sa otThreadSet键序列计数器
 *
 */
uint32_t otThreadGetKeySequenceCounter(otInstance *aInstance);

/**
 * 设置thrKeySequenceCounter。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aKeySequenceCounter  thrKeySequenceCounter值。
 *
 * @sa otThreadGetKeySequence计数器
 *
 */
void otThreadSetKeySequenceCounter(otInstance *aInstance, uint32_t aKeySequenceCounter);

/**
 * 获取thrKeySwitchGuardTime
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns thrKeySwitchGuardTime值（小时）。
 *
 * @sa otThreadSet键切换保护时间
 *
 */
uint32_t otThreadGetKeySwitchGuardTime(otInstance *aInstance);

/**
 * 设置thrKeySwitchGuardTime
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aKeySwitchGuardTime  thrKeySwitchGuardTime值（小时）。
 *
 * @sa otThreadGetKeySwitch保护时间
 *
 */
void otThreadSetKeySwitchGuardTime(otInstance *aInstance, uint32_t aKeySwitchGuardTime);

/**
 * 从线程网络分离。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功从线程网络分离。
 * @retval OT_ERROR_INVALID_STATE线程已禁用。
 *
 */
otError otThreadBecomeDetached(otInstance *aInstance);

/**
 * 尝试作为子对象重新附加。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE成功开始尝试成为孩子。
 * @retval OT_ERROR_INVALID_STATE线程已禁用。
 *
 */
otError otThreadBecomeChild(otInstance *aInstance);

/**
 * 此函数获取下一个邻居信息。它用于遍历邻居表的条目。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  迭代器上下文的指针。要获取第一个邻居条目，应将其设置为OT_neighbor_INFO_ITERATOR_INIT。
 * @param[out]    aInfo      指向邻居信息的指针。
 *
 * @retval OT_ERROR_NONE成功找到表中的下一个邻居条目。
 * @retval OT_ERROR_NOT_FOUND表中不存在后续邻居条目。
 * @retval OT_ERROR_INVALID_ARGS@p aIterator或@p aInfo为空。
 *
 */
otError otThreadGetNextNeighborInfo(otInstance *aInstance, otNeighborInfoIterator *aIterator, otNeighborInfo *aInfo);

/**
 * 获取设备角色。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_DEVICE_ROLE_DISABLED线程堆栈已禁用。
 * @retval OT_DEVICE_ROLE_DETACHED设备当前未参与线程网络/分区。
 * @retval OT_DEVICE_ROLE_CHILD设备当前作为线程子级运行。
 * @retval OT_DEVICE_ROLE_ROUTER设备当前作为线程路由器运行。
 * @retval OT_DEVICE_ROLE_LEADER设备当前作为线程引导器运行。
 *
 */
otDeviceRole otThreadGetDeviceRole(otInstance *aInstance);

/**
 * 将设备角色转换为可读字符串。
 *
 * @param[in] aRole   要转换的设备角色。
 *
 * @returns 表示@p aRole的字符串。
 *
 */
const char *otThreadDeviceRoleToString(otDeviceRole aRole);

/**
 * 此函数获取线程引线数据。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aLeaderData  指向引线数据放置位置的指针。
 *
 * @retval OT_ERROR_NONE已成功检索引线数据。
 * @retval OT_ERROR_DETACHED当前未连接。
 *
 */
otError otThreadGetLeaderData(otInstance *aInstance, otLeaderData *aLeaderData);

/**
 * 获取领队的路由器ID。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 领导者的路由器ID。
 *
 */
uint8_t otThreadGetLeaderRouterId(otInstance *aInstance);

/**
 * 获得领导者的体重。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 领导者的体重。
 *
 */
uint8_t otThreadGetLeaderWeight(otInstance *aInstance);

/**
 * 获取分区ID。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 分区ID。
 *
 */
uint32_t otThreadGetPartitionId(otInstance *aInstance);

/**
 * 获取RLOC16。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns RLOC16。
 *
 */
uint16_t otThreadGetRloc16(otInstance *aInstance);

/**
 * 该函数检索作为父级的线程路由器的诊断信息。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aParentInfo  指向父路由器信息所在位置的指针。
 *
 */
otError otThreadGetParentInfo(otInstance *aInstance, otRouterInfo *aParentInfo);

/**
 * 该函数检索线程父级的平均RSSI。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aParentRssi  指向父RSSI应该放置的位置的指针。
 *
 */
otError otThreadGetParentAverageRssi(otInstance *aInstance, int8_t *aParentRssi);

/**
 * 该函数从线程父级检索最后一个数据包的RSSI。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aLastRssi    指向最后一个RSSI应该放置的位置的指针。
 *
 * @retval OT_ERROR_NONE已成功检索RSSI数据。
 * @retval OT_ERROR_FAILED无法获取RSSI数据。
 * @retval OT_ERROR_INVALID_ARGS@p aLastRsi为空。
 *
 */
otError otThreadGetParentLastRssi(otInstance *aInstance, int8_t *aLastRssi);

/**
 * 获取IPv6计数器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns 指向IPv6计数器的指针。
 *
 */
const otIpCounters *otThreadGetIp6Counters(otInstance *aInstance);

/**
 * 重置IPv6计数器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otThreadResetIp6Counters(otInstance *aInstance);

/**
 * 获取线程MLE计数器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns 指向线程MLE计数器的指针。
 *
 */
const otMleCounters *otThreadGetMleCounters(otInstance *aInstance);

/**
 * 重置线程MLE计数器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otThreadResetMleCounters(otInstance *aInstance);

/**
 * 每次收到MLE父响应消息时都会调用此函数指针。
 *
 * @param[in]  aStats    指向堆栈上保存统计数据的位置的指针。
 * @param[in]  aContext  指向回调客户端特定上下文的指针。
 *
 */
typedef void (*otThreadParentResponseCallback)(otThreadParentResponseInfo *aInfo, void *aContext);

/**
 * 此函数注册回调以接收MLE父响应数据。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aCallback  指向在接收MLE父响应消息时调用的函数的指针。
 * @param[in]  aContext   指向回调客户端特定上下文的指针。
 *
 */
void otThreadRegisterParentResponseCallback(otInstance *                   aInstance,
                                            otThreadParentResponseCallback aCallback,
                                            void *                         aContext);

/**
 * 此结构表示线程发现请求数据。
 *
 */
typedef struct otThreadDiscoveryRequestInfo
{
    otExtAddress mExtAddress;   ///<IEEE 802.15.4请求者的扩展地址
    uint8_t      mVersion : 4;  ///<线程版本。
    bool         mIsJoiner : 1; ///<是否来自细木工。
} otThreadDiscoveryRequestInfo;

/**
 * 每次收到MLE发现请求消息时都会调用此函数指针。
 *
 * @param[in]  aInfo     指向发现请求信息数据的指针。
 * @param[in]  aContext  指向回调应用程序特定上下文的指针。
 *
 */
typedef void (*otThreadDiscoveryRequestCallback)(const otThreadDiscoveryRequestInfo *aInfo, void *aContext);

/**
 * 此函数设置回调以接收MLE发现请求数据。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aCallback  指向在接收MLE发现请求消息时调用的函数的指针。
 * @param[in]  aContext   指向回调应用程序特定上下文的指针。
 *
 */
void otThreadSetDiscoveryRequestCallback(otInstance *                     aInstance,
                                         otThreadDiscoveryRequestCallback aCallback,
                                         void *                           aContext);

/**
 * 此函数指针类型定义回调以通知“otThreadLocateAnycastDestination（）”请求的结果。
 *
 * @param[in] aContext            指向任意上下文的指针（注册回调时提供）。
 * @param[in] aError              处理请求时出错。OT_ERROR_NONE表示成功。OT_ERROR_RESPONSE_TIMEOUT表示找不到目标。OT_ERROR_ABORT表示请求已中止。
 * @param[in] aMeshLocalAddress   指向选播地址最近目标的网格本地EID的指针
 *                                when @p aError为OT_ERROR_NONE，否则为NULL。
 * @param[in] aRloc16             如果找到目标的RLOC16，则为无效RLOC16（0xfffe）。
 *
 */
typedef void (*otThreadAnycastLocatorCallback)(void *              aContext,
                                               otError             aError,
                                               const otIp6Address *aMeshLocalAddress,
                                               uint16_t            aRloc16);

/**
 * 此函数请求查找给定选播地址的最近目的地。
 *
 * 此功能仅在启用“OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE”时可用。
 *
 * 如果先前的请求正在进行，则对该函数的后续调用将取消并替换先前的请求。
 *
 * @param[in] aInstance         指向OpenThread实例的指针。
 * @param[in] aAnycastAddress   要查找的选播地址。不得为空。
 * @param[in] aCallback         用于报告结果的回调函数。
 * @param[in] aContext          与@p aCallback一起使用的任意上下文。
 *
 * @retval OT_ERROR_NONE请求成功启动@p将调用Callback来报告结果。
 * @retval OT_ERROR_INVALID_ARGS@p aAnycastAddress不是有效的anycast地址，或者@p aCallback为NULL。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法准备并发送请求消息。
 *
 */
otError otThreadLocateAnycastDestination(otInstance *                   aInstance,
                                         const otIp6Address *           aAnycastAddress,
                                         otThreadAnycastLocatorCallback aCallback,
                                         void *                         aContext);

/**
 * 此函数指示当前是否正在进行选播定位请求。
 *
 * 此功能仅在启用“OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE”时可用。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 如果当前正在进行选播定位请求，则为TRUE，否则为FALSE。
 *
 */
bool otThreadIsAnycastLocateInProgress(otInstance *aInstance);

/**
 * 此函数发送主动地址通知（ADDR_NTF.NTF）消息。
 *
 * 此函数仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aDestination  发送ADDR_NTF的目的地。ntf消息。
 * @param[in]  aTarget       ADDR_NTF的目标地址。ntf消息。
 * @param[in]  aMlIid        ADDR_NTF的ML-IID。ntf消息。
 *
 */
void otThreadSendAddressNotification(otInstance *              aInstance,
                                     otIp6Address *            aDestination,
                                     otIp6Address *            aTarget,
                                     otIp6InterfaceIdentifier *aMlIid);

/**
 * 此函数在主干链路上发送主动主干通知（PRO_BB.ntf）消息。
 *
 * 此函数仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。
 *
 * @param[in]  aInstance                    指向OpenThread实例的指针。
 * @param[in]  aTarget                      PRO_BB的目标地址。ntf消息。
 * @param[in]  aMlIid                       PRO_BB的ML-IID。ntf消息。
 * @param[in]  aTimeSinceLastTransaction    自上次事务以来的时间（秒）。
 *
 * @retval OT_ERROR_NONE已成功发送PRO_BB。主干链路上的ntf。
 * @retval OT_ERROR_NO_BUFS如果可用的消息缓冲区不足。
 *
 */
otError otThreadSendProactiveBackboneNotification(otInstance *              aInstance,
                                                  otIp6Address *            aTarget,
                                                  otIp6InterfaceIdentifier *aMlIid,
                                                  uint32_t                  aTimeSinceLastTransaction);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_THREAD_H_

