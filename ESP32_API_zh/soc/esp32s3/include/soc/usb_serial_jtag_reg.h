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
#ifndef _SOC_USB_DEVICE_REG_H_
#define _SOC_USB_DEVICE_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"

#define USB_SERIAL_JTAG_EP1_REG          (DR_REG_USB_DEVICE_BASE + 0x0)
/* USB_SERIAL_JTAG_RDWR_BYTE:R/W；位位置：[7:0]；默认值：8'0；*/
/*description:通过此字段向UART Tx/Rx FIFO写入和读取字节数据。当设置了USB_DEVICE_SERIAL_IN_EMPTY_INT时，用户可以将数据（最多64字节）写入UART Tx FIFO。当设置了USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时，用户可以检查USB_DEVICE_OUT_EP1_WR_ADDR USB_SERIAL-JTAG_OUT_EP0_RD_ADDR以了解接收到多少数据，然后从UART Rx FIFO读取数据。。*/
#define USB_SERIAL_JTAG_RDWR_BYTE    0x000000FF
#define USB_SERIAL_JTAG_RDWR_BYTE_M  ((USB_DEVICE_RDWR_BYTE_V)<<(USB_DEVICE_RDWR_BYTE_S))
#define USB_SERIAL_JTAG_RDWR_BYTE_V  0xFF
#define USB_SERIAL_JTAG_RDWR_BYTE_S  0

#define USB_SERIAL_JTAG_EP1_CONF_REG          (DR_REG_USB_DEVICE_BASE + 0x4)
/* USB_SERIAL_JTAG_SERIAL_OUT_EP_DATA_AVAIL:RO；位位置：[2]；默认值：1’b0；*/
/*description:1’b1：表示UART Rx FIFO中有数据。。*/
#define USB_SERIAL_JTAG_SERIAL_OUT_EP_DATA_AVAIL    (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_EP_DATA_AVAIL_M  (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_EP_DATA_AVAIL_V  0x1
#define USB_SERIAL_JTAG_SERIAL_OUT_EP_DATA_AVAIL_S  2
/* USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE：RO；位位置：[1]；默认值：1’b1；*/
/*description:1’b1：表示UART Tx FIFO未满，可以将数据写入。写入USB_SERIAL_JTAG_WR_DONE后，该位将为0，直到USB主机读取UART Tx FIFO中的数据。。*/
#define USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE    (BIT(1))
#define USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE_M  (BIT(1))
#define USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE_V  0x1
#define USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE_S  1
/* USB_SERIAL_JTAG_WR_DONE:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以指示已完成向UART Tx FIFO写入字节数据。。*/
#define USB_SERIAL_JTAG_WR_DONE    (BIT(0))
#define USB_SERIAL_JTAG_WR_DONE_M  (BIT(0))
#define USB_SERIAL_JTAG_WR_DONE_V  0x1
#define USB_SERIAL_JTAG_WR_DONE_S  0

