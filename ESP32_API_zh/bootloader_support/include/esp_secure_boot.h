/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include <esp_err.h>
#include "soc/efuse_periph.h"
#include "esp_image_format.h"
#include "esp_rom_efuse.h"
#include "sdkconfig.h"
#include "esp_rom_crc.h"

#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/efuse.h"
#include "esp32/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/efuse.h"
#include "esp32s2/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/efuse.h"
#include "esp32c3/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/efuse.h"
#include "esp32s3/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/efuse.h"
#include "esp32h2/rom/secure_boot.h"
#endif

#ifdef CONFIG_SECURE_BOOT_V1_ENABLED
#if !defined(CONFIG_SECURE_SIGNED_ON_BOOT) || !defined(CONFIG_SECURE_SIGNED_ON_UPDATE) || !defined(CONFIG_SECURE_SIGNED_APPS)
#error "internal sdkconfig error, secure boot should always enable all signature options"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* 支持安全引导功能。

   可以作为应用程序或引导程序代码的一部分进行编译。
*/

#define ESP_SECURE_BOOT_DIGEST_LEN 32

#ifdef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
#include "esp_efuse.h"
#include "esp_efuse_table.h"
#endif

/** @brief 当前是否在硬件中启用了安全引导？
 *
 * 这意味着从现在起，ROM引导加载程序代码将仅引导经过验证的安全引导加载程序。
 *
 * @return 如果启用了安全引导，则为true。
 */
static inline bool esp_secure_boot_enabled(void)
{
#if CONFIG_IDF_TARGET_ESP32
    #ifdef CONFIG_SECURE_BOOT_V1_ENABLED
        #ifndef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
            return REG_READ(EFUSE_BLK0_RDATA6_REG) & EFUSE_RD_ABS_DONE_0;
        #else
            return esp_efuse_read_field_bit(ESP_EFUSE_ABS_DONE_0);
        #endif
    #elif CONFIG_SECURE_BOOT_V2_ENABLED
        #ifndef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
            return ets_use_secure_boot_v2();
        #else
            return esp_efuse_read_field_bit(ESP_EFUSE_ABS_DONE_1);
        #endif
    #endif
#else
    #ifndef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
        return esp_rom_efuse_is_secure_boot_enabled();
    #else
        return esp_efuse_read_field_bit(ESP_EFUSE_SECURE_BOOT_EN);
    #endif
#endif
    return false; /* menuconfig中未启用安全引导*/
}

/** @brief 从引导加载程序映像生成安全摘要
 *
 * @important 此函数只能从引导加载程序代码中调用。
 *
 * 此功能仅在安全引导V1方案的上下文中使用。
 *
 * 如果尚未为引导加载程序启用安全引导，这将：1）生成安全引导密钥并将其刻录到EFUSE（不启用R/W保护）2）从引导加载程序生成摘要并将其保存到闪存地址0x0
 *
 * 如果在调用此函数之后但在调用esp_secure_boot_permanently_enable（）之前第一次启动被中断，则不会重新生成EFUSE上烧录的密钥，除非使用espefuse手动完成。py工具
 *
 * @return 如果安全引导摘要已成功生成或发现已存在，则ESP_OK
 */
esp_err_t esp_secure_boot_generate_digest(void);

/** @brief 如果尚未启用安全引导V1，请启用它。
 *
 * @important 如果此功能成功，则通过efuse在芯片上永久启用安全引导V1。
 *
 * @important 此函数只能从引导加载程序代码中调用。
 *
 * @important 在安全引导V1的情况下，这将启用EFUSE上的安全引导密钥的r/w保护，因此必须确保在此之前调用esp_Secure_Boot_generate_edigest（）。如果尚未为引导加载程序启用安全引导，则这将1）启用EFUSE上的安全启动密钥的r/w保护2）通过吹扫EFUSE_RD_ABS_DONE_0 EFUSE来启用安全引导。
 *
 * 此函数不会验证引导加载程序的安全引导（ROM引导加载程序会执行此操作）
 *
 * 如果efuse被部分烧毁，表明安全引导不应或无法正确启用，则将失败。
 *
 * @return 如果efuse状态不允许完全启用安全引导，则返回ESP_ERR_INVALID_STATE。ESP_OK（如果从现在起在该芯片上启用了安全引导）。
 */
