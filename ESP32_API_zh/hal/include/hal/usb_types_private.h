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

/*
注意：此头文件包含与USB2.0相关的类型和宏，可由DWC_OTG控制器特定的代码（即USB主机堆栈的硬件特定层）使用。因此，此标头仅用于HAL层之下（包括HAL层）。对于硬件实现不可知的类型和宏（即HCD层及以上），请将它们添加到“usb/usb_types_ch9.h”标头中。
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief DWC OTG控制器支持的USB速度
 */
typedef enum {
    USB_PRIV_SPEED_FULL,
    USB_PRIV_SPEED_LOW,
} usb_priv_speed_t;

/**
 * @brief DWC OTG控制器支持的USB传输类型
 */
typedef enum {
    USB_PRIV_XFER_TYPE_CTRL,
    USB_PRIV_XFER_TYPE_ISOCHRONOUS,
    USB_PRIV_XFER_TYPE_BULK,
    USB_PRIV_XFER_TYPE_INTR,
} usb_priv_xfer_type_t;

/**
 * @brief 周期帧列表的不同可能长度的枚举
 */
typedef enum {
    USB_HAL_FRAME_LIST_LEN_8 = 8,
    USB_HAL_FRAME_LIST_LEN_16 = 16,
    USB_HAL_FRAME_LIST_LEN_32 = 32,
    USB_HAL_FRAME_LIST_LEN_64 = 64,
} usb_hal_frame_list_len_t;

/**
 * @brief 支持USB帧数的间隔（即1ms）
 */
typedef enum {
    USB_HAL_INTERVAL_1 = 1,
    USB_HAL_INTERVAL_2 = 2,
    USB_HAL_INTERVAL_4 = 4,
    USB_HAL_INTERVAL_8 = 8,
    USB_HAL_INTERVAL_16 = 16,
    USB_HAL_INTERVAL_32 = 32,
    USB_HAL_INTERVAL_64 = 64,
} usb_hal_interval_t;

#ifdef __cplusplus
}
#endif

