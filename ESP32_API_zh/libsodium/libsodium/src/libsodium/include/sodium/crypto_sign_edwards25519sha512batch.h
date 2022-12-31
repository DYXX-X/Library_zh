#ifndef crypto_sign_edwards25519sha512batch_H
#define crypto_sign_edwards25519sha512batch_H

/*
 * 警告：这是一个原型，不应在新项目中使用。
 *
 * crypto_sign_edwards25519sha512batch是为最初使用NaCl构建的应用程序提供的，但根据该构建的作者的建议，新应用程序应该使用ed25519。
 *
 * 在Sodium中，应该使用高级crypto_sign_*（）函数。
 */

#include <stddef.h>
#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

#define crypto_sign_edwards25519sha512batch_BYTES 64U
#define crypto_sign_edwards25519sha512batch_PUBLICKEYBYTES 32U
#define crypto_sign_edwards25519sha512batch_SECRETKEYBYTES (32U + 32U)
#define crypto_sign_edwards25519sha512batch_MESSAGEBYTES_MAX (SODIUM_SIZE_MAX - crypto_sign_edwards25519sha512batch_BYTES)

SODIUM_EXPORT
int crypto_sign_edwards25519sha512batch(unsigned char *sm,
                                        unsigned long long *smlen_p,
                                        const unsigned char *m,
                                        unsigned long long mlen,
                                        const unsigned char *sk)
            __attribute__ ((deprecated)) __attribute__ ((nonnull(1, 5)));

SODIUM_EXPORT
int crypto_sign_edwards25519sha512batch_open(unsigned char *m,
                                             unsigned long long *mlen_p,
                                             const unsigned char *sm,
                                             unsigned long long smlen,
                                             const unsigned char *pk)
            __attribute__ ((deprecated)) __attribute__ ((nonnull(3, 5)));

SODIUM_EXPORT
int crypto_sign_edwards25519sha512batch_keypair(unsigned char *pk,
                                                unsigned char *sk)
            __attribute__ ((deprecated)) __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

