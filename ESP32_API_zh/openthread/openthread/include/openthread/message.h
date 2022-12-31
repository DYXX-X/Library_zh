/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件定义了与消息缓冲区和队列相关的顶级OpenThreadAPI。
 */

#ifndef OPENTHREAD_MESSAGE_H_
#define OPENTHREAD_MESSAGE_H_

#include <openthread/instance.h>
#include <openthread/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api消息
 *
 * @brief 此模块包括操作OpenThread消息缓冲区的函数。
 *
 * @{
 *
 */

/**
 * 此类型是OpenThread消息缓冲区的不透明表示。
 *
 */
typedef struct otMessage otMessage;

/**
 * 此结构表示消息缓冲区信息。
 *
 */
typedef struct otBufferInfo
{
    uint16_t mTotalBuffers;            ///<池中缓冲区的数量。
    uint16_t mFreeBuffers;             ///<可用消息缓冲区的数量。
    uint16_t m6loSendMessages;         ///<6lo发送队列中的消息数。
    uint16_t m6loSendBuffers;          ///<6lo发送队列中的缓冲区数。
    uint16_t m6loReassemblyMessages;   ///＜6LoWPAN重新组装队列中的消息数。
    uint16_t m6loReassemblyBuffers;    ///<6LoWPAN重新组装队列中的缓冲区数。
    uint16_t mIp6Messages;             ///<IPv6发送队列中的消息数。
    uint16_t mIp6Buffers;              ///<IPv6发送队列中的缓冲区数。
    uint16_t mMplMessages;             ///<MPL发送队列中的消息数。
    uint16_t mMplBuffers;              ///<MPL发送队列中的缓冲区数。
    uint16_t mMleMessages;             ///<MLE发送队列中的消息数。
    uint16_t mMleBuffers;              ///<MLE发送队列中的缓冲区数。
    uint16_t mArpMessages;             ///<ARP发送队列中的消息数。
    uint16_t mArpBuffers;              ///<ARP发送队列中的缓冲区数。
    uint16_t mCoapMessages;            ///<CoAP发送队列中的消息数。
    uint16_t mCoapBuffers;             ///<CoAP发送队列中的缓冲区数。
    uint16_t mCoapSecureMessages;      ///<CoAP安全发送队列中的消息数。
    uint16_t mCoapSecureBuffers;       ///<CoAP安全发送队列中的缓冲区数。
    uint16_t mApplicationCoapMessages; ///<应用程序CoAP发送队列中的消息数。
    uint16_t mApplicationCoapBuffers;  ///<应用程序CoAP发送队列中的缓冲区数。
} otBufferInfo;

/**
 * 此枚举定义OpenThread消息优先级。
 *
 */
typedef enum otMessagePriority
{
    OT_MESSAGE_PRIORITY_LOW    = 0, ///<低优先级。
    OT_MESSAGE_PRIORITY_NORMAL = 1, ///<正常优先级。
    OT_MESSAGE_PRIORITY_HIGH   = 2, ///<高优先级。
} otMessagePriority;

/**
 * 此结构表示消息设置。
 *
 */
typedef struct otMessageSettings
{
    bool    mLinkSecurityEnabled; ///<TRUE，如果消息应在第2层得到保护。
    uint8_t mPriority;            ///<优先级（必须是`otMessagePriority`中的`OT_MESSAGE_Priority_*`）。
} otMessageSettings;

/**
 * 释放已分配的消息缓冲区。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 *
 * @sa otMessage附加
 * @sa otMessage获取长度
 * @sa otMessageSet长度
 * @sa otMessage获取偏移
 * @sa otMessageSet偏移
 * @sa otMessage读取
 * @sa otMessage写入
 *
 */
void otMessageFree(otMessage *aMessage);

/**
 * 获取消息长度（字节）。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 *
 * @returns 消息长度（字节）。
 *
 * @sa otMessage自由
 * @sa otMessage附加
 * @sa otMessageSet长度
 * @sa otMessage获取偏移
 * @sa otMessageSet偏移
 * @sa otMessage读取
 * @sa otMessage写入
 * @sa otMessageSet长度
 *
 */
uint16_t otMessageGetLength(const otMessage *aMessage);

/**
 * 以字节为单位设置消息长度。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 * @param[in]  aLength   以字节为单位的长度。
 *
 * @retval OT_ERROR_NONE成功设置消息长度。
 * @retval OT_ERROR_NO_BUFS没有可用的缓冲区来增长消息。
 *
 * @sa otMessage自由
 * @sa otMessage附加
 * @sa otMessage获取长度
 * @sa otMessage获取偏移
 * @sa otMessageSet偏移
 * @sa otMessage读取
 * @sa otMessage写入
 *
 */
otError otMessageSetLength(otMessage *aMessage, uint16_t aLength);

/**
 * 获取以字节为单位的消息偏移量。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 *
 * @returns 消息偏移值。
 *
 * @sa otMessage自由
 * @sa otMessage附加
 * @sa otMessage获取长度
 * @sa otMessageSet长度
 * @sa otMessageSet偏移
 * @sa otMessage读取
 * @sa otMessage写入
 *
 */
uint16_t otMessageGetOffset(const otMessage *aMessage);

/**
 * 以字节为单位设置消息偏移量。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 * @param[in]  aOffset   以字节为单位的偏移量。
 *
 * @sa otMessage自由
 * @sa otMessage附加
 * @sa otMessage获取长度
 * @sa otMessageSet长度
 * @sa otMessage获取偏移
 * @sa otMessage读取
 * @sa otMessage写入
 *
 */
void otMessageSetOffset(otMessage *aMessage, uint16_t aOffset);

/**
 * 此函数指示是否为消息启用了链接安全性。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 *
 * @retval TRUE如果启用了链接安全性。
 * @retval FALSE如果未启用链接安全性。
 *
 */
bool otMessageIsLinkSecurityEnabled(const otMessage *aMessage);

/**
 * 此功能设置/强制使用直接传输转发消息。新邮件的默认设置为“false”。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 * @param[in]  aEnabled  如果“true”，则强制消息使用直接传输。如果“false”，则消息遵循正常过程。
 *
 */
void otMessageSetDirectTransmission(otMessage *aMessage, bool aEnabled);

/**
 * 此函数返回与消息相关联的平均RSS（接收信号强度）。
 *
 * @returns 平均RSS值（单位dBm）或OT_RADIO_RSSI_INVALID（如果没有可用的平均RSS）。
 *
 */
int8_t otMessageGetRss(const otMessage *aMessage);

/**
 * 将字节附加到消息。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 * @param[in]  aBuf      指向要附加的数据的指针。
 * @param[in]  aLength   要追加的字节数。
 *
 * @retval OT_ERROR_NONE成功附加到消息
 * @retval OT_ERROR_NO_BUFS没有可用的缓冲区来增长消息。
 *
 * @sa otMessage自由
 * @sa otMessage获取长度
 * @sa otMessageSet长度
 * @sa otMessage获取偏移
 * @sa otMessageSet偏移
 * @sa otMessage读取
 * @sa otMessage写入
 *
 */
otError otMessageAppend(otMessage *aMessage, const void *aBuf, uint16_t aLength);

/**
 * 从消息中读取字节。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 * @param[in]  aOffset   以字节为单位的偏移量。
 * @param[in]  aBuf      指向消息字节被读取到的缓冲区的指针。
 * @param[in]  aLength   要读取的字节数。
 *
 * @returns 读取的字节数。
 *
 * @sa otMessage自由
 * @sa otMessage附加
 * @sa otMessage获取长度
 * @sa otMessageSet长度
 * @sa otMessage获取偏移
 * @sa otMessageSet偏移
 * @sa otMessage写入
 *
 */
uint16_t otMessageRead(const otMessage *aMessage, uint16_t aOffset, void *aBuf, uint16_t aLength);

/**
 * 将字节写入消息。
 *
 * @param[in]  aMessage  指向消息缓冲区的指针。
 * @param[in]  aOffset   以字节为单位的偏移量。
 * @param[in]  aBuf      指向写入消息字节的缓冲区的指针。
 * @param[in]  aLength   要写入的字节数。
 *
 * @returns 写入的字节数。
 *
 * @sa otMessage自由
 * @sa otMessage附加
 * @sa otMessage获取长度
 * @sa otMessageSet长度
 * @sa otMessage获取偏移
 * @sa otMessageSet偏移
 * @sa otMessage读取
 *
 */
int otMessageWrite(otMessage *aMessage, uint16_t aOffset, const void *aBuf, uint16_t aLength);

/**
 * 此结构表示OpenThread消息队列。
 */
typedef struct
{
    void *mData; ///<实现使用的不透明数据。
} otMessageQueue;

/**
 * 初始化消息队列。
 *
 * 在任何其他“otMessageQueue”函数之前，必须为“otMessageQueue”实例调用一次且只能调用一次此函数。如果在初始化“otMessageQueue”之前使用了其他队列API，或者如果它被多次初始化，则该行为是未定义的。
 *
 * @param[in]  aQueue     指向消息队列的指针。
 *
 */
void otMessageQueueInit(otMessageQueue *aQueue);

/**
 * 此函数将消息添加到给定消息队列的末尾。
 *
 * @param[in]  aQueue    指向消息队列的指针。
 * @param[in]  aMessage  要添加的消息。
 *
 */
void otMessageQueueEnqueue(otMessageQueue *aQueue, otMessage *aMessage);

/**
 * 此函数在给定消息队列的开头/前面添加消息。
 *
 * @param[in]  aQueue    指向消息队列的指针。
 * @param[in]  aMessage  要添加的消息。
 *
 */
void otMessageQueueEnqueueAtHead(otMessageQueue *aQueue, otMessage *aMessage);

/**
 * 此函数用于从给定的消息队列中删除消息。
 *
 * @param[in]  aQueue    指向消息队列的指针。
 * @param[in]  aMessage  要删除的邮件。
 *
 */
void otMessageQueueDequeue(otMessageQueue *aQueue, otMessage *aMessage);

/**
 * 此函数返回指向队列头部消息的指针。
 *
 * @param[in]  aQueue    指向消息队列的指针。
 *
 * @returns  指向队列开头消息的指针，如果队列为空，则为NULL。
 *
 */
otMessage *otMessageQueueGetHead(otMessageQueue *aQueue);

/**
 * 此函数通过向前迭代（从头到尾）返回指向队列中下一条消息的指针。
 *
 * @param[in]  aQueue    指向消息队列的指针。
 * @param[in]  aMessage  指向当前消息缓冲区的指针。
 *
 * @returns  指向队列中“aMessage”之后的下一条消息的指针，如果“aMessage是队列的尾部”，则为NULL。如果“aMessage”不在队列“aQueue”中，则返回NULL。
 *
 */
otMessage *otMessageQueueGetNext(otMessageQueue *aQueue, const otMessage *aMessage);

/**
 * 获取消息缓冲区信息。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[out]  aBufferInfo  写入消息缓冲区信息的指针。
 *
 */
void otMessageGetBufferInfo(otInstance *aInstance, otBufferInfo *aBufferInfo);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_MESSAGE_H_

