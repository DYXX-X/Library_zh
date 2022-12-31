/** 版权所有2021 Espressif Systems（Shanghai）PTE LTD
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/** RMT_CH0DATA_REG寄存器通过apb-fifo访问通道0的读写数据寄存器。
 */
#define RMT_CH0DATA_REG (DR_REG_RMT_BASE + 0x0)
/** RMT_CH0DATA:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道0的数据。
 */
#define RMT_CH0DATA    0xFFFFFFFFU
#define RMT_CH0DATA_M  (RMT_CH0DATA_V << RMT_CH0DATA_S)
#define RMT_CH0DATA_V  0xFFFFFFFFU
#define RMT_CH0DATA_S  0

/** RMT_CH1DATA_REG寄存器通过apb-fifo访问通道1的读写数据寄存器。
 */
#define RMT_CH1DATA_REG (DR_REG_RMT_BASE + 0x4)
/** RMT_CH1DATA:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道1的数据。
 */
#define RMT_CH1DATA    0xFFFFFFFFU
#define RMT_CH1DATA_M  (RMT_CH1DATA_V << RMT_CH1DATA_S)
#define RMT_CH1DATA_V  0xFFFFFFFFU
#define RMT_CH1DATA_S  0

/** RMT_CH2DATA_REG寄存器通过apb-fifo访问通道2的读写数据寄存器。
 */
#define RMT_CH2DATA_REG (DR_REG_RMT_BASE + 0x8)
/** RMT_CH2DATA:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道2的数据。
 */
#define RMT_CH2DATA    0xFFFFFFFFU
#define RMT_CH2DATA_M  (RMT_CH2DATA_V << RMT_CH2DATA_S)
#define RMT_CH2DATA_V  0xFFFFFFFFU
#define RMT_CH2DATA_S  0

/** RMT_CH3DATA_REG寄存器通过apb-fifo访问通道3的读写数据寄存器。
 */
#define RMT_CH3DATA_REG (DR_REG_RMT_BASE + 0xc)
/** RMT_CH3DATA:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道3的数据。
 */
#define RMT_CH3DATA    0xFFFFFFFFU
#define RMT_CH3DATA_M  (RMT_CH3DATA_V << RMT_CH3DATA_S)
#define RMT_CH3DATA_V  0xFFFFFFFFU
#define RMT_CH3DATA_S  0

/** RMT_CH4DATA_REG寄存器通过apb-fifo访问通道$n的读写数据寄存器。
 */
#define RMT_CH4DATA_REG (DR_REG_RMT_BASE + 0x10)
/** RMT_CH4DATA:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道$n的数据。
 */
#define RMT_CH4DATA    0xFFFFFFFFU
#define RMT_CH4DATA_M  (RMT_CH4DATA_V << RMT_CH4DATA_S)
#define RMT_CH4DATA_V  0xFFFFFFFFU
#define RMT_CH4DATA_S  0

/** RMT_CH5DATA_REG寄存器通过apb-fifo访问通道$n的读写数据寄存器。
 */
#define RMT_CH5DATA_REG (DR_REG_RMT_BASE + 0x14)
/** RMT_ch5数据：RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道$n的数据。
 */
#define RMT_CH5DATA    0xFFFFFFFFU
#define RMT_CH5DATA_M  (RMT_CH5DATA_V << RMT_CH5DATA_S)
#define RMT_CH5DATA_V  0xFFFFFFFFU
#define RMT_CH5DATA_S  0

/** RMT_CH6DATA_REG寄存器通过apb-fifo访问通道$n的读写数据寄存器。
 */
#define RMT_CH6DATA_REG (DR_REG_RMT_BASE + 0x18)
/** RMT_CH6DATA:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道$n的数据。
 */
#define RMT_CH6DATA    0xFFFFFFFFU
#define RMT_CH6DATA_M  (RMT_CH6DATA_V << RMT_CH6DATA_S)
#define RMT_CH6DATA_V  0xFFFFFFFFU
#define RMT_CH6DATA_S  0

/** RMT_CH7DATA_REG寄存器通过apb-fifo访问通道$n的读写数据寄存器。
 */
#define RMT_CH7DATA_REG (DR_REG_RMT_BASE + 0x1c)
/** RMT_ch7数据：RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道$n的数据。
 */
#define RMT_CH7DATA    0xFFFFFFFFU
#define RMT_CH7DATA_M  (RMT_CH7DATA_V << RMT_CH7DATA_S)
#define RMT_CH7DATA_V  0xFFFFFFFFU
#define RMT_CH7DATA_S  0

/** RMT_CH0CONF0_REG寄存器通道0配置寄存器0
 */
#define RMT_CH0CONF0_REG (DR_REG_RMT_BASE + 0x20)
/** RMT_TX_START_0:WT；位位置：[0]；默认值：0；设置此位以开始在CHANNEL0上发送数据。
 */
#define RMT_TX_START_0    (BIT(0))
#define RMT_TX_START_0_M  (RMT_TX_START_0_V << RMT_TX_START_0_S)
#define RMT_TX_START_0_V  0x00000001U
#define RMT_TX_START_0_S  0
/** RMT_MEM_RD_RST_0:WT；位位置：[1]；默认值：0；设置此位以通过访问变送器重置通道0的读ram地址。
 */
#define RMT_MEM_RD_RST_0    (BIT(1))
#define RMT_MEM_RD_RST_0_M  (RMT_MEM_RD_RST_0_V << RMT_MEM_RD_RST_0_S)
#define RMT_MEM_RD_RST_0_V  0x00000001U
#define RMT_MEM_RD_RST_0_S  1
/** RMT_APB_MEM_RST_0:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置CHANNEL0的W/R ram地址。
 */
#define RMT_APB_MEM_RST_0    (BIT(2))
#define RMT_APB_MEM_RST_0_M  (RMT_APB_MEM_RST_0_V << RMT_APB_MEM_RST_0_S)
#define RMT_APB_MEM_RST_0_V  0x00000001U
#define RMT_APB_MEM_RST_0_S  2
/** RMT_TX_CONTI_MODE_0:R/W；位位置：[3]；默认值：0；设置此位以重新开始从通道0中的第一个数据到最后一个数据的传输。
 */
#define RMT_TX_CONTI_MODE_0    (BIT(3))
#define RMT_TX_CONTI_MODE_0_M  (RMT_TX_CONTI_MODE_0_V << RMT_TX_CONTI_MODE_0_S)
#define RMT_TX_CONTI_MODE_0_V  0x00000001U
#define RMT_TX_CONTI_MODE_0_S  3
/** RMT_MEM_TX_WRAP_EN_0:R/W；位位置：[4]；默认值：0；这是环绕模式的通道0启用位：当要发送的数据超过其内存大小时，它将在开始时恢复发送。
 */
#define RMT_MEM_TX_WRAP_EN_0    (BIT(4))
#define RMT_MEM_TX_WRAP_EN_0_M  (RMT_MEM_TX_WRAP_EN_0_V << RMT_MEM_TX_WRAP_EN_0_S)
#define RMT_MEM_TX_WRAP_EN_0_V  0x00000001U
#define RMT_MEM_TX_WRAP_EN_0_S  4
/** RMT_IDLE_OUT_LV_0:R/W；位位置：[5]；默认值：0；当信道0处于空闲状态时，该位配置信道0中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_0    (BIT(5))
#define RMT_IDLE_OUT_LV_0_M  (RMT_IDLE_OUT_LV_0_V << RMT_IDLE_OUT_LV_0_S)
#define RMT_IDLE_OUT_LV_0_V  0x00000001U
#define RMT_IDLE_OUT_LV_0_S  5
/** RMT_IDLE_OUT_EN_0:R/W；位位置：[6]；默认值：0；这是处于空闲状态的CHANNEL0的输出启用控制位。
 */
#define RMT_IDLE_OUT_EN_0    (BIT(6))
#define RMT_IDLE_OUT_EN_0_M  (RMT_IDLE_OUT_EN_0_V << RMT_IDLE_OUT_EN_0_S)
#define RMT_IDLE_OUT_EN_0_V  0x00000001U
#define RMT_IDLE_OUT_EN_0_S  6
/** RMT_TX_STOP_0:R/W/SC；位位置：[7]；默认值：0；设置此位以停止信道0的发射机发送数据。
 */
#define RMT_TX_STOP_0    (BIT(7))
#define RMT_TX_STOP_0_M  (RMT_TX_STOP_0_V << RMT_TX_STOP_0_S)
#define RMT_TX_STOP_0_V  0x00000001U
#define RMT_TX_STOP_0_S  7
/** RMT_DIV_CNT_0:R/W；比特位置：[15:8]；默认值：2；该寄存器用于配置信道0时钟的除法器。
 */
#define RMT_DIV_CNT_0    0x000000FFU
#define RMT_DIV_CNT_0_M  (RMT_DIV_CNT_0_V << RMT_DIV_CNT_0_S)
#define RMT_DIV_CNT_0_V  0x000000FFU
#define RMT_DIV_CNT_0_S  8
/** RMT_MEM_SIZE_0:R/W；比特位置：[19:16]；默认值：1；此寄存器用于配置分配给CHANNEL0的最大内存大小。
 */
#define RMT_MEM_SIZE_0    0x0000000FU
#define RMT_MEM_SIZE_0_M  (RMT_MEM_SIZE_0_V << RMT_MEM_SIZE_0_S)
#define RMT_MEM_SIZE_0_V  0x0000000FU
#define RMT_MEM_SIZE_0_S  16
/** RMT_CARRIER_EFF_EN_0:R/W；位位置：[20]；默认值：1；1： 仅在CHANNEL0的发送数据状态下，在输出信号上添加载波调制。0：在CHANNEL 0的所有状态下，对输出信号添加载波调制，仅在RMT_CARRIR_EN_CH0为1时有效。
 */
#define RMT_CARRIER_EFF_EN_0    (BIT(20))
#define RMT_CARRIER_EFF_EN_0_M  (RMT_CARRIER_EFF_EN_0_V << RMT_CARRIER_EFF_EN_0_S)
#define RMT_CARRIER_EFF_EN_0_V  0x00000001U
#define RMT_CARRIER_EFF_EN_0_S  20
/** RMT_CARRIER_EN_0:R/W；位位置：[21]；默认值：1；这是信道0的载波调制启用控制位。1：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_0    (BIT(21))
#define RMT_CARRIER_EN_0_M  (RMT_CARRIER_EN_0_V << RMT_CARRIER_EN_0_S)
#define RMT_CARRIER_EN_0_V  0x00000001U
#define RMT_CARRIER_EN_0_S  21
/** RMT_CARRIER_OUT_LV_0:R/W；位位置：[22]；默认值：1；该位用于配置信道0的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_0    (BIT(22))
#define RMT_CARRIER_OUT_LV_0_M  (RMT_CARRIER_OUT_LV_0_V << RMT_CARRIER_OUT_LV_0_S)
#define RMT_CARRIER_OUT_LV_0_V  0x00000001U
#define RMT_CARRIER_OUT_LV_0_S  22
/** RMT_AFIFO_RST_0:WT；位位置：[23]；默认值：0；保留
 */
#define RMT_AFIFO_RST_0    (BIT(23))
#define RMT_AFIFO_RST_0_M  (RMT_AFIFO_RST_0_V << RMT_AFIFO_RST_0_S)
#define RMT_AFIFO_RST_0_V  0x00000001U
#define RMT_AFIFO_RST_0_S  23
/** RMT_CONF_UPDATE_0:WT；位位置：[24]；默认值：0；CHANNEL0的同步位
 */
#define RMT_CONF_UPDATE_0    (BIT(24))
#define RMT_CONF_UPDATE_0_M  (RMT_CONF_UPDATE_0_V << RMT_CONF_UPDATE_0_S)
#define RMT_CONF_UPDATE_0_V  0x00000001U
#define RMT_CONF_UPDATE_0_S  24

/** RMT_CH1CONF0_REG寄存器通道1配置寄存器0
 */
#define RMT_CH1CONF0_REG (DR_REG_RMT_BASE + 0x24)
/** RMT_TX_START_1:WT；位位置：[0]；默认值：0；设置此位以开始在信道1上发送数据。
 */
#define RMT_TX_START_1    (BIT(0))
#define RMT_TX_START_1_M  (RMT_TX_START_1_V << RMT_TX_START_1_S)
#define RMT_TX_START_1_V  0x00000001U
#define RMT_TX_START_1_S  0
/** RMT_MEM_RD_RST_1:WT；位位置：[1]；默认值：0；设置该位以通过访问变送器重置通道1的读ram地址。
 */
#define RMT_MEM_RD_RST_1    (BIT(1))
#define RMT_MEM_RD_RST_1_M  (RMT_MEM_RD_RST_1_V << RMT_MEM_RD_RST_1_S)
#define RMT_MEM_RD_RST_1_V  0x00000001U
#define RMT_MEM_RD_RST_1_S  1
/** RMT_APB_MEM_RST_1:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置通道1的W/R ram地址。
 */
#define RMT_APB_MEM_RST_1    (BIT(2))
#define RMT_APB_MEM_RST_1_M  (RMT_APB_MEM_RST_1_V << RMT_APB_MEM_RST_1_S)
#define RMT_APB_MEM_RST_1_V  0x00000001U
#define RMT_APB_MEM_RST_1_S  2
/** RMT_TX_CONTI_MODE_1:R/W；位位置：[3]；默认值：0；设置此位以重新开始从信道1中的第一个数据到最后一个数据的传输。
 */
#define RMT_TX_CONTI_MODE_1    (BIT(3))
#define RMT_TX_CONTI_MODE_1_M  (RMT_TX_CONTI_MODE_1_V << RMT_TX_CONTI_MODE_1_S)
#define RMT_TX_CONTI_MODE_1_V  0x00000001U
#define RMT_TX_CONTI_MODE_1_S  3
/** RMT_MEM_TX_WRAP_EN_1:R/W；位位置：[4]；默认值：0；这是环绕模式的通道1启用位：当要发送的数据超过其内存大小时，它将在开始时恢复发送。
 */
#define RMT_MEM_TX_WRAP_EN_1    (BIT(4))
#define RMT_MEM_TX_WRAP_EN_1_M  (RMT_MEM_TX_WRAP_EN_1_V << RMT_MEM_TX_WRAP_EN_1_S)
#define RMT_MEM_TX_WRAP_EN_1_V  0x00000001U
#define RMT_MEM_TX_WRAP_EN_1_S  4
/** RMT_IDLE_OUT_LV_1:R/W；位位置：[5]；默认值：0；当信道1处于空闲状态时，该位配置信道1中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_1    (BIT(5))
#define RMT_IDLE_OUT_LV_1_M  (RMT_IDLE_OUT_LV_1_V << RMT_IDLE_OUT_LV_1_S)
#define RMT_IDLE_OUT_LV_1_V  0x00000001U
#define RMT_IDLE_OUT_LV_1_S  5
/** RMT_IDLE_OUT_EN_1:R/W；位位置：[6]；默认值：0；这是处于空闲状态的信道1的输出启用控制位。
 */
#define RMT_IDLE_OUT_EN_1    (BIT(6))
#define RMT_IDLE_OUT_EN_1_M  (RMT_IDLE_OUT_EN_1_V << RMT_IDLE_OUT_EN_1_S)
#define RMT_IDLE_OUT_EN_1_V  0x00000001U
#define RMT_IDLE_OUT_EN_1_S  6
/** RMT_TX_STOP_1:R/W/SC；位位置：[7]；默认值：0；设置此位以停止信道1的发射机发送数据。
 */
#define RMT_TX_STOP_1    (BIT(7))
#define RMT_TX_STOP_1_M  (RMT_TX_STOP_1_V << RMT_TX_STOP_1_S)
#define RMT_TX_STOP_1_V  0x00000001U
#define RMT_TX_STOP_1_S  7
/** RMT_DIV_CNT_1:R/W；比特位置：[15:8]；默认值：2；该寄存器用于配置信道1时钟分频器。
 */
#define RMT_DIV_CNT_1    0x000000FFU
#define RMT_DIV_CNT_1_M  (RMT_DIV_CNT_1_V << RMT_DIV_CNT_1_S)
#define RMT_DIV_CNT_1_V  0x000000FFU
#define RMT_DIV_CNT_1_S  8
/** RMT_MEM_SIZE_1:R/W；比特位置：[19:16]；默认值：1；此寄存器用于配置分配给信道1的最大内存大小。
 */
#define RMT_MEM_SIZE_1    0x0000000FU
#define RMT_MEM_SIZE_1_M  (RMT_MEM_SIZE_1_V << RMT_MEM_SIZE_1_S)
#define RMT_MEM_SIZE_1_V  0x0000000FU
#define RMT_MEM_SIZE_1_S  16
/** RMT_CARRIER_EFF_EN_1:R/W；位位置：[20]；默认值：1；1： 仅在CHANNEL1的发送数据状态下，在输出信号上添加载波调制。0：在CHANNEL 1的所有状态下，对输出信号添加载波调制，仅在RMT_CARRIR_EN_CH1为1时有效。
 */
#define RMT_CARRIER_EFF_EN_1    (BIT(20))
#define RMT_CARRIER_EFF_EN_1_M  (RMT_CARRIER_EFF_EN_1_V << RMT_CARRIER_EFF_EN_1_S)
#define RMT_CARRIER_EFF_EN_1_V  0x00000001U
#define RMT_CARRIER_EFF_EN_1_S  20
/** RMT_CARRIER_EN_1:R/W；位位置：[21]；默认值：1；这是信道1的载波调制启用控制位。1：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_1    (BIT(21))
#define RMT_CARRIER_EN_1_M  (RMT_CARRIER_EN_1_V << RMT_CARRIER_EN_1_S)
#define RMT_CARRIER_EN_1_V  0x00000001U
#define RMT_CARRIER_EN_1_S  21
/** RMT_CARRIER_OUT_LV_1:R/W；位位置：[22]；默认值：1；该位用于配置信道1的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_1    (BIT(22))
#define RMT_CARRIER_OUT_LV_1_M  (RMT_CARRIER_OUT_LV_1_V << RMT_CARRIER_OUT_LV_1_S)
#define RMT_CARRIER_OUT_LV_1_V  0x00000001U
#define RMT_CARRIER_OUT_LV_1_S  22
/** RMT_AFIFO_RST_1:WT；位位置：[23]；默认值：0；保留
 */
#define RMT_AFIFO_RST_1    (BIT(23))
#define RMT_AFIFO_RST_1_M  (RMT_AFIFO_RST_1_V << RMT_AFIFO_RST_1_S)
#define RMT_AFIFO_RST_1_V  0x00000001U
#define RMT_AFIFO_RST_1_S  23
/** RMT_CONF_UPDATE_1:WT；位位置：[24]；默认值：0；通道1的同步位
 */
#define RMT_CONF_UPDATE_1    (BIT(24))
#define RMT_CONF_UPDATE_1_M  (RMT_CONF_UPDATE_1_V << RMT_CONF_UPDATE_1_S)
#define RMT_CONF_UPDATE_1_V  0x00000001U
#define RMT_CONF_UPDATE_1_S  24

/** RMT_CH2CONF0_REG寄存器通道2配置寄存器0
 */
#define RMT_CH2CONF0_REG (DR_REG_RMT_BASE + 0x28)
/** RMT_TX_START_2:WT；位位置：[0]；默认值：0；设置此位以开始在信道2上发送数据。
 */
#define RMT_TX_START_2    (BIT(0))
#define RMT_TX_START_2_M  (RMT_TX_START_2_V << RMT_TX_START_2_S)
#define RMT_TX_START_2_V  0x00000001U
#define RMT_TX_START_2_S  0
/** RMT_MEM_RD_RST_2:WT；位位置：[1]；默认值：0；设置此位以通过访问变送器重置通道2的读ram地址。
 */
#define RMT_MEM_RD_RST_2    (BIT(1))
#define RMT_MEM_RD_RST_2_M  (RMT_MEM_RD_RST_2_V << RMT_MEM_RD_RST_2_S)
#define RMT_MEM_RD_RST_2_V  0x00000001U
#define RMT_MEM_RD_RST_2_S  1
/** RMT_APB_MEM_rst2:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置通道2的W/R ram地址。
 */
#define RMT_APB_MEM_RST_2    (BIT(2))
#define RMT_APB_MEM_RST_2_M  (RMT_APB_MEM_RST_2_V << RMT_APB_MEM_RST_2_S)
#define RMT_APB_MEM_RST_2_V  0x00000001U
#define RMT_APB_MEM_RST_2_S  2
/** RMT_TX_CONTI_mode2:R/W；位位置：[3]；默认值：0；设置此位以重新启动信道2中从第一个数据到最后一个数据的传输。
 */
#define RMT_TX_CONTI_MODE_2    (BIT(3))
#define RMT_TX_CONTI_MODE_2_M  (RMT_TX_CONTI_MODE_2_V << RMT_TX_CONTI_MODE_2_S)
#define RMT_TX_CONTI_MODE_2_V  0x00000001U
#define RMT_TX_CONTI_MODE_2_S  3
/** RMT_MEM_TX_WRAP_en2:R/W；位位置：[4]；默认值：0；这是环绕模式的通道2启用位：当要发送的数据超过其内存大小时，它将在开始时恢复发送。
 */
#define RMT_MEM_TX_WRAP_EN_2    (BIT(4))
#define RMT_MEM_TX_WRAP_EN_2_M  (RMT_MEM_TX_WRAP_EN_2_V << RMT_MEM_TX_WRAP_EN_2_S)
#define RMT_MEM_TX_WRAP_EN_2_V  0x00000001U
#define RMT_MEM_TX_WRAP_EN_2_S  4
/** RMT_IDLE_OUT_LV_2：R/W；位位置：[5]；默认值：0；当信道2处于空闲状态时，该位配置信道2中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_2    (BIT(5))
#define RMT_IDLE_OUT_LV_2_M  (RMT_IDLE_OUT_LV_2_V << RMT_IDLE_OUT_LV_2_S)
#define RMT_IDLE_OUT_LV_2_V  0x00000001U
#define RMT_IDLE_OUT_LV_2_S  5
/** RMT_IDLE_OUT_en2:R/W；位位置：[6]；默认值：0；这是处于空闲状态的信道2的输出启用控制位。
 */
