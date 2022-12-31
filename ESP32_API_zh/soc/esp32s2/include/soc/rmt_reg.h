/**
 * SPDX文件版权所有文本：2022 Espressif Systems（上海）有限公司
 *
 *  SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** RMT_CH0DATA_REG寄存器通过APB FIFO读取和写入通道0的数据
 */
#define RMT_CH0DATA_REG (DR_REG_RMT_BASE + 0x0)
/** RMT_CH0_DATA:RO；位位置：[31:0]；默认值：0；该寄存器用于通过APB FIFO读取和写入通道0的数据。
 */
#define RMT_CH0_DATA    0xFFFFFFFFU
#define RMT_CH0_DATA_M  (RMT_CH0_DATA_V << RMT_CH0_DATA_S)
#define RMT_CH0_DATA_V  0xFFFFFFFFU
#define RMT_CH0_DATA_S  0

/** RMT_CH1DATA_REG寄存器通过APB FIFO读取和写入通道1的数据
 */
#define RMT_CH1DATA_REG (DR_REG_RMT_BASE + 0x4)
/** RMT_CH0_DATA:RO；位位置：[31:0]；默认值：0；该寄存器用于通过APB FIFO读取和写入通道1的数据。
 */
#define RMT_CH0_DATA    0xFFFFFFFFU
#define RMT_CH0_DATA_M  (RMT_CH0_DATA_V << RMT_CH0_DATA_S)
#define RMT_CH0_DATA_V  0xFFFFFFFFU
#define RMT_CH0_DATA_S  0

/** RMT_CH2DATA_REG寄存器通过APB FIFO读取和写入通道2的数据
 */
#define RMT_CH2DATA_REG (DR_REG_RMT_BASE + 0x8)
/** RMT_CH0_DATA:RO；位位置：[31:0]；默认值：0；该寄存器用于通过APB FIFO读取和写入通道2的数据。
 */
#define RMT_CH0_DATA    0xFFFFFFFFU
#define RMT_CH0_DATA_M  (RMT_CH0_DATA_V << RMT_CH0_DATA_S)
#define RMT_CH0_DATA_V  0xFFFFFFFFU
#define RMT_CH0_DATA_S  0

/** RMT_CH3DATA_REG寄存器通过APB FIFO读取和写入通道3的数据
 */
#define RMT_CH3DATA_REG (DR_REG_RMT_BASE + 0xc)
/** RMT_CH0_DATA:RO；位位置：[31:0]；默认值：0；该寄存器用于通过APB FIFO读取和写入通道3的数据。
 */
#define RMT_CH0_DATA    0xFFFFFFFFU
#define RMT_CH0_DATA_M  (RMT_CH0_DATA_V << RMT_CH0_DATA_S)
#define RMT_CH0_DATA_V  0xFFFFFFFFU
#define RMT_CH0_DATA_S  0

/** RMT_CH0CONF0_REG寄存器通道0配置寄存器0
 */
#define RMT_CH0CONF0_REG (DR_REG_RMT_BASE + 0x10)
/** RMT_DIV_CNT_CH0:R/W；位位置：[7:0]；默认值：2；此字段用于配置信道0的时钟分频器。
 */
#define RMT_DIV_CNT_CH0    0x000000FFU
#define RMT_DIV_CNT_CH0_M  (RMT_DIV_CNT_CH0_V << RMT_DIV_CNT_CH0_S)
#define RMT_DIV_CNT_CH0_V  0x000000FFU
#define RMT_DIV_CNT_CH0_S  0
/** RMT_IDLE_THRES_CH0:R/W；比特位置：[23:8]；默认值：4096；当在比该字段值更长的连续时钟周期内没有检测到输入信号上的边沿时，接收结束。
 */
#define RMT_IDLE_THRES_CH0    0x0000FFFFU
#define RMT_IDLE_THRES_CH0_M  (RMT_IDLE_THRES_CH0_V << RMT_IDLE_THRES_CH0_S)
#define RMT_IDLE_THRES_CH0_V  0x0000FFFFU
#define RMT_IDLE_THRES_CH0_S  8
/** RMT_MEM_SIZE_CH0:R/W；比特位置：[26:24]；默认值：1；此字段用于配置分配给信道0的最大块。有效范围为1~4-0。
 */
#define RMT_MEM_SIZE_CH0    0x00000007U
#define RMT_MEM_SIZE_CH0_M  (RMT_MEM_SIZE_CH0_V << RMT_MEM_SIZE_CH0_S)
#define RMT_MEM_SIZE_CH0_V  0x00000007U
#define RMT_MEM_SIZE_CH0_S  24
/** RMT_CARRIER_EFF_EN_CH0:R/W；位位置：[27]；默认值：1；1： 仅在信道0的数据发送状态下对输出信号添加载波调制。0：在信道0所有状态下对信号添加载波调变。这里的状态包括空闲状态（ST_idle）、从RAM读取数据（ST_RD_MEM）和发送存储在RAM中的数据（ST_SEND）。仅当RMT_CARRIR_EN_CH0设置为1时有效。
 */
#define RMT_CARRIER_EFF_EN_CH0    (BIT(27))
#define RMT_CARRIER_EFF_EN_CH0_M  (RMT_CARRIER_EFF_EN_CH0_V << RMT_CARRIER_EFF_EN_CH0_S)
#define RMT_CARRIER_EFF_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EFF_EN_CH0_S  27
/** RMT_CARRIER_EN_CH0:R/W；位位置：[28]；默认值：1；此位用于启用信道0.1的载波调制：在输出信号上添加载波调制。0：输出信号无载波调制。
 */
#define RMT_CARRIER_EN_CH0    (BIT(28))
#define RMT_CARRIER_EN_CH0_M  (RMT_CARRIER_EN_CH0_V << RMT_CARRIER_EN_CH0_S)
#define RMT_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EN_CH0_S  28
/** RMT_CARRIER_OUT_LV_CH0:R/W；位位置：[29]；默认值：1；该位用于配置信道0的载波位置。
 *
 *  1’0：在低电平输出信号上添加载波。
 *
 *  1'h1：在高电平输出信号上添加载波。
 */
#define RMT_CARRIER_OUT_LV_CH0    (BIT(29))
#define RMT_CARRIER_OUT_LV_CH0_M  (RMT_CARRIER_OUT_LV_CH0_V << RMT_CARRIER_OUT_LV_CH0_S)
#define RMT_CARRIER_OUT_LV_CH0_V  0x00000001U
#define RMT_CARRIER_OUT_LV_CH0_S  29

/** RMT_CH0CONF1_REG寄存器通道0配置寄存器1
 */
#define RMT_CH0CONF1_REG (DR_REG_RMT_BASE + 0x14)
/** RMT_TX_START_CH0:R/W；位位置：[0]；默认值：0；设置此位以开始在通道0上发送数据。
 */
#define RMT_TX_START_CH0    (BIT(0))
#define RMT_TX_START_CH0_M  (RMT_TX_START_CH0_V << RMT_TX_START_CH0_S)
#define RMT_TX_START_CH0_V  0x00000001U
#define RMT_TX_START_CH0_S  0
/** RMT_RX_EN_CH0:R/W；位位置：[1]；默认值：0；设置此位以使接收器能够在信道0上接收数据。
 */
#define RMT_RX_EN_CH0    (BIT(1))
#define RMT_RX_EN_CH0_M  (RMT_RX_EN_CH0_V << RMT_RX_EN_CH0_S)
#define RMT_RX_EN_CH0_V  0x00000001U
#define RMT_RX_EN_CH0_S  1
/** RMT_MEM_WR_RST_CH0:WO；位位置：[2]；默认值：0；设置此位以重置接收器为通道0访问的RAM写入地址。
 */
#define RMT_MEM_WR_RST_CH0    (BIT(2))
#define RMT_MEM_WR_RST_CH0_M  (RMT_MEM_WR_RST_CH0_V << RMT_MEM_WR_RST_CH0_S)
#define RMT_MEM_WR_RST_CH0_V  0x00000001U
#define RMT_MEM_WR_RST_CH0_S  2
/** RMT_MEM_RD_RST_CH0:WO；位位置：[3]；默认值：0；设置此位以重置发射器为通道0访问的RAM读取地址。
 */
#define RMT_MEM_RD_RST_CH0    (BIT(3))
#define RMT_MEM_RD_RST_CH0_M  (RMT_MEM_RD_RST_CH0_V << RMT_MEM_RD_RST_CH0_S)
#define RMT_MEM_RD_RST_CH0_V  0x00000001U
#define RMT_MEM_RD_RST_CH0_S  3
/** RMT_APB_MEM_RST_CH0:WO；位位置：[4]；默认值：0；设置此位以通过访问apb fifo重置通道0的W/R ram地址。
 */
#define RMT_APB_MEM_RST_CH0    (BIT(4))
#define RMT_APB_MEM_RST_CH0_M  (RMT_APB_MEM_RST_CH0_V << RMT_APB_MEM_RST_CH0_S)
#define RMT_APB_MEM_RST_CH0_V  0x00000001U
#define RMT_APB_MEM_RST_CH0_S  4
/** RMT_MEM_OWNER_CH0:R/W；位位置：[5]；默认值：1；此位标记通道0的RAM块的所有权。
 *
 *  1’1：接收器正在使用RAM。
 *
 *  1’0：发射器正在使用RAM。
 */
#define RMT_MEM_OWNER_CH0    (BIT(5))
#define RMT_MEM_OWNER_CH0_M  (RMT_MEM_OWNER_CH0_V << RMT_MEM_OWNER_CH0_S)
#define RMT_MEM_OWNER_CH0_V  0x00000001U
#define RMT_MEM_OWNER_CH0_S  5
/** RMT_TX_CONTI_MODE_CH0:R/W；位位置：[6]；默认值：0；设置此位以从信道0中的第一个数据重新开始连续节点中的传输。
 */
#define RMT_TX_CONTI_MODE_CH0    (BIT(6))
#define RMT_TX_CONTI_MODE_CH0_M  (RMT_TX_CONTI_MODE_CH0_V << RMT_TX_CONTI_MODE_CH0_S)
#define RMT_TX_CONTI_MODE_CH0_V  0x00000001U
#define RMT_TX_CONTI_MODE_CH0_S  6
/** RMT_RX滤波器_ EN _ CH0：R/W；位位置：[7]；默认值：0；设置此位以启用信道0的接收机滤波器。
 */
#define RMT_RX_FILTER_EN_CH0    (BIT(7))
#define RMT_RX_FILTER_EN_CH0_M  (RMT_RX_FILTER_EN_CH0_V << RMT_RX_FILTER_EN_CH0_S)
#define RMT_RX_FILTER_EN_CH0_V  0x00000001U
#define RMT_RX_FILTER_EN_CH0_S  7
/** RMT_RX滤波器阈值CH0:R/W；比特位置：[15:8]；默认值：15；在接收模式下，当输入脉冲的宽度小于RMT_RX_FILTER_THRES_CH0 APB时钟周期时，将此字段设置为忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_CH0    0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_M  (RMT_RX_FILTER_THRES_CH0_V << RMT_RX_FILTER_THRES_CH0_S)
#define RMT_RX_FILTER_THRES_CH0_V  0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_S  8
/** RMT_CHK_RX_CARRIER_EN_CH0:R/W；位位置：[16]；默认值：0；当为信道0启用载波调制时，设置此位以启用存储器环路读取模式。
 */
#define RMT_CHK_RX_CARRIER_EN_CH0    (BIT(16))
#define RMT_CHK_RX_CARRIER_EN_CH0_M  (RMT_CHK_RX_CARRIER_EN_CH0_V << RMT_CHK_RX_CARRIER_EN_CH0_S)
#define RMT_CHK_RX_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CHK_RX_CARRIER_EN_CH0_S  16
/** RMT_REF_ALWAYS_ON_CH0:R/W；位位置：[17]；默认值：0；设置此位以选择信道0的基准时钟。
 *
 *  1'H:APB_CLK 1'H:REF_TICK
 */
#define RMT_REF_ALWAYS_ON_CH0    (BIT(17))
#define RMT_REF_ALWAYS_ON_CH0_M  (RMT_REF_ALWAYS_ON_CH0_V << RMT_REF_ALWAYS_ON_CH0_S)
#define RMT_REF_ALWAYS_ON_CH0_V  0x00000001U
#define RMT_REF_ALWAYS_ON_CH0_S  17
/** RMT_IDLE_OUT_LV_CH0:R/W；位位置：[18]；默认值：0；当发射机处于空闲状态时，该位配置信道0中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_CH0    (BIT(18))
#define RMT_IDLE_OUT_LV_CH0_M  (RMT_IDLE_OUT_LV_CH0_V << RMT_IDLE_OUT_LV_CH0_S)
#define RMT_IDLE_OUT_LV_CH0_V  0x00000001U
#define RMT_IDLE_OUT_LV_CH0_S  18
/** RMT_IDLE_OUT_EN_CH0:R/W；位位置：[19]；默认值：0；这是处于空闲状态的通道0的输出启用位。
 */
#define RMT_IDLE_OUT_EN_CH0    (BIT(19))
#define RMT_IDLE_OUT_EN_CH0_M  (RMT_IDLE_OUT_EN_CH0_V << RMT_IDLE_OUT_EN_CH0_S)
#define RMT_IDLE_OUT_EN_CH0_V  0x00000001U
#define RMT_IDLE_OUT_EN_CH0_S  19
/** RMT_TX_STOP_CH0:R/W；位位置：[20]；默认值：0；设置此位以停止信道0的发射机发送数据。
 */
#define RMT_TX_STOP_CH0    (BIT(20))
#define RMT_TX_STOP_CH0_M  (RMT_TX_STOP_CH0_V << RMT_TX_STOP_CH0_S)
#define RMT_TX_STOP_CH0_V  0x00000001U
#define RMT_TX_STOP_CH0_S  20

/** RMT_CH1CONF0_REG寄存器通道1配置寄存器0
 */
#define RMT_CH1CONF0_REG (DR_REG_RMT_BASE + 0x18)
/** RMT_DIV_CNT_CH0:R/W；位位置：[7:0]；默认值：2；此字段用于配置信道1的时钟分频器。
 */
#define RMT_DIV_CNT_CH0    0x000000FFU
#define RMT_DIV_CNT_CH0_M  (RMT_DIV_CNT_CH0_V << RMT_DIV_CNT_CH0_S)
#define RMT_DIV_CNT_CH0_V  0x000000FFU
#define RMT_DIV_CNT_CH0_S  0
/** RMT_IDLE_THRES_CH0:R/W；比特位置：[23:8]；默认值：4096；当在比该字段值更长的连续时钟周期内没有检测到输入信号上的边沿时，接收结束。
 */
#define RMT_IDLE_THRES_CH0    0x0000FFFFU
#define RMT_IDLE_THRES_CH0_M  (RMT_IDLE_THRES_CH0_V << RMT_IDLE_THRES_CH0_S)
#define RMT_IDLE_THRES_CH0_V  0x0000FFFFU
#define RMT_IDLE_THRES_CH0_S  8
/** RMT_MEM_SIZE_CH0:R/W；比特位置：[26:24]；默认值：1；此字段用于配置分配给信道1的最大块。有效范围为1~4-1。
 */
#define RMT_MEM_SIZE_CH0    0x00000007U
#define RMT_MEM_SIZE_CH0_M  (RMT_MEM_SIZE_CH0_V << RMT_MEM_SIZE_CH0_S)
#define RMT_MEM_SIZE_CH0_V  0x00000007U
#define RMT_MEM_SIZE_CH0_S  24
/** RMT_CARRIER_EFF_EN_CH0:R/W；位位置：[27]；默认值：1；1： 仅在信道1的数据发送状态下对输出信号添加载波调制。0：在信道1所有状态下对信号添加载波调变。这里的状态包括空闲状态（ST_idle）、从RAM读取数据（ST_RD_MEM）和发送存储在RAM中的数据（ST_SEND）。仅当RMT_CARRIR_EN_CH1设置为1时有效。
 */
#define RMT_CARRIER_EFF_EN_CH0    (BIT(27))
#define RMT_CARRIER_EFF_EN_CH0_M  (RMT_CARRIER_EFF_EN_CH0_V << RMT_CARRIER_EFF_EN_CH0_S)
#define RMT_CARRIER_EFF_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EFF_EN_CH0_S  27
/** RMT_CARRIER_EN_CH0:R/W；位位置：[28]；默认值：1；此位用于启用信道1的载波调制。1：在输出信号上添加载波调制。0：输出信号无载波调制。
 */
