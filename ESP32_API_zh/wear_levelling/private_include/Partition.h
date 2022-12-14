#ifndef _Partition_H_
#define _Partition_H_

#include "esp_err.h"

#include "Flash_Access.h"
#include "esp_partition.h"

/**
* @brief 此类用于访问分区。类实现Flash_Access接口
*
*/
class Partition : public Flash_Access
{

public:
    Partition(const esp_partition_t *partition);

    virtual size_t chip_size();

    virtual esp_err_t erase_sector(size_t sector);
    virtual esp_err_t erase_range(size_t start_address, size_t size);

    virtual esp_err_t write(size_t dest_addr, const void *src, size_t size);
    virtual esp_err_t read(size_t src_addr, void *dest, size_t size);

    virtual size_t sector_size();

    virtual ~Partition();
protected:
    const esp_partition_t *partition;

};

#endif // _分区_H_

