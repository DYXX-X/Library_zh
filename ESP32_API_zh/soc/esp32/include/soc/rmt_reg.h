// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef _SOC_RMT_REG_H_
#define _SOC_RMT_REG_H_

#include "soc.h"
#define RMT_CH0DATA_REG          (DR_REG_RMT_BASE + 0x0000)

#define RMT_CH1DATA_REG          (DR_REG_RMT_BASE + 0x0004)

#define RMT_CH2DATA_REG          (DR_REG_RMT_BASE + 0x0008)

#define RMT_CH3DATA_REG          (DR_REG_RMT_BASE + 0x000c)

#define RMT_CH4DATA_REG          (DR_REG_RMT_BASE + 0x0010)

#define RMT_CH5DATA_REG          (DR_REG_RMT_BASE + 0x0014)

#define RMT_CH6DATA_REG          (DR_REG_RMT_BASE + 0x0018)

#define RMT_CH7DATA_REG          (DR_REG_RMT_BASE + 0x001c)

#define RMT_CH0CONF0_REG          (DR_REG_RMT_BASE + 0x0020)
/* RMT_CLK_EN:R/W；位位置：[31]；默认值：1'0；*/
/*description:此位用于控制时钟。当软件配置RMT内部寄存器时，它控制寄存器时钟。*/
#define RMT_CLK_EN  (BIT(31))
#define RMT_CLK_EN_M  (BIT(31))
#define RMT_CLK_EN_V  0x1
#define RMT_CLK_EN_S  31
/* RMT_MEM_PD:R/W；位位置：[30]；默认值：1’b0；*/
/*description:此位用于减少内存消耗的功率。1： mem处于低功率状态。*/
#define RMT_MEM_PD  (BIT(30))
#define RMT_MEM_PD_M  (BIT(30))
#define RMT_MEM_PD_V  0x1
#define RMT_MEM_PD_S  30
/* RMT_CARRIER_OUT_LV_CH0:R/W；位位置：[29]；默认值：1’b1；*/
/*描述：此位用于配置信道的载波调制方式。1’b1：低输出电平传输1’b0：高输出电平传输。*/
#define RMT_CARRIER_OUT_LV_CH0  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH0_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH0_V  0x1
#define RMT_CARRIER_OUT_LV_CH0_S  29
/* RMT_CARRIER_EN_CH0:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道0的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH0  (BIT(28))
#define RMT_CARRIER_EN_CH0_M  (BIT(28))
#define RMT_CARRIER_EN_CH0_V  0x1
#define RMT_CARRIER_EN_CH0_S  28
/* RMT_MEM_SIZE_CH0:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道0的内存块数量。*/
#define RMT_MEM_SIZE_CH0  0x0000000F
#define RMT_MEM_SIZE_CH0_M  ((RMT_MEM_SIZE_CH0_V)<<(RMT_MEM_SIZE_CH0_S))
#define RMT_MEM_SIZE_CH0_V  0xF
#define RMT_MEM_SIZE_CH0_S  24
/* RMT_IDLE_THRES_CH0:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果在输入信号上没有检测到边缘的时间超过reg_idle_thres_ch0，则完成接收过程。*/
#define RMT_IDLE_THRES_CH0  0x0000FFFF
#define RMT_IDLE_THRES_CH0_M  ((RMT_IDLE_THRES_CH0_V)<<(RMT_IDLE_THRES_CH0_S))
#define RMT_IDLE_THRES_CH0_V  0xFFFF
#define RMT_IDLE_THRES_CH0_S  8
/* RMT_DIV_CNT_CH0:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道0中的分频器因数。*/
#define RMT_DIV_CNT_CH0  0x000000FF
#define RMT_DIV_CNT_CH0_M  ((RMT_DIV_CNT_CH0_V)<<(RMT_DIV_CNT_CH0_S))
#define RMT_DIV_CNT_CH0_V  0xFF
#define RMT_DIV_CNT_CH0_S  0

#define RMT_CH0CONF1_REG          (DR_REG_RMT_BASE + 0x0024)
/* RMT_IDLE_OUT_EN_CH0:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于IDLE状态的通道0的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH0  (BIT(19))
#define RMT_IDLE_OUT_EN_CH0_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH0_V  0x1
#define RMT_IDLE_OUT_EN_CH0_S  19
/* RMT_IDLE_OUT_LV_CH0:R/W；位位置：[18]；默认值：1’b0；*/
/*description:此位配置信道0在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH0  (BIT(18))
#define RMT_IDLE_OUT_LV_CH0_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH0_V  0x1
#define RMT_IDLE_OUT_LV_CH0_S  18
/* RMT_REF_ALWAYS_ON_CH0:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH0  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH0_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH0_V  0x1
#define RMT_REF_ALWAYS_ON_CH0_S  17
/* RMT_REF_CNT_RST_CH0:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置通道0中的除法器。*/
#define RMT_REF_CNT_RST_CH0  (BIT(16))
#define RMT_REF_CNT_RST_CH0_M  (BIT(16))
#define RMT_REF_CNT_RST_CH0_V  0x1
#define RMT_REF_CNT_RST_CH0_S  16
/* RMT_RX滤波器阈值CH0:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel0忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH0  0x000000FF
#define RMT_RX_FILTER_THRES_CH0_M  ((RMT_RX_FILTER_THRES_CH0_V)<<(RMT_RX_FILTER_THRES_CH0_S))
#define RMT_RX_FILTER_THRES_CH0_V  0xFF
#define RMT_RX_FILTER_THRES_CH0_S  8
/* RMT_RX滤波器_ EN _ CH0：R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道0的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH0  (BIT(7))
#define RMT_RX_FILTER_EN_CH0_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH0_V  0x1
#define RMT_RX_FILTER_EN_CH0_S  7
/* RMT_TX_CONTI_MODE_CH0:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续一次又一次从信道0中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH0  (BIT(6))
#define RMT_TX_CONTI_MODE_CH0_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH0_V  0x1
#define RMT_TX_CONTI_MODE_CH0_S  6
/* RMT_MEM_OWNER_CH0:R/W；位位置：[5]；默认值：1’b1；*/
/*描述：这是channel0的ram使用权的标记。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH0  (BIT(5))
#define RMT_MEM_OWNER_CH0_M  (BIT(5))
#define RMT_MEM_OWNER_CH0_V  0x1
#define RMT_MEM_OWNER_CH0_S  5
/* RMT_APB_MEM_RST_CH0:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道0的W/R ram地址*/
#define RMT_APB_MEM_RST_CH0  (BIT(4))
#define RMT_APB_MEM_RST_CH0_M  (BIT(4))
#define RMT_APB_MEM_RST_CH0_V  0x1
#define RMT_APB_MEM_RST_CH0_S  4
/* RMT_MEM_RD_RST_CH0:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道0的读ram地址。*/
#define RMT_MEM_RD_RST_CH0  (BIT(3))
#define RMT_MEM_RD_RST_CH0_M  (BIT(3))
#define RMT_MEM_RD_RST_CH0_V  0x1
#define RMT_MEM_RD_RST_CH0_S  3
/* RMT_MEM_WR_RST_CH0:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道0的写ram地址。*/
#define RMT_MEM_WR_RST_CH0  (BIT(2))
#define RMT_MEM_WR_RST_CH0_M  (BIT(2))
#define RMT_MEM_WR_RST_CH0_V  0x1
#define RMT_MEM_WR_RST_CH0_S  2
/* RMT_RX_EN_CH0:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道0的接收数据。*/
#define RMT_RX_EN_CH0  (BIT(1))
#define RMT_RX_EN_CH0_M  (BIT(1))
#define RMT_RX_EN_CH0_V  0x1
#define RMT_RX_EN_CH0_S  1
/* RMT_TX_START_CH0:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送通道0的数据。*/
#define RMT_TX_START_CH0  (BIT(0))
#define RMT_TX_START_CH0_M  (BIT(0))
#define RMT_TX_START_CH0_V  0x1
#define RMT_TX_START_CH0_S  0

#define RMT_CH1CONF0_REG          (DR_REG_RMT_BASE + 0x0028)
/* RMT_CARRIER_OUT_LV_CH1:R/W；位位置：[29]；默认值：1’b1；*/
/*描述：此位用于配置信道1.1’b1：在低输出电平上传输1’b0：在高输出电平上发送的载波调制方式。*/
#define RMT_CARRIER_OUT_LV_CH1  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH1_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH1_V  0x1
#define RMT_CARRIER_OUT_LV_CH1_S  29
/* RMT_CARRIER_EN_CH1:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道1的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH1  (BIT(28))
#define RMT_CARRIER_EN_CH1_M  (BIT(28))
#define RMT_CARRIER_EN_CH1_V  0x1
#define RMT_CARRIER_EN_CH1_S  28
/* RMT_MEM_SIZE_CH1:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道1的内存块数量。*/
#define RMT_MEM_SIZE_CH1  0x0000000F
#define RMT_MEM_SIZE_CH1_M  ((RMT_MEM_SIZE_CH1_V)<<(RMT_MEM_SIZE_CH1_S))
#define RMT_MEM_SIZE_CH1_V  0xF
#define RMT_MEM_SIZE_CH1_S  24
/* RMT_IDLE_THRES_CH1:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:此寄存器用于配置分配给通道1的内存块数量。*/
#define RMT_IDLE_THRES_CH1  0x0000FFFF
#define RMT_IDLE_THRES_CH1_M  ((RMT_IDLE_THRES_CH1_V)<<(RMT_IDLE_THRES_CH1_S))
#define RMT_IDLE_THRES_CH1_V  0xFFFF
#define RMT_IDLE_THRES_CH1_S  8
/* RMT_DIV_CNT_CH1:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道1中的分频器因数。*/
#define RMT_DIV_CNT_CH1  0x000000FF
#define RMT_DIV_CNT_CH1_M  ((RMT_DIV_CNT_CH1_V)<<(RMT_DIV_CNT_CH1_S))
#define RMT_DIV_CNT_CH1_V  0xFF
#define RMT_DIV_CNT_CH1_S  0

#define RMT_CH1CONF1_REG          (DR_REG_RMT_BASE + 0x002c)
/* RMT_IDLE_OUT_EN_CH1:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于IDLE状态的通道1的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH1  (BIT(19))
#define RMT_IDLE_OUT_EN_CH1_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH1_V  0x1
#define RMT_IDLE_OUT_EN_CH1_S  19
/* RMT_IDLE_OUT_LV_CH1:R/W；位位置：[18]；默认值：1’b0；*/
/*description:此位配置信道1在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH1  (BIT(18))
#define RMT_IDLE_OUT_LV_CH1_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH1_V  0x1
#define RMT_IDLE_OUT_LV_CH1_S  18
/* RMT_REF_ALWAYS_ON_CH1:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH1  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH1_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH1_V  0x1
#define RMT_REF_ALWAYS_ON_CH1_S  17
/* RMT_REF_CNT_RST_CH1:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置通道1中的除法器。*/
#define RMT_REF_CNT_RST_CH1  (BIT(16))
#define RMT_REF_CNT_RST_CH1_M  (BIT(16))
#define RMT_REF_CNT_RST_CH1_V  0x1
#define RMT_REF_CNT_RST_CH1_S  16
/* RMT_RX滤波器阈值CH1:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel1忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH1  0x000000FF
#define RMT_RX_FILTER_THRES_CH1_M  ((RMT_RX_FILTER_THRES_CH1_V)<<(RMT_RX_FILTER_THRES_CH1_S))
#define RMT_RX_FILTER_THRES_CH1_V  0xFF
#define RMT_RX_FILTER_THRES_CH1_S  8
/* RMT_RX滤波器_ EN _ CH1:R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道1的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH1  (BIT(7))
#define RMT_RX_FILTER_EN_CH1_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH1_V  0x1
#define RMT_RX_FILTER_EN_CH1_S  7
/* RMT_TX_CONTI_MODE_CH1:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续一次又一次地从信道1中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH1  (BIT(6))
#define RMT_TX_CONTI_MODE_CH1_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH1_V  0x1
#define RMT_TX_CONTI_MODE_CH1_S  6
/* RMT_MEM_OWNER_CH1:R/W；位位置：[5]；默认值：1’b1；*/
/*描述：这是channel1的ram使用权的标记。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH1  (BIT(5))
#define RMT_MEM_OWNER_CH1_M  (BIT(5))
#define RMT_MEM_OWNER_CH1_V  0x1
#define RMT_MEM_OWNER_CH1_S  5
/* RMT_APB_MEM_RST_CH1:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道1的W/R ram地址*/
#define RMT_APB_MEM_RST_CH1  (BIT(4))
#define RMT_APB_MEM_RST_CH1_M  (BIT(4))
#define RMT_APB_MEM_RST_CH1_V  0x1
#define RMT_APB_MEM_RST_CH1_S  4
/* RMT_MEM_RD_RST_CH1:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道1的读ram地址。*/
#define RMT_MEM_RD_RST_CH1  (BIT(3))
#define RMT_MEM_RD_RST_CH1_M  (BIT(3))
#define RMT_MEM_RD_RST_CH1_V  0x1
#define RMT_MEM_RD_RST_CH1_S  3
/* RMT_MEM_WR_RST_CH1:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道1的写ram地址。*/
#define RMT_MEM_WR_RST_CH1  (BIT(2))
#define RMT_MEM_WR_RST_CH1_M  (BIT(2))
#define RMT_MEM_WR_RST_CH1_V  0x1
#define RMT_MEM_WR_RST_CH1_S  2
/* RMT_RX_EN_CH1:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道1的接收数据。*/
#define RMT_RX_EN_CH1  (BIT(1))
#define RMT_RX_EN_CH1_M  (BIT(1))
#define RMT_RX_EN_CH1_V  0x1
#define RMT_RX_EN_CH1_S  1
/* RMT_TX_START_CH1:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送信道1的数据。*/
#define RMT_TX_START_CH1  (BIT(0))
#define RMT_TX_START_CH1_M  (BIT(0))
#define RMT_TX_START_CH1_V  0x1
#define RMT_TX_START_CH1_S  0

#define RMT_CH2CONF0_REG          (DR_REG_RMT_BASE + 0x0030)
/* RMT_CARRIER_OUT_LV_CH2:R/W；位位置：[29]；默认值：1’b1；*/
/*description:此位用于配置信道2.1’b1：添加到低电平1’b0：添加到高电平的载波位置。*/
#define RMT_CARRIER_OUT_LV_CH2  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH2_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH2_V  0x1
#define RMT_CARRIER_OUT_LV_CH2_S  29
/* RMT_CARRIER_EN_CH2:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道2的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH2  (BIT(28))
#define RMT_CARRIER_EN_CH2_M  (BIT(28))
#define RMT_CARRIER_EN_CH2_V  0x1
#define RMT_CARRIER_EN_CH2_S  28
/* RMT_MEM_SIZE_CH2:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道2的内存块数量。*/
#define RMT_MEM_SIZE_CH2  0x0000000F
#define RMT_MEM_SIZE_CH2_M  ((RMT_MEM_SIZE_CH2_V)<<(RMT_MEM_SIZE_CH2_S))
#define RMT_MEM_SIZE_CH2_V  0xF
#define RMT_MEM_SIZE_CH2_S  24
/* RMT_IDLE_THRES_CH2:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果计数器的值大于reg_idle_thres_ch2，则完成接收过程。*/
#define RMT_IDLE_THRES_CH2  0x0000FFFF
#define RMT_IDLE_THRES_CH2_M  ((RMT_IDLE_THRES_CH2_V)<<(RMT_IDLE_THRES_CH2_S))
#define RMT_IDLE_THRES_CH2_V  0xFFFF
#define RMT_IDLE_THRES_CH2_S  8
/* RMT_DIV_CNT_CH2:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道2中的分频器因数。*/
#define RMT_DIV_CNT_CH2  0x000000FF
#define RMT_DIV_CNT_CH2_M  ((RMT_DIV_CNT_CH2_V)<<(RMT_DIV_CNT_CH2_S))
#define RMT_DIV_CNT_CH2_V  0xFF
#define RMT_DIV_CNT_CH2_S  0

#define RMT_CH2CONF1_REG          (DR_REG_RMT_BASE + 0x0034)
/* RMT_IDLE_OUT_EN_CH2:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于IDLE状态的通道2的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH2  (BIT(19))
#define RMT_IDLE_OUT_EN_CH2_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH2_V  0x1
#define RMT_IDLE_OUT_EN_CH2_S  19
/* RMT_IDLE_OUT_LV_CH2:R/W；位位置：[18]；默认值：1’b0；*/
/*description:该位配置信道2在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH2  (BIT(18))
#define RMT_IDLE_OUT_LV_CH2_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH2_V  0x1
#define RMT_IDLE_OUT_LV_CH2_S  18
/* RMT_REF_ALWAYS_ON_CH2:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH2  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH2_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH2_V  0x1
#define RMT_REF_ALWAYS_ON_CH2_S  17
/* RMT_REF_CNT_RST_CH2:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置信道2中的除法器。*/
#define RMT_REF_CNT_RST_CH2  (BIT(16))
#define RMT_REF_CNT_RST_CH2_M  (BIT(16))
#define RMT_REF_CNT_RST_CH2_V  0x1
#define RMT_REF_CNT_RST_CH2_S  16
/* RMT_RX滤波器阈值CH2:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel2忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH2  0x000000FF
#define RMT_RX_FILTER_THRES_CH2_M  ((RMT_RX_FILTER_THRES_CH2_V)<<(RMT_RX_FILTER_THRES_CH2_S))
#define RMT_RX_FILTER_THRES_CH2_V  0xFF
#define RMT_RX_FILTER_THRES_CH2_S  8
/* RMT_RX滤波器_ EN _ CH2:R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道2的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH2  (BIT(7))
#define RMT_RX_FILTER_EN_CH2_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH2_V  0x1
#define RMT_RX_FILTER_EN_CH2_S  7
/* RMT_TX_CONTI_MODE_CH2:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续从信道2中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH2  (BIT(6))
#define RMT_TX_CONTI_MODE_CH2_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH2_V  0x1
#define RMT_TX_CONTI_MODE_CH2_S  6
/* RMT_MEM_OWNER_CH2:R/W；位位置：[5]；默认值：1’b1；*/
/*描述：这是信道2的ram使用权的标记。1’b1：接收机使用ram 0：发射机使用ram*/
#define RMT_MEM_OWNER_CH2  (BIT(5))
#define RMT_MEM_OWNER_CH2_M  (BIT(5))
#define RMT_MEM_OWNER_CH2_V  0x1
#define RMT_MEM_OWNER_CH2_S  5
/* RMT_APB_MEM_RST_CH2:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道2的W/R ram地址*/
#define RMT_APB_MEM_RST_CH2  (BIT(4))
#define RMT_APB_MEM_RST_CH2_M  (BIT(4))
#define RMT_APB_MEM_RST_CH2_V  0x1
#define RMT_APB_MEM_RST_CH2_S  4
/* RMT_MEM_RD_RST_CH2:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道2的读ram地址。*/
#define RMT_MEM_RD_RST_CH2  (BIT(3))
#define RMT_MEM_RD_RST_CH2_M  (BIT(3))
#define RMT_MEM_RD_RST_CH2_V  0x1
#define RMT_MEM_RD_RST_CH2_S  3
/* RMT_MEM_WR_RST_CH2:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道2的写ram地址。*/
#define RMT_MEM_WR_RST_CH2  (BIT(2))
#define RMT_MEM_WR_RST_CH2_M  (BIT(2))
#define RMT_MEM_WR_RST_CH2_V  0x1
#define RMT_MEM_WR_RST_CH2_S  2
/* RMT_RX_EN_CH2:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道2的接收数据。*/
#define RMT_RX_EN_CH2  (BIT(1))
#define RMT_RX_EN_CH2_M  (BIT(1))
#define RMT_RX_EN_CH2_V  0x1
#define RMT_RX_EN_CH2_S  1
/* RMT_TX_START_CH2:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送信道2的数据。*/
#define RMT_TX_START_CH2  (BIT(0))
#define RMT_TX_START_CH2_M  (BIT(0))
#define RMT_TX_START_CH2_V  0x1
#define RMT_TX_START_CH2_S  0

