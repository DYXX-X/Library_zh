/*
 * wlantest-IEEE 802.11协议监控和测试工具版权所有（c）2010-2013，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifdef CONFIG_IEEE80211W
#ifndef CCMP_H
#define CCMP_H

u8 * ccmp_decrypt(const u8 *tk, const u8 *hdr, const u8 *data,
		  size_t data_len, size_t *decrypted_len, bool espnow_pkt);
u8 * ccmp_encrypt(const u8 *tk, u8 *frame, size_t len, size_t hdrlen,
		  u8 *pn, int keyid, size_t *encrypted_len);
u8 * ccmp_encrypt_pv1(const u8 *tk, const u8 *a1, const u8 *a2, const u8 *a3,
		      const u8 *frame, size_t len,
		      size_t hdrlen, const u8 *pn, int keyid,
		      size_t *encrypted_len);
void ccmp_get_pn(u8 *pn, const u8 *data);
u8 * ccmp_256_decrypt(const u8 *tk, const u8 *hdr, const u8 *data,
		      size_t data_len, size_t *decrypted_len);
u8 * ccmp_256_encrypt(const u8 *tk, u8 *frame, size_t len, size_t hdrlen,
		      u8 *pn, int keyid, size_t *encrypted_len);

#endif /* CCMP_H */
#endif /* CONFIG_IEEE80211W */

