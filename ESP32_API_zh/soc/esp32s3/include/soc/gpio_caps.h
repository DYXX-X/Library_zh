// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ESP32-S3具有1个GPIO外围设备
#define SOC_GPIO_PORT           (1)
#define SOC_GPIO_PIN_COUNT      (49)

// 在ESP32-S3上，数字IO有自己的寄存器来控制上拉/下拉/功能，独立于RTC寄存器。
#define SOC_GPIO_SUPPORT_RTC_INDEPENDENT (1)
// 强制保持是ESP32-S3的新功能
#define SOC_GPIO_SUPPORT_FORCE_HOLD      (1)

// 0~48（22~25除外）有效
#define SOC_GPIO_VALID_GPIO_MASK         (0x1FFFFFFFFFFFFULL & ~(0ULL | BIT22 | BIT23 | BIT24 | BIT25))
// 仅输入GPIO
#define SOC_GPIO_VALID_OUTPUT_GPIO_MASK  (SOC_GPIO_VALID_GPIO_MASK)

// 支持配置休眠状态
#define SOC_GPIO_SUPPORT_SLP_SWITCH  (1)

#ifdef __cplusplus
}
#endif

