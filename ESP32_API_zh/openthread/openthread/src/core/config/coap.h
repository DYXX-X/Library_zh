/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括CoAP的编译时配置。
 *
 */

#ifndef CONFIG_COAP_H_
#define CONFIG_COAP_H_

/**
 * @def OPENTHREAD_CONFIG_COAP_SERVER_MAX_CACHED_RESPONSES
 *
 * CoAP可确认消息的最大缓存响应数。
 *
 * 缓存响应用于邮件重复数据消除。
 *
 */
#ifndef OPENTHREAD_CONFIG_COAP_SERVER_MAX_CACHED_RESPONSES
#define OPENTHREAD_CONFIG_COAP_SERVER_MAX_CACHED_RESPONSES 10
#endif

/**
 * @def OPENTHREAD_CONFIG_COAP_API_ENABLE
 *
 * 定义为1以启用CoAP API。
 *
 */
#ifndef OPENTHREAD_CONFIG_COAP_API_ENABLE
#define OPENTHREAD_CONFIG_COAP_API_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_COAP_OBSERVE_API_ENABLE
 *
 * 定义为1以启用CoAP观察（RFC7641）API。
 *
 */
#ifndef OPENTHREAD_CONFIG_COAP_OBSERVE_API_ENABLE
#define OPENTHREAD_CONFIG_COAP_OBSERVE_API_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_COAP_BLOCKWISE_TRANSFER_ENABLE
 *
 * 定义为1以启用CoAP逐块传输。
 *
 */
#ifndef OPENTHREAD_CONFIG_COAP_BLOCKWISE_TRANSFER_ENABLE
#define OPENTHREAD_CONFIG_COAP_BLOCKWISE_TRANSFER_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_COAP_MAX_BLOCK_LENGTH
 *
 * 此设置配置CoAP逐块传输期间一个块的最大长度。
 *
 */
#ifndef OPENTHREAD_CONFIG_COAP_MAX_BLOCK_LENGTH
#define OPENTHREAD_CONFIG_COAP_MAX_BLOCK_LENGTH 1024
#endif

/**
 * @def OPENTHREAD_CONFIG_COAP_SECURE_API_ENABLE
 *
 * 定义为1以启用CoAP安全API。
 *
 */
#ifndef OPENTHREAD_CONFIG_COAP_SECURE_API_ENABLE
#define OPENTHREAD_CONFIG_COAP_SECURE_API_ENABLE 0
#endif

#endif // CONFIG_COAP_H_