#define RMT_IDLE_OUT_EN_2    (BIT(6))
#define RMT_IDLE_OUT_EN_2_M  (RMT_IDLE_OUT_EN_2_V << RMT_IDLE_OUT_EN_2_S)
#define RMT_IDLE_OUT_EN_2_V  0x00000001U
#define RMT_IDLE_OUT_EN_2_S  6
/** RMT_TX_stop2:R/W/SC；位位置：[7]；默认值：0；设置此位以停止信道2的发射机发送数据。
 */
#define RMT_TX_STOP_2    (BIT(7))
#define RMT_TX_STOP_2_M  (RMT_TX_STOP_2_V << RMT_TX_STOP_2_S)
#define RMT_TX_STOP_2_V  0x00000001U
#define RMT_TX_STOP_2_S  7
/** RMT_DIV_CNT_2：R/W；比特位置：[15:8]；默认值：2；该寄存器用于配置信道2时钟分频器。
 */
#define RMT_DIV_CNT_2    0x000000FFU
#define RMT_DIV_CNT_2_M  (RMT_DIV_CNT_2_V << RMT_DIV_CNT_2_S)
#define RMT_DIV_CNT_2_V  0x000000FFU
#define RMT_DIV_CNT_2_S  8
/** RMT_MEM_SIZE_2：R/W；比特位置：[19:16]；默认值：1；此寄存器用于配置分配给信道2的最大内存大小。
 */
#define RMT_MEM_SIZE_2    0x0000000FU
#define RMT_MEM_SIZE_2_M  (RMT_MEM_SIZE_2_V << RMT_MEM_SIZE_2_S)
#define RMT_MEM_SIZE_2_V  0x0000000FU
#define RMT_MEM_SIZE_2_S  16
/** RMT_CARRIER_EFF_en2:R/W；位位置：[20]；默认值：1；1： 仅在CHANNEL2的发送数据状态下，在输出信号上添加载波调制。0：在CHANNEL 2的所有状态下，对输出信号添加载波调制，仅在RMT_CARRIR_EN_CH2为1时有效。
 */
#define RMT_CARRIER_EFF_EN_2    (BIT(20))
#define RMT_CARRIER_EFF_EN_2_M  (RMT_CARRIER_EFF_EN_2_V << RMT_CARRIER_EFF_EN_2_S)
#define RMT_CARRIER_EFF_EN_2_V  0x00000001U
#define RMT_CARRIER_EFF_EN_2_S  20
/** RMT_CARRIER_en2:R/W；位位置：[21]；默认值：1；这是信道2.1的载波调制启用控制位：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_2    (BIT(21))
#define RMT_CARRIER_EN_2_M  (RMT_CARRIER_EN_2_V << RMT_CARRIER_EN_2_S)
#define RMT_CARRIER_EN_2_V  0x00000001U
#define RMT_CARRIER_EN_2_S  21
/** RMT_CARRIER_OUT_LV_2:R/W；位位置：[22]；默认值：1；该位用于配置信道2的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_2    (BIT(22))
#define RMT_CARRIER_OUT_LV_2_M  (RMT_CARRIER_OUT_LV_2_V << RMT_CARRIER_OUT_LV_2_S)
#define RMT_CARRIER_OUT_LV_2_V  0x00000001U
#define RMT_CARRIER_OUT_LV_2_S  22
/** RMT_AFIFO_RST_2:WT；位位置：[23]；默认值：0；保留
 */
#define RMT_AFIFO_RST_2    (BIT(23))
#define RMT_AFIFO_RST_2_M  (RMT_AFIFO_RST_2_V << RMT_AFIFO_RST_2_S)
#define RMT_AFIFO_RST_2_V  0x00000001U
#define RMT_AFIFO_RST_2_S  23
/** RMT_CONF_UPDATE_2:WT；位位置：[24]；默认值：0；信道2的同步位
 */
#define RMT_CONF_UPDATE_2    (BIT(24))
#define RMT_CONF_UPDATE_2_M  (RMT_CONF_UPDATE_2_V << RMT_CONF_UPDATE_2_S)
#define RMT_CONF_UPDATE_2_V  0x00000001U
#define RMT_CONF_UPDATE_2_S  24

/** RMT_CH3CONF0_REG寄存器通道3配置寄存器0
 */
#define RMT_CH3CONF0_REG (DR_REG_RMT_BASE + 0x2c)
/** RMT_TX_START_3:WT；位位置：[0]；默认值：0；设置此位以开始在信道3上发送数据。
 */
#define RMT_TX_START_3    (BIT(0))
#define RMT_TX_START_3_M  (RMT_TX_START_3_V << RMT_TX_START_3_S)
#define RMT_TX_START_3_V  0x00000001U
#define RMT_TX_START_3_S  0
/** RMT_MEM_RD_RST_3:WT；位位置：[1]；默认值：0；设置该位以通过访问变送器重置通道3的读ram地址。
 */
#define RMT_MEM_RD_RST_3    (BIT(1))
#define RMT_MEM_RD_RST_3_M  (RMT_MEM_RD_RST_3_V << RMT_MEM_RD_RST_3_S)
#define RMT_MEM_RD_RST_3_V  0x00000001U
#define RMT_MEM_RD_RST_3_S  1
/** RMT_APB_MEM_RST_3:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置通道3的W/R ram地址。
 */
#define RMT_APB_MEM_RST_3    (BIT(2))
#define RMT_APB_MEM_RST_3_M  (RMT_APB_MEM_RST_3_V << RMT_APB_MEM_RST_3_S)
#define RMT_APB_MEM_RST_3_V  0x00000001U
#define RMT_APB_MEM_RST_3_S  2
/** RMT_TX_CONTI_mode3:R/W；位位置：[3]；默认值：0；设置此位以重新启动从信道3中的第一个数据到最后一个数据的传输。
 */
#define RMT_TX_CONTI_MODE_3    (BIT(3))
#define RMT_TX_CONTI_MODE_3_M  (RMT_TX_CONTI_MODE_3_V << RMT_TX_CONTI_MODE_3_S)
#define RMT_TX_CONTI_MODE_3_V  0x00000001U
#define RMT_TX_CONTI_MODE_3_S  3
/** RMT_MEM_TX_WRAP_EN_3:R/W；位位置：[4]；默认值：0；这是环绕模式的通道3启用位：当要发送的数据超过其内存大小时，它将在开始时恢复发送。
 */
#define RMT_MEM_TX_WRAP_EN_3    (BIT(4))
#define RMT_MEM_TX_WRAP_EN_3_M  (RMT_MEM_TX_WRAP_EN_3_V << RMT_MEM_TX_WRAP_EN_3_S)
#define RMT_MEM_TX_WRAP_EN_3_V  0x00000001U
#define RMT_MEM_TX_WRAP_EN_3_S  4
/** RMT_IDLE_OUT_LV_3:R/W；位位置：[5]；默认值：0；当信道3处于空闲状态时，该位配置信道3中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_3    (BIT(5))
#define RMT_IDLE_OUT_LV_3_M  (RMT_IDLE_OUT_LV_3_V << RMT_IDLE_OUT_LV_3_S)
#define RMT_IDLE_OUT_LV_3_V  0x00000001U
#define RMT_IDLE_OUT_LV_3_S  5
/** RMT_IDLE_OUT_EN_3:R/W；位位置：[6]；默认值：0；这是处于空闲状态的通道3的输出启用控制位。
 */
#define RMT_IDLE_OUT_EN_3    (BIT(6))
#define RMT_IDLE_OUT_EN_3_M  (RMT_IDLE_OUT_EN_3_V << RMT_IDLE_OUT_EN_3_S)
#define RMT_IDLE_OUT_EN_3_V  0x00000001U
#define RMT_IDLE_OUT_EN_3_S  6
/** RMT_TX_stop3:R/W/SC；位位置：[7]；默认值：0；设置此位以停止信道3的发射机发送数据。
 */
#define RMT_TX_STOP_3    (BIT(7))
#define RMT_TX_STOP_3_M  (RMT_TX_STOP_3_V << RMT_TX_STOP_3_S)
#define RMT_TX_STOP_3_V  0x00000001U
#define RMT_TX_STOP_3_S  7
/** RMT_DIV_CNT_3:R/W；比特位置：[15:8]；默认值：2；该寄存器用于配置信道3时钟分频器。
 */
#define RMT_DIV_CNT_3    0x000000FFU
#define RMT_DIV_CNT_3_M  (RMT_DIV_CNT_3_V << RMT_DIV_CNT_3_S)
#define RMT_DIV_CNT_3_V  0x000000FFU
#define RMT_DIV_CNT_3_S  8
/** RMT_MEM_SIZE_3:R/W；比特位置：[19:16]；默认值：1；此寄存器用于配置分配给信道3的最大内存大小。
 */
#define RMT_MEM_SIZE_3    0x0000000FU
#define RMT_MEM_SIZE_3_M  (RMT_MEM_SIZE_3_V << RMT_MEM_SIZE_3_S)
#define RMT_MEM_SIZE_3_V  0x0000000FU
#define RMT_MEM_SIZE_3_S  16
/** RMT_CARRIER_EFF_EN_3:R/W；位位置：[20]；默认值：1；1： 仅在信道3的发送数据状态下，在输出信号上添加载波调制。0：在信道3所有状态下，对输出信号添加载波调制，仅在RMT_CARRIR_EN_CH3为1时有效。
 */
#define RMT_CARRIER_EFF_EN_3    (BIT(20))
#define RMT_CARRIER_EFF_EN_3_M  (RMT_CARRIER_EFF_EN_3_V << RMT_CARRIER_EFF_EN_3_S)
#define RMT_CARRIER_EFF_EN_3_V  0x00000001U
#define RMT_CARRIER_EFF_EN_3_S  20
/** RMT_CARRIER_EN_3:R/W；位位置：[21]；默认值：1；这是信道3.1的载波调制启用控制位：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_3    (BIT(21))
#define RMT_CARRIER_EN_3_M  (RMT_CARRIER_EN_3_V << RMT_CARRIER_EN_3_S)
#define RMT_CARRIER_EN_3_V  0x00000001U
#define RMT_CARRIER_EN_3_S  21
/** RMT_CARRIER_OUT_LV_3:R/W；位位置：[22]；默认值：1；该位用于配置信道3的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_3    (BIT(22))
#define RMT_CARRIER_OUT_LV_3_M  (RMT_CARRIER_OUT_LV_3_V << RMT_CARRIER_OUT_LV_3_S)
#define RMT_CARRIER_OUT_LV_3_V  0x00000001U
#define RMT_CARRIER_OUT_LV_3_S  22
/** RMT_AFIFO_RST_3:WT；位位置：[23]；默认值：0；保留
 */
#define RMT_AFIFO_RST_3    (BIT(23))
#define RMT_AFIFO_RST_3_M  (RMT_AFIFO_RST_3_V << RMT_AFIFO_RST_3_S)
#define RMT_AFIFO_RST_3_V  0x00000001U
#define RMT_AFIFO_RST_3_S  23
/** RMT_CONF_UPDATE_3:WT；位位置：[24]；默认值：0；通道3的同步位
 */
#define RMT_CONF_UPDATE_3    (BIT(24))
#define RMT_CONF_UPDATE_3_M  (RMT_CONF_UPDATE_3_V << RMT_CONF_UPDATE_3_S)
#define RMT_CONF_UPDATE_3_V  0x00000001U
#define RMT_CONF_UPDATE_3_S  24

/** RMT_CH4CONF0_REG寄存器通道4配置寄存器0
 */
#define RMT_CH4CONF0_REG (DR_REG_RMT_BASE + 0x30)
/** RMT_DIV_CNT_4:R/W；位位置：[7:0]；默认值：2；该寄存器用于配置信道4时钟分频器。
 */
#define RMT_DIV_CNT_4    0x000000FFU
#define RMT_DIV_CNT_4_M  (RMT_DIV_CNT_4_V << RMT_DIV_CNT_4_S)
#define RMT_DIV_CNT_4_V  0x000000FFU
#define RMT_DIV_CNT_4_S  0
/** RMT_IDLE_THRES_4:R/W；比特位置：[22:8]；默认值：32767；当在输入信号上没有检测到边沿并且连续时钟周期长于该寄存器值时，接收过程结束。
 */
#define RMT_IDLE_THRES_4    0x00007FFFU
#define RMT_IDLE_THRES_4_M  (RMT_IDLE_THRES_4_V << RMT_IDLE_THRES_4_S)
#define RMT_IDLE_THRES_4_V  0x00007FFFU
#define RMT_IDLE_THRES_4_S  8
/** RMT_MEM_SIZE_4:R/W；位位置：[27:24]；默认值：1；此寄存器用于配置分配给信道4的最大内存大小。
 */
#define RMT_MEM_SIZE_4    0x0000000FU
#define RMT_MEM_SIZE_4_M  (RMT_MEM_SIZE_4_V << RMT_MEM_SIZE_4_S)
#define RMT_MEM_SIZE_4_V  0x0000000FU
#define RMT_MEM_SIZE_4_S  24
/** RMT_CARRIER_EN_4:R/W；位位置：[28]；默认值：1；这是信道4.1的载波调制启用控制位：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_4    (BIT(28))
#define RMT_CARRIER_EN_4_M  (RMT_CARRIER_EN_4_V << RMT_CARRIER_EN_4_S)
#define RMT_CARRIER_EN_4_V  0x00000001U
#define RMT_CARRIER_EN_4_S  28
/** RMT_CARRIER_OUT_LV_4:R/W；位位置：[29]；默认值：1；该位用于配置信道4的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_4    (BIT(29))
#define RMT_CARRIER_OUT_LV_4_M  (RMT_CARRIER_OUT_LV_4_V << RMT_CARRIER_OUT_LV_4_S)
#define RMT_CARRIER_OUT_LV_4_V  0x00000001U
#define RMT_CARRIER_OUT_LV_4_S  29

/** RMT_CH4CONF1_REG寄存器通道4配置寄存器1
 */
#define RMT_CH4CONF1_REG (DR_REG_RMT_BASE + 0x34)
/** RMT_RX_EN_4:R/W；位位置：[0]；默认值：0；设置此位以使接收器能够在信道4上接收数据。
 */
#define RMT_RX_EN_4    (BIT(0))
#define RMT_RX_EN_4_M  (RMT_RX_EN_4_V << RMT_RX_EN_4_S)
#define RMT_RX_EN_4_V  0x00000001U
#define RMT_RX_EN_4_S  0
/** RMT_MEM_WR_RST_4:WT；位位置：[1]；默认值：0；设置此位以通过访问接收器重置通道4的写ram地址。
 */
#define RMT_MEM_WR_RST_4    (BIT(1))
#define RMT_MEM_WR_RST_4_M  (RMT_MEM_WR_RST_4_V << RMT_MEM_WR_RST_4_S)
#define RMT_MEM_WR_RST_4_V  0x00000001U
#define RMT_MEM_WR_RST_4_S  1
/** RMT_APB_MEM_RST_4:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置CHANNEL4的W/R ram地址。
 */
#define RMT_APB_MEM_RST_4    (BIT(2))
#define RMT_APB_MEM_RST_4_M  (RMT_APB_MEM_RST_4_V << RMT_APB_MEM_RST_4_S)
#define RMT_APB_MEM_RST_4_V  0x00000001U
#define RMT_APB_MEM_RST_4_S  2
/** RMT_MEM_OWNER_4:R/W/SC；位位置：[3]；默认值：1；此寄存器标记CHANNEL4的ram块的所有权。
 *
 *  1’1：接收器正在使用ram。
 *
 *  1':0:APB总线正在使用ram。
 */
#define RMT_MEM_OWNER_4    (BIT(3))
#define RMT_MEM_OWNER_4_M  (RMT_MEM_OWNER_4_V << RMT_MEM_OWNER_4_S)
#define RMT_MEM_OWNER_4_V  0x00000001U
#define RMT_MEM_OWNER_4_S  3
/** RMT_RX滤波器_EN_4:R/W；位位置：[4]；默认值：0；这是信道4的接收滤波器的启用位。
 */
#define RMT_RX_FILTER_EN_4    (BIT(4))
#define RMT_RX_FILTER_EN_4_M  (RMT_RX_FILTER_EN_4_V << RMT_RX_FILTER_EN_4_S)
#define RMT_RX_FILTER_EN_4_V  0x00000001U
#define RMT_RX_FILTER_EN_4_S  4
/** RMT_RX滤波器阈值4:R/W；比特位置：[12:5]；默认值：15；在APB时钟周期（接收模式）中，当输入脉冲的宽度小于此寄存器值时，忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_4    0x000000FFU
#define RMT_RX_FILTER_THRES_4_M  (RMT_RX_FILTER_THRES_4_V << RMT_RX_FILTER_THRES_4_S)
#define RMT_RX_FILTER_THRES_4_V  0x000000FFU
#define RMT_RX_FILTER_THRES_4_S  5
/** RMT_MEM_RX_WRAP_EN_4:R/W；位位置：[13]；默认值：0；这是环绕模式的通道4启用位：当要接收的数据大于其内存大小时，它将在开始时恢复接收。
 */
#define RMT_MEM_RX_WRAP_EN_4    (BIT(13))
#define RMT_MEM_RX_WRAP_EN_4_M  (RMT_MEM_RX_WRAP_EN_4_V << RMT_MEM_RX_WRAP_EN_4_S)
#define RMT_MEM_RX_WRAP_EN_4_V  0x00000001U
#define RMT_MEM_RX_WRAP_EN_4_S  13
/** RMT_AFIFO_RST_4:WT；位位置：[14]；默认值：0；保留
 */
#define RMT_AFIFO_RST_4    (BIT(14))
#define RMT_AFIFO_RST_4_M  (RMT_AFIFO_RST_4_V << RMT_AFIFO_RST_4_S)
#define RMT_AFIFO_RST_4_V  0x00000001U
#define RMT_AFIFO_RST_4_S  14
/** RMT_CONF_UPDATE_4:WT；位位置：[15]；默认值：0；通道4的同步位
 */
#define RMT_CONF_UPDATE_4    (BIT(15))
#define RMT_CONF_UPDATE_4_M  (RMT_CONF_UPDATE_4_V << RMT_CONF_UPDATE_4_S)
#define RMT_CONF_UPDATE_4_V  0x00000001U
#define RMT_CONF_UPDATE_4_S  15

/** RMT_CH5CONF0_REG寄存器通道5配置寄存器0
 */
#define RMT_CH5CONF0_REG (DR_REG_RMT_BASE + 0x38)
/** RMT_DIV_CNT_5:R/W；位位置：[7:0]；默认值：2；该寄存器用于配置信道5时钟分频器。
 */
#define RMT_DIV_CNT_5    0x000000FFU
#define RMT_DIV_CNT_5_M  (RMT_DIV_CNT_5_V << RMT_DIV_CNT_5_S)
#define RMT_DIV_CNT_5_V  0x000000FFU
#define RMT_DIV_CNT_5_S  0
/** RMT_IDLE_THRES_5:R/W；比特位置：[22:8]；默认值：32767；当在输入信号上没有检测到边沿并且连续时钟周期长于该寄存器值时，接收过程结束。
 */
#define RMT_IDLE_THRES_5    0x00007FFFU
#define RMT_IDLE_THRES_5_M  (RMT_IDLE_THRES_5_V << RMT_IDLE_THRES_5_S)
#define RMT_IDLE_THRES_5_V  0x00007FFFU
#define RMT_IDLE_THRES_5_S  8
/** RMT_MEM_SIZE_5:R/W；位位置：[27:24]；默认值：1；此寄存器用于配置分配给通道5的最大内存大小。
 */
#define RMT_MEM_SIZE_5    0x0000000FU
#define RMT_MEM_SIZE_5_M  (RMT_MEM_SIZE_5_V << RMT_MEM_SIZE_5_S)
#define RMT_MEM_SIZE_5_V  0x0000000FU
#define RMT_MEM_SIZE_5_S  24
/** RMT_CARRIER_EN_5:R/W；位位置：[28]；默认值：1；这是信道5.1的载波调制启用控制位：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_5    (BIT(28))
#define RMT_CARRIER_EN_5_M  (RMT_CARRIER_EN_5_V << RMT_CARRIER_EN_5_S)
#define RMT_CARRIER_EN_5_V  0x00000001U
#define RMT_CARRIER_EN_5_S  28
/** RMT_CARRIER_OUT_LV_5:R/W；位位置：[29]；默认值：1；该位用于配置信道5的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_5    (BIT(29))
#define RMT_CARRIER_OUT_LV_5_M  (RMT_CARRIER_OUT_LV_5_V << RMT_CARRIER_OUT_LV_5_S)
#define RMT_CARRIER_OUT_LV_5_V  0x00000001U
#define RMT_CARRIER_OUT_LV_5_S  29

/** RMT_CH5CONF1_REG寄存器通道5配置寄存器1
 */
#define RMT_CH5CONF1_REG (DR_REG_RMT_BASE + 0x3c)
/** RMT_RX_EN_5:R/W；位位置：[0]；默认值：0；设置此位以使接收器能够在信道5上接收数据。
 */
