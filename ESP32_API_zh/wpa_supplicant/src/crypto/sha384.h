/*
 * SHA384哈希实现和接口函数版权所有（c）2015-2017，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef SHA384_H
#define SHA384_H

#define SHA384_MAC_LEN 48

int hmac_sha384_vector(const u8 *key, size_t key_len, size_t num_elem,
		       const u8 *addr[], const size_t *len, u8 *mac);
int hmac_sha384(const u8 *key, size_t key_len, const u8 *data,
		size_t data_len, u8 *mac);
int sha384_prf(const u8 *key, size_t key_len, const char *label,
	       const u8 *data, size_t data_len, u8 *buf, size_t buf_len);
int sha384_prf_bits(const u8 *key, size_t key_len, const char *label,
		    const u8 *data, size_t data_len, u8 *buf,
		    size_t buf_len_bits);
int tls_prf_sha384(const u8 *secret, size_t secret_len,
		   const char *label, const u8 *seed, size_t seed_len,
		   u8 *out, size_t outlen);
int hmac_sha384_kdf(const u8 *secret, size_t secret_len,
		    const char *label, const u8 *seed, size_t seed_len,
		    u8 *out, size_t outlen);

#endif /* SHA384_H */

