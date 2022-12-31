/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义平台诊断接口。
 *
 */

#ifndef OPENTHREAD_PLATFORM_DIAG_H_
#define OPENTHREAD_PLATFORM_DIAG_H_

#include <stddef.h>
#include <stdint.h>

#include <openthread/error.h>
#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平台工厂诊断
 *
 * @brief 该模块包括诊断功能的平台抽象。
 *
 * @{
 *
 */

/**
 * 此功能处理工厂诊断命令行。
 *
 * The output of this function (the content written to @p aOutput）必须以“\0”结尾，并且“\0”在输出缓冲区内。
 *
 * @param[in]   aInstance       当前请求的OpenThread实例。
 * @param[in]   aArgsLength     @p aArgs中的参数数。
 * @param[in]   aArgs           诊断命令行的参数。
 * @param[out]  aOutput         诊断执行结果。
 * @param[in]   aOutputMaxLen   输出缓冲区大小。
 *
 * @retval  OT_ERROR_INVALID_ARGS支持该命令，但提供的参数无效。
 * @retval  OT_ERROR_NONE命令已成功处理。
 * @retval  OT_ERROR_INVALID_COMMAND命令无效或不受支持。
 *
 */
otError otPlatDiagProcess(otInstance *aInstance,
                          uint8_t     aArgsLength,
                          char *      aArgs[],
                          char *      aOutput,
                          size_t      aOutputMaxLen);

/**
 * 此功能启用/禁用工厂诊断模式。
 *
 * @param[in]  aMode  TRUE启用诊断模式，否则为FALSE。
 *
 */
void otPlatDiagModeSet(bool aMode);

/**
 * 此功能指示工厂诊断模式是否启用。
 *
 * @returns 如果启用了工厂诊断模式，则为TRUE，否则为FALSE。
 *
 */
bool otPlatDiagModeGet(void);

/**
 * 此功能设置用于工厂诊断的通道。
 *
 * @param[in]  aChannel  通道值。
 *
 */
void otPlatDiagChannelSet(uint8_t aChannel);

/**
 * 此功能设置用于工厂诊断的发射功率。
 *
 * @param[in]  aTxPower  发射功率值。
 *
 */
void otPlatDiagTxPowerSet(int8_t aTxPower);

/**
 * 此功能处理接收的无线帧。
 *
 * @param[in]   aInstance   当前请求的OpenThread实例。
 * @param[in]   aFrame      接收到的无线电帧。
 * @param[in]   aError      接收到的无线帧状态。
 *
 */
void otPlatDiagRadioReceived(otInstance *aInstance, otRadioFrame *aFrame, otError aError);

/**
 * 此功能处理报警事件。
 *
 * @param[in]   aInstance   当前请求的OpenThread实例。
 *
 */
void otPlatDiagAlarmCallback(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_PLATFORM_DIAG_H_

