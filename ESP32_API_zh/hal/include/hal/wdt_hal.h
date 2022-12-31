// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "soc/soc_caps.h"
#include "hal/wdt_types.h"
#include "hal/mwdt_ll.h"
#include "hal/rwdt_ll.h"

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    wdt_inst_t inst;                /**<此HAL上下文正在使用哪个WDT实例（即MWDT0、MWDT1、RWDT）*/
    union {
        timg_dev_t *mwdt_dev;       /**<MWDT的起始地址*/
        rtc_cntl_dev_t *rwdt_dev;   /**<RWDT的起始地址*/
    };
} wdt_hal_context_t;

/* ----------------------------初始化和配置---------------------------*/

/**
 * @brief 初始化一个WDT关联的HAL上下文
 *
 * 此函数通过执行以下操作初始化一个WDT（MWDT0、MWDT1或RWDT）硬件：
 * -禁用WDT及其所有阶段
 * -使用默认值设置一些寄存器
 * -设置WDT源时钟预分频器（不适用于RWDT）
 * -可选地启用电平中断
 *
 * HAL上下文通过存储此WDT实例的类型（即MWDT或RWDT）以及指向相关寄存器的指针来初始化。
 *
 * @param hal HAL层的上下文
 * @param wdt_inst 要初始化哪个WDT实例（MWDT0、MWDT1或RWDT）
 * @param prescaler MWDT源时钟预分频器。未用于RWDT
 * @param enable_intr 如果为True，则启用电平中断。False禁用
 *
 * @note 尽管ESP32上的WDT具有边缘中断，但此HAL不使用它，并且将始终禁用它。
 * @note RWDT没有预分频器。它的节拍率等于其源时钟（RTC慢时钟）的频率。
 */
void wdt_hal_init(wdt_hal_context_t *hal, wdt_inst_t wdt_inst, uint32_t prescaler, bool enable_intr);

/**
 * @brief 取消WDT及其HAL上下文的初始化
 *
 * 此函数通过馈送然后禁用WDT来解除WDT的初始化。WDT的中断也被清除和禁用。HAL上下文已清除。
 *
 * @param hal HAL层的上下文
 */
void wdt_hal_deinit(wdt_hal_context_t *hal);

/**
 * @brief 配置WDT的特定阶段
 *
 * @param hal HAL层的上下文
 * @param stage 要配置的阶段（0到3）
 * @param timeout 阶段超时的WDT刻度数
 * @param behavior 舞台结束时要采取什么行动。注意，只有RWDT支持RTC复位动作。
 *
 * @note 仅当WDT解锁时才能调用此函数。首先调用wdt_hal_write_protect_disable（）。
 */
void wdt_hal_config_stage(wdt_hal_context_t *hal, wdt_stage_t stage, uint32_t timeout, wdt_stage_action_t behavior);

/* --------------------------------运行时间------------------------------*/

/**
 * @brief 禁用WDT寄存器的写保护
 *
 * @param hal HAL层的上下文
 */
void wdt_hal_write_protect_disable(wdt_hal_context_t *hal);

/**
 * @brief 启用WDT寄存器的写保护
 *
 * @param hal HAL层的上下文
 */
void wdt_hal_write_protect_enable(wdt_hal_context_t *hal);

/**
 * @brief 启用WDT
 *
 * 启用后，WDT将开始计数。此函数在启用WDT之前还为其提供数据。
 *
 * @param hal HAL层的上下文
 *
 * @note 仅当WDT解锁时才能调用此函数。首先调用wdt_hal_write_protect_disable（）。
 */
void wdt_hal_enable(wdt_hal_context_t *hal);

/**
 * @brief 禁用WDT
 *
 * @param hal HAL层的上下文
 *
 * @note 仅当WDT解锁时才能调用此函数。首先调用wdt_hal_write_protect_disable（）。
 */
void wdt_hal_disable(wdt_hal_context_t *hal);

/**
 * @brief 处理WDT中断
 *
 * 清除中断状态位并馈送WDT
 *
 * @param hal HAL层的上下文
 *
 * @note 仅当WDT解锁时才能调用此函数。首先调用wdt_hal_write_protect_disable（）。
 */
void wdt_hal_handle_intr(wdt_hal_context_t *hal);

/**
 * @brief 向WDT馈电
 *
 * 给WDT供电将重置内部计数和当前阶段。
 *
 * @param hal HAL层的上下文
 *
 * @note 仅当WDT解锁时才能调用此函数。首先调用wdt_hal_write_protect_disable（）。
 */
void wdt_hal_feed(wdt_hal_context_t *hal);

/**
 * @brief 启用/禁用WDT闪存引导模式
 *
 * @param hal HAL层的上下文
 * @param enable True表示启用闪存引导模式，false表示禁用。
 *
 * @note 即使禁用WDT，闪存启动模式也会触发超时。
 * @note 仅当WDT解锁时才能调用此函数。首先调用wdt_hal_write_protect_disable（）。
 */
void wdt_hal_set_flashboot_en(wdt_hal_context_t *hal, bool enable);

/**
 * @brief 检查WDT是否已启用
 *
 * @param hal HAL层的上下文
 * @return 如果启用，则为True，否则为false
 */
bool wdt_hal_is_enabled(wdt_hal_context_t *hal);

#ifdef __cplusplus
}
#endif

