/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括使用IPv6/UDP接口的线程无线电封装链路（TREL）的平台抽象。
 *
 */

#ifndef OPENTHREAD_PLATFORM_TREL_UDP6_H_
#define OPENTHREAD_PLATFORM_TREL_UDP6_H_

#include <stdint.h>

#include <openthread/error.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板电缆
 *
 * @brief 该模块包括使用IPv6/UDP接口的线程无线电封装链路（TREL）的平台抽象。
 *
 * @{
 *
 */

/**
 * 此函数初始化TREL IPv6/UDP接口。
 *
 * 此函数在任何其他TREL平台函数之前调用。
 *
 * @param[in] aInstance        OpenThread实例结构。
 * @param[in] aUnicastAddress  要添加到接口并用作tx源和rx目标的单播地址。
 * @param[in] aUdpPort         要使用的UDP端口号。
 *
 */
void otPlatTrelUdp6Init(otInstance *aInstance, const otIp6Address *aUnicastAddress, uint16_t aUdpPort);

/**
 * 此函数更新TREL IPv6/UDP接口的单播IPv6地址。
 *
 * 接口只能有一个单播IPv6地址。调用此函数将替换任何先前设置的单播IPv6地址（在从“otPlatTrelUdp6Init”初始化期间，或更早调用“otPlatTreeUdp6UpdateAddress（）”期间）。
 *
 * @param[in] aInstance        OpenThread实例结构。
 * @param[in] aUnicastAddress  要添加到接口并用作tx源和rx目标的单播地址。
 *
 */
void otPlatTrelUdp6UpdateAddress(otInstance *aInstance, const otIp6Address *aUnicastAddress);

/**
 * 此函数将TREL IPv6/UDP接口订阅到新的多播地址。
 *
 * 可以多次调用此函数以订阅不同的地址。接口初始化时，除了从“otPlatTrelUdp6Init（）”函数添加的单播地址之外，接口还应接受/接收发往任何先前预订的多播地址的数据包。
 *
 * @param[in] aInstance          OpenThread实例结构。
 * @param[in] aMulticastAddress  多播IPv6地址。
 *
 */
void otPlatTrelUdp6SubscribeMulticastAddress(otInstance *aInstance, const otIp6Address *aMulticastAddress);

/**
 * 此函数请求将数据包发送到给定的目的地。
 *
 * @param[in] aInstance        OpenThread实例结构。
 * @param[in] aBuffer          指向包含要发送的数据包的缓冲区的指针。
 * @param[in] aLength          数据包长度（字节数）。
 * @param[in] aDestAddress     目标IPv6地址（可以是单播或多播IPv6地址）。
 *
 * @retval OT_ERROR_NONE已成功处理tx请求。
 * @retval OT_ERROR_ABORT接口未就绪，tx已中止
 *
 */
otError otPlatTrelUdp6SendTo(otInstance *        aInstance,
                             const uint8_t *     aBuffer,
                             uint16_t            aLength,
                             const otIp6Address *aDestAddress);

/**
 * 此函数是来自平台的回调，用于通知收到的数据包。
 *
 * @note 缓冲区内容（直到其指定长度）可能会在OpenThread内核处理过程中发生更改（例如，就地解密），因此平台实现应该期望从该函数返回后
 * packet @p a缓冲区内容可能已更改。
 *
 * @param[in] aInstance        OpenThread实例结构。
 * @param[in] aBuffer          包含接收到的数据包的缓冲区。
 * @param[in] aLength          数据包长度（字节数）。
 *
 */
extern void otPlatTrelUdp6HandleReceived(otInstance *aInstance, uint8_t *aBuffer, uint16_t aLength);

/**
 * 此可选功能仅用于测试。它更改TREL接口的测试模式状态。
 *
 * 此功能请求暂时禁用或启用TREL接口。禁用后，所有通过TREL接口的流量都应被无声地丢弃。
 *
 * OpenThread提供了该方法的默认弱实现（返回NOT_IMPLEMENTED）。
 *
 * @param[in] aInstance        OpenThread实例结构。
 * @param[in] aEnable          指示是否启用/禁用TREL接口。
 *
 * @retval OT_ERROR_NONE成功更改TREL接口测试状态（启用/禁用）。
 * @retval OT_ERROR_FAILED无法启用TREL接口。
 * @retval OT_ERROR_NOT_IMPLEMENTED平台不提供此功能。
 *
 */
otError otPlatTrelUdp6SetTestMode(otInstance *aInstance, bool aEnable);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_PLATFORM_TREL_UDP6_H_

