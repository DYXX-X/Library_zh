// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_SPI_REG_H_
#define _SOC_SPI_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define REG_SPI_BASE(i)     (DR_REG_SPI2_BASE + (((i)>3) ? (((i-2)* 0x1000) + 0x10000) : ((i - 2)* 0x1000 )))

#define SPI_CMD_REG(i)          (REG_SPI_BASE(i) + 0x000)
/* SPI_USR:R/W；位位置：[24]；默认值：1’b0；*/
/*description:用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。无法通过CONF_buf更改。*/
#define SPI_USR  (BIT(24))
#define SPI_USR_M  (BIT(24))
#define SPI_USR_V  0x1
#define SPI_USR_S  24
/* SPI_CONF_BITLEN:R/W；比特位置：[22:0]；默认值：23'd0；*/
/*description:定义spi_CONF状态的spi_clk周期。可在形态状态下配置。*/
#define SPI_CONF_BITLEN  0x007FFFFF
#define SPI_CONF_BITLEN_M  ((SPI_CONF_BITLEN_V)<<(SPI_CONF_BITLEN_S))
#define SPI_CONF_BITLEN_V  0x7FFFFF
#define SPI_CONF_BITLEN_S  0

#define SPI_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x004)
/* SPI_USR_ADDR_VALUE：R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:[31:8]：从设备的地址[7:0]：保留。可在形态状态下配置。*/
#define SPI_USR_ADDR_VALUE  0xFFFFFFFF
#define SPI_USR_ADDR_VALUE_M  ((SPI_USR_ADDR_VALUE_V)<<(SPI_USR_ADDR_VALUE_S))
#define SPI_USR_ADDR_VALUE_V  0xFFFFFFFF
#define SPI_USR_ADDR_VALUE_S  0

#define SPI_CTRL_REG(i)          (REG_SPI_BASE(i) + 0x008)
/* SPI_WR_BIT_ORDER:R/W；位位置：[26]；默认值：1’b0；*/
/*description:在命令地址写入数据（MOSI）阶段1:LSB首先0:MSB。可在形态状态下配置。*/
#define SPI_WR_BIT_ORDER  (BIT(26))
#define SPI_WR_BIT_ORDER_M  (BIT(26))
#define SPI_WR_BIT_ORDER_V  0x1
#define SPI_WR_BIT_ORDER_S  26
/* SPI_RD_BIT_ORDER:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：在读取数据（MISO）阶段1:LSB优先0:MSB优先。可在形态状态下配置。*/
#define SPI_RD_BIT_ORDER  (BIT(25))
#define SPI_RD_BIT_ORDER_M  (BIT(25))
#define SPI_RD_BIT_ORDER_V  0x1
#define SPI_RD_BIT_ORDER_S  25
/* SPI_WP_REG:R/W；位位置：[21]；默认值：1’b1；*/
/*description:SPI空闲时写保护信号输出。1： 输出高0：输出低。可在形态状态下配置。*/
#define SPI_WP_REG  (BIT(21))
#define SPI_WP_REG_M  (BIT(21))
#define SPI_WP_REG_V  0x1
#define SPI_WP_REG_S  21
/* SPI_D_POL:R/W；位位置：[19]；默认值：1’b1；*/
/*description:该位用于设置MOSI线极性1：高0低。可在形态状态下配置。*/
#define SPI_D_POL  (BIT(19))
#define SPI_D_POL_M  (BIT(19))
#define SPI_D_POL_V  0x1
#define SPI_D_POL_S  19
/* SPI_Q_POL:R/W；位位置：[18]；默认值：1’b1；*/
/*描述：该位用于设置MISO线极性1：高0低。可在形态状态下配置。*/
#define SPI_Q_POL  (BIT(18))
#define SPI_Q_POL_M  (BIT(18))
#define SPI_Q_POL_V  0x1
#define SPI_Q_POL_S  18
/* SPI_FREAD_OCT:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用8个信号。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_FREAD_OCT  (BIT(16))
#define SPI_FREAD_OCT_M  (BIT(16))
#define SPI_FREAD_OCT_V  0x1
#define SPI_FREAD_OCT_S  16
/* SPI_FREAD_QUAD:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用4个信号。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_FREAD_QUAD  (BIT(15))
#define SPI_FREAD_QUAD_M  (BIT(15))
#define SPI_FREAD_QUAD_V  0x1
#define SPI_FREAD_QUAD_S  15
/* SPI_FREAD_DUAL:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用2个信号。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_FREAD_DUAL  (BIT(14))
#define SPI_FREAD_DUAL_M  (BIT(14))
#define SPI_FREAD_DUAL_V  0x1
#define SPI_FREAD_DUAL_S  14
/* SPI_FCMD_OCT:R/W；位位置：[10]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用8个信号。可在形态状态下配置。*/
#define SPI_FCMD_OCT  (BIT(10))
#define SPI_FCMD_OCT_M  (BIT(10))
#define SPI_FCMD_OCT_V  0x1
#define SPI_FCMD_OCT_S  10
/* SPI_FCMD_QUAD:R/W；位位置：[9]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。*/
#define SPI_FCMD_QUAD  (BIT(9))
#define SPI_FCMD_QUAD_M  (BIT(9))
#define SPI_FCMD_QUAD_V  0x1
#define SPI_FCMD_QUAD_S  9
/* SPI_FCMD_DUAL:R/W；位位置：[8]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。*/
#define SPI_FCMD_DUAL  (BIT(8))
#define SPI_FCMD_DUAL_M  (BIT(8))
#define SPI_FCMD_DUAL_V  0x1
#define SPI_FCMD_DUAL_S  8
/* SPI_FADDR_OCT:R/W；位位置：[7]；默认值：1’b0；*/
/*description:在addr阶段1：启用0：禁用期间应用8个信号。可在形态状态下配置。*/
#define SPI_FADDR_OCT  (BIT(7))
#define SPI_FADDR_OCT_M  (BIT(7))
#define SPI_FADDR_OCT_V  0x1
#define SPI_FADDR_OCT_S  7
/* SPI_FADDR_QUAD:R/W；位位置：[6]；默认值：1’b0；*/
/*description:在addr阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。*/
#define SPI_FADDR_QUAD  (BIT(6))
#define SPI_FADDR_QUAD_M  (BIT(6))
#define SPI_FADDR_QUAD_V  0x1
#define SPI_FADDR_QUAD_S  6
/* SPI_FADDR_DUAL:R/W；位位置：[5]；默认值：1’b0；*/
/*description:在addr阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。*/
#define SPI_FADDR_DUAL  (BIT(5))
#define SPI_FADDR_DUAL_M  (BIT(5))
#define SPI_FADDR_DUAL_V  0x1
#define SPI_FADDR_DUAL_S  5
/* SPI_DUMMY_OUT:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：在虚拟阶段，spi的信号电平由spi控制器输出。可在形态状态下配置。*/
#define SPI_DUMMY_OUT  (BIT(3))
#define SPI_DUMMY_OUT_M  (BIT(3))
#define SPI_DUMMY_OUT_V  0x1
#define SPI_DUMMY_OUT_S  3
/* SPI_EXT_HOLD_EN:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置位以保持spi。该位与spi_usr_prep_hold spi_usr_cmd_hold spi_usr_addr_hold spi_usr_dummy_hold spi-usr_din_hold spi/usr_dout_hold和spi_usr_hold_pol组合。可在形态状态下配置。*/
#define SPI_EXT_HOLD_EN  (BIT(2))
#define SPI_EXT_HOLD_EN_M  (BIT(2))
#define SPI_EXT_HOLD_EN_V  0x1
#define SPI_EXT_HOLD_EN_S  2

#define SPI_CTRL1_REG(i)          (REG_SPI_BASE(i) + 0x00C)
/* SPI_CS_HOLD_DELAY：R/W；比特位置：[19:14]；默认值：6'h1；*/
/*描述：SPI cs信号被SPI时钟周期延迟。可在形态状态下配置。*/
#define SPI_CS_HOLD_DELAY  0x0000003F
#define SPI_CS_HOLD_DELAY_M  ((SPI_CS_HOLD_DELAY_V)<<(SPI_CS_HOLD_DELAY_S))
#define SPI_CS_HOLD_DELAY_V  0x3F
#define SPI_CS_HOLD_DELAY_S  14
/* SPI_W16_17_-WR_ENA:R/W；位位置：[4]；默认值：1'h1；*/
/*描述：1:reg_buf[16][17]可以写入0:reg_buf[16][17]不能写入。可在形态状态下配置。*/
#define SPI_W16_17_WR_ENA  (BIT(4))
#define SPI_W16_17_WR_ENA_M  (BIT(4))
#define SPI_W16_17_WR_ENA_V  0x1
#define SPI_W16_17_WR_ENA_S  4
/* SPI_RSCK_DATA_OUT:R/W；位位置：[3]；默认值：1'0；*/
/*description:当tsck与rsck相同时，可以节省半个周期。1： rsck posedge 0处的输出数据：tsck posedge处的输出*/
#define SPI_RSCK_DATA_OUT  (BIT(3))
#define SPI_RSCK_DATA_OUT_M  (BIT(3))
#define SPI_RSCK_DATA_OUT_V  0x1
#define SPI_RSCK_DATA_OUT_S  3
/* SPI_CLK_MODE_13:R/W；位位置：[2]；默认值：1'0；*/
/*描述：｛CPOL CPHA｝1：支持spi-clk模式1和3第一边缘输出数据B[0]/B[7]。0：支持spi-clk模式0和2第一边缘输出数据B[1]/B[6]。*/
#define SPI_CLK_MODE_13  (BIT(2))
#define SPI_CLK_MODE_13_M  (BIT(2))
#define SPI_CLK_MODE_13_V  0x1
#define SPI_CLK_MODE_13_S  2
/* SPI_CLK_MODE：R/W；位位置：[1:0]；默认值：2'h0；*/
/*description:SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。可以在CONF状态下配置。*/
#define SPI_CLK_MODE  0x00000003
#define SPI_CLK_MODE_M  ((SPI_CLK_MODE_V)<<(SPI_CLK_MODE_S))
#define SPI_CLK_MODE_V  0x3
#define SPI_CLK_MODE_S  0

#define SPI_CTRL2_REG(i)          (REG_SPI_BASE(i) + 0x010)
/* SPI_CS_DELAY_NUM:R/W；位位置：[30:29]；默认值：2'h0；*/
/*描述：spics信号被系统时钟周期延迟。可在形态状态下配置。*/
#define SPI_CS_DELAY_NUM  0x00000003
#define SPI_CS_DELAY_NUM_M  ((SPI_CS_DELAY_NUM_V)<<(SPI_CS_DELAY_NUM_S))
#define SPI_CS_DELAY_NUM_V  0x3
#define SPI_CS_DELAY_NUM_S  29
/* SPI_CS_DELAY_MODE：R/W；位位置：[28:26]；默认值：3'h0；*/
/*描述：spi_cs信号被spi_clk延迟。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，否则延迟半个循环3：延迟一个循环。可在形态状态下配置。*/
#define SPI_CS_DELAY_MODE  0x00000007
#define SPI_CS_DELAY_MODE_M  ((SPI_CS_DELAY_MODE_V)<<(SPI_CS_DELAY_MODE_S))
#define SPI_CS_DELAY_MODE_V  0x7
#define SPI_CS_DELAY_MODE_S  26
/* SPI_CS_HOLD_TIME:R/W；比特位置：[25:13]；默认值：13'h1；*/
/*描述：cs引脚的spi时钟延迟周期此位与spicshold位组合。可在形态状态下配置。*/
#define SPI_CS_HOLD_TIME  0x00001FFF
#define SPI_CS_HOLD_TIME_M  ((SPI_CS_HOLD_TIME_V)<<(SPI_CS_HOLD_TIME_S))
#define SPI_CS_HOLD_TIME_V  0x1FFF
#define SPI_CS_HOLD_TIME_S  13
/* SPI_CS_SETUP_TIME:R/W；位位置：[12:0]；默认值：13'0；*/
/*描述：spi时钟准备阶段的（周期+1）此位与spicssetup位组合。可在形态状态下配置。*/
#define SPI_CS_SETUP_TIME  0x00001FFF
#define SPI_CS_SETUP_TIME_M  ((SPI_CS_SETUP_TIME_V)<<(SPI_CS_SETUP_TIME_S))
#define SPI_CS_SETUP_TIME_V  0x1FFF
#define SPI_CS_SETUP_TIME_S  0

#define SPI_CLOCK_REG(i)          (REG_SPI_BASE(i) + 0x014)
/* SPI_CLK_EQU_SYSCLK:R/W；位位置：[31]；默认值：1’b1；*/
/*description:在主模式1中：spi_clk与系统0相等：spi_clk与系统时钟分开。可在形态状态下配置。*/
#define SPI_CLK_EQU_SYSCLK  (BIT(31))
#define SPI_CLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_CLK_EQU_SYSCLK_V  0x1
#define SPI_CLK_EQU_SYSCLK_S  31
/* SPI_CLKDIV_PRE:R/W；比特位置：[30:18]；默认值：13'b0；*/
/*description:在主模式下，它是spi_clk的预除法器。可在形态状态下配置。*/
#define SPI_CLKDIV_PRE  0x00001FFF
#define SPI_CLKDIV_PRE_M  ((SPI_CLKDIV_PRE_V)<<(SPI_CLKDIV_PRE_S))
#define SPI_CLKDIV_PRE_V  0x1FFF
#define SPI_CLKDIV_PRE_S  18
/* SPI_CLKCNT_N:R/W；比特位置：[17:12]；默认值：6'h3；*/
/*description:在主模式下，它是spi_clk的除法器。因此spi_clk频率为系统/（spi_clkdiv_pre+1）/（spi_clkcnt_N+1）。可在形态状态下配置。*/
#define SPI_CLKCNT_N  0x0000003F
#define SPI_CLKCNT_N_M  ((SPI_CLKCNT_N_V)<<(SPI_CLKCNT_N_S))
#define SPI_CLKCNT_N_V  0x3F
#define SPI_CLKCNT_N_S  12
/* SPI_CLKCNT_H:R/W；位位置：[11:6]；默认值：6'h1；*/
/*description:在主模式下，它必须是floor（（spi_clkcnt_N+1）/2-1）。在从属模式下，它必须为0。可以在CONF状态下配置。*/
#define SPI_CLKCNT_H  0x0000003F
#define SPI_CLKCNT_H_M  ((SPI_CLKCNT_H_V)<<(SPI_CLKCNT_H_S))
#define SPI_CLKCNT_H_V  0x3F
#define SPI_CLKCNT_H_S  6
/* SPI_CLKCNT_L:R/W；比特位置：[5:0]；默认值：6'h3；*/
/*description:在主模式下，它必须等于spi_clkcnt_N。在从属模式下，它必须为0。可以在CONF状态下配置。*/
#define SPI_CLKCNT_L  0x0000003F
#define SPI_CLKCNT_L_M  ((SPI_CLKCNT_L_V)<<(SPI_CLKCNT_L_S))
#define SPI_CLKCNT_L_V  0x3F
#define SPI_CLKCNT_L_S  0

