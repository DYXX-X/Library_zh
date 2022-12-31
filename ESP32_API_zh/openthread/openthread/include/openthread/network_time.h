/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread网络时间同步服务API。
 */

#ifndef OPENTHREAD_NETWORK_TIME_H_
#define OPENTHREAD_NETWORK_TIME_H_

#include <openthread/error.h>
#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api网络时间
 *
 * @brief 该模块包括控制网络时间同步服务的功能。
 *
 * @{
 *
 */

/**
 * 此枚举表示OpenThread时间同步状态。
 *
 */
typedef enum otNetworkTimeStatus
{
    OT_NETWORK_TIME_UNSYNCHRONIZED = -1, ///<设备尚未连接到网络。
    OT_NETWORK_TIME_RESYNC_NEEDED  = 0,  ///<设备已超过两个时间段未收到时间同步。
    OT_NETWORK_TIME_SYNCHRONIZED   = 1,  ///<设备网络时间已同步。
} otNetworkTimeStatus;

/**
 * 当发生网络时间同步或状态更改时，调用此函数指针。
 *
 */
typedef void (*otNetworkTimeSyncCallbackFn)(void *aCallbackContext);

/**
 * 零被认为是无效的时间同步序列。
 *
 */
#define OT_TIME_SYNC_INVALID_SEQ 0

/**
 * 获取线程网络时间。
 *
 * @param[in]    aInstance     OpenThread实例结构。
 * @param[inout] aNetworkTime  线程网络时间（以微秒为单位）。
 *
 * @returns 时间同步状态。
 *
 */
otNetworkTimeStatus otNetworkTimeGet(otInstance *aInstance, uint64_t *aNetworkTime);

/**
 * 设置时间同步周期。
 *
 * 只有在禁用线程协议时才能调用此函数。
 *
 * @param[in] aInstance         OpenThread实例结构。
 * @param[in] aTimeSyncPeriod   时间同步周期，以秒为单位。
 *
 * @retval OT_ERROR_NONE成功设置时间同步周期。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 */
otError otNetworkTimeSetSyncPeriod(otInstance *aInstance, uint16_t aTimeSyncPeriod);

/**
 * 获取时间同步周期。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 时间同步周期。
 *
 */
uint16_t otNetworkTimeGetSyncPeriod(otInstance *aInstance);

/**
 * 为支持路由器的设备设置时间同步XTAL精度阈值。
 *
 * 只有在禁用线程协议时才能调用此函数。
 *
 * @param[in] aInstance        OpenThread实例结构。
 * @param[in] aXTALThreshold   路由器的XTAL精度阈值（PPM）。
 *
 * @retval OT_ERROR_NONE成功设置时间同步周期。
 * @retval OT_ERROR_INVALID_STATE线程协议已启用。
 *
 */
otError otNetworkTimeSetXtalThreshold(otInstance *aInstance, uint16_t aXTALThreshold);

/**
 * 获取路由器的时间同步XTAL精度阈值。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 路由器的XTAL精度阈值（PPM）。
 *
 */
uint16_t otNetworkTimeGetXtalThreshold(otInstance *aInstance);

/**
 * 设置发生网络时间同步或状态更改时要调用的回调
 *
 * 只有当网络时间偏移跳跃OPENTHREAD_CONFIG_time_SYNC_JUMP_NOTIF_MIN_US或状态改变时，才能调用此回调。
 *
 * @param[in] aInstance OpenThread实例结构。
 * @param[in] aCallbackFn 要调用的回调函数
 * @param[in] aCallbackContext 调用时要传递给回调函数的上下文
 *
 */
void otNetworkTimeSyncSetCallback(otInstance *                aInstance,
                                  otNetworkTimeSyncCallbackFn aCallbackFn,
                                  void *                      aCallbackContext);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_NETWORK_TIME_H_

