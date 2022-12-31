#ifndef crypto_stream_salsa20_H
#define crypto_stream_salsa20_H

/*
 *  警告：这只是一个流密码。它不是经过身份验证的加密。虽然它提供了一些防止窃听的保护，但它不提供任何防止主动攻击的安全性。除非你知道你在做什么，否则你要找的可能是crypto_box函数。
 */

#include <stddef.h>
#include <stdint.h>
#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

#define crypto_stream_salsa20_KEYBYTES 32U
SODIUM_EXPORT
size_t crypto_stream_salsa20_keybytes(void);

#define crypto_stream_salsa20_NONCEBYTES 8U
SODIUM_EXPORT
size_t crypto_stream_salsa20_noncebytes(void);

#define crypto_stream_salsa20_MESSAGEBYTES_MAX SODIUM_SIZE_MAX
SODIUM_EXPORT
size_t crypto_stream_salsa20_messagebytes_max(void);

SODIUM_EXPORT
int crypto_stream_salsa20(unsigned char *c, unsigned long long clen,
                          const unsigned char *n, const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_salsa20_xor(unsigned char *c, const unsigned char *m,
                              unsigned long long mlen, const unsigned char *n,
                              const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_salsa20_xor_ic(unsigned char *c, const unsigned char *m,
                                 unsigned long long mlen,
                                 const unsigned char *n, uint64_t ic,
                                 const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
void crypto_stream_salsa20_keygen(unsigned char k[crypto_stream_salsa20_KEYBYTES])
            __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

