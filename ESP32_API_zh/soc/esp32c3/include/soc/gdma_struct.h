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
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct gdma_dev_s {
    struct {
        union {
            struct {
                uint32_t in_done:                   1;       /*当接收到Rx通道0的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。*/
                uint32_t in_suc_eof:                1;       /*当接收到Rx通道0的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且未检测到Rx信道0的数据错误时，原始断开位变为低电平。*/
                uint32_t in_err_eof:                1;       /*当仅在外围设备为Rx通道0的UHCI0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。*/
                uint32_t out_done:                  1;       /*当一个输出链接描述符所指向的最后一个数据已传输到Tx信道0的外围设备时，原始中断位变为高电平。*/
                uint32_t out_eof:                   1;       /*当从Tx信道0的存储器中读取一个输出描述符所指向的最后数据时，原始中断位变为高电平。*/
                uint32_t in_dscr_err:               1;       /*当检测到内联描述符错误（包括所有者错误）时，原始中断位变为高电平，其中包括Rx通道0的内联描述符的第二个和第三个字错误。*/
                uint32_t out_dscr_err:              1;       /*当检测到包括所有者错误的输出链接描述符错误时，原始中断位变为高电平。*/
                uint32_t in_dscr_empty:             1;       /*当内联指向的Rx缓冲区已满且接收数据未完成但Rx通道0没有更多内联时，原始中断位变为高电平。*/
                uint32_t out_total_eof:             1;       /*当针对Tx信道0发送出对应于输出链接（包括一个链路描述符或几个链路描述符）的数据时，原始中断位变为高电平。*/
                uint32_t infifo_ovf:                1;       /*当Rx通道0的1级fifo溢出时，此原始中断位变为高电平。*/
                uint32_t infifo_udf:                1;       /*当Rx通道0的1级fifo下溢时，该原始中断位变为高电平。*/
                uint32_t outfifo_ovf:               1;       /*当Tx信道0的1级fifo溢出时，该原始中断位变为高电平。*/
                uint32_t outfifo_udf:               1;       /*当Tx信道0的1级fifo下溢时，该原始中断位变为高电平。*/
                uint32_t reserved13:               19;       /*保留*/
            };
            uint32_t val;
        } raw;
        union {
            struct {
                uint32_t in_done:                  1;        /*IN_DONE_CH_INT中断的原始中断状态位。*/
                uint32_t in_suc_eof:               1;        /*IN_SUC_EOF_CH_INT中断的原始中断状态位。*/
                uint32_t in_err_eof:               1;        /*IN_ERR_EOF_CH_INT中断的原始中断状态位。*/
                uint32_t out_done:                 1;        /*OUT_DONE_CH_INT中断的原始中断状态位。*/
                uint32_t out_eof:                  1;        /*OUT_EOF_CH_INT中断的原始中断状态位。*/
                uint32_t in_dscr_err:              1;        /*IN_DSCR_ERR_CH_INT中断的原始中断状态位。*/
                uint32_t out_dscr_err:             1;        /*OUT_DSCR_ERR_CH_INT中断的原始中断状态位。*/
                uint32_t in_dscr_empty:            1;        /*IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。*/
                uint32_t out_total_eof:            1;        /*OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。*/
                uint32_t infifo_ovf:               1;        /*INFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
                uint32_t infifo_udf:               1;        /*INFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
                uint32_t outfifo_ovf:              1;        /*OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
                uint32_t outfifo_udf:              1;        /*OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
                uint32_t reserved13:              19;        /*保留*/
            };
            uint32_t val;
        } st;
        union {
            struct {
                uint32_t in_done:                   1;       /*IN_DONE_CH_INT中断的中断启用位。*/
                uint32_t in_suc_eof:                1;       /*IN_SUC_EOF_CH_INT中断的中断启用位。*/
                uint32_t in_err_eof:                1;       /*IN_ERR_EOF_CH_INT中断的中断启用位。*/
                uint32_t out_done:                  1;       /*OUT_DONE_CH_INT中断的中断启用位。*/
                uint32_t out_eof:                   1;       /*OUT_EOF_CH_INT中断的中断启用位。*/
                uint32_t in_dscr_err:               1;       /*IN_DSCR_ERR_CH_INT中断的中断启用位。*/
                uint32_t out_dscr_err:              1;       /*OUT_DSCR_ERR_CH_INT中断的中断启用位。*/
                uint32_t in_dscr_empty:             1;       /*IN_DSCR_EMPTY_CH_INT中断的中断启用位。*/
                uint32_t out_total_eof:             1;       /*OUT_TOTAL_EOF_CH_INT中断的中断启用位。*/
                uint32_t infifo_ovf:                1;       /*INFIFO_OVF_L1_CH_INT中断的中断启用位。*/
                uint32_t infifo_udf:                1;       /*INFIFO_UDF_L1_CH_INT中断的中断启用位。*/
                uint32_t outfifo_ovf:               1;       /*OUTFIFO_OVF_L1_CH_INT中断的中断启用位。*/
                uint32_t outfifo_udf:               1;       /*OUTFIFO_UDF_L1_CH_INT中断的中断启用位。*/
                uint32_t reserved13:               19;       /*保留*/
            };
            uint32_t val;
        } ena;
        union {
            struct {
                uint32_t in_done:                   1;       /*设置此位以清除IN_DONE_CH_INT中断。*/
                uint32_t in_suc_eof:                1;       /*设置此位以清除IN_SUC_EOF_CH_INT中断。*/
                uint32_t in_err_eof:                1;       /*设置此位以清除IN_ERR_EOF_CH_INT中断。*/
                uint32_t out_done:                  1;       /*设置该位以清除OUT_DONE_CH_INT中断。*/
                uint32_t out_eof:                   1;       /*设置此位以清除OUT_EOF_CH_INT中断。*/
                uint32_t in_dscr_err:               1;       /*设置该位以清除IN_DSCR_ERR_CH_INT中断。*/
                uint32_t out_dscr_err:              1;       /*设置该位以清除OUT_DSCR_ERR_CH_INT中断。*/
                uint32_t in_dscr_empty:             1;       /*设置此位以清除IN_DSCR_EMPTY_CH_INT中断。*/
                uint32_t out_total_eof:             1;       /*设置此位以清除OUT_TOTAL_EOF_CH_INT中断。*/
                uint32_t infifo_ovf:                1;       /*设置此位以清除INFIFO_OVF_L1_CH_INT中断。*/
                uint32_t infifo_udf:                1;       /*设置此位以清除INFIFO_UDF_L1_CH_INT中断。*/
                uint32_t outfifo_ovf:               1;       /*设置该位以清除OUTFIFO_OVF_L1_CH_INT中断。*/
                uint32_t outfifo_udf:               1;       /*设置该位以清除OUTFIFO_UDF_L1_CH_INT中断。*/
                uint32_t reserved13:               19;       /*保留*/
            };
            uint32_t val;
        } clr;
    } intr[3];
    uint32_t reserved_30;
    uint32_t reserved_34;
    uint32_t reserved_38;
    uint32_t reserved_3c;
    union {
        struct {
            uint32_t ahb_testmode: 3;                    /*保留*/
            uint32_t reserved3:    1;                    /*保留*/
            uint32_t ahb_testaddr: 2;                    /*保留*/
            uint32_t reserved6:   26;                    /*保留*/
        };
        uint32_t val;
    } ahb_test;
    union {
        struct {
            uint32_t ahbm_rst_inter: 1;                  /*设置该位，然后清除该位以重置内部ahb FSM。*/
            uint32_t reserved1:      1;
            uint32_t arb_pri_dis:    1;                  /*设置此位以禁用优先级仲裁功能。*/
            uint32_t clk_en:         1;
            uint32_t reserved4:     28;
        };
        uint32_t val;
    } misc_conf;
    uint32_t date;                                       /**/
    uint32_t reserved_4c;
    uint32_t reserved_50;
    uint32_t reserved_54;
    uint32_t reserved_58;
    uint32_t reserved_5c;
    uint32_t reserved_60;
    uint32_t reserved_64;
    uint32_t reserved_68;
    uint32_t reserved_6c;
    struct {
        struct {
            union {
                struct {
                    uint32_t in_rst:               1;            /*该位用于重置DMA通道0 Rx FSM和Rx FIFO指针。*/
                    uint32_t in_loop_test:         1;            /*保留*/
                    uint32_t indscr_burst_en:      1;            /*当访问内部SRAM时，将此位设置为1以启用Rx通道0读取链路描述符的INCR突发传输。*/
                    uint32_t in_data_burst_en:     1;            /*将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道0的INCR突发传输。*/
                    uint32_t mem_trans_en:         1;            /*将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。*/
                    uint32_t reserved5:           27;            /*保留*/
                };
                uint32_t val;
            } in_conf0;
            union {
                struct {
                    uint32_t reserved0:         12;
                    uint32_t in_check_owner:     1;              /*设置此位以启用检查链接描述符的所有者属性。*/
                    uint32_t reserved13:        19;              /*保留*/
                };
                uint32_t val;
            } in_conf1;
            union {
                struct {
                    uint32_t infifo_full:            1;          /*Rx信道0的L1 Rx FIFO满信号。*/
                    uint32_t infifo_empty:           1;          /*Rx信道0的L1 Rx FIFO空信号。*/
                    uint32_t infifo_cnt:             6;          /*寄存器将数据的字节数存储在Rx通道0的L1 Rx FIFO中。*/
                    uint32_t reserved8:             15;          /*保留*/
                    uint32_t in_remain_under_1b:     1;          /*保留*/
                    uint32_t in_remain_under_2b:     1;          /*保留*/
                    uint32_t in_remain_under_3b:     1;          /*保留*/
                    uint32_t in_remain_under_4b:     1;          /*保留*/
                    uint32_t in_buf_hungry:          1;          /*保留*/
                    uint32_t reserved28:             4;          /*保留*/
                };
                uint32_t val;
            } infifo_status;
            union {
                struct {
                    uint32_t infifo_rdata:    12;                /*该寄存器存储从DMA FIFO弹出的数据。*/
                    uint32_t infifo_pop:       1;                /*设置此位以从DMA FIFO弹出数据。*/
                    uint32_t reserved13:      19;                /*保留*/
                };
                uint32_t val;
            } in_pop;
            union {
                struct {
                    uint32_t addr:               20;             /*该寄存器存储第一个内联描述符地址的20个最低有效位。*/
                    uint32_t auto_ret:            1;             /*当当前接收数据中存在一些错误时，设置此位以返回当前内联描述符的地址。*/
                    uint32_t stop:                1;             /*设置此位以停止处理内联描述符。*/
                    uint32_t start:               1;             /*设置此位以开始处理内联描述符。*/
                    uint32_t restart:             1;             /*设置此位以装入新的内联描述符。*/
                    uint32_t park:                1;             /*1： 内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。*/
                    uint32_t reserved25:          7;
                };
                uint32_t val;
            } in_link;
            union {
                struct {
                    uint32_t inlink_dscr_addr:    18;            /*此寄存器存储当前内联描述符的地址。*/
                    uint32_t in_dscr_state:        2;            /*保留*/
                    uint32_t in_state:             3;            /*保留*/
                    uint32_t reserved23:           9;            /*保留*/
                };
                uint32_t val;
            } in_state;
            uint32_t in_suc_eof_des_addr;                    /**/
            uint32_t in_err_eof_des_addr;                    /**/
            uint32_t in_dscr;                                /**/
            uint32_t in_dscr_bf0;                            /**/
            uint32_t in_dscr_bf1;                            /**/
            union {
                struct {
                    uint32_t rx_pri:     4;                      /*Rx通道0的优先级。值越大，优先级越高。*/
                    uint32_t reserved4: 28;
                };
                uint32_t val;
            } in_pri;
            union {
                struct {
                    uint32_t sel:             6;                 /*此寄存器用于为Rx通道选择外设。0:SPI2.1:保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
                    uint32_t reserved6:      26;
                };
                uint32_t val;
            } in_peri_sel;
        } in;
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
        struct {
            union {
                struct {
                    uint32_t out_rst:               1;           /*该位用于重置DMA通道0 Tx FSM和Tx FIFO指针。*/
                    uint32_t out_loop_test:         1;           /*保留*/
                    uint32_t out_auto_wrback:       1;           /*设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。*/
                    uint32_t out_eof_mode:          1;           /*传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道0的EOF标志*/
                    uint32_t outdscr_burst_en:      1;           /*当访问内部SRAM时，将此位设置为1以启用Tx信道0读取链路描述符的INCR突发传输。*/
                    uint32_t out_data_burst_en:     1;           /*当访问内部SRAM时，将此位设置为1，以启用传输数据的Tx信道0的INCR突发传输。*/
                    uint32_t reserved6:            26;
                };
                uint32_t val;
            } out_conf0;
            union {
                struct {
                    uint32_t reserved0:          12;
                    uint32_t out_check_owner:     1;             /*设置此位以启用检查链接描述符的所有者属性。*/
                    uint32_t reserved13:         19;             /*保留*/
                };
                uint32_t val;
            } out_conf1;
            union {
                struct {
                    uint32_t outfifo_full:            1;         /*Tx信道0的L1 Tx FIFO满信号。*/
                    uint32_t outfifo_empty:           1;         /*Tx信道0的L1 Tx FIFO空信号。*/
                    uint32_t outfifo_cnt:             6;         /*寄存器将数据的字节数存储在Tx信道0的L1 Tx FIFO中。*/
                    uint32_t reserved8:              15;         /*保留*/
                    uint32_t out_remain_under_1b:     1;         /*保留*/
                    uint32_t out_remain_under_2b:     1;         /*保留*/
                    uint32_t out_remain_under_3b:     1;         /*保留*/
                    uint32_t out_remain_under_4b:     1;         /*保留*/
                    uint32_t reserved27:              5;         /*保留*/
                };
                uint32_t val;
            } outfifo_status;
            union {
                struct {
                    uint32_t outfifo_wdata:     9;               /*该寄存器存储需要推入DMA FIFO的数据。*/
                    uint32_t outfifo_push:      1;               /*设置此位以将数据推入DMA FIFO。*/
                    uint32_t reserved10:       22;               /*保留*/
                };
                uint32_t val;
            } out_push;
            union {
                struct {
                    uint32_t addr:               20;             /*该寄存器存储第一个输出链接描述符地址的20个最低有效位。*/
                    uint32_t stop:                1;             /*设置此位以停止处理outlink描述符。*/
                    uint32_t start:               1;             /*设置此位以开始处理outlink描述符。*/
                    uint32_t restart:             1;             /*设置此位以从最后一个地址重新启动新的outlink。*/
                    uint32_t park:                1;             /*1： outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。*/
                    uint32_t reserved24:          8;
                };
                uint32_t val;
            } out_link;
            union {
                struct {
                    uint32_t outlink_dscr_addr:    18;           /*此寄存器存储当前outlink描述符的地址。*/
                    uint32_t out_dscr_state:        2;           /*保留*/
                    uint32_t out_state:             3;           /*保留*/
                    uint32_t reserved23:            9;           /*保留*/
                };
                uint32_t val;
            } out_state;
            uint32_t out_eof_des_addr;                       /**/
            uint32_t out_eof_bfr_des_addr;                   /**/
            uint32_t out_dscr;                               /**/
            uint32_t out_dscr_bf0;                           /**/
            uint32_t out_dscr_bf1;                           /**/
            union {
                struct {
                    uint32_t tx_pri:     4;                      /*Tx信道0的优先级。值越大，优先级越高。*/
                    uint32_t reserved4: 28;
                };
                uint32_t val;
            } out_pri;
            union {
                struct {
                    uint32_t sel:              6;                /*此寄存器用于为Tx信道选择外设。0:SPI2.1：保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
                    uint32_t reserved6:       26;
                };
                uint32_t val;
            } out_peri_sel;
        } out;
        uint32_t reserved_104;
        uint32_t reserved_108;
        uint32_t reserved_10c;
        uint32_t reserved_110;
        uint32_t reserved_114;
        uint32_t reserved_118;
        uint32_t reserved_11c;
        uint32_t reserved_120;
        uint32_t reserved_124;
        uint32_t reserved_128;
        uint32_t reserved_12c;
    } channel[3];
} gdma_dev_t;

extern gdma_dev_t GDMA;

#ifdef __cplusplus
}
#endif

