/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义了DNS-SD服务器API。
 */

#ifndef OPENTHREAD_DNSSD_SERVER_H_
#define OPENTHREAD_DNSSD_SERVER_H_

#include <stdint.h>

#include <openthread/dns.h>
#include <openthread/error.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api dnssd服务器
 *
 * @brief 该模块包括用于DNS-SD服务器的API。
 *
 * @{
 *
 */

/**
 * 当DNS-SD查询订阅以下之一时调用此函数：1.服务名称。2.服务实例名称。3.主机名。
 *
 * DNS-SD查询实现负责识别@p aFullName是什么。
 * If @p aFullName是服务名称或服务实例名称，DNS-SD查询实现应发现相应的服务实例信息，并使用“otDnssdQueryHandleDiscoveredServiceInstance”通知DNS-SD服务器。
 * If @p aFullName是主机名，DNS-SD查询实现应发现主机信息，并使用“otDnssdQueryHandleDiscoveredHost”通知DNS-SD服务器。
 *
 * @note 可以对同一名称进行多个订阅。DNS-SD查询实现应记录活动订阅的数量，并在@p aFullName没有活动订阅时停止通知。
 *
 * @param[in] aContext      指向应用程序特定上下文的指针。
 * @param[in] aFullName     以空结尾的完整服务名称（例如“_ipps._tcp.default.service.arpa”）、完整服务实例名称（例如，“OpenThread.ipps._tcp.default.server.arpa。”）或完整主机名称（例如：“ot-host.default.serve.arpa”）。
 *
 * @sa otDnssdQueryHandleDiscoveredServiceInstance
 * @sa otDnssdQueryHandleDiscoveredHost
 *
 */
typedef void (*otDnssdQuerySubscribeCallback)(void *aContext, const char *aFullName);

/**
 * 当DNS-SD查询取消订阅以下之一时调用此函数：1.服务名称。2.服务实例名称。3.主机名。
 *
 * DNS-SD查询实现负责识别@p aFullName是什么。
 *
 * @note 可以对同一名称进行多个订阅。DNS-SD查询实现应记录活动订阅的数量，并在@p aFullName没有活动订阅时停止通知。
 *
 * @param[in] aContext      指向应用程序特定上下文的指针。
 * @param[in] aFullName     以空结尾的完整服务名称（例如“_ipps._tcp.default.service.arpa.”）或完整服务实例名称（例如，“OpenThread.ipps._tcp.default.server.arpa”）。
 *
 */
typedef void (*otDnssdQueryUnsubscribeCallback)(void *aContext, const char *aFullName);

/**
 * 此不透明类型表示DNS-SD查询。
 *
 */
typedef void otDnssdQuery;

/**
 * 此结构表示DNS-SD查询的已发现服务实例的信息。
 *
 */
typedef struct otDnssdServiceInstanceInfo
{
    const char *        mFullName;   ///<完整实例名称（例如“OpenThread.ipps._tcp.default.service.arpa”）。
    const char *        mHostName;   ///<主机名（例如“othost.default.service.arpa”）。
    uint8_t             mAddressNum; ///<主机IPv6地址数。
    const otIp6Address *mAddresses;  ///<主机IPv6地址。
    uint16_t            mPort;       ///<服务端口。
    uint16_t            mPriority;   ///<服务优先级。
    uint16_t            mWeight;     ///<服务重量。
    uint16_t            mTxtLength;  ///<服务TXT RDATA长度。
    const uint8_t *     mTxtData;    ///<服务TXT RDATA。
    uint32_t            mTtl;        ///<服务TTL（秒）。
} otDnssdServiceInstanceInfo;

/**
 * 此结构表示DNS-SD查询的已发现主机的信息。
 *
 */
typedef struct otDnssdHostInfo
{
    uint8_t             mAddressNum; ///<主机IPv6地址数。
    const otIp6Address *mAddresses;  ///<主机IPv6地址。
    uint32_t            mTtl;        ///<服务TTL（秒）。
} otDnssdHostInfo;

/**
 * 此枚举指定DNS-SD查询类型。
 *
 */
typedef enum
{
    OT_DNSSD_QUERY_TYPE_NONE         = 0, ///<未指定服务类型。
    OT_DNSSD_QUERY_TYPE_BROWSE       = 1, ///<服务类型浏览服务。
    OT_DNSSD_QUERY_TYPE_RESOLVE      = 2, ///<服务类型解析服务实例。
    OT_DNSSD_QUERY_TYPE_RESOLVE_HOST = 3, ///<服务类型解析主机名。
} otDnssdQueryType;

/**
 * 此函数设置DNS-SD服务器查询回调。
 *
 * The DNS-SD server calls @p a订阅以订阅服务或服务实例以解析DNS-SD查询，而@p a取消订阅以在解析查询或超时时取消订阅。
 *
 * @note @p a订阅和@p a取消订阅必须同时设置或取消设置。
 *
 * @param[in] aInstance     OpenThread实例结构。
 * @param[in] aSubscribe    指向用于订阅服务或服务实例的回调函数的指针。
 * @param[in] aUnsubscribe  用于取消订阅服务或服务实例的回调函数的指针。
 * @param[in] aContext      指向应用程序特定上下文的指针。
 *
 */
void otDnssdQuerySetCallbacks(otInstance *                    aInstance,
                              otDnssdQuerySubscribeCallback   aSubscribe,
                              otDnssdQueryUnsubscribeCallback aUnsubscribe,
                              void *                          aContext);

/**
 * 此函数通知发现的服务实例。
 *
 * 外部查询解析器（例如发现代理）应调用此函数以通知OpenThread核心订阅的服务或服务实例。
 *
 * @note @p aInstanceInfo不能包含未指定的或链接的本地或环回或多播IP地址。
 *
 * @param[in] aInstance         OpenThread实例结构。
 * @param[in] aServiceFullName  以null结尾的完整服务名称。
 * @param[in] aInstanceInfo     指向发现的服务实例信息的指针。
 *
 */
void otDnssdQueryHandleDiscoveredServiceInstance(otInstance *                aInstance,
                                                 const char *                aServiceFullName,
                                                 otDnssdServiceInstanceInfo *aInstanceInfo);
/**
 * 此函数用于通知发现的主机。
 *
 * 外部查询解析器（例如发现代理）应调用此函数以通知OpenThread核心订阅的主机。
 *
 * @note @p aHostInfo不能包含未指定的或链接的本地或环回或多播IP地址。
 *
 * @param[in] aInstance         OpenThread实例结构。
 * @param[in] aHostFullName     以空结尾的完整主机名。
 * @param[in] aHostInfo         指向发现的服务实例信息的指针。
 *
 */
void otDnssdQueryHandleDiscoveredHost(otInstance *aInstance, const char *aHostFullName, otDnssdHostInfo *aHostInfo);

/**
 * 此函数获取DNS-SD服务器中的下一个查询。
 *
 * @param[in] aInstance         OpenThread实例结构。
 * @param[in] aQuery            查询指针。传递NULL以获取第一个查询。
 *
 * @returns  指向查询的指针，如果没有更多查询，则返回NULL。
 *
 */
const otDnssdQuery *otDnssdGetNextQuery(otInstance *aInstance, const otDnssdQuery *aQuery);

/**
 * 此函数获取特定查询的DNS-SD查询类型和名称。
 *
 * @param[in]   aQuery            从“otDnssdGetNextQuery”获取的查询指针。
 * @param[out]  aNameOutput       名称输出缓冲区，长度应为`OT_DNS_MAX_name_SIZE`字节。
 *
 * @returns DNS-SD查询类型。
 *
 */
otDnssdQueryType otDnssdGetQueryTypeAndName(const otDnssdQuery *aQuery, char (*aNameOutput)[OT_DNS_MAX_NAME_SIZE]);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_DNSSD_SERVER_H_

