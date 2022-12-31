/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
注意：此头文件包含与USB2.0相关的类型和宏，可由DWC_OTG控制器特定的代码（即USB主机堆栈的硬件特定层）使用。因此，此标头仅用于HAL层之下（包括HAL层）。对于硬件实现不可知的类型和宏（即HCD层及以上），请将它们添加到“usb/usb_types_ch9.h”标头中。
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief USB PHY目标
 */
typedef enum {
    USB_PHY_TARGET_INT,              /**<USB目标是内部PHY*/
    USB_PHY_TARGET_EXT,              /**<USB目标是外部PHY*/
    USB_PHY_TARGET_MAX,
} usb_phy_target_t;

/**
 * @brief USB PHY源
 */
typedef enum {
    USB_PHY_CTRL_OTG,                /**<PHY控制器为USB OTG*/
#if SOC_USB_SERIAL_JTAG_SUPPORTED
    USB_PHY_CTRL_SERIAL_JTAG,        /**<PHY控制器是USB串行JTAG*/
#endif
    USB_PHY_CTRL_MAX,
} usb_phy_controller_t;

/**
 * @brief USB OTG模式
 */
typedef enum {
    USB_PHY_MODE_DEFAULT,            /**<USB OTG默认模式*/
    USB_OTG_MODE_HOST,               /**<USB OTG主机模式*/
    USB_OTG_MODE_DEVICE,             /**<USB OTG设备模式*/
    USB_OTG_MODE_MAX,
} usb_otg_mode_t;

/**
 * @brief USB速度
 */
typedef enum {
    USB_PHY_SPEED_UNDEFINED,
    USB_PHY_SPEED_LOW,              /**<USB低速（1.5 Mbit/s）*/
    USB_PHY_SPEED_FULL,             /**<USB全速（12 Mbit/s）*/
    USB_PHY_SPEED_MAX,
} usb_phy_speed_t;

#ifdef __cplusplus
}
#endif