esp_err_t esp_secure_boot_permanently_enable(void);

/** @brief 启用安全引导V2（如果尚未启用）。
 *
 * @important 如果此功能成功，则通过efuse在芯片上永久启用安全引导V2。
 *
 * @important 此函数只能从引导加载程序代码中调用。
 *
 * @important 在安全引导V2的情况下，这将启用BLK2中EFUSE上的安全引导密钥的写入保护。如果尚未为引导加载程序启用安全引导，这将1）启用EFUSE_RD_ABS_DONE_1 EFUSE上的安全启动密钥的W保护。
 *
 * 此函数不会验证引导加载程序的安全引导（ROM引导加载程序会执行此操作）
 *
 * @param image_data 要加载的应用程序的图像元数据。
 *
 * 如果efuse被部分烧毁，表明安全引导不应或无法正确启用，则将失败。
 *
 * @return 如果efuse状态不允许完全启用安全引导，则返回ESP_ERR_INVALID_STATE。ESP_OK（如果从现在起在该芯片上启用了安全引导）。
 */
esp_err_t esp_secure_boot_v2_permanently_enable(const esp_image_metadata_t *image_data);

/** @brief 验证附加到闪存中某些二进制数据的安全引导签名。
 *
 * 对于ECDSA方案（安全引导V1）-带SHA256映像的确定性ECDSA对于RSA方案（安全启动V2）-SHA-256映像的RSA-PSS验证
 *
 * 公钥被编译成ECDSA方案中的调用程序。有关详细信息，请参阅apt-docs/security/secure-boot-v1.rst或docs/security/secure-boot-v2.rst。
 *
 * @param src_addr 闪存中数据的起始偏移量。
 * @param length 数据长度（字节）。签名附加在长度字节之后。
 *
 * 如果启用了闪存加密，则在验证图像时将对其进行透明解密。
 *
 * @note 此函数没有任何故障注入阻力，因此在安全引导过程中不应调用（但可以在验证更新等时调用）
 *
 * @return 如果签名有效，则ESP_OK；如果签名失败，则ESP_ERR_INVALID_STATE；如果其他失败（即无法读取闪存），则ESP_FAIL。
 */
esp_err_t esp_secure_boot_verify_signature(uint32_t src_addr, uint32_t length);

/** @brief 闪存数据格式的安全引导验证块。*/
typedef struct {
    uint32_t version;
    uint8_t signature[64];
} esp_secure_boot_sig_block_t;

/** @brief 验证secure boot V1的ECDSA安全引导签名块。
 *
 *  基于图像的SHA256哈希计算具有SHA256的确定性ECDSA。要使用此功能，必须在项目配置中启用ECDSA签名验证。
 *
 * 类似于esp_secure_boot_verify_signature（），但可以在预先计算摘要时使用。
 * @param sig_block 指向ECDSA签名块数据的指针
 * @param image_digest 指向保存SHA-256哈希的32字节缓冲区的指针。
 * @param verified_digest 指向32字节缓冲区的指针，如果验证完成，该缓冲区将接收经过验证的摘要。（仅在引导加载程序实现期间使用，否则结果无效。）
 *
 */
esp_err_t esp_secure_boot_verify_ecdsa_signature_block(const esp_secure_boot_sig_block_t *sig_block, const uint8_t *image_digest, uint8_t *verified_digest);

#if !CONFIG_IDF_TARGET_ESP32 || CONFIG_ESP32_REV_MIN_3
/**
 * @brief 结构，用于保存从单个图像的签名块计算的公钥摘要。
 *
 * 每个图像可以有一个或多个签名块（最多SECURE_BOOT_NUM_blocks）。每个签名块包括一个公钥。
 */
