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

#include <stdint.h>
#include "esp_flash.h"
#include "spi_flash_chip_driver.h"


/*
 * “chip_generic”SPI闪存操作是SPI闪存命令的最低通用子集，可在大多数芯片上工作。
 *
 * 这些函数可以通过esp_flash_common_chip_driver chip_drv原样使用，也可以在创建新的spi_flash_host_driver_t chip_drov结构时用作“基本chip_drf”函数。
 *
 * 此标头中的所有函数都是内部函数，而不是公共API的一部分。请参见esp_flash。h表示公共API。
 */

/**
 * @brief 通用探测功能
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param flash_id 预期的制造商id。
 *
 * @return 如果从chip->drv_read_id读取的id匹配（始终），则返回ESP_OK。
 */
esp_err_t spi_flash_chip_generic_probe(esp_flash_t *chip, uint32_t flash_id);

/**
 * @brief 通用复位功能
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 *
 * @return 如果发送成功，则返回ESP_OK，或从主机驱动程序的`common_command``或`wait_idle``函数传递的错误代码。
 */
esp_err_t spi_flash_chip_generic_reset(esp_flash_t *chip);

/**
 * @brief 通用尺寸检测功能
 *
 * 尝试通过使用芯片的低位4位->drv->read_id result=N来检测芯片的大小，并假设大小为2^N。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param size 检测尺寸的输出
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果制造商id不正确，则ESP_ERR_FLASH_UNSUPPORTED_CHIP可能表示读数错误
 *      -或从主机驱动程序的“read_id”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_detect_size(esp_flash_t *chip, uint32_t *size);

/**
 * @brief 使用通用擦除芯片命令擦除芯片。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -或从主机驱动程序的“set_write_protect”、“wait_idle”或“erase_chip”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_erase_chip(esp_flash_t *chip);

/**
 * @brief 使用通用扇区擦除命令擦除扇区。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param start_address 要擦除的扇区的起始地址
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -或从主机驱动程序的“set_write_protect”、“wait_idle”或“erase_sector”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_erase_sector(esp_flash_t *chip, uint32_t start_address);

/**
 * @brief 通过通用64KB块擦除命令擦除块
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param start_address 要擦除的块的起始地址
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -或从主机驱动程序的“set_write_protect”、“wait_idle”或“erase_block”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_erase_block(esp_flash_t *chip, uint32_t start_address);

/**
 * @brief 使用与编程读取模式匹配的读取命令从闪存读取。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param buffer 保存从闪存读取的数据的缓冲区
 * @param address 闪存上数据的起始地址
 * @param length 要读取的长度
 *
 * @return 当前始终为ESP_OK
 */
esp_err_t spi_flash_chip_generic_read(esp_flash_t *chip, void *buffer, uint32_t address, uint32_t length);

/**
 * @brief 使用页面程序命令执行页面程序。
 *
 * @note 每个调用的长度不应超过“chip->host->max_write_bytes”中的限制。在“spi_flash_chip_generic_write”中递归调用此函数，直到整个页面被编程。强烈建议改为调用``spi_flash_chip_generic_write``。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param buffer 保存要编程的数据的缓冲区
 * @param address 写入闪存的起始地址
 * @param length 写入长度，不超过``chip->host->max_write_bytes``。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -或从主机驱动程序的“wait_idle”或“program_page”函数传递的其他错误
 */
esp_err_t
spi_flash_chip_generic_page_program(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);

/**
 * @brief 执行常规写入。将写缓冲区拆分为页面程序操作，并为每个操作调用chip->chip_drv->page-proprogram（）。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param buffer 保存要编程的数据的缓冲区
 * @param address 写入闪存的起始地址
 * @param length 要写入的长度
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -或从主机驱动程序的“wait_idle”或“program_page”函数传递的其他错误
  */
esp_err_t spi_flash_chip_generic_write(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);

/**
 * @brief 使用片上闪存加密执行写入。尚未实施。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param buffer 保存要编程的数据的缓冲区
 * @param address 写入闪存的起始地址
 * @param length 要写入的长度
 *
 * @return 始终为ESP_ERR_FLASH_UNSUPPORTED_HOST。
 */
esp_err_t
spi_flash_chip_generic_write_encrypted(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);