#define RMT_CH3CONF0_REG          (DR_REG_RMT_BASE + 0x0038)
/* RMT_CARRIER_OUT_LV_CH3:R/W；位位置：[29]；默认值：1’b1；*/
/*description:此位用于配置信道3.1’b1：添加到低电平1’b0：添加到高电平的载波位置。*/
#define RMT_CARRIER_OUT_LV_CH3  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH3_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH3_V  0x1
#define RMT_CARRIER_OUT_LV_CH3_S  29
/* RMT_CARRIER_EN_CH3:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道3的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH3  (BIT(28))
#define RMT_CARRIER_EN_CH3_M  (BIT(28))
#define RMT_CARRIER_EN_CH3_V  0x1
#define RMT_CARRIER_EN_CH3_S  28
/* RMT_MEM_SIZE_CH3:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道3的内存块数量。*/
#define RMT_MEM_SIZE_CH3  0x0000000F
#define RMT_MEM_SIZE_CH3_M  ((RMT_MEM_SIZE_CH3_V)<<(RMT_MEM_SIZE_CH3_S))
#define RMT_MEM_SIZE_CH3_V  0xF
#define RMT_MEM_SIZE_CH3_S  24
/* RMT_IDLE_THRES_CH3:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果计数器的值大于reg_idle_thres_ch3，则完成接收过程。*/
#define RMT_IDLE_THRES_CH3  0x0000FFFF
#define RMT_IDLE_THRES_CH3_M  ((RMT_IDLE_THRES_CH3_V)<<(RMT_IDLE_THRES_CH3_S))
#define RMT_IDLE_THRES_CH3_V  0xFFFF
#define RMT_IDLE_THRES_CH3_S  8
/* RMT_DIV_CNT_CH3:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道3中的分频器因数。*/
#define RMT_DIV_CNT_CH3  0x000000FF
#define RMT_DIV_CNT_CH3_M  ((RMT_DIV_CNT_CH3_V)<<(RMT_DIV_CNT_CH3_S))
#define RMT_DIV_CNT_CH3_V  0xFF
#define RMT_DIV_CNT_CH3_S  0

#define RMT_CH3CONF1_REG          (DR_REG_RMT_BASE + 0x003c)
/* RMT_IDLE_OUT_EN_CH3:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于IDLE状态的通道3的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH3  (BIT(19))
#define RMT_IDLE_OUT_EN_CH3_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH3_V  0x1
#define RMT_IDLE_OUT_EN_CH3_S  19
/* RMT_IDLE_OUT_LV_CH3:R/W；位位置：[18]；默认值：1’b0；*/
/*description:该位配置信道3在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH3  (BIT(18))
#define RMT_IDLE_OUT_LV_CH3_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH3_V  0x1
#define RMT_IDLE_OUT_LV_CH3_S  18
/* RMT_REF_ALWAYS_ON_CH3:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH3  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH3_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH3_V  0x1
#define RMT_REF_ALWAYS_ON_CH3_S  17
/* RMT_REF_CNT_RST_CH3:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置通道3中的除法器。*/
#define RMT_REF_CNT_RST_CH3  (BIT(16))
#define RMT_REF_CNT_RST_CH3_M  (BIT(16))
#define RMT_REF_CNT_RST_CH3_V  0x1
#define RMT_REF_CNT_RST_CH3_S  16
/* RMT_RX滤波器阈值CH3:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel3忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH3  0x000000FF
#define RMT_RX_FILTER_THRES_CH3_M  ((RMT_RX_FILTER_THRES_CH3_V)<<(RMT_RX_FILTER_THRES_CH3_S))
#define RMT_RX_FILTER_THRES_CH3_V  0xFF
#define RMT_RX_FILTER_THRES_CH3_S  8
/* RMT_RX滤波器_内部通道3：R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道3的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH3  (BIT(7))
#define RMT_RX_FILTER_EN_CH3_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH3_V  0x1
#define RMT_RX_FILTER_EN_CH3_S  7
/* RMT_TX_CONTI_MODE_CH3:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续从信道3中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH3  (BIT(6))
#define RMT_TX_CONTI_MODE_CH3_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH3_V  0x1
#define RMT_TX_CONTI_MODE_CH3_S  6
/* RMT_MEM_OWNER_CH3:R/W；位位置：[5]；默认值：1’b1；*/
/*description:这是channel3内存使用权的标志。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH3  (BIT(5))
#define RMT_MEM_OWNER_CH3_M  (BIT(5))
#define RMT_MEM_OWNER_CH3_V  0x1
#define RMT_MEM_OWNER_CH3_S  5
/* RMT_APB_MEM_RST_CH3:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道3的W/R ram地址*/
#define RMT_APB_MEM_RST_CH3  (BIT(4))
#define RMT_APB_MEM_RST_CH3_M  (BIT(4))
#define RMT_APB_MEM_RST_CH3_V  0x1
#define RMT_APB_MEM_RST_CH3_S  4
/* RMT_MEM_RD_RST_CH3:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道3的读ram地址。*/
#define RMT_MEM_RD_RST_CH3  (BIT(3))
#define RMT_MEM_RD_RST_CH3_M  (BIT(3))
#define RMT_MEM_RD_RST_CH3_V  0x1
#define RMT_MEM_RD_RST_CH3_S  3
/* RMT_MEM_WR_RST_CH3:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道3的写ram地址。*/
#define RMT_MEM_WR_RST_CH3  (BIT(2))
#define RMT_MEM_WR_RST_CH3_M  (BIT(2))
#define RMT_MEM_WR_RST_CH3_V  0x1
#define RMT_MEM_WR_RST_CH3_S  2
/* RMT_RX_EN_CH3:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道3的接收数据。*/
#define RMT_RX_EN_CH3  (BIT(1))
#define RMT_RX_EN_CH3_M  (BIT(1))
#define RMT_RX_EN_CH3_V  0x1
#define RMT_RX_EN_CH3_S  1
/* RMT_TX_START_CH3:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送信道3的数据。*/
#define RMT_TX_START_CH3  (BIT(0))
#define RMT_TX_START_CH3_M  (BIT(0))
#define RMT_TX_START_CH3_V  0x1
#define RMT_TX_START_CH3_S  0

#define RMT_CH4CONF0_REG          (DR_REG_RMT_BASE + 0x0040)
/* RMT_CARRIER_OUT_LV_CH4:R/W；位位置：[29]；默认值：1’b1；*/
/*描述：此位用于配置信道4.1’b1：添加到低电平1’b0：添加到高电平的载波位置。*/
#define RMT_CARRIER_OUT_LV_CH4  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH4_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH4_V  0x1
#define RMT_CARRIER_OUT_LV_CH4_S  29
/* RMT_CARRIER_EN_CH4:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道4的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH4  (BIT(28))
#define RMT_CARRIER_EN_CH4_M  (BIT(28))
#define RMT_CARRIER_EN_CH4_V  0x1
#define RMT_CARRIER_EN_CH4_S  28
/* RMT_MEM_SIZE_CH4:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道4的内存块数量。*/
#define RMT_MEM_SIZE_CH4  0x0000000F
#define RMT_MEM_SIZE_CH4_M  ((RMT_MEM_SIZE_CH4_V)<<(RMT_MEM_SIZE_CH4_S))
#define RMT_MEM_SIZE_CH4_V  0xF
#define RMT_MEM_SIZE_CH4_S  24
/* RMT_IDLE_threshold_CH4:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果计数器的值大于reg_idle_thres_ch4，则完成接收过程。*/
#define RMT_IDLE_THRES_CH4  0x0000FFFF
#define RMT_IDLE_THRES_CH4_M  ((RMT_IDLE_THRES_CH4_V)<<(RMT_IDLE_THRES_CH4_S))
#define RMT_IDLE_THRES_CH4_V  0xFFFF
#define RMT_IDLE_THRES_CH4_S  8
/* RMT_DIV_CNT_CH4:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道4中的分频器因数。*/
#define RMT_DIV_CNT_CH4  0x000000FF
#define RMT_DIV_CNT_CH4_M  ((RMT_DIV_CNT_CH4_V)<<(RMT_DIV_CNT_CH4_S))
#define RMT_DIV_CNT_CH4_V  0xFF
#define RMT_DIV_CNT_CH4_S  0

#define RMT_CH4CONF1_REG          (DR_REG_RMT_BASE + 0x0044)
/* RMT_IDLE_OUT_EN_CH4:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于IDLE状态的通道4的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH4  (BIT(19))
#define RMT_IDLE_OUT_EN_CH4_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH4_V  0x1
#define RMT_IDLE_OUT_EN_CH4_S  19
/* RMT_IDLE_OUT_LV_CH4:R/W；位位置：[18]；默认值：1’b0；*/
/*description:该位配置信道4在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH4  (BIT(18))
#define RMT_IDLE_OUT_LV_CH4_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH4_V  0x1
#define RMT_IDLE_OUT_LV_CH4_S  18
/* RMT_REF_ALWAYS_ON_CH4：R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH4  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH4_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH4_V  0x1
#define RMT_REF_ALWAYS_ON_CH4_S  17
/* RMT_REF_CNT_RST_CH4:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置信道4中的除法器。*/
#define RMT_REF_CNT_RST_CH4  (BIT(16))
#define RMT_REF_CNT_RST_CH4_M  (BIT(16))
#define RMT_REF_CNT_RST_CH4_V  0x1
#define RMT_REF_CNT_RST_CH4_S  16
/* RMT_RX滤波器阈值CH4：R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel4忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH4  0x000000FF
#define RMT_RX_FILTER_THRES_CH4_M  ((RMT_RX_FILTER_THRES_CH4_V)<<(RMT_RX_FILTER_THRES_CH4_S))
#define RMT_RX_FILTER_THRES_CH4_V  0xFF
#define RMT_RX_FILTER_THRES_CH4_S  8
/* RMT_RX滤波器_内部通道4：R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道4的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH4  (BIT(7))
#define RMT_RX_FILTER_EN_CH4_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH4_V  0x1
#define RMT_RX_FILTER_EN_CH4_S  7
/* RMT_TX_CONTI_MODE_CH4:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续从信道4中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH4  (BIT(6))
#define RMT_TX_CONTI_MODE_CH4_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH4_V  0x1
#define RMT_TX_CONTI_MODE_CH4_S  6
/* RMT_MEM_OWNER_CH4:R/W；位位置：[5]；默认值：1’b1；*/
/*description:这是channel4内存使用权的标志。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH4  (BIT(5))
#define RMT_MEM_OWNER_CH4_M  (BIT(5))
#define RMT_MEM_OWNER_CH4_V  0x1
#define RMT_MEM_OWNER_CH4_S  5
/* RMT_APB_MEM_RST_CH4:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道4的W/R ram地址*/
#define RMT_APB_MEM_RST_CH4  (BIT(4))
#define RMT_APB_MEM_RST_CH4_M  (BIT(4))
#define RMT_APB_MEM_RST_CH4_V  0x1
#define RMT_APB_MEM_RST_CH4_S  4
/* RMT_MEM_RD_RST_CH4:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道4的读ram地址。*/
#define RMT_MEM_RD_RST_CH4  (BIT(3))
#define RMT_MEM_RD_RST_CH4_M  (BIT(3))
#define RMT_MEM_RD_RST_CH4_V  0x1
#define RMT_MEM_RD_RST_CH4_S  3
/* RMT_MEM_WR_RST_CH4:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道4的写ram地址。*/
#define RMT_MEM_WR_RST_CH4  (BIT(2))
#define RMT_MEM_WR_RST_CH4_M  (BIT(2))
#define RMT_MEM_WR_RST_CH4_V  0x1
#define RMT_MEM_WR_RST_CH4_S  2
/* RMT_RX_EN_CH4:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道4的接收数据。*/
#define RMT_RX_EN_CH4  (BIT(1))
#define RMT_RX_EN_CH4_M  (BIT(1))
#define RMT_RX_EN_CH4_V  0x1
#define RMT_RX_EN_CH4_S  1
/* RMT_TX_START_CH4:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送信道4的数据。*/
#define RMT_TX_START_CH4  (BIT(0))
#define RMT_TX_START_CH4_M  (BIT(0))
#define RMT_TX_START_CH4_V  0x1
#define RMT_TX_START_CH4_S  0

#define RMT_CH5CONF0_REG          (DR_REG_RMT_BASE + 0x0048)
/* RMT_CARRIER_OUT_LV_CH5:R/W；位位置：[29]；默认值：1’b1；*/
/*description:此位用于配置信道5.1’b1：添加到低电平1’b0：添加到高电平的载波位置。*/
#define RMT_CARRIER_OUT_LV_CH5  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH5_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH5_V  0x1
#define RMT_CARRIER_OUT_LV_CH5_S  29
/* RMT_CARRIER_EN_CH5:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道5的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH5  (BIT(28))
#define RMT_CARRIER_EN_CH5_M  (BIT(28))
#define RMT_CARRIER_EN_CH5_V  0x1
#define RMT_CARRIER_EN_CH5_S  28
/* RMT_MEM_SIZE_CH5:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道5的内存块数量。*/
#define RMT_MEM_SIZE_CH5  0x0000000F
#define RMT_MEM_SIZE_CH5_M  ((RMT_MEM_SIZE_CH5_V)<<(RMT_MEM_SIZE_CH5_S))
#define RMT_MEM_SIZE_CH5_V  0xF
#define RMT_MEM_SIZE_CH5_S  24
/* RMT_IDLE_threshold_CH5:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果计数器的值大于reg_idle_thres_ch5，则完成接收过程。*/
#define RMT_IDLE_THRES_CH5  0x0000FFFF
#define RMT_IDLE_THRES_CH5_M  ((RMT_IDLE_THRES_CH5_V)<<(RMT_IDLE_THRES_CH5_S))
#define RMT_IDLE_THRES_CH5_V  0xFFFF
#define RMT_IDLE_THRES_CH5_S  8
/* RMT_DIV_CNT_CH5:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道5中的分频器因数。*/
#define RMT_DIV_CNT_CH5  0x000000FF
#define RMT_DIV_CNT_CH5_M  ((RMT_DIV_CNT_CH5_V)<<(RMT_DIV_CNT_CH5_S))
#define RMT_DIV_CNT_CH5_V  0xFF
#define RMT_DIV_CNT_CH5_S  0

#define RMT_CH5CONF1_REG          (DR_REG_RMT_BASE + 0x004c)
/* RMT_IDLE_OUT_EN_CH5:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于IDLE状态的通道5的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH5  (BIT(19))
#define RMT_IDLE_OUT_EN_CH5_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH5_V  0x1
#define RMT_IDLE_OUT_EN_CH5_S  19
/* RMT_IDLE_OUT_LV_CH5:R/W；位位置：[18]；默认值：1’b0；*/
/*description:该位配置信道5在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH5  (BIT(18))
#define RMT_IDLE_OUT_LV_CH5_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH5_V  0x1
#define RMT_IDLE_OUT_LV_CH5_S  18
/* RMT_REF_ALWAYS_ON_CH5:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH5  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH5_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH5_V  0x1
#define RMT_REF_ALWAYS_ON_CH5_S  17
/* RMT_REF_CNT_RST_CH5:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置通道5中的除法器。*/
#define RMT_REF_CNT_RST_CH5  (BIT(16))
#define RMT_REF_CNT_RST_CH5_M  (BIT(16))
#define RMT_REF_CNT_RST_CH5_V  0x1
#define RMT_REF_CNT_RST_CH5_S  16
/* RMT_RX滤波器阈值CH5:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel5忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH5  0x000000FF
#define RMT_RX_FILTER_THRES_CH5_M  ((RMT_RX_FILTER_THRES_CH5_V)<<(RMT_RX_FILTER_THRES_CH5_S))
#define RMT_RX_FILTER_THRES_CH5_V  0xFF
#define RMT_RX_FILTER_THRES_CH5_S  8
/* RMT_RX滤波器_内部通道5：R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道5的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH5  (BIT(7))
#define RMT_RX_FILTER_EN_CH5_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH5_V  0x1
#define RMT_RX_FILTER_EN_CH5_S  7
/* RMT_TX_CONTI_MODE_CH5:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续从信道5中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH5  (BIT(6))
#define RMT_TX_CONTI_MODE_CH5_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH5_V  0x1
#define RMT_TX_CONTI_MODE_CH5_S  6
/* RMT_MEM_OWNER_CH5:R/W；位位置：[5]；默认值：1’b1；*/
/*description:这是channel5内存使用权的标志。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH5  (BIT(5))
#define RMT_MEM_OWNER_CH5_M  (BIT(5))
#define RMT_MEM_OWNER_CH5_V  0x1
#define RMT_MEM_OWNER_CH5_S  5
/* RMT_APB_MEM_RST_CH5:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道5的W/R ram地址*/
#define RMT_APB_MEM_RST_CH5  (BIT(4))
#define RMT_APB_MEM_RST_CH5_M  (BIT(4))
#define RMT_APB_MEM_RST_CH5_V  0x1
#define RMT_APB_MEM_RST_CH5_S  4
/* RMT_MEM_RD_RST_CH5:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道5的读ram地址。*/
#define RMT_MEM_RD_RST_CH5  (BIT(3))
#define RMT_MEM_RD_RST_CH5_M  (BIT(3))
#define RMT_MEM_RD_RST_CH5_V  0x1
#define RMT_MEM_RD_RST_CH5_S  3
/* RMT_MEM_WR_RST_CH5:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道5的写ram地址。*/
#define RMT_MEM_WR_RST_CH5  (BIT(2))
#define RMT_MEM_WR_RST_CH5_M  (BIT(2))
#define RMT_MEM_WR_RST_CH5_V  0x1
#define RMT_MEM_WR_RST_CH5_S  2
/* RMT_RX_EN_CH5:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道5的接收数据。*/
#define RMT_RX_EN_CH5  (BIT(1))
#define RMT_RX_EN_CH5_M  (BIT(1))
#define RMT_RX_EN_CH5_V  0x1
#define RMT_RX_EN_CH5_S  1
/* RMT_TX_START_CH5:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送信道5的数据。*/
#define RMT_TX_START_CH5  (BIT(0))
#define RMT_TX_START_CH5_M  (BIT(0))
#define RMT_TX_START_CH5_V  0x1
#define RMT_TX_START_CH5_S  0

