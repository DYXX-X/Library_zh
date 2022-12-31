/*
 * AES SIV（RFC 5297）版权所有（c）2013 Cozybit，Inc。
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef AES_SIV_H
#define AES_SIV_H

int aes_siv_encrypt(const u8 *key, size_t key_len,
		    const u8 *pw, size_t pwlen,
		    size_t num_elem, const u8 *addr[], const size_t *len,
		    u8 *out);
int aes_siv_decrypt(const u8 *key, size_t key_len,
		    const u8 *iv_crypt, size_t iv_c_len,
		    size_t num_elem, const u8 *addr[], const size_t *len,
		    u8 *out);

#endif /* AES_SIV_H */

