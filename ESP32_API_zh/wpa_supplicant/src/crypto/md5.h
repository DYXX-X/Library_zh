/*
 * MD5哈希实现和接口函数版权所有（c）2003-2009，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef MD5_H
#define MD5_H

#define MD5_MAC_LEN 16

int hmac_md5_vector(const u8 *key, size_t key_len, size_t num_elem,
		    const u8 *addr[], const size_t *len, u8 *mac);
int hmac_md5(const u8 *key, size_t key_len, const u8 *data, size_t data_len,
	     u8 *mac);

#endif /* MD5_H */

