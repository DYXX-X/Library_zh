/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括各种行为的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_MISC_H_
#define OPENTHREAD_PLATFORM_MISC_H_

#include <stdint.h>

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平台杂项
 *
 * @brief 该模块包括各种行为的平台抽象。
 *
 * @{
 *
 */

/**
 * 此功能在平台上执行软件重置（如果支持）。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 */
void otPlatReset(otInstance *aInstance);

/**
 * 可能重置原因代码的枚举。
 *
 * 这些与Spinel重置原因代码的顺序相同。
 *
 */
typedef enum
{
    OT_PLAT_RESET_REASON_POWER_ON = 0,
    OT_PLAT_RESET_REASON_EXTERNAL = 1,
    OT_PLAT_RESET_REASON_SOFTWARE = 2,
    OT_PLAT_RESET_REASON_FAULT    = 3,
    OT_PLAT_RESET_REASON_CRASH    = 4,
    OT_PLAT_RESET_REASON_ASSERT   = 5,
    OT_PLAT_RESET_REASON_OTHER    = 6,
    OT_PLAT_RESET_REASON_UNKNOWN  = 7,
    OT_PLAT_RESET_REASON_WATCHDOG = 8,

    OT_PLAT_RESET_REASON_COUNT,
} otPlatResetReason;

/**
 * 此函数返回上次平台重置的原因。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 */
otPlatResetReason otPlatGetResetReason(otInstance *aInstance);

/**
 * 此函数为断言提供了特定于平台的实现。
 *
 * @param[in] aFilename    发生断言的文件的名称。
 * @param[in] aLineNumber  文件中发生断言的行号。
 *
 */
void otPlatAssertFail(const char *aFilename, int aLineNumber);

/**
 * 此函数执行特定于平台的操作以唤醒主机MCU。这仅用于NCP配置。
 *
 */
void otPlatWakeHost(void);

/**
 * 微控制器电源状态的枚举。
 *
 * 当启用“OPENTHREAD_COONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL”时，这些值用于NCP配置。
 *
 * 当底层平台的操作系统进入空闲模式（即，处理所有活动任务/事件，MCU可能进入节能电源状态）时，电源状态指定NCP的微控制器（MCU）的期望电源状态。
 *
 * 电源状态主要决定主机应如何与NCP交互，以及主机在与NCP通信之前是否需要NCP的外部触发器（“poke”）。
 *
 * 重置后，MCU电源状态必须为“OT_PLAT_power_state_ON”。
 *
 */
typedef enum
{
    /**
     * NCP的MCU始终保持开启状态。
     *
     * 当NCP的所需电源状态设置为“ON”时，主机可以向NCP发送消息，而不需要任何“poke”或外部触发器。
     *
     * @note “ON”电源状态仅决定MCU的电源模式，与无线电状态无关。
     *
     */
    OT_PLAT_MCU_POWER_STATE_ON = 0,

    /**
     * NCP的MCU可以进入低功耗（节能）状态。
     *
     * 当NCP的所需功率状态设置为“LOW_power”时，主机在与NCP通信（向NCP发送消息）之前应“触发”NCP（例如，外部触发，如中断）。“poke”机制由平台代码决定（基于NCP与主机的接口）。
     *
     * 当电源状态设置为“LOW_power”时，NCP仍可（在任何时候）向主机发送消息。请注意，从NCP接收到消息并不表示NCP的电源状态已经改变，即，当主机想要与NCP通话时，主机将继续“戳”，直到电源状态被明确改变（通过成功调用“otPlatSetMcuPowerState（）”将状态改为“ON”）。
     *
     * @note “LOW_POWER”电源状态仅决定MCU的电源模式，与无线电的状态无关（无线电由OpenThread核心和设备角色管理，例如设备是否休眠。
     *
     */
    OT_PLAT_MCU_POWER_STATE_LOW_POWER = 1,

    /**
     * NCP完全关闭。
     *
     * NCP硬件复位（通过复位引脚）需要将NCP恢复到“SPINEL_MCU_POWER_STATE_ON”。复位后RAM不被保留。
     *
     */
    OT_PLAT_MCU_POWER_STATE_OFF = 2,
} otPlatMcuPowerState;

/**
 * 此功能设置所需的MCU电源状态。
 *
 * 这仅适用于启用“OPENTHREAD_COONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL”时的NCP配置。
 *
 * @param[in] aInstance      指向OpenThread实例的指针。
 * @param[in] aState         新的MCU电源状态。
 *
 * @retval OT_ERROR_NONE电源状态更新成功。
 * @retval OT_ERROR_FAILED平台不支持给定的MCU电源状态。
 *
 */
otError otPlatSetMcuPowerState(otInstance *aInstance, otPlatMcuPowerState aState);

/**
 * 此函数获取当前所需的MCU电源状态。
 *
 * 这仅适用于启用“OPENTHREAD_COONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL”时的NCP配置。
 *
 * 复位后，电源状态必须返回`OT_PLAT_power_state_ON`。在操作期间，电源状态应仅通过显式成功调用“otPlatSetMcuPowerState（）”来更改。
 *
 * @param[in] aInstance  指向OpenThread实例的指针。
 *
 * @returns 当前电源状态。
 *
 */
otPlatMcuPowerState otPlatGetMcuPowerState(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_MISC_H_

