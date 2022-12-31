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
#ifndef _SOC_UART_STRUCT_H_
#define _SOC_UART_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct uart_dev_s {
    union {
        struct {
            uint32_t rw_byte:          8;           /*此寄存器存储rx fifo读取的一字节数据。*/
            uint32_t reserved:         24;
        };
        uint32_t val;
    } fifo;
    union {
        struct {
            uint32_t rxfifo_full:      1;           /*当接收机接收的数据超过（rx_flow_thrhd_h3 rx_flow_thrhd）时，该中断原始位变为高电平。*/
            uint32_t txfifo_empty:     1;           /*当发射机fifo中的数据量小于（（tx_mem_cnttxfifo_cnt）时，该中断原始位变为高电平。*/
            uint32_t parity_err:       1;           /*当接收机检测到数据的奇偶校验错误时，该中断原始位变为高电平。*/
            uint32_t frm_err:          1;           /*当接收器检测到数据的帧错误时，该中断原始位变为高电平。*/
            uint32_t rxfifo_ovf:       1;           /*当接收机接收到的数据超过fifo所能存储的数据时，该中断原始位变为高电平。*/
            uint32_t dsr_chg:          1;           /*当接收机检测到dsrn信号的边沿变化时，该中断原始位变为高电平。*/
            uint32_t cts_chg:          1;           /*当接收机检测到ctsn信号的边沿变化时，该中断原始位变为高电平。*/
            uint32_t brk_det:          1;           /*当接收器检测到停止位之后的0时，该中断原始位变为高电平。*/
            uint32_t rxfifo_tout:      1;           /*当接收器接收一个字节的时间超过rx_tout_thhd时，该中断原始位变为高电平。*/
            uint32_t sw_xon:           1;           /*当接收器接收到uart_sw_flow_con_en设置为1的xoff字符时，该中断原始位变为高电平。*/
            uint32_t sw_xoff:          1;           /*当接收器接收到uart_sw_flow_con_en设置为1的xon字符时，该中断原始位变为高电平。*/
            uint32_t glitch_det:       1;           /*当接收机检测到起始位时，该中断原始位变为高电平。*/
            uint32_t tx_brk_done:      1;           /*当发送器fifo中的所有数据发送完毕后，当发送器完成发送0时，该中断原始位变为高电平。*/
            uint32_t tx_brk_idle_done: 1;           /*当发射机在发送最后一个数据后保持最短的持续时间时，该中断原始位变为高电平。*/
            uint32_t tx_done:          1;           /*当发射机发送fifo中的所有数据时，该中断原始位变为高电平。*/
            uint32_t rs485_parity_err: 1;           /*当rs485检测到奇偶校验错误时，该中断原始位变为高电平。*/
            uint32_t rs485_frm_err:    1;           /*当rs485检测到数据帧错误时，该中断原始位变为高电平。*/
            uint32_t rs485_clash:      1;           /*当rs485检测到发送器和接收器之间的冲突时，该中断原始位变为高电平。*/
            uint32_t at_cmd_char_det:  1;           /*当接收器检测到配置的at_cmd字符时，该中断原始位变为高电平。*/
            uint32_t reserved19:      13;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rxfifo_full:      1;            /*这是rxfifo_full_int_ena设置为1时rxfify_full_int_raw的状态位。*/
            uint32_t txfifo_empty:     1;            /*这是当txfifo_empty_int_ena设置为1时，txfifo_oempty_int_raw的状态位。*/
            uint32_t parity_err:       1;            /*这是parity_err_int_ena设置为1时parity_err _int_raw的状态位。*/
            uint32_t frm_err:          1;            /*这是当fm_err_int_ena设置为1时frm_err_int_raw的状态位。*/
            uint32_t rxfifo_ovf:       1;            /*这是当rxfifo_ovf_int_ena设置为1时rxfifo_ovf_int_raw的状态位。*/
            uint32_t dsr_chg:          1;            /*这是dsr_chg_int_ena设置为1时dsr_chg_int_raw的状态位。*/
            uint32_t cts_chg:          1;            /*这是当cts_chg_int_ena设置为1时，cts_chg_int_raw的状态位。*/
            uint32_t brk_det:          1;            /*这是brk_det_int_ena设置为1时brk_dep_int_raw的状态位。*/
            uint32_t rxfifo_tout:      1;            /*这是rxfifo_out_int_ena设置为1时rxfify_out_int_raw的状态位。*/
            uint32_t sw_xon:           1;            /*这是sw_xon_int_ena设置为1时sw_xon_ent_raw的状态位。*/
            uint32_t sw_xoff:          1;            /*这是sw_xoff_int_ena设置为1时sw_xoff_int_raw的状态位。*/
            uint32_t glitch_det:       1;            /*这是当glitch_det_int_ena设置为1时，glitch_ded_int_raw的状态位。*/
            uint32_t tx_brk_done:      1;            /*这是当tx_brk_done_int_ena设置为1时，tx_brk_done_int_raw的状态位。*/
            uint32_t tx_brk_idle_done: 1;            /*这是当tx_brk_idle_done_int_ena设置为1时，tx_brk_idle_done_int.raw的状态位。*/
            uint32_t tx_done:          1;            /*这是tx_done_int_ena设置为1时tx_done_It_raw的状态位。*/
            uint32_t rs485_parity_err: 1;            /*这是rs485_parity_int_ena设置为1时rs485_parite_err_int_raw的状态位。*/
            uint32_t rs485_frm_err:    1;            /*这是当rs485_fm_err_int_ena设置为1时，rs485_fm_err_int_raw的状态位。*/
            uint32_t rs485_clash:      1;            /*这是rs485_clash_int_ena设置为1时rs485_clash_int_raw的状态位。*/
            uint32_t at_cmd_char_det:  1;            /*这是at_cmd_char_det_int_ena设置为1时at_cmd_det_int_raw的状态位。*/
            uint32_t reserved19:      13;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rxfifo_full:      1;           /*这是rxifo_full_int_st寄存器的启用位。*/
            uint32_t txfifo_empty:     1;           /*这是rxifo_full_int_st寄存器的启用位。*/
            uint32_t parity_err:       1;           /*这是parity_err_int_st寄存器的启用位。*/
            uint32_t frm_err:          1;           /*这是frm_err_int_st寄存器的启用位。*/
            uint32_t rxfifo_ovf:       1;           /*这是rxfifo_ovf_int_st寄存器的启用位。*/
            uint32_t dsr_chg:          1;           /*这是dsr_chg_int_st寄存器的启用位。*/
            uint32_t cts_chg:          1;           /*这是cts_chg_int_st寄存器的启用位。*/
            uint32_t brk_det:          1;           /*这是brk_det_int_st寄存器的启用位。*/
            uint32_t rxfifo_tout:      1;           /*这是rxifo_out_int_st寄存器的启用位。*/
            uint32_t sw_xon:           1;           /*这是sw_xon_int_st寄存器的启用位。*/
            uint32_t sw_xoff:          1;           /*这是sw_xoff_int_st寄存器的启用位。*/
            uint32_t glitch_det:       1;           /*这是glizz_det_int_st寄存器的启用位。*/
            uint32_t tx_brk_done:      1;           /*这是tx_brk_done_int_st寄存器的启用位。*/
            uint32_t tx_brk_idle_done: 1;           /*这是tx_brk_idle_done_int_st寄存器的启用位。*/
            uint32_t tx_done:          1;           /*这是tx_done_int_st寄存器的启用位。*/
            uint32_t rs485_parity_err: 1;           /*这是rs485_parity_err_int_st寄存器的启用位。*/
            uint32_t rs485_frm_err:    1;           /*这是rs485_parity_err_int_st寄存器的启用位。*/
            uint32_t rs485_clash:      1;           /*这是rs485_clash_int_st寄存器的启用位。*/
            uint32_t at_cmd_char_det:  1;           /*这是at_cmd_char_det_int_st寄存器的启用位。*/
            uint32_t reserved19:      13;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rxfifo_full:      1;           /*设置此位以清除rxifo_full_int_raw中断。*/
            uint32_t txfifo_empty:     1;           /*设置此位以清除txfifo_empty_int_raw中断。*/
            uint32_t parity_err:       1;           /*设置此位以清除parity_err_int_raw中断。*/
            uint32_t frm_err:          1;           /*设置此位以清除frm_err_int_raw中断。*/
            uint32_t rxfifo_ovf:       1;           /*设置此位以清除rxfifo_ovf_int_raw中断。*/
            uint32_t dsr_chg:          1;           /*设置此位以清除dsr_chg_int_raw中断。*/
            uint32_t cts_chg:          1;           /*设置此位以清除cts_chg_int_raw中断。*/
            uint32_t brk_det:          1;           /*设置此位以清除brk_det_int_raw中断。*/
            uint32_t rxfifo_tout:      1;           /*设置此位以清除rxifo_out_int_raw中断。*/
            uint32_t sw_xon:           1;           /*设置此位以清除sw_xon_int_raw中断。*/
            uint32_t sw_xoff:          1;           /*设置此位以清除sw_xon_int_raw中断。*/
            uint32_t glitch_det:       1;           /*设置此位以清除故障_det_int_raw中断。*/
            uint32_t tx_brk_done:      1;           /*设置此位以清除tx_brk_done_int_raw中断。。*/
            uint32_t tx_brk_idle_done: 1;           /*设置此位以清除tx_brk_idle_done_int_raw中断。*/
            uint32_t tx_done:          1;           /*设置此位以清除tx_done_int_raw中断。*/
            uint32_t rs485_parity_err: 1;           /*设置此位以清除rs485_parity_err_int_raw中断。*/
            uint32_t rs485_frm_err:    1;           /*设置此位以清除rs485_frm_err_int_raw中断。*/
            uint32_t rs485_clash:      1;           /*设置此位以清除rs485_clash_int_raw中断。*/
            uint32_t at_cmd_char_det:  1;           /*设置此位以清除at_cmd_char_det_int_raw中断。*/
            uint32_t reserved19:      13;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t div_int:    20;                /*寄存器值是分频器因数的整数部分。*/
            uint32_t div_frag:    4;                /*寄存器值是分频器系数的小数部分。*/
            uint32_t reserved24:  8;
        };
        uint32_t val;
    } clk_div;
    union {
        struct {
            uint32_t en: 1;                         /*这是检测波特率的启用位。*/
            uint32_t reserved1:   7;
            uint32_t glitch_filt: 8;                /*当输入脉冲宽度低于该值时，忽略该脉冲。该寄存器用于自动波特率检测过程。*/
            uint32_t reserved16: 16;
        };
        uint32_t val;
    } auto_baud;
    union {
        struct {
            uint32_t rxfifo_cnt: 8;                 /*（rx_mem_cntrxfifo_cnt）存储接收器fifo中有效数据的字节数。rxmem_cnt寄存器存储3个最高有效位，rxifo_cnt存储8个最低有效位。*/
            uint32_t st_urx_out: 4;                 /*该寄存器存储接收器的有限状态机的值。0:RX空闲1:RX字符串2:RX数据3:RX数据4:RX数据5:RX数据6:RX数据7:RX数据8:RX数据9:RX数据10:RX数据11:RX STP1 12:RX STP2 13:RX DL1*/
            uint32_t reserved12: 1;
            uint32_t dsrn:       1;                 /*该寄存器存储内部uart dsr信号的电平值。*/
            uint32_t ctsn:       1;                 /*该寄存器存储内部uart cts信号的电平值。*/
            uint32_t rxd:        1;                 /*该寄存器存储内部uart rxd信号的电平值。*/
            uint32_t txfifo_cnt: 8;                 /*（tx_mem_cnt txfifo cnt）存储发射机fifo中有效数据的字节数。tx_mem_cnt存储3个最高有效位txfifo_cnt存储8个最低有效位。*/
            uint32_t st_utx_out: 4;                 /*该寄存器存储发射机的有限状态机的值。0:TX_IDLE 1:TX_STRT 2:TX_DAT0 3:TX_DAT1 4:TX_DAT2 5:TX_DAT3 6:TX_DAT4 7:TX_DAT5 8:TX_DAT6 9:TX_DAT7 10:TX_PRTY 11:TX_STP1 12:TX_STP2 13:TX_DL0 14:TX_DL1*/
            uint32_t reserved28: 1;
            uint32_t dtrn:       1;                 /*寄存器表示内部uart dsr信号的电平值。*/
            uint32_t rtsn:       1;                 /*该寄存器表示内部uart cts信号的电平值。*/
            uint32_t txd:        1;                 /*该寄存器表示内部uart rxd信号的电平值。*/
        };
        uint32_t val;
    } status;
    union {
        struct {
            uint32_t parity:             1;         /*此寄存器用于配置奇偶校验模式。0：偶数1：奇数*/
            uint32_t parity_en:          1;         /*设置此位以启用uart奇偶校验。*/
            uint32_t bit_num:            2;         /*此寄存器用于设置数据长度：0:5位1:6位2:7位3:8位*/
            uint32_t stop_bit_num:       2;         /*该寄存器用于设置停止位的长度。1： 1位2:1.5位3:2位*/
            uint32_t sw_rts:             1;         /*该寄存器用于配置软件流控制中使用的软件rts信号。*/
            uint32_t sw_dtr:             1;         /*该寄存器用于配置软件流控制中使用的软件dtr信号。。*/
            uint32_t txd_brk:            1;         /*设置此位，使变送器在发送数据过程完成时发送0。*/
            uint32_t irda_dplx:          1;         /*设置此位以启用irda环回模式。*/
            uint32_t irda_tx_en:         1;         /*这是irda发射器的启动启用位。*/
            uint32_t irda_wctl:          1;         /*1： irda发射机的第11位与第10位相同。0：将irda发射器的第11位设置为0。*/
            uint32_t irda_tx_inv:        1;         /*设置此位以反转irda发射器电平的电平值。*/
            uint32_t irda_rx_inv:        1;         /*设置此位以反转irda接收机电平的电平值。*/
            uint32_t loopback:           1;         /*设置此位以启用uart环回测试模式。*/
            uint32_t tx_flow_en:         1;         /*设置此位以启用变送器的流量控制功能。*/
            uint32_t irda_en:            1;         /*设置此位以启用irda协议。*/
            uint32_t rxfifo_rst:         1;         /*设置此位以重置uart接收器的fifo。*/
            uint32_t txfifo_rst:         1;         /*设置此位以重置uart发射器的fifo。*/
            uint32_t rxd_inv:            1;         /*设置此位以反转uart rxd信号的电平值。*/
            uint32_t cts_inv:            1;         /*设置此位以反转uart cts信号的电平值。*/
            uint32_t dsr_inv:            1;         /*设置此位以反转uart dsr信号的电平值。*/
            uint32_t txd_inv:            1;         /*设置此位以反转uart txd信号的电平值。*/
            uint32_t rts_inv:            1;         /*设置此位以反转uart rts信号的电平值。*/
            uint32_t dtr_inv:            1;         /*设置此位以反转uart dtr信号的电平值。*/
            uint32_t clk_en:             1;         /*1： 为寄存器强制时钟：仅在写入寄存器时支持时钟*/
            uint32_t err_wr_mask:        1;         /*1： 当数据错误时，接收机停止在fifo中存储数据。0：即使接收到的数据错误，接收器也会存储数据。*/
            uint32_t tick_ref_always_on: 1;         /*该寄存器用于选择时钟。1： apb时钟：ref_tick*/
            uint32_t reserved28:         4;
        };
        uint32_t val;
    } conf0;
    union {
        struct {
            uint32_t rxfifo_full_thrhd:  7;         /*当接收器接收到的数据超过其阈值时，接收器将产生rxifo_full_int_raw中断。阈值是（rx_flow_thrhd_h3 rxfiff_full_thrhd）。*/
            uint32_t reserved7:          1;
            uint32_t txfifo_empty_thrhd: 7;         /*当发射机fifo中的数据量小于其阈值时，它将产生txfifoemptyintraw中断。阈值为（tx_mem_empty_thrd txfifoempty.thrd）*/
            uint32_t reserved15:         1;
            uint32_t rx_flow_thrhd:      7;         /*当接收机接收到的数据超过其阈值时，接收机产生信号通知发射机停止传输数据。阈值是（rx_flow_thrhd_h3 rx-flow_thrhd）。*/
            uint32_t rx_flow_en:         1;         /*这是uart接收器的流启用位。1： 通过配置sw_rts信号选择软件流控制*/
            uint32_t rx_tout_thrhd:      7;         /*此寄存器用于配置uart接收器接收字节的超时值。*/
            uint32_t rx_tout_en:         1;         /*这是uart接收器超时功能的启用位。*/
        };
        uint32_t val;
    } conf1;
    union {
        struct {
            uint32_t min_cnt:     20;               /*该寄存器存储低电平脉冲的最小持续时间值，用于波特率检测过程。*/
            uint32_t reserved20:  12;
        };
        uint32_t val;
    } lowpulse;
    union {
        struct {
            uint32_t min_cnt:     20;               /*该寄存器存储高电平脉冲的最大持续时间值，用于波特率检测过程。*/
            uint32_t reserved20:  12;
        };
        uint32_t val;
    } highpulse;
    union {
        struct {
            uint32_t edge_cnt:    10;               /*该寄存器存储rxd边缘变化的计数，用于波特率检测过程。*/
            uint32_t reserved10:  22;
        };
        uint32_t val;
    } rxd_cnt;
    union {
        struct {
            uint32_t sw_flow_con_en: 1;             /*设置此位以启用软件流控制。它与寄存器swxon或swxoff一起使用。*/
            uint32_t xonoff_del:     1;             /*设置此位以从接收的数据中删除流控制字符。*/
            uint32_t force_xon:      1;             /*设置此位以清除ctsn，以停止发射器发送数据。*/
            uint32_t force_xoff:     1;             /*设置此位以设置ctsn，使发射器能够继续发送数据。*/
            uint32_t send_xon:       1;             /*设置此位以发送xon字符，硬件会自动清除。*/
            uint32_t send_xoff:      1;             /*设置此位以发送xoff字符，硬件会自动清除。*/
            uint32_t reserved6:     26;
        };
        uint32_t val;
    } flow_conf;
    union {
        struct {
            uint32_t active_threshold:10;           /*当输入rxd边缘的变化超过该寄存器值时，uart从浅睡眠模式激活。*/
            uint32_t reserved10:      22;
        };
        uint32_t val;
    } sleep_conf;
    union {
        struct {
            uint32_t xon_threshold:  8;             /*当接收器fifo中的数据量大于此寄存器值时，它将发送一个uart_swflow_conn设置为1的xoff字符。*/
            uint32_t xoff_threshold: 8;             /*当接收器fifo中的数据量小于此寄存器值时，它将发送一个uart_sw_flow_con_en设置为1的xon字符。*/
            uint32_t xon_char:       8;             /*此寄存器存储xon流控制字符。*/
            uint32_t xoff_char:      8;             /*此寄存器存储xoff流控制字符。*/
        };
        uint32_t val;
    } swfc_conf;
    union {
        struct {
            uint32_t rx_idle_thrhd:10;              /*当接收机接收字节数据所花费的时间超过该寄存器值时，它将产生帧结束信号，以便uhci停止接收数据。*/
            uint32_t tx_idle_num:  10;              /*此寄存器用于配置传输之间的持续时间。*/
            uint32_t tx_brk_num:    8;              /*此寄存器用于在发送数据的过程完成后配置0发送的数量。当txd_brk设置为1时，它是活动的。*/
            uint32_t reserved28:    4;
        };
        uint32_t val;
    } idle_conf;
    union {
        struct {
            uint32_t en:               1;           /*设置此位以选择rs485模式。*/
            uint32_t dl0_en:           1;           /*设置此位以将停止位延迟1位。*/
            uint32_t dl1_en:           1;           /*设置此位以将停止位延迟1位。*/
            uint32_t tx_rx_en:         1;           /*设置此位以启用将发射器的输出数据信号环回至接收器的输入数据信号。*/
            uint32_t rx_busy_tx_en:    1;           /*1： 当rs485的接收机忙时，启用rs485的发射机发送数据。0:rs485的发射机在接收机忙时不应发送数据。*/
            uint32_t rx_dly_num:       1;           /*该寄存器用于延迟接收机的内部数据信号。*/
            uint32_t tx_dly_num:       4;           /*该寄存器用于延迟变送器的内部数据信号。*/
            uint32_t reserved10:      22;
        };
        uint32_t val;
    } rs485_conf;
    union {
        struct {
            uint32_t pre_idle_num:24;               /*此寄存器用于配置接收器接收第一个at_cmd之前的空闲持续时间，当持续时间小于此寄存器值时，它不会将接收到的下一个数据作为at_cmd字符。*/
            uint32_t reserved24:   8;
        };
        uint32_t val;
    } at_cmd_precnt;
    union {
        struct {
            uint32_t post_idle_num:24;              /*此寄存器用于配置上一个at_cmd和下一个数据之间的持续时间，当持续时间小于此寄存器值时，它不会将上一个数据作为at_cmd字符。*/
            uint32_t reserved24:    8;
        };
        uint32_t val;
    } at_cmd_postcnt;
    union {
        struct {
            uint32_t rx_gap_tout:24;                /*此寄存器用于配置at_cmd字符之间的持续时间，当持续时间小于此寄存器值时，它不会将数据视为连续的at_cmd字符串。*/
            uint32_t reserved24:  8;
        };
        uint32_t val;
    } at_cmd_gaptout;
    union {
        struct {
            uint32_t data:        8;                /*此寄存器用于配置at_cmd字符的内容。*/
            uint32_t char_num:    8;                /*此寄存器用于配置接收器接收的连续at_cmd字符数。*/
            uint32_t reserved16: 16;
        };
        uint32_t val;
    } at_cmd_char;
    union {
        struct {
            uint32_t mem_pd:             1;         /*将此位设置为关闭内存，当3个uart中的reg_mem_pd寄存器都设置为1时，内存将进入低功耗模式。*/
            uint32_t reserved1:          1;
            uint32_t reserved2:          1;
            uint32_t rx_size:            4;         /*该寄存器用于配置分配给接收机fifo的内存量。默认字节num为128。*/
            uint32_t tx_size:            4;         /*该寄存器用于配置分配给发射机fifo的内存量。默认字节num为128。*/
            uint32_t reserved11:         4;
            uint32_t rx_flow_thrhd_h3:   3;         /*请参考rx-flow_thrhd的描述。*/
            uint32_t rx_tout_thrhd_h3:   3;         /*请参阅rxtout_thhd的描述。*/
            uint32_t xon_threshold_h2:   2;         /*请参阅uart_xon_threshold的描述。*/
            uint32_t xoff_threshold_h2:  2;         /*请参阅uart_xoff_threshold的描述。*/
            uint32_t rx_mem_full_thrhd:  3;         /*请参阅rxfiffullthhd的描述。*/
            uint32_t tx_mem_empty_thrhd: 3;         /*请参阅txfifoempty_thrd的描述。*/
            uint32_t reserved31:         1;
        };
        uint32_t val;
    } mem_conf;
    union {
        struct {
            uint32_t status:24;
            uint32_t reserved24:    8;
        };
        uint32_t val;
    } mem_tx_status;
    union {
        struct {
            uint32_t status:      24;
            uint32_t reserved24:   8;
        };
        struct {
            uint32_t reserved0:     2;
            uint32_t rd_addr:      11;              /*此寄存器存储rx mem读取地址。*/
            uint32_t wr_addr:      11;              /*此寄存器存储rx mem写地址。*/
            uint32_t reserved:      8;
        };
        uint32_t val;
    } mem_rx_status;
    union {
        struct {
            uint32_t rx_cnt: 3;                      /*请参阅rxfifcnt的描述。*/
            uint32_t tx_cnt: 3;                      /*请参阅txfifocnt的说明。*/
            uint32_t reserved6: 26;
        };
        uint32_t val;
    } mem_cnt_status;
    union {
        struct {
            uint32_t min_cnt:     20;                 /*此寄存器存储rxd pos边缘计数，用于波特率检测过程。*/
            uint32_t reserved20:  12;
        };
        uint32_t val;
    } pospulse;
    union {
        struct {
            uint32_t min_cnt:     20;                 /*该寄存器存储rxd负边缘计数，用于波特率检测过程。*/
            uint32_t reserved20:  12;
        };
        uint32_t val;
    } negpulse;
    uint32_t reserved_70;
    uint32_t reserved_74;
    uint32_t date;                                    /**/
    uint32_t id;                                      /**/
} uart_dev_t;
extern uart_dev_t UART0;
extern uart_dev_t UART1;
extern uart_dev_t UART2;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_UART_STRUCT_H_ */