#define RMT_CARRIER_EN_CH0    (BIT(28))
#define RMT_CARRIER_EN_CH0_M  (RMT_CARRIER_EN_CH0_V << RMT_CARRIER_EN_CH0_S)
#define RMT_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EN_CH0_S  28
/** RMT_CARRIER_OUT_LV_CH0:R/W；位位置：[29]；默认值：1；该位用于配置信道1的载波位置。
 *
 *  1’0：在低电平输出信号上添加载波。
 *
 *  1'h1：在高电平输出信号上添加载波。
 */
#define RMT_CARRIER_OUT_LV_CH0    (BIT(29))
#define RMT_CARRIER_OUT_LV_CH0_M  (RMT_CARRIER_OUT_LV_CH0_V << RMT_CARRIER_OUT_LV_CH0_S)
#define RMT_CARRIER_OUT_LV_CH0_V  0x00000001U
#define RMT_CARRIER_OUT_LV_CH0_S  29

/** RMT_CH1CONF1_REG寄存器通道1配置寄存器1
 */
#define RMT_CH1CONF1_REG (DR_REG_RMT_BASE + 0x1c)
/** RMT_TX_START_CH0:R/W；位位置：[0]；默认值：0；设置此位以开始在信道1上发送数据。
 */
#define RMT_TX_START_CH0    (BIT(0))
#define RMT_TX_START_CH0_M  (RMT_TX_START_CH0_V << RMT_TX_START_CH0_S)
#define RMT_TX_START_CH0_V  0x00000001U
#define RMT_TX_START_CH0_S  0
/** RMT_RX_EN_CH0:R/W；位位置：[1]；默认值：0；设置此位以使接收机能够在信道1上接收数据。
 */
#define RMT_RX_EN_CH0    (BIT(1))
#define RMT_RX_EN_CH0_M  (RMT_RX_EN_CH0_V << RMT_RX_EN_CH0_S)
#define RMT_RX_EN_CH0_V  0x00000001U
#define RMT_RX_EN_CH0_S  1
/** RMT_MEM_WR_RST_CH0:WO；位位置：[2]；默认值：0；设置此位以重置接收器为通道1访问的RAM写入地址。
 */
#define RMT_MEM_WR_RST_CH0    (BIT(2))
#define RMT_MEM_WR_RST_CH0_M  (RMT_MEM_WR_RST_CH0_V << RMT_MEM_WR_RST_CH0_S)
#define RMT_MEM_WR_RST_CH0_V  0x00000001U
#define RMT_MEM_WR_RST_CH0_S  2
/** RMT_MEM_RD_RST_CH0:WO；位位置：[3]；默认值：0；设置此位以重置发射器为通道1访问的RAM读取地址。
 */
#define RMT_MEM_RD_RST_CH0    (BIT(3))
#define RMT_MEM_RD_RST_CH0_M  (RMT_MEM_RD_RST_CH0_V << RMT_MEM_RD_RST_CH0_S)
#define RMT_MEM_RD_RST_CH0_V  0x00000001U
#define RMT_MEM_RD_RST_CH0_S  3
/** RMT_APB_MEM_RST_CH0:WO；位位置：[4]；默认值：0；设置此位以通过访问apb fifo重置通道1的W/R ram地址。
 */
#define RMT_APB_MEM_RST_CH0    (BIT(4))
#define RMT_APB_MEM_RST_CH0_M  (RMT_APB_MEM_RST_CH0_V << RMT_APB_MEM_RST_CH0_S)
#define RMT_APB_MEM_RST_CH0_V  0x00000001U
#define RMT_APB_MEM_RST_CH0_S  4
/** RMT_MEM_OWNER_CH0:R/W；位位置：[5]；默认值：1；该位标记通道1的RAM块的所有权。
 *
 *  1’1：接收器正在使用RAM。
 *
 *  1’0：发射器正在使用RAM。
 */
#define RMT_MEM_OWNER_CH0    (BIT(5))
#define RMT_MEM_OWNER_CH0_M  (RMT_MEM_OWNER_CH0_V << RMT_MEM_OWNER_CH0_S)
#define RMT_MEM_OWNER_CH0_V  0x00000001U
#define RMT_MEM_OWNER_CH0_S  5
/** RMT_TX_CONTI_MODE_CH0:R/W；位位置：[6]；默认值：0；设置此位以从信道1中的第一个数据重新开始连续节点中的传输。
 */
#define RMT_TX_CONTI_MODE_CH0    (BIT(6))
#define RMT_TX_CONTI_MODE_CH0_M  (RMT_TX_CONTI_MODE_CH0_V << RMT_TX_CONTI_MODE_CH0_S)
#define RMT_TX_CONTI_MODE_CH0_V  0x00000001U
#define RMT_TX_CONTI_MODE_CH0_S  6
/** RMT_RX滤波器_ EN _ CH0：R/W；位位置：[7]；默认值：0；设置此位以启用信道1的接收机滤波器。
 */
#define RMT_RX_FILTER_EN_CH0    (BIT(7))
#define RMT_RX_FILTER_EN_CH0_M  (RMT_RX_FILTER_EN_CH0_V << RMT_RX_FILTER_EN_CH0_S)
#define RMT_RX_FILTER_EN_CH0_V  0x00000001U
#define RMT_RX_FILTER_EN_CH0_S  7
/** RMT_RX滤波器阈值CH0:R/W；比特位置：[15:8]；默认值：15；在接收模式下，当输入脉冲的宽度小于RMT_RX_FILTER_THRES_CH1 APB时钟周期时，将此字段设置为忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_CH0    0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_M  (RMT_RX_FILTER_THRES_CH0_V << RMT_RX_FILTER_THRES_CH0_S)
#define RMT_RX_FILTER_THRES_CH0_V  0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_S  8
/** RMT_CHK_RX_CARRIER_EN_CH0:R/W；位位置：[16]；默认值：0；当信道1启用载波调制时，设置此位以启用存储器环路读取模式。
 */
#define RMT_CHK_RX_CARRIER_EN_CH0    (BIT(16))
#define RMT_CHK_RX_CARRIER_EN_CH0_M  (RMT_CHK_RX_CARRIER_EN_CH0_V << RMT_CHK_RX_CARRIER_EN_CH0_S)
#define RMT_CHK_RX_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CHK_RX_CARRIER_EN_CH0_S  16
/** RMT_REF_ALWAYS_ON_CH0:R/W；位位置：[17]；默认值：0；设置此位以选择信道1的基准时钟。
 *
 *  1'H:APB_CLK 1'H:REF_TICK
 */
#define RMT_REF_ALWAYS_ON_CH0    (BIT(17))
#define RMT_REF_ALWAYS_ON_CH0_M  (RMT_REF_ALWAYS_ON_CH0_V << RMT_REF_ALWAYS_ON_CH0_S)
#define RMT_REF_ALWAYS_ON_CH0_V  0x00000001U
#define RMT_REF_ALWAYS_ON_CH0_S  17
/** RMT_IDLE_OUT_LV_CH0:R/W；位位置：[18]；默认值：0；当发射机处于空闲状态时，该位配置信道1中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_CH0    (BIT(18))
#define RMT_IDLE_OUT_LV_CH0_M  (RMT_IDLE_OUT_LV_CH0_V << RMT_IDLE_OUT_LV_CH0_S)
#define RMT_IDLE_OUT_LV_CH0_V  0x00000001U
#define RMT_IDLE_OUT_LV_CH0_S  18
/** RMT_IDLE_OUT_EN_CH0:R/W；位位置：[19]；默认值：0；这是空闲状态下通道1的输出启用位。
 */
#define RMT_IDLE_OUT_EN_CH0    (BIT(19))
#define RMT_IDLE_OUT_EN_CH0_M  (RMT_IDLE_OUT_EN_CH0_V << RMT_IDLE_OUT_EN_CH0_S)
#define RMT_IDLE_OUT_EN_CH0_V  0x00000001U
#define RMT_IDLE_OUT_EN_CH0_S  19
/** RMT_TX_STOP_CH0:R/W；位位置：[20]；默认值：0；设置此位以停止信道1的发射机发送数据。
 */
#define RMT_TX_STOP_CH0    (BIT(20))
#define RMT_TX_STOP_CH0_M  (RMT_TX_STOP_CH0_V << RMT_TX_STOP_CH0_S)
#define RMT_TX_STOP_CH0_V  0x00000001U
#define RMT_TX_STOP_CH0_S  20

/** RMT_CH2CONF0_REG寄存器通道2配置寄存器0
 */
#define RMT_CH2CONF0_REG (DR_REG_RMT_BASE + 0x20)
/** RMT_DIV_CNT_CH0:R/W；位位置：[7:0]；默认值：2；此字段用于配置信道2的时钟分频器。
 */
#define RMT_DIV_CNT_CH0    0x000000FFU
#define RMT_DIV_CNT_CH0_M  (RMT_DIV_CNT_CH0_V << RMT_DIV_CNT_CH0_S)
#define RMT_DIV_CNT_CH0_V  0x000000FFU
#define RMT_DIV_CNT_CH0_S  0
/** RMT_IDLE_THRES_CH0:R/W；比特位置：[23:8]；默认值：4096；当在比该字段值更长的连续时钟周期内没有检测到输入信号上的边沿时，接收结束。
 */
#define RMT_IDLE_THRES_CH0    0x0000FFFFU
#define RMT_IDLE_THRES_CH0_M  (RMT_IDLE_THRES_CH0_V << RMT_IDLE_THRES_CH0_S)
#define RMT_IDLE_THRES_CH0_V  0x0000FFFFU
#define RMT_IDLE_THRES_CH0_S  8
/** RMT_MEM_SIZE_CH0:R/W；比特位置：[26:24]；默认值：1；此字段用于配置分配给信道2的最大块。有效范围为1~4-2。
 */
#define RMT_MEM_SIZE_CH0    0x00000007U
#define RMT_MEM_SIZE_CH0_M  (RMT_MEM_SIZE_CH0_V << RMT_MEM_SIZE_CH0_S)
#define RMT_MEM_SIZE_CH0_V  0x00000007U
#define RMT_MEM_SIZE_CH0_S  24
/** RMT_CARRIER_EFF_EN_CH0:R/W；位位置：[27]；默认值：1；1： 仅在信道2的数据发送状态下对输出信号添加载波调制。0：在信道2所有状态下对信号添加载波调变。这里的状态包括空闲状态（ST_idle）、从RAM读取数据（ST_RD_MEM）和发送存储在RAM中的数据（ST_SEND）。仅当RMT_CARRIR_EN_CH2设置为1时有效。
 */
#define RMT_CARRIER_EFF_EN_CH0    (BIT(27))
#define RMT_CARRIER_EFF_EN_CH0_M  (RMT_CARRIER_EFF_EN_CH0_V << RMT_CARRIER_EFF_EN_CH0_S)
#define RMT_CARRIER_EFF_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EFF_EN_CH0_S  27
/** RMT_CARRIER_EN_CH0:R/W；位位置：[28]；默认值：1；此位用于启用信道2.1的载波调制：在输出信号上添加载波调制。0：输出信号无载波调制。
 */
#define RMT_CARRIER_EN_CH0    (BIT(28))
#define RMT_CARRIER_EN_CH0_M  (RMT_CARRIER_EN_CH0_V << RMT_CARRIER_EN_CH0_S)
#define RMT_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EN_CH0_S  28
/** RMT_CARRIER_OUT_LV_CH0:R/W；位位置：[29]；默认值：1；该位用于配置信道2的载波位置。
 *
 *  1’0：在低电平输出信号上添加载波。
 *
 *  1'h1：在高电平输出信号上添加载波。
 */
#define RMT_CARRIER_OUT_LV_CH0    (BIT(29))
#define RMT_CARRIER_OUT_LV_CH0_M  (RMT_CARRIER_OUT_LV_CH0_V << RMT_CARRIER_OUT_LV_CH0_S)
#define RMT_CARRIER_OUT_LV_CH0_V  0x00000001U
#define RMT_CARRIER_OUT_LV_CH0_S  29

/** RMT_CH2CONF1_REG寄存器通道2配置寄存器1
 */
#define RMT_CH2CONF1_REG (DR_REG_RMT_BASE + 0x24)
/** RMT_TX_START_CH0:R/W；位位置：[0]；默认值：0；设置此位以开始在信道2上发送数据。
 */
#define RMT_TX_START_CH0    (BIT(0))
#define RMT_TX_START_CH0_M  (RMT_TX_START_CH0_V << RMT_TX_START_CH0_S)
#define RMT_TX_START_CH0_V  0x00000001U
#define RMT_TX_START_CH0_S  0
/** RMT_RX_EN_CH0:R/W；位位置：[1]；默认值：0；设置此位以使接收机能够在信道2上接收数据。
 */
#define RMT_RX_EN_CH0    (BIT(1))
#define RMT_RX_EN_CH0_M  (RMT_RX_EN_CH0_V << RMT_RX_EN_CH0_S)
#define RMT_RX_EN_CH0_V  0x00000001U
#define RMT_RX_EN_CH0_S  1
/** RMT_MEM_WR_RST_CH0:WO；位位置：[2]；默认值：0；设置此位以重置接收器为通道2访问的RAM写入地址。
 */
#define RMT_MEM_WR_RST_CH0    (BIT(2))
#define RMT_MEM_WR_RST_CH0_M  (RMT_MEM_WR_RST_CH0_V << RMT_MEM_WR_RST_CH0_S)
#define RMT_MEM_WR_RST_CH0_V  0x00000001U
#define RMT_MEM_WR_RST_CH0_S  2
/** RMT_MEM_RD_RST_CH0:WO；位位置：[3]；默认值：0；设置此位以重置发射机为信道2访问的RAM读取地址。
 */
#define RMT_MEM_RD_RST_CH0    (BIT(3))
#define RMT_MEM_RD_RST_CH0_M  (RMT_MEM_RD_RST_CH0_V << RMT_MEM_RD_RST_CH0_S)
#define RMT_MEM_RD_RST_CH0_V  0x00000001U
#define RMT_MEM_RD_RST_CH0_S  3
/** RMT_APB_MEM_RST_CH0:WO；位位置：[4]；默认值：0；设置此位以通过访问apb fifo重置通道2的W/R ram地址。
 */
#define RMT_APB_MEM_RST_CH0    (BIT(4))
#define RMT_APB_MEM_RST_CH0_M  (RMT_APB_MEM_RST_CH0_V << RMT_APB_MEM_RST_CH0_S)
#define RMT_APB_MEM_RST_CH0_V  0x00000001U
#define RMT_APB_MEM_RST_CH0_S  4
/** RMT_MEM_OWNER_CH0:R/W；位位置：[5]；默认值：1；该位标记通道2的RAM块的所有权。
 *
 *  1’1：接收器正在使用RAM。
 *
 *  1’0：发射器正在使用RAM。
 */
#define RMT_MEM_OWNER_CH0    (BIT(5))
#define RMT_MEM_OWNER_CH0_M  (RMT_MEM_OWNER_CH0_V << RMT_MEM_OWNER_CH0_S)
#define RMT_MEM_OWNER_CH0_V  0x00000001U
#define RMT_MEM_OWNER_CH0_S  5
/** RMT_TX_CONTI_MODE_CH0:R/W；位位置：[6]；默认值：0；设置此位以从信道2中的第一个数据重新开始连续节点中的传输。
 */
#define RMT_TX_CONTI_MODE_CH0    (BIT(6))
#define RMT_TX_CONTI_MODE_CH0_M  (RMT_TX_CONTI_MODE_CH0_V << RMT_TX_CONTI_MODE_CH0_S)
#define RMT_TX_CONTI_MODE_CH0_V  0x00000001U
#define RMT_TX_CONTI_MODE_CH0_S  6
/** RMT_RX滤波器_ EN _ CH0：R/W；位位置：[7]；默认值：0；设置此位以启用信道2的接收机滤波器。
 */
