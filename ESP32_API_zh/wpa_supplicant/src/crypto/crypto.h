/*
 * 加密库的包装函数版权所有（c）2004-2017，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 *
 * 该文件定义了需要为wpa_supplicant和hostapd实现的加密函数。如果不使用TLS，则使用MD5、SHA1和AES的内部实现，不需要外部库。当启用TLS时（例如，通过启用EAP-TLS或EAP-PEAP），TLS实现所使用的加密库预计也将用于非TLS需求，以便通过不两次实现这些功能来节省空间。
 *
 * 用于使用每个加密库的包装器代码位于其自己的文件（crypto*.c）中，其中一个文件被构建并链接进来，以提供此处定义的函数。
 */

#ifndef CRYPTO_H
#define CRYPTO_H

/**
 * md4_vector-数据向量的md4哈希
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
int md4_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac);

/**
 * md5_vector-数据向量的md5哈希
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
int md5_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac);


/**
 * sha1_vector-数据向量的SHA-1哈希
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
int sha1_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		u8 *mac);

/**
 * fips186_2-prf-NIST FIPS出版物186-2变更通知1 prf
 * @seed: PRF种子/密钥
 * @seed_len: 种子长度（字节）
 * @x: PRF输出缓冲区
 * @xlen: 输出长度（字节）：成功时返回0，失败时返回-1
 *
 * 此函数实现NIST FIPS出版物186-2中为EAP-SIM指定的随机数生成。此PRF使用与SHA-1类似的函数，但具有不同的消息填充。
 */
int __must_check fips186_2_prf(const u8 *seed, size_t seed_len, u8 *x,
			       size_t xlen);

/**
 * sha256_vector-数据向量的sha256哈希
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
int sha256_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac);

/**
 * sha384_vector-数据矢量的sha384哈希
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
int sha384_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac);

/**
 * sha512_vector-数据向量的sha512哈希
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
int sha512_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac);

/**
 * des_encrypt-使用des加密一个块
 * @clear: 8个八位字节（英寸）
 * @key: 7个八位字节（in）（不包括奇偶校验位）
 * @cypher: 8个八位字节（out）返回：成功时为0，失败时为-1
 */
int des_encrypt(const u8 *clear, const u8 *key, u8 *cypher);

/**
 * aes_encrypt_init-初始化aes进行加密
 * @key: 加密密钥
 * @len: 以字节为单位的密钥长度（通常为16，即128位）返回：指向上下文数据的指针或失败时的%NULL
 */
void * aes_encrypt_init(const u8 *key, size_t len);

/**
 * aes_encrypt-加密一个aes块
 * @ctx: aes_encrypt_init（）中的上下文指针
 * @plain: 要加密的明文数据（16字节）
 * @crypt: 加密数据的缓冲区（16字节）：成功时返回0，失败时返回-1
 */
int aes_encrypt(void *ctx, const u8 *plain, u8 *crypt);

/**
 * aes_encrypt_deinit-取消初始化aes加密
 * @ctx: aes_encrypt_init（）中的上下文指针
 */
void aes_encrypt_deinit(void *ctx);

/**
 * aes_decrypt_init-初始化aes进行解密
 * @key: 解密钥匙
 * @len: 以字节为单位的密钥长度（通常为16，即128位）返回：指向上下文数据的指针或失败时的%NULL
 */
void * aes_decrypt_init(const u8 *key, size_t len);

/**
 * aes_decrypt-解密一个aes块
 * @ctx: aes_encrypt_init（）中的上下文指针
 * @crypt: 加密数据（16字节）
 * @plain: 解密数据的缓冲区（16字节）：成功时返回0，失败时返回-1
 */
int aes_decrypt(void *ctx, const u8 *crypt, u8 *plain);

/**
 * aes_decrypt_deinit-取消初始化aes解密
 * @ctx: aes_encrypt_init（）中的上下文指针
 */
void aes_decrypt_deinit(void *ctx);


enum crypto_hash_alg {
	CRYPTO_HASH_ALG_MD5, CRYPTO_HASH_ALG_SHA1,
	CRYPTO_HASH_ALG_HMAC_MD5, CRYPTO_HASH_ALG_HMAC_SHA1,
	CRYPTO_HASH_ALG_SHA256, CRYPTO_HASH_ALG_HMAC_SHA256,
	CRYPTO_HASH_ALG_SHA384, CRYPTO_HASH_ALG_SHA512
};