#define RMT_CH6CONF0_REG          (DR_REG_RMT_BASE + 0x0050)
/* RMT_CARRIER_OUT_LV_CH6:R/W；位位置：[29]；默认值：1’b1；*/
/*描述：此位用于配置信道6.1’b1：添加到低电平1’b0：添加到高电平的载波位置。*/
#define RMT_CARRIER_OUT_LV_CH6  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH6_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH6_V  0x1
#define RMT_CARRIER_OUT_LV_CH6_S  29
/* RMT_CARRIER_EN_CH6:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道6的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH6  (BIT(28))
#define RMT_CARRIER_EN_CH6_M  (BIT(28))
#define RMT_CARRIER_EN_CH6_V  0x1
#define RMT_CARRIER_EN_CH6_S  28
/* RMT_MEM_SIZE_CH6:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道6的内存块数量。*/
#define RMT_MEM_SIZE_CH6  0x0000000F
#define RMT_MEM_SIZE_CH6_M  ((RMT_MEM_SIZE_CH6_V)<<(RMT_MEM_SIZE_CH6_S))
#define RMT_MEM_SIZE_CH6_V  0xF
#define RMT_MEM_SIZE_CH6_S  24
/* RMT_IDLE_threshold_CH6:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果计数器的值大于reg_idle_thres_ch6，则完成接收过程。*/
#define RMT_IDLE_THRES_CH6  0x0000FFFF
#define RMT_IDLE_THRES_CH6_M  ((RMT_IDLE_THRES_CH6_V)<<(RMT_IDLE_THRES_CH6_S))
#define RMT_IDLE_THRES_CH6_V  0xFFFF
#define RMT_IDLE_THRES_CH6_S  8
/* RMT_DIV_CNT_CH6:R/W；位位置：[7:0]；默认值：8'h2；*/
/*描述：此寄存器用于配置信道6中的分频器因数。*/
#define RMT_DIV_CNT_CH6  0x000000FF
#define RMT_DIV_CNT_CH6_M  ((RMT_DIV_CNT_CH6_V)<<(RMT_DIV_CNT_CH6_S))
#define RMT_DIV_CNT_CH6_V  0xFF
#define RMT_DIV_CNT_CH6_S  0

#define RMT_CH6CONF1_REG          (DR_REG_RMT_BASE + 0x0054)
/* RMT_IDLE_OUT_EN_CH6:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于空闲状态的通道6的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH6  (BIT(19))
#define RMT_IDLE_OUT_EN_CH6_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH6_V  0x1
#define RMT_IDLE_OUT_EN_CH6_S  19
/* RMT_IDLE_OUT_LV_CH6:R/W；位位置：[18]；默认值：1’b0；*/
/*描述：该位配置信道6在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH6  (BIT(18))
#define RMT_IDLE_OUT_LV_CH6_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH6_V  0x1
#define RMT_IDLE_OUT_LV_CH6_S  18
/* RMT_REF_ALWAYS_ON_CH6:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH6  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH6_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH6_V  0x1
#define RMT_REF_ALWAYS_ON_CH6_S  17
/* RMT_REF_CNT_RST_CH6:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置通道6中的除法器。*/
#define RMT_REF_CNT_RST_CH6  (BIT(16))
#define RMT_REF_CNT_RST_CH6_M  (BIT(16))
#define RMT_REF_CNT_RST_CH6_V  0x1
#define RMT_REF_CNT_RST_CH6_S  16
/* RMT_RX滤波器阈值CH6:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，channel6忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH6  0x000000FF
#define RMT_RX_FILTER_THRES_CH6_M  ((RMT_RX_FILTER_THRES_CH6_V)<<(RMT_RX_FILTER_THRES_CH6_S))
#define RMT_RX_FILTER_THRES_CH6_V  0xFF
#define RMT_RX_FILTER_THRES_CH6_S  8
/* RMT_RX滤波器_内部通道6：R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道6的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH6  (BIT(7))
#define RMT_RX_FILTER_EN_CH6_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH6_V  0x1
#define RMT_RX_FILTER_EN_CH6_S  7
/* RMT_TX_CONTI_MODE_CH6:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续从信道6中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH6  (BIT(6))
#define RMT_TX_CONTI_MODE_CH6_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH6_V  0x1
#define RMT_TX_CONTI_MODE_CH6_S  6
/* RMT_MEM_OWNER_CH6:R/W；位位置：[5]；默认值：1’b1；*/
/*description:这是channel6内存使用权的标志。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH6  (BIT(5))
#define RMT_MEM_OWNER_CH6_M  (BIT(5))
#define RMT_MEM_OWNER_CH6_V  0x1
#define RMT_MEM_OWNER_CH6_S  5
/* RMT_APB_MEM_RST_CH6:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道6的W/R ram地址*/
#define RMT_APB_MEM_RST_CH6  (BIT(4))
#define RMT_APB_MEM_RST_CH6_M  (BIT(4))
#define RMT_APB_MEM_RST_CH6_V  0x1
#define RMT_APB_MEM_RST_CH6_S  4
/* RMT_MEM_RD_RST_CH6:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置信道6的读ram地址。*/
#define RMT_MEM_RD_RST_CH6  (BIT(3))
#define RMT_MEM_RD_RST_CH6_M  (BIT(3))
#define RMT_MEM_RD_RST_CH6_V  0x1
#define RMT_MEM_RD_RST_CH6_S  3
/* RMT_MEM_WR_RST_CH6:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道6的写ram地址。*/
#define RMT_MEM_WR_RST_CH6  (BIT(2))
#define RMT_MEM_WR_RST_CH6_M  (BIT(2))
#define RMT_MEM_WR_RST_CH6_V  0x1
#define RMT_MEM_WR_RST_CH6_S  2
/* RMT_RX_EN_CH6:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为启用信道6的接收数据。*/
#define RMT_RX_EN_CH6  (BIT(1))
#define RMT_RX_EN_CH6_M  (BIT(1))
#define RMT_RX_EN_CH6_V  0x1
#define RMT_RX_EN_CH6_S  1
/* RMT_TX_START_CH6:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送信道6的数据。*/
#define RMT_TX_START_CH6  (BIT(0))
#define RMT_TX_START_CH6_M  (BIT(0))
#define RMT_TX_START_CH6_V  0x1
#define RMT_TX_START_CH6_S  0

#define RMT_CH7CONF0_REG          (DR_REG_RMT_BASE + 0x0058)
/* RMT_CARRIER_OUT_LV_CH7:R/W；位位置：[29]；默认值：1’b1；*/
/*描述：此位用于配置信道7.1’b1：添加到低电平1’b0：添加到高电平的载波位置。*/
#define RMT_CARRIER_OUT_LV_CH7  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH7_M  (BIT(29))
#define RMT_CARRIER_OUT_LV_CH7_V  0x1
#define RMT_CARRIER_OUT_LV_CH7_S  29
/* RMT_CARRIER_EN_CH7:R/W；位位置：[28]；默认值：1’b1；*/
/*description:这是信道7的载波调制启用控制位。*/
#define RMT_CARRIER_EN_CH7  (BIT(28))
#define RMT_CARRIER_EN_CH7_M  (BIT(28))
#define RMT_CARRIER_EN_CH7_V  0x1
#define RMT_CARRIER_EN_CH7_S  28
/* RMT_MEM_SIZE_CH7:R/W；位位置：[27:24]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给通道7的内存块数量。*/
#define RMT_MEM_SIZE_CH7  0x0000000F
#define RMT_MEM_SIZE_CH7_M  ((RMT_MEM_SIZE_CH7_V)<<(RMT_MEM_SIZE_CH7_S))
#define RMT_MEM_SIZE_CH7_V  0xF
#define RMT_MEM_SIZE_CH7_S  24
/* RMT_IDLE_THRES_CH7:R/W；比特位置：[23:8]；默认值：16'h1000；*/
/*description:在接收模式下，如果计数器的值大于reg_idle_thres_ch7，则完成接收过程。*/
#define RMT_IDLE_THRES_CH7  0x0000FFFF
#define RMT_IDLE_THRES_CH7_M  ((RMT_IDLE_THRES_CH7_V)<<(RMT_IDLE_THRES_CH7_S))
#define RMT_IDLE_THRES_CH7_V  0xFFFF
#define RMT_IDLE_THRES_CH7_S  8
/* RMT_DIV_CNT_CH7:R/W；位位置：[7:0]；默认值：8'h2；*/
/*description:此寄存器用于配置信道7中的分频器因数。*/
#define RMT_DIV_CNT_CH7  0x000000FF
#define RMT_DIV_CNT_CH7_M  ((RMT_DIV_CNT_CH7_V)<<(RMT_DIV_CNT_CH7_S))
#define RMT_DIV_CNT_CH7_V  0xFF
#define RMT_DIV_CNT_CH7_S  0

#define RMT_CH7CONF1_REG          (DR_REG_RMT_BASE + 0x005c)
/* RMT_IDLE_OUT_EN_CH7:R/W；位位置：[19]；默认值：1’b0；*/
/*description:这是处于空闲状态的通道6的输出启用控制位。*/
#define RMT_IDLE_OUT_EN_CH7  (BIT(19))
#define RMT_IDLE_OUT_EN_CH7_M  (BIT(19))
#define RMT_IDLE_OUT_EN_CH7_V  0x1
#define RMT_IDLE_OUT_EN_CH7_S  19
/* RMT_IDLE_OUT_LV_CH7:R/W；位位置：[18]；默认值：1’b0；*/
/*description:该位配置信道7在空闲状态下的输出信号电平。*/
#define RMT_IDLE_OUT_LV_CH7  (BIT(18))
#define RMT_IDLE_OUT_LV_CH7_M  (BIT(18))
#define RMT_IDLE_OUT_LV_CH7_V  0x1
#define RMT_IDLE_OUT_LV_CH7_S  18
/* RMT_REF_ALWAYS_ON_CH7:R/W；位位置：[17]；默认值：1’b0；*/
/*description:此位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
#define RMT_REF_ALWAYS_ON_CH7  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH7_M  (BIT(17))
#define RMT_REF_ALWAYS_ON_CH7_V  0x1
#define RMT_REF_ALWAYS_ON_CH7_S  17
/* RMT_REF_CNT_RST_CH7:R/W；位位置：[16]；默认值：1’b0；*/
/*description:此位用于重置通道7中的除法器。*/
#define RMT_REF_CNT_RST_CH7  (BIT(16))
#define RMT_REF_CNT_RST_CH7_M  (BIT(16))
#define RMT_REF_CNT_RST_CH7_V  0x1
#define RMT_REF_CNT_RST_CH7_S  16
/* RMT_RX滤波器阈值CH7:R/W；比特位置：[15:8]；默认值：8'hf；*/
/*描述：在接收模式下，当脉冲宽度小于此值时，通道7忽略输入脉冲。*/
#define RMT_RX_FILTER_THRES_CH7  0x000000FF
#define RMT_RX_FILTER_THRES_CH7_M  ((RMT_RX_FILTER_THRES_CH7_V)<<(RMT_RX_FILTER_THRES_CH7_S))
#define RMT_RX_FILTER_THRES_CH7_V  0xFF
#define RMT_RX_FILTER_THRES_CH7_S  8
/* RMT_RX滤波器_内部通道7：R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是信道7的接收滤波器启用位。*/
#define RMT_RX_FILTER_EN_CH7  (BIT(7))
#define RMT_RX_FILTER_EN_CH7_M  (BIT(7))
#define RMT_RX_FILTER_EN_CH7_V  0x1
#define RMT_RX_FILTER_EN_CH7_S  7
/* RMT_TX_CONTI_MODE_CH7:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以继续从通道7中的第一个数据发送到最后一个数据。*/
#define RMT_TX_CONTI_MODE_CH7  (BIT(6))
#define RMT_TX_CONTI_MODE_CH7_M  (BIT(6))
#define RMT_TX_CONTI_MODE_CH7_V  0x1
#define RMT_TX_CONTI_MODE_CH7_S  6
/* RMT_MEM_OWNER_CH7:R/W；位位置：[5]；默认值：1’b1；*/
/*description:这是channel7内存使用权的标志。1’b1：接收器使用ram 0：发射器使用ram*/
#define RMT_MEM_OWNER_CH7  (BIT(5))
#define RMT_MEM_OWNER_CH7_M  (BIT(5))
#define RMT_MEM_OWNER_CH7_V  0x1
#define RMT_MEM_OWNER_CH7_S  5
/* RMT_APB_MEM_RST_CH7:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以通过apb-fifo访问重置通道7的W/R ram地址*/
#define RMT_APB_MEM_RST_CH7  (BIT(4))
#define RMT_APB_MEM_RST_CH7_M  (BIT(4))
#define RMT_APB_MEM_RST_CH7_V  0x1
#define RMT_APB_MEM_RST_CH7_S  4
/* RMT_MEM_RD_RST_CH7:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以通过发射机访问重置通道7的读ram地址。*/
#define RMT_MEM_RD_RST_CH7  (BIT(3))
#define RMT_MEM_RD_RST_CH7_M  (BIT(3))
#define RMT_MEM_RD_RST_CH7_V  0x1
#define RMT_MEM_RD_RST_CH7_S  3
/* RMT_MEM_WR_RST_CH7:R/W；位位置：[2]；默认值：1'0；*/
/*description:设置此位以通过接收器访问重置通道7的写ram地址。*/
#define RMT_MEM_WR_RST_CH7  (BIT(2))
#define RMT_MEM_WR_RST_CH7_M  (BIT(2))
#define RMT_MEM_WR_RST_CH7_V  0x1
#define RMT_MEM_WR_RST_CH7_S  2
/* RMT_RX_EN_CH7:R/W；位位置：[1]；默认值：1'0；*/
/*description:将此位设置为信道7的enbale接收数据。*/
#define RMT_RX_EN_CH7  (BIT(1))
#define RMT_RX_EN_CH7_M  (BIT(1))
#define RMT_RX_EN_CH7_V  0x1
#define RMT_RX_EN_CH7_S  1
/* RMT_TX_START_CH7:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以开始发送通道7的数据。*/
#define RMT_TX_START_CH7  (BIT(0))
#define RMT_TX_START_CH7_M  (BIT(0))
#define RMT_TX_START_CH7_V  0x1
#define RMT_TX_START_CH7_S  0

