/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括毫秒报警服务的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_ALARM_MILLI_H_
#define OPENTHREAD_PLATFORM_ALARM_MILLI_H_

#include <stdint.h>

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板报警器
 *
 * @brief 该模块包括报警服务的平台抽象。
 *
 * @{
 *
 */

/**
 * Set the alarm to fire at @p @p aT0之后的aDt毫秒。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[in] aT0        参考时间。
 * @param[in] aDt        从@p aT0开始的时间延迟（毫秒）。
 */
void otPlatAlarmMilliStartAt(otInstance *aInstance, uint32_t aT0, uint32_t aDt);

/**
 * 停止报警。
 *
 * @param[in] aInstance  OpenThread实例结构。
 */
void otPlatAlarmMilliStop(otInstance *aInstance);

/**
 * 获取当前时间。
 *
 * @returns 当前时间（毫秒）。
 */
uint32_t otPlatAlarmMilliGetNow(void);

/**
 * 发出警报已启动的信号。
 *
 * @param[in] aInstance  OpenThread实例结构。
 */
extern void otPlatAlarmMilliFired(otInstance *aInstance);

/**
 * 向诊断模块发出警报已触发的信号。
 *
 * @param[in] aInstance  OpenThread实例结构。
 */
extern void otPlatDiagAlarmFired(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_ALARM_MILLI_H_