struct crypto_hash;

/**
 * crypto_hash_init-初始化哈希/HMAC函数
 * @alg: 哈希算法
 * @key: 键控哈希的密钥（例如HMAC）或%NULL（如果不需要）
 * @key_len: 键的长度（以字节为单位）返回：指向要与其他哈希函数一起使用的哈希上下文的指针或失败时的%NULL
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
struct crypto_hash * crypto_hash_init(enum crypto_hash_alg alg, const u8 *key,
				      size_t key_len);

/**
 * crypto_hash_update-将数据添加到哈希计算
 * @ctx: crypto_hash_init（）中的上下文指针
 * @data: 要添加的数据缓冲区
 * @len: 缓冲区长度
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
void crypto_hash_update(struct crypto_hash *ctx, const u8 *data, size_t len);

/**
 * crypto_hash_finish-完成哈希计算
 * @ctx: crypto_hash_init（）中的上下文指针
 * @hash: 哈希值的缓冲区或%NULL（如果调用方只是释放哈希上下文）
 * @len: 指向缓冲区长度的指针，如果调用者只是释放哈希上下文，则返回%NULL；返回时，该值设置为哈希值的实际长度返回：成功时返回0，如果缓冲区太小（len设置为所需长度）则返回-1，其他失败时返回-2（包括失败的crypto_hash_update（）操作）
 *
 * 此函数计算哈希值并释放用于哈希计算的上下文缓冲区。
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int crypto_hash_finish(struct crypto_hash *ctx, u8 *hash, size_t *len);


enum crypto_cipher_alg {
	CRYPTO_CIPHER_NULL = 0, CRYPTO_CIPHER_ALG_AES, CRYPTO_CIPHER_ALG_3DES,
	CRYPTO_CIPHER_ALG_DES, CRYPTO_CIPHER_ALG_RC2, CRYPTO_CIPHER_ALG_RC4
};

struct crypto_cipher;

/**
 * crypto_cipher_init-初始化块/流密码函数
 * @alg: 密码算法
 * @iv: 块密码的初始化向量或流密码的%NULL
 * @key: 密码密钥
 * @key_len: 密钥长度（以字节为单位）返回：指向要与其他密码函数一起使用的密码上下文的指针，或失败时返回%NULL
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
struct crypto_cipher * crypto_cipher_init(enum crypto_cipher_alg alg,
					  const u8 *iv, const u8 *key,
					  size_t key_len);

/**
 * crypto_cipher_encrypt-密码加密
 * @ctx: 来自crypto_cipher_init（）的上下文指针
 * @plain: 密码明文
 * @crypt: 生成的密文
 * @len: 明文长度返回：成功时为0，失败时为-1
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_cipher_encrypt(struct crypto_cipher *ctx,
				       const u8 *plain, u8 *crypt, size_t len);

/**
 * crypto_cipher_decrypt-密码解密
 * @ctx: 来自crypto_cipher_init（）的上下文指针
 * @crypt: 要解密的密文
 * @plain: 生成的明文
 * @len: 密文长度：成功时返回0，失败时返回-1
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_cipher_decrypt(struct crypto_cipher *ctx,
				       const u8 *crypt, u8 *plain, size_t len);

/**
 * crypto_cipher_decrypt-自由密码上下文
 * @ctx: 来自crypto_cipher_init（）的上下文指针
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
void crypto_cipher_deinit(struct crypto_cipher *ctx);


struct crypto_public_key;
struct crypto_private_key;

/**
 * crypt_public_key_import-导入RSA公钥
 * @key: 密钥缓冲区（DER编码的RSA公钥）
 * @len: 密钥缓冲区长度（字节）返回：指向公钥的指针或失败时的%NULL
 *
 * 如果加密库支持X.509解析，则此函数只能返回%NULL。在这种情况下，crypto_public_key_from_cert（）用于从证书导入公钥。
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
struct crypto_public_key * crypto_public_key_import(const u8 *key, size_t len);

struct crypto_public_key *
crypto_public_key_import_parts(const u8 *n, size_t n_len,
			       const u8 *e, size_t e_len);

/**
 * crypt_private_key_import-导入RSA私钥
 * @key: 密钥缓冲区（DER编码的RSA私钥）
 * @len: 密钥缓冲区长度（字节）
 * @passwd: 密钥加密密码或%NULL（如果密钥未加密）返回：指向私钥的指针或失败时的%NULL
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
struct crypto_private_key * crypto_private_key_import(const u8 *key,
						      size_t len,
						      const char *passwd);

/**
 * crypt_public_key_from_cert-从证书导入RSA公钥
 * @buf: DER编码的X.509证书
 * @len: 证书缓冲区长度（字节）返回：指向公钥的指针或失败时的%NULL
 *
 * 如果加密库不支持X.509解析，则此函数只能返回%NULL。在这种情况下，将使用内部代码解析证书，并使用crypto_public_key_import（）导入公钥。
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
struct crypto_public_key * crypto_public_key_from_cert(const u8 *buf,
						       size_t len);

/**
 * crypt_public_key_encrypt_pkcs1_v15-公钥加密（PKCS#1 v1.5）
 * @key: 公钥
 * @in: 明文缓冲区
 * @inlen: 明文缓冲区的长度（字节）
 * @out: 加密数据的输出缓冲区
 * @outlen: 输出缓冲区的长度（字节）；设置为成功时使用的长度返回：成功时为0，失败时为-1
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_public_key_encrypt_pkcs1_v15(
	struct crypto_public_key *key, const u8 *in, size_t inlen,
	u8 *out, size_t *outlen);

/**
 * crypt_private_key_decrypt_pkcs1_v15-私钥解密（PKCS#1 v1.5）
 * @key: 私钥
 * @in: 加密缓冲区
 * @inlen: 加密缓冲区的长度（字节）
 * @out: 加密数据的输出缓冲区
 * @outlen: 输出缓冲区的长度（字节）；设置为成功时使用的长度返回：成功时为0，失败时为-1
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_private_key_decrypt_pkcs1_v15(
	struct crypto_private_key *key, const u8 *in, size_t inlen,
	u8 *out, size_t *outlen);

/**
 * crypt_private_key_sign_pkcs1-使用私钥签名（PKCS#1）
 * @key: crypto_Private_key_import（）中的私钥
 * @in: 明文缓冲区
 * @inlen: 明文缓冲区的长度（字节）
 * @out: 加密（签名）数据的输出缓冲区
 * @outlen: 输出缓冲区的长度（字节）；设置为成功时使用的长度返回：成功时为0，失败时为-1
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_private_key_sign_pkcs1(struct crypto_private_key *key,
					       const u8 *in, size_t inlen,
					       u8 *out, size_t *outlen);

/**
 * crypt_public_key_free-免费公钥
 * @key: 公钥
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
void crypto_public_key_free(struct crypto_public_key *key);

/**
 * crypt_private_key_free-免费私钥
 * @key: crypto_Private_key_import（）中的私钥
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
void crypto_private_key_free(struct crypto_private_key *key);

/**
 * crypt_public_key_decrypt_pkcs1-解密PKCS#1签名
 * @key: 公钥
 * @crypt: 加密的签名数据（使用私钥）
 * @crypt_len: 加密签名数据长度
 * @plain: 明文缓冲区（至少crypt_len字节）
 * @plain_len: 明文长度（输入时的最大缓冲区大小，输出时的实际长度）；返回：成功时返回0，失败时返回-1
 */
