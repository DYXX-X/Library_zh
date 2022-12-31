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
#ifndef _SOC_I2C_STRUCT_H_
#define _SOC_I2C_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct i2c_dev_s {
    union {
        struct {
            uint32_t period:14;             /*此寄存器用于配置SCL时钟的低电平宽度。*/
            uint32_t reserved14:    18;
        };
        uint32_t val;
    } scl_low_period;
    union {
        struct {
            uint32_t sda_force_out:    1;           /*1： 正常输出sda数据0：交换sda\o和sda\oe的函数（sda\o是原始的内部输出sda信号sda\oe是内部输出sdd信号的使能位）*/
            uint32_t scl_force_out:    1;           /*1： 正常输出scl时钟0：交换sclo和scloe的功能（sclo是原始的内部输出scl信号scloe是内部输出scl信号的使能位）*/
            uint32_t sample_scl_level: 1;           /*将此位设置为SCL低电平的采样数据。清除此位以采样SCL高电平的数据。*/
            uint32_t reserved3:        1;
            uint32_t ms_mode:          1;           /*设置此位以将模块配置为i2c主设备，清除此位以配置模块为i2c从设备。*/
            uint32_t trans_start:      1;           /*设置此位以开始在tx_fifo中发送数据。*/
            uint32_t tx_lsb_first:     1;           /*该位用于控制需要发送数据的发送模式。1： 从最高有效位0接收数据：从最低有效位接收数据*/
            uint32_t rx_lsb_first:     1;           /*该位用于控制接收数据的存储模式。1： 从最高有效位0接收数据：从最低有效位接收数据*/
            uint32_t clk_en:           1;           /*这是用于读取或写入寄存器的时钟门控控制位。*/
            uint32_t reserved9:       23;
        };
        uint32_t val;
    } ctr;
    union {
        struct {
            uint32_t ack_rec:             1;        /*该寄存器存储ACK位的值。*/
            uint32_t slave_rw:            1;        /*当处于从模式1时：主读从0：主写从。*/
            uint32_t time_out:            1;        /*当I2C需要多于time_out_reg时钟来接收数据时，该寄存器变为高电平。*/
            uint32_t arb_lost:            1;        /*当I2C失去对SDA线的控制时，该寄存器变为高电平。*/
            uint32_t bus_busy:            1;        /*1： I2C总线正忙于传输数据。0:I2C总线处于空闲状态。*/
            uint32_t slave_addressed:     1;        /*当被配置为i2c从设备并且主设备发送的地址等于从设备的地址时，该位将为高电平。*/
            uint32_t byte_trans:          1;        /*当传输一个字节时，该寄存器变为高电平。*/
            uint32_t reserved7:           1;
            uint32_t rx_fifo_cnt:         6;        /*此寄存器表示需要发送的数据量。*/
            uint32_t reserved14:          4;
            uint32_t tx_fifo_cnt:         6;        /*该寄存器将接收的数据量存储在ram中。*/
            uint32_t scl_main_state_last: 3;        /*此寄存器存储i2c模块的状态机值。3'h0:SCL_MAIN_IDLE 3'h1:SCL_ADDRESS_SHIFT 3'h2:SCL_ACK_ADDRESS 3'h3:SCL_RX_DATA 3'h4 SCL_TX_DATA 3'h5:SCL_SEND_ACK 3'h6:SCL_WAIT_ACK*/
            uint32_t reserved27:          1;
            uint32_t scl_state_last:      3;        /*此寄存器存储状态机的值以生成SCL。3'h0:SCL_IDLE 3'h1:SCL_START 3'h2:SCL_LOW_EDGE 3'h3:SCL_LLOW 3'h4:SCL_HIGH_EDGE 3'h5:SCL_HIGH 3'h6:SCL_STOP*/
            uint32_t reserved31:          1;
        };
        uint32_t val;
    } status_reg;
    union {
        struct {
            uint32_t tout:      20;                 /*此寄存器用于配置接收数据的最大时钟数，单位：APB时钟周期。*/
            uint32_t reserved20:12;
        };
        uint32_t val;
    } timeout;
    union {
        struct {
            uint32_t addr:       15;                /*当配置为i2c从机时，该寄存器用于配置从机的地址。*/
            uint32_t reserved15: 16;
            uint32_t en_10bit:    1;                /*该寄存器用于启用从10位地址模式。*/
        };
        uint32_t val;
    } slave_addr;
    union {
        struct {
            uint32_t rx_fifo_start_addr: 5;         /*这是最后一个接收数据的偏移地址，如nonfof_rx_thres_register中所述。*/
            uint32_t rx_fifo_end_addr:   5;         /*这是第一个接收数据的偏移地址，如nonifo_rx_thres_register中所述。*/
            uint32_t tx_fifo_start_addr: 5;         /*这是第一个发送数据的偏移地址，如非ifo_tx_thres寄存器中所述。*/
            uint32_t tx_fifo_end_addr:   5;         /*这是最后一次发送数据的偏移地址，如非ifo_tx_thres寄存器中所述。*/
            uint32_t reserved20:        12;
        };
        uint32_t val;
    } fifo_st;
    union {
        struct {
            uint32_t rx_fifo_full_thrhd: 5;
            uint32_t tx_fifo_empty_thrhd:5;         /*使用apb-fifo访问时配置tx_fifo空threhd值*/
            uint32_t nonfifo_en:         1;         /*将此位设置为enble apb nonifo访问。*/
            uint32_t fifo_addr_cfg_en:   1;         /*当该位设置为1时，地址后的字节表示I2C从机ram的偏移地址。*/
            uint32_t rx_fifo_rst:        1;         /*设置此位以在使用apb fifo访问时重置rx fifo。*/
            uint32_t tx_fifo_rst:        1;         /*设置此位以在使用apb fifo访问时重置tx fifo。*/
            uint32_t nonfifo_rx_thres:   6;         /*当I2C接收到多于非ifo_rx_thres数据时，它将产生rx_send_full_int_raw中断并更新接收数据的当前偏移地址。*/
            uint32_t nonfifo_tx_thres:   6;         /*当I2C发送的数据多于非ifo_tx_thres数据时，它将产生tx_send_empty_int_raw中断并更新发送数据的当前偏移地址。*/
            uint32_t reserved26:         6;
        };
        uint32_t val;
    } fifo_conf;
    union {
        struct {
            uint32_t data:              8;          /*寄存器表示使用apb-fifo访问时从rx_fifo读取的字节数据*/
            uint32_t reserved:          24;
        };
        uint32_t val;
    } fifo_data;
    union {
        struct {
            uint32_t rx_fifo_full:     1;           /*使用apb fifo访问时rx_fifo已满的原始中断状态位。*/
            uint32_t tx_fifo_empty:    1;           /*使用apb fifo访问时，tx_fifo的原始中断状态位为空。*/
            uint32_t rx_fifo_ovf:      1;           /*当使用apb fifo访问时，用于接收数据溢出的原始中断状态位。*/
            uint32_t end_detect:       1;           /*end_detect_int中断的原始中断状态位。当I2C处理END命令时，它将产生END_detect_int中断。*/
            uint32_t slave_tran_comp:  1;           /*slave_trans_comp_int中断的原始中断状态位。当I2C从设备检测到STOP位时，它将产生Slave_trans_comp_int中断。*/
            uint32_t arbitration_lost: 1;           /*仲裁_lost_int中断的原始中断状态位。当I2C失去I2C总线的使用权时，它将产生仲裁_。*/
            uint32_t master_tran_comp: 1;           /*master_tra_comp_int中断的原始中断状态位。当I2C Master发送或接收字节时，它将产生Master_tran_comp_int中断。*/
            uint32_t trans_complete:   1;           /*trans_complete_int中断的原始中断状态位。当I2C Master完成STOP命令时，它将产生trans_complete_int中断。*/
            uint32_t time_out:         1;           /*time_out_int中断的原始中断状态位。当I2C花费大量时间来接收数据时，它将产生time_out_int中断。*/
            uint32_t trans_start:      1;           /*trans_start_int中断的原始中断状态位。当I2C发送START位时，它将产生trans_START_int中断。*/
            uint32_t ack_err:          1;           /*ack_err_int中断的原始中断状态位。当I2C接收到错误的ACK位时，它将产生ACK_err_int中断。。*/
            uint32_t rx_rec_full:      1;           /*rx_rec_full_int中断的原始中断状态位。当I2C接收的数据多于非ifo_rx_thres时，它将产生rx_rec_full_int中断。*/
            uint32_t tx_send_empty:    1;           /*tx_send_empty_int中断的原始中断状态位。当I2C发送的数据多于非ifo_tx_thres时，它将产生tx_send_empty_int中断。。*/
            uint32_t reserved13:      19;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rx_fifo_full:     1;           /*设置此位以清除rx_fifo_full_int中断。*/
            uint32_t tx_fifo_empty:    1;           /*设置此位以清除tx_fifo_empty_int中断。*/
            uint32_t rx_fifo_ovf:      1;           /*设置此位以清除rx_fifo_ovf_int中断。*/
            uint32_t end_detect:       1;           /*设置此位以清除end_detect_int中断。*/
            uint32_t slave_tran_comp:  1;           /*设置此位以清除slave_trans_comp_int中断。*/
            uint32_t arbitration_lost: 1;           /*设置此位以清除仲裁_lost_int中断。*/
            uint32_t master_tran_comp: 1;           /*设置此位以清除master_tran_comp中断。*/
            uint32_t trans_complete:   1;           /*设置此位以清除trans_complete_int中断。*/
            uint32_t time_out:         1;           /*设置此位以清除time_out_int中断。*/
            uint32_t trans_start:      1;           /*设置此位以清除trans_start_int中断。*/
            uint32_t ack_err:          1;           /*设置此位以清除ack_err_int中断。*/
            uint32_t rx_rec_full:      1;           /*设置此位以清除rx_rec_full_int中断。*/
            uint32_t tx_send_empty:    1;           /*设置此位以清除tx_send_empty_int中断。*/
            uint32_t reserved13:      19;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t rx_fifo_full:     1;           /*rx_fifo_full_int中断的启用位。*/
            uint32_t tx_fifo_empty:    1;           /*tx_fifo_empty_int中断的启用位。*/
            uint32_t rx_fifo_ovf:      1;           /*rx_fifo_ovf_int中断的启用位。*/
            uint32_t end_detect:       1;           /*end_detect_int中断的启用位。*/
            uint32_t slave_tran_comp:  1;           /*slave_trans_comp_int中断的启用位。*/
            uint32_t arbitration_lost: 1;           /*仲裁_lost_int中断的启用位。*/
            uint32_t master_tran_comp: 1;           /*master_tran_comp_int中断的启用位。*/
            uint32_t trans_complete:   1;           /*trans_complete_int中断的启用位。*/
            uint32_t time_out:         1;           /*time_out_int中断的启用位。*/
            uint32_t trans_start:      1;           /*trans_start_int中断的启用位。*/
            uint32_t ack_err:          1;           /*ack_err_int中断的启用位。*/
            uint32_t rx_rec_full:      1;           /*rx_rec_full_int中断的启用位。*/
            uint32_t tx_send_empty:    1;           /*tx_send_empty_int中断的启用位。*/
            uint32_t reserved13:      19;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rx_fifo_full:     1;            /*rx_fifo_full_int中断的屏蔽中断状态。*/
            uint32_t tx_fifo_empty:    1;            /*tx_fifo_empty_int中断的屏蔽中断状态。*/
            uint32_t rx_fifo_ovf:      1;            /*rx_fifo_ovf_int中断的屏蔽中断状态。*/
            uint32_t end_detect:       1;            /*end_detect_int中断的屏蔽中断状态。*/
            uint32_t slave_tran_comp:  1;            /*slave_trans_comp_int中断的屏蔽中断状态。*/
            uint32_t arbitration_lost: 1;            /*仲裁_lost_int中断的屏蔽中断状态。*/
            uint32_t master_tran_comp: 1;            /*master_tran_comp_int中断的屏蔽中断状态。*/
            uint32_t trans_complete:   1;            /*trans_complete_int中断的屏蔽中断状态。*/
            uint32_t time_out:         1;            /*time_out_int中断的屏蔽中断状态。*/
            uint32_t trans_start:      1;            /*trans_start_int中断的屏蔽中断状态。*/
            uint32_t ack_err:          1;            /*ack_err_int中断的屏蔽中断状态。*/
            uint32_t rx_rec_full:      1;            /*rx_rec_full_int中断的屏蔽中断状态。*/
            uint32_t tx_send_empty:    1;            /*tx_send_empty_int中断的屏蔽中断状态。*/
            uint32_t reserved13:      19;
        };
        uint32_t val;
    } int_status;
    union {
        struct {
            uint32_t time:        10;                /*此寄存器用于配置时钟num I2C，用于在SCL的负边缘之后保存数据。*/
            uint32_t reserved10:  22;
        };
        uint32_t val;
    } sda_hold;
    union {
        struct {
            uint32_t time:       10;                 /*此寄存器用于配置时钟编号I2C，用于在SCL的偏倚后对SDA上的数据进行采样*/
            uint32_t reserved10: 22;
        };
        uint32_t val;
    } sda_sample;
    union {
        struct {
            uint32_t period:     14;                 /*此寄存器用于在SCL为低电平期间配置时钟num。*/
            uint32_t reserved14: 18;
        };
        uint32_t val;
    } scl_high_period;
    uint32_t reserved_3c;
    union {
        struct {
            uint32_t time:       10;                /*该寄存器用于为开始标记配置SDA的负边缘和SCL的负边缘之间的时钟num。*/
            uint32_t reserved10: 22;
        };
        uint32_t val;
    } scl_start_hold;
    union {
        struct {
            uint32_t time:       10;                /*该寄存器用于配置SCL的偏旁和SDA的负边之间的时钟num，以用于重新启动标记。*/
            uint32_t reserved10: 22;
        };
        uint32_t val;
    } scl_rstart_setup;
    union {
        struct {
            uint32_t time:       14;                /*该寄存器用于配置STOP位的偏倚后的时钟num。*/
            uint32_t reserved14: 18;
        };
        uint32_t val;
    } scl_stop_hold;
    union {
        struct {
            uint32_t time:       10;                /*该寄存器用于配置SCL的偏旁和SDA的偏旁之间的时钟num。*/
            uint32_t reserved10: 22;
        };
        uint32_t val;
    } scl_stop_setup;
    union {
        struct {
            uint32_t thres:      3;                 /*当输入SCL的脉冲宽度小于该寄存器值时，I2C忽略该脉冲。*/
            uint32_t en:         1;                 /*这是SCL的筛选器启用位。*/
            uint32_t reserved4: 28;
        };
        uint32_t val;
    } scl_filter_cfg;
    union {
        struct {
            uint32_t thres:      3;                 /*当输入SCL的脉冲宽度小于该寄存器值时，I2C忽略该脉冲。*/
            uint32_t en:         1;                 /*这是SDA的过滤器启用位。*/
            uint32_t reserved4: 28;
        };
        uint32_t val;
    } sda_filter_cfg;
    union {
        struct {
            uint32_t byte_num:      8;              /*Byte_num表示需要发送或接收的数据数量。*/
            uint32_t ack_en:        1;              /*ack_check_en ack_exp和ack值用于控制ack位。*/
            uint32_t ack_exp:       1;              /*ack_check_en ack_exp和ack值用于控制ack位。*/
            uint32_t ack_val:       1;              /*ack_check_en ack_exp和ack值用于控制ack位。*/
            uint32_t op_code:       3;              /*op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。*/
            uint32_t reserved14:   17;
            uint32_t done:  1;                      /*当命令0在I2C主模式下完成时，该位变为高电平。*/
        };
        uint32_t val;
    } command[16];
    uint32_t reserved_98;
    uint32_t reserved_9c;
    uint32_t reserved_a0;
    uint32_t reserved_a4;
    uint32_t reserved_a8;
    uint32_t reserved_ac;
    uint32_t reserved_b0;
    uint32_t reserved_b4;
    uint32_t reserved_b8;
    uint32_t reserved_bc;
    uint32_t reserved_c0;
    uint32_t reserved_c4;
    uint32_t reserved_c8;
    uint32_t reserved_cc;
    uint32_t reserved_d0;
    uint32_t reserved_d4;
    uint32_t reserved_d8;
    uint32_t reserved_dc;
    uint32_t reserved_e0;
    uint32_t reserved_e4;
    uint32_t reserved_e8;
    uint32_t reserved_ec;
    uint32_t reserved_f0;
    uint32_t reserved_f4;
    uint32_t date;                                  /**/
    uint32_t reserved_fc;
    uint32_t ram_data[32];                          /*这是使用apb非ifo访问时ram的起始地址。*/
} i2c_dev_t;
extern i2c_dev_t I2C0;
extern i2c_dev_t I2C1;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_I2C_STRUCT_H_ */