#define RMT_CH0STATUS_REG          (DR_REG_RMT_BASE + 0x0060)
/* RMT_STATUS_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道0的状态*/
#define RMT_STATUS_CH0  0xFFFFFFFF
#define RMT_STATUS_CH0_M  ((RMT_STATUS_CH0_V)<<(RMT_STATUS_CH0_S))
#define RMT_STATUS_CH0_V  0xFFFFFFFF
#define RMT_STATUS_CH0_S  0
/* RMT_APB_MEM_RD_ERR_CH0:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道0的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH0 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH0_M  ((RMT_APB_MEM_RD_ERR_CH0_V)<<(RMT_APB_MEM_RD_ERR_CH0_S))
#define RMT_APB_MEM_RD_ERR_CH0_V  0x1
#define RMT_APB_MEM_RD_ERR_CH0_S  31
/* RMT_APB_MEM_WR_ERR_CH0:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道0的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH0 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH0_M  ((RMT_APB_MEM_WR_ERR_CH0_V)<<(RMT_APB_MEM_WR_ERR_CH0_S))
#define RMT_APB_MEM_WR_ERR_CH0_V  0x1
#define RMT_APB_MEM_WR_ERR_CH0_S  30
/* RMT_MEM_EMPTY_CH0:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel0的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH0 (BIT(29))
#define RMT_MEM_EMPTY_CH0_M  ((RMT_MEM_EMPTY_CH0_V)<<(RMT_MEM_EMPTY_CH0_S))
#define RMT_MEM_EMPTY_CH0_V  0x1
#define RMT_MEM_EMPTY_CH0_S  29
/* RMT_MEM_FULL_CH0:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel0的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH0 (BIT(28))
#define RMT_MEM_FULL_CH0_M  ((RMT_MEM_FULL_CH0_V)<<(RMT_MEM_FULL_CH0_S))
#define RMT_MEM_FULL_CH0_V  0x1
#define RMT_MEM_FULL_CH0_S  28
/* RMT_MEM_OWNER_ERR_CH0:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道0配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH0 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH0_M  ((RMT_MEM_OWNER_ERR_CH0_V)<<(RMT_MEM_OWNER_ERR_CH0_S))
#define RMT_MEM_OWNER_ERR_CH0_V  0x1
#define RMT_MEM_OWNER_ERR_CH0_S  27
/* RMT_STATE_CH0:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel0状态机状态寄存器。3'h0：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH0 0x07000000
#define RMT_STATE_CH0_M  ((RMT_STATE_CH0_V)<<(RMT_STATE_CH0_S))
#define RMT_STATE_CH0_V  0x7
#define RMT_STATE_CH0_S  24
/* RMT_MEM_RADDR_EX_CH0:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道0的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH0 0x003ff000
#define RMT_MEM_RADDR_EX_CH0_M  ((RMT_MEM_RADDR_EX_CH0_V)<<(RMT_MEM_RADDR_EX_CH0_S))
#define RMT_MEM_RADDR_EX_CH0_V  0x3ff
#define RMT_MEM_RADDR_EX_CH0_S  12
/* RMT_MEM_WADDR_EX_CH0:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道0的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH0 0x000003ff
#define RMT_MEM_WADDR_EX_CH0_M  ((RMT_MEM_WADDR_EX_CH0_V)<<(RMT_MEM_WADDR_EX_CH0_S))
#define RMT_MEM_WADDR_EX_CH0_V  0x3ff
#define RMT_MEM_WADDR_EX_CH0_S  0

#define RMT_CH1STATUS_REG          (DR_REG_RMT_BASE + 0x0064)
/* RMT_STATUS_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道1的状态*/
#define RMT_STATUS_CH1  0xFFFFFFFF
#define RMT_STATUS_CH1_M  ((RMT_STATUS_CH1_V)<<(RMT_STATUS_CH1_S))
#define RMT_STATUS_CH1_V  0xFFFFFFFF
#define RMT_STATUS_CH1_S  0
/* RMT_APB_MEM_RD_ERR_CH1:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道1的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH1 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH1_M  ((RMT_APB_MEM_RD_ERR_CH1_V)<<(RMT_APB_MEM_RD_ERR_CH1_S))
#define RMT_APB_MEM_RD_ERR_CH1_V  0x1
#define RMT_APB_MEM_RD_ERR_CH1_S  31
/* RMT_APB_MEM_WR_ERR_CH1:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道1的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH1 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH1_M  ((RMT_APB_MEM_WR_ERR_CH1_V)<<(RMT_APB_MEM_WR_ERR_CH1_S))
#define RMT_APB_MEM_WR_ERR_CH1_V  0x1
#define RMT_APB_MEM_WR_ERR_CH1_S  30
/* RMT_MEM_EMPTY_CH1:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel1的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH1 (BIT(29))
#define RMT_MEM_EMPTY_CH1_M  ((RMT_MEM_EMPTY_CH1_V)<<(RMT_MEM_EMPTY_CH1_S))
#define RMT_MEM_EMPTY_CH1_V  0x1
#define RMT_MEM_EMPTY_CH1_S  29
/* RMT_MEM_FULL_CH1:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel1的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH1 (BIT(28))
#define RMT_MEM_FULL_CH1_M  ((RMT_MEM_FULL_CH1_V)<<(RMT_MEM_FULL_CH1_S))
#define RMT_MEM_FULL_CH1_V  0x1
#define RMT_MEM_FULL_CH1_S  28
/* RMT_MEM_OWNER_ERR_CH1:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当channel1配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH1 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH1_M  ((RMT_MEM_OWNER_ERR_CH1_V)<<(RMT_MEM_OWNER_ERR_CH1_S))
#define RMT_MEM_OWNER_ERR_CH1_V  0x1
#define RMT_MEM_OWNER_ERR_CH1_S  27
/* RMT_STATE_CH1:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel1状态机状态寄存器。3'h0：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH1 0x07000000
#define RMT_STATE_CH1_M  ((RMT_STATE_CH1_V)<<(RMT_STATE_CH1_S))
#define RMT_STATE_CH1_V  0x7
#define RMT_STATE_CH1_S  24
/* RMT_MEM_RADDR_EX_CH1:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道1的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH1 0x003ff000
#define RMT_MEM_RADDR_EX_CH1_M  ((RMT_MEM_RADDR_EX_CH1_V)<<(RMT_MEM_RADDR_EX_CH1_S))
#define RMT_MEM_RADDR_EX_CH1_V  0x3ff
#define RMT_MEM_RADDR_EX_CH1_S  12
/* RMT_MEM_WADDR_EX_CH1:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道1的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH1 0x000003ff
#define RMT_MEM_WADDR_EX_CH1_M  ((RMT_MEM_WADDR_EX_CH1_V)<<(RMT_MEM_WADDR_EX_CH1_S))
#define RMT_MEM_WADDR_EX_CH1_V  0x3ff
#define RMT_MEM_WADDR_EX_CH1_S  0

#define RMT_CH2STATUS_REG          (DR_REG_RMT_BASE + 0x0068)
/* RMT_STATUS_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道2的状态*/
#define RMT_STATUS_CH2  0xFFFFFFFF
#define RMT_STATUS_CH2_M  ((RMT_STATUS_CH2_V)<<(RMT_STATUS_CH2_S))
#define RMT_STATUS_CH2_V  0xFFFFFFFF
#define RMT_STATUS_CH2_S  0
/* RMT_APB_MEM_RD_ERR_CH2:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道2的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH2 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH2_M  ((RMT_APB_MEM_RD_ERR_CH2_V)<<(RMT_APB_MEM_RD_ERR_CH2_S))
#define RMT_APB_MEM_RD_ERR_CH2_V  0x1
#define RMT_APB_MEM_RD_ERR_CH2_S  31
/* RMT_APB_MEM_WR_ERR_CH2:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道2的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH2 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH2_M  ((RMT_APB_MEM_WR_ERR_CH2_V)<<(RMT_APB_MEM_WR_ERR_CH2_S))
#define RMT_APB_MEM_WR_ERR_CH2_V  0x1
#define RMT_APB_MEM_WR_ERR_CH2_S  30
/* RMT_MEM_EMPTY_CH2:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel2的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH2 (BIT(29))
#define RMT_MEM_EMPTY_CH2_M  ((RMT_MEM_EMPTY_CH2_V)<<(RMT_MEM_EMPTY_CH2_S))
#define RMT_MEM_EMPTY_CH2_V  0x1
#define RMT_MEM_EMPTY_CH2_S  29
/* RMT_MEM_FULL_CH2:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel2的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH2 (BIT(28))
#define RMT_MEM_FULL_CH2_M  ((RMT_MEM_FULL_CH2_V)<<(RMT_MEM_FULL_CH2_S))
#define RMT_MEM_FULL_CH2_V  0x1
#define RMT_MEM_FULL_CH2_S  28
/* RMT_MEM_OWNER_ERR_CH2:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道2配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH2 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH2_M  ((RMT_MEM_OWNER_ERR_CH2_V)<<(RMT_MEM_OWNER_ERR_CH2_S))
#define RMT_MEM_OWNER_ERR_CH2_V  0x1
#define RMT_MEM_OWNER_ERR_CH2_S  27
/* RMT_STATE_CH2:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel2状态机状态寄存器。3'h0：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH2 0x07000000
#define RMT_STATE_CH2_M  ((RMT_STATE_CH2_V)<<(RMT_STATE_CH2_S))
#define RMT_STATE_CH2_V  0x7
#define RMT_STATE_CH2_S  24
/* RMT_MEM_RADDR_EX_CH2:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道2的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH2 0x003ff000
#define RMT_MEM_RADDR_EX_CH2_M  ((RMT_MEM_RADDR_EX_CH2_V)<<(RMT_MEM_RADDR_EX_CH2_S))
#define RMT_MEM_RADDR_EX_CH2_V  0x3ff
#define RMT_MEM_RADDR_EX_CH2_S  12
/* RMT_MEM_WADDR_EX_CH2:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道2的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH2 0x000003ff
#define RMT_MEM_WADDR_EX_CH2_M  ((RMT_MEM_WADDR_EX_CH2_V)<<(RMT_MEM_WADDR_EX_CH2_S))
#define RMT_MEM_WADDR_EX_CH2_V  0x3ff
#define RMT_MEM_WADDR_EX_CH2_S  0

#define RMT_CH3STATUS_REG          (DR_REG_RMT_BASE + 0x006c)
/* RMT_STATUS_CH3:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道3的状态*/
#define RMT_STATUS_CH3  0xFFFFFFFF
#define RMT_STATUS_CH3_M  ((RMT_STATUS_CH3_V)<<(RMT_STATUS_CH3_S))
#define RMT_STATUS_CH3_V  0xFFFFFFFF
#define RMT_STATUS_CH3_S  0
/* RMT_APB_MEM_RD_ERR_CH3:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道3的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH3 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH3_M  ((RMT_APB_MEM_RD_ERR_CH3_V)<<(RMT_APB_MEM_RD_ERR_CH3_S))
#define RMT_APB_MEM_RD_ERR_CH3_V  0x1
#define RMT_APB_MEM_RD_ERR_CH3_S  31
/* RMT_APB_MEM_WR_ERR_CH3:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道3的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH3 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH3_M  ((RMT_APB_MEM_WR_ERR_CH3_V)<<(RMT_APB_MEM_WR_ERR_CH3_S))
#define RMT_APB_MEM_WR_ERR_CH3_V  0x1
#define RMT_APB_MEM_WR_ERR_CH3_S  30
/* RMT_MEM_EMPTY_CH3:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel3的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH3 (BIT(29))
#define RMT_MEM_EMPTY_CH3_M  ((RMT_MEM_EMPTY_CH3_V)<<(RMT_MEM_EMPTY_CH3_S))
#define RMT_MEM_EMPTY_CH3_V  0x1
#define RMT_MEM_EMPTY_CH3_S  29
/* RMT_MEM_FULL_CH3:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel3的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH3 (BIT(28))
#define RMT_MEM_FULL_CH3_M  ((RMT_MEM_FULL_CH3_V)<<(RMT_MEM_FULL_CH3_S))
#define RMT_MEM_FULL_CH3_V  0x1
#define RMT_MEM_FULL_CH3_S  28
/* RMT_MEM_OWNER_ERR_CH3:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道3配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH3 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH3_M  ((RMT_MEM_OWNER_ERR_CH3_V)<<(RMT_MEM_OWNER_ERR_CH3_S))
#define RMT_MEM_OWNER_ERR_CH3_V  0x1
#define RMT_MEM_OWNER_ERR_CH3_S  27
/* RMT_STATE_CH3:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:通道3状态机状态寄存器。3'00：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH3 0x07000000
#define RMT_STATE_CH3_M  ((RMT_STATE_CH3_V)<<(RMT_STATE_CH3_S))
#define RMT_STATE_CH3_V  0x7
#define RMT_STATE_CH3_S  24
/* RMT_MEM_RADDR_EX_CH3:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道3的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH3 0x003ff000
#define RMT_MEM_RADDR_EX_CH3_M  ((RMT_MEM_RADDR_EX_CH3_V)<<(RMT_MEM_RADDR_EX_CH3_S))
#define RMT_MEM_RADDR_EX_CH3_V  0x3ff
#define RMT_MEM_RADDR_EX_CH3_S  12
/* RMT_MEM_WADDR_EX_CH3:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道3的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH3 0x000003ff
#define RMT_MEM_WADDR_EX_CH3_M  ((RMT_MEM_WADDR_EX_CH3_V)<<(RMT_MEM_WADDR_EX_CH3_S))
#define RMT_MEM_WADDR_EX_CH3_V  0x3ff
#define RMT_MEM_WADDR_EX_CH3_S  0

#define RMT_CH4STATUS_REG          (DR_REG_RMT_BASE + 0x0070)
/* RMT_STATUS_CH4:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道4的状态*/
#define RMT_STATUS_CH4  0xFFFFFFFF
#define RMT_STATUS_CH4_M  ((RMT_STATUS_CH4_V)<<(RMT_STATUS_CH4_S))
#define RMT_STATUS_CH4_V  0xFFFFFFFF
#define RMT_STATUS_CH4_S  0
/* RMT_APB_MEM_RD_ERR_CH4:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道4的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH4 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH4_M  ((RMT_APB_MEM_RD_ERR_CH4_V)<<(RMT_APB_MEM_RD_ERR_CH4_S))
#define RMT_APB_MEM_RD_ERR_CH4_V  0x1
#define RMT_APB_MEM_RD_ERR_CH4_S  31
/* RMT_APB_MEM_WR_ERR_CH4:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道4的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH4 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH4_M  ((RMT_APB_MEM_WR_ERR_CH4_V)<<(RMT_APB_MEM_WR_ERR_CH4_S))
#define RMT_APB_MEM_WR_ERR_CH4_V  0x1
#define RMT_APB_MEM_WR_ERR_CH4_S  30
/* RMT_MEM_EMPTY_CH4:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel4的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH4 (BIT(29))
#define RMT_MEM_EMPTY_CH4_M  ((RMT_MEM_EMPTY_CH4_V)<<(RMT_MEM_EMPTY_CH4_S))
#define RMT_MEM_EMPTY_CH4_V  0x1
#define RMT_MEM_EMPTY_CH4_S  29
/* RMT_MEM_FULL_CH4:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel4的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH4 (BIT(28))
#define RMT_MEM_FULL_CH4_M  ((RMT_MEM_FULL_CH4_V)<<(RMT_MEM_FULL_CH4_S))
#define RMT_MEM_FULL_CH4_V  0x1
#define RMT_MEM_FULL_CH4_S  28
/* RMT_MEM_OWNER_ERR_CH4:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道4配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH4 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH4_M  ((RMT_MEM_OWNER_ERR_CH4_V)<<(RMT_MEM_OWNER_ERR_CH4_S))
#define RMT_MEM_OWNER_ERR_CH4_V  0x1
#define RMT_MEM_OWNER_ERR_CH4_S  27
/* RMT_STATE_CH4:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel4状态机状态寄存器。3'00：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH4 0x07000000
#define RMT_STATE_CH4_M  ((RMT_STATE_CH4_V)<<(RMT_STATE_CH4_S))
#define RMT_STATE_CH4_V  0x7
#define RMT_STATE_CH4_S  24
/* RMT_MEM_RADDR_EX_CH4:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道4的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH4 0x003ff000
#define RMT_MEM_RADDR_EX_CH4_M  ((RMT_MEM_RADDR_EX_CH4_V)<<(RMT_MEM_RADDR_EX_CH4_S))
#define RMT_MEM_RADDR_EX_CH4_V  0x3ff
#define RMT_MEM_RADDR_EX_CH4_S  12
/* RMT_MEM_WADDR_EX_CH4:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道4的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH4 0x000003ff
#define RMT_MEM_WADDR_EX_CH4_M  ((RMT_MEM_WADDR_EX_CH4_V)<<(RMT_MEM_WADDR_EX_CH4_S))
#define RMT_MEM_WADDR_EX_CH4_V  0x3ff
#define RMT_MEM_WADDR_EX_CH4_S  0

#define RMT_CH5STATUS_REG          (DR_REG_RMT_BASE + 0x0074)
/* RMT_STATUS_CH5:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道5的状态*/
#define RMT_STATUS_CH5  0xFFFFFFFF
#define RMT_STATUS_CH5_M  ((RMT_STATUS_CH5_V)<<(RMT_STATUS_CH5_S))
#define RMT_STATUS_CH5_V  0xFFFFFFFF
#define RMT_STATUS_CH5_S  0
/* RMT_APB_MEM_RD_ERR_CH5:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道5的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH5 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH5_M  ((RMT_APB_MEM_RD_ERR_CH5_V)<<(RMT_APB_MEM_RD_ERR_CH5_S))
#define RMT_APB_MEM_RD_ERR_CH5_V  0x1
#define RMT_APB_MEM_RD_ERR_CH5_S  31
/* RMT_APB_MEM_WR_ERR_CH5:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道5的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH5 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH5_M  ((RMT_APB_MEM_WR_ERR_CH5_V)<<(RMT_APB_MEM_WR_ERR_CH5_S))
#define RMT_APB_MEM_WR_ERR_CH5_V  0x1
#define RMT_APB_MEM_WR_ERR_CH5_S  30
/* RMT_MEM_EMPTY_CH5:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel5的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH5 (BIT(29))
#define RMT_MEM_EMPTY_CH5_M  ((RMT_MEM_EMPTY_CH5_V)<<(RMT_MEM_EMPTY_CH5_S))
#define RMT_MEM_EMPTY_CH5_V  0x1
#define RMT_MEM_EMPTY_CH5_S  29
/* RMT_MEM_FULL_CH5:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel5的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH5 (BIT(28))
#define RMT_MEM_FULL_CH5_M  ((RMT_MEM_FULL_CH5_V)<<(RMT_MEM_FULL_CH5_S))
#define RMT_MEM_FULL_CH5_V  0x1
#define RMT_MEM_FULL_CH5_S  28
/* RMT_MEM_OWNER_ERR_CH5:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道5配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH5 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH5_M  ((RMT_MEM_OWNER_ERR_CH5_V)<<(RMT_MEM_OWNER_ERR_CH5_S))
#define RMT_MEM_OWNER_ERR_CH5_V  0x1
#define RMT_MEM_OWNER_ERR_CH5_S  27
/* RMT_STATE_CH5:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel5状态机状态寄存器。3'00：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH5 0x07000000
#define RMT_STATE_CH5_M  ((RMT_STATE_CH5_V)<<(RMT_STATE_CH5_S))
#define RMT_STATE_CH5_V  0x7
#define RMT_STATE_CH5_S  24
/* RMT_MEM_RADDR_EX_CH5:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道5的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH5 0x003ff000
#define RMT_MEM_RADDR_EX_CH5_M  ((RMT_MEM_RADDR_EX_CH5_V)<<(RMT_MEM_RADDR_EX_CH5_S))
#define RMT_MEM_RADDR_EX_CH5_V  0x3ff
#define RMT_MEM_RADDR_EX_CH5_S  12
/* RMT_MEM_WADDR_EX_CH5:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道5的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH5 0x000003ff
#define RMT_MEM_WADDR_EX_CH5_M  ((RMT_MEM_WADDR_EX_CH5_V)<<(RMT_MEM_WADDR_EX_CH5_S))
#define RMT_MEM_WADDR_EX_CH5_V  0x3ff
#define RMT_MEM_WADDR_EX_CH5_S  0

#define RMT_CH6STATUS_REG          (DR_REG_RMT_BASE + 0x0078)
/* RMT_STATUS_CH6:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道6的状态*/
#define RMT_STATUS_CH6  0xFFFFFFFF
#define RMT_STATUS_CH6_M  ((RMT_STATUS_CH6_V)<<(RMT_STATUS_CH6_S))
#define RMT_STATUS_CH6_V  0xFFFFFFFF
#define RMT_STATUS_CH6_S  0
/* RMT_APB_MEM_RD_ERR_CH6:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道6的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH6 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH6_M  ((RMT_APB_MEM_RD_ERR_CH6_V)<<(RMT_APB_MEM_RD_ERR_CH6_S))
#define RMT_APB_MEM_RD_ERR_CH6_V  0x1
#define RMT_APB_MEM_RD_ERR_CH6_S  31
/* RMT_APB_MEM_WR_ERR_CH6:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道6的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH6 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH6_M  ((RMT_APB_MEM_WR_ERR_CH6_V)<<(RMT_APB_MEM_WR_ERR_CH6_S))
#define RMT_APB_MEM_WR_ERR_CH6_V  0x1
#define RMT_APB_MEM_WR_ERR_CH6_S  30
/* RMT_MEM_EMPTY_CH6:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel6的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH6 (BIT(29))
#define RMT_MEM_EMPTY_CH6_M  ((RMT_MEM_EMPTY_CH6_V)<<(RMT_MEM_EMPTY_CH6_S))
#define RMT_MEM_EMPTY_CH6_V  0x1
#define RMT_MEM_EMPTY_CH6_S  29
/* RMT_MEM_FULL_CH6:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel6的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH6 (BIT(28))
#define RMT_MEM_FULL_CH6_M  ((RMT_MEM_FULL_CH6_V)<<(RMT_MEM_FULL_CH6_S))
#define RMT_MEM_FULL_CH6_V  0x1
#define RMT_MEM_FULL_CH6_S  28
/* RMT_MEM_OWNER_ERR_CH6:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道6配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH6 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH6_M  ((RMT_MEM_OWNER_ERR_CH6_V)<<(RMT_MEM_OWNER_ERR_CH6_S))
#define RMT_MEM_OWNER_ERR_CH6_V  0x1
#define RMT_MEM_OWNER_ERR_CH6_S  27
/* RMT_STATE_CH6:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel6状态机状态寄存器。3'00：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH6 0x07000000
#define RMT_STATE_CH6_M  ((RMT_STATE_CH6_V)<<(RMT_STATE_CH6_S))
#define RMT_STATE_CH6_V  0x7
#define RMT_STATE_CH6_S  24
/* RMT_MEM_RADDR_EX_CH6:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道6的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH6 0x003ff000
#define RMT_MEM_RADDR_EX_CH6_M  ((RMT_MEM_RADDR_EX_CH6_V)<<(RMT_MEM_RADDR_EX_CH6_S))
#define RMT_MEM_RADDR_EX_CH6_V  0x3ff
#define RMT_MEM_RADDR_EX_CH6_S  12
/* RMT_MEM_WADDR_EX_CH6:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道6的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH6 0x000003ff
#define RMT_MEM_WADDR_EX_CH6_M  ((RMT_MEM_WADDR_EX_CH6_V)<<(RMT_MEM_WADDR_EX_CH6_S))
#define RMT_MEM_WADDR_EX_CH6_V  0x3ff
#define RMT_MEM_WADDR_EX_CH6_S  0

#define RMT_CH7STATUS_REG          (DR_REG_RMT_BASE + 0x007c)
/* RMT_STATUS_CH7:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:通道7的状态*/
#define RMT_STATUS_CH7  0xFFFFFFFF
#define RMT_STATUS_CH7_M  ((RMT_STATUS_CH7_V)<<(RMT_STATUS_CH7_S))
#define RMT_STATUS_CH7_V  0xFFFFFFFF
#define RMT_STATUS_CH7_S  0
/* RMT_APB_MEM_RD_ERR_CH7:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当apb读取地址超出配置范围时，通道7的apb读取内存状态位变为高电平。*/
#define RMT_APB_MEM_RD_ERR_CH7 (BIT(31))
#define RMT_APB_MEM_RD_ERR_CH7_M  ((RMT_APB_MEM_RD_ERR_CH7_V)<<(RMT_APB_MEM_RD_ERR_CH7_S))
#define RMT_APB_MEM_RD_ERR_CH7_V  0x1
#define RMT_APB_MEM_RD_ERR_CH7_S  31
/* RMT_APB_MEM_WR_ERR_CH7:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当apb写入地址超出配置范围时，通道7的apb写入内存状态位变为高电平。*/
#define RMT_APB_MEM_WR_ERR_CH7 (BIT(30))
#define RMT_APB_MEM_WR_ERR_CH7_M  ((RMT_APB_MEM_WR_ERR_CH7_V)<<(RMT_APB_MEM_WR_ERR_CH7_S))
#define RMT_APB_MEM_WR_ERR_CH7_V  0x1
#define RMT_APB_MEM_WR_ERR_CH7_S  30
/* RMT_MEM_EMPTY_CH7:RO；位位置：[29]；默认值：1’b0；*/
/*description:channel7的内存空状态位。在非循环模式下，当mem_raddr_ex大于或等于配置范围时，此位变为高电平。*/
#define RMT_MEM_EMPTY_CH7 (BIT(29))
#define RMT_MEM_EMPTY_CH7_M  ((RMT_MEM_EMPTY_CH7_V)<<(RMT_MEM_EMPTY_CH7_S))
#define RMT_MEM_EMPTY_CH7_V  0x1
#define RMT_MEM_EMPTY_CH7_S  29
/* RMT_MEM_FULL_CH7:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mem_waddr_ex大于或等于配置范围时，channel7的内存满状态位变为高电平。*/
#define RMT_MEM_FULL_CH7 (BIT(28))
#define RMT_MEM_FULL_CH7_M  ((RMT_MEM_FULL_CH7_V)<<(RMT_MEM_FULL_CH7_S))
#define RMT_MEM_FULL_CH7_V  0x1
#define RMT_MEM_FULL_CH7_S  28
/* RMT_MEM_OWNER_ERR_CH7:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当通道7配置为接收模式时，如果rmt_mem_owner寄存器未设置为1，则此位将变为高电平。*/
#define RMT_MEM_OWNER_ERR_CH7 (BIT(27))
#define RMT_MEM_OWNER_ERR_CH7_M  ((RMT_MEM_OWNER_ERR_CH7_V)<<(RMT_MEM_OWNER_ERR_CH7_S))
#define RMT_MEM_OWNER_ERR_CH7_V  0x1
#define RMT_MEM_OWNER_ERR_CH7_S  27
/* RMT_STATE_CH7:RO；比特位置：[26:24]；默认值：3'h0；*/
/*description:channel7状态机状态寄存器。3'00：空闲，3'h1：发送，3'h2：读取内存，3'h3：接收，3'h4：等待。*/
#define RMT_STATE_CH7 0x07000000
#define RMT_STATE_CH7_M  ((RMT_STATE_CH7_V)<<(RMT_STATE_CH7_S))
#define RMT_STATE_CH7_V  0x7
#define RMT_STATE_CH7_S  24
/* RMT_MEM_RADDR_EX_CH7:RO；比特位置：[21:12]；默认值：10'0；*/
/*description:通道7的当前内存写入地址。*/
#define RMT_MEM_RADDR_EX_CH7 0x003ff000
#define RMT_MEM_RADDR_EX_CH7_M  ((RMT_MEM_RADDR_EX_CH7_V)<<(RMT_MEM_RADDR_EX_CH7_S))
#define RMT_MEM_RADDR_EX_CH7_V  0x3ff
#define RMT_MEM_RADDR_EX_CH7_S  12
/* RMT_MEM_WADDR_EX_CH7:RO；位位置：[9:0]；默认值：10'0；*/
/*description:通道7的当前内存读取地址。*/
#define RMT_MEM_WADDR_EX_CH7 0x000003ff
#define RMT_MEM_WADDR_EX_CH7_M  ((RMT_MEM_WADDR_EX_CH7_V)<<(RMT_MEM_WADDR_EX_CH7_S))
#define RMT_MEM_WADDR_EX_CH7_V  0x3ff
#define RMT_MEM_WADDR_EX_CH7_S  0