#define RMT_RX_FILTER_EN_CH0    (BIT(7))
#define RMT_RX_FILTER_EN_CH0_M  (RMT_RX_FILTER_EN_CH0_V << RMT_RX_FILTER_EN_CH0_S)
#define RMT_RX_FILTER_EN_CH0_V  0x00000001U
#define RMT_RX_FILTER_EN_CH0_S  7
/** RMT_RX滤波器阈值CH0:R/W；比特位置：[15:8]；默认值：15；在接收模式下，当输入脉冲的宽度小于RMT_RX_FILTER_THRES_CH2 APB时钟周期时，将此字段设置为忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_CH0    0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_M  (RMT_RX_FILTER_THRES_CH0_V << RMT_RX_FILTER_THRES_CH0_S)
#define RMT_RX_FILTER_THRES_CH0_V  0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_S  8
/** RMT_CHK_RX_CARRIER_EN_CH0:R/W；位位置：[16]；默认值：0；当信道2启用载波调制时，设置此位以启用存储器环路读取模式。
 */
#define RMT_CHK_RX_CARRIER_EN_CH0    (BIT(16))
#define RMT_CHK_RX_CARRIER_EN_CH0_M  (RMT_CHK_RX_CARRIER_EN_CH0_V << RMT_CHK_RX_CARRIER_EN_CH0_S)
#define RMT_CHK_RX_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CHK_RX_CARRIER_EN_CH0_S  16
/** RMT_REF_ALWAYS_ON_CH0:R/W；位位置：[17]；默认值：0；设置此位以选择信道2的基准时钟。
 *
 *  1'H:APB_CLK 1'H:REF_TICK
 */
#define RMT_REF_ALWAYS_ON_CH0    (BIT(17))
#define RMT_REF_ALWAYS_ON_CH0_M  (RMT_REF_ALWAYS_ON_CH0_V << RMT_REF_ALWAYS_ON_CH0_S)
#define RMT_REF_ALWAYS_ON_CH0_V  0x00000001U
#define RMT_REF_ALWAYS_ON_CH0_S  17
/** RMT_IDLE_OUT_LV_CH0:R/W；位位置：[18]；默认值：0；当发射机处于空闲状态时，该位配置信道2中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_CH0    (BIT(18))
#define RMT_IDLE_OUT_LV_CH0_M  (RMT_IDLE_OUT_LV_CH0_V << RMT_IDLE_OUT_LV_CH0_S)
#define RMT_IDLE_OUT_LV_CH0_V  0x00000001U
#define RMT_IDLE_OUT_LV_CH0_S  18
/** RMT_IDLE_OUT_EN_CH0:R/W；位位置：[19]；默认值：0；这是处于空闲状态的通道2的输出启用位。
 */
#define RMT_IDLE_OUT_EN_CH0    (BIT(19))
#define RMT_IDLE_OUT_EN_CH0_M  (RMT_IDLE_OUT_EN_CH0_V << RMT_IDLE_OUT_EN_CH0_S)
#define RMT_IDLE_OUT_EN_CH0_V  0x00000001U
#define RMT_IDLE_OUT_EN_CH0_S  19
/** RMT_TX_STOP_CH0:R/W；位位置：[20]；默认值：0；设置此位以停止信道2的发射机发送数据。
 */
#define RMT_TX_STOP_CH0    (BIT(20))
#define RMT_TX_STOP_CH0_M  (RMT_TX_STOP_CH0_V << RMT_TX_STOP_CH0_S)
#define RMT_TX_STOP_CH0_V  0x00000001U
#define RMT_TX_STOP_CH0_S  20

/** RMT_CH3CONF0_REG寄存器通道3配置寄存器0
 */
#define RMT_CH3CONF0_REG (DR_REG_RMT_BASE + 0x28)
/** RMT_DIV_CNT_CH0:R/W；位位置：[7:0]；默认值：2；此字段用于配置信道3的时钟分频器。
 */
#define RMT_DIV_CNT_CH0    0x000000FFU
#define RMT_DIV_CNT_CH0_M  (RMT_DIV_CNT_CH0_V << RMT_DIV_CNT_CH0_S)
#define RMT_DIV_CNT_CH0_V  0x000000FFU
#define RMT_DIV_CNT_CH0_S  0
/** RMT_IDLE_THRES_CH0:R/W；比特位置：[23:8]；默认值：4096；当在比该字段值更长的连续时钟周期内没有检测到输入信号上的边沿时，接收结束。
 */
#define RMT_IDLE_THRES_CH0    0x0000FFFFU
#define RMT_IDLE_THRES_CH0_M  (RMT_IDLE_THRES_CH0_V << RMT_IDLE_THRES_CH0_S)
#define RMT_IDLE_THRES_CH0_V  0x0000FFFFU
#define RMT_IDLE_THRES_CH0_S  8
/** RMT_MEM_SIZE_CH0:R/W；比特位置：[26:24]；默认值：1；此字段用于配置分配给信道3的最大块。有效范围为1~4-3。
 */
#define RMT_MEM_SIZE_CH0    0x00000007U
#define RMT_MEM_SIZE_CH0_M  (RMT_MEM_SIZE_CH0_V << RMT_MEM_SIZE_CH0_S)
#define RMT_MEM_SIZE_CH0_V  0x00000007U
#define RMT_MEM_SIZE_CH0_S  24
/** RMT_CARRIER_EFF_EN_CH0:R/W；位位置：[27]；默认值：1；1： 仅在信道3的数据发送状态下对输出信号添加载波调制。0：在信道3所有状态下对信号添加载波调变。这里的状态包括空闲状态（ST_idle）、从RAM读取数据（ST_RD_MEM）和发送存储在RAM中的数据（ST_SEND）。仅当RMT_CARRIR_EN_CH3设置为1时有效。
 */
#define RMT_CARRIER_EFF_EN_CH0    (BIT(27))
#define RMT_CARRIER_EFF_EN_CH0_M  (RMT_CARRIER_EFF_EN_CH0_V << RMT_CARRIER_EFF_EN_CH0_S)
#define RMT_CARRIER_EFF_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EFF_EN_CH0_S  27
/** RMT_CARRIER_EN_CH0:R/W；位位置：[28]；默认值：1；此位用于启用信道3.1的载波调制：在输出信号上添加载波调制。0：输出信号无载波调制。
 */
#define RMT_CARRIER_EN_CH0    (BIT(28))
#define RMT_CARRIER_EN_CH0_M  (RMT_CARRIER_EN_CH0_V << RMT_CARRIER_EN_CH0_S)
#define RMT_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CARRIER_EN_CH0_S  28
/** RMT_CARRIER_OUT_LV_CH0:R/W；位位置：[29]；默认值：1；该位用于配置信道3的载波位置。
 *
 *  1’0：在低电平输出信号上添加载波。
 *
 *  1'h1：在高电平输出信号上添加载波。
 */
#define RMT_CARRIER_OUT_LV_CH0    (BIT(29))
#define RMT_CARRIER_OUT_LV_CH0_M  (RMT_CARRIER_OUT_LV_CH0_V << RMT_CARRIER_OUT_LV_CH0_S)
#define RMT_CARRIER_OUT_LV_CH0_V  0x00000001U
#define RMT_CARRIER_OUT_LV_CH0_S  29

/** RMT_CH3CONF1_REG寄存器通道3配置寄存器1
 */
#define RMT_CH3CONF1_REG (DR_REG_RMT_BASE + 0x2c)
/** RMT_TX_START_CH0:R/W；位位置：[0]；默认值：0；设置此位以开始在信道3上发送数据。
 */
#define RMT_TX_START_CH0    (BIT(0))
#define RMT_TX_START_CH0_M  (RMT_TX_START_CH0_V << RMT_TX_START_CH0_S)
#define RMT_TX_START_CH0_V  0x00000001U
#define RMT_TX_START_CH0_S  0
/** RMT_RX_EN_CH0:R/W；位位置：[1]；默认值：0；设置此位以使接收机能够在信道3上接收数据。
 */
#define RMT_RX_EN_CH0    (BIT(1))
#define RMT_RX_EN_CH0_M  (RMT_RX_EN_CH0_V << RMT_RX_EN_CH0_S)
#define RMT_RX_EN_CH0_V  0x00000001U
#define RMT_RX_EN_CH0_S  1
/** RMT_MEM_WR_RST_CH0:WO；位位置：[2]；默认值：0；设置此位以重置接收器为通道3访问的RAM写入地址。
 */
#define RMT_MEM_WR_RST_CH0    (BIT(2))
#define RMT_MEM_WR_RST_CH0_M  (RMT_MEM_WR_RST_CH0_V << RMT_MEM_WR_RST_CH0_S)
#define RMT_MEM_WR_RST_CH0_V  0x00000001U
#define RMT_MEM_WR_RST_CH0_S  2
/** RMT_MEM_RD_RST_CH0:WO；位位置：[3]；默认值：0；设置此位以重置发射器为通道3访问的RAM读取地址。
 */
#define RMT_MEM_RD_RST_CH0    (BIT(3))
#define RMT_MEM_RD_RST_CH0_M  (RMT_MEM_RD_RST_CH0_V << RMT_MEM_RD_RST_CH0_S)
#define RMT_MEM_RD_RST_CH0_V  0x00000001U
#define RMT_MEM_RD_RST_CH0_S  3
/** RMT_APB_MEM_RST_CH0:WO；位位置：[4]；默认值：0；设置此位以通过访问apb fifo重置通道3的W/R ram地址。
 */
#define RMT_APB_MEM_RST_CH0    (BIT(4))
#define RMT_APB_MEM_RST_CH0_M  (RMT_APB_MEM_RST_CH0_V << RMT_APB_MEM_RST_CH0_S)
#define RMT_APB_MEM_RST_CH0_V  0x00000001U
#define RMT_APB_MEM_RST_CH0_S  4
/** RMT_MEM_OWNER_CH0:R/W；位位置：[5]；默认值：1；该位标记通道3的RAM块的所有权。
 *
 *  1’1：接收器正在使用RAM。
 *
 *  1’0：发射器正在使用RAM。
 */
#define RMT_MEM_OWNER_CH0    (BIT(5))
#define RMT_MEM_OWNER_CH0_M  (RMT_MEM_OWNER_CH0_V << RMT_MEM_OWNER_CH0_S)
#define RMT_MEM_OWNER_CH0_V  0x00000001U
#define RMT_MEM_OWNER_CH0_S  5
/** RMT_TX_CONTI_MODE_CH0:R/W；位位置：[6]；默认值：0；设置此位以从信道3中的第一个数据重新开始连续节点中的传输。
 */
#define RMT_TX_CONTI_MODE_CH0    (BIT(6))
#define RMT_TX_CONTI_MODE_CH0_M  (RMT_TX_CONTI_MODE_CH0_V << RMT_TX_CONTI_MODE_CH0_S)
#define RMT_TX_CONTI_MODE_CH0_V  0x00000001U
#define RMT_TX_CONTI_MODE_CH0_S  6
/** RMT_RX滤波器_ EN _ CH0：R/W；位位置：[7]；默认值：0；设置此位以启用信道3的接收机滤波器。
 */
#define RMT_RX_FILTER_EN_CH0    (BIT(7))
#define RMT_RX_FILTER_EN_CH0_M  (RMT_RX_FILTER_EN_CH0_V << RMT_RX_FILTER_EN_CH0_S)
#define RMT_RX_FILTER_EN_CH0_V  0x00000001U
#define RMT_RX_FILTER_EN_CH0_S  7
/** RMT_RX滤波器阈值CH0:R/W；比特位置：[15:8]；默认值：15；在接收模式下，当输入脉冲的宽度小于RMT_RX_FILTER_THRES_CH3 APB时钟周期时，将此字段设置为忽略输入脉冲。
 */
#define RMT_RX_FILTER_THRES_CH0    0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_M  (RMT_RX_FILTER_THRES_CH0_V << RMT_RX_FILTER_THRES_CH0_S)
#define RMT_RX_FILTER_THRES_CH0_V  0x000000FFU
#define RMT_RX_FILTER_THRES_CH0_S  8
/** RMT_CHK_RX_CARRIER_EN_CH0:R/W；位位置：[16]；默认值：0；当信道3启用载波调制时，设置此位以启用存储器环路读取模式。
 */
#define RMT_CHK_RX_CARRIER_EN_CH0    (BIT(16))
#define RMT_CHK_RX_CARRIER_EN_CH0_M  (RMT_CHK_RX_CARRIER_EN_CH0_V << RMT_CHK_RX_CARRIER_EN_CH0_S)
#define RMT_CHK_RX_CARRIER_EN_CH0_V  0x00000001U
#define RMT_CHK_RX_CARRIER_EN_CH0_S  16
/** RMT_REF_ALWAYS_ON_CH0:R/W；位位置：[17]；默认值：0；设置此位以选择信道3的基准时钟。
 *
 *  1'H:APB_CLK 1'H:REF_TICK
 */
#define RMT_REF_ALWAYS_ON_CH0    (BIT(17))
#define RMT_REF_ALWAYS_ON_CH0_M  (RMT_REF_ALWAYS_ON_CH0_V << RMT_REF_ALWAYS_ON_CH0_S)
#define RMT_REF_ALWAYS_ON_CH0_V  0x00000001U
#define RMT_REF_ALWAYS_ON_CH0_S  17
/** RMT_IDLE_OUT_LV_CH0:R/W；位位置：[18]；默认值：0；当发射机处于空闲状态时，该位配置信道3中输出信号的电平。
 */
#define RMT_IDLE_OUT_LV_CH0    (BIT(18))
#define RMT_IDLE_OUT_LV_CH0_M  (RMT_IDLE_OUT_LV_CH0_V << RMT_IDLE_OUT_LV_CH0_S)
#define RMT_IDLE_OUT_LV_CH0_V  0x00000001U
#define RMT_IDLE_OUT_LV_CH0_S  18
/** RMT_IDLE_OUT_EN_CH0:R/W；位位置：[19]；默认值：0；这是空闲状态下通道3的输出启用位。
 */
#define RMT_IDLE_OUT_EN_CH0    (BIT(19))
#define RMT_IDLE_OUT_EN_CH0_M  (RMT_IDLE_OUT_EN_CH0_V << RMT_IDLE_OUT_EN_CH0_S)
#define RMT_IDLE_OUT_EN_CH0_V  0x00000001U
#define RMT_IDLE_OUT_EN_CH0_S  19
/** RMT_TX_STOP_CH0:R/W；位位置：[20]；默认值：0；设置此位以停止信道3的发射机发送数据。
 */
#define RMT_TX_STOP_CH0    (BIT(20))
#define RMT_TX_STOP_CH0_M  (RMT_TX_STOP_CH0_V << RMT_TX_STOP_CH0_S)
#define RMT_TX_STOP_CH0_V  0x00000001U
#define RMT_TX_STOP_CH0_S  20

/** RMT_CH0STATUS_REG寄存器通道0状态寄存器
 */
#define RMT_CH0STATUS_REG (DR_REG_RMT_BASE + 0x30)
/** RMT_MEM_WADDR_EX_CH0:RO；位位置：[8:0]；默认值：0；当信道0的接收机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_CH0    0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_M  (RMT_MEM_WADDR_EX_CH0_V << RMT_MEM_WADDR_EX_CH0_S)
#define RMT_MEM_WADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_S  0
/** RMT_MEM_RADDR_EX_CH0:RO；比特位置：[18:10]；默认值：0；当信道0的发射机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_CH0    0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_M  (RMT_MEM_RADDR_EX_CH0_V << RMT_MEM_RADDR_EX_CH0_S)
#define RMT_MEM_RADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_S  10
/** RMT_STATE_CH0:RO；比特位置：[22:20]；默认值：0；此字段记录通道0的FSM状态。
 */
#define RMT_STATE_CH0    0x00000007U
#define RMT_STATE_CH0_M  (RMT_STATE_CH0_V << RMT_STATE_CH0_S)
#define RMT_STATE_CH0_V  0x00000007U
#define RMT_STATE_CH0_S  20
/** RMT_MEM_OWNER_ERR_CH0:RO；位位置：[23]；默认值：0；当内存块的所有权被侵犯时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_CH0    (BIT(23))
#define RMT_MEM_OWNER_ERR_CH0_M  (RMT_MEM_OWNER_ERR_CH0_V << RMT_MEM_OWNER_ERR_CH0_S)
#define RMT_MEM_OWNER_ERR_CH0_V  0x00000001U
#define RMT_MEM_OWNER_ERR_CH0_S  23
/** RMT_MEM_FULL_CH0:RO；位位置：[24]；默认值：0；如果接收器接收的数据超过存储器允许的数据量，则将设置此状态位。
 */
