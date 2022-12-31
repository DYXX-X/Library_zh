/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包含OpenThread API for Dataset Updater模块。
 */

#ifndef OPENTHREAD_DATASET_UPDATER_H_
#define OPENTHREAD_DATASET_UPDATER_H_

#include <openthread/dataset.h>
#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api操作数据集
 *
 * @brief 此模块包含数据集更新程序的函数。
 *
 *   当启用数据集更新器功能时（即“OPENTHREAD_CONFIG_Dataset_Updater_ENABLE”设置为1），此模块中的功能可用。此外，此功能仅在FTD版本上可用。
 *
 * @{
 *
 */

/**
 * 当数据集更新请求完成时，调用此回调函数指针，报告数据集更新的成功或失败状态。
 *
 * @param[in] aError   错误状态。OT_ERROR_NONE表示数据集更新成功。OT_ERROR_INVALID_STATE表示由于状态无效（MLE被禁用）而导致的故障。OT_ERROR_ALREADY表示由于网络中的另一个设备请求冲突的数据集更新而导致的故障。
 *
 * @param[in] aContext 指向任意上下文的指针（由用户在`otDatasetUpdaterRequestUpdate（）`中提供）。
 *
 */
typedef void (*otDatasetUpdaterCallback)(otError aError, void *aContext);

/**
 * 此函数请求更新操作数据集。
 *
 * @p aDataset应包含要更新的字段及其新值。它不能包含“活动”或“挂起”时间戳字段。延迟字段是可选的，如果未提供，将使用默认值（1000 ms）。
 *
 * @param[in]  aInstance               指向OpenThread实例的指针。
 * @param[in]  aDataset                指向包含要更改字段的数据集的指针。
 * @param[in]  aCallback               用于指示数据集更新请求何时完成的回调。
 * @param[in]  aContext                传递给回调的任意上下文。
 *
 * @retval OT_ERROR_NONE数据集更新已成功启动（@p aCallback将在完成时调用）。
 * @retval OT_ERROR_INVALID_STATE设备已禁用（MLE已禁用）。
 * @retval OT_ERROR_INVALID_ARGS@p aDataset无效（包含活动或待定时间戳）。
 * @retval OT_ERROR_BUSY无法启动更新，前一个更新正在进行。
 * @retval OT_ERROR_NO_BUFS无法分配缓冲区以保存数据集。
 *
 */
otError otDatasetUpdaterRequestUpdate(otInstance *                aInstance,
                                      const otOperationalDataset *aDataset,
                                      otDatasetUpdaterCallback    aCallback,
                                      void *                      aContext);

/**
 * 此函数取消正在进行的（如果有）操作数据集更新请求。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 *
 */
void otDatasetUpdaterCancelUpdate(otInstance *aInstance);

/**
 * 此函数指示是否存在正在进行的操作数据集更新请求。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 *
 * @retval TRUE正在进行更新。
 * @retval FALSE没有正在进行的更新。
 *
 */
bool otDatasetUpdaterIsUpdateOngoing(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_DATASET_UPDATER_H_