#define RMT_CH0ADDR_REG          (DR_REG_RMT_BASE + 0x0080)
/* RMT_APB_MEM_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:apb fifo访问通道0中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH0  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH0_M  ((RMT_APB_MEM_ADDR_CH0_V)<<(RMT_APB_MEM_ADDR_CH0_S))
#define RMT_APB_MEM_ADDR_CH0_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH0_S  0

#define RMT_CH1ADDR_REG          (DR_REG_RMT_BASE + 0x0084)
/* RMT_APB_MEM_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:apb fifo访问通道1中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH1  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH1_M  ((RMT_APB_MEM_ADDR_CH1_V)<<(RMT_APB_MEM_ADDR_CH1_S))
#define RMT_APB_MEM_ADDR_CH1_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH1_S  0

#define RMT_CH2ADDR_REG          (DR_REG_RMT_BASE + 0x0088)
/* RMT_APB_MEM_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*描述：apb fifo访问通道2中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH2  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH2_M  ((RMT_APB_MEM_ADDR_CH2_V)<<(RMT_APB_MEM_ADDR_CH2_S))
#define RMT_APB_MEM_ADDR_CH2_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH2_S  0

#define RMT_CH3ADDR_REG          (DR_REG_RMT_BASE + 0x008c)
/* RMT_APB_MEM_ADDR_CH3:RO；位位置：[31:0]；默认值：32'h0；*/
/*描述：apb fifo访问通道3中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH3  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH3_M  ((RMT_APB_MEM_ADDR_CH3_V)<<(RMT_APB_MEM_ADDR_CH3_S))
#define RMT_APB_MEM_ADDR_CH3_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH3_S  0

#define RMT_CH4ADDR_REG          (DR_REG_RMT_BASE + 0x0090)
/* RMT_APB_MEM_ADDR_CH4:RO；位位置：[31:0]；默认值：32'h0；*/
/*描述：apb fifo访问通道4中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH4  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH4_M  ((RMT_APB_MEM_ADDR_CH4_V)<<(RMT_APB_MEM_ADDR_CH4_S))
#define RMT_APB_MEM_ADDR_CH4_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH4_S  0

#define RMT_CH5ADDR_REG          (DR_REG_RMT_BASE + 0x0094)
/* RMT_APB_MEM_ADDR_CH5:RO；位位置：[31:0]；默认值：32'h0；*/
/*描述：apb fifo访问通道5中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH5  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH5_M  ((RMT_APB_MEM_ADDR_CH5_V)<<(RMT_APB_MEM_ADDR_CH5_S))
#define RMT_APB_MEM_ADDR_CH5_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH5_S  0

#define RMT_CH6ADDR_REG          (DR_REG_RMT_BASE + 0x0098)
/* RMT_APB_MEM_ADDR_CH6:RO；位位置：[31:0]；默认值：32'h0；*/
/*描述：apb fifo访问通道6中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH6  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH6_M  ((RMT_APB_MEM_ADDR_CH6_V)<<(RMT_APB_MEM_ADDR_CH6_S))
#define RMT_APB_MEM_ADDR_CH6_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH6_S  0

#define RMT_CH7ADDR_REG          (DR_REG_RMT_BASE + 0x009c)
/* RMT_APB_MEM_ADDR_CH7:RO；位位置：[31:0]；默认值：32'h0；*/
/*描述：apb fifo访问通道7中的ram相对地址*/
#define RMT_APB_MEM_ADDR_CH7  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH7_M  ((RMT_APB_MEM_ADDR_CH7_V)<<(RMT_APB_MEM_ADDR_CH7_S))
#define RMT_APB_MEM_ADDR_CH7_V  0xFFFFFFFF
#define RMT_APB_MEM_ADDR_CH7_S  0

#define RMT_INT_RAW_REG          (DR_REG_RMT_BASE + 0x00a0)
/* RMT_CH7_TX_THR_EVENT_INT_RAW:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当通道7中的发射机发送的数据超过reg_rmt_tx_lim_ch7时，通道7的中断原始位变为高电平。*/
#define RMT_CH7_TX_THR_EVENT_INT_RAW  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_RAW_M  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH7_TX_THR_EVENT_INT_RAW_S  31
/* RMT_CH6_TX_tr_EVENT_INT_RAW:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当信道6中的发射机发送的数据超过reg_rmt_tx_lim_ch6时，信道6的中断原始位变为高电平。*/
#define RMT_CH6_TX_THR_EVENT_INT_RAW  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_RAW_M  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH6_TX_THR_EVENT_INT_RAW_S  30
/* RMT_CH5_TX_THR_EVENT_INT_RAW:RO；位位置：[29]；默认值：1’b0；*/
/*描述：当信道5中的发射机发送的数据超过reg_rmt_tx_lim_ch5时，信道5的中断原始位变为高电平。*/
#define RMT_CH5_TX_THR_EVENT_INT_RAW  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_RAW_M  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH5_TX_THR_EVENT_INT_RAW_S  29
/* RMT_CH4_TX_THR_EVENT_INT_RAW:RO；位位置：[28]；默认值：1’b0；*/
/*描述：当信道4中的发射机发送的数据超过reg_rmt_tx_lim_ch4时，信道4的中断原始位变为高电平。*/
#define RMT_CH4_TX_THR_EVENT_INT_RAW  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_RAW_M  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH4_TX_THR_EVENT_INT_RAW_S  28
/* RMT_CH3_TX_THR_EVENT_INT_RAW:RO；位位置：[27]；默认值：1’b0；*/
/*描述：当信道3中的发射机发送的数据超过reg_rmt_tx_lim_ch3时，信道3的中断原始位变为高电平。*/
#define RMT_CH3_TX_THR_EVENT_INT_RAW  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_RAW_M  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH3_TX_THR_EVENT_INT_RAW_S  27
/* RMT_CH2_TX_THR_EVENT_INT_RAW:RO；位位置：[26]；默认值：1’b0；*/
/*描述：当信道2中的发射机发送的数据超过reg_rmt_tx_lim_ch2时，信道2的中断原始位变为高电平。*/
#define RMT_CH2_TX_THR_EVENT_INT_RAW  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_RAW_M  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH2_TX_THR_EVENT_INT_RAW_S  26
/* RMT_CH1_TX_THR_EVENT_INT_RAW:RO；位位置：[25]；默认值：1’b0；*/
/*描述：当信道1中的发射机发送的数据超过reg_rmt_tx_lim_ch1时，信道1的中断原始位变为高电平。*/
#define RMT_CH1_TX_THR_EVENT_INT_RAW  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_RAW_M  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH1_TX_THR_EVENT_INT_RAW_S  25
/* RMT_CH0_TX_THR_EVENT_INT_RAW:RO；位位置：[24]；默认值：1’b0；*/
/*描述：当信道0中的发射机发送的数据超过reg_rmt_tx_lim_ch0时，信道0的中断原始位变为高电平。*/
#define RMT_CH0_TX_THR_EVENT_INT_RAW  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_RAW_M  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_RAW_V  0x1
#define RMT_CH0_TX_THR_EVENT_INT_RAW_S  24
/* RMT_CH7_ERR_INT_RAW:RO；位位置：[23]；默认值：1’b0；*/
/*描述：当通道7检测到一些错误时，通道7的中断原始位变为高电平。*/
#define RMT_CH7_ERR_INT_RAW  (BIT(23))
#define RMT_CH7_ERR_INT_RAW_M  (BIT(23))
#define RMT_CH7_ERR_INT_RAW_V  0x1
#define RMT_CH7_ERR_INT_RAW_S  23
/* RMT_CH7_RX_END_INT_RAW:RO；位位置：[22]；默认值：1’b0；*/
/*描述：当接收过程完成时，通道7的中断原始位变为高电平。*/
#define RMT_CH7_RX_END_INT_RAW  (BIT(22))
#define RMT_CH7_RX_END_INT_RAW_M  (BIT(22))
#define RMT_CH7_RX_END_INT_RAW_V  0x1
#define RMT_CH7_RX_END_INT_RAW_S  22
/* RMT_CH7_TX_END_INT_RAW:RO；位位置：[21]；默认值：1’b0；*/
/*描述：当传输过程完成时，通道7的中断原始位变为高电平。*/
#define RMT_CH7_TX_END_INT_RAW  (BIT(21))
#define RMT_CH7_TX_END_INT_RAW_M  (BIT(21))
#define RMT_CH7_TX_END_INT_RAW_V  0x1
#define RMT_CH7_TX_END_INT_RAW_S  21
/* RMT_CH6_ERR_INT_RAW:RO；位位置：[20]；默认值：1’b0；*/
/*描述：当通道6检测到一些错误时，通道6的中断原始位变为高电平。*/
#define RMT_CH6_ERR_INT_RAW  (BIT(20))
#define RMT_CH6_ERR_INT_RAW_M  (BIT(20))
#define RMT_CH6_ERR_INT_RAW_V  0x1
#define RMT_CH6_ERR_INT_RAW_S  20
/* RMT_CH6_RX_END_INT_RAW:RO；位位置：[19]；默认值：1’b0；*/
/*描述：当接收过程完成时，通道6的中断原始位变为高电平。*/
#define RMT_CH6_RX_END_INT_RAW  (BIT(19))
#define RMT_CH6_RX_END_INT_RAW_M  (BIT(19))
#define RMT_CH6_RX_END_INT_RAW_V  0x1
#define RMT_CH6_RX_END_INT_RAW_S  19
/* RMT_CH6_TX_END_INT_RAW:RO；位位置：[18]；默认值：1’b0；*/
/*描述：当传输过程完成时，信道6的中断原始位变为高电平。*/
#define RMT_CH6_TX_END_INT_RAW  (BIT(18))
#define RMT_CH6_TX_END_INT_RAW_M  (BIT(18))
#define RMT_CH6_TX_END_INT_RAW_V  0x1
#define RMT_CH6_TX_END_INT_RAW_S  18
/* RMT_CH5_ERR_INT_RAW:RO；位位置：[17]；默认值：1’b0；*/
/*描述：当通道5检测到一些错误时，通道5的中断原始位变为高电平。*/
#define RMT_CH5_ERR_INT_RAW  (BIT(17))
#define RMT_CH5_ERR_INT_RAW_M  (BIT(17))
#define RMT_CH5_ERR_INT_RAW_V  0x1
#define RMT_CH5_ERR_INT_RAW_S  17
/* RMT_CH5_RX_END_INT_RAW:RO；位位置：[16]；默认值：1’b0；*/
/*描述：当接收过程完成时，通道5的中断原始位变为高电平。*/
#define RMT_CH5_RX_END_INT_RAW  (BIT(16))
#define RMT_CH5_RX_END_INT_RAW_M  (BIT(16))
#define RMT_CH5_RX_END_INT_RAW_V  0x1
#define RMT_CH5_RX_END_INT_RAW_S  16
/* RMT_CH5_TX_END_INT_RAW:RO；位位置：[15]；默认值：1’b0；*/
/*描述：当传输过程完成时，信道5的中断原始位变为高电平。*/
#define RMT_CH5_TX_END_INT_RAW  (BIT(15))
#define RMT_CH5_TX_END_INT_RAW_M  (BIT(15))
#define RMT_CH5_TX_END_INT_RAW_V  0x1
#define RMT_CH5_TX_END_INT_RAW_S  15
/* RMT_CH4_ERR_INT_RAW:RO；位位置：[14]；默认值：1’b0；*/
/*描述：当通道4检测到一些错误时，通道4的中断原始位变为高电平。*/
#define RMT_CH4_ERR_INT_RAW  (BIT(14))
#define RMT_CH4_ERR_INT_RAW_M  (BIT(14))
#define RMT_CH4_ERR_INT_RAW_V  0x1
#define RMT_CH4_ERR_INT_RAW_S  14
/* RMT_CH4_RX_END_INT_RAW:RO；位位置：[13]；默认值：1’b0；*/
/*描述：当接收过程完成时，信道4的中断原始位变为高电平。*/
#define RMT_CH4_RX_END_INT_RAW  (BIT(13))
#define RMT_CH4_RX_END_INT_RAW_M  (BIT(13))
#define RMT_CH4_RX_END_INT_RAW_V  0x1
#define RMT_CH4_RX_END_INT_RAW_S  13
/* RMT_CH4_TX_END_INT_RAW:RO；位位置：[12]；默认值：1’b0；*/
/*描述：当传输过程完成时，信道4的中断原始位变为高电平。*/
#define RMT_CH4_TX_END_INT_RAW  (BIT(12))
#define RMT_CH4_TX_END_INT_RAW_M  (BIT(12))
#define RMT_CH4_TX_END_INT_RAW_V  0x1
#define RMT_CH4_TX_END_INT_RAW_S  12
/* RMT_CH3_ERR_INT_RAW:RO；位位置：[11]；默认值：1’b0；*/
/*描述：当通道3检测到一些错误时，通道3的中断原始位变为高电平。*/
#define RMT_CH3_ERR_INT_RAW  (BIT(11))
#define RMT_CH3_ERR_INT_RAW_M  (BIT(11))
#define RMT_CH3_ERR_INT_RAW_V  0x1
#define RMT_CH3_ERR_INT_RAW_S  11
/* RMT_CH3_RX_END_INT_RAW:RO；位位置：[10]；默认值：1’b0；*/
/*描述：当接收过程完成时，通道3的中断原始位变为高电平。*/
#define RMT_CH3_RX_END_INT_RAW  (BIT(10))
#define RMT_CH3_RX_END_INT_RAW_M  (BIT(10))
#define RMT_CH3_RX_END_INT_RAW_V  0x1
#define RMT_CH3_RX_END_INT_RAW_S  10
/* RMT_CH3_TX_END_INT_RAW:RO；位位置：[9]；默认值：1’b0；*/
/*描述：当传输过程完成时，信道3的中断原始位变为高电平。*/
#define RMT_CH3_TX_END_INT_RAW  (BIT(9))
#define RMT_CH3_TX_END_INT_RAW_M  (BIT(9))
#define RMT_CH3_TX_END_INT_RAW_V  0x1
#define RMT_CH3_TX_END_INT_RAW_S  9
/* RMT_CH2_ERR_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*描述：当通道2检测到一些错误时，通道2的中断原始位变为高电平。*/
#define RMT_CH2_ERR_INT_RAW  (BIT(8))
#define RMT_CH2_ERR_INT_RAW_M  (BIT(8))
#define RMT_CH2_ERR_INT_RAW_V  0x1
#define RMT_CH2_ERR_INT_RAW_S  8
/* RMT_CH2_RX_END_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*描述：当接收过程完成时，信道2的中断原始位变为高电平。*/
#define RMT_CH2_RX_END_INT_RAW  (BIT(7))
#define RMT_CH2_RX_END_INT_RAW_M  (BIT(7))
#define RMT_CH2_RX_END_INT_RAW_V  0x1
#define RMT_CH2_RX_END_INT_RAW_S  7
/* RMT_CH2_TX_END_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*描述：当传输过程完成时，信道2的中断原始位变为高电平。*/
#define RMT_CH2_TX_END_INT_RAW  (BIT(6))
#define RMT_CH2_TX_END_INT_RAW_M  (BIT(6))
#define RMT_CH2_TX_END_INT_RAW_V  0x1
#define RMT_CH2_TX_END_INT_RAW_S  6
/* RMT_CH1_ERR_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*描述：当通道1检测到一些错误时，通道1的中断原始位变为高电平。*/
#define RMT_CH1_ERR_INT_RAW  (BIT(5))
#define RMT_CH1_ERR_INT_RAW_M  (BIT(5))
#define RMT_CH1_ERR_INT_RAW_V  0x1
#define RMT_CH1_ERR_INT_RAW_S  5
/* RMT_CH1_RX_END_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*描述：当接收过程完成时，通道1的中断原始位变为高电平。*/
#define RMT_CH1_RX_END_INT_RAW  (BIT(4))
#define RMT_CH1_RX_END_INT_RAW_M  (BIT(4))
#define RMT_CH1_RX_END_INT_RAW_V  0x1
#define RMT_CH1_RX_END_INT_RAW_S  4
/* RMT_CH1_TX_END_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*描述：当传输过程完成时，信道1的中断原始位变为高电平。*/
#define RMT_CH1_TX_END_INT_RAW  (BIT(3))
#define RMT_CH1_TX_END_INT_RAW_M  (BIT(3))
#define RMT_CH1_TX_END_INT_RAW_V  0x1
#define RMT_CH1_TX_END_INT_RAW_S  3
/* RMT_CH0_ERR_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*描述：当通道0检测到一些错误时，通道0的中断原始位变为高电平。*/
#define RMT_CH0_ERR_INT_RAW  (BIT(2))
#define RMT_CH0_ERR_INT_RAW_M  (BIT(2))
#define RMT_CH0_ERR_INT_RAW_V  0x1
#define RMT_CH0_ERR_INT_RAW_S  2
/* RMT_CH0_RX_END_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*描述：当接收过程完成时，通道0的中断原始位变为高电平。*/
#define RMT_CH0_RX_END_INT_RAW  (BIT(1))
#define RMT_CH0_RX_END_INT_RAW_M  (BIT(1))
#define RMT_CH0_RX_END_INT_RAW_V  0x1
#define RMT_CH0_RX_END_INT_RAW_S  1
/* RMT_CH0_TX_END_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*描述：当传输过程完成时，通道0的中断原始位变为高电平。*/
#define RMT_CH0_TX_END_INT_RAW  (BIT(0))
#define RMT_CH0_TX_END_INT_RAW_M  (BIT(0))
#define RMT_CH0_TX_END_INT_RAW_V  0x1
#define RMT_CH0_TX_END_INT_RAW_S  0

