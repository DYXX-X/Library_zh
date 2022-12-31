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
#ifndef _SOC_UHCI_STRUCT_H_
#define _SOC_UHCI_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct uhci_dev_s {
    union {
        struct {
            uint32_t tx_rst:             1;            /*写入1，然后将0写入该位以重置解码状态机。*/
            uint32_t rx_rst:             1;            /*写入1，然后将0写入该位以重置编码状态机。*/
            uint32_t uart0_ce:           1;            /*设置此位以链接HCI和UART0。*/
            uint32_t uart1_ce:           1;            /*设置此位以链接HCI和UART1。*/
            uint32_t reserved4:          1;
            uint32_t seper_en:           1;            /*设置此位以使用特殊字符分隔数据帧。*/
            uint32_t head_en:            1;            /*设置此位以使用格式化标头对数据包进行编码。*/
            uint32_t crc_rec_en:         1;            /*设置此位以使UHCI能够接收16位CRC。*/
            uint32_t uart_idle_eof_en:   1;            /*如果该位设置为1，则当UART处于空闲状态时，UHCI将结束有效载荷接收过程。*/
            uint32_t len_eof_en:         1;            /*如果该位被设置为1，则当接收字节计数达到指定值时，UHCI解码器接收有效载荷数据结束。当UHCI_HEAD_EN为1时，该值是由UHCI数据包报头指示的有效载荷长度，当UHCI_LEAD_EN是0时，该数值是配置值。如果该位设置为0，则当接收到0xc0时，UHCI解码器接收有效载荷数据结束。*/
            uint32_t encode_crc_en:      1;            /*通过将16位CCITT-CRC附加到有效负载的末尾，设置该位以启用数据完整性检查。*/
            uint32_t clk_en:             1;            /*1’b1：强制打开寄存器时钟。1’b0：仅当应用程序写入寄存器时才支持时钟。*/
            uint32_t uart_rx_brk_eof_en: 1;            /*如果该位设置为1，则当UART接收到NULL帧时，UHCI将结束有效载荷接收过程。*/
            uint32_t reserved13:        19;
        };
        uint32_t val;
    } conf0;
    union {
        struct {
            uint32_t rx_start:                1;       /*一*/
            uint32_t tx_start:                1;       /*一*/
            uint32_t rx_hung:                 1;       /*一*/
            uint32_t tx_hung:                 1;       /*一*/
            uint32_t send_s_q:                1;       /*一*/
            uint32_t send_a_q:                1;       /*一*/
            uint32_t outlink_eof_err:         1;       /*这是中断原始位。当EOF中存在一些错误时触发*/
            uint32_t app_ctrl0:               1;       /*软控制int原始位。*/
            uint32_t app_ctrl1:               1;       /*软控制int原始位。*/
            uint32_t reserved9:              23;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rx_start:               1;        /*一*/
            uint32_t tx_start:               1;        /*一*/
            uint32_t rx_hung:                1;        /*一*/
            uint32_t tx_hung:                1;        /*一*/
            uint32_t send_s_q:               1;        /*一*/
            uint32_t send_a_q:               1;        /*一*/
            uint32_t outlink_eof_err:        1;        /*一*/
            uint32_t app_ctrl0:              1;        /*一*/
            uint32_t app_ctrl1:              1;        /*一*/
            uint32_t reserved9:             23;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rx_start:                1;       /*一*/
            uint32_t tx_start:                1;       /*一*/
            uint32_t rx_hung:                 1;       /*一*/
            uint32_t tx_hung:                 1;       /*一*/
            uint32_t send_s_q:                1;       /*一*/
            uint32_t send_a_q:                1;       /*一*/
            uint32_t outlink_eof_err:         1;       /*一*/
            uint32_t app_ctrl0:               1;       /*一*/
            uint32_t app_ctrl1:               1;       /*一*/
            uint32_t reserved9:              23;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rx_start:                1;       /*一*/
            uint32_t tx_start:                1;       /*一*/
            uint32_t rx_hung:                 1;       /*一*/
            uint32_t tx_hung:                 1;       /*一*/
            uint32_t send_s_q:                1;       /*一*/
            uint32_t send_a_q:                1;       /*一*/
            uint32_t outlink_eof_err:         1;       /*一*/
            uint32_t app_ctrl0:               1;       /*一*/
            uint32_t app_ctrl1:               1;       /*一*/
            uint32_t reserved9:              23;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t check_sum_en:    1;               /*一*/
            uint32_t check_seq_en:    1;               /*一*/
            uint32_t crc_disable:     1;               /*一*/
            uint32_t save_head:       1;               /*一*/
            uint32_t tx_check_sum_re: 1;               /*一*/
            uint32_t tx_ack_num_re:   1;               /*一*/
            uint32_t reserved6:       1;
            uint32_t wait_sw_start:   1;               /*一*/
            uint32_t sw_start:        1;               /*一*/
            uint32_t reserved9:      12;
            uint32_t reserved21:     11;
        };
        uint32_t val;
    } conf1;
    union {
        struct {
            uint32_t rx_err_cause: 3;                  /*一*/
            uint32_t decode_state: 3;                  /*一*/
            uint32_t reserved6:   26;
        };
        uint32_t val;
    } state0;
    union {
        struct {
            uint32_t encode_state: 3;                  /*一*/
            uint32_t reserved3:   29;
        };
        uint32_t val;
    } state1;
    union {
        struct {
            uint32_t tx_c0_esc_en: 1;                  /*一*/
            uint32_t tx_db_esc_en: 1;                  /*一*/
            uint32_t tx_11_esc_en: 1;                  /*一*/
            uint32_t tx_13_esc_en: 1;                  /*一*/
            uint32_t rx_c0_esc_en: 1;                  /*一*/
            uint32_t rx_db_esc_en: 1;                  /*一*/
            uint32_t rx_11_esc_en: 1;                  /*一*/
            uint32_t rx_13_esc_en: 1;                  /*一*/
            uint32_t reserved8:   24;
        };
        uint32_t val;
    } escape_conf;
    union {
        struct {
            uint32_t txfifo_timeout:       8;          /*一*/
            uint32_t txfifo_timeout_shift: 3;          /*一*/
            uint32_t txfifo_timeout_ena:   1;          /*一*/
            uint32_t rxfifo_timeout:       8;          /*一*/
            uint32_t rxfifo_timeout_shift: 3;          /*一*/
            uint32_t rxfifo_timeout_ena:   1;          /*一*/
            uint32_t reserved24:           8;
        };
        uint32_t val;
    } hung_conf;
    union {
        struct {
            uint32_t ack_num:      3;
            uint32_t ack_num_load: 1;                  /*一*/
            uint32_t reserved4:   28;
        };
        uint32_t val;
    } ack_num;
    uint32_t rx_head;                                  /*一*/
    union {
        struct {
            uint32_t single_send_num: 3;               /*一*/
            uint32_t single_send_en:  1;               /*一*/
            uint32_t always_send_num: 3;               /*一*/
            uint32_t always_send_en:  1;               /*一*/
            uint32_t reserved8:      24;
        };
        uint32_t val;
    } quick_sent;
    struct {
        uint32_t w_data[2];                                 /*一*/
    } q_data[7];
    union {
        struct {
            uint32_t seper_char:      8;               /*一*/
            uint32_t seper_esc_char0: 8;               /*一*/
            uint32_t seper_esc_char1: 8;               /*一*/
            uint32_t reserved24:      8;               /*一*/
        };
        uint32_t val;
    } esc_conf0;
    union {
        struct {
            uint32_t seq0:           8;                /*一*/
            uint32_t seq0_char0:     8;                /*一*/
            uint32_t seq0_char1:     8;                /*一*/
            uint32_t reserved24:     8;
        };
        uint32_t val;
    } esc_conf1;
    union {
        struct {
            uint32_t seq1:           8;                /*一*/
            uint32_t seq1_char0:     8;                /*一*/
            uint32_t seq1_char1:     8;                /*一*/
            uint32_t reserved24:     8;
        };
        uint32_t val;
    } esc_conf2;
    union {
        struct {
            uint32_t seq2:           8;                /*一*/
            uint32_t seq2_char0:     8;                /*一*/
            uint32_t seq2_char1:     8;                /*一*/
            uint32_t reserved24:     8;
        };
        uint32_t val;
    } esc_conf3;
    union {
        struct {
            uint32_t thrs:      13;                    /*一*/
            uint32_t reserved13:19;
        };
        uint32_t val;
    } pkt_thres;
    uint32_t date;                                     /*一*/
} uhci_dev_t;
extern uhci_dev_t UHCI0;
extern uhci_dev_t UHCI1;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_UHCI_STRUCT_H_ */

