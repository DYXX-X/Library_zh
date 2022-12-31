/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread CoAP安全实现的顶级函数。
 *
 *  @note 此模块中的函数需要构建时功能`OPENTHREAD_COONFIG_COAP_SECURE_API_ENABLE=1'。
 *
 *  @note 要启用密码套件DTLS_PSK_WITH_AES_128_CCM_8，必须在MBEDTLS配置中启用MBEDTLS_KEY_EXCHANGE_PSK_ENABLED。h要启用密码套件DTLS_ECDHE_ECDSA_WITH_AES_128_CCM_8，必须在MBEDTLS config.h中启用MBEDTLS_KEY_EXCHANGE_ECDHE-ECDSA_ENABLED。
 */

#ifndef OPENTHREAD_COAP_SECURE_H_
#define OPENTHREAD_COAP_SECURE_H_

#include <stdint.h>

#include <openthread/coap.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api coap安全
 *
 * @brief 该模块包括控制CoAP安全（CoAP over DTLS）通信的功能。
 *
 *   当启用CoAP安全API功能（`OPENTHREAD_COONFIG_CoAP_Secure_API_ENABLE`）时，此模块中的功能可用。
 *
 * @{
 *
 */

#define OT_DEFAULT_COAP_SECURE_PORT 5684 ///<RFC 7252中指定的默认CoAP安全端口

/**
 * 当DTLS连接状态更改时，调用此函数指针。
 *
 * @param[in]  aConnected  如果建立了连接，则为true，否则为false。
 * @param[in]  aContext    指向任意上下文信息的指针。
 *
 */
typedef void (*otHandleCoapSecureClientConnect)(bool aConnected, void *aContext);

/**
 * 此功能启动CoAP安全服务。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aPort      要绑定到的本地UDP端口。
 *
 * @retval OT_ERROR_NONE已成功启动CoAP安全服务器。
 *
 */
otError otCoapSecureStart(otInstance *aInstance, uint16_t aPort);

/**
 * 此函数用于停止CoAP安全服务器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otCoapSecureStop(otInstance *aInstance);

/**
 * 此方法设置预共享密钥（PSK）和密码套件DTLS_PSK_WITH_AES_128_CCM_8。
 *
 * @note 此函数要求启用构建时功能`MBEDTLS_KEY_EXCHANGE_PSK_ENABLED`。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aPsk          指向PSK的指针。
 * @param[in]  aPskLength    PSK长度。
 * @param[in]  aPskIdentity  PSK的标识名。
 * @param[in]  aPskIdLength  PSK标识长度。
 *
 */
void otCoapSecureSetPsk(otInstance *   aInstance,
                        const uint8_t *aPsk,
                        uint16_t       aPskLength,
                        const uint8_t *aPskIdentity,
                        uint16_t       aPskIdLength);

/**
 * 此方法返回对等x509证书base64编码。
 *
 * @note 此函数要求启用构建时功能`MBEDTLS_BASE64_C`和`MBEDLLS_SL_KEEP_PEER_CERTIFICATE`。
 *
 * @param[in]   aInstance        指向OpenThread实例的指针。
 * @param[out]  aPeerCert        指向base64编码的证书缓冲区的指针。
 * @param[out]  aCertLength      base64编码的对等证书的长度。
 * @param[in]   aCertBufferSize  aPeerCert的缓冲区大小。
 *
 * @retval OT_ERROR_INVALID_STATE尚未连接。
 * @retval OT_ERROR_NONE成功获取对等证书。
 * @retval OT_ERROR_NO_BUFS无法为证书分配内存。
 *
 */
otError otCoapSecureGetPeerCertificateBase64(otInstance *   aInstance,
                                             unsigned char *aPeerCert,
                                             size_t *       aCertLength,
                                             size_t         aCertBufferSize);

/**
 * 此方法设置coap安全连接的身份验证模式。
 *
 * 禁用或启用对等证书的验证。必须在开始前调用。
 *
 * @param[in]   aInstance               指向OpenThread实例的指针。
 * @param[in]   aVerifyPeerCertificate  true，以验证对等证书。
 *
 */
void otCoapSecureSetSslAuthMode(otInstance *aInstance, bool aVerifyPeerCertificate);

/**
 * 此方法使用DTLS_ECDHE_ECDSA_with_AES_128_CCM_8为DTLS会话设置本地设备的X509证书和相应的私钥。
 *
 * @note 此函数需要`MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED=1 `。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aX509Cert          指向PEM格式X509证书的指针。
 * @param[in]  aX509Length        证书的长度。
 * @param[in]  aPrivateKey        指向PEM格式私钥的指针。
 * @param[in]  aPrivateKeyLength  私钥的长度。
 *
 */
void otCoapSecureSetCertificate(otInstance *   aInstance,
                                const uint8_t *aX509Cert,
                                uint32_t       aX509Length,
                                const uint8_t *aPrivateKey,
                                uint32_t       aPrivateKeyLength);

/**
 * 此方法设置受信任的顶级CA。它是验证对等方证书所必需的。
 *
 * 应用CoAPS的DTLS模式“ECDHE ECDSA with AES 128 CCM 8”。
 *
 * @note 此函数需要`MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED=1 `。
 *
 * @param[in]  aInstance                指向OpenThread实例的指针。
 * @param[in]  aX509CaCertificateChain  指向PEM格式的X509 CA链的指针。
 * @param[in]  aX509CaCertChainLength   链条的长度。
 *
 */
void otCoapSecureSetCaCertificateChain(otInstance *   aInstance,
                                       const uint8_t *aX509CaCertificateChain,
                                       uint32_t       aX509CaCertChainLength);

/**
 * 此方法初始化与对等方的DTLS会话。
 *
 * @param[in]  aInstance               指向OpenThread实例的指针。
 * @param[in]  aSockAddr               指向远程套接字地址的指针。
 * @param[in]  aHandler                指向DTLS连接状态更改时将调用的函数的指针。
 * @param[in]  aContext                指向任意上下文信息的指针。
 *
 * @retval OT_ERROR_NONE已成功启动DTLS连接。
 *
 */
otError otCoapSecureConnect(otInstance *                    aInstance,
                            const otSockAddr *              aSockAddr,
                            otHandleCoapSecureClientConnect aHandler,
                            void *                          aContext);

/**
 * 此方法停止DTLS连接。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otCoapSecureDisconnect(otInstance *aInstance);

/**
 * 此方法指示DTLS会话是否已连接。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @retval TRUE DTLS会话已连接。
 * @retval FALSE DTLS会话未连接。
 *
 */
bool otCoapSecureIsConnected(otInstance *aInstance);

/**
 * 此方法指示DTLS会话是否处于活动状态。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @retval TRUE如果DTLS会话处于活动状态。
 * @retval 如果DTLS会话未激活，则返回FALSE。
 *
 */
bool otCoapSecureIsConnectionActive(otInstance *aInstance);

/**
 * 此方法通过安全DTLS连接逐块发送CoAP请求。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * 如果期望对请求作出响应，则应提供相应的功能和上下文信息。如果不需要响应，这些参数应该是NULL指针。如果标头中未设置消息Id（等于0），则此函数将为消息分配唯一的消息Id。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      对要发送的消息的引用。
 * @param[in]  aHandler      响应接收或超时时应调用的函数指针。
 * @param[in]  aContext      指向任意上下文信息的指针。
 * @param[in]  aTransmitHook 在Block1响应接收时调用的函数指针。
 * @param[in]  aReceiveHook  在Block2响应接收时调用的函数指针。
 *
 * @retval OT_ERROR_NONE已成功发送CoAP消息。
 * @retval OT_ERROR_NO_BUFS无法分配重传数据。
 * @retval OT_ERROR_INVALID_STATE DTLS连接未初始化。
 *
 */
otError otCoapSecureSendRequestBlockWise(otInstance *                aInstance,
                                         otMessage *                 aMessage,
                                         otCoapResponseHandler       aHandler,
                                         void *                      aContext,
                                         otCoapBlockwiseTransmitHook aTransmitHook,
                                         otCoapBlockwiseReceiveHook  aReceiveHook);

/**
 * 此方法通过安全DTLS连接发送CoAP请求。
 *
 * 如果期望对请求作出响应，则应提供相应的功能和上下文信息。如果不需要响应，这些参数应该是NULL指针。如果标头中未设置消息Id（等于0），则此函数将为消息分配唯一的消息Id。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      对要发送的消息的引用。
 * @param[in]  aHandler      响应接收或超时时应调用的函数指针。
 * @param[in]  aContext      指向任意上下文信息的指针。
 *
 * @retval OT_ERROR_NONE已成功发送CoAP消息。
 * @retval OT_ERROR_NO_BUFS无法分配重传数据。
 * @retval OT_ERROR_INVALID_STATE DTLS连接未初始化。
 *
 */
otError otCoapSecureSendRequest(otInstance *          aInstance,
                                otMessage *           aMessage,
                                otCoapResponseHandler aHandler,
                                void *                aContext);

/**
 * 此函数将资源添加到CoAP安全服务器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapSecureAddResource(otInstance *aInstance, otCoapResource *aResource);

/**
 * 此函数用于从CoAP安全服务器中删除资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapSecureRemoveResource(otInstance *aInstance, otCoapResource *aResource);

/**
 * 此函数向CoAP安全服务器添加逐块资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapSecureAddBlockWiseResource(otInstance *aInstance, otCoapBlockwiseResource *aResource);

/**
 * 此函数从CoAP安全服务器中删除按块划分的资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapSecureRemoveBlockWiseResource(otInstance *aInstance, otCoapBlockwiseResource *aResource);

/**
 * 此函数为未处理的CoAP安全请求设置默认处理程序。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aHandler   当未处理的请求到达时应调用的函数指针。
 * @param[in]  aContext   指向任意上下文信息的指针。如果未使用，则可能为NULL。
 *
 */
void otCoapSecureSetDefaultHandler(otInstance *aInstance, otCoapRequestHandler aHandler, void *aContext);

/**
 * 此方法设置连接的回调以指示客户端何时连接到CoAP安全服务器。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aHandler      DTLS连接建立后将调用的函数的指针。
 * @param[in]  aContext      指向任意上下文信息的指针。如果未使用，则可能为NULL。
 *
 */
void otCoapSecureSetClientConnectedCallback(otInstance *                    aInstance,
                                            otHandleCoapSecureClientConnect aHandler,
                                            void *                          aContext);

/**
 * 此函数从CoAP安全服务器逐块发送CoAP响应。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向要发送的CoAP响应的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aContext      指向任意上下文信息的指针。如果未使用，则可能为NULL。
 * @param[in]  aTransmitHook 接收Block1请求时调用的函数指针。
 *
 * @retval OT_ERROR_NONE已成功将CoAP响应消息排入队列。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法发送CoAP响应。
 *
 */
otError otCoapSecureSendResponseBlockWise(otInstance *                aInstance,
                                          otMessage *                 aMessage,
                                          const otMessageInfo *       aMessageInfo,
                                          void *                      aContext,
                                          otCoapBlockwiseTransmitHook aTransmitHook);

/**
 * 此函数从CoAP安全服务器发送CoAP响应。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向要发送的CoAP响应的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 *
 * @retval OT_ERROR_NONE已成功将CoAP响应消息排入队列。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法发送CoAP响应。
 *
 */
otError otCoapSecureSendResponse(otInstance *aInstance, otMessage *aMessage, const otMessageInfo *aMessageInfo);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif /* OPENTHREAD_COAP_SECURE_H_ */

