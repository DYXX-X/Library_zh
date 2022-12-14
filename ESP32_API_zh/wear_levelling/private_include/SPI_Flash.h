#ifndef _SPI_Flash_H_
#define _SPI_Flash_H_

#include "esp_err.h"
#include "Flash_Access.h"

/**
* @brief 此类用于访问SPI闪存设备。类实现Flash_Access接口
*
*/
class SPI_Flash : public Flash_Access
{

public:
    SPI_Flash();

    size_t chip_size() override;
    esp_err_t erase_sector(size_t sector) override;
    esp_err_t erase_range(size_t start_address, size_t size) override;
    esp_err_t write(size_t dest_addr, const void *src, size_t size) override;
    esp_err_t read(size_t src_addr, void *dest, size_t size) override;
    size_t sector_size() override;
    ~SPI_Flash() override;
};

#endif // _SPI_激光H_