int __must_check crypto_public_key_decrypt_pkcs1(
	struct crypto_public_key *key, const u8 *crypt, size_t crypt_len,
	u8 *plain, size_t *plain_len);

int crypto_dh_init(u8 generator, const u8 *prime, size_t prime_len, u8 *privkey,
		   u8 *pubkey);
int crypto_dh_derive_secret(u8 generator, const u8 *prime, size_t prime_len,
			    const u8 *order, size_t order_len,
			    const u8 *privkey, size_t privkey_len,
			    const u8 *pubkey, size_t pubkey_len,
			    u8 *secret, size_t *len);

/**
 * crypto_global_init-初始化加密包装
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_global_init(void);

/**
 * crypto_global_deinit-取消初始化加密包装
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
void crypto_global_deinit(void);

/**
 * crypto_mod_exp-大整数的模幂
 * @base: 基整数（大端字节数组）
 * @base_len: 基整数的长度（字节）
 * @power: 幂整数（大端字节数组）
 * @power_len: 幂整数的长度（字节）
 * @modulus: 模数整数（大端字节数组）
 * @modulus_len: 模数整数的长度（字节）
 * @result: 结果缓冲区
 * @result_len: 结果长度（输入时的最大缓冲区大小，输出时的实际长度）返回：成功时为0，失败时为-1
 *
 * 此函数用于计算结果=基数^幂模模数。moduleslen用作模数缓冲区的最大大小。成功时将其设置为使用的大小。
 *
 * 此函数仅用于内部TLSv1实现（CONFIG_TLS=内部）。如果不使用，加密包装器不需要实现这一点。
 */
