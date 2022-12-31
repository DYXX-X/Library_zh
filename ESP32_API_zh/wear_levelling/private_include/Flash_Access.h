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


#ifndef _Flash_Access_H_
#define _Flash_Access_H_
#include "esp_err.h"

/**
* @brief 通用闪存访问接口类
*
*/
class Flash_Access
{
public:
    virtual size_t chip_size() = 0;

    virtual esp_err_t erase_sector(size_t sector) = 0;
    virtual esp_err_t erase_range(size_t start_address, size_t size) = 0;

    virtual esp_err_t write(size_t dest_addr, const void *src, size_t size) = 0;
    virtual esp_err_t read(size_t src_addr, void *dest, size_t size) = 0;

    virtual size_t sector_size() = 0;

    virtual esp_err_t flush()
    {
        return ESP_OK;
    };

    virtual ~Flash_Access() {};
};

#endif // _闪存_访问_H_

