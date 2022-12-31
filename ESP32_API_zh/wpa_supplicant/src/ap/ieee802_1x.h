/*
 * hostapd/IEEE 802.1X-2004身份验证器版权所有（c）2002-2012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef IEEE802_1X_H
#define IEEE802_1X_H

struct hostapd_data;
struct sta_info;
struct eapol_state_machine;
struct hostapd_config;
struct hostapd_bss_config;
struct hostapd_radius_attr;
struct radius_msg;


void ieee802_1x_receive(struct hostapd_data *hapd, const u8 *sa, const u8 *buf,
			size_t len);

#endif /* IEEE802_1X_H */

