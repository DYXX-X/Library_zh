// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

#ifndef _SpiFlash_H_
#define _SpiFlash_H_

#include <stdbool.h>

#include "esp_err.h"
#include "esp32/rom/spi_flash.h"

/**
* @brief 此类用于模拟闪存设备。
*
*/
class SpiFlash
{

public:
    SpiFlash();
    ~SpiFlash();

    void init(uint32_t chip_size, uint32_t block_size, uint32_t sector_size, uint32_t page_size, const char* partitions_bin);

    uint32_t get_chip_size();
    uint32_t get_block_size();
    uint32_t get_sector_size();
    uint32_t get_page_size();

    esp_rom_spiflash_result_t erase_block(uint32_t block);
    esp_rom_spiflash_result_t erase_sector(uint32_t sector);
    esp_rom_spiflash_result_t erase_page(uint32_t page);

    esp_rom_spiflash_result_t write(uint32_t dest_addr, const void *src, uint32_t size);
    esp_rom_spiflash_result_t read(uint32_t src_addr, void *dest, uint32_t size);

    uint32_t get_erase_cycles(uint32_t sector);
    uint32_t get_total_erase_cycles();

    void set_erase_cycles_limit(uint32_t limit);
    void set_total_erase_cycles_limit(uint32_t limit);

    void reset_erase_cycles();
    void reset_total_erase_cycles();

    uint8_t* get_memory_ptr(uint32_t src_address);

private:
    uint32_t chip_size;
    uint32_t block_size;
    uint32_t sector_size;
    uint32_t page_size;

    uint32_t blocks;
    uint32_t sectors;
    uint32_t pages;

    uint8_t* memory;

    bool* erase_states;

    uint32_t* erase_cycles;
    uint32_t erase_cycles_limit;
    uint32_t total_erase_cycles;
    uint32_t total_erase_cycles_limit;

    void deinit();
};

#endif // _闪烁_H_

