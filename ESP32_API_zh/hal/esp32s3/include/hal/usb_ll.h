// 版权所有2020 Espressif Systems（上海）私人有限公司
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


#include "soc/soc.h"
#include "soc/system_reg.h"
#include "soc/gpio_sig_map.h"
#include "soc/usb_periph.h"
#include "soc/rtc_cntl_struct.h"

static inline void usb_ll_int_phy_enable(void)
{
    USB_WRAP.otg_conf.pad_enable = 1;
    // USB_OTG使用内部PHY
    USB_WRAP.otg_conf.phy_sel = 0;
    // phy_sel由以下寄存器值控制
    RTCCNTL.usb_conf.sw_hw_usb_phy_sel = 1;
    // phy_sel=sw_usb_phy_sel=1，usb_OTG与内部phy连接
    RTCCNTL.usb_conf.sw_usb_phy_sel = 1;
}

static inline void usb_ll_ext_phy_enable(void)
{
    USB_WRAP.otg_conf.pad_enable = 1;
    // USB_OTG使用外部PHY
    USB_WRAP.otg_conf.phy_sel = 1;
    // phy_sel由以下寄存器值控制
    RTCCNTL.usb_conf.sw_hw_usb_phy_sel = 1;
    // phy_sel=sw_usb_phy_sel=0，usb_OTG通过GPIO矩阵与外部phy连接
    RTCCNTL.usb_conf.sw_usb_phy_sel = 0;
}

static inline void usb_ll_int_phy_pullup_conf(bool dp_pu, bool dp_pd, bool dm_pu, bool dm_pd)
{
    usb_wrap_otg_conf_reg_t conf = USB_WRAP.otg_conf;
    conf.pad_pull_override = 1;
    conf.dp_pullup = dp_pu;
    conf.dp_pulldown = dp_pd;
    conf.dm_pullup = dm_pu;
    conf.dm_pulldown = dm_pd;
    USB_WRAP.otg_conf = conf;
}