#define RMT_MEM_FULL_CH0    (BIT(24))
#define RMT_MEM_FULL_CH0_M  (RMT_MEM_FULL_CH0_V << RMT_MEM_FULL_CH0_S)
#define RMT_MEM_FULL_CH0_V  0x00000001U
#define RMT_MEM_FULL_CH0_S  24
/** RMT_MEM_EMPTY_CH0:RO；位位置：[25]；默认值：0；当要发送的数据超过内存允许的范围并且包装模式被禁用时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_CH0    (BIT(25))
#define RMT_MEM_EMPTY_CH0_M  (RMT_MEM_EMPTY_CH0_V << RMT_MEM_EMPTY_CH0_S)
#define RMT_MEM_EMPTY_CH0_V  0x00000001U
#define RMT_MEM_EMPTY_CH0_S  25
/** RMT_APB_MEM_WR_ERR_CH0:RO；位位置：[26]；默认值：0；当通过APB总线写入RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_CH0    (BIT(26))
#define RMT_APB_MEM_WR_ERR_CH0_M  (RMT_APB_MEM_WR_ERR_CH0_V << RMT_APB_MEM_WR_ERR_CH0_S)
#define RMT_APB_MEM_WR_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_CH0_S  26
/** RMT_APB_MEM_RD_ERR_CH0:RO；位位置：[27]；默认值：0；当通过APB总线读取RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_CH0    (BIT(27))
#define RMT_APB_MEM_RD_ERR_CH0_M  (RMT_APB_MEM_RD_ERR_CH0_V << RMT_APB_MEM_RD_ERR_CH0_S)
#define RMT_APB_MEM_RD_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_CH0_S  27

/** RMT_CH1STATUS_REG寄存器通道1状态寄存器
 */
#define RMT_CH1STATUS_REG (DR_REG_RMT_BASE + 0x34)
/** RMT_MEM_WADDR_EX_CH0:RO；位位置：[8:0]；默认值：0；当信道1的接收机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_CH0    0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_M  (RMT_MEM_WADDR_EX_CH0_V << RMT_MEM_WADDR_EX_CH0_S)
#define RMT_MEM_WADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_S  0
/** RMT_MEM_RADDR_EX_CH0:RO；比特位置：[18:10]；默认值：0；当信道1的发射机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_CH0    0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_M  (RMT_MEM_RADDR_EX_CH0_V << RMT_MEM_RADDR_EX_CH0_S)
#define RMT_MEM_RADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_S  10
/** RMT_STATE_CH0:RO；比特位置：[22:20]；默认值：0；此字段记录通道1的FSM状态。
 */
#define RMT_STATE_CH0    0x00000007U
#define RMT_STATE_CH0_M  (RMT_STATE_CH0_V << RMT_STATE_CH0_S)
#define RMT_STATE_CH0_V  0x00000007U
#define RMT_STATE_CH0_S  20
/** RMT_MEM_OWNER_ERR_CH0:RO；位位置：[23]；默认值：0；当内存块的所有权被侵犯时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_CH0    (BIT(23))
#define RMT_MEM_OWNER_ERR_CH0_M  (RMT_MEM_OWNER_ERR_CH0_V << RMT_MEM_OWNER_ERR_CH0_S)
#define RMT_MEM_OWNER_ERR_CH0_V  0x00000001U
#define RMT_MEM_OWNER_ERR_CH0_S  23
/** RMT_MEM_FULL_CH0:RO；位位置：[24]；默认值：0；如果接收器接收的数据超过存储器允许的数据量，则将设置此状态位。
 */
#define RMT_MEM_FULL_CH0    (BIT(24))
#define RMT_MEM_FULL_CH0_M  (RMT_MEM_FULL_CH0_V << RMT_MEM_FULL_CH0_S)
#define RMT_MEM_FULL_CH0_V  0x00000001U
#define RMT_MEM_FULL_CH0_S  24
/** RMT_MEM_EMPTY_CH0:RO；位位置：[25]；默认值：0；当要发送的数据超过内存允许的范围并且包装模式被禁用时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_CH0    (BIT(25))
#define RMT_MEM_EMPTY_CH0_M  (RMT_MEM_EMPTY_CH0_V << RMT_MEM_EMPTY_CH0_S)
#define RMT_MEM_EMPTY_CH0_V  0x00000001U
#define RMT_MEM_EMPTY_CH0_S  25
/** RMT_APB_MEM_WR_ERR_CH0:RO；位位置：[26]；默认值：0；当通过APB总线写入RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_CH0    (BIT(26))
#define RMT_APB_MEM_WR_ERR_CH0_M  (RMT_APB_MEM_WR_ERR_CH0_V << RMT_APB_MEM_WR_ERR_CH0_S)
#define RMT_APB_MEM_WR_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_CH0_S  26
/** RMT_APB_MEM_RD_ERR_CH0:RO；位位置：[27]；默认值：0；当通过APB总线读取RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_CH0    (BIT(27))
#define RMT_APB_MEM_RD_ERR_CH0_M  (RMT_APB_MEM_RD_ERR_CH0_V << RMT_APB_MEM_RD_ERR_CH0_S)
#define RMT_APB_MEM_RD_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_CH0_S  27

/** RMT_CH2STATUS_REG寄存器通道2状态寄存器
 */
#define RMT_CH2STATUS_REG (DR_REG_RMT_BASE + 0x38)
/** RMT_MEM_WADDR_EX_CH0:RO；位位置：[8:0]；默认值：0；当信道2的接收机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_CH0    0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_M  (RMT_MEM_WADDR_EX_CH0_V << RMT_MEM_WADDR_EX_CH0_S)
#define RMT_MEM_WADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_S  0
/** RMT_MEM_RADDR_EX_CH0:RO；比特位置：[18:10]；默认值：0；当信道2的发射机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_CH0    0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_M  (RMT_MEM_RADDR_EX_CH0_V << RMT_MEM_RADDR_EX_CH0_S)
#define RMT_MEM_RADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_S  10
/** RMT_STATE_CH0:RO；比特位置：[22:20]；默认值：0；此字段记录通道2的FSM状态。
 */
#define RMT_STATE_CH0    0x00000007U
#define RMT_STATE_CH0_M  (RMT_STATE_CH0_V << RMT_STATE_CH0_S)
#define RMT_STATE_CH0_V  0x00000007U
#define RMT_STATE_CH0_S  20
/** RMT_MEM_OWNER_ERR_CH0:RO；位位置：[23]；默认值：0；当内存块的所有权被侵犯时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_CH0    (BIT(23))
#define RMT_MEM_OWNER_ERR_CH0_M  (RMT_MEM_OWNER_ERR_CH0_V << RMT_MEM_OWNER_ERR_CH0_S)
#define RMT_MEM_OWNER_ERR_CH0_V  0x00000001U
#define RMT_MEM_OWNER_ERR_CH0_S  23
/** RMT_MEM_FULL_CH0:RO；位位置：[24]；默认值：0；如果接收器接收的数据超过存储器允许的数据量，则将设置此状态位。
 */
#define RMT_MEM_FULL_CH0    (BIT(24))
#define RMT_MEM_FULL_CH0_M  (RMT_MEM_FULL_CH0_V << RMT_MEM_FULL_CH0_S)
#define RMT_MEM_FULL_CH0_V  0x00000001U
#define RMT_MEM_FULL_CH0_S  24
/** RMT_MEM_EMPTY_CH0:RO；位位置：[25]；默认值：0；当要发送的数据超过内存允许的范围并且包装模式被禁用时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_CH0    (BIT(25))
#define RMT_MEM_EMPTY_CH0_M  (RMT_MEM_EMPTY_CH0_V << RMT_MEM_EMPTY_CH0_S)
#define RMT_MEM_EMPTY_CH0_V  0x00000001U
#define RMT_MEM_EMPTY_CH0_S  25
/** RMT_APB_MEM_WR_ERR_CH0:RO；位位置：[26]；默认值：0；当通过APB总线写入RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_CH0    (BIT(26))
#define RMT_APB_MEM_WR_ERR_CH0_M  (RMT_APB_MEM_WR_ERR_CH0_V << RMT_APB_MEM_WR_ERR_CH0_S)
#define RMT_APB_MEM_WR_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_CH0_S  26
/** RMT_APB_MEM_RD_ERR_CH0:RO；位位置：[27]；默认值：0；当通过APB总线读取RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_CH0    (BIT(27))
#define RMT_APB_MEM_RD_ERR_CH0_M  (RMT_APB_MEM_RD_ERR_CH0_V << RMT_APB_MEM_RD_ERR_CH0_S)
#define RMT_APB_MEM_RD_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_CH0_S  27

/** RMT_CH3STATUS_REG寄存器通道3状态寄存器
 */
#define RMT_CH3STATUS_REG (DR_REG_RMT_BASE + 0x3c)
/** RMT_MEM_WADDR_EX_CH0:RO；位位置：[8:0]；默认值：0；当信道3的接收机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_WADDR_EX_CH0    0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_M  (RMT_MEM_WADDR_EX_CH0_V << RMT_MEM_WADDR_EX_CH0_S)
#define RMT_MEM_WADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_WADDR_EX_CH0_S  0
/** RMT_MEM_RADDR_EX_CH0:RO；比特位置：[18:10]；默认值：0；当信道3的发射机使用RAM时，该字段记录存储器地址偏移。
 */
#define RMT_MEM_RADDR_EX_CH0    0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_M  (RMT_MEM_RADDR_EX_CH0_V << RMT_MEM_RADDR_EX_CH0_S)
#define RMT_MEM_RADDR_EX_CH0_V  0x000001FFU
#define RMT_MEM_RADDR_EX_CH0_S  10
/** RMT_STATE_CH0:RO；比特位置：[22:20]；默认值：0；此字段记录通道3的FSM状态。
 */
#define RMT_STATE_CH0    0x00000007U
#define RMT_STATE_CH0_M  (RMT_STATE_CH0_V << RMT_STATE_CH0_S)
#define RMT_STATE_CH0_V  0x00000007U
#define RMT_STATE_CH0_S  20
/** RMT_MEM_OWNER_ERR_CH0:RO；位位置：[23]；默认值：0；当内存块的所有权被侵犯时，将设置此状态位。
 */
#define RMT_MEM_OWNER_ERR_CH0    (BIT(23))
#define RMT_MEM_OWNER_ERR_CH0_M  (RMT_MEM_OWNER_ERR_CH0_V << RMT_MEM_OWNER_ERR_CH0_S)
#define RMT_MEM_OWNER_ERR_CH0_V  0x00000001U
#define RMT_MEM_OWNER_ERR_CH0_S  23
/** RMT_MEM_FULL_CH0:RO；位位置：[24]；默认值：0；如果接收器接收的数据超过存储器允许的数据量，则将设置此状态位。
 */
#define RMT_MEM_FULL_CH0    (BIT(24))
#define RMT_MEM_FULL_CH0_M  (RMT_MEM_FULL_CH0_V << RMT_MEM_FULL_CH0_S)
#define RMT_MEM_FULL_CH0_V  0x00000001U
#define RMT_MEM_FULL_CH0_S  24
/** RMT_MEM_EMPTY_CH0:RO；位位置：[25]；默认值：0；当要发送的数据超过内存允许的范围并且包装模式被禁用时，将设置此状态位。
 */
#define RMT_MEM_EMPTY_CH0    (BIT(25))
#define RMT_MEM_EMPTY_CH0_M  (RMT_MEM_EMPTY_CH0_V << RMT_MEM_EMPTY_CH0_S)
#define RMT_MEM_EMPTY_CH0_V  0x00000001U
#define RMT_MEM_EMPTY_CH0_S  25
/** RMT_APB_MEM_WR_ERR_CH0:RO；位位置：[26]；默认值：0；当通过APB总线写入RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_WR_ERR_CH0    (BIT(26))
#define RMT_APB_MEM_WR_ERR_CH0_M  (RMT_APB_MEM_WR_ERR_CH0_V << RMT_APB_MEM_WR_ERR_CH0_S)
#define RMT_APB_MEM_WR_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_WR_ERR_CH0_S  26
/** RMT_APB_MEM_RD_ERR_CH0:RO；位位置：[27]；默认值：0；当通过APB总线读取RAM时，如果偏移地址超出内存大小，将设置此状态位。
 */
#define RMT_APB_MEM_RD_ERR_CH0    (BIT(27))
#define RMT_APB_MEM_RD_ERR_CH0_M  (RMT_APB_MEM_RD_ERR_CH0_V << RMT_APB_MEM_RD_ERR_CH0_S)
#define RMT_APB_MEM_RD_ERR_CH0_V  0x00000001U
#define RMT_APB_MEM_RD_ERR_CH0_S  27

/** RMT_CH0ADDR_REG寄存器通道0地址寄存器
 */
#define RMT_CH0ADDR_REG (DR_REG_RMT_BASE + 0x40)
/** RMT_APB_MEM_WADDR_CH0:RO；位位置：[8:0]；默认值：0；该字段记录通道0通过APB总线写入RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_CH0    0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_M  (RMT_APB_MEM_WADDR_CH0_V << RMT_APB_MEM_WADDR_CH0_S)
#define RMT_APB_MEM_WADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_S  0
/** RMT_APB_MEM_RADDR_CH0:RO；比特位置：[18:10]；默认值：0；该字段记录通道0通过APB总线读取RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_CH0    0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_M  (RMT_APB_MEM_RADDR_CH0_V << RMT_APB_MEM_RADDR_CH0_S)
#define RMT_APB_MEM_RADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_S  10

/** RMT_CH1ADDR_REG寄存器通道1地址寄存器
 */
#define RMT_CH1ADDR_REG (DR_REG_RMT_BASE + 0x44)
/** RMT_APB_MEM_WADDR_CH0:RO；位位置：[8:0]；默认值：0；该字段记录通道1通过APB总线写入RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_CH0    0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_M  (RMT_APB_MEM_WADDR_CH0_V << RMT_APB_MEM_WADDR_CH0_S)
#define RMT_APB_MEM_WADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_S  0
/** RMT_APB_MEM_RADDR_CH0:RO；比特位置：[18:10]；默认值：0；该字段记录通道1通过APB总线读取RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_CH0    0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_M  (RMT_APB_MEM_RADDR_CH0_V << RMT_APB_MEM_RADDR_CH0_S)
#define RMT_APB_MEM_RADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_S  10

/** RMT_CH2ADDR_REG寄存器通道2地址寄存器
 */
#define RMT_CH2ADDR_REG (DR_REG_RMT_BASE + 0x48)
/** RMT_APB_MEM_WADDR_CH0:RO；位位置：[8:0]；默认值：0；该字段记录通道2通过APB总线写入RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_CH0    0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_M  (RMT_APB_MEM_WADDR_CH0_V << RMT_APB_MEM_WADDR_CH0_S)
#define RMT_APB_MEM_WADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_S  0
/** RMT_APB_MEM_RADDR_CH0:RO；比特位置：[18:10]；默认值：0；该字段记录通道2通过APB总线读取RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_RADDR_CH0    0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_M  (RMT_APB_MEM_RADDR_CH0_V << RMT_APB_MEM_RADDR_CH0_S)
#define RMT_APB_MEM_RADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_S  10

/** RMT_CH3ADDR_REG寄存器通道3地址寄存器
 */
#define RMT_CH3ADDR_REG (DR_REG_RMT_BASE + 0x4c)
/** RMT_APB_MEM_WADDR_CH0:RO；位位置：[8:0]；默认值：0；该字段记录通道3通过APB总线写入RAM时的内存地址偏移。
 */
#define RMT_APB_MEM_WADDR_CH0    0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_M  (RMT_APB_MEM_WADDR_CH0_V << RMT_APB_MEM_WADDR_CH0_S)
#define RMT_APB_MEM_WADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_WADDR_CH0_S  0
/** RMT_APB_MEM_RADDR_CH0:RO；比特位置：[18:10]；默认值：0；该字段记录通道3通过APB总线读取RAM时的存储器地址偏移。
 */
#define RMT_APB_MEM_RADDR_CH0    0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_M  (RMT_APB_MEM_RADDR_CH0_V << RMT_APB_MEM_RADDR_CH0_S)
#define RMT_APB_MEM_RADDR_CH0_V  0x000001FFU
#define RMT_APB_MEM_RADDR_CH0_S  10

/** RMT_INT_RAW_REG寄存器原始中断状态寄存器
 */
