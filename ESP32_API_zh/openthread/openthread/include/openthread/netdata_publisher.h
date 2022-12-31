/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread Network Data Publisher API。
 */

#ifndef OPENTHREAD_NETDATA_PUBLISHER_H_
#define OPENTHREAD_NETDATA_PUBLISHER_H_

#include <openthread/netdata.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api线程常规
 *
 * @{
 *
 * 网络数据发布器通过监控网络数据并管理是否或何时添加或删除条目，提供了限制线程网络数据中类似服务和/或前缀（网格前缀或外部路由）条目数量的机制。
 *
 * 此模块中的所有功能都需要启用“OPENTHREAD_CONFIG_NETDATA_PUBLISHER_ENABLE”。
 *
 */

/**
 * 此枚举表示从发布服务器回调报告的事件。
 *
 */
typedef enum otNetDataPublisherEvent
{
    OT_NETDATA_PUBLISHER_EVENT_ENTRY_ADDED   = 0, ///<已发布条目将添加到线程网络数据。
    OT_NETDATA_PUBLISHER_EVENT_ENTRY_REMOVED = 1, ///<已发布条目将从线程网络数据中删除。
} otNetDataPublisherEvent;

/**
 * 此函数指针类型定义了用于通知何时将“DNS/SRP服务”条目添加到线程网络数据或从中删除的回调。
 *
 * 在删除时，无论是通过“Publisher”删除条目（例如，当网络数据中已有太多类似条目时）还是通过显式调用取消发布条目（例如调用“otNetDataUnpublishDnsSrpService（）”），都会调用回调。
 *
 * @param[in] aEvent     指示事件（是否添加或删除条目）。
 * @param[in] aContext   指向应用程序特定上下文的指针。
 *
 */
typedef void (*otNetDataDnsSrpServicePublisherCallback)(otNetDataPublisherEvent aEvent, void *aContext);

/**
 * 此函数指针类型定义了用于通知何时将前缀（网格或外部路由上）条目添加到线程网络数据或从线程网络数据中删除前缀的回调。
 *
 * 在删除时，调用回调，而不管该条目是由“Publisher”删除（例如，当网络数据中已有太多类似条目时），还是通过显式调用取消发布该条目。
 *
 * @param[in] aEvent     指示事件（是否添加或删除条目）。
 * @param[in] aPrefix    指向前缀项的指针。
 * @param[in] aContext   指向应用程序特定上下文的指针。
 *
 */
typedef void (*otNetDataPrefixPublisherCallback)(otNetDataPublisherEvent aEvent,
                                                 const otIp6Prefix *     aPrefix,
                                                 void *                  aContext);

/**
 * 此函数请求在线程网络数据中发布“DNS/SRP服务选播地址”。
 *
 * 此函数要求启用功能`OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE`。
 *
 * 对该函数的调用将删除并替换以前发布的任何“DNS/SRP服务”条目（从以前对任何`otNetDataPublishDnsSrpService｛Type｝（）`函数的调用）。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aSequenceNUmber  DNS/SRP Anycast服务的序列号。
 *
 */
void otNetDataPublishDnsSrpServiceAnycast(otInstance *aInstance, uint8_t aSequenceNUmber);

/**
 * 此函数请求在线程网络数据中发布“DNS/SRP服务单播地址”。
 *
 * 此函数要求启用功能`OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE`。
 *
 * 对该函数的调用将删除并替换以前发布的任何“DNS/SRP服务”条目（从以前对任何`otNetDataPublishDnsSrpService｛Type｝（）`函数的调用）。
 *
 * 此函数通过在服务TLV数据中包含地址和端口信息来发布“DNS/SRP服务单播地址”。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aAddress   要发布的DNS/SRP服务器地址（不得为空）。
 * @param[in] aPort      要发布的SRP服务器端口号。
 *
 */
void otNetDataPublishDnsSrpServiceUnicast(otInstance *aInstance, const otIp6Address *aAddress, uint16_t aPort);

/**
 * 此函数请求在线程网络数据中发布“DNS/SRP服务单播地址”。
 *
 * 此函数要求启用功能`OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE`。
 *
 * 对该函数的调用将删除并替换以前发布的任何“DNS/SRP服务”条目（从以前对任何`otNetDataPublishDnsSrpService｛Type｝（）`函数的调用）。
 *
 * 与“otNetDataPublishDnsSrpServiceUnicast（）”不同，该函数要求提供已发布的地址并将信息包含在服务TLV数据中，该函数使用设备的网格本地EID并将信息包括在服务器TLV数据。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aPort      要发布的SRP服务器端口号。
 *
 */
void otNetDataPublishDnsSrpServiceUnicastMeshLocalEid(otInstance *aInstance, uint16_t aPort);

/**
 * 此函数指示当前是否将“DNS/SRP服务”条目添加到线程网络数据中。
 *
 * 此函数要求启用功能`OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE`。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @retval TRUE已发布的DNS/SRP服务条目将添加到线程网络数据中。
 * @retval FALSE该条目不会添加到“线程网络数据”中，或者没有要发布的条目。
 *
 */
bool otNetDataIsDnsSrpServiceAdded(otInstance *aInstance);

/**
 * 此函数设置一个回调，用于通知发布的“DNS/SRP服务”何时实际添加到线程网络数据中或从中删除。
 *
 * 对该函数的后续调用将替换之前设置的任何回调函数。
 *
 * 此函数要求启用功能`OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE`。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aCallback        回调函数指针（如果不需要，可以为NULL）。
 * @param[in] aContext         指向应用程序特定上下文的指针（在调用@p aCallback时使用）。
 *
 */
void otNetDataSetDnsSrpServicePublisherCallback(otInstance *                            aInstance,
                                                otNetDataDnsSrpServicePublisherCallback aCallback,
                                                void *                                  aContext);

/**
 * 此函数用于从线程网络数据中取消发布以前添加的任何“DNS/SRP（Anycast或Unicast）Service”条目。
 *
 * 此函数要求启用功能`OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE`。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 */
void otNetDataUnpublishDnsSrpService(otInstance *aInstance);

/**
 * 此函数请求在线程网络数据中发布网格上前缀。
 *
 * 此功能要求启用功能“OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE”。
 *
 * 只能发布稳定的条目（即，“aConfig.mStable”必须为TRUE）。
 *
 * @param[in] aInstance           指向OpenThread实例的指针。
 * @param[in] aConfig             要发布的网格前缀配置（不得为空）。
 *
 * @retval OT_ERROR_NONE已成功发布网格前缀。
 * @retval OT_ERROR_INVALID_ARGS@p aConfig无效（前缀错误、标志组合无效或不稳定）。
 * @retval OT_ERROR_ALREADY具有相同前缀的条目已在发布列表中。
 * @retval OT_ERROR_NO_BUFS无法为新请求分配条目。Publisher支持由配置`OPENTHREAD_config_NETDATA_Publisher_MAX_prefix_entries`确定的有限数量的条目（在网格前缀和外部路由之间共享）。
 *
 *
 */
otError otNetDataPublishOnMeshPrefix(otInstance *aInstance, const otBorderRouterConfig *aConfig);

/**
 * 此函数请求在线程网络数据中发布外部路由前缀。
 *
 * 此功能要求启用功能“OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE”。
 *
 * 只能发布稳定的条目（即，“aConfig.mStable”必须为TRUE）。
 *
 * @param[in] aInstance           指向OpenThread实例的指针。
 * @param[in] aConfig             要发布的外部路由配置（不能为空）。
 *
 * @retval OT_ERROR_NONE已成功发布外部路由。
 * @retval OT_ERROR_INVALID_ARGS@p aConfig无效（前缀错误、标志组合无效或不稳定）。
 * @retval OT_ERROR_ALREADY具有相同前缀的条目已在发布列表中。
 * @retval OT_ERROR_NO_BUFS无法为新请求分配条目。Publisher支持由配置`OPENTHREAD_config_NETDATA_Publisher_MAX_prefix_entries`确定的有限数量的条目（在网格前缀和外部路由之间共享）。
 */
otError otNetDataPublishExternalRoute(otInstance *aInstance, const otExternalRouteConfig *aConfig);

/**
 * 此函数指示当前是否将已发布的前缀条目（网格或外部路由上）添加到“线程网络数据”中。
 *
 * 此功能要求启用功能“OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE”。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aPrefix    指向前缀的指针（不能为空）。
 *
 * @retval TRUE已发布的前缀条目将添加到“线程网络数据”中。
 * @retval FALSE该条目不会添加到“线程网络数据”中，或者没有要发布的条目。
 *
 */
bool otNetDataIsPrefixAdded(otInstance *aInstance, const otIp6Prefix *aPrefix);

/**
 * 此函数设置一个回调，用于通知何时将已发布的前缀条目实际添加到线程网络数据中或从中删除。
 *
 * 对该函数的后续调用将替换之前设置的任何回调函数。
 *
 * 此功能要求启用功能“OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE”。
 *
 * @param[in] aInstance        指向OpenThread实例的指针。
 * @param[in] aCallback        回调函数指针（如果不需要，可以为NULL）。
 * @param[in] aContext         指向应用程序特定上下文的指针（在调用@p aCallback时使用）。
 *
 */
void otNetDataSetPrefixPublisherCallback(otInstance *                     aInstance,
                                         otNetDataPrefixPublisherCallback aCallback,
                                         void *                           aContext);

/**
 * 此函数用于取消发布先前发布的前缀（在网格或外部管线上）。
 *
 * 此功能要求启用功能“OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE”。
 *
 * @param[in] aInstance          指向OpenThread实例的指针。
 * @param[in] aPrefix            要取消发布的前缀（不能为空）。
 *
 * @retval OT_ERROR_NONE前缀已成功发布。
 * @retval OT_ERROR_NOT_FOUND在已发布列表中找不到前缀。
 *
 */
otError otNetDataUnpublishPrefix(otInstance *aInstance, const otIp6Prefix *aPrefix);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_NETDATA_PUBLISHER_H_

