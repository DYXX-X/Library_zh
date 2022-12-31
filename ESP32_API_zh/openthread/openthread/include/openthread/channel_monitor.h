/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包括用于通道监控功能的OpenThread API
 */

#ifndef OPENTHREAD_CHANNEL_MONITOR_H_
#define OPENTHREAD_CHANNEL_MONITOR_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api通道监视器
 *
 * @brief 该模块包括信道监控功能。
 *
 *   启用通道监视器功能（`OPENTHREAD_CONFIG_channel_monitor_ENABLE`）时，此模块中的功能可用。
 *
 *   信道监测将定期监测所有信道，以帮助确定较干净的信道（干扰较小的信道）。
 *
 *   当信道监测激活时，执行零持续时间能量扫描，每个采样间隔在每个信道上采集单个RSSI采样。将RSSI样本与预先指定的RSSI阈值进行比较。作为信道质量的指示符，信道监测模块保持并提供在（大约）指定采样窗口（称为信道占用）内高于阈值的RSSI采样的平均速率/百分比。
 *
 * @{
 *
 */

/**
 * 此功能启用/禁用信道监控操作。
 *
 * 一旦操作开始，将清除以前收集的所有数据。但是，禁用操作后，以前收集的数据仍然有效，可以读取。
 *
 * @note 当IPv6接口启动/关闭时，OpenThread核心在内部启用/禁用通道监控操作（即，调用“otIp6SetEnabled（）”）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aEnabled        TRUE表示启用/启动信道监控操作，FALSE表示禁用/停止信道监控操作。
 *
 * @retval OT_ERROR_NONE通道监控状态成功更改
 * @retval OT_ERROR_ALREADY信道监控已处于相同状态。
 *
 */
otError otChannelMonitorSetEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 此功能指示信道监控操作是否已启用并正在运行。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns 如果启用了信道监视操作，则为TRUE，否则为FALSE。
 *
 */
bool otChannelMonitorIsEnabled(otInstance *aInstance);

/**
 * 获取通道监视采样间隔（毫秒）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  通道监视器采样间隔（毫秒）。
 *
 */
uint32_t otChannelMonitorGetSampleInterval(otInstance *aInstance);

/**
 * 获取信道监测RSSI阈值（dBm）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  RSSI阈值（dBm）。
 *
 */
int8_t otChannelMonitorGetRssiThreshold(otInstance *aInstance);

/**
 * 获取信道监测平均采样窗口长度（采样数）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  平均采样窗口。
 *
 */
uint32_t otChannelMonitorGetSampleWindow(otInstance *aInstance);

/**
 * 获取信道监测RSSI样本总数（每个信道）。
 *
 * 该计数指示自启动以来（自启用线程网络接口以来）每个通道（按通道监控模块）的采样总数。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  到目前为止（每个信道）的RSSI采样总数。
 *
 */
uint32_t otChannelMonitorGetSampleCount(otInstance *aInstance);

/**
 * 获取给定频道的当前频道占用率。
 *
 * 信道占用值表示高于RSSI阈值的RSSI样本的平均速率/百分比（“坏”RSSI样本）。
 *
 * 对于第一个“样本窗口”样本，平均值保持为实际百分比（即“坏”样本数与样本总数的比率）。在“窗口”样本之后，平均器使用指数加权移动平均值。实际上，这意味着平均值代表最新“kSampleWindow”样本具有最高权重的最多“3个窗口”最后样本。
 *
 * 最大值“0xffff”表示所有RSSI样本均高于RSSI阈值（即100%的样本为“坏”）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aChannel        获取链路占用率的信道。
 *
 * @returns 给定频道的当前频道占用率。
 *
 */
uint16_t otChannelMonitorGetChannelOccupancy(otInstance *aInstance, uint8_t aChannel);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_CHANNEL_MONITOR_H_