int __must_check crypto_mod_exp(const u8 *base, size_t base_len,
				const u8 *power, size_t power_len,
				const u8 *modulus, size_t modulus_len,
				u8 *result, size_t *result_len);

/**
 * rc4_skip-用跳过流开始将rc4流与给定数据进行异或
 * @key: RC4键
 * @keylen: RC4密钥长度
 * @skip: 从RC4流开始跳过的字节数
 * @data: 要与RC4流进行异或的数据
 * @data_len: buf长度返回：成功时返回0，失败时返回-1
 *
 * 为给定密钥生成RC4伪随机流，跳过流的开头，并将最终结果与数据缓冲区进行XOR，以执行RC4加密/解密。
 */
int rc4_skip(const u8 *key, size_t keylen, size_t skip,
	     u8 *data, size_t data_len);

/**
 * crypto_get_random-生成加密强伪随机字节
 * @buf: 数据缓冲区
 * @len: 生成返回的字节数：成功时为0，失败时为-1
 *
 * 如果PRNG没有足够的熵来确保不可预测的字节序列，则此函数必须返回-1。
 */
int crypto_get_random(void *buf, size_t len);


/**
 * 结构crypto_bignum-bignum
 *
 * bignum实现的内部数据结构。内容特定于使用的加密库。
 */
struct crypto_bignum;

/**
 * 结构crypto_key-key
 *
 * ssl密钥的内部数据结构。内容特定于使用的加密库。
 */
struct crypto_key;

/**
 * crypto_bignum_init-为bignum分配内存返回：指向分配的bignum的指针或失败时的%NULL
 */
struct crypto_bignum * crypto_bignum_init(void);

/**
 * crypto_bignum_init_set-为bignum分配内存并设置值
 * @buf: 具有无符号二进制值的缓冲区
 * @len: 八位字节中buf的长度返回：失败时指向分配的bignum或%NULL的指针
 */
struct crypto_bignum * crypto_bignum_init_set(const u8 *buf, size_t len);

/**
 * crypto_bignum_init_set-为bignum分配内存并设置值（uint）
 * @val: 要设置返回值的值：失败时指向分配的bignum或%NULL的指针
 */
struct crypto_bignum * crypto_bignum_init_uint(unsigned int val);

/**
 * crypto_bignum_deinit-释放bignum
 * @n: crypto_Bignum_init（）或crypto_Bignum_init_set（）中的Bignum
 * @clear: 是否从内存中清除值
 */
void crypto_bignum_deinit(struct crypto_bignum *n, int clear);

/**
 * crypto_bignum_to_bin-将二进制缓冲区设置为无符号bignum
 * @a: Bignum公司
 * @buf: 二进制数缓冲区
 * @len: @buf的长度（八位字节）
 * @padlen: 将结果填充到的长度（以八位字节为单位）或0表示不填充返回：成功时写入的八位字节数，失败时为-1
 */
int crypto_bignum_to_bin(const struct crypto_bignum *a,
			 u8 *buf, size_t buflen, size_t padlen);

/**
 * crypto_bignum_rand-创建模数范围内的随机数
 * @r: Bignum；设置为随机值
 * @m: Bignum；模数返回：成功时为0，失败时为-1
 */
int crypto_bignum_rand(struct crypto_bignum *r, const struct crypto_bignum *m);

