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
    //启用内部PHY
    hw->otg_conf.pad_enable = 1;
    hw->otg_conf.phy_sel = 0;
}

/**
 * @brief 为USB_OTG配置外部PHY
 *
 * @param hw USB Wrap寄存器的起始地址
 */
static inline void usb_phy_ll_ext_otg_enable(usb_wrap_dev_t *hw)
{
    //启用外部PHY
    hw->otg_conf.phy_sel = 1;
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

