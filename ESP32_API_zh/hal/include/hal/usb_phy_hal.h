/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "usb_types_private.h"
#include "usb_phy_types.h"
#include "soc/soc_caps.h"
#include "soc/usb_wrap_struct.h"
#if SOC_USB_SERIAL_JTAG_SUPPORTED
#include "soc/usb_serial_jtag_struct.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    usb_wrap_dev_t *wrap_dev;                   /**<指向USB包装器寄存器基址的指针*/
#if SOC_USB_SERIAL_JTAG_SUPPORTED
    usb_serial_jtag_dev_t *jtag_dev;            /**<指向USB串行JTAG寄存器基址的指针*/
#endif
} usb_phy_hal_context_t;

/**
 * @brief 初始化USB PHY hal。在调用其他hal层函数之前，应先调用此函数
 *
 * @param hal HAL层的上下文
 */
void usb_phy_hal_init(usb_phy_hal_context_t *hal);

/**
 * @brief 为USB_OTG配置内部/外部PHY
 *
 * @param hal HAL层的上下文
 * @param phy_target USB PHY目标
 */
void usb_phy_hal_otg_conf(usb_phy_hal_context_t *hal, usb_phy_target_t phy_target);

#if SOC_USB_SERIAL_JTAG_SUPPORTED
/**
 * @brief 为USB_Serial_JTAG配置内部/外部PHY
 *
 * @param hal HAL层的上下文
 * @param phy_target USB PHY目标
 */
void usb_phy_hal_jtag_conf(usb_phy_hal_context_t *hal, usb_phy_target_t phy_target);
#endif

/**
 * @brief 配置D+/D-作为主机的上拉/下拉负载
 *
 * @param hal HAL层的上下文
 */
void usb_phy_hal_int_load_conf_host(usb_phy_hal_context_t *hal);

/**
 * @brief 将D+/D-作为设备配置上拉/下拉负载
 *
 * @param hal HAL层的上下文
 * @param speed USB速度
 */
void usb_phy_hal_int_load_conf_dev(usb_phy_hal_context_t *hal, usb_priv_speed_t speed);

/**
 * @brief 启用/禁用内部PHY的测试模式，以模拟主机设备断开连接
 *
 * @param hal HAL层的上下文
 * @param disconn 是否断开连接
 */
void usb_phy_hal_int_mimick_disconn(usb_phy_hal_context_t *hal, bool disconn);

#ifdef __cplusplus
}
#endif

