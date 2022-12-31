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

/**组：FIFO R/W寄存器*/
/** chndata寄存器的类型通过apb-fifo访问的CHANNELn的读写数据寄存器。
 */
typedef union {
    struct {
        /** chndata:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道n的数据。
         */
        uint32_t chndata: 32;
    };
    uint32_t val;
} rmt_chndata_reg_t;

/** chmdata寄存器的类型通过apb-fifo访问CHANNEL$n的读写数据寄存器。
 */
typedef union {
    struct {
        /** chmdata:RO；位位置：[31:0]；默认值：0；通过APB FIFO读取和写入通道$n的数据。
         */
        uint32_t chmdata: 32;
    };
    uint32_t val;
} rmt_chmdata_reg_t;


/**组：配置寄存器*/
/** chncf0寄存器类型通道n配置寄存器0
 */
typedef union {
    struct {
        /** tx_start_n:WT；位位置：[0]；默认值：0；设置此位以开始在CHANNELn上发送数据。
         */
        uint32_t tx_start_n: 1;
        /** mem_rd_rst_n:WT；位位置：[1]；默认值：0；设置此位以通过访问变送器重置CHANNELn的读ram地址。
         */
        uint32_t mem_rd_rst_n: 1;
        /** apb_mem_rst_n:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置CHANNELn的W/R ram地址。
         */
        uint32_t apb_mem_rst_n: 1;
        /** tx_conti_mode_n:R/W；位位置：[3]；默认值：0；设置此位以重新启动从CHANNELn中的第一个数据到最后一个数据的传输。
         */
        uint32_t tx_conti_mode_n: 1;
        /** mem_tx_wrap_en_n:R/W；位位置：[4]；默认值：0；这是环绕模式的通道n启用位：当要发送的数据超过其内存大小时，它将在开始时恢复发送。
         */
        uint32_t mem_tx_wrap_en_n: 1;
        /** idle_out_lv_n:R/W；位位置：[5]；默认值：0；当信道n处于空闲状态时，该位配置信道n中输出信号的电平。
         */
        uint32_t idle_out_lv_n: 1;
        /** idle_out_en_n:R/W；位位置：[6]；默认值：0；这是处于空闲状态的CHANNELn的输出启用控制位。
         */
        uint32_t idle_out_en_n: 1;
        /** tx_stop_n:R/W/SC；位位置：[7]；默认值：0；设置此位以停止CHANNELn的发射机发送数据。
         */
        uint32_t tx_stop_n: 1;
        /** div_cnt_n:R/W；比特位置：[15:8]；默认值：2；该寄存器用于配置CHANNELn时钟分频器。
         */
        uint32_t div_cnt_n: 8;
        /** mem_size_n:R/W；比特位置：[19:16]；默认值：1；此寄存器用于配置分配给CHANNELn的最大内存大小。
         */
        uint32_t mem_size_n: 4;
        /** 载波eff_en_n:R/W；位位置：[20]；默认值：1；1： 仅在信道n的发送数据状态下，在输出信号上添加载波调制。0：在信道n的所有状态下，在输出信号上添加载波调制。仅当RMT_CARRIR_EN_CHn为1时有效。
         */
        uint32_t carrier_eff_en_n: 1;
        /** 载波en_n:R/W；位位置：[21]；默认值：1；这是信道n的载波调制启用控制位。1： 在输出信号中添加载波调制。0：sig_out中无载波调制。
         */
        uint32_t carrier_en_n: 1;
        /** 载波out_lv_n:R/W；位位置：[22]；默认值：1；该位用于配置信道n的载波位置。
         *
         *  1’0：在低电平上添加载波。
         *
         *  1’h1：在高电平上添加载波。
         */
        uint32_t carrier_out_lv_n: 1;
        /** afifo_rst_n:WT；位位置：[23]；默认值：0；保留
         */
        uint32_t afifo_rst_n: 1;
        /** conf_update_n:WT；位位置：[24]；默认值：0；CHANNELn的同步位
         */
        uint32_t conf_update_n: 1;
        uint32_t reserved_25: 7;
    };
    uint32_t val;
} rmt_chnconf0_reg_t;

