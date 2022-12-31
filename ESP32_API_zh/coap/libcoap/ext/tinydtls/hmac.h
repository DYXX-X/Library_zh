/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_HMAC_H_
#define _DTLS_HMAC_H_

#include <sys/types.h>

#include "tinydtls.h"
#include "global.h"

#ifdef WITH_SHA256
#ifdef RIOT_VERSION
#include "hashes/sha256.h"

typedef sha256_context_t dtls_hash_ctx;
typedef sha256_context_t dtls_sha256_ctx;
#define DTLS_HASH_CTX_SIZE sizeof(sha256_context_t)
#define DTLS_SHA256_DIGEST_LENGTH (SHA256_DIGEST_LENGTH)

#define dtls_sha256_init(Ctx)             sha256_init((Ctx))
#define dtls_sha256_update(Ctx,Input,Len) sha256_update((Ctx), (Input), (Len))
#define dtls_sha256_final(Buf,Ctx)        sha256_final((Ctx), (Buf))

#elif defined ESP_PLATFORM && defined CONFIG_LIBSODIUM_USE_MBEDTLS_SHA
#include "sodium/crypto_hash_sha256.h"

typedef crypto_hash_sha256_state dtls_hash_ctx;
typedef crypto_hash_sha256_state dtls_sha256_ctx;
#define DTLS_HASH_CTX_SIZE sizeof(crypto_hash_sha256_state)
#define DTLS_SHA256_DIGEST_LENGTH (crypto_hash_sha256_BYTES)

#define dtls_sha256_init(Ctx)             crypto_hash_sha256_init((Ctx))
#define dtls_sha256_update(Ctx,Input,Len) crypto_hash_sha256_update((Ctx), (Input), (Len))
#define dtls_sha256_final(Buf,Ctx)        crypto_hash_sha256_final((Ctx), (Buf))

#else /* ! RIOT_VERSION && ! ESP_PLATFORM */

/**Aaron D.Gifford的SHA256实现参见http://www.aarongifford.com/ */
#include "sha2/sha2.h"

typedef dtls_sha256_ctx dtls_hash_ctx;
#define DTLS_HASH_CTX_SIZE sizeof(dtls_sha256_ctx)

#endif /* ! RIOT_VERSION && ! ESP_PLATFORM */


typedef dtls_hash_ctx *dtls_hash_t;


static inline void
dtls_hash_init(dtls_hash_t ctx) {
  dtls_sha256_init((dtls_sha256_ctx *)ctx);
}

static inline void 
dtls_hash_update(dtls_hash_t ctx, const unsigned char *input, size_t len) {
  dtls_sha256_update((dtls_sha256_ctx *)ctx, input, len);
}

static inline size_t
dtls_hash_finalize(unsigned char *buf, dtls_hash_t ctx) {
  dtls_sha256_final(buf, (dtls_sha256_ctx *)ctx);
  return DTLS_SHA256_DIGEST_LENGTH;
}
#endif /* WITH_SHA256 */

void dtls_hmac_storage_init(void);

/**
 * \defgroup HMAC密钥散列消息认证码（HMAC）NIST标准FIPS 198描述了用作DTLS PRF的散列函数的密钥散列消息验证码（HMMAC）@{
 */

#define DTLS_HMAC_BLOCKSIZE   64	/**<hmac块的大小*/
#define DTLS_HMAC_DIGEST_SIZE 32	/**<摘要大小（适用于SHA-256）*/
#define DTLS_HMAC_MAX         64	/**<摘要中的最大字节数*/

/**
 * dtls_hmac_init（）中使用的已知哈希函数列表。标识符与<a href=“http://tools.ietf.org/html/rfc5246#section-7.4.1.4.1“>RFC 5246第7.4.1.4.1节</a>。
 */
typedef enum { 
  HASH_NONE=0, HASH_MD5=1, HASH_SHA1=2, HASH_SHA224=3,
  HASH_SHA256=4, HASH_SHA384=5, HASH_SHA512=6
} dtls_hashfunc_t;

/**
 * HMAC生成的上下文。此对象使用dtls_hmac_init（）初始化，必须传递给dtls_hmac_update（）和dtls_hmac_finalize（）。完成后，组件\c H无效，必须使用dtls_hmac_init（）再次初始化，然后才能再次使用该结构。
 */
typedef struct {
  unsigned char pad[DTLS_HMAC_BLOCKSIZE]; /**<ipad和opad存储*/
  dtls_hash_ctx data;		          /**<哈希函数的上下文*/
} dtls_hmac_context_t;

/**
 * 初始化现有HMAC上下文。
 *
 * @param ctx 要初始化的HMAC上下文。
 * @param key    秘密钥匙。
 * @param klen   @p键的长度。
 */
void dtls_hmac_init(dtls_hmac_context_t *ctx, const unsigned char *key, size_t klen);

/**
 * 使用给定的密钥分配新的HMAC上下文。如果正确设置了\c ctx，则此函数返回\c 1，否则返回\c 0或\c-1。注意，此函数分配必须由dtls_hmac_free（）释放的新存储。
 *
 * \param key密钥。\param klen \p键的长度。\错误时返回新的dtls_hmac_context_t对象或@c NULL
 */
dtls_hmac_context_t *dtls_hmac_new(const unsigned char *key, size_t klen);

/**
 * Releases the storage for @p dtls_hmac_new（）分配的ctx。
 *
 * @param ctx 要释放的dtls_hmac_context_t。
 */
void dtls_hmac_free(dtls_hmac_context_t *ctx);

/**
 * 使用来自\p输入的数据更新HMAC上下文。
 * 
 * \param ctx HMAC上下文。\param input输入数据。\param ilen输入的大小。
 */
void dtls_hmac_update(dtls_hmac_context_t *ctx,
		      const unsigned char *input, size_t ilen);

/** 
 * 完成HMAC生成并将结果写入给定的输出参数结果。缓冲区必须足够大，以容纳由实际哈希函数创建的消息摘要。如果有疑问，请使用\c DTLS_HMAC_MAX。函数返回写入\c result的字节数。
 *
 * \param ctx HMAC上下文。\param result写入MAC的输出参数。\return写入结果的MAC的长度。
 */
int dtls_hmac_finalize(dtls_hmac_context_t *ctx, unsigned char *result);

/**@}*/

#endif /* _DTLS_HMAC_H_ */

