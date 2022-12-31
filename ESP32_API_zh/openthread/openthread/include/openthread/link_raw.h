/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义原始OpenThread IEEE 802.15.4链路层API。
 */

#ifndef OPENTHREAD_LINK_RAW_H_
#define OPENTHREAD_LINK_RAW_H_

#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api链接原始
 *
 * @brief 该模块包括控制原始链路层配置的功能。
 *
 * @{
 *
 */

/**
 * 此函数指针指向接收到IEEE 802.15.4帧。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aFrame       指向接收帧的指针，如果接收操作被中止，则返回NULL。
 * @param[in]  aError       OT_ERROR_NONE（当成功接收到帧时）。OT_ERROR_ABORT，当接收中止且未接收到帧时。
 *
 */
typedef void (*otLinkRawReceiveDone)(otInstance *aInstance, otRadioFrame *aFrame, otError aError);

/**
 * 此功能启用/禁用原始链接层。
 *
 * @param[in] aInstance     指向OpenThread实例的指针。
 * @param[in] aCallback     指向在收到IEEE 802.15.4帧时调用的函数的指针。NULL将禁用原始链接层。
 *
 * @retval OT_ERROR_FAILED无法启用/禁用无线电。
 * @retval OT_ERROR_INVALID_STATE如果OpenThread IPv6接口已启用。
 * @retval OT_ERROR_NONE如果已成功设置启用状态。
 *
 */
otError otLinkRawSetReceiveDone(otInstance *aInstance, otLinkRawReceiveDone aCallback);

/**
 * 此函数指示是否启用了原始链接层。
 *
 * @param[in] aInstance     指向OpenThread实例的指针。
 *
 * @retval true启用原始链接层。
 * @retval false禁用原始链接层。
 *
 */
bool otLinkRawIsEnabled(otInstance *aInstance);

/**
 * 此函数获取混杂模式的状态。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @retval true混杂模式已启用。
 * @retval false混杂模式已禁用。
 *
 */
bool otLinkRawGetPromiscuous(otInstance *aInstance);

/**
 * 此函数启用或禁用混杂模式。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aEnable      启用或禁用混杂模式的值。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSetPromiscuous(otInstance *aInstance, bool aEnable);

/**
 * 设置地址筛选的短地址。
 *
 * @param[in] aInstance      指向OpenThread实例的指针。
 * @param[in] aShortAddress  IEEE 802.15.4短地址。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSetShortAddress(otInstance *aInstance, uint16_t aShortAddress);

/**
 * 将收音机从“接收”转换为“睡眠”。关掉收音机。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功转换为睡眠。
 * @retval OT_ERROR_BUSY收音机正在发射
 * @retval OT_ERROR_INVALID_STATE无线电已禁用
 *
 */
otError otLinkRawSleep(otInstance *aInstance);

/**
 * 将收音机从“睡眠”转换为“接收”。打开收音机。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功转换为接收。
 * @retval OT_ERROR_INVALID_STATE无线电已禁用或正在发送。
 *
 */
otError otLinkRawReceive(otInstance *aInstance);

/**
 * 收音机从“发射”转换为“接收”。此方法返回指向传输缓冲区的指针。
 *
 * 调用者在此缓冲区中形成IEEE 802.15.4帧，然后调用otLinkRawTransmit（）请求传输。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 指向传输缓冲区的指针，如果未启用原始链路层，则为NULL。
 *
 */
otRadioFrame *otLinkRawGetTransmitBuffer(otInstance *aInstance);

/**
 * 此函数指针指向接收到IEEE 802.15.4帧。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aFrame           指向传输的帧的指针。
 * @param[in]  aAckFrame        指向ACK帧的指针。
 * @param[in]  aError           OT_ERROR_NONE。OT_ERROR_NO_ACK（当发送帧但未收到ACK时）OT_ERROR _CHANNEL_ACCESS_FAILURE（当由于信道上的活动而无法进行传输时）。OT_ERROR_ABORT（传输因其他原因中止时）。
 *
 */
typedef void (*otLinkRawTransmitDone)(otInstance *  aInstance,
                                      otRadioFrame *aFrame,
                                      otRadioFrame *aAckFrame,
                                      otError       aError);

/**
 * 此方法开始无线电上的发射序列。
 *
 * 在请求传输之前，调用者必须在otLinkRawGetTransmitBuffer（）提供的缓冲区中形成IEEE 802.15.4帧。otRadioFrame结构中还包括信道和发射功率。
 *
 * 发射序列包括：1.将无线电从接收转换为发射。2.在给定信道上以给定发射功率发射PSDU。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aCallback    在传输完成时调用的函数的指针。
 *
 * @retval OT_ERROR_NONE已成功转换为传输。
 * @retval OT_ERROR_INVALID_STATE无线电未处于接收状态。
 *
 */
otError otLinkRawTransmit(otInstance *aInstance, otLinkRawTransmitDone aCallback);

/**
 * 获取最近的RSSI测量值。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 有效时的RSSI单位为dBm。当RSSI无效时为127。
 *
 */
int8_t otLinkRawGetRssi(otInstance *aInstance);

/**
 * 获取无线电功能。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 无线电能力位向量。堆栈基于此值启用或禁用某些函数。
 *
 */
otRadioCaps otLinkRawGetCaps(otInstance *aInstance);

/**
 * 此函数指针指向接收到IEEE 802.15.4帧。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aEnergyScanMaxRssi   扫描信道上遇到的最大RSSI。
 *
 */
typedef void (*otLinkRawEnergyScanDone)(otInstance *aInstance, int8_t aEnergyScanMaxRssi);

/**
 * 该方法开始无线电上的能量扫描序列。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aScanChannel     要执行能量扫描的通道。
 * @param[in]  aScanDuration    要扫描的通道的持续时间（毫秒）。
 * @param[in]  aCallback        完成扫描通道时调用的函数的指针。
 *
 * @retval OT_ERROR_NONE已成功开始扫描通道。
 * @retval OT_ERROR_NOT_IMPLEMENTED收音机不支持能量扫描。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawEnergyScan(otInstance *            aInstance,
                            uint8_t                 aScanChannel,
                            uint16_t                aScanDuration,
                            otLinkRawEnergyScanDone aCallback);

/**
 * 启用/禁用挂起帧的源匹配。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aEnable      启用/禁用挂起帧的源匹配。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchEnable(otInstance *aInstance, bool aEnable);

/**
 * 向源匹配表添加短地址。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aShortAddress    要添加的短地址。
 *
 * @retval OT_ERROR_NONE已成功将短地址添加到源匹配表。
 * @retval OT_ERROR_NO_BUFS源匹配表中没有可用条目。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchAddShortEntry(otInstance *aInstance, uint16_t aShortAddress);

/**
 * 向源匹配表添加扩展地址。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aExtAddress      要添加的扩展地址。
 *
 * @retval OT_ERROR_NONE已成功将扩展地址添加到源匹配表。
 * @retval OT_ERROR_NO_BUFS源匹配表中没有可用条目。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchAddExtEntry(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 正在删除源匹配表的短地址。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aShortAddress    要删除的短地址。
 *
 * @retval OT_ERROR_NONE已成功从源匹配表中删除短地址。
 * @retval OT_ERROR_NO_ADDRESS短地址不在源匹配表中。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchClearShortEntry(otInstance *aInstance, uint16_t aShortAddress);

/**
 * 正在删除收音机源匹配表的扩展地址。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aExtAddress      要删除的扩展地址。
 *
 * @retval OT_ERROR_NONE已成功从源匹配表中删除扩展地址。
 * @retval OT_ERROR_NO_ADDRESS扩展地址不在源匹配表中。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchClearExtEntry(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 从源匹配表中删除所有短地址。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchClearShortEntries(otInstance *aInstance);

/**
 * 从源匹配表中删除所有扩展地址。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSrcMatchClearExtEntries(otInstance *aInstance);

/**
 * 更新MAC密钥和密钥索引。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[in]   aKeyIdMode   钥匙ID模式。
 * @param[in]   aKeyId       关键索引。
 * @param[in]   aPrevKey     上一个MAC密钥。
 * @param[in]   aCurrKey     当前MAC密钥。
 * @param[in]   aNextKey     下一个MAC密钥。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSetMacKey(otInstance *    aInstance,
                           uint8_t         aKeyIdMode,
                           uint8_t         aKeyId,
                           const otMacKey *aPrevKey,
                           const otMacKey *aCurrKey,
                           const otMacKey *aNextKey);

/**
 * 设置当前MAC帧计数器值。
 *
 * @param[in]   aInstance         指向OpenThread实例的指针。
 * @param[in]   aMacFrameCounter  MAC帧计数器值。
 *
 * @retval OT_ERROR_NONE如果成功。
 * @retval OT_ERROR_INVALID_STATE如果未启用原始链路层。
 *
 */
otError otLinkRawSetMacFrameCounter(otInstance *aInstance, uint32_t aMacFrameCounter);

/**
 * 获取无线电芯片的当前平台时间（64位宽度）。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 当前无线电时间（以微秒为单位）。
 *
 */
uint64_t otLinkRawGetRadioTime(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_LINK_RAW_H_