#define RMT_RX_EN_5    (BIT(0))
#define RMT_RX_EN_5_M  (RMT_RX_EN_5_V << RMT_RX_EN_5_S)
#define RMT_RX_EN_5_V  0x00000001U
#define RMT_RX_EN_5_S  0
/** RMT_MEM_WR_RST_5:WT；位位置：[1]；默认值：0；设置此位以通过访问接收器重置通道5的写ram地址。
 */
#define RMT_MEM_WR_RST_5    (BIT(1))
#define RMT_MEM_WR_RST_5_M  (RMT_MEM_WR_RST_5_V << RMT_MEM_WR_RST_5_S)
#define RMT_MEM_WR_RST_5_V  0x00000001U
#define RMT_MEM_WR_RST_5_S  1
/** RMT_APB_MEM_RST_5:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置通道5的W/R ram地址。
 */
#define RMT_APB_MEM_RST_5    (BIT(2))
#define RMT_APB_MEM_RST_5_M  (RMT_APB_MEM_RST_5_V << RMT_APB_MEM_RST_5_S)
#define RMT_APB_MEM_RST_5_V  0x00000001U
#define RMT_APB_MEM_RST_5_S  2
/** RMT_MEM_OWNER_5:R/W/SC；位位置：[3]；默认值：1；此寄存器标记CHANNEL5的ram块的所有权。
 *
 *  1’1：接收器正在使用ram。
 *
 *  1':0:APB总线正在使用ram。
 */
#define RMT_MEM_OWNER_5    (BIT(3))
#define RMT_MEM_OWNER_5_M  (RMT_MEM_OWNER_5_V << RMT_MEM_OWNER_5_S)
#define RMT_MEM_OWNER_5_V  0x00000001U
#define RMT_MEM_OWNER_5_S  3
/** RMT_RX滤波器_EN_5:R/W；位位置：[4]；默认值：0；这是信道5的接收滤波器的启用位。
 */
#define RMT_RX_FILTER_EN_5    (BIT(4))
#define RMT_RX_FILTER_EN_5_M  (RMT_RX_FILTER_EN_5_V << RMT_RX_FILTER_EN_5_S)
#define RMT_RX_FILTER_EN_5_V  0x00000001U
#define RMT_RX_FILTER_EN_5_S  4
/** RMT_RX滤波器阈值5:R/W；比特位置：[12:5]；默认值：15；在APB时钟周期（接收模式）中，当输入脉冲的宽度小于此寄存器值时，忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_5    0x000000FFU
#define RMT_RX_FILTER_THRES_5_M  (RMT_RX_FILTER_THRES_5_V << RMT_RX_FILTER_THRES_5_S)
#define RMT_RX_FILTER_THRES_5_V  0x000000FFU
#define RMT_RX_FILTER_THRES_5_S  5
/** RMT_MEM_RX_WRAP_EN_5:R/W；位位置：[13]；默认值：0；这是环绕模式的通道5启用位：当要接收的数据大于其内存大小时，它将在开始时恢复接收。
 */
#define RMT_MEM_RX_WRAP_EN_5    (BIT(13))
#define RMT_MEM_RX_WRAP_EN_5_M  (RMT_MEM_RX_WRAP_EN_5_V << RMT_MEM_RX_WRAP_EN_5_S)
#define RMT_MEM_RX_WRAP_EN_5_V  0x00000001U
#define RMT_MEM_RX_WRAP_EN_5_S  13
/** RMT_AFIFO_RST_5:WT；位位置：[14]；默认值：0；保留
 */
#define RMT_AFIFO_RST_5    (BIT(14))
#define RMT_AFIFO_RST_5_M  (RMT_AFIFO_RST_5_V << RMT_AFIFO_RST_5_S)
#define RMT_AFIFO_RST_5_V  0x00000001U
#define RMT_AFIFO_RST_5_S  14
/** RMT_CONF_UPDATE_5:WT；位位置：[15]；默认值：0；通道5的同步位
 */
#define RMT_CONF_UPDATE_5    (BIT(15))
#define RMT_CONF_UPDATE_5_M  (RMT_CONF_UPDATE_5_V << RMT_CONF_UPDATE_5_S)
#define RMT_CONF_UPDATE_5_V  0x00000001U
#define RMT_CONF_UPDATE_5_S  15

/** RMT_CH6CONF0_REG寄存器通道6配置寄存器0
 */
#define RMT_CH6CONF0_REG (DR_REG_RMT_BASE + 0x40)
/** RMT_DIV_CNT_6:R/W；位位置：[7:0]；默认值：2；该寄存器用于配置信道6时钟分频器。
 */
#define RMT_DIV_CNT_6    0x000000FFU
#define RMT_DIV_CNT_6_M  (RMT_DIV_CNT_6_V << RMT_DIV_CNT_6_S)
#define RMT_DIV_CNT_6_V  0x000000FFU
#define RMT_DIV_CNT_6_S  0
/** RMT_IDLE_THRES_6:R/W；比特位置：[22:8]；默认值：32767；当在输入信号上没有检测到边沿并且连续时钟周期长于该寄存器值时，接收过程结束。
 */
#define RMT_IDLE_THRES_6    0x00007FFFU
#define RMT_IDLE_THRES_6_M  (RMT_IDLE_THRES_6_V << RMT_IDLE_THRES_6_S)
#define RMT_IDLE_THRES_6_V  0x00007FFFU
#define RMT_IDLE_THRES_6_S  8
/** RMT_MEM_SIZE_6:R/W；位位置：[27:24]；默认值：1；此寄存器用于配置分配给通道6的最大内存大小。
 */
#define RMT_MEM_SIZE_6    0x0000000FU
#define RMT_MEM_SIZE_6_M  (RMT_MEM_SIZE_6_V << RMT_MEM_SIZE_6_S)
#define RMT_MEM_SIZE_6_V  0x0000000FU
#define RMT_MEM_SIZE_6_S  24
/** RMT_CARRIER_EN_6:R/W；位位置：[28]；默认值：1；这是信道6.1的载波调制启用控制位：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_6    (BIT(28))
#define RMT_CARRIER_EN_6_M  (RMT_CARRIER_EN_6_V << RMT_CARRIER_EN_6_S)
#define RMT_CARRIER_EN_6_V  0x00000001U
#define RMT_CARRIER_EN_6_S  28
/** RMT_CARRIER_OUT_LV_6:R/W；位位置：[29]；默认值：1；该位用于配置信道6的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_6    (BIT(29))
#define RMT_CARRIER_OUT_LV_6_M  (RMT_CARRIER_OUT_LV_6_V << RMT_CARRIER_OUT_LV_6_S)
#define RMT_CARRIER_OUT_LV_6_V  0x00000001U
#define RMT_CARRIER_OUT_LV_6_S  29

/** RMT_CH6CONF1_REG寄存器通道6配置寄存器1
 */
#define RMT_CH6CONF1_REG (DR_REG_RMT_BASE + 0x44)
/** RMT_RX_EN_6:R/W；位位置：[0]；默认值：0；设置此位以使接收器能够在信道6上接收数据。
 */
#define RMT_RX_EN_6    (BIT(0))
#define RMT_RX_EN_6_M  (RMT_RX_EN_6_V << RMT_RX_EN_6_S)
#define RMT_RX_EN_6_V  0x00000001U
#define RMT_RX_EN_6_S  0
/** RMT_MEM_WR_RST_6:WT；位位置：[1]；默认值：0；设置此位以通过访问接收器重置通道6的写ram地址。
 */
#define RMT_MEM_WR_RST_6    (BIT(1))
#define RMT_MEM_WR_RST_6_M  (RMT_MEM_WR_RST_6_V << RMT_MEM_WR_RST_6_S)
#define RMT_MEM_WR_RST_6_V  0x00000001U
#define RMT_MEM_WR_RST_6_S  1
/** RMT_APB_MEM_RST_6:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置通道6的W/R ram地址。
 */
#define RMT_APB_MEM_RST_6    (BIT(2))
#define RMT_APB_MEM_RST_6_M  (RMT_APB_MEM_RST_6_V << RMT_APB_MEM_RST_6_S)
#define RMT_APB_MEM_RST_6_V  0x00000001U
#define RMT_APB_MEM_RST_6_S  2
/** RMT_MEM_OWNER_6:R/W/SC；位位置：[3]；默认值：1；此寄存器标记CHANNEL6的ram块的所有权。
 *
 *  1’1：接收器正在使用ram。
 *
 *  1':0:APB总线正在使用ram。
 */
#define RMT_MEM_OWNER_6    (BIT(3))
#define RMT_MEM_OWNER_6_M  (RMT_MEM_OWNER_6_V << RMT_MEM_OWNER_6_S)
#define RMT_MEM_OWNER_6_V  0x00000001U
#define RMT_MEM_OWNER_6_S  3
/** RMT_RX滤波器_EN_6:R/W；位位置：[4]；默认值：0；这是信道6的接收滤波器的启用位。
 */
#define RMT_RX_FILTER_EN_6    (BIT(4))
#define RMT_RX_FILTER_EN_6_M  (RMT_RX_FILTER_EN_6_V << RMT_RX_FILTER_EN_6_S)
#define RMT_RX_FILTER_EN_6_V  0x00000001U
#define RMT_RX_FILTER_EN_6_S  4
/** RMT_RX滤波器阈值6:R/W；比特位置：[12:5]；默认值：15；在APB时钟周期（接收模式）中，当输入脉冲的宽度小于此寄存器值时，忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_6    0x000000FFU
#define RMT_RX_FILTER_THRES_6_M  (RMT_RX_FILTER_THRES_6_V << RMT_RX_FILTER_THRES_6_S)
#define RMT_RX_FILTER_THRES_6_V  0x000000FFU
#define RMT_RX_FILTER_THRES_6_S  5
/** RMT_MEM_RX_WRAP_EN_6:R/W；位位置：[13]；默认值：0；这是环绕模式的通道6启用位：当要接收的数据大于其内存大小时，它将在开始时恢复接收。
 */
#define RMT_MEM_RX_WRAP_EN_6    (BIT(13))
#define RMT_MEM_RX_WRAP_EN_6_M  (RMT_MEM_RX_WRAP_EN_6_V << RMT_MEM_RX_WRAP_EN_6_S)
#define RMT_MEM_RX_WRAP_EN_6_V  0x00000001U
#define RMT_MEM_RX_WRAP_EN_6_S  13
/** RMT_AFIFO_RST_6:WT；位位置：[14]；默认值：0；保留
 */
#define RMT_AFIFO_RST_6    (BIT(14))
#define RMT_AFIFO_RST_6_M  (RMT_AFIFO_RST_6_V << RMT_AFIFO_RST_6_S)
#define RMT_AFIFO_RST_6_V  0x00000001U
#define RMT_AFIFO_RST_6_S  14
/** RMT_CONF_UPDATE_6:WT；位位置：[15]；默认值：0；通道6的同步位
 */
#define RMT_CONF_UPDATE_6    (BIT(15))
#define RMT_CONF_UPDATE_6_M  (RMT_CONF_UPDATE_6_V << RMT_CONF_UPDATE_6_S)
#define RMT_CONF_UPDATE_6_V  0x00000001U
#define RMT_CONF_UPDATE_6_S  15

/** RMT_CH7CONF0_REG寄存器通道7配置寄存器0
 */
#define RMT_CH7CONF0_REG (DR_REG_RMT_BASE + 0x48)
/** RMT_DIV_CNT_7:R/W；位位置：[7:0]；默认值：2；该寄存器用于配置信道7时钟的除法器。
 */
#define RMT_DIV_CNT_7    0x000000FFU
#define RMT_DIV_CNT_7_M  (RMT_DIV_CNT_7_V << RMT_DIV_CNT_7_S)
#define RMT_DIV_CNT_7_V  0x000000FFU
#define RMT_DIV_CNT_7_S  0
/** RMT_IDLE_THRES_7:R/W；比特位置：[22:8]；默认值：32767；当在输入信号上没有检测到边沿并且连续时钟周期长于该寄存器值时，接收过程结束。
 */
#define RMT_IDLE_THRES_7    0x00007FFFU
#define RMT_IDLE_THRES_7_M  (RMT_IDLE_THRES_7_V << RMT_IDLE_THRES_7_S)
#define RMT_IDLE_THRES_7_V  0x00007FFFU
#define RMT_IDLE_THRES_7_S  8
/** RMT_MEM_SIZE_7:R/W；位位置：[27:24]；默认值：1；此寄存器用于配置分配给通道7的最大内存大小。
 */
#define RMT_MEM_SIZE_7    0x0000000FU
#define RMT_MEM_SIZE_7_M  (RMT_MEM_SIZE_7_V << RMT_MEM_SIZE_7_S)
#define RMT_MEM_SIZE_7_V  0x0000000FU
#define RMT_MEM_SIZE_7_S  24
/** RMT_CARRIER_EN_7:R/W；位位置：[28]；默认值：1；这是信道7.1的载波调制启用控制位：在输出信号中添加载波调制。0：sig_out中无载波调制。
 */
#define RMT_CARRIER_EN_7    (BIT(28))
#define RMT_CARRIER_EN_7_M  (RMT_CARRIER_EN_7_V << RMT_CARRIER_EN_7_S)
#define RMT_CARRIER_EN_7_V  0x00000001U
#define RMT_CARRIER_EN_7_S  28
/** RMT_CARRIER_OUT_LV_7:R/W；位位置：[29]；默认值：1；该位用于配置信道7的载波位置。
 *
 *  1’0：在低电平上添加载波。
 *
 *  1’h1：在高电平上添加载波。
 */
#define RMT_CARRIER_OUT_LV_7    (BIT(29))
#define RMT_CARRIER_OUT_LV_7_M  (RMT_CARRIER_OUT_LV_7_V << RMT_CARRIER_OUT_LV_7_S)
#define RMT_CARRIER_OUT_LV_7_V  0x00000001U
#define RMT_CARRIER_OUT_LV_7_S  29

/** RMT_CH7CONF1_REG寄存器通道7配置寄存器1
 */
#define RMT_CH7CONF1_REG (DR_REG_RMT_BASE + 0x4c)
/** RMT_RX_EN_7:R/W；位位置：[0]；默认值：0；设置此位以使接收器能够在信道7上接收数据。
 */
#define RMT_RX_EN_7    (BIT(0))
#define RMT_RX_EN_7_M  (RMT_RX_EN_7_V << RMT_RX_EN_7_S)
#define RMT_RX_EN_7_V  0x00000001U
#define RMT_RX_EN_7_S  0
/** RMT_MEM_WR_RST_7:WT；位位置：[1]；默认值：0；设置此位以通过访问接收器重置通道7的写ram地址。
 */
#define RMT_MEM_WR_RST_7    (BIT(1))
#define RMT_MEM_WR_RST_7_M  (RMT_MEM_WR_RST_7_V << RMT_MEM_WR_RST_7_S)
#define RMT_MEM_WR_RST_7_V  0x00000001U
#define RMT_MEM_WR_RST_7_S  1
/** RMT_APB_MEM_RST_7:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置通道7的W/R ram地址。
 */
#define RMT_APB_MEM_RST_7    (BIT(2))
#define RMT_APB_MEM_RST_7_M  (RMT_APB_MEM_RST_7_V << RMT_APB_MEM_RST_7_S)
#define RMT_APB_MEM_RST_7_V  0x00000001U
#define RMT_APB_MEM_RST_7_S  2
/** RMT_MEM_OWNER_7:R/W/SC；位位置：[3]；默认值：1；此寄存器标记CHANNEL7的ram块的所有权。
 *
 *  1’1：接收器正在使用ram。
 *
 *  1':0:APB总线正在使用ram。
 */
#define RMT_MEM_OWNER_7    (BIT(3))
#define RMT_MEM_OWNER_7_M  (RMT_MEM_OWNER_7_V << RMT_MEM_OWNER_7_S)
#define RMT_MEM_OWNER_7_V  0x00000001U
#define RMT_MEM_OWNER_7_S  3
/** RMT_RX滤波器_EN_7:R/W；位位置：[4]；默认值：0；这是信道7的接收滤波器的启用位。
 */
#define RMT_RX_FILTER_EN_7    (BIT(4))
#define RMT_RX_FILTER_EN_7_M  (RMT_RX_FILTER_EN_7_V << RMT_RX_FILTER_EN_7_S)
#define RMT_RX_FILTER_EN_7_V  0x00000001U
#define RMT_RX_FILTER_EN_7_S  4
/** RMT_RX滤波器阈值7:R/W；比特位置：[12:5]；默认值：15；在APB时钟周期（接收模式）中，当输入脉冲的宽度小于此寄存器值时，忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_7    0x000000FFU
#define RMT_RX_FILTER_THRES_7_M  (RMT_RX_FILTER_THRES_7_V << RMT_RX_FILTER_THRES_7_S)
#define RMT_RX_FILTER_THRES_7_V  0x000000FFU
#define RMT_RX_FILTER_THRES_7_S  5
/** RMT_MEM_RX_WRAP_EN_7:R/W；位位置：[13]；默认值：0；这是环绕模式的通道7启用位：当要接收的数据大于其内存大小时，它将在开始时恢复接收。
 */
#define RMT_MEM_RX_WRAP_EN_7    (BIT(13))
#define RMT_MEM_RX_WRAP_EN_7_M  (RMT_MEM_RX_WRAP_EN_7_V << RMT_MEM_RX_WRAP_EN_7_S)
#define RMT_MEM_RX_WRAP_EN_7_V  0x00000001U
#define RMT_MEM_RX_WRAP_EN_7_S  13
/** RMT_AFIFO_RST_7:WT；位位置：[14]；默认值：0；保留
 */
#define RMT_AFIFO_RST_7    (BIT(14))
#define RMT_AFIFO_RST_7_M  (RMT_AFIFO_RST_7_V << RMT_AFIFO_RST_7_S)
#define RMT_AFIFO_RST_7_V  0x00000001U
#define RMT_AFIFO_RST_7_S  14
/** RMT_CONF_UPDATE_7:WT；位位置：[15]；默认值：0；通道7的同步位
 */
#define RMT_CONF_UPDATE_7    (BIT(15))
#define RMT_CONF_UPDATE_7_M  (RMT_CONF_UPDATE_7_V << RMT_CONF_UPDATE_7_S)
#define RMT_CONF_UPDATE_7_V  0x00000001U
#define RMT_CONF_UPDATE_7_S  15

/** RMT_CH0STATUS_REG寄存器通道0状态寄存器
 */
#define RMT_CH0STATUS_REG (DR_REG_RMT_BASE + 0x50)
/** RMT_MEM_RADDR_EX_0:RO；位位置：[9:0]；默认值：0；当信道0的发射机使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_0    0x000003FFU
#define RMT_MEM_RADDR_EX_0_M  (RMT_MEM_RADDR_EX_0_V << RMT_MEM_RADDR_EX_0_S)
#define RMT_MEM_RADDR_EX_0_V  0x000003FFU
#define RMT_MEM_RADDR_EX_0_S  0
/** RMT_APB_MEM_WADDR_0:RO；比特位置：[20:11]；默认值：0；当通过APB总线写入RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_0    0x000003FFU
#define RMT_APB_MEM_WADDR_0_M  (RMT_APB_MEM_WADDR_0_V << RMT_APB_MEM_WADDR_0_S)
#define RMT_APB_MEM_WADDR_0_V  0x000003FFU
#define RMT_APB_MEM_WADDR_0_S  11
/** RMT_STATE_0:RO；位位置：[24:22]；默认值：0；此寄存器记录CHANNEL0的FSM状态。
 */
#define RMT_STATE_0    0x00000007U
#define RMT_STATE_0_M  (RMT_STATE_0_V << RMT_STATE_0_S)
#define RMT_STATE_0_V  0x00000007U
#define RMT_STATE_0_S  22
/** RMT_MEM_EMPTY_0:RO；位位置：[25]；默认值：0；当要设置的数据大于内存大小并且禁用环绕模式时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_0    (BIT(25))
#define RMT_MEM_EMPTY_0_M  (RMT_MEM_EMPTY_0_V << RMT_MEM_EMPTY_0_S)
#define RMT_MEM_EMPTY_0_V  0x00000001U
#define RMT_MEM_EMPTY_0_S  25
/** RMT_APB_MEM_WR_ERR_0:RO；位位置：[26]；默认值：0；当通过APB总线写入时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_0    (BIT(26))
#define RMT_APB_MEM_WR_ERR_0_M  (RMT_APB_MEM_WR_ERR_0_V << RMT_APB_MEM_WR_ERR_0_S)
#define RMT_APB_MEM_WR_ERR_0_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_0_S  26

/** RMT_CH1STATUS_REG寄存器通道1状态寄存器
 */
#define RMT_CH1STATUS_REG (DR_REG_RMT_BASE + 0x54)
/** RMT_MEM_RADDR_EX_1:RO；位位置：[9:0]；默认值：0；当信道1的发射机使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_1    0x000003FFU
#define RMT_MEM_RADDR_EX_1_M  (RMT_MEM_RADDR_EX_1_V << RMT_MEM_RADDR_EX_1_S)
#define RMT_MEM_RADDR_EX_1_V  0x000003FFU
#define RMT_MEM_RADDR_EX_1_S  0
/** RMT_APB_MEM_WADDR_1:RO；比特位置：[20:11]；默认值：0；当通过APB总线写入RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_1    0x000003FFU
#define RMT_APB_MEM_WADDR_1_M  (RMT_APB_MEM_WADDR_1_V << RMT_APB_MEM_WADDR_1_S)
#define RMT_APB_MEM_WADDR_1_V  0x000003FFU
#define RMT_APB_MEM_WADDR_1_S  11
/** RMT_STATE_1:RO；位位置：[24:22]；默认值：0；此寄存器记录信道1的FSM状态。
 */
