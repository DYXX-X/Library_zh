/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包含用于卡纸检测功能的OpenThread API。
 */

#ifndef OPENTHREAD_JAM_DETECTION_H_
#define OPENTHREAD_JAM_DETECTION_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api堵塞检测
 *
 * @brief 该模块包括信号干扰检测功能。
 *
 *   当堵塞检测功能（`OPENTHREAD_CONFIG_jam_detection_ENABLE`）启用时，此模块中的功能可用。
 *
 * @{
 *
 */

/**
 * 如果启用信号堵塞检测并检测到堵塞，则调用此函数指针。
 *
 * @param[in]  aJamState 当前堵塞状态（如果检测到堵塞，则为“true”，否则为“false”）。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otJamDetectionCallback)(bool aJamState, void *aContext);

/**
 * 设置干扰检测RSSI阈值（单位dBm）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aRssiThreshold  RSSI阈值。
 *
 * @retval OT_ERROR_NONE已成功设置阈值。
 *
 */
otError otJamDetectionSetRssiThreshold(otInstance *aInstance, int8_t aRssiThreshold);

/**
 * 获取干扰检测RSSI阈值（单位dBm）。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 干扰检测RSSI阈值。
 */
int8_t otJamDetectionGetRssiThreshold(otInstance *aInstance);

/**
 * 设置堵塞检测窗口（以秒为单位）。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aWindow              堵塞检测窗口（有效范围为1至63）
 *
 * @retval OT_ERROR_NONE成功设置窗口。
 * @retval OT_ERROR_INVALID_ARGS给定的输入参数不在有效范围内（1-63）
 *
 */
otError otJamDetectionSetWindow(otInstance *aInstance, uint8_t aWindow);

/**
 * 获取卡纸检测窗口（秒）。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 *
 * @returns 堵塞检测窗口。
 *
 */
uint8_t otJamDetectionGetWindow(otInstance *aInstance);

/**
 * 设置卡纸检测忙周期（以秒为单位）。
 *
 * RSSI必须高于阈值才能触发检测的检测窗口内的聚合秒数。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aBusyPeriod          卡纸检测忙期（应为非零且小于或等于卡纸检测窗口）
 *
 * @retval OT_ERROR_NONE成功设置窗口。
 * @retval OT_ERROR_INVALID_ARGS给定输入不在有效范围内。
 *
 */
otError otJamDetectionSetBusyPeriod(otInstance *aInstance, uint8_t aBusyPeriod);

/**
 * 获取卡纸检测忙周期（秒）
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 *
 * @returns 卡纸检测忙期。
 *
 */
uint8_t otJamDetectionGetBusyPeriod(otInstance *aInstance);

/**
 * 启动干扰检测。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aCallback            为通知干扰状态变化而调用的函数的指针。
 * @param[in]  aContext             指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE成功启动干扰检测。
 * @retval OT_ERROR_ALREADY卡纸检测之前已启动。
 *
 */
otError otJamDetectionStart(otInstance *aInstance, otJamDetectionCallback aCallback, void *aContext);

/**
 * 停止干扰检测。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE成功停止干扰检测。
 * @retval OT_ERROR_ALREADY卡纸检测已停止。
 *
 */
otError otJamDetectionStop(otInstance *aInstance);

/**
 * 获取卡纸检测状态（启用/禁用）
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 *
 * @returns 卡纸检测状态（如果启用，则为真，否则为假）。
 *
 */
bool otJamDetectionIsEnabled(otInstance *aInstance);

/**
 * 获取卡纸检测状态
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 *
 * @returns 卡纸检测状态（检测到“真”卡纸，否则为“假”）。
 *
 */
bool otJamDetectionGetState(otInstance *aInstance);

/**
 * 获取当前历史位图。
 *
 * 该值提供干扰检测模块的当前状态信息，用于监控/调试。它返回一个64位的值，其中每一位对应一秒的间隔，从最新间隔的位0开始，最早间隔的位63（63秒之前）。如果干扰检测模块在相应的1秒间隔内观察到/检测到高信号电平，则该位设置为1。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 *
 * @returns 当前历史位图。
 *
 */
uint64_t otJamDetectionGetHistoryBitmap(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_JAM_DETECTION_H_