#define RMT_INT_RAW_REG (DR_REG_RMT_BASE + 0x50)
/** RMT_CH0_TX_END_INT_RAW:RO；位位置：[0]；默认值：0；信道0的中断原始位。传输结束时触发。
 */
#define RMT_CH0_TX_END_INT_RAW    (BIT(0))
#define RMT_CH0_TX_END_INT_RAW_M  (RMT_CH0_TX_END_INT_RAW_V << RMT_CH0_TX_END_INT_RAW_S)
#define RMT_CH0_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH0_TX_END_INT_RAW_S  0
/** RMT_CH0_RX_END_INT_RAW:RO；位位置：[1]；默认值：0；信道0的中断原始位。接收结束时触发。
 */
#define RMT_CH0_RX_END_INT_RAW    (BIT(1))
#define RMT_CH0_RX_END_INT_RAW_M  (RMT_CH0_RX_END_INT_RAW_V << RMT_CH0_RX_END_INT_RAW_S)
#define RMT_CH0_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH0_RX_END_INT_RAW_S  1
/** RMT_CH0_ERR_INT_RAW:RO；位位置：[2]；默认值：0；通道0的中断原始位。发生错误时触发。
 */
#define RMT_CH0_ERR_INT_RAW    (BIT(2))
#define RMT_CH0_ERR_INT_RAW_M  (RMT_CH0_ERR_INT_RAW_V << RMT_CH0_ERR_INT_RAW_S)
#define RMT_CH0_ERR_INT_RAW_V  0x00000001U
#define RMT_CH0_ERR_INT_RAW_S  2
/** RMT_CH1_TX_END_INT_RAW:RO；位位置：[3]；默认值：0；信道1的中断原始位。传输结束时触发。
 */
#define RMT_CH1_TX_END_INT_RAW    (BIT(3))
#define RMT_CH1_TX_END_INT_RAW_M  (RMT_CH1_TX_END_INT_RAW_V << RMT_CH1_TX_END_INT_RAW_S)
#define RMT_CH1_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH1_TX_END_INT_RAW_S  3
/** RMT_CH1_RX_END_INT_RAW:RO；位位置：[4]；默认值：0；信道1的中断原始位。接收结束时触发。
 */
#define RMT_CH1_RX_END_INT_RAW    (BIT(4))
#define RMT_CH1_RX_END_INT_RAW_M  (RMT_CH1_RX_END_INT_RAW_V << RMT_CH1_RX_END_INT_RAW_S)
#define RMT_CH1_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH1_RX_END_INT_RAW_S  4
/** RMT_CH1_ERR_INT_RAW:RO；位位置：[5]；默认值：0；通道1的中断原始位。发生错误时触发。
 */
#define RMT_CH1_ERR_INT_RAW    (BIT(5))
#define RMT_CH1_ERR_INT_RAW_M  (RMT_CH1_ERR_INT_RAW_V << RMT_CH1_ERR_INT_RAW_S)
#define RMT_CH1_ERR_INT_RAW_V  0x00000001U
#define RMT_CH1_ERR_INT_RAW_S  5
/** RMT_CH2_TX_END_INT_RAW:RO；位位置：[6]；默认值：0；信道2的中断原始位。传输结束时触发。
 */
#define RMT_CH2_TX_END_INT_RAW    (BIT(6))
#define RMT_CH2_TX_END_INT_RAW_M  (RMT_CH2_TX_END_INT_RAW_V << RMT_CH2_TX_END_INT_RAW_S)
#define RMT_CH2_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH2_TX_END_INT_RAW_S  6
/** RMT_CH2_RX_END_INT_RAW:RO；位位置：[7]；默认值：0；信道2的中断原始位。接收结束时触发。
 */
#define RMT_CH2_RX_END_INT_RAW    (BIT(7))
#define RMT_CH2_RX_END_INT_RAW_M  (RMT_CH2_RX_END_INT_RAW_V << RMT_CH2_RX_END_INT_RAW_S)
#define RMT_CH2_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH2_RX_END_INT_RAW_S  7
/** RMT_CH2_ERR_INT_RAW:RO；位位置：[8]；默认值：0；通道2的中断原始位。发生错误时触发。
 */
#define RMT_CH2_ERR_INT_RAW    (BIT(8))
#define RMT_CH2_ERR_INT_RAW_M  (RMT_CH2_ERR_INT_RAW_V << RMT_CH2_ERR_INT_RAW_S)
#define RMT_CH2_ERR_INT_RAW_V  0x00000001U
#define RMT_CH2_ERR_INT_RAW_S  8
/** RMT_CH3_TX_END_INT_RAW:RO；位位置：[9]；默认值：0；信道3的中断原始位。传输结束时触发。
 */
#define RMT_CH3_TX_END_INT_RAW    (BIT(9))
#define RMT_CH3_TX_END_INT_RAW_M  (RMT_CH3_TX_END_INT_RAW_V << RMT_CH3_TX_END_INT_RAW_S)
#define RMT_CH3_TX_END_INT_RAW_V  0x00000001U
#define RMT_CH3_TX_END_INT_RAW_S  9
/** RMT_CH3_RX_END_INT_RAW:RO；位位置：[10]；默认值：0；信道3的中断原始位。接收结束时触发。
 */
#define RMT_CH3_RX_END_INT_RAW    (BIT(10))
#define RMT_CH3_RX_END_INT_RAW_M  (RMT_CH3_RX_END_INT_RAW_V << RMT_CH3_RX_END_INT_RAW_S)
#define RMT_CH3_RX_END_INT_RAW_V  0x00000001U
#define RMT_CH3_RX_END_INT_RAW_S  10
/** RMT_CH3_ERR_INT_RAW:RO；位位置：[11]；默认值：0；通道3的中断原始位。发生错误时触发。
 */
#define RMT_CH3_ERR_INT_RAW    (BIT(11))
#define RMT_CH3_ERR_INT_RAW_M  (RMT_CH3_ERR_INT_RAW_V << RMT_CH3_ERR_INT_RAW_S)
#define RMT_CH3_ERR_INT_RAW_V  0x00000001U
#define RMT_CH3_ERR_INT_RAW_S  11
/** RMT_CH0_TX_THR_EVENT_INT_RAW:RO；位位置：[12]；默认值：0；通道0的中断原始位。当变送器发送的数据超过配置值时触发。
 */
#define RMT_CH0_TX_THR_EVENT_INT_RAW    (BIT(12))
#define RMT_CH0_TX_THR_EVENT_INT_RAW_M  (RMT_CH0_TX_THR_EVENT_INT_RAW_V << RMT_CH0_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH0_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_RAW_S  12
/** RMT_CH1_TX_THR_EVENT_INT_RAW:RO；位位置：[13]；默认值：0；通道1的中断原始位。当变送器发送的数据超过配置值时触发。
 */
#define RMT_CH1_TX_THR_EVENT_INT_RAW    (BIT(13))
#define RMT_CH1_TX_THR_EVENT_INT_RAW_M  (RMT_CH1_TX_THR_EVENT_INT_RAW_V << RMT_CH1_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH1_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_RAW_S  13
/** RMT_CH2_TX_THR_EVENT_INT_RAW:RO；位位置：[14]；默认值：0；通道2的中断原始位。当变送器发送的数据超过配置值时触发。
 */
#define RMT_CH2_TX_THR_EVENT_INT_RAW    (BIT(14))
#define RMT_CH2_TX_THR_EVENT_INT_RAW_M  (RMT_CH2_TX_THR_EVENT_INT_RAW_V << RMT_CH2_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH2_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_RAW_S  14
/** RMT_CH3_TX_THR_EVENT_INT_RAW:RO；位位置：[15]；默认值：0；通道3的中断原始位。当变送器发送的数据超过配置值时触发。
 */
#define RMT_CH3_TX_THR_EVENT_INT_RAW    (BIT(15))
#define RMT_CH3_TX_THR_EVENT_INT_RAW_M  (RMT_CH3_TX_THR_EVENT_INT_RAW_V << RMT_CH3_TX_THR_EVENT_INT_RAW_S)
#define RMT_CH3_TX_THR_EVENT_INT_RAW_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_RAW_S  15
/** RMT_CH0_TX_lop_INT_RAW:RO；位位置：[16]；默认值：0；通道0的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH0_TX_LOOP_INT_RAW    (BIT(16))
#define RMT_CH0_TX_LOOP_INT_RAW_M  (RMT_CH0_TX_LOOP_INT_RAW_V << RMT_CH0_TX_LOOP_INT_RAW_S)
#define RMT_CH0_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_RAW_S  16
/** RMT_CH1_TX_LOOP_INT_RAW:RO；位位置：[17]；默认值：0；通道1的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH1_TX_LOOP_INT_RAW    (BIT(17))
#define RMT_CH1_TX_LOOP_INT_RAW_M  (RMT_CH1_TX_LOOP_INT_RAW_V << RMT_CH1_TX_LOOP_INT_RAW_S)
#define RMT_CH1_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_RAW_S  17
/** RMT_CH2_TX_LOOP_INT_RAW:RO；位位置：[18]；默认值：0；通道2的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH2_TX_LOOP_INT_RAW    (BIT(18))
#define RMT_CH2_TX_LOOP_INT_RAW_M  (RMT_CH2_TX_LOOP_INT_RAW_V << RMT_CH2_TX_LOOP_INT_RAW_S)
#define RMT_CH2_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_RAW_S  18
/** RMT_CH3_TX_LOOP_INT_RAW:RO；位位置：[19]；默认值：0；通道3的中断原始位。当循环计数达到配置的阈值时触发。
 */
#define RMT_CH3_TX_LOOP_INT_RAW    (BIT(19))
#define RMT_CH3_TX_LOOP_INT_RAW_M  (RMT_CH3_TX_LOOP_INT_RAW_V << RMT_CH3_TX_LOOP_INT_RAW_S)
#define RMT_CH3_TX_LOOP_INT_RAW_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_RAW_S  19

/** RMT_INT_ST_REG寄存器屏蔽中断状态寄存器
 */
#define RMT_INT_ST_REG (DR_REG_RMT_BASE + 0x54)
/** RMT_CH0_TX_END_INT_ST:RO；位位置：[0]；默认值：0；RMT_CH0_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH0_TX_END_INT_ST    (BIT(0))
#define RMT_CH0_TX_END_INT_ST_M  (RMT_CH0_TX_END_INT_ST_V << RMT_CH0_TX_END_INT_ST_S)
#define RMT_CH0_TX_END_INT_ST_V  0x00000001U
#define RMT_CH0_TX_END_INT_ST_S  0
/** RMT_CH0_RX_END_INT_ST:RO；位位置：[1]；默认值：0；RMT_CH0_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH0_RX_END_INT_ST    (BIT(1))
#define RMT_CH0_RX_END_INT_ST_M  (RMT_CH0_RX_END_INT_ST_V << RMT_CH0_RX_END_INT_ST_S)
#define RMT_CH0_RX_END_INT_ST_V  0x00000001U
#define RMT_CH0_RX_END_INT_ST_S  1
/** RMT_CH0_ERR_INT_ST:RO；位位置：[2]；默认值：0；RMT_CH0_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH0_ERR_INT_ST    (BIT(2))
#define RMT_CH0_ERR_INT_ST_M  (RMT_CH0_ERR_INT_ST_V << RMT_CH0_ERR_INT_ST_S)
#define RMT_CH0_ERR_INT_ST_V  0x00000001U
#define RMT_CH0_ERR_INT_ST_S  2
/** RMT_CH1_TX_END_INT_ST:RO；位位置：[3]；默认值：0；RMT_CH1_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH1_TX_END_INT_ST    (BIT(3))
#define RMT_CH1_TX_END_INT_ST_M  (RMT_CH1_TX_END_INT_ST_V << RMT_CH1_TX_END_INT_ST_S)
#define RMT_CH1_TX_END_INT_ST_V  0x00000001U
#define RMT_CH1_TX_END_INT_ST_S  3
/** RMT_CH1_RX_END_INT_ST:RO；位位置：[4]；默认值：0；RMT_CH1_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH1_RX_END_INT_ST    (BIT(4))
#define RMT_CH1_RX_END_INT_ST_M  (RMT_CH1_RX_END_INT_ST_V << RMT_CH1_RX_END_INT_ST_S)
#define RMT_CH1_RX_END_INT_ST_V  0x00000001U
#define RMT_CH1_RX_END_INT_ST_S  4
/** RMT_CH1_ERR_INT_ST:RO；位位置：[5]；默认值：0；RMT_CH1_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH1_ERR_INT_ST    (BIT(5))
#define RMT_CH1_ERR_INT_ST_M  (RMT_CH1_ERR_INT_ST_V << RMT_CH1_ERR_INT_ST_S)
#define RMT_CH1_ERR_INT_ST_V  0x00000001U
#define RMT_CH1_ERR_INT_ST_S  5
/** RMT_CH2_TX_END_INT_ST:RO；位位置：[6]；默认值：0；RMT_CH2_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH2_TX_END_INT_ST    (BIT(6))
#define RMT_CH2_TX_END_INT_ST_M  (RMT_CH2_TX_END_INT_ST_V << RMT_CH2_TX_END_INT_ST_S)
#define RMT_CH2_TX_END_INT_ST_V  0x00000001U
#define RMT_CH2_TX_END_INT_ST_S  6
/** RMT_CH2_RX_END_INT_ST:RO；位位置：[7]；默认值：0；RMT_CH2_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH2_RX_END_INT_ST    (BIT(7))
#define RMT_CH2_RX_END_INT_ST_M  (RMT_CH2_RX_END_INT_ST_V << RMT_CH2_RX_END_INT_ST_S)
#define RMT_CH2_RX_END_INT_ST_V  0x00000001U
#define RMT_CH2_RX_END_INT_ST_S  7
/** RMT_CH2_ERR_INT_ST:RO；位位置：[8]；默认值：0；RMT_CH2_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH2_ERR_INT_ST    (BIT(8))
#define RMT_CH2_ERR_INT_ST_M  (RMT_CH2_ERR_INT_ST_V << RMT_CH2_ERR_INT_ST_S)
#define RMT_CH2_ERR_INT_ST_V  0x00000001U
#define RMT_CH2_ERR_INT_ST_S  8
/** RMT_CH3_TX_END_INT_ST:RO；位位置：[9]；默认值：0；RMT_CH3_TX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH3_TX_END_INT_ST    (BIT(9))
#define RMT_CH3_TX_END_INT_ST_M  (RMT_CH3_TX_END_INT_ST_V << RMT_CH3_TX_END_INT_ST_S)
#define RMT_CH3_TX_END_INT_ST_V  0x00000001U
#define RMT_CH3_TX_END_INT_ST_S  9
/** RMT_CH3_RX_END_INT_ST:RO；位位置：[10]；默认值：0；RMT_CH3_RX_END_INT的屏蔽中断状态位。
 */
#define RMT_CH3_RX_END_INT_ST    (BIT(10))
#define RMT_CH3_RX_END_INT_ST_M  (RMT_CH3_RX_END_INT_ST_V << RMT_CH3_RX_END_INT_ST_S)
#define RMT_CH3_RX_END_INT_ST_V  0x00000001U
#define RMT_CH3_RX_END_INT_ST_S  10
/** RMT_CH3_ERR_INT_ST:RO；位位置：[11]；默认值：0；RMT_CH3_ERR_INT的屏蔽中断状态位。
 */
#define RMT_CH3_ERR_INT_ST    (BIT(11))
#define RMT_CH3_ERR_INT_ST_M  (RMT_CH3_ERR_INT_ST_V << RMT_CH3_ERR_INT_ST_S)
#define RMT_CH3_ERR_INT_ST_V  0x00000001U
#define RMT_CH3_ERR_INT_ST_S  11
/** RMT_CH0_TX_THR_EVENT_INT_ST:RO；位位置：[12]；默认值：0；RMT_CH0_TTX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH0_TX_THR_EVENT_INT_ST    (BIT(12))
#define RMT_CH0_TX_THR_EVENT_INT_ST_M  (RMT_CH0_TX_THR_EVENT_INT_ST_V << RMT_CH0_TX_THR_EVENT_INT_ST_S)
#define RMT_CH0_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_ST_S  12
/** RMT_CH1_TX_THR_EVENT_INT_ST:RO；位位置：[13]；默认值：0；RMT_CH1_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH1_TX_THR_EVENT_INT_ST    (BIT(13))
#define RMT_CH1_TX_THR_EVENT_INT_ST_M  (RMT_CH1_TX_THR_EVENT_INT_ST_V << RMT_CH1_TX_THR_EVENT_INT_ST_S)
#define RMT_CH1_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_ST_S  13
/** RMT_CH2_TX_THR_EVENT_INT_ST:RO；位位置：[14]；默认值：0；RMT_CH2_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH2_TX_THR_EVENT_INT_ST    (BIT(14))
#define RMT_CH2_TX_THR_EVENT_INT_ST_M  (RMT_CH2_TX_THR_EVENT_INT_ST_V << RMT_CH2_TX_THR_EVENT_INT_ST_S)
#define RMT_CH2_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_ST_S  14
/** RMT_CH3_TX_THR_EVENT_INT_ST:RO；位位置：[15]；默认值：0；RMT_CH3_TX_THR_EVENT_INT的屏蔽中断状态位。
 */