#define RMT_STATE_1    0x00000007U
#define RMT_STATE_1_M  (RMT_STATE_1_V << RMT_STATE_1_S)
#define RMT_STATE_1_V  0x00000007U
#define RMT_STATE_1_S  22
/** RMT_MEM_EMPTY_1:RO；位位置：[25]；默认值：0；当要设置的数据大于内存大小并且禁用环绕模式时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_1    (BIT(25))
#define RMT_MEM_EMPTY_1_M  (RMT_MEM_EMPTY_1_V << RMT_MEM_EMPTY_1_S)
#define RMT_MEM_EMPTY_1_V  0x00000001U
#define RMT_MEM_EMPTY_1_S  25
/** RMT_APB_MEM_WR_ERR_1:RO；位位置：[26]；默认值：0；当通过APB总线写入时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_1    (BIT(26))
#define RMT_APB_MEM_WR_ERR_1_M  (RMT_APB_MEM_WR_ERR_1_V << RMT_APB_MEM_WR_ERR_1_S)
#define RMT_APB_MEM_WR_ERR_1_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_1_S  26

/** RMT_CH2STATUS_REG寄存器通道2状态寄存器
 */
#define RMT_CH2STATUS_REG (DR_REG_RMT_BASE + 0x58)
/** RMT_MEM_RADDR_EX_2:RO；位位置：[9:0]；默认值：0；当信道2的发射机使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_2    0x000003FFU
#define RMT_MEM_RADDR_EX_2_M  (RMT_MEM_RADDR_EX_2_V << RMT_MEM_RADDR_EX_2_S)
#define RMT_MEM_RADDR_EX_2_V  0x000003FFU
#define RMT_MEM_RADDR_EX_2_S  0
/** RMT_APB_MEM_waddr2:RO；比特位置：[20:11]；默认值：0；当通过APB总线写入RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_2    0x000003FFU
#define RMT_APB_MEM_WADDR_2_M  (RMT_APB_MEM_WADDR_2_V << RMT_APB_MEM_WADDR_2_S)
#define RMT_APB_MEM_WADDR_2_V  0x000003FFU
#define RMT_APB_MEM_WADDR_2_S  11
/** RMT_state2:RO；位位置：[24:22]；默认值：0；此寄存器记录信道2的FSM状态。
 */
#define RMT_STATE_2    0x00000007U
#define RMT_STATE_2_M  (RMT_STATE_2_V << RMT_STATE_2_S)
#define RMT_STATE_2_V  0x00000007U
#define RMT_STATE_2_S  22
/** RMT_MEM_EMPTY_2:RO；位位置：[25]；默认值：0；当要设置的数据大于内存大小并且禁用环绕模式时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_2    (BIT(25))
#define RMT_MEM_EMPTY_2_M  (RMT_MEM_EMPTY_2_V << RMT_MEM_EMPTY_2_S)
#define RMT_MEM_EMPTY_2_V  0x00000001U
#define RMT_MEM_EMPTY_2_S  25
/** RMT_APB_MEM_WR_ERR_2:RO；位位置：[26]；默认值：0；当通过APB总线写入时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_2    (BIT(26))
#define RMT_APB_MEM_WR_ERR_2_M  (RMT_APB_MEM_WR_ERR_2_V << RMT_APB_MEM_WR_ERR_2_S)
#define RMT_APB_MEM_WR_ERR_2_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_2_S  26

/** RMT_CH3STATUS_REG寄存器通道3状态寄存器
 */
#define RMT_CH3STATUS_REG (DR_REG_RMT_BASE + 0x5c)
/** RMT_MEM_RADDR_EX_3:RO；位位置：[9:0]；默认值：0；当信道3的发射机使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_3    0x000003FFU
#define RMT_MEM_RADDR_EX_3_M  (RMT_MEM_RADDR_EX_3_V << RMT_MEM_RADDR_EX_3_S)
#define RMT_MEM_RADDR_EX_3_V  0x000003FFU
#define RMT_MEM_RADDR_EX_3_S  0
/** RMT_APB_MEM_WADDR_3:RO；比特位置：[20:11]；默认值：0；当通过APB总线写入RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_3    0x000003FFU
#define RMT_APB_MEM_WADDR_3_M  (RMT_APB_MEM_WADDR_3_V << RMT_APB_MEM_WADDR_3_S)
#define RMT_APB_MEM_WADDR_3_V  0x000003FFU
#define RMT_APB_MEM_WADDR_3_S  11
/** RMT_STATE_3:RO；位位置：[24:22]；默认值：0；此寄存器记录通道3的FSM状态。
 */
#define RMT_STATE_3    0x00000007U
#define RMT_STATE_3_M  (RMT_STATE_3_V << RMT_STATE_3_S)
#define RMT_STATE_3_V  0x00000007U
#define RMT_STATE_3_S  22
/** RMT_MEM_EMPTY_3:RO；位位置：[25]；默认值：0；当要设置的数据大于内存大小并且禁用环绕模式时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_3    (BIT(25))
#define RMT_MEM_EMPTY_3_M  (RMT_MEM_EMPTY_3_V << RMT_MEM_EMPTY_3_S)
#define RMT_MEM_EMPTY_3_V  0x00000001U
#define RMT_MEM_EMPTY_3_S  25
/** RMT_APB_MEM_WR_ERR_3:RO；位位置：[26]；默认值：0；当通过APB总线写入时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_3    (BIT(26))
#define RMT_APB_MEM_WR_ERR_3_M  (RMT_APB_MEM_WR_ERR_3_V << RMT_APB_MEM_WR_ERR_3_S)
#define RMT_APB_MEM_WR_ERR_3_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_3_S  26

/** RMT_CH4STATUS_REG寄存器通道4状态寄存器
 */
#define RMT_CH4STATUS_REG (DR_REG_RMT_BASE + 0x60)
/** RMT_MEM_WADDR_EX_4:RO；位位置：[9:0]；默认值：192；当信道4的接收器使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_4    0x000003FFU
#define RMT_MEM_WADDR_EX_4_M  (RMT_MEM_WADDR_EX_4_V << RMT_MEM_WADDR_EX_4_S)
#define RMT_MEM_WADDR_EX_4_V  0x000003FFU
#define RMT_MEM_WADDR_EX_4_S  0
/** RMT_APB_MEM_RADDR_4:RO；比特位置：[20:11]；默认值：192；当通过APB总线读取RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_4    0x000003FFU
#define RMT_APB_MEM_RADDR_4_M  (RMT_APB_MEM_RADDR_4_V << RMT_APB_MEM_RADDR_4_S)
#define RMT_APB_MEM_RADDR_4_V  0x000003FFU
#define RMT_APB_MEM_RADDR_4_S  11
/** RMT_STATE_4:RO；位位置：[24:22]；默认值：0；该寄存器记录信道4的FSM状态。
 */
#define RMT_STATE_4    0x00000007U
#define RMT_STATE_4_M  (RMT_STATE_4_V << RMT_STATE_4_S)
#define RMT_STATE_4_V  0x00000007U
#define RMT_STATE_4_S  22
/** RMT_MEM_OWNER_ERR_4:RO；位位置：[25]；默认值：0；当内存块的所有权错误时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_4    (BIT(25))
#define RMT_MEM_OWNER_ERR_4_M  (RMT_MEM_OWNER_ERR_4_V << RMT_MEM_OWNER_ERR_4_S)
#define RMT_MEM_OWNER_ERR_4_V  0x00000001U
#define RMT_MEM_OWNER_ERR_4_S  25
/** RMT_MEM_FULL_4:RO；位位置：[26]；默认值：0；如果接收器接收到的数据超过内存大小，则设置此状态位。
 */
#define RMT_MEM_FULL_4    (BIT(26))
#define RMT_MEM_FULL_4_M  (RMT_MEM_FULL_4_V << RMT_MEM_FULL_4_S)
#define RMT_MEM_FULL_4_V  0x00000001U
#define RMT_MEM_FULL_4_S  26
/** RMT_APB_MEM_RD_ERR_4:RO；位位置：[27]；默认值：0；当通过APB总线读取时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_4    (BIT(27))
#define RMT_APB_MEM_RD_ERR_4_M  (RMT_APB_MEM_RD_ERR_4_V << RMT_APB_MEM_RD_ERR_4_S)
#define RMT_APB_MEM_RD_ERR_4_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_4_S  27

/** RMT_CH5STATUS_REG寄存器通道5状态寄存器
 */
#define RMT_CH5STATUS_REG (DR_REG_RMT_BASE + 0x64)
/** RMT_MEM_WADDR_EX_5:RO；位位置：[9:0]；默认值：192；当信道5的接收器使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_5    0x000003FFU
#define RMT_MEM_WADDR_EX_5_M  (RMT_MEM_WADDR_EX_5_V << RMT_MEM_WADDR_EX_5_S)
#define RMT_MEM_WADDR_EX_5_V  0x000003FFU
#define RMT_MEM_WADDR_EX_5_S  0
/** RMT_APB_MEM_RADDR_5:RO；比特位置：[20:11]；默认值：192；当通过APB总线读取RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_5    0x000003FFU
#define RMT_APB_MEM_RADDR_5_M  (RMT_APB_MEM_RADDR_5_V << RMT_APB_MEM_RADDR_5_S)
#define RMT_APB_MEM_RADDR_5_V  0x000003FFU
#define RMT_APB_MEM_RADDR_5_S  11
/** RMT_STATE_5:RO；位位置：[24:22]；默认值：0；该寄存器记录通道5的FSM状态。
 */
#define RMT_STATE_5    0x00000007U
#define RMT_STATE_5_M  (RMT_STATE_5_V << RMT_STATE_5_S)
#define RMT_STATE_5_V  0x00000007U
#define RMT_STATE_5_S  22
/** RMT_MEM_OWNER_ERR_5:RO；位位置：[25]；默认值：0；当内存块的所有权错误时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_5    (BIT(25))
#define RMT_MEM_OWNER_ERR_5_M  (RMT_MEM_OWNER_ERR_5_V << RMT_MEM_OWNER_ERR_5_S)
#define RMT_MEM_OWNER_ERR_5_V  0x00000001U
#define RMT_MEM_OWNER_ERR_5_S  25
/** RMT_MEM_FULL_5:RO；位位置：[26]；默认值：0；如果接收器接收到的数据超过内存大小，则设置此状态位。
 */
#define RMT_MEM_FULL_5    (BIT(26))
#define RMT_MEM_FULL_5_M  (RMT_MEM_FULL_5_V << RMT_MEM_FULL_5_S)
#define RMT_MEM_FULL_5_V  0x00000001U
#define RMT_MEM_FULL_5_S  26
/** RMT_APB_MEM_RD_ERR_5:RO；位位置：[27]；默认值：0；当通过APB总线读取时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_5    (BIT(27))
#define RMT_APB_MEM_RD_ERR_5_M  (RMT_APB_MEM_RD_ERR_5_V << RMT_APB_MEM_RD_ERR_5_S)
#define RMT_APB_MEM_RD_ERR_5_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_5_S  27

/** RMT_CH6STATUS_REG寄存器通道6状态寄存器
 */
#define RMT_CH6STATUS_REG (DR_REG_RMT_BASE + 0x68)
/** RMT_MEM_WADDR_EX_6:RO；位位置：[9:0]；默认值：192；当信道6的接收器使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_6    0x000003FFU
#define RMT_MEM_WADDR_EX_6_M  (RMT_MEM_WADDR_EX_6_V << RMT_MEM_WADDR_EX_6_S)
#define RMT_MEM_WADDR_EX_6_V  0x000003FFU
#define RMT_MEM_WADDR_EX_6_S  0
/** RMT_APB_MEM_RADDR_6:RO；比特位置：[20:11]；默认值：192；当通过APB总线读取RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_6    0x000003FFU
#define RMT_APB_MEM_RADDR_6_M  (RMT_APB_MEM_RADDR_6_V << RMT_APB_MEM_RADDR_6_S)
#define RMT_APB_MEM_RADDR_6_V  0x000003FFU
#define RMT_APB_MEM_RADDR_6_S  11
/** RMT_STATE_6:RO；位位置：[24:22]；默认值：0；此寄存器记录通道6的FSM状态。
 */
#define RMT_STATE_6    0x00000007U
#define RMT_STATE_6_M  (RMT_STATE_6_V << RMT_STATE_6_S)
#define RMT_STATE_6_V  0x00000007U
#define RMT_STATE_6_S  22
/** RMT_MEM_OWNER_ERR_6:RO；位位置：[25]；默认值：0；当内存块的所有权错误时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_6    (BIT(25))
#define RMT_MEM_OWNER_ERR_6_M  (RMT_MEM_OWNER_ERR_6_V << RMT_MEM_OWNER_ERR_6_S)
#define RMT_MEM_OWNER_ERR_6_V  0x00000001U
#define RMT_MEM_OWNER_ERR_6_S  25
/** RMT_MEM_FULL_6:RO；位位置：[26]；默认值：0；如果接收器接收到的数据超过内存大小，则设置此状态位。
 */
#define RMT_MEM_FULL_6    (BIT(26))
#define RMT_MEM_FULL_6_M  (RMT_MEM_FULL_6_V << RMT_MEM_FULL_6_S)
#define RMT_MEM_FULL_6_V  0x00000001U
#define RMT_MEM_FULL_6_S  26
/** RMT_APB_MEM_RD_ERR_6:RO；位位置：[27]；默认值：0；当通过APB总线读取时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_6    (BIT(27))
#define RMT_APB_MEM_RD_ERR_6_M  (RMT_APB_MEM_RD_ERR_6_V << RMT_APB_MEM_RD_ERR_6_S)
#define RMT_APB_MEM_RD_ERR_6_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_6_S  27

/** RMT_CH7STATUS_REG寄存器通道7状态寄存器
 */
#define RMT_CH7STATUS_REG (DR_REG_RMT_BASE + 0x6c)
/** RMT_MEM_WADDR_EX_7:RO；位位置：[9:0]；默认值：192；当通道7的接收器使用RAM时，该寄存器记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_7    0x000003FFU
#define RMT_MEM_WADDR_EX_7_M  (RMT_MEM_WADDR_EX_7_V << RMT_MEM_WADDR_EX_7_S)
#define RMT_MEM_WADDR_EX_7_V  0x000003FFU
#define RMT_MEM_WADDR_EX_7_S  0
/** RMT_APB_MEM_RADDR_7:RO；比特位置：[20:11]；默认值：192；当通过APB总线读取RAM时，该寄存器记录内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_7    0x000003FFU
#define RMT_APB_MEM_RADDR_7_M  (RMT_APB_MEM_RADDR_7_V << RMT_APB_MEM_RADDR_7_S)
#define RMT_APB_MEM_RADDR_7_V  0x000003FFU
#define RMT_APB_MEM_RADDR_7_S  11
/** RMT_STATE_7:RO；位位置：[24:22]；默认值：0；该寄存器记录通道7的FSM状态。
 */
#define RMT_STATE_7    0x00000007U
#define RMT_STATE_7_M  (RMT_STATE_7_V << RMT_STATE_7_S)
#define RMT_STATE_7_V  0x00000007U
#define RMT_STATE_7_S  22
/** RMT_MEM_OWNER_ERR_7:RO；位位置：[25]；默认值：0；当内存块的所有权错误时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_7    (BIT(25))
#define RMT_MEM_OWNER_ERR_7_M  (RMT_MEM_OWNER_ERR_7_V << RMT_MEM_OWNER_ERR_7_S)
#define RMT_MEM_OWNER_ERR_7_V  0x00000001U
#define RMT_MEM_OWNER_ERR_7_S  25
/** RMT_MEM_FULL_7:RO；位位置：[26]；默认值：0；如果接收器接收到的数据超过内存大小，则设置此状态位。
 */
#define RMT_MEM_FULL_7    (BIT(26))
#define RMT_MEM_FULL_7_M  (RMT_MEM_FULL_7_V << RMT_MEM_FULL_7_S)
#define RMT_MEM_FULL_7_V  0x00000001U
#define RMT_MEM_FULL_7_S  26
/** RMT_APB_MEM_RD_ERR_7:RO；位位置：[27]；默认值：0；当通过APB总线读取时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_7    (BIT(27))
#define RMT_APB_MEM_RD_ERR_7_M  (RMT_APB_MEM_RD_ERR_7_V << RMT_APB_MEM_RD_ERR_7_S)
#define RMT_APB_MEM_RD_ERR_7_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_7_S  27

/** RMT_INT_RAW_REG寄存器原始中断状态
 */
#define RMT_INT_RAW_REG (DR_REG_RMT_BASE + 0x70)
/** RMT_CH0_TX_END_INT_RAW:R/WTC/SS；位位置：[0]；默认值：0；通道0的中断原始位。传输完成时触发。
 */
#define RMT_CH0_TX_END_INT_RAW    (BIT(0))
#define RMT_CH0_TX_END_INT_RAW_M  (RMT_CH0_TX_END_INT_RAW_V << RMT_CH0_TX_END_INT_RAW_S)
#define RMT_CH0_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH0_TX_END_INT_RAW_S  0
/** RMT_CH1_TX_END_INT_RAW:R/WTC/SS；位位置：[1]；默认值：0；通道1的中断原始位。传输完成时触发。
 */
#define RMT_CH1_TX_END_INT_RAW    (BIT(1))
#define RMT_CH1_TX_END_INT_RAW_M  (RMT_CH1_TX_END_INT_RAW_V << RMT_CH1_TX_END_INT_RAW_S)
#define RMT_CH1_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH1_TX_END_INT_RAW_S  1
/** RMT_CH2_TX_END_INT_RAW:R/WTC/SS；位位置：[2]；默认值：0；信道2的中断原始位。传输完成时触发。
 */
#define RMT_CH2_TX_END_INT_RAW    (BIT(2))
#define RMT_CH2_TX_END_INT_RAW_M  (RMT_CH2_TX_END_INT_RAW_V << RMT_CH2_TX_END_INT_RAW_S)
#define RMT_CH2_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH2_TX_END_INT_RAW_S  2
/** RMT_CH3_TX_END_INT_RAW:R/WTC/SS；位位置：[3]；默认值：0；通道3的中断原始位。传输完成时触发。
 */
#define RMT_CH3_TX_END_INT_RAW    (BIT(3))
#define RMT_CH3_TX_END_INT_RAW_M  (RMT_CH3_TX_END_INT_RAW_V << RMT_CH3_TX_END_INT_RAW_S)
#define RMT_CH3_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH3_TX_END_INT_RAW_S  3
/** RMT_CH0_ERR_INT_RAW:R/WTC/SS；位位置：[4]；默认值：0；CHANNEL0的中断原始位。发生错误时触发。
 */
#define RMT_CH0_ERR_INT_RAW    (BIT(4))
#define RMT_CH0_ERR_INT_RAW_M  (RMT_CH0_ERR_INT_RAW_V << RMT_CH0_ERR_INT_RAW_S)
#define RMT_CH0_ERR_INT_RAW_V  0x00000001U
#define RMT_CH0_ERR_INT_RAW_S  4
/** RMT_CH1_ERR_INT_RAW:R/WTC/SS；位位置：[5]；默认值：0；通道1的中断原始位。发生错误时触发。
 */
#define RMT_CH1_ERR_INT_RAW    (BIT(5))
#define RMT_CH1_ERR_INT_RAW_M  (RMT_CH1_ERR_INT_RAW_V << RMT_CH1_ERR_INT_RAW_S)
#define RMT_CH1_ERR_INT_RAW_V  0x00000001U
#define RMT_CH1_ERR_INT_RAW_S  5
/** RMT_CH2_ERR_INT_RAW:R/WTC/SS；位位置：[6]；默认值：0；通道2的中断原始位。发生错误时触发。
 */
#define RMT_CH2_ERR_INT_RAW    (BIT(6))
#define RMT_CH2_ERR_INT_RAW_M  (RMT_CH2_ERR_INT_RAW_V << RMT_CH2_ERR_INT_RAW_S)
#define RMT_CH2_ERR_INT_RAW_V  0x00000001U
#define RMT_CH2_ERR_INT_RAW_S  6
/** RMT_CH3_ERR_INT_RAW:R/WTC/SS；位位置：[7]；默认值：0；通道3的中断原始位。发生错误时触发。
 */
#define RMT_CH3_ERR_INT_RAW    (BIT(7))
#define RMT_CH3_ERR_INT_RAW_M  (RMT_CH3_ERR_INT_RAW_V << RMT_CH3_ERR_INT_RAW_S)
#define RMT_CH3_ERR_INT_RAW_V  0x00000001U
#define RMT_CH3_ERR_INT_RAW_S  7
/** RMT_CH0_TX_THR_EVENT_INT_RAW:R/WTC/SS；位位置：[8]；默认值：0；CHANNEL0的中断原始位。当变送器发送的数据超过配置值时触发。
 */
#define RMT_CH0_TX_THR_EVENT_INT_RAW    (BIT(8))
#define RMT_CH0_TX_THR_EVENT_INT_RAW_M  (RMT_CH0_TX_THR_EVENT_INT_RAW_V << RMT_CH0_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH0_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_RAW_S  8
/** RMT_CH1_TX_THR_EVENT_INT_RAW:R/WTC/SS；位位置：[9]；默认值：0；信道1的中断原始位。当发射机发送的数据超过配置值时触发。
 */
#define RMT_CH1_TX_THR_EVENT_INT_RAW    (BIT(9))
#define RMT_CH1_TX_THR_EVENT_INT_RAW_M  (RMT_CH1_TX_THR_EVENT_INT_RAW_V << RMT_CH1_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH1_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_RAW_S  9
/** RMT_CH2_TX_THR_EVENT_INT_RAW:R/WTC/SS；位位置：[10]；默认值：0；信道2的中断原始位。当发射机发送的数据超过配置值时触发。
 */
