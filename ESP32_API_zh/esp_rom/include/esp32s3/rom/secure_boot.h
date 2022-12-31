/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "ets_sys.h"
#include "rsa_pss.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ets_secure_boot_sig_block ets_secure_boot_sig_block_t;
typedef struct ets_secure_boot_signature ets_secure_boot_signature_t;
typedef struct ets_secure_boot_key_digests ets_secure_boot_key_digests_t;

/* 反FI度量：使用完整的单词表示成功/失败，而不是0/非零
*/
typedef enum {
    SB_SUCCESS = 0x3A5A5AA5,
    SB_FAILED = 0x7533885E,
} secure_boot_status_t;

/* 验证引导加载程序映像（重新配置缓存以映射，从efuse加载受信任的密钥摘要）

 如果allow_key_revoke为true并且设置了主动撤销efuse，则任何失败的签名都会在efuse中撤销其关联的密钥。

 如果结果为ETS_OK，则将引导加载程序的“简单散列”复制到verified_hash中。
*/
int ets_secure_boot_verify_bootloader(uint8_t *verified_hash, bool allow_key_revoke);

/* 验证引导加载程序映像（将缓存重新配置为映射），并提供密钥摘要作为参数。）

   可用于在永久启用安全引导之前验证安全引导状态。

   如果结果为ETS_OK，则将引导加载程序的“简单散列”复制到verified_hash中。
*/
secure_boot_status_t ets_secure_boot_verify_bootloader_with_keys(uint8_t *verified_hash, const ets_secure_boot_key_digests_t *trusted_keys, bool stage_load);

/* 使用提供的受信任密钥摘要，根据提供的摘要验证提供的签名。

   不重新配置缓存或任何其他硬件访问。
*/
secure_boot_status_t ets_secure_boot_verify_signature(const ets_secure_boot_signature_t *sig, const uint8_t *image_digest, const ets_secure_boot_key_digests_t *trusted_keys, uint8_t *verified_digest);

/* 阅读efuse的关键摘要。任何已撤销/丢失的摘要都将标记为NULL

   如果至少找到一个有效摘要，则返回0。
*/
ETS_STATUS ets_secure_boot_read_key_digests(ets_secure_boot_key_digests_t *trusted_keys);

#define CRC_SIGN_BLOCK_LEN 1196
#define SIG_BLOCK_PADDING 4096
#define ETS_SECURE_BOOT_V2_SIGNATURE_MAGIC 0xE7

/* Secure Boot V2签名块（最多可附加3个）*/
struct ets_secure_boot_sig_block {
    uint8_t magic_byte;
    uint8_t version;
    uint8_t _reserved1;
    uint8_t _reserved2;
    uint8_t image_digest[32];
    ets_rsa_pubkey_t key;
    uint8_t signature[384];
    uint32_t block_crc;
    uint8_t _padding[16];
};

_Static_assert(sizeof(ets_secure_boot_sig_block_t) == 1216, "ets_secure_boot_sig_block_t should occupy 1216 Bytes in memory");

#define SECURE_BOOT_NUM_BLOCKS 3

/* V2安全引导签名扇区（最多3个块）*/
struct ets_secure_boot_signature {
    ets_secure_boot_sig_block_t block[SECURE_BOOT_NUM_BLOCKS];
    uint8_t _padding[4096 - (sizeof(ets_secure_boot_sig_block_t) * SECURE_BOOT_NUM_BLOCKS)];
};

_Static_assert(sizeof(ets_secure_boot_signature_t) == 4096, "ets_secure_boot_signature_t should occupy 4096 Bytes in memory");

#define MAX_KEY_DIGESTS 3

struct ets_secure_boot_key_digests {
    const void *key_digests[MAX_KEY_DIGESTS];
    bool allow_key_revoke;
};

#ifdef __cplusplus
}
#endif

