#ifndef crypto_hash_H
#define crypto_hash_H

/*
 * 警告：除非出于互操作性的目的，您绝对需要使用SHA512，否则您可能需要考虑使用crypto_generichash（）。与SHA512不同，crypto_generichash（）不易受到长度扩展攻击。
 */

#include <stddef.h>

#include "crypto_hash_sha512.h"
#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

#define crypto_hash_BYTES crypto_hash_sha512_BYTES
SODIUM_EXPORT
size_t crypto_hash_bytes(void);

SODIUM_EXPORT
int crypto_hash(unsigned char *out, const unsigned char *in,
                unsigned long long inlen) __attribute__ ((nonnull(1)));

#define crypto_hash_PRIMITIVE "sha512"
SODIUM_EXPORT
const char *crypto_hash_primitive(void)
            __attribute__ ((warn_unused_result));

#ifdef __cplusplus
}
#endif

#endif

