/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread库的顶级sntp函数。
 */

#ifndef OPENTHREAD_SNTP_H_
#define OPENTHREAD_SNTP_H_

#include <stdint.h>

#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api sntp
 *
 * @brief 该模块包括控制SNTP通信的功能。
 *
 * @{
 *
 */

#define OT_SNTP_DEFAULT_SERVER_IP "2001:4860:4806:8::" ///<定义默认SNTP服务器地址-Google NTP服务器。
#define OT_SNTP_DEFAULT_SERVER_PORT 123                ///<定义默认SNTP服务器端口。

/**
 * 此结构实现SNTP查询参数。
 *
 */
typedef struct otSntpQuery
{
    const otMessageInfo *mMessageInfo; ///<与SNTP服务器相关的消息信息的引用。
} otSntpQuery;

/**
 * 当收到SNTP响应时，调用此函数指针。
 *
 * @param[in]  aContext   指向应用程序特定上下文的指针。
 * @param[in]  aTime      指定服务器上响应留给客户端的时间，以UNIX时间为单位。
 * @param[in]  aResult    SNTP事务的结果。
 *
 * @retval  OT_ERROR_NONE成功接收到响应，时间以@p aTime表示。
 * @retval  OT_ERROR_ABORT SNTP事务被堆栈中止。
 * @retval  OT_ERROR_BUSY已收到Kiss-o'-死亡数据包。
 * @retval  OT_ERROR_RESPONSE_TIMEOUT超时内未收到SNTP响应。
 * @retval  OT_ERROR_FAILED收到响应，但包含不正确的数据。
 *
 */
typedef void (*otSntpResponseHandler)(void *aContext, uint64_t aTime, otError aResult);

/**
 * 此函数发送SNTP查询。
 *
 * 仅当启用功能“OPENTHREAD_CONFIG_SNTP_CLIENT_ENABLE”时，此功能才可用。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aQuery      用于指定SNTP查询参数的指针。
 * @param[in]  aHandler    响应接收或超时时应调用的函数指针。
 * @param[in]  aContext    指向任意上下文信息的指针。
 *
 */
otError otSntpClientQuery(otInstance *          aInstance,
                          const otSntpQuery *   aQuery,
                          otSntpResponseHandler aHandler,
                          void *                aContext);

/**
 * 此函数设置unix时代号。
 *
 * unix时代的默认值设置为0。随后的时代从2106年开始。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aUnixEra    Unix时代编号。
 *
 */
void otSntpClientSetUnixEra(otInstance *aInstance, uint32_t aUnixEra);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_SNTP_H_