/**
 * @brief 发送写启用或写禁用命令，并验证状态寄存器中的预期位（1）是否已设置。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param write_protect true表示启用写保护，false表示发送写启用。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -或从主机驱动程序的“wait_idle”、“read_status”或“set_write_protect”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_set_write_protect(esp_flash_t *chip, bool write_protect);

/**
 * @brief 检查从RDSR读取的状态寄存器中是否设置了WEL（写入启用锁存器）位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param out_write_protect 是否设置写保护的输出。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -或从主机驱动程序的“read_status”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_get_write_protect(esp_flash_t *chip, bool *out_write_protect);

#define ESP_FLASH_CHIP_GENERIC_NO_TIMEOUT -1
/**
 * @brief 发送命令以读取芯片的某个寄存器
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param reg_id     要读取的寄存器类型
 * @param out_reg    寄存器值的输出
 * @return esp_err_t从主机驱动程序的“read_status”函数传递的错误代码。
 */
esp_err_t spi_flash_chip_generic_read_reg(esp_flash_t* chip, spi_flash_register_t reg_id, uint32_t* out_reg);

/**
 * @brief 通过RDSR命令读取闪存状态，并等待位0（正在写入的位）被清除。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param timeout_us 在超时前等待的时间，在我们身上。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -ESP_ERR_TIMEOUT（如果超时前未空闲）
 *      -或从主机驱动程序的“wait_idle”或“read_status”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_wait_idle(esp_flash_t *chip, uint32_t timeout_us);

/**
 * @brief 根据芯片上下文中的数据设置指定的SPI读取模式。如果需要，设置四元启用状态寄存器位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 *
 * @return
 *      -ESP_OK（如果成功）
*      -ESP_ERR_TIMEOUT（如果超时前未空闲）
 *      -或从主机驱动程序的“set_write_protect”或“common_command”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_set_io_mode(esp_flash_t *chip);

/**
  * 获取是否设置了Quad Enable（QE）。
  *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param out_quad_mode 用于存储输出模式的指针。
 *          -SPI_FLASH_QOUT:QE已启用
 *          -否则：QE被禁用
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -或从主机驱动程序的“common_command”函数传递的其他错误
  */
esp_err_t spi_flash_chip_generic_get_io_mode(esp_flash_t *chip, esp_flash_io_mode_t* out_quad_mode);

/**
 * @brief 读取芯片唯一ID。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param flash_unique_id 指向存储输出唯一id的指针。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果芯片不支持读取id，则为ESP_ERR_NOT_SUPPORTED。
 */
esp_err_t spi_flash_chip_generic_read_unique_id(esp_flash_t *chip, uint64_t* flash_unique_id);

/**
 * 通用SPI闪存chip_drv使用上述所有功能进行操作。在默认的自动检测中，如果找不到更具体的chip_drv，则将其用作一个陷阱。
 */
extern const spi_flash_chip_t esp_flash_chip_generic;

/*******************************************************************************
 *  公用事业
*******************************************************************************/

///用QE位读取状态寄存器的函数指针类型。
typedef esp_err_t (*esp_flash_rdsr_func_t)(esp_flash_t* chip, uint32_t* out_sr);

/**
 * 使用RDSR2（35H）读取SR的第15-8位，使用RDSR（05H）读取第7-0位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param out_sr 指向保存状态寄存器的缓冲区的指针，16位。
 *
 * @return 如果成功，则返回ESP_OK，否则返回从主机驱动程序的“common_command”函数传递的错误代码。
 */
esp_err_t spi_flash_common_read_status_16b_rdsr_rdsr2(esp_flash_t* chip, uint32_t* out_sr);

/**
 * 使用RDSR2（35H）读取SR的第15-8位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param out_sr 指向保存状态寄存器的缓冲区的指针，8位。
 *
 * @return 如果成功，则返回ESP_OK，否则返回从主机驱动程序的“common_command”函数传递的错误代码。
 */
esp_err_t spi_flash_common_read_status_8b_rdsr2(esp_flash_t* chip, uint32_t* out_sr);

/**
 * 使用RDSR（05H）读取SR的第7-0位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param out_sr 指向保存状态寄存器的缓冲区的指针，8位。
 *
 * @return 如果成功，则返回ESP_OK，否则返回从主机驱动程序的“common_command”函数传递的错误代码。
 */
