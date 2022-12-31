/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread骨干路由器API（用于带有`OpenThread_CONFIG_Backbone_Router_ENABLE`的线程1.2 FTD）。
 *
 */

#ifndef OPENTHREAD_BACKBONE_ROUTER_FTD_H_
#define OPENTHREAD_BACKBONE_ROUTER_FTD_H_

#include <openthread/backbone_router.h>
#include <openthread/ip6.h>
#include <openthread/netdata.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api骨干路由器
 *
 * @{
 *
 */

/**
 * 表示骨干路由器状态。
 *
 */
typedef enum
{
    OT_BACKBONE_ROUTER_STATE_DISABLED  = 0, ///<骨干功能已禁用。
    OT_BACKBONE_ROUTER_STATE_SECONDARY = 1, ///<辅助骨干路由器。
    OT_BACKBONE_ROUTER_STATE_PRIMARY   = 2, ///<主骨干路由器。
} otBackboneRouterState;

/**
 * 此功能启用或禁用主干功能。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 * @param[in] aEnable   TRUE表示启用主干功能，否则为FALSE。
 *
 * @sa otBackbone路由器获取状态
 * @sa otBackbone路由器获取配置
 * @sa otBackboneRouterSet配置
 * @sa otBackbone路由器注册器
 *
 */
void otBackboneRouterSetEnabled(otInstance *aInstance, bool aEnable);

/**
 * 此函数获取骨干路由器状态。
 *
 * @param[in] aInstance       指向OpenThread实例的指针。
 *
 * @retval OT_BACKBONE_ROUTER_STATE_DISABLED骨干功能已禁用。
 * @retval OT_BACKBONE_ROUTER_STATE_SECONDARY辅助骨干路由器。
 * @retval OT_BACKBONE_ROUTER_STATE_PRIMARY主骨干路由器。
 *
 * @sa otBackboneRouterSet已启用
 * @sa otBackbone路由器获取配置
 * @sa otBackboneRouterSet配置
 * @sa otBackbone路由器注册器
 *
 */
otBackboneRouterState otBackboneRouterGetState(otInstance *aInstance);

/**
 * 此函数获取本地骨干路由器配置。
 *
 * @param[in]   aInstance            指向OpenThread实例的指针。
 * @param[out]  aConfig              放置本地骨干路由器配置的指针。
 *
 *
 * @sa otBackboneRouterSet已启用
 * @sa otBackbone路由器获取状态
 * @sa otBackboneRouterSet配置
 * @sa otBackbone路由器注册器
 *
 */
void otBackboneRouterGetConfig(otInstance *aInstance, otBackboneRouterConfig *aConfig);

/**
 * 此功能设置本地骨干路由器配置。
 *
 * @param[in]  aInstance             指向OpenThread实例的指针。
 * @param[in]  aConfig               指向要生效的骨干路由器配置的指针。
 *
 * @retval OT_ERROR_NONE已成功更新配置。
 * @retval OT_ERROR_INVALID_ARGS@p aConfig中的配置无效。
 *
 * @sa otBackboneRouterSet已启用
 * @sa otBackbone路由器获取状态
 * @sa otBackbone路由器获取配置
 * @sa otBackbone路由器注册器
 *
 */
otError otBackboneRouterSetConfig(otInstance *aInstance, const otBackboneRouterConfig *aConfig);

/**
 * 此函数显式注册本地骨干路由器配置。
 *
 * @param[in]  aInstance             指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NO_BUFS空间不足，无法添加骨干路由器服务。
 * @retval OT_ERROR_NONE已成功将服务器数据请求消息排队等待传递。
 *
 * @sa otBackboneRouterSet已启用
 * @sa otBackbone路由器获取状态
 * @sa otBackbone路由器获取配置
 * @sa otBackboneRouterSet配置
 *
 */
otError otBackboneRouterRegister(otInstance *aInstance);

/**
 * 此方法返回骨干路由器注册抖动值。
 *
 * @returns 骨干路由器注册抖动值。
 *
 * @sa otBackboneRouterSet注册抖动
 *
 */
uint8_t otBackboneRouterGetRegistrationJitter(otInstance *aInstance);

/**
 * 此方法设置骨干路由器注册抖动值。
 *
 * @param[in]  aJitter 要设置的骨干路由器注册抖动值。
 *
 * @sa otBackbone路由器获取注册抖动
 *
 */
void otBackboneRouterSetRegistrationJitter(otInstance *aInstance, uint8_t aJitter);

/**
 * 此方法获取本地域前缀配置。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[out] aConfig   指向域前缀配置的指针。
 *
 * @retval OT_ERROR_NONE已成功获取域前缀配置。
 * @retval OT_ERROR_NOT_FOUND未配置域前缀。
 *
 */
otError otBackboneRouterGetDomainPrefix(otInstance *aInstance, otBorderRouterConfig *aConfig);

/**
 * 此方法为下一个DUA注册配置响应状态。
 *
 * 注意：仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。仅用于测试和认证。
 *
 * TODO:（DUA）支持coap错误代码和用于认证的相应过程。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 * @param[in] aMlIid    指向网格本地IID的指针。如果为NULL，则对任何即将到来的DUA使用@p aStatus进行响应。req，否则只响应带有匹配的@p aMlIid的请求。
 * @param[in] aStatus   要响应的状态。
 *
 *
 */
void otBackboneRouterConfigNextDuaRegistrationResponse(otInstance *                    aInstance,
                                                       const otIp6InterfaceIdentifier *aMlIid,
                                                       uint8_t                         aStatus);

/**
 * 此方法为下一个多播侦听器注册配置响应状态。
 *
 * 注意：仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。仅用于测试和认证。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aStatus    要响应的状态。
 *
 */
void otBackboneRouterConfigNextMulticastListenerRegistrationResponse(otInstance *aInstance, uint8_t aStatus);

/**
 * 表示多播侦听器事件。
 *
 */
typedef enum
{
    OT_BACKBONE_ROUTER_MULTICAST_LISTENER_ADDED   = 0, ///<已添加多播侦听器。
    OT_BACKBONE_ROUTER_MULTICAST_LISTENER_REMOVED = 1, ///<多播侦听器已删除或过期。
} otBackboneRouterMulticastListenerEvent;

/**
 * 每当多播侦听器发生更改时，都会调用此函数指针。
 *
 * @param[in] aContext  用户上下文指针。
 * @param[in] aEvent    多播侦听器事件。
 * @param[in] aAddress  多播侦听器的IPv6多播地址。
 *
 */
typedef void (*otBackboneRouterMulticastListenerCallback)(void *                                 aContext,
                                                          otBackboneRouterMulticastListenerEvent aEvent,
                                                          const otIp6Address *                   aAddress);

/**
 * 此方法设置骨干路由器多播侦听器回调。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aCallback  指向多播侦听器回调的指针。
 * @param[in] aContext   用户上下文指针。
 *
 */
void otBackboneRouterSetMulticastListenerCallback(otInstance *                              aInstance,
                                                  otBackboneRouterMulticastListenerCallback aCallback,
                                                  void *                                    aContext);

/**
 * 此方法清除多播侦听器。
 *
 * 注意：仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。仅用于测试和认证。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @sa otBackboneRouterMulticastListener添加
 * @sa otBackboneRouterMulticastListener获取下一个
 *
 */
void otBackboneRouterMulticastListenerClear(otInstance *aInstance);

/**
 * 此方法添加多播侦听器。
 *
 * 注意：仅在启用“OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE”时可用。仅用于测试和认证。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aAddress   多播侦听器地址。
 * @param[in] aTimeout   多播侦听器的超时（以秒为单位），或0表示使用默认MLR超时。
 *
 * @retval OT_ERROR_NONE如果已成功添加多播侦听器。
 * @retval OT_ERROR_INVALID_ARGS如果多播侦听器地址无效。
 * @retval OT_ERROR_NO_BUFS没有可用空间来保存多播侦听器。
 *
 * @sa otBackboneRouterMulticastListener清除
 * @sa otBackboneRouterMulticastListener获取下一个
 *
 */
otError otBackboneRouterMulticastListenerAdd(otInstance *aInstance, const otIp6Address *aAddress, uint32_t aTimeout);

#define OT_BACKBONE_ROUTER_MULTICAST_LISTENER_ITERATOR_INIT \
    0 ///<otBackboneRouterMulticastListenerIterator的初始化器

typedef uint16_t otBackboneRouterMulticastListenerIterator; ///<用于遍历多播侦听器。

/**
 * 此结构表示骨干路由器多播侦听器信息。
 *
 */
typedef struct otBackboneRouterMulticastListenerInfo
{
    otIp6Address mAddress; // 多播侦听器地址。
    uint32_t     mTimeout; // 超时（秒）。
} otBackboneRouterMulticastListenerInfo;

/**
 * 此函数获取下一个多播侦听器信息（使用迭代器）。
 *
 * @param[in]     aInstance    指向OpenThread实例的指针。
 * @param[inout]  aIterator    迭代器的指针。成功后，迭代器将更新为指向下一个多播侦听器。要获取第一个条目，迭代器应设置为OT_BACKBONE_ROUTER_MULTICAST_LISTENER_iterator_INIT。
 * @param[out]    aListenerInfo  指向“otBackboneRouterMulticastListenerInfo”的指针，其中放置了下一个多播侦听器的信息（成功时）。
 *
 * @retval OT_ERROR_NONE已成功找到下一个多播侦听器信息（@p aListenerInfo已成功更新）。
 * @retval OT_ERROR_NOT_FOUND未找到后续多播侦听器信息。
 *
 * @sa otBackboneRouterMulticastListener清除
 * @sa otBackboneRouterMulticastListener添加
 *
 */
otError otBackboneRouterMulticastListenerGetNext(otInstance *                               aInstance,
                                                 otBackboneRouterMulticastListenerIterator *aIterator,
                                                 otBackboneRouterMulticastListenerInfo *    aListenerInfo);

/**
 * 表示ND代理事件。
 *
 */
typedef enum
{
    OT_BACKBONE_ROUTER_NDPROXY_ADDED   = 0, ///<ND代理已添加。
    OT_BACKBONE_ROUTER_NDPROXY_REMOVED = 1, ///<ND代理已删除。
    OT_BACKBONE_ROUTER_NDPROXY_RENEWED = 2, ///<ND代理已续订。
    OT_BACKBONE_ROUTER_NDPROXY_CLEARED = 3, ///<所有ND代理均已清除。
} otBackboneRouterNdProxyEvent;

/**
 * 只要Nd代理更改，就会调用此函数指针。
 *
 * @param[in] aContext  用户上下文指针。
 * @param[in] aEvent    ND代理事件。
 * @param[in] aDua      ND代理的域单播地址，如果@p aEvent为`OT_BACKBONE_ROUTER_NDPROXY_CLEARED`，则为`nullptr`。
 *
 */
typedef void (*otBackboneRouterNdProxyCallback)(void *                       aContext,
                                                otBackboneRouterNdProxyEvent aEvent,
                                                const otIp6Address *         aDua);

/**
 * 此方法设置骨干路由器ND代理回调。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aCallback  指向ND代理回调的指针。
 * @param[in] aContext   用户上下文指针。
 *
 */
void otBackboneRouterSetNdProxyCallback(otInstance *                    aInstance,
                                        otBackboneRouterNdProxyCallback aCallback,
                                        void *                          aContext);

/**
 * 表示骨干路由器ND代理信息。
 *
 */
struct otBackboneRouterNdProxyInfo
{
    otIp6InterfaceIdentifier *mMeshLocalIid;             ///<网格局部IID
    uint32_t                  mTimeSinceLastTransaction; ///<自上次交易以来的时间（秒）
    uint16_t                  mRloc16;                   ///< RLOC16
};

/**
 * 此方法获取骨干路由器ND代理信息。
 *
 * @param[in]   aInstance     指向OpenThread实例的指针。
 * @param[in]   aDua          域单播地址。
 * @param[out]  aNdProxyInfo  指向ND代理信息的指针。
 *
 * @retval OT_ERROR_NONE成功获取ND代理信息。
 * @retval OT_ERROR_NOT_FOUND在ND代理表中找不到域单播地址。
 *
 */
otError otBackboneRouterGetNdProxyInfo(otInstance *                 aInstance,
                                       const otIp6Address *         aDua,
                                       otBackboneRouterNdProxyInfo *aNdProxyInfo);

/**
 * 表示域前缀事件。
 *
 */
typedef enum
{
    OT_BACKBONE_ROUTER_DOMAIN_PREFIX_ADDED   = 0, ///<已添加域前缀。
    OT_BACKBONE_ROUTER_DOMAIN_PREFIX_REMOVED = 1, ///<域前缀已删除。
    OT_BACKBONE_ROUTER_DOMAIN_PREFIX_CHANGED = 2, ///<域前缀已更改。
} otBackboneRouterDomainPrefixEvent;

/**
 * 每当域前缀更改时，都会调用此函数指针。
 *
 * @param[in] aContext       用户上下文指针。
 * @param[in] aEvent         域前缀事件。
 * @param[in] aDomainPrefix  如果添加或更改了新的域前缀，则为nullptr。
 *
 */
typedef void (*otBackboneRouterDomainPrefixCallback)(void *                            aContext,
                                                     otBackboneRouterDomainPrefixEvent aEvent,
                                                     const otIp6Prefix *               aDomainPrefix);
/**
 * 此方法设置骨干路由器域前缀回调。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 * @param[in] aCallback  指向域前缀回调的指针。
 * @param[in] aContext   用户上下文指针。
 *
 */
void otBackboneRouterSetDomainPrefixCallback(otInstance *                         aInstance,
                                             otBackboneRouterDomainPrefixCallback aCallback,
                                             void *                               aContext);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_BACKBONE_ROUTER_FTD_H_

