/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread平台无线电驱动程序的mac帧接口。
 *
 */

#ifndef OPENTHREAD_UTILS_MAC_FRAME_H
#define OPENTHREAD_UTILS_MAC_FRAME_H

#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此枚举指定IEEE 802.15.4地址类型。
 *
 */
typedef enum
{
    OT_MAC_ADDRESS_TYPE_NONE,     ///<无地址。
    OT_MAC_ADDRESS_TYPE_SHORT,    ///<IEEE 802.15.4短地址。
    OT_MAC_ADDRESS_TYPE_EXTENDED, ///<IEEE 802.15.4扩展地址。
} otMacAddressType;

/**
 * 此结构表示IEEE 802.15.4短地址或扩展地址。
 *
 */
typedef struct otMacAddress
{
    union
    {
        otShortAddress mShortAddress; ///<IEEE 802.15.4短地址。
        otExtAddress   mExtAddress;   ///<IEEE 802.15.4扩展地址。
    } mAddress;

    otMacAddressType mType; ///<地址类型（短、扩展或无）。
} otMacAddress;

/**
 * Check if @p aFrame是Ack帧。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  true这是一个ACK帧。
 * @retval  false它不是ACK帧。
 *
 */
bool otMacFrameIsAck(const otRadioFrame *aFrame);

/**
 * Check if @p aFrame是数据帧。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  true这是一个数据帧。
 * @retval  false它不是数据帧。
 *
 */
bool otMacFrameIsData(const otRadioFrame *aFrame);

/**
 * Check if @p aFrame是命令帧。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  true这是一个命令帧。
 * @retval  false它不是命令帧。
 *
 */
bool otMacFrameIsCommand(const otRadioFrame *aFrame);

/**
 * Check if @p aFrame是数据请求命令。
 *
 * @param[in]   aFrame          指向框架的指针。对于802.15.4-2015及以上的帧，该帧应该已经被解密。
 *
 * @retval  true这是一个数据请求命令帧。
 * @retval  false它不是数据请求命令帧。
 *
 */
bool otMacFrameIsDataRequest(const otRadioFrame *aFrame);

/**
 * Check if @p aFrame请求ACK。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  true它请求ACK。
 * @retval  false它不请求ACK。
 *
 */
bool otMacFrameIsAckRequested(const otRadioFrame *aFrame);

/**
 * Check if @p aFrame匹配@p aPandId和@p aShortAddress或@p aExtAddress。
 *
 * @param[in]   aFrame          指向框架的指针。
 * @param[in]   aPanId          要匹配的PAN id。
 * @param[in]   aShortAddress   要匹配的短地址。
 * @param[in]   aExtAddress     要匹配的扩展地址。
 *
 * @retval  true它是广播或与PAN id和其中一个地址匹配。
 * @retval  false不匹配。
 *
 */
bool otMacFrameDoesAddrMatch(const otRadioFrame *aFrame,
                             otPanId             aPanId,
                             otShortAddress      aShortAddress,
                             const otExtAddress *aExtAddress);

/**
 * 获取源MAC地址。
 *
 * @param[in]   aFrame          指向框架的指针。
 * @param[out]  aMacAddress     指向MAC地址的指针。
 *
 * @retval  OT_ERROR_NONE已成功获取源MAC地址。
 * @retval  OT_ERROR_PARSE无法分析源MAC地址。
 *
 */
otError otMacFrameGetSrcAddr(const otRadioFrame *aFrame, otMacAddress *aMacAddress);

/**
 * 获取目标MAC地址。
 *
 * @param[in]   aFrame          指向框架的指针。
 * @param[out]  aMacAddress     指向MAC地址的指针。
 *
 * @retval  OT_ERROR_NONE已成功获取目标MAC地址。
 * @retval  OT_ERROR_PARSE无法分析目标MAC地址。
 *
 */
otError otMacFrameGetDstAddr(const otRadioFrame *aFrame, otMacAddress *aMacAddress);

/**
 * 获取@p aFrame的序列。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @returns 帧的顺序。
 *
 */
uint8_t otMacFrameGetSequence(const otRadioFrame *aFrame);

/**
 * 此函数对要发送的帧执行AES CCM。
 *
 * @param[in]  aFrame       指向要发送的MAC帧缓冲区的指针。
 * @param[in]  aExtAddress  指向扩展地址的指针，将用于为AES CCM计算生成随机数。
 *
 */
void otMacFrameProcessTransmitAesCcm(otRadioFrame *aFrame, const otExtAddress *aExtAddress);

/**
 * 告诉@p aFrame的版本是否为2015。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  这是一个2015年版的框架。
 * @retval  false它不是2015版框架。
 *
 */
bool otMacFrameIsVersion2015(const otRadioFrame *aFrame);

/**
 * 为@p aFrame生成Imm Ack。
 *
 * @param[in]    aFrame             指向框架的指针。
 * @param[in]    aIsFramePending    ACK的帧挂起位的值。
 * @param[out]   aAckFrame          指向要生成的ack帧的指针。
 *
 */