/**
 * crypto_bignum_add-c=a+b
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum；用于存储a+b的结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_add(const struct crypto_bignum *a,
		      const struct crypto_bignum *b,
		      struct crypto_bignum *c);

/**
 * crypto_bignum_mod-c=a%b
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum；用于存储%b的结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_mod(const struct crypto_bignum *a,
		      const struct crypto_bignum *b,
		      struct crypto_bignum *c);

/**
 * crypto_bignum_exptmod-模幂：d=a^b（mod c）
 * @a: Bignum；基础
 * @b: Bignum；拥护者
 * @c: Bignum；模数，模数
 * @d: Bignum；用于存储a^b（mod c）的结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_exptmod(const struct crypto_bignum *a,
			  const struct crypto_bignum *b,
			  const struct crypto_bignum *c,
			  struct crypto_bignum *d);

/**
 * crypto_bignum_inverse-反转bignum，使a*c=1（mod b）
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum；用于存储结果返回：成功时返回0，失败时返回-1
 */
int crypto_bignum_inverse(const struct crypto_bignum *a,
			  const struct crypto_bignum *b,
			  struct crypto_bignum *c);

/**
 * crypto_bignum_sub-c=a-b
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum；用于存储a-b返回的结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_sub(const struct crypto_bignum *a,
		      const struct crypto_bignum *b,
		      struct crypto_bignum *c);

/**
 * crypto_bignum_div-c=a/b
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum；用于存储a/b返回结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_div(const struct crypto_bignum *a,
		      const struct crypto_bignum *b,
		      struct crypto_bignum *c);

/**
 * crypto_bignum_addmod-d=a+b（mod c）
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum公司
 * @d: Bignum；用于存储（a+b）%c的结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_addmod(const struct crypto_bignum *a,
			 const struct crypto_bignum *b,
			 const struct crypto_bignum *c,
			 struct crypto_bignum *d);

/**
 * crypto_bignum_mulud-d=a*b（模式c）
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum公司
 * @d: Bignum；用于存储（a*b）%c的结果：成功时返回0，失败时返回-1
 */
int crypto_bignum_mulmod(const struct crypto_bignum *a,
			 const struct crypto_bignum *b,
			 const struct crypto_bignum *c,
			 struct crypto_bignum *d);

/**
 * crypto_bignum_cmp-比较两个bignum
 * @a: Bignum公司
 * @b: Bignum返回：如果a<b，则返回-1；如果a==b，则为0；如果a>b，则1
 */
int crypto_bignum_cmp(const struct crypto_bignum *a,
		      const struct crypto_bignum *b);

/**
 * crypto_bignum_bits-获取bignum的大小（以位为单位）
 * @a: Bignum返回：Bignum中的位数
 */
int crypto_bignum_bits(const struct crypto_bignum *a);

/**
 * crypto_bignum_is_zero-给定的bignum为零
 * @a: Bignum公司
 * Returns: 1 if @a 为零，否则为0
 */
int crypto_bignum_is_zero(const struct crypto_bignum *a);

/**
 * crypto_bignum_is_one-是给定的bignum
 * @a: Bignum公司
 * Returns: 1 if @a 如果不是，则为1或0
 */
int crypto_bignum_is_one(const struct crypto_bignum *a);

/**
 * crypto_bignum_legendre-计算legendre符号（a/p）
 * @a: Bignum公司
 * @p: Bignum返回：Legendre符号-成功时为1,0,1-2关于计算失败
 */
int crypto_bignum_legendre(const struct crypto_bignum *a,
        const struct crypto_bignum *p);


/**
 * struct crypto_ec-椭圆曲线上下文
 *
 * EC实施的内部数据结构。内容特定于使用的加密库。
 */
struct crypto_ec;

/**
 * crypto_ec_init-初始化椭圆曲线上下文
 * @group: ECC组的标识号（RFC 2409的IANA“组描述”属性注册表）返回：指向EC上下文的指针或失败时的%NULL
 */
struct crypto_ec * crypto_ec_init(int group);

/**
 * crypto_ec_deinit-取消初始化椭圆曲线上下文
 * @e: 来自crypto_EC_init（）的EC上下文
 */
void crypto_ec_deinit(struct crypto_ec *e);

/**
 * crypto_ec_prime_len-以八位字节为单位获取素数的长度
 * @e: 来自crypto_EC_init（）的EC上下文返回：定义组的素数的长度
 */
size_t crypto_ec_prime_len(struct crypto_ec *e);

/**
 * crypto_ec_prime_len_bits-获取素数的长度（以位为单位）
 * @e: 来自crypto_EC_init（）的EC上下文返回：以位为单位定义组的素数的长度
 */