#define RMT_INT_ST_REG          (DR_REG_RMT_BASE + 0x00a4)
/* RMT_CH7_TX_THR_EVENT_INT_ST:RO；位位置：[31]；默认值：1’b0；*/
/*描述：当mt_ch7_tx_thr_event_int_ena设置为1时，通道7的rmt_ch7_tx_thr_event_int_raw的中断状态位。*/
#define RMT_CH7_TX_THR_EVENT_INT_ST  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_ST_M  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH7_TX_THR_EVENT_INT_ST_S  31
/* RMT_CH6_TX_tr_EVENT_INT_ST:RO；位位置：[30]；默认值：1’b0；*/
/*描述：当mt_ch6_tx_tr_event_int_ena设置为1时，通道6的rmt_ch6_tx_tR_event_int_raw的中断状态位。*/
#define RMT_CH6_TX_THR_EVENT_INT_ST  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_ST_M  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH6_TX_THR_EVENT_INT_ST_S  30
/* RMT_CH5_TX_THR_EVENT_INT_ST:RO；位位置：[29]；默认值：1’b0；*/
/*描述：当mt_ch5_tx_thr_event_int_ena设置为1时，通道5的rmt_ch5_tx_thr_event_int_raw的中断状态位。*/
#define RMT_CH5_TX_THR_EVENT_INT_ST  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_ST_M  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH5_TX_THR_EVENT_INT_ST_S  29
/* RMT_CH4_TX_THR_EVENT_INT_ST:RO；位位置：[28]；默认值：1’b0；*/
/*description:当mt_ch4_tx_thr_event_int_ena设置为1时，通道4的rmt_ch4_tx_thr事件_int_raw的中断状态位。*/
#define RMT_CH4_TX_THR_EVENT_INT_ST  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_ST_M  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH4_TX_THR_EVENT_INT_ST_S  28
/* RMT_CH3_TX_THR_EVENT_INT_ST:RO；位位置：[27]；默认值：1’b0；*/
/*description:当mt_ch3_tx_thr_event_int_ena设置为1时，通道3的rmt_ch3_tx_thr_event_int_raw的中断状态位。*/
#define RMT_CH3_TX_THR_EVENT_INT_ST  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_ST_M  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH3_TX_THR_EVENT_INT_ST_S  27
/* RMT_CH2_TX_THR_EVENT_INT_ST:RO；位位置：[26]；默认值：1’b0；*/
/*描述：当mt_ch2_tx_thr_event_int_ena设置为1时，通道2的rmt_ch2_tx_thr_event_int_raw的中断状态位。*/
#define RMT_CH2_TX_THR_EVENT_INT_ST  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_ST_M  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH2_TX_THR_EVENT_INT_ST_S  26
/* RMT_CH1_TX_THR_EVENT_INT_ST:RO；位位置：[25]；默认值：1’b0；*/
/*描述：当mt_ch1_tx_thr_event_int_ena设置为1时，通道1的rmt_ch1_tx_thr_event_int_raw的中断状态位。*/
#define RMT_CH1_TX_THR_EVENT_INT_ST  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_ST_M  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH1_TX_THR_EVENT_INT_ST_S  25
/* RMT_CH0_TX_THR_EVENT_INT_ST:RO；位位置：[24]；默认值：1’b0；*/
/*描述：当mt_ch0_tx_thr_event_int_ena设置为1时，通道0的rmt_ch0_tx_thr_event_int_raw的中断状态位。*/
#define RMT_CH0_TX_THR_EVENT_INT_ST  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_ST_M  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_ST_V  0x1
#define RMT_CH0_TX_THR_EVENT_INT_ST_S  24
/* RMT_CH7_ERR_INT_ST:RO；位位置：[23]；默认值：1’b0；*/
/*描述：当rmt_ch7_err_int_ena设置为1时，通道7的rmt_ch7_err_int_raw的中断状态位。*/
#define RMT_CH7_ERR_INT_ST  (BIT(23))
#define RMT_CH7_ERR_INT_ST_M  (BIT(23))
#define RMT_CH7_ERR_INT_ST_V  0x1
#define RMT_CH7_ERR_INT_ST_S  23
/* RMT_CH7_RX_END_INT_ST:RO；位位置：[22]；默认值：1’b0；*/
/*描述：当rmt_ch7_rx_end_int_ena设置为1时，通道7的rmt_ch7_rx_end_int_raw的中断状态位。*/
#define RMT_CH7_RX_END_INT_ST  (BIT(22))
#define RMT_CH7_RX_END_INT_ST_M  (BIT(22))
#define RMT_CH7_RX_END_INT_ST_V  0x1
#define RMT_CH7_RX_END_INT_ST_S  22
/* RMT_CH7_TX_END_INT_ST:RO；位位置：[21]；默认值：1’b0；*/
/*描述：当mt_ch7_tx_end_int_ena设置为1时，通道7的mt_ch7_tx_end_int.raw的中断状态位。*/
#define RMT_CH7_TX_END_INT_ST  (BIT(21))
#define RMT_CH7_TX_END_INT_ST_M  (BIT(21))
#define RMT_CH7_TX_END_INT_ST_V  0x1
#define RMT_CH7_TX_END_INT_ST_S  21
/* RMT_CH6_ERR_INT_ST:RO；位位置：[20]；默认值：1’b0；*/
/*描述：当rmt_ch6_err_int_ena设置为1时，通道6的rmt_ch6_err_int_raw的中断状态位。*/
#define RMT_CH6_ERR_INT_ST  (BIT(20))
#define RMT_CH6_ERR_INT_ST_M  (BIT(20))
#define RMT_CH6_ERR_INT_ST_V  0x1
#define RMT_CH6_ERR_INT_ST_S  20
/* RMT_CH6_RX_END_INT_ST:RO；位位置：[19]；默认值：1’b0；*/
/*描述：当rmt_ch6_rx_end_int_ena设置为1时，通道6的rmt_ch6_rx_end_int_raw的中断状态位。*/
#define RMT_CH6_RX_END_INT_ST  (BIT(19))
#define RMT_CH6_RX_END_INT_ST_M  (BIT(19))
#define RMT_CH6_RX_END_INT_ST_V  0x1
#define RMT_CH6_RX_END_INT_ST_S  19
/* RMT_CH6_TX_END_INT_ST:RO；位位置：[18]；默认值：1’b0；*/
/*描述：当mt_ch6_tx_end_int_ena设置为1时，通道6的mt_ch6_tx_end_int_raw的中断状态位。*/
#define RMT_CH6_TX_END_INT_ST  (BIT(18))
#define RMT_CH6_TX_END_INT_ST_M  (BIT(18))
#define RMT_CH6_TX_END_INT_ST_V  0x1
#define RMT_CH6_TX_END_INT_ST_S  18
/* RMT_CH5_ERR_INT_ST:RO；位位置：[17]；默认值：1’b0；*/
/*描述：当rmt_ch5_err_int_ena设置为1时，通道5的rmt_ch5-err_int_raw的中断状态位。*/
#define RMT_CH5_ERR_INT_ST  (BIT(17))
#define RMT_CH5_ERR_INT_ST_M  (BIT(17))
#define RMT_CH5_ERR_INT_ST_V  0x1
#define RMT_CH5_ERR_INT_ST_S  17
/* RMT_CH5_RX_END_INT_ST:RO；位位置：[16]；默认值：1’b0；*/
/*描述：当rmt_ch5_rx_end_int_ena设置为1时，通道5的rmt_ch5-rx_end.int_raw的中断状态位。*/
#define RMT_CH5_RX_END_INT_ST  (BIT(16))
#define RMT_CH5_RX_END_INT_ST_M  (BIT(16))
#define RMT_CH5_RX_END_INT_ST_V  0x1
#define RMT_CH5_RX_END_INT_ST_S  16
/* RMT_CH5_TX_END_INT_ST:RO；位位置：[15]；默认值：1’b0；*/
/*描述：当mt_ch5_tx_end_int_ena设置为1时，通道5的mt_ch5_tx_end_int.raw的中断状态位。*/
#define RMT_CH5_TX_END_INT_ST  (BIT(15))
#define RMT_CH5_TX_END_INT_ST_M  (BIT(15))
#define RMT_CH5_TX_END_INT_ST_V  0x1
#define RMT_CH5_TX_END_INT_ST_S  15
/* RMT_CH4_ERR_INT_ST:RO；位位置：[14]；默认值：1’b0；*/
/*描述：当rmt_ch4_err_int_ena设置为1时，通道4的rmt_ch4-err_int_raw的中断状态位。*/
#define RMT_CH4_ERR_INT_ST  (BIT(14))
#define RMT_CH4_ERR_INT_ST_M  (BIT(14))
#define RMT_CH4_ERR_INT_ST_V  0x1
#define RMT_CH4_ERR_INT_ST_S  14
/* RMT_CH4_RX_END_INT_ST:RO；位位置：[13]；默认值：1’b0；*/
/*描述：当rmt_ch4_rx_end_int_ena设置为1时，通道4的rmt_ch4-rx_end.int_raw的中断状态位。*/
#define RMT_CH4_RX_END_INT_ST  (BIT(13))
#define RMT_CH4_RX_END_INT_ST_M  (BIT(13))
#define RMT_CH4_RX_END_INT_ST_V  0x1
#define RMT_CH4_RX_END_INT_ST_S  13
/* RMT_CH4_TX_END_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*描述：当mt_ch4_tx_end_int_ena设置为1时，通道4的mt_ch_4_tx_end_int_raw的中断状态位。*/
#define RMT_CH4_TX_END_INT_ST  (BIT(12))
#define RMT_CH4_TX_END_INT_ST_M  (BIT(12))
#define RMT_CH4_TX_END_INT_ST_V  0x1
#define RMT_CH4_TX_END_INT_ST_S  12
/* RMT_CH3_ERR_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*描述：当rmt_ch3_err_int_ena设置为1时，通道3的rmt_ch3-err_int_raw的中断状态位。*/
#define RMT_CH3_ERR_INT_ST  (BIT(11))
#define RMT_CH3_ERR_INT_ST_M  (BIT(11))
#define RMT_CH3_ERR_INT_ST_V  0x1
#define RMT_CH3_ERR_INT_ST_S  11
/* RMT_CH3_RX_END_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*描述：当rmt_ch3_rx_end_int_ena设置为1时，通道3的rmt_ch_3_rx_end_int_raw的中断状态位。*/
#define RMT_CH3_RX_END_INT_ST  (BIT(10))
#define RMT_CH3_RX_END_INT_ST_M  (BIT(10))
#define RMT_CH3_RX_END_INT_ST_V  0x1
#define RMT_CH3_RX_END_INT_ST_S  10
/* RMT_CH3_TX_END_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*描述：当mt_ch3_tx_end_int_ena设置为1时，通道3的mt_ch3_tx_end_int.raw的中断状态位。*/
#define RMT_CH3_TX_END_INT_ST  (BIT(9))
#define RMT_CH3_TX_END_INT_ST_M  (BIT(9))
#define RMT_CH3_TX_END_INT_ST_V  0x1
#define RMT_CH3_TX_END_INT_ST_S  9
/* RMT_CH2_ERR_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*描述：当rmt_ch2_err_int_ena设置为1时，通道2的rmt_ch2-err_int_raw的中断状态位。*/
#define RMT_CH2_ERR_INT_ST  (BIT(8))
#define RMT_CH2_ERR_INT_ST_M  (BIT(8))
#define RMT_CH2_ERR_INT_ST_V  0x1
#define RMT_CH2_ERR_INT_ST_S  8
/* RMT_CH2_RX_END_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*描述：当rmt_ch2_rx_end_int_ena设置为1时，通道2的rmt_ch_2_rx_end_int_raw的中断状态位。*/
#define RMT_CH2_RX_END_INT_ST  (BIT(7))
#define RMT_CH2_RX_END_INT_ST_M  (BIT(7))
#define RMT_CH2_RX_END_INT_ST_V  0x1
#define RMT_CH2_RX_END_INT_ST_S  7
/* RMT_CH2_TX_END_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*描述：当mt_ch2_tx_end_int_ena设置为1时，通道2的mt_ch2_tx_end_int.raw的中断状态位。*/
#define RMT_CH2_TX_END_INT_ST  (BIT(6))
#define RMT_CH2_TX_END_INT_ST_M  (BIT(6))
#define RMT_CH2_TX_END_INT_ST_V  0x1
#define RMT_CH2_TX_END_INT_ST_S  6
/* RMT_CH1_ERR_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*描述：当rmt_ch1_err_int_ena设置为1时，通道1的rmt_ch1-err_int_raw的中断状态位。*/
#define RMT_CH1_ERR_INT_ST  (BIT(5))
#define RMT_CH1_ERR_INT_ST_M  (BIT(5))
#define RMT_CH1_ERR_INT_ST_V  0x1
#define RMT_CH1_ERR_INT_ST_S  5
/* RMT_CH1_RX_END_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*描述：当rmt_ch1_rx_end_int_ena设置为1时，通道1的rmt_ch1-rx_end.int_raw的中断状态位。*/
#define RMT_CH1_RX_END_INT_ST  (BIT(4))
#define RMT_CH1_RX_END_INT_ST_M  (BIT(4))
#define RMT_CH1_RX_END_INT_ST_V  0x1
#define RMT_CH1_RX_END_INT_ST_S  4
/* RMT_CH1_TX_END_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*描述：当mt_ch1_tx_end_int_ena设置为1时，通道1的mt_ch1_tx_end_int.raw的中断状态位。*/
#define RMT_CH1_TX_END_INT_ST  (BIT(3))
#define RMT_CH1_TX_END_INT_ST_M  (BIT(3))
#define RMT_CH1_TX_END_INT_ST_V  0x1
#define RMT_CH1_TX_END_INT_ST_S  3
/* RMT_CH0_ERR_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*描述：当rmt_ch0_err_int_ena设置为0时，通道0的rmt_ch0 _err_int.raw的中断状态位。*/
#define RMT_CH0_ERR_INT_ST  (BIT(2))
#define RMT_CH0_ERR_INT_ST_M  (BIT(2))
#define RMT_CH0_ERR_INT_ST_V  0x1
#define RMT_CH0_ERR_INT_ST_S  2
/* RMT_CH0_RX_END_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*描述：当rmt_ch0_rx_end_int_ena设置为0时，通道0的rmt_ch0 _rx_end.int_raw的中断状态位。*/
#define RMT_CH0_RX_END_INT_ST  (BIT(1))
#define RMT_CH0_RX_END_INT_ST_M  (BIT(1))
#define RMT_CH0_RX_END_INT_ST_V  0x1
#define RMT_CH0_RX_END_INT_ST_S  1
/* RMT_CH0_TX_END_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*描述：当mt_ch0_tx_end_int_ena设置为0时，通道0的mt_ch0 _tx_end.int_raw的中断状态位。*/
#define RMT_CH0_TX_END_INT_ST  (BIT(0))
#define RMT_CH0_TX_END_INT_ST_M  (BIT(0))
#define RMT_CH0_TX_END_INT_ST_V  0x1
#define RMT_CH0_TX_END_INT_ST_S  0

