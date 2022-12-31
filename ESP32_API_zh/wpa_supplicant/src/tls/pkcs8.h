/*
 * PKCS#8（私钥信息语法）版权所有（c）2006-2009，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef PKCS8_H
#define PKCS8_H

struct crypto_private_key * pkcs8_key_import(const u8 *buf, size_t len);
struct crypto_private_key *
pkcs8_enc_key_import(const u8 *buf, size_t len, const char *passwd);

#endif /* PKCS8_H */

