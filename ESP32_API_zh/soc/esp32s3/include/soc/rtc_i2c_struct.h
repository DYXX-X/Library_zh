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
#ifdef __cplusplus
extern "C" {
#endif

/**组：配置寄存器*/
/** i2c_scl_low寄存器类型配置低scl周期
 */
typedef union {
    struct {
        /** i2c_scl_low_period_reg:R/W；比特位置：[19:0]；默认值：256；scl=0的时间段
         */
        uint32_t i2c_scl_low_period_reg:20;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} rtc_i2c_scl_low_reg_t;

/** i2c_ctrl寄存器类型配置i2c-ctrl
 */
typedef union {
    struct {
        /** i2c_sda_frce_out:R/W；位位置：[0]；默认值：0；1=推拉式，0=开放式排水
         */
        uint32_t i2c_sda_force_out:1;
        /** i2c_scl_force_out:R/W；位位置：[1]；默认值：0；1=推拉式，0=开放式排水
         */
        uint32_t i2c_scl_force_out:1;
        /** i2c_ms_mode:R/W；位位置：[2]；默认值：0；1=主，0=从
         */
        uint32_t i2c_ms_mode:1;
        /** i2c_trans_start:R/W；位位置：[3]；默认值：0；强制启动
         */
        uint32_t i2c_trans_start:1;
        /** i2c_tx_lsb_first:R/W；位位置：[4]；默认值：0；先通过lsb
         */
        uint32_t i2c_tx_lsb_first:1;
        /** i2c_rx_lsb_first:R/W；位位置：[5]；默认值：0；首先接收lsb
         */
        uint32_t i2c_rx_lsb_first:1;
        uint32_t reserved_6:23;
        /** i2c_i2c_ctrl_clk_gate_en:R/W；位位置：[29]；默认值：0；配置i2c ctrl clk启用
         */
        uint32_t i2c_i2c_ctrl_clk_gate_en:1;
        /** i2c_i2c_reset:R/W；位位置：[30]；默认值：0；rtc i2c开关复位
         */
        uint32_t i2c_i2c_reset:1;
        /** i2c_i2cclk_en:R/W；位位置：[31]；默认值：0；rtc i2c reg clk门控
         */
        uint32_t i2c_i2cclk_en:1;
    };
    uint32_t val;
} rtc_i2c_ctrl_reg_t;

/** i2c_to寄存器配置超时的类型
 */
typedef union {
    struct {
        /** i2c_time_out_reg:R/W；比特位置：[19:0]；默认值：65536；超时阈值
         */
        uint32_t i2c_time_out_reg:20;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} rtc_i2c_to_reg_t;

/** i2c_slave_addr寄存器类型配置从属id
 */
typedef union {
    struct {
        /** i2c_slave_addr:R/W；位位置：[14:0]；默认值：0；从属地址
         */
        uint32_t i2c_slave_addr:15;
        uint32_t reserved_15:16;
        /** i2c_addr_10bit_en:R/W；位位置：[31]；默认值：0；i2c 10位模式启用
         */
        uint32_t i2c_addr_10bit_en:1;
    };
    uint32_t val;
} rtc_i2c_slave_addr_reg_t;

/** i2c_scl_high寄存器类型配置高scl周期
 */
typedef union {
    struct {
        /** i2c_scl_high_period_reg:R/W；比特位置：[19:0]；默认值：256；scl=1的时间段
         */
        uint32_t i2c_scl_high_period_reg:20;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} rtc_i2c_scl_high_reg_t;

/** i2c_sda_duty寄存器类型配置sda负载
 */
typedef union {
    struct {
        /** i2c_sda_duty_num：R/W；比特位置：[19:0]；默认值：16；SCL变低后SDA切换的时间段
         */
        uint32_t i2c_sda_duty_num:20;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} rtc_i2c_sda_duty_reg_t;

/** i2c_scl_start_period寄存器类型配置scl启动周期
 */
typedef union {
    struct {
        /** i2c_scl_start_period:R/W；比特位置：[19:0]；默认值：8；触发I2C启动后SCL切换的时间段
         */
        uint32_t i2c_scl_start_period:20;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} rtc_i2c_scl_start_period_reg_t;

/** i2c_scl_stop_period寄存器类型配置scl停止周期
 */
typedef union {
    struct {
        /** i2c_scl_stop_period:R/W；比特位置：[19:0]；默认值：8；触发I2C结束后SCL停止的时间段
         */
        uint32_t i2c_scl_stop_period:20;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} rtc_i2c_scl_stop_period_reg_t;

/** i2c_data寄存器类型获取i2c数据状态
 */
typedef union {
    struct {
        /** i2c_i2c_rdata:RO；位位置：[7:0]；默认值：0；收到的数据
         */
        uint32_t i2c_i2c_rdata:8;
        /** i2c_slave_tx_data:R/W；比特位置：[15:8]；默认值：0；从设备发送的数据
         */
        uint32_t i2c_slave_tx_data:8;
        uint32_t reserved_16:15;
        /** i2c_i2c_done:RO；位位置：[31]；默认值：0；i2c完成
         */
        uint32_t i2c_i2c_done:1;
    };
    uint32_t val;
} rtc_i2c_data_reg_t;

/** i2c_cmd0寄存器的类型i2c commond0寄存器
 */
typedef union {
    struct {
        /** i2c_command0:R/W；比特位置：[13:0]；默认值：2307；命令0
         */
        uint32_t i2c_command0:14;
        uint32_t reserved_14:17;
        /** i2c_command0_done:RO；位位置：[31]；默认值：0；命令_已完成
         */
        uint32_t i2c_command0_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd0_reg_t;

/** i2c_cmd1寄存器的类型i2c common1寄存器
 */
typedef union {
    struct {
        /** i2c_command1:R/W；比特位置：[13:0]；默认值：6401；命令1
         */
        uint32_t i2c_command1:14;
        uint32_t reserved_14:17;
        /** i2c_command1_done:RO；位位置：[31]；默认值：0；命令1_已完成
         */
        uint32_t i2c_command1_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd1_reg_t;

/** i2c_cmd2寄存器的类型i2c common2寄存器
 */
typedef union {
    struct {
        /** i2c_command2:R/W；比特位置：[13:0]；默认值：2306；命令2
         */
        uint32_t i2c_command2:14;
        uint32_t reserved_14:17;
        /** i2c_command2_done:RO；位位置：[31]；默认值：0；命令2_done
         */
        uint32_t i2c_command2_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd2_reg_t;

/** i2c_cmd3寄存器的类型i2c common3寄存器
 */
typedef union {
    struct {
        /** i2c_command3:R/W；比特位置：[13:0]；默认值：257；命令3
         */
        uint32_t i2c_command3:14;
        uint32_t reserved_14:17;
        /** i2c_command3_done:RO；位位置：[31]；默认值：0；命令3_done
         */
        uint32_t i2c_command3_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd3_reg_t;

/** i2c_cmd4寄存器的类型i2c common4寄存器
 */
typedef union {
    struct {
        /** i2c_command4:R/W；比特位置：[13:0]；默认值：2305；命令4
         */
        uint32_t i2c_command4:14;
        uint32_t reserved_14:17;
        /** i2c_command4_done:RO；位位置：[31]；默认值：0；命令4_done
         */
        uint32_t i2c_command4_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd4_reg_t;

/** i2c_cmd5寄存器类型i2c commond5_register
 */
typedef union {
    struct {
        /** i2c_command5:R/W；比特位置：[13:0]；默认值：5889；命令5
         */
        uint32_t i2c_command5:14;
        uint32_t reserved_14:17;
        /** i2c_command5_done:RO；位位置：[31]；默认值：0；命令5_done
         */
        uint32_t i2c_command5_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd5_reg_t;

/** i2c_cmd6寄存器的类型i2c-commond6寄存器
 */
typedef union {
    struct {
        /** i2c_command6:R/W；比特位置：[13:0]；默认值：6401；命令6
         */
        uint32_t i2c_command6:14;
        uint32_t reserved_14:17;
        /** i2c_command6_done:RO；位位置：[31]；默认值：0；命令6_done
         */
        uint32_t i2c_command6_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd6_reg_t;

/** i2c_cmd7寄存器的类型i2c-commond7寄存器
 */
typedef union {
    struct {
        /** i2c_command7:R/W；比特位置：[13:0]；默认值：2308；命令7
         */
        uint32_t i2c_command7:14;
        uint32_t reserved_14:17;
        /** i2c_command7_done:RO；位位置：[31]；默认值：0；命令7_done
         */
        uint32_t i2c_command7_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd7_reg_t;

/** i2c_cmd8寄存器的类型i2c commond8寄存器
 */
typedef union {
    struct {
        /** i2c_command8:R/W；比特位置：[13:0]；默认值：6401；命令8
         */
        uint32_t i2c_command8:14;
        uint32_t reserved_14:17;
        /** i2c_command8_done:RO；位位置：[31]；默认值：0；命令8_done
         */
        uint32_t i2c_command8_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd8_reg_t;

/** i2c_cmd9寄存器的类型i2c-commond9寄存器
 */
typedef union {
    struct {
        /** i2c_command9:R/W；比特位置：[13:0]；默认值：2307；命令9
         */
        uint32_t i2c_command9:14;
        uint32_t reserved_14:17;
        /** i2c_command9_done:RO；位位置：[31]；默认值：0；命令9_done
         */
        uint32_t i2c_command9_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd9_reg_t;

/** i2c_cmd10寄存器的类型i2c commond10寄存器
 */
typedef union {
    struct {
        /** i2c_command10:R/W；比特位置：[13:0]；默认值：257；命令10
         */
        uint32_t i2c_command10:14;
        uint32_t reserved_14:17;
        /** i2c_command10_done:RO；位位置：[31]；默认值：0；命令10_done
         */
        uint32_t i2c_command10_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd10_reg_t;

/** i2c_cmd11寄存器的类型i2c commond11寄存器
 */
typedef union {
    struct {
        /** i2c_command11:R/W；比特位置：[13:0]；默认值：2305；命令11
         */
        uint32_t i2c_command11:14;
        uint32_t reserved_14:17;
        /** i2c_command11_done:RO；位位置：[31]；默认值：0；命令11_done
         */
        uint32_t i2c_command11_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd11_reg_t;

/** i2c_cmd12寄存器的类型i2c common12寄存器
 */
typedef union {
    struct {
        /** i2c_command12:R/W；比特位置：[13:0]；默认值：5889；命令12
         */
        uint32_t i2c_command12:14;
        uint32_t reserved_14:17;
        /** i2c_command12_done:RO；位位置：[31]；默认值：0；命令12_done
         */
        uint32_t i2c_command12_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd12_reg_t;

/** i2c_cmd13寄存器的类型i2c commond13寄存器
 */
typedef union {
    struct {
        /** i2c_command13:R/W；比特位置：[13:0]；默认值：6401；命令13
         */
        uint32_t i2c_command13:14;
        uint32_t reserved_14:17;
        /** i2c_command13_done:RO；位位置：[31]；默认值：0；命令13_done
         */
        uint32_t i2c_command13_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd13_reg_t;

/** i2c_cmd14寄存器的类型i2c commond14寄存器
 */
typedef union {
    struct {
        /** i2c_command14:R/W；比特位置：[13:0]；默认值：0；命令14
         */
        uint32_t i2c_command14:14;
        uint32_t reserved_14:17;
        /** i2c_command14_done:RO；位位置：[31]；默认值：0；命令14_done
         */
        uint32_t i2c_command14_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd14_reg_t;

/** i2c_cmd15寄存器的类型i2c commond15寄存器
 */
typedef union {
    struct {
        /** i2c_command15:R/W；比特位置：[13:0]；默认值：0；命令15
         */
        uint32_t i2c_command15:14;
        uint32_t reserved_14:17;
        /** i2c_command15_done:RO；位位置：[31]；默认值：0；命令15_done
         */
        uint32_t i2c_command15_done:1;
    };
    uint32_t val;
} rtc_i2c_cmd15_reg_t;


/**组：状态寄存器*/
/** i2c_status寄存器类型获取i2c状态
 */
typedef union {
    struct {
        /** i2c_ack_rec:RO；位位置：[0]；默认值：0；确认响应
         */
        uint32_t i2c_ack_rec:1;
        /** i2c_slave_rw:RO；位位置：[1]；默认值：0；从读或写
         */
        uint32_t i2c_slave_rw:1;
        /** i2c_arb_list:RO；位位置：[2]；默认值：0；仲裁失败
         */
        uint32_t i2c_arb_lost:1;
        /** i2c_bus_busy:RO；位位置：[3]；默认值：0；公共汽车很忙
         */
        uint32_t i2c_bus_busy:1;
        /** i2c_slave_addressed:RO；位位置：[4]；默认值：0；从属寄存器子地址
         */
        uint32_t i2c_slave_addressed:1;
        /** i2c_byte_trans:RO；位位置：[5]；默认值：0；已完成一字节传输
         */
        uint32_t i2c_byte_trans:1;
        /** i2c_op_cnt:RO；位位置：[7:6]；默认值：0；哪个操作有效
         */
        uint32_t i2c_op_cnt:2;
        uint32_t reserved_8:8;
        /** i2c_shift_reg:RO；比特位置：[23:16]；默认值：0；移位器内容
         */
        uint32_t i2c_shift_reg:8;
        /** i2c_scl_main_state_last:RO；比特位置：[26:24]；默认值：0；i2c最后一个主状态
         */
        uint32_t i2c_scl_main_state_last:3;
        uint32_t reserved_27:1;
        /** i2c_scl_state_last:RO；位位置：[30:28]；默认值：0；scl最后状态
         */
        uint32_t i2c_scl_state_last:3;
        uint32_t reserved_31:1;
    };
    uint32_t val;
} rtc_i2c_status_reg_t;


/**组：中断寄存器*/
/** i2c_int_clr寄存器中断清除寄存器的类型
 */
typedef union {
    struct {
        /** i2c_slave_trans_comp_int_clr:工单；位位置：[0]；默认值：0；清除从属传输完成中断
         */
        uint32_t i2c_slave_tran_comp_int_clr:1;
        /** i2c_arbitation_lost_int_clr:WO；位位置：[1]；默认值：0；清除仲裁丢失中断
         */
        uint32_t i2c_arbitration_lost_int_clr:1;
        /** i2c_master_tran_comp_int_clr:工单；位位置：[2]；默认值：0；清除主传输完成中断
         */
        uint32_t i2c_master_tran_comp_int_clr:1;
        /** i2c_trans_complete_int_clr:工单；位位置：[3]；默认值：0；清除传输完成中断
         */
        uint32_t i2c_trans_complete_int_clr:1;
        /** i2c_time_out_int_clr:工单；位位置：[4]；默认值：0；清除超时中断
         */
        uint32_t i2c_time_out_int_clr:1;
        /** i2c_ack_err_int_clr:工单；位位置：[5]；默认值：0；清除确认错误中断
         */
        uint32_t i2c_ack_err_int_clr:1;
        /** i2c_rx_data_int_clr:工单；位位置：[6]；默认值：0；清除接收数据中断
         */
        uint32_t i2c_rx_data_int_clr:1;
        /** i2c_tx_data_int_clr:工单；位位置：[7]；默认值：0；清除运输装载数据完成中断
         */
        uint32_t i2c_tx_data_int_clr:1;
        /** i2c_detect_start_int_clr:WO；位位置：[8]；默认值：0；清除检测启动中断
         */
        uint32_t i2c_detect_start_int_clr:1;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} rtc_i2c_int_clr_reg_t;

/** i2c_int_raw寄存器中断原始寄存器的类型
 */
typedef union {
    struct {
        /** i2c_slave_trans_comp_int_raw:RO；位位置：[0]；默认值：0；从传输完成中断原始
         */
        uint32_t i2c_slave_tran_comp_int_raw:1;
        /** i2c_arbitation_lost_int_raw:RO；位位置：[1]；默认值：0；仲裁丢失中断原始
         */
        uint32_t i2c_arbitration_lost_int_raw:1;
        /** i2c_master_tran_comp_int_raw:RO；位位置：[2]；默认值：0；主传输完成中断原始
         */
        uint32_t i2c_master_tran_comp_int_raw:1;
        /** i2c_trans_complete_int_raw:RO；位位置：[3]；默认值：0；传输完成中断原始
         */
        uint32_t i2c_trans_complete_int_raw:1;
        /** i2c_time_out_int_raw:RO；位位置：[4]；默认值：0；原始超时中断
         */
        uint32_t i2c_time_out_int_raw:1;
        /** i2c_ack_err_int_raw:RO；位位置：[5]；默认值：0；ack错误中断原始
         */
        uint32_t i2c_ack_err_int_raw:1;
        /** i2c_rx_data_int_raw:RO；位位置：[6]；默认值：0；原始接收数据中断
         */
        uint32_t i2c_rx_data_int_raw:1;
        /** i2c_tx_data_int_raw:RO；位位置：[7]；默认值：0；原始传输数据中断
         */
        uint32_t i2c_tx_data_int_raw:1;
        /** i2c_detect_start_int_raw:RO；位位置：[8]；默认值：0；原始检测启动中断
         */
        uint32_t i2c_detect_start_int_raw:1;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} rtc_i2c_int_raw_reg_t;

/** i2c_int_st寄存器中断状态寄存器的类型
 */
typedef union {
    struct {
        /** i2c_slave_trans_comp_int_st:RO；位位置：[0]；默认值：0；从传输完成中断状态
         */
        uint32_t i2c_slave_tran_comp_int_st:1;
        /** i2c_arbitation_lost_int_st:RO；位位置：[1]；默认值：0；仲裁丢失中断状态
         */
        uint32_t i2c_arbitration_lost_int_st:1;
        /** i2c_master_tran_comp_int_st:RO；位位置：[2]；默认值：0；主传输完成中断状态
         */
        uint32_t i2c_master_tran_comp_int_st:1;
        /** i2c_trans_complete_int_st:RO；位位置：[3]；默认值：0；传输完成中断状态
         */
        uint32_t i2c_trans_complete_int_st:1;
        /** i2c_time_out_int_st:RO；位位置：[4]；默认值：0；超时中断状态
         */
        uint32_t i2c_time_out_int_st:1;
        /** i2c_ack_err_int_st:RO；位位置：[5]；默认值：0；ack错误中断状态
         */
        uint32_t i2c_ack_err_int_st:1;
        /** i2c_rx_data_int_st:RO；位位置：[6]；默认值：0；接收数据中断状态
         */
        uint32_t i2c_rx_data_int_st:1;
        /** i2c_tx_data_int_st:RO；位位置：[7]；默认值：0；传输数据中断状态
         */
        uint32_t i2c_tx_data_int_st:1;
        /** i2c_detect_start_int_st:RO；位位置：[8]；默认值：0；检测启动中断状态
         */
        uint32_t i2c_detect_start_int_st:1;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} rtc_i2c_int_st_reg_t;

/** i2c_int_ena寄存器中断启用寄存器的类型
 */
typedef union {
    struct {
        /** i2c_slave_trans_comp_int_ena:R/W；位位置：[0]；默认值：0；启用从传输完成中断
         */
        uint32_t i2c_slave_tran_comp_int_ena:1;
        /** i2c_arbitation_lost_int_ena:R/W；位位置：[1]；默认值：0；启用仲裁丢失中断
         */
        uint32_t i2c_arbitration_lost_int_ena:1;
        /** i2c_master_tran_comp_int_ena:R/W；位位置：[2]；默认值：0；启用主传输完成中断
         */
        uint32_t i2c_master_tran_comp_int_ena:1;
        /** i2c_trans_complete_int_ena:R/W；位位置：[3]；默认值：0；启用传输完成中断
         */
        uint32_t i2c_trans_complete_int_ena:1;
        /** i2c_time_out_int_ena:R/W；位位置：[4]；默认值：0；启用超时中断
         */
        uint32_t i2c_time_out_int_ena:1;
        /** i2c_ack_err_int_ena:R/W；位位置：[5]；默认值：0；启用eack错误中断
         */
        uint32_t i2c_ack_err_int_ena:1;
        /** i2c_rx_data_int_ena:R/W；位位置：[6]；默认值：0；启用接收数据中断
         */
        uint32_t i2c_rx_data_int_ena:1;
        /** i2c_tx_data_int_ena:R/W；位位置：[7]；默认值：0；启用传输数据中断
         */
        uint32_t i2c_tx_data_int_ena:1;
        /** i2c_detect_start_int_ena:R/W；位位置：[8]；默认值：0；启用检测启动中断
         */
        uint32_t i2c_detect_start_int_ena:1;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} rtc_i2c_int_ena_reg_t;


/**组：版本寄存器*/
/** i2c_date寄存器类型版本寄存器
 */
typedef union {
    struct {
        /** i2c_i2c_date:R/W；位位置：[27:0]；默认值：26235664；版本
         */
        uint32_t i2c_i2c_date:28;
        uint32_t reserved_28:4;
    };
    uint32_t val;
} rtc_i2c_date_reg_t;


typedef struct {
    volatile rtc_i2c_scl_low_reg_t i2c_scl_low;
    volatile rtc_i2c_ctrl_reg_t i2c_ctrl;
    volatile rtc_i2c_status_reg_t i2c_status;
    volatile rtc_i2c_to_reg_t i2c_to;
    volatile rtc_i2c_slave_addr_reg_t i2c_slave_addr;
    volatile rtc_i2c_scl_high_reg_t i2c_scl_high;
    volatile rtc_i2c_sda_duty_reg_t i2c_sda_duty;
    volatile rtc_i2c_scl_start_period_reg_t i2c_scl_start_period;
    volatile rtc_i2c_scl_stop_period_reg_t i2c_scl_stop_period;
    volatile rtc_i2c_int_clr_reg_t i2c_int_clr;
    volatile rtc_i2c_int_raw_reg_t i2c_int_raw;
    volatile rtc_i2c_int_st_reg_t i2c_int_st;
    volatile rtc_i2c_int_ena_reg_t i2c_int_ena;
    volatile rtc_i2c_data_reg_t i2c_data;
    volatile rtc_i2c_cmd0_reg_t i2c_cmd0;
    volatile rtc_i2c_cmd1_reg_t i2c_cmd1;
    volatile rtc_i2c_cmd2_reg_t i2c_cmd2;
    volatile rtc_i2c_cmd3_reg_t i2c_cmd3;
    volatile rtc_i2c_cmd4_reg_t i2c_cmd4;
    volatile rtc_i2c_cmd5_reg_t i2c_cmd5;
    volatile rtc_i2c_cmd6_reg_t i2c_cmd6;
    volatile rtc_i2c_cmd7_reg_t i2c_cmd7;
    volatile rtc_i2c_cmd8_reg_t i2c_cmd8;
    volatile rtc_i2c_cmd9_reg_t i2c_cmd9;
    volatile rtc_i2c_cmd10_reg_t i2c_cmd10;
    volatile rtc_i2c_cmd11_reg_t i2c_cmd11;
    volatile rtc_i2c_cmd12_reg_t i2c_cmd12;
    volatile rtc_i2c_cmd13_reg_t i2c_cmd13;
    volatile rtc_i2c_cmd14_reg_t i2c_cmd14;
    volatile rtc_i2c_cmd15_reg_t i2c_cmd15;
    uint32_t reserved_078[33];
    volatile rtc_i2c_date_reg_t i2c_date;
} rtc_dev_t;


#ifndef __cplusplus
_Static_assert(sizeof(rtc_dev_t) == 0x100, "Invalid size of rtc_dev_t structure");
#endif

#ifdef __cplusplus
}
#endif