#define RMT_INT_ENA_REG          (DR_REG_RMT_BASE + 0x00a8)
/* RMT_CH7_TX_THR_EVENT_INT_ENA:R/W；位位置：[31]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch7_tx_thr_event_int_st。*/
#define RMT_CH7_TX_THR_EVENT_INT_ENA  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_ENA_M  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH7_TX_THR_EVENT_INT_ENA_S  31
/* RMT_CH6_TX_tr_EVENT_INT_ENA:R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch6_tx_tr_event_int_st。*/
#define RMT_CH6_TX_THR_EVENT_INT_ENA  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_ENA_M  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH6_TX_THR_EVENT_INT_ENA_S  30
/* RMT_CH5_TX_THR_EVENT_INT_ENA:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch5_tx_thr_event_int_st。*/
#define RMT_CH5_TX_THR_EVENT_INT_ENA  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_ENA_M  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH5_TX_THR_EVENT_INT_ENA_S  29
/* RMT_CH4_TX_THR_EVENT_INT_ENA:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch4_tx_thr_event_int_st。*/
#define RMT_CH4_TX_THR_EVENT_INT_ENA  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_ENA_M  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH4_TX_THR_EVENT_INT_ENA_S  28
/* RMT_CH3_TX_THR_EVENT_INT_ENA:R/W；位位置：[27]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch3_tx_thr_event_int_st。*/
#define RMT_CH3_TX_THR_EVENT_INT_ENA  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_ENA_M  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH3_TX_THR_EVENT_INT_ENA_S  27
/* RMT_CH2_TX_THR_EVENT_INT_ENA:R/W；位位置：[26]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch2_tx_thr_event_int_st。*/
#define RMT_CH2_TX_THR_EVENT_INT_ENA  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_ENA_M  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH2_TX_THR_EVENT_INT_ENA_S  26
/* RMT_CH1_TX_THR_EVENT_INT_ENA:R/W；位位置：[25]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch1_tx_thr_event_int_st。*/
#define RMT_CH1_TX_THR_EVENT_INT_ENA  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_ENA_M  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH1_TX_THR_EVENT_INT_ENA_S  25
/* RMT_CH0_TX_THR_EVENT_INT_ENA:R/W；位位置：[24]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch0_tx_thr_event_int_st。*/
#define RMT_CH0_TX_THR_EVENT_INT_ENA  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_ENA_M  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_ENA_V  0x1
#define RMT_CH0_TX_THR_EVENT_INT_ENA_S  24
/* RMT_CH7_ERR_INT_ENA:R/W；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch7_err_int_st。*/
#define RMT_CH7_ERR_INT_ENA  (BIT(23))
#define RMT_CH7_ERR_INT_ENA_M  (BIT(23))
#define RMT_CH7_ERR_INT_ENA_V  0x1
#define RMT_CH7_ERR_INT_ENA_S  23
/* RMT_CH7_RX_END_INT_ENA:R/W；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch7_rx_end_int_st。*/
#define RMT_CH7_RX_END_INT_ENA  (BIT(22))
#define RMT_CH7_RX_END_INT_ENA_M  (BIT(22))
#define RMT_CH7_RX_END_INT_ENA_V  0x1
#define RMT_CH7_RX_END_INT_ENA_S  22
/* RMT_CH7_TX_END_INT_ENA:R/W；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch7_tx_end_int_st。*/
#define RMT_CH7_TX_END_INT_ENA  (BIT(21))
#define RMT_CH7_TX_END_INT_ENA_M  (BIT(21))
#define RMT_CH7_TX_END_INT_ENA_V  0x1
#define RMT_CH7_TX_END_INT_ENA_S  21
/* RMT_CH6_ERR_INT_ENA:R/W；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch6_err_int_st。*/
#define RMT_CH6_ERR_INT_ENA  (BIT(20))
#define RMT_CH6_ERR_INT_ENA_M  (BIT(20))
#define RMT_CH6_ERR_INT_ENA_V  0x1
#define RMT_CH6_ERR_INT_ENA_S  20
/* RMT_CH6_RX_END_INT_ENA:R/W；位位置：[19]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch6_rx_end_int_st。*/
#define RMT_CH6_RX_END_INT_ENA  (BIT(19))
#define RMT_CH6_RX_END_INT_ENA_M  (BIT(19))
#define RMT_CH6_RX_END_INT_ENA_V  0x1
#define RMT_CH6_RX_END_INT_ENA_S  19
/* RMT_CH6_TX_END_INT_ENA:R/W；位位置：[18]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch6_tx_end_int_st。*/
#define RMT_CH6_TX_END_INT_ENA  (BIT(18))
#define RMT_CH6_TX_END_INT_ENA_M  (BIT(18))
#define RMT_CH6_TX_END_INT_ENA_V  0x1
#define RMT_CH6_TX_END_INT_ENA_S  18
/* RMT_CH5_ERR_INT_ENA:R/W；位位置：[17]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch5_err_int_st。*/
#define RMT_CH5_ERR_INT_ENA  (BIT(17))
#define RMT_CH5_ERR_INT_ENA_M  (BIT(17))
#define RMT_CH5_ERR_INT_ENA_V  0x1
#define RMT_CH5_ERR_INT_ENA_S  17
/* RMT_CH5_RX_END_INT_ENA:R/W；位位置：[16]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch5_rx_end_int_st。*/
#define RMT_CH5_RX_END_INT_ENA  (BIT(16))
#define RMT_CH5_RX_END_INT_ENA_M  (BIT(16))
#define RMT_CH5_RX_END_INT_ENA_V  0x1
#define RMT_CH5_RX_END_INT_ENA_S  16
/* RMT_CH5_TX_END_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch5_tx_end_int_st。*/
#define RMT_CH5_TX_END_INT_ENA  (BIT(15))
#define RMT_CH5_TX_END_INT_ENA_M  (BIT(15))
#define RMT_CH5_TX_END_INT_ENA_V  0x1
#define RMT_CH5_TX_END_INT_ENA_S  15
/* RMT_CH4_ERR_INT_ENA:R/W；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch4_err_int_st。*/
#define RMT_CH4_ERR_INT_ENA  (BIT(14))
#define RMT_CH4_ERR_INT_ENA_M  (BIT(14))
#define RMT_CH4_ERR_INT_ENA_V  0x1
#define RMT_CH4_ERR_INT_ENA_S  14
/* RMT_CH4_RX_END_INT_ENA:R/W；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch4_rx_end_int_st。*/
#define RMT_CH4_RX_END_INT_ENA  (BIT(13))
#define RMT_CH4_RX_END_INT_ENA_M  (BIT(13))
#define RMT_CH4_RX_END_INT_ENA_V  0x1
#define RMT_CH4_RX_END_INT_ENA_S  13
/* RMT_CH4_TX_END_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch4_tx_end_int_st。*/
#define RMT_CH4_TX_END_INT_ENA  (BIT(12))
#define RMT_CH4_TX_END_INT_ENA_M  (BIT(12))
#define RMT_CH4_TX_END_INT_ENA_V  0x1
#define RMT_CH4_TX_END_INT_ENA_S  12
/* RMT_CH3_ERR_INT_ENA：R/W；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch3_err_int_st。*/
#define RMT_CH3_ERR_INT_ENA  (BIT(11))
#define RMT_CH3_ERR_INT_ENA_M  (BIT(11))
#define RMT_CH3_ERR_INT_ENA_V  0x1
#define RMT_CH3_ERR_INT_ENA_S  11
/* RMT_CH3_RX_END_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch3_rx_end_int_st。*/
#define RMT_CH3_RX_END_INT_ENA  (BIT(10))
#define RMT_CH3_RX_END_INT_ENA_M  (BIT(10))
#define RMT_CH3_RX_END_INT_ENA_V  0x1
#define RMT_CH3_RX_END_INT_ENA_S  10
/* RMT_CH3_TX_END_INT_ENA：R/W；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch3_tx_end_int_st。*/
#define RMT_CH3_TX_END_INT_ENA  (BIT(9))
#define RMT_CH3_TX_END_INT_ENA_M  (BIT(9))
#define RMT_CH3_TX_END_INT_ENA_V  0x1
#define RMT_CH3_TX_END_INT_ENA_S  9
/* RMT_CH2_ERR_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch2_err_int_st。*/
#define RMT_CH2_ERR_INT_ENA  (BIT(8))
#define RMT_CH2_ERR_INT_ENA_M  (BIT(8))
#define RMT_CH2_ERR_INT_ENA_V  0x1
#define RMT_CH2_ERR_INT_ENA_S  8
/* RMT_CH2_RX_END_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch2_rx_end_int_st。*/
#define RMT_CH2_RX_END_INT_ENA  (BIT(7))
#define RMT_CH2_RX_END_INT_ENA_M  (BIT(7))
#define RMT_CH2_RX_END_INT_ENA_V  0x1
#define RMT_CH2_RX_END_INT_ENA_S  7
/* RMT_CH2_TX_END_INT_ENA：R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch2_tx_end_int_st。*/
#define RMT_CH2_TX_END_INT_ENA  (BIT(6))
#define RMT_CH2_TX_END_INT_ENA_M  (BIT(6))
#define RMT_CH2_TX_END_INT_ENA_V  0x1
#define RMT_CH2_TX_END_INT_ENA_S  6
/* RMT_CH1_ERR_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch1_err_int_st。*/
#define RMT_CH1_ERR_INT_ENA  (BIT(5))
#define RMT_CH1_ERR_INT_ENA_M  (BIT(5))
#define RMT_CH1_ERR_INT_ENA_V  0x1
#define RMT_CH1_ERR_INT_ENA_S  5
/* RMT_CH1_RX_END_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch1_rx_end_int_st。*/
#define RMT_CH1_RX_END_INT_ENA  (BIT(4))
#define RMT_CH1_RX_END_INT_ENA_M  (BIT(4))
#define RMT_CH1_RX_END_INT_ENA_V  0x1
#define RMT_CH1_RX_END_INT_ENA_S  4
/* RMT_CH1_TX_END_INT_ENA：R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch1_tx_end_int_st。*/
#define RMT_CH1_TX_END_INT_ENA  (BIT(3))
#define RMT_CH1_TX_END_INT_ENA_M  (BIT(3))
#define RMT_CH1_TX_END_INT_ENA_V  0x1
#define RMT_CH1_TX_END_INT_ENA_S  3
/* RMT_CH0_ERR_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch0_err_int_st。*/
#define RMT_CH0_ERR_INT_ENA  (BIT(2))
#define RMT_CH0_ERR_INT_ENA_M  (BIT(2))
#define RMT_CH0_ERR_INT_ENA_V  0x1
#define RMT_CH0_ERR_INT_ENA_S  2
/* RMT_CH0_RX_END_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch0_rx_end_int_st。*/
#define RMT_CH0_RX_END_INT_ENA  (BIT(1))
#define RMT_CH0_RX_END_INT_ENA_M  (BIT(1))
#define RMT_CH0_RX_END_INT_ENA_V  0x1
#define RMT_CH0_RX_END_INT_ENA_S  1
/* RMT_CH0_TX_END_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以启用rmt_ch0_tx_end_int_st。*/
#define RMT_CH0_TX_END_INT_ENA  (BIT(0))
#define RMT_CH0_TX_END_INT_ENA_M  (BIT(0))
#define RMT_CH0_TX_END_INT_ENA_V  0x1
#define RMT_CH0_TX_END_INT_ENA_S  0

#define RMT_INT_CLR_REG          (DR_REG_RMT_BASE + 0x00ac)
/* RMT_CH7_TX_THR_EVENT_INT_CLR:WO；位位置：[31]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch7_tx_thr_event_int_raw中断。*/
#define RMT_CH7_TX_THR_EVENT_INT_CLR  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_CLR_M  (BIT(31))
#define RMT_CH7_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH7_TX_THR_EVENT_INT_CLR_S  31
/* RMT_CH6_TX_tr_EVENT_INT_CLR:WO；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch6_tx_tr_event_int_raw中断。*/
#define RMT_CH6_TX_THR_EVENT_INT_CLR  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_CLR_M  (BIT(30))
#define RMT_CH6_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH6_TX_THR_EVENT_INT_CLR_S  30
/* RMT_CH5_TX_THR_EVENT_INT_CLR:WO；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch5_tx_thr_event_int_raw中断。*/
#define RMT_CH5_TX_THR_EVENT_INT_CLR  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_CLR_M  (BIT(29))
#define RMT_CH5_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH5_TX_THR_EVENT_INT_CLR_S  29
/* RMT_CH4_TX_THR_EVENT_INT_CLR:WO；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch4_tx_thr_event_int_raw中断。*/
#define RMT_CH4_TX_THR_EVENT_INT_CLR  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_CLR_M  (BIT(28))
#define RMT_CH4_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH4_TX_THR_EVENT_INT_CLR_S  28
/* RMT_CH3_TX_THR_EVENT_INT_CLR:WO；位位置：[27]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch3_tx_thr_event_int_raw中断。*/
#define RMT_CH3_TX_THR_EVENT_INT_CLR  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_CLR_M  (BIT(27))
#define RMT_CH3_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH3_TX_THR_EVENT_INT_CLR_S  27
/* RMT_CH2_TX_THR_EVENT_INT_CLR:WO；位位置：[26]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch2_tx_thr_event_int_raw中断。*/
#define RMT_CH2_TX_THR_EVENT_INT_CLR  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_CLR_M  (BIT(26))
#define RMT_CH2_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH2_TX_THR_EVENT_INT_CLR_S  26
/* RMT_CH1_TX_THR_EVENT_INT_CLR:WO；位位置：[25]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch1_tx_thr_event_int_raw中断。*/
#define RMT_CH1_TX_THR_EVENT_INT_CLR  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_CLR_M  (BIT(25))
#define RMT_CH1_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH1_TX_THR_EVENT_INT_CLR_S  25
/* RMT_CH0_TX_THR_EVENT_INT_CLR:WO；位位置：[24]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch0_tx_thr_event_int_raw中断。*/
#define RMT_CH0_TX_THR_EVENT_INT_CLR  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_CLR_M  (BIT(24))
#define RMT_CH0_TX_THR_EVENT_INT_CLR_V  0x1
#define RMT_CH0_TX_THR_EVENT_INT_CLR_S  24
/* RMT_CH7_ERR_INT_CLR:WO；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch7_err_int_raw。*/
#define RMT_CH7_ERR_INT_CLR  (BIT(23))
#define RMT_CH7_ERR_INT_CLR_M  (BIT(23))
#define RMT_CH7_ERR_INT_CLR_V  0x1
#define RMT_CH7_ERR_INT_CLR_S  23
/* RMT_CH7_RX_END_INT_CLR:WO；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch7_tx_end_int_raw。*/
#define RMT_CH7_RX_END_INT_CLR  (BIT(22))
#define RMT_CH7_RX_END_INT_CLR_M  (BIT(22))
#define RMT_CH7_RX_END_INT_CLR_V  0x1
#define RMT_CH7_RX_END_INT_CLR_S  22
/* RMT_CH7_TX_END_INT_CLR:WO；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch7_rx_end_int_raw。。*/
#define RMT_CH7_TX_END_INT_CLR  (BIT(21))
#define RMT_CH7_TX_END_INT_CLR_M  (BIT(21))
#define RMT_CH7_TX_END_INT_CLR_V  0x1
#define RMT_CH7_TX_END_INT_CLR_S  21
/* RMT_CH6_ERR_INT_CLR:WO；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch6_err_int_raw。*/
#define RMT_CH6_ERR_INT_CLR  (BIT(20))
#define RMT_CH6_ERR_INT_CLR_M  (BIT(20))
#define RMT_CH6_ERR_INT_CLR_V  0x1
#define RMT_CH6_ERR_INT_CLR_S  20
/* RMT_CH6_RX_END_INT_CLR:WO；位位置：[19]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch6_tx_end_int_raw。*/
#define RMT_CH6_RX_END_INT_CLR  (BIT(19))
#define RMT_CH6_RX_END_INT_CLR_M  (BIT(19))
#define RMT_CH6_RX_END_INT_CLR_V  0x1
#define RMT_CH6_RX_END_INT_CLR_S  19
/* RMT_CH6_TX_END_INT_CLR:WO；位位置：[18]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch6_rx_end_int_raw。。*/
#define RMT_CH6_TX_END_INT_CLR  (BIT(18))
#define RMT_CH6_TX_END_INT_CLR_M  (BIT(18))
#define RMT_CH6_TX_END_INT_CLR_V  0x1
#define RMT_CH6_TX_END_INT_CLR_S  18
/* RMT_CH5_ERR_INT_CLR:WO；位位置：[17]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch5_err_int_raw。*/
#define RMT_CH5_ERR_INT_CLR  (BIT(17))
#define RMT_CH5_ERR_INT_CLR_M  (BIT(17))
#define RMT_CH5_ERR_INT_CLR_V  0x1
#define RMT_CH5_ERR_INT_CLR_S  17
/* RMT_CH5_RX_END_INT_CLR:WO；位位置：[16]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch5_tx_end_int_raw。*/
#define RMT_CH5_RX_END_INT_CLR  (BIT(16))
#define RMT_CH5_RX_END_INT_CLR_M  (BIT(16))
#define RMT_CH5_RX_END_INT_CLR_V  0x1
#define RMT_CH5_RX_END_INT_CLR_S  16
/* RMT_CH5_TX_END_INT_CLR:WO；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch5_rx_end_int_raw。。*/
#define RMT_CH5_TX_END_INT_CLR  (BIT(15))
#define RMT_CH5_TX_END_INT_CLR_M  (BIT(15))
#define RMT_CH5_TX_END_INT_CLR_V  0x1
#define RMT_CH5_TX_END_INT_CLR_S  15
/* RMT_CH4_ERR_INT_CLR:WO；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch4_err_int_raw。*/
#define RMT_CH4_ERR_INT_CLR  (BIT(14))
#define RMT_CH4_ERR_INT_CLR_M  (BIT(14))
#define RMT_CH4_ERR_INT_CLR_V  0x1
#define RMT_CH4_ERR_INT_CLR_S  14
/* RMT_CH4_RX_END_INT_CLR:WO；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch4_tx_end_int_raw。*/
#define RMT_CH4_RX_END_INT_CLR  (BIT(13))
#define RMT_CH4_RX_END_INT_CLR_M  (BIT(13))
#define RMT_CH4_RX_END_INT_CLR_V  0x1
#define RMT_CH4_RX_END_INT_CLR_S  13
/* RMT_CH4_TX_END_INT_CLR:WO；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch4_rx_end_int_raw。。*/
#define RMT_CH4_TX_END_INT_CLR  (BIT(12))
#define RMT_CH4_TX_END_INT_CLR_M  (BIT(12))
#define RMT_CH4_TX_END_INT_CLR_V  0x1
#define RMT_CH4_TX_END_INT_CLR_S  12
/* RMT_CH3_ERR_INT_CLR:WO；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch3_err_int_raw。*/
#define RMT_CH3_ERR_INT_CLR  (BIT(11))
#define RMT_CH3_ERR_INT_CLR_M  (BIT(11))
#define RMT_CH3_ERR_INT_CLR_V  0x1
#define RMT_CH3_ERR_INT_CLR_S  11
/* RMT_CH3_RX_END_INT_CLR:WO；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch3_tx_end_int_raw。*/
#define RMT_CH3_RX_END_INT_CLR  (BIT(10))
#define RMT_CH3_RX_END_INT_CLR_M  (BIT(10))
#define RMT_CH3_RX_END_INT_CLR_V  0x1
#define RMT_CH3_RX_END_INT_CLR_S  10
/* RMT_CH3_TX_END_INT_CLR:WO；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch3_rx_end_int_raw。。*/
#define RMT_CH3_TX_END_INT_CLR  (BIT(9))
#define RMT_CH3_TX_END_INT_CLR_M  (BIT(9))
#define RMT_CH3_TX_END_INT_CLR_V  0x1
#define RMT_CH3_TX_END_INT_CLR_S  9
/* RMT_CH2_ERR_INT_CLR:WO；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch2_err_int_raw。*/
#define RMT_CH2_ERR_INT_CLR  (BIT(8))
#define RMT_CH2_ERR_INT_CLR_M  (BIT(8))
#define RMT_CH2_ERR_INT_CLR_V  0x1
#define RMT_CH2_ERR_INT_CLR_S  8
/* RMT_CH2_RX_END_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch2_tx_end_int_raw。*/
#define RMT_CH2_RX_END_INT_CLR  (BIT(7))
#define RMT_CH2_RX_END_INT_CLR_M  (BIT(7))
#define RMT_CH2_RX_END_INT_CLR_V  0x1
#define RMT_CH2_RX_END_INT_CLR_S  7
/* RMT_CH2_TX_END_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch2_rx_end_int_raw。。*/
#define RMT_CH2_TX_END_INT_CLR  (BIT(6))
#define RMT_CH2_TX_END_INT_CLR_M  (BIT(6))
#define RMT_CH2_TX_END_INT_CLR_V  0x1
#define RMT_CH2_TX_END_INT_CLR_S  6
/* RMT_CH1_ERR_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch1_err_int_raw。*/
#define RMT_CH1_ERR_INT_CLR  (BIT(5))
#define RMT_CH1_ERR_INT_CLR_M  (BIT(5))
#define RMT_CH1_ERR_INT_CLR_V  0x1
#define RMT_CH1_ERR_INT_CLR_S  5
/* RMT_CH1_RX_END_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch1_tx_end_int_raw。*/
#define RMT_CH1_RX_END_INT_CLR  (BIT(4))
#define RMT_CH1_RX_END_INT_CLR_M  (BIT(4))
#define RMT_CH1_RX_END_INT_CLR_V  0x1
#define RMT_CH1_RX_END_INT_CLR_S  4
/* RMT_CH1_TX_END_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch1_rx_end_int_raw。。*/
#define RMT_CH1_TX_END_INT_CLR  (BIT(3))
#define RMT_CH1_TX_END_INT_CLR_M  (BIT(3))
#define RMT_CH1_TX_END_INT_CLR_V  0x1
#define RMT_CH1_TX_END_INT_CLR_S  3
/* RMT_CH0_ERR_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch0_err_int_raw。*/
#define RMT_CH0_ERR_INT_CLR  (BIT(2))
#define RMT_CH0_ERR_INT_CLR_M  (BIT(2))
#define RMT_CH0_ERR_INT_CLR_V  0x1
#define RMT_CH0_ERR_INT_CLR_S  2
/* RMT_CH0_RX_END_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch0_tx_end_int_raw。*/
#define RMT_CH0_RX_END_INT_CLR  (BIT(1))
#define RMT_CH0_RX_END_INT_CLR_M  (BIT(1))
#define RMT_CH0_RX_END_INT_CLR_V  0x1
#define RMT_CH0_RX_END_INT_CLR_S  1
/* RMT_CH0_TX_END_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除rmt_ch0_rx_end_int_raw。。*/
#define RMT_CH0_TX_END_INT_CLR  (BIT(0))
#define RMT_CH0_TX_END_INT_CLR_M  (BIT(0))
#define RMT_CH0_TX_END_INT_CLR_V  0x1
#define RMT_CH0_TX_END_INT_CLR_S  0