size_t crypto_ec_prime_len_bits(struct crypto_ec *e);

/**
 * crypto_ec_get_prime-获取定义ec组的prime
 * @e: 来自crypto_EC_init（）的EC上下文返回：定义组的Prime（bignum）
 */
const struct crypto_bignum * crypto_ec_get_prime(struct crypto_ec *e);

/**
 * crypto_ec_get_order-获取ec组的顺序
 * @e: crypto_EC_init（）中的EC上下文返回：组的顺序（bignum）
 */
const struct crypto_bignum * crypto_ec_get_order(struct crypto_ec *e);

/**
 * 结构crypto_ec_point-椭圆曲线点
 *
 * EC实现的内部数据结构表示一个点。内容特定于使用的加密库。
 */
struct crypto_ec_point;

/**
 * crypto_ec_point_init-初始化ec点的数据
 * @e: crypto_EC_init（）返回的EC上下文：指向EC点数据的指针或失败时的%NULL
 */
struct crypto_ec_point * crypto_ec_point_init(struct crypto_ec *e);

/**
 * crypto_ec_point_deinit-取消初始化ec点数据
 * @p: 来自crypto_EC_point_init（）的EC点数据
 * @clear: 是否从内存中清除EC点值
 */
void crypto_ec_point_deinit(struct crypto_ec_point *p, int clear);

/**
 * crypto_ec_point_to_bin-将ec点值写入二进制数据
 * @e: 来自crypto_EC_init（）的EC上下文
 * @p: 来自crypto_EC_point_init（）的EC点数据
 * @x: 用于写入x坐标的二进制数据的缓冲区，如果未使用，则为%NULL
 * @y: 用于写入y坐标的二进制数据的缓冲区，如果未使用，则返回%NULL：成功时返回0，失败时返回-1
 *
 * 此函数可用于将EC点写入二进制数据，其格式为x和y坐标以大端字节顺序字段填充到定义组的素数的长度。
 */
int crypto_ec_point_to_bin(struct crypto_ec *e,
        const struct crypto_ec_point *point, u8 *x, u8 *y);

/**
 * crypto_ec_point_from_bin-从二进制数据创建ec点
 * @e: 来自crypto_EC_init（）的EC上下文
 * @val: 从返回中读取EC点的二进制数据：指向EC点数据的指针或失败时的%NULL
 *
 * 该函数从提供的缓冲区读取EC点的x和y坐标，假设值以大端字节顺序排列，字段填充到定义组的素数长度。
 */
struct crypto_ec_point * crypto_ec_point_from_bin(struct crypto_ec *e,
        const u8 *val);

/**
 * crypto_bignum_add-c=a+b
 * @e: 来自crypto_EC_init（）的EC上下文
 * @a: Bignum公司
 * @b: Bignum公司
 * @c: Bignum；用于存储a+b的结果：成功时返回0，失败时返回-1
 */
int crypto_ec_point_add(struct crypto_ec *e, const struct crypto_ec_point *a,
        const struct crypto_ec_point *b,
        struct crypto_ec_point *c);

/**
 * crypto_bignum_mul-res=b*p
 * @e: 来自crypto_EC_init（）的EC上下文
 * @p: EC点
 * @b: Bignum公司
 * @res: EC点；用于存储b*p的结果：成功时返回0，失败时返回-1
 */
int crypto_ec_point_mul(struct crypto_ec *e, const struct crypto_ec_point *p,
        const struct crypto_bignum *b,
        struct crypto_ec_point *res);

/**
 * crypto_ec_point_invert-计算ec点的倒数
 * @e: 来自crypto_EC_init（）的EC上下文
 * @p: 要反转的EC点（和操作结果）返回：成功时返回0，失败时返回-1
 */
int crypto_ec_point_invert(struct crypto_ec *e, struct crypto_ec_point *p);

/**
 * crypto_ec_point_solve_y_coord-求解x坐标的y坐标
 * @e: 来自crypto_EC_init（）的EC上下文
 * @p: 用于返回结果的EC点
 * @x: x坐标
 * @y_bit: y位（0或1），用于选择要使用的y值：成功时返回0，失败时返回-1
 */