#define SPI_USER_REG(i)          (REG_SPI_BASE(i) + 0x018)
/* SPI_USR_COMMAND：R/W；位位置：[31]；默认值：1’b1；*/
/*description:此位启用操作的命令阶段。可在形态状态下配置。*/
#define SPI_USR_COMMAND  (BIT(31))
#define SPI_USR_COMMAND_M  (BIT(31))
#define SPI_USR_COMMAND_V  0x1
#define SPI_USR_COMMAND_S  31
/* SPI_USR_ADDR:R/W；位位置：[30]；默认值：1’b0；*/
/*description:此位启用操作的地址阶段。可在形态状态下配置。*/
#define SPI_USR_ADDR  (BIT(30))
#define SPI_USR_ADDR_M  (BIT(30))
#define SPI_USR_ADDR_V  0x1
#define SPI_USR_ADDR_S  30
/* SPI_USR_DUMMY:R/W；位位置：[29]；默认值：1’b0；*/
/*description:此位启用操作的虚拟阶段。可在形态状态下配置。*/
#define SPI_USR_DUMMY  (BIT(29))
#define SPI_USR_DUMMY_M  (BIT(29))
#define SPI_USR_DUMMY_V  0x1
#define SPI_USR_DUMMY_S  29
/* SPI_USR_MISO:R/W；位位置：[28]；默认值：1’b0；*/
/*description:此位启用操作的读取数据阶段。可在形态状态下配置。*/
#define SPI_USR_MISO  (BIT(28))
#define SPI_USR_MISO_M  (BIT(28))
#define SPI_USR_MISO_V  0x1
#define SPI_USR_MISO_S  28
/* SPI_USR_MOSI:R/W；位位置：[27]；默认值：1’b0；*/
/*description:此位启用操作的写入数据阶段。可在形态状态下配置。*/
#define SPI_USR_MOSI  (BIT(27))
#define SPI_USR_MOSI_M  (BIT(27))
#define SPI_USR_MOSI_V  0x1
#define SPI_USR_MOSI_S  27
/* SPI_USR_dumm_IDLE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：当位被启用时，spi时钟在虚拟阶段被禁用。可在形态状态下配置。*/
#define SPI_USR_DUMMY_IDLE  (BIT(26))
#define SPI_USR_DUMMY_IDLE_M  (BIT(26))
#define SPI_USR_DUMMY_IDLE_V  0x1
#define SPI_USR_DUMMY_IDLE_S  26
/* SPI_USR_MOSI-HIGHPART:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：写入数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。*/
#define SPI_USR_MOSI_HIGHPART  (BIT(25))
#define SPI_USR_MOSI_HIGHPART_M  (BIT(25))
#define SPI_USR_MOSI_HIGHPART_V  0x1
#define SPI_USR_MOSI_HIGHPART_S  25
/* SPI_USR_MISO_HIGHPART:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：读取数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。*/
#define SPI_USR_MISO_HIGHPART  (BIT(24))
#define SPI_USR_MISO_HIGHPART_M  (BIT(24))
#define SPI_USR_MISO_HIGHPART_V  0x1
#define SPI_USR_MISO_HIGHPART_S  24
/* SPI_USR_PREP_HOLD：R/W；位位置：[23]；默认值：1’b0；*/
/*描述：spi保持在准备状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
#define SPI_USR_PREP_HOLD  (BIT(23))
#define SPI_USR_PREP_HOLD_M  (BIT(23))
#define SPI_USR_PREP_HOLD_V  0x1
#define SPI_USR_PREP_HOLD_S  23
/* SPI_USR_CMD_HOLD：R/W；位位置：[22]；默认值：1’b0；*/
/*描述：spi保持在命令状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
#define SPI_USR_CMD_HOLD  (BIT(22))
#define SPI_USR_CMD_HOLD_M  (BIT(22))
#define SPI_USR_CMD_HOLD_V  0x1
#define SPI_USR_CMD_HOLD_S  22
/* SPI_USR_ADDR_HOLD:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：spi保持在地址状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
#define SPI_USR_ADDR_HOLD  (BIT(21))
#define SPI_USR_ADDR_HOLD_M  (BIT(21))
#define SPI_USR_ADDR_HOLD_V  0x1
#define SPI_USR_ADDR_HOLD_S  21
/* SPI_USR_DUMMY_HOLD:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：spi保持在伪状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
#define SPI_USR_DUMMY_HOLD  (BIT(20))
#define SPI_USR_DUMMY_HOLD_M  (BIT(20))
#define SPI_USR_DUMMY_HOLD_V  0x1
#define SPI_USR_DUMMY_HOLD_S  20
/* SPI_USR_DIN_HOLD:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：spi保持在数据状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
#define SPI_USR_DIN_HOLD  (BIT(19))
#define SPI_USR_DIN_HOLD_M  (BIT(19))
#define SPI_USR_DIN_HOLD_V  0x1
#define SPI_USR_DIN_HOLD_S  19
/* SPI_USR_DOUT_HOLD:R/W；位位置：[18]；默认值：1’b0；*/
/*描述：spi保持在数据输出状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
#define SPI_USR_DOUT_HOLD  (BIT(18))
#define SPI_USR_DOUT_HOLD_M  (BIT(18))
#define SPI_USR_DOUT_HOLD_V  0x1
#define SPI_USR_DOUT_HOLD_S  18
/* SPI_USR_HOLD_POL:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：它与保持位相结合以设置spi保持线1的极性：当spi保持行为高时，spi将保持0：当spi保持行为低时，spi保持。可在形态状态下配置。*/
#define SPI_USR_HOLD_POL  (BIT(17))
#define SPI_USR_HOLD_POL_M  (BIT(17))
#define SPI_USR_HOLD_POL_V  0x1
#define SPI_USR_HOLD_POL_S  17
/* SPI_SIO:R/W；位位置：[16]；默认值：1’b0；*/
/*description:设置该位以启用3线半双工通信mosi和miso信号共享同一引脚。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_SIO  (BIT(16))
#define SPI_SIO_M  (BIT(16))
#define SPI_SIO_V  0x1
#define SPI_SIO_S  16
/* SPI_USR_CONF_NXT：R/W；位位置：[15]；默认值：1’b0；*/
/*description:1：启用下一个seg trans操作的DMA CONF阶段，这意味着seg trans将继续。0：分段传输将在当前SPI分段传输之后结束，或者这不是分段传输模式。可在形态状态下配置。*/
#define SPI_USR_CONF_NXT  (BIT(15))
#define SPI_USR_CONF_NXT_M  (BIT(15))
#define SPI_USR_CONF_NXT_V  0x1
#define SPI_USR_CONF_NXT_S  15
/* SPI_FWRITE_OCT:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用8个信号。可在形态状态下配置。*/
#define SPI_FWRITE_OCT  (BIT(14))
#define SPI_FWRITE_OCT_M  (BIT(14))
#define SPI_FWRITE_OCT_V  0x1
#define SPI_FWRITE_OCT_S  14
/* SPI_FWRITE_QUAD:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用4个信号。可在形态状态下配置。*/
#define SPI_FWRITE_QUAD  (BIT(13))
#define SPI_FWRITE_QUAD_M  (BIT(13))
#define SPI_FWRITE_QUAD_V  0x1
#define SPI_FWRITE_QUAD_S  13
/* SPI_FWRITE_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用2个信号。可在形态状态下配置。*/
#define SPI_FWRITE_DUAL  (BIT(12))
#define SPI_FWRITE_DUAL_M  (BIT(12))
#define SPI_FWRITE_DUAL_V  0x1
#define SPI_FWRITE_DUAL_S  12
/* SPI_WR_BYTE_ORDER:R/W；位位置：[11]；默认值：1’b0；*/
/*description:在命令地址写入数据（MOSI）阶段1:big endian 0:litte_endian。可在形态状态下配置。*/
#define SPI_WR_BYTE_ORDER  (BIT(11))
#define SPI_WR_BYTE_ORDER_M  (BIT(11))
#define SPI_WR_BYTE_ORDER_V  0x1
#define SPI_WR_BYTE_ORDER_S  11
/* SPI_RD_BYTE_ORDER:R/W；位位置：[10]；默认值：1’b0；*/
/*description:在读取数据（MISO）阶段1:big endian 0:little_endian。可在形态状态下配置。*/
#define SPI_RD_BYTE_ORDER  (BIT(10))
#define SPI_RD_BYTE_ORDER_M  (BIT(10))
#define SPI_RD_BYTE_ORDER_V  0x1
#define SPI_RD_BYTE_ORDER_S  10
/* SPI_CK_OUT_EDGE：R/W；位位置：[9]；默认值：1’b0；*/
/*描述：该位与spi_mosidelaymode位组合以设置mosi信号延迟模式。可在形态状态下配置。*/
#define SPI_CK_OUT_EDGE  (BIT(9))
#define SPI_CK_OUT_EDGE_M  (BIT(9))
#define SPI_CK_OUT_EDGE_V  0x1
#define SPI_CK_OUT_EDGE_S  9
/* SPI_rscki_EDGE:R/W；位位置：[8]；默认值：1’b0；*/
/*description:在从属模式下，此位可用于更改rsck的极性。0:rsck=！spi_ck_。1： rsck=spi_ck_i。*/
#define SPI_RSCK_I_EDGE  (BIT(8))
#define SPI_RSCK_I_EDGE_M  (BIT(8))
#define SPI_RSCK_I_EDGE_V  0x1
#define SPI_RSCK_I_EDGE_S  8
/* SPI_CS_SETUP:R/W；位位置：[7]；默认值：1’b1；*/
/*描述：当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_CS_SETUP  (BIT(7))
#define SPI_CS_SETUP_M  (BIT(7))
#define SPI_CS_SETUP_V  0x1
#define SPI_CS_SETUP_S  7
/* SPI_CS_HOLD:R/W；位位置：[6]；默认值：1’b1；*/
/*描述：当spi处于完成阶段时，spi cs保持低。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_CS_HOLD  (BIT(6))
#define SPI_CS_HOLD_M  (BIT(6))
#define SPI_CS_HOLD_V  0x1
#define SPI_CS_HOLD_S  6
/* SPI_tscki_EDGE:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：在从属模式下，此位可用于更改tsck的极性。0:tsck=spi_ck_i。1： tsck=！spi_ck_。*/
#define SPI_TSCK_I_EDGE  (BIT(5))
#define SPI_TSCK_I_EDGE_M  (BIT(5))
#define SPI_TSCK_I_EDGE_V  0x1
#define SPI_TSCK_I_EDGE_S  5
/* SPI_OPI_MODE：R/W；位位置：[4]；默认值：1’b0；*/
/*description:仅用于主模式。1： spi控制器处于OPI模式（均为8-b-m）。0：其他。可在形态状态下配置。*/
#define SPI_OPI_MODE  (BIT(4))
#define SPI_OPI_MODE_M  (BIT(4))
#define SPI_OPI_MODE_V  0x1
#define SPI_OPI_MODE_S  4
/* SPI_QPI_MODE:R/W；位位置：[3]；默认值：1’b0；*/
/*description:主模式和从模式。1： spi控制器处于QPI模式。0：其他。可在形态状态下配置。*/
#define SPI_QPI_MODE  (BIT(3))
#define SPI_QPI_MODE_M  (BIT(3))
#define SPI_QPI_MODE_V  0x1
#define SPI_QPI_MODE_S  3
/* SPI_DOUTDIN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置位以启用全双工通信。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_DOUTDIN  (BIT(0))
#define SPI_DOUTDIN_M  (BIT(0))
#define SPI_DOUTDIN_V  0x1
#define SPI_DOUTDIN_S  0

#define SPI_USER1_REG(i)          (REG_SPI_BASE(i) + 0x01C)
/* SPI_USR_ADDR_title：R/W；位位置：[31:27]；默认值：5'd23；*/
/*description:地址相位的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
#define SPI_USR_ADDR_BITLEN  0x0000001F
#define SPI_USR_ADDR_BITLEN_M  ((SPI_USR_ADDR_BITLEN_V)<<(SPI_USR_ADDR_BITLEN_S))
#define SPI_USR_ADDR_BITLEN_V  0x1F
#define SPI_USR_ADDR_BITLEN_S  27
/* SPI_USR_DUMMY_CYCLELEN:R/W；位位置：[7:0]；默认值：8'd7；*/
/*description:虚拟相位的spi_clk周期长度。寄存器值应为（cycle_num-1）。可在形态状态下配置。*/
#define SPI_USR_DUMMY_CYCLELEN  0x000000FF
#define SPI_USR_DUMMY_CYCLELEN_M  ((SPI_USR_DUMMY_CYCLELEN_V)<<(SPI_USR_DUMMY_CYCLELEN_S))
#define SPI_USR_DUMMY_CYCLELEN_V  0xFF
#define SPI_USR_DUMMY_CYCLELEN_S  0

#define SPI_USER2_REG(i)          (REG_SPI_BASE(i) + 0x020)
/* SPI_USR_COMMAND_BITLEN:R/W；位位置：[31:28]；默认值：4'd7；*/
/*description:命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
#define SPI_USR_COMMAND_BITLEN  0x0000000F
#define SPI_USR_COMMAND_BITLEN_M  ((SPI_USR_COMMAND_BITLEN_V)<<(SPI_USR_COMMAND_BITLEN_S))
#define SPI_USR_COMMAND_BITLEN_V  0xF
#define SPI_USR_COMMAND_BITLEN_S  28
/* SPI_USR_COMMAND_VALUE:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*description:命令的值。可在形态状态下配置。*/
#define SPI_USR_COMMAND_VALUE  0x0000FFFF
#define SPI_USR_COMMAND_VALUE_M  ((SPI_USR_COMMAND_VALUE_V)<<(SPI_USR_COMMAND_VALUE_S))
#define SPI_USR_COMMAND_VALUE_V  0xFFFF
#define SPI_USR_COMMAND_VALUE_S  0

