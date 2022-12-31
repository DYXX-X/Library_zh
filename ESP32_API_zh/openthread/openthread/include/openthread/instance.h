/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread实例API。
 */

#ifndef OPENTHREAD_INSTANCE_H_
#define OPENTHREAD_INSTANCE_H_

#include <stdlib.h>

#include <openthread/error.h>
#include <openthread/platform/logging.h>
#include <openthread/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * OpenThread API单调版本号。
 *
 * 每次公共OpenThread API包含头的内容更改时，此数字必须增加一。
 *
 * @note 这个数字同时支持OpenThread平台和用户API。
 *
 */
#define OPENTHREAD_API_VERSION (171)

/**
 * @addtogroup api实例
 *
 * @brief 此模块包括控制OpenThread实例的函数。
 *
 * @{
 *
 */

/**
 * 此结构表示OpenThread实例结构。
 */
typedef struct otInstance otInstance;

/**
 * 此函数初始化OpenThread库。
 *
 * 此函数初始化OpenThread，并为后续的OpenThreadAPI调用做好准备。在调用OpenThread之前，必须先调用此函数。
 *
 * 此函数可用，仅当启用对多个OpenThread实例的支持时才能使用。
 *
 * @param[in]    aInstanceBuffer      OpenThread用于分配otInstance结构的缓冲区。
 * @param[inout] aInstanceBufferSize  输入时，aInstanceBuffer的大小。在输出时，如果没有足够的空间用于otInstance，则为otInstance所需的字节数。
 *
 * @returns  指向新OpenThread实例的指针。
 *
 * @sa otInstanceFinalize
 *
 */
otInstance *otInstanceInit(void *aInstanceBuffer, size_t *aInstanceBufferSize);

/**
 * 此函数初始化OpenThread库的静态单个实例。
 *
 * 此函数初始化OpenThread，并为后续的OpenThreadAPI调用做好准备。在调用OpenThread之前，必须先调用此函数。
 *
 * 此函数可用，仅当禁用对多个OpenThread实例的支持时才能使用。
 *
 * @returns 指向单个OpenThread实例的指针。
 *
 */
otInstance *otInstanceInitSingle(void);

/**
 * 此函数指示实例是否有效/已初始化。
 *
 * 如果使用“otInstanceInitSingle（）”（在单个实例的情况下）或“otInstanceInit（）””（在多实例的情况中）获取和初始化实例，则该实例视为有效。随后对“otInstanceFinalize（）”的调用会导致该实例被视为未初始化。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 如果给定实例有效/已初始化，则为TRUE，否则为FALSE。
 *
 */
bool otInstanceIsInitialized(otInstance *aInstance);

/**
 * 此函数禁用OpenThread库。
 *
 * 当OpenThread不再使用时调用此函数。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 */
void otInstanceFinalize(otInstance *aInstance);

/**
 * 此函数返回当前实例的正常运行时间（以毫秒为单位）。
 *
 * 此函数需要启用`OPENTHREAD_CONFIG_UPTIME_ENABLE`。
 *
 * 自OpenThread实例初始化以来，正常运行时间以毫秒为单位。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @returns 正常运行时间（毫秒数）。
 *
 */
uint64_t otInstanceGetUptime(otInstance *aInstance);

#define OT_UPTIME_STRING_SIZE 24 ///<正常运行时间字符串表示的推荐大小。

/**
 * 此函数将当前实例的正常运行时间作为可读字符串返回。
 *
 * 此函数需要启用`OPENTHREAD_CONFIG_UPTIME_ENABLE`。
 *
 * 该字符串的格式为“<hh>：<mm>：<ss>.<mmmm>”，表示小时、分钟、秒和毫秒（如果正常运行时间短于一天）或“<dd>d.<hh>：<mm>：<ss>.<mmmm>”（如果超过一天）。
 *
 * If the resulting string does not fit in @p aBuffer（在其@p aSize字符内），字符串将被截断，但输出的字符串始终以空结尾。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[out] aBuffer   指向用于输出字符串的字符数组的指针。
 * @param[in]  aSize     @p aBuffer的大小（以字节为单位）。建议使用`OT_UPTIME_STRING_SIZE`。
 *
 */
void otInstanceGetUptimeAsString(otInstance *aInstance, char *aBuffer, uint16_t aSize);

/**
 * 此枚举定义作为“otStateChangedCallback”的一部分传递的标志。
 *
 */
