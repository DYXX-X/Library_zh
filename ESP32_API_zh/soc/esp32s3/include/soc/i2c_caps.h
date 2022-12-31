// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

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

// ESP32-S3具有2个I2C。
#define SOC_I2C_NUM            (2)

#define SOC_I2C_FIFO_LEN       (32) /*!< I2C硬件FIFO深度*/

//ESP32-S3支持硬件FSM重置
#define SOC_I2C_SUPPORT_HW_FSM_RST  (1)
//ESP32-S3支持硬件清除总线
#define SOC_I2C_SUPPORT_HW_CLR_BUS  (1)

#define SOC_I2C_SUPPORT_XTAL       (1)
#define SOC_I2C_SUPPORT_RTC        (1)

#ifdef __cplusplus
}
#endif

