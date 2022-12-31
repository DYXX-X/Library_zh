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
#ifndef _SOC_SPI_STRUCT_H_
#define _SOC_SPI_STRUCT_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct spi_dev_s {
    union {
        struct {
            uint32_t conf_bitlen                   :    18;  /*定义SPI_CONF状态的APB周期。可在形态状态下配置。*/
            uint32_t reserved18                    :    5;  /*保留*/
            uint32_t update                        :    1;  /*设置此位以将SPI寄存器从APB时钟域同步到SPI模块时钟域，这仅用于SPI主模式。*/
            uint32_t usr                           :    1;  /*用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。无法通过CONF_buf更改。*/
            uint32_t reserved25                    :    7;  /*保留*/
        };
        uint32_t val;
    } cmd;
    uint32_t addr;
    union {
        struct {
            uint32_t reserved0                     :    3;  /*保留*/
            uint32_t dummy_out                     :    1;  /*在虚设阶段，spi的信号电平由spi控制器输出。可在形态状态下配置。*/
            uint32_t reserved4                     :    1;  /*保留*/
            uint32_t faddr_dual                    :    1;  /*在地址阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。*/
            uint32_t faddr_quad                    :    1;  /*在地址阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。*/
            uint32_t reserved7                     :    1;  /*保留*/
            uint32_t fcmd_dual                     :    1;  /*在命令阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。*/
            uint32_t fcmd_quad                     :    1;  /*在命令阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。*/
            uint32_t reserved10                    :    4;  /*保留*/
            uint32_t fread_dual                    :    1;  /*在读取操作中，读取数据相位施加2个信号。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t fread_quad                    :    1;  /*在读取操作中，读取数据阶段施加4个信号。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t reserved16                    :    1;  /*保留*/
            uint32_t reserved17                    :    1;  /*保留*/
            uint32_t q_pol                         :    1;  /*该位用于设置MISO线极性，1：高0，低。可在形态状态下配置。*/
            uint32_t d_pol                         :    1;  /*该位用于设置MOSI线极性，1：高0，低。可在形态状态下配置。*/
            uint32_t hold_pol                      :    1;  /*SPI空闲时的SPI_HOLD输出值。1： 输出高，0：输出低。可在形态状态下配置。*/
            uint32_t wp_pol                        :    1;  /*SPI空闲时的写保护信号输出。1： 输出高，0：输出低。可在形态状态下配置。*/
            uint32_t reserved22                    :    3;  /*保留*/
            uint32_t rd_bit_order                  :    1;  /*在读取数据（MISO）阶段1:LSB优先0:MSB优先。可在形态状态下配置。*/
            uint32_t wr_bit_order                  :    1;  /*在命令地址写入数据（MOSI）阶段1:LSB首先为0:MSB。可在形态状态下配置。*/
            uint32_t reserved27                    :    5;  /*保留*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t clkcnt_l                      :    6;  /*在主模式下，它必须等于spi_clkcnt_N。在从属模式下，它必须为0。可以在CONF状态下配置。*/
            uint32_t clkcnt_h                      :    6;  /*在主模式下，它必须是floor（（spi_clkcnt_N+1）/2-1）。在从属模式下，它必须为0。可以在CONF状态下配置。*/
            uint32_t clkcnt_n                      :    6;  /*在主模式中，它是spi_clk的除法器。因此spi_clk频率为系统/（spi_clkdiv_pre+1）/（spi_clkcnt_N+1）。可在形态状态下配置。*/
            uint32_t clkdiv_pre                    :    4;  /*在主模式中，它是spi_clk的预除法器。可在形态状态下配置。*/
            uint32_t reserved22                    :    9;  /*保留*/
            uint32_t clk_equ_sysclk                :    1;  /*在主模式1中：spi_clk与系统0相等：spi_clk与系统时钟分开。可在形态状态下配置。*/
        };
        uint32_t val;
    } clock;
    union {
        struct {
            uint32_t doutdin                       :    1;  /*设置该位以启用全双工通信。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t reserved1                     :    2;  /*保留*/
            uint32_t qpi_mode                      :    1;  /*主模式和从模式。1： spi控制器处于QPI模式。0：其他。可在形态状态下配置。*/
            uint32_t reserved4                     :    1;  /*保留*/
            uint32_t tsck_i_edge                   :    1;  /*在从属模式下，该位可用于改变tsck的极性。0:tsck=spi_ck_i。1： tsck=！spi_ck_。*/
            uint32_t cs_hold                       :    1;  /*当spi处于完成阶段时，spi cs保持较低。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t cs_setup                      :    1;  /*当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t rsck_i_edge                   :    1;  /*在从属模式下，这个位可以用来改变rsck的极性。0:rsck=！spi_ck_。1： rsck=spi_ck_i。*/
            uint32_t ck_out_edge                   :    1;  /*该位与spi_mosidelaymode位组合以设置mosi信号延迟模式。可在形态状态下配置。*/
            uint32_t reserved10                    :    2;  /*保留*/
            uint32_t fwrite_dual                   :    1;  /*在写入操作中，读取数据阶段施加2个信号。可在形态状态下配置。*/
            uint32_t fwrite_quad                   :    1;  /*在写入操作中，读取数据阶段施加4个信号。可在形态状态下配置。*/
            uint32_t reserved14                    :    1;  /*保留*/
            uint32_t usr_conf_nxt                  :    1;  /*1： 启用下一个seg传输操作的DMA CONF阶段，这意味着seg传输将继续。0：分段传输将在当前SPI分段传输之后结束，或者这不是分段传输模式。可在形态状态下配置。*/
            uint32_t reserved16                    :    1;  /*保留*/
            uint32_t sio                           :    1;  /*设置该位以启用3线半双工通信mosi和miso信号共享同一引脚。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t reserved18                    :    6;  /*保留*/
            uint32_t usr_miso_highpart             :    1;  /*读取数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。*/
            uint32_t usr_mosi_highpart             :    1;  /*写入数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。*/
            uint32_t usr_dummy_idle                :    1;  /*当位被启用时，spi时钟在伪相位被禁用。可在形态状态下配置。*/
            uint32_t usr_mosi                      :    1;  /*此位启用操作的写入数据阶段。可在形态状态下配置。*/
            uint32_t usr_miso                      :    1;  /*此位启用操作的读取数据阶段。可在形态状态下配置。*/
            uint32_t usr_dummy                     :    1;  /*此位启用操作的虚拟阶段。可在形态状态下配置。*/
            uint32_t usr_addr                      :    1;  /*此位启用操作的地址阶段。可在形态状态下配置。*/
            uint32_t usr_command                   :    1;  /*此位启用操作的命令阶段。可在形态状态下配置。*/
        };
        uint32_t val;
    } user;
    union {
        struct {
            uint32_t usr_dummy_cyclelen            :    8;  /*虚拟相位的spi_clk周期长度。寄存器值应为（cycle_num-1）。可在形态状态下配置。*/
            uint32_t reserved8                     :    8;  /*保留*/
            uint32_t mst_wfull_err_end_en          :    1;  /*1： 当SPI RX AFIFO wfull错误在GP-SPI主FD/HD模式下有效时，SPI传输结束。0:当SPI RX AFIFO wfull错误在GP-SPI主FD/HD模式下有效时，SPI传输未结束。*/
            uint32_t cs_setup_time                 :    5;  /*spi时钟准备阶段的（周期+1），该位与spi_cs_setup位组合。可在形态状态下配置。*/
            uint32_t cs_hold_time                  :    5;  /*通过spi时钟的cs引脚的延迟周期该位与spicshold位组合。可在形态状态下配置。*/
            uint32_t usr_addr_bitlen               :    5;  /*地址相位的位长度。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
        };
        uint32_t val;
    } user1;
    union {
        struct {
            uint32_t usr_command_value             :    16;  /*命令的值。可在形态状态下配置。*/
            uint32_t reserved16                    :    11;  /*保留*/
            uint32_t mst_rempty_err_end_en         :    1;  /*1： 当SPI TX AFIFO读取空错误在GP-SPI主FD/HD模式下有效时，SPI传输结束。0：当SPI TX AFIFO读取空错误在GP-SPI主FD/HD模式下有效时，SPI传输未结束。*/
            uint32_t usr_command_bitlen            :    4;  /*命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
        };
        uint32_t val;
    } user2;
    union {
        struct {
            uint32_t ms_data_bitlen                :    18;  /*这些位的值是在主模式DMA控制传输或CPU控制传输中配置的SPI传输数据位长度。该值也是从模式DMA RX控制传输中配置的比特长度。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
            uint32_t reserved18                    :    14;  /*保留*/
        };
        uint32_t val;
    } ms_dlen;
    union {
        struct {
            uint32_t cs0_dis                       :    1;  /*SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/至CS$n。可在形态状态下配置。*/
            uint32_t cs1_dis                       :    1;  /*SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/至CS$n。可在形态状态下配置。*/
            uint32_t cs2_dis                       :    1;  /*SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/至CS$n。可在形态状态下配置。*/
            uint32_t cs3_dis                       :    1;  /*SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/至CS$n。可在形态状态下配置。*/
            uint32_t cs4_dis                       :    1;  /*SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/至CS$n。可在形态状态下配置。*/
            uint32_t cs5_dis                       :    1;  /*SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/至CS$n。可在形态状态下配置。*/
            uint32_t ck_dis                        :    1;  /*1： spi-clk-out禁用，0:spi-clk-out启用。可在形态状态下配置。*/
            uint32_t master_cs_pol                 :    6;  /*在主模式中，位是spi cs线的极性，其值相当于spi_cs^spi_master_cs_pol。可在形态状态下配置。*/
            uint32_t reserved13                    :    10;  /*保留*/
            uint32_t slave_cs_pol                  :    1;  /*spi从输入cs极性选择。1： 发票0：未更改。可在形态状态下配置。*/
            uint32_t reserved24                    :    5;  /*保留*/
            uint32_t ck_idle_edge                  :    1;  /*1： 当空闲0时spi-clk线为高：当空闲时spi-clk线为低。可在形态状态下配置。*/
            uint32_t cs_keep_active                :    1;  /*当位置位时，spi-cs线保持低电平。可在形态状态下配置。*/
            uint32_t quad_din_pin_swap             :    1;  /*1： spi四输入交换启用0：spi四输出交换禁用。可在形态状态下配置。*/
        };
        uint32_t val;
    } misc;
    union {
        struct {
            uint32_t din0_mode                     :    2;  /*输入信号被SPI模块时钟周期延迟，0：无延迟输入，1：具有clk_apb的偏旁输入，2：具有clk _apb的负边输入，3：具有SPI_clk的输入。可在形态状态下配置。*/
            uint32_t din1_mode                     :    2;  /*输入信号被SPI模块时钟周期延迟，0：无延迟输入，1：具有clk_apb的偏旁输入，2：具有clk _apb的负边输入，3：具有SPI_clk的输入。可在形态状态下配置。*/
            uint32_t din2_mode                     :    2;  /*输入信号被SPI模块时钟周期延迟，0：无延迟输入，1：具有clk_apb的偏旁输入，2：具有clk _apb的负边输入，3：具有SPI_clk的输入。可在形态状态下配置。*/
            uint32_t din3_mode                     :    2;  /*输入信号被SPI模块时钟周期延迟，0：无延迟输入，1：具有clk_apb的偏旁输入，2：具有clk _apb的负边输入，3：具有SPI_clk的输入。可在形态状态下配置。*/
            uint32_t reserved8                     :    8;  /*输入信号被SPI模块时钟周期延迟，0：无延迟输入，1：具有clk_apb的偏旁输入，2：具有clk _apb的负边输入，3：具有SPI_clk的输入。可在形态状态下配置。*/
            uint32_t timing_hclk_active            :    1;  /*1： 启用SPI输入定时模块中的hclk。0：禁用。可在形态状态下配置。*/
            uint32_t reserved17                    :    15;  /*保留*/
        };
        uint32_t val;
    } din_mode;
    union {
        struct {
            uint32_t din0_num                      :    2;  /*输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，……可配置为CONF状态。*/
            uint32_t din1_num                      :    2;  /*输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，……可配置为CONF状态。*/
            uint32_t din2_num                      :    2;  /*输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，……可配置为CONF状态。*/
            uint32_t din3_num                      :    2;  /*输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，……可配置为CONF状态。*/
            uint32_t reserved8                     :    24;  /*保留*/
        };
        uint32_t val;
    } din_num;
    union {
        struct {
            uint32_t dout0_mode                    :    1;  /*输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：在其负边缘的SPI模块时钟周期的输出延迟。可在形态状态下配置。*/
            uint32_t dout1_mode                    :    1;  /*输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：在其负边缘的SPI模块时钟周期的输出延迟。可在形态状态下配置。*/
            uint32_t dout2_mode                    :    1;  /*输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：在其负边缘的SPI模块时钟周期的输出延迟。可在形态状态下配置。*/
            uint32_t dout3_mode                    :    1;  /*输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：在其负边缘的SPI模块时钟周期的输出延迟。可在形态状态下配置。*/
            uint32_t reserved4                     :    28;  /*保留*/
        };
        uint32_t val;
    } dout_mode;
    union {
        struct {
            uint32_t reserved0                     :    18;  /*保留*/
            uint32_t dma_seg_trans_en              :    1;  /*在spi-dma半从模式下启用dma段传输。1： 启用。0：禁用。*/
            uint32_t rx_seg_trans_clr_en           :    1;  /*1： spi_dma_infifofull_vld由spi-slave cmd 5.0清除：spi_trans_done清除spi_dma.infifofull-vld。*/
            uint32_t tx_seg_trans_clr_en           :    1;  /*1： spi_dma_outfifoempty_vld由spi从命令6清除。*/
            uint32_t rx_eof_en                     :    1;  /*1： 当dma推送数据字节的数量等于spi-dma转换中的spi_slv/mst_dma_rd_bytelen[19:0]的值时，设置spi_dma_inlink_eof。0:spi_dma_inlink_eof由非seg trans中的spi_trans_done或seg trans中的spi_dma_seg_trans_done设置。*/
            uint32_t reserved22                    :    5;  /*保留*/
            uint32_t dma_rx_ena                    :    1;  /*设置此位以启用SPI DMA控制的接收数据模式。*/
            uint32_t dma_tx_ena                    :    1;  /*设置此位以启用SPI DMA控制的发送数据模式。*/
            uint32_t rx_afifo_rst                  :    1;  /*设置此位以重置RX AFIFO，用于接收SPI主模式和从模式传输中的数据。*/
            uint32_t buf_afifo_rst                 :    1;  /*设置此位以重置BUF TX AFIFO，用于在SPI从CPU控制模式传输和主模式传输中发送数据。*/
            uint32_t dma_afifo_rst                 :    1;  /*设置此位以重置DMA TX AFIFO，用于在SPI从属DMA控制模式传输中发送数据。*/
        };
        uint32_t val;
    } dma_conf;
    union {
        struct {
            uint32_t infifo_full_err               :    1;  /*SPI_DMA_INFIFO_FULL_ERROR_INT中断的启用位。*/
            uint32_t outfifo_empty_err             :    1;  /*SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的启用位。*/
            uint32_t ex_qpi                        :    1;  /*SPI从设备Ex_QPI中断的启用位。*/
            uint32_t en_qpi                        :    1;  /*SPI从属En_QPI中断的启用位。*/
            uint32_t cmd7                          :    1;  /*SPI从属CMD7中断的启用位。*/
            uint32_t cmd8                          :    1;  /*SPI从属CMD8中断的启用位。*/
            uint32_t cmd9                          :    1;  /*SPI从属CMD9中断的启用位。*/
            uint32_t cmda                          :    1;  /*SPI从属CMDA中断的启用位。*/
            uint32_t rd_dma_done                   :    1;  /*SPI_SLV_RD_DMA_DONE_INT中断的启用位。*/
            uint32_t wr_dma_done                   :    1;  /*SPI_SLV_WR_DMA_DONE_INT中断的启用位。*/
            uint32_t rd_buf_done                   :    1;  /*SPI_SLV_RD_BUF_DON_INT中断的启用位。*/
            uint32_t wr_buf_done                   :    1;  /*SPI_SLV_WR_BUF_DON_INT中断的启用位。*/
            uint32_t trans_done                    :    1;  /*SPI_TRANS_DONE_INT中断的启用位。*/
            uint32_t dma_seg_trans_done            :    1;  /*SPI_DMA_SEG_TRANS_DONE_INT中断的启用位。*/
            uint32_t seg_magic_err                 :    1;  /*SPI_SEG_MAGIC_ERR_INT中断的启用位。*/
            uint32_t buf_addr_err                  :    1;  /*SPI_SLV_BUF_ADDR_ERR_INT中断的启用位。*/
            uint32_t cmd_err                       :    1;  /*SPI_SLV_CMD_ERR_INT中断的启用位。*/
            uint32_t mst_rx_afifo_wfull_err        :    1;  /*SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的启用位。*/
            uint32_t mst_tx_afifo_rempty_err       :    1;  /*SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的启用位。*/
            uint32_t app2                          :    1;  /*SPI_APP2_INT中断的启用位。*/
            uint32_t app1                          :    1;  /*SPI_APP1_INT中断的启用位。*/
            uint32_t reserved21                    :    11;  /*保留*/
        };
        uint32_t val;
    } dma_int_ena;
    union {
        struct {
            uint32_t infifo_full_err               :    1;  /*SPI_DMA_INFIFO_FULL_ERROR_INT中断的清除位。*/
            uint32_t outfifo_empty_err             :    1;  /*SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的清除位。*/
            uint32_t ex_qpi                        :    1;  /*SPI从设备Ex_QPI中断的清除位。*/
            uint32_t en_qpi                        :    1;  /*SPI从属En_QPI中断的清除位。*/
            uint32_t cmd7                          :    1;  /*SPI从属CMD7中断的清除位。*/
            uint32_t cmd8                          :    1;  /*SPI从属CMD8中断的清除位。*/
            uint32_t cmd9                          :    1;  /*SPI从属CMD9中断的清除位。*/
            uint32_t cmda                          :    1;  /*SPI从属CMDA中断的清除位。*/
            uint32_t rd_dma_done                   :    1;  /*SPI_SLV_RD_DMA_DONE_INT中断的清除位。*/
            uint32_t wr_dma_done                   :    1;  /*SPI_SLV_WR_DMA_DONE_INT中断的清除位。*/
            uint32_t rd_buf_done                   :    1;  /*SPI_SLV_RD_BUF_DON_INT中断的清除位。*/
            uint32_t wr_buf_done                   :    1;  /*SPI_SLV_WR_BUF_DON_INT中断的清除位。*/
            uint32_t trans_done                    :    1;  /*SPI_TRANS_DONE_INT中断的清除位。*/
            uint32_t dma_seg_trans_done            :    1;  /*SPI_DMA_SEG_TRANS_DONE_INT中断的清除位。*/
            uint32_t seg_magic_err                 :    1;  /*SPI_SEG_MAGIC_ERR_INT中断的清除位。*/
            uint32_t buf_addr_err                  :    1;  /*SPI_SLV_BUF_ADDR_ERR_INT中断的清除位。*/
            uint32_t cmd_err                       :    1;  /*SPI_SLV_CMD_ERR_INT中断的清除位。*/
            uint32_t mst_rx_afifo_wfull_err        :    1;  /*SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的清除位。*/
            uint32_t mst_tx_afifo_rempty_err       :    1;  /*SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的清除位。*/
            uint32_t app2                          :    1;  /*SPI_APP2_INT中断的清除位。*/
            uint32_t app1                          :    1;  /*SPI_APP1_INT中断的清除位。*/
            uint32_t reserved21                    :    11;  /*保留*/
        };
        uint32_t val;
    } dma_int_clr;
    union {
        struct {
            uint32_t infifo_full_err               :    1;  /*1： DMA Rx的当前数据速率小于SPI，SPI将丢失接收数据。0：其他。*/
            uint32_t outfifo_empty_err             :    1;  /*1： DMA TX的当前数据速率小于SPI。SPI将在主模式下停止，并在从模式下发送所有0。0：其他。*/
            uint32_t ex_qpi                        :    1;  /*SPI从属Ex_QPI中断的原始位。1： SPI从模式Ex_QPI传输结束。0：其他。*/
            uint32_t en_qpi                        :    1;  /*SPI从属En_QPI中断的原始位。1： SPI从属模式En_QPI传输结束。0：其他。*/
            uint32_t cmd7                          :    1;  /*SPI从属CMD7中断的原始位。1： SPI从模式CMD7传输结束。0：其他。*/
            uint32_t cmd8                          :    1;  /*SPI从属CMD8中断的原始位。1： SPI从模式CMD8传输结束。0：其他。*/
            uint32_t cmd9                          :    1;  /*SPI从属CMD9中断的原始位。1： SPI从模式CMD9传输结束。0：其他。*/
            uint32_t cmda                          :    1;  /*SPI从属CMDA中断的原始位。1： SPI从模式CMDA传输结束。0：其他。*/
            uint32_t rd_dma_done                   :    1;  /*SPI_SLV_RD_DMA_DONE_INT中断的原始位。1： SPI从属模式Rd_DMA传输结束。0：其他。*/
            uint32_t wr_dma_done                   :    1;  /*SPI_SLV_WR_DMA_DONE_INT中断的原始位。1： SPI从属模式Wr_DMA传输结束。0：其他。*/
            uint32_t rd_buf_done                   :    1;  /*SPI_SLV_RD_BUF_DON_INT中断的原始位。1： SPI从模式Rd_BUF传输结束。0：其他。*/
            uint32_t wr_buf_done                   :    1;  /*SPI_SLV_WR_BUF_DON_INT中断的原始位。1： SPI从模式Wr_BUF传输结束。0：其他。*/
            uint32_t trans_done                    :    1;  /*SPI_TRANS_DONE_INT中断的原始位。1： SPI主模式传输结束。0：其他。*/
            uint32_t dma_seg_trans_done            :    1;  /*SPI_DMA_SEG_TRANS_DONE_INT中断的原始位。1： spi主DMA全双工/半双工seg-conf传输结束或从半双工seg传输结束。数据已被推送到相应的存储器。0:seg conf trans或seg trans未结束或未发生。*/
            uint32_t seg_magic_err                 :    1;  /*SPI_SEG_MAGIC_ERR_INT中断的原始位。1： CONF缓冲区中的神奇值是DMA seg-CONF传输中的错误。0：其他。*/
            uint32_t buf_addr_err                  :    1;  /*SPI_SLV_BUF_ADDR_ERR_INT中断的原始位。1： 当前SPI从模式CPU控制的FD、Wr_BUF或Rd_BUF传输的访问数据地址大于63.0：其他。*/
            uint32_t cmd_err                       :    1;  /*SPI_SLV_CMD_ERR_INT中断的原始位。1： 当前SPI从属HD模式传输中的从属命令值不受支持。0：其他。*/
            uint32_t mst_rx_afifo_wfull_err        :    1;  /*SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的原始位。1： 当SPI在主模式下输入数据时，存在RX AFIFO写满错误。0：其他。*/
            uint32_t mst_tx_afifo_rempty_err       :    1;  /*SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的原始位。1： 当SPI以主模式输出数据时，存在TX BUF AFIFO读取空错误。0：其他。*/
            uint32_t app2                          :    1;  /*SPI_APP2_INT中断的原始位。该值仅由应用程序控制。*/
            uint32_t app1                          :    1;  /*SPI_APP1_INT中断的原始位。该值仅由应用程序控制。*/
            uint32_t reserved21                    :    11;  /*保留*/
        };
        uint32_t val;
    } dma_int_raw;
    union {
        struct {
            uint32_t infifo_full_err               :    1;  /*SPI_DMA_INFIFO_FULL_ERROR_INT中断的状态位。*/
            uint32_t outfifo_empty_err             :    1;  /*SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的状态位。*/
            uint32_t ex_qpi                        :    1;  /*SPI从属Ex_QPI中断的状态位。*/
            uint32_t en_qpi                        :    1;  /*SPI从属En_QPI中断的状态位。*/
            uint32_t cmd7                          :    1;  /*SPI从属CMD7中断的状态位。*/
            uint32_t cmd8                          :    1;  /*SPI从属CMD8中断的状态位。*/
            uint32_t cmd9                          :    1;  /*SPI从属CMD9中断的状态位。*/
            uint32_t cmda                          :    1;  /*SPI从属CMDA中断的状态位。*/
            uint32_t rd_dma_done                   :    1;  /*SPI_SLV_RD_DMA_DONE_INT中断的状态位。*/
            uint32_t wr_dma_done                   :    1;  /*SPI_SLV_WR_DMA_DONE_INT中断的状态位。*/
            uint32_t rd_buf_done                   :    1;  /*SPI_SLV_RD_BUF_DON_INT中断的状态位。*/
            uint32_t wr_buf_done                   :    1;  /*SPI_SLV_WR_BUF_DON_INT中断的状态位。*/
            uint32_t trans_done                    :    1;  /*SPI_TRANS_DONE_INT中断的状态位。*/
            uint32_t dma_seg_trans_done            :    1;  /*SPI_DMA_SEG_TRANS_DONE_INT中断的状态位。*/
            uint32_t seg_magic_err                 :    1;  /*SPI_SEG_MAGIC_ERR_INT中断的状态位。*/
            uint32_t buf_addr_err                  :    1;  /*SPI_SLV_BUF_ADDR_ERR_INT中断的状态位。*/
            uint32_t cmd_err                       :    1;  /*SPI_SLV_CMD_ERR_INT中断的状态位。*/
            uint32_t mst_rx_afifo_wfull_err        :    1;  /*SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的状态位。*/
            uint32_t mst_tx_afifo_rempty_err       :    1;  /*SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的状态位。*/
            uint32_t app2                          :    1;  /*SPI_APP2_INT中断的状态位。*/
            uint32_t app1                          :    1;  /*SPI_APP1_INT中断的状态位。*/
            uint32_t reserved21                    :    11;  /*保留*/
        };
        uint32_t val;
    } dma_int_st;
    uint32_t reserved_44;
    uint32_t reserved_48;
    uint32_t reserved_4c;
    uint32_t reserved_50;
    uint32_t reserved_54;
    uint32_t reserved_58;
    uint32_t reserved_5c;
    uint32_t reserved_60;
    uint32_t reserved_64;
    uint32_t reserved_68;
    uint32_t reserved_6c;
    uint32_t reserved_70;
    uint32_t reserved_74;
    uint32_t reserved_78;
    uint32_t reserved_7c;
    uint32_t reserved_80;
    uint32_t reserved_84;
    uint32_t reserved_88;
    uint32_t reserved_8c;
    uint32_t reserved_90;
    uint32_t reserved_94;
    uint32_t data_buf[16];
    uint32_t reserved_d8;
    uint32_t reserved_dc;
    union {
        struct {
            uint32_t clk_mode                      :    2;  /*SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。可以在CONF状态下配置。*/
            uint32_t clk_mode_13                   :    1;  /*｛CPOL，CPHA｝，1：支持spi-clk模式1和3，第一边缘输出数据B[0]/B[7]。0：支持spi clk模式0和2，第一边缘输出数据B[1]/B[6]。*/
            uint32_t rsck_data_out                 :    1;  /*当tsck与rsck相同时，它可以节省半个周期。1： rsck posedge 0处的输出数据：tsck posedge处的输出*/
            uint32_t reserved4                     :    4;  /*保留*/
            uint32_t rddma_bitlen_en               :    1;  /*1： SPI_SLV_DATA_BITLEN以DMA控制模式（Rd_DMA）存储主从数据长度的数据位长度。0:其他*/
            uint32_t wrdma_bitlen_en               :    1;  /*1： SPI_SLV_DATA_BITLEN以DMA控制模式（Wr_DMA）存储主写从数据长度的数据位长度。0:其他*/
            uint32_t rdbuf_bitlen_en               :    1;  /*1： SPI_SLV_DATA_BITLEN以CPU控制模式（Rd_BUF）存储主从数据长度的数据位长度。0:其他*/
            uint32_t wrbuf_bitlen_en               :    1;  /*1： SPI_SLV_DATA_BITLEN以CPU控制模式（Wr_BUF）存储主写从数据长度的数据位长度。0:其他*/
            uint32_t reserved12                    :    10;  /*保留*/
            uint32_t dma_seg_magic_value           :    4;  /*主DMA seg trans中BM表的神奇值。*/
            uint32_t slave_mode                    :    1;  /*设置SPI工作模式。1： 从模式0：主模式。*/
            uint32_t soft_reset                    :    1;  /*软件重置启用，重置spi时钟线cs线和数据线。可在形态状态下配置。*/
            uint32_t usr_conf                      :    1;  /*1： 启用当前分段传输操作的DMA CONF阶段，这意味着分段传输将启动。0：这不是seg trans模式。*/
            uint32_t reserved29                    :    3;  /*保留*/
        };
        uint32_t val;
    } slave;
    union {
        struct {
            uint32_t data_bitlen                   :    18;  /*SPI从FD和HD模式下传输的数据位长度。*/
            uint32_t last_command                  :    8;  /*在从属模式下，它是命令值。*/
            uint32_t last_addr                     :    6;  /*在从属模式下，它是地址的值。*/
        };
        uint32_t val;
    } slave1;
    union {
        struct {
            uint32_t clk_en                        :    1;  /*设置此位以启用clk门*/
            uint32_t mst_clk_active                :    1;  /*设置此位以开启SPI模块时钟。*/
            uint32_t mst_clk_sel                   :    1;  /*该位用于在主模式下选择SPI模块时钟源。1： PLL_CLK_80M。0:XTAL CLK。*/
            uint32_t reserved3                     :    29;  /*保留*/
        };
        uint32_t val;
    } clk_gate;
    uint32_t reserved_ec;
    union {
        struct {
            uint32_t date                          :    28;  /*SPI寄存器版本。*/
            uint32_t reserved28                    :    4;  /*保留*/
        };
        uint32_t val;
    } date;
} spi_dev_t;

extern spi_dev_t GPSPI2;

#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_STRUCT_H_ */

