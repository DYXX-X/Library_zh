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
#ifndef _SOC_SPI_MEM_STRUCT_H_
#define _SOC_SPI_MEM_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct spi_mem_dev_s {
    union {
        struct {
            uint32_t mst_st:         4;                 /*SPI1主FSM的当前状态。*/
            uint32_t st:             4;                 /*SPI1从FSM的当前状态：mspi_st。0：空闲状态1：准备状态2：发送命令状态3：发送地址状态4：等待状态5：读取数据状态6：写入数据状态7：完成状态8：读取数据结束状态。*/
            uint32_t reserved8:      9;                 /*保留*/
            uint32_t flash_pe:       1;                 /*在用户模式下，设置为指示将触发编程/擦除操作。该位与spi_mem_usr位组合。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t usr:            1;                 /*用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_hpm:      1;                 /*将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_res:      1;                 /*此位与reg_resandres位结合使用，可将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_dp:       1;                 /*将闪存驱动器关闭。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_ce:       1;                 /*芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_be:       1;                 /*块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_se:       1;                 /*扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pp:       1;                 /*页面编程启用（要编程的数据为1字节~256字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
            uint32_t flash_wrsr:     1;                 /*写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdsr:     1;                 /*读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdid:     1;                 /*读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wrdi:     1;                 /*写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wren:     1;                 /*写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_read:     1;                 /*读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
        };
        uint32_t val;
    } cmd;
    uint32_t addr;                                      /*SPI1地址寄存器*/
    union {
        struct {
            uint32_t reserved0:       3;                /*保留*/
            uint32_t fdummy_out:      1;                /*在虚设阶段，spi的信号电平由spi控制器输出。*/
            uint32_t reserved4:       3;                /*保留*/
            uint32_t fcmd_dual:       1;                /*在命令阶段1施加2个信号：启用0：禁用*/
            uint32_t fcmd_quad:       1;                /*在命令阶段1施加4个信号：启用0：禁用*/
            uint32_t reserved9:       1;                /*保留*/
            uint32_t fcs_crc_en:      1;                /*对于SPI1，在将加密数据写入闪存之前初始化crc32模块。低激活。*/
            uint32_t tx_crc_en:       1;                /*对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0:禁用*/
            uint32_t reserved12:      1;                /*保留*/
            uint32_t fastrd_mode:     1;                /*此位启用位：spi_mem_fread_qio spi_mem_fread_dio spi_mem-fread_qout和spi_mem.fread_dout。1： 启用0：禁用。*/
            uint32_t fread_dual:      1;                /*在读取操作中，读取数据阶段施加2个信号。1： 启用0：禁用。*/
            uint32_t resandres:       1;                /*设备ID被读出到SPI_MEM_RD_STATUS寄存器，该位与SPI_MEM_flash_res位组合。1： 启用0：禁用。*/
            uint32_t reserved16:      2;                /*保留*/
            uint32_t q_pol:           1;                /*该位用于设置MISO线极性1：高0低*/
            uint32_t d_pol:           1;                /*该位用于设置MOSI线极性1：高0低*/
            uint32_t fread_quad:      1;                /*在读取操作中，读取数据阶段施加4个信号。1： 启用0：禁用。*/
            uint32_t wp:              1;                /*SPI空闲时的写保护信号输出。1： 输出高0：输出低。*/
            uint32_t wrsr_2b:         1;                /*当状态寄存器被设置时，两个字节的数据将被写入状态寄存器。1： 启用0：禁用。*/
            uint32_t fread_dio:       1;                /*在读操作中，地址阶段和读数据阶段施加2个信号。1： 启用0：禁用。*/
            uint32_t fread_qio:       1;                /*在读操作中，地址阶段和读数据阶段施加4个信号。1： 启用0：禁用。*/
            uint32_t reserved25:      7;                /*保留*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t clk_mode:            2;            /*SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。*/
            uint32_t cs_hold_dly_res:    10;            /*发送RES/DP/HPM命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*512）SPI_CLK周期。*/
            uint32_t reserved2:           18;               /*保留*/
            uint32_t rxfifo_rst:       1;               /*SPI0 RX FIFO复位信号。*/
            uint32_t rxfifo_wfull_err: 1;               /*1： SPI0 RX FIFO写满错误缓存/EDMA未读取所有数据。0：无错误。*/
        };
        uint32_t val;
    } ctrl1;
    union {
        struct {
            uint32_t cs_setup_time: 5;                  /*通过spi时钟的准备阶段的（周期-1）该位与spi_mem_cs_setup位组合。*/
            uint32_t cs_hold_time:  5;                  /*Spi cs信号被Spi时钟延迟至无效，该位与Spi_mem_cs_hold位组合。*/
            uint32_t reserved10:       15;                  /*保留*/
            uint32_t cs_hold_delay: 6;                  /*这些位用于设置访问闪存时SPI突发传输之间的最小CS高时间tSHSL。tSHSL是（SPI_MEM_CS_HOLD_DELAY[5:0]+1）MSPI核心时钟周期。*/
            uint32_t sync_reset:    1;                  /*FSM将被重置。*/
        };
        uint32_t val;
    } ctrl2;
    union {
        struct {
            uint32_t clkcnt_l:       8;                 /*在主模式下，它必须等于spi_mem_clkcnt_N。*/
            uint32_t clkcnt_h:       8;                 /*在主模式下，必须为floor（（spi_mem_clkcnt_N+1）/2-1）。*/
            uint32_t clkcnt_n:       8;                 /*在主模式中，它是spi_mem_clk的除法器。因此spi_mem_clk频率为系统/（spi_mem_clkcnt_N+1）*/
            uint32_t reserved24:         7;                 /*保留*/
            uint32_t clk_equ_sysclk: 1;                 /*将此位设置为1分割模式。*/
        };
        uint32_t val;
    } clock;
    union {
        struct {
            uint32_t reserved0:          6;                 /*保留*/
            uint32_t cs_hold:        1;                 /*当spi处于完成阶段时，spi cs保持较低。1： 启用0：禁用。*/
            uint32_t cs_setup:       1;                 /*当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。*/
            uint32_t reserved8:          1;                 /*保留*/
            uint32_t ck_out_edge:       1;          /*该位与spi_mem_msi_delaymode位组合以设置mosi信号延迟模式。*/
            uint32_t reserved10:            2;          /*保留*/
            uint32_t fwrite_dual:       1;          /*在写入操作中，读取数据阶段应用2个信号*/
            uint32_t fwrite_quad:       1;          /*在写入操作中，读取数据阶段应用4个信号*/
            uint32_t fwrite_dio:        1;          /*在写操作中，地址阶段和读数据阶段施加2个信号。*/
            uint32_t fwrite_qio:        1;          /*在写操作中，地址阶段和读数据阶段施加4个信号。*/
            uint32_t reserved16:            8;          /*保留*/
            uint32_t usr_miso_highpart: 1;          /*读取数据阶段仅访问缓冲区的高部分spi_mem_w8～spi_mem-w15。1：启用0：禁用。*/
            uint32_t usr_mosi_highpart: 1;          /*写入数据阶段仅访问缓冲区的高部分spi_mem_w8～spi_mem-w15。1：启用0：禁用。*/
            uint32_t usr_dummy_idle:    1;          /*当位被启用时，SPI时钟在虚拟阶段被禁用。*/
            uint32_t usr_mosi:          1;          /*此位启用操作的写入数据阶段。*/
            uint32_t usr_miso:          1;          /*此位启用操作的读取数据阶段。*/
            uint32_t usr_dummy:         1;          /*此位启用操作的虚拟阶段。*/
            uint32_t usr_addr:          1;          /*此位启用操作的地址阶段。*/
            uint32_t usr_command:       1;          /*此位启用操作的命令阶段。*/
        };
        uint32_t val;
    } user;
    union {
        struct {
            uint32_t usr_dummy_cyclelen:     6;         /*伪相位的spi_mem_clk周期长度。寄存器值应为（cycle_num-1）。*/
            uint32_t reserved6:             20;         /*保留*/
            uint32_t usr_addr_bitlen:        6;         /*地址相位的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } user1;
    union {
        struct {
            uint32_t usr_command_value:     16;         /*命令的值。*/
            uint32_t reserved16:            12;         /*保留*/
            uint32_t usr_command_bitlen:     4;         /*命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）*/
        };
        uint32_t val;
    } user2;
    union {
        struct {
            uint32_t usr_mosi_bit_len:    10;           /*写入数据的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved10:          22;           /*保留*/
        };
        uint32_t val;
    } mosi_dlen;
    union {
        struct {
            uint32_t usr_miso_bit_len:    10;           /*读取数据的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved10:          22;           /*保留*/
        };
        uint32_t val;
    } miso_dlen;
    union {
        struct {
            uint32_t status:     16;                    /*设置spi_mem_flash_rdsr位和spi_mem_flash_res位时存储该值。*/
            uint32_t wb_mode:     8;                    /*闪存快速读取模式中的模式位与spi_mem_fastrd_Mode位组合。*/
            uint32_t reserved24:  8;                    /*保留*/
        };
        uint32_t val;
    } rd_status;
    uint32_t reserved_30;
    union {
        struct {
            uint32_t cs0_dis:            1;             /*SPI_CS0引脚启用1：禁用SPI_CS00：SPI_CS01引脚激活以选择SPI设备，如闪存外部RAM等。*/
            uint32_t cs1_dis:            1;             /*SPI_CS1引脚启用1：禁用SPI_CS1 0：SPI_CS1端口激活以选择SPI设备，如闪存外部RAM等。*/
            uint32_t reserved2:          1;             /*保留*/
            uint32_t mst_st_trans_end:         1;       /*该位用于指示完成了spi0_mst_st控制的传输。*/
            uint32_t mst_st_trans_end_en:      1;       /*该位用于启用spi0_mst_st控制传输的中断。*/
            uint32_t st_trans_end:             1;       /*该位用于指示完成了spi0_slv_st控制的传输。*/
            uint32_t st_trans_end_en:          1;       /*该位用于启用spi0_slv_st控制传输的中断。*/
            uint32_t reserved7:                    2;       /*保留*/
            uint32_t ck_idle_edge:       1;             /*1： 空闲时spi clk线为高0：空闲时spi-clk线为低*/
            uint32_t cs_keep_active:     1;             /*当位置位时，spi-cs线保持低电平。*/
            uint32_t reserved11:                  21;       /*保留*/
        };
        uint32_t val;
    } misc;
    uint32_t tx_crc;                                    /*SPI1 TX CRC数据寄存器。*/
    union {
        struct {
            uint32_t req_en:               1;           /*对于SPI0缓存访问，启用1:启用0:禁用。*/
            uint32_t usr_addr_4byte:           1;       /*对于具有4字节地址1的SPI1缓存读闪存：启用0：禁用。*/
            uint32_t flash_usr_cmd:        1;           /*对于用户定义命令1:enable0:disable的SPI0缓存读取闪存。*/
            uint32_t fdin_dual:                1;       /*对于SPI1反相，施加2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
            uint32_t fdout_dual:               1;       /*对于SPI1双相位，施加2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
            uint32_t faddr_dual:               1;       /*对于SPI1地址相位，施加2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
            uint32_t fdin_quad:                1;       /*对于SPI1反相，施加4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
            uint32_t fdout_quad:               1;       /*对于SPI1双相位，施加4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
            uint32_t faddr_quad:               1;       /*对于SPI1地址相位，施加4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
            uint32_t reserved9:               23;       /*保留*/
        };
        uint32_t val;
    } cache_fctrl;
    uint32_t reserved_40;
    uint32_t reserved_44;
    uint32_t reserved_48;
    uint32_t reserved_4c;
    uint32_t reserved_50;
    union {
        struct {
            uint32_t spi0_st:              4;           /*SPI0从属FSM的当前状态：SPI0_slv_st。0：空闲状态1：准备状态2：发送命令状态3：发送地址状态4：等待状态5：读取数据状态6：写入数据状态7：完成状态8：读取数据结束状态。*/
            uint32_t spi0_mst_st:          3;           /*SPI0主FSM的当前状态：SPI0_mst_st。0:空闲状态1:EM_CACHE_GRANT 2:编程/擦除挂起状态3:SPI0读取数据状态4:等待缓存/EDMA发送数据存储在SPI0 TX FIFO 5:SPI0写入数据状态。*/
            uint32_t cspi_lock_delay_time: 5;           /*SPI1发送PER后SPI0_slv_st对SPI0/1仲裁器的锁定延迟时间。*/
            uint32_t reserved12:              20;           /*保留*/
        };
        uint32_t val;
    } fsm;
    uint32_t data_buf[16];
    union {
        struct {
            uint32_t reserved0:                1;       /*保留*/
            uint32_t waiti_dummy:              1;       /*等待闪存空闲（RDSR）时的虚拟阶段启用*/
            uint32_t waiti_cmd:                8;       /*等待闪存空闲（RDSR）的命令。*/
            uint32_t waiti_dummy_cyclelen:     6;       /*等待闪存空闲（RDSR）时的虚拟周期长度。*/
            uint32_t reserved16:              16;       /*保留*/
        };
        uint32_t val;
    } flash_waiti_ctrl;
    union {
        struct {
            uint32_t flash_per:             1;          /*当该位被设置时，将触发程序擦除恢复位程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pes:             1;          /*当位被设置时，将触发程序擦除暂停位程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_per_wait_en:     1;          /*设置此位以启用程序擦除暂停后的SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*128）SPI_CLK周期。*/
            uint32_t flash_pes_wait_en:     1;          /*设置此位以启用程序擦除暂停后的SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
            uint32_t pes_per_en:            1;          /*设置此位以启用PES结束触发PER传输选项。如果该位为0，应用程序应在PES完成后发送PER。*/
            uint32_t flash_pes_en:          1;          /*设置此位以启用自动暂停功能。*/
            uint32_t pesr_end_msk:         16;          /*检查SUS/SUS1/SUS2状态位时的掩码值。如果读取的状态值为status_in[15:0]（当仅读取一个字节的数据时，只有status_in[7:0]有效，而当读取两个字节数据时，status_in[15:0]有效）SUS/SUS1/SUS2=status_in[15:0]^SPI_MEM_PESR_END_MSK[15:0]。*/
            uint32_t frd_sus_2b:            1;          /*1： 检查闪存SUS/SUS1/SUS2状态位时读取两个字节。0：检查闪存SUS/SUS1/SUS2状态位时读取一个字节*/
            uint32_t per_end_en:            1;          /*1： 应检查WIP和SUS/SUS1/SUS2位，以确保闪存的恢复状态。0：只需检查WIP为0。*/
            uint32_t pes_end_en:            1;          /*1： 应检查WIP和SUS/SUS1/SUS2位，以确保闪存的挂起状态。0：只需检查WIP为0。*/
            uint32_t sus_timeout_cnt:       7;          /*当SPI1检查SPI_MEM_SUS_TIMEOUT_CNT[6:0]次的SUS/SUS1/SUS2位失败时，它将被视为检查通过。*/
        };
        uint32_t val;
    } flash_sus_ctrl;
    union {
        struct {
            uint32_t flash_per_command:     8;          /*编程/擦除恢复命令。*/
            uint32_t flash_pes_command:     8;          /*编程/擦除暂停命令。*/
            uint32_t wait_pesr_command:    16;          /*闪存SUS/SUS1/SUS2状态位读取命令。当应检查SUS/SUS1/SUS2位以确保闪存的挂起或恢复状态时，应发送命令。*/
        };
        uint32_t val;
    } flash_sus_cmd;
    union {
        struct {
            uint32_t flash_sus:     1;                  /*闪存挂起的状态仅在SPI1中使用。*/
            uint32_t reserved1:    31;                  /*保留*/
        };
        uint32_t val;
    } sus_status;
    union {
        struct {
            uint32_t timing_clk_ena:       1;           /*该位用于启用所有读取操作的定时调整时钟。*/
            uint32_t timing_cali:              1;       /*该位用于启用所有读取操作的定时自动校准。*/
            uint32_t extra_dummy_cyclelen:     3;       /*为spi时钟校准添加额外的伪spi时钟周期长度。*/
            uint32_t reserved5:               27;           /*保留*/
        };
        uint32_t val;
    } timing_cali;
    union {
        struct {
            uint32_t din0_mode: 2;                      /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din1_mode: 2;                      /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din2_mode: 2;                      /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t din3_mode: 2;                      /*输入信号延迟系统时钟周期0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
            uint32_t reserved8:    24;                      /*保留*/
        };
        uint32_t val;
    } din_mode;
    union {
        struct {
            uint32_t din0_num: 2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din1_num: 2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din2_num: 2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t din3_num: 2;                       /*输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
            uint32_t reserved8:   24;                       /*保留*/
        };
        uint32_t val;
    } din_num;
    union {
        struct {
            uint32_t dout0_mode: 1;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout1_mode: 1;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout2_mode: 1;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t dout3_mode: 1;                     /*输出信号被系统时钟周期延迟0：无延迟的输出1：带clk_apb的偏倚输出2：带clk _apb的负边输出3：带clk160的偏倚的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
            uint32_t reserved4:     28;                     /*保留*/
        };
        uint32_t val;
    } dout_mode;
    uint32_t reserved_b8;
    uint32_t reserved_bc;
    union {
        struct {
            uint32_t per_end_int_ena:        1;         /*SPI_MEM_PER_END_INT中断的启用位。*/
            uint32_t pes_end_int_ena:        1;         /*SPI_MEM_PES_END_INT中断的启用位。*/
            uint32_t wpe_end_int_ena:        1;         /*SPI_MEM_WPE_END_INT中断的启用位。*/
            uint32_t st_end_int_ena:         1;         /*SPI_MEM_SLV_ST_END_INT中断的启用位。*/
            uint32_t mst_st_end_int_ena:     1;         /*SPI_MEM_MST_ST_END_INT中断的启用位。*/
            uint32_t reserved5:             27;         /*保留*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t per_end:                1;         /*SPI_MEM_PER_END_INT中断的清除位。*/
            uint32_t pes_end:                1;         /*SPI_MEM_PES_END_INT中断的清除位。*/
            uint32_t wpe_end:                1;         /*SPI_MEM_WPE_END_INT中断的清除位。*/
            uint32_t st_end:                 1;         /*SPI_MEM_SLV_ST_END_INT中断的清除位。*/
            uint32_t mst_st_end:             1;         /*SPI_MEM_MST_ST_END_INT中断的清除位。*/
            uint32_t reserved5:             27;         /*保留*/
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t per_end:                1;         /*SPI_MEM_PER_END_INT中断的原始位。1： 发送自动恢复命令（0x7A）并恢复闪存时触发。0：其他。*/
            uint32_t pes_end:                1;         /*SPI_MEM_PES_END_INT中断的原始位。1： 发送自动暂停命令（0x75）并暂停闪存时触发。0：其他。*/
            uint32_t wpe_end:                1;         /*SPI_MEM_WPE_END_INT中断的原始位。1： 发送WRSR/PP/SE/BE/CE且闪存已空闲时触发。0：其他。*/
            uint32_t st_end:                 1;         /*SPI_MEM_SLV_ST_END_INT中断的原始位。1： 当spi1_slv_st从非空闲状态更改为空闲状态时触发。这意味着SPI_CS升高。0：其他*/
            uint32_t mst_st_end:             1;         /*SPI_MEM_MST_ST_END_INT中断的原始位。1： 当spi1_mst_st从非空闲状态更改为空闲状态时触发。0：其他。*/
            uint32_t reserved5:             27;         /*保留*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t per_end:               1;          /*SPI_MEM_PER_END_INT中断的状态位。*/
            uint32_t pes_end:               1;          /*SPI_MEM_PES_END_INT中断的状态位。*/
            uint32_t wpe_end:               1;          /*SPI_MEM_WPE_END_INT中断的状态位。*/
            uint32_t st_end:                1;          /*SPI_MEM_SLV_ST_END_INT中断的状态位。*/
            uint32_t mst_st_end:            1;          /*SPI_MEM_MST_ST_END_INT中断的状态位。*/
            uint32_t reserved5:            27;          /*保留*/
        };
        uint32_t val;
    } int_st;
    uint32_t reserved_d0;
    uint32_t reserved_d4;
    uint32_t reserved_d8;
    union {
        struct {
            uint32_t clk_en:     1;                     /*寄存器时钟门启用信号。1： 启用。0：禁用。*/
            uint32_t reserved1: 31;                         /*保留*/
        };
        uint32_t val;
    } clock_gate;
    union {
        struct {
            uint32_t spi01_clk_sel: 2;                  /*当数字系统时钟选择PLL时钟且PLL时钟的频率为480MHz时，reg_spi01_clk_sel:0:SPI0/1模块时钟（clk）的值为80MHz。1： SPI0/1模块时钟（clk）为120MHz。2： SPI0/1模块时钟（clk）160MHz。3： 未使用。当数字系统时钟选择PLL时钟且PLL时钟的频率为320MHz时，reg_spi01_clk_sel:0:SPI0/1模块时钟（clk）的值为80MHz。1： SPI0/1模块时钟（clk）为80MHz。2： SPI0/1模块时钟（clk）160MHz。3： 未使用。*/
            uint32_t reserved2:        30;                  /*保留*/
        };
        uint32_t val;
    } core_clk_sel;
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
            uint32_t date:      28;                     /*版本控制寄存器*/
            uint32_t reserved28: 4;                     /*保留*/
        };
        uint32_t val;
    } date;
} spi_mem_dev_t;
extern spi_mem_dev_t SPIMEM0;
extern spi_mem_dev_t SPIMEM1;

_Static_assert(sizeof(spi_mem_dev_t) == 0x400, "spi_mem_dev_t size error!");

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_SPI_MEM_STRUCT_H_ */

