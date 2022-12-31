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

#include "soc/dport_reg.h"
#include "soc/flash_encryption_reg.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 在闪存中启用加密
 */
static inline void spi_flash_encrypt_ll_enable(void)
{
    DPORT_REG_SET_BIT(DPORT_SLAVE_SPI_CONFIG_REG, DPORT_SLAVE_SPI_MASK_PRO | DPORT_SPI_ENCRYPT_ENABLE);
}

/**
 * 禁用闪存中的加密
 */
static inline void spi_flash_encrypt_ll_disable(void)
{
    DPORT_REG_CLR_BIT(DPORT_SLAVE_SPI_CONFIG_REG, DPORT_SLAVE_SPI_MASK_PRO | DPORT_SPI_ENCRYPT_ENABLE);
}

/**
 * 将闪存地址复制到物理地址
 *
 * @param flash_addr 闪存地址。
 *
 * @note 地址必须是8字节对齐的
 */
static inline void spi_flash_encrypt_ll_address_save(uint32_t flash_addr)
{
    REG_WRITE(FLASH_ENCRYPTION_ADDRESS_REG, flash_addr);
}

/**
 * 等待闪存加密操作完成。
 */
static inline void spi_flash_encrypt_ll_calculate_wait_idle(void)
{
    while(!(REG_READ(FLASH_ENCRYPTION_DONE_REG) & BIT(0))) {
    }
}

/**
 * 开始对数据缓冲区进行加密。
 */
static inline void spi_flash_encrypt_ll_calculate_start(void)
{
    REG_WRITE(FLASH_ENCRYPTION_START_REG, BIT(0));
}

/**
 * 保存明文以进行加密
 *
 * @param address 要写入的分区的地址。
 * @param buffer 用于存储输入数据的缓冲区。
 * @param size 缓冲区大小。
 */
static inline void spi_flash_encrypt_ll_plaintext_save(uint32_t address, const uint32_t* buffer, uint32_t size)
{
    for (int i = 0; i < 8; i++) {
        REG_WRITE(FLASH_ENCRYPTION_BUFFER_REG + (i << 2), buffer[i]);
    }
}

/**
 * 完成闪存加密，并使加密结果可由SPI访问。
 */
static inline void spi_flash_encrypt_ll_done(void)
{
    // 在ESP32上什么都不做
}

/**
 * 设置为销毁加密结果
 */
static inline void spi_flash_encrypt_ll_destroy(void)
{
    // 在ESP32上什么都不做
}

/**
 * 检查是否有资格加密缓冲区
 *
 * @param address 写入的闪存分区的地址。
 * @param length 缓冲区大小。
 */
static inline bool spi_flash_encrypt_ll_check(uint32_t address, uint32_t length)
{
    return ((address % 16) == 0) ? true : false;
}

#ifdef __cplusplus
}
#endif

