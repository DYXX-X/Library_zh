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
#ifndef _SOC_UART_STRUCT_H_
#define _SOC_UART_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct uart_dev_s {
    union {
        struct {
            uint32_t rw_byte;                 /*一*/
        };
        uint32_t val;
    } ahb_fifo;
    union {
        struct {
            uint32_t rxfifo_full:              1;       /*当接收器接收到的数据超过rxfif_full_thrhd指定的数据时，此中断原始位变为高电平。*/
            uint32_t txfifo_empty:             1;       /*当Tx FIFO中的数据量小于txfifo_empty_thrhd指定的值时，该中断原始位变为高电平。*/
            uint32_t parity_err:               1;       /*当接收器检测到数据中的奇偶校验错误时，该中断原始位变为高电平。*/
            uint32_t frm_err:                  1;       /*当接收机检测到数据帧错误时，该中断原始位变为高电平。*/
            uint32_t rxfifo_ovf:               1;       /*当接收器接收的数据超过FIFO所能存储的数据时，该中断原始位变为高电平。*/
            uint32_t dsr_chg:                  1;       /*当接收机检测到DSRn信号的边沿变化时，该中断原始位变为高电平。*/
            uint32_t cts_chg:                  1;       /*当接收机检测到CTSn信号的边沿变化时，该中断原始位变为高电平。*/
            uint32_t brk_det:                  1;       /*当接收器在停止位之后检测到0时，该中断原始位变为高电平。*/
            uint32_t rxfifo_tout:              1;       /*当接收器接收一个字节的时间超过rx_tout_thhd时，该中断原始位变为高电平。*/
            uint32_t sw_xon:                   1;       /*当uart_sw_flow_con_en设置为1时，当接收器接收到Xon字符时，该中断原始位变为高电平。*/
            uint32_t sw_xoff:                  1;       /*当uart_sw_flow_con_en设置为1时，当接收器接收到Xoff字符时，该中断原始位变为高电平。*/
            uint32_t glitch_det:               1;       /*当接收器检测到起始位中间出现故障时，该中断原始位变为高电平。*/
            uint32_t tx_brk_done:              1;       /*在发送Tx FIFO中的所有数据后，当发送器完成发送NULL字符时，该中断原始位变为高电平。*/
            uint32_t tx_brk_idle_done:         1;       /*当发射机在发送最后一个数据后保持最短的持续时间时，该中断原始位变为高电平。*/
            uint32_t tx_done:                  1;       /*当发射机发出FIFO中的所有数据时，该中断原始位变为高电平。*/
            uint32_t rs485_parity_err:         1;       /*当接收机在rs485模式下从发射机回波中检测到奇偶校验错误时，该中断原始位变为高电平。*/
            uint32_t rs485_frm_err:            1;       /*当接收机在rs485模式下从发射机回波中检测到数据帧错误时，该中断原始位变为高电平。*/
            uint32_t rs485_clash:              1;       /*当在rs485模式下检测到发射机和接收机之间的冲突时，该中断原始位变为高电平。*/
            uint32_t at_cmd_char_det:          1;       /*当接收器检测到配置的at_cmd字符时，该中断原始位变为高电平。*/
            uint32_t wakeup:                   1;       /*当输入rxd边缘的变化次数超过浅睡眠模式下reg_active_threshold指定的次数时，此中断原始位变为高电平。*/
            uint32_t reserved20:              12;       /*保留*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rxfifo_full:             1;        /*这是rxfifo_full_int_ena设置为1时rxfify_full_int_raw的状态位。*/
            uint32_t txfifo_empty:            1;        /*这是当txfifo_empty_int_ena设置为1时，txfifo_oempty_int_raw的状态位。*/
            uint32_t parity_err:              1;        /*这是parity_err_int_ena设置为1时parity_err _int_raw的状态位。*/
            uint32_t frm_err:                 1;        /*这是当frm_err_int_ena设置为1时frm_err_int_raw的状态位。*/
            uint32_t rxfifo_ovf:              1;        /*这是当rxfifo_ovf_int_ena设置为1时rxfifo_ovf_int_raw的状态位。*/
            uint32_t dsr_chg:                 1;        /*这是dsr_chg_int_ena设置为1时dsr_chg_int_raw的状态位。*/
            uint32_t cts_chg:                 1;        /*这是当cts_chg_int_ena设置为1时，cts_chg_int_raw的状态位。*/
            uint32_t brk_det:                 1;        /*这是brk_det_int_ena设置为1时brk_dep_int_raw的状态位。*/
            uint32_t rxfifo_tout:             1;        /*这是rxfifo_out_int_ena设置为1时rxfify_out_int_raw的状态位。*/
            uint32_t sw_xon:                  1;        /*这是sw_xon_int_ena设置为1时sw_xon_ent_raw的状态位。*/
            uint32_t sw_xoff:                 1;        /*这是sw_xoff_int_ena设置为1时sw_xoff_int_raw的状态位。*/
            uint32_t glitch_det:              1;        /*这是当glitch_det_int_ena设置为1时，glitch_ded_int_raw的状态位。*/
            uint32_t tx_brk_done:             1;        /*这是当tx_brk_done_int_ena设置为1时，tx_brk_done_int_raw的状态位。*/
            uint32_t tx_brk_idle_done:        1;        /*这是当tx_brk_idle_done_int_ena设置为1时，tx_brk_idle_done_int.raw的stauts位。*/
            uint32_t tx_done:                 1;        /*这是tx_done_int_ena设置为1时tx_done_It_raw的状态位。*/
            uint32_t rs485_parity_err:        1;        /*这是rs485_parity_int_ena设置为1时rs485_parite_err_int_raw的状态位。*/
            uint32_t rs485_frm_err:           1;        /*这是当rs485_fm_err_int_ena设置为1时，rs485_frm_err_int_raw的状态位。*/
            uint32_t rs485_clash:             1;        /*这是rs485_clash_int_ena设置为1时rs485_clash_int_raw的状态位。*/
            uint32_t at_cmd_char_det:         1;        /*这是at_cmd_char_det_int_ena设置为1时at_cmd_det_int_raw的状态位。*/
            uint32_t wakeup:                  1;        /*这是当uart_weakeup_int_ena设置为1时uart_wwakeup_int_raw的状态位。*/
            uint32_t reserved20:             12;        /*保留*/
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rxfifo_full:              1;       /*这是rxifo_full_int_st寄存器的启用位。*/
            uint32_t txfifo_empty:             1;       /*这是txfifo_empty_int_st寄存器的启用位。*/
            uint32_t parity_err:               1;       /*这是parity_err_int_st寄存器的启用位。*/
            uint32_t frm_err:                  1;       /*这是frm_err_int_st寄存器的启用位。*/
            uint32_t rxfifo_ovf:               1;       /*这是rxfifo_ovf_int_st寄存器的启用位。*/
            uint32_t dsr_chg:                  1;       /*这是dsr_chg_int_st寄存器的启用位。*/
            uint32_t cts_chg:                  1;       /*这是cts_chg_int_st寄存器的启用位。*/
            uint32_t brk_det:                  1;       /*这是brk_det_int_st寄存器的启用位。*/
            uint32_t rxfifo_tout:              1;       /*这是rxifo_out_int_st寄存器的启用位。*/
            uint32_t sw_xon:                   1;       /*这是sw_xon_int_st寄存器的启用位。*/
            uint32_t sw_xoff:                  1;       /*这是sw_xoff_int_st寄存器的启用位。*/
            uint32_t glitch_det:               1;       /*这是glizz_det_int_st寄存器的启用位。*/
            uint32_t tx_brk_done:              1;       /*这是tx_brk_done_int_st寄存器的启用位。*/
            uint32_t tx_brk_idle_done:         1;       /*这是tx_brk_idle_done_int_st寄存器的启用位。*/
            uint32_t tx_done:                  1;       /*这是tx_done_int_st寄存器的启用位。*/
            uint32_t rs485_parity_err:         1;       /*这是rs485_parity_err_int_st寄存器的启用位。*/
            uint32_t rs485_frm_err:            1;       /*这是rs485_parity_err_int_st寄存器的启用位。*/
            uint32_t rs485_clash:              1;       /*这是rs485_clash_int_st寄存器的启用位。*/
            uint32_t at_cmd_char_det:          1;       /*这是at_cmd_char_det_int_st寄存器的启用位。*/
            uint32_t wakeup:                   1;       /*这是uart_wakeup_int_st寄存器的启用位。*/
            uint32_t reserved20:              12;       /*保留*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rxfifo_full:              1;       /*设置此位以清除rxifo_full_int_raw中断。*/
            uint32_t txfifo_empty:             1;       /*设置此位以清除txfifo_empty_int_raw中断。*/
            uint32_t parity_err:               1;       /*设置此位以清除parity_err_int_raw中断。*/
            uint32_t frm_err:                  1;       /*设置此位以清除frm_err_int_raw中断。*/
            uint32_t rxfifo_ovf:               1;       /*设置此位以清除rxfifo_ovf_int_raw中断。*/
            uint32_t dsr_chg:                  1;       /*设置此位以清除dsr_chg_int_raw中断。*/
            uint32_t cts_chg:                  1;       /*设置此位以清除cts_chg_int_raw中断。*/
            uint32_t brk_det:                  1;       /*设置此位以清除brk_det_int_raw中断。*/
            uint32_t rxfifo_tout:              1;       /*设置此位以清除rxifo_out_int_raw中断。*/
            uint32_t sw_xon:                   1;       /*设置此位以清除sw_xon_int_raw中断。*/
            uint32_t sw_xoff:                  1;       /*设置此位以清除sw_xoff_int_raw中断。*/
            uint32_t glitch_det:               1;       /*设置此位以清除故障_det_int_raw中断。*/
            uint32_t tx_brk_done:              1;       /*设置此位以清除tx_brk_done_int_raw中断。。*/
            uint32_t tx_brk_idle_done:         1;       /*设置此位以清除tx_brk_idle_done_int_raw中断。*/
            uint32_t tx_done:                  1;       /*设置此位以清除tx_done_int_raw中断。*/
            uint32_t rs485_parity_err:         1;       /*设置此位以清除rs485_parity_err_int_raw中断。*/
            uint32_t rs485_frm_err:            1;       /*设置此位以清除rs485_frm_err_int_raw中断。*/
            uint32_t rs485_clash:              1;       /*设置此位以清除rs485_clash_int_raw中断。*/
            uint32_t at_cmd_char_det:          1;       /*设置此位以清除at_cmd_char_det_int_raw中断。*/
            uint32_t wakeup:                   1;       /*设置此位以清除uart_wakeup_int_raw中断。*/
            uint32_t reserved20:              12;       /*保留*/
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t div_int:    12;                    /*分频因子的整数部分。*/
            uint32_t reserved12:  8;
            uint32_t div_frag:    4;                    /*分频因子的小数部分。*/
            uint32_t reserved24:  8;                    /*保留*/
        };
        uint32_t val;
    } clk_div;
    union {
        struct {
            uint32_t glitch_filt:    8;                 /*当输入脉冲宽度低于该值时，该脉冲被忽略。*/
            uint32_t glitch_filt_en: 1;                 /*设置此位以启用Rx信号滤波器。*/
            uint32_t reserved9:     23;
        };
        uint32_t val;
    } rx_filt;
    union {
        struct {
            uint32_t rxfifo_cnt:10;                     /*在Rx FIFO中存储有效数据的字节数。*/
            uint32_t reserved10: 3;
            uint32_t dsrn:       1;                     /*寄存器表示内部uart dsr信号的电平值。*/
            uint32_t ctsn:       1;                     /*该寄存器表示内部uart cts信号的电平值。*/
            uint32_t rxd:        1;                     /*该寄存器表示内部uart rxd信号的电平值。*/
            uint32_t txfifo_cnt:10;                     /*在Tx FIFO中存储数据的字节数。*/
            uint32_t reserved26: 3;                     /*保留*/
            uint32_t dtrn:       1;                     /*该位表示内部uart dtr信号的电平。*/
            uint32_t rtsn:       1;                     /*该位表示内部uart rts信号的电平。*/
            uint32_t txd:        1;                     /*该位表示内部uart txd信号的电平。*/
        };
        uint32_t val;
    } status;
    union {
        struct {
            uint32_t parity:       1;                   /*此寄存器用于配置奇偶校验模式。*/
            uint32_t parity_en:    1;                   /*设置此位以启用uart奇偶校验。*/
            uint32_t bit_num:      2;                   /*此寄存器用于设置数据长度。*/
            uint32_t stop_bit_num: 2;                   /*该寄存器用于设置停止位的长度。*/
            uint32_t sw_rts:       1;                   /*该寄存器用于配置软件流控制中使用的软件rts信号。*/
            uint32_t sw_dtr:       1;                   /*该寄存器用于配置软件流控制中使用的软件dtr信号。*/
            uint32_t txd_brk:      1;                   /*当发送数据的过程完成时，将此位设置为enbale发射器发送NULL。*/
            uint32_t irda_dplx:    1;                   /*设置此位以启用IrDA环回模式。*/
            uint32_t irda_tx_en:   1;                   /*这是IrDA发射器的启动启用位。*/
            uint32_t irda_wctl:    1;                   /*1’h1:IrDA发射机的第11位与第10位相同。1’0：将IrDA发射器的第11位设置为0。*/
            uint32_t irda_tx_inv:  1;                   /*设置此位以反转IrDA发射器的电平。*/
            uint32_t irda_rx_inv:  1;                   /*设置此位以反转IrDA接收器的电平。*/
            uint32_t loopback:     1;                   /*设置此位以启用uart环回测试模式。*/
            uint32_t tx_flow_en:   1;                   /*设置此位以启用变送器的流量控制功能。*/
            uint32_t irda_en:      1;                   /*设置此位以启用IrDA协议。*/
            uint32_t rxfifo_rst:   1;                   /*设置此位以重置uart接收FIFO。*/
            uint32_t txfifo_rst:   1;                   /*设置此位以重置uart传输FIFO。*/
            uint32_t rxd_inv:      1;                   /*设置此位以反转uart rxd信号的电平值。*/
            uint32_t cts_inv:      1;                   /*设置此位以反转uart cts信号的电平值。*/
            uint32_t dsr_inv:      1;                   /*设置此位以反转uart dsr信号的电平值。*/
            uint32_t txd_inv:      1;                   /*设置此位以反转uart txd信号的电平值。*/
            uint32_t rts_inv:      1;                   /*设置此位以反转uart rts信号的电平值。*/
            uint32_t dtr_inv:      1;                   /*设置此位以反转uart dtr信号的电平值。*/
            uint32_t clk_en:       1;                   /*1'h1：强制打开寄存器时钟。1’0：仅当应用程序写入寄存器时才支持时钟。*/
            uint32_t err_wr_mask:  1;                   /*1’h1：当数据错误时，接收器停止将数据存储到FIFO中。1’0：即使接收到的数据错误，接收器也会存储数据。*/
            uint32_t autobaud_en:  1;                   /*这是检测波特率的启用位。*/
            uint32_t mem_clk_en:   1;                   /*UART存储器时钟门启用信号。*/
            uint32_t reserved29:   3;
        };
        uint32_t val;
    } conf0;
    union {
        struct {
            uint32_t rxfifo_full_thrhd:  9;             /*当接收器接收到的数据超过此寄存器值时，它将产生rxifo_full_int中断。*/
            uint32_t txfifo_empty_thrhd: 9;             /*当Tx FIFO中的数据量小于此寄存器值时，它将产生txfifo_empty_int中断。*/
            uint32_t dis_rx_dat_ovf:     1;             /*禁用UART Rx数据溢出检测。*/
            uint32_t rx_tout_flow_dis:   1;             /*设置此位以在硬件流控制工作时停止累积idle_cnt。*/
            uint32_t rx_flow_en:         1;             /*这是UART接收器的流量启用位。*/
            uint32_t rx_tout_en:         1;             /*这是uart接收器超时功能的启用位。*/
            uint32_t reserved22:        10;
        };
        uint32_t val;
    } conf1;
    union {
        struct {
            uint32_t min_cnt:         12;               /*该寄存器存储低电平脉冲的最小持续时间值。它用于波特率检测过程。*/
            uint32_t reserved12:      20;               /*保留*/
        };
        uint32_t val;
    } lowpulse;
    union {
        struct {
            uint32_t min_cnt:          12;              /*该寄存器存储高电平脉冲的最大持续时间值。它用于波特率检测过程。*/
            uint32_t reserved12:       20;              /*保留*/
        };
        uint32_t val;
    } highpulse;
    union {
        struct {
            uint32_t edge_cnt:    10;                   /*此寄存器存储rxd边缘变化的计数。它用于波特率检测过程。*/
            uint32_t reserved10:  22;                   /*保留*/
        };
        uint32_t val;
    } rxd_cnt;
    union {
        struct {
            uint32_t sw_flow_con_en: 1;                 /*设置此位以启用软件流控制。它与寄存器sw_xon或sw_xoff一起使用。*/
            uint32_t xonoff_del:     1;                 /*设置此位以从接收的数据中删除流控制字符。*/
            uint32_t force_xon:      1;                 /*设置此位以使发射器能够继续发送数据。*/
            uint32_t force_xoff:     1;                 /*设置此位以停止发射器发送数据。*/
            uint32_t send_xon:       1;                 /*设置此位以发送Xon字符。它由硬件自动清除。*/
            uint32_t send_xoff:      1;                 /*设置此位以发送Xoff字符。它由硬件自动清除。*/
            uint32_t reserved6:     26;                 /*保留*/
        };
        uint32_t val;
    } flow_conf;
    union {
        struct {
            uint32_t active_threshold:10;               /*当输入rxd边缘的变化次数超过此寄存器值时，uart从浅睡眠模式激活。*/
            uint32_t reserved10:      22;               /*保留*/
        };
        uint32_t val;
    } sleep_conf;
    union {
        struct {
            uint32_t xoff_threshold: 9;                 /*当Rx FIFO中的数据量大于此寄存器值且uart_sw_flow_con_en设置为1时，它将发送一个Xoff字符。*/
            uint32_t xoff_char:      8;                 /*此寄存器存储Xoff流控制字符。*/
            uint32_t reserved17:    15;                 /*保留*/
        };
        uint32_t val;
    } swfc_conf0;
    union {
        struct {
            uint32_t xon_threshold: 9;                  /*当Rx FIFO中的数据量小于此寄存器值且uart_sw_flow_con_en设置为1时，它将发送Xon字符。*/
            uint32_t xon_char:      8;                  /*此寄存器存储Xon流控制字符。*/
            uint32_t reserved17:   15;                  /*保留*/
        };
        uint32_t val;
    } swfc_conf1;
    union {
        struct {
            uint32_t tx_brk_num: 8;                     /*此寄存器用于配置发送数据过程完成后要发送的0的数量。当txd_brk设置为1时激活。*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } txbrk_conf;
    union {
        struct {
            uint32_t rx_idle_thrhd:10;                  /*当接收机接收一字节数据的时间超过该寄存器值时，它将产生帧结束信号。*/
            uint32_t tx_idle_num:  10;                  /*此寄存器用于配置传输之间的持续时间。*/
            uint32_t reserved20:   12;                  /*保留*/
        };
        uint32_t val;
    } idle_conf;
    union {
        struct {
            uint32_t en:               1;               /*设置此位以选择rs485模式。*/
            uint32_t dl0_en:           1;               /*设置此位以将停止位延迟1位。*/
            uint32_t dl1_en:           1;               /*设置此位以将停止位延迟1位。*/
            uint32_t tx_rx_en:         1;               /*设置此位，使接收器能够在发射器以rs485模式传输数据时接收数据。*/
            uint32_t rx_busy_tx_en:    1;               /*1’h1：当rs485接收器线路繁忙时，启用rs485发射器发送数据。*/
            uint32_t rx_dly_num:       1;               /*该寄存器用于延迟接收机的内部数据信号。*/
            uint32_t tx_dly_num:       4;               /*该寄存器用于延迟变送器的内部数据信号。*/
            uint32_t reserved10:      22;               /*保留*/
        };
        uint32_t val;
    } rs485_conf;
    union {
        struct {
            uint32_t pre_idle_num:16;                   /*该寄存器用于配置接收机接收第一个at_cmd之前的空闲持续时间。*/
            uint32_t reserved16:  16;                   /*保留*/
        };
        uint32_t val;
    } at_cmd_precnt;
    union {
        struct {
            uint32_t post_idle_num:16;                  /*此寄存器用于配置上一个at_cmd和下一个数据之间的持续时间。*/
            uint32_t reserved16:   16;                  /*保留*/
        };
        uint32_t val;
    } at_cmd_postcnt;
    union {
        struct {
            uint32_t rx_gap_tout:16;                    /*此寄存器用于配置at_cmd字符之间的持续时间。*/
            uint32_t reserved16: 16;                    /*保留*/
        };
        uint32_t val;
    } at_cmd_gaptout;
    union {
        struct {
            uint32_t data:        8;                    /*此寄存器用于配置at_cmd字符的内容。*/
            uint32_t char_num:    8;                    /*此寄存器用于配置接收器接收的连续at_cmd字符数。*/
            uint32_t reserved16: 16;                    /*保留*/
        };
        uint32_t val;
    } at_cmd_char;
    union {
        struct {
            uint32_t reserved0:     1;
            uint32_t rx_size:       3;                  /*此寄存器用于配置分配给接收FIFO的内存量。默认值为128字节。*/
            uint32_t tx_size:       3;                  /*该寄存器用于配置分配给传输FIFO的内存量。默认值为128字节。*/
            uint32_t rx_flow_thrhd: 9;                  /*此寄存器用于配置硬件流控制工作时可接收的最大数据量。*/
            uint32_t rx_tout_thrhd:10;                  /*此寄存器用于配置接收器接收一个字节所需的阈值时间。当接收器花费更多时间接收一个字节且rx_tout_en设置为1时，将触发rxifo_out_int中断。*/
            uint32_t force_pd:      1;                  /*设置此位以强制关闭UART存储器。*/
            uint32_t force_pu:      1;                  /*设置此位以强制启动UART存储器。*/
            uint32_t reserved28:    4;
        };
        uint32_t val;
    } mem_conf;
    union {
        struct {
            uint32_t apb_tx_waddr:10;                   /*当软件通过APB写入Tx FIFO时，该寄存器将偏移地址存储在Tx FIFO中。*/
            uint32_t reserved10:   1;                   /*保留*/
            uint32_t tx_raddr:    10;                   /*当Tx FSM通过Tx-FIFO_Ctrl读取数据时，该寄存器将偏移地址存储在Tx FIFO中。*/
            uint32_t reserved21:  11;                   /*保留*/
        };
        uint32_t val;
    } mem_tx_status;
    union {
        struct {
            uint32_t apb_rx_raddr:10;                   /*当软件通过APB从RX FIFO读取数据时，该寄存器将偏移地址存储在RX-FIFO中。UART0为10'100。UART1为10'180。*/
            uint32_t reserved10:   1;                   /*保留*/
            uint32_t rx_waddr:    10;                   /*当Rx-FIFO_Ctrl写入Rx FIFO时，该寄存器将偏移地址存储在Rx FIFO中。UART0为10'100。UART1为10'180。*/
            uint32_t reserved21:  11;                   /*保留*/
        };
        uint32_t val;
    } mem_rx_status;
    union {
        struct {
            uint32_t st_urx_out: 4;                     /*这是接收器的状态寄存器。*/
            uint32_t st_utx_out: 4;                     /*这是变送器的状态寄存器。*/
            uint32_t reserved8: 24;                     /*保留*/
        };
        uint32_t val;
    } fsm_status;
    union {
        struct {
            uint32_t min_cnt:        12;                /*该寄存器存储两个正边缘之间的最小输入时钟计数。它被应用于boudrate检测过程。*/
            uint32_t reserved12:     20;                /*保留*/
        };
        uint32_t val;
    } pospulse;
    union {
        struct {
            uint32_t min_cnt:        12;                /*该寄存器存储两个负边缘之间的最小输入时钟计数。它被应用于boudrate检测过程。*/
            uint32_t reserved12:     20;                /*保留*/
        };
        uint32_t val;
    } negpulse;
    union {
        struct {
            uint32_t sclk_div_b:   6;                   /*分频因子的分母。*/
            uint32_t sclk_div_a:   6;                   /*分频因子的分子。*/
            uint32_t sclk_div_num: 8;                   /*分频因子的整数部分。*/
            uint32_t sclk_sel:     2;                   /*UART时钟源选择。1： 80Mhz 2:8Mhz 3:XTAL。*/
            uint32_t sclk_en:      1;                   /*设置此位以启用UART Tx/Rx时钟。*/
            uint32_t rst_core:     1;                   /*写入1，然后将0写入该位重置UART Tx/Rx。*/
            uint32_t tx_sclk_en:   1;                   /*设置此位以启用UART Tx时钟。*/
            uint32_t rx_sclk_en:   1;                   /*设置此位以启用UART Rx时钟。*/
            uint32_t tx_rst_core:  1;                   /*写入1，然后将0写入该位重置UART Tx。*/
            uint32_t rx_rst_core:  1;                   /*写入1，然后将0写入该位重置UART Rx。*/
            uint32_t reserved28:   4;
        };
        uint32_t val;
    } clk_conf;
    uint32_t date;                                      /*UART版本寄存器*/
    union {
        struct {
            uint32_t id                            :    30;  /*此寄存器用于配置uart_id。*/
            uint32_t high_speed                    :    1;  /*此位用于选择同步模式。1： 寄存器自动同步到UART核心时钟，UART核心应与APB时钟保持一致。0：配置寄存器后，软件需要将1写入UART_REG_UPDATE以同步寄存器。*/
            uint32_t update                        :    1;  /*软件写入1将寄存器同步到UART核心时钟域，并在同步完成后由硬件清除。*/
        };
        uint32_t val;
    } id;
} uart_dev_t;
extern uart_dev_t UART0;
extern uart_dev_t UART1;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_UART_STRUCT_H_ */

