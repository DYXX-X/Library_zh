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

#ifndef _WL_Flash_H_
#define _WL_Flash_H_

#include "esp_err.h"
#include "Flash_Access.h"
#include "WL_Config.h"
#include "WL_State.h"

/**
* @brief 该类用于对闪光装置进行磨损校正。类实现Flash_Access接口
*
*/
class WL_Flash : public Flash_Access
{
public :
    WL_Flash();
    ~WL_Flash() override;

    virtual esp_err_t config(wl_config_t *cfg, Flash_Access *flash_drv);
    virtual esp_err_t init();

    size_t chip_size() override;
    size_t sector_size() override;


    esp_err_t erase_sector(size_t sector) override;
    esp_err_t erase_range(size_t start_address, size_t size) override;

    esp_err_t write(size_t dest_addr, const void *src, size_t size) override;
    esp_err_t read(size_t src_addr, void *dest, size_t size) override;

    esp_err_t flush() override;

    Flash_Access *get_drv();
    wl_config_t *get_cfg();

protected:
    bool configured = false;
    bool initialized = false;
    wl_state_t state;
    wl_config_t cfg;
    Flash_Access *flash_drv = NULL;

    size_t addr_cfg;
    size_t addr_state1;
    size_t addr_state2;
    size_t index_state1;
    size_t index_state2;

    size_t flash_size;
    uint32_t state_size;
    uint32_t cfg_size;
    uint8_t *temp_buff = NULL;
    size_t dummy_addr;
    uint32_t pos_data[4];

    esp_err_t initSections();
    esp_err_t updateWL();
    esp_err_t recoverPos();
    size_t calcAddr(size_t addr);

    esp_err_t updateVersion();
    esp_err_t updateV1_V2();
    void fillOkBuff(int n);
    bool OkBuffSet(int n);
};

#endif // _WL_激光H_