#define RMT_CH2_TX_THR_EVENT_INT_RAW    (BIT(10))
#define RMT_CH2_TX_THR_EVENT_INT_RAW_M  (RMT_CH2_TX_THR_EVENT_INT_RAW_V << RMT_CH2_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH2_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_RAW_S  10
/** RMT_CH3_TX_THR_EVENT_INT_RAW:R/WTC/SS；位位置：[11]；默认值：0；信道3的中断原始位。当发射机发送的数据超过配置值时触发。
 */
#define RMT_CH3_TX_THR_EVENT_INT_RAW    (BIT(11))
#define RMT_CH3_TX_THR_EVENT_INT_RAW_M  (RMT_CH3_TX_THR_EVENT_INT_RAW_V << RMT_CH3_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH3_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_RAW_S  11
/** RMT_CH0_TX_lop_INT_RAW:R/WTC/SS；位位置：[12]；默认值：0；CHANNEL0的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH0_TX_LOOP_INT_RAW    (BIT(12))
#define RMT_CH0_TX_LOOP_INT_RAW_M  (RMT_CH0_TX_LOOP_INT_RAW_V << RMT_CH0_TX_LOOP_INT_RAW_S)
#define RMT_CH0_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_RAW_S  12
/** RMT_CH1_TX_LOOP_INT_RAW:R/WTC/SS；位位置：[13]；默认值：0；通道1的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH1_TX_LOOP_INT_RAW    (BIT(13))
#define RMT_CH1_TX_LOOP_INT_RAW_M  (RMT_CH1_TX_LOOP_INT_RAW_V << RMT_CH1_TX_LOOP_INT_RAW_S)
#define RMT_CH1_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_RAW_S  13
/** RMT_CH2_TX_LOOP_INT_RAW:R/WTC/SS；位位置：[14]；默认值：0；通道2的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH2_TX_LOOP_INT_RAW    (BIT(14))
#define RMT_CH2_TX_LOOP_INT_RAW_M  (RMT_CH2_TX_LOOP_INT_RAW_V << RMT_CH2_TX_LOOP_INT_RAW_S)
#define RMT_CH2_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_RAW_S  14
/** RMT_CH3_TX_LOOP_INT_RAW:R/WTC/SS；位位置：[15]；默认值：0；通道3的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH3_TX_LOOP_INT_RAW    (BIT(15))
#define RMT_CH3_TX_LOOP_INT_RAW_M  (RMT_CH3_TX_LOOP_INT_RAW_V << RMT_CH3_TX_LOOP_INT_RAW_S)
#define RMT_CH3_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_RAW_S  15
/** RMT_CH4_RX_END_INT_RAW:R/WTC/SS；位位置：[16]；默认值：0；信道4的中断原始位。接收完成时触发。
 */
#define RMT_CH4_RX_END_INT_RAW    (BIT(16))
#define RMT_CH4_RX_END_INT_RAW_M  (RMT_CH4_RX_END_INT_RAW_V << RMT_CH4_RX_END_INT_RAW_S)
#define RMT_CH4_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH4_RX_END_INT_RAW_S  16
/** RMT_CH5_RX_END_INT_RAW:R/WTC/SS；位位置：[17]；默认值：0；信道5的中断原始位。接收完成时触发。
 */
#define RMT_CH5_RX_END_INT_RAW    (BIT(17))
#define RMT_CH5_RX_END_INT_RAW_M  (RMT_CH5_RX_END_INT_RAW_V << RMT_CH5_RX_END_INT_RAW_S)
#define RMT_CH5_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH5_RX_END_INT_RAW_S  17
/** RMT_CH6_RX_END_INT_RAW:R/WTC/SS；位位置：[18]；默认值：0；信道6的中断原始位。接收完成时触发。
 */
#define RMT_CH6_RX_END_INT_RAW    (BIT(18))
#define RMT_CH6_RX_END_INT_RAW_M  (RMT_CH6_RX_END_INT_RAW_V << RMT_CH6_RX_END_INT_RAW_S)
#define RMT_CH6_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH6_RX_END_INT_RAW_S  18
/** RMT_CH7_RX_END_INT_RAW:R/WTC/SS；位位置：[19]；默认值：0；通道7的中断原始位。接收完成时触发。
 */
#define RMT_CH7_RX_END_INT_RAW    (BIT(19))
#define RMT_CH7_RX_END_INT_RAW_M  (RMT_CH7_RX_END_INT_RAW_V << RMT_CH7_RX_END_INT_RAW_S)
#define RMT_CH7_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH7_RX_END_INT_RAW_S  19
/** RMT_CH4_ERR_INT_RAW:R/WTC/SS；位位置：[20]；默认值：0；通道4的中断原始位。发生错误时触发。
 */
#define RMT_CH4_ERR_INT_RAW    (BIT(20))
#define RMT_CH4_ERR_INT_RAW_M  (RMT_CH4_ERR_INT_RAW_V << RMT_CH4_ERR_INT_RAW_S)
#define RMT_CH4_ERR_INT_RAW_V  0x00000001U
#define RMT_CH4_ERR_INT_RAW_S  20
/** RMT_CH5_ERR_INT_RAW:R/WTC/SS；位位置：[21]；默认值：0；通道5的中断原始位。发生错误时触发。
 */
#define RMT_CH5_ERR_INT_RAW    (BIT(21))
#define RMT_CH5_ERR_INT_RAW_M  (RMT_CH5_ERR_INT_RAW_V << RMT_CH5_ERR_INT_RAW_S)
#define RMT_CH5_ERR_INT_RAW_V  0x00000001U
#define RMT_CH5_ERR_INT_RAW_S  21
/** RMT_CH6_ERR_INT_RAW:R/WTC/SS；位位置：[22]；默认值：0；通道6的中断原始位。发生错误时触发。
 */
#define RMT_CH6_ERR_INT_RAW    (BIT(22))
#define RMT_CH6_ERR_INT_RAW_M  (RMT_CH6_ERR_INT_RAW_V << RMT_CH6_ERR_INT_RAW_S)
#define RMT_CH6_ERR_INT_RAW_V  0x00000001U
#define RMT_CH6_ERR_INT_RAW_S  22
/** RMT_CH7_ERR_INT_RAW:R/WTC/SS；位位置：[23]；默认值：0；通道7的中断原始位。发生错误时触发。
 */
#define RMT_CH7_ERR_INT_RAW    (BIT(23))
#define RMT_CH7_ERR_INT_RAW_M  (RMT_CH7_ERR_INT_RAW_V << RMT_CH7_ERR_INT_RAW_S)
#define RMT_CH7_ERR_INT_RAW_V  0x00000001U
#define RMT_CH7_ERR_INT_RAW_S  23
/** RMT_CH4_RX_tr_EVENT_INT_RAW:R/WTC/SS；位位置：[24]；默认值：0；通道4的中断原始位。当接收器接收到的数据超过配置值时触发。
 */
#define RMT_CH4_RX_THR_EVENT_INT_RAW    (BIT(24))
#define RMT_CH4_RX_THR_EVENT_INT_RAW_M  (RMT_CH4_RX_THR_EVENT_INT_RAW_V << RMT_CH4_RX_THR_EVENT_INT_RAW_S)
#define RMT_CH4_RX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH4_RX_THR_EVENT_INT_RAW_S  24
/** RMT_CH5_RX_tr_EVENT_INT_RAW:R/WTC/SS；位位置：[25]；默认值：0；通道5的中断原始位。当接收器接收到的数据超过配置值时触发。
 */
#define RMT_CH5_RX_THR_EVENT_INT_RAW    (BIT(25))
#define RMT_CH5_RX_THR_EVENT_INT_RAW_M  (RMT_CH5_RX_THR_EVENT_INT_RAW_V << RMT_CH5_RX_THR_EVENT_INT_RAW_S)
#define RMT_CH5_RX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH5_RX_THR_EVENT_INT_RAW_S  25
/** RMT_CH6_RX_tr_EVENT_INT_RAW:R/WTC/SS；位位置：[26]；默认值：0；通道6的中断原始位。当接收器接收到的数据超过配置值时触发。
 */
#define RMT_CH6_RX_THR_EVENT_INT_RAW    (BIT(26))
#define RMT_CH6_RX_THR_EVENT_INT_RAW_M  (RMT_CH6_RX_THR_EVENT_INT_RAW_V << RMT_CH6_RX_THR_EVENT_INT_RAW_S)
#define RMT_CH6_RX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH6_RX_THR_EVENT_INT_RAW_S  26
/** RMT_CH7_RX_THR_EVENT_INT_RAW:R/WTC/SS；位位置：[27]；默认值：0；通道7的中断原始位。当接收器接收到的数据超过配置值时触发。
 */
#define RMT_CH7_RX_THR_EVENT_INT_RAW    (BIT(27))
#define RMT_CH7_RX_THR_EVENT_INT_RAW_M  (RMT_CH7_RX_THR_EVENT_INT_RAW_V << RMT_CH7_RX_THR_EVENT_INT_RAW_S)
#define RMT_CH7_RX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH7_RX_THR_EVENT_INT_RAW_S  27
/** RMT_CH3_DMA_ACCESS_FAIL_INT_RAW:R/WTC/SS；位位置：[28]；默认值：0；通道3的中断原始位。当dma访问通道3失败时触发。
 */
#define RMT_CH3_DMA_ACCESS_FAIL_INT_RAW    (BIT(28))
#define RMT_CH3_DMA_ACCESS_FAIL_INT_RAW_M  (RMT_CH3_DMA_ACCESS_FAIL_INT_RAW_V << RMT_CH3_DMA_ACCESS_FAIL_INT_RAW_S)
#define RMT_CH3_DMA_ACCESS_FAIL_INT_RAW_V  0x00000001U
#define RMT_CH3_DMA_ACCESS_FAIL_INT_RAW_S  28
/** RMT_CH7_DMA_ACCESS_FAIL_INT_RAW:R/WTC/SS；位位置：[29]；默认值：0；通道7的中断原始位。当dma访问通道7失败时触发。
 */
#define RMT_CH7_DMA_ACCESS_FAIL_INT_RAW    (BIT(29))
#define RMT_CH7_DMA_ACCESS_FAIL_INT_RAW_M  (RMT_CH7_DMA_ACCESS_FAIL_INT_RAW_V << RMT_CH7_DMA_ACCESS_FAIL_INT_RAW_S)
#define RMT_CH7_DMA_ACCESS_FAIL_INT_RAW_V  0x00000001U
#define RMT_CH7_DMA_ACCESS_FAIL_INT_RAW_S  29

/** RMT_INT_ST_REG寄存器屏蔽中断状态
 */
#define RMT_INT_ST_REG (DR_REG_RMT_BASE + 0x74)
/** RMT_CH0_TX_END_INT_ST:RO；位位置：[0]；默认值：0；CH0_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH0_TX_END_INT_ST    (BIT(0))
#define RMT_CH0_TX_END_INT_ST_M  (RMT_CH0_TX_END_INT_ST_V << RMT_CH0_TX_END_INT_ST_S)
#define RMT_CH0_TX_END_INT_ST_V  0x00000001U
#define RMT_CH0_TX_END_INT_ST_S  0
/** RMT_CH1_TX_END_INT_ST:RO；位位置：[1]；默认值：0；CH1_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH1_TX_END_INT_ST    (BIT(1))
#define RMT_CH1_TX_END_INT_ST_M  (RMT_CH1_TX_END_INT_ST_V << RMT_CH1_TX_END_INT_ST_S)
#define RMT_CH1_TX_END_INT_ST_V  0x00000001U
#define RMT_CH1_TX_END_INT_ST_S  1
/** RMT_CH2_TX_END_INT_ST:RO；位位置：[2]；默认值：0；CH2_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH2_TX_END_INT_ST    (BIT(2))
#define RMT_CH2_TX_END_INT_ST_M  (RMT_CH2_TX_END_INT_ST_V << RMT_CH2_TX_END_INT_ST_S)
#define RMT_CH2_TX_END_INT_ST_V  0x00000001U
#define RMT_CH2_TX_END_INT_ST_S  2
/** RMT_CH3_TX_END_INT_ST:RO；位位置：[3]；默认值：0；CH3_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH3_TX_END_INT_ST    (BIT(3))
#define RMT_CH3_TX_END_INT_ST_M  (RMT_CH3_TX_END_INT_ST_V << RMT_CH3_TX_END_INT_ST_S)
#define RMT_CH3_TX_END_INT_ST_V  0x00000001U
#define RMT_CH3_TX_END_INT_ST_S  3
/** RMT_CH0_ERR_INT_ST:RO；位位置：[4]；默认值：0；CH0_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH0_ERR_INT_ST    (BIT(4))
#define RMT_CH0_ERR_INT_ST_M  (RMT_CH0_ERR_INT_ST_V << RMT_CH0_ERR_INT_ST_S)
#define RMT_CH0_ERR_INT_ST_V  0x00000001U
#define RMT_CH0_ERR_INT_ST_S  4
/** RMT_CH1_ERR_INT_ST:RO；位位置：[5]；默认值：0；CH1_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH1_ERR_INT_ST    (BIT(5))
#define RMT_CH1_ERR_INT_ST_M  (RMT_CH1_ERR_INT_ST_V << RMT_CH1_ERR_INT_ST_S)
#define RMT_CH1_ERR_INT_ST_V  0x00000001U
#define RMT_CH1_ERR_INT_ST_S  5
/** RMT_CH2_ERR_INT_ST:RO；位位置：[6]；默认值：0；CH2_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH2_ERR_INT_ST    (BIT(6))
#define RMT_CH2_ERR_INT_ST_M  (RMT_CH2_ERR_INT_ST_V << RMT_CH2_ERR_INT_ST_S)
#define RMT_CH2_ERR_INT_ST_V  0x00000001U
#define RMT_CH2_ERR_INT_ST_S  6
/** RMT_CH3_ERR_INT_ST:RO；位位置：[7]；默认值：0；CH3_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH3_ERR_INT_ST    (BIT(7))
#define RMT_CH3_ERR_INT_ST_M  (RMT_CH3_ERR_INT_ST_V << RMT_CH3_ERR_INT_ST_S)
#define RMT_CH3_ERR_INT_ST_V  0x00000001U
#define RMT_CH3_ERR_INT_ST_S  7
/** RMT_CH0_TX_THR_EVENT_INT_ST:RO；位位置：[8]；默认值：0；CH0_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH0_TX_THR_EVENT_INT_ST    (BIT(8))
#define RMT_CH0_TX_THR_EVENT_INT_ST_M  (RMT_CH0_TX_THR_EVENT_INT_ST_V << RMT_CH0_TX_THR_EVENT_INT_ST_S)
#define RMT_CH0_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_ST_S  8
/** RMT_CH1_TX_THR_EVENT_INT_ST:RO；位位置：[9]；默认值：0；CH1_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH1_TX_THR_EVENT_INT_ST    (BIT(9))
#define RMT_CH1_TX_THR_EVENT_INT_ST_M  (RMT_CH1_TX_THR_EVENT_INT_ST_V << RMT_CH1_TX_THR_EVENT_INT_ST_S)
#define RMT_CH1_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_ST_S  9
/** RMT_CH2_TX_THR_EVENT_INT_ST:RO；位位置：[10]；默认值：0；CH2_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH2_TX_THR_EVENT_INT_ST    (BIT(10))
#define RMT_CH2_TX_THR_EVENT_INT_ST_M  (RMT_CH2_TX_THR_EVENT_INT_ST_V << RMT_CH2_TX_THR_EVENT_INT_ST_S)
#define RMT_CH2_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_ST_S  10
/** RMT_CH3_TX_THR_EVENT_INT_ST:RO；位位置：[11]；默认值：0；CH3_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH3_TX_THR_EVENT_INT_ST    (BIT(11))
#define RMT_CH3_TX_THR_EVENT_INT_ST_M  (RMT_CH3_TX_THR_EVENT_INT_ST_V << RMT_CH3_TX_THR_EVENT_INT_ST_S)
#define RMT_CH3_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_ST_S  11
/** RMT_CH0_TX_lop_INT_ST:RO；位位置：[12]；默认值：0；CH0_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH0_TX_LOOP_INT_ST    (BIT(12))
#define RMT_CH0_TX_LOOP_INT_ST_M  (RMT_CH0_TX_LOOP_INT_ST_V << RMT_CH0_TX_LOOP_INT_ST_S)
#define RMT_CH0_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_ST_S  12
/** RMT_CH1_TX_LOOP_INT_ST:RO；位位置：[13]；默认值：0；CH1_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH1_TX_LOOP_INT_ST    (BIT(13))
#define RMT_CH1_TX_LOOP_INT_ST_M  (RMT_CH1_TX_LOOP_INT_ST_V << RMT_CH1_TX_LOOP_INT_ST_S)
#define RMT_CH1_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_ST_S  13
/** RMT_CH2_TX_LOOP_INT_ST:RO；位位置：[14]；默认值：0；CH2_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH2_TX_LOOP_INT_ST    (BIT(14))
#define RMT_CH2_TX_LOOP_INT_ST_M  (RMT_CH2_TX_LOOP_INT_ST_V << RMT_CH2_TX_LOOP_INT_ST_S)
#define RMT_CH2_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_ST_S  14
/** RMT_CH3_TX_LOOP_INT_ST:RO；位位置：[15]；默认值：0；CH3_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH3_TX_LOOP_INT_ST    (BIT(15))
#define RMT_CH3_TX_LOOP_INT_ST_M  (RMT_CH3_TX_LOOP_INT_ST_V << RMT_CH3_TX_LOOP_INT_ST_S)
#define RMT_CH3_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_ST_S  15
/** RMT_CH4_RX_END_INT_ST:RO；位位置：[16]；默认值：0；CH4_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH4_RX_END_INT_ST    (BIT(16))
#define RMT_CH4_RX_END_INT_ST_M  (RMT_CH4_RX_END_INT_ST_V << RMT_CH4_RX_END_INT_ST_S)
#define RMT_CH4_RX_END_INT_ST_V  0x00000001U
#define RMT_CH4_RX_END_INT_ST_S  16
/** RMT_CH5_RX_END_INT_ST:RO；位位置：[17]；默认值：0；CH5_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH5_RX_END_INT_ST    (BIT(17))
#define RMT_CH5_RX_END_INT_ST_M  (RMT_CH5_RX_END_INT_ST_V << RMT_CH5_RX_END_INT_ST_S)
#define RMT_CH5_RX_END_INT_ST_V  0x00000001U
#define RMT_CH5_RX_END_INT_ST_S  17
/** RMT_CH6_RX_END_INT_ST:RO；位位置：[18]；默认值：0；CH6_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH6_RX_END_INT_ST    (BIT(18))
#define RMT_CH6_RX_END_INT_ST_M  (RMT_CH6_RX_END_INT_ST_V << RMT_CH6_RX_END_INT_ST_S)
#define RMT_CH6_RX_END_INT_ST_V  0x00000001U
#define RMT_CH6_RX_END_INT_ST_S  18
/** RMT_CH7_RX_END_INT_ST:RO；位位置：[19]；默认值：0；CH7_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH7_RX_END_INT_ST    (BIT(19))
#define RMT_CH7_RX_END_INT_ST_M  (RMT_CH7_RX_END_INT_ST_V << RMT_CH7_RX_END_INT_ST_S)
#define RMT_CH7_RX_END_INT_ST_V  0x00000001U
#define RMT_CH7_RX_END_INT_ST_S  19
/** RMT_CH4_ERR_INT_ST:RO；位位置：[20]；默认值：0；CH4_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH4_ERR_INT_ST    (BIT(20))
#define RMT_CH4_ERR_INT_ST_M  (RMT_CH4_ERR_INT_ST_V << RMT_CH4_ERR_INT_ST_S)
#define RMT_CH4_ERR_INT_ST_V  0x00000001U
#define RMT_CH4_ERR_INT_ST_S  20
/** RMT_CH5_ERR_INT_ST:RO；位位置：[21]；默认值：0；CH5_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH5_ERR_INT_ST    (BIT(21))
#define RMT_CH5_ERR_INT_ST_M  (RMT_CH5_ERR_INT_ST_V << RMT_CH5_ERR_INT_ST_S)
#define RMT_CH5_ERR_INT_ST_V  0x00000001U
#define RMT_CH5_ERR_INT_ST_S  21
/** RMT_CH6_ERR_INT_ST:RO；位位置：[22]；默认值：0；CH6_ERROR_INT的屏蔽中断状态位。
 */
#define RMT_CH6_ERR_INT_ST    (BIT(22))
#define RMT_CH6_ERR_INT_ST_M  (RMT_CH6_ERR_INT_ST_V << RMT_CH6_ERR_INT_ST_S)
#define RMT_CH6_ERR_INT_ST_V  0x00000001U
#define RMT_CH6_ERR_INT_ST_S  22
/** RMT_CH7_ERR_INT_ST:RO；位位置：[23]；默认值：0；CH7_ERROR_INT的屏蔽中断状态位。
 */
