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


/**
 * GD（GigaDevice）SPI闪存芯片_drv使用上述所有功能进行操作。在默认的自动检测中，如果找不到更具体的chip_drv，则将其用作一个陷阱。
 *
 * 请注意，这适用于产品ID为40H（GD25Q）和60H（GD25:LQ）的GD芯片。芯片驱动器根据芯片ID使用不同的命令来写入SR2寄存器。对于GD25Q40-GD25Q16芯片和GD25LQ芯片，使用WRSR（01H）命令；而WRSR2（31H）用于GD25Q32-GD25Q127芯片。
 */
esp_err_t spi_flash_chip_gd_probe(esp_flash_t *chip, uint32_t flash_id);
esp_err_t spi_flash_chip_gd_set_io_mode(esp_flash_t *chip);
esp_err_t spi_flash_chip_gd_get_io_mode(esp_flash_t *chip, esp_flash_io_mode_t* out_io_mode);

extern const spi_flash_chip_t esp_flash_chip_gd;

