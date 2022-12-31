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

#include "hal/spi_types.h"
#include "esp_flash.h"

#ifdef __cplusplus
extern "C" {
#endif

///SPI闪存初始化配置
typedef struct {
    spi_host_device_t host_id;      ///<要使用的总线
    int cs_io_num;                  ///<输出CS信号的GPIO引脚
    esp_flash_io_mode_t io_mode;    ///<从闪存读取的IO模式
    esp_flash_speed_t speed;        ///<闪存时钟的速度
    int input_delay_ns;             ///<数据引脚的输入延迟，单位为ns。如果未知，则设置为0。
    /**
     * CS线路ID，当“host_ID”不是SPI1_host或“CONFIG_SPI_FLASH_SHARE_SPI1_BUS”已启用时忽略。在这种情况下，使用的CS线路由SPI总线锁自动分配。
     */
    int cs_id;
} esp_flash_spi_device_config_t;

/**
 *  将SPI闪存设备添加到SPI总线上。
 *
 * 总线应该已经由“spi_bus_initialization”初始化。
 *
 * @param out_chip 用于保存已初始化芯片的指针。
 * @param config 要初始化的芯片的配置。
 *
 * @return
 *      -ESP_ERR_INVALID_ARG:out_chip为NULL，或者配置中的某些字段无效。
 *      -ESP_ERR_NO_MEM:未能为芯片结构分配内存。
 *      -ESP_OK：成功。
 */
esp_err_t spi_bus_add_flash_device(esp_flash_t **out_chip, const esp_flash_spi_device_config_t *config);

/**
 *  从SPI总线上卸下SPI闪存设备。
 *
 * @param chip 要删除的闪存设备。
 *
 * @return
 *      -ESP_ERR_INVALID_ARG:芯片无效。
 *      -ESP_OK：成功。
 */
esp_err_t spi_bus_remove_flash_device(esp_flash_t *chip);

#ifdef __cplusplus
}
#endif

