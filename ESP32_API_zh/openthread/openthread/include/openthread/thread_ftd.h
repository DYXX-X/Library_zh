/*
 *  版权所有（c）2016-2017，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread线程API（仅限FTD）。
 */

#ifndef OPENTHREAD_THREAD_FTD_H_
#define OPENTHREAD_THREAD_FTD_H_

#include <openthread/link.h>
#include <openthread/message.h>
#include <openthread/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api线程路由器
 *
 * @{
 *
 */

/**
 * 此结构保存线程子级的诊断信息
 *
 */
typedef struct
{
    otExtAddress mExtAddress;           ///<IEEE 802.15.4扩展地址
    uint32_t     mTimeout;              ///<超时
    uint32_t     mAge;                  ///<上次听到的时间
    uint16_t     mRloc16;               ///< RLOC16
    uint16_t     mChildId;              ///<子ID
    uint8_t      mNetworkDataVersion;   ///<网络数据版本
    uint8_t      mLinkQualityIn;        ///<链接质量输入
    int8_t       mAverageRssi;          ///<平均RSSI
    int8_t       mLastRssi;             ///<最后观察到的RSSI
    uint16_t     mFrameErrorRate;       ///<帧错误率（0xffff->100%）。需要错误跟踪功能。
    uint16_t     mMessageErrorRate;     ///<（IPv6）消息错误率（0xffff->100%）。需要错误跟踪功能。
    uint16_t     mQueuedMessageCnt;     ///<子项的排队消息数。
    uint8_t      mVersion;              ///<MLE版本
    bool         mRxOnWhenIdle : 1;     ///空闲时<rx打开
    bool         mFullThreadDevice : 1; ///<全线程设备
    bool         mFullNetworkData : 1;  ///<完整网络数据
    bool         mIsStateRestoring : 1; ///<处于恢复状态
    bool         mIsCslSynced : 1;      ///<子CSL是否同步
} otChildInfo;

#define OT_CHILD_IP6_ADDRESS_ITERATOR_INIT 0 ///<otChildIP6AddressIterator的初始化器

typedef uint16_t otChildIp6AddressIterator; ///<用于遍历线程子项的IPv6地址。

/**
 * 此枚举定义EID缓存条目状态。
 *
 */
typedef enum otCacheEntryState
{
    OT_CACHE_ENTRY_STATE_CACHED      = 0, // 条目已缓存并正在使用。
    OT_CACHE_ENTRY_STATE_SNOOPED     = 1, // 通过窥探优化（检查接收的消息）创建条目。
    OT_CACHE_ENTRY_STATE_QUERY       = 2, // 条目表示EID的持续查询。
    OT_CACHE_ENTRY_STATE_RETRY_QUERY = 3, // 条目处于重试等待模式（先前的查询未得到响应）。
} otCacheEntryState;

/**
 * 此结构表示EID缓存条目。
 *
 */
typedef struct otCacheEntryInfo
{
    otIp6Address      mTarget;             ///<目标EID
    otShortAddress    mRloc16;             ///< RLOC16
    otCacheEntryState mState;              ///<进入状态
    bool              mCanEvict : 1;       ///<指示是否可以收回条目。
    bool              mValidLastTrans : 1; ///<表示上次交易时间和ML-EID是否有效。
    uint32_t          mLastTransTime;      ///<上次事务时间（适用于缓存状态）。
    otIp6Address      mMeshLocalEid;       ///<网格本地EID（适用于缓存状态下的条目）。
    uint16_t          mTimeout;            ///<超时（秒）（如果处于窥探/查询/重试查询状态，则适用）。
    uint16_t          mRetryDelay;         ///<重试延迟（秒）（如果处于查询重试状态，则适用）。
} otCacheEntryInfo;

/**
 * 此类型表示用于遍历EID缓存表项的迭代器。
 *
 * 要初始化迭代器并从缓存表中的第一个条目开始，请将其结构中的所有字段设置为零（例如，“memset”迭代器设置为零）。
 *
 */
typedef struct otCacheEntryIterator
{
    const void *mData[2]; ///<核心实现使用的不透明数据。用户不应更改。
} otCacheEntryIterator;

/**
 * 获取当前允许的最大子级数。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 当前允许的最大子级数。
 *
 * @sa otThreadSetMaxAllowedChildren
 *
 */
uint16_t otThreadGetMaxAllowedChildren(otInstance *aInstance);

/**
 * 设置当前允许的最大子级数。
 *
 * 仅当线程协议操作停止时，才能设置此参数。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMaxChildren  允许的最大子项数。
 *
 * @retval  OT_ERROR_NONE已成功设置最大值。
 * @retval  OT_ERROR_INVALID_ARGS如果@p aMaxChildren不在范围[1，OPENTHREAD_CONFIG_MLE_MAX_CHILDREN]内。
 * @retval  OT_ERROR_INVALID_STATE如果线程未停止。
 *
 * @sa otThreadGetMaxAllowedChildren
 *
 */
otError otThreadSetMaxAllowedChildren(otInstance *aInstance, uint16_t aMaxChildren);

/**
 * 此方法指示设备是否符合路由器条件。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval TRUE如果设备符合路由器条件。
 * @retval FALSE如果设备不符合路由器条件。
 *
 */
bool otThreadIsRouterEligible(otInstance *aInstance);

/**
 * 此函数设置设备是否符合路由器条件。
 *
 * If @p aQualified为false，并且设备当前作为路由器运行，此调用将导致设备分离并尝试作为子设备重新连接。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aEligible  TRUE将设备配置为路由器合格，否则为FALSE。
 *
 * @retval OT_ERROR_NONE成功设置路由器合格配置。
 * @retval OT_ERROR_NOT_CAPABLE设备无法成为路由器。
 *
 */
otError otThreadSetRouterEligible(otInstance *aInstance, bool aEligible);

/**
 * 设置首选路由器Id。
 *
 * 成为路由器/领导者后，节点尝试使用此路由器Id。如果未设置首选路由器Id或无法使用，则选择随机生成的路由器Id。只有在分离或禁用设备角色时，才能设置此属性。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aRouterId    首选路由器Id。
 *
 * @retval OT_ERROR_NONE已成功设置首选路由器Id。
 * @retval 无法设置OT_ERROR_INVALID_STATE（角色未分离或禁用）
 *
 */
otError otThreadSetPreferredRouterId(otInstance *aInstance, uint8_t aRouterId);

/**
 * 获取在“领导者”角色中操作时使用的“线程领导者权重”。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns “螺纹引线权重”值。
 *
 * @sa otThreadSet引线权重
 *
 */
uint8_t otThreadGetLocalLeaderWeight(otInstance *aInstance);

/**
 * 设置在“引线”角色中操作时使用的“引线权重”。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aWeight   “螺纹引线权重”值。
 *
 * @sa otThreadGetLeader权重
 *
 */
void otThreadSetLocalLeaderWeight(otInstance *aInstance, uint8_t aWeight);

/**
 * 获取在Leader角色中操作时使用的首选线程Leader分区Id。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 线程引线分区Id值。
 *
 */
uint32_t otThreadGetPreferredLeaderPartitionId(otInstance *aInstance);

/**
 * 设置在Leader角色中操作时使用的首选线程Leader分区Id。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aPartitionId  线程引线分区Id值。
 *
 */
void otThreadSetPreferredLeaderPartitionId(otInstance *aInstance, uint32_t aPartitionId);

/**
 * 获取Joiner UDP端口。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns Joiner UDP端口号。
 *
 * @sa otThreadSetJoinerUdp端口
 *
 */
uint16_t otThreadGetJoinerUdpPort(otInstance *aInstance);

/**
 * 设置Joiner UDP端口。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aJoinerUdpPort  Joiner UDP端口号。
 *
 * @retval  OT_ERROR_NONE已成功设置Joiner UDP端口。
 *
 * @sa otThreadGetJoinerUdp端口
 *
 */
otError otThreadSetJoinerUdpPort(otInstance *aInstance, uint16_t aJoinerUdpPort);

/**
 * 设置带外转向数据。
 *
 * 应设置配置选项“OPENTHREAD_CONFIG_MLE_STEERING_DATA_SET_OOB_ENABLE”，以启用带外转向数据的设置。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aExtAddress     用于更新转向数据的地址。全部为零以清除转向数据（无转向数据）。所有0xFF将转向数据/布隆过滤器设置为接受/允许所有。然后将特定的EUI64添加到当前转向数据/布隆滤波器。
 *
 */
void otThreadSetSteeringData(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 获取Leader角色中使用的CONTEXT_ID_REUSE_DELAY参数。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns CONTEXT_ID_REUSE_DELAY值。
 *
 * @sa otThreadSetContextIdReuseDelay
 *
 */
uint32_t otThreadGetContextIdReuseDelay(otInstance *aInstance);

/**
 * 设置Leader角色中使用的CONTEXT_ID_REUSE_DELAY参数。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aDelay    CONTEXT_ID_REUSE_DELAY值。
 *
 * @sa otThreadGetContextIdReuseDelay
 *
 */
void otThreadSetContextIdReuseDelay(otInstance *aInstance, uint32_t aDelay);

/**
 * 获取路由器角色中使用的NETWORK_ID_TIMEOUT参数。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns NETWORK_ID_TIMEOUT值。
 *
 * @sa otThreadSetNetworkIdTimeout
 *
 */
uint8_t otThreadGetNetworkIdTimeout(otInstance *aInstance);

/**
 * 设置Leader角色中使用的NETWORK_ID_TIMEOUT参数。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aTimeout  NETWORK_ID_TIMEOUT值。
 *
 * @sa otThreadGetNetworkId超时
 *
 */
void otThreadSetNetworkIdTimeout(otInstance *aInstance, uint8_t aTimeout);

/**
 * 获取REED角色中使用的ROUTER_UPGRADE_THRESHOLD参数。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns ROUTER_UPGRADE_THRESHOLD值。
 *
 * @sa otThreadSetRouter升级阈值
 *
 */
uint8_t otThreadGetRouterUpgradeThreshold(otInstance *aInstance);

/**
 * 设置Leader角色中使用的ROUTER_UPGRADE_THRESHOLD参数。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aThreshold  ROUTER_UPGRADE_THRESHOLD值。
 *
 * @sa otThreadGetRouter升级阈值
 *
 */
void otThreadSetRouterUpgradeThreshold(otInstance *aInstance, uint8_t aThreshold);

/**
 * 释放设备在Leader角色中分配的路由器ID。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aRouterId  要发布的路由器ID。有效范围为[0，62]。
 *
 * @retval OT_ERROR_NONE已成功释放路由器id。
 * @retval OT_ERROR_INVALID_ARGS@p aRouterId不在范围[0，62]内。
 * @retval OT_ERROR_INVALID_STATE设备当前未作为领导者运行。
 * @retval OT_ERROR_NOT_FOUND当前未分配路由器id。
 *
 */
otError otThreadReleaseRouterId(otInstance *aInstance, uint8_t aRouterId);

/**
 * 尝试成为路由器。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE成功开始尝试成为路由器。
 * @retval OT_ERROR_INVALID_STATE线程已禁用。
 */
otError otThreadBecomeRouter(otInstance *aInstance);

/**
 * 成为领导者并开始新的分区。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE成功成为领导者并开始新分区。
 * @retval OT_ERROR_INVALID_STATE线程已禁用。
 */
otError otThreadBecomeLeader(otInstance *aInstance);

/**
 * 获取ROUTER角色中使用的ROUTER_DOWNGRADE_THRESHOLD参数。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns ROUTER_DOWNGRADE_THRESHOLD值。
 *
 * @sa otThreadSetRouter降级阈值
 *
 */
uint8_t otThreadGetRouterDowngradeThreshold(otInstance *aInstance);

/**
 * 设置Leader角色中使用的ROUTER_DOWNGRADE_THRESHOLD参数。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aThreshold  ROUTER_DOWNGRADE_THRESHOLD值。
 *
 * @sa otThreadGetRouter降级阈值
 *
 */
void otThreadSetRouterDowngradeThreshold(otInstance *aInstance, uint8_t aThreshold);

/**
 * 获取REED/ROUTER角色中使用的ROUTER_SELECTION_JITTER参数。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 *
 * @returns ROUTER_SELECTION_JITTER值。
 *
 * @sa otThreadSet路由器选择抖动
 *
 */
uint8_t otThreadGetRouterSelectionJitter(otInstance *aInstance);

/**
 * 设置REED/ROUTER角色中使用的ROUTER_SELECTION_JITTER参数。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 * @param[in]  aRouterJitter  ROUTER_SELECTION_JITTER值。
 *
 * @sa otThreadGetRouterSelection抖动
 *
 */
void otThreadSetRouterSelectionJitter(otInstance *aInstance, uint8_t aRouterJitter);

/**
 * 该功能通过其Child ID或RLOC16保留所连接Child的诊断信息。
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 * @param[in]   aChildId    附加子项的子ID或RLOC16。
 * @param[out]  aChildInfo  指向放置子信息的位置的指针。
 *
 * @retval OT_ERROR_NONE@p aChildInfo已使用给定ID的信息成功更新。
 * @retval OT_ERROR_NOT_FOUND没有具有此子ID的有效子级。
 * @retval OT_ERROR_INVALID_ARGS如果@p aChildInfo为空。
 *
 */
otError otThreadGetChildInfoById(otInstance *aInstance, uint16_t aChildId, otChildInfo *aChildInfo);

/**
 * 该函数通过内部表索引保留附加子项的诊断信息。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[in]   aChildIndex  表索引。
 * @param[out]  aChildInfo   指向放置子信息的位置的指针。
 *
 * @retval OT_ERROR_NONE@p aChildInfo已成功更新为给定索引的信息。
 * @retval OT_ERROR_NOT_FOUND此索引中没有有效的子级。
 * @retval OT_ERROR_INVALID_ARGS@p aChildInfo为NULL，或者@p aCildIndex超出范围（高于最大表索引）。
 *
 * @sa otGetMaxAllowedChildren
 *
 */
otError otThreadGetChildInfoByIndex(otInstance *aInstance, uint16_t aChildIndex, otChildInfo *aChildInfo);

/**
 * 此函数获取给定子级的下一个IPv6地址（使用迭代器）。
 *
 * @param[in]     aInstance    指向OpenThread实例的指针。
 * @param[in]     aChildIndex  子索引。
 * @param[inout]  aIterator    迭代器的指针。成功后，迭代器将更新为指向列表中的下一个条目。要获得第一个IPv6地址，迭代器应设置为OT_CHILD_IP6_address_iterator_INIT。
 * @param[out]    aAddress     指向放置子节点下一个地址的IPv6地址的指针（成功时）。
 *
 * @retval OT_ERROR_NONE已成功找到下一个IPv6地址（@p aAddress已成功更新）。
 * @retval OT_ERROR_NOT_FOUND子级没有后续的IPv6地址条目。
 * @retval OT_ERROR_INVALID_ARGS@p aIterator或@p aAddress为空，或者@p aChildIndex处的子级无效。
 *
 * @sa otThreadGetChildInfo（按索引）
 *
 */
otError otThreadGetChildNextIp6Address(otInstance *               aInstance,
                                       uint16_t                   aChildIndex,
                                       otChildIp6AddressIterator *aIterator,
                                       otIp6Address *             aAddress);

/**
 * 获取当前路由器ID序列。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 路由器ID序列。
 *
 */
uint8_t otThreadGetRouterIdSequence(otInstance *aInstance);

/**
 * 该函数返回允许的最大路由器ID
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 *
 * @returns 允许的最大路由器ID。
 *
 */
uint8_t otThreadGetMaxRouterId(otInstance *aInstance);

/**
 * 该函数保留给定线程路由器的诊断信息。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[in]   aRouterId    给定路由器的路由器ID或RLOC16。
 * @param[out]  aRouterInfo  指向路由器信息放置位置的指针。
 *
 * @retval OT_ERROR_NONE已成功检索到给定id的路由器信息。
 * @retval OT_ERROR_NOT_FOUND没有具有给定id的路由器条目。
 * @retval OT_ERROR_INVALID_ARGS@p aRouterInfo为空。
 *
 */
otError otThreadGetRouterInfo(otInstance *aInstance, uint16_t aRouterId, otRouterInfo *aRouterInfo);

/**
 * 此函数获取下一个EID缓存条目（使用迭代器）。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[out]   aEntryInfo  指向放置EID缓存条目信息的位置的指针。
 * @param[inout] aIterator   指向迭代器的指针。它将被更新以指向下一个成功条目。要获得第一个条目，请通过将迭代器的所有字段设置为零（例如，迭代器结构的“memset”设置为零）来初始化迭代器。
 *
 * @retval OT_ERROR_NONE已成功为下一个EID缓存条目填充@p aEntryInfo。
 * @retval OT_ERROR_NOT_FOUND地址缓存表中没有更多条目。
 *
 */
otError otThreadGetNextCacheEntry(otInstance *aInstance, otCacheEntryInfo *aEntryInfo, otCacheEntryIterator *aIterator);

/**
 * 获取线程PSKc
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 * @param[out]  aPskc       指向“otPskc”的指针，以返回检索到的线程PSKc。
 *
 * @sa otThreadSetPskc
 *
 */
void otThreadGetPskc(otInstance *aInstance, otPskc *aPskc);

/**
 * 获取存储的线程PSKc的密钥引用
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`。
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 *
 * @returns PSKc的关键参考
 *
 * @sa otThreadSetPskcRef
 *
 */
otPskcRef otThreadGetPskcRef(otInstance *aInstance);

/**
 * 设置线程PSKc
 *
 * 仅当禁用线程协议时，此功能才会成功。成功调用此函数也会使非易失性内存中的活动和挂起操作数据集失效。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aPskc       指向新线程PSKc的指针。
 *
 * @retval OT_ERROR_NONE成功设置线程PSKc。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThreadGetPskc
 *
 */
otError otThreadSetPskc(otInstance *aInstance, const otPskc *aPskc);

/**
 * 设置线程PSKc
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`。
 *
 * 仅当禁用线程协议时，此功能才会成功。成功调用此函数也会使非易失性内存中的活动和挂起操作数据集失效。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aPskcRef    新线程PSKc的关键参考。
 *
 * @retval OT_ERROR_NONE成功设置线程PSKc。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 * @sa otThreadGetPskcRef
 *
 */
otError otThreadSetPskcRef(otInstance *aInstance, otPskcRef aKeyRef);

/**
 * 获取分配的父优先级。
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 *
 * @returns 分配的父优先级值-2表示未分配。
 *
 * @sa otThreadSet父优先级
 *
 */
int8_t otThreadGetParentPriority(otInstance *aInstance);

/**
 * 设置父优先级。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aParentPriority  父优先级值。
 *
 * @retval OT_ERROR_NONE成功设置父优先级。
 * @retval OT_ERROR_INVALID_ARGS如果父优先级值不在1、0、-1和-2之间。
 *
 * @sa otThreadGetParentPriority
 *
 */
otError otThreadSetParentPriority(otInstance *aInstance, int8_t aParentPriority);

/**
 * 此函数获取每个MTD子设备可以作为父设备向该设备注册的最大IP地址数。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 每个MTD子级可以作为父级向此设备注册的最大IP地址数。
 *
 * @sa otThreadSet最大子IP地址
 *
 */
uint8_t otThreadGetMaxChildIpAddresses(otInstance *aInstance);

/**
 * 此函数设置/恢复每个MTD子设备可以作为父设备向该设备注册的最大IP地址数。
 *
 * @note 此API需要`OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE`，并且仅由线程测试线束用于限制参考父级的地址注册，以便测试MTD DUT反应。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aMaxIpAddresses  每个MTD子级可以作为父级向此设备注册的最大IP地址数。0以清除设置并恢复默认值。
 *
 * @retval OT_ERROR_NONE已成功设置/清除号码。
 * @retval OT_ERROR_INVALID_ARGS如果超过允许的最大数量。
 *
 * @sa otThreadGetMaxChildIpAddresses（otThreadGetMax子IP地址）
 *
 */
otError otThreadSetMaxChildIpAddresses(otInstance *aInstance, uint8_t aMaxIpAddresses);

/**
 * 此枚举定义了“otNeighborTableCallback”中使用的常量，以指示邻居表中的更改。
 *
 */
typedef enum
{
    OT_NEIGHBOR_TABLE_EVENT_CHILD_ADDED,        ///<正在添加子项。
    OT_NEIGHBOR_TABLE_EVENT_CHILD_REMOVED,      ///<正在删除一个孩子。
    OT_NEIGHBOR_TABLE_EVENT_CHILD_MODE_CHANGED, ///<现有儿童模式已更改。
    OT_NEIGHBOR_TABLE_EVENT_ROUTER_ADDED,       ///<正在添加路由器。
    OT_NEIGHBOR_TABLE_EVENT_ROUTER_REMOVED,     ///<正在删除路由器。
} otNeighborTableEvent;

/**
 * 此类型表示邻居表条目信息（子或路由器），并用作邻居表回调“otNeighborTableCallback”中的参数。
 *
 */
typedef struct
{
    otInstance *mInstance; ///<OpenThread实例。
    union
    {
        otChildInfo    mChild;  ///<子邻居信息。
        otNeighborInfo mRouter; ///<路由器邻居信息。
    } mInfo;
} otNeighborTableEntryInfo;

/**
 * 调用此函数指针以通知邻居表中存在更改。
 *
 * @param[in]  aEvent      事件标志。
 * @param[in]  aEntryInfo  指向表条目信息的指针。
 *
 */
typedef void (*otNeighborTableCallback)(otNeighborTableEvent aEvent, const otNeighborTableEntryInfo *aEntryInfo);

/**
 * 此函数注册邻居表回调函数。
 *
 * 当邻居表发生变化时（例如，正在添加/删除子项或路由器邻居项或更改现有子项的模式），将调用提供的回调（如果非NULL）。
 *
 * 对该方法的后续调用将覆盖先前的回调。请注意，在更新邻居/子表时调用此回调，并且总是在“otStateChangedCallback”之前调用。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aCallback  指向回调处理程序函数的指针。
 *
 */
void otThreadRegisterNeighborTableCallback(otInstance *aInstance, otNeighborTableCallback aCallback);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_THREAD_FTD_H_