typedef struct {
    uint8_t key_digests[SECURE_BOOT_NUM_BLOCKS][ESP_SECURE_BOOT_DIGEST_LEN];    /* 签名块中公钥组件的SHA*/
    unsigned num_digests;                                       /* 从索引0开始的有效摘要数*/
} esp_image_sig_public_key_digests_t;

/** @brief 验证secure boot V2的RSA安全引导签名块。
 *
 *  根据签名块中的公钥与efuse中存储的公钥摘要进行比较，对SHA-256图像执行RSA-PSS验证。
 *
 * 类似于esp_secure_boot_verify_signature（），但可以在预先计算摘要时使用。
 * @param sig_block 指向RSA签名块数据的指针
 * @param image_digest 指向保存SHA-256哈希的32字节缓冲区的指针。
 * @param verified_digest 指向32字节缓冲区的指针，如果验证完成，该缓冲区将接收经过验证的摘要。（仅在引导加载程序实现期间使用，否则结果无效。）
 *
 */
esp_err_t esp_secure_boot_verify_rsa_signature_block(const ets_secure_boot_signature_t *sig_block, const uint8_t *image_digest, uint8_t *verified_digest);
#endif // !CONFIG_IDF_TARGET_ESP32 || CONFIG_ESP32_REV_MIN_3

/** @brief 传统ECDSA验证功能
 *
 * @note 不推荐，请调用esp_secure_boot_verify_ecdsa_signature_block（）或esp_secure_boot_verify _rsa_signiture_block（）。
 *
 * @param sig_block 指向ECDSA签名块数据的指针
 * @param image_digest 指向保存SHA-256哈希的32字节缓冲区的指针。
 */
esp_err_t esp_secure_boot_verify_signature_block(const esp_secure_boot_sig_block_t *sig_block, const uint8_t *image_digest)
    __attribute__((deprecated("use esp_secure_boot_verify_ecdsa_signature_block instead")));


#define FLASH_OFFS_SECURE_BOOT_IV_DIGEST 0

/** @brief 安全引导IV+摘要标题*/
typedef struct {
    uint8_t iv[128];
    uint8_t digest[64];
} esp_secure_boot_iv_digest_t;

/** @brief 启动期间检查安全引导V2
 *
 * @note 此函数在应用程序启动期间自动调用，无需从应用程序调用。
 *
 * 在启动期间验证安全启动配置：
 *
 * -更正任何不安全的安全启动设置
 */
void esp_secure_boot_init_checks(void);

#if !BOOTLOADER_BUILD && CONFIG_SECURE_SIGNED_APPS_RSA_SCHEME

/** @brief 扫描当前运行的应用程序以查找签名块
 *
 * @note 此函数不验证签名是否有效或相应的公钥是否可信，它只读取存在的签名块的数量，并可选地计算签名块中提供的公钥的摘要。
 *
 * @param digest_public_keys 如果为true，则public_key_digests结构中的key_digents字段将填充每个签名块中提供的公钥摘要。请注意，如果启用了Secure Boot V2，则只有当eFuse中也存在相同的摘要时，每个公钥才会被信任（但此功能不检查）。
 *
 * @param public_key_digests[out] 结构初始化时，num_digests字段设置为找到的签名数。如果设置了digest_public_keys，则还会计算并存储公钥摘要。
 *
 * @return
 *  -ESP_OK-至少找到一个签名
 *  -ESP_ERR_NOT_FOUND-未找到签名，num_digests值将为零
 *  -ESP_FAIL-尝试从闪存读取签名块时出错
 */
esp_err_t esp_secure_boot_get_signature_blocks_for_running_app(bool digest_public_keys, esp_image_sig_public_key_digests_t *public_key_digests);

#endif // !BOOTLOADER_BUILD && CONFIG_SECURE_SIGNED_APPS_RSA_SCHEME

/** @brief 设置与secure_boot相关的所有安全eFuse功能
 *
 * @return
 *  -ESP_OK-成功
 */
esp_err_t esp_secure_boot_enable_secure_features(void);

#ifdef __cplusplus
}
#endif

