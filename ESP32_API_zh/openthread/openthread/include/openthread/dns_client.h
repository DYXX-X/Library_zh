/*
 *  版权所有（c）2017-2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread库的顶级DNS函数。
 */

#ifndef OPENTHREAD_DNS_CLIENT_H_
#define OPENTHREAD_DNS_CLIENT_H_

#include <openthread/dns.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api dns
 *
 * @brief 此模块包括控制DNS通信的功能。
 *
 *   仅当启用功能“OPENTHREAD_CONFIG_DNS_CLIENT_ENABLE”时，此模块中的功能才可用。
 *
 * @{
 *
 */

/**
 * 此枚举类型表示`otDnsQueryConfig`中的“Recursion Desired”（RD）标志。
 *
 */
typedef enum
{
    OT_DNS_FLAG_UNSPECIFIED       = 0, ///<表示未指定标志。
    OT_DNS_FLAG_RECURSION_DESIRED = 1, ///<表示DNS名称服务器可以递归解析查询。
    OT_DNS_FLAG_NO_RECURSION      = 2, ///<表示DNS名称服务器无法递归解析查询。
} otDnsRecursionFlag;

/**
 * 此枚举类型表示“otDnsQueryConfig”中的NAT64模式。
 *
 * NAT64模式指示在DNS客户端地址解析期间是允许还是不允许NAT64地址转换。此模式仅在启用“OPENTHREAD_CONFIG_DNS_CLIENT_NAME64_ENABLE”时使用。
 *
 */
typedef enum
{
    OT_DNS_NAT64_UNSPECIFIED = 0, ///未指定<NAT64模式。使用默认NAT64模式。
    OT_DNS_NAT64_ALLOW       = 1, ///<在DNS客户端地址解析期间允许NAT64地址转换。
    OT_DNS_NAT64_DISALLOW    = 2, ///<在DNS客户端地址解析期间不允许NAT64地址转换。
} otDnsNat64Mode;

/**
 * 此结构表示DNS查询配置。
 *
 * 此结构中的任何字段都可以设置为零，以表示未指定。未指定字段的处理方式由使用“otDnsQueryConfig”实例的函数决定。
 *
 */
typedef struct otDnsQueryConfig
{
    otSockAddr         mServerSockAddr;  ///<服务器地址（IPv6地址/端口）。未指定的全部为零或零端口。
    uint32_t           mResponseTimeout; ///<rx响应的等待时间（毫秒）。零表示未指定值。
    uint8_t            mMaxTxAttempts;   ///<报告失败前的最大tx尝试次数。未指定值为零。
    otDnsRecursionFlag mRecursionFlag;   ///<指示服务器是否可以递归解析查询。
    otDnsNat64Mode     mNat64Mode;       ///<在地址解析期间允许/不允许NAT64地址转换。
} otDnsQueryConfig;

/**
 * 此函数获取DNS客户端使用的当前默认查询配置。
 *
 * 当OpenThread堆栈启动时，默认DNS查询配置由一组OT配置选项确定，例如`OpenThread_config_DNS_CLIENT_default_SERVER_IP6_ADDRESS `、`_default_RERVER_PORT`、`default_RESPONSE_TIMEOUT`等（有关所有相关配置选项，请参阅`config/DNS_CLIENT.h `）。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 *
 * @returns 指向DNS客户端使用的当前默认配置的指针。
 *
 */
const otDnsQueryConfig *otDnsClientGetDefaultConfig(otInstance *aInstance);

/**
 * 此函数设置DNS客户端上的默认查询配置。
 *
 * @note 任何正在进行的查询将继续使用启动时的配置。新的默认配置将用于任何未来的DNS查询。
 *
 * The @p aConfig可以为空。在这种情况下，默认配置将被设置为OT配置选项“OPENTHREAD_config_DNS_CLIENT_default_{}”中的默认值。这会在OpenThread堆栈启动时将默认查询配置重置回配置。
 *
 * In a non-NULL @p aConfig，调用者可以选择不指定“otDnsQueryConfig”实例中的某些字段（值为零）。未指定的字段被相应的OT配置选项定义`OPENTHREAD_config_DNS_CLIENT_DEFAULT_{}'替换，以形成默认查询配置。
 *
 * 当启用“OPENTHREAD_CONFIG_DNS_CLIENT_DEFAULT_SERVER_ADDRESS_AUTO_SET_ENABLE”时，DNS客户端将自动设置并更新默认配置中的服务器IPv6地址。只有当用户未显式设置或指定它时，才能执行此操作。此行为要求启用SRP客户端及其自动启动功能。然后，SRP客户端将监视线程网络数据中的DNS/SRP服务条目，以选择SRP服务器。所选SRP服务器地址也在默认配置中设置为DNS服务器地址。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aConfig     指向要用作默认值的新查询配置的指针。
 *
 */
void otDnsClientSetDefaultConfig(otInstance *aInstance, const otDnsQueryConfig *aConfig);

/**
 * 此类型是对地址解析DNS查询的响应的不透明表示。
 *
 * 回调`otDnsAddressCallback`提供指向此类型实例的指针。
 *
 */
typedef struct otDnsAddressResponse otDnsAddressResponse;

/**
 * 当收到地址解析查询的DNS响应时，调用此函数指针。
 *
 * 在此回调中，用户可以使用`otDnsAddressResponseGet｛Item｝（）`函数以及@p aResponse指针来获取有关响应的详细信息。
 *
 * The @p aResponse指针只能在此回调中使用，从该函数返回后，它将不会保持有效，因此用户不得保留@p aResponse指针以供以后使用。
 *
 * @param[in]  aError     DNS事务的结果。
 * @param[in]  aResponse  指向响应的指针（总是非NULL）。
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 *
 * The @p aError可能包含以下内容：
 *
 *  -OT_ERROR_NONE成功接收到响应。
 *  -OT_ERROR_ABORT堆栈中止了DNS事务。
 *  -OT_ERROR_RESPONSE_TIMEOUT超时内未收到DNS响应。
 *
 * 如果服务器拒绝地址解析请求，则来自服务器的错误代码映射如下：
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
 */
typedef void (*otDnsAddressCallback)(otError aError, const otDnsAddressResponse *aResponse, void *aContext);

/**
 * 此函数为给定主机名发送AAAA（IPv6）记录的地址解析DNS查询。
 *
 * The @p aConfig可以为空。在这种情况下，默认配置（来自`otDnsClientGetDefaultConfig（）`）将用作
 * the config for this query. In a non-NULL @p aConfig，某些字段可以不指定（值为零）。然后，未指定的字段将被默认配置中的值替换。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aHostName        要查询其地址的主机名（不得为空）。
 * @param[in]  aCallback        响应接收或超时时应调用的函数指针。
 * @param[in]  aContext         指向任意上下文信息的指针。
 * @param[in]  aConfig          指向用于此查询的配置的指针。
 *
 * @retval OT_ERROR_NONE查询已成功发送@p将调用Callback报告状态。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法准备和发送查询。
 *
 */
otError otDnsClientResolveAddress(otInstance *            aInstance,
                                  const char *            aHostName,
                                  otDnsAddressCallback    aCallback,
                                  void *                  aContext,
                                  const otDnsQueryConfig *aConfig);

/**
 * 此函数获取与地址解析DNS响应关联的完整主机名。
 *
 * 此函数只能从“otDnsAddressCallback”中使用。
 *
 * @param[in]  aResponse         指向响应的指针。
 * @param[out] aNameBuffer       用于输出完整主机名的缓冲区到字符数组（不能为空）。
 * @param[in]  aNameBufferSize   @p aNameBuffer的大小。
 *
 * @retval OT_ERROR_NONE已成功读取完整主机名。
 * @retval OT_ERROR_NO_BUFS名称不适合@p aNameBuffer。
 *
 */
otError otDnsAddressResponseGetHostName(const otDnsAddressResponse *aResponse,
                                        char *                      aNameBuffer,
                                        uint16_t                    aNameBufferSize);

/**
 * 此函数获取与地址解析DNS响应关联的IPv6地址。
 *
 * 此函数只能从“otDnsAddressCallback”中使用。
 *
 * The response may include multiple IPv6 address records. @p 索引可用于遍历地址列表。索引0获取第一个地址，依此类推。当我们到达列表末尾时，将返回`OT_ERROR_NOT_FOUND`。
 *
 * @param[in]  aResponse     指向响应的指针。
 * @param[in]  aIndex        要检索的地址记录索引。
 * @param[out] aAddress      指向IPv6地址以输出地址的指针（不得为空）。
 * @param[out] aTtl          指向“uint32_t”的指针，用于输出该地址的TTL。如果调用者不想获取TTL，它可以为NULL。
 *
 * @retval OT_ERROR_NONE地址读取成功。
 * @retval OT_ERROR_NOT_FOUND@p aResponse中@p aIndex处没有地址记录。
 * @retval OT_ERROR_PARSE无法分析@p aResponse中的记录。
 *
 */
otError otDnsAddressResponseGetAddress(const otDnsAddressResponse *aResponse,
                                       uint16_t                    aIndex,
                                       otIp6Address *              aAddress,
                                       uint32_t *                  aTtl);

/**
 * 此类型是对浏览（服务实例枚举）DNS查询的响应的不透明表示。
 *
 * 回调`otDnsBrowseCallback`提供指向此类型实例的指针。
 *
 */
typedef struct otDnsBrowseResponse otDnsBrowseResponse;

/**
 * 当收到浏览（服务实例枚举）查询的DNS响应时，调用此函数指针。
 *
 * 在此回调中，用户可以使用`otDnsBrowseResponseGet｛Item｝（）`函数以及@p aResponse指针来获取有关响应的详细信息。
 *
 * The @p aResponse指针只能在此回调中使用，从该函数返回后，它将不会保持有效，因此用户不得保留@p aResponse指针以供以后使用。
 *
 * @param[in]  aError     DNS事务的结果。
 * @param[in]  aResponse  指向响应的指针（总是非NULL）。
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 *
 * For the full list of possible values for @p aError，请参阅`otDnsAddressCallback（）`。
 *
 */
typedef void (*otDnsBrowseCallback)(otError aError, const otDnsBrowseResponse *aResponse, void *aContext);

/**
 * 此结构提供DNS服务实例的信息。
 *
 */
typedef struct otDnsServiceInfo
{
    uint32_t     mTtl;                ///<服务记录TTL（秒）。
    uint16_t     mPort;               ///<服务端口号。
    uint16_t     mPriority;           ///<服务优先级。
    uint16_t     mWeight;             ///<服务重量。
    char *       mHostNameBuffer;     ///<输出服务主机名的缓冲区（如果不需要，可以为NULL）。
    uint16_t     mHostNameBufferSize; ///<`mHostNameBuffer`的大小。
    otIp6Address mHostAddress;        ///<主机IPv6地址。如果不可用，则设置为全零。
    uint32_t     mHostAddressTtl;     ///<主机地址TTL。
    uint8_t *    mTxtData;            ///<输出TXT数据的缓冲区（如果不需要，可以为NULL）。
    uint16_t     mTxtDataSize;        ///<输入时，“mTxtData”缓冲区的大小。输出“mTxtData”长度时。
    uint32_t     mTxtDataTtl;         ///<TXT数据TTL。
} otDnsServiceInfo;

/**
 * 此函数发送给定服务名称的DNS浏览（服务实例枚举）查询。
 *
 * 当启用“OPENTHREAD_CONFIG_DNS_CLIENT_SERVICE_DISCOVERY_ENABLE”时，此功能可用。
 *
 * The @p aConfig可以为空。在这种情况下，默认配置（来自`otDnsClientGetDefaultConfig（）`）将用作
 * the config for this query. In a non-NULL @p aConfig，某些字段可以不指定（值为零）。然后，未指定的字段将被默认配置中的值替换。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aServiceName     要查询的服务名称（不能为空）。
 * @param[in]  aCallback        响应接收或超时时应调用的函数指针。
 * @param[in]  aContext         指向任意上下文信息的指针。
 * @param[in]  aConfig          指向用于此查询的配置的指针。
 *
 * @retval OT_ERROR_NONE查询已成功发送@p将调用Callback报告状态。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法准备和发送查询。
 *
 */
otError otDnsClientBrowse(otInstance *            aInstance,
                          const char *            aServiceName,
                          otDnsBrowseCallback     aCallback,
                          void *                  aContext,
                          const otDnsQueryConfig *aConfig);

/**
 * 此函数获取与DNS浏览（服务实例枚举）响应关联的服务名称。
 *
 * 此函数只能在`otDnsBrowseCallback`中使用。
 *
 * @param[in]  aResponse         指向响应的指针。
 * @param[out] aNameBuffer       用于输出服务名称的缓冲区到字符数组（不能为空）。
 * @param[in]  aNameBufferSize   @p aNameBuffer的大小。
 *
 * @retval OT_ERROR_NONE已成功读取服务名称。
 * @retval OT_ERROR_NO_BUFS名称不适合@p aNameBuffer。
 *
 */
otError otDnsBrowseResponseGetServiceName(const otDnsBrowseResponse *aResponse,
                                          char *                     aNameBuffer,
                                          uint16_t                   aNameBufferSize);

/**
 * 此函数获取与DNS浏览（服务实例枚举）响应关联的服务实例。
 *
 * 此函数只能在`otDnsBrowseCallback`中使用。
 *
 * The response may include multiple service instance records. @p 索引可用于遍历列表。索引零给出第一条记录。当我们到达列表末尾时，将返回`OT_ERROR_NOT_FOUND`。
 *
 * 请注意，此函数获取服务实例标签，而不是完整的服务实例名称，其格式为“＜实例＞.＜服务＞.＜域＞”。
 *
 * @param[in]  aResponse          指向响应的指针。
 * @param[in]  aIndex             要检索的服务实例记录索引。
 * @param[out] aLabelBuffer       用于输出服务实例标签的缓冲区到字符数组（不能为空）。
 * @param[in]  aLabelBufferSize   @p aLabelBuffer的大小。
 *
 * @retval OT_ERROR_NONE已成功读取服务实例。
 * @retval OT_ERROR_NO_BUFS名称不适合@p aNameBuffer。
 * @retval OT_ERROR_NOT_FOUND@p aResponse中@p aIndex处没有服务实例记录。
 * @retval OT_ERROR_PARSE无法分析@p aResponse中的记录。
 *
 */
otError otDnsBrowseResponseGetServiceInstance(const otDnsBrowseResponse *aResponse,
                                              uint16_t                   aIndex,
                                              char *                     aLabelBuffer,
                                              uint8_t                    aLabelBufferSize);

/**
 * 此函数从DNS浏览（服务实例枚举）响应中获取服务实例的信息。
 *
 * 此函数只能在`otDnsBrowseCallback`中使用。
 *
 * 浏览DNS响应应包括枚举的服务实例的SRV、TXT和AAAA记录（请注意，这是“应该”而不是“必须”要求）。此函数尝试在可用时检索给定服务实例的此信息。
 *
 * - If no matching SRV record is found in @p aResponse，`OT_ERROR_NOT_FOUND`被返回。
 * - If a matching SRV record is found in @p aResponse，@p aServiceInfo被更新，并返回`OT_ERROR_NONE`。
 * - If no matching TXT record is found in @p aResponse，@p aServiceInfo中的`mTxtDataSize`设置为零。
 * - If no matching AAAA record is found in @p aResponse，`mHostAddress设置为全零或未指定地址。
 * - If there are multiple AAAA records for the host name in @p aResponse，`mHostAddress`设置为第一个。可以使用“otDnsBrowseResponseGetHostAddress（）”检索其他地址。
 *
 * @param[in]  aResponse          指向响应的指针。
 * @param[in]  aInstanceLabel     服务实例标签（不得为空）。
 * @param[out] aServiceInfo       用于输出服务实例信息的“ServiceInfo”（不能为空）。
 *
 * @retval OT_ERROR_NONE已读取服务实例信息@p aServiceInfo已更新。
 * @retval OT_ERROR_NOT_FOUND找不到@p aInstanceLabel的匹配SRV记录。
 * @retval OT_ERROR_NO_BUFS主机名和/或TXT数据无法容纳在给定的缓冲区中。
 * @retval OT_ERROR_PARSE无法分析@p aResponse中的记录。
 *
 */
otError otDnsBrowseResponseGetServiceInfo(const otDnsBrowseResponse *aResponse,
                                          const char *               aInstanceLabel,
                                          otDnsServiceInfo *         aServiceInfo);

/**
 * 此函数从DNS浏览（服务实例枚举）响应中获取主机IPv6地址。
 *
 * 此函数只能在`otDnsBrowseCallback`中使用。
 *
 * The response can include zero or more IPv6 address records. @p 索引可用于遍历地址列表。索引0获取第一个地址，依此类推。当我们到达列表末尾时，将返回`OT_ERROR_NOT_FOUND`。
 *
 * @param[in]  aResponse     指向响应的指针。
 * @param[in]  aHostName     获取地址的主机名（不得为空）。
 * @param[in]  aIndex        要检索的地址记录索引。
 * @param[out] aAddress      指向IPv6地址以输出地址的指针（不得为空）。
 * @param[out] aTtl          指向“uint32_t”的指针，用于输出该地址的TTL。如果调用者不想获取TTL，它可以为NULL。
 *
 * @retval OT_ERROR_NONE地址读取成功。
 * @retval OT_ERROR_NOT_FOUND在@p aIndex的@p aResponse中没有@p aHostname的地址记录。
 * @retval OT_ERROR_PARSE无法分析@p aResponse中的记录。
 *
 */
otError otDnsBrowseResponseGetHostAddress(const otDnsBrowseResponse *aResponse,
                                          const char *               aHostName,
                                          uint16_t                   aIndex,
                                          otIp6Address *             aAddress,
                                          uint32_t *                 aTtl);

/**
 * 此类型是对服务实例解析DNS查询的响应的不透明表示。
 *
 * 回调`otDnsAddressCallback`提供指向此类型实例的指针。
 *
 */
typedef struct otDnsServiceResponse otDnsServiceResponse;

/**
 * 当收到服务实例解析查询的DNS响应时，调用此函数指针。
 *
 * 在此回调中，用户可以使用`otDnsServiceResponseGet｛Item｝（）`函数以及@p aResponse指针来获取有关响应的详细信息。
 *
 * The @p aResponse指针只能在此回调中使用，从该函数返回后，它将不会保持有效，因此用户不得保留@p aResponse指针以供以后使用。
 *
 * @param[in]  aError     DNS事务的结果。
 * @param[in]  aResponse  指向响应的指针（总是非NULL）。
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 *
 * For the full list of possible values for @p aError，请参阅`otDnsAddressCallback（）`。
 *
 */
typedef void (*otDnsServiceCallback)(otError aError, const otDnsServiceResponse *aResponse, void *aContext);

/**
 * 此函数为给定服务实例发送DNS服务实例解析查询。
 *
 * 当启用“OPENTHREAD_CONFIG_DNS_CLIENT_SERVICE_DISCOVERY_ENABLE”时，此功能可用。
 *
 * The @p aConfig可以为空。在这种情况下，默认配置（来自`otDnsClientGetDefaultConfig（）`）将用作
 * the config for this query. In a non-NULL @p aConfig，某些字段可以不指定（值为零）。然后，未指定的字段将被默认配置中的值替换。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aInstanceLabel     服务实例标签。
 * @param[in]  aServiceName       服务名称（与@p aInstanceLabel一起形成完整的实例名称）。
 * @param[in]  aCallback          响应接收或超时时应调用的函数指针。
 * @param[in]  aContext           指向任意上下文信息的指针。
 * @param[in]  aConfig            指向用于此查询的配置的指针。
 *
 * @retval OT_ERROR_NONE查询已成功发送@p将调用Callback报告状态。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法准备和发送查询。
 * @retval OT_ERROR_INVALID_ARGS@p aInstanceLabel为空。
 *
 */
otError otDnsClientResolveService(otInstance *            aInstance,
                                  const char *            aInstanceLabel,
                                  const char *            aServiceName,
                                  otDnsServiceCallback    aCallback,
                                  void *                  aContext,
                                  const otDnsQueryConfig *aConfig);

/**
 * 此函数获取与DNS服务实例解析响应关联的服务实例名称。
 *
 * 此函数只能从“otDnsServiceCallback”中使用。
 *
 * @param[in]  aResponse         指向响应的指针。
 * @param[out] aLabelBuffer      用于输出服务实例标签的缓冲区到字符数组（不能为空）。
 * @param[in]  aLabelBufferSize  @p aLabelBuffer的大小。
 * @param[out] aNameBuffer       一个缓冲区到字符数组，用于输出服务名称的其余部分（如果用户对获取名称不感兴趣，则可以为NULL）。
 * @param[in]  aNameBufferSize   @p aNameBuffer的大小。
 *
 * @retval OT_ERROR_NONE已成功读取服务名称。
 * @retval OT_ERROR_NO_BUFS标签或名称不适合给定的缓冲区。
 *
 */
otError otDnsServiceResponseGetServiceName(const otDnsServiceResponse *aResponse,
                                           char *                      aLabelBuffer,
                                           uint8_t                     aLabelBufferSize,
                                           char *                      aNameBuffer,
                                           uint16_t                    aNameBufferSize);

/**
 * 此函数从DNS服务实例解析响应中获取服务实例的信息。
 *
 * 此函数只能从“otDnsServiceCallback”中使用。
 *
 * - If no matching SRV record is found in @p aResponse，`OT_ERROR_NOT_FOUND`被返回。
 * - If a matching SRV record is found in @p aResponse，@p aServiceInfo被更新，并返回`OT_ERROR_NONE`。
 * - If no matching TXT record is found in @p aResponse，@p aServiceInfo中的`mTxtDataSize`设置为零。
 * - If no matching AAAA record is found in @p aResponse，`mHostAddress设置为全零或未指定地址。
 * - If there are multiple AAAA records for the host name in @p aResponse，`mHostAddress`设置为第一个。可以使用“otDnsServiceResponseGetHostAddress（）”检索其他地址。
 *
 * @param[in]  aResponse          指向响应的指针。
 * @param[out] aServiceInfo       用于输出服务实例信息的“ServiceInfo”（不能为空）。
 *
 * @retval OT_ERROR_NONE已读取服务实例信息@p aServiceInfo已更新。
 * @retval OT_ERROR_NOT_FOUND在@p aResponse中找不到匹配的SRV记录。
 * @retval OT_ERROR_NO_BUFS主机名和/或TXT数据无法容纳在给定的缓冲区中。
 * @retval OT_ERROR_PARSE无法分析@p aResponse中的记录。
 *
 */
otError otDnsServiceResponseGetServiceInfo(const otDnsServiceResponse *aResponse, otDnsServiceInfo *aServiceInfo);

/**
 * 此函数从DNS服务实例解析响应中获取主机IPv6地址。
 *
 * 此函数只能从“otDnsServiceCallback”中使用。
 *
 * The response can include zero or more IPv6 address records. @p 索引可用于遍历地址列表。索引0获取第一个地址，依此类推。当我们到达列表末尾时，将返回`OT_ERROR_NOT_FOUND`。
 *
 * @param[in]  aResponse     指向响应的指针。
 * @param[in]  aHostName     获取地址的主机名（不得为空）。
 * @param[in]  aIndex        要检索的地址记录索引。
 * @param[out] aAddress      指向IPv6地址以输出地址的指针（不得为空）。
 * @param[out] aTtl          指向“uint32_t”的指针，用于输出该地址的TTL。如果调用者不想获取TTL，它可以为NULL。
 *
 * @retval OT_ERROR_NONE地址读取成功。
 * @retval OT_ERROR_NOT_FOUND在@p aIndex的@p aResponse中没有@p aHostname的地址记录。
 * @retval OT_ERROR_PARSE无法分析@p aResponse中的记录。
 *
 */
otError otDnsServiceResponseGetHostAddress(const otDnsServiceResponse *aResponse,
                                           const char *                aHostName,
                                           uint16_t                    aIndex,
                                           otIp6Address *              aAddress,
                                           uint32_t *                  aTtl);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_DNS_CLIENT_H_

