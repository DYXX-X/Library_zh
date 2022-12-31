// 版权所有2017-2021 Espressif Systems（Shanghai）PTE LTD
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
#ifndef _SOC_GDMA_STRUCT_H_
#define _SOC_GDMA_STRUCT_H_


#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct gdma_dev_s {
    struct {
        struct {
            union {
                struct {
                    uint32_t in_rst                        :    1;  /*该位用于重置DMA通道0 Rx FSM和Rx FIFO指针。*/
                    uint32_t in_loop_test                  :    1;  /*保留*/
                    uint32_t indscr_burst_en               :    1;  /*当访问内部SRAM时，将此位设置为1以启用Rx通道0读取链路描述符的INCR突发传输。*/
                    uint32_t in_data_burst_en              :    1;  /*将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道0的INCR突发传输。*/
                    uint32_t mem_trans_en                  :    1;  /*将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。*/
                    uint32_t reserved5                     :    1;  /*保留*/
                    uint32_t reserved6                     :    26;  /*保留*/
                };
                uint32_t val;
            } conf0;
            union {
                struct {
                    uint32_t dma_infifo_full_thrs          :    12;  /*当Rx FIFO中接收到的Rx通道0字节数达到寄存器值时，该寄存器用于生成INFIFO_FULL_WM_INT中断。*/
                    uint32_t in_check_owner                :    1;  /*设置此位以启用检查链接描述符的所有者属性。*/
                    uint32_t in_ext_mem_bk_size            :    2;  /*DMA访问外部SRAM时Rx通道0的块大小。0:16字节1:32字节2/3:保留*/
                    uint32_t reserved15                    :    17;  /*保留*/
                };
                uint32_t val;
            } conf1;
            union {
                struct {
                    uint32_t in_done                       :    1;  /*当接收到Rx通道0的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。*/
                    uint32_t in_suc_eof                    :    1;  /*当接收到Rx通道0的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且未检测到Rx信道0的数据错误时，原始断开位变为低电平。*/
                    uint32_t in_err_eof                    :    1;  /*仅当外围设备为Rx通道0的UHCI0时，检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。*/
                    uint32_t in_dscr_err                   :    1;  /*当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误、Rx通道0的内联描述符的第二个和第三个字错误。*/
                    uint32_t in_dscr_empty                 :    1;  /*当内联指向的Rx缓冲区已满且接收数据未完成时，原始中断位变为高电平，但Rx通道0不再有内联。*/
                    uint32_t infifo_full_wm                :    1;  /*当接收到的数据字节数达到信道0的Rx FIFO中REG_DMA_INFIFO_FULL_THS_CH0配置的阈值时，原始中断位变为高电平。*/
                    uint32_t infifo_ovf_l1                 :    1;  /*当Rx通道0的1级fifo溢出时，此原始中断位变为高电平。*/
                    uint32_t infifo_udf_l1                 :    1;  /*当Rx通道0的1级fifo下溢时，该原始中断位变为高电平。*/
                    uint32_t infifo_ovf_l3                 :    1;  /*当Rx通道0的3级fifo溢出时，此原始中断位变为高电平。*/
                    uint32_t infifo_udf_l3                 :    1;  /*当Rx通道0的3级fifo下溢时，该原始中断位变为高电平。*/
                    uint32_t reserved10                    :    22;  /*保留*/
                };
                uint32_t val;
            } int_raw;
            union {
                struct {
                    uint32_t in_done                       :    1;  /*IN_DONE_CH_INT中断的原始中断状态位。*/
                    uint32_t in_suc_eof                    :    1;  /*IN_SUC_EOF_CH_INT中断的原始中断状态位。*/
                    uint32_t in_err_eof                    :    1;  /*IN_ERR_EOF_CH_INT中断的原始中断状态位。*/
                    uint32_t in_dscr_err                   :    1;  /*IN_DSCR_ERR_CH_INT中断的原始中断状态位。*/
                    uint32_t in_dscr_empty                 :    1;  /*IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。*/
                    uint32_t infifo_full_wm                :    1;  /*INFIFO_FULL_WM_CH_INT中断的原始中断状态位。*/
                    uint32_t infifo_ovf_l1                 :    1;  /*INFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
                    uint32_t infifo_udf_l1                 :    1;  /*INFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
                    uint32_t infifo_ovf_l3                 :    1;  /*INFIFO_OVF_L3_CH_INT中断的原始中断状态位。*/
                    uint32_t infifo_udf_l3                 :    1;  /*INFIFO_UDF_L3_CH_INT中断的原始中断状态位。*/
                    uint32_t reserved10                    :    22;  /*保留*/
                };
                uint32_t val;
            } int_st;
            union {
                struct {
                    uint32_t in_done                       :    1;  /*IN_DONE_CH_INT中断的中断启用位。*/
                    uint32_t in_suc_eof                    :    1;  /*IN_SUC_EOF_CH_INT中断的中断启用位。*/
                    uint32_t in_err_eof                    :    1;  /*IN_ERR_EOF_CH_INT中断的中断启用位。*/
                    uint32_t in_dscr_err                   :    1;  /*IN_DSCR_ERR_CH_INT中断的中断启用位。*/
                    uint32_t in_dscr_empty                 :    1;  /*IN_DSCR_EMPTY_CH_INT中断的中断启用位。*/
                    uint32_t infifo_full_wm                :    1;  /*INFIFO_FULL_WM_CH_INT中断的中断启用位。*/
                    uint32_t infifo_ovf_l1                 :    1;  /*INFIFO_OVF_L1_CH_INT中断的中断启用位。*/
                    uint32_t infifo_udf_l1                 :    1;  /*INFIFO_UDF_L1_CH_INT中断的中断启用位。*/
                    uint32_t infifo_ovf_l3                 :    1;  /*INFIFO_OVF_L3_CH_INT中断的中断启用位。*/
                    uint32_t infifo_udf_l3                 :    1;  /*INFIFO_UDF_L3_CH_INT中断的中断启用位。*/
                    uint32_t reserved10                    :    22;  /*保留*/
                };
                uint32_t val;
            } int_ena;
            union {
                struct {
                    uint32_t in_done                       :    1;  /*设置此位以清除IN_DONE_CH_INT中断。*/
                    uint32_t in_suc_eof                    :    1;  /*设置此位以清除IN_SUC_EOF_CH_INT中断。*/
                    uint32_t in_err_eof                    :    1;  /*设置此位以清除IN_ERR_EOF_CH_INT中断。*/
                    uint32_t in_dscr_err                   :    1;  /*设置该位以清除IN_DSCR_ERR_CH_INT中断。*/
                    uint32_t in_dscr_empty                 :    1;  /*设置此位以清除IN_DSCR_EMPTY_CH_INT中断。*/
                    uint32_t dma_infifo_full_wm            :    1;  /*设置此位以清除INFIFO_FULL_WM_CH_INT中断。*/
                    uint32_t infifo_ovf_l1                 :    1;  /*设置此位以清除INFIFO_OVF_L1_CH_INT中断。*/
                    uint32_t infifo_udf_l1                 :    1;  /*设置此位以清除INFIFO_UDF_L1_CH_INT中断。*/
                    uint32_t infifo_ovf_l3                 :    1;  /*设置此位以清除INFIFO_OVF_L3_CH_INT中断。*/
                    uint32_t infifo_udf_l3                 :    1;  /*设置此位以清除INFIFO_UDF_L3_CH_INT中断。*/
                    uint32_t reserved10                    :    22;  /*保留*/
                };
                uint32_t val;
            } int_clr;
            union {
                struct {
                    uint32_t infifo_full_l1                :    1;  /*Rx信道0的L1 Rx FIFO满信号。*/
                    uint32_t infifo_empty_l1               :    1;  /*Rx信道0的L1 Rx FIFO空信号。*/
                    uint32_t infifo_full_l2                :    1;  /*Rx信道0的L2 Rx FIFO满信号。*/
                    uint32_t infifo_empty_l2               :    1;  /*Rx信道0的L2 Rx FIFO空信号。*/
                    uint32_t infifo_full_l3                :    1;  /*Rx信道0的L3 Rx FIFO满信号。*/
                    uint32_t infifo_empty_l3               :    1;  /*Rx信道0的L3 Rx FIFO空信号。*/
                    uint32_t infifo_cnt_l1                 :    6;  /*寄存器将数据的字节数存储在Rx通道0的L1 Rx FIFO中。*/
                    uint32_t infifo_cnt_l2                 :    7;  /*寄存器将数据的字节数存储在Rx通道0的L2 Rx FIFO中。*/
                    uint32_t infifo_cnt_l3                 :    5;  /*寄存器将数据的字节数存储在Rx通道0的L3 Rx FIFO中。*/
                    uint32_t in_remain_under_1b_l3         :    1;  /*保留*/
                    uint32_t in_remain_under_2b_l3         :    1;  /*保留*/
                    uint32_t in_remain_under_3b_l3         :    1;  /*保留*/
                    uint32_t in_remain_under_4b_l3         :    1;  /*保留*/
                    uint32_t in_buf_hungry                 :    1;  /*保留*/
                    uint32_t reserved29                    :    3;  /*保留*/
                };
                uint32_t val;
            } infifo_status;
            union {
                struct {
                    uint32_t infifo_rdata                  :    12;  /*该寄存器存储从DMA FIFO弹出的数据。*/
                    uint32_t infifo_pop                    :    1;  /*设置此位以从DMA FIFO弹出数据。*/
                    uint32_t reserved13                    :    19;  /*保留*/
                };
                uint32_t val;
            } pop;
            union {
                struct {
                    uint32_t addr                          :    20;  /*该寄存器存储第一个内联描述符地址的20个最低有效位。*/
                    uint32_t auto_ret                      :    1;  /*当当前接收数据中存在一些错误时，设置此位以返回当前内联描述符的地址。*/
                    uint32_t stop                          :    1;  /*设置此位以停止处理内联描述符。*/
                    uint32_t start                         :    1;  /*设置此位以开始处理内联描述符。*/
                    uint32_t restart                       :    1;  /*设置此位以装入新的内联描述符。*/
                    uint32_t park                          :    1;  /*1： 内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。*/
                    uint32_t reserved25                    :    7;
                };
                uint32_t val;
            } link;
            union {
                struct {
                    uint32_t dscr_addr                     :    18;  /*此寄存器存储当前内联描述符的地址。*/
                    uint32_t in_dscr_state                 :    2;  /*保留*/
                    uint32_t in_state                      :    3;  /*保留*/
                    uint32_t reserved23                    :    9;  /*保留*/
                };
                uint32_t val;
            } state;
            uint32_t suc_eof_des_addr;
            uint32_t err_eof_des_addr;
            uint32_t dscr;
            uint32_t dscr_bf0;
            uint32_t dscr_bf1;
            union {
                struct {
                    uint32_t reserved0                     :    8;
                    uint32_t rx_weight                     :    4;  /*Rx通道0的权重。*/
                    uint32_t reserved12                    :    20;
                };
                uint32_t val;
            } wight;
            uint32_t reserved_40;
            union {
                struct {
                    uint32_t rx_pri                        :    4;  /*Rx通道0的优先级。值越大，优先级越高。*/
                    uint32_t reserved4                     :    28;
                };
                uint32_t val;
            } pri;
            union {
                struct {
                    uint32_t sel                           :    6;  /*此寄存器用于选择Rx通道的外围设备0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。*/
                    uint32_t reserved6                     :    26;
                };
                uint32_t val;
            } peri_sel;
            uint32_t reserved_4c;
            uint32_t reserved_50;
            uint32_t reserved_54;
            uint32_t reserved_58;
            uint32_t reserved_5c;
        } in;
        struct {
            union {
                struct {
                    uint32_t out_rst                       :    1;  /*该位用于重置DMA通道0 Tx FSM和Tx FIFO指针。*/
                    uint32_t out_loop_test                 :    1;  /*保留*/
                    uint32_t out_auto_wrback               :    1;  /*设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。*/
                    uint32_t out_eof_mode                  :    1;  /*传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道0的EOF标志*/
                    uint32_t outdscr_burst_en              :    1;  /*当访问内部SRAM时，将此位设置为1以启用Tx信道0读取链路描述符的INCR突发传输。*/
                    uint32_t out_data_burst_en             :    1;  /*当访问内部SRAM时，将此位设置为1，以启用传输数据的Tx信道0的INCR突发传输。*/
                    uint32_t reserved6                     :    1;
                    uint32_t reserved7                     :    25;
                };
                uint32_t val;
            } conf0;
            union {
                struct {
                    uint32_t reserved0                     :    12;
                    uint32_t out_check_owner               :    1;  /*设置此位以启用检查链接描述符的所有者属性。*/
                    uint32_t out_ext_mem_bk_size           :    2;  /*DMA访问外部SRAM时Tx通道0的块大小。0:16字节1:32字节2/3:保留*/
                    uint32_t reserved15                    :    17;  /*保留*/
                };
                uint32_t val;
            } conf1;
            union {
                struct {
                    uint32_t out_done                      :    1;  /*当一个输出链接描述符所指向的最后一个数据已传输到Tx信道0的外围设备时，原始中断位变为高电平。*/
                    uint32_t out_eof                       :    1;  /*当从Tx信道0的存储器中读取一个输出描述符所指向的最后数据时，原始中断位变为高电平。*/
                    uint32_t out_dscr_err                  :    1;  /*当检测到outlink描述符错误时，原始中断位变为高电平，包括所有者错误、Tx信道0的outlink描述符的第二个和第三个字错误。*/
                    uint32_t out_total_eof                 :    1;  /*当针对Tx信道0发送出对应于输出链接（包括一个链路描述符或几个链路描述符）的数据时，原始中断位变为高电平。*/
                    uint32_t outfifo_ovf_l1                :    1;  /*当Tx信道0的1级fifo溢出时，该原始中断位变为高电平。*/
                    uint32_t outfifo_udf_l1                :    1;  /*当Tx信道0的1级fifo下溢时，该原始中断位变为高电平。*/
                    uint32_t outfifo_ovf_l3                :    1;  /*当Tx信道0的3级fifo溢出时，该原始中断位变为高电平。*/
                    uint32_t outfifo_udf_l3                :    1;  /*当Tx信道0的3级fifo下溢时，该原始中断位变为高电平。*/
                    uint32_t reserved8                     :    24;  /*保留*/
                };
                uint32_t val;
            } int_raw;
            union {
                struct {
                    uint32_t out_done                      :    1;  /*OUT_DONE_CH_INT中断的原始中断状态位。*/
                    uint32_t out_eof                       :    1;  /*OUT_EOF_CH_INT中断的原始中断状态位。*/
                    uint32_t out_dscr_err                  :    1;  /*OUT_DSCR_ERR_CH_INT中断的原始中断状态位。*/
                    uint32_t out_total_eof                 :    1;  /*OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。*/
                    uint32_t outfifo_ovf_l1                :    1;  /*OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
                    uint32_t outfifo_udf_l1                :    1;  /*OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
                    uint32_t outfifo_ovf_l3                :    1;  /*OUTFIFO_OVF_L3_CH_INT中断的原始中断状态位。*/
                    uint32_t outfifo_udf_l3                :    1;  /*OUTFIFO_UDF_L3_CH_INT中断的原始中断状态位。*/
                    uint32_t reserved8                     :    24;  /*保留*/
                };
                uint32_t val;
            } int_st;
            union {
                struct {
                    uint32_t out_done                      :    1;  /*OUT_DONE_CH_INT中断的中断启用位。*/
                    uint32_t out_eof                       :    1;  /*OUT_EOF_CH_INT中断的中断启用位。*/
                    uint32_t out_dscr_err                  :    1;  /*OUT_DSCR_ERR_CH_INT中断的中断启用位。*/
                    uint32_t out_total_eof                 :    1;  /*OUT_TOTAL_EOF_CH_INT中断的中断启用位。*/
                    uint32_t outfifo_ovf_l1                :    1;  /*OUTFIFO_OVF_L1_CH_INT中断的中断启用位。*/
                    uint32_t outfifo_udf_l1                :    1;  /*OUTFIFO_UDF_L1_CH_INT中断的中断启用位。*/
                    uint32_t outfifo_ovf_l3                :    1;  /*OUTFIFO_OVF_L3_CH_INT中断的中断启用位。*/
                    uint32_t outfifo_udf_l3                :    1;  /*OUTFIFO_UDF_L3_CH_INT中断的中断启用位。*/
                    uint32_t reserved8                     :    24;  /*保留*/
                };
                uint32_t val;
            } int_ena;
            union {
                struct {
                    uint32_t out_done                      :    1;  /*设置该位以清除OUT_DONE_CH_INT中断。*/
                    uint32_t out_eof                       :    1;  /*设置此位以清除OUT_EOF_CH_INT中断。*/
                    uint32_t out_dscr_err                  :    1;  /*设置该位以清除OUT_DSCR_ERR_CH_INT中断。*/
                    uint32_t out_total_eof                 :    1;  /*设置此位以清除OUT_TOTAL_EOF_CH_INT中断。*/
                    uint32_t outfifo_ovf_l1                :    1;  /*设置该位以清除OUTFIFO_OVF_L1_CH_INT中断。*/
                    uint32_t outfifo_udf_l1                :    1;  /*设置该位以清除OUTFIFO_UDF_L1_CH_INT中断。*/
                    uint32_t outfifo_ovf_l3                :    1;  /*设置此位以清除OUTFIFO_OVF_L3_CH_INT中断。*/
                    uint32_t outfifo_udf_l3                :    1;  /*设置此位以清除OUTFIFO_UDF_L3_CH_INT中断。*/
                    uint32_t reserved8                     :    24;  /*保留*/
                };
                uint32_t val;
            } int_clr;
            union {
                struct {
                    uint32_t outfifo_full_l1               :    1;  /*Tx信道0的L1 Tx FIFO满信号。*/
                    uint32_t outfifo_empty_l1              :    1;  /*Tx信道0的L1 Tx FIFO空信号。*/
                    uint32_t outfifo_full_l2               :    1;  /*Tx信道0的L2 Tx FIFO满信号。*/
                    uint32_t outfifo_empty_l2              :    1;  /*Tx信道0的L2 Tx FIFO空信号。*/
                    uint32_t outfifo_full_l3               :    1;  /*Tx信道0的L3 Tx FIFO满信号。*/
                    uint32_t outfifo_empty_l3              :    1;  /*Tx信道0的L3 Tx FIFO空信号。*/
                    uint32_t outfifo_cnt_l1                :    5;  /*寄存器将数据的字节数存储在Tx信道0的L1 Tx FIFO中。*/
                    uint32_t outfifo_cnt_l2                :    7;  /*寄存器将Tx信道0的数据字节数存储在L2 Tx FIFO中。*/
                    uint32_t outfifo_cnt_l3                :    5;  /*寄存器将Tx信道0的数据字节数存储在L3 Tx FIFO中。*/
                    uint32_t out_remain_under_1b_l3        :    1;  /*保留*/
                    uint32_t out_remain_under_2b_l3        :    1;  /*保留*/
                    uint32_t out_remain_under_3b_l3        :    1;  /*保留*/
                    uint32_t out_remain_under_4b_l3        :    1;  /*保留*/
                    uint32_t reserved27                    :    5;  /*保留*/
                };
                uint32_t val;
            } outfifo_status;
            union {
                struct {
                    uint32_t outfifo_wdata                 :    9;  /*该寄存器存储需要推入DMA FIFO的数据。*/
                    uint32_t outfifo_push                  :    1;  /*设置此位以将数据推入DMA FIFO。*/
                    uint32_t reserved10                    :    22;  /*保留*/
                };
                uint32_t val;
            } push;
            union {
                struct {
                    uint32_t addr                          :    20;  /*该寄存器存储第一个输出链接描述符地址的20个最低有效位。*/
                    uint32_t stop                          :    1;  /*设置此位以停止处理outlink描述符。*/
                    uint32_t start                         :    1;  /*设置此位以开始处理outlink描述符。*/
                    uint32_t restart                       :    1;  /*设置此位以从最后一个地址重新启动新的outlink。*/
                    uint32_t park                          :    1;  /*1： outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。*/
                    uint32_t reserved24                    :    8;
                };
                uint32_t val;
            } link;
            union {
                struct {
                    uint32_t dscr_addr                     :    18;  /*此寄存器存储当前outlink描述符的地址。*/
                    uint32_t out_dscr_state                :    2;  /*保留*/
                    uint32_t out_state                     :    3;  /*保留*/
                    uint32_t reserved23                    :    9;  /*保留*/
                };
                uint32_t val;
            } state;
            uint32_t eof_des_addr;
            uint32_t eof_bfr_des_addr;
            uint32_t dscr;
            uint32_t dscr_bf0;
            uint32_t dscr_bf1;
            union {
                struct {
                    uint32_t reserved0                     :    8;
                    uint32_t tx_weight                     :    4;  /*Tx通道0的权重。*/
                    uint32_t reserved12                    :    20;
                };
                uint32_t val;
            } wight;
            uint32_t reserved_a0;
            union {
                struct {
                    uint32_t tx_pri                        :    4;  /*Tx信道0的优先级。值越大，优先级越高。*/
                    uint32_t reserved4                     :    28;
                };
                uint32_t val;
            } pri;
            union {
                struct {
                    uint32_t sel                           :    6;  /*此寄存器用于为Tx信道0.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。；7： AES。8： 沙。9： ADC_DAC。*/
                    uint32_t reserved6                     :    26;
                };
                uint32_t val;
            } peri_sel;
            uint32_t reserved_ac;
            uint32_t reserved_b0;
            uint32_t reserved_b4;
            uint32_t reserved_b8;
            uint32_t reserved_bc;
        } out;
    } channel[5];
    union {
        struct {
            uint32_t ahb_testmode                  :    3;  /*保留*/
            uint32_t reserved3                     :    1;  /*保留*/
            uint32_t ahb_testaddr                  :    2;  /*保留*/
            uint32_t reserved6                     :    26;  /*保留*/
        };
        uint32_t val;
    } ahb_test;
    union {
        struct {
            uint32_t reserved0                     :    4;  /*保留*/
            uint32_t dma_ram_force_pd              :    1;  /*断电，断电*/
            uint32_t dma_ram_force_pu              :    1;
            uint32_t dma_ram_clk_fo                :    1;  /*1： 在DMA中访问RAM时，强制打开时钟并绕过门时钟。0：在DMA中访问RAM时将使用门时钟。*/
            uint32_t reserved7                     :    25;
        };
        uint32_t val;
    } pd_conf;
    union {
        struct {
            uint32_t ahbm_rst_inter                :    1;  /*设置此位，然后清除此位以重置内部ahb FSM。*/
            uint32_t ahbm_rst_exter                :    1;  /*设置此位，然后清除此位以重置外部ahb FSM。*/
            uint32_t arb_pri_dis                   :    1;  /*设置此位以禁用优先级仲裁功能。*/
            uint32_t reserved3                     :    1;
            uint32_t clk_en                        :    1;
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } misc_conf;
    struct {
        union {
            struct {
                uint32_t in_size                       :    7;  /*此寄存器用于配置Rx信道0.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。*/
                uint32_t reserved7                     :    25;
            };
            uint32_t val;
        } in;
        union {
            struct {
                uint32_t out_size                      :    7;  /*此寄存器用于配置Tx信道0.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。*/
                uint32_t reserved7                     :    25;
            };
            uint32_t val;
        } out;
    } sram_size[5];
    uint32_t extmem_reject_addr;
    union {
        struct {
            uint32_t extmem_reject_attr            :    2;  /*拒绝访问。位0：如果该位为1，则拒绝访问为READ。位1：如果该位为1，则拒绝访问为WRITE。*/
            uint32_t extmem_reject_channel_num     :    4;  /*寄存器指示拒绝从哪个通道访问。*/
            uint32_t extmem_reject_peri_num        :    6;  /*该寄存器指示拒绝从哪个外围设备访问。*/
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } extmem_reject_st;
    union {
        struct {
            uint32_t extmem_reject                 :    1;  /*当访问外部RAM被许可控制拒绝时，原始中断位变为高电平。*/
            uint32_t reserved1                     :    31;  /*保留*/
        };
        uint32_t val;
    } extmem_reject_int_raw;
    union {
        struct {
            uint32_t extmem_reject                 :    1;  /*EXTMEM_REJECT_INT中断的原始中断状态位。*/
            uint32_t reserved1                     :    31;  /*保留*/
        };
        uint32_t val;
    } extmem_reject_int_st;
    union {
        struct {
            uint32_t extmem_reject                 :    1;  /*EXTMEM_REJECT_INT中断的中断启用位。*/
            uint32_t reserved1                     :    31;  /*保留*/
        };
        uint32_t val;
    } extmem_reject_int_ena;
    union {
        struct {
            uint32_t extmem_reject                 :    1;  /*设置该位以清除EXTMEM_REJECT_INT中断。*/
            uint32_t reserved1                     :    31;  /*保留*/
        };
        uint32_t val;
    } extmem_reject_int_clr;
    uint32_t date;
} gdma_dev_t;
extern gdma_dev_t GDMA;
#ifdef __cplusplus
}
#endif



#endif /*_SOC_GDMA_STRUCT_H_ */