#define RMT_CH7_ERR_INT_ST    (BIT(23))
#define RMT_CH7_ERR_INT_ST_M  (RMT_CH7_ERR_INT_ST_V << RMT_CH7_ERR_INT_ST_S)
#define RMT_CH7_ERR_INT_ST_V  0x00000001U
#define RMT_CH7_ERR_INT_ST_S  23
/** RMT_CH4_RX_tr_EVENT_INT_ST:RO；位位置：[24]；默认值：0；CH4_RX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH4_RX_THR_EVENT_INT_ST    (BIT(24))
#define RMT_CH4_RX_THR_EVENT_INT_ST_M  (RMT_CH4_RX_THR_EVENT_INT_ST_V << RMT_CH4_RX_THR_EVENT_INT_ST_S)
#define RMT_CH4_RX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH4_RX_THR_EVENT_INT_ST_S  24
/** RMT_CH5_RX_tr_EVENT_INT_ST:RO；位位置：[25]；默认值：0；CH5_RX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH5_RX_THR_EVENT_INT_ST    (BIT(25))
#define RMT_CH5_RX_THR_EVENT_INT_ST_M  (RMT_CH5_RX_THR_EVENT_INT_ST_V << RMT_CH5_RX_THR_EVENT_INT_ST_S)
#define RMT_CH5_RX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH5_RX_THR_EVENT_INT_ST_S  25
/** RMT_CH6_RX_tr_EVENT_INT_ST:RO；位位置：[26]；默认值：0；CH6_RX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH6_RX_THR_EVENT_INT_ST    (BIT(26))
#define RMT_CH6_RX_THR_EVENT_INT_ST_M  (RMT_CH6_RX_THR_EVENT_INT_ST_V << RMT_CH6_RX_THR_EVENT_INT_ST_S)
#define RMT_CH6_RX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH6_RX_THR_EVENT_INT_ST_S  26
/** RMT_CH7_RX_THR_EVENT_INT_ST:RO；位位置：[27]；默认值：0；CH7_RX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH7_RX_THR_EVENT_INT_ST    (BIT(27))
#define RMT_CH7_RX_THR_EVENT_INT_ST_M  (RMT_CH7_RX_THR_EVENT_INT_ST_V << RMT_CH7_RX_THR_EVENT_INT_ST_S)
#define RMT_CH7_RX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH7_RX_THR_EVENT_INT_ST_S  27
/** RMT_CH3_DMA_ACCESS_FAIL_INT_ST:RO；位位置：[28]；默认值：0；CH3_DMA_ACCESS_FAIL_INT的屏蔽中断状态位。
 */
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ST    (BIT(28))
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ST_M  (RMT_CH3_DMA_ACCESS_FAIL_INT_ST_V << RMT_CH3_DMA_ACCESS_FAIL_INT_ST_S)
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ST_V  0x00000001U
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ST_S  28
/** RMT_CH7_DMA_ACCESS_FAIL_INT_ST:RO；位位置：[29]；默认值：0；CH7_DMA_ACCESS_FAIL_INT的屏蔽中断状态位。
 */
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ST    (BIT(29))
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ST_M  (RMT_CH7_DMA_ACCESS_FAIL_INT_ST_V << RMT_CH7_DMA_ACCESS_FAIL_INT_ST_S)
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ST_V  0x00000001U
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ST_S  29

/** RMT_INT_ENA_REG寄存器中断启用位
 */
#define RMT_INT_ENA_REG (DR_REG_RMT_BASE + 0x78)
/** RMT_CH0_TX_END_INT_ENA:R/W；位位置：[0]；默认值：0；CH0_TX_END_INT的中断启用位。
 */
#define RMT_CH0_TX_END_INT_ENA    (BIT(0))
#define RMT_CH0_TX_END_INT_ENA_M  (RMT_CH0_TX_END_INT_ENA_V << RMT_CH0_TX_END_INT_ENA_S)
#define RMT_CH0_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH0_TX_END_INT_ENA_S  0
/** RMT_CH1_TX_END_INT_ENA：R/W；位位置：[1]；默认值：0；CH1_TX_END_INT的中断启用位。
 */
#define RMT_CH1_TX_END_INT_ENA    (BIT(1))
#define RMT_CH1_TX_END_INT_ENA_M  (RMT_CH1_TX_END_INT_ENA_V << RMT_CH1_TX_END_INT_ENA_S)
#define RMT_CH1_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH1_TX_END_INT_ENA_S  1
/** RMT_CH2_TX_END_INT_ENA：R/W；位位置：[2]；默认值：0；CH2_TX_END_INT的中断启用位。
 */
#define RMT_CH2_TX_END_INT_ENA    (BIT(2))
#define RMT_CH2_TX_END_INT_ENA_M  (RMT_CH2_TX_END_INT_ENA_V << RMT_CH2_TX_END_INT_ENA_S)
#define RMT_CH2_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH2_TX_END_INT_ENA_S  2
/** RMT_CH3_TX_END_INT_ENA：R/W；位位置：[3]；默认值：0；CH3_TX_END_INT的中断启用位。
 */
#define RMT_CH3_TX_END_INT_ENA    (BIT(3))
#define RMT_CH3_TX_END_INT_ENA_M  (RMT_CH3_TX_END_INT_ENA_V << RMT_CH3_TX_END_INT_ENA_S)
#define RMT_CH3_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH3_TX_END_INT_ENA_S  3
/** RMT_CH0_ERR_INT_ENA:R/W；位位置：[4]；默认值：0；CH0_ERR_INT的中断启用位。
 */
#define RMT_CH0_ERR_INT_ENA    (BIT(4))
#define RMT_CH0_ERR_INT_ENA_M  (RMT_CH0_ERR_INT_ENA_V << RMT_CH0_ERR_INT_ENA_S)
#define RMT_CH0_ERR_INT_ENA_V  0x00000001U
#define RMT_CH0_ERR_INT_ENA_S  4
/** RMT_CH1_ERR_INT_ENA:R/W；位位置：[5]；默认值：0；CH1_ERR_INT的中断启用位。
 */
#define RMT_CH1_ERR_INT_ENA    (BIT(5))
#define RMT_CH1_ERR_INT_ENA_M  (RMT_CH1_ERR_INT_ENA_V << RMT_CH1_ERR_INT_ENA_S)
#define RMT_CH1_ERR_INT_ENA_V  0x00000001U
#define RMT_CH1_ERR_INT_ENA_S  5
/** RMT_CH2_ERR_INT_ENA:R/W；位位置：[6]；默认值：0；CH2_ERR_INT的中断启用位。
 */
#define RMT_CH2_ERR_INT_ENA    (BIT(6))
#define RMT_CH2_ERR_INT_ENA_M  (RMT_CH2_ERR_INT_ENA_V << RMT_CH2_ERR_INT_ENA_S)
#define RMT_CH2_ERR_INT_ENA_V  0x00000001U
#define RMT_CH2_ERR_INT_ENA_S  6
/** RMT_CH3_ERR_INT_ENA：R/W；位位置：[7]；默认值：0；CH3_ERR_INT的中断启用位。
 */
#define RMT_CH3_ERR_INT_ENA    (BIT(7))
#define RMT_CH3_ERR_INT_ENA_M  (RMT_CH3_ERR_INT_ENA_V << RMT_CH3_ERR_INT_ENA_S)
#define RMT_CH3_ERR_INT_ENA_V  0x00000001U
#define RMT_CH3_ERR_INT_ENA_S  7
/** RMT_CH0_TX_THR_EVENT_INT_ENA:R/W；位位置：[8]；默认值：0；CH0_TTX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH0_TX_THR_EVENT_INT_ENA    (BIT(8))
#define RMT_CH0_TX_THR_EVENT_INT_ENA_M  (RMT_CH0_TX_THR_EVENT_INT_ENA_V << RMT_CH0_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH0_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_ENA_S  8
/** RMT_CH1_TX_THR_EVENT_INT_ENA:R/W；位位置：[9]；默认值：0；CH1_TX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH1_TX_THR_EVENT_INT_ENA    (BIT(9))
#define RMT_CH1_TX_THR_EVENT_INT_ENA_M  (RMT_CH1_TX_THR_EVENT_INT_ENA_V << RMT_CH1_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH1_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_ENA_S  9
/** RMT_CH2_TX_THR_EVENT_INT_ENA:R/W；位位置：[10]；默认值：0；CH2_TX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH2_TX_THR_EVENT_INT_ENA    (BIT(10))
#define RMT_CH2_TX_THR_EVENT_INT_ENA_M  (RMT_CH2_TX_THR_EVENT_INT_ENA_V << RMT_CH2_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH2_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_ENA_S  10
/** RMT_CH3_TX_THR_EVENT_INT_ENA:R/W；位位置：[11]；默认值：0；CH3_TX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH3_TX_THR_EVENT_INT_ENA    (BIT(11))
#define RMT_CH3_TX_THR_EVENT_INT_ENA_M  (RMT_CH3_TX_THR_EVENT_INT_ENA_V << RMT_CH3_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH3_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_ENA_S  11
/** RMT_CH0_TX_lop_INT_ENA:R/W；位位置：[12]；默认值：0；CH0_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH0_TX_LOOP_INT_ENA    (BIT(12))
#define RMT_CH0_TX_LOOP_INT_ENA_M  (RMT_CH0_TX_LOOP_INT_ENA_V << RMT_CH0_TX_LOOP_INT_ENA_S)
#define RMT_CH0_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_ENA_S  12
/** RMT_CH1_TX_LOOP_INT_ENA：R/W；位位置：[13]；默认值：0；CH1_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH1_TX_LOOP_INT_ENA    (BIT(13))
#define RMT_CH1_TX_LOOP_INT_ENA_M  (RMT_CH1_TX_LOOP_INT_ENA_V << RMT_CH1_TX_LOOP_INT_ENA_S)
#define RMT_CH1_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_ENA_S  13
/** RMT_CH2_TX_LOOP_INT_ENA：R/W；位位置：[14]；默认值：0；CH2_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH2_TX_LOOP_INT_ENA    (BIT(14))
#define RMT_CH2_TX_LOOP_INT_ENA_M  (RMT_CH2_TX_LOOP_INT_ENA_V << RMT_CH2_TX_LOOP_INT_ENA_S)
#define RMT_CH2_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_ENA_S  14
/** RMT_CH3_TX_LOOP_INT_ENA：R/W；位位置：[15]；默认值：0；CH3_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH3_TX_LOOP_INT_ENA    (BIT(15))
#define RMT_CH3_TX_LOOP_INT_ENA_M  (RMT_CH3_TX_LOOP_INT_ENA_V << RMT_CH3_TX_LOOP_INT_ENA_S)
#define RMT_CH3_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_ENA_S  15
/** RMT_CH4_RX_END_INT_ENA:R/W；位位置：[16]；默认值：0；CH4_RX_END_INT的中断启用位。
 */
#define RMT_CH4_RX_END_INT_ENA    (BIT(16))
#define RMT_CH4_RX_END_INT_ENA_M  (RMT_CH4_RX_END_INT_ENA_V << RMT_CH4_RX_END_INT_ENA_S)
#define RMT_CH4_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH4_RX_END_INT_ENA_S  16
/** RMT_CH5_RX_END_INT_ENA:R/W；位位置：[17]；默认值：0；CH5_RX_END_INT的中断启用位。
 */
#define RMT_CH5_RX_END_INT_ENA    (BIT(17))
#define RMT_CH5_RX_END_INT_ENA_M  (RMT_CH5_RX_END_INT_ENA_V << RMT_CH5_RX_END_INT_ENA_S)
#define RMT_CH5_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH5_RX_END_INT_ENA_S  17
/** RMT_CH6_RX_END_INT_ENA:R/W；位位置：[18]；默认值：0；CH6_RX_END_INT的中断启用位。
 */
#define RMT_CH6_RX_END_INT_ENA    (BIT(18))
#define RMT_CH6_RX_END_INT_ENA_M  (RMT_CH6_RX_END_INT_ENA_V << RMT_CH6_RX_END_INT_ENA_S)
#define RMT_CH6_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH6_RX_END_INT_ENA_S  18
/** RMT_CH7_RX_END_INT_ENA:R/W；位位置：[19]；默认值：0；CH7_RX_END_INT的中断启用位。
 */
#define RMT_CH7_RX_END_INT_ENA    (BIT(19))
#define RMT_CH7_RX_END_INT_ENA_M  (RMT_CH7_RX_END_INT_ENA_V << RMT_CH7_RX_END_INT_ENA_S)
#define RMT_CH7_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH7_RX_END_INT_ENA_S  19
/** RMT_CH4_ERR_INT_ENA:R/W；位位置：[20]；默认值：0；CH4_ERR_INT的中断启用位。
 */
#define RMT_CH4_ERR_INT_ENA    (BIT(20))
#define RMT_CH4_ERR_INT_ENA_M  (RMT_CH4_ERR_INT_ENA_V << RMT_CH4_ERR_INT_ENA_S)
#define RMT_CH4_ERR_INT_ENA_V  0x00000001U
#define RMT_CH4_ERR_INT_ENA_S  20
/** RMT_CH5_ERR_INT_ENA:R/W；位位置：[21]；默认值：0；CH5_ERR_INT的中断启用位。
 */
#define RMT_CH5_ERR_INT_ENA    (BIT(21))
#define RMT_CH5_ERR_INT_ENA_M  (RMT_CH5_ERR_INT_ENA_V << RMT_CH5_ERR_INT_ENA_S)
#define RMT_CH5_ERR_INT_ENA_V  0x00000001U
#define RMT_CH5_ERR_INT_ENA_S  21
/** RMT_CH6_ERR_INT_ENA:R/W；位位置：[22]；默认值：0；CH6_ERROR_INT的中断启用位。
 */
#define RMT_CH6_ERR_INT_ENA    (BIT(22))
#define RMT_CH6_ERR_INT_ENA_M  (RMT_CH6_ERR_INT_ENA_V << RMT_CH6_ERR_INT_ENA_S)
#define RMT_CH6_ERR_INT_ENA_V  0x00000001U
#define RMT_CH6_ERR_INT_ENA_S  22
/** RMT_CH7_ERR_INT_ENA:R/W；位位置：[23]；默认值：0；CH7_ERROR_INT的中断启用位。
 */
#define RMT_CH7_ERR_INT_ENA    (BIT(23))
#define RMT_CH7_ERR_INT_ENA_M  (RMT_CH7_ERR_INT_ENA_V << RMT_CH7_ERR_INT_ENA_S)
#define RMT_CH7_ERR_INT_ENA_V  0x00000001U
#define RMT_CH7_ERR_INT_ENA_S  23
/** RMT_CH4_RX_tr_EVENT_INT_ENA:R/W；位位置：[24]；默认值：0；CH4_RX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH4_RX_THR_EVENT_INT_ENA    (BIT(24))
#define RMT_CH4_RX_THR_EVENT_INT_ENA_M  (RMT_CH4_RX_THR_EVENT_INT_ENA_V << RMT_CH4_RX_THR_EVENT_INT_ENA_S)
#define RMT_CH4_RX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH4_RX_THR_EVENT_INT_ENA_S  24
/** RMT_CH5_RX_tr_EVENT_INT_ENA:R/W；位位置：[25]；默认值：0；CH5_RX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH5_RX_THR_EVENT_INT_ENA    (BIT(25))
#define RMT_CH5_RX_THR_EVENT_INT_ENA_M  (RMT_CH5_RX_THR_EVENT_INT_ENA_V << RMT_CH5_RX_THR_EVENT_INT_ENA_S)
#define RMT_CH5_RX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH5_RX_THR_EVENT_INT_ENA_S  25
/** RMT_CH6_RX_tr_EVENT_INT_ENA:R/W；位位置：[26]；默认值：0；CH6_RX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH6_RX_THR_EVENT_INT_ENA    (BIT(26))
#define RMT_CH6_RX_THR_EVENT_INT_ENA_M  (RMT_CH6_RX_THR_EVENT_INT_ENA_V << RMT_CH6_RX_THR_EVENT_INT_ENA_S)
#define RMT_CH6_RX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH6_RX_THR_EVENT_INT_ENA_S  26
/** RMT_CH7_RX_THR_EVENT_INT_ENA:R/W；位位置：[27]；默认值：0；CH7_RX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH7_RX_THR_EVENT_INT_ENA    (BIT(27))
#define RMT_CH7_RX_THR_EVENT_INT_ENA_M  (RMT_CH7_RX_THR_EVENT_INT_ENA_V << RMT_CH7_RX_THR_EVENT_INT_ENA_S)
#define RMT_CH7_RX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH7_RX_THR_EVENT_INT_ENA_S  27
/** RMT_CH3_DMA_ACCESS_FAIL_INT_ENA:R/W；位位置：[28]；默认值：0；CH3_DMA_ACCESS_FAIL_INT的中断启用位。
 */
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ENA    (BIT(28))
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ENA_M  (RMT_CH3_DMA_ACCESS_FAIL_INT_ENA_V << RMT_CH3_DMA_ACCESS_FAIL_INT_ENA_S)
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ENA_V  0x00000001U
#define RMT_CH3_DMA_ACCESS_FAIL_INT_ENA_S  28
/** RMT_CH7_DMA_ACCESS_FAIL_INT_ENA:R/W；位位置：[29]；默认值：0；CH7_DMA_ACCESS_FAIL_INT的中断启用位。
 */
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ENA    (BIT(29))
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ENA_M  (RMT_CH7_DMA_ACCESS_FAIL_INT_ENA_V << RMT_CH7_DMA_ACCESS_FAIL_INT_ENA_S)
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ENA_V  0x00000001U
#define RMT_CH7_DMA_ACCESS_FAIL_INT_ENA_S  29

/** RMT_INT_CLR_REG寄存器中断清除位
 */
#define RMT_INT_CLR_REG (DR_REG_RMT_BASE + 0x7c)
/** RMT_CH0_TX_END_INT_CLR:WT；位位置：[0]；默认值：0；设置此位以清除CHO_TX_END_INT中断。
 */
#define RMT_CH0_TX_END_INT_CLR    (BIT(0))
#define RMT_CH0_TX_END_INT_CLR_M  (RMT_CH0_TX_END_INT_CLR_V << RMT_CH0_TX_END_INT_CLR_S)
#define RMT_CH0_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH0_TX_END_INT_CLR_S  0
/** RMT_CH1_TX_END_INT_CLR:WT；位位置：[1]；默认值：0；设置此位以清除CH1_TX_END_INT中断。
 */
#define RMT_CH1_TX_END_INT_CLR    (BIT(1))
#define RMT_CH1_TX_END_INT_CLR_M  (RMT_CH1_TX_END_INT_CLR_V << RMT_CH1_TX_END_INT_CLR_S)
#define RMT_CH1_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH1_TX_END_INT_CLR_S  1
/** RMT_CH2_TX_END_INT_CLR:WT；位位置：[2]；默认值：0；设置此位以清除CH2_TX_END_INT中断。
 */
#define RMT_CH2_TX_END_INT_CLR    (BIT(2))
#define RMT_CH2_TX_END_INT_CLR_M  (RMT_CH2_TX_END_INT_CLR_V << RMT_CH2_TX_END_INT_CLR_S)
#define RMT_CH2_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH2_TX_END_INT_CLR_S  2
/** RMT_CH3_TX_END_INT_CLR:WT；位位置：[3]；默认值：0；设置该位以清除CH3_TX_END_INT中断。
 */
#define RMT_CH3_TX_END_INT_CLR    (BIT(3))
#define RMT_CH3_TX_END_INT_CLR_M  (RMT_CH3_TX_END_INT_CLR_V << RMT_CH3_TX_END_INT_CLR_S)
#define RMT_CH3_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH3_TX_END_INT_CLR_S  3
/** RMT_CH0_ERR_INT_CLR:WT；位位置：[4]；默认值：0；设置此位以清除CHO_ERROR_INT中断。
 */
#define RMT_CH0_ERR_INT_CLR    (BIT(4))
#define RMT_CH0_ERR_INT_CLR_M  (RMT_CH0_ERR_INT_CLR_V << RMT_CH0_ERR_INT_CLR_S)
#define RMT_CH0_ERR_INT_CLR_V  0x00000001U
#define RMT_CH0_ERR_INT_CLR_S  4
/** RMT_CH1_ERR_INT_CLR:WT；位位置：[5]；默认值：0；设置该位以清除CH1_ERROR_INT中断。
 */
#define RMT_CH1_ERR_INT_CLR    (BIT(5))
#define RMT_CH1_ERR_INT_CLR_M  (RMT_CH1_ERR_INT_CLR_V << RMT_CH1_ERR_INT_CLR_S)
#define RMT_CH1_ERR_INT_CLR_V  0x00000001U
#define RMT_CH1_ERR_INT_CLR_S  5
/** RMT_CH2_ERR_INT_CLR:WT；位位置：[6]；默认值：0；设置此位以清除CH2_ERR_INT中断。
 */
#define RMT_CH2_ERR_INT_CLR    (BIT(6))
#define RMT_CH2_ERR_INT_CLR_M  (RMT_CH2_ERR_INT_CLR_V << RMT_CH2_ERR_INT_CLR_S)
#define RMT_CH2_ERR_INT_CLR_V  0x00000001U
#define RMT_CH2_ERR_INT_CLR_S  6
/** RMT_CH3_ERR_INT_CLR:WT；位位置：[7]；默认值：0；设置该位以清除CH3_ERROR_INT中断。
 */
#define RMT_CH3_ERR_INT_CLR    (BIT(7))
#define RMT_CH3_ERR_INT_CLR_M  (RMT_CH3_ERR_INT_CLR_V << RMT_CH3_ERR_INT_CLR_S)
#define RMT_CH3_ERR_INT_CLR_V  0x00000001U
#define RMT_CH3_ERR_INT_CLR_S  7
/** RMT_CH0_TX_THR_EVENT_INT_CLR:WT；位位置：[8]；默认值：0；设置此位以清除CHO_TX_THR_EVENT_INT中断。
 */
#define RMT_CH0_TX_THR_EVENT_INT_CLR    (BIT(8))
#define RMT_CH0_TX_THR_EVENT_INT_CLR_M  (RMT_CH0_TX_THR_EVENT_INT_CLR_V << RMT_CH0_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH0_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_CLR_S  8
/** RMT_CH1_TX_THR_EVENT_INT_CLR:WT；位位置：[9]；默认值：0；设置此位以清除CH1_TX_THR_EVENT_INT中断。
 */
#define RMT_CH1_TX_THR_EVENT_INT_CLR    (BIT(9))
#define RMT_CH1_TX_THR_EVENT_INT_CLR_M  (RMT_CH1_TX_THR_EVENT_INT_CLR_V << RMT_CH1_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH1_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_CLR_S  9
/** RMT_CH2_TX_THR_EVENT_INT_CLR:WT；位位置：[10]；默认值：0；设置此位以清除CH2_TX_THR_EVENT_INT中断。
 */
