/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread UDP API。
 *
 */

#ifndef OPENTHREAD_UDP_H_
#define OPENTHREAD_UDP_H_

#include <openthread/ip6.h>
#include <openthread/message.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api udp
 *
 * @brief 该模块包括控制UDP通信的功能。
 *
 * @{
 *
 */

/**
 * 此回调允许OpenThread为某些UDP消息提供特定的处理程序。
 *
 * @retval  true消息由此接收器处理，不应进一步处理。
 * @retval  false此接收方不处理消息。
 *
 */
typedef bool (*otUdpHandler)(void *aContext, const otMessage *aMessage, const otMessageInfo *aMessageInfo);

/**
 * 此结构表示UDP接收器。
 *
 */
typedef struct otUdpReceiver
{
    struct otUdpReceiver *mNext;    ///<指向下一个UDP接收器的指针（仅限内部使用）。
    otUdpHandler          mHandler; ///<指向接收器回调的函数指针。
    void *                mContext; ///<指向应用程序特定上下文的指针。
} otUdpReceiver;

/**
 * 此函数用于添加UDP接收器。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aUdpReceiver    指向UDP接收器的指针。
 *
 * @retval  OT_ERROR_NONE成功添加接收器。
 * @retval  OT_ERROR_ALREADY已添加UDP接收器。
 *
 */
otError otUdpAddReceiver(otInstance *aInstance, otUdpReceiver *aUdpReceiver);

/**
 * 此函数用于删除UDP接收器。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aUdpReceiver    指向UDP接收器的指针。
 *
 * @retval  OT_ERROR_NONE接收器已成功删除。
 * @retval  OT_ERROR_NOT_FOUND未添加UDP接收器。
 *
 */
otError otUdpRemoveReceiver(otInstance *aInstance, otUdpReceiver *aUdpReceiver);

/**
 * 此函数发送不带套接字的UDP消息。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向没有UDP标头的消息的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 *
 * @retval OT_ERROR_NONE已成功将消息排入输出接口。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法添加IPv6标头。
 *
 */
otError otUdpSendDatagram(otInstance *aInstance, otMessage *aMessage, otMessageInfo *aMessageInfo);

/**
 * 此回调允许OpenThread将收到的UDP消息通知应用程序。
 *
 */
typedef void (*otUdpReceive)(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo);

/**
 * 此结构表示UDP套接字。
 *
 */
typedef struct otUdpSocket
{
    otSockAddr          mSockName; ///<本地IPv6套接字地址。
    otSockAddr          mPeerName; ///<对等IPv6套接字地址。
    otUdpReceive        mHandler;  ///<指向应用程序回调的函数指针。
    void *              mContext;  ///<指向应用程序特定上下文的指针。
    void *              mHandle;   ///<平台UDP的句柄。
    struct otUdpSocket *mNext;     ///<指向下一个UDP套接字的指针（仅限内部使用）。
} otUdpSocket;

/**
 * 此枚举定义OpenThread网络接口标识符。
 *
 */
typedef enum otNetifIdentifier
{
    OT_NETIF_UNSPECIFIED = 0, ///<未指定的网络接口。
    OT_NETIF_THREAD,          ///<线程接口。
    OT_NETIF_BACKBONE,        ///<骨干界面。
} otNetifIdentifier;

/**
 * 为发送UDP消息分配新的消息缓冲区。
 *
 * @note 如果@p aSettings为“NULL”，则链接层安全性启用，消息优先级默认设置为OT_message_priority_NORMAL。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSettings  指向消息设置的指针，或NULL以使用默认设置。
 *
 * @returns 指向消息缓冲区的指针，如果没有可用的消息缓冲区或参数无效，则返回NULL。
 *
 * @sa otMessage自由
 *
 */
otMessage *otUdpNewMessage(otInstance *aInstance, const otMessageSettings *aSettings);

/**
 * 打开UDP/IPv6套接字。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSocket    指向UDP套接字结构的指针。
 * @param[in]  aCallback  指向应用程序回调函数的指针。
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功打开套接字。
 * @retval OT_ERROR_FAILED无法打开套接字。
 *
 */
otError otUdpOpen(otInstance *aInstance, otUdpSocket *aSocket, otUdpReceive aCallback, void *aContext);

/**
 * 检查UDP套接字是否打开。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSocket    指向UDP套接字结构的指针。
 *
 * @returns UDP套接字是否打开。
 *
 */
bool otUdpIsOpen(otInstance *aInstance, const otUdpSocket *aSocket);

/**
 * 关闭UDP/IPv6套接字。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSocket    指向UDP套接字结构的指针。
 *
 * @retval OT_ERROR_NONE已成功关闭套接字。
 * @retval OT_ERROR_FAILED无法关闭UDP套接字。
 *
 */
otError otUdpClose(otInstance *aInstance, otUdpSocket *aSocket);

/**
 * 绑定UDP/IPv6套接字。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSocket    指向UDP套接字结构的指针。
 * @param[in]  aSockName  指向IPv6套接字地址结构的指针。
 * @param[in]  aNetif     要绑定的网络接口。
 *
 * @retval OT_ERROR_NONE绑定操作成功。
 * @retval OT_ERROR_FAILED无法绑定UDP套接字。
 *
 */
otError otUdpBind(otInstance *aInstance, otUdpSocket *aSocket, const otSockAddr *aSockName, otNetifIdentifier aNetif);

/**
 * 连接UDP/IPv6套接字。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSocket    指向UDP套接字结构的指针。
 * @param[in]  aSockName  指向IPv6套接字地址结构的指针。
 *
 * @retval OT_ERROR_NONE连接操作成功。
 * @retval OT_ERROR_FAILED无法连接UDP套接字。
 *
 */
otError otUdpConnect(otInstance *aInstance, otUdpSocket *aSocket, const otSockAddr *aSockName);

/**
 * 发送UDP/IPv6消息。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aSocket       指向UDP套接字结构的指针。
 * @param[in]  aMessage      指向消息缓冲区的指针。
 * @param[in]  aMessageInfo  指向消息信息结构的指针。
 *
 * 如果返回值为OT_ERROR_NONE，OpenThread将获得@paMessage的所有权，调用方将不再
 * reference @p a消息。如果返回值不是OT_ERROR_NONE，
 * including freeing @p aMessage（如果不再需要消息缓冲区）。
 *
 * @retval OT_ERROR_NONE消息已成功安排发送。
 * @retval OT_ERROR_INVALID_ARGS提供的参数无效。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法添加UDP和IPv6标头。
 *
 */
otError otUdpSend(otInstance *aInstance, otUdpSocket *aSocket, otMessage *aMessage, const otMessageInfo *aMessageInfo);

/**
 * 此函数获取UDP套接字链接列表的头。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns 指向UDP套接字链接列表头部的指针。
 *
 */
otUdpSocket *otUdpGetSockets(otInstance *aInstance);

/**
 * @}
 *
 */

/**
 * @addtogroup api udp转发
 *
 * @brief 该模块包括UDP转发功能。
 *
 *   当启用udp转发功能（`OPENTHREAD_CONFIG_udp_forward_ENABLE`）时，此模块中的功能可用。
 *
 * @{
 *
 */

/**
 * 此函数指针将UDP数据包传递给主机，主机应通过其自己的网络堆栈发送数据包。
 *
 * @param[in]  aMessage   指向UDP消息的指针。
 * @param[in]  aPeerPort  目标UDP端口。
 * @param[in]  aPeerAddr  指向目标IPv6地址的指针。
 * @param[in]  aSockPort  源UDP端口。
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 *
 */
typedef void (*otUdpForwarder)(otMessage *   aMessage,
                               uint16_t      aPeerPort,
                               otIp6Address *aPeerAddr,
                               uint16_t      aSockPort,
                               void *        aContext);

/**
 * 设置UDP转发回调以将UDP数据包传递到主机。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aForwarder           指向被调用以将UDP数据包转发到主机的函数的指针。
 * @param[in]  aContext             指向应用程序特定上下文的指针。
 *
 */
void otUdpForwardSetForwarder(otInstance *aInstance, otUdpForwarder aForwarder, void *aContext);

/**
 * 处理从主机接收的UDP数据包。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aMessage             指向UDP消息的指针。
 * @param[in]  aPeerPort            源UDP端口。
 * @param[in]  aPeerAddr            指向源地址的指针。
 * @param[in]  aSockPort            目标UDP端口。
 *
 * @warning 无论呼叫成功还是失败，消息都会被释放。
 *
 */
void otUdpForwardReceive(otInstance *        aInstance,
                         otMessage *         aMessage,
                         uint16_t            aPeerPort,
                         const otIp6Address *aPeerAddr,
                         uint16_t            aSockPort);

/**
 * 确定给定UDP端口是否由OpenThread API以独占方式打开。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  port                 要验证的UDP端口号。
 *
 * @retval true该端口仅由OpenThread使用。
 * @retval false该端口未被任何OpenThread API使用或共享（例如，是骨干套接字）。
 *
 */
bool otUdpIsPortInUse(otInstance *aInstance, uint16_t port);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_UDP_H_