#define SPI_MOSI_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x024)
/* SPI_USR_MOSI_ditlen:R/W；比特位置：[22:0]；默认值：23'0；*/
/*description:写入数据的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
#define SPI_USR_MOSI_DBITLEN  0x007FFFFF
#define SPI_USR_MOSI_DBITLEN_M  ((SPI_USR_MOSI_DBITLEN_V)<<(SPI_USR_MOSI_DBITLEN_S))
#define SPI_USR_MOSI_DBITLEN_V  0x7FFFFF
#define SPI_USR_MOSI_DBITLEN_S  0

#define SPI_MISO_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x028)
/* SPI_USR_MISO_DBITLEN:R/W；比特位置：[22:0]；默认值：23'0；*/
/*description:读取数据的位长度。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
#define SPI_USR_MISO_DBITLEN  0x007FFFFF
#define SPI_USR_MISO_DBITLEN_M  ((SPI_USR_MISO_DBITLEN_V)<<(SPI_USR_MISO_DBITLEN_S))
#define SPI_USR_MISO_DBITLEN_V  0x7FFFFF
#define SPI_USR_MISO_DBITLEN_S  0

#define SPI_MISC_REG(i)          (REG_SPI_BASE(i) + 0x02C)
/* SPI_QUAD_DIN_PIN_SWAP:R/W；位位置：[31]；默认值：1'0；*/
/*描述：1:spi四输入交换启用0:spi四输出交换禁用。可在形态状态下配置。*/
#define SPI_QUAD_DIN_PIN_SWAP  (BIT(31))
#define SPI_QUAD_DIN_PIN_SWAP_M  (BIT(31))
#define SPI_QUAD_DIN_PIN_SWAP_V  0x1
#define SPI_QUAD_DIN_PIN_SWAP_S  31
/* SPI_CS_KEEP_ACTIVE:R/W；位位置：[30]；默认值：1’b0；*/
/*描述：设置位时，spi cs线保持低电平。可在形态状态下配置。*/
#define SPI_CS_KEEP_ACTIVE  (BIT(30))
#define SPI_CS_KEEP_ACTIVE_M  (BIT(30))
#define SPI_CS_KEEP_ACTIVE_V  0x1
#define SPI_CS_KEEP_ACTIVE_S  30
/* SPI_CK_inidle_EDGE：R/W；位位置：[29]；默认值：1’b0；*/
/*描述：1：空闲时spi-clk线为高0：空闲时spi-clk线路为低。可在形态状态下配置。*/
#define SPI_CK_IDLE_EDGE  (BIT(29))
#define SPI_CK_IDLE_EDGE_M  (BIT(29))
#define SPI_CK_IDLE_EDGE_V  0x1
#define SPI_CK_IDLE_EDGE_S  29
/* SPI_CD_IDLE_EDGE：R/W；位位置：[26]；默认值：1’b0；*/
/*description:spi_cd的默认值。可在形态状态下配置。*/
#define SPI_CD_IDLE_EDGE  (BIT(26))
#define SPI_CD_IDLE_EDGE_M  (BIT(26))
#define SPI_CD_IDLE_EDGE_V  0x1
#define SPI_CD_IDLE_EDGE_S  26
/* SPI_CD_CMD_SET:R/W；位位置：[25]；默认值：1’b0；*/
/*description:1:spi_cd=！spi_st[3:0]处于spi_SEND_CMD状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
#define SPI_CD_CMD_SET  (BIT(25))
#define SPI_CD_CMD_SET_M  (BIT(25))
#define SPI_CD_CMD_SET_V  0x1
#define SPI_CD_CMD_SET_S  25
/* SPI_DQS_IDLE_EDGE:R/W；位位置：[24]；默认值：1’b0；*/
/*description:spi_dqs的默认值。可在形态状态下配置。*/
#define SPI_DQS_IDLE_EDGE  (BIT(24))
#define SPI_DQS_IDLE_EDGE_M  (BIT(24))
#define SPI_DQS_IDLE_EDGE_V  0x1
#define SPI_DQS_IDLE_EDGE_S  24
/* SPI_SLAVE_CS_POL:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：spi从输入cs极性选择。1： 发票0：未更改。可在形态状态下配置。*/
#define SPI_SLAVE_CS_POL  (BIT(23))
#define SPI_SLAVE_CS_POL_M  (BIT(23))
#define SPI_SLAVE_CS_POL_V  0x1
#define SPI_SLAVE_CS_POL_S  23
/* SPI_CD_ADDR_SET:R/W；位位置：[22]；默认值：1’b0；*/
/*description:1:spi_cd=！spi_st[3:0]处于spi_SEND_ADDR状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
#define SPI_CD_ADDR_SET  (BIT(22))
#define SPI_CD_ADDR_SET_M  (BIT(22))
#define SPI_CD_ADDR_SET_V  0x1
#define SPI_CD_ADDR_SET_S  22
/* SPI_CD_DUMMY_SET:R/W；位位置：[21]；默认值：1’b0；*/
/*description:1:spi_cd=！spi_st[3:0]处于spi_DUMMY状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
#define SPI_CD_DUMMY_SET  (BIT(21))
#define SPI_CD_DUMMY_SET_M  (BIT(21))
#define SPI_CD_DUMMY_SET_V  0x1
#define SPI_CD_DUMMY_SET_S  21
/* SPI_CD_DATA_SET:R/W；位位置：[20]；默认值：1’b0；*/
/*description:1:spi_cd=！spi_st[3:0]处于spi_DOUT或spi_DIN状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
#define SPI_CD_DATA_SET  (BIT(20))
#define SPI_CD_DATA_SET_M  (BIT(20))
#define SPI_CD_DATA_SET_V  0x1
#define SPI_CD_DATA_SET_S  20
/* SPI_CMD_DTR_EN:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：1:SPI clk和SPI_SEND_CMD状态的数据处于DTR模式，包括主控1/2/4/8-bm。可在形态状态下配置。*/
#define SPI_CMD_DTR_EN  (BIT(19))
#define SPI_CMD_DTR_EN_M  (BIT(19))
#define SPI_CMD_DTR_EN_V  0x1
#define SPI_CMD_DTR_EN_S  19
/* SPI_ADDR_DTR_EN:R/W；位位置：[18]；默认值：1’b0；*/
/*描述：1:SPI clk和SPI_SEND_ADDR状态的数据处于DTR模式，包括主控1/2/4/8-bm。可在形态状态下配置。*/
#define SPI_ADDR_DTR_EN  (BIT(18))
#define SPI_ADDR_DTR_EN_M  (BIT(18))
#define SPI_ADDR_DTR_EN_V  0x1
#define SPI_ADDR_DTR_EN_S  18
/* SPI_DATA_DTR_EN:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：1:SPI clk以及SPI_DOUT和SPI_DIN状态的数据处于DTR模式，包括主控1/2/4/8-bm。可在形态状态下配置。*/
#define SPI_DATA_DTR_EN  (BIT(17))
#define SPI_DATA_DTR_EN_M  (BIT(17))
#define SPI_DATA_DTR_EN_V  0x1
#define SPI_DATA_DTR_EN_S  17
/* SPI_CLK_DATA_DTR_EN:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：1:SPI主DTR模式应用于SPI clk数据和SPI_dqs*/
#define SPI_CLK_DATA_DTR_EN  (BIT(16))
#define SPI_CLK_DATA_DTR_EN_M  (BIT(16))
#define SPI_CLK_DATA_DTR_EN_V  0x1
#define SPI_CLK_DATA_DTR_EN_S  16
/* SPI_MASTER_CS_POL:R/W；比特位置：[12:7]；默认值：6'b0；*/
/*描述：在主模式中，位是spi cs线的极性，值等于spi_cs^spi_master_cs_pol。可在形态状态下配置。*/
#define SPI_MASTER_CS_POL  0x0000003F
#define SPI_MASTER_CS_POL_M  ((SPI_MASTER_CS_POL_V)<<(SPI_MASTER_CS_POL_S))
#define SPI_MASTER_CS_POL_V  0x3F
#define SPI_MASTER_CS_POL_S  7
/* SPI_CK_DIS:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：1:spi-clk-out禁用0:spi-clk-out启用。可在形态状态下配置。*/
#define SPI_CK_DIS  (BIT(6))
#define SPI_CK_DIS_M  (BIT(6))
#define SPI_CK_DIS_V  0x1
#define SPI_CK_DIS_S  6
/* SPI_CS5_DIS:R/W；位位置：[5]；默认值：1’b1；*/
/*描述：SPI CS5引脚启用1：禁用CS5 0：SPI_CS5信号来自/至CS5引脚。可在形态状态下配置。*/
#define SPI_CS5_DIS  (BIT(5))
#define SPI_CS5_DIS_M  (BIT(5))
#define SPI_CS5_DIS_V  0x1
#define SPI_CS5_DIS_S  5
/* SPI_CS4_DIS:R/W；位位置：[4]；默认值：1’b1；*/
/*描述：SPI CS4引脚启用1：禁用CS4 0：SPI_CS4信号来自/至CS4引脚。可在形态状态下配置。*/
#define SPI_CS4_DIS  (BIT(4))
#define SPI_CS4_DIS_M  (BIT(4))
#define SPI_CS4_DIS_V  0x1
#define SPI_CS4_DIS_S  4
/* SPI_CS3_DIS：R/W；位位置：[3]；默认值：1’b1；*/
/*description:保留*/
#define SPI_CS3_DIS  (BIT(3))
#define SPI_CS3_DIS_M  (BIT(3))
#define SPI_CS3_DIS_V  0x1
#define SPI_CS3_DIS_S  3
/* SPI_CS2_DIS:R/W；位位置：[2]；默认值：1’b1；*/
/*描述：SPI CS2引脚启用1：禁用CS2 0：SPI_CS2信号来自/至CS2引脚。可在形态状态下配置。*/
#define SPI_CS2_DIS  (BIT(2))
#define SPI_CS2_DIS_M  (BIT(2))
#define SPI_CS2_DIS_V  0x1
#define SPI_CS2_DIS_S  2
/* SPI_CS1_DIS:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：SPI CS1引脚启用1：禁用CS1 0：SPI_CS1信号来自/至CS1引脚。可在形态状态下配置。*/
#define SPI_CS1_DIS  (BIT(1))
#define SPI_CS1_DIS_M  (BIT(1))
#define SPI_CS1_DIS_V  0x1
#define SPI_CS1_DIS_S  1
/* SPI_CS0_DIS:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：SPI CS0引脚启用1：禁用CS0 0：SPI_CS0信号来自/至CS0引脚。可在形态状态下配置。*/
#define SPI_CS0_DIS  (BIT(0))
#define SPI_CS0_DIS_M  (BIT(0))
#define SPI_CS0_DIS_V  0x1
#define SPI_CS0_DIS_S  0

#define SPI_SLAVE_REG(i)          (REG_SPI_BASE(i) + 0x030)
/* SPI_SOFT_RESET:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：软件复位使能复位spi时钟线cs线和数据线。可在形态状态下配置。*/
#define SPI_SOFT_RESET  (BIT(31))
#define SPI_SOFT_RESET_M  (BIT(31))
#define SPI_SOFT_RESET_V  0x1
#define SPI_SOFT_RESET_S  31
/* SPI_SLAVE_MODE：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置SPI工作模式。1： 从模式0：主模式。*/
#define SPI_SLAVE_MODE  (BIT(30))
#define SPI_SLAVE_MODE_M  (BIT(30))
#define SPI_SLAVE_MODE_V  0x1
#define SPI_SLAVE_MODE_S  30
/* SPI_TRANS_DONE_AUTO_CLR_EN:R/W；位位置：[29]；默认值：1’b0；*/
/*描述：spitransdone自动清除启用在spitransdonne的pos边缘后3个apb周期清除。0：禁用。1： 启用。可在形态状态下配置。*/
#define SPI_TRANS_DONE_AUTO_CLR_EN  (BIT(29))
#define SPI_TRANS_DONE_AUTO_CLR_EN_M  (BIT(29))
#define SPI_TRANS_DONE_AUTO_CLR_EN_V  0x1
#define SPI_TRANS_DONE_AUTO_CLR_EN_S  29
/* SPI_TRANS_CNT:RO；比特位置：[26:23]；默认值：4'b0；*/
/*description:主模式和从模式下的操作计数器。*/
#define SPI_TRANS_CNT  0x0000000F
#define SPI_TRANS_CNT_M  ((SPI_TRANS_CNT_V)<<(SPI_TRANS_CNT_S))
#define SPI_TRANS_CNT_V  0xF
#define SPI_TRANS_CNT_S  23
/* SPI_SEG_MAGIC_ERR_INT_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*description:1：启用seg魔法值错误中断。0：其他。可在形态状态下配置。*/
#define SPI_SEG_MAGIC_ERR_INT_EN  (BIT(11))
#define SPI_SEG_MAGIC_ERR_INT_EN_M  (BIT(11))
#define SPI_SEG_MAGIC_ERR_INT_EN_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_EN_S  11
/* SPI_INT_DMA_SEG_TRANS_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*description:spi_dma_seg_trans_done中断启用。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_INT_DMA_SEG_TRANS_EN  (BIT(10))
#define SPI_INT_DMA_SEG_TRANS_EN_M  (BIT(10))
#define SPI_INT_DMA_SEG_TRANS_EN_V  0x1
#define SPI_INT_DMA_SEG_TRANS_EN_S  10
/* SPI_INT_TRANS_DONE_EN:R/W；位位置：[9]；默认值：1’b1；*/
/*description:spi_trans_done中断启用。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_INT_TRANS_DONE_EN  (BIT(9))
#define SPI_INT_TRANS_DONE_EN_M  (BIT(9))
#define SPI_INT_TRANS_DONE_EN_V  0x1
#define SPI_INT_TRANS_DONE_EN_S  9
/* SPI_INT_WR_DMA_DONE_EN:R/W；位位置：[8]；默认值：1’b0；*/
/*description:spi_slv_wr_dma中断启用。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_INT_WR_DMA_DONE_EN  (BIT(8))
#define SPI_INT_WR_DMA_DONE_EN_M  (BIT(8))
#define SPI_INT_WR_DMA_DONE_EN_V  0x1
#define SPI_INT_WR_DMA_DONE_EN_S  8
/* SPI_INT_RD_DMA_DONE_EN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:spi_slv_rd_dma中断启用。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_INT_RD_DMA_DONE_EN  (BIT(7))
#define SPI_INT_RD_DMA_DONE_EN_M  (BIT(7))
#define SPI_INT_RD_DMA_DONE_EN_V  0x1
#define SPI_INT_RD_DMA_DONE_EN_S  7
/* SPI_INT_WR_BUF_DONE_EN:R/W；位位置：[6]；默认值：1’b0；*/
/*description:spi_slv_wr_buf中断启用。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_INT_WR_BUF_DONE_EN  (BIT(6))
#define SPI_INT_WR_BUF_DONE_EN_M  (BIT(6))
#define SPI_INT_WR_BUF_DONE_EN_V  0x1
#define SPI_INT_WR_BUF_DONE_EN_S  6
/* SPI_INT_RD_BUF_DONE_EN:R/W；位位置：[5]；默认值：1’b0；*/
/*description:spi_slv_rd_buf中断启用。1： 启用0：禁用。可在形态状态下配置。*/
#define SPI_INT_RD_BUF_DONE_EN  (BIT(5))
#define SPI_INT_RD_BUF_DONE_EN_M  (BIT(5))
#define SPI_INT_RD_BUF_DONE_EN_V  0x1
#define SPI_INT_RD_BUF_DONE_EN_S  5
/* SPI_TRANS_DONE:R/W；位位置：[4]；默认值：1’b0；*/
/*description:在主模式和从模式下完成任何操作的中断原始位。无法通过CONF_buf更改。*/
#define SPI_TRANS_DONE  (BIT(4))
#define SPI_TRANS_DONE_M  (BIT(4))
#define SPI_TRANS_DONE_V  0x1
#define SPI_TRANS_DONE_S  4

#define SPI_SLAVE1_REG(i)          (REG_SPI_BASE(i) + 0x034)
/* SPI_SLV_LAST_ADDR:R/W；位位置：[31:24]；默认值：8'd0；*/
/*description:在从属模式下，它是地址的值。*/
#define SPI_SLV_LAST_ADDR  0x000000FF
#define SPI_SLV_LAST_ADDR_M  ((SPI_SLV_LAST_ADDR_V)<<(SPI_SLV_LAST_ADDR_S))
#define SPI_SLV_LAST_ADDR_V  0xFF
#define SPI_SLV_LAST_ADDR_S  24
/* SPI_SLV_LAST_COMMAND:R/W；比特位置：[23:16]；默认值：8'b0；*/
/*description:在从属模式下，它是命令的值。*/
#define SPI_SLV_LAST_COMMAND  0x000000FF
#define SPI_SLV_LAST_COMMAND_M  ((SPI_SLV_LAST_COMMAND_V)<<(SPI_SLV_LAST_COMMAND_S))
#define SPI_SLV_LAST_COMMAND_V  0xFF
#define SPI_SLV_LAST_COMMAND_S  16
/* SPI_SLV_WR_DMA_DONE:R/W；位位置：[15]；默认值：1’b0；*/
/*description:在从属模式下完成dma写入操作的中断原始位。无法通过CONF_buf更改。*/
#define SPI_SLV_WR_DMA_DONE  (BIT(15))
#define SPI_SLV_WR_DMA_DONE_M  (BIT(15))
#define SPI_SLV_WR_DMA_DONE_V  0x1
#define SPI_SLV_WR_DMA_DONE_S  15
/* SPI_SLV_CMD_ERR:RO；位位置：[14]；默认值：1’b0；*/
/*description:1:SPI从设备不支持上次SPI传输的命令值。0：支持命令值或未收到命令值。*/
#define SPI_SLV_CMD_ERR  (BIT(14))
#define SPI_SLV_CMD_ERR_M  (BIT(14))
#define SPI_SLV_CMD_ERR_V  0x1
#define SPI_SLV_CMD_ERR_S  14
/* SPI_SLV_ADDR_ERR:RO；位位置：[13]；默认值：1’b0；*/
/*description:1:SPI从属设备不支持上次SPI传输的地址值。0:支持地址值或未收到地址值。*/
#define SPI_SLV_ADDR_ERR  (BIT(13))
#define SPI_SLV_ADDR_ERR_M  (BIT(13))
#define SPI_SLV_ADDR_ERR_V  0x1
#define SPI_SLV_ADDR_ERR_S  13
/* SPI_SLV_NO_QPI_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：1:spi从属QPI模式不受支持。0:支持spi从属QPI模式。*/
#define SPI_SLV_NO_QPI_EN  (BIT(12))
#define SPI_SLV_NO_QPI_EN_M  (BIT(12))
#define SPI_SLV_NO_QPI_EN_V  0x1
#define SPI_SLV_NO_QPI_EN_S  12
/* SPI_SLV_CMD_ERR_CLR:R/W；位位置：[11]；默认值：1’b0；*/
/*description:1：清除spi_slv_cmd_err。0:无效。可以通过CONF_buf更改。*/
#define SPI_SLV_CMD_ERR_CLR  (BIT(11))
#define SPI_SLV_CMD_ERR_CLR_M  (BIT(11))
#define SPI_SLV_CMD_ERR_CLR_V  0x1
#define SPI_SLV_CMD_ERR_CLR_S  11
/* SPI_SLV_ADDR_ERR_CLR:R/W；位位置：[10]；默认值：1’b0；*/
/*description:1：清除spi_slv_addr_err。0:无效。可以通过CONF_buf更改。*/
#define SPI_SLV_ADDR_ERR_CLR  (BIT(10))
#define SPI_SLV_ADDR_ERR_CLR_M  (BIT(10))
#define SPI_SLV_ADDR_ERR_CLR_V  0x1
#define SPI_SLV_ADDR_ERR_CLR_S  10

#define SPI_SLV_WRBUF_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x038)
/* SPI_CONF_BASE_BITLEN:R/W；位位置：[31:25]；默认值：7'd108；*/
/*description:CONF状态的基本spi_clk循环。如果启用了spi_usr_CONF，则CONF状态的实际周期长度为spi_CONF_base_bitlen[6:0]+spi_CONF-bitlen[23:0]。*/
#define SPI_CONF_BASE_BITLEN  0x0000007F
#define SPI_CONF_BASE_BITLEN_M  ((SPI_CONF_BASE_BITLEN_V)<<(SPI_CONF_BASE_BITLEN_S))
#define SPI_CONF_BASE_BITLEN_V  0x7F
#define SPI_CONF_BASE_BITLEN_S  25
/* SPI_SLV_WR_BUF_DONE:R/W；位位置：[24]；默认值：1’b0；*/
/*description:用于在从属模式下完成写缓冲操作的中断原始位。无法通过CONF_buf更改。*/
#define SPI_SLV_WR_BUF_DONE  (BIT(24))
#define SPI_SLV_WR_BUF_DONE_M  (BIT(24))
#define SPI_SLV_WR_BUF_DONE_V  0x1
#define SPI_SLV_WR_BUF_DONE_S  24

