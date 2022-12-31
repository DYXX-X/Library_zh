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

#ifndef _WL_Ext_Perf_H_
#define _WL_Ext_Perf_H_

#include "WL_Flash.h"
#include "WL_Ext_Cfg.h"

class WL_Ext_Perf : public WL_Flash
{
public:
    WL_Ext_Perf();
    ~WL_Ext_Perf() override;

    esp_err_t config(WL_Config_s *cfg, Flash_Access *flash_drv) override;
    esp_err_t init() override;

    size_t chip_size() override;
    size_t sector_size() override;


    esp_err_t erase_sector(size_t sector) override;
    esp_err_t erase_range(size_t start_address, size_t size) override;

protected:
    uint32_t flash_sector_size;
    uint32_t fat_sector_size;
    uint32_t size_factor;
    uint32_t *sector_buffer;

    virtual esp_err_t erase_sector_fit(uint32_t start_sector, uint32_t count);

};

#endif // _WL_外部_穿孔_H_

