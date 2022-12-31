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
#ifndef _SOC_UHCI_STRUCT_H_
#define _SOC_UHCI_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct uhci_dev_s {
    union {
        struct {
            uint32_t in_rst:             1;                /*设置此位以在链接操作中重置。*/
            uint32_t out_rst:            1;                /*设置此位以重置链接操作。*/
            uint32_t ahbm_fifo_rst:      1;                /*设置此位以重置dma ahb fifo。*/
            uint32_t ahbm_rst:           1;                /*设置此位以重置dma ahb接口。*/
            uint32_t in_loop_test:       1;                /*设置此位以启用in链接的循环测试。*/
            uint32_t out_loop_test:      1;                /*设置此位以启用输出链接的循环测试。*/
            uint32_t out_auto_wrback:    1;                /*当in链接的长度为0时，继续自动使用下一个in链接。*/
            uint32_t out_no_restart_clr: 1;                /*不要使用*/
            uint32_t out_eof_mode:       1;                /*设置此位以在DMA弹出所有数据后生成eof，清除此位以使DMA推送所有数据后产生eof*/
            uint32_t uart0_ce:           1;                /*设置此位以使用UART发送或接收数据。*/
            uint32_t uart1_ce:           1;                /*设置此位以使用UART1发送或接收数据。*/
            uint32_t uart2_ce:           1;                /*设置此位以使用UART2发送或接收数据。*/
            uint32_t outdscr_burst_en:   1;                /*设置此位以启用链接中的DMA以使用突发模式。*/
            uint32_t indscr_burst_en:    1;                /*设置此位以启用DMA输出链接以使用突发模式。*/
            uint32_t out_data_burst_en:  1;                /*设置此位以启用DMA突发模式*/
            uint32_t mem_trans_en:       1;
            uint32_t seper_en:           1;                /*设置此位以使用特殊字符分隔数据帧。*/
            uint32_t head_en:            1;                /*设置此位以启用在数据帧之前使用头数据包。*/
            uint32_t crc_rec_en:         1;                /*当头包中的crc_en位为1时，设置此位以启用接收器的crc计算能力，则data_frame之后将有crc字节*/
            uint32_t uart_idle_eof_en:   1;                /*当满足数据帧后的空闲时间时，设置该位以启用空闲时间，这意味着数据帧的结束。*/
            uint32_t len_eof_en:         1;                /*当接收到的数据等于packet_len时，设置此位以启用在包头中使用packet_ln，这意味着数据帧的结束。*/
            uint32_t encode_crc_en:      1;                /*当头包中的位6为1时，设置此位以启用数据帧的crc计算。*/
            uint32_t clk_en:             1;                /*设置此位以启用读或写寄存器的时钟门控。*/
            uint32_t uart_rx_brk_eof_en: 1;                /*设置此位以启用brk字符作为数据帧的结尾。*/
            uint32_t reserved24:         8;
        };
        uint32_t val;
    } conf0;
    union {
        struct {
            uint32_t rx_start:            1;               /*发送分隔符字符后，将产生uhcirxstartint中断。*/
            uint32_t tx_start:            1;               /*当DMA检测到分隔符字符时，它将产生uhci_tx_start_int中断。*/
            uint32_t rx_hung:             1;               /*当DMA花费大量时间接收数据时，它将产生uhci_rx_hung_int中断。*/
            uint32_t tx_hung:             1;               /*当DMA花费大量时间从RAM读取数据时，它将产生uhci_tx_hung_int中断。*/
            uint32_t in_done:             1;               /*当一个链路内描述符完成时，它将产生uhci_indoneint中断。*/
            uint32_t in_suc_eof:          1;               /*当接收到数据包时，它将产生uhci_in_suc_eof_int中断。*/
            uint32_t in_err_eof:          1;               /*当链接描述符中的eof出现一些错误时，它将产生uhciin_err_eofint中断。*/
            uint32_t out_done:            1;               /*当一个输出链路描述符完成时，它将产生uhci_outdoneint中断。*/
            uint32_t out_eof:             1;               /*当当前描述符的eof位为1时，它将产生uhci_out_eof_int中断。*/
            uint32_t in_dscr_err:         1;               /*当出链路描述符出现一些错误时，它将产生uhci_indscr_errint中断。*/
            uint32_t out_dscr_err:        1;               /*当链路内描述符出现一些错误时，它将产生uhcioutdscrerrint中断。*/
            uint32_t in_dscr_empty:       1;               /*当DMA没有足够的内部链路时，它将产生uhci_in_dscr_err_int中断。*/
            uint32_t outlink_eof_err:     1;               /*当outlink描述符中存在一些关于eof的错误时，它将产生uhci_outlinkeof_errint中断。*/
            uint32_t out_total_eof:       1;               /*当所有数据被发送后，它将产生uhci_out_total_eof_int中断。*/
            uint32_t send_s_q:            1;               /*当使用单个发送寄存器发送短数据包时，当dma发送了短数据包后，将产生此中断。*/
            uint32_t send_a_q:            1;               /*当使用always_send寄存器发送一系列短数据包时，当dma发送了短数据包后，它将产生此中断。*/
            uint32_t dma_in_fifo_full_wm: 1;
            uint32_t reserved17:         15;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rx_start:            1;
            uint32_t tx_start:            1;
            uint32_t rx_hung:             1;
            uint32_t tx_hung:             1;
            uint32_t in_done:             1;
            uint32_t in_suc_eof:          1;
            uint32_t in_err_eof:          1;
            uint32_t out_done:            1;
            uint32_t out_eof:             1;
            uint32_t in_dscr_err:         1;
            uint32_t out_dscr_err:        1;
            uint32_t in_dscr_empty:       1;
            uint32_t outlink_eof_err:     1;
            uint32_t out_total_eof:       1;
            uint32_t send_s_q:            1;
            uint32_t send_a_q:            1;
            uint32_t dma_in_fifo_full_wm: 1;
            uint32_t reserved17:         15;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rx_start:            1;
            uint32_t tx_start:            1;
            uint32_t rx_hung:             1;
            uint32_t tx_hung:             1;
            uint32_t in_done:             1;
            uint32_t in_suc_eof:          1;
            uint32_t in_err_eof:          1;
            uint32_t out_done:            1;
            uint32_t out_eof:             1;
            uint32_t in_dscr_err:         1;
            uint32_t out_dscr_err:        1;
            uint32_t in_dscr_empty:       1;
            uint32_t outlink_eof_err:     1;
            uint32_t out_total_eof:       1;
            uint32_t send_s_q:            1;
            uint32_t send_a_q:            1;
            uint32_t dma_in_fifo_full_wm: 1;
            uint32_t reserved17:         15;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rx_start:            1;
            uint32_t tx_start:            1;
            uint32_t rx_hung:             1;
            uint32_t tx_hung:             1;
            uint32_t in_done:             1;
            uint32_t in_suc_eof:          1;
            uint32_t in_err_eof:          1;
            uint32_t out_done:            1;
            uint32_t out_eof:             1;
            uint32_t in_dscr_err:         1;
            uint32_t out_dscr_err:        1;
            uint32_t in_dscr_empty:       1;
            uint32_t outlink_eof_err:     1;
            uint32_t out_total_eof:       1;
            uint32_t send_s_q:            1;
            uint32_t send_a_q:            1;
            uint32_t dma_in_fifo_full_wm: 1;
            uint32_t reserved17:         15;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t full:       1;                      /*1： DMA输出链接描述符的fifo已满。*/
            uint32_t empty:      1;                      /*1： 链接描述符的fifo中的DMA为空。*/
            uint32_t reserved2: 30;
        };
        uint32_t val;
    } dma_out_status;
    union {
        struct {
            uint32_t fifo_wdata: 9;                      /*这是需要将数据推送到链接描述符的fifo中。*/
            uint32_t reserved9:  7;
            uint32_t fifo_push:  1;                      /*设置此位以将数据推送到链接描述符的fifo中。*/
            uint32_t reserved17:15;
        };
        uint32_t val;
    } dma_out_push;
    union {
        struct {
            uint32_t full:         1;
            uint32_t empty:        1;
            uint32_t reserved2:    2;
            uint32_t rx_err_cause: 3;                    /*该寄存器存储在外链路描述符的数据包中引起的错误。*/
            uint32_t reserved7:   25;
        };
        uint32_t val;
    } dma_in_status;
    union {
        struct {
            uint32_t fifo_rdata:  12;                    /*该寄存器存储从链接描述符的fifo中弹出的数据。*/
            uint32_t reserved12:   4;
            uint32_t fifo_pop:     1;                    /*设置此位以在链接描述符的fifo中弹出数据。*/
            uint32_t reserved17:  15;
        };
        uint32_t val;
    } dma_in_pop;
    union {
        struct {
            uint32_t addr:         20;                   /*该寄存器存储第一个出链路描述符的地址的至少20位。*/
            uint32_t reserved20:    8;
            uint32_t stop:          1;                   /*设置此位以停止处理输出链接描述符。*/
            uint32_t start:         1;                   /*设置此位以开始处理输出链接描述符。*/
            uint32_t restart:       1;                   /*设置此位以装入新的输出链接描述符*/
            uint32_t park:          1;                   /*1： 输出链路描述符的fsm处于空闲状态。0:输出链接描述符的fsm正在工作。*/
        };
        uint32_t val;
    } dma_out_link;
    union {
        struct {
            uint32_t addr:       20;                     /*该寄存器存储第一个链路内描述符地址的至少20位。*/
            uint32_t auto_ret:    1;                     /*1： 当数据包在链路描述符中出错时，返回到最近使用的描述符。*/
            uint32_t reserved21:  7;
            uint32_t stop:        1;                     /*设置此位以停止处理链接内描述符。*/
            uint32_t start:       1;                     /*设置此位以开始处理链接内描述符。*/
            uint32_t restart:     1;                     /*设置此位以装入新的链接内描述符*/
            uint32_t park:        1;                     /*1： 链路内描述符的fsm处于空闲状态。0:链接内描述符的fsm正在工作*/
        };
        uint32_t val;
    } dma_in_link;
    union {
        struct {
            uint32_t check_sum_en:          1;            /*设置此位以使解码器能够检查数据包标头中的check_sum。*/
            uint32_t check_seq_en:          1;            /*设置此位以使解码器能够检查数据包标头中的序列号。*/
            uint32_t crc_disable:           1;            /*设置此位以禁用crc计算。*/
            uint32_t save_head:             1;            /*设置此位以保存数据包标头。*/
            uint32_t tx_check_sum_re:       1;            /*设置此位以启用硬件自动替换数据包标头中的check_sum。*/
            uint32_t tx_ack_num_re:         1;            /*设置此位以启用硬件自动替换数据包标头中的ack num。*/
            uint32_t check_owner:           1;            /*设置此位以检查链接描述符中的所有者位。*/
            uint32_t wait_sw_start:         1;            /*设置此位以启用软件方式添加数据包标头。*/
            uint32_t sw_start:              1;            /*设置此位以开始插入数据包标头。*/
            uint32_t dma_in_fifo_full_thrs:12;            /*当链接描述符的fifo中的数据量大于该寄存器值时，将产生uhcidma_in_fifofull_wm_int中断。*/
            uint32_t reserved21:           11;
        };
        uint32_t val;
    } conf1;
    uint32_t state0;                                       /**/
    uint32_t state1;                                       /**/
    uint32_t dma_out_eof_des_addr;                         /*当该描述符中的eof位为1时，该寄存器存储出链路描述的地址。*/
    uint32_t dma_in_suc_eof_des_addr;                      /*当该描述符中的eof位为1时，该寄存器存储链路内描述符的地址。*/
    uint32_t dma_in_err_eof_des_addr;                      /*当此描述符中存在一些错误时，此寄存器存储链接内描述符的地址。*/
    uint32_t dma_out_eof_bfr_des_addr;                     /*当此描述符中存在一些错误时，此寄存器存储出链路描述符的地址。*/
    union {
        struct {
            uint32_t test_mode:   3;                       /*bit2是ahb总线测试启用，bit1用于选择写（1）或读（0）模式。bit0用于选择仅测试一次（1）或继续（0）*/
            uint32_t reserved3:   1;
            uint32_t test_addr:   2;                       /*这两位代表ahb总线地址位[20:19]*/
            uint32_t reserved6:  26;
        };
        uint32_t val;
    } ahb_test;
    uint32_t dma_in_dscr;                                  /*当前链接描述符的第三个dword的内容*/
    uint32_t dma_in_dscr_bf0;                              /*当前链接描述符的第一个dword的内容*/
    uint32_t dma_in_dscr_bf1;                              /*当前链接描述符的第二个dword的内容*/
    uint32_t dma_out_dscr;                                 /*当前输出链接描述符的第三个dword的内容*/
    uint32_t dma_out_dscr_bf0;                             /*当前输出链接描述符的第一个dword的内容*/
    uint32_t dma_out_dscr_bf1;                             /*当前输出链接描述符的第二个dword的内容*/
    union {
        struct {
            uint32_t tx_c0_esc_en: 1;                      /*设置此位以在DMA接收数据时启用0xc0字符解码。*/
            uint32_t tx_db_esc_en: 1;                      /*设置此位以在DMA接收数据时启用0xdb字符解码。*/
            uint32_t tx_11_esc_en: 1;                      /*设置此位以在DMA接收数据时启用流控制字符0x11解码。*/
            uint32_t tx_13_esc_en: 1;                      /*设置此位以在DMA接收数据时启用流控制字符0x13解码。*/
            uint32_t rx_c0_esc_en: 1;                      /*设置此位以在DMA发送数据时启用0xc0字符替换。*/
            uint32_t rx_db_esc_en: 1;                      /*设置此位以在DMA发送数据时启用0xdb字符替换。*/
            uint32_t rx_11_esc_en: 1;                      /*设置此位以在DMA发送数据时启用流控制字符0x11替换。*/
            uint32_t rx_13_esc_en: 1;                      /*设置此位以在DMA发送数据时启用流控制字符0x13替换。*/
            uint32_t reserved8:   24;
        };
        uint32_t val;
    } escape_conf;
    union {
        struct {
            uint32_t txfifo_timeout:       8;              /*此寄存器存储超时值。当DMA接收数据的时间超过此寄存器值时，它将产生uhci_tx_hung_int中断。*/
            uint32_t txfifo_timeout_shift: 3;              /*当刻度计数的值>=（17'd8000>>reg_txfifo_timeout_shift）时，将清除刻度计数*/
            uint32_t txfifo_timeout_ena:   1;              /*tx fifo接收数据超时的启用位*/
            uint32_t rxfifo_timeout:       8;              /*该寄存器存储超时值。当DMA从RAM读取数据所花费的时间超过该寄存器值时，将产生uhci_rx_hung_int中断。*/
            uint32_t rxfifo_timeout_shift: 3;              /*当刻度计数的值>=（17'd8000>>reg_rxfifo_timeout_shift）时，将清除刻度计数*/
            uint32_t rxfifo_timeout_ena:   1;              /*这是DMA发送数据超时的启用位*/
            uint32_t reserved24:           8;
        };
        uint32_t val;
    } hung_conf;
    uint32_t ack_num;                                      /**/
    uint32_t rx_head;                                      /*该寄存器存储DMA接收的数据包报头*/
    union {
        struct {
            uint32_t single_send_num: 3;                   /*比特用于选择哪个短数据包*/
            uint32_t single_send_en:  1;                   /*设置此位以启用发送短数据包*/
            uint32_t always_send_num: 3;                   /*比特用于选择哪个短数据包*/
            uint32_t always_send_en:  1;                   /*设置此位以允许连续发送相同的短数据包*/
            uint32_t reserved8:      24;
        };
        uint32_t val;
    } quick_sent;
    struct {
        uint32_t w_data[2];                                /*此寄存器存储短数据包的dword内容*/
    } q_data[7];
    union {
        struct {
            uint32_t seper_char:      8;                   /*此寄存器存储分隔符字符分隔符字符用于分隔数据帧。*/
            uint32_t seper_esc_char0: 8;                   /*此寄存器存储用于替换数据中分隔符字符的第一个字符。*/
            uint32_t seper_esc_char1: 8;                   /*此寄存器存储用于替换数据中分隔符字符的第二个字符。默认情况下，0xdc 0xdb替换0xc0。*/
            uint32_t reserved24:      8;
        };
        uint32_t val;
    } esc_conf0;
    union {
        struct {
            uint32_t seq0:       8;                        /*此寄存器存储用于替换单独字符的第一个替换字符。*/
            uint32_t seq0_char0: 8;                        /*此寄存器存储用于替换数据中的reg_esc_seq0的第一个字符。*/
            uint32_t seq0_char1: 8;                        /*此寄存器存储用于替换数据中的reg_esc_seq0的第二个字符*/
            uint32_t reserved24: 8;
        };
        uint32_t val;
    } esc_conf1;
    union {
        struct {
            uint32_t seq1:       8;                        /*此寄存器存储用于打开flow_control的流控制字符*/
            uint32_t seq1_char0: 8;                        /*此寄存器存储用于替换数据中的reg_esc_seq1的第一个字符。*/
            uint32_t seq1_char1: 8;                        /*此寄存器存储用于替换数据中的reg_esc_seq1的第二个字符。*/
            uint32_t reserved24: 8;
        };
        uint32_t val;
    } esc_conf2;
    union {
        struct {
            uint32_t seq2:       8;                        /*此寄存器存储flow_control字符以关闭flow_controll*/
            uint32_t seq2_char0: 8;                        /*此寄存器存储用于替换数据中的reg_esc_seq2的第一个字符。*/
            uint32_t seq2_char1: 8;                        /*此寄存器存储用于替换数据中的reg_esc_seq2的第二个字符。*/
            uint32_t reserved24: 8;
        };
        uint32_t val;
    } esc_conf3;
    union {
        struct {
            uint32_t thrs:      13;                        /*当分组有效载荷的量大于该值时，完成接收数据的过程。*/
            uint32_t reserved13:19;
        };
        uint32_t val;
    } pkt_thres;
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
    uint32_t date;                                         /*版本信息*/
} uhci_dev_t;
extern uhci_dev_t UHCI0;
extern uhci_dev_t UHCI1;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_UHCI_STRUCT_H_ */

