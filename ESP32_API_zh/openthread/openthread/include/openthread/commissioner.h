/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包含线程专员角色的函数。
 */

#ifndef OPENTHREAD_COMMISSIONER_H_
#define OPENTHREAD_COMMISSIONER_H_

#include <openthread/dataset.h>
#include <openthread/ip6.h>
#include <openthread/joiner.h>
#include <openthread/platform/radio.h>
#include <openthread/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api专员
 *
 * @brief 本模块包括线程专员角色的功能。
 *
 * @{
 *
 */

/**
 * 此枚举定义了专员州。
 *
 */
typedef enum otCommissionerState
{
    OT_COMMISSIONER_STATE_DISABLED = 0, ///<专员角色已禁用。
    OT_COMMISSIONER_STATE_PETITION = 1, ///<目前正在申请成为专员。
    OT_COMMISSIONER_STATE_ACTIVE   = 2, ///<专员角色活跃。
} otCommissionerState;

/**
 * 此枚举定义了专员的加入者事件。
 *
 */
typedef enum otCommissionerJoinerEvent
{
    OT_COMMISSIONER_JOINER_START     = 0,
    OT_COMMISSIONER_JOINER_CONNECTED = 1,
    OT_COMMISSIONER_JOINER_FINALIZE  = 2,
    OT_COMMISSIONER_JOINER_END       = 3,
    OT_COMMISSIONER_JOINER_REMOVED   = 4,
} otCommissionerJoinerEvent;

#define OT_COMMISSIONING_PASSPHRASE_MIN_SIZE 6   ///<调试密码的最小大小
#define OT_COMMISSIONING_PASSPHRASE_MAX_SIZE 255 ///<调试密码的最大大小

#define OT_PROVISIONING_URL_MAX_SIZE 64 ///<设置URL字符串中的最大大小（字符数）（不包括空字符）。

#define OT_STEERING_DATA_MAX_LENGTH 16 ///<最大转向数据长度（字节）

/**
 * 此结构表示转向数据。
 *
 */
typedef struct otSteeringData
{
    uint8_t mLength;                         ///<转向数据长度（字节）
    uint8_t m8[OT_STEERING_DATA_MAX_LENGTH]; ///<字节值
} otSteeringData;

/**
 * 此结构表示调试数据集。
 *
 */
typedef struct otCommissioningDataset
{
    uint16_t       mLocator;       ///<边界路由器RLOC16
    uint16_t       mSessionId;     ///<专员会话Id
    otSteeringData mSteeringData;  ///<转向数据
    uint16_t       mJoinerUdpPort; ///<Joiner UDP端口

    bool mIsLocatorSet : 1;       ///如果设置了边界路由器RLOC16，则<TRUE，否则为FALSE。
    bool mIsSessionIdSet : 1;     ///如果设置了专员会话Id，则<TRUE，否则为FALSE。
    bool mIsSteeringDataSet : 1;  ///如果设置了转向数据，则<TRUE，否则为FALSE。
    bool mIsJoinerUdpPortSet : 1; ///如果设置了Joiner UDP端口，则<TRUE，否则为FALSE。
} otCommissioningDataset;

#define OT_JOINER_MAX_PSKD_LENGTH 32 ///<Joiner PSKd的最大字符串长度（不包括空字符）。

/**
 * 此结构表示Joiner PSKd。
 *
 */
typedef struct otJoinerPskd
{
    char m8[OT_JOINER_MAX_PSKD_LENGTH + 1]; ///<字符字符串数组（必须以空结尾-+1表示空字符）。
} otJoinerPskd;

/**
 * 此枚举定义联接者信息类型。
 *
 */
typedef enum otJoinerInfoType
{
    OT_JOINER_INFO_TYPE_ANY       = 0, ///<接受任何Joiner（未指定EUI64或Discerner）。
    OT_JOINER_INFO_TYPE_EUI64     = 1, ///<Joiner EUI-64已指定（`otJoinerInfo`中的`mSharedId.mEui64`）。
    OT_JOINER_INFO_TYPE_DISCERNER = 2, ///<Joiner Discerner已指定（`otJoinerInfo`中的`mSharedId.mDiscerner`）。
} otJoinerInfoType;

/**
 * 此结构表示加入者信息。
 *
 */
typedef struct otJoinerInfo
{
    otJoinerInfoType mType; ///<联接类型。
    union
    {
        otExtAddress      mEui64;     ///<Joiner EUI64（当“mType”为“OT_Joiner_INFO_TYPE_EUI64”时）
        otJoinerDiscerner mDiscerner; ///<Joiner Discerner（当`mType`为`OT_Joiner_INFO_TYPE_Discerner`时）
    } mSharedId;                      ///<共享字段
    otJoinerPskd mPskd;               ///<加入者PSKd
    uint32_t     mExpirationTime;     ///<加入者过期时间（毫秒）
} otJoinerInfo;

/**
 * 每当专员状态更改时，都会调用此函数指针。
 *
 * @param[in]  aChannelMask       通道掩码值。
 * @param[in]  aEnergyList        指向能量测量列表的指针。
 * @param[in]  aEnergyListLength  @p aEnergyListLength中的条目数。
 * @param[in]  aContext           指向应用程序特定上下文的指针。
 *
 */
typedef void (*otCommissionerStateCallback)(otCommissionerState aState, void *aContext);

/**
 * 每当连接程序状态更改时，都会调用此函数指针。
 *
 * @param[in]  aEvent       加入者事件类型。
 * @param[in]  aJoinerInfo  指向加入者信息的指针。
 * @param[in]  aJoinerId    指向Joiner ID的指针（如果未知，则为NULL）。
 * @param[in]  aContext     指向应用程序特定上下文的指针。
 *
 */
typedef void (*otCommissionerJoinerCallback)(otCommissionerJoinerEvent aEvent,
                                             const otJoinerInfo *      aJoinerInfo,
                                             const otExtAddress *      aJoinerId,
                                             void *                    aContext);

/**
 * 此函数启用线程专员角色。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aStateCallback    当专员状态更改时调用的函数的指针。
 * @param[in]  aJoinerCallback   出现一个指针，指向用joiner事件调用的函数。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE成功启动专员服务。
 * @retval OT_ERROR_ALREADY专员已启动。
 * @retval OT_ERROR_INVALID_STATE设备当前未连接到网络。
 *
 */
otError otCommissionerStart(otInstance *                 aInstance,
                            otCommissionerStateCallback  aStateCallback,
                            otCommissionerJoinerCallback aJoinerCallback,
                            void *                       aCallbackContext);

/**
 * 此函数禁用线程专员角色。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功停止专员服务。
 * @retval OT_ERROR_ALREADY专员已停止。
 *
 */
otError otCommissionerStop(otInstance *aInstance);

/**
 * 此函数用于添加Joiner条目。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aEui64             指向Joiner的IEEE EUI-64的指针，对于任何Joiner为NULL。
 * @param[in]  aPskd              指向PSKd的指针。
 * @param[in]  aTimeout           自动删除Joiner的时间，以秒为单位。
 *
 * @retval OT_ERROR_NONE已成功添加加入者。
 * @retval OT_ERROR_NO_BUFS没有可用于添加Joiner的缓冲区。
 * @retval OT_ERROR_INVALID_ARGS@p aEui64或@p aPskd无效。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerAddJoiner(otInstance *        aInstance,
                                const otExtAddress *aEui64,
                                const char *        aPskd,
                                uint32_t            aTimeout);

/**
 * 此函数使用给定的Joiner Discerner值添加Joiner条目。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aDiscerner         指向Joiner Discerner的指针。
 * @param[in]  aPskd              指向PSKd的指针。
 * @param[in]  aTimeout           自动删除Joiner的时间，以秒为单位。
 *
 * @retval OT_ERROR_NONE已成功添加加入者。
 * @retval OT_ERROR_NO_BUFS没有可用于添加Joiner的缓冲区。
 * @retval OT_ERROR_INVALID_ARGS@p aDiscerner或@p aPskd无效。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerAddJoinerWithDiscerner(otInstance *             aInstance,
                                             const otJoinerDiscerner *aDiscerner,
                                             const char *             aPskd,
                                             uint32_t                 aTimeout);

/**
 * 这个方法在某个位置获取加入者信息。
 *
 * @param[in]      aInstance   指向实例的指针。
 * @param[inout]   aIterator   指向Joiner Info迭代器上下文的指针。
 * @param[out]     aJoiner     对Joiner信息的引用。
 *
 * @retval OT_ERROR_NONE成功获取加入者信息。
 * @retval OT_ERROR_NOT_FOUND未找到下一个加入者。
 *
 */
otError otCommissionerGetNextJoinerInfo(otInstance *aInstance, uint16_t *aIterator, otJoinerInfo *aJoiner);

/**
 * 此函数用于删除Joiner条目。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aEui64             指向Joiner的IEEE EUI-64的指针，对于任何Joiner为NULL。
 *
 * @retval OT_ERROR_NONE已成功删除Joiner。
 * @retval OT_ERROR_NOT_FOUND找不到@p aEui64指定的Joiner。
 * @retval OT_ERROR_INVALID_ARGS@p aEui64无效。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerRemoveJoiner(otInstance *aInstance, const otExtAddress *aEui64);

/**
 * 此函数用于删除Joiner条目。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aEui64             指向Joiner Discerner的指针。
 *
 * @retval OT_ERROR_NONE已成功删除Joiner。
 * @retval OT_ERROR_NOT_FOUND找不到@p aEui64指定的Joiner。
 * @retval OT_ERROR_INVALID_ARGS@p aDiscerner无效。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerRemoveJoinerWithDiscerner(otInstance *aInstance, const otJoinerDiscerner *aDiscerner);

/**
 * 此函数获取设置URL。
 *
 * @param[in]    aInstance       指向OpenThread实例的指针。
 *
 * @returns 指向URL字符串的指针。
 *
 */
const char *otCommissionerGetProvisioningUrl(otInstance *aInstance);

/**
 * 此函数用于设置设置URL。
 *
 * @param[in]  aInstance             指向OpenThread实例的指针。
 * @param[in]  aProvisioningUrl      指向配置URL的指针（可以为NULL以设置为空字符串）。
 *
 * @retval OT_ERROR_NONE已成功设置设置URL。
 * @retval OT_ERROR_INVALID_ARGS@p aProvisioningUrl无效（太长）。
 *
 */
otError otCommissionerSetProvisioningUrl(otInstance *aInstance, const char *aProvisioningUrl);

/**
 * 此函数发送一条AnnounceBegin消息。
 *
 * @param[in]  aInstance             指向OpenThread实例的指针。
 * @param[in]  aChannelMask          通道掩码值。
 * @param[in]  aCount                每个频道的公告消息数。
 * @param[in]  aPeriod               两次连续MLE通告传输之间的时间（以毫秒为单位）。
 * @param[in]  aAddress              指向IPv6目标的指针。
 *
 * @retval OT_ERROR_NONE已成功将公告开始消息排入队列。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成公告开始消息。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerAnnounceBegin(otInstance *        aInstance,
                                    uint32_t            aChannelMask,
                                    uint8_t             aCount,
                                    uint16_t            aPeriod,
                                    const otIp6Address *aAddress);

/**
 * 当专员收到能源报告时，调用此函数指针。
 *
 * @param[in]  aChannelMask       通道掩码值。
 * @param[in]  aEnergyList        指向能量测量列表的指针。
 * @param[in]  aEnergyListLength  @p aEnergyListLength中的条目数。
 * @param[in]  aContext           指向应用程序特定上下文的指针。
 *
 */
typedef void (*otCommissionerEnergyReportCallback)(uint32_t       aChannelMask,
                                                   const uint8_t *aEnergyList,
                                                   uint8_t        aEnergyListLength,
                                                   void *         aContext);

/**
 * 此函数发送能量扫描查询消息。
 *
 * @param[in]  aInstance             指向OpenThread实例的指针。
 * @param[in]  aChannelMask          通道掩码值。
 * @param[in]  aCount                每个通道的能量测量数。
 * @param[in]  aPeriod               能量测量之间的时间（毫秒）。
 * @param[in]  aScanDuration         每个能量测量的扫描持续时间（毫秒）。
 * @param[in]  aAddress              指向IPv6目标的指针。
 * @param[in]  aCallback             指向在接收能量报告消息时调用的函数的指针。
 * @param[in]  aContext              指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功将能量扫描查询消息排入队列。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成能量扫描查询消息。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerEnergyScan(otInstance *                       aInstance,
                                 uint32_t                           aChannelMask,
                                 uint8_t                            aCount,
                                 uint16_t                           aPeriod,
                                 uint16_t                           aScanDuration,
                                 const otIp6Address *               aAddress,
                                 otCommissionerEnergyReportCallback aCallback,
                                 void *                             aContext);

/**
 * 当专员收到PAN ID冲突消息时，调用此函数指针。
 *
 * @param[in]  aPanId             PAN ID值。
 * @param[in]  aChannelMask       通道掩码值。
 * @param[in]  aContext           指向应用程序特定上下文的指针。
 *
 */
typedef void (*otCommissionerPanIdConflictCallback)(uint16_t aPanId, uint32_t aChannelMask, void *aContext);

/**
 * 此函数发送PAN ID查询消息。
 *
 * @param[in]  aInstance             指向OpenThread实例的指针。
 * @param[in]  aPanId                要查询的PAN ID。
 * @param[in]  aChannelMask          通道掩码值。
 * @param[in]  aAddress              指向IPv6目标的指针。
 * @param[in]  aCallback             指向在接收PAN ID冲突消息时调用的函数的指针。
 * @param[in]  aContext              指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功将PAN ID查询消息排入队列。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成PAN ID查询消息。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 * @note 仅在使用otCommissionerStart（）成功启动专员角色后使用此选项。
 *
 */
otError otCommissionerPanIdQuery(otInstance *                        aInstance,
                                 uint16_t                            aPanId,
                                 uint32_t                            aChannelMask,
                                 const otIp6Address *                aAddress,
                                 otCommissionerPanIdConflictCallback aCallback,
                                 void *                              aContext);

/**
 * 此函数用于发送MGMT_CONDER_GET。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aTlvs      指向TLV的指针。
 * @param[in]  aLength    TLV的长度。
 *
 * @retval OT_ERROR_NONE成功发送meshcop数据集命令。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法发送。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 */
otError otCommissionerSendMgmtGet(otInstance *aInstance, const uint8_t *aTlvs, uint8_t aLength);

/**
 * 此函数用于发送MGMT_CONDER_SET。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aDataset   指向调试数据集的指针。
 * @param[in]  aTlvs      指向TLV的指针。
 * @param[in]  aLength    TLV的长度。
 *
 * @retval OT_ERROR_NONE成功发送meshcop数据集命令。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法发送。
 * @retval OT_ERROR_INVALID_STATE专员未激活。
 *
 */
otError otCommissionerSendMgmtSet(otInstance *                  aInstance,
                                  const otCommissioningDataset *aDataset,
                                  const uint8_t *               aTlvs,
                                  uint8_t                       aLength);

/**
 * 此函数返回专员会话ID。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns 当前专员会话id。
 *
 */
uint16_t otCommissionerGetSessionId(otInstance *aInstance);

/**
 * 此函数返回专员状态。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @retval OT_COMMISSIONER_STATE_DISABLED专员已禁用。
 * @retval OT_COMMISSIONER_STATE_PETITION成为专员。
 * @retval OT_COMMISSIONER_STATE_ACTIVE专员已启用。
 *
 */
otCommissionerState otCommissionerGetState(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_COMMISSIONER_H_

