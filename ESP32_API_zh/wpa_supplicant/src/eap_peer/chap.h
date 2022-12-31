/*
 * CHAP-MD5（RFC 1994）版权所有（c）2007-2009，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef CHAP_H
#define CHAP_H

#define CHAP_MD5_LEN 16

int chap_md5(u8 id, const u8 *secret, size_t secret_len, const u8 *challenge,
	     size_t challenge_len, u8 *response);

#endif /* CHAP_H */

