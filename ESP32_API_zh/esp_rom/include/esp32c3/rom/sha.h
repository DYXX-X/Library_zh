// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#ifndef _ROM_SHA_H_
#define _ROM_SHA_H_

#include <stdint.h>
#include <stdbool.h>
#include "ets_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SHA1 = 0,
    SHA2_224,
    SHA2_256,
    SHA_TYPE_MAX
} SHA_TYPE;

typedef struct SHAContext {
    bool start;
    bool in_hardware;               // 此上下文当前是否在外围设备中？如果多个SHA交错，则需要手动清除
    SHA_TYPE type;
    uint32_t state[16];             // 对于SHA1/SHA224/SHA256，使用8个，其他使用16个
    unsigned char buffer[128];      // 对于SHA1/SHA224/SHA256，使用64，其他使用128
    uint32_t total_bits[4];
} SHA_CTX;

void ets_sha_enable(void);

void ets_sha_disable(void);

ets_status_t ets_sha_init(SHA_CTX *ctx, SHA_TYPE type);

ets_status_t ets_sha_starts(SHA_CTX *ctx, uint16_t sha512_t);

void ets_sha_get_state(SHA_CTX *ctx);

void ets_sha_process(SHA_CTX *ctx, const unsigned char *input);

void ets_sha_update(SHA_CTX *ctx, const unsigned char *input, uint32_t input_bytes, bool update_ctx);

ets_status_t ets_sha_finish(SHA_CTX *ctx, unsigned char *output);

#ifdef __cplusplus
}
#endif

#endif /* _ROM_SHA_H_ */