#define RMT_CH3_TX_THR_EVENT_INT_ST    (BIT(15))
#define RMT_CH3_TX_THR_EVENT_INT_ST_M  (RMT_CH3_TX_THR_EVENT_INT_ST_V << RMT_CH3_TX_THR_EVENT_INT_ST_S)
#define RMT_CH3_TX_THR_EVENT_INT_ST_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_ST_S  15
/** RMT_CH0_TX_lop_INT_ST:RO；位位置：[16]；默认值：0；RMT_CH0_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH0_TX_LOOP_INT_ST    (BIT(16))
#define RMT_CH0_TX_LOOP_INT_ST_M  (RMT_CH0_TX_LOOP_INT_ST_V << RMT_CH0_TX_LOOP_INT_ST_S)
#define RMT_CH0_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_ST_S  16
/** RMT_CH1_TX_LOOP_INT_ST:RO；位位置：[17]；默认值：0；RMT_CH1_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH1_TX_LOOP_INT_ST    (BIT(17))
#define RMT_CH1_TX_LOOP_INT_ST_M  (RMT_CH1_TX_LOOP_INT_ST_V << RMT_CH1_TX_LOOP_INT_ST_S)
#define RMT_CH1_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_ST_S  17
/** RMT_CH2_TX_LOOP_INT_ST:RO；位位置：[18]；默认值：0；RMT_CH2_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH2_TX_LOOP_INT_ST    (BIT(18))
#define RMT_CH2_TX_LOOP_INT_ST_M  (RMT_CH2_TX_LOOP_INT_ST_V << RMT_CH2_TX_LOOP_INT_ST_S)
#define RMT_CH2_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_ST_S  18
/** RMT_CH3_TX_LOOP_INT_ST:RO；位位置：[19]；默认值：0；RMT_CH3_TX_LOOP_INT的屏蔽中断状态位。
 */
#define RMT_CH3_TX_LOOP_INT_ST    (BIT(19))
#define RMT_CH3_TX_LOOP_INT_ST_M  (RMT_CH3_TX_LOOP_INT_ST_V << RMT_CH3_TX_LOOP_INT_ST_S)
#define RMT_CH3_TX_LOOP_INT_ST_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_ST_S  19

/** RMT_INT_ENA_REG寄存器中断启用寄存器
 */
#define RMT_INT_ENA_REG (DR_REG_RMT_BASE + 0x58)
/** RMT_CH0_TX_END_INT_ENA:R/W；位位置：[0]；默认值：0；RMT_CH0_TX_END_INT的中断启用位。
 */
#define RMT_CH0_TX_END_INT_ENA    (BIT(0))
#define RMT_CH0_TX_END_INT_ENA_M  (RMT_CH0_TX_END_INT_ENA_V << RMT_CH0_TX_END_INT_ENA_S)
#define RMT_CH0_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH0_TX_END_INT_ENA_S  0
/** RMT_CH0_RX_END_INT_ENA:R/W；位位置：[1]；默认值：0；RMT_CH0_RX_END_INT的中断启用位。
 */
#define RMT_CH0_RX_END_INT_ENA    (BIT(1))
#define RMT_CH0_RX_END_INT_ENA_M  (RMT_CH0_RX_END_INT_ENA_V << RMT_CH0_RX_END_INT_ENA_S)
#define RMT_CH0_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH0_RX_END_INT_ENA_S  1
/** RMT_CH0_ERR_INT_ENA:R/W；位位置：[2]；默认值：0；RMT_CH0_ERR_INT的中断启用位。
 */
#define RMT_CH0_ERR_INT_ENA    (BIT(2))
#define RMT_CH0_ERR_INT_ENA_M  (RMT_CH0_ERR_INT_ENA_V << RMT_CH0_ERR_INT_ENA_S)
#define RMT_CH0_ERR_INT_ENA_V  0x00000001U
#define RMT_CH0_ERR_INT_ENA_S  2
/** RMT_CH1_TX_END_INT_ENA：R/W；位位置：[3]；默认值：0；RMT_CH1_TX_END_INT的中断启用位。
 */
#define RMT_CH1_TX_END_INT_ENA    (BIT(3))
#define RMT_CH1_TX_END_INT_ENA_M  (RMT_CH1_TX_END_INT_ENA_V << RMT_CH1_TX_END_INT_ENA_S)
#define RMT_CH1_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH1_TX_END_INT_ENA_S  3
/** RMT_CH1_RX_END_INT_ENA:R/W；位位置：[4]；默认值：0；RMT_CH1_RX_END_INT的中断启用位。
 */
#define RMT_CH1_RX_END_INT_ENA    (BIT(4))
#define RMT_CH1_RX_END_INT_ENA_M  (RMT_CH1_RX_END_INT_ENA_V << RMT_CH1_RX_END_INT_ENA_S)
#define RMT_CH1_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH1_RX_END_INT_ENA_S  4
/** RMT_CH1_ERR_INT_ENA:R/W；位位置：[5]；默认值：0；RMT_CH1_ERR_INT的中断启用位。
 */
#define RMT_CH1_ERR_INT_ENA    (BIT(5))
#define RMT_CH1_ERR_INT_ENA_M  (RMT_CH1_ERR_INT_ENA_V << RMT_CH1_ERR_INT_ENA_S)
#define RMT_CH1_ERR_INT_ENA_V  0x00000001U
#define RMT_CH1_ERR_INT_ENA_S  5
/** RMT_CH2_TX_END_INT_ENA：R/W；位位置：[6]；默认值：0；RMT_CH2_TX_END_INT的中断启用位。
 */
#define RMT_CH2_TX_END_INT_ENA    (BIT(6))
#define RMT_CH2_TX_END_INT_ENA_M  (RMT_CH2_TX_END_INT_ENA_V << RMT_CH2_TX_END_INT_ENA_S)
#define RMT_CH2_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH2_TX_END_INT_ENA_S  6
/** RMT_CH2_RX_END_INT_ENA:R/W；位位置：[7]；默认值：0；RMT_CH2_RX_END_INT的中断启用位。
 */
#define RMT_CH2_RX_END_INT_ENA    (BIT(7))
#define RMT_CH2_RX_END_INT_ENA_M  (RMT_CH2_RX_END_INT_ENA_V << RMT_CH2_RX_END_INT_ENA_S)
#define RMT_CH2_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH2_RX_END_INT_ENA_S  7
/** RMT_CH2_ERR_INT_ENA:R/W；位位置：[8]；默认值：0；RMT_CH2_ERR_INT的中断启用位。
 */
#define RMT_CH2_ERR_INT_ENA    (BIT(8))
#define RMT_CH2_ERR_INT_ENA_M  (RMT_CH2_ERR_INT_ENA_V << RMT_CH2_ERR_INT_ENA_S)
#define RMT_CH2_ERR_INT_ENA_V  0x00000001U
#define RMT_CH2_ERR_INT_ENA_S  8
/** RMT_CH3_TX_END_INT_ENA：R/W；位位置：[9]；默认值：0；RMT_CH3_TX_END_INT的中断启用位。
 */
#define RMT_CH3_TX_END_INT_ENA    (BIT(9))
#define RMT_CH3_TX_END_INT_ENA_M  (RMT_CH3_TX_END_INT_ENA_V << RMT_CH3_TX_END_INT_ENA_S)
#define RMT_CH3_TX_END_INT_ENA_V  0x00000001U
#define RMT_CH3_TX_END_INT_ENA_S  9
/** RMT_CH3_RX_END_INT_ENA:R/W；位位置：[10]；默认值：0；RMT_CH3_RX_END_INT的中断启用位。
 */
#define RMT_CH3_RX_END_INT_ENA    (BIT(10))
#define RMT_CH3_RX_END_INT_ENA_M  (RMT_CH3_RX_END_INT_ENA_V << RMT_CH3_RX_END_INT_ENA_S)
#define RMT_CH3_RX_END_INT_ENA_V  0x00000001U
#define RMT_CH3_RX_END_INT_ENA_S  10
/** RMT_CH3_ERR_INT_ENA：R/W；位位置：[11]；默认值：0；RMT_CH3_ERR_INT的中断启用位。
 */
#define RMT_CH3_ERR_INT_ENA    (BIT(11))
#define RMT_CH3_ERR_INT_ENA_M  (RMT_CH3_ERR_INT_ENA_V << RMT_CH3_ERR_INT_ENA_S)
#define RMT_CH3_ERR_INT_ENA_V  0x00000001U
#define RMT_CH3_ERR_INT_ENA_S  11
/** RMT_CH0_TX_THR_EVENT_INT_ENA:R/W；位位置：[12]；默认值：0；RMT_CH0_TTX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH0_TX_THR_EVENT_INT_ENA    (BIT(12))
#define RMT_CH0_TX_THR_EVENT_INT_ENA_M  (RMT_CH0_TX_THR_EVENT_INT_ENA_V << RMT_CH0_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH0_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_ENA_S  12
/** RMT_CH1_TX_THR_EVENT_INT_ENA:R/W；位位置：[13]；默认值：0；RMT_CH1_TX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH1_TX_THR_EVENT_INT_ENA    (BIT(13))
#define RMT_CH1_TX_THR_EVENT_INT_ENA_M  (RMT_CH1_TX_THR_EVENT_INT_ENA_V << RMT_CH1_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH1_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_ENA_S  13
/** RMT_CH2_TX_THR_EVENT_INT_ENA:R/W；位位置：[14]；默认值：0；RMT_CH2_TX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH2_TX_THR_EVENT_INT_ENA    (BIT(14))
#define RMT_CH2_TX_THR_EVENT_INT_ENA_M  (RMT_CH2_TX_THR_EVENT_INT_ENA_V << RMT_CH2_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH2_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_ENA_S  14
/** RMT_CH3_TX_THR_EVENT_INT_ENA:R/W；位位置：[15]；默认值：0；RMT_CH3_TX_THR_EVENT_INT的中断启用位。
 */
#define RMT_CH3_TX_THR_EVENT_INT_ENA    (BIT(15))
#define RMT_CH3_TX_THR_EVENT_INT_ENA_M  (RMT_CH3_TX_THR_EVENT_INT_ENA_V << RMT_CH3_TX_THR_EVENT_INT_ENA_S)
#define RMT_CH3_TX_THR_EVENT_INT_ENA_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_ENA_S  15
/** RMT_CH0_TX_lop_INT_ENA:R/W；位位置：[16]；默认值：0；RMT_CH0_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH0_TX_LOOP_INT_ENA    (BIT(16))
#define RMT_CH0_TX_LOOP_INT_ENA_M  (RMT_CH0_TX_LOOP_INT_ENA_V << RMT_CH0_TX_LOOP_INT_ENA_S)
#define RMT_CH0_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_ENA_S  16
/** RMT_CH1_TX_LOOP_INT_ENA：R/W；位位置：[17]；默认值：0；RMT_CH1_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH1_TX_LOOP_INT_ENA    (BIT(17))
#define RMT_CH1_TX_LOOP_INT_ENA_M  (RMT_CH1_TX_LOOP_INT_ENA_V << RMT_CH1_TX_LOOP_INT_ENA_S)
#define RMT_CH1_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_ENA_S  17
/** RMT_CH2_TX_LOOP_INT_ENA：R/W；位位置：[18]；默认值：0；RMT_CH2_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH2_TX_LOOP_INT_ENA    (BIT(18))
#define RMT_CH2_TX_LOOP_INT_ENA_M  (RMT_CH2_TX_LOOP_INT_ENA_V << RMT_CH2_TX_LOOP_INT_ENA_S)
#define RMT_CH2_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_ENA_S  18
/** RMT_CH3_TX_LOOP_INT_ENA：R/W；位位置：[19]；默认值：0；RMT_CH3_TX_LOOP_INT的中断启用位。
 */
#define RMT_CH3_TX_LOOP_INT_ENA    (BIT(19))
#define RMT_CH3_TX_LOOP_INT_ENA_M  (RMT_CH3_TX_LOOP_INT_ENA_V << RMT_CH3_TX_LOOP_INT_ENA_S)
#define RMT_CH3_TX_LOOP_INT_ENA_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_ENA_S  19

/** RMT_INT_CLR_REG寄存器中断清除寄存器
 */
#define RMT_INT_CLR_REG (DR_REG_RMT_BASE + 0x5c)
/** RMT_CH0_TX_END_INT_CLR:WO；位位置：[0]；默认值：0；设置此位以清除RMT_CH0_TX_END_INT中断。
 */
#define RMT_CH0_TX_END_INT_CLR    (BIT(0))
#define RMT_CH0_TX_END_INT_CLR_M  (RMT_CH0_TX_END_INT_CLR_V << RMT_CH0_TX_END_INT_CLR_S)
#define RMT_CH0_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH0_TX_END_INT_CLR_S  0
/** RMT_CH0_RX_END_INT_CLR:WO；位位置：[1]；默认值：0；设置此位以清除RMT_CH0_RX_END_INT中断。
 */
#define RMT_CH0_RX_END_INT_CLR    (BIT(1))
#define RMT_CH0_RX_END_INT_CLR_M  (RMT_CH0_RX_END_INT_CLR_V << RMT_CH0_RX_END_INT_CLR_S)
#define RMT_CH0_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH0_RX_END_INT_CLR_S  1
/** RMT_CH0_ERR_INT_CLR:WO；位位置：[2]；默认值：0；设置此位以清除RMT_CH0_ERR_INT中断。
 */
#define RMT_CH0_ERR_INT_CLR    (BIT(2))
#define RMT_CH0_ERR_INT_CLR_M  (RMT_CH0_ERR_INT_CLR_V << RMT_CH0_ERR_INT_CLR_S)
#define RMT_CH0_ERR_INT_CLR_V  0x00000001U
#define RMT_CH0_ERR_INT_CLR_S  2
/** RMT_CH1_TX_END_INT_CLR:WO；位位置：[3]；默认值：0；设置此位以清除RMT_CH1_TX_END_INT中断。
 */
#define RMT_CH1_TX_END_INT_CLR    (BIT(3))
#define RMT_CH1_TX_END_INT_CLR_M  (RMT_CH1_TX_END_INT_CLR_V << RMT_CH1_TX_END_INT_CLR_S)
#define RMT_CH1_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH1_TX_END_INT_CLR_S  3
/** RMT_CH1_RX_END_INT_CLR:WO；位位置：[4]；默认值：0；设置此位以清除RMT_CH1_RX_END_INT中断。
 */
#define RMT_CH1_RX_END_INT_CLR    (BIT(4))
#define RMT_CH1_RX_END_INT_CLR_M  (RMT_CH1_RX_END_INT_CLR_V << RMT_CH1_RX_END_INT_CLR_S)
#define RMT_CH1_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH1_RX_END_INT_CLR_S  4
/** RMT_CH1_ERR_INT_CLR:WO；位位置：[5]；默认值：0；设置此位以清除RMT_CH1_ERR_INT中断。
 */
#define RMT_CH1_ERR_INT_CLR    (BIT(5))
#define RMT_CH1_ERR_INT_CLR_M  (RMT_CH1_ERR_INT_CLR_V << RMT_CH1_ERR_INT_CLR_S)
#define RMT_CH1_ERR_INT_CLR_V  0x00000001U
#define RMT_CH1_ERR_INT_CLR_S  5
/** RMT_CH2_TX_END_INT_CLR:WO；位位置：[6]；默认值：0；设置此位以清除RMT_CH2_TX_END_INT中断。
 */