typedef struct {
    /** chmconf0寄存器类型通道m配置寄存器0
    */
    union {
        struct {
            /** div_cnt_m:R/W；位位置：[7:0]；默认值：2；该寄存器用于配置CHANNELm时钟分频器。
             */
            uint32_t div_cnt_m: 8;
            /** 空闲阈值m：R/W；比特位置：[22:8]；默认值：32767；当在输入信号上没有检测到边沿并且连续时钟周期长于该寄存器值时，接收过程结束。
             */
            uint32_t idle_thres_m: 15;
            uint32_t reserved_23: 1;
            /** mem_size_m:R/W；位位置：[27:24]；默认值：1；此寄存器用于配置分配给CHANNELm的最大内存大小。
             */
            uint32_t mem_size_m: 4;
            /** 载波en_m:R/W；位位置：[28]；默认值：1；这是CHANNELm的载波调制启用控制位。1： 在输出信号中添加载波调制。0：sig_out中无载波调制。
             */
            uint32_t carrier_en_m: 1;
            /** 载波out_lv_m:R/W；位位置：[29]；默认值：1；该位用于配置CHANNELm的载波位置。
             *
             *  1’0：在低电平上添加载波。
             *
             *  1’h1：在高电平上添加载波。
             */
            uint32_t carrier_out_lv_m: 1;
            uint32_t reserved_30: 2;
        };
        uint32_t val;
    } conf0;

    /** chmconf1寄存器类型通道m配置寄存器1
     */
    union {
        struct {
            /** rx_en_m：R/W；位位置：[0]；默认值：0；设置此位以使接收器能够在CHANNELm上接收数据。
             */
            uint32_t rx_en_m: 1;
            /** mem_wr_rst_m:WT；位位置：[1]；默认值：0；设置此位以通过访问接收器重置CHANNELm的写ram地址。
             */
            uint32_t mem_wr_rst_m: 1;
            /** apb_mem_rst_m:WT；位位置：[2]；默认值：0；设置此位以通过访问apb fifo重置CHANNELm的W/R ram地址。
             */
            uint32_t apb_mem_rst_m: 1;
            /** mem_owner_m:R/W/SC；位位置：[3]；默认值：1；此寄存器标记CHANNELm ram块的所有权。
             *
             *  1’1：接收器正在使用ram。
             *
             *  1':0:APB总线正在使用ram。
             */
            uint32_t mem_owner_m: 1;
            /** rx滤波器_en_m：R/W；位位置：[4]；默认值：0；这是CHANNELm的接收滤波器启用位。
             */
            uint32_t rx_filter_en_m: 1;
            /** rx滤波器阈值：R/W；比特位置：[12:5]；默认值：15；在APB时钟周期（接收模式）中，当输入脉冲的宽度小于此寄存器值时，忽略输入脉冲。
             */
            uint32_t rx_filter_thres_m: 8;
            /** mem_rx_wrap_en_m：读/写；位位置：[13]；默认值：0；这是环绕模式的通道m启用位：当要接收的数据大于其内存大小时，它将在开始时恢复接收。
             */
            uint32_t mem_rx_wrap_en_m: 1;
            /** afifo_rst_m:WT；位位置：[14]；默认值：0；保留
             */
            uint32_t afifo_rst_m: 1;
            /** conf_update_m:WT；位位置：[15]；默认值：0；CHANNELm的同步位
             */
            uint32_t conf_update_m: 1;
            uint32_t reserved_16: 16;
        };
        uint32_t val;
    } conf1;
} rmt_chmconf_reg_t;

/** chm_rx_carrier_rm寄存器类型信道m载波删除寄存器
 */
typedef union {
    struct {
        /** 载波低阈值chm:R/W；比特位置：[15:0]；默认值：0；对于信道m，载波调制模式中的低电平周期是（REG_RMT_REG_CARRIR_low_THRES_CHm+1）。
         */
        uint32_t carrier_low_thres_chm: 16;
        /** 载波高阈值：R/W；比特位置：[31:16]；默认值：0；对于信道m，载波调制模式中的高电平周期是（REG_RMT_REG_CARRIR_high_THRES_CHm+1）。
         */
        uint32_t carrier_high_thres_chm: 16;
    };
    uint32_t val;
} rmt_chm_rx_carrier_rm_reg_t;

/** sys_conf寄存器类型RMT apb配置寄存器
 */
typedef union {
    struct {
        /** apb_fifo_mask:R/W；位位置：[0]；默认值：0；1’1：直接访问内存。1’0：通过FIFO访问内存。
         */
        uint32_t apb_fifo_mask: 1;
        /** mem_clk_force_on:R/W；位位置：[1]；默认值：0；设置此位以启用RMT内存的时钟。
         */
        uint32_t mem_clk_force_on: 1;
        /** mem_force_pd:R/W；位位置：[2]；默认值：0；设置此位以关闭RMT内存。
         */
        uint32_t mem_force_pd: 1;
        /** mem_force_pu:R/W；位位置：[3]；默认值：0；1： 禁用RMT记忆灯睡眠断电功能。0：当RMT处于浅睡眠模式时，关闭RMT内存。
         */
        uint32_t mem_force_pu: 1;
        /** sclk_div_num:R/W；位位置：[11:4]；默认值：1；分数除数的整数部分
         */
        uint32_t sclk_div_num: 8;
        /** sclk_div_a:R/W；比特位置：[17:12]；默认值：0；分数除数的分数部分的分子
         */
        uint32_t sclk_div_a: 6;
        /** sclk_div_b:R/W；比特位置：[23:18]；默认值：0；分数除数的分数部分的分母
         */
        uint32_t sclk_div_b: 6;
        /** sclk_sel:R/W；位位置：[25:24]；默认值：1；选择rmtsclk的时钟源。1： CLK_80Mhz；2： CLK_8MHz；2： XTAL公司
         */
        uint32_t sclk_sel: 2;
        /** sclk_active:R/W；位位置：[26]；默认值：1；rmt_sclk开关
         */
        uint32_t sclk_active: 1;
        uint32_t reserved_27: 4;
        /** clk_en:R/W；位位置：[31]；默认值：0；RMT寄存器时钟门启用信号。1： 给寄存器的驱动时钟加电。0：关闭寄存器的驱动时钟
         */
        uint32_t clk_en: 1;
    };
    uint32_t val;
} rmt_sys_conf_reg_t;

/** ref_cnt_rst寄存器类型RMT时钟分频器复位寄存器
 */
