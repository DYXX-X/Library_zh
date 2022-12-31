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

/**组：FIFO配置*/
/** fifo寄存器类型fifo数据寄存器
 */
typedef union {
    struct {
        /** rxifo_rd_byte:RO；位位置：[7:0]；默认值：0；UART$n通过该寄存器访问FIFO。必须是unit32_t而不是位字段，以避免在写入期间执行读->写操作。写入时读取会影响RX fifo
         */
        uint32_t rxfifo_rd_byte;
    };
    uint32_t val;
} uart_fifo_reg_t;

/** mem_conf寄存器UART阈值类型和分配配置
 */
typedef union {
    struct {
        uint32_t reserved_0:1;
        /** rx尺寸：R/W；位位置：[3:1]；默认值：1；此寄存器用于配置分配给接收FIFO的内存量。默认值为128字节。
         */
        uint32_t rx_size:3;
        /** tx_size:R/W；比特位置：[6:4]；默认值：1；该寄存器用于配置分配给传输FIFO的内存量。默认值为128字节。
         */
        uint32_t tx_size:3;
        /** rx_flow_thrhd:R/W；比特位置：[16:7]；默认值：0；此寄存器用于配置硬件流控制工作时可接收的最大数据量。
         */
        uint32_t rx_flow_thrhd:10;
        /** rx_tut_thrhd:R/W；比特位置：[26:17]；默认值：10；此寄存器用于配置接收器接收一个字节所需的阈值时间。当接收器花费更多时间接收一个字节且rx_tout_en设置为1时，将触发rxifo_out_int中断。
         */
        uint32_t rx_tout_thrhd:10;
        /** mem_force_pd:R/W；位位置：[27]；默认值：0；设置此位以强制关闭UART存储器。
         */
        uint32_t mem_force_pd:1;
        /** mem_force_pu:R/W；位位置：[28]；默认值：0；设置此位以强制启动UART存储器。
         */
        uint32_t mem_force_pu:1;
        uint32_t reserved_29:3;
    };
    uint32_t val;
} uart_mem_conf_reg_t;


/**组：中断寄存器*/
/** int_raw寄存器的类型原始中断状态
 */