#define RMT_CH2_TX_END_INT_CLR    (BIT(6))
#define RMT_CH2_TX_END_INT_CLR_M  (RMT_CH2_TX_END_INT_CLR_V << RMT_CH2_TX_END_INT_CLR_S)
#define RMT_CH2_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH2_TX_END_INT_CLR_S  6
/** RMT_CH2_RX_END_INT_CLR:WO；位位置：[7]；默认值：0；设置此位以清除RMT_CH2_RX_END_INT中断。
 */
#define RMT_CH2_RX_END_INT_CLR    (BIT(7))
#define RMT_CH2_RX_END_INT_CLR_M  (RMT_CH2_RX_END_INT_CLR_V << RMT_CH2_RX_END_INT_CLR_S)
#define RMT_CH2_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH2_RX_END_INT_CLR_S  7
/** RMT_CH2_ERR_INT_CLR:WO；位位置：[8]；默认值：0；设置此位以清除RMT_CH2_ERR_INT中断。
 */
#define RMT_CH2_ERR_INT_CLR    (BIT(8))
#define RMT_CH2_ERR_INT_CLR_M  (RMT_CH2_ERR_INT_CLR_V << RMT_CH2_ERR_INT_CLR_S)
#define RMT_CH2_ERR_INT_CLR_V  0x00000001U
#define RMT_CH2_ERR_INT_CLR_S  8
/** RMT_CH3_TX_END_INT_CLR:WO；位位置：[9]；默认值：0；设置此位以清除RMT_CH3_TX_END_INT中断。
 */
#define RMT_CH3_TX_END_INT_CLR    (BIT(9))
#define RMT_CH3_TX_END_INT_CLR_M  (RMT_CH3_TX_END_INT_CLR_V << RMT_CH3_TX_END_INT_CLR_S)
#define RMT_CH3_TX_END_INT_CLR_V  0x00000001U
#define RMT_CH3_TX_END_INT_CLR_S  9
/** RMT_CH3_RX_END_INT_CLR:WO；位位置：[10]；默认值：0；设置此位以清除RMT_CH3_RX_END_INT中断。
 */
#define RMT_CH3_RX_END_INT_CLR    (BIT(10))
#define RMT_CH3_RX_END_INT_CLR_M  (RMT_CH3_RX_END_INT_CLR_V << RMT_CH3_RX_END_INT_CLR_S)
#define RMT_CH3_RX_END_INT_CLR_V  0x00000001U
#define RMT_CH3_RX_END_INT_CLR_S  10
/** RMT_CH3_ERR_INT_CLR:WO；位位置：[11]；默认值：0；设置此位以清除RMT_CH3_ERR_INT中断。
 */
#define RMT_CH3_ERR_INT_CLR    (BIT(11))
#define RMT_CH3_ERR_INT_CLR_M  (RMT_CH3_ERR_INT_CLR_V << RMT_CH3_ERR_INT_CLR_S)
#define RMT_CH3_ERR_INT_CLR_V  0x00000001U
#define RMT_CH3_ERR_INT_CLR_S  11
/** RMT_CH0_TX_THR_EVENT_INT_CLR:WO；位位置：[12]；默认值：0；设置此位以清除RMT_CH0_TX_THR_EVENT_INT中断。
 */
#define RMT_CH0_TX_THR_EVENT_INT_CLR    (BIT(12))
#define RMT_CH0_TX_THR_EVENT_INT_CLR_M  (RMT_CH0_TX_THR_EVENT_INT_CLR_V << RMT_CH0_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH0_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH0_TX_THR_EVENT_INT_CLR_S  12
/** RMT_CH1_TX_THR_EVENT_INT_CLR:WO；位位置：[13]；默认值：0；设置此位以清除RMT_CH1_TX_THR_EVENT_INT中断。
 */
#define RMT_CH1_TX_THR_EVENT_INT_CLR    (BIT(13))
#define RMT_CH1_TX_THR_EVENT_INT_CLR_M  (RMT_CH1_TX_THR_EVENT_INT_CLR_V << RMT_CH1_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH1_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH1_TX_THR_EVENT_INT_CLR_S  13
/** RMT_CH2_TX_THR_EVENT_INT_CLR:WO；位位置：[14]；默认值：0；设置此位以清除RMT_CH2_TX_THR_EVENT_INT中断。
 */
#define RMT_CH2_TX_THR_EVENT_INT_CLR    (BIT(14))
#define RMT_CH2_TX_THR_EVENT_INT_CLR_M  (RMT_CH2_TX_THR_EVENT_INT_CLR_V << RMT_CH2_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH2_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH2_TX_THR_EVENT_INT_CLR_S  14
/** RMT_CH3_TX_THR_EVENT_INT_CLR:WO；位位置：[15]；默认值：0；设置此位以清除RMT_CH3_TX_THR_EVENT_INT中断。
 */
#define RMT_CH3_TX_THR_EVENT_INT_CLR    (BIT(15))
#define RMT_CH3_TX_THR_EVENT_INT_CLR_M  (RMT_CH3_TX_THR_EVENT_INT_CLR_V << RMT_CH3_TX_THR_EVENT_INT_CLR_S)
#define RMT_CH3_TX_THR_EVENT_INT_CLR_V  0x00000001U
#define RMT_CH3_TX_THR_EVENT_INT_CLR_S  15
/** RMT_CH0_TX_lop_INT_CLR:WO；位位置：[16]；默认值：0；设置此位以清除RMT_CH0_TX_LOOP_INT中断。
 */
#define RMT_CH0_TX_LOOP_INT_CLR    (BIT(16))
#define RMT_CH0_TX_LOOP_INT_CLR_M  (RMT_CH0_TX_LOOP_INT_CLR_V << RMT_CH0_TX_LOOP_INT_CLR_S)
#define RMT_CH0_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH0_TX_LOOP_INT_CLR_S  16
/** RMT_CH1_TX_LOOP_INT_CLR:WO；位位置：[17]；默认值：0；设置此位以清除RMT_CH1_TX_LOOP_INT中断。
 */
#define RMT_CH1_TX_LOOP_INT_CLR    (BIT(17))
#define RMT_CH1_TX_LOOP_INT_CLR_M  (RMT_CH1_TX_LOOP_INT_CLR_V << RMT_CH1_TX_LOOP_INT_CLR_S)
#define RMT_CH1_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH1_TX_LOOP_INT_CLR_S  17
/** RMT_CH2_TX_LOOP_INT_CLR:WO；位位置：[18]；默认值：0；设置此位以清除RMT_CH2_TX_LOOP_INT中断。
 */
#define RMT_CH2_TX_LOOP_INT_CLR    (BIT(18))
#define RMT_CH2_TX_LOOP_INT_CLR_M  (RMT_CH2_TX_LOOP_INT_CLR_V << RMT_CH2_TX_LOOP_INT_CLR_S)
#define RMT_CH2_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH2_TX_LOOP_INT_CLR_S  18
/** RMT_CH3_TX_LOOP_INT_CLR:WO；位位置：[19]；默认值：0；设置此位以清除RMT_CH3_TX_LOOP_INT中断。
 */
#define RMT_CH3_TX_LOOP_INT_CLR    (BIT(19))
#define RMT_CH3_TX_LOOP_INT_CLR_M  (RMT_CH3_TX_LOOP_INT_CLR_V << RMT_CH3_TX_LOOP_INT_CLR_S)
#define RMT_CH3_TX_LOOP_INT_CLR_V  0x00000001U
#define RMT_CH3_TX_LOOP_INT_CLR_S  19

/** RMT_CH0CARRIER_DDUTY_REG寄存器通道0占空比配置寄存器
 */
#define RMT_CH0CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x60)
/** RMT_CARRIER_LOW_CH0:R/W；比特位置：[15:0]；默认值：64；该字段用于配置信道0的低电平载波的时钟周期。
 */
#define RMT_CARRIER_LOW_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_M  (RMT_CARRIER_LOW_CH0_V << RMT_CARRIER_LOW_CH0_S)
#define RMT_CARRIER_LOW_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_S  0
/** RMT_CARRIER_HIGH_CH0:R/W；比特位置：[31:16]；默认值：64；该字段用于配置信道0的高电平载波的时钟周期。
 */
#define RMT_CARRIER_HIGH_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_M  (RMT_CARRIER_HIGH_CH0_V << RMT_CARRIER_HIGH_CH0_S)
#define RMT_CARRIER_HIGH_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_S  16

/** RMT_CH1CARRIER_DDUTY_REG寄存器通道1占空比配置寄存器
 */
#define RMT_CH1CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x64)
/** RMT_CARRIER_LOW_CH0:R/W；比特位置：[15:0]；默认值：64；该字段用于配置信道1的低电平载波的时钟周期。
 */
#define RMT_CARRIER_LOW_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_M  (RMT_CARRIER_LOW_CH0_V << RMT_CARRIER_LOW_CH0_S)
#define RMT_CARRIER_LOW_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_S  0
/** RMT_CARRIER_HIGH_CH0:R/W；比特位置：[31:16]；默认值：64；该字段用于配置信道1的高电平载波的时钟周期。
 */
#define RMT_CARRIER_HIGH_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_M  (RMT_CARRIER_HIGH_CH0_V << RMT_CARRIER_HIGH_CH0_S)
#define RMT_CARRIER_HIGH_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_S  16

/** RMT_CH2CARRIR_DUTY_REG寄存器通道2占空比配置寄存器
 */
#define RMT_CH2CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x68)
/** RMT_CARRIER_LOW_CH0:R/W；比特位置：[15:0]；默认值：64；该字段用于配置信道2的低电平载波的时钟周期。
 */
#define RMT_CARRIER_LOW_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_M  (RMT_CARRIER_LOW_CH0_V << RMT_CARRIER_LOW_CH0_S)
#define RMT_CARRIER_LOW_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_S  0
/** RMT_CARRIER_HIGH_CH0:R/W；比特位置：[31:16]；默认值：64；该字段用于配置信道2的高电平载波的时钟周期。
 */
#define RMT_CARRIER_HIGH_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_M  (RMT_CARRIER_HIGH_CH0_V << RMT_CARRIER_HIGH_CH0_S)
#define RMT_CARRIER_HIGH_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_S  16

/** RMT_CH3CARRIER_DUTY_REG寄存器通道3占空比配置寄存器
 */
#define RMT_CH3CARRIER_DUTY_REG (DR_REG_RMT_BASE + 0x6c)
/** RMT_CARRIER_LOW_CH0:R/W；比特位置：[15:0]；默认值：64；该字段用于配置信道3的低电平载波的时钟周期。
 */
#define RMT_CARRIER_LOW_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_M  (RMT_CARRIER_LOW_CH0_V << RMT_CARRIER_LOW_CH0_S)
#define RMT_CARRIER_LOW_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_CH0_S  0
/** RMT_CARRIER_HIGH_CH0:R/W；比特位置：[31:16]；默认值：64；该字段用于配置信道3的高电平载波的时钟周期。
 */
#define RMT_CARRIER_HIGH_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_M  (RMT_CARRIER_HIGH_CH0_V << RMT_CARRIER_HIGH_CH0_S)
#define RMT_CARRIER_HIGH_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_CH0_S  16

/** RMT_CH0_TX_LIM_REG寄存器通道0 TX事件配置寄存器
 */
#define RMT_CH0_TX_LIM_REG (DR_REG_RMT_BASE + 0x70)
/** RMT_TX_LIM_CH0:R/W；位位置：[8:0]；默认值：128；此字段用于配置通道0可以发送的最大条目。当RMT_MEM_SIZE_CH0=1时，此字段可以设置为0~128（6432/16=128）之间的任何值。当RMT_MEM_SIZE_CH0>1时，此字段可以设置为（0~128）RMT_MEM-SIZE_CHO中的任何值。
 */
#define RMT_TX_LIM_CH0    0x000001FFU
#define RMT_TX_LIM_CH0_M  (RMT_TX_LIM_CH0_V << RMT_TX_LIM_CH0_S)
#define RMT_TX_LIM_CH0_V  0x000001FFU
#define RMT_TX_LIM_CH0_S  0
/** RMT_TX_LOOP_NUM_CH0:R/W；比特位置：[18:9]；默认值：0；此字段用于配置启用连续传输模式时的最大循环时间。
 */
#define RMT_TX_LOOP_NUM_CH0    0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_M  (RMT_TX_LOOP_NUM_CH0_V << RMT_TX_LOOP_NUM_CH0_S)
#define RMT_TX_LOOP_NUM_CH0_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_S  9
/** RMT_TX_LOOP_CNT_EN_CH0:R/W；位位置：[19]；默认值：0；此位用于启用循环计数。
 */
#define RMT_TX_LOOP_CNT_EN_CH0    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH0_M  (RMT_TX_LOOP_CNT_EN_CH0_V << RMT_TX_LOOP_CNT_EN_CH0_S)
#define RMT_TX_LOOP_CNT_EN_CH0_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH0_S  19
/** RMT_LOOP_COUNT_RESET_CH0:WO；位位置：[20]；默认值：0；当连续传输模式有效时，该位用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH0    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH0_M  (RMT_LOOP_COUNT_RESET_CH0_V << RMT_LOOP_COUNT_RESET_CH0_S)
#define RMT_LOOP_COUNT_RESET_CH0_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH0_S  20

/** RMT_CH1_TX_LIM_REG寄存器通道1 TX事件配置寄存器
 */
#define RMT_CH1_TX_LIM_REG (DR_REG_RMT_BASE + 0x74)
/** RMT_TX_LIM_CH0:R/W；位位置：[8:0]；默认值：128；此字段用于配置通道1可以发送的最大条目。当RMT_MEM_SIZE_CH1=1时，此字段可以设置为0~128（6432/16=128）之间的任何值。当RMT_MEM_SIZE_CH1>1时，此字段可以设置为（0~128）RMT_MEM-SIZE_CH2中的任何值。
 */
#define RMT_TX_LIM_CH0    0x000001FFU
#define RMT_TX_LIM_CH0_M  (RMT_TX_LIM_CH0_V << RMT_TX_LIM_CH0_S)
#define RMT_TX_LIM_CH0_V  0x000001FFU
#define RMT_TX_LIM_CH0_S  0
/** RMT_TX_LOOP_NUM_CH0:R/W；比特位置：[18:9]；默认值：0；此字段用于配置启用连续传输模式时的最大循环时间。
 */
#define RMT_TX_LOOP_NUM_CH0    0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_M  (RMT_TX_LOOP_NUM_CH0_V << RMT_TX_LOOP_NUM_CH0_S)
#define RMT_TX_LOOP_NUM_CH0_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_S  9
/** RMT_TX_LOOP_CNT_EN_CH0:R/W；位位置：[19]；默认值：0；此位用于启用循环计数。
 */
#define RMT_TX_LOOP_CNT_EN_CH0    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH0_M  (RMT_TX_LOOP_CNT_EN_CH0_V << RMT_TX_LOOP_CNT_EN_CH0_S)
#define RMT_TX_LOOP_CNT_EN_CH0_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH0_S  19
/** RMT_LOOP_COUNT_RESET_CH0:WO；位位置：[20]；默认值：0；当连续传输模式有效时，该位用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH0    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH0_M  (RMT_LOOP_COUNT_RESET_CH0_V << RMT_LOOP_COUNT_RESET_CH0_S)
#define RMT_LOOP_COUNT_RESET_CH0_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH0_S  20

/** RMT_CH2_TX_LIM_REG寄存器通道2 TX事件配置寄存器
 */
#define RMT_CH2_TX_LIM_REG (DR_REG_RMT_BASE + 0x78)
/** RMT_TX_LIM_CH0:R/W；位位置：[8:0]；默认值：128；此字段用于配置通道2可以发送的最大条目。当RMT_MEM_SIZE_CH2=1时，此字段可以设置为0~128（6432/16=128）之间的任何值。当RMT_MEM_SIZE_CH2>1时，此字段可以设置为（0~128）RMT_MEM-SIZE_CH2中的任何值。
 */
#define RMT_TX_LIM_CH0    0x000001FFU
#define RMT_TX_LIM_CH0_M  (RMT_TX_LIM_CH0_V << RMT_TX_LIM_CH0_S)
#define RMT_TX_LIM_CH0_V  0x000001FFU
#define RMT_TX_LIM_CH0_S  0
/** RMT_TX_LOOP_NUM_CH0:R/W；比特位置：[18:9]；默认值：0；此字段用于配置启用连续传输模式时的最大循环时间。
 */