esp_err_t spi_flash_common_read_status_8b_rdsr(esp_flash_t* chip, uint32_t* out_sr);

///用QE位写入状态寄存器的函数指针类型。
typedef esp_err_t (*esp_flash_wrsr_func_t)(esp_flash_t* chip, uint32_t sr);

/**
 * 使用WRSR（01H）写入SR的第7-0位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param sr 要写入的状态寄存器的值，8位。
 *
 * @return 如果成功，则返回ESP_OK，否则返回从主机驱动程序的“common_command”函数传递的错误代码。
 */
esp_err_t spi_flash_common_write_status_8b_wrsr(esp_flash_t* chip, uint32_t sr);

/**
 * 使用WRSR（01H）写入SR的第15-0位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param sr 要写入的状态寄存器的值，16位。
 *
 * @return 如果成功，则返回ESP_OK，否则返回从主机驱动程序的“common_command”函数传递的错误代码。
 */
esp_err_t spi_flash_common_write_status_16b_wrsr(esp_flash_t* chip, uint32_t sr);

/**
 * 使用WRSR2（31H）写入SR的第15-8位。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param sr 要写入的状态寄存器的值，8位。
 *
 * @return 如果成功，则返回ESP_OK，否则返回从主机驱动程序的“common_command”函数传递的错误代码。
 */
esp_err_t spi_flash_common_write_status_8b_wrsr2(esp_flash_t* chip, uint32_t sr);

/**
 * @brief set_read_mode chip_drv函数的实用函数。如果需要，设置并检查闪存芯片中的QE位，以启用QIO/QOUT模式。
 *
 * 尽管读/写状态寄存器的命令以及QE位的位置可能不同，但大多数芯片QE启用遵循一种通用模式。
 *
 * 还应通过spi_flash_chip_generic_config_host_io_mode（）配置寄存器以实际执行四次转换和读取时发送的命令。
 *
 * 请注意，wrsr_func、rdsr_func和qe_sr_bit的位长度和qe位置应一致。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param wrsr_func 用于写入状态寄存器的函数指针
 * @param rdsr_func 用于读取状态寄存器的函数指针
 * @param qe_sr_bit 状态，仅限qe位。
 *
 * @return 始终为ESP_OK（当前）。
 */
esp_err_t spi_flash_common_set_io_mode(esp_flash_t *chip, esp_flash_wrsr_func_t wrsr_func, esp_flash_rdsr_func_t rdsr_func, uint32_t qe_sr_bit);

/**
 * @brief 配置主机寄存器以使用“chip->read_mode”中设置的指定读取模式。
 *
 * 通常在实际读取事务之前在chip_drv read（）函数中调用。还要准备在读取函数中发送的命令。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param flags 配置io模式的特殊规则（即是否使用32位命令（目前仅支持W25Q256和GD25Q256））
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果芯片未正确初始化，则为ESP_ERR_FLASH_NOT_INITIALISED
 *      -或从主机驱动程序的“configure_host_mode”函数传递的其他错误
 */
esp_err_t spi_flash_chip_generic_config_host_io_mode(esp_flash_t *chip, uint32_t flags);
#define SPI_FLASH_CONFIG_IO_MODE_32B_ADDR BIT(0)

/**
 * @brief 处理显式产量请求
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @param wip  正在进行写入（擦除），如果在擦除/写入命令的等待空闲期间调用此函数，则为“true”；否则为“false”。
 * @return 如果成功，则ESP_OK，否则失败。
 */
esp_err_t spi_flash_chip_generic_yield(esp_flash_t* chip, uint32_t wip);

/**
 * @brief 闪存挂起命令配置的设置。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @return ESP_OK
 */
esp_err_t spi_flash_chip_generic_suspend_cmd_conf(esp_flash_t *chip);

/**
 *
 * @brief 读取芯片唯一ID不支持的功能。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。
 * @param flash_unique_id 用于存储输出唯一id的指针（虽然此函数是不受支持的函数，但应保留参数以保持函数指针的一致性）。
 * @return 始终为ESP_ERR_NOT_SUPPORTED。
 */
esp_err_t spi_flash_chip_generic_read_unique_id_none(esp_flash_t *chip, uint64_t* flash_unique_id);

///大多数芯片使用的默认超时配置
extern const flash_chip_op_timeout_t spi_flash_chip_generic_timeout;

