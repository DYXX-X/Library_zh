/*
 * PKCS#1（RSA加密）版权所有（c）2006-2009，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef PKCS1_H
#define PKCS1_H

int pkcs1_encrypt(int block_type, struct crypto_rsa_key *key,
		  int use_private, const u8 *in, size_t inlen,
		  u8 *out, size_t *outlen);
int pkcs1_v15_private_key_decrypt(struct crypto_rsa_key *key,
				  const u8 *in, size_t inlen,
				  u8 *out, size_t *outlen);
int pkcs1_decrypt_public_key(struct crypto_rsa_key *key,
			     const u8 *crypt, size_t crypt_len,
			     u8 *plain, size_t *plain_len);

#endif /* PKCS1_H */