typedef union {
    struct {
        /** ref_cnt_rst_ch0:WT；位位置：[0]；默认值：0；该寄存器用于重置信道0的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch0: 1;
        /** ref_cnt_rst_ch1:WT；位位置：[1]；默认值：0；该寄存器用于重置信道1的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch1: 1;
        /** ref_cnt_rst_ch2:WT；位位置：[2]；默认值：0；该寄存器用于重置信道2的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch2: 1;
        /** ref_cnt_rst_ch3:WT；位位置：[3]；默认值：0；该寄存器用于重置信道3的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch3: 1;
        /** ref_cnt_rst_ch4:WT；位位置：[4]；默认值：0；该寄存器用于重置信道4的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch4: 1;
        /** ref_cnt_rst_ch5:WT；位位置：[5]；默认值：0；该寄存器用于重置信道5的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch5: 1;
        /** ref_cnt_rst_ch6:WT；位位置：[6]；默认值：0；该寄存器用于重置信道6的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch6: 1;
        /** ref_cnt_rst_ch7:WT；位位置：[7]；默认值：0；该寄存器用于重置信道7的时钟分频器。
         */
        uint32_t ref_cnt_rst_ch7: 1;
        uint32_t reserved_8: 24;
    };
    uint32_t val;
} rmt_ref_cnt_rst_reg_t;


/**组：状态寄存器*/
/** chnstatus寄存器类型通道n状态寄存器
 */
typedef union {
    struct {
        /** mem_raddr_ex_n:RO；位位置：[9:0]；默认值：0；当信道n的发射机使用RAM时，该寄存器记录存储器地址偏移。
         */
        uint32_t mem_raddr_ex_n: 10;
        uint32_t reserved_10: 1;
        /** apb_mem_waddr_n:RO；比特位置：[20:11]；默认值：0；当通过APB总线写入RAM时，该寄存器记录内存地址偏移。
         */
        uint32_t apb_mem_waddr_n: 10;
        uint32_t reserved_21: 1;
        /** state_n:RO；位位置：[24:22]；默认值：0；此寄存器记录CHANNELn的FSM状态。
         */
        uint32_t state_n: 3;
        /** mem_empty_n:RO；位位置：[25]；默认值：0；当要设置的数据大于内存大小并且禁用环绕模式时，将设置此状态位。
         */
        uint32_t mem_empty_n: 1;
        /** apb_mem_wr_err_n:RO；位位置：[26]；默认值：0；当通过APB总线写入时，如果偏移地址超出内存大小，将设置此状态位。
         */
        uint32_t apb_mem_wr_err_n: 1;
        uint32_t reserved_27: 5;
    };
    uint32_t val;
} rmt_chnstatus_reg_t;

/** chmstatus寄存器类型通道m状态寄存器
 */
typedef union {
    struct {
        /** mem_waddr_ex_m:RO；位位置：[9:0]；默认值：192；当CHANNELm的接收器使用RAM时，该寄存器记录存储器地址偏移。
         */
        uint32_t mem_waddr_ex_m: 10;
        uint32_t reserved_10: 1;
        /** apb_mem_raddr_m:RO；比特位置：[20:11]；默认值：192；当通过APB总线读取RAM时，该寄存器记录内存地址偏移。
         */
        uint32_t apb_mem_raddr_m: 10;
        uint32_t reserved_21: 1;
        /** state_m:RO；位位置：[24:22]；默认值：0；此寄存器记录CHANNELm的FSM状态。
         */
        uint32_t state_m: 3;
        /** mem_owner_err_m:RO；位位置：[25]；默认值：0；当内存块的所有权错误时，将设置此状态位。
         */
        uint32_t mem_owner_err_m: 1;
        /** mem_full_m:RO；位位置：[26]；默认值：0；如果接收器接收到的数据超过内存大小，则设置此状态位。
         */
        uint32_t mem_full_m: 1;
        /** apb_mem_rd_err_m:RO；位位置：[27]；默认值：0；当通过APB总线读取时，如果偏移地址超出内存大小，将设置此状态位。
         */
        uint32_t apb_mem_rd_err_m: 1;
        uint32_t reserved_28: 4;
    };
    uint32_t val;
} rmt_chmstatus_reg_t;


/**组：中断寄存器*/
/** int_raw寄存器的类型原始中断状态
 */
