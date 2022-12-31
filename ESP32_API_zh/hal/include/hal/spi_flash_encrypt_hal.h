// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

/*******************************************************************************
 * 注意HAL不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// SPI闪存加密的HAL层

#include "hal/spi_flash_encrypted_ll.h"

/**
 * @brief 启用闪存加密
 */
void spi_flash_encryption_hal_enable(void);

/**
 * @brief 禁用闪存加密
 */
void spi_flash_encryption_hal_disable(void);

/**
 * 操作前准备闪存加密。
 *
 * @param address 写入操作的闪存中的目标地址。
 * @param buffer 编程数据
 * @param size 按程序调整大小。
 *
 * @note 地址和缓冲区必须是8字对齐的。
 */
void spi_flash_encryption_hal_prepare(uint32_t address, const uint32_t* buffer, uint32_t size);

/**
 * @brief 完成闪存数据加密操作。
 */
void spi_flash_encryption_hal_done(void);

/**
 * 销毁加密结果
 */
void spi_flash_encryption_hal_destroy(void);

/**
 * 检查是否有资格加密缓冲区
 *
 * @param address 写入的闪存分区的地址。
 * @param length 缓冲区大小。
 */
bool spi_flash_encryption_hal_check(uint32_t address, uint32_t length);