#define USB_SERIAL_JTAG_INT_RAW_REG          (DR_REG_USB_DEVICE_BASE + 0x8)
/* USB_SERIAL_JTAG_OUT_EP2_ZERO_paiload_INT_RAW:R/WTC/SS；位位置：[11]；默认值：1’b0；*/
/*描述：当OUT端点2接收到具有零播放负载的数据包时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_RAW    (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_RAW_M  (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_RAW_S  11
/* USB_SERIAL_JTAG_OUT_EP1_ZERO_paiload_INT_RAW:R/WTC/SS；位位置：[10]；默认值：1’b0；*/
/*描述：当OUT端点1接收到具有零播放负载的数据包时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_RAW    (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_RAW_M  (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_RAW_S  10
/* USB_SERIAL_JTAG_USB_BUS_RESET_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当检测到usb总线重置时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_RAW    (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_RAW_M  (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_RAW_S  9
/* USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当接收到IN端点1的IN令牌时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_RAW    (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_RAW_M  (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_RAW_S  8
/* USB_SERIAL_JTAG_STUFF_ERR_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当检测到填充错误时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_STUFF_ERR_INT_RAW    (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_RAW_M  (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_STUFF_ERR_INT_RAW_S  7
/* USB_SERIAL_JTAG_CRC16_ERR_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当检测到CRC16错误时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_CRC16_ERR_INT_RAW    (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_RAW_M  (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_CRC16_ERR_INT_RAW_S  6
/* USB_SERIAL_JTAG_CRC5_ERR_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当检测到CRC5错误时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_CRC5_ERR_INT_RAW    (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_RAW_M  (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_CRC5_ERR_INT_RAW_S  5
/* USB_SERIAL_JTAG_PID_ERR_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当检测到pid错误时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_PID_ERR_INT_RAW    (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_RAW_M  (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_PID_ERR_INT_RAW_S  4
/* USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b1；*/
/*description:当串行端口IN终结点为空时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_RAW    (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_RAW_M  (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_RAW_S  3
/* USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当串行端口OUT端点接收到一个数据包时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_RAW    (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_RAW_M  (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_RAW_S  2
/* USB_SERIAL_JTAG_SOF_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*description:收到SOF帧时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_SOF_INT_RAW    (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_RAW_M  (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_SOF_INT_RAW_S  1
/* USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到JTAG的IN端点2的flush cmd时，原始中断位变为高电平。。*/
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_RAW    (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_RAW_M  (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_RAW_V  0x1
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_RAW_S  0

#define USB_SERIAL_JTAG_INT_ST_REG          (DR_REG_USB_DEVICE_BASE + 0xC)
/* USB_SERIAL_JTAG_OUT_EP2_ZERO_paiload_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ST    (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ST_M  (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ST_V  0x1
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ST_S  11
/* USB_SERIAL_JTAG_OUT_EP1_ZERO_paiload_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ST    (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ST_M  (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ST_V  0x1
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ST_S  10
/* USB_SERIAL_JTAG_USB_BUS_RESET_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_USB_BUS_RESET_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ST    (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ST_M  (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ST_V  0x1
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ST_S  9
/* USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ST    (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ST_M  (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ST_V  0x1
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ST_S  8
/* USB_SERIAL_JTAG_STUFF_ERR_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_STUFF_ERR_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ST    (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ST_M  (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ST_V  0x1
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ST_S  7
/* USB_SERIAL_JTAG_CRC16_ERR_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_CRC16_ERR_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ST    (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ST_M  (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ST_V  0x1
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ST_S  6
/* USB_SERIAL_JTAG_CRC5_ERR_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_CRC5_ERR_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ST    (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ST_M  (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ST_V  0x1
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ST_S  5
/* USB_SERIAL_JTAG_PID_ERR_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_PID_ERR_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_PID_ERR_INT_ST    (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_ST_M  (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_ST_V  0x1
#define USB_SERIAL_JTAG_PID_ERR_INT_ST_S  4
/* USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ST    (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ST_M  (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ST_V  0x1
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ST_S  3
/* USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ST    (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ST_M  (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ST_V  0x1
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ST_S  2
/* USB_SERIAL_JTAG_SOF_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_SOF_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_SOF_INT_ST    (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_ST_M  (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_ST_V  0x1
#define USB_SERIAL_JTAG_SOF_INT_ST_S  1
/* USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT中断的原始中断状态位。。*/
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ST    (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ST_M  (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ST_V  0x1
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ST_S  0

#define USB_SERIAL_JTAG_INT_ENA_REG          (DR_REG_USB_DEVICE_BASE + 0x10)
/* USB_SERIAL_JTAG_OUT_EP2_ZERO_paiload_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ENA    (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ENA_M  (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ENA_S  11
/* USB_SERIAL_JTAG_OUT_EP1_ZERO_paiload_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ENA    (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ENA_M  (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ENA_S  10
/* USB_SERIAL_JTAG_USB_BUS_RESET_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_USB_BUS_RESET_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ENA    (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ENA_M  (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_ENA_S  9
/* USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ENA    (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ENA_M  (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ENA_S  8
/* USB_SERIAL_JTAG_STUFF_ERR_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_STUFF_ERR_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ENA    (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ENA_M  (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_STUFF_ERR_INT_ENA_S  7
/* USB_SERIAL_JTAG_CRC16_ERR_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_CRC16_ERR_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ENA    (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ENA_M  (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_CRC16_ERR_INT_ENA_S  6
/* USB_SERIAL_JTAG_CRC5_ERR_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_CRC5_ERR_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ENA    (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ENA_M  (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_CRC5_ERR_INT_ENA_S  5
/* USB_SERIAL_JTAG_PID_ERR_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_PID_ERR_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_PID_ERR_INT_ENA    (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_ENA_M  (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_PID_ERR_INT_ENA_S  4
/* USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ENA    (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ENA_M  (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ENA_S  3
/* USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ENA    (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ENA_M  (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ENA_S  2
/* USB_SERIAL_JTAG_SOF_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_SOF_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_SOF_INT_ENA    (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_ENA_M  (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_SOF_INT_ENA_S  1
/* USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT中断的中断启用位。。*/
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ENA    (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ENA_M  (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ENA_V  0x1
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ENA_S  0

#define USB_SERIAL_JTAG_INT_CLR_REG          (DR_REG_USB_DEVICE_BASE + 0x14)
/* USB_SERIAL_JTAG_OUT_EP2_ZERO_paiload_INT_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT中断。。*/
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_CLR    (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_CLR_M  (BIT(11))
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_CLR_S  11
/* USB_SERIAL_JTAG_OUT_EP1_ZERO_paiload_INT_CLR:WT；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT中断。。*/
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_CLR    (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_CLR_M  (BIT(10))
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_CLR_S  10
/* USB_SERIAL_JTAG_USB_BUS_RESET_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_USB_BUS_RESET_INT中断。。*/
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_CLR    (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_CLR_M  (BIT(9))
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_USB_BUS_RESET_INT_CLR_S  9
/* USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_IN_TOKEN_IN_EP1_INT中断。。*/
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_CLR    (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_CLR_M  (BIT(8))
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_CLR_S  8
/* USB_SERIAL_JTAG_STUFF_ERR_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_STUFF_ERR_INT中断。。*/
#define USB_SERIAL_JTAG_STUFF_ERR_INT_CLR    (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_CLR_M  (BIT(7))
#define USB_SERIAL_JTAG_STUFF_ERR_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_STUFF_ERR_INT_CLR_S  7
/* USB_SERIAL_JTAG_CRC16_ERR_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_CRC16_ERR_INT中断。。*/
#define USB_SERIAL_JTAG_CRC16_ERR_INT_CLR    (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_CLR_M  (BIT(6))
#define USB_SERIAL_JTAG_CRC16_ERR_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_CRC16_ERR_INT_CLR_S  6
/* USB_SERIAL_JTAG_CRC5_ERR_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_CRC5_ERR_INT中断。。*/
#define USB_SERIAL_JTAG_CRC5_ERR_INT_CLR    (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_CLR_M  (BIT(5))
#define USB_SERIAL_JTAG_CRC5_ERR_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_CRC5_ERR_INT_CLR_S  5
/* USB_SERIAL_JTAG_PID_ERR_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_PID_ERR_INT中断。。*/
#define USB_SERIAL_JTAG_PID_ERR_INT_CLR    (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_CLR_M  (BIT(4))
#define USB_SERIAL_JTAG_PID_ERR_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_PID_ERR_INT_CLR_S  4
/* USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT中断。。*/
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_CLR    (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_CLR_M  (BIT(3))
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_CLR_S  3
/* USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT中断。。*/
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_CLR    (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_CLR_M  (BIT(2))
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_CLR_S  2
/* USB_SERIAL_JTAG_SOF_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_JTAG_SOF_INT中断。。*/
#define USB_SERIAL_JTAG_SOF_INT_CLR    (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_CLR_M  (BIT(1))
#define USB_SERIAL_JTAG_SOF_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_SOF_INT_CLR_S  1
/* USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT中断。。*/
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_CLR    (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_CLR_M  (BIT(0))
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_CLR_V  0x1
#define USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_CLR_S  0

#define USB_SERIAL_JTAG_CONF0_REG          (DR_REG_USB_DEVICE_BASE + 0x18)
/* USB_SERIAL_JTAG_USB_JTAG_BRIDGE_EN:R/W；位位置：[16]；默认值：1’b0；*/
/*description:设置此位usb_jtag，usb_jtag与内部jtag之间的连接断开，MTMS、MTDI、MTCK通过GPIO Matrix输出，MTDO通过GPIO矩阵输入。。*/
#define USB_SERIAL_JTAG_USB_JTAG_BRIDGE_EN    (BIT(16))
#define USB_SERIAL_JTAG_USB_JTAG_BRIDGE_EN_M  (BIT(16))
#define USB_SERIAL_JTAG_USB_JTAG_BRIDGE_EN_V  0x1
#define USB_SERIAL_JTAG_USB_JTAG_BRIDGE_EN_S  16
/* USB_SERIAL_JTAG_PHY_TX_EDGE_SEL:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：0：时钟负边缘的TX输出。1： 时钟边缘的Tx输出。。*/
#define USB_SERIAL_JTAG_PHY_TX_EDGE_SEL    (BIT(15))
#define USB_SERIAL_JTAG_PHY_TX_EDGE_SEL_M  (BIT(15))
#define USB_SERIAL_JTAG_PHY_TX_EDGE_SEL_V  0x1
#define USB_SERIAL_JTAG_PHY_TX_EDGE_SEL_S  15
/* USB_SERIAL_JTAG_USB_PAD_ENABLE:R/W；位位置：[14]；默认值：1’b1；*/
/*description:启用USB pad功能。。*/
#define USB_SERIAL_JTAG_USB_PAD_ENABLE    (BIT(14))
#define USB_SERIAL_JTAG_USB_PAD_ENABLE_M  (BIT(14))
#define USB_SERIAL_JTAG_USB_PAD_ENABLE_V  0x1
#define USB_SERIAL_JTAG_USB_PAD_ENABLE_S  14
/* USB_SERIAL_JTAG_PULLUP_VALUE:R/W；位位置：[13]；默认值：1’b0；*/
/*description:控制上拉值。。*/
#define USB_SERIAL_JTAG_PULLUP_VALUE    (BIT(13))
#define USB_SERIAL_JTAG_PULLUP_VALUE_M  (BIT(13))
#define USB_SERIAL_JTAG_PULLUP_VALUE_V  0x1
#define USB_SERIAL_JTAG_PULLUP_VALUE_S  13
/* USB_SERIAL_JTAG_DM_下拉：R/W；位位置：[12]；默认值：1’b0；*/
/*description:控制USB D-下拉。。*/
#define USB_SERIAL_JTAG_DM_PULLDOWN    (BIT(12))
#define USB_SERIAL_JTAG_DM_PULLDOWN_M  (BIT(12))
#define USB_SERIAL_JTAG_DM_PULLDOWN_V  0x1
#define USB_SERIAL_JTAG_DM_PULLDOWN_S  12
/* USB_SERIAL_JTAG_DM_PULLUP:R/W；位位置：[11]；默认值：1’b0；*/
/*description:控制USB D-上拉。。*/
#define USB_SERIAL_JTAG_DM_PULLUP    (BIT(11))
#define USB_SERIAL_JTAG_DM_PULLUP_M  (BIT(11))
#define USB_SERIAL_JTAG_DM_PULLUP_V  0x1
#define USB_SERIAL_JTAG_DM_PULLUP_S  11
/* USB_SERIAL_JTAG_DP_pull:R/W；位位置：[10]；默认值：1’b0；*/
/*description:控制USB D+下拉。。*/
#define USB_SERIAL_JTAG_DP_PULLDOWN    (BIT(10))
#define USB_SERIAL_JTAG_DP_PULLDOWN_M  (BIT(10))
#define USB_SERIAL_JTAG_DP_PULLDOWN_V  0x1
#define USB_SERIAL_JTAG_DP_PULLDOWN_S  10
/* USB_SERIAL_JTAG_DP_PULLUP:R/W；位位置：[9]；默认值：1’b1；*/
/*description:控制USB D+上拉。。*/
#define USB_SERIAL_JTAG_DP_PULLUP    (BIT(9))
#define USB_SERIAL_JTAG_DP_PULLUP_M  (BIT(9))
#define USB_SERIAL_JTAG_DP_PULLUP_V  0x1
#define USB_SERIAL_JTAG_DP_PULLUP_S  9
/* USB_SERIAL_JTAG_PAD_PULL_OVERRIDE:R/W；位位置：[8]；默认值：1’b0；*/
/*description:启用软件控制USB D+D-下拉。*/
#define USB_SERIAL_JTAG_PAD_PULL_OVERRIDE    (BIT(8))
#define USB_SERIAL_JTAG_PAD_PULL_OVERRIDE_M  (BIT(8))
#define USB_SERIAL_JTAG_PAD_PULL_OVERRIDE_V  0x1
#define USB_SERIAL_JTAG_PAD_PULL_OVERRIDE_S  8
/* USB_SERIAL_JTAG_VREF_OVERRIDE:R/W；位位置：[7]；默认值：1’b0；*/
/*description:启用软件控制输入阈值。*/
#define USB_SERIAL_JTAG_VREF_OVERRIDE    (BIT(7))
#define USB_SERIAL_JTAG_VREF_OVERRIDE_M  (BIT(7))
#define USB_SERIAL_JTAG_VREF_OVERRIDE_V  0x1
#define USB_SERIAL_JTAG_VREF_OVERRIDE_S  7
/* USB_SERIAL_JTAG_VREFL:R/W；比特位置：[6:5]；默认值：2’b0；*/
/*描述：控制单端输入低阈值，0.8V至1.04V，步进80mV。*/
#define USB_SERIAL_JTAG_VREFL    0x00000003
#define USB_SERIAL_JTAG_VREFL_M  ((USB_DEVICE_VREFL_V)<<(USB_DEVICE_VREFL_S))
#define USB_SERIAL_JTAG_VREFL_V  0x3
#define USB_SERIAL_JTAG_VREFL_S  5
/* USB_SERIAL_JTAG_VREFH:R/W；位位置：[4:3]；默认值：2’b0；*/
/*描述：控制单端输入高阈值，1.76V至2V，步进80mV。*/
#define USB_SERIAL_JTAG_VREFH    0x00000003
#define USB_SERIAL_JTAG_VREFH_M  ((USB_DEVICE_VREFH_V)<<(USB_DEVICE_VREFH_S))
#define USB_SERIAL_JTAG_VREFH_V  0x3
#define USB_SERIAL_JTAG_VREFH_S  3
/* USB_SERIAL_JTAG_EXCHG_PINS：R/W；位位置：[2]；默认值：1’b0；*/
/*描述：USB D+D-交换。*/
#define USB_SERIAL_JTAG_EXCHG_PINS    (BIT(2))
#define USB_SERIAL_JTAG_EXCHG_PINS_M  (BIT(2))
#define USB_SERIAL_JTAG_EXCHG_PINS_V  0x1
#define USB_SERIAL_JTAG_EXCHG_PINS_S  2
/* USB_SERIAL_JTAG_EXCHG_PINS_OVERRIDE:R/W；位位置：[1]；默认值：1’b0；*/
/*description:启用软件控制USB D+D-交换。*/
#define USB_SERIAL_JTAG_EXCHG_PINS_OVERRIDE    (BIT(1))
#define USB_SERIAL_JTAG_EXCHG_PINS_OVERRIDE_M  (BIT(1))
#define USB_SERIAL_JTAG_EXCHG_PINS_OVERRIDE_V  0x1
#define USB_SERIAL_JTAG_EXCHG_PINS_OVERRIDE_S  1
/* USB_SERIAL_JTAG_PHY_SEL:R/W；位位置：[0]；默认值：1’b0；*/
/*description:选择内部/外部PHY。*/
#define USB_SERIAL_JTAG_PHY_SEL    (BIT(0))
#define USB_SERIAL_JTAG_PHY_SEL_M  (BIT(0))
#define USB_SERIAL_JTAG_PHY_SEL_V  0x1
#define USB_SERIAL_JTAG_PHY_SEL_S  0

#define USB_SERIAL_JTAG_TEST_REG          (DR_REG_USB_DEVICE_BASE + 0x1C)
/* USB_SERIAL_JTAG_TEST_RX_DM:RO；位位置：[6]；默认值：1’b0；*/
/*description:USB D-测试中的rx值。*/
#define USB_SERIAL_JTAG_TEST_RX_DM    (BIT(6))
#define USB_SERIAL_JTAG_TEST_RX_DM_M  (BIT(6))
#define USB_SERIAL_JTAG_TEST_RX_DM_V  0x1
#define USB_SERIAL_JTAG_TEST_RX_DM_S  6
/* USB_SERIAL_JTAG_TEST_RX_DP:RO；位位置：[5]；默认值：1’b0；*/
/*描述：测试中的USB D+rx值。*/
#define USB_SERIAL_JTAG_TEST_RX_DP    (BIT(5))
#define USB_SERIAL_JTAG_TEST_RX_DP_M  (BIT(5))
#define USB_SERIAL_JTAG_TEST_RX_DP_V  0x1
#define USB_SERIAL_JTAG_TEST_RX_DP_S  5
/* USB_SERIAL_JTAG_TEST_RX_RCV:RO；位位置：[4]；默认值：1’b0；*/
/*描述：测试中的USB差分rx值。*/
#define USB_SERIAL_JTAG_TEST_RX_RCV    (BIT(4))
#define USB_SERIAL_JTAG_TEST_RX_RCV_M  (BIT(4))
#define USB_SERIAL_JTAG_TEST_RX_RCV_V  0x1
#define USB_SERIAL_JTAG_TEST_RX_RCV_S  4
/* USB_SERIAL_JTAG_TEST_TX_DM:R/W；位位置：[3]；默认值：1’b0；*/
/*description:测试中的USB D-tx值。*/
#define USB_SERIAL_JTAG_TEST_TX_DM    (BIT(3))
#define USB_SERIAL_JTAG_TEST_TX_DM_M  (BIT(3))
#define USB_SERIAL_JTAG_TEST_TX_DM_V  0x1
#define USB_SERIAL_JTAG_TEST_TX_DM_S  3
/* USB_SERIAL_JTAG_TEST_TX_DP:R/W；位位置：[2]；默认值：1’b0；*/
/*description:测试中的USB D+tx值。*/
#define USB_SERIAL_JTAG_TEST_TX_DP    (BIT(2))
#define USB_SERIAL_JTAG_TEST_TX_DP_M  (BIT(2))
#define USB_SERIAL_JTAG_TEST_TX_DP_V  0x1
#define USB_SERIAL_JTAG_TEST_TX_DP_S  2
/* USB_SERIAL_JTAG_TEST_USB_OE:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：USB pad正在测试中。*/
#define USB_SERIAL_JTAG_TEST_USB_OE    (BIT(1))
#define USB_SERIAL_JTAG_TEST_USB_OE_M  (BIT(1))
#define USB_SERIAL_JTAG_TEST_USB_OE_V  0x1
#define USB_SERIAL_JTAG_TEST_USB_OE_S  1
/* USB_SERIAL_JTAG_TEST_ENABLE:R/W；位位置：[0]；默认值：1’b0；*/
/*description:启用USB焊盘测试。*/
#define USB_SERIAL_JTAG_TEST_ENABLE    (BIT(0))
#define USB_SERIAL_JTAG_TEST_ENABLE_M  (BIT(0))
#define USB_SERIAL_JTAG_TEST_ENABLE_V  0x1
#define USB_SERIAL_JTAG_TEST_ENABLE_S  0

#define USB_SERIAL_JTAG_JFIFO_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x20)
/* USB_SERIAL_JTAG_OUT_FIFO_RESET:R/W；位位置：[9]；默认值：1’b0；*/
/*description:写1重置JTAG输出fifo。。*/
#define USB_SERIAL_JTAG_OUT_FIFO_RESET    (BIT(9))
#define USB_SERIAL_JTAG_OUT_FIFO_RESET_M  (BIT(9))
#define USB_SERIAL_JTAG_OUT_FIFO_RESET_V  0x1
#define USB_SERIAL_JTAG_OUT_FIFO_RESET_S  9
/* USB_SERIAL_JTAG_IN_FIFO_RESET:R/W；位位置：[8]；默认值：1’b0；*/
/*description:写入1以重置fifo中的JTAG。。*/
#define USB_SERIAL_JTAG_IN_FIFO_RESET    (BIT(8))
#define USB_SERIAL_JTAG_IN_FIFO_RESET_M  (BIT(8))
#define USB_SERIAL_JTAG_IN_FIFO_RESET_V  0x1
#define USB_SERIAL_JTAG_IN_FIFO_RESET_S  8
/* USB_SERIAL_JTAG_OUT_FIFO_FULL:RO；位位置：[7]；默认值：1’b0；*/
/*描述：1:JTAG输出fifo已满。。*/
#define USB_SERIAL_JTAG_OUT_FIFO_FULL    (BIT(7))
#define USB_SERIAL_JTAG_OUT_FIFO_FULL_M  (BIT(7))
#define USB_SERIAL_JTAG_OUT_FIFO_FULL_V  0x1
#define USB_SERIAL_JTAG_OUT_FIFO_FULL_S  7
/* USB_SERIAL_JTAG_OUT_FIFO_EMPTY:RO；位位置：[6]；默认值：1’b1；*/
/*description:1:JTAG out fifo为空。。*/
#define USB_SERIAL_JTAG_OUT_FIFO_EMPTY    (BIT(6))
#define USB_SERIAL_JTAG_OUT_FIFO_EMPTY_M  (BIT(6))
#define USB_SERIAL_JTAG_OUT_FIFO_EMPTY_V  0x1
#define USB_SERIAL_JTAG_OUT_FIFO_EMPTY_S  6
/* USB_SERIAL_JTAG_OUT_FIFO_CNT:RO；比特位置：[5:4]；默认值：2'd0；*/
/*description:JTAT输出fifo计数器。。*/
#define USB_SERIAL_JTAG_OUT_FIFO_CNT    0x00000003
#define USB_SERIAL_JTAG_OUT_FIFO_CNT_M  ((USB_DEVICE_OUT_FIFO_CNT_V)<<(USB_DEVICE_OUT_FIFO_CNT_S))
#define USB_SERIAL_JTAG_OUT_FIFO_CNT_V  0x3
#define USB_SERIAL_JTAG_OUT_FIFO_CNT_S  4
/* USB_SERIAL_JTAG_IN_FIFO_FULL:RO；位位置：[3]；默认值：1’b0；*/
/*描述：1:fifo中的JTAG已满。。*/
#define USB_SERIAL_JTAG_IN_FIFO_FULL    (BIT(3))
#define USB_SERIAL_JTAG_IN_FIFO_FULL_M  (BIT(3))
#define USB_SERIAL_JTAG_IN_FIFO_FULL_V  0x1
#define USB_SERIAL_JTAG_IN_FIFO_FULL_S  3
/* USB_SERIAL_JTAG_IN_FIFO_EMPTY:RO；位位置：[2]；默认值：1’b1；*/
/*description:1:fifo中的JTAG为空。。*/
#define USB_SERIAL_JTAG_IN_FIFO_EMPTY    (BIT(2))
#define USB_SERIAL_JTAG_IN_FIFO_EMPTY_M  (BIT(2))
#define USB_SERIAL_JTAG_IN_FIFO_EMPTY_V  0x1
#define USB_SERIAL_JTAG_IN_FIFO_EMPTY_S  2
/* USB_SERIAL_JTAG_IN_FIFO_CNT:RO；位位置：[1:0]；默认值：2'd0；*/
/*description:fifo计数器中的JTAT。。*/
#define USB_SERIAL_JTAG_IN_FIFO_CNT    0x00000003
#define USB_SERIAL_JTAG_IN_FIFO_CNT_M  ((USB_DEVICE_IN_FIFO_CNT_V)<<(USB_DEVICE_IN_FIFO_CNT_S))
#define USB_SERIAL_JTAG_IN_FIFO_CNT_V  0x3
#define USB_SERIAL_JTAG_IN_FIFO_CNT_S  0

#define USB_SERIAL_JTAG_FRAM_NUM_REG          (DR_REG_USB_DEVICE_BASE + 0x24)
/* USB_SERIAL_JTAG_SOF_FRAME_INDEX:RO；位位置：[10:0]；默认值：11'd0；*/
/*description:接收到的SOF帧的帧索引。。*/
#define USB_SERIAL_JTAG_SOF_FRAME_INDEX    0x000007FF
#define USB_SERIAL_JTAG_SOF_FRAME_INDEX_M  ((USB_DEVICE_SOF_FRAME_INDEX_V)<<(USB_DEVICE_SOF_FRAME_INDEX_S))
#define USB_SERIAL_JTAG_SOF_FRAME_INDEX_V  0x7FF
#define USB_SERIAL_JTAG_SOF_FRAME_INDEX_S  0

#define USB_SERIAL_JTAG_IN_EP0_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x28)
/* USB_SERIAL_JTAG_IN_EP0_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取IN端点0的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP0_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP0_RD_ADDR_M  ((USB_DEVICE_IN_EP0_RD_ADDR_V)<<(USB_DEVICE_IN_EP0_RD_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP0_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP0_RD_ADDR_S  9
/* USB_SERIAL_JTAG_IN_EP0_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入IN端点0的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP0_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP0_WR_ADDR_M  ((USB_DEVICE_IN_EP0_WR_ADDR_V)<<(USB_DEVICE_IN_EP0_WR_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP0_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP0_WR_ADDR_S  2
/* USB_SERIAL_JTAG_IN_EP0_STATE:RO；位位置：[1:0]；默认值：2'b1；*/
/*description:IN终结点0的状态。。*/
#define USB_SERIAL_JTAG_IN_EP0_STATE    0x00000003
#define USB_SERIAL_JTAG_IN_EP0_STATE_M  ((USB_DEVICE_IN_EP0_STATE_V)<<(USB_DEVICE_IN_EP0_STATE_S))
#define USB_SERIAL_JTAG_IN_EP0_STATE_V  0x3
#define USB_SERIAL_JTAG_IN_EP0_STATE_S  0

#define USB_SERIAL_JTAG_IN_EP1_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x2C)
/* USB_SERIAL_JTAG_IN_EP1_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取IN端点1的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP1_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP1_RD_ADDR_M  ((USB_DEVICE_IN_EP1_RD_ADDR_V)<<(USB_DEVICE_IN_EP1_RD_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP1_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP1_RD_ADDR_S  9
/* USB_SERIAL_JTAG_IN_EP1_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入IN端点1的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP1_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP1_WR_ADDR_M  ((USB_DEVICE_IN_EP1_WR_ADDR_V)<<(USB_DEVICE_IN_EP1_WR_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP1_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP1_WR_ADDR_S  2
/* USB_SERIAL_JTAG_IN_EP1_STATE:RO；位位置：[1:0]；默认值：2'b1；*/
/*description:IN端点1的状态。。*/
#define USB_SERIAL_JTAG_IN_EP1_STATE    0x00000003
#define USB_SERIAL_JTAG_IN_EP1_STATE_M  ((USB_DEVICE_IN_EP1_STATE_V)<<(USB_DEVICE_IN_EP1_STATE_S))
#define USB_SERIAL_JTAG_IN_EP1_STATE_V  0x3
#define USB_SERIAL_JTAG_IN_EP1_STATE_S  0

#define USB_SERIAL_JTAG_IN_EP2_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x30)
/* USB_SERIAL_JTAG_IN_EP2_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取IN端点2的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP2_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP2_RD_ADDR_M  ((USB_DEVICE_IN_EP2_RD_ADDR_V)<<(USB_DEVICE_IN_EP2_RD_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP2_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP2_RD_ADDR_S  9
/* USB_SERIAL_JTAG_IN_EP2_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入IN端点2的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP2_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP2_WR_ADDR_M  ((USB_DEVICE_IN_EP2_WR_ADDR_V)<<(USB_DEVICE_IN_EP2_WR_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP2_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP2_WR_ADDR_S  2
/* USB_SERIAL_JTAG_IN_EP2_STATE:RO；位位置：[1:0]；默认值：2'b1；*/
/*description:IN端点2的状态。。*/
#define USB_SERIAL_JTAG_IN_EP2_STATE    0x00000003
#define USB_SERIAL_JTAG_IN_EP2_STATE_M  ((USB_DEVICE_IN_EP2_STATE_V)<<(USB_DEVICE_IN_EP2_STATE_S))
#define USB_SERIAL_JTAG_IN_EP2_STATE_V  0x3
#define USB_SERIAL_JTAG_IN_EP2_STATE_S  0

#define USB_SERIAL_JTAG_IN_EP3_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x34)
/* USB_SERIAL_JTAG_IN_EP3_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取IN端点3的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP3_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP3_RD_ADDR_M  ((USB_DEVICE_IN_EP3_RD_ADDR_V)<<(USB_DEVICE_IN_EP3_RD_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP3_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP3_RD_ADDR_S  9
/* USB_SERIAL_JTAG_IN_EP3_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入IN端点3的数据地址。。*/
#define USB_SERIAL_JTAG_IN_EP3_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_IN_EP3_WR_ADDR_M  ((USB_DEVICE_IN_EP3_WR_ADDR_V)<<(USB_DEVICE_IN_EP3_WR_ADDR_S))
#define USB_SERIAL_JTAG_IN_EP3_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_IN_EP3_WR_ADDR_S  2
/* USB_SERIAL_JTAG_IN_EP3_STATE:RO；位位置：[1:0]；默认值：2'b1；*/
/*description:IN端点3的状态。。*/
#define USB_SERIAL_JTAG_IN_EP3_STATE    0x00000003
#define USB_SERIAL_JTAG_IN_EP3_STATE_M  ((USB_DEVICE_IN_EP3_STATE_V)<<(USB_DEVICE_IN_EP3_STATE_S))
#define USB_SERIAL_JTAG_IN_EP3_STATE_V  0x3
#define USB_SERIAL_JTAG_IN_EP3_STATE_S  0

#define USB_SERIAL_JTAG_OUT_EP0_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x38)
/* USB_SERIAL_JTAG_OUT_EP0_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取OUT端点0的数据地址。。*/
#define USB_SERIAL_JTAG_OUT_EP0_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP0_RD_ADDR_M  ((USB_DEVICE_OUT_EP0_RD_ADDR_V)<<(USB_DEVICE_OUT_EP0_RD_ADDR_S))
#define USB_SERIAL_JTAG_OUT_EP0_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP0_RD_ADDR_S  9
/* USB_SERIAL_JTAG_OUT_EP0_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入OUT端点0的数据地址。当检测到USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时，OUT EP0中有USB_SERIAL-JTAG_OUT_EP0_WR_ADDR-2字节数据。。*/
#define USB_SERIAL_JTAG_OUT_EP0_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP0_WR_ADDR_M  ((USB_DEVICE_OUT_EP0_WR_ADDR_V)<<(USB_DEVICE_OUT_EP0_WR_ADDR_S))
#define USB_SERIAL_JTAG_OUT_EP0_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP0_WR_ADDR_S  2
/* USB_SERIAL_JTAG_OUT_EP0_STATE:RO；位位置：[1:0]；默认值：2’b0；*/
/*description:OUT终结点0的状态。。*/
#define USB_SERIAL_JTAG_OUT_EP0_STATE    0x00000003
#define USB_SERIAL_JTAG_OUT_EP0_STATE_M  ((USB_DEVICE_OUT_EP0_STATE_V)<<(USB_DEVICE_OUT_EP0_STATE_S))
#define USB_SERIAL_JTAG_OUT_EP0_STATE_V  0x3
#define USB_SERIAL_JTAG_OUT_EP0_STATE_S  0

#define USB_SERIAL_JTAG_OUT_EP1_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x3C)
/* USB_SERIAL_JTAG_OUT_EP1_REC_DATA_CNT:RO；比特位置：[22:16]；默认值：7'd0；*/
/*description:接收到一个数据包时OUT端点1中的数据计数。。*/
#define USB_SERIAL_JTAG_OUT_EP1_REC_DATA_CNT    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP1_REC_DATA_CNT_M  ((USB_DEVICE_OUT_EP1_REC_DATA_CNT_V)<<(USB_DEVICE_OUT_EP1_REC_DATA_CNT_S))
#define USB_SERIAL_JTAG_OUT_EP1_REC_DATA_CNT_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP1_REC_DATA_CNT_S  16
/* USB_SERIAL_JTAG_OUT_EP1_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取OUT端点1的数据地址。。*/
#define USB_SERIAL_JTAG_OUT_EP1_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP1_RD_ADDR_M  ((USB_DEVICE_OUT_EP1_RD_ADDR_V)<<(USB_DEVICE_OUT_EP1_RD_ADDR_S))
#define USB_SERIAL_JTAG_OUT_EP1_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP1_RD_ADDR_S  9
/* USB_SERIAL_JTAG_OUT_EP1_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入OUT端点1的数据地址。当检测到USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时，OUT EP1中有USB_SERIAL-JTAG_OUT_EP1_WR_ADDR-2字节数据。。*/
#define USB_SERIAL_JTAG_OUT_EP1_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP1_WR_ADDR_M  ((USB_DEVICE_OUT_EP1_WR_ADDR_V)<<(USB_DEVICE_OUT_EP1_WR_ADDR_S))
#define USB_SERIAL_JTAG_OUT_EP1_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP1_WR_ADDR_S  2
/* USB_SERIAL_JTAG_OUT_EP1_STATE:RO；位位置：[1:0]；默认值：2’b0；*/
/*description:OUT端点1的状态。。*/
#define USB_SERIAL_JTAG_OUT_EP1_STATE    0x00000003
#define USB_SERIAL_JTAG_OUT_EP1_STATE_M  ((USB_DEVICE_OUT_EP1_STATE_V)<<(USB_DEVICE_OUT_EP1_STATE_S))
#define USB_SERIAL_JTAG_OUT_EP1_STATE_V  0x3
#define USB_SERIAL_JTAG_OUT_EP1_STATE_S  0

#define USB_SERIAL_JTAG_OUT_EP2_ST_REG          (DR_REG_USB_DEVICE_BASE + 0x40)
/* USB_SERIAL_JTAG_OUT_EP2_RD_ADDR:RO；比特位置：[15:9]；默认值：7'd0；*/
/*description:读取OUT端点2的数据地址。。*/
#define USB_SERIAL_JTAG_OUT_EP2_RD_ADDR    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP2_RD_ADDR_M  ((USB_DEVICE_OUT_EP2_RD_ADDR_V)<<(USB_DEVICE_OUT_EP2_RD_ADDR_S))
#define USB_SERIAL_JTAG_OUT_EP2_RD_ADDR_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP2_RD_ADDR_S  9
/* USB_SERIAL_JTAG_OUT_EP2_WR_ADDR:RO；比特位置：[8:2]；默认值：7'd0；*/
/*description:写入OUT端点2的数据地址。当检测到USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时，OUT EP2中有USB_SERIAL-JTAG_OUT_EP2_WR_ADDR-2字节数据。。*/
#define USB_SERIAL_JTAG_OUT_EP2_WR_ADDR    0x0000007F
#define USB_SERIAL_JTAG_OUT_EP2_WR_ADDR_M  ((USB_DEVICE_OUT_EP2_WR_ADDR_V)<<(USB_DEVICE_OUT_EP2_WR_ADDR_S))
#define USB_SERIAL_JTAG_OUT_EP2_WR_ADDR_V  0x7F
#define USB_SERIAL_JTAG_OUT_EP2_WR_ADDR_S  2
/* USB_SERIAL_JTAG_OUT_EP2_STATE:RO；位位置：[1:0]；默认值：2’b0；*/
/*description:OUT端点2的状态。。*/
#define USB_SERIAL_JTAG_OUT_EP2_STATE    0x00000003
#define USB_SERIAL_JTAG_OUT_EP2_STATE_M  ((USB_DEVICE_OUT_EP2_STATE_V)<<(USB_DEVICE_OUT_EP2_STATE_S))
#define USB_SERIAL_JTAG_OUT_EP2_STATE_V  0x3
#define USB_SERIAL_JTAG_OUT_EP2_STATE_S  0

#define USB_SERIAL_JTAG_MISC_CONF_REG          (DR_REG_USB_DEVICE_BASE + 0x44)
/* USB_SERIAL_JTAG_CLK_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:1'h1:强制打开寄存器时钟。1’0：仅当应用程序写入寄存器时才支持时钟。。*/
#define USB_SERIAL_JTAG_CLK_EN    (BIT(0))
#define USB_SERIAL_JTAG_CLK_EN_M  (BIT(0))
#define USB_SERIAL_JTAG_CLK_EN_V  0x1
#define USB_SERIAL_JTAG_CLK_EN_S  0

#define USB_SERIAL_JTAG_MEM_CONF_REG          (DR_REG_USB_DEVICE_BASE + 0x48)
/* USB_SERIAL_JTAG_USB_MEM_CLK_EN:R/W；位位置：[1]；默认值：1’b1；*/
/*description:1:为usb内存强制时钟。。*/
#define USB_SERIAL_JTAG_USB_MEM_CLK_EN    (BIT(1))
#define USB_SERIAL_JTAG_USB_MEM_CLK_EN_M  (BIT(1))
#define USB_SERIAL_JTAG_USB_MEM_CLK_EN_V  0x1
#define USB_SERIAL_JTAG_USB_MEM_CLK_EN_S  1
/* USB_SERIAL_JTAG_USB_MEM_PD:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：1：关闭usb内存。。*/
#define USB_SERIAL_JTAG_USB_MEM_PD    (BIT(0))
#define USB_SERIAL_JTAG_USB_MEM_PD_M  (BIT(0))
#define USB_SERIAL_JTAG_USB_MEM_PD_V  0x1
#define USB_SERIAL_JTAG_USB_MEM_PD_S  0

#define USB_SERIAL_JTAG_DATE_REG          (DR_REG_USB_DEVICE_BASE + 0x80)
/* USB_SERIAL_JTAG_DATE:R/W；位位置：[31:0]；默认值：32'h2101200；*/
/*description:注册版本。。*/
#define USB_SERIAL_JTAG_DATE    0xFFFFFFFF
#define USB_SERIAL_JTAG_DATE_M  ((USB_DEVICE_DATE_V)<<(USB_DEVICE_DATE_S))
#define USB_SERIAL_JTAG_DATE_V  0xFFFFFFFF
#define USB_SERIAL_JTAG_DATE_S  0


#ifdef __cplusplus
}
#endif



#endif /*_SOC_USB_DEVICE_REG_H_ */

