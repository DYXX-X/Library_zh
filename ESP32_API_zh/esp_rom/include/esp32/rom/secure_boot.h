/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include "sdkconfig.h"

#pragma once

#include <stdint.h>
#include "ets_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

void ets_secure_boot_start(void);

void ets_secure_boot_finish(void);

void ets_secure_boot_hash(const uint32_t *buf);

void ets_secure_boot_obtain(void);

int ets_secure_boot_check(uint32_t *buf);

void ets_secure_boot_rd_iv(uint32_t *buf);

void ets_secure_boot_rd_abstract(uint32_t *buf);

bool ets_secure_boot_check_start(uint8_t abs_index, uint32_t iv_addr);

int ets_secure_boot_check_finish(uint32_t *abstract);

#ifdef CONFIG_ESP32_REV_MIN_3
#include "rsa_pss.h"

#define SECURE_BOOT_NUM_BLOCKS 1

#define CRC_SIGN_BLOCK_LEN 1196
#define SIG_BLOCK_PADDING 4096
#define ETS_SECURE_BOOT_V2_SIGNATURE_MAGIC 0xE7

// 反FI措施：内部使用完整的成功/失败词，而不是0/非零
typedef enum {
    SBV2_SUCCESS = 0x3A5A5AA5,
    SB_SUCCESS   = 0x3A5A5AA5,
    SBV2_FAILED = 0xA533885A,
    SB_FAILED   = 0xA533885A,
} secure_boot_v2_status_t;

/* ESP32 ECO3的Secure Boot版本2签名格式*/
typedef struct {
    uint8_t magic_byte;
    uint8_t version;
    uint8_t _reserved1;
    uint8_t _reserved2;
    uint8_t image_digest[32];
    ets_rsa_pubkey_t key;
    uint8_t signature[384];
    uint32_t block_crc;
    uint8_t _padding[16];
} ets_secure_boot_sig_block_t;
_Static_assert(sizeof(ets_secure_boot_sig_block_t) == 1216, "invalid sig block size");

/* ROM最多支持3个，但IDF只检查第一个（SECURE_BOOT_NUM_BLOCKS）*/
#define SECURE_BOOT_MAX_APPENDED_SIGN_BLOCKS_TO_IMAGE 3

/* 多键块支持*/
typedef struct {
    ets_secure_boot_sig_block_t block[SECURE_BOOT_MAX_APPENDED_SIGN_BLOCKS_TO_IMAGE];
    uint8_t _padding[4096 - (sizeof(ets_secure_boot_sig_block_t) * SECURE_BOOT_MAX_APPENDED_SIGN_BLOCKS_TO_IMAGE)];
} ets_secure_boot_signature_t;

_Static_assert(sizeof(ets_secure_boot_signature_t) == 4096, "invalid sig sector size");

typedef struct {
    const void *key_digests[SECURE_BOOT_NUM_BLOCKS];
} ets_secure_boot_key_digests_t;

/** @brief 验证附加到固件映像的签名块。在ROM中实现。
 *
 * 此函数用于在将其公钥哈希写入Efuse之前验证引导加载程序。此外，它还用于在启动和OTA上加载图像时验证应用程序。
 *
 * @param sig 签名块从固件闪存对齐4096字节。（ROM实现需要3个块，sig->块[3]）。
 * @param image_digest 要验证的固件的SHA-256摘要
 * @param trusted_key_digest 单个签名块的公钥（ets_rsa_bkey_t）的SHA-256摘要。
 * @param verified_digest image_digest的RSA-PSS签名。传递未初始化的数组。
 *
 * @return SBV2_SUCCESS，如果签名对于失败有效SBV2_FAILED。
 */
secure_boot_v2_status_t ets_secure_boot_verify_signature(const ets_secure_boot_signature_t *sig, const uint8_t *image_digest, const uint8_t *trusted_key_digest, uint8_t *verified_digest);

/** @brief 此函数用于验证第一阶段引导加载程序。在ROM中实现。验证后重新启动。它读取Efuse密钥以验证公钥。
 *
 * 当前工作流中未使用此功能。
 *
 */
void ets_secure_boot_verify_boot_bootloader(void);

/** @brief 确认安全引导V2是否已启用。在ROM中实现。
 *
 * 在ESP32-ECO3中-检查EFuse中ABS_DONE_1的值。
 *
 * @return 如果已启用安全引导v2，则为true如果未启用安全引导v2，则为False。
 */
bool ets_use_secure_boot_v2(void);

#else
#define SECURE_BOOT_NUM_BLOCKS 0

#endif /* CONFIG_ESP32_REV_MIN_3 */

#ifdef __cplusplus
}
#endif