#define RMT_CH2_TX_THR_EVENT_INT_CLR    (BIT(10))
#define RMT_CH2_TX_THR_EVENT_INT_CLR_M  (RMT_CH2_TX_THR_EVENT_INT_CLR_V << RMT_CH2_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH2_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_CLR_S  10
/** RMT_CH3_TX_THR_EVENT_INT_CLR:WT；位位置：[11]；默认值：0；设置此位以清除CH3_TX_THR_EVENT_INT中断。
 */
#define RMT_CH3_TX_THR_EVENT_INT_CLR    (BIT(11))
#define RMT_CH3_TX_THR_EVENT_INT_CLR_M  (RMT_CH3_TX_THR_EVENT_INT_CLR_V << RMT_CH3_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH3_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_CLR_S  11
/** RMT_CH0_TX_lop_INT_CLR:WT；位位置：[12]；默认值：0；设置此位以清除CHO_TX_LOP_INT中断。
 */
#define RMT_CH0_TX_LOOP_INT_CLR    (BIT(12))
#define RMT_CH0_TX_LOOP_INT_CLR_M  (RMT_CH0_TX_LOOP_INT_CLR_V << RMT_CH0_TX_LOOP_INT_CLR_S)
#define RMT_CH0_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_CLR_S  12
/** RMT_CH1_TX_LOOP_INT_CLR:WT；位位置：[13]；默认值：0；设置该位以清除CH1_TX_LOP_INT中断。
 */
#define RMT_CH1_TX_LOOP_INT_CLR    (BIT(13))
#define RMT_CH1_TX_LOOP_INT_CLR_M  (RMT_CH1_TX_LOOP_INT_CLR_V << RMT_CH1_TX_LOOP_INT_CLR_S)
#define RMT_CH1_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_CLR_S  13
/** RMT_CH2_TX_LOOP_INT_CLR:WT；位位置：[14]；默认值：0；设置此位以清除CH2_TX_LOOP_INT中断。
 */
#define RMT_CH2_TX_LOOP_INT_CLR    (BIT(14))
#define RMT_CH2_TX_LOOP_INT_CLR_M  (RMT_CH2_TX_LOOP_INT_CLR_V << RMT_CH2_TX_LOOP_INT_CLR_S)
#define RMT_CH2_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_CLR_S  14
/** RMT_CH3_TX_LOOP_INT_CLR:WT；位位置：[15]；默认值：0；设置该位以清除CH_3_TX_LOOP_INT中断。
 */
#define RMT_CH3_TX_LOOP_INT_CLR    (BIT(15))
#define RMT_CH3_TX_LOOP_INT_CLR_M  (RMT_CH3_TX_LOOP_INT_CLR_V << RMT_CH3_TX_LOOP_INT_CLR_S)
#define RMT_CH3_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_CLR_S  15
/** RMT_CH4_RX_END_INT_CLR:WT；位位置：[16]；默认值：0；设置此位以清除H4_RX_END_INT中断。
 */
#define RMT_CH4_RX_END_INT_CLR    (BIT(16))
#define RMT_CH4_RX_END_INT_CLR_M  (RMT_CH4_RX_END_INT_CLR_V << RMT_CH4_RX_END_INT_CLR_S)
#define RMT_CH4_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH4_RX_END_INT_CLR_S  16
/** RMT_CH5_RX_END_INT_CLR:WT；位位置：[17]；默认值：0；设置此位以清除H5_RX_END_INT中断。
 */
#define RMT_CH5_RX_END_INT_CLR    (BIT(17))
#define RMT_CH5_RX_END_INT_CLR_M  (RMT_CH5_RX_END_INT_CLR_V << RMT_CH5_RX_END_INT_CLR_S)
#define RMT_CH5_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH5_RX_END_INT_CLR_S  17
/** RMT_CH6_RX_END_INT_CLR:WT；位位置：[18]；默认值：0；设置此位以清除CH6_RX_END_INT中断。
 */
#define RMT_CH6_RX_END_INT_CLR    (BIT(18))
#define RMT_CH6_RX_END_INT_CLR_M  (RMT_CH6_RX_END_INT_CLR_V << RMT_CH6_RX_END_INT_CLR_S)
#define RMT_CH6_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH6_RX_END_INT_CLR_S  18
/** RMT_CH7_RX_END_INT_CLR:WT；位位置：[19]；默认值：0；设置此位以清除H7_RX_END_INT中断。
 */
#define RMT_CH7_RX_END_INT_CLR    (BIT(19))
#define RMT_CH7_RX_END_INT_CLR_M  (RMT_CH7_RX_END_INT_CLR_V << RMT_CH7_RX_END_INT_CLR_S)
#define RMT_CH7_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH7_RX_END_INT_CLR_S  19
/** RMT_CH4_ERR_INT_CLR:WT；位位置：[20]；默认值：0；设置此位以清除H4_ERR_INT中断。
 */
#define RMT_CH4_ERR_INT_CLR    (BIT(20))
#define RMT_CH4_ERR_INT_CLR_M  (RMT_CH4_ERR_INT_CLR_V << RMT_CH4_ERR_INT_CLR_S)
#define RMT_CH4_ERR_INT_CLR_V  0x00000001U
#define RMT_CH4_ERR_INT_CLR_S  20
/** RMT_CH5_ERR_INT_CLR:WT；位位置：[21]；默认值：0；设置此位以清除H5_ERR_INT中断。
 */
#define RMT_CH5_ERR_INT_CLR    (BIT(21))
#define RMT_CH5_ERR_INT_CLR_M  (RMT_CH5_ERR_INT_CLR_V << RMT_CH5_ERR_INT_CLR_S)
#define RMT_CH5_ERR_INT_CLR_V  0x00000001U
#define RMT_CH5_ERR_INT_CLR_S  21
/** RMT_CH6_ERR_INT_CLR:WT；位位置：[22]；默认值：0；设置此位以清除CH6_ERROR_INT中断。
 */
#define RMT_CH6_ERR_INT_CLR    (BIT(22))
#define RMT_CH6_ERR_INT_CLR_M  (RMT_CH6_ERR_INT_CLR_V << RMT_CH6_ERR_INT_CLR_S)
#define RMT_CH6_ERR_INT_CLR_V  0x00000001U
#define RMT_CH6_ERR_INT_CLR_S  22
/** RMT_CH7_ERR_INT_CLR:WT；位位置：[23]；默认值：0；设置此位以清除H7_ERR_INT中断。
 */
#define RMT_CH7_ERR_INT_CLR    (BIT(23))
#define RMT_CH7_ERR_INT_CLR_M  (RMT_CH7_ERR_INT_CLR_V << RMT_CH7_ERR_INT_CLR_S)
#define RMT_CH7_ERR_INT_CLR_V  0x00000001U
#define RMT_CH7_ERR_INT_CLR_S  23
/** RMT_CH4_RX_tr_EVENT_INT_CLR:WT；位位置：[24]；默认值：0；设置此位以清除H4_RX_THR_EVENT_INT中断。
 */
#define RMT_CH4_RX_THR_EVENT_INT_CLR    (BIT(24))
#define RMT_CH4_RX_THR_EVENT_INT_CLR_M  (RMT_CH4_RX_THR_EVENT_INT_CLR_V << RMT_CH4_RX_THR_EVENT_INT_CLR_S)
#define RMT_CH4_RX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH4_RX_THR_EVENT_INT_CLR_S  24
/** RMT_CH5_RX_tr_EVENT_INT_CLR:WT；位位置：[25]；默认值：0；设置此位以清除H5_RX_THR_EVENT_INT中断。
 */
#define RMT_CH5_RX_THR_EVENT_INT_CLR    (BIT(25))
#define RMT_CH5_RX_THR_EVENT_INT_CLR_M  (RMT_CH5_RX_THR_EVENT_INT_CLR_V << RMT_CH5_RX_THR_EVENT_INT_CLR_S)
#define RMT_CH5_RX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH5_RX_THR_EVENT_INT_CLR_S  25
/** RMT_CH6_RX_tr_EVENT_INT_CLR:WT；位位置：[26]；默认值：0；设置此位以清除CH6_RX_THR_EVENT_INT中断。
 */
#define RMT_CH6_RX_THR_EVENT_INT_CLR    (BIT(26))
#define RMT_CH6_RX_THR_EVENT_INT_CLR_M  (RMT_CH6_RX_THR_EVENT_INT_CLR_V << RMT_CH6_RX_THR_EVENT_INT_CLR_S)
#define RMT_CH6_RX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH6_RX_THR_EVENT_INT_CLR_S  26
/** RMT_CH7_RX_THR_EVENT_INT_CLR:WT；位位置：[27]；默认值：0；设置此位以清除CH7_RX_THR_EVENT_INT中断。
 */
#define RMT_CH7_RX_THR_EVENT_INT_CLR    (BIT(27))
#define RMT_CH7_RX_THR_EVENT_INT_CLR_M  (RMT_CH7_RX_THR_EVENT_INT_CLR_V << RMT_CH7_RX_THR_EVENT_INT_CLR_S)
#define RMT_CH7_RX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH7_RX_THR_EVENT_INT_CLR_S  27
/** RMT_CH3_DMA_ACCESS_FAIL_INT_CLR:WT；位位置：[28]；默认值：0；设置此位以清除CH3_DMA_ACCESS_FAIL_INT中断。
 */
#define RMT_CH3_DMA_ACCESS_FAIL_INT_CLR    (BIT(28))
#define RMT_CH3_DMA_ACCESS_FAIL_INT_CLR_M  (RMT_CH3_DMA_ACCESS_FAIL_INT_CLR_V << RMT_CH3_DMA_ACCESS_FAIL_INT_CLR_S)
#define RMT_CH3_DMA_ACCESS_FAIL_INT_CLR_V  0x00000001U
#define RMT_CH3_DMA_ACCESS_FAIL_INT_CLR_S  28
/** RMT_CH7_DMA_ACCESS_FAIL_INT_CLR:WT；位位置：[29]；默认值：0；设置此位以清除CH7_DMA_ACCESS_FAIL_INT中断。
 */
#define RMT_CH7_DMA_ACCESS_FAIL_INT_CLR    (BIT(29))
#define RMT_CH7_DMA_ACCESS_FAIL_INT_CLR_M  (RMT_CH7_DMA_ACCESS_FAIL_INT_CLR_V << RMT_CH7_DMA_ACCESS_FAIL_INT_CLR_S)
#define RMT_CH7_DMA_ACCESS_FAIL_INT_CLR_V  0x00000001U
#define RMT_CH7_DMA_ACCESS_FAIL_INT_CLR_S  29

/** RMT_CH0CARRIER_DDUTY_REG寄存器通道0占空比配置寄存器
 */
#define RMT_CH0CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x80)
/** RMT_CARRIER_LOW_CH0:R/W；比特位置：[15:0]；默认值：64；该寄存器用于配置信道0的载波低电平时钟周期。
 */
#define RMT_CARRIER_LOW_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_M  (RMT_CARRIER_LOW_CH0_V << RMT_CARRIER_LOW_CH0_S)
#define RMT_CARRIER_LOW_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_S  0
/** RMT_CARRIER_HIGH_CH0:R/W；比特位置：[31:16]；默认值：64；该寄存器用于为信道0配置载波的高电平时钟周期。
 */
#define RMT_CARRIER_HIGH_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_M  (RMT_CARRIER_HIGH_CH0_V << RMT_CARRIER_HIGH_CH0_S)
#define RMT_CARRIER_HIGH_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_S  16

/** RMT_CH1CARRIER_DDUTY_REG寄存器通道1占空比配置寄存器
 */
#define RMT_CH1CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x84)
/** RMT_CARRIER_LOW_CH1:R/W；比特位置：[15:0]；默认值：64；该寄存器用于为信道1配置载波的低电平时钟周期。
 */
#define RMT_CARRIER_LOW_CH1    0x0000FFFFU
#define RMT_CARRIER_LOW_CH1_M  (RMT_CARRIER_LOW_CH1_V << RMT_CARRIER_LOW_CH1_S)
#define RMT_CARRIER_LOW_CH1_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH1_S  0
/** RMT_CARRIER_HIGH_CH1:R/W；比特位置：[31:16]；默认值：64；该寄存器用于为信道1配置载波的高电平时钟周期。
 */
#define RMT_CARRIER_HIGH_CH1    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH1_M  (RMT_CARRIER_HIGH_CH1_V << RMT_CARRIER_HIGH_CH1_S)
#define RMT_CARRIER_HIGH_CH1_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH1_S  16

/** RMT_CH2CARRIR_DUTY_REG寄存器通道2占空比配置寄存器
 */
#define RMT_CH2CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x88)
/** RMT_CARRIER_LOW_CH2:R/W；比特位置：[15:0]；默认值：64；该寄存器用于为信道2配置载波的低电平时钟周期。
 */
#define RMT_CARRIER_LOW_CH2    0x0000FFFFU
#define RMT_CARRIER_LOW_CH2_M  (RMT_CARRIER_LOW_CH2_V << RMT_CARRIER_LOW_CH2_S)
#define RMT_CARRIER_LOW_CH2_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH2_S  0
/** RMT_CARRIER_HIGH_CH2:R/W；比特位置：[31:16]；默认值：64；该寄存器用于为信道2配置载波的高电平时钟周期。
 */
#define RMT_CARRIER_HIGH_CH2    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH2_M  (RMT_CARRIER_HIGH_CH2_V << RMT_CARRIER_HIGH_CH2_S)
#define RMT_CARRIER_HIGH_CH2_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH2_S  16

/** RMT_CH3CARRIER_DUTY_REG寄存器通道3占空比配置寄存器
 */
#define RMT_CH3CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x8c)
/** RMT_CARRIER_LOW_CH3:R/W；比特位置：[15:0]；默认值：64；该寄存器用于为信道3配置载波的低电平时钟周期。
 */
#define RMT_CARRIER_LOW_CH3    0x0000FFFFU
#define RMT_CARRIER_LOW_CH3_M  (RMT_CARRIER_LOW_CH3_V << RMT_CARRIER_LOW_CH3_S)
#define RMT_CARRIER_LOW_CH3_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH3_S  0
/** RMT_CARRIER_HIGH_CH3:R/W；比特位置：[31:16]；默认值：64；该寄存器用于为信道3配置载波的高电平时钟周期。
 */
#define RMT_CARRIER_HIGH_CH3    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH3_M  (RMT_CARRIER_HIGH_CH3_V << RMT_CARRIER_HIGH_CH3_S)
#define RMT_CARRIER_HIGH_CH3_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH3_S  16

/** RMT_CH4_RX_CARRIR_RM_REG寄存器通道4载波移除寄存器
 */
#define RMT_CH4_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x90)
/** RMT_CARRIER_LOW_threshold_CH4:R/W；比特位置：[15:0]；默认值：0；对于信道4，载波调制模式中的低电平周期是（REG_RMT_REG_CARRIR_low_THRES_CH4+1）。
 */
#define RMT_CARRIER_LOW_THRES_CH4    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH4_M  (RMT_CARRIER_LOW_THRES_CH4_V << RMT_CARRIER_LOW_THRES_CH4_S)
#define RMT_CARRIER_LOW_THRES_CH4_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH4_S  0
/** RMT_CARRIER_HIGH_threshold_CH4:R/W；比特位置：[31:16]；默认值：0；对于信道4，载波调制模式中的高电平周期是（REG_RMT_REG_CARRIR_high_THRES_CH4+1）。
 */
#define RMT_CARRIER_HIGH_THRES_CH4    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH4_M  (RMT_CARRIER_HIGH_THRES_CH4_V << RMT_CARRIER_HIGH_THRES_CH4_S)
#define RMT_CARRIER_HIGH_THRES_CH4_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH4_S  16

/** RMT_CH5_RX_CARRIR_RM_REG寄存器通道5载波移除寄存器
 */
#define RMT_CH5_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x94)
/** RMT_CARRIER_LOW_threshold_CH5:R/W；比特位置：[15:0]；默认值：0；对于信道5，载波调制模式中的低电平周期是（REG_RMT_REG_CARRIR_low_THRES_CH5+1）。
 */
#define RMT_CARRIER_LOW_THRES_CH5    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH5_M  (RMT_CARRIER_LOW_THRES_CH5_V << RMT_CARRIER_LOW_THRES_CH5_S)
#define RMT_CARRIER_LOW_THRES_CH5_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH5_S  0
/** RMT_CARRIER_HIGH_threshold_CH5:R/W；比特位置：[31:16]；默认值：0；对于信道5，载波调制模式中的高电平周期是（REG_RMT_REG_CARRIR_high_THRES_CH5+1）。
 */
#define RMT_CARRIER_HIGH_THRES_CH5    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH5_M  (RMT_CARRIER_HIGH_THRES_CH5_V << RMT_CARRIER_HIGH_THRES_CH5_S)
#define RMT_CARRIER_HIGH_THRES_CH5_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH5_S  16

/** RMT_CH6_RX_CARRIR_RM_REG寄存器通道6载波移除寄存器
 */
#define RMT_CH6_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x98)
/** RMT_CARRIER_LOW_threshold_CH6:R/W；比特位置：[15:0]；默认值：0；对于信道6，载波调制模式中的低电平周期是（REG_RMT_REG_CARRIR_low_THRES_CH6+1）。
 */
#define RMT_CARRIER_LOW_THRES_CH6    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH6_M  (RMT_CARRIER_LOW_THRES_CH6_V << RMT_CARRIER_LOW_THRES_CH6_S)
#define RMT_CARRIER_LOW_THRES_CH6_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH6_S  0
/** RMT_CARRIER_HIGH_threshold_CH6:R/W；比特位置：[31:16]；默认值：0；对于信道6，载波调制模式中的高电平周期是（REG_RMT_REG_CARRIR_high_THRES_CH6+1）。
 */
#define RMT_CARRIER_HIGH_THRES_CH6    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH6_M  (RMT_CARRIER_HIGH_THRES_CH6_V << RMT_CARRIER_HIGH_THRES_CH6_S)
#define RMT_CARRIER_HIGH_THRES_CH6_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH6_S  16

/** RMT_CH7_RX_CARRIR_RM_REG寄存器通道7载波移除寄存器
 */
#define RMT_CH7_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x9c)
/** RMT_CARRIER_LOW_threshold_CH7:R/W；比特位置：[15:0]；默认值：0；对于信道7，载波调制模式中的低电平周期是（REG_RMT_REG_CARRIR_low_THRES_CH7+1）。
 */
#define RMT_CARRIER_LOW_THRES_CH7    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH7_M  (RMT_CARRIER_LOW_THRES_CH7_V << RMT_CARRIER_LOW_THRES_CH7_S)
#define RMT_CARRIER_LOW_THRES_CH7_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH7_S  0
/** RMT_CARRIER_HIGH_threshold_CH7:R/W；比特位置：[31:16]；默认值：0；对于信道7，载波调制模式中的高电平周期是（REG_RMT_REG_CARRIR_high_THRES_CH7+1）。
 */
#define RMT_CARRIER_HIGH_THRES_CH7    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH7_M  (RMT_CARRIER_HIGH_THRES_CH7_V << RMT_CARRIER_HIGH_THRES_CH7_S)
#define RMT_CARRIER_HIGH_THRES_CH7_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH7_S  16

/** RMT_CH0_TX_LIM_REG寄存器通道0 TX事件配置寄存器
 */
#define RMT_CH0_TX_LIM_REG (DR_REG_RMT_BASE + 0xa0)
/** RMT_TX_LIM_CH0:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置CHANNEL0可以发送的最大条目。
 */
#define RMT_TX_LIM_CH0    0x000001FFU
#define RMT_TX_LIM_CH0_M  (RMT_TX_LIM_CH0_V << RMT_TX_LIM_CH0_S)
#define RMT_TX_LIM_CH0_V  0x000001FFU
#define RMT_TX_LIM_CH0_S  0
/** RMT_TX_LOOP_NUM_CH0:R/W；比特位置：[18:9]；默认值：0；当tx_conti_mode有效时，此寄存器用于配置最大循环计数。
 */
#define RMT_TX_LOOP_NUM_CH0    0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_M  (RMT_TX_LOOP_NUM_CH0_V << RMT_TX_LOOP_NUM_CH0_S)
#define RMT_TX_LOOP_NUM_CH0_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_S  9
/** RMT_TX_LOOP_CNT_EN_CH0:R/W；位位置：[19]；默认值：0；此寄存器是循环计数的启用位。
 */
#define RMT_TX_LOOP_CNT_EN_CH0    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH0_M  (RMT_TX_LOOP_CNT_EN_CH0_V << RMT_TX_LOOP_CNT_EN_CH0_S)
#define RMT_TX_LOOP_CNT_EN_CH0_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH0_S  19
/** RMT_LOOP_COUNT_RESET_CH0:WT；位位置：[20]；默认值：0；当tx_conti_mode有效时，此寄存器用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH0    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH0_M  (RMT_LOOP_COUNT_RESET_CH0_V << RMT_LOOP_COUNT_RESET_CH0_S)
#define RMT_LOOP_COUNT_RESET_CH0_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH0_S  20
/** RMT_LOOP_top_EN_CH0:R/W；位位置：[21]；默认值：0；该位用于在循环计数器计数到CHANNEL0的循环数后启用循环发送停止功能。
 */
#define RMT_LOOP_STOP_EN_CH0    (BIT(21))
#define RMT_LOOP_STOP_EN_CH0_M  (RMT_LOOP_STOP_EN_CH0_V << RMT_LOOP_STOP_EN_CH0_S)
#define RMT_LOOP_STOP_EN_CH0_V  0x00000001U
#define RMT_LOOP_STOP_EN_CH0_S  21