#define SPI_SLV_RDBUF_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x03C)
/* SPI_SEG_MAGIC_ERR:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：1：在主DMA seg传输模式下，CONF缓冲区中最近的魔法值不正确。0：其他。*/
#define SPI_SEG_MAGIC_ERR  (BIT(25))
#define SPI_SEG_MAGIC_ERR_M  (BIT(25))
#define SPI_SEG_MAGIC_ERR_V  0x1
#define SPI_SEG_MAGIC_ERR_S  25
/* SPI_SLV_RD_BUF_DONE:R/W；位位置：[24]；默认值：1’b0；*/
/*description:用于在从属模式下完成读缓冲操作的中断原始位。无法通过CONF_buf更改。*/
#define SPI_SLV_RD_BUF_DONE  (BIT(24))
#define SPI_SLV_RD_BUF_DONE_M  (BIT(24))
#define SPI_SLV_RD_BUF_DONE_V  0x1
#define SPI_SLV_RD_BUF_DONE_S  24
/* SPI_SLV_DMA_RD_byten:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:在从属模式下，它是读取操作的字节长度。寄存器值应为byte_num。*/
#define SPI_SLV_DMA_RD_BYTELEN  0x000FFFFF
#define SPI_SLV_DMA_RD_BYTELEN_M  ((SPI_SLV_DMA_RD_BYTELEN_V)<<(SPI_SLV_DMA_RD_BYTELEN_S))
#define SPI_SLV_DMA_RD_BYTELEN_V  0xFFFFF
#define SPI_SLV_DMA_RD_BYTELEN_S  0

#define SPI_SLV_RD_BYTE_REG(i)          (REG_SPI_BASE(i) + 0x040)
/* SPI_USR_CONF:R/W；位位置：[31]；默认值：1’b0；*/
/*description:1：启用当前seg trans操作的DMA CONF阶段，这意味着seg trans将启动。0：这不是seg trans模式。*/
#define SPI_USR_CONF  (BIT(31))
#define SPI_USR_CONF_M  (BIT(31))
#define SPI_USR_CONF_V  0x1
#define SPI_USR_CONF_S  31
/* SPI_SLV_RD_DMA_DONE：R/W；位位置：[30]；默认值：1’b0；*/
/*描述：在从属模式下完成Rd DMA操作的中断原始位。无法通过CONF_buf更改。*/
#define SPI_SLV_RD_DMA_DONE  (BIT(30))
#define SPI_SLV_RD_DMA_DONE_M  (BIT(30))
#define SPI_SLV_RD_DMA_DONE_V  0x1
#define SPI_SLV_RD_DMA_DONE_S  30
/* SPI_DMA_SEG_MAGIC_VALUE:R/W；位位置：[27:24]；默认值：4'd10；*/
/*描述：主DMA seg trans中BM表的神奇值。*/
#define SPI_DMA_SEG_MAGIC_VALUE  0x0000000F
#define SPI_DMA_SEG_MAGIC_VALUE_M  ((SPI_DMA_SEG_MAGIC_VALUE_V)<<(SPI_DMA_SEG_MAGIC_VALUE_S))
#define SPI_DMA_SEG_MAGIC_VALUE_V  0xF
#define SPI_DMA_SEG_MAGIC_VALUE_S  24
/* SPI_SLV_WRBUF_BYTELEN_EN:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：1:spi_slv_data_bytelen以CPU控制模式（Wr_BUF）存储主数据写入从数据长度的数据字节长度。0:其他*/
#define SPI_SLV_WRBUF_BYTELEN_EN  (BIT(23))
#define SPI_SLV_WRBUF_BYTELEN_EN_M  (BIT(23))
#define SPI_SLV_WRBUF_BYTELEN_EN_V  0x1
#define SPI_SLV_WRBUF_BYTELEN_EN_S  23
/* SPI_SLV_RDBUF_BYTELEN_EN:R/W；位位置：[22]；默认值：1’b0；*/
/*描述：1:spi_slv_data_bytelen以CPU控制模式（Rd_BUF）存储主从数据长度的数据字节长度。0:其他*/
#define SPI_SLV_RDBUF_BYTELEN_EN  (BIT(22))
#define SPI_SLV_RDBUF_BYTELEN_EN_M  (BIT(22))
#define SPI_SLV_RDBUF_BYTELEN_EN_V  0x1
#define SPI_SLV_RDBUF_BYTELEN_EN_S  22
/* SPI_SLV_WRDMA_BYTELEN_EN:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：1:spi_slv_data_bytelen以DMA控制模式（Wr_DMA）存储主写从数据长度的数据字节长度。0:其他*/
#define SPI_SLV_WRDMA_BYTELEN_EN  (BIT(21))
#define SPI_SLV_WRDMA_BYTELEN_EN_M  (BIT(21))
#define SPI_SLV_WRDMA_BYTELEN_EN_V  0x1
#define SPI_SLV_WRDMA_BYTELEN_EN_S  21
/* SPI_SLV_RDDMA_BYTELEN_EN:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：1:spi_slv_data_bytelen以DMA控制模式（Rd_DMA）存储主从数据长度的数据字节长度。0:其他*/
#define SPI_SLV_RDDMA_BYTELEN_EN  (BIT(20))
#define SPI_SLV_RDDMA_BYTELEN_EN_M  (BIT(20))
#define SPI_SLV_RDDMA_BYTELEN_EN_V  0x1
#define SPI_SLV_RDDMA_BYTELEN_EN_S  20
/* SPI_SLV_DATA_BYTELEN:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*description:从模式下最后一次SPI传输的全双工或半双工数据字节长度。在半双工模式下，该值由位[23:20]控制。*/
#define SPI_SLV_DATA_BYTELEN  0x000FFFFF
#define SPI_SLV_DATA_BYTELEN_M  ((SPI_SLV_DATA_BYTELEN_V)<<(SPI_SLV_DATA_BYTELEN_S))
#define SPI_SLV_DATA_BYTELEN_V  0xFFFFF
#define SPI_SLV_DATA_BYTELEN_S  0

#define SPI_FSM_REG(i)          (REG_SPI_BASE(i) + 0x044)
/* SPI_MST_DMA_RD_byten:R/W；比特位置：[31:12]；默认值：20'00；*/
/*description:在非seg-trans或seg-trans模式下定义主DMA读取字节长度。spi_rx_eof_en为0时无效。可以在CONF状态下配置。。*/
#define SPI_MST_DMA_RD_BYTELEN  0x000FFFFF
#define SPI_MST_DMA_RD_BYTELEN_M  ((SPI_MST_DMA_RD_BYTELEN_V)<<(SPI_MST_DMA_RD_BYTELEN_S))
#define SPI_MST_DMA_RD_BYTELEN_V  0xFFFFF
#define SPI_MST_DMA_RD_BYTELEN_S  12
/* SPI_ST:RO；位位置：[3:0]；默认值：4'b0；*/
/*description:spi状态机的状态。0：空闲状态1：准备状态2：发送命令状态3：发送数据状态4：红色数据状态5：写入数据状态6：等待状态7：完成状态。*/
#define SPI_ST  0x0000000F
#define SPI_ST_M  ((SPI_ST_V)<<(SPI_ST_S))
#define SPI_ST_V  0xF
#define SPI_ST_S  0

#define SPI_HOLD_REG(i)          (REG_SPI_BASE(i) + 0x048)
/* SPI_DMA_SEG_TRANS_DONE:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：1:spi主DMA全双工/半双工seg传输或从半双工sef传输。数据已被推送到相应的存储器。0:seg传输未结束或未发生。无法通过CONF_buf更改。*/
#define SPI_DMA_SEG_TRANS_DONE  (BIT(7))
#define SPI_DMA_SEG_TRANS_DONE_M  (BIT(7))
#define SPI_DMA_SEG_TRANS_DONE_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_S  7
/* SPI_HOLD_OUT_TIME:R/W；比特位置：[6:4]；默认值：3'b0；*/
/*描述：当spi_hold_out_en启用时，设置输出spi_hold信号的保持周期。可在形态状态下配置。*/
#define SPI_HOLD_OUT_TIME  0x00000007
#define SPI_HOLD_OUT_TIME_M  ((SPI_HOLD_OUT_TIME_V)<<(SPI_HOLD_OUT_TIME_S))
#define SPI_HOLD_OUT_TIME_V  0x7
#define SPI_HOLD_OUT_TIME_S  4
/* SPI_HOLD_OUT_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:启用将spi输出保持值设置为spi_hold_reg。它可以用于用spi_ext_hold_en和其他usr保持信号保持spi状态机。可在形态状态下配置。*/
#define SPI_HOLD_OUT_EN  (BIT(3))
#define SPI_HOLD_OUT_EN_M  (BIT(3))
#define SPI_HOLD_OUT_EN_V  0x1
#define SPI_HOLD_OUT_EN_S  3
/* SPI_HOLD_VAL_REG:R/W；位位置：[2]；默认值：1’b0；*/
/*description:spi保持输出值，该值应与spi_hold_out_en一起使用。可在形态状态下配置。*/
#define SPI_HOLD_VAL_REG  (BIT(2))
#define SPI_HOLD_VAL_REG_M  (BIT(2))
#define SPI_HOLD_VAL_REG_V  0x1
#define SPI_HOLD_VAL_REG_S  2
/* SPI_INT_HOLD_ENA:R/W；位位置：[1:0]；默认值：2’b0；*/
/*描述：此寄存器用于两个SPI主机共享相同的cs时钟和数据信号。如果另一个SPI忙，则设置一个SPI的位，SPI将保持。1（3）：在空闲阶段保持2：在准备阶段保持。可在形态状态下配置。*/
#define SPI_INT_HOLD_ENA  0x00000003
#define SPI_INT_HOLD_ENA_M  ((SPI_INT_HOLD_ENA_V)<<(SPI_INT_HOLD_ENA_S))
#define SPI_INT_HOLD_ENA_V  0x3
#define SPI_INT_HOLD_ENA_S  0

#define SPI_DMA_CONF_REG(i)          (REG_SPI_BASE(i) + 0x04C)
/* SPI_DMA_SEG_TRANS_CLR:R/W；位位置：[28]；默认值：1’b0；*/
/*description:1：结束从属seg trans，用作0x05命令。2个或更多个端段传输信号将在DMA RX中引起错误。*/
#define SPI_DMA_SEG_TRANS_CLR  (BIT(28))
#define SPI_DMA_SEG_TRANS_CLR_M  (BIT(28))
#define SPI_DMA_SEG_TRANS_CLR_V  0x1
#define SPI_DMA_SEG_TRANS_CLR_S  28
/* SPI_EXT_MEM_BK_SIZE:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:选择外部内存块大小。*/
#define SPI_EXT_MEM_BK_SIZE  0x00000003
#define SPI_EXT_MEM_BK_SIZE_M  ((SPI_EXT_MEM_BK_SIZE_V)<<(SPI_EXT_MEM_BK_SIZE_S))
#define SPI_EXT_MEM_BK_SIZE_V  0x3
#define SPI_EXT_MEM_BK_SIZE_S  26
/* SPI_DMA_OUTFIFO_EMPTY_CLR:R/W；位位置：[23]；默认值：1’b0；*/
/*description:1：清除spi_dma_outfifo_empty_vld。0：不要控制它。*/
#define SPI_DMA_OUTFIFO_EMPTY_CLR  (BIT(23))
#define SPI_DMA_OUTFIFO_EMPTY_CLR_M  (BIT(23))
#define SPI_DMA_OUTFIFO_EMPTY_CLR_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_CLR_S  23
/* SPI_DMA_INFIFO_FULL_CLR:R/W；位位置：[22]；默认值：1’b0；*/
/*description:1：清除spi_dma_infifo_full_vld。0：不要控制它。*/
#define SPI_DMA_INFIFO_FULL_CLR  (BIT(22))
#define SPI_DMA_INFIFO_FULL_CLR_M  (BIT(22))
#define SPI_DMA_INFIFO_FULL_CLR_V  0x1
#define SPI_DMA_INFIFO_FULL_CLR_S  22
/* SPI_RX_EOF_EN:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：1：当dma推送数据字节数等于spi-dma转换中的spi_slv/mst_dma_rd_bytelen[19:0]的值时，设置spi_dma_inlink_eof。0:spi_dma_inlink_eof由非seg trans中的spi_trans_done或seg trans中的spi_dma_seg_trans_done设置。*/
#define SPI_RX_EOF_EN  (BIT(21))
#define SPI_RX_EOF_EN_M  (BIT(21))
#define SPI_RX_EOF_EN_V  0x1
#define SPI_RX_EOF_EN_S  21
/* SPI_SLV_TX_SEG_TRANS_CLR_EN:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：1:spi slave cmd 6清除spi_dma_outfifoempty_vld。0:spi_trans_done清除spi_dma _outfifo empty-vld。*/
#define SPI_SLV_TX_SEG_TRANS_CLR_EN  (BIT(20))
#define SPI_SLV_TX_SEG_TRANS_CLR_EN_M  (BIT(20))
#define SPI_SLV_TX_SEG_TRANS_CLR_EN_V  0x1
#define SPI_SLV_TX_SEG_TRANS_CLR_EN_S  20
/* SPI_SLV_RX_SEG_TRANS_CLR_EN:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：1:spi slave cmd 5清除spi_dma_infifo full_vld。0:spi_trans_done清除spi_dma _infifo full_vld。*/
#define SPI_SLV_RX_SEG_TRANS_CLR_EN  (BIT(19))
#define SPI_SLV_RX_SEG_TRANS_CLR_EN_M  (BIT(19))
#define SPI_SLV_RX_SEG_TRANS_CLR_EN_V  0x1
#define SPI_SLV_RX_SEG_TRANS_CLR_EN_S  19
/* SPI_DMA_SLV_SEG_TRANS_EN:R/W；位位置：[18]；默认值：1’b0；*/
/*description:在spi-dma半从模式下启用dma段传输。1： 启用。0：禁用。*/
#define SPI_DMA_SLV_SEG_TRANS_EN  (BIT(18))
#define SPI_DMA_SLV_SEG_TRANS_EN_M  (BIT(18))
#define SPI_DMA_SLV_SEG_TRANS_EN_V  0x1
#define SPI_DMA_SLV_SEG_TRANS_EN_S  18
/* SPI_SLV_LAST_SEG_POP_CLR:R/W；位位置：[17]；默认值：1’b0；*/
/*description:1：清除spi_slv_seg_frt_pop_mask。0:其他*/
#define SPI_SLV_LAST_SEG_POP_CLR  (BIT(17))
#define SPI_SLV_LAST_SEG_POP_CLR_M  (BIT(17))
#define SPI_SLV_LAST_SEG_POP_CLR_V  0x1
#define SPI_SLV_LAST_SEG_POP_CLR_S  17
/* SPI_DMA_CONTINUE:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：spi-dma继续tx/rx数据。*/
#define SPI_DMA_CONTINUE  (BIT(16))
#define SPI_DMA_CONTINUE_M  (BIT(16))
#define SPI_DMA_CONTINUE_V  0x1
#define SPI_DMA_CONTINUE_S  16
/* SPI_DMA_TX_STOP:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：当处于continue tx/rx模式时，spidma写入数据停止。*/
#define SPI_DMA_TX_STOP  (BIT(15))
#define SPI_DMA_TX_STOP_M  (BIT(15))
#define SPI_DMA_TX_STOP_V  0x1
#define SPI_DMA_TX_STOP_S  15
/* SPI_DMA_RX_STOP:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：当处于continue tx/rx模式时，spidma读取数据停止。*/
#define SPI_DMA_RX_STOP  (BIT(14))
#define SPI_DMA_RX_STOP_M  (BIT(14))
#define SPI_DMA_RX_STOP_V  0x1
#define SPI_DMA_RX_STOP_S  14
/* SPI_MEM_TRANS_EN:R/W；位位置：[13]；默认值：1’b0；*/
/*说明：*/
#define SPI_MEM_TRANS_EN  (BIT(13))
#define SPI_MEM_TRANS_EN_M  (BIT(13))
#define SPI_MEM_TRANS_EN_V  0x1
#define SPI_MEM_TRANS_EN_S  13
/* SPI_OUT_DATA_BURST_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：spidma以突发模式从内存读取数据。*/
#define SPI_OUT_DATA_BURST_EN  (BIT(12))
#define SPI_OUT_DATA_BURST_EN_M  (BIT(12))
#define SPI_OUT_DATA_BURST_EN_V  0x1
#define SPI_OUT_DATA_BURST_EN_S  12
/* SPI_INDSCR_BURST_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：当将数据写入内存时，读取描述符使用突发模式。*/
#define SPI_INDSCR_BURST_EN  (BIT(11))
#define SPI_INDSCR_BURST_EN_M  (BIT(11))
#define SPI_INDSCR_BURST_EN_V  0x1
#define SPI_INDSCR_BURST_EN_S  11
/* SPI_OUTDSCR_BURST_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：读取描述符在读取内存数据时使用突发模式。*/
#define SPI_OUTDSCR_BURST_EN  (BIT(10))
#define SPI_OUTDSCR_BURST_EN_M  (BIT(10))
#define SPI_OUTDSCR_BURST_EN_V  0x1
#define SPI_OUTDSCR_BURST_EN_S  10
/* SPI_OUT_EOF_MODE：R/W；位位置：[9]；默认值：1’b1；*/
/*描述：退出eof标志生成模式。1：当dma从fifo弹出所有数据时0：当ahb将所有数据推送到fifo时。*/
#define SPI_OUT_EOF_MODE  (BIT(9))
#define SPI_OUT_EOF_MODE_M  (BIT(9))
#define SPI_OUT_EOF_MODE_V  0x1
#define SPI_OUT_EOF_MODE_S  9
/* SPI_OUT_AUTO_werback:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：当设置位时，当内联长度为0时，DMA继续使用下一个内联节点。*/
#define SPI_OUT_AUTO_WRBACK  (BIT(8))
#define SPI_OUT_AUTO_WRBACK_M  (BIT(8))
#define SPI_OUT_AUTO_WRBACK_V  0x1
#define SPI_OUT_AUTO_WRBACK_S  8
/* SPI_OUT_LOOP_TEST:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置位以测试链接。*/
#define SPI_OUT_LOOP_TEST  (BIT(7))
#define SPI_OUT_LOOP_TEST_M  (BIT(7))
#define SPI_OUT_LOOP_TEST_V  0x1
#define SPI_OUT_LOOP_TEST_S  7
/* SPI_IN_LOOP_TEST:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置要在链接中测试的位。*/
#define SPI_IN_LOOP_TEST  (BIT(6))
#define SPI_IN_LOOP_TEST_M  (BIT(6))
#define SPI_IN_LOOP_TEST_V  0x1
#define SPI_IN_LOOP_TEST_S  6
/* SPI_AHBM_RST:R/W；位位置：[5]；默认值：1’b0；*/
/*description:重置spi-dma-ahb主机。*/
#define SPI_AHBM_RST  (BIT(5))
#define SPI_AHBM_RST_M  (BIT(5))
#define SPI_AHBM_RST_V  0x1
#define SPI_AHBM_RST_S  5
/* SPI_AHBM_FIFO_RST:R/W；位位置：[4]；默认值：1’b0；*/
/*description:重置spi-dmaahb主fifo指针。*/
#define SPI_AHBM_FIFO_RST  (BIT(4))
#define SPI_AHBM_FIFO_RST_M  (BIT(4))
#define SPI_AHBM_FIFO_RST_V  0x1
#define SPI_AHBM_FIFO_RST_S  4
/* SPI_OUT_RST:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：该位用于重置dma fsm和数据fifo指针。*/
#define SPI_OUT_RST  (BIT(3))
#define SPI_OUT_RST_M  (BIT(3))
#define SPI_OUT_RST_V  0x1
#define SPI_OUT_RST_S  3
/* SPI_IN_RST:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：该位用于在dma fsm和数据fifo指针中重置。*/
#define SPI_IN_RST  (BIT(2))
#define SPI_IN_RST_M  (BIT(2))
#define SPI_IN_RST_V  0x1
#define SPI_IN_RST_S  2

