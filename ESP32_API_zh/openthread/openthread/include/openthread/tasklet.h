/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义了用于Tasklets的OpenThread API。
 */

#ifndef OPENTHREAD_TASKLET_H_
#define OPENTHREAD_TASKLET_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api小任务
 *
 * @brief 该模块包括控制线程堆栈执行的函数。
 *
 * @{
 *
 */

/**
 * 在调用时运行所有排队的OpenThread微线程。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 */
void otTaskletsProcess(otInstance *aInstance);

/**
 * 指示OpenThread是否有挂起的小任务。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 * @retval TRUE如果有挂起的微任务。
 * @retval 如果没有挂起的任务，则返回FALSE。
 *
 */
bool otTaskletsArePending(otInstance *aInstance);

/**
 * 当tasklet队列从空转换为非空时，OpenThread调用此函数。
 *
 * @param[in] aInstance 指向OpenThread实例的指针。
 *
 */
extern void otTaskletsSignalPending(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_TASKLET_H_

