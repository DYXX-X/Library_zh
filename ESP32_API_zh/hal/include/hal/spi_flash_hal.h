// 版权所有2010-2019 Espressif Systems（上海）私人有限公司
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

/*******************************************************************************
 * 注意HAL不是公共api，不要在应用程序代码中使用。参见hal/include/hal/readme.md中的自述文件
 ******************************************************************************/

// SPI闪存的HAL层（公共部分）

#pragma once

#include "hal/spi_flash_ll.h"
#include "hal/spi_types.h"
#include "hal/spi_flash_types.h"
#include "soc/soc_memory_types.h"

/* 硬件主机特定常量*/
#define SPI_FLASH_HAL_MAX_WRITE_BYTES 64
#define SPI_FLASH_HAL_MAX_READ_BYTES 64

/**
 * 使用SPI外设的所有芯片的通用驱动程序上下文结构。将其包含在也使用SPI外设的其他驱动程序实现的驱动程序数据的HEAD中。
 */
typedef struct {
    spi_flash_host_inst_t inst; ///<主机实例，包含主机数据和函数指针表。可能随主机更新（硬件版本）。
    spi_dev_t *spi;             ///<指向SPI外围寄存器（SP1、SPI2或SPI3）的指针。初始化前设置。
    int cs_num;                 ///<使用哪个cs引脚，0-2。
    struct {
        uint8_t extra_dummy;            ///<用于补偿的预先计算的额外假人
        uint8_t cs_setup;               ///<（周期-1）准备阶段的spi时钟。
        uint8_t cs_hold;                ///<主机使用的CS保持时间配置
        uint8_t reserved2;              ///<保留，设置为0。
    };
    spi_flash_ll_clock_reg_t clock_conf;    ///<预先计算的时钟配置值
    esp_flash_io_mode_t base_io_mode;       ///<常用命令的默认IO模式掩码
    uint32_t flags;             ///<带有一组驱动程序代码的配置的标志。（例如QPI模式、自动挂起模式、64位地址模式等）
#define SPI_FLASH_HOST_CONTEXT_FLAG_AUTO_SUSPEND         BIT(0)  ///<在配置中设置自动挂起时。
#define SPI_FLASH_HOST_CONTEXT_FLAG_AUTO_RESUME          BIT(1)  ///<设置自动恢复功能。
#define SPI_FLASH_HOST_CONTEXT_FLAG_OCTAL_MODE           BIT(2)  ///<Flash在八进制spi模式下工作。
    spi_flash_sus_cmd_conf sus_cfg;        ///<存储挂起命令/掩码信息。
    uint32_t slicer_flags;      ///切片器标志，用于配置读取或写入时如何正确切片数据。
#define SPI_FLASH_HOST_CONTEXT_SLICER_FLAG_DTR           BIT(0)  ///<根据DTR模式切片数据，地址和长度必须为偶数（A0=0）。
} spi_flash_hal_context_t;
_Static_assert(sizeof(spi_flash_hal_context_t) == 40, "size of spi_flash_hal_context_t incorrect. Please check data compatibility with the ROM");

///此结构提供MSPI Flash所需的时序相关配置，应与“spi_Flash_hal_config_t”中的并集一致。
typedef struct {
    uint32_t extra_dummy;
    uint32_t cs_hold;
    uint8_t cs_setup;
    spi_flash_ll_clock_reg_t clock_config;
} spi_flash_hal_timing_config_t;

