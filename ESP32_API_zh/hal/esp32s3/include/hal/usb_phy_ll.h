/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include "soc/soc.h"
#include "soc/system_reg.h"
#include "soc/usb_wrap_struct.h"
#include "soc/rtc_cntl_struct.h"
#include "soc/usb_serial_jtag_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为USB_OTG配置内部PHY
 *
 * @param hw USB Wrap寄存器的起始地址
 */
static inline void usb_phy_ll_int_otg_enable(usb_wrap_dev_t *hw)
{
    hw->otg_conf.pad_enable = 1;
    // USB_OTG使用内部PHY
    hw->otg_conf.phy_sel = 0;
    // phy_sel由以下寄存器值控制
    RTCCNTL.usb_conf.sw_hw_usb_phy_sel = 1;
    // phy_sel=sw_usb_phy_sel=1，usb_OTG与内部phy连接
    RTCCNTL.usb_conf.sw_usb_phy_sel = 1;
}

/**
 * @brief 为USB_OTG配置外部PHY
 *
 * @param hw USB Wrap寄存器的起始地址
 */
static inline void usb_phy_ll_ext_otg_enable(usb_wrap_dev_t *hw)
{
    // USB_OTG使用外部PHY
    hw->otg_conf.phy_sel = 1;
    // phy_sel由以下寄存器值控制
    RTCCNTL.usb_conf.sw_hw_usb_phy_sel = 1;
    // phy_sel=sw_usb_phy_sel=0，usb_OTG通过GPIO矩阵与外部phy连接
    RTCCNTL.usb_conf.sw_usb_phy_sel = 0;
}

/**
 * @brief 为USB_Serial_JTAG配置内部PHY
 *
 * @param hw USB Serial_JTAG寄存器的起始地址
 */
static inline void usb_phy_ll_int_jtag_enable(usb_serial_jtag_dev_t *hw)
{
    // USB_Serial_JTAG使用内部PHY
    hw->conf0.phy_sel = 0;
    // 禁用软件控制USB D+D-下拉（设备FS:dp_pullup=1）
    hw->conf0.pad_pull_override = 0;
    // 启用USB pad功能
    hw->conf0.usb_pad_enable = 1;
    // phy_sel由以下寄存器值控制
    RTCCNTL.usb_conf.sw_hw_usb_phy_sel = 1;
    // phy_sel=sw_usb_phy_sel=0，usb_Serial_JTAG与内部phy连接
    RTCCNTL.usb_conf.sw_usb_phy_sel = 0;
}

/**
 * @brief 为USB_Serial_JTAG配置外部PHY
 *
 * @param hw USB Serial_JTAG寄存器的起始地址
 */
static inline void usb_phy_ll_ext_jtag_enable(usb_serial_jtag_dev_t *hw)
{
    // USB_Serial_JTAG使用外部PHY
    hw->conf0.phy_sel = 1;
    // phy_sel由以下寄存器值控制
    RTCCNTL.usb_conf.sw_hw_usb_phy_sel = 1;
    // phy_sel=sw_usb_phy_sel=1，usb_Serial_JTAG与外部phy连接
    RTCCNTL.usb_conf.sw_usb_phy_sel = 1;
}

/**
 * @brief 配置内部PHY的端口负载
 *
 * @param hw USB Wrap寄存器的起始地址
 * @param dp_pu D+上拉载荷
 * @param dp_pd D+下拉负载
 * @param dm_pu D-上拉载荷
 * @param dm_pd D-下拉荷载
 */
static inline void usb_phy_ll_int_load_conf(usb_wrap_dev_t *hw, bool dp_pu, bool dp_pd, bool dm_pu, bool dm_pd)
{
    usb_wrap_otg_conf_reg_t conf = hw->otg_conf;
    conf.pad_pull_override = 1;
    conf.dp_pullup = dp_pu;
    conf.dp_pulldown = dp_pd;
    conf.dm_pullup = dm_pu;
    conf.dm_pulldown = dm_pd;
    hw->otg_conf = conf;
}

/**
 * @brief 启用内部PHY的测试模式
 *
 * @param hw USB Wrap寄存器的起始地址
 * @param en 是否启用内部PHY的测试模式
 */
static inline void usb_phy_ll_int_enable_test_mode(usb_wrap_dev_t *hw, bool en)
{
    if (en) {
        // 清除USB_WRAP_TEST_CONF_REG
        hw->test_conf.val = 0;
        // 设置USB测试板
        hw->test_conf.test_usb_wrap_oe = 1;
        // 启用USB测试模式
        hw->test_conf.test_enable = 1;
    } else {
        hw->test_conf.test_enable = 0;
    }
}

#ifdef __cplusplus
}
#endif

