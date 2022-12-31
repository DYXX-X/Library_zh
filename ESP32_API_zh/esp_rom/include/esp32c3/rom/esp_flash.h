// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 注意：ROM中的大多数esp_flash API都与esp-IDF中的头文件兼容，该函数只是添加了ROM特定的部分
*/

struct spi_flash_chip_t;
typedef struct esp_flash_t esp_flash_t;

/* 将esp_flash使用的“全局”数据包装在ROM中的结构*/
typedef struct {
    /* 默认SPI闪存芯片，即连接到MCU的主芯片如果传递给esp_flash_xxx API函数的“chip”参数始终为NULL，则使用该芯片
    */
    esp_flash_t *default_chip;

    /* 全局API OS通知开始/结束/chip_check函数

       如果未配置其他主机功能，ROM将使用这些功能。
    */
    struct {
        esp_err_t (*start)(esp_flash_t *chip);
        esp_err_t (*end)(esp_flash_t *chip, esp_err_t err);
        esp_err_t (*chip_check)(esp_flash_t **inout_chip);
    } api_funcs;
} esp_flash_rom_global_data_t;

/** 访问ROM spi_flash驱动程序使用的全局数据指针
 */
esp_flash_rom_global_data_t *esp_flash_get_rom_global_data(void);

#ifdef __cplusplus
}
#endif