#define SPI_DMA_OUT_LINK_REG(i)          (REG_SPI_BASE(i) + 0x050)
/* SPI_DMA_TX_ENA:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：spidma写入数据状态位。*/
#define SPI_DMA_TX_ENA  (BIT(31))
#define SPI_DMA_TX_ENA_M  (BIT(31))
#define SPI_DMA_TX_ENA_V  0x1
#define SPI_DMA_TX_ENA_S  31
/* SPI_OUTLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置要装入新outlink描述符的位。*/
#define SPI_OUTLINK_RESTART  (BIT(30))
#define SPI_OUTLINK_RESTART_M  (BIT(30))
#define SPI_OUTLINK_RESTART_V  0x1
#define SPI_OUTLINK_RESTART_S  30
/* SPI_OUTLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置位以开始使用outlink描述符。*/
#define SPI_OUTLINK_START  (BIT(29))
#define SPI_OUTLINK_START_M  (BIT(29))
#define SPI_OUTLINK_START_V  0x1
#define SPI_OUTLINK_START_S  29
/* SPI_OUTLINK_STOP：R/W；位位置：[28]；默认值：1’b0；*/
/*description:将位设置为stop以使用outlink描述符。*/
#define SPI_OUTLINK_STOP  (BIT(28))
#define SPI_OUTLINK_STOP_M  (BIT(28))
#define SPI_OUTLINK_STOP_V  0x1
#define SPI_OUTLINK_STOP_S  28
/* SPI_OUTLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:第一个outlink描述符的地址。*/
#define SPI_OUTLINK_ADDR  0x000FFFFF
#define SPI_OUTLINK_ADDR_M  ((SPI_OUTLINK_ADDR_V)<<(SPI_OUTLINK_ADDR_S))
#define SPI_OUTLINK_ADDR_V  0xFFFFF
#define SPI_OUTLINK_ADDR_S  0

#define SPI_DMA_IN_LINK_REG(i)          (REG_SPI_BASE(i) + 0x054)
/* SPI_DMA_RX_ENA:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：spidma读取数据状态位。*/
#define SPI_DMA_RX_ENA  (BIT(31))
#define SPI_DMA_RX_ENA_M  (BIT(31))
#define SPI_DMA_RX_ENA_V  0x1
#define SPI_DMA_RX_ENA_S  31
/* SPI_INLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置要装入新内联描述符的位。*/
#define SPI_INLINK_RESTART  (BIT(30))
#define SPI_INLINK_RESTART_M  (BIT(30))
#define SPI_INLINK_RESTART_V  0x1
#define SPI_INLINK_RESTART_S  30
/* SPI_INLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置开始使用内联描述符的位。*/
#define SPI_INLINK_START  (BIT(29))
#define SPI_INLINK_START_M  (BIT(29))
#define SPI_INLINK_START_V  0x1
#define SPI_INLINK_START_S  29
/* SPI_INLINK_STOP：R/W；位位置：[28]；默认值：1’b0；*/
/*description:将位设置为stop以使用内联描述符。*/
#define SPI_INLINK_STOP  (BIT(28))
#define SPI_INLINK_STOP_M  (BIT(28))
#define SPI_INLINK_STOP_V  0x1
#define SPI_INLINK_STOP_S  28
/* SPI_INLINK_AUTO_RET:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：当设置位时，当数据包出错时，内联描述符返回到第一个链接节点。*/
#define SPI_INLINK_AUTO_RET  (BIT(20))
#define SPI_INLINK_AUTO_RET_M  (BIT(20))
#define SPI_INLINK_AUTO_RET_V  0x1
#define SPI_INLINK_AUTO_RET_S  20
/* SPI_INLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:第一个内联描述符的地址。*/
#define SPI_INLINK_ADDR  0x000FFFFF
#define SPI_INLINK_ADDR_M  ((SPI_INLINK_ADDR_V)<<(SPI_INLINK_ADDR_S))
#define SPI_INLINK_ADDR_V  0xFFFFF
#define SPI_INLINK_ADDR_S  0

#define SPI_DMA_INT_ENA_REG(i)          (REG_SPI_BASE(i) + 0x058)
/* SPI_SLV_CMDA_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的启用位。*/
#define SPI_SLV_CMDA_INT_ENA  (BIT(15))
#define SPI_SLV_CMDA_INT_ENA_M  (BIT(15))
#define SPI_SLV_CMDA_INT_ENA_V  0x1
#define SPI_SLV_CMDA_INT_ENA_S  15
/* SPI_SLV_CMD9_INT_ENA：R/W；位位置：[14]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的启用位。*/
#define SPI_SLV_CMD9_INT_ENA  (BIT(14))
#define SPI_SLV_CMD9_INT_ENA_M  (BIT(14))
#define SPI_SLV_CMD9_INT_ENA_V  0x1
#define SPI_SLV_CMD9_INT_ENA_S  14
/* SPI_SLV_CMD8_INT_ENA：R/W；位位置：[13]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的启用位。*/
#define SPI_SLV_CMD8_INT_ENA  (BIT(13))
#define SPI_SLV_CMD8_INT_ENA_M  (BIT(13))
#define SPI_SLV_CMD8_INT_ENA_V  0x1
#define SPI_SLV_CMD8_INT_ENA_S  13
/* SPI_SLV_CMD7_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的启用位。*/
#define SPI_SLV_CMD7_INT_ENA  (BIT(12))
#define SPI_SLV_CMD7_INT_ENA_M  (BIT(12))
#define SPI_SLV_CMD7_INT_ENA_V  0x1
#define SPI_SLV_CMD7_INT_ENA_S  12
/* SPI_SLV_CMD6_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:SPI从属CMD6中断的启用位。*/
#define SPI_SLV_CMD6_INT_ENA  (BIT(11))
#define SPI_SLV_CMD6_INT_ENA_M  (BIT(11))
#define SPI_SLV_CMD6_INT_ENA_V  0x1
#define SPI_SLV_CMD6_INT_ENA_S  11
/* SPI_OUTFIFO_EMPTY_ERR_INT_ENA：R/W；位位置：[10]；默认值：1’b0；*/
/*description:outifo空错误中断的启用位。*/
#define SPI_OUTFIFO_EMPTY_ERR_INT_ENA  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_ENA_M  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_ENA_V  0x1
#define SPI_OUTFIFO_EMPTY_ERR_INT_ENA_S  10
/* SPI_INFIFO_FULL_ERR_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:infinfo完全错误中断的启用位。*/
#define SPI_INFIFO_FULL_ERR_INT_ENA  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_ENA_M  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_ENA_V  0x1
#define SPI_INFIFO_FULL_ERR_INT_ENA_S  9
/* SPI_OUT_TOTAL_EOF_INT_ENA：R/W；位位置：[8]；默认值：1’b0；*/
/*description:向主机发送所有数据包的启用位已完成。可在形态状态下配置。*/
#define SPI_OUT_TOTAL_EOF_INT_ENA  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ENA_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ENA_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_ENA_S  8
/* SPI_OUT_EOF_INT_ENA：R/W；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的启用位已完成。可在形态状态下配置。*/
#define SPI_OUT_EOF_INT_ENA  (BIT(7))
#define SPI_OUT_EOF_INT_ENA_M  (BIT(7))
#define SPI_OUT_EOF_INT_ENA_V  0x1
#define SPI_OUT_EOF_INT_ENA_S  7
/* SPI_OUT_DONE_INT_ENA：R/W；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的启用位。可以在CONF状态下配置。*/
#define SPI_OUT_DONE_INT_ENA  (BIT(6))
#define SPI_OUT_DONE_INT_ENA_M  (BIT(6))
#define SPI_OUT_DONE_INT_ENA_V  0x1
#define SPI_OUT_DONE_INT_ENA_S  6
/* SPI_IN_SUC_EOF_INT_ENA：R/W；位位置：[5]；默认值：1’b0；*/
/*description:用于完成从主机接收所有数据包的启用位。可在形态状态下配置。*/
#define SPI_IN_SUC_EOF_INT_ENA  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ENA_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ENA_V  0x1
#define SPI_IN_SUC_EOF_INT_ENA_S  5
/* SPI_IN_ERR_EOF_INT_ENA：R/W；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的启用位。可在形态状态下配置。*/
#define SPI_IN_ERR_EOF_INT_ENA  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ENA_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ENA_V  0x1
#define SPI_IN_ERR_EOF_INT_ENA_S  4
/* SPI_IN_DONE_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:用于完成内联描述符使用的启用位。可在形态状态下配置。*/
#define SPI_IN_DONE_INT_ENA  (BIT(3))
#define SPI_IN_DONE_INT_ENA_M  (BIT(3))
#define SPI_IN_DONE_INT_ENA_V  0x1
#define SPI_IN_DONE_INT_ENA_S  3
/* SPI_INLINK_DSCR_ERROR_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的启用位。可在形态状态下配置。*/
#define SPI_INLINK_DSCR_ERROR_INT_ENA  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ENA_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ENA_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_ENA_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的启用位。可在形态状态下配置。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够内联描述符的启用位。可在形态状态下配置。*/
#define SPI_INLINK_DSCR_EMPTY_INT_ENA  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ENA_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ENA_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_ENA_S  0

#define SPI_DMA_INT_RAW_REG(i)          (REG_SPI_BASE(i) + 0x05C)
/* SPI_SLV_CMDA_INT_RAW:R/W；位位置：[15]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的原始位。*/
#define SPI_SLV_CMDA_INT_RAW  (BIT(15))
#define SPI_SLV_CMDA_INT_RAW_M  (BIT(15))
#define SPI_SLV_CMDA_INT_RAW_V  0x1
#define SPI_SLV_CMDA_INT_RAW_S  15
/* SPI_SLV_CMD9_INT_RAW:R/W；位位置：[14]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的原始位。*/
#define SPI_SLV_CMD9_INT_RAW  (BIT(14))
#define SPI_SLV_CMD9_INT_RAW_M  (BIT(14))
#define SPI_SLV_CMD9_INT_RAW_V  0x1
#define SPI_SLV_CMD9_INT_RAW_S  14
/* SPI_SLV_CMD8_INT_RAW:R/W；位位置：[13]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的原始位。*/
#define SPI_SLV_CMD8_INT_RAW  (BIT(13))
#define SPI_SLV_CMD8_INT_RAW_M  (BIT(13))
#define SPI_SLV_CMD8_INT_RAW_V  0x1
#define SPI_SLV_CMD8_INT_RAW_S  13
/* SPI_SLV_CMD7_INT_RAW：R/W；位位置：[12]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的原始位。*/
#define SPI_SLV_CMD7_INT_RAW  (BIT(12))
#define SPI_SLV_CMD7_INT_RAW_M  (BIT(12))
#define SPI_SLV_CMD7_INT_RAW_V  0x1
#define SPI_SLV_CMD7_INT_RAW_S  12
/* SPI_SLV_CMD6_INT_RAW：R/W；位位置：[11]；默认值：1’b0；*/
/*description:SPI从属CMD6中断的原始位。*/
#define SPI_SLV_CMD6_INT_RAW  (BIT(11))
#define SPI_SLV_CMD6_INT_RAW_M  (BIT(11))
#define SPI_SLV_CMD6_INT_RAW_V  0x1
#define SPI_SLV_CMD6_INT_RAW_S  11
/* SPI_OUTFIFO_EMPTY_ERR_INT_RAW:RO；位位置：[10]；默认值：1’b0；*/
/*描述：1:spi_dma_outfifoempty和spi_pop_data_prep有效，这意味着没有要弹出的数据，但pop有效。0：其他。无法通过CONF_buf更改。*/
#define SPI_OUTFIFO_EMPTY_ERR_INT_RAW  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_RAW_M  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_RAW_V  0x1
#define SPI_OUTFIFO_EMPTY_ERR_INT_RAW_S  10
/* SPI_INFIFO_FULL_ERR_INT_RAW:RO；位位置：[9]；默认值：1’b0；*/
/*描述：1:spi_dma_infifo_full和spi_push_data_prep有效，这意味着dma Rx缓冲区已满，但push有效。0：其他。无法通过CONF_buf更改。*/
#define SPI_INFIFO_FULL_ERR_INT_RAW  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_RAW_M  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_RAW_V  0x1
#define SPI_INFIFO_FULL_ERR_INT_RAW_S  9
/* SPI_OUT_TOTAL_EOF_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*description:将所有数据包发送到主机的原始位已完成。可在形态状态下配置。*/
#define SPI_OUT_TOTAL_EOF_INT_RAW  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_RAW_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_RAW_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_RAW_S  8
/* SPI_OUT_EOF_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的原始位已完成。可在形态状态下配置。*/
#define SPI_OUT_EOF_INT_RAW  (BIT(7))
#define SPI_OUT_EOF_INT_RAW_M  (BIT(7))
#define SPI_OUT_EOF_INT_RAW_V  0x1
#define SPI_OUT_EOF_INT_RAW_S  7
/* SPI_OUT_DONE_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的原始位。可在形态状态下配置。*/
#define SPI_OUT_DONE_INT_RAW  (BIT(6))
#define SPI_OUT_DONE_INT_RAW_M  (BIT(6))
#define SPI_OUT_DONE_INT_RAW_V  0x1
#define SPI_OUT_DONE_INT_RAW_S  6
/* SPI_IN_SUC_EOF_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*description:完成从主机接收所有数据包的原始位。可在形态状态下配置。*/
#define SPI_IN_SUC_EOF_INT_RAW  (BIT(5))
#define SPI_IN_SUC_EOF_INT_RAW_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_RAW_V  0x1
#define SPI_IN_SUC_EOF_INT_RAW_S  5
/* SPI_IN_ERR_EOF_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的原始位。可在形态状态下配置。*/
#define SPI_IN_ERR_EOF_INT_RAW  (BIT(4))
#define SPI_IN_ERR_EOF_INT_RAW_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_RAW_V  0x1
#define SPI_IN_ERR_EOF_INT_RAW_S  4
/* SPI_IN_DONE_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*description:完成内联描述符使用的原始位。可在形态状态下配置。*/
#define SPI_IN_DONE_INT_RAW  (BIT(3))
#define SPI_IN_DONE_INT_RAW_M  (BIT(3))
#define SPI_IN_DONE_INT_RAW_V  0x1
#define SPI_IN_DONE_INT_RAW_S  3
/* SPI_INLINK_DSCR_ERROR_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的原始位。可在形态状态下配置。*/
#define SPI_INLINK_DSCR_ERROR_INT_RAW  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_RAW_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_RAW_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_RAW_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的原始位。可在形态状态下配置。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够的内联描述符的原始位。可在形态状态下配置。*/
#define SPI_INLINK_DSCR_EMPTY_INT_RAW  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_RAW_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_RAW_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_RAW_S  0

