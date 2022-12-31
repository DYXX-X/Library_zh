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

#define SOC_UART_FIFO_LEN          (128)      /*!< UART硬件FIFO长度*/
#define SOC_UART_BITRATE_MAX       (5000000)  /*!< UART支持的最大比特率*/

#define SOC_UART_NUM           (3)

// 当FIFO不为空且启用XOFF时，UART具有额外的TX_WAIT_END状态
#define SOC_UART_SUPPORT_FSM_TX_WAIT_SEND   (1)

#ifdef __cplusplus
}
#endif

