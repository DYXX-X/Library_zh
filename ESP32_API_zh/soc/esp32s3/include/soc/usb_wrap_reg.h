// 版权所有2017-2021 Espressif Systems（Shanghai）PTE LTD
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
#ifndef _SOC_USB_WRAP_REG_H_
#define _SOC_USB_WRAP_REG_H_


#include "soc.h"
#ifdef __cplusplus
extern "C" {
#endif

#define USB_WRAP_OTG_CONF_REG          (DR_REG_USB_WRAP_BASE + 0x0)
/* USB_WRAP_CLK_EN:R/W；位位置：[31]；默认值：1'0；*/
/*description:禁用CSR寄存器的自动时钟门控。*/
#define USB_WRAP_CLK_EN    (BIT(31))
#define USB_WRAP_CLK_EN_M  (BIT(31))
#define USB_WRAP_CLK_EN_V  0x1
#define USB_WRAP_CLK_EN_S  31
/* USB_WRAP_DFIFO-FORCE_PU:R/W；位位置：[22]；默认值：1’b0；*/
/*description:禁用dfifo进入低功率模式。dfifo中的数据不会丢失。。*/
#define USB_WRAP_DFIFO_FORCE_PU    (BIT(22))
#define USB_WRAP_DFIFO_FORCE_PU_M  (BIT(22))
#define USB_WRAP_DFIFO_FORCE_PU_V  0x1
#define USB_WRAP_DFIFO_FORCE_PU_S  22
/* USB_WRAP_PHY_TX_EDGE_SEL:R/W；位位置：[21]；默认值：1’b0；*/
/*description:选择phy tx信号输出时钟边沿。*/
#define USB_WRAP_PHY_TX_EDGE_SEL    (BIT(21))
#define USB_WRAP_PHY_TX_EDGE_SEL_M  (BIT(21))
#define USB_WRAP_PHY_TX_EDGE_SEL_V  0x1
#define USB_WRAP_PHY_TX_EDGE_SEL_S  21
/* USB_WRAP_PHY_CLK_FORCE_ON:R/W；位位置：[20]；默认值：1’b1；*/
/*description:强制物理时钟始终打开。*/
#define USB_WRAP_PHY_CLK_FORCE_ON    (BIT(20))
#define USB_WRAP_PHY_CLK_FORCE_ON_M  (BIT(20))
#define USB_WRAP_PHY_CLK_FORCE_ON_V  0x1
#define USB_WRAP_PHY_CLK_FORCE_ON_S  20
/* USB_WRAP_AHB_CLK_FORCE_ON:R/W；位位置：[19]；默认值：1’b1；*/
/*描述：强制ahb时钟始终打开。*/
#define USB_WRAP_AHB_CLK_FORCE_ON    (BIT(19))
#define USB_WRAP_AHB_CLK_FORCE_ON_M  (BIT(19))
#define USB_WRAP_AHB_CLK_FORCE_ON_V  0x1
#define USB_WRAP_AHB_CLK_FORCE_ON_S  19
/* USB_WRAP_USB_PAD_ENABLE:R/W；位位置：[18]；默认值：1’b1；*/
/*description:启用USB pad功能。*/
#define USB_WRAP_USB_PAD_ENABLE    (BIT(18))
#define USB_WRAP_USB_PAD_ENABLE_M  (BIT(18))
#define USB_WRAP_USB_PAD_ENABLE_V  0x1
#define USB_WRAP_USB_PAD_ENABLE_S  18
/* USB_WRAP_PULLUP_VALUE:R/W；位位置：[17]；默认值：1’b0；*/
/*description:控制上拉值。*/
#define USB_WRAP_PULLUP_VALUE    (BIT(17))
#define USB_WRAP_PULLUP_VALUE_M  (BIT(17))
#define USB_WRAP_PULLUP_VALUE_V  0x1
#define USB_WRAP_PULLUP_VALUE_S  17
/* USB_WRAP_DM_PULLDOWN:R/W；位位置：[16]；默认值：1’b0；*/
/*description:控制USB D+下拉。*/
#define USB_WRAP_DM_PULLDOWN    (BIT(16))
#define USB_WRAP_DM_PULLDOWN_M  (BIT(16))
#define USB_WRAP_DM_PULLDOWN_V  0x1
#define USB_WRAP_DM_PULLDOWN_S  16
/* USB_WRAP_DM_PULLUP:R/W；位位置：[15]；默认值：1’b0；*/
/*description:控制USB D+上拉。*/
#define USB_WRAP_DM_PULLUP    (BIT(15))
#define USB_WRAP_DM_PULLUP_M  (BIT(15))
#define USB_WRAP_DM_PULLUP_V  0x1
#define USB_WRAP_DM_PULLUP_S  15
/* USB_WRAP_DP_PULLDOWN:R/W；位位置：[14]；默认值：1’b0；*/
/*description:控制USB D+下拉。*/
#define USB_WRAP_DP_PULLDOWN    (BIT(14))
#define USB_WRAP_DP_PULLDOWN_M  (BIT(14))
#define USB_WRAP_DP_PULLDOWN_V  0x1
#define USB_WRAP_DP_PULLDOWN_S  14
/* USB_WRAP_DP_PULLUP:R/W；位位置：[13]；默认值：1’b0；*/
/*description:控制USB D+上拉。*/
#define USB_WRAP_DP_PULLUP    (BIT(13))
#define USB_WRAP_DP_PULLUP_M  (BIT(13))
#define USB_WRAP_DP_PULLUP_V  0x1
#define USB_WRAP_DP_PULLUP_S  13
/* USB_WRAP_PAD_PULL_OVERRIDE:R/W；位位置：[12]；默认值：1’b0；*/
/*description:启用软件控制器USB D+D-下拉。*/
#define USB_WRAP_PAD_PULL_OVERRIDE    (BIT(12))
#define USB_WRAP_PAD_PULL_OVERRIDE_M  (BIT(12))
#define USB_WRAP_PAD_PULL_OVERRIDE_V  0x1
#define USB_WRAP_PAD_PULL_OVERRIDE_S  12
/* USB_WRAP_VREF_OVERRIDE:R/W；位位置：[11]；默认值：1’b0；*/
/*description:启用软件控制器输入阈值。*/
#define USB_WRAP_VREF_OVERRIDE    (BIT(11))
#define USB_WRAP_VREF_OVERRIDE_M  (BIT(11))
#define USB_WRAP_VREF_OVERRIDE_V  0x1
#define USB_WRAP_VREF_OVERRIDE_S  11
/* USB_WRAP_VREFL:R/W；比特位置：[10:9]；默认值：2’b0；*/
/*描述：控制单端输入低阈值，0.8V至1.04V，步进80mV。*/
#define USB_WRAP_VREFL    0x00000003
#define USB_WRAP_VREFL_M  ((USB_WRAP_VREFL_V)<<(USB_WRAP_VREFL_S))
#define USB_WRAP_VREFL_V  0x3
#define USB_WRAP_VREFL_S  9
/* USB_WRAP_VREFH:R/W；比特位置：[8:7]；默认值：2’b0；*/
/*描述：控制单端输入高阈值，1.76V至2V，步进80mV。*/
#define USB_WRAP_VREFH    0x00000003
#define USB_WRAP_VREFH_M  ((USB_WRAP_VREFH_V)<<(USB_WRAP_VREFH_S))
#define USB_WRAP_VREFH_V  0x3
#define USB_WRAP_VREFH_S  7
/* USB_WRAP_EXCHG_PINS：R/W；位位置：[6]；默认值：1’b0；*/
/*描述：USB D+D-交换。*/
#define USB_WRAP_EXCHG_PINS    (BIT(6))
#define USB_WRAP_EXCHG_PINS_M  (BIT(6))
#define USB_WRAP_EXCHG_PINS_V  0x1
#define USB_WRAP_EXCHG_PINS_S  6
/* USB_WRAP_EXCHG_PINS_OVERRIDE:R/W；位位置：[5]；默认值：1’b0；*/
/*description:启用软件控制器USB D+D-交换。*/
#define USB_WRAP_EXCHG_PINS_OVERRIDE    (BIT(5))
#define USB_WRAP_EXCHG_PINS_OVERRIDE_M  (BIT(5))
#define USB_WRAP_EXCHG_PINS_OVERRIDE_V  0x1
#define USB_WRAP_EXCHG_PINS_OVERRIDE_S  5
/* USB_WRAP_DBNCE_FLTR_BYPASS:R/W；位位置：[4]；默认值：1’b0；*/
/*description:为avaid、bvalid、vbusvalid、会话结束、id信号绕过反跳过滤器。*/
#define USB_WRAP_DBNCE_FLTR_BYPASS    (BIT(4))
#define USB_WRAP_DBNCE_FLTR_BYPASS_M  (BIT(4))
#define USB_WRAP_DBNCE_FLTR_BYPASS_V  0x1
#define USB_WRAP_DBNCE_FLTR_BYPASS_S  4
/* USB_WRAP_DFIFO-FORCE_PD:R/W；位位置：[3]；默认值：1’b0；*/
/*description:强制dfifo进入低功耗模式。dfifo中的数据不会丢失。。*/
#define USB_WRAP_DFIFO_FORCE_PD    (BIT(3))
#define USB_WRAP_DFIFO_FORCE_PD_M  (BIT(3))
#define USB_WRAP_DFIFO_FORCE_PD_V  0x1
#define USB_WRAP_DFIFO_FORCE_PD_S  3
/* USB_WRAP_PHY_SEL:R/W；位位置：[2]；默认值：1’b0；*/
/*description:选择内部外部PHY。*/
#define USB_WRAP_PHY_SEL    (BIT(2))
#define USB_WRAP_PHY_SEL_M  (BIT(2))
#define USB_WRAP_PHY_SEL_V  0x1
#define USB_WRAP_PHY_SEL_S  2
/* USB_WRAP_SRP_SESSEND值：R/W；位位置：[1]；默认值：1’b0；*/
/*描述：srp会话结束信号的软件超越值。。*/
#define USB_WRAP_SRP_SESSEND_VALUE    (BIT(1))
#define USB_WRAP_SRP_SESSEND_VALUE_M  (BIT(1))
#define USB_WRAP_SRP_SESSEND_VALUE_V  0x1
#define USB_WRAP_SRP_SESSEND_VALUE_S  1
/* USB_WRAP_SRP_SESSEND_OVERRIDE:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于启用srp会话结束信号的软件覆盖。。*/
#define USB_WRAP_SRP_SESSEND_OVERRIDE    (BIT(0))
#define USB_WRAP_SRP_SESSEND_OVERRIDE_M  (BIT(0))
#define USB_WRAP_SRP_SESSEND_OVERRIDE_V  0x1
#define USB_WRAP_SRP_SESSEND_OVERRIDE_S  0

#define USB_WRAP_TEST_CONF_REG          (DR_REG_USB_WRAP_BASE + 0x4)
/* USB_WRAP_TEST_RX_DM:RO；位位置：[6]；默认值：1’b0；*/
/*description:USB D-测试中的rx值。*/
#define USB_WRAP_TEST_RX_DM    (BIT(6))
#define USB_WRAP_TEST_RX_DM_M  (BIT(6))
#define USB_WRAP_TEST_RX_DM_V  0x1
#define USB_WRAP_TEST_RX_DM_S  6
/* USB_WRAP_TEST_RX_DP:RO；位位置：[5]；默认值：1’b0；*/
/*描述：测试中的USB D+rx值。*/
#define USB_WRAP_TEST_RX_DP    (BIT(5))
#define USB_WRAP_TEST_RX_DP_M  (BIT(5))
#define USB_WRAP_TEST_RX_DP_V  0x1
#define USB_WRAP_TEST_RX_DP_S  5
/* USB_WRAP_TEST_RX_RCV:RO；位位置：[4]；默认值：1’b0；*/
/*描述：测试中的USB差分rx值。*/
#define USB_WRAP_TEST_RX_RCV    (BIT(4))
#define USB_WRAP_TEST_RX_RCV_M  (BIT(4))
#define USB_WRAP_TEST_RX_RCV_V  0x1
#define USB_WRAP_TEST_RX_RCV_S  4
/* USB_WRAP_TEST_TX_DM:R/W；位位置：[3]；默认值：1’b0；*/
/*description:测试中的USB D-tx值。*/
#define USB_WRAP_TEST_TX_DM    (BIT(3))
#define USB_WRAP_TEST_TX_DM_M  (BIT(3))
#define USB_WRAP_TEST_TX_DM_V  0x1
#define USB_WRAP_TEST_TX_DM_S  3
/* USB_WRAP_TEST_TX_DP:R/W；位位置：[2]；默认值：1’b0；*/
/*description:测试中的USB D+tx值。*/
#define USB_WRAP_TEST_TX_DP    (BIT(2))
#define USB_WRAP_TEST_TX_DP_M  (BIT(2))
#define USB_WRAP_TEST_TX_DP_V  0x1
#define USB_WRAP_TEST_TX_DP_S  2
/* USB_WRAP_TEST_USB_OE:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：USB pad正在测试中。*/
#define USB_WRAP_TEST_USB_OE    (BIT(1))
#define USB_WRAP_TEST_USB_OE_M  (BIT(1))
#define USB_WRAP_TEST_USB_OE_V  0x1
#define USB_WRAP_TEST_USB_OE_S  1
/* USB_WRAP_TEST_ENABLE:R/W；位位置：[0]；默认值：1’b0；*/
/*description:启用USB焊盘测试。*/
#define USB_WRAP_TEST_ENABLE    (BIT(0))
#define USB_WRAP_TEST_ENABLE_M  (BIT(0))
#define USB_WRAP_TEST_ENABLE_V  0x1
#define USB_WRAP_TEST_ENABLE_S  0

#define USB_WRAP_DATE_REG          (DR_REG_USB_WRAP_BASE + 0x3FC)
/* USB_WRAP_DATE:R/W；位位置：[31:0]；默认值：32'h2102010；*/
/*description:日期寄存器。*/
#define USB_WRAP_DATE    0xFFFFFFFF
#define USB_WRAP_DATE_M  ((USB_WRAP_DATE_V)<<(USB_WRAP_DATE_S))
#define USB_WRAP_DATE_V  0xFFFFFFFF
#define USB_WRAP_DATE_S  0


#ifdef __cplusplus
}
#endif



#endif /*_SOC_USB_WRAP_REG_H_ */

