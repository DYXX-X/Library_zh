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

#ifndef _WL_Ext_Safe_H_
#define _WL_Ext_Safe_H_

#include "WL_Flash.h"
#include "WL_Ext_Cfg.h"
#include "WL_Ext_Perf.h"

class WL_Ext_Safe : public WL_Ext_Perf
{
public:
    WL_Ext_Safe();
    ~WL_Ext_Safe() override;

    esp_err_t config(WL_Config_s *cfg, Flash_Access *flash_drv) override;
    esp_err_t init() override;

    size_t chip_size() override;

protected:
    esp_err_t erase_sector_fit(uint32_t start_sector, uint32_t count) override;

    // 转储扇区
    uint32_t dump_addr; // 转储缓冲区地址
    uint32_t state_addr;// 存储事务状态的扇区

    esp_err_t recover();
};

#endif // _WL_外部安全_H_

