/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包括OpenThread API for Channel Manager模块。
 */

#ifndef OPENTHREAD_CHANNEL_MANAGER_H_
#define OPENTHREAD_CHANNEL_MANAGER_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api通道管理器
 *
 * @brief 此模块包括Channel Manager的功能。
 *
 *   启用Channel Manager功能（`OPENTHREAD_CONFIG_Channel_Manager_ENABLE`）时，此模块中的功能可用。Channel Manager仅在FTD版本上可用。
 *
 * @{
 *
 */

/**
 * 此函数请求线程网络频道更改。
 *
 * 网络在指定的延迟后切换到给定的信道（请参见otChannelManagerSetDelay（））。通过更新待定操作数据集来执行频道更改。
 *
 * 对该功能的后续调用将取消先前请求的正在进行的频道更改。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aChannel           线程网络的新通道。
 *
 */
void otChannelManagerRequestChannelChange(otInstance *aInstance, uint8_t aChannel);

/**
 * 此函数获取上次成功调用`otChannelManagerRequestChannelChange（）的通道`
 *
 * @returns 最后一个请求的频道，如果还没有频道更改请求，则为零。
 *
 */
uint8_t otChannelManagerGetRequestedChannel(otInstance *aInstance);

/**
 * 此函数获取Channel Manager用于频道更改的延迟（以秒为单位）。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 *
 * @returns 频道更改的延迟（秒）。
 *
 */
uint16_t otChannelManagerGetDelay(otInstance *aInstance);

/**
 * 此功能设置用于频道更改的延迟（以秒为单位）。
 *
 * 延迟最好应长于线程网络内所有休眠终端设备使用的最大数据轮询间隔。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aDelay             延迟（秒）。
 *
 * @retval OT_ERROR_NONE延迟已成功更新。
 * @retval OT_ERROR_INVALID_ARGS给定的延迟@p aDelay太短。
 *
 */
otError otChannelManagerSetDelay(otInstance *aInstance, uint16_t aDelay);

/**
 * 此函数请求“ChannelManager”检查并选择新频道并开始频道更改。
 *
 * 与“otChannelManagerRequestChannelChange（）”不同，该函数要求“ChannelManager”自行选择频道（基于收集的频道质量信息）。
 *
 * 一旦调用，Channel Manager将执行以下3个步骤：
 *
 * 1） “ChannelManager”决定频道更改是否有用。如果“aSkipQualityCheck”设置为true（强制进行频道选择并跳过质量检查），则可以跳过此检查。该步骤使用设备上收集的链路质量度量（例如CCA故障率、每个邻居的帧和消息错误率等）来确定当前信道质量是否处于证明信道改变合理的水平。
 *
 * 2） 如果第一步通过，则“ChannelManager”选择一个可能更好的频道。它使用“ChannelMonitor”模块收集的信道质量数据。在此步骤中使用受支持和受支持的频道。（请参见otChannelManagerSetSupportedChannels（）和otChannelManagementSetFavoredChannel（））。
 *
 * 3） 如果新选择的频道与当前频道不同，则“ChannelManager”请求/启动频道更改过程（内部调用“RequestChannelChange（）”）。
 *
 * @param[in] aInstance                指向OpenThread实例的指针。
 * @param[in] aSkipQualityCheck        指示是否应跳过质量检查（步骤1）。
 *
 * @retval OT_ERROR_NONE频道选择成功完成。
 * @retval OT_ERROR_NOT_FOUND支持的信道掩码为空，因此无法选择信道。
 *
 */
otError otChannelManagerRequestChannelSelect(otInstance *aInstance, bool aSkipQualityCheck);

/**
 * 此功能启用/禁用自动频道选择功能。
 *
 * 启用后，“ChannelManager”将定期调用“RequestChannelSelect（false）”。周期间隔可以通过“SetAutoChannelSelectionInterval（）”设置。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 * @param[in]  aEnabled     指示是启用还是禁用此功能。
 *
 */
void otChannelManagerSetAutoChannelSelectionEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此功能指示是否启用自动频道选择功能。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 启用时为TRUE，禁用时为FALSE。
 *
 */
bool otChannelManagerGetAutoChannelSelectionEnabled(otInstance *aInstance);

/**
 * 此功能设置自动频道选择功能使用的时段间隔（以秒为单位）。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 * @param[in] aInterval   间隔（秒）。
 *
 * @retval OT_ERROR_NONE间隔设置成功。
 * @retval OT_ERROR_INVALID_ARGS@p aInterval无效（零）。
 *
 */
otError otChannelManagerSetAutoChannelSelectionInterval(otInstance *aInstance, uint32_t aInterval);

/**
 * 此函数获取自动频道选择功能使用的时段间隔（以秒为单位）。
 *
 * @param[in]  aInstance    指向OpenThread实例的指针。
 *
 * @returns 间隔（秒）。
 *
 */
uint32_t otChannelManagerGetAutoChannelSelectionInterval(otInstance *aInstance);

/**
 * 此函数获取支持的通道掩码。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  支持的通道作为位掩码。
 *
 */
uint32_t otChannelManagerGetSupportedChannels(otInstance *aInstance);

/**
 * 此函数设置支持的通道掩码。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aChannelMask  通道掩码。
 *
 */
void otChannelManagerSetSupportedChannels(otInstance *aInstance, uint32_t aChannelMask);

/**
 * 此函数获取首选频道掩码。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  最受欢迎的频道作为比特掩码。
 *
 */
uint32_t otChannelManagerGetFavoredChannels(otInstance *aInstance);

/**
 * 此函数设置首选频道掩码。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aChannelMask  通道掩码。
 *
 */
void otChannelManagerSetFavoredChannels(otInstance *aInstance, uint32_t aChannelMask);

/**
 * 此函数获取CCA故障率阈值
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 *
 * @returns  CCA故障率阈值。值0映射到0%，0xffff映射到100%。
 *
 */
uint16_t otChannelManagerGetCcaFailureRateThreshold(otInstance *aInstance);

/**
 * 此功能设置CCA故障率阈值
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aThreshold    CCA故障率阈值。值0映射到0%，0xffff映射到100%。
 *
 */
void otChannelManagerSetCcaFailureRateThreshold(otInstance *aInstance, uint16_t aThreshold);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_CHANNEL_MANAGER_H_

