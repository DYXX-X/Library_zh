#ifndef crypto_scalarmult_H
#define crypto_scalarmult_H

#include <stddef.h>

#include "crypto_scalarmult_curve25519.h"
#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

#define crypto_scalarmult_BYTES crypto_scalarmult_curve25519_BYTES
SODIUM_EXPORT
size_t  crypto_scalarmult_bytes(void);

#define crypto_scalarmult_SCALARBYTES crypto_scalarmult_curve25519_SCALARBYTES
SODIUM_EXPORT
size_t  crypto_scalarmult_scalarbytes(void);

#define crypto_scalarmult_PRIMITIVE "curve25519"
SODIUM_EXPORT
const char *crypto_scalarmult_primitive(void);

SODIUM_EXPORT
int crypto_scalarmult_base(unsigned char *q, const unsigned char *n)
            __attribute__ ((nonnull));

/*
 * 注意：请勿将此功能的结果直接用于密钥交换。
 *
 * 使用公钥对结果进行哈希，以计算共享密钥：H（q||client_pk||server_pk）
 *
 * 或者，除非这不是一个选项，否则请改用crypt_kx（）API。
 */
SODIUM_EXPORT
int crypto_scalarmult(unsigned char *q, const unsigned char *n,
                      const unsigned char *p)
            __attribute__ ((warn_unused_result)) __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