int crypto_ec_point_solve_y_coord(struct crypto_ec *e,
        struct crypto_ec_point *p,
        const struct crypto_bignum *x, int y_bit);

/**
 * crypto_ec_point_compute_y_sqr-计算y^2=x^3+ax+b
 * @e: 来自crypto_EC_init（）的EC上下文
 * @x: x坐标返回：成功时返回y^2，失败时返回%NULL
 */
struct crypto_bignum *
crypto_ec_point_compute_y_sqr(struct crypto_ec *e,
        const struct crypto_bignum *x);

/**
 * crypto_ec_point_is_at_infinity-检查ec点是否为中性元素
 * @e: 来自crypto_EC_init（）的EC上下文
 * @p: EC点返回：如果指定的EC点是组的中性元素，则返回1；如果不是，则返回0
 */
int crypto_ec_point_is_at_infinity(struct crypto_ec *e,
        const struct crypto_ec_point *p);

/**
 * crypto_ec_point_is_on_curve-检查ec点是否在曲线上
 * @e: 来自crypto_EC_init（）的EC上下文
 * @p: EC点返回：如果指定的EC点位于曲线上，则返回1；如果不在曲线上，返回0
 */
int crypto_ec_point_is_on_curve(struct crypto_ec *e,
        const struct crypto_ec_point *p);

/**
 * crypto_ec_point_cmp-比较两个ec点
 * @e: 来自crypto_EC_init（）的EC上下文
 * @a: EC点
 * @b: EC点返回：等于0，否则为非零
 */
int crypto_ec_point_cmp(const struct crypto_ec *e,
        const struct crypto_ec_point *a,
        const struct crypto_ec_point *b);

/**
 * crypto_ec_get_publicy_buf-将ec公钥写入缓冲区
 * @key: 加密密钥
 * @key_buf: 密钥缓冲区
 * @len: 缓冲区长度成功时返回0，否则返回非零
 */
int crypto_ec_get_publickey_buf(struct crypto_key *key, u8 *key_buf, int len);

/**
 * crypto_ec_get_group_from_key-从密钥写入ec组
 * @key: 加密密钥返回：EC组
 */
struct crypto_ec_group *crypto_ec_get_group_from_key(struct crypto_key *key);

/**
 * crypto_ec_get_private_key-获取ec私钥（bignum格式）
 * @key: crypto key返回：私钥
 */
struct crypto_bignum *crypto_ec_get_private_key(struct crypto_key *key);

/**
 * crypto_ec_get_key-从字符流读取密钥
 * @privkey: 私钥
 * @privkey_len: 私钥len返回：加密密钥
 */
struct crypto_key *crypto_ec_get_key(const u8 *privkey, size_t privkey_len);

/**
 * crypto_ec_get_mbedtls_to_nist_group_id-从mbedtls内部组获取nist组
 * @id: mbedtls组返回：NIST组
 */
unsigned int crypto_ec_get_mbedtls_to_nist_group_id(int id);

/**
 * crypto_ec_get_curve_id-从ec组获取曲线id
 * @group: EC组返回：曲线ID
 */
int crypto_ec_get_curve_id(const struct crypto_ec_group *group);

/**
 * crypto_ecdh：加密ecdh
 * @key_own: 自己的密钥
 * @key_peer: 对等密钥
 * @secret: 秘密
 * @secret_len: secret len返回：如果成功，则返回0，否则返回负值
 */
int crypto_ecdh(struct crypto_key *key_own, struct crypto_key *key_peer,
		    u8 *secret, size_t *secret_len);

/**
 * crypto_ecdsa_get_sign：获取加密ecdsa签名哈希
 * @hash: 有符号散列
 * @r: 电子数据采集系统
 * @s: 电子数据采集系统
 * @csign: csign公司
 * @hash_len: 哈希长度返回：如果成功，则返回0，否则返回负值
 */
int crypto_ecdsa_get_sign(unsigned char *hash,
		const struct crypto_bignum *r, const struct crypto_bignum *s,
		struct crypto_key *csign, int hash_len);

/**
 * crypto_edcsa_sign_verify：验证加密ecdsa签名哈希
 * @hash: 有符号散列
 * @r: 电子数据采集系统
 * @s: 电子数据采集系统
 * @csign: csign公司
 * @hlen: 哈希长度返回：如果成功，则返回0，否则返回负值
 */
