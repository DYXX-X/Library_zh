// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#define SOC_TOUCH_SHIELD_CHANNEL            (14) /*!< 防水功能包括屏蔽通道（TOUCH_PAD_NUM14）*/
#define SOC_TOUCH_DENOISE_CHANNEL           (0)  /*!< T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。*/

#ifdef __cplusplus
}
#endif

