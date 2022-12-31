/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread SRP（服务注册协议）客户端API。
 */

#ifndef OPENTHREAD_SRP_CLIENT_H_
#define OPENTHREAD_SRP_CLIENT_H_

#include <openthread/dns.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api srp
 *
 * @brief 此模块包括控制SRP客户端行为的功能。
 *
 * @{
 *
 */

/**
 * 此枚举指定SRP客户端项（服务或主机信息）状态。
 *
 */
typedef enum
{
    OT_SRP_CLIENT_ITEM_STATE_TO_ADD,     ///<要添加/注册的项目。
    OT_SRP_CLIENT_ITEM_STATE_ADDING,     ///<正在添加/注册项目。
    OT_SRP_CLIENT_ITEM_STATE_TO_REFRESH, ///<要刷新的项目（重新注册以续订租约）。
    OT_SRP_CLIENT_ITEM_STATE_REFRESHING, ///<项目正在刷新。
    OT_SRP_CLIENT_ITEM_STATE_TO_REMOVE,  ///<要删除的项目。
    OT_SRP_CLIENT_ITEM_STATE_REMOVING,   ///<正在删除项。
    OT_SRP_CLIENT_ITEM_STATE_REGISTERED, ///<项目已向服务器注册。
    OT_SRP_CLIENT_ITEM_STATE_REMOVED,    ///<项目已删除。
} otSrpClientItemState;

/**
 * 此结构表示SRP客户端主机信息。
 *
 */
typedef struct otSrpClientHostInfo
{
    const char *         mName;         ///<主机名（标签）字符串（如果尚未设置，则为NULL）。
    const otIp6Address * mAddresses;    ///<指向主机IPv6地址数组的指针（如果尚未设置，则为NULL）。
    uint8_t              mNumAddresses; ///<“mAddresses”阵列中的IPv6地址数。
    otSrpClientItemState mState;        ///<主机信息状态。
} otSrpClientHostInfo;

/**
 * 此结构表示SRP客户端服务。
 *
 * 此结构中的值（包括名称和TXT记录项的字符串缓冲区）必须在将此结构的实例从`otSrpClientAddService（）`或`otSrpClientRemoveService（）'传递给OpenThread后保持不变。
 *
 */
typedef struct otSrpClientService
{
    const char *         mName;          ///<服务名称标签（例如，“_chip_udp”，而不是完整域名）。
    const char *         mInstanceName;  ///<服务实例名称标签（不是全名）。
    const char *const *  mSubTypeLabels; ///<服务子类型标签数组（必须以“NULL”结尾，也可以是“NULL”）。
    const otDnsTxtEntry *mTxtEntries;    ///<TXT条目数组（条目数量由`mNumTxtEntries`给出）。
    uint16_t             mPort;          ///<服务端口号。
    uint16_t             mPriority;      ///<服务优先级。
    uint16_t             mWeight;        ///<使用重量。
    uint8_t              mNumTxtEntries; ///<“mTxtEntries”数组中的条目数。

    /**
     * @note 以下字段仅由OT核心使用/管理。它们的值无关紧要，当在“otSrpClientAddService（）”或“otSrtClientRemoveService（））”中传递“otSrpClientService”的实例时，它们的值将被忽略。用户不应修改这些字段。
     *
     */

    otSrpClientItemState       mState; ///<服务状态（由OT核心管理）。
    uint32_t                   mData;  ///<内部数据（OT核心使用）。
    struct otSrpClientService *mNext;  ///<指向链接列表中下一个条目的指针（由OT核心管理）。
} otSrpClientService;

/**
 * 此函数指针类型定义SRP客户端用于通知用户更改/事件/错误的回调。
 *
 * 在成功向SRP服务器注册更新（即添加/删除主机信息和/或某些服务）时，或者如果出现故障或错误（例如，服务器拒绝更新请求或客户端超时等待响应等），将调用此回调。
 *
 * 如果成功重新注册更新，“aError”参数将为“OT_ERROR_NONE”，主机信息和服务的完整列表将作为回调的输入参数提供。注意，主机信息和服务每个都在相关数据结构的对应“mState”成员变量中跟踪其自身的状态（指示主机信息/服务是已注册还是已删除，还是仍在添加/删除等的状态）。
 *
 * 删除的服务列表作为其自己的链接列表“aRemovedServices”在回调中传递。请注意，当调用回调时，SRP客户端（OpenThread实现）使用“aRemovedServices”中列出的已删除服务实例完成，并且不再跟踪/存储它们（即，如果从回调调用“otSrpClientGetServices（）”，则已删除的服务将不会出现在返回的列表中）。在回调中提供单独的已删除服务列表有助于向用户指示哪些项现在已删除，并允许用户重新声明/重用实例。
 *
 * 如果服务器拒绝SRP更新请求，DNS响应代码（RFC 2136）将映射到以下错误：
 *
 *  -（0）NOERROR成功（无错误条件）->OT_error_NONE
 *  -（1）由于格式错误，FORMERR服务器无法解释->OT_error_PARSE
 *  -（2）SERVERFAIL服务器遇到内部故障->OT_ERROR_FAILED
 *  -（3）NXDOMAIN名称应该存在，但不存在->OT_ERROR_not_FOUND
 *  -（4）NOTIMP服务器不支持查询类型（OpCode）->OT_ERROR_not_IMPLEMENTED
 *  -（5）由于策略/安全原因拒绝REFUSED服务器->OT_ERROR_security
 *  -（6）YXDOMAIN某些不应该存在的名称确实存在->OT_ERROR_DUPLICATED
 *  -（7）YXRSET某些不应该存在的RRset确实存在->OT_ERROR_DUPLICATED
 *  -（8）NXRRSET某些应该存在但不存在的RRset->OT_ERROR_not_FOUND
 *  -（9）NOTAUTH服务对区域->OT_ERROR_SECURITY无效
 *  -（10）NOTZONE名称不在区域中->OT_ERROR_PARSE
 *  -（20）BADNAME名称错误->OT_ERROR_PARSE
 *  -（21）BADALG坏算法->OT_ERROR_SECURITY
 *  -（22）错误截断->OT_ERROR_PARSE
 *  -其他响应代码->OT_ERROR_FAILED
 *
 * 也可能出现以下错误：
 *
 *  -OT_ERROR_RESPONSE_TIMEOUT：等待服务器响应超时（客户端将继续重试）。
 *  -OT_ERROR_INVALID_ARGS:提供的服务结构无效（例如，服务名称错误或“otDnsTxtEntry”）。
 *  -OT_ERROR_NO_BUFS:缓冲区不足，无法准备或发送更新消息。
 *
 * 请注意，如果出现任何故障，客户端将继续操作，即在等待一段时间后准备并（重新）向服务器发送SRP更新消息。重试等待间隔从最小值开始，并在每次失败时增加增长因子，直到最大值（有关详细信息，请参阅配置参数`OPENTHREAD_CONFIG_SRP_CLIENT_MIN_retry_wait_interval`和相关参数）。
 *
 * @param[in] aError            错误（见上文）。
 * @param[in] aHostInfo         指向主机信息的指针。
 * @param[in] aService          包含所有服务（不包括已删除的服务）的链接列表的开头。如果列表为空，则为NULL。
 * @param[in] aRemovedServices  包含所有已删除服务的链接列表的开头。如果列表为空，则为NULL。
 * @param[in] aContext          指向任意上下文的指针（在注册回调时提供）。
 *
 */
typedef void (*otSrpClientCallback)(otError                    aError,
                                    const otSrpClientHostInfo *aHostInfo,
                                    const otSrpClientService * aServices,
                                    const otSrpClientService * aRemovedServices,
                                    void *                     aContext);

/**
 * 此函数指针类型定义SRP客户端用于在自动启动或停止时通知用户的回调。
 *
 * 这仅在启用自动启动功能`OPENTHREAD_CONFIG_SRP_CLIENT_auto_start_API_ENABLE`时使用。
 *
 * 当启用自动启动模式且SRP客户端自动启动或停止时，将调用此回调。
 *
 * @param[in] aServerSockAddress   非NULL指针表示SRP服务器已启动，指针将给出选定的服务器套接字地址。NULL指针表示SRP服务器已停止。
 * @param[in] aContext             指向任意上下文的指针（在注册回调时提供）。
 *
 */
typedef void (*otSrpClientAutoStartCallback)(const otSockAddr *aServerSockAddr, void *aContext);

/**
 * 此函数启动SRP客户端操作。
 *
 * 满足以下所有条件后，SRP客户端将准备并向SRP服务器发送“SRP更新”消息：
 *
 *  -SRP客户端启动-调用“otSrpClientStart（）”。
 *  -主机名已设置-调用`otSrpClientSetHostName（）`。
 *  -至少设置了一个主机IPv6地址-调用了“otSrpClientSetHostName（）”。
 *  -至少添加了一个服务-调用了“otSrpClientAddService（）”。
 *
 * 调用这些函数的顺序无关紧要。当满足所有条件时，SRP客户端将在准备“SRP更新”消息并将其发送到服务器之前等待短暂的延迟。此延迟允许用户在发送第一个SRP更新消息之前添加多个服务和/或IPv6地址（确保发送包含所有信息的单个SRP更新）。配置`OPENTHREAD_config_SRP_CLIENT_UPDATE_TX_DELAY`指定延迟间隔。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aServerSockAddr  SRP服务器的套接字地址（IPv6地址和端口号）。
 *
 * @retval OT_ERROR_NONE SRP客户端操作已成功启动，或已使用相同的服务器套接字地址和回调运行。
 * @retval OT_ERROR_BUSY SRP客户端正忙着使用不同的套接字地址运行。
 * @retval OT_ERROR_FAILED无法打开/连接客户端的UDP套接字。
 *
 */
otError otSrpClientStart(otInstance *aInstance, const otSockAddr *aServerSockAddr);

/**
 * 此函数用于停止SRP客户端操作。
 *
 * 此函数停止与SRP服务器的任何进一步交互。请注意，它不会删除或清除主机信息和/或服务列表。它会在客户端重新启动后标记所有要再次添加/删除的服务。
 *
 * @param[in] aInstance       指向OpenThread实例的指针。
 *
 */
void otSrpClientStop(otInstance *aInstance);

/**
 * 此函数指示SRP客户端是否正在运行。
 *
 * @param[in] aInstance       指向OpenThread实例的指针。
 *
 * @returns 如果SRP客户端正在运行，则为TRUE，否则为FALSE。
 *
 */
bool otSrpClientIsRunning(otInstance *aInstance);

/**
 * 此函数获取SRP客户端正在使用的SRP服务器的套接字地址（IPv6地址和端口号）。
 *
 * 如果客户端未运行，则地址未指定（全部为零），端口号为零。
 *
 * @param[in] aInstance       指向OpenThread实例的指针。
 *
 * @returns 指向SRP服务器套接字地址的指针（总是非NULL）。
 *
 */
const otSockAddr *otSrpClientGetServerAddress(otInstance *aInstance);

/**
 * 此函数设置回调以通知调用方来自SRP客户端的事件/更改。
 *
 * SRP客户端允许注册单个回调。因此，对该函数的连续调用将覆盖以前设置的任何回调函数。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 * @param[in] aCallback   通知事件和更改的回调。如果不需要，可以为NULL。
 * @param[in] aContext    与@p aCallback一起使用的任意上下文。
 *
 */
void otSrpClientSetCallback(otInstance *aInstance, otSrpClientCallback aCallback, void *aContext);

/**
 * 此功能启用自动启动模式。
 *
 * 这仅在启用自动启动功能`OPENTHREAD_CONFIG_SRP_CLIENT_auto_start_API_ENABLE`时可用。
 *
 * 配置选项`OPENTHREAD_Config_SRP_CLIENT_AUTO_START_DEFAULT_MODE`指定默认自动启动模式（在OT堆栈开始时启用还是禁用）。
 *
 * 启用自动启动后，SRP客户端将监控SRP服务器服务条目的线程网络数据，并在检测到SRP服务器时自动启动和停止客户端。
 *
 * 如果找到多个SRP服务器，将随机选择一个。如果不再检测到所选SRP服务器（不再出现在线程网络数据中），SRP客户端将停止，然后它可以切换到另一个SRP服务器。
 *
 * 当通过成功调用“otSrpClientStart（）”显式启动SRP客户端时，无论自动启动模式的状态如何，以及在线程网络数据中是否发现相同的SRP服务器地址，都将继续使用“otSrpClientStart（（）”中给定的SRP服务器地址。在这种情况下，只有显式的“otSrpClientStop（）”调用才会停止客户端。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 * @param[in] aCallback   用于通知客户端何时自动启动/停止的回调。如果不需要，可以为NULL。
 * @param[in] aContext    调用@p aCallback时要传递的上下文。
 *
 */
void otSrpClientEnableAutoStartMode(otInstance *aInstance, otSrpClientAutoStartCallback aCallback, void *aContext);

/**
 * 此功能禁用自动启动模式。
 *
 * 这仅在启用自动启动功能`OPENTHREAD_CONFIG_SRP_CLIENT_auto_start_API_ENABLE`时可用。
 *
 * 如果客户端已在运行，禁用自动启动模式不会停止客户端，但客户端会停止监视线程网络数据，以验证所选SRP服务器是否仍在其中。
 *
 * 请注意，调用“otSrpClientStop（）”也将禁用自动启动模式。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 *
 */
void otSrpClientDisableAutoStartMode(otInstance *aInstance);

/**
 * 此功能指示自动启动模式的当前状态（启用或禁用）。
 *
 * 这仅在启用自动启动功能`OPENTHREAD_CONFIG_SRP_CLIENT_auto_start_API_ENABLE`时可用。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 *
 * @returns 如果启用了自动启动模式，则为TRUE，否则为FALSE。
 *
 */
bool otSrpClientIsAutoStartModeEnabled(otInstance *aInstance);

/**
 * 此函数获取SRP更新请求中使用的租用间隔。
 *
 * 请注意，这是SRP客户端请求的租赁期限。服务器可以选择接受不同的租赁间隔。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 *
 * @returns 租赁间隔（秒）。
 *
 */
uint32_t otSrpClientGetLeaseInterval(otInstance *aInstance);

/**
 * 此函数设置SRP更新请求中使用的租用间隔。
 *
 * 更改租赁间隔不会影响已注册服务/主机信息的可接受租赁间隔。它只影响任何未来的SRP更新消息（即，添加新服务和/或刷新现有服务）。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 * @param[in] aInterval   租赁间隔（秒）。如果为零，将使用`OPENTHREAD_CONFIG_SRP_CLIENT_default_LEASE`指定的默认值。
 *
 */
void otSrpClientSetLeaseInterval(otInstance *aInstance, uint32_t aInterval);

/**
 * 此函数获取SRP更新请求中使用的密钥租用间隔。
 *
 * 请注意，这是SRP客户端请求的租赁期限。服务器可以选择接受不同的租赁间隔。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 *
 * @returns 密钥租用间隔（秒）。
 *
 */
uint32_t otSrpClientGetKeyLeaseInterval(otInstance *aInstance);

/**
 * 此函数设置SRP更新请求中使用的密钥租用间隔。
 *
 * 更改租赁间隔不会影响已注册服务/主机信息的可接受租赁间隔。它只影响任何未来的SRP更新消息（即，添加新服务和/或刷新现有服务）。
 *
 * @param[in] aInstance    指向OpenThread实例的指针。
 * @param[in] aInterval    密钥租用间隔（秒）。如果为零，将使用`OPENTHREAD_CONFIG_SRP_CLIENT_default_KEY_LEASE`指定的默认值。
 *
 */
void otSrpClientSetKeyLeaseInterval(otInstance *aInstance, uint32_t aInterval);

/**
 * 此函数获取主机信息。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 *
 * @returns 指向主机信息结构的指针。
 *
 */
const otSrpClientHostInfo *otSrpClientGetHostInfo(otInstance *aInstance);

/**
 * 此函数用于设置主机名标签。
 *
 * 成功调用此函数后，将调用“otSrpClientCallback”以向SRP服务器报告主机信息注册状态。
 *
 * The name string buffer pointed to by @p aName必须保持不变，并在从该函数返回后保持不变。OpenThread将保留指向字符串的指针。
 *
 * 可以在客户端启动之前或启动之后，但在向服务器注册主机信息之前设置主机名（主机信息应为“STATE_TO_ADD”或“STATE_REMOVED”）。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 * @param[in] aName       指向主机名标签字符串的指针（不能为空）。指向字符串缓冲区的指针必须持续存在，并在从该函数返回后保持有效和恒定。
 *
 * @retval OT_ERROR_NONE已成功设置主机名标签。
 * @retval OT_ERROR_INVALID_ARGS@p aName为空。
 * @retval OT_ERROR_INVALID_STATE主机名已设置并向服务器注册。
 *
 */
otError otSrpClientSetHostName(otInstance *aInstance, const char *aName);

/**
 * 此函数用于设置/更新主机IPv6地址列表。
 *
 * 主机IPv6地址可以在SRP客户端启动之前或运行期间设置/更改（例如，添加/删除或更改先前注册的主机地址），除非正在删除主机信息（客户端正忙于处理来自先前调用“otSrpClientRemoveHostAndServices（）”的删除请求，并且主机信息仍处于“STATE_to_remove”或“STATE_REMOVING”状态）。
 *
 * The host IPv6 address array pointed to by @p a从该函数返回后，地址必须保持不变（使用“OT_ERROR_NONE”）。OpenThread将保存指向数组的指针。
 *
 * 成功调用此函数后，将调用“otSrpClientCallback”以向SRP服务器报告地址注册的状态。
 *
 * @param[in] aInstance           指向OpenThread实例的指针。
 * @param[in] aAddresses          指向包含主机IPv6地址的数组的指针。
 * @param[in] aNumAddresses       @p aAddresses数组中的地址数。
 *
 * @retval OT_ERROR_NONE主机IPv6地址列表更改已成功启动。将调用“otSrpClientCallback”报告向服务器注册地址的状态。
 * @retval OT_ERROR_INVALID_ARGS地址列表无效（例如，必须至少包含一个地址）。
 * @retval OT_ERROR_INVALID_STATE主机正在删除，因此无法更改主机地址。
 *
 */
otError otSrpClientSetHostAddresses(otInstance *aInstance, const otIp6Address *aIp6Addresses, uint8_t aNumAddresses);

/**
 * 此函数用于添加要向服务器注册的服务。
 *
 * 成功调用此函数后，将调用“otSrpClientCallback”以向SRP服务器报告服务添加/注册的状态。
 *
 * The `otSrpClientService` instance being pointed to by @p a从该函数返回后，服务必须保持不变（使用“OT_ERROR_NONE”）。OpenThread将保存指向服务实例的指针。
 *
 * OpenThread不再跟踪“otSrpClientService”实例，只有在
 *
 *  -它通过调用“otSrpClientRemoveService（）”显式删除，或通过调用“OTSrpClientMoveHostAndServices（）”与其他服务一起删除，并且只有在调用“otSrpClientCallback”指示服务已删除后才能删除。或
 *  -对“otSrpClientClearHostAndServices（）”的调用，将立即删除主机和所有相关服务。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aService         指向要添加的“otSrpClientService”实例的指针。

 * @retval OT_ERROR_NONE添加服务成功启动。将调用“otSrpClientCallback”来报告状态。
 * @retval OT_ERROR_ALREADY列表中已存在具有相同服务和实例名称的服务。
 * @retval OT_ERROR_INVALID_ARGS服务结构无效（例如，服务名称错误或`otDnsTxtEntry`）。
 *
 */
otError otSrpClientAddService(otInstance *aInstance, otSrpClientService *aService);

/**
 * 此函数请求向服务器注销服务。
 *
 * 成功调用此函数后，将调用“otSrpClientCallback”以向SRP服务器报告删除请求的状态。

 * The `otSrpClientService` instance being pointed to by @p a从该函数返回后，服务必须保持不变（使用“OT_ERROR_NONE”）。OpenThread将在删除过程中保留服务实例。只有在调用了“otSrpClientCallback”之后，才能指示服务实例已从SRP客户端服务列表中删除，并且可以被释放/重用。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aService         指向要删除的“otSrpClientService”实例的指针。
 *
 * @retval OT_ERROR_NONE服务删除已成功启动。将调用“otSrpClientCallback”来报告状态。
 * @retval OT_ERROR_NOT_FOUND在列表中找不到服务。
 *
 */
otError otSrpClientRemoveService(otInstance *aInstance, otSrpClientService *aService);

/**
 * 此函数清除服务，立即将其从客户端服务列表中删除。
 *
 * 与向服务器发送更新消息以删除服务的“otSrpClientRemoveService（）”不同，此函数从客户端的服务列表中清除服务，而无需与服务器进行任何交互。成功调用此函数后，不会调用“otSrpClientCallback”，调用方可以立即回收并重新使用@p aService条目。
 *
 * This function can be used along with a subsequent call to `otSrpClientAddService()` (potentially reusing the same @p 具有相同服务和实例名称的服务条目）来更新现有服务中的一些参数。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aService         指向要删除的“otSrpClientService”实例的指针。
 *
 * @retval OT_ERROR_NONE成功删除@p aService。可立即回收再利用。
 * @retval OT_ERROR_NOT_FOUND在列表中找不到服务。
 *
 */
otError otSrpClientClearService(otInstance *aInstance, otSrpClientService *aService);

/**
 * 此函数获取客户端管理的服务列表。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 *
 * @returns 指向所有服务的链接列表头的指针，如果列表为空，则为NULL。
 *
 */
const otSrpClientService *otSrpClientGetServices(otInstance *aInstance);

/**
 * 此函数启动主机信息和所有服务的删除过程。
 *
 * 从该函数返回后，将调用“otSrpClientCallback”以向SRP服务器报告删除请求的状态。
 *
 * If the host info is to be permanently removed from server, @p aRemoveKeyLease应设置为“true”，这将删除与服务器上主机关联的密钥租约。否则，密钥租用记录将保持原样，这将确保服务器保留主机名，以备客户端再次能够提供和注册其服务时使用。
 *
 * The @p aSendUnregisterServer确定主机信息尚未向服务器注册时的行为。如果
 * @p aSendUnregisterServer设置为“false”（这是默认值/预期值），则SRP客户端将立即删除主机信息和服务，而无需向服务器发送更新消息（如果
 * nothing is yet registered with it). If @p aSendUnregisterServer设置为“true”，则SRP客户端将向服务器发送更新消息。请注意，如果注册了主机信息，则@p aSendUnrollToServer的值无关紧要，SRP客户端将始终向服务器发送更新消息，请求删除所有信息。
 *
 * One situation where @p 如果在设备重置/重新启动时，调用方可能希望删除服务器上以前注册的任何服务，则SendUnregisterServer可能会很有用。在这种情况下，调用者可以“otSrpClientSetHostName（）”，然后请求“otSrpClientRemoveHostAndServices（）”并将“aSendUngToServer”设置为“true”。
 *
 * @param[in] aInstance          指向OpenThread实例的指针。
 * @param[in] aRemoveKeyLease    一个布尔值，指示是否也应删除主机密钥租约。
 * @param[in] aSendUnregToServer 一个布尔值，指示在未注册主机信息时是否向服务器发送更新。
 *
 * @retval OT_ERROR_NONE成功开始删除主机信息和服务。将调用“otSrpClientCallback”来报告状态。
 * @retval OT_ERROR_ALREADY主机信息已删除。
 *
 */
otError otSrpClientRemoveHostAndServices(otInstance *aInstance, bool aRemoveKeyLease, bool aSendUnregToServer);

/**
 * 此函数清除所有主机信息和所有服务。
 *
 * 与向服务器发送更新消息以删除所有信息的`otSrpClientRemoveHostAndServices（）`不同，此函数会立即清除所有信息，而无需与服务器进行任何交互。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 *
 */
void otSrpClientClearHostAndServices(otInstance *aInstance);

/**
 * 此函数获取SRP客户端使用的域名。
 *
 * 此函数需要启用`OPENTHREAD_CONFIG_SRP_CLIENT_DOMAIN_NAME_API_ENABLE`。
 *
 * 如果未设置域名，将使用“default.service.arpa”。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 *
 * @returns 域名字符串。
 *
 */
const char *otSrpClientGetDomainName(otInstance *aInstance);

/**
 * 此函数设置SRP客户端使用的域名。
 *
 * 此函数需要启用`OPENTHREAD_CONFIG_SRP_CLIENT_DOMAIN_NAME_API_ENABLE`。
 *
 * 如果未设置，将使用“default.service.arpa”。
 *
 * The name string buffer pointed to by @p aName必须保持不变，并在从该函数返回后保持不变。OpenThread将保留指向字符串的指针。
 *
 * 可以在客户端启动之前或启动之后，但在主机信息向服务器注册之前设置域名（主机信息应为“STATE_TO_ADD”或“STATE_TOP_REMOVE”）。
 *
 * @param[in] aInstance     指向OpenThread实例的指针。
 * @param[in] aName         指向域名字符串的指针。如果为NULL，则将其设置为默认值“default.service.arpa”。
 *
 * @retval OT_ERROR_NONE已成功设置域名标签。
 * @retval OT_ERROR_INVALID_STATE主机信息已向服务器注册。
 *
 */
otError otSrpClientSetDomainName(otInstance *aInstance, const char *aName);

/**
 * 此函数将“otSrpClientItemState”转换为字符串。
 *
 * @param[in] aItemState  项目状态。
 *
 * @returns @p aItemState的字符串表示。
 *
 */
const char *otSrpClientItemStateToString(otSrpClientItemState aItemState);

/**
 * 此功能启用/禁用“服务密钥记录包含”模式。
 *
 * 启用后，SRP客户端将在其发送的SRP更新消息中的服务描述说明中包含KEY记录。
 *
 * 当启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”配置时，此功能可用。
 *
 * @note KEY记录在“服务描述说明”中是可选的（它是必需的，并且始终包含在“主机描述说明”内）。SRP客户端的默认行为是不包含它。此函数旨在覆盖仅用于测试的默认行为。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aEnabled   TRUE表示启用，FALSE表示禁用“服务密钥记录包含”模式。
 *
 */
void otSrpClientSetServiceKeyRecordEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此方法指示“服务密钥记录包含”模式是启用还是禁用。
 *
 * 当启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”配置时，此功能可用。
 *
 * @param[in] aInstance     指向OpenThread实例的指针。
 *
 * @returns 如果启用了“服务密钥记录包含”模式，则为TRUE，否则为FALSE。
 *
 */
bool otSrpClientIsServiceKeyRecordEnabled(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_SRP_CLIENT_H_

