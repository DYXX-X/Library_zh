#ifndef crypto_hash_sha256_H
#define crypto_hash_sha256_H

/*
 * 警告：除非出于互操作性的目的，您绝对需要使用SHA256，否则您可能需要考虑使用crypto_generichash（）。与SHA256不同，crypto_generichash（）不易受到长度扩展攻击。
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

typedef struct crypto_hash_sha256_state {
    uint32_t state[8];
    uint64_t count;
    uint8_t  buf[64];
} crypto_hash_sha256_state;

SODIUM_EXPORT
size_t crypto_hash_sha256_statebytes(void);

#define crypto_hash_sha256_BYTES 32U
SODIUM_EXPORT
size_t crypto_hash_sha256_bytes(void);

SODIUM_EXPORT
int crypto_hash_sha256(unsigned char *out, const unsigned char *in,
                       unsigned long long inlen) __attribute__ ((nonnull(1)));

SODIUM_EXPORT
int crypto_hash_sha256_init(crypto_hash_sha256_state *state)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_hash_sha256_update(crypto_hash_sha256_state *state,
                              const unsigned char *in,
                              unsigned long long inlen)
            __attribute__ ((nonnull(1)));

SODIUM_EXPORT
int crypto_hash_sha256_final(crypto_hash_sha256_state *state,
                             unsigned char *out)
            __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