#define SPI_DMA_INT_ST_REG(i)          (REG_SPI_BASE(i) + 0x060)
/* SPI_SLV_CMDA_INT_ST:R/W；位位置：[15]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的状态位。*/
#define SPI_SLV_CMDA_INT_ST  (BIT(15))
#define SPI_SLV_CMDA_INT_ST_M  (BIT(15))
#define SPI_SLV_CMDA_INT_ST_V  0x1
#define SPI_SLV_CMDA_INT_ST_S  15
/* SPI_SLV_CMD9_INT_ST:R/W；位位置：[14]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的状态位。*/
#define SPI_SLV_CMD9_INT_ST  (BIT(14))
#define SPI_SLV_CMD9_INT_ST_M  (BIT(14))
#define SPI_SLV_CMD9_INT_ST_V  0x1
#define SPI_SLV_CMD9_INT_ST_S  14
/* SPI_SLV_CMD8_INT_ST:R/W；位位置：[13]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的状态位。*/
#define SPI_SLV_CMD8_INT_ST  (BIT(13))
#define SPI_SLV_CMD8_INT_ST_M  (BIT(13))
#define SPI_SLV_CMD8_INT_ST_V  0x1
#define SPI_SLV_CMD8_INT_ST_S  13
/* SPI_SLV_CMD7_INT_ST:R/W；位位置：[12]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的状态位。*/
#define SPI_SLV_CMD7_INT_ST  (BIT(12))
#define SPI_SLV_CMD7_INT_ST_M  (BIT(12))
#define SPI_SLV_CMD7_INT_ST_V  0x1
#define SPI_SLV_CMD7_INT_ST_S  12
/* SPI_SLV_CMD6_INT_ST:R/W；位位置：[11]；默认值：1’b0；*/
/*description:SPI从属CMD6中断的状态位。*/
#define SPI_SLV_CMD6_INT_ST  (BIT(11))
#define SPI_SLV_CMD6_INT_ST_M  (BIT(11))
#define SPI_SLV_CMD6_INT_ST_V  0x1
#define SPI_SLV_CMD6_INT_ST_S  11
/* SPI_OUTFIFO_EMPTY_ERR_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:outifo空错误的状态位。*/
#define SPI_OUTFIFO_EMPTY_ERR_INT_ST  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_ST_M  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_ST_V  0x1
#define SPI_OUTFIFO_EMPTY_ERR_INT_ST_S  10
/* SPI_INFIFO_FULL_ERR_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:infinfo完全错误的状态位。*/
#define SPI_INFIFO_FULL_ERR_INT_ST  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_ST_M  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_ST_V  0x1
#define SPI_INFIFO_FULL_ERR_INT_ST_S  9
/* SPI_OUT_TOTAL_EOF_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:向主机发送所有数据包的状态位已完成。*/
#define SPI_OUT_TOTAL_EOF_INT_ST  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ST_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ST_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_ST_S  8
/* SPI_OUT_EOF_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的状态位已完成。*/
#define SPI_OUT_EOF_INT_ST  (BIT(7))
#define SPI_OUT_EOF_INT_ST_M  (BIT(7))
#define SPI_OUT_EOF_INT_ST_V  0x1
#define SPI_OUT_EOF_INT_ST_S  7
/* SPI_OUT_DONE_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的状态位。*/
#define SPI_OUT_DONE_INT_ST  (BIT(6))
#define SPI_OUT_DONE_INT_ST_M  (BIT(6))
#define SPI_OUT_DONE_INT_ST_V  0x1
#define SPI_OUT_DONE_INT_ST_S  6
/* SPI_IN_SUC_EOF_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:完成从主机接收所有数据包的状态位。*/
#define SPI_IN_SUC_EOF_INT_ST  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ST_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ST_V  0x1
#define SPI_IN_SUC_EOF_INT_ST_S  5
/* SPI_IN_ERR_EOF_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的状态位。*/
#define SPI_IN_ERR_EOF_INT_ST  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ST_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ST_V  0x1
#define SPI_IN_ERR_EOF_INT_ST_S  4
/* SPI_IN_DONE_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:完成内联描述符使用的状态位。*/
#define SPI_IN_DONE_INT_ST  (BIT(3))
#define SPI_IN_DONE_INT_ST_M  (BIT(3))
#define SPI_IN_DONE_INT_ST_V  0x1
#define SPI_IN_DONE_INT_ST_S  3
/* SPI_INLINK_DSCR_ERROR_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的状态位。*/
#define SPI_INLINK_DSCR_ERROR_INT_ST  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ST_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ST_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_ST_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的状态位。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_ST  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ST_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ST_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_ST_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够的内联描述符的状态位。*/
#define SPI_INLINK_DSCR_EMPTY_INT_ST  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ST_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ST_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_ST_S  0

#define SPI_DMA_INT_CLR_REG(i)          (REG_SPI_BASE(i) + 0x064)
/* SPI_SLV_CMDA_INT_CLR:R/W；位位置：[15]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的清除位。*/
#define SPI_SLV_CMDA_INT_CLR  (BIT(15))
#define SPI_SLV_CMDA_INT_CLR_M  (BIT(15))
#define SPI_SLV_CMDA_INT_CLR_V  0x1
#define SPI_SLV_CMDA_INT_CLR_S  15
/* SPI_SLV_CMD9_INT_CLR:R/W；位位置：[14]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的清除位。*/
#define SPI_SLV_CMD9_INT_CLR  (BIT(14))
#define SPI_SLV_CMD9_INT_CLR_M  (BIT(14))
#define SPI_SLV_CMD9_INT_CLR_V  0x1
#define SPI_SLV_CMD9_INT_CLR_S  14
/* SPI_SLV_CMD8_INT_CLR:R/W；位位置：[13]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的清除位。*/
#define SPI_SLV_CMD8_INT_CLR  (BIT(13))
#define SPI_SLV_CMD8_INT_CLR_M  (BIT(13))
#define SPI_SLV_CMD8_INT_CLR_V  0x1
#define SPI_SLV_CMD8_INT_CLR_S  13
/* SPI_SLV_CMD7_INT_CLR:R/W；位位置：[12]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的清除位。*/
#define SPI_SLV_CMD7_INT_CLR  (BIT(12))
#define SPI_SLV_CMD7_INT_CLR_M  (BIT(12))
#define SPI_SLV_CMD7_INT_CLR_V  0x1
#define SPI_SLV_CMD7_INT_CLR_S  12
/* SPI_SLV_CMD6_INT_CLR:R/W；位位置：[11]；默认值：1’b0；*/
/*description:SPI从属CMD6中断的清除位。*/
#define SPI_SLV_CMD6_INT_CLR  (BIT(11))
#define SPI_SLV_CMD6_INT_CLR_M  (BIT(11))
#define SPI_SLV_CMD6_INT_CLR_V  0x1
#define SPI_SLV_CMD6_INT_CLR_S  11
/* SPI_OUTFIFO_EMPTY_ERR_INT_CLR:R/W；位位置：[10]；默认值：1’b0；*/
/*description:1：清除spi_dma_outfifo_empty_err信号。0:无效。可以通过CONF_buf更改。*/
#define SPI_OUTFIFO_EMPTY_ERR_INT_CLR  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_CLR_M  (BIT(10))
#define SPI_OUTFIFO_EMPTY_ERR_INT_CLR_V  0x1
#define SPI_OUTFIFO_EMPTY_ERR_INT_CLR_S  10
/* SPI_INFIFO_FULL_ERR_INT_CLR:R/W；位位置：[9]；默认值：1’b0；*/
/*description:1：清除spi_dma_infifo_full_err。0:无效。可以通过CONF_buf更改。*/
#define SPI_INFIFO_FULL_ERR_INT_CLR  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_CLR_M  (BIT(9))
#define SPI_INFIFO_FULL_ERR_INT_CLR_V  0x1
#define SPI_INFIFO_FULL_ERR_INT_CLR_S  9
/* SPI_OUT_TOTAL_EOF_INT_CLR:R/W；位位置：[8]；默认值：1’b0；*/
/*description:将所有数据包发送到主机的清除位已完成。可在形态状态下配置。*/
#define SPI_OUT_TOTAL_EOF_INT_CLR  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_CLR_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_CLR_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_CLR_S  8
/* 输出_输出_输入_输出_输出：R/W；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的清除位已完成。可在形态状态下配置。*/
#define SPI_OUT_EOF_INT_CLR  (BIT(7))
#define SPI_OUT_EOF_INT_CLR_M  (BIT(7))
#define SPI_OUT_EOF_INT_CLR_V  0x1
#define SPI_OUT_EOF_INT_CLR_S  7
/* SPI_OUT_DONE_INT_CLR:R/W；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的清除位。可在形态状态下配置。*/
#define SPI_OUT_DONE_INT_CLR  (BIT(6))
#define SPI_OUT_DONE_INT_CLR_M  (BIT(6))
#define SPI_OUT_DONE_INT_CLR_V  0x1
#define SPI_OUT_DONE_INT_CLR_S  6
/* SPI_IN_SUC_EOF_INT_CLR:R/W；位位置：[5]；默认值：1’b0；*/
/*description:完成从主机接收所有数据包的清除位。可在形态状态下配置。*/
#define SPI_IN_SUC_EOF_INT_CLR  (BIT(5))
#define SPI_IN_SUC_EOF_INT_CLR_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_CLR_V  0x1
#define SPI_IN_SUC_EOF_INT_CLR_S  5
/* SPI_IN_ERR_EOF_INT_CLR:R/W；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的清除位。可在形态状态下配置。*/
#define SPI_IN_ERR_EOF_INT_CLR  (BIT(4))
#define SPI_IN_ERR_EOF_INT_CLR_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_CLR_V  0x1
#define SPI_IN_ERR_EOF_INT_CLR_S  4
/* SPI_IN_DONE_INT_CLR:R/W；位位置：[3]；默认值：1’b0；*/
/*description:用于完成内联描述符使用的清除位。可在形态状态下配置。*/
#define SPI_IN_DONE_INT_CLR  (BIT(3))
#define SPI_IN_DONE_INT_CLR_M  (BIT(3))
#define SPI_IN_DONE_INT_CLR_V  0x1
#define SPI_IN_DONE_INT_CLR_S  3
/* SPI_INLINK_DSCR_ERROR_INT_CLR:R/W；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的清除位。可在形态状态下配置。*/
#define SPI_INLINK_DSCR_ERROR_INT_CLR  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_CLR_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_CLR_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_CLR_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_CLR:R/W；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的清除位。可在形态状态下配置。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_CLR:R/W；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够的内联描述符的清除位。可在形态状态下配置。*/
#define SPI_INLINK_DSCR_EMPTY_INT_CLR  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_CLR_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_CLR_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_CLR_S  0

#define SPI_IN_ERR_EOF_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x068)
/* SPI_DMA_IN_ERR_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:spidma产生接收错误时的内联描述符地址。*/
#define SPI_DMA_IN_ERR_EOF_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_IN_ERR_EOF_DES_ADDR_M  ((SPI_DMA_IN_ERR_EOF_DES_ADDR_V)<<(SPI_DMA_IN_ERR_EOF_DES_ADDR_S))
#define SPI_DMA_IN_ERR_EOF_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_IN_ERR_EOF_DES_ADDR_S  0

#define SPI_IN_SUC_EOF_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x06C)
/* SPI_DMA_IN_SUC_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:spidma生成from_suc_eof时的最后一个内联描述符地址。*/
#define SPI_DMA_IN_SUC_EOF_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_IN_SUC_EOF_DES_ADDR_M  ((SPI_DMA_IN_SUC_EOF_DES_ADDR_V)<<(SPI_DMA_IN_SUC_EOF_DES_ADDR_S))
#define SPI_DMA_IN_SUC_EOF_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_IN_SUC_EOF_DES_ADDR_S  0

#define SPI_INLINK_DSCR_REG(i)          (REG_SPI_BASE(i) + 0x070)
/* SPI_DMA_INLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前在描述符指针中的内容。*/
#define SPI_DMA_INLINK_DSCR  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_M  ((SPI_DMA_INLINK_DSCR_V)<<(SPI_DMA_INLINK_DSCR_S))
#define SPI_DMA_INLINK_DSCR_V  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_S  0

#define SPI_INLINK_DSCR_BF0_REG(i)          (REG_SPI_BASE(i) + 0x074)
/* SPI_DMA_INLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:描述符指针中next的内容。*/
#define SPI_DMA_INLINK_DSCR_BF0  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF0_M  ((SPI_DMA_INLINK_DSCR_BF0_V)<<(SPI_DMA_INLINK_DSCR_BF0_S))
#define SPI_DMA_INLINK_DSCR_BF0_V  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF0_S  0

#define SPI_INLINK_DSCR_BF1_REG(i)          (REG_SPI_BASE(i) + 0x078)
/* SPI_DMA_INLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:描述符中当前数据缓冲区指针的内容。*/
#define SPI_DMA_INLINK_DSCR_BF1  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF1_M  ((SPI_DMA_INLINK_DSCR_BF1_V)<<(SPI_DMA_INLINK_DSCR_BF1_S))
#define SPI_DMA_INLINK_DSCR_BF1_V  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF1_S  0

#define SPI_OUT_EOF_BFR_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x07C)
/* SPI_DMA_OUT_EOF_BFR_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:相对于产生eof的outlink描述符的缓冲区地址。*/
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR_M  ((SPI_DMA_OUT_EOF_BFR_DES_ADDR_V)<<(SPI_DMA_OUT_EOF_BFR_DES_ADDR_S))
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR_S  0

#define SPI_OUT_EOF_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x080)
/* SPI_DMA_OUT_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:spidma生成to_eof时的最后一个outlink描述符地址。*/
#define SPI_DMA_OUT_EOF_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_DES_ADDR_M  ((SPI_DMA_OUT_EOF_DES_ADDR_V)<<(SPI_DMA_OUT_EOF_DES_ADDR_S))
#define SPI_DMA_OUT_EOF_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_DES_ADDR_S  0

#define SPI_OUTLINK_DSCR_REG(i)          (REG_SPI_BASE(i) + 0x084)
/* SPI_DMA_OUTLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出描述符指针的内容。*/
#define SPI_DMA_OUTLINK_DSCR  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_M  ((SPI_DMA_OUTLINK_DSCR_V)<<(SPI_DMA_OUTLINK_DSCR_S))
#define SPI_DMA_OUTLINK_DSCR_V  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_S  0

#define SPI_OUTLINK_DSCR_BF0_REG(i)          (REG_SPI_BASE(i) + 0x088)
/* SPI_DMA_OUTLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:next-out描述符指针的内容。*/
#define SPI_DMA_OUTLINK_DSCR_BF0  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF0_M  ((SPI_DMA_OUTLINK_DSCR_BF0_V)<<(SPI_DMA_OUTLINK_DSCR_BF0_S))
#define SPI_DMA_OUTLINK_DSCR_BF0_V  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF0_S  0

#define SPI_OUTLINK_DSCR_BF1_REG(i)          (REG_SPI_BASE(i) + 0x08C)
/* SPI_DMA_OUTLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出描述符数据缓冲区指针的内容。*/
#define SPI_DMA_OUTLINK_DSCR_BF1  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF1_M  ((SPI_DMA_OUTLINK_DSCR_BF1_V)<<(SPI_DMA_OUTLINK_DSCR_BF1_S))
#define SPI_DMA_OUTLINK_DSCR_BF1_V  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF1_S  0

