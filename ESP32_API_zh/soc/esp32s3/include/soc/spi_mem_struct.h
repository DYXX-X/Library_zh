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
#ifndef _SOC_SPI_MEM_STRUCT_H_
#define _SOC_SPI_MEM_STRUCT_H_


#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct spi_mem_dev_s {
    union {
        struct {
            uint32_t reserved0                     :    17;  /*保留*/
            uint32_t flash_pe                      :    1;  /*在用户模式下，设置为指示将触发编程/擦除操作。该位与SPI_MEM_USR位组合。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t usr                           :    1;  /*用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_hpm                     :    1;  /*将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_res                     :    1;  /*此位与SPI_MEM_RESANRES位结合，将Flash从断电状态或高性能模式释放，并获得设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_dp                      :    1;  /*将闪存驱动器关闭。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_ce                      :    1;  /*芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_be                      :    1;  /*块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_se                      :    1;  /*扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pp                      :    1;  /*页面编程启用（要编程的数据为1字节~64字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
            uint32_t flash_wrsr                    :    1;  /*写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdsr                    :    1;  /*读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_rdid                    :    1;  /*读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wrdi                    :    1;  /*写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_wren                    :    1;  /*写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_read                    :    1;  /*读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
        };
        uint32_t val;
    } cmd;
    uint32_t addr;
    union {
        struct {
            uint32_t reserved0                     :    3;  /*保留*/
            uint32_t fdummy_out                    :    1;  /*在DUMMY阶段，SPI总线的信号电平由SPI0控制器输出。*/
            uint32_t fdout_oct                     :    1;  /*设置此位以在DOUT阶段启用8位模式（8-bm）。*/
            uint32_t fdin_oct                      :    1;  /*设置此位以在DIN阶段启用8位模式（8-bm）。*/
            uint32_t faddr_oct                     :    1;  /*设置此位以在ADDR阶段启用8位模式（8-bm）。*/
            uint32_t fcmd_dual                     :    1;  /*设置此位以在CMD阶段启用2位模式（2-bm）。*/
            uint32_t fcmd_quad                     :    1;  /*设置此位以在CMD阶段启用4位模式（4-bm）。*/
            uint32_t fcmd_oct                      :    1;  /*设置此位以在CMD阶段启用8位模式（8-bm）。*/
            uint32_t fcs_crc_en                    :    1;  /*对于SPI1，在将加密数据写入闪存之前初始化crc32模块。低激活。*/
            uint32_t tx_crc_en                     :    1;  /*对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0:禁用*/
            uint32_t reserved12                    :    1;  /*保留*/
            uint32_t fastrd_mode                   :    1;  /*当设置SPI_MEM_FREAD_QIO、SPI_MEM_FREAD_DIO、SPI_MEM_FREAD_DQUAD或SPI_MEM-FREAD_DUAL时，应设置此位。*/
            uint32_t fread_dual                    :    1;  /*在硬件0x3B读取操作中，DIN相位施加2个信号。1： 启用0：禁用。*/
            uint32_t resandres                     :    1;  /*设备ID被读出到SPI_MEM_RD_STATUS寄存器，该位与SPI_MEM_flash_res位组合。1： 启用0：禁用。*/
            uint32_t reserved16                    :    2;  /*保留*/
            uint32_t q_pol                         :    1;  /*该位用于设置MISO线极性，1：高0，低*/
            uint32_t d_pol                         :    1;  /*该位用于设置MOSI线极性，1：高0，低*/
            uint32_t fread_quad                    :    1;  /*在硬件0x6B读取操作中，DIN相位应用4个信号（4位模式）。1： 启用0：禁用。*/
            uint32_t wp                            :    1;  /*SPI空闲时的写保护信号输出。1： 输出高，0：输出低。*/
            uint32_t wrsr_2b                       :    1;  /*设置状态寄存器时，两个字节的数据将写入状态寄存器。1： 启用0：禁用。*/
            uint32_t fread_dio                     :    1;  /*在硬件0xBB读取操作中，ADDR相位和DIN相位应用2个信号（2位模式）。1： 启用0：禁用。*/
            uint32_t fread_qio                     :    1;  /*在硬件0xEB读取操作中，ADDR相位和DIN相位施加4个信号（4位模式）。1： 启用0：禁用。*/
            uint32_t reserved25                    :    7;  /*保留*/
        };
        uint32_t val;
    } ctrl;
    union {
        struct {
            uint32_t clk_mode                      :    2;  /*SPI总线时钟（SPI_CLK）模式位。0:当CS不活动时，SPI总线时钟（SPI_CLK）关闭1:SPI_CLK在SPI_CS不活动后延迟一个周期2:SPI_CLK2在SPI_C不活动后推迟两个周期3:SPI_CLK始终打开。*/
            uint32_t cs_hold_dly_res               :    10;  /*发送RES/DP/HPM/PES/PER命令后，SPI1可以等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4或*256）SPI_CLK周期。*/
            uint32_t reserved2                     :    18;  /*保留*/
            uint32_t rxfifo_rst                    :    1;  /*SPI0 RX FIFO复位信号。设置此位并在SPI0传输开始之前清除。*/
            uint32_t reserved31                    :    1;  /*保留*/
        };
        uint32_t val;
    } ctrl1;
    union {
        struct {
            uint32_t cs_setup_time                 :    5;  /*通过SPI_CLK（即SPI_CS设置时间）来计算PREP阶段的（周期-1）。这些位与SPI_MEM_CS_SETUP位组合。*/
            uint32_t cs_hold_time                  :    5;  /*SPI总线CS（SPI_CS）信号被SPI总线时钟（SPI_CLK）延迟到非活动状态，这是非ECC模式下的SPI_CS保持时间。这些位与SPI_MEM_CS_HOLD位组合。*/
            uint32_t ecc_cs_hold_time              :    3;  /*SPI_MEM_CS_HOLD_TIME+SPI_MEM_ECC_CS_HOLD _TIME是访问闪存时ECC模式下的SPI_CS保持周期。*/
            uint32_t ecc_skip_page_corner          :    1;  /*1： MSPI在访问闪存时跳过页面角落。0：访问闪存时不跳过页面角落。*/
            uint32_t ecc_16to18_byte_en            :    1;  /*设置此位以在访问闪存时启用MSPI ECC 16字节数据和2 ECC字节模式。*/
            uint32_t reserved15                    :    10;  /*保留*/
            uint32_t cs_hold_delay                 :    6;  /*这些位用于设置访问闪存时SPI突发传输之间的最小CS高时间tSHSL。tSHSL是（SPI_MEM_CS_HOLD_DELAY[5:0]+1）MSPI核心时钟周期。*/
            uint32_t sync_reset                    :    1;  /*FSM将被重置。*/
        };
        uint32_t val;
    } ctrl2;
    union {
        struct {
            uint32_t clkcnt_l                      :    8;  /*它必须等于SPI_MEM_CLKCNT_N的值。*/
            uint32_t clkcnt_h                      :    8;  /*它必须是下限值（（SPI_MEM_CLKCNT_N+1）/2-1）。*/
            uint32_t clkcnt_n                      :    8;  /*当SPI0访问闪存时，f_SPI_CLK=f_MSPI_CORE_CLK/（SPI_MEM_CLKCNT_N+1）*/
            uint32_t reserved24                    :    7;  /*保留*/
            uint32_t clk_equ_sysclk                :    1;  /*当SPI0访问闪存时，将此位设置为1分区模式，f_SPI_CLK=f_MPI_CORE_CLK。*/
        };
        uint32_t val;
    } clock;
    union {
        struct {
            uint32_t reserved0                     :    6;  /*保留*/
            uint32_t cs_hold                       :    1;  /*当MSPI处于DONE状态时，设置此位以保持SPI_CS为低。*/
            uint32_t cs_setup                      :    1;  /*当MSPI处于PREP状态时，设置此位以保持SPI_CS为低。*/
            uint32_t reserved8                     :    1;  /*保留*/
            uint32_t ck_out_edge                   :    1;  /*该位与SPI_MEM_CK_IDLE_EDGE位相结合，用于改变SPI_CLK的时钟模式0~3。*/
            uint32_t reserved10                    :    2;  /*保留*/
            uint32_t fwrite_dual                   :    1;  /*设置此位以启用SPI1写入操作中DOUT阶段的2-bm。*/
            uint32_t fwrite_quad                   :    1;  /*设置此位以启用SPI1写入操作中DOUT阶段的4位字节。*/
            uint32_t fwrite_dio                    :    1;  /*设置此位以在SPI1写入操作中的ADDR和DOUT阶段启用2-bm。*/
            uint32_t fwrite_qio                    :    1;  /*设置此位以启用SPI1写入操作中ADDR和DOUT阶段的4位模式（4-bm）。*/
            uint32_t reserved16                    :    8;  /*保留*/
            uint32_t usr_miso_highpart             :    1;  /*DIN相位仅访问缓冲器SPI_MEM_W8_REG~SPI_MEM-W15_REG的高部分。1： 启用0：禁用。*/
            uint32_t usr_mosi_highpart             :    1;  /*DOUT阶段仅访问缓冲器SPI_MEM_W8_REG~SPI_MEM-W15_REG的高部分。1： 启用0：禁用。*/
            uint32_t usr_dummy_idle                :    1;  /*当位被启用时，SPI_CLK在DUMMY阶段被禁用（无时钟边沿）。*/
            uint32_t usr_mosi                      :    1;  /*设置此位以启用写入数据操作的DOUT阶段。*/
            uint32_t usr_miso                      :    1;  /*设置此位以启用读取数据操作的DIN阶段。*/
            uint32_t usr_dummy                     :    1;  /*设置此位以启用操作的DUMMY阶段。*/
            uint32_t usr_addr                      :    1;  /*设置此位以启用操作的ADDR阶段。*/
            uint32_t usr_command                   :    1;  /*设置此位以启用操作的CMD阶段。*/
        };
        uint32_t val;
    } user;
    union {
        struct {
            uint32_t usr_dummy_cyclelen            :    6;  /*SPI_CLK周期长度减去DUMMY相位的1。*/
            uint32_t reserved6                     :    20;  /*保留*/
            uint32_t usr_addr_bitlen               :    6;  /*ADDR相位的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } user1;
    union {
        struct {
            uint32_t usr_command_value             :    16;  /*用户定义（USR）命令的值。*/
            uint32_t reserved16                    :    12;  /*保留*/
            uint32_t usr_command_bitlen            :    4;  /*CMD阶段的位长度。寄存器值应为（bit_num-1）*/
        };
        uint32_t val;
    } user2;
    union {
        struct {
            uint32_t usr_mosi_bit_len              :    10;  /*DOUT相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved10                    :    22;  /*保留*/
        };
        uint32_t val;
    } mosi_dlen;
    union {
        struct {
            uint32_t usr_miso_bit_len              :    10;  /*DIN相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t reserved10                    :    22;  /*保留*/
        };
        uint32_t val;
    } miso_dlen;
    union {
        struct {
            uint32_t status                        :    16;  /*设置SPI_MEM_FLASH_RDSR位和SPI_MEM-FLASH_RES位时存储该值。*/
            uint32_t wb_mode                       :    8;  /*闪存快速读取模式中的模式位与SPI_MEM_FASTRD_Mode位组合。*/
            uint32_t reserved24                    :    8;  /*保留*/
        };
        uint32_t val;
    } rd_status;
    uint32_t ext_addr;
    union {
        struct {
            uint32_t cs0_dis                       :    1;  /*设置此位以升高高SPI_CS引脚，这意味着当SPI1传输开始时，连接到SPI_CS的SPI设备（闪存）处于低电平。*/
            uint32_t cs1_dis                       :    1;  /*设置此位以升高高SPI_CS1引脚，这意味着当SPI1传输开始时，连接到SPI_CS1的SPI设备（Ext_RAM）处于低电平。*/
            uint32_t reserved0                     :    5;  /*保留*/
            uint32_t fsub_pin                      :    1;  /*闪存连接到SPI SUBPIN总线。*/
            uint32_t ssub_pin                      :    1;  /*Ext_RAM连接到SPI SUBPIN总线。*/
            uint32_t ck_idle_edge                  :    1;  /*1： SPI_CLK线空闲时为高电平。0:SPI_CLK线空闲时低*/
            uint32_t cs_keep_active                :    1;  /*当位置位时，SPI_CS线保持低电平。*/
            uint32_t auto_per                      :    1;  /*设置此位以启用自动PER功能。如果发送PES命令，硬件将发出PER命令。*/
            uint32_t reserved12                    :    20;  /*保留*/
        };
        uint32_t val;
    } misc;
    uint32_t tx_crc;
    union {
        struct {
            uint32_t req_en                        :    1;  /*设置此位以启用Cache的访问和SPI0的传输。*/
            uint32_t usr_cmd_4byte                 :    1;  /*设置此位以启用具有32位地址的SPI0读闪存。SPI_MEM_USR_ADDR_BITLEN的值应为31。*/
            uint32_t flash_usr_cmd                 :    1;  /*1： SPI0读取闪存的命令值为SPI_MEM_USR_command_value。0：硬件读取命令值，由SPI_MEM_FREAD_QIO、SPI_MEM_FREAD_DIO、SPI_MEM_FREAD_FQUAD、SPI_MEM _FREAD_DUAL和SPI_MEM-FASTRD_MODE位控制。*/
            uint32_t fdin_dual                     :    1;  /*当SPI0访问闪存时，将此位设置为在DIN阶段启用2-bm。*/
            uint32_t fdout_dual                    :    1;  /*当SPI0访问闪存时，将此位设置为在DOUT阶段启用2-bm。*/
            uint32_t faddr_dual                    :    1;  /*当SPI0访问闪存时，将此位设置为在ADDR阶段启用2-bm。*/
            uint32_t fdin_quad                     :    1;  /*当SPI0访问闪存时，将此位设置为在DIN阶段启用4-bm。*/
            uint32_t fdout_quad                    :    1;  /*当SPI0访问闪存时，将此位设置为在DOUT阶段启用4-bm。*/
            uint32_t faddr_quad                    :    1;  /*当SPI0访问闪存时，将此位设置为在ADDR阶段启用4-bm。*/
            uint32_t reserved9                     :    23;  /*保留*/
        };
        uint32_t val;
    } cache_fctrl;
    union {
        struct {
            uint32_t usr_scmd_4byte                :    1;  /*设置此位以启用SPI0读取32位地址的Ext_RAM。SPI_MEM_SRAM_ADDR_BITLEN的值应为31。*/
            uint32_t usr_sram_dio                  :    1;  /*将该位设置为在SPI0 Ext_RAM传输的所有阶段启用2-bm。*/
            uint32_t usr_sram_qio                  :    1;  /*设置该位以在所有SPI0 Ext_RAM传输中启用QPI模式。*/
            uint32_t usr_wr_sram_dummy             :    1;  /*当SPI0访问Ext_RAM时，设置此位以启用写入操作中的DUMMY阶段。*/
            uint32_t usr_rd_sram_dummy             :    1;  /*当SPI0访问Ext_RAM时，设置此位以启用读取操作中的DUMMY阶段。*/
            uint32_t usr_rcmd                      :    1;  /*1： SPI0读取Ext_RAM的命令值为SPI_MEM_CACHE_SRAM_USR_WR_CMD_value。0：值为0x2。*/
            uint32_t sram_rdummy_cyclelen          :    6;  /*当SPI0访问Ext_RAM时，读取数据传输中的SPI_CLK周期减去DUMMY阶段的1。*/
            uint32_t reserved12                    :    2;  /*保留*/
            uint32_t sram_addr_bitlen              :    6;  /*当SPI0访问Ext_RAM时，它是ADDR相位的位长度。寄存器值应为（bit_num-1）。*/
            uint32_t usr_wcmd                      :    1;  /*1： SPI0写入Ext_RAM的命令值为SPI_MEM_CACHE_SRAM_USR_RD_CMD_value。0：值为0x3。*/
            uint32_t sram_oct                      :    1;  /*设置该位以在所有SPI0 Ext_RAM传输中启用OPI模式。*/
            uint32_t sram_wdummy_cyclelen          :    6;  /*当SPI0访问Ext_RAM时，写入数据传输中的SPI_CLK周期减去DUMMY阶段的1。*/
            uint32_t reserved28                    :    4;  /*保留*/
        };
        uint32_t val;
    } cache_sctrl;
    union {
        struct {
            uint32_t sclk_mode                     :    2;  /*SPI0访问Ext_RAM时的SPI_CLK模式位。0:当CS不活动时，SPI_CLK关闭1:在CS不活动后，SPI_CLK延迟一个周期2:在CS不激活后，SPI-CLK延迟两个周期3:SPI_CLK始终打开。*/
            uint32_t swb_mode                      :    8;  /*SPI0访问Ext_RAM时的模式位。*/
            uint32_t sdin_dual                     :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在DIN阶段启用2-bm。*/
            uint32_t sdout_dual                    :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在DOUT阶段启用2-bm。*/
            uint32_t saddr_dual                    :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在ADDR阶段启用2-bm。*/
            uint32_t scmd_dual                     :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在CMD阶段启用2-bm。*/
            uint32_t sdin_quad                     :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在DIN阶段启用4-bm。*/
            uint32_t sdout_quad                    :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在DOUT阶段启用4-bm。*/
            uint32_t saddr_quad                    :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在ADDR阶段启用4-bm。*/
            uint32_t scmd_quad                     :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在CMD阶段启用4-bm。*/
            uint32_t sdin_oct                      :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在DIN阶段启用8-bm。*/
            uint32_t sdout_oct                     :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在DOUT阶段启用8-bm。*/
            uint32_t saddr_oct                     :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在ADDR阶段启用8-bm。*/
            uint32_t scmd_oct                      :    1;  /*当SPI0访问Ext_RAM时，将此位设置为在CMD阶段启用8-bm。*/
            uint32_t sdummy_out                    :    1;  /*当SPI0访问Ext_RAM时，在DUMMY阶段，SPI0控制器输出SPI总线的信号电平。*/
            uint32_t reserved23                    :    9;  /*保留*/
        };
        uint32_t val;
    } sram_cmd;
    union {
        struct {
            uint32_t usr_rd_cmd_value              :    16;  /*当SPI0读取Ext_RAM时，它是CMD阶段的命令值。*/
            uint32_t reserved16                    :    12;  /*保留*/
            uint32_t usr_rd_cmd_bitlen             :    4;  /*当SPI0读取Ext_RAM时，它是CMD阶段的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } sram_drd_cmd;
    union {
        struct {
            uint32_t usr_wr_cmd_value              :    16;  /*当SPI0写入Ext_RAM时，它是CMD阶段的命令值。*/
            uint32_t reserved16                    :    12;  /*保留*/
            uint32_t usr_wr_cmd_bitlen             :    4;  /*当SPI0写入Ext_RAM时，它是CMD阶段的位长度。寄存器值应为（bit_num-1）。*/
        };
        uint32_t val;
    } sram_dwr_cmd;
    union {
        struct {
            uint32_t cnt_l                         :    8;  /*它必须等于SPI_MEM_SCLKCNT_N的值。*/
            uint32_t cnt_h                         :    8;  /*它必须是下限值（（SPI_MEM_SCLKCNT_N+1）/2-1）。*/
            uint32_t cnt_n                         :    8;  /*当SPI0访问Ext_RAM时，f_SPI_CLK=f_MSPI_CORE_CLK/（SPI_MEM_SCLKCNT_N+1）*/
            uint32_t reserved24                    :    7;  /*保留*/
            uint32_t equ_sysclk                    :    1;  /*当SPI0访问Ext_RAM时，将此位设置为1分割模式，f_SPI_CLK=f_MPI_CORE_CLK。*/
        };
        uint32_t val;
    } sram_clk;
    union {
        struct {
            uint32_t st                            :    3;  /*SPI0状态机的状态。0：空闲状态（idle），1：准备状态（PREP），2：发送命令状态（CMD），3：发送地址状态（ADDR），4：红色数据状态（DIN），5：写入数据状态（DOUT），6：等待状态（DUMMY），7：完成状态（done）。*/
            uint32_t reserved3                     :    29;  /*保留*/
        };
        uint32_t val;
    } fsm;
    uint32_t data_buf[16];                                                /*数据缓冲器*/
    union {
        struct {
            uint32_t waiti_en                      :    1;  /*设置此位以在发送PP/SE/BE/CE/WRSR/PES命令时启用自动等待闪存空闲操作。*/
            uint32_t waiti_dummy                   :    1;  /*设置此位以启用自动等待闪存空闲传输（RDSR）中的DUMMY阶段。*/
            uint32_t waiti_cmd                     :    8;  /*自动等待闪存空闲传输（RDSR）的命令值。*/
            uint32_t waiti_dummy_cyclelen          :    6;  /*等待闪存空闲（RDSR）时的虚拟周期长度。*/
            uint32_t reserved16                    :    16;  /*保留*/
        };
        uint32_t val;
    } flash_waiti_ctrl;
    union {
        struct {
            uint32_t flash_per                     :    1;  /*程序擦除恢复位，程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_pes                     :    1;  /*程序擦除暂停位，当该位被设置时，将触发程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
            uint32_t flash_per_wait_en             :    1;  /*设置此位以在发送程序擦除恢复（PER）后添加延迟时间。*/
            uint32_t flash_pes_wait_en             :    1;  /*设置此位以在发送程序擦除暂停（PES）命令后增加延迟时间。*/
            uint32_t pes_per_en                    :    1;  /*设置此位以启用PES传输触发PES传输选项。*/
            uint32_t pesr_idle_en                  :    1;  /*1： 分离PER闪存等待空闲和PES闪存等待空闲。0：不分开。*/
            uint32_t reserved6                     :    26;  /*保留*/
        };
        uint32_t val;
    } flash_sus_cmd;
    union {
        struct {
            uint32_t flash_pes_en                  :    1;  /*设置此位以启用自动挂起功能。*/
            uint32_t flash_per_command             :    8;  /*编程/擦除恢复命令值。*/
            uint32_t flash_pes_command             :    8;  /*编程/擦除暂停命令值。*/
            uint32_t reserved17                    :    15;  /*保留*/
        };
        uint32_t val;
    } flash_sus_ctrl;
    union {
        struct {
            uint32_t flash_sus                     :    1;  /*闪存挂起的状态。发送PES命令时设置该位，发送PER时清除该位。仅用于SPI1。*/
            uint32_t reserved1                     :    1;  /*保留*/
            uint32_t flash_hpm_dly_256             :    1;  /*1： 发送HPM命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:SPI1在发送HPM命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
            uint32_t flash_res_dly_256             :    1;  /*1： 发送RES命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:发送RES命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
            uint32_t flash_dp_dly_256              :    1;  /*1： 发送DP命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:SPI1在发送DP命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
            uint32_t flash_per_dly_256             :    1;  /*当SPI_MEM_FLASH_PER_WAIT_EN为1时有效。1:SPI1在发送PER命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:发送PER命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
            uint32_t flash_pes_dly_256             :    1;  /*当SPI_MEM_FLASH_PES_WAIT_EN为1时有效。1:SPI1在发送PES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:SPI1在发送PES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
            uint32_t reserved7                     :    25;  /*保留*/
        };
        uint32_t val;
    } sus_status;
    union {
        struct {
            uint32_t timing_clk_ena                :    1;  /*将此位设置为开启HCLK。当PLL通电时，HCLK的频率等于PLL的频率。否则，频率等于XTAL的频率。*/
            uint32_t timing_cali                   :    1;  /*设置此位以在DUMMY阶段为所有读取操作添加额外的SPI_CLK周期。*/
            uint32_t extra_dummy_cyclelen          :    3;  /*当SPI0访问闪存时，在DUMMY阶段添加额外的SPI_CLK周期用于定时补偿。设置SPI_MEM_TIMING_CALI位时激活。*/
            uint32_t reserved5                     :    27;  /*保留*/
        };
        uint32_t val;
    } timing_cali;
    union {
        struct {
            uint32_t din0_mode                     :    3;  /*SPI_D输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din1_mode                     :    3;  /*SPI_Q输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din2_mode                     :    3;  /*SPI_WP输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din3_mode                     :    3;  /*SPI_HD输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din4_mode                     :    3;  /*SPI_IO4输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din5_mode                     :    3;  /*SPI_IO5输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din6_mode                     :    3;  /*SPI_IO6输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t din7_mode                     :    3;  /*SPI_IO7输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t dins_mode                     :    3;  /*SPI_DQS输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_MEM_DINS_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t reserved27                    :    5;  /*保留*/
        };
        uint32_t val;
    } din_mode;
    union {
        struct {
            uint32_t din0_num                      :    2;  /*SPI_D输入延迟数。*/
            uint32_t din1_num                      :    2;  /*SPI_Q输入延迟数。*/
            uint32_t din2_num                      :    2;  /*SPI_WP输入延迟数。*/
            uint32_t din3_num                      :    2;  /*SPI_HD输入延迟数。*/
            uint32_t din4_num                      :    2;  /*SPI_IO4输入延迟数。*/
            uint32_t din5_num                      :    2;  /*SPI_IO5输入延迟数。*/
            uint32_t din6_num                      :    2;  /*SPI_IO6输入延迟数。*/
            uint32_t din7_num                      :    2;  /*SPI_IO7输入延迟数。*/
            uint32_t dins_num                      :    2;  /*SPI_DQS输入延迟数。*/
            uint32_t reserved18                    :    14;  /*保留*/
        };
        uint32_t val;
    } din_num;
    union {
        struct {
            uint32_t dout0_mode                    :    1;  /*SPI_D输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout1_mode                    :    1;  /*SPI_Q输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout2_mode                    :    1;  /*SPI_WP输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout3_mode                    :    1;  /*SPI_HD输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout4_mode                    :    1;  /*SPI_IO4输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout5_mode                    :    1;  /*SPI_IO5输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout6_mode                    :    1;  /*SPI_IO6输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t dout7_mode                    :    1;  /*SPI_IO7输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t douts_mode                    :    1;  /*SPI_DQS输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t reserved9                     :    23;  /*保留*/
        };
        uint32_t val;
    } dout_mode;
    uint32_t reserved_b8;
    union {
        struct {
            uint32_t smem_timing_clk_ena           :    1;  /*将此位设置为开启HCLK。当PLL通电时，HCLK的频率等于PLL的频率。否则，频率等于XTAL的频率。*/
            uint32_t smem_timing_cali              :    1;  /*设置此位以在DUMMY阶段为所有读取操作添加额外的SPI_CLK周期。*/
            uint32_t smem_extra_dummy_cyclelen     :    3;  /*当SPI0访问Ext_RAM时，在DUMMY阶段添加额外的SPI_CLK周期用于定时补偿。设置SPI_SMEM_TIMING_CALI位时激活。*/
            uint32_t reserved5                     :    27;  /*保留*/
        };
        uint32_t val;
    } spi_smem_timing_cali;
    union {
        struct {
            uint32_t smem_din0_mode                :    3;  /*SPI_D输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din1_mode                :    3;  /*SPI_Q输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din2_mode                :    3;  /*SPI_WP输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din3_mode                :    3;  /*SPI_HD输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din4_mode                :    3;  /*SPI_IO4输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din5_mode                :    3;  /*SPI_IO5输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din6_mode                :    3;  /*SPI_IO6输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_din7_mode                :    3;  /*SPI_IO7输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t smem_dins_mode                :    3;  /*SPI_DQS输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DINS_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。*/
            uint32_t reserved27                    :    5;  /*保留*/
        };
        uint32_t val;
    } spi_smem_din_mode;
    union {
        struct {
            uint32_t smem_din0_num                 :    2;  /*SPI_D输入延迟数。*/
            uint32_t smem_din1_num                 :    2;  /*SPI_Q输入延迟数。*/
            uint32_t smem_din2_num                 :    2;  /*SPI_WP输入延迟数。*/
            uint32_t smem_din3_num                 :    2;  /*SPI_HD输入延迟数。*/
            uint32_t smem_din4_num                 :    2;  /*SPI_IO4输入延迟数。*/
            uint32_t smem_din5_num                 :    2;  /*SPI_IO5输入延迟数。*/
            uint32_t smem_din6_num                 :    2;  /*SPI_IO6输入延迟数。*/
            uint32_t smem_din7_num                 :    2;  /*SPI_IO7输入延迟数。*/
            uint32_t smem_dins_num                 :    2;  /*SPI_DQS输入延迟数。*/
            uint32_t reserved18                    :    14;  /*保留*/
        };
        uint32_t val;
    } spi_smem_din_num;
    union {
        struct {
            uint32_t smem_dout0_mode               :    1;  /*SPI_D输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout1_mode               :    1;  /*SPI_Q输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout2_mode               :    1;  /*SPI_WP输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout3_mode               :    1;  /*SPI_HD输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout4_mode               :    1;  /*SPI_IO4输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout5_mode               :    1;  /*SPI_IO5输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout6_mode               :    1;  /*SPI_IO6输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_dout7_mode               :    1;  /*SPI_IO7输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t smem_douts_mode               :    1;  /*SPI_DQS输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。*/
            uint32_t reserved9                     :    23;  /*保留*/
        };
        uint32_t val;
    } spi_smem_dout_mode;
    union {
        struct {
            uint32_t ecc_err_int_num               :    8;  /*设置MSPI ECC读取的错误时间，以生成MSPI SPI_MEM_ECC_ERR_INT中断。*/
            uint32_t fmem_ecc_err_int_en           :    1;  /*设置此位以计算访问闪存时MSPI ECC读取的错误时间。*/
            uint32_t reserved9                     :    23;  /*保留*/
        };
        uint32_t val;
    } ecc_ctrl;
    uint32_t ecc_err_addr;
    union {
        struct {
            uint32_t reserved0                     :    6;  /*保留*/
            uint32_t ecc_data_err_bit              :    7;  /*当设置SPI_FMEM_ECC_ERR_INT_EN/SPI_SMEM_ECC-ERR_INT_EN并访问闪存/Ext_RAM时，它记录第一个ECC数据错误位号。该值的范围为0~127，对应于16个数据字节中的位数。它由SPI_MEM_ECC_ERR_INT_CLR位清除。*/
            uint32_t ecc_chk_err_bit               :    3;  /*设置SPI_MEM_ECC_BYTE_ERR时，这些位显示ECC字节的错误位数。*/
            uint32_t ecc_byte_err                  :    1;  /*当设置SPI_FMEM_ECC_ERR_INT_EN/SPI_SMEM_ECC-ERR_INT_EN并访问闪存/Ext_RAM时，它记录第一个ECC字节错误。它由SPI_MEM_ECC_ERR_INT_CLR位清除。*/
            uint32_t ecc_err_cnt                   :    8;  /*此位显示MSPI ECC读取的错误时间，包括ECC字节错误和数据字节错误。设置SPI_MEM_ECC_ERR_INT_CLR位时清除。*/
            uint32_t reserved25                    :    7;  /*保留*/
        };
        uint32_t val;
    } ecc_err_bit;
    uint32_t reserved_d8;
    union {
        struct {
            uint32_t smem_cs_setup                 :    1;  /*当MSPI处于PREP状态时，设置此位以保持SPI_CS为低。*/
            uint32_t smem_cs_hold                  :    1;  /*当MSPI处于DONE状态时，设置此位以保持SPI_CS为低。*/
            uint32_t smem_cs_setup_time            :    5;  /*通过SPI_CLK（即SPI_CS设置时间）来计算PREP阶段的（周期-1）。这些位与SPI_MEM_CS_SETUP位组合。*/
            uint32_t smem_cs_hold_time             :    5;  /*SPI总线CS（SPI_CS）信号被SPI总线时钟（SPI_CLK）延迟到非活动状态，这是非ECC模式下的SPI_CS保持时间。这些位与SPI_MEM_CS_HOLD位组合。*/
            uint32_t smem_ecc_cs_hold_time         :    3;  /*SPI_SMEM_CS_HOLD_TIME+SPI_SMEM_ECC_CS_HOLD _TIME是访问外部RAM时ECC模式下的MSPI CS保持周期。*/
            uint32_t smem_ecc_skip_page_corner     :    1;  /*1： MSPI在访问外部RAM时跳过页面角落。0：访问外部RAM时不跳过页角。*/
            uint32_t smem_ecc_16to18_byte_en       :    1;  /*设置此位以在访问外部RAM时启用MSPI ECC 16字节数据和2 ECC字节模式。*/
            uint32_t reserved17                    :    7;  /*保留*/
            uint32_t smem_ecc_err_int_en           :    1;  /*设置此位以计算访问外部RAM时MSPI ECC读取的错误时间。*/
            uint32_t smem_cs_hold_delay            :    6;  /*当访问外部RAM时，这些位用于设置SPI突发传输之间的最小CS高时间tSHSL。tSHSL是（SPI_SMEM_CS_HOLD_DELAY[5:0]+1）MSPI核心时钟周期。*/
            uint32_t reserved31                    :    1;  /*保留*/
        };
        uint32_t val;
    } spi_smem_ac;
    union {
        struct {
            uint32_t fmem_ddr_en                   :    1;  /*1： 在ddr模式下，0在sdr模式下*/
            uint32_t fmem_var_dummy                :    1;  /*设置位以启用DDR模式下的可变虚拟周期。*/
            uint32_t fmem_ddr_rdat_swp             :    1;  /*设置位以在DDR模式下重新排序字的RX数据。*/
            uint32_t fmem_ddr_wdat_swp             :    1;  /*设置位以在DDR模式下交换字的TX数据。*/
            uint32_t fmem_ddr_cmd_dis              :    1;  /*当ddr模式时，该位用于在CMD阶段禁用双边缘。*/
            uint32_t fmem_outminbytelen            :    7;  /*这是熊猫设备中的最小输出数据长度。*/
            uint32_t fmem_tx_ddr_msk_en            :    1;  /*当访问闪存时，设置此位以屏蔽MSPI ECC DDR写入模式中的第一个或最后一个字节。*/
            uint32_t fmem_rx_ddr_msk_en            :    1;  /*当访问闪存时，设置此位以屏蔽MSPI ECC DDR读取模式中的第一个或最后一个字节。*/
            uint32_t fmem_usr_ddr_dqs_thd          :    7;  /*基于SPI_CLK的存储器数据选通的延迟数。*/
            uint32_t fmem_ddr_dqs_loop             :    1;  /*1： 使用内部信号作为数据选通，选通不能被输入定时模块延迟。0：使用来自PAD的输入SPI_DQS信号作为数据选通，选通可由输入定时模块延迟*/
            uint32_t fmem_ddr_dqs_loop_mode        :    1;  /*设置SPI_FMEM_DDR_DQS_LOOP和SPI_FMEM-DDR_EN时，1：使用内部SPI_CLK作为数据选通。0：使用内部~SPI_CLK作为数据选通。否则，此位无效。*/
            uint32_t reserved23                    :    1;  /*保留*/
            uint32_t fmem_clk_diff_en              :    1;  /*设置此位以启用差分SPI_CLK#。*/
            uint32_t fmem_hyperbus_mode            :    1;  /*设置此位以启用SPI超级总线模式。*/
            uint32_t fmem_dqs_ca_in                :    1;  /*设置此位以启用CMD和ADDR的SPI相位中的SPI_DQS信号输入。*/
            uint32_t fmem_hyperbus_dummy_2x        :    1;  /*当SPI0访问闪存或SPI1访问闪存或sram时，设置此位以启用SPI超级总线模式下的可变虚拟功能。*/
            uint32_t fmem_clk_diff_inv             :    1;  /*设置此位以在访问闪存时反转SPI_DIFF。*/
            uint32_t fmem_octa_ram_addr            :    1;  /*设置此位以在访问闪存时启用octa_ram地址输出，这意味着ADDR_out[31:0]={spi_usr_ADDR_value[25:4]，6'd0，spi_usr_ADDR_value[3:1]，1'b0}。*/
            uint32_t fmem_hyperbus_ca              :    1;  /*设置此位以在访问闪存时启用HyperRAM地址输出，这意味着ADDR_out[31:0]={spi_usr_ADDR_value[19:4]，13'd0，spi_usr_ADDR_value[3:1]}。*/
            uint32_t reserved31                    :    1;  /*保留*/
        };
        uint32_t val;
    } ddr;
    union {
        struct {
            uint32_t smem_ddr_en                   :    1;  /*1： 在ddr模式下，0在sdr模式下*/
            uint32_t smem_var_dummy                :    1;  /*设置位以启用spi-ddr模式下的可变虚拟周期。*/
            uint32_t smem_ddr_rdat_swp             :    1;  /*设置位以重新排序spi-ddr模式下单词的rx数据。*/
            uint32_t smem_ddr_wdat_swp             :    1;  /*设置位以重新排序spi-ddr模式下单词的tx数据。*/
            uint32_t smem_ddr_cmd_dis              :    1;  /*当ddr模式时，该位用于在CMD阶段禁用双边缘。*/
            uint32_t smem_outminbytelen            :    7;  /*它是ddr-psram中的最小输出数据长度。*/
            uint32_t smem_tx_ddr_msk_en            :    1;  /*当访问外部RAM时，设置此位以屏蔽MSPI ECC DDR写入模式中的第一个或最后一个字节。*/
            uint32_t smem_rx_ddr_msk_en            :    1;  /*当访问外部RAM时，设置此位以屏蔽MSPI ECC DDR读取模式中的第一个或最后一个字节。*/
            uint32_t smem_usr_ddr_dqs_thd          :    7;  /*基于SPI_CLK的存储器数据选通的延迟数。*/
            uint32_t smem_ddr_dqs_loop             :    1;  /*1： 使用内部信号作为数据选通，选通不能被输入定时模块延迟。0：使用来自PAD的输入SPI_DQS信号作为数据选通，选通可由输入定时模块延迟*/
            uint32_t smem_ddr_dqs_loop_mode        :    1;  /*设置SPI_SMEM_DDR_DQS_LOOP和SPI_SMEM-DDR_EN时，1：使用内部SPI_CLK作为数据选通。0：使用内部~SPI_CLK作为数据选通。否则，此位无效。*/
            uint32_t reserved23                    :    1;  /*保留*/
            uint32_t smem_clk_diff_en              :    1;  /*设置此位以启用差分SPI_CLK#。*/
            uint32_t smem_hyperbus_mode            :    1;  /*设置此位以启用SPI超级总线模式。*/
            uint32_t smem_dqs_ca_in                :    1;  /*设置此位以启用CMD和ADDR的SPI相位中的SPI_DQS信号输入。*/
            uint32_t smem_hyperbus_dummy_2x        :    1;  /*当SPI0访问闪存或SPI1访问闪存或sram时，设置此位以启用SPI超级总线模式下的可变虚拟功能。*/
            uint32_t smem_clk_diff_inv             :    1;  /*设置此位以在访问外部RAM时反转SPI_DIFF。*/
            uint32_t smem_octa_ram_addr            :    1;  /*设置此位以在访问外部ram时启用八位ram地址输出，这意味着ADDR_out[31:0]={spi_usr_ADDR_value[25:4]，6'd0，spi_usr_ADDR_value[3:1]，1'b0}。*/
            uint32_t smem_hyperbus_ca              :    1;  /*设置此位以在访问外部RAM时启用HyperRAM地址输出，这意味着ADDR_out[31:0]={spi_usr_ADDR_value[19:4]，13'd0，spi_usr_ADDR_value[3:1]}。*/
            uint32_t reserved31                    :    1;  /*保留*/
        };
        uint32_t val;
    } spi_smem_ddr;
    union {
        struct {
            uint32_t clk_en                        :    1;  /*寄存器时钟门启用信号。1： 启用。0：禁用。*/
            uint32_t reserved1                     :    31;  /*保留*/
        };
        uint32_t val;
    } clock_gate;
    union {
        struct {
            uint32_t core_clk_sel                  :    2;  /*当数字系统时钟选择PLL时钟且PLL时钟频率为480MHz时，SPI_MEM_CORE_CLK_SEL:0:SPI0/1模块时钟（MSPI_CORE_CLK）的值为80MHz。1： MSPI_CORE_CLK为120MHz。2： MSPI_CORE_CLK为160MHz。3： MSPI_CORE_CLK为240MHz。当数字系统时钟选择PLL时钟且PLL时钟的频率为320MHz时，SPI_MEM_CORE_CLK_SEL:0:MSPI_CORE_CLK的值为80MHz。1： MSPI_CORE_CLK为80MHz。2： MSPI_CORE_CLK 160MHz。3： 未使用。*/
            uint32_t reserved2                     :    30;  /*保留*/
        };
        uint32_t val;
    } core_clk_sel;
    union {
        struct {
            uint32_t per_end_en                    :    1;  /*SPI_MEM_PER_END_INT中断的启用位。*/
            uint32_t pes_end_en                    :    1;  /*SPI_MEM_PES_END_INT中断的启用位。*/
            uint32_t total_trans_end_en            :    1;  /*SPI_MEM_TOTAL_TRANS_END_INT中断的启用位。*/
            uint32_t brown_out_en                  :    1;  /*SPI_MEM_BROWN_OUT_INT中断的启用位。*/
            uint32_t ecc_err_en                    :    1;  /*SPI_MEM_ECC_ERR_INT中断的启用位。*/
            uint32_t reserved5                     :    27;  /*保留*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t per_end_int_clr               :    1;  /*SPI_MEM_PER_END_INT中断的清除位。*/
            uint32_t pes_end_int_clr               :    1;  /*SPI_MEM_PES_END_INT中断的清除位。*/
            uint32_t total_trans_end_int_clr       :    1;  /*SPI_MEM_TOTAL_TRANS_END_INT中断的清除位。*/
            uint32_t brown_out_int_clr             :    1;  /*SPI_MEM_BROWN_OUT_INT中断的状态位。*/
            uint32_t ecc_err_int_clr               :    1;  /*SPI_MEM_ECC_ERR_INT中断的清除位。SPI_MEM_ECC_ERR_ADDR和SPI_MEM_。*/
            uint32_t reserved5                     :    27;  /*保留*/
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t per_end_int_raw               :    1;  /*SPI_MEM_PER_END_INT中断的原始位。1： 发送自动恢复命令（0x7A）并成功恢复闪存时触发。0：其他。*/
            uint32_t pes_end_int_raw               :    1;  /*SPI_MEM_PES_END_INT中断的原始位。1： 发送自动暂停命令（0x75）并成功暂停闪存时触发。0：其他。*/
            uint32_t total_trans_end_int_raw       :    1;  /*SPI_MEM_TOTAL_TRANS_END_INT中断的原始位。1： SPI1传输完成且闪存已空闲时触发。当WRSR/PP/SE/BE/CE被发送并且PES/PER命令被发送时，当WRSR/PP/SE-BE/CE成功时，该位被设置。0：其他。*/
            uint32_t brown_out_int_raw             :    1;  /*SPI_MEM_BROWN_OUT_INT中断的原始位。1： 触发条件是芯片失去电源，RTC模块向SPI1发出棕色关闭闪存请求。SPI1向闪存发出暂停命令后，触发此中断，MSPI返回空闲状态。0：其他。*/
            uint32_t ecc_err_int_raw               :    1;  /*SPI_MEM_ECC_ERR_INT中断的原始位。当APB_CTRL_FECC_ERR_INT_EN被设置并且APB_CTRL_SECC_ERR_INT_EN被清除时，当SPI0/1 ECC读闪存的错误时间等于或大于APB_CTRL_ECC_ERR_INT_NUM时，该位被触发。当APB_CTRL_FECC_ERR_INT_EN被清除并且APB_CTRL_SECC_ERR_INT_EN被设置时，当SPI0/1 ECC读取外部RAM的错误时间等于或大于APB_CTRL_ECC_ERR_INT_NUM时，该位被触发。当设置APB_CTRL_FECC_ERR_INT_EN和APB_CTRL_SECC_ERR_INT_EN时，当SPI0/1 ECC读取外部RAM和闪存的总错误时间等于或大于APB_CTRL_ECC_ERR_INT_NUM时，触发此位。当APB_CTRL_FECC_ERR_INT_EN和APB_CTRL_SECC_ERR_INT_EN被清除时，该位将不会被触发。*/
            uint32_t reserved5                     :    27;  /*保留*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t per_end_int_st                :    1;  /*SPI_MEM_PER_END_INT中断的状态位。*/
            uint32_t pes_end_int_st                :    1;  /*SPI_MEM_PES_END_INT中断的状态位。*/
            uint32_t total_trans_end_int_st        :    1;  /*SPI_MEM_TOTAL_TRANS_END_INT中断的状态位。*/
            uint32_t brown_out_int_st              :    1;  /*SPI_MEM_BROWN_OUT_INT中断的状态位。*/
            uint32_t ecc_err_int_st                :    1;  /*SPI_MEM_ECC_ERR_INT中断的状态位。*/
            uint32_t reserved5                     :    27;  /*保留*/
        };
        uint32_t val;
    } int_st;
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
            uint32_t reg_smem_spiclk_fun_drv       :    2;  /*当设置位SPI_SPICLK_PAD_DRV_CTL_EN并且MSPI访问外部RAM时，SPI_CLK PAD的驱动器由位SPI_SMEM_SPICLK_FUN_DRV[1:0]控制。*/
            uint32_t fmem_spiclk_fun_drv           :    2;  /*当设置位SPI_SPICLK_PAD_DRV_CTL_EN并且MSPI访问闪存时，SPI_CLK PAD的驱动器由位SPI_FMEM_SPICLK_FUN_DRV[1:0]控制。*/
            uint32_t reg_spiclk_pad_drv_ctl_en     :    1;  /*SPI_CLK PAD驱动器控制信号。1： SPI_CLK PAD的驱动器由位SPI_FMEM_SPICLK_FUN_DRV[1:0]和SPI_SMEM_SPICLK_FUN_DRV[1:0]控制。0:SPI_CLK PAD的驱动器由SPICLK PAD的位IO_MUX_FUNC_DRV[1:0]控制。*/
            uint32_t date                          :    23;  /*SPI寄存器版本。*/
            uint32_t reserved28                    :    4;  /*保留*/
        };
        uint32_t val;
    } date;
} spi_mem_dev_t;
extern spi_mem_dev_t SPIMEM0;
extern spi_mem_dev_t SPIMEM1;
#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_MEM_STRUCT_H_ */