#define RMT_TX_LOOP_NUM_CH0    0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_M  (RMT_TX_LOOP_NUM_CH0_V << RMT_TX_LOOP_NUM_CH0_S)
#define RMT_TX_LOOP_NUM_CH0_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_S  9
/** RMT_TX_LOOP_CNT_EN_CH0:R/W；位位置：[19]；默认值：0；此位用于启用循环计数。
 */
#define RMT_TX_LOOP_CNT_EN_CH0    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH0_M  (RMT_TX_LOOP_CNT_EN_CH0_V << RMT_TX_LOOP_CNT_EN_CH0_S)
#define RMT_TX_LOOP_CNT_EN_CH0_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH0_S  19
/** RMT_LOOP_COUNT_RESET_CH0:WO；位位置：[20]；默认值：0；当连续传输模式有效时，该位用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH0    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH0_M  (RMT_LOOP_COUNT_RESET_CH0_V << RMT_LOOP_COUNT_RESET_CH0_S)
#define RMT_LOOP_COUNT_RESET_CH0_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH0_S  20

/** RMT_CH3_TX_LIM_REG寄存器通道3 TX事件配置寄存器
 */
#define RMT_CH3_TX_LIM_REG (DR_REG_RMT_BASE + 0x7c)
/** RMT_TX_LIM_CH0:R/W；位位置：[8:0]；默认值：128；此字段用于配置通道3可以发送的最大条目。当RMT_MEM_SIZE_CH3=1时，此字段可以设置为0~128（6432/16=128）之间的任何值。当RMT_MEM_SIZE_CH3>1时，此字段可以设置为（0~128）RMT_MEM-SIZE_CH3中的任何值。
 */
#define RMT_TX_LIM_CH0    0x000001FFU
#define RMT_TX_LIM_CH0_M  (RMT_TX_LIM_CH0_V << RMT_TX_LIM_CH0_S)
#define RMT_TX_LIM_CH0_V  0x000001FFU
#define RMT_TX_LIM_CH0_S  0
/** RMT_TX_LOOP_NUM_CH0:R/W；比特位置：[18:9]；默认值：0；此字段用于配置启用连续传输模式时的最大循环时间。
 */
#define RMT_TX_LOOP_NUM_CH0    0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_M  (RMT_TX_LOOP_NUM_CH0_V << RMT_TX_LOOP_NUM_CH0_S)
#define RMT_TX_LOOP_NUM_CH0_V  0x000003FFU
#define RMT_TX_LOOP_NUM_CH0_S  9
/** RMT_TX_LOOP_CNT_EN_CH0:R/W；位位置：[19]；默认值：0；此位用于启用循环计数。
 */
#define RMT_TX_LOOP_CNT_EN_CH0    (BIT(19))
#define RMT_TX_LOOP_CNT_EN_CH0_M  (RMT_TX_LOOP_CNT_EN_CH0_V << RMT_TX_LOOP_CNT_EN_CH0_S)
#define RMT_TX_LOOP_CNT_EN_CH0_V  0x00000001U
#define RMT_TX_LOOP_CNT_EN_CH0_S  19
/** RMT_LOOP_COUNT_RESET_CH0:WO；位位置：[20]；默认值：0；当连续传输模式有效时，该位用于重置循环计数。
 */
#define RMT_LOOP_COUNT_RESET_CH0    (BIT(20))
#define RMT_LOOP_COUNT_RESET_CH0_M  (RMT_LOOP_COUNT_RESET_CH0_V << RMT_LOOP_COUNT_RESET_CH0_S)
#define RMT_LOOP_COUNT_RESET_CH0_V  0x00000001U
#define RMT_LOOP_COUNT_RESET_CH0_S  20

/** RMT_APB_CONF_REG寄存器RMT APB配置寄存器
 */
#define RMT_APB_CONF_REG (DR_REG_RMT_BASE + 0x80)
/** RMT_APB_FIFO掩码：R/W；位位置：[0]；默认值：0；1’1：直接访问内存。1’0：通过APB FIFO访问内存。
 */
#define RMT_APB_FIFO_MASK    (BIT(0))
#define RMT_APB_FIFO_MASK_M  (RMT_APB_FIFO_MASK_V << RMT_APB_FIFO_MASK_S)
#define RMT_APB_FIFO_MASK_V  0x00000001U
#define RMT_APB_FIFO_MASK_S  0
/** RMT_MEM_TX_WRAP_EN:R/W；位位置：[1]；默认值：0；设置此位以启用换行模式。
 */
#define RMT_MEM_TX_WRAP_EN    (BIT(1))
#define RMT_MEM_TX_WRAP_EN_M  (RMT_MEM_TX_WRAP_EN_V << RMT_MEM_TX_WRAP_EN_S)
#define RMT_MEM_TX_WRAP_EN_V  0x00000001U
#define RMT_MEM_TX_WRAP_EN_S  1
/** RMT_MEM_CLK_FORCE_ON:R/W；位位置：[2]；默认值：1；设置此位以在RMT模块开始工作时启用RAM时钟，在RMT停止工作时禁用此时钟，以实现低功耗方案。
 */
#define RMT_MEM_CLK_FORCE_ON    (BIT(2))
#define RMT_MEM_CLK_FORCE_ON_M  (RMT_MEM_CLK_FORCE_ON_V << RMT_MEM_CLK_FORCE_ON_S)
#define RMT_MEM_CLK_FORCE_ON_V  0x00000001U
#define RMT_MEM_CLK_FORCE_ON_S  2
/** RMT_MEM_FORCE_PD:R/W；位位置：[3]；默认值：0；设置此位以关闭RMT内存。
 */
#define RMT_MEM_FORCE_PD    (BIT(3))
#define RMT_MEM_FORCE_PD_M  (RMT_MEM_FORCE_PD_V << RMT_MEM_FORCE_PD_S)
#define RMT_MEM_FORCE_PD_V  0x00000001U
#define RMT_MEM_FORCE_PD_S  3
/** RMT_MEM_FORCE_PU:R/W；位位置：[4]；默认值：0；1： 禁用RAM的轻睡眠断电功能。0：当RMT处于轻睡眠模式时，关闭RMT RAM。
 */
#define RMT_MEM_FORCE_PU    (BIT(4))
#define RMT_MEM_FORCE_PU_M  (RMT_MEM_FORCE_PU_V << RMT_MEM_FORCE_PU_S)
#define RMT_MEM_FORCE_PU_V  0x00000001U
#define RMT_MEM_FORCE_PU_S  4
/** RMT_CLK_EN:R/W；位位置：[31]；默认值：0；RMT寄存器的时钟门控启用位，以实现低功耗方案。1： 为RMT寄存器通电驱动时钟。0：关闭RMT寄存器的驱动器时钟。
 */
#define RMT_CLK_EN    (BIT(31))
#define RMT_CLK_EN_M  (RMT_CLK_EN_V << RMT_CLK_EN_S)
#define RMT_CLK_EN_V  0x00000001U
#define RMT_CLK_EN_S  31

/** RMT_TX_SIM_REG寄存器启用RMT同时传输
 */
#define RMT_TX_SIM_REG (DR_REG_RMT_BASE + 0x84)
/** RMT_TX_SIM_CH0:R/W；位位置：[0]；默认值：0；设置此位以启用通道0，以便与其他启用的通道同时开始发送数据。
 */
#define RMT_TX_SIM_CH0    (BIT(0))
#define RMT_TX_SIM_CH0_M  (RMT_TX_SIM_CH0_V << RMT_TX_SIM_CH0_S)
#define RMT_TX_SIM_CH0_V  0x00000001U
#define RMT_TX_SIM_CH0_S  0
/** RMT_TX_SIM_CH1:R/W；位位置：[1]；默认值：0；设置此位以使信道1能够与其他启用的信道同时开始发送数据。
 */
#define RMT_TX_SIM_CH1    (BIT(1))
#define RMT_TX_SIM_CH1_M  (RMT_TX_SIM_CH1_V << RMT_TX_SIM_CH1_S)
#define RMT_TX_SIM_CH1_V  0x00000001U
#define RMT_TX_SIM_CH1_S  1
/** RMT_TX_SIM_CH2:R/W；位位置：[2]；默认值：0；设置此位以使信道2能够与其他启用的信道同时开始发送数据。
 */
#define RMT_TX_SIM_CH2    (BIT(2))
#define RMT_TX_SIM_CH2_M  (RMT_TX_SIM_CH2_V << RMT_TX_SIM_CH2_S)
#define RMT_TX_SIM_CH2_V  0x00000001U
#define RMT_TX_SIM_CH2_S  2
/** RMT_TX_SIM_CH3:R/W；位位置：[3]；默认值：0；设置此位以启用通道3，使其能够与其他启用的通道同时开始发送数据。
 */
#define RMT_TX_SIM_CH3    (BIT(3))
#define RMT_TX_SIM_CH3_M  (RMT_TX_SIM_CH3_V << RMT_TX_SIM_CH3_S)
#define RMT_TX_SIM_CH3_V  0x00000001U
#define RMT_TX_SIM_CH3_S  3
/** RMT_TX_SIM_EN:R/W；位位置：[4]；默认值：0；该位用于使多个信道同时开始发送数据。
 */
#define RMT_TX_SIM_EN    (BIT(4))
#define RMT_TX_SIM_EN_M  (RMT_TX_SIM_EN_V << RMT_TX_SIM_EN_S)
#define RMT_TX_SIM_EN_V  0x00000001U
#define RMT_TX_SIM_EN_S  4

/** RMT_REF_CNT_RST_REG寄存器RMT时钟分频器复位寄存器
 */
#define RMT_REF_CNT_RST_REG (DR_REG_RMT_BASE + 0x88)
/** RMT_REF_CNT_RST_CH0:R/W；位位置：[0]；默认值：0；该位用于重置信道0的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH0    (BIT(0))
#define RMT_REF_CNT_RST_CH0_M  (RMT_REF_CNT_RST_CH0_V << RMT_REF_CNT_RST_CH0_S)
#define RMT_REF_CNT_RST_CH0_V  0x00000001U
#define RMT_REF_CNT_RST_CH0_S  0
/** RMT_REF_CNT_RST_CH1:R/W；位位置：[1]；默认值：0；该位用于重置信道1的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH1    (BIT(1))
#define RMT_REF_CNT_RST_CH1_M  (RMT_REF_CNT_RST_CH1_V << RMT_REF_CNT_RST_CH1_S)
#define RMT_REF_CNT_RST_CH1_V  0x00000001U
#define RMT_REF_CNT_RST_CH1_S  1
/** RMT_REF_CNT_RST_CH2:R/W；位位置：[2]；默认值：0；该位用于重置信道2的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH2    (BIT(2))
#define RMT_REF_CNT_RST_CH2_M  (RMT_REF_CNT_RST_CH2_V << RMT_REF_CNT_RST_CH2_S)
#define RMT_REF_CNT_RST_CH2_V  0x00000001U
#define RMT_REF_CNT_RST_CH2_S  2
/** RMT_REF_CNT_RST_CH3:R/W；位位置：[3]；默认值：0；该位用于重置信道3的时钟分频器。
 */
#define RMT_REF_CNT_RST_CH3    (BIT(3))
#define RMT_REF_CNT_RST_CH3_M  (RMT_REF_CNT_RST_CH3_V << RMT_REF_CNT_RST_CH3_S)
#define RMT_REF_CNT_RST_CH3_V  0x00000001U
#define RMT_REF_CNT_RST_CH3_S  3

/** RMT_CH0_RX_CARRIR_RM_REG寄存器通道0载波移除寄存器
 */
#define RMT_CH0_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x8c)
/** RMT_CARRIER_LOW_threshold_CH0:R/W；比特位置：[15:0]；默认值：0；载波调制模式中的低电平周期是信道0的（RMT_CARRIR_low_THRES_CH0+1）时钟周期。
 */
#define RMT_CARRIER_LOW_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_M  (RMT_CARRIER_LOW_THRES_CH0_V << RMT_CARRIER_LOW_THRES_CH0_S)
#define RMT_CARRIER_LOW_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_S  0
/** RMT_CARRIER_HIGH_threshold_CH0:R/W；比特位置：[31:16]；默认值：0；载波调制模式中的高电平周期是信道0的（RMT_CARRIR_high_THRES_CH0+1）时钟周期。
 */
#define RMT_CARRIER_HIGH_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_M  (RMT_CARRIER_HIGH_THRES_CH0_V << RMT_CARRIER_HIGH_THRES_CH0_S)
#define RMT_CARRIER_HIGH_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_S  16

/** RMT_CH1_RX_CARRIR_RM_REG寄存器通道1载波移除寄存器
 */
#define RMT_CH1_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x90)
/** RMT_CARRIER_LOW_threshold_CH0:R/W；比特位置：[15:0]；默认值：0；载波调制模式中的低电平周期是信道1的（RMT_CARRIR_low_THRES_CH1+1）时钟周期。
 */
#define RMT_CARRIER_LOW_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_M  (RMT_CARRIER_LOW_THRES_CH0_V << RMT_CARRIER_LOW_THRES_CH0_S)
#define RMT_CARRIER_LOW_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_S  0
/** RMT_CARRIER_HIGH_threshold_CH0:R/W；比特位置：[31:16]；默认值：0；载波调制模式中的高电平周期是信道1的（RMT_CARRIR_high_THRES_CH1+1）时钟周期。
 */
#define RMT_CARRIER_HIGH_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_M  (RMT_CARRIER_HIGH_THRES_CH0_V << RMT_CARRIER_HIGH_THRES_CH0_S)
#define RMT_CARRIER_HIGH_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_S  16

/** RMT_CH2_RX_CARRIR_RM_REG寄存器通道2载波移除寄存器
 */
#define RMT_CH2_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x94)
/** RMT_CARRIER_LOW_threshold_CH0:R/W；比特位置：[15:0]；默认值：0；载波调制模式中的低电平周期是信道2的（RMT_CARRIR_low_THRES_CH2+1）时钟周期。
 */
#define RMT_CARRIER_LOW_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_M  (RMT_CARRIER_LOW_THRES_CH0_V << RMT_CARRIER_LOW_THRES_CH0_S)
#define RMT_CARRIER_LOW_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_S  0
/** RMT_CARRIER_HIGH_threshold_CH0:R/W；比特位置：[31:16]；默认值：0；载波调制模式中的高电平周期是信道2的（RMT_CARRIR_high_THRES_CH2+1）时钟周期。
 */
#define RMT_CARRIER_HIGH_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_M  (RMT_CARRIER_HIGH_THRES_CH0_V << RMT_CARRIER_HIGH_THRES_CH0_S)
#define RMT_CARRIER_HIGH_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_S  16

/** RMT_CH3_RX_CARRIR_RM_REG寄存器通道3载波移除寄存器
 */
#define RMT_CH3_RX_CARRIER_RM_REG (DR_REG_RMT_BASE + 0x98)
/** RMT_CARRIER_LOW_threshold_CH0:R/W；比特位置：[15:0]；默认值：0；载波调制模式中的低电平周期是信道3的（RMT_CARRIR_low_THRES_CH3+1）时钟周期。
 */
#define RMT_CARRIER_LOW_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_M  (RMT_CARRIER_LOW_THRES_CH0_V << RMT_CARRIER_LOW_THRES_CH0_S)
#define RMT_CARRIER_LOW_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_LOW_THRES_CH0_S  0
/** RMT_CARRIER_HIGH_threshold_CH0:R/W；比特位置：[31:16]；默认值：0；载波调制模式中的高电平周期是信道3的（RMT_CARRIR_high_THRES_CH3+1）时钟周期。
 */
#define RMT_CARRIER_HIGH_THRES_CH0    0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_M  (RMT_CARRIER_HIGH_THRES_CH0_V << RMT_CARRIER_HIGH_THRES_CH0_S)
#define RMT_CARRIER_HIGH_THRES_CH0_V  0x0000FFFFU
#define RMT_CARRIER_HIGH_THRES_CH0_S  16

/** RMT_DATE_REG寄存器版本控制寄存器
 */
#define RMT_DATE_REG (DR_REG_RMT_BASE + 0xfc)
/** RMT_DATE:R/W；位位置：[31:0]；默认值：41989881；版本控制寄存器
 */
#define RMT_DATE    0xFFFFFFFFU
#define RMT_DATE_M  (RMT_DATE_V << RMT_DATE_S)
#define RMT_DATE_V  0xFFFFFFFFU
#define RMT_DATE_S  0

#ifdef __cplusplus
}
#endif

