/** 版权所有2021浓缩咖啡系统（上海）有限公司
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**组：定时寄存器*/
/** scl_low_period寄存器类型配置scl时钟的低电平宽度
 */
typedef union {
    struct {
        /** scl_low_period:R/W；位位置：[8:0]；默认值：0；此寄存器用于配置SCL在I2C模块时钟周期中在主模式下保持低电平的时间。
         */
        uint32_t scl_low_period:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_scl_low_period_reg_t;

/** sda_hold寄存器的类型配置负SCL边缘后的保持时间。
 */
typedef union {
    struct {
        /** sda_hold_time:R/W；位位置：[8:0]；默认值：0；该寄存器用于配置在SCL负边缘之后保持数据的时间，以I2C模块时钟周期为单位。
         */
        uint32_t sda_hold_time:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_sda_hold_reg_t;

/** sda_sample寄存器的类型配置正SCL边缘后的采样时间。
 */
typedef union {
    struct {
        /** sda_sample_time:R/W；位位置：[8:0]；默认值：0；该寄存器用于在I2C模块时钟周期中配置SDA采样的时间。
         */
        uint32_t sda_sample_time:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_sda_sample_reg_t;

/** scl_high_period寄存器的类型配置scl的高级别宽度
 */
typedef union {
    struct {
        /** scl_high-period:R/W；位位置：[8:0]；默认值：0；此寄存器用于配置SCL在I2C模块时钟周期中在主模式下保持高电平的时间。
         */
        uint32_t scl_high_period:9;
        /** scl_wait_high_period:R/W；比特位置：[15:9]；默认值：0；此寄存器用于在I2C模块时钟周期中配置SCL_FSM在主模式下SCL高电平的等待时间。
         */
        uint32_t scl_wait_high_period:7;
        uint32_t reserved_16:16;
    };
    uint32_t val;
} i2c_scl_high_period_reg_t;

/** scl_start_hold寄存器的类型为启动条件配置SDA和scl负边缘之间的延迟
 */
typedef union {
    struct {
        /** scl_start_hold_time:R/W；位位置：[8:0]；默认值：8；该寄存器用于在I2C模块时钟周期中，为START条件配置SDA的负边缘和SCL的负边缘之间的时间。
         */
        uint32_t scl_start_hold_time:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_scl_start_hold_reg_t;

/** scl_rstart_setup寄存器的类型配置scl的正边缘和SDA的负边缘之间的延迟
 */
typedef union {
    struct {
        /** scl_rstart_setup_time:R/W；位位置：[8:0]；默认值：8；该寄存器用于在I2C模块时钟周期中，为RESTART条件配置SCL的正边缘和SDA的负边缘之间的时间。
         */
        uint32_t scl_rstart_setup_time:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_scl_rstart_setup_reg_t;

/** scl_stop_hold寄存器的类型为停止条件配置scl时钟边缘之后的延迟
 */
typedef union {
    struct {
        /** scl_stop_hold_time:R/W；位位置：[8:0]；默认值：8；该寄存器用于在I2C模块时钟周期中配置STOP条件后的延迟。
         */
        uint32_t scl_stop_hold_time:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_scl_stop_hold_reg_t;

/** scl_stop_setup寄存器的类型为停止条件配置SDA和scl正边缘之间的延迟
 */
typedef union {
    struct {
        /** scl_stop_setup_time:R/W；位位置：[8:0]；默认值：8；该寄存器用于在I2C模块时钟周期中配置SCL的正边缘和SDA的正边缘之间的时间。
         */
        uint32_t scl_stop_setup_time:9;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} i2c_scl_stop_setup_reg_t;

/** scl_st_time_out寄存器的类型scl状态超时寄存器
 */
typedef union {
    struct {
        /** scl_st_to_i2c：右侧；位位置：[4:0]；默认值：16；SCL_FSM状态不变周期的阈值。应该不超过23
         */
        uint32_t scl_st_to_i2c:5;
        uint32_t reserved_5:27;
    };
    uint32_t val;
} i2c_scl_st_time_out_reg_t;

/** scl_main_st_time_out寄存器的类型scl主状态超时寄存器
 */
typedef union {
    struct {
        /** scl_main_st_to_i2c：右侧；位位置：[4:0]；默认值：16；SCL_MAIN_FSM状态未更改期间的阈值。不应该超过23
         */
        uint32_t scl_main_st_to_i2c:5;
        uint32_t reserved_5:27;
    };
    uint32_t val;
} i2c_scl_main_st_time_out_reg_t;


/**组：配置寄存器*/
/** ctr寄存器类型传输设置
 */
typedef union {
    struct {
        /** sda_frce_out:R/W；位位置：[0]；默认值：1；0：直接输出；1： 漏极开路输出。
         */
        uint32_t sda_force_out:1;
        /** scl_force_out:R/W；位位置：[1]；默认值：1；0：直接输出；1： 漏极开路输出。
         */
        uint32_t scl_force_out:1;
        /** sample_scl_level:R/W；位位置：[2]；默认值：0；此寄存器用于选择采样模式。1： 在SCL低电平上采样SDA数据。0:SCL高电平上的SDA数据采样。
         */
        uint32_t sample_scl_level:1;
        /** rx_full_ack_level:R/W；位位置：[3]；默认值：1；此寄存器用于配置rx_fifo_cnt达到阈值时主机需要发送的ACK值。
         */
        uint32_t rx_full_ack_level:1;
        /** ms_mode：R/W；位位置：[4]；默认值：0；设置此位以将模块配置为I2C主机。清除此位以将模块配置为I2C从设备。
         */
        uint32_t ms_mode:1;
        /** trans_start:WT；位位置：[5]；默认值：0；设置此位以开始发送txfifo中的数据。
         */
        uint32_t trans_start:1;
        /** tx_lsb_first:R/W；位位置：[6]；默认值：0；该位用于控制需要发送的数据的发送模式。1： 从最低有效位发送数据；0：从最高有效位发送数据。
         */
        uint32_t tx_lsb_first:1;
        /** rx_lsb_first:R/W；位位置：[7]；默认值：0；该位用于控制接收数据的存储模式。1： 从所述最低有效位接收数据；0：从最高有效位接收数据。
         */
        uint32_t rx_lsb_first:1;
        /** clk_en:R/W；位位置：[8]；默认值：0；保留
         */
        uint32_t clk_en:1;
        /** 仲裁_ en:R/W；位位置：[9]；默认值：1；这是仲裁_列表的启用位。
         */
        uint32_t arbitration_en:1;
        /** fsm_rst:WT；位位置：[10]；默认值：0；该寄存器用于重置scl FMS。
         */
        uint32_t fsm_rst:1;
        /** conf_upgate:WT；位位置：[11]；默认值：0；同步位
         */
        uint32_t conf_upgate:1;
        /** slv_tx_auto_start_en:R/W；位位置：[12]；默认值：0；这是从设备自动发送数据的启用位
         */
        uint32_t slv_tx_auto_start_en:1;
        /** 地址_10bit_rw_check_en:R/W；位位置：[13]；默认值：0；这是用于检查10位寻址的r/w位是否符合I2C协议的启用位
         */
        uint32_t addr_10bit_rw_check_en:1;
        /** addr_broadcasting_en:R/W；位位置：[14]；默认值：0；这是支持7位通用调用函数的启用位。
         */
        uint32_t addr_broadcasting_en:1;
        uint32_t reserved_15:17;
    };
    uint32_t val;
} i2c_ctr_reg_t;

/** 要注册的类型设置接收数据的超时控制。
 */
typedef union {
    struct {
        /** 时间输出值：R/W；位位置：[4:0]；默认值：16；该寄存器用于配置在APB时钟周期中接收数据位的超时。
         */
        uint32_t time_out_value:5;
        /** time_out_en:R/W；位位置：[5]；默认值：0；这是超时控制的启用位。
         */
        uint32_t time_out_en:1;
        uint32_t reserved_6:26;
    };
    uint32_t val;
} i2c_to_reg_t;

/** 从属地址寄存器类型本地从属地址设置
 */
typedef union {
    struct {
        /** 从属地址：R/W；位位置：[14:0]；默认值：0；当配置为I2C从设备时，此字段用于配置从设备地址。
         */
        uint32_t slave_addr:15;
        uint32_t reserved_15:16;
        /** 地址_10bit_en:R/W；位位置：[31]；默认值：0；该字段用于在主模式下启用从10位寻址模式。
         */
        uint32_t addr_10bit_en:1;
    };
    uint32_t val;
} i2c_slave_addr_reg_t;

/** fifo.conf寄存器fifo配置寄存器的类型。
 */
typedef union {
    struct {
        /** rxifo_wm_thrd:R/W；位位置：[4:0]；默认值：11；非ifo访问模式下rx FIFO的水位标记阈值。当reg_reg_fifo_prt_en为1且rx fifo计数器大于reg_rxfifo_wm_thrd[4:0]时，reg_rxfifo_wm_int_raw位将有效。
         */
        uint32_t rxfifo_wm_thrhd:5;
        /** txfifo_wm_thhd:R/W；比特位置：[9:5]；默认值：4；非ifo访问模式下tx FIFO的水位标记阈值。当reg_reg_fifo_prt_en为1且tx fifo计数器小于reg_txfifo_wm_thrd[4:0]时，reg_txfifo_wm_int_raw位将有效。
         */
        uint32_t txfifo_wm_thrhd:5;
        /** nonifo_en:R/W；位位置：[10]；默认值：0；设置此位以启用APB非ifo访问。
         */
        uint32_t nonfifo_en:1;
        /** fifo_addr_cfg_en:R/W；位位置：[11]；默认值：0；当该位设置为1时，在I2C地址字节之后接收的字节表示I2C从RAM中的偏移地址。
         */
        uint32_t fifo_addr_cfg_en:1;
        /** rx_fifo_rst:R/W；位位置：[12]；默认值：0；设置此位以重置rx fifo。
         */
        uint32_t rx_fifo_rst:1;
        /** tx_fifo_rst:R/W；位位置：[13]；默认值：0；设置此位以重置tx fifo。
         */
        uint32_t tx_fifo_rst:1;
        /** fifo_prt_en:R/W；位位置：[14]；默认值：1；非FIFO访问模式下FIFO指针的控制启用位。此位控制tx/rx_fifo溢出、下溢、满和空的有效位和中断。
         */
        uint32_t fifo_prt_en:1;
        uint32_t reserved_15:17;
    };
    uint32_t val;
} i2c_fifo_conf_reg_t;

/** filter_cfg寄存器SCL和SDA滤波器配置寄存器的类型
 */
typedef union {
    struct {
        /** scl_filter_threes:R/W；位位置：[3:0]；默认值：0；当SCL输入上的脉冲在I2C模块时钟周期中的宽度小于该寄存器值时，I2C控制器将忽略该脉冲。
         */
        uint32_t scl_filter_thres:4;
        /** sda_filter_threes:R/W；位位置：[7:4]；默认值：0；当SDA输入上的脉冲在I2C模块时钟周期中的宽度小于该寄存器值时，I2C控制器将忽略该脉冲。
         */
        uint32_t sda_filter_thres:4;
        /** scl_filter_en:R/W；位位置：[8]；默认值：1；这是SCL的筛选器启用位。
         */
        uint32_t scl_filter_en:1;
        /** sda_filter_en:R/W；位位置：[9]；默认值：1；这是SDA的过滤器启用位。
         */
        uint32_t sda_filter_en:1;
        uint32_t reserved_10:22;
    };
    uint32_t val;
} i2c_filter_cfg_reg_t;

/** clk_conf寄存器类型I2C clk配置寄存器
 */
typedef union {
    struct {
        /** sclk_div_num:R/W；位位置：[7:0]；默认值：0；i2c模的分数除数的积分部分
         */
        uint32_t sclk_div_num:8;
        /** sclk_div_a:R/W；比特位置：[13:8]；默认值：0；i2c模的分数除数的分数部分的分子
         */
        uint32_t sclk_div_a:6;
        /** sclk_div_b:R/W；比特位置：[19:14]；默认值：0；i2c模的分数除数的分数部分的分母
         */
        uint32_t sclk_div_b:6;
        /** sclk_sel:R/W；位位置：[20]；默认值：0；i2c模块的时钟选择：0-XTAL；1-CLK_8MHz。
         */
        uint32_t sclk_sel:1;
        /** sclk_active:R/W；位位置：[21]；默认值：1；i2c模块的时钟开关
         */
        uint32_t sclk_active:1;
        uint32_t reserved_22:10;
    };
    uint32_t val;
} i2c_clk_conf_reg_t;

/** scl_sp_conf寄存器的类型电源配置寄存器
 */
typedef union {
    struct {
        /** scl_rst_slv_en:R/W/SC；位位置：[0]；默认值：0；当I2C主机为空闲时，设置此位以发送SCL脉冲。脉冲数等于reg_scl_rst_slv_num[4:0]。
         */
        uint32_t scl_rst_slv_en:1;
        /** scl_rst_slv_num:R/W；比特位置：[5:1]；默认值：0；配置I2C主模式下生成的SCL脉冲。当reg_scl_rst_slv_en为1时有效。
         */
        uint32_t scl_rst_slv_num:5;
        /** scl_pd_en:R/W；位位置：[6]；默认值：0；I2C输出SCL线的断电启用位。1： 关闭电源。0：未断电。将reg_scl_force_out和reg_scl_pd_en设置为1以将scl拉低。
         */
        uint32_t scl_pd_en:1;
        /** sda_d_en:R/W；位位置：[7]；默认值：0；I2C输出SDA线的断电启用位。1： 关闭电源。0：未断电。将reg_sda_force_out和reg_sda_pd_en设置为1以将sda拉低。
         */
        uint32_t sda_pd_en:1;
        uint32_t reserved_8:24;
    };
    uint32_t val;
} i2c_scl_sp_conf_reg_t;

/** scl_stretch_conf寄存器类型设置I2C从设备的scl拉伸
 */
typedef union {
    struct {
        /** 拉伸_保护_数量：R/W；位位置：[9:0]；默认值：0；配置I2C从机拉伸SCL线的周期。
         */
        uint32_t stretch_protect_num:10;
        /** slave_scl_stretch_en:R/W；位位置：[10]；默认值：0；从属SCL拉伸功能的启用位。1： 启用。0：禁用。当reg_slave_SCL_stretch_en为1并且发生拉伸事件时，SCL输出线将拉伸为低。在reg_stretch_cause中可以看到拉伸原因。
         */
        uint32_t slave_scl_stretch_en:1;
        /** slave_scl_stretch_clr:WT；位位置：[11]；默认值：0；设置此位以清除I2C从属SCL拉伸功能。
         */
        uint32_t slave_scl_stretch_clr:1;
        /** slave_byte_ack_ctl_en:R/W；位位置：[12]；默认值：0；从站控制ACK电平功能的启用位。
         */
        uint32_t slave_byte_ack_ctl_en:1;
        /** slave_byte_ack_lvl:R/W；位位置：[13]；默认值：0；启用从属控制ACK级别功能时设置ACK级别。
         */
        uint32_t slave_byte_ack_lvl:1;
        uint32_t reserved_14:18;
    };
    uint32_t val;
} i2c_scl_stretch_conf_reg_t;


/**组：状态寄存器*/
/** sr寄存器类型描述I2C工作状态。
 */
typedef union {
    struct {
        /** resp_rec:RO；位位置：[0]；默认值：0；在主模式或从模式下接收的ACK值。0:ACK，1:NACK。
         */
        uint32_t resp_rec:1;
        /** slave_rw:RO；位位置：[1]；默认值：0；当处于从属模式时，1：主设备从从属设备读取；0：主设备写入从设备。
         */
        uint32_t slave_rw:1;
        uint32_t reserved_2:1;
        /** arb_list:RO；位位置：[3]；默认值：0；当I2C控制器失去对SCL线的控制时，此寄存器变为1。
         */
        uint32_t arb_lost:1;
        /** bus_busy:RO；位位置：[4]；默认值：0；1： I2C总线忙于传输数据；0：I2C总线处于空闲状态。
         */
        uint32_t bus_busy:1;
        /** 从属地址：RO；位位置：[5]；默认值：0；当配置为I2C从设备时，主设备发送的地址等于从设备的地址，则该位将为高电平。
         */
        uint32_t slave_addressed:1;
        uint32_t reserved_6:2;
        /** rxifo_cnt:RO；比特位置：[13:8]；默认值：0；此字段表示需要发送的数据量。
         */
        uint32_t rxfifo_cnt:6;
        /** 拉伸_使用：RO；比特位置：[15:14]；默认值：3；在从属模式下拉伸SCL低的原因。0：在I2C读取数据状态开始时将SCL拉伸为低。1： 当I2C Tx FIFO在从属模式中为空时，将SCL拉伸为低。2： 当I2C Rx FIFO在从属模式中满时，将SCL拉伸为低。
         */
        uint32_t stretch_cause:2;
        uint32_t reserved_16:2;
        /** txfifo_cnt:RO；比特位置：[23:18]；默认值：0；该字段将接收的数据量存储在RAM中。
         */
        uint32_t txfifo_cnt:6;
        /** scl_main_state_last:RO；比特位置：[26:24]；默认值：0；此字段指示I2C模块状态机的状态。0：空闲；1： 地址移位；2： ACK地址；3： Rx数据；4： Tx数据；5： 发送ACK；6： 等待ACK
         */
        uint32_t scl_main_state_last:3;
        uint32_t reserved_27:1;
        /** scl_state_last:RO；位位置：[30:28]；默认值：0；此字段指示用于生成SCL的状态机的状态。0：空闲；1： 启动；2： 负边缘；3： 低；4： 正边缘；5： 高；6： 停止
         */
        uint32_t scl_state_last:3;
        uint32_t reserved_31:1;
    };
    uint32_t val;
} i2c_sr_reg_t;

/** fifo_st寄存器fifo状态寄存器的类型。
 */
typedef union {
    struct {
        /** rxfifo_raddr:RO；位位置：[4:0]；默认值：0；这是从rxfifo读取的APB的偏移地址
         */
        uint32_t rxfifo_raddr:5;
        /** rxifo_addr:RO；比特位置：[9:5]；默认值：0；这是i2c模块接收数据并写入rxfifo的偏移地址。
         */
        uint32_t rxfifo_waddr:5;
        /** txfifo_reddr:RO；比特位置：[14:10]；默认值：0；这是从txfifo读取的i2c模块的偏移地址。
         */
        uint32_t txfifo_raddr:5;
        /** txfifo_addr:RO；比特位置：[19:15]；默认值：0；这是写入txfifo的APB总线的偏移地址。
         */
        uint32_t txfifo_waddr:5;
        uint32_t reserved_20:2;
        /** slave_rw_point:RO；位位置：[29:22]；默认值：0；I2C从属模式下的接收数据。
         */
        uint32_t slave_rw_point:8;
        uint32_t reserved_30:2;
    };
    uint32_t val;
} i2c_fifo_st_reg_t;

/** 数据寄存器Rx FIFO读取数据的类型。
 */
typedef union {
    struct {
        /** fifo_data：反渗透；位位置：[7:0]；默认值：0；rx FIFO读取数据的值。
         */
        uint32_t fifo_rdata:8;
        uint32_t reserved_8:24;
    };
    uint32_t val;
} i2c_data_reg_t;


/**组：中断寄存器*/
/** int_raw寄存器的类型原始中断状态
 */
typedef union {
    struct {
        /** rxifo_wm_int_raw:R/SS/WTC；位位置：[0]；默认值：0；I2C_RXFIFO_WM_INT中断的原始中断位。
         */
        uint32_t rxfifo_wm_int_raw:1;
        /** txfifo_wm_int_raw:R/SS/WTC；位位置：[1]；默认值：1；I2C_TXFIFO_WM_INT中断的原始中断位。
         */
        uint32_t txfifo_wm_int_raw:1;
        /** rxfifo_ovf_int_raw:R/SS/WTC；位位置：[2]；默认值：0；I2C_RXFIFO_OVF_INT中断的原始中断位。
         */
        uint32_t rxfifo_ovf_int_raw:1;
        /** end_detect_int_raw:R/SS/WTC；位位置：[3]；默认值：0；I2C_END_DETECT_INT中断的原始中断位。
         */
        uint32_t end_detect_int_raw:1;
        /** 字节trans_done_int_raw:R/SS/WTC；位位置：[4]；默认值：0；I2C_END_DETECT_INT中断的原始中断位。
         */
        uint32_t byte_trans_done_int_raw:1;
        /** arbitation_lost_int_raw:R/SS/WTC；位位置：[5]；默认值：0；I2C_ARBITRATION_LOST_INT中断的原始中断位。
         */
        uint32_t arbitration_lost_int_raw:1;
        /** mst_xfifo_udf_int_raw:R/SS/WTC；位位置：[6]；默认值：0；I2C_TRANS_COMPLETE_INT中断的原始中断位。
         */
        uint32_t mst_txfifo_udf_int_raw:1;
        /** trans_complete_int_raw:R/SS/WTC；位位置：[7]；默认值：0；I2C_TRANS_COMPLETE_INT中断的原始中断位。
         */
        uint32_t trans_complete_int_raw:1;
        /** time_out_int_raw:R/SS/WTC；位位置：[8]；默认值：0；I2C_TIME_OUT_INT中断的原始中断位。
         */
        uint32_t time_out_int_raw:1;
        /** trans_start_int_raw:R/SS/WTC；位位置：[9]；默认值：0；I2C_TRANS_START_INT中断的原始中断位。
         */
        uint32_t trans_start_int_raw:1;
        /** nack_int_raw:R/SS/WTC；位位置：[10]；默认值：0；I2C_SLAVE_STRETCH_INT中断的原始中断位。
         */
        uint32_t nack_int_raw:1;
        /** txfifo_ovf_int_raw:R/SS/WTC；位位置：[11]；默认值：0；I2C_TXFIFO_OVF_INT中断的原始中断位。
         */
        uint32_t txfifo_ovf_int_raw:1;
        /** rxfifo_udf_int_raw:R/SS/WTC；位位置：[12]；默认值：0；I2C_RXIFO_UDF_INT中断的原始中断位。
         */
        uint32_t rxfifo_udf_int_raw:1;
        /** scl_st_to_int_raw:R/SS/WTC；位位置：[13]；默认值：0；I2C_SCL_ST_TO_INT中断的原始中断位。
         */
        uint32_t scl_st_to_int_raw:1;
        /** scl_main_st_to_int_raw:R/SS/WTC；位位置：[14]；默认值：0；I2C_SCL_MAIN_ST_TO_INT中断的原始中断位。
         */
        uint32_t scl_main_st_to_int_raw:1;
        /** det_start_int_raw:R/SS/WTC；位位置：[15]；默认值：0；I2C_DET_START_INT中断的原始中断位。
         */
        uint32_t det_start_int_raw:1;
        /** slave_strech_int_raw:R/SS/WTC；位位置：[16]；默认值：0；I2C_SLAVE_STRETCH_INT中断的原始中断位。
         */
        uint32_t slave_stretch_int_raw:1;
        /** general_call_int_raw:R/SS/WTC；位位置：[17]；默认值：0；I2C_GENARAL_CALL_INT中断的原始中断位。
         */
        uint32_t general_call_int_raw:1;
        uint32_t reserved_18:14;
    };
    uint32_t val;
} i2c_int_raw_reg_t;

/** int_clr寄存器类型中断清除位
 */
typedef union {
    struct {
        /** rxifo_wm_int_clr:WT；位位置：[0]；默认值：0；设置此位以清除I2C_RXFIFO_WM_INT中断。
         */
        uint32_t rxfifo_wm_int_clr:1;
        /** txfifo_wm_int_clr:WT；位位置：[1]；默认值：0；设置此位以清除I2C_TXFIFO_WM_INT中断。
         */
        uint32_t txfifo_wm_int_clr:1;
        /** rxfifo_ovf_int_clr:WT；位位置：[2]；默认值：0；设置此位以清除I2C_RXFIFO_OVF_INT中断。
         */
        uint32_t rxfifo_ovf_int_clr:1;
        /** end_detect_int_clr:WT；位位置：[3]；默认值：0；设置此位以清除I2C_END_DETECT_INT中断。
         */
        uint32_t end_detect_int_clr:1;
        /** 字节trans_done_int_clr:WT；位位置：[4]；默认值：0；设置此位以清除I2C_END_DETECT_INT中断。
         */
        uint32_t byte_trans_done_int_clr:1;
        /** 仲裁_时间_时间_ clr:WT；位位置：[5]；默认值：0；设置此位以清除I2C_ARBITRATION_LOST_INT中断。
         */
        uint32_t arbitration_lost_int_clr:1;
        /** mst_xfifo_udf_int_clr:WT；位位置：[6]；默认值：0；设置此位以清除I2C_TRANS_COMPLETE_INT中断。
         */
        uint32_t mst_txfifo_udf_int_clr:1;
        /** trans_complete_int_clr:WT；位位置：[7]；默认值：0；设置此位以清除I2C_TRANS_COMPLETE_INT中断。
         */
        uint32_t trans_complete_int_clr:1;
        /** time_out_int_clr:WT；位位置：[8]；默认值：0；设置此位以清除I2C_TIME_OUT_INT中断。
         */
        uint32_t time_out_int_clr:1;
        /** trans_start_int_clr:WT；位位置：[9]；默认值：0；设置此位以清除I2C_TRANS_START_INT中断。
         */
        uint32_t trans_start_int_clr:1;
        /** nack_int_clr:WT；位位置：[10]；默认值：0；设置此位以清除I2C_SLAVE_STRETCH_INT中断。
         */
        uint32_t nack_int_clr:1;
        /** txfifo_ovf_int_clr:WT；位位置：[11]；默认值：0；设置此位以清除I2C_TXFIFO_OVF_INT中断。
         */
        uint32_t txfifo_ovf_int_clr:1;
        /** rxfix_udf_int_clr:WT；位位置：[12]；默认值：0；设置此位以清除I2C_RXFIFO_UFD_INT中断。
         */
        uint32_t rxfifo_udf_int_clr:1;
        /** scl_st_to_int_clr:WT；位位置：[13]；默认值：0；设置此位以清除I2C_SCL_ST_to_INT中断。
         */
        uint32_t scl_st_to_int_clr:1;
        /** scl_main_st_to_int_clr:WT；位位置：[14]；默认值：0；设置此位以清除I2C_SCL_MAIN_ST_to_INT中断。
         */
        uint32_t scl_main_st_to_int_clr:1;
        /** det_start_int_clr:WT；位位置：[15]；默认值：0；设置此位以清除I2C_DET_START_INT中断。
         */
        uint32_t det_start_int_clr:1;
        /** slave_surch_int_clr:WT；位位置：[16]；默认值：0；设置此位以清除I2C_SLAVE_STRETCH_INT中断。
         */
        uint32_t slave_stretch_int_clr:1;
        /** general_call_int_clr:WT；位位置：[17]；默认值：0；为I2C_GENARAL_CALL_INT中断设置此位。
         */
        uint32_t general_call_int_clr:1;
        uint32_t reserved_18:14;
    };
    uint32_t val;
} i2c_int_clr_reg_t;

/** int_ena寄存器中断启用位的类型
 */
typedef union {
    struct {
        /** rxifo_wm_int_ena:R/W；位位置：[0]；默认值：0；I2C_RXFIFO_WM_INT中断的中断启用位。
         */
        uint32_t rxfifo_wm_int_ena:1;
        /** txfifo_wm_int_ena:R/W；位位置：[1]；默认值：0；I2C_TXFIFO_WM_INT中断的中断启用位。
         */
        uint32_t txfifo_wm_int_ena:1;
        /** rxfifo_ovf_int_ena:R/W；位位置：[2]；默认值：0；I2C_RXFIFO_OVF_INT中断的中断启用位。
         */
        uint32_t rxfifo_ovf_int_ena:1;
        /** end_detect_int_ena:R/W；位位置：[3]；默认值：0；I2C_END_DETECT_INT中断的中断启用位。
         */
        uint32_t end_detect_int_ena:1;
        /** 字节trans_done_int_ena:R/W；位位置：[4]；默认值：0；I2C_END_DETECT_INT中断的中断启用位。
         */
        uint32_t byte_trans_done_int_ena:1;
        /** 仲裁_停止_退出：R/W；位位置：[5]；默认值：0；I2C_ARBITRATION_LOST_INT中断的中断启用位。
         */
        uint32_t arbitration_lost_int_ena:1;
        /** mst_tfifo_udf-int_ena:R/W；位位置：[6]；默认值：0；I2C_TRANS_COMPLETE_INT中断的中断启用位。
         */
        uint32_t mst_txfifo_udf_int_ena:1;
        /** trans_complete_int_ena:R/W；位位置：[7]；默认值：0；I2C_TRANS_COMPLETE_INT中断的中断启用位。
         */
        uint32_t trans_complete_int_ena:1;
        /** time_out_int_ena:R/W；位位置：[8]；默认值：0；I2C_TIME_OUT_INT中断的中断启用位。
         */
        uint32_t time_out_int_ena:1;
        /** trans_start_int_ena:R/W；位位置：[9]；默认值：0；I2C_TRANS_START_INT中断的中断启用位。
         */
        uint32_t trans_start_int_ena:1;
        /** nack_int_ena:R/W；位位置：[10]；默认值：0；I2C_SLAVE_STRETCH_INT中断的中断启用位。
         */
        uint32_t nack_int_ena:1;
        /** txfifo_ovf_int_ena:R/W；位位置：[11]；默认值：0；I2C_TXFIFO_OVF_INT中断的中断启用位。
         */
        uint32_t txfifo_ovf_int_ena:1;
        /** rxifo_udf_int_ena:R/W；位位置：[12]；默认值：0；I2C_RXIFO_UDF_INT中断的中断启用位。
         */
        uint32_t rxfifo_udf_int_ena:1;
        /** scl_st_to_int_ena:R/W；位位置：[13]；默认值：0；I2C_SCL_ST_TO_INT中断的中断启用位。
         */
        uint32_t scl_st_to_int_ena:1;
        /** scl_main_st_to_int_ena:R/W；位位置：[14]；默认值：0；I2C_SCL_MAIN_ST_TO_INT中断的中断启用位。
         */
        uint32_t scl_main_st_to_int_ena:1;
        /** det_start_int_ena:R/W；位位置：[15]；默认值：0；I2C_DET_START_INT中断的中断启用位。
         */
        uint32_t det_start_int_ena:1;
        /** slave_surch_int_ena:R/W；位位置：[16]；默认值：0；I2C_SLAVE_STRETCH_INT中断的中断启用位。
         */
        uint32_t slave_stretch_int_ena:1;
        /** general_call_int_ena:R/W；位位置：[17]；默认值：0；I2C_GENARAL_CALL_INT中断的中断启用位。
         */
        uint32_t general_call_int_ena:1;
        uint32_t reserved_18:14;
    };
    uint32_t val;
} i2c_int_ena_reg_t;

/** int_status寄存器类型捕获的I2C通信事件的状态
 */
typedef union {
    struct {
        /** rxifo_wm_int_st:RO；位位置：[0]；默认值：0；I2C_RXFIFO_WM_INT中断的屏蔽中断状态位。
         */
        uint32_t rxfifo_wm_int_st:1;
        /** txfifo_wm_int_st:RO；位位置：[1]；默认值：0；I2C_TXFIFO_WM_INT中断的屏蔽中断状态位。
         */
        uint32_t txfifo_wm_int_st:1;
        /** rxfifo_ovf_int_st:RO；位位置：[2]；默认值：0；I2C_RXFIFO_OVF_INT中断的屏蔽中断状态位。
         */
        uint32_t rxfifo_ovf_int_st:1;
        /** end_detect_int_st:RO；位位置：[3]；默认值：0；I2C_END_DETECT_INT中断的屏蔽中断状态位。
         */
        uint32_t end_detect_int_st:1;
        /** 字节trans_done_int_st:RO；位位置：[4]；默认值：0；I2C_END_DETECT_INT中断的屏蔽中断状态位。
         */
        uint32_t byte_trans_done_int_st:1;
        /** 仲裁_列表_列表：RO；位位置：[5]；默认值：0；I2C_ARBITRATION_LOST_INT中断的屏蔽中断状态位。
         */
        uint32_t arbitration_lost_int_st:1;
        /** mst_xfifo_udf_int_st:RO；位位置：[6]；默认值：0；I2C_TRANS_COMPLETE_INT中断的屏蔽中断状态位。
         */
        uint32_t mst_txfifo_udf_int_st:1;
        /** trans_complete_int_st:RO；位位置：[7]；默认值：0；I2C_TRANS_COMPLETE_INT中断的屏蔽中断状态位。
         */
        uint32_t trans_complete_int_st:1;
        /** time_out_int_st:RO；位位置：[8]；默认值：0；I2C_TIME_OUT_INT中断的屏蔽中断状态位。
         */
        uint32_t time_out_int_st:1;
        /** trans_start_int_st:RO；位位置：[9]；默认值：0；I2C_TRANS_START_INT中断的屏蔽中断状态位。
         */
        uint32_t trans_start_int_st:1;
        /** nack_int_st:RO；位位置：[10]；默认值：0；I2C_SLAVE_STRETCH_INT中断的屏蔽中断状态位。
         */
        uint32_t nack_int_st:1;
        /** txfifo_ovf_int_st:RO；位位置：[11]；默认值：0；I2C_TXFIFO_OVF_INT中断的屏蔽中断状态位。
         */
        uint32_t txfifo_ovf_int_st:1;
        /** rxifo_udf_int_st:RO；位位置：[12]；默认值：0；I2C_RXIFO_UDF_INT中断的屏蔽中断状态位。
         */
        uint32_t rxfifo_udf_int_st:1;
        /** scl_st_to_int_st:RO；位位置：[13]；默认值：0；I2C_SCL_ST_TO_INT中断的屏蔽中断状态位。
         */
        uint32_t scl_st_to_int_st:1;
        /** scl_main_st_to_int_st:RO；位位置：[14]；默认值：0；I2C_SCL_MAIN_ST_TO_INT中断的屏蔽中断状态位。
         */
        uint32_t scl_main_st_to_int_st:1;
        /** det_start_int_st:RO；位位置：[15]；默认值：0；I2C_DET_START_INT中断的屏蔽中断状态位。
         */
        uint32_t det_start_int_st:1;
        /** slave_stch_int_st:RO；位位置：[16]；默认值：0；I2C_SLAVE_STRETCH_INT中断的屏蔽中断状态位。
         */
        uint32_t slave_stretch_int_st:1;
        /** general_call_int_st:RO；位位置：[17]；默认值：0；I2C_GENARAL_CALL_INT中断的屏蔽中断状态位。
         */
        uint32_t general_call_int_st:1;
        uint32_t reserved_18:14;
    };
    uint32_t val;
} i2c_int_status_reg_t;


/**组：命令寄存器*/
/** comd0寄存器类型I2C命令寄存器0
 */
typedef union {
    struct {
        /** command0:R/W；比特位置：[13:0]；默认值：0；这是命令0的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command0:14;
        uint32_t reserved_14:17;
        /** command0_done:R/W/SS；位位置：[31]；默认值：0；在I2C主模式下执行命令0时，该位变为高电平。
         */
        uint32_t command0_done:1;
    };
    uint32_t val;
} i2c_comd0_reg_t;

/** comd1寄存器类型I2C命令寄存器1
 */
typedef union {
    struct {
        /** 命令1:R/W；比特位置：[13:0]；默认值：0；这是命令1的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command1:14;
        uint32_t reserved_14:17;
        /** command1_done:R/W/SS；位位置：[31]；默认值：0；当命令1在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command1_done:1;
    };
    uint32_t val;
} i2c_comd1_reg_t;

/** comd2寄存器类型I2C命令寄存器2
 */
typedef union {
    struct {
        /** 命令2:R/W；比特位置：[13:0]；默认值：0；这是命令2的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command2:14;
        uint32_t reserved_14:17;
        /** command2_done:R/W/SS；位位置：[31]；默认值：0；当命令2在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command2_done:1;
    };
    uint32_t val;
} i2c_comd2_reg_t;

/** comd3寄存器类型I2C命令寄存器3
 */
typedef union {
    struct {
        /** 命令3:R/W；比特位置：[13:0]；默认值：0；这是命令3的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command3:14;
        uint32_t reserved_14:17;
        /** command3_done:R/W/SS；位位置：[31]；默认值：0；当命令3在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command3_done:1;
    };
    uint32_t val;
} i2c_comd3_reg_t;

/** comd4寄存器类型I2C命令寄存器4
 */
typedef union {
    struct {
        /** 命令4:R/W；比特位置：[13:0]；默认值：0；这是命令4的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command4:14;
        uint32_t reserved_14:17;
        /** command4_done:R/W/SS；位位置：[31]；默认值：0；当命令4在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command4_done:1;
    };
    uint32_t val;
} i2c_comd4_reg_t;

/** comd5寄存器类型I2C命令寄存器5
 */
typedef union {
    struct {
        /** 命令5:R/W；比特位置：[13:0]；默认值：0；这是命令5的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command5:14;
        uint32_t reserved_14:17;
        /** command5_done:R/W/SS；位位置：[31]；默认值：0；当命令5在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command5_done:1;
    };
    uint32_t val;
} i2c_comd5_reg_t;

/** comd6寄存器类型I2C命令寄存器6
 */
typedef union {
    struct {
        /** 命令6:R/W；比特位置：[13:0]；默认值：0；这是命令6的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command6:14;
        uint32_t reserved_14:17;
        /** command6_done:R/W/SS；位位置：[31]；默认值：0；当命令6在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command6_done:1;
    };
    uint32_t val;
} i2c_comd6_reg_t;

/** comd7寄存器类型I2C命令寄存器7
 */
typedef union {
    struct {
        /** 命令7:R/W；比特位置：[13:0]；默认值：0；这是命令7的内容。它由三部分组成：op_code是命令，0:RSTART；1： 写入；2： 阅读；3： 停止；4： 结束。Byte_num表示需要发送或接收的字节数。eck_en、ack_exp和ack用于控制ack比特。有关详细信息，请参阅I2C cmd结构。
         */
        uint32_t command7:14;
        uint32_t reserved_14:17;
        /** command7_done:R/W/SS；位位置：[31]；默认值：0；当命令7在I2C主模式下完成时，该位变为高电平。
         */
        uint32_t command7_done:1;
    };
    uint32_t val;
} i2c_comd7_reg_t;


/**组：版本寄存器*/
/** 日期寄存器类型版本寄存器
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：537330177；这是版本寄存器。
         */
        uint32_t date:32;
    };
    uint32_t val;
} i2c_date_reg_t;


/**组：地址寄存器*/
/** txfifo_start_addr寄存器类型I2C txfifo基地址寄存器
 */
typedef union {
    struct {
        /** txfifo_start_addr:RO；位位置：[31:0]；默认值：0；这是I2C txfifo的第一个地址。
         */
        uint32_t txfifo_start_addr:32;
    };
    uint32_t val;
} i2c_txfifo_start_addr_reg_t;

/** rxfifo_start_addr寄存器I2C rxfifo基址寄存器的类型
 */
typedef union {
    struct {
        /** rxifo_start_addr:RO；位位置：[31:0]；默认值：0；这是I2C rxfifo的第一个地址。
         */
        uint32_t rxfifo_start_addr:32;
    };
    uint32_t val;
} i2c_rxfifo_start_addr_reg_t;


typedef struct {
    volatile i2c_scl_low_period_reg_t scl_low_period;
    volatile i2c_ctr_reg_t ctr;
    volatile i2c_sr_reg_t sr;
    volatile i2c_to_reg_t to;
    volatile i2c_slave_addr_reg_t slave_addr;
    volatile i2c_fifo_st_reg_t fifo_st;
    volatile i2c_fifo_conf_reg_t fifo_conf;
    volatile i2c_data_reg_t data;
    volatile i2c_int_raw_reg_t int_raw;
    volatile i2c_int_clr_reg_t int_clr;
    volatile i2c_int_ena_reg_t int_ena;
    volatile i2c_int_status_reg_t int_status;
    volatile i2c_sda_hold_reg_t sda_hold;
    volatile i2c_sda_sample_reg_t sda_sample;
    volatile i2c_scl_high_period_reg_t scl_high_period;
    uint32_t reserved_03c;
    volatile i2c_scl_start_hold_reg_t scl_start_hold;
    volatile i2c_scl_rstart_setup_reg_t scl_rstart_setup;
    volatile i2c_scl_stop_hold_reg_t scl_stop_hold;
    volatile i2c_scl_stop_setup_reg_t scl_stop_setup;
    volatile i2c_filter_cfg_reg_t filter_cfg;
    volatile i2c_clk_conf_reg_t clk_conf;
    volatile i2c_comd0_reg_t comd0;
    volatile i2c_comd1_reg_t comd1;
    volatile i2c_comd2_reg_t comd2;
    volatile i2c_comd3_reg_t comd3;
    volatile i2c_comd4_reg_t comd4;
    volatile i2c_comd5_reg_t comd5;
    volatile i2c_comd6_reg_t comd6;
    volatile i2c_comd7_reg_t comd7;
    volatile i2c_scl_st_time_out_reg_t scl_st_time_out;
    volatile i2c_scl_main_st_time_out_reg_t scl_main_st_time_out;
    volatile i2c_scl_sp_conf_reg_t scl_sp_conf;
    volatile i2c_scl_stretch_conf_reg_t scl_stretch_conf;
    uint32_t reserved_088[28];
    volatile i2c_date_reg_t date;
    uint32_t reserved_0fc;
    volatile i2c_txfifo_start_addr_reg_t txfifo_start_addr;
    uint32_t reserved_104[31];
    volatile i2c_rxfifo_start_addr_reg_t rxfifo_start_addr;
} i2c_dev_t;

extern i2c_dev_t I2C0;
extern i2c_dev_t I2C1;

#ifndef __cplusplus
_Static_assert(sizeof(i2c_dev_t) == 0x184, "Invalid size of i2c_dev_t structure");
#endif

#ifdef __cplusplus
}
#endif