/** RMT_CH1_TX_LIM_REG寄存器通道1 TX事件配置寄存器
 */
#define RMT_CH1_TX_LIM_REG (DR_REG_RMT_BASE + 0xa4)
/** RMT_TX_LIM_CH1:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道1可以发送的最大条目。
 */
#define RMT_TX_LIM_CH1    0x000001FFU
#define RMT_TX_LIM_CH1_M  (RMT_TX_LIM_CH1_V << RMT_TX_LIM_CH1_S)
#define RMT_TX_LIM_CH1_V  0x000001FFU
#define RMT_TX_LIM_CH1_S  0
/** RMT_TX_LOOP_NUM_CH1:R/W；比特位置：[18:9]；默认值：0；当tx_conti_mode有效时，此寄存器用于配置最大循环计数。
 */
#define RMT_TX_LOOP_NUM_CH1    0x000003FFU
#define RMT_TX_LOOP_NUM_CH1_M  (RMT_TX_LOOP_NUM_CH1_V << RMT_TX_LOOP_NUM_CH1_S)
#define RMT_TX_LOOP_NUM_CH1_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH1_S  9
/** RMT_TX_LOOP_CNT_EN_CH1:R/W；位位置：[19]；默认值：0；此寄存器是循环计数的启用位。
 */
#define RMT_TX_LOOP_CNT_EN_CH1    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH1_M  (RMT_TX_LOOP_CNT_EN_CH1_V << RMT_TX_LOOP_CNT_EN_CH1_S)
#define RMT_TX_LOOP_CNT_EN_CH1_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH1_S  19
/** RMT_LOOP_COUNT_RESET_CH1:WT；位位置：[20]；默认值：0；当tx_conti_mode有效时，此寄存器用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH1    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH1_M  (RMT_LOOP_COUNT_RESET_CH1_V << RMT_LOOP_COUNT_RESET_CH1_S)
#define RMT_LOOP_COUNT_RESET_CH1_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH1_S  20
/** RMT_LOOP_top_EN_CH1:R/W；位位置：[21]；默认值：0；该位用于在循环计数器计数到信道1的循环数后启用循环发送停止功能。
 */
#define RMT_LOOP_STOP_EN_CH1    (BIT(21))
#define RMT_LOOP_STOP_EN_CH1_M  (RMT_LOOP_STOP_EN_CH1_V << RMT_LOOP_STOP_EN_CH1_S)
#define RMT_LOOP_STOP_EN_CH1_V  0x00000001U
#define RMT_LOOP_STOP_EN_CH1_S  21

/** RMT_CH2_TX_LIM_REG寄存器通道2 TX事件配置寄存器
 */
#define RMT_CH2_TX_LIM_REG (DR_REG_RMT_BASE + 0xa8)
/** RMT_TX_LIM_CH2:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道2可以发送的最大条目。
 */
#define RMT_TX_LIM_CH2    0x000001FFU
#define RMT_TX_LIM_CH2_M  (RMT_TX_LIM_CH2_V << RMT_TX_LIM_CH2_S)
#define RMT_TX_LIM_CH2_V  0x000001FFU
#define RMT_TX_LIM_CH2_S  0
/** RMT_TX_LOOP_NUM_CH2:R/W；比特位置：[18:9]；默认值：0；当tx_conti_mode有效时，此寄存器用于配置最大循环计数。
 */
#define RMT_TX_LOOP_NUM_CH2    0x000003FFU
#define RMT_TX_LOOP_NUM_CH2_M  (RMT_TX_LOOP_NUM_CH2_V << RMT_TX_LOOP_NUM_CH2_S)
#define RMT_TX_LOOP_NUM_CH2_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH2_S  9
/** RMT_TX_LOOP_CNT_EN_CH2:R/W；位位置：[19]；默认值：0；此寄存器是循环计数的启用位。
 */
#define RMT_TX_LOOP_CNT_EN_CH2    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH2_M  (RMT_TX_LOOP_CNT_EN_CH2_V << RMT_TX_LOOP_CNT_EN_CH2_S)
#define RMT_TX_LOOP_CNT_EN_CH2_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH2_S  19
/** RMT_LOOP_COUNT_RESET_CH2:WT；位位置：[20]；默认值：0；当tx_conti_mode有效时，此寄存器用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH2    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH2_M  (RMT_LOOP_COUNT_RESET_CH2_V << RMT_LOOP_COUNT_RESET_CH2_S)
#define RMT_LOOP_COUNT_RESET_CH2_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH2_S  20
/** RMT_LOOP_top_EN_CH2:R/W；位位置：[21]；默认值：0；该位用于在循环计数器计数到信道2的循环数后启用循环发送停止功能。
 */
#define RMT_LOOP_STOP_EN_CH2    (BIT(21))
#define RMT_LOOP_STOP_EN_CH2_M  (RMT_LOOP_STOP_EN_CH2_V << RMT_LOOP_STOP_EN_CH2_S)
#define RMT_LOOP_STOP_EN_CH2_V  0x00000001U
#define RMT_LOOP_STOP_EN_CH2_S  21

/** RMT_CH3_TX_LIM_REG寄存器通道3 TX事件配置寄存器
 */
#define RMT_CH3_TX_LIM_REG (DR_REG_RMT_BASE + 0xac)
/** RMT_TX_LIM_CH3:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道3可以发送的最大条目。
 */
#define RMT_TX_LIM_CH3    0x000001FFU
#define RMT_TX_LIM_CH3_M  (RMT_TX_LIM_CH3_V << RMT_TX_LIM_CH3_S)
#define RMT_TX_LIM_CH3_V  0x000001FFU
#define RMT_TX_LIM_CH3_S  0
/** RMT_TX_LOOP_NUM_CH3:R/W；比特位置：[18:9]；默认值：0；当tx_conti_mode有效时，此寄存器用于配置最大循环计数。
 */
#define RMT_TX_LOOP_NUM_CH3    0x000003FFU
#define RMT_TX_LOOP_NUM_CH3_M  (RMT_TX_LOOP_NUM_CH3_V << RMT_TX_LOOP_NUM_CH3_S)
#define RMT_TX_LOOP_NUM_CH3_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH3_S  9
/** RMT_TX_LOOP_CNT_EN_CH3:R/W；位位置：[19]；默认值：0；此寄存器是循环计数的启用位。
 */
#define RMT_TX_LOOP_CNT_EN_CH3    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH3_M  (RMT_TX_LOOP_CNT_EN_CH3_V << RMT_TX_LOOP_CNT_EN_CH3_S)
#define RMT_TX_LOOP_CNT_EN_CH3_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH3_S  19
/** RMT_LOOP_COUNT_RESET_CH3:WT；位位置：[20]；默认值：0；当tx_conti_mode有效时，此寄存器用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH3    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH3_M  (RMT_LOOP_COUNT_RESET_CH3_V << RMT_LOOP_COUNT_RESET_CH3_S)
#define RMT_LOOP_COUNT_RESET_CH3_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH3_S  20
/** RMT_LOOP_top_EN_CH3:R/W；位位置：[21]；默认值：0；该位用于在循环计数器计数到信道3的循环数后启用循环发送停止功能。
 */
#define RMT_LOOP_STOP_EN_CH3    (BIT(21))
#define RMT_LOOP_STOP_EN_CH3_M  (RMT_LOOP_STOP_EN_CH3_V << RMT_LOOP_STOP_EN_CH3_S)
#define RMT_LOOP_STOP_EN_CH3_V  0x00000001U
#define RMT_LOOP_STOP_EN_CH3_S  21

/** RMT_CH4_RX_LIM_REG寄存器通道4 RX事件配置寄存器
 */
#define RMT_CH4_RX_LIM_REG (DR_REG_RMT_BASE + 0xb0)
/** RMT_CH4_RX_LIM_REG:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道4可以接收的最大条目。
 */
#define RMT_CH4_RX_LIM_REG    0x000001FFU
#define RMT_CH4_RX_LIM_REG_M  (RMT_CH4_RX_LIM_REG_V << RMT_CH4_RX_LIM_REG_S)
#define RMT_CH4_RX_LIM_REG_V  0x000001FFU
#define RMT_CH4_RX_LIM_REG_S  0

/** RMT_CH5_RX_LIM_REG寄存器通道5 RX事件配置寄存器
 */
#define RMT_CH5_RX_LIM_REG (DR_REG_RMT_BASE + 0xb4)
/** RMT_CH5_RX_LIM_REG:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道5可以接收的最大条目。
 */
#define RMT_CH5_RX_LIM_REG    0x000001FFU
#define RMT_CH5_RX_LIM_REG_M  (RMT_CH5_RX_LIM_REG_V << RMT_CH5_RX_LIM_REG_S)
#define RMT_CH5_RX_LIM_REG_V  0x000001FFU
#define RMT_CH5_RX_LIM_REG_S  0

/** RMT_CH6_RX_LIM_REG寄存器通道6 RX事件配置寄存器
 */
#define RMT_CH6_RX_LIM_REG (DR_REG_RMT_BASE + 0xb8)
/** RMT_CH6_RX_LIM_REG:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道6可以接收的最大条目。
 */
#define RMT_CH6_RX_LIM_REG    0x000001FFU
#define RMT_CH6_RX_LIM_REG_M  (RMT_CH6_RX_LIM_REG_V << RMT_CH6_RX_LIM_REG_S)
#define RMT_CH6_RX_LIM_REG_V  0x000001FFU
#define RMT_CH6_RX_LIM_REG_S  0

/** RMT_CH7_RX_LIM_REG寄存器通道7 RX事件配置寄存器
 */
#define RMT_CH7_RX_LIM_REG (DR_REG_RMT_BASE + 0xbc)
/** RMT_CH7_RX_LIM_REG:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置信道7可以接收的最大条目。
 */
#define RMT_CH7_RX_LIM_REG    0x000001FFU
#define RMT_CH7_RX_LIM_REG_M  (RMT_CH7_RX_LIM_REG_V << RMT_CH7_RX_LIM_REG_S)
#define RMT_CH7_RX_LIM_REG_V  0x000001FFU
#define RMT_CH7_RX_LIM_REG_S  0

/** RMT_SYS_CONF_REG寄存器RMT apb配置寄存器
 */
#define RMT_SYS_CONF_REG (DR_REG_RMT_BASE + 0xc0)
/** RMT_APB_FIFO掩码：R/W；位位置：[0]；默认值：0；1’1：直接访问内存。1’0：通过FIFO访问内存。
 */
#define RMT_APB_FIFO_MASK    (BIT(0))
#define RMT_APB_FIFO_MASK_M  (RMT_APB_FIFO_MASK_V << RMT_APB_FIFO_MASK_S)
#define RMT_APB_FIFO_MASK_V  0x00000001U
#define RMT_APB_FIFO_MASK_S  0
/** RMT_MEM_CLK_FORCE_ON:R/W；位位置：[1]；默认值：0；设置此位以启用RMT内存的时钟。
 */
#define RMT_MEM_CLK_FORCE_ON    (BIT(1))
#define RMT_MEM_CLK_FORCE_ON_M  (RMT_MEM_CLK_FORCE_ON_V << RMT_MEM_CLK_FORCE_ON_S)
#define RMT_MEM_CLK_FORCE_ON_V  0x00000001U
#define RMT_MEM_CLK_FORCE_ON_S  1
/** RMT_MEM_FORCE_PD:R/W；位位置：[2]；默认值：0；设置此位以关闭RMT内存。
 */
#define RMT_MEM_FORCE_PD    (BIT(2))
#define RMT_MEM_FORCE_PD_M  (RMT_MEM_FORCE_PD_V << RMT_MEM_FORCE_PD_S)
#define RMT_MEM_FORCE_PD_V  0x00000001U
#define RMT_MEM_FORCE_PD_S  2
/** RMT_MEM_FORCE_PU:R/W；位位置：[3]；默认值：0；1： 禁用RMT记忆灯睡眠断电功能。0：当RMT处于浅睡眠模式时，关闭RMT内存。
 */
#define RMT_MEM_FORCE_PU    (BIT(3))
#define RMT_MEM_FORCE_PU_M  (RMT_MEM_FORCE_PU_V << RMT_MEM_FORCE_PU_S)
#define RMT_MEM_FORCE_PU_V  0x00000001U
#define RMT_MEM_FORCE_PU_S  3
/** RMT_SCLK_DIV_NUM:R/W；位位置：[11:4]；默认值：1；分数除数的整数部分
 */
#define RMT_SCLK_DIV_NUM    0x000000FFU
#define RMT_SCLK_DIV_NUM_M  (RMT_SCLK_DIV_NUM_V << RMT_SCLK_DIV_NUM_S)
#define RMT_SCLK_DIV_NUM_V  0x000000FFU
#define RMT_SCLK_DIV_NUM_S  4
/** RMT_SCLK_DIV_A:R/W；比特位置：[17:12]；默认值：0；分数除数的分数部分的分子
 */
#define RMT_SCLK_DIV_A    0x0000003FU
#define RMT_SCLK_DIV_A_M  (RMT_SCLK_DIV_A_V << RMT_SCLK_DIV_A_S)
#define RMT_SCLK_DIV_A_V  0x0000003FU
#define RMT_SCLK_DIV_A_S  12
/** RMT_SCLK_DIV_B:R/W；比特位置：[23:18]；默认值：0；分数除数的分数部分的分母
 */
#define RMT_SCLK_DIV_B    0x0000003FU
#define RMT_SCLK_DIV_B_M  (RMT_SCLK_DIV_B_V << RMT_SCLK_DIV_B_S)
#define RMT_SCLK_DIV_B_V  0x0000003FU
#define RMT_SCLK_DIV_B_S  18
/** RMT_SCLK_SEL:R/W；位位置：[25:24]；默认值：1；选择rmtsclk的时钟源。1： CLK_80Mhz；2： CLK_8MHz；2： XTAL公司
 */
#define RMT_SCLK_SEL    0x00000003U
#define RMT_SCLK_SEL_M  (RMT_SCLK_SEL_V << RMT_SCLK_SEL_S)
#define RMT_SCLK_SEL_V  0x00000003U
#define RMT_SCLK_SEL_S  24
/** RMT_SCLK_ACTIVE:R/W；位位置：[26]；默认值：1；rmt_sclk开关
 */
#define RMT_SCLK_ACTIVE    (BIT(26))
#define RMT_SCLK_ACTIVE_M  (RMT_SCLK_ACTIVE_V << RMT_SCLK_ACTIVE_S)
#define RMT_SCLK_ACTIVE_V  0x00000001U
#define RMT_SCLK_ACTIVE_S  26
/** RMT_CLK_EN:R/W；位位置：[31]；默认值：0；RMT寄存器时钟门启用信号。1： 给寄存器的驱动时钟加电。0：关闭寄存器的驱动时钟
 */
#define RMT_CLK_EN    (BIT(31))
#define RMT_CLK_EN_M  (RMT_CLK_EN_V << RMT_CLK_EN_S)
#define RMT_CLK_EN_V  0x00000001U
#define RMT_CLK_EN_S  31

/** RMT_TX_SIM_REG寄存器RMT TX同步寄存器
 */
#define RMT_TX_SIM_REG (DR_REG_RMT_BASE + 0xc4)
/** RMT_TX_SIM_CH0:R/W；位位置：[0]；默认值：0；设置此位以启用CHANNEL0开始与其他启用的信道同步发送数据。
 */
#define RMT_TX_SIM_CH0    (BIT(0))
#define RMT_TX_SIM_CH0_M  (RMT_TX_SIM_CH0_V << RMT_TX_SIM_CH0_S)
#define RMT_TX_SIM_CH0_V  0x00000001U
#define RMT_TX_SIM_CH0_S  0
/** RMT_TX_SIM_CH1:R/W；位位置：[1]；默认值：0；设置此位以启用CHANNEL1开始与其他启用的信道同步发送数据。
 */
#define RMT_TX_SIM_CH1    (BIT(1))
#define RMT_TX_SIM_CH1_M  (RMT_TX_SIM_CH1_V << RMT_TX_SIM_CH1_S)
#define RMT_TX_SIM_CH1_V  0x00000001U
#define RMT_TX_SIM_CH1_S  1
/** RMT_TX_SIM_CH2:R/W；位位置：[2]；默认值：0；设置此位以启用CHANNEL2开始与其他启用的信道同步发送数据。
 */
#define RMT_TX_SIM_CH2    (BIT(2))
#define RMT_TX_SIM_CH2_M  (RMT_TX_SIM_CH2_V << RMT_TX_SIM_CH2_S)
#define RMT_TX_SIM_CH2_V  0x00000001U
#define RMT_TX_SIM_CH2_S  2
/** RMT_TX_SIM_CH3:R/W；位位置：[3]；默认值：0；设置此位以启用CHANNEL3开始与其他启用的信道同步发送数据。
 */
#define RMT_TX_SIM_CH3    (BIT(3))
#define RMT_TX_SIM_CH3_M  (RMT_TX_SIM_CH3_V << RMT_TX_SIM_CH3_S)
#define RMT_TX_SIM_CH3_V  0x00000001U
#define RMT_TX_SIM_CH3_S  3
/** RMT_TX_SIM_EN:R/W；位位置：[4]；默认值：0；此寄存器用于使多个通道开始同步发送数据。
 */
#define RMT_TX_SIM_EN    (BIT(4))
#define RMT_TX_SIM_EN_M  (RMT_TX_SIM_EN_V << RMT_TX_SIM_EN_S)
#define RMT_TX_SIM_EN_V  0x00000001U
#define RMT_TX_SIM_EN_S  4

/** RMT_REF_CNT_RST_REG寄存器RMT时钟分频器复位寄存器
 */
#define RMT_REF_CNT_RST_REG (DR_REG_RMT_BASE + 0xc8)
/** RMT_REF_CNT_RST_CH0:WT；位位置：[0]；默认值：0；该寄存器用于重置信道0的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH0    (BIT(0))
#define RMT_REF_CNT_RST_CH0_M  (RMT_REF_CNT_RST_CH0_V << RMT_REF_CNT_RST_CH0_S)
#define RMT_REF_CNT_RST_CH0_V  0x00000001U
#define RMT_REF_CNT_RST_CH0_S  0
/** RMT_REF_CNT_RST_CH1:WT；位位置：[1]；默认值：0；该寄存器用于重置信道1的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH1    (BIT(1))
#define RMT_REF_CNT_RST_CH1_M  (RMT_REF_CNT_RST_CH1_V << RMT_REF_CNT_RST_CH1_S)
#define RMT_REF_CNT_RST_CH1_V  0x00000001U
#define RMT_REF_CNT_RST_CH1_S  1
/** RMT_REF_CNT_RST_CH2:WT；位位置：[2]；默认值：0；该寄存器用于重置信道2的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH2    (BIT(2))
#define RMT_REF_CNT_RST_CH2_M  (RMT_REF_CNT_RST_CH2_V << RMT_REF_CNT_RST_CH2_S)
#define RMT_REF_CNT_RST_CH2_V  0x00000001U
#define RMT_REF_CNT_RST_CH2_S  2
/** RMT_REF_CNT_RST_CH3:WT；位位置：[3]；默认值：0；该寄存器用于重置信道3的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH3    (BIT(3))
#define RMT_REF_CNT_RST_CH3_M  (RMT_REF_CNT_RST_CH3_V << RMT_REF_CNT_RST_CH3_S)
#define RMT_REF_CNT_RST_CH3_V  0x00000001U
#define RMT_REF_CNT_RST_CH3_S  3
/** RMT_REF_CNT_RST_CH4:WT；位位置：[4]；默认值：0；该寄存器用于重置信道4的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH4    (BIT(4))
#define RMT_REF_CNT_RST_CH4_M  (RMT_REF_CNT_RST_CH4_V << RMT_REF_CNT_RST_CH4_S)
#define RMT_REF_CNT_RST_CH4_V  0x00000001U
#define RMT_REF_CNT_RST_CH4_S  4
/** RMT_REF_CNT_RST_CH5:WT；位位置：[5]；默认值：0；该寄存器用于重置信道5的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH5    (BIT(5))
#define RMT_REF_CNT_RST_CH5_M  (RMT_REF_CNT_RST_CH5_V << RMT_REF_CNT_RST_CH5_S)
#define RMT_REF_CNT_RST_CH5_V  0x00000001U
#define RMT_REF_CNT_RST_CH5_S  5
/** RMT_REF_CNT_RST_CH6:WT；位位置：[6]；默认值：0；该寄存器用于重置信道6的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH6    (BIT(6))
#define RMT_REF_CNT_RST_CH6_M  (RMT_REF_CNT_RST_CH6_V << RMT_REF_CNT_RST_CH6_S)
#define RMT_REF_CNT_RST_CH6_V  0x00000001U
#define RMT_REF_CNT_RST_CH6_S  6
/** RMT_REF_CNT_RST_CH7:WT；位位置：[7]；默认值：0；该寄存器用于重置信道7的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH7    (BIT(7))
#define RMT_REF_CNT_RST_CH7_M  (RMT_REF_CNT_RST_CH7_V << RMT_REF_CNT_RST_CH7_S)
#define RMT_REF_CNT_RST_CH7_V  0x00000001U
#define RMT_REF_CNT_RST_CH7_S  7

/** RMT_DATE_REG寄存器RMT版本寄存器
 */
#define RMT_DATE_REG (DR_REG_RMT_BASE + 0xcc)
/** RMT_DATE:R/W；位位置：[27:0]；默认值：34607489；这是版本寄存器。
 */
#define RMT_DATE    0x0FFFFFFFU
#define RMT_DATE_M  (RMT_DATE_V << RMT_DATE_S)
#define RMT_DATE_V  0x0FFFFFFFU
#define RMT_DATE_S  0

#ifdef __cplusplus
}
#endif

