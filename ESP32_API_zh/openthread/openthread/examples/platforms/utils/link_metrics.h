/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread平台无线电驱动程序的链接度量接口。
 *
 *   该模块中定义的API可由平台用于在其无线电驱动程序中实现增强的基于ACK的探测功能（探测主题侧）。
 *
 */

#ifndef OPENTHREAD_UTILS_LINK_METRICS_H
#define OPENTHREAD_UTILS_LINK_METRICS_H

#include <openthread/link_metrics.h>

#include "mac_frame.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此方法初始化Link Metrics util模块。
 *
 * @param[in]  aNoiseFloor    Link Metrics使用的噪声下限。应将其设置为平台的噪声下限（测量的噪声下限、接收器灵敏度或常数）。
 *
 */
void otLinkMetricsInit(int8_t aNoiseFloor);

/**
 * 此方法设置/清除特定启动器的增强型基于ACK的探测。
 *
 * 此方法可以启动/停止地址为@p aShortAddress和
 * @p a外部地址。一旦探测开始，设备将记录从该邻居发送的链路层帧的链路度量数据，并将该数据包括在发送给该邻居的增强ACK中的报头IE中。
 *
 * @param[in]  aShortAddress    启动器的短地址。
 * @param[in]  aExtAddress      指向启动器扩展地址的指针。
 * @param[in]  aLinkMetrics     指定要查询的度量的标志（将省略Pdu计数）。什么时候
 *                              @p aLinkMetrics等于“0”，此方法清除启动器。
 *
 * @retval  OT_ERROR_NONE已成功配置增强型基于ACK的探测。
 * @retval  OT_ERROR_INVALID_ARGS@p aExtAddress为“nullptr”。
 * @retval  OT_ERROR_NOT_FOUND尝试清除时找不到@p aShortAddress指示的启动器。
 * @retval  OT_ERROR_NO_BUFS无法支持更多启动器。
 *
 */
otError otLinkMetricsConfigureEnhAckProbing(otShortAddress      aShortAddress,
                                            const otExtAddress *aExtAddress,
                                            otLinkMetrics       aLinkMetrics);

/**
 * 此方法生成将包含在供应商特定IE中的链接度量数据（针对确认帧进行评估）字节。
 *
 * 此方法首先检查由@p aMacAddress指示的启动器指定的链接度量。然后将值写入@paData。
 *
 * @param[in]  aMacAddress    启动器的Mac地址。
 * @param[in]  aLqi           确认帧的LQI值。
 * @param[in]  aRssi          确认帧的RSSI值。
 * @param[out] aData          指向将写入数据的缓冲区的指针。调用者应确保缓冲区的大小不小于之前配置的链接度量数据的大小。
 *
 * @returns  读取数据的大小。如果未找到启动器或@p aData无效，则将为“0”。
 *
 */
uint8_t otLinkMetricsEnhAckGenData(const otMacAddress *aMacAddress, uint8_t aLqi, int8_t aRssi, uint8_t *aData);

/**
 * 此方法返回特定启动器的增强型基于ACK的探测的数据长度。
 *
 * @param[in]  aMacAddress    启动器的Mac地址。
 *
 * @returns  数据的大小`0 `如果未为启动器配置。
 *
 */
uint8_t otLinkMetricsEnhAckGetDataLen(const otMacAddress *aMacAddress);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_UTILS_LINK_METRICS_H

