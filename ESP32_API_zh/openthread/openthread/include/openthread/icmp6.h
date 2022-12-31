/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread库的顶级ICMPv6函数。
 */

#ifndef OPENTHREAD_ICMP6_H_
#define OPENTHREAD_ICMP6_H_

#include <openthread/ip6.h>
#include <openthread/message.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api-icmp6
 *
 * @brief 该模块包括控制ICMPv6通信的功能。
 *
 * @{
 *
 */

/**
 * ICMPv6消息类型
 *
 */
typedef enum otIcmp6Type
{
    OT_ICMP6_TYPE_DST_UNREACH       = 1,   ///<目标不可访问
    OT_ICMP6_TYPE_PACKET_TO_BIG     = 2,   ///<包到大
    OT_ICMP6_TYPE_TIME_EXCEEDED     = 3,   ///<超过时间
    OT_ICMP6_TYPE_PARAMETER_PROBLEM = 4,   ///<参数问题
    OT_ICMP6_TYPE_ECHO_REQUEST      = 128, ///<回显请求
    OT_ICMP6_TYPE_ECHO_REPLY        = 129, ///<回音回复
    OT_ICMP6_TYPE_ROUTER_SOLICIT    = 133, ///<路由器请求
    OT_ICMP6_TYPE_ROUTER_ADVERT     = 134, ///<路由器广告
} otIcmp6Type;

/**
 * ICMPv6消息代码
 *
 */
typedef enum otIcmp6Code
{
    OT_ICMP6_CODE_DST_UNREACH_NO_ROUTE = 0, ///<目标无法访问无路由
    OT_ICMP6_CODE_FRAGM_REAS_TIME_EX   = 1, ///<超过碎片重新组装时间
} otIcmp6Code;

#define OT_ICMP6_HEADER_DATA_SIZE 4 ///<ICMPv6报头的消息特定数据的大小。

/**
 * @struct otIcmp6标题
 *
 * 此结构表示ICMPv6标头。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIcmp6Header
{
    uint8_t  mType;     ///<类型
    uint8_t  mCode;     ///<代码
    uint16_t mChecksum; ///<校验和
    union OT_TOOL_PACKED_FIELD
    {
        uint8_t  m8[OT_ICMP6_HEADER_DATA_SIZE / sizeof(uint8_t)];
        uint16_t m16[OT_ICMP6_HEADER_DATA_SIZE / sizeof(uint16_t)];
        uint32_t m32[OT_ICMP6_HEADER_DATA_SIZE / sizeof(uint32_t)];
    } mData; ///<消息特定数据
} OT_TOOL_PACKED_END;

/**
 * 此类型表示ICMPv6标头。
 *
 */
typedef struct otIcmp6Header otIcmp6Header;

/**
 * 此回调允许OpenThread将收到的ICMPv6消息通知应用程序。
 *
 * @param[in]  aContext      指向任意上下文信息的指针。
 * @param[in]  aMessage      指向接收到的消息的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aIcmpHeader   指向接收到的ICMPv6标头的指针。
 *
 */
typedef void (*otIcmp6ReceiveCallback)(void *               aContext,
                                       otMessage *          aMessage,
                                       const otMessageInfo *aMessageInfo,
                                       const otIcmp6Header *aIcmpHeader);

/**
 * 此结构实现ICMPv6消息处理程序。
 *
 */
typedef struct otIcmp6Handler
{
    otIcmp6ReceiveCallback mReceiveCallback; ///<ICMPv6收到回调
    void *                 mContext;         ///<指向任意上下文信息的指针。
    struct otIcmp6Handler *mNext;            ///<指向列表中下一个处理程序的指针。
} otIcmp6Handler;

/**
 * ICMPv6回显应答模式
 *
 */
typedef enum otIcmp6EchoMode
{
    OT_ICMP6_ECHO_HANDLER_DISABLED       = 0, ///<ICMPv6回声处理已禁用
    OT_ICMP6_ECHO_HANDLER_UNICAST_ONLY   = 1, ///<ICMPv6仅对单播请求启用回显处理
    OT_ICMP6_ECHO_HANDLER_MULTICAST_ONLY = 2, ///<ICMPv6仅对多播请求启用回显处理
    OT_ICMP6_ECHO_HANDLER_ALL            = 3, ///<ICMPv6已为单播和多播请求启用回显处理
} otIcmp6EchoMode;

/**
 * 此函数指示是否启用ICMPv6 Echo处理。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ICMP6_ECHO_HANDLER_DISABLED ICMPv6回波处理已禁用。
 * @retval OT_ICMP6_ECHO_HANDLER_UNICAST_ONLY ICMPv6仅对单播请求启用回声处理
 * @retval OT_ICMP6_ECHO_HANDLER_MULTICAST_ONLY ICMPv6仅对多播请求启用回显处理
 * @retval OT_ICMP6_ECHO_HANDLER_ALL ICMPv6 ECHO处理已为单播和多播请求启用
 *
 */
otIcmp6EchoMode otIcmp6GetEchoMode(otInstance *aInstance);

/**
 * 此函数设置是否启用ICMPv6 Echo处理。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aMode     ICMPv6 Echo处理模式。
 *
 */
void otIcmp6SetEchoMode(otInstance *aInstance, otIcmp6EchoMode aMode);

/**
 * 此函数注册处理程序以提供接收到的ICMPv6消息。
 *
 * @note 处理程序结构@paHandler必须存储在持久（静态）内存中。OpenThread不会复制处理程序结构。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aHandler  指向处理程序的指针，该处理程序包含在接收ICMPv6消息时调用的回调。
 *
 */
otError otIcmp6RegisterHandler(otInstance *aInstance, otIcmp6Handler *aHandler);

/**
 * 此函数通过线程接口发送ICMPv6回声请求。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向包含ICMPv6有效负载的消息缓冲区的指针。
 * @param[in]  aMessageInfo  对与@p aMessage关联的消息信息的引用。
 * @param[in]  aIdentifier   用于帮助将回显答复与此回显请求匹配的标识符。可能为零。
 *
 */
otError otIcmp6SendEchoRequest(otInstance *         aInstance,
                               otMessage *          aMessage,
                               const otMessageInfo *aMessageInfo,
                               uint16_t             aIdentifier);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_ICMP6_H_

