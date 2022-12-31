/**
 * SPDX文件版权所有文本：2017-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**组：FIFO R/W寄存器*/
/** chndata寄存器类型通过APB FIFO读取和写入通道n的数据
 */
typedef union {
    struct {
        /** chn_data:RO；位位置：[31:0]；默认值：0；该寄存器用于通过APB FIFO读取和写入通道n的数据。
         */
        uint32_t chn_data: 32;
    };
    uint32_t val;
} rmt_chndata_reg_t;


/**组：配置寄存器*/
/** chncf0寄存器类型通道n配置寄存器0
 */
typedef union {
    struct {
        /** div_cnt:R/W；位位置：[7:0]；默认值：2；此字段用于配置信道n的时钟分频器。
         */
        uint32_t div_cnt: 8;
        /** 空闲阈值：R/W；比特位置：[23:8]；默认值：4096；当在比该字段值更长的连续时钟周期内没有检测到输入信号上的边沿时，接收结束。
         */
        uint32_t idle_thres: 16;
        /** mem_size:R/W；比特位置：[26:24]；默认值：1；此字段用于配置分配给信道n的最大块。有效范围为1~4-n。
         */
        uint32_t mem_size: 3;
        /** 载波eff_en:R/W；位位置：[27]；默认值：1；1： 仅在信道n的数据发送状态下对输出信号添加载波调制。0：在信道n所有状态下对信号添加载波调变。这里的状态包括空闲状态（ST_idle）、从RAM读取数据（ST_RD_MEM）和发送存储在RAM中的数据（ST_SEND）。仅当RMT_CARRIR_EN_CHn设置为1时有效。
         */
        uint32_t carrier_eff_en: 1;
        /** carrier_en:R/W；位位置：[28]；默认值：1；此位用于启用信道n的载波调制。1：在输出信号上添加载波调制。0：输出信号无载波调制。
         */
        uint32_t carrier_en: 1;
        /** carrier_out_lv:R/W；位位置：[29]；默认值：1；该位用于配置信道n的载波位置。
         *
         *  1’0：在低电平输出信号上添加载波。
         *
         *  1'h1：在高电平输出信号上添加载波。
         */
        uint32_t carrier_out_lv: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} rmt_chnconf0_reg_t;

/** chnconf1寄存器类型通道n配置寄存器1
 */
typedef union {
    struct {
        /** tx_start:R/W；位位置：[0]；默认值：0；设置此位以开始在通道n上发送数据。
         */
        uint32_t tx_start: 1;
        /** rx_en:R/W；位位置：[1]；默认值：0；设置此位以使接收机能够在信道n上接收数据。
         */
        uint32_t rx_en: 1;
        /** mem_wr_rst:WO；位位置：[2]；默认值：0；设置此位以重置接收器为通道n访问的RAM写入地址。
         */
        uint32_t mem_wr_rst: 1;
        /** mem_rd_rst:WO；位位置：[3]；默认值：0；设置此位以重置发射机为信道n访问的RAM读取地址。
         */
        uint32_t mem_rd_rst: 1;
        /** apb_mem_rst:WO；位位置：[4]；默认值：0；设置此位以通过访问apb fifo重置通道n的W/R ram地址。
         */
        uint32_t apb_mem_rst: 1;
        /** 内存所有者：R/W；位位置：[5]；默认值：1；该位标记通道n的RAM块的所有权。
         *
         *  1’1：接收器正在使用RAM。
         *
         *  1’0：发射器正在使用RAM。
         */
        uint32_t mem_owner: 1;
        /** tx_conti_mode:R/W；位位置：[6]；默认值：0；设置此位以从信道n中的第一个数据重新开始连续节点中的传输。
         */
        uint32_t tx_conti_mode: 1;
        /** rx滤波器-en:R/W；位位置：[7]；默认值：0；设置此位以启用信道n的接收机滤波器。
         */
        uint32_t rx_filter_en: 1;
        /** rx滤波器阈值：R/W；比特位置：[15:8]；默认值：15；在接收模式下，当输入脉冲的宽度小于RMT_RX_FILTER_THRES_CHn APB时钟周期时，将此字段设置为忽略输入脉冲。
         */
        uint32_t rx_filter_thres: 8;
        /** chk_rx_carrier_en:R/W；位位置：[16]；默认值：0；当信道n启用载波调制时，设置此位以启用存储器环路读取模式。
         */
        uint32_t chk_rx_carrier_en: 1;
        /** ref_always_on:R/W；位位置：[17]；默认值：0；设置此位以选择信道n的基准时钟。
         *
         *  1'H:APB_CLK 1'H:REF_TICK
         */
        uint32_t ref_always_on: 1;
        /** idle_out_lv:R/W；位位置：[18]；默认值：0；当发射机处于空闲状态时，该位配置信道n中输出信号的电平。
         */
        uint32_t idle_out_lv: 1;
        /** idle_out_en:R/W；位位置：[19]；默认值：0；这是空闲状态下通道n的输出启用位。
         */
        uint32_t idle_out_en: 1;
        /** tx_stop:R/W；位位置：[20]；默认值：0；设置此位以停止信道n的发射机发送数据。
         */
        uint32_t tx_stop: 1;
        uint32_t reserved_21: 11;
    };
    uint32_t val;
} rmt_chnconf1_reg_t;

/** apb_conf寄存器类型RMT apb配置寄存器
 */
typedef union {
    struct {
        /** apb_fifo_mask:R/W；位位置：[0]；默认值：0；1’1：直接访问内存。1’0：通过APB FIFO访问内存。
         */
        uint32_t apb_fifo_mask: 1;
        /** mem_tx_wrap_en:R/W；位位置：[1]；默认值：0；设置此位以启用换行模式。
         */
        uint32_t mem_tx_wrap_en: 1;
        /** mem_clk_force_on:R/W；位位置：[2]；默认值：1；设置此位以在RMT模块开始工作时启用RAM时钟，在RMT停止工作时禁用此时钟，以实现低功耗方案。
         */
        uint32_t mem_clk_force_on: 1;
        /** mem_force_pd:R/W；位位置：[3]；默认值：0；设置此位以关闭RMT内存。
         */
        uint32_t mem_force_pd: 1;
        /** mem_force_pu:R/W；位位置：[4]；默认值：0；1： 禁用RAM的轻睡眠断电功能。0：当RMT处于轻睡眠模式时，关闭RMT RAM。
         */
        uint32_t mem_force_pu: 1;
        uint32_t reserved_5: 26;
        /** clk_en:R/W；位位置：[31]；默认值：0；RMT寄存器的时钟门控启用位，以实现低功耗方案。1： 为RMT寄存器通电驱动时钟。0：关闭RMT寄存器的驱动器时钟。
         */
        uint32_t clk_en: 1;
    };
    uint32_t val;
} rmt_apb_conf_reg_t;

/** ref_cnt_rst寄存器类型RMT时钟分频器复位寄存器
 */
typedef union {
    struct {
        /** ref_cnt_rst_ch0:R/W；位位置：[0]；默认值：0；该位用于重置信道0的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch0: 1;
        /** ref_cnt_rst_ch1:R/W；位位置：[1]；默认值：0；该位用于重置信道1的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch1: 1;
        /** ref_cnt_rst_ch2:R/W；位位置：[2]；默认值：0；该位用于重置信道2的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch2: 1;
        /** ref_cnt_rst_ch3:R/W；位位置：[3]；默认值：0；该位用于重置信道3的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch3: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} rmt_ref_cnt_rst_reg_t;

/** chn_rx-carrier_rm寄存器类型通道n载波删除寄存器
 */
typedef union {
    struct {
        /** 载波低阈值：R/W；比特位置：[15:0]；默认值：0；载波调制模式中的低电平周期是信道n的（RMT_CARRIR_low_THRES_CHn+1）个时钟周期。
         */
        uint32_t carrier_low_thres_ch: 16;
        /** 载波高阈值：R/W；比特位置：[31:16]；默认值：0；载波调制模式中的高电平周期是信道n的（RMT_CARRIR_high_THRES_CHn+1）时钟周期。
         */
        uint32_t carrier_high_thres_ch: 16;
    };
    uint32_t val;
} rmt_chn_rx_carrier_rm_reg_t;


/**组：状态寄存器*/
/** chnstatus寄存器类型通道n状态寄存器
 */
typedef union {
    struct {
        /** mem_waddr_ex:RO；位位置：[8:0]；默认值：0；当信道n的接收机使用RAM时，该字段记录存储器地址偏移。
         */
        uint32_t mem_waddr_ex: 9;
        uint32_t reserved_9: 1;
        /** mem_raddr_ex:RO；比特位置：[18:10]；默认值：0；当信道n的发射机使用RAM时，该字段记录存储器地址偏移。
         */
        uint32_t mem_raddr_ex: 9;
        uint32_t reserved_19: 1;
        /** 状态：RO；比特位置：[22:20]；默认值：0；此字段记录通道n的FSM状态。
         */
        uint32_t state: 3;
        /** mem_owner_err:RO；位位置：[23]；默认值：0；当内存块的所有权被侵犯时，将设置此状态位。
         */
        uint32_t mem_owner_err: 1;
        /** mem_full:RO；位位置：[24]；默认值：0；如果接收器接收的数据超过存储器允许的数据量，则将设置此状态位。
         */
        uint32_t mem_full: 1;
        /** mem_empty:RO；位位置：[25]；默认值：0；当要发送的数据超过内存允许的范围并且包装模式被禁用时，将设置此状态位。
         */
        uint32_t mem_empty: 1;
        /** apb_mem_wr_err:RO；位位置：[26]；默认值：0；当通过APB总线写入RAM时，如果偏移地址超出内存大小，将设置此状态位。
         */
        uint32_t apb_mem_wr_err: 1;
        /** apb_mem_rd_err:RO；位位置：[27]；默认值：0；当通过APB总线读取RAM时，如果偏移地址超出内存大小，将设置此状态位。
         */
        uint32_t apb_mem_rd_err: 1;
        uint32_t reserved_28: 4;
    };
    uint32_t val;
} rmt_chnstatus_reg_t;

/** chnaddr寄存器类型通道n地址寄存器
 */
typedef union {
    struct {
        /** apb_mem_waddr_ch0:RO；位位置：[8:0]；默认值：0；该字段记录通道n通过APB总线写入RAM时的内存地址偏移。
         */
        uint32_t apb_mem_waddr_ch0: 9;
        uint32_t reserved_9: 1;
        /** apb_mem_raddr_ch0:RO；比特位置：[18:10]；默认值：0；该字段记录通道n通过APB总线读取RAM时的内存地址偏移。
         */
        uint32_t apb_mem_raddr_ch0: 9;
        uint32_t reserved_19: 13;
    };
    uint32_t val;
} rmt_chnaddr_reg_t;


/**组：中断寄存器*/
/** int_raw寄存器类型原始中断状态寄存器
 */
typedef union {
    struct {
        /** ch0_tx_end_int_raw:RO；位位置：[0]；默认值：0；信道0的中断原始位。传输结束时触发。
         */
        uint32_t ch0_tx_end_int_raw: 1;
        /** ch0_rx_end_int_raw:RO；位位置：[1]；默认值：0；信道0的中断原始位。接收结束时触发。
         */
        uint32_t ch0_rx_end_int_raw: 1;
        /** ch0_err_int_raw:RO；位位置：[2]；默认值：0；通道0的中断原始位。发生错误时触发。
         */
        uint32_t ch0_err_int_raw: 1;
        /** ch1_tx_end_int_raw:RO；位位置：[3]；默认值：0；信道1的中断原始位。传输结束时触发。
         */
        uint32_t ch1_tx_end_int_raw: 1;
        /** ch1_rx_end_int_raw:RO；位位置：[4]；默认值：0；信道1的中断原始位。接收结束时触发。
         */
        uint32_t ch1_rx_end_int_raw: 1;
        /** ch1_err_int_raw:RO；位位置：[5]；默认值：0；通道1的中断原始位。发生错误时触发。
         */
        uint32_t ch1_err_int_raw: 1;
        /** ch2_tx_end_int_raw:RO；位位置：[6]；默认值：0；信道2的中断原始位。传输结束时触发。
         */
        uint32_t ch2_tx_end_int_raw: 1;
        /** ch2_rx_end_int_raw:RO；位位置：[7]；默认值：0；信道2的中断原始位。接收结束时触发。
         */
        uint32_t ch2_rx_end_int_raw: 1;
        /** ch2_err_int_raw:RO；位位置：[8]；默认值：0；通道2的中断原始位。发生错误时触发。
         */
        uint32_t ch2_err_int_raw: 1;
        /** ch3_tx_end_int_raw:RO；位位置：[9]；默认值：0；信道3的中断原始位。传输结束时触发。
         */
        uint32_t ch3_tx_end_int_raw: 1;
        /** ch3_rx_end_int_raw:RO；位位置：[10]；默认值：0；信道3的中断原始位。接收结束时触发。
         */
        uint32_t ch3_rx_end_int_raw: 1;
        /** ch3_err_int_raw:RO；位位置：[11]；默认值：0；通道3的中断原始位。发生错误时触发。
         */
        uint32_t ch3_err_int_raw: 1;
        /** ch0_tx_thr_event_int_raw:RO；位位置：[12]；默认值：0；通道0的中断原始位。当变送器发送的数据超过配置值时触发。
         */
        uint32_t ch0_tx_thr_event_int_raw: 1;
        /** ch1_tx_thr_event_int_raw:RO；位位置：[13]；默认值：0；通道1的中断原始位。当变送器发送的数据超过配置值时触发。
         */
        uint32_t ch1_tx_thr_event_int_raw: 1;
        /** ch2_tx_thr_event_int_raw:RO；位位置：[14]；默认值：0；通道2的中断原始位。当变送器发送的数据超过配置值时触发。
         */
        uint32_t ch2_tx_thr_event_int_raw: 1;
        /** ch3_tx_thr_event_int_raw:RO；位位置：[15]；默认值：0；通道3的中断原始位。当变送器发送的数据超过配置值时触发。
         */
        uint32_t ch3_tx_thr_event_int_raw: 1;
        /** ch0_tx_lop_int_raw:RO；位位置：[16]；默认值：0；通道0的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch0_tx_loop_int_raw: 1;
        /** ch1_tx_loop_int_raw:RO；位位置：[17]；默认值：0；通道1的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch1_tx_loop_int_raw: 1;
        /** ch2_tx_loop_int_raw:RO；位位置：[18]；默认值：0；通道2的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch2_tx_loop_int_raw: 1;
        /** ch3_tx_loop_int_raw:RO；位位置：[19]；默认值：0；通道3的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch3_tx_loop_int_raw: 1;
        uint32_t reserved_20: 12;
    };
    uint32_t val;
} rmt_int_raw_reg_t;

/** int_st寄存器类型屏蔽中断状态寄存器
 */
typedef union {
    struct {
        /** ch0_tx_end_int_st:RO；位位置：[0]；默认值：0；RMT_CH0_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch0_tx_end_int_st: 1;
        /** ch0_rx_end_int_st:RO；位位置：[1]；默认值：0；RMT_CH0_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch0_rx_end_int_st: 1;
        /** ch0_err_int_st:RO；位位置：[2]；默认值：0；RMT_CH0_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch0_err_int_st: 1;
        /** ch1_tx_end_int_st:RO；位位置：[3]；默认值：0；RMT_CH1_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch1_tx_end_int_st: 1;
        /** ch1_rx_end_int_st:RO；位位置：[4]；默认值：0；RMT_CH1_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch1_rx_end_int_st: 1;
        /** ch1_err_int_st:RO；位位置：[5]；默认值：0；RMT_CH1_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch1_err_int_st: 1;
        /** ch2_tx_end_int_st:RO；位位置：[6]；默认值：0；RMT_CH2_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch2_tx_end_int_st: 1;
        /** ch2_rx_end_int_st:RO；位位置：[7]；默认值：0；RMT_CH2_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch2_rx_end_int_st: 1;
        /** ch2_err_int_st:RO；位位置：[8]；默认值：0；RMT_CH2_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch2_err_int_st: 1;
        /** ch3_tx_end_int_st:RO；位位置：[9]；默认值：0；RMT_CH3_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch3_tx_end_int_st: 1;
        /** ch3_rx_end_int_st:RO；位位置：[10]；默认值：0；RMT_CH3_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch3_rx_end_int_st: 1;
        /** ch3_err_int_st:RO；位位置：[11]；默认值：0；RMT_CH3_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch3_err_int_st: 1;
        /** ch0_tx_thr_event_int_st:RO；位位置：[12]；默认值：0；RMT_CH0_TTX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch0_tx_thr_event_int_st: 1;
        /** ch1_tx_thr_event_int_st:RO；位位置：[13]；默认值：0；RMT_CH1_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch1_tx_thr_event_int_st: 1;
        /** ch2_tx_thr_event_int_st:RO；位位置：[14]；默认值：0；RMT_CH2_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch2_tx_thr_event_int_st: 1;
        /** ch3_tx_thr_event_int_st:RO；位位置：[15]；默认值：0；RMT_CH3_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch3_tx_thr_event_int_st: 1;
        /** ch0_tx_lop_int_st:RO；位位置：[16]；默认值：0；RMT_CH0_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch0_tx_loop_int_st: 1;
        /** ch1_tx_loop_int_st:RO；位位置：[17]；默认值：0；RMT_CH1_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch1_tx_loop_int_st: 1;
        /** ch2_tx_loop_int_st:RO；位位置：[18]；默认值：0；RMT_CH2_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch2_tx_loop_int_st: 1;
        /** ch3_tx_loop_int_st:RO；位位置：[19]；默认值：0；RMT_CH3_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch3_tx_loop_int_st: 1;
        uint32_t reserved_20: 12;
    };
    uint32_t val;
} rmt_int_st_reg_t;

/** int_ena寄存器类型中断启用寄存器
 */
typedef union {
    struct {
        /** ch0_tx_end_int_ena:R/W；位位置：[0]；默认值：0；RMT_CH0_TX_END_INT的中断启用位。
         */
        uint32_t ch0_tx_end_int_ena: 1;
        /** ch0_rx_end_int_ena:R/W；位位置：[1]；默认值：0；RMT_CH0_RX_END_INT的中断启用位。
         */
        uint32_t ch0_rx_end_int_ena: 1;
        /** ch0_err_int_ena:R/W；位位置：[2]；默认值：0；RMT_CH0_ERR_INT的中断启用位。
         */
        uint32_t ch0_err_int_ena: 1;
        /** ch1_tx_end_int_ena:R/W；位位置：[3]；默认值：0；RMT_CH1_TX_END_INT的中断启用位。
         */
        uint32_t ch1_tx_end_int_ena: 1;
        /** ch1_rx_end_int_ena:R/W；位位置：[4]；默认值：0；RMT_CH1_RX_END_INT的中断启用位。
         */
        uint32_t ch1_rx_end_int_ena: 1;
        /** ch1_err_int_ena:R/W；位位置：[5]；默认值：0；RMT_CH1_ERR_INT的中断启用位。
         */
        uint32_t ch1_err_int_ena: 1;
        /** ch2_tx_end_int_ena:R/W；位位置：[6]；默认值：0；RMT_CH2_TX_END_INT的中断启用位。
         */
        uint32_t ch2_tx_end_int_ena: 1;
        /** ch2_rx_end_int_ena:R/W；位位置：[7]；默认值：0；RMT_CH2_RX_END_INT的中断启用位。
         */
        uint32_t ch2_rx_end_int_ena: 1;
        /** ch2_err_int_ena:R/W；位位置：[8]；默认值：0；RMT_CH2_ERR_INT的中断启用位。
         */
        uint32_t ch2_err_int_ena: 1;
        /** ch3_tx_end_int_ena:R/W；位位置：[9]；默认值：0；RMT_CH3_TX_END_INT的中断启用位。
         */
        uint32_t ch3_tx_end_int_ena: 1;
        /** ch3_rx_end_int_ena:R/W；位位置：[10]；默认值：0；RMT_CH3_RX_END_INT的中断启用位。
         */
        uint32_t ch3_rx_end_int_ena: 1;
        /** ch3_err_int_ena:R/W；位位置：[11]；默认值：0；RMT_CH3_ERR_INT的中断启用位。
         */
        uint32_t ch3_err_int_ena: 1;
        /** ch0_tx_thr_event_int_ena:R/W；位位置：[12]；默认值：0；RMT_CH0_TTX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch0_tx_thr_event_int_ena: 1;
        /** ch1_tx_thr_event_int_ena:R/W；位位置：[13]；默认值：0；RMT_CH1_TX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch1_tx_thr_event_int_ena: 1;
        /** ch2_tx_thr_event_int_ena:R/W；位位置：[14]；默认值：0；RMT_CH2_TX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch2_tx_thr_event_int_ena: 1;
        /** ch3_tx_thr_event_int_ena:R/W；位位置：[15]；默认值：0；RMT_CH3_TX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch3_tx_thr_event_int_ena: 1;
        /** ch0_tx_lop_int_ena:R/W；位位置：[16]；默认值：0；RMT_CH0_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch0_tx_loop_int_ena: 1;
        /** ch1_tx_loop_int_ena:R/W；位位置：[17]；默认值：0；RMT_CH1_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch1_tx_loop_int_ena: 1;
        /** ch2_tx_loop_int_ena:R/W；位位置：[18]；默认值：0；RMT_CH2_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch2_tx_loop_int_ena: 1;
        /** ch3_tx_loop_int_ena:R/W；位位置：[19]；默认值：0；RMT_CH3_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch3_tx_loop_int_ena: 1;
        uint32_t reserved_20: 12;
    };
    uint32_t val;
} rmt_int_ena_reg_t;

/** int_clr寄存器类型中断清除寄存器
 */
typedef union {
    struct {
        /** ch0_tx_end_int_clr:工单；位位置：[0]；默认值：0；设置此位以清除RMT_CH0_TX_END_INT中断。
         */
        uint32_t ch0_tx_end_int_clr: 1;
        /** ch0_rx_end_int_clr：工单；位位置：[1]；默认值：0；设置此位以清除RMT_CH0_RX_END_INT中断。
         */
        uint32_t ch0_rx_end_int_clr: 1;
        /** ch0_err_int_clr:工单；位位置：[2]；默认值：0；设置此位以清除RMT_CH0_ERR_INT中断。
         */
        uint32_t ch0_err_int_clr: 1;
        /** ch1_tx_end_int_clr:工单；位位置：[3]；默认值：0；设置此位以清除RMT_CH1_TX_END_INT中断。
         */
        uint32_t ch1_tx_end_int_clr: 1;
        /** ch1_rx_end_int_clr:工单；位位置：[4]；默认值：0；设置此位以清除RMT_CH1_RX_END_INT中断。
         */
        uint32_t ch1_rx_end_int_clr: 1;
        /** ch1_err_int_clr:WO；位位置：[5]；默认值：0；设置此位以清除RMT_CH1_ERR_INT中断。
         */
        uint32_t ch1_err_int_clr: 1;
        /** ch2_tx_end_int_clr:工单；位位置：[6]；默认值：0；设置此位以清除RMT_CH2_TX_END_INT中断。
         */
        uint32_t ch2_tx_end_int_clr: 1;
        /** ch2_rx_end_int_clr：工单；位位置：[7]；默认值：0；设置此位以清除RMT_CH2_RX_END_INT中断。
         */
        uint32_t ch2_rx_end_int_clr: 1;
        /** ch2_err_int_clr:工单；位位置：[8]；默认值：0；设置此位以清除RMT_CH2_ERR_INT中断。
         */
        uint32_t ch2_err_int_clr: 1;
        /** ch3_tx_end_int_clr:工单；位位置：[9]；默认值：0；设置此位以清除RMT_CH3_TX_END_INT中断。
         */
        uint32_t ch3_tx_end_int_clr: 1;
        /** ch3_rx_end_int_clr：工单；位位置：[10]；默认值：0；设置此位以清除RMT_CH3_RX_END_INT中断。
         */
        uint32_t ch3_rx_end_int_clr: 1;
        /** ch3_err_int_clr:工单；位位置：[11]；默认值：0；设置此位以清除RMT_CH3_ERR_INT中断。
         */
        uint32_t ch3_err_int_clr: 1;
        /** ch0_tx_thr_event_int_clr:工单；位位置：[12]；默认值：0；设置此位以清除RMT_CH0_TX_THR_EVENT_INT中断。
         */
        uint32_t ch0_tx_thr_event_int_clr: 1;
        /** ch1_tx_thr_event_int_clr:工单；位位置：[13]；默认值：0；设置此位以清除RMT_CH1_TX_THR_EVENT_INT中断。
         */
        uint32_t ch1_tx_thr_event_int_clr: 1;
        /** ch2_tx_thr_event_int_clr:工单；位位置：[14]；默认值：0；设置此位以清除RMT_CH2_TX_THR_EVENT_INT中断。
         */
        uint32_t ch2_tx_thr_event_int_clr: 1;
        /** ch3_tx_thr_event_int_clr:工单；位位置：[15]；默认值：0；设置此位以清除RMT_CH3_TX_THR_EVENT_INT中断。
         */
        uint32_t ch3_tx_thr_event_int_clr: 1;
        /** ch0_tx_lop_int_clr:WO；位位置：[16]；默认值：0；设置此位以清除RMT_CH0_TX_LOOP_INT中断。
         */
        uint32_t ch0_tx_loop_int_clr: 1;
        /** ch1_tx_loop_int_clr:工单；位位置：[17]；默认值：0；设置此位以清除RMT_CH1_TX_LOOP_INT中断。
         */
        uint32_t ch1_tx_loop_int_clr: 1;
        /** ch2_tx_loop_int_clr:工单；位位置：[18]；默认值：0；设置此位以清除RMT_CH2_TX_LOOP_INT中断。
         */
        uint32_t ch2_tx_loop_int_clr: 1;
        /** ch3_tx_loop_int_clr:工单；位位置：[19]；默认值：0；设置此位以清除RMT_CH3_TX_LOOP_INT中断。
         */
        uint32_t ch3_tx_loop_int_clr: 1;
        uint32_t reserved_20: 12;
    };
    uint32_t val;
} rmt_int_clr_reg_t;


/**组：载波占空比寄存器*/
/** chncrier_duty寄存器类型通道n占空比配置寄存器
 */
typedef union {
    struct {
        /** 低：R/W；比特位置：[15:0]；默认值：64；该字段用于配置信道n的低电平载波的时钟周期。
         */
        uint32_t low: 16;
        /** 高：R/W；比特位置：[31:16]；默认值：64；该字段用于配置信道n的高电平载波的时钟周期。
         */
        uint32_t high: 16;
    };
    uint32_t val;
} rmt_chncarrier_duty_reg_t;


/**组：Tx事件配置寄存器*/
/** chn_tx-lim寄存器类型通道n tx事件配置寄存器
 */
typedef union {
    struct {
        /** tx_lim：右侧；位位置：[8:0]；默认值：128；此字段用于配置通道n可以发送的最大条目。当RMT_MEM_SIZE_CHn=1时，此字段可以设置为0~128（6432/16=128）之间的任何值。当RMT_MEM_SIZE_CHn>1时，此字段可以设置为（0~128）RMT_MEM-SIZE_CHn中的任何值。
         */
        uint32_t tx_lim: 9;
        /** tx_loop_num:R/W；比特位置：[18:9]；默认值：0；此字段用于配置启用连续传输模式时的最大循环时间。
         */
        uint32_t tx_loop_num: 10;
        /** tx_loop_cnt_en:R/W；位位置：[19]；默认值：0；此位用于启用循环计数。
         */
        uint32_t tx_loop_cnt_en: 1;
        /** loop_count_reset：工单；位位置：[20]；默认值：0；当连续传输模式有效时，该位用于重置循环计数。
         */
        uint32_t loop_count_reset: 1;
        uint32_t reserved_21: 11;
    };
    uint32_t val;
} rmt_chn_tx_lim_reg_t;

/** tx_sim寄存器类型启用RMT同时传输
 */
typedef union {
    struct {
        /** tx_sim_ch0:R/W；位位置：[0]；默认值：0；设置此位以启用通道0，以便与其他启用的通道同时开始发送数据。
         */
        uint32_t tx_sim_ch0: 1;
        /** tx_sim_ch1:R/W；位位置：[1]；默认值：0；设置此位以使信道1能够与其他启用的信道同时开始发送数据。
         */
        uint32_t tx_sim_ch1: 1;
        /** tx_sim_ch2:R/W；位位置：[2]；默认值：0；设置此位以使信道2能够与其他启用的信道同时开始发送数据。
         */
        uint32_t tx_sim_ch2: 1;
        /** tx_sim_ch3:R/W；位位置：[3]；默认值：0；设置此位以启用通道3，使其能够与其他启用的通道同时开始发送数据。
         */
        uint32_t tx_sim_ch3: 1;
        /** tx_sim_en:R/W；位位置：[4]；默认值：0；该位用于使多个信道同时开始发送数据。
         */
        uint32_t en: 1;
        uint32_t reserved_5: 27;
    };
    uint32_t val;
} rmt_tx_sim_reg_t;


/**组：版本寄存器*/
/** 日期寄存器类型版本控制寄存器
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：41989881；版本控制寄存器
         */
        uint32_t date: 32;
    };
    uint32_t val;
} rmt_date_reg_t;


typedef struct rmt_dev_t {
    volatile rmt_chndata_reg_t data_ch[4];
    volatile struct {
        volatile rmt_chnconf0_reg_t conf0;
        volatile rmt_chnconf1_reg_t conf1;
    } conf_ch[4];
    volatile rmt_chnstatus_reg_t status_ch[4];
    volatile rmt_chnaddr_reg_t apb_mem_addr_ch[4];
    volatile rmt_int_raw_reg_t int_raw;
    volatile rmt_int_st_reg_t int_st;
    volatile rmt_int_ena_reg_t int_ena;
    volatile rmt_int_clr_reg_t int_clr;
    volatile rmt_chncarrier_duty_reg_t carrier_duty_ch[4];
    volatile rmt_chn_tx_lim_reg_t tx_lim_ch[4];
    volatile rmt_apb_conf_reg_t apb_conf;
    volatile rmt_tx_sim_reg_t tx_sim;
    volatile rmt_ref_cnt_rst_reg_t ref_cnt_rst;
    volatile rmt_chn_rx_carrier_rm_reg_t ch_rx_carrier_rm[4];
    uint32_t reserved_09c[24];
    volatile rmt_date_reg_t date;
} rmt_dev_t;


#ifndef __cplusplus
_Static_assert(sizeof(rmt_dev_t) == 0x100, "Invalid size of rmt_dev_t structure");
#endif

extern rmt_dev_t RMT;

typedef struct {
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
    } chan[4];
} rmt_mem_t;

extern rmt_mem_t RMTMEM;

#ifdef __cplusplus
}
#endif

