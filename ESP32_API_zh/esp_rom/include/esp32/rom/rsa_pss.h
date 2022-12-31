// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "sdkconfig.h"
#ifdef CONFIG_ESP32_REV_MIN_3

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ETS_SIG_LEN 384 /* 字节*/
#define ETS_DIGEST_LEN 32 /* SHA-256，字节*/

/* 安全引导版本2-公钥格式*/
typedef struct {
    uint8_t n[384]; /* 公钥模数*/
    uint32_t e;     /* 公钥指数*/
    uint8_t rinv[384];
    uint32_t mdash;
} ets_rsa_pubkey_t;


bool ets_rsa_pss_verify(const ets_rsa_pubkey_t *key, const uint8_t *sig, const uint8_t *digest, uint8_t *verified_digest);

void ets_mgf1_sha256(const uint8_t *mgfSeed, size_t seedLen, size_t maskLen, uint8_t *mask);

bool ets_emsa_pss_verify(const uint8_t *encoded_message, const uint8_t *mhash, uint8_t *verified_digest);

#ifdef __cplusplus
}
#endif

#endif // CONFIG_ESP32_REV_MIN_3

