/*
   BLAKE2参考源代码包-参考C实现

   塞缪尔·内维斯于2012年撰写<sneves@dei.uc.pt>

   在法律允许的范围内，作者已将本软件的所有版权和相关权利以及邻近权利授予全球公共领域。本软件的分发无任何担保。

   所有代码均根据[CC0]获得三重许可(http://creativecommons.org/publicdomain/zero/1.0)，[OOpenSSL许可证](https://www.openssl.org/source/license.html)，或[Apache公共许可证2.0](http://www.apache.org/licenses/LICENSE-2.0)，由您选择。
 */

#ifndef blake2_H
#define blake2_H

#include <stddef.h>
#include <stdint.h>

#include "crypto_generichash_blake2b.h"
#include "export.h"

#define blake2b_init_param crypto_generichash_blake2b__init_param
#define blake2b_init crypto_generichash_blake2b__init
#define blake2b_init_salt_personal \
    crypto_generichash_blake2b__init_salt_personal
#define blake2b_init_key crypto_generichash_blake2b__init_key
#define blake2b_init_key_salt_personal \
    crypto_generichash_blake2b__init_key_salt_personal
#define blake2b_update crypto_generichash_blake2b__update
#define blake2b_final crypto_generichash_blake2b__final
#define blake2b crypto_generichash_blake2b__blake2b
#define blake2b_salt_personal crypto_generichash_blake2b__blake2b_salt_personal
#define blake2b_pick_best_implementation \
    crypto_generichash_blake2b__pick_best_implementation

enum blake2b_constant {
    BLAKE2B_BLOCKBYTES    = 128,
    BLAKE2B_OUTBYTES      = 64,
    BLAKE2B_KEYBYTES      = 64,
    BLAKE2B_SALTBYTES     = 16,
    BLAKE2B_PERSONALBYTES = 16
};

#if defined(__IBMC__) || defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

typedef struct blake2b_param_ {
    uint8_t digest_length;                   /*  1 */
    uint8_t key_length;                      /*  2 */
    uint8_t fanout;                          /*  3 */
    uint8_t depth;                           /*  4 */
    uint8_t leaf_length[4];                  /*  8 */
    uint8_t node_offset[8];                  /* 16 */
    uint8_t node_depth;                      /* 17 */
    uint8_t inner_length;                    /* 18 */
    uint8_t reserved[14];                    /* 32 */
    uint8_t salt[BLAKE2B_SALTBYTES];         /* 48 */
    uint8_t personal[BLAKE2B_PERSONALBYTES]; /* 64 */
} blake2b_param;

typedef struct blake2b_state {
    uint64_t h[8];
    uint64_t t[2];
    uint64_t f[2];
    uint8_t  buf[2 * 128];
    size_t   buflen;
    uint8_t  last_node;
} blake2b_state;

#if defined(__IBMC__) || defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#pragma pack()
#else
#pragma pack(pop)
#endif

/* 流式API*/
int blake2b_init(blake2b_state *S, const uint8_t outlen);
int blake2b_init_salt_personal(blake2b_state *S, const uint8_t outlen,
                               const void *salt, const void *personal);
int blake2b_init_key(blake2b_state *S, const uint8_t outlen, const void *key,
                     const uint8_t keylen);
int blake2b_init_key_salt_personal(blake2b_state *S, const uint8_t outlen,
                                   const void *key, const uint8_t keylen,
                                   const void *salt, const void *personal);
int blake2b_init_param(blake2b_state *S, const blake2b_param *P);
int blake2b_update(blake2b_state *S, const uint8_t *in, uint64_t inlen);
int blake2b_final(blake2b_state *S, uint8_t *out, uint8_t outlen);

/* 简单API*/
int blake2b(uint8_t *out, const void *in, const void *key, const uint8_t outlen,
            const uint64_t inlen, uint8_t keylen);
int blake2b_salt_personal(uint8_t *out, const void *in, const void *key,
                          const uint8_t outlen, const uint64_t inlen,
                          uint8_t keylen, const void *salt,
                          const void *personal);

typedef int (*blake2b_compress_fn)(blake2b_state *S,
                                   const uint8_t  block[BLAKE2B_BLOCKBYTES]);
int blake2b_pick_best_implementation(void);
int blake2b_compress_ref(blake2b_state *S,
                         const uint8_t  block[BLAKE2B_BLOCKBYTES]);
int blake2b_compress_ssse3(blake2b_state *S,
                           const uint8_t  block[BLAKE2B_BLOCKBYTES]);
int blake2b_compress_sse41(blake2b_state *S,
                           const uint8_t  block[BLAKE2B_BLOCKBYTES]);
int blake2b_compress_avx2(blake2b_state *S,
                          const uint8_t  block[BLAKE2B_BLOCKBYTES]);

#endif

