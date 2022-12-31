/*
 *  版权所有（c）2016-2017，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread操作数据集API（仅限FTD）。
 */

#ifndef OPENTHREAD_DATASET_FTD_H_
#define OPENTHREAD_DATASET_FTD_H_

#include <openthread/dataset.h>
#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api操作数据集
 *
 * @{
 *
 */

/**
 * 此方法创建一个新的操作数据集，以在形成新网络时使用。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[out] aDataset   操作数据集。
 *
 * @retval OT_ERROR_NONE已成功创建新的操作数据集。
 * @retval OT_ERROR_FAILED无法为新参数生成随机值。
 *
 */
otError otDatasetCreateNewNetwork(otInstance *aInstance, otOperationalDataset *aDataset);

/**
 * 获取最小延迟计时器。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval 最小延迟计时器的值（毫秒）。
 *
 */
uint32_t otDatasetGetDelayTimerMinimal(otInstance *aInstance);

/**
 * 设置最小延迟计时器。
 *
 * @note 此API仅用于测试和演示目的。使用此API更改设置将导致生产应用程序不符合线程规范。
 *
 * @param[in]  aInstance           指向OpenThread实例的指针。
 * @param[in]  aDelayTimerMinimal  最小延迟计时器的值（毫秒）。
 *
 * @retval  OT_ERROR_NONE成功设置最小延迟计时器。
 * @retval  OT_ERROR_INVALID_ARGS如果@p aDelayTimerMinimal无效。
 *
 */
otError otDatasetSetDelayTimerMinimal(otInstance *aInstance, uint32_t aDelayTimerMinimal);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_DATASET_FTD_H_

