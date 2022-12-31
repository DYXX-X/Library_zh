/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义了服务注册协议（SRP）服务器的API。
 */

#ifndef OPENTHREAD_SRP_SERVER_H_
#define OPENTHREAD_SRP_SERVER_H_

#include <stdint.h>

#include <openthread/dns.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api srp
 *
 * @brief 该模块包括服务注册协议的功能。
 *
 * @{
 *
 */

/**
 * 此不透明类型表示SRP服务主机。
 *
 */
typedef struct otSrpServerHost otSrpServerHost;

/**
 * 此不透明类型表示SRP服务。
 *
 */
typedef struct otSrpServerService otSrpServerService;

/**
 * SRP服务器上SRP服务更新事务的ID。
 *
 */
typedef uint32_t otSrpServerServiceUpdateId;

/**
 * 服务标志类型，用于指示在SRP服务列表中搜索（或迭代）时要包含或排除哪些服务。
 *
 * 这是位标志的组合。特定位标志在枚举`OT_SRP_SERVER_FLAG_*`中定义。
 *
 */
typedef uint8_t otSrpServerServiceFlags;

enum
{
    OT_SRP_SERVER_SERVICE_FLAG_BASE_TYPE = 1 << 0, ///<包括基本服务（不是子类型）。
    OT_SRP_SERVER_SERVICE_FLAG_SUB_TYPE  = 1 << 1, ///<包括子类型服务。
    OT_SRP_SERVER_SERVICE_FLAG_ACTIVE    = 1 << 2, ///<包括活动（未删除）服务。
    OT_SRP_SERVER_SERVICE_FLAG_DELETED   = 1 << 3, ///<包括删除的服务。
};

enum
{
    /**
     * 此常量定义一个“otSrpServerServiceFlags”组合，接受任何服务（基本/子类型、活动/删除）。
     *
     */
    OT_SRP_SERVER_FLAGS_ANY_SERVICE = (OT_SRP_SERVER_SERVICE_FLAG_BASE_TYPE | OT_SRP_SERVER_SERVICE_FLAG_SUB_TYPE |
                                       OT_SRP_SERVER_SERVICE_FLAG_ACTIVE | OT_SRP_SERVER_SERVICE_FLAG_DELETED),

    /**
     * 此常量定义仅接受基本服务的“otSrpServerServiceFlags”组合。
     *
     */
    OT_SRP_SERVER_FLAGS_BASE_TYPE_SERVICE_ONLY =
        (OT_SRP_SERVER_SERVICE_FLAG_BASE_TYPE | OT_SRP_SERVER_SERVICE_FLAG_ACTIVE | OT_SRP_SERVER_SERVICE_FLAG_DELETED),

    /**
     * 此常量定义仅接受子类型服务的“otSrpServerServiceFlags”组合。
     *
     */
    OT_SRP_SERVER_FLAGS_SUB_TYPE_SERVICE_ONLY =
        (OT_SRP_SERVER_SERVICE_FLAG_SUB_TYPE | OT_SRP_SERVER_SERVICE_FLAG_ACTIVE | OT_SRP_SERVER_SERVICE_FLAG_DELETED),

    /**
     * 此常量定义接受任何活动服务（未删除）的“otSrpServerServiceFlags”组合。
     *
     */
    OT_SRP_SERVER_FLAGS_ANY_TYPE_ACTIVE_SERVICE =
        (OT_SRP_SERVER_SERVICE_FLAG_BASE_TYPE | OT_SRP_SERVER_SERVICE_FLAG_SUB_TYPE |
         OT_SRP_SERVER_SERVICE_FLAG_ACTIVE),

    /**
     * 此常量定义接受任何已删除服务的“otSrpServerServiceFlags”组合。
     *
     */
    OT_SRP_SERVER_FLAGS_ANY_TYPE_DELETED_SERVICE =
        (OT_SRP_SERVER_SERVICE_FLAG_BASE_TYPE | OT_SRP_SERVER_SERVICE_FLAG_SUB_TYPE |
         OT_SRP_SERVER_SERVICE_FLAG_ACTIVE),
};

/**
 * 表示SRP服务器的状态
 *
 */
typedef enum
{
    OT_SRP_SERVER_STATE_DISABLED = 0, ///<SRP服务器已禁用。
    OT_SRP_SERVER_STATE_RUNNING  = 1, ///<SRP服务器正在运行。
    OT_SRP_SERVER_STATE_STOPPED  = 2, ///<SRP服务器已停止。
} otSrpServerState;

/**
 * 此枚举表示SRP服务器使用的地址模式。
 *
 * 地址模式指定SRP服务器如何确定地址和端口号，以及如何在线程网络数据中发布此信息。
 *
 */
typedef enum otSrpServerAddressMode
{
    OT_SRP_SERVER_ADDRESS_MODE_UNICAST = 0, ///<单播地址模式。
    OT_SRP_SERVER_ADDRESS_MODE_ANYCAST = 1, ///<Anycast地址模式。
} otSrpServerAddressMode;

/**
 * 该结构包括SRP服务器LEASE和KEY-LEASE配置。
 *
 */
typedef struct otSrpServerLeaseConfig
{
    uint32_t mMinLease;    ///<最小LEASE间隔（秒）。
    uint32_t mMaxLease;    ///<以秒为单位的最大LEASE间隔。
    uint32_t mMinKeyLease; ///<最小KEY-LEASE间隔（秒）。
    uint32_t mMaxKeyLease; ///<最大KEY-LEASE间隔（秒）。
} otSrpServerLeaseConfig;

/**
 * 此函数将授权的域返回给SRP服务器。
 *
 * 如果域未由SetDomain设置，则将返回“default.service.arpa.”。即使域设置为没有尾随点，也始终附加尾随点。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns 指向点连接域字符串的指针。
 *
 */
const char *otSrpServerGetDomain(otInstance *aInstance);

/**
 * 此函数用于设置SRP服务器上的域。
 *
 * A trailing dot will be appended to @p aDomain（如果尚未存在）。仅应在启用SRP服务器之前调用此函数。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aDomain    要设置的域。不得为空。
 *
 * @retval  OT_ERROR_NONE成功将域设置为@p aDomain。
 * @retval  OT_ERROR_INVALID_STATE SRP服务器已启用，无法更改域。
 * @retval  OT_ERROR_INVALID_ARGS参数@p aDomain不是有效的DNS域名。
 * @retval  OT_ERROR_NO_BUFS没有内存存储@p aDomain的内容。
 *
 */
otError otSrpServerSetDomain(otInstance *aInstance, const char *aDomain);

/**
 * 此函数返回SRP服务器的状态。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns SRP服务器的当前状态。
 *
 */
otSrpServerState otSrpServerGetState(otInstance *aInstance);

/**
 * 此函数返回SRP服务器使用的地址模式。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @returns SRP服务器的地址模式。
 *
 */
otSrpServerAddressMode otSrpServerGetAddressMode(otInstance *aInstance);

/**
 * 此函数设置SRP服务器使用的地址模式。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aMode      要使用的地址模式。
 *
 * @retval OT_ERROR_NONE成功设置地址模式。
 * @retval OT_ERROR_INVALID_STATE SRP服务器已启用，无法更改地址模式。
 *
 */
otError otSrpServerSetAddressMode(otInstance *aInstance, otSrpServerAddressMode aMode);

/**
 * 此函数返回用于选播地址模式的序列号。
 *
 * 序列号包含在网络数据中发布的“DNS/SRP服务选播地址”条目中。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @returns 选播序列号。
 *
 */
uint8_t otSrpServerGetAnycastModeSequenceNumber(otInstance *aInstance);

/**
 * 此函数设置用于选播地址模式的序列号。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aSequenceNumber  要使用的序列号。
 *
 * @retval OT_ERROR_NONE成功设置地址模式。
 * @retval OT_ERROR_INVALID_STATE SRP服务器已启用，序列号无法更改。
 *
 */
otError otSrpServerSetAnycastModeSequenceNumber(otInstance *aInstance, uint8_t aSequenceNumber);

/**
 * 此功能启用/禁用SRP服务器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aEnabled   启用/禁用SRP服务器的布尔值。
 *
 */
void otSrpServerSetEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此函数返回SRP服务器LEASE和KEY-LEASE配置。
 *
 * @param[in]   aInstance     指向OpenThread实例的指针。
 * @param[out]  aLeaseConfig  指向“otSrpServerLeaseConfig”实例的指针。
 *
 */
void otSrpServerGetLeaseConfig(otInstance *aInstance, otSrpServerLeaseConfig *aLeaseConfig);

/**
 * 此函数设置SRP服务器LEASE和KEY-LEASE配置。
 *
 * 当客户端请求非零LEASE时间时，授予的值将限制在[aMinLease，aMaxLease]范围内；并且将在范围[aMinKeyLease，aMaxKeyLease]中授予非零KEY-LEASE。对于零LEASE或KEY-LEASE时间，将授予零。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aLeaseConfig  指向“otSrpServerLeaseConfig”实例的指针。
 *
 * @retval  OT_ERROR_NONE成功设置LEASE和KEY-LEASE范围。
 * @retval  OT_ERROR_INVALID_ARGS LEASE或KEY-LEASE范围无效。
 *
 */
otError otSrpServerSetLeaseConfig(otInstance *aInstance, const otSrpServerLeaseConfig *aLeaseConfig);

/**
 * 此函数处理SRP服务更新。
 *
 * SRP服务器调用此函数以通知SRP主机和可能的SRP服务正在更新。重要的是，在处理程序通过调用otSrpServerHandleServiceUpdateResult返回结果或在@paTimeout之后超时之前，不会提交SRP更新。
 *
 * SRP服务观察者应始终在收到更新事件后立即调用otSrpServerHandleServiceUpdateResult，错误代码为OT_error_NONE。
 *
 * 更通用的处理程序可以对SRP主机/服务执行验证，如果任何验证失败，则拒绝SRP更新。例如，广告代理应该在支持多播的链路上通告（或删除）主机和服务，并在出现任何故障时返回特定的错误代码。
 *
 * @param[in]  aId       服务更新事务ID。此ID必须与`otSrpServerHandleServiceUpdateResult`一起返回。
 * @param[in]  aHost     指向包含SRP更新的otSrpServerHost对象的指针。处理程序应发布/取消发布主机，并且每个服务都指向具有以下规则的此主机：1。如果未删除主机（由“otSrpServerHostIsDeleted”表示），则应使用mDNS发布或更新该主机。否则，应取消发布主机（删除AAAA RR）。2.对于指向此主机的每个服务点，如果要取消发布主机，则必须取消发布。否则，处理程序应在未删除服务时发布或更新服务（由“otSrpServerServiceIsDeleted”表示），并在删除时取消发布。
 * @param[in]  aTimeout  处理程序处理服务事件的最长时间（毫秒）。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 * @sa otSrpServerSetServiceUpdateHandler
 * @sa otSrpServerHandleServiceUpdateResult
 *
 */
typedef void (*otSrpServerServiceUpdateHandler)(otSrpServerServiceUpdateId aId,
                                                const otSrpServerHost *    aHost,
                                                uint32_t                   aTimeout,
                                                void *                     aContext);

/**
 * 此函数设置SRP服务器上的SRP服务更新处理程序。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aServiceHandler  指向服务处理程序的指针。使用NULL删除处理程序。
 * @param[in]  aContext         指向任意上下文信息的指针。如果未使用，则可能为NULL。
 *
 */
void otSrpServerSetServiceUpdateHandler(otInstance *                    aInstance,
                                        otSrpServerServiceUpdateHandler aServiceHandler,
                                        void *                          aContext);

/**
 * 此函数将处理SRP更新的结果报告给SRP服务器。
 *
 * 服务更新处理程序应调用此函数以返回其处理SRP更新的结果。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aId        服务更新事务ID。该ID应与通过“otSrpServerServiceUpdateHandler”提供的ID相同。
 * @param[in]  aError     要返回到SRP服务器的错误。使用OT_ERROR_DUPLICATED表示DNS名称冲突。
 *
 */
void otSrpServerHandleServiceUpdateResult(otInstance *aInstance, otSrpServerServiceUpdateId aId, otError aError);

/**
 * 此函数返回SRP服务器上的下一个注册主机。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aHost      指向当前主机的指针；使用NULL获取第一个主机。
 *
 * @returns  指向已注册主机的指针。如果找不到更多主机，则返回NULL。
 *
 */
const otSrpServerHost *otSrpServerGetNextHost(otInstance *aInstance, const otSrpServerHost *aHost);

/**
 * 此函数告知SRP服务主机是否已删除。
 *
 * SRP服务主机可以删除，但保留其名称以备将来使用。在这种情况下，不会从SRP服务器/注册表中删除主机实例。
 *
 * @param[in]  aHost  指向SRP服务主机的指针。
 *
 * @returns  如果主机已被删除，则为TRUE，否则为FALSE。
 *
 */
bool otSrpServerHostIsDeleted(const otSrpServerHost *aHost);

/**
 * 此函数返回主机的全名。
 *
 * @param[in]  aHost  指向SRP服务主机的指针。
 *
 * @returns  指向以空结尾的主机名字符串的指针。
 *
 */
const char *otSrpServerHostGetFullName(const otSrpServerHost *aHost);

/**
 * 此函数返回给定主机的地址。
 *
 * @param[in]   aHost          指向SRP服务主机的指针。
 * @param[out]  aAddressesNum  一个指针，指向应该将地址数输出到的位置。
 *
 * @returns  指向IPv6地址数组的指针。
 *
 */
const otIp6Address *otSrpServerHostGetAddresses(const otSrpServerHost *aHost, uint8_t *aAddressesNum);

/**
 * 此函数返回给定主机的下一个服务（不包括任何子类型服务）。
 *
 * @note 此函数已被弃用，将被删除`可以改用otSrpServerHostFindNextService（）。
 *
 * @param[in]  aHost     指向SRP服务主机的指针。
 * @param[in]  aService  指向当前SRP服务实例的指针；使用NULL获取第一个服务。
 *
 * @returns  指向下一个服务的指针，如果没有更多服务，则返回NULL。
 *
 */
const otSrpServerService *otSrpServerHostGetNextService(const otSrpServerHost *   aHost,
                                                        const otSrpServerService *aService);

/**
 * 此函数用于查找主机上的下一个匹配服务。
 *
 * 标志、服务和实例名称的组合允许对服务的完整列表和/或它们的子集进行迭代，以匹配特定条件，或找到特定服务。
 *
 * 要迭代主机的所有服务：service=otSrpServerHostFindNextService（主机，服务，OT_SRP_SERVER_FLAGS_ANY_service，NULL，NULL）；
 *
 * 仅迭代基本服务（排除子类型）：service=otSrpServerHostFindNextService（主机，服务，OT_SRP_SERVER_FLAGS_base_TYPE_service_only，NULL，NULL）；
 *
 * 要迭代特定实例名称“instanceName”的子类型：service=otSrpServerHostFindNextService（主机，服务，OT_SRP_SERVER_FLAGS_sub_TYPE_service_ONLY，NULL，instanceName）；
 *
 * 要查找具有服务名称“serviceName”和服务实例名称“instanceName”的特定服务，请执行以下操作：service=otSrpServerHostFindNextService（host，NULL，OT_SRP_SERVER_FLAGS_ANY_service，serviceName，instanceName）；
 *
 * 要查找具有给定服务实例名称“instanceName”的基本类型服务：service=otSrpServerHostFindNextService（host，NULL，OT_SRP_SERVER_FLAGS_base_type_service_ONLY，NULL，instanceName）；
 *
 * @param[in] aHost          指向SRP服务主机的指针（不得为空）。
 * @param[in] aPrevService   指向上一个服务的指针，或从列表开头开始为NULL。
 * @param[in] aFlags         指示要包括哪些服务的标志（基本/子类型、活动/已删除）。
 * @param[in] aServiceName   要匹配的服务名称。设置为NULL以接受任何名称。
 * @param[in] aInstanceName  要匹配的服务实例名称。设置为NULL以接受任何名称。
 *
 * @returns  指向下一个匹配服务的指针，如果找不到匹配服务，则返回NULL。
 *
 */
const otSrpServerService *otSrpServerHostFindNextService(const otSrpServerHost *   aHost,
                                                         const otSrpServerService *aPrevService,
                                                         otSrpServerServiceFlags   aFlags,
                                                         const char *              aServiceName,
                                                         const char *              aInstanceName);

/**
 * 此函数指示SRP服务是否已删除。
 *
 * SRP服务可以删除，但保留其名称以备将来使用。在这种情况下，服务实例不会从SRP服务器/注册表中删除。如果删除主机，则保证删除所有服务。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  如果服务已被删除，则为TRUE，否则为FALSE。
 *
 */
bool otSrpServerServiceIsDeleted(const otSrpServerService *aService);

/**
 * 此函数指示SRP服务是否为子类型。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  如果服务是子类型，则为TRUE；如果不是，则为FALSE。
 *
 */
bool otSrpServerServiceIsSubType(const otSrpServerService *aService);

/**
 * 此函数返回服务的完整服务实例名称。
 *
 * @note 此函数已被弃用，将被删除`可以改用otSrpServerServiceGetInstanceName（）`。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  指向以空结尾的服务实例名称字符串的指针。
 *
 */
const char *otSrpServerServiceGetFullName(const otSrpServerService *aService);

/**
 * 此函数返回服务的完整服务实例名称。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  指向以空结尾的服务实例名称字符串的指针。
 *
 */
const char *otSrpServerServiceGetInstanceName(const otSrpServerService *aService);

/**
 * 此函数返回服务的完整服务名称。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  指向以空结尾的服务名称字符串的指针。
 *
 */
const char *otSrpServerServiceGetServiceName(const otSrpServerService *aService);

/**
 * 此函数从服务名称获取子类型标签。
 *
 * This function is intended to be used when the @p aService是子类型，即服务的“otSrpServerServiceIsSubType（）”返回TRUE。如果不是子类型，则此函数返回`OT_ERROR_INVALID_ARGS`。
 *
 * 子类型服务的完整服务名称在“<sublabel>.sub.<servicelabel>.<domain>.”之后。此函数将“＜sub label＞”复制到@p aLabel缓冲区中。
 *
 * The @p aLabel确保在返回后始终为空终止，即使在失败的情况下也是如此。
 *
 * @param[in]  aService           指向SRP服务的指针。
 * @param[out] aLabel             指向要将子类型标签名称复制到其中的缓冲区的指针。
 * @param[in]  aMaxSize           @p aLabel缓冲区的最大大小。
 *
 * @retval OT_ERROR_NONE@p aLabel已成功更新。
 * @retval OT_ERROR_NO_BUFS子类型标签无法容纳在@p aLabel缓冲区中（可以容纳的标签中的字符数将复制到@p aLabel中，以确保其以空结尾）。
 * @retval OT_ERROR_INVALID_ARGS SRP服务不是子类型。
 *
 */
otError otSrpServerServiceGetServiceSubTypeLabel(const otSrpServerService *aService, char *aLabel, uint8_t aMaxSize);

/**
 * 此函数返回服务实例的端口。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  服务的端口。
 *
 */
uint16_t otSrpServerServiceGetPort(const otSrpServerService *aService);

/**
 * 此函数返回服务实例的权重。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  服务的重量。
 *
 */
uint16_t otSrpServerServiceGetWeight(const otSrpServerService *aService);

/**
 * 此函数返回服务实例的优先级。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  服务的优先级。
 *
 */
uint16_t otSrpServerServiceGetPriority(const otSrpServerService *aService);

/**
 * 此函数返回服务实例的TXT记录数据。
 *
 * @param[in]  aService        指向SRP服务的指针。
 * @param[out] aDataLength     返回TXT记录数据长度的指针。不得为空。
 *
 * @returns 指向包含TXT记录数据的缓冲区的指针（TXT数据长度以@p aDataLength返回）。
 *
 */
const uint8_t *otSrpServerServiceGetTxtData(const otSrpServerService *aService, uint16_t *aDataLength);

/**
 * 此函数返回服务实例所在的主机。
 *
 * @param[in]  aService  指向SRP服务的指针。
 *
 * @returns  指向主机实例的指针。
 *
 */
const otSrpServerHost *otSrpServerServiceGetHost(const otSrpServerService *aService);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_SRP_SERVER_H_