typedef union {
    struct {
        /** rxfifo_full_int_raw:R/WTC/SS；位位置：[0]；默认值：0；当接收器接收到的数据超过rxfif_full_thrhd指定的数据时，此中断原始位变为高电平。
         */
        uint32_t rxfifo_full_int_raw:1;
        /** txfifo_empty_int_raw:R/WTC/SS；位位置：[1]；默认值：1；当Tx FIFO中的数据量小于txfifo_empty_thrhd指定的值时，该中断原始位变为高电平。
         */
        uint32_t txfifo_empty_int_raw:1;
        /** parity_err_int_raw:R/WTC/SS；位位置：[2]；默认值：0；当接收器检测到数据中的奇偶校验错误时，该中断原始位变为高电平。
         */
        uint32_t parity_err_int_raw:1;
        /** frm_err_int_raw:R/WTC/SS；位位置：[3]；默认值：0；当接收机检测到数据帧错误时，该中断原始位变为高电平。
         */
        uint32_t frm_err_int_raw:1;
        /** rxfifo_ovf_int_raw:R/WTC/SS；位位置：[4]；默认值：0；当接收器接收的数据超过FIFO所能存储的数据时，该中断原始位变为高电平。
         */
        uint32_t rxfifo_ovf_int_raw:1;
        /** dsr_chg_int_raw:R/WTC/SS；位位置：[5]；默认值：0；当接收机检测到DSRn信号的边沿变化时，该中断原始位变为高电平。
         */
        uint32_t dsr_chg_int_raw:1;
        /** cts_chg_int_raw:R/WTC/SS；位位置：[6]；默认值：0；当接收机检测到CTSn信号的边沿变化时，该中断原始位变为高电平。
         */
        uint32_t cts_chg_int_raw:1;
        /** brk_det_int_raw:R/WTC/SS；位位置：[7]；默认值：0；当接收器在停止位之后检测到0时，该中断原始位变为高电平。
         */
        uint32_t brk_det_int_raw:1;
        /** rxifo_out_int_raw:R/WTC/SS；位位置：[8]；默认值：0；当接收器接收一个字节的时间超过rx_tout_thhd时，该中断原始位变为高电平。
         */
        uint32_t rxfifo_tout_int_raw:1;
        /** sw_xon_int_raw:R/WTC/SS；位位置：[9]；默认值：0；当uart_sw_flow_con_en设置为1时，当接收器接收到Xon字符时，该中断原始位变为高电平。
         */
        uint32_t sw_xon_int_raw:1;
        /** sw_xoff_int_raw:R/WTC/SS；位位置：[10]；默认值：0；当uart_sw_flow_con_en设置为1时，当接收器接收到Xoff字符时，该中断原始位变为高电平。
         */
        uint32_t sw_xoff_int_raw:1;
        /** 故障_det_int_raw:R/WTC/SS；位位置：[11]；默认值：0；当接收器检测到起始位中间出现故障时，该中断原始位变为高电平。
         */
        uint32_t glitch_det_int_raw:1;
        /** tx_brk_done_int_raw:R/WTC/SS；位位置：[12]；默认值：0；在发送Tx FIFO中的所有数据后，当发送器完成发送NULL字符时，该中断原始位变为高电平。
         */
        uint32_t tx_brk_done_int_raw:1;
        /** tx_brk_idle_done_int_raw:R/WTC/SS；位位置：[13]；默认值：0；当发射机在发送最后一个数据后保持最短的持续时间时，该中断原始位变为高电平。
         */
        uint32_t tx_brk_idle_done_int_raw:1;
        /** tx_done_int_raw:R/WTC/SS；位位置：[14]；默认值：0；当发射机发出FIFO中的所有数据时，该中断原始位变为高电平。
         */
        uint32_t tx_done_int_raw:1;
        /** rs485_parity_err_int_raw:R/WTC/SS；位位置：[15]；默认值：0；当接收机在rs485模式下从发射机回波中检测到奇偶校验错误时，该中断原始位变为高电平。
         */
        uint32_t rs485_parity_err_int_raw:1;
        /** rs485_frm_err_int_raw:R/WTC/SS；位位置：[16]；默认值：0；当接收机在rs485模式下从发射机回波中检测到数据帧错误时，该中断原始位变为高电平。
         */
        uint32_t rs485_frm_err_int_raw:1;
        /** rs485_clash_int_raw:R/WTC/SS；位位置：[17]；默认值：0；当在rs485模式下检测到发射机和接收机之间的冲突时，该中断原始位变为高电平。
         */
        uint32_t rs485_clash_int_raw:1;
        /** at_cmd_char_det_int_raw:R/WTC/SS；位位置：[18]；默认值：0；当接收器检测到配置的at_cmd字符时，该中断原始位变为高电平。
         */
        uint32_t at_cmd_char_det_int_raw:1;
        /** wakeup_int_raw:R/WTC/SS；位位置：[19]；默认值：0；当输入rxd边缘的变化次数超过浅睡眠模式下reg_active_threshold指定的次数时，此中断原始位变为高电平。
         */
        uint32_t wakeup_int_raw:1;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} uart_int_raw_reg_t;

/** int_st寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** rxifo_full_int_st:RO；位位置：[0]；默认值：0；这是rxfifo_full_int_ena设置为1时rxfify_full_int_raw的状态位。
         */
        uint32_t rxfifo_full_int_st:1;
        /** txfifo_empty_int_st:RO；位位置：[1]；默认值：0；这是当txfifo_empty_int_ena设置为1时，txfifo_oempty_int_raw的状态位。
         */
        uint32_t txfifo_empty_int_st:1;
        /** parity_err_int_st:RO；位位置：[2]；默认值：0；这是parity_err_int_ena设置为1时parity_err _int_raw的状态位。
         */
        uint32_t parity_err_int_st:1;
        /** frm_err_int_st:RO；位位置：[3]；默认值：0；这是当frm_err_int_ena设置为1时frm_err_int_raw的状态位。
         */
        uint32_t frm_err_int_st:1;
        /** rxfifo_ovf_int_st:RO；位位置：[4]；默认值：0；这是当rxfifo_ovf_int_ena设置为1时rxfifo_ovf_int_raw的状态位。
         */
        uint32_t rxfifo_ovf_int_st:1;
        /** dsr_chg_int_st:RO；位位置：[5]；默认值：0；这是dsr_chg_int_ena设置为1时dsr_chg_int_raw的状态位。
         */
        uint32_t dsr_chg_int_st:1;
        /** cts_chg_int_st:RO；位位置：[6]；默认值：0；这是当cts_chg_int_ena设置为1时，cts_chg_int_raw的状态位。
         */
        uint32_t cts_chg_int_st:1;
        /** brk_det_int_st:RO；位位置：[7]；默认值：0；这是brk_det_int_ena设置为1时brk_dep_int_raw的状态位。
         */
        uint32_t brk_det_int_st:1;
        /** rxifo_out_int_st:RO；位位置：[8]；默认值：0；这是rxfifo_out_int_ena设置为1时rxfify_out_int_raw的状态位。
         */
        uint32_t rxfifo_tout_int_st:1;
        /** sw_xon_int_st:RO；位位置：[9]；默认值：0；这是sw_xon_int_ena设置为1时sw_xon_ent_raw的状态位。
         */
        uint32_t sw_xon_int_st:1;
        /** sw_xoff_int_st:RO；位位置：[10]；默认值：0；这是sw_xoff_int_ena设置为1时sw_xoff_int_raw的状态位。
         */
        uint32_t sw_xoff_int_st:1;
        /** 故障_det_int_st:RO；位位置：[11]；默认值：0；这是当glitch_det_int_ena设置为1时，glitch_ded_int_raw的状态位。
         */
        uint32_t glitch_det_int_st:1;
        /** tx_brk_done_int_st:RO；位位置：[12]；默认值：0；这是当tx_brk_done_int_ena设置为1时，tx_brk_done_int_raw的状态位。
         */
        uint32_t tx_brk_done_int_st:1;
        /** tx_brk_idle_done_int_st:RO；位位置：[13]；默认值：0；这是当tx_brk_idle_done_int_ena设置为1时，tx_brk_idle_done_int.raw的stauts位。
         */
        uint32_t tx_brk_idle_done_int_st:1;
        /** tx_done_int_st:RO；位位置：[14]；默认值：0；这是tx_done_int_ena设置为1时tx_done_It_raw的状态位。
         */
        uint32_t tx_done_int_st:1;
        /** rs485_parity_err_int_st:RO；位位置：[15]；默认值：0；这是rs485_parity_int_ena设置为1时rs485_parite_err_int_raw的状态位。
         */
        uint32_t rs485_parity_err_int_st:1;
        /** rs485_frm_err_int_st:RO；位位置：[16]；默认值：0；这是当rs485_fm_err_int_ena设置为1时，rs485_frm_err_int_raw的状态位。
         */
        uint32_t rs485_frm_err_int_st:1;
        /** rs485_clash_int_st:RO；位位置：[17]；默认值：0；这是rs485_clash_int_ena设置为1时rs485_clash_int_raw的状态位。
         */
        uint32_t rs485_clash_int_st:1;
        /** at_cmd_char_det_int_st:RO；位位置：[18]；默认值：0；这是at_cmd_char_det_int_ena设置为1时at_cmd_det_int_raw的状态位。
         */
        uint32_t at_cmd_char_det_int_st:1;
        /** 唤醒_int_st:RO；位位置：[19]；默认值：0；这是当uart_weakeup_int_ena设置为1时uart_wwakeup_int_raw的状态位。
         */
        uint32_t wakeup_int_st:1;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} uart_int_st_reg_t;

