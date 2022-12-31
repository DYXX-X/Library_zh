/*
 *  版权所有（c）2016-2017，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread边界路由器API。
 */

#ifndef OPENTHREAD_BORDER_ROUTER_H_
#define OPENTHREAD_BORDER_ROUTER_H_

#include <openthread/ip6.h>
#include <openthread/netdata.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api边界路由器
 *
 * @brief 该模块包括使用OpenThread边界路由器管理本地网络数据的功能。
 *
 * @{
 *
 */

/**
 * 此方法初始化给定基础结构接口上的边界路由管理器。
 *
 * @note  必须在任何其他otBorderRouting*API之前调用此方法。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aInfraIfIndex      基础结构接口索引。
 * @param[in]  aInfraIfIsRunning  指示基础结构接口是否正在运行的布尔值。
 *
 * @retval  OT_ERROR_NONE已在给定基础结构上成功启动边界路由管理器。
 * @retval  OT_ERROR_INVALID_STATE边界路由管理器已初始化。
 * @retval  OT_ERROR_INVALID_ARGS基础结构接口的索引无效。
 * @retval  OT_ERROR_FAILED内部故障。通常是由于生成随机前缀失败。
 *
 * @sa otPlatInfraIfStateChanged。
 *
 */
otError otBorderRoutingInit(otInstance *aInstance, uint32_t aInfraIfIndex, bool aInfraIfIsRunning);

/**
 * 此方法启用/禁用边界路由管理器。
 *
 * @note  默认情况下，“边界路由管理器”处于禁用状态。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aEnabled   启用/禁用路由管理器的布尔值。
 *
 * @retval  OT_ERROR_INVALID_STATE边界路由管理器尚未初始化。
 * @retval  OT_ERROR_NONE已成功启用/禁用边界路由管理器。
 *
 */
otError otBorderRoutingSetEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此方法返回网格外可路由（OMR）前缀。
 *
 * 如果没有OMR前缀，则随机生成的64位前缀将在线程网络中发布。
 *
 * @param[in]   aInstance  指向OpenThread实例的指针。
 * @param[out]  aPrefix    指向前缀将输出到的位置的指针。
 *
 * @retval  OT_ERROR_INVALID_STATE边界路由管理器尚未初始化。
 * @retval  OT_ERROR_NONE已成功检索到OMR前缀。
 *
 */
otError otBorderRoutingGetOmrPrefix(otInstance *aInstance, otIp6Prefix *aPrefix);

/**
 * 此方法返回相邻基础结构链路的链路前缀。
 *
 * 如果尚未在链路上通告可用的链路上前缀，则将在基础设施链路上通告随机生成的64位前缀。
 *
 * @param[in]   aInstance  指向OpenThread实例的指针。
 * @param[out]  aPrefix    指向前缀将输出到的位置的指针。
 *
 * @retval  OT_ERROR_INVALID_STATE边界路由管理器尚未初始化。
 * @retval  OT_ERROR_NONE已成功检索到链接前缀。
 *
 */
otError otBorderRoutingGetOnLinkPrefix(otInstance *aInstance, otIp6Prefix *aPrefix);

/**
 * 此方法提供本地线程网络数据的完整或稳定副本。
 *
 * @param[in]     aInstance    指向OpenThread实例的指针。
 * @param[in]     aStable      复制稳定版本时为TRUE，复制完整版本时为FALSE。
 * @param[out]    aData        指向数据缓冲区的指针。
 * @param[inout]  aDataLength  输入时，@p aData指向的数据缓冲区的大小。退出时，复制的字节数。
 */
otError otBorderRouterGetNetData(otInstance *aInstance, bool aStable, uint8_t *aData, uint8_t *aDataLength);

/**
 * 将边界路由器配置添加到本地网络数据。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aConfig   指向边界路由器配置的指针。
 *
 * @retval OT_ERROR_NONE已成功将配置添加到本地网络数据。
 * @retval OT_ERROR_INVALID_ARGS一个或多个配置参数无效。
 * @retval OT_ERROR_NO_BUFS没有足够的空间将配置添加到本地网络数据。
 *
 * @sa otBorderRouterRemoveOnMeshPrefix
 * @sa otBorderRouter注册表
 */
otError otBorderRouterAddOnMeshPrefix(otInstance *aInstance, const otBorderRouterConfig *aConfig);

/**
 * 从本地网络数据中删除边界路由器配置。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aPrefix   指向IPv6前缀的指针。
 *
 * @retval OT_ERROR_NONE已成功从本地网络数据中删除配置。
 * @retval OT_ERROR_NOT_FOUND找不到边界路由器条目。
 *
 * @sa otBorderRouteAddOnMeshPrefix
 * @sa otBorderRouter注册表
 */
otError otBorderRouterRemoveOnMeshPrefix(otInstance *aInstance, const otIp6Prefix *aPrefix);

/**
 * 此函数获取本地网络数据中的下一个网格上前缀。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向网络数据迭代器上下文的指针。要获取网格上的第一个条目，应将其设置为OT_NETWORK_DATA_ITERATOR_INIT。
 * @param[out]    aConfig    指向“网格上前缀”信息的指针。
 *
 * @retval OT_ERROR_NONE已成功找到下一个网格上前缀。
 * @retval OT_ERROR_NOT_FOUND线程网络数据中不存在后续的网格上前缀。
 *
 */
otError otBorderRouterGetNextOnMeshPrefix(otInstance *           aInstance,
                                          otNetworkDataIterator *aIterator,
                                          otBorderRouterConfig * aConfig);

/**
 * 将外部路由配置添加到本地网络数据。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aConfig   指向外部路由配置的指针。
 *
 * @retval OT_ERROR_NONE已成功将配置添加到本地网络数据。
 * @retval OT_ERROR_INVALID_ARGS一个或多个配置参数无效。
 * @retval OT_ERROR_NO_BUFS没有足够的空间将配置添加到本地网络数据。
 *
 * @sa otBorderRouterRemoveRoute
 * @sa otBorderRouter注册表
 */
otError otBorderRouterAddRoute(otInstance *aInstance, const otExternalRouteConfig *aConfig);

/**
 * 从本地网络数据中删除外部路由配置。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aPrefix   指向IPv6前缀的指针。
 *
 * @retval OT_ERROR_NONE已成功从本地网络数据中删除配置。
 * @retval OT_ERROR_NOT_FOUND找不到边界路由器条目。
 *
 * @sa otBorderRouter添加路线
 * @sa otBorderRouter注册表
 */
otError otBorderRouterRemoveRoute(otInstance *aInstance, const otIp6Prefix *aPrefix);

/**
 * 此函数获取本地网络数据中的下一个外部路由。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向网络数据迭代器上下文的指针。要获取第一个外部路由条目，应将其设置为OT_NETWORK_DATA_ITERATOR_INIT。
 * @param[out]    aConfig    指向外部路由信息的指针。
 *
 * @retval OT_ERROR_NONE已成功找到下一个外部路由。
 * @retval OT_ERROR_NOT_FOUND线程网络数据中不存在后续的外部路由条目。
 *
 */
otError otBorderRouterGetNextRoute(otInstance *           aInstance,
                                   otNetworkDataIterator *aIterator,
                                   otExternalRouteConfig *aConfig);

/**
 * 立即向领导登记本地网络数据。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功将服务器数据请求消息排队等待传递。
 *
 * @sa otBorderRouteAddOnMeshPrefix
 * @sa otBorderRouterRemoveOnMeshPrefix
 * @sa otBorderRouter添加路线
 * @sa otBorderRouterRemoveRoute
 */
otError otBorderRouterRegister(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_BORDER_ROUTER_H_