///SPI驱动程序的配置结构。
typedef struct {
    union {
        struct {
            uint32_t extra_dummy;   ///<定时补偿的额外虚设。
            uint32_t cs_hold;       ///<主机使用的CS保持时间配置
            uint8_t cs_setup;       ///spi时钟的准备阶段<（周期-1）
            spi_flash_ll_clock_reg_t clock_config;  ///<（可选）八进制闪存的时钟配置。
        };
        spi_flash_hal_timing_config_t timing_reg;  ///<重新配置定时调整规则。
    };
    bool iomux;             ///<是否使用IOMUX，用于定时补偿。
    int input_delay_ns;     ///<启动时钟后MISO引脚上的输入延迟，用于定时补偿。
    esp_flash_speed_t speed;///<SPI闪存时钟速度。
    spi_host_device_t host_id;            ///<SPI外围设备ID。
    int cs_num;             ///<使用哪个cs引脚，0-（SOC_SPI_PERIPH_cs_NUM-1）。
    bool auto_sus_en;       ///<自动暂停功能启用位1：启用，0：禁用。
    bool octal_mode_en;     ///<Octal spi闪存模式启用位1：启用，0：禁用。
    bool using_timing_tuning;               ///<系统存在SPI0/1定时调整，如果设置为1，则直接使用系统中的值。
    esp_flash_io_mode_t default_io_mode;        ///<默认flash io模式。
} spi_flash_hal_config_t;

/**
 * 配置SPI闪存hal设置。
 *
 * @param data 缓冲区用于保存配置的数据，缓冲区应位于DRAM中，以便在缓存禁用时可用
 * @param cfg 要设置的配置
 *
 * @return
 *      -ESP_OK：成功
 *      -ESP_ERR_INVALID_ARG：数据缓冲区不在DRAM中。
 */
esp_err_t spi_flash_hal_init(spi_flash_hal_context_t *data_out, const spi_flash_hal_config_t *cfg);

/**
 * 在事务之前配置与设备相关的寄存器。
 *
 * @param host 驱动程序上下文。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t spi_flash_hal_device_config(spi_flash_host_inst_t *host);

/**
 * 向设备发送用户定义的spi事务。
 *
 * @note 这通常在memspi接口不支持某些特定命令时使用。由于此功能支持定时补偿，因此它还用于在频率较高时接收一些数据。
 *
 * @param host 驱动程序上下文。
 * @param trans 要发送的事务还保存接收的数据。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t spi_flash_hal_common_command(spi_flash_host_inst_t *host, spi_flash_trans_t *trans);

/**
 * 使用擦除芯片（C7h）命令擦除整个闪存芯片。
 *
 * @param host 驱动程序上下文。
 */
void spi_flash_hal_erase_chip(spi_flash_host_inst_t *host);

/**
 * 通过扇区擦除（20h）命令按其起始地址擦除特定扇区。仅适用于24位地址。
 *
 * @param host 驱动程序上下文。
 * @param start_address 要擦除的扇区的起始地址。
 */
void spi_flash_hal_erase_sector(spi_flash_host_inst_t *host, uint32_t start_address);

/**
 * 通过64KB块擦除（D8h）命令按起始地址擦除特定的64KB块。仅适用于24位地址。
 *
 * @param host 驱动程序上下文。
 * @param start_address 要擦除的块的起始地址。
 */
void spi_flash_hal_erase_block(spi_flash_host_inst_t *host, uint32_t start_address);

/**
 * 使用page Program（02h）命令对闪存页面进行编程。仅适用于24位地址。
 *
 * @param host 驱动程序上下文。
 * @param address 要编程的页面地址
 * @param buffer 数据到程序
 * @param length 缓冲区大小（字节），不大于``SPI_FLASH_HAL_MAX_WRITE_bytes``（64）字节。
 */
void spi_flash_hal_program_page(spi_flash_host_inst_t *host, const void *buffer, uint32_t address, uint32_t length);

/**
 * 从闪光灯中读取。在调用此函数之前，调用``spi_flash_hal_configure_host_read_mode``配置读取命令。
 *
 * @param host 驱动程序上下文。
 * @param buffer 用于存储读取数据的缓冲区
 * @param address 要读取的地址
 * @param length 读取长度，不大于``SPI_FLASH_HAL_MAX_read_BYTES``（64）字节。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t spi_flash_hal_read(spi_flash_host_inst_t *host, void *buffer, uint32_t address, uint32_t read_len);

/**
 * @brief 向闪存芯片发送写启用（06h）或写禁用（04h）命令。
 *
 * @param driver 驱动程序上下文。
 * @param wp true启用写保护，否则为false。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t spi_flash_hal_set_write_protect(spi_flash_host_inst_t *host, bool wp);

/**
 * 检查SPI主机是否空闲，是否可以执行其他操作。
 *
 * @param host 驱动程序上下文。
 *
 * @return 0：忙，1：空闲，2：挂起。
 */