/** int_ena寄存器中断启用位的类型
 */
typedef union {
    struct {
        /** rxifo_full_int_ena:R/W；位位置：[0]；默认值：0；这是rxifo_full_int_st寄存器的启用位。
         */
        uint32_t rxfifo_full_int_ena:1;
        /** txfifo_empty_int_ena:R/W；位位置：[1]；默认值：0；这是txfifo_empty_int_st寄存器的启用位。
         */
        uint32_t txfifo_empty_int_ena:1;
        /** parity_err_int_ena:R/W；位位置：[2]；默认值：0；这是parity_err_int_st寄存器的启用位。
         */
        uint32_t parity_err_int_ena:1;
        /** frm_err_int_ena:R/W；位位置：[3]；默认值：0；这是frm_err_int_st寄存器的启用位。
         */
        uint32_t frm_err_int_ena:1;
        /** rxfifo_ovf_int_ena:R/W；位位置：[4]；默认值：0；这是rxfifo_ovf_int_st寄存器的启用位。
         */
        uint32_t rxfifo_ovf_int_ena:1;
        /** dsr_chg_int_ena:R/W；位位置：[5]；默认值：0；这是dsr_chg_int_st寄存器的启用位。
         */
        uint32_t dsr_chg_int_ena:1;
        /** cts_chg_int_ena:R/W；位位置：[6]；默认值：0；这是cts_chg_int_st寄存器的启用位。
         */
        uint32_t cts_chg_int_ena:1;
        /** brk_det_int_ena:R/W；位位置：[7]；默认值：0；这是brk_det_int_st寄存器的启用位。
         */
        uint32_t brk_det_int_ena:1;
        /** rxifo_out_int_ena:R/W；位位置：[8]；默认值：0；这是rxifo_out_int_st寄存器的启用位。
         */
        uint32_t rxfifo_tout_int_ena:1;
        /** sw_xon_int_ena:R/W；位位置：[9]；默认值：0；这是sw_xon_int_st寄存器的启用位。
         */
        uint32_t sw_xon_int_ena:1;
        /** sw_xoff_int_ena:R/W；位位置：[10]；默认值：0；这是sw_xoff_int_st寄存器的启用位。
         */
        uint32_t sw_xoff_int_ena:1;
        /** 故障_det_int_ena:R/W；位位置：[11]；默认值：0；这是glizz_det_int_st寄存器的启用位。
         */
        uint32_t glitch_det_int_ena:1;
        /** tx_brk_done_int_ena:R/W；位位置：[12]；默认值：0；这是tx_brk_done_int_st寄存器的启用位。
         */
        uint32_t tx_brk_done_int_ena:1;
        /** tx_brk_idle_done_int_ena:R/W；位位置：[13]；默认值：0；这是tx_brk_idle_done_int_st寄存器的启用位。
         */
        uint32_t tx_brk_idle_done_int_ena:1;
        /** tx_done_int_ena:R/W；位位置：[14]；默认值：0；这是tx_done_int_st寄存器的启用位。
         */
        uint32_t tx_done_int_ena:1;
        /** rs485_parity_err_int_ena:R/W；位位置：[15]；默认值：0；这是rs485_parity_err_int_st寄存器的启用位。
         */
        uint32_t rs485_parity_err_int_ena:1;
        /** rs485_frm_err_int_ena:R/W；位位置：[16]；默认值：0；这是rs485_parity_err_int_st寄存器的启用位。
         */
        uint32_t rs485_frm_err_int_ena:1;
        /** rs485_clash_int_ena:R/W；位位置：[17]；默认值：0；这是rs485_clash_int_st寄存器的启用位。
         */
        uint32_t rs485_clash_int_ena:1;
        /** at_cmd_char_det_int_ena:R/W；位位置：[18]；默认值：0；这是at_cmd_char_det_int_st寄存器的启用位。
         */
        uint32_t at_cmd_char_det_int_ena:1;
        /** 唤醒_ int_ena:R/W；位位置：[19]；默认值：0；这是uart_wakeup_int_st寄存器的启用位。
         */
        uint32_t wakeup_int_ena:1;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} uart_int_ena_reg_t;

/** int_clr寄存器类型中断清除位
 */
typedef union {
    struct {
        /** rxifo_full_int_clr:WT；位位置：[0]；默认值：0；设置此位以清除rxifo_full_int_raw中断。
         */
        uint32_t rxfifo_full_int_clr:1;
        /** txfifo_empty_int_clr:WT；位位置：[1]；默认值：0；设置此位以清除txfifo_empty_int_raw中断。
         */
        uint32_t txfifo_empty_int_clr:1;
        /** parity_err_int_clr:WT；位位置：[2]；默认值：0；设置此位以清除parity_err_int_raw中断。
         */
        uint32_t parity_err_int_clr:1;
        /** frm_err_int_clr:WT；位位置：[3]；默认值：0；设置此位以清除frm_err_int_raw中断。
         */
        uint32_t frm_err_int_clr:1;
        /** rxfifo_ovf_int_clr:WT；位位置：[4]；默认值：0；设置此位以清除rxfifo_ovf_int_raw中断。
         */
        uint32_t rxfifo_ovf_int_clr:1;
        /** dsr_chg_int_clr:WT；位位置：[5]；默认值：0；设置此位以清除dsr_chg_int_raw中断。
         */
        uint32_t dsr_chg_int_clr:1;
        /** cts_chg_int_clr:WT；位位置：[6]；默认值：0；设置此位以清除cts_chg_int_raw中断。
         */
        uint32_t cts_chg_int_clr:1;
        /** brk_det_int_clr:WT；位位置：[7]；默认值：0；设置此位以清除brk_det_int_raw中断。
         */
        uint32_t brk_det_int_clr:1;
        /** rxifo_out_int_clr:WT；位位置：[8]；默认值：0；设置此位以清除rxifo_out_int_raw中断。
         */
        uint32_t rxfifo_tout_int_clr:1;
        /** sw_xon_int_clr:WT；位位置：[9]；默认值：0；设置此位以清除sw_xon_int_raw中断。
         */
        uint32_t sw_xon_int_clr:1;
        /** sw_xoff_int_clr:WT；位位置：[10]；默认值：0；设置此位以清除sw_xoff_int_raw中断。
         */
        uint32_t sw_xoff_int_clr:1;
        /** 故障_det_int_clr:WT；位位置：[11]；默认值：0；设置此位以清除故障_det_int_raw中断。
         */
        uint32_t glitch_det_int_clr:1;
        /** tx_brk_done_int_clr:WT；位位置：[12]；默认值：0；设置此位以清除tx_brk_done_int_raw中断。。
         */
        uint32_t tx_brk_done_int_clr:1;
        /** tx_brk_idle_done_int_clr:WT；位位置：[13]；默认值：0；设置此位以清除tx_brk_idle_done_int_raw中断。
         */
        uint32_t tx_brk_idle_done_int_clr:1;
        /** tx_done_int_clr:WT；位位置：[14]；默认值：0；设置此位以清除tx_done_int_raw中断。
         */
        uint32_t tx_done_int_clr:1;
        /** rs485_parity_err_int_clr:WT；位位置：[15]；默认值：0；设置此位以清除rs485_parity_err_int_raw中断。
         */
        uint32_t rs485_parity_err_int_clr:1;
        /** rs485_frm_err_int_clr:WT；位位置：[16]；默认值：0；设置此位以清除rs485_frm_err_int_raw中断。
         */
        uint32_t rs485_frm_err_int_clr:1;
        /** rs485_clash_int_clr:WT；位位置：[17]；默认值：0；设置此位以清除rs485_clash_int_raw中断。
         */
        uint32_t rs485_clash_int_clr:1;
        /** at_cmd_char_det_int_clr:WT；位位置：[18]；默认值：0；设置此位以清除at_cmd_char_det_int_raw中断。
         */
        uint32_t at_cmd_char_det_int_clr:1;
        /** 唤醒_ int_ clr:WT；位位置：[19]；默认值：0；设置此位以清除uart_wakeup_int_raw中断。
         */
        uint32_t wakeup_int_clr:1;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} uart_int_clr_reg_t;


/**组：配置寄存器*/
/** clkdiv寄存器时钟分频器配置的类型
 */
typedef union {
    struct {
        /** clkdiv:R/W；位位置：[11:0]；默认值：694；分频因子的整数部分。
         */
        uint32_t clkdiv:12;
        uint32_t reserved_12:8;
        /** clkdiv_frag:R/W；比特位置：[23:20]；默认值：0；分频因子的小数部分。
         */
        uint32_t clkdiv_frag:4;
        uint32_t reserved_24:8;
    };
    uint32_t val;
} uart_clkdiv_reg_t;

/** rx_filt寄存器rx滤波器配置类型
 */
typedef union {
    struct {
        /** glitch_filt:R/W；位位置：[7:0]；默认值：8；当输入脉冲宽度小于该值时，该脉冲被忽略。
         */
        uint32_t glitch_filt:8;
        /** glitch_filt_en:R/W；位位置：[8]；默认值：0；设置此位以启用Rx信号滤波器。
         */
        uint32_t glitch_filt_en:1;
        uint32_t reserved_9:23;
    };
    uint32_t val;
} uart_rx_filt_reg_t;

/** conf0寄存器的类型
 */
typedef union {
    struct {
        /** 奇偶校验：R/W；位位置：[0]；默认值：0；此寄存器用于配置奇偶校验模式。
         */
        uint32_t parity:1;
        /** parity_en:R/W；位位置：[1]；默认值：0；设置此位以启用uart奇偶校验。
         */
        uint32_t parity_en:1;
        /** bit_num:R/W；位位置：[3:2]；默认值：3；此寄存器用于设置数据长度。
         */
        uint32_t bit_num:2;
        /** stop_bit_num:R/W；比特位置：[5:4]；默认值：1；该寄存器用于设置停止位的长度。
         */
        uint32_t stop_bit_num:2;
        /** sw_rts:R/W；位位置：[6]；默认值：0；该寄存器用于配置软件流控制中使用的软件rts信号。
         */
        uint32_t sw_rts:1;
        /** sw_dtr:R/W；位位置：[7]；默认值：0；该寄存器用于配置软件流控制中使用的软件dtr信号。
         */
        uint32_t sw_dtr:1;
        /** txd_brk:R/W；位位置：[8]；默认值：0；当发送数据的过程完成时，将此位设置为enbale发射器发送NULL。
         */
        uint32_t txd_brk:1;
        /** irda_dplx:R/W；位位置：[9]；默认值：0；设置此位以启用IrDA环回模式。
         */
        uint32_t irda_dplx:1;
        /** irda_tx_en:R/W；位位置：[10]；默认值：0；这是IrDA发射器的启动启用位。
         */
        uint32_t irda_tx_en:1;
        /** irda_wctl:R/W；位位置：[11]；默认值：0；1’h1:IrDA发射机的第11位与第10位相同。1’0：将IrDA发射器的第11位设置为0。
         */
        uint32_t irda_wctl:1;
        /** irda_tx_inv:R/W；位位置：[12]；默认值：0；设置此位以反转IrDA发射器的电平。
         */
        uint32_t irda_tx_inv:1;
        /** irda_rx_inv:R/W；位位置：[13]；默认值：0；设置此位以反转IrDA接收器的电平。
         */
        uint32_t irda_rx_inv:1;
        /** 回送：R/W；位位置：[14]；默认值：0；设置此位以启用uart环回测试模式。
         */
        uint32_t loopback:1;
        /** tx_flow_en:R/W；位位置：[15]；默认值：0；设置此位以启用变送器的流量控制功能。
         */
        uint32_t tx_flow_en:1;
        /** irda_en:R/W；位位置：[16]；默认值：0；设置此位以启用IrDA协议。
         */
        uint32_t irda_en:1;
        /** rxifo_rst:R/W；位位置：[17]；默认值：0；设置此位以重置uart接收FIFO。
         */
        uint32_t rxfifo_rst:1;
        /** txfifo_rst:R/W；位位置：[18]；默认值：0；设置此位以重置uart传输FIFO。
         */
        uint32_t txfifo_rst:1;
        /** rxd_inv:R/W；位位置：[19]；默认值：0；设置此位以反转uart rxd信号的电平值。
         */
        uint32_t rxd_inv:1;
        /** cts_inv:R/W；位位置：[20]；默认值：0；设置此位以反转uart cts信号的电平值。
         */
        uint32_t cts_inv:1;
        /** dsr_inv:R/W；位位置：[21]；默认值：0；设置此位以反转uart dsr信号的电平值。
         */
        uint32_t dsr_inv:1;
        /** txd_inv:R/W；位位置：[22]；默认值：0；设置此位以反转uart txd信号的电平值。
         */
        uint32_t txd_inv:1;
        /** rts_inv:R/W；位位置：[23]；默认值：0；设置此位以反转uart rts信号的电平值。
         */
        uint32_t rts_inv:1;
        /** dtr_inv:R/W；位位置：[24]；默认值：0；设置此位以反转uart dtr信号的电平值。
         */
        uint32_t dtr_inv:1;
        /** clk_en:R/W；位位置：[25]；默认值：0；1'h1：强制打开寄存器时钟。1’0：仅当应用程序写入寄存器时才支持时钟。
         */
        uint32_t clk_en:1;
        /** 错误_ _掩码：R/W；位位置：[26]；默认值：0；1’h1：当数据错误时，接收器停止将数据存储到FIFO中。1’0：即使接收到的数据错误，接收器也会存储数据。
         */
        uint32_t err_wr_mask:1;
        /** autobaud_en:R/W；位位置：[27]；默认值：0；这是检测波特率的启用位。
         */
        uint32_t autobaud_en:1;
        /** mem_clk_en:R/W；位位置：[28]；默认值：1；UART存储器时钟门启用信号。
         */
        uint32_t mem_clk_en:1;
        uint32_t reserved_29:3;
    };
    uint32_t val;
} uart_conf0_reg_t;

/** conf1寄存器类型配置寄存器1
 */
typedef union {
    struct {
        /** rxifo_full_thrhd:R/W；位位置：[9:0]；默认值：96；当接收器接收到的数据超过此寄存器值时，它将产生rxifo_full_int中断。
         */
        uint32_t rxfifo_full_thrhd:10;
        /** txfifo_empty_thrd:R/W；比特位置：[19:10]；默认值：96；当Tx FIFO中的数据量小于此寄存器值时，它将产生txfifo_empty_int中断。
         */
        uint32_t txfifo_empty_thrhd:10;
        /** dis_rx_dat_ovf:R/W；位位置：[20]；默认值：0；禁用UART Rx数据溢出检测。
         */
        uint32_t dis_rx_dat_ovf:1;
        /** rx_tout_flow_dis:R/W；位位置：[21]；默认值：0；设置此位以在硬件流控制工作时停止累积idle_cnt。
         */
        uint32_t rx_tout_flow_dis:1;
        /** rx_flow_en:R/W；位位置：[22]；默认值：0；这是UART接收器的流量启用位。
         */
        uint32_t rx_flow_en:1;
        /** rx_tout_en:R/W；位位置：[23]；默认值：0；这是uart接收器超时功能的启用位。
         */
        uint32_t rx_tout_en:1;
        uint32_t reserved_24:8;
    };
    uint32_t val;
} uart_conf1_reg_t;

/** flow_conf寄存器类型软件流控制配置
 */
typedef union {
    struct {
        /** sw_flow_con_en:R/W；位位置：[0]；默认值：0；设置此位以启用软件流控制。它与寄存器sw_xon或sw_xoff一起使用。
         */
        uint32_t sw_flow_con_en:1;
        /** xonoff_del:R/W；位位置：[1]；默认值：0；设置此位以从接收的数据中删除流控制字符。
         */
        uint32_t xonoff_del:1;
        /** force_xon:R/W；位位置：[2]；默认值：0；设置此位以使发射器能够继续发送数据。
         */
        uint32_t force_xon:1;
        /** force_xoff:R/W；位位置：[3]；默认值：0；设置此位以停止发射器发送数据。
         */
        uint32_t force_xoff:1;
        /** send_xon:R/W/SS/SC；位位置：[4]；默认值：0；设置此位以发送Xon字符。它由硬件自动清除。
         */
        uint32_t send_xon:1;
        /** send_xoff:R/W/SS/SC；位位置：[5]；默认值：0；设置此位以发送Xoff字符。它由硬件自动清除。
         */
        uint32_t send_xoff:1;
        uint32_t reserved_6:26;
    };
    uint32_t val;
} uart_flow_conf_reg_t;

/** sleep_conf寄存器类型睡眠模式配置
 */
typedef union {
    struct {
        /** 活动阈值：R/W；位位置：[9:0]；默认值：240；当输入rxd边缘的变化次数超过此寄存器值时，uart从浅睡眠模式激活。
         */
        uint32_t active_threshold:10;
        uint32_t reserved_10:22;
    };
    uint32_t val;
} uart_sleep_conf_reg_t;

/** swfc_conf0寄存器类型软件流控制字符配置
 */
typedef union {
    struct {
        /** xoff_threshold:R/W；位位置：[9:0]；默认值：224；当Rx FIFO中的数据量大于此寄存器值且uart_sw_flow_con_en设置为1时，它将发送一个Xoff字符。
         */
        uint32_t xoff_threshold:10;
        /** xoff_char:R/W；比特位置：[17:10]；默认值：19；此寄存器存储Xoff流控制字符。
         */
        uint32_t xoff_char:8;
        uint32_t reserved_18:14;
    };
    uint32_t val;
} uart_swfc_conf0_reg_t;

/** swfc_conf1寄存器类型软件流控制字符配置
 */
typedef union {
    struct {
        /** xon_threshold:R/W；位位置：[9:0]；默认值：0；当Rx FIFO中的数据量小于此寄存器值且uart_sw_flow_con_en设置为1时，它将发送一个Xon字符。
         */
        uint32_t xon_threshold:10;
        /** xon_char：R/W；比特位置：[17:10]；默认值：17；此寄存器存储Xon流控制字符。
         */
        uint32_t xon_char:8;
        uint32_t reserved_18:14;
    };
    uint32_t val;
} uart_swfc_conf1_reg_t;

/** txbrk_conf寄存器Tx中断字符配置的类型
 */
typedef union {
    struct {
        /** tx_brk_num:R/W；位位置：[7:0]；默认值：10；此寄存器用于配置发送数据过程完成后要发送的0的数量。当txd_brk设置为1时激活。
         */
        uint32_t tx_brk_num:8;
        uint32_t reserved_8:24;
    };
    uint32_t val;
} uart_txbrk_conf_reg_t;

/** idle_conf寄存器类型帧结束空闲配置
 */
typedef union {
    struct {
        /** rxidle_thrhd:R/W；位位置：[9:0]；默认值：256；当接收机接收一字节数据的时间超过该寄存器值时，它将产生帧结束信号。
         */
        uint32_t rx_idle_thrhd:10;
        /** tx_idle_num:R/W；比特位置：[19:10]；默认值：256；此寄存器用于配置传输之间的持续时间。
         */
        uint32_t tx_idle_num:10;
        uint32_t reserved_20:12;
    };
    uint32_t val;
} uart_idle_conf_reg_t;

/** rs485_conf寄存器rs485模式配置类型
 */
typedef union {
    struct {
        /** rs485_en:R/W；位位置：[0]；默认值：0；设置此位以选择rs485模式。
         */
        uint32_t rs485_en:1;
        /** dl0_en:R/W；位位置：[1]；默认值：0；设置此位以将停止位延迟1位。
         */
        uint32_t dl0_en:1;
        /** dl1_en:R/W；位位置：[2]；默认值：0；设置此位以将停止位延迟1位。
         */
        uint32_t dl1_en:1;
        /** rs485tx_rx_en:R/W；位位置：[3]；默认值：0；设置此位，使接收器能够在发射器以rs485模式传输数据时接收数据。
         */
        uint32_t rs485tx_rx_en:1;
        /** rs485rxby_tx_en:R/W；位位置：[4]；默认值：0；1’h1：当rs485接收器线路繁忙时，启用rs485发射器发送数据。
         */
        uint32_t rs485rxby_tx_en:1;
        /** rs485_rx_dly_num:R/W；位位置：[5]；默认值：0；该寄存器用于延迟接收机的内部数据信号。
         */
        uint32_t rs485_rx_dly_num:1;
        /** rs485_tx_dly_num:R/W；比特位置：[9:6]；默认值：0；该寄存器用于延迟变送器的内部数据信号。
         */
        uint32_t rs485_tx_dly_num:4;
        uint32_t reserved_10:22;
    };
    uint32_t val;
} uart_rs485_conf_reg_t;

/** clk_conf寄存器UART核心时钟配置的类型
 */
typedef union {
    struct {
        /** sclk_div_b:R/W；比特位置：[5:0]；默认值：0；分频因子的分母。
         */
        uint32_t sclk_div_b:6;
        /** sclk_div_a:R/W；位位置：[11:6]；默认值：0；分频因子的分子。
         */
        uint32_t sclk_div_a:6;
        /** sclk_div_num:R/W；比特位置：[19:12]；默认值：1；分频因子的整数部分。
         */
        uint32_t sclk_div_num:8;
        /** sclk_sel:R/W；比特位置：[21:20]；默认值：3；UART时钟源选择。1： 80Mhz，2:8Mhz，3:XTAL。
         */
        uint32_t sclk_sel:2;
        /** sclk_en:R/W；位位置：[22]；默认值：1；设置此位以启用UART Tx/Rx时钟。
         */
        uint32_t sclk_en:1;
        /** rst_core:R/W；位位置：[23]；默认值：0；写入1，然后将0写入该位，重置UART Tx/Rx。
         */
        uint32_t rst_core:1;
        /** tx_sclk_en:R/W；位位置：[24]；默认值：1；设置此位以启用UART Tx时钟。
         */
        uint32_t tx_sclk_en:1;
        /** rx_sclk_en:R/W；位位置：[25]；默认值：1；设置此位以启用UART Rx时钟。
         */
        uint32_t rx_sclk_en:1;
        /** tx_rst_core:R/W；位位置：[26]；默认值：0；写入1，然后将0写入该位，重置UART Tx。
         */
        uint32_t tx_rst_core:1;
        /** rx_rst_core:R/W；位位置：[27]；默认值：0；写入1，然后将0写入该位，重置UART Rx。
         */
        uint32_t rx_rst_core:1;
        uint32_t reserved_28:4;
    };
    uint32_t val;
} uart_clk_conf_reg_t;


/**组：状态寄存器*/
/** 状态寄存器类型UART状态寄存器
 */
typedef union {
    struct {
        /** rxifo_cnt:RO；位位置：[9:0]；默认值：0；在Rx FIFO中存储有效数据的字节数。
         */
        uint32_t rxfifo_cnt:10;
        uint32_t reserved_10:3;
        /** dsrn:RO；位位置：[13]；默认值：0；寄存器表示内部uart dsr信号的电平值。
         */
        uint32_t dsrn:1;
        /** ctsn:RO；位位置：[14]；默认值：1；该寄存器表示内部uart cts信号的电平值。
         */
        uint32_t ctsn:1;
        /** rxd:RO；位位置：[15]；默认值：1；该寄存器表示内部uart rxd信号的电平值。
         */
        uint32_t rxd:1;
        /** txfifo_cnt:RO；比特位置：[25:16]；默认值：0；在Tx FIFO中存储数据的字节数。
         */
        uint32_t txfifo_cnt:10;
        uint32_t reserved_26:3;
        /** dtrn:RO；位位置：[29]；默认值：1；该位表示内部uart dtr信号的电平。
         */
        uint32_t dtrn:1;
        /** rtsn:RO；位位置：[30]；默认值：1；该位表示内部uart rts信号的电平。
         */
        uint32_t rtsn:1;
        /** txd:RO；位位置：[31]；默认值：1；该位表示内部uart txd信号的电平。
         */
        uint32_t txd:1;
    };
    uint32_t val;
} uart_status_reg_t;

/** mem_tx_status寄存器tx FIFO写入和读取偏移地址的类型。
 */
typedef union {
    struct {
        /** apb_tx_waddr:RO；位位置：[9:0]；默认值：0；当软件通过APB写入Tx FIFO时，该寄存器将偏移地址存储在Tx FIFO中。
         */
        uint32_t apb_tx_waddr:10;
        uint32_t reserved_10:1;
        /** tx_raddr:RO；比特位置：[20:11]；默认值：0；当Tx FSM通过Tx-FIFO_Ctrl读取数据时，该寄存器将偏移地址存储在Tx FIFO中。
         */
        uint32_t tx_raddr:10;
        uint32_t reserved_21:11;
    };
    uint32_t val;
} uart_mem_tx_status_reg_t;

/** mem_rx_status寄存器rx FIFO写入和读取偏移地址的类型。
 */
typedef union {
    struct {
        /** apb_rx-raddr:RO；位位置：[9:0]；默认值：512；当软件通过APB从RX FIFO读取数据时，该寄存器将偏移地址存储在RX-FIFO中。UART0为10'4200。UART1为10'280。UART2为10'300。
         */
        uint32_t apb_rx_raddr:10;
        uint32_t reserved_10:1;
        /** rx_addr:RO；比特位置：[20:11]；默认值：512；当Rx-FIFO_Ctrl写入Rx FIFO时，该寄存器将偏移地址存储在Rx FIFO中。UART0为10'4200。UART1为10'280。UART2为10'300。
         */
        uint32_t rx_waddr:10;
        uint32_t reserved_21:11;
    };
    uint32_t val;
} uart_mem_rx_status_reg_t;

/** fsm_status寄存器UART发送和接收状态的类型。
 */
typedef union {
    struct {
        /** st_urx_out:RO；位位置：[3:0]；默认值：0；这是接收器的状态寄存器。
         */
        uint32_t st_urx_out:4;
        /** st_utx_out:RO；位位置：[7:4]；默认值：0；这是变送器的状态寄存器。
         */
        uint32_t st_utx_out:4;
        uint32_t reserved_8:24;
    };
    uint32_t val;
} uart_fsm_status_reg_t;


/**组：Autobaud寄存器*/
/** 低脉冲寄存器类型Autobaud最小低脉冲持续时间寄存器
 */
typedef union {
    struct {
        /** lowpulse_min_cnt:RO；位位置：[11:0]；默认值：4095；该寄存器存储低电平脉冲的最小持续时间值。它用于波特率检测过程。
         */
        uint32_t lowpulse_min_cnt:12;
        uint32_t reserved_12:20;
    };
    uint32_t val;
} uart_lowpulse_reg_t;

/** 高脉冲寄存器类型Autobaud最小高脉冲持续时间寄存器
 */
typedef union {
    struct {
        /** highpulse_min_cnt:RO；位位置：[11:0]；默认值：4095；该寄存器存储高电平脉冲的最大持续时间值。它用于波特率检测过程。
         */
        uint32_t highpulse_min_cnt:12;
        uint32_t reserved_12:20;
    };
    uint32_t val;
} uart_highpulse_reg_t;

/** rxd_cnt寄存器类型Autobaud边缘变化计数寄存器
 */
typedef union {
    struct {
        /** rxd_edge_cnt:RO；位位置：[9:0]；默认值：0；此寄存器存储rxd边缘变化的计数。它用于波特率检测过程。
         */
        uint32_t rxd_edge_cnt:10;
        uint32_t reserved_10:22;
    };
    uint32_t val;
} uart_rxd_cnt_reg_t;

/** pospulse寄存器类型Autobaud高脉冲寄存器
 */
typedef union {
    struct {
        /** posedge_min_cnt:RO；位位置：[11:0]；默认值：4095；该寄存器存储两个正边缘之间的最小输入时钟计数。它被应用于boudrate检测过程。
         */
        uint32_t posedge_min_cnt:12;
        uint32_t reserved_12:20;
    };
    uint32_t val;
} uart_pospulse_reg_t;

/** 负脉冲寄存器类型Autobaud低脉冲寄存器
 */
typedef union {
    struct {
        /** negege_min_cnt:RO；位位置：[11:0]；默认值：4095；该寄存器存储两个负边缘之间的最小输入时钟计数。它被应用于boudrate检测过程。
         */
        uint32_t negedge_min_cnt:12;
        uint32_t reserved_12:20;
    };
    uint32_t val;
} uart_negpulse_reg_t;


/**组：AT转义序列选择配置*/
/** at_cmd_precnt寄存器的类型序列前定时配置
 */
typedef union {
    struct {
        /** pre_idle_num:R/W；比特位置：[15:0]；默认值：2305；该寄存器用于配置接收机接收第一个at_cmd之前的空闲持续时间。
         */
        uint32_t pre_idle_num:16;
        uint32_t reserved_16:16;
    };
    uint32_t val;
} uart_at_cmd_precnt_reg_t;

/** at_cmd_postcnt寄存器的类型后序定时配置
 */
typedef union {
    struct {
        /** post_idle_num:R/W；比特位置：[15:0]；默认值：2305；此寄存器用于配置上一个at_cmd和下一个数据之间的持续时间。
         */
        uint32_t post_idle_num:16;
        uint32_t reserved_16:16;
    };
    uint32_t val;
} uart_at_cmd_postcnt_reg_t;

/** at_cmd_gaptout寄存器超时配置的类型
 */
typedef union {
    struct {
        /** rx间隙_输出：R/W；比特位置：[15:0]；默认值：11；此寄存器用于配置at_cmd字符之间的持续时间。
         */
        uint32_t rx_gap_tout:16;
        uint32_t reserved_16:16;
    };
    uint32_t val;
} uart_at_cmd_gaptout_reg_t;

/** at_cmd_char寄存器at转义序列检测配置的类型
 */
typedef union {
    struct {
        /** at_cmd_char:R/W；位位置：[7:0]；默认值：43；此寄存器用于配置at_cmd字符的内容。
         */
        uint32_t at_cmd_char:8;
        /** char_num:R/W；比特位置：[15:8]；默认值：3；此寄存器用于配置接收器接收的连续at_cmd字符数。
         */
        uint32_t char_num:8;
        uint32_t reserved_16:16;
    };
    uint32_t val;
} uart_at_cmd_char_reg_t;


/**组：版本寄存器*/
/** 日期寄存器类型UART版本寄存器
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：33587824；这是版本寄存器。
         */
        uint32_t date:32;
    };
    uint32_t val;
} uart_date_reg_t;

