/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括基础设施网络接口的平台抽象。
 *
 */

#ifndef OPENTHREAD_PLATFORM_INFRA_IF_H_
#define OPENTHREAD_PLATFORM_INFRA_IF_H_

#include <stdint.h>

#include <openthread/error.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此方法告诉基础接口是否分配了给定的IPv6地址。
 *
 * @param[in]  aInfraIfIndex  基础接口的索引。
 * @param[in]  aAddress       IPv6地址。
 *
 * @returns  如果基础接口已分配IPv6地址，则为TRUE，否则为FALSE。
 *
 */
bool otPlatInfraIfHasAddress(uint32_t aInfraIfIndex, const otIp6Address *aAddress);

/**
 * 此方法在给定基础结构接口上发送ICMPv6邻居发现消息。
 *
 * 参见RFC 4861：https://tools.ietf.org/html/rfc4861.
 *
 * @param[in]  aInfraIfIndex  此消息发送到的基础结构接口的索引。
 * @param[in]  aDestAddress   此邮件发送到的目标地址。
 * @param[in]  aBuffer        ICMPv6消息缓冲区。ICMPv6校验和为零，平台应进行校验和计算。
 * @param[in]  aBufferLength  消息缓冲区的长度。
 *
 * @note  根据RFC 4861，实现应该发送带有IPv6链路本地源地址的消息
 *        of interface @p aInfraIfIndex和IP跃点限制255。
 *
 * @retval OT_ERROR_NONE已成功发送ICMPv6消息。
 * @retval OT_ERROR_FAILED无法发送ICMPv6消息。
 *
 */
otError otPlatInfraIfSendIcmp6Nd(uint32_t            aInfraIfIndex,
                                 const otIp6Address *aDestAddress,
                                 const uint8_t *     aBuffer,
                                 uint16_t            aBufferLength);

/**
 * infra接口驱动程序调用此方法以通知OpenThread收到ICMPv6邻居发现消息。
 *
 * 参见RFC 4861：https://tools.ietf.org/html/rfc4861.
 *
 * @param[in]  aInstance      OpenThread实例结构。
 * @param[in]  aInfraIfIndex  接收ICMPv6消息的基础结构接口的索引。
 * @param[in]  aSrcAddress    接收此消息的源地址。
 * @param[in]  aBuffer        ICMPv6消息缓冲区。
 * @param[in]  aBufferLength  ICMPv6消息缓冲区的长度。
 *
 * @note  根据RFC 4861，呼叫者应强制要求源地址必须是IPv6链路本地地址，IP跃点限制必须是255。
 *
 */
extern void otPlatInfraIfRecvIcmp6Nd(otInstance *        aInstance,
                                     uint32_t            aInfraIfIndex,
                                     const otIp6Address *aSrcAddress,
                                     const uint8_t *     aBuffer,
                                     uint16_t            aBufferLength);

/**
 * infra接口驱动程序调用此方法以通知OpenThread接口状态更改。
 *
 * 即使接口的运行状态没有改变，平台也可以调用方法。在这种情况下，路由管理器状态不受影响。
 *
 * @param[in]  aInstance          OpenThread实例结构。
 * @param[in]  aInfraIfIndex      基础结构接口的索引。
 * @param[in]  aIsRunning         指示基础结构接口是否正在运行的布尔值。
 *
 * @retval  OT_ERROR_NONE已成功更新基础接口状态。
 * @retval  OT_ERROR_INVALID_STATE路由管理器未初始化。
 * @retval  OT_ERROR_INVALID_ARGS@p aInfraIfIndex与初始化路由管理器的基础接口不匹配。
 *
 */
extern otError otPlatInfraIfStateChanged(otInstance *aInstance, uint32_t aInfraIfIndex, bool aIsRunning);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_INFRA_IF_H_