typedef union {
    struct {
        /** ch0_tx_end_int_raw:R/WTC/SS；位位置：[0]；默认值：0；通道0的中断原始位。传输完成时触发。
         */
        uint32_t ch0_tx_end_int_raw: 1;
        /** ch1_tx_end_int_raw:R/WTC/SS；位位置：[1]；默认值：0；通道1的中断原始位。传输完成时触发。
         */
        uint32_t ch1_tx_end_int_raw: 1;
        /** ch2_tx_end_int_raw:R/WTC/SS；位位置：[2]；默认值：0；信道2的中断原始位。传输完成时触发。
         */
        uint32_t ch2_tx_end_int_raw: 1;
        /** ch3_tx_end_int_raw:R/WTC/SS；位位置：[3]；默认值：0；通道3的中断原始位。传输完成时触发。
         */
        uint32_t ch3_tx_end_int_raw: 1;
        /** ch0_err_int_raw:R/WTC/SS；位位置：[4]；默认值：0；CHANNEL0的中断原始位。发生错误时触发。
         */
        uint32_t ch0_err_int_raw: 1;
        /** ch1_err_int_raw:R/WTC/SS；位位置：[5]；默认值：0；通道1的中断原始位。发生错误时触发。
         */
        uint32_t ch1_err_int_raw: 1;
        /** ch2_err_int_raw:R/WTC/SS；位位置：[6]；默认值：0；通道2的中断原始位。发生错误时触发。
         */
        uint32_t ch2_err_int_raw: 1;
        /** ch3_err_int_raw:R/WTC/SS；位位置：[7]；默认值：0；通道3的中断原始位。发生错误时触发。
         */
        uint32_t ch3_err_int_raw: 1;
        /** ch0_tx_thr_event_int_raw:R/WTC/SS；位位置：[8]；默认值：0；CHANNEL0的中断原始位。当变送器发送的数据超过配置值时触发。
         */
        uint32_t ch0_tx_thr_event_int_raw: 1;
        /** ch1_tx_thr_event_int_raw:R/WTC/SS；位位置：[9]；默认值：0；信道1的中断原始位。当发射机发送的数据超过配置值时触发。
         */
        uint32_t ch1_tx_thr_event_int_raw: 1;
        /** ch2_tx_thr_event_int_raw:R/WTC/SS；位位置：[10]；默认值：0；信道2的中断原始位。当发射机发送的数据超过配置值时触发。
         */
        uint32_t ch2_tx_thr_event_int_raw: 1;
        /** ch3_tx_thr_event_int_raw:R/WTC/SS；位位置：[11]；默认值：0；信道3的中断原始位。当发射机发送的数据超过配置值时触发。
         */
        uint32_t ch3_tx_thr_event_int_raw: 1;
        /** ch0_tx_lop_int_raw:R/WTC/SS；位位置：[12]；默认值：0；CHANNEL0的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch0_tx_loop_int_raw: 1;
        /** ch1_tx_loop_int_raw:R/WTC/SS；位位置：[13]；默认值：0；通道1的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch1_tx_loop_int_raw: 1;
        /** ch2_tx_loop_int_raw:R/WTC/SS；位位置：[14]；默认值：0；通道2的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch2_tx_loop_int_raw: 1;
        /** ch3_tx_loop_int_raw:R/WTC/SS；位位置：[15]；默认值：0；通道3的中断原始位。当循环计数达到配置的阈值时触发。
         */
        uint32_t ch3_tx_loop_int_raw: 1;
        /** ch4_rx_end_int_raw:R/WTC/SS；位位置：[16]；默认值：0；信道4的中断原始位。接收完成时触发。
         */
        uint32_t ch4_rx_end_int_raw: 1;
        /** ch5_rx_end_int_raw:R/WTC/SS；位位置：[17]；默认值：0；信道5的中断原始位。接收完成时触发。
         */
        uint32_t ch5_rx_end_int_raw: 1;
        /** ch6_rx_end_int_raw:R/WTC/SS；位位置：[18]；默认值：0；信道6的中断原始位。接收完成时触发。
         */
        uint32_t ch6_rx_end_int_raw: 1;
        /** ch7_rx_end_int_raw:R/WTC/SS；位位置：[19]；默认值：0；通道7的中断原始位。接收完成时触发。
         */
        uint32_t ch7_rx_end_int_raw: 1;
        /** ch4_err_int_raw:R/WTC/SS；位位置：[20]；默认值：0；通道4的中断原始位。发生错误时触发。
         */
        uint32_t ch4_err_int_raw: 1;
        /** ch5_err_int_raw:R/WTC/SS；位位置：[21]；默认值：0；通道5的中断原始位。发生错误时触发。
         */
        uint32_t ch5_err_int_raw: 1;
        /** ch6_err_int_raw:R/WTC/SS；位位置：[22]；默认值：0；通道6的中断原始位。发生错误时触发。
         */
        uint32_t ch6_err_int_raw: 1;
        /** ch7_err_int_raw:R/WTC/SS；位位置：[23]；默认值：0；通道7的中断原始位。发生错误时触发。
         */
        uint32_t ch7_err_int_raw: 1;
        /** ch4_rx_tr_event_int_raw:R/WTC/SS；位位置：[24]；默认值：0；通道4的中断原始位。当接收器接收到的数据超过配置值时触发。
         */
        uint32_t ch4_rx_thr_event_int_raw: 1;
        /** ch5_rx_tr_event_int_raw:R/WTC/SS；位位置：[25]；默认值：0；通道5的中断原始位。当接收器接收到的数据超过配置值时触发。
         */
        uint32_t ch5_rx_thr_event_int_raw: 1;
        /** ch6_rx_tr_event_int_raw:R/WTC/SS；位位置：[26]；默认值：0；通道6的中断原始位。当接收器接收到的数据超过配置值时触发。
         */
        uint32_t ch6_rx_thr_event_int_raw: 1;
        /** ch7_rx_thr_event_int_raw:R/WTC/SS；位位置：[27]；默认值：0；通道7的中断原始位。当接收器接收到的数据超过配置值时触发。
         */
        uint32_t ch7_rx_thr_event_int_raw: 1;
        /** ch3_dma_access_fail_int_raw:R/WTC/SS；位位置：[28]；默认值：0；通道3的中断原始位。当dma访问通道3失败时触发。
         */
        uint32_t ch3_dma_access_fail_int_raw: 1;
        /** ch7_dma_access_fail_int_raw:R/WTC/SS；位位置：[29]；默认值：0；通道7的中断原始位。当dma访问通道7失败时触发。
         */
        uint32_t ch7_dma_access_fail_int_raw: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} rmt_int_raw_reg_t;

/** int_st寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** ch0_tx_end_int_st:RO；位位置：[0]；默认值：0；CH0_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch0_tx_end_int_st: 1;
        /** ch1_tx_end_int_st:RO；位位置：[1]；默认值：0；CH1_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch1_tx_end_int_st: 1;
        /** ch2_tx_end_int_st:RO；位位置：[2]；默认值：0；CH2_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch2_tx_end_int_st: 1;
        /** ch3_tx_end_int_st:RO；位位置：[3]；默认值：0；CH3_TX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch3_tx_end_int_st: 1;
        /** ch0_err_int_st:RO；位位置：[4]；默认值：0；CH0_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch0_err_int_st: 1;
        /** ch1_err_int_st:RO；位位置：[5]；默认值：0；CH1_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch1_err_int_st: 1;
        /** ch2_err_int_st:RO；位位置：[6]；默认值：0；CH2_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch2_err_int_st: 1;
        /** ch3_err_int_st:RO；位位置：[7]；默认值：0；CH3_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch3_err_int_st: 1;
        /** ch0_tx_thr_event_int_st:RO；位位置：[8]；默认值：0；CH0_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch0_tx_thr_event_int_st: 1;
        /** ch1_tx_thr_event_int_st:RO；位位置：[9]；默认值：0；CH1_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch1_tx_thr_event_int_st: 1;
        /** ch2_tx_thr_event_int_st:RO；位位置：[10]；默认值：0；CH2_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch2_tx_thr_event_int_st: 1;
        /** ch3_tx_thr_event_int_st:RO；位位置：[11]；默认值：0；CH3_TX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch3_tx_thr_event_int_st: 1;
        /** ch0_tx_lop_int_st:RO；位位置：[12]；默认值：0；CH0_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch0_tx_loop_int_st: 1;
        /** ch1_tx_loop_int_st:RO；位位置：[13]；默认值：0；CH1_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch1_tx_loop_int_st: 1;
        /** ch2_tx_loop_int_st:RO；位位置：[14]；默认值：0；CH2_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch2_tx_loop_int_st: 1;
        /** ch3_tx_loop_int_st:RO；位位置：[15]；默认值：0；CH3_TX_LOOP_INT的屏蔽中断状态位。
         */
        uint32_t ch3_tx_loop_int_st: 1;
        /** ch4_rx_end_int_st:RO；位位置：[16]；默认值：0；CH4_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch4_rx_end_int_st: 1;
        /** ch5_rx_end_int_st:RO；位位置：[17]；默认值：0；CH5_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch5_rx_end_int_st: 1;
        /** ch6_rx_end_int_st:RO；位位置：[18]；默认值：0；CH6_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch6_rx_end_int_st: 1;
        /** ch7_rx_end_int_st:RO；位位置：[19]；默认值：0；CH7_RX_END_INT的屏蔽中断状态位。
         */
        uint32_t ch7_rx_end_int_st: 1;
        /** ch4_err_int_st:RO；位位置：[20]；默认值：0；CH4_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch4_err_int_st: 1;
        /** ch5_err_int_st:RO；位位置：[21]；默认值：0；CH5_ERR_INT的屏蔽中断状态位。
         */
        uint32_t ch5_err_int_st: 1;
        /** ch6_err_int_st:RO；位位置：[22]；默认值：0；CH6_ERROR_INT的屏蔽中断状态位。
         */
        uint32_t ch6_err_int_st: 1;
        /** ch7_err_int_st:RO；位位置：[23]；默认值：0；CH7_ERROR_INT的屏蔽中断状态位。
         */
        uint32_t ch7_err_int_st: 1;
        /** ch4_rx_tr_event_int_st:RO；位位置：[24]；默认值：0；CH4_RX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch4_rx_thr_event_int_st: 1;
        /** ch5_rx_tr_event_int_st:RO；位位置：[25]；默认值：0；CH5_RX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch5_rx_thr_event_int_st: 1;
        /** ch6_rx_tr_event_int_st:RO；位位置：[26]；默认值：0；CH6_RX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch6_rx_thr_event_int_st: 1;
        /** ch7_rx_thr_event_int_st:RO；位位置：[27]；默认值：0；CH7_RX_THR_EVENT_INT的屏蔽中断状态位。
         */
        uint32_t ch7_rx_thr_event_int_st: 1;
        /** ch3_dma_access_fail_int_st:RO；位位置：[28]；默认值：0；CH3_DMA_ACCESS_FAIL_INT的屏蔽中断状态位。
         */
        uint32_t ch3_dma_access_fail_int_st: 1;
        /** ch7_dma_access_fail_int_st:RO；位位置：[29]；默认值：0；CH7_DMA_ACCESS_FAIL_INT的屏蔽中断状态位。
         */
        uint32_t ch7_dma_access_fail_int_st: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} rmt_int_st_reg_t;

