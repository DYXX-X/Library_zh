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
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * esp flash内部函数可能返回错误，这些错误代码应与esp_err_t代码一致。但是为了减少源文件对esp_err_t的依赖性，它们使用了这个可替换头中定义的错误代码。此标头应确保与esp_err_t的一致性。
 */

enum {
    /* 这些代码应与esp_err_t错误一致。但是，ESP-IDF中不允许使用相同值的错误代码。这是一种变通方法，以避免在“soc”和“esp_common”组件之间引入依赖关系。缺点是esp_err_to_name（esp_err_FLASH_SIZE_NOT_MATCH）的输出将是esp_err_INVALID_SIZE。*/
    ESP_ERR_FLASH_SIZE_NOT_MATCH = ESP_ERR_INVALID_SIZE,  ///<芯片没有足够的空间用于当前分区表
    ESP_ERR_FLASH_NO_RESPONSE = ESP_ERR_INVALID_RESPONSE, ///<Chip未响应命令，或超时。
};

//ROM代码已经取了1和2，为了避免可能的冲突，从3开始。
#define ESP_ERR_FLASH_NOT_INITIALISED   (ESP_ERR_FLASH_BASE+3) ///<esp_flash_chip_t结构未被esp_flash init（）正确初始化。
#define ESP_ERR_FLASH_UNSUPPORTED_HOST  (ESP_ERR_FLASH_BASE+4) ///<此主机SPI总线（chip->SPI字段）不支持请求的操作。
#define ESP_ERR_FLASH_UNSUPPORTED_CHIP  (ESP_ERR_FLASH_BASE+5) ///<此型号的SPI闪存芯片不支持请求的操作。
#define ESP_ERR_FLASH_PROTECTED         (ESP_ERR_FLASH_BASE+6) ///<由于芯片的写入保护已启用，写入操作失败。

#ifdef __cplusplus
}
#endif

