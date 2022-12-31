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
#ifndef _SOC_RMT_STRUCT_H_
#define _SOC_RMT_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct rmt_dev_s {
    uint32_t data_ch[8];                                /*通过apb fifo访问通道0-7的R/W ram地址。注意，在某些情况下，从FIFO读取的数据可能会丢失。由于使用RMTMEM方法的RMT内存区域访问没有此问题，并且提供了FIFO寄存器所具有的所有功能，因此建议使用此方法。*/
    struct {
        union {
            struct {
                uint32_t div_cnt:        8;             /*该寄存器用于配置信道0-7中的分频器因数。*/
                uint32_t idle_thres:    16;             /*在接收模式中，当在输入信号上没有检测到边缘的时间超过reg_idle_thres_ch0时，则完成接收过程。*/
                uint32_t mem_size:       4;             /*该寄存器用于配置分配给通道0-7的内存块数量。*/
                uint32_t carrier_en:     1;             /*这是信道0-7的载波调制启用控制位。*/
                uint32_t carrier_out_lv: 1;             /*该位用于配置信道0-7.1’b1的载波调制方式：在低输出电平上传输1’b0：在高输出电平上发送。*/
                uint32_t mem_pd:         1;             /*此位用于减少内存消耗的功率。1： 存储器处于低功率状态。*/
                uint32_t clk_en:         1;             /*该位用于控制时钟。当软件配置RMT内部寄存器时，它控制寄存器时钟。*/
            };
            uint32_t val;
        } conf0;
        union {
            struct {
                uint32_t tx_start:        1;            /*设置此位以开始发送信道0-7的数据。*/
                uint32_t rx_en:           1;            /*设置此位以启用信道0-7的接收数据。*/
                uint32_t mem_wr_rst:      1;            /*设置此位以通过接收器访问重置通道0-7的写ram地址。*/
                uint32_t mem_rd_rst:      1;            /*设置此位以通过发射机访问重置信道0-7的读ram地址。*/
                uint32_t apb_mem_rst:     1;            /*设置此位以通过apb-fifo访问重置通道0-7的W/R ram地址（不鼓励使用fifo，请参阅上面data_ch[]项中的注释）*/
                uint32_t mem_owner:       1;            /*这是通道0-7内存使用权的标志。1’b1：接收机使用内存0：发射机使用内存*/
                uint32_t tx_conti_mode:   1;            /*设置此位以继续一次又一次地从信道0-7中的第一个数据发送到最后一个数据。*/
                uint32_t rx_filter_en:    1;            /*这是信道0-7的接收滤波器启用位。*/
                uint32_t rx_filter_thres: 8;            /*在接收模式信道0-7中，当脉冲宽度小于该值时忽略输入脉冲。*/
                uint32_t ref_cnt_rst:     1;            /*该位用于重置通道0-7中的除法器。*/
                uint32_t ref_always_on:   1;            /*该位用于选择基准时钟。1’b1：clk_apb 1’b0：clk_ref*/
                uint32_t idle_out_lv:     1;            /*该位配置信道0-7在空闲状态下的输出信号电平。*/
                uint32_t idle_out_en:     1;            /*这是处于空闲状态的通道0-7的输出启用控制位。*/
                uint32_t reserved20:     12;
            };
            uint32_t val;
        } conf1;
    } conf_ch[8];
    uint32_t status_ch[8];                              /*通道0-7的状态*/
    uint32_t apb_mem_addr_ch[8];                        /*apb fifo访问通道0-7中的ram相对地址（不鼓励使用fifo，请参阅上面data_ch[]项的注释）*/
    union {
        struct {
            uint32_t ch0_tx_end:       1;               /*当传输过程完成时，信道0的中断原始位变为高电平。*/
            uint32_t ch0_rx_end:       1;               /*当接收过程完成时，通道0的中断原始位变为高电平。*/
            uint32_t ch0_err:          1;               /*当通道0检测到一些错误时，通道0的中断原始位变为高电平。*/
            uint32_t ch1_tx_end:       1;               /*当传输过程完成时，信道1的中断原始位变为高电平。*/
            uint32_t ch1_rx_end:       1;               /*当接收过程完成时，信道1的中断原始位变为高电平。*/
            uint32_t ch1_err:          1;               /*当通道1检测到一些错误时，通道1的中断原始位变为高电平。*/
            uint32_t ch2_tx_end:       1;               /*当传输过程完成时，信道2的中断原始位变为高电平。*/
            uint32_t ch2_rx_end:       1;               /*当接收过程完成时，信道2的中断原始位变为高电平。*/
            uint32_t ch2_err:          1;               /*当通道2检测到一些错误时，通道2的中断原始位变为高电平。*/
            uint32_t ch3_tx_end:       1;               /*当传输过程完成时，信道3的中断原始位变为高电平。*/
            uint32_t ch3_rx_end:       1;               /*当接收过程完成时，通道3的中断原始位变为高电平。*/
            uint32_t ch3_err:          1;               /*当通道3检测到一些错误时，通道3的中断原始位变为高电平。*/
            uint32_t ch4_tx_end:       1;               /*当传输过程完成时，信道4的中断原始位变为高电平。*/
            uint32_t ch4_rx_end:       1;               /*当接收过程完成时，信道4的中断原始位变为高电平。*/
            uint32_t ch4_err:          1;               /*当通道4检测到一些错误时，通道4的中断原始位变为高电平。*/
            uint32_t ch5_tx_end:       1;               /*当传输过程完成时，信道5的中断原始位变为高电平。*/
            uint32_t ch5_rx_end:       1;               /*当接收过程完成时，信道5的中断原始位变为高电平。*/
            uint32_t ch5_err:          1;               /*当通道5检测到一些错误时，通道5的中断原始位变为高电平。*/
            uint32_t ch6_tx_end:       1;               /*当传输过程完成时，信道6的中断原始位变为高电平。*/
            uint32_t ch6_rx_end:       1;               /*当接收过程完成时，信道6的中断原始位变为高电平。*/
            uint32_t ch6_err:          1;               /*当通道6检测到一些错误时，通道6的中断原始位变为高电平。*/
            uint32_t ch7_tx_end:       1;               /*当传输过程完成时，通道7的中断原始位变为高电平。*/
            uint32_t ch7_rx_end:       1;               /*当接收过程完成时，通道7的中断原始位变为高电平。*/
            uint32_t ch7_err:          1;               /*当通道7检测到一些错误时，通道7的中断原始位变为高电平。*/
            uint32_t ch0_tx_thr_event: 1;               /*当信道0中的发射机发送的数据超过reg_rmt_tx_lim_ch0时，信道0的中断原始位变为高电平。*/
            uint32_t ch1_tx_thr_event: 1;               /*当信道1中的发射机发送的数据超过reg_rmt_tx_lim_ch1时，信道1的中断原始位变为高电平。*/
            uint32_t ch2_tx_thr_event: 1;               /*当信道2中的发射机发送的数据超过reg_rmt_tx_lim_ch2时，信道2的中断原始位变为高电平。*/
            uint32_t ch3_tx_thr_event: 1;               /*当信道3中的发射机发送的数据超过reg_rmt_tx_lim_ch3时，信道3的中断原始位变为高电平。*/
            uint32_t ch4_tx_thr_event: 1;               /*当信道4中的发射机发送的数据超过reg_rmt_tx_lim_ch4时，信道4的中断原始位变为高电平。*/
            uint32_t ch5_tx_thr_event: 1;               /*当信道5中的发射机发送的数据超过reg_rmt_tx_lim_ch5时，信道5的中断原始位变为高电平。*/
            uint32_t ch6_tx_thr_event: 1;               /*当信道6中的发射机发送的数据超过reg_rmt_tx_lim_ch6时，信道6的中断原始位变为高电平。*/
            uint32_t ch7_tx_thr_event: 1;               /*当信道7中的发射机发送的数据超过reg_rmt_tx_lim_ch7时，信道7的中断原始位变为高电平。*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t ch0_tx_end:       1;                /*当mt_ch0_tx_end_int_ena设置为0时，通道0的mt_ch0 _tx_end.int_raw的中断状态位。*/
            uint32_t ch0_rx_end:       1;                /*当rmt_ch0_rx_end_int_ena设置为0时，通道0的rmt_ch0 _rx_end.int_raw的中断状态位。*/
            uint32_t ch0_err:          1;                /*当rmt_ch0_err_int_ena设置为0时，通道0的rmt_ch0 _err_int.raw的中断状态位。*/
            uint32_t ch1_tx_end:       1;                /*当mt_ch1_tx_end_int_ena设置为1时，通道1的mt_ch1_tx_end_int.raw的中断状态位。*/
            uint32_t ch1_rx_end:       1;                /*当rmt_ch1_rx_end_int_ena设置为1时，通道1的rmt_ch_1_rx_end_int_raw的中断状态位。*/
            uint32_t ch1_err:          1;                /*当rmt_ch1_err_int_ena设置为1时，通道1的rmt_chl_err_int_raw的中断状态位。*/
            uint32_t ch2_tx_end:       1;                /*当mt_ch2_tx_end_int_ena设置为1时，通道2的mt_ch2_tx_end_int.raw的中断状态位。*/
            uint32_t ch2_rx_end:       1;                /*当rmt_ch2_rx_end_int_ena设置为1时，通道2的rmt_ch_2_rx_end_int_raw的中断状态位。*/
            uint32_t ch2_err:          1;                /*当rmt_ch2_err_int_ena设置为1时，通道2的rmt_ch1_err_int_raw的中断状态位。*/
            uint32_t ch3_tx_end:       1;                /*当mt_ch3_tx_end_int_ena设置为1时，通道3的mt_ch3_tx_end_int.raw的中断状态位。*/
            uint32_t ch3_rx_end:       1;                /*当rmt_ch3_rx_end_int_ena设置为1时，通道3的rmt_ch_3_rx_end_int_raw的中断状态位。*/
            uint32_t ch3_err:          1;                /*当rmt_ch3_err_int_ena设置为1时，通道3的rmt_ch2_err_int_raw的中断状态位。*/
            uint32_t ch4_tx_end:       1;                /*当mt_ch4_tx_end_int_ena设置为1时，通道4的mt_ch_4_tx_end_int_raw的中断状态位。*/
            uint32_t ch4_rx_end:       1;                /*当rmt_ch4_rx_end_int_ena设置为1时，通道4的rmt_ch_4_rx_end_int_raw的中断状态位。*/
            uint32_t ch4_err:          1;                /*当rmt_ch4_err_int_ena设置为1时，通道4的rmt_ch4-err_int_raw的中断状态位。*/
            uint32_t ch5_tx_end:       1;                /*当mt_ch5_tx_end_int_ena设置为1时，通道5的mt_ch5_tx_end_int_raw的中断状态位。*/
            uint32_t ch5_rx_end:       1;                /*当rmt_ch5_rx_end_int_ena设置为1时，通道5的rmt_ch_5_rx_end_int_raw的中断状态位。*/
            uint32_t ch5_err:          1;                /*当rmt_ch5_err_int_ena设置为1时，通道5的rmt_ch2_err_int_raw的中断状态位。*/
            uint32_t ch6_tx_end:       1;                /*当mt_ch6_tx_end_int_ena设置为1时，通道6的mt_ch6_tx_end_int_raw的中断状态位。*/
            uint32_t ch6_rx_end:       1;                /*当rmt_ch6_rx_end_int_ena设置为1时，通道6的rmt_ch6_rx_end_int_raw的中断状态位。*/
            uint32_t ch6_err:          1;                /*当rmt_ch6_err_int_ena设置为1时，通道6的rmt_ch6_err_int_raw的中断状态位。*/
            uint32_t ch7_tx_end:       1;                /*当mt_ch7_tx_end_int_ena设置为1时，通道7的mt_ch7_tx_end_int_raw的中断状态位。*/
            uint32_t ch7_rx_end:       1;                /*当rmt_ch7_rx_end_int_ena设置为1时，通道7的rmt_ch7_rx_end_int_raw的中断状态位。*/
            uint32_t ch7_err:          1;                /*当rmt_ch7_err_int_ena设置为1时，通道7的rmt_ch7_err_int_raw的中断状态位。*/
            uint32_t ch0_tx_thr_event: 1;                /*当mt_ch0_txt_thr_event_int_ena设置为1时，通道0的rmt_ch0_tx_thr_event_int_raw的中断状态位。*/
            uint32_t ch1_tx_thr_event: 1;                /*当mt_ch1_tx_thr_event_int_ena设置为1时，通道1的rmt_ch1_tx_thr_event_int_raw的中断状态位。*/
            uint32_t ch2_tx_thr_event: 1;                /*当mt_ch2_tx_thr_event_int_ena设置为1时，通道2的rmt_ch2_tx_thr_event_int_raw的中断状态位。*/
            uint32_t ch3_tx_thr_event: 1;                /*当mt_ch3_tx_thr_event_int_ena设置为1时，通道3的rmt_ch3_tx_thr_event_int_raw的中断状态位。*/
            uint32_t ch4_tx_thr_event: 1;                /*当mt_ch4_tx_thr_event_int_ena设置为1时，通道4的rmt_ch4_tx_thr事件_int_raw的中断状态位。*/
            uint32_t ch5_tx_thr_event: 1;                /*当mt_ch5_tx_thr_event_int_ena设置为1时，通道5的rmt_ch5_tx_thr_event_int_raw的中断状态位。*/
            uint32_t ch6_tx_thr_event: 1;                /*当mt_ch6_tx_tr_event_int_ena设置为1时，通道6的rmt_ch6_tx_tx_thr_event_int.raw的中断状态位。*/
            uint32_t ch7_tx_thr_event: 1;                /*当mt_ch7_tx_thr_event_int_ena设置为1时，通道7的rmt_ch7_tx_thr_event_int_raw的中断状态位。*/
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t ch0_tx_end:       1;               /*设置此位以启用rmt_ch0_tx_end_int_st。*/
            uint32_t ch0_rx_end:       1;               /*设置此位以启用rmt_ch0_rx_end_int_st。*/
            uint32_t ch0_err:          1;               /*设置此位以启用rmt_ch0_err_int_st。*/
            uint32_t ch1_tx_end:       1;               /*设置此位以启用rmt_ch1_tx_end_int_st。*/
            uint32_t ch1_rx_end:       1;               /*设置此位以启用rmt_ch1_rx_end_int_st。*/
            uint32_t ch1_err:          1;               /*设置此位以启用rmt_ch1_err_int_st。*/
            uint32_t ch2_tx_end:       1;               /*设置此位以启用rmt_ch2_tx_end_int_st。*/
            uint32_t ch2_rx_end:       1;               /*设置此位以启用rmt_ch2_rx_end_int_st。*/
            uint32_t ch2_err:          1;               /*设置此位以启用rmt_ch2_err_int_st。*/
            uint32_t ch3_tx_end:       1;               /*设置此位以启用rmt_ch3_tx_end_int_st。*/
            uint32_t ch3_rx_end:       1;               /*设置此位以启用rmt_ch3_rx_end_int_st。*/
            uint32_t ch3_err:          1;               /*设置此位以启用rmt_ch3_err_int_st。*/
            uint32_t ch4_tx_end:       1;               /*设置此位以启用rmt_ch4_tx_end_int_st。*/
            uint32_t ch4_rx_end:       1;               /*设置此位以启用rmt_ch4_rx_end_int_st。*/
            uint32_t ch4_err:          1;               /*设置此位以启用rmt_ch4_err_int_st。*/
            uint32_t ch5_tx_end:       1;               /*设置此位以启用rmt_ch5_tx_end_int_st。*/
            uint32_t ch5_rx_end:       1;               /*设置此位以启用rmt_ch5_rx_end_int_st。*/
            uint32_t ch5_err:          1;               /*设置此位以启用rmt_ch5_err_int_st。*/
            uint32_t ch6_tx_end:       1;               /*设置此位以启用rmt_ch6_tx_end_int_st。*/
            uint32_t ch6_rx_end:       1;               /*设置此位以启用rmt_ch6_rx_end_int_st。*/
            uint32_t ch6_err:          1;               /*设置此位以启用rmt_ch6_err_int_st。*/
            uint32_t ch7_tx_end:       1;               /*设置此位以启用rmt_ch7_tx_end_int_st。*/
            uint32_t ch7_rx_end:       1;               /*设置此位以启用rmt_ch7_rx_end_int_st。*/
            uint32_t ch7_err:          1;               /*设置此位以启用rmt_ch7_err_int_st。*/
            uint32_t ch0_tx_thr_event: 1;               /*设置此位以启用rmt_ch0_tx_thr_event_int_st。*/
            uint32_t ch1_tx_thr_event: 1;               /*设置此位以启用rmt_ch1_tx_thr_event_int_st。*/
            uint32_t ch2_tx_thr_event: 1;               /*设置此位以启用rmt_ch2_tx_thr_event_int_st。*/
            uint32_t ch3_tx_thr_event: 1;               /*设置此位以启用rmt_ch3_tx_thr_event_int_st。*/
            uint32_t ch4_tx_thr_event: 1;               /*设置此位以启用rmt_ch4_tx_thr_event_int_st。*/
            uint32_t ch5_tx_thr_event: 1;               /*设置此位以启用rmt_ch5_tx_thr_event_int_st。*/
            uint32_t ch6_tx_thr_event: 1;               /*设置此位以启用rmt_ch6_tx_tr_event_int_st。*/
            uint32_t ch7_tx_thr_event: 1;               /*设置此位以启用rmt_ch7_tx_thr_event_int_st。*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t ch0_tx_end:       1;               /*设置此位以清除rmt_ch0_rx_end_int_raw。。*/
            uint32_t ch0_rx_end:       1;               /*设置此位以清除rmt_ch0_tx_end_int_raw。*/
            uint32_t ch0_err:          1;               /*设置此位以清除rmt_ch0_err_int_raw。*/
            uint32_t ch1_tx_end:       1;               /*设置此位以清除rmt_ch1_rx_end_int_raw。。*/
            uint32_t ch1_rx_end:       1;               /*设置此位以清除rmt_ch1_tx_end_int_raw。*/
            uint32_t ch1_err:          1;               /*设置此位以清除rmt_ch1_err_int_raw。*/
            uint32_t ch2_tx_end:       1;               /*设置此位以清除rmt_ch2_rx_end_int_raw。。*/
            uint32_t ch2_rx_end:       1;               /*设置此位以清除rmt_ch2_tx_end_int_raw。*/
            uint32_t ch2_err:          1;               /*设置此位以清除rmt_ch2_err_int_raw。*/
            uint32_t ch3_tx_end:       1;               /*设置此位以清除rmt_ch3_rx_end_int_raw。。*/
            uint32_t ch3_rx_end:       1;               /*设置此位以清除rmt_ch3_tx_end_int_raw。*/
            uint32_t ch3_err:          1;               /*设置此位以清除rmt_ch3_err_int_raw。*/
            uint32_t ch4_tx_end:       1;               /*设置此位以清除rmt_ch4_rx_end_int_raw。。*/
            uint32_t ch4_rx_end:       1;               /*设置此位以清除rmt_ch4_tx_end_int_raw。*/
            uint32_t ch4_err:          1;               /*设置此位以清除rmt_ch4_err_int_raw。*/
            uint32_t ch5_tx_end:       1;               /*设置此位以清除rmt_ch5_rx_end_int_raw。。*/
            uint32_t ch5_rx_end:       1;               /*设置此位以清除rmt_ch5_tx_end_int_raw。*/
            uint32_t ch5_err:          1;               /*设置此位以清除rmt_ch5_err_int_raw。*/
            uint32_t ch6_tx_end:       1;               /*设置此位以清除rmt_ch6_rx_end_int_raw。。*/
            uint32_t ch6_rx_end:       1;               /*设置此位以清除rmt_ch6_tx_end_int_raw。*/
            uint32_t ch6_err:          1;               /*设置此位以清除rmt_ch6_err_int_raw。*/
            uint32_t ch7_tx_end:       1;               /*设置此位以清除rmt_ch7_rx_end_int_raw。。*/
            uint32_t ch7_rx_end:       1;               /*设置此位以清除rmt_ch7_tx_end_int_raw。*/
            uint32_t ch7_err:          1;               /*设置此位以清除rmt_ch7_err_int_raw。*/
            uint32_t ch0_tx_thr_event: 1;               /*设置此位以清除rmt_ch0_tx_thr_event_int_raw中断。*/
            uint32_t ch1_tx_thr_event: 1;               /*设置此位以清除rmt_ch1_tx_thr_event_int_raw中断。*/
            uint32_t ch2_tx_thr_event: 1;               /*设置此位以清除rmt_ch2_tx_thr_event_int_raw中断。*/
            uint32_t ch3_tx_thr_event: 1;               /*设置此位以清除rmt_ch3_tx_thr_event_int_raw中断。*/
            uint32_t ch4_tx_thr_event: 1;               /*设置此位以清除rmt_ch4_tx_thr_event_int_raw中断。*/
            uint32_t ch5_tx_thr_event: 1;               /*设置此位以清除rmt_ch5_tx_thr_event_int_raw中断。*/
            uint32_t ch6_tx_thr_event: 1;               /*设置此位以清除rmt_ch6_tx_tr_event_int_raw中断。*/
            uint32_t ch7_tx_thr_event: 1;               /*设置此位以清除rmt_ch7_tx_thr_event_int_raw中断。*/
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t low: 16;                           /*该寄存器用于配置信道0-7的载波低电平值。*/
            uint32_t high:16;                           /*该寄存器用于配置信道0-7的载波高电平值。*/
        };
        uint32_t val;
    } carrier_duty_ch[8];
    union {
        struct {
            uint32_t limit: 9;                          /*当通道0-7发送的数据超过reg_rmt_tx_lim_ch0时，通道0-7产生相对中断。*/
            uint32_t reserved9: 23;
        };
        uint32_t val;
    } tx_lim_ch[8];
    union {
        struct {
            uint32_t fifo_mask:  1;                     /*设置此位以启用RMTMEM并禁用apb-fifo访问（不鼓励使用fifo，请参阅上面data_ch[]项的注释）*/
            uint32_t mem_tx_wrap_en: 1;                 /*当需要发送的数据超过信道的mem可以存储的数据时，设置该位以启用mem的重用，该位与regrmt_txlim_chn一起使用。*/
            uint32_t reserved2:     30;
        };
        uint32_t val;
    } apb_conf;
    uint32_t reserved_f4;
    uint32_t reserved_f8;
    uint32_t date;                                      /*这是版本寄存器。*/
} rmt_dev_t;
extern rmt_dev_t RMT;

typedef struct rmt_item32_s {
    union {
        struct {
            uint32_t duration0 :15;
            uint32_t level0 :1;
            uint32_t duration1 :15;
            uint32_t level1 :1;
        };
        uint32_t val;
    };
} rmt_item32_t;

//允许使用RMTMEM.chan[0].data32[8]访问RMT内存
typedef volatile struct rmt_mem_s {
    struct {
        rmt_item32_t data32[64];
    } chan[8];
} rmt_mem_t;
extern rmt_mem_t RMTMEM;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_RMT_STRUCT_H_ */

