/*
 *  版权所有（c）2017，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包含OpenThread API for child监督功能
 */

#ifndef OPENTHREAD_CHILD_SUPERVISION_H_
#define OPENTHREAD_CHILD_SUPERVISION_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api子监控
 *
 * @brief 本模块包括儿童监护功能。
 *
 *   当启用子监控功能（`OPENTHREAD_CONFIG_child_supervision_ENABLE`）时，此模块中的功能可用。
 *
 * @{
 *
 */

/**
 * 获取儿童监护间隔（秒）。
 *
 * 儿童监护功能为家长提供了一种机制，以确保在监护间隔内向每个瞌睡的孩子发送信息。如果在监督间隔内没有传输到子级，OpenThread将进入队列，并向子级发送监督消息（具有空负载的数据消息）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  儿童监护间隔。零表示禁用儿童监护。
 *
 */
uint16_t otChildSupervisionGetInterval(otInstance *aInstance);

/**
 * 设置子监控间隔（以秒为单位）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aInterval       监督间隔（秒）。零表示禁用对父级的监督。
 *
 */
void otChildSupervisionSetInterval(otInstance *aInstance, uint16_t aInterval);

/**
 * 获取监督检查超时间隔（秒）。
 *
 * 如果设备是一个昏昏欲睡的孩子，并且在指定的检查超时内没有收到来自其父母的消息，则它将启动重新连接过程（与父母的MLE孩子更新请求/响应交换）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 *
 * @returns  监督检查超时。零表示禁用了对孩子的监督检查。
 *
 */
uint16_t otChildSupervisionGetCheckTimeout(otInstance *aInstance);

/**
 * 设置监督检查超时间隔（秒）。
 *
 * @param[in]  aInstance       指向OpenThread实例的指针。
 * @param[in]  aTimeout        检查超时（秒）。零表示禁用对孩子的监督检查。
 *
 */
void otChildSupervisionSetCheckTimeout(otInstance *aInstance, uint16_t aTimeout);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_CHILD_SUPERVISION_H_

