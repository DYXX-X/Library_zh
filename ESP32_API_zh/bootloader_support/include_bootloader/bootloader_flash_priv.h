/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BOOTLOADER_FLASH_H
#define __BOOTLOADER_FLASH_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <esp_err.h>
#include <esp_spi_flash.h> /* 在bootloader中包含错误值*/
#include "sdkconfig.h"
#include "bootloader_flash.h"

#define FLASH_SECTOR_SIZE 0x1000
#define FLASH_BLOCK_SIZE 0x10000
#define MMAP_ALIGNED_MASK 0x0000FFFF

/* SPI命令（实际在线命令而非SPI控制器位掩码）适用于bootloader_execute_flash_command静态函数。
*/
#define CMD_RDID       0x9F
#define CMD_WRSR       0x01
#define CMD_WRSR2      0x31 /* 并非所有SPI闪存都使用此命令*/
#define CMD_WREN       0x06
#define CMD_WRDI       0x04
#define CMD_RDSR       0x05
#define CMD_RDSR2      0x35 /* 并非所有SPI闪存都使用此命令*/
#define CMD_OTPEN      0x3A /* 启用OTP模式，并非所有SPI闪存都使用此命令*/
#define CMD_RDSFDP     0x5A /* 读取闪存的SFDP*/
#define CMD_WRAP       0x77 /* 使用换行命令设置突发*/
#define CMD_RESUME     0x7A /* 清除闪存暂停位的恢复命令*/


/* 为bootloader_support代码提供Flash API，可从bootloader或应用程序代码中使用。

   此标头仅可用于bootloader和bootloader_support组件中的源代码。
*/

/**
 * @brief 获取可用页数
 *
 * @return 可用页数
 */
uint32_t bootloader_mmap_get_free_pages(void);

/**
 * @brief 将闪存区域映射到数据存储器
 *
 * @important 在bootloader代码中，一次只能对一个区域进行bootloader_mmap。在映射另一个区域之前，必须先对上一个区域进行bootloader_munmap。
 *
 * @important 在应用程序代码中，这些函数不是线程安全的。
 *
 * 每次成功调用bootloader_mmap时，调用一次bootloader_munmap。
 *
 * 在esp-idf应用程序中，此函数直接映射到spi_flash_map。
 *
 * @param offset -启动闪存偏移以映射到内存。
 * @param length -要映射的数据长度。
 *
 * @return 指向映射数据内存（位于src_addr）的指针，如果发生分配错误，则返回NULL。
 */
const void *bootloader_mmap(uint32_t src_addr, uint32_t size);


/**
 * @brief 取消映射先前映射的闪存区域
 *
 * 每次成功调用bootloader_mmap时，调用一次bootloader_munmap。
 */
void bootloader_munmap(const void *mapping);

/**
 * @brief  从Flash读取数据。
 *
 *
 * @note 所有src、dest和size必须对齐4字节。
 *
 * @param  src   Flash中数据的源地址。
 * @param  dest  指向目标缓冲区的指针
 * @param  size  数据长度
 * @param  allow_decrypt 如果为true并且启用了闪存加密，则闪存上的数据将作为读取的一部分被透明地解密。
 *
 * @return 成功时ESP_OK，SPI失败时ESP_ERR_FLASH_OP_FAIL，SPI超时时ESP_ERR _FLASH_OP _TIMEOUT。
 */
esp_err_t bootloader_flash_read(size_t src_addr, void *dest, size_t size, bool allow_decrypt);


/**
 * @brief  将数据写入闪存。
 *
 * @note dest_addr、src和size都必须对齐4字节。如果设置了write_encrypted，dest_addr和size必须对齐32字节。
 *
 * 注意：在bootloader中，当write_encrypted==true时，src缓冲区将被加密。
 *
 * @param  dest_addr 要写入闪存的目标地址。
 * @param  src 指向要写入闪存的数据的指针
 * @param  size 数据长度（字节）。
 * @param  write_encrypted 如果为真，数据将被加密写入闪存。
 *
 * @return 成功时ESP_OK，SPI失败时ESP_ERR_FLASH_OP_FAIL，SPI超时时ESP_ERR _FLASH_OP _TIMEOUT。
 */
esp_err_t bootloader_flash_write(size_t dest_addr, void *src, size_t size, bool write_encrypted);

/**
 * @brief  擦除闪存扇区。
 *
 * @param  sector  扇区号，计数从扇区0开始，每个扇区4KB。
 *
 * @return 电子邮箱地址
 */
esp_err_t bootloader_flash_erase_sector(size_t sector);

/**
 * @brief  清除Flash范围。
 *
 * @param  start_addr 闪存偏移的起始地址
 * @param  size       要擦除的扇区对齐大小
 *
 * @return 电子邮箱地址
 */
esp_err_t bootloader_flash_erase_range(uint32_t start_addr, uint32_t size);

/* 缓存MMU块大小*/
#define MMU_BLOCK_SIZE    0x00010000

/* 缓存MMU地址掩码（MMU表忽略零位）*/
#define MMU_FLASH_MASK    (~(MMU_BLOCK_SIZE - 1))

/**
 * @brief 计算要映射的缓存页数
 * @param size  要映射的数据大小
 * @param vaddr  将映射数据的虚拟地址
 * @return 执行映射所需的缓存MMU页数
 */
static inline uint32_t bootloader_cache_pages_to_map(uint32_t size, uint32_t vaddr)
{
    return (size + (vaddr - (vaddr & MMU_FLASH_MASK)) + MMU_BLOCK_SIZE - 1) / MMU_BLOCK_SIZE;
}

/**
 * @brief 在闪存上执行用户命令
 *
 * @param command 要执行的命令值。
 * @param mosi_data 要发送的MOSI数据
 * @param mosi_len MOSI数据长度，以位为单位
 * @param miso_len 要接收的MISO数据长度，以位为单位
 * @return 收到MISO数据
 */
uint32_t bootloader_execute_flash_command(uint8_t command, uint32_t mosi_data, uint8_t mosi_len, uint8_t miso_len);

/**
 * @brief 读取闪存的SFDP
 *
 * @param sfdp_addr 要读取的参数的地址
 * @param miso_byte_num 要读取的字节数
 * @return 读取的SFDP，小端，最多4字节
 */
uint32_t bootloader_flash_read_sfdp(uint32_t sfdp_addr, unsigned int miso_byte_num);

/**
 * @brief 启用闪存写入保护（WEL位）。
 */
void bootloader_enable_wp(void);

#endif

