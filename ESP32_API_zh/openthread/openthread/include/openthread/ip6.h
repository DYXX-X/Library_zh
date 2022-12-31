/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread IPv6 API。
 */

#ifndef OPENTHREAD_IP6_H_
#define OPENTHREAD_IP6_H_

#include <openthread/message.h>
#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 第6页
 *
 * @brief 该模块包括控制IPv6通信的功能。
 *
 * @{
 *
 */

#define OT_IP6_PREFIX_SIZE 8                           ///<IPv6前缀的大小（字节）
#define OT_IP6_PREFIX_BITSIZE (OT_IP6_PREFIX_SIZE * 8) ///<IPv6前缀的大小（位）
#define OT_IP6_IID_SIZE 8                              ///<IPv6接口标识符的大小（字节）
#define OT_IP6_ADDRESS_SIZE 16                         ///<IPv6地址的大小（字节）

/**
 * @struct otIp6接口标识符
 *
 * 此结构表示IPv6地址的接口标识符。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIp6InterfaceIdentifier
{
    union OT_TOOL_PACKED_FIELD
    {
        uint8_t  m8[OT_IP6_IID_SIZE];                     ///<8位字段
        uint16_t m16[OT_IP6_IID_SIZE / sizeof(uint16_t)]; ///<16位字段
        uint32_t m32[OT_IP6_IID_SIZE / sizeof(uint32_t)]; ///<32位字段
    } mFields;                                            ///<接口标识符访问器字段
} OT_TOOL_PACKED_END;

/**
 * 此结构表示IPv6地址的接口标识符。
 *
 */
typedef struct otIp6InterfaceIdentifier otIp6InterfaceIdentifier;

/**
 * @struct otIp6网络前缀
 *
 * 此结构表示IPv6地址的网络前缀（地址的最高有效64位）。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIp6NetworkPrefix
{
    uint8_t m8[OT_IP6_PREFIX_SIZE]; ///<网络前缀。
} OT_TOOL_PACKED_END;

/**
 * 此结构表示IPv6地址的网络前缀（地址的最高有效64位）。
 *
 */
typedef struct otIp6NetworkPrefix otIp6NetworkPrefix;

/**
 * @struct otIp6地址组件
 *
 * 此结构表示IPv6地址的组件。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIp6AddressComponents
{
    otIp6NetworkPrefix       mNetworkPrefix; ///<网络前缀（地址的最高有效64位）
    otIp6InterfaceIdentifier mIid;           ///<接口标识符（地址的最低有效64位）
} OT_TOOL_PACKED_END;

/**
 * 此结构表示IPv6地址的组件。
 *
 */
typedef struct otIp6AddressComponents otIp6AddressComponents;

/**
 * @struct otIp6地址
 *
 * 此结构表示IPv6地址。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIp6Address
{
    union OT_TOOL_PACKED_FIELD
    {
        uint8_t                m8[OT_IP6_ADDRESS_SIZE];                     ///<8位字段
        uint16_t               m16[OT_IP6_ADDRESS_SIZE / sizeof(uint16_t)]; ///<16位字段
        uint32_t               m32[OT_IP6_ADDRESS_SIZE / sizeof(uint32_t)]; ///<32位字段
        otIp6AddressComponents mComponents;                                 ///<IPv6地址组件
    } mFields;                                                              ///<IPv6访问器字段
} OT_TOOL_PACKED_END;

/**
 * 此结构表示IPv6地址。
 *
 */
typedef struct otIp6Address otIp6Address;

/**
 * 此结构表示IPv6前缀。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIp6Prefix
{
    otIp6Address mPrefix; ///<IPv6前缀。
    uint8_t      mLength; ///<IPv6前缀长度（以位为单位）。
} OT_TOOL_PACKED_END;

/**
 * 此结构表示IPv6前缀。
 *
 */
typedef struct otIp6Prefix otIp6Prefix;

/**
 * IPv6地址来源
 *
 */
enum
{
    OT_ADDRESS_ORIGIN_THREAD = 0, ///<线程分配地址（ALOC、RLOC、MLEID等）
    OT_ADDRESS_ORIGIN_SLAAC  = 1, ///<SLAAC分配地址
    OT_ADDRESS_ORIGIN_DHCPV6 = 2, ///<DHCPv6分配的地址
    OT_ADDRESS_ORIGIN_MANUAL = 3, ///<手动分配的地址
};

/**
 * 此结构表示IPv6网络接口单播地址。
 *
 */
typedef struct otNetifAddress
{
    otIp6Address           mAddress;                ///<IPv6单播地址。
    uint8_t                mPrefixLength;           ///<前缀长度（以位为单位）。
    uint8_t                mAddressOrigin;          ///<IPv6地址来源。
    bool                   mPreferred : 1;          ///如果首选地址，则<TRUE，否则为FALSE。
    bool                   mValid : 1;              ///如果地址有效，则<TRUE，否则为FALSE。
    bool                   mScopeOverrideValid : 1; ///如果mScopeOverride值有效，则<TRUE，否则为FALSE。
    unsigned int           mScopeOverride : 4;      ///<此地址的IPv6作用域。
    bool                   mRloc : 1;               ///如果地址是RLOC，则<TRUE，否则为FALSE。
    struct otNetifAddress *mNext;                   ///<指向下一个网络接口地址的指针。
} otNetifAddress;

/**
 * 此结构表示IPv6网络接口多播地址。
 *
 */
typedef struct otNetifMulticastAddress
{
    otIp6Address                          mAddress; ///<IPv6多播地址。
    const struct otNetifMulticastAddress *mNext;    ///<指向下一个网络接口多播地址的指针。
} otNetifMulticastAddress;

/**
 * 此结构表示IPv6套接字地址。
 *
 */
typedef struct otSockAddr
{
    otIp6Address mAddress; ///<IPv6地址。
    uint16_t     mPort;    ///<传输层端口。
} otSockAddr;

/**
 * ECN状态，如IP报头中所示。
 *
 */
enum
{
    OT_ECN_NOT_CAPABLE = 0x0, ///<非ECT
    OT_ECN_CAPABLE_0   = 0x2, ///< ECT(0)
    OT_ECN_CAPABLE_1   = 0x1, ///< ECT(1)
    OT_ECN_MARKED      = 0x3, ///<遇到拥堵（CE）
};

/**
 * 此结构表示本地和对等IPv6套接字地址。
 *
 */
typedef struct otMessageInfo
{
    otIp6Address mSockAddr; ///<本地IPv6地址。
    otIp6Address mPeerAddr; ///<对等IPv6地址。
    uint16_t     mSockPort; ///<本地传输层端口。
    uint16_t     mPeerPort; ///<对等传输层端口。
    const void * mLinkInfo; ///<指向链接特定信息的指针。
    uint8_t      mHopLimit; ///<IPv6跃点限制值。仅当“mAllowZeroHopLimit”为FALSE时适用。
                            ///<如果“0”，则IPv6跃点限制为默认值`OPENTHREAD_CONFIG_IP6_Hop_Limit_default`。
                            ///<否则，指定IPv6跃点限制。
    uint8_t mEcn : 2;       ///<数据包的ECN状态，如IPv6标头中所示。
    bool    mIsHostInterface : 1;   ///＜TRUE，如果通过主机接口发送/接收数据包，否则为FALSE。
    bool    mAllowZeroHopLimit : 1; ///<TRUE表示“mHopLimit”中允许IPv6跃点限制0，否则为FALSE。
    bool    mMulticastLoop : 1;     ///＜TRUE允许循环返回多播，否则为FALSE。
} otMessageInfo;

/**
 * 互联网协议编号。
 *
 */
enum
{
    OT_IP6_PROTO_HOP_OPTS = 0,  ///<IPv6逐跳选项
    OT_IP6_PROTO_TCP      = 6,  ///<传输控制协议
    OT_IP6_PROTO_UDP      = 17, ///<用户数据报
    OT_IP6_PROTO_IP6      = 41, ///<IPv6封装
    OT_IP6_PROTO_ROUTING  = 43, ///<IPv6的路由标头
    OT_IP6_PROTO_FRAGMENT = 44, ///<IPv6的片段标头
    OT_IP6_PROTO_ICMP6    = 58, ///<IPv6的ICMP
    OT_IP6_PROTO_NONE     = 59, ///<IPv6没有下一个标头
    OT_IP6_PROTO_DST_OPTS = 60, ///<IPv6的目标选项
};

/**
 * 此功能打开/关闭IPv6接口。
 *
 * 调用此函数以启用/禁用IPv6通信。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 * @param[in] aEnabled  TRUE表示启用IPv6，否则为FALSE。
 *
 * @retval OT_ERROR_NONE成功启动/关闭IPv6接口。
 * @retval OT_ERROR_INVALID_STATE IPv6接口不可用，因为设备在原始链路模式下运行（仅在启用“OPENTHREAD_CONFIG_link_raw_ENABLE”功能时适用）。
 *
 */
otError otIp6SetEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此函数指示IPv6接口是否启动。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @retval TRUE IPv6接口已启用。
 * @retval FALSE IPv6接口已禁用。
 *
 */
bool otIp6IsEnabled(otInstance *aInstance);

/**
 * 将网络接口地址添加到线程接口。
 *
 * The passed-in instance @p aAddress由Thread接口复制。线程接口仅支持固定数量的外部添加的单播地址。请参阅OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aAddress  指向网络接口地址的指针。
 *
 * @retval OT_ERROR_NONE已成功添加（或更新）网络接口地址。
 * @retval OT_ERROR_INVALID_ARGS@p aAddress指示的IP地址是内部地址。
 * @retval OT_ERROR_NO_BUFS网络接口已存储允许的最大外部地址。
 */
otError otIp6AddUnicastAddress(otInstance *aInstance, const otNetifAddress *aAddress);

/**
 * 从线程接口中删除网络接口地址。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aAddress  指向IP地址的指针。
 *
 * @retval OT_ERROR_NONE已成功删除网络接口地址。
 * @retval OT_ERROR_INVALID_ARGS@p aAddress指示的IP地址是内部地址。
 * @retval OT_ERROR_NOT_FOUND找不到@p aAddress指示的IP地址。
 */
otError otIp6RemoveUnicastAddress(otInstance *aInstance, const otIp6Address *aAddress);

/**
 * 获取分配给线程接口的IPv6地址列表。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向第一个网络接口地址的指针。
 */
const otNetifAddress *otIp6GetUnicastAddresses(otInstance *aInstance);

/**
 * 将线程接口订阅到网络接口多播地址。
 *
 * The passed in instance @p aAddress将由Thread接口复制。线程接口仅支持固定数量的外部添加的多播地址。请参阅OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aAddress  指向IP地址的指针。
 *
 * @retval OT_ERROR_NONE已成功订阅网络接口多播地址。
 * @retval OT_ERROR_ALREADY多播地址已订阅。
 * @retval OT_ERROR_INVALID_ARGS@p aAddress指示的IP地址是无效地址。
 * @retval OT_ERROR_INVALID_STATE网络接口未启动。
 * @retval OT_ERROR_NO_BUFS网络接口已存储允许的最大外部多播地址。
 *
 */
otError otIp6SubscribeMulticastAddress(otInstance *aInstance, const otIp6Address *aAddress);

/**
 * 将线程接口取消订阅到网络接口多播地址。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aAddress  指向IP地址的指针。
 *
 * @retval OT_ERROR_NONE已成功取消订阅网络接口多播地址。
 * @retval OT_ERROR_INVALID_ARGS@p aAddress指示的IP地址是内部地址。
 * @retval OT_ERROR_NOT_FOUND找不到@p aAddress指示的IP地址。
 */
otError otIp6UnsubscribeMulticastAddress(otInstance *aInstance, const otIp6Address *aAddress);

/**
 * 获取订阅线程接口的IPv6多播地址列表。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向第一个网络接口多播地址的指针。
 *
 */
const otNetifMulticastAddress *otIp6GetMulticastAddresses(otInstance *aInstance);

/**
 * 检查线程接口上是否启用了多播混杂模式。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @sa otIp6SetMulticastPromicuous已启用
 *
 */
bool otIp6IsMulticastPromiscuousEnabled(otInstance *aInstance);

/**
 * 在线程接口上启用多播混杂模式。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aEnabled   TRUE表示启用多播混杂模式，否则为FALSE。
 *
 * @sa otIp6IsMulticastPromicuous已启用
 *
 */
void otIp6SetMulticastPromiscuousEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 为发送IPv6消息分配新的消息缓冲区。
 *
 * @note 如果@p aSettings为“NULL”，则链接层安全性启用，消息优先级默认设置为OT_message_priority_NORMAL。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSettings  指向消息设置的指针，或NULL设置默认设置。
 *
 * @returns 指向消息缓冲区的指针，如果没有可用的消息缓冲区或参数无效，则返回NULL。
 *
 * @sa otMessage自由
 *
 */
otMessage *otIp6NewMessage(otInstance *aInstance, const otMessageSettings *aSettings);

/**
 * 分配新的消息缓冲区，并将IPv6数据报写入消息缓冲区以发送IPv6消息。
 *
 * @note 如果@p aSettings为NULL，则启用链接层安全性，并从IPv6消息本身获取消息优先级。
 *       If @p aSettings不为NULL，将忽略@p aSetting->mPriority，并从IPv6消息本身获取。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aData        指向IPv6数据报缓冲区的指针。
 * @param[in]  aDataLength  @p aData指向的IPv6数据报缓冲区的大小。
 * @param[in]  aSettings    指向消息设置的指针，或NULL设置默认设置。
 *
 * @returns 指向消息的指针，如果IPv6标头格式错误或消息缓冲区不足，则为NULL。
 *
 * @sa otMessage自由
 *
 */
otMessage *otIp6NewMessageFromBuffer(otInstance *             aInstance,
                                     const uint8_t *          aData,
                                     uint16_t                 aDataLength,
                                     const otMessageSettings *aSettings);

/**
 * 当接收到IPv6数据报时，调用此函数指针。
 *
 * @param[in]  aMessage  指向包含接收到的IPv6数据报的消息缓冲区的指针。此函数传递
 *                       the ownership of the @p a发送回叫接收者的消息。消息在处理后应该由回调的接收方释放（请参见otMessageFree（））。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otIp6ReceiveCallback)(otMessage *aMessage, void *aContext);

/**
 * 此函数注册回调以提供接收的IPv6数据报。
 *
 * 默认情况下，此回调不传递线程控制流量。请参见otIp6SetReceiveFilterEnabled（）以更改线程控制流量筛选器设置。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aCallback         当接收到IPv6数据报时调用的函数的指针，或NULL以禁用回调。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 * @sa otIp6IsReceiveFilter已启用
 * @sa otIp6SetReceiveFilter已启用
 *
 */
void otIp6SetReceiveCallback(otInstance *aInstance, otIp6ReceiveCallback aCallback, void *aCallbackContext);

/**
 * @struct otIp6地址信息
 *
 * 此结构表示IPv6地址信息。
 *
 */
typedef struct otIp6AddressInfo
{
    const otIp6Address *mAddress;       ///<指向IPv6地址的指针。
    uint8_t             mPrefixLength;  ///<如果是单播地址，则为mAddress的前缀长度。
    uint8_t             mScope : 4;     ///<此地址的范围。
    bool                mPreferred : 1; ///<这是否是首选地址。
} otIp6AddressInfo;

/**
 * 添加或删除内部IPv6地址时调用此函数指针。
 *
 * @param[in]   aAddressInfo        指向IPv6地址信息的指针。
 * @param[in]   aIsAdded            如果添加了@p aAddress，则返回TRUE；如果删除了@p a Address，则为FALSE。
 * @param[in]   aContext            指向应用程序特定上下文的指针。
 *
 */
typedef void (*otIp6AddressCallback)(const otIp6AddressInfo *aAddressInfo, bool aIsAdded, void *aContext);

/**
 * 此函数注册回调以通知内部IPv6地址更改。
 *
 * @param[in]   aInstance           指向OpenThread实例的指针。
 * @param[in]   aCallback           添加或删除内部IPv6地址时调用的函数的指针。NULL将禁用回调。
 * @param[in]   aCallbackContext    指向应用程序特定上下文的指针。
 *
 */
void otIp6SetAddressCallback(otInstance *aInstance, otIp6AddressCallback aCallback, void *aCallbackContext);

/**
 * 此函数指示当通过otIp6SetReceiveCallback（）中指定的回调传递IPv6数据报时，是否过滤掉线程控制流量。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns  如果线程控制流量被过滤掉，则为TRUE，否则为FALSE。
 *
 * @sa otIp6Set接收回调
 * @sa otIp6SetReceiveFilter已启用
 *
 */
bool otIp6IsReceiveFilterEnabled(otInstance *aInstance);

/**
 * 此函数设置当通过otIp6SetReceiveCallback（）中指定的回调传递IPv6数据报时，是否过滤掉线程控制流量。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aEnabled  如果线程控制流量被过滤掉，则为TRUE，否则为FALSE。
 *
 * @sa otIp6Set接收回调
 * @sa otIsReceiveIp6Filter已启用
 *
 */
void otIp6SetReceiveFilterEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此函数通过线程接口发送IPv6数据报。
 *
 * The caller transfers ownership of @p a打电话时的消息。当处理完成时，OpenThread将释放@p aMessage，包括返回“OT_ERROR_NONE”以外的值时。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aMessage  指向包含IPv6数据报的消息缓冲区的指针。
 *
 * @retval OT_ERROR_NONE已成功处理消息。
 * @retval OT_ERROR_DROP消息格式良好，但由于数据包处理规则，未完全处理。
 * @retval OT_ERROR_NO_BUFS在处理数据报时无法分配必要的消息缓冲区。
 * @retval OT_ERROR_NO_ROUTE没有到主机的路由。
 * @retval OT_ERROR_INVALID_SOURCE_ADDRESS源地址无效，例如任意播地址或多播地址。
 * @retval OT_ERROR_PARSE在处理消息时遇到格式错误的标头。
 *
 */
otError otIp6Send(otInstance *aInstance, otMessage *aMessage);

/**
 * 此函数将端口添加到允许的不安全端口列表中。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aPort     端口值。
 *
 * @retval OT_ERROR_NONE端口已成功添加到允许的不安全端口列表中。
 * @retval OT_ERROR_INVALID_ARGS端口无效（值0保留供内部使用）。
 * @retval OT_ERROR_NO_BUFS不安全端口列表已满。
 *
 */
otError otIp6AddUnsecurePort(otInstance *aInstance, uint16_t aPort);

/**
 * 此函数从允许的不安全端口列表中删除端口。
 *
 * @note 此函数通过用内部端口列表中@p aPort之后的元素覆盖@p aPort来删除@p aPort。在调用otIp6GetUnsecurePorts（）和otIp6RemoveUnsecurePort（）以删除不安全的端口时要小心。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aPort     端口值。
 *
 * @retval OT_ERROR_NONE已成功从允许的不安全端口列表中删除该端口。
 * @retval OT_ERROR_INVALID_ARGS端口无效（值0保留供内部使用）。
 * @retval OT_ERROR_NOT_FOUND在不安全端口列表中找不到端口。
 *
 */
otError otIp6RemoveUnsecurePort(otInstance *aInstance, uint16_t aPort);

/**
 * 此函数从允许的不安全端口列表中删除所有端口。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 */
void otIp6RemoveAllUnsecurePorts(otInstance *aInstance);

/**
 * 此函数返回指向不安全端口列表的指针。
 *
 * @note 端口值0用于指示无效条目。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aNumEntries  列表中的条目数。
 *
 * @returns 指向不安全端口列表的指针。
 *
 */
const uint16_t *otIp6GetUnsecurePorts(otInstance *aInstance, uint8_t *aNumEntries);

/**
 * 测试两个IPv6地址是否相同。
 *
 * @param[in]  aFirst   指向要比较的第一个IPv6地址的指针。
 * @param[in]  aSecond  指向要比较的第二个IPv6地址的指针。
 *
 * @retval TRUE两个IPv6地址相同。
 * @retval FALSE两个IPv6地址不相同。
 *
 */
bool otIp6IsAddressEqual(const otIp6Address *aFirst, const otIp6Address *aSecond);

/**
 * 测试两个IPv6前缀是否相同。
 *
 * @param[in]  aFirst   指向要比较的第一个IPv6前缀的指针。
 * @param[in]  aSecond  指向要比较的第二个IPv6前缀的指针。
 *
 * @retval TRUE两个IPv6前缀相同。
 * @retval FALSE两个IPv6前缀不相同。
 *
 */
bool otIp6ArePrefixesEqual(const otIp6Prefix *aFirst, const otIp6Prefix *aSecond);

/**
 * 此函数将人类可读的IPv6地址字符串转换为二进制表示。
 *
 * @param[in]   aString   指向以NULL结尾的字符串的指针。
 * @param[out]  aAddress  指向IPv6地址的指针。
 *
 * @retval OT_ERROR_NONE已成功分析字符串。
 * @retval OT_ERROR_INVALID_ARGS无法分析字符串。
 *
 */
otError otIp6AddressFromString(const char *aString, otIp6Address *aAddress);

#define OT_IP6_ADDRESS_STRING_SIZE 40 ///<IPv6地址字符串表示的推荐大小。

/**
 * 此函数将给定的IPv6地址转换为可读字符串。
 *
 * IPv6地址字符串的格式为16个十六进制值，以“：”分隔（即“%x:%x:%x:…：%x”）。
 *
 * If the resulting string does not fit in @p aBuffer（在其@p aSize字符内），字符串将被截断，但输出的字符串始终以空结尾。
 *
 * @param[in]  aAddress  指向IPv6地址的指针（不能为空）。
 * @param[out] aBuffer   指向字符数组以输出字符串的指针（不能为空）。
 * @param[in]  aSize     @p aBuffer的大小（以字节为单位）。建议使用`OT_IP6_ADDRESS_STRING_SIZE`。
 *
 */
void otIp6AddressToString(const otIp6Address *aAddress, char *aBuffer, uint16_t aSize);

#define OT_IP6_SOCK_ADDR_STRING_SIZE 48 ///<IPv6套接字地址字符串表示的推荐大小。

/**
 * 此函数将给定的IPv6套接字地址转换为可读字符串。
 *
 * IPv6套接字地址字符串的格式为“[<address>]:<port>”，其中`<address>显示为16个十六进制值，用'：'分隔，`<port>`是十进制格式的端口号（即，“[%x:%x:…：%x]：%u”）
 *
 * If the resulting string does not fit in @p aBuffer（在其@p aSize字符内），字符串将被截断，但输出的字符串始终以空结尾。
 *
 * @param[in]  aSockAddr 指向IPv6套接字地址的指针（不能为空）。
 * @param[out] aBuffer   指向字符数组以输出字符串的指针（不能为空）。
 * @param[in]  aSize     @p aBuffer的大小（以字节为单位）。建议使用`OT_IP6_SOCK_ADDR_STRING_SIZE`。
 *
 */
void otIp6SockAddrToString(const otSockAddr *aSockAddr, char *aBuffer, uint16_t aSize);

#define OT_IP6_PREFIX_STRING_SIZE 45 ///<IPv6前缀字符串表示的推荐大小。

/**
 * 此函数将给定的IPv6前缀转换为可读字符串。
 *
 * IPv6地址字符串的格式为“%x:%x:%x:…[：：]/plen”。
 *
 * If the resulting string does not fit in @p aBuffer（在其@p aSize字符内），字符串将被截断，但输出的字符串始终以空结尾。
 *
 * @param[in]  aPrefix   指向IPv6前缀的指针（不能为空）。
 * @param[out] aBuffer   指向字符数组以输出字符串的指针（不能为空）。
 * @param[in]  aSize     @p aBuffer的大小（以字节为单位）。建议使用`OT_IP6_PREFIX_STRING_SIZE`。
 *
 */
void otIp6PrefixToString(const otIp6Prefix *aPrefix, char *aBuffer, uint16_t aSize);

/**
 * 此函数返回两个IPv6地址的前缀匹配长度（位）。
 *
 * @param[in]  aFirst   指向第一个IPv6地址的指针。
 * @param[in]  aSecond  指向第二个IPv6地址的指针。
 *
 * @returns  前缀匹配长度（以位为单位）。
 *
 */
uint8_t otIp6PrefixMatch(const otIp6Address *aFirst, const otIp6Address *aSecond);

/**
 * 此函数指示给定的IPv6地址是否为未指定地址。
 *
 * @param[in]  aAddress   指向IPv6地址的指针。
 *
 * @retval TRUE如果IPv6地址是未指定的地址。
 * @retval 如果IPv6地址不是未指定的地址，则返回FALSE。
 *
 */
bool otIp6IsAddressUnspecified(const otIp6Address *aAddress);

/**
 * 此函数执行OpenThread源地址选择。
 *
 * @param[in]     aInstance     指向OpenThread实例的指针。
 * @param[inout]  aMessageInfo  指向消息信息的指针。
 *
 * @retval  OT_ERROR_NONE找到一个源地址，并填充到@p aMessageInfo的mSockAddr中。
 * @retval  OT_ERROR_NOT_FOUND未找到源地址，@p aMessageInfo未更改。
 *
 */
otError otIp6SelectSourceAddress(otInstance *aInstance, otMessageInfo *aMessageInfo);

/**
 * 此功能指示SLAAC模块是否已启用。
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE`。
 *
 * @retval TRUE SLAAC模块已启用。
 * @retval FALSE SLAAC模块已禁用。
 *
 */
bool otIp6IsSlaacEnabled(otInstance *aInstance);

/**
 * 此功能启用/禁用SLAAC模块。
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE`。
 *
 * 启用SLAAC模块后，SLAAC地址（基于网络数据中的网格前缀）将添加到接口。当SLAAC模块被禁用时，之前添加的任何SLAAC地址都将被删除。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 * @param[in] aEnabled  TRUE表示启用，FALSE表示禁用。
 *
 */
void otIp6SetSlaacEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此函数指针允许用户过滤前缀，而不允许添加基于前缀的SLAC地址。
 *
 * `otIp6SetSlaacPrefixFilter（）`可用于设置筛选器处理程序。当SLAAC模块将要基于前缀添加SLAAC地址时，将调用筛选器处理程序。它的布尔返回值决定是否过滤（不添加）地址。
 *
 * @param[in] aInstacne   指向OpenThread实例的指针。
 * @param[in] aPrefix     指向要为其添加SLAAC地址的前缀的指针。
 *
 * @retval TRUE表示应过滤而不添加基于前缀的SLAC地址。
 * @retval FALSE表示应添加基于前缀的SLAC地址。
 *
 */
typedef bool (*otIp6SlaacPrefixFilter)(otInstance *aInstance, const otIp6Prefix *aPrefix);

/**
 * 此函数设置SLAAC模块筛选器处理程序。
 *
 * 此函数要求启用构建时功能`OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE`。
 *
 * 当SLAAC模块将基于前缀添加SLAAC地址以决定是否应添加地址时，SLAAC将调用过滤器处理程序。
 *
 * NULL筛选器处理程序禁用筛选并允许添加所有SLAAC地址。
 *
 * 如果未调用此函数，SLAAC模块使用的默认过滤器将为NULL（过滤被禁用）。
 *
 * @param[in] aInstance    指向OpenThread实例的指针。
 * @param[in] aFilter      指向SLAC前缀筛选器处理程序的指针，或NULL以禁用筛选。
 *
 */
void otIp6SetSlaacPrefixFilter(otInstance *aInstance, otIp6SlaacPrefixFilter aFilter);

/**
 * 使用“otIp6RegisterMulticastListeners”的结果调用此函数指针。
 *
 * @param[in]  aContext  指向用户上下文的指针。
 * @param[in]  aError    当成功发送MLR时，OT_ERROR_NONE。req并接收MLR。rsp、OT_ERROR_RESPONSE_TIMEOUT（当接收MLR失败时）。rsp，OT_ERROR_PARSE，当无法解析MLR.rsp时。
 * @param[in]  aMlrStatus         当@p aError为OT_ERROR_NONE时，多播侦听器注册状态。
 * @param[in]  aFailedAddresses   当@p aError为OT_ERROR_NONE时，指向失败IPv6地址的指针。
 * @param[in]  aFailedAddressNum  当@p aError为OT_ERROR_NONE时，失败的IPv6地址数。
 *
 * @sa otIp6RegisterMulticastListeners
 *
 */
typedef void (*otIp6RegisterMulticastListenersCallback)(void *              aContext,
                                                        otError             aError,
                                                        uint8_t             aMlrStatus,
                                                        const otIp6Address *aFailedAddresses,
                                                        uint8_t             aFailedAddressNum);

/**
 * 此函数将多播侦听器注册到主骨干路由器。
 *
 * 注意：仅当同时启用`OPENTHREAD_COONFIG_TMF_PROXY_MLR_ENABLE`和`OPENTHRAD_CONFIG_COMMISSIONER_ENABLE'时可用）
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aAddresses   要注册的多播地址数组。
 * @param[in]  aAddressNum  要注册的多播地址数（如果@p aAddresses为NULL，则为0）。
 * @param[in]  aTimeout     指向MLR.req中包含的超时值（以秒为单位）的指针。超时值为0将删除相应的多播侦听器。如果为NULL，则为MLR。req默认没有超时Tlv。
 * @param[in]  aCallback    指向回调函数的指针。
 * @param[in]  aContext     指向用户上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功发送MLR.req。如果此方法返回OT_ERROR_NONE，将调用@p aCallback。
 * @retval OT_ERROR_BUSY如果以前的注册正在进行。
 * @retval OT_ERROR_INVALID_ARGS如果一个或多个参数无效。
 * @retval OT_ERROR_INVALID_STATE如果设备未处于发送MLR的有效状态。req（例如专员未启动，主骨干路由器未找到）。
 * @retval OT_ERROR_NO_BUFS如果可用的消息缓冲区不足。
 *
 * @sa otIp6RegisterMulticastListeners回调
 *
 */
otError otIp6RegisterMulticastListeners(otInstance *                            aInstance,
                                        const otIp6Address *                    aAddresses,
                                        uint8_t                                 aAddressNum,
                                        const uint32_t *                        aTimeout,
                                        otIp6RegisterMulticastListenersCallback aCallback,
                                        void *                                  aContext);

/**
 * 此函数设置网格本地IID（用于测试）。
 *
 * 仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 * @param[in]   aIid        指向要设置的网格本地IID的指针。
 *
 * @retval  OT_ERROR_NONE已成功设置网格本地IID。
 * @retval  OT_ERROR_INVALID_STATE线程协议已启用。
 *
 */
otError otIp6SetMeshLocalIid(otInstance *aInstance, const otIp6InterfaceIdentifier *aIid);

/**
 * 此函数将给定的IP协议号转换为可读字符串。
 *
 * @param[in] aIpProto   IP协议编号（`OT_IP6_PROTO_*`枚举）。
 *
 * @returns 表示@p aIpProto的字符串。
 *
 */
const char *otIp6ProtoToString(uint8_t aIpProto);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_IP6_H_

