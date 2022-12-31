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
#ifndef _SOC_SPI_STRUCT_H_
#define _SOC_SPI_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct spi_dev_s {
    union {
        struct {
            uint32_t reserved0: 16;                         /*保留*/
            uint32_t flash_per:  1;                         /*当该位被设置时，将触发程序擦除恢复位程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pes:  1;                         /*当位被设置时，将触发程序擦除暂停位程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t usr:        1;                         /*用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_hpm:  1;                         /*将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_res:  1;                         /*此位与reg_resandres位结合使用，可将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_dp:   1;                         /*将闪存驱动器关闭。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_ce:   1;                         /*芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_be:   1;                         /*块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_se:   1;                         /*扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pp:   1;                         /*页面编程启用（要编程的数据为1字节~256字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
            uint32_t flash_wrsr: 1;                         /*写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdsr: 1;                         /*读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdid: 1;                         /*读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wrdi: 1;                         /*写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wren: 1;                         /*写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_read: 1;                         /*读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
        };
        uint32_t val;
    } cmd;
    uint32_t addr;                                          /*从/从主机的地址。从MSB到LSB的SPI传输。如果长度>32位，则地址从slv_wr_status的MSB开始继续。*/
    union {
        struct {
            uint32_t reserved0:         10;                 /*保留*/
            uint32_t fcs_crc_en:         1;                 /*对于SPI1，在将加密数据写入闪存之前初始化crc32模块。低激活。*/
            uint32_t tx_crc_en:          1;                 /*对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0:禁用*/
            uint32_t wait_flash_idle_en: 1;                 /*当程序闪存或擦除闪存时，等待闪存空闲。1： 启用0：禁用。*/
            uint32_t fastrd_mode:        1;                 /*此位启用以下位：spi_fread_qio spi_fread_dio spi_fread_6out和spi_fread_dout。1： 启用0：禁用。*/
            uint32_t fread_dual:         1;                 /*在读取操作中，读取数据阶段施加2个信号。1： 启用0：禁用。*/
            uint32_t resandres:          1;                 /*设备ID被读出到SPI_RD_STATUS寄存器，该位与SPI_flash_res位组合。1： 启用0：禁用。*/
            uint32_t reserved16:         4;                 /*保留*/
            uint32_t fread_quad:         1;                 /*在读取操作中，读取数据阶段施加4个信号。1： 启用0：禁用。*/
            uint32_t wp:                 1;                 /*SPI空闲时的写保护信号输出。1： 输出高0：输出低。*/
            uint32_t wrsr_2b:            1;                 /*当状态寄存器被设置时，两个字节的数据将被写入状态寄存器。1： 启用0：禁用。*/
            uint32_t fread_dio:          1;                 /*在读操作中，地址阶段和读数据阶段施加2个信号。1： 启用0：禁用。*/
            uint32_t fread_qio:          1;                 /*在读操作中，地址阶段和读数据阶段施加4个信号。1： 启用0：禁用。*/
            uint32_t rd_bit_order:       1;                 /*在读数据（MISO）阶段1:LSB优先0:MSB优先*/
            uint32_t wr_bit_order:       1;                 /*在命令地址写入数据（MOSI）阶段1:LSB首先为0:MSB*/
            uint32_t reserved27:         5;                 /*保留*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t reserved0:        16;                  /*保留*/
            uint32_t cs_hold_delay_res:12;                  /*当spi时钟启用恢复闪存时，恢复闪存的延迟周期。*/
            uint32_t cs_hold_delay:     4;                  /*SPI cs信号延迟SPI时钟周期*/
        };
        uint32_t val;
    } ctrl1;
    union {
        struct {
            uint32_t status:    16;                         /*在从属模式下，它是主机读取的状态。*/
            uint32_t wb_mode:    8;                         /*在闪存快速读取模式中，模式位与spi_fastrd_Mode位组合。*/
            uint32_t status_ext: 8;                         /*在从属模式下，它是主机读取的状态。*/
        };
        uint32_t val;
    } rd_status;
    union {
        struct {
            uint32_t setup_time:       4;                   /*（周期-1），准备，按spi时钟相位，该位与spi_cs_setup位组合。*/
            uint32_t hold_time:        4;                   /*通过spi时钟延迟cs引脚的周期，该位与spicshold位组合。*/
            uint32_t ck_out_low_mode:  4;                   /*当值大于8时，修改spi时钟占空比，这些位与spi_clkcnt_N位和spi_clkcnt_L位组合。*/
            uint32_t ck_out_high_mode: 4;                   /*当值大于8时，修改spi时钟占空比，这些位与spi_clkcnt_N位和spi_clkcnt_H位组合。*/
            uint32_t miso_delay_mode:  2;                   /*MISO信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，否则延迟半个循环3：延迟一个循环*/
            uint32_t miso_delay_num:   3;                   /*MISO信号被系统时钟周期延迟*/
            uint32_t mosi_delay_mode:  2;                   /*MOSI信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，否则延迟半个循环3：延迟一个循环*/
            uint32_t mosi_delay_num:   3;                   /*MOSI信号被系统时钟周期延迟*/
            uint32_t cs_delay_mode:    2;                   /*spi_cs信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，则延迟一个循环，否则延迟半个循环3：延迟一个*/
            uint32_t cs_delay_num:     4;                   /*spi_cs信号被系统时钟周期延迟*/
        };
        uint32_t val;
    } ctrl2;
    union {
        struct {
            uint32_t clkcnt_l:       6;                     /*在主模式下，它必须等于spi_clkcnt_N。在从属模式下，必须为0。*/
            uint32_t clkcnt_h:       6;                     /*在主模式下，它必须是floor（（spi_clkcnt_N+1）/2-1）。在从属模式下，必须为0。*/
            uint32_t clkcnt_n:       6;                     /*在主模式中，它是spi_clk的除法器。因此spi_clk频率为系统/（spi_clkdiv_pre+1）/（spi_clkcnt_N+1）*/
            uint32_t clkdiv_pre:    13;                     /*在主模式中，它是spi_clk的预除法器。*/
            uint32_t clk_equ_sysclk: 1;                     /*在主模式1中：spi_clk与系统0相等：spi_clk与系统时钟分开。*/
        };
        uint32_t val;
    } clock;
    union {
        struct {
            uint32_t doutdin:           1;                  /*设置该位以启用全双工通信。1： 启用0：禁用。*/
            uint32_t reserved1:         3;                  /*保留*/
            uint32_t cs_hold:           1;                  /*当spi处于、完成阶段时，spi cs保持低位。1： 启用0：禁用。*/
            uint32_t cs_setup:          1;                  /*spi cs在spi处于准备阶段时启用。1： 启用0：禁用。*/
            uint32_t ck_i_edge:         1;                  /*在从属模式中，位与主模式中的spi_ck_out_edge相同。它与spi_miso_delay_mode位组合。*/
            uint32_t ck_out_edge:       1;                  /*该位与spi_mosidelaymode位组合以设置mosi信号延迟模式。*/
            uint32_t reserved8:         2;                  /*保留*/
            uint32_t rd_byte_order:     1;                  /*在读数据（MISO）阶段1:big endian 0:little_endian*/
            uint32_t wr_byte_order:     1;                  /*在命令地址写入数据（MOSI）阶段1:big endian 0:litte_endian*/
            uint32_t fwrite_dual:       1;                  /*在写入操作中，读取数据阶段应用2个信号*/
            uint32_t fwrite_quad:       1;                  /*在写入操作中，读取数据阶段应用4个信号*/
            uint32_t fwrite_dio:        1;                  /*在写操作中，地址阶段和读数据阶段施加2个信号。*/
            uint32_t fwrite_qio:        1;                  /*在写操作中，地址阶段和读数据阶段施加4个信号。*/
            uint32_t sio:               1;                  /*设置该位以启用3线半双工通信mosi和miso信号共享同一引脚。1： 启用0：禁用。*/
            uint32_t usr_hold_pol:      1;                  /*它与保持位组合以设置spi保持线1的极性：当spi保持线路为高时，spi将保持0：当spi保持线路为低时，spi保持*/
            uint32_t usr_dout_hold:     1;                  /*spi保持在数据输出状态，该位与spi_usr_hold_pol位组合。*/
            uint32_t usr_din_hold:      1;                  /*spi保持在与spi_usr_hold_pol位组合的数据状态。*/
            uint32_t usr_dummy_hold:    1;                  /*spi保持在伪状态，该位与spi_usr_hold_pol位组合。*/
            uint32_t usr_addr_hold:     1;                  /*spi保持在与spi_usr_hold_pol位组合的地址状态。*/
            uint32_t usr_cmd_hold:      1;                  /*spi保持在命令状态，该位与spi_usr_hold_pol位组合。*/
            uint32_t usr_prep_hold:     1;                  /*spi保持在准备状态，该位与spi_usr_hold_pol位组合。*/
            uint32_t usr_miso_highpart: 1;                  /*读取数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。*/
            uint32_t usr_mosi_highpart: 1;                  /*写入数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。*/
            uint32_t usr_dummy_idle:    1;                  /*当位被启用时，spi时钟在伪相位被禁用。*/
            uint32_t usr_mosi:          1;                  /*此位启用操作的写入数据阶段。*/
            uint32_t usr_miso:          1;                  /*此位启用操作的读取数据阶段。*/
            uint32_t usr_dummy:         1;                  /*此位启用操作的虚拟阶段。*/
            uint32_t usr_addr:          1;                  /*此位启用操作的地址阶段。*/
            uint32_t usr_command:       1;                  /*此位启用操作的命令阶段。*/
        };
        uint32_t val;
    } user;
    union {
        struct {
            uint32_t usr_dummy_cyclelen: 8;                 /*虚拟相位的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
            uint32_t reserved8:         18;                 /*保留*/
            uint32_t usr_addr_bitlen:    6;                 /*地址相位的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } user1;
    union {
        struct {
            uint32_t usr_command_value: 16;                 /*命令的值。输出顺序：位7-0，然后是15-8。*/
            uint32_t reserved16:        12;                 /*保留*/
            uint32_t usr_command_bitlen: 4;                 /*命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）*/
        };
        uint32_t val;
    } user2;
    union {
        struct {
            uint32_t usr_mosi_dbitlen:24;                   /*写入数据的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved24:       8;                   /*保留*/
        };
        uint32_t val;
    } mosi_dlen;
    union {
        struct {
            uint32_t usr_miso_dbitlen:24;                   /*读取数据的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved24:       8;                   /*保留*/
        };
        uint32_t val;
    } miso_dlen;
    uint32_t slv_wr_status;                                 /*在从属模式下，该寄存器是主设备要写入的状态寄存器。在主模式中，该寄存器是64位地址条件下的较高32位。*/
    union {
        struct {
            uint32_t cs0_dis:        1;                     /*SPI CS0引脚启用，1:禁用CS0，0:SPI_CS0信号来自/至CS0引脚*/
            uint32_t cs1_dis:        1;                     /*SPI CS1引脚启用，1：禁用CS1，0：SPI_CS1信号来自/至CS1引脚*/
            uint32_t cs2_dis:        1;                     /*SPI CS2引脚启用，1：禁用CS2，0：SPI_CS2信号来自/至CS2引脚*/
            uint32_t reserved3:      2;                     /*保留*/
            uint32_t ck_dis:         1;                     /*1： spi clk out禁用0：spi clk-out启用*/
            uint32_t master_cs_pol:  3;                     /*在主模式中，位是spi cs线的极性，值等于spi_cs^spi_master_cs_pol。*/
            uint32_t reserved9:      2;                     /*保留*/
            uint32_t master_ck_sel:  3;                     /*在主模式下，spi-cs行被启用为spi-clk，它与spi_cs0_dis spi_cs1_dis spi_cs2_dis组合。*/
            uint32_t reserved14:    15;                     /*保留*/
            uint32_t ck_idle_edge:   1;                     /*1： 空闲时spi clk线为高0：空闲时spi-clk线为低*/
            uint32_t cs_keep_active: 1;                     /*当位置位时，spi-cs线保持低电平。*/
            uint32_t reserved31:     1;                     /*保留*/
        };
        uint32_t val;
    } pin;
    union {
        struct {
            uint32_t rd_buf_done:  1;                       /*用于在从属模式下完成读缓冲操作的中断原始位。*/
            uint32_t wr_buf_done:  1;                       /*用于在从属模式下完成写缓冲操作的中断原始位。*/
            uint32_t rd_sta_done:  1;                       /*用于在从属模式下完成读取状态操作的中断原始位。*/
            uint32_t wr_sta_done:  1;                       /*用于在从属模式下完成写入状态操作的中断原始位。*/
            uint32_t trans_done:   1;                       /*用于在主模式和从模式下完成任何操作的中断原始位。*/
            uint32_t rd_buf_inten: 1;                       /*用于在从属模式下完成读缓冲操作的中断使能位。*/
            uint32_t wr_buf_inten: 1;                       /*用于在从属模式下完成写缓冲操作的中断使能位。*/
            uint32_t rd_sta_inten: 1;                       /*在从模式下完成读状态操作的中断使能位。*/
            uint32_t wr_sta_inten: 1;                       /*用于在从属模式下完成写入状态操作的中断启用位。*/
            uint32_t trans_inten:  1;                       /*用于在主模式和从模式下完成任何操作的中断启用位。*/
            uint32_t cs_i_mode:    2;                       /*在从属模式中，该位用于同步输入spi cs信号并消除spi cs抖动。*/
            uint32_t reserved12:   5;                       /*保留*/
            uint32_t last_command: 3;                       /*在从属模式下，它是命令值。*/
            uint32_t last_state:   3;                       /*在从属模式下，这是spi状态机的状态。*/
            uint32_t trans_cnt:    4;                       /*主模式和从模式下的操作计数器。4： 读取状态*/
            uint32_t cmd_define:   1;                       /*1： 从模式命令在SPI_SLAVE3中定义。0：从模式命令固定为：1：写入状态2：写入缓冲区和3：读取缓冲区。*/
            uint32_t wr_rd_sta_en: 1;                       /*在从属模式下启用写和读状态*/
            uint32_t wr_rd_buf_en: 1;                       /*在从属模式下启用写和读缓冲区*/
            uint32_t slave_mode:   1;                       /*1： 从模式0：主模式。*/
            uint32_t sync_reset:   1;                       /*软件重置启用，重置spi时钟线cs线和数据线。*/
        };
        uint32_t val;
    } slave;
    union {
        struct {
            uint32_t rdbuf_dummy_en:  1;                    /*在从模式中，它是读缓冲操作的虚拟阶段的启用位。*/
            uint32_t wrbuf_dummy_en:  1;                    /*在从属模式中，它是写入缓冲区操作的虚拟阶段的启用位。*/
            uint32_t rdsta_dummy_en:  1;                    /*在从属模式下，它是读取状态操作的虚拟阶段的启用位。*/
            uint32_t wrsta_dummy_en:  1;                    /*在从属模式下，它是写入状态操作的虚拟阶段的启用位。*/
            uint32_t wr_addr_bitlen:  6;                    /*在从属模式下，它是写入缓冲区操作的地址长度（以位为单位）。寄存器值应为（bit_num-1）。*/
            uint32_t rd_addr_bitlen:  6;                    /*在从属模式下，它是读缓冲操作的地址长度（以位为单位）。寄存器值应为（bit_num-1）。*/
            uint32_t reserved16:      9;                    /*保留*/
            uint32_t status_readback: 1;                    /*在从属模式1中：读取SPI_SLV_WR_STATUS寄存器0：读取SPI_RD_STATUS寄存器。*/
            uint32_t status_fast_en:  1;                    /*在从属模式下，启用快速读取状态。*/
            uint32_t status_bitlen:   5;                    /*在从属模式下，它是状态位的长度。*/
        };
        uint32_t val;
    } slave1;
    union {
        struct {
            uint32_t rdsta_dummy_cyclelen: 8;               /*在从属模式下，它是读取状态操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
            uint32_t wrsta_dummy_cyclelen: 8;               /*在从属模式中，它是写入状态操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
            uint32_t rdbuf_dummy_cyclelen: 8;               /*在从属模式中，它是读缓冲操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
            uint32_t wrbuf_dummy_cyclelen: 8;               /*在从属模式下，它是写入缓冲区操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
        };
        uint32_t val;
    } slave2;
    union {
        struct {
            uint32_t rdbuf_cmd_value: 8;                    /*在从属模式下，它是读取缓冲区命令的值。*/
            uint32_t wrbuf_cmd_value: 8;                    /*在从属模式下，它是写入缓冲区命令的值。*/
            uint32_t rdsta_cmd_value: 8;                    /*在从属模式下，它是读取状态命令的值。*/
            uint32_t wrsta_cmd_value: 8;                    /*在从属模式下，它是写入状态命令的值。*/
        };
        uint32_t val;
    } slave3;
    union {
        struct {
            uint32_t bit_len:    24;                        /*在从属模式下，它是写入缓冲区操作的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved24:  8;                        /*保留*/
        };
        uint32_t val;
    } slv_wrbuf_dlen;
    union {
        struct {
            uint32_t bit_len:    24;                        /*在从属模式下，它是读取缓冲区操作的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved24:  8;                        /*保留*/
        };
        uint32_t val;
    } slv_rdbuf_dlen;
    union {
        struct {
            uint32_t req_en:        1;                      /*对于SPI0缓存访问，启用1:启用0:禁用。*/
            uint32_t usr_cmd_4byte: 1;                      /*对于具有4字节的SPI0缓存读闪存，命令1:enable 0:disable。*/
            uint32_t flash_usr_cmd: 1;                      /*对于用户定义命令1:enable0:disable的SPI0缓存读取闪存。*/
            uint32_t flash_pes_en:  1;                      /*对于SPI0，spi1在缓存读取闪存1之前发送suspend命令：enable 0：disable。*/
            uint32_t reserved4:    28;                      /*保留*/
        };
        uint32_t val;
    } cache_fctrl;
    union {
        struct {
            uint32_t reserved0:           1;                /*保留*/
            uint32_t usr_sram_dio:        1;                /*对于SPI0在spi-sram模式中，spi双I/O模式启用1：启用0：禁用*/
            uint32_t usr_sram_qio:        1;                /*对于SPI0在spi-sram模式下，spiquad I/O模式启用1：启用0：禁用*/
            uint32_t usr_wr_sram_dummy:   1;                /*对于SPI0，在spi-sram模式中，它是写入操作的虚拟阶段的启用位。*/
            uint32_t usr_rd_sram_dummy:   1;                /*对于SPI0，在spi-sram模式中，它是读取操作的虚拟阶段的启用位。*/
            uint32_t cache_sram_usr_rcmd: 1;                /*对于SPI0，在spi-sram模式下，缓存读取sram以执行用户定义命令。*/
            uint32_t sram_bytes_len:      8;                /*对于SPI0，在sram模式下，它是spi读取sram数据的字节长度。*/
            uint32_t sram_dummy_cyclelen: 8;                /*对于SPI0，在sram模式中，它是地址相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t sram_addr_bitlen:    6;                /*对于SPI0，在sram模式中，它是地址相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t cache_sram_usr_wcmd: 1;                /*对于SPI0在spi-sram模式缓存中，为用户定义命令写入sram*/
            uint32_t reserved29:          3;                /*保留*/
        };
        uint32_t val;
    } cache_sctrl;
    union {
        struct {
            uint32_t dio:       1;                          /*对于SPI0 SRAM DIO模式启用。当设置位时，将发送SRAM DIO启用命令。操作完成后，该位将被清除。*/
            uint32_t qio:       1;                          /*对于SPI0 SRAM QIO模式启用。当设置位时，将发送SRAM QIO启用命令。操作完成后，该位将被清除。*/
            uint32_t reserved2: 2;                          /*对于SPI0 SRAM写入启用。当位被设置时，SRAM写入操作将被触发。操作完成后，该位将被清除。*/
            uint32_t rst_io:    1;                          /*对于SPI0 SRAM IO模式重置启用。当位被设置时，SRAM IO模式复位操作将被触发。一旦操作完成，该位将被清除*/
            uint32_t reserved5:27;                          /*保留*/
        };
        uint32_t val;
    } sram_cmd;
    union {
        struct {
            uint32_t usr_rd_cmd_value:   16;                /*对于SPI0，当启用缓存模式时，它是SRAM命令阶段的读取命令值。*/
            uint32_t reserved16:         12;                /*保留*/
            uint32_t usr_rd_cmd_bitlen:   4;                /*对于SPI0，当启用缓存模式时，它是SRAM命令阶段的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } sram_drd_cmd;
    union {
        struct {
            uint32_t usr_wr_cmd_value: 16;                  /*对于SPI0，当启用缓存模式时，它是SRAM命令阶段的写入命令值。*/
            uint32_t reserved16:       12;                  /*保留*/
            uint32_t usr_wr_cmd_bitlen: 4;                  /*对于SPI0，当启用缓存模式时，它是SRAM命令阶段的位。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } sram_dwr_cmd;
    union {
        struct {
            uint32_t slv_rdata_bit:24;                      /*在从属模式下，它是读取数据的位长度。值为长度-1。*/
            uint32_t reserved24:    8;                      /*保留*/
        };
        uint32_t val;
    } slv_rd_bit;
    uint32_t reserved_68;
    uint32_t reserved_6c;
    uint32_t reserved_70;
    uint32_t reserved_74;
    uint32_t reserved_78;
    uint32_t reserved_7c;
    uint32_t data_buf[16];                                  /*数据缓冲器*/
    uint32_t tx_crc;                                        /*对于SPI1，256位数据的crc32值。*/
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
    union {
        struct {
            uint32_t t_pp_time: 12;                         /*页面程序延迟时间由系统时钟决定。*/
            uint32_t reserved12: 4;                         /*保留*/
            uint32_t t_pp_shift: 4;                         /*页面程序延迟时间偏移。*/
            uint32_t reserved20:11;                         /*保留*/
            uint32_t t_pp_ena:   1;                         /*页面程序延迟启用。*/
        };
        uint32_t val;
    } ext0;
    union {
        struct {
            uint32_t t_erase_time: 12;                      /*通过系统时钟擦除闪存延迟时间。*/
            uint32_t reserved12:    4;                      /*保留*/
            uint32_t t_erase_shift: 4;                      /*擦除闪存延迟时间偏移。*/
            uint32_t reserved20:   11;                      /*保留*/
            uint32_t t_erase_ena:   1;                      /*擦除闪存延迟启用。*/
        };
        uint32_t val;
    } ext1;
    union {
        struct {
            uint32_t st:         3;                         /*spi状态机的状态。*/
            uint32_t reserved3: 29;                         /*保留*/
        };
        uint32_t val;
    } ext2;
    union {
        struct {
            uint32_t int_hold_ena: 2;                       /*该寄存器用于两个SPI主机共享相同的cs时钟和数据信号。如果另一个SPI忙，则设置一个SPI的位，SPI将保持。1（3）：保持，空闲，阶段2：保持，准备，阶段。*/
            uint32_t reserved2:   30;                       /*保留*/
        };
        uint32_t val;
    } ext3;
    union {
        struct {
            uint32_t reserved0:         2;                  /*保留*/
            uint32_t in_rst:            1;                  /*该位用于在dma fsm和数据fifo指针中重置。*/
            uint32_t out_rst:           1;                  /*该位用于重置dma fsm和数据fifo指针。*/
            uint32_t ahbm_fifo_rst:     1;                  /*重置spi-dmaahb主fifo指针。*/
            uint32_t ahbm_rst:          1;                  /*重置spi-dma ahb主机。*/
            uint32_t in_loop_test:      1;                  /*设置要在链接中测试的位。*/
            uint32_t out_loop_test:     1;                  /*设置位以测试链接。*/
            uint32_t out_auto_wrback:   1;                  /*当链接为空时，自动跳转到下一个。*/
            uint32_t out_eof_mode:      1;                  /*脱离标志生成模式。1： 当dma从fifo 0中弹出所有数据时：当ahb将所有数据推送到fifo时。*/
            uint32_t outdscr_burst_en:  1;                  /*读取描述符在读取内存数据时使用突发模式。*/
            uint32_t indscr_burst_en:   1;                  /*当将数据写入存储器时，读描述符使用突发模式。*/
            uint32_t out_data_burst_en: 1;                  /*spidma以突发模式从存储器读取数据。*/
            uint32_t reserved13:        1;                  /*保留*/
            uint32_t dma_rx_stop:       1;                  /*当处于continue tx/rx模式时，spidma读取数据停止。*/
            uint32_t dma_tx_stop:       1;                  /*当处于continue tx/rx模式时，spidma写入数据停止。*/
            uint32_t dma_continue:      1;                  /*spi-dma继续tx/rx数据。*/
            uint32_t reserved17:       15;                  /*保留*/
        };
        uint32_t val;
    } dma_conf;
    union {
        struct {
            uint32_t addr:        20;                       /*第一个outlink描述符的地址。*/
            uint32_t reserved20:   8;                       /*保留*/
            uint32_t stop:         1;                       /*将位设置为停止以使用outlink描述符。*/
            uint32_t start:        1;                       /*设置位以开始使用outlink描述符。*/
            uint32_t restart:      1;                       /*设置要装入新的outlink描述符的位。*/
            uint32_t reserved31:   1;                       /*保留*/
        };
        uint32_t val;
    } dma_out_link;
    union {
        struct {
            uint32_t addr:       20;                        /*第一个内联描述符的地址。*/
            uint32_t auto_ret:    1;                        /*当设置位时，内联描述符返回到下一个描述符，而数据包错误*/
            uint32_t reserved21:  7;                        /*保留*/
            uint32_t stop:        1;                        /*将位设置为stop以使用内联描述符。*/
            uint32_t start:       1;                        /*设置开始使用内联描述符的位。*/
            uint32_t restart:     1;                        /*设置要装入新内联描述符的位。*/
            uint32_t reserved31:  1;                        /*保留*/
        };
        uint32_t val;
    } dma_in_link;
    union {
        struct {
            uint32_t rx_en:      1;                         /*spi-dma读取数据状态位。*/
            uint32_t tx_en:      1;                         /*spi-dma写入数据状态位。*/
            uint32_t reserved2: 30;                         /*spidma从内存计数中读取数据。*/
        };
        uint32_t val;
    } dma_status;
    union {
        struct {
            uint32_t inlink_dscr_empty:  1;                 /*缺少足够内联描述符的启用位。*/
            uint32_t outlink_dscr_error: 1;                 /*outlink描述符错误的启用位。*/
            uint32_t inlink_dscr_error:  1;                 /*内联描述符错误的启用位。*/
            uint32_t in_done:            1;                 /*用于完成内联描述符使用的启用位。*/
            uint32_t in_err_eof:         1;                 /*接收错误的启用位。*/
            uint32_t in_suc_eof:         1;                 /*用于完成从主机接收所有数据包的启用位。*/
            uint32_t out_done:           1;                 /*用于完成outlink描述符使用的启用位。*/
            uint32_t out_eof:            1;                 /*向主机发送数据包的启用位已完成。*/
            uint32_t out_total_eof:      1;                 /*用于向主机发送所有数据包的启用位已完成。*/
            uint32_t reserved9:         23;                 /*保留*/
        };
        uint32_t val;
    } dma_int_ena;
    union {
        struct {
            uint32_t inlink_dscr_empty:  1;                 /*缺少足够内联描述符的原始位。*/
            uint32_t outlink_dscr_error: 1;                 /*outlink描述符错误的原始位。*/
            uint32_t inlink_dscr_error:  1;                 /*内联描述符错误的原始位。*/
            uint32_t in_done:            1;                 /*用于完成内联描述符使用的原始位。*/
            uint32_t in_err_eof:         1;                 /*接收错误的原始位。*/
            uint32_t in_suc_eof:         1;                 /*用于完成从主机接收所有数据包的原始位。*/
            uint32_t out_done:           1;                 /*用于完成outlink描述符使用的原始位。*/
            uint32_t out_eof:            1;                 /*向主机发送数据包的原始位已完成。*/
            uint32_t out_total_eof:      1;                 /*将所有数据包发送到主机的原始位已完成。*/
            uint32_t reserved9:         23;                 /*保留*/
        };
        uint32_t val;
    } dma_int_raw;
    union {
        struct {
            uint32_t inlink_dscr_empty:  1;                  /*缺少足够内联描述符的状态位。*/
            uint32_t outlink_dscr_error: 1;                  /*outlink描述符错误的状态位。*/
            uint32_t inlink_dscr_error:  1;                  /*内联描述符错误的状态位。*/
            uint32_t in_done:            1;                  /*用于完成内联描述符使用的状态位。*/
            uint32_t in_err_eof:         1;                  /*接收错误的状态位。*/
            uint32_t in_suc_eof:         1;                  /*完成从主机接收所有数据包的状态位。*/
            uint32_t out_done:           1;                  /*用于完成outlink描述符使用的状态位。*/
            uint32_t out_eof:            1;                  /*向主机发送数据包的状态位已完成。*/
            uint32_t out_total_eof:      1;                  /*向主机发送所有数据包的状态位已完成。*/
            uint32_t reserved9:         23;                  /*保留*/
        };
        uint32_t val;
    } dma_int_st;
    union {
        struct {
            uint32_t inlink_dscr_empty:  1;                 /*缺少足够的内联描述符的明确位。*/
            uint32_t outlink_dscr_error: 1;                 /*outlink描述符错误的清除位。*/
            uint32_t inlink_dscr_error:  1;                 /*内联描述符错误的清除位。*/
            uint32_t in_done:            1;                 /*用于完成内联描述符使用的清除位。*/
            uint32_t in_err_eof:         1;                 /*接收错误的清除位。*/
            uint32_t in_suc_eof:         1;                 /*用于完成从主机接收所有数据包的清除位。*/
            uint32_t out_done:           1;                 /*用于完成outlink描述符使用的清除位。*/
            uint32_t out_eof:            1;                 /*向主机发送数据包的清除位已完成。*/
            uint32_t out_total_eof:      1;                 /*将所有数据包发送到主机的清除位已完成。*/
            uint32_t reserved9:         23;                 /*保留*/
        };
        uint32_t val;
    } dma_int_clr;
    uint32_t dma_in_err_eof_des_addr;                       /*spidma产生接收错误时的内联描述符地址。*/
    uint32_t dma_in_suc_eof_des_addr;                       /*spi-dma生成from_suc_eof时的最后一个内联描述符地址。*/
    uint32_t dma_inlink_dscr;                               /*当前在描述符指针中的内容。*/
    uint32_t dma_inlink_dscr_bf0;                           /*描述符指针中next的内容。*/
    uint32_t dma_inlink_dscr_bf1;                           /*描述符中当前数据缓冲区指针的内容。*/
    uint32_t dma_out_eof_bfr_des_addr;                      /*相对于产生eof的outlink描述符的缓冲区地址。*/
    uint32_t dma_out_eof_des_addr;                          /*spi-dma生成to_eof时的最后一个outlink描述符地址。*/
    uint32_t dma_outlink_dscr;                              /*当前输出描述符指针的内容。*/
    uint32_t dma_outlink_dscr_bf0;                          /*下一个输出描述符指针的内容。*/
    uint32_t dma_outlink_dscr_bf1;                          /*当前输出描述符数据缓冲区指针的内容。*/
    uint32_t dma_rx_status;                                 /*spidma从内存状态读取数据。*/
    uint32_t dma_tx_status;                                 /*spidma将数据写入内存状态。*/
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
            uint32_t date:      28;                         /*SPI寄存器版本。*/
            uint32_t reserved28: 4;                         /*保留*/
        };
        uint32_t val;
    } date;
} spi_dev_t;
extern spi_dev_t SPI0;                                      /* SPI0 IS FOR INTERNAL USE*/
extern spi_dev_t SPI1;
extern spi_dev_t SPI2;
extern spi_dev_t SPI3;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_SPI_STRUCT_H_ */

