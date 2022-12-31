#ifndef crypto_aead_aes256gcm_H
#define crypto_aead_aes256gcm_H

/*
 * 警告：尽管在TLS中使用AES-GCM是最流行的AEAD构造，但在不同的环境中安全地使用AES-GM是很棘手的。
 *
 * 使用给定密钥加密的输入数据不得超过约350 GB。这是针对~16 KB的消息--实际数字因消息大小而异。
 *
 * 此外，随机数很短，重复的随机数将完全破坏该方案的安全性。
 *
 * 因此，Nonce应该来自原子计数器，这在分布式环境中很难设置。
 *
 * 除非您绝对需要AES-GCM，否则请改用crypto_aead_xchacha20poly1305_ietf_*（）。它没有任何这些限制。或者，如果不需要验证其他数据，只需使用crypto_secretbox（）。
 */

#include <stddef.h>
#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

SODIUM_EXPORT
int crypto_aead_aes256gcm_is_available(void);

#define crypto_aead_aes256gcm_KEYBYTES  32U
SODIUM_EXPORT
size_t crypto_aead_aes256gcm_keybytes(void);

#define crypto_aead_aes256gcm_NSECBYTES 0U
SODIUM_EXPORT
size_t crypto_aead_aes256gcm_nsecbytes(void);

#define crypto_aead_aes256gcm_NPUBBYTES 12U
SODIUM_EXPORT
size_t crypto_aead_aes256gcm_npubbytes(void);

#define crypto_aead_aes256gcm_ABYTES    16U
SODIUM_EXPORT
size_t crypto_aead_aes256gcm_abytes(void);

#define crypto_aead_aes256gcm_MESSAGEBYTES_MAX \
    SODIUM_MIN(SODIUM_SIZE_MAX - crypto_aead_aes256gcm_ABYTES, \
               (16ULL * ((1ULL << 32) - 2ULL)))
SODIUM_EXPORT
size_t crypto_aead_aes256gcm_messagebytes_max(void);

typedef struct CRYPTO_ALIGN(16) crypto_aead_aes256gcm_state_ {
    unsigned char opaque[512];
} crypto_aead_aes256gcm_state;

SODIUM_EXPORT
size_t crypto_aead_aes256gcm_statebytes(void);

SODIUM_EXPORT
int crypto_aead_aes256gcm_encrypt(unsigned char *c,
                                  unsigned long long *clen_p,
                                  const unsigned char *m,
                                  unsigned long long mlen,
                                  const unsigned char *ad,
                                  unsigned long long adlen,
                                  const unsigned char *nsec,
                                  const unsigned char *npub,
                                  const unsigned char *k)
            __attribute__ ((nonnull(1, 8, 9)));

SODIUM_EXPORT
int crypto_aead_aes256gcm_decrypt(unsigned char *m,
                                  unsigned long long *mlen_p,
                                  unsigned char *nsec,
                                  const unsigned char *c,
                                  unsigned long long clen,
                                  const unsigned char *ad,
                                  unsigned long long adlen,
                                  const unsigned char *npub,
                                  const unsigned char *k)
            __attribute__ ((warn_unused_result)) __attribute__ ((nonnull(4, 8, 9)));

SODIUM_EXPORT
int crypto_aead_aes256gcm_encrypt_detached(unsigned char *c,
                                           unsigned char *mac,
                                           unsigned long long *maclen_p,
                                           const unsigned char *m,
                                           unsigned long long mlen,
                                           const unsigned char *ad,
                                           unsigned long long adlen,
                                           const unsigned char *nsec,
                                           const unsigned char *npub,
                                           const unsigned char *k)
            __attribute__ ((nonnull(1, 2, 9, 10)));

SODIUM_EXPORT
int crypto_aead_aes256gcm_decrypt_detached(unsigned char *m,
                                           unsigned char *nsec,
                                           const unsigned char *c,
                                           unsigned long long clen,
                                           const unsigned char *mac,
                                           const unsigned char *ad,
                                           unsigned long long adlen,
                                           const unsigned char *npub,
                                           const unsigned char *k)
            __attribute__ ((warn_unused_result)) __attribute__ ((nonnull(3, 5, 8, 9)));

/* --预计算接口--*/

SODIUM_EXPORT
int crypto_aead_aes256gcm_beforenm(crypto_aead_aes256gcm_state *ctx_,
                                   const unsigned char *k)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int crypto_aead_aes256gcm_encrypt_afternm(unsigned char *c,
                                          unsigned long long *clen_p,
                                          const unsigned char *m,
                                          unsigned long long mlen,
                                          const unsigned char *ad,
                                          unsigned long long adlen,
                                          const unsigned char *nsec,
                                          const unsigned char *npub,
                                          const crypto_aead_aes256gcm_state *ctx_)
            __attribute__ ((nonnull(1, 8, 9)));

SODIUM_EXPORT
int crypto_aead_aes256gcm_decrypt_afternm(unsigned char *m,
                                          unsigned long long *mlen_p,
                                          unsigned char *nsec,
                                          const unsigned char *c,
                                          unsigned long long clen,
                                          const unsigned char *ad,
                                          unsigned long long adlen,
                                          const unsigned char *npub,
                                          const crypto_aead_aes256gcm_state *ctx_)
            __attribute__ ((warn_unused_result)) __attribute__ ((nonnull(4, 8, 9)));

SODIUM_EXPORT
int crypto_aead_aes256gcm_encrypt_detached_afternm(unsigned char *c,
                                                   unsigned char *mac,
                                                   unsigned long long *maclen_p,
                                                   const unsigned char *m,
                                                   unsigned long long mlen,
                                                   const unsigned char *ad,
                                                   unsigned long long adlen,
                                                   const unsigned char *nsec,
                                                   const unsigned char *npub,
                                                   const crypto_aead_aes256gcm_state *ctx_)
            __attribute__ ((nonnull(1, 2, 9, 10)));

SODIUM_EXPORT
int crypto_aead_aes256gcm_decrypt_detached_afternm(unsigned char *m,
                                                   unsigned char *nsec,
                                                   const unsigned char *c,
                                                   unsigned long long clen,
                                                   const unsigned char *mac,
                                                   const unsigned char *ad,
                                                   unsigned long long adlen,
                                                   const unsigned char *npub,
                                                   const crypto_aead_aes256gcm_state *ctx_)
            __attribute__ ((warn_unused_result)) __attribute__ ((nonnull(3, 5, 8, 9)));

SODIUM_EXPORT
void crypto_aead_aes256gcm_keygen(unsigned char k[crypto_aead_aes256gcm_KEYBYTES])
            __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

