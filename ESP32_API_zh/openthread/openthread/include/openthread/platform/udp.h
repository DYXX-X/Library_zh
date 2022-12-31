/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括平台UDP服务的抽象。
 */

#ifndef OPENTHREAD_PLATFORM_UDP_H_
#define OPENTHREAD_PLATFORM_UDP_H_

#include <openthread/udp.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此函数按平台初始化UDP套接字。
 *
 * @param[in]   aUdpSocket  指向UDP套接字的指针。
 *
 * @retval  OT_ERROR_NONE已成功初始化平台的UDP套接字。
 * @retval  OT_ERROR_FAILED无法初始化UDP套接字。
 *
 */
otError otPlatUdpSocket(otUdpSocket *aUdpSocket);

/**
 * 此函数按平台关闭UDP套接字。
 *
 * @param[in]   aUdpSocket  指向UDP套接字的指针。
 *
 * @retval  OT_ERROR_NONE已成功关闭平台的UDP套接字。
 * @retval  OT_ERROR_FAILED无法关闭UDP套接字。
 *
 */
otError otPlatUdpClose(otUdpSocket *aUdpSocket);

/**
 * 此函数按平台绑定UDP套接字。
 *
 * @param[in]   aUdpSocket  指向UDP套接字的指针。
 *
 * @retval  OT_ERROR_NONE已通过平台成功绑定UDP套接字。
 * @retval  OT_ERROR_FAILED无法绑定UDP套接字。
 *
 */
otError otPlatUdpBind(otUdpSocket *aUdpSocket);

/**
 * 此函数将UDP套接字绑定到平台网络接口。
 *
 * 注意：仅在使用`OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE`时可用。
 *
 * @param[in]   aUdpSocket          指向UDP套接字的指针。
 * @param[in]   aNetifIdentifier    网络接口标识符。
 *
 * @retval  OT_ERROR_NONE已成功绑定UDP套接字。
 * @retval  OT_ERROR_FAILED无法绑定UDP。
 *
 */
otError otPlatUdpBindToNetif(otUdpSocket *aUdpSocket, otNetifIdentifier aNetifIdentifier);

/**
 * 此函数按平台连接UDP套接字。
 *
 * @param[in]   aUdpSocket  指向UDP套接字的指针。
 *
 * @retval  OT_ERROR_NONE已通过平台成功连接。
 * @retval  OT_ERROR_FAILED无法连接UDP套接字。
 *
 */
otError otPlatUdpConnect(otUdpSocket *aUdpSocket);

/**
 * 此函数按平台发送UDP负载。
 *
 * @param[in]   aUdpSocket      指向UDP套接字的指针。
 * @param[in]   aMessage        指向要发送的消息的指针。
 * @param[in]   aMessageInfo    指向与@p aMessage关联的消息信息的指针。
 *
 * @retval  OT_ERROR_NONE平台已成功发送，@p aMessage已释放。
 * @retval  OT_ERROR_FAILED无法绑定UDP套接字。
 *
 */
otError otPlatUdpSend(otUdpSocket *aUdpSocket, otMessage *aMessage, const otMessageInfo *aMessageInfo);

/**
 * 此函数配置UDP套接字以加入UDP多播组。
 *
 * 注意：仅在使用`OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE`时可用。
 *
 * @param[in]   aUdpSocket          指向UDP套接字的指针。
 * @param[in]   aNetifIdentifier    网络接口标识符。
 * @param[in]   aAddress            UDP多播组地址。
 *
 * @retval  OT_ERROR_NONE已成功加入多播组。
 * @retval  OT_ERROR_FAILED无法加入多播组。
 *
 */
otError otPlatUdpJoinMulticastGroup(otUdpSocket *       aUdpSocket,
                                    otNetifIdentifier   aNetifIdentifier,
                                    const otIp6Address *aAddress);

/**
 * 此函数将UDP套接字配置为离开UDP多播组。
 *
 * 注意：仅在使用`OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE`时可用。
 *
 * @param[in]   aUdpSocket          指向UDP套接字的指针。
 * @param[in]   aNetifIdentifier    网络接口标识符。
 * @param[in]   aAddress            UDP多播组地址。
 *
 * @retval  OT_ERROR_NONE已成功离开多播组。
 * @retval  OT_ERROR_FAILED无法离开多播组。
 *
 */
otError otPlatUdpLeaveMulticastGroup(otUdpSocket *       aUdpSocket,
                                     otNetifIdentifier   aNetifIdentifier,
                                     const otIp6Address *aAddress);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_UDP_H_

