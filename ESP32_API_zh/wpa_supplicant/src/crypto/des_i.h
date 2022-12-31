/*
 * DES和3DES-EDE密码版权所有（c）2006-2009，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef DES_I_H
#define DES_I_H

struct des3_key_s {
	u32 ek[3][32];
	u32 dk[3][32];
};

void des_key_setup(const u8 *key, u32 *ek, u32 *dk);
void des_block_encrypt(const u8 *plain, const u32 *ek, u8 *crypt);
void des_block_decrypt(const u8 *crypt, const u32 *dk, u8 *plain);

void des3_key_setup(const u8 *key, struct des3_key_s *dkey);
void des3_encrypt(const u8 *plain, const struct des3_key_s *key, u8 *crypt);
void des3_decrypt(const u8 *crypt, const struct des3_key_s *key, u8 *plain);

#endif /* DES_I_H */