void otMacFrameGenerateImmAck(const otRadioFrame *aFrame, bool aIsFramePending, otRadioFrame *aAckFrame);

/**
 * 为@p aFrame生成Enh Ack。
 *
 * @param[in]    aFrame             指向框架的指针。
 * @param[in]    aIsFramePending    ACK的帧挂起位的值。
 * @param[in]    aIeData            指向要发送的ACK的IE数据部分的指针。
 * @param[in]    aIeLength          要发送的ACK的IE数据部分的长度。
 * @param[out]   aAckFrame          指向要生成的ack帧的指针。
 *
 * @retval  OT_ERROR_NONE在@p aAckFrame中成功生成Enh Ack。
 * @retval  OT_ERROR_PARSE@p aFrame格式不正确。
 *
 */
otError otMacFrameGenerateEnhAck(const otRadioFrame *aFrame,
                                 bool                aIsFramePending,
                                 const uint8_t *     aIeData,
                                 uint8_t             aIeLength,
                                 otRadioFrame *      aAckFrame);

/**
 * 将CSL IE内容设置到框架中。
 *
 * @param[inout]    aFrame         指向要修改的帧的指针。
 * @param[in]       aCslPeriod     CSL IE中的CSL期间。
 * @param[in]       aCslPhase      CSL IE中的CSL阶段。
 *
 */
void otMacFrameSetCslIe(otRadioFrame *aFrame, uint16_t aCslPeriod, uint16_t aCslPhase);

/**
 * 告诉是否启用了@p aFrame的安全性。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  true该框架已启用安全性。
 * @retval  false该框架未启用安全性。
 *
 */
bool otMacFrameIsSecurityEnabled(otRadioFrame *aFrame);

/**
 * 告诉@p aFrame的密钥ID模式是否为1。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @retval  true帧密钥ID模式为1。
 * @retval  false未启用帧安全性或密钥ID模式不是1。
 *
 */
bool otMacFrameIsKeyIdMode1(otRadioFrame *aFrame);

/**
 * 获取@p aFrame的密钥ID。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @returns 键ID模式为1的帧的键ID。如果失败，则返回0。
 *
 */
uint8_t otMacFrameGetKeyId(otRadioFrame *aFrame);

/**
 * Set key ID to @p a具有键ID模式1的帧。
 *
 * @param[inout]    aFrame     指向要修改的帧的指针。
 * @param[in]       aKeyId     要设置到帧的关键点ID。
 *
 */
void otMacFrameSetKeyId(otRadioFrame *aFrame, uint8_t aKeyId);

/**
 * 获取@p aFrame的帧计数器。
 *
 * @param[in]   aFrame          指向框架的指针。
 *
 * @returns 帧的帧计数器。如果失败，则返回UINT32_MAX。
 *
 */
uint32_t otMacFrameGetFrameCounter(otRadioFrame *aFrame);

/**
 * 将帧计数器设置为@p aFrame。
 *
 * @param[inout]    aFrame         指向要修改的帧的指针。
 * @param[in]       aFrameCounter  帧计数器设置为帧。
 *
 */
void otMacFrameSetFrameCounter(otRadioFrame *aFrame, uint32_t aFrameCounter);

/**
 * 将CSL IE写入缓冲区（不设置IE值）。
 *
 * @param[out]  aDest    指向输出缓冲区的指针。
 *
 * @returns  写入缓冲区的字节总数（CSL IE的总长度）。
 *
 */
uint8_t otMacFrameGenerateCslIeTemplate(uint8_t *aDest);

/**
 * 将Enh ACK探测IE（具有THREAD OUI的供应商IE）写入缓冲区。
 *
 * @p aIeData可以是“NULL”。如果@p aIeData为“NULL”，则此方法将生成未设置数据的IE。这允许用户首先生成模式，然后更新值。（例如，使用`otMacFrameSetEnhAckProbeIe`）
 *
 * @param[out]  aDest          指向输出缓冲区的指针。
 * @param[in]   aIeData        指向链接度量数据的指针。
 * @param[in]   aIeDataLength  链接度量数据值的长度。应为“1”或“2”。（根据规范4.11.3.4.4.6）
 *
 * @returns  写入缓冲区的字节总数（供应商IE的总长度）。
 *
 */
uint8_t otMacFrameGenerateEnhAckProbingIe(uint8_t *aDest, const uint8_t *aIeData, uint8_t aIeDataLength);

/**
 * 设置帧中Enh ACK探测IE（具有THREAD OUI的供应商IE）的数据值。
 *
 * 如果在@p aFrame中未找到Enh ACK探测IE，则不会执行任何操作。
 *
 * @param[in]  aFrame    包含IE.的目标帧不能为“NULL”。
 * @param[in]  aData     指向数据值的指针。不得为“NULL”。
 * @param[in]  aDataLen  @p aData的长度。
 *
 */
void otMacFrameSetEnhAckProbingIe(otRadioFrame *aFrame, const uint8_t *aData, uint8_t aDataLen);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_UTILS_MAC_FRAME_H

