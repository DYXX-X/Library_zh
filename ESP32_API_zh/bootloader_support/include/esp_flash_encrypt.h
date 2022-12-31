/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include "esp_attr.h"
#include "esp_err.h"
#ifndef BOOTLOADER_BUILD
#include "esp_spi_flash.h"
#endif
#include "soc/efuse_periph.h"
#include "sdkconfig.h"

#ifdef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
#include "esp_efuse.h"
#include "esp_efuse_table.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* @brief 基于efuse值的Flash加密模式
*/
typedef enum {
    ESP_FLASH_ENC_MODE_DISABLED,          // 未启用闪存加密（闪存密码cnt=0）
    ESP_FLASH_ENC_MODE_DEVELOPMENT,       // 闪存加密已启用，但用于开发（允许通过UART刷新）
    ESP_FLASH_ENC_MODE_RELEASE            // 已为Release启用闪存加密（禁用UART上的刷新）
} esp_flash_enc_mode_t;

/**
 * @file esp_partition.h
 * @brief 支持闪存加密功能
 *
 * 可以作为应用程序或引导程序代码的一部分进行编译。
 */

/** @brief 当前是否在硬件中启用了闪存加密？
 *
 * 如果Flash_CRYPT_CNT efuse设置了奇数位，则启用闪存加密。
 *
 * @return 如果启用了闪存加密，则为true。
 */
static inline /**@秒*/ IRAM_ATTR /**@结束秒*/ bool esp_flash_encryption_enabled(void)
{
    uint32_t flash_crypt_cnt = 0;
#if CONFIG_IDF_TARGET_ESP32
    #ifndef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
        flash_crypt_cnt = REG_GET_FIELD(EFUSE_BLK0_RDATA0_REG, EFUSE_RD_FLASH_CRYPT_CNT);
    #else
        esp_efuse_read_field_blob(ESP_EFUSE_FLASH_CRYPT_CNT, &flash_crypt_cnt, ESP_EFUSE_FLASH_CRYPT_CNT[0]->bit_count);
    #endif
#else
    #ifndef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
        flash_crypt_cnt = REG_GET_FIELD(EFUSE_RD_REPEAT_DATA1_REG, EFUSE_SPI_BOOT_CRYPT_CNT);
    #else
        esp_efuse_read_field_blob(ESP_EFUSE_SPI_BOOT_CRYPT_CNT, &flash_crypt_cnt, ESP_EFUSE_SPI_BOOT_CRYPT_CNT[0]->bit_count);
    #endif
#endif
    /* __内置parity在flash中，因此我们内联计算奇偶校验*/
    bool enabled = false;
    while (flash_crypt_cnt) {
        if (flash_crypt_cnt & 1) {
            enabled = !enabled;
        }
        flash_crypt_cnt >>= 1;
    }
    return enabled;
}

/* @brief 设备闪存加密更新
 *
 * 如果在设备菜单配置中启用了闪存加密，则作为引导加载程序过程的一部分调用。
 *
 * 如果FLASH_CRYPT_CNT efuse奇偶校验为1（即设置的位数为奇数），则立即返回ESP_OK（表示闪存加密已启用且功能正常）。
 *
 * 如果FLASH_CRYPT_CNT有效奇偶校验为0（即设置了偶数位），则假设闪存刚刚用需要加密的明文写入。
 *
 * 闪存的以下区域已就地加密：
 *
 * -如果找到有效的明文映像，则为引导加载程序映像。[*]
 * -分区表（如果找到有效的明文表）。
 * -包含有效明文应用程序映像的任何应用程序分区。
 * -设置了“encrypt”标志的任何其他分区。[**]
 *
 * 重新加密过程完成后，将“1”位添加到FLASH_CRYPT_CNT值（将奇偶校验设置为1），并重新烧录EFUSE。
 *
 * [*]如果在启用安全引导的情况下重新刷新引导加载程序，请在将引导加载程序写入闪存之前对其进行预加密，否则安全引导将失败。
 *
 * [**]因此，如果在启用安全引导的情况下串行重新闪存先前的闪存设备，并使用FLASH_CRYPT_CNT触发重新加密，则必须同时将明文内容重新闪存到设置了“encrypt”标志的所有分区，否则此数据将损坏（加密两次）。
 *
 * @note 该函数的后置条件是所有应该加密的分区都被加密。
 *
 * @note 在运行此功能时，请注意不要关闭设备电源，否则当前正在加密的分区将丢失。
 *
 * @note 在执行加密操作时，RTC_WDT将重置（如果配置了RTC_WDT）。
 *
 * @return 如果所有操作都成功，则为ESP_OK；如果在加密所有分区期间发生致命错误，则为ESP _ERR_INVALID_STATE。
 */
esp_err_t esp_flash_encrypt_check_and_update(void);


/** @brief 就地加密闪存扇区块
 *
 * @note 此函数用于在带扇区的操作之间重置RTC_WDT。
 * @param src_addr 闪存中的源偏移。应为4096字节的倍数。
 * @param data_length 要加密的数据长度（字节）。将舍入为4096字节的下一个倍数。
 *
 * @return 如果所有操作都成功，则ESP_OK；如果SPI闪存失败，则ESP_ERR_FLASH_OP_FAIL；如果闪存超时，则ESP-ERR_FLASH-OP_TIMEOUT。
 */
esp_err_t esp_flash_encrypt_region(uint32_t src_addr, size_t data_length);

/** @brief 写保护FLASH_CRYPT_CNT
 *
 * 如果启用了闪存加密但未使用安全引导，则作为引导过程的一部分调用。这应防止在没有安全引导的情况下，未经授权代码的串行重新闪烁。
 *
 * @note 仅在ESP32 V3上，写保护FLASH_CRYPT_CNT也将阻止禁用UART下载模式。如果两者都需要，请在调用此函数之前调用esp_efuse_sable_rom_download_mode（）。
 *
 */
void esp_flash_write_protect_crypt_cnt(void);

/** @brief 返回闪存加密模式
 *
 * 该API在引导过程中调用，但也可以由应用程序调用，以检查ESP32的当前闪存加密模式
 *
 * @return
 */
esp_flash_enc_mode_t esp_get_flash_encryption_mode(void);


/** @brief 启动期间检查闪存加密模式
 *
 * @note 此函数在应用程序启动期间自动调用，无需从应用程序调用。
 *
 * 在启动期间验证闪存加密配置：
 *
 * -如果启用了硬件安全引导，请更正任何不安全的闪存加密设置。
 * -如果efuse配置与项目配置在任何方面都不匹配，则记录警告
 */
void esp_flash_encryption_init_checks(void);

/** @brief 设置与闪存加密相关的所有安全eFuse功能
 *
 * @return
 *  -ESP_OK-成功
 */
esp_err_t esp_flash_encryption_enable_secure_features(void);

/** @brief 将Flash加密从“开发”切换到“发布”
 *
 * 如果已经处于“释放”模式，该功能将不起作用。如果闪存加密efuse尚未启用，则中止。它燃烧：
 *  -“在dl模式下禁用加密”
 *  -将FLASH_CRYPT_CNT efuse设置为最大值
 */
void esp_flash_encryption_set_release_mode(void);

#ifdef __cplusplus
}
#endif