#define SPI_DMA_OUTSTATUS_REG(i)          (REG_SPI_BASE(i) + 0x090)
/* SPI_DMA_OUTFIFO空：RO；位位置：[31]；默认值：1’b1；*/
/*description:SPI dma outifo为空。*/
#define SPI_DMA_OUTFIFO_EMPTY  (BIT(31))
#define SPI_DMA_OUTFIFO_EMPTY_M  (BIT(31))
#define SPI_DMA_OUTFIFO_EMPTY_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_S  31
/* SPI_DMA_OUTFIFO_FULL:RO；位位置：[30]；默认值：1’b0；*/
/*描述：SPI dma outifo已满。*/
#define SPI_DMA_OUTFIFO_FULL  (BIT(30))
#define SPI_DMA_OUTFIFO_FULL_M  (BIT(30))
#define SPI_DMA_OUTFIFO_FULL_V  0x1
#define SPI_DMA_OUTFIFO_FULL_S  30
/* SPI_DMA_OUTFIFO_CNT:RO；位位置：[29:23]；默认值：7'b0；*/
/*description:SPI dma outifo数据的剩余部分。*/
#define SPI_DMA_OUTFIFO_CNT  0x0000007F
#define SPI_DMA_OUTFIFO_CNT_M  ((SPI_DMA_OUTFIFO_CNT_V)<<(SPI_DMA_OUTFIFO_CNT_S))
#define SPI_DMA_OUTFIFO_CNT_V  0x7F
#define SPI_DMA_OUTFIFO_CNT_S  23
/* SPI_DMA_OUT_STATE:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:SPI dma out数据状态。*/
#define SPI_DMA_OUT_STATE  0x00000007
#define SPI_DMA_OUT_STATE_M  ((SPI_DMA_OUT_STATE_V)<<(SPI_DMA_OUT_STATE_S))
#define SPI_DMA_OUT_STATE_V  0x7
#define SPI_DMA_OUT_STATE_S  20
/* SPI_DMA_OUTDSCR_STATE:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:SPI dma输出描述符状态。*/
#define SPI_DMA_OUTDSCR_STATE  0x00000003
#define SPI_DMA_OUTDSCR_STATE_M  ((SPI_DMA_OUTDSCR_STATE_V)<<(SPI_DMA_OUTDSCR_STATE_S))
#define SPI_DMA_OUTDSCR_STATE_V  0x3
#define SPI_DMA_OUTDSCR_STATE_S  18
/* SPI_DMA_OUTDSCR_ADDR:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:SPI dma输出描述符地址。*/
#define SPI_DMA_OUTDSCR_ADDR  0x0003FFFF
#define SPI_DMA_OUTDSCR_ADDR_M  ((SPI_DMA_OUTDSCR_ADDR_V)<<(SPI_DMA_OUTDSCR_ADDR_S))
#define SPI_DMA_OUTDSCR_ADDR_V  0x3FFFF
#define SPI_DMA_OUTDSCR_ADDR_S  0

#define SPI_DMA_INSTATUS_REG(i)          (REG_SPI_BASE(i) + 0x094)
/* SPI_DMA_INFIFO空：RO；位位置：[31]；默认值：1’b1；*/
/*description:SPI dma infinfo为空。*/
#define SPI_DMA_INFIFO_EMPTY  (BIT(31))
#define SPI_DMA_INFIFO_EMPTY_M  (BIT(31))
#define SPI_DMA_INFIFO_EMPTY_V  0x1
#define SPI_DMA_INFIFO_EMPTY_S  31
/* SPI_DMA_infifofull:RO；位位置：[30]；默认值：1’b0；*/
/*description:SPI dma infinfo已满。*/
#define SPI_DMA_INFIFO_FULL  (BIT(30))
#define SPI_DMA_INFIFO_FULL_M  (BIT(30))
#define SPI_DMA_INFIFO_FULL_V  0x1
#define SPI_DMA_INFIFO_FULL_S  30
/* SPI_DMA_INFIFO_CNT:RO；位位置：[29:23]；默认值：7'b0；*/
/*description:SPI dma infinfo数据的剩余部分。*/
#define SPI_DMA_INFIFO_CNT  0x0000007F
#define SPI_DMA_INFIFO_CNT_M  ((SPI_DMA_INFIFO_CNT_V)<<(SPI_DMA_INFIFO_CNT_S))
#define SPI_DMA_INFIFO_CNT_V  0x7F
#define SPI_DMA_INFIFO_CNT_S  23
/* SPI_DMA_IN_STATE:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:SPI dma处于数据状态。*/
#define SPI_DMA_IN_STATE  0x00000007
#define SPI_DMA_IN_STATE_M  ((SPI_DMA_IN_STATE_V)<<(SPI_DMA_IN_STATE_S))
#define SPI_DMA_IN_STATE_V  0x7
#define SPI_DMA_IN_STATE_S  20
/* SPI_DMA_INDSCR_STATE:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:SPI dma处于描述符状态。*/
#define SPI_DMA_INDSCR_STATE  0x00000003
#define SPI_DMA_INDSCR_STATE_M  ((SPI_DMA_INDSCR_STATE_V)<<(SPI_DMA_INDSCR_STATE_S))
#define SPI_DMA_INDSCR_STATE_V  0x3
#define SPI_DMA_INDSCR_STATE_S  18
/* SPI_DMA_INDSCR_ADDR:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:描述符地址中的SPI dma。*/
#define SPI_DMA_INDSCR_ADDR  0x0003FFFF
#define SPI_DMA_INDSCR_ADDR_M  ((SPI_DMA_INDSCR_ADDR_V)<<(SPI_DMA_INDSCR_ADDR_S))
#define SPI_DMA_INDSCR_ADDR_V  0x3FFFF
#define SPI_DMA_INDSCR_ADDR_S  0

#define SPI_W0_REG(i)          (REG_SPI_BASE(i) + 0x098)
/* SPI_BUF0:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF0  0xFFFFFFFF
#define SPI_BUF0_M  ((SPI_BUF0_V)<<(SPI_BUF0_S))
#define SPI_BUF0_V  0xFFFFFFFF
#define SPI_BUF0_S  0

#define SPI_W1_REG(i)          (REG_SPI_BASE(i) + 0x09C)
/* SPI_BUF1:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF1  0xFFFFFFFF
#define SPI_BUF1_M  ((SPI_BUF1_V)<<(SPI_BUF1_S))
#define SPI_BUF1_V  0xFFFFFFFF
#define SPI_BUF1_S  0

#define SPI_W2_REG(i)          (REG_SPI_BASE(i) + 0x0A0)
/* SPI_BUF2:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF2  0xFFFFFFFF
#define SPI_BUF2_M  ((SPI_BUF2_V)<<(SPI_BUF2_S))
#define SPI_BUF2_V  0xFFFFFFFF
#define SPI_BUF2_S  0

#define SPI_W3_REG(i)          (REG_SPI_BASE(i) + 0x0A4)
/* SPI_BUF3:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF3  0xFFFFFFFF
#define SPI_BUF3_M  ((SPI_BUF3_V)<<(SPI_BUF3_S))
#define SPI_BUF3_V  0xFFFFFFFF
#define SPI_BUF3_S  0

#define SPI_W4_REG(i)          (REG_SPI_BASE(i) + 0x0A8)
/* SPI_BUF4:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF4  0xFFFFFFFF
#define SPI_BUF4_M  ((SPI_BUF4_V)<<(SPI_BUF4_S))
#define SPI_BUF4_V  0xFFFFFFFF
#define SPI_BUF4_S  0

#define SPI_W5_REG(i)          (REG_SPI_BASE(i) + 0x0AC)
/* SPI_BUF5:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF5  0xFFFFFFFF
#define SPI_BUF5_M  ((SPI_BUF5_V)<<(SPI_BUF5_S))
#define SPI_BUF5_V  0xFFFFFFFF
#define SPI_BUF5_S  0

#define SPI_W6_REG(i)          (REG_SPI_BASE(i) + 0x0B0)
/* SPI_BUF6:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF6  0xFFFFFFFF
#define SPI_BUF6_M  ((SPI_BUF6_V)<<(SPI_BUF6_S))
#define SPI_BUF6_V  0xFFFFFFFF
#define SPI_BUF6_S  0

#define SPI_W7_REG(i)          (REG_SPI_BASE(i) + 0x0B4)
/* SPI_BUF7:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF7  0xFFFFFFFF
#define SPI_BUF7_M  ((SPI_BUF7_V)<<(SPI_BUF7_S))
#define SPI_BUF7_V  0xFFFFFFFF
#define SPI_BUF7_S  0

#define SPI_W8_REG(i)          (REG_SPI_BASE(i) + 0x0B8)
/* SPI_BUF8:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF8  0xFFFFFFFF
#define SPI_BUF8_M  ((SPI_BUF8_V)<<(SPI_BUF8_S))
#define SPI_BUF8_V  0xFFFFFFFF
#define SPI_BUF8_S  0

#define SPI_W9_REG(i)          (REG_SPI_BASE(i) + 0x0BC)
/* SPI_BUF9:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF9  0xFFFFFFFF
#define SPI_BUF9_M  ((SPI_BUF9_V)<<(SPI_BUF9_S))
#define SPI_BUF9_V  0xFFFFFFFF
#define SPI_BUF9_S  0

#define SPI_W10_REG(i)          (REG_SPI_BASE(i) + 0x0C0)
/* SPI_BUF10:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF10  0xFFFFFFFF
#define SPI_BUF10_M  ((SPI_BUF10_V)<<(SPI_BUF10_S))
#define SPI_BUF10_V  0xFFFFFFFF
#define SPI_BUF10_S  0

#define SPI_W11_REG(i)          (REG_SPI_BASE(i) + 0x0C4)
/* SPI_BUF11:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF11  0xFFFFFFFF
#define SPI_BUF11_M  ((SPI_BUF11_V)<<(SPI_BUF11_S))
#define SPI_BUF11_V  0xFFFFFFFF
#define SPI_BUF11_S  0

#define SPI_W12_REG(i)          (REG_SPI_BASE(i) + 0x0C8)
/* SPI_BUF12:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF12  0xFFFFFFFF
#define SPI_BUF12_M  ((SPI_BUF12_V)<<(SPI_BUF12_S))
#define SPI_BUF12_V  0xFFFFFFFF
#define SPI_BUF12_S  0

#define SPI_W13_REG(i)          (REG_SPI_BASE(i) + 0x0CC)
/* SPI_BUF13:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF13  0xFFFFFFFF
#define SPI_BUF13_M  ((SPI_BUF13_V)<<(SPI_BUF13_S))
#define SPI_BUF13_V  0xFFFFFFFF
#define SPI_BUF13_S  0

#define SPI_W14_REG(i)          (REG_SPI_BASE(i) + 0x0D0)
/* SPI_BUF14:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF14  0xFFFFFFFF
#define SPI_BUF14_M  ((SPI_BUF14_V)<<(SPI_BUF14_S))
#define SPI_BUF14_V  0xFFFFFFFF
#define SPI_BUF14_S  0

#define SPI_W15_REG(i)          (REG_SPI_BASE(i) + 0x0D4)
/* SPI_BUF15:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF15  0xFFFFFFFF
#define SPI_BUF15_M  ((SPI_BUF15_V)<<(SPI_BUF15_S))
#define SPI_BUF15_V  0xFFFFFFFF
#define SPI_BUF15_S  0

#define SPI_W16_REG(i)          (REG_SPI_BASE(i) + 0x0D8)
/* SPI_BUF16:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF16  0xFFFFFFFF
#define SPI_BUF16_M  ((SPI_BUF16_V)<<(SPI_BUF16_S))
#define SPI_BUF16_V  0xFFFFFFFF
#define SPI_BUF16_S  0

#define SPI_W17_REG(i)          (REG_SPI_BASE(i) + 0x0DC)
/* SPI_BUF17:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF17  0xFFFFFFFF
#define SPI_BUF17_M  ((SPI_BUF17_V)<<(SPI_BUF17_S))
#define SPI_BUF17_V  0xFFFFFFFF
#define SPI_BUF17_S  0

#define SPI_DIN_MODE_REG(i)          (REG_SPI_BASE(i) + 0x0E0)
/* SPI_TIMING_CLK_ENA:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：1：在spitiming中启用hclk。v.0：禁用它。可在形态状态下配置。*/
#define SPI_TIMING_CLK_ENA  (BIT(24))
#define SPI_TIMING_CLK_ENA_M  (BIT(24))
#define SPI_TIMING_CLK_ENA_V  0x1
#define SPI_TIMING_CLK_ENA_S  24
/* SPI_DIN7模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN7_MODE  0x00000007
#define SPI_DIN7_MODE_M  ((SPI_DIN7_MODE_V)<<(SPI_DIN7_MODE_S))
#define SPI_DIN7_MODE_V  0x7
#define SPI_DIN7_MODE_S  21
/* SPI_DIN6_MODE：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN6_MODE  0x00000007
#define SPI_DIN6_MODE_M  ((SPI_DIN6_MODE_V)<<(SPI_DIN6_MODE_S))
#define SPI_DIN6_MODE_V  0x7
#define SPI_DIN6_MODE_S  18
/* SPI_DIN5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN5_MODE  0x00000007
#define SPI_DIN5_MODE_M  ((SPI_DIN5_MODE_V)<<(SPI_DIN5_MODE_S))
#define SPI_DIN5_MODE_V  0x7
#define SPI_DIN5_MODE_S  15
/* SPI_DIN4_MODE：R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN4_MODE  0x00000007
#define SPI_DIN4_MODE_M  ((SPI_DIN4_MODE_V)<<(SPI_DIN4_MODE_S))
#define SPI_DIN4_MODE_V  0x7
#define SPI_DIN4_MODE_S  12
/* SPI_DIN3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN3_MODE  0x00000007
#define SPI_DIN3_MODE_M  ((SPI_DIN3_MODE_V)<<(SPI_DIN3_MODE_S))
#define SPI_DIN3_MODE_V  0x7
#define SPI_DIN3_MODE_S  9
/* SPI_din_模式：R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN2_MODE  0x00000007
#define SPI_DIN2_MODE_M  ((SPI_DIN2_MODE_V)<<(SPI_DIN2_MODE_S))
#define SPI_DIN2_MODE_V  0x7
#define SPI_DIN2_MODE_S  6
/* SPI_DIN1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN1_MODE  0x00000007
#define SPI_DIN1_MODE_M  ((SPI_DIN1_MODE_V)<<(SPI_DIN1_MODE_S))
#define SPI_DIN1_MODE_V  0x7
#define SPI_DIN1_MODE_S  3
/* SPI_DIN0_MODE：R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期0延迟：输入而不延迟1：输入clk_apb 2的偏倚，输入clk.apb 3的负边，输入spiclk。可在形态状态下配置。*/
#define SPI_DIN0_MODE  0x00000007
#define SPI_DIN0_MODE_M  ((SPI_DIN0_MODE_V)<<(SPI_DIN0_MODE_S))
#define SPI_DIN0_MODE_V  0x7
#define SPI_DIN0_MODE_S  0

#define SPI_DIN_NUM_REG(i)          (REG_SPI_BASE(i) + 0x0E4)
/* SPI_DIN7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN7_NUM  0x00000003
#define SPI_DIN7_NUM_M  ((SPI_DIN7_NUM_V)<<(SPI_DIN7_NUM_S))
#define SPI_DIN7_NUM_V  0x3
#define SPI_DIN7_NUM_S  14
/* SPI_DIN6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN6_NUM  0x00000003
#define SPI_DIN6_NUM_M  ((SPI_DIN6_NUM_V)<<(SPI_DIN6_NUM_S))
#define SPI_DIN6_NUM_V  0x3
#define SPI_DIN6_NUM_S  12
/* SPI_DIN5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN5_NUM  0x00000003
#define SPI_DIN5_NUM_M  ((SPI_DIN5_NUM_V)<<(SPI_DIN5_NUM_S))
#define SPI_DIN5_NUM_V  0x3
#define SPI_DIN5_NUM_S  10
/* SPI_DIN4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN4_NUM  0x00000003
#define SPI_DIN4_NUM_M  ((SPI_DIN4_NUM_V)<<(SPI_DIN4_NUM_S))
#define SPI_DIN4_NUM_V  0x3
#define SPI_DIN4_NUM_S  8
/* SPI_DIN3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN3_NUM  0x00000003
#define SPI_DIN3_NUM_M  ((SPI_DIN3_NUM_V)<<(SPI_DIN3_NUM_S))
#define SPI_DIN3_NUM_V  0x3
#define SPI_DIN3_NUM_S  6
/* SPI_din_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN2_NUM  0x00000003
#define SPI_DIN2_NUM_M  ((SPI_DIN2_NUM_V)<<(SPI_DIN2_NUM_S))
#define SPI_DIN2_NUM_V  0x3
#define SPI_DIN2_NUM_S  4
/* SPI_DIN1_NUM：随机；位位置：[3:2]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN1_NUM  0x00000003
#define SPI_DIN1_NUM_M  ((SPI_DIN1_NUM_V)<<(SPI_DIN1_NUM_S))
#define SPI_DIN1_NUM_V  0x3
#define SPI_DIN1_NUM_S  2
/* SPI_DIN0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DIN0_NUM  0x00000003
#define SPI_DIN0_NUM_M  ((SPI_DIN0_NUM_V)<<(SPI_DIN0_NUM_S))
#define SPI_DIN0_NUM_V  0x3
#define SPI_DIN0_NUM_S  0

#define SPI_DOUT_MODE_REG(i)          (REG_SPI_BASE(i) + 0x0E8)
/* SPI_DOUT7_模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT7_MODE  0x00000007
#define SPI_DOUT7_MODE_M  ((SPI_DOUT7_MODE_V)<<(SPI_DOUT7_MODE_S))
#define SPI_DOUT7_MODE_V  0x7
#define SPI_DOUT7_MODE_S  21
/* SPI_DOUT6_MODE：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT6_MODE  0x00000007
#define SPI_DOUT6_MODE_M  ((SPI_DOUT6_MODE_V)<<(SPI_DOUT6_MODE_S))
#define SPI_DOUT6_MODE_V  0x7
#define SPI_DOUT6_MODE_S  18
/* SPI_DOUT5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT5_MODE  0x00000007
#define SPI_DOUT5_MODE_M  ((SPI_DOUT5_MODE_V)<<(SPI_DOUT5_MODE_S))
#define SPI_DOUT5_MODE_V  0x7
#define SPI_DOUT5_MODE_S  15
/* SPI_DOUT4_MODE：R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT4_MODE  0x00000007
#define SPI_DOUT4_MODE_M  ((SPI_DOUT4_MODE_V)<<(SPI_DOUT4_MODE_S))
#define SPI_DOUT4_MODE_V  0x7
#define SPI_DOUT4_MODE_S  12
/* SPI_DOUT3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT3_MODE  0x00000007
#define SPI_DOUT3_MODE_M  ((SPI_DOUT3_MODE_V)<<(SPI_DOUT3_MODE_S))
#define SPI_DOUT3_MODE_V  0x7
#define SPI_DOUT3_MODE_S  9
/* SPI_DOUT2_MODE：R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT2_MODE  0x00000007
#define SPI_DOUT2_MODE_M  ((SPI_DOUT2_MODE_V)<<(SPI_DOUT2_MODE_S))
#define SPI_DOUT2_MODE_V  0x7
#define SPI_DOUT2_MODE_S  6
/* SPI_DOUT1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT1_MODE  0x00000007
#define SPI_DOUT1_MODE_M  ((SPI_DOUT1_MODE_V)<<(SPI_DOUT1_MODE_S))
#define SPI_DOUT1_MODE_V  0x7
#define SPI_DOUT1_MODE_S  3
/* SPI_DOUT0_MODE：R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb 2的偏旁输出，带clk.apb 3的负边输出，带spiclk。可在形态状态下配置。*/
#define SPI_DOUT0_MODE  0x00000007
#define SPI_DOUT0_MODE_M  ((SPI_DOUT0_MODE_V)<<(SPI_DOUT0_MODE_S))
#define SPI_DOUT0_MODE_V  0x7
#define SPI_DOUT0_MODE_S  0

