#ifndef crypto_stream_H
#define crypto_stream_H

/*
 *  警告：这只是一个流密码。它不是经过身份验证的加密。虽然它提供了一些防止窃听的保护，但它不提供任何防止主动攻击的安全性。除非你知道你在做什么，否则你要找的可能是crypto_box函数。
 */

#include <stddef.h>

#include "crypto_stream_xsalsa20.h"
#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

#define crypto_stream_KEYBYTES crypto_stream_xsalsa20_KEYBYTES
SODIUM_EXPORT
size_t  crypto_stream_keybytes(void);

#define crypto_stream_NONCEBYTES crypto_stream_xsalsa20_NONCEBYTES
SODIUM_EXPORT
size_t  crypto_stream_noncebytes(void);

#define crypto_stream_MESSAGEBYTES_MAX crypto_stream_xsalsa20_MESSAGEBYTES_MAX
SODIUM_EXPORT
size_t  crypto_stream_messagebytes_max(void);

#define crypto_stream_PRIMITIVE "xsalsa20"
SODIUM_EXPORT
const char *crypto_stream_primitive(void);

SODIUM_EXPORT
int crypto_stream(unsigned char *c, unsigned long long clen,
                  const unsigned char *n, const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_stream_xor(unsigned char *c, const unsigned char *m,
                      unsigned long long mlen, const unsigned char *n,
                      const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
void crypto_stream_keygen(unsigned char k[crypto_stream_KEYBYTES])
            __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

