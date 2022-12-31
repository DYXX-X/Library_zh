// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_RTC_I2C_STRUCT_H_
#define _SOC_RTC_I2C_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct rtc_i2c_dev_s {
    union {
        struct {
            uint32_t period:        20;             /*scl=0的时间段*/
            uint32_t reserved20:    12;
        };
        uint32_t val;
    } scl_low;
    union {
        struct {
            uint32_t sda_force_out:        1;       /*1=推拉0=打开排水管*/
            uint32_t scl_force_out:        1;       /*1=推拉0=打开排水管*/
            uint32_t ms_mode:              1;       /*1=主0=从*/
            uint32_t trans_start:          1;       /*强制启动*/
            uint32_t tx_lsb_first:         1;       /*先通过lsb*/
            uint32_t rx_lsb_first:         1;       /*首先接收lsb*/
            uint32_t reserved6:           23;
            uint32_t i2c_ctrl_clk_gate_en: 1;
            uint32_t i2c_reset:            1;       /*rtc i2c开关复位*/
            uint32_t i2cclk_en:            1;       /*rtc i2c reg clk门控*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t ack_rec:             1;        /*确认响应*/
            uint32_t slave_rw:            1;        /*从读或写*/
            uint32_t arb_lost:            1;        /*仲裁失败*/
            uint32_t bus_busy:            1;        /*公共汽车很忙*/
            uint32_t slave_addressed:     1;        /*从属寄存器子地址*/
            uint32_t byte_trans:          1;        /*已完成一字节传输*/
            uint32_t op_cnt:              2;        /*哪个操作有效*/
            uint32_t reserved8:           8;
            uint32_t shift:               8;        /*移位器内容*/
            uint32_t scl_main_state_last: 3;        /*i2c最后一个主状态*/
            uint32_t reserved27:          1;
            uint32_t scl_state_last:      3;        /*scl最后状态*/
            uint32_t reserved31:          1;
        };
        uint32_t val;
    } status;
    union {
        struct {
            uint32_t time_out:  20;                 /*超时阈值*/
            uint32_t reserved20:12;
        };
        uint32_t val;
    } timeout;
    union {
        struct {
            uint32_t addr:         15;              /*从属地址*/
            uint32_t reserved15:   16;
            uint32_t en_10bit:      1;              /*i2c 10位模式启用*/
        };
        uint32_t val;
    } slave_addr;
    union {
        struct {
            uint32_t period:         20;            /*scl=1的时间段*/
            uint32_t reserved20:     12;
        };
        uint32_t val;
    } scl_high;
    union {
        struct {
            uint32_t sda_duty_num:20;               /*SCL变低后SDA切换的时间段*/
            uint32_t reserved20:  12;
        };
        uint32_t val;
    } sda_duty;
    union {
        struct {
            uint32_t scl_start_period:20;           /*触发I2C启动后SCL切换的时间段*/
            uint32_t reserved20:      12;
        };
        uint32_t val;
    } scl_start_period;
    union {
        struct {
            uint32_t scl_stop_period:20;            /*触发I2C结束后SCL停止的时间段*/
            uint32_t reserved20:     12;
        };
        uint32_t val;
    } scl_stop_period;
    union {
        struct {
            uint32_t slave_tran_comp:          1;   /*清除从属传输完成中断*/
            uint32_t arbitration_lost:         1;   /*清除仲裁丢失中断*/
            uint32_t master_tran_comp:         1;   /*清除主传输完成中断*/
            uint32_t trans_complete:           1;   /*清除传输完成中断*/
            uint32_t time_out:                 1;   /*清除超时中断*/
            uint32_t ack_err:                  1;   /*清除确认错误中断*/
            uint32_t rx_data:                  1;   /*清除接收数据中断*/
            uint32_t tx_data:                  1;   /*清除运输装载数据完成中断*/
            uint32_t detect_start:             1;   /*清除检测启动中断*/
            uint32_t reserved9:               23;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t slave_tran_comp:          1;   /*从传输完成中断原始*/
            uint32_t arbitration_lost:         1;   /*仲裁丢失中断原始*/
            uint32_t master_tran_comp:         1;   /*主传输完成中断原始*/
            uint32_t trans_complete:           1;   /*传输完成中断原始*/
            uint32_t time_out:                 1;   /*原始超时中断*/
            uint32_t ack_err:                  1;   /*ack错误中断原始*/
            uint32_t rx_data:                  1;   /*原始接收数据中断*/
            uint32_t tx_data:                  1;   /*原始传输数据中断*/
            uint32_t detect_start:             1;   /*原始检测启动中断*/
            uint32_t reserved9:               23;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t slave_tran_comp:         1;    /*从传输完成中断状态*/
            uint32_t arbitration_lost:        1;    /*仲裁丢失中断状态*/
            uint32_t master_tran_comp:        1;    /*主传输完成中断状态*/
            uint32_t trans_complete:          1;    /*传输完成中断状态*/
            uint32_t time_out:                1;    /*超时中断状态*/
            uint32_t ack_err:                 1;    /*ack错误中断状态*/
            uint32_t rx_data:                 1;    /*接收数据中断状态*/
            uint32_t tx_data:                 1;    /*传输数据中断状态*/
            uint32_t detect_start:            1;    /*检测启动中断状态*/
            uint32_t reserved9:              23;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t slave_tran_comp:          1;   /*启用从传输完成中断*/
            uint32_t arbitration_lost:         1;   /*启用仲裁丢失中断*/
            uint32_t master_tran_comp:         1;   /*启用主传输完成中断*/
            uint32_t trans_complete:           1;   /*启用传输完成中断*/
            uint32_t time_out:                 1;   /*启用超时中断*/
            uint32_t ack_err:                  1;   /*启用eack错误中断*/
            uint32_t rx_data:                  1;   /*启用接收数据中断*/
            uint32_t tx_data:                  1;   /*启用传输数据中断*/
            uint32_t detect_start:             1;   /*启用检测启动中断*/
            uint32_t reserved9:               23;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t i2c_rdata:     8;              /*收到的数据*/
            uint32_t slave_tx_data: 8;              /*从设备发送的数据*/
            uint32_t reserved16:   15;
            uint32_t i2c_done:      1;              /*i2c完成*/
        };
        uint32_t val;
    } fifo_data;
    union {
        struct {
            uint32_t command0:     14;              /*命令0*/
            uint32_t reserved14:   17;
            uint32_t done:          1;              /*命令_已完成*/
        };
        uint32_t val;
    } command[16];
    uint32_t reserved_78;
    uint32_t reserved_7c;
    uint32_t reserved_80;
    uint32_t reserved_84;
    uint32_t reserved_88;
    uint32_t reserved_8c;
    uint32_t reserved_90;
    uint32_t reserved_94;
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
    uint32_t reserved_f8;
    union {
        struct {
            uint32_t i2c_date:  28;
            uint32_t reserved28: 4;
        };
        uint32_t val;
    } date;
} rtc_i2c_dev_t;
extern rtc_i2c_dev_t RTC_I2C;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_RTC_I2C_STRUCT_H_ */