uint32_t spi_flash_hal_check_status(spi_flash_host_inst_t *host);

/**
 * @brief 为指定的io模式配置SPI主机硬件寄存器。
 *
 *  请注意，调用此函数将配置SPI主机寄存器，因此如果将任何其他命令作为set_io_mode（）的一部分运行，则必须在调用此函数之前运行这些命令。
 *
 *  根据读取命令的格式配置命令值、地址长度和虚拟周期：
 *
 *  -命令：8位，值设置。
 *  -地址：24位
 *  -dummy：补偿输入延迟的周期
 *  -输出和输入数据：0位。
 *
 *  以下命令仍然需要：
 *
 *  -读取数据：设置地址值和数据（长度和内容），无需触摸命令和虚拟相位。
 *  -普通读取：设置命令值、地址值（如果未使用，则长度为0）
 *  -公共写入：设置命令值、地址值（如果未使用，则长度为0）、禁用虚拟相位并设置输出数据。
 *
 * @param host 驱动程序上下文
 * @param io_mode 要使用的硬件读取模式
 * @param addr_bitlen 地址相位的长度，以位为单位
 * @param dummy_cyclelen_base 伪相位的基本周期，可以附加一些额外的伪周期来补偿定时。
 * @param command  要发送到总线上闪存芯片的实际读取命令。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t spi_flash_hal_configure_host_io_mode(spi_flash_host_inst_t *host, uint32_t command, uint32_t addr_bitlen,
                                               int dummy_cyclelen_base, esp_flash_io_mode_t io_mode);

/**
 * 轮询，直到最后一次操作完成。
 *
 * @param host 驱动程序上下文。
 */
void spi_flash_hal_poll_cmd_done(spi_flash_host_inst_t *host);

/**
 * 检查给定的缓冲区是否可以直接用作写入缓冲区。如果“芯片”连接到主SPI总线，我们只能从禁用缓存的可访问区域直接写入。
 *
 * @param host 驱动程序上下文
 * @param p 保存要发送的数据的缓冲区。
 *
 * @return 如果缓冲区可用于发送数据，则为True，否则为false。
 */
bool spi_flash_hal_supports_direct_write(spi_flash_host_inst_t *host, const void *p);

/**
 * 检查给定的缓冲区是否可以直接用作读取缓冲区。如果“芯片”连接到主SPI总线，我们只能从禁用缓存的情况下可访问的区域直接读取。
 *
 * @param host 驱动程序上下文
 * @param p 保存接收数据的缓冲区。
 *
 * @return 如果缓冲区可用于接收数据，则为True，否则为false。
 */
bool spi_flash_hal_supports_direct_read(spi_flash_host_inst_t *host, const void *p);

/**
 * @brief 从挂起恢复闪存芯片状态。
 *
 * @param host 驱动程序上下文。
 *
 */
void spi_flash_hal_resume(spi_flash_host_inst_t *host);

/**
 * @brief 手动将闪存设置为挂起状态。
 *
 * @param host 驱动程序上下文。
 *
 */
void spi_flash_hal_suspend(spi_flash_host_inst_t *host);

/**
 * 设置读取闪存挂起状态寄存器
 *
 * @param host 驱动程序上下文。
 * @param sus_conf 闪存芯片暂停功能配置（主要用于命令配置）可能因芯片而异。
 *
 * @return 始终ESP_OK
 */
esp_err_t spi_flash_hal_setup_read_suspend(spi_flash_host_inst_t *host, const spi_flash_sus_cmd_conf *sus_conf);