int crypto_edcsa_sign_verify(const unsigned char *hash, const struct crypto_bignum *r,
			const struct crypto_bignum *s, struct crypto_key *csign, int hlen);

/**
 * crypto_ec_parse_subpub_key：从子公钥获取ec密钥上下文
 * @p: 数据
 * @len: 数据长度返回：crypto_key
 */
struct crypto_key *crypto_ec_parse_subpub_key(const unsigned char *p, size_t len);

/**
 * crypto_is_ec_key：检查密钥是否为ec密钥
 * @key: crypto key Return：如果key else为false，则返回true
 */
int crypto_is_ec_key(struct crypto_key *key);

/**
 * crypto_ec_gen_keypair：生成crypto-ec密钥对
 * @ike_group: grpup返回：加密密钥
 */
struct crypto_key * crypto_ec_gen_keypair(u16 ike_group);

/**
 * crypto_ec_write_pub_key：返回字符缓冲区中的公钥
 * @key: 加密密钥
 * @der_len: buffer len返回：公钥缓冲区
 */
int crypto_ec_write_pub_key(struct crypto_key *key, unsigned char **key_buf);

/**
 * crypto_ec_set_pubkey_point：在ec曲线上设置bignum点
 * @group: ec组
 * @buf: x、 y坐标
 * @len: x和y坐标的长度返回：加密密钥
 */
struct crypto_key * crypto_ec_set_pubkey_point(const struct crypto_ec_group *group,
					     const u8 *buf, size_t len);
/**
 * crypto_ec_free_key:免费加密密钥返回：无
 */
void crypto_ec_free_key(struct crypto_key *key);
/**
 * crypto_debug_print_ec_key：打印ec密钥
 * @title: 标题
 * @key: 加密密钥返回：无
 */
void crypto_debug_print_ec_key(const char *title, struct crypto_key *key);

/**
 * crypto_ec_get_public_key：来自加密密钥的公钥
 * @key: cryptokey返回：公钥
 */
struct crypto_ec_point *crypto_ec_get_public_key(struct crypto_key *key);

/**
 * crypto_get_order：免费加密密钥返回：无
 */
int crypto_get_order(struct crypto_ec_group *group, struct crypto_bignum *x);

/**
 * cryptoec_get_affine_cordinates：获取ec曲线的仿射坐标
 * @e: ec曲线
 * @pt: 指向
 * @x: x坐标
 * @y: y坐标如果成功返回：0
 */
int crypto_ec_get_affine_coordinates(struct crypto_ec *e, struct crypto_ec_point *pt,
        struct crypto_bignum *x, struct crypto_bignum *y);

/**
 * crypto_ec_get_group_byname：按名称获取ec曲线组
 * @name: ec曲线名称返回：ec组
 */
struct crypto_ec_group *crypto_ec_get_group_byname(const char *name);

/**
 * crypt_key_compare：检查两个密钥是否属于同一个返回：1如果是，否则为0
 */
int crypto_key_compare(struct crypto_key *key1, struct crypto_key *key2);

/*
 * crypto_write_pubkey_der：获取der格式的公钥
 * @csign: 钥匙
 * @key_buf: 字符格式的密钥缓冲区如果成功，返回：字符缓冲区的长度
 */
int crypto_write_pubkey_der(struct crypto_key *csign, unsigned char **key_buf);

/**
 * crypto_free_buffer:加密API分配的空闲缓冲区
 * @buf: 缓冲区指针返回：无
 */
void crypto_free_buffer(unsigned char *buf);

/**
 * @crypto_ec_get_priv_key_der: 获取der格式的私钥
 * @key: 关键结构
 * @key_data: 字符缓冲区中的关键数据
 * @key_len =字符缓冲区的密钥长度如果成功返回：0
 */
int crypto_ec_get_priv_key_der(struct crypto_key *key, unsigned char **key_data, int *key_len);

/**
 * crypto_bignum_to_string:以ascii格式获取大数字
 * @a: 大的数字
 * @buf: 将数字写入的缓冲区
 * @buflen: 缓冲区长度
 * @padlen: padding length如果成功返回：0
 */
int crypto_bignum_to_string(const struct crypto_bignum *a,
                         u8 *buf, size_t buflen, size_t padlen);
#endif /* CRYPTO_H */

