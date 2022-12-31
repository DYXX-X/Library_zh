/*
 * IEEE 802.11通用例程版权所有（c）2002-2019，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef IEEE802_11_COMMON_H
#define IEEE802_11_COMMON_H

#include "defs.h"
#include "ieee802_11_defs.h"
#include "esp_wifi_driver.h"

struct element {
	u8 id;
	u8 datalen;
	u8 data[];
} STRUCT_PACKED;

/* 元素迭代助手*/
#define for_each_element(_elem, _data, _datalen)                        \
	for (_elem = (const struct element *) (_data);                  \
			(const u8 *) (_data) + (_datalen) - (const u8 *) _elem >=  \
			(int) sizeof(*_elem) &&                                 \
			(const u8 *) (_data) + (_datalen) - (const u8 *) _elem >=  \
			(int) sizeof(*_elem) + _elem->datalen;                  \
			_elem = (const struct element *) (_elem->data + _elem->datalen))

#define for_each_element_id(element, _id, data, datalen)                \
	for_each_element(element, data, datalen)                        \
	if (element->id == (_id))

struct wpa_supplicant;

int ieee802_11_parse_candidate_list(const char *pos, u8 *nei_rep,
				    size_t nei_rep_len);
const u8 * get_ie(const u8 *ies, size_t len, u8 eid);
int ieee802_11_parse_elems(struct wpa_supplicant *wpa_s, const u8 *start, size_t len);
int ieee802_11_ext_capab(const u8 *ie, unsigned int capab);
const u8 * get_vendor_ie(const u8 *ies, size_t len, u32 vendor_type);
size_t mbo_add_ie(u8 *buf, size_t len, const u8 *attr, size_t attr_len);
u8 get_operating_class(u8 chan, int sec_channel);
#endif /* IEEE802_11_COMMON_H */

