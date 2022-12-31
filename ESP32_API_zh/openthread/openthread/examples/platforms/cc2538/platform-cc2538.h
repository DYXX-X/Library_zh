/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括特定于平台的初始化器。
 *
 */

#ifndef PLATFORM_CC2538_H_
#define PLATFORM_CC2538_H_

#include <openthread-core-config.h>
#include <stdint.h>
#include <openthread/config.h>
#include <openthread/instance.h>

#include "cc2538-reg.h"

// 全局OpenThread实例结构
extern otInstance *sInstance;

/**
 * 初始化调试uart
 */
void cc2538DebugUartInit(void);

/**
 * 此函数初始化OpenThread使用的报警服务。
 *
 */
void cc2538AlarmInit(void);

/**
 * 此功能执行报警驱动程序处理。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 *
 */
void cc2538AlarmProcess(otInstance *aInstance);

/**
 * 此函数初始化OpenThread使用的无线电服务。
 *
 */
void cc2538RadioInit(void);

/**
 * 此功能执行无线电驱动程序处理。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 *
 */
void cc2538RadioProcess(otInstance *aInstance);

/**
 * 此函数初始化OpenThread使用的随机数服务。
 *
 */
void cc2538RandomInit(void);

/**
 * 此功能执行UART驱动程序处理。
 *
 */
void cc2538UartProcess(void);

#if OPENTHREAD_CONFIG_CC2538_WITH_CC2592 && OPENTHREAD_CONFIG_CC2592_USE_HGM
/**
 * 更改CC2592 HGM引脚的状态。
 *
 * @param	aState	Whether or 不启用HGM
 */
void cc2538RadioSetHgm(bool aState);

/**
 * 检索CC2592 HGM引脚的状态。
 */
bool cc2538RadioGetHgm(void);
#endif // OPENTHREAD_CONFIG_CC2538_WITH_CC2592 && OPENTHREAD_CONFIG_CC2592_USE_HGM

typedef enum
{
    OT_CC2538_TIMER_ENERGY_SCAN, ///<能量扫描内部计时器
    OT_CC2538_TIMERS_COUNT,      ///<内部计时器数量
} otCC2538Timer;

/**
 * 此功能设置内部计时器。
 *
 * @param[in]   aTimer  计时器标识符。
 * @param[in]   aDelay  触发计时器的延迟，且不得超过“INT32_MAX”。
 *
 */
void cc2538SetTimer(otCC2538Timer aTimer, uint32_t aDelay);

#endif // PLATFORM_CC2538_H_