/** id寄存器类型UART id寄存器
 */
typedef union {
    struct {
        /** 编号：R/W；位位置：[29:0]；默认值：1280；此寄存器用于配置uart_id。
         */
        uint32_t id:30;
        /** 高速：R/W；位位置：[30]；默认值：1；此位用于选择同步模式。1： 寄存器自动同步到UART核心时钟，UART核心应与APB时钟保持一致。0：配置寄存器后，软件需要将1写入UART_REG_UPDATE以同步寄存器。
         */
        uint32_t high_speed:1;
        /** reg_update:R/W/SC；位位置：[31]；默认值：0；软件写入1将寄存器同步到UART核心时钟域，并在同步完成后由硬件清除。
         */
        uint32_t reg_update:1;
    };
    uint32_t val;
} uart_id_reg_t;


typedef struct {
    volatile uart_fifo_reg_t fifo;
    volatile uart_int_raw_reg_t int_raw;
    volatile uart_int_st_reg_t int_st;
    volatile uart_int_ena_reg_t int_ena;
    volatile uart_int_clr_reg_t int_clr;
    volatile uart_clkdiv_reg_t clkdiv;
    volatile uart_rx_filt_reg_t rx_filt;
    volatile uart_status_reg_t status;
    volatile uart_conf0_reg_t conf0;
    volatile uart_conf1_reg_t conf1;
    volatile uart_lowpulse_reg_t lowpulse;
    volatile uart_highpulse_reg_t highpulse;
    volatile uart_rxd_cnt_reg_t rxd_cnt;
    volatile uart_flow_conf_reg_t flow_conf;
    volatile uart_sleep_conf_reg_t sleep_conf;
    volatile uart_swfc_conf0_reg_t swfc_conf0;
    volatile uart_swfc_conf1_reg_t swfc_conf1;
    volatile uart_txbrk_conf_reg_t txbrk_conf;
    volatile uart_idle_conf_reg_t idle_conf;
    volatile uart_rs485_conf_reg_t rs485_conf;
    volatile uart_at_cmd_precnt_reg_t at_cmd_precnt;
    volatile uart_at_cmd_postcnt_reg_t at_cmd_postcnt;
    volatile uart_at_cmd_gaptout_reg_t at_cmd_gaptout;
    volatile uart_at_cmd_char_reg_t at_cmd_char;
    volatile uart_mem_conf_reg_t mem_conf;
    volatile uart_mem_tx_status_reg_t mem_tx_status;
    volatile uart_mem_rx_status_reg_t mem_rx_status;
    volatile uart_fsm_status_reg_t fsm_status;
    volatile uart_pospulse_reg_t pospulse;
    volatile uart_negpulse_reg_t negpulse;
    volatile uart_clk_conf_reg_t clk_conf;
    volatile uart_date_reg_t date;
    volatile uart_id_reg_t id;
} uart_dev_t;

extern uart_dev_t UART0;
extern uart_dev_t UART1;
extern uart_dev_t UART2;

#ifndef __cplusplus
_Static_assert(sizeof(uart_dev_t) == 0x84, "Invalid size of uart_dev_t structure");
_Static_assert(sizeof(UART0.fifo.rxfifo_rd_byte) == 4, "FIFO, must be a uint32_t, not bitfield!");
_Static_assert(sizeof(UART1.fifo.rxfifo_rd_byte) == 4, "FIFO, must be a uint32_t, not bitfield!");
_Static_assert(sizeof(UART2.fifo.rxfifo_rd_byte) == 4, "FIFO, must be a uint32_t, not bitfield!");
#endif

#ifdef __cplusplus
}
#endif

