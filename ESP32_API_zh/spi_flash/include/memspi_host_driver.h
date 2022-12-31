// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#pragma once
#include "hal/spi_flash_hal.h"

/**memspi的默认配置（高速版本）*/
#define ESP_FLASH_DEFAULT_HOST_DRIVER()  (spi_flash_host_driver_t) { \
        .dev_config = spi_flash_hal_device_config, \
        .common_command = spi_flash_hal_common_command, \
        .read_id = memspi_host_read_id_hs, \
        .erase_chip = spi_flash_hal_erase_chip, \
        .erase_sector = spi_flash_hal_erase_sector, \
        .erase_block = spi_flash_hal_erase_block, \
        .read_status = memspi_host_read_status_hs, \
        .set_write_protect = spi_flash_hal_set_write_protect, \
        .supports_direct_write = spi_flash_hal_supports_direct_write, \
        .supports_direct_read = spi_flash_hal_supports_direct_read, \
        .program_page = spi_flash_hal_program_page, \
        .write_data_slicer = memspi_host_write_data_slicer, \
        .read = spi_flash_hal_read, \
        .read_data_slicer = memspi_host_read_data_slicer, \
        .host_status = spi_flash_hal_check_status, \
        .configure_host_io_mode = spi_flash_hal_configure_host_io_mode, \
        .poll_cmd_done = spi_flash_hal_poll_cmd_done, \
        .flush_cache = memspi_host_flush_cache, \
        .check_suspend = NULL, \
        .resume = spi_flash_hal_resume, \
        .suspend = spi_flash_hal_suspend,\
        .sus_setup = spi_flash_hal_setup_read_suspend,\
}

///memspi主机的配置
typedef spi_flash_hal_config_t memspi_host_config_t;
///memspi主机的上下文
typedef spi_flash_hal_context_t memspi_host_inst_t;

/**
 * 初始化内存SPI主机。
 *
 * @param host 指向主机结构的指针。
 * @param cfg 指向配置结构的指针
 *
 * @return 始终返回ESP_OK
 */
esp_err_t memspi_host_init_pointers(memspi_host_inst_t *host, const memspi_host_config_t *cfg);

/*******************************************************************************
 * 注意：此文件的其余部分是HAL层的一部分。HAL不是公共api，不用于应用程序代码。参见hal/include/hal/readme.md中的自述文件
 ******************************************************************************/

/**
 * @brief 读取从RDSR（05h）读取的状态寄存器。
 *
 * 通过memspi接口依靠`common_command``高速实现RDID。
 *
 * @param host 驱动程序上下文。
 * @param id 从设备读取ID的输出。
 *
 * @return
 *  -ESP_OK：如果成功
 *  -ESP_ERR_FLASH_NO_RESPONSE：如果芯片没有响应
 *  -或“spi_halcommon_command”中的其他情况``
 */
esp_err_t memspi_host_read_id_hs(spi_flash_host_inst_t *host, uint32_t *id);

/**
 * 通过memspi接口依靠`common_command``高速实现RDSR。
 *
 * @param host 驱动程序上下文。
 * @param id 从设备读取ID的输出。
 *
 * @return
 *  -ESP_OK：如果成功
 *  -或“spi_halcommon_command”中的其他情况``
 */
esp_err_t memspi_host_read_status_hs(spi_flash_host_inst_t *host, uint8_t *out_sr);

/**
 * 修改内容后刷新缓存（如果需要）。
 *
 * @param host 驱动程序上下文。
 * @param addr 修改区域的起始地址
 * @param size 修改区域的大小。
 *
 * @return 始终为ESP_OK。
 */
esp_err_t memspi_host_flush_cache(spi_flash_host_inst_t *host, uint32_t addr, uint32_t size);

/**
 *  擦除整个芯片的内容。
 *
 * @param host 驱动程序上下文。
 */
void memspi_host_erase_chip(spi_flash_host_inst_t *host);

/**
 *  擦除从给定地址开始的扇区。仅适用于24位地址。
 *
 * @param host 驱动程序上下文。
 * @param start_address 扇区的起始地址。
 */
void memspi_host_erase_sector(spi_flash_host_inst_t *host, uint32_t start_address);

/**
 *  擦除从给定地址开始的块。仅适用于24位地址。
 *
 * @param host 驱动程序上下文。
 * @param start_address 块的起始地址。
 */
void memspi_host_erase_block(spi_flash_host_inst_t *host, uint32_t start_address);

/**
 * 用缓冲区的内容编程页面。仅适用于24位地址。
 *
 * @param host 驱动程序上下文。
 * @param buffer 包含要闪存的数据的缓冲区。
 * @param address 闪存数据的起始地址。
 * @param length 要闪存的字节数。
 */
void memspi_host_program_page(spi_flash_host_inst_t *host, const void *buffer, uint32_t address, uint32_t length);

/**
 * 设置写入芯片的能力。
 *
 * @param host 驱动程序上下文。
 * @param wp 启用或禁用写保护（true-启用，false-禁用）。
 */
esp_err_t memspi_host_set_write_protect(spi_flash_host_inst_t *host, bool wp);

/**
 * 将数据读取到缓冲区。
 *
 * @param host 驱动程序上下文。
 * @param buffer 包含要读取的数据的缓冲区。
 * @param address 读取数据的起始地址。
 * @param length 要读取的字节数。
 */
esp_err_t memspi_host_read(spi_flash_host_inst_t *host, void *buffer, uint32_t address, uint32_t read_len);

/**
 * @brief 用于非加密区域中使用的读取数据的切片器。此切片器仅将长度限制为主机支持的最大大小。
 *
 * @param address 要读取的闪存地址
 * @param len 要读取的长度
 * @param align_address 要读取的地址的输出应等于输入“地址”`
 * @param page_size 物理SPI闪存页面大小
 *
 * @return 实际上可以在“spi_flash_host_driver_t”中的一个“read”调用中读取的长度。
 */
int memspi_host_read_data_slicer(spi_flash_host_inst_t *host, uint32_t address, uint32_t len, uint32_t *align_address, uint32_t page_size);

/**
 * @brief 用于写入非加密区域中使用的数据的切片器。此限幅器将长度限制为主机支持的最大大小，如果写入数据超出页面边界（256字节），则进行截断
 *
 * @param address 要写入的闪存地址
 * @param len 要写入的长度
 * @param align_address 要写入的地址的输出应等于输入地址`
 * @param page_size 物理SPI闪存页面大小
 *
 * @return 实际上可以在“spi_flash_host_driver_t”中的一个“program_page”调用中写入的长度。
 */
int memspi_host_write_data_slicer(spi_flash_host_inst_t *host, uint32_t address, uint32_t len, uint32_t *align_address, uint32_t page_size);

