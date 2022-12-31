#ifndef crypto_stream_chacha20_H
#define crypto_stream_chacha20_H

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

#define crypto_stream_chacha20_KEYBYTES 32U
SODIUM_EXPORT
size_t crypto_stream_chacha20_keybytes(void);

#define crypto_stream_chacha20_NONCEBYTES 8U
SODIUM_EXPORT
size_t crypto_stream_chacha20_noncebytes(void);

#define crypto_stream_chacha20_MESSAGEBYTES_MAX SODIUM_SIZE_MAX
SODIUM_EXPORT
size_t crypto_stream_chacha20_messagebytes_max(void);

/* ChaCha20具有64位随机数和64位计数器，如最初设计的*/

SODIUM_EXPORT
int crypto_stream_chacha20(unsigned char *c, unsigned long long clen,
                           const unsigned char *n, const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_chacha20_xor(unsigned char *c, const unsigned char *m,
                               unsigned long long mlen, const unsigned char *n,
                               const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_chacha20_xor_ic(unsigned char *c, const unsigned char *m,
                                  unsigned long long mlen,
                                  const unsigned char *n, uint64_t ic,
                                  const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
void crypto_stream_chacha20_keygen(unsigned char k[crypto_stream_chacha20_KEYBYTES])
            __attribute__ ((nonnull));

/* 具有96位随机数和32位计数器（IETF）的ChaCha20*/

#define crypto_stream_chacha20_ietf_KEYBYTES 32U
SODIUM_EXPORT
size_t crypto_stream_chacha20_ietf_keybytes(void);

#define crypto_stream_chacha20_ietf_NONCEBYTES 12U
SODIUM_EXPORT
size_t crypto_stream_chacha20_ietf_noncebytes(void);

#define crypto_stream_chacha20_ietf_MESSAGEBYTES_MAX \
    SODIUM_MIN(SODIUM_SIZE_MAX, 64ULL * (1ULL << 32))
SODIUM_EXPORT
size_t crypto_stream_chacha20_ietf_messagebytes_max(void);

SODIUM_EXPORT
int crypto_stream_chacha20_ietf(unsigned char *c, unsigned long long clen,
                                const unsigned char *n, const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_chacha20_ietf_xor(unsigned char *c, const unsigned char *m,
                                    unsigned long long mlen, const unsigned char *n,
                                    const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_chacha20_ietf_xor_ic(unsigned char *c, const unsigned char *m,
                                       unsigned long long mlen,
                                       const unsigned char *n, uint32_t ic,
                                       const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
void crypto_stream_chacha20_ietf_keygen(unsigned char k[crypto_stream_chacha20_ietf_KEYBYTES])
            __attribute__ ((nonnull));

/* 别名*/

#define crypto_stream_chacha20_IETF_KEYBYTES crypto_stream_chacha20_ietf_KEYBYTES
#define crypto_stream_chacha20_IETF_NONCEBYTES crypto_stream_chacha20_ietf_NONCEBYTES
#define crypto_stream_chacha20_IETF_MESSAGEBYTES_MAX crypto_stream_chacha20_ietf_MESSAGEBYTES_MAX

#ifdef __cplusplus
}
#endif

#endif