enum
{
    OT_CHANGED_IP6_ADDRESS_ADDED            = 1 << 0,  ///<已添加IPv6地址
    OT_CHANGED_IP6_ADDRESS_REMOVED          = 1 << 1,  ///<IPv6地址已删除
    OT_CHANGED_THREAD_ROLE                  = 1 << 2,  ///<角色（已禁用、已分离、子级、路由器、领导者）已更改
    OT_CHANGED_THREAD_LL_ADDR               = 1 << 3,  ///<链接本地地址已更改
    OT_CHANGED_THREAD_ML_ADDR               = 1 << 4,  ///<网格本地地址已更改
    OT_CHANGED_THREAD_RLOC_ADDED            = 1 << 5,  ///<已添加RLOC
    OT_CHANGED_THREAD_RLOC_REMOVED          = 1 << 6,  ///<RLOC已删除
    OT_CHANGED_THREAD_PARTITION_ID          = 1 << 7,  ///<分区ID已更改
    OT_CHANGED_THREAD_KEY_SEQUENCE_COUNTER  = 1 << 8,  ///<线程密钥序列已更改
    OT_CHANGED_THREAD_NETDATA               = 1 << 9,  ///<线程网络数据已更改
    OT_CHANGED_THREAD_CHILD_ADDED           = 1 << 10, ///<已添加子项
    OT_CHANGED_THREAD_CHILD_REMOVED         = 1 << 11, ///<子项已删除
    OT_CHANGED_IP6_MULTICAST_SUBSCRIBED     = 1 << 12, ///<已订阅IPv6多播地址
    OT_CHANGED_IP6_MULTICAST_UNSUBSCRIBED   = 1 << 13, ///<从IPv6多播地址取消订阅
    OT_CHANGED_THREAD_CHANNEL               = 1 << 14, ///<线程网络频道已更改
    OT_CHANGED_THREAD_PANID                 = 1 << 15, ///<线程网络PAN Id已更改
    OT_CHANGED_THREAD_NETWORK_NAME          = 1 << 16, ///<线程网络名称已更改
    OT_CHANGED_THREAD_EXT_PANID             = 1 << 17, ///<线程网络扩展PAN ID已更改
    OT_CHANGED_NETWORK_KEY                  = 1 << 18, ///<网络密钥已更改
    OT_CHANGED_PSKC                         = 1 << 19, ///<PSKc已更改
    OT_CHANGED_SECURITY_POLICY              = 1 << 20, ///<安全策略已更改
    OT_CHANGED_CHANNEL_MANAGER_NEW_CHANNEL  = 1 << 21, ///<通道管理器新的挂起线程通道已更改
    OT_CHANGED_SUPPORTED_CHANNEL_MASK       = 1 << 22, ///<支持的频道掩码已更改
    OT_CHANGED_COMMISSIONER_STATE           = 1 << 23, ///<专员状态已更改
    OT_CHANGED_THREAD_NETIF_STATE           = 1 << 24, ///<线程网络接口状态已更改
    OT_CHANGED_THREAD_BACKBONE_ROUTER_STATE = 1 << 25, ///<骨干路由器状态已更改
    OT_CHANGED_THREAD_BACKBONE_ROUTER_LOCAL = 1 << 26, ///<本地骨干路由器配置已更改
    OT_CHANGED_JOINER_STATE                 = 1 << 27, ///<加入者状态已更改
    OT_CHANGED_ACTIVE_DATASET               = 1 << 28, ///<活动操作数据集已更改
    OT_CHANGED_PENDING_DATASET              = 1 << 29, ///<挂起操作数据集已更改
};

/**
 * 此类型表示指示已更改的特定状态/配置的位字段。请参见`OT_CHANGED_*`定义。
 *
 */
typedef uint32_t otChangedFlags;

/**
 * 调用此函数指针以通知OpenThread中的某些配置或状态更改。
 *
 * @param[in]  aFlags    指示已更改的特定状态的位字段。请参见`OT_CHANGED_*`定义。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otStateChangedCallback)(otChangedFlags aFlags, void *aContext);

/**
 * 此函数注册回调，以指示OpenThread中的某些配置或状态何时更改。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aCallback  指向在特定配置或状态更改时调用的函数的指针。
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE将回调添加到回调列表中。
 * @retval OT_ERROR_ALREADY回调已注册。
 * @retval 由于资源限制，OT_ERROR_NO_BUFS无法添加回调。
 *
 */
otError otSetStateChangedCallback(otInstance *aInstance, otStateChangedCallback aCallback, void *aContext);

/**
 * 此函数删除一个回调，以指示OpenThread中的某些配置或状态何时更改。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aCallback   指向在特定配置或状态更改时调用的函数的指针。
 * @param[in]  aContext    指向应用程序特定上下文的指针。
 *
 */
void otRemoveStateChangeCallback(otInstance *aInstance, otStateChangedCallback aCallback, void *aContext);

/**
 * 此方法触发平台重置。
 *
 * 重置过程确保所有OpenThread状态/信息（存储在易失性内存中）被擦除。请注意，“otPlatformReset”不会删除保存在非易失性存储器中的任何持久状态/信息。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otInstanceReset(otInstance *aInstance);

/**
 * 此方法删除存储在非易失性存储器上的所有设置，然后触发平台重置。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otInstanceFactoryReset(otInstance *aInstance);

/**
 * 此方法重置OpenThread无线电堆栈的内部状态。
 *
 * 保留回调和配置。
 *
 * 此API仅在无线电版本下可用（`OPENTHREAD_radio=1`）。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otInstanceResetRadioStack(otInstance *aInstance);

/**
 * 此函数清除存储在非易失性内存中的所有OpenThread持久信息（网络设置）。仅当设备处于“禁用”状态/角色时，擦除才成功。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功擦除所有持久信息/状态。
 * @retval OT_ERROR_INVALID_STATE设备未处于“禁用”状态/角色。
 *
 */
otError otInstanceErasePersistentInfo(otInstance *aInstance);

/**
 * 此函数获取OpenThread版本字符串。
 *
 * @returns 指向OpenThread版本的指针。
 *
 */
const char *otGetVersionString(void);

/**
 * 此函数获取OpenThread无线电版本字符串。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 指向OpenThread无线电版本的指针。
 *
 */
const char *otGetRadioVersionString(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_INSTANCE_H_