/** int_ena寄存器中断启用位的类型
 */
typedef union {
    struct {
        /** ch0_tx_end_int_ena:R/W；位位置：[0]；默认值：0；CH0_TX_END_INT的中断启用位。
         */
        uint32_t ch0_tx_end_int_ena: 1;
        /** ch1_tx_end_int_ena:R/W；位位置：[1]；默认值：0；CH1_TX_END_INT的中断启用位。
         */
        uint32_t ch1_tx_end_int_ena: 1;
        /** ch2_tx_end_int_ena:R/W；位位置：[2]；默认值：0；CH2_TX_END_INT的中断启用位。
         */
        uint32_t ch2_tx_end_int_ena: 1;
        /** ch3_tx_end_int_ena:R/W；位位置：[3]；默认值：0；CH3_TX_END_INT的中断启用位。
         */
        uint32_t ch3_tx_end_int_ena: 1;
        /** ch0_err_int_ena:R/W；位位置：[4]；默认值：0；CH0_ERR_INT的中断启用位。
         */
        uint32_t ch0_err_int_ena: 1;
        /** ch1_err_int_ena:R/W；位位置：[5]；默认值：0；CH1_ERR_INT的中断启用位。
         */
        uint32_t ch1_err_int_ena: 1;
        /** ch2_err_int_ena:R/W；位位置：[6]；默认值：0；CH2_ERR_INT的中断启用位。
         */
        uint32_t ch2_err_int_ena: 1;
        /** ch3_err_int_ena:R/W；位位置：[7]；默认值：0；CH3_ERR_INT的中断启用位。
         */
        uint32_t ch3_err_int_ena: 1;
        /** ch0_tx_thr_event_int_ena:R/W；位位置：[8]；默认值：0；CH0_TTX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch0_tx_thr_event_int_ena: 1;
        /** ch1_tx_thr_event_int_ena:R/W；位位置：[9]；默认值：0；CH1_TX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch1_tx_thr_event_int_ena: 1;
        /** ch2_tx_thr_event_int_ena:R/W；位位置：[10]；默认值：0；CH2_TX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch2_tx_thr_event_int_ena: 1;
        /** ch3_tx_thr_event_int_ena:R/W；位位置：[11]；默认值：0；CH3_TX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch3_tx_thr_event_int_ena: 1;
        /** ch0_tx_lop_int_ena:R/W；位位置：[12]；默认值：0；CH0_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch0_tx_loop_int_ena: 1;
        /** ch1_tx_loop_int_ena:R/W；位位置：[13]；默认值：0；CH1_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch1_tx_loop_int_ena: 1;
        /** ch2_tx_loop_int_ena:R/W；位位置：[14]；默认值：0；CH2_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch2_tx_loop_int_ena: 1;
        /** ch3_tx_loop_int_ena:R/W；位位置：[15]；默认值：0；CH3_TX_LOOP_INT的中断启用位。
         */
        uint32_t ch3_tx_loop_int_ena: 1;
        /** ch4_rx_end_int_ena:R/W；位位置：[16]；默认值：0；CH4_RX_END_INT的中断启用位。
         */
        uint32_t ch4_rx_end_int_ena: 1;
        /** ch5_rx_end_int_ena:R/W；位位置：[17]；默认值：0；CH5_RX_END_INT的中断启用位。
         */
        uint32_t ch5_rx_end_int_ena: 1;
        /** ch6_rx_end_int_ena:R/W；位位置：[18]；默认值：0；CH6_RX_END_INT的中断启用位。
         */
        uint32_t ch6_rx_end_int_ena: 1;
        /** ch7_rx_end_int_ena:R/W；位位置：[19]；默认值：0；CH7_RX_END_INT的中断启用位。
         */
        uint32_t ch7_rx_end_int_ena: 1;
        /** ch4_err_int_ena:R/W；位位置：[20]；默认值：0；CH4_ERR_INT的中断启用位。
         */
        uint32_t ch4_err_int_ena: 1;
        /** ch5_err_int_ena:R/W；位位置：[21]；默认值：0；CH5_ERR_INT的中断启用位。
         */
        uint32_t ch5_err_int_ena: 1;
        /** ch6_err_int_ena:R/W；位位置：[22]；默认值：0；CH6_ERROR_INT的中断启用位。
         */
        uint32_t ch6_err_int_ena: 1;
        /** ch7_err_int_ena:R/W；位位置：[23]；默认值：0；CH7_ERROR_INT的中断启用位。
         */
        uint32_t ch7_err_int_ena: 1;
        /** ch4_rx_tr_event_int_ena:R/W；位位置：[24]；默认值：0；CH4_RX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch4_rx_thr_event_int_ena: 1;
        /** ch5_rx_tr_event_int_ena:R/W；位位置：[25]；默认值：0；CH5_RX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch5_rx_thr_event_int_ena: 1;
        /** ch6_rx_tr_event_int_ena:R/W；位位置：[26]；默认值：0；CH6_RX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch6_rx_thr_event_int_ena: 1;
        /** ch7_rx_thr_event_int_ena:R/W；位位置：[27]；默认值：0；CH7_RX_THR_EVENT_INT的中断启用位。
         */
        uint32_t ch7_rx_thr_event_int_ena: 1;
        /** ch3_dma_access_fail_int_ena:R/W；位位置：[28]；默认值：0；CH3_DMA_ACCESS_FAIL_INT的中断启用位。
         */
        uint32_t ch3_dma_access_fail_int_ena: 1;
        /** ch7_dma_access_fail_int_ena:R/W；位位置：[29]；默认值：0；CH7_DMA_ACCESS_FAIL_INT的中断启用位。
         */
        uint32_t ch7_dma_access_fail_int_ena: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} rmt_int_ena_reg_t;

/** int_clr寄存器类型中断清除位
 */
typedef union {
    struct {
        /** ch0_tx_end_int_clr:WT；位位置：[0]；默认值：0；设置此位以清除CHO_TX_END_INT中断。
         */
        uint32_t ch0_tx_end_int_clr: 1;
        /** ch1_tx_end_int_clr:WT；位位置：[1]；默认值：0；设置此位以清除CH1_TX_END_INT中断。
         */
        uint32_t ch1_tx_end_int_clr: 1;
        /** ch2_tx_end_int_clr:WT；位位置：[2]；默认值：0；设置此位以清除CH2_TX_END_INT中断。
         */
        uint32_t ch2_tx_end_int_clr: 1;
        /** ch3_tx_end_int_clr:WT；位位置：[3]；默认值：0；设置该位以清除CH3_TX_END_INT中断。
         */
        uint32_t ch3_tx_end_int_clr: 1;
        /** ch0_err_int_clr:WT；位位置：[4]；默认值：0；设置此位以清除CHO_ERROR_INT中断。
         */
        uint32_t ch0_err_int_clr: 1;
        /** ch1_err_int_clr:WT；位位置：[5]；默认值：0；设置该位以清除CH1_ERROR_INT中断。
         */
        uint32_t ch1_err_int_clr: 1;
        /** ch2_err_int_clr:WT；位位置：[6]；默认值：0；设置此位以清除CH2_ERR_INT中断。
         */
        uint32_t ch2_err_int_clr: 1;
        /** ch3_err_int_clr:WT；位位置：[7]；默认值：0；设置该位以清除CH3_ERROR_INT中断。
         */
        uint32_t ch3_err_int_clr: 1;
        /** ch0_tx_thr_event_int_clr:WT；位位置：[8]；默认值：0；设置此位以清除CHO_TX_THR_EVENT_INT中断。
         */
        uint32_t ch0_tx_thr_event_int_clr: 1;
        /** ch1_tx_thr_event_int_clr:WT；位位置：[9]；默认值：0；设置此位以清除CH1_TX_THR_EVENT_INT中断。
         */
        uint32_t ch1_tx_thr_event_int_clr: 1;
        /** ch2_tx_thr_event_int_clr:WT；位位置：[10]；默认值：0；设置此位以清除CH2_TX_THR_EVENT_INT中断。
         */
        uint32_t ch2_tx_thr_event_int_clr: 1;
        /** ch3_tx_thr_event_int_clr:WT；位位置：[11]；默认值：0；设置此位以清除CH3_TX_THR_EVENT_INT中断。
         */
        uint32_t ch3_tx_thr_event_int_clr: 1;
        /** ch0_tx_lop_int_clr:WT；位位置：[12]；默认值：0；设置此位以清除CHO_TX_LOP_INT中断。
         */
        uint32_t ch0_tx_loop_int_clr: 1;
        /** ch1_tx_loop_int_clr:WT；位位置：[13]；默认值：0；设置该位以清除CH1_TX_LOP_INT中断。
         */
        uint32_t ch1_tx_loop_int_clr: 1;
        /** ch2_tx_loop_int_clr:WT；位位置：[14]；默认值：0；设置此位以清除CH2_TX_LOOP_INT中断。
         */
        uint32_t ch2_tx_loop_int_clr: 1;
        /** ch3_tx_loop_int_clr:WT；位位置：[15]；默认值：0；设置该位以清除CH_3_TX_LOOP_INT中断。
         */
        uint32_t ch3_tx_loop_int_clr: 1;
        /** ch4_rx_end_int_clr:WT；位位置：[16]；默认值：0；设置此位以清除H4_RX_END_INT中断。
         */
        uint32_t ch4_rx_end_int_clr: 1;
        /** ch5_rx_end_int_clr:WT；位位置：[17]；默认值：0；设置此位以清除H5_RX_END_INT中断。
         */
        uint32_t ch5_rx_end_int_clr: 1;
        /** ch6_rx_end_int_clr:WT；位位置：[18]；默认值：0；设置此位以清除CH6_RX_END_INT中断。
         */
        uint32_t ch6_rx_end_int_clr: 1;
        /** ch7_rx_end_int_clr:WT；位位置：[19]；默认值：0；设置此位以清除H7_RX_END_INT中断。
         */
        uint32_t ch7_rx_end_int_clr: 1;
        /** ch4_err_int_clr:WT；位位置：[20]；默认值：0；设置此位以清除H4_ERR_INT中断。
         */
        uint32_t ch4_err_int_clr: 1;
        /** ch5_err_int_clr:WT；位位置：[21]；默认值：0；设置此位以清除H5_ERR_INT中断。
         */
        uint32_t ch5_err_int_clr: 1;
        /** ch6_err_int_clr:WT；位位置：[22]；默认值：0；设置此位以清除CH6_ERROR_INT中断。
         */
        uint32_t ch6_err_int_clr: 1;
        /** ch7_err_int_clr:WT；位位置：[23]；默认值：0；设置此位以清除H7_ERR_INT中断。
         */
        uint32_t ch7_err_int_clr: 1;
        /** ch4_rx_tr_event_int_clr:WT；位位置：[24]；默认值：0；设置此位以清除H4_RX_THR_EVENT_INT中断。
         */
        uint32_t ch4_rx_thr_event_int_clr: 1;
        /** ch5_rx_tr_event_int_clr:WT；位位置：[25]；默认值：0；设置此位以清除H5_RX_THR_EVENT_INT中断。
         */
        uint32_t ch5_rx_thr_event_int_clr: 1;
        /** ch6_rx_tr_event_int_clr:WT；位位置：[26]；默认值：0；设置此位以清除CH6_RX_THR_EVENT_INT中断。
         */
        uint32_t ch6_rx_thr_event_int_clr: 1;
        /** ch7_rx_thr_event_int_clr:WT；位位置：[27]；默认值：0；设置此位以清除CH7_RX_THR_EVENT_INT中断。
         */
        uint32_t ch7_rx_thr_event_int_clr: 1;
        /** ch3_dma_access_fail_int_clr:WT；位位置：[28]；默认值：0；设置此位以清除CH3_DMA_ACCESS_FAIL_INT中断。
         */
        uint32_t ch3_dma_access_fail_int_clr: 1;
        /** ch7_dma_access_fail_int_clr:WT；位位置：[29]；默认值：0；设置此位以清除CH7_DMA_ACCESS_FAIL_INT中断。
         */
        uint32_t ch7_dma_access_fail_int_clr: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} rmt_int_clr_reg_t;


/**组：载波占空比寄存器*/
/** chncrier_duty寄存器类型通道n占空比配置寄存器
 */
typedef union {
    struct {
        /** 载波low_chn:R/W；比特位置：[15:0]；默认值：64；该寄存器用于为CHANNELn配置载波的低电平时钟周期。
         */
        uint32_t carrier_low_chn: 16;
        /** 载波_高_chn：R/W；比特位置：[31:16]；默认值：64；该寄存器用于为CHANNELn配置载波的高电平时钟周期。
         */
        uint32_t carrier_high_chn: 16;
    };
    uint32_t val;
} rmt_chncarrier_duty_reg_t;


/**组：Tx事件配置寄存器*/
/** chn_tx-lim寄存器类型通道n tx事件配置寄存器
 */
typedef union {
    struct {
        /** tx_lim_chn:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置CHANNELn可以发送的最大条目。
         */
        uint32_t tx_lim_chn: 9;
        /** tx_loop_num_chn:R/W；比特位置：[18:9]；默认值：0；当tx_conti_mode有效时，此寄存器用于配置最大循环计数。
         */
        uint32_t tx_loop_num_chn: 10;
        /** tx_loop_cnt_en_chn:R/W；位位置：[19]；默认值：0；此寄存器是循环计数的启用位。
         */
        uint32_t tx_loop_cnt_en_chn: 1;
        /** loop_count_reset_chn:WT；位位置：[20]；默认值：0；当tx_conti_mode有效时，此寄存器用于重置循环计数。
         */
        uint32_t loop_count_reset_chn: 1;
        /** loop_top_en_chn:R/W；位位置：[21]；默认值：0；该位用于在循环计数器计数到CHANNELn的循环数后启用循环发送停止功能。
         */
        uint32_t loop_stop_en_chn: 1;
        uint32_t reserved_22: 10;
    };
    uint32_t val;
} rmt_chn_tx_lim_reg_t;

/** tx_sim寄存器类型RMT tx同步寄存器
 */
typedef union {
    struct {
        /** tx_sim_ch0:R/W；位位置：[0]；默认值：0；设置此位以启用CHANNEL0开始与其他启用的信道同步发送数据。
         */
        uint32_t tx_sim_ch0: 1;
        /** tx_sim_ch1:R/W；位位置：[1]；默认值：0；设置此位以启用CHANNEL1开始与其他启用的信道同步发送数据。
         */
        uint32_t tx_sim_ch1: 1;
        /** tx_sim_ch2:R/W；位位置：[2]；默认值：0；设置此位以启用CHANNEL2开始与其他启用的信道同步发送数据。
         */
        uint32_t tx_sim_ch2: 1;
        /** tx_sim_ch3:R/W；位位置：[3]；默认值：0；设置此位以启用CHANNEL3开始与其他启用的信道同步发送数据。
         */
        uint32_t tx_sim_ch3: 1;
        /** tx_sim_en:R/W；位位置：[4]；默认值：0；此寄存器用于使多个通道开始同步发送数据。
         */
        uint32_t tx_sim_en: 1;
        uint32_t reserved_5: 27;
    };
    uint32_t val;
} rmt_tx_sim_reg_t;


/**组：Rx事件配置寄存器*/
/** chm_rx_lim寄存器类型通道m rx事件配置寄存器
 */
typedef union {
    struct {
        /** chm_rx_lim_reg:R/W；位位置：[8:0]；默认值：128；此寄存器用于配置CHANNELm可以接收的最大条目。
         */
        uint32_t chm_rx_lim_reg: 9;
        uint32_t reserved_9: 23;
    };
    uint32_t val;
} rmt_chm_rx_lim_reg_t;


/**组：版本寄存器*/
/** 日期寄存器类型RMT版本寄存器
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[27:0]；默认值：34607489；这是版本寄存器。
         */
        uint32_t date: 28;
        uint32_t reserved_28: 4;
    };
    uint32_t val;
} rmt_date_reg_t;


