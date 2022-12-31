/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件定义OpenThread示例应用程序所需的平台特定函数。
 */

#ifndef OPENTHREAD_SYSTEM_H_
#define OPENTHREAD_SYSTEM_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此函数执行OpenThread驱动程序的所有特定于平台的初始化。
 *
 * @note OpenThread库不调用此函数。相反，当OpenThread驱动程序的初始化最合适时，系统/ROS应该调用此函数。
 *
 * @param[in]  argc  @p argv中的参数数。
 * @param[in]  argv  参数向量。
 *
 */
void otSysInit(int argc, char *argv[]);

/**
 * 此函数为OpenThread的驱动程序执行所有特定于平台的去初始化。
 *
 * @note OpenThread库不调用此函数。相反，当OpenThread驱动程序的去初始化最合适时，系统/ROS应该调用此函数。
 *
 */
void otSysDeinit(void);

/**
 * 如果请求了伪重置，则此函数返回true。
 *
 * 在这种情况下，主循环应该关闭并重新初始化OpenThread实例。
 *
 * @note OpenThread库不调用此函数。相反，系统/ROS应该在主循环中调用此函数，以确定何时关闭并重新初始化OpenThread实例。
 *
 */
bool otSysPseudoResetWasRequested(void);

/**
 * 此函数为OpenThread的示例应用程序执行所有特定于平台的处理。
 *
 * @note OpenThread库不调用此函数。相反，当处理OpenThread的驱动程序最合适时，系统/ROS应该在主循环中调用此函数。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 *
 */
void otSysProcessDrivers(otInstance *aInstance);

/**
 * 每当平台驱动程序需要处理时，都会调用此函数。
 *
 * @note OpenThread库不处理此函数。相反，系统/ROS应该处理此函数，并调度对“otSysProcessDrivers（）”的调用。
 *
 */
extern void otSysEventSignalPending(void);

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_SYSTEM_H_