#define RMT_CH0CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00b0)
/* RMT_CARRIER_HIGH_CH0:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*description:此寄存器用于配置信道0的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH0  0x0000FFFF
#define RMT_CARRIER_HIGH_CH0_M  ((RMT_CARRIER_HIGH_CH0_V)<<(RMT_CARRIER_HIGH_CH0_S))
#define RMT_CARRIER_HIGH_CH0_V  0xFFFF
#define RMT_CARRIER_HIGH_CH0_S  16
/* RMT_CARRIER_LOW_CH0:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*description:此寄存器用于配置信道0的载波低电平值。*/
#define RMT_CARRIER_LOW_CH0  0x0000FFFF
#define RMT_CARRIER_LOW_CH0_M  ((RMT_CARRIER_LOW_CH0_V)<<(RMT_CARRIER_LOW_CH0_S))
#define RMT_CARRIER_LOW_CH0_V  0xFFFF
#define RMT_CARRIER_LOW_CH0_S  0

#define RMT_CH1CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00b4)
/* RMT_CARRIER_HIGH_CH1:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*description:此寄存器用于配置信道1的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH1  0x0000FFFF
#define RMT_CARRIER_HIGH_CH1_M  ((RMT_CARRIER_HIGH_CH1_V)<<(RMT_CARRIER_HIGH_CH1_S))
#define RMT_CARRIER_HIGH_CH1_V  0xFFFF
#define RMT_CARRIER_HIGH_CH1_S  16
/* RMT_CARRIER_LOW_CH1:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*description:此寄存器用于配置信道1的载波低电平值。*/
#define RMT_CARRIER_LOW_CH1  0x0000FFFF
#define RMT_CARRIER_LOW_CH1_M  ((RMT_CARRIER_LOW_CH1_V)<<(RMT_CARRIER_LOW_CH1_S))
#define RMT_CARRIER_LOW_CH1_V  0xFFFF
#define RMT_CARRIER_LOW_CH1_S  0

#define RMT_CH2CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00b8)
/* RMT_CARRIER_HIGH_CH2:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*description:此寄存器用于配置信道2的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH2  0x0000FFFF
#define RMT_CARRIER_HIGH_CH2_M  ((RMT_CARRIER_HIGH_CH2_V)<<(RMT_CARRIER_HIGH_CH2_S))
#define RMT_CARRIER_HIGH_CH2_V  0xFFFF
#define RMT_CARRIER_HIGH_CH2_S  16
/* RMT_CARRIER_LOW_CH2:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*description:此寄存器用于配置信道2的载波低电平值。*/
#define RMT_CARRIER_LOW_CH2  0x0000FFFF
#define RMT_CARRIER_LOW_CH2_M  ((RMT_CARRIER_LOW_CH2_V)<<(RMT_CARRIER_LOW_CH2_S))
#define RMT_CARRIER_LOW_CH2_V  0xFFFF
#define RMT_CARRIER_LOW_CH2_S  0

#define RMT_CH3CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00bc)
/* RMT_CARRIER_HIGH_CH3:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*description:此寄存器用于配置信道3的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH3  0x0000FFFF
#define RMT_CARRIER_HIGH_CH3_M  ((RMT_CARRIER_HIGH_CH3_V)<<(RMT_CARRIER_HIGH_CH3_S))
#define RMT_CARRIER_HIGH_CH3_V  0xFFFF
#define RMT_CARRIER_HIGH_CH3_S  16
/* RMT_CARRIER_LOW_CH3:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*description:此寄存器用于配置信道3的载波低电平值。*/
#define RMT_CARRIER_LOW_CH3  0x0000FFFF
#define RMT_CARRIER_LOW_CH3_M  ((RMT_CARRIER_LOW_CH3_V)<<(RMT_CARRIER_LOW_CH3_S))
#define RMT_CARRIER_LOW_CH3_V  0xFFFF
#define RMT_CARRIER_LOW_CH3_S  0

#define RMT_CH4CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00c0)
/* RMT_CARRIER_HIGH_CH4:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*description:此寄存器用于配置信道4的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH4  0x0000FFFF
#define RMT_CARRIER_HIGH_CH4_M  ((RMT_CARRIER_HIGH_CH4_V)<<(RMT_CARRIER_HIGH_CH4_S))
#define RMT_CARRIER_HIGH_CH4_V  0xFFFF
#define RMT_CARRIER_HIGH_CH4_S  16
/* RMT_CARRIER_LOW_CH4:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*描述：此寄存器用于配置信道4的载波低电平值。*/
#define RMT_CARRIER_LOW_CH4  0x0000FFFF
#define RMT_CARRIER_LOW_CH4_M  ((RMT_CARRIER_LOW_CH4_V)<<(RMT_CARRIER_LOW_CH4_S))
#define RMT_CARRIER_LOW_CH4_V  0xFFFF
#define RMT_CARRIER_LOW_CH4_S  0

#define RMT_CH5CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00c4)
/* RMT_CARRIER_HIGH_CH5:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*description:此寄存器用于配置信道5的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH5  0x0000FFFF
#define RMT_CARRIER_HIGH_CH5_M  ((RMT_CARRIER_HIGH_CH5_V)<<(RMT_CARRIER_HIGH_CH5_S))
#define RMT_CARRIER_HIGH_CH5_V  0xFFFF
#define RMT_CARRIER_HIGH_CH5_S  16
/* RMT_CARRIER_LOW_CH5:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*description:此寄存器用于配置信道5的载波低电平值。*/
#define RMT_CARRIER_LOW_CH5  0x0000FFFF
#define RMT_CARRIER_LOW_CH5_M  ((RMT_CARRIER_LOW_CH5_V)<<(RMT_CARRIER_LOW_CH5_S))
#define RMT_CARRIER_LOW_CH5_V  0xFFFF
#define RMT_CARRIER_LOW_CH5_S  0

#define RMT_CH6CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00c8)
/* RMT_CARRIER_HIGH_CH6:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*描述：此寄存器用于配置信道6的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH6  0x0000FFFF
#define RMT_CARRIER_HIGH_CH6_M  ((RMT_CARRIER_HIGH_CH6_V)<<(RMT_CARRIER_HIGH_CH6_S))
#define RMT_CARRIER_HIGH_CH6_V  0xFFFF
#define RMT_CARRIER_HIGH_CH6_S  16
/* RMT_CARRIER_LOW_CH6:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*描述：此寄存器用于配置信道6的载波低电平值。*/
#define RMT_CARRIER_LOW_CH6  0x0000FFFF
#define RMT_CARRIER_LOW_CH6_M  ((RMT_CARRIER_LOW_CH6_V)<<(RMT_CARRIER_LOW_CH6_S))
#define RMT_CARRIER_LOW_CH6_V  0xFFFF
#define RMT_CARRIER_LOW_CH6_S  0

#define RMT_CH7CARRIER_DUTY_REG          (DR_REG_RMT_BASE + 0x00cc)
/* RMT_CARRIER_HIGH_CH7:R/W；比特位置：[31:16]；默认值：16'h40；*/
/*描述：此寄存器用于配置信道7的载波高电平值。*/
#define RMT_CARRIER_HIGH_CH7  0x0000FFFF
#define RMT_CARRIER_HIGH_CH7_M  ((RMT_CARRIER_HIGH_CH7_V)<<(RMT_CARRIER_HIGH_CH7_S))
#define RMT_CARRIER_HIGH_CH7_V  0xFFFF
#define RMT_CARRIER_HIGH_CH7_S  16
/* RMT_CARRIER_LOW_CH7:R/W；比特位置：[15:0]；默认值：16'h40；*/
/*描述：此寄存器用于配置信道7的载波低电平值。*/
#define RMT_CARRIER_LOW_CH7  0x0000FFFF
#define RMT_CARRIER_LOW_CH7_M  ((RMT_CARRIER_LOW_CH7_V)<<(RMT_CARRIER_LOW_CH7_S))
#define RMT_CARRIER_LOW_CH7_V  0xFFFF
#define RMT_CARRIER_LOW_CH7_S  0

#define RMT_CH0_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00d0)
/* RMT_TX_LIM_CH0:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel0发送的数据超过reg_rmt_tx_lim_ch0时，channel0会产生相关中断。*/
#define RMT_TX_LIM_CH0  0x000001FF
#define RMT_TX_LIM_CH0_M  ((RMT_TX_LIM_CH0_V)<<(RMT_TX_LIM_CH0_S))
#define RMT_TX_LIM_CH0_V  0x1FF
#define RMT_TX_LIM_CH0_S  0

#define RMT_CH1_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00d4)
/* RMT_TX_LIM_CH1:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel1发送的数据超过reg_rmt_tx_lim_ch1时，channel1产生相对中断。*/
#define RMT_TX_LIM_CH1  0x000001FF
#define RMT_TX_LIM_CH1_M  ((RMT_TX_LIM_CH1_V)<<(RMT_TX_LIM_CH1_S))
#define RMT_TX_LIM_CH1_V  0x1FF
#define RMT_TX_LIM_CH1_S  0

#define RMT_CH2_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00d8)
/* RMT_TX_LIM_CH2:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel2发送的数据超过reg_rmt_tx_lim_ch2时，channel2产生相对中断。*/
#define RMT_TX_LIM_CH2  0x000001FF
#define RMT_TX_LIM_CH2_M  ((RMT_TX_LIM_CH2_V)<<(RMT_TX_LIM_CH2_S))
#define RMT_TX_LIM_CH2_V  0x1FF
#define RMT_TX_LIM_CH2_S  0

#define RMT_CH3_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00dc)
/* RMT_TX_LIM_CH3:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel3发送的数据超过reg_rmt_tx_lim_ch3时，channel3产生相对中断。*/
#define RMT_TX_LIM_CH3  0x000001FF
#define RMT_TX_LIM_CH3_M  ((RMT_TX_LIM_CH3_V)<<(RMT_TX_LIM_CH3_S))
#define RMT_TX_LIM_CH3_V  0x1FF
#define RMT_TX_LIM_CH3_S  0

#define RMT_CH4_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00e0)
/* RMT_TX_LIM_CH4:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel4发送的数据超过reg_rmt_tx_lim_ch4数据时，channel4产生相对中断。*/
#define RMT_TX_LIM_CH4  0x000001FF
#define RMT_TX_LIM_CH4_M  ((RMT_TX_LIM_CH4_V)<<(RMT_TX_LIM_CH4_S))
#define RMT_TX_LIM_CH4_V  0x1FF
#define RMT_TX_LIM_CH4_S  0

#define RMT_CH5_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00e4)
/* RMT_TX_LIM_CH5:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel5发送的数据超过reg_rmt_tx_lim_ch5时，channel5会产生相关中断。*/
#define RMT_TX_LIM_CH5  0x000001FF
#define RMT_TX_LIM_CH5_M  ((RMT_TX_LIM_CH5_V)<<(RMT_TX_LIM_CH5_S))
#define RMT_TX_LIM_CH5_V  0x1FF
#define RMT_TX_LIM_CH5_S  0

#define RMT_CH6_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00e8)
/* RMT_TX_LIM_CH6:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel6发送的数据超过reg_rmt_tx_lim_ch6数据时，channel6产生相对中断。*/
#define RMT_TX_LIM_CH6  0x000001FF
#define RMT_TX_LIM_CH6_M  ((RMT_TX_LIM_CH6_V)<<(RMT_TX_LIM_CH6_S))
#define RMT_TX_LIM_CH6_V  0x1FF
#define RMT_TX_LIM_CH6_S  0

#define RMT_CH7_TX_LIM_REG          (DR_REG_RMT_BASE + 0x00ec)
/* RMT_TX_LIM_CH7:R/W；位位置：[8:0]；默认值：9'h80；*/
/*描述：当channel7发送的数据超过reg_rmt_tx_lim_ch7时，channel7会产生相关中断。*/
#define RMT_TX_LIM_CH7  0x000001FF
#define RMT_TX_LIM_CH7_M  ((RMT_TX_LIM_CH7_V)<<(RMT_TX_LIM_CH7_S))
#define RMT_TX_LIM_CH7_V  0x1FF
#define RMT_TX_LIM_CH7_S  0

#define RMT_APB_CONF_REG          (DR_REG_RMT_BASE + 0x00f0)
/* RMT_MEM_TX_WRAP_EN:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：当需要发送的数据超过通道的mem可以存储的数据时，设置此位以启用mem的重用，此位与regrmt_txlim_chn一起使用。*/
#define RMT_MEM_TX_WRAP_EN  (BIT(1))
#define RMT_MEM_TX_WRAP_EN_M  (BIT(1))
#define RMT_MEM_TX_WRAP_EN_V  0x1
#define RMT_MEM_TX_WRAP_EN_S  1
/* RMT_APB_FIFO掩码：R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以禁用apb-fifo访问*/
#define RMT_APB_FIFO_MASK  (BIT(0))
#define RMT_APB_FIFO_MASK_M  (BIT(0))
#define RMT_APB_FIFO_MASK_V  0x1
#define RMT_APB_FIFO_MASK_S  0

#define RMT_DATE_REG          (DR_REG_RMT_BASE + 0x00fc)
/* RMT_DATE:R/W；位位置：[31:0]；默认值：32'h16022600；*/
/*description:这是版本寄存器。*/
#define RMT_DATE  0xFFFFFFFF
#define RMT_DATE_M  ((RMT_DATE_V)<<(RMT_DATE_S))
#define RMT_DATE_V  0xFFFFFFFF
#define RMT_DATE_S  0

/* RMT内存块地址*/
#define RMT_CHANNEL_MEM(i)  (DR_REG_RMT_BASE + 0x800 + 64 * 4 * (i))


#endif /*_SOC_RMT_REG_H_ */

