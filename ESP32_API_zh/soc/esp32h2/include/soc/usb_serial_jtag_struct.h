// 版权所有2021浓缩咖啡系统（上海）有限公司。
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
#ifndef _SOC_USB_SERIAL_JTAG_STRUCT_H_
#define _SOC_USB_SERIAL_JTAG_STRUCT_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"

typedef volatile struct usb_serial_jtag_dev_s {
    union {
        struct {
            uint32_t rdwr_byte                     :    8;  /*通过该字段向UART Tx/Rx FIFO写入和读取字节数据。当设置了USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT时，用户可以将数据（最多64字节）写入UART Tx FIFO。当设置了USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时，用户可以检查USB_SERIAL_JTAG_OUT_EP1_WR_ADDR和USB_SERIAL-JTAG_OUT_EP0_RD_ADDR，以了解接收了多少数据，然后从UART Rx FIFO读取该数据量。*/
            uint32_t reserved8                     :    24;  /*保留*/
        };
        uint32_t val;
    } ep1;
    union {
        struct {
            uint32_t wr_done                       :    1;  /*设置此位以指示已完成向UART Tx FIFO写入字节数据。然后该位保持为0，直到USB主机读取UART Tx FIFO中的数据。*/
            uint32_t serial_in_ep_data_free        :    1;  /*1’b1：表示UART Tx FIFO未满，数据可以写入。在写入USB_SERIAL_JTAG_WR_DONE后，这将是1’b0，直到数据发送到USB主机。*/
            uint32_t serial_out_ep_data_avail      :    1;  /*1’b1：表示UART Rx FIFO中有数据。*/
            uint32_t reserved3                     :    29;  /*保留*/
        };
        uint32_t val;
    } ep1_conf;
    union {
        struct {
            uint32_t jtag_in_flush_int_raw         :    1;  /*当接收到JTAG的IN端点2的刷新命令时，原始中断位变为高电平。*/
            uint32_t sof_int_raw                   :    1;  /*当接收到SOF帧时，原始中断位变为高电平。*/
            uint32_t serial_out_recv_pkt_int_raw   :    1;  /*当串行端口OUT端点接收到一个数据包时，原始中断位变为高电平。*/
            uint32_t serial_in_empty_int_raw       :    1;  /*当串行端口IN端点为空时，原始中断位变为高电平。*/
            uint32_t pid_err_int_raw               :    1;  /*当检测到PID错误时，原始中断位变为高电平。*/
            uint32_t crc5_err_int_raw              :    1;  /*当检测到CRC5错误时，原始中断位变为高电平。*/
            uint32_t crc16_err_int_raw             :    1;  /*当检测到CRC16错误时，原始中断位变为高电平。*/
            uint32_t stuff_err_int_raw             :    1;  /*当检测到位填充错误时，原始中断位变为高电平。*/
            uint32_t in_token_rec_in_ep1_int_raw   :    1;  /*当接收到IN端点1的IN令牌时，原始中断位变为高电平。*/
            uint32_t usb_bus_reset_int_raw         :    1;  /*当检测到USB总线复位时，原始中断位变为高电平。*/
            uint32_t out_ep1_zero_payload_int_raw  :    1;  /*当OUT端点1接收到具有零有效载荷的分组时，原始中断位变为高电平。*/
            uint32_t out_ep2_zero_payload_int_raw  :    1;  /*当OUT端点2接收到具有零有效载荷的分组时，原始中断位变为高电平。*/
            uint32_t reserved12                    :    20;  /*保留*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t jtag_in_flush_int_st          :    1;  /*USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT中断的原始中断状态位。*/
            uint32_t sof_int_st                    :    1;  /*USB_SERIAL_JTAG_SOF_INT中断的原始中断状态位。*/
            uint32_t serial_out_recv_pkt_int_st    :    1;  /*USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT中断的原始中断状态位。*/
            uint32_t serial_in_empty_int_st        :    1;  /*USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT中断的原始中断状态位。*/
            uint32_t pid_err_int_st                :    1;  /*USB_SERIAL_JTAG_PID_ERR_INT中断的原始中断状态位。*/
            uint32_t crc5_err_int_st               :    1;  /*USB_SERIAL_JTAG_CRC5_ERR_INT中断的原始中断状态位。*/
            uint32_t crc16_err_int_st              :    1;  /*USB_SERIAL_JTAG_CRC16_ERR_INT中断的原始中断状态位。*/
            uint32_t stuff_err_int_st              :    1;  /*USB_SERIAL_JTAG_STUFF_ERR_INT中断的原始中断状态位。*/
            uint32_t in_token_rec_in_ep1_int_st    :    1;  /*USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT中断的原始中断状态位。*/
            uint32_t usb_bus_reset_int_st          :    1;  /*USB_SERIAL_JTAG_USB_BUS_RESET_INT中断的原始中断状态位。*/
            uint32_t out_ep1_zero_payload_int_st   :    1;  /*USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT中断的原始中断状态位。*/
            uint32_t out_ep2_zero_payload_int_st   :    1;  /*USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT中断的原始中断状态位。*/
            uint32_t reserved12                    :    20;  /*保留*/
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t jtag_in_flush_int_ena         :    1;  /*USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT中断的中断启用位。*/
            uint32_t sof_int_ena                   :    1;  /*USB_SERIAL_JTAG_SOF_INT中断的中断启用位。*/
            uint32_t serial_out_recv_pkt_int_ena   :    1;  /*USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT中断的中断启用位。*/
            uint32_t serial_in_empty_int_ena       :    1;  /*USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT中断的中断启用位。*/
            uint32_t pid_err_int_ena               :    1;  /*USB_SERIAL_JTAG_PID_ERR_INT中断的中断启用位。*/
            uint32_t crc5_err_int_ena              :    1;  /*USB_SERIAL_JTAG_CRC5_ERR_INT中断的中断启用位。*/
            uint32_t crc16_err_int_ena             :    1;  /*USB_SERIAL_JTAG_CRC16_ERR_INT中断的中断启用位。*/
            uint32_t stuff_err_int_ena             :    1;  /*USB_SERIAL_JTAG_STUFF_ERR_INT中断的中断启用位。*/
            uint32_t in_token_rec_in_ep1_int_ena   :    1;  /*USB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT中断的中断启用位。*/
            uint32_t usb_bus_reset_int_ena         :    1;  /*USB_SERIAL_JTAG_USB_BUS_RESET_INT中断的中断启用位。*/
            uint32_t out_ep1_zero_payload_int_ena  :    1;  /*USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT中断的中断启用位。*/
            uint32_t out_ep2_zero_payload_int_ena  :    1;  /*USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT中断的中断启用位。*/
            uint32_t reserved12                    :    20;  /*保留*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t jtag_in_flush_int_clr         :    1;  /*设置此位以清除USB_SERIAL_JTAG_JTAG_IN_FLUSH_INT中断。*/
            uint32_t sof_int_clr                   :    1;  /*设置此位以清除USB_SERIAL_JTAG_JTAG_SOF_INT中断。*/
            uint32_t serial_out_recv_pkt_int_clr   :    1;  /*设置此位以清除USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT中断。*/
            uint32_t serial_in_empty_int_clr       :    1;  /*设置此位以清除USB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT中断。*/
            uint32_t pid_err_int_clr               :    1;  /*设置此位以清除USB_SERIAL_JTAG_PID_ERR_INT中断。*/
            uint32_t crc5_err_int_clr              :    1;  /*设置此位以清除USB_SERIAL_JTAG_CRC5_ERR_INT中断。*/
            uint32_t crc16_err_int_clr             :    1;  /*设置此位以清除USB_SERIAL_JTAG_CRC16_ERR_INT中断。*/
            uint32_t stuff_err_int_clr             :    1;  /*设置此位以清除USB_SERIAL_JTAG_STUFF_ERR_INT中断。*/
            uint32_t in_token_rec_in_ep1_int_clr   :    1;  /*设置此位以清除USB_SERIAL_JTAG_IN_TOKEN_IN_EP1_INT中断。*/
            uint32_t usb_bus_reset_int_clr         :    1;  /*设置此位以清除USB_SERIAL_JTAG_USB_BUS_RESET_INT中断。*/
            uint32_t out_ep1_zero_payload_int_clr  :    1;  /*设置此位以清除USB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT中断。*/
            uint32_t out_ep2_zero_payload_int_clr  :    1;  /*设置此位以清除USB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT中断。*/
            uint32_t reserved12                    :    20;  /*保留*/
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t phy_sel                       :    1;  /*选择内部/外部PHY。1’b0：内部PHY，1’b1：外部PHY*/
            uint32_t exchg_pins_override           :    1;  /*启用软件控制USB D+D-交换*/
            uint32_t exchg_pins                    :    1;  /*USB D+D-交换*/
            uint32_t vrefh                         :    2;  /*控制单端输入高阈值。1.76V至2V，步进80mV*/
            uint32_t vrefl                         :    2;  /*控制单端输入低阈值。0.8V至1.04V，步进80mV*/
            uint32_t vref_override                 :    1;  /*启用软件控制输入阈值*/
            uint32_t pad_pull_override             :    1;  /*启用软件控制USB D+D-下拉*/
            uint32_t dp_pullup                     :    1;  /*控制USB D+上拉。*/
            uint32_t dp_pulldown                   :    1;  /*控制USB D+下拉。*/
            uint32_t dm_pullup                     :    1;  /*控制USB D-上拉。*/
            uint32_t dm_pulldown                   :    1;  /*控制USB D-下拉。*/
            uint32_t pullup_value                  :    1;  /*控制上拉值。*/
            uint32_t usb_pad_enable                :    1;  /*启用USB pad功能。*/
            uint32_t reserved15                    :    17;
        };
        uint32_t val;
    } conf0;
    union {
        struct {
            uint32_t test_enable                   :    1;  /*启用USB焊盘测试*/
            uint32_t test_usb_oe                   :    1;  /*测试中的USB垫*/
            uint32_t test_tx_dp                    :    1;  /*测试中的USB D+tx值*/
            uint32_t test_tx_dm                    :    1;  /*USB D-测试中的tx值*/
            uint32_t reserved4                     :    28;
        };
        uint32_t val;
    } test;
    union {
        struct {
            uint32_t in_fifo_cnt                   :    2;  /*JTAG在fifo计数器中。*/
            uint32_t in_fifo_empty                 :    1;  /*1： fifo中的JTAG为空。*/
            uint32_t in_fifo_full                  :    1;  /*1： fifo中的JTAG已满。*/
            uint32_t out_fifo_cnt                  :    2;  /*JTAT输出fifo计数器。*/
            uint32_t out_fifo_empty                :    1;  /*1： JTAG输出fifo为空。*/
            uint32_t out_fifo_full                 :    1;  /*1： JTAG输出fifo已满。*/
            uint32_t in_fifo_reset                 :    1;  /*写1以重置fifo中的JTAG。*/
            uint32_t out_fifo_reset                :    1;  /*写1以重置JTAG输出fifo。*/
            uint32_t reserved10                    :    22;
        };
        uint32_t val;
    } jfifo_st;
    union {
        struct {
            uint32_t sof_frame_index               :    11;  /*收到SOF帧的帧索引。*/
            uint32_t reserved11                    :    21;
        };
        uint32_t val;
    } fram_num;
    union {
        struct {
            uint32_t in_ep0_state                  :    2;  /*IN终结点0的状态。*/
            uint32_t in_ep0_wr_addr                :    7;  /*写入IN终结点0的数据地址。*/
            uint32_t in_ep0_rd_addr                :    7;  /*读取IN终结点0的数据地址。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } in_ep0_st;
    union {
        struct {
            uint32_t in_ep1_state                  :    2;  /*IN端点1的状态。*/
            uint32_t in_ep1_wr_addr                :    7;  /*写入IN端点1的数据地址。*/
            uint32_t in_ep1_rd_addr                :    7;  /*读取IN端点1的数据地址。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } in_ep1_st;
    union {
        struct {
            uint32_t in_ep2_state                  :    2;  /*IN端点2的状态。*/
            uint32_t in_ep2_wr_addr                :    7;  /*写入IN端点2的数据地址。*/
            uint32_t in_ep2_rd_addr                :    7;  /*读取IN端点2的数据地址。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } in_ep2_st;
    union {
        struct {
            uint32_t in_ep3_state                  :    2;  /*IN端点3的状态。*/
            uint32_t in_ep3_wr_addr                :    7;  /*写入IN端点3的数据地址。*/
            uint32_t in_ep3_rd_addr                :    7;  /*读取IN端点3的数据地址。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } in_ep3_st;
    union {
        struct {
            uint32_t out_ep0_state                 :    2;  /*OUT终结点0的状态。*/
            uint32_t out_ep0_wr_addr               :    7;  /*写入OUT端点0的数据地址。当检测到USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时。OUT EP0中有USB_SERIAL_JTAG_OUT_EP0_WR_ADDR-2字节数据。*/
            uint32_t out_ep0_rd_addr               :    7;  /*读取OUT端点0的数据地址。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } out_ep0_st;
    union {
        struct {
            uint32_t out_ep1_state                 :    2;  /*OUT端点1的状态。*/
            uint32_t out_ep1_wr_addr               :    7;  /*写入OUT端点1的数据地址。当检测到USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时。在OUT EP1中存在USB_SERIAL_JTAG_OUT_EP1_WR_ADDR-2字节数据。*/
            uint32_t out_ep1_rd_addr               :    7;  /*读取OUT端点1的数据地址。*/
            uint32_t out_ep1_rec_data_cnt          :    7;  /*当接收到一个数据包时，OUT端点1中的数据计数。*/
            uint32_t reserved23                    :    9;  /*保留*/
        };
        uint32_t val;
    } out_ep1_st;
    union {
        struct {
            uint32_t out_ep2_state                 :    2;  /*OUT端点2的状态。*/
            uint32_t out_ep2_wr_addr               :    7;  /*写入OUT端点2的数据地址。当检测到USB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT时。在OUT EP2中存在USB_SERIAL_JTAG_OUT_EP2_WR_ADDR-2字节数据。*/
            uint32_t out_ep2_rd_addr               :    7;  /*读取OUT端点2的数据地址。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } out_ep2_st;
    union {
        struct {
            uint32_t clk_en                        :    1;  /*1'h1：强制打开寄存器时钟。1’0：仅当应用程序写入寄存器时才支持时钟。*/
            uint32_t reserved1                     :    31;
        };
        uint32_t val;
    } misc_conf;
    union {
        struct {
            uint32_t usb_mem_pd                    :    1;  /*1： 关闭usb内存。*/
            uint32_t usb_mem_clk_en                :    1;  /*1： 强制打开usb内存时钟。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } mem_conf;
    uint32_t reserved_4c;
    uint32_t reserved_50;
    uint32_t reserved_54;
    uint32_t reserved_58;
    uint32_t reserved_5c;
    uint32_t reserved_60;
    uint32_t reserved_64;
    uint32_t reserved_68;
    uint32_t reserved_6c;
    uint32_t reserved_70;
    uint32_t reserved_74;
    uint32_t reserved_78;
    uint32_t reserved_7c;
    uint32_t date;
} usb_serial_jtag_dev_t;
extern usb_serial_jtag_dev_t USB_SERIAL_JTAG;
#ifdef __cplusplus
}
#endif



#endif /*_SOC_USB_SERIAL_JTAG_STRUCT_H_ */