#define SPI_DOUT_NUM_REG(i)          (REG_SPI_BASE(i) + 0x0EC)
/* SPI_DOUT7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT7_NUM  0x00000003
#define SPI_DOUT7_NUM_M  ((SPI_DOUT7_NUM_V)<<(SPI_DOUT7_NUM_S))
#define SPI_DOUT7_NUM_V  0x3
#define SPI_DOUT7_NUM_S  14
/* SPI_DOUT6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT6_NUM  0x00000003
#define SPI_DOUT6_NUM_M  ((SPI_DOUT6_NUM_V)<<(SPI_DOUT6_NUM_S))
#define SPI_DOUT6_NUM_V  0x3
#define SPI_DOUT6_NUM_S  12
/* SPI_DOUT5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT5_NUM  0x00000003
#define SPI_DOUT5_NUM_M  ((SPI_DOUT5_NUM_V)<<(SPI_DOUT5_NUM_S))
#define SPI_DOUT5_NUM_V  0x3
#define SPI_DOUT5_NUM_S  10
/* SPI_DOUT4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT4_NUM  0x00000003
#define SPI_DOUT4_NUM_M  ((SPI_DOUT4_NUM_V)<<(SPI_DOUT4_NUM_S))
#define SPI_DOUT4_NUM_V  0x3
#define SPI_DOUT4_NUM_S  8
/* SPI_DOUT3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT3_NUM  0x00000003
#define SPI_DOUT3_NUM_M  ((SPI_DOUT3_NUM_V)<<(SPI_DOUT3_NUM_S))
#define SPI_DOUT3_NUM_V  0x3
#define SPI_DOUT3_NUM_S  6
/* SPI_DOUT2_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT2_NUM  0x00000003
#define SPI_DOUT2_NUM_M  ((SPI_DOUT2_NUM_V)<<(SPI_DOUT2_NUM_S))
#define SPI_DOUT2_NUM_V  0x3
#define SPI_DOUT2_NUM_S  4
/* SPI_DOUT1_NUM:R/W；位位置：[3:2]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT1_NUM  0x00000003
#define SPI_DOUT1_NUM_M  ((SPI_DOUT1_NUM_V)<<(SPI_DOUT1_NUM_S))
#define SPI_DOUT1_NUM_V  0x3
#define SPI_DOUT1_NUM_S  2
/* SPI_DOUT0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期…可配置为CONF状态。*/
#define SPI_DOUT0_NUM  0x00000003
#define SPI_DOUT0_NUM_M  ((SPI_DOUT0_NUM_V)<<(SPI_DOUT0_NUM_S))
#define SPI_DOUT0_NUM_V  0x3
#define SPI_DOUT0_NUM_S  0

#define SPI_LCD_CTRL_REG(i)          (REG_SPI_BASE(i) + 0x0F0)
/* SPI_LCD_MODE_EN:R/W；位位置：[31]；默认值：1’b0；*/
/*description:1：启用LCD模式输出vsync hsync de。0：禁用。可在形态状态下配置。*/
#define SPI_LCD_MODE_EN  (BIT(31))
#define SPI_LCD_MODE_EN_M  (BIT(31))
#define SPI_LCD_MODE_EN_V  0x1
#define SPI_LCD_MODE_EN_S  31
/* SPI_LCD_VT_HEIGHT:R/W；位位置：[30:21]；默认值：10'd0；*/
/*description:是框架的垂直总高度。可在形态状态下配置。*/
#define SPI_LCD_VT_HEIGHT  0x000003FF
#define SPI_LCD_VT_HEIGHT_M  ((SPI_LCD_VT_HEIGHT_V)<<(SPI_LCD_VT_HEIGHT_S))
#define SPI_LCD_VT_HEIGHT_V  0x3FF
#define SPI_LCD_VT_HEIGHT_S  21
/* SPI_LCD_VA_HEIGHT：R/W；比特位置：[20:11]；默认值：10'd0；*/
/*description:是框架的垂直活动高度。可在形态状态下配置。*/
#define SPI_LCD_VA_HEIGHT  0x000003FF
#define SPI_LCD_VA_HEIGHT_M  ((SPI_LCD_VA_HEIGHT_V)<<(SPI_LCD_VA_HEIGHT_S))
#define SPI_LCD_VA_HEIGHT_V  0x3FF
#define SPI_LCD_VA_HEIGHT_S  11
/* SPI_LCD_HB_FRONT:R/W；位位置：[10:0]；默认值：11'd0；*/
/*描述：这是一个框架的水平空白前门廊。可在形态状态下配置。*/
#define SPI_LCD_HB_FRONT  0x000007FF
#define SPI_LCD_HB_FRONT_M  ((SPI_LCD_HB_FRONT_V)<<(SPI_LCD_HB_FRONT_S))
#define SPI_LCD_HB_FRONT_V  0x7FF
#define SPI_LCD_HB_FRONT_S  0

#define SPI_LCD_CTRL1_REG(i)          (REG_SPI_BASE(i) + 0x0F4)
/* SPI_LCD_HT_WIDTH:R/W；位位置：[31:20]；默认值：12'd0；*/
/*description:这是一个框架的水平总宽度。可在形态状态下配置。*/
#define SPI_LCD_HT_WIDTH  0x00000FFF
#define SPI_LCD_HT_WIDTH_M  ((SPI_LCD_HT_WIDTH_V)<<(SPI_LCD_HT_WIDTH_S))
#define SPI_LCD_HT_WIDTH_V  0xFFF
#define SPI_LCD_HT_WIDTH_S  20
/* SPI_LCD_HA_WIDTH:R/W；比特位置：[19:8]；默认值：12'd0；*/
/*description:它是帧的水平活动宽度。可在形态状态下配置。*/
#define SPI_LCD_HA_WIDTH  0x00000FFF
#define SPI_LCD_HA_WIDTH_M  ((SPI_LCD_HA_WIDTH_V)<<(SPI_LCD_HA_WIDTH_S))
#define SPI_LCD_HA_WIDTH_V  0xFFF
#define SPI_LCD_HA_WIDTH_S  8
/* SPI_LCD_VB_FRONT:R/W；位位置：[7:0]；默认值：8'd0；*/
/*描述：这是一个框架的垂直空白前门廊。可在形态状态下配置。*/
#define SPI_LCD_VB_FRONT  0x000000FF
#define SPI_LCD_VB_FRONT_M  ((SPI_LCD_VB_FRONT_V)<<(SPI_LCD_VB_FRONT_S))
#define SPI_LCD_VB_FRONT_V  0xFF
#define SPI_LCD_VB_FRONT_S  0

#define SPI_LCD_CTRL2_REG(i)          (REG_SPI_BASE(i) + 0x0F8)
/* SPI_LCD_HSYNC_POSITION:R/W；位位置：[31:24]；默认值：8'd0；*/
/*description:这是一行中spi_hsync激活脉冲的位置。可在形态状态下配置。*/
#define SPI_LCD_HSYNC_POSITION  0x000000FF
#define SPI_LCD_HSYNC_POSITION_M  ((SPI_LCD_HSYNC_POSITION_V)<<(SPI_LCD_HSYNC_POSITION_S))
#define SPI_LCD_HSYNC_POSITION_V  0xFF
#define SPI_LCD_HSYNC_POSITION_S  24
/* SPI_HSYNC_IDLE_POL:R/W；位位置：[23]；默认值：1'd0；*/
/*description:spi_hsync的空闲值。可在形态状态下配置。*/
#define SPI_HSYNC_IDLE_POL  (BIT(23))
#define SPI_HSYNC_IDLE_POL_M  (BIT(23))
#define SPI_HSYNC_IDLE_POL_V  0x1
#define SPI_HSYNC_IDLE_POL_S  23
/* SPI_LCD_HSYNC_WIDTH:R/W；比特位置：[22:16]；默认值：7'd1；*/
/*description:这是一行中spi_hsync激活脉冲的位置。可在形态状态下配置。*/
#define SPI_LCD_HSYNC_WIDTH  0x0000007F
#define SPI_LCD_HSYNC_WIDTH_M  ((SPI_LCD_HSYNC_WIDTH_V)<<(SPI_LCD_HSYNC_WIDTH_S))
#define SPI_LCD_HSYNC_WIDTH_V  0x7F
#define SPI_LCD_HSYNC_WIDTH_S  16
/* SPI_VSYNC_IDLE_POL:R/W；位位置：[7]；默认值：1'd0；*/
/*description:spi_vsync的空闲值。可在形态状态下配置。*/
#define SPI_VSYNC_IDLE_POL  (BIT(7))
#define SPI_VSYNC_IDLE_POL_M  (BIT(7))
#define SPI_VSYNC_IDLE_POL_V  0x1
#define SPI_VSYNC_IDLE_POL_S  7
/* SPI_LCD_VSYNC_WIDTH:R/W；比特位置：[6:0]；默认值：7'd1；*/
/*description:这是一行中spi_vsync激活脉冲的位置。可在形态状态下配置。*/
#define SPI_LCD_VSYNC_WIDTH  0x0000007F
#define SPI_LCD_VSYNC_WIDTH_M  ((SPI_LCD_VSYNC_WIDTH_V)<<(SPI_LCD_VSYNC_WIDTH_S))
#define SPI_LCD_VSYNC_WIDTH_V  0x7F
#define SPI_LCD_VSYNC_WIDTH_S  0

#define SPI_LCD_D_MODE_REG(i)          (REG_SPI_BASE(i) + 0x0FC)
/* SPI_HS_BLANK_EN:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：1:spi_hsync的脉冲在seg trans或one trans的垂直消隐行中输出。0:spi_hsync脉冲仅在seg trans中的有源区行中有效。*/
#define SPI_HS_BLANK_EN  (BIT(16))
#define SPI_HS_BLANK_EN_M  (BIT(16))
#define SPI_HS_BLANK_EN_V  0x1
#define SPI_HS_BLANK_EN_S  16
/* SPI_DE_IDLE_POL:R/W；位位置：[15]；默认值：1'd0；*/
/*description:spi_de的空闲值。*/
#define SPI_DE_IDLE_POL  (BIT(15))
#define SPI_DE_IDLE_POL_M  (BIT(15))
#define SPI_DE_IDLE_POL_V  0x1
#define SPI_DE_IDLE_POL_S  15
/* SPI_D_VSYNC_MODE：R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输出spi_vsync被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spi_clk。可在形态状态下配置。*/
#define SPI_D_VSYNC_MODE  0x00000007
#define SPI_D_VSYNC_MODE_M  ((SPI_D_VSYNC_MODE_V)<<(SPI_D_VSYNC_MODE_S))
#define SPI_D_VSYNC_MODE_V  0x7
#define SPI_D_VSYNC_MODE_S  12
/* SPI_D_HSYNC_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输出spi_hsync被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
#define SPI_D_HSYNC_MODE  0x00000007
#define SPI_D_HSYNC_MODE_M  ((SPI_D_HSYNC_MODE_V)<<(SPI_D_HSYNC_MODE_S))
#define SPI_D_HSYNC_MODE_V  0x7
#define SPI_D_HSYNC_MODE_S  9
/* SPI_D_DE_MODE：R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输出spi_de被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
#define SPI_D_DE_MODE  0x00000007
#define SPI_D_DE_MODE_M  ((SPI_D_DE_MODE_V)<<(SPI_D_DE_MODE_S))
#define SPI_D_DE_MODE_V  0x7
#define SPI_D_DE_MODE_S  6
/* SPI_D_CD_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输出spi_cd被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spi_clk。可在形态状态下配置。*/
#define SPI_D_CD_MODE  0x00000007
#define SPI_D_CD_MODE_M  ((SPI_D_CD_MODE_V)<<(SPI_D_CD_MODE_S))
#define SPI_D_CD_MODE_V  0x7
#define SPI_D_CD_MODE_S  3
/* SPI_D_DQS_MODE：R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输出spidqs被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
#define SPI_D_DQS_MODE  0x00000007
#define SPI_D_DQS_MODE_M  ((SPI_D_DQS_MODE_V)<<(SPI_D_DQS_MODE_S))
#define SPI_D_DQS_MODE_V  0x7
#define SPI_D_DQS_MODE_S  0

#define SPI_LCD_D_NUM_REG(i)          (REG_SPI_BASE(i) + 0x100)
/* SPI_D_VSYNC_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输出spi_vsync延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
#define SPI_D_VSYNC_NUM  0x00000003
#define SPI_D_VSYNC_NUM_M  ((SPI_D_VSYNC_NUM_V)<<(SPI_D_VSYNC_NUM_S))
#define SPI_D_VSYNC_NUM_V  0x3
#define SPI_D_VSYNC_NUM_S  8
/* SPI_D_HSYNC_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*description:输出spi_hsync延迟了系统时钟周期0：延迟了1个周期1：延迟了2个周期……可以在CONF状态下配置。*/
#define SPI_D_HSYNC_NUM  0x00000003
#define SPI_D_HSYNC_NUM_M  ((SPI_D_HSYNC_NUM_V)<<(SPI_D_HSYNC_NUM_S))
#define SPI_D_HSYNC_NUM_V  0x3
#define SPI_D_HSYNC_NUM_S  6
/* SPI_D_DE_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输出spi_de延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
#define SPI_D_DE_NUM  0x00000003
#define SPI_D_DE_NUM_M  ((SPI_D_DE_NUM_V)<<(SPI_D_DE_NUM_S))
#define SPI_D_DE_NUM_V  0x3
#define SPI_D_DE_NUM_S  4
/* SPI_D_CD_NUM:R/W；位位置：[3:2]；默认值：2'h0；*/
/*description:输出spi_cd延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
#define SPI_D_CD_NUM  0x00000003
#define SPI_D_CD_NUM_M  ((SPI_D_CD_NUM_V)<<(SPI_D_CD_NUM_S))
#define SPI_D_CD_NUM_V  0x3
#define SPI_D_CD_NUM_S  2
/* SPI_D_DQS_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*description:输出spi_dqs延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
#define SPI_D_DQS_NUM  0x00000003
#define SPI_D_DQS_NUM_M  ((SPI_D_DQS_NUM_V)<<(SPI_D_DQS_NUM_S))
#define SPI_D_DQS_NUM_V  0x3
#define SPI_D_DQS_NUM_S  0

#define SPI_DATE_REG(i)          (REG_SPI_BASE(i) + 0x3FC)
/* SPI_日期：RW；位位置：[27:0]；默认值：28'h1907240；*/
/*description:SPI寄存器版本。*/
#define SPI_DATE  0x0FFFFFFF
#define SPI_DATE_M  ((SPI_DATE_V)<<(SPI_DATE_S))
#define SPI_DATE_V  0xFFFFFFF
#define SPI_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_REG_H_ */