typedef struct {
    volatile rmt_chndata_reg_t chndata[4];
    volatile rmt_chmdata_reg_t chmdata[4];
    volatile rmt_chnconf0_reg_t chnconf0[4];
    volatile rmt_chmconf_reg_t chmconf[4];
    volatile rmt_chnstatus_reg_t chnstatus[4];
    volatile rmt_chmstatus_reg_t chmstatus[4];
    volatile rmt_int_raw_reg_t int_raw;
    volatile rmt_int_st_reg_t int_st;
    volatile rmt_int_ena_reg_t int_ena;
    volatile rmt_int_clr_reg_t int_clr;
    volatile rmt_chncarrier_duty_reg_t chncarrier_duty[4];
    volatile rmt_chm_rx_carrier_rm_reg_t chm_rx_carrier_rm[4];
    volatile rmt_chn_tx_lim_reg_t chn_tx_lim[4];
    volatile rmt_chm_rx_lim_reg_t chm_rx_lim[4];
    volatile rmt_sys_conf_reg_t sys_conf;
    volatile rmt_tx_sim_reg_t tx_sim;
    volatile rmt_ref_cnt_rst_reg_t ref_cnt_rst;
    volatile rmt_date_reg_t date;
} rmt_dev_t;

#ifndef __cplusplus
_Static_assert(sizeof(rmt_dev_t) == 0xd0, "Invalid size of rmt_dev_t structure");
#endif

typedef struct {
    union {
        struct {
            uint32_t duration0 : 15;
            uint32_t level0 : 1;
            uint32_t duration1 : 15;
            uint32_t level1 : 1;
        };
        uint32_t val;
    };
} rmt_item32_t;

typedef struct {
    struct {
        volatile rmt_item32_t data32[48];
    } chan[8];
} rmt_mem_t;

#ifndef __cplusplus
_Static_assert(sizeof(rmt_item32_t) == 0x04, "Invalid size of rmt_item32_t structure");
_Static_assert(sizeof(rmt_mem_t) == 0x04 * 8 * 48, "Invalid size of rmt_mem_t structure");
#endif

extern rmt_dev_t RMT;
extern rmt_mem_t RMTMEM;

#ifdef __cplusplus
}
#endif

