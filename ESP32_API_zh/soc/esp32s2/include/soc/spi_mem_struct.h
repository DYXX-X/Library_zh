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
#ifndef _SOC_SPI_MEM_STRUCT_H_
#define _SOC_SPI_MEM_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct spi_mem_dev_s {
    union {
        struct {
            uint32_t reserved0: 17;                             /*保留*/
            uint32_t flash_pe:   1;                             /*在用户模式下，设置为指示将触发编程/擦除操作。该位与spi_mem_usr位组合。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t usr:        1;                             /*用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_hpm:  1;                             /*将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_res:  1;                             /*此位与reg_resandres位结合使用，可将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_dp:   1;                             /*将闪存驱动器关闭。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_ce:   1;                             /*芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_be:   1;                             /*块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_se:   1;                             /*扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pp:   1;                             /*页面编程启用（要编程的数据为1字节~256字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
            uint32_t flash_wrsr: 1;                             /*写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdsr: 1;                             /*读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdid: 1;                             /*读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wrdi: 1;                             /*写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wren: 1;                             /*写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_read: 1;                             /*读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
        };
        uint32_t val;
    } cmd;
    uint32_t addr;                                              /*在用户模式下，它是内存地址。除此之外，位0位23是存储器地址，位24位31是传输的字节长度。*/
    union {
        struct {
            uint32_t reserved0:   3;                            /*保留*/
            uint32_t fdummy_out:  1;                            /*在虚设阶段，spi的信号电平由spi控制器输出。*/
            uint32_t fdout_oct:   1;                            /*在写入数据阶段1期间施加8个信号：启用0：禁用*/
            uint32_t fdin_oct:    1;                            /*在读取数据阶段1期间施加8个信号：启用0：禁用*/
            uint32_t faddr_oct:   1;                            /*在地址阶段1期间施加8个信号：启用0：禁用*/
            uint32_t fcmd_dual:   1;                            /*在命令阶段1施加2个信号：启用0：禁用*/
            uint32_t fcmd_quad:   1;                            /*在命令阶段1施加4个信号：启用0：禁用*/
            uint32_t fcmd_oct:    1;                            /*在命令阶段1施加8个信号：启用0：禁用*/
            uint32_t fcs_crc_en:  1;                            /*对于SPI1，在将加密数据写入闪存之前初始化crc32模块。低激活。*/
            uint32_t tx_crc_en:   1;                            /*对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0:禁用*/
            uint32_t reserved12:  1;                            /*保留*/
            uint32_t fastrd_mode: 1;                            /*此位启用位：spi_mem_fread_qio spi_mem_fread_dio spi_mem-fread_qout和spi_mem.fread_dout。1： 启用0：禁用。*/
            uint32_t fread_dual:  1;                            /*在读取操作中，读取数据阶段施加2个信号。1： 启用0：禁用。*/
            uint32_t resandres:   1;                            /*设备ID被读出到SPI_MEM_RD_STATUS寄存器，该位与SPI_MEM_flash_res位组合。1： 启用0：禁用。*/
            uint32_t reserved16:  2;                            /*保留*/
            uint32_t q_pol:       1;                            /*该位用于设置MISO线极性1：高0低*/
            uint32_t d_pol:       1;                            /*该位用于设置MOSI线极性1：高0低*/
            uint32_t fread_quad:  1;                            /*在读取操作中，读取数据阶段施加4个信号。1： 启用0：禁用。*/
            uint32_t wp:          1;                            /*SPI空闲时的写保护信号输出。1： 输出高0：输出低。*/
            uint32_t wrsr_2b:     1;                            /*当状态寄存器被设置时，两个字节的数据将被写入状态寄存器。1： 启用0：禁用。*/
            uint32_t fread_dio:   1;                            /*在读操作中，地址阶段和读数据阶段施加2个信号。1： 启用0：禁用。*/
            uint32_t fread_qio:   1;                            /*在读操作中，地址阶段和读数据阶段施加4个信号。1： 启用0：禁用。*/
            uint32_t reserved25:  7;                            /*保留*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t clk_mode:        2;                        /*SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。*/
            uint32_t cs_hold_dly_res:12;                        /*当spi时钟启用从待机模式恢复闪存时，恢复闪存的延迟周期。*/
            uint32_t cs_hold_dly:    12;                        /*SPI fsm被SPI时钟周期延迟到空闲。*/
            uint32_t cs_dly_num:      2;                        /*spi_mem_cs信号被系统时钟周期延迟*/
            uint32_t cs_dly_mode:     2;                        /*cs信号延迟了系统时钟周期0：无延迟输出1：输出clk_apb的偏倚2，输出clk_apb的负边3：输出clk _160的偏倚4，输出clk _660的负边5：输出spi_clk*/
            uint32_t reserved30:      1;
            uint32_t cs_dly_edge:     1;                        /*该位用于选择spi时钟边沿以修改CS线定时。*/
        };
        uint32_t val;
    } ctrl1;
    union {
        struct {
            uint32_t cs_setup_time:13;                          /*通过spi时钟的准备阶段的（周期-1）该位与spi_mem_cs_setup位组合。*/
            uint32_t cs_hold_time: 13;                          /*Spi cs信号被Spi时钟延迟至无效，该位与Spi_mem_cs_hold位组合。*/
            uint32_t reserved26:    5;                          /*保留*/
            uint32_t sync_reset:    1;                          /*FSM将被重置。*/
        };
        uint32_t val;
    } ctrl2;
    union {
        struct {
            uint32_t clkcnt_l:       8;                         /*在主模式下，它必须等于spi_mem_clkcnt_N。*/
            uint32_t clkcnt_h:       8;                         /*在主模式下，必须为floor（（spi_mem_clkcnt_N+1）/2-1）。*/
            uint32_t clkcnt_n:       8;                         /*在主模式中，它是spi_mem_clk的除法器。因此spi_mem_clk频率为系统/（spi_mem_clkcnt_N+1）*/
            uint32_t reserved24:     7;                         /*在主模式下，它是spi_mem_clk的预除法器。*/
            uint32_t clk_equ_sysclk: 1;                         /*保留*/
        };
        uint32_t val;
    } clock;
    union {
        struct {
            uint32_t reserved0:         6;                      /*保留*/
            uint32_t cs_hold:           1;                      /*当spi处于完成阶段时，spi cs保持较低。1： 启用0：禁用。*/
            uint32_t cs_setup:          1;                      /*当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。*/
            uint32_t reserved8:         1;                      /*保留*/
            uint32_t ck_out_edge:       1;                      /*该位与spi_mem_msi_delaymode位组合以设置mosi信号延迟模式。*/
            uint32_t reserved10:        2;                      /*保留*/
            uint32_t fwrite_dual:       1;                      /*在写入操作中，读取数据阶段应用2个信号*/
            uint32_t fwrite_quad:       1;                      /*在写入操作中，读取数据阶段应用4个信号*/
            uint32_t fwrite_dio:        1;                      /*在写操作中，地址阶段和读数据阶段施加2个信号。*/
            uint32_t fwrite_qio:        1;                      /*在写操作中，地址阶段和读数据阶段施加4个信号。*/
            uint32_t reserved16:        8;                      /*保留*/
            uint32_t usr_miso_highpart: 1;                      /*读取数据阶段仅访问缓冲区的高部分spi_mem_w8～spi_mem-w15。1：启用0：禁用。*/
            uint32_t usr_mosi_highpart: 1;                      /*写入数据阶段仅访问缓冲区的高部分spi_mem_w8～spi_mem-w15。1：启用0：禁用。*/
            uint32_t usr_dummy_idle:    1;                      /*当位被启用时，spi时钟在伪相位被禁用。*/
            uint32_t usr_mosi:          1;                      /*此位启用操作的写入数据阶段。*/
            uint32_t usr_miso:          1;                      /*此位启用操作的读取数据阶段。*/
            uint32_t usr_dummy:         1;                      /*此位启用操作的虚拟阶段。*/
            uint32_t usr_addr:          1;                      /*此位启用操作的地址阶段。*/
            uint32_t usr_command:       1;                      /*此位启用操作的命令阶段。*/
        };
        uint32_t val;
    } user;
    union {
        struct {
            uint32_t usr_dummy_cyclelen: 8;                     /*伪相位的spi_mem_clk周期长度。寄存器值应为（cycle_num-1）。*/
            uint32_t reserved8:         18;                     /*保留*/
            uint32_t usr_addr_bitlen:    6;                     /*地址相位的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } user1;
    union {
        struct {
            uint32_t usr_command_value: 16;                     /*命令的值。*/
            uint32_t reserved16:        12;                     /*保留*/
            uint32_t usr_command_bitlen: 4;                     /*命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）*/
        };
        uint32_t val;
    } user2;
    union {
        struct {
            uint32_t usr_mosi_bit_len:11;                       /*写入数据的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved11:      21;                       /*保留*/
        };
        uint32_t val;
    } mosi_dlen;
    union {
        struct {
            uint32_t usr_miso_bit_len:11;                       /*读取数据的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved11:      21;                       /*保留*/
        };
        uint32_t val;
    } miso_dlen;
    union {
        struct {
            uint32_t status:    16;                             /*设置spi_mem_flash_rdsr位和spi_mem_flash_res位时存储该值。*/
            uint32_t wb_mode:    8;                             /*闪存快速读取模式中的模式位与spi_mem_fastrd_Mode位组合。*/
            uint32_t reserved24: 8;                             /*保留*/
        };
        uint32_t val;
    } rd_status;
    uint32_t ext_addr;                                          /*在64位地址模式下，寄存器是较高的32位。*/
    union {
        struct {
            uint32_t cs0_dis:           1;                      /*SPI CS0引脚启用1：禁用CS0 0：SPI_mem_CS0信号来自/至CS0引脚*/
            uint32_t cs1_dis:           1;                      /*SPI CS1引脚启用1：禁用CS1 0：SPI_mem_CS1信号来自/至CS1引脚*/
            uint32_t reserved2:         1;                      /*保留*/
            uint32_t trans_end:         1;                      /*该位用于指示传输已完成。*/
            uint32_t trans_end_en:      1;                      /*该位用于启用SPI传输中断。*/
            uint32_t cs_pol:            2;                      /*在主模式中，位是spi cs线的极性，值等于spi_mem_cs^spi_mem_master_cs_pol。*/
            uint32_t fsub_pin:          1;                      /*对于SPI0，闪存连接到SUBPINs。*/
            uint32_t ssub_pin:          1;                      /*对于SPI0，sram连接到SUBPIN。*/
            uint32_t ck_idle_edge:      1;                      /*1： 空闲时spi clk线为高0：空闲时spi-clk线为低*/
            uint32_t cs_keep_active:    1;                      /*当位置位时，spi-cs线保持低电平。*/
            uint32_t auto_per:          1;                      /*保留*/
            uint32_t reserved12:       20;                      /*保留*/
        };
        uint32_t val;
    } misc;
    uint32_t tx_crc;                                            /*对于SPI1，crc32的值。*/
    union {
        struct {
            uint32_t req_en:              1;                    /*对于SPI0缓存访问，启用1:启用0:禁用。*/
            uint32_t usr_cmd_4byte:       1;                    /*对于具有4字节的SPI0缓存读闪存，命令1:enable 0:disable。*/
            uint32_t flash_usr_cmd:       1;                    /*对于用户定义命令1:enable0:disable的SPI0缓存读取闪存。*/
            uint32_t fdin_dual:           1;                    /*对于SPI0闪存，相位应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
            uint32_t fdout_dual:          1;                    /*对于SPI0闪存双相，施加2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
            uint32_t faddr_dual:          1;                    /*对于SPI0闪存地址阶段，应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
            uint32_t fdin_quad:           1;                    /*对于SPI0闪存，相位应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
            uint32_t fdout_quad:          1;                    /*对于SPI0闪存双相，施加4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
            uint32_t faddr_quad:          1;                    /*对于SPI0闪存地址阶段，应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
            uint32_t reserved9:          23;                    /*保留*/
        };
        uint32_t val;
    } cache_fctrl;
    union {
        struct {
            uint32_t usr_scmd_4byte:       1;                   /*对于SPI0，在spi-sram模式下，使用4字节命令1：enable 0：disable读取闪存。*/
            uint32_t usr_sram_dio:         1;                   /*对于SPI0在spi-sram模式中，spi双I/O模式启用1：启用0：禁用*/
            uint32_t usr_sram_qio:         1;                   /*对于SPI0在spi-sram模式下，spiquad I/O模式启用1：启用0：禁用*/
            uint32_t usr_wr_sram_dummy:    1;                   /*对于SPI0，在spi-sram模式中，它是写入操作的虚拟阶段的启用位。*/
            uint32_t usr_rd_sram_dummy:    1;                   /*对于SPI0，在spi-sram模式中，它是读取操作的虚拟阶段的启用位。*/
            uint32_t cache_sram_usr_rcmd:  1;                   /*对于SPI0，在spi-sram模式下，缓存读取sram以执行用户定义命令。*/
            uint32_t sram_rdummy_cyclelen: 8;                   /*对于SPI0，在sram模式中，它是读取伪相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t sram_addr_bitlen:     6;                   /*对于SPI0，在sram模式中，它是地址相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t cache_sram_usr_wcmd:  1;                   /*对于SPI0在spi-sram模式缓存中，为用户定义命令写入sram*/
            uint32_t sram_oct:             1;                   /*保留*/
            uint32_t sram_wdummy_cyclelen: 8;                   /*对于SPI0，在sram模式中，它是写入伪相位的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
            uint32_t reserved30:           2;                   /*保留*/
        };
        uint32_t val;
    } cache_sctrl;
    union {
        struct {
            uint32_t sclk_mode:  2;                             /*SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。*/
            uint32_t swb_mode:   8;                             /*psram快速读取模式中的模式位与spi_mem_fastrd_Mode位组合。*/
            uint32_t sdin_dual:  1;                             /*对于SPI0 sram din相位应用2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
            uint32_t sdout_dual: 1;                             /*对于SPI0 sram双相位，施加2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
            uint32_t saddr_dual: 1;                             /*对于SPI0 sram地址相位，施加2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
            uint32_t scmd_dual:  1;                             /*对于SPI0 sram cmd相位，施加2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
            uint32_t sdin_quad:  1;                             /*对于SPI0 sram din相位，施加4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
            uint32_t sdout_quad: 1;                             /*对于SPI0，sram双相位应用4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
            uint32_t saddr_quad: 1;                             /*对于SPI0 sram地址相位，施加4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
            uint32_t scmd_quad:  1;                             /*对于SPI0 sram cmd相位，施加4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
            uint32_t sdin_oct:   1;                             /*对于SPI0 sram，相位施加8个信号。1： 启用0：禁用。*/
            uint32_t sdout_oct:  1;                             /*对于SPI0，sram双相位施加8个信号。1： 启用0：禁用。*/
            uint32_t saddr_oct:  1;                             /*对于SPI0 sram地址相位，施加4个信号。1： 启用0：禁用。*/
            uint32_t scmd_oct:   1;                             /*对于SPI0 sram cmd相位，施加8个信号。1： 启用0：禁用。*/
            uint32_t sdummy_out: 1;                             /*在虚设阶段，spi的信号电平由spi控制器输出。*/
            uint32_t reserved23: 9;                             /*保留*/
        };
        uint32_t val;
    } sram_cmd;
    union {
        struct {
            uint32_t usr_rd_cmd_value:            16;           /*对于SPI0，当启用缓存模式时，它是sram命令阶段的读取命令值。*/
            uint32_t reserved16:                  12;           /*保留*/
            uint32_t usr_rd_cmd_bitlen:            4;           /*对于SPI0，当启用缓存模式时，它是sram命令阶段的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } sram_drd_cmd;
    union {
        struct {
            uint32_t usr_wr_cmd_value:            16;           /*对于SPI0，当启用缓存模式时，它是sram命令阶段的写入命令值。*/
            uint32_t reserved16:                  12;           /*保留*/
            uint32_t usr_wr_cmd_bitlen:            4;           /*对于SPI0，当启用缓存模式时，它是sram命令阶段的位。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } sram_dwr_cmd;
    union {
        struct {
            uint32_t cnt_l:           8;                        /*对于SPI0 sram接口，它必须等于spi_mem_clkcnt_N。*/
            uint32_t cnt_h:           8;                        /*对于SPI0 sram接口，它必须是floor（（spi_mem_clkcnt_N+1）/2-1）。*/
            uint32_t cnt_n:           8;                        /*对于SPI0 sram接口，它是spi_mem_clk的除法器。因此spi_mem_clk频率为系统/（spi_mem_clkcnt_N+1）*/
            uint32_t reserved24:      7;                        /*保留*/
            uint32_t equ_sysclk:      1;                        /*对于SPI0 sram接口1:spi_mem_clk等于系统0：spi_mem_clk与系统时钟分开。*/
        };
        uint32_t val;
    } sram_clk;
    union {
        struct {
            uint32_t st:         3;                             /*spi状态机的状态。0：空闲状态1：准备状态2：发送命令状态3：发送数据状态4：红色数据状态5：写入数据状态6：等待状态7：完成状态。*/
            uint32_t reserved3: 29;                             /*保留*/
        };
        uint32_t val;
    } fsm;
    uint32_t data_buf[16];                                                /*数据缓冲器*/
    union {
        struct {
            uint32_t waiti_en:             1;                   /*编程闪存或擦除闪存时自动等待闪存空闲操作。1： 启用0：禁用。*/
            uint32_t waiti_dummy:          1;                   /*自动等待闪存空闲时的虚拟阶段启用*/
            uint32_t waiti_cmd:            8;                   /*自动等待空闲的命令*/
            uint32_t waiti_dummy_cyclelen: 8;                   /*自动等待闪存空闲时的虚拟周期长度*/
            uint32_t reserved18:          14;                   /*保留*/
        };
        uint32_t val;
    } flash_waiti_ctrl;
    union {
        struct {
            uint32_t flash_per:  1;                             /*当该位被设置时，将触发程序擦除恢复位程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pes:  1;                             /*当位被设置时，将触发程序擦除暂停位程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t reserved2: 30;
        };
        uint32_t val;
    } flash_sus_cmd;
    union {
        struct {
            uint32_t flash_pes_en:      1;                      /*自动挂起启用*/
            uint32_t flash_per_command: 8;                      /*编程/擦除恢复命令。*/
            uint32_t flash_pes_command: 8;                      /*编程/擦除暂停命令。*/
            uint32_t reserved17:       15;
        };
        uint32_t val;
    } flash_sus_ctrl;
    union {
        struct {
            uint32_t flash_sus:  1;                             /*闪存挂起的状态仅在SPI1中使用。*/
            uint32_t reserved1: 31;
        };
        uint32_t val;
    } sus_status;
    union {
        struct {
            uint32_t timing_clk_ena:       1;                   /*该位用于启用所有读取操作的定时调整时钟。*/
            uint32_t timing_cali:          1;                   /*该位用于启用所有读取操作的定时自动校准。*/
            uint32_t extra_dummy_cyclelen: 3;                   /*为spi时钟校准添加额外的伪spi时钟周期长度。*/
            uint32_t reserved5:           27;
        };
        uint32_t val;
    } timing_cali;
    union {
        struct {
            uint32_t din0_mode:  2;                             /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din1_mode:  2;                             /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din2_mode:  2;                             /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din3_mode:  2;                             /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din4_mode:  2;                             /*输入信号被系统时钟周期0延迟：输入而不延迟1：输入具有clk_apb的偏旁2输入具有clk _apb的负边3：输入具有spiclk*/
            uint32_t din5_mode:  2;                             /*输入信号被系统时钟周期0延迟：输入，无延迟1：输入，带clk_apb的偏旁2输入，带clk_apb负边3输入，带spiclk*/
            uint32_t din6_mode:  2;                             /*输入信号被延迟系统时钟周期0：输入，无延迟1：输入，带clk_apb的偏旁2输入，带clk_apb负边3输入，带spiclk*/
            uint32_t din7_mode:  2;                             /*输入信号被系统时钟周期0延迟：输入而不延迟1：输入具有clk_apb的偏旁2输入具有clk _apb的负边3：输入具有spiclk*/
            uint32_t dins_mode:  2;                             /*输入信号被系统时钟周期0延迟：输入而不延迟1：输入具有clk_apb的偏旁2输入具有clk _apb的负边3：输入具有spiclk*/
            uint32_t reserved18:14;                             /*保留*/
        };
        uint32_t val;
    } din_mode;
    union {
        struct {
            uint32_t din0_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din1_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din2_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din3_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din4_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din5_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din6_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din7_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dins_num:   3;                             /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t reserved27: 5;                             /*保留*/
        };
        uint32_t val;
    } din_num;
    union {
        struct {
            uint32_t dout0_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout1_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout2_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout3_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout4_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏旁输出2，带clk.apb的负边输出3：带spiclk的输出*/
            uint32_t dout5_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏旁输出2，带clk.apb的负边输出3：带spiclk的输出*/
            uint32_t dout6_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏旁输出2，带clk.apb的负边输出3：带spiclk的输出*/
            uint32_t dout7_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏旁输出2，带clk.apb的负边输出3：带spiclk的输出*/
            uint32_t douts_mode: 2;                             /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏旁输出2，带clk.apb的负边输出3：带spiclk的输出*/
            uint32_t reserved18:14;                             /*保留*/
        };
        uint32_t val;
    } dout_mode;
    union {
        struct {
            uint32_t dout0_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout1_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout2_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout3_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout4_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout5_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout6_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t dout7_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t douts_num:  2;                             /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t reserved18:14;                             /*保留*/
        };
        uint32_t val;
    } dout_num;
    union {
        struct {
            uint32_t spi_smem_timing_clk_ena:       1;          /*对于sram，该位用于启用所有读取操作的定时调整时钟。*/
            uint32_t spi_smem_timing_cali:          1;          /*对于sram，该位用于启用所有读取操作的定时自动校准。*/
            uint32_t spi_smem_extra_dummy_cyclelen: 3;          /*对于sram，为spi时钟校准添加额外的伪spi时钟周期长度。*/
            uint32_t reserved5:                    27;
        };
        uint32_t val;
    } spi_smem_timing_cali;
    union {
        struct {
            uint32_t spi_smem_din0_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din1_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din2_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din3_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din4_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din5_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din6_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_din7_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t spi_smem_dins_mode: 2;                     /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t reserved18:        14;                     /*保留*/
        };
        uint32_t val;
    } spi_smem_din_mode;
    union {
        struct {
            uint32_t spi_smem_din0_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din1_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din2_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din3_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din4_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din5_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din6_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_din7_num: 3;                      /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_dins_num: 3;                      /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t reserved27:        5;                      /*保留*/
        };
        uint32_t val;
    } spi_smem_din_num;
    union {
        struct {
            uint32_t spi_smem_dout0_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout1_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout2_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout3_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout4_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout5_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout6_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout7_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_douts_mode: 2;                    /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t reserved18:         14;                    /*保留*/
        };
        uint32_t val;
    } spi_smem_dout_mode;
    union {
        struct {
            uint32_t spi_smem_dout0_num: 2;                     /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_dout1_num: 2;                     /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_dout2_num: 2;                     /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_dout3_num: 2;                     /*输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t spi_smem_dout4_num: 2;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout5_num: 2;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout6_num: 2;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_dout7_num: 2;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t spi_smem_douts_num: 2;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t reserved18:        14;                     /*保留*/
        };
        uint32_t val;
    } spi_smem_dout_num;
    union {
        struct {
            uint32_t spi_smem_cs_setup:      1;                 /*对于spi0，当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。*/
            uint32_t spi_smem_cs_hold:       1;                 /*对于spi0，当spi处于完成阶段时，spi cs保持低。1： 启用0：禁用。*/
            uint32_t spi_smem_cs_setup_time:13;                 /*对于spi时钟准备阶段的spi0（周期-1），该位与spi_mem_cs_setup位组合。*/
            uint32_t spi_smem_cs_hold_time: 13;                 /*对于spi0，spi-cs信号被spi时钟延迟到无效，该位与spi_mem_cs_hold位组合。*/
            uint32_t reserved28:             4;
        };
        uint32_t val;
    } spi_smem_ac;
    union {
        struct {
            uint32_t spi_fmem_ddr_en:            1;             /*1： 在ddr模式中0在sdr模式中*/
            uint32_t spi_fmem_var_dummy:         1;             /*设置位以启用spi-ddr模式下的可变虚拟周期。*/
            uint32_t spi_fmem_ddr_rdat_swp:      1;             /*设置位以重新排序spi-ddr模式下单词的rx数据。*/
            uint32_t spi_fmem_ddr_wdat_swp:      1;             /*设置位以重新排序spi-ddr模式下单词的tx数据。*/
            uint32_t spi_fmem_ddr_cmd_dis:       1;             /*当ddr模式时，该位用于在命令阶段禁用双边缘。*/
            uint32_t spi_fmem_outminbytelen:     8;             /*这是熊猫设备中的最小输出数据长度。*/
            uint32_t spi_fmem_usr_ddr_dqs_thd:   8;             /*基于SPI时钟从存储器发出的数据选通的延迟数。*/
            uint32_t spi_fmem_ddr_dqs_loop:      1;             /*数据选通由SPI产生。*/
            uint32_t spi_fmem_ddr_dqs_loop_mode: 2;             /*这些位与用于在ddr模式中选择数据选通产生模式的位spi_fmem_ddr_fdqs循环相组合。*/
            uint32_t reserved24:                 8;             /*保留*/
        };
        uint32_t val;
    } ddr;
    union {
        struct {
            uint32_t spi_smem_ddr_en:            1;             /*1： 在ddr模式中0在sdr模式中*/
            uint32_t spi_smem_var_dummy:         1;             /*设置位以启用spi-ddr模式下的可变虚拟周期。*/
            uint32_t spi_smem_ddr_rdat_swp:      1;             /*设置位以重新排序spi-ddr模式下单词的rx数据。*/
            uint32_t spi_smem_ddr_wdat_swp:      1;             /*设置位以重新排序spi-ddr模式下单词的tx数据。*/
            uint32_t spi_smem_ddr_cmd_dis:       1;             /*当ddr模式时，该位用于在命令阶段禁用双边缘。*/
            uint32_t spi_smem_outminbytelen:     8;             /*它是ddr-psram中的最小输出数据长度。*/
            uint32_t spi_smem_usr_ddr_dqs_thd:   8;             /*基于SPI时钟从存储器发出的数据选通的延迟数。*/
            uint32_t spi_smem_ddr_dqs_loop:      1;             /*数据选通由SPI产生。*/
            uint32_t spi_smem_ddr_dqs_loop_mode: 2;             /*这些比特与用于在ddr模式中选择数据选通产生模式的比特spimem_ddr_fdqs循环相结合。*/
            uint32_t reserved24:                 8;             /*保留*/
        };
        uint32_t val;
    } spi_smem_ddr;
    union {
        struct {
            uint32_t clk_en:     1;                             /*寄存器时钟门启用信号。1： 启用。0：禁用。*/
            uint32_t reserved1: 31;                             /*保留*/
        };
        uint32_t val;
    } clock_gate;
    union {
        struct {
            uint32_t spi01_clk_sel: 2;                          /*当数字系统时钟选择PLL时钟且PLL时钟的频率为480MHz时，reg_spi01_clk_sel:0:SPI0/1模块时钟（clk）的值为80MHz。1： SPI0/1模块时钟（clk）为120MHz。2： SPI0/1模块时钟（clk）160MHz。3： 未使用。当数字系统时钟选择PLL时钟且PLL时钟的频率为320MHz时，reg_spi01_clk_sel:0:SPI0/1模块时钟（clk）的值为80MHz。1： SPI0/1模块时钟（clk）为80MHz。2： SPI0/1模块时钟（clk）160MHz。3： 未使用。*/
            uint32_t reserved2:    30;                          /*保留*/
        };
        uint32_t val;
    } spi_core_clk_sel;
    uint32_t reserved_e4;
    uint32_t reserved_e8;
    uint32_t reserved_ec;
    uint32_t reserved_f0;
    uint32_t reserved_f4;
    uint32_t reserved_f8;
    uint32_t reserved_fc;
    uint32_t reserved_100;
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
            uint32_t date:      28;                             /*SPI寄存器版本。*/
            uint32_t reserved28: 4;                             /*保留*/
        };
        uint32_t val;
    } date;
} spi_mem_dev_t;
_Static_assert(sizeof(spi_mem_dev_t) == 0x400, "invalid spi_mem_dev_t size");
extern spi_mem_dev_t SPIMEM0;
extern spi_mem_dev_t SPIMEM1;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_SPI_MEM_STRUCT_H_ */

