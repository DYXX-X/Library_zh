/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包括用于ping发送方模块的OpenThread API。
 */

#ifndef OPENTHREAD_PING_SENDER_H_
#define OPENTHREAD_PING_SENDER_H_

#include <stdint.h>

#include <openthread/error.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api ping发送器
 *
 * @brief 此文件包含ping发送器模块的OpenThread API。
 *
 * @{
 *
 */

/**
 * 此结构表示ping应答。
 *
 */
typedef struct otPingSenderReply
{
    otIp6Address mSenderAddress;  ///<发件人IPv6地址（从中接收ping应答的地址）。
    uint16_t     mRoundTripTime;  ///<往返时间（毫秒）。
    uint16_t     mSize;           ///<答复中的数据大小（字节数）（不包括IPv6和ICMP6标头）。
    uint16_t     mSequenceNumber; ///<序列号。
    uint8_t      mHopLimit;       ///<跳跃限制。
} otPingSenderReply;

/**
 * 此结构表示ping请求的统计信息。
 *
 */
typedef struct otPingSenderStatistics
{
    uint16_t mSentCount;          ///<已发送的ping请求数。
    uint16_t mReceivedCount;      ///<收到的ping回复数。
    uint32_t mTotalRoundTripTime; ///<ping请求的总往返时间。
    uint16_t mMinRoundTripTime;   ///<ping请求之间的最小往返时间。
    uint16_t mMaxRoundTripTime;   ///<ping请求之间的最大往返时间。
    bool     mIsMulticast;        ///<这是否是多播ping请求。
} otPingSenderStatistics;

/**
 * 此函数指针类型指定回调以通知收到ping应答。
 *
 * @param[in] aReply      指向“otPingSenderReply”的指针，其中包含有关接收到的ping答复的信息。
 * @param[in] aContext    指向应用程序特定上下文的指针。
 *
 */
typedef void (*otPingSenderReplyCallback)(const otPingSenderReply *aReply, void *aContext);

/**
 * 此函数指针类型指定要报告ping统计信息的回调。
 *
 * @param[in] aStatistics      指向“otPingSenderStatistics”的指针，该指针包含有关接收到的ping统计信息的信息。
 * @param[in] aContext         指向应用程序特定上下文的指针。
 *
 */
typedef void (*otPingSenderStatisticsCallback)(const otPingSenderStatistics *aStatistics, void *aContext);

/**
 * 此结构表示ping请求配置。
 *
 */
typedef struct otPingSenderConfig
{
    otIp6Address              mSource;        ///<ping的源地址。
    otIp6Address              mDestination;   ///<要ping的目标地址。
    otPingSenderReplyCallback mReplyCallback; ///<报告回复的回调函数（如果不需要，可以为NULL）。
    otPingSenderStatisticsCallback
             mStatisticsCallback; ///<报告统计信息的回调函数（如果不需要，可以为NULL）。
    void *   mCallbackContext;    ///<指向回调应用程序特定上下文的指针。
    uint16_t mSize;               ///<数据大小（字节数）不包括IPv6/ICMPv6标头。默认值为零。
    uint16_t mCount;              ///<要发送的ping消息数。零将使用默认值。
    uint32_t mInterval;           ///<Ping tx间隔（毫秒）。零将使用默认值。
    uint16_t mTimeout;            ///<发送最终请求后等待最终答复的时间（毫秒）。
                                  ///<零以使用默认值。
    uint8_t mHopLimit;            ///<跃点限制（如果“mAllowZeroHopLimit”为false，则使用）。默认值为零。
    bool    mAllowZeroHopLimit;   ///<指示跃点限制是否为零。
} otPingSenderConfig;

/**
 * 此函数启动ping。
 *
 * @param[in] aInstance            指向OpenThread实例的指针。
 * @param[in] aConfig              要使用的ping配置。
 *
 * @retval OT_ERROR_NONE ping成功启动。
 * @retval OT_ERROR_BUSY无法启动，因为前一个正在进行的ping请求正忙。
 * @retval OT_ERROR_INVALID_ARGS@p aConfig包含无效参数（例如，ping间隔太长）。

 *
 */
otError otPingSenderPing(otInstance *aInstance, const otPingSenderConfig *aConfig);

/**
 * 此函数用于停止正在进行的ping。
 *
 * @param[in] aInstance            指向OpenThread实例的指针。
 *
 */
void otPingSenderStop(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PING_SENDER_H_

