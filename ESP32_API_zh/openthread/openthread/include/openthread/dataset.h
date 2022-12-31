/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread操作数据集API（用于FTD和MTD）。
 */

#ifndef OPENTHREAD_DATASET_H_
#define OPENTHREAD_DATASET_H_

#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/platform/crypto.h>
#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api操作数据集
 *
 * @{
 *
 */

#define OT_NETWORK_KEY_SIZE 16 ///<线程网络密钥的大小（字节）

/**
 * @struct otNetwork密钥
 *
 * 此结构表示线程网络密钥。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otNetworkKey
{
    uint8_t m8[OT_NETWORK_KEY_SIZE]; ///<字节值
} OT_TOOL_PACKED_END;

/**
 * 此结构表示线程网络密钥。
 *
 */
typedef struct otNetworkKey otNetworkKey;

/**
 * 此数据类型表示NetworkKey的KeyRef。
 *
 */
typedef otCryptoKeyRef otNetworkKeyRef; ///<参考密钥

#define OT_NETWORK_NAME_MAX_SIZE 16 ///<线程网络名称字段的最大大小（字节）

/**
 * 此结构表示网络名称。
 *
 * “otNetworkName”是以空结尾的C字符串（即，“m8”字符数组必须以空字符“\0”结尾）。
 *
 */
typedef struct otNetworkName
{
    char m8[OT_NETWORK_NAME_MAX_SIZE + 1]; ///<字节值。“+1”表示空字符。
} otNetworkName;

#define OT_EXT_PAN_ID_SIZE 8 ///<线程PAN ID的大小（字节）

/**
 * 此结构表示扩展PAN ID。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otExtendedPanId
{
    uint8_t m8[OT_EXT_PAN_ID_SIZE]; ///<字节值
} OT_TOOL_PACKED_END;

/**
 * 此结构表示扩展PAN ID。
 *
 */
typedef struct otExtendedPanId otExtendedPanId;

#define OT_MESH_LOCAL_PREFIX_SIZE OT_IP6_PREFIX_SIZE ///<网格本地前缀的大小（字节）

/**
 * 此结构表示网格本地前缀。
 *
 */
typedef otIp6NetworkPrefix otMeshLocalPrefix;

#define OT_PSKC_MAX_SIZE 16 ///<PSKc的最大大小（字节）

/**
 * 该结构表示PSKc。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otPskc
{
    uint8_t m8[OT_PSKC_MAX_SIZE]; ///<字节值
} OT_TOOL_PACKED_END;

/**
 * 该结构表示PSKc。
 *
 */
typedef struct otPskc otPskc;

/**
 * 此数据类型表示PSKc的KeyRef。
 *
 */
typedef otCryptoKeyRef otPskcRef; ///<参考密钥

/**
 * 此结构表示安全策略。
 *
 */
typedef struct otSecurityPolicy
{
    uint16_t mRotationTime; ///<thrKeyRotation的值（以小时为单位）。

    bool    mObtainNetworkKeyEnabled : 1;        ///<已启用获取带外调试的网络密钥
    bool    mNativeCommissioningEnabled : 1;     ///<允许使用PSKc进行本地调试
    bool    mRoutersEnabled : 1;                 ///<线程1.0/1.1.x路由器已启用
    bool    mExternalCommissioningEnabled : 1;   ///<允许外部专员认证
    bool    mBeaconsEnabled : 1;                 ///<线程1.0/1.1.x信标已启用
    bool    mCommercialCommissioningEnabled : 1; ///<商业调试已启用
    bool    mAutonomousEnrollmentEnabled : 1;    ///<自动注册已启用
    bool    mNetworkKeyProvisioningEnabled : 1;  ///<已启用网络密钥设置
    bool    mTobleLinkEnabled : 1;               ///<ToBLE链接已启用
    bool    mNonCcmRoutersEnabled : 1;           ///<非CCM路由器已启用
    uint8_t mVersionThresholdForRouting : 3;     ///<路由的版本阈值
} otSecurityPolicy;

/**
 * 此类型表示通道遮罩。
 *
 */
typedef uint32_t otChannelMask;

#define OT_CHANNEL_1_MASK (1 << 1)   ///<通道1
#define OT_CHANNEL_2_MASK (1 << 2)   ///<通道2
#define OT_CHANNEL_3_MASK (1 << 3)   ///<通道3
#define OT_CHANNEL_4_MASK (1 << 4)   ///<通道4
#define OT_CHANNEL_5_MASK (1 << 5)   ///<通道5
#define OT_CHANNEL_6_MASK (1 << 6)   ///<通道6
#define OT_CHANNEL_7_MASK (1 << 7)   ///<通道7
#define OT_CHANNEL_8_MASK (1 << 8)   ///<通道8
#define OT_CHANNEL_9_MASK (1 << 9)   ///<通道9
#define OT_CHANNEL_10_MASK (1 << 10) ///<通道10
#define OT_CHANNEL_11_MASK (1 << 11) ///<通道11
#define OT_CHANNEL_12_MASK (1 << 12) ///<通道12
#define OT_CHANNEL_13_MASK (1 << 13) ///<通道13
#define OT_CHANNEL_14_MASK (1 << 14) ///<通道14
#define OT_CHANNEL_15_MASK (1 << 15) ///<信道15
#define OT_CHANNEL_16_MASK (1 << 16) ///<通道16
#define OT_CHANNEL_17_MASK (1 << 17) ///<通道17
#define OT_CHANNEL_18_MASK (1 << 18) ///<通道18
#define OT_CHANNEL_19_MASK (1 << 19) ///<通道19
#define OT_CHANNEL_20_MASK (1 << 20) ///<信道20
#define OT_CHANNEL_21_MASK (1 << 21) ///<信道21
#define OT_CHANNEL_22_MASK (1 << 22) ///<信道22
#define OT_CHANNEL_23_MASK (1 << 23) ///<通道23
#define OT_CHANNEL_24_MASK (1 << 24) ///<信道24
#define OT_CHANNEL_25_MASK (1 << 25) ///<通道25
#define OT_CHANNEL_26_MASK (1 << 26) ///<信道26

/**
 * 此结构表示活动或待定操作数据集中存在不同的组件。
 *
 */
typedef struct otOperationalDatasetComponents
{
    bool mIsActiveTimestampPresent : 1;  ///如果存在活动时间戳，则<TRUE，否则为FALSE。
    bool mIsPendingTimestampPresent : 1; ///＜TRUE，如果存在待定时间戳，否则为FALSE。
    bool mIsNetworkKeyPresent : 1;       ///如果存在网络密钥，则<TRUE，否则为FALSE。
    bool mIsNetworkNamePresent : 1;      ///如果存在网络名称，则<TRUE，否则为FALSE。
    bool mIsExtendedPanIdPresent : 1;    ///如果存在扩展PAN ID，则<TRUE，否则为FALSE。
    bool mIsMeshLocalPrefixPresent : 1;  ///如果存在网格本地前缀，则<TRUE，否则为FALSE。
    bool mIsDelayPresent : 1;            ///如果存在延迟计时器，则<TRUE，否则为FALSE。
    bool mIsPanIdPresent : 1;            ///如果存在PAN ID，则<TRUE，否则为FALSE。
    bool mIsChannelPresent : 1;          ///如果存在信道，则<TRUE，否则为FALSE。
    bool mIsPskcPresent : 1;             ///如果存在PSKc，则<TRUE，否则为FALSE。
    bool mIsSecurityPolicyPresent : 1;   ///如果存在安全策略，则<TRUE，否则为FALSE。
    bool mIsChannelMaskPresent : 1;      ///如果存在通道掩码，则<TRUE，否则为FALSE。
} otOperationalDatasetComponents;

/**
 * 此结构表示活动或挂起的操作数据集。
 *
 * 数据集中的组件是可选的`mComponets的结构指定数据集中存在哪些组件。
 *
 */
typedef struct otOperationalDataset
{
    uint64_t                       mActiveTimestamp;  ///<活动时间戳
    uint64_t                       mPendingTimestamp; ///<待定时间戳
    otNetworkKey                   mNetworkKey;       ///<网络密钥
    otNetworkName                  mNetworkName;      ///<网络名称
    otExtendedPanId                mExtendedPanId;    ///<扩展PAN ID
    otMeshLocalPrefix              mMeshLocalPrefix;  ///<网格本地前缀
    uint32_t                       mDelay;            ///<延迟计时器
    otPanId                        mPanId;            ///< PAN ID
    uint16_t                       mChannel;          ///<通道
    otPskc                         mPskc;             ///<PSKc
    otSecurityPolicy               mSecurityPolicy;   ///<安全策略
    otChannelMask                  mChannelMask;      ///<通道掩码
    otOperationalDatasetComponents mComponents;       ///<指定在数据集中设置哪些组件。
} otOperationalDataset;

/**
 * 操作数据集的最大长度（字节）。
 *
 */
#define OT_OPERATIONAL_DATASET_MAX_LENGTH 254

/**
 * 此结构表示活动或挂起的操作数据集。
 *
 * 操作数据集按照线程的指定进行TLV编码。
 *
 */
typedef struct otOperationalDatasetTlvs
{
    uint8_t mTlvs[OT_OPERATIONAL_DATASET_MAX_LENGTH]; ///<操作数据集TLVs。
    uint8_t mLength;                                  ///<操作数据集的大小（字节）。
} otOperationalDatasetTlvs;

/**
 * 此枚举表示meshcop TLV类型。
 *
 */
typedef enum otMeshcopTlvType
{
    OT_MESHCOP_TLV_CHANNEL                  = 0,   ///<meshcop通道TLV
    OT_MESHCOP_TLV_PANID                    = 1,   ///<meshcop Pan-Id TLV
    OT_MESHCOP_TLV_EXTPANID                 = 2,   ///<meshcop扩展平移Id TLV
    OT_MESHCOP_TLV_NETWORKNAME              = 3,   ///<meshcop网络名称TLV
    OT_MESHCOP_TLV_PSKC                     = 4,   ///<meshcop PSKc TLV
    OT_MESHCOP_TLV_NETWORKKEY               = 5,   ///<meshcop网络密钥TLV
    OT_MESHCOP_TLV_NETWORK_KEY_SEQUENCE     = 6,   ///<meshcop网络密钥序列TLV
    OT_MESHCOP_TLV_MESHLOCALPREFIX          = 7,   ///<meshcop网格本地前缀TLV
    OT_MESHCOP_TLV_STEERING_DATA            = 8,   ///<meshcop转向数据TLV
    OT_MESHCOP_TLV_BORDER_AGENT_RLOC        = 9,   ///<meshcop边境特工定位器TLV
    OT_MESHCOP_TLV_COMMISSIONER_ID          = 10,  ///<meshcop专员ID TLV
    OT_MESHCOP_TLV_COMM_SESSION_ID          = 11,  ///<meshcop专员会话ID TLV
    OT_MESHCOP_TLV_SECURITYPOLICY           = 12,  ///<meshcop安全策略TLV
    OT_MESHCOP_TLV_GET                      = 13,  ///<meshcop获取TLV
    OT_MESHCOP_TLV_ACTIVETIMESTAMP          = 14,  ///<meshcop活动时间戳TLV
    OT_MESHCOP_TLV_COMMISSIONER_UDP_PORT    = 15,  ///<meshcop专员UDP端口TLV
    OT_MESHCOP_TLV_STATE                    = 16,  ///<meshcop状态TLV
    OT_MESHCOP_TLV_JOINER_DTLS              = 17,  ///<meshcop Joiner DTLS封装TLV
    OT_MESHCOP_TLV_JOINER_UDP_PORT          = 18,  ///<meshcop Joiner UDP端口TLV
    OT_MESHCOP_TLV_JOINER_IID               = 19,  ///<meshcop Joiner IID TLV
    OT_MESHCOP_TLV_JOINER_RLOC              = 20,  ///<meshcop Joiner路由器定位器TLV
    OT_MESHCOP_TLV_JOINER_ROUTER_KEK        = 21,  ///<meshcop Joiner路由器KEK TLV
    OT_MESHCOP_TLV_PROVISIONING_URL         = 32,  ///<meshcop设置URL TLV
    OT_MESHCOP_TLV_VENDOR_NAME_TLV          = 33,  ///<meshcop供应商名称TLV
    OT_MESHCOP_TLV_VENDOR_MODEL_TLV         = 34,  ///<meshcop供应商型号TLV
    OT_MESHCOP_TLV_VENDOR_SW_VERSION_TLV    = 35,  ///<meshcop供应商软件版本TLV
    OT_MESHCOP_TLV_VENDOR_DATA_TLV          = 36,  ///<meshcop供应商数据TLV
    OT_MESHCOP_TLV_VENDOR_STACK_VERSION_TLV = 37,  ///<meshcop供应商堆栈版本TLV
    OT_MESHCOP_TLV_UDP_ENCAPSULATION_TLV    = 48,  ///<meshcop UDP封装TLV
    OT_MESHCOP_TLV_IPV6_ADDRESS_TLV         = 49,  ///<meshcop IPv6地址TLV
    OT_MESHCOP_TLV_PENDINGTIMESTAMP         = 51,  ///<meshcop待定时间戳TLV
    OT_MESHCOP_TLV_DELAYTIMER               = 52,  ///<meshcop延迟计时器TLV
    OT_MESHCOP_TLV_CHANNELMASK              = 53,  ///<meshcop通道掩码TLV
    OT_MESHCOP_TLV_COUNT                    = 54,  ///<meshcop计数TLV
    OT_MESHCOP_TLV_PERIOD                   = 55,  ///<meshcop周期TLV
    OT_MESHCOP_TLV_SCAN_DURATION            = 56,  ///<meshcop扫描持续时间TLV
    OT_MESHCOP_TLV_ENERGY_LIST              = 57,  ///<meshcop能源清单TLV
    OT_MESHCOP_TLV_DISCOVERYREQUEST         = 128, ///<meshcop发现请求TLV
    OT_MESHCOP_TLV_DISCOVERYRESPONSE        = 129, ///<meshcop发现响应TLV
    OT_MESHCOP_TLV_JOINERADVERTISEMENT      = 241, ///<meshcop Joiner广告TLV
} otMeshcopTlvType;

/**
 * 当收到对MGMT_SET请求的响应或超时时，调用此函数指针。
 *
 * @param[in]  aResult   操作的结果。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 * @retval  OT_ERROR_NONE领导接受了该请求。
 * @retval  OT_ERROR_REJECTED领导拒绝了请求。
 * @retval  OT_ERROR_PARSE分析响应时出错。
 * @retval  OT_ERROR_ABORT对等方已重置请求。
 * @retval  OT_ERROR_RESPONSE_TIMEOUT超时期间未收到响应或确认。
 *
 */
typedef void (*otDatasetMgmtSetCallback)(otError aResult, void *aContext);

/**
 * 此函数指示活动操作数据集中是否存在有效网络。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 如果活动操作数据集中存在有效网络，则为TRUE，否则为FALSE。
 *
 */
bool otDatasetIsCommissioned(otInstance *aInstance);

/**
 * 此函数获取活动操作数据集。
 *
 * @param[in]   aInstance 指向OpenThread实例的指针。
 * @param[out]  aDataset  指向活动操作数据集放置位置的指针。
 *
 * @retval OT_ERROR_NONE已成功检索活动操作数据集。
 * @retval OT_ERROR_NOT_FOUND设置存储中没有相应的值。
 *
 */
otError otDatasetGetActive(otInstance *aInstance, otOperationalDataset *aDataset);

/**
 * 此函数获取活动操作数据集。
 *
 * @param[in]   aInstance 指向OpenThread实例的指针。
 * @param[out]  aDataset  指向活动操作数据集放置位置的指针。
 *
 * @retval OT_ERROR_NONE已成功检索活动操作数据集。
 * @retval OT_ERROR_NOT_FOUND设置存储中没有相应的值。
 *
 */
otError otDatasetGetActiveTlvs(otInstance *aInstance, otOperationalDatasetTlvs *aDataset);

/**
 * 此函数设置活动操作数据集。
 *
 * 如果数据集不包含活动时间戳，则数据集仅部分完成。
 *
 * 如果在具有部分完整活动数据集的设备上启用了线程，则该设备将尝试使用数据集中的任何现有信息连接到现有线程网络。连接到网络只需要线程网络密钥。
 *
 * 如果数据集中不包括频道，设备将通过不同频道发送MLE公告消息，以查找其他频道上的邻居。
 *
 * 如果设备成功连接到线程网络，则设备将从其父级检索完整的活动数据集。请注意，支持路由器的设备在拥有完整的活动数据集之前，不会转换为路由器或领导者角色。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aDataset  指向活动操作数据集的指针。
 *
 * @retval OT_ERROR_NONE成功设置活动操作数据集。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法设置活动操作数据集。
 * @retval OT_ERROR_NOT_IMPLEMENTED平台未实现设置功能。
 *
 */
otError otDatasetSetActive(otInstance *aInstance, const otOperationalDataset *aDataset);

/**
 * 此函数设置活动操作数据集。
 *
 * 如果数据集不包含活动时间戳，则数据集仅部分完成。
 *
 * 如果在具有部分完整活动数据集的设备上启用了线程，则该设备将尝试使用数据集中的任何现有信息连接到现有线程网络。连接到网络只需要线程网络密钥。
 *
 * 如果数据集中不包括频道，设备将通过不同频道发送MLE公告消息，以查找其他频道上的邻居。
 *
 * 如果设备成功连接到线程网络，则设备将从其父级检索完整的活动数据集。请注意，支持路由器的设备在拥有完整的活动数据集之前，不会转换为路由器或领导者角色。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aDataset  指向活动操作数据集的指针。
 *
 * @retval OT_ERROR_NONE成功设置活动操作数据集。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法设置活动操作数据集。
 * @retval OT_ERROR_NOT_IMPLEMENTED平台未实现设置功能。
 *
 */
otError otDatasetSetActiveTlvs(otInstance *aInstance, const otOperationalDatasetTlvs *aDataset);

/**
 * 此函数获取待定操作数据集。
 *
 * @param[in]   aInstance 指向OpenThread实例的指针。
 * @param[out]  aDataset  指向将放置挂起操作数据集的位置的指针。
 *
 * @retval OT_ERROR_NONE成功检索到挂起的操作数据集。
 * @retval OT_ERROR_NOT_FOUND设置存储中没有相应的值。
 *
 */
otError otDatasetGetPending(otInstance *aInstance, otOperationalDataset *aDataset);

/**
 * 此函数获取待定操作数据集。
 *
 * @param[in]   aInstance 指向OpenThread实例的指针。
 * @param[out]  aDataset  指向将放置挂起操作数据集的位置的指针。
 *
 * @retval OT_ERROR_NONE成功检索到挂起的操作数据集。
 * @retval OT_ERROR_NOT_FOUND设置存储中没有相应的值。
 *
 */
otError otDatasetGetPendingTlvs(otInstance *aInstance, otOperationalDatasetTlvs *aDataset);

/**
 * 此函数设置挂起操作数据集。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aDataset  指向挂起操作数据集的指针。
 *
 * @retval OT_ERROR_NONE成功设置挂起操作数据集。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法设置挂起操作数据集。
 * @retval OT_ERROR_NOT_IMPLEMENTED平台未实现设置功能。
 *
 */
otError otDatasetSetPending(otInstance *aInstance, const otOperationalDataset *aDataset);

/**
 * 此函数设置挂起操作数据集。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aDataset  指向挂起操作数据集的指针。
 *
 * @retval OT_ERROR_NONE成功设置挂起操作数据集。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法设置挂起操作数据集。
 * @retval OT_ERROR_NOT_IMPLEMENTED平台未实现设置功能。
 *
 */
otError otDatasetSetPendingTlvs(otInstance *aInstance, const otOperationalDatasetTlvs *aDataset);

/**
 * 此函数发送MGMT_ACTIVE_GET。
 *
 * @param[in]  aInstance           指向OpenThread实例的指针。
 * @param[in]  aDatasetComponents  指向数据集组件结构的指针，指定要请求的组件。
 * @param[in]  aTlvTypes           指向包含要请求的其他原始TLV类型的数组的指针。
 * @param[in]  aLength             @p aTlvTypes的长度。
 * @param[in]  aAddress            指向IPv6目标的指针（如果为NULL）将使用Leader ALOC作为默认值。
 *
 * @retval OT_ERROR_NONE成功发送meshcop数据集命令。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法发送。
 *
 */
otError otDatasetSendMgmtActiveGet(otInstance *                          aInstance,
                                   const otOperationalDatasetComponents *aDatasetComponents,
                                   const uint8_t *                       aTlvTypes,
                                   uint8_t                               aLength,
                                   const otIp6Address *                  aAddress);

/**
 * 此函数发送MGMT_ACTIVE_SET。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aDataset   指向操作数据集的指针。
 * @param[in]  aTlvs      指向TLV的指针。
 * @param[in]  aLength    TLV的长度。
 * @param[in]  aCallback  指向响应接收或超时时调用的函数的指针。
 * @param[in]  aContext   指向@p aCallback的应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE成功发送meshcop数据集命令。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法发送。
 * @retval OT_ERROR_BUSY上一个请求正在进行。
 *
 */
otError otDatasetSendMgmtActiveSet(otInstance *                aInstance,
                                   const otOperationalDataset *aDataset,
                                   const uint8_t *             aTlvs,
                                   uint8_t                     aLength,
                                   otDatasetMgmtSetCallback    aCallback,
                                   void *                      aContext);

/**
 * 此函数发送MGMT_PENDING_GET。
 *
 * @param[in]  aInstance           指向OpenThread实例的指针。
 * @param[in]  aDatasetComponents  指向数据集组件结构的指针，指定要请求的组件。
 * @param[in]  aTlvTypes           指向包含要请求的其他原始TLV类型的数组的指针。
 * @param[in]  aLength             @p aTlvTypes的长度。
 * @param[in]  aAddress            指向IPv6目标的指针（如果为NULL）将使用Leader ALOC作为默认值。
 *
 * @retval OT_ERROR_NONE成功发送meshcop数据集命令。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法发送。
 *
 */
otError otDatasetSendMgmtPendingGet(otInstance *                          aInstance,
                                    const otOperationalDatasetComponents *aDatasetComponents,
                                    const uint8_t *                       aTlvTypes,
                                    uint8_t                               aLength,
                                    const otIp6Address *                  aAddress);

/**
 * 此函数发送MGMT_PENDING_SET。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aDataset   指向操作数据集的指针。
 * @param[in]  aTlvs      指向TLV的指针。
 * @param[in]  aLength    TLV的长度。
 * @param[in]  aCallback  指向响应接收或超时时调用的函数的指针。
 * @param[in]  aContext   指向@p aCallback的应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE成功发送meshcop数据集命令。
 * @retval OT_ERROR_NO_BUFS缓冲区空间不足，无法发送。
 * @retval OT_ERROR_BUSY上一个请求正在进行。
 *
 */
otError otDatasetSendMgmtPendingSet(otInstance *                aInstance,
                                    const otOperationalDataset *aDataset,
                                    const uint8_t *             aTlvs,
                                    uint8_t                     aLength,
                                    otDatasetMgmtSetCallback    aCallback,
                                    void *                      aContext);

/**
 * 此函数根据给定的密码短语、网络名称和扩展PAN ID生成PSKc。
 *
 * PSKc用于建立专员会议。
 *
 * @param[in]  aPassPhrase   调试密码短语。
 * @param[in]  aNetworkName  PSKc计算的网络名称。
 * @param[in]  aExtPanId     用于PSKc计算的扩展PAN ID。
 * @param[out] aPskc         用于输出生成的PSKc的变量指针。
 *
 * @retval OT_ERROR_NONE成功生成PSKc。
 * @retval OT_ERROR_INVALID_ARGS如果任何输入参数无效。
 *
 */
otError otDatasetGeneratePskc(const char *           aPassPhrase,
                              const otNetworkName *  aNetworkName,
                              const otExtendedPanId *aExtPanId,
                              otPskc *               aPskc);

/**
 * 此函数从给定的以空结尾的C字符串设置“otNetworkName”实例。
 *
 * This function also validates that the given @p aNameString遵循UTF-8编码，其长度不超过`OT_NETWORK_NAME_MAX_SIZE`。
 *
 * @param[out] aNetworkName        指向要设置的“otNetworkName”的指针。
 * @param[in]  aNameString         名称C字符串。
 *
 * @retval OT_ERROR_NONE已从@p aNameString成功设置@p aNetworkName。
 * @retval OT_ERROR_INVALID_ARGS@p aNameStrng无效（太长或不遵循UTF-8编码）。
 *
 */
otError otNetworkNameFromString(otNetworkName *aNetworkName, const char *aNameString);

/**
 * 此函数从“otOperationalDatasetTlvs”解析操作数据集。
 *
 * @param[in]  aDatasetTlvs  指向数据集TLV的指针。
 * @param[out] aDataset      指向数据集放置位置的指针。
 *
 * @retval OT_ERROR_NONE已从@p aDatasetTlvs成功设置@p aData集。
 * @retval OT_ERROR_INVALID_ARGS@p aDatasetTlvs无效。
 *
 */
otError otDatasetParseTlvs(const otOperationalDatasetTlvs *aDatasetTlvs, otOperationalDataset *aDataset);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_DATASET_H_

