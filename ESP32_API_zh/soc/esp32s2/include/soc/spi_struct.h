// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
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
            uint32_t conf_bitlen:23;                      /*定义spi_CONF状态的spi_clk周期。可在形态状态下配置。*/
            uint32_t reserved23:  1;                      /*保留*/
            uint32_t usr:         1;                      /*用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。无法通过CONF_buf更改。*/
            uint32_t reserved25:  7;                      /*保留*/
        };
        uint32_t val;
    } cmd;
    uint32_t addr;                                        /*[31:8]：从设备的地址[7:0]：保留。可在形态状态下配置。*/
    union {
        struct {
            uint32_t reserved0:    2;                     /*保留*/
            uint32_t ext_hold_en:  1;                     /*设置钻头以保持spi。该位与spi_usr_prep_hold spi_usr_cmd_hold spi_usr_addr_hold spi_usr_dummy_hold spi-usr_din_hold spi/usr_dout_hold和spi_usr_hold_pol组合。可在形态状态下配置。*/
            uint32_t dummy_out:    1;                     /*在虚设阶段，spi的信号电平由spi控制器输出。可在形态状态下配置。*/
            uint32_t reserved4:    1;                     /*保留*/
            uint32_t faddr_dual:   1;                     /*在地址阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。*/
            uint32_t faddr_quad:   1;                     /*在地址阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。*/
            uint32_t faddr_oct:    1;                     /*在地址阶段1：启用0：禁用期间应用8个信号。可在形态状态下配置。*/
            uint32_t fcmd_dual:    1;                     /*在命令阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。*/
            uint32_t fcmd_quad:    1;                     /*在命令阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。*/
            uint32_t fcmd_oct:     1;                     /*在命令阶段1：启用0：禁用期间应用8个信号。可在形态状态下配置。*/
            uint32_t reserved11:   3;                     /*保留*/
            uint32_t fread_dual:   1;                     /*在读取操作中，读取数据阶段施加2个信号。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t fread_quad:   1;                     /*在读取操作中，读取数据阶段施加4个信号。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t fread_oct:    1;                     /*在读取操作中，读取数据阶段施加8个信号。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t reserved17:   1;                     /*保留*/
            uint32_t q_pol:        1;                     /*该位用于设置MISO线极性1：高0低。可在形态状态下配置。*/
            uint32_t d_pol:        1;                     /*该位用于设置MOSI线极性1：高0低。可在形态状态下配置。*/
            uint32_t reserved20:   1;                     /*保留*/
            uint32_t wp:           1;                     /*SPI空闲时的写保护信号输出。1： 输出高0：输出低。可在形态状态下配置。*/
            uint32_t reserved22:   3;                     /*保留*/
            uint32_t rd_bit_order: 1;                     /*在读取数据（MISO）阶段1:LSB优先0:MSB优先。可在形态状态下配置。*/
            uint32_t wr_bit_order: 1;                     /*在命令地址写入数据（MOSI）阶段1:LSB首先为0:MSB。可在形态状态下配置。*/
            uint32_t reserved27:   5;                     /*保留*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t clk_mode:      2;                    /*SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。可以在CONF状态下配置。*/
            uint32_t clk_mode_13:   1;                    /*｛CPOL CPHA｝1：支持spi-clk模式1和3第一边缘输出数据B[0]/B[7]。0：支持spi-clk模式0和2第一边缘输出数据B[1]/B[6]。*/
            uint32_t rsck_data_out: 1;                    /*当tsck与rsck相同时，它可以节省半个周期。1： rsck posedge 0处的输出数据：tsck posedge处的输出*/
            uint32_t w16_17_wr_ena: 1;                    /*1： reg_buf[16][17]可以写入0：reg_buf[11][17]不能写入。可在形态状态下配置。*/
            uint32_t reserved5:     9;                    /*保留*/
            uint32_t cs_hold_delay: 6;                    /*SPI cs信号延迟SPI时钟周期。可在形态状态下配置。*/
            uint32_t reserved20:   12;                    /*保留*/
        };
        uint32_t val;
    } ctrl1;
    union {
        struct {
            uint32_t cs_setup_time:13;                    /*spi时钟准备阶段的（周期+1），该位与spi_cs_setup位组合。可在形态状态下配置。*/
            uint32_t cs_hold_time: 13;                    /*通过spi时钟的cs引脚的延迟周期该位与spicshold位组合。可在形态状态下配置。*/
            uint32_t cs_delay_mode: 3;                    /*spi_cs信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，则延迟一个循环，否则延迟半个循环3：延迟一个。可在形态状态下配置。*/
            uint32_t cs_delay_num:  2;                    /*spi_cs信号被系统时钟周期延迟。可在形态状态下配置。*/
            uint32_t reserved31:    1;                    /*保留*/
        };
        uint32_t val;
    } ctrl2;
    union {
        struct {
            uint32_t clkcnt_l:       6;                   /*在主模式下，它必须等于spi_clkcnt_N。在从属模式下，它必须为0。可以在CONF状态下配置。*/
            uint32_t clkcnt_h:       6;                   /*在主模式下，它必须是floor（（spi_clkcnt_N+1）/2-1）。在从属模式下，它必须为0。可以在CONF状态下配置。*/
            uint32_t clkcnt_n:       6;                   /*在主模式中，它是spi_clk的除法器。因此spi_clk频率为系统/（spi_clkdiv_pre+1）/（spi_clkcnt_N+1）。可在形态状态下配置。*/
            uint32_t clkdiv_pre:    13;                   /*在主模式中，它是spi_clk的预除法器。可在形态状态下配置。*/
            uint32_t clk_equ_sysclk: 1;                   /*在主模式1中：spi_clk与系统0相等：spi_clk与系统时钟分开。可在形态状态下配置。*/
        };
        uint32_t val;
    } clock;
    union {
        struct {
            uint32_t doutdin:           1;                /*设置该位以启用全双工通信。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t reserved1:         2;                /*保留*/
            uint32_t qpi_mode:          1;                /*主模式和从模式。1： spi控制器处于QPI模式。0：其他。可在形态状态下配置。*/
            uint32_t opi_mode:          1;                /*仅适用于主模式。1： spi控制器处于OPI模式（均为8-b-m）。0：其他。可在形态状态下配置。*/
            uint32_t tsck_i_edge:       1;                /*在从属模式下，该位可用于改变tsck的极性。0:tsck=spi_ck_i。1： tsck=！spi_ck_。*/
            uint32_t cs_hold:           1;                /*当spi处于完成阶段时，spi cs保持较低。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t cs_setup:          1;                /*当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t rsck_i_edge:       1;                /*在从属模式下，该位可用于改变rsck的极性。0:rsck=！spi_ck_。1： rsck=spi_ck_i。*/
            uint32_t ck_out_edge:       1;                /*该位与spi_mosidelaymode位组合以设置mosi信号延迟模式。可在形态状态下配置。*/
            uint32_t rd_byte_order:     1;                /*在读取数据（MISO）阶段1:big endian 0:little_endian。可在形态状态下配置。*/
            uint32_t wr_byte_order:     1;                /*在命令地址写入数据（MOSI）阶段1:big endian 0:litte_endian。可在形态状态下配置。*/
            uint32_t fwrite_dual:       1;                /*在写入操作中，读取数据阶段施加2个信号。可在形态状态下配置。*/
            uint32_t fwrite_quad:       1;                /*在写入操作中，读取数据阶段施加4个信号。可在形态状态下配置。*/
            uint32_t fwrite_oct:        1;                /*在写入操作中，读取数据阶段施加8个信号。可在形态状态下配置。*/
            uint32_t usr_conf_nxt:      1;                /*1： 启用下一个分段传输操作的DMA CONF阶段，这意味着分段传输将继续。0：分段传输将在当前SPI分段传输之后结束，或者这不是分段传输模式。可在形态状态下配置。*/
            uint32_t sio:               1;                /*设置该位以启用3线半双工通信mosi和miso信号共享同一引脚。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t usr_hold_pol:      1;                /*它与保持位相结合，以设置spi保持线1的极性：当spi保持线路为高时，spi将保持0：当spi保持线路为低时，spi保持。可在形态状态下配置。*/
            uint32_t usr_dout_hold:     1;                /*spi保持在数据输出状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
            uint32_t usr_din_hold:      1;                /*spi保持在数据状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
            uint32_t usr_dummy_hold:    1;                /*spi保持在伪状态，该位与spi_usr_hold_pol位组合。可在形态状态下配置。*/
            uint32_t usr_addr_hold:     1;                /*spi保持在地址状态，该位与spi_usr_hold_pol位组合。可在形态状态下配置。*/
            uint32_t usr_cmd_hold:      1;                /*spi保持在命令状态，该位与spi_usr_hold_pol位组合。可在形态状态下配置。*/
            uint32_t usr_prep_hold:     1;                /*spi保持在准备状态，该位与spiusr_hold_pol位组合。可在形态状态下配置。*/
            uint32_t usr_miso_highpart: 1;                /*读取数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。*/
            uint32_t usr_mosi_highpart: 1;                /*写入数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。*/
            uint32_t usr_dummy_idle:    1;                /*当位被启用时，spi时钟在伪相位被禁用。可在形态状态下配置。*/
            uint32_t usr_mosi:          1;                /*此位启用操作的写入数据阶段。可在形态状态下配置。*/
            uint32_t usr_miso:          1;                /*此位启用操作的读取数据阶段。可在形态状态下配置。*/
            uint32_t usr_dummy:         1;                /*此位启用操作的虚拟阶段。可在形态状态下配置。*/
            uint32_t usr_addr:          1;                /*此位启用操作的地址阶段。可在形态状态下配置。*/
            uint32_t usr_command:       1;                /*此位启用操作的命令阶段。可在形态状态下配置。*/
        };
        uint32_t val;
    } user;
    union {
        struct {
            uint32_t usr_dummy_cyclelen: 8;               /*虚拟相位的spi_clk周期长度。寄存器值应为（cycle_num-1）。可在形态状态下配置。*/
            uint32_t reserved8:         19;               /*保留*/
            uint32_t usr_addr_bitlen:    5;               /*地址相位的位长度。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
        };
        uint32_t val;
    } user1;
    union {
        struct {
            uint32_t usr_command_value: 16;               /*命令的值。可在形态状态下配置。*/
            uint32_t reserved16:        12;               /*保留*/
            uint32_t usr_command_bitlen: 4;               /*命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
        };
        uint32_t val;
    } user2;
    union {
        struct {
            uint32_t usr_mosi_bit_len:23;                 /*写入数据的位长度。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
            uint32_t reserved23:       9;                 /*保留*/
        };
        uint32_t val;
    } mosi_dlen;
    union {
        struct {
            uint32_t usr_miso_bit_len:23;                 /*读取数据的位长度。寄存器值应为（bit_num-1）。可在形态状态下配置。*/
            uint32_t reserved23:       9;                 /*保留*/
        };
        uint32_t val;
    } miso_dlen;
    union {
        struct {
            uint32_t cs0_dis:           1;                /*SPI CS0引脚启用1：禁用CS0 0：SPI_CS0信号来自/至CS0引脚。可在形态状态下配置。*/
            uint32_t cs1_dis:           1;                /*SPI CS1引脚启用1：禁用CS1 0：SPI_CS1信号来自/至CS1引脚。可在形态状态下配置。*/
            uint32_t cs2_dis:           1;                /*SPI CS2引脚启用1：禁用CS2 0：SPI_CS2信号来自/至CS2引脚。可在形态状态下配置。*/
            uint32_t cs3_dis:           1;                /*保留*/
            uint32_t cs4_dis:           1;                /*SPI CS4引脚启用1：禁用CS4 0：SPI_CS4信号来自/至CS4引脚。可在形态状态下配置。*/
            uint32_t cs5_dis:           1;                /*SPI CS5引脚启用1：禁用CS5 0：SPI_CS5信号来自/至CS5引脚。可在形态状态下配置。*/
            uint32_t ck_dis:            1;                /*1： spi clk out禁用0：spi clk-out启用。可在形态状态下配置。*/
            uint32_t master_cs_pol:     6;                /*在主模式中，位是spi cs线的极性，值等于spi_cs^spi_master_cs_pol。可在形态状态下配置。*/
            uint32_t reserved13:        3;                /*保留*/
            uint32_t clk_data_dtr_en:   1;                /*1： SPI主DTR模式应用于SPI clk数据和SPI_dqs*/
            uint32_t data_dtr_en:       1;                /*1： SPI clk以及SPI_DOUT和SPI_DIN状态的数据处于DTR模式，包括主控1/2/4/8-bm。可在形态状态下配置。*/
            uint32_t addr_dtr_en:       1;                /*1： SPI clk和SPI_SEND_ADDR状态的数据处于DTR模式，包括主控1/2/4/8-bm。可在形态状态下配置。*/
            uint32_t cmd_dtr_en:        1;                /*1： SPI clk和SPI_SEND_CMD状态的数据处于DTR模式，包括主控1/2/4/8-bm。可在形态状态下配置。*/
            uint32_t cd_data_set:       1;                /*1： spi_cd=！spi_st[3:0]处于spi_DOUT或spi_DIN状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
            uint32_t cd_dummy_set:      1;                /*1： spi_cd=！spi_st[3:0]处于spi_DUMMY状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
            uint32_t cd_addr_set:       1;                /*1： spi_cd=！spi_st[3:0]处于spi_SEND_ADDR状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
            uint32_t slave_cs_pol:      1;                /*spi从输入cs极性选择。1： 发票0：未更改。可在形态状态下配置。*/
            uint32_t dqs_idle_edge:     1;                /*spi_dqs的默认值。可在形态状态下配置。*/
            uint32_t cd_cmd_set:        1;                /*1： spi_cd=！spi_st[3:0]处于spi_SEND_CMD状态时的spi_cd_idle_edge。0:spi_cd=spi_cd_idle_edge。可在形态状态下配置。*/
            uint32_t cd_idle_edge:      1;                /*spi_cd的默认值。可在形态状态下配置。*/
            uint32_t reserved27:        2;                /*保留*/
            uint32_t ck_idle_edge:      1;                /*1： 当空闲0时spi-clk线为高：当空闲时spi-clk线为低。可在形态状态下配置。*/
            uint32_t cs_keep_active:    1;                /*当位置位时，spi-cs线保持低电平。可在形态状态下配置。*/
            uint32_t quad_din_pin_swap: 1;                /*1： spi四输入交换启用0：spi四输出交换禁用。可在形态状态下配置。*/
        };
        uint32_t val;
    } misc;
    union {
        struct {
            uint32_t reserved0:              4;           /*保留*/
            uint32_t trans_done:             1;           /*用于在主模式和从模式下完成任何操作的中断原始位。无法通过CONF_buf更改。*/
            uint32_t int_rd_buf_done_en:     1;           /*spi_slv_rd_buf中断启用。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t int_wr_buf_done_en:     1;           /*spi_slv_wr_buf中断启用。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t int_rd_dma_done_en:     1;           /*spi_slv_rd_dma中断启用。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t int_wr_dma_done_en:     1;           /*spi_slv_wr_dma中断启用。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t int_trans_done_en:      1;           /*spi_trans_done中断启用。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t int_dma_seg_trans_en:   1;           /*spi_dma_seg_trans_done中断启用。1： 启用0：禁用。可在形态状态下配置。*/
            uint32_t seg_magic_err_int_en:   1;           /*1： 启用seg魔法值错误中断。0：其他。可在形态状态下配置。*/
            uint32_t reserved12:            11;           /*保留*/
            uint32_t trans_cnt:              4;           /*主模式和从模式下的操作计数器。*/
            uint32_t reserved27:             1;           /*保留*/
            uint32_t reserved28:             1;           /*保留*/
            uint32_t trans_done_auto_clr_en: 1;           /*spi_trans_done自动清除启用在spi_trans-done的pos边缘之后3个apb周期清除它。0：禁用。1： 启用。可在形态状态下配置。*/
            uint32_t slave_mode:             1;           /*设置SPI工作模式。1： 从模式0：主模式。*/
            uint32_t soft_reset:             1;           /*软件复位使能复位spi时钟线cs线和数据线。可在形态状态下配置。*/
        };
        uint32_t val;
    } slave;
    union {
        struct {
            uint32_t reserved0:       10;                 /*保留*/
            uint32_t addr_err_clr:     1;                 /*1： 清除spi_slv_addr_err。0:无效。可以通过CONF_buf更改。*/
            uint32_t cmd_err_clr:      1;                 /*1： 清除spi_slv_cmd_err。0:无效。可以通过CONF_buf更改。*/
            uint32_t no_qpi_en:        1;                 /*1： 不支持spi从属QPI模式。0:支持spi从属QPI模式。*/
            uint32_t addr_err:         1;                 /*1： SPI从属设备不支持上次SPI传输的地址值。0:支持地址值或未收到地址值。*/
            uint32_t cmd_err:          1;                 /*1： SPI从属设备不支持上次SPI传输的命令值。0：支持命令值或未收到命令值。*/
            uint32_t wr_dma_done:      1;                 /*用于在从属模式下完成dma写入操作的中断原始位。无法通过CONF_buf更改。*/
            uint32_t last_command:     8;                 /*在从属模式下，它是命令值。*/
            uint32_t last_addr:        8;                 /*在从属模式下，它是地址的值。*/
        };
        uint32_t val;
    } slave1;
    union {
        struct {
            uint32_t reserved0:       24;                 /*保留*/
            uint32_t wr_buf_done:      1;                 /*用于在从属模式下完成写缓冲操作的中断原始位。无法通过CONF_buf更改。*/
            uint32_t conf_base_bitlen: 7;                 /*CONF状态的基本spi_clk循环。如果启用了spi_usr_CONF，则CONF状态的实际周期长度为spi_CONF_base_bitlen[6:0]+spi_CONF-bitlen[23:0]。*/
        };
        uint32_t val;
    } slv_wrbuf_dlen;
    union {
        struct {
            uint32_t dma_rd_bytelen:    20;               /*在从属模式下，它是读取操作的字节长度。寄存器值应为byte_num。*/
            uint32_t reserved20:         4;               /*保留*/
            uint32_t rd_buf_done:        1;               /*用于在从属模式下完成读缓冲操作的中断原始位。无法通过CONF_buf更改。*/
            uint32_t seg_magic_err:      1;               /*1： CONF缓冲区中最近的魔法值在主DMA seg传输模式中不正确。0：其他。*/
            uint32_t reserved26:         6;               /*保留*/
        };
        uint32_t val;
    } slv_rdbuf_dlen;
    union {
        struct {
            uint32_t data_bytelen:        20;             /*从模式下最后一次SPI传输的全双工或半双工数据字节长度。在半双工模式下，该值由位[23:20]控制。*/
            uint32_t rddma_bytelen_en:     1;             /*1： spi_slv_data_bytelen以DMA控制模式（Rd_DMA）存储主从数据长度的数据字节长度。0:其他*/
            uint32_t wrdma_bytelen_en:     1;             /*1： spi_slv_data_bytelen以DMA控制模式（Wr_DMA）存储主写从数据长度的数据字节长度。0:其他*/
            uint32_t rdbuf_bytelen_en:     1;             /*1： spi_slv_data_bytelen以CPU控制模式（Rd_BUF）存储主从数据长度的数据字节长度。0:其他*/
            uint32_t wrbuf_bytelen_en:     1;             /*1： spi_slv_data_bytelen以CPU控制模式（Wr_BUF）存储主写从数据长度的数据字节长度。0:其他*/
            uint32_t dma_seg_magic_value:  4;             /*主DMA seg trans中BM表的神奇值。*/
            uint32_t reserved28:           2;             /*保留*/
            uint32_t rd_dma_done:          1;             /*在从属模式下完成Rd DMA操作的中断原始位。无法通过CONF_buf更改。*/
            uint32_t usr_conf:             1;             /*1： 启用当前分段传输操作的DMA CONF阶段，这意味着分段传输将启动。0：这不是seg trans模式。*/
        };
        uint32_t val;
    } slv_rd_byte;
    union {
        struct {
            uint32_t st:                 4;               /*spi状态机的状态。0：空闲状态1：准备状态2：发送命令状态3：发送数据状态4：红色数据状态5：写入数据状态6：等待状态7：完成状态。*/
            uint32_t reserved4:          8;               /*保留*/
            uint32_t mst_dma_rd_bytelen:20;               /*在非seg-trans或seg-trans模式下定义主DMA读取字节长度。spi_rx_eof_en为0时无效。可以在CONF状态下配置。。*/
        };
        uint32_t val;
    } fsm;
    union {
        struct {
            uint32_t int_hold_ena:       2;               /*该寄存器用于两个SPI主机共享相同的cs时钟和数据信号。如果另一个SPI忙，则设置一个SPI的位，SPI将保持。1（3）：在空闲阶段保持2：在准备阶段保持。可在形态状态下配置。*/
            uint32_t hold_val:           1;               /*spi保存应与spi_hold_out_en一起使用的输出值。可在形态状态下配置。*/
            uint32_t hold_out_en:        1;               /*启用将spi输出保持值设置为spi_hold_reg。它可以用于用spi_ext_hold_en和其他usr保持信号保持spi状态机。可在形态状态下配置。*/
            uint32_t hold_out_time:      3;               /*当spi_hold_out_en启用时，设置输出spi_hold信号的保持周期。可在形态状态下配置。*/
            uint32_t dma_seg_trans_done: 1;               /*1： spi主DMA全双工/半双工seg传输结束或从半双工seb传输结束。数据已被推送到相应的存储器。0:seg传输未结束或未发生。无法通过CONF_buf更改。*/
            uint32_t reserved8:         24;               /*保留*/
        };
        uint32_t val;
    } hold;
    union {
        struct {
            uint32_t reserved0:               2;          /*保留*/
            uint32_t in_rst:                  1;          /*该位用于在dma fsm和数据fifo指针中重置。*/
            uint32_t out_rst:                 1;          /*该位用于重置dma fsm和数据fifo指针。*/
            uint32_t ahbm_fifo_rst:           1;          /*重置spi-dma ahb主fifo指针。*/
            uint32_t ahbm_rst:                1;          /*重置spi-dma ahb主机。*/
            uint32_t in_loop_test:            1;          /*设置要在链接中测试的位。*/
            uint32_t out_loop_test:           1;          /*设置位以测试链接。*/
            uint32_t out_auto_wrback:         1;          /*当设置位时，当内联长度为0时，DMA继续使用下一个内联节点。*/
            uint32_t out_eof_mode:            1;          /*1：当dma从fifo中弹出所有数据时0：当ahb将所有数据推送到fifo时。*/
            uint32_t outdscr_burst_en:        1;          /*读取描述符在读取内存数据时使用突发模式。*/
            uint32_t indscr_burst_en:         1;          /*当将数据写入存储器时，读描述符使用突发模式。*/
            uint32_t out_data_burst_en:       1;          /*spidma以突发模式从存储器读取数据。*/
            uint32_t mem_trans_en:            1;
            uint32_t dma_rx_stop:             1;          /*当处于continue tx/rx模式时，spidma读取数据停止。*/
            uint32_t dma_tx_stop:             1;          /*当处于continue tx/rx模式时，spidma写入数据停止。*/
            uint32_t dma_continue:            1;          /*spi-dma继续tx/rx数据。*/
            uint32_t last_seg_pop_clr:        1;          /*1： 清除spi_slv_seg_frt_pop_mask。0:其他*/
            uint32_t dma_seg_trans_en:        1;          /*在spi-dma半从模式下启用dma段传输。1： 启用。0：禁用。*/
            uint32_t rx_seg_trans_clr_en:     1;          /*1： spi_dma_infifofull_vld由spi-slave cmd 5.0清除：spi_trans_done清除spi_dma.infifofull-vld。*/
            uint32_t tx_seg_trans_clr_en:     1;          /*1： spi_dma_outfifoempty_vld由spi从命令6清除。*/
            uint32_t rx_eof_en:               1;          /*1： 当dma推送数据字节的数量等于spi-dma转换中的spi_slv/mst_dma_rd_bytelen[19:0]的值时，设置spi_dma_inlink_eof。0:spi_dma_inlink_eof由非seg trans中的spi_trans_done或seg trans中的spi_dma_seg_trans_done设置。*/
            uint32_t infifo_full_clr:         1;          /*1： 清除spi_dma_infifo_full_vld。0：不要控制它。*/
            uint32_t outfifo_empty_clr:       1;          /*1： 清除spi_dma_outfifo_empty_vld。0：不要控制它。*/
            uint32_t reserved24:              2;          /*保留*/
            uint32_t ext_mem_bk_size:         2;          /*选择外部内存块大小。*/
            uint32_t dma_seg_trans_clr:       1;          /*1： 结束作为0x05命令的从属seg trans。2个或更多个端段传输信号将在DMA RX中引起错误。*/
            uint32_t reserved29:              3;          /*保留*/
        };
        uint32_t val;
    } dma_conf;
    union {
        struct {
            uint32_t addr:           20;                  /*第一个outlink描述符的地址。*/
            uint32_t reserved20:      8;                  /*保留*/
            uint32_t stop:            1;                  /*将位设置为停止以使用outlink描述符。*/
            uint32_t start:           1;                  /*设置位以开始使用outlink描述符。*/
            uint32_t restart:         1;                  /*设置要装入新的outlink描述符的位。*/
            uint32_t dma_tx_ena:      1;                  /*spi-dma写入数据状态位。*/
        };
        uint32_t val;
    } dma_out_link;
    union {
        struct {
            uint32_t addr:           20;                  /*第一个内联描述符的地址。*/
            uint32_t auto_ret:        1;                  /*当设置位时，当数据包出错时，内联描述符返回到第一个链接节点。*/
            uint32_t reserved21:      7;                  /*保留*/
            uint32_t stop:            1;                  /*将位设置为stop以使用内联描述符。*/
            uint32_t start:           1;                  /*设置开始使用内联描述符的位。*/
            uint32_t restart:         1;                  /*设置要装入新内联描述符的位。*/
            uint32_t dma_rx_ena:      1;                  /*spi-dma读取数据状态位。*/
        };
        uint32_t val;
    } dma_in_link;
    union {
        struct {
            uint32_t inlink_dscr_empty:          1;       /*缺少足够内联描述符的启用位。可在形态状态下配置。*/
            uint32_t outlink_dscr_error:         1;       /*outlink描述符错误的启用位。可在形态状态下配置。*/
            uint32_t inlink_dscr_error:          1;       /*内联描述符错误的启用位。可在形态状态下配置。*/
            uint32_t in_done:                    1;       /*用于完成内联描述符使用的启用位。可在形态状态下配置。*/
            uint32_t in_err_eof:                 1;       /*接收错误的启用位。可在形态状态下配置。*/
            uint32_t in_suc_eof:                 1;       /*用于完成从主机接收所有数据包的启用位。可在形态状态下配置。*/
            uint32_t out_done:                   1;       /*用于完成outlink描述符使用的启用位。可以在CONF状态下配置。*/
            uint32_t out_eof:                    1;       /*向主机发送数据包的启用位已完成。可在形态状态下配置。*/
            uint32_t out_total_eof:              1;       /*用于向主机发送所有数据包的启用位已完成。可在形态状态下配置。*/
            uint32_t infifo_full_err:            1;       /*infinfo完全错误中断的启用位。*/
            uint32_t outfifo_empty_err:          1;       /*outifo空错误中断的启用位。*/
            uint32_t cmd6:                       1;       /*SPI从属CMD6中断的启用位。*/
            uint32_t cmd7:                       1;       /*SPI从属CMD7中断的启用位。*/
            uint32_t cmd8:                       1;       /*SPI从属CMD8中断的启用位。*/
            uint32_t cmd9:                       1;       /*SPI从属CMD9中断的启用位。*/
            uint32_t cmda:                       1;       /*SPI从属CMDA中断的启用位。*/
            uint32_t reserved16:                16;       /*保留*/
        };
        uint32_t val;
    } dma_int_ena;
    union {
        struct {
            uint32_t inlink_dscr_empty:          1;       /*缺少足够内联描述符的原始位。可在形态状态下配置。*/
            uint32_t outlink_dscr_error:         1;       /*outlink描述符错误的原始位。可在形态状态下配置。*/
            uint32_t inlink_dscr_error:          1;       /*内联描述符错误的原始位。可在形态状态下配置。*/
            uint32_t in_done:                    1;       /*用于完成内联描述符使用的原始位。可在形态状态下配置。*/
            uint32_t in_err_eof:                 1;       /*接收错误的原始位。可在形态状态下配置。*/
            uint32_t in_suc_eof:                 1;       /*用于完成从主机接收所有数据包的原始位。可在形态状态下配置。*/
            uint32_t out_done:                   1;       /*用于完成outlink描述符使用的原始位。可在形态状态下配置。*/
            uint32_t out_eof:                    1;       /*向主机发送数据包的原始位已完成。可在形态状态下配置。*/
            uint32_t out_total_eof:              1;       /*将所有数据包发送到主机的原始位已完成。可在形态状态下配置。*/
            uint32_t infifo_full_err:            1;       /*1： spi_dma_infifo_full和spi_push_data_prep有效，这意味着dma Rx缓冲区已满。0：其他。无法通过CONF_buf更改。*/
            uint32_t outfifo_empty_err:          1;       /*1： spi_dma_outfifoempty和spi_pop_data_prep有效，这意味着没有要弹出的数据，但pop有效。0：其他。无法通过CONF_buf更改。*/
            uint32_t cmd6:                       1;       /*SPI从属CMD6中断的原始位。*/
            uint32_t cmd7:                       1;       /*SPI从属CMD7中断的原始位。*/
            uint32_t cmd8:                       1;       /*SPI从属CMD8中断的原始位。*/
            uint32_t cmd9:                       1;       /*SPI从属CMD9中断的原始位。*/
            uint32_t cmda:                       1;       /*SPI从属CMDA中断的原始位。*/
            uint32_t reserved16:                16;       /*保留*/
        };
        uint32_t val;
    } dma_int_raw;
    union {
        struct {
            uint32_t inlink_dscr_empty:         1;        /*缺少足够内联描述符的状态位。*/
            uint32_t outlink_dscr_error:        1;        /*outlink描述符错误的状态位。*/
            uint32_t inlink_dscr_error:         1;        /*内联描述符错误的状态位。*/
            uint32_t in_done:                   1;        /*用于完成内联描述符使用的状态位。*/
            uint32_t in_err_eof:                1;        /*接收错误的状态位。*/
            uint32_t in_suc_eof:                1;        /*完成从主机接收所有数据包的状态位。*/
            uint32_t out_done:                  1;        /*用于完成outlink描述符使用的状态位。*/
            uint32_t out_eof:                   1;        /*向主机发送数据包的状态位已完成。*/
            uint32_t out_total_eof:             1;        /*向主机发送所有数据包的状态位已完成。*/
            uint32_t infifo_full_err:           1;        /*infinfo完全错误的状态位。*/
            uint32_t outfifo_empty_err:         1;        /*outifo空错误的状态位。*/
            uint32_t cmd6:                      1;        /*SPI从属CMD6中断的状态位。*/
            uint32_t cmd7:                      1;        /*SPI从属CMD7中断的状态位。*/
            uint32_t cmd8:                      1;        /*SPI从属CMD8中断的状态位。*/
            uint32_t cmd9:                      1;        /*SPI从属CMD9中断的状态位。*/
            uint32_t cmda:                      1;        /*SPI从属CMDA中断的状态位。*/
            uint32_t reserved16:               16;        /*保留*/
        };
        uint32_t val;
    } dma_int_st;
    union {
        struct {
            uint32_t inlink_dscr_empty:          1;       /*缺少足够的内联描述符的明确位。可在形态状态下配置。*/
            uint32_t outlink_dscr_error:         1;       /*outlink描述符错误的清除位。可在形态状态下配置。*/
            uint32_t inlink_dscr_error:          1;       /*内联描述符错误的清除位。可在形态状态下配置。*/
            uint32_t in_done:                    1;       /*用于完成内联描述符使用的清除位。可在形态状态下配置。*/
            uint32_t in_err_eof:                 1;       /*接收错误的清除位。可在形态状态下配置。*/
            uint32_t in_suc_eof:                 1;       /*用于完成从主机接收所有数据包的清除位。可在形态状态下配置。*/
            uint32_t out_done:                   1;       /*用于完成outlink描述符使用的清除位。可在形态状态下配置。*/
            uint32_t out_eof:                    1;       /*向主机发送数据包的清除位已完成。可在形态状态下配置。*/
            uint32_t out_total_eof:              1;       /*将所有数据包发送到主机的清除位已完成。可在形态状态下配置。*/
            uint32_t infifo_full_err:            1;       /*1： 清除spi_dma_infifo_full_err。0:无效。可以通过CONF_buf更改。*/
            uint32_t outfifo_empty_err:          1;       /*1： 清除spi_dma_outfifo_empty_err信号。0:无效。可以通过CONF_buf更改。*/
            uint32_t cmd6:                       1;       /*SPI从属CMD6中断的清除位。*/
            uint32_t cmd7:                       1;       /*SPI从属CMD7中断的清除位。*/
            uint32_t cmd8:                       1;       /*SPI从属CMD8中断的清除位。*/
            uint32_t cmd9:                       1;       /*SPI从属CMD9中断的清除位。*/
            uint32_t cmda:                       1;       /*SPI从属CMDA中断的清除位。*/
            uint32_t reserved16:                16;       /*保留*/
        };
        uint32_t val;
    } dma_int_clr;
    uint32_t dma_in_err_eof_des_addr;                         /*spidma产生接收错误时的内联描述符地址。*/
    uint32_t dma_in_suc_eof_des_addr;                         /*spi-dma生成from_suc_eof时的最后一个内联描述符地址。*/
    uint32_t dma_inlink_dscr;                                 /*当前在描述符指针中的内容。*/
    uint32_t dma_inlink_dscr_bf0;                             /*描述符指针中next的内容。*/
    uint32_t dma_inlink_dscr_bf1;                             /*描述符中当前数据缓冲区指针的内容。*/
    uint32_t dma_out_eof_bfr_des_addr;                        /*相对于产生eof的outlink描述符的缓冲区地址。*/
    uint32_t dma_out_eof_des_addr;                            /*spi-dma生成to_eof时的最后一个outlink描述符地址。*/
    uint32_t dma_outlink_dscr;                                /*当前输出描述符指针的内容。*/
    uint32_t dma_outlink_dscr_bf0;                            /*下一个输出描述符指针的内容。*/
    uint32_t dma_outlink_dscr_bf1;                            /*当前输出描述符数据缓冲区指针的内容。*/
    union {
        struct {
            uint32_t out_dscr_addr:    18;                /*SPI dma输出描述符地址。*/
            uint32_t out_dscr_state:    2;                /*SPI dma输出描述符状态。*/
            uint32_t out_state:         3;                /*SPI dma输出数据状态。*/
            uint32_t out_fifo_cnt:      7;                /*SPI dma outifo数据的剩余部分。*/
            uint32_t out_fifo_full:     1;                /*SPI dma outifo已满。*/
            uint32_t out_fifo_empty:    1;                /*SPI dma outifo为空。*/
        };
        uint32_t val;
    } dma_out_status;
    union {
        struct {
            uint32_t in_dscr_addr:    18;                 /*描述符地址中的SPI dma。*/
            uint32_t in_dscr_state:    2;                 /*SPI dma处于描述符状态。*/
            uint32_t in_state:         3;                 /*SPI dma处于数据状态。*/
            uint32_t in_fifo_cnt:      7;                 /*SPI dma infinfo数据的剩余部分。*/
            uint32_t in_fifo_full:     1;                 /*SPI dma infinfo已满。*/
            uint32_t in_fifo_empty:    1;                 /*SPI dma infinfo为空。*/
        };
        uint32_t val;
    } dma_in_status;
    uint32_t data_buf[18];                                          /*数据缓冲器*/
    union {
        struct {
            uint32_t din0_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din1_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din2_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din3_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din4_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din5_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din6_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t din7_mode:      3;                   /*输入信号被延迟系统时钟周期0：输入而不延迟1：输入，具有clk_apb 2的偏倚。可在形态状态下配置。*/
            uint32_t timing_clk_ena: 1;                   /*1： 在spitiming.v.0中启用hclk：禁用它。可在形态状态下配置。*/
            uint32_t reserved25:     7;                   /*保留*/
        };
        uint32_t val;
    } din_mode;
    union {
        struct {
            uint32_t din0_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din1_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din2_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din3_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din4_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din5_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din6_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t din7_num:   2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t reserved16:16;                       /*保留*/
        };
        uint32_t val;
    } din_num;
    union {
        struct {
            uint32_t dout0_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout1_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout2_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout3_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout4_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout5_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout6_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t dout7_mode: 3;                       /*输出信号被系统时钟周期0延迟：无延迟的输出1：带clk_apb2的偏倚输出，带clk-apb3的负边输出：带spiclk的输出。可在形态状态下配置。*/
            uint32_t reserved24: 8;                       /*保留*/
        };
        uint32_t val;
    } dout_mode;
    union {
        struct {
            uint32_t dout0_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout1_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout2_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout3_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout4_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout5_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout6_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t dout7_num:  2;                       /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t reserved16:16;                       /*保留*/
        };
        uint32_t val;
    } dout_num;
    union {
        struct {
            uint32_t lcd_hb_front: 11;                    /*它是框架的水平空白前门廊。可在形态状态下配置。*/
            uint32_t lcd_va_height:10;                    /*它是框架的垂直活动高度。可在形态状态下配置。*/
            uint32_t lcd_vt_height:10;                    /*它是框架的垂直总高度。可在形态状态下配置。*/
            uint32_t lcd_mode_en:   1;                    /*1： 启用LCD模式输出vsync hsync de.0：禁用。可在形态状态下配置。*/
        };
        uint32_t val;
    } lcd_ctrl;
    union {
        struct {
            uint32_t lcd_vb_front: 8;                     /*它是框架的垂直空白前门廊。可在形态状态下配置。*/
            uint32_t lcd_ha_width:12;                     /*它是帧的水平活动宽度。可在形态状态下配置。*/
            uint32_t lcd_ht_width:12;                     /*它是框架的水平总宽度。可在形态状态下配置。*/
        };
        uint32_t val;
    } lcd_ctrl1;
    union {
        struct {
            uint32_t lcd_vsync_width:    7;               /*这是一行中spi_vsync激活脉冲的位置。可在形态状态下配置。*/
            uint32_t vsync_idle_pol:     1;               /*它是spi_vsync的空闲值。可在形态状态下配置。*/
            uint32_t reserved8:          8;               /*保留*/
            uint32_t lcd_hsync_width:    7;               /*这是一行中spi_hsync激活脉冲的位置。可在形态状态下配置。*/
            uint32_t hsync_idle_pol:     1;               /*它是spi_hsync的空闲值。可在形态状态下配置。*/
            uint32_t lcd_hsync_position: 8;               /*这是一行中spi_hsync激活脉冲的位置。可在形态状态下配置。*/
        };
        uint32_t val;
    } lcd_ctrl2;
    union {
        struct {
            uint32_t d_dqs_mode:   3;                     /*输出spidqs被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
            uint32_t d_cd_mode:    3;                     /*输出spicd被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
            uint32_t d_de_mode:    3;                     /*输出spi_de被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
            uint32_t d_hsync_mode: 3;                     /*输出spi_sync被系统时钟周期0延迟：输出没有延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
            uint32_t d_vsync_mode: 3;                     /*输出spisync被系统时钟周期0延迟：输出无延迟1：输出具有clk_apb 2的偏旁，输出具有clk _apb 3的负边：输出具有spiclk。可在形态状态下配置。*/
            uint32_t de_idle_pol:  1;                     /*它是spi_de的空闲值。*/
            uint32_t hs_blank_en:  1;                     /*1： spi_hsync的脉冲在seg trans或one trans的垂直消隐行中输出。0:spi_hsync脉冲仅在seg trans中的有源区行中有效。*/
            uint32_t reserved17:  15;                     /*保留*/
        };
        uint32_t val;
    } lcd_d_mode;
    union {
        struct {
            uint32_t d_dqs_num:   2;                      /*输出spi_dqs延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t d_cd_num:    2;                      /*输出spi_cd延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t d_de_num:    2;                      /*输出spi_de延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t d_hsync_num: 2;                      /*输出spi_hsync延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t d_vsync_num: 2;                      /*输出spi_vsync延迟系统时钟周期0：延迟1个周期1：延迟2个周期……可配置为CONF状态。*/
            uint32_t reserved10: 22;                      /*保留*/
        };
        uint32_t val;
    } lcd_d_num;
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
    uint32_t reserved_130;
    uint32_t reserved_134;
    uint32_t reserved_138;
    uint32_t reserved_13c;
    uint32_t reserved_140;
    uint32_t reserved_144;
    uint32_t reserved_148;
    uint32_t reserved_14c;
    uint32_t reserved_150;
    uint32_t reserved_154;
    uint32_t reserved_158;
    uint32_t reserved_15c;
    uint32_t reserved_160;
    uint32_t reserved_164;
    uint32_t reserved_168;
    uint32_t reserved_16c;
    uint32_t reserved_170;
    uint32_t reserved_174;
    uint32_t reserved_178;
    uint32_t reserved_17c;
    uint32_t reserved_180;
    uint32_t reserved_184;
    uint32_t reserved_188;
    uint32_t reserved_18c;
    uint32_t reserved_190;
    uint32_t reserved_194;
    uint32_t reserved_198;
    uint32_t reserved_19c;
    uint32_t reserved_1a0;
    uint32_t reserved_1a4;
    uint32_t reserved_1a8;
    uint32_t reserved_1ac;
    uint32_t reserved_1b0;
    uint32_t reserved_1b4;
    uint32_t reserved_1b8;
    uint32_t reserved_1bc;
    uint32_t reserved_1c0;
    uint32_t reserved_1c4;
    uint32_t reserved_1c8;
    uint32_t reserved_1cc;
    uint32_t reserved_1d0;
    uint32_t reserved_1d4;
    uint32_t reserved_1d8;
    uint32_t reserved_1dc;
    uint32_t reserved_1e0;
    uint32_t reserved_1e4;
    uint32_t reserved_1e8;
    uint32_t reserved_1ec;
    uint32_t reserved_1f0;
    uint32_t reserved_1f4;
    uint32_t reserved_1f8;
    uint32_t reserved_1fc;
    uint32_t reserved_200;
    uint32_t reserved_204;
    uint32_t reserved_208;
    uint32_t reserved_20c;
    uint32_t reserved_210;
    uint32_t reserved_214;
    uint32_t reserved_218;
    uint32_t reserved_21c;
    uint32_t reserved_220;
    uint32_t reserved_224;
    uint32_t reserved_228;
    uint32_t reserved_22c;
    uint32_t reserved_230;
    uint32_t reserved_234;
    uint32_t reserved_238;
    uint32_t reserved_23c;
    uint32_t reserved_240;
    uint32_t reserved_244;
    uint32_t reserved_248;
    uint32_t reserved_24c;
    uint32_t reserved_250;
    uint32_t reserved_254;
    uint32_t reserved_258;
    uint32_t reserved_25c;
    uint32_t reserved_260;
    uint32_t reserved_264;
    uint32_t reserved_268;
    uint32_t reserved_26c;
    uint32_t reserved_270;
    uint32_t reserved_274;
    uint32_t reserved_278;
    uint32_t reserved_27c;
    uint32_t reserved_280;
    uint32_t reserved_284;
    uint32_t reserved_288;
    uint32_t reserved_28c;
    uint32_t reserved_290;
    uint32_t reserved_294;
    uint32_t reserved_298;
    uint32_t reserved_29c;
    uint32_t reserved_2a0;
    uint32_t reserved_2a4;
    uint32_t reserved_2a8;
    uint32_t reserved_2ac;
    uint32_t reserved_2b0;
    uint32_t reserved_2b4;
    uint32_t reserved_2b8;
    uint32_t reserved_2bc;
    uint32_t reserved_2c0;
    uint32_t reserved_2c4;
    uint32_t reserved_2c8;
    uint32_t reserved_2cc;
    uint32_t reserved_2d0;
    uint32_t reserved_2d4;
    uint32_t reserved_2d8;
    uint32_t reserved_2dc;
    uint32_t reserved_2e0;
    uint32_t reserved_2e4;
    uint32_t reserved_2e8;
    uint32_t reserved_2ec;
    uint32_t reserved_2f0;
    uint32_t reserved_2f4;
    uint32_t reserved_2f8;
    uint32_t reserved_2fc;
    uint32_t reserved_300;
    uint32_t reserved_304;
    uint32_t reserved_308;
    uint32_t reserved_30c;
    uint32_t reserved_310;
    uint32_t reserved_314;
    uint32_t reserved_318;
    uint32_t reserved_31c;
    uint32_t reserved_320;
    uint32_t reserved_324;
    uint32_t reserved_328;
    uint32_t reserved_32c;
    uint32_t reserved_330;
    uint32_t reserved_334;
    uint32_t reserved_338;
    uint32_t reserved_33c;
    uint32_t reserved_340;
    uint32_t reserved_344;
    uint32_t reserved_348;
    uint32_t reserved_34c;
    uint32_t reserved_350;
    uint32_t reserved_354;
    uint32_t reserved_358;
    uint32_t reserved_35c;
    uint32_t reserved_360;
    uint32_t reserved_364;
    uint32_t reserved_368;
    uint32_t reserved_36c;
    uint32_t reserved_370;
    uint32_t reserved_374;
    uint32_t reserved_378;
    uint32_t reserved_37c;
    uint32_t reserved_380;
    uint32_t reserved_384;
    uint32_t reserved_388;
    uint32_t reserved_38c;
    uint32_t reserved_390;
    uint32_t reserved_394;
    uint32_t reserved_398;
    uint32_t reserved_39c;
    uint32_t reserved_3a0;
    uint32_t reserved_3a4;
    uint32_t reserved_3a8;
    uint32_t reserved_3ac;
    uint32_t reserved_3b0;
    uint32_t reserved_3b4;
    uint32_t reserved_3b8;
    uint32_t reserved_3bc;
    uint32_t reserved_3c0;
    uint32_t reserved_3c4;
    uint32_t reserved_3c8;
    uint32_t reserved_3cc;
    uint32_t reserved_3d0;
    uint32_t reserved_3d4;
    uint32_t reserved_3d8;
    uint32_t reserved_3dc;
    uint32_t reserved_3e0;
    uint32_t reserved_3e4;
    uint32_t reserved_3e8;
    uint32_t reserved_3ec;
    uint32_t reserved_3f0;
    uint32_t reserved_3f4;
    uint32_t reserved_3f8;
    union {
        struct {
            uint32_t date:      28;                       /*SPI寄存器版本。*/
            uint32_t reserved28: 4;                       /*保留*/
        };
        uint32_t val;
    } date;
} spi_dev_t;
extern spi_dev_t GPSPI2;   //FSPI
extern spi_dev_t GPSPI3;   //HSPI

_Static_assert(sizeof(spi_dev_t)==0x400, "***invalid spi");


#ifdef __cplusplus
}
#endif

#endif  /* _SOC_SPI_STRUCT_H_ */

