// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
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
 * 注意ll不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// SPI闪存加密的低层。

#include <stdbool.h>
#include <string.h>
#include "soc/system_reg.h"
#include "soc/hwcrypto_reg.h"
#include "soc/soc.h"
#include "hal/assert.h"

#ifdef __cplusplus
extern "C" {
#endif

///选择要手动加密的芯片类型
typedef enum
{
    FLASH_ENCRYPTION_MANU = 0, ///!< 手动加密闪存芯片。
    PSRAM_ENCRYPTION_MANU = 1  ///!< 手动加密psram芯片。
} flash_encrypt_ll_type_t;

/**
 * 在spi引导模式和下载引导模式下启用闪存加密功能。
 */
static inline void spi_flash_encrypt_ll_enable(void)
{
    REG_SET_BIT(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG,
                SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT |
                SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT);
}

/*
 * 禁用闪存加密模式。
 */
static inline void spi_flash_encrypt_ll_disable(void)
{
    REG_CLR_BIT(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG,
                SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT);
}

/**
 * 选择要手动加密的芯片类型
 *
 * @param type 要加密的芯片类型
 *
 * @note 硬件当前支持闪存加密。
 */
static inline void spi_flash_encrypt_ll_type(flash_encrypt_ll_type_t type)
{
    // 我们的硬件仅支持闪存加密
    HAL_ASSERT(type == FLASH_ENCRYPTION_MANU);
    REG_WRITE(AES_XTS_DESTINATION_REG, type);
}

/**
 * 配置单个加密的数据大小。
 *
 * @param block_size 所需块的大小。
 */
static inline void spi_flash_encrypt_ll_buffer_length(uint32_t size)
{
    // 所需的块不应大于块大小。
    REG_WRITE(AES_XTS_SIZE_REG, size >> 5);
}

/**
 * 保存32位明文。
 *
 * @param address 写入的闪存分区的地址。
 * @param buffer 用于存储输入数据的缓冲区。
 * @param size 缓冲区大小。
 *
 */
static inline void spi_flash_encrypt_ll_plaintext_save(uint32_t address, const uint32_t* buffer, uint32_t size)
{
    uint32_t plaintext_offs = (address % 64);
    memcpy((void *)(AES_XTS_PLAIN_BASE + plaintext_offs), buffer, size);
}

/**
 * 将闪存地址复制到XTS_AES物理地址
 *
 * @param flash_addr 要写入的闪存地址。
 */
static inline void spi_flash_encrypt_ll_address_save(uint32_t flash_addr)
{
    REG_WRITE(AES_XTS_PHYSICAL_ADDR_REG, flash_addr);
}

/**
 * 启动闪存加密
 */
static inline void spi_flash_encrypt_ll_calculate_start(void)
{
    REG_WRITE(AES_XTS_TRIGGER_REG, 1);
}

/**
 * 等待闪存加密终止
 */
static inline void spi_flash_encrypt_ll_calculate_wait_idle(void)
{
    while(REG_READ(AES_XTS_STATE_REG) == 0x1) {
    }
}

/**
 * 完成闪存加密，并使加密结果可由SPI访问。
 */
static inline void spi_flash_encrypt_ll_done(void)
{
    REG_WRITE(AES_XTS_RELEASE_REG, 1);
    while(REG_READ(AES_XTS_STATE_REG) != 0x3) {
    }
}

/**
 * 设置为销毁加密结果
 */
static inline void spi_flash_encrypt_ll_destroy(void)
{
    REG_WRITE(AES_XTS_DESTROY_REG, 1);
}

/**
 * 检查是否有资格加密缓冲区
 *
 * @param address 写入的闪存分区的地址。
 * @param length 缓冲区大小。
 */
static inline bool spi_flash_encrypt_ll_check(uint32_t address, uint32_t length)
{
    return ((address % length) == 0) ? true : false;
}

#ifdef __cplusplus
}
#endif

