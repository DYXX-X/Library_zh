/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define SOC_TOUCH_SHIELD_CHANNEL            (14) /*!< 防水功能包括屏蔽通道（TOUCH_PAD_NUM14）*/
#define SOC_TOUCH_DENOISE_CHANNEL           (0)  /*!< T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。*/

#ifdef __cplusplus
}
#endif

